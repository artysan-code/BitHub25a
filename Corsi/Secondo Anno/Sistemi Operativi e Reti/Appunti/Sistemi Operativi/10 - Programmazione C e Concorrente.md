# Programmazione C e Concorrente
Questa nota copre gli **elementi di programmazione in C** strumentali al laboratorio (slide 5): come un programma scritto in C usa concretamente i servizi del SO — system call, creazione di processi, segnali, comunicazione tra processi. È il complemento "a livello di codice" dei concetti teorici di [[02 - Concetti di Base e Strutture]] (system call), [[03 - Processi e Thread]] (processi e segnali) e [[04 - Sincronizzazione]] (IPC).
> [!info] Inquadramento
> Il C fu creato da **Dennis Ritchie (1972)** per scrivere UNIX, e molte scelte di UNIX traspaiono ancora nel linguaggio. Materiale strumentale: gli esempi (`5.x_*.c`) sono in `Materiale Didattico/.../code/`. Non serve impararlo a memoria, ma capire *come* il codice arriva al kernel.
## Everything is a file
La filosofia UNIX **"everything is a file"** ([[09 - Linux e BASH|già vista]]) si riflette nel C: socket, device, dischi, stampanti, modem, pipe sono trattati come file, cioè acceduti tramite **file descriptor**. Ogni processo nasce con tre file già aperti (vedi [[09 - Linux e BASH#I tre stream standard]] e [[02 - Concetti di Base e Strutture#Protezione e shell]]):

| Nome | Short | fd | Default |
|---|---|---|---|
| Standard In | `stdin` | 0 | tastiera |
| Standard Out | `stdout` | 1 | console |
| Standard Error | `stderr` | 2 | console |
## Stampare "Hello World" a tre livelli
Lo stesso risultato — scrivere su stdout — si ottiene a tre livelli di astrazione decrescente, ed è il filo conduttore per capire il rapporto **libreria ↔ system call**.
> [!example] (1) Libreria standard — `printf`
> ```c
> #include <stdio.h>
> int main(int argc, char **argv) {
>     printf("Hello World!\n");
>     return 0;
> }
> ```
> `printf` è una comoda funzione di **libreria** (`libc`), che internamente userà `write`.

> [!example] (2) System call POSIX — `write`
> ```c
> #include <unistd.h>
> #define STDOUT 1
> int main(int argc, char **argv) {
>     char msg[] = "Hello World!\n";
>     write(STDOUT, msg, sizeof(msg));   // write(fd, buf, len)
>     return 0;
> }
> ```
> `write(fd, buf, len)` scrive direttamente sul **file descriptor** 1 (stdout).

> [!example] (3) Chiamata diretta — `syscall`
> ```c
> #include <unistd.h>
> #include <sys/syscall.h>
> #define STDOUT 1
> int main(int argc, char **argv) {
>     char msg[] = "Hello World!\n";
>     syscall(SYS_write, STDOUT, msg, sizeof(msg));
>     return 0;
> }
> ```
> `syscall(numero, ...)` invoca la system call **per numero** (`SYS_write`), bypassando il wrapper di `libc`.
## Il processo di build
Da sorgente a eseguibile: il **C preprocessor** elabora `#include`/`#define` di `.c` e `.h`, il **C compiler** produce i file oggetto `.o`, il **linker** li unisce alle librerie (es. `libc.a`) generando il binario eseguibile (storicamente `a.out`). La struttura interna dell'eseguibile (header, numero magico, segmenti) è in [[07 - File System#Struttura interna dei file]].
## Dalla libreria alla system call
Cosa accade *davvero* quando un programma chiama `read()`? La catena, dal user space fino al kernel, è lunga (qui semplificata ma corretta). È l'approfondimento concreto del [[02 - Concetti di Base e Strutture#Meccanismo: i passi di una system call|meccanismo delle system call]].
> [!info] La libreria standard wrappa le system call
> `libc` fornisce wrapper comodi (`read`, `write`, `exit`, …). Il passaggio effettivo al kernel richiede l'istruzione macchina **`syscall`** (storicamente l'interrupt `int 0x80`), scritta in assembly dentro `libc`.

**Lato user space (glibc):**
1. `read()` è un alias di `__libc_read`, wrapper in `glibc/sysdeps/unix/sysv/linux/read.c`.
2. Chiama `SYSCALL_CANCEL(read, …)`, che gestisce la **pthread cancellation** (abilita/disabilita la cancellazione asincrona attorno alla syscall).
3. Si arriva a `INLINE_SYSCALL_CALL` → `internal_syscall3` (3 = numero di argomenti): prepara i registri secondo la **convenzione x86-64** — `%rdi`=fd, `%rsi`=buf, `%rdx`=count, `%rax`=numero della syscall (`__NR_read` = 0) — ed esegue l'istruzione `syscall`.

**Lato kernel:**
4. L'istruzione `syscall` salta all'indirizzo nel registro `MSR_LSTAR`, cioè l'entry point `entry_SYSCALL_64` (`arch/x86/entry/entry_64.S`): `swapgs`, salvataggio dello stack utente, `SWITCH_TO_KERNEL_CR3` (passa alla [[06 - Gestione della Memoria|page table]] del kernel), impostazione dello stack del kernel.
5. Chiama il dispatcher C `do_syscall_64` (`arch/x86/entry/syscall_64.c`) → `do_syscall_x64` → `x64_sys_call(regs, nr)`: uno **switch** generato automaticamente seleziona la funzione in base a `nr` (`case 0 → __x64_sys_read`).
6. `__x64_sys_read` è generata dalla macro `SYSCALL_DEFINE3(read, …)` in `fs/read_write.c` e chiama `ksys_read(fd, buf, count)`.
7. `ksys_read` esegue la logica reale: **lookup** del file descriptor, controllo dei permessi, lettura via `vfs_read()` → `file->f_op->read_iter`, fino al driver o al file system concreto (ext4, procfs, socket… vedi [[07 - File System|VFS]] e [[08 - Input Output]]).

| | User space (glibc) | Kernel |
|---|---|---|
| Punto d'ingresso | `read()` → `__libc_read` | `entry_SYSCALL_64` |
| Meccanismo | prepara i registri + `syscall` | dispatcher `do_syscall_64` |
| Funzione finale | — | `ksys_read` → `vfs_read` |
## Creazione di processi: fork, exec, wait
Le tre system call cardine (concetti in [[03 - Processi e Thread#System call di gestione]]); qui in C.
- **`fork()`** duplica il processo corrente: restituisce il **PID del figlio** al genitore e **0** al figlio (così i due rami si distinguono).
- **`wait(&status)`** sospende il genitore finché un figlio cambia stato (es. `exit` o segnale), scrivendo lo stato in `status`.
- **`execv(path, argv)`** sostituisce l'immagine del processo con un nuovo binario; `argv` termina con `NULL`. Esistono varianti (`execl`, `execlp`, `execvp`, …).
> [!example] fork + wait + execv
> ```c
> void main(void) {
>     int pid, child_status;
>     char *args[] = {"/bin/ls", "-l", NULL};
>     if (fork() == 0) {            // ramo figlio
>         execv(args[0], args);     // carica ed esegue /bin/ls
>     } else {                      // ramo padre
>         wait(&child_status);      // attende il figlio
>     }
> }
> ```

> [!example] Una shell minimale (in C)
> È la versione concreta del [[02 - Concetti di Base e Strutture#Protezione e shell|ciclo della shell]]:
> ```c
> while (1) {
>     char cmd[256], *args[256];
>     int status; pid_t pid;
>     read_command(cmd, args);   // legge comando e argomenti
>     pid = fork();
>     if (pid == 0) {
>         execv(cmd, args);      // figlio: esegue il comando
>         exit(1);               // raggiunto solo se execv fallisce
>     } else {
>         wait(&status);         // padre: attende
>     }
> }
> ```
## Segnali in C
I [[03 - Processi e Thread#I segnali|segnali]] gestiscono eventi asincroni. API principali:
- `signal(signum, handler)` registra un **gestore** (signal handler) per `signum`.
- `alarm(seconds)` consegna `SIGALRM` dopo un certo numero di secondi.
- `kill(pid, sig)` invia il segnale `sig` al processo `pid` — **non** lo "uccide" e basta (es. `Ctrl+C` → `SIGINT`, `Ctrl+Z` → `SIGTSTP`, vedi [[09 - Linux e BASH#Foreground e background|job control]]).
> [!example] alarm + handler
> ```c
> #include <stdio.h>
> #include <signal.h>
> #include <unistd.h>
> #include <stdlib.h>
> void alarm_handler(int signal) {
>     printf("In signal handler: caught signal %d!\n", signal);
>     exit(0);
> }
> int main(int argc, char **argv) {
>     signal(SIGALRM, alarm_handler);
>     alarm(1);                  // SIGALRM dopo 1 secondo
>     while (1) printf("I am running!\n");
>     return 0;
> }
> ```
## Comunicazione tra processi: le pipe
Le [[02 - Concetti di Base e Strutture#File speciali e pipe|pipe]] collegano processi su un canale FIFO. In shell: `cat names.txt | sort` (pipe anonima) oppure `mkfifo named.pipe` (pipe **con nome**). In C servono quattro system call: `open`, `close`, `pipe(pipefd[2])` (crea la pipe e i due fd delle estremità), `dup`/`dup2`.
### dup / dup2 e la redirezione
> [!quote] Definizione — dup / dup2
> `dup(oldfd)` duplica un file descriptor sul **più basso fd libero**; `dup2(oldfd, newfd)` lo duplica su un fd **specifico**. Servono ad **"agganciare"** `STDOUT_FILENO` (1) o `STDIN_FILENO` (0) a un file o a una pipe.

Questo è il **meccanismo concreto** dietro la [[09 - Linux e BASH#Redirezione e pipe|redirezione della shell]]: "cambiare dove punta un fd" significa fare `dup2` prima di `execv`.
> [!example] Redirezione dell'output su file
> ```c
> int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
> dup2(fd, STDOUT_FILENO);   // ora stdout punta a output.txt
> printf("Questo va in output.txt\n");
> close(fd);
> ```

> [!example] Pipeline `ps aux | grep httpd` in C
> ```c
> int fd[2];
> pipe(fd);
> if (fork() == 0) {                 // figlio: ps
>     close(fd[0]);
>     dup2(fd[1], STDOUT_FILENO);    // stdout → pipe
>     execlp("ps", "ps", "aux", NULL);
> } else {                           // padre: grep
>     close(fd[1]);
>     dup2(fd[0], STDIN_FILENO);     // stdin ← pipe
>     execlp("grep", "grep", "httpd", NULL);
> }
> ```
### Perché chiudere le estremità della pipe?
Le `close` sulle estremità non usate **non** sono opzionali:
1. **Evitare blocchi**: chi scrive può restare bloccato se un'estremità di lettura resta aperta.
2. **Ricezione EOF**: `sort` termina solo all'EOF, che arriva quando **tutte** le estremità di scrittura sono chiuse.
3. **Evitare letture accidentali** dalla pipe nel processo sbagliato.
4. Dopo `dup2`, chiudere il fd **originale** così ogni processo usa solo la pipe (lato scrittura in chi scrive, lato lettura in chi legge).
5. Il **padre** deve chiudere entrambe le estremità dopo la `fork`.
## File di esempio del laboratorio
Gli esempi del corso (in `Materiale Didattico/.../code/`):
- `5.1_hello_world_1/2/3.c` — le tre versioni di Hello World.
- `5.2_my_first_fork_1/2.c` — creazione di processi con `fork`.
- `5.3_my_signal_1/2.c` — gestione di segnali e allarmi.
- `5.4_fork_pipe.c` — comunicazione tra processi via pipe.
- `5.5_my_first_bash.c` — una BASH minimale in C.

Lo **script di compilazione** (`compile.sh`) fa parte del materiale: vale la pena studiarlo.
> [!example] Esercizio d'esame — somma di pari e dispari
> Un processo genera due figli **P1** e **P2**. P1 cicla generando interi casuali in $[0,100]$ e comunica al padre **solo i dispari**; P2 fa lo stesso ma **solo i pari**. Il padre, per ogni coppia ricevuta, ne calcola e stampa la somma. Il programma termina quando la somma supera **190**: il padre invia allora un segnale di terminazione a ciascun figlio. Richiede `fork`, `pipe`, `signal`/`kill`. Altre tracce in [[Tracce d'Esame Pratiche]].
## Collegamenti con altri argomenti
> [!info] Mappa dei rimandi
> - **Meccanismo delle system call (TRAP, registri, modalità kernel/user)** → [[02 - Concetti di Base e Strutture]]
> - **Processi, `fork`/`exec`/`wait`, segnali, stati** → [[03 - Processi e Thread]]
> - **IPC, pipe, race condition** → [[04 - Sincronizzazione]]
> - **fd standard, redirezione e pipe in shell, job control** → [[09 - Linux e BASH]]
> - **VFS ed eseguibili** → [[07 - File System]] · **driver e dispositivi** → [[08 - Input Output]]

---
**Argomento precedente:** [[09 - Linux e BASH]]
