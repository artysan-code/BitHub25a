## Lezione II
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
- L'idea di **astrazione**: il sistema operativo si pone tra hardware e software utente gestendo autonomamente ogni risorsa.
- Visione **top-down**: il sistema operativo fornisce astrazioni ai programmi applicativi.
- Visione **bottom-up**: il sistema operativo fornisce un’allocazione ordinata e controllata di processori, memorie e unità I/O ai vari programmi che li richiedono.

Il sistema operativo deve poter:
- Un'organizzazione ordinata e controllata delle risorse.
- Astrazione dei concetti (non più hardware, ma file, database, etc...).
- **Multiplexing** nel tempo e spazio della CPU, che corrisponde alla gestione di molteplici richieste da parte di utenti per diverse operazioni.
#### Storia dei Sistemi Operativi (Non rivisto sul libro)
##### Prima generazione - Vacuum tubes
Sviluppo storico:
- John Atanasoff / clifford Berry:
	- Costruirono il primo computer digitale a 300 valvole alla Iowa State University
- Colossus: progettato da Bletchley Park, inghilterra.
- Mark I: Howard Aiken ad Harvard.
- ENIAC: Pennsylvenya.

Tecnologie estremamente lente e specifiche, nessun sistema operativo. Nessun linguaggio di programmazione, con alta manutenzione sia hardware che software.

La prima volta fu la creazione delle **schede perforate**, per trattenere informazioni.
##### Seconda Generazione - Transistors and batch systems
Negli anni '50 nacquero nuove invenzioni e concetti:
- Grazie ai **transistor** i computer diventano affidabili per grandi enti.
	- Nasce un'organizzazione interna: progettisti, costruttori, programmatori e operatori.
	- **Mainframe**: grandi macchine, chiuse in sale condizionate e gestite da personale professionale.
- Introduzione del **Sistema Batch**.
	- Step by step
		- Prima bisogna trascrivere i dati su nastro magnetico o inserire il nastro magnetico.
		- Dopodiché viene calcolato e fornito l'output fisico.
- Funzionamento:
	- Job raccolti su schede perforate e trasferiti su nastri magnetici con un computer ausiliario.
	- **Macchina principale**, usata per il calcolo mentre l'output era gestito offline.

Quando l'I/O diventa troppo lento, si inizio a cercare di impegnare l'hardware negli intervalli di attesa (Concetto che ritroveremo dopo, pipeline).
##### Terza Generazione - ICs and multiprogramming
Come si programmava:
- **SJOB**: specifica il numero massimo di esecuzione, numero utente e nome del programmatore.
- **FORTRAN**: Carica il compilatore FORTRAN
- **Programma**: Codice sorgente da compilare.
- **LOAD**: Carica il programma compilato.
- **RUN**: Esegue il programma

- **Innovazioni tecnologiche**:
	- Introduzione ai circuiti integrati (**IC**), miglior rapporto prezzo/prestazioni.
	- Introduzione alla **multiprogrammazione**, per far lavorare continuamente la cpu.
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

- Problema delle architetture batch: CPU inattiva per calcoli scientifici o per dati commerciali.
- Memoria partizionata per job multipli
	- **Spooling** (Simultaneous peripheral operation on line) per caricare nuovi job senza interruzioni.
- Problema di inserimento job, tempi troppo lunghi per inserimento job e output
	- **Time Sharing**, per risposta rapida. La CPU veniva assegnata a job utenti attivi. (Multics, troppo complesso).
	- Protezione hardware necessaria 
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
- Diversi sistemi di standardizzazione
	- POSIX
	- VIBM
- Varianti del sistema UNIX
	- MINIX, piccolo sistema UNIX compatibile con standard POSIX e fatto in C e Assembler.
		- Basato sul micro-kernel a scopo didattico
		- Ancora usato nei processori moderni.
- Nascita da MINIX di Linux.
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

#### Sguardo all'Hardware
Un'architettura semplificata di un calcolatore è formata da:
- CPU con MMU
- Memoria principale
- Video controller o scheda integrata
	- Con monitor
- Keyboard controller
	- Con tastiera
- USB controller
	- USB devices
- Hard Disk controller
	- Hard disk drive
- Tutti collegati da un bus

Tutte le informazioni vengono trovate ad[[2 - Organizzazione dei sistemi di calcolo#^4bb1a1| Architettura Capitolo II]].

#### Avvio del sistema (BOOT)
- La memoria flash della scheda madre contiene il firmware (BIOS)
- la CPU esegue il BIOS
	- Inizializza la RAM e le risorse
	- Esegue la scansione PCI/PCIe e inizializza i dispositivi
	- Imposta firmware runtime per servizi critici che devono essere usati.
- Il BIOS cerca nella tabella delle partizioni la posizione sul secondo settore di dispositivo di avvio.
- Può leggere semplici filesystem (Tipo FAT-32) e avvia il bootloader.
	- Il bootloader può caricare altri programmi di bootloading.
- Viene caricato il sistema operativo.

(Fino a 1.3)
## Lezione III
#### Sistemi Operativi
- **Sistemi Operativi per Mainframe**
- **Sistemi Operativi per Server**
- **Sistemi Operativi per Personal Computer**
- **Sistemi Operativi per Smartphone**
- **Sistemi Operativi per IoT e Embedded**
- **Sistemi Operativi Real-Time**
- **Sistemi Operativi per Smart Card**
Cosa hanno in comune?
- Extended Machine
	- Estensione delle funzionalità hardware
	- Astrazione Hardware
	- Nascondere i dettagli al programmatore
- Resource Manager
	- Proteggere l'uso simultaneo delle risorse
	- Condivisione equa delle risorse
	- Resource accounting/limiting
#### Concetti base di un sistema operativo
Il sistema operativo offre funzionalità, chiamate **servizi**, attraverso chiamate di sistema. Esempi di servizi sono il **File System Service** e **Process Management Service**.
##### L'astrazione del Processo
I **processi** sono astrazioni a livello utente per poter eseguire un programma per conto di un utente. Ogni processo ha il proprio spazio di indirizzamento e i dati usati nell'elaborazione vengono recuperati e salvati in file.

I file persistono rispetto ai processi.

Il programma in esecuzione è un processo a cui è associato:
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

Ogni layout dipende dal **sistema operativo**, **l'architettura della macchina** e 

I processi vengono salvati in una **tabella dei processi** del sistema operativo, un processo sospeso consiste in una voce di questa tabella e del suo spazio degli indirizzi.

Ogni processo può essere **creato**, **terminato**, **messo in pausa** e **rieseguito**. Ogni processo può creare un altro **processo figlio** (crea una gerarchia di processi).

Ogni processo è di proprietà di un **utente** identificato da un UID (condiviso generalmente anche dal processo). Su UNIX un processo figlio ha lo stesso UID del processo padre ad esempio. Gli utenti possono essere membri di un gruppo identificato da un GUID.

Un processo **root/superuser/administrator** è speciale ed ha più permessi.
##### L'astrazione del File
Il file è un'astrazione di un dispositivo di memorizzazione reale (ad esempio un disco). Possiamo leggere e scrivere dati da/su un file fornendo una posizione e la quantità di dati da trasferire.

I file sono contenuti e organizzati in **directory** che ha un suo identificatore (la directory è un file), da cui la filosofia UNIX "everything is a file".

Le directory formano con i file una gerarchia, alla base abbiamo la **radice (root)** che ci permette di accedere ai file tramite il **percorso assoluto (absolute path)**. Esistono però anche dei **percorsi relativi (relative path)** che dipendono dalla directory di lavoro.

Altri file system possono essere montati da **mount** nella root: `/mnt/windows`.

###### Diritti di accesso