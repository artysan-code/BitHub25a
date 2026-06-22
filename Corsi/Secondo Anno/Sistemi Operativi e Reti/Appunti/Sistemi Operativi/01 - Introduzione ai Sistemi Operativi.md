# 01 - Introduzione ai Sistemi Operativi
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
### Modalità kernel e modalità utente
L'hardware supporta (almeno) due modalità operative:

- **Modalità kernel** (o **supervisor**): accesso completo all'hardware, può eseguire qualsiasi istruzione. Vi gira il sistema operativo.
- **Modalità utente**: disponibile solo un sottoinsieme di istruzioni, accesso all'hardware controllato. Vi girano le applicazioni.

> [!example] Perché la distinzione conta
> Un utente è libero di sostituire il proprio client di posta o di scriverne uno; **non** è libero di scrivere il gestore degli interrupt del clock, che è parte del SO ed è protetto dall'hardware contro le modifiche. Questa barriera è meno netta nei sistemi [[#^embedded|embedded]].
## Storia dei sistemi operativi
L'idea risale a **Charles Babbage** (1792-1871) e al suo *motore analitico*, mai completato; **Ada Lovelace** ne scrisse il software (da cui il linguaggio Ada). I SO veri arrivano però con i computer elettronici.
### Prima generazione (1945-55) — valvole termoioniche
Macchine a **valvole termoioniche** o **relè elettromeccanici** (a valvole: l'**ENIAC** di Mauchly ed Eckert e il **Colossus**; a relè: lo **Z3** di Zuse e il **Mark I**; il *primo computer digitale funzionante* fu però l'**ABC** di Atanasoff e Berry). Lentissime, programmate **cablando circuiti** o in linguaggio macchina puro. **Nessun sistema operativo, nessun linguaggio di programmazione**. Negli anni '50 arrivano le **schede perforate**.
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

> [!info] Nascita di UNIX
> Da MULTICS, **Ken Thompson** (Bell Labs) scrive una versione ridotta — inizialmente **monoutente** su PDP-7 — poi evoluta su PDP-11 e **riscritta in C** da Dennis Ritchie: nasce **UNIX** (multiutente). Il proliferare di varianti incompatibili porta allo standard **POSIX** (IEEE). Da UNIX derivano **MINIX** (didattico, micro-kernel, → MINIX 3) e, ispirato a MINIX, **Linux** di Linus Torvalds.
### Quarta generazione (1980-oggi) — personal computer
I circuiti **LSI** (migliaia di transistor per cm²) rendono possibile il PC. Intel rilascia l'**8080** (1974). Quando IBM cerca un SO, **Microsoft** acquista il DOS da Seattle Computer Products e lo adatta a **MS-DOS**, dominando il mercato dei PC IBM.

La **GUI** — inventata da **Engelbart** e sviluppata allo **Xerox PARC** — viene colta da **Steve Jobs**: nasce l'**Apple Macintosh**, user-friendly e di successo. Microsoft risponde con **Windows**, inizialmente ambiente grafico sopra MS-DOS, poi sistema autonomo (Windows 95 → XP → 7 → 8…). Apple adotta poi un kernel derivato dal microkernel **Mach** su base **BSD UNIX**: **macOS** è quindi un sistema UNIX-based.
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
- **Multicore**: più core reali sullo stesso chip; possono condividere o meno le cache.
- **GPU**: migliaia di core semplici per calcolo massicciamente parallelo (SIMD), usata anche per calcolo generico (GPGPU).

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

Le **cache** nascondono la latenza della RAM sfruttando la **località spaziale** (dati vicini) e **temporale** (dati usati di recente). La **MMU (Memory Management Unit)** traduce gli indirizzi **virtuali** in **fisici**, abilita la [[06 - Gestione della Memoria|memoria virtuale]] e protegge lo spazio di indirizzi di ogni processo; usa il **TLB** come cache delle traduzioni.
### Dischi e memoria di massa
- **HDD (Hard Disk Drive)**: piatti magnetici rotanti, testine su braccio mobile. Tempo di accesso = *seek time* + *rotational delay* + *transfer time*. Organizzazione in tracce, settori, cilindri.
- **SSD (Solid State Drive)**: memoria flash NAND, nessuna parte mobile, molto più veloce negli accessi casuali; richiede **wear leveling**.
### Dispositivi di I/O
Ogni dispositivo ha due parti: un **controller** (interfaccia con registri di controllo/stato, semplice da pilotare per il SO) e il **dispositivo fisico**. Il **driver** (in kernel mode) traduce le richieste del SO in comandi per il controller. Tre modi di gestire un trasferimento:

- **Polling** (*busy waiting*): la CPU interroga di continuo il dispositivo — spreca cicli.
- **Interrupt-driven**: il dispositivo genera un **interrupt** quando è pronto — efficiente (ripreso in [[08 - Input Output]]).
- **DMA (Direct Memory Access)**: un controller trasferisce i dati direttamente da/verso la memoria senza impegnare la CPU — ottimale per grandi quantità.
### Bus e avvio
I componenti comunicano tramite **bus** (CPU-RAM, PCIe per le periferiche, SATA per i dischi, USB hot-pluggable). All'accensione, il firmware (**BIOS/UEFI**) esegue il **boot**: test dell'hardware, individuazione del dispositivo di avvio, caricamento del SO in memoria.
## Panoramica dei sistemi operativi (lo "zoo")
Esistono SO molto diversi a seconda del contesto d'uso:

- **Mainframe**: orientati a throughput elevato — *batch processing*, elaborazione di transazioni, time-sharing per molti utenti (es. z/OS, applicazioni mission-critical bancarie).
- **Server**: servono più utenti in rete (file sharing, database, stampa, hosting web). Es. Linux, FreeBSD, Windows Server, Solaris.
- **Multiprocessore**: gestiscono più CPU/core per maggiore potenza.
- **Personal computer**: singolo utente, multiprogrammazione, GUI, applicazioni di produttività. Es. Windows, macOS, Linux.
- **Palmari / smartphone**: multicore, GPS, fotocamere, app di terze parti. Es. Android, iOS.
- **Embedded / IoT**: footprint ridotto, funzioni specifiche, dispositivi connessi (TV, elettrodomestici, telecamere). Es. Embedded Linux, QNX, RIOT. ^embedded
- **Real-time**: rispettano scadenze temporali rigide. **Hard real-time** (scadenze inviolabili, es. controllo industriale/militare) vs **soft real-time** (ritardi occasionali tollerabili). Es. VxWorks, eCos.
- **Smart card**: risorse minime, spesso orientati a Java (JavaCard).

> [!info] Cosa hanno in comune
> Indipendentemente dalla categoria, tutti i SO svolgono le due funzioni viste: **macchina estesa** (astrazione dell'hardware) e **gestore delle risorse** (multiplexing nel tempo e nello spazio, isolamento, accounting).

---

**Prossimo argomento:** [[02 - Concetti di Base e Strutture]] — system call, l'astrazione di processo e file, e le strutture interne del sistema operativo.
