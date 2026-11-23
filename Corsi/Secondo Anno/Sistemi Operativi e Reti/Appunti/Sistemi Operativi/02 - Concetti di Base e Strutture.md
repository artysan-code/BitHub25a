# Concetti di Base e Strutture
Il sistema operativo offre le proprie funzionalità — i **servizi** (es. *File System Service*, *Process Management Service*) — alle applicazioni attraverso le **chiamate di sistema**. Questa nota copre l'interfaccia (system call), le astrazioni fondamentali che il SO espone (processo, file) e le architetture interne con cui può essere costruito. Prerequisito: [[01 - Introduzione ai Sistemi Operativi]].
## System call (chiamate di sistema)
Le **system call** sono l'interfaccia con cui un processo in [[01 - Introduzione ai Sistemi Operativi#Modalità kernel e modalità utente|modalità utente]] richiede un servizio al kernel. Il meccanismo è **specifico** del SO e dell'hardware, perciò viene **incapsulato** in una libreria: in UNIX la **libreria C** (`libc`, basata su POSIX) esporta una procedura per ogni chiamata di sistema *(slide 2025-2026)*. La slide 2026-2027 presenta così il ruolo delle librerie (es. `libc`): forniscono funzioni utilizzabili dai programmi C; alcune invocano direttamente una system call, altre offrono funzionalità di livello più alto, eventualmente con più system call. Esempio: `printf()` è una funzione di libreria che, per scrivere sul terminale, può utilizzare la system call `write()`. **POSIX** definisce interfacce standard che favoriscono la portabilità dei programmi tra sistemi compatibili. La `libc` fornisce anche funzioni di più alto livello (es. `printf`, `fopen`, `malloc`) che internamente possono invocare le system call. Non esiste una sola `libc`: su Linux ci sono ad esempio **glibc**, **musl** e **uclibc**, che implementano tutte lo standard ma con differenze *(slide 2025-2026)*.
### Meccanismo: i passi di una system call
Dal punto di vista del programmatore una system call **sembra** una normale chiamata di funzione (`read(...)`), ma sotto c'è un passaggio in più: la funzione di libreria è solo un **involucro sottile** che prepara i dati ed esegue una **TRAP**, un'istruzione che porta la CPU in [[01 - Introduzione ai Sistemi Operativi#Modalità kernel e modalità utente|modalità kernel]] saltando solo a indirizzi specifici. Il codice utente non può "saltare" nel kernel di sua iniziativa: deve passare per la trap, che entra solo in punti controllati.

> [!info] I tre livelli attraversati
> **Applicazione** → *function call* → **libreria (`libc`)** → *system call / TRAP* → **kernel (SO)** → **hardware** (CPU, memoria, periferiche).
> La libreria fa da ponte: l'applicazione chiama una funzione comoda e portabile (basata su POSIX), la `libc` si occupa dei dettagli — dipendenti dal SO e dall'hardware — per entrare nel kernel. È questo che rende il codice C portabile tra UNIX diversi. *(Schema dei livelli: slide 2025-2026.)*

Esempio: `read(fd, buffer, nbytes)`. Il diagramma del corso (figura di Tanenbaum) scompone la chiamata in **11 passi** (il titolo della slide 2026-2027 dice «I 10 passi», ma la figura ne numera 11; l'11 è l'«istruzione successiva» del programma chiamante); la colonna *modalità* mostra dove avviene ciascuno e dove si attraversa la barriera utente↔kernel:

| # | Cosa succede | Modalità |
|---|---|---|
| 1–3 | Il chiamante colloca i parametri `fd`, `&buffer`, `nbytes` nei **registri** (`RDI`, `RSI`, `RDX`) o sullo **stack** se sono troppi | utente |
| 4 | Chiama la procedura di libreria `read()` della `libc` (ancora una normale chiamata di funzione) | utente |
| 5 | La `libc` mette il **numero** della system call in `RAX` — l'indice che identifica *quale* gestore del kernel eseguire | utente |
| 6 | Esegue l'istruzione **TRAP** (`SYSCALL` su x86-64): commuta in modalità kernel; è come una call ma *cambia modalità* e può saltare solo a indirizzi controllati | utente → kernel |
| 7 | **Dispatch**: il kernel usa il numero in `RAX` per indicizzare la **tabella delle system call** e trovare il gestore corrispondente | kernel |
| 8 | Esegue il **gestore** (nella figura: «Gestore della chiamata di sistema») che svolge il servizio (qui: legge dal file descriptor); la validazione dei parametri è *(extra, non da slide)* | kernel |
| 9 | Il controllo torna alla procedura di libreria, all'istruzione **successiva alla TRAP** | kernel → utente |
| 10 | La libreria **ritorna** al programma, che prosegue come dopo una normale chiamata | utente |
| 11 | Il programma prosegue con l'**istruzione successiva** alla chiamata (figura); l'eventuale pulizia dello stack (incremento dello Stack Pointer) è *(extra, non da slide)* | utente |

> [!warning] La chiamata può bloccare
> Se il dato richiesto non è disponibile, la system call **blocca** il processo: il SO ne esegue altri e riprende il chiamato quando la condizione è soddisfatta. Lo stato di blocco è gestito dallo [[05 - Scheduling|scheduler]].

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> L'istruzione TRAP, il cambio di modalità e la gestione di interrupt sono il punto di contatto con l'hardware: vedi il livello ISA in [[05 - Livello di architettura dell'insieme d'istruzioni]].

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
> - vale `-1` se la creazione fallisce (nessun figlio creato; causa leggibile da `errno`). *(extra, non da slide: `errno`)*
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
> Quindi `pid` non è "il proprio identificatore", ma il modo per sapere **in quale dei due processi mi trovo**. Per il PID vero ci sono `getpid()` (il proprio) e `getppid()` (quello del padre). *(extra, non da slide)* Il flusso completo padre-figlio è in [[03 - Processi e Thread]] e, lato programmazione C, in [[10 - Programmazione C e Concorrente]].

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

Convenzioni dei valori di ritorno: `pid` = id processo, `fd` = file descriptor, `n` = numero di byte, `s` = esito. Quasi tutte le call ritornano **-1 in caso di errore** — impostando la variabile globale `errno`, che `perror()` traduce in un messaggio leggibile *(extra, non da slide: `errno` e `perror`)* — e `0` o un valore utile in caso di successo (`open` → un `fd ≥ 0`; `read` → byte letti, `0` a fine file; `lseek` → la nuova posizione) *(extra, non da slide: i valori di ritorno `open`, `read`, `lseek` e le eccezioni di `execve` ed `exit`)*. Vanno ricordate tre **eccezioni**:
- `fork()` ritorna **due volte** (riquadro sopra);
- `execve()` **non ritorna** se ha successo — l'immagine del processo è stata sostituita — e dà `-1` solo su errore (mnemonico: *se `execve` ritorna, è andata male*);
- `exit()` **non ritorna mai**, perché termina il processo (lo `status` lo raccoglie il padre con `waitpid`; il fatto che sia un valore 0–255 è *(extra, non da slide)*).
### API Win32 di Windows
Windows offre API equivalenti (non identiche) alle system call UNIX. La slide 2026-2027 riporta solo sei corrispondenze indicative (creazione processo `fork()`+`execve()` ↔ `CreateProcess()`, apertura `open()` ↔ `CreateFile()`, lettura `read()` ↔ `ReadFile()`, scrittura `write()` ↔ `WriteFile()`, chiusura `close()` ↔ `CloseHandle()`, attesa `waitpid()` ↔ `WaitForSingleObject()`) e precisa che le funzioni non sono necessariamente equivalenti nel comportamento. La tabella completa qui sotto è della slide 2025-2026:

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
| `chmod`          | (nessuna)                           | Win32 non supporta la sicurezza (anche se NT sì, slide 2025-2026); le ACL di NT e l'assenza dei permessi POSIX sono *(extra, non da slide)* |
| `kill`           | (nessuna)                           | Win32 non supporta i segnali                            |
| `time`           | `GetLocalTime`                      | Ora locale di sistema                                   |
### Costo delle system call
Una system call è **costosa**: comporta il passaggio da user space a kernel space (slide 2025-2026); ad essa si aggiungono salvataggio/ripristino dei registri, validazione dei parametri ed eventuale blocco del chiamante *(extra, non da slide)*. Per questo si tende a minimizzarne il numero: la slide 2025-2026 indica come problema che le system call sono **costose** (passaggio da user space a kernel space); la slide 2026-2027 non lo riporta. Ad esempio la `libc` **bufferizza** le scritture e le svuota in blocco, sostituendo molte `write()` con una sola e riducendo i cambi di contesto *(extra, non da slide)*.

> [!question] Domande tipiche d'esame
> - **D:** Cosa sono le system call e perché vengono incapsulate in una libreria? **R:** Sono il meccanismo con cui un processo in **modalità utente** richiede un servizio al kernel. Il meccanismo è specifico del SO e dell'hardware, quindi viene **incapsulato** nella libreria C (`libc`, basata su POSIX), che esporta una funzione per ogni system call → **portabilità** del codice.
> - **D:** Descrivi i passi di una system call (es. `read`). **R:** (1) i parametri vanno nei **registri** (`RDI`, `RSI`, `RDX`); (2) si chiama la funzione di libreria `read()`; (3) il **numero** della syscall va in `RAX`; (4) l'istruzione **TRAP** (`SYSCALL`) commuta in **modalità kernel**; (5) il kernel identifica la chiamata da `RAX`, esegue il gestore (validando i parametri *(extra, non da slide)*); (6) ritorno alla libreria e al programma. La chiamata può **bloccare** il processo (gestione affidata allo scheduler).

> [!info] Mettiti alla prova
> - **C — processi** (`fork`/`waitpid`/`execve`/`exit`): [[Indice degli Esercizi#Processi|fork_pari_dispari_soglia.c]] e [[Indice degli Esercizi#Processi|26_01_24_appello.c]] · tracce [[Tracce d'Esame Pratiche#Processi|P2]], [[Tracce d'Esame Pratiche#Processi|P6]], [[Tracce d'Esame Pratiche#Processi|P10]].
> - **C — file** (`open`/`read`/`lseek`/`stat`): [[Indice degli Esercizi#Processi|fork_seek_occurrences.c]] · tracce [[Tracce d'Esame Pratiche#Processi|P1]], [[Tracce d'Esame Pratiche#Processi|P9]].
## L'astrazione di processo
Un **processo** è l'astrazione di un programma in esecuzione per conto di un utente. È un *contenitore* con tutto il necessario all'esecuzione. Trattazione completa in [[03 - Processi e Thread]]; qui i concetti base.

> [!quote] Definizione — Processo
> Programma in esecuzione, a cui sono associati uno **spazio di indirizzi** (vedi [[06 - Gestione della Memoria]]) e un insieme di **risorse** (registri, file aperti, allarmi, …).

Ogni processo ha un **layout** in memoria (segmenti **Text**, **Data**, **Stack**) che dipende da SO, architettura e programma. I file **persistono** oltre la vita dei processi.

I processi sono registrati in una **tabella dei processi** del SO. Ogni processo può essere **creato**, **terminato**, **sospeso** e **ripreso**, e può creare **processi figli** (formando una gerarchia). Ogni processo appartiene a un **utente** identificato da uno **UID** (i gruppi da un **GID**; la slide 2025-2026 scriveva «GUID», la slide 2026-2027 scrive «GID»). Nella slide 2026-2027 ogni processo è associato a un utente e a uno o più gruppi; UID e GID contribuiscono a determinare quali risorse il processo può utilizzare; su UNIX il figlio eredita normalmente le credenziali del padre (nella slide 2025-2026: eredita lo UID del padre). L'utente **root/superuser** ha permessi speciali: nella slide 2026-2027 root ha UID 0 e dispone di privilegi amministrativi, per cui i suoi processi possono compiere operazioni normalmente non consentite agli altri utenti.
## File e file system: concetti base
Trattazione completa in [[07 - File System]]; qui le basi necessarie a capire l'interfaccia.

> [!quote] Definizione — File
> Astrazione di un dispositivo di memorizzazione: si leggono/scrivono dati indicando posizione e quantità, senza conoscere i dettagli fisici del disco.

I file sono raccolti in **directory** (a loro volta file). Filosofia UNIX: **"everything is a file"** — o, più precisamente a livello di interfaccia, *"everything is a file descriptor"*, dato che file, pipe e dispositivi si manipolano tutti con le stesse system call (`read`/`write`/`close`).

**Gerarchia e percorsi**: la gerarchia parte dalla **directory radice** `/`. Si accede ai file con **percorsi assoluti** (`/home/ast/todo`) o **relativi** alla directory di lavoro (`../slides.pdf`). Altri file system possono essere **montati** (`mount`) nella gerarchia (es. `/mnt/usb`).

> [!example] File system di un dipartimento universitario
> La radice contiene due directory di primo livello: `Students/` (con sottodirectory per studente: `Robbert/`, `Matty/`, `Leo/`) e `Faculty/` (con sottodirectory per docente: `Prof.Brown/`, `Prof.Green/`, `Prof.White/`). Nella figura `Prof.Brown/` contiene `Courses/` (con `CS101/`, `CS105/`), `Papers/`, `Grants/` e `Committees/` (con `SOSP/`, `COST-11/`); `Prof.Green/` e `Prof.White/` contengono file. Ogni sottoalbero è indipendente: aggiungere un professore significa creare una nuova directory sotto `Faculty/` senza toccare il resto.
### Diritti di accesso
Ogni file o directory ha **un proprietario** (*owner*) e **un gruppo** (*group*); i permessi si esprimono con **tre tuple da 3 bit** che dicono *cosa può fare* ciascuna categoria di utente. Attenzione: `owner`/`group`/`others` **non** sono parti del file, ma indicano **chi** vi accede:
- **owner**: l'utente che possiede il file/directory;
- **group**: gli utenti che appartengono al suo gruppo;
- **others**: tutti gli altri.

I tre bit sono **r**ead, **w**rite, e**x**ecute, ma il loro significato **cambia tra file e directory** *(extra, non da slide)*:

| | `r` | `w` | `x` |
|---|---|---|---|
| **File** | leggere il contenuto | modificarne il contenuto | eseguirlo come programma |
| **Directory** | elencarne i nomi (`ls`) | creare/rinominare/eliminare voci | **attraversarla**: entrarci (`cd`) e accedere ai file dentro |

```
-rwxr-x--x  myuser mygroup ...  myfile
```
Owner `rwx` (legge, scrive, esegue), group `r-x` (legge, esegue), others `--x` (solo esegue).
In **notazione ottale** ogni tupla è la somma dei suoi bit — **`r`=4, `w`=2, `x`=1** — quindi `rwx`=7, `rw-`=6, `r-x`=5, `r--`=4. La mappatura numerica di `chmod` (es. `chmod 660`) è nella slide `SOR2025-2026_3.1_Introduction-to-Linux-and-BASH.pdf`, non nella slide 3; gli esempi `755`=`rwxr-xr-x` e `644`=`rw-r--r--` sono *(extra, non da slide)*.

> [!example] Permessi in pratica — `chmod 744` e `chmod 644` *(extra, non da slide)*
> `chmod 744 os/hello.sh` → `rwxr--r--`: owner può eseguire, group e others solo leggere.
> `chmod 644 os/` → `rw-r--r--` sulla **directory**: rimuove il bit execute (`x`) dalla directory, rendendo impossibile attraversarla (*traversal*) o accedere ai file al suo interno — anche se i file stessi avessero i permessi giusti. Creare file, listare con `ls` e aprire file nella directory richiedono tutti che `x` sia impostato sulla directory.
> Per una directory funzionante si usa di norma **`755`** (`rwxr-xr-x`): qui `644` è mostrato apposta come esempio di cosa la *rompe* (toglie `x`, cioè l'attraversabilità).

> [!info] Mettiti alla prova
> - **Comando:** crea un file di test e prova `chmod`, `ls -l`, `stat` nel terminale, verificando i bit `rwx` ↔ notazione ottale (`755`, `644`).
> - **Teorico:** permessi e comandi sono svolti in [[09 - Linux e BASH (Esercizi)]] e approfonditi in [[09 - Linux e BASH]].
### File speciali e pipe
In UNIX i dispositivi sono astratti come file:
- **Block special files**: dispositivi a blocchi (dischi), es. `/dev/sda2`.
- **Character special files**: dispositivi a caratteri (porte seriali), es. `/dev/ttyS0`.
- Altri: **link simbolici**, **FIFO/pipe**, socket.

I **link** sono un caso particolare: esistono in due varianti distinte.
- **Hard link** *(extra, non da slide)*: crea una seconda **voce di directory** che punta allo **stesso inode** del file originale — non è una copia, ma un secondo nome per lo stesso dato. Comando: `ln nome1 nome2` (default di `ln`). Limite: non può attraversare file system diversi (l'inode è locale al file system).
- **Symbolic link** (o *soft link*): file speciale che contiene un **percorso** verso il file di destinazione; può attraversare file system e può puntare a directory. Comando: `ln -s nome1 nome2` (`--symbolic` è la forma lunga GNU equivalente). Se il file di destinazione viene eliminato, il symbolic link diventa *dangling* (punta al nulla) *(extra, non da slide)*. Nella slide 3 compaiono solo i *symbolic links* tra i file speciali e la system call `link`; `ln -s` è nella slide 3.1.

> [!info] `ln` di default crea hard link *(extra, non da slide)*
> `ln foo.txt bar.txt` crea un hard link: `foo.txt` e `bar.txt` condividono lo stesso inode — `unlink` dell'uno non cancella i dati finché esiste almeno un'altra voce. `ls -F` marca i *symbolic link* (non gli hard link) con `@`; gli hard link non hanno marcatori visibili.

Una **pipe** è un canale di comunicazione **FIFO**: un processo scrive dati e un altro li legge; il sistema operativo permette di crearla e utilizzarla per la comunicazione tra processi (slide 2026-2027). Le pipe sono pseudo-file per la comunicazione tra processi su un canale FIFO: vanno predisposte in anticipo *(slide 2025-2026)*, appaiono come file normali a chi legge/scrive e permettono comunicazione (tipicamente unidirezionale) tra processi.

> [!question] Domanda tipica d'esame *(extra, non da slide)*
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

Su questi tre fd la shell costruisce la **redirezione** (`>`, `2>`, `|`): tra `fork` ed `execve` cambia *dove puntano* prima di avviare il programma, in modo trasparente al programma stesso. Il meccanismo completo, con tabelle ed esempi, è in [[09 - Linux e BASH#Redirezione e pipe|Redirezione e pipe]].
## Strutture del sistema operativo
Come è organizzato *internamente* il SO. Ogni struttura ha un compromesso fra prestazioni, robustezza e manutenibilità. La slide 2026-2027 introduce exokernel, unikernel e microkernel con la domanda «dove conviene implementare le funzionalità del sistema operativo?»: la scelta comporta compromessi tra prestazioni, isolamento, flessibilità e complessità.
### Sistemi monolitici
L'intero SO è **un unico programma** in modalità kernel: un *main* che invoca le procedure di servizio (che eseguono le system call) appoggiate a procedure di utilità.
- **Flessibilità vs complessità** (slide): offre una certa flessibilità in termini di prestazioni e design; tuttavia, poiché tutto è strettamente interconnesso, un bug in una parte può causare problemi in altre parti, fino a **crash sistemici**.
- **Pro**: molto **efficiente** (chiamate di funzione dirette, nessun overhead interno) *(extra, non da slide)*.
- **Contro**: difficile da mantenere e debuggare *(extra, non da slide)*; un errore in una parte può **compromettere l'intero sistema**; nessun vero isolamento interno (slide).
- **Un solo spazio di indirizzamento**: tutte le funzioni (processi, memoria, I/O) sono strettamente integrate e devono essere compilate e collegate in **un unico eseguibile del kernel**; un bug in una parte può causare crash sistemici.
- **Mancanza di occultamento delle informazioni**: in teoria ogni procedura può accedere a qualsiasi altra procedura o variabile del kernel; non c'è un vero isolamento tra le parti.
- **Struttura a tre strati**: user mode, kernel mode e hardware, con la **trap** (interruzione software che trasferisce il controllo al SO) come meccanismo di comunicazione tra i livelli.
- **Modularità parziale**: estensioni caricabili a runtime (driver, file system come moduli) e **librerie condivise** (`.so` in UNIX, **DLL** in Windows).

Esempi: UNIX tradizionale, **Linux**, gran parte di Windows *(extra, non da slide)*.
### Sistemi a livelli (layered)
Idea (slide 2026-2027): organizzare il SO in **livelli** con responsabilità ben definite; ogni livello offre servizi ai livelli superiori e utilizza le funzionalità dei livelli inferiori; le interfacce tra livelli aiutano a separare le responsabilità. Generalizzazione del monolitico, con livelli gerarchici ognuno costruito su quello sotto *(slide 2025-2026)*. La figura della slide mostra anelli concentrici (kernel, system calls, shared libraries, user programs; livelli 0–3). Esempi storici: **THE**, uno dei primi SO progettati con struttura a livelli; **MULTICS**, che usa **anelli di protezione** per distinguere livelli di privilegio (i livelli interni più privilegiati). La slide 2025-2026 attribuiva a THE **6** livelli (allocazione del processore, memoria, comunicazione, I/O, dispositivi, utenti); la slide 2026-2027 non li elenca. Il dettaglio qui sotto, dal più basso al più alto, non è nelle slide *(extra, non da slide)*: **(0)** allocazione del processore e multiprogrammazione, **(1)** gestione della memoria, **(2)** comunicazione operatore-processo, **(3)** gestione dell'I/O, **(4)** programmi utente, **(5)** l'operatore (Dijkstra, 1968).
- **Pro**: maggiore **modularità**, sviluppo e manutenzione più facili, migliore controllo delle dipendenze tra componenti (slide 2026-2027); separazione delle responsabilità, **protezione** delle risorse e dei dati critici *(slide 2025-2026)*; debug livello per livello *(extra, non da slide)*.
- **Contro**: non è sempre semplice stabilire una suddivisione rigida in livelli (slide 2026-2027); overhead negli attraversamenti *(extra, non da slide)*.
### Microkernel (client-server)
Solo le funzioni **essenziali** restano nel kernel (**microkernel**); i servizi (file system, gestione processi, driver) girano come **processi in user mode** che comunicano tramite **scambio di messaggi**. È il modello **client-server** *(slide 2025-2026)*: un client invia un messaggio al server competente, che risponde *(extra, non da slide: la descrizione dello scambio)*.

Nel microkernel restano (slide 2026-2027): gestione delle interruzioni e delle operazioni privilegiate, meccanismi fondamentali di [[05 - Scheduling|scheduling]] e di gestione della memoria, comunicazione tra processi (**IPC**, *Inter-Process Communication*). Fuori dal microkernel: file system, numerosi driver e altri servizi del SO, eseguiti come processi separati. Differenza rispetto al monolitico: molti servizi non condividono lo stesso spazio di indirizzamento privilegiato. In **MINIX** (figura) programmi utente (es. Shell, Make), server (es. FS) e driver (es. Disk, TTY) sono processi in modalità utente distinti; il microkernel gestisce interrupt, processi, scheduling e comunicazione tra processi.
- **Pro**: aderisce al **Principle of Least Authority** (POLA: ogni componente ha solo i privilegi che gli servono, così la **Trusted Computing Base** — TCB, l'insieme di codice di cui ci si deve necessariamente fidare *(extra, non da slide)* — resta ridotta: un kernel più piccolo può essere più facile da analizzare e verificare); **isolamento** (un errore in un driver può essere contenuto senza compromettere necessariamente l'intero sistema; nella slide 2025-2026: un server che cade non blocca il sistema), **sicurezza** e **manutenibilità** (servizi e driver sviluppati e aggiornati in modo più indipendente); portabilità ed estensibilità *(extra, non da slide)*.
- **Contro**: lo **scambio di messaggi** e i cambi di contesto introducono **overhead** rispetto alle chiamate dirette tra componenti del kernel → prestazioni inferiori al monolitico. Compromesso (slide 2026-2027): maggiore isolamento e modularità a fronte di una possibile perdita di prestazioni.

Esempi: **MINIX 3**; **QNX** *(slide 2025-2026)*; Mach, Symbian *(extra, non da slide)*.

> [!question] Domanda tipica d'esame
> - **D:** Differenza tra kernel **monolitico** e **microkernel**. **R:** Nel **monolitico** l'intero SO è un unico programma in modalità kernel: le procedure si chiamano direttamente (molto **efficiente**), ma un bug in una parte può compromettere tutto e non c'è isolamento interno. Nel **microkernel** restano nel kernel solo le funzioni essenziali (scheduling, IPC, memoria di basso livello); i servizi (file system, driver) girano come **processi in user mode** che comunicano via **scambio di messaggi** → maggiore **affidabilità** e **sicurezza** (TCB piccolo, *Principle of Least Authority*), ma più lento per l'overhead dei messaggi.
### Macchine virtuali
Una **macchina virtuale (VM)** è la copia virtuale dell'hardware, su cui può girare un intero SO. Idea nata con **VM/370** di IBM (anni '70) per separare la multiprogrammazione dalla macchina estesa; oggi di nuovo di interesse in diversi ambiti (slide); alla base del **cloud** *(extra, non da slide)*. Il **Virtual Machine Monitor (VMM)** o **hypervisor** emula l'hardware.

Vantaggi delle VM (slide):
- **Isolamento**: ogni VM opera indipendentemente;
- **Flessibilità**: si possono eseguire più sistemi operativi simultaneamente (es. OS/360, CMS);
- **Gestione semplificata**: si facilita la gestione e la manutenzione separando multiprogrammazione e risorse hardware.

Uso moderno: il successore **z/VM** gira sui mainframe IBM serie Z e fa girare più sistemi operativi completi, come Linux, in ambienti ad alta intensità di transazioni e dati.

Tipi di hypervisor:
- **Type 1 (bare metal)**: l'hypervisor gira **direttamente sull'hardware** (es. Xen; VMware ESXi, Hyper-V *(extra, non da slide)*).
- **Type 2 (hosted)**: l'hypervisor gira **sopra un SO host** (es. QEMU; VirtualBox *(extra, non da slide)*); in teoria non c'è specializzazione del SO sottostante (fig. b della slide), nella pratica usa moduli del kernel per accelerare la simulazione (fig. c).
#### Struttura interna di VM/370 con CMS
In VM/370 ogni utente riceve una **Virtual 370** identica all'hardware fisico, su cui gira un SO chiamato **CMS** (*Conversational Monitor System*); che sia **monoutente** è *(extra, non da slide)*. La pila di virtualizzazione è:
```
Virtual 370s  (una per utente)
    CMS       (SO monoutente per ciascuna VM)
    VM/370    (hypervisor)
370 bare hardware
```
Il meccanismo di trap a due livelli funziona così:
- Le **istruzioni di I/O** e le trap generate dal **CMS** vengono intercettate dall'**hypervisor VM/370**, che le gestisce emulando l'hardware e rimandando il controllo al CMS.
- Le **system call** di un'applicazione che gira dentro una VM vengono intercettate dal **CMS** della rispettiva macchina virtuale, che le gestisce come un normale SO monoutente — l'hypervisor non è coinvolto *(extra, non da slide: la figura indica solo dove avvengono le trap)*.
Il risultato è che si ottengono **N interfacce di system call indipendenti dal SO**, una per ogni VM: ogni macchina virtuale può potenzialmente eseguire un SO diverso con la propria interfaccia.

> [!info] Container — diversi dalle VM
> Premessa (slide 2026-2027): ogni VM esegue un SO *guest* con un proprio kernel, consente isolamento e l'esecuzione di SO differenti, ma richiede risorse per il SO guest; le esigenze moderne sono distribuire rapidamente applicazioni e servizi, ridurre il consumo di risorse, riprodurre facilmente gli ambienti software e gestire molte istanze di un'applicazione. I **container** (**Docker** per la gestione dei container, **Kubernetes** per la loro orchestrazione; LXC, Podman *(extra, non da slide)*) condividono il **kernel dell'host** e isolano a livello di **processo**: niente SO completo dentro, quindi leggeri e ad avvio generalmente rapido. Idea chiave (slide 2026-2027): le VM isolano interi ambienti di sistema, i container isolano principalmente applicazioni e processi. Ogni container può avere filesystem, librerie e configurazioni proprie; l'isolamento si basa su funzionalità del kernel come **namespace** e **cgroups** in Linux; più container possono girare sullo stesso host; sono facili da distribuire e riprodurre. Limite: non possono eseguire un kernel diverso da quello dell'host e non c'è partizionamento rigido delle risorse come nelle VM *(extra, non da slide)*. Se il **kernel viene compromesso**, **tutti i container** sono a rischio *(slide 2025-2026; nella slide 2026-2027: l'isolamento dipende anche dalla sicurezza e dalla configurazione del kernel host)*.

| Caratteristica       | Virtual Machine (VM)              | Container                             |
| -------------------- | --------------------------------- | ------------------------------------- |
| **Kernel**           | ogni VM ha il proprio kernel      | condividono il kernel dell'host       |
| **Peso**             | pesanti (OS completo)             | leggeri (solo app + dipendenze)       |
| **Avvio**            | generalmente più lento *(slide 2025-2026: minuti)* | generalmente più veloce *(slide 2025-2026: secondi)* |
| **Isolamento**       | molto forte                       | più debole (a livello di processo)    |
| **Compatibilità OS** | può eseguire OS diversi           | deve usare lo stesso kernel dell'host |
| **Uso tipico**       | sistemi legacy, ambienti multipli | microservizi, app cloud-native        |

> [!question] Domande tipiche d'esame
> - **D:** Cos'è una macchina virtuale e che differenza c'è tra hypervisor **Type 1** e **Type 2**? **R:** Una VM è la copia virtuale dell'hardware su cui può girare un intero SO isolato; l'hypervisor (VMM) emula l'hardware. **Type 1 (bare metal)**: l'hypervisor gira direttamente sull'hardware (Xen; VMware ESXi, Hyper-V *(extra, non da slide)*). **Type 2 (hosted)**: gira sopra un SO host (QEMU; VirtualBox *(extra, non da slide)*).
> - **D:** Differenza tra **VM** e **container**. **R:** La VM include un kernel/OS **completo** (pesante, avvio generalmente più lento, isolamento forte, può eseguire OS diversi dall'host). Il container **condivide il kernel dell'host** e isola a livello di **processo** (leggero, avvio generalmente più rapido, ma deve usare lo stesso kernel e ha isolamento più debole).
### Exokernel
Idea (slide 2026-2027): ridurre al minimo le funzioni del kernel, separando la **protezione** delle risorse dalla loro gestione. L'exokernel assegna e protegge risorse hardware (CPU, memoria, disco) e non impone astrazioni di alto livello (es. un particolare modello di file system); le applicazioni usano **Library OS (LibOS)** a livello utente per costruire le astrazioni di cui hanno bisogno. Vantaggio: maggiore flessibilità e controllo sulle risorse. Limite: maggiore complessità per applicazioni e librerie di sistema. Differenza rispetto a un hypervisor: espone risorse hardware protette invece di presentare macchine virtuali complete.

*(Slide 2025-2026)* Separa il **controllo** delle risorse dalla **macchina estesa**: come un VMM, ma **non emula l'hardware** — fornisce solo una condivisione sicura delle risorse a basso livello, assegnando a ciascuna VM utente solo le risorse che le competono. Elimina l'overhead delle mappature complesse. Uso prevalentemente di ricerca / alte prestazioni *(extra, non da slide)*. Esempio: **Exokernel (MIT)**.
### Unikernel
Idea (slide 2026-2027): integrare un'applicazione e le funzionalità del SO necessarie per eseguirla in **un'unica immagine**. Si parte dall'applicazione (es. un web server) e si includono solo i componenti di sistema necessari (rete, memoria, driver, ecc.); applicazione e componenti del SO operano tipicamente nello **stesso spazio di indirizzamento**; l'immagine risultante può essere eseguita direttamente su un hypervisor. Nella slide 2025-2026: sistemi minimi basati su **LibOS** (Library Operating System), una sola applicazione per macchina virtuale.
- **Pro**: dimensioni ridotte, avvio rapido, superficie d'attacco ridotta (slide 2026-2027); nessun overhead di protezione SO↔app, perché esiste una sola applicazione per VM *(slide 2025-2026)*; avvio in millisecondi *(extra, non da slide)*.
- **Contro**: minore flessibilità e maggiore complessità nella gestione e nel debugging (slide 2026-2027); ogni immagine esegue una sola applicazione — **manutenzione difficile** *(slide 2025-2026)* (aggiornare una libreria richiede ricompilare e ridistribuire il binario completo *(extra, non da slide)*).
- **Uso**: applicazioni cloud specializzate, microservizi, embedded *(extra, non da slide)*.
- **Esempi**: **MirageOS**, **IncludeOS** (slide); i linguaggi (OCaml, C++) e gli usi (web/rete, server web) sono *(extra, non da slide)*.

**Confronto finale (slide 2026-2027)**: non esiste un'architettura migliore in assoluto; la scelta dipende da prestazioni, protezione, flessibilità e manutenzione.

| | Exokernel | Unikernel | Microkernel |
|---|---|---|---|
| **Idea** | Proteggere e assegnare risorse | Integrare app e SO | Separare kernel e servizi |
| **Organizzazione** | Kernel minimo + LibOS | Immagine specializzata | Kernel minimo + server |
| **Punto di forza** | Flessibilità | Leggerezza | Isolamento |
| **Compromesso** | Complessità delle LibOS | Scarsa generalità | Overhead IPC |
| **Esempio** | MIT Exokernel | MirageOS | MINIX 3 |

> [!question] Domanda tipica d'esame
> - **D:** Confronta exokernel, unikernel e microkernel. **R:** **Exokernel**: il kernel assegna e protegge le risorse hardware e le applicazioni costruiscono le astrazioni con librerie a livello utente (LibOS); punto di forza flessibilità, compromesso complessità delle LibOS. **Unikernel**: applicazione e componenti di sistema necessari in un'unica immagine specializzata, eseguibile su un hypervisor; punto di forza leggerezza, compromesso scarsa generalità. **Microkernel**: kernel minimo, servizi (file system, driver) come processi separati che comunicano via messaggi; punto di forza isolamento, compromesso overhead IPC. Non esiste un'architettura migliore in assoluto: dipende da prestazioni, protezione, flessibilità e manutenzione.

---
**Argomento precedente:** [[01 - Introduzione ai Sistemi Operativi]] · **Prossimo:** [[03 - Processi e Thread]] — modello di processo, thread, e implementazione della multiprogrammazione.
