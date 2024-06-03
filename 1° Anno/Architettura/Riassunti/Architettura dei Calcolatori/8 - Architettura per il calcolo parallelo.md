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
## 8.3 - Multiprocessori con memoria condivisa
### 8.3.1 - Multiprocessori e multicomputer a confronto
### 8.3.2 - Semantica della memoria
### 8.3.3 - Architetture di multiprocessori simmetrici UMA
### 8.3.4 - Multiprocessori NUMA
### 8.3.5 - Multiprocessori COMA
## 8.4 - Multicomputer a scambio di messaggi
### 8.4.1 - Reti d'interconnessione
### 8.4.2 - Massive Parallel Processors
### 8.4.3 - Cluster
### 8.4.4 - Software di comunicazione per multicomputer
### 8.4.5 - Scheduling
### 8.4.6 - Memoria condivisa a livello applicativo
### 8.4.7 - Prestazioni
## 8.5 - Grid Computing