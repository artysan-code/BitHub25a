# Linux e BASH
Questa nota copre la parte **pratica** del corso — l'uso di **Linux** e della shell **BASH** (slide 3.1) — complementare ai concetti del [[02 - Concetti di Base e Strutture]]. Là si spiega *cos'è* una shell e *come* il SO espone i suoi servizi (system call, astrazione di file e processo, ciclo `fork`/`execve`); qui si vede *come si usa* davvero il sistema da terminale: comandi, redirezione, permessi, processi, scripting.

> [!info] Inquadramento nel programma
> Corrisponde al punto «**Unix e Linux (caso di studio)**» del programma. È materiale **pratico**, da eseguire a terminale: gli esercizi di autovalutazione del prof (`3.1_Exercises`) coprono la maggior parte dei comandi di questa nota (non `useradd`/`sudo`, `alias`, `history`, `top`). Fonte originale delle slide: Robert Putnam (Boston University), adattate da Danilo Croce.
## Cos'è Linux
> [!quote] Definizione — Linux
> Linux è un **clone di Unix** (propriamente, il solo **kernel**) avviato nel **1991** e scritto da zero da **Linus Torvalds** con una rete di sviluppatori. Secondo le slide, il **64%** dei server del mondo esegue una variante di Unix o Linux; anche i telefoni Android e l'Amazon Kindle usano Linux. Oltre ad Android, molti dispositivi embedded girano su Linux *(extra, non da slide)*.

La filosofia Unix (Kernighan & Pike, *The Unix Programming Environment*) è **«small programs that do one thing well»** *(formula comune, non da slide)*: la potenza di un sistema viene dalle **relazioni** tra i programmi più che dai singoli programmi. Tanti piccoli strumenti, banali in isolamento, diventano potenti se **combinati** (vedi [[#Redirezione e pipe]] e [[#Utility di elaborazione del testo]]). L'ultimo punto dell'agenda della slide («Hello, world in C») è svolto nella nota [[10 - Programmazione C e Concorrente]]. La storia completa di Unix→Linux è in [[01 - Introduzione ai Sistemi Operativi]].

La struttura del file system somiglia a un **albero capovolto**: le *directory* (le «cartelle» di Windows) sono raccolte di file e di altre directory, ogni directory ha una directory genitore tranne la radice (*root*), e molte hanno sottodirectory. A differenza di Windows (più dischi `C:`, `D:`, più file system), Unix/Linux ha **una sola gerarchia** di file system, ad albero da `/`. La struttura delle directory (`/bin`, `/etc`, `/usr`, …) è già descritta in [[07 - File System#Struttura delle cartelle in Linux]].
## La shell BASH
> [!quote] Definizione — Shell
> Programma che **interpreta i comandi** digitati e li invia al sistema operativo. Fornisce anche comandi interni (*built-in*), strutture di controllo per la programmazione e variabili d'ambiente.

**BASH** = **Bourne-again Shell** (versione GNU della shell scritta da Stephen Bourne intorno al 1977); è la shell di default. Un'alternativa comune è **TCSH**. Il *ciclo interno* della shell — legge un comando, fa `fork`, il figlio fa `execve`, il padre `waitpid` — è descritto in [[02 - Concetti di Base e Strutture#Protezione e shell]].
### Anatomia di un comando
Un comando ha tre parti: **command**, **options**, **parameters**. Esempio: `cal -j 3 1999` → `cal` è il comando, `-j` un'opzione (*switch*), `3` e `1999` i parametri. Le opzioni hanno forma **breve** e **lunga**: `date -u` ≡ `date --universal`. Comandi base per provare: `shazam` (comando inesistente: la shell risponde con un errore), `whoami` (il mio login), `hostname` (nome macchina), `echo "Hello, world"` (stampa i caratteri a schermo), `echo $HOME` (stampa una variabile d'ambiente), `date` (data e ora correnti), `cal` (calendario del mese corrente). Domande della slide: qual è la natura del *prompt*? Qual è stata la risposta del sistema al comando inesistente?

> [!example] Sostituzione di comando (command substitution)
> `echo my login is $(whoami)` → la shell **sostituisce** `$(...)` con l'output del comando interno. Es. `echo "Oggi è $(date)"` *(extra, non da slide)*.
### History e aiuto
La shell tiene la cronologia dei comandi:
- `history` elenca i comandi recenti; frecce ↑/↓ per scorrerli.
- `!!` ripete l'ultimo comando; `!132` ripete il comando n°132; `!ls` ripete l'ultimo che inizia per `ls`.
- Aiuto: `comando --help`, `man comando`, `help` (built-in BASH), `man bash`.

> [!info] man usa less
> `man` mostra le pagine tramite il pager **`less`**: `Spazio`/`f` pagina avanti, `b` indietro, `<`/`>` inizio/fine, `/pattern` cerca avanti (`n` ripete), `?pattern` cerca indietro (`N`), `h` aiuto, `q` esci. Il pager `less` serve anche per i file lunghi (`less file`). L'editor emacs ha una modalità dedicata alle pagine `man`, comoda da usare.

> [!info] Mettiti alla prova
> Esercizio `3.1_Exercises` del prof: **17** (`man` e `less`). Da provare a terminale.
## Variabili e ambiente
Per creare una variabile si usa l'assegnamento, **senza spazi** attorno a `=`: `foo="un valore"` oppure `foo=5`. La si ritrova con il comando `set`.

> [!quote] Definizione — Variabili d'ambiente
> Variabili usate convenzionalmente dalla shell per memorizzare informazioni (es. dove cercare i comandi: **PATH**). A differenza delle variabili ordinarie, sono **condivise con i programmi** che la shell lancia.

- `export foo` rende `foo` una variabile d'ambiente (visibile ai processi figli).
- `echo $PATH` mostra il valore di PATH; `printenv` elenca tutte le variabili d'ambiente.

PATH è tipicamente impostato nei [[#File di configurazione|dotfiles]].

> [!info] Mettiti alla prova
> Esercizio `3.1_Exercises` del prof: **5** (variabili d'ambiente e `PATH`). Da provare a terminale.
## Navigare e gestire il file system
Comandi essenziali: `pwd` (stampa la directory corrente), `ls` (elenca i file), `cd` (cambia directory).
### Percorsi e caratteri speciali
Un percorso è **assoluto** se inizia con `/`, **relativo** se parte dalla *working directory* (non inizia con `/`) — vedi [[07 - File System#Nomi di percorso]]. La shell interpreta alcuni caratteri speciali (*filename expansion*):

| Simbolo | Significato |
|---|---|
| `~` | home directory |
| `.` | directory corrente |
| `..` | directory genitore |
| `*` | wildcard: qualsiasi sequenza di caratteri |
| `?` | wildcard: un singolo carattere |
| `TAB` | completa il nome parzialmente digitato |

Esempi: `cd /usr/local/lib`, `cd ~` (o solo `cd`), `cd ..`, `cd /`, `ls -d pro*` (solo le directory che iniziano per "pro").
### Opzioni utili di ls
`ls -a` (mostra anche i nascosti), `-l` (formato lungo), `-lh` (dimensioni leggibili), `-lt` (ordina per data — molto utile), `-lR` (ricorsivo), `-ld` (la directory e non il suo contenuto), `-F` (aggiunge un carattere indicatore del tipo), `-lS` (ordina per dimensione).
### Comandi su file e directory
| Comando | Funzione |
|---|---|
| `cp file1 file2` | copia |
| `mv file dest` | sposta / rinomina |
| `rm file` (`-r` ricorsivo) | rimuove |
| `mkdir` / `rmdir` | crea / rimuove directory (vuota) |
| `touch file` | crea un file vuoto / aggiorna il timestamp |
| `cat` / `tac` | mostra un file / lo mostra al contrario |
| `head -n` / `tail -n` | prime / ultime n righe |
| `less file` | scorre il file pagina per pagina |
| `file` | identifica il tipo di un file |
| `od` | dump del contenuto (anche binario) |
| `ln -s file nuovo` | crea un link simbolico |

> [!example] Manipolazione tipica
> ```bash
> cd                                     # torna alla home
> mkdir test && cd test
> echo 'Hello everyone' > myfile.txt     # crea (sovrascrive)
> echo 'Goodbye all' >> myfile.txt       # accoda
> less myfile.txt                        # mostra il file
> mkdir subdir1/subdir2                   # FALLISCE (manca il genitore)
> mkdir -p subdir1/subdir2                # riesce (-p crea la catena)
> mv myfile.txt subdir1/subdir2
> cd ..
> rmdir test                              # FALLISCE (non vuota)
> rm -rf test                             # riesce (ricorsivo, forzato)
> ```
> `rmdir` cancella solo directory **vuote**; `rm -rf` rimuove ricorsivamente — **attenzione**, è irreversibile.
### Link simbolici
A volte conviene raggiungere un file da più punti della gerarchia: in Windows si crea uno «shortcut», in Linux un **link simbolico**. Esempio della slide: `mkdir foo` (crea la directory), `touch foo/bar` (crea un file vuoto), `ln -s foo/bar .` crea il link simbolico nella directory corrente. La differenza tra hard link e soft link è trattata in [[02 - Concetti di Base e Strutture#File speciali e pipe]].
### Cercare file: find
Il comando `find` localizza file in alberi profondi (sintassi un po' ostica):
- `find . -name my-file.txt` cerca per nome a partire da `.`
- `find ~ -name bu -type d` cerca **directory** chiamate "bu" nella home
- `find ~ -name '*.txt'` cerca tutti i `.txt` (gli apici evitano che la shell espanda `*` prima di passarlo a `find`)
- `find . -type f -empty` trova i **file vuoti** (dimensione zero) *(extra, non da slide)*

**`-exec`: eseguire un comando sui file trovati** *(extra, non da slide)*. Variante `\;` (un'invocazione per file) e `+` (tutti i file in un'unica chiamata, più efficiente):
```bash
find . -name '*.log' -exec wc -l {} \;    # conta righe in ogni .log (un wc per file)
find . -name '*.log' -exec wc -l {} +    # stesso risultato, un solo wc per tutti
find . -type f -empty -exec rm {} +       # rimuove tutti i file vuoti
```
`{}` è il segnaposto che viene sostituito dal nome del file trovato. Vedi applicazioni pratiche in [[09 - Linux e BASH (Esercizi)]].

> [!info] Mettiti alla prova
> Esercizi `3.1_Exercises` del prof: **1, 22, 23** (file, directory, link simbolici), **25** (`ls` avanzato) e **Bonus** (`tar`), da provare a terminale; **24** (`find`), svolto in [[09 - Linux e BASH (Esercizi)#Es. 24 — Ricerca file con `find` (nome, tipo, azione)|Es. 24]].
## Redirezione e pipe
È il cuore della filosofia Unix — comporre piccoli programmi. Per capirla serve il concetto di **file descriptor standard**.
### I tre stream standard
*(extra, non da slide)* Le slide usano solo `|`, `>` e `>>`; la redirezione di stderr compare nell'esercitazione.

Quando la shell lancia un processo, gli consegna **già tre file descriptor aperti** (interi, gli stessi di `open`/`read`/`write` POSIX visti in [[02 - Concetti di Base e Strutture#Categorie principali di system call POSIX]]):

| fd | Nome | Default |
|---|---|---|
| 0 | **stdin** | tastiera |
| 1 | **stdout** | terminale |
| 2 | **stderr** | terminale |

Un programma fa `write` su fd 1 per l'output normale e su fd 2 per gli errori, **senza sapere** dove puntano davvero.

> [!info] Cosa fa davvero la redirezione (il nesso con POSIX)
> La redirezione **non** è una magia della shell: tra `fork` ed `execve` (vedi il [[02 - Concetti di Base e Strutture#Protezione e shell|ciclo della shell]]) la shell **cambia dove punta un fd** *prima* di avviare il programma. `comando > file` fa sì che fd 1 punti a `file` invece che al terminale; il programma continua a fare `write` su fd 1, ignaro di tutto. Per questo `stdin`/`stdout`/`stderr` sono solo un caso particolare dei file descriptor POSIX.
### Operatori di redirezione
*(extra, non da slide)* Le slide mostrano solo `>` (crea) e `>>` (accoda) nell'esempio sulla manipolazione dei file e `> users` nell'ultima pipeline.

| Sintassi | Effetto |
|---|---|
| `> file` (o `1> file`) | redirige **stdout** su `file` (sovrascrive) |
| `>> file` | redirige stdout su `file` (**accoda**) |
| `2> file` | redirige **stderr** su `file` |
| `2>&1` | redirige stderr **sullo stesso fd** di stdout |
| `< file` | prende **stdin** da `file` |

Esempi: `ls /etc /pippo > out.txt 2> err.txt` separa output ed errori; `comando > tutto.txt 2>&1` li unisce nello stesso file.
### Il comando `w`
`w` mostra gli **utenti attualmente connessi** al sistema e cosa stanno eseguendo (TTY, da quanto sono connessi, programma in esecuzione). Nelle slide è il comando sorgente delle pipeline di esempio (`w  # show who's logged on`):
```bash
w                        # elenco utenti + processo in primo piano
w | wc -l               # quante righe (= quanti utenti + 2 righe header)
w | grep 'danilo'       # c'è danilo connesso?
```
La riga `w | wc -l` è *(extra, non da slide)*.
### Le pipe
> [!quote] Definizione — Pipe
> L'operatore `|` collega lo **stdout** di un comando allo **stdin** del successivo, formando una **pipeline**. È l'uso pratico della [[02 - Concetti di Base e Strutture#File speciali e pipe|pipe come canale FIFO]] tra processi.

> [!example] Pipeline tipiche
> ```bash
> w | less                          # pagina l'output di w
> w | grep 'danilo'                 # solo le righe con 'danilo'
> w | grep -v 'danilo'              # solo le righe SENZA 'danilo'
> w | grep 'danilo' | sed s/danilo/scholar/g   # filtra e sostituisce
> w | wc                            # conta righe, parole, caratteri
> w | awk -F" " '{print $1}' | less        # estrae la prima colonna, la pagina con less
> w | awk -F" " '{print $1}' | sort        # utenti ordinati (con duplicati)
> w | awk -F" " '{print $1}' | sort | uniq        # utenti unici
> w | awk -F" " '{print $1}' | sort | uniq > users  # ...salvati su file
> ```

> [!question] Domanda tipica d'esame
> - **D:** Cosa fa il comando `ls /etc /xyz > out.txt 2>&1`? Cosa finisce in `out.txt`? **R:** `> out.txt` redirige **stdout** (fd 1) su `out.txt`. `2>&1` redirige **stderr** (fd 2) sullo stesso file descriptor di stdout, cioè anch'esso su `out.txt`. Quindi in `out.txt` finiscono sia l'elenco dei file in `/etc` sia il messaggio di errore «No such file or directory» per `/xyz`. Senza `2>&1`, l'errore apparirebbe solo a terminale.
> - **D:** Qual è la differenza tra `>` e `>>` nella redirezione? E tra `|` e `>`? **R:** `> file` **sovrascrive** il file (lo crea se non esiste); `>> file` **accoda** in fondo senza cancellare il contenuto precedente. La pipe `|` connette lo stdout di un processo allo stdin di un altro processo in parallelo (senza file intermedio); `>` scrive su un file disco.

> [!info] Mettiti alla prova
> Esercizio `3.1_Exercises` del prof: **6** (redirezione di input/output e log). Da provare a terminale (non è tra gli esercizi svolti in [[09 - Linux e BASH (Esercizi)]]).
## Permessi dei file
Il concetto è introdotto in [[02 - Concetti di Base e Strutture#Diritti di accesso]]; qui la pratica con **`chmod`**. Ogni file ha permessi **read/write/execute** per **owner**, **group** e **other**, visibili con `ls -l`:
```
-rw-r--r-- 1 tuta0 tutorial 0 Sep 4 10:25 foo
```
(owner `rw-`, group `r--`, other `r--`). Il file della slide si crea con `touch foo`.
### chmod simbolico
Lettere: `u`=owner, `g`=group, `o`=other, `a`=all; permessi `r`/`w`/`x`; operatori `+`/`-`/`=`:
- `chmod ug+x foo` → aggiunge *execute* a owner e group: da `-rw-r--r--` si passa a `-rwxr-xr--`.
- `chmod a-x foo` → toglie *execute* a tutti: si torna a `-rw-r--r--`.
### chmod ottale
read = **4**, write = **2**, execute = **1**, sommati per ogni tripletta:

| # | Permesso | rwx |
|---|---|---|
| 0 | nessuno | `000` |
| 1 | x | `001` |
| 2 | w | `010` |
| 3 | wx | `011` |
| 4 | r | `100` |
| 5 | rx | `101` |
| 6 | rw | `110` |
| 7 | rwx | `111` |

Esempio della slide: `chmod 660 foo` → `-rw-rw----` (4+2=6 per owner e group, other `0`). `chmod 744 foo` → `rwxr--r--` *(extra, non da slide)*.

> [!warning] x sulle directory *(extra, non da slide)*
> Sulla directory il bit `x` non significa "eseguire" ma **attraversare**: senza `x` non si può entrare nella directory né accedere ai file al suo interno, anche se i file hanno i permessi giusti (vedi [[02 - Concetti di Base e Strutture#Diritti di accesso]]).

> [!question] Domanda tipica d'esame
> - **D:** Cosa rappresenta il permesso `chmod 644 file`? Esprimi sia in ottale sia in simbolico. **R:** `6` = `110` = `rw-` (owner: lettura e scrittura); `4` = `100` = `r--` (group: solo lettura); `4` = `100` = `r--` (other: solo lettura). In simbolico equivale a `chmod u=rw,go=r file`. È il permesso tipico di un file di testo: il proprietario lo modifica, gli altri lo leggono.
> - **D:** Quale differenza c'è tra `chmod +x dir` e `chmod +r dir` su una directory? *(extra, non da slide)* **R:** `+x` aggiunge il permesso di **attraversamento** (entrare nella directory con `cd`, accedere ai file dentro); `+r` aggiunge il permesso di **lettura dell'elenco** (fare `ls`). Senza `x` si può avere `r` ma non si riesce ad accedere ai file al suo interno; è una combinazione rara ma significativa.

> [!info] Mettiti alla prova
> Esercizio `3.1_Exercises` del prof: **15** (`chmod` simbolico e ottale). Da provare a terminale (non è tra gli esercizi svolti in [[09 - Linux e BASH (Esercizi)]]).
## Eseguire comandi e script
- **Comando nel PATH**: basta il nome, `command_name` (se l'eseguibile sta in una directory del [[#Variabili e ambiente|PATH]]).
- **Eseguibile nella directory corrente**: `./executable_name` (il prefisso `./` dice "è qui"), previo `chmod +x`.
- **Script bash**: `bash scriptname.sh`, oppure renderlo eseguibile e lanciarlo con `./`.
- Esempi della slide: comando semplice `ls -l`; script nella directory corrente `./my_script.sh`; esecuzione in background `./long_task.sh &`.

> [!quote] Definizione — Shebang
> La prima riga di uno script può indicare l'interprete con `#!` (**shebang**): `#!/bin/bash` per Bash, `#!/usr/bin/python3` per Python. Così `./script` viene eseguito dall'interprete giusto, senza chiamarlo esplicitamente: `./my_script.sh` gira con Bash se in cima c'è `#!/bin/bash`, `./my_script.py` con Python se in cima c'è `#!/usr/bin/python3`.

> [!example] Script con parametri e variabili (countdown.sh)
> Script `countdown.sh` dell'esercitazione del professore (le slide rimandano a `cat countdown.sh`), usato negli esercizi di job control:
> ```bash
> #!/bin/bash
> # Check if a parameter is given
> if [ "$#" -ne 1 ]; then
>     echo "Usage: $0 <starting_number>"
>     exit 1
> fi
> START_NUM=$1
> for i in $(seq $START_NUM -1 1); do
>     echo $i
>     sleep $((RANDOM % 3))
> done
> ```
> `$#` = numero di argomenti; `$0` = nome dello script; `$1` = primo argomento; `$(seq …)` è una [[#Anatomia di un comando|sostituzione di comando]] e `$((…))` una sostituzione aritmetica. Dall'esercitazione, non dalle slide: il ciclo `for i in $(seq …); do … done` ripete il corpo per ogni valore prodotto da `seq` (qui da `START_NUM` a 1, con passo −1); `if [ … ]; then … fi` esegue il blocco se la condizione è vera (`-ne` = «diverso», confronto numerico); `exit 1` termina lo script con codice di errore; `sleep n` attende n secondi e `RANDOM` è una variabile della shell che dà un intero casuale, quindi `$((RANDOM % 3))` vale 0, 1 o 2 *(extra, non da slide)*. Per usarlo: `chmod +x countdown.sh`, poi lo si esegue per qualche secondo e lo si interrompe con Ctrl-C.
## Processi e job control
Ogni programma in esecuzione è un [[03 - Processi e Thread|processo]] numerato (PID).
- `ps` elenca i tuoi processi (e, con le opzioni giuste, anche quelli degli altri); `ps -ef` dà un elenco lungo di tutti quelli del sistema; `ps -ef | grep nome` filtra (es. `ps -ef | grep danilo` mostra i processi degli utenti della classe).
- `top` mostra, aggiornandosi ogni pochi secondi, i maggiori consumatori di CPU (utile per ragionare sullo [[05 - Scheduling|scheduling]]).
### Foreground e background
Di default un comando gira in **foreground**: la shell aspetta che finisca. Con `&` gira in **background** e la shell torna subito al prompt:
```bash
mycommand &
[1] 54356          # [job number] e PID
```
- **Ctrl-C** termina il processo in foreground (invia [[03 - Processi e Thread#I segnali|SIGINT]] *(extra, non da slide)*).
- **Ctrl-Z** sospende il processo in foreground; poi `bg` lo fa ripartire in background, `fg` lo riporta in foreground.
- `jobs` elenca i job della shell; `bg 2` / `fg 2` agiscono sul job n°2.
- `kill PID` (es. `kill 56894`, l'identificatore a cinque cifre) oppure `kill %n` (per *job number*, es. `kill %1`) terminano un processo inviandogli un [[03 - Processi e Thread#I segnali|segnale]].
- Se si avvia un programma e poi si decide di mandarlo in background: `countdown 200 > c.out`, **Ctrl-Z** per sospenderlo, `bg` per farlo proseguire in background, `fg` per riportarlo in foreground. Con più processi sospesi si usa `jobs` e poi `bg`/`fg` con il numero del job (es. `bg 2`).

> [!example] Sequenza tipica
> ```bash
> countdown 20 > c.txt &   # background, output su file (così non disturba)
> jobs                     # elenca i job
> ps                       # vedi il processo
> kill %1                  # termina il job 1
> ```
### Sessioni persistenti: screen e nohup
Per processi lunghi che devono **sopravvivere alla disconnessione** del terminale:
- **`screen`**: gestore di sessioni del terminale. `screen` avvia una sessione; `Ctrl+A` poi `D` la **stacca** (*detach*) lasciandola viva (si può prima avviare un comando nella sessione); `screen -ls` elenca le sessioni; `screen -r <id>` la ri-aggancia (*reattach*), anche dallo stesso o da un altro terminale; `Ctrl+D` termina la sessione. Mantiene i processi attivi anche se la connessione cade e permette più finestre in una sessione.
- **`nohup`** ("no hang up"): `nohup comando &` fa proseguire il comando anche dopo la chiusura del terminale; l'output va in **`nohup.out`** se non rediretto. Esempi della slide: `nohup ./data_processing_script.sh &` (script che non si ferma al logout); `nohup ./heavy_task.sh > output.log 2> errors.log &`.

| | `screen` | `nohup` |
|---|---|---|
| Persistenza di sessione | sì, ri-agganciabile | no, gira staccato in modo permanente |
| Più finestre | sì | no |
| Uso tipico | task lunghi **interattivi** | task **non interattivi** in background |

> [!question] Domanda tipica d'esame
> - **D:** Cosa succede se si usa Ctrl+Z su un processo in foreground? Come si fa poi a riportarlo in esecuzione? **R:** Ctrl+Z invia il segnale di **sospensione** al processo in foreground: il processo viene messo in pausa e il controllo torna alla shell. Da lì: `fg` lo riporta in **foreground** (torna a girare nel terminale); `bg` lo manda in **background** (continua a girare senza occupare il terminale); `jobs` elenca tutti i job sospesi o in background con il loro numero; `kill %n` lo termina.
> - **D:** Qual è la differenza tra `screen` e `nohup` per far sopravvivere un processo alla chiusura del terminale? **R:** Entrambi sopravvivono alla disconnessione. `nohup comando &` stacca il processo in modo **permanente**: non è ri-agganciabile, l'output va in `nohup.out`. `screen` crea una sessione **ri-agganciabile** (`screen -r`): si può rientrare, interagire, usare più finestre nella stessa sessione. Per task non interattivi va bene `nohup`; per task interattivi o lunghi con output da monitorare si preferisce `screen`.

> [!info] Mettiti alla prova
> Esercizi `3.1_Exercises` del prof: **7, 8, 9, 10** (script `countdown.sh`, job control). Da provare a terminale; nel file [[09 - Linux e BASH (Esercizi)]] non sono svolti.
## File di configurazione
I file di configurazione iniziano con `.` (**dotfiles**, *hidden files*, nascosti di default) e non compaiono con `ls`: servono `ls -a` o `ls -al`. Bash legge più file di avvio al login: alcuni sono protetti dal sistema, altri stanno nella home e si possono personalizzare.
- **`.bash_profile`** (si visualizza con `less` o `cat`): eseguito al **login**; qui di solito è impostato PATH.
- **`.bashrc`**: eseguito a ogni **nuova shell**; sede tipica degli **alias**, es. `alias rm='rm -i'` (chiede conferma prima di cancellare).
- Gestione alias: `alias` (elenca tutti), `unalias rm` (lo rimuove subito), `which rm` o `type rm` (verifica se è attivo).
- Per rimuoverlo stabilmente si modifica `.bashrc` con un editor (gedit, emacs, vim) e si commenta la riga con `#` all'inizio; l'effetto si vede alla creazione della **successiva** shell Bash.
## Utility di elaborazione del testo
Strumenti combinabili in [[#Redirezione e pipe|pipeline]]:

| Comando | Funzione |
|---|---|
| `cat` / `tac` | mostra un file / lo mostra al contrario |
| `less` | mostra i file pagina per pagina |
| `head` / `tail` | prime / ultime righe |
| `grep` | cerca un pattern (vedi [[#Espressioni regolari]]) |
| `sed` | *stream editor* (in particolare search & replace) |
| `awk` | linguaggio di scansione/elaborazione per campi |
| `cut` | estrae colonne/campi |
| `sort` / `uniq` | ordina / rimuove duplicati adiacenti |
| `wc` | conta righe, parole, caratteri |
| `tr` | traduce/elimina caratteri |
| `diff` | confronta due file |
| `split` | divide un file in più parti |
| `od` | dump (anche binario) |
| `tar` | archivia (vedi [[07 - File System#Creazione di archivi]]) |

> [!example] Combinazioni frequenti *(extra, non da slide)*
> ```bash
> sort parole.txt | uniq -c | sort -nr      # frequenza decrescente
> cut -f1,4 studenti.tsv                     # colonne 1 e 4 (TSV)
> awk -F'\t' '$4>=28' studenti.tsv           # righe con voto >= 28
> tr 'A-Z' 'a-z' < frasi.txt                 # tutto minuscolo
> ```

**`awk`** — linguaggio di elaborazione per campi (colonne): *(extra, non da slide: le slide mostrano solo `awk -F" " '{print $1}'` e `sed s/danilo/scholar/g` nelle pipeline)*
- Sintassi base: `awk 'pattern { azione }' file`; se omessa l'azione è `{print}`.
- `-F'\t'` imposta il **separatore di campo** (tab nell'esempio; `-F':'` per i due punti, `-F','` per CSV). Le variabili `$1`, `$2`, … sono le colonne; `$0` è la riga intera; `NR` è il numero di riga; `NF` il numero di campi.
- Condizione numerica: `awk -F'\t' '$4>=28' studenti.tsv` → stampa le righe in cui la 4ª colonna è ≥ 28.
- Calcoli: `awk -F'\t' '{sum+=$4} END {print sum/NR}' studenti.tsv` → media del voto.
- Se il file ha l'intestazione (come `studenti.tsv`), la si salta con `NR>1`: `awk -F'\t' 'NR>1 && $4>=28'` e `awk -F'\t' 'NR>1 {s+=$4; n++} END {print s/n}'`.
- Output selettivo: `awk -F'\t' '{print $1, $3}' studenti.tsv` → solo colonne 1 e 3, separate da spazio.

Vedi esempi con output reale in [[09 - Linux e BASH (Esercizi)]].

**`sed`** — *stream editor*, opera riga per riga: *(extra, non da slide: le slide mostrano solo `awk -F" " '{print $1}'` e `sed s/danilo/scholar/g` nelle pipeline)*
- Sostituzione: `sed 's/vecchio/nuovo/' file` sostituisce la **prima occorrenza** per riga; con il flag `g` **tutte**: `sed 's/danilo/scholar/g'`.
- `-i` modifica il file **in place** (sovrascrive il file originale): `sed -i 's/foo/bar/g' file.txt`. Attenzione: non c'è undo senza backup.
- Eliminare righe che corrispondono a un pattern: `sed '/^#/d' file` (cancella le righe di commento).

**`cut`** — estrae campi o colonne: *(extra, non da slide)*
- `cut -f2,4 file` estrae i campi **2 e 4** (separatore tab di default).
- `-d','` cambia il delimitatore: `cut -d',' -f1,3 file.csv` estrae le colonne 1 e 3 da un CSV.
- `-c5-10` estrae i **caratteri** dalla posizione 5 alla 10 (utile per file a larghezza fissa).

**`tr`** — traduce o elimina caratteri (legge da stdin): *(extra, non da slide)*
- `tr 'A-Z' 'a-z' < file` converte tutto in **minuscolo**; `tr 'a-z' 'A-Z'` in maiuscolo.
- `-d` **cancella** i caratteri dell'insieme: `tr -d '0-9' < file` rimuove tutte le cifre.
- `-s` **comprime** le ripetizioni consecutive: `tr -s ' ' < file` riduce più spazi a uno solo.
- `-c` usa il **complemento** dell'insieme: `tr -cd 'a-z\n'` mantiene solo lettere minuscole e newline, cancella tutto il resto.

**`od`** — dump del contenuto (anche binario): *(extra, non da slide)*
- `od -t x1 file` mostra i byte in **esadecimale** (utile per ispezionare file binari o caratteri non stampabili).
- `od -c file` mostra i byte come **caratteri** con le sequenze di escape C (es. `\n`, `\t`, `\0`).
- `od -An -t x1 file` come sopra ma senza l'offset iniziale (flag `-An`).

**`split` / `seq`** — dividere e generare sequenze: *(extra, non da slide)*
- `seq 1 1000 > f` genera i numeri **1..1000** su righe separate (un numero per riga) e li salva in `f`.
- `seq 1 2 99` genera i dispari 1, 3, 5, … 99 (primo, passo, ultimo).
- `split -l 100 f parte_` spezza `f` in blocchi da **100 righe** ciascuno, con nomi `parte_aa`, `parte_ab`, `parte_ac`, … (suffisso alfabetico automatico).
- `split -b 1M file.bin blocco_` spezza per dimensione (1 MiB per blocco).

> [!info] Mettiti alla prova
> Esercizi `3.1_Exercises` del prof su filtri e testo: **2, 3, 4, 12, 13, 14, 16, 18, 19, 20, 21** (`awk`, `sed`, `cut`, `tr`, `od`, `split`, `sort`/`uniq`). Svolti con output reale in [[09 - Linux e BASH (Esercizi)]] i numeri **[[09 - Linux e BASH (Esercizi)#Es. 3 — Manipolazione con grep, awk, sed|3]]**, **[[09 - Linux e BASH (Esercizi)#Es. 16 — Tipo di file e ispezione binaria (`file`, `od`)|16]]**, **[[09 - Linux e BASH (Esercizi)#Es. 19 — Selezione colonne con `cut` (TSV)|19]]**, **[[09 - Linux e BASH (Esercizi)#Es. 20 — Trasformazioni con `tr`|20]]**, **[[09 - Linux e BASH (Esercizi)#Es. 21 — Suddividere file con `split` e ricomporre|21]]**; gli altri sono da provare a terminale.

> [!question] Domanda tipica d'esame
> - **D:** Come si estrae la lista degli utenti unici da `w` usando una pipeline? **R:** `w | awk -F" " '{print $1}' | sort | uniq`. `awk` estrae la prima colonna (il nome utente), `sort` ordina (necessario perché `uniq` rimuove solo i **duplicati adiacenti**), `uniq` rimuove i duplicati. Per salvare il risultato su file si aggiunge `> users` in fondo.
> - **D:** Qual è la differenza tra `sed 's/a/b/' file` e `sed 's/a/b/g' file`? **R:** Senza `g`, `sed` sostituisce solo la **prima occorrenza** di `a` per ogni riga; con il flag `g` (*global*) sostituisce **tutte le occorrenze** nella riga. Es. sulla riga `aaa`: senza `g` → `baa`; con `g` → `bbb`.
## Espressioni regolari
Molti strumenti (**grep**, **sed**) usano stringhe che descrivono sequenze di caratteri: le **regular expression** (*grep* = *general regular expression parser*).

| Pattern | Significato |
|---|---|
| `^foo` | la riga **inizia** con "foo" |
| `bar$` | la riga **finisce** con "bar" |
| `[0-9]\{3\}` | un numero di **3 cifre** |
| `.*a.*e.*i.*o.*u.*` | parole con le vocali **in ordine** (per provarlo su un dizionario la slide indica lo script `~/linux-materials/scripts/vowels.sh`) |

> [!example] Regex in pratica con `grep`
> ```bash
> grep '^foo' file         # righe che INIZIANO con "foo"
> grep 'bar$' file         # righe che FINISCONO con "bar"
> grep -E '[0-9]{3}' file  # righe con almeno 3 cifre consecutive (-E = regex estese)
> grep '^$' file           # righe vuote
> ```
> Con `grep -E` (o `egrep`) le graffe `{3}` si scrivono direttamente; con `grep` classico vanno protette: `[0-9]\{3\}`. Le ultime due righe (`grep -E '[0-9]{3}'` e `grep '^$'`) sono *(extra, non da slide)*.

> [!question] Domanda tipica d'esame
> - **D:** Cosa seleziona il pattern `^foo` in `grep`, e in cosa differisce da `foo$`? **R:** `^foo` seleziona le righe che **iniziano** con "foo" (il simbolo `^` àncora il pattern all'inizio della riga); `foo$` seleziona quelle che **finiscono** con "foo" (`$` àncora alla fine). Combinati, `^foo$` seleziona le righe che contengono *esattamente* "foo".

> [!info] Mettiti alla prova
> Esercizi `3.1_Exercises` del prof: **4** (punti 5-6) e **11** (regex con `grep`). Da provare a terminale; nel file [[09 - Linux e BASH (Esercizi)]] non sono svolti.
## Creare utenti (useradd)
`useradd` è un'utilità **di basso livello** per aggiungere utenti su Ubuntu. Sintassi: `sudo useradd -s /percorso/shell -d /home/{dirname} -m -G {gruppo-secondario} {username}`. Esempio della slide: `sudo useradd -s /bin/bash -d /home/vivek/ -m -G sudo vivek` crea l'utente `vivek`: `-s` shell di login, `-d` home directory, `-m` crea la home, `-G` gruppo secondario (opzionale: con `sudo` il nuovo utente può a sua volta usare `sudo`, cioè ha accesso da amministratore). Poi `sudo passwd vivek` imposta la password. **`sudo`** esegue un comando come **root** (l'utente che lo usa deve avere i privilegi di root; vedi [[02 - Concetti di Base e Strutture|UID e superuser]]).
## Editor di testo
- **emacs**: «coltellino svizzero», con modalità per tutti i principali linguaggi, personalizzabile all'infinito (Emacs Lisp). La curva di apprendimento, un tempo ripida, si è ridotta con menu e barre degli strumenti; funziona con o senza X Window.
- **vim**: versione migliore di `vi` (uno dei primi editor a schermo intero); in mani esperte è efficiente e veloce, popolare tra i sistemisti. Non richiede X Window.
- **gedit**: in stile Notepad con alcune funzioni da programmazione (es. evidenziazione delle parole chiave); richiede X Window (ambiente grafico).
- **nano**: editor leggero, senza X Window.

> [!info] Le tre modalità di Vim
> - **Normal**: navigazione e manipolazione (frecce o `j k l m …` come scritto nella slide; in vim i tasti di movimento sono `h j k l` *(extra, non da slide)*; `p` incolla il testo copiato (*put*), `x` cancella il carattere sotto il cursore, `dd` cancella la riga corrente, `:` entra in command mode).
> - **Insert**: inserimento di testo (si entra con `i`, si esce con `ESC`).
> - **Visual**: selezione (si entra con `v`, `y` copia/yank).
> Command mode (da `:`): `:q` esci, `:q!` esci senza salvare, `:w nomefile` scrive il file, `:help` aiuto (molto esteso).
## Collegamenti con altri argomenti
> [!info] Mappa dei rimandi
> - **Shell come ciclo fork/execve, system call POSIX, file descriptor, pipe come IPC** → [[02 - Concetti di Base e Strutture]]
> - **Processi, segnali (SIGINT/SIGKILL), stati** → [[03 - Processi e Thread]]
> - **`top` e scheduling della CPU** → [[05 - Scheduling]]
> - **Struttura delle directory Linux, `mount`, hard/soft link, `tar`** → [[07 - File System]]
> - **Storia di Unix e Linux** → [[01 - Introduzione ai Sistemi Operativi]]

---
**Argomento precedente:** [[08 - Input Output]] · **Prossimo:** [[10 - Programmazione C e Concorrente]]
