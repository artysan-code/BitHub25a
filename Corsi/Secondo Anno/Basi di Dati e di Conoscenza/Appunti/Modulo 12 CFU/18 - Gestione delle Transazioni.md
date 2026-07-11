## Definizione di transazione

> [!quote] Definizione — Transazione
> Una **transazione** è parte di un programma caratterizzata da un inizio (**begin-transaction**, `start transaction` in SQL), una fine (**end-transaction**, non esplicitata in SQL) e al cui interno deve essere eseguito una e una sola volta uno dei seguenti comandi:
> - **`commit work`** — per terminare correttamente
> - **`rollback work`** — per abortire la transazione

Un **sistema transazionale** (**OLTP** — *Online Transaction Processing*) è in grado di definire ed eseguire transazioni per conto di un certo numero di applicazioni concorrenti.

### Differenza fra applicazione e transazione

Un **programma applicativo** può contenere al suo interno più transazioni distinte, ciascuna delimitata dal proprio `begin`/`end`. Le azioni fra un `begin T` e il corrispondente `end T` costituiscono la transazione T; il programma applicativo può proseguire con altre azioni e delimitare altre transazioni.

> [!example] Una transazione
> ```sql
> start transaction;
> update ContoCorrente
>   set Saldo = Saldo + 10 where NumConto = 12202;
> update ContoCorrente
>   set Saldo = Saldo - 10 where NumConto = 42177;
> commit work;
> ```

> [!example] Una transazione con decisioni
> ```sql
> start transaction;
> update ContoCorrente
>   set Saldo = Saldo + 10 where NumConto = 12202;
> update ContoCorrente
>   set Saldo = Saldo - 10 where NumConto = 42177;
> select Saldo into A
>   from ContoCorrente
>   where NumConto = 42177;
> if (A>=0)  then commit work
>            else rollback work;
> ```

### Transazioni in JDBC

La modalità delle transazioni si sceglie con un metodo dell'interfaccia `Connection`:

```java
setAutoCommit(boolean autoCommit)
```

- **`con.setAutoCommit(true)`** (default): modalità "autocommit", ogni singola operazione è una transazione a sé.
- **`con.setAutoCommit(false)`**: gestione delle transazioni da programma, tramite `con.commit()` e `con.rollback()`; non esiste un comando esplicito `start transaction`.

## Il concetto di transazione: le proprietà ACIDE

Una transazione è un'unità di elaborazione che gode delle proprietà **ACIDE**: **A**tomicità, **C**onsistenza, **I**solamento, **D**urata (persistenza).

### Atomicità

Una transazione è un'unità atomica di elaborazione: **non può lasciare la base di dati in uno stato intermedio**.

- un guasto o un errore *prima* del commit devono causare l'annullamento (**UNDO**) delle operazioni svolte;
- un guasto o errore *dopo* il commit non deve avere conseguenze: se necessario vanno ripetute (**REDO**) le operazioni.

L'**esito** di una transazione è dunque:
- **Commit** — caso "normale" e più frequente (in pratica, la stragrande maggioranza dei casi);
- **Abort** (o rollback):
  - richiesto dall'applicazione stessa (metaforicamente un "suicidio");
  - richiesto dal sistema, a seguito di violazione dei vincoli, di problemi di concorrenza, o di incertezza in caso di fallimento (un "omicidio").

### Consistenza

La transazione rispetta i vincoli di integrità. Conseguenza: se lo stato iniziale della base di dati è corretto, anche lo stato finale è corretto.

### Isolamento

La transazione non risente degli effetti delle altre transazioni **concorrenti**: l'esecuzione concorrente di una collezione di transazioni deve produrre un risultato che si potrebbe ottenere con un'esecuzione sequenziale (seriale). Conseguenza: una transazione non espone i suoi stati intermedi ad altre transazioni, evitando così l'**effetto domino**.

### Durabilità (persistenza)

Gli effetti di una transazione andata in commit non vanno perduti ("durano per sempre"), anche in presenza di guasti: **commit significa impegno**.

## Transazioni e moduli del DBMS

Le quattro proprietà ACID sono garantite da moduli distinti del DBMS:

- **Atomicità e durabilità** → **Gestore dell'affidabilità** (*Reliability manager*)
- **Isolamento** → **Gestore della concorrenza**
- **Consistenza** → **Gestore dell'integrità a tempo di esecuzione** (con il supporto del compilatore del DDL)

Nell'architettura complessiva del DBMS (si veda anche [[17 - Organizzazione Fisica dei Dati]]), il **Gestore delle transazioni** governa il gestore della concorrenza e il gestore dell'affidabilità, entrambi collegati al gestore dei metodi d'accesso e al gestore del buffer, che a loro volta si appoggiano al gestore della memoria secondaria.

# Gestore dell'affidabilità

Il **gestore dell'affidabilità** gestisce l'esecuzione dei comandi transazionali (`start transaction`/**B**egin, `commit work`/**C**, `rollback work`/**A**bort) e le operazioni di ripristino (*recovery*) dopo i guasti (*warm restart* e *cold restart*). Assicura **atomicità** e **durabilità**, usando il **log**: un archivio permanente che registra le operazioni svolte (due metafore classiche: il filo di Arianna, e le briciole di pane di Hansel e Gretel).

### Architettura del controllore dell'affidabilità

```
Gestore dei metodi d'accesso        Gestore delle transazioni
        │ fix, unfix                     │ begin, commit, abort
        └──────────────┬──────────────────┘
              Gestore della affidabilità
                       │ fix, unfix, force (pagine BD e log)
              Gestore del buffer
                       │ read, write
              Gestore della memoria secondaria
                       │
                  BD  /  Log
```

## Persistenza delle memorie

- **Memoria centrale**: non è persistente.
- **Memoria di massa**: è persistente ma può danneggiarsi.
- **Memoria stabile**: memoria che non può danneggiarsi (è un'**astrazione**), perseguita attraverso la ridondanza (dischi replicati, nastri, ...).

## Il log

Il log è un **file sequenziale** gestito dal controllore dell'affidabilità, scritto in memoria stabile: un "diario di bordo" che riporta tutte le operazioni in ordine.

### Record nel log

**Operazioni delle transazioni**:
- `begin`, $B(T)$
- `insert`, $I(T,O,AS)$ — dove $AS$ è l'*after state*
- `delete`, $D(T,O,BS)$ — dove $BS$ è il *before state*
- `update`, $U(T,O,BS,AS)$
- `commit`, $C(T)$, `abort`, $A(T)$

**Record di sistema**:
- `dump`
- `checkpoint`

### Struttura del log

Il log è una sequenza temporale di record. Fra un `dump` e un `checkpoint`, e fra checkpoint successivi, si susseguono i record `begin`, `update`, `commit`, `abort` delle transazioni in corso, fino a un eventuale `crash`.

## Log, checkpoint e dump: a che cosa servono?

- Il **log** serve "a ricostruire" le operazioni.
- **Checkpoint** e **dump** servono ad evitare che la ricostruzione debba partire dall'inizio dei tempi: si usano con riferimento a tipi di guasti diversi.

### Undo e redo

- **Undo** di un'azione su un oggetto $O$:
  - `update`, `delete`: copiare il valore del *before state* ($BS$) nell'oggetto $O$
  - `insert`: eliminare $O$
- **Redo** di un'azione su un oggetto $O$:
  - `insert`, `update`: copiare il valore dell'*after state* ($AS$) nell'oggetto $O$
  - `delete`: reinserire $O$

> [!info] Idempotenza di undo e redo
> $\text{undo}(\text{undo}(A)) = \text{undo}(A)$
>
> $\text{redo}(\text{redo}(A)) = \text{redo}(A)$
>
> Questa proprietà è essenziale: se il ripristino viene interrotto da un ulteriore guasto e deve essere ripetuto, riapplicare undo o redo più volte non altera il risultato.

### Checkpoint

Operazione che serve a "fare il punto" della situazione, semplificando le successive operazioni di ripristino: ha lo scopo di registrare quali transazioni sono attive in un certo istante (e, dualmente, di confermare che le altre o non sono iniziate o sono finite).

> [!example] Paragone (estremo)
> Come la "chiusura dei conti" di fine anno di un'amministrazione: dal 25 novembre (ad esempio) non si accettano nuove richieste di "operazioni" e si concludono tutte quelle avviate prima di accettarne di nuove.

**Modalità più semplice di checkpoint**:
1. si sospende l'accettazione di richieste di ogni tipo (scrittura, inserimenti, ..., commit, abort);
2. si trasferiscono in memoria di massa (tramite `force`) tutte le pagine sporche relative a transazioni andate in commit;
3. si registrano sul log in modo sincrono (`force`) gli identificatori delle transazioni in corso;
4. si riprende l'accettazione delle operazioni.

Così siamo sicuri che: per tutte le transazioni che hanno effettuato il commit i dati sono in memoria di massa; le transazioni "a metà strada" sono elencate nel checkpoint.

### Dump

Copia completa ("di riserva", *backup*) della base di dati:
- solitamente prodotta mentre il sistema non è operativo;
- salvata in memoria stabile, come il file di log, ed è chiamata **backup**;
- un record di `dump` nel log indica il momento in cui il dump è stato effettuato (e dettagli pratici: file, dispositivo, ...).

## Esito di una transazione

L'esito di una transazione è determinato **irrevocabilmente** quando viene scritto il record di **commit** nel log in modo sincrono, con una `force`:
- un guasto *prima* di tale istante porta a un **undo** di tutte le azioni, per ricostruire lo stato originario della base di dati;
- un guasto *successivo* non deve avere conseguenze: lo stato finale della base di dati deve essere ricostruito, con **redo** se necessario.

I record di `abort`, invece, possono essere scritti in modo asincrono.

## Regole fondamentali per il log

- **Write-Ahead-Log (WAL)**: si scrive il log (parte *before*) prima del database → consente di disfare le azioni (undo).
- **Commit-Precedenza**: si scrive il log (parte *after*) prima del commit → consente di rifare le azioni (redo).

Resta da decidere: **quando** scriviamo effettivamente nella base di dati? Ci sono varie alternative (modalità immediata, differita, mista), a seconda di quando avviene la scrittura fisica $w(x)$ nella base di dati rispetto alle scritture nel log $U(T,X,BS,AS)$ e al commit $C$.

### Modalità immediata

Il DB può contenere valori *after state* provenienti da transazioni non ancora in commit (*uncommitted*).

- Richiede **Undo** delle operazioni delle transazioni uncommitted al momento del guasto;
- **Non** richiede Redo.

### Modalità differita

Il DB **non** contiene valori *after state* provenienti da transazioni uncommitted (le scritture fisiche avvengono solo dopo il commit).

- In caso di abort, non occorre fare niente;
- Rende superflua la procedura di Undo;
- Richiede **Redo**.

### Modalità mista

Una terza modalità, in cui la scrittura può avvenire sia in modalità immediata che differita:

- consente l'ottimizzazione delle operazioni di *flush* (il gestore del buffer decide quando è più conveniente scrivere);
- richiede **sia** Undo **che** Redo.

## Guasti

- **Guasti "soft"**: errori di programma, crash di sistema, caduta di tensione.
  - si perde la memoria centrale;
  - non si perde la memoria secondaria;
  - si risolvono con **warm restart** (ripresa a caldo).
- **Guasti "hard"**: sui dispositivi di memoria secondaria.
  - si perde anche la memoria secondaria;
  - non si perde la memoria stabile (e quindi il log);
  - si risolvono con **cold restart** (ripresa a freddo).

### Modello "fail-stop"

Il sistema si trova sempre in uno dei tre stati `Normal`, `Stop`, `Restart`:

```
Normal --Fail--> Stop --Boot--> Restart --Restart completato--> Normal
                  ↑________________Fail_______________________/
```

Un guasto può avvenire sia dallo stato `Normal` sia durante il `Restart` stesso (il che richiede che le procedure di ripristino siano idempotenti, coerentemente con la proprietà di undo e redo vista sopra).

## Processo di restart

**Obiettivo**: classificare le transazioni in:
- **completate** (tutti i dati in memoria stabile);
- **in commit ma non necessariamente completate** (può servire redo);
- **senza commit** (vanno annullate, undo).

### Ripresa a caldo (warm restart)

Quattro fasi:

1. **Trovare l'ultimo checkpoint**, ripercorrendo il log a ritroso.
2. **Costruire gli insiemi UNDO** (transazioni da disfare) e **REDO** (transazioni da rifare), a partire dalle transazioni attive al checkpoint, aggiornandoli man mano che si incontrano `commit` (spostano da UNDO a REDO) e nuovi `begin` (aggiungono a UNDO) procedendo in avanti dal checkpoint fino al crash.
3. **Ripercorrere il log all'indietro**, fino alla più vecchia azione delle transazioni in UNDO e REDO, disfacendo (undo) tutte le azioni delle transazioni in UNDO.
4. **Ripercorrere il log in avanti**, rifacendo (redo) tutte le azioni delle transazioni in REDO.

> [!example] Esempio di warm restart
> Log (semplificato): `B(T1) B(T2) U(T2,O1,B1,A1) I(T1,O2,A2) B(T3) C(T1) B(T4) U(T3,O2,B3,A3) U(T4,O3,B4,A4) CK(T2,T3,T4) C(T4) B(T5) U(T3,O3,B5,A5) U(T5,O4,B6,A6) D(T3,O5,B7) A(T3) C(T5) I(T2,O6,A8)` seguito da **crash**.
>
> **1. Ultimo checkpoint**: `CK(T2,T3,T4)`, con transazioni attive $\{T2, T3, T4\}$.
>
> **2. Costruzione UNDO/REDO** (a partire dal checkpoint, procedendo in avanti):
> - Setup: $UNDO = \{T2,T3,T4\}$, $REDO = \{\}$
> - $C(T4) \to UNDO = \{T2,T3\}$, $REDO = \{T4\}$
> - $B(T5) \to UNDO = \{T2,T3,T5\}$, $REDO = \{T4\}$
> - $C(T5) \to UNDO = \{T2,T3\}$, $REDO = \{T4,T5\}$
>
> Al momento del crash, $T2$ e $T3$ non sono mai andate in commit: restano in UNDO ($T3$ pur avendo un `abort` esplicito, va comunque disfatta).
>
> **3. Fase UNDO** (a ritroso, disfa le azioni di $T2$ e $T3$): si annullano nell'ordine inverso $D(O6)$, $O5=B7$, $O3=B5$, $O2=B3$, $O1=B1$.
>
> **4. Fase REDO** (in avanti, rifà le azioni di $T4$ e $T5$): si riapplicano $O3=A4$, $O4=A6$.

### Ripresa a freddo (cold restart)

1. Si ripristinano i dati a partire dal **backup** (dump).
2. Si eseguono le operazioni registrate sul **log** fino all'istante del guasto.
3. Si esegue una **ripresa a caldo**.

# Controllo di concorrenza

La concorrenza è fondamentale: decine o centinaia di transazioni al secondo (**tps**, *Transaction per Second*) non possono essere eseguite in modo seriale. Esempi tipici: sistemi bancari, prenotazioni aeree.

**Modello di riferimento**: operazioni di input-output su oggetti astratti $x$, $y$, $z$.

**Problema**: l'esecuzione concorrente causa **anomalie**, che vanno quindi governate.

## Anomalie della concorrenza

### Perdita di aggiornamento

Due transazioni identiche: $t_1: r(x),\ x=x+1,\ w(x)$ e $t_2: r(x),\ x=x+1,\ w(x)$. Inizialmente $x=2$; dopo un'esecuzione seriale $x=4$.

Con esecuzione concorrente: $t_1$ legge $x=2$ e calcola $x=3$; prima che $t_1$ scriva, $t_2$ legge anch'essa $x=2$ e calcola $x=3$; entrambe scrivono $x=3$ e fanno commit. Un aggiornamento viene **perso**: $x=3$ invece di $4$.

### Lettura sporca (dirty read)

$t_1$ modifica $x$ ma poi va in **abort**; nel frattempo $t_2$ ha già letto il valore modificato (non ancora committato) e ne fa commit. Aspetto critico: $t_2$ ha letto uno stato intermedio ("sporco") e lo può comunicare all'esterno, anche se quello stato non è mai realmente esistito nella base di dati (essendo stato annullato).

### Letture inconsistenti

$t_1$ legge $x$ due volte, con $t_2$ che nel frattempo modifica e fa commit di $x$ fra le due letture di $t_1$: $t_1$ legge due valori diversi per lo stesso oggetto nell'ambito della stessa transazione.

### Aggiornamento fantasma

Si assuma un vincolo $y+z=1000$. $t_1$ legge $y$ (prima che $t_2$ lo modifichi) e legge $z$ (dopo che $t_2$ lo ha modificato), mentre $t_2$ trasferisce $100$ da $y$ a $z$ (mantenendo il vincolo) e fa commit fra le due letture di $t_1$. $t_1$ calcola $s=y+z=1100$: il vincolo sembra non soddisfatto, perché $t_1$ ha visto un aggiornamento non coerente (una "fotografia" mista fra stato prima e dopo l'aggiornamento di $t_2$).

### Inserimento fantasma

$t_1$ "legge gli stipendi degli impiegati del dipartimento A e calcola la media"; $t_2$ inserisce un nuovo impiegato in A e fa commit; $t_1$ ripete la stessa lettura e ottiene un risultato diverso, a causa di una riga "nuova" comparsa nel frattempo (non individuabile con i soli lock sui dati esistenti, perché riguarda un dato che *prima* non c'era).

### Riepilogo delle anomalie

| Anomalia | Tipo di conflitto |
|---|---|
| Perdita di aggiornamento | W-W |
| Lettura sporca | R-W (o W-W) con abort |
| Letture inconsistenti | R-W |
| Aggiornamento fantasma | R-W |
| Inserimento fantasma | R-W su dato "nuovo" |

## Gestore della concorrenza

Ignorando per semplicità buffer e affidabilità, il gestore della concorrenza riceve richieste `read`/`write` dal gestore dei metodi d'accesso e `begin`/`commit`/`abort` dal gestore delle transazioni; consulta la **tabella dei lock** e inoltra le operazioni (non necessariamente tutte, e non necessariamente nello stesso ordine) al gestore della memoria secondaria.

## Schedule

Nel controllo della concorrenza, una **transazione è una sequenza di operazioni di input/output** (si omettono le operazioni di manipolazione dei dati). Uno **schedule** è la sequenza (intrecciata) delle operazioni di più transazioni, così come vengono effettivamente eseguite.

> [!example] Uno schedule
> $S_1: r_1(x)\ r_2(z)\ w_1(x)\ w_2(z)$

**Ipotesi semplificativa** (che verrà poi rimossa, non accettabile in pratica): si considera la **commit-proiezione**, ignorando le transazioni che vanno in abort (rimuovendo tutte le loro azioni dallo schedule). Ipotesi teorica: uno schedule deve decidere se accettare o rifiutare le azioni di una transazione senza conoscere il suo esito finale — la commit-proiezione è quindi una semplificazione non realistica, utile solo per definire le proprietà teoriche.

## Controllo di concorrenza: obiettivo

**Obiettivo**: evitare le anomalie.

- **Scheduler**: un sistema che accetta o rifiuta (o riordina) le operazioni richieste dalle transazioni, rifiutando quelle che generano anomalie.
- **Schedule seriale**: le transazioni sono separate, eseguite una alla volta.
- **Schedule serializzabile**: produce lo stesso risultato di uno schedule seriale sulle stesse transazioni. Richiede una nozione di **equivalenza fra schedule**; si assume che ogni transazione singola sia corretta.

### Idea base

Individuare classi di schedule serializzabili che siano **sottoclassi** degli schedule possibili, siano effettivamente serializzabili, e la cui proprietà di serializzabilità sia **verificabile a costo basso**:

```
Schedule ⊃ Schedule Serializzabili ⊃ Schedule Seriali
```

## View-serializzabilità

**Definizioni preliminari**:
- $r_i(x)$ **legge-da** $w_j(x)$ in uno schedule $S$ se $w_j(x)$ precede $r_i(x)$ in $S$ e non c'è $w_k(x)$ fra $r_i(x)$ e $w_j(x)$ in $S$.
- $w_i(x)$ in uno schedule $S$ è **scrittura finale** se è l'ultima scrittura dell'oggetto $x$ in $S$.

> [!quote] Definizione — View-equivalenza e view-serializzabilità
> Due schedule $S_i$ e $S_j$ sono **view-equivalenti** ($S_i \approx_V S_j$) se hanno la stessa relazione *legge-da* e le stesse scritture finali.
>
> Uno schedule è **view-serializzabile** se è view-equivalente a un qualche schedule seriale. L'insieme degli schedule view-serializzabili è indicato con **VSR**.

> [!example] View-serializzabilità: esempi
> $S_3: w_0(x)\ r_2(x)\ r_1(x)\ w_2(x)\ w_2(z)$
> $S_4: w_0(x)\ r_1(x)\ r_2(x)\ w_2(x)\ w_2(z)$ (seriale)
> $S_5: w_0(x)\ r_1(x)\ w_1(x)\ r_2(x)\ w_1(z)$
> $S_6: w_0(x)\ r_1(x)\ w_1(x)\ w_1(z)\ r_2(x)$ (seriale)
>
> - $S_3$ è view-equivalente allo schedule seriale $S_4$: è quindi view-serializzabile.
> - $S_5$ non è view-equivalente a $S_4$, ma è view-equivalente allo schedule seriale $S_6$: è quindi view-serializzabile.
>
> Gli schedule delle anomalie viste sopra **non** sono view-serializzabili:
> - $S_7: r_1(x)\ r_2(x)\ w_1(x)\ w_2(x)$ (perdita di aggiornamento)
> - $S_8: r_1(x)\ r_2(x)\ w_2(x)\ r_1(x)$ (letture inconsistenti)
> - $S_9: r_1(x)\ r_1(y)\ r_2(z)\ r_2(y)\ w_2(y)\ w_2(z)\ r_1(z)$ (aggiornamento fantasma)

**Complessità**: la verifica della view-equivalenza di due schedule dati è **polinomiale**, ma decidere la view-serializzabilità di uno schedule è un problema **NP-completo**. Non è quindi utilizzabile in pratica.

## Conflict-serializzabilità

**Definizione preliminare**: un'azione $a_i$ è in **conflitto** con $a_j$ ($i \neq j$) se operano sullo stesso oggetto e almeno una di esse è una scrittura. Due casi: conflitto **read-write** ($rw$ o $wr$) e conflitto **write-write** ($ww$).

> [!quote] Definizione — Conflict-equivalenza e conflict-serializzabilità
> Due schedule $S_i$ e $S_j$ sono **conflict-equivalenti** ($S_i \approx_C S_j$) se includono le stesse operazioni e ogni coppia di operazioni in conflitto compare nello stesso ordine in entrambi.
>
> Uno schedule è **conflict-serializzabile** se è conflict-equivalente a un qualche schedule seriale. L'insieme degli schedule conflict-serializzabili è indicato con **CSR**.

### CSR e VSR

Ogni schedule conflict-serializzabile è view-serializzabile, ma **non necessariamente viceversa**: $\text{CSR} \subset \text{VSR}$.

> [!example] Controesempio per la non necessità
> $r_1(x)\ w_2(x)\ w_1(x)\ w_3(x)$:
> - **view-serializzabile**: view-equivalente a $r_1(x)\ w_1(x)\ w_2(x)\ w_3(x)$
> - **non conflict-serializzabile**: la coppia in conflitto $(w_2, w_1)$ compare nell'ordine opposto rispetto a qualunque schedule seriale che rispetti anche $r_1$ prima di $w_1$.

**CSR implica VSR**: se $S_1 \approx_C S_2$ allora $S_1 \approx_V S_2$. Dimostrazione: i due schedule hanno le **stesse scritture finali** (se non fosse così, ci sarebbero almeno due scritture in ordine diverso, e poiché due scritture sono sempre in conflitto, i due schedule non sarebbero $\approx_C$) e la **stessa relazione "legge-da"** (analogamente, se fosse diversa ci sarebbero scritture o coppie lettura-scrittura in ordine diverso, violando $\approx_C$).

### Verifica di conflict-serializzabilità: il grafo dei conflitti

Per mezzo del **grafo dei conflitti**: un nodo per ogni transazione $t_i$; un arco (orientato) da $t_i$ a $t_j$ se c'è almeno un conflitto fra un'azione $a_i$ e un'azione $a_j$ tale che $a_i$ precede $a_j$.

> [!info] Teorema
> Uno schedule è in **CSR** se e solo se il grafo dei conflitti è **aciclico**.

**Dimostrazione**:
- Se uno schedule $S$ è CSR, allora è $\approx_C$ a uno schedule seriale. Ordinando le transazioni dello schedule seriale secondo il TID $t_1, t_2, \dots, t_n$: poiché lo schedule seriale ha tutti i conflitti nello stesso ordine dello schedule $S$, nel grafo di $S$ ci possono essere solo archi $(i,j)$ con $i<j$, e quindi il grafo non può avere cicli (un ciclo richiederebbe almeno un arco $(i,j)$ con $i>j$).
- Se il grafo di $S$ è aciclico, allora esiste fra i nodi un **ordinamento topologico** (una numerazione dei nodi tale che il grafo contiene solo archi $(i,j)$ con $i<j$). Lo schedule seriale le cui transazioni sono ordinate secondo l'ordinamento topologico è equivalente a $S$, perché per tutti i conflitti $(i,j)$ si ha sempre $i<j$.

## Controllo della concorrenza in pratica

Anche la conflict-serializzabilità, pur più rapidamente verificabile (l'algoritmo, con opportune strutture dati, richiede tempo lineare), è **inutilizzabile in pratica**: la tecnica sarebbe efficiente se potessimo conoscere il grafo dall'inizio, ma non è così — uno scheduler deve operare **incrementalmente**, decidendo ad ogni richiesta di operazione se eseguirla subito o fare qualcos'altro; non è praticabile mantenere il grafo, aggiornarlo e verificarne l'aciclicità ad ogni richiesta. Inoltre la tecnica si basa sull'ipotesi (irrealistica) di commit-proiezione.

In pratica si usano tecniche che:
- garantiscono la conflict-serializzabilità **senza** dover costruire il grafo;
- **non** richiedono l'ipotesi della commit-proiezione.

## Lock

Principio:
- tutte le letture sono precedute da `r_lock` (lock condiviso) e seguite da `unlock`;
- tutte le scritture sono precedute da `w_lock` (lock esclusivo) e seguite da `unlock`.

Quando una transazione prima legge e poi scrive un oggetto, può: richiedere subito un lock esclusivo, oppure chiedere prima un lock condiviso e poi uno esclusivo (**lock escalation**).

Il **lock manager** riceve queste richieste dalle transazioni e le accoglie o rifiuta, sulla base della tavola dei conflitti.

### Gestione dei lock

| Richiesta | free | r_locked | w_locked |
|---|---|---|---|
| `r_lock` | OK / r_locked | OK / r_locked | NO / w_locked |
| `w_lock` | OK / w_locked | OK / r_locked* | NO / w_locked |
| `unlock` | error | OK / depends | OK / free |

\* Nota: una richiesta di `w_lock` su una risorsa già `r_locked` non è concedibile se c'è più di un lettore; un contatore tiene conto del numero di "lettori", e la risorsa è rilasciata quando il contatore scende a zero.

Se la risorsa non è concessa, la transazione richiedente è posta in attesa (eventualmente in coda), fino a quando la risorsa non diventa disponibile. Il lock manager gestisce una **tabella dei lock**, per ricordare la situazione.

## Locking a due fasi (2PL)

Usato da quasi tutti i sistemi reali. Garantisce "a priori" la conflict-serializzabilità. Basata su due regole:
1. "proteggere" tutte le letture e scritture con lock;
2. un vincolo sulle richieste e i rilasci dei lock: **una transazione, dopo aver rilasciato un lock, non può acquisirne altri**.

> [!quote] Definizione — Two Phase Locking (2PL)
> Uno scheduling in cui una transazione, dopo aver rilasciato un lock, non può acquisirne altri sulla stessa risorsa (né su alcuna risorsa, nella formulazione più stretta), è detto **2PL**: la transazione attraversa una fase di crescita (acquisizione di lock) seguita da una fase di decrescita (rilascio di lock), senza sovrapposizioni.

### 2PL e CSR

Ogni schedule 2PL è anche conflict-serializzabile, ma **non necessariamente viceversa**: $\text{2PL} \subset \text{CSR}$.

> [!example] Controesempio per la non necessità
> $r_1(x)\ w_1(x)\ r_2(x)\ w_2(x)\ r_3(y)\ w_1(y)$ viola 2PL (perché $t_1$ acquisisce il lock su $y$ dopo aver rilasciato il lock su $x$, cioè dopo la fase di decrescita) ma è comunque conflict-serializzabile.

**2PL implica CSR** (dimostrazione): sia $S$ uno schedule 2PL. Si consideri, per ciascuna transazione, l'istante in cui ha acquisito tutte le risorse e sta per rilasciare la prima (il "punto di svolta"). Ordinando le transazioni secondo questo valore temporale, si ottiene uno schedule seriale corrispondente. Si vuole dimostrare che tale schedule è equivalente a $S$: si consideri un conflitto fra un'azione di $t_i$ e un'azione di $t_j$ con $i<j$ (secondo l'ordinamento); è possibile che compaiano in ordine invertito in $S$? No, perché in tal caso $t_j$ dovrebbe aver rilasciato la risorsa in questione **prima** della sua acquisizione da parte di $t_i$, il che contraddirebbe la definizione dell'ordinamento (violando la proprietà 2PL).

## Locking a due fasi stretto

Condizione aggiuntiva: **i lock possono essere rilasciati solo dopo il commit o l'abort**. Supera la necessità dell'ipotesi di commit-proiezione (ed elimina il rischio di letture sporche).

## Riepilogo delle classi di schedule

```
Schedule ⊃ VSR ⊃ CSR ⊃ 2PL ⊃ Schedule Seriali
```

## Controllo di concorrenza basato su timestamp (TS)

Tecnica alternativa al 2PL.

> [!quote] Definizione — Timestamp
> Un **timestamp** è un identificatore che definisce un ordinamento totale sugli eventi di un sistema. Ogni transazione ha un timestamp che rappresenta l'istante di inizio della transazione.

Uno schedule è accettato solo se riflette l'ordinamento seriale delle transazioni indotto dai timestamp.

### Dettagli

Lo scheduler mantiene due contatori $\text{RTM}(x)$ e $\text{WTM}(x)$ per ogni oggetto (il massimo timestamp fra le transazioni che rispettivamente hanno letto o scritto $x$). Riceve richieste di lettura e scrittura, con indicato il timestamp della transazione:

- **`read(x, ts)`**:
  - se $ts < \text{WTM}(x)$: la richiesta è respinta e la transazione viene **uccisa** (perché leggerebbe un valore "vecchio" rispetto a una scrittura più recente);
  - altrimenti: la richiesta è accolta e $\text{RTM}(x)$ è posto uguale al maggiore fra $\text{RTM}(x)$ e $ts$.
- **`write(x, ts)`**:
  - se $ts < \text{WTM}(x)$ oppure $ts < \text{RTM}(x)$: la richiesta è respinta e la transazione viene **uccisa**;
  - altrimenti: la richiesta è accolta e $\text{WTM}(x)$ è posto uguale a $ts$.

Vengono uccise molte transazioni. Per funzionare anche senza l'ipotesi di commit-proiezione, la tecnica deve "bufferizzare" le scritture fino al commit (con attese).

> [!example] Esempio di timestamp ordering
> $\text{RTM}(x)=7$, $\text{WTM}(x)=4$:
>
> | Richiesta | Risposta | Nuovo valore |
> |---|---|---|
> | $read(x,6)$ | ok | — |
> | $read(x,8)$ | ok | $\text{RTM}(x)=8$ |
> | $read(x,9)$ | ok | $\text{RTM}(x)=9$ |
> | $write(x,8)$ | no, $t_8$ uccisa | — |
> | $write(x,11)$ | ok | $\text{WTM}(x)=11$ |
> | $read(x,10)$ | no, $t_{10}$ uccisa | — |

### 2PL vs TS

Sono **incomparabili**: esistono schedule in TS ma non in 2PL, schedule in 2PL ma non in TS, e schedule in entrambi.

- In **2PL** le transazioni in conflitto sono poste in **attesa**; in **TS** vengono **uccise e rilanciate** (con nuovo timestamp).
- Per rimuovere l'ipotesi di commit-proiezione, entrambe le tecniche richiedono un'**attesa per il commit** (bufferizzazione delle scritture).
- 2PL può causare **deadlock** (stallo).
- Le ripartenze sono di solito più costose delle attese: in pratica, **conviene il 2PL**.

## Controllo di concorrenza multi-versione

Idea del metodo: ogni `write` genera una **nuova copia** dell'oggetto, mentre i `read` leggono la copia "giusta" (quella corrispondente al proprio timestamp).

I `write` generano una nuova copia con un nuovo $\text{WTM}$; istante per istante ogni oggetto $x$ ha $N>1$ copie attive, con $\text{WTM}_N(x)$. C'è poi un solo $\text{RTM}(x)$ globale. Le vecchie copie vengono scartate quando non sono più presenti transazioni in lettura che dovrebbero leggerle.

### Meccanismo

- **`read(x, ts)`**: viene **sempre accettata**; si seleziona la copia $x_k$ in lettura tale che: se $ts > \text{WTM}_N(x)$, allora $k=N$; altrimenti si prenda $k$ tale che $\text{WTM}_k(x) \leq ts < \text{WTM}_{k+1}(x)$.
- **`write(x, ts)`**: se $ts < \text{RTM}(x)$ la richiesta è respinta; altrimenti si crea una nuova versione (N incrementato) con $\text{WTM}_N(x) = ts$.

> [!example] Esempio di controllo multi-versione
> $\text{RTM}(x)=7$, $N=1$, $\text{WTM}(x_1)=4$:
>
> | Richiesta | Risposta | Nuovo valore |
> |---|---|---|
> | $read(x,6)$ | ok | — |
> | $read(x,8)$ | ok | $\text{RTM}(x)=8$ |
> | $read(x,9)$ | ok | $\text{RTM}(x)=9$ |
> | $write(x,8)$ | no | $t_8$ uccisa |
> | $write(x,11)$ | ok | $N=2$, $\text{WTM}(x_2)=11$ |
> | $read(x,10)$ | ok su copia 1 | $\text{RTM}(x)=10$ |
> | $read(x,12)$ | ok su copia 2 | $\text{RTM}(x)=12$ |
> | $write(x,13)$ | ok | $N=3$, $\text{WTM}(x_3)=13$ |
>
> A differenza del controllo a singola versione, le letture con timestamp compreso fra due scritture (es. $read(x,10)$) non vengono uccise: leggono semplicemente la versione corretta per il loro istante.

## Stallo (deadlock)

**Attese incrociate**: due transazioni detengono ciascuna una risorsa e aspettano la risorsa detenuta dall'altra.

> [!example] Esempio di deadlock
> $t_1: read(x),\ write(y)$ e $t_2: read(y),\ write(x)$, con schedule:
> $$r\_lock_1(x),\ r\_lock_2(y),\ read_1(x),\ read_2(y),\ w\_lock_1(y),\ w\_lock_2(x)$$
> $t_1$ attende il lock su $y$ (detenuto da $t_2$ in lettura), $t_2$ attende il lock su $x$ (detenuto da $t_1$ in lettura): nessuna delle due può proseguire.

### Risoluzione dello stallo

Uno stallo corrisponde a un **ciclo nel grafo delle attese** (nodo = transazione, arco = attesa). Tre tecniche:

1. **Timeout**: problema — la scelta dell'intervallo comporta un trade-off (troppo corto: falsi positivi; troppo lungo: attese inutili).
2. **Rilevamento dello stallo**: ricerca di cicli nel grafo delle attese.
3. **Prevenzione dello stallo**: uccisione di transazioni "sospette" (può esagerare, uccidendo transazioni che non sarebbero effettivamente entrate in stallo).

## Livelli di isolamento in SQL:1999 (e JDBC)

Le transazioni possono essere definite `read-only` (non possono richiedere lock esclusivi). Il livello di isolamento può essere scelto per ogni transazione:

- **`read uncommitted`**: permette letture sporche, letture inconsistenti, aggiornamenti fantasma e inserimenti fantasma.
- **`read committed`**: evita letture sporche ma permette letture inconsistenti, aggiornamenti fantasma e inserimenti fantasma.
- **`repeatable read`**: evita tutte le anomalie esclusi gli inserimenti fantasma.
- **`serializable`**: evita tutte le anomalie.

> [!info] Nota
> La perdita di aggiornamento è **sempre evitata**, indipendentemente dal livello di isolamento scelto.

### Livelli di isolamento: implementazione

Sulle **scritture** si ha sempre il 2PL stretto (e quindi si evita sempre la perdita di aggiornamento).

- **`read uncommitted`**: nessun lock in lettura (e non rispetta i lock altrui).
- **`read committed`**: lock in lettura (e rispetta quelli altrui), ma senza 2PL (i lock in lettura vengono rilasciati subito dopo la lettura, non alla fine della transazione).
- **`repeatable read`**: 2PL anche in lettura, con lock sui dati.
- **`serializable`**: 2PL con **lock di predicato**.

Inoltre, un nuovo livello offerto dai sistemi moderni: **`snapshot isolation`**, basato sulla gestione di più versioni dei dati (concettualmente collegato al controllo di concorrenza multi-versione descritto sopra).

### Lock di predicato

Necessario per evitare gli inserimenti fantasma (bloccando anche righe che *ancora non esistono* ma che soddisferebbero il predicato di una query).

- **Caso peggiore**: lock sull'intera relazione.
- **Se siamo fortunati**: lock sull'indice (solo sull'intervallo di valori coperto dal predicato).

### Update lock

Il deadlock più frequente avviene quando due transazioni concorrenti vogliono prima leggere e poi scrivere la stessa risorsa (entrambe acquisiscono un lock condiviso e poi tentano di fare l'upgrade a esclusivo, bloccandosi a vicenda). Per evitare questa situazione, i sistemi offrono gli **update lock** (UL): acquisito da transazioni che vogliono inizialmente leggere un oggetto per poi modificarne il valore.

| Richiesta | SL | UL | XL |
|---|---|---|---|
| **SL** | OK | OK | No |
| **UL** | OK | No | No |
| **XL** | No | No | No |

A differenza di due `r_lock` (SL) che possono coesistere, un `UL` è **incompatibile con un altro UL**: solo una transazione alla volta può "prenotarsi" per l'upgrade a scrittura, evitando così l'attesa incrociata.
