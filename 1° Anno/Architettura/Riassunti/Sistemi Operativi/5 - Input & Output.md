Oltre a fornire astrazioni come processi e thread, spazi degli indirizzi e file, un sistema operativo controlla anche tutti i dispositivi di I/O del computer, inviando comandi ai dispositivi, intercettando gli interrupt e gestendo gli errori. 

Per prima cosa vedremo alcuni dei principi dell’hardware per l’I/O, poi analizzeremo il software per l’I/O in generale. Il software per l’I/O può essere strutturato in livelli (layer), dove ciascuno svolge un’attività ben precisa.
## 5.1 - Principi hardware dell'I/O
L’hardware per l’I/O viene considerato da punti di vista diversi: gli ingegneri elettronici lo giudicano in termini di chip, cavi, alimentatori, motori e di qualsiasi altro componente fisico. I programmatori sono interessati all’interfaccia disponibile al software: comandi accettati dall’hardware, funzioni eseguibili e possibili errori. Il nostro interesse è focalizzato sulla programmazione dell’hardware e non sul suo funzionamento interno.

(pagine riassunte: 0.75)
### 5.1.1 - Dispositivi di I/O
I dispositivi di I/O si dividono principalmente in due categorie: **dispositivi a blocchi** e **dispositivi a caratteri**.
1. **Dispositivi a blocchi**: Archiviazione di informazioni in blocchi di dimensioni fisse, ciascuno con il proprio indirizzo. I trasferimenti avvengono in unità di uno o più blocchi consecutivi. Ogni blocco può essere letto o scritto indipendentemente dagli altri. Esempi: dischi rigidi magnetici e unità SSD.
2. **Dispositivi a caratteri**: Gestione di un flusso di caratteri senza struttura a blocchi, non indirizzabili e senza operazioni di ricerca. Esempi: tastiere e stampanti.
Questa classificazione non è perfetta, poiché alcuni dispositivi non rientrano in queste categorie, come i clock, che non sono indirizzabili a blocchi e non gestiscono flussi di caratteri, ma generano solo interrupt a intervalli definiti.

Nonostante le limitazioni, la suddivisione in dispositivi a blocchi e a caratteri è utile per rendere il software del sistema operativo indipendente dal tipo di dispositivo, come nel caso del file system, che si occupa solo di dispositivi a blocchi astratti.

Le diverse velocità dei dispositivi di I/O rappresentano una sfida per il software, che deve garantire buone prestazioni nel trasferimento dei dati.

(pagine riassunte: 0.75)
### 5.1.2 - Controller dei dispositivi
I dispositivi di I/O sono composti da una componente meccanica e una elettronica. La parte elettronica è chiamata **controller del dispositivo** o **adattatore**, mentre la parte meccanica è il dispositivo stesso. Questa separazione consente una progettazione modulare e standardizzata.

Se l'interfaccia tra controller e dispositivo segue standard ufficiali (ANSI, IEEE, ISO) o _de facto_, i produttori possono creare controller o dispositivi compatibili.

Il flusso seriale di bit che esce dal dispositivo inizia con un **preambolo** (contenente informazioni come il numero dei cilindri e dei settori), seguito dai 4096 bit del settore e da una **checksum** o **codice di correzione degli errori** (**ECC**). Il controller converte questo flusso in un blocco di byte, esegue le correzioni degli errori e, dopo aver verificato l'integrità dei dati, copia il blocco nella memoria principale.

I monitor LCD hanno rapidamente sostituito i vecchi monitor a **tubo catodico** (**CRT**). I CRT utilizzano un raggio di elettroni per disegnare i pixel su uno schermo fluorescente. Gli LCD, rispetto ai CRT, sono più leggeri, consumano meno energia e sono più resistenti. Inoltre, gli schermi LCD moderni hanno una risoluzione così alta che l'occhio umano non può distinguere i singoli pixel.

(pagine riassunte: 1)
### 5.1.3 - Input/Output mappato in memoria
I dispositivi di I/O comunicano con la CPU tramite registri di controllo e buffer di dati. Il sistema operativo scrive nei registri per dare comandi al dispositivo e legge da essi per conoscere lo stato del dispositivo.

Due approcci per la comunicazione CPU-dispositivo sono: l'uso di **porte di I/O** e l'**I/O mappato in memoria**. Nel primo metodo, i registri di controllo hanno un numero di porta di I/O associato e sono accessibili tramite istruzioni speciali IN e OUT. Nel secondo metodo, i registri di controllo sono mappati nello spazio della memoria.

L'I/O mappato in memoria ha vantaggi come l'accessibilità dai linguaggi ad alto livello, la facilità di protezione dai processi utente e la possibilità di riferimento tramite istruzioni di memoria. Tuttavia, richiede complessità aggiuntiva per gestire la cache e potrebbe causare conflitti in sistemi con più bus.

L'utilizzo di porte di I/O è più semplice in termini di gestione della cache ma potrebbe causare ritardi nel bus della memoria dedicato. Soluzioni alternative includono l'uso di un dispositivo "spia" sul bus della memoria o il filtraggio degli indirizzi sul bridge PCI.

Entrambi gli approcci presentano compromessi e richiedono decisioni di progettazione ponderate, specialmente per garantire la compatibilità con sistemi legacy.

(pagine riassunte: 3.25)
### 5.1.4 - Direct memory access (DMA)
La CPU può comunicare con i controller dei dispositivi tramite l'accesso diretto alla memoria (DMA). Il DMA consente il trasferimento di dati tra memoria e dispositivi senza coinvolgere continuamente la CPU, migliorando l'efficienza.
#### Processo di DMA:
1. **Programmazione del Controller DMA**: La CPU configura il controller DMA impostando i registri per specificare il trasferimento dei dati.
2. **Richiesta di Lettura**: Il controller DMA invia una richiesta di lettura al controller del disco.
3. **Scrittura in Memoria**: Il controller DMA esegue l'operazione di scrittura in memoria.
4. **Conferma**: Il controller del disco invia un segnale di conferma al controller DMA.
5. **Aggiornamento degli Indirizzi**: Il controller DMA incrementa l'indirizzo di memoria e decrementa il conteggio dei byte.
#### Modalità di Operazione del DMA:
- **Cycle Stealing**: Il controller DMA ruba cicli di bus dalla CPU per trasferire i dati, rallentando leggermente la CPU.
- **Modalità Burst**: Il controller DMA acquisisce il bus per una serie di trasferimenti consecutivi, rilasciandolo poi. Questa modalità è più efficiente.
#### Fly-by Mode:
In questa modalità, il controller DMA dirige il trasferimento dei dati direttamente dalla periferica alla memoria principale senza intermediari, sebbene alcuni controller DMA utilizzino un ciclo extra per trasferire dati da dispositivo a dispositivo o da memoria a memoria.
#### Utilizzo di Buffer Interni:
I controller del disco utilizzano buffer interni per:
- Verificare la checksum prima del trasferimento per assicurarsi che i dati non siano corrotti.
- Gestire la velocità costante dei bit in arrivo dal disco, evitando perdite di dati.
#### Vantaggi e Svantaggi del DMA:
- **Vantaggi**: Efficienza nel trasferimento dei dati e riduzione del carico sulla CPU.
- **Svantaggi**: La CPU potrebbe essere più veloce del controller DMA in alcuni sistemi, rendendo il DMA superfluo e aumentando i costi di implementazione.
#### Applicazione nei Sistemi:
Il DMA è comune nei sistemi con controller dedicati e complessi, mentre nei sistemi a basso costo (come quelli embedded), la CPU potrebbe gestire direttamente i trasferimenti per risparmiare sui costi hardware.

(pagine riassunte: 3)
### 5.1.5 - Ancora sugli interrupt
Gli interrupt hardware funzionano come segue: quando un dispositivo di I/O completa un'operazione, invia un segnale di interrupt tramite una linea del bus al controller degli interrupt della scheda madre. Il controller decide come gestire l'interrupt in base alla priorità e, se necessario, lo invia alla CPU interrompendo l'attuale esecuzione. La CPU utilizza il numero dell'interrupt per accedere a una tabella, chiamata vettore degli interrupt, che contiene gli indirizzi delle procedure di servizio degli interrupt.

Durante un interrupt, la CPU salva le informazioni essenziali, come il contatore di programma, per poter riprendere l'esecuzione interrotta. Queste informazioni sono generalmente salvate nello stack, che può essere problematico se si tratta dello stack utente, portando a errori gravi. Usare lo stack del kernel è più sicuro, ma può comportare la necessità di cambiare il contesto della MMU e invalidare la cache, aumentando il tempo di gestione dell'interrupt.

Il software gioca un ruolo importante nella gestione degli interrupt, coordinando con l'hardware per garantire che le operazioni di I/O siano eseguite correttamente e efficientemente.
#### 5.1.5.1 - Interrupt precisi e imprecisi
In sistemi informatici moderni, soprattutto quelli che utilizzano pipeline e architetture superscalari, la gestione degli interrupt presenta sfide particolari. Nei vecchi sistemi, quando si verificava un interrupt, tutte le istruzioni fino a quel momento erano già state eseguite completamente. Tuttavia, con l'introduzione della pipeline e delle architetture superscalari, questo non è sempre vero.

Nei moderni processori, se si verifica un interrupt mentre la pipeline è piena, molte istruzioni potrebbero essere in vari stati di esecuzione. Anche in architetture superscalari, le istruzioni possono essere divise in micro-operazioni e eseguite in ordine sparso. Questo può portare a una situazione in cui, al momento dell'interrupt, molte istruzioni sono in vari stati di avanzamento, complicando la gestione dell'interrupt.

Un interrupt che lascia la macchina in uno stato ben definito è detto **interrupt preciso** e presenta quattro proprietà chiave. In primo luogo, il valore del program counter (PC) è salvato in un luogo noto. In secondo luogo, tutte le istruzioni eseguite prima del PC sono state completate, mentre nessuna istruzione successiva è stata eseguita. In terzo luogo, lo stato di esecuzione dell'istruzione puntata dal PC è noto. Infine, non vi è alcuna restrizione sull'avvio di istruzioni oltre a quella puntata dal PC, ma qualsiasi modifica apportata ai registri o alla memoria deve essere completamente annullata quando si verifica l'interrupt.

Al contrario, un interrupt che non soddisfa questi requisiti è detto **interrupt impreciso**, il che rende la gestione dell'interrupt più complessa. In particolare, le macchine con interrupt imprecisi tendono a salvare molte informazioni sullo stack per consentire al sistema operativo di capire lo stato della macchina al momento dell'interrupt.

Alcune macchine, come la famiglia x86, supportano interrupt precisi per garantire la compatibilità con il software esistente. Tuttavia, questo comporta una maggiore complessità nella logica dell'interrupt all'interno della CPU.

Infine, è importante notare che anche le istruzioni transitorie, annullate a seguito di un'interrupt, possono rappresentare un rischio per la sicurezza, poiché lasciano tracce nella microarchitettura della CPU che potrebbero essere sfruttate da potenziali attaccanti.

(pagine riassunte: 3.5)
## 5.2 - Principi del software di I/O

### 5.2.1 - Obbiettivi del software di I/O

### 5.2.2 - I/O programmato

### 5.2.3 - I/O guidato dagli interrupt

### 5.2.4 - I/O con DMA

## 5.3 - Livelli del software di I/O

### 5.3.1 - Gestori  degli interrupt

### 5.3.2 - Driver di dispositivo

### 5.3.3 - Software per l'I/O indipendente dal dispositivo

### 5.3.4 - Software di I/O nello spazio utente

## 5.4 - Dischi

### 5.4.1 - Hardware dei dischi

### 5.4.2 - Formattazione dei dischi

### 5.4.3 - Algoritmi di scheduling del braccio del disco

### 5.4.4 - Gestione degli errori

### 5.4.5 - Memoria stabile

## 5.5 - Clock

### 5.5.1 - Hardware del clock

### 5.5.2 - Software del clock

### 5.5.3 - Soft timer

## 5.6 - Interfacce utente: tastiera, mouse e monitor

### 5.6.1 - Software di input

### 5.6.2 - Software di output

## 5.7 - Thin client

## 5.8 - Gestione del risparmio energetico

### 5.8.1 - Problemi relativi all'hardware

### 5.8.2 - Problemi relativi al sistema operativo

### 5.8.3 - Questioni relative ai programmi applicativi

## 5.9 - Stato della ricerca sull'input/output


[[|Prossimo Capitolo]]