# Linux e BASH
Questa nota copre la parte **pratica** del corso — l'uso di **Linux** e della shell **BASH** (slide 3.1) — complementare ai concetti del [[02 - Concetti di Base e Strutture]]. Là si spiega *cos'è* una shell e *come* il SO espone i suoi servizi (system call, astrazione di file e processo, ciclo `fork`/`execve`); qui si vede *come si usa* davvero il sistema da terminale: comandi, redirezione, permessi, processi, scripting.
> [!info] Inquadramento nel programma
> Corrisponde al punto «**Unix e Linux (caso di studio)**» del programma. È materiale **pratico**, da eseguire a terminale: gli esercizi di autovalutazione del prof (`3.1_Exercises`) coprono tutti i comandi di questa nota. Fonte originale delle slide: Robert Putnam (Boston University), adattate da Danilo Croce.
## Cos'è Linux
> [!quote] Definizione — Linux
> Linux è un **clone di Unix** (propriamente, il solo **kernel**) avviato nel **1991** e scritto da zero da **Linus Torvalds** con una rete di sviluppatori. Oggi la maggioranza dei server, oltre ad Android e a molti dispositivi embedded, gira su una variante Unix/Linux.

La filosofia Unix (Kernighan & Pike, *The Unix Programming Environment*) è **«small programs that do one thing well»**: la potenza di un sistema viene dalle **relazioni** tra i programmi più che dai singoli programmi. Tanti piccoli strumenti, banali in isolamento, diventano potenti se **combinati** (vedi [[#Redirezione e pipe]] e [[#Utility di elaborazione del testo]]). La storia completa di Unix→Linux è in [[01 - Introduzione ai Sistemi Operativi]].

A differenza di Windows (più dischi `C:`, `D:`), Unix/Linux ha **una sola gerarchia** di file system, ad albero da `/`. La struttura delle directory (`/bin`, `/etc`, `/usr`, …) è già descritta in [[07 - File System#Struttura delle cartelle in Linux]].
## La shell BASH
> [!quote] Definizione — Shell
> Programma che **interpreta i comandi** digitati e li invia al sistema operativo. Fornisce anche comandi interni (*built-in*), strutture di controllo per la programmazione e variabili d'ambiente.

**BASH** = **Bourne-again Shell** (versione GNU della shell scritta da Stephen Bourne intorno al 1977); è la shell di default. Un'alternativa comune è **TCSH**. Il *ciclo interno* della shell — legge un comando, fa `fork`, il figlio fa `execve`, il padre `waitpid` — è descritto in [[02 - Concetti di Base e Strutture#Protezione e shell]].
### Anatomia di un comando
Un comando ha tre parti: **command**, **options**, **parameters**. Esempio: `cal -j 3 1999` → `cal` è il comando, `-j` un'opzione (*switch*), `3` e `1999` i parametri. Le opzioni hanno forma **breve** e **lunga**: `date -u` ≡ `date --universal`. Comandi base per provare: `whoami` (il mio login), `hostname` (nome macchina), `echo "Hello, world"`, `echo $HOME`, `date`, `cal`.
> [!example] Sostituzione di comando (command substitution)
> `echo my login is $(whoami)` → la shell **sostituisce** `$(...)` con l'output del comando interno. Es. `echo "Oggi è $(date)"`.
### History e aiuto
La shell tiene la cronologia dei comandi:
- `history` elenca i comandi recenti; frecce ↑/↓ per scorrerli.
- `!!` ripete l'ultimo comando; `!132` ripete il comando n°132; `!ls` ripete l'ultimo che inizia per `ls`.
- Aiuto: `comando --help`, `man comando`, `help` (built-in BASH), `man bash`.
> [!info] man usa less
> `man` mostra le pagine tramite il pager **`less`**: `Spazio`/`f` pagina avanti, `b` indietro, `<`/`>` inizio/fine, `/pattern` cerca avanti (`n` ripete), `?pattern` cerca indietro (`N`), `h` aiuto, `q` esci.
## Variabili e ambiente
Per creare una variabile si usa l'assegnamento, **senza spazi** attorno a `=`: `foo="un valore"` oppure `foo=5`. La si ritrova con il comando `set`.
> [!quote] Definizione — Variabili d'ambiente
> Variabili usate convenzionalmente dalla shell per memorizzare informazioni (es. dove cercare i comandi: **PATH**). A differenza delle variabili ordinarie, sono **condivise con i programmi** che la shell lancia.

- `export foo` rende `foo` una variabile d'ambiente (visibile ai processi figli).
- `echo $PATH` mostra il valore di PATH; `printenv` elenca tutte le variabili d'ambiente.

PATH è tipicamente impostato nei [[#File di configurazione|dotfiles]].
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
> mkdir test && cd test
> echo 'Hello everyone' > myfile.txt     # crea (sovrascrive)
> echo 'Goodbye all' >> myfile.txt       # accoda
> mkdir subdir1/subdir2                   # FALLISCE (manca il genitore)
> mkdir -p subdir1/subdir2                # riesce (-p crea la catena)
> mv myfile.txt subdir1/subdir2
> cd ..
> rmdir test                              # FALLISCE (non vuota)
> rm -rf test                             # riesce (ricorsivo, forzato)
> ```
> `rmdir` cancella solo directory **vuote**; `rm -rf` rimuove ricorsivamente — **attenzione**, è irreversibile.
### Link simbolici
`ln -s foo/bar .` crea un **link simbolico** (l'equivalente dello "shortcut" di Windows) nella directory corrente. La differenza tra hard link e soft link è trattata in [[02 - Concetti di Base e Strutture#File speciali e pipe]].
### Cercare file: find
Il comando `find` localizza file in alberi profondi (sintassi un po' ostica):
- `find . -name my-file.txt` cerca per nome a partire da `.`
- `find ~ -name bu -type d` cerca **directory** chiamate "bu" nella home
- `find ~ -name '*.txt'` cerca tutti i `.txt` (gli apici evitano che la shell espanda `*` prima di passarlo a `find`)
## Redirezione e pipe
È il cuore della filosofia Unix — comporre piccoli programmi. Per capirla serve il concetto di **file descriptor standard**.
### I tre stream standard
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
| Sintassi | Effetto |
|---|---|
| `> file` (o `1> file`) | redirige **stdout** su `file` (sovrascrive) |
| `>> file` | redirige stdout su `file` (**accoda**) |
| `2> file` | redirige **stderr** su `file` |
| `2>&1` | redirige stderr **sullo stesso fd** di stdout |
| `< file` | prende **stdin** da `file` |

Esempi: `ls /etc /pippo > out.txt 2> err.txt` separa output ed errori; `comando > tutto.txt 2>&1` li unisce nello stesso file.
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
> w | awk -F" " '{print $1}' | sort | uniq        # utenti unici
> w | awk -F" " '{print $1}' | sort | uniq > users  # ...salvati su file
> ```
## Permessi dei file
Il concetto è introdotto in [[02 - Concetti di Base e Strutture#Diritti di accesso]]; qui la pratica con **`chmod`**. Ogni file ha permessi **read/write/execute** per **owner**, **group** e **other**, visibili con `ls -l`:
```
-rw-r--r-- 1 tuta0 tutorial 0 Sep 4 10:25 foo
```
(owner `rw-`, group `r--`, other `r--`).
### chmod simbolico
Lettere: `u`=owner, `g`=group, `o`=other, `a`=all; permessi `r`/`w`/`x`; operatori `+`/`-`/`=`:
- `chmod ug+x foo` → aggiunge *execute* a owner e group.
- `chmod a-x foo` → toglie *execute* a tutti.
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

Esempi: `chmod 660 foo` → `rw-rw----` (owner e group `6`=rw, other `0`); `chmod 744 foo` → `rwxr--r--`.
> [!warning] x sulle directory
> Sulla directory il bit `x` non significa "eseguire" ma **attraversare**: senza `x` non si può entrare nella directory né accedere ai file al suo interno, anche se i file hanno i permessi giusti (vedi [[02 - Concetti di Base e Strutture#Diritti di accesso]]).
## Eseguire comandi e script
- **Comando nel PATH**: basta il nome, `command_name` (se l'eseguibile sta in una directory del [[#Variabili e ambiente|PATH]]).
- **Eseguibile nella directory corrente**: `./executable_name` (il prefisso `./` dice "è qui"), previo `chmod +x`.
- **Script bash**: `bash scriptname.sh`, oppure renderlo eseguibile e lanciarlo con `./`.
> [!quote] Definizione — Shebang
> La prima riga di uno script può indicare l'interprete con `#!` (**shebang**): `#!/bin/bash` per Bash, `#!/usr/bin/python3` per Python. Così `./script` viene eseguito dall'interprete giusto, senza chiamarlo esplicitamente.

> [!example] Script con parametri e variabili (countdown.sh)
> Esempio del corso, usato negli esercizi di job control:
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
> `$#` = numero di argomenti; `$0` = nome dello script; `$1` = primo argomento; `$(seq …)` è una [[#Anatomia di un comando|sostituzione di comando]] e `$((…))` una sostituzione aritmetica.
## Processi e job control
Ogni programma in esecuzione è un [[03 - Processi e Thread|processo]] numerato (PID).
- `ps` elenca i tuoi processi; `ps -ef` tutti quelli del sistema; `ps -ef | grep nome` filtra.
- `top` mostra in tempo reale i maggiori consumatori di CPU (utile per ragionare sullo [[05 - Scheduling|scheduling]]).
### Foreground e background
Di default un comando gira in **foreground**: la shell aspetta che finisca. Con `&` gira in **background** e la shell torna subito al prompt:
```bash
mycommand &
[1] 54356          # [job number] e PID
```
- **Ctrl-C** invia [[03 - Processi e Thread#I segnali|SIGINT]] e termina il processo in foreground.
- **Ctrl-Z** sospende il processo in foreground; poi `bg` lo fa ripartire in background, `fg` lo riporta in foreground.
- `jobs` elenca i job della shell; `bg 2` / `fg 2` agiscono sul job n°2.
- `kill PID` oppure `kill %n` (per *job number*) terminano un processo inviandogli un [[03 - Processi e Thread#I segnali|segnale]].
> [!example] Sequenza tipica
> ```bash
> countdown 20 > c.txt &   # background, output su file (così non disturba)
> jobs                     # elenca i job
> ps                       # vedi il processo
> kill %1                  # termina il job 1
> ```
### Sessioni persistenti: screen e nohup
Per processi lunghi che devono **sopravvivere alla disconnessione** del terminale:
- **`screen`**: gestore di sessioni del terminale. `screen` avvia una sessione; `Ctrl+A` poi `D` la **stacca** (*detach*) lasciandola viva; `screen -ls` elenca le sessioni; `screen -r <id>` la ri-aggancia (*reattach*). Permette più finestre in una sessione.
- **`nohup`** ("no hang up"): `nohup comando &` fa proseguire il comando anche dopo la chiusura del terminale; l'output va in **`nohup.out`** se non rediretto. Es. `nohup ./task.sh > output.log 2> errors.log &`.

| | `screen` | `nohup` |
|---|---|---|
| Persistenza | sì, ri-agganciabile | sì, ma staccato in modo permanente |
| Più finestre | sì | no |
| Uso tipico | task lunghi **interattivi** | task **non interattivi** in background |
## File di configurazione
I file di configurazione iniziano con `.` (sono **dotfiles**, *hidden files*) e non compaiono con `ls`: servono `ls -a` o `ls -al`.
- **`.bash_profile`**: eseguito al **login**; qui di solito è impostato PATH.
- **`.bashrc`**: eseguito a ogni **nuova shell**; sede tipica degli **alias**, es. `alias rm='rm -i'` (chiede conferma prima di cancellare).
- Gestione alias: `alias` (elenca tutti), `unalias rm` (lo rimuove subito), `which rm` (verifica se è attivo). Per rimuoverlo stabilmente si commenta la riga in `.bashrc` con `#`.
## Utility di elaborazione del testo
Strumenti combinabili in [[#Redirezione e pipe|pipeline]]:

| Comando | Funzione |
|---|---|
| `cat` / `tac` | mostra un file / lo mostra al contrario |
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

> [!example] Combinazioni frequenti
> ```bash
> sort parole.txt | uniq -c | sort -nr      # frequenza decrescente
> cut -f1,4 studenti.tsv                     # colonne 1 e 4 (TSV)
> awk -F'\t' '$4>=28' studenti.tsv           # righe con voto >= 28
> tr 'A-Z' 'a-z' < frasi.txt                 # tutto minuscolo
> ```
## Espressioni regolari
Molti strumenti (**grep**, **sed**) usano stringhe che descrivono sequenze di caratteri: le **regular expression** (*grep* = *general regular expression parser*).

| Pattern | Significato |
|---|---|
| `^foo` | la riga **inizia** con "foo" |
| `bar$` | la riga **finisce** con "bar" |
| `[0-9]\{3\}` | un numero di **3 cifre** |
| `.*a.*e.*i.*o.*u.*` | parole con le vocali **in ordine** |
## Creare utenti (useradd)
`sudo useradd -s /bin/bash -d /home/vivek/ -m -G sudo vivek` crea l'utente: `-s` shell di login, `-d` home directory, `-m` crea la home, `-G` gruppo secondario (`sudo` = privilegi admin). Poi `sudo passwd vivek` imposta la password. **`sudo`** esegue un comando come **root** (vedi [[02 - Concetti di Base e Strutture|UID e superuser]]).
## Editor di testo
- **emacs**: estensibile all'infinito (Emacs Lisp), con modalità per ogni linguaggio.
- **vim**: erede di `vi`, efficiente e veloce, popolare tra i sistemisti.
- **gedit**: in stile Notepad (richiede ambiente grafico).
- **nano**: editor leggero da terminale.
> [!info] Le tre modalità di Vim
> - **Normal**: navigazione e manipolazione (frecce o `j k l`, `x` cancella un carattere, `dd` cancella la riga, `p` incolla, `:` entra in command mode).
> - **Insert**: inserimento di testo (si entra con `i`, si esce con `ESC`).
> - **Visual**: selezione (si entra con `v`, `y` copia/yank).
> Command mode (da `:`): `:q` esci, `:q!` esci senza salvare, `:w file` salva, `:help` aiuto.
## Collegamenti con altri argomenti
> [!info] Mappa dei rimandi
> - **Shell come ciclo fork/execve, system call POSIX, file descriptor, pipe come IPC** → [[02 - Concetti di Base e Strutture]]
> - **Processi, segnali (SIGINT/SIGKILL), stati** → [[03 - Processi e Thread]]
> - **`top` e scheduling della CPU** → [[05 - Scheduling]]
> - **Struttura delle directory Linux, `mount`, hard/soft link, `tar`** → [[07 - File System]]
> - **Storia di Unix e Linux** → [[01 - Introduzione ai Sistemi Operativi]]

---
**Argomento precedente:** [[08 - Input Output]] · **Prossimo:** [[10 - Programmazione C e Concorrente]]
