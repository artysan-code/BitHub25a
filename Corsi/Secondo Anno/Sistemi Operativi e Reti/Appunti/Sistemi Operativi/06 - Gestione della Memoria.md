# Gestione della Memoria
Il **gestore della memoria** (*memory manager*) è la parte del sistema operativo che astrae la [gerarchia fisica della memoria](#Gerarchia%20della%20memoria%20e%20ruolo%20del%20gestore) in un modello utilizzabile, tiene traccia di quali zone sono occupate o libere, alloca memoria ai processi che la richiedono e la libera quando non serve più. Tutta questa lezione riguarda la **memoria principale (RAM)**; lo storage di massa (dischi/SSD) e il [[07 - File System|file system]] sono trattati a parte.
> [!quote] Legge di Parkinson (parafrasi)
> *I programmi si espandono fino a riempire tutta la memoria disponibile.* Per quanta RAM si aggiunga, il software cresce più in fretta: un laptop con 32 GB ha 20 000 volte la memoria dell'IBM 7094 (il più grande computer del mondo nei primi anni '60)… ed è sempre pieno.

Il percorso storico-concettuale di questa lezione va dal modello più semplice a quello moderno: **nessuna astrazione → astrazione con spazi degli indirizzi → memoria virtuale paginata**.
## Gerarchia della memoria e ruolo del gestore
Il **desiderio** dell'utente sarebbe una memoria privata, grande, veloce, persistente e a basso costo. La realtà tecnologica è diversa, e si risolve con una **gerarchia**: dalla memoria veloce e costosa (pochi registri/cache) a quella lenta, economica e capiente (RAM → SSD → disco → USB). La CPU e i livelli di cache sono descritti nel dettaglio in Architettura (vedi callout finale [Collegamenti con Architettura](#Collegamenti%20con%20Architettura)).
Compito del SO è **astrarre** questa gerarchia e gestirla: il gestore della memoria traccia l'uso, alloca e libera spazio per i processi.
## Memoria senza astrazione
Il modello più semplice è l'**uso diretto della memoria fisica**: il programma vede solo indirizzi fisici. Con un'istruzione come `MOV REGISTER1,1000` il contenuto della cella fisica `1000` finisce in `REGISTER1`.
> [!warning] Il problema della memoria fisica nuda
> Senza astrazione **un programma può interferire con un altro** scrivendo nei suoi indirizzi, e un applicativo utente può addirittura **cancellare il sistema operativo**. È impossibile far convivere in sicurezza più programmi.
### Monoprogrammazione
Con un solo programma per volta in memoria, esistono tre organizzazioni storiche:
- **OS in RAM** in basso, *user program* sopra — mainframe e minicomputer (ormai desueto).
- **OS in ROM** in alto — tipico dei [[01 - Introduzione ai Sistemi Operativi#^embedded|sistemi embedded]].
- **OS + driver in ROM, resto in RAM** — primi PC: la ROM con i driver di base si chiamava **BIOS** (*Basic Input Output System*), es. MS-DOS.
### Multiprogrammazione senza astrazione
Si possono eseguire più programmi anche senza astrazione, usando lo **swapping**.
> [!quote] Definizione — Swapping
> Salvataggio dell'intero contenuto della memoria di un processo in un file su memoria **non volatile**, e successivo caricamento del programma seguente. Sposta interi processi tra RAM e disco/SSD.

L'approccio *naive* di caricare più programmi consecutivamente in memoria fisica **non funziona**: due programmi che iniziano con `JMP 24` e `JMP 28` usano **indirizzi assoluti**; il secondo, caricato dopo il primo, salta erroneamente dentro le istruzioni del primo, causando errori e crash. È il sintomo che serve una **astrazione dell'indirizzo**.
## Astrazione della memoria: spazi degli indirizzi
La soluzione è separare e proteggere i programmi tramite l'astrazione dello **spazio degli indirizzi**.
> [!quote] Definizione — Spazio degli indirizzi (*address space*)
> Insieme **unico** di indirizzi che un programma può usare per indirizzare la memoria. È indipendente da quello degli altri processi e rappresenta una forma astratta di memoria: ogni processo "crede" di avere la propria memoria privata.
### Registri base e limite
Un'implementazione hardware semplice usa due registri speciali presenti in molte CPU:
- **Registro base**: indirizzo fisico di **inizio** del programma in memoria → realizza la **rilocazione dinamica** (ogni indirizzo generato viene sommato alla base).
- **Registro limite**: **lunghezza** del programma → applica la **protezione**.

Ad ogni riferimento alla memoria `MOV Reg1, Addr` l'hardware esegue due controlli:
- `IF (Addr > LIMIT)` → **NOT OKAY** (fuori dai limiti del programma).
- `IF (BASE + Addr < BASE)` → **NOT OKAY** (overflow dell'indirizzo).

| | Pro | Contro |
|---|---|---|
| **Registri base/limite** | Spazio degli indirizzi separato e protetto per ogni processo | Una somma e un confronto **a ogni accesso** → può essere lento |
## Swapping e gestione della memoria libera
Un computer medio all'avvio ha **50–100 processi** o più (Photoshop può chiedere ~1 GB solo per avviarsi): la memoria fisica necessaria spesso eccede quella disponibile. Due strategie per il sovraccarico:
- **Swapping dei processi**: sposta interi processi tra RAM e memoria non volatile; i processi inattivi sono archiviati su disco/SSD.
- **Memoria virtuale**: esegue i programmi anche se solo **parzialmente** presenti in RAM (vedi [Memoria virtuale](#Memoria%20virtuale)).
### Frammentazione e compattazione
Con partizioni dinamiche, lo swapping continuo di processi di taglie diverse lascia **buchi** sparsi: è la **frammentazione** della memoria. Serve la **compattazione** (spostare i processi per unire lo spazio libero), operazione **estremamente lenta**.
### Crescita dei processi
I segmenti di **dati** e di **stack** possono crescere durante l'esecuzione. Si lascia perciò *room for growth* attorno a ciascun processo (stack che cresce verso il basso, dati verso l'alto). In caso di *out of memory* le opzioni sono: «**uccidere**» il processo, **trasferirlo** altrove, oppure fare **swapping**.
### Bitmap vs liste collegate
Per tenere traccia della memoria (es. in blocchi da 4 byte) ci sono due metodi; il problema riguarda non solo la memoria, ma anche risorse come il [[07 - File System|file system]].
- **Bitmap**: un bit per blocco indica se è allocato. Trovare un buco di *k* blocchi richiede una **scansione** (lenta).
- **Lista collegata** di segmenti processo/buco (P/H, con indirizzo di partenza e lunghezza): trade-off tra allocazione lenta e deallocazione lenta. Tenere i buchi **ordinati per indirizzo** permette una rapida **coalescenza** (fusione di buchi adiacenti). In pratica si usa spesso una **doppia** linked list, che facilita il controllo del segmento precedente e l'aggiornamento dei puntatori alla terminazione di un processo.
> [!example] I quattro casi di coalescenza (doppia lista)
> Quando un processo X termina e libera la propria zona di memoria, si possono presentare quattro configurazioni con i segmenti adiacenti nella lista (A = processo a sinistra, B = processo a destra, H = buco):
> - **(a)** A — X — B: nessun buco adiacente → si sostituisce X con un **singolo buco**.
> - **(b)** A — X — H: buco a destra di X → X e H vengono **uniti in un buco più grande**.
> - **(c)** H — X — B: buco a sinistra di X → H e X vengono **uniti in un buco più grande**.
> - **(d)** H — X — H: buchi su entrambi i lati → tutti e tre i segmenti **confluiscono in un unico buco**.
### Algoritmi di allocazione
Scelto un buco abbastanza grande per una richiesta:
- **First Fit**: il **primo** buco disponibile. Il più semplice (usato in MINIX3).
- **Next Fit**: il **successivo** buco a partire dall'ultima posizione. In pratica più lento del First Fit.
- **Best Fit**: il buco **più adeguato** (più piccolo che basta). Tende a generare frammentazione (lascia buchi minuscoli).
- **Worst Fit**: il buco **meno adeguato** (il più grande). Prestazioni scadenti in pratica.
- **Quick Fit**: mantiene liste separate per le dimensioni più richieste. Veloce, ma **scarsa coalescenza**.
- **Buddy Allocation** (Linux): migliora la coalescenza (vedi sotto).
### Buddy allocation (Linux)
Linux alloca le pagine principalmente con l'algoritmo di **Buddy Memory Allocation** (descritto al Cap. 10.4 del libro).
> [!example] Funzionamento del buddy
> La memoria parte come un singolo blocco contiguo (es. 64 pagine). A ogni richiesta la dimensione è **arrotondata a una potenza di 2** e il blocco viene **diviso a metà** ripetutamente finché si ottiene un pezzo della taglia giusta, che viene allocato. Quando due blocchi **adiacenti** provenienti dalla stessa divisione vengono liberati, vengono **uniti** (coalescenza) per riformare il blocco più grande.
### SLAB allocator
Il buddy può causare **frammentazione interna** (una richiesta di 65 pagine ne fa allocare 128). Lo **SLAB allocator** di Linux risolve prendendo blocchi grandi tramite il buddy e ritagliandoli in unità più piccole.
> [!quote] Definizione — Slab
> Il kernel crea e distrugge di continuo piccoli oggetti di tipo e dimensione specifici. Nello slab allocation la memoria è divisa in blocchi detti **slab**, ulteriormente suddivisi in **chunk** di dimensione uniforme adatti a ospitare un oggetto di un certo tipo. Uno slab può essere **pieno**, **parzialmente pieno** o **vuoto**.

Quando un oggetto viene deallocato non torna subito al sistema: resta nella **cache**, così una nuova istanza dello stesso tipo è riallocata rapidamente **senza overhead di inizializzazione**. Lo slab tiene un puntatore all'inizio della memoria, l'indice del prossimo slot libero e un array `bufctl` di indici dei prossimi oggetti liberi.
> [!example] Struttura interna di uno slab
> Un singolo slab in memoria è disposto così:
> ```
> [ Slab descriptor | bufctl array | Object_0 | Free slot | Object_2 | Object_3 | Object_4 | Free slot ]
> ```
> Il **slab descriptor** contiene il puntatore all'inizio e l'indice del prossimo slot libero. Il **bufctl array** è un array di indici che, per ogni slot, indica il successivo slot libero (forma una lista linkata implicita nei liberi). Gli slot "Free slot" corrispondono a oggetti deallocati ma non ancora restituiti al sistema.

> [!info] Livelli di allocazione della memoria in Linux
> Linux organizza l'allocazione della memoria del kernel in tre livelli sovrapposti:
> 1. **Buddy allocator** (base): gestisce blocchi di pagine fisiche contigue. Causa **frammentazione interna**: una richiesta di 65 pagine porta ad allocarne 128 (potenza di 2 successiva).
> 2. **vmalloc** e **Slab allocator** (sopra il Buddy): entrambi usano il Buddy per ottenere blocchi grandi e li ritagliano in unità più piccole. `vmalloc` gestisce regioni virtualmente contigue ma non necessariamente fisicamente contigue; lo **Slab** gestisce oggetti di tipo uniforme con riuso della cache.
> 3. **`kmalloc()`** (sopra lo Slab): interfaccia generale del kernel per allocazioni di piccole dimensioni; internamente usa lo Slab allocator.
## Memoria virtuale
Il problema dei programmi **più grandi della memoria** disponibile esiste fin dalle origini dell'informatica (anni '60), specie in ambito scientifico e ingegneristico. La prima soluzione furono gli **overlay**: piccoli segmenti del programma di cui viene caricato in memoria solo quello **necessario**, mentre gli overlay successivi lo **sovrascrivono** (o coesistono), scambiandosi tra memoria e disco. Il limite era che il **programmatore** doveva suddividere *manualmente* il programma in overlay — un lavoro tedioso e soggetto a errori: da qui la motivazione storica della **memoria virtuale**, che automatizza questo meccanismo.

La **memoria virtuale** estende l'idea dei registri base e limite. Ogni programma ha il proprio spazio degli indirizzi suddiviso in **pagine** (intervalli contigui di indirizzi); **non tutte** devono stare contemporaneamente in memoria fisica. L'hardware mappa le pagine effettivamente presenti; se una pagina manca, interviene il sistema operativo.
> [!quote] Definizione — Memoria virtuale
> Crea per il processo l'**illusione** di uno spazio di indirizzi ampio (es. indicizzabile con 48 bit) detto **spazio di indirizzi virtuale**, mentre la RAM, molto più limitata, è la **memoria fisica**. La **MMU** (*Memory Management Unit*) traduce gli indirizzi virtuali (usati dal processo) in indirizzi fisici (inviati alla memoria).

La maggior parte dei sistemi moderni usa il **paging** (paginazione); un'alternativa storica con unità di dimensione variabile è la [segmentazione](#La%20segmentazione), oggi meno comune.
### Paginazione (paging)
> [!quote] Definizione — Paginazione
> Si dividono memoria fisica e virtuale in **pagine** di dimensione fissa (es. 4096 byte = 4 KB) e si traducono le **pagine virtuali** in **pagine fisiche** (dette **frame**).

Se 16 pagine virtuali sono mappate su 8 frame, alcune pagine restano **non mappate** (contrassegnate con `X`). Se un programma riferisce una pagina non mappata si verifica un **page fault**: il SO assegna un frame (eventualmente spostando su disco un frame poco usato — *quale?* vedi [Algoritmi di sostituzione](#Algoritmi%20di%20sostituzione%20delle%20pagine)), carica la pagina richiesta e aggiorna la mappa della MMU.
> [!example] Esempio — `MOV REG,32780`
> L'indirizzo `32780` riferisce la **pagina virtuale 8** all'offset 12: infatti $32780 - 2^{15}\,(32768) = 12$. Se la pagina non è mappata, il SO può sostituire un frame, spostando il precedente su disco e facendo puntare al nuovo, accedendo all'indirizzo $4108 = 4096 + 12$. Il page fault avviene nello spazio kernel durante il **trap** eseguito dal SO.
### La MMU e la page table
> [!quote] Definizione — Page Table (tabella delle pagine)
> Struttura che dà la **relazione** tra indirizzi virtuali e fisici: il numero di pagina virtuale è usato come **indice** nella tabella per ottenere il numero di **frame**.

Internamente la MMU spezza l'**indirizzo virtuale** in due campi. Esempio con indirizzo virtuale `8196` = `0010 000000000100` su un sistema a 16 pagine da 4 KB:
- **Numero di pagina**: bit alti (qui 4 bit → 16 pagine). Indice nella page table.
- **Offset**: bit bassi (qui 12 bit → indirizza i 4096 byte interni a ogni frame). Copiato **direttamente** dall'input all'output.

Negli esempi si usano indirizzi a 16 bit per chiarezza. I PC reali usano 32 o 64 bit:
- **32 bit, pagine 4 KB**: 12 bit di offset → tabella di $2^{(32-12)} = 2^{20} = 1\,048\,576$ voci. Fattibile anche con pochi GB di RAM.
- **64 bit, pagine 4 KB**: richiederebbe $2^{52}$ voci (impraticabile). In realtà i sistemi a 64 bit usano **48 bit** → 256 TB bastano e avanzano; gli altri bit sono riservati per il futuro.
### Voce della page table
Ogni voce contiene il numero del frame (es. 12 bit per pagine da 4 KB) più diversi **bit di controllo**:
- **Presente/Assente**: indica se la pagina virtuale è **in memoria**.
- **Protezione**: tipi di accesso consentiti (lettura, scrittura, esecuzione).
- **Supervisor**: se la pagina è accessibile solo al SO o anche ai programmi utente.
- **Modificato (M)**, detto *dirty bit*: si attiva quando la pagina viene **scritta** (serve a sapere se va riscritta su disco).
- **Riferimento (R)**, detto *accessed bit*: si attiva ogni volta che si **accede** alla pagina.
- **Caching disabled**: disabilita la cache per quella pagina.

L'indirizzo in memoria della tabella delle pagine «del processo» è scritto nel registro **PTBR** (*Page Table Base Register*). I bit **M** e **R** sono fondamentali per gli [algoritmi di sostituzione](#Algoritmi%20di%20sostituzione%20delle%20pagine).
> [!info] Dove memorizzare la tabella delle pagine?
> Due opzioni principali, con un netto trade-off:
> - **Registri hardware** (un registro per ogni pagina): la tabella è caricata in un insieme di registri dedicati all'avvio del processo. Semplice e senza accessi aggiuntivi alla RAM; ma l'insieme di registri è costoso, e con tabelle grandi il **cambio di contesto** richiede di ricaricare tutti i registri → molto lento.
> - **Memoria principale (RAM) + PTBR**: la tabella risiede in RAM e il registro **PTBR** punta all'inizio della tabella del processo corrente. Il cambio di contesto è rapido (si aggiorna solo PTBR); svantaggio: ogni accesso alla memoria virtuale richiede **due accessi RAM** (uno per leggere la voce della tabella, uno per il dato vero e proprio) → mappatura più lenta senza TLB.
### TLB (Translation Lookaside Buffer)
La paginazione ha un problema di prestazioni: ogni istruzione richiede un accesso alla memoria per prelevarla **più** un accesso alla page table → **raddoppio** degli accessi, prestazioni dimezzate. Se un'istruzione impiega 1 ns, la ricerca nella tabella dovrebbe stare sotto 0,2 ns per non creare colli di bottiglia.
La soluzione sfrutta la **località di riferimento**: i programmi fanno molti riferimenti a un **piccolo** numero di pagine.
> [!quote] Definizione — TLB (*Translation Lookaside Buffer*)
> Dispositivo hardware (cache) che mappa indirizzi virtuali in fisici **senza** passare dalla tabella delle pagine, riducendo gli accessi in memoria. Ha poche voci (es. 8–256), ciascuna con numero di pagina virtuale, bit modificato, codice di protezione e frame fisico.

Funzionamento: alla richiesta di un indirizzo la MMU controlla **prima** il TLB; se la voce è presente e valida (*TLB hit*), il frame è preso direttamente; se non c'è (**TLB miss**) si fa la ricerca normale nella page table e la voce trovata **rimpiazza** una voce del TLB. Le modifiche ai permessi di una pagina richiedono di **invalidare o aggiornare** la voce corrispondente nel TLB per garantire coerenza.
Su alcune architetture **RISC** (SPARC, MIPS, HP PA) il TLB è gestito **via software**: un TLB miss non innesca una ricerca automatica della MMU, ma genera un *errore di TLB* che il SO gestisce cercando la pagina, aggiornando il TLB e riavviando l'istruzione.
### Page table multi-livello
Uno spazio di indirizzi virtuali molto grande porterebbe a una tabella enorme e a uno **spreco di memoria** (e con 48 bit ci sono 64 miliardi di pagine!). La soluzione è la **tabella delle pagine multi-livello**, «attraversata» (*walked*) dalla MMU.
- **x86 a 2 livelli**: registro **CR3** che punta al vertice della gerarchia; indirizzo a 32 bit diviso in `PT1` (10 bit) + `PT2` (10 bit) + offset (12 bit).
- **x86-64 a 4 livelli**: **PGD** (Page Global Directory) → **PUD** (Page Upper Directory) → **PMD** (Page Mid-level Directory) → **PTE** (Page Table Entry). I campi sono 9+9+9+9 bit + 12 di offset: $2^9 \times 2^9 \times 2^9 \times 2^9 \times 2^{12} = 2^{48}$ byte = 256 TB. Il registro **CR3** punta al PGD.
### Tipi di miss
- I **TLB miss** sono comuni per via del numero limitato di voci (es. 64); aumentare il TLB è costoso e richiede compromessi nel chip.
- **Soft miss**: la pagina è in memoria ma non nel TLB → serve solo aggiornare il TLB.
- **Hard miss**: la pagina **non è in memoria** → serve un accesso alla memoria non volatile (disco/SSD), molto più lento.
- La ricerca nella gerarchia delle tabelle si chiama **page table walk**. Un accesso a un **indirizzo non valido** può portare a un **segmentation fault** e alla terminazione del programma.
## Algoritmi di sostituzione delle pagine
Quando si verifica un **page fault** e la memoria fisica è piena, il SO deve scegliere **quale pagina** rimuovere (scrivendola su disco se modificata). La paginazione crea l'illusione di una memoria praticamente illimitata. Promemoria sui bit della voce: **M** (modificato/*dirty*) e **R** (riferito/*accessed*).
### Algoritmo ottimale
> [!quote] Definizione — Algoritmo ottimale
> Rimuove la pagina con il **riferimento più distante nel futuro** (quella che non sarà usata per il maggior numero di istruzioni). Es: se una pagina non sarà usata per 8 milioni di istruzioni e un'altra per 6 milioni, si rimuove la prima.

È **impossibile** da realizzare (il SO non può prevedere il futuro), ma serve come **termine di confronto**: se un algoritmo reale è solo l'1% peggiore dell'ottimale, il margine di miglioramento è dell'1%.
### NRU (Not Recently Used)
Usa i bit **R** e **M**, impostati dall'hardware a ogni accesso. Il bit **R** viene **azzerato periodicamente** (es. a ogni interrupt del clock) per identificare le pagine non usate di recente. Le pagine sono divise in **4 classi**:
- **Classe 0**: non referenziata, non modificata.
- **Classe 1**: non referenziata, modificata.
- **Classe 2**: referenziata, non modificata.
- **Classe 3**: referenziata, modificata.

La classe 1 sembra impossibile, ma compare quando un interrupt del clock azzera il bit R di una pagina di classe 3 (gli interrupt **non** azzerano M, informazione necessaria a sapere se riscrivere su disco). NRU rimuove una pagina **a caso dalla classe più bassa non vuota**. Vantaggi: semplicità, efficienza implementativa, prestazioni accettabili.
### FIFO (First-In, First-Out)
Elimina la pagina **più vecchia** in memoria: il SO rimuove la pagina in testa alla lista durante un page fault e aggiunge la nuova in coda. **Problema**: la pagina più vecchia potrebbe essere ancora frequentemente usata, rendendo FIFO poco efficace. Raramente usato nella forma semplice.
### Seconda chance
Miglioramento del FIFO: controlla il bit **R** della pagina più vecchia.
- Se **R = 0**: pagina vecchia e non usata di recente → **sostituita**.
- Se **R = 1**: il bit viene **azzerato**, la pagina è reinserita **in fondo** alla lista e trattata come appena caricata (timestamp aggiornato).

Se trova una pagina non referenziata la rimuove; se **tutte** le pagine sono referenziate, Seconda Chance degenera in **FIFO puro**, con un ciclo completo di reset dei bit R prima di rimuovere la pagina iniziale.
### Clock
Realizza la stessa idea di Seconda Chance ma con una **lista circolare** di frame e una **lancetta** (come un orologio) che punta alla pagina più vecchia, evitando di spostare continuamente le pagine nella lista.
- Se **R = 0** sulla pagina puntata → rimossa e sostituita, la lancetta avanza.
- Se **R = 1** → il bit è azzerato e la lancetta avanza alla pagina successiva.

Si ripete finché non si trova una pagina con R = 0. **Più efficiente** di Seconda Chance e FIFO.
### LRU (Least Recently Used)
> [!quote] Definizione — LRU
> Le pagine non usate di recente sono candidate alla sostituzione. Implementazione ideale: una lista con le pagine più usate in testa e le meno usate in coda.

Tende all'ottimo ma è **costoso**: ogni riferimento richiederebbe di aggiornare la lista (uno *stack*) e copiare pagine intere, anche con hardware dedicato. Esiste una variante hardware con un **contatore a 64 bit** per ogni riferimento: al page fault si rimuove la pagina con il contatore più basso (uso meno recente). Praticamente non utilizzato nella forma pura.
### NFU e Aging
**NFU** (*Not Frequently Used*) simula LRU via software: associa un **contatore** a ogni pagina, incrementato a ogni interrupt del clock in base al bit R. Tanti accessi → alto valore → minore probabilità di rimozione. **Limite**: NFU **non dimentica** mai l'uso passato, e può fare scelte subottimali (una pagina usatissima in un periodo e poi abbandonata potrebbe non venire mai sostituita).
> [!quote] Definizione — Aging
> Miglioramento di NFU con contatori a numero di bit **fisso** (es. 8 bit). A ogni interrupt del clock i bit vengono **shiftati a destra** e il bit R viene aggiunto a **sinistra**. Così l'**emula LRU** dando meno peso agli usi passati e preferendo le pagine meno referenziate di recente.

> [!example] NFU e Aging in azione
> Pagina con contatore `00000000`: se accedono diventa `10000000`, poi `11000000`, se non accedono diventa `01100000` (lo shift "spegne" gradualmente i riferimenti vecchi). Registrando **un solo bit per intervallo** non si distingue l'ordine esatto dei riferimenti nello stesso tick, ma su più tick l'algoritmo distingue correttamente la pagina usata più di recente.

**Limiti**: l'aging non distingue l'ordine esatto dei riferimenti recenti e ha un orizzonte temporale limitato (non necessariamente un male). **8 bit** sono in genere sufficienti per un buon compromesso tra accuratezza e uso di memoria.
### Working set
> [!quote] Definizione — Working set
> Insieme delle pagine **attualmente** usate da un processo; rappresenta la **località di riferimento**, cioè le pagine a cui il processo accede durante una fase dell'esecuzione. Formalmente $w(k,t)$ è l'insieme di pagine usate negli ultimi $k$ riferimenti.

Con il **demand paging** le pagine sono caricate "on demand", solo quando servono: inizialmente si verificano molti page fault finché tutte le pagine necessarie non sono in memoria. La funzione $w(k,t)$ è **monotona non decrescente** al crescere di $k$ e ha un **asintoto finito** (correlato allo spazio degli indirizzi del programma): esiste un ampio intervallo di $k$ in cui il working set resta invariato.
> [!warning] Thrashing
> Se il working set è completamente in memoria, si hanno **pochi** page fault. Se è **più grande** della memoria disponibile, si verificano **frequenti** page fault che rallentano drasticamente il processo: questo fenomeno è il **thrashing**.

Molti SO tracciano il working set di ogni processo e lo mantengono in memoria; la **pre-paginazione** carica in anticipo le pagine basandosi sul working set. In pratica il working set è definito **in termini di tempo**: le pagine usate negli ultimi $\tau$ secondi di esecuzione.
> [!example] Algoritmo Working Set
> Un interrupt periodico azzera il bit R a ogni ciclo di clock. Durante un page fault si scandiscono tutte le pagine controllando R:
> - **R = 1** → aggiorna il tempo di ultimo utilizzo (la pagina è nel working set).
> - **R = 0 ed età > τ** → la pagina **non** è nel working set → rimossa.
> - **R = 0 ed età ≤ τ** → resta, ma si segna la più vecchia come candidata.
>
> Se nessuna pagina è rimovibile si sceglie la più vecchia con R = 0, altrimenti una a caso.
### WSClock
Evoluzione del Clock che integra le informazioni del working set; popolare per **semplicità e buone prestazioni**. Usa una lista circolare di frame, ciascuno con tempo di ultimo utilizzo, bit **R** e bit **M**.
- A ogni page fault si esamina la pagina indicata dalla lancetta. Se **R = 1** non è candidata (usata nel ciclo): R viene messo a 0 e la lancetta avanza.
- Se **R = 0** ed **età > τ**:
  - **M = 0** (pulita): non è nel working set ed esiste una copia valida su disco → il frame è riciclato e vi si mette la nuova pagina.
  - **M = 1** (sporca): non c'è copia valida → non può essere sfrattata subito. Per evitare rallentamenti la **scrittura su disco viene schedulata** e rimandata, la lancetta avanza e l'algoritmo procede (lungo la lista potrebbe esserci una pagina pulita e vecchia usabile subito).

Per limitare il traffico su disco si fissa un **numero massimo** di scritture (*n* pagine) per giro di orologio. Al completamento del giro: se ci sono scritture pendenti la lancetta cerca pagine **pulite** (una scrittura completata rende la pagina pulita); se **non** ci sono scritture pendenti significa che tutte le pagine sono nel working set, e si sceglie una pagina pulita **a caso** (o, se non ce ne sono, la corrente, scrivendola su disco).
### Riepilogo
| Algoritmo | Commento |
|---|---|
| **Ottimale** | Non implementabile, ma utile come termine di confronto |
| **LRU** (Least Recently Used) | Eccellente, ma difficile da implementare con precisione |
| **NRU** (Not Recently Used) | Approssimazione molto rozza dell'LRU |
| **FIFO** | Può eliminare pagine importanti → molti page fault |
| **Seconda chance** | Deciso miglioramento rispetto al FIFO |
| **Clock** | Realistico |
| **NFU** (Not Frequently Used) | Approssimazione abbastanza rozza dell'LRU |
| **Aging** | Efficiente, approssima bene l'LRU |
| **Working set** | Piuttosto dispendioso da implementare |
| **WSClock** | Efficiente e buono |

**Aging** e **WSClock** sono i «migliori» (basati rispettivamente su LRU e sull'idea di working set): buone prestazioni e implementazione efficiente. Windows e Linux adottano **varianti** di questi algoritmi, combinando elementi diversi in base a esigenze e hardware.
## Problemi di progettazione
La paginazione richiede di bilanciare molti aspetti. I problemi più comuni: allocazione **globale vs locale**, **equa vs proporzionale**, dinamica di allocazione, policy di pulizia, dimensione delle pagine, spazi separati istruzioni/dati, pagine e librerie condivise, file mappati in memoria.
### Allocazione globale vs locale
- **Allocazione locale**: ogni processo riceve una porzione **fissa** di memoria. Semplice, ma inefficiente se il working set varia (al page fault si possono rimuovere **solo** pagine dello stesso processo).
- **Allocazione globale**: distribuzione **dinamica** della memoria tra i processi (al page fault si possono rimuovere pagine di **qualsiasi** processo). Più efficace ma più complessa.

Gli algoritmi globali si adattano meglio quando il working set varia nel tempo. Con quelli locali il **thrashing** può verificarsi se il working set cresce oltre la memoria allocata, oppure la memoria si **spreca** se il working set si riduce. Con l'allocazione globale il SO deve assegnare e riassegnare frame dinamicamente; può usare i **bit di aging** per monitorare la frequenza d'accesso (stima approssimativa, non sempre sufficiente a prevenire il thrashing).
### Allocazione equa vs proporzionale
- **Equa**: distribuzione uniforme dei frame (es. 12 416 frame / 10 processi = 1241 frame ciascuno). Non tiene conto delle esigenze diverse.
- **Proporzionale**: frame assegnati in base alla **dimensione** del processo. Rispecchia meglio le necessità.

È importante un **limite minimo di pagine** per processo: garantire abbastanza pagine per le operazioni fondamentali, evitando che istruzioni che attraversano i limiti di pagina non possano eseguire.
### Page Fault Frequency (PFF)
Gestione **dinamica** dei frame: si parte da un'allocazione proporzionale e la si aggiorna durante l'esecuzione.
> [!quote] Definizione — PFF (Page Fault Frequency)
> Monitora la frequenza dei page fault per regolare l'allocazione di memoria di un processo: **aumenta** i frame se i page fault sono troppo frequenti, li **diminuisce** se sono rari. Non specifica *quale* pagina rimuovere, ma la **dimensione** dell'allocazione.

Secondo algoritmi come LRU, più frame → meno page fault. Si contano i page fault al secondo con una **media mobile**: alta frequenza (curva sopra la soglia **A**) → servono più frame; bassa frequenza (sotto la soglia **B**) → il processo ha più memoria del necessario.
### Gestione del thrashing
Anche con il miglior algoritmo, il **thrashing** può sempre verificarsi se i working set di **tutti** i processi eccedono la memoria: il PFF segnala una richiesta collettiva senza che nessun processo possa cedere frame. Strategie di mitigazione:
- **OOM Killer** (*Out Of Memory Killer*): processo di sistema che seleziona e **termina** processi in base a un punteggio di "cattiveria" (alto uso di memoria o minore importanza) per liberare RAM.
- **Swapping**: meno drastico, sposta interi processi su memoria non volatile liberando le loro pagine, senza interromperne l'esecuzione.
- **Scheduling a due livelli**: alcuni processi stanno in memoria non volatile e solo una parte è schedulata attivamente (utile per ridurre l'occupazione dei processi in background nei [[01 - Introduzione ai Sistemi Operativi|sistemi interattivi]]). La selezione considera se i processi sono [[05 - Scheduling#Comportamento dei processi|CPU bound o I/O bound]] e la loro frequenza di paginazione.
- **Altre tecniche**: **compattamento**, **compressione** e **deduplicazione** (*same page merging*).
### Policy di pulizia e paging daemon
L'aging è più efficace con molti **frame liberi** disponibili: se i frame sono tutti occupati e modificati, occorre scrivere le vecchie pagine su disco prima di caricarne di nuove. È preferibile mantenere un buon numero di frame liberi.
> [!quote] Definizione — Paging daemon
> Processo in background, inattivo per la maggior parte del tempo, che si attiva **periodicamente** per controllare lo stato della memoria. Quando i frame liberi scarseggiano, seleziona pagine da rimpiazzare con un algoritmo di sostituzione.

Se le pagine sono state modificate vengono scritte su memoria non volatile, conservandone il contenuto per un eventuale rapido ripristino. Implementazione con **clock a due lancette**: la **lancetta anteriore** (paging daemon) avanza scrivendo le pagine sporche su disco; la **lancetta posteriore** si occupa della sostituzione, con maggiore probabilità di trovare pagine **pulite** grazie al lavoro del daemon.
### Dimensione delle pagine
La scelta della dimensione delle pagine (es. unire due pagine da 4 KB in una da 8 KB) bilancia fattori opposti:
- **Pagine piccole**: riducono la **frammentazione interna** (spazio sprecato nelle pagine parzialmente vuote) e l'uso di memoria. *Contro*: tabelle delle pagine **più grandi** (più voci), più overhead.
- **Pagine grandi**: tabelle più piccole, ma più frammentazione interna.

> [!example] Calcolo della dimensione ottimale
> Con processo medio di $s$ byte, pagina di $p$ byte, voce di tabella di $e$ byte:
> - numero di pagine per processo $\approx s/p$;
> - spazio occupato dalla tabella: $s \cdot e / p$ byte;
> - memoria sprecata per frammentazione interna nell'ultima pagina: $p/2$ in media (**fenomeno dell'ultima pagina**: l'ultima pagina allocata è spesso parzialmente vuota).
>
> **Overhead totale**: $\dfrac{se}{p} + \dfrac{p}{2}$. Derivando rispetto a $p$ e ponendo a zero: $-\dfrac{se}{p^2} + \dfrac{1}{2} = 0 \Rightarrow p = \sqrt{2se}$. Per $s = 1$ MB ed $e = 8$ byte, $p$ ottimale ≈ **4 KB**.

La gamma tipica va da 512 byte a 64 KB; la dimensione comune attuale è **4 KB**. Alcuni SO usano pagine di **diverse dimensioni** (es. pagine grandi per il kernel); le **Transparent Huge Pages (THP)** usano pagine grandi spostando la memoria del processo per creare intervalli contigui.
### Spazi separati istruzioni/dati
La maggior parte dei computer ha un **unico** spazio di indirizzi condiviso da programma e dati. Alcuni sistemi storici avevano spazi separati **I-space** (istruzioni) e **D-space** (dati), raddoppiando lo spazio disponibile. Oggi si vedono ancora spazi separati nelle **cache**, nei **TLB** e nella **cache L1**: dove lo spazio è poco, si tende a separare le istruzioni (più importanti) dai dati.
### Pagine e librerie condivise (copy on write)
È comune che molti utenti eseguano lo **stesso programma** o usino le **stesse librerie**: condividere pagine è più efficiente che tenerne copie separate.
- Le pagine **di sola lettura** (testo dei programmi) si possono condividere; quelle **dei dati** generalmente **no**.
- Per facilitare la condivisione si separano **I-space** e **D-space**: processi diversi possono usare la **stessa** tabella delle pagine per l'I-space ma tabelle diverse per il D-space. Lo scheduler usa i puntatori per impostare la MMU.

> [!warning] Problemi della condivisione
> Rimuovere un processo dalla memoria può causare numerosi page fault in un altro processo che condivide le stesse pagine: è cruciale sapere se le pagine sono ancora in uso per non liberarle per sbaglio.

> [!quote] Definizione — Copy on Write (COW)
> Dopo una [[03 - Processi e Thread#^fork|fork]] in UNIX, genitore e figlio condividono testo e dati inizialmente in **sola lettura**. Se un processo **modifica** i dati si genera una trap e viene creata una **copia** della sola pagina modificata (entrambe diventano poi scrivibili). Evita di copiare pagine che non vengono mai modificate: estremamente efficiente.

Le **librerie condivise** (*Dynamic Link Libraries*, DLL) riducono l'ingombro di grandi librerie comuni; per i dati si applica il copy on write. Poiché possono essere caricate a indirizzi diversi nei vari processi, devono essere **compilate con indirizzi relativi** (offset) anziché assoluti.
### File mappati in memoria
> [!quote] Definizione — File mappati in memoria
> Un processo può **mappare** un file nel proprio spazio di indirizzi virtuali. Alla mappatura **nessuna pagina** viene caricata subito: sono paginate su richiesta man mano che vengono "toccate". Quando il processo termina (o la mappatura è eliminata), tutte le pagine modificate vengono **riscritte sul file**.

Offre un **modello di I/O alternativo**: si accede al file come a un grande array di caratteri in memoria. Se più processi mappano lo **stesso** file, possono **comunicare** attraverso questa memoria condivisa (le modifiche di uno sono immediatamente visibili agli altri).
## Dettagli implementativi
### Attività del SO nella paginazione
- **Creazione del processo**: determinare le dimensioni iniziali di programma e dati, creare e inizializzare la tabella delle pagine, allocare lo spazio di scambio su memoria non volatile, inizializzare l'area di scambio e registrare le informazioni nella tabella dei processi.
- **Esecuzione del processo**: azzerare la MMU e svuotare il TLB se necessario, rendere attiva la tabella delle pagine del processo, opzionalmente **pre-paginare** alcune pagine per ridurre i page fault iniziali.
- **Gestione dei page fault**: determinare l'indirizzo virtuale che ha causato il fault, trovare la pagina necessaria su memoria non volatile, scegliere un frame (eventualmente sfrattando pagine vecchie), caricare la pagina e ripristinare il *program counter*.
- **Chiusura del processo**: rilasciare tabella delle pagine, pagine in memoria e spazio su disco/SSD, gestendo le **pagine condivise** (rilasciate solo dopo l'ultimo utilizzo).
### Page fault in 10 passi
> [!example] Sequenza completa di gestione di un page fault
> **A. Inizio**
> 1. **Trap nel kernel**: l'hardware salva il *program counter* sullo stack; le informazioni sull'istruzione corrente vanno nei registri speciali della CPU.
> 2. **Routine di servizio**: una routine in assembly salva i registri e le informazioni volatili, poi invoca il gestore dei page fault.
> 3. **Identificazione della pagina virtuale** mancante (dai registri hardware o analizzando l'istruzione dal PC).
>
> **B. Gestione e risoluzione**
> 4. **Verifica validità e protezione** dell'indirizzo; se invalido → segnale di errore o terminazione.
> 5. **Rilascio di un frame libero**: se non ce ne sono, si esegue un algoritmo di sostituzione; se la pagina scelta è "sporca" viene schedulata per la scrittura e il processo è sospeso.
> 6. **Caricamento della pagina richiesta** nel frame liberato (da disco/SSD); durante il caricamento può girare un altro processo.
>
> **C. Conclusione e ripresa**
> 7. **Aggiornamento delle tabelle**: la page table riflette la nuova posizione; il frame è segnato come disponibile.
> 8. **Ripristino dell'istruzione in errore** allo stato iniziale; il PC torna a puntare a quell'istruzione.
> 9. **Ripresa del processo**: viene rischedulato, si torna alla routine assembly.
> 10. **Ricarica dei registri** e ritorno allo spazio utente, riprendendo da dove era stato interrotto.
### Pinning delle pagine durante l'I/O
> [!warning] Problema con il page fault durante l'I/O
> Un processo avvia una lettura in un buffer nel suo spazio di indirizzi e viene sospeso in attesa. Se un secondo processo genera un page fault, c'è il rischio che la pagina contenente il buffer di I/O venga scelta per la rimozione: se è in corso un trasferimento **DMA** (vedi [[08 - Input Output#DMA|Direct Memory Access]]), la rimozione causerebbe scritture errate.

**Soluzione — *pinning***: le pagine usate per l'I/O vengono "bloccate" (*pinned*) in memoria, impedendone la rimozione finché l'operazione non è completa. **Alternativa**: gestire l'I/O nei buffer del **kernel** e poi copiare i dati nelle pagine utente (richiede una copia in più, potenzialmente più lenta).
### Gestione dello spazio di scambio (swap)
*Dove* viene messa una pagina quando è "paginata fuori" dalla memoria?
- **Spazio di scambio** (*file* o **partizione di swap**): il SO prevede una partizione speciale o un dispositivo separato (come nei sistemi UNIX), strutturato in modo diverso dal [[07 - File System|file system]] usato per file e cartelle — partizione con file system semplificato e numeri di blocco relativi.
- **Allocazione**: all'avvio si alloca spazio nella partizione pari alla dimensione del processo, gestito come lista di parti libere.
- **Associazione processo–area**: ogni processo ha un'area di scambio; l'indirizzo dove scrivere una pagina si calcola sommando l'offset della pagina all'inizio dell'area di scambio.

Due strategie di paginazione: **(a)** area di scambio **statica**, ogni pagina ha una posizione fissa su disco; **(b)** **salvataggio dinamico**, l'indirizzo su disco è scelto al momento dello scambio (tavola per processo che indica la posizione di ogni pagina). Alcuni SO (es. Windows) usano file pre-allocati nel file system normale.
## La segmentazione
La memoria vista finora è **monodimensionale**: gli indirizzi virtuali vanno da 0 a un massimo, disposti in modo lineare e contiguo. Questo è **problematico** in scenari come la **compilazione**, dove diverse tabelle (testo sorgente, tabella dei simboli, costanti, albero di parsing, stack) crescono dinamicamente e in modo imprevedibile: la crescita di una tabella può causare **sovrapposizioni** con un'altra.
### Memoria monodimensionale vs segmentata
> [!quote] Definizione — Segmentazione
> Introduce spazi di indirizzi virtuali **multipli e indipendenti** detti **segmenti**. Ciascun segmento ha una sequenza lineare di indirizzi da 0 a un massimo **variabile**; segmenti diversi possono avere lunghezze diverse e cambiare dimensione durante l'esecuzione, **crescendo o riducendosi senza interferire** l'uno con l'altro. Un indirizzo si specifica con due parti: **numero di segmento** e **indirizzo nel segmento**.
### Vantaggi
- **Flessibilità**: i segmenti crescono/si riducono indipendentemente (es. lo stack del compilatore senza toccare le altre tabelle), eliminando le collisioni della memoria monodimensionale.
- **Semplificazione del linking**: se ogni procedura occupa un segmento separato, il linking diventa più semplice (modifiche a una procedura non richiedono di aggiornare gli indirizzi delle altre).
- **Condivisione e protezione**: facilita la condivisione di risorse (es. librerie condivise) tra processi e permette di applicare **livelli di protezione** diversi ai segmenti (sola lettura, sola esecuzione).
### Paginazione vs segmentazione
| Considerazione | Paginazione | Segmentazione |
|---|---|---|
| Il programmatore deve saperlo? | NO | SI |
| Quanti spazi di indirizzi lineari? | 1 | Molti |
| Lo spazio totale può superare la memoria fisica? | SI | SI |
| Procedure e dati distinti e protetti separatamente? | NO | SI |
| Tabelle a dimensione variabile gestite facilmente? | NO | SI |
| Condivisione di procedure tra utenti facilitata? | NO | SI |
| Perché fu inventata? | Spazio di indirizzi grande senza più memoria fisica | Spezzare programmi/dati in spazi logicamente indipendenti, facilitando condivisione e protezione |

La segmentazione offre più flessibilità e gestione delle strutture dati, ma è **più complessa da implementare**.
### Segmentazione pura e frammentazione esterna
A differenza delle pagine (dimensione fissa), i **segmenti** hanno dimensione variabile. Sostituendo segmenti di taglie diverse la memoria si suddivide in parti, alcune con segmenti e altre vuote: è la **frammentazione esterna** (*checkerboarding*), risolvibile con la **compattazione**.
### MULTICS
> [!info] MULTICS — pioniere di segmentazione + paginazione
> Progetto di ricerca del **M.I.T.**, operativo nel **1969** e influente fino al 2000 (impatto su UNIX, architettura x86, TLB). Forniva fino a $2^{18}$ segmenti per programma, ciascuno lungo fino a $2^{16} = 65\,536$ parole. I **segmenti** erano trattati come spazi di memoria virtuale **indipendenti e paginati**.

Ogni segmento ha un **descrittore** a **36 bit** con la seguente struttura (i numeri indicano la larghezza in bit di ogni campo):

| Campo | Bit | Significato |
|---|---|---|
| Indirizzo memoria fisica tabella pagine | 18 | Dove si trova la page table del segmento in RAM |
| Lunghezza segmento (in pagine) | 9 | Numero di pagine del segmento |
| Dimensione pagina | 1 | 0 = 1024 parole; 1 = 64 parole |
| Paginato/non paginato | 1 | 0 = segmento paginato; 1 = non paginato |
| Bit miscellanei | 3 | Vari flag di sistema |
| Bit di protezione | 3 | Permessi di accesso |

Il *descriptor segment* raccoglie tutti i descrittori. L'indirizzo virtuale a **34 bit** è diviso in: numero di segmento (18 bit) + indirizzo nel segmento, a sua volta numero di pagina (6 bit) + offset nella pagina (10 bit).

> [!example] Conversione di un indirizzo MULTICS
> 1. Il numero di segmento individua il **descrittore** del segmento.
> 2. Si verifica che la tabella delle pagine del segmento sia in memoria.
> 3. Si esamina la voce della pagina virtuale: se non in memoria → page fault; altrimenti si estrae l'indirizzo d'inizio della pagina.
> 4. Si ottiene l'indirizzo in memoria principale sommando l'**offset** all'origine della pagina.
> 5. Avviene la lettura o il salvataggio.

MULTICS fu il **primo** sistema a usare un **TLB** (16 parole) per accelerare la ricerca degli indirizzi: programmi con working set minore del TLB raggiungono maggiore efficienza. Ogni voce del TLB conteneva sei campi: **Segment number** e **Virtual page** (campo di confronto usato per la ricerca), **Page frame** (risultato della traduzione), **Protection** (permessi), **Age** e un bit **"Is this entry used?"** (voce presente/valida). L'esistenza di **due dimensioni di pagina** (1024 e 64 parole) rendeva il TLB reale più complesso di questa versione semplificata.
### Segmentazione in x86
Fino all'x86-64, Intel x86 rifletteva il modello MULTICS combinando segmentazione e paginazione (16 000 segmenti indipendenti, ognuno fino a 1 miliardo di parole a 32 bit). Nell'**x86-64** la segmentazione diventa **obsoleta**, mantenuta via software solo per compatibilità, perché i SO chiave (UNIX, Windows) non la adottano per portabilità e Intel ha preferito ottimizzare lo spazio del chip. L'architettura x86 è apprezzata per l'equilibrio tra paginazione, segmentazione e retrocompatibilità.
## Il comando `free` (Linux)
> [!info] `free` — monitorare la memoria
> Fornisce dettagli sull'utilizzo della memoria fisica e dello **swap**. Colonne principali:
> - `total`: memoria fisica totale disponibile.
> - `used`: memoria attualmente in uso.
> - `free`: memoria libera/non utilizzata.
> - `shared`: memoria condivisa (obsoleta, presente solo per compatibilità).
> - `buff/cache`: memoria per buffer/cache/**slab**, recuperabile se necessario.
> - `available`: stima della memoria disponibile per nuove applicazioni, considerando buffer e cache.

Opzioni utili: `-h` (formato leggibile MB/GB); `-b`, `--kilo`, `--mega`, `--giga` (unità di misura); `-t` (mostra i totali); `-s N` (aggiornamento continuo ogni N secondi, simile a `watch`).
> [!info] Collegamenti con Architettura
> La struttura della **CPU**, dei registri e della gerarchia di cache è approfondita nel corso di Architettura dei Sistemi di Elaborazione del primo anno: vedi [[2 - Organizzazione dei sistemi di calcolo]] e la nota dedicata [[3 - Gestione della Memoria]], che copre lo stesso materiale di Tanenbaum (paginazione, MMU, sostituzione delle pagine) da una prospettiva architetturale.
