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

### 2.2.4 - Codici correttori

### 2.2.5 - Memoria cache

### 2.2.6 - Assemblaggio e tipi di memoria

## 2.3 - Memoria secondaria

### 2.3.1 - Gerarchie di memoria

### 2.3.2 - Dischi magnetici

### 2.3.3 - Dischi IDE

### 2.3.4 - Dischi SCSI

### 2.3.5 - RAID

### 2.3.6 - Dischi a stato solido

### 2.3.7 - CD-ROM

### 2.3.8 - CD-registrabili

### 2.3.9 - CD-riscrivibili

### 2.3.10 - DVD

### 2.3.11 - Blu-Ray

## 2.4 - Input/Output

### 2.4.1 - Bus

### 2.4.2 - Terminali

### 2.4.3 - Mouse

### 2.4.4 - Controller per videogiochi

### 2.4.5 - Stampanti

### 2.4.6 - Macchine fotografiche digitali

### 2.4.7 - Codifica dei caratteri
