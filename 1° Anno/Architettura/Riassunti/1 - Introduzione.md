Un calcolatore digitale è una macchina in grado di svolgere operazioni per le persone tramite istruzioni che vengono fornite da queste ultime. Una sequenza di istruzioni da eseguire si chiama **programma** e deve essere scritto in un *linguaggio* comprensibile per la macchina.
Quest'ultimo si chiama **linguaggio macchina** e contiene un insieme di istruzioni fornito dal produttore della macchina. Questo linguaggio risulta difficile da comprendere e utilizzare, per questo si è cercato di creare dei livelli di astrazione per semplificare il lavoro del **programmatore**. Questo approccio di astrazione si chiama **approccio strutturale**.

## 1. 1 Approccio Strutturale 
Per avvicinare un linguaggio naturale come quello umano a quello macchina bisogna impostare dei livelli di astrazione. 

### Linguaggi, Livelli e Macchine Virtuali
Per affrontare il problema abbiamo due modi distinti, ponendo $L_0$ come il linguaggio di una macchina $M_0$ e un linguaggio $L_1$ non compatibile con $M_0$:
- **Traduzione**, scriviamo un programma in linguaggio $L_0$, chiamato **traduttore** che prende in input un programma scritto in $L_1$ e lo riscrive in linguaggio $L_0$. Implica maggiore velocità del codice, ma difficoltà maggiore nel rendere un programma **compatibile**. (Durante l'esecuzione, il computer ha il controllo del traduttore)
- **Interpretazione**, scriviamo un programma in linguaggio $L_0$, chiamato **interprete** che prende in input un programma scritto in $L_1$ e lo esegue con le stesse istruzioni scritte in $L_0$. (Durante l'esecuzione, il computer ha il controllo dell'interprete e il programma in $L_1$ è visto come un insieme di dati)

Per rendere effettivi questi metodi $L_1$ e $L_0$ devono essere due linguaggi con livelli di astrazione non troppo distanti (per questo si suddivide in più strati questo metodo). Invece di parlare di tutto il livello astrazione che ha portato a creare un **linguaggio virtuale**, di solito, si parla direttamente di **macchine virtuali** $M_n$ su cui vengono eseguiti linguaggi virtuali $L_n$ tramite traduzione o interpretazione. Le chiamiamo virtuali perché la realizzazione di queste macchine è troppo dispendiosa e conviene invece studiarle a livello logico. Questo metodo ci permette di dare ad ogni macchina virtuale un livello, creando così una **struttura multi-livello** a strati (Figura 1).

### Attuali macchine multi-livello

Le macchine multi-livello attuali sono divise in livelli da 0 a 5(logicamente parlando):
0. **Livello Logico Digitale**, formato principalmente da porte (gate) che implementano la logica booleana e formano dei transistor che prendono input digitali da dei registri.
1. **Livello Micro-Architettura**, dove troviamo un circuito chiamato **ALU** che esegue operazioni semplici su dati ottenuti dai registri (in genere da 8 a 32) formando un **datapath** (letteralmente percorso di dati). Generalmente viene gestito da un **micro-programma** ma può essere anche semplicemente gestito dall'hardware.
2. **Livello ISA** , un livello di istruzioni fornite dal produttore che vengono interpretate dal microprogramma o dai circuiti elettronici.
3. **Livello Macchina del Sistema Operativo**, generalmente una versione ibrida del precedente, in quanto contiene istruzioni di tipo ISA e implementa funzionalità utili. Alcune istruzioni vengono interpretate dal Sistema Operativo e altre direttamente dal microprogramma.
4. **Livello del Linguaggio Assemblativo**, pensato per rendere più semplice al programmatore scrivere un programma adatto ai livelli sottostanti. Questi linguaggi sono inizialmente tradotti in un *linguaggio virtuale* inferiore e poi interpretati. Il loro traduttore si chiama **assemblatore**.
5. **Livello del Linguaggio ad Alto Livello**, linguaggi moderni che sono molto più semplici da utilizzare e che utilizzano un **compilatore** al posto dell'assemblatore per essere tradotti nei livelli sottostanti, anche se ne esistono di interpretati.

### Evoluzione delle macchine multi-livello

Grazie a questa suddivisione della macchina in livelli, siamo arrivati concettualmente a dividere **l'hardware**, cioè l'insieme delle componenti tangibili di un'architettura, dal software, cioè gli algoritmi e il modo di implementarli. 

$$\text{Hardware e Software sono logicamente equivalenti.}$$

Nel tempo la tecnologia si è sviluppata ed adattata ai diversi problemi che incontrava. I primi computer digitali (degli anni '40) erano solitamente divisi in livello ISA e livello logico digitale, che portava a creare hardware sempre più complesso per ottenere nuove funzionalità. Nel 1951 Maurice Wilkes propose di invertire questo andamento questa**astrazione logica** progettando ciò che oggi definiamo un microprogramma, che traduceva un programma ISA in un linguaggio logico con istruzioni molto semplici (allo scopo di ridurre errori hardware e
dispendio di risorse).

Nel 1960, allo scopo di ridurre il lungo percorso per compilare ed eseguire un programma (passava in una macchina che veniva condivisa da più programmatori e molto lenta), si creò un programma definitivo chiamato anche oggi **sistema operativo** allo scopo di automatizzare molti processi della compilazione ed esecuzione dei programmi.

Col tempo si arrivò alla conclusione che per ottenere nuove funzioni "hardware\" bastava studiarle a livello software. Tuttavia questo metodo rallentò l'esecuzione dei microprogrammi con l'aumentare delle funzioni aggiunte, quindi si tornò nuovamente al punto di partenza, eliminando la microprogrammazione e riducendo il carico di istruzioni
che il processore doveva sostenere.

## Pietre militari nell'architettura dei computer (Capitolo da Rivedere)

Questo capitolo verrà minimizzato in quanto tratta la storia effettiva dal 1642 al 1990 circa. In quanto è un capitolo puramente ispirato alla curiosità, sarà disponibile interamente esclusivamente sul libro.
### Generazione Zero - Meccanici (1642-1945)

Le prime macchine, anche se sembrerà assurdo, le ritroviamo fin dal 1642 con macchine come *La macchina di Pascal* che era completamente meccanica, o *La macchina di Leibniz*. Queste macchine eseguivano operazioni molto semplici (algoritmi singoli), portando quindi gli investitori dei progetti a voler cercare di implementare macchine sempre più complesse (algoritmi multipli) che portarono, tre secoli fa, a creare effettive calcolatrici come quelle moderne.
### Prima Generazione - Valvole (1945-1955)

Come nella maggior parte delle scoperte scientifiche e tecnologiche, la guerra ebbe un enorme effetto. Vi fu la creazione di enormi calcolatori per per aiutare i militanti (calcolo delle coordinate per artiglieria, la lotta contro ENIGMA, \...), tra i più conosciuti l'*ENIAC*, che aveva 18.000 valvole e 1500 relè e consumava fino a 140Kw di energia. La cosa più importante che abbiamo in questo periodo è lo sviluppo della *macchina di von Neumann* o anche IAS, nome dato in onore del suo creatore, che ebbe due importanti aggiornamenti:

- L'utilizzo del binario al posto di un sistema decimale per semplificare l'architettura di computer come quello ENIAC.
- La suddivisione della macchina in memoria, l'unità logico aritmetica, unità di controllo e dispositivi di input e output. (Nei computer moderni l'ALU e la CU formano la CPU)  

### Seconda Generazione - Transistor (1955-1965

In questa generazione di computer troviamo come principale portatore di sviluppo il **transistor**, inventato nel 1948 da John Bardenn. Inizialmente le aziende più famose non avevano intenzione di investire in questa tecnologia e nei computer in generale, ma con l'arrivo del PDP-1 (prima macchina dotata di 4096 byte di memoria a 18 bit con 200.000 istruzioni al secondo).Da lì la IBM e la DEC (aziende investitrici in tecnologie) iniziarono a
produrre prodotti che riuscivano a raggiungere velocità modeste (non comparabili ai computer attuali a valvole) ma che avevano un costo enormemente inferiore. Con il PDP-8 arrivò anche l'utilizzo dell'**omnibus**, che permetteva in *parallelo* di connettere diverse componenti contemporaneamente.

Altra invenzione di nicchia fu il **supercomputer** di *Seymour Cray*, figura paragonabile al genio di von Neumann. Ultima nota fu il computer Burroughts B5000, primo progetto incentrato principalmente sul software. Cercarono di implementare al meglio un linguaggio chiamato Algol 60, precursore di Java e C, nella macchina.

### Terza Generazione - Circuiti Integrati (1965-1980)

L'invenzione dei circuiti integrati da parte di Jack Kilby e Robert Noyce, permise la costruzione di computer sempre più piccoli e veloci (grazie al fatto che si poteva raggruppare fino a 10 transistor in un chip).

I principali cambiamenti riguardarono l'invenzione della **multiprogrammazione**, che ritroviamo con l'innovativa serie 360 IBM (Famiglia di computer IBM), dove è possibile avere più programmi in memoria allo stesso tempo, in attesa. Generalmente gli sviluppi si incentrarono sul minimizzare ancora di più l'hardware aumentandone però le capacità.

### Quarta Generazione - Integrazione a grandissima scala (1980-?)

Grazie alla tecnologia VLSI (Very Large Scale Integration), si iniziarono a creare chip che contenevano centinaia, migliaia se non milioni di transistor. Prima dell'avvento dei primi microcomputer, ogni università o azienda doveva dotarsi di un costoso computer che fungeva da centro di calcolo; dopodiché ogni privato o dipartimento poteva dotarsi del proprio calcolatore.

Inizialmente, quando un privato comprava un computer, si doveva montare componente per componente (ricevuta in un apposito kit) e scrivere il proprio sistema operativo. Col tempo arrivarono in dei floppy disk i primi sistemi operativi, contenenti una serie di istruzioni eseguibili sulla **shell**.

Con l'inizio della vendita di Personal Computer preassemblati e preparati per l'utilizzo (dove vediamo in concorrenza IBM, Apple, Atari\...) arrivò con Apple il primo computer dotato di **GUI** (Graphical User Interface) l'Apple Lisa, che fu troppo costoso e sostituito con una opzione più economica chiamata Macintosh. (Non tratterò il resto di questo capitolo che parla semplicemente dello sviluppo dei processori Intel/AMD e di nuove tecnologie)

### Quinta Generazione - Computer a basso consumo e Computer invisibili

Con l'avanzare della tecnologia i personal computer diventarono sempre più piccoli, arrivando alle invenzioni di tablet come il GridPad nel 1989. Rivoluzionari sono anche i PDA (Personal Digital Assistans), inventati da Jeff Hawkins che utilizzavano una particolare tecnica chiamato \"Graffiti\" che rendeva la scrittura leggibile più adattabile al computer (per renderla più leggibile per quest'ultimo). Questo tipo di tecnologia venne applicata sui smartphone.

Non fu però la cosa più rilevante, infatti abbiamo l'avvento dei **computer invisibili**, che erano dei microcomputer applicati agli elettrodomestici. La particolarità era la **coprogettazione** che avevano, cioè lo sviluppo sia dell'hardware che del software compatibile da parte delle aziende. 

## Tipologie di computer

In questa sezione vedremo alcune tipologie di tecnologie moderne che si stanno tutt'ora sviluppando.  

### Forze tecnologiche ed economiche

Durante l'evoluzione della tecnologia dei computer uno scienziato, Gordon Moore, iniziò a studiare l'andamento della crescita tecnologica, notando che rimaneva costante circa ogni 3 anni. Teorizzò la **Legge di Moore**, che fu più una analisi dell'andamento delle tecnologie. Essa teorizzava che il numero di transistor raddoppia circa ogni 18 mesi (Semplicemente ogni anno nuove tecnologie rendono i transistor sempre più piccoli ed efficienti), che corrisponde al 60% in più ogni anno.

Questa legge ci mostra come arriveremo ad un certo punto in cui l'ottimizzazione di un circuito, quindi la riduzione della dimensione dei transistor e altre migliorie, diventerà infattibile portandoci ad un **limite fisico**. Ora sono in sviluppo nuove tecnologie come le **macchine quantiche** che ci permetteranno di ovviare al problema. Questo tipo di sviluppo non è però mancato anche alle altre tecnologie, ad esempio le memorie sono passate in pochi anni da 10 MB di Hard disk a 1 TB di Hard disk.
### Microcontrollori

Come microcontrollori intendiamo le tecnologie integrate nelle apparecchiature che non sono elaboratori. Essi comandano e gestiscono l'interfaccia utente. Possiamo trovarli nelle macchine, negli elettrodomestici, nei dispositivi per la comunicazione e per l'intrattenimento etc\... Sono dei sistemi a sola scrittura e sono descritti da tre caratteristiche fondamentali:

- Le risorse utilizzate e i processi produttivi sono i più economici possibili, per permettere di poterne produrre in maggiore quantità.
- Lavorano in tempo reale, traducendo input direttamente in output che risulta in un tipo diverso di architettura.
- Hanno limiti fisici e hardware: peso, capienza della batteria, limiti elettrici e meccanici.
### Personal Computer

Il *personal computer* o PC abbreviato non è altro che un elaboratore \"personale\" composto generalmente da gigabyte di memoria, disco fisso, lettore CD-ROM/DVD/Blu-ray, scheda audio, interfaccia di rete e altre periferiche come monitor, mouse e tastiera. Ha un sistema operativo innovativo e sofisticato per rendere questa tecnologia accessibile a tutti, esistono sia portatili che desktop.
### Server

Un'altra tecnologia molto in vigore oggi sono i **server**, nient'altro che un personal computer con performance aumentate che ha lo scopo di eseguire miliardi di operazioni e transazioni al secondo. La tecnologia più usata con i server sono i **cluster** (sale server), che consisteva nel mettere in parallelo centinaia, se non migliaia, di server collegati con una rete di trasferimento dati ad alta velocità, riuscendo così a dividere le operazioni da eseguire in diverse macchine. In genere i cluster di grandi dimensioni si trovano in locali o edifici chiamati **data center**. I loro ambiti sono diversi, ma i più utilizzati sono quelli di Internet Web Server, cioè la gestione dei siti internet (tra richieste, caricamenti, trasferimenti).

### Mainframe

Questa è una tecnologia appartenente agli anni '60 che però rimane ancora utilizzato in alcune aziende che non vogliono riprogrammare da zero l'intero sistema di gestione dei dati e piuttosto preferiscono sostituirlo ogni tanto.

Sono enormi macchine con potenze di calcolo inferiori ai cluster ma con una maggiore banda di input/output che gli permette di elaborare una enorme quantità di dati. Altro tipo di tecnologia nota sono i **supercomputer** con CPU incredibilmente veloci utilizzate principalmente per calcoli ingegneristici e scientifici di alto livello, come scontri tra galassie, sintesi di nuove medicine oppure simulazioni dei flussi d'aria attorno agli aerei. 
### Unità metriche

Nel sistema metrico abbiamo dei prefissi che servono a dare un valore diverso all'unità di misura che stiamo usando. Però nell'informatica non funziona proprio come dalle altre parti. Ci viene da pensare che 1 Megabyte corrisponde a 1.000.000 di byte (cioè $10^3$), invece essendo che la misura è binaria 1 Kilobyte corrisponde a 1024 byte (Cioè $2^10$). Inoltre, dobbiamo distinguere la **velocità di trasferimento** che si misura in bit/s, che effettivamente viene proporzionata in $10^n$, e la **capacità**, che invece si misura usando il sistema binario quindi $2^n$.