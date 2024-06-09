Il seguente capitolo tratta, come dice il titolo, l'organizzazione hardware di un sistema di calcolo completo: componenti, tecniche di sviluppo, miglioramenti.
## 2.1 Processori

La **CPU** (*Central Process Unit*) è il cervello della macchina ed esegue tutti i programmi prelevandoli dalla memoria. Essa è connessa internamente ed esternamente ai componenti tramite i **bus**, che per ora vediamo come un insieme di cavi paralleli sui quali vengono trasmessi indirizzi, dati e segnali di controllo.

La CPU è composta da diverse unità, quali la **CU** (*Control Unit*), la **ALU** e diversi registri che fungono da piccola memoria ma con alte velocità di lettura e scrittura. Tra i registri più importanti abbiamo il **Program Counter** e l'**Instruction Register** che rispettivamente puntano alla istruzione successiva e contengono l'istruzione corrente.
### 2.1.1 Organizzazione della CPU

Il **percorso dati** (Letteralmente il percorso che esegue un dato) di una tipica CPU di von Neumann è composta da: *1 a 32 registri*, una *ALU* e dei *bus* che connettono i registri, a registri di input, alla ALU, etc\... La ALU esegue semplici operazioni il cui output viene salvato in registri di output.

Esistono due tipologie di operazioni: quelle di **registro-memoria** che prelevano informazioni dalla memoria e le inseriscono nei registri e quelle di **registro-registro** che spostano informazioni o le forniscono alla ALU e poi le spostano nel registro di output. Tutto il lavoro svolto dalla ALU e i suoi registri è chiamato **ciclo del percorso dati** e rappresenta il cuore della maggior parte delle CPU.
### 2.1.2 Esecuzione dell'istruzione 

Il **ciclo esecutivo delle istruzioni** sono i passaggi per permettere alla CPU di eseguire una istruzione, si chiama anche **fetch-decode-execute**. I passaggi generalmente sono i seguenti: 
- Prelevare l'istruzione successiva della memoria e portarla nell'IR. 
- Modificare il PC per puntarlo all'istruzione seguente.
- Decodificare l'istruzione interna all'IR.
- Se l'istruzione usa una parola di memoria

La precedente descrizione somiglia quasi ad un programma scritto in *pseudo-codifica*, il che implica che possiamo scrivere un programma che esegua queste istruzioni. Questo programma è proprio un **interprete**, quindi possiamo creare una "CPU Virtuale" che gira un un linguaggio compatibile con quella macchina (Concetto di interpreti e linguaggi interpreti).

L'interprete permetteva di aggiungere nuove istruzioni e funzionalità senza toccare l'hardware, quindi a livello software. Per poter mantenere una famiglia di macchine che potevano tutte eseguire le stesse istruzioni, venne creato il concetto di **architettura**, che creava un layer di compatibilità.

Grazie alle architetture, si potevano inviare aggiornamenti di alcune istruzioni, risolvere errori prima dell'esecuzione dei programmi e sviluppare in modo efficiente nuove istruzioni. Un altro fattore che rese sempre più usato il principio di interpretazione fu lo sviluppo delle **memorie di controllo**, memorie molto veloci in cui veniva salvato l'interprete per rendere più veloce l'interpretazione.

### 2.1.3 RISC contro CISC
Tradizionalmente, c'è sempre stata una tendenza a sviluppare nuove tecnologie in grado di implementare istruzioni sempre più complesse. L'ultima tendenza è stata quella di _interpretare_ le istruzioni, con l'obiettivo finale di ridurre il divario tra l'hardware progettato e il software scritto dai programmatori. Questo ha portato a una nuova tipologia di implementazione dei calcolatori e la divisione in due tipologie di esse.

Seguendo il modello di _Seymour Cray_, fu inventato un nuovo tipo di microcomputer ad alte prestazioni che suscitò l'interesse di alcuni progettisti, i quali tentarono di seguire lo stile di quella architettura. Questo portò all'avvio di un progetto chiamato **RISC** (Reduced Instruction Set Computer), che si proponeva di sviluppare una tecnologia con le seguenti caratteristiche:
- Non doveva essere retrocompatibile con altre architetture.
- Doveva essere progettato per massimizzare **l'emissione delle istruzioni**, relegando in secondo piano il tempo effettivo di esecuzione delle istruzioni.

In contrapposizione abbiamo invece i calcolatori di tipo **CISC** (Complex Instruction Set Computer) che seguivano la precedente moda.

Ne conseguì una vera e propria "guerra religiosa" tra i sostenitori delle metodologie di progettazione RISC e CISC. Tuttavia, nonostante i buoni propositi e le eccellenti caratteristiche, perché l'architettura RISC non ha prevalso sulla concorrenza?

La risposta si trova sia a livello _economico_ che di _compatibilità_. Gli investimenti in aziende come **Intel** e la necessità di mantenere la compatibilità con il software esistente rendevano poco conveniente l'adozione di una nuova tecnologia. L'unico compromesso fu offerto da Intel in alcuni processori, che integravano un nucleo RISC e uno CISC, per migliorare parzialmente le prestazioni pur mantenendo la compatibilità con l'architettura esistente.

### 2.1.4 Principi di progettazione dei calcolatori moderni
Il progetto **RISC** continua a portare con sé principi di progettazione che sono tuttora applicati a livello generale, in quanto ottimali. I _principi di progettazione RISC_ seguiti attualmente sono i seguenti:
- _Tutte le istruzioni sono eseguite direttamente dall'hardware_, senza l'utilizzo dell'interpretazione di microistruzioni. Eliminando questo livello di astrazione, si ottengono migliori performance nel calcolatore.
- _Massimizzare la frequenza di emissione delle istruzioni_, ponendo al centro la tecnica del **parallelismo delle istruzioni**, di cui parleremo più avanti. Generalmente è preferibile eseguire più istruzioni contemporaneamente piuttosto che eseguirle più velocemente, indipendentemente dal tempo di esecuzione.
- _Istruzioni facili da decodificare_, creando uno o pochi pattern di istruzioni per rendere la decodifica semplice. La fase di decodifica può rallentare significativamente l'esecuzione delle istruzioni se non è ben progettata.
- _Solo le istruzioni Load e Store fanno riferimento alla memoria_, separando le operazioni in passi distinti: prelevare gli operandi e memorizzarli nei registri per l'esecuzione. Prelevare dati dalla memoria è un'operazione potenzialmente lenta e soggetta a vari problemi. La soluzione è fare riferimento solo alle istruzioni di load e store, facendo operare tutte le altre sui registri.
- _Disponibilità di molti registri_, poiché prelevare dati dalla memoria è molto lento. È preferibile conservare i valori nei registri, in quanto sono notevolmente più veloci.

### 2.1.5 Parallelismo a livello d'istruzione
I progettisti di calcolatori si sforzano costantemente di migliorare le prestazioni delle loro macchine. Per questo motivo molti progettisti di computer vedono nel parallelismo (compiere più azioni allo stesso tempo) un modo per ottenere prestazioni più elevate con una data velocità di clock.

Il parallelismo può essere presente in due forme:
- *a livello d'istruzione*: è sfruttato all'interno delle singole istruzioni per far si che la macchina possa elaborarne un maggior numero al secondo
- *a livello di processore*: sono presenti più CPU che lavorano congiuntamente su uno stesso problema

In questo paragrafo analizziamo il primo tipo, nel prossimo, invece, quello a livello di processore.
#### 2.1.5.1 - Pipelining
Per migliorare la velocità di esecuzione delle istruzioni, sin dagli anni '50 (come con IBM Stretch), i computer sono stati dotati di buffer di prefetch, registri in grado di anticipare il prelievo delle istruzioni dalla memoria. Ciò ha permesso di avere le istruzioni pronte per l'esecuzione senza dover attendere la loro lettura dalla memoria principale al momento del bisogno. Queste istruzioni vengono memorizzate in un insieme di registri chiamati **buffer di prefetch**, da cui possono essere utilizzate immediatamente quando necessario, senza attendere il completamento della lettura dalla memoria.

In pratica la tecnica di *prefetching* divide l'esecuzione dell'istruzione in due parti:
- prelievo dell'istruzione
- esecuzione dell'istruzione
Il concetto di *pipeline* spinge questa strategia molto più avanti; invece di dividere l'esecuzione di un'istruzione solamente in due fasi, la divide in un numero maggiore di parti (~12) che possono essere eseguite in parallelo: ciascuna di queste parti è gestita da componenti hardware dedicati.

Durante il primo ciclo di clock, lo stadio S1 preleva l'istruzione 1 dalla memoria. Nel secondo ciclo, S2 decodifica l'istruzione 1 mentre S1 preleva l'istruzione 2. Nel terzo ciclo, S3 preleva gli operandi per l'istruzione 2 e l'istruzione 1, S2 decodifica l'istruzione 2, e S1 preleva la terza istruzione. Durante il quarto ciclo, S4 esegue l'istruzione 1, S3 preleva gli operandi per l'istruzione 2, S2 decodifica l'istruzione 3, e S1 preleva l'istruzione 4. Infine, nell'ultimo ciclo, S5 scrive il risultato dell'istruzione 1, mentre gli altri stadi continuano a lavorare sulle istruzioni successive.

Supponendo un ciclo di clock di 2 ns e 10 ns per completare i cinque stadi della pipeline, la macchina sembrerebbe avere una velocità di 100 MIPS. Tuttavia, poiché viene completata un'istruzione ogni 2 ns, la vera velocità di elaborazione è di 500 MIPS anziché solo 100.

L'uso della pipeline bilancia la **latenza** e la **larghezza di banda del processore**. Con un ciclo di clock di T ns e una pipeline a n stadi, la latenza è di nT ns, poiché ogni istruzione attraversa n stadi, ciascuno richiedente T ns. Sebbene si potrebbe teoricamente misurare la velocità di esecuzione in BIPS$^{3}$ anziché in MIPS, questa pratica non è comune e quindi non verrà adottata.
Figura 2.4
#### 2.1.5.2 - Architetture superscalari
Se è bene avere una pipeline, averne due è sicuramente meglio. La Figura 2.5 mostra un ipotetico progetto di una CPU con due pipeline, entrambe basate sullo schema della Figura 2.4. In questa situazione una singola unità di fetch preleva due istruzioni alla volta e le inserisce nelle pipeline, ognuna delle quali è dotata di una ALU. Affinché le due istruzioni possano essere eseguite in parallelo, non devono però esserci conflitti nell'uso delle risorse e nessuna delle due istruzioni deve dipendere dal risultato dell’altra. Come nel caso della singola pipeline, o è il compilatore a occuparsi di gestire correttamente questa situazione oppure i conflitti sono rilevati ed eliminati durante l’esecuzione per mezzo di componenti hardware ad hoc.

La pipeline principale, chiamata **pipeline u**, poteva eseguire una qualsiasi istruzione Pentium. La seconda pipeline, chiamata **pipeline v**, poteva invece eseguire solamente semplici istruzioni su interi.

Figura 2.5

Alcune regole determinavano se due istruzioni potevano essere eseguite in parallelo. Se non erano sufficientemente semplici o compatibili, solo la prima veniva eseguita subito, mentre la seconda veniva trattenuta per essere accoppiata all'istruzione successiva. Le istruzioni erano sempre eseguite in ordine. Compilatori specifici per il Pentium, capaci di produrre coppie di istruzioni compatibili, potevano generare programmi più veloci rispetto ai vecchi compilatori. Un'architettura con quattro pipeline richiederebbe la duplicazione di molti componenti hardware, quindi nelle CPU di gamma alta si utilizza un approccio diverso, con una singola pipeline associata a più unità funzionali. Questo approccio, chiamato **architettura superscalare** dal 1987, risale al calcolatore CDC 6600, che prelevava un'istruzione ogni 100 ns e la passava a una delle 10 unità funzionali che lavoravano in parallelo mentre la CPU avviava l'istruzione successiva.

Nel corso del tempo la definizione di “superscalare” si è in qualche modo evoluta; ora è utilizzata per descrivere processori che lanciano più istruzioni (spesso quattro o sei) durante un ciclo di clock. Ovviamente una CPU superscalare, per poter gestire tutte queste istruzioni, deve avere più unità funzionali.

(pagine riassunte: 4)

### 2.1.6 - Parallelismo a livello di processore
La richiesta di calcolatori sempre più veloci è inarrestabile. Tuttavia, poiché le CPU continuano a diventare più veloci, si incontreranno problemi legati alla velocità della luce, con un ritardo di propagazione di 20 cm/ns nei cavi di rame e nelle fibre ottiche. Inoltre, chip più veloci generano più calore, il cui smaltimento rappresenta un problema significativo. La difficoltà di dissipare il calore è la principale ragione per cui la velocità di clock delle CPU è stagnata negli ultimi dieci anni. Il parallelismo a livello d'istruzione aiuta, ma il miglioramento delle prestazioni tramite pipeline e operazioni superscalari è limitato. Per ottenere guadagni significativi, l'unica soluzione è progettare calcolatori con più CPU. Pertanto, verrà ora analizzata l'organizzazione di alcuni di questi sistemi.
#### 2.1.6.1 - Computer con parallelismo sui dati

Molti problemi in ambiti computazionali come la fisica, l'ingegneria e la computer graphic utilizzano cicli e array, o comunque hanno una struttura altamente regolare. Spesso, gli stessi calcoli vengono ripetuti su diversi insiemi di dati. Questa regolarità rende tali programmi particolarmente adatti all'esecuzione parallela, migliorandone le prestazioni. Due metodi principali sono stati utilizzati per eseguire questi programmi in modo rapido ed efficiente: i processori SIMD e i processori vettoriali. I processori SIMD sono generalmente considerati calcolatori paralleli, mentre i processori vettoriali sono visti come un'estensione di un singolo processore.

I computer con parallelismo sui dati, grazie alla loro efficienza, hanno trovato molte applicazioni di successo. Essi offrono una grande potenza computazionale utilizzando un numero inferiore di transistor rispetto ad altri approcci. I processori con parallelismo sui dati sono tra i metodi più efficaci per ottenere alte prestazioni dal silicio. Poiché tutti i processori eseguono la stessa istruzione, il sistema richiede solo un "cervello" per controllare il computer. Pertanto, il processore necessita solo di uno stadio di prelievo, uno di decodifica e di una logica di controllo.

Un processore SIMD (Single Instruction-stream Multiple Datastream) consiste di un elevato numero di processori identici che eseguono la stessa sequenza d’istruzioni su insiemi diversi di dati.

Le moderne unità di elaborazione grafica (GPU) si basano ampiamente sull'elaborazione SIMD per offrire grande potenza di calcolo con pochi transistor. L'elaborazione grafica è adatta ai processori SIMD poiché molti algoritmi sono altamente regolari, con operazioni ripetute su pixel, vertici, texture e contorni. Ad ogni ciclo, lo scheduler sceglie due thread da eseguire sul processore SIMD. L'istruzione successiva di ciascun thread viene poi eseguita da 16 processori SIMD. Se ogni thread può eseguire 16 operazioni per ciclo, una GPU Fermi con 32 SM a pieno carico può eseguire 512 operazioni per ciclo.

Agli occhi di un programmatore, i **processori vettoriali** risultano molto simili a un processore SIMD. Anche questi processori eseguono in modo molto efficiente una stessa sequenza di operazioni su coppie di dati, anche se, a differenza dei processori SIMD, tutte le operazioni di addizione sono eseguite da un unico sommatore, altamente strutturato a pipeline.

Sia i processori SIMD sia i processori vettoriali lavorano su array di dati. Entrambi eseguono singole istruzioni che, per esempio, sommano a coppie gli elementi di due vettori ma, mentre un processore SIMD lo fa usando tanti sommatori quanti sono gli elementi dei vettori, in un processore vettoriale si utilizza invece un **registro vettoriale**, che consiste di un insieme di registri convenzionali caricabili dalla memoria in una singola istruzione.

Le istruzioni SSE (Streaming SIMD Extension) dell’architettura Intel Core utilizzano questo modello di esecuzione per velocizzare i programmi altamente regolari, come le applicazioni multimediali o il software scientifico.

#### 2.1.6.2 - Multiprocessori
In un processore parallelo sui dati, le unità di elaborazione non sono CPU indipendenti poiché condividono un'unica unità di controllo. Il primo sistema parallelo con più CPU complete che analizziamo è il **multiprocessore**, composto da più CPU che condividono una memoria comune. Ogni CPU può leggere e scrivere in qualsiasi parte della memoria, quindi devono coordinarsi tramite software per evitare conflitti. Quando due o più CPU interagiscono così strettamente, si dice che sono *tightly coupled*.

Sono possibili vari schemi d’implcmentazione, il più semplice dei quali consiste nell’avere un singolo bus con più CPU, tutte connesse a un’unica memoria.

È facile prevedere conflitti quando molti processori veloci tentano di accedere alla memoria attraverso lo stesso bus. Per ridurre queste contese e migliorare le prestazioni, i progettisti di multiprocessori hanno ideato vari schemi. Una soluzione, mostrata nella Figura 2.8, prevede che ogni processore abbia una propria memoria locale non accessibile agli altri. Questa memoria può contenere il codice del programma e i dati non condivisi, riducendo significativamente il traffico sul bus principale. Oltre a questo schema, ne esistono altri. Rispetto ad altri tipi di calcolatori paralleli, i multiprocessori offrono il vantaggio di un modello di programmazione basato sulla memoria condivisa. Poiché ogni processore può accedere all'intera memoria, non ci sono problemi se lo studio di una cellula supera i limiti della regione assegnata.
#### 2.1.6.3 - Multicomputer
Se da un lato è relativamente semplice costruire multiprocessori composti da un modesto numero di processori (non più di 256), è invece decisamente più complicato realizzarne di più grandi. La difficoltà risiede nel connettere tutti i processori alla memoria. Per aggirare questi problemi molti progettisti hanno semplicemente abbandonato l’idea di avere una memoria condivisa e hanno costruito sistemi composti da un gran numero di calcolatori interconnessi, ciascuno dotato di una memoria privata. Questi sistemi sono detti **multicomputer**. In questi sistemi le CPU sono dette con legame lasco (*loosely coupled*), in contrapposizione con quelle che compongono i multiprocessori.

Le CPU dei multicomputer comunicano fra loro inviandosi messaggi, simili alle e-mail, ma molto più veloci. Nel caso di grandi sistemi, dato che non è efficiente connettere mutualmente tutti i calcolatori, si utilizzano topologie diverse come griglie 2D e 3D, alberi e anelli.

Visto che è facile programmare i multiprocessori, mentre i multicomputer sono facili da costruire, molte ricerche sono indirizzate alla realizzazione di sistemi ibridi che uniscano le qualità di entrambi. Tali calcolatori cercano di dare l'illusione che esista una memoria condivisa, senza però averne realmente una in quanto troppo costosa.

(pagine riassunte: 4.5)
## 2.2 - Memoria principale
La **memoria** è quella parte del calcolatore in cui sono depositati programmi e dati. Alcuni informatici utilizzano il termine inglese **store** o **storage** al posto di memoria, anche se il termine Storage viene utilizzato sempre più frequentemente per riferirsi alla registrazione dei dati nei dischi. Se non ci fosse una memoria da cui il processore potesse leggere e scrivere informazioni, non esisterebbero i calcolatori digitali a programma memorizzato.
### 2.2.1 - Bit
L’unità base della memoria è la cifra binaria, chiamata **bit**. Un bit può avere valore 0 oppure i ed è l’unità più semplice possibile.

Quando si dice che i calcolatori utilizzano l’aritmetica binaria perché è "efficiente” , s’intende che l’informazione digitale può essere memorizzata utilizzando dei valori di una certa quantità fisica continua, come la tensione o la corrente. Se occorre distinguere più valori, allora ci deve essere una minor separazione tra valori adiacenti e la memoria risulta di conseguenza meno affidabile.

Alcuni calcolatori sono pubblicizzati affermando che sono dotati di aritmetica decimale oltre di quella binaria. Il trucco utilizzato consiste nell’usare 4 bit per memorizzare una cifra decimale mediante un codice chiamato BCD (*Binary Coded Decimal*). Quattro bit forniscono 16 combinazioni, di cui 10 sono utilizzate per le cifre da 0 a 9, mentre 6 sono inutilizzate.

(pagine riassunte: 1)
### 2.2.2 - Indirizzi di memoria
Le memorie sono costituite da un certo numero di **celle** (o **locazioni**) ciascuna delle quali può memorizzare informazioni. Ciascuna cella ha un numero, chiamato **indirizzo**, attraverso il quale il programma può riferirsi a essa. Se una memoria ha $n$ celle, i suoi indirizzi varieranno da 0 a $n - 1$. Tutte le celle di una memoria contengono lo stesso numero di bit; se una cella è costituita da $k$ bit, essa può contenere una qualsiasi delle $2^{k}$ diverse combinazioni di bit. I calcolatori che usano il sistema numerico binario (comprese la notazione ottale ed esadecimale) esprimono gli indirizzi di memoria in notazione binaria. Se un indirizzo ha $m$ bit, il massimo numero di celle indirizzabili è $2^{m}.$ 

La cella rappresenta la più piccola unità indirizzabile; negli ultimi anni quasi tutti i produttori di calcolatori ne hanno standardizzato la dimensione impostandola a 8 bit. Questa dimensione è chiamata **byte**, ma anche il termine **ottetto** (**octet**) è talvolta utilizzato; i byte sono raggruppati in **parole** (word).

(pagine riassunte: 2)
### 2.2.3 - Ordinamento dei byte
All'interno di una parola i byte possono essere numerati da destra a sinistra o da sinistra a destra. Questa scelta presenta degli importanti risvolti. Il primo sistema, in cui la numerazione comincia a partire dall'estremo più "grande" è chiamato *big endian*, in contrapposizione con il sistema *little endian* della figura 2.11.

Figura 2.11

Nei sistemi *big endian* e *little endian*, un intero a 32 bit con valore 6 è rappresentato dai bit 110 nei 3 bit più a destra e zero nei 29 bit più a sinistra. Nel sistema *big endian*, i bit 110 sono nel byte 3, mentre nel sistema *little endian* sono nel byte 0. Entrambe le rappresentazioni sono corrette e coerenti internamente. I problemi sorgono quando uno di questi sistemi invia un record all'altro via rete. Se una macchina *big endian* invia un record a una *little endian*, byte per byte, l'ordine dei byte risulta invertito, causando errori nella lettura di valori numerici.

Una soluzione potrebbe essere un programma che inverte i byte all'interno di una parola dopo la copia, ma non esiste una soluzione semplice al problema. Un metodo poco efficiente consiste nell'includere un'intestazione prima di ogni dato per specificarne il tipo e la lunghezza, permettendo al ricevente di effettuare solo le conversioni necessarie.

(pagine riassunte: 2)
### 2.2.4 - Codici correttori
Le memorie dei calcolatori possono occasionalmente commettere errori a causa di picchi di tensione o altre cause. Per proteggersi, alcune memorie utilizzano codici di rilevazione e/o correzione degli errori, aggiungendo bit extra a ogni parola di memoria. Una parola di memoria con $m$ bit di dati e $r$ bit di controllo, formando una **parola di codice** (codeword) di $(n = m + r)$ bit, può rilevare e correggere errori in base alla **distanza di Hamming**.

La distanza di Hamming, ottenuta calcolando l'OR esclusivo (XOR) tra i bit di due parole e contando i bit a 1 nel risultato, determina la capacità di rilevazione e correzione degli errori. Per rilevare $d$ errori singoli, è necessaria una parola con distanza $d+1$, mentre per correggere $d$errori singoli serve una distanza $2d+1$.

Un esempio semplice di codice di correzione è l'uso di un singolo **bit di parità**, scelto per rendere pari (o dispari) il numero di bit 1 nella parola di codice. Questo codice ha una distanza di 2, permettendo di rilevare errori singoli, poiché ogni errore singolo altera la parità. Tuttavia, non può correggere errori tripli, poiché due errori singoli possono trasformare una parola valida in un'altra valida, rendendo impossibile la correzione.

(pagine riassunte: 4.25)
### 2.2.5 - Memoria cache
Storicamente, le CPU sono sempre state più veloci delle memorie. Mentre le CPU hanno migliorato le loro prestazioni tramite architetture a pipeline e superscalari, le memorie hanno aumentato principalmente la loro capacità, peggiorando lo squilibrio tra i due componenti. Questo squilibrio si manifesta quando la CPU deve attendere diversi cicli per ottenere i dati richiesti dalla memoria. Esistono due approcci per affrontare questo problema:

1. **Lettura anticipata e blocco della CPU**: le istruzioni di lettura dalla memoria iniziano appena vengono incontrate, ma la CPU si blocca se tenta di utilizzare una parola non ancora arrivata.
2. **Compilatori ottimizzati**: i compilatori generano codice che evita di utilizzare parole prima che siano disponibili, ma questo approccio è difficile da implementare.

La tecnologia non è il problema principale, ma piuttosto le considerazioni economiche. Le memorie veloci quanto le CPU devono essere integrate nel chip della CPU, aumentando i costi e le dimensioni. La soluzione ideale sarebbe avere una grande quantità di memoria veloce a basso costo, ma le limitazioni pratiche impongono di scegliere tra una piccola quantità di memoria veloce e una grande quantità di memoria lenta.

Per combinare i vantaggi di entrambe, si utilizza la **cache**, una piccola e veloce memoria che contiene le parole di memoria più frequentemente usate. La CPU cerca prima nella cache e, se la parola non è presente, la richiede alla memoria centrale. Questo riduce drasticamente il tempo medio di accesso se una frazione significativa delle parole è presente nella cache.

Il successo della cache dipende dalla **principio di località**, che afferma che i riferimenti alla memoria in brevi intervalli temporali tendono a usare solo una piccola frazione della memoria totale. Le parole vicine a quella referenziata vengono caricate nella cache per accessi futuri veloci.

Il tempo medio di accesso può essere calcolato come:
$$\text{Tempo medio di accesso} = c + (1 - h)m$$
dove \(c\) è il tempo di accesso alla cache, \(m\) è il tempo di accesso alla memoria centrale, e \(h\) è la frequenza di successi della cache.

Le memorie centrali e le cache sono divise in blocchi fissi, o **linee di cache**. In caso di fallimento della cache, viene caricata un'intera linea dalla memoria centrale.

Un quarto problema è la scelta tra una **cache unificata** (istruzioni e dati nella stessa cache) e una **cache specializzata** (istruzioni e dati in cache separate), quest'ultima più comune oggi per permettere accessi paralleli e perché le istruzioni non necessitano di riscrittura.

Infine, è comune avere più livelli di cache: una primaria integrata nel chip, una secondaria sullo stesso circuito della CPU, e una terziaria più lontana.

(pagine riassunte: 3.25)
### 2.2.6 - Assemblaggio e tipi di memoria
A partire dalle prime memorie basate su semiconduttori e fino ai primi anni ’90, la memoria era prodotta, venduta e installata in un unico chip. Spesso i primi PC erano dotati di prese nelle quali era possibile inserire chip di memoria aggiuntivi, se e quando l’utente ne avesse avuto bisogno.

A partire dall’inizio degli anni ’90 vari chip, in genere di 8 o 16 elementi, sono montati su una piccola scheda a circuiti stampati venduta singolarmente. Essa è chiamata **SIMM** (Single Inline Memory Module) oppure **DIMM** (Dual Inline Memory Module), a seconda che abbia i connettori allineati su uno o su due lati della scheda. Le SIMM, poco utilizzate ai giorni nostri, hanno un connettore laterale con 72 contatti e trasferiscono 32 bit per ciclo di clock; le DIMM invece hanno generalmente connettori con 120 contatti su ogni lato, per un totale di 240 contatti, e trasferiscono 64 bit per ciclo di clock. Le DIMM più diffuse oggi sono le DDR3, la terza versione delle memorie a doppia velocità (Double Data Rate).

Nei calcolatori portatili si usano DIMM più piccole, chiamate **SO-DIMM** (Small Outline DIMM ). Alle SIMM e alle DIMM è possibile aggiungere un bit di parità o la correzione d’errore, ma, dato che la frequenza media degli errori di un modulo è di uno ogni 10 anni, spesso nella maggior parte dei calcolatori ordinari le funzionalità di rilevazione e correzione degli errori non sono presenti.

(pagine riassunte: 1)
## 2.3 - Memoria secondaria
La domanda se la memoria centrale possa mai essere troppo grande è inutile: non lo sarà mai.

Con il progredire della tecnologia, la nostra capacità di archiviare informazioni cresce a ritmi esponenziali. Basti pensare alla digitalizzazione del patrimonio della Biblioteca del Congresso: 50 milioni di libri, immagini e testo che richiederebbero 100 Terabyte di memoria, una quantità enorme oggi, ma che potrebbe diventare gestibile in futuro.

Se per ora queste quantità di dati sono inaccessibili alla memoria centrale, il futuro ci riserva tecnologie che le renderanno fruibili.

La nostra "fame di memoria" è inarrestabile e la tecnologia continuerà a evolversi per soddisfarla.
### 2.3.1 - Gerarchie di memoria
La soluzione che viene tradizionalmente adottata per memorizzare una gran mole di dati consiste nell'organizzare gerarchicamente la memoria. Nella parte altra della gerarchia si trovano i registri della CPU, ai quali si può accedere alla stessa velocità della CPU. Più sotto vi è la moria cache, la cui dimensione può variare da 32 KB fino ad alcuni MB. La memoria centrale è il passo successivo e la sua dimensione è compresa tra 1 e centinaia di GB. Troviamo poi i dischi magnetici, la vera forza lavoro della memorizzazione permanente. Infine ci sono i nastri magnetici e i dischi ottici usati per l'archiviazione.

Muovendosi verso il basso della gerarchia aumentano tre parametri chiave. Innanzitutto, il tempo di accesso diventa via via più grande. Secondariamente la capacità di memorizzazione aumenta man mano si scende verso il basso. In terzo luogo, scendendo lunga la gerarchia diminuiscono anche i costi unitari.

(pagine riassunte: 1)
### 2.3.2 - Dischi magnetici
Un disco magnetico è composto da piatti di alluminio rivestiti di materiale magnetico, con diametri variabili tra 3 e 9 cm. La testina del disco, sospesa su un cuscinetto d'aria, scrive e legge i dati magnetizzando la superficie del disco. Le sequenze circolari di bit scritti durante una rotazione completa del disco sono chiamate **tracce**, suddivise in **settori** di lunghezza fissa, tipicamente 512 byte. Ogni settore è preceduto da un **preambolo** per la sincronizzazione della testina e seguito da un codice di correzione degli errori, come il codice **Reed-Solomon**. Tra i settori ci sono piccoli spazi chiamati **spazi tra settori**.

I dischi hanno bracci mobili che posizionano la testina su diverse tracce concentriche. La densità lineare dei bit lungo le tracce è diversa dalla densità radiale. I dischi ad alta densità usano la **registrazione perpendicolare**, che permette una maggiore densità di dati. Alcuni dischi sono sigillati per prevenire la polvere, noti come **dischi Winchester**, e oggi chiamati hard disk.

I dischi con più piatti impilati verticalmente formano cilindri di tracce allineate. Le prestazioni dei dischi dipendono dal **tempo di ricerca** (tra 5 e 10 ms), dalla **latenza rotazionale** (tra 3 e 6 ms), e dal tempo di trasferimento dei dati (13-16 ns per settore di 512 byte). La lettura di settori sparsi è inefficiente a causa di questi tempi.

La differenza tra **burst rate** e **sustained rate** di un disco è significativa: il burst rate è la velocità di lettura immediata, mentre il sustained rate è la velocità media di lettura, che include i tempi di ricerca e latenza.

Ogni disco ha un controllore dedicato che gestisce comandi, movimento del braccio, rilevamento e correzione degli errori, conversione dei dati e bufferizzazione. Il controllore gestisce anche i settori con errori, sostituendoli con settori liberi riservati per questo scopo.

(pagine riassunte: 3.5)
### 2.3.3 - Dischi IDE
I dischi dei moderni personal computer sono l'evoluzione di quelli presenti nei PC XT della IBM. Il sistema operativo leggeva e scriveva sul disco utilizzando il **BIOS**, situato in una memoria di sola lettura integrata nel PC, che lanciava le istruzioni necessarie per il trasferimento dei dati.

Con l'introduzione delle unità **IDE** (_Integrated Drive Electronics_) negli anni '80, il controllo divenne integrato con l'unità stessa anziché essere su una scheda separata. Tuttavia, le chiamate al BIOS per l'indirizzamento dei settori rimasero invariate, basate su una geometria specifica. Questo causò problemi di retrocompatibilità e rese necessaria la remappatura virtuale della geometria reale.

Le unità IDE evolsero in unità **EIDE** (_Extended_ IDE), che supportavano anche l'indirizzamento **LBA** (_Logical Block Addressing_), superando i limiti precedenti. Tuttavia, questo nuovo schema comportò un nuovo collo di bottiglia.

Le unità e i controllori EIDE migliorarono ulteriormente. I controllori potevano avere due canali, ciascuno con un disco primario e uno secondario. Lo standard EIDE si evolse in **ATA-3** (AT attachment), poi in **ATAPI-4** (ATA Packet Interface) con velocità fino a 33 MB/s, e successivamente in ATAPI-5 con velocità fino a 66 MB/s. Con ATAPI-6, il limite dei 128 GB imposto dagli indirizzi LBA a 28 bit divenne problematico e fu esteso a 48 bit.

ATAPI-7 introdusse l'interfaccia **serial ATA**, trasferendo i dati in modo seriale su un connettore a 7 pin. Questo standard prometteva velocità fino a 1.5 GB/s e riduceva il consumo energetico, diventando importante anche nei portatili.

(pagine riassunte: 1.75)
### 2.3.4 - Dischi SCSI
Gli hard disk SCSI offrono una velocità di trasferimento dati superiore rispetto agli IDE, con un'interfaccia diversa. La tecnologia SCSI, nata dalle origini dei floppy disk, è stata standardizzata nel 1986 come Small Computer System Interface (**SCSI**). Le versioni successive hanno garantito incrementi di velocità, con la wide SCSI a 16 bit diventata lo standard attuale.

Questi dischi sono predominanti nelle workstation e nei server di fascia alta, soprattutto nei sistemi RAID, grazie alla loro velocità. Lo SCSI non è solo un'interfaccia per gli hard disk, ma anche un bus che supporta fino a sette dispositivi, inclusi hard disk, CD-ROM, scanner e altro. Ogni dispositivo SCSI ha un ID unico e due connettori.

I cavi SCSI sono progettati per garantire elevata immunità al rumore, con 50 contatti di cui 25 dedicati alla terra. Sono disponibili versioni a 8 e 16 bit, quest'ultima richiede un cavo aggiuntivo per i segnali. La lunghezza dei cavi consente l'uso di dispositivi esterni come hard disk e scanner.

I controllori SCSI possono agire sia come iniziatori che come destinatari di comunicazione. Di solito, il controllore lancia comandi ai dispositivi, coordinando l'accesso al bus quando più dispositivi tentano di utilizzarlo contemporaneamente.

(pagine riassunte: 1.5)
### 2.3.5 - RAID
Negli ultimi dieci anni, le prestazioni delle CPU sono aumentate esponenzialmente, raddoppiando circa ogni 18 mesi, mentre i dischi non hanno seguito lo stesso ritmo, causando un divario significativo tra le prestazioni della CPU e quelle dei dischi. Per affrontare questo problema, si è adottata l'elaborazione parallela per le CPU e l'I/O parallelo per i dischi, portando alla creazione dei sistemi **RAID** (Redundant Array of Independent Disks).

Il concetto di RAID implica l'uso di un insieme di dischi vicino al server, gestito da un controllore RAID che distribuisce i dati tra i vari dischi, migliorando così le prestazioni e l'affidabilità rispetto a un singolo disco **SLED** (Single Large Expensive Disk). I RAID appaiono al sistema operativo come un singolo disco, ma distribuiscono i dati su più unità, permettendo operazioni parallele.

Patterson e i suoi colleghi hanno definito diversi livelli di RAID, da 0 a 5:

-  **RAID 0**: Distribuisce i dati in "strip" (strisce) su più dischi in modalità round robin. Funziona bene con richieste di grandi dimensioni ma male con richieste di singoli settori.
-  **RAID 1**: Duplica tutti i dischi, utilizzando dischi di backup. Offre alta affidabilità e può distribuire le letture su più dischi.
-  **RAID 2**: Utilizza codici di Hamming su parole di dati, con bit di parità aggiunti per la correzione degli errori. È stato usato nel calcolatore Thinking Machines CM-2.
-  **RAID 3**: Simile al RAID 2 ma semplificato, con un solo disco dedicato ai bit di parità. Permette la correzione degli errori in caso di guasto di un disco.
-  **RAID 4**: Come RAID 0 ma con una "strip" di parità su un disco aggiuntivo. Il disco di parità può diventare un collo di bottiglia.
-  **RAID 5**: Distribuisce i bit di parità su tutti i dischi in modalità round robin, evitando il collo di bottiglia del RAID 4 ma complicando la ricostruzione dei dati in caso di guasto di un disco.

(pagine riassunte: 4)
### 2.3.6 - Dischi a stato solido
I dischi basati su memoria flash non volatile, noti come SSD (_Solid State Drive_), stanno diventando sempre più popolari come alternativa ad alta velocità rispetto ai tradizionali dischi magnetici. Gli SSD utilizzano celle di memoria flash a stato solido, costituite da transistor flash speciali con una porta flottante che può essere caricata e scaricata mediante alte tensioni. Questa struttura consente agli SSD di avere prestazioni superiori ai dischi magnetici, con tempi di ricerca pari a zero e nessuna parte in movimento, rendendoli ideali per i computer portatili.

Tuttavia, gli SSD hanno alcuni svantaggi. Il costo per gigabyte è significativamente più alto rispetto ai dischi magnetici, rendendoli adatti solo per applicazioni specifiche o non sensibili ai costi. Inoltre, le celle flash degli SSD hanno una durata limitata, poiché possono essere scritte solo circa 100.000 volte prima di guastarsi. Questo è dovuto al danno progressivo causato dal processo di iniezione di elettroni nella porta flottante.

Per mitigare questo problema, gli SSD utilizzano una mappa logica dei blocchi per riassegnare i blocchi di destinazione a quelli meno utilizzati, il che comporta un overhead nel salvataggio dei dati. Alcuni SSD utilizzano celle flash multilivello per memorizzare più bit per cella, aumentando la capacità di memorizzazione. Queste celle possono mantenere fino a quattro livelli di carica, consentendo la memorizzazione di due bit per ogni cella flash.

(pagine riassunte: 2)
### 2.3.7 - CD-ROM
I dischi ottici, sviluppati inizialmente per registrare programmi televisivi, sono oggi utilizzati ampiamente come dispositivi di memorizzazione per computer, grazie alla loro grande capacità e basso costo. Sono comuni per distribuire software, libri, film e dati vari, oltre che per creare copie di backup degli hard disk.

Nel 1980, Philips e Sony svilupparono il CD (Compact Disc), che sostituì rapidamente i dischi in vinile per la musica. I dettagli tecnici del CD furono pubblicati nello Standard Internazionale IS 10149, noto come **Libro rosso** (Red Book). La standardizzazione internazionale delle specifiche di dischi e lettori consentì l'interoperabilità tra CD e lettori di diversi produttori.

La produzione di un CD coinvolge l'uso di un laser infrarosso ad alta potenza per creare buchi (pit) su un disco di vetro fotosensibile, creando uno stampo per il policarbonato liquido. I pit e le aree non incise (land) consentono la lettura dei dati tramite un diodo laser a bassa potenza che distingue tra pit e land. I dati sono codificati come transizioni pit/land o land/pit.

Nel 1984, Philips e Sony pubblicarono il **Libro giallo** (Yellow Book), definendo lo standard per i CD-ROM (Compact Disc-Read Only Memory), compatibili con i CD audio per dimensioni e metodi di produzione. Questo standard includeva miglioramenti per la correzione degli errori, fondamentali per la memorizzazione affidabile dei dati dei computer.

Il **Libro giallo** definisce due modalità di dati. Il **Modo 1** comprende 16 byte di preambolo, 2048 byte di dati e 288 byte di codice di correzione degli errori. Il **Modo 2** combina dati e campi ECC in un campo dati di 2336 byte, adatto per applicazioni come audio e video che non richiedono correzione degli errori.

Nel 1986, Philips introdusse il **Libro verde** (Green Book), che aggiunse grafica e la possibilità di combinare audio, video e dati in un singolo settore per i CD-ROM multimediali.

Per l'uso universale dei CD-ROM su diversi computer, fu creato il file system **High Sierra**, diventato lo Standard Internazionale ISO 9660. Questo file system ha tre livelli: il **livello 1** supporta nomi di file con un massimo di 8 caratteri più un'estensione di 3 caratteri, con file contigui; il **livello 2** permette nomi di file fino a 32 caratteri; il **livello 3** consente file non contigui.

(pagine riassunte: 4)
### 2.3.8 - CD-registrabili
Inizialmente, l'attrezzatura per produrre i master dei CD-ROM era molto costosa, ma a partire dalla metà degli anni '90, i masterizzatori CD divennero comuni e accessibili. Questi dispositivi, noti come **CD-R**, sono simili ai CD-ROM ma con una scanalatura di 0,6 mm per guidare il laser durante la scrittura. I primi CD-R erano dorati a causa dell'uso dell'oro per lo strato riflettente, a differenza dell'alluminio utilizzato nei CD-ROM.

Il **Libro arancione**, pubblicato nel 1989, definiva i CD-R e il formato **CD-ROM XA**, che permetteva la scrittura incrementale sui CD-R, consentendo di aggiungere settori in momenti diversi. Un insieme di settori scritti in una volta è chiamato **traccia del CD-ROM**.Questo metodo crea tracce multiple, ciascuna con il proprio **VTOC** (Volume Table of Contents), per gestire i file presenti. Tuttavia, i CD-ROM multisessione non sono leggibili dai lettori standard di CD audio, che si aspettano una singola VTOC all'inizio del disco.

(pagine riassunte: 2.5)
### 2.3.9 - CD-riscrivibili
Una tecnologia oggi disponibile è quella dei **CD-RW** (CD-ReWritable), che usano supporti della stessa dimensione dei CD-R. I CD-RW però, invece di usare la cianina o la ftalocianina per lo strato sul quale registrare, impiegano una lega di argento, indio, antimonio e tellurio. Questa lega ha due stati stabili, quello cristallino e quello amorfo, con diverse proprietà riflettenti. 

I lettori CD-RW utilizzano laser che funzionano a tre potenze distinte. 
Alla potenza più elevata il laser scioglie la lega portandola dallo stato cristallino altamente riflettente a quello amorfo, dotato di una riflettività minore e che rappresenta un pit. 
Alla potenza media la lega si scioglie e si ricompone nello stato cristallino naturale per tornare a rappresentare un land. 
Alla potenza più bassa è possibile rilevare lo stato del materiale (per operazioni di lettura),senza però indurre alcuna trasformazione.

(pagine riassunte: 0.5)
### 2.3.10 - DVD
Il formato base dei CD/CD-ROM è stato definito intorno al 1980, quando Hollywood cercava di sostituire le videocassette analogiche. Questa esigenza, combinata con l'avanzamento tecnologico e la domanda di tre mercati ricchi, portò allo sviluppo del DVD, inizialmente acronimo di Digital Video Disk, poi rinominato Digital Versatile Disk. I DVD, simili ai CD, sono creati iniettando policarbonato in uno stampo, con *pit* e *land* sulla superficie letti da un laser rosso. Le innovazioni dei DVD includono *pit* più piccoli e una spirale più stretta.

Esistono quattro formati di DVD per soddisfare diverse esigenze di capacità:
1. Singolo lato, singolo strato (4.7 GB)
2. Singolo lato, doppio strato (8.5 GB)
3. Doppio lato, singolo strato (9.4 GB)
4. Doppio lato, doppio strato (17 GB)

La tecnologia a doppio strato utilizza uno strato riflettente inferiore coperto da uno semiriflettente, permettendo al laser di leggere su due livelli differenti. Il livello inferiore richiede *pit* e *land* leggermente più grandi, riducendo leggermente la capacità rispetto allo strato superiore.

Tra le funzionalità standard dei DVD vi sono l'omissione in tempo reale delle scene scabrose, l'audio a sei canali e il supporto per il *Pan-and-Scan*.

(pagine riassunte: 2.25)
### 2.3.11 - Blu-Ray
Il DVD è stato appena introdotto e già il suo successore minaccia di renderlo obsoleto; si tratta del **Blu-Ray**, chiamato in questo modo poiché utilizza un laser blu invece di quello rosso dei DVD. I laser blu hanno una lunghezza d’onda più piccola di quelli rossi, il che permette una messa a fuoco più accurata e l’uso di pii e land più piccoli. Ci si aspetta che alla fine Blu-Ray sostituirà i CD-ROM e i DVD, ma questo passaggio potrebbe richiedere degli anni.

(pagine riassunte: 0.25)
## 2.4 - Input/Output
Come sappiamo un calcolatore è composto da tre componenti principali: la CPU, le memorie e i dispositivi di I/O. Finora abbiamo analizzato la CPU e le memorie; adesso passiamo allo studio dei dispositivi di I/O e alla loro connessione con il resto del sistema.
### 2.4.1 - Bus
La configurazione tipica di un computer consiste in una scatola metallica contenente una **scheda madre**. Questa scheda ospita il chip della CPU, slot per moduli DIMM e altri chip di supporto, oltre a un bus lungo la sua lunghezza con prese per i connettori delle schede di I/O.

Ogni dispositivo di I/O ha due componenti principali: il **controllore**, che contiene la maggior parte dell'elettronica, e il dispositivo stesso, come un lettore di dischi. Il controllore può essere integrato sulla scheda madre o situato su una scheda aggiuntiva. Ad esempio, il controllore video spesso si trova su una scheda aggiuntiva per offrire opzioni avanzate come acceleratori hardware e memoria aggiuntiva. Il controllore gestisce il dispositivo di I/O e il suo accesso al bus, eseguendo operazioni di **Direct Memory Access (DMA)**, che permette di leggere e scrivere dati in memoria senza l'intervento della CPU. Una volta completato il trasferimento, il controllore genera un **interrupt** che fa sospendere alla CPU il programma corrente per eseguire una speciale procedura chiamata **gestore dell'interrupt**.

Se la CPU e un controllore di I/O cercano di usare il bus contemporaneamente, un **arbitro del bus** decide i turni, generalmente dando priorità alle periferiche di I/O per evitare perdite di dati. Questo processo, noto come **furto di cicli**, può rallentare le prestazioni del computer.

Il bus **ISA (Industry Standard Architecture)**, utilizzato nei vecchi PC, continuò ad essere usato da molti produttori di cloni e periferiche, anche dopo l'introduzione del nuovo e più veloce bus del PS/2 di IBM. Questo portò IBM alla situazione paradossale di essere l'unico produttore di PC non compatibili con lo standard IBM.
#### 2.4.1.1 - I bus PCI e PCIe
Nonostante le pressioni di mercato per mantenere lo status quo, i vecchi bus divennero troppo lenti, portando allo sviluppo di macchine con più bus, come il vecchio bus ISA o il suo successore retrocompatibile **EISA** (Extended ISA). Alla fine, il bus **PCI** (Peripheral Component Interconnect) di Intel prevalse.

Nel mondo dei computer, la velocità è sempre un problema e anche i bus PCI furono ritenuti troppo lenti, portando alla nascita dei bus PCIe. I computer moderni supportano sia PCI che PCIe, consentendo la connessione di dispositivi nuovi e veloci al bus PCIe e dispositivi più vecchi e lenti al bus PCI.

Il PCIe rappresenta una svolta rispetto al PCI, non essendo nemmeno un bus tradizionale, ma una rete punto a punto che utilizza linee seriali di bit e commutazione di pacchetto, simile a Internet.

Le principali differenze del PCIe includono:
1. **Connessione seriale**: la trasmissione avviene su una linea di 1 bit piuttosto che 8, 16, 32 o 64 bit, evitando problemi di *skew* che limitano la velocità in connessioni parallele.
2. **Comunicazioni punto a punto**: quando la CPU comunica con un dispositivo, invia un pacchetto che passa attraverso la root complex sulla scheda madre e talvolta attraverso uno switch. Questo sistema ricorda lo sviluppo di Ethernet, passata da trasmissioni in broadcast a comunicazioni punto a punto tramite switch.

(pagine riassunte: 4.5)
### 2.4.2 - Terminali
Esistono diverse tipologie di dispositivi di I/O. I terminali sono costituiti da due componenti principali: la tastiera e il monitor. Nei mainframe, questi componenti sono spesso integrati in un unico dispositivo collegato al calcolatore principale tramite una linea seriale o un cavo telefonico. Questi terminali sono ancora ampiamente utilizzati nelle prenotazioni delle compagnie aeree, nelle banche e in altri sistemi basati su mainframe. Nei personal computer, invece, tastiera e monitor sono dispositivi separati, anche se la tecnologia utilizzata è sostanzialmente la stessa.

(pagine riassunte: 0.25)
#### 2.4.2.1 - Tastiere
La pressione di un tasto di un PC genera un interrupt che stimola una parte del sistema operativo, chiamata gestore dell’interrupt della tastiera. Questa routine, leggendo un registro hardware della tastiera, ricava il numero associato al tasto premuto. Anche quando si rilascia un tasto viene generato un interrupt. La gestione di sequenze multi-tasto che coinvolgono i tasti SHIFT, CTRL e ALT è fatta interamente via software.

(pagine riassunte: 0.5)
#### 2.4.2.2 - Touch screen
Nonostante le tastiere continuino ad essere utilizzate, un nuovo dispositivo di input ha guadagnato popolarità: il touch screen. Tipici dispositivi touch includono touchpad nei portatili e schermi di smartphone o tablet. I touch screen più comuni sono di tipo resistivo, capacitivo o a infrarossi.

**Touch screen a infrarossi**: Utilizzano trasmettitori di raggi infrarossi e ricevitori disposti ai lati dello schermo. Quando un oggetto opaco interrompe i fasci di luce, il ricevitore rileva la caduta del segnale e comunica le coordinate al sistema operativo.

**Touch screen resistivi**: Composti da due strati, uno superiore flessibile con fili orizzontali e uno inferiore con fili verticali. La pressione su un punto dello schermo fa sì che i fili dei due strati si tocchino, permettendo di localizzare l’area premuta. Funzionano bene con un solo dito, ma hanno difficoltà con più dita contemporaneamente.

**Touch screen capacitivi a proiezione**: Utilizzati in gran parte degli smartphone e tablet, particolarmente quelli a **mutua capacitanza**, sono in grado di riconoscere il tocco di più dita contemporaneamente, abilitando gesti come espansione e pizzicamento. Questi schermi non reagiscono a oggetti non conduttivi come penne o dita coperte da guanti. Durante l’uso, le tensioni applicate ai "fili" dello schermo rilevano i cambiamenti di capacitanza causati dal tocco delle dita.

(pagine riassunte: 1.75)
#### 2.4.2.3 - Schermi piatti
I primi schermi dei computer utilizzavano tubi catodici (CRT) simili a quelli delle vecchie televisioni. Oggi, la tecnologia più comune è quella degli schermi a cristalli liquidi (LCD).

Gli **LCD** utilizzano cristalli liquidi, che sono molecole organiche viscose con proprietà ottiche che possono essere controllate elettricamente. Uno schermo LCD è composto da due lastre di vetro parallele contenenti cristalli liquidi, con elettrodi trasparenti collegati a ciascuna lastra. Una luce retroilluminante illumina lo schermo, mentre i campi elettrici creati dagli elettrodi regolano l'intensità della luce che passa attraverso i cristalli liquidi, permettendo di visualizzare immagini.

Un esempio di schermo LCD è lo schermo **TN** (*Twisted Nematic*), dove le molecole del cristallo liquido si allineano lungo solchi orizzontali e verticali su due lastre, causando una torsione di 90 gradi. Questo tipo di schermo può usare due schemi per l'applicazione della tensione: 

1. **Schermi a matrice passiva**: Economici, utilizzano fili paralleli per controllare i pixel.
2. **Schermi a matrice attiva**: Più costosi ma di qualità superiore, utilizzano un piccolo elemento di commutazione, chiamato **thin film transistor** (TFT), per ogni pixel. La maggior parte dei laptop e dei monitor a schermo piatto usano la tecnologia TFT.

Nuove tecnologie stanno emergendo tra cui gli **schermi OLED** (*Organic Light Emitting Diode*), che utilizzano molecole organiche caricate elettricamente tra due elettrodi.

(pagine riassunte: 2.25)
#### 2.4.2.4 - RAM della scheda video
La maggior parte dei monitor viene aggiornata dalle 60 alle 100 volte al secondo utilizzando una memoria speciale chiamata **Video RAM** (VRAM) situata sulla scheda del controllore dello schermo. Questa memoria contiene una o più bitmap che rappresentano l'immagine dello schermo. Ad esempio, per uno schermo con risoluzione 1920x1080 pixel, la VRAM deve contenere 1920x1080 valori, uno per ogni pixel.

In uno schermo standard, ogni pixel è rappresentato da un valore RGB (Red, Green, Blue) composto da 3 byte, uno per ciascuna componente del colore del pixel. Pertanto, una VRAM per uno schermo 1920x1080 con 3 byte per pixel richiede oltre 6,2 MB di spazio.

Per ridurre i requisiti di memoria e il tempo di elaborazione della CPU, alcuni computer utilizzano un unico numero a 8 bit per rappresentare il colore desiderato, utilizzando una **tavolozza** (color palette) hardware con 256 elementi, ciascuno dei quali memorizza un valore RGB a 24 bit. Questo approccio, chiamato **colore indicizzato**, riduce i requisiti di memoria della VRAM di due terzi, ma limita la visualizzazione a 256 colori simultanei.

Gli schermi basati su bitmap richiedono una notevole larghezza di banda.

(pagine riassunte: 0.75)
### 2.4.3 - Mouse
Nel tempo, l'uso dei computer è diventato sempre più accessibile a persone con conoscenze tecniche limitate. Inizialmente, i computer erano dotati di interfacce a linea di comando, considerate poco intuitive dagli utenti non specializzati. Per migliorare l'usabilità, molti produttori hanno sviluppato interfacce punta-e-clicca, introducendo il **mouse** come strumento principale.

Il mouse, un piccolo dispositivo di plastica, muove un puntatore sullo schermo in corrispondenza del movimento sul tavolo. Ha uno, due o tre pulsanti per selezionare elementi e voci di menu.

Esistono tre tipi di mouse:
1. **Meccanico**: Utilizza due rotelle di gomma disposte perpendicolarmente per misurare il movimento. Le rotelle guidano potenziometri che calcolano la distanza percorsa.
2. **Ottico**: Senza rotelle o pallina, utilizza un **LED** e un fotorilevatore. I primi modelli richiedevano un tappetino con una griglia di linee. I moderni mouse ottici illuminano la superficie sottostante con un LED e una fotocamera registra immagini circa 1000 volte al secondo.
3. **Opto-meccanico**: Combina elementi meccanici e ottici, con una pallina che fa ruotare due cilindretti perpendicolari collegati a codificatori con fori. Il movimento del mouse è rilevato attraverso impulsi di luce che passano attraverso i fori.

Il software del computer traduce i movimenti del mouse in coordinate sullo schermo, permettendo agli utenti di selezionare elementi semplicemente posizionando il puntatore e premendo un pulsante.

(pagine riassunte: 2)
### 2.4.4 - Controller per videogiochi
Grazie alle molteplici esigenze degli utilizzatori di videogiochi il mercato delle console di gioco ha sviluppato dispositivi di input specializzati.
#### 2.4.4.1 - Il controller Wiimote
Il **Wiimote** interagisce in tempo reale con la console di gioco tramite un sistema bluetooth. Grazie ai sensori di movimento, il Wiimote può rilevare movimenti in tre dimensioni e, se puntato verso il televisore, offre una precisa funzione di puntamento.

Il monitoraggio dei movimenti tridimensionali è effettuato tramite un accelerometro a tre assi. Ogni massa dell'accelerometro risponde all'accelerazione lungo il proprio asse, modificando la capacitanza rispetto a una parete fissa di metallo. Misurando queste variazioni, si rileva l'accelerazione lungo le tre direzioni.

Tuttavia, gli accelerometri, pur efficaci nel rilevare movimenti tridimensionali, non sono sufficientemente precisi per controllare un puntatore sullo schermo televisivo a causa di un margine di errore che aumenta nel tempo.

Per una rilevazione più precisa, il Wiimote utilizza tecnologie di computer vision. Una **sensor bar** posta sopra il televisore contiene LED a distanza fissa. Il Wiimote, dotato di una videocamera, può determinare la distanza e l'orientamento rispetto allo schermo osservando questi LED. La distanza tra i LED nel campo visivo del Wiimote è proporzionale alla distanza del controller dalla sensor bar, e la posizione dei LED indica la direzione di puntamento. Monitorando continuamente questa orientazione, il Wiimote offre una capacità di puntamento precisa senza gli errori degli accelerometri.
#### 2.4.4.2 - Il controller Kinect
Il dispositivo Kinect utilizza tecniche di computer vision per determinare le interazioni dell'utente con la console di gioco. Il suo funzionamento si basa sulla rilevazione della posizione dell'utente nella stanza, dell'orientamento e dei movimenti del corpo.

La capacità di rilevazione di Kinect dipende da una fotocamera di profondità e da una videocamera. La fotocamera di profondità misura la distanza degli oggetti nel campo visivo emettendo un fascio di raggi laser infrarossi e catturando i riflessi con una camera a infrarossi.

L'informazione sulla profondità viene combinata con i dati strutturali della videocamera per creare una mappa di profondità della scena. Questa mappa è elaborata da un algoritmo di computer vision per localizzare le persone nella stanza e analizzare l'orientamento e i movimenti del loro corpo.

(pagine riassunte: 2)
### 2.4.5 - Stampanti
I computer spesso dispongono di stampanti per poter stampare il proprio lavoro, ne parleremo in questo paragrafo.
#### 2.4.5.1 - Stampanti laser
Dopo l'invenzione della stampa, il progresso più significativo nella riproduzione dei testi è rappresentato dalla **stampante laser**. Questo dispositivo offre alta qualità dell'immagine, eccellente flessibilità, grande velocità e costi contenuti.

Il cuore della stampante laser è un tamburo rotante caricato elettricamente e rivestito di materiale fotosensibile. Un laser, modulato per produrre regioni luminose e scure, disegna l'immagine desiderata sul tamburo, scaricando le aree colpite dalla luce. Il tamburo, ruotando, passa attraverso il toner, che si attacca alle aree caricate elettricamente. Il toner viene poi trasferito su un foglio di carta, creando l'immagine finale.

Questo complesso processo combina fisica, chimica, meccanica e ottica. Alcuni produttori vendono meccanismi completi chiamati **motori di stampa** che comprendono tutte queste fasi.

Le stampanti laser utilizzano linguaggi di programmazione specializzati come PCL di HP, PostScript di Adobe o PDF per descrivere come devono essere stampate le pagine.

Per riprodurre la scala dei grigi, viene usata la tecnica dei mezzitoni, che divide l'immagine in celle di 6x6 pixel. Il numero di pixel neri in ogni cella determina la percezione di tonalità di grigio. La risoluzione effettiva dell'immagine si riduce a 100 celle per pollice, misurata in **lpi** (linee per pollice).
#### 2.4.5.2 - Stampanti a colori
Sebbene la maggior parte delle stampanti laser sia monocromatica, le stampanti laser a colori stanno diventando sempre più comuni. Le immagini a colori possono essere viste in due modi: tramite luce trasmessa (come sui monitor) o tramite luce riflessa (come nelle fotografie su carta). 

Le immagini su monitor sono create combinando i tre colori primari additivi: rosso, verde e blu (RGB). Al contrario, le immagini su carta sono create sovrapponendo i tre colori primari sottrattivi: ciano, magenta e giallo (CMY). Tuttavia, poiché è difficile ottenere un nero puro con questi tre colori, le stampanti a colori usano anche il nero (K), risultando nel sistema CMYK.

Il **gamut** o **gamma dei colori** è l'insieme completo dei colori che un dispositivo può rappresentare. Né i monitor né le stampanti possono riprodurre tutti i colori del mondo reale. I monitor utilizzano luce trasmessa e hanno un fondo nero, mentre le stampanti usano luce riflessa e hanno un fondo chiaro. Inoltre, i monitor generano 256 intensità per colore e le stampanti usano i mezzitoni, rendendo complessa la conversione accurata delle immagini dal monitor alla stampa. Le gamme di colori RGB e CMYK sono diverse, complicando ulteriormente questa conversione.
#### 2.4.5.3 - Stampanti a getto d'inchiostro
Per le stampe casalinghe a basso costo, molti preferiscono le **stampanti a getto d’inchiostro**. La testina di stampa mobile, che contiene le cartucce di inchiostro, si muove orizzontalmente lungo la carta spruzzando inchiostro attraverso piccoli ugelli. Le goccioline di inchiostro hanno un volume di circa 1 picolitro. Esistono due tipi principali di stampanti a getto d’inchiostro: *piezoelettriche* e *termiche*.

Le stampanti piezoelettriche utilizzano un cristallo particolare che si deforma quando gli viene applicata una tensione, spruzzando così una goccia di inchiostro. Le stampanti termiche, invece, hanno una resistenza che riscalda rapidamente l’inchiostro fino a farlo evaporare, formando una bolla di gas che spruzza l’inchiostro attraverso l'ugello.

Per ottenere risultati migliori, è importante usare carte e inchiostri speciali. Ci sono due tipi di inchiostro: a **base di coloranti** e a **pigmenti**. Gli inchiostri a base di coloranti producono colori luminosi e fluiscono facilmente, ma tendono a sbiadire sotto la luce solare. Gli inchiostri a base di pigmenti contengono particelle solide che non sbiadiscono facilmente, ma sono meno luminosi e possono bloccare gli ugelli, necessitando di una pulizia periodica.
#### 2.4.5.4 - Stampanti speciali
Oltre alle comuni stampanti laser e a getto d'inchiostro, esistono altri tipi di stampanti utilizzate in contesti che richiedono particolari requisiti di qualità del colore e costi. Le **stampanti a inchiostro solido** usano blocchi di inchiostro ceroso che vengono sciolti e spruzzati sulla carta, dove si solidificano e si fondono grazie a rulli rigidi. Queste stampanti possono richiedere fino a 10 minuti per riscaldare l'inchiostro all'accensione.

Le **stampanti a getto di cera** impiegano un nastro rivestito di inchiostri cerosi, che vengono fusi e trasferiti sulla carta come pixel tramite elementi riscaldanti, utilizzando il sistema CMYK.

Le **stampanti a sublimazione** passano direttamente dallo stato solido a quello gassoso senza passare per lo stato liquido. Utilizzano una testina di stampa con elementi riscaldanti programmabili per trasferire coloranti CMYK sulla carta.

Infine, le **stampanti termiche** impiegano una testina con piccoli aghi che si scaldano rapidamente quando attraversati da una corrente elettrica. Questi aghi disegnano punti sulla carta termosensibile, creando l'immagine desiderata.

(pagine riassunte: 5)
### 2.4.6 - Apparecchiature per telecomunicazioni
Al giorno d’oggi la maggior parte dei calcolatori è connessa a una rete di calcolatori, che spesso è Internet.
#### 2.4.6.1 - Modem
L'uso diffuso dei computer ha reso comune la necessità di comunicare tra loro. Le linee telefoniche, progettate per la voce, non sono adatte a trasmettere i segnali digitali dei computer senza distorsione. Per risolvere questo problema, si utilizza un segnale sinusoidale chiamato **portante**, che può essere trasmesso con minore distorsione. Variando l'ampiezza, la frequenza o la fase di questo segnale, è possibile trasmettere dati digitali. Questo processo è noto come **modulazione** e i dispositivi che lo realizzano si chiamano modem, da MOdulator DEModulator.

Esistono diversi tipi di modulazione:
- **Modulazione d'ampiezza**: utilizza due tensioni diverse per rappresentare 0 e 1.
- **Modulazione di frequenza**: mantiene una tensione costante, cambiando la frequenza per rappresentare 0 e 1.
- **Modulazione di fase**: mantiene costanti ampiezza e frequenza, invertendo la fase di 180 gradi per i cambiamenti di bit. In versioni più sofisticate, la fase cambia di 45, 135, 225 o 315 gradi, rappresentando 2 bit per intervallo, noto come **modulazione a coppia di bit**.

I modem moderni operano a 56 Kbps, combinando diverse tecniche di modulazione. Questi modem sono **full-duplex**, capaci di trasmettere simultaneamente in entrambe le direzioni. I modem che trasmettono in una sola direzione per volta sono **half-duplex**, mentre le linee che trasmettono solo in una direzione sono **simplex**.
#### 2.4.6.2 - Digital subscriber line
Quando le società telefoniche raggiunsero la velocità di 56 Kbps, l'industria della TV via cavo offriva già velocità superiori a 10 Mbps e la TV satellitare raggiungeva i 50 Mbps. Con l'aumento dell'importanza dell'accesso a Internet, le società telefoniche, note come **telcos**, dovettero offrire un servizio più competitivo rispetto alle linee *dial-up*. La loro risposta fu l'introduzione di servizi a **banda larga** (broadband), inclusi i servizi **xDSL** (*Digital Subscriber Line*), tra cui il più diffuso è l'**ADSL** (Asymmetric DSL).

La lentezza dei modem tradizionali è dovuta all'ottimizzazione del sistema telefonico per la voce umana, con il **ciclo locale** limitato a 3000 Hz, riducendo la velocità di trasferimento dati tramite un filtro nell'ufficio della compagnia telefonica. L'ADSL divide il ciclo locale in 256 canali di 4312,5 Hz ciascuno: il canale 0 per il servizio telefonico tradizionale **POTS** (Plain Old Telephone Service), i canali 1-5 non utilizzati per evitare interferenze tra voce e dati, e i rimanenti 250 canali per la trasmissione dei dati, con due canali per il controllo del traffico.

Un dispositivo d’interfaccia **NID** (*Network Interface Device*) viene installato presso l'edificio del cliente per segnare il confine tra la proprietà della compagnia telefonica e quella dell'utente. Un **divisore** (*splitter*) separa la banda 0-4000 Hz per il servizio telefonico dai dati, instradando il segnale POTS verso il telefono o il fax e il segnale dati verso un modem ADSL.

All'altro capo del cavo, presso la compagnia telefonica, un altro divisore separa il segnale vocale, instradandolo verso un commutatore per la voce, mentre i segnali a frequenza maggiore di 26 kHz sono inviati a un dispositivo **DSLAM** (*DSL Access Multiplexer*). Il DSLAM riconverte il segnale digitale in un flusso di bit e crea pacchetti di dati da spedire all'ISP.
#### 2.4.6.3 - Internet via cavo
In ogni grande città c’è una sede principale dell’operatore via cavo, collegata a diverse **stazioni di testa** tramite fibre ottiche o cavi ad alta larghezza di banda. Le stazioni di testa, a loro volta, connettono centinaia di case e uffici attraverso un cavo condiviso con una larghezza di banda di circa 750 MHz. Questo sistema condiviso pone il problema di gestire chi può trasmettere dati, quando e a quale frequenza.

I canali TV via cavo nel Nord America occupano l'intervallo tra 50 e 550 MHz, con canali di 6 MHz ciascuno. In Europa, i canali partono da 65 MHz e occupano tra i 6 e gli 8 MHz. La parte inferiore della banda non è utilizzata per la TV.

Per aggiungere l'accesso a Internet senza interferire con i programmi TV e garantire il traffico bidirezionale, i cavi moderni offrono una banda minima di 550 MHz, spesso raggiungendo 750 MHz. Il traffico in uscita utilizza la banda 5-42 MHz, mentre il traffico in entrata utilizza la parte alta della banda.

L'accesso a Internet richiede un modem con due interfacce: una verso il computer e l'altra verso il cavo di rete. Il modem via cavo determina la propria distanza dalla stazione di testa tramite un processo chiamato **ranging**, regolando l'utilizzo dei canali in uscita e la temporizzazione. I canali sono divisi in **minislot** temporali, utilizzati per trasmettere pacchetti di dati. La stazione di testa assegna i *minislot* ai modem per richiedere la larghezza di banda necessaria. In caso di contesa, il modem aspetta un tempo casuale prima di riprovare.

I canali in entrata sono gestiti dalla stazione di testa senza contese, utilizzando pacchetti di 204 byte. Durante l'inizializzazione del modem, dopo aver completato il ranging e ottenuto i canali in uscita e in entrata, il modem può iniziare a trasmettere pacchetti. Il primo pacchetto richiede un indirizzo IP all'ISP e l'ora del giorno.

Per garantire la sicurezza, il traffico è criptato in entrambe le direzioni. Durante l'inizializzazione, si stabiliscono le chiavi di cifratura e il modem si identifica fornendo il proprio numero univoco. Completata l'inizializzazione, l'utente può registrarsi presso l'ISP e utilizzare il servizio.

(pagine riassunte: 8.5)
### 2.4.7 - Macchine fotografiche digitali
Le macchine fotografiche digitali sono diventate una periferica del computer, poiché sempre più spesso il computer viene utilizzato per la fotografia digitale. Analogamente alle macchine fotografiche tradizionali, le digitali hanno una lente che forma un’immagine del soggetto sulla parte posteriore dell’apparecchio. Tuttavia, invece della pellicola, le digitali utilizzano una griglia rettangolare di **CCD** (Charge-Coupled Device) sensibili alla luce. 

I CCD producono valori indipendentemente dal colore della luce che li colpisce. Per creare immagini a colori, i CCD sono organizzati in gruppi di quattro, coperti da un **filtro di Bayer** che consente alla luce rossa di colpire un solo CCD, alla luce blu di colpirne un altro, e alla luce verde di colpire due CCD, poiché l'occhio umano è più sensibile alla luce verde.

Quando si scatta una foto, il software della macchina esegue tre azioni: mette a fuoco, determina l’esposizione e calcola il bilanciamento del bianco. La messa a fuoco automatica ottimizza le alte frequenze dell’immagine, l’esposizione viene regolata in base alla luce che raggiunge i CCD, e il bilanciamento del bianco corregge le dominanti cromatiche. 

L'immagine catturata viene letta dai CCD e memorizzata come una griglia di pixel nella memoria interna. Successivamente, il software della macchina effettua la correzione del bilanciamento del bianco. L'immagine può essere compressa per risparmiare spazio, spesso utilizzando il formato **JPEG** che applica la trasformata di Fourier bidimensionale e riduce le componenti ad alta frequenza.

Infine, l’immagine viene memorizzata su una memoria flash o un piccolo hard disk rimovibile chiamato **microdrive**. La post-elaborazione e la scrittura dell’immagine possono richiedere alcuni secondi per ciascuna foto.

(pagine riassunte: 2.25)
### 2.4.8 - Codifica dei caratteri
Ogni calcolatore ha un insieme di caratteri che, come minimo indispensabile, comprende le 26 lettere maiuscole, le 26 lettere minuscole, le cifre da 0 a 9 e un insieme di simboli speciali, come spazio, punto, virgola, segno meno e ritorno a capo. La corrispondenza tra caratteri e numeri naturali costituisce un **codice di caratteri**. È necessario che due calcolatori che comunicano fra loro utilizzino lo stesso codice, altrimenti non saranno in grado di capirsi.
#### 2.4.8.1 - ASCII
Un codice ampiamente utilizzato si chiama **ASCII** (*American Standard Code for Information Interchange*). I caratteri ASCII sono definiti da 7 bit, permettendo così un totale di 128 caratteri distinti. Ciononostante, visto che i computer sono orientati ai byte, ogni carattere ASCII viene normalmente memorizzato in un byte distinto. I codici compresi tra 0 e 1F (in esadecimale) sono caratteri di controllo e non vengono stampati. I codici da 128 a 255 non fanno parte della codifica ASCII, ma i PC IBM li hanno utilizzati per caratteri speciali come le emoticon e la maggior parte dei computer attuali li utilizza ancora.

Molti dei caratteri di controllo ASCII sono pensati per la trasmissione di dati.

I caratteri ASCII stampabili comprendono lettere maiuscole e minuscole, cifre, sim- boli di punteggiatura e alcuni simboli matematici.
#### 2.4.8.2 - UNICODE
Il primo tentativo di espandere il codice ASCII fu il codice IS 646, che aggiungeva 128 caratteri per trasformarlo in un codice a 8 bit chiamato **Latin-1**. Successivamente, il codice IS 8859 introdusse il concetto di **code page**, un insieme di 256 caratteri specifici per una lingua o gruppo di lingue. Tuttavia, il code page presentava problemi di gestione e non supportava lingue come giapponese o cinese.

Per risolvere questi problemi, un consorzio di produttori di computer creò **UNICODE**, diventato poi uno Standard Internazionale (IS 10646). UNICODE assegna a ogni carattere un valore a 16 bit chiamato **code point**, semplificando la scrittura dei programmi poiché non esistono caratteri speciali composti da più byte.

I code point di UNICODE sono divisi in blocchi multipli di 16 e assegnati a vari alfabeti principali, segni diacritici, simboli di punteggiatura, caratteri soprascritti e sottoscritti, simboli matematici, forme geometriche e simboli ornamentali. Include anche i simboli richiesti per le lingue cinese, giapponese e coreana.

Nonostante UNICODE risolva molti problemi di internazionalizzazione, non risolve tutti i problemi globali. Ad esempio, i caratteri Han non sono ordinati come nei dizionari e l'aggiunta di nuove parole in lingue come il giapponese richiede nuovi code point. Inoltre, UNICODE utilizza lo stesso code point per caratteri con aspetti simili ma significati diversi in giapponese e cinese.
#### 2.4.8.3 - UTF-8
Nonostante fosse un miglioramento rispetto all'ASCII, Unicode ha esaurito i code point disponibili e utilizza 16 bit per carattere, risultando inefficiente per il testo ASCII puro. Per affrontare questi problemi è stato sviluppato **UTF-8 (UCS Transformation Format)**, che codifica i caratteri in una lunghezza variabile da 1 a 4 byte e può rappresentare circa due miliardi di caratteri. UTF-8 è diventato il sistema di codifica dominante sul Web.

UTF-8 ha numerosi vantaggi: i codici da 0 a 127 corrispondono esattamente ai caratteri ASCII, permettendo di rappresentarli con un solo byte, mentre per gli altri caratteri il bit più significativo del primo byte è impostato a 1, indicando la presenza di byte aggiuntivi. Questo schema consente di codificare i caratteri ASCII con 8 bit, riducendo lo spreco di spazio. Inoltre, il primo byte di ogni carattere UTF-8 determina univocamente il numero di byte del carattere e i byte successivi iniziano sempre con 10, rendendo UTF-8 auto sincronizzante e facilitando l'analisi e la gestione del testo.

UTF-8 è generalmente usato per codificare i 17 piani di Unicode, anche se il suo schema supporta molti più code point dei 1.114.112 definiti da Unicode.

(pagine riassunte: 4.75)

[[3 - Livello logico digitale|Prossimo Capitolo]] 