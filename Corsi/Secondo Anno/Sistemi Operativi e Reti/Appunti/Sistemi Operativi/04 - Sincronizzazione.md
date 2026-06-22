# 04 - Sincronizzazione
I processi (e i [[03 - Processi e Thread|thread]]) hanno bisogno di **comunicare** (condividere dati durante l'esecuzione) e di **sincronizzarsi** (tenere conto delle dipendenze ed evitare di intralciarsi). Questa nota tratta la **comunicazione tra processi (IPC)** e in particolare il problema della **mutua esclusione**, con le sue soluzioni: semafori, mutex, variabili condizionali e monitor.
## Il problema della concorrenza
Poiché i processi sono [[03 - Processi e Thread#Processi concorrenti|concorrenti]] e il SO non garantisce ordine né tempistica, l'accesso non coordinato a dati condivisi produce errori.
### Race condition
> [!quote] Definizione — Race condition
> Situazione in cui due o più processi accedono a dati condivisi e il risultato finale **dipende dall'ordine** preciso di esecuzione. La lettura/aggiornamento di un dato dovrebbe essere **atomica**: se non lo è, i processi "gareggiano" e possono giungere a conclusioni errate.

> [!example] Lo spooler di stampa
> Lo spooler ha una variabile `in` che indica la prossima posizione libera. Il processo A legge `in = 7`, ma viene **sospeso** prima di scrivere. B legge anch'esso `in = 7`, scrive il suo file in posizione 7 e imposta `in = 8`. Quando A riprende, scrive in posizione 7, **sovrascrivendo** il file di B. Un file di stampa va perso.
### Regioni critiche e requisiti
La parte di codice che accede alla risorsa condivisa è la **regione critica**. Una buona soluzione di mutua esclusione deve soddisfare **quattro requisiti**:
1. Due processi non possono trovarsi **contemporaneamente** nelle rispettive regioni critiche.
2. Non si possono fare **ipotesi** sulla velocità o sul numero di CPU.
3. Nessun processo **fuori** dalla propria regione critica può bloccarne altri.
4. Nessun processo deve **aspettare all'infinito** per entrare nella propria regione critica.
## Mutua esclusione con busy waiting
Le prime soluzioni tengono la CPU occupata mentre si attende: **busy waiting**.
### (Non) soluzioni elementari
- **Disabilitare gli interrupt**: impedisce la riallocazione della CPU, ma funziona **solo su CPU singola** ed è pericoloso lasciarlo fare ai processi utente.
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
### Il problema del busy waiting
Tutte queste soluzioni tengono la CPU **occupata ad attendere** (**spin lock**): è uno **spreco di risorse**. La soluzione è far sì che un processo in attesa **restituisca volontariamente la CPU** allo scheduler invece di "girare a vuoto".
## sleep e wakeup
Due primitive: `sleep()` blocca il processo chiamante (stato `BLOCKED`, CPU allo scheduler); `wakeup(process)` lo riporta a `READY`.

> [!example] Produttore-consumatore con sleep/wakeup
> Due processi condividono un buffer di dimensione fissa e un contatore `count`. Il **produttore** inserisce e dorme se il buffer è pieno (`count == N`); il **consumatore** preleva e dorme se è vuoto (`count == 0`). Ciascuno risveglia l'altro al momento giusto.
> ```c
> void producer(void){
>     while(TRUE){ item = produce_item();
>         if(count == N) sleep();
>         insert_item(item); count++;
>         if(count == 1) wakeup(cons); } }
> void consumer(void){
>     while(TRUE){
>         if(count == 0) sleep();
>         item = remove_item(); count--;
>         if(count == N-1) wakeup(prod);
>         consume_item(item); } }
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
### Semaforo o mutex?
- **Finalità**: il **mutex** garantisce la mutua esclusione (una risorsa, un thread alla volta); il **semaforo** controlla l'accesso a una risorsa ma serve anche per la **sincronizzazione** tra thread (es. produttore/consumatore).
- **Semantica**: il mutex ha una semantica di **proprietà** (solo chi l'ha acquisito può rilasciarlo); il semaforo **no** (qualsiasi thread può fare `up`/`down`).
- **Regola pratica**: per la sola esclusione mutua → **mutex** (più semplice e prevedibile); per coordinare più thread o risorse con N istanze → **semaforo**.
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

> [!info] sleep/wakeup vs wait/signal
> Differenza cruciale: `wait` e `signal` sono **protetti dalla mutua esclusione del monitor**. Un processo che entra in una procedura del monitor ne ha l'esclusività finché non chiama `wait`: non può quindi essere interrotto a metà e **non può perdere un segnale**, eliminando il problema del wakeup perso visto con `sleep/wakeup`.

**Monitor vs semafori**: i monitor sono **costrutti di linguaggio** (richiedono il supporto del compilatore, limitati ai linguaggi che li offrono); i semafori sono di **basso livello** ma utilizzabili ovunque (anche via routine assembly). Entrambi funzionano con memoria condivisa, **non** in sistemi distribuiti (dove serve lo scambio di messaggi).
## Scambio di messaggi
Per i sistemi **senza memoria condivisa** (es. distribuiti) la sincronizzazione usa lo **scambio di messaggi** con due primitive: `send(destinazione, messaggio)` e `receive(sorgente, messaggio)`. È il meccanismo alla base del modello [[02 - Concetti di Base e Strutture#Microkernel (client-server)|client-server]] e della comunicazione di rete.
## Barriere
Le **barriere** sincronizzano processi divisi in **fasi**: quando un processo raggiunge la barriera attende che **tutti** gli altri la raggiungano prima di proseguire. Utili nei calcoli paralleli (es. su matrici), dove non si può passare all'iterazione successiva finché tutti non hanno finito quella corrente.
## Problemi avanzati
### Inversione delle priorità
> [!quote] Definizione — Priority inversion
> Un thread ad **alta priorità** attende una risorsa bloccata da un thread a **bassa priorità**; un thread a **priorità media**, estraneo alla risorsa, impedisce a quello a bassa priorità di completare e rilasciare la risorsa. Il risultato: il thread ad alta priorità resta bloccato pur avendo la precedenza.

> [!example] Il Mars Pathfinder
> Il rover **Sojourner** (SO real-time) ebbe questo problema: un thread di bassa priorità deteneva un mutex su una risorsa condivisa; un thread di alta priorità attendeva; un thread di priorità media monopolizzava la CPU impedendo il rilascio. Il blocco del thread ad alta priorità causava continui **riavvii** del sistema. La NASA risolse con il **Priority Inheritance Protocol**: il thread a bassa priorità **eredita temporaneamente** la priorità di quello in attesa, completa, rilascia il mutex e torna alla priorità originale (vedi anche [[05 - Scheduling]]).
### Read-Copy-Update (RCU)
*"I migliori lock sono quelli che non si usano."* L'obiettivo è permettere **accessi concorrenti senza lock**, evitando l'inconsistenza dei dati. Principio: si **aggiorna** una struttura dati consentendo letture simultanee; i lettori vedono **o** la versione vecchia **o** la nuova, **mai un misto**.
- **Inserimento**: il nuovo nodo è preparato e reso visibile in modo **atomico** (collegato solo quando completamente inizializzato).
- **Rimozione**: il nodo è prima **scollegato**, poi liberato solo dopo il **grace period** — il tempo entro cui ogni thread esce almeno una volta dalla sezione critica (così nessuno detiene più un riferimento al nodo).

RCU è poco comune nei processi utente ma **diffusissimo nei kernel**: il kernel **Linux** lo usa in rete, file system, driver e gestione della memoria.

---
**Argomento precedente:** [[03 - Processi e Thread]] · **Prossimo:** [[05 - Scheduling]] — algoritmi di scheduling per sistemi batch, interattivi e real-time.
