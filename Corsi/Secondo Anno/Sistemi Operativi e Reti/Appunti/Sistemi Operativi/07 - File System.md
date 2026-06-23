# File System
Tutti i programmi devono **memorizzare e recuperare informazioni**. Mentre un processo è in esecuzione può tenere i suoi dati nel proprio spazio di indirizzi, ma questo spazio ha tre limiti fondamentali che il file system risolve.
## Perché servono i file
La memoria di lavoro (RAM) da sola non basta come supporto per le informazioni a lungo termine.
> [!warning] I tre limiti della sola RAM
> - **Capacità limitata**: la [[06 - Gestione della Memoria|RAM fisica]] è piccola; molte applicazioni richiedono molto più spazio (anche terabyte).
> - **Perdita dei dati (volatilità)**: le informazioni in RAM si perdono al termine del [[03 - Processi e Thread|processo]] o in caso di crash/blackout.
> - **Accesso concorrente**: più processi devono poter accedere alle stesse informazioni *simultaneamente*; tenerle nello spazio di indirizzi di un singolo processo lo impedisce.

Da qui i tre **requisiti per la memorizzazione a lungo termine**: salvare grandi quantità di dati, **persistenza** oltre la vita del processo, **accessibilità** condivisa da più processi. La soluzione hardware sono **dischi magnetici e SSD** (operazioni essenziali: leggere/scrivere blocchi); la soluzione concettuale è l'astrazione **file**.
> [!quote] Definizione — File system
> Un **file system** è il modo in cui il sistema operativo **organizza e memorizza in modo persistente** le informazioni su un dispositivo, fornendo un'**astrazione** sui dispositivi di memorizzazione (disco, SSD, rete, RAM, …). I dati sono organizzati in **file** e (tipicamente) **directory**. Il file system gestisce **struttura, denominazione, accesso, protezione e implementazione** dei file.

Esempi di file system reali: **FAT12/FAT16** (MS-DOS), **NTFS** (Windows), **Ext4** (Linux), **APFS** (macOS/iOS). Distinguiamo sempre due punti di vista: l'**interfaccia utente** (nomi dei file, operazioni consentite) e l'**implementazione tecnica** (gestione della memoria, struttura interna), rilevante per i progettisti del sistema.
## Come si vede un disco e dove sta il file system
A basso livello un disco è una **sequenza lineare di blocchi di dimensione fissa** che supporta due sole operazioni: *leggere il blocco k* e *scrivere il blocco k*. Da questa visione povera nascono subito le domande che il file system deve risolvere: «come si trovano le informazioni?», «come si impedisce a un utente di leggere i dati di un altro?», «come si sa quali blocchi sono liberi?».
> [!info] Roadmap — dove operano queste lezioni
> Tra il programma utente e lo storage il SO impila più livelli:
> - **Syscall** (`open`, `read`, `write`, `readdir`, …) ← interfaccia del programma utente.
> - **Virtual File System (VFS)** ← strato comune che unifica i file system reali (vedi [[#File System virtuali VFS]]).
> - **Page cache** + driver specifici (FAT, NTFS, Ext4, …).
> - **Buffer cache** ← blocchi del disco tenuti in RAM (vedi [[#Performance del file system]]).
> - **Storage** (HDD, SSD, rete, RAM).
>
> Le **lezioni sul File System** coprono dal VFS ai driver; le **lezioni su I/O** coprono lo strato dello storage fisico ([[08 - Input Output]]).
# I file
Il file è il mattone dell'astrazione: serve a salvare e leggere informazioni su disco **nascondendo i dettagli tecnici** all'utente.
## Nomi dei file
I file sono identificati da **nomi**, le cui regole dipendono dal sistema operativo.
- **Lunghezza e «sensibilità»**: alcuni sistemi limitano la lunghezza (es. 8 lettere in MS-DOS), altri ammettono nomi lunghi. ^naming
- **Caratteri speciali vietati**: variano per file system — FAT12 vieta `* | < > ? \` e altri (inclusi caratteri di controllo); Ext4 vieta il carattere **NUL** (`\0`, 0x00) e i nomi speciali `.` e `..`. Il carattere `/` non è un vincolo specifico di Ext4: è il **separatore di percorso** del kernel UNIX, quindi è impossibile in qualsiasi nome di file su qualunque file system UNIX.
- **Case sensitivity**: cosa significa? È la distinzione tra maiuscole e minuscole. I sistemi **UNIX** distinguono (`File.txt` ≠ `file.txt`), **MS-DOS** no. ^case
- **Evoluzione**: vari file system (FAT-16, FAT-32, NTFS) differiscono per costruzione dei nomi e supporto **Unicode**.
### Estensioni
Cos'è un'**estensione**? È la parte del nome che segue un punto e indica una caratteristica del file (es. `.jpg` per immagini JPEG, `.mp3` per audio MPEG layer 3). ^estensione
> [!info] Ruolo delle estensioni — convenzione vs vincolo
> - In **UNIX** le estensioni sono **puramente convenzionali**: il SO non le impone, il significato dei dati lo decidono i programmi utente.
> - In **Windows** le estensioni sono **registrate nel sistema** e associate a programmi specifici, che si avviano interagendo col file (es. `.docx` → Microsoft Word).

Estensioni tipiche: `.bak` (backup), `.c` (sorgente C), `.gif`/`.jpg` (immagini), `.html` (ipertesto web), `.mp3`/`.mpg` (audio/video MPEG), `.o` (file oggetto non ancora linkato), `.pdf`, `.ps` (PostScript), `.tex` (input TeX), `.txt` (testo), `.zip` (archivio compresso).
## Struttura interna dei file
Il SO può vedere il contenuto del file in tre modi diversi.
> [!example] Tre tipologie di struttura
> - **(a) Sequenza non strutturata di byte**: il SO vede solo una serie di byte; il **significato lo danno i programmi utente**. Massima flessibilità — è l'approccio di **UNIX, Linux, macOS e Windows**.
> - **(b) Sequenza di record a lunghezza fissa**: il file è una sequenza di record con struttura interna definita; lettura/scrittura a *unità di record*. Modello storico delle schede perforate a 80 colonne nei mainframe.
> - **(c) Albero di record**: record a lunghezza variabile con un **campo chiave** in posizione fissa, organizzati ad albero per ricerche rapide per chiave. Usato in mainframe per elaborazioni commerciali.
### Tipi di file
- **File normali**: contengono informazioni utente, la forma più comune.
- **Directory**: file di sistema che mantengono la struttura del file system (vedi [[#Le directory]]).
- **File speciali a caratteri**: modellano dispositivi seriali di I/O (terminali, stampanti).
- **File speciali a blocchi**: modellano i dischi.

Tra i file normali si distinguono **file ASCII** (righe di testo stampabili; variano per il carattere di fine riga) e **file binari** (non leggibili come testo, struttura interna nota ai programmi: eseguibili, archivi).
> [!example] Strutture interne di file binari
> - **File eseguibile** (prime versioni di UNIX): inizia con un'**intestazione (header)** contenente un *numero magico* che identifica il file come eseguibile, le dimensioni di testo/dati/BSS, la dimensione della tabella dei simboli, il **punto d'ingresso** e i flag; seguono **testo e dati** (caricati e rilocati in memoria), i **bit di riposizionamento** e la **tabella dei simboli** (per il debug). Il numero magico evita di eseguire file «non eseguibili».
> - **File di archivio**: raccolta di procedure di libreria (moduli) compilate ma non collegate; ogni modulo ha un'intestazione con nome, data, proprietario, codice di protezione e dimensione.

Come si riconosce il tipo di un file? Alcuni sistemi (il vecchio **TOPS-20**) avevano meccanismi complessi di file *tipizzati*, che però limitavano l'uso dei file. In UNIX l'utility `file` usa **euristiche** sul contenuto per determinare il tipo (testo, directory, eseguibile, …).
## Accesso ai file
Come si specifica *quale* parte del file leggere?
> [!quote] Definizione — Accesso sequenziale vs casuale
> - **Accesso sequenziale**: lettura dei file dall'inizio alla fine, nell'ordine. Unico metodo dei primi SO, adatto ai nastri magnetici.
> - **Accesso casuale (random)**: introdotto con i dischi, permette di leggere byte/record in qualsiasi ordine. Cruciale per applicazioni come i **database**, che devono raggiungere un record specifico senza attraversare l'intero file.

La posizione di lettura si fissa con l'operazione **`seek`**, dopo la quale si può leggere sequenzialmente dalla nuova posizione. Adottato sia in UNIX sia in Windows.
## Attributi dei file
Oltre a nome e dati, ogni file ha **attributi** (o *metadati*), variabili per SO.
> [!info] Categorie di attributi comuni
> - **Protezione e accesso**: chi può accedere e come (proprietario, creatore, password).
> - **Flag**: sola lettura, nascosto, di sistema, di archivio (da backup), ASCII/binario, accesso casuale/sequenziale, temporaneo, bloccato.
> - **Attributi temporali**: data/ora di creazione, ultimo accesso, ultima modifica.
> - **Dimensione**: attuale e massima.
> - **Gestione dei record** (per file basati su record): lunghezza del record, posizione e lunghezza della chiave.

Gli attributi sono cruciali per la **protezione**, il controllo dell'accesso e la gestione efficace dei file.
## Operazioni sui file
Le chiamate di sistema tipiche su file sono:
1. **Create** — crea un file senza dati, per «annunciarne» la presenza e impostare attributi.
2. **Delete** — elimina il file per liberare spazio.
3. **Open** — apre il file: carica in memoria attributi e indirizzi su disco, per velocizzare gli accessi successivi.
4. **Close** — chiude il file, libera spazio nelle tabelle interne e **forza la scrittura dell'ultimo blocco**.
5. **Read** — legge dati dalla posizione corrente, in un buffer fornito.
6. **Write** — scrive dati alla posizione corrente; può ampliare il file o sovrascrivere.
7. **Append** — aggiunge dati solo alla fine (forma limitata di write).
8. **Seek** — riposiziona il puntatore per l'[[#^random|accesso casuale]].
9. **Get Attributes** — legge gli attributi (es. il programma UNIX `make` li usa per la gestione dei progetti). ^random
10. **Set Attributes** — modifica attributi (protezione, flag) dopo la creazione.
11. **Rename** — rinomina il file, alternativa a copia + eliminazione (utile per file grandi).
### Operazioni su file in UNIX (POSIX)
L'apertura di un file restituisce un **handle** (descrittore di file, *file descriptor*) usato dalle operazioni successive. Ogni funzione può restituire un errore (es. `ENOENT` = file inesistente, `EBADF` = descrittore non valido).
> [!example] Aprire e leggere un file
> ```c
> int fd = open("foo.txt", O_RDONLY);
> char buf[512];
> ssize_t bytes_read = read(fd, buf, 512);
> close(fd);
> printf("read %zd: %s\n", bytes_read, buf);
> ```

> [!example] Posizionamento con `lseek`
> ```c
> int fd = open("foo.txt", O_RDONLY);
> lseek(fd, 128, SEEK_CUR);   // sposta avanti di 128 byte dalla pos. corrente
> char buf[8];
> read(fd, buf, 8);           // legge 8 byte dalla nuova posizione
> close(fd);
> ```
> `SEEK_CUR` indica che lo spostamento è **relativo** alla posizione corrente.

> [!example] Aprire in scrittura, creare e troncare
> ```c
> int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC);
> char buf[] = "Hi there";
> write(fd, buf, strlen(buf));
> close(fd);
> ```
> I **flag** controllano il comportamento dell'apertura: `O_WRONLY` (sola scrittura), `O_CREAT` (crea se non esiste), `O_TRUNC` (se esiste, tronca a dimensione 0). Risultato: sovrascrive `foo.txt` con `"Hi there"` o lo crea.

Altre operazioni UNIX: `unlink("foo.txt")` (rimuove), `rename("foo.txt","bar.txt")` (rinomina), `chmod("foo.txt", 0755)` (cambia i permessi), `chown("foo.txt", uid, gid)` (cambia il proprietario). Un programma `11_copyfile.c` copia un file tramite un **buffer da 4096 byte**, con controllo dei parametri e gestione degli errori in apertura/lettura/scrittura/chiusura. Il programma `11_write_and_read_POSIX.c` illustra e confronta due metodi di scrittura/lettura: **binario** (più efficiente, ma non leggibile direttamente dall'utente) e **testuale** (più leggibile, meno efficiente); introduce inoltre una funzione custom `read_line` che legge un file riga per riga fino al carattere `\n`.
# Le directory
Per tenere traccia dei file, il file system usa le **directory**.
> [!quote] Definizione — Directory
> Le **directory** (o cartelle) sono **file** che tengono traccia degli altri file all'interno di un file system, mappando i nomi alle informazioni necessarie per localizzare i dati su disco.
## Da singolo livello a gerarchia
- **Directory a livello singolo**: una sola directory (talvolta *root directory*) contiene tutti i file. Comune nei primi PC e nel supercomputer CDC 6600; vantaggio = semplicità e rapidità nel localizzare i file. Limite: **impraticabile con migliaia di file**.
- **Riemersione moderna**: molti concetti del file system sono ciclici. La directory singola è ancora utile in **dispositivi embedded** (fotocamere, lettori MP3) e tecnologie **RFID**/carte di credito, dove la semplicità conta più della scalabilità. Cos'è un sistema **embedded**? Un sistema dedicato a basso costo: vedi [[01 - Introduzione ai Sistemi Operativi#^embedded|sistemi embedded]].
> [!quote] Definizione — Directory gerarchiche
> Un **sistema di directory gerarchico** organizza i file in gruppi correlati mediante directory ramificate ad **albero**. Ogni utente può avere una directory principale privata (es. reti aziendali). Tutti i file system moderni usano questa struttura; storicamente sperimentata in **MULTICS** negli anni '60.
## Nomi di percorso
Come si specifica un file in un albero di directory?
- **Percorso assoluto (path)**: parte dalla directory radice e conduce al file, unico per ogni file (es. `/usr/ast/mailbox`). Il **separatore** cambia: `/` in UNIX, `\` in Windows, `>` in MULTICS.
- **Percorso relativo**: basato sulla **directory di lavoro** (directory corrente) del processo; non inizia col separatore (es. `mailbox`). I due comandi seguenti sono equivalenti se la working directory è `/usr/hjb`:
  - `cp /usr/hjb/mailbox /usr/hjb/mailbox.bak`
  - `cp mailbox mailbox.bak`

> [!info] Directory di lavoro e voci speciali
> - La **working directory** cambia dinamicamente per ciascun processo e non influisce sugli altri né sul file system dopo l'uscita del processo.
> - Le **procedure di libreria** evitano di cambiarla, o la ripristinano dopo l'uso.
> - Voci speciali presenti in ogni directory: `.` (punto) = directory corrente; `..` (punto punto) = directory **genitore**. Servono a navigare l'albero (es. `cp ../lib/dictionary .`).
## Operazioni sulle directory
- `create` — crea una directory vuota con le voci `.` e `..`.
- `delete` — elimina una directory, **possibile solo se vuota**.
- `opendir` / `closedir` — apre/chiude una directory per leggerne il contenuto.
- `readdir` — restituisce la voce successiva di una directory aperta, **senza esporne la struttura interna**.
- `rename` — rinomina una directory (come per un file).

Un programma `11_show_dir_content.c` mostra informazioni dettagliate sui file (simile a `ls -lh`): dimensione, permessi, proprietario e gruppo, data dell'ultima modifica, usando la funzione **`stat()`** per ottenere i metadati.
## Link e file condivisi
- **`link`** — crea un **hard link**: collega un file esistente a un nuovo percorso **condividendone l'i-node**.
- **`unlink`** — rimuove una voce di directory, cancellando il file solo se è l'**ultimo** link.
- **Link simbolici (soft link)**: varianti che puntano al **nome** di un file (non all'i-node) e possono attraversare i confini del file system o macchine remote; più flessibili ma meno efficienti. Approfonditi in [[#File condivisi hard link e link simbolici]].
# Creazione di archivi
Operazioni di livello utente per raggruppare e comprimere file.
> [!info] tar e gzip
> - **TAR (Tape Archive)**: raccoglie più file e cartelle in un **unico archivio**, mantenendo struttura e permessi originali. Usato per backup, trasferimento, archiviazione.
> - **gzip (GZ)**: comprime l'archivio con un algoritmo **senza perdita di dati** per ridurre lo spazio. Un `.tar.gz` è quindi un file creato con `tar` e poi compresso con `gzip`.

Comandi base:
- Creazione: `tar -czvf nome-archivio.tar.gz /percorso/cartella` → `c` crea, `z` comprime con gzip, `v` output verboso, `f` specifica il nome file.
- Estrazione: `tar -xzvf nome-archivio.tar.gz` → `x` estrae, `z` decomprime, `v` verboso, `f` nome file.

> [!example] Confronto ZIP/UNZIP vs TAR.GZ
> - **ZIP** comprime ogni file *singolarmente* prima di archiviarli (`zip nome.zip file1 file2`, `unzip nome.zip`). Vantaggio: ampia **compatibilità** (Windows, macOS), velocità su file singoli.
> - **TAR.GZ** raccoglie tutto e comprime l'intero archivio. Vantaggi: tasso di **compressione più alto** (archivi grandi) e migliore conservazione di struttura e **permessi**.
# Implementazione del file system
Il file system risponde a **cinque domande** chiave: ^cinque-domande
1. Come **memorizzare i file**? → [[#Implementazione dei file]]
2. Come **implementare le directory**? → [[#Implementazione delle directory]]
3. Come **gestire lo spazio su disco**? → [[#Gestione dello spazio su disco]]
4. Come garantire le **prestazioni**? → [[#Performance del file system]]
5. Come garantire l'**affidabilità**? → [[#Affidabilità del file system]]
## Layout del file system
Il file system è il metodo per organizzare i dati su memoria **non volatile** (dischi/SSD). Un disco può essere suddiviso in più **partizioni**, ciascuna con un proprio file system indipendente. I metodi di strutturazione variano con l'epoca del computer.
> [!info] Vecchio stile — BIOS con MBR (Master Boot Record)
> - L'**MBR** sta nel **settore 0** del disco ed è essenziale per l'avvio; contiene la **tabella delle partizioni** (inizio/fine di ciascuna) e identifica la **partizione attiva**.
> - **Processo di avvio**: il BIOS legge l'MBR, trova la partizione attiva e ne carica il **boot block** per avviare il SO.
> - Ogni partizione inizia con un boot block, seguito da **superblocco**, gestione dello **spazio libero**, **i-node**, **directory radice**, file e directory.

> [!info] Nuova scuola — UEFI (Unified Extensible Firmware Interface)
> Sostituisce il BIOS tradizionale. Vantaggi: **avvio più veloce**, compatibilità 32/64 bit, interfaccia grafica con mouse, **Secure Boot**. Funziona con **GPT**, superando il limite di **2,2 TB** dell'MBR. UEFI non si basa sull'MBR: cerca la tabella delle partizioni nel **secondo blocco**, riservando il **primo blocco** per compatibilità con il software che si aspetta di trovare un MBR legacy.
> - **GPT (GUID Partition Table)**: gestione avanzata delle partizioni — fino a **8 ZiB**, numero (quasi) illimitato di partizioni, **backup** della tabella, controllo di integrità **CRC**.
> - **EFI System Partition (ESP)**: partizione speciale sui dischi GPT che archivia bootloader, driver e utility di diagnostica; usa **FAT32** per compatibilità col firmware UEFI.
> - **Secure Boot**: funzionalità UEFI che controlla le **firme digitali** di bootloader/driver/SO e avvia solo software firmato, bloccando malware e rootkit all'avvio (alcune distro Linux richiedono di disattivarlo).
## Implementazione dei file
Obiettivo: gestire l'**associazione tra file e blocchi del disco**. È fondamentale per integrità, accesso efficiente e gestione dello spazio. Esistono vari metodi (indici, liste concatenate, bitmap, alberi).
### Allocazione contigua
> [!quote] Definizione — Allocazione contigua
> I file sono memorizzati come **sequenze contigue di blocchi** sul disco. Esempio: un file di 50 KB su disco con blocchi da 1 KB occupa **50 blocchi consecutivi**.

- **Vantaggi**: semplice da implementare (basta l'indirizzo del primo blocco + numero di blocchi); **alta efficienza di lettura** (l'intero file si legge in una sola operazione, senza ritardi).
- **Svantaggio — frammentazione**: col tempo i dischi si **frammentano** per la rimozione di file, lasciando intervalli di blocchi liberi sparsi. Allocare un nuovo file richiede di **conoscerne in anticipo la dimensione finale** e trovare un buco adeguato → serve **compattazione** del disco. È l'analogo su disco della [[06 - Gestione della Memoria|frammentazione della memoria]].
### Allocazione a liste concatenate
> [!quote] Definizione — Liste concatenate
> I file sono organizzati come **liste concatenate di blocchi**: ogni blocco contiene una parte di dati e un **puntatore** al blocco successivo. La voce di directory traccia solo l'indirizzo del **primo blocco**.

- **Vantaggi**: usa **tutti** i blocchi disponibili, minima frammentazione esterna.
- **Limiti**: l'**accesso casuale (`seek`) è lentissimo** (bisogna seguire la catena dall'inizio); inoltre lo spazio dati di ogni blocco è ridotto dal puntatore, quindi letture/scritture di dimensione «potenza di due» diventano meno efficienti. Adatto a file letti prevalentemente in **sequenza**.
### FAT (File Allocation Table)
Ottimizza le liste concatenate **spostando i puntatori** dai blocchi a una tabella in memoria.
> [!quote] Definizione — FAT
> La **FAT (File Allocation Table)** è una tabella tenuta **in memoria RAM** in cui **ogni blocco del disco è una voce** che contiene il numero del blocco successivo del file (o un indicatore di fine, es. `-1`). La sequenza dei blocchi di un file è quindi interamente in memoria.

> [!example] Lettura di una FAT
> - File A usa i blocchi `4 → 7 → 2 → 10 → 12` (fine).
> - File B usa i blocchi `6 → 3 → 11 → 14` (fine).
> Poiché i puntatori sono fuori dai blocchi, **l'intero blocco è disponibile per i dati** e l'**accesso casuale è semplificato** (la catena è tutta in RAM).

> [!warning] Limite della FAT — consumo di memoria
> La FAT deve stare **interamente in memoria principale**. Con voci da 3–4 byte, un disco da **1 TB** con blocchi da 1 KB richiederebbe fino a **3 GB di RAM** solo per la FAT → non adatta a dischi grandi. Originariamente in **MS-DOS**, ancora usata da Windows/UEFI e comunissima su **schede SD** (fotocamere, lettori musicali).

> [!example] Limiti per versione FAT — ragionamento numerico
> Ogni versione FAT prende il nome dal numero di **bit per entry** nella tabella; i bit determinano quanti cluster si possono indirizzare e quindi la dimensione massima del volume:
> - **FAT12**: 12 bit per entry → $2^{12}$ cluster → file massimo di circa **32 MB**.
> - **FAT16**: 16 bit per entry → $2^{16}$ cluster → file massimo di circa **2 GB**.
> - **FAT32**: 32 bit per entry, ma i 4 bit alti sono riservati → ~$2^{28}$ cluster indirizzabili → il limite di **4 GB per file** deriva dal campo dimensione a 32 bit nell'entry di **directory**, non dal numero di cluster.
### I-node
> [!quote] Definizione — I-node (index node)
> Un **i-node** è la struttura dati fondamentale dei file system UNIX-like (ext2/ext3/ext4). Contiene **tutte le informazioni su un file tranne il nome e il contenuto**: metadati (permessi, proprietario, timestamp, dimensione) e gli **indirizzi dei blocchi di dati**. Ogni file e directory è rappresentato da un i-node univoco.

> [!info] I-node vs FAT
> - La **FAT** traccia i file con una tabella di allocazione; i sistemi **i-node** separano le informazioni sul file dalla sua **posizione fisica** sul disco.
> - **Efficienza di memoria**: solo gli i-node dei **file aperti** sono in memoria; l'array degli i-node è proporzionale al numero di **file aperti**, **non** alla dimensione del disco (vantaggio decisivo sulla FAT).
> - I sistemi i-node gestiscono meglio i **metadati** e scalano su dischi grandi.

> [!example] Gestione dei file grandi (indirizzamento indiretto)
> Un i-node ha spazio limitato per gli indirizzi (es. blocchi diretti 0–7). Per i file che superano il limite, uno degli indirizzi punta a un **blocco di puntatori** che contiene ulteriori indirizzi di blocchi dati. Così si gestiscono file molto grandi. In **NTFS** (Windows) si usa una struttura simile con i-node più grandi che possono contenere **file piccoli all'interno dell'i-node stesso**.
## Implementazione delle directory
> [!quote] Definizione — Funzione delle directory
> Le directory mappano i **nomi ASCII** dei file sulle informazioni necessarie a localizzare i dati su disco. Il metodo di allocazione varia: indirizzi di blocchi contigui, primo blocco delle liste concatenate, oppure **numero di i-node**.

Due strutture base:
- **(a) Attributi nella voce**: voci a dimensione fissa con gli **indirizzi del disco e gli attributi** dentro la voce di directory.
- **(b) Riferimento a i-node**: ogni voce **fa solo riferimento a un i-node**, che contiene gli attributi (modello UNIX).
### Nomi di file a lunghezza variabile
Supporto per nomi fino a ~255 caratteri. Due tecniche:
- **(a) Voci di lunghezza variabile**: header di lunghezza fissa seguito dal **nome del file** in linea.
- **(b) Gestione a heap**: voci di directory a lunghezza fissa con i nomi gestiti in uno **heap separato** (la voce contiene un puntatore al nome).

Entrambe gestiscono i nomi variabili ma presentano sfide nella **gestione degli spazi vuoti** quando un file viene cancellato (frammentazione interna alla directory).
### Ricerca: liste, hash e cache
- **Ricerca lineare**: storicamente i file in una directory si cercavano linearmente; **lento** con molti file.
- **Tabelle di hash**: il nome del file è sottoposto a **hashing** per generare un indice `0…n-1`; la voce della tabella indica il punto di partenza della ricerca. Le **collisioni** si gestiscono con liste concatenate. Accelera molto la ricerca in directory grandi.
- **Caching delle ricerche**: si salvano in cache i risultati delle ricerche comuni; efficace quando la maggior parte delle ricerche riguarda un numero limitato di file. Hash e cache aumentano l'**efficienza** ma anche la **complessità amministrativa**: convengono per directory molto estese.
### File condivisi: hard link e link simbolici
In ambienti collaborativi più utenti devono lavorare sugli **stessi file**: un file può comparire nella directory di più utenti (struttura non più ad albero puro, ma a **grafo aciclico**).
> [!info] Hard link — conteggio dei riferimenti
> - L'**hard link** punta **direttamente all'i-node** del file condiviso. L'i-node mantiene un **contatore di link** (`Conteggio`).
> - **Spazio-efficiente**: un solo i-node indipendentemente dal numero di link; una sola voce di directory per ciascun link.
> - Il file viene rimosso **solo quando il conteggio arriva a 0**.
> - **Problema**: se il proprietario originale (es. C) cancella il file, il conteggio scende (es. da 2 a 1) ma il file **resta** finché esistono altri link → possibile **confusione sulla proprietà** (l'i-node continua a indicare `Proprietario = C`).

> [!info] Link simbolici (soft link)
> - Puntano al **nome** del file, non all'i-node → **maggiore flessibilità**: possono riferirsi a file oltre i confini del file system e su macchine remote.
> - **Meno efficienti**: richiedono un i-node per ogni link e hanno **overhead** nella risoluzione del percorso.
> - **Diventano invalidi** alla rimozione del file originale (*dangling link*).
> - **Problema comune**: file con più percorsi possono essere **elaborati più volte** da programmi di backup/ricerca → rischio di **duplicazione**.
# Gestione dello spazio su disco
I file si memorizzano su disco in due modi: **allocazione contigua** o **suddivisione in blocchi non contigui**. La contigua richiede di spostare il file se cresce (come la segmentazione in memoria); i **blocchi non contigui** di dimensione fissa danno più flessibilità e migliore utilizzo.
## Dimensione dei blocchi — il compromesso
La scelta della dimensione del blocco è un **compromesso tra spazio ed efficienza**.
> [!info] Prestazioni vs efficienza dello spazio
> - **Blocchi grandi**: più dati per operazione di lettura/scrittura (trasferimento veloce) **MA** spreco di spazio con file piccoli ([[06 - Gestione della Memoria|frammentazione interna]]).
> - **Blocchi piccoli**: minimo spreco con file piccoli **MA** un file si distribuisce su più blocchi → più ricerche e ritardi (anche di **rotazione** nei dischi).
> - Il valore comune **4 KB** bilancia tempo di trasferimento ed efficienza dello spazio.

Il grafico tipico: la **velocità di trasferimento** cresce con la dimensione del blocco; l'**efficienza di utilizzo** dello spazio (rapporto dimensione reale/spazio allocato) **cala** oltre la dimensione media dei file. Le due curve si incrociano intorno ai **4 KB**.
> [!info] Dischi magnetici vs memoria flash
> - **Dischi magnetici**: la scelta dipende da **tempo di ricerca** e **ritardo di rotazione**; blocchi più grandi = più velocità, meno efficienza.
> - **Memoria flash (SSD)**: può avere sprechi sia con blocchi grandi sia piccoli, per via delle **dimensioni fisse delle pagine flash**.
> - **Tendenza**: con dischi sempre più capienti (TB) può convenire usare blocchi più grandi, accettando meno efficienza in cambio di prestazioni.
## Tenere traccia dei blocchi liberi
> [!info] Metodo 1 — Lista concatenata
> Si usa una **lista concatenata di blocchi del disco** che contengono i numeri dei **blocchi liberi**; le liste risiedono negli **stessi blocchi liberi** (costo zero quando il disco è quasi pieno). Esempio: con blocchi da 1 KB e numeri da 32 bit, ogni blocco-lista contiene **255** numeri di blocchi liberi (1 voce è il puntatore al blocco successivo). Per 1 TB servono ~4 milioni di voci.

> [!info] Metodo 2 — Bitmap
> Una **bitmap** con **un bit per ogni blocco**: `1` = libero, `0` = allocato. Per un disco da 1 TB serve una bitmap da ~1 miliardo di bit. In genere richiede **meno spazio** della lista concatenata, tranne quando il disco è **quasi pieno** (lì la lista, avendo pochi blocchi liberi, occupa meno).

> [!info] Ottimizzazione della lista — conteggi di blocchi consecutivi
> Si possono tracciare **serie di blocchi consecutivi** invece di blocchi singoli: a ciascun indirizzo si associa un **conteggio** (8/16/32 bit) di blocchi liberi consecutivi. Nell'ipotesi migliore un disco quasi vuoto è descritto da **due numeri** (indirizzo del primo blocco libero + conteggio). Efficiente per dischi quasi vuoti, meno per dischi frammentati.
### Free list con blocchi di puntatori in memoria
> [!info] Funzionamento della free list
> La gestione può usare una **lista concatenata di blocchi di puntatori** (*free list*), tenendo in memoria **un solo blocco** di puntatori alla volta (ottimizza la RAM). Quando si crea un file, i blocchi necessari si prelevano da quelli disponibili nel blocco in memoria; quando il blocco si svuota, se ne legge uno nuovo dal disco.
>
> Problema: con molti **file temporanei**, se il blocco di puntatori in memoria è quasi pieno, le frequenti allocazioni/rilasci causano molte operazioni di **I/O su disco**. Una strategia alternativa **divide il blocco pieno** per gestire meglio i blocchi liberi senza I/O su disco.
## Quote del disco
Nei sistemi **multiutente** il SO limita lo spazio per utente.
> [!info] Meccanismo delle quote
> - L'amministratore assegna a ogni utente un numero massimo di **file e blocchi**; il SO verifica che non venga superato.
> - Ogni apertura di file consulta gli attributi (incluso il **proprietario**); gli incrementi di dimensione sono contabilizzati nella quota del proprietario.
> - Una **tabella delle quote** tiene un record per ciascun utente con file aperti; i record sono riscritti sul file delle quote alla **chiusura** dei file.
> - **Limiti soft e hard**: il limite **soft** può essere superato *temporaneamente* (durante una sessione), il **hard** mai. Superare il hard o ignorare gli avvisi del soft porta alla **restrizione dell'accesso**; l'utente deve rientrare nel soft prima di scollegarsi.
## Intermezzo — organizzazione di Ext2
> [!example] Componenti del file system Ext2 (cap. 10.6.3 del libro)
> Il disco è diviso in **gruppi di blocchi**. Ogni gruppo contiene:
> - **Superblocco**: layout, numero di i-node e di blocchi.
> - **Descrittore del gruppo**: blocchi liberi, i-node liberi, posizione delle bitmap.
> - **Bitmap dei blocchi** e **bitmap degli i-node** (design ereditato da MINIX 1).
> - **I-node** numerati (un i-node descrive un solo file).
> - **Blocchi di dati** (file e directory, non necessariamente contigui).

> [!info] Collocazione e preallocazione in Ext2
> - Gli i-node delle directory sono **distribuiti tra i gruppi di blocchi**; Ext2 cerca di posizionare i file nella **stessa area della directory genitore** per minimizzare la frammentazione, usando le bitmap per trovare aree libere.
> - **Preallocazione**: Ext2 prealloca **otto blocchi aggiuntivi** per ogni nuovo file, riducendo la frammentazione dovuta a scritture successive.
> - Le voci di directory contengono: numero dell'i-node, dimensione della voce (`rec_len`), tipo, lunghezza del nome. Alla cancellazione di un file (es. «voluminoso»), la voce precedente **estende il proprio `rec_len`** per assorbire lo spazio liberato.
> - Accesso ai file via syscall (`open`); il percorso si analizza dalla directory corrente o radice; ricerche **lineari ma ottimizzate da una cache** delle directory recenti; supporto a **soft link e hard link**.
# Performance del file system
Il collo di bottiglia è la differenza di velocità tra memoria e disco.
> [!warning] Memoria vs disco magnetico
> - **Memoria**: accesso ultraveloce (~10 ns per leggere una parola a 32 bit).
> - **Disco magnetico**: molto più lento per il **tempo di ricerca della traccia** (5–10 ms) e l'attesa che il settore passi sotto la testina.
> - L'accesso al disco può essere **milioni di volte** più lento dell'accesso alla memoria → i file system applicano ottimizzazioni per ridurre numero di accessi, tempo di `seek` e spreco di spazio.
## Block cache (buffer cache)
> [!quote] Definizione — Block cache / buffer cache
> La **cache (block cache o buffer cache)** è una raccolta di **blocchi del disco tenuti in memoria** per ridurre i tempi di accesso al disco, conservando i blocchi più usati.

Funzionamento: a ogni richiesta di lettura si verifica **se il blocco è già in cache**. Se sì, la richiesta è soddisfatta senza accedere al disco; se no, il blocco viene prima letto da disco, portato in cache e poi usato. La ricerca in cache usa una **tabella di hash** (lista concatenata per i blocchi con lo stesso valore).
> [!info] Algoritmi di sostituzione nella cache
> Quando la cache è piena, i nuovi blocchi sostituiscono quelli esistenti (riscritti su disco se modificati). Si usano gli stessi algoritmi della [[06 - Gestione della Memoria|paginazione]]: **FIFO**, **seconda chance**, **LRU**. La lista LRU è bidirezionale (meno recenti in testa, più recenti in fondo).
>
> **Limite di LRU**: in caso di **crash** può lasciare il file system **incoerente**, specialmente per blocchi critici come i blocchi degli i-node → si usa uno schema LRU modificato basato su importanza e necessità immediata. I **blocchi critici** modificati si scrivono **subito** su disco per mantenere la coerenza.

> [!info] Posizionamento degli i-node sul disco
> Leggere anche un file piccolo basato su i-node richiede **due accessi al disco**: uno per l'i-node e uno per il blocco dati. Per ridurre lo spostamento della testina si adottano due strategie:
> - **I-node a metà disco**: posizionare gli i-node al centro del disco **dimezza in media** il tempo di ricerca rispetto al posizionamento tradizionale (i-node all'inizio del disco).
> - **Gruppi di cilindri**: dividere il disco in **gruppi di cilindri**, ciascuno con i propri i-node, blocchi dati e lista dei blocchi liberi; così i-node e dati di un file restano vicini fisicamente.

> [!info] Read ahead e deframmentazione
> - **Allocazione intelligente**: blocchi vicini nello stesso cilindro per minimizzare il movimento del braccio del disco; bitmap in memoria per allocare blocchi adiacenti (scrittura sequenziale efficiente).
> - **Read ahead**: si leggono in anticipo i blocchi successivi attesi.
> - **Deframmentazione**: col tempo i dischi si frammentano; riorganizza i file per renderli contigui e raggruppa lo spazio libero. Windows fornisce `defrag` — **consigliato per HDD, sconsigliato per SSD** (usura inutile). I file system Linux (in particolare **ext4** e **btrfs**) riducono la necessità di deframmentazione grazie alla **preallocazione di blocchi contigui** in fase di scrittura: quando si scrive un file, ext4 prealloca un gruppo di blocchi adiacenti anziché uno alla volta, limitando la frammentazione per i file in espansione.
## Buffer cache vs page cache
> [!info] Due cache, spesso gli stessi dati
> - **Buffer cache**: memorizza i **blocchi del disco** in RAM per ridurre gli accessi.
> - **Page cache**: memorizza le **pagine del VFS** in RAM prima di passare al driver del dispositivo.
> - **Dati duplicati**: le due cache contengono spesso gli stessi dati (es. file **mappati in memoria**). Molti SO **fondono** buffer e page cache per un uso più efficiente della RAM: un file interamente mappato in memoria non occupa un'area di memoria utile per altre pagine, ma sfrutta la buffer cache del disco.
## Strategie di scrittura
> [!info] UNIX vs Windows
> - **UNIX**: chiamata `sync` per scrivere **periodicamente** i blocchi modificati su disco, riducendo la perdita di dati in caso di crash.
> - **Windows**: strategia **write-through** (scrittura immediata) dei blocchi modificati, integrata con la chiamata `FlushFileBuffers`.
## Il comando `free`
> [!info] Leggere l'uso della memoria in Linux
> Il comando **`free`** (`free -h` per output leggibile) mostra l'utilizzo della RAM, inclusa la cache:
> - Colonna **`buff/cache`**: spazio usato per buffer e cache (inclusi i dati letti dal disco).
> - Colonna **`free`**: memoria fisica **non utilizzata** attualmente.
> - Colonna **`available`**: stima della memoria **realmente disponibile** per nuovi processi, considerando anche la cache facilmente liberabile.
>
> La cache velocizza l'accesso ai file frequenti riducendo le letture ripetute dal disco lento.
## Compressione e deduplicazione
> [!info] Ottimizzazione dello spazio
> - **Compressione**: riduce la dimensione dei file con algoritmi che identificano e sostituiscono sequenze ripetute. File system come **NTFS** (Windows), **Btrfs** e **ZFS** possono comprimere automaticamente.
> - **Deduplicazione**: rileva e rimuove i dati **duplicati** in tutto il file system, conservando una sola copia di ciascun dato unico (a livello di blocchi o di porzioni di file). Richiede un **controllo degli hash** per evitare falsi positivi dovuti a collisioni.
# Affidabilità del file system
Diverse minacce possono compromettere i dati.
> [!warning] Minacce all'affidabilità
> - **Guasti del disco**: blocchi danneggiati (settori illeggibili) o errori sull'intero disco (fallimento hardware).
> - **Interruzioni di energia (blackout)**: scritture inconsistenti su dati o **metadati**.
> - **Bug del software / corruzione dei (meta)dati**: errori di programmazione che scrivono dati errati.
> - **Errori umani / comandi errati**: es. `rm *.o` vs `rm * .o`.
> - **Perdita/furto del computer / accesso non autorizzato**.
> - **Malware / ransomware**: virus che infettano, criptano o distruggono i dati.
## Backup
> [!quote] Perché si fa il backup
> «I backup su disco sono generalmente effettuati per affrontare uno dei due potenziali problemi: **recupero da un disastro** e **recupero dalla stupidità**.»

> [!info] Cinque considerazioni pratiche sul backup
> 1. **Quali file salvare**: un backup impiega molto tempo e occupa molto spazio; occorre decidere se salvare l'intero file system o solo alcune directory.
> 2. **Ripristino incrementale**: il **backup incrementale** salva solo i file modificati dall'ultimo backup completo. Il ripristino è più complesso: va prima ripristinato il backup completo più recente, poi applicati tutti i backup incrementali **in ordine cronologico crescente** (dal più vecchio al più recente).
> 3. **Compressione rischiosa**: con molti algoritmi di compressione basta un **singolo punto difettoso** sul supporto per rendere illeggibile l'intero flusso compresso; la scelta di comprimere va valutata con attenzione.
> 4. **Backup su file system attivo**: se durante il backup vengono aggiunti, cancellati o modificati file, il risultato potrebbe essere incoerente; per questo si usano **snapshot** (istantanee) dello stato del file system.
> 5. **Backup fuori sede**: i backup devono essere conservati lontano dai computer principali, ma questo introduce ulteriori **rischi per la sicurezza** (più luoghi da sorvegliare).
Modalità: **backup completo** (copia totale, settimanale/mensile) e **backup incrementale** (solo i file modificati dall'ultimo completo → meno tempo e spazio). Tipologie:
- **Backup fisico**: copia **sequenziale di tutti i blocchi** del disco (dal blocco 0 all'ultimo). Semplice e veloce (alla velocità del disco), ma deve evitare blocchi danneggiati e file inutili (paginazione, ibernazione); **manca di flessibilità** (no incrementali, no ripristino di singoli file).
- **Backup logico**: seleziona e copia **solo file e directory specifici** modificati a partire da una data, ignorando file di sistema e blocchi danneggiati. Ideale per incrementali e per ripristinare file singoli.
> [!example] Algoritmo di backup logico (UNIX)
> Si include ogni file/directory modificato dopo il backup precedente **e tutte le directory lungo il percorso** verso i file modificati (così la struttura è ricostruibile). Nella figura del libro, gli oggetti in grigio (i-node modificati) e i nodi sul percorso verso di essi vengono salvati. L'algoritmo si articola in **quattro fasi**:
> 1. **Rilevamento delle modifiche**: si parte dalla directory radice, si esaminano tutte le voci e si contrassegna nella **bitmap** gli i-node dei file e delle directory modificati; vengono incluse tutte le directory lungo il percorso verso i file modificati, indipendentemente dal proprio stato.
> 2. **Pulizia della bitmap**: si deselezionano le directory che non contengono né file modificati né sottodirectory modificate, lasciando nella bitmap solo gli elementi che richiedono effettivamente il backup.
> 3. **Backup delle directory contrassegnate**: si salvano le directory marcate con i loro attributi.
> 4. **Backup dei file contrassegnati**: si salvano i file marcati con i relativi attributi.

> [!info] Casi speciali nel ripristino del backup logico
> 1. **Free list non è un file**: la lista dei blocchi liberi non è oggetto di backup e va **ricostruita da zero** alla fine del ripristino; è sempre possibile farlo, poiché i blocchi liberi sono il complemento dei blocchi occupati da tutti i file.
> 2. **Hard link**: un file collegato a più directory tramite hard link deve essere ripristinato **una sola volta**; tutte le directory che dovrebbero puntarvi devono poi puntarci correttamente.
> 3. **Sparse file**: i file UNIX possono contenere **buchi** (si scrive a un offset distante senza riempire il mezzo); i buchi non si salvano e non si ripristinano; al momento del ripristino l'area corrispondente viene riempita di **zero**, preservando la dimensione virtuale del file.
> 4. **File speciali**: file speciali come le **pipe** e altri pseudo-file non andrebbero mai salvati nel backup, indipendentemente dalla directory in cui si trovano.

> [!info] Bonus — `rsync`
> **`rsync`** sincronizza file e cartelle tra due location (stessa macchina o macchine diverse), trasmettendo **solo le parti di file modificate**. Ideale per backup, ripristino e sincronizzazione in rete; supporta link, dispositivi, attributi, permessi; può usare **SSH** per trasferimenti cifrati.
> - Locale: `rsync -av /sorgente/cartella /destinazione/cartella` (`-a` = modalità archivio, mantiene permessi/struttura; `-v` = verboso).
> - Remoto: `rsync -av /sorgente/cartella utente@remoto:/destinazione/cartella`.
## Coerenza del file system
La coerenza è cruciale per l'integrità dei dati; problemi sorgono dopo un **crash** durante la scrittura dei blocchi.
- **Utility di verifica**: UNIX (`fsck`) e Windows (`sfc`) controllano la coerenza, eseguite all'avvio dopo un crash.
- **File system con journaling**: progettati per gestire autonomamente la maggior parte delle incoerenze, **senza** controlli esterni dopo un crash.
> [!info] Come funziona fsck — controllo dei blocchi
> `fsck` costruisce **due tabelle di contatori**, una per i blocchi presenti nei file e una per i blocchi nella lista dei liberi, scorrendo tutti gli i-node. Al termine confronta le due tabelle e individua tre possibili anomalie:
> - **(a) Blocco mancante**: un blocco non appare in nessuna delle due tabelle → viene **aggiunto alla lista dei blocchi liberi**.
> - **(b) Blocco duplicato nella lista dei liberi**: un blocco compare più volte tra i liberi → la lista viene **deduplicata**.
> - **(c) Blocco di dati presente in più file**: un blocco risulta assegnato a due file distinti → il blocco viene **copiato** e ciascun file riceve la propria copia, segnalando all'utente che uno dei due è probabilmente corrotto.
### Journaling
> [!quote] Definizione — Journaling
> Un file system con **journaling** registra **anticipatamente** in un **log (journal)** le operazioni da eseguire, per garantire la coerenza in caso di crash. Il journal è come un **registro che tiene traccia delle modifiche prima che avvengano effettivamente**. Usato in **NTFS**, **ext4**, **ReiserFS**; default in macOS.

> [!info] Come funziona — tre fasi
> 1. **Registrazione**: prima di ogni modifica (creazione/cancellazione di un file), il file system scrive nel journal un record che **descrive l'operazione**.
> 2. **Esecuzione**: il file system esegue la modifica effettiva sul disco.
> 3. **Conferma**: completata l'operazione, aggiorna il journal per indicare il **successo**.
>
> Dopo un crash, al riavvio il file system **consulta il journal**: se trova operazioni registrate ma non confermate, le **completa**. Garantisce che le modifiche parziali non lascino il file system incoerente (tutto o niente). Vantaggi: **integrità dei dati** e **recupero rapido**.
>
> Esempio dell'eliminazione di un file in UNIX: rimozione dalla directory, rilascio dell'i-node, restituzione dei blocchi al pool dei liberi. Senza journaling, un crash a metà può perdere l'accesso a i-node/blocchi o assegnarli erroneamente.
## Sicurezza dei dati
> [!warning] Eliminazione sicura e cifratura
> - La **cancellazione standard non rimuove fisicamente** i dati dal disco, lasciandoli vulnerabili. L'eliminazione sicura richiede distruzione fisica o **sovrascrittura approfondita**.
> - Su dischi magnetici, sovrascrivere con zeri non basta (residui magnetici recuperabili); è consigliato inserire **sequenze di 0 e numeri casuali**, ripetendo l'operazione **almeno 3–7 volte** (attenzione: molte scritture stressano gli **SSD**).
> - Sugli **SSD** la mappatura dei blocchi flash è gestita dalla **FTL** (Flash Translation Layer), non dal file system → sovrascrittura meno prevedibile.
> - **Cifratura del disco**: la soluzione più efficace è cifrare l'intero disco con algoritmi robusti come **AES**. **SED (Self-Encrypting Drives)** = cifratura integrata nel dispositivo (ma con possibili vulnerabilità). Windows usa AES con la **chiave master del volume** decifrata tramite password utente, chiave di ripristino o **TPM**.

> [!example] Domande d'esame tipiche
> - Importanza dei file: perché esistono e quali limiti della RAM risolvono.
> - Tipologie di file (normali, speciali a caratteri, speciali a blocchi, ASCII, binari) e strutture interne (sequenza di byte, record fissi, albero di record).
> - Metodi di implementazione dei file: **allocazione contigua**, **liste concatenate**, **FAT**, **i-node** — pregi e difetti di ciascuno.
> - Struttura e implementazione delle directory: voce con attributi vs riferimento a i-node; nomi a lunghezza variabile; ricerca lineare, hash, cache.
> - Accesso ai file: differenza tra **accesso sequenziale** e **accesso casuale** (random); ruolo di `seek`.
> - Differenza tra **percorso assoluto** e **percorso relativo**; directory di lavoro; voci speciali `.` e `..`.
# File system virtuali (VFS)
I SO moderni gestiscono **più file system simultaneamente** (NTFS, FAT-32, FAT-16, …). Windows li distingue con lettere di unità (`C:`, `D:`, …); i sistemi **UNIX** li integrano in un'**unica struttura gerarchica**.
> [!quote] Definizione — VFS (Virtual File System)
> Il **VFS** è uno strato che permette di integrare vari file system in una struttura unificata, basato su un **livello di codice comune** che interagisce con i file system reali sottostanti (locali e remoti, es. **NFS — Network File System**).

- **Interfaccia superiore**: interagisce con le **syscall POSIX** dei processi utente (`open`, `read`, `write`).
- **Interfaccia inferiore**: decine di funzioni che il VFS invia ai file system sottostanti.
> [!info] Concetti chiave del VFS
> - **Superblock**: descrittore di alto livello di un file system specifico nel VFS (tipo, dimensione, …); identifica e gestisce le risorse del file system sottostante.
> - **V-node**: astrazione di un **singolo file** nel VFS; contiene metadati (permessi, proprietà, dimensione) e riferimenti ai dati reali. Il VFS usa i v-node per offrire un accesso **indipendente dal file system**.
> - **Directory**: mappa i nomi dei file ai rispettivi v-node, indipendentemente dal file system, fornendo un'**interfaccia unificata**.

> [!info] Aggiungere un nuovo file system
> - **Registrazione**: ogni file system fornisce al VFS un **vettore di funzioni** richieste; così il VFS sa come eseguire le operazioni.
> - **Montaggio**: al `mount`, il file system fornisce informazioni al VFS (es. superblock); l'apertura di un file crea un **v-node** mappato sulle operazioni del file system reale.
> - **Gestione I/O**: i file aperti sono tracciati tramite v-node e tabelle dei descrittori; `read` segue il puntatore dalla tabella dei descrittori al v-node e alle funzioni del file system reale.
> - Aggiungere nuovi file system è relativamente semplice: basta fornire funzioni conformi all'**interfaccia VFS** → gestione trasparente di file system eterogenei.
# Bonus — RAID
Non solo il SO garantisce l'affidabilità: anche l'**hardware** può farlo.
> [!quote] Definizione — RAID
> **RAID** = *Redundant Array of Inexpensive (poi Independent) Disks*. Nato (Patterson et al., 1988) per migliorare **prestazioni e affidabilità** dei dischi magnetici, in contrapposizione al concetto di **SLED** (Single Large Expensive Disk). Un **controller RAID** gestisce un contenitore di dischi (SCSI, SATA o SSD) accanto al computer.

> [!info] Livelli RAID
> - **RAID 0** (*+storage*): distribuisce i dati in **strip** (strisce) su più dischi → prestazioni elevate su richieste grandi, ma **nessuna ridondanza** (meno affidabile).
> - **RAID 1** (*+redundancy*): **duplicazione** (mirroring) dei dischi → tolleranza agli errori, lettura migliorata, scrittura come unità singola.
> - **RAID 2** (*+storage*): a livello di parole/byte con **codice di Hamming**.
> - **RAID 3** (*+redundancy, +storage*): singolo **bit di parità** per parola, richiede sincronizzazione delle unità.
> - **RAID 4** (*+storage, +redundancy*): strip con un'unità extra dedicata alla **parità**.
> - **RAID 5** (*+storage, +redundancy*): distribuisce i bit di parità **uniformemente** su tutte le unità.
> - **RAID 6**: come RAID 5 ma con un **blocco di parità aggiuntivo** → maggiore tolleranza agli errori.
> - **RAID 0+1**: combinazione — mirroring (RAID 1) di insiemi di dischi in striping (RAID 0).

> [!example] RAID 5 in azione (parità XOR)
> Tre dischi A, B, C. La parità si calcola con **XOR** bit a bit dei dati e si memorizza (a rotazione) su un disco.
> - Disco A: `1011` · Disco B: `1100`
> - Parità (C) = `1011 XOR 1100 = 0111`
>
> Se il **Disco B si guasta**, lo ricostruiamo: `1011 (A) XOR 0111 (C) = 1100` = dati originali di B. È il principio di tolleranza ai guasti del RAID a parità.
# Storia ed esempi di file system
## File system V7 di UNIX (1979)
> [!info] UNIX V7
> Derivato da **MULTICS** e implementato sul **PDP-11**, ha contribuito alla fama di UNIX. Struttura ad **albero gerarchico** con possibilità di formare un **grafo aciclico orientato** tramite link. Nomi dei file: max **14 caratteri** (esclusi `/` e NUL); massimo **64K file** per file system (formato delle voci di directory). La **voce di directory** è composta da numero di i-node (2 byte) + nome del file (14 byte). L'i-node contiene attributi (dimensioni, timestamp, proprietario, gruppo, protezione) e un **contatore di link**. La ricerca di `/usr/ast/mbox` procede leggendo directory e individuando i-node, partendo da radice o working directory, usando `.` e `..`. Il design ha influenzato i file system UNIX successivi, fino ai moderni Linux.
## Evoluzione dei file system Linux
> [!info] Da Ext a Ext4 e oltre
> - **Ext (1992)**: primo file system di Linux (Rémy Card), supera i limiti di MINIX (max 2 GB), primo a usare il **VFS** nel kernel.
> - **Ext2 (1993)**: risolve problemi di Ext (immutabilità degli i-node, frammentazione). **Immutabilità**: gli attributi principali dell'i-node (es. numero identificativo) non cambiano per tutta la vita del file. Prevale su Xiafs per affidabilità a lungo termine.
> - **Ext3**: aggiunge il **journaling** per maggiore integrità.
> - **Ext4 (2006–2008)**: introduce gli **extent** (strutture che indicano un intervallo **contiguo** di blocchi: indirizzo iniziale + numero di blocchi consecutivi), semplificando la gestione dei file grandi; usa un **Journaling Block Device (JBD)**; journaling configurabile (solo metadati o intero disco); supporta file fino a **16 TB** e file system fino a **1 EB**. Adottato da Google (2010) e Android 2.3 (al posto di YAFFS).
> - **Btrfs** («better F S»): **Copy-on-Write** (condivide il file originale invece di copiarlo; scrive le modifiche in una nuova posizione invece di sovrascrivere → previene la perdita di dati). File fino a 16 EiB, snapshot, supporto RAID 0/1/1+0, **checksum** dei dati, allocazione dinamica degli inode, deframmentazione/ridimensionamento a caldo, ottimizzazione SSD. Più avanzato di ext4 ma **meno maturo/testato**.
# Struttura delle cartelle in Linux
In Linux **anche i dispositivi sono visti come file**. La gerarchia parte dalla radice `/`.
> [!info] Cartelle principali
> - **`/bin`**: binari dei comandi essenziali (`cat`, `ls`, `pwd`, `cp`, `mv`, `rm`, …).
> - **`/boot`**: file per il **boot loader** e il **kernel** (`grub`, …).
> - **`/etc`**: file di **configurazione** del sistema (`fstab`, `group`, `hosts`, …).
> - **`/usr`**: pacchetti di sistema, applicazioni utente, dati condivisibili (`/usr/local`, `/usr/bin`, `/usr/lib`, …).
> - **`/var`**: file variabili — temporanei, **log**, cache, spool, lock.
> - **`/sbin`**: binari di **sistema** (`fdisk`, `ifconfig`, `mkfs`, `reboot`, …).
> - **`/home`**: directory principale degli utenti (Documenti, Immagini, …).
> - **`/lib`**: librerie essenziali (incluso il compilatore C e le sue librerie).
> - **`/dev`**: file descrittori dei **dispositivi** (hard disk, periferiche).
> - **`/media`**: media rimovibili **montati automaticamente** (CD, USB).
> - **`/mnt`**: punto per il **mount manuale** di file system temporanei.
> - **`/opt`**: software opzionale e add-on.
> - **`/root`**: home dell'utente **root**.
> - **`/tmp`**: file temporanei.
## Visualizzare e montare partizioni
> [!info] Scoprire partizioni e file system
> - **`lsblk`**: elenca i **dispositivi a blocchi** (dischi e partizioni).
> - **`fdisk -l`**: elenca dettagliatamente tutte le partizioni, comprese quelle non montate (`sudo fdisk -l`).
> - **`mount -l`**: elenca i file system **attualmente montati** con opzioni ed etichette.

> [!quote] Cos'è montare una partizione?
> **Montare** (`mount`) collega il file system di un dispositivo a una directory dell'albero, rendendone visibile il contenuto. Senza montaggio, attaccando una chiavetta USB non se ne vedrebbe il contenuto.

> [!example] Montaggio e smontaggio
> - Sintassi: `mount [opzioni] <dispositivo> <directory>` — es. `sudo mount /dev/sda1 /mnt/mydisk`.
> - La directory di destinazione deve **esistere prima** (`mkdir /mnt/mydisk`).
> - Opzioni comuni: `-t <tipo>` (es. `-t ext4`), `-o ro` (sola lettura).
> - Smontaggio: `sudo umount /mnt/mydisk`. Lo **smontaggio corretto** è essenziale per prevenire la perdita di dati.
>
> Queste operazioni richiedono privilegi di root.
# Collegamenti con altri argomenti
> [!info] Mappa dei rimandi
> - **Memoria virtuale e paginazione**: gli algoritmi di sostituzione della [[#Block cache buffer cache|block cache]] (FIFO, seconda chance, LRU) e la frammentazione interna/esterna sono trattati in [[06 - Gestione della Memoria]].
> - **I/O e storage fisico**: il comportamento di dischi e SSD (tempo di `seek`, ritardo di rotazione, **DMA**, buffer cache lato hardware) è nelle lezioni su [[08 - Input Output]].
> - **Processi**: i descrittori di file e le syscall sono legati alla gestione dei [[03 - Processi e Thread|processi]].
> - **Concetti di base**: il ruolo del file system come gestore di risorse è introdotto in [[02 - Concetti di Base e Strutture]].
