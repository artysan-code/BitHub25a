# Introduzione ai Sistemi Operativi
Un calcolatore moderno è un sistema complesso: uno o più **processori**, **memoria centrale**, **dischi**, **periferiche di I/O** (tastiera, mouse, monitor, interfacce di rete) collegati da un sistema di **bus**. Gestire direttamente questo hardware è troppo difficile, quindi i computer dispongono di uno strato di software — il **sistema operativo (SO)** — che si frappone tra hardware e applicazioni.

L'utente non interagisce mai direttamente col SO, ma tramite un programma di interfaccia: la **shell** (modalità testo) o la **GUI** (icone, finestre, mouse). Attenzione: shell e GUI **non sono** il sistema operativo, ma solo il livello più basso del software in modalità utente.
## Cos'è un sistema operativo
È difficile definire un SO oltre alla constatazione che è *il software che gira in modalità kernel* — e nemmeno questo è del tutto vero (parti come la GUI girano in modalità utente). Il SO svolge due funzioni non correlate, che corrispondono a due visioni complementari.

> [!quote] Definizione — Sistema operativo
> Strato di software che astrae e gestisce le risorse hardware, fornendo ai programmi un'interfaccia semplice e ordinata e arbitrando l'accesso condiviso alle risorse.
### Macchina estesa (visione top-down)
A livello di linguaggio macchina l'hardware è **primitivo e scomodo** da programmare, soprattutto per l'I/O. Il SO nasconde questa complessità dietro **astrazioni**:
- I **driver** astraggono i singoli dispositivi: un driver è l'interfaccia che permette al SO di parlare con un dispositivo specifico.
- Sopra i driver, l'astrazione del **file** (vedi [[07 - File System]]) permette di leggere/scrivere/creare dati senza conoscere settori, tracce e cilindri del disco.

> [!info] Principio
> Una buona astrazione trasforma un'attività quasi impossibile (gestire l'hardware nudo) in due attività fattibili (definire l'astrazione, e usarla).
### Gestore delle risorse (visione bottom-up)
Il SO esiste per **gestire in modo ordinato e controllato** le risorse di un sistema complesso, condivise tra più programmi e utenti. La condivisione (**multiplexing**) avviene in due modi:
- **Nel tempo**: programmi/utenti si alternano nell'uso della stessa risorsa (es. la CPU, la stampante).
- **Nello spazio**: la risorsa è divisa tra più utenti (es. la memoria, il disco).

Il SO deve inoltre garantire **isolamento** tra i processi, **equità** nell'accesso e tracciamento dell'uso delle risorse (*accounting*).

> [!question] Domanda tipica d'esame
> - **D:** Quali sono le due visioni (funzioni) di un sistema operativo? **R:** **Macchina estesa** (top-down): nasconde la complessità dell'hardware dietro astrazioni (driver, file), offrendo ai programmi un'interfaccia pulita. **Gestore delle risorse** (bottom-up): alloca in modo ordinato e controllato le risorse condivise tramite **multiplexing nel tempo** (CPU, stampante) e **nello spazio** (RAM, disco), garantendo isolamento, equità e accounting.
### Modalità kernel e modalità utente
L'hardware supporta (almeno) due modalità operative:
- **Modalità kernel** (o **supervisor**): accesso completo all'hardware, può eseguire qualsiasi istruzione. Vi gira il sistema operativo.
- **Modalità utente**: disponibile solo un sottoinsieme di istruzioni, accesso all'hardware controllato. Vi girano le applicazioni.

> [!example] Perché la distinzione conta
> Un utente è libero di sostituire il proprio client di posta o di scriverne uno; **non** è libero di scrivere il gestore degli interrupt del clock, che è parte del SO ed è protetto dall'hardware contro le modifiche. Questa barriera è meno netta nei sistemi [[#^embedded|embedded]].

> [!question] Domanda tipica d'esame
> - **D:** Differenza tra modalità kernel e modalità utente, e perché è necessaria? **R:** In **modalità kernel** (supervisor) si ha accesso completo all'hardware e a tutte le istruzioni: vi gira il SO. In **modalità utente** è disponibile solo un sottoinsieme di istruzioni con accesso controllato all'hardware: vi girano le applicazioni. La distinzione **protegge** il SO — un'applicazione non può, ad esempio, riscrivere il gestore degli interrupt del clock o accedere direttamente all'hardware.
## Storia dei sistemi operativi
L'idea risale a **Charles Babbage** (1792-1871) e al suo *motore analitico*, mai completato; **Ada Lovelace** ne scrisse il software (da cui il linguaggio Ada). I SO veri arrivano però con i computer elettronici.
### Prima generazione (1945-55) — valvole termoioniche
Le prime macchine si dividevano per tecnologia costruttiva:
- a **valvole termoioniche**: l'**ENIAC** di Mauchly ed Eckert e il **Colossus**;
- a **relè elettromeccanici**: lo **Z3** di Zuse e il **Mark I**.

Il *primo computer digitale funzionante* fu però l'**ABC** di Atanasoff e Berry. Erano macchine lentissime, programmate **cablando circuiti** o in linguaggio macchina puro: **nessun sistema operativo, nessun linguaggio di programmazione**. Negli anni '50 arrivano le **schede perforate**.
### Seconda generazione (1955-65) — transistor e sistemi batch
I **transistor** rendono i computer affidabili: nascono i **mainframe**, chiusi in sale condizionate e gestiti da operatori professionali. Per eseguire un **job** si scriveva il programma (FORTRAN o assembler), lo si perforava su schede e si attendeva la stampa.

Per ridurre i tempi morti nasce il **sistema batch**: i job vengono raccolti e riversati su nastro magnetico da un computer ausiliario economico (IBM 1401), poi elaborati in blocco dalla macchina principale (IBM 7094).

> [!example] Struttura di un job batch (schede di controllo)
> `$JOB` (tempo max, utente, programmatore) → `$FORTRAN` (carica il compilatore) → *programma sorgente* → `$LOAD` (carica l'eseguibile) → `$RUN` (esegui) → `$END`.
### Terza generazione (1965-80) — circuiti integrati e multiprogrammazione
I **circuiti integrati (IC)** migliorano il rapporto prezzo/prestazioni. IBM unifica le linee scientifica (*word-oriented*, 7094) e commerciale (*character-oriented*, 1401) con il **System/360**, prima **famiglia di computer compatibili** con lo stesso set di istruzioni (discendenti fino alla serie Z). Idee chiave introdotte:
- **Multiprogrammazione**: la memoria è partizionata tra più job; mentre uno attende l'I/O, la CPU lavora su un altro, evitando di restare inattiva (critico per i carichi commerciali, dove l'attesa I/O è l'80-90% del tempo).
- **Spooling** (*Simultaneous Peripheral Operation On Line*): i job vengono caricati su disco appena arrivano, senza fermare la macchina.
- **Time-sharing**: variante della multiprogrammazione in cui più utenti interattivi condividono la CPU a turni rapidi (primo sistema: CTSS del M.I.T. su 7094). Da qui **MULTICS**, antesignano del concetto di *computer utility* e quindi del **cloud** moderno.

> [!question] Domande tipiche d'esame
> - **D:** Cos'è la multiprogrammazione e quale problema risolve? **R:** Partiziona la memoria tra più job: mentre uno attende l'**I/O**, la CPU esegue un altro job, evitando di restare inattiva. Risolve lo spreco dovuto all'attesa dell'I/O, che nei carichi commerciali arriva all'**80–90%** del tempo.
> - **D:** Cosa introduce il System/360 di IBM? **R:** La prima **famiglia di computer compatibili** (stesso set di istruzioni, modelli scalabili che eseguono lo stesso software) e la diffusione su larga scala di **multiprogrammazione** e **spooling**.

> [!info] Nascita di UNIX
> Da MULTICS, **Ken Thompson** (Bell Labs, 1969) scrive una versione ridotta — chiamata inizialmente **UNICS** (*UNIplexed Information and Computing Service*), poi rinominata UNIX — su PDP-7 in assembler, poi evoluta su PDP-11 (1970-1974) e **riscritta in C** da Dennis Ritchie (partendo dal linguaggio B). La terza versione di UNIX è già scritta in C. Nel **1974** viene pubblicato un articolo su UNIX su *Communications of the ACM*; Thompson e Ritchie ricevono il **ACM Turing Award nel 1984**. UNIX diventa popolare in ambito accademico e aziendale, ma il proliferare di varianti incompatibili (ramo **System V** e ramo **BSD**) genera frammentazione. Per porvi rimedio nasce lo standard **POSIX** (IEEE, 1984, fusione di System V e BSD), cui si aggiungono nel tempo i progetti [[#^stdunix|di standardizzazione]] OSF, X/Open e Open Group. Da UNIX derivano **MINIX** (didattico, micro-kernel, → MINIX 3) e, ispirato a MINIX, **Linux** di Linus Torvalds (1991).

Le varianti commerciali più importanti erano basate su **UNIX System V Release 4 (SVR4)**; **Solaris 2.x** (Sun Microsystems) ne è l'implementazione di maggior successo commerciale. Questi sistemi erano però diventati molto grossi e complicati — al contrario dell'idea originaria di Thompson. Nel **1987** **Andrew Tanenbaum** sviluppa **MINIX**, un piccolo sistema UNIX compatibile con POSIX scritto a scopo didattico e basato sul modello a **micro-kernel**: circa **11.800 righe di C** e **800 righe di Assembler**. MINIX è poi la principale ispirazione per Linux (vedi messaggio storico di Torvalds del 1991 su comp.os.minix).

> [!info] Progetti di standardizzazione UNIX ^stdunix
> Alla frammentazione System V / BSD rispondono diversi enti:
> - **POSIX** (IEEE, 1984): standard di interfaccia unificata.
> - **OSF** (*Open Software Foundation*, 1988): consorzio IBM, DEC, Hewlett-Packard; produce **OSF/1**.
> - **X/Open** (1993): definisce la **Single UNIX Specification**; i sistemi conformi ottengono il marchio **UNIX 95**.
> - **Open Group** (1996, fusione OSF + X/Open): emana la seconda versione della Single UNIX Specification (1997) con marchio **UNIX 98**.

> [!info] MINIX 3 e Intel Management Engine
> **MINIX 3** (Vrije Universiteit Amsterdam) è stato adottato da **Intel** per il suo **Management Engine (ME)**, il sottosistema di gestione integrato nei processori moderni. È quindi presente in quasi tutti i desktop, server e laptop x86, rendendolo di fatto uno dei SO più diffusi al mondo pur restando invisibile all'utente finale. La licenza è della Vrije Universiteit Amsterdam (copyright 1987, 1997, 2006).

> [!info] Albero genealogico delle varianti UNIX *(approfondimento)*
> Il diagramma delle slide (*A Success Story*) mostra tre rami principali:
> - **BSD** (Berkeley Software Distribution): da Unix V5/V6 → BSD 1.x-4.3 → FreeBSD, NetBSD, OpenBSD, DragonFly BSD → **macOS** (via NeXTSTEP/OPENSTEP e il kernel Darwin, basato su Mach + BSD).
> - **System V**: Unix/32V → System III → System V R1–R4 → **Solaris** (Sun/Oracle), HP-UX, AIX, UnixWare, SCO.
> - **Linux** (1991): nasce ispirato a MINIX, ma indipendente; evolve in parallelo, con Android come suo principale discendente mobile.
> Le varianti a sorgente aperto (verdi nel diagramma) convivono con quelle proprietarie (rosse: HP-UX, AIX, Solaris). macOS è derivato da BSD/NeXTSTEP ed è quindi UNIX-based.
### Quarta generazione (1980-oggi) — personal computer
I circuiti **LSI** (migliaia di transistor per cm²) rendono possibile il PC. Intel rilascia l'**8080** (1974): **Gary Kildall** scrive per esso il sistema operativo **CP/M** e fonda **Digital Research**, che lo adatta ai microcomputer. Quando negli anni '80 IBM cerca un SO per il suo PC, **Kildall rifiuta l'incontro** con IBM — un'occasione mancata storica; così **Microsoft** acquista il DOS da Seattle Computer Products e lo adatta a **MS-DOS**, dominando il mercato dei PC IBM.

La **GUI** — inventata da **Engelbart** e sviluppata allo **Xerox PARC** — viene colta da **Steve Jobs**: nasce l'**Apple Macintosh**, user-friendly e di successo. Microsoft risponde con **Windows**, inizialmente ambiente grafico sopra MS-DOS, poi sistema autonomo (Windows 95 → XP → 7 → 8…). La linea professionale **Windows NT** fu invece fortemente influenzata dall'architettura del **VMS** di **DEC** (i minicomputer VAX) — una parentela che sfociò poi in una controversia legale con DEC. Apple adotta poi un kernel derivato dal microkernel **Mach** su base **BSD UNIX**: **macOS** è quindi un sistema UNIX-based.
### Quinta generazione (1990-oggi) — computer mobili
Dai primi telefoni portatili ("il mattone") agli **smartphone** (Nokia N9000, 1996; termine coniato da Ericsson nel 1997). Oggi il mercato è dominato da **Android** (Google, basato su Linux) e **iOS** (Apple), dopo una fase iniziale di **Symbian OS**.
## Analisi dell'hardware
Il SO è intimamente legato all'hardware su cui gira e deve conoscerlo a fondo.
### Processori (CPU)
La CPU esegue il **ciclo fetch-decode-execute**: preleva l'istruzione, la decodifica, la esegue, ripete. Ogni CPU ha un proprio **instruction set (ISA)**: un binario x86 non gira su ARM e viceversa.

Contiene **registri** interni per dati e risultati temporanei, tra cui:
- **Program Counter (PC)**: indirizzo della prossima istruzione.
- **Stack Pointer (SP)**: cima dello stack (frame di procedura, parametri, variabili locali).
- **PSW (Program Status Word)**: bit di condizione, bit di modalità (kernel/user), priorità.

Il **cambio di contesto** ([[03 - Processi e Thread|context switch]]) salva i registri del processo corrente e carica quelli del prossimo, permettendo il multitasking. Tecniche hardware per le prestazioni:
- **Pipeline**: gli stadi (fetch/decode/execute) di istruzioni successive si sovrappongono, aumentando il throughput.
- **Multithreading / hyperthreading**: la CPU mantiene lo stato di più thread e commuta rapidamente quando uno si blocca — **non** è vero parallelismo, ma il SO vede i thread hardware come CPU separate.
- **Multicore**: più core reali sullo stesso chip. La cache L2 può seguire due topologie: **(a)** condivisa tra tutti i core (un unico blocco di L2 sul chip, accesso uniforme) oppure **(b)** privata per ogni core (ciascun core ha la propria L2 locale). In entrambi i casi la cache L1 resta privata per core.
- **GPU**: migliaia di core semplici per calcolo massicciamente parallelo (SIMD), usata anche per calcolo generico (GPGPU).
- **Multiprocessori**: più CPU fisiche nello stesso sistema. Tre vantaggi principali: **throughput** (più lavoro svolto in parallelo), **economia di scala** (le CPU condividono alimentazione, contenitore e periferiche, costando meno di tante macchine separate) e **affidabilità** (il guasto di una CPU degrada le prestazioni ma non ferma il sistema).

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> Il funzionamento dettagliato della CPU (ciclo fetch-decode-execute, registri, microarchitettura, pipeline) è trattato nel corso del primo anno: [[2 - Organizzazione dei sistemi di calcolo]] e [[4 - Livello di microarchitettura]].
### Memoria
La memoria è organizzata in una **gerarchia**, con trade-off tra velocità, capacità e costo:

| Livello | Tempo di accesso | Capacità | Volatile |
|---|---|---|---|
| Registri | < 1 ns | < 1 KB | sì |
| Cache (L1/L2/L3) | pochi ns | KB–MB | sì |
| Memoria centrale (RAM) | decine di ns | GB | sì |
| Disco / SSD | µs–ms | TB | no |

Le **cache** nascondono la latenza della RAM scommettendo su due principi di **località**: **temporale** (un dato usato di recente sarà probabilmente riusato a breve) e **spaziale** (accedendo a un dato, è probabile accedere a quelli a esso vicini). Su questi due principi si fonda l'efficacia di qualsiasi cache.

> [!info] I quattro problemi di gestione di una cache
> Qualsiasi sistema di cache (non solo quella della CPU) deve risolvere quattro domande, che ritroveremo identiche negli [[06 - Gestione della Memoria#Algoritmi di sostituzione delle pagine|algoritmi di sostituzione delle pagine]] e nella [[07 - File System#Block cache (buffer cache)|block cache]]:
> 1. **Quando** inserire un nuovo elemento nella cache?
> 2. **In quale riga** della cache inserirlo?
> 3. **Quale elemento rimuovere** quando serve liberare uno slot?
> 4. **Dove** mettere nella memoria più grande l'elemento appena rimosso?

La **MMU (Memory Management Unit)** traduce gli indirizzi **virtuali** in **fisici**, abilita la [[06 - Gestione della Memoria|memoria virtuale]] e protegge lo spazio di indirizzi di ogni processo. Per non rifare ogni volta la stessa traduzione, si appoggia al **TLB (Translation Lookaside Buffer)**: una piccola cache che conserva le traduzioni indirizzo→pagina più recenti, così la MMU le riusa invece di ricalcolarle (approfondito in [[06 - Gestione della Memoria]]).
### Dischi e memoria di massa
- **HDD (Hard Disk Drive)**: piatti magnetici rotanti, testine su braccio mobile. Tempo di accesso = *seek time* + *rotational delay* + *transfer time*. Organizzazione in tracce, settori, cilindri.
- **SSD (Solid State Drive)**: memoria flash NAND, nessuna parte mobile, molto più veloce negli accessi casuali; richiede **wear leveling**.
### Dispositivi di I/O
Ogni dispositivo ha due parti: un **controller** (interfaccia con registri di controllo/stato, semplice da pilotare per il SO) e il **dispositivo fisico**. Il **driver** (in kernel mode) traduce le richieste del SO in comandi per il controller, accedendo ai suoi registri tramite **porte di I/O dedicate** o **memoria mappata** (PMIO/MMIO, approfonditi in [[08 - Input Output]]). Tre modi di gestire un trasferimento:
- **Polling** (*busy waiting*): la CPU interroga di continuo il dispositivo — spreca cicli.
- **Interrupt-driven**: il dispositivo genera un **interrupt** quando è pronto — efficiente (ripreso in [[08 - Input Output]]).
- **DMA (Direct Memory Access)**: un controller trasferisce i dati direttamente da/verso la memoria senza impegnare la CPU — ottimale per grandi quantità.

> [!question] Domanda tipica d'esame
> - **D:** Quali sono i tre modi in cui il SO può gestire un trasferimento di I/O? **R:** **Polling** (*busy waiting*): la CPU interroga di continuo il dispositivo, sprecando cicli. **Interrupt-driven**: il dispositivo genera un interrupt quando è pronto, liberando la CPU nel frattempo. **DMA**: un controller trasferisce i dati direttamente da/verso la memoria senza impegnare la CPU, ideale per grandi quantità. Approfonditi in [[08 - Input Output]].
### Architettura dei bus (x86)
Un sistema x86 moderno ha **più bus** con funzioni e velocità diverse:
- **DDR4**: bus veloce tra CPU e **memoria** centrale.
- **PCIe** (*Peripheral Component Interconnect Express*): il bus principale e più veloce, usa connessioni **punto-punto dedicate** (più efficienti dei bus condivisi), tipicamente per la **GPU**.
- **DMI** (*Direct Media Interface*): collega la CPU a un **hub** che raccoglie tutti gli altri dispositivi (compresi quelli **legacy**, su un hub separato).
- **USB** (*Universal Serial Bus*): nato per i dispositivi **lenti**, oggi raggiunge fino a **40 Gbps**; connettore a **4–11 conduttori** (alimentazione + dati); è **hot-pluggable** (collegamento immediato senza riavvio).
### Sequenza di avvio (BIOS/UEFI)
All'accensione il firmware (**BIOS/UEFI**) esegue il **boot**.

> [!example] Sequenza di avvio del BIOS
> 1. La **memoria flash** della scheda madre contiene il firmware (BIOS); premuto il pulsante di accensione, la CPU **esegue il BIOS**.
> 2. Il BIOS **inizializza la RAM** e le altre risorse, esegue la **scansione dei bus PCI/PCIe** e inizializza i dispositivi, imposta il **firmware runtime** per i servizi critici (es. I/O a basso livello).
> 3. Cerca la **tabella delle partizioni** sul **secondo settore** del dispositivo di avvio (contiene le posizioni delle altre partizioni).
> 4. Sa leggere **file system semplici** (es. **FAT-32**) e carica il **primo bootloader** dalla partizione indicata dal boot manager; il bootloader può caricarne altri a catena.
> 5. Alla fine viene caricato il **sistema operativo**.
>
> L'alternativa moderna al BIOS è **UEFI** (con tabella partizioni **GPT**, Secure Boot, superamento del limite di 2,2 TB), trattata in [[07 - File System#Layout del file system|File System]].
## Panoramica dei sistemi operativi (lo "zoo")
Le slide del corso si concentrano su server e dispositivi mobili; il Tanenbaum (cap. 1) presenta però un'intera "fauna" di SO secondo il contesto d'uso *(panoramica utile, oltre il perimetro stretto delle slide)*:
- **Mainframe**: orientati a throughput elevato — *batch processing*, elaborazione di transazioni, time-sharing per molti utenti (es. z/OS, applicazioni mission-critical bancarie).
- **Server**: servono più utenti in rete (file sharing, database, stampa, hosting web). Es. Linux, FreeBSD, Windows Server, Solaris.
- **Multiprocessore**: gestiscono più CPU/core per maggiore potenza.
- **Personal computer**: singolo utente, multiprogrammazione, GUI, applicazioni di produttività. Es. Windows, macOS, Linux.
- **Palmari / smartphone**: multicore, GPS, fotocamere, app di terze parti. Es. Android, iOS.
- **Embedded / IoT**: footprint ridotto, funzioni specifiche, dispositivi connessi (TV, elettrodomestici, telecamere, schede come **Arduino** ed **ESP32**). Es. Embedded Linux, QNX, RIOT. ^embedded
- **Real-time**: rispettano scadenze temporali rigide. **Hard real-time** (scadenze inviolabili, es. controllo industriale/militare) vs **soft real-time** (ritardi occasionali tollerabili). Es. VxWorks, eCos.
- **Smart card**: risorse minime, spesso orientati a Java (JavaCard).

> [!info] Cosa hanno in comune
> Indipendentemente dalla categoria, tutti i SO svolgono le due funzioni viste: **macchina estesa** (astrazione dell'hardware) e **gestore delle risorse** (multiplexing nel tempo e nello spazio, isolamento, accounting).

---

**Prossimo argomento:** [[02 - Concetti di Base e Strutture]] — system call, l'astrazione di processo e file, e le strutture interne del sistema operativo.
