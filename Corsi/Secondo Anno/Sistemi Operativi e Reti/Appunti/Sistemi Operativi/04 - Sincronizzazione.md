# Sincronizzazione
I processi (e i [[03 - Processi e Thread|thread]]) raramente vivono isolati: hanno bisogno di **comunicare** — scambiarsi dati durante l'esecuzione — e di **sincronizzarsi**, cioè coordinarsi per rispettare le dipendenze reciproche ed evitare di intralciarsi. L'insieme dei meccanismi con cui il sistema operativo consente ai processi di scambiarsi informazioni e coordinare le proprie azioni prende il nome di **comunicazione tra processi** (*Inter-Process Communication*, **IPC**). Questa nota affronta il nodo centrale dell'IPC con memoria condivisa — la **mutua esclusione**, cioè garantire che un solo processo alla volta entri nella porzione di codice che usa una risorsa condivisa — e ne presenta le soluzioni in ordine di astrazione crescente: semafori, mutex, variabili condizionali e monitor. ^ipc

> [!info] Per il laboratorio
> Gli esercizi di questa parte si scrivono in **C** con le **POSIX Threads** (`pthread`). Se segui l'ordine delle lezioni conviene affrontare prima [[10 - Programmazione C e Concorrente]] (compilazione, `pthread_create`/`pthread_join`) e [[09 - Linux e BASH]] (shell e strumenti del terminale): nelle slide il laboratorio in C precede la teoria della sincronizzazione, mentre in queste note l'ordine segue il libro di testo (Tanenbaum).
## Il problema della concorrenza
Poiché i processi sono [[03 - Processi e Thread#Processi concorrenti|concorrenti]] e il SO non garantisce ordine né tempistica, l'accesso non coordinato a dati condivisi produce errori.
### Race condition
> [!quote] Definizione — Race condition
> Situazione in cui due o più processi accedono a dati condivisi e il risultato finale **dipende dall'ordine** preciso di esecuzione. La lettura/aggiornamento di un dato dovrebbe essere **atomica**: se non lo è, i processi "gareggiano" e possono giungere a conclusioni errate.

> [!example] Lo spooler di stampa
> Lo *spooler di stampa* è il servizio che mette in coda i documenti da stampare depositandoli in un'apposita **directory di spooling**; più processi vi accodano file contemporaneamente, ed è questa scrittura concorrente a generare la corsa. Una variabile condivisa `in` indica la prossima posizione libera nella coda. Il processo A legge `in = 7`, ma viene **sospeso** prima di usarla; B legge a sua volta `in = 7`, scrive il proprio file in posizione 7 e aggiorna `in = 8`. Quando A riprende, scrive anch'esso in posizione 7, **sovrascrivendo** il file di B: un lavoro di stampa va perso. L'esito finale dipende dall'**ordine di esecuzione** dei due processi — ecco la race condition.

> [!question] Domanda tipica d'esame
> **D:** Cos'è una race condition e perché è problematica? **R:** Una race condition è una situazione in cui due o più processi accedono a dati condivisi e il risultato finale dipende dall'ordine preciso di esecuzione. È problematica perché produce risultati errati e non deterministici: nell'esempio dello spooler di stampa, due processi leggono la stessa posizione libera e uno sovrascrive l'altro, causando la perdita di un lavoro di stampa.

### Regioni critiche e requisiti
La parte di codice in cui un processo accede a una risorsa condivisa è la **regione critica** (*critical region*). Concettualmente ogni processo attraversa quattro fasi in sequenza: la **sezione di ingresso** (*entry*), in cui chiede il permesso di entrare; la **regione critica** vera e propria; la **sezione di uscita** (*exit*), che segnala l'avvenuta uscita; e la **sezione non critica** (*remainder*), tutto il resto del lavoro che non tocca risorse condivise. Il problema della mutua esclusione consiste nel progettare le sezioni di ingresso e di uscita in modo che due regioni critiche non si sovrappongano mai. Una buona soluzione deve soddisfare **quattro requisiti**:
1. Due processi non possono trovarsi **contemporaneamente** nelle rispettive regioni critiche.
2. Non si possono fare **ipotesi** sulla velocità o sul numero di CPU.
3. Nessun processo **fuori** dalla propria regione critica può bloccarne altri.
4. Nessun processo deve **aspettare all'infinito** per entrare nella propria regione critica.

> [!question] Domanda tipica d'esame
> **D:** Elenca i quattro requisiti di una buona soluzione alla mutua esclusione. **R:** (1) Due processi non possono trovarsi contemporaneamente nelle rispettive regioni critiche; (2) non si possono fare ipotesi sulla velocità o sul numero di CPU; (3) nessun processo fuori dalla propria regione critica può bloccarne altri; (4) nessun processo deve aspettare all'infinito per entrare nella propria regione critica.

## Mutua esclusione con busy waiting
Le prime soluzioni tengono la CPU occupata mentre si attende: **busy waiting**.
### (Non) soluzioni elementari
- **Disabilitare gli interrupt**: impedisce la riallocazione della CPU, ma funziona **solo su CPU singola** ed è pericoloso lasciarlo fare ai processi utente. Su sistemi **multicore**, disabilitare gli interrupt di un core non offre garanzie: gli altri core possono comunque accedere alla memoria condivisa e interferire.
- **Variabili di blocco** (lock 0/1): proteggono la regione critica, ma la "corsa" si sposta semplicemente **sulla variabile di blocco** (leggere-e-impostare non è atomico).
### Alternanza rigorosa
Una variabile `turn` stabilisce di chi è il turno; ciascuno aspetta in `while(turn != me)`. **Non** è una buona soluzione: viola il requisito 3 — un processo fuori dalla regione critica può **bloccarne** un altro (non si può entrare due volte di fila).
### Algoritmo di Peterson
Combina la variabile `turn` con un array `interested[]`: prima di entrare, un processo segnala l'interesse e scrive `turn` con il **proprio** indice, poi attende **finché `turn` resta suo e l'altro è interessato**. Se entrambi tentano insieme, l'**ultimo** a scrivere `turn` è quello che aspetta, mentre l'altro entra: niente attesa reciproca.
```c
#define N 2                    /* numero di processi */
int turn;                      /* a chi tocca? */
int interested[N];             /* inizialmente tutti 0 (FALSE) */

void enter_region(int process) {        /* process è 0 o 1 */
    int other = 1 - process;            /* l'altro processo */
    interested[process] = TRUE;         /* mostra interesse */
    turn = process;                     /* imposta il flag */
    while (turn == process && interested[other] == TRUE) ;  /* attesa */
}
void leave_region(int process) {
    interested[process] = FALSE;        /* esce dalla regione critica */
}
```

> [!question] Domanda tipica d'esame
> **D:** Perché l'alternanza rigorosa non è una soluzione accettabile alla mutua esclusione? Come la risolve l'algoritmo di Peterson? **R:** L'alternanza rigorosa viola il requisito 3: un processo fermo fuori dalla propria regione critica può bloccare l'altro impedendogli di entrarvi due volte di fila (non si può entrare due volte consecutive). L'algoritmo di Peterson combina la variabile `turn` con l'array `interested[]`: prima di entrare ogni processo segnala il proprio interesse e scrive il proprio indice in `turn`; se entrambi tentano insieme, l'ultimo a scrivere `turn` attende mentre l'altro entra, eliminando l'attesa reciproca senza violare nessuno dei quattro requisiti.

### TSL e XCHG
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
Due primitive: `sleep()` blocca il processo chiamante (stato `BLOCKED`, CPU allo scheduler); `wakeup(process)` lo riporta a `READY`.

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
> Il consumatore potrebbe essere risvegliato **un attimo prima** di addormentarsi: legge `count == 0`, ma prima di chiamare `sleep()` viene interrotto; il produttore inserisce e invia `wakeup`, che però va **perso** perché il consumatore non dorme ancora. Poi il consumatore dorme… e nessuno lo risveglierà più. Un **bit di attesa del wakeup** (accumulatore di risvegli) è un *workaround*, ma non risolve sempre il problema.
## Semafori
Introdotti da **E. W. Dijkstra (1965)** per contare e gestire i wakeup. Un semaforo è un intero ≥ 0 con due operazioni **atomiche** ("indivisibili"):
- **`down`** (P): se il valore è > 0 lo decrementa e prosegue; se è 0 il processo si **blocca** in una coda di attesa associata al semaforo ("va a dormire").
- **`up`** (V): incrementa il valore; se c'erano processi in coda ne **risveglia** uno.

> [!example] Produttore-consumatore con semafori
> Tre semafori: `mutex` (accesso esclusivo al buffer), `empty` (posti liberi), `full` (posti occupati).
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
> `mutex` **serializza** l'accesso al buffer; `empty` blocca il produttore quando il buffer è pieno, `full` blocca il consumatore quando è vuoto. Codice in `code/6_thread_e_sincronizzazione/6.2_producer_consumer_semaphore.c`.

> [!example] Deadlock da inversione dei down — errore classico da esame
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
> Se nuovi lettori continuano ad arrivare mentre uno scrittore attende, lo scrittore potrebbe **non ottenere mai** l'accesso (blocco perpetuo). Una soluzione mette i nuovi lettori **in coda dietro** gli scrittori in attesa: riduce la concorrenza ma evita la starvation. Codice in `code/6_thread_e_sincronizzazione/6.3_reader_writer_semaphore.c`.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Thread e Sincronizzazione|prod_cons_sem.c]] (produttore–consumatore con la tripla `mutex`/`full`/`empty`) e [[Indice degli Esercizi#Thread e Sincronizzazione|readers_writers_pari_dispari.c]] (lettori–scrittori con priorità ai lettori).
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Semafori|TS1]] (produttore–consumatore) e [[Tracce d'Esame Pratiche#Thread — Semafori|TS3]] (uno scrittore, cinque lettori).
## Mutex
Un **mutex** è una versione **esplicita e semplificata** del semaforo, usata per la sola mutua esclusione quando **non serve contare**. Ha due stati: **locked** e **unlocked** (basta un bit). Due procedure: `mutex_lock` e `mutex_unlock`.

Quando un thread vuole entrare nella regione critica chiama `mutex_lock`: se il mutex è *unlocked* entra; se è *locked* attende **senza busy waiting**, cedendo la CPU con `thread_yield`. Al termine chiama `mutex_unlock`.

> [!info] Dettagli
> I mutex possono essere implementati in user space con istruzioni atomiche come **TSL** o **XCHG** (vedi [[5 - Livello di architettura dell'insieme d'istruzioni]]). Alcune librerie offrono `mutex_trylock`, che tenta il lock o restituisce errore **senza bloccare**. I mutex sono efficaci quando i thread condividono lo spazio di indirizzi.
### Mutex in Pthreads
| Chiamata | Descrizione |
|---|---|
| `pthread_mutex_init` | Inizializza un mutex |
| `pthread_mutex_destroy` | Distrugge un mutex (solo se non detenuto) |
| `pthread_mutex_lock` | Blocca il mutex (sospende se già occupato) |
| `pthread_mutex_trylock` | Tenta il lock senza sospendere (errore se occupato) |
| `pthread_mutex_unlock` | Sblocca (solo il thread che detiene il lock) |

**`lock` vs `trylock`**: `lock` quando l'accesso esclusivo è necessario e si **può attendere** in coda; `trylock` quando si vuole **solo tentare** e proseguire con altro se il lock è occupato (utile per evitare deadlock).

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
Il mutex da solo **non** consente di attendere efficientemente una **condizione specifica** (es. "il buffer non è vuoto"): senza altri strumenti il thread dovrebbe fare busy waiting su un `while`. Le **variabili condizionali** (`pthread_cond`) aggiungono la possibilità di sospendersi finché un evento non si verifica, **senza consumare CPU**.

Un thread chiama `pthread_cond_wait(&cond, &mutex)`: **rilascia atomicamente il mutex** e si addormenta; quando un altro thread chiama `pthread_cond_signal`, il thread si risveglia e **riacquisisce il mutex**.

> [!example] Giulia, Matteo e il portatile condiviso
> Il portatile sta in un armadietto chiuso a chiave (il **mutex**); a volte è **scarico** (la condizione non è soddisfatta). *Senza* variabili condizionali, Giulia apre, vede scarico, richiude, riprova in continuazione: **busy waiting** e mutex tenuto inutilmente. *Con* `cond_wait`, Giulia "va a dormire" **restituendo la chiave** (rilascia il mutex); quando Matteo finisce di ricaricarlo invia `cond_signal` e Giulia si risveglia, **riacquisisce il mutex** e prende il portatile. Niente busy waiting, sincronizzazione solo quando la condizione è vera.

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
while (buffer == 0) {              /* attesa passiva finché il buffer non è pieno */
    pthread_cond_wait(&cond, &mutex);
}
consume(buffer);
pthread_mutex_unlock(&mutex);
```

> [!warning] while, non if — risvegli spuri
> La condizione va sempre verificata in un ciclo `while`, **mai con un semplice `if`**. Il motivo: i **risvegli spuri** (*spurious wakeup*). Su alcune implementazioni POSIX `pthread_cond_wait` può tornare anche senza che nessuno abbia chiamato `signal`. Se si usa `if`, il thread procede erroneamente anche quando la condizione non è ancora vera. Il ciclo `while` ricontrolla la condizione a ogni risveglio, proteggendo da questo scenario.

Esempio completo nel codice del corso: `code/6_thread_e_sincronizzazione/6.4_producer_consumer_pthread.c`.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Thread e Sincronizzazione|pari_dispari_insert_mutex.c]] — pattern `wait`/`signal` con `pthread_cond_wait` e somma progressiva.
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Mutex|TM2]] (buffer pari/dispari + somma progressiva) e [[Tracce d'Esame Pratiche#Thread — Mutex|TM1]] (controllo con variabile condizione).
## Monitor
La programmazione con semafori **richiede estrema attenzione**: un piccolo errore (es. invertire due `down`) causa race condition o deadlock. **Brinch Hansen** e **Hoare** proposero un costrutto di sincronizzazione ad alto livello: il **monitor**.

Un **monitor** raggruppa procedure, variabili e strutture dati; i processi possono chiamarne le procedure ma **non** accedere ai dati interni. **Solo un processo alla volta** è attivo nel monitor: la **mutua esclusione è garantita dal compilatore** (non dal programmatore), riducendo gli errori.

Per le attese, i monitor usano **variabili condizionali** con `wait` e `signal`. A differenza dei semafori, queste **non accumulano segnali**: se `signal` arriva e nessuno è in attesa, va perso. Linguaggi come **Java** supportano i monitor tramite metodi `synchronized`.

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

> [!info] Perché il monitor usa «if» e le pthread_cond usano «while»
> Nella [[#Variabili condizionali (pthread_cond)|sezione precedente]] abbiamo imposto sempre `while`, mai `if`, per difenderci dai risvegli spuri; qui invece il monitor usa `if(count == N) wait(full)` ed è **corretto**. La differenza sta nella **semantica della segnalazione**. Nel monitor classico (semantica di **Hoare**) `signal` **cede immediatamente** il controllo al processo risvegliato, che riprende l'esecuzione quando la condizione attesa è *certamente* vera: un solo controllo con `if` basta. Le **pthread_cond** seguono invece la semantica di **Mesa**: `signal` marca soltanto il thread come risvegliabile, ma questo riacquisisce il mutex *più tardi* — quando la condizione potrebbe essere tornata falsa — e può subire risvegli spuri; per questo serve il `while`, che ricontrolla la condizione a ogni risveglio. Stesso schema, garanzie diverse.

> [!info] sleep/wakeup vs wait/signal
> Differenza cruciale: `wait` e `signal` sono **protetti dalla mutua esclusione del monitor**. Un processo che entra in una procedura del monitor ne ha l'esclusività finché non chiama `wait`: non può quindi essere interrotto a metà e **non può perdere un segnale**, eliminando il problema del wakeup perso visto con `sleep/wakeup`.

**Monitor vs semafori**: i monitor sono **costrutti di linguaggio** (richiedono il supporto del compilatore, limitati ai linguaggi che li offrono); i semafori sono di **basso livello** ma utilizzabili ovunque (anche via routine assembly). Entrambi funzionano con memoria condivisa, **non** in sistemi distribuiti (dove serve lo scambio di messaggi).

> [!info] Perché Java supporta i monitor e C no
> I monitor delegano la **mutua esclusione al compilatore** (o al runtime), sottraendo il controllo diretto al programmatore — e quindi anche al sistema operativo. Questo crea una tensione: il SO vuole il pieno controllo della macchina, e un linguaggio che si rivolge **direttamente** al SO (come il **C**) non può imporre per conto suo politiche di accesso esclusivo. In **Java**, invece, tra il programma e il SO si interpone la **JVM** (Java Virtual Machine): è la JVM a fare da arbitro, garantendo che i metodi `synchronized` siano eseguiti in mutua esclusione prima di passare al SO. Lo strato intermedio è la ragione per cui i monitor sono implementabili in Java ma non direttamente in C.
## Scambio di messaggi
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
Le **barriere** sincronizzano processi divisi in **fasi**: quando un processo raggiunge la barriera attende che **tutti** gli altri la raggiungano prima di proseguire. Utili nei calcoli paralleli (es. su matrici), dove non si può passare all'iterazione successiva finché tutti non hanno finito quella corrente.
## Problemi avanzati
### Inversione delle priorità
> [!quote] Definizione — Priority inversion
> Un thread ad **alta priorità** attende una risorsa bloccata da un thread a **bassa priorità**; un thread a **priorità media**, estraneo alla risorsa, impedisce a quello a bassa priorità di completare e rilasciare la risorsa. Il risultato: il thread ad alta priorità resta bloccato pur avendo la precedenza.

> [!example] Il Mars Pathfinder
> Il rover **Sojourner** (SO real-time) ebbe questo problema: un thread di bassa priorità deteneva un mutex su una risorsa condivisa; un thread di alta priorità attendeva; un thread di priorità media monopolizzava la CPU impedendo il rilascio. Il blocco del thread ad alta priorità causava continui **riavvii** del sistema. La NASA risolse con il **Priority Inheritance Protocol**: il thread a bassa priorità **eredita temporaneamente** la priorità di quello in attesa, completa, rilascia il mutex e torna alla priorità originale (vedi anche [[05 - Scheduling]]).

> [!info] Soluzioni all'inversione di priorità
> Le tre strategie principali per prevenire o limitare l'inversione sono:
> 1. **Priority Ceiling** *(extra, non da slide)* — si assegna una *priorità-tetto* al mutex stesso: il thread che acquisisce il mutex riceve automaticamente quella priorità. Finché nessun thread con priorità superiore al tetto deve acquisire quel mutex, l'inversione è impossibile per costruzione.
> 2. **Priority Inheritance** — il thread a bassa priorità che detiene il mutex **eredita temporaneamente** la priorità del thread ad alta priorità in attesa; completa la sezione critica, rilascia il mutex e torna alla propria priorità originale. È la soluzione adottata dalla NASA per il Mars Pathfinder.
> 3. **Random Boosting** *(extra, non da slide)* — aumenta in modo casuale la priorità di thread che detengono un mutex, con l'obiettivo probabilistico di sbloccare prima la risorsa contesa. Approccio meno deterministico degli altri due, usato in alcuni ambienti Windows.

> [!question] Domanda tipica d'esame
> **D:** Cos'è l'inversione delle priorità? Descrivi il caso del Mars Pathfinder e la soluzione adottata. **R:** L'inversione delle priorità si verifica quando un thread ad alta priorità attende una risorsa bloccata da un thread a bassa priorità, mentre un thread a priorità media — estraneo alla risorsa — monopolizza la CPU impedendo al thread a bassa priorità di completare e rilasciare il lock. Nel caso del rover Sojourner (Mars Pathfinder), questo causava continui riavvii del sistema real-time. La NASA risolse con il **Priority Inheritance Protocol**: il thread a bassa priorità eredita temporaneamente la priorità del thread in attesa, completa la sezione critica, rilascia il mutex e torna alla priorità originale.

### Read-Copy-Update (RCU)
*"I migliori lock sono quelli che non si usano."* L'obiettivo è permettere **accessi concorrenti senza lock**, evitando l'inconsistenza dei dati. Principio: si **aggiorna** una struttura dati consentendo letture simultanee; i lettori vedono **o** la versione vecchia **o** la nuova, **mai un misto**.
- **Inserimento**: il nuovo nodo è preparato e reso visibile in modo **atomico** (collegato solo quando completamente inizializzato).
- **Rimozione**: il nodo è prima **scollegato**, poi liberato solo dopo il **grace period** — il tempo entro cui ogni thread esce almeno una volta dalla sezione critica (così nessuno detiene più un riferimento al nodo).

RCU è poco comune nei processi utente ma **diffusissimo nei kernel**: il kernel **Linux** lo usa in rete, file system, driver e gestione della memoria.

---
**Argomento precedente:** [[03 - Processi e Thread]] · **Prossimo:** [[05 - Scheduling]] — algoritmi di scheduling per sistemi batch, interattivi e real-time.
