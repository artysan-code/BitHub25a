# Processi e Thread
Il **processo** è l'astrazione con cui il SO esegue programmi per conto degli utenti; il **thread** è il flusso di esecuzione *dentro* un processo. Questa nota copre modello, gestione, stati, segnali/interrupt e thread. Prerequisito: l'astrazione di processo introdotta in [[02 - Concetti di Base e Strutture]].

> [!info] Per il laboratorio
> La pratica di questa nota — `fork`/`exec`/`wait`, segnali, pipe, pthreads — si scrive in **C**. Se segui l'ordine delle lezioni, vedi prima [[10 - Programmazione C e Concorrente]] (le system call in C) e [[09 - Linux e BASH]] (shell e terminale): nelle slide il laboratorio precede questa teoria, mentre qui l'ordine segue il libro.
## Il modello di processo
> [!quote] Definizione — Processo
> Un **processo è un programma in esecuzione**. È un'astrazione fondamentale del SO, che gli consente di semplificare **allocazione**, **accounting** (contabilizzazione) e **limitazione** delle risorse. Il SO mantiene in una **tabella dei processi** le informazioni sulle risorse e sullo stato interno di ogni processo.

Con la multiprogrammazione la CPU passa rapidamente da un processo all'altro (**process switch**): a livello fisico esiste **un solo program counter** e **un solo processo è attivo** in un dato istante, ma concettualmente ogni processo ha il **proprio flusso di controllo** (il proprio program counter logico). A ogni cambio si **salva il PC** del processo uscente e si **ripristina** quello entrante. Il risultato è uno **pseudo-parallelismo**: tutti i processi progrediscono, ma uno solo alla volta usa davvero la CPU *(slide 2025-2026; nel 2026-2027 la precisazione è «per CPU», vedi [[#Processi concorrenti]])*.
### Processi concorrenti
In linea di principio i processi sono **reciprocamente indipendenti**: per interagire hanno bisogno di **mezzi espliciti** (vedi [[04 - Sincronizzazione]]). La CPU è assegnata a turno e il SO **non offre garanzie di tempistica né di ordine** di esecuzione: non si può quindi assumere *quando* o *in che ordine* i processi verranno eseguiti.

**Concorrenza e parallelismo** *(slide 2026-2027, p. 7)*: su una **singola CPU** più processi possono avanzare nel tempo condividendo la CPU, ma in un dato istante **uno solo** è in esecuzione su quella CPU; il SO li alterna con **cambi di contesto** (*context switch*). Sui sistemi **multicore** più processi possono invece essere eseguiti **realmente in parallelo**, su core differenti. *Idea chiave*: **concorrenza e parallelismo non sono sinonimi**. La slide 2026-2027 (p. 4) apre inoltre con la domanda «Quanti processi per ogni programma?».
### Gerarchie di processi
Nei sistemi UNIX-like i processi formano una **gerarchia** *(slide 2026-2027, p. 9)*: un processo può creare uno o più **processi figli**; ogni processo ha un identificatore (**PID**) e normalmente un **processo padre** (**PPID**). All'avvio il kernel lancia il **primo processo in spazio utente**, generalmente con **PID 1**, che nei sistemi Linux moderni è spesso **`systemd`**.

*(Slide 2025-2026)* Il SO crea in genere un solo processo iniziale, **`init`** (nei sistemi moderni `init` avvia anche **`kthreadd`**, processo che gestisce i thread del kernel). Da lì i processi si creano **in modo indipendente**: un processo **padre** crea un processo **figlio**, generando una **struttura ad albero** e **gruppi di processi**.

> [!example] La shell crea processi
> ```bash
> $ find /tmp > t.log &
> $ ls | more
> ```
> Ogni comando lanciato dalla shell diventa un processo figlio; `init → login → sh → (ls, find, more)` è un tipico albero *(extra, non da slide: la catena `login → sh`; la slide cita solo `init` e i comandi della shell)*.
>
> Slide 2026-2027: il primo comando esegue `find` **in background** e ne salva l'output nel file `t.log`; il secondo collega due programmi attraverso una **pipe**.

L'uso pratico della shell e del **job control** (`ps`, `kill`, `bg`/`fg`, `&`) è in [[09 - Linux e BASH#Processi e job control]].

> [!question] Domanda tipica d'esame
> **D:** Cos'è un processo e in cosa differisce da un programma? **R:** Un processo è un *programma in esecuzione*: è l'istanza dinamica di un programma statico, dotata di proprio spazio di indirizzi, stato della CPU (registri, PC, stack) e risorse (file aperti, segnali). Il programma è il codice statico su disco; il processo è l'entità a cui il SO alloca la CPU e le risorse.
## Gestione dei processi
### Creazione di un processo
Quattro eventi principali causano la creazione di un processo:
1. **Inizializzazione** del sistema.
2. Esecuzione di una **system call di creazione** da parte di un processo già in esecuzione (`fork()`). ^fork
3. **Richiesta dell'utente** di creare un nuovo processo (es. da shell).
4. **Avvio di un lavoro batch**.
### Terminazione di un processo
Quattro condizioni tipiche:
1. **Uscita normale** (volontaria).
2. **Uscita per errore** (volontaria — il programma rileva l'errore e termina).
3. **Errore fatale** (involontario — es. istruzione illegale).
4. **Ucciso da un altro processo** (involontario, via segnale).
### System call di gestione
| Call              | Cosa fa                                                                                                                                                                                                          |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `fork`            | Crea un nuovo processo figlio. *(Slide 2026-2027)* Il figlio riceve uno **spazio di indirizzamento logicamente equivalente** a quello del padre; alcune risorse sono **ereditate o condivise**, come i riferimenti ai file aperti. *(Slide 2025-2026)* Il figlio è un **clone "privato"** del genitore; condivide *alcune* risorse (file aperti con offset condiviso, segmento di codice, variabili d'ambiente e directory corrente ereditate). |
| `exec` (`execve`) | **Sostituisce** l'immagine del processo con un nuovo programma: *(slide 2026-2027)* **non crea un nuovo processo**, il **PID rimane invariato**. *(Slide 2025-2026)* Usata in combinazione con `fork`.                  |
| `exit`            | Terminazione **volontaria**; lo *stato di uscita* è restituito al processo **genitore**.                                                                                                                         |
| `kill`            | Invia un **segnale** a un processo (o a un gruppo). *(Slide 2026-2027)* **Non provoca necessariamente la terminazione.** *(Slide 2025-2026)* Può causare la terminazione **involontaria**.                         |
| `waitpid`         | *(Slide 2026-2027)* Permette al padre di **attendere un figlio** e raccoglierne lo **stato di terminazione**.                                                                                                    |

Schema tipico della shell *(slide 2026-2027, p. 12)*: `fork()` → `execve()` → `waitpid()`.

> [!info] Codice di laboratorio
> Esempi C su `fork`, `exec`, segnali e pipe in `Materiale Didattico/Sistemi Operativi/Esempi/5_elementi_di_programmazione_concorrente_code/`. Il pattern `fork` + `exec` + `waitpid` è quello della shell visto in [[02 - Concetti di Base e Strutture]]. La trattazione in C di `fork`/`exec`/`wait`, dei segnali (`signal`/`alarm`/`kill`) e delle pipe (`pipe`/`dup2`) è in [[10 - Programmazione C e Concorrente]].

> [!question] Domanda tipica d'esame
> **D:** Cosa fa `fork()` e in che modo è usata con `exec`? **R:** `fork()` crea un nuovo processo figlio come clone "privato" del genitore: condividono il segmento di codice e le variabili d'ambiente ereditate, ma hanno spazi di indirizzi separati. Il valore di ritorno distingue padre (PID del figlio) da figlio (0). `exec` (nella forma `execve`) sostituisce poi l'immagine del processo figlio con un nuovo programma: il pattern `fork` + `exec` + `wait` è quello usato dalla shell per lanciare comandi.

> [!info] Mettiti alla prova
> - **Teorico:** conteggio processi da `fork` → [[03 - Processi e Thread (Esercizi)#Es. 1 — Conteggio processi: `fork` sequenziali|Es. 1]] e [[03 - Processi e Thread (Esercizi)#Es. 2 — `fork` dentro un ciclo|Es. 2]]; duplicazione del buffer (`fflush` prima della `fork`) → [[03 - Processi e Thread (Esercizi)#Es. 4 — Duplicazione del buffer: `printf` prima della `fork`|Es. 4]].
> - **Tracce d'esame:** tutte le [[Tracce d'Esame Pratiche#Processi|tracce P1–P10]] usano `fork`/`exec`/`wait`/`kill`.
> - **C:** [[Indice degli Esercizi#Processi|fork_sum.c]] (fork + pipe + `SIGTERM`) e [[Indice degli Esercizi#Processi|matrix_fork.c]] (fork + calcolo parallelo su pipe).
## Stati di un processo
Un processo può trovarsi in **tre stati**:
- **Running** (in esecuzione): sta effettivamente usando la CPU.
- **Ready** (pronto): eseguibile, temporaneamente fermo per lasciare la CPU a un altro.
- **Blocked** (bloccato): non eseguibile finché non si verifica un **evento esterno** (es. arrivo di input).

Il SO alloca la CPU tenendo traccia di questi stati; è lo **[[05 - Scheduling|scheduler]]** a (de)assegnare la CPU. Lo stato evolve secondo quattro transizioni:

```text
Running ──(1) si blocca in attesa di input──►  Blocked
Running ──(2) lo scheduler sceglie un altro──►  Ready
Ready   ──(3) lo scheduler sceglie questo────►  Running
Blocked ──(4) l'input diventa disponibile────►  Ready
```

Il corso adotta il modello a **tre stati** *operativi*: la **creazione** e la **terminazione** del processo (le sezioni precedenti) sono **eventi** agli estremi del ciclo di vita, non stati stazionari del diagramma — un processo «non finisce mai» *nel diagramma* perché questo descrive solo la fase in cui è *vivo* e contende la CPU. Alcuni testi rendono espliciti due stati aggiuntivi — **new** *(extra, non da slide)* (appena creato, non ancora ammesso tra i *ready*) e **terminated/zombie** (ha già fatto `exit`, ma la sua voce resta finché il genitore non ne raccoglie lo stato di uscita con `wait`) — ma **non sono nelle slide di Croce**, che si fermano ai tre stati.

> [!question] Domanda tipica d'esame
> **D:** Quali sono i tre stati di un processo e le quattro transizioni tra essi? **R:** Gli stati sono **Running** (la CPU è assegnata al processo), **Ready** (eseguibile ma in attesa della CPU) e **Blocked** (non eseguibile, in attesa di un evento esterno). Le transizioni sono: (1) Running→Blocked, quando il processo si blocca in attesa di input; (2) Running→Ready, quando lo [[05 - Scheduling|scheduler]] sceglie un altro processo; (3) Ready→Running, quando lo scheduler sceglie questo processo; (4) Blocked→Ready, quando l'input atteso diventa disponibile.

> [!question] Domanda tipica d'esame
> **D:** Il modello a tre stati (Running/Ready/Blocked) descrive l'intero ciclo di vita del processo? **R:** No: descrive solo la fase *operativa* in cui il processo è vivo e contende la CPU. La **creazione** e la **terminazione** sono **eventi** agli estremi — alla nascita il processo entra come *ready*, e con `exit` lascia il diagramma — non stati di esso. Il corso e il Tanenbaum si fermano a tre stati; il modello a cinque stati di altri testi esplicita anche *new* e *terminated/zombie*.
### Informazioni associate a un processo
La **tabella dei processi** è un array di strutture, **una voce per processo**, chiamata anche **PCB** (*Process Control Block*). Conserva tutto ciò che serve a **sospendere e riprendere** un processo come se non si fosse mai fermato: quando passa da *running* a *ready*/*blocked*, il suo stato viene salvato qui. Il SO mantiene le informazioni necessarie a gestire e **riprendere l'esecuzione** di un processo. Secondo la slide 2026-2027 (p. 15) sono:

- **identificazione e protezione**: identificatori (**PID**, **PPID**), credenziali (**UID**, **GID**) e privilegi;
- **memoria e risorse**: **spazio di indirizzamento virtuale**, **file descriptor** e file aperti, directory di lavoro e altre risorse associate;
- **esecuzione**: **stato** del processo (Running, Ready, Blocked), **contesto di esecuzione** (registri, Program Counter, Stack Pointer), informazioni sullo **scheduling** e sui **segnali**.

Queste informazioni sono mantenute dal kernel tramite strutture dati associate ai processi, spesso descritte concettualmente come **tabella dei processi**.

*(Slide 2025-2026)* L'elenco era:

- **ID** (**PID**), **Utente** (**UID**), **Gruppo** (**GID**);
- **spazio degli indirizzi** di memoria;
- **registri hardware** (ad esempio, il Program Counter);
- **file aperti**;
- **segnali** (*signal*);
- **interrupt**.

La slide 2025-2026 precisava che queste informazioni sono memorizzate nella **tabella dei processi** del sistema operativo.

*(Extra, non da slide: la suddivisione in tre aree e i campi della tabella seguente.)* I campi tipici si raggruppano in tre aree:

| Gestione del processo | Gestione della memoria | Gestione dei file |
|---|---|---|
| Registri, **PC**, **PSW**, puntatore allo stack | Puntatore al segmento **testo** (codice) | Directory radice |
| Stato del processo, priorità, parametri di scheduling | Puntatore al segmento **dati** | Directory di lavoro |
| **PID**, processo genitore, gruppo del processo | Puntatore al segmento **stack** | Descrittori dei file aperti |
| Segnali, tempi di CPU (proprio e dei figli), allarmi | | **UID**, **GID** |

I campi di memoria sono ripresi in [[06 - Gestione della Memoria]], quelli dei file in [[07 - File System]]. È sulla voce del PCB che, a ogni **interrupt**, l'hardware e la routine assembly salvano i registri del processo corrente (vedi sotto).

*(Extra, non da slide: chiarimento.)* **Anche il processo in *running* ha la sua voce nel PCB**: la tabella contiene *tutti* i processi e un campo ne registra proprio lo *stato* (`running`/`ready`/`blocked`). Ciò che cambia è *dove* vive lo stato «vivo»: mentre il processo esegue, i suoi registri e il PC stanno nei **registri fisici della CPU**, e la copia nel PCB è quella salvata all'ultimo cambio di contesto (quindi non aggiornata); al successivo **context switch** (running → ready/blocked) l'hardware e la routine assembly riscrivono i registri correnti nella sua voce. Il PCB esiste appunto per poter **sospendere e riprendere** ogni processo, qualunque sia il suo stato.

> [!question] Domanda tipica d'esame
> **D:** Anche il processo in esecuzione (*running*) ha una voce nel PCB, o solo i processi *ready*/*blocked*? **R:** Tutti i processi hanno una voce nella tabella, **incluso quello in *running*** (un campo ne registra lo *stato*). Per il processo in esecuzione lo stato «vivo» (registri, PC) sta nei registri della CPU; la copia nel PCB viene aggiornata al **context switch**, quando il processo lascia la CPU. Il PCB serve proprio a **sospenderlo e riprenderlo** come se non si fosse mai fermato.
## Modellazione della multiprogrammazione
*(Approfondimento dal Tanenbaum, cap. 2 — non presente nelle slide di Croce: utile per capire il «perché» della multiprogrammazione, non materia d'esame stretta.)*

Quanto rende davvero la [[01 - Introduzione ai Sistemi Operativi#Terza generazione (1965-80) — circuiti integrati e multiprogrammazione|multiprogrammazione]]? Un modello **probabilistico** lo quantifica. Se un processo passa una frazione **$p$** del suo tempo in **attesa di I/O**, con **$n$** processi in memoria la probabilità che siano **tutti** in attesa nello stesso istante (CPU inattiva) è $p^n$. L'utilizzo della CPU è quindi:
$$\text{Utilizzo CPU} = 1 - p^n$$
dove **$n$** è il **grado di multiprogrammazione** (numero di processi contemporaneamente in memoria).
Conseguenze pratiche:
- Più processi in memoria → più utilizzo, ma con **rendimenti decrescenti**.
- Se i processi attendono l'I/O l'**80%** del tempo ($p = 0{,}8$), con **10 processi** l'utilizzo è $1 - 0{,}8^{10} \approx 89{,}3\%$, cioè uno spreco di circa il **10,7%**: per scendere **sotto il 10%** di spreco servono almeno **11 processi** ($1 - 0{,}8^{11} \approx 91{,}4\%$, spreco $\approx 8{,}6\%$).
- È un'**approssimazione**: assume i processi **indipendenti** (con una sola CPU non lo sono del tutto — un modello esatto userebbe la **teoria delle code**), ma la conclusione resta valida.

> [!example] Esempio — quanta CPU guadagno aggiungendo RAM?
> Memoria di 8 GB: 2 GB al SO e 2 GB per programma → **3 programmi** in memoria. Con $p = 0{,}8$:
> $$\text{Utilizzo} = 1 - 0{,}8^3 = 1 - 0{,}512 \approx 49\%$$
> Salendo a 16 GB → **7 programmi**: $1 - 0{,}8^7 \approx 79\%$ (**+30%** di throughput). Altri 8 GB portano dal 79% a circa il **91%** (solo **+12%**): il primo upgrade conviene, il secondo molto meno.

> [!question] Domanda tipica d'esame
> **D:** Qual è la formula dell'utilizzo della CPU in multiprogrammazione e cosa significano i suoi termini? **R:** $\text{Utilizzo CPU} = 1 - p^n$, dove **$p$** è la frazione di tempo che un processo passa in **attesa di I/O** e **$n$** è il **grado di multiprogrammazione** (processi in memoria). Il termine $p^n$ è la probabilità che **tutti** gli $n$ processi attendano l'I/O nello stesso istante, lasciando la **CPU inattiva**. Il modello assume i processi indipendenti, quindi è un'approssimazione.
## Segnali e interrupt
Sia i **segnali** sia gli **interrupt** servono a gestire **eventi asincroni**, ma a livelli diversi. La tabella seguente è della slide 2025-2026.

| | Interrupt | Segnale (signal) |
|---|---|---|
| **Origine** | dispositivi **hardware** (tastiera, disco) | eventi **software** (da un processo o dal SO) |
| **Gestione** | routine di servizio (**ISR**) | handler personalizzato o azione di default |
| **Uso** | comunicazione hardware↔software | condizioni eccezionali nelle applicazioni |
| **Asincronia** | gestiti **immediatamente** dall'hardware | inviati in modo **asincrono**, ma il processo può gestirli in modo sincrono |

Slide 2026-2027 (p. 16):
- **Interrupt hardware**: generati da dispositivi hardware o da meccanismi come il **timer**; interrompono temporaneamente il normale flusso di esecuzione della CPU; il controllo passa a un gestore del kernel (**interrupt handler**), che permette al SO di reagire agli eventi hardware.
- **Segnali** (*signals*): notifiche gestite dal kernel e dirette a processi o thread; possono essere generati da altri processi, dal terminale o da eventi di esecuzione; possono causare la **terminazione**, la **sospensione** o l'esecuzione di un **handler**.
- Esempi: timer hardware → interrupt; `Ctrl+C` → il terminale provoca l'invio di `SIGINT` al **gruppo di processi in foreground**; accesso non valido alla memoria → tipicamente `SIGSEGV`.
- *Idea chiave*: gli **interrupt** sono gestiti dal kernel; i **segnali** sono uno dei meccanismi con cui il kernel notifica eventi ai processi.
### Gli interrupt
**Idea** *(slide 2025-2026)*: per togliere la CPU a un processo e ridarla allo scheduler ci si appoggia al supporto hardware agli interrupt, così lo **scheduler ottiene periodicamente il controllo** — ogni volta che l'hardware genera un interrupt (formulazione 2025-2026; nel 2026-2027 non ogni interrupt provoca un cambio di processo).

L'**interrupt vector** è associato a ciascun dispositivo di I/O e linea di interrupt, fa parte della **IDT** (Interrupt Descriptor Table) e contiene l'indirizzo iniziale del **gestore di interrupt** fornito dal SO. Tipi di interruzione: **software**, **dispositivo hardware (asincrono)**, **eccezioni**.

*(Slide 2026-2027, p. 17)* Il problema è come il SO possa **riprendere il controllo della CPU** mentre un programma è in esecuzione. Un dispositivo hardware può generare un interrupt; un **timer** genera interrupt che permettono al kernel di verificare se sia opportuno cambiare il processo in esecuzione; la CPU interrompe il flusso corrente e passa a un gestore del kernel. L'**interrupt vector** identifica il gestore associato a un evento; nell'architettura **x86** la **IDT** contiene i descrittori necessari a individuarlo. **Attenzione: non ogni interrupt provoca un cambio di processo.** *Idea chiave*: gli interrupt permettono al kernel di riprendere il controllo; lo scheduler decide, quando necessario, quale processo o thread eseguire.

> [!example] Cosa succede a un interrupt (livello più basso del SO) — slide 2025-2026
> 1. L'hardware **impila** il Program Counter e le info del processo.
> 2. L'hardware carica il **nuovo PC** dal vettore di interrupt.
> 3. La procedura **assembly salva i registri**.
> 4. La procedura assembly **imposta un nuovo stack**.
> 5. Viene eseguito il **servizio di interrupt in C** (tipicamente legge il buffer d'input).
> 6. Lo **scheduler** decide quale processo eseguire dopo.
> 7. La procedura C ritorna al codice assembly.
> 8. L'assembly **avvia il processo** scelto.

> [!example] Schema semplificato di un interrupt — slide 2026-2027, p. 18
> 1. Un dispositivo o un timer **genera un interrupt**.
> 2. La CPU **salva le informazioni essenziali** per poter riprendere l'esecuzione.
> 3. La CPU **passa al gestore** dell'interrupt nel kernel.
> 4. Il kernel **gestisce l'evento**, eventualmente salvando ulteriori registri e informazioni di contesto.
> 5. Se necessario, il kernel può **invocare lo scheduler** per scegliere un altro processo o thread.
> 6. Il sistema **ripristina il contesto** appropriato e riprende l'esecuzione.
>
> Due esiti possibili: **nessun cambio di contesto** (riprende il processo interrotto) oppure **cambio di contesto** (viene eseguito un altro processo o thread). *Idea chiave*: gestire un interrupt e cambiare processo sono **due operazioni distinte**; la seconda non è sempre necessaria.

> [!warning] Lo scheduler è il mediatore
> *(Slide 2025-2026)* A ogni interruzione lo scheduler ottiene il controllo: **un processo non può cedere la CPU a un altro (context switch) senza passare attraverso lo scheduler**. *(Slide 2026-2027: lo scheduler viene invocato solo «se necessario» e non ogni interrupt provoca un cambio di processo.)*

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> Il salvataggio dei registri e la commutazione a livello assembly sono trattati in [[07 - Livello del linguaggio Assemblativo]]; gli interrupt come dispositivo hardware sono ripresi in [[08 - Input Output]].
### I segnali
Esempi di segnali POSIX *(slide 2026-2027, p. 19)*: `SIGINT` (richiesta di interruzione, tipicamente da `Ctrl+C`), `SIGTERM` (richiesta di terminazione), `SIGKILL` (terminazione forzata), `SIGSEGV` (accesso non valido alla memoria), `SIGSTOP`/`SIGCONT` (sospensione e ripresa), `SIGPIPE` (scrittura su una pipe senza lettori). Quando arriva un segnale il processo può, a seconda del segnale, **eseguire l'azione predefinita**, **ignorarlo** o **eseguire un handler personalizzato** (*signal handler*). *Idea chiave*: un segnale non significa necessariamente terminazione del processo.

*(Slide 2025-2026)*
- **Tipi**: indotti da hardware (es. `SIGKILL`) o da software (es. `SIGQUIT`, `SIGPIPE`).
- **Azioni** possibili: `Term`, `Ign`, `Core`, `Stop`, `Cont`. Ogni segnale ha un'azione di **default**, tipicamente **sovrascrivibile**; i segnali possono essere **bloccati** e le azioni ritardate.
- **Catching**: il processo registra un **handler**; il SO consegna il segnale e fa eseguire l'handler; il contesto corrente va salvato/ripristinato.

La parola «**tipicamente**» (sovrascrivibile, bloccabile) è importante: a differenza di un **interrupt** hardware — che il processo *non* può rifiutare — un segnale è di norma **mascherabile**, cioè catturabile con un handler, ignorabile o bloccabile. Fanno eccezione **due segnali «forti»**, `SIGKILL` (termina) e `SIGSTOP` (sospende): **non** possono essere catturati, ignorati né bloccati, e in questo senso hanno verso il processo una «forza» paragonabile a quella di un interrupt. *(Slide 2026-2027, p. 20: «SIGKILL e SIGSTOP non possono essere intercettati, ignorati o bloccati»; per molti altri segnali si può installare un handler o impedirne temporaneamente la consegna tramite una **maschera**.)*

> [!question] Domanda tipica d'esame
> **D:** Un segnale può essere «forte» come un interrupt, cioè non rifiutabile dal processo? **R:** Di norma **no**: il segnale è software ed è **mascherabile** (il processo può catturarlo, ignorarlo o bloccarlo), mentre un **interrupt** hardware non è rifiutabile dal processo. L'eccezione sono i due segnali **non mascherabili** `SIGKILL` e `SIGSTOP`: non si possono catturare, ignorare né bloccare, e in quel caso il segnale è «forte» quanto un interrupt nei confronti del processo.
#### Permessi e consegna
Slide 2026-2027 (p. 22): un processo può inviare segnali ad altri processi **se dispone dei permessi necessari**; nei sistemi UNIX-like il kernel **verifica le credenziali** del mittente e del destinatario, e i processi con **privilegi appropriati** possono inviare segnali anche a processi di altri utenti. *(Slide 2025-2026)* Un processo può inviare segnali **solo a processi dello stesso utente** (il kernel controlla **UID/EUID** → niente `Ctrl+C` ai processi di root). L'invio (`kill`) è una **system call**: il segnale viene **accodato nel kernel** al processo/thread target.

Ogni processo (o thread) ha nel kernel una struttura con: **segnali pendenti** (in attesa di consegna), **maschera dei segnali bloccati** (temporaneamente sospesi) e **tabella delle disposizioni** (per ogni segnale: default, ignorato o handler personalizzato). Alla consegna il kernel verifica prima se il segnale può essere consegnato *(slide 2026-2027, p. 22)*.

Alla consegna, se è registrato un **handler utente** il kernel: **salva il contesto** (registri, PC, SP, flag), **prepara lo stack del segnale** e imposta l'indirizzo dell'handler. L'handler viene eseguito in **user space**; al termine un *trampolino* invoca la system call **`rt_sigreturn`**, con cui il kernel **ripristina il contesto** e **riprende il PC originale**. Se **non** c'è handler, si applica la **disposizione di default** (termina, ignora o sospende, a seconda del segnale). *(Slide 2026-2027: il kernel prepara il contesto per eseguire l'handler in spazio utente e al termine ripristina normalmente il contesto interrotto; `rt_sigreturn` e il «trampolino» sono della slide 2025-2026.)*

*(Slide 2026-2027)* **Non tutti i segnali sono accodati singolarmente**: più occorrenze dello stesso segnale standard possono essere rappresentate da un'**unica condizione pendente**.
#### Esempio: gestire Ctrl+C (SIGINT)
```c
void signalHandler(int signum) {
    printf("Interrupt signal %d received\n", signum);
    // cleanup e terminazione
    exit(signum);
}
int main() {
    signal(SIGINT, signalHandler);   // registra handler per SIGINT (Ctrl+C)
    while (1) {
        printf("Going to sleep....\n");
        sleep(1);
    }
    return 0;
}
```

> [!question] Domanda tipica d'esame
> **D:** Qual è la differenza tra interrupt e segnale? **R:** Un **interrupt** è generato da un dispositivo *hardware* (tastiera, disco) e gestito da una ISR (Interrupt Service Routine) del SO tramite il vettore di interrupt (IDT); interrompe temporaneamente il processo corrente e passa a un gestore del kernel, che può (non sempre) invocare lo [[05 - Scheduling|scheduler]] per cambiare processo. Un **segnale** è un meccanismo *software* che notifica a un processo un evento (es. `SIGINT` da Ctrl+C, `SIGKILL` per forzare la terminazione): il processo può registrare un handler, ignorarlo (se il segnale lo permette) o accettare l'azione di default. La consegna avviene tramite il kernel, che salva il contesto corrente, esegue l'handler in user space e lo ripristina via `rt_sigreturn`.

> [!info] Mettiti alla prova
> - **C:** [[Indice degli Esercizi#Processi|fork_sum.c]], [[Indice degli Esercizi#Processi|fork_pari_dispari_soglia.c]] e [[Indice degli Esercizi#Processi|26_01_24_appello.c]] terminano i figli con `kill(pid, SIGTERM)`.
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Processi|P2]], [[Tracce d'Esame Pratiche#Processi|P6]], [[Tracce d'Esame Pratiche#Processi|P10]].
## Thread
Finora abbiamo assunto **1 processo ⇒ 1 thread**. Con l'esecuzione **multithreaded** un processo ha **N thread**. Perché più thread per processo? Sono **lightweight process** (processi leggeri): consentono **parallelismo efficiente** in spazio e tempo e una **comunicazione/sincronizzazione semplici** (condividono lo **spazio di indirizzi**).

> [!example] Usi tipici
> Un **word processor** con tre thread (interazione tastiera, riformattazione, salvataggio su disco) resta reattivo mentre lavora in background. Un **web server multithread** ha un **dispatcher thread** che riceve le richieste e le passa ai **worker thread**, sfruttando una **web page cache** condivisa.
>
> Schema di massima del codice (slide "Utilizzo dei thread (2)"):
> ```c
> // (a) dispatcher thread
> while (TRUE) {
>     get_next_request(&buf);
>     handoff_work(&buf);
> }
>
> // (b) worker thread
> while (TRUE) {
>     wait_for_work(&buf);
>     look_for_page_in_cache(&buf, &page);
>     if (page_not_in_cache(&page))
>         read_page_from_disk(&buf, &page);
>     return_page(&page);
> }
> ```
### Thread e processi
I thread **risiedono nello stesso spazio di indirizzi di un singolo processo**: tutti gli scambi avvengono **tramite dati condivisi** (e i thread si sincronizzano con [[04 - Sincronizzazione|semplici primitive]]). Ogni thread ha però **stack**, **registri hardware** e **stato** propri, cioè un proprio **contesto di esecuzione** (registri, program counter, stack); *(slide 2026-2027)* le informazioni necessarie alla sua gestione sono mantenute dalla **libreria dei thread** o dal **kernel**, secondo il modello di implementazione. *(Slide 2025-2026)* La tabella dei thread è più leggera di quella dei processi. Ciascun thread può effettuare qualsiasi system call per conto del processo a cui appartiene.

| Per processo (condiviso) | Per thread (privato) |
|---|---|
| Spazio di indirizzi | Program counter |
| Variabili globali | Registri |
| File aperti | Stack |
| Processi figli | Stato |
| Allarmi pendenti | |
| Segnali e relativi handler | |
| Informazioni di accounting | |
### Thread POSIX (pthreads)
| Chiamata | Descrizione |
|---|---|
| `pthread_create` | Crea un nuovo thread |
| `pthread_exit` | Termina il thread chiamante |
| `pthread_join` | Attende l'uscita di uno specifico thread |
| `pthread_yield` | Rilascia la CPU per un altro thread |
| `pthread_attr_init` | Crea e inizializza la struttura di attributi |
| `pthread_attr_destroy` | Rimuove la struttura di attributi |

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_THREADS 10
void *print_hello_world(void *tid) {
    printf("Hello World. Greetings from thread %d\n", tid);
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);
        if (status != 0) exit(-1);
    }
    return 0;
}
```

> [!warning] Output non deterministico — domanda del docente
> Il `main` **non chiama `pthread_join`**: termina (con `return 0`) senza attendere il completamento dei thread figli. L'ordine in cui i 10 thread eseguono `printf` dipende dallo **scheduler**, che non offre garanzie di tempistica né di ordine (cfr. [[#Processi concorrenti]]). L'output osservabile può essere qualsiasi permutazione dei messaggi, o addirittura incompleto se il processo termina prima che tutti i thread abbiano stampato. *"What will the output be?"* — la risposta corretta è: **non si può sapere a priori**.

> [!info] Codice di laboratorio
> Esempi su thread, producer-consumer e reader-writer in `Materiale Didattico/Sistemi Operativi/Esempi/6_thread_e_sincronizzazione/`.

> [!info] Mettiti alla prova
> - **C — pthreads:** [[Indice degli Esercizi#Thread e Sincronizzazione|pos_neg_one_thread_mutex.c]], [[Indice degli Esercizi#Thread e Sincronizzazione|pari_dispari_insert_mutex.c]], [[Indice degli Esercizi#Thread e Sincronizzazione|init_max_min_mutex.c]] — `pthread_create`/`join`/`exit`.
> - **Tracce d'esame:** [[Tracce d'Esame Pratiche#Thread — Mutex|TM1]], [[Tracce d'Esame Pratiche#Thread — Mutex|TM2]], [[Tracce d'Esame Pratiche#Thread — Mutex|TM3]].
### Implementazione dei thread
Esistono **tre luoghi** di implementazione: nello **spazio utente**, nel **kernel**, o **ibrida**.
#### Nello spazio utente
I thread sono gestiti da una **libreria** in user space, senza che il kernel li conosca individualmente: **N thread utente → 1 thread del kernel** (modello **molti-a-uno, N:1**, nome presente nelle slide 2026-2027, p. 34). La libreria mantiene lo stato di ciascun thread (registri, stack, stato di esecuzione), decide quale eseguire e gestisce il passaggio dall'uno all'altro; il kernel vede **un'unica entità schedulabile**. Quindi i thread utente si alternano, ma **non possono essere eseguiti contemporaneamente su più core**. *Idea chiave*: è la libreria, non il kernel, a schedulare i singoli thread utente.

*Vantaggi del modello N:1 (slide 2026-2027, p. 35)*:
- **portabilità**: può funzionare anche su SO privi di supporto nativo per più thread;
- **cambio di thread leggero**: non richiede necessariamente una chiamata al kernel, quindi **minore overhead** (nessuna transizione user mode → kernel mode);
- **scheduling personalizzabile**: ogni processo può adottare una propria politica di gestione dei thread.

*Limiti (slide 2026-2027, p. 36)*:
- **system call bloccanti**: se un thread esegue una chiamata bloccante, può bloccare **l'intero processo** e quindi tutti i suoi thread;
- **nessun parallelismo reale** tra i thread dello stesso processo su più core;
- **scheduling cooperativo**: il kernel non schedula i thread utente e, senza un meccanismo di *preemption* gestito dalla libreria, i thread devono cedere volontariamente il controllo.

*Idea chiave*: il modello N:1 è leggero, ma limita parallelismo e gestione indipendente dei blocchi.

*(Slide 2025-2026)* Il kernel vede i thread come normali processi a singolo thread (funzionano anche su SO che **non supportano** i thread). Ogni processo ha la **propria tabella dei thread**.
- **Pro**: il cambio tra thread **non richiede un context switch completo** (niente `trap` → **molto più veloce**); si può **personalizzare l'algoritmo di scheduling** per processo; maggiore scalabilità.
- **Contro**: una **system call bloccante** di un thread **ferma tutti** i thread del processo; un **page fault** blocca l'intero processo; **niente interrupt del clock** → impossibile uno scheduling round-robin. Quindi poco adatti ad applicazioni in cui i thread si bloccano spesso (es. web server).
#### Nello spazio kernel
Il SO **conosce e gestisce direttamente** i thread *(slide 2026-2027, p. 37)*: ogni thread ha un proprio **contesto di esecuzione** (registri, Program Counter, stack) e il kernel può **schedularli individualmente**; se un thread si blocca, altri thread dello stesso processo possono continuare; sui sistemi **multicore** più thread dello stesso processo possono eseguire **realmente in parallelo**. Librerie come **Pthreads** offrono le API per creare e coordinare i thread, mentre il kernel ne gestisce esecuzione e scheduling. *Compromesso*: maggiore flessibilità e parallelismo, ma operazioni di gestione potenzialmente **più costose** di quelle fatte interamente in spazio utente.

*(Slide 2025-2026)* Niente sistema run-time per processo. Le chiamate potenzialmente bloccanti sono **system call** (costo più alto), ma se un thread si blocca il kernel può eseguire un altro thread (dello stesso o di un altro processo). Alcuni sistemi **riciclano** i thread per ridurre i costi; a un page fault il kernel verifica se ci sono altri thread eseguibili.
#### Ibrida
Si effettua il **multiplexing** dei thread utente sui **thread del kernel**, combinando i vantaggi dei due approcci. *(Slide 2026-2027)* Il numero di thread del kernel utilizzati dipende dal modello e dall'implementazione della libreria di threading. *(Slide 2025-2026)* Il programmatore decide quanti thread kernel usare e quanti thread utente multiplexare (maggiore flessibilità). Il kernel è consapevole solo dei thread kernel, ma ciascuno di essi può gestire più thread utente. Combina i vantaggi dei due approcci.

*(Extra, non da slide: i nomi dei modelli **M:N** e **1:1**; il nome **N:1** è invece nelle slide 2026-2027.)* Per fissare i termini: un **thread utente** è un flusso che la **libreria** (in user space) crea e avvicenda *senza* che il kernel lo sappia; un **thread kernel** è invece un flusso che il **kernel** conosce e **schedula** direttamente sulla CPU. Il *multiplexing* ibrido **mappa N thread utente su M thread kernel** (con $M \le N$): è il modello **M:N**. *Multiplexing* significa proprio far passare **più** flussi logici (i thread utente) attraverso un **numero minore** di canali realmente schedulabili (i thread kernel), alternandoli — ogni thread kernel è una «corsia» su cui la libreria avvicenda più thread utente. Per confronto, i thread *solo utente* sono il modello **N:1** (tutti mappati sull'unica entità che il kernel vede, il processo) e i thread *solo kernel* sono **1:1** (a ogni thread utente corrisponde un thread kernel).

> [!question] Domanda tipica d'esame
> **D:** Che differenza c'è tra thread utente e thread kernel, e cosa significa farne il *multiplexing* nell'approccio ibrido? **R:** Un **thread utente** è gestito e schedulato da una **libreria** in user space ed è invisibile al kernel; un **thread kernel** è conosciuto e schedulato dal **kernel**. Il *multiplexing* ibrido **mappa N thread utente su M thread kernel** ($M \le N$, modello **M:N**): più thread utente si avvicendano sullo stesso thread kernel, che è l'unità realmente messa in esecuzione. Solo-utente corrisponde a **N:1**, solo-kernel a **1:1**.
### Problemi aperti
La programmazione con thread richiede cautela. *(Slide 2026-2027, p. 39)* Esempio: due thread usano lo **stesso buffer** per preparare un messaggio; il thread A scrive il messaggio nel buffer condiviso e, prima che A lo invii, il thread B modifica lo stesso buffer; quando A riprende, invia il contenuto del buffer. Quale messaggio viene inviato, quello di A o quello di B? Il risultato **dipende dall'ordine** con cui vengono eseguite le operazioni dei due thread: è una **race condition**, trattata nella lezione successiva ([[04 - Sincronizzazione]]). *(Slide 2025-2026)*:
- Molte **procedure di libreria** possono causare **conflitti** se un thread sovrascrive dati cruciali per un altro (es. un buffer condiviso per assemblare un messaggio di rete, sovrascritto da un secondo thread dopo un interrupt del clock). I **wrapper** (un bit "libreria in uso") evitano i conflitti ma limitano il parallelismo → tema della [[04 - Sincronizzazione]].
- La **gestione dei segnali** è complicata: alcuni sono specifici di un thread, altri no, e decidere chi li gestisce è non banale.

> [!question] Domanda tipica d'esame
> **D:** Quali sono i vantaggi dei thread rispetto ai processi e come differiscono le tre implementazioni (user space, kernel, ibrida)? **R:** I thread (processi leggeri) condividono lo spazio di indirizzi del processo, quindi la comunicazione è più rapida e il context switch tra thread è meno costoso di quello tra processi *(extra, non da slide)*. Nell'implementazione **user space** il cambio di thread non richiede necessariamente una trap al kernel (più veloce, scheduling personalizzabile), ma una system call bloccante ferma tutti i thread del processo. Nell'implementazione **kernel** il cambio è una system call (costo maggiore), ma se un thread si blocca il kernel può eseguirne un altro dello stesso processo. L'approccio **ibrido** effettua il multiplexing di N thread utente su M thread kernel, combinando i vantaggi di entrambi.

---
**Argomento precedente:** [[02 - Concetti di Base e Strutture]] · **Prossimo:** [[04 - Sincronizzazione]] — race condition, mutua esclusione, semafori, mutex, monitor e problemi classici di IPC.
