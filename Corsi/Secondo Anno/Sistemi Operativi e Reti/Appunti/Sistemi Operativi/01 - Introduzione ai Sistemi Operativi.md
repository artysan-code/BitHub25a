# Introduzione ai Sistemi Operativi
Un calcolatore moderno è un sistema complesso: uno o più **processori**, **memoria centrale**, **dischi**, **periferiche di I/O** (tastiera, mouse, monitor, interfacce di rete) collegati da un sistema di **bus**. Gestire direttamente questo hardware è troppo difficile, quindi i computer dispongono di uno strato di software — il **sistema operativo (SO)** — che si frappone tra hardware e applicazioni.

L'utente non interagisce mai direttamente col SO, ma tramite un programma di interfaccia: la **shell** (modalità testo) o la **GUI** (icone, finestre, mouse). Attenzione: shell e GUI **non sono** il sistema operativo, ma solo il livello più basso del software in modalità utente. *(extra, non da slide)*
## Cos'è un sistema operativo
È difficile definire un SO oltre alla constatazione che è *il software che gira in modalità kernel* — e nemmeno questo è del tutto vero (parti come la GUI girano in modalità utente). *(extra, non da slide)* Il SO svolge due funzioni non correlate, che corrispondono a due visioni complementari.

> [!quote] Definizione — Sistema operativo
> Strato di software che astrae e gestisce le risorse hardware, fornendo ai programmi un'interfaccia semplice e ordinata e arbitrando l'accesso condiviso alle risorse.
### Macchina estesa (visione top-down)
A livello di linguaggio macchina l'hardware è **primitivo e scomodo** da programmare, soprattutto per l'I/O. Il SO nasconde questa complessità dietro **astrazioni**:
- I **driver** astraggono i singoli dispositivi: un driver è l'interfaccia che permette al SO di parlare con un dispositivo specifico. *(extra, non da slide)*
- Sopra i driver, l'astrazione del **file** (vedi [[07 - File System]]) permette di leggere/scrivere/creare dati senza conoscere settori, tracce e cilindri del disco. *(extra, non da slide)*

> [!info] Principio *(extra, non da slide)*
> Una buona astrazione trasforma un'attività quasi impossibile (gestire l'hardware nudo) in due attività fattibili (definire l'astrazione, e usarla).
### Gestore delle risorse (visione bottom-up)
Il SO esiste per **gestire in modo ordinato e controllato** le risorse di un sistema complesso, condivise tra più programmi e utenti. La condivisione (**multiplexing**) avviene in due modi:
- **Nel tempo**: programmi/utenti si alternano nell'uso della stessa risorsa (es. la CPU, la stampante).
- **Nello spazio**: la risorsa è divisa tra più utenti (es. la memoria, il disco).

Le risorse gestite non sono solo hardware (processori, memoria, unità di I/O) ma anche **file** e **database**.

Il SO deve inoltre garantire **isolamento** tra i processi, **equità** nell'accesso e tracciamento dell'uso delle risorse (*accounting*) *(slide 3, p. 7: «protegge l'uso simultaneo/non sicuro delle risorse», «condivisione equa», «resource accounting/limiting»)*.
### Modalità kernel e modalità utente
L'hardware supporta (almeno) due modalità operative:
- **Modalità kernel** (o **supervisor**): accesso completo all'hardware, può eseguire qualsiasi istruzione. Vi gira il sistema operativo.
- **Modalità utente**: disponibile solo un sottoinsieme di istruzioni, accesso all'hardware controllato. Vi girano le applicazioni.

> [!example] Perché la distinzione conta *(extra, non da slide)*
> Un utente è libero di sostituire il proprio client di posta o di scriverne uno; **non** è libero di scrivere il gestore degli interrupt del clock, che è parte del SO ed è protetto dall'hardware contro le modifiche. Questa barriera è meno netta nei sistemi [[#^embedded|embedded]].

> [!question] Domande tipiche d'esame
> - **D:** Quali sono le due visioni di un sistema operativo? **R:** **Macchina estesa** (top-down): il SO nasconde la complessità dell'hardware dietro astrazioni (driver, file) e offre ai programmi un'interfaccia semplice. **Gestore delle risorse** (bottom-up): il SO alloca in modo ordinato e controllato processori, memoria e I/O tra più programmi e utenti, con multiplexing nel tempo (CPU, stampante) e nello spazio (memoria, disco).
> - **D:** Che differenza c'è tra modalità kernel e modalità utente? **R:** In **modalità kernel** (supervisor) si ha accesso completo all'hardware e si può eseguire qualsiasi istruzione: vi gira il SO. In **modalità utente** è disponibile solo un sottoinsieme di istruzioni, con accesso all'hardware controllato: vi girano le applicazioni.
## Storia dei sistemi operativi
L'idea risale a **Charles Babbage** (1792-1871) e al suo *motore analitico*, mai completato; **Ada Lovelace** ne scrisse il software (da cui il linguaggio Ada) *(extra, non da slide)*. I SO veri arrivano però con i computer elettronici.
### Prima generazione (1945-55) — valvole termoioniche
Le prime macchine si dividevano per tecnologia costruttiva:
- a **valvole termoioniche**: l'**ENIAC** di Mauchly ed Eckert e il **Colossus**;
- a **relè elettromeccanici**: lo **Z3** di Zuse e il **Mark I**. *(extra, non da slide: l'assegnazione di ENIAC, Colossus e Mark I)*

Il *primo computer digitale funzionante* fu però l'**ABC** di John Atanasoff e Clifford Berry (Iowa State University, 300 valvole). Il **Colossus** fu progettato a Bletchley Park (Inghilterra) per la crittoanalisi del cifrario Lorenz; lo **Z3** di Konrad Zuse fu costruito a Berlino; il **Mark I** da Howard Aiken a Harvard; l'**ENIAC** all'Università della Pennsylvania. Erano macchine lentissime (secondi per operazione), progettate, costruite, programmate e gestite dagli stessi ingegneri, **cablando circuiti** o in linguaggio macchina puro: **nessun sistema operativo, nessun linguaggio di programmazione** (nemmeno l'assembly), con alta manutenzione (soprattutto per sostituire le valvole bruciate). Negli anni '50 arrivano le **schede perforate**, che semplificano l'inserimento dei codici.

> [!info] Il primo «bug» (9 settembre 1947, Harvard Mark II)
> Il computer ha un malfunzionamento; i tecnici trovano una falena incastrata in un relè elettromeccanico, la rimuovono e la incollano sul registro delle attività, annotando ironicamente: *«First actual case of bug being found.»* Il termine *bug* era già usato per indicare i difetti tecnici: la vicenda lo ha reso celebre. Da allora si cercano bug (il *debugging*), anche se oggi sono quasi sempre software.
### Seconda generazione (1955-65) — transistor e sistemi batch
I **transistor** rendono i computer affidabili, consentendone la vendita a grandi enti (università, industrie, governi): ruoli distinti tra progettisti, costruttori, programmatori e operatori. Nascono i **mainframe**, chiusi in sale condizionate e gestiti da operatori professionali. Per eseguire un **job** si scriveva il programma (FORTRAN o assembler), lo si perforava su schede e si attendeva la stampa.

Per ridurre i tempi morti nasce il **sistema batch**: i job vengono raccolti e riversati su nastro magnetico da un computer ausiliario economico (IBM 1401), poi elaborati in blocco dalla macchina principale (IBM 7094), mentre l'output veniva gestito offline.

> [!example] Struttura di un job batch (schede di controllo)
> `$JOB` (tempo max, utente, programmatore) → `$FORTRAN` (carica il compilatore) → *programma sorgente* → `$LOAD` (carica l'eseguibile) → `$RUN` (esegui, con i dati forniti) → `$END`.
>
> **Innovazione**: le schede di controllo automatizzano la compilazione e l'esecuzione dei job, riducendo l'intervento dell'operatore. **Limite**: durante le operazioni di I/O di un job la CPU resta inattiva (la slide si chiede se quel tempo si possa usare per eseguire un altro job). *(slide 2025-2026)* Le schede di controllo sono i precursori dei moderni interpreti via shell o a riga di comando.

> [!question] Domanda tipica d'esame
> - **D:** Che cos'è un sistema batch e qual è il suo limite? **R:** I job vengono raccolti su schede perforate, riversati su nastro da un computer ausiliario (IBM 1401) ed elaborati in blocco dalla macchina principale (IBM 7094); le schede di controllo (`$JOB`, `$FORTRAN`, `$LOAD`, `$RUN`, `$END`) automatizzano compilazione ed esecuzione e riducono l'intervento dell'operatore. **Limite**: durante l'I/O di un job la CPU resta inattiva.
### Terza generazione (1965-80) — circuiti integrati e multiprogrammazione
I **circuiti integrati (IC)** migliorano il rapporto prezzo/prestazioni. Nascono famiglie di computer compatibili e sistemi operativi più sofisticati. IBM unifica le linee scientifica (*word-oriented*, 7094) e commerciale (*character-oriented*, 1401) *(extra, non da slide: la distinzione word/character)* con il **System/360**, prima **famiglia di computer compatibili** con lo stesso set di istruzioni, adatta sia al calcolo scientifico sia a quello commerciale; il successo fu enorme e seguirono i modelli **IBM 370, 4300, 3080, 3090** (i discendenti della serie System/360 sono ancora usati per grandi basi di dati e server, fino alla serie Z *(extra, non da slide: la serie Z)*) *(slide 2025-2026: i modelli e il successo del System/360 non compaiono nelle slide 2026-2027, che lo citano solo come esempio di famiglia compatibile)*. Il suo sistema operativo, **OS/360**, era complesso e universale ma difficile da mantenere, con problemi continui di gestione e aggiornamento; contribuì a diffondere tecniche chiave come la multiprogrammazione. Il modello di «famiglia di computer» fu adottato anche dai concorrenti *(slide 2025-2026: OS/360 e impatto)*. Il **problema** dei sistemi batch è che la CPU resta inutilizzata quando il job in esecuzione attende un'operazione di I/O. Idee chiave introdotte:
- **Multiprogrammazione**: più job sono mantenuti contemporaneamente in memoria (partizionata tra i job); mentre uno attende l'I/O, il sistema operativo assegna la CPU a un altro, evitando che resti inattiva. Obiettivo: migliorare l'utilizzo della CPU. *(slide 2025-2026)* Critico per i carichi commerciali, dove l'attesa I/O è l'80-90% del tempo (per i calcoli scientifici il tempo sprecato è insignificante).
- **Spooling** (*Simultaneous Peripheral Operation On Line*) *(slide 2025-2026)*: i job vengono caricati su disco appena arrivano, senza fermare la macchina.
- **Time-sharing** (condivisione del tempo): nei sistemi batch l'utente deve attendere il completamento del job per ottenere una risposta; nel time-sharing la CPU è assegnata a turno ai diversi programmi e più utenti interagiscono contemporaneamente con il sistema. Obiettivo: garantire tempi di risposta brevi (primo sistema: CTSS del M.I.T. su 7094 *(extra, non da slide)*). *(slide 2025-2026)* Serve protezione hardware per un vero time-sharing. Da qui **MULTICS** (*MULTiplexed Information and Computing Service*, 1965), sistema per il multiplexing e i servizi informatici, uno dei progetti pionieristici del time-sharing, con importanti innovazioni nell'organizzazione dei sistemi operativi *(slide 2025-2026: non ebbe mai veramente successo, ma i suoi principi permangono nel tempo)*; introdusse molte caratteristiche innovative che ritroviamo nei sistemi moderni, ma era anche estremamente complesso. Lo testimonia la citazione di **Tom Van Vleck** (1973): *«I remarked to Dennis that easily half the code I was writing in Multics was error recovery code»*. Antesignano del concetto di *computer utility* e quindi del **cloud** moderno *(extra, non da slide)*.

> [!info] Nascita di UNIX
> Da MULTICS, **Ken Thompson** (Bell Labs, 1969) scrive una versione ridotta e **monoutente** — chiamata inizialmente **UNICS** (*UNiplexed Information and Computing Service*), poi rinominata UNIX — su PDP-7 in assembler, poi evoluta su PDP-11 (1970-1974) e **riscritta in C** da Dennis Ritchie (partendo dal linguaggio B). La terza versione di UNIX è già scritta in C. Nel **1974** viene pubblicato un articolo su UNIX (su *Communications of the ACM* *(extra, non da slide)*); **ACM Turing Award nel 1984**, a Thompson e Ritchie *(extra, non da slide: i destinatari)*. UNIX è un sistema operativo multiutente e con multiprogrammazione, popolare in ambito accademico e aziendale (inizialmente condiviso e libero), ma il proliferare di varianti incompatibili (ramo **System V** e ramo **BSD**) genera frammentazione. Le differenze tra i sistemi rendono difficile sviluppare programmi portabili; per porvi rimedio nasce lo standard **POSIX** (IEEE), che specifica un insieme comune di interfacce e comportamenti del sistema operativo *(slide 2025-2026: nel 1984, come fusione di System V e BSD)*. La **Single UNIX Specification** definisce i requisiti per la compatibilità con lo standard UNIX. Idea chiave: un programma che usa interfacce standard può essere compilato ed eseguito su sistemi diversi, con meno modifiche; molte funzioni C usate nel corso per processi, thread e sincronizzazione sono definite da POSIX. Si aggiungono nel tempo i progetti [[#^stdunix|di standardizzazione]] OSF, X/Open e Open Group. Da UNIX derivano **MINIX** (didattico, micro-kernel, → MINIX 3) e, ispirato a MINIX, **Linux** di Linus Torvalds (1991).

Con il tempo i sistemi UNIX diventano sempre più complessi e studiare il funzionamento interno di un sistema operativo commerciale diventa difficile. *(slide 2025-2026)* Le varianti commerciali più importanti erano basate su **UNIX System V Release 4 (SVR4)**; **Solaris 2.x** (Sun Microsystems) ne è l'implementazione di maggior successo commerciale; questi sistemi erano molto grossi e complicati — al contrario dell'idea originaria di Thompson — e in alcuni casi costosi. Nel **1987** **Andrew Tanenbaum** sviluppa **MINIX**, un piccolo sistema operativo di tipo UNIX scritto a scopo didattico (compatibile con POSIX) e basato sul modello a **micro-kernel**, con molte funzionalità organizzate in componenti separati; permette di studiare concretamente l'organizzazione di un sistema operativo. *(slide 2025-2026)* Circa **11.800 righe di C** e **800 righe di Assembler**. MINIX è poi la principale ispirazione per Linux (vedi messaggio storico di Torvalds del 1991 su comp.os.minix).

> [!info] Il progetto GNU e il software libero
> Al MIT, nei primi anni '80, una stampante Xerox si inceppa spesso: **Richard Stallman** vorrebbe modificarne il software per avvisare gli utenti del blocco, ma non può accedere al codice sorgente, perché non è libero. Nasce la domanda: perché chi usa un programma non dovrebbe poterlo studiare, modificare e condividere?
> - **1983**: Stallman annuncia il progetto **GNU** (*GNU's Not Unix*), con l'obiettivo di costruire un sistema operativo compatibile con UNIX ma interamente libero. *Software libero* non significa necessariamente gratuito: significa libertà di usare, studiare, modificare e ridistribuire il software.
> - Il progetto sviluppa componenti fondamentali: **GCC** (compilatore libero per C e altri linguaggi), **Bash** (shell), **GNU Coreutils** (strumenti di base come `ls`, `cp`, `mv`, `cat`).
> - Manca il kernel: GNU avvia lo sviluppo di **GNU Hurd**, che incontra grandi difficoltà e ritardi. Nel **1991** Linus Torvalds sviluppa indipendentemente il kernel **Linux**.
> - Insieme nasce **GNU/Linux**: GNU aveva molti strumenti ma non un kernel pronto; Linux aveva un kernel, ma gli servivano strumenti e applicazioni. Da allora **Linux (e Android)** hanno prosperato, soprattutto in ambienti **server** e **mobile** (la slide mostra il grafico delle vendite mondiali di smartphone dal 2007).

> [!info] Progetti di standardizzazione UNIX *(slide 2025-2026)* ^stdunix
> Alla frammentazione System V / BSD rispondono diversi enti:
> - **POSIX** (IEEE, 1984): standard di interfaccia unificata.
> - **OSF** (*Open Software Foundation*, 1988): consorzio IBM, DEC, Hewlett-Packard; produce **OSF/1**.
> - **X/Open** (1993): definisce la **Single UNIX Specification**; i sistemi conformi ottengono il marchio **UNIX 95**.
> - **Open Group** (1996, fusione OSF + X/Open): emana la seconda versione della Single UNIX Specification (1997) con marchio **UNIX 98**.

> [!info] MINIX 3 e Intel Management Engine
> **MINIX 3** (Vrije Universiteit Amsterdam) è stato adottato da **Intel** per il suo **Management Engine (ME)**, il sottosistema di gestione integrato nei processori moderni. *(slide 2025-2026)* È quindi presente in desktop, server e laptop x86 *(extra, non da slide: «quasi tutti» e «uno dei SO più diffusi al mondo»)*, pur restando invisibile all'utente finale. *(slide 2026-2027)* Versioni derivate da MINIX 3 sono state impiegate nel firmware di alcuni Intel Management Engine: sottosistemi che operano indipendentemente dal sistema operativo principale. Non tutti i sistemi operativi sono visibili all'utente: alcuni sono usati all'interno di dispositivi o sottosistemi dedicati, per gestire specifiche funzionalità hardware. La licenza è della Vrije Universiteit Amsterdam (copyright 1987, 1997, 2006).

> [!info] Albero genealogico delle varianti UNIX *(approfondimento)*
> Il diagramma delle slide (*A Success Story*) mostra tre rami principali:
> - **BSD** (Berkeley Software Distribution): da Unix V5/V6 → BSD 1.x-4.3 → FreeBSD, NetBSD, OpenBSD, DragonFly BSD → **macOS** (via NeXTSTEP/OPENSTEP e il kernel Darwin, basato su Mach + BSD).
> - **System V**: Unix/32V → System III → System V R1–R4 → **Solaris** (Sun/Oracle), HP-UX, AIX, UnixWare, SCO.
> - **Linux** (1991): nasce ispirato a MINIX, ma indipendente; evolve in parallelo, con Android come suo principale discendente mobile *(extra, non da slide: Android non compare nel diagramma; la slide successiva lo cita insieme a Linux)*.
> Le varianti a sorgente aperto (verdi nel diagramma) convivono con quelle proprietarie (rosse: HP-UX, AIX, Solaris). macOS è derivato da BSD/NeXTSTEP ed è quindi UNIX-based.

> [!question] Domanda tipica d'esame
> - **D:** Differenza tra multiprogrammazione e time-sharing. **R:** **Multiprogrammazione**: più job sono contemporaneamente in memoria e, quando uno attende l'I/O, il SO assegna la CPU a un altro; obiettivo: migliorare l'utilizzo della CPU. Nei sistemi batch però l'utente attende comunque la fine del job. **Time-sharing**: la CPU è assegnata a turno ai diversi programmi e più utenti interagiscono contemporaneamente con il sistema; obiettivo: tempi di risposta brevi (MULTICS fu uno dei progetti pionieristici).
### Quarta generazione (1980-oggi) — personal computer
I circuiti **LSI** (migliaia di transistor per cm²) rendono possibile il PC. Intel rilascia l'**8080** (1974 *(extra, non da slide)*): **Gary Kildall** scrive per esso il sistema operativo **CP/M** e fonda **Digital Research**, che lo adatta ai microcomputer. Quando negli anni '80 IBM cerca un SO per il suo PC, **Kildall rifiuta l'incontro** con IBM — un'occasione mancata storica; così **Microsoft** acquista il DOS da Seattle Computer Products e lo adatta a **MS-DOS**, dominando il mercato dei PC IBM.

La **GUI** — inventata da **Engelbart** e sviluppata allo **Xerox PARC** — viene colta da **Steve Jobs**: nasce l'**Apple Macintosh**, user-friendly e di successo. Microsoft risponde con **Windows**, inizialmente ambiente grafico sopra MS-DOS, poi sistema autonomo: **Windows 2000** e i successori consolidano la posizione di Microsoft; **Vista** e **Windows 8** incontrano resistenza, mentre **Windows 10** ha successo (la sequenza 95 → XP → 7 è *(extra, non da slide)*). La linea professionale **Windows NT** fu invece fortemente influenzata dall'architettura del **VMS** di **DEC** (i minicomputer VAX) — una parentela che sfociò poi in una controversia legale con DEC. Apple consolida il proprio sistema operativo basato su UNIX ma *architecture-specific*, con un kernel derivato dal microkernel **Mach** su base **BSD UNIX** *(extra, non da slide: Mach)*: **macOS** è quindi un sistema UNIX-based.
### Quinta generazione (1990-oggi) — computer mobili
Dai primi telefoni portatili ("il mattone") agli **smartphone** (Nokia N9000, 1996; termine coniato da Ericsson nel 1997) *(extra, non da slide: tutta la frase)*. Oggi il mercato è dominato da **Android** (Google, basato su Linux) e **iOS** (Apple), dopo una fase iniziale di **Symbian OS** (il grafico sulle vendite di smartphone, slide 2 p. 30, mostra Android in forte crescita, iOS secondo, Symbian, BlackBerry e Windows marginali).
## Analisi dell'hardware
Il SO è intimamente legato all'hardware su cui gira e deve conoscerlo a fondo.
### Processori (CPU)
La CPU esegue il **ciclo fetch-decode-execute**: preleva l'istruzione, la decodifica, la esegue, ripete. Ogni CPU ha un proprio **instruction set (ISA)**: un binario x86 non gira su ARM e viceversa. *(extra, non da slide)*

Contiene **registri** interni per dati e risultati temporanei, tra cui:
- **Program Counter (PC)**: indirizzo della prossima istruzione.
- **Stack Pointer (SP)**: cima dello stack (frame di procedura, parametri, variabili locali).
- **PSW (Program Status Word)**: contiene informazioni sullo stato del programma (bit di condizione, bit di modalità kernel/user, priorità *(extra, non da slide: elenco dei campi)*); è fondamentale per le chiamate di sistema e l'I/O.

Più programmi possono usare la stessa CPU grazie al **multiplexing temporale**: la CPU esegue un programma per un certo intervallo, poi il sistema operativo può sospenderlo e assegnarla a un altro, conservandone lo stato per poterlo riprendere. Il **cambio di contesto** ([[03 - Processi e Thread|context switch]]) salva lo stato del programma corrente (registri, program counter, ecc.) e ripristina quello del successivo: più programmi condividono una CPU dando l'impressione di avanzare contemporaneamente. Tecniche hardware per le prestazioni:
- **Pipeline**: gli stadi (fetch/decode/execute) di istruzioni successive si sovrappongono, aumentando il throughput; le progettazioni avanzate come la pipeline non sono del tutto trasparenti al sistema operativo.
- **Multithreading hardware (SMT / Hyper-Threading)**: un singolo core mantiene lo stato di più thread hardware, che condividono le risorse di esecuzione del core; **non** c'è esecuzione parallela vera e propria (slide 2025-2026). Il SO vede più **processori logici**, che non equivalgono a più core fisici, e ne deve tenere conto. *(extra, non da slide: la commutazione rapida quando un thread si blocca)*
- **Multicore**: più core reali sullo stesso chip. La cache L2 può seguire due topologie: **(a)** condivisa tra tutti i core (un unico blocco di L2 sul chip, accesso uniforme) oppure **(b)** privata per ogni core (ciascun core ha la propria L2 locale). In entrambi i casi la cache L1 resta privata per core.
- **GPU**: processori specializzati nell'esecuzione parallela di molte operazioni *(extra, non da slide: migliaia di core semplici, SIMD, uso per calcolo generico GPGPU)*.
- **Multiprocessori e multicore**: più processori o core fisici permettono una **reale esecuzione parallela**. Tre vantaggi: **throughput** (più lavoro svolto in parallelo), **economia di scala** e **affidabilità**. *(extra, non da slide: la spiegazione dei tre vantaggi — le CPU condividono alimentazione, contenitore e periferiche, costando meno di tante macchine separate; il guasto di una CPU degrada le prestazioni ma non ferma il sistema)*

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> Il funzionamento dettagliato della CPU (ciclo fetch-decode-execute, registri, microarchitettura, pipeline) è trattato nel corso del primo anno: [[02 - Organizzazione dei sistemi di calcolo]] e [[04 - Livello di microarchitettura]].
### Memoria
La memoria è organizzata in una **gerarchia**, con trade-off tra velocità, capacità e costo:

| Livello | Tempo di accesso | Capacità | Volatile |
|---|---|---|---|
| Registri | < 1 ns | < 1 KB | sì |
| Cache (L1/L2/L3) | 1–8 ns | 4–8 MB | sì |
| Memoria centrale (RAM) | 10–50 ns | 16–64 GB | sì |
| Disco magnetico / SSD | 10 ms / da decine a centinaia di µs | 2–16+ TB | no |

I valori sono quelli della figura della slide (*A typical memory hierarchy*, slide 2 p. 38: «The numbers are very rough approximations»); per il livello disco/SSD la figura indica anche una *optional persistent memory*. *(extra, non da slide: la colonna «Volatile» e il dettaglio L1/L2/L3)* Le memorie più veloci sono generalmente meno capienti: il caching mantiene temporaneamente i dati più utili vicino alla CPU.

Le **cache** nascondono la latenza della RAM scommettendo su due principi di **località**: **temporale** (un dato usato di recente sarà probabilmente riusato a breve) e **spaziale** (accedendo a un dato, è probabile accedere a quelli a esso vicini). Su questi due principi si fonda l'efficacia di qualsiasi cache. *(extra, non da slide: i due principi di località)*

> [!info] I quattro problemi di gestione di una cache
> Qualsiasi sistema di cache (non solo quella della CPU) deve risolvere quattro domande, che ritroveremo identiche negli [[06 - Gestione della Memoria#Algoritmi di sostituzione delle pagine|algoritmi di sostituzione delle pagine]] e nella [[07 - File System#Block cache (buffer cache)|block cache]]:
> 1. **Quando** inserire un nuovo elemento nella cache?
> 2. **In quale riga** della cache inserirlo?
> 3. **Quale elemento rimuovere** quando serve liberare uno slot?
> 4. **Dove** mettere nella memoria più grande l'elemento appena rimosso?

La **MMU (Memory Management Unit)** traduce gli indirizzi **virtuali** in **fisici**, abilita la [[06 - Gestione della Memoria|memoria virtuale]] e protegge lo spazio di indirizzi di ogni processo. Per non rifare ogni volta la stessa traduzione, si appoggia al **TLB (Translation Lookaside Buffer)**: una piccola cache che conserva le traduzioni indirizzo→pagina più recenti, così la MMU le riusa invece di ricalcolarle (approfondito in [[06 - Gestione della Memoria]]). *(extra, non da slide 2: la MMU compare solo nella figura dell'architettura, slide 2 p. 33, tra CPU e bus; funzione della MMU e TLB sono trattati nelle slide sulla memoria)*
### Dischi e memoria di massa
- **HDD (Hard Disk Drive)**: piatti magnetici rotanti, testine su braccio mobile. Tempo di accesso = *seek time* + *rotational delay* + *transfer time*. Organizzazione in tracce, settori, cilindri. *(extra, non da slide)* Nella figura della slide (slide 2 p. 40): più piatti con otto superfici (0-7), una testina di lettura/scrittura per superficie, spostate insieme dal braccio.
- **SSD (Solid State Drive)**: spesso (erroneamente) indicato anche come «disco»; dati in memoria elettronica (flash), nessuna parte mobile, molto più veloce dei dischi magnetici (negli accessi casuali *(extra, non da slide)*; memoria NAND *(extra, non da slide)*); richiede **wear leveling** *(extra, non da slide)*.
### Dispositivi di I/O
Ogni dispositivo ha due parti: un **controller** (interfaccia con registri di controllo/stato, semplice da pilotare per il SO) e il **dispositivo fisico**. Il **driver** (in kernel mode) traduce le richieste del SO in comandi per il controller, accedendo ai suoi registri tramite **porte di I/O dedicate** (istruzioni di tipo `IN`/`OUT`) o **memoria mappata** (PMIO/MMIO, approfonditi in [[08 - Input Output]]). Il dispositivo fisico ha un'interfaccia elementare ma complicata da pilotare (esempio: i dischi SATA). Per eseguire un'operazione di I/O il processo effettua una chiamata di sistema, il kernel invoca il driver del dispositivo e il driver programma il controller e avvia l'operazione. Per verificarne il completamento, tre modi di gestire un trasferimento:
- **Polling** (*busy waiting*): il sistema controlla periodicamente lo stato del dispositivo (la CPU interroga di continuo e spreca cicli: *(extra, non da slide)*).
- **Interrupt-driven**: il dispositivo genera un **interrupt** quando è pronto — efficiente (ripreso in [[08 - Input Output]]).
- **DMA (Direct Memory Access)**: un controller trasferisce i dati direttamente da/verso la memoria senza impegnare la CPU — ottimale per grandi quantità. È un meccanismo hardware, oggi normalmente implementato nei controller dei dispositivi o in appositi engine DMA: la CPU configura il trasferimento (indirizzi, direzione, quantità di dati), il controller trasferisce i blocchi direttamente tra dispositivo e memoria mentre la CPU svolge altre attività, e al completamento la CPU è normalmente notificata con un interrupt. *(slide 2025-2026)* La slide lo definiva «dispositivo hardware speciale».

> [!question] Domanda tipica d'esame
> - **D:** Come avviene un'operazione di I/O e come si verifica il completamento? **R:** Il processo effettua una chiamata di sistema, il kernel invoca il driver del dispositivo e il driver programma il **controller** e avvia l'operazione. Il completamento si verifica con **polling** (il sistema controlla periodicamente lo stato del dispositivo) o con **interrupt** (il controller segnala il completamento alla CPU); con il **DMA** il controller trasferisce i dati direttamente tra dispositivo e memoria, senza che la CPU copi ogni dato, e la CPU è notificata con un interrupt alla fine.
### Architettura dei bus (x86)
Un sistema x86 moderno ha **più bus** con funzioni e velocità diverse:
- **DDR4**: bus veloce tra CPU e **memoria** centrale.
- **PCIe** (*Peripheral Component Interconnect Express*): il bus principale e più veloce, usa connessioni **punto-punto dedicate** (più efficienti dei bus condivisi), tipicamente per la **GPU**.
- **DMI** (*Direct Media Interface*): collega la CPU a un **hub** che raccoglie tutti gli altri dispositivi; i dispositivi **legacy** possono essere collegati a un **processore hub separato** (slide 2026-2027). Nella figura (slide 2 pp. 44-45) la CPU (core con cache, cache condivisa, GPU core, controller di memoria) è collegata a due banchi di memoria DDR4 e, via PCIe, alla scheda grafica; via DMI al **Platform Controller Hub**, che serve slot PCIe, SATA, porte USB 3.2 e USB 4, Gigabit Ethernet e altri dispositivi PCIe.
- **USB** (*Universal Serial Bus*): nato per i dispositivi **lenti**, oggi raggiunge fino a **40 Gbps**; connettore a **4–11 conduttori** (alimentazione + dati); è **hot-pluggable** (collegamento immediato senza riavvio).
### Sequenza di avvio (BIOS/UEFI)
All'accensione il firmware (**BIOS/UEFI**) esegue il **boot**. Nei sistemi moderni il firmware della scheda madre è normalmente **UEFI**; i sistemi più vecchi usavano il meccanismo *legacy* **BIOS/MBR**. *(slide 2026-2027)* Sequenza:
1. la CPU inizia l'esecuzione del firmware;
2. il firmware inizializza memoria e dispositivi hardware;
3. individua il dispositivo da cui effettuare il boot e consulta le informazioni di boot memorizzate dal firmware;
4. carica dalla **EFI System Partition** il boot manager / bootloader;
5. il bootloader carica in memoria il kernel del sistema operativo;
6. il kernel inizializza le proprie strutture dati, i driver e i servizi necessari;
7. infine viene avviato il sistema operativo.

> [!example] Sequenza di avvio del BIOS *(slide 2025-2026)*
> 1. La **memoria flash** della scheda madre contiene il firmware (BIOS); premuto il pulsante di accensione, la CPU **esegue il BIOS**.
> 2. Il BIOS **inizializza la RAM** e le altre risorse, esegue la **scansione dei bus PCI/PCIe** e inizializza i dispositivi, imposta il **firmware runtime** per i servizi critici (es. I/O a basso livello).
> 3. Cerca la **tabella delle partizioni** sul **secondo settore** del dispositivo di avvio (contiene le posizioni delle altre partizioni).
> 4. Sa leggere **file system semplici** (es. **FAT-32**) e carica il **primo bootloader** dalla partizione indicata dal boot manager; il bootloader può caricarne altri a catena.
> 5. Alla fine viene caricato il **sistema operativo**.
>
> *(extra, non da slide: GPT, Secure Boot, limite di 2,2 TB)* UEFI (alternativa moderna al BIOS) usa la tabella partizioni **GPT**, supporta Secure Boot e supera il limite di 2,2 TB; la GPT è trattata in [[07 - File System#Layout del file system|File System]].

> [!question] Domanda tipica d'esame
> - **D:** Descrivi la sequenza di avvio di un calcolatore moderno. **R:** La CPU inizia a eseguire il **firmware** (nei sistemi moderni UEFI; nei più vecchi BIOS/MBR); il firmware inizializza memoria e dispositivi, individua il dispositivo di boot e ne consulta le informazioni; carica dalla **EFI System Partition** il boot manager/bootloader; il bootloader carica in memoria il **kernel**; il kernel inizializza strutture dati, driver e servizi; infine parte il sistema operativo.
## Panoramica dei sistemi operativi (lo "zoo")
Le slide (SOR 3, pp. 3-6) classificano i sistemi operativi secondo il contesto d'uso (è la stessa «fauna» di sistemi operativi presentata dal Tanenbaum, cap. 1):
- **Mainframe**: computer di grandi dimensioni usati in grandi aziende e istituzioni. Funzioni principali: *batch processing* (lavori senza interazione dell'utente, es. elaborazione reclami), *elaborazione di transazioni* (numerose richieste simultanee, es. prenotazioni aeree), *timesharing* (molti utenti eseguono lavori contemporaneamente, es. interrogazioni a database). Es. **z/OS** (successore di OS/360), per applicazioni mission-critical (banche, e-commerce).
- **Server**: servono più utenti attraverso la rete, con servizi di file sharing, database, stampa, hosting web; usati da provider di servizi internet e aziende per infrastrutture critiche. Es. Linux, FreeBSD, Windows Server, Solaris.
- **Multiprocessore**: gestiscono più CPU/core per maggiore potenza *(extra, non da slide: nella slide l'elenco numerato salta la voce 5)*.
- **Personal computer**: supportano un singolo utente con multiprogrammazione e, spesso, architetture multiprocessore; compiti quotidiani (videoscrittura, navigazione web, fogli di calcolo); facilità d'uso, interfaccia grafica, supporto per applicazioni di produttività. Es. Windows, macOS, Linux, FreeBSD.
- **Smartphone e tablet**: mercato dominato da **Android** (Google) e **iOS** (Apple); supportano CPU multicore, GPS, fotocamere e numerose app di terze parti (oltre 3 milioni su Google Play Store).
- **IoT ed embedded**: dispositivi connessi (es. frigoriferi, lavatrici, telecamere di sicurezza), tipicamente leggeri, con funzioni specifiche e limitate; footprint ridotto (es. **RIOT** può girare su meno di 10 KB). Es. Embedded Linux, QNX, TinyOS. Altri esempi di dispositivi (TV, schede come Arduino ed ESP32) *(extra, non da slide)*. ^embedded
- **Real-time**: progettati per rispettare **scadenze rigide** nei processi industriali e militari. **Hard real-time**: risposte immediate e precise (es. robotica industriale); **soft real-time**: occasionali ritardi tollerabili (es. streaming multimediale). Es. eCos, VxWorks.
- **Smart card**: usati in smart card per pagamenti, autenticazioni e altro, alimentate tramite contatti o induzione, con capacità limitate. *Java-oriented*: alcune eseguono applet Java per la multiprogrammazione. Es. sistemi proprietari, **JavaCard** per applet multiprogrammate.

> [!info] Cosa hanno in comune
> Indipendentemente dalla categoria, tutti i SO gestiscono le risorse hardware e offrono astrazioni ai programmi (**macchina estesa** e **gestore delle risorse**, vedi sopra), **ma** le diverse categorie privilegiano obiettivi differenti: throughput, interattività, consumi, affidabilità o rispetto delle scadenze temporali (slide SOR 3 p. 6).

---

**Prossimo argomento:** [[02 - Concetti di Base e Strutture]] — system call, l'astrazione di processo e file, e le strutture interne del sistema operativo.
