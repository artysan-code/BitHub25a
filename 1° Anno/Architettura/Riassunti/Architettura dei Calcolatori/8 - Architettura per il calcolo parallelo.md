Le industrie, siano esse scientifiche, fisiche o mediche, richiedono agli ingegneri potenze di calcolo strabilianti che, a causa dei **limiti fisici** (come la velocità della luce e gli atomi), non possono essere raggiunte con le tecnologie tradizionali.

Per questo motivo, in questa epoca si sta cercando di ottimizzare il **parallelismo** per permettere di elaborare una quantità elevata di istruzioni in un intervallo di tempo ridotto. Esistono diversi livelli di parallelismo, ma verranno trattati tutti in maniera adeguata nei capitoli successivi.

Generalmente, però, infrastrutture con **multicomputer** o **multiprocessori** possono essere **legati strettamente** (elevata larghezza di banda e ritardo trascurabile) o **legati debolmente** (bassa larghezza di banda e ritardo notevole, svolgono i calcoli in modo poco interattivo).

(Pagine riassunte: 2)
## 8.1 - Parallelismo nel chip
Tratteremo generalmente il parallelismo interno al chip, nelle sue maniere più astratte come quello a livello di istruzioni, fino alla coabitazione di CPU nello stesso chip.
### 8.1.1 - Parallelismo a livello di istruzioni
I due principali tipi di parallelismo a livello di istruzioni sono i seguenti:
- **Processori superscalari**: Questi processori dispongono di un hardware particolare che consente di emettere più istruzioni simultaneamente verso l'unità di esecuzione. Tuttavia, il loro utilizzo è limitato dai costi elevati dovuti alla complessità dell'hardware necessario.
- **Processori VLIW (Very Long Instruction Word)**: Come suggerisce il nome, questi processori eseguono istruzioni molto lunghe (fino a 136 bit), che possono contenere diverse operazioni per le varie unità funzionali. Tuttavia, risultano poco flessibili poiché è difficile utilizzare appieno tutte le unità funzionali con ogni istruzione. Nei calcolatori moderni, si adotta un principio di **pacchetto**, determinato da un **marcatore di pacchetto**, che equivale effettivamente a un blocco di istruzioni da eseguire. Questo approccio consente al programmatore di stabilire quali istruzioni eseguire prima e contemporaneamente, migliorando l'efficienza dell'esecuzione.

(Vi è la spiegazione del processore VLIW TriMedia, dubito possa servire)

(Pagine riassunte: 1.5)
### 8.1.2 - Multithreading nel chip
Quando un riferimento di memoria fallisce nella prima e nella seconda cache, la CPU deve attendere che i dati necessari vengano recuperati dalla memoria principale. Questo intervallo di attesa rappresenta uno spreco di tempo per la CPU. Per ovviare a questo problema, esistono diversi metodi di **multithreading nel chip** che permettono di mantenere la CPU occupata su un secondo thread mentre attende i dati per il primo.

Il primo approccio è chiamato **multithreading a grana fine**. In questo metodo, per utilizzare al massimo l'hardware, si usa un rapido cambio di contesto. I gruppi di thread (cioè gruppi di processi che devono essere eseguiti in una determinata sequenza) vengono eseguiti ciclicamente. Questo approccio è illustrato nel libro a pagina 570, figura 8.7 a-b-c-d.

Il secondo approccio è il **multithreading a grana grossa**, che opera in modo speculare rispetto al precedente. In questo caso, il cambio di contesto avviene ad ogni stallo del thread. Sebbene sia meno efficiente del multithreading a grana fine, se implementato con un algoritmo che prevede possibili stalli, può cambiare contesto in modo efficiente, mantenendo la CPU occupata con un numero ridotto di thread.

Un ulteriore vantaggio del multithreading a grana grossa è la possibilità di svuotare la pipeline ad ogni commutazione, mantenendo così l'identità del thread chiara e riducendo il rischio di confusione tra thread durante il cambio di contesto. Questo è particolarmente utile nei processori che emettono un numero maggiore di istruzioni.

Esiste anche un terzo metodo chiamato **multithreading simultaneo**. In questo approccio, ciascun thread emette due istruzioni e, in caso di stallo, si verifica un cambio di contesto verso il thread successivo. Questo metodo è un miglioramento del multithreading a grana grossa ed è considerato il più efficiente per i processori moderni.
#### Hyperthreading nel Core i7
Un'applicazione pratica del principio di multithreading si trova nei processori Intel, che durante la produzione del Pentium 4 furono progettati per supportare un principio di multithreading chiamato **hyperthreading** (il primo vero processore a implementarlo fu lo Xeon del 2002).

A livello fisico, diventava sempre più difficile migliorare l'hardware: aggiungere core, moduli, aumentare la frequenza del clock e allungare la pipeline portavano tutti a inefficienze termiche, di architettura e di predizione delle istruzioni. Il multithreading, invece, migliorava le prestazioni del processore del 25% aumentando solo del 5% la superficie del chip.

Il principio alla base dell'hyperthreading è eseguire due thread contemporaneamente, in modo simile ad avere due processori con memoria e cache condivisa. Proprio per questa condivisione, Intel ha identificato diversi metodi per la gestione logica dei thread, che ora vediamo:
- **Condivisione ripartita delle risorse**: Le risorse hardware e gli intervalli di esecuzione vengono divisi equamente in maniera forzata, evitando così che i thread entrino in conflitto.
- **Condivisione totale delle risorse**: L'opposto del metodo precedente, senza un algoritmo di selezione, in cui il primo thread che arriva utilizza tutte le risorse disponibili. Se un thread riempie le risorse, la coda di attesa dei thread successivi si riempie e il thread principale rischia di non avere più spazio per le risorse successive.
- **Condivisione a soglia**: Un thread può acquisire risorse dinamicamente, ma senza superare 3/4 della coda di attesa. In questo modo, un thread lento e uno veloce possono essere eseguiti in autonomia senza bloccarsi a vicenda (evitando il fenomeno dello starving).
- **Duplicazione delle risorse**: Poiché le risorse hardware devono essere maggiori per eseguire due thread contemporaneamente, i metodi di condivisione implicano un principio di duplicazione.

Le modalità utilizzate vengono selezionate dinamicamente a seconda della situazione per rendere più efficiente ogni casistica (per ulteriori dettagli, vedere l'esempio nella figura 8.9 del libro).

(Pagine riassunte: 6.5)
### 8.1.3 - Multiprocessori in un solo chip
Il multithreading in alcuni ambiti non fornisce abbastanza performance. Proprio per questo una tecnologia che suscita tutt'ora interesse è quella del **multiprocessore in un chip**.
#### Multiprocessori Omogenei in un solo chip
Questo metodo è principalmente utilizzato nei server farm che raggruppano molti server web. Vi sono due possibili implementazioni:
1. **Due pipeline con una sola CPU**: Questo approccio permette potenzialmente di raddoppiare il throughput. Consente la condivisione di alcune risorse, ma presenta una maggiore complessità di progettazione.
2. **Due core con una sola pipeline**: In questo caso, il core corrisponde a un grande circuito che comprende una CPU, un controller I/O e una cache, che può essere inserito in un chip in maniera modulare. Questo approccio è più semplice da implementare ed è attualmente utilizzato in molte architetture moderne che supportano più core (n core).
#### Multiprocessore a singolo chip Core i7
Un processore Core i7 presenta 4 o più core, dove ogni core è dotato di tre cache private: due di primo livello per istruzioni e dati, e una di secondo livello, unificata.

Il livello successivo della gerarchia è occupato dalla cache di livello 3, condivisa tra tutti i core, che si connette al livello sottostante tramite una **rete ad anello**. Una richiesta di comunicazione che entra nella rete viene trasmessa al nodo successivo, dove si verifica se la richiesta ha raggiunto il suo nodo di destinazione. Questo design consente una maggiore larghezza di banda, ma introduce anche una maggiore latenza.
#### Multiprocessori eterogenei in un solo chip
Tutte queste tecniche non sono applicabili in ogni ambito. Diversi dispositivi elettronici, come lettori CD, telefoni, e altri, necessitano di metodologie e applicativi differenti per rendere il prodotto ottimale per le prestazioni richieste.

Ad esempio, i telefoni cellulari richiedono un multiprocessore eterogeneo, concentrato sulla gestione modulo per modulo, a causa della varietà di funzioni che svolgono: telecamera, schermo, audio input e output, rete internet mobile e Wi-Fi, ecc. I dispositivi audiovisivi, invece, necessitano principalmente di moduli di memoria per elaborare grandi quantità di dati rapidamente.

Quali tecniche sono utilizzate per un processore eterogeneo? La gestione dei moduli (o core) è fondamentale. 

Si può utilizzare un semplice bus, che però diventa un collo di bottiglia per sistemi più grandi. In alternativa, si possono usare più bus o un sistema ad anello che attraversa tutti i core. Ogni passaggio viene gestito tramite un **token** che arbitra le comunicazioni tra i core (viene preso da un core e poi rilasciato nell'anello).

Un esempio di interconnessione nel chip di tipo eterogenea è il **CoreConnect** della IBM, che, a differenza del bus PCI, non presenta problemi di retrocompatibilità. È composto da tre bus:
- Un bus per il **processore**, veloce, sincrono e a pipeline con dati a 32, 64 e 128 bit, temporizzati a 66, 133 o 183 MHz. Ha una velocità massima di trasferimento di 23,4 Gbps, contro i 4,2 Gbps del PCI. La tecnologia a pipeline permette di trasferire diverse richieste da diversi core, ottimizzato per connettere core veloci e trasferire blocchi corti.
- Un bus per i **dispositivi I/O** più lenti, con interfaccia a 8, 16 e 32 bit, che può contenere non più di qualche centinaio di porte logiche. Ha una velocità massima di trasferimento di 300 Mbps.
- Un bus per i **registri di periferica**, molto lento, che serve esclusivamente per fare riferimento ai registri delle periferiche.

*(in questo capitolo chiedo un possibile secondo parere in quanto c'ho capito ben poco)*

(Pagine riassunte: 6.25)
## 8.2 - Coprocessori
Il principio del coprocessore è di riuscire a eseguire in maniera dipendente o anche indipendente un insieme di istruzioni specifiche. Si possono trovare in molti ambiti e giocano un ruolo importante nelle performance del sistema.

(Pagine riassunte: 0.5)
### 8.2.1 - Processori di rete
Partendo da una piccola introduzione sulle reti in generale, parliamo ora dei processori di rete che permettono di gestire i dati di ingresso ed uscita in maniera più efficiente, vista la banda di dati trasferibile con l'avanzare della tecnologia di rete.
#### Introduzione alle reti
Le reti dei calcolatori sono di due tipi principali: **LAN** (Local-Area Network) e **WAN** (Wide-Area Network). Le LAN connettono dispositivi all'interno di edifici o aree limitate, mentre le WAN collegano dispositivi su lunghe distanze.

La tecnologia LAN più usata è l'**Ethernet**, che oggi si connette a un commutatore centrale (switch) con velocità che possono arrivare fino a 10 Gbps. 

La tecnologia WAN è composta da **router** collegati ai server tramite cavi o fibre ottiche. I dati vengono suddivisi in **pacchetti** di dimensioni variabili tra 64 e 1500 byte, che viaggiano attraverso i router verso altre macchine tramite la tecnica della **commutazione di pacchetto store-and-forward**: il pacchetto viene memorizzato sul router e poi inoltrato al successivo fino alla destinazione.

Dal lato utente, il calcolatore prepara i pacchetti e li spedisce all'*ISP* (Internet Service Provider), che li inoltra nella rete un salto alla volta finché non raggiungono i server web. Il *firewall* filtra i pacchetti per bloccare quelli malevoli. La rete utilizza diversi **protocolli** che definiscono la struttura dei pacchetti e il metodo di trasferimento; ad esempio, una richiesta di pagina web utilizza il protocollo *HTTP*, che viene elaborato dal server web.

Una connessione al server web avviene tramite il protocollo **TCP** (Transfer Control Protocol), che garantisce che i pacchetti siano trasferiti completamente e nell'ordine corretto. Una richiesta HTTP ricevuta dal server viene elaborata e risponde con un messaggio TCP, che contiene un'**intestazione TCP**. Il messaggio viene poi preparato dal **Protocollo IP**, aggiungendo un'**intestazione IP** (contenente mittente, destinatario e altri campi).

Questo pacchetto viene quindi passato al livello di trasmissione dati (data link layer), dove viene allegata un'ulteriore intestazione per la trasmissione vera e propria. Infine, il pacchetto contiene una checksum (presente anche nell'intestazione IP) per verificare la presenza di errori.

Per quanto riguarda le connessioni ADSL, il pacchetto è simile, ma utilizza un'intestazione Ethernet specifica per le connessioni telefoniche.
#### Introduzione ai processori di rete
Abbiamo visto la complessità dei trasferimenti in rete: in una LAN a 40 Gbps, possiamo trasferire 5 milioni di pacchetti da 1 KB al secondo, o addirittura 80 milioni di pacchetti da 64 byte. Svolgere le attività descritte sopra in 12-200 ns è impossibile per il software.

Una prima implementazione prevede l'utilizzo di un **ASIC** (Application-Specific Integrated Circuit), un circuito integrato progettato su misura per ogni specifica applicazione. Tuttavia, i chip ASIC sono molto costosi e le modifiche richiedono una riprogettazione completa della scheda.

Una seconda possibilità utilizza i circuiti **FPGA** (Field Programmable Gate Array), un insieme di porte logiche che possono essere riorganizzate mediante la modifica dei collegamenti tra di loro. Gli FPGA sono più semplici da creare e possono essere riprogrammati, ma sono lenti e costosi rispetto agli ASIC.

Infine, ci sono i **processori di rete**, dispositivi programmabili che ricevono, elaborano e rilasciano pacchetti alla stessa velocità con cui viaggiano i collegamenti. Un processore di rete è composto da un processore, una memoria e circuiti logici di supporto collegati da un bus principale. Dopo l'elaborazione, i pacchetti vengono inviati sul bus principale (se la scheda è interna all'utente) o su un'altra linea (se è un router).

La memoria dei processori di rete comprende **SRAM** (Static RAM), più veloce e utilizzata per memorizzare tabelle di indirizzamento e altre strutture importanti, e **SDRAM** (Synchronous DRAM), meno costosa e più lenta, utilizzata per memorizzare i pacchetti in elaborazione.

I processori di rete possono elaborare milioni di pacchetti al secondo su ogni linea. Per questo motivo, dispongono di sistemi di parallelismo a livello di chip, suddivisi in **PPE** (Protocol/Programmable/Packet Processing Engine), che sono core RISC con una quantità ridotta di memoria per il programma e le variabili. Questi core possono essere organizzati in serie di core identici che si supportano reciprocamente; in caso di saturazione, aggiungono i pacchetti in coda nella SDRAM. L'elaborazione può avvenire anche tramite una pipeline, come nei processori, o tramite multithreading, trattando i pacchetti come thread da eseguire.
#### Elaborazione dei pacchetti
L'elaborazione dei pacchetti è divisa in passaggi specifici, indipendentemente dal sistema implementato. Generalmente, queste fasi si dividono in due tipi di operazioni: l'elaborazione **in entrata** dei pacchetti di rete e **in uscita**.

Le fasi sono le seguenti:
1. **Verifica del checksum**: Se il pacchetto è di tipo Ethernet, viene confrontato il CRC con quello ricalcolato. Successivamente, se il checksum è assente o corretto, viene verificato ulteriormente il checksum IP per assicurarsi che il pacchetto non sia stato danneggiato da un bit difettoso.
2. **Estrazione di campi**: Vengono estratti i dati principali dalle intestazioni Ethernet o IP e caricati nei registri o nella SRAM.
3. **Classificazione dei pacchetti**: Ogni pacchetto viene classificato, fornendo un contesto logico, come pacchetto dati o controllo, in base alle sue specifiche caratteristiche.
4. **Selezione del percorso**: Viene creato un percorso preferenziale per i pacchetti comuni e veloci da elaborare, mentre gli altri vengono smistati tramite il processore di controllo.
5. **Determinazione del destinatario di rete**: I pacchetti IP contengono un indirizzo del destinatario a 32 bit. Poiché una ricerca su una tabella di $2^{32}$ elementi non è praticabile, la parte più significativa dell'indirizzo IP viene utilizzata per identificare il numero di rete, e il restante per specificare la macchina all'interno di quella rete. Questa operazione è spesso gestita da un ASIC dedicato.
6. **Instradamento**: Una volta determinato il percorso del destinatario, si sceglie la linea di uscita su cui instradare il pacchetto, cercandola nella tabella della SRAM.
7. **Scomposizione e riassemblaggio**: Poiché i pacchetti da inviare possono essere molto grandi, vengono scomposti in segmenti standard e poi riassemblati dal destinatario per ricostruire i dati originali.
8. **Elaborazione**: Alcuni compiti, come la compressione/decompressione o la cifratura/decifratura, richiedono un'enorme potenza di calcolo e sono affidati al processore di rete.
9. **Gestione dell'intestazione**: Viene gestita l'aggiunta, la rimozione o la modifica di informazioni nell'intestazione del pacchetto, come il numero di salti che il pacchetto ha eseguito, presente nell'intestazione IP.
10. **Gestione della coda**: Per evitare problemi di latenza o jitter in alcune applicazioni particolari e per gestire il carico generale dei pacchetti in input/output, il processore di rete gestisce la coda.
11. **Generazione della checksum**: I pacchetti in uscita devono avere un checksum. Il CRC viene generalmente generato dall'hardware piuttosto che dal processore di rete.
12. **Contabilità**: Viene monitorato il traffico dei pacchetti, soprattutto quando la scheda funge da servizio per conto di altre reti, gestito dal processore di rete.
13. **Raccolta di statistiche**: Sebbene opzionale, la raccolta di statistiche permette di avere una diagnostica sul traffico di rete, fornendo utili informazioni per l'analisi delle prestazioni.

Questi passaggi sono cruciali per garantire un'efficiente elaborazione dei pacchetti di rete e per mantenere un alto livello di prestazioni nei sistemi di comunicazione.
#### Incremento delle prestazioni
Le ottimizzazioni nei sistemi di rete sono varie e non si concentrano esclusivamente sulla velocità di clock, l'emissione/immissione dei pacchetti o la velocità di trasferimento, ma piuttosto sul carico complessivo della scheda. Ecco alcune tecniche di ottimizzazione:
1. **Parallelismo**: Aggiungere più PPE (Protocol/Programmable/Packet Processing Engine) può aumentare significativamente l'efficienza, permettendo di elaborare più pacchetti simultaneamente.
2. **Schede specifiche**: Creare schede specifiche per casi particolari e pesanti può migliorare le prestazioni in scenari specifici.
3. **Miglioramenti hardware**: Diversi miglioramenti hardware possono contribuire all'ottimizzazione:
   - **Aumento della larghezza del bus**: Un bus più ampio può trasferire più dati simultaneamente, riducendo i colli di bottiglia.
   - **Incremento della velocità di clock**: Un aumento della velocità di clock può accelerare l'elaborazione, sebbene possa anche aumentare il consumo energetico e il calore generato.
   - **Sostituzione della SDRAM con SRAM**: La SRAM è più veloce della SDRAM e può migliorare le prestazioni complessive, anche se a un costo più elevato.

Queste ottimizzazioni, implementate singolarmente o in combinazione, contribuiscono a migliorare l'efficienza e le prestazioni delle schede di rete, garantendo un'elaborazione più rapida e affidabile dei pacchetti.

(Pagine riassunte: 7.5)
### 8.2.2 - Processori grafici
Generalmente la CPU non è capace di elaborare enormi quantità di dati in intervalli infimi, come nei casi dei rendering 3D o di grafiche avanzate. Per questo esiste una tipologia di calcolatore chiamato GPU che fornisce performance competitive alla CPU.
#### GPU NVIDIA Fermi
Un esempio di famiglia di GPU è la famiglia **NVIDIA Fermi**. Descritta nel libro, questa famiglia presenta 16 **SM** (Streaming Multiprocessors), ciascuno dotato di una cache L1 privata ad alta larghezza di banda. Ogni SM contiene 32 core **CUDA**, che sono processori semplici in grado di eseguire calcoli interi a singola precisione e operazioni in virgola mobile. Gli SM condividono una cache L2 di 768 KB, collegata a un'interfaccia DRAM a più porte. La comunicazione tra la GPU e il processore host avviene tramite una DRAM condivisa, spesso attraverso un'interfaccia PCI-Express.

Data la presenza di grandi gruppi di core negli SM, questi eseguono operazioni identiche a ciclo continuo, in un processo chiamato **SIMD** (Single-Instruction Multiple Data), che preleva e decodifica un'istruzione per ciclo. Questa capacità di calcolo massiccia offre notevoli vantaggi ai programmatori.

Programmare per una GPU è più complesso rispetto alla programmazione per una CPU. NVIDIA ha quindi fornito un linguaggio specifico per i core CUDA, ottimizzato per il parallelismo degli SM. I thread vengono raggruppati in blocchi e assegnati agli SM. Se ogni thread esegue la stessa identica istruzione, fino a 16 istruzioni possono essere eseguite per ciclo di clock. In caso di divergenza delle istruzioni, l'elaborazione della GPU rallenta. Gli ambiti grafici e di rendering sono particolarmente adatti a questa tecnologia, sebbene le GPU si stiano espandendo in altri campi, portando alla definizione di GPGPU (General-Purpose Graphics Processing Units).

Essenziale è anche il sistema di gerarchia della memoria, che assicura che la GPU non manchi di larghezza di banda, evitando così arresti imprevisti.

(Pagine riassunte: 3)
### 8.2.3 - Crittoprocessori
La sicurezza al giorno d'oggi è uno dei principi fondamentali, soprattutto nel trasferimento dei dati. Le funzioni di crittografia e autenticazione, sia tra server che tra client e server, richiedono notevoli risorse computazionali. Per questo motivo, esistono coprocessori specifici dedicati all'elaborazione di queste funzioni.

Esistono due principali tipi di metodi crittografici: **a chiave simmetrica** e **a chiave pubblica**. La crittografia a chiave simmetrica utilizza la stessa chiave per cifrare e decifrare i dati, smistando i bit in maniera casuale per impedire la decifrazione non autorizzata del messaggio. La crittografia a chiave pubblica, invece, utilizza una coppia di chiavi (una pubblica e una privata) e si basa su operazioni matematiche complesse come la moltiplicazione o l'elevazione di numeri molto grandi (ad esempio 1024 bit), che richiedono molte risorse.

Sebbene esista hardware specifico per tutte queste mansioni, come i coprocessori crittografici, non verrà trattato in dettaglio in questo contesto.

(Pagine riassunte: 0.5)
## 8.3 - Multiprocessori con memoria condivisa
Ora trattiamo l'aggiunta di diverse CPU e come poter creare sistemi che permettono di applicarsi ad ambiti più grandi. Tratteremo i **multiprocessori** e i **multicomputer**.
### 8.3.1 - Multiprocessori e multicomputer a confronto
Le metodologie di parallelismo, la comunicazione di informazioni tra CPU, condivisione di compiti e selezione di essi, sono tutte problematiche che vengono risolte e strutturate nei seguenti sistemi in maniera differente.
#### Multiprocessori
Il multiprocessore è un calcolatore in cui tutte le CPU condividono una memoria comune. Tutti i processi che cooperano in un multiprocessore possono condividere un unico spazio degli indirizzi virtuali mappato nella memoria comune. Ogni processo può leggere o scrivere una parola di memoria, ma soprattutto possono *comunicare tra di loro* tramite la memoria condivisa: uno scrive dati in memoria e l'altro li legge.

Questa capacità di comunicare facilmente è ciò che rende i multiprocessori particolarmente utili. La programmazione risulta più semplice e si possono risolvere efficacemente molti problemi, come il rendering di tutti gli elementi in un'immagine.

Poiché tutte le CPU accedono a una sola memoria, il sistema operativo è unico e vi è una sola mappa delle pagine e una sola tabella dei processi. Quando un processo viene bloccato, le sue informazioni rimangono salvate nella tabella e la CPU può passare all'esecuzione del processo successivo.
#### Multicomputer
Il **multicomputer** prevede per ogni CPU una memoria privata a cui accede tramite semplici istruzioni, diversamente dai multiprocessori, comunicando con le altre CPU lungo una **rete di interconnessione**.

Quando una CPU (ad esempio, CPU 0) vuole accedere all'area di memoria di un'altra CPU (ad esempio, CPU 1) per analizzare il contenuto, spedisce una richiesta di copia dati. Questa richiesta, una volta analizzata, permette alla CPU 1 di riportare i dati richiesti a CPU 0. Durante questo processo, CPU 0 rimane bloccata e viene sbloccata al ricevimento dei dati, utilizzando un semplice sistema *send* e *receive*.

Nonostante il metodo di comunicazione dei multicomputer possa sembrare rudimentale e meno efficiente rispetto ai multiprocessori, essi sono molto più facili da costruire. Per trarre vantaggio da entrambe le tecnologie, si è puntato a sviluppare sistemi **ibridi** o **scalabili** che implementano entrambe le filosofie.

Le implementazioni della memoria condivisa possono essere riassunte utilizzando l'architettura a livelli precedentemente studiata:
- **Memoria condivisa sotto il sistema operativo**: In questa configurazione, vi è una sola memoria fisica gestita dal sistema operativo che tiene traccia delle pagine e risponde all'hardware. Questo approccio è tipico dei multiprocessori.
- **Memoria condivisa sopra il sistema operativo**: Nei sistemi di multicomputer, la memoria condivisa può essere simulata come uno spazio paginato di indirizzi virtuali condivisi. Questo approccio è chiamato **DSM** (Distributed Shared Memory). Quando una CPU tenta di accedere a una pagina di memoria non sua, si verifica una trap rivolta al sistema operativo. Il sistema operativo interrompe la CPU che possiede quella memoria per trasferire le informazioni alla CPU richiedente, dopodiché il ciclo di istruzioni continua.
- **Memoria condivisa nel sistema runtime**: In questa configurazione, la memoria condivisa è astratta a livello di codice programmato (livello superiore). Questa implementazione elimina la necessità di hardware specifico, permettendo di implementare la propria astrazione tramite il compilatore. Un esempio di questo approccio è il sistema Linda, che vede la memoria virtuale come un insieme di tuple.

Questi approcci permettono di sfruttare al meglio le caratteristiche dei multiprocessori e dei multicomputer, combinando la facilità di costruzione con l'efficienza nella comunicazione e nell'elaborazione.
#### Tassonomia dei calcolatori paralleli
Abbiamo uno schema approssimativo che organizza i calcolatori paralleli, fornito da Flynn, che si basa su due concetti fondamentali: **flussi di istruzioni** e **flussi di dati**.

Supponendo di classificare i flussi in 1 o molteplici, abbiamo quattro categorie principali di processori:
- **SISD**, macchina sequenziale classica di von Neumann, una istruzione produce un dato.
- **SIMD**, possono ricevere a volta solo un tipo di istruzione, ma operare simultaneamente su diversi dati. Si dividono in due categorie: **processori vettoriali** e **unità di calcolo vettoriali**.
- **MISD**, categoria particolare dove diverse istruzioni lavorano sugli stessi dati.
- **MIMD**, un insieme di CPU indipendenti che lavorano su molteplici dati, come i multicomputer e multiprocessori o generalmente le macchine parallele. La classificazione si complica ulteriormente con le *categorie di multicomputer e multiprocessori*:
	- I multiprocessori si dividono per la metodologia di implementazione della memoria condivisa e sono: **UMA** (Uniform Memory Access), **NUMA** (Non-Uniform Memory Access) e **COMA** (Cache Only Memory Access).
	- I multicomputer, detti anche **NORMA** (No Remote Memory Access), si dividono in due categorie: **MPP** (Massively Parallel Processor) collegati da una rete strettamente legata e **COW** (Cluster of Workstations), o **NOW** (Network of Workstations) o più semplicemente **clusters**.

(Pagine riassunte: 7.5)
### 8.3.2 - Semantica della memoria
Nei multiprocessori, le metodologie di accesso alla memoria pongono problemi di progettazione e gestione delle richieste di memoria. Per comprendere meglio questo concetto, dobbiamo definire la **semantica della memoria**, che consiste in un contratto tra hardware, software e memorie. Le regole che stabiliscono questa semantica si chiamano **modelli di consistenza**.
#### Consistenza stretta
Un'utopia, in cui ogni locazione $x$ ritorna il valore di scrittura più recente, è impossibile da implementare se non tramite un modulo di memoria che serve tutte le richieste nell'ordine in cui sono recapitate, il che diventa un collo di bottiglia per l'intero sistema.
#### Consistenza sequenziale
In questa implementazione, quando ci sono diverse richieste di scrittura o lettura nella stessa area di memoria, l'hardware effettua un **rimescolamento non deterministico** e ne *rende partecipe tutte le CPU che hanno fatto richiesta*. 

Lo scopo fondamentale è che vi sia una sequenza definita a tutti gli ambiti (quindi le CPU) e che non ci siano discrepanze (Se la CPU 1 scrive 100, la CPU 2 scrive 200 e CPU 3 e 4 leggono entrambe leggeranno o 100 o 200 ma mai diversamente) anche se meno stretto.
#### Consistenza di processore
Questo metodo è meno rigoroso ma molto più facile da implementare, soprattutto per multiprocessori di notevoli dimensioni. Si basa su due concetti:
- Le scritture di ogni CPU sono percepite da tutte le altre CPU nello stesso ordine in cui sono state emesse.
- Per ogni parola di memoria, tutte le CPU vedono lo stesso ordine di scritture al suo interno.

La prima impone una certezza sull'ordine delle scritture eseguite sulla memoria da parte di tutte le CPU, mentre la seconda impone che non vi sia ambiguità su ciò che è stato scritto su un'area di memoria; tutti devono concordare su chi ha scritto per ultimo. Questo metodo, però, **non garantisce che tutte le CPU vedano le modifiche nello stesso ordine**, ma garantisce l'ordine delle scritture.
#### Consistenza debole
Questa non garantisce nemmeno l'ordine delle scritture, il che potrebbe farla sembrare ancora meno attenta. Per risolvere un po' del caos, questo sistema possiede delle variabili e delle operazioni di sincronizzazione, dove ogni CPU deve terminare il proprio lavoro e fermarsi.

Questa operazione effettua un **flush della pipeline** e conduce la memoria a uno stato stabile senza operazioni pendenti. Queste operazioni sono sequenzialmente consistenti, in quanto anche se vengono emesse da più CPU, tutti i processori percepiscono lo stesso ordine globale.

Queste sincronizzazioni, quindi, assicurano spazi temporali ordinati, ma non tutta la sequenza ordinata (vedere il libro fig. 8.25).
#### Consistenza dopo rilascio
La **consistenza debole** è inefficiente perché richiede il completamento di tutte le operazioni di memoria pendenti e blocca le nuove operazioni finché le precedenti non sono terminate. Un miglioramento a questo modello è la **consistenza dopo rilascio** (*release consistency*), che adotta un approccio simile alle sezioni critiche.

Quando un processo esce da una regione critica, non è necessario completare immediatamente tutte le scritture. Basta assicurarsi che vengano effettuate prima che un altro processo rientri nella regione critica. Questo modello suddivide l'operazione di sincronizzazione della consistenza debole in due operazioni distinte:
1. **acquire**: Prima di leggere o scrivere una variabile condivisa, la CPU deve eseguire un'operazione acquire sulla variabile di sincronizzazione per ottenere l'accesso esclusivo ai dati condivisi.
2. **release**: Al termine dell'uso della variabile condivisa, la CPU esegue un'operazione release per rilasciare l'accesso. La release non forza il completamento immediato di tutte le scritture pendenti, ma attende che tutte le scritture precedenti siano completate senza ritardare nuove operazioni di memoria.

Quando si esegue una acquire, si verifica se tutte le release precedenti sono state completate. Se non lo sono, la acquire rimane sospesa fino al loro termine. Questo schema evita di ritardare frequentemente le istruzioni, mantenendo comunque la consistenza.

La ricerca sui modelli di consistenza della memoria continua, con nuovi approcci in fase di sviluppo.

(Pagine riassunte: 4)
### 8.3.3 - Architetture di multiprocessori simmetrici UMA
I multiprocessori più semplici comunicano su un solo bus, uno alla volta, controllando se è libero e in caso inserendo l'indirizzo di memoria richiesto. Se il bus è occupato, la CPU deve aspettare che si liberi, rendendola inattiva.

Una soluzione è l'implementazione di una memoria cache, che riduce il carico del bus e permette alla CPU di eseguire alcune operazioni tramite questa. Il problema risulta nella coerenza della cache (vedremo dopo).

Un'ulteriore implementazione è la memoria privata con un bus dedicato, che permette alle CPU di attingere alla memoria condivisa solo per le variabili condivise; questo metodo richiede però una cooperazione attiva del compilatore, in quanto i programmi, le variabili e gli stack devono essere caricati nella memoria privata.
#### Cache snooping
Il problema della coerenza della cache emerge quando una CPU accede a dati aggiornati da un'altra CPU. Se la CPU 1 vuole leggere una linea di cache già modificata dalla CPU 2, può farlo, ma se entrambe accedono contemporaneamente alla stessa linea, potrebbero verificarsi problemi. La CPU 2 potrebbe ottenere una copia della linea e lavorarci, ma se la CPU 1 apporta modifiche, la CPU 2 lavorerà su **dati obsoleti**.

Questo è proprio il **problema della coerenza** o **consistenza della cache**. Vengono però proposte molte soluzioni che si presentano come **protocolli di coerenza della cache** e ora li analizzeremo.

Tutte queste sono accomunate da un principio di controllo sui trasferimenti del bus tramite dei dispositivi chiamati **snooping cache** o **snoopy cache**.

Il più semplice protocollo si chiama **write through**: se una CPU non trova un dato nella cache (*read miss*) il controllore carica nella cache il dato richiesto, così le successive letture saranno soddisfate (*read hit*) tenendo aggiornata la variabile. Un fallimento di scrittura (*write miss*) la parola modificata viene salvata in memoria e la linea contenente la parola non viene caricata nella cache. In caso di successo di scrittura (*write it*) viene aggiornata la cache e inoltre la parola viene scritta direttamente in memoria principale.

(Sul libro è rappresentato l'esempio del Cache Snooper in questa parte)

Esistono molte varianti del protocollo: una snooping cache potrebbe aggiornare un elemento anziché invalidarlo, che concettualmente equivale a un'invalidazione seguita da un caricamento dalla memoria principale. Ogni protocollo di cache deve scegliere tra aggiornamento e invalidazione, con prestazioni variabili a seconda dei carichi di lavoro. I messaggi di aggiornamento sono più grandi ma prevengono miss futuri. 

Un'altra variante prevede il caricamento nella snooping cache anche in caso di write miss; la scelta dipende dalla probabilità che la parola venga riscritta presto. Questa politica, chiamata **write-allocate**, può migliorare le prestazioni se tale probabilità è alta. Tuttavia, ogni operazione di scrittura che raggiunge la memoria tramite il bus può creare un collo di bottiglia, anche con poche CPU. 

Per ridurre il traffico sul bus, alcuni protocolli **write-back** assicurano che non tutte le scritture raggiungano direttamente la memoria, annotando la validità delle linee modificate, che verranno scritte in memoria solo dopo molte scritture.
##### Esempio effettivo Cache Snooper
Nell'analisi delle operazioni di una snooping cache, consideriamo due cache: cache 1 che esegue le operazioni e cache 2 che osserva. In caso di un read miss, cache 1 richiede una linea dalla memoria, e cache 2 osserva senza intervenire. Con un read hit, la richiesta viene soddisfatta localmente, quindi cache 2 non ne è a conoscenza. 

Le operazioni di scrittura sono più complesse: se la CPU1 effettua una scrittura, cache 1 invia una richiesta di scrittura sul bus sia in caso di hit che di miss. Cache 2 verifica se possiede la parola da scrivere; se non la possiede, non intraprende alcuna azione. Se invece la parola è presente in cache 2, questa la invalida per evitare dati obsoleti, rimuovendo l'elemento dalla cache. Poiché tutte le cache monitorano le richieste sul bus, ogni scrittura comporta l'aggiornamento della cache del richiedente e della memoria e l'invalidazione delle copie obsolete nelle altre cache, prevenendo incoerenze. Se la CPU di cache 2 deve leggere la parola successivamente, la leggerà dalla memoria aggiornata, mantenendo la coerenza tra cache 1, cache 2 e memoria. 
#### Protocollo MESI di coerenza delle cache
Il protocollo MESI è un protocollo di coerenza delle cache di tipo write-back, utilizzato, tra gli altri, dal Pentium 4 per lo snooping sul bus. MESI è acronimo di Modified, Exclusive, Shared e Invalid, che sono i quattro stati in cui si possono trovare gli elementi della cache. Questi stati sono: 

1. **Non valido**: l'elemento di cache non contiene dati validi.
2. **Condiviso**: la linea potrebbe essere presente in più di una cache e la memoria è aggiornata.
3. **Esclusivo**: nessun'altra cache contiene la linea e la memoria è aggiornata.
4. **Modificato**: l'elemento è valido ma la memoria non è aggiornata e non ci sono altre copie della linea.

Quando una CPU si avvia, tutti gli elementi della cache sono contrassegnati come non validi. Alla prima lettura, la linea referenziata viene prelevata dalla memoria e inserita nella cache della CPU con stato esclusivo, poiché è l'unica copia presente. Le letture successive utilizzano l'elemento della cache senza coinvolgere il bus. Se un'altra CPU preleva la stessa linea, la CPU originale viene informata tramite snooping e entrambe le copie vengono contrassegnate come condivise, indicando che la linea è presente in più cache e la memoria è aggiornata. 

Se la CPU2 scrive in una linea di cache che si trova nello stato condiviso, emette un segnale di invalidazione sul bus, indicando alle altre CPU di eliminare le loro copie, e la linea passa allo stato modificato. Se una linea si trova nello stato esclusivo durante una scrittura, non è necessario alcun segnale di invalidazione, poiché non ci sono altre copie. 

Quando la CPU3 legge una linea detenuta da CPU2 nello stato modificato, la CPU2 scrive la linea in memoria e la contrassegna come condivisa. La CPU3 può quindi prelevare la sua copia. Se la CPU2 successivamente scrive nella linea, la copia della CPU3 viene invalidata. Se la CPU1 scrive nella linea, la CPU2 richiede alla CPU1 di attendere la scrittura della linea in memoria, quindi la contrassegna come non valida. 

Se si usa la politica write-allocate, la linea viene caricata nella cache e contrassegnata come modificata. Altrimenti, la scrittura avviene direttamente in memoria e la linea non viene caricata in alcuna cache.
#### Multiprocessori UMA con commutatori crossbar
Per quanto si possa ottimizzare il sistema, un bus non è sufficiente per 16 o 32 CPU. Per questo motivo si utilizza un meccanismo chiamato **commutatore crossbar**, utilizzato anche nei centralini telefonici, che collega k CPU a k memorie.

Ad ogni intersezione tra le linee verticali di uscita e quelle orizzontali di ingresso, c'è un **crosspoint**, un piccolo commutatore che può essere aperto o chiuso. Quando viene chiuso, permette la comunicazione con la linea intersecata (vedere fig. 8.29 (a)) e vengono chiusi per impedire che i collegamenti formati si intreccino, come nel gioco degli scacchi dove le torri non si attaccano.

Queste reti sono **non bloccanti**, quindi non viene mai negato un collegamento a una CPU e non necessitano di pianificazione per nuovi collegamenti. Tuttavia, presentano limiti fisici all'aumentare del numero di CPU e memorie.
#### Multiprocessori UMA con reti a commutazione multilivello
Supponendo di organizzare ora questi collegamenti con un commutatore 2 x 2 con due ingressi e due uscite. I messaggi possiamo impostarli in quattro parti per comodità: modulo di memoria da usare, indirizzo del modulo, opcode dell'operazione e valore.

Come rendere questo un metodo ottimale per sistemi più complessi? Abbiamo una possibilità economica e senza problemi, la **rete omega**.

Collega n CPU a n memorie con $\log_{2}{n}$ **livelli** di $\frac{n}{2}$ commutatori ciascuno, quindi $\log_{2}{n}\frac{n}{2}$ commutatori, molto più efficiente del sistema precedente. Spesso ci si riferisce a questa rete con il termine **mescolamento perfetto**. Al ricevimento di un segnale di READ, il primo commutatore al primo livello legge il primo bit del modulo richiesto, se è 0 lo instrada verso le linee superiori, viceversa con 1. Diventando inutili questi bit, verranno sostituiti con l'indirizzo del destinatario, per rimandare indietro la richiesta.

A differenza della rete con commutatori a crossbar però questa è una rete **bloccante**, cioè che non permette in caso di conflitti nei commutatori di far passare ogni richiesta. Una tecnica comune è quella di usare i bit meno significativi come numero di modulo, così da distribuire parole consecutive in diversi moduli (Quindi un modulo non ha tutte parole consecutive, ma diversi moduli hanno diverse parole consecutive). Un sistema di memoria in cui le parole consecutive si trovano in moduli diversi si chiama **interlacciato** e massimizza il parallelismo perché i riferimenti della memoria sono consecutivi.

(Pagine riassunte: 8.5)
### 8.3.4 - Multiprocessori NUMA
I processori UMA a singolo bus sono limitati a una dozzina di bus, mentre quelli con rete omega o a commutazione crossbar sono molto costosi. Per raggiungere centinaia di CPU bisogna abbandonare l'idea che tutti i moduli di memoria abbiano lo stesso tempo di accesso. Questo è il principio dei multiprocessori di tipo **NUMA** che, come i sistemi UMA, gestiscono un unico spazio di indirizzamento, ma offrono un accesso più veloce ai moduli di memoria vicini.

I sistemi NUMA si caratterizzano per tre aspetti principali:
- Hanno un unico spazio di indirizzamento visibile a tutte le CPU.
- L'accesso alle memorie distanti avviene tramite istruzioni LOAD e STORE.
- L'accesso alla memoria distante è più lento rispetto a quella vicina.

Si parla di **NC-NUMA** quando manca il sistema di caching, e di **CC-NUMA** quando sono presenti cache coerenti.

Un esempio di multiprocessore NC-NUMA è il Cm*. Come illustrato nella figura 8.32, ogni CPU ha una memoria locale con un proprio bus e una **MMU** (Memory Management Unit). La MMU determina se una richiesta di accesso alla memoria è locale o esterna e inoltra la richiesta rispettivamente sul bus locale o sul bus di sistema. Le richieste esterne richiedono un tempo di accesso dieci volte superiore rispetto a quelle interne, ma permettono comunque di eseguire le operazioni necessarie.

Nel sistema NC-NUMA, la coerenza è garantita poiché non esiste cache, quindi ogni parola ha una sola locazione di memoria. Tuttavia, questo richiede una gestione ottimale della posizione di ogni parola.

Per migliorare l'efficienza, esiste solitamente un processo demone chiamato **scanner delle pagine**. Questo scanner, eseguito a intervalli di pochi secondi, analizza le statistiche di utilizzo e rimuove le pagine mal posizionate. Quando si verifica un errore di accesso a una variabile, lo scanner sa dove posizionare correttamente la pagina. Per evitare errori, ogni pagina ha un intervallo di vita definito durante il quale non può essere eliminata.
#### Multiprocessore NUMA con cache coerente
All'aumentare delle CPU nel sistema, la mancanza di caching penalizza le performance; pur implementando lo snooping, sarà difficile mantenere la coerenza nella cache in sistemi di grandi dimensioni.

Il metodo più comune per costruire grandi multiprocessori oggi è il **CC-NUMA** (Cache-Coherent NUMA), un sistema *multiprocessore basato su directory*. Questi sistemi sono divisi in nodi, ognuno dei quali contiene una CPU, una RAM e una *directory*. Quando una CPU emette un'istruzione e la passa alla MMU, l'indirizzo viene diviso in **nodo**, **linea** e **offset**. Se la parola richiesta si trova in un altro nodo, viene inviata una richiesta attraverso la *rete d'interconnessione* al nodo corretto per verificare se possiede la linea richiesta in cache e, in caso affermativo, dove si trovi.

La richiesta viene instradata all'hardware della directory del nodo, che usa l'indice per cercare la linea nella tabella. Se la linea non è presente nella tabella (quindi non è in cache), viene estratta dalla RAM, l'elemento nella directory viene aggiornato per indicare che la linea appartiene al nodo richiedente e la linea viene inviata a quest'ultimo. Se invece la linea è presente nella cache del nodo, l'hardware aggiorna la linea imponendo come valore il nodo richiedente e chiede al nodo trovato nella directory di consegnare la linea al richiedente e invalidare la propria cache.

La restrizione di questo progetto è che una linea si trovi per lo più nella cache di un solo nodo, per motivi implementativi ed economici. Si potrebbe risolvere il problema implementando in ogni directory k campi che individuano gli altri nodi, consentendo il caching di una linea in k nodi. Un'altra soluzione è sostituire ogni numero del nodo con una bitmap in cui ogni bit corrisponde a un nodo, eliminando il limite sul numero di copie di una linea, ma aumentando significativamente le informazioni accessorie. Una terza possibilità è gestire un campo a 8 bit in ogni elemento della directory che corrisponde a un puntatore a una lista concatenata di tutte le copie della linea di cache corrispondente.

Non tratteremo però le migliorie specifiche.
#### Il multiprocessore NUMA Sun Fire E25k (saltato)

(Pagine riassunte: 9)
### 8.3.5 - Multiprocessori COMA
Le macchine precedentemente analizzate presentano diversi problemi all'aumentare della grandezza del multiprocessore, come lenti accessi alla memoria distante, fallimenti di cache e colli di bottiglia, principalmente legati alla gestione della memoria e alla distanza delle chiamate.

Usare ogni memoria principale di una CPU come cache risolve questi problemi, ed è il principio del progetto **COMA** (Cache Only Memory Access), che non richiede che ogni pagina abbia una macchina prefissata di appartenenza come nei NUMA e CC-NUMA. Lo spazio di indirizzi fisici è diviso in linee di cache che vengono trasferite all'interno del sistema su richiesta.

Una memoria che si limita ad attrarre le linee richieste si chiama **memoria attrattiva**. Il principio della RAM principale come grande cache aumenta notevolmente il tasso di hit e le performance, ma comporta altri problemi: come localizzare le linee di cache e cosa succede quando viene estromessa dalla memoria l'ultima copia di una linea.

Per risolvere il primo problema, si può mappare le pagine intere in una bitmap, dove ciascun bit corrisponde a una linea di cache e ne indica la presenza o assenza. Questo è un tipo di **COMA semplice** o **S-COMA**; se una linea è presente, deve trovarsi nella posizione corretta della sua pagina. Se non è così, il tentativo di usarla causerà una trap che porterà il software a cercarla e caricarla. Metodi per migliorare la ricerca delle linee distanti includono associare una macchina di appartenenza solo al suo elemento di directory oppure organizzare la memoria ad albero e cercare verso l'alto fino a trovarla.

Per il secondo problema, basta non cancellare l'ultima copia di una linea; si può anche interrogare la directory per verificare se ci sono altre copie e, in caso affermativo, eliminarle.

(Pagine riassunte: 1.5)
## 8.4 - Multicomputer a scambio di messaggi
Abbiamo già trattato le differenze tra multicomputer e multiprocessori; sommando tutte le competenze acquisite ora arriviamo a differenze prestazionali ed economiche molto significative. 

Il sistema operativo percepisce i multiprocessori come dotati di memoria condivisa su cui eseguono istruzioni di load e store. Tuttavia, i multiprocessori hanno l'enorme svantaggio economico di non poter ospitare un gran numero di calcolatori, mentre i multicomputer eccellono in questo aspetto.

Vedremo nel capitolo successivo che, sebbene i multiprocessori abbiano raggiunto configurazioni con 72 chip a doppia CPU (come nel Sun E25K), esistono multicomputer con fino a 65.536 CPU. Anche se i multiprocessori sono molto più semplici da sviluppare per i programmatori, i multicomputer sono allettanti per la loro potenza di calcolo parallelo.

I multicomputer operano tramite le primitive *send* e *receive* per lo scambio esplicito di messaggi e sono implementati in sistemi con reti di scambio ad alta velocità. Per una maggiore comprensione, si può fare riferimento alla figura 8.36, che mostra come siano costituiti da diversi elementi (che possiamo vedere come se fossero computer) che comunicano tra loro attraverso una rete di interconnessione molto veloce.

(Pagine riassunte: 1)
### 8.4.1 - Reti d'interconnessione
Similmente ai multiprocessori, abbiamo visto che i multicomputer posseggono una rete di interconnessione che collega tutti i nodi. Entrambe sono reti di scambio messaggi o meglio **pacchetti** ed è una caratteristica comune ad ogni elaboratore di dati.
#### Topologia
La topologia dei collegamenti definisce come vengono effettuati i collegamenti in una rete d'interconnessione ed è rappresentata tramite grafi. Ogni nodo ha dei collegamenti in uscita, il cui numero è chiamato **grado del nodo** o **fanout**. Un maggiore fanout offre più possibilità di instradamento e riduce gli errori; una rete di grado k può rimanere operativa anche senza k - 1 collegamenti.

Altre caratteristiche importanti includono:
- **Diametro** della rete d'interconnessione: il percorso più lungo tra due nodi, rappresentando il caso peggiore.
- **Larghezza di banda di bisezione**: la capacità di trasmissione al secondo, ottenuta dividendo la rete a metà e scollegando i nodi tra le due parti. La larghezza di banda di bisezione è il numero più basso di collegamenti rimossi tra tutte le possibili divisioni, rappresentando il caso peggiore di trasferimento.
- **Dimensionalità**: il numero di modi con cui un nodo può raggiungere un altro nodo. Una rete è *zero-dimensionale* se non ci sono alternative di percorso, *uno-dimensionale* se c'è una scelta (ad esempio, andare a destra o sinistra), *due-dimensionale* con due assi, e così via.

Esistono diversi modi per creare una rete di connessione (vedi fig. 8.37):
- **Stella**: ogni nodo è collegato a un nodo centrale usato solo per la commutazione, ma diventa un collo di bottiglia con l'aumento delle richieste.
- **Interconnessione completa**: un grafo completo dove ogni nodo è collegato a ogni altro nodo, molto efficiente ma costoso.
- **Albero**: presenta problemi di larghezza di banda di bisezione; il traffico vicino alla radice diventa un collo di bottiglia. Può essere migliorato con un **albero grasso**, dove i nodi vicino alla cima hanno maggiore capacità di collegamento.
- **Anello**: ogni nodo è collegato ai suoi adiacenti, di tipo monodimensionale.
- **Griglia o mesh**: un progetto bidimensionale molto usato a livello commerciale, regolare e facile da implementare. Il diametro cresce con la radice quadrata del numero di nodi. Una variante migliorata è il **toro**, dove i vertici opposti sono collegati tra loro, riducendo errori e diametro.
- **Cubo**: un tipo tridimensionale che può essere esteso a quattro dimensioni duplicandolo e collegando i nodi corrispondenti. Lo stesso vale per le cinque dimensioni e oltre, formando un **ipercubo n-dimensionale**.

(Pagine riassunte: 3.5)
### 8.4.2 - Massive Parallel Processors
La prima categoria di multicomputer è la **MPP** (Massive Parallel Processors), enormi computer con costi di svariati milioni, successori dei mainframe. Utilizzano calcolatori standard e sono dotati di una rete di interconnessione ad alta banda e velocità, con software brevettati. Gli MPP hanno un'enorme capacità I/O e operano generalmente con trasferimenti di piccoli pacchetti. Presentano una bassa tolleranza agli errori, che possono bloccare calcoli importanti per ore, quindi sono dotati di hardware e software di controllo per mitigare questi problemi.
#### BlueGene (Saltato)

#### Red Storm (saltato)


(Pagine riassunte: 10)
### 8.4.3 - Cluster
Un'altra categoria di multicomputer è rappresentata dai **cluster di computer**, costituiti da migliaia di computer o workstation collegati tramite schede di rete. I cluster possono essere paragonati ai MPP come i PC ai mainframe, specialmente per quanto riguarda l'ambito di utilizzo. Grazie all'evoluzione dei computer e al mercato sempre più accessibile, i cluster rendono gli MPP utili solo in situazioni molto specifiche e di nicchia.

Esistono due tipi particolari di cluster: **centralizzati** e **decentralizzati**. I cluster centralizzati sono costituiti da agglomerati di PC disposti in sale o scaffali in modo compatto (**headless workstations**), mentre i cluster decentralizzati sono formati da PC distribuiti in un edificio o campus. I cluster decentralizzati sono generalmente dotati di molte periferiche, sono eterogenei e risultano molto complessi da implementare.
#### Google
Uno dei più grandi colossi multinazionali gestisce il motore di ricerca più potente e veloce al mondo, se non il più utilizzato. Trova, indicizza e memorizza oltre 40 miliardi di pagine del **World Wide Web**, permettendo ricerche in meno di mezzo secondo per utenti di tutto il mondo contemporaneamente. Sebbene sia semplice da usare, il sistema è altamente complesso. Vediamolo in dettaglio.

Google è strutturato in centri *decentralizzati* in tutto il mondo. Quando viene effettuata una richiesta, l'IP dell'utente viene esaminato e la richiesta viene inoltrata al centro più vicino. Questi centri utilizzano tecnologie di trasferimento ad alta velocità (2,488 Gbps) con connessioni di backup e dispongono di riserve di energia e motori di emergenza, rendendo Google quasi inarrestabile.

Analizziamo una *query* inviata a Google. Il *bilanciatore di carico* instrada la richiesta verso un *interrogatore di query*, che a sua volta invia la richiesta in parallelo al *correttore ortografico* e al *server pubblicità*. Le parole di ricerca vengono analizzate in parallelo nei server degli indici, che contengono un elemento per ogni parola presente nel web. Ogni elemento presenta tutti i documenti legati a quella parola, ordinati secondo il **PageRank**, un algoritmo segreto basato principalmente sul numero di collegamenti entranti nella pagina e il rank delle pagine da cui provengono.

Per incrementare le prestazioni, gli indici sono divisi in **shard**. La shard 1 contiene tutte le parole indicizzate e gli ID dei primi n documenti, la shard 2 contiene tutte le parole e gli n documenti successivi, e così via. Al crescere del web, le shard si scomporranno ulteriormente.

I server degli indici restituiscono un insieme di identificativi di documenti, combinati secondo le relazioni booleane della query. Successivamente, si accede ai documenti per ottenere titoli, URL ed estratti di testo. I risultati vengono poi rispediti al gestore delle interrogazioni, che li riordina secondo il PageRank. Se vi sono errori ortografici, vengono segnalati, e vengono aggiunti annunci pubblicitari pertinenti alla ricerca. Tutti i risultati sono formattati in *HTML*.

Proprio come nei cluster di workstation, Google non ha acquistato un enorme centro di calcolo dal costo di miliardi, ma ha suddiviso il carico tra molti computer economici reperibili sul mercato. Il software è progettato per gestire errori, sia hardware che software. Ironicamente, la prima soluzione a un problema è spesso riavviare il sistema interessato.

Tre lezioni chiave nella gestione dei server che Google ha appreso vi è:
- I componenti sono soggetti ad anomalie, quindi è necessario prevederle a priori.
- Duplicare i componenti aumenta la produttività e le risorse disponibili.
- È conveniente ottimizzare il rapporto prezzo/prestazioni.

(Pagine riassunte: 5.5)
### 8.4.4 - Software di comunicazione per multicomputer
Per la gestione effettiva della comunicazione tra i nodi di un multicomputer e la sincronizzazione. I sistemi a scambio di messaggi eseguono due o più processi in modo indipendente, anche se qualche d'uno potrebbe produrre dati che devono essere usati da altri processi. Neanche è possibile sapere se il destinatario sarà pronto quando il mittente ha i dati disponibili.

Molti sistemi a scambio di messaggi forniscono delle primitive *send* e *receive* ma ci sono ulteriori metodi:
- **Scambio sincrono di messaggi**; se il mittente esegue una send esso viene bloccato fino a che il destinatario non invia un receive. Al cedere nuovamente il controllo della chiamata al mittente, questo è sicuro che il messaggio è stato spedito e copiato correttamente. La limitazione ovviamente risiede nella sincronia (mette in attesa il mittente).
- **Scambio di messaggi bufferizzato**; il messaggio viene inviato dal mittente direttamente in uno slot di buffer, che copierà il messaggio non appena il destinatario invierà una richiesta di receive. Il mittente può riprendere il proprio lavoro subito dopo l'invio, ma non saprà se il messaggio è arrivato correttamente.
- **Scambio di messaggi non bloccante**, come il precedente, ma il mittente non può usare il buffer fino a che non è certo che è svuotato. Usa quindi il sistema operativo per cercare, tramite un interrupt o del *polling* sul sistema, di capire se può usare nuovamente il buffer.
#### MPI - Interfaccia a scambio di messaggi
Successore del precedente software **PVM** (Parallel Virtual Machine), arriva **MPI** (Message-Passing Interface), che non si occupa più di creare o gestire i processi, compito che spetta all'utente tramite chiamate di sistema locali. Una volta creati, i processi sono organizzati in gruppi statici che non possono essere modificati; MPI opera a livello di questi gruppi.

MPI si basa su quattro concetti principali:
1. **Comunicatori**: un gruppo di processi uniti a un contesto, che è un'etichetta usata per identificare una fase di esecuzione. Il contesto viene usato per evitare che i messaggi interferiscano tra loro durante la spedizione o ricezione.
2. **Tipi di dati nei messaggi**: ogni messaggio ha un tipo che rappresenta cosa sta essendo spedito o ricevuto. Esistono tipi primitivi, come interi, caratteri o numeri in virgola mobile con precisione singola o doppia, ma anche tipi derivati.
3. **Operazioni di comunicazione**: MPI supporta quattro modalità base di comunicazione disponibili sia in modalità bloccante che non bloccante:
   - **Sincrona**: come descritto nell'introduzione.
   - **Bufferizzata**: come descritto nell'introduzione.
   - **Standard**: dipende dall'implementazione e può essere una delle modalità precedenti.
   - **Pronto**: il mittente suppone che il destinatario sia pronto anche se non ne è certo.
   Nelle forme di comunicazione collettiva, i processi devono effettuare la chiamata e usare in maniera appropriata gli argomenti (ad esempio, nei processi organizzati ad albero).
4. **Topologie virtuali**: permette all'utente di specificare l'organizzazione del processo (ad albero, anello, griglia, ecc.).

(Pagine riassunte: 2.5)
### 8.4.5 - Scheduling
La gestione dei processi e la creazione dei compiti nel sistema MPI comportano una sfida di *gestione temporale* dei job. Quando devono essere eseguiti, chi deve essere eseguito per primo, e da chi sono tutte questioni che vengono organizzate dallo *scheduler*.

Lo scheduler, una volta informato del numero di CPU necessarie per un job, può gestirlo in diversi modi:
- **FIFO**: i compiti vengono eseguiti in ordine sequenziale di arrivo. Appena c'è disponibilità di CPU, lo scheduler le associa ai job in attesa. Più job possono essere eseguiti contemporaneamente se ci sono abbastanza CPU disponibili.
- **Senza bloccaggio testa coda**: questo metodo seleziona continuamente il primo job compatibile con l'intervallo di tempo disponibile, minimizzando il numero di CPU in idle.
- **Tiling**: lo scheduler richiede sia il tempo necessario per completare il job in minuti, sia il numero di CPU richieste. In questo modo, può ottimizzare l'allocazione dei compiti per ridurre al minimo il tempo di idle, migliorando ulteriormente l'efficienza rispetto al metodo precedente.

(Pagine riassunte: 1)
### 8.4.6 - Memoria condivisa a livello applicativo
Il sistema di scambio messaggi MPI non è molto amato dai programmatori, che preferirebbero lavorare con l'illusione di una memoria condivisa. Raggiungere sia la potenza di calcolo con macchine economiche che la semplicità di programmazione è uno degli obiettivi fondamentali di questi studi. Sebbene non esista una memoria condivisa fisica, come accennato in precedenza, questa può essere simulata a livello software, anche se non  implementabile a livello hardware.
#### Memoria condivisa distribuita
Un tipo di sistema a memoria condivisa a livello applicativo è quello dei sistemi basati su pagine, spesso chiamati **DSM** (Distributed Shared Memory). Un insieme di CPU di un multicomputer condivide uno spazio di indirizzi virtuali paginato (come illustrato in figura 8.46).

Quando una CPU richiede una pagina locale, non ci sono problemi. Tuttavia, se la pagina non è disponibile localmente, si genera un errore. In questo caso, la pagina non viene caricata dal disco; invece, il sistema runtime o il sistema operativo inviano un segnale al nodo che possiede la pagina per trasferirla al nodo richiedente. Alla fine, l'errore è risolto poiché la pagina diventa locale per la CPU richiedente. Alcune implementazioni permettono di mantenere la pagina originale nel nodo di appartenenza e una copia nel nodo richiedente.

La presenza di una sola copia di una pagina costringe il sistema a farla girare avanti e indietro, creando il problema noto come **falsa condivisione**. Una possibile ottimizzazione è di dichiarare inizialmente le pagine scrivibili come di sola lettura. Quando viene sollevato l'errore per la scrittura, il sistema crea una copia della pagina, chiamata **pagina gemella**. La pagina originale viene impostata in modalità lettura/scrittura, e le scritture successive possono procedere. Se successivamente si verifica un altro errore, la pagina viene inviata al nodo richiedente, e viene fatto un confronto parola per parola tra questa e la pagina gemella. Solo le modifiche vengono inviate, riducendo la dimensione del messaggio.

Per la ricerca delle pagine non trovate, si possono implementare gli stessi metodi usati nei sistemi NUMA e COMA.

(Pagine riassunte: 7.5)
### 8.4.7 - Prestazioni
Lo scopo del parallelismo è migliorare le performance e il lato economico di un sistema, confrontandolo a quello monocalcolatore. In questo capitolo tratteremo i parametri di analisi delle prestazioni e le ottimizzazioni che si fanno.
#### Parametri di valutazione hardware
I principali componenti analizzati sono la CPU, l'I/O e la rete di interconnessione. Esistono due concetti chiave per questi componenti: la **latenza** e la **larghezza di banda**.

La latenza (*roundtrip latency*) è il tempo necessario affinché un pacchetto venga inviato, processato e ritorni. Questo dipende dalla destinazione del collegamento, che può essere la memoria, una CPU, o un altro dispositivo, e dal tipo di instradamento utilizzato:
- **Commutazione di circuiti**: La latenza dipende dal tempo di configurazione e di trasferimento, inclusa l'invio di un pacchetto sonda che prepara il trasferimento allocando le risorse.
- **Commutazione di pacchetto**: La latenza è influenzata dal tempo di configurazione e dall'assemblaggio del pacchetto, sommato al ritardo introdotto dai commutatori e al tempo necessario per attraversarli.
- **Wormhole routing**: La latenza dipende dal tempo di configurazione iniziale per assemblare il pacchetto e dal tempo di trasferimento, con l'aggiunta del tempo di propagazione, che è spesso trascurabile.

L'altra metrica hardware è la larghezza di banda, in particolare la **larghezza di banda complessiva**, che è la somma delle capacità di tutti i collegamenti e rappresenta il massimo numero di bit che può transitare simultaneamente sulla rete.
#### Parametri di valutazione software
Oltre all'hardware l'utente è interessato a capire quanta effettiva differenza c'è tra girare un sistema su un monoprocessore e un multicomputer.

Un ottimo sistema per rappresentare ciò è un grafico dell'incremento di velocità in funzione del numero di CPU. Potrei trattare tutti gli esempi, ma generalmente ogni applicativo ha diversi grafici, più tende verso l'alto meglio è implementato e l'unico con incremento quasi lineare è il **problema degli n-corpi**.

Il motivo per cui non si può raggiungere la linearità risiede nei programmi che richiedono esecuzioni sequenziali, che devono essere quindi associate ad una CPU esclusiva.
#### Miglioramento delle prestazioni
Generalmente, aumentare il numero di CPU fino a evitare colli di bottiglia migliora le prestazioni; tali sistemi si chiamano **scalabili**. Un esempio è il confronto tra un sistema a bus e un sistema a griglia. Idealmente, un sistema scalabile dovrebbe mantenere latenza e banda costanti, ma nella pratica l'aumento della banda provoca un notevole incremento della latenza con l'aumentare delle dimensioni del progetto. La latenza è cruciale in molte applicazioni, quindi i progettisti hanno sviluppato varie tecniche per ridurla.

Una tecnica utile è il **caching**, dove una o più copie dei dati sono conservate vicino alle locazioni che li utilizzano o a cui "appartengono". Questo crea copie di livelli e gerarchie diverse, risolvendo il problema tramite un aggiornamento continuo dei dati.

Un'altra tecnica è il **prefetching**, che prevede il caricamento anticipato di un dato prima che sia necessario. La lettura può essere sovrapposta alla normale esecuzione, rendendo il dato già disponibile quando richiesto. Questa operazione può essere gestita dal compilatore, se è consapevole della macchina su cui gira.

Il **multithreading** è un'altra tecnica già trattata in precedenza.

Infine, le **scritture non bloccanti** rappresentano una tecnica avanzata, difficile da realizzare, ma che permette di non bloccare il programma durante l'esecuzione dell'istruzione di scrittura.

(Pagine riassunte: 6.25)
## 8.5 - Grid Computing

(Pagine riassunte: 3)