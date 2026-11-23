# Sincronizzazione
I processi (e i [[03 - Processi e Thread|thread]]) raramente vivono isolati: hanno bisogno di **comunicare** — scambiarsi dati durante l'esecuzione — e di **sincronizzarsi**, cioè coordinarsi per rispettare le dipendenze reciproche ed evitare di intralciarsi. L'insieme dei meccanismi con cui il sistema operativo consente ai processi di scambiarsi informazioni e coordinare le proprie azioni prende il nome di **comunicazione tra processi** (*Inter-Process Communication*, **IPC**). Questa nota affronta il nodo centrale dell'IPC con memoria condivisa — la **mutua esclusione**, cioè garantire che un solo processo alla volta entri nella porzione di codice che usa una risorsa condivisa — e ne presenta le soluzioni in ordine di astrazione crescente: semafori, mutex, variabili condizionali e monitor. ^ipc

> [!info] Per il laboratorio
> Gli esercizi di questa parte si scrivono in **C** con le **POSIX Threads** (`pthread`). Se segui l'ordine delle lezioni conviene affrontare prima [[10 - Programmazione C e Concorrente]] (compilazione, `pthread_create`/`pthread_join`) e [[09 - Linux e BASH]] (shell e strumenti del terminale): nelle slide il laboratorio in C precede la teoria della sincronizzazione, mentre in queste note l'ordine segue il libro di testo (Tanenbaum).
## Il problema della concorrenza
Poiché i processi sono [[03 - Processi e Thread#Processi concorrenti|concorrenti]] e il SO non garantisce ordine né tempistica, l'accesso non coordinato a dati condivisi produce errori.

Nell'edizione 2026-2027 la slide precisa il quadro (pp. 8 e 71-72). I **thread dello stesso processo** condividono lo spazio di indirizzamento (codice, variabili globali e heap) e possono quindi accedere e modificare contemporaneamente gli stessi dati; ciascun thread possiede però i propri registri, Program Counter e stack. I **processi distinti** hanno normalmente spazi di indirizzamento separati (le variabili di un processo non sono direttamente accessibili dagli altri) ma possono condividere risorse, ad esempio file o dispositivi. In entrambi i casi l'accesso concorrente a risorse condivise può richiedere **sincronizzazione** e mutua esclusione: i problemi e gli algoritmi di questa nota sono generali, mentre gli esempi pratici usano soprattutto i thread e le primitive Pthreads. Tra processi la comunicazione passa da meccanismi espliciti di IPC (le **pipe** scambiano dati; i **segnali** notificano eventi, e il processo destinatario può reagire con un *signal handler*); tra thread dello stesso processo bastano le variabili condivise, coordinate con mutex, semafori e variabili condizionali. Idea chiave: i processi sono normalmente isolati nella memoria; i thread condividono la memoria, ma devono sincronizzarsi (la condivisione rende la comunicazione più immediata, ma introduce il rischio di race condition).
### Race condition
> [!quote] Definizione — Race condition
> Situazione in cui due o più processi accedono a dati condivisi e il risultato finale **dipende dall'ordine** preciso di esecuzione. La lettura/aggiornamento di un dato dovrebbe essere **atomica**: se non lo è, i processi "gareggiano" e possono giungere a conclusioni errate.

> [!example] Lo spooler di stampa
> Lo *spooler di stampa* è il servizio che mette in coda i documenti da stampare depositandoli in un'apposita **directory di spooling**; più processi vi accodano file contemporaneamente, ed è questa scrittura concorrente a generare la corsa. Una variabile condivisa `in` indica la prossima posizione libera nella coda. Il processo A legge `in = 7`, ma viene **sospeso** prima di usarla; B legge a sua volta `in = 7`, scrive il proprio file in posizione 7 e aggiorna `in = 8`. Quando A riprende, scrive anch'esso in posizione 7, **sovrascrivendo** il file di B: un lavoro di stampa va perso. L'esito finale dipende dall'**ordine di esecuzione** dei due processi — ecco la race condition.

> [!question] Domanda tipica d'esame
> **D:** Cos'è una race condition e perché è problematica? **R:** Una race condition è una situazione in cui due o più processi accedono a dati condivisi e il risultato finale dipende dall'ordine preciso di esecuzione. È problematica perché produce risultati errati e non deterministici: nell'esempio dello spooler di stampa, due processi leggono la stessa posizione libera e uno sovrascrive l'altro, causando la perdita di un lavoro di stampa.
### Regioni critiche e requisiti
La parte di codice in cui un processo accede a una risorsa condivisa è la **regione critica** (*critical region*). Concettualmente ogni processo attraversa quattro fasi in sequenza: la **sezione di ingresso** (*entry*), in cui chiede il permesso di entrare; la **regione critica** vera e propria; la **sezione di uscita** (*exit*), che segnala l'avvenuta uscita; e la **sezione non critica** (*remainder*), tutto il resto del lavoro che non tocca risorse condivise. Il problema della mutua esclusione consiste nel progettare le sezioni di ingresso e di uscita in modo che due regioni critiche non si sovrappongano mai. *(extra, non da slide: la scomposizione in quattro fasi)* Una buona soluzione deve soddisfare, secondo la slide, **quattro requisiti**:
1. Due processi non possono trovarsi **contemporaneamente** nelle rispettive regioni critiche.
2. Non si possono fare **ipotesi** sulla velocità o sul numero di CPU.
3. Nessun processo **fuori** dalla propria regione critica può bloccarne altri.
4. Nessun processo deve **aspettare all'infinito** per entrare nella propria regione critica.

> [!question] Domanda tipica d'esame
> **D:** Elenca i quattro requisiti di una buona soluzione alla mutua esclusione. **R:** (1) Due processi non possono trovarsi contemporaneamente nelle rispettive regioni critiche; (2) non si possono fare ipotesi sulla velocità o sul numero di CPU; (3) nessun processo fuori dalla propria regione critica può bloccarne altri; (4) nessun processo deve aspettare all'infinito per entrare nella propria regione critica.
## Mutua esclusione con busy waiting
Le prime soluzioni tengono la CPU occupata mentre si attende: **busy waiting**.
### (Non) soluzioni elementari
- **Disabilitare gli interrupt**: impedisce la riallocazione della CPU, ma funziona **solo su CPU singola**; *(extra, non da slide)* è inoltre pericoloso lasciarlo fare ai processi utente. Su sistemi **multicore**, disabilitare gli interrupt di un core non offre garanzie: gli altri core possono comunque accedere alla memoria condivisa e interferire. *(extra, non da slide)*
- **Variabili di blocco** (lock 0/1): proteggono la regione critica, ma la "corsa" si sposta semplicemente **sulla variabile di blocco** (leggere-e-impostare non è atomico).
### Alternanza rigorosa
Una variabile `turn` stabilisce di chi è il turno; ciascuno aspetta in `while(turn != me)`. **Non** è una buona soluzione: viola il requisito 3 — un processo fuori dalla regione critica può **bloccarne** un altro (non si può entrare due volte di fila).
### Algoritmo di Peterson
Combina la variabile `turn` con un array `interested[]`: prima di entrare, un processo segnala l'interesse e scrive `turn` con il **proprio** indice, poi attende **finché `turn` resta suo e l'altro è interessato**. Se entrambi tentano insieme, l'**ultimo** a scrivere `turn` è quello che aspetta, mentre l'altro entra: niente attesa reciproca.

Analogia della slide 2026-2027 (p. 12): Alice e Bob vogliono usare un'unica postazione in un ufficio, una persona alla volta. Ciascuno **segnala il proprio interesse**; se l'altro non è interessato entra subito; se lo sono entrambi, **chi scrive per ultimo il proprio nome cede la precedenza** all'altro, che entra; chi non ha la precedenza attende, e all'uscita segnala di aver finito. Domanda della slide: se Alice scrive per ultima il proprio nome, chi aspetta? Aspetta **Alice**.
```c
#define N 2                    /* numero di processi */
int turn;                      /* chi cede la precedenza in caso di contesa */
int interested[N];             /* inizialmente tutti 0 (FALSE) */

void enter_region(int process) {        /* process è 0 o 1 */
    int other = 1 - process;            /* l'altro processo */
    interested[process] = TRUE;         /* mostra interesse */
    turn = process;                     /* imposta il flag */
    while (turn == process && interested[other] == TRUE)
        ;                               /* attesa attiva (busy waiting) */
}
void leave_region(int process) {
    interested[process] = FALSE;        /* esce dalla regione critica */
}
```
Nella slide 2026-2027 (p. 13) `turn` non indica quale processo può entrare, ma **quale processo deve aspettare** se entrambi sono interessati: chi scrive per ultimo in `turn` cede la precedenza all'altro. Disclaimer della slide: Peterson è un algoritmo teorico; il codice con normali variabili `int` non è un'implementazione C moderna sicura, perché richiederebbe operazioni atomiche e un modello di memoria adeguato.

> [!question] Domanda tipica d'esame
> **D:** Perché l'alternanza rigorosa non è una soluzione accettabile alla mutua esclusione? Come la risolve l'algoritmo di Peterson? **R:** L'alternanza rigorosa viola il requisito 3: un processo fermo fuori dalla propria regione critica può bloccare l'altro impedendogli di entrarvi due volte di fila (non si può entrare due volte consecutive). L'algoritmo di Peterson combina la variabile `turn` con l'array `interested[]`: prima di entrare ogni processo segnala il proprio interesse e scrive il proprio indice in `turn`; se entrambi tentano insieme, l'ultimo a scrivere `turn` attende mentre l'altro entra, eliminando l'attesa reciproca senza violare nessuno dei quattro requisiti.

> [!info] Mettiti alla prova
> - **Teorico:** traccia di un'esecuzione interlacciata di Peterson (chi entra, chi attende) → [[04 - Sincronizzazione (Esercizi)#Es. 1 — Traccia dell'algoritmo di Peterson|Es. 1]].
### TSL e XCHG
*(extra, non da slide)* *Sezione non presente nelle slide: la slide 6 si limita a dire che i mutex «possono essere implementati nello spazio utente con istruzioni come TSL o XCHG» (vedi [[#Mutex]]); il funzionamento di TSL e il codice assembly non vi compaiono.*
Molte CPU offrono un'istruzione hardware per la mutua esclusione: **TSL** (*Test and Set Lock*). TSL legge il contenuto di una locazione di memoria (`LOCK`) in un registro e vi scrive un valore non zero, il tutto in modo **atomico** — il bus viene bloccato verso le altre CPU per tutta la durata dell'operazione, impedendo qualsiasi accesso concorrente alla stessa locazione.
```asm
enter_region:
    TSL REGISTER, LOCK   ; copia lock nel registro e imposta lock a 1
    CMP REGISTER, #0     ; il lock era 0?
    JNE enter_region     ; se era già 1, riprova (busy waiting)
    RET                  ; lock acquisito, entra nella regione critica
leave_region:
    MOVE LOCK, #0        ; imposta lock a 0
    RET                  ; torna al chiamante
```
L'alternativa è l'istruzione **XCHG**, che scambia atomicamente il contenuto di due locazioni. È disponibile su **tutte le CPU x86 Intel** ed è usata per la sincronizzazione di basso livello al posto di TSL. La differenza pratica è minima: entrambe garantiscono l'atomicità, ma XCHG è lo standard su architettura x86 mentre TSL è comune su altre famiglie.

> [!info] TSL, XCHG e i mutex
> Le istruzioni TSL e XCHG sono la base su cui si costruiscono i **mutex in user space**: `mutex_lock` e `mutex_unlock` (vedi [[#Mutex]]) possono essere implementati con queste istruzioni senza passare dal kernel quando la risorsa è libera; in caso di contesa reale il lock ricorre comunque al kernel per bloccare il thread (come descritto per il Futex).
### Il problema del busy waiting
Tutte queste soluzioni tengono la CPU **occupata ad attendere** (**spin lock**): è uno **spreco di risorse**. La soluzione è far sì che un processo in attesa **restituisca volontariamente la CPU** allo scheduler invece di "girare a vuoto".
## sleep e wakeup
Due primitive: `sleep()` blocca il processo chiamante (stato `BLOCKED`, CPU allo scheduler); `wakeup(process)` lo riporta a `READY`. *(i nomi degli stati sono quelli della [[03 - Processi e Thread]], non della slide)*

> [!example] Produttore-consumatore con sleep/wakeup
> Due processi condividono un buffer di dimensione fissa e un contatore `count`. Il **produttore** inserisce e dorme se il buffer è pieno (`count == N`); il **consumatore** preleva e dorme se è vuoto (`count == 0`). Ciascuno risveglia l'altro al momento giusto.
> ```c
> void producer(void){
>     while(TRUE){
>         item = produce_item();
>         if(count == N) sleep();         /* buffer pieno: si addormenta */
>         insert_item(item);
>         count++;
>         if(count == 1) wakeup(cons);    /* era vuoto: sveglia il consumatore */
>     }
> }
> void consumer(void){
>     while(TRUE){
>         if(count == 0) sleep();         /* buffer vuoto: si addormenta */
>         item = remove_item();
>         count--;
>         if(count == N-1) wakeup(prod);  /* era pieno: sveglia il produttore */
>         consume_item(item);
>     }
> }
> ```

> [!warning] Il problema del wakeup perso (lost wakeup)
> Il consumatore potrebbe essere risvegliato **un attimo prima** di addormentarsi: legge `count == 0`, ma prima di chiamare `sleep()` viene interrotto; il produttore inserisce e invia `wakeup`, che però va **perso** perché il consumatore non dorme ancora. Poi il consumatore dorme… e nessuno lo risveglierà più. Un **bit di attesa del wakeup** (accumulatore di risvegli) è un *workaround*, ma non risolve sempre il problema: si attiva quando un processo non dormiente riceve un `wakeup`; se è acceso, impedisce al processo di entrare in `sleep` e viene poi spento; viene **resettato dal consumatore ad ogni ciclo**.
## Semafori
Un semaforo è una **variabile di sincronizzazione**, introdotta da **E. W. Dijkstra** (1965, anno dalla slide 2025-2026), che rappresenta un **numero di disponibilità** (slide 2026-2027, p. 22); nell'edizione 2025-2026 la slide lo presentava come lo strumento creato per contare e gestire i wakeup. È un intero ≥ 0 con due operazioni **atomiche** ("indivisibili"):
- **`down`** (P): se il valore è > 0 lo decrementa e prosegue; se è 0 il processo si **blocca** in attesa di una disponibilità, in una coda di attesa associata al semaforo ("va a dormire").
- **`up`** (V): rende disponibile una risorsa; se ci sono processi in attesa, ne permette a uno di proseguire. *(slide 2025-2026)* Se il valore è 0 e ci sono processi nella coda di attesa, questi vengono **svegliati** (eventualmente per entrare in competizione ed eseguire di nuovo `down`); in ogni caso il valore viene **incrementato** e il processo che ha invocato `up` continua la sua esecuzione.

Idea chiave della slide 2026-2027: `down` e `up` sono atomiche, cioè il controllo e l'aggiornamento del semaforo non possono interferire tra loro.

In C con le API POSIX (`<semaphore.h>`) `down` corrisponde a `sem_wait()` e `up` a `sem_post()`; si inizializza con `sem_init(&s, 0, valore)` e si distrugge con `sem_destroy()`. Gli esempi 2026-2027 definiscono due funzioni `down()`/`up()` che li incapsulano, così il codice resta identico allo pseudocodice delle slide. *(avviso degli esempi: `sem_init` per semafori anonimi non funziona su macOS, usare Linux)*

> [!example] Produttore-consumatore con semafori
> Tre semafori: `mutex` (accesso esclusivo al buffer), `empty` (posti liberi, inizialmente N), `full` (posti occupati, inizialmente 0).
> ```c
> #define N 100
> typedef int sema;
> sema mutex = 1;
> sema empty = N, full = 0;
>
> void producer(void){
>     int item;
>     while(TRUE){ item = produce_item();
>         down(&empty);    /* un posto libero in meno */
>         down(&mutex);    /* entra nella regione critica */
>         insert_item(item);
>         up(&mutex);      /* esce dalla regione critica */
>         up(&full); } }   /* un posto occupato in più */
> void consumer(void){
>     int item;
>     while(TRUE){
>         down(&full);
>         down(&mutex);
>         item = remove_item();
>         up(&mutex);
>         up(&empty);
>         consume_item(item); } }
> ```
> `mutex` **serializza** l'accesso al buffer; `empty` blocca il produttore quando il buffer è pieno, `full` blocca il consumatore quando è vuoto. Codice in `Esempi/6_thread_e_sincronizzazione/6.2_producer_consumer_semaphore.c`; nella versione 2026-2027 (`Esempi/6_thread_e_sincronizzazione_2026-2027/`) il buffer è una **coda circolare FIFO** di N posizioni e produttore e consumatore eseguono un numero finito di iterazioni, mentre la versione 2025-2026 usa un buffer gestito come pila (indice `in` che sale e scende) con cicli infiniti.

> [!example] Deadlock da inversione dei down — errore classico da esame *(extra, non da slide)*
> Nel produttore-consumatore con semafori l'ordine corretto nel produttore è:
> ```c
> down(&empty);   /* 1. verifica che ci sia spazio */
> down(&mutex);   /* 2. entra nella regione critica */
> ```
> Se i due `down` vengono **invertiti**:
> ```c
> down(&mutex);   /* 1. acquisisce la regione critica */
> down(&empty);   /* 2. verifica lo spazio — TROPPO TARDI */
> ```
> Supponiamo che il buffer sia **pieno** ($\text{empty} = 0$): il produttore acquisisce `mutex` (ora $= 0$), poi si blocca su `down(&empty)` perché il buffer è pieno. Il consumatore tenta `down(&mutex)` per prelevare un elemento, ma `mutex = 0` — va in sleep. Nessuno può proseguire: il produttore attende spazio, il consumatore attende il mutex, ma solo il consumatore potrebbe liberare spazio e solo il produttore potrebbe rilasciare il mutex. **Deadlock**. Lo stesso ragionamento vale per l'inversione nel consumatore (`down(&mutex)` prima di `down(&full)`).
### I filosofi a cena
*(extra, non da slide)* *Sezione non presente nelle slide: filosofi a cena, livelock ed Ethernet non compaiono nella slide 6.*
Problema classico posto e risolto da **Dijkstra (1965)**, da allora banco di prova per ogni nuova primitiva di sincronizzazione. **Cinque filosofi** siedono a un tavolo circolare e alternano il **pensare** e il **mangiare**; per mangiare servono **due forchette** (sinistra e destra), ma fra ogni coppia di piatti c'è **una sola forchetta** condivisa coi vicini. Obiettivo: farli mangiare senza che restino bloccati per sempre.
La soluzione "ovvia" — *prendi la forchetta sinistra, poi la destra* — è **sbagliata**:

> [!warning] Deadlock e starvation
> - Se **tutti** afferrano la forchetta sinistra nello stesso istante, nessuno può prendere la destra: **deadlock**.
> - Variante "se la destra è occupata, posa la sinistra e riprova": se i filosofi restano sincronizzati prendono-posano all'infinito senza progredire. I processi *eseguono* azioni ma non *avanzano*: è una forma di **livelock** (un tipo di starvation in cui non c'è blocco passivo, ma assenza di progresso). Aspettare un tempo **casuale** riduce il rischio (è ciò che fa Ethernet con le collisioni), ma non lo elimina: inaccettabile dove serve garanzia (es. il controllo di un impianto nucleare).

Una soluzione corretta ma **senza parallelismo** è racchiudere l'intera fase in un **mutex**: mangia un filosofo per volta. La soluzione di Tanenbaum permette invece il **massimo parallelismo** (due filosofi non vicini mangiano insieme) usando un **array di stati** + **un semaforo per filosofo**:
```c
#define N 5
#define LEFT  (i+N-1)%N        /* vicino di sinistra di i */
#define RIGHT (i+1)%N          /* vicino di destra di i   */
#define THINKING 0
#define HUNGRY   1
#define EATING   2
typedef int sema;
int  state[N];                 /* stato di ogni filosofo        */
sema mutex = 1;                /* protegge l'array state[]      */
sema s[N];                     /* un semaforo per filosofo (init 0) */

void philosopher(int i){
    while(TRUE){ think(); take_forks(i); eat(); put_forks(i); }
}
void take_forks(int i){
    down(&mutex);
    state[i] = HUNGRY;
    test(i);                   /* prova a prendere le due forchette */
    up(&mutex);
    down(&s[i]);               /* si blocca se non le ha ottenute   */
}
void put_forks(int i){
    down(&mutex);
    state[i] = THINKING;
    test(LEFT);                /* un vicino può mangiare adesso? */
    test(RIGHT);
    up(&mutex);
}
void test(int i){
    if(state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING){
        state[i] = EATING;
        up(&s[i]);             /* sblocca il filosofo i */
    }
}
```
Un filosofo passa a **EATING solo se nessuno dei due vicini sta mangiando**: il `mutex` protegge `state[]`, mentre il semaforo `s[i]` tiene bloccato il filosofo affamato finché le forchette non si liberano. Risultato: **niente deadlock né starvation**, con il massimo parallelismo possibile.
### Lettori e scrittori
Regola base: in ogni istante sono ammessi **R lettori oppure 1 scrittore** (es. un database: molte letture simultanee, una sola scrittura). Il **primo** lettore blocca l'accesso agli scrittori (`down(&db)`), i successivi incrementano un contatore `rc`, l'**ultimo** lo rilascia (`up(&db)`).
```c
typedef int sema;
sema mutex = 1;        /* protegge il contatore rc */
sema db = 1;           /* controlla l'accesso al database */
int rc = 0;            /* numero di lettori attivi */

void reader(void){
    while(TRUE){
        down(&mutex); rc++; if(rc == 1) down(&db); up(&mutex);
        read_db();
        down(&mutex); rc--; if(rc == 0) up(&db); up(&mutex);
        use_data_read();
    }
}
void writer(void){
    while(TRUE){
        think_up_data();
        down(&db); write_db(); up(&db);
    }
}
```

> [!warning] Starvation degli scrittori
> Se nuovi lettori continuano ad arrivare mentre uno scrittore attende, lo scrittore potrebbe **non ottenere mai** l'accesso (blocco perpetuo). Una soluzione mette i nuovi lettori **in coda dietro** gli scrittori in attesa (gli scrittori ottengono l'accesso dopo i lettori già attivi): riduce la concorrenza, con un potenziale impatto sulle prestazioni, ma evita la starvation. Esistono anche soluzioni che danno **priorità agli scrittori**; ogni strategia ha vantaggi e svantaggi. Codice in `Esempi/6_thread_e_sincronizzazione/6.3_reader_writer_semaphore.c`. Nella versione 2026-2027 (`Esempi/6_thread_e_sincronizzazione_2026-2027/6.3_reader_writer_semaphore.c`) ci sono 3 thread lettori e 1 scrittore, ciascuno con 5 operazioni, due semafori POSIX `mutex` (protegge `rc`) e `db`, e i wrapper `down()`/`up()` che chiamano `sem_wait()`/`sem_post()`; compilato con `-Wall -Wextra -pthread` ed eseguito: termina senza warning, con 15 letture e 5 scritture. Priorità ai lettori (come nella slide), quindi la starvation dello scrittore resta possibile.

> [!info] Mettiti alla prova
> - **Teorico:** traccia dei valori di un semaforo → [[04 - Sincronizzazione (Esercizi)#Es. 2 — Valori di un semaforo e coda dei bloccati|Es. 2]]; deadlock da inversione dei `down` → [[04 - Sincronizzazione (Esercizi)#Es. 3 — Deadlock da inversione dei `down`|Es. 3]]; traccia produttore–consumatore → [[04 - Sincronizzazione (Esercizi)#Es. 4 — Produttore–consumatore: traccia dei semafori|Es. 4]]; lettori–scrittori → [[04 - Sincronizzazione (Esercizi)#Es. 5 — Lettori e scrittori: il contatore `rc`|Es. 5]].
> - **C:** [[Indice degli Esercizi#Thread e Sincronizzazione|prod_cons_sem.c]] (produttore–consumatore con la tripla `mutex`/`full`/`empty`) e [[Indice degli Esercizi#Thread e Sincronizzazione|readers_writers_pari_dispari.c]] (lettori–scrittori con priorità ai lettori).
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Semafori|TS1]] (produttore–consumatore) e [[Tracce d'Esame Pratiche#Thread — Semafori|TS3]] (uno scrittore, cinque lettori).
## Mutex
Un **mutex** è una versione **esplicita e semplificata** del semaforo, usata per la sola mutua esclusione quando **non serve contare**. Ha due stati: **locked** e **unlocked** (basta un bit, ma spesso si usa un intero: 0 = *unlocked*, altri valori = *locked*; slide 2026-2027, p. 36). Due procedure: `mutex_lock` e `mutex_unlock`.

Un thread che vuole entrare nella regione critica chiama `mutex_lock` (in Pthreads `pthread_mutex_lock()`): se il mutex è *unlocked* lo acquisisce ed entra; se è *locked* attende che diventi disponibile. Terminata la regione critica chiama `mutex_unlock` (`pthread_mutex_unlock()`). *(slide 2025-2026)* L'attesa avviene **senza busy waiting**: se un thread non può acquisire il lock, cede la CPU a un altro thread con `thread_yield`. Nella slide 2026-2027 (p. 37) questo punto è riformulato: nelle implementazioni moderne l'attesa può comportare la **sospensione** del thread, evitando di occupare inutilmente la CPU, e alcune implementazioni possono usare brevi fasi di busy waiting.

> [!info] Dettagli
> I mutex possono essere implementati in user space con istruzioni atomiche come **TSL** o **XCHG** (vedi [[05 - Livello di architettura dell'insieme d'istruzioni]]). Alcune librerie offrono `mutex_trylock`, che tenta il lock o restituisce errore **senza bloccare**. I mutex sono efficaci quando i thread condividono lo spazio di indirizzi. La condivisione di memoria tra processi può essere gestita tramite il kernel o con sistemi operativi che permettono di condividere parti dello spazio degli indirizzi *(slide 2026-2027, p. 38)*.
### Mutex in Pthreads
| Chiamata | Descrizione |
|---|---|
| `pthread_mutex_init` | Inizializza un mutex |
| `pthread_mutex_destroy` | Distrugge un mutex (solo se non detenuto) |
| `pthread_mutex_lock` | Blocca il mutex (sospende se già occupato) |
| `pthread_mutex_trylock` | Tenta il lock senza sospendere (errore se occupato) |
| `pthread_mutex_unlock` | Sblocca (solo il thread che detiene il lock) |

**`lock` vs `trylock`**: `lock` quando l'accesso esclusivo è necessario e si **può attendere** in coda; `trylock` quando si vuole **solo tentare** e proseguire con altro se il lock è occupato (utile per evitare deadlock).

```c
if (pthread_mutex_trylock(&mutex) == 0) {
    /* lock ottenuto: si eseguono le operazioni protette */
    printf("Ho ottenuto il lock e sto eseguendo operazioni.\n");
    sleep(2);                       /* simula un'operazione lunga */
    printf("Ho terminato e rilascio il lock.\n");
    pthread_mutex_unlock(&mutex);
} else {
    /* lock non disponibile: si prosegue con altre operazioni */
    printf("Non sono riuscito a ottenere il lock, continuo con altre operazioni.\n");
}
```

> [!info] Futex (Fast User Space Mutex) *(extra, non da slide)*
> Gli **spin-lock** e i mutex con busy waiting sprecano CPU per attese lunghe; passare al kernel per bloccare un processo è oneroso se le contese sono poche. Il **Futex** combina i due approcci: tenta prima di acquisire il lock in **user space** (senza syscall, come TSL/XCHG) e ricorre al kernel per bloccarsi solo se la contesa è reale. Così le acquisizioni non contese restano veloci, e si paga il costo del kernel solo quando davvero necessario.
### Semaforo o mutex?
- **Finalità**: il **mutex** garantisce la mutua esclusione (una risorsa, un thread alla volta); il **semaforo** controlla l'accesso a una risorsa ma serve anche per la **sincronizzazione** tra thread (es. produttore/consumatore).
- **Semantica**: il mutex ha una semantica di **proprietà** (solo chi l'ha acquisito può rilasciarlo); il semaforo **no** (qualsiasi thread può fare `up`/`down`).
- **Regola pratica**: per la sola esclusione mutua → **mutex** (più semplice e prevedibile); per coordinare più thread o risorse con N istanze → **semaforo**.

> [!question] Domanda tipica d'esame
> **D:** Qual è la differenza tra mutex e semaforo? Quando si preferisce l'uno all'altro? **R:** Il mutex è una primitiva binaria (locked/unlocked) con semantica di **proprietà**: solo il thread che ha acquisito il lock può rilasciarlo. Il semaforo è un contatore intero ≥ 0 incrementabile/decrementabile da qualsiasi thread, e serve sia per la mutua esclusione sia per la sincronizzazione tra thread (es. produttore/consumatore con semafori `empty` e `full`). Si usa il mutex per la sola esclusione mutua (più semplice e prevedibile); il semaforo quando occorre coordinare più thread o gestire risorse con N istanze.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Thread e Sincronizzazione|thread_mutex_file.c]] (accesso esclusivo a un file via mutex) e [[Indice degli Esercizi#Thread e Sincronizzazione|init_max_min_mutex.c]] (mutex senza variabile condizione, con flag e busy-wait).
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Mutex|TM1]] e [[Tracce d'Esame Pratiche#Thread — Mutex|TM3]].
## Variabili condizionali (pthread_cond)
Il mutex da solo **non** consente di attendere efficientemente una **condizione specifica** (es. "il buffer non è vuoto"; oppure: un thread deve attendere che un contatore condiviso raggiunga un valore, ad esempio ≥ 10; il mutex da solo garantisce l'accesso a uno alla volta, ma non fa attendere in modo efficiente; slide 2026-2027, p. 43): senza altri strumenti il thread dovrebbe fare busy waiting su un `while`. Le **variabili condizionali** (`pthread_cond`) aggiungono la possibilità di sospendersi finché un evento non si verifica, **senza consumare CPU**.

Un thread chiama `pthread_cond_wait(&cond, &mutex)`: **rilascia atomicamente il mutex** e si addormenta; quando un altro thread chiama `pthread_cond_signal`, il thread si risveglia e **riacquisisce il mutex**.

> [!example] Giulia, Matteo e il portatile condiviso
> Il portatile sta in un armadietto chiuso a chiave (il **mutex**); a volte è **scarico** (la condizione non è soddisfatta). *Senza* variabili condizionali, Giulia apre, vede scarico, richiude, riprova in continuazione: **busy waiting** e mutex tenuto inutilmente. *Con* `cond_wait`, Giulia "va a dormire" **restituendo la chiave** (rilascia il mutex); quando Matteo finisce di ricaricarlo invia `cond_signal` e Giulia si risveglia, **riacquisisce il mutex**, **verifica nuovamente** che il portatile sia pronto e lo prende. Niente busy waiting. *(slide 2025-2026)* Sincronizzazione solo quando la condizione è vera.

*Esercizio proposto dalla slide 2026-2027 (p. 73), da svolgere in C con Pthreads:* Giulia deve realizzare 5 presentazioni con il portatile condiviso, inizialmente scarico; Matteo deve ricaricarlo e intervenire soltanto quando è scarico; dopo ogni presentazione il portatile si scarica con probabilità del 50%. Richieste: `pthread_create()` e `pthread_join()`, un mutex per proteggere lo stato condiviso, variabili condizionali con `pthread_cond_wait()` e `pthread_cond_signal()`; **nessun busy waiting**, ed entrambi i thread devono terminare correttamente dopo la quinta presentazione.

| Chiamata | Descrizione |
|---|---|
| `pthread_cond_init` | Inizializza una variabile di condizione (associata a un mutex) |
| `pthread_cond_destroy` | Distrugge la variabile (solo se nessuno è in attesa) |
| `pthread_cond_wait` | Blocca il thread; rilascia il mutex durante l'attesa e lo riacquisisce al risveglio |
| `pthread_cond_signal` | Risveglia **un** thread in attesa (se nessuno attende, il segnale è perso) |
| `pthread_cond_broadcast` | Risveglia **tutti** i thread in attesa |
### Confronto: busy waiting vs pthread_cond_wait (produttore/consumatore)
Senza variabili condizionali il consumatore è costretto a usare **busy waiting**: rilascia il mutex, dorme un po' con `usleep`, riprende il mutex e ricontrolla la condizione — sprecando CPU e tenendo il mutex occupato inutilmente tra un ciclo e l'altro.
```c
/* versione con busy waiting — inefficiente */
pthread_mutex_lock(&mutex);
while (buffer == 0) {              /* controlla continuamente la condizione */
    pthread_mutex_unlock(&mutex);
    usleep(1000);                  /* ritardo per ridurre il busy waiting, non ottimale */
    pthread_mutex_lock(&mutex);
}
consume(buffer);
pthread_mutex_unlock(&mutex);
```
Con `pthread_cond_wait` il thread si sospende **senza consumare CPU**: rilascia il mutex e si mette in attesa in un'unica operazione **atomica**, e lo riacquisisce solo quando viene risvegliato dal produttore tramite `pthread_cond_signal`.
```c
/* versione con variabile condizionale — efficiente */
pthread_mutex_lock(&mutex);
while (buffer == 0) {
    /* attende finché il buffer non contiene almeno un elemento;
       pthread_cond_wait rilascia il mutex durante l'attesa
       e lo riacquisisce prima di ritornare */
    pthread_cond_wait(&cond, &mutex);
}
consume(buffer);
pthread_mutex_unlock(&mutex);
```

> [!warning] while, non if — risvegli spuri *(extra, non da slide: i risvegli spuri; l'uso di `while` e il motivo generale sono nelle slide 2026-2027)*
> La condizione va sempre verificata in un ciclo `while`, **mai con un semplice `if`**: secondo la slide 2026-2027 (pp. 47 e 51) al risveglio il thread deve ricontrollare la condizione, perché ricevere un segnale non garantisce che sia soddisfatta. Un ulteriore motivo: i **risvegli spuri** (*spurious wakeup*). Su alcune implementazioni POSIX `pthread_cond_wait` può tornare anche senza che nessuno abbia chiamato `signal`. Se si usa `if`, il thread procede erroneamente anche quando la condizione non è ancora vera. Il ciclo `while` ricontrolla la condizione a ogni risveglio, proteggendo da questo scenario.

Esempio completo nel codice del corso: `Esempi/6_thread_e_sincronizzazione/6.4_producer_consumer_pthread.c` (edizione 2025-2026: buffer di **un solo elemento**, con le variabili `condc` e `condp`). Nell'edizione 2026-2027 (`Esempi/6_thread_e_sincronizzazione_2026-2027/6.4_producer_consumer_pthread.c`, slide p. 51) il buffer è una **coda circolare di N posizioni** con due variabili condizionali, `not_full` e `not_empty`. Il produttore attende finché il buffer è pieno, inserisce e segnala `not_empty` (codice qui sotto). Nei due esempi 2026-2027 (6.2 semafori, 6.4 mutex+cond) il buffer circolare è identico e, con lo stesso `rand()`, producono la stessa sequenza (83, 86, 77, 15, …): cambia solo il meccanismo di attesa (`empty`/`full` contro `not_full`/`not_empty`). Entrambi eseguiti: terminano dopo 20 produzioni e 20 consumi.
```c
pthread_mutex_lock(&mutex);
while (count == N) {                       /* buffer pieno */
    pthread_cond_wait(&not_full, &mutex);  /* rilascia il mutex e attende */
}
insert_item();
print_buffer();
pthread_cond_signal(&not_empty);           /* un elemento è disponibile */
pthread_mutex_unlock(&mutex);
```
Il mutex garantisce l'accesso esclusivo al buffer e alle variabili che ne descrivono lo stato; `pthread_cond_wait` rilascia atomicamente il mutex e lo riacquisisce prima di ritornare, permettendo così al consumatore di prelevare un elemento e segnalare `not_full`.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Thread e Sincronizzazione|pari_dispari_insert_mutex.c]] — pattern `wait`/`signal` con `pthread_cond_wait` e somma progressiva.
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Mutex|TM2]] (buffer pari/dispari + somma progressiva) e [[Tracce d'Esame Pratiche#Thread — Mutex|TM1]] (controllo con variabile condizione).
> - **Esercizio della slide 2026-2027 (p. 73):** Giulia e Matteo con mutex e `pthread_cond_*` (nessun codice di soluzione nelle slide né negli esempi: da scrivere in autonomia).
## Monitor
La programmazione con semafori **richiede estrema attenzione**: un piccolo errore (es. invertire due `down` *(extra, non da slide)*) causa race condition o deadlock. **Brinch Hansen** e **Hoare** proposero un costrutto di sincronizzazione ad alto livello: il **monitor**.

Un **monitor** raggruppa procedure, variabili e strutture dati; i processi possono chiamarne le procedure ma **non** accedere ai dati interni. **Solo un processo alla volta** è attivo nel monitor: la **mutua esclusione è garantita dal compilatore** (non dal programmatore), riducendo gli errori.

Struttura (slide 2026-2027, p. 55): un monitor dichiara variabili (`integer i; condition c;`) e procedure (`procedure producer(); ... end; procedure consumer(); ... end;`) racchiuse tra `monitor` ed `end monitor`.

Per le attese, i monitor usano **variabili condizionali** con `wait` e `signal`. A differenza dei semafori, queste **non accumulano segnali**: se `signal` arriva e nessuno è in attesa, va perso. Linguaggi come **Java** supportano i monitor tramite metodi `synchronized`: nella slide 2026-2027 si precisa che un solo thread alla volta può eseguire metodi sincronizzati sullo stesso oggetto, grazie al monitor associato a quell'oggetto. Idea chiave: con mutex e variabili condizionali il programmatore gestisce **esplicitamente** la sincronizzazione; un monitor invece incapsula dati e operazioni e garantisce che una sola attività alla volta esegua le sue procedure.

> [!example] Produttore-consumatore con monitor
> ```c
> monitor ProdCons {
>     condition full, empty;
>     int count = 0;
>     void enter(int item) {
>         if(count == N) wait(full);
>         insert_item(item); count++;
>         if(count == 1) signal(empty);
>     }
>     void remove(int *item) {
>         if(count == 0) wait(empty);
>         *item = remove_item(); count--;
>         if(count == N-1) signal(full);
>     }
> }
> void producer(){ while(TRUE){ item = produce_item(); ProdCons.enter(item); } }
> void consumer(){ while(TRUE){ ProdCons.remove(&item); consume_item(item); } }
> ```
> L'accesso a `enter` e `remove` è **serializzato dal monitor**.
>
> Nel codice non compaiono `lock()` e `unlock()`: la slide 2026-2027 (pp. 56 e 59) chiede chi garantisca la mutua esclusione, e la risposta è il monitor stesso. `wait()` sospende il thread e **libera l'accesso al monitor**, permettendo ad altri thread di entrare; `signal()` risveglia un thread in attesa su quella condizione; due thread non possono mai eseguire contemporaneamente all'interno del monitor.

> [!info] Perché il monitor usa «if» e le pthread_cond usano «while» *(extra, non da slide: la spiegazione if/while; il lost wakeup nei monitor è nelle slide 2026-2027, pp. 59-60)*
> Nella [[#Variabili condizionali (pthread_cond)|sezione precedente]] abbiamo imposto sempre `while`, mai `if`, per difenderci dai risvegli spuri; qui invece il monitor usa `if(count == N) wait(full)` ed è **corretto**. La differenza sta nella **semantica della segnalazione**. Nel monitor classico (semantica di **Hoare**) `signal` **cede immediatamente** il controllo al processo risvegliato, che riprende l'esecuzione quando la condizione attesa è *certamente* vera: un solo controllo con `if` basta. Le **pthread_cond** seguono invece la semantica di **Mesa**: `signal` marca soltanto il thread come risvegliabile, ma questo riacquisisce il mutex *più tardi* — quando la condizione potrebbe essere tornata falsa — e può subire risvegli spuri; per questo serve il `while`, che ricontrolla la condizione a ogni risveglio. Stesso schema, garanzie diverse.

> [!info] sleep/wakeup vs wait/signal
> Differenza cruciale: `wait` e `signal` sono **protetti dalla mutua esclusione del monitor**. Un processo che entra in una procedura del monitor ne ha l'esclusività finché non chiama `wait`: non può quindi essere interrotto a metà e **non può perdere un segnale**, eliminando il problema del wakeup perso visto con `sleep/wakeup`. *(slide 2025-2026: formulazione con «non verrà interrotto, ad esempio dallo scheduler, finché non ha terminato di posizionarsi in uno stato di attesa»)*
>
> Formulazione della slide 2026-2027 (pp. 59-60): la soluzione ingenua `sleep/wakeup` controlla la condizione e poi si sospende, e se il `wakeup` arriva tra il controllo e la sospensione il risveglio va perso (**lost wakeup**). Nei monitor il thread controlla la condizione mentre detiene la mutua esclusione e `wait()` rilascia il controllo esclusivo e mette il thread in attesa **atomicamente**: il controllo protetto e l'attesa atomica eliminano la finestra critica.

**Monitor vs semafori**: i monitor sono **costrutti di linguaggio** (richiedono il supporto del compilatore, limitati ai linguaggi che li offrono); i semafori sono di **basso livello** ma utilizzabili ovunque: linguaggi come C e Pascal non hanno né monitor né semafori. *(slide 2025-2026)* I semafori si possono aggiungere con routine in assembly; conclusione: i semafori sono a basso livello, i monitor limitati ai linguaggi che li supportano. Nella slide 2026-2027 (p. 61) in C i semafori e le altre primitive sono disponibili tramite **librerie e API POSIX**; i semafori sono primitive esplicite, utilizzabili anche per coordinare **processi distinti** con i meccanismi appropriati; i monitor sono un'astrazione di livello più alto (incapsulamento dei dati, mutua esclusione e attesa condizionale) e anche in C si possono realizzare strutture analoghe con mutex e variabili condizionali POSIX. *(slide 2025-2026)* Entrambi funzionano con memoria condivisa, **non** in sistemi distribuiti (dove serve lo scambio di messaggi).

> [!info] Perché Java supporta i monitor e C no *(extra, non da slide: la spiegazione; che Java offra i monitor con `synchronized` è nelle slide)*
> I monitor delegano la **mutua esclusione al compilatore** (o al runtime), sottraendo il controllo diretto al programmatore — e quindi anche al sistema operativo. Questo crea una tensione: il SO vuole il pieno controllo della macchina, e un linguaggio che si rivolge **direttamente** al SO (come il **C**) non può imporre per conto suo politiche di accesso esclusivo. In **Java**, invece, tra il programma e il SO si interpone la **JVM** (Java Virtual Machine): è la JVM a fare da arbitro, garantendo che i metodi `synchronized` siano eseguiti in mutua esclusione prima di passare al SO. Lo strato intermedio è la ragione per cui i monitor sono implementabili in Java ma non direttamente in C.
## Scambio di messaggi
*(extra, non da slide)* *Sezione non presente nelle slide: la slide 6 elenca «Scambi di messaggi» solo nell'indice (p. 2) e non ha pagine dedicate.*
Per i sistemi **senza memoria condivisa** (es. distribuiti) la sincronizzazione usa lo **scambio di messaggi** con due primitive: `send(destinazione, messaggio)` e `receive(sorgente, messaggio)`. È il meccanismo alla base del modello [[02 - Concetti di Base e Strutture#Microkernel (client-server)|client-server]] e della comunicazione di rete.

> [!example] Produttore-consumatore con scambio di messaggi
> Si usano in totale **N messaggi**, analoghi agli N posti del buffer in memoria condivisa. All'avvio il **consumatore** invia al produttore N messaggi vuoti (i "gettoni" che segnalano posti disponibili). Il **produttore** esegue `receive` per prendere un messaggio vuoto, lo riempie con l'elemento prodotto e lo invia al consumatore con `send`. Il consumatore esegue `receive` per prelevare un messaggio pieno, lo elabora e rimanda un messaggio vuoto al produttore. Se il produttore è più veloce, esaurisce i messaggi vuoti e si blocca su `receive`; se il consumatore è più veloce, esaurisce i messaggi pieni e si blocca. La corrispondenza con il buffer condiviso è diretta: i messaggi vuoti contano i posti liberi, quelli pieni i posti occupati — gli stessi ruoli dei semafori `empty` e `full` (vedi [[#Semafori]]).

> [!info] Problemi progettuali specifici del modello a messaggi
> A differenza di semafori e monitor — che operano su **memoria condivisa** e non devono preoccuparsi di perdite o imposture — lo scambio di messaggi introduce problemi assenti negli altri modelli:
> - **Perdita di messaggi**: il canale di comunicazione (rete, [[#^ipc|IPC]]) può scartare messaggi; occorre un meccanismo di ritrasmissione.
> - **Acknowledgment (ACK)**: il mittente deve poter confermare che il destinatario ha ricevuto il messaggio; senza ACK non può distinguere tra «messaggio perso» e «risposta persa».
> - **Messaggi duplicati**: se l'ACK si perde, il mittente ritrasmette e il destinatario riceve lo stesso messaggio due volte; serve un numero di sequenza per scartare i duplicati.
> - **Autenticazione**: in un sistema distribuito occorre verificare di comunicare con il processo corretto e non con un impostore.
> Questi problemi non si pongono con semafori o monitor perché lì la comunicazione avviene **direttamente in memoria** — non c'è un canale fisico che possa perdere o alterare i dati.
## Barriere
Le **barriere** sincronizzano processi divisi in **fasi**: quando un processo raggiunge la barriera attende che **tutti** gli altri la raggiungano prima di proseguire. Utili nei calcoli paralleli (es. su matrici), dove non si può passare all'iterazione successiva finché tutti non hanno finito quella corrente. *(slide 2025-2026: l'attesa è indicata «ad esempio usando `pthread_join`»)*

Nella slide 2026-2027 (pp. 62-64) la barriera sincronizza più **thread** che svolgono un lavoro suddiviso in fasi: quando un thread la raggiunge attende gli altri, e all'arrivo dell'ultimo tutti proseguono alla fase successiva (figura: (a) i processi si avvicinano alla barriera; (b) tutti tranne uno sono bloccati; (c) all'arrivo dell'ultimo tutti passano). In Pthreads si usa `pthread_barrier_wait()`. Differenza: `pthread_join()` attende la **terminazione** di un thread, mentre la barriera sincronizza thread che devono **continuare a lavorare**.
## Problemi avanzati
### Inversione delle priorità
> [!quote] Definizione — Priority inversion
> Un thread ad **alta priorità** attende una risorsa bloccata da un thread a **bassa priorità**; un thread a **priorità media**, estraneo alla risorsa, impedisce a quello a bassa priorità di completare e rilasciare la risorsa. Il risultato: il thread ad alta priorità resta bloccato pur avendo la precedenza.

> [!example] Il Mars Pathfinder
> Il rover **Sojourner** (SO real-time) ebbe questo problema: un thread di bassa priorità deteneva un mutex su una risorsa condivisa; un thread di alta priorità attendeva; un thread di priorità media monopolizzava la CPU impedendo il rilascio. Il blocco del thread ad alta priorità causava continui **riavvii** del sistema. La NASA risolse con il **Priority Inheritance Protocol**: il thread a bassa priorità **eredita temporaneamente** la priorità di quello in attesa, completa, rilascia il mutex e torna alla priorità originale (vedi anche [[05 - Scheduling]]).

> [!info] Soluzioni all'inversione di priorità *(da slide: solo Priority Inheritance; le altre voci sono extra)*
> Le tre strategie principali per prevenire o limitare l'inversione sono:
> 1. **Priority Ceiling** *(extra, non da slide)* — si assegna una *priorità-tetto* al mutex stesso: il thread che acquisisce il mutex riceve automaticamente quella priorità. Finché nessun thread con priorità superiore al tetto deve acquisire quel mutex, l'inversione è impossibile per costruzione.
> 2. **Priority Inheritance** — il thread a bassa priorità che detiene il mutex **eredita temporaneamente** la priorità del thread ad alta priorità in attesa; completa la sezione critica, rilascia il mutex e torna alla propria priorità originale. È la soluzione adottata dalla NASA per il Mars Pathfinder.
> 3. **Random Boosting** *(extra, non da slide)* — aumenta in modo casuale la priorità di thread che detengono un mutex, con l'obiettivo probabilistico di sbloccare prima la risorsa contesa. Approccio meno deterministico degli altri due, usato in alcuni ambienti Windows.

> [!question] Domanda tipica d'esame
> **D:** Cos'è l'inversione delle priorità? Descrivi il caso del Mars Pathfinder e la soluzione adottata. **R:** L'inversione delle priorità si verifica quando un thread ad alta priorità attende una risorsa bloccata da un thread a bassa priorità, mentre un thread a priorità media — estraneo alla risorsa — monopolizza la CPU impedendo al thread a bassa priorità di completare e rilasciare il lock. Nel caso del rover Sojourner (Mars Pathfinder), questo causava continui riavvii del sistema real-time. La NASA risolse con il **Priority Inheritance Protocol**: il thread a bassa priorità eredita temporaneamente la priorità del thread in attesa, completa la sezione critica, rilascia il mutex e torna alla priorità originale.
### Read-Copy-Update (RCU)
*(slide 2025-2026: la slide 2026-2027 non tratta più RCU; il contenuto di questa sezione resta come nell'edizione precedente)*

*"I migliori lock sono quelli che non si usano."* L'obiettivo è permettere **accessi concorrenti senza lock**, evitando l'inconsistenza dei dati (es. calcolare la media di un array mentre lo si riordina). Principio: si **aggiorna** una struttura dati consentendo letture simultanee; i lettori vedono **o** la versione vecchia **o** la nuova, **mai un misto**.
- **Inserimento**: il nuovo nodo è preparato e reso visibile in modo **atomico** (collegato solo quando completamente inizializzato).
- **Rimozione**: i nodi (nella slide B e D) sono eliminati senza bisogno di lock: i lettori vedono o la nuova o la vecchia struttura, mai entrambe. Ma **quando liberarli?** Finché ci sono lettori non si può. Il nodo è quindi prima **scollegato**, poi liberato solo dopo il **grace period** — il tempo entro cui ogni thread esce almeno una volta dalla sezione critica (così nessuno detiene più un riferimento al nodo). L'operazione RCU determina il tempo massimo per trattenere un riferimento; si attende un periodo ≥ grace period prima di liberare la memoria. I thread nella sezione critica non si bloccano né vanno in sleep, perciò si aspetta un cambio di contesto.

RCU è poco comune nei processi utente ma **diffusissimo nei kernel**: il kernel **Linux** lo usa in rete, file system, driver e gestione della memoria.

---
**Argomento precedente:** [[03 - Processi e Thread]] · **Prossimo:** [[05 - Scheduling]] — algoritmi di scheduling per sistemi batch, interattivi e real-time.
