# 02 - Concetti di Base e Strutture
Il sistema operativo offre le proprie funzionalità — i **servizi** (es. *File System Service*, *Process Management Service*) — alle applicazioni attraverso le **chiamate di sistema**. Questa nota copre l'interfaccia (system call), le astrazioni fondamentali che il SO espone (processo, file) e le architetture interne con cui può essere costruito. Prerequisito: [[01 - Introduzione ai Sistemi Operativi]].
## System call (chiamate di sistema)
Le **system call** sono l'interfaccia con cui un processo in [[01 - Introduzione ai Sistemi Operativi#Modalità kernel e modalità utente|modalità utente]] richiede un servizio al kernel. Il meccanismo è **specifico** del SO e dell'hardware, perciò viene **incapsulato** in una libreria: in UNIX la **libreria C** (`libc`, basata su POSIX) esporta una procedura per ogni chiamata di sistema.
### Meccanismo: i passi di una system call
Esempio: `read(fd, buffer, nbytes)`.
1. **Preparazione parametri** (user space): il chiamante mette i parametri nei **registri** (`RDI`, `RSI`, `RDX`) o sullo stack.
2. **Chiamata alla procedura di libreria** `read()` della `libc`.
3. La libreria mette il **numero della system call** in un registro (`RAX`) — indice nella *tabella delle system call* del kernel.
4. **Istruzione TRAP** (`SYSCALL` su x86-64): commuta in **modalità kernel**. È simile a una chiamata di procedura ma *cambia modalità* e può saltare solo a indirizzi controllati.
5. Il kernel identifica la chiamata da `RAX`, **valida i parametri** ed esegue il gestore (es. legge dal file descriptor).
6. **Ritorno** alla procedura di libreria e quindi al programma, all'istruzione successiva alla TRAP.

> [!warning] La chiamata può bloccare
> Se il dato richiesto non è disponibile, la system call **blocca** il processo: il SO ne esegue altri e riprende il chiamato quando la condizione è soddisfatta. Lo stato di blocco è gestito dallo [[05 - Scheduling|scheduler]].

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> L'istruzione TRAP, il cambio di modalità e la gestione di interrupt sono il punto di contatto con l'hardware: vedi il livello ISA in [[5 - Livello di architettura dell'insieme d'istruzioni]].
### Categorie principali di system call POSIX
**Gestione dei processi** (vedi [[03 - Processi e Thread]]):

| Call | Descrizione |
|------|-------------|
| `pid = fork()` | Crea un processo figlio identico al genitore |
| `pid = waitpid(pid, &statloc, options)` | Attende la terminazione di un figlio |
| `s = execve(name, argv, environp)` | Sostituisce l'immagine del processo |
| `exit(status)` | Termina il processo e restituisce lo stato |

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

Convenzioni: `s = -1` indica errore; `pid` = id processo; `fd` = file descriptor; `n` = numero di byte.
### API Win32 di Windows
Windows offre API equivalenti (non identiche) alle system call UNIX:

| UNIX | Win32 | Note |
|------|-------|------|
| `fork` | `CreateProcess` | `CreateProcess` = `fork` + `execve` |
| `waitpid` | `WaitForSingleObject` | Attende un processo |
| `open`/`close` | `CreateFile`/`CloseHandle` | |
| `read`/`write` | `ReadFile`/`WriteFile` | |
| `lseek` | `SetFilePointer` | |
| `mkdir`/`rmdir` | `CreateDirectory`/`RemoveDirectory` | |
| `link` | (nessuna) | Win32 non supporta i link |
| `mount` | (nessuna) | Win32 non supporta `mount` |
| `kill` | (nessuna) | Win32 non supporta i segnali |
### Costo delle system call
Una system call è **costosa**: richiede un cambio di contesto user↔kernel, salvataggio/ripristino dei registri, validazione dei parametri ed eventuale blocco del chiamante. Per questo si tende a minimizzarne il numero (es. I/O bufferizzato).
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
### Diritti di accesso
I file sono protetti da **tuple di 3 bit** per **owner**, **group** e **others**: **r**ead, **w**rite, e**x**ecute.

```
-rwxr-x--x  myuser mygroup ...  myfile
```
Owner `rwx` (legge, scrive, esegue), group `r-x` (legge, esegue), others `--x` (solo esegue).
### File speciali e pipe
In UNIX i dispositivi sono astratti come file:
- **Block special files**: dispositivi a blocchi (dischi), es. `/dev/sda2`.
- **Character special files**: dispositivi a caratteri (porte seriali), es. `/dev/ttyS0`.
- Altri: **link simbolici**, **FIFO/pipe**, socket.

Le **pipe** sono pseudo-file per la comunicazione tra processi su un canale **FIFO**: vanno predisposte in anticipo, appaiono come file normali a chi legge/scrive e permettono comunicazione (tipicamente unidirezionale) tra processi.
## Protezione e shell
La **protezione** è il meccanismo con cui il SO controlla l'accesso a risorse e dati (i bit `rwx`, gli UID/GID, la separazione kernel/user). La **shell** non è il SO ma il suo principale programma di interfaccia: legge comandi e li esegue creando processi.

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

> [!info] Approfondimento — Linux e BASH
> L'uso pratico della shell, i comandi e lo scripting BASH sono nelle slide 3.1 del corso e nel codice di `Materiale Didattico/.../code/`.
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
### Macchine virtuali
Una **macchina virtuale (VM)** è la copia virtuale dell'hardware, su cui può girare un intero SO. Idea nata con **VM/370** di IBM (anni '70) per separare la multiprogrammazione dalla macchina estesa; oggi alla base del **cloud**. Il **Virtual Machine Monitor (VMM)** o **hypervisor** emula l'hardware:
- **Type 1 (bare metal)**: l'hypervisor gira **direttamente sull'hardware** (es. VMware ESXi, Xen, Hyper-V).
- **Type 2 (hosted)**: l'hypervisor gira **sopra un SO host** (es. VirtualBox, QEMU); nella pratica usa moduli del kernel per accelerare.

> [!info] Container — diversi dalle VM
> I **container** (Docker, LXC, Podman, Kubernetes) condividono il **kernel dell'host** e isolano a livello di **processo**: niente SO completo dentro, quindi leggeri e ad avvio rapido. Limite: non possono eseguire un kernel diverso da quello dell'host e non c'è partizionamento rigido delle risorse come nelle VM.
### Exokernel
Separa il **controllo** delle risorse dalla **macchina estesa**: come un VMM, ma **non emula l'hardware** — fornisce solo una condivisione sicura delle risorse a basso livello, assegnando a ciascuna VM utente solo le risorse che le competono. Elimina l'overhead delle mappature complesse. Uso prevalentemente di ricerca / alte prestazioni.
### Unikernel
Sistemi minimi basati su **LibOS** (Library Operating System): l'applicazione **e** il SO minimo necessario sono compilati in **un singolo binario** che gira su una VM, una sola applicazione per macchina.

- **Pro**: footprint minimo, avvio in millisecondi, superficie d'attacco ridotta, nessun overhead di protezione SO↔app.
- **Uso**: applicazioni cloud specializzate, microservizi, embedded.

---
**Argomento precedente:** [[01 - Introduzione ai Sistemi Operativi]] · **Prossimo:** [[03 - Processi e Thread]] — modello di processo, thread, e implementazione della multiprogrammazione.
