## Introduzione ai Sistemi Operativi
#### Cos'è un sistema operativo?
Un moderno calcolatore è tipicamente formato da:
	- Uno o più processori
	- Memoria Centrale.
	- Dischi.
	- Stampanti e altre periferiche I/O.

I dettagli di basso livello (livelli inferiori) sono molto complessi. La gestione di tutti i componenti richiede uno strato intermedio software: il **Sistema Operativo**.

Il sistema operativo deve gestire:
- Processori, Memorie e componenti interni.
- Interfacce esterne I/O o moduli esterni.
- Periferiche esterne come mouse, tastiera, monitor e stampanti.
Deve fungere da maschera tra il livello sottostante e il livello superiore (**astrazione**), per gestire al meglio le componenti. Quindi funziona come **gestore delle risorse**, per permettere all'utente di usare al meglio il proprio hardware senza fatiche o problemi.

Ci sono due modalità supportate dall'hardware:
- Modalità kernel (o supervisor).
- Modalità utente.

Il sistema operativo è modalità kernel, mentre i programmi e il software usato dall'utente si trovano appunto in modalità utente. Questa divisione garantisce anche un interfaccia tra software e sistema operativo, permettendo quindi una divisione di aree di scrittura e lettura. 

Vi sono diversi concetti del sistema operativo:
- **Astrazione**: il sistema operativo si pone tra hardware e software utente gestendo autonomamente ogni risorsa.
- Visione **top-down**: il sistema operativo fornisce astrazioni ai programmi applicativi.
- Visione **bottom-up**: il sistema operativo fornisce un’allocazione ordinata e controllata di processori, memorie e unità I/O ai vari programmi che li richiedono.

Il sistema operativo deve fornire:
- Un'organizzazione ordinata e controllata delle risorse.
- Astrazione dei concetti (non più hardware, ma file, database, etc...).
- **Multiplexing** nel tempo e spazio della CPU, che corrisponde alla gestione di molteplici richieste da parte di utenti per diverse operazioni.
#### Breve accenno alla storia dei SO
##### Prima generazione - Vacuum tubes
Sviluppo storico:
- **John Atanasoff & Clifford Berry**: Costruirono il primo computer digitale alla Iowa State University (300 valvole). 
- **Konrad Zuse**: Costruì il Z3 a Berlino con relè elettromeccanici.
- **Colossus**: Progettato a Bletchley Park, Inghilterra.
- **Mark I**: Costruito da Howard Aiken ad Harvard.
- **ENIAC**: Creato da William Mauchley e J. Presper Eckert all'Università della Pennsylvania.

Tecnologie estremamente lente e specifiche, nessun sistema operativo. Nessun linguaggio di programmazione, con alta manutenzione sia hardware che software.

> [!note] Miglioramenti negli anni 50'
> Introduzione delle **schede perforate**, per implementare la programmazione e semplificare l'inserimento dei codici.
##### Seconda Generazione - Transistors and batch systems
Negli anni '50 nacquero nuove invenzioni e concetti:
- Grazie ai **transistor** i computer diventano affidabili per grandi enti.
	- Nasce un'organizzazione interna: progettisti, costruttori, programmatori e operatori.
	- **Mainframe**: grandi macchine, chiuse in sale condizionate e gestite da personale professionale.
- Introduzione del **Sistema Batch**.
	- Step by step
		- Prima bisogna trascrivere i dati su nastro magnetico ed inserirlo nella macchina.
		- Viene calcolato e fornito l'output fisico.
	- Come si programmava:
		- **$JOB**: specifica il numero massimo di esecuzione, numero utente e nome del programmatore.
		- **$FORTRAN**: Carica il compilatore FORTRAN.
		- **Programma**: Codice sorgente da compilare.
		- **$LOAD**: Carica il programma compilato.
		- **$RUN**: Esegue il programma
- Funzionamento:
	- Job raccolti su schede perforate e trasferiti su nastri magnetici con un computer ausiliario.
	- **Macchina principale**, usata per il calcolo mentre l'output era gestito offline.

Quando l'I/O diventa troppo lento, si inizio a cercare di impegnare l'hardware negli intervalli di attesa (Concetto che ritroveremo dopo, pipeline).
##### Terza Generazione - ICs and multiprogramming
- **Innovazioni tecnologiche**:
	- Introduzione ai circuiti integrati (**IC**), miglior rapporto prezzo/prestazioni.
	- Introduzione alla **multiprogrammazione**, per sfruttare al meglio la CPU.
- **IBM System/360**:
	- Serie di computer **compatibili** con lo stesso set di istruzioni.
	- Gestione sia di calcoli scientifici che commerciali
	- Successo enorme seguito dai modelli successivi.
- **OS/360**:
	- Sistema operativo complesso e universale, ma difficile da mantenere.
	- Problemi di gestione e aggiornamento continui.
	- Diffusione di tecniche chiave per la multiprogrammazione.
- **Impatto**:
	- Modello di **famiglia di computer**.
	- Discendenti di **OS/360** vengono ancora usati da grandi basi di dati e server.

Problema delle architetture batch: CPU inattiva per calcoli scientifici o per dati commerciali:
- Memoria partizionata per job multipli
	- **Spooling** (Simultaneous peripheral operation on line) per caricare nuovi job senza interruzioni.
- Problema di inserimento job, tempi troppo lunghi per inserimento job e output
	- **Time Sharing**, per risposta rapida. La CPU veniva assegnata a job utenti attivi. (Multics, troppo complesso ma con fondamenta ben solide nel futuro).
	- Protezione hardware necessaria per time sharing.
- Sistema operativo per multiplexing e servizi informatici (non molto successo)

###### UNIX
- Sistema operativo multiutente e con multiprogrammazione.
- Storia
	- MULTICS
	- Ken Thompson
		- PDP-7 scritto in assembler.
		- UNICS (Uniplexed Information and Computing Service)
		- Unix, PDP-11
		- Partendo dal linguaggio B poi viene sviluppato in C riducendo notevolmente le righe di codice usate.
		- Si evolve nel sistema operativo UNIX e diventa popolare per ambiti accademici e aziendali.
		- Troppe versioni di UNIX danno luogo ad un CAOS, fino a che la IEEE viene sviluppato POSIX, per garantire stabilità. 
- Diversi sistemi di standardizzazione, che miravano a consolidare i vari aspetti di UNIX e ottenere un'interfaccia standard per programmare in UNIX.
	- POSIX
	- OSF
	- X/OPEN
- Varianti del sistema UNIX
	- Solaris 2.x, variazione di UNIX diffusa con grande successo commerciale.
	- MINIX, piccolo sistema UNIX compatibile con standard POSIX e fatto in C e Assembler.
		- Basato sul micro-kernel a scopo didattico
		- Ancora usato nei processori moderni.
		- Basato su modello micro-kernel.
- Da MINIX a Linux.
- Microsoft acquisisce DOS e nasce MS-DOS
	- Successo con Windows 10
- Apple introduce Apple Macinthosh con GUI
##### Quarta Generazione - Personal Computers
Diverse aziende si mettono in gioco:
- Sviluppo dei circuiti LSI e nascita dei PC.
- Intel introduce l'8080, necessità di un sistema operativo
- Microsoft compra DOS da Seattle Computer Products.
	- Nasce MS-DOS e domina il mercato dei PC IBM.

Inizia ad arrivare la necessità di portare i computer alle persone:
- Nasce l'idea della GUI da Steve Jobs con Apple.
- Microsoft crea Windows come ambiente grafico su MS-DOS.
##### Quinta Generazione - Mobile Computers
Evoluzioni:
- Apple consolida il suo OS basato su UNIX ma con architettura specifica.
- Vari aggiornamenti Windows.

Prosperazione di Linux (e Android):
- Nuovi ambienti server e mobile.
- Minix non muore e viene usato ancora da Intel per desktop, server e laptop.

#### Architettura Hardware dei Sistemi di Calcolo
Un moderno calcolatore è tipicamente formato da:
- Uno o più processori
- Memoria principale
- Dischi o unità flash (SSD)
- Stampanti
- Tastiera
- Mouse
- Display
- Interfacce di rete
- Dispositivi di I/O

Tutti questi componenti sono collegati attraverso un sistema di **bus** che permette la comunicazione tra le varie parti del sistema.

##### Il Processore (CPU)
La CPU è il cervello del computer ed esegue istruzioni dalla memoria. Il **ciclo base della CPU** (fetch-decode-execute) consiste in:

1. **Fetch**: Preleva l'istruzione dalla memoria
2. **Decode**: Decodifica l'istruzione per determinarne il tipo e gli operandi
3. **Execute**: Esegue l'istruzione
4. Ripete il ciclo con l'istruzione successiva

I programmi vengono eseguiti ripetendo questo ciclo fino al termine dell'esecuzione.

**Instruction Set Architecture (ISA)**

Ogni CPU esegue un set specifico di istruzioni (instruction set):
- Un processore **x86** non può eseguire programmi scritti per **ARM**
- Un processore **ARM** non può eseguire programmi per **x86**
- L'ISA definisce anche le istruzioni per caricare/salvare dati dalla memoria

**Registri della CPU**

Tutte le CPU contengono **registri** interni per memorizzare variabili importanti e risultati temporanei. I registri principali includono:

- **Program Counter (PC)**: contiene l'indirizzo della prossima istruzione da eseguire
- **Stack Pointer (SP)**: punta alla cima dello stack corrente in memoria
  - Lo stack contiene frame di procedure con parametri e variabili locali
- **Program Status Word (PSW)**: registro fondamentale contenente:
  - Bit di condizione (zero, carry, overflow, ecc.)
  - Informazioni sullo stato del programma
  - Bit di modalità (kernel/user)
  - Priorità di esecuzione
  - Il PSW è essenziale per le chiamate di sistema e la gestione dell'I/O

**Modalità Operative**

Le CPU moderne supportano due modalità operative (supportate dall'hardware):

- **Modalità kernel (supervisor mode)**:
  - Il sistema operativo può eseguire qualsiasi istruzione
  - Accesso completo a tutto l'hardware
  - Può modificare registri protetti e PSW
  - Può eseguire istruzioni privilegiate

- **Modalità utente (user mode)**:
  - Solo un sottoinsieme limitato di istruzioni disponibile
  - Accesso controllato all'hardware
  - Protezione del sistema da modifiche non autorizzate
  - I programmi applicativi girano in questa modalità

Il passaggio tra le modalità avviene tramite le **system call** (chiamate di sistema), usando istruzioni speciali come `TRAP`, `INT`, o `SYSCALL` che causano un cambio di contesto controllato.

**Gestione del Multiplexing Temporale**

Il sistema operativo gestisce il **multiplexing temporale della CPU**:
- Durante il cambio di contesto, il SO salva tutti i registri del processo corrente
- Carica i registri del prossimo processo da eseguire
- Questo permette l'esecuzione alternata di più programmi (multitasking)

**Pipeline**

Le progettazioni avanzate delle CPU utilizzano la **pipeline** per migliorare le prestazioni. Invece di eseguire un'istruzione alla volta attraverso tutti gli stadi, la pipeline permette di sovrapporre l'esecuzione:

```
Senza Pipeline (sequenziale):
Istruzione 1: [Fetch] → [Decode] → [Execute]
Istruzione 2:                        [Fetch] → [Decode] → [Execute]

Con Pipeline (sovrapposta):
Tempo 1: [Fetch 1]
Tempo 2: [Decode 1] [Fetch 2]
Tempo 3: [Execute 1] [Decode 2] [Fetch 3]
Tempo 4:            [Execute 2] [Decode 3] [Fetch 4]
```

Caratteristiche della pipeline:
- Permette di eseguire più istruzioni contemporaneamente in stadi diversi
- Migliora il throughput (numero di istruzioni completate per unità di tempo)
- **Non è completamente trasparente al sistema operativo** - il SO deve considerare gli effetti della pipeline durante il context switching

Le pipeline moderne possono includere:
- **Holding buffer**: buffer intermedio per gestire istruzioni in attesa
- **Multiple execution units**: più unità di esecuzione in parallelo per eseguire istruzioni indipendenti simultaneamente

Problemi della pipeline:
- **Hazard**: conflitti per risorse condivise
- **Branch misprediction**: previsione errata delle diramazioni condizionali

**Multithreading e Hyperthreading**

Il **multithreading** (o **hyperthreading** in Intel) è una tecnica hardware che:
- Mantiene lo stato di **due o più thread** all'interno della CPU
- **Non è vera esecuzione parallela** - solo un thread alla volta usa le unità di esecuzione funzionali
- Permette alla CPU di passare rapidamente da un thread all'altro quando uno è bloccato (es. cache miss)
- Maschera le latenze di memoria
- **Il sistema operativo deve tenerne conto** - vede thread hardware come CPU separate ma deve capire che condividono risorse

**Architetture Multiprocessore e Multicore**

I sistemi moderni utilizzano multiple CPU o core per aumentare le prestazioni:

**Vantaggi dei multiprocessori**:
- **Throughput**: maggiore capacità di calcolo totale
- **Economia di scala**: condivisione di risorse (memoria, periferiche)
- **Affidabilità**: il sistema continua a funzionare anche se un processore fallisce

**Architetture multicore moderne**:

Esempio 1 - Multicore con cache L2 condivisa:
```
+-------------------+
| Core1 | Core2     |
|  L1   |  L1       |
+-------------------+
|   L2 cache (condivisa)
+-------------------+
| Core3 | Core4     |
|  L1   |  L1       |
+-------------------+
```

Esempio 2 - Multicore con cache L1 private e L2 private:
```
+-------+  +-------+
| Core1 |  | Core2 |
|  L1   |  |  L1   |
|  L2   |  |  L2   | ← Cache private per ogni core
+-------+  +-------+
+-------+  +-------+
| Core3 |  | Core4 |
|  L1   |  |  L1   |
|  L2   |  |  L2   |
+-------+  +-------+
```

**GPU (Graphics Processing Unit)**

Le GPU moderne sono processori altamente paralleli:
- Migliaia di core semplici ottimizzati per operazioni parallele massicce
- Utilizzate non solo per grafica ma anche per calcolo scientifico (GPGPU - General Purpose GPU)
- Architettura SIMD (Single Instruction Multiple Data)
- Il sistema operativo deve gestire la comunicazione CPU-GPU e l'allocazione della memoria video

**Cache e il loro Impatto Fondamentale**

Le cache sono **fondamentali** per le prestazioni moderne perché:
- Nascondono la latenza della memoria principale (che è 50-100x più lenta)
- Sfruttano la **località spaziale** (dati vicini) e **temporale** (dati usati recentemente) dei programmi
- Possono fornire speedup di 10-100x rispetto all'accesso diretto alla RAM
- Senza cache, le CPU moderne sarebbero inutilizzabili

##### Gerarchia della Memoria

I computer moderni dispongono di una **gerarchia di memorie** con trade-off tra velocità, capacità e costo:

```
Typical access time                           Typical capacity
<1 nsec              [Registri]               <1 KB
1-8 nsec             [Cache]                  4-8 MB
10-50 nsec           [Main memory]            16-64 GB
10 msec /            [Magnetic disk / SSD]    2-16+ TB { optional
10s-100s usec                                           persistent
                                                        memory
```

**Dettaglio dei livelli**:

1. **Registri** (< 1 nsec):
   - Integrati direttamente nella CPU
   - Accesso praticamente istantaneo
   - Capacità minima (< 1 KB, tipicamente 16-32 registri da 32-64 bit)
   - Gestiti esplicitamente dal compilatore e dall'instruction set

2. **Cache** (1-8 nsec):
   - Memoria SRAM (Static RAM) molto veloce ma costosa
   - Organizzata in livelli gerarchici: L1, L2, L3
   - **L1 cache**: la più veloce, più piccola, dedicata per core
     - Tipicamente divisa in L1i (instruction) e L1d (data)
     - Dimensione: 32-64 KB per core
     - Latenza: 1-2 nsec (4-5 cicli di clock)
   - **L2 cache**: intermedia, spesso privata per core
     - Dimensione: 256-512 KB per core
     - Latenza: 3-4 nsec (10-20 cicli)
   - **L3 cache**: più grande, condivisa tra tutti i core
     - Dimensione: 4-32 MB totali
     - Latenza: 8-12 nsec (40-75 cicli)
   - Gestita automaticamente dall'hardware (trasparente al programmatore)

3. **Memoria principale - RAM** (10-50 nsec):
   - Memoria DRAM (Dynamic RAM)
   - **Volatile** (perde tutti i dati quando viene tolta l'alimentazione)
   - Accesso relativamente veloce ma molto più lenta della cache
   - Latenza tipica: 50-100 nsec (150-300 cicli di clock)
   - Capacità tipica nei sistemi moderni: 16-64 GB (fino a 512 GB-2 TB nei server)
   - Tecnologia attuale: DDR4, DDR5

4. **Memoria secondaria** (10 msec per HDD, 10s-100s µsec per SSD):
   - **Persistente** (mantiene i dati anche senza alimentazione)
   - Due tipi principali con caratteristiche molto diverse:

   **HDD (Hard Disk Drive)**:
   - Basato su dischi magnetici rotanti con testine meccaniche
   - Latenza media: 5-10 millisecondi
   - Throughput sequenziale: 100-200 MB/s
   - Molto più lento per accesso casuale
   - Capacità: 1-20 TB
   - Costo per GB: molto basso

   **SSD (Solid State Drive)**:
   - Basato su memoria flash (NAND)
   - Nessuna parte meccanica in movimento
   - Latenza: 10s-100s microsecondi (100-1000x più veloce di HDD)
   - Throughput sequenziale: 500 MB/s (SATA) fino a 7000 MB/s (NVMe PCIe 4.0)
   - Accesso casuale molto veloce
   - Capacità: 256 GB - 8 TB
   - Costo per GB: più alto di HDD ma in diminuzione

**Problemi della Gestione della Cache**

Il sistema di cache deve risolvere diverse questioni critiche (il sistema operativo deve essere consapevole di questi aspetti anche se la gestione è principalmente hardware):

1. **Quando inserire un nuovo elemento nella cache?**
   - **On demand**: quando viene richiesto e non è presente (cache miss)
   - **Prefetching**: anticipando le richieste future basandosi su pattern di accesso

2. **In quale riga della cache inserire il nuovo elemento?**
   - **Direct mapped**: posizione fissa determinata dall'indirizzo (veloce ma può causare conflitti)
   - **Fully associative**: può andare in qualsiasi posizione (flessibile ma costoso)
   - **Set associative** (più comune): compromesso - l'indirizzo determina un set, dentro il set è fully associative (es. 4-way, 8-way, 16-way)

3. **Quale elemento rimuovere dalla cache quando è necessario spazio?**
   - **LRU (Least Recently Used)**: rimuove l'elemento usato meno recentemente (più comune)
   - **LFU (Least Frequently Used)**: rimuove l'elemento usato meno frequentemente
   - **Random**: scelta casuale (semplice ma meno efficiente)
   - **FIFO (First In First Out)**: rimuove il più vecchio
   - **Pseudo-LRU**: approssimazione di LRU più semplice da implementare

4. **Dove mettere un elemento appena eliminato nella memoria più grande?**
   - **Write-through**: ogni scrittura nella cache viene immediatamente propagata alla memoria principale (sicuro ma lento)
   - **Write-back** (più comune): le modifiche rimangono solo in cache fino all'eviction (veloce ma richiede bit "dirty")

**Coerenza della Cache nei Sistemi Multicore**

Nei sistemi con più core e cache private sorge il problema della coerenza:
- **Problema**: lo stesso dato può esistere in cache diverse, e se un core lo modifica, le altre cache hanno una copia obsoleta
- **Soluzione**: protocolli di coerenza cache hardware
  - **MESI protocol** (Modified, Exclusive, Shared, Invalid)
  - **MOESI protocol** (aggiunge stato Owned)
- Il sistema operativo deve essere consapevole di questi aspetti per:
  - Allocazione corretta dei thread ai core
  - Gestione della memoria condivisa tra processi
  - Ottimizzazione della località dei dati

**MMU (Memory Management Unit)**

La **MMU** è un componente hardware fondamentale, tipicamente integrato nella CPU, che:
- Gestisce la traduzione degli indirizzi **virtuali** (usati dai programmi) in indirizzi **fisici** (della RAM)
- Permette l'implementazione della **memoria virtuale**
- Fornisce **protezione della memoria** tra processi (ogni processo ha il suo spazio di indirizzi isolato)
- Supporta la **paginazione** (divide la memoria in pagine) e la **segmentazione**
- Contiene il **TLB** (Translation Lookaside Buffer): cache specializzata per le traduzioni di indirizzo più veloce

##### Storage Non Volatile: Dischi e SSD

**Dischi Magnetici (HDD - Hard Disk Drive)**

Struttura fisica di un disco magnetico:
- **Piatti (platters)**: dischi rotanti rivestiti di materiale magnetico - ogni disco ha due superfici utilizzabili
- **Testine di lettura/scrittura (read/write heads)**: una per superficie, montate su braccio mobile
- **Motore**: rotazione costante (5400-15000 RPM)

Organizzazione logica: **tracce**, **settori** (512 byte o 4 KB), **cilindri**. Tempo di accesso = Seek time + Rotational delay + Transfer time

**SSD (Solid State Drive)**: Nessuna parte mobile, memoria flash NAND, 100-1000x più veloce per accessi casuali, wear leveling necessario.

##### Dispositivi di I/O

Ogni dispositivo ha due componenti:
1. **Controller**: interfaccia semplice per il SO con registri di controllo/stato
2. **Dispositivo fisico**: interfaccia complessa da pilotare

**Driver**: software in kernel mode che traduce richieste SO in comandi specifici per il controller.

**Comunicazione con I/O**: Istruzioni IN/OUT o Memory-mapped I/O.

**Metodi di Esecuzione**:
1. **Polling**: CPU interroga continuamente - spreco di cicli
2. **Interrupt-Driven**: dispositivo genera interrupt quando pronto - efficiente
3. **DMA**: trasferimento diretto memoria-dispositivo senza CPU - ottimale per grandi quantità

##### Bus di Sistema

Architettura moderna multilivello:
- **DDR4/DDR5** (CPU-RAM): 25-80 GB/s
- **PCIe**: point-to-point, ×1/×4/×8/×16 lanes, PCIe 4.0 = 2 GB/s per lane
- **DMI**: CPU al chipset
- **SATA**: 6 Gb/s per dischi
- **USB**: da 1.5 Mb/s (USB 1.0) a 40 Gb/s (USB 4), hot-pluggable

#### Lo zoo dei Sistemi Operativi
Quanti sistemi operativi esistono?
##### Sistemi Operativi per Mainframe
- Funzioni principali:
	- **Batch processing**: esegue lavori senza interazione dell'utente
	- **Elaborazione di transizioni**: gestisce numerose richieste simultanee
	- **Timesharing**: molti utenti eseguono lavori simultaneamente
	  
- Esempi: Z/OS usato per applicazioni mission-critical (banche, e-commerce)
##### Sistemi Operativi per Server
Utilizzato su server che servono più utenti attraverso la rete
- Funzioni principali:
	- **File sharing**
	- **Database**
	- **Stampa**
	- **Hosting Web**
- Esempi: Linux, FreeBSD, Windows Server, Solaris
##### Sistemi Operativi per Personal Computer
Supportano un singolo utente con multiprogrammazione e architetture multiprocessore
- Utilizzati per compiti quotidiani: Videoscrittura, navigazione web, fogli di calcolo
- Esempi: Windows, MacOS, Linux, FreeBSD
- Caratterizzato da facilità d'uso, interfaccia grafica, supporto per applicazioni di produttività
##### Sistemi Operativi per Smartphone
- Mercato dominato da **Android** (google) e **iOS** (apple)
- Supportano CPU multicore, GPS, fotocamere e numerose app di terze parti
##### Sistemi Operativi per IoT e Embedded
Usati in dispositivi connessi (frigoriferi, lavatrici, telecamere di sicurezza). Sono tipicamente leggeri con funzioni specifiche e limitate
- Caratteristiche: footprint ridotto (RIOT può girare su meno di 10 KB)
- Esempi: Embedded Linux, QNX, TinyOS
##### Sistemi Operativi Real-Time
Progettati per rispettare scadenze rigide nei processi industriali e militari
- Funzioni principali:
	- **Hard real-time**: risposte immediate e precise
	- **Soft real-time**: occasionali ritardi tollerabili
- Esempi: eCos, VxWorks
##### Sistemi Operativi per Smart Card
Usati in smart card per pagamenti, autenticazioni e altro. Alimentate con contatti o induzione, con capacità limitate
- Java-oriented: alcune eseguono applet java per multiprogrammazione
- Esempi: Sistemi proprietari, JavaCard per applet multiprogrammate

##### Cosa hanno in comune?
Tutti i sistemi operativi, indipendentemente dalla loro categoria, condividono due funzioni fondamentali:

**Extended Machine (Macchina Estesa)**
- Estensione delle funzionalità hardware attraverso l'astrazione
- Nasconde i dettagli di basso livello al programmatore
- Fornisce interfacce semplici e intuitive per l'accesso alle risorse
- Esempio: invece di gestire direttamente i settori del disco, il programmatore lavora con file e directory

**Resource Manager (Gestore delle Risorse)**
- Proteggere l'uso simultaneo delle risorse tra processi multipli
- Garantire una condivisione equa delle risorse (CPU, memoria, I/O)
- Resource accounting e limiting per tracciare e limitare l'uso delle risorse
- Prevenire interferenze tra processi (isolamento)
- Multiplexing nel tempo (CPU, stampanti) e nello spazio (memoria, disco)

#### Concetti base di un sistema operativo
Il sistema operativo offre funzionalità, chiamate **servizi**, attraverso chiamate di sistema. Esempi di servizi sono il **File System Service** e **Process Management Service**.

##### System Call (Chiamate di Sistema)

Le **system call** (o **chiamate di sistema**) sono l'interfaccia che il sistema operativo offre alle applicazioni per richiedere servizi. Rappresentano il meccanismo attraverso cui un processo in modalità utente può richiedere servizi al kernel.

**Problema principale:**
- Il meccanismo delle chiamate di sistema è **altamente specifico** del sistema operativo e dell'hardware
- La necessità di efficienza esaspera questo problema

**Soluzione:**
- **Incapsulare** le chiamate di sistema nella **libreria C** (libc)
- Tipicamente esporta una chiamata di libreria per ogni chiamata di sistema
- UNIX libc si basa sulla libreria C **POSIX**
- Esistono molte librerie C UNIX diverse

**Meccanismo dettagliato: I 10 passi per effettuare una chiamata di sistema**

Consideriamo l'esempio della system call `read(fd, buffer, nbytes)`:

**Passi 1-3: Preparazione (User Space)**
1. **Preparazione dei parametri**: il programma chiamante prepara i parametri (i.e., `fd`, `buffer`, `nbytes`)
   - Solitamente memorizzandoli nei **registri** (es. RDI, RSI, RDX) o nello **stack** (se sono di più)

2. **Chiamata alla procedura di libreria**: Il programma effettua la chiamata alla procedura di libreria (es. `read()`)

3. **Pone nbytes nel registro RDX**, buffer nel registro RSI, e fd nel registro RDI

**Passi 4-6: Transizione a Kernel Mode**
4. **Chiamata read dalla libreria C**

5. **Collocazione del numero di chiamata di sistema**: colloca il numero della chiamata di sistema in un registro, come **RAX**
   - Questo numero identifica quale funzione del kernel deve essere eseguita (es. read, write, open, ecc.)
   - Il kernel può consultare una **tabella di chiamate di sistema**, dove ogni numero è associato a un gestore specifico

6. **Passaggio a modalità kernel**: si esegue un'istruzione **"trap"** (ad esempio, `SYSCALL` in x86-64)
   - Passare dalla modalità utente a quella kernel
   - L'istruzione "trap" è simile a una chiamata di procedura ma **cambia la modalità** in modalità kernel
   - Può saltare solo a indirizzi specifici o indici di una tabella di memoria, a differenza della chiamata di procedura normale

**Passi 7-8: Esecuzione (Kernel Space)**
7. **Invio**: Il kernel riceve la trap e identifica la system call dal registro RAX

8. **Esecuzione del gestore di chiamate di sistema**: Il gestore di chiamate di sistema specifico viene eseguito
   - Il kernel valida i parametri
   - Esegue l'operazione richiesta (es. lettura dal file descriptor)

**Passi 9-10: Ritorno a User Mode**
9. **Ritorno alla procedura di libreria utente**: dopo l'esecuzione, il controllo può essere restituito alla procedura di libreria utente, all'istruzione successiva all'istruzione "trap"

10. **Istruzione successiva**: La procedura di libreria ritorna al programma chiamante con il risultato

**Nota importante: Possibilità di blocco**
- La chiamata di sistema può **bloccare il chiamante**, ad esempio, se l'input desiderato non è disponibile
- Il sistema operativo può quindi eseguire altri processi
- Quando l'input o le condizioni desiderate sono disponibili, il processo bloccato viene **ripreso**
- Tornando alla procedura di libreria utente e procedendo all'istruzione successiva

**Categorie principali di system call POSIX:**

**1. Gestione dei Processi**

| Call | Description |
|------|-------------|
| `pid = fork()` | Crea un processo figlio identico al genitore |
| `pid = waitpid(pid, &statloc, options)` | Attende che un processo figlio termini |
| `s = execve(name, argv, environp)` | Sostituisce l'immagine centrale di un processo |
| `exit(status)` | Termina l'esecuzione del processo e restituisce lo stato |

**2. Gestione dei File**

| Call | Description |
|------|-------------|
| `fd = open(file, how, ...)` | Apre un file per la lettura, la scrittura o entrambe le operazioni |
| `s = close(fd)` | Chiude un file aperto |
| `n = read(fd, buffer, nbytes)` | Legge dati da un file in un buffer |
| `n = write(fd, buffer, nbytes)` | Scrive dati da un buffer in un file |
| `position = lseek(fd, offset, whence)` | Sposta il puntatore del file |
| `s = stat(name, &buf)` | Ottiene informazioni sullo stato di un file |

**3. Gestione delle Directory e File System**

| Call | Description |
|------|-------------|
| `s = mkdir(name, mode)` | Crea una nuova directory |
| `s = rmdir(name)` | Rimuove una directory vuota |
| `s = link(name1, name2)` | Crea una nuova voce, nome2, che punta a nome1 |
| `s = unlink(name)` | Rimuove una voce della directory |
| `s = mount(special, name, flag)` | Monta un file system |
| `s = umount(special)` | Smonta un file system |

**4. Altre System Call**

| Call | Description |
|------|-------------|
| `s = chdir(dirname)` | Cambia la directory di lavoro |
| `s = chmod(name, mode)` | Modifica i bit di protezione di un file |
| `s = kill(pid, signal)` | Invia un segnale a un processo (NON uccide direttamente!) |
| `s = time(&seconds)` | Ottiene il tempo trascorso dal 1° gennaio 1970 |

**Note:**
- Il codice di ritorno `s` è `-1` se si è verificato un errore
- `pid` è l'ID di un processo
- `fd` è un descrittore di file
- `n` è un conteggio di byte
- `position` è un offset all'interno del file

**API Windows Win32**

Windows fornisce API equivalenti (anche se non identiche) alle system call UNIX:

| UNIX | Win32 | Descrizione |
|------|-------|-------------|
| `fork` | `CreateProcess` | Crea un nuovo processo |
| `waitpid` | `WaitForSingleObject` | Può attendere l'uscita di un processo |
| `execve` | (none) | CreateProcess = fork + execve |
| `exit` | `ExitProcess` | Termina l'esecuzione |
| `open` | `CreateFile` | Crea un file o apre un file esistente |
| `close` | `CloseHandle` | Chiude un file |
| `read` | `ReadFile` | Legge dati da un file |
| `write` | `WriteFile` | Scrive dati in un file |
| `lseek` | `SetFilePointer` | Sposta il puntatore del file |
| `stat` | `GetFileAttributesEx` | Ottiene vari attributi del file |
| `mkdir` | `CreateDirectory` | Crea una nuova directory |
| `rmdir` | `RemoveDirectory` | Rimuove una directory vuota |
| `link` | (none) | Win32 non supporta i link |
| `unlink` | `DeleteFile` | Distrugge un file esistente |
| `mount` | (none) | Win32 non supporta mount |
| `umount` | (none) | Win32 non supporta mount, quindi no umount |
| `chdir` | `SetCurrentDirectory` | Cambia la directory di lavoro corrente |
| `chmod` | (none) | Win32 non supporta security (anche se NT lo fa) |
| `kill` | (none) | Win32 non supporta i segnali |
| `time` | `GetLocalTime` | Ottiene l'ora corrente |

**Esempio di utilizzo delle system call:**

```c
#define TRUE 1

while (TRUE) {
    type_prompt();                        /* visualizza prompt sullo schermo */
    read_command(command, parameters);     /* legge input dal terminale */

    if (fork() != 0) {                    /* fork off child process */
        /* Parent code. */
        waitpid(-1, &status, 0);          /* attende che il figlio termini */
    } else {
        /* Child code. */
        execve(command, parameters, 0);    /* esegue il comando */
    }
}
```

Questo esempio mostra il funzionamento di una semplice shell che:
1. Visualizza un prompt
2. Legge un comando dall'utente
3. Crea un processo figlio con `fork()`
4. Il processo padre attende con `waitpid()`
5. Il processo figlio esegue il comando con `execve()`

**Performance delle System Call:**

Le system call sono **costose** in termini di performance perché richiedono:
- Un **cambio di contesto** (context switch) tra modalità utente e kernel
- Salvataggio e ripristino dei registri
- Validazione dei parametri
- Possibile blocco del processo chiamante

##### L'astrazione del Processo
I **processi** sono astrazioni a livello utente per poter eseguire un programma per conto di un utente. Ogni processo ha il proprio spazio di indirizzamento e i dati usati nell'elaborazione vengono recuperati e salvati in file.

I file persistono rispetto ai processi.

##### Il programma in esecuzione è un processo a cui è associato:
- Uno spazio di indirizzi
- Un insieme di risorse
	- Registri
	- File Aperti
	- Allarmi
	- ...
Il processo può essere visto come un container, che contiene tutte le informazioni necessarie all'esecuzione del programma.

Un processo può essere descritto tramite un **layout**:
- Stack
- Data
- Text

Ogni layout dipende dal **sistema operativo**, **l'architettura della macchina** e **il programma**.
##### Ciclo di vita dei processi
I processi vengono salvati in una **tabella dei processi** del sistema operativo, un processo sospeso consiste in una voce di questa tabella e del suo spazio degli indirizzi.

Ogni processo può essere **creato**, **terminato**, **messo in pausa** e **rieseguito**. Ogni processo può creare un altro **processo figlio** (crea una gerarchia di processi).

Ogni processo è di proprietà di un **utente** identificato da un UID (condiviso generalmente anche dal processo). Su UNIX un processo figlio ha lo stesso UID del processo padre ad esempio. Gli utenti possono essere membri di un gruppo identificato da un GUID.

Un processo **root/superuser/administrator** è speciale ed ha più permessi.
##### File
Il file è un'**astrazione di un dispositivo di memorizzazione** (eventualmente) reale (ad esempio un disco). Possiamo leggere e scrivere dati da/su un file fornendo una posizione e la quantità di dati da trasferire.

**Caratteristiche dei file:**
- È possibile leggere e scrivere dati da/su file fornendo una posizione e una quantità di dati da trasferire
- I file vengono collezionati in **directory** (o cartelle)
- Una directory conserva un identificatore per ogni file che contiene
- Una directory è un file a sé stante
- Filosofia UNIX: **"Everything is a file"**

**Gerarchia dei File System:**

Le directory e i file formano una **gerarchia**:
- La gerarchia inizia dalla **"directory principale"** o **"directory radice" (root)**: `/`
- È possibile accedere ai file tramite **percorsi assoluti (absolute path)**: `/home/ast/todo-list`
- ... o **percorsi relativi** a partire dalla directory di lavoro corrente: `../courses/slides1.pdf`
- Altri filesystem possono essere **montati** (da `mount`) nella root: `/mnt/windows`

**Mount Operation:**

Prima del mount, i file dell'unità esterna (es. USB) non sono accessibili. Dopo aver eseguito l'operazione di mount, fanno parte della gerarchia dei file e possono essere acceduti normalmente attraverso il path specificato.

##### Diritti di accesso

I file sono "protetti" da **tuple a tre bit** per il **proprietario** (owner), il **gruppo** (group) e gli **altri utenti** (other users).

Le tuple contengono un bit:
- **(r)ead**: permesso di lettura
- **(w)rite**: permesso di scrittura
- **e(x)ecute**: permesso di esecuzione

Sono disponibili anche altri bit per funzionalità avanzate.

**Esempio di permessi:**
```
-rwxr-x--x myuser mygroup 14492 Dec 4 18:04 myfile
```
- **Owner** è autorizzato a eseguire, modificare e leggere il file (rwx)
- **Group** è autorizzato a leggere ed eseguire il file (r-x)
- **Other users** sono autorizzati solo ad eseguire il file (--x)

##### File Speciali

I dispositivi hardware sono astratti come file in UNIX:

**Block special files** (dispositivi a blocchi, esempio i dischi):
```
brw-rw---- 1 root root 8, 2 Dec 4 18:04 /dev/sda2
```

**Character special files** (dispositivi a caratteri, ad esempio le porte seriali):
```
crw-rw---- 1 root root 4,64 Dec 4 18:04 /dev/ttyS0
```

**Altri file speciali:**
- **Symbolic links** (collegamenti simbolici)
- **Named/anonymous FIFOs** (pipes/sockets)

**"Everything is a file descriptor"** - In UNIX, quasi tutto può essere trattato come un file e acceduto tramite file descriptor.

##### Pipe

Le **pipe** sono pseudo-file che consentono ai processi di comunicare su un canale **FIFO** (First In First Out):

**Caratteristiche:**
- Devono essere impostate in anticipo
- Sembrano file "normali" per i processi che leggono e scrivono da/su di esse
- Permettono comunicazione unidirezionale tra processi

**Esempio:** Due processi collegati da una pipe possono scambiarsi dati, dove il processo A scrive nella pipe e il processo B legge dalla pipe.

##### Esempio pratico di accesso ai file

```bash
herbertb@sleet:~/tmp$ pwd
/home/herbertb/tmp

herbertb@sleet:~/tmp$ mkdir os
herbertb@sleet:~/tmp$ cat > os/hello.sh
#!/bin/sh
echo "hello world!"

herbertb@sleet:~/tmp$ chmod 744 os/hello.sh
herbertb@sleet:~/tmp$ os/hello.sh
hello world!

herbertb@sleet:~/tmp$ chmod 644 os         # Cosa succede?
herbertb@sleet:~/tmp$ cat > os/qq.txt      # Funziona?
herbertb@sleet:~/tmp$ ls os/               # Funziona?
herbertb@sleet:~/tmp$ os/hello.sh          # Funziona?
herbertb@sleet:~/tmp$ rm os/hello.sh       # Funziona?
```

**Termini importanti da ricordare:**
- **Path** (percorso)
- **Folder / map / directory** (cartella / directory)
- **Root directory** (directory radice)
- **Working directory** (directory di lavoro corrente)
- **File descriptor** (descrittore di file)
- **Mounting** (montaggio)
- **Block/character special files** (file speciali a blocchi/caratteri)
- **Pipe** (tubo di comunicazione)

#### Strutture dei Sistemi Operativi
I sistemi operativi possono essere organizzati secondo diverse architetture, ciascuna con vantaggi e svantaggi specifici.

##### Sistemi Monolitici

La struttura più comune e tradizionale. L'intero sistema operativo gira come un singolo programma in modalità kernel.

**Organizzazione del sistema monolitico:**

Il sistema è organizzato come:
- **Programma principale** che invoca le chiamate di sistema richieste
- Il kernel è un **blocco monolitico** con:
  - **Procedure di servizio** che eseguono le chiamate di Sistema
  - **Procedure di utilità** che aiutano a implementare le procedure di servizio

**Caratteristiche dei Sistemi Operativi Monolitici:**

1. **Approccio "tutto in uno"**:
   - Il kernel è un'**unica unità grande e interconnessa**
   - Tutte le funzioni del sistema operativo (gestione processi, gestione memoria, gestione I/O) sono **strettamente integrate** in un unico spazio di indirizzamento

2. **Flessibilità vs Complessità**:
   - Offre una certa flessibilità in termini di prestazioni e design
   - Tuttavia, dato che tutto è strettamente interconnesso, un **bug o errore** in una parte del sistema può causare problemi in altre parti
   - Potenzialmente porta a **crash sistemici**

3. **Compilazione e Collegamento**:
   - Tutte le funzioni e procedure del sistema operativo devono essere **compilate e collegate** in un unico eseguibile del kernel

4. **Mancanza di occultamento**:
   - Tutte le procedure possono, in teoria, accedere a qualsiasi altra procedura o variabile all'interno del kernel
   - Non c'è un vero e proprio "occultamento" o isolamento tra le diverse parti del sistema

5. **Utilizzo di "trap"**:
   - Meccanismo attraverso il quale un programma può richiedere i servizi del sistema operativo
   - Avviene attraverso **interruzioni software** che trasferiscono il controllo al sistema operativo

6. **Struttura a tre strati**:
   - Una suddivisione del sistema in livelli: **user mode**, **kernel mode** e **hardware**
   - Il "trap" agisce come meccanismo di comunicazione tra questi livelli

**Caratteristiche moderne:**

1. **Estensioni caricabili**:
   - Molti sistemi operativi permettono di **caricare dinamicamente** componenti aggiuntivi
   - Esempi: driver di dispositivi, file system
   - Possono essere caricati e scaricati a seconda delle necessità
   - Offre una certa **modularità** anche in un sistema monolitico

2. **Librerie Condivise e DLL**:
   - Sia UNIX che Windows supportano librerie di codice condivise tra più programmi
   - In UNIX: **"librerie condivise"** (shared libraries)
   - In Windows: **"Dynamic Link Libraries" (DLL)**
   - Contengono codice che può essere eseguito da più programmi contemporaneamente
   - Riducono la necessità di avere copie multiple del medesimo codice in memoria

**Architettura completa:**

```
User Applications
────────────────────────────────────
System Call Interface
────────────────────────────────────
│                                 IPC
│  File System     │  Process      Scheduler
│   Character      │  Control      Memory
│   Block          │               Management
│  Device Drivers  │
────────────────────────────────────
Hardware Control
────────────────────────────────────
Hardware
```

**Kernel Unificato con interconnessione completa:**
- Tutte le funzionalità centralizzate in un unico kernel
- Ogni componente ha la capacità di richiamare qualsiasi altro componente
- Questa struttura può diventare complessa e meno gestibile con l'evoluzione del sistema

**Vantaggi:**
- Molto efficiente (nessun overhead nelle chiamate interne)
- Performance elevate per via di chiamate di funzione dirette

**Svantaggi:**
- Difficile da mantenere e debuggare
- Un errore in qualsiasi parte può compromettere l'intero sistema
- Scalabilità limitata con l'aumentare della complessità

**Esempi:** UNIX tradizionale, Linux, Windows (in gran parte)

##### Sistemi a Livelli (Layered Systems)

L'**organizzazione stratificata** dei sistemi operativi è una generalizzazione dell'approccio monolitico.

**Sistema THE:**
Il sistema THE fu uno dei primi a implementare questa idea, con **sei livelli gerarchici**:
- Livello 5: Operatore
- Livello 4: Programmi utente
- Livello 3: Gestione I/O
- Livello 2: Comunicazione operatore-processo
- Livello 1: Gestione memoria e disco
- Livello 0: Allocazione processore e multiprogrammazione

Questi livelli gestivano l'allocazione del processore, la memoria, la comunicazione, l'I/O, i dispositivi, e gli utenti.

**Sistema MULTICS:**
Il sistema MULTICS usava **anelli concentrici** per definire i privilegi, con livelli interni più privilegiati di quelli esterni:

```
           Possible uses of the levels
    User programs ──┐
   Shared libraries──┤
     System calls ───┤
         Kernel ─────┤  ← Livello 0 (più privilegiato)
              1 ─────┤
            2 ───────┤
          3 ─────────┘
               Level
```

**Vantaggi:**
- **Protezione** delle risorse e dati critici
- **Separazione chiara** dei compiti (es. valutazione degli studenti)
- Modularità e separazione delle responsabilità
- Facilita il debugging (livello per livello)
- Buona organizzazione concettuale

**Svantaggi:**
- Difficile definire i livelli appropriati
- Meno efficiente per via dei molteplici attraversamenti di livelli
- Overhead nelle chiamate tra livelli

##### Microkernel (Sistemi Client-Server basati su Microkernel)

Organizza le **service procedure** che vengono eseguite in modo separato come **processi → System Servers/Drivers**.

**Principio fondamentale:**
- Solo le funzioni essenziali rimangono nel kernel (microkernel)
- I servizi principali girano come processi utente
- I processi di sistema comunicano attraverso il **passaggio di messaggi**
- Le chiamate di sistema si basano sullo stesso **meccanismo di messaggistica**
- Meccanismo di messaggistica implementato nel kernel minimale ⇒ **Microkernel**

**Componenti in kernel mode (microkernel):**
- Gestione della memoria di basso livello
- Scheduling della CPU
- Comunicazione inter-processo (IPC)
- Gestione base degli interrupt
- Il microkernel gestisce **interrupts, processes, scheduling, interprocess communication**

**Servizi in user mode:**
- File system (FS)
- Process management (Proc.)
- Reincarnation server (Reinc.)
- Driver di dispositivo (Disk, TTY, Network, Print)
- Server di memoria virtuale
- Altri servizi

**Architettura completa di MINIX:**

```
                    Process
        ┌──────────────────────────────────┐
        │  Shell  Make   Other             │ User programs
User    ├──────────────────────────────────┤
mode    │  FS   Proc.  Reinc.   Other      │ Servers
        ├──────────────────────────────────┤
        │ Disk TTY Netw Print Other        │ Drivers
        ├──────────────────────────────────┤
        │ Microkernel handles interrupts,  │
        │ processes, scheduling, inter-    │Clock Sys
        │ process communication            │
        └──────────────────────────────────┘
```

**Vantaggi (Pro):**
- È più facile aderire al **Principle of Least Authority (POLA)**:
  - **Trusted Computing Base (TCB)** relativamente "piccolo"
  - Ogni processo del sistema operativo può fare solo ciò che è necessario per svolgere il proprio compito
  - La compromissione, ad esempio, del driver di stampa non influisce sul resto del sistema operativo
- **Maggiore affidabilità**: un errore in un server non blocca l'intero sistema
- **Maggiore sicurezza**: servizi isolati
- **Facilita la portabilità** su diverse architetture
- **Facilita l'estensibilità**
- **Isolamento** tra i componenti

**Svantaggi (Contra):**
- Il **passaggio di messaggi è più lento** di una chiamata di funzione (come in un kernel monolitico)
- **Overhead** nelle comunicazioni tra componenti (via IPC)
- **Performance inferiori** rispetto ai sistemi monolitici

**Esempi:** MINIX 3, Mach, QNX, Symbian OS

##### Macchine Virtuali (Virtual Machines)

Le **macchine virtuali (VM)** permettono l'esecuzione di più sistemi operativi su un unico hardware fisico, simulando un ambiente separato per ciascuno.

**Origini e Storia:**

Il sistema **VM/370** di IBM (anni '70) è stato uno dei primi a implementare macchine virtuali:
- Creava ambienti virtuali identici all'hardware fisico
- Capace di eseguire diversi sistemi operativi contemporaneamente
- **Inventato negli anni '70** per separare la multiprogrammazione dalla macchina estesa
- Oggi di nuovo interesse in diversi ambiti
- **N interfacce di chiamata di sistema** indipendenti dal sistema operativo

**Struttura del VM/370 con CMS (Conversational Monitor System):**

```
         Virtual 370s
    ┌───────┬───────┬───────┐
    │       │       │       │ ← System calls here
I/O │  CMS  │  CMS  │  CMS  │ ← Trap here
inst├───────┴───────┴───────┤
here│       VM/370           │ ← Trap here
    ├───────────────────────┤
    │  370 Bare hardware    │
    └───────────────────────┘
```

**Vantaggi:**
- **Isolamento**: Ogni VM opera indipendentemente
- **Flessibilità**: Possibilità di eseguire diversi sistemi operativi simultaneamente (es. OS/360, CMS)
- **Gestione Semplificata**: Facilita la gestione e manutenzione separando multiprogrammazione e risorse hardware

**Uso Moderno:**
Il successore **z/VM** viene utilizzato sui mainframe IBM serie Z per far girare più sistemi operativi completi, come **Linux**, in ambienti ad alta intensità di transazioni e dati.

**Tipi di Hypervisor:**

Il **Virtual Machine Monitor (VMM)** o **Hypervisor** emula l'hardware:

**Type 1 Hypervisor (Bare Metal):**
- VMM viene eseguito sul "pezzo di ferro" (direttamente su HW)
- Esempio: Xen

```
┌──────────────────────┐
│ Excel Word Mplayer   │
│ Apollon              │
├──────┬───────┬───────┤
│      │       │       │
│Windows Linux   ...   │
├──────────────────────┤
│  Type 1 hypervisor   │
├──────────────────────┤
```

**Type 2 Hypervisor (Hosted):**
- VMM ospitato nel sistema operativo
- Esempio: QEMU

**Pure Type 2:**
```
   Guest OS process      Host OS
┌─────────────────┐     process
│  Guest OS       │   ┌───────┐
├─────────────────┤   │       │
│ Machine simulator│   │       │
├─────────────────┤   │       │
│Host operating   │   │       │
│system           │   │       │
└─────────────────┘   └───────┘
```

**Practical Type 2:**
In teoria non c'è nessuna specializzazione da parte del sistema operativo sottostante. Nella pratica esistono dei **moduli del Kernel** usati per ottimizzare il processo di simulazione:

```
   Guest OS process
┌─────────────────┐   Kernel
│  Guest OS       │   module
├─────────────────┤   ┌──┐
│Type 2 hypervisor│───┤  │
├─────────────────┤   └──┘
│Host operating   │
│system           │
└─────────────────┘
```

**Applicazioni Moderne:**
- Cloud computing (AWS, Azure, Google Cloud)
- Testing e sviluppo
- Migrazione e backup semplificati
- Isolamento completo tra VM

##### Container

I **container** possono eseguire più istanze di un sistema operativo su una singola macchina.

**Caratteristiche principali:**
- Ogni container **condivide il kernel** del sistema operativo host e i file binari e le librerie
- Il container **non contiene il sistema operativo completo** e può quindi essere **leggero**
- Forniscono isolamento a livello di processo

**Vantaggi:**
- **Footprint ridotto**: molto più leggeri delle VM
- **Avvio rapido**: lancio quasi istantaneo
- **Efficienza**: condividono risorse con l'host
- **Portabilità**: facilmente trasferibili tra ambienti

**Svantaggi dei container:**
- **Non è possibile eseguire un container con un sistema operativo completamente diverso** da quello dell'host
- A differenza delle macchine virtuali, **non esiste un rigido partizionamento delle risorse**
- I container sono **isolati a livello di processo**
- Se un container altera la stabilità del kernel sottostante, ciò può influire sugli altri container

**Esempi:** Docker, Kubernetes, LXC, Podman

##### Exokernel

**Idea centrale:** Separare il controllo delle risorse dalla macchina estesa

**Caratteristiche:**
- Simile a un VMM/Hypervisor, ma:
  - **Exokernel non emula l'hardware**
  - Fornisce solo una **condivisione sicura delle risorse a basso livello**
- Ogni **macchina virtuale a livello utente** esegue il suo sistema operativo, ma è limitata a utilizzare solo le risorse assegnate
- Rispetto ad altri approcci, l'exokernel elimina la necessità di mappature complesse, concentrandosi solo su **quale macchina virtuale ha accesso a quali risorse**

**Vantaggi:**
- **Massima efficienza** e controllo
- Le applicazioni possono implementare le proprie astrazioni
- **Eliminazione overhead** delle mappature complesse

**Uso:**
- Usato principalmente in contesti di ricerca
- Sistemi specializzati ad alte prestazioni

##### Unikernel

Gli **unikernel** sono sistemi minimi basati su **LibOS** (Library Operating System), progettati per eseguire una **singola applicazione** su una macchina virtuale.

**Caratteristiche:**
- **Esempio:** WebServer
- Questi sistemi contengono **solo la funzionalità necessaria** per supportare l'applicazione specifica, come un server web, su una macchina virtuale
- Gli unikernel sono **altamente efficienti** poiché non richiedono protezione tra il sistema operativo (LibOS)
  - Esiste solo un'applicazione per macchina virtuale

**Vantaggi:**
- **Footprint molto ridotto**: dimensioni minime
- **Avvio velocissimo**: startup in millisecondi
- **Sicurezza aumentata**: superficie di attacco ridotta
- **Performance**: nessun overhead di protezione tra SO e applicazione

**Uso:**
- Applicazioni cloud specializzate
- Sistemi embedded
- Microservizi

**Storia:**
Il concetto degli unikernel è stato recentemente riscoperto, offrendo una soluzione leggera ed efficiente per eseguire applicazioni isolate su macchine virtuali.

##### Client-Server Model
Una variante del microkernel dove i servizi sono organizzati come server che rispondono a richieste dei client.

**Funzionamento:**
1. Un processo client richiede un servizio
2. Il messaggio viene inviato al server appropriato
3. Il server elabora la richiesta
4. La risposta viene inviata al client

Questa struttura facilita l'implementazione di sistemi distribuiti.

##### Macchine Virtuali
Il sistema operativo crea l'illusione di avere multiple macchine virtuali, ciascuna con il proprio sistema operativo.

**Tipi di virtualizzazione:**
- **Type 1 (Bare Metal)**: l'hypervisor gira direttamente sull'hardware (VMware ESXi, Xen, Hyper-V)
- **Type 2 (Hosted)**: l'hypervisor gira sopra un sistema operativo host (VirtualBox, VMware Workstation)

**Vantaggi:**
- Isolamento completo tra VM
- Possibilità di eseguire sistemi operativi diversi simultaneamente
- Facilita testing e sviluppo
- Migrazione e backup semplificati

**Uso moderno:**
- Cloud computing (AWS, Azure, Google Cloud)
- Containerizzazione (Docker, Kubernetes)

##### Exokernel
Approccio radicale che elimina quasi completamente l'astrazione. L'exokernel si limita a proteggere le risorse e le alloca ai programmi applicativi, che gestiscono direttamente l'hardware.

**Caratteristiche:**
- Massima efficienza e controllo
- Le applicazioni possono implementare le proprie astrazioni
- Usato principalmente in contesti di ricerca

##### Unikernel
Architettura specializzata dove l'applicazione e il sistema operativo minimo necessario sono compilati insieme in un singolo binario.

**Vantaggi:**
- Footprint molto ridotto
- Avvio velocissimo
- Sicurezza aumentata (superficie di attacco ridotta)

**Uso:**
- Applicazioni cloud specializzate
- Sistemi embedded
- Microservizi