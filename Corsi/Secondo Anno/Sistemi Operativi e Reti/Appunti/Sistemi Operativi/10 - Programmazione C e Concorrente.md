# Programmazione C e Concorrente
Questa nota copre gli **elementi di programmazione in C** strumentali al laboratorio (slide 5): come un programma scritto in C usa concretamente i servizi del SO — system call, creazione di processi, segnali, comunicazione tra processi. È il complemento "a livello di codice" dei concetti teorici di [[02 - Concetti di Base e Strutture]] (system call), [[03 - Processi e Thread]] (processi e segnali) e [[04 - Sincronizzazione]] (IPC).

> [!info] Inquadramento
> Il C fu creato da **Dennis Ritchie (1972)** per scrivere UNIX, e molte scelte di UNIX traspaiono ancora nel linguaggio. Materiale strumentale: gli esempi (`5.x_*.c`) sono in `Materiale Didattico/Sistemi Operativi/Esempi/`. Non serve impararlo a memoria, ma capire *come* il codice arriva al kernel.
## Everything is a file
La filosofia UNIX **"everything is a file"** ([[09 - Linux e BASH|già vista]]) si riflette nel C: socket, device, dischi, stampanti, modem, pipe sono trattati come file, cioè acceduti tramite **file descriptor**. Per convenzione, i programmi avviati da una shell hanno normalmente tre file già aperti (vedi [[09 - Linux e BASH#I tre stream standard]] e [[02 - Concetti di Base e Strutture#Protezione e shell]]):

| Nome | Short | fd | Default |
|---|---|---|---|
| Standard input | `stdin` | 0 | input (di solito la tastiera) |
| Standard output | `stdout` | 1 | output (di solito il terminale) |
| Standard error | `stderr` | 2 | messaggi di errore (di solito il terminale) |

Non sono necessariamente collegati alla tastiera o al terminale: possono essere reindirizzati a file o pipe.
## Stampare "Hello World" a tre livelli
Lo stesso risultato — scrivere su stdout — si ottiene a tre livelli di astrazione decrescente, ed è il filo conduttore per capire il rapporto **libreria ↔ system call**. Le firme usate nelle slide: `int printf(const char *format, ...);`, `ssize_t write(int fd, const void *buf, size_t count);`, `long syscall(long number, ...);`.

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
> int main(void) {
>     char msg[] = "Hello World!\n";
>     write(STDOUT_FILENO, msg, sizeof(msg) - 1);   // write(fd, buf, count)
>     return 0;
> }
> ```
> `write(fd, buf, count)` scrive direttamente sul **file descriptor** 1 (stdout, `STDOUT_FILENO`). Si usa `sizeof(msg) - 1` per non scrivere anche il terminatore `'\0'` della stringa (`sizeof` lo conta). Il file del laboratorio (`5.1_hello_world_2.c`) usa invece `#define STDOUT 1` e `sizeof(msg)`.

> [!example] (3) Chiamata diretta — `syscall`
> ```c
> #define _GNU_SOURCE
> #include <unistd.h>
> #include <sys/syscall.h>
> int main(void) {
>     char msg[] = "Hello World!\n";
>     syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg) - 1);
>     return 0;
> }
> ```
> `syscall(numero, ...)` invoca la system call **per numero** (`SYS_write`), bypassando il wrapper di `libc`. Gli esempi `5.1_hello_world_1/2/3.c` sono quelli mostrati a lezione.
## Il processo di build
Da sorgente a eseguibile, in tre fasi (figura della slide: file `defs.h`, `mac.h`, `main.c`, `help.c`, `other.c`):
1. il **C preprocessor** elabora i file sorgente `.c` e gli header `.h` (`#include`, `#define`);
2. il **C compiler** produce un file oggetto per ciascun sorgente (`main.o`, `help.o`, `other.o`);
3. il **linker** unisce i file oggetto alla libreria (`libc.a`) generando il **programma binario eseguibile** (storicamente `a.out`).

La struttura interna dell'eseguibile (header, numero magico, segmenti) è in [[07 - File System#Struttura interna dei file]].
## Dalla libreria alla system call
Cosa accade *davvero* quando un programma chiama `read()`? La catena, dal user space fino al kernel, è lunga (qui semplificata ma corretta). È l'approfondimento concreto del [[02 - Concetti di Base e Strutture#Meccanismo: i passi di una system call|meccanismo delle system call]].

> [!info] La libreria standard wrappa le system call
> La `libc` offre funzioni che permettono ai programmi di usare i servizi del sistema operativo. Alcune, come `read()` e `write()`, sono **wrapper** di system call; altre, come `printf()`, offrono funzionalità di livello più alto. Il programma richiama normalmente funzioni di libreria, senza eseguire direttamente istruzioni assembly.
>
> **Come si entra nel kernel?** Su Linux x86-64 il passaggio da modalità utente a modalità kernel avviene normalmente con l'istruzione macchina **`syscall`** (storicamente l'interrupt `int 0x80`, *(extra, non da slide)*), eseguita dentro la `libc`. La funzione `syscall()` della `libc` permette inoltre di invocare esplicitamente una system call Linux. Idea chiave: funzione C, wrapper di libreria e system call non sono necessariamente la stessa cosa.

Le tappe del viaggio di `read(fd, buf, n)`: (1) il programma la invoca; (2) `glibc` prepara gli argomenti e il numero della system call; (3) la CPU esegue l'istruzione `syscall` e passa in modalità kernel; (4) il kernel identifica la chiamata e la inoltra al gestore appropriato; (5) file system o driver eseguono la lettura; (6) il programma riceve il risultato. La domanda da tenere a mente: dove finisce il codice utente e dove comincia il kernel? Non servono le macro a memoria: serve capire il percorso. La slide indica anche una tabella delle system call (`filippo.io/linux-syscall-table`): per ciascuna, numero in `%rax`, argomenti in `%rdi`, `%rsi`, `%rdx`, … e punto d'ingresso (es. `0 read`, `1 write`, `2 open`, `3 close`); il valore di ritorno viene restituito in `%rax`.

**Lato user space (glibc):**
1. `read()` è un alias di `__libc_read` *(extra, non da slide)*, wrapper in `glibc/sysdeps/unix/sysv/linux/read.c`.
2. Il corpo è `return SYSCALL_CANCEL(read, fd, buf, nbytes);`. `SYSCALL_CANCEL` rende la chiamata compatibile con la **cancellazione dei thread** (pthread cancellation). Dalla glibc 2.41 non attiva più la cancellazione asincrona attorno alla syscall: chiama `__syscall_cancel()`, che controlla se il thread può essere cancellato. Se il processo ha un solo thread o la cancellazione non è attiva, esegue una syscall normale con le macro `INTERNAL_SYSCALL` (il percorso seguito sotto); altrimenti passa a `__syscall_cancel_arch()`, scritta in assembly. Motivo: se un thread viene cancellato mentre è bloccato in `read()`, glibc deve sapere con certezza se la syscall è già stata eseguita.
3. Si arriva a `INTERNAL_SYSCALL` (definita per architettura; per x86_64 in `glibc/sysdeps/unix/sysv/linux/x86_64/sysdep.h`) → `internal_syscall3` (3 = numero di argomenti): prepara i registri secondo la **convenzione x86-64** — `%rdi`=fd, `%rsi`=buf, `%rdx`=count, `%rax`=numero della syscall (`__NR_read` = 0) — ed esegue l'istruzione `syscall`. Il numero è una costante definita dal kernel (`arch/x86/entry/syscalls/syscall_64.tbl`, riga `0 common read sys_read`) e resa disponibile da glibc tramite gli header.

> [!example] `internal_syscall3` (slide)
> ```c
> #define internal_syscall3(number, arg1, arg2, arg3)            \
>    ({                                                              \
>        unsigned long resultvar;                                    \
>        register long _a1 asm("rdi") = arg1;                        \
>        register long _a2 asm("rsi") = arg2;                        \
>        register long _a3 asm("rdx") = arg3;                        \
>        asm volatile ("syscall\n\t"                                 \
>                      : "=a"(resultvar)                             \
>                      : "0"(number), "r"(_a1), "r"(_a2), "r"(_a3)   \
>                      : "memory", "cc", "r11", "cx");               \
>        (long) resultvar;                                           \
>    })
> ```
> È qui che viene realmente eseguita `syscall`: la macro carica il numero in `%rax` e gli argomenti nei registri della convenzione Linux a 64 bit.

`syscall` **non è una funzione C**: è un'istruzione macchina della CPU x86-64. Quando la CPU la esegue: passa dalla modalità utente alla modalità kernel; trasferisce il controllo a un indirizzo di ingresso configurato dal sistema operativo; memorizza in `RCX` l'indirizzo a cui riprendere l'esecuzione e in `R11` i flag della CPU precedenti alla chiamata, per il successivo ritorno al programma utente. Il passaggio di modalità è realizzato direttamente dall'hardware, non da una normale chiamata a funzione.

**Lato kernel:**
4. Durante l'inizializzazione Linux imposta il registro speciale `IA32_LSTAR` (`wrmsrq(MSR_LSTAR, (unsigned long)entry_SYSCALL_64)`): l'istruzione `syscall` salta quindi a `entry_SYSCALL_64` (`arch/x86/entry/entry_64.S`). Qui: `swapgs`, salvataggio dello stack utente, `SWITCH_TO_KERNEL_CR3` (KPTI: passa alla [[06 - Gestione della Memoria|page table]] del kernel), impostazione dello stack del kernel, salvataggio dei registri utente in `struct pt_regs`, poi `call do_syscall_64`.
5. `do_syscall_64` (`arch/x86/entry/syscall_64.c`) prepara il contesto con `syscall_enter_from_user_mode()` (aggiorna il context tracking, riabilita gli interrupt, gestisce ptrace, seccomp, audit e tracepoint), poi → `do_syscall_x64` → `x64_sys_call(regs, nr)`: uno **switch** generato automaticamente seleziona la funzione in base a `nr` (`case 0 → __x64_sys_read`). Dal kernel 6.9 lo switch sostituisce la chiamata indiretta tramite `sys_call_table`, come mitigazione di Spectre-BHI. L'header `syscalls_64.h` è generato in compilazione dalla tabella `syscall_64.tbl`.
6. `__x64_sys_read` è generata dalla macro `SYSCALL_DEFINE3(read, …)` in `fs/read_write.c` e chiama `ksys_read(fd, buf, count)`. `SYSCALL_DEFINEn` (da `DEFINE0` a `DEFINE6`) definisce una system call con `n` argomenti (es. `chmod` è `DEFINE2`, `linkat` è `DEFINE5`).
7. `ksys_read` esegue la logica reale: individua il file associato al descrittore, gestisce la posizione di lettura e invoca `vfs_read()`, che verifica le condizioni e inoltra la richiesta alle operazioni del file: `file->f_op->read` se disponibile, altrimenti `file->f_op->read_iter` tramite `new_sync_read()`, fino al driver o al file system concreto (ext4, procfs, pipe, socket… vedi [[07 - File System|VFS]] e [[08 - Input Output]]). Il VFS fornisce un'interfaccia uniforme verso oggetti differenti.

> [!info] Altre system call e gestori (slide)
> `write` → `ksys_write` (`fs/read_write.c`); `lseek` → `ksys_lseek`; `open` → `do_sys_open` (`fs/open.c`); `fchown` → `ksys_fchown`; `mkdirat` → `do_mkdirat` (`fs/namei.c`); `execve` → `do_execve` (`fs/exec.c`); `mprotect` → `do_mprotect_pkey` (`mm/mprotect.c`); `socket` → `__sys_socket`, `connect` → `__sys_connect` (`net/socket.c`); `setpriority` → `set_one_prio` (`kernel/sys.c`); `sched_setattr` → `sched_setattr` (`kernel/sched/syscalls.c`). Lista completa: `syscalls.mebeim.net`.

| | User space (glibc) | Kernel |
|---|---|---|
| Punto d'ingresso | `read()` → `__libc_read` | `entry_SYSCALL_64` |
| Meccanismo | prepara i registri + `syscall` | dispatcher `do_syscall_64` |
| Funzione finale | — | `ksys_read` → `vfs_read` |
## Creazione di processi: fork, exec, wait
Le tre system call cardine (concetti in [[03 - Processi e Thread#System call di gestione]]), qui usate in C:
- **`pid_t fork()`** duplica il processo corrente: restituisce il **PID del figlio** al genitore e **0** al figlio (così i due rami si distinguono).
- **`pid_t wait(int *wstatus)`** attende la terminazione di **uno qualsiasi** dei figli e ne restituisce il PID, scrivendo lo stato in `wstatus`. Per attendere un figlio specifico, o anche i figli sospesi, si usa `waitpid()`.
- **`int execv(const char *path, char *const argv[])`** carica un nuovo binario (`path`) nel processo corrente, rimuovendo tutte le altre mappature di memoria; `argv` contiene gli argomenti del programma e termina con `NULL` (es. `argv = {"/bin/ls", "-a", NULL}`). Esistono diverse varianti `exec(v)(p)` (si veda `man`: `execl`, `execlp`, `execvp`, …).

> [!example] fork + wait + execv
> ```c
> #include <stdio.h>
> #include <unistd.h>
> #include <sys/wait.h>
> int main(void) {
>     pid_t pid = fork();
>     if (pid < 0) {                // fork fallita
>         perror("fork");
>         return 1;
>     }
>     if (pid == 0) {               // ramo figlio
>         char *args[] = {"/bin/ls", "-l", NULL};
>         execv(args[0], args);     // carica ed esegue /bin/ls
>         perror("execv");          // raggiunto solo se execv fallisce
>         _exit(127);
>     }
>     waitpid(pid, NULL, 0);        // ramo padre: attende il figlio
>     return 0;
> }
> ```

> [!info] Varianti di `exec` e `wait` vs `waitpid` *(extra, non da slide)*
> Le varianti di `exec` differiscono per **come** si passano gli argomenti e se si cerca nel `PATH`:
> - **`execv`/`execvp`**: argomenti come **vettore** `argv[]` (terminato da `NULL`); la `p` (`execvp`, `execlp`) cerca l'eseguibile nel **`PATH`**, così si scrive `"ls"` invece di `"/bin/ls"`.
> - **`execl`/`execlp`**: argomenti come **lista** esplicita: `execl(path, arg0, arg1, …, NULL)`.
>
> Per attendere i figli: **`wait(&status)`** sospende finché **un qualsiasi** figlio termina; **`waitpid(pid, &status, 0)`** attende **uno specifico** figlio — indispensabile con più figli (come nelle tracce a due figli).

> [!info] Come il figlio comunica il codice d'uscita al padre *(extra, non da slide)*
> Il padre legge lo **stato** del figlio tramite `wait(&status)`, ma è il figlio a *impostarlo* chiamando **`exit(N)`** prima di terminare. Il valore `N` è recuperabile con la macro `WEXITSTATUS(status)` (dopo aver verificato `WIFEXITED(status)`). Se il figlio non chiama `exit` esplicitamente (es. `execv` va a buon fine e il processo figlio termina naturalmente), il valore di ritorno del `main` del programma eseguito fa le veci di `N`.
> ```c
> if (fork() == 0) {
>     /* ... lavoro del figlio ... */
>     exit(42);          // figlio: segnala codice 42 al padre
> } else {
>     wait(&status);
>     if (WIFEXITED(status))
>         printf("Figlio uscito con codice %d\n", WEXITSTATUS(status)); // stampa 42
> }
> ```

> [!question] Domanda tipica d'esame
> - **D:** Cosa restituisce `fork()` e come fanno padre e figlio a distinguersi? **R:** `fork()` duplica il processo; restituisce il **PID del figlio** al genitore e **0** al figlio (`-1` in caso di errore). I due rami eseguono lo stesso codice ma si distinguono testando il valore di ritorno: `if (fork() == 0) { /* figlio */ } else { /* padre */ }`.
> - **D:** Differenza tra `wait` e `waitpid`. **R:** `wait(&status)` attende la terminazione di **un qualsiasi** figlio; `waitpid(pid, &status, 0)` attende il figlio **con quel PID** specifico — utile quando un processo ne ha generati più di uno.

> [!example] Una shell minimale (in C)
> È la versione concreta del [[02 - Concetti di Base e Strutture#Protezione e shell|ciclo della shell]]: attende che l'utente digiti un comando, avvia un processo per eseguirlo (`fork` + `execv`), attende che il processo termini (`wait`).
> ```c
> while (1) {
>     char cmd[256], *args[256];
>     int status; pid_t pid;
>     read_command(cmd, args);   // legge comando e argomenti
>     pid = fork();
>     if (pid == 0) {
>         execv(cmd, args);      // figlio: esegue il comando
>         _exit(127);            // raggiunto solo se execv fallisce
>     } else {
>         wait(&status);         // padre: attende
>     }
> }
> ```

> [!info] Com'è fatta `read_command`? (`getline` + `strtok`) *(extra, non da slide: dal codice 5.5)*
> La shell minima usa `read_command`, che concretamente: legge una riga con **`getline(&line, &len, stdin)`** (restituisce **−1** all'EOF, cioè `Ctrl+D` → si esce dal ciclo); poi la **tokenizza** con **`strtok(line, " \n")`**, riempiendo `args[]` (terminato da `NULL`, come richiesto da `execvp`). Se `execvp` fallisce, si chiama `perror(...)` ed `exit(1)`.

> [!info] Comandi builtin: gestiti dal padre senza `fork` *(extra, non da slide: dal codice 5.5)*
> La shell minimale manca di un dettaglio presente in `5.5_my_first_bash.c`: i **comandi builtin** (come `exit`) devono essere intercettati *prima* della `fork`, perché appartengono al processo shell stesso — non ha senso delegarli a un figlio. La distinzione è strutturale:
> ```c
> read_command(cmd, args);
>
> if (strcmp(cmd, "exit") == 0)   // builtin: gestito dal padre, senza fork
>     exit(0);
>
> pid = fork();                   // solo per i comandi esterni
> if (pid == 0) {
>     execvp(cmd, args);
>     exit(1);
> } else {
>     wait(&status);
> }
> ```
> Questa è la ragione per cui una shell reale mantiene una lista di builtin (`cd`, `exit`, `export`, …) che non genera processi figli.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Processi|fork_sum.c]], [[Indice degli Esercizi#Processi|fork_pari_dispari_soglia.c]], [[Indice degli Esercizi#Processi|fork_catena_moltiplica.c]], [[Indice degli Esercizi#Processi|matrix_fork.c]], [[Indice degli Esercizi#Processi|26_01_24_appello.c]].
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Processi|P2]], [[Tracce d'Esame Pratiche#Processi|P3]], [[Tracce d'Esame Pratiche#Processi|P5]], [[Tracce d'Esame Pratiche#Processi|P6]], [[Tracce d'Esame Pratiche#Processi|P10]].
## Segnali in C
I [[03 - Processi e Thread#I segnali|segnali]] gestiscono eventi asincroni: a volte un processo deve essere interrotto durante la sua esecuzione, e gli si invia un segnale. Il processo interrotto può **catturare** il segnale installando un gestore di segnali (*signal handler*).

Quando l'utente preme una combinazione di tasti, il **driver del terminale** la intercetta e invia un segnale a tutti i processi del gruppo in foreground:
- `Ctrl+C` → `SIGINT`: per default termina il processo;
- `Ctrl+Z` → `SIGTSTP`: per default sospende il processo (vedi [[09 - Linux e BASH#Foreground e background|job control]]);
- `Ctrl+\` → `SIGQUIT`: per default termina il processo e genera un core dump.

API principali:
- `sighandler_t signal(int signum, sighandler_t handler)` registra un **gestore** (signal handler) per `signum`.
- `unsigned int alarm(unsigned int seconds)` consegna `SIGALRM` dopo il numero di secondi specificato.
- `int kill(pid_t pid, int sig)` invia il segnale `sig` al processo `pid` — **non** lo "uccide" e basta: l'effetto dipende dal segnale e dal gestore installato. `SIGKILL` e `SIGSTOP` non possono essere né catturati né ignorati.

> [!example] alarm + handler
> ```c
> #include <stdio.h>
> #include <signal.h>
> #include <unistd.h>
> #include <stdlib.h>
> void alarm_handler(int sig) {
>     const char msg[] = "Allarme ricevuto!\n";
>     write(STDOUT_FILENO, msg, sizeof(msg) - 1);
>     _exit(0);
> }
> int main(int argc, char **argv) {
>     signal(SIGALRM, alarm_handler);
>     alarm(1);                  // SIGALRM dopo 1 secondo
>     while (1) {
>         printf("I am running!\n");
>     }
>     return 0;
> }
> ```
> Nell'handler la slide usa `write` e `_exit` invece di `printf` ed `exit`. Il file del laboratorio (`5.3_my_signal_2.c`) usa `printf` con `strsignal` ed `exit(0)`.

> [!example] Intercettare `Ctrl+C` (`SIGINT`) *(extra, non da slide)*
> ```c
> #include <stdio.h>
> #include <signal.h>
> #include <string.h>
> #include <unistd.h>
> void handler(int sig) {
>     printf("Ricevuto: %s\n", strsignal(sig));  // nome leggibile del segnale
> }
> int main(void) {
>     signal(SIGINT, handler);   // Ctrl+C non termina piu' il processo
>     while (1) pause();         // attende un segnale
> }
> ```
> `strsignal(sig)` restituisce la descrizione testuale del segnale (es. "Interrupt"). Catturando `SIGINT` con un handler, `Ctrl+C` viene gestito invece di terminare il programma.

> [!info] `sigaction` e `SIGUSR1`/`SIGUSR2` *(extra, non da slide)*
> Le slide usano solo `signal()`. `sigaction(signum, &act, NULL)` è l'alternativa con comportamento ben definito (si imposta `act.sa_handler` e `act.sa_flags`); `SIGUSR1` e `SIGUSR2` sono segnali **riservati all'utente**, senza significato predefinito (per default terminano il processo), usati come notifiche tra processi: `kill(pid, SIGUSR1)`.
> ```c
> #include <stdio.h>
> #include <signal.h>
> #include <string.h>
> #include <unistd.h>
> static void handler(int sig) {
>     const char msg[] = "ricevuto SIGUSR1\n";
>     (void)sig;
>     write(STDOUT_FILENO, msg, sizeof(msg) - 1);
> }
> int main(void) {
>     struct sigaction act;
>     memset(&act, 0, sizeof(act));
>     act.sa_handler = handler;
>     sigaction(SIGUSR1, &act, NULL);
>     kill(getpid(), SIGUSR1);   // il processo invia il segnale a se stesso
>     return 0;
> }
> ```

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Processi|fork_pari_dispari_soglia.c]] e [[Indice degli Esercizi#Processi|fork_sum.c]] terminano i figli con `kill(pid, SIGTERM)`.
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Processi|P2]], [[Tracce d'Esame Pratiche#Processi|P6]].
## Comunicazione tra processi: le pipe
Le [[02 - Concetti di Base e Strutture#File speciali e pipe|pipe]] collegano processi su un canale FIFO. In shell: `cat names.txt | sort` (pipe anonima: la shell collega l'output standard di `cat` all'input standard di `sort`) oppure `mkfifo named.pipe` (pipe **con nome**, FIFO). In C servono le system call:
- `int open(const char *pathname, int flags, ...)` apre il file indicato; il parametro `mode` va aggiunto quando si usa `O_CREAT`;
- `int close(int fd)` chiude il descrittore `fd`;
- `int pipe(int pipefd[2])` crea una pipe con due fd per le sue estremità (`pipefd[0]` lettura, `pipefd[1]` scrittura);
- `int dup(int oldfd)` copia `oldfd` usando il fd inutilizzato con il numero più basso; `dup2` (sotto).

> [!example] Pipe con nome (`mkfifo`)
> A differenza della pipe anonima (che vive solo tra processi imparentati), una **named pipe** è un file persistente nel file system creato con `mkfifo`, usabile anche tra processi **non** imparentati:
> ```bash
> mkfifo named.pipe
> echo "Hello World!" > named.pipe &   # un processo scrive (si blocca finché qualcuno legge)
> cat named.pipe                       # un altro processo legge
> ```
> `mkfifo` crea una FIFO accessibile tramite un nome nel file system. Il processo che scrive attende che la FIFO venga aperta anche in lettura; `cat` riceve e visualizza i dati. Senza `&` la shell resterebbe bloccata sull'`echo`, in attesa di un lettore, e non potrebbe eseguire il `cat` successivo dallo stesso terminale.
### dup / dup2 e la redirezione
> [!quote] Definizione — dup / dup2
> `dup(oldfd)` duplica un file descriptor sul **più basso fd libero**; `dup2(oldfd, newfd)` lo duplica su un fd **specifico**. Servono ad **"agganciare"** `STDOUT_FILENO` (1) o `STDIN_FILENO` (0) a un file o a una pipe.

Questo è il **meccanismo concreto** dietro la [[09 - Linux e BASH#Redirezione e pipe|redirezione della shell]]: "cambiare dove punta un fd" significa fare `dup2` prima di `execv`.

> [!example] Redirezione dell'output su file
> ```c
> int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
> dup2(fd, STDOUT_FILENO);   // ora stdout punta a output.txt
> printf("Questo va in output.txt\n");
> close(fd);
> ```
> L'output viene scritto in `output.txt` invece che in console (uso tipico: log, salvataggio dell'output). `O_TRUNC` svuota il file se esiste già.

> [!example] Pipeline `ps aux | grep httpd` in C
> ```c
> int fd[2];
> pipe(fd);
> if (fork() == 0) {                 // figlio: ps
>     close(fd[0]);
>     dup2(fd[1], STDOUT_FILENO);    // stdout → pipe
>     close(fd[1]);                  // l'originale non serve più
>     execlp("ps", "ps", "aux", NULL);
> } else {                           // padre: grep
>     close(fd[1]);
>     dup2(fd[0], STDIN_FILENO);     // stdin ← pipe
>     close(fd[0]);
>     execlp("grep", "grep", "httpd", NULL);
> }
> ```
> Esempio minimale (avvertenza della slide): il processo padre viene **sostituito** da `grep` tramite `execlp`, quindi non resta una shell in attesa dei comandi successivi. Una shell vera crea normalmente due processi figli per i programmi della pipeline, mentre il padre mantiene il controllo e può attenderli: l'esempio con due figli è più sotto.

> [!example] Output di un figlio su un file di log (`O_APPEND`)
> ```c
> if (fork() == 0) {
>     int log_fd = open("logfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
>     dup2(log_fd, STDOUT_FILENO);    // l'output va in logfile.txt
>     close(log_fd);
>     execlp("ls", "ls", "-l", NULL); // comando eseguito dal figlio
> }
> ```
> L'output di `ls -l` va in `logfile.txt` (`O_APPEND` aggiunge in coda senza svuotare il file). `execlp` sostituisce il processo corrente con il programma indicato. Uso tipico: logging centralizzato.

> [!info] Variante del laboratorio: `close` + `dup`
> Gli esempi del corso (`5.4_fork_pipe.c`) spesso usano, invece di `dup2`, la coppia equivalente **`close` + `dup`**. Poiché `dup(oldfd)` occupa il **fd libero più basso**, chiudendo prima `STDOUT_FILENO` (1) e poi facendo `dup(fd[1])`, il duplicato finisce proprio sull'fd 1: quindi `close(STDOUT_FILENO); dup(fd[1]);` equivale a `dup2(fd[1], STDOUT_FILENO);`.

> [!example] Due figli con due `waitpid` distinti (`cat | sort`)
> A differenza del caso `ps | grep` (dove il **padre** diventa `grep` con `execlp`), qui il padre **resta in vita**: esegue **due `fork` sequenziali** e poi raccoglie ciascun figlio con il proprio `waitpid`. È il pattern del laboratorio (`5.4_fork_pipe.c`) e delle tracce d'esame a due figli (P2/P3/P4):
> ```c
> pid_t cat_pid, sort_pid;
> int fd[2];
> pipe(fd);
>
> cat_pid = fork();
> if (cat_pid == 0) {                  // figlio 1: cat
>     dup2(fd[1], STDOUT_FILENO);      // stdout → pipe
>     close(fd[0]); close(fd[1]);
>     execlp("cat", "cat", "names.txt", NULL);
> }
>
> sort_pid = fork();                   // la seconda fork avviene nel PADRE
> if (sort_pid == 0) {                 // figlio 2: sort
>     dup2(fd[0], STDIN_FILENO);       // stdin ← pipe
>     close(fd[0]); close(fd[1]);
>     execlp("sort", "sort", NULL);
> }
>
> close(fd[0]); close(fd[1]);          // il padre chiude entrambe le estremità
> waitpid(cat_pid,  NULL, 0);          // attende il figlio 1
> waitpid(sort_pid, NULL, 0);          // attende il figlio 2
> ```
> La **seconda `fork` è eseguita dal padre** (il figlio 1 ha già fatto `execlp` e non la raggiunge). Ogni `waitpid` identifica uno specifico figlio tramite il suo PID: un `wait` generico non consentirebbe di attenderli in un ordine preciso.

> [!question] Domanda tipica d'esame
> - **D:** Come si realizza in C la redirezione dell'output di un programma su una pipe (o un file)? **R:** Si **aggancia** lo stdout alla pipe/file con `dup2(fd, STDOUT_FILENO)` (o `close(STDOUT_FILENO); dup(fd);`) **prima** della `execv`: il programma eseguito scriverà su `STDOUT_FILENO` (1) senza saperlo, ma l'fd 1 ora punta alla pipe/file. È il meccanismo dietro la redirezione della shell.
### Perché chiudere le estremità della pipe?
**Regola di fondo**: ogni processo deve chiudere le estremità della pipe che non utilizza. Il lettore riceve EOF solo quando **tutte** le estremità di scrittura sono chiuse; se tutte le estremità di lettura sono chiuse, una scrittura provoca `SIGPIPE` (oppure fallisce con `EPIPE`). Lasciare descrittori inutilizzati aperti può impedire la corretta terminazione dei processi.

Le `close` sulle estremità non usate **non** sono opzionali, per queste ragioni:
1. **Evitare blocchi e `SIGPIPE` mancati**: se un'estremità di lettura resta aperta in un processo che non legge, lo scrittore non riceve `SIGPIPE` e, a pipe piena, resta bloccato.
2. **Ricezione EOF**: `sort` termina solo all'EOF, che arriva quando **tutte** le estremità di scrittura sono chiuse.
3. **Evitare letture accidentali** dalla pipe nel processo sbagliato.
4. Dopo `dup2`, chiudere il fd **originale** così ogni processo usa solo la pipe (lato scrittura in chi scrive, lato lettura in chi legge).
5. Il **padre** deve chiudere entrambe le estremità dopo la `fork`.

> [!example] Esercizio d'esame — somma di pari e dispari
> Un processo genera due figli **P1** e **P2**. P1 cicla generando interi casuali in $[0,100]$ e comunica al padre **solo i dispari**; P2 fa lo stesso ma **solo i pari**. Il padre, per ogni coppia ricevuta, ne calcola e stampa la somma. Il programma termina quando la somma supera **190**: il padre invia allora un segnale di terminazione a ciascun figlio. Richiede `fork`, `pipe`, `signal`/`kill`. Soluzione: [[Tracce d'Esame Pratiche#Processi|P2]]; altre tracce in [[Tracce d'Esame Pratiche]].
>
> Specifiche della slide: una pipe **distinta** per ciascun figlio; a ogni iterazione il padre legge un numero da P1 e uno da P2 (la «coppia»); alla fine il padre invia `SIGTERM` a entrambi i figli e ne attende la terminazione con `waitpid()`. Attenzione: se i figli chiamano `srand()` con lo stesso seme generano la stessa sequenza; la slide suggerisce `srand(time(NULL) ^ getpid())` dopo la `fork()`.

> [!info] Mettiti alla prova
> - **C — pipe:** [[Indice degli Esercizi#Processi|fork_sum.c]], [[Indice degli Esercizi#Processi|fork_seek_occurrences.c]], [[Indice degli Esercizi#Processi|fork_file_pari_dispari.c]], [[Indice degli Esercizi#Processi|fork_fusione_pari_dispari.c]].
> - **dup/dup2 + pipe bidirezionale:** [[Indice degli Esercizi#Processi|fork_pipe_bidirezionale_quadrato.c]] (traccia [[Tracce d'Esame Pratiche#Processi|P7]]).
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Processi|P1]], [[Tracce d'Esame Pratiche#Processi|P8]], [[Tracce d'Esame Pratiche#Processi|P9]].
## File di esempio del laboratorio
*(Sezione di riferimento rapido — inventario del codice, non argomento d'esame.)* Gli esempi del corso (in `Materiale Didattico/Sistemi Operativi/Esempi/`):
- `5.1_hello_world_1/2/3.c` — le tre versioni di Hello World.
- `5.2_my_first_fork_1/2.c` — creazione di processi con `fork` (`_1`: un semplice esempio di invocazione di `fork`; `_2`: creazione dei processi e avvio di applicazioni da codice C).
- `5.3_my_signal_1/2.c` — gestione di segnali (`_1`) e di allarmi (`_2`).
- `5.4_fork_pipe.c` — comunicazione tra processi via pipe.
- `5.5_my_first_bash.c` — una BASH minimale in C.

Lo **script di compilazione** (`compile.sh`) fa parte del materiale: vale la pena studiarlo.

> [!info] `compile.sh` e i livelli di ottimizzazione
> Lo script (shebang `#!/bin/bash`, variabile `CC=clang`, `OPTIONS="-O2"`) compila gli esempi con `clang` (o `gcc`, intercambiabili) ed espone i flag di **ottimizzazione**: `-O0` (nessuna ottimizzazione → compilazione rapida e debug facile), `-O1`/`-O2`/`-O3` (ottimizzazioni crescenti → eseguibile più veloce ma compilazione più lenta e codice più difficile da debuggare). Lo script usa `-O2`; gli altri livelli sono descritti nei suoi commenti.
>
> *(extra, non da slide)* I file `5.2_my_first_fork_1.c`, `5.2_my_first_fork_2.c` e `5.4_fork_pipe.c` usano `wait`/`waitpid` senza `#include <sys/wait.h>`: con compilatori recenti (GCC ≥ 14, clang ≥ 16) la dichiarazione implicita è un **errore** e non compilano finché non si aggiunge l'include.
## Collegamenti con altri argomenti
> [!info] Mappa dei rimandi
> - **Meccanismo delle system call (TRAP, registri, modalità kernel/user)** → [[02 - Concetti di Base e Strutture]]
> - **Processi, `fork`/`exec`/`wait`, segnali, stati** → [[03 - Processi e Thread]]
> - **IPC, pipe, race condition** → [[04 - Sincronizzazione]]
> - **fd standard, redirezione e pipe in shell, job control** → [[09 - Linux e BASH]]
> - **VFS ed eseguibili** → [[07 - File System]] · **driver e dispositivi** → [[08 - Input Output]]

---
**Argomento precedente:** [[09 - Linux e BASH]]
