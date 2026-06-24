# Concetti di Base e Strutture
Il sistema operativo offre le proprie funzionalità — i **servizi** (es. *File System Service*, *Process Management Service*) — alle applicazioni attraverso le **chiamate di sistema**. Questa nota copre l'interfaccia (system call), le astrazioni fondamentali che il SO espone (processo, file) e le architetture interne con cui può essere costruito. Prerequisito: [[01 - Introduzione ai Sistemi Operativi]].
## System call (chiamate di sistema)
Le **system call** sono l'interfaccia con cui un processo in [[01 - Introduzione ai Sistemi Operativi#Modalità kernel e modalità utente|modalità utente]] richiede un servizio al kernel. Il meccanismo è **specifico** del SO e dell'hardware, perciò viene **incapsulato** in una libreria: in UNIX la **libreria C** (`libc`, basata su POSIX) esporta una procedura per ogni chiamata di sistema.
### Meccanismo: i passi di una system call
Dal punto di vista del programmatore una system call **sembra** una normale chiamata di funzione (`read(...)`), ma sotto c'è un passaggio in più: la funzione di libreria è solo un **involucro sottile** che prepara i dati ed esegue una **TRAP**, l'unica istruzione capace di portare la CPU in [[01 - Introduzione ai Sistemi Operativi#Modalità kernel e modalità utente|modalità kernel]]. Il codice utente non può "saltare" nel kernel di sua iniziativa: deve passare per la trap, che entra solo in punti controllati.

> [!info] I tre livelli attraversati
> **Applicazione** → *function call* → **libreria (`libc`)** → *system call / TRAP* → **kernel (SO)** → **hardware** (CPU, memoria, periferiche).
> La libreria fa da ponte: l'applicazione chiama una funzione comoda e portabile (basata su POSIX), la `libc` si occupa dei dettagli — dipendenti dal SO e dall'hardware — per entrare nel kernel. È questo che rende il codice C portabile tra UNIX diversi.

Esempio: `read(fd, buffer, nbytes)`. Il diagramma del corso (figura di Tanenbaum) scompone la chiamata in **11 passi**; la colonna *modalità* mostra dove avviene ciascuno e dove si attraversa la barriera utente↔kernel:

| # | Cosa succede | Modalità |
|---|---|---|
| 1–3 | Il chiamante colloca i parametri `fd`, `&buffer`, `nbytes` nei **registri** (`RDI`, `RSI`, `RDX`) o sullo **stack** se sono troppi | utente |
| 4 | Chiama la procedura di libreria `read()` della `libc` (ancora una normale chiamata di funzione) | utente |
| 5 | La `libc` mette il **numero** della system call in `RAX` — l'indice che identifica *quale* gestore del kernel eseguire | utente |
| 6 | Esegue l'istruzione **TRAP** (`SYSCALL` su x86-64): commuta in modalità kernel; è come una call ma *cambia modalità* e può saltare solo a indirizzi controllati | utente → kernel |
| 7 | **Dispatch**: il kernel usa il numero in `RAX` per indicizzare la **tabella delle system call** e trovare il gestore corrispondente | kernel |
| 8 | Esegue il **gestore**: valida i parametri e svolge il servizio (qui: legge dal file descriptor) | kernel |
| 9 | Il controllo torna alla procedura di libreria, all'istruzione **successiva alla TRAP** | kernel → utente |
| 10 | La libreria **ritorna** al programma, che prosegue come dopo una normale chiamata | utente |
| 11 | Il programma **ripulisce lo stack** (incremento dello Stack Pointer), come dopo ogni chiamata di funzione | utente |

> [!warning] La chiamata può bloccare
> Se il dato richiesto non è disponibile, la system call **blocca** il processo: il SO ne esegue altri e riprende il chiamato quando la condizione è soddisfatta. Lo stato di blocco è gestito dallo [[05 - Scheduling|scheduler]].

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> L'istruzione TRAP, il cambio di modalità e la gestione di interrupt sono il punto di contatto con l'hardware: vedi il livello ISA in [[5 - Livello di architettura dell'insieme d'istruzioni]].

> [!info] Approfondimento — dalla libc al kernel
> La catena completa da `read()` (user space) fino a `ksys_read()` (kernel) — `glibc` → istruzione `syscall` → `entry_SYSCALL_64` → `do_syscall_64` → `__x64_sys_read` — è ricostruita passo-passo in [[10 - Programmazione C e Concorrente#Dalla libreria alla system call]].
### Categorie principali di system call POSIX
**Gestione dei processi** (vedi [[03 - Processi e Thread]]):

| Call                                    | Descrizione                                  |
| --------------------------------------- | -------------------------------------------- |
| `pid = fork()`                          | Crea un processo figlio identico al genitore |
| `pid = waitpid(pid, &statloc, options)` | Attende la terminazione di un figlio         |
| `s = execve(name, argv, environp)`      | Sostituisce l'immagine del processo          |
| `exit(status)`                          | Termina il processo e restituisce lo stato   |

> [!info] Come funziona `fork()`: duplicazione e doppio ritorno
> `fork()` **non avvia un altro programma**: **duplica** il processo che la chiama. Subito dopo esistono **due processi** quasi identici — il **padre** (l'originale) e il **figlio** (la copia) — che eseguono lo **stesso codice** e proseguono **entrambi dalla riga successiva** alla `fork()`, come se il programma venisse eseguito due volte in parallelo.
> Per far fare loro cose diverse (il sorgente è uno solo) si usa il **valore restituito**, diverso nei due processi:
> - nel **figlio** vale `0`;
> - nel **padre** vale il **PID del figlio** (> 0);
> - vale `-1` se la creazione fallisce (nessun figlio creato; causa leggibile da `errno`).
>
> ```c
> pid_t pid = fork();
> if (pid == 0) {
>     /* lo esegue SOLO il figlio */
> } else if (pid > 0) {
>     /* lo esegue SOLO il padre — pid è il PID del figlio */
> } else {
>     /* errore: fork fallita */
> }
> ```
> Quindi `pid` non è "il proprio identificatore", ma il modo per sapere **in quale dei due processi mi trovo**. Per il PID vero ci sono `getpid()` (il proprio) e `getppid()` (quello del padre). Il flusso completo padre-figlio è in [[03 - Processi e Thread]] e, lato programmazione C, in [[10 - Programmazione C e Concorrente]].

**Gestione dei file** (vedi [[07 - File System]]):

| Call | Descrizione |
|------|-------------|
| `fd = open(file, how, ...)` | Apre un file in lettura/scrittura |
| `s = close(fd)` | Chiude un file aperto |
| `n = read(fd, buffer, nbytes)` | Legge dati da un file in un buffer |
| `n = write(fd, buffer, nbytes)` | Scrive dati da un buffer su file |
| `position = lseek(fd, offset, whence)` | Sposta il puntatore del file |
| `s = stat(name, &buf)` | Ottiene informazioni sullo stato di un file |

**Gestione di directory e file system**:

| Call | Descrizione |
|------|-------------|
| `s = mkdir(name, mode)` | Crea una directory |
| `s = rmdir(name)` | Rimuove una directory vuota |
| `s = link(name1, name2)` | Crea una voce `name2` che punta a `name1` |
| `s = unlink(name)` | Rimuove una voce di directory |
| `s = mount(special, name, flag)` | Monta un file system |
| `s = umount(special)` | Smonta un file system |

**Varie**:

| Call | Descrizione |
|------|-------------|
| `s = chdir(dirname)` | Cambia la directory di lavoro |
| `s = chmod(name, mode)` | Modifica i bit di protezione di un file |
| `s = kill(pid, signal)` | Invia un **segnale** a un processo (non lo "uccide" e basta!) |
| `s = time(&seconds)` | Secondi trascorsi dal 1° gennaio 1970 |

Convenzioni dei valori di ritorno: `pid` = id processo, `fd` = file descriptor, `n` = numero di byte, `s` = esito. Quasi tutte le call ritornano **-1 in caso di errore** — impostando la variabile globale `errno`, che `perror()` traduce in un messaggio leggibile — e `0` o un valore utile in caso di successo (`open` → un `fd ≥ 0`; `read` → byte letti, `0` a fine file; `lseek` → la nuova posizione). Tre **eccezioni** da ricordare: `fork()` ritorna **due volte** (riquadro sopra); `execve()` **non ritorna** se ha successo — l'immagine del processo è stata sostituita — e dà `-1` solo su errore (mnemonico: *se `execve` ritorna, è andata male*); `exit()` **non ritorna mai**, perché termina il processo (lo `status`, 0–255, lo raccoglie il padre con `waitpid`).
### API Win32 di Windows
Windows offre API equivalenti (non identiche) alle system call UNIX:

| UNIX             | Win32                               | Note                                                    |
| ---------------- | ----------------------------------- | ------------------------------------------------------- |
| `fork`           | `CreateProcess`                     | `CreateProcess` = `fork` + `execve`                     |
| `waitpid`        | `WaitForSingleObject`               | Attende un processo                                     |
| `execve`         | (nessuna)                           | `CreateProcess` assorbe già `execve`                    |
| `exit`           | `ExitProcess`                       | Termina il processo                                     |
| `open`/`close`   | `CreateFile`/`CloseHandle`          |                                                         |
| `read`/`write`   | `ReadFile`/`WriteFile`              |                                                         |
| `lseek`          | `SetFilePointer`                    |                                                         |
| `stat`           | `GetFileAttributesEx`               | Ottiene attributi del file                              |
| `mkdir`/`rmdir`  | `CreateDirectory`/`RemoveDirectory` |                                                         |
| `unlink`         | `DeleteFile`                        |                                                         |
| `link`           | (nessuna)                           | Win32 non supporta i link                               |
| `mount`/`umount` | (nessuna)                           | Win32 non supporta `mount`                              |
| `chdir`          | `SetCurrentDirectory`               |                                                         |
| `chmod`          | (nessuna)                           | Win32 non supporta i permessi POSIX (NT ha ACL proprie) |
| `kill`           | (nessuna)                           | Win32 non supporta i segnali                            |
| `time`           | `GetLocalTime`                      | Ora locale di sistema                                   |
### Costo delle system call
Una system call è **costosa**: richiede un cambio di contesto user↔kernel, salvataggio/ripristino dei registri, validazione dei parametri ed eventuale blocco del chiamante. Per questo si tende a minimizzarne il numero (es. I/O bufferizzato).

> [!example] Domande tipiche d'esame
> - **D:** Cosa sono le system call e perché vengono incapsulate in una libreria? **R:** Sono il meccanismo con cui un processo in **modalità utente** richiede un servizio al kernel. Il meccanismo è specifico del SO e dell'hardware, quindi viene **incapsulato** nella libreria C (`libc`, basata su POSIX), che esporta una funzione per ogni system call → **portabilità** del codice.
> - **D:** Descrivi i passi di una system call (es. `read`). **R:** (1) i parametri vanno nei **registri** (`RDI`, `RSI`, `RDX`); (2) si chiama la funzione di libreria `read()`; (3) il **numero** della syscall va in `RAX`; (4) l'istruzione **TRAP** (`SYSCALL`) commuta in **modalità kernel**; (5) il kernel identifica la chiamata da `RAX`, valida i parametri ed esegue il gestore; (6) ritorno alla libreria e al programma. La chiamata può **bloccare** il processo (gestione affidata allo scheduler).
## L'astrazione di processo
Un **processo** è l'astrazione di un programma in esecuzione per conto di un utente. È un *contenitore* con tutto il necessario all'esecuzione. Trattazione completa in [[03 - Processi e Thread]]; qui i concetti base.

> [!quote] Definizione — Processo
> Programma in esecuzione, a cui sono associati uno **spazio di indirizzi** (vedi [[06 - Gestione della Memoria]]) e un insieme di **risorse** (registri, file aperti, allarmi, …).

Ogni processo ha un **layout** in memoria (segmenti **Text**, **Data**, **Stack**) che dipende da SO, architettura e programma. I file **persistono** oltre la vita dei processi.

I processi sono registrati in una **tabella dei processi** del SO. Ogni processo può essere **creato**, **terminato**, **sospeso** e **ripreso**, e può creare **processi figli** (formando una gerarchia). Ogni processo appartiene a un **utente** identificato da uno **UID** (i gruppi da un **GID**); su UNIX il figlio eredita lo UID del padre. L'utente **root/superuser** ha permessi speciali.
## File e file system: concetti base
Trattazione completa in [[07 - File System]]; qui le basi necessarie a capire l'interfaccia.

> [!quote] Definizione — File
> Astrazione di un dispositivo di memorizzazione: si leggono/scrivono dati indicando posizione e quantità, senza conoscere i dettagli fisici del disco.

I file sono raccolti in **directory** (a loro volta file). Filosofia UNIX: **"everything is a file"**.

**Gerarchia e percorsi**: la gerarchia parte dalla **directory radice** `/`. Si accede ai file con **percorsi assoluti** (`/home/ast/todo`) o **relativi** alla directory di lavoro (`../slides.pdf`). Altri file system possono essere **montati** (`mount`) nella gerarchia (es. `/mnt/usb`).

> [!example] File system di un dipartimento universitario
> La radice contiene due directory di primo livello: `Students/` (con sottodirectory per studente: `Robbert/`, `Matty/`, `Leo/`) e `Faculty/` (con sottodirectory per docente: `Prof.Brown/`, `Prof.Green/`, `Prof.White/`). A sua volta `Prof.Brown/` contiene `Papers/`, `Grants/`, `Committees/`; `Prof.Green/` contiene `Courses/` (con `CS101/`, `CS105/`). Ogni sottoalbero è indipendente: aggiungere un professore significa creare una nuova directory sotto `Faculty/` senza toccare il resto.
### Diritti di accesso
Ogni file o directory ha **un proprietario** (*owner*) e **un gruppo** (*group*); i permessi si esprimono con **tre tuple da 3 bit** che dicono *cosa può fare* ciascuna categoria di utente. Attenzione: `owner`/`group`/`others` **non** sono parti del file, ma indicano **chi** vi accede:
- **owner**: l'utente che possiede il file/directory;
- **group**: gli utenti che appartengono al suo gruppo;
- **others**: tutti gli altri.

I tre bit sono **r**ead, **w**rite, e**x**ecute, ma il loro significato **cambia tra file e directory**:

| | `r` | `w` | `x` |
|---|---|---|---|
| **File** | leggere il contenuto | modificarne il contenuto | eseguirlo come programma |
| **Directory** | elencarne i nomi (`ls`) | creare/rinominare/eliminare voci | **attraversarla**: entrarci (`cd`) e accedere ai file dentro |

```
-rwxr-x--x  myuser mygroup ...  myfile
```
Owner `rwx` (legge, scrive, esegue), group `r-x` (legge, esegue), others `--x` (solo esegue).
In **notazione ottale** ogni tupla è la somma dei suoi bit — **`r`=4, `w`=2, `x`=1** — quindi `rwx`=7, `rw-`=6, `r-x`=5, `r--`=4. È così che si leggono i numeri di `chmod`: `755`=`rwxr-xr-x`, `644`=`rw-r--r--`.

> [!example] Permessi in pratica — `chmod 744` e `chmod 644`
> `chmod 744 os/hello.sh` → `rwxr--r--`: owner può eseguire, group e others solo leggere.
> `chmod 644 os/` → `rw-r--r--` sulla **directory**: rimuove il bit execute (`x`) dalla directory, rendendo impossibile attraversarla (*traversal*) o accedere ai file al suo interno — anche se i file stessi avessero i permessi giusti. Creare file, listare con `ls` e aprire file nella directory richiedono tutti che `x` sia impostato sulla directory.
> Per una directory funzionante si usa di norma **`755`** (`rwxr-xr-x`): qui `644` è mostrato apposta come esempio di cosa la *rompe* (toglie `x`, cioè l'attraversabilità).
### File speciali e pipe
In UNIX i dispositivi sono astratti come file:
- **Block special files**: dispositivi a blocchi (dischi), es. `/dev/sda2`.
- **Character special files**: dispositivi a caratteri (porte seriali), es. `/dev/ttyS0`.
- Altri: **link simbolici**, **FIFO/pipe**, socket.

I **link** sono un caso particolare: esistono in due varianti distinte.
- **Hard link**: crea una seconda **voce di directory** che punta allo **stesso inode** del file originale — non è una copia, ma un secondo nome per lo stesso dato. Comando: `ln nome1 nome2` (default di `ln`). Limite: non può attraversare file system diversi (l'inode è locale al file system).
- **Symbolic link** (o *soft link*): file speciale che contiene un **percorso** verso il file di destinazione; può attraversare file system e può puntare a directory. Comando: `ln -s nome1 nome2` (`--symbolic` è la forma lunga GNU equivalente). Se il file di destinazione viene eliminato, il symbolic link diventa *dangling* (punta al nulla).

> [!info] `ln` di default crea hard link
> `ln foo.txt bar.txt` crea un hard link: `foo.txt` e `bar.txt` condividono lo stesso inode — `unlink` dell'uno non cancella i dati finché esiste almeno un'altra voce. `ls -F` marca i *symbolic link* (non gli hard link) con `@`; gli hard link non hanno marcatori visibili.

Le **pipe** sono pseudo-file per la comunicazione tra processi su un canale **FIFO**: vanno predisposte in anticipo, appaiono come file normali a chi legge/scrive e permettono comunicazione (tipicamente unidirezionale) tra processi.

> [!example] Domanda tipica d'esame
> - **D:** Differenza tra **hard link** e **symbolic link**. **R:** L'**hard link** è una seconda voce di directory che punta allo **stesso inode** del file (non è una copia): vale solo all'interno dello stesso file system e il dato esiste finché c'è almeno un link (`ln nome1 nome2`). Il **symbolic link** è un file speciale che contiene un **percorso** verso la destinazione: può attraversare file system diversi e puntare a directory, ma diventa *dangling* se la destinazione viene eliminata (`ln -s nome1 nome2`).
## Protezione e shell
La **protezione** è il meccanismo con cui il SO controlla l'accesso a risorse e dati (i bit `rwx`, gli UID/GID, la separazione kernel/user). La **shell** non è il SO ma il suo principale programma di interfaccia: legge comandi e li esegue creando processi.
> [!info] Anticipazione — qui è la prospettiva concettuale (cap. 1)
> Shell, redirezione e permessi sono introdotti qui solo per capire *l'interfaccia* del SO. La trattazione **pratica** di Linux e BASH — comandi, permessi con `chmod`, redirezione e pipe in dettaglio, file descriptor, processi e job control, scripting — è nella nota [[09 - Linux e BASH]].

> [!example] La shell in poche righe
> ```c
> while (TRUE) {
>     type_prompt();                     /* mostra il prompt */
>     read_command(command, parameters); /* legge il comando */
>     if (fork() != 0) {                 /* processo padre */
>         waitpid(-1, &status, 0);       /* attende il figlio */
>     } else {                           /* processo figlio */
>         execve(command, parameters, 0);/* esegue il comando */
>     }
> }
> ```

Ogni processo eredita dalla shell tre **stream standard** (i canali di I/O predefiniti), ciascuno identificato da un **file descriptor** intero — lo stesso tipo di numero restituito da `open()` e usato da `read()`/`write()` (vedi [[#Categorie principali di system call POSIX|system call POSIX]]):
- **stdin** — *standard input*, **fd 0**: da dove il programma **legge** (di default la tastiera);
- **stdout** — *standard output*, **fd 1**: dove scrive l'**output** normale (di default lo schermo);
- **stderr** — *standard error*, **fd 2**: dove scrive i **messaggi d'errore** (di default lo schermo, ma separabile dall'output).

Su questi tre fd la shell costruisce la **redirezione** (`>`, `2>`, `|`): tra `fork` ed `execve` cambia *dove puntano* prima di avviare il programma, in modo trasparente al programma stesso. Il meccanismo completo, con tabelle ed esempi, è in [[09 - Linux e BASH|Redirezione e pipe]].
## Strutture del sistema operativo
Come è organizzato *internamente* il SO. Ogni struttura ha un compromesso fra prestazioni, robustezza e manutenibilità.
### Sistemi monolitici
L'intero SO è **un unico programma** in modalità kernel: un *main* che invoca le procedure di servizio (che eseguono le system call) appoggiate a procedure di utilità.
- **Pro**: molto **efficiente** (chiamate di funzione dirette, nessun overhead interno).
- **Contro**: difficile da mantenere e debuggare; un errore in una parte può **compromettere l'intero sistema**; nessun vero isolamento interno.
- **Modularità parziale**: estensioni caricabili a runtime (driver, file system come moduli) e **librerie condivise** (`.so` in UNIX, **DLL** in Windows).

Esempi: UNIX tradizionale, **Linux**, gran parte di Windows.
### Sistemi a livelli (layered)
Generalizzazione del monolitico: il SO è diviso in **livelli gerarchici**, ognuno costruito su quello sotto. Il sistema **THE** (Dijkstra) ne usava 6 (dall'allocazione del processore in basso ai programmi utente in alto); **MULTICS** usava **anelli concentrici** di privilegio (i livelli interni più privilegiati).
- **Pro**: separazione delle responsabilità, **protezione**, debug livello per livello.
- **Contro**: difficile definire i livelli; overhead negli attraversamenti.
### Microkernel (client-server)
Solo le funzioni **essenziali** restano nel kernel (**microkernel**); i servizi (file system, gestione processi, driver) girano come **processi in user mode** che comunicano tramite **scambio di messaggi**. È il modello **client-server**: un client invia un messaggio al server competente, che risponde.

Nel kernel restano: gestione memoria di basso livello, [[05 - Scheduling|scheduling]], **IPC** e gestione base degli interrupt.
- **Pro**: aderisce al **Principle of Least Authority** (TCB piccolo); **affidabilità** e **sicurezza** (un server che cade non blocca il sistema); portabilità ed estensibilità.
- **Contro**: lo **scambio di messaggi** è più lento di una chiamata di funzione → overhead e prestazioni inferiori al monolitico.

Esempi: **MINIX 3**, Mach, QNX, Symbian.

> [!example] Domanda tipica d'esame
> - **D:** Differenza tra kernel **monolitico** e **microkernel**. **R:** Nel **monolitico** l'intero SO è un unico programma in modalità kernel: le procedure si chiamano direttamente (molto **efficiente**), ma un bug in una parte può compromettere tutto e non c'è isolamento interno. Nel **microkernel** restano nel kernel solo le funzioni essenziali (scheduling, IPC, memoria di basso livello); i servizi (file system, driver) girano come **processi in user mode** che comunicano via **scambio di messaggi** → maggiore **affidabilità** e **sicurezza** (TCB piccolo, *Principle of Least Authority*), ma più lento per l'overhead dei messaggi.
### Macchine virtuali
Una **macchina virtuale (VM)** è la copia virtuale dell'hardware, su cui può girare un intero SO. Idea nata con **VM/370** di IBM (anni '70) per separare la multiprogrammazione dalla macchina estesa; oggi alla base del **cloud**. Il **Virtual Machine Monitor (VMM)** o **hypervisor** emula l'hardware:
- **Type 1 (bare metal)**: l'hypervisor gira **direttamente sull'hardware** (es. VMware ESXi, Xen, Hyper-V).
- **Type 2 (hosted)**: l'hypervisor gira **sopra un SO host** (es. VirtualBox, QEMU); nella pratica usa moduli del kernel per accelerare.
#### Struttura interna di VM/370 con CMS
In VM/370 ogni utente riceve una **Virtual 370** identica all'hardware fisico, su cui gira un SO monoutente chiamato **CMS** (*Conversational Monitor System*). La pila di virtualizzazione è:
```
Virtual 370s  (una per utente)
    CMS       (SO monoutente per ciascuna VM)
    VM/370    (hypervisor)
370 bare hardware
```
Il meccanismo di trap a due livelli funziona così:
- Le **istruzioni di I/O** e le trap generate dal **CMS** vengono intercettate dall'**hypervisor VM/370**, che le gestisce emulando l'hardware e rimandando il controllo al CMS.
- Le **system call** di un'applicazione che gira dentro una VM vengono intercettate dal **CMS** della rispettiva macchina virtuale, che le gestisce come un normale SO monoutente — l'hypervisor non è coinvolto.
Il risultato è che si ottengono **N interfacce di system call indipendenti dal SO**, una per ogni VM: ogni macchina virtuale può potenzialmente eseguire un SO diverso con la propria interfaccia.

> [!info] Container — diversi dalle VM
> I **container** (Docker, LXC, Podman, Kubernetes) condividono il **kernel dell'host** e isolano a livello di **processo**: niente SO completo dentro, quindi leggeri e ad avvio rapido. Limite: non possono eseguire un kernel diverso da quello dell'host e non c'è partizionamento rigido delle risorse come nelle VM.

| Caratteristica       | Virtual Machine (VM)              | Container                             |
| -------------------- | --------------------------------- | ------------------------------------- |
| **Kernel**           | ogni VM ha il proprio kernel      | condividono il kernel dell'host       |
| **Peso**             | pesanti (OS completo)             | leggeri (solo app + dipendenze)       |
| **Avvio**            | lento (minuti)                    | rapido (secondi)                      |
| **Isolamento**       | molto forte                       | più debole (a livello di processo)    |
| **Compatibilità OS** | può eseguire OS diversi           | deve usare lo stesso kernel dell'host |
| **Uso tipico**       | sistemi legacy, ambienti multipli | microservizi, app cloud-native        |

> [!example] Domande tipiche d'esame
> - **D:** Cos'è una macchina virtuale e che differenza c'è tra hypervisor **Type 1** e **Type 2**? **R:** Una VM è la copia virtuale dell'hardware su cui può girare un intero SO isolato; l'hypervisor (VMM) emula l'hardware. **Type 1 (bare metal)**: l'hypervisor gira direttamente sull'hardware (VMware ESXi, Xen, Hyper-V). **Type 2 (hosted)**: gira sopra un SO host (VirtualBox, QEMU).
> - **D:** Differenza tra **VM** e **container**. **R:** La VM include un kernel/OS **completo** (pesante, avvio in minuti, isolamento forte, può eseguire OS diversi dall'host). Il container **condivide il kernel dell'host** e isola a livello di **processo** (leggero, avvio in secondi, ma deve usare lo stesso kernel e ha isolamento più debole).
### Exokernel
Separa il **controllo** delle risorse dalla **macchina estesa**: come un VMM, ma **non emula l'hardware** — fornisce solo una condivisione sicura delle risorse a basso livello, assegnando a ciascuna VM utente solo le risorse che le competono. Elimina l'overhead delle mappature complesse. Uso prevalentemente di ricerca / alte prestazioni. Esempio: **Exokernel (MIT)**.
### Unikernel
Sistemi minimi basati su **LibOS** (Library Operating System): l'applicazione **e** il SO minimo necessario sono compilati in **un singolo binario** che gira su una VM, una sola applicazione per macchina.
- **Pro**: footprint minimo, avvio in millisecondi, superficie d'attacco ridotta, nessun overhead di protezione SO↔app.
- **Contro**: ogni immagine esegue una sola applicazione — **manutenzione difficile** (aggiornare una libreria richiede ricompilare e ridistribuire il binario completo).
- **Uso**: applicazioni cloud specializzate, microservizi, embedded.
- **Esempi**: **MirageOS** (OCaml, web/rete), **IncludeOS** (C++, server web).

---
**Argomento precedente:** [[01 - Introduzione ai Sistemi Operativi]] · **Prossimo:** [[03 - Processi e Thread]] — modello di processo, thread, e implementazione della multiprogrammazione.
