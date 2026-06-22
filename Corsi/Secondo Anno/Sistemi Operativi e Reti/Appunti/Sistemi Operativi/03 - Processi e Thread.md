# 03 - Processi e Thread
Il **processo** è l'astrazione con cui il SO esegue programmi per conto degli utenti; il **thread** è il flusso di esecuzione *dentro* un processo. Questa nota copre modello, gestione, stati, segnali/interrupt e thread. Prerequisito: l'astrazione di processo introdotta in [[02 - Concetti di Base e Strutture]].
## Il modello di processo
> [!quote] Definizione — Processo
> Un **processo è un programma in esecuzione**. È un'astrazione fondamentale del SO, che gli consente di semplificare **allocazione**, **accounting** (contabilizzazione) e **limitazione** delle risorse. Il SO mantiene in una **tabella dei processi** le informazioni sulle risorse e sullo stato interno di ogni processo.

Con la multiprogrammazione la CPU passa rapidamente da un processo all'altro (**process switch**): a livello fisico esiste **un solo program counter** e **un solo processo è attivo** in un dato istante, ma concettualmente ogni processo ha il **proprio flusso di controllo** (il proprio program counter logico). A ogni cambio si **salva il PC** del processo uscente e si **ripristina** quello entrante. Il risultato è uno **pseudo-parallelismo**: tutti i processi progrediscono, ma uno solo alla volta usa davvero la CPU.
### Processi concorrenti
In linea di principio i processi sono **reciprocamente indipendenti**: per interagire hanno bisogno di **mezzi espliciti** (vedi [[04 - Sincronizzazione]]). La CPU è assegnata a turno e il SO **non offre garanzie di tempistica né di ordine** di esecuzione: non si può quindi assumere *quando* o *in che ordine* i processi verranno eseguiti.
### Gerarchie di processi
Il SO crea in genere un solo processo iniziale, **`init`** (nei sistemi moderni `init` avvia anche **`kthreadd`**, processo che gestisce i thread del kernel). Da lì i processi si creano **in modo indipendente**: un processo **padre** crea un processo **figlio**, generando una **struttura ad albero** e **gruppi di processi**.

> [!example] La shell crea processi
> ```bash
> $ find /tmp & > t.log &
> $ ls | more
> ```
> Ogni comando lanciato dalla shell diventa un processo figlio; `init → login → sh → (ls, find, more)` è un tipico albero.
## Gestione dei processi
### Creazione di un processo
Quattro eventi principali causano la creazione di un processo:
1. **Inizializzazione** del sistema.
2. Esecuzione di una **system call di creazione** da parte di un processo già in esecuzione (`fork()`). ^fork
3. **Richiesta dell'utente** di creare un nuovo processo (es. da shell).
4. **Avvio di un lavoro batch**.
### Terminazione di un processo
Quattro condizioni tipiche:
1. **Uscita normale** (volontaria).
2. **Uscita per errore** (volontaria — il programma rileva l'errore e termina).
3. **Errore fatale** (involontario — es. istruzione illegale).
4. **Ucciso da un altro processo** (involontario, via segnale).
### System call di gestione
| Call | Cosa fa |
|------|---------|
| `fork` | Crea un nuovo processo: il figlio è un **clone "privato"** del genitore. Condivide *alcune* risorse (file aperti con offset condiviso, segmento di codice, variabili d'ambiente e directory corrente ereditate). |
| `exec` (`execve`) | **Sostituisce** l'immagine del processo con un nuovo programma. Usata in combinazione con `fork`. |
| `exit` | Terminazione **volontaria**; lo *stato di uscita* è restituito al processo **genitore**. |
| `kill` | Invia un **segnale** a un processo (o a un gruppo). Può causare la terminazione **involontaria**. |

> [!info] Codice di laboratorio
> Esempi C su `fork`, `exec`, segnali e pipe in `Materiale Didattico/.../code/5_elementi_di_programmazione_concorrente_code/`. Il pattern `fork` + `exec` + `waitpid` è quello della shell visto in [[02 - Concetti di Base e Strutture]].
## Stati di un processo
Un processo può trovarsi in **tre stati**:
- **Running** (in esecuzione): sta effettivamente usando la CPU.
- **Ready** (pronto): eseguibile, temporaneamente fermo per lasciare la CPU a un altro.
- **Blocked** (bloccato): non eseguibile finché non si verifica un **evento esterno** (es. arrivo di input).

Il SO alloca la CPU tenendo traccia di questi stati; è lo **[[05 - Scheduling|scheduler]]** a (de)assegnare la CPU. Lo stato evolve secondo quattro transizioni:

```text
Running ──(1) si blocca in attesa di input──►  Blocked
Running ──(2) lo scheduler sceglie un altro──►  Ready
Ready   ──(3) lo scheduler sceglie questo────►  Running
Blocked ──(4) l'input diventa disponibile────►  Ready
```
### Informazioni associate a un processo
Nella **tabella dei processi** il SO conserva, per ciascun processo: **PID**, **UID**, **GID**; lo **spazio di indirizzi** di memoria (vedi [[06 - Gestione della Memoria]]); i **registri hardware** (incluso il Program Counter); i **file aperti**; i **segnali** e gli **interrupt** pendenti.
## Segnali e interrupt
Sia i **segnali** sia gli **interrupt** servono a gestire **eventi asincroni**, ma a livelli diversi.

| | Interrupt | Segnale (signal) |
|---|---|---|
| **Origine** | dispositivi **hardware** (tastiera, disco) | eventi **software** (da un processo o dal SO) |
| **Gestione** | routine di servizio (**ISR**) | handler personalizzato o azione di default |
| **Uso** | comunicazione hardware↔software | condizioni eccezionali nelle applicazioni |
### Gli interrupt
**Idea**: per togliere la CPU a un processo e ridarla allo scheduler ci si appoggia al supporto hardware agli interrupt, così lo **scheduler ottiene periodicamente il controllo** — ogni volta che l'hardware genera un interrupt.

L'**interrupt vector** è associato a ciascun dispositivo di I/O e linea di interrupt, fa parte della **IDT** (Interrupt Descriptor Table) e contiene l'indirizzo iniziale del **gestore di interrupt** fornito dal SO. Tipi di interruzione: **software**, **dispositivo hardware (asincrono)**, **eccezioni**.

> [!example] Cosa succede a un interrupt (livello più basso del SO)
> 1. L'hardware **impila** il Program Counter e le info del processo.
> 2. L'hardware carica il **nuovo PC** dal vettore di interrupt.
> 3. La procedura **assembly salva i registri**.
> 4. La procedura assembly **imposta un nuovo stack**.
> 5. Viene eseguito il **servizio di interrupt in C** (tipicamente legge il buffer d'input).
> 6. Lo **scheduler** decide quale processo eseguire dopo.
> 7. La procedura C ritorna al codice assembly.
> 8. L'assembly **avvia il processo** scelto.

> [!warning] Lo scheduler è il mediatore
> A ogni interruzione lo scheduler ottiene il controllo: **un processo non può cedere la CPU a un altro (context switch) senza passare attraverso lo scheduler**.

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> Il salvataggio dei registri e la commutazione a livello assembly sono trattati in [[7 - Livello del linguaggio Assemblativo]]; gli interrupt come dispositivo hardware sono ripresi in [[08 - Input Output]].
### I segnali
- **Tipi**: indotti da hardware (es. `SIGKILL`) o da software (es. `SIGQUIT`, `SIGPIPE`).
- **Azioni** possibili: `Term`, `Ign`, `Core`, `Stop`, `Cont`. Ogni segnale ha un'azione di **default**, tipicamente **sovrascrivibile**; i segnali possono essere **bloccati** e le azioni ritardate.
- **Catching**: il processo registra un **handler**; il SO consegna il segnale e fa eseguire l'handler; il contesto corrente va salvato/ripristinato.
#### Permessi e consegna
Un processo può inviare segnali **solo a processi dello stesso utente** (il kernel controlla **UID/EUID** → niente `Ctrl+C` ai processi di root). L'invio (`kill`) è una **system call**: il segnale viene **accodato nel kernel** al processo/thread target.

Ogni processo (o thread) ha nel kernel una struttura con: **segnali pendenti** (in attesa di consegna), **maschera dei segnali bloccati** (temporaneamente sospesi) e **tabella delle disposizioni** (per ogni segnale: default, ignorato o handler personalizzato).

Alla consegna, se è registrato un **handler utente** il kernel: **salva il contesto** (registri, PC, SP, flag), **prepara lo stack del segnale** e imposta l'indirizzo dell'handler. L'handler viene eseguito in **user space**; al termine un *trampolino* invoca la system call **`rt_sigreturn`**, con cui il kernel **ripristina il contesto** e **riprende il PC originale**. Se **non** c'è handler, si applica la **disposizione di default** (termina, ignora o sospende, a seconda del segnale).
#### Esempio: gestire Ctrl+C (SIGINT)
```c
void signalHandler(int signum) {
    printf("Interrupt signal %d received\n", signum);
    // cleanup e terminazione
    exit(signum);
}
int main() {
    signal(SIGINT, signalHandler);   // registra handler per SIGINT (Ctrl+C)
    while (1) {
        printf("Going to sleep....\n");
        sleep(1);
    }
    return 0;
}
```
## Thread
Finora abbiamo assunto **1 processo ⇒ 1 thread**. Con l'esecuzione **multithreaded** un processo ha **N thread**. Perché più thread per processo? Sono **lightweight process** (processi leggeri): consentono **parallelismo efficiente** in spazio e tempo e una **comunicazione/sincronizzazione semplici** (condividono lo **spazio di indirizzi**).

> [!example] Usi tipici
> Un **word processor** con tre thread (interazione tastiera, riformattazione, salvataggio su disco) resta reattivo mentre lavora in background. Un **web server multithread** ha un **dispatcher thread** che riceve le richieste e le passa ai **worker thread**, sfruttando una **web page cache** condivisa.
>
> Schema di massima del codice (slide "Utilizzo dei thread (2)"):
> ```c
> // (a) dispatcher thread
> while (TRUE) {
>     get_next_request(&buf);
>     handoff_work(&buf);
> }
>
> // (b) worker thread
> while (TRUE) {
>     wait_for_work(&buf);
>     look_for_page_in_cache(&buf, &page);
>     if (page_not_in_cache(&page))
>         read_page_from_disk(&buf, &page);
>     return_page(&page);
> }
> ```
### Thread e processi
I thread **risiedono nello stesso spazio di indirizzi di un singolo processo**: tutti gli scambi avvengono **tramite dati condivisi** (e i thread si sincronizzano con [[04 - Sincronizzazione|semplici primitive]]). Ogni thread ha però **stack**, **registri hardware** e **stato** propri. La tabella dei thread è più leggera di quella dei processi, e ciascun thread può effettuare qualsiasi system call per conto del processo a cui appartiene.

| Per processo (condiviso) | Per thread (privato) |
|---|---|
| Spazio di indirizzi | Program counter |
| Variabili globali | Registri |
| File aperti | Stack |
| Processi figli | Stato |
| Allarmi pendenti | |
| Segnali e relativi handler | |
| Informazioni di accounting | |
### Thread POSIX (pthreads)
| Chiamata | Descrizione |
|---|---|
| `pthread_create` | Crea un nuovo thread |
| `pthread_exit` | Termina il thread chiamante |
| `pthread_join` | Attende l'uscita di uno specifico thread |
| `pthread_yield` | Rilascia la CPU per un altro thread |
| `pthread_attr_init` | Crea e inizializza la struttura di attributi |
| `pthread_attr_destroy` | Rimuove la struttura di attributi |

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_THREADS 10
void *print_hello_world(void *tid) {
    printf("Hello World. Greetings from thread %d\n", tid);
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);
        if (status != 0) exit(-1);
    }
    return 0;
}
```
> [!warning] Output non deterministico — domanda del docente
> Il `main` **non chiama `pthread_join`**: termina (con `return 0`) senza attendere il completamento dei thread figli. L'ordine in cui i 10 thread eseguono `printf` dipende dallo **scheduler**, che non offre garanzie di tempistica né di ordine (cfr. [[#Processi concorrenti]]). L'output osservabile può essere qualsiasi permutazione dei messaggi, o addirittura incompleto se il processo termina prima che tutti i thread abbiano stampato. *"What will the output be?"* — la risposta corretta è: **non si può sapere a priori**.
> [!info] Codice di laboratorio
> Esempi su thread, producer-consumer e reader-writer in `Materiale Didattico/.../code/6_thread_e_sincronizzazione/`.
### Implementazione dei thread
Esistono **tre luoghi** di implementazione: nello **spazio utente**, nel **kernel**, o **ibrida**.
#### Nello spazio utente
I thread sono gestiti da una **libreria** in user space; il kernel li vede come normali processi a singolo thread (funzionano anche su SO che **non supportano** i thread). Ogni processo ha la **propria tabella dei thread**.
- **Pro**: il cambio tra thread **non richiede un context switch completo** (niente `trap` → **molto più veloce**); si può **personalizzare l'algoritmo di scheduling** per processo; maggiore scalabilità.
- **Contro**: una **system call bloccante** di un thread **ferma tutti** i thread del processo; un **page fault** blocca l'intero processo; **niente interrupt del clock** → impossibile uno scheduling round-robin. Quindi poco adatti ad applicazioni in cui i thread si bloccano spesso (es. web server).
#### Nello spazio kernel
È il **kernel** a gestire i thread: niente sistema run-time per processo. Le chiamate potenzialmente bloccanti sono **system call** (costo più alto), ma se un thread si blocca il kernel può eseguire un altro thread (dello stesso o di un altro processo). Alcuni sistemi **riciclano** i thread per ridurre i costi; a un page fault il kernel verifica se ci sono altri thread eseguibili.
#### Ibrida
Si effettua il **multiplexing** dei thread utente su un numero scelto di **thread del kernel**: il programmatore decide quanti thread kernel usare e quanti thread utente multiplexare. Il kernel è consapevole solo dei thread kernel, ma ciascuno di essi può gestire più thread utente. Combina i vantaggi dei due approcci.
### Problemi aperti
La programmazione con thread richiede cautela:
- Molte **procedure di libreria** possono causare **conflitti** se un thread sovrascrive dati cruciali per un altro (es. un buffer condiviso per assemblare un messaggio di rete, sovrascritto da un secondo thread dopo un interrupt del clock). I **wrapper** (un bit "libreria in uso") evitano i conflitti ma limitano il parallelismo → tema della [[04 - Sincronizzazione]].
- La **gestione dei segnali** è complicata: alcuni sono specifici di un thread, altri no, e decidere chi li gestisce è non banale.

---
**Argomento precedente:** [[02 - Concetti di Base e Strutture]] · **Prossimo:** [[04 - Sincronizzazione]] — race condition, mutua esclusione, semafori, mutex, monitor e problemi classici di IPC.
