In questo capitolo si tratterà la gestione della memoria da parte del **sistema operativo** seguendo quella che è la **gerarchia delle memorie**, dalle più veloci e costose alle più lente ed economiche. 

Il compito del sistema operativo è di organizzarle (esclusa la cache) per eseguire in maniera efficiente tutti i propri compiti. La parte che esegue questo compito è chiamata **gestore della memoria**.

(Pagine riassunte: 1)
## 3.1 - Nessuna astrazione della memoria
Supponendo un'organizzazione senza astrazione di memoria, un sistema può essere strutturato in tre modalità:
- Può trovarsi *in fondo alla memoria* (fig 3.1 a) nella **RAM** (Random Access Memory).
- Può trovarsi *in cima alla memoria* (fig 3.1 b) nella **ROM** (Read Only Memory).
- Può trovarsi come nel primo caso, ma con i *driver dei dispositivi* in cima alla memoria nella ROM.

Il primo e l'ultimo metodo sono molto rischiosi: un programma utente scritto male potrebbe eliminare o sovrascrivere il sistema operativo, perdendo così l'accesso all'intera memoria.

Inoltre, generalmente non è possibile eseguire più di un programma alla volta. Si potrebbe usare la divisione in thread, ma ciò non permetterebbe l'esecuzione di due programmi non relazionati, a causa della mancanza di astrazione, che implica la mancanza ulteriore di un'astrazione dei possibili thread thread.
#### Esecuzione di molteplici programmi senza astrazione della memoria
Esiste un metodo con cui i creatori dei computer IBM hanno risolto il problema dell'esecuzione dei programmi. ù

Sapendo che generalmente il sistema operativo esegue un programma, lo copia in un file (**swapping**) e passa al successivo, hanno implementato una suddivisione fisica della memoria in blocchi di 2 KB con una chiave di protezione di 4 bit (custodita in registri speciali nella CPU) che specifica l'accesso alla memoria. Il sistema operativo intercettava ogni tentativo di accesso alla memoria con un codice di protezione diverso dal **PSW** (Program Status Word, anch'esso con una chiave di 4 bit), impedendo ai programmi di accedere ai blocchi di memoria assegnati ad altri programmi.

Tuttavia, un problema sorge quando due programmi vengono eseguiti in maniera sequenziale e sovrapposta (il primo programma parte, attende, è ancora in esecuzione e parte il secondo). Quando i due programmi hanno delle locazioni predisposte, essi sono ancora legati alle **chiamate fisiche alla memoria**, generando errori.

Altre implementazioni per risolvere questo problema includono la **rilocazione statica**, che consiste nell'aggiungere n bit all'indirizzo di ogni istruzione. Tuttavia, questo sistema funziona solo in ambiti predefiniti, come elettrodomestici (lavastoviglie, lavatrici), dove il programma conosce già cosa eseguire.

(Pagine riassunte: 3.5)
## 3.2 - Un'astrazione della memoria: gli spazi degli indirizzi
Come detto precedentemente, senza implementazione hardware o un rigoroso controllo nell'esecuzione dei programmi utente, lavorare con la memoria fisica crea enormi rischi per i sistemi operativi. Per questo motivo sono state sviluppate diverse implementazioni per mitigare questi rischi.
### 3.2.1 - Nozione di spazio degli indirizzi
Abbiamo visto l'implementazione non funzionante nel sottocapitolo precedente, quindi come implementare al meglio questa memoria? La prima soluzione consiste nello **spazio degli indirizzi**, ovvero l'insieme degli indirizzi che un processo può usare (simile ai numeri di telefono, agli indirizzi IPv4, ecc.).

Questo concetto non è limitato alla memoria, ma è generalizzabile, indicizzabile e strutturabile a piacimento; anche i domini .com, ad esempio, hanno uno spazio di indirizzamento.
#### Registri base e registri limite
Una soluzione per gestire la memoria in modo sicuro è l'utilizzo di un **registro base** e un **registro limite**, che segnano rispettivamente l'inizio e la fine della memoria assegnata a un programma. Quando un programma consulta la memoria, l'indirizzo effettivo viene calcolato sommando il registro base all'indirizzo specificato nell'istruzione. Ad esempio, se un programma ha un jump to 28 e il registro base è 4096, l'indirizzo effettivo sarà 28 + 4096.

Se un'istruzione tenta di accedere a un indirizzo al di fuori dell'intervallo definito dal registro base e dal registro limite, viene generato un errore e l'operazione viene bloccata. Questo meccanismo non solo protegge le aree di memoria dei diversi programmi da accessi non autorizzati, ma consente anche l'allocazione sequenziale dei programmi in memoria, migliorando la gestione e la protezione degli indirizzi.

Sebbene efficace, questa soluzione comporta un lieve impatto sulle prestazioni, poiché ogni calcolo dell'indirizzo richiede un'operazione addizionale per sommare il registro base.

(Pagine riassunte: 2.5)
### 3.2.2 - Swapping
Lo **swapping** consiste nel suddividere due stati di processi: *dormiente* e *attivo*. Un processo attivo risiede nella memoria volatile e rimane in esecuzione, mentre un processo dormiente viene trasferito nella *swap*, un'area di memoria fisica che conserva i programmi non più eseguiti ma pronti per essere rieseguiti. 

Una soluzione ancora più avanzata per migliorare questo metodo è la **memoria virtuale**, che permette ai programmi di essere eseguiti anche quando sono solo parzialmente presenti in memoria.

Quando lo swapping genera molti spazi vuoti (a causa della de-allocazione per inserire nella swap), è possibile eliminarli tramite la **memory compaction**. Tuttavia, questa operazione è molto costosa per la CPU. Inoltre, i programmi con allocazione dinamica possono avere difficoltà a trovare spazio aggiuntivo intorno al loro indirizzo. Per questo motivo, generalmente si alloca più spazio del necessario se si prevede che il programma possa richiedere più memoria, mettendo in swap il processo adiacente o spostando il processo principale.

Esiste un metodo più specifico per processi con due segmenti: un segmento heap per le variabili allocate e rilasciate dinamicamente e un segmento stack per le variabili locali e gli indirizzi di ritorno. Il segmento heap si espande verso l'alto, mentre lo stack si espande verso il basso. Quando non c'è più spazio disponibile, non invadono i processi adiacenti; invece, si cerca un nuovo spazio più grande o si termina il processo.

(Pagine riassunte: 2.25)
### 3.2.3 - Gestione della memoria libera
Nella gestione della memoria ci sono molte variabili che identificano una soluzione possibile, ma l'organo che deve controllarle è il sistema operativo. Per questo motivo esistono due tipi di gestione che analizzeremo che sono i seguenti.
#### Gestione della memoria con bitmap
La gestione della memoria tramite **bitmap** associa a ogni elemento della bitmap un'area di memoria. Se un'area è occupata, l'elemento corrispondente della bitmap avrà valore 1, altrimenti sarà 0. Ogni elemento della bitmap mappa un intervallo specifico di memoria.

Il vantaggio della bitmap è che permette di *gestire la memoria a blocchi*, consentendo di allocare blocchi specifici e di verificare se sono occupati o liberi. Tuttavia, se la bitmap mappa blocchi molto piccoli (ad esempio 4 byte), pur sembrando piccola (1/32 della memoria), dovrà leggere comunque elemento per elemento questa, e nel caso peggiore l'intera bitmap. Al contrario, se la bitmap mappa blocchi molto grandi (come 4 KB), ci sarà una maggiore perdita di spazio a causa della scarsa precisione nell'allocazione.
#### Gestione della memoria con liste
In questa metodologia, la memoria è divisa in sequenze (liste) che contengono: al primo indice H se la casella è vuota o P se è occupata; al secondo indice l'indirizzo di partenza; al terzo indice lo spazio del segmento; e all'ultimo un puntatore al segmento successivo. Una buona implementazione prevede un secondo collegamento alla lista precedente per facilitare il movimento.

La gestione della memoria è semplificata: ad esempio, se abbiamo in ordine un processo A seguito da B e poi da un segmento vuoto, al termine di B il segmento vuoto ingloberà lo spazio di B. È quindi facile controllare i processi vicini e vedere se è possibile unire i segmenti.

Grazie a questa struttura sequenziale della memoria, è facile applicare vari algoritmi:
- **First fit** cerca la prima area di memoria disponibile che sia abbastanza grande.
- **Next fit**, una variante del First fit, riprende la ricerca dal punto in cui era stata interrotta, risultando leggermente meno efficiente del First fit.
- **Best fit** legge tutti gli spazi e sceglie il più adatto, tendendo a occupare spazi stretti e risultando molto più lento dei precedenti.
- **Worst fit** fa l'opposto del Best fit per evitare di occupare spazi inutili e stretti, ma cercare lo spazio più grande lo rende anch'esso inefficiente.
- **Quick fit** mantiene liste separate per le dimensioni più comuni. Cerca prima nella lista della dimensione richiesta e, se non trova un blocco libero, cerca in una lista di dimensioni superiori. È ottimo per la ricerca e la semplicità, ma può creare frammentazione della memoria e la gestione di molte liste può diventare complessa, richiedendo memoria aggiuntiva.

Alcune buone implementazioni includono ordinare le liste per dimensione per ottimizzare First fit e Best fit, rendendoli più veloci. Un'altra è mantenere le informazioni delle liste all'interno dello spazio stesso, con le prime parole di ogni spazio che contengono le informazioni e i puntatori.

(Pagine riassunte: 3)
###### Esempio pratico (facoltativo)
Supponiamo di avere un sistema Quick Fit con liste per blocchi di 8, 16 e 32 byte. Ecco come potrebbe avvenire una serie di operazioni di allocazione e deallocazione:

1. **Allocazione di 8 byte**:
    
    - Il sistema controlla la lista di blocchi da 8 byte.
    - Trova un blocco libero e lo assegna.
2. **Allocazione di 20 byte**:
    
    - Non c'è una lista per 20 byte, quindi il sistema cerca in una lista di blocchi più grande, ad esempio 32 byte.
    - Trova un blocco da 32 byte, lo assegna e segna i 12 byte rimanenti come non utilizzati (potrebbe generare frammentazione interna).
3. **Deallocazione di 8 byte**:
    
    - Il blocco rilasciato viene reinserito nella lista di blocchi da 8 byte.
4. **Allocazione di 16 byte**:
    
    - Il sistema controlla la lista di blocchi da 16 byte.
    - Trova un blocco libero e lo assegna.
## 3.3 - Memoria virtuale
Con l'avanzare del tempo si vedeva come i sistemi a registri base e limite non potevano funzionare; le implementazioni fatte erano molto complesse e comunque non potevano reggere l'aumento esponenziale del software.

Lo swapping era una soluzione parziale al problema del poco spazio di memoria, serviva una gestione più efficiente della memoria; pochi programmatori si impegnavano nel ottimizzare i propri programmi e non riuscivano comunque ad implementarlo al meglio.

Per questo si arrivò alla coniazione della **memoria virtuale**: ogni programma ha il suo spazio suddiviso in **pagine**, che sono intervalli di indirizzi contigui. L'implementazione è simile ad una generalizzazione della precedente (registri base e limite) ma ora la vedremo al meglio

(Pagine riassunte: 1.25)
### 3.3.1 - Paginazione
Uno dei sistemi più utilizzati di memoria virtuale è chiamato **paginazione**. Su qualsiasi computer, i programmi referenziano un insieme di indirizzi di memoria. Gli **indirizzi virtuali** possono essere generati tramite indicizzazione, registri base o altre tecniche, ma nella memoria virtuale le chiamate vengono generalmente passate direttamente alla **MMU** (Memory Management Unit), che mappa gli indirizzi virtuali su quelli fisici.

Gli indirizzi virtuali mascherano la memoria fisica effettiva gestita dalla MMU, permettendo l'esecuzione di programmi da 64 KB su memorie da 32 KB caricando solo le pagine utilizzate.

Lo spazio virtuale è diviso in intervalli definiti di memoria chiamati **pagine** (virtuali). Le unità fisiche corrispondenti sono invece chiamate **frame** o **page frame**. Tuttavia, questa suddivisione non risolve la differenza di spazio tra le pagine presenti e i frame presenti. Come fare allora?

Quando un programma fa riferimento a un'area di memoria non esistente, l'MMU rileva che la pagina non è mappata e causa una **trap** della CPU verso il sistema operativo, chiamata **page fault**. L'OS prende un frame poco usato, lo carica sul disco liberandolo, lo mappa con il nuovo indirizzo non mappato e riesegue l'istruzione che era in trap.

(Pagine riassunte: 3.5)
### 3.3.2 - Tabelle delle pagine
Il modo di tradurre un indirizzo virtuale in uno fisico avviene tramite la **tabella delle pagine**. Gli indirizzi virtuali arrivano divisi in *numero di pagina* e *offset della pagina*; trovato il corrispondente numero di pagina nella tabella, esso si traduce in un nuovo indirizzo fisico che ha come page number il corrispondente nella tabella e come offset quello presente nell'indirizzo virtuale. 
#### Struttura di una voce della tabella delle pagine
Analizziamo ora le voci della tabella delle pagine:
- I primi bit corrispondono al **numero del frame**, specificando dove la pagina sarà fisicamente situata.
- Il bit *presente/assente* indica se la pagina è effettivamente esistente (1) o se la pagina virtuale non è replicabile sulla memoria fisica (0), causando un *page fault* in quest'ultimo caso.
- I bit di **protezione** specificano le operazioni eseguibili, come lettura/scrittura (1) o sola lettura (0), ma possono avere più modalità.
- Il bit **modificato** (o *dirty bit*) e il bit **referenziato** tengono traccia dell'uso della pagina. Quando una pagina viene scritta, il bit modificato viene impostato a 1. Se il bit modificato è 1, l'OS lo copia sul disco e poi lo pulisce; se è 0, può direttamente rimuovere la pagina. Il bit referenziato indica se la pagina è stata utilizzata: 1 se precedentemente utilizzata, 0 se inutilizzata. Sono utili per le scelte del sistema operativo.
- L'ultimo bit consente di *disabilitare il caching* per programmi che supportano la scrittura in cache dei dispositivi.

(Pagine riassunte: 2)
### 3.3.3 - Velocizzare la paginazione
I principi fondamentali per la velocità del sistema precedentemente trattato sono i seguenti:
- Il mappaggio dall'indirizzo virtuale a quello fisico deve essere veloce.
- Lo spazio virtuale degli indirizzi è grande quindi la tabella sarà grande di conseguenza. Inoltre, ogni programma ha con se una tabella privata degli indirizzi.

Nei sistemi moderni c'è sempre più bisogno di indirizzi grandi, come a 32 bit che mappano milioni di pagine o a 64 bit che nemmeno possiamo immaginare. La velocità richiesta è fondamentale per avere un sistema senza colli di bottiglia, vediamo allora diverse soluzioni.
#### Translation lookaside buffer
Analizziamo ora come ottimizzare questa metodologia di gestione della memoria. La tabella delle pagine risiede nella memoria, il che influisce significativamente sulle performance poiché, ad ogni accesso, la CPU deve consultare la tabella delle pagine e poi accedere alla memoria, dimezzando di fatto le performance.

Una soluzione è equipaggiare i PC con un hardware che mappa gli indirizzi virtuali su quelli fisici senza consultare direttamente la tabella delle pagine; questo dispositivo è chiamato **TLB** (Translation Lookaside Buffer) o **memoria associativa**. Si trova all'interno della MMU e contiene un numero ridotto di voci (solitamente 8, ma può arrivare a 256 o più), memorizzando le mappature come nella tabella delle pagine, ma con l'aggiunta del numero di pagina. La CPU, infatti, tende a richiedere accesso alle stesse poche pagine ripetutamente.

Quando la CPU fa una richiesta, la MMU interroga il TLB tramite un hardware specializzato:
- Se il TLB contiene un riscontro valido e non protetto, il frame viene preso direttamente dal TLB.
- Se il riscontro è valido ma protetto, si genera un errore di protezione.
- Se non trova un riscontro, la MMU rileva un **TLB miss** e consulta la tabella delle pagine, sostituendo una delle voci del TLB con la nuova mappatura prelevata. Successivamente, se la stessa pagina verrà richiesta di nuovo, si avrà un **TLB hit**, con l'operazione eseguita correttamente e rapidamente.
#### Gestione software del TLB
Quando la MMU non trova una voce nel TLB, non interroga direttamente la tabella delle pagine, ma genera un errore e passa il compito al sistema operativo. L'OS trova la pagina, sostituisce una voce nel TLB con la nuova mappatura e riavvia l'istruzione. Questo processo avviene in poche istruzioni poiché i TLB miss sono molto più frequenti di un page fault.

Un approccio efficace, sebbene generico, è permettere al sistema operativo di *anticipare* alcune sostituzioni, prevedendo quali pagine potrebbero essere richieste più frequentemente.

Per evitare ulteriori errori durante un TLB miss mentre si cerca nella tabella delle pagine, viene mantenuta una *cache software estesa* delle voci TLB in una posizione fissa che l'OS controlla prima di accedere al TLB.

Esistono due tipi di TLB miss:
- **TLB soft-miss**: quando una pagina non è nel TLB ma è presente nella tabella delle pagine, quindi il TLB viene aggiornato.
- **TLB hard-miss**: quando una pagina non è nel TLB né nella memoria, causando un page fault, che è molto più lento.

Una miss può essere sia soft che hard, o una combinazione delle due. Se un programma tenta di accedere a un indirizzo non valido, non è necessario aggiornare il TLB poiché si registra come un **errore di segmentazione**, causato da un errore del programmatore.

(Pagine riassunte: 3.5)
### 3.3.4 - Tabelle delle pagine per grandi memorie
Un problema del TLB può essere lavorare con indirizzi virtuali molto grandi.
#### Tabelle delle pagine multilivello (fatto con GPT da rivedere in quanto difficile)
Consideriamo le tabelle delle pagine multilivello. Un esempio è un indirizzo virtuale a 32 bit diviso in PT1 (10 bit), PT2 (10 bit) e Offset (12 bit), con pagine da 4 KB. Questo metodo evita di mantenere tutte le tabelle in memoria, mettendo da parte quelle non necessarie. Un processo con 12 MB di spazio indirizzi ha un grande spazio vuoto tra i dati e lo stack.

Con una tabella delle pagine a due livelli, l'indirizzo virtuale viene usato per indicizzare nella tabella di livello superiore (PT1) e poi nella tabella di livello inferiore (PT2). Ad esempio, l'indirizzo 0x00403004 ha PT1=1, PT2=2 e Offset=4. La MMU usa PT1 per trovare la tabella inferiore e PT2 per trovare il frame della pagina. Se la pagina non è in memoria, si verifica un page fault.

Questo sistema riduce il numero di tabelle necessarie in memoria. Le voci inutilizzate nella tabella di livello superiore hanno bit Presente/Assente a 0, causando un page fault se vengono accedute. La tabella delle pagine a due livelli può essere estesa a tre o più livelli per maggiore flessibilità.

Processori come l'Intel 80386 usavano tabelle a due livelli per indirizzare 4 GB di memoria. Il Pentium Pro ha introdotto un terzo livello per indirizzare oltre 4 GB. Con il supporto ai 64 bit, si è aggiunto un quarto livello, consentendo di indirizzare fino a 256 TB di memoria. Alcuni nuovi processori supportano un quinto livello per estendere gli indirizzi fino a 57 bit, permettendo di indirizzare fino a 128 PB di memoria, rendendo però più costosi i page table walk.
#### Tabelle delle pagine invertite
In questo tipo di progettazione, c'è una sola voce per frame nella memoria reale, riducendo il numero totale di voci. Ogni voce tiene traccia di ciò che è memorizzato nel frame.

Il problema sorge quando lo spazio degli indirizzi virtuali è molto più grande della memoria fisica. Quando il processo \( n \) referenzia la pagina virtuale \( p \), l'hardware deve cercare la voce \((n, p)\) nella tabella delle pagine invertite.

Le ottimizzazioni includono l'uso del TLB, che filtra parte delle chiamate, e di una funzione hash per l'indirizzo virtuale. Se la hash table ha tante voci quanti sono i frame in memoria, la catena media avrà solo una voce, ottimizzando notevolmente il mappaggio.

(Pagine riassunte: 3.5)
## 3.4 - Algoritmi di sostituzione delle pagine


(Pagine riassunte: 0.75)
### 3.4.1 - L'algoritmo ottimale di sostituzione delle pagine


(Pagine riassunte: 0.5)
### 3.4.2 - Not recently used (NRU)


(Pagine riassunte: 1)
### 3.4.3 - First-in, first-out (FIFO)


(Pagine riassunte: 0.5)
### 3.4.4 - Seconda chance


(Pagine riassunte: 0.5)
### 3.4.5 - Clock

### 3.4.6 - Least recently used (LRU)


(Pagine riassunte: 1)
### 3.4.7 - (Saltato)
### 3.4.8 - Working set


(Pagine riassunte: 3.75)
### 3.4.9 - WSClock


(Pagine riassunte: 1.75)
### 3.4.10 - Riepilogo degli algoritmi di sostituzione delle pagine


(Pagine riassunte: 0.75)
## 3.5 - Problemi di progettazione dei sistemi di paginazione

### 3.5.1 - Politiche di allocazioni globali e locali


(Pagine riassunte: 2.5)
### 3.5.2 - Controllo del carico


(Pagine riassunte: 0.5)
### 3.5.3 - Dimensione dello spazio


(Pagine riassunte: 1.75)
### 3.5.4 - Istruzioni separate e spazi di dati


(Pagine riassunte: 0.75)
### 3.5.5 - Pagine condivise


(Pagine riassunte: 1.5)
### 3.5.6 - Librerie condivise


(Pagine riassunte: 2)
### 3.5.7 - File mappati


(Pagine riassunte: 0.5)
### 3.5.8 - Politica di ripulitura


(Pagine riassunte: 0.5)
### 3.5.9 - Interfaccia della memoria virtuale


(Pagine riassunte:  0.75)
## 3.6 - Problemi di implementazione
### 3.6.1 - Il sistema operativo e la paginazione


(Pagine riassunte: 1)
### 3.6.2 - Gestione dei page fault


(Pagine riassunte: 1)
### 3.6.3 - Backup delle istruzioni


(Pagine riassunte: 1)
### 3.6.4 - Bloccare le pagine in memoria


(Pagine riassunte: 0.5)
### 3.6.5 - Memoria secondaria


(Pagine riassunte: 1.75)
### 3.6.6 - Separazione fra politica e meccanismo


(Pagine riassunte: 1.25)
## 3.7 - Segmentazione


(Pagine riassunte: 2.75)
### 3.7.1 - Implementazione della segmentazione pura


(Pagine riassunte: 0.75)
### 3.7.2 - Segmentazione con la paginazione: MULTICS


(Pagine riassunte: 4)
### 3.7.3 - Segmentazione con paginazione: l'Intel x86


(Pagine riassunte: 4.5)
## 3.8 - Stato della ricerca sulla gestione della memoria

(Pagine riassunte: 1)