Un calcolatore digitale è una macchina in grado di eseguire operazioni per le persone tramite istruzioni fornite da queste ultime. Una sequenza di istruzioni da eseguire si chiama **programma** e deve essere scritta in un _linguaggio_ comprensibile dalla macchina.

Questo linguaggio, chiamato **linguaggio macchina**, contiene un insieme di istruzioni fornite dal produttore della macchina. Poiché il linguaggio macchina è difficile da comprendere e utilizzare, sono stati creati livelli di astrazione per semplificare il lavoro del **programmatore**. Questo approccio di astrazione è noto come **approccio strutturale**.

(Pagine riassunte: 1)
## 1. 1 - Approccio Strutturale 
Per avvicinare un linguaggio naturale come quello umano a quello macchina bisogna impostare dei livelli di astrazione.
### 1.1.1 - Linguaggi, Livelli e Macchine Virtuali  
Per affrontare il problema della compatibilità tra linguaggi, consideriamo $L_0$ come il linguaggio di una macchina $M_0$ e $L_1$ come un linguaggio non compatibile con $M_0$. Ci sono due approcci distinti:
- **Traduzione**: consiste nello scrivere un programma in linguaggio $L_0$, chiamato **traduttore**, che prende in input un programma scritto in $L_1$ e lo riscrive in linguaggio $L_0$. Questo metodo garantisce maggiore velocità di esecuzione, ma rende più difficile la compatibilità del programma. Durante l'esecuzione, il computer ha il controllo del traduttore.
- **Interpretazione**: consiste nello scrivere un programma in linguaggio $L_0$, chiamato **interprete**, che prende in input un programma scritto in $L_1$ e lo esegue utilizzando istruzioni di $L_0$. In questo caso, durante l'esecuzione, il computer ha il controllo dell'interprete e il programma in $L_1$ è trattato come un insieme di dati.

Per implementare efficacemente questi metodi, i linguaggi $L_1$ e $L_0$ devono avere livelli di astrazione non troppo distanti. Per questo motivo, spesso si suddivide il processo in più strati. Anziché parlare dell'intero livello di astrazione che ha portato alla creazione di un **linguaggio virtuale**, si parla direttamente di **macchine virtuali** $M_n$ su cui vengono eseguiti linguaggi virtuali $L_n$ tramite traduzione o interpretazione. Queste macchine sono chiamate virtuali perché la loro realizzazione fisica sarebbe troppo dispendiosa, e quindi vengono studiate a livello logico. Questo approccio consente di assegnare a ogni macchina virtuale un livello, creando una **struttura multilivello** a strati.

(Pagine riassunte: 2.75)
### 1.1.2 - Attuali macchine multi-livello
Le **macchine multilivello attuali** sono divise logicamente in livelli da 0 a 5:
- **Livello Logico Digitale**: formato principalmente da porte logiche che implementano la logica booleana, formate da transistor che ricevono input digitali dai registri.
- **Livello Micro-Architettura**: comprende il circuito *ALU* (Arithmetic Logic Unit) che esegue operazioni semplici su dati ottenuti dai registri (generalmente da 8 a 32), formando un *datapath*. Questo livello è gestito da un *microprogramma* o direttamente dall'hardware.
- **Livello ISA** (Instruction Set Architecture): contiene un *insieme di istruzioni* fornite dal produttore, interpretate dal microprogramma o dai circuiti elettronici.
- **Livello Macchina del Sistema Operativo**: una versione ibrida del livello ISA, contenente istruzioni ISA e implementando funzionalità utili. Alcune istruzioni sono interpretate dal Sistema Operativo, altre dal microprogramma.
- **Livello del Linguaggio Assemblativo**: semplifica la scrittura di programmi per i livelli sottostanti. I linguaggi assemblativi sono tradotti in un linguaggio virtuale inferiore e poi interpretati. Il traduttore utilizzato è chiamato assemblatore.
- **Livello del Linguaggio ad Alto Livello**: comprende linguaggi moderni molto più semplici da usare, tradotti nei livelli sottostanti da un compilatore o interpretati direttamente.

(Pagine riassunte: 2.5)
### 1.1.3 - Evoluzione delle macchine multi-livello
Grazie alla suddivisione della macchina in livelli, abbiamo distinto concettualmente l'**hardware** (le componenti tangibili di un'architettura) dal **software** (gli algoritmi e il modo di implementarli). $$\text{Hardware e software sono logicamente equivalenti.}$$Nel tempo, la tecnologia si è sviluppata per affrontare vari problemi. I primi computer digitali degli anni '40 erano solitamente divisi tra il livello ISA e il livello logico digitale, portando a un hardware sempre più complesso per ottenere nuove funzionalità. 

Nel 1951, Maurice Wilkes propose di invertire questa tendenza attraverso l'**astrazione logica**, progettando ciò che oggi definiamo un microprogramma, che traduceva un programma ISA in un linguaggio logico con istruzioni molto semplici, riducendo errori hardware e il dispendio di risorse. 

Negli anni '60, per ridurre i lunghi tempi di compilazione ed esecuzione dei programmi (spesso eseguiti su macchine condivise e lente), fu creato un programma definitivo, chiamato **sistema operativo**, per automatizzare molti processi di compilazione ed esecuzione dei programmi. Col tempo, si concluse che per ottenere nuove funzioni "hardware" bastava studiarle a livello software. 

Tuttavia, questo metodo rallentò l'esecuzione dei microprogrammi con l'aumentare delle funzioni aggiunte, portando infine a un ritorno all'approccio iniziale, eliminando la microprogrammazione e riducendo il carico di istruzioni che il processore doveva gestire.

(Pagine riassunte: 5)
## 1.2 - Pietre militari nell'architettura dei computer
Il seguente capitolo è stato riassunto in maniera probabilmente eccessiva, a causa del fatto che ci sono troppi dati da trascrivere e che sembrano valere poco per un'orale.

Per riferimenti a livello di libro le pagine sono da 13 a 29.
### 1.2.1 - Generazione Zero - Meccanici (1642-1945)
Le prime macchine, incredibile a dirsi, risalgono al 1642. Un esempio famoso è la _macchina di Pascal_, in grado di eseguire addizioni e sottrazioni. Un altro è la _macchina di Leibniz_, che poteva eseguire anche moltiplicazioni e divisioni. Queste macchine eseguivano operazioni molto semplici (algoritmi singoli), ma stimolarono l'interesse degli investitori a sviluppare macchine sempre più complesse, in grado di eseguire algoritmi multipli. Questo interesse e sviluppo portarono, nel corso di tre secoli, alla creazione delle calcolatrici che conosciamo oggi.

(Pagine riassunte: 3.5)
### 1.2.2 - Prima Generazione - Valvole (1945-1955)
Come in molte scoperte scientifiche e tecnologiche, la guerra ha avuto un enorme impatto sullo sviluppo dei calcolatori. Durante la Seconda Guerra Mondiale, furono creati calcolatori enormi per assistere le operazioni militari, come il calcolo delle coordinate per l'artiglieria e la decifrazione dei codici (come nella lotta contro ENIGMA). Tra i più noti ci sono il *Colossus*, il primo calcolatore digitale, e l'*ENIAC*, che conteneva 18.000 valvole, 1.500 relè e consumava fino a 140 kW di energia.

Uno dei contributi più significativi di questo periodo è lo sviluppo della macchina di von Neumann, chiamata così in onore del suo creatore. Questa macchina introdusse due importanti innovazioni:
- L'uso del sistema binario al posto del sistema decimale, semplificando l'architettura dei computer come l'ENIAC.
- La suddivisione della macchina in memoria, unità logico-aritmetica (ALU), unità di controllo (CU) e dispositivi di input e output. Nei computer moderni, l'ALU e la CU formano la CPU.

(Pagine riassunte: 3)
### 1.2.3 - Seconda Generazione - Transistor (1955-1965)
In questa generazione di computer, il principale motore di sviluppo fu il **transistor**, inventato nel 1948 da John Bardeen. Inizialmente, le aziende più famose erano riluttanti a investire in questa tecnologia e nei computer in generale. Tuttavia, con l'arrivo del PDP-1, la prima macchina dotata di 4096 byte di memoria a 18 bit con 200.000 istruzioni al secondo, le cose cambiarono. La IBM e la DEC, aziende investitrici in tecnologie, iniziarono a produrre prodotti che, pur non raggiungendo le velocità dei computer a valvole dell'epoca, avevano costi significativamente inferiori. Con il PDP-8 arrivò anche l'uso dell'**omnibus**, che permetteva di connettere diverse componenti in parallelo.

Un'altra invenzione di rilievo fu il **supercomputer** di Seymour Cray, una figura paragonabile a quella di von Neumann per il suo genio. Infine, il computer Burroughs B5000 rappresentò il primo progetto incentrato principalmente sul software. Questo computer cercò di implementare al meglio un linguaggio chiamato Algol 60, precursore di Java e C, nella macchina.

(Pagine riassunte: 2.5)
### 1.2.4 - Terza Generazione - Circuiti Integrati (1965-1980)
L'invenzione dei circuiti integrati da parte di Jack Kilby e Robert Noyce permise la costruzione di computer sempre più piccoli e veloci, grazie alla possibilità di raggruppare fino a 10 transistor in un chip. Questa innovazione portò a una significativa riduzione delle dimensioni e dei costi dei computer, aumentando al contempo le loro capacità e velocità.

Un'altra grande innovazione fu l'introduzione del concetto di **famiglia di computer**, che consentiva di coprire una gamma più ampia di necessità dei clienti con modelli diversi ma compatibili tra loro. Questo approccio permetteva alle aziende di offrire una varietà di soluzioni scalabili e aggiornabili nel tempo.

I principali cambiamenti di questo periodo riguardarono anche l'invenzione della **multiprogrammazione**, una tecnica che consentiva di avere più programmi in memoria allo stesso tempo, pronti per l'esecuzione. Questa tecnica divenne una caratteristica distintiva della serie IBM 360, una delle famiglie di computer più innovative dell'epoca. La multiprogrammazione ottimizzava l'uso delle risorse di calcolo, permettendo di eseguire più operazioni contemporaneamente e migliorando l'efficienza complessiva del sistema.

In sintesi, gli sviluppi tecnologici si concentrarono sulla riduzione delle dimensioni dell'hardware e sull'aumento delle capacità, introducendo concetti avanzati come la multiprogrammazione per sfruttare al meglio le risorse disponibili.

(Pagine riassunte: 2)
### 1.2.5 - Quarta Generazione - Integrazione a grandissima scala (1980-?)
Grazie alla tecnologia VLSI (Very Large Scale Integration), si iniziarono a creare chip che contenevano centinaia, migliaia, se non milioni di transistor. Questa evoluzione consentì la realizzazione di microcomputer, i quali trasformarono il modo in cui le università, le aziende e, infine, i privati potevano accedere alla potenza di calcolo. Prima dell'avvento dei microcomputer, le istituzioni dovevano dotarsi di costosi computer centralizzati per il calcolo, mentre con i microcomputer ogni dipartimento o privato poteva permettersi il proprio calcolatore.

L'era dei personal computer iniziò grazie al prezzo economico di questi nuovi dispositivi, rendendo possibile a chiunque di possederne uno. All'inizio, i computer per privati venivano venduti come kit da montare, con i componenti da assemblare manualmente e il software da scrivere ex novo. Successivamente, con l'arrivo dei primi sistemi operativi distribuiti su floppy disk, i computer vennero forniti con una shell contenente una serie di istruzioni eseguibili.

Con l'inizio della vendita di Personal Computer preassemblati e pronti all'uso, diverse aziende entrarono in competizione, tra cui IBM, Apple, e Atari. Apple si distinse per l'introduzione del primo computer dotato di **GUI** (Graphical User Interface), l'Apple Lisa. Nonostante fosse innovativo, l'Apple Lisa risultò troppo costoso, e fu presto sostituito da una versione più economica chiamata Macintosh.

L'introduzione del GUI rivoluzionò l'interazione uomo-macchina, rendendo i computer molto più accessibili e intuitivi per l'utente medio. Questo segna un importante passaggio nell'evoluzione dei personal computer, focalizzandosi sull'usabilità e sull'accessibilità, fattori che hanno contribuito significativamente alla diffusione di massa dei computer.

Lo sviluppo dei processori, come quelli di Intel e AMD, e delle nuove tecnologie correlate, continuò a migliorare le prestazioni e le capacità dei computer, ma questo è un argomento che esula da questo riassunto e che si concentra maggiormente sugli aspetti storici e tecnologici fondamentali.

(Pagine riassunte: 3)
###### Informazione
Il capitolo 1.2.6 è stato saltato in quanto presunto non importante.
## 1.3 - Tipologie di computer
In questa sezione vedremo alcune tipologie di tecnologie moderne che si stanno tutt'ora sviluppando.  
### 1.3.1 - Forze tecnologiche ed economiche
Durante l'evoluzione della tecnologia dei computer, uno scienziato, Gordon Moore, iniziò ad analizzare l'andamento della crescita tecnologica, notando una curva costante circa ogni 3 anni. Teorizzò quella che è ora conosciuta come la **Legge di Moore**, che rappresenta più un'osservazione empirica che una legge fisica.

#### La Legge di Moore

La Legge di Moore teorizza che il numero di transistor su un chip raddoppia circa ogni 18 mesi, il che equivale a un incremento del 60% ogni anno. Questa previsione implica che, grazie all'innovazione continua, i transistor diventano sempre più piccoli e più efficienti, permettendo ai processori di diventare più potenti e meno costosi.

#### Implicazioni della Legge di Moore

- **Aumento della Potenza di Calcolo**: Ogni 18 mesi, la potenza di calcolo dei microprocessori raddoppia, permettendo l'esecuzione di operazioni più complesse e l'elaborazione di dati più rapidamente.
- **Riduzione dei Costi**: Man mano che i transistor diventano più piccoli, i costi di produzione per unità di calcolo diminuiscono, rendendo la tecnologia più accessibile.
- **Miniaturizzazione dei Dispositivi**: La miniaturizzazione dei transistor permette la produzione di dispositivi elettronici sempre più compatti e portatili.

#### Limiti della Legge di Moore

Moore stesso riconobbe che questa tendenza non può continuare indefinitamente. L'ottimizzazione di un circuito e la riduzione delle dimensioni dei transistor incontrano dei **limiti fisici**:

- **Limiti di Scala**: Alla scala dei nanometri, i transistor diventano così piccoli che gli effetti quantistici iniziano a interferire con il loro funzionamento.
- **Problemi di Dissipazione del Calore**: Transistor più piccoli e più numerosi generano più calore, il che rappresenta una sfida per la gestione termica.
- **Costi di Produzione**: Le tecnologie necessarie per produrre transistor a scale estremamente ridotte diventano esponenzialmente più costose.

#### Oltre la Legge di Moore: Nuove Tecnologie

Con l'approssimarsi dei limiti fisici imposti dalla Legge di Moore, la ricerca si sta orientando verso nuove tecnologie, tra cui:

- **Computer Quantistici**: Utilizzano qubit al posto dei bit tradizionali, permettendo un salto quantico nella capacità di calcolo.
- **Architetture Neuromorfiche**: Ispirate al funzionamento del cervello umano, queste architetture promettono di rivoluzionare il modo in cui i computer elaborano le informazioni.
- **Memorie Avanzate**: Le tecnologie di memoria stanno evolvendo rapidamente, passando da hard disk con capacità di 10 MB a unità di memorizzazione con capacità di 1 TB e oltre in pochi decenni.

La Legge di Moore ha guidato l'industria dei semiconduttori per decenni, ma il futuro della tecnologia dei computer potrebbe dipendere sempre più da innovazioni radicali oltre il semplice miglioramento dei transistor tradizionali.

(Pagine riassunte: 2)
### 1.3.4 Microcontrollori
Come microcontrollori intendiamo le tecnologie integrate nelle apparecchiature che non sono elaboratori. Essi comandano e gestiscono l'interfaccia utente. Possiamo trovarli nelle macchine, negli elettrodomestici, nei dispositivi per la comunicazione e per l'intrattenimento etc\... Sono dei sistemi a sola scrittura e sono descritti da tre caratteristiche fondamentali:

- Le risorse utilizzate e i processi produttivi sono i più economici possibili, per permettere di poterne produrre in maggiore quantità.
- Lavorano in tempo reale, traducendo input direttamente in output che risulta in un tipo diverso di architettura.
- Hanno limiti fisici e hardware: peso, capienza della batteria, limiti elettrici e meccanici.
### 1.3.6 Personal Computer

Il *personal computer* o PC abbreviato non è altro che un elaboratore \"personale\" composto generalmente da gigabyte di memoria, disco fisso, lettore CD-ROM/DVD/Blu-ray, scheda audio, interfaccia di rete e altre periferiche come monitor, mouse e tastiera. Ha un sistema operativo innovativo e sofisticato per rendere questa tecnologia accessibile a tutti, esistono sia portatili che desktop.
### 1.3.7 Server

Un'altra tecnologia molto in vigore oggi sono i **server**, nient'altro che un personal computer con performance aumentate che ha lo scopo di eseguire miliardi di operazioni e transazioni al secondo. La tecnologia più usata con i server sono i **cluster** (sale server), che consisteva nel mettere in parallelo centinaia, se non migliaia, di server collegati con una rete di trasferimento dati ad alta velocità, riuscendo così a dividere le operazioni da eseguire in diverse macchine. In genere i cluster di grandi dimensioni si trovano in locali o edifici chiamati **data center**. I loro ambiti sono diversi, ma i più utilizzati sono quelli di Internet Web Server, cioè la gestione dei siti internet (tra richieste, caricamenti, trasferimenti).

### 1.3.8 Mainframe

Questa è una tecnologia appartenente agli anni '60 che però rimane ancora utilizzato in alcune aziende che non vogliono riprogrammare da zero l'intero sistema di gestione dei dati e piuttosto preferiscono sostituirlo ogni tanto.

Sono enormi macchine con potenze di calcolo inferiori ai cluster ma con una maggiore banda di input/output che gli permette di elaborare una enorme quantità di dati. Altro tipo di tecnologia nota sono i **supercomputer** con CPU incredibilmente veloci utilizzate principalmente per calcoli ingegneristici e scientifici di alto livello, come scontri tra galassie, sintesi di nuove medicine oppure simulazioni dei flussi d'aria attorno agli aerei. 
### 1.5 Unità metriche

Nel sistema metrico abbiamo dei prefissi che servono a dare un valore diverso all'unità di misura che stiamo usando. Però nell'informatica non funziona proprio come dalle altre parti. Ci viene da pensare che 1 Megabyte corrisponde a 1.000.000 di byte (cioè $10^3$), invece essendo che la misura è binaria 1 Kilobyte corrisponde a 1024 byte (Cioè $2^10$). Inoltre, dobbiamo distinguere la **velocità di trasferimento** che si misura in bit/s, che effettivamente viene proporzionata in $10^n$, e la **capacità**, che invece si misura usando il sistema binario quindi $2^n$.

[[2 - Organizzazione dei sistemi di calcolo|Continua...]]