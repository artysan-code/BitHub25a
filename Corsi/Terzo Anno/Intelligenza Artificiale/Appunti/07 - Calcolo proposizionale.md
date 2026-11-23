---
tags:
  - intelligenza-artificiale
  - logica
  - calcolo-proposizionale
slide:
  - "0041_Logic_CalProposizionale_26_27_v1.4.pdf"
---
# Calcolo proposizionale
Slide `0041_Logic_CalProposizionale_26_27_v1.4.pdf` (81 pagine; R&N 4ª ed., capitoli 7.4-7.8, 9.1, 9.5; alcune slide sono di Maria Simi, Università di Pisa), che sul sito del corso è la **Lezione 7**: «Agenti Logici: il ruolo del Calcolo Proposizionale: sintassi e semantica del CProp, algoritmi di inferenza, risoluzione per il CProp, applicazione al planning». Nell'ordine del corso questa nota viene **tra la [[04 - Agenti basati sulla conoscenza]] e la [[05 - Logica del primo ordine]]**; ha il numero 07 solo per non rinumerare le note esistenti e non rompere i rimandi. Il file `0041` è la versione 26_27 presa dai File del canale «Lezioni» di Teams.

> [!warning] Ricostruita dalle sole slide
> Di questa lezione non c'è registrazione (la lezione del 4/11/2026 non ha né registrazione né nota): la nota è ricostruita dalle sole slide. Manca quindi tutto ciò che il professore ha detto a voce: spiegazioni, esempi, indicazioni su cosa è richiesto all'esame. Ciò che nella parte sul calcolo proposizionale della nota 04 è stato detto a lezione (2/11/2026) è rimasto lì, e di volta in volta rimanda a questa nota.

Le pagine indicate sono quelle del PDF. Le formule che nella slide sono immagini sono state lette dall'immagine della pagina. I nomi (TT-Entails, DPLL, WalkSAT, SATplan) e i nomi di funzione degli algoritmi sono quelli delle slide, che li riportano in inglese (le figure vengono dal libro).

## Panoramica e sintassi
La panoramica (p. 2) elenca: la rappresentazione della conoscenza in CPROP; sintassi e semantica del CPROP; l'inferenza nel CPROP (algoritmo *naive*, algoritmi di *random walk*, deduzione e inferenza: risoluzione); l'applicazione del CPROP al mondo del Wumpus.

> [!quote] Sintassi (p. 3)
> La sintassi definisce quali sono le frasi legittime del linguaggio:
> - $\mathit{formula} \to \mathit{formulaAtomica} \mid \mathit{formulaComplessa}$
> - $\mathit{formulaAtomica} \to \mathit{True} \mid \mathit{False} \mid P \mid Q \mid R \mid \dots$
> - $\mathit{formulaComplessa} \to (\mathit{formula}) \mid [\mathit{formula}] \mid \lnot\,\mathit{formula} \mid (\mathit{formula}\land\mathit{formula}) \mid (\mathit{formula}\lor\mathit{formula}) \mid (\mathit{formula}\Rightarrow\mathit{formula}) \mid (\mathit{formula}\Leftrightarrow\mathit{formula})$
> - **Precedenza degli operatori**: $\lnot,\ \land,\ \lor,\ \Rightarrow,\ \Leftrightarrow$ (dalla più alta).

**Esempi** (p. 4): $((A\land B)\Rightarrow C)$. Si possono omettere le parentesi assumendo la precedenza $\lnot > \land > \lor > \Rightarrow,\Leftrightarrow$: la formula $\lnot P\lor Q\land R\Rightarrow S$ è la stessa di $(((\lnot P)\lor(Q\land R))\Rightarrow S)$. La slide la disegna come albero di *formulaComplessa*: la radice è $\Rightarrow$, con $S$ a destra e a sinistra $\lor$, che ha $\lnot$ (su $P$) e $\land$ (su $Q$ e $R$).

## Semantica e mondi possibili (modelli)
> [!quote] Semantica (pp. 5-6)
> - La semantica ha a che fare col significato delle frasi: definisce se un enunciato è vero o falso rispetto a una **interpretazione** (mondo possibile).
> - Una interpretazione definisce un valore di verità per **tutti** i simboli proposizionali.
> - Un **modello** è una interpretazione che rende vera una formula o un insieme di formule.
> - **Semantica composizionale**: il significato di una frase è determinato dal significato dei suoi componenti, a partire dalle frasi atomiche (i simboli proposizionali).

**Esempio** (p. 5, con due griglie del Wumpus come figure): l'interpretazione $\{P_{3,1}\ \text{vero},\ P_{1,2}\ \text{falso},\ W_{1,3}\ \text{vero}\}$ rende vera la formula $P_{3,1}\Rightarrow W_{1,3}\lor P_{1,2}$. La slide mostra anche una seconda interpretazione, $\{P_{3,1}\ \text{falso},\ P_{1,1}\ \text{vero},\ W_{1,3}\ \text{vero}\}$, legata alla seconda griglia.

### Tabelle di verità dei connettivi
Le regole della semantica composizionale (p. 6) a parole:

| Formula | Vera se |
|---|---|
| $\mathit{True}$ / $\mathit{False}$ | sempre vera / sempre falsa |
| $P\land Q$ | $P$ e $Q$ sono veri |
| $P\lor Q$ | $P$ oppure $Q$, o entrambi, sono veri |
| $\lnot P$ | $P$ è falso |
| $P\Rightarrow Q$ | $P$ è falso oppure $Q$ è vero |
| $P\Leftrightarrow Q$ | entrambi veri o entrambi falsi |

> [!info] Non è nella slide
> La slide dà queste regole solo a parole. Le righe della tabella di verità per i singoli connettivi (i quattro casi di $P$ e $Q$) non sono sviluppate nella slide: si ricavano da queste regole.

## Conseguenza logica
> [!quote] Conseguenza logica (p. 7)
> Una formula $A$ è **conseguenza logica** di un insieme di formule $KB$ se e solo se in ogni modello di $KB$ anche $A$ è vera ($KB\models A$). Indicando con $M(\alpha)$ l'insieme delle interpretazioni che rendono $\alpha$ vera, cioè i modelli di $\alpha$, e con $M(KB)$ i modelli di un insieme di formule $KB$:
> $$KB\models\alpha\quad\text{sse}\quad M(KB)\subseteq M(\alpha)$$

> [!example] Esempio dal mondo del Wumpus (pp. 8-9)
> $KB=\{B_{2,1},\ \lnot B_{1,1},\ +\text{regole del WW}\}$. Si vuole stabilire l'assenza di pozzi in $[1,2]$ e in $[2,2]$: $KB\models\lnot P_{1,2}$? $KB\models\lnot P_{2,2}$? Considerando solo l'esistenza di pozzi nelle tre caselle $P_{1,2}$, $P_{2,2}$ e $P_{3,1}$ ci sono **otto** interpretazioni o mondi possibili.
>
> La figura di p. 9 disegna gli otto mondi e, con linee chiuse, l'insieme dei modelli di $KB$ e quello dei modelli di $\lnot P_{1,2}$ (a) e di $\lnot P_{2,2}$ (b). La slide conclude:
> - $KB\models\lnot P_{1,2}$ poiché $M(KB)\subseteq M(\lnot P_{1,2})$;
> - $KB\not\models\lnot P_{2,2}$ poiché $M(KB)\not\subseteq M(P_{2,2})$ (così è scritto nella slide; la slide stessa nella figura (b) disegna l'insieme di $\lnot P_{2,2}$, quindi qui $M(P_{2,2})$ è quasi certamente un refuso per $M(\lnot P_{2,2})$).

## Equivalenza logica
> [!quote] Equivalenza logica (p. 10)
> $A\equiv B$ se e solo se $A\models B$ e $B\models A$. Esempi della slide: $A\land B\equiv B\land A$ (commutatività di $\land$); $\lnot(A\land B)\equiv\lnot A\lor\lnot B$ e $\lnot(A\lor B)\equiv\lnot A\land\lnot B$ (De Morgan).

La tabella delle **equivalenze logiche notevoli** (pp. 11-16, costruita pagina per pagina; la slide la riporta in inglese, come nel libro) vale per qualunque formula $\alpha,\beta,\gamma$:

| Equivalenza | Nome nella slide |
|---|---|
| $(\alpha\land\beta)\equiv(\beta\land\alpha)$ | commutatività di $\land$ |
| $(\alpha\lor\beta)\equiv(\beta\lor\alpha)$ | commutatività di $\lor$ |
| $((\alpha\land\beta)\land\gamma)\equiv(\alpha\land(\beta\land\gamma))$ | associatività di $\land$ |
| $((\alpha\lor\beta)\lor\gamma)\equiv(\alpha\lor(\beta\lor\gamma))$ | associatività di $\lor$ |
| $\lnot(\lnot\alpha)\equiv\alpha$ | eliminazione della doppia negazione |
| $(\alpha\Rightarrow\beta)\equiv(\lnot\beta\Rightarrow\lnot\alpha)$ | contrapposizione |
| $(\alpha\Rightarrow\beta)\equiv(\lnot\alpha\lor\beta)$ | eliminazione dell'implicazione |
| $(\alpha\Leftrightarrow\beta)\equiv((\alpha\Rightarrow\beta)\land(\beta\Rightarrow\alpha))$ | eliminazione della doppia implicazione |
| $\lnot(\alpha\land\beta)\equiv(\lnot\alpha\lor\lnot\beta)$ | De Morgan |
| $\lnot(\alpha\lor\beta)\equiv(\lnot\alpha\land\lnot\beta)$ | De Morgan |
| $(\alpha\land(\beta\lor\gamma))\equiv((\alpha\land\beta)\lor(\alpha\land\gamma))$ | distributività di $\land$ su $\lor$ |
| $(\alpha\lor(\beta\land\gamma))\equiv((\alpha\lor\beta)\land(\alpha\lor\gamma))$ | distributività di $\lor$ su $\land$ |

## Validità e soddisfacibilità
> [!quote] Validità, soddisfacibilità (p. 17)
> - Una formula $A$ è **valida** sse è vera in tutte le interpretazioni ($A$ è anche detta **tautologia**).
> - $A$ è **soddisfacibile** sse esiste (almeno) una interpretazione in cui $A$ è vera.
> - $A$ è valida sse $\lnot A$ non è soddisfacibile (o $\lnot A$ è **insoddisfacibile**).

## Inferenza nel calcolo proposizionale
Come verificare la soddisfacibilità delle formule (p. 18). Gli algoritmi elencati sono: **TT-Entails** (tabelle di verità), **DPLL** (Davis, Putnam; la slide lo indica «da leggere, non in programma») e la ricerca locale **WalkSAT**.

**Inferenza per Prop** (p. 19):
- **model checking**: una forma di inferenza che sfrutta la definizione di conseguenza logica; si enumerano i possibili modelli (tecnica delle tabelle di verità);
- **algoritmi per la soddisfacibilità**: $KB\models A$ sse $KB_\land\land\lnot A$ è insoddisfacibile, dove $KB_\land$ è la congiunzione delle formule della base (la slide scrive $KB_{\wedge}$ con il simbolo $\land$ a pedice).

### Tabella di verità e TT-Entails
**Esempio con tabella di verità** (pp. 20-22): $(\lnot A\lor B)\land(A\lor C)\models(B\lor C)$. Le colonne sono $A$, $B$, $C$, $\lnot A\lor B$, $A\lor C$, $B\lor C$; le righe sono le $2^3$ combinazioni (la slide le costruisce con il $2^3$ a margine):

| $A$ | $B$ | $C$ | $\lnot A\lor B$ | $A\lor C$ | $B\lor C$ |
|---|---|---|---|---|---|
| T | T | T | T | T | T |
| T | T | F | T | T | T |
| T | F | T | F | T | |
| T | F | F | F | T | |
| F | T | T | T | T | T |
| F | T | F | T | F | |
| F | F | T | T | T | T |
| F | F | F | T | F | |

Nelle righe in cui sono veri sia $\lnot A\lor B$ sia $A\lor C$ (cioè in cui $KB$ è soddisfatta) $B\lor C$ è vera: la colonna «Soddisfatto» della slide (p. 22) ha $T$ solo in quelle quattro righe, e le altre restano vuote perché non interessano.

> [!example] L'algoritmo TV-Consegue? (TT-Entails?) (pp. 23-25)
> Problema: $KB\models\alpha$? Si enumerano tutte le possibili interpretazioni di $KB$ (se $k$ sono i simboli usati da $KB$, i possibili modelli sono $2^k$). Per ciascuna interpretazione: se non soddisfa $KB$, va bene (OK); se soddisfa $KB$, si controlla che soddisfi anche $\alpha$.
>
> Esempio della slide (p. 25): $(\lnot A\lor B)\land(A\lor C)\models(B\lor C)$? con $KB=(\lnot A\lor B)\land(A\lor C)$, formula alfa $B\lor C$, simboli $[A,B,C]$ e modello iniziale $[\ ]$. La chiamata `TT-CHECK-ALL` assegna i simboli uno alla volta, prima $A=t$ poi $A=f$ e così via, e alle otto foglie risponde OK. Le foglie $[A{=}t;B{=}f;C{=}t]$, $[A{=}t;B{=}f;C{=}f]$, $[A{=}f;B{=}t;C{=}f]$, $[A{=}f;B{=}f;C{=}f]$ sono segnate «not a model for KB» (per queste $KB$ è falsa e l'algoritmo risponde comunque vero); nelle altre quattro $KB$ è vera e anche $B\lor C$ lo è.

Lo pseudocodice (p. 24, figura 7.10 del libro: «a truth-table enumeration algorithm for deciding propositional entailment»; $\mathrm{PL\text{-}TRUE?}$ restituisce vero se una formula è vera in un modello; $model$ è un modello parziale, un assegnamento ad alcuni dei simboli):

```pseudo
\begin{algorithm}
\caption{TT-Entails?($KB, \alpha$)}
\begin{algorithmic}
\State $symbols \gets$ la lista dei simboli proposizionali in $KB$ e $\alpha$
\State \Return \Call{TT-Check-All}{$KB, \alpha, symbols, \{\}$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{TT-Check-All($KB, \alpha, symbols, model$)}
\begin{algorithmic}
\If{\Call{Empty?}{$symbols$}}
  \If{\Call{PL-True?}{$KB, model$}}
    \State \Return \Call{PL-True?}{$\alpha, model$}
  \Else
    \State \Return $true$ \Comment{quando $KB$ è falsa, risponde sempre vero}
  \EndIf
\Else
  \State $P \gets$ \Call{First}{$symbols$}
  \State $rest \gets$ \Call{Rest}{$symbols$}
  \State \Return \Call{TT-Check-All}{$KB, \alpha, rest, model \cup \{P = true\}$} \textbf{and} \Call{TT-Check-All}{$KB, \alpha, rest, model \cup \{P = false\}$}
\EndIf
\end{algorithmic}
\end{algorithm}
```

> [!info] Non è nella slide
> La slide non dà un commento di costo. Che il numero di interpretazioni sia $2^k$ per $k$ simboli è invece scritto (p. 23).

## Algoritmi per la soddisfacibilità (SAT)
### Forma a clausole e forma normale congiuntiva
> [!quote] Forma a clausole e CNF (p. 26)
> Gli algoritmi SAT usano la $KB$ in **forma a clausole** (insiemi di letterali): $\{A,B\}\ \{\lnot B,C,D\}\ \{\lnot A,F\}$. La **forma normale congiuntiva** (CNF) è una congiunzione di disgiunzioni di letterali: $(A\lor B)\land(\lnot B\lor C\lor D)\land(\lnot A\lor F)$. **Non è restrittiva**: è sempre possibile ottenerla con trasformazioni che preservano l'equivalenza logica.

**Trasformazione in forma a clausole** (p. 27), i passi sono:
1. eliminazione della $\Leftrightarrow$: $(A\Leftrightarrow B)\equiv(A\Rightarrow B)\land(B\Rightarrow A)$;
2. eliminazione dell'$\Rightarrow$: $(A\Rightarrow B)\equiv(\lnot A\lor B)$;
3. distribuzione delle negazioni all'interno: $\lnot(A\lor B)\equiv(\lnot A\land\lnot B)$ e $\lnot(A\land B)\equiv(\lnot A\lor\lnot B)$ (De Morgan);
4. distribuzione delle disgiunzioni $\lor$ su $\land$ (CNF): $(A\lor(B\land C))\equiv(A\lor B)\land(A\lor C)$.

Notazione insiemistica: $\{A,B\}\ \{A,C\}$.

> [!example] Esempio di trasformazione (p. 28)
> 1. $B_{1,1}\Leftrightarrow(P_{1,2}\lor P_{2,1})$
> 2. $(B_{1,1}\Rightarrow(P_{1,2}\lor P_{2,1}))\land((P_{1,2}\lor P_{2,1})\Rightarrow B_{1,1})$
> 3. $(\lnot B_{1,1}\lor(P_{1,2}\lor P_{2,1}))\land(\lnot(P_{1,2}\lor P_{2,1})\lor B_{1,1})$
> 4. $(\lnot B_{1,1}\lor(P_{1,2}\lor P_{2,1}))\land((\lnot P_{1,2}\land\lnot P_{2,1})\lor B_{1,1})$
> 5. $(\lnot B_{1,1}\lor P_{1,2}\lor P_{2,1})\land(\lnot P_{1,2}\lor B_{1,1})\land(\lnot P_{2,1}\lor B_{1,1})$
> 6. $\{\lnot B_{1,1},P_{1,2},P_{2,1}\}\ \{\lnot P_{1,2},B_{1,1}\}\ \{\lnot P_{2,1},B_{1,1}\}$

### DPLL (facoltativo)
La slide (pp. 29-30) lo segnala «facoltativo» (già in p. 18: «da leggere, non in programma») e cita il lavoro originale: Davis, Logemann e Loveland, *A Machine Program for Theorem Proving*, Communications of the ACM, vol. 5, n. 7, 1962, pp. 394-397.

> [!info] Cos'è DPLL (pp. 30-33)
> Parte da una $KB$ in forma a clausole. È una **enumerazione in profondità** di tutti i possibili modelli, con tre miglioramenti rispetto a TT-Entails:
> 1. **terminazione anticipata**: si può decidere sulla verità di una clausola anche con modelli parziali. Basta che un letterale sia vero (se $A$ è vero lo sono anche $\{A,B\}$ e $\{A,C\}$ indipendentemente dai valori di $B$ e $C$, a causa della disgiunzione); se anche una sola clausola è falsa, l'interpretazione complessiva è falsa e non è un modello dell'insieme di clausole;
> 2. **euristica dei simboli (o letterali) puri**: un simbolo puro appare con lo stesso segno in tutte le clausole (esempio: in $\{A,\lnot B\}\ \{\lnot B,\lnot C\}\ \{C,A\}$, $A$ è puro, $B$ anche, $C$ no). Nel determinare se un simbolo è puro si possono trascurare le occorrenze in clausole già rese vere. I simboli puri si assegnano a True se il letterale è positivo, False se negativo. Non si eliminano modelli utili: se le clausole hanno un modello, continuano ad averlo dopo questo assegnamento;
> 3. **euristica delle clausole unitarie**: una clausola unitaria ha un solo letterale non assegnato (esempio: $\{B\}$ è unitaria, ma lo è anche $\{B,\lnot C\}$ quando $C=\mathit{True}$). Conviene assegnare prima valori al letterale nelle clausole unitarie; l'assegnamento è univoco (True se positivo, False se negativo).

Lo schema dell'algoritmo (p. 34, figura 7.17 del libro; la slide mette in evidenza con riquadri le tre euristiche; come TT-Entails?, DPLL lavora su modelli parziali):

```pseudo
\begin{algorithm}
\caption{DPLL-Satisfiable?($s$)}
\begin{algorithmic}
\State $clauses \gets$ l'insieme delle clausole della rappresentazione CNF di $s$
\State $symbols \gets$ la lista dei simboli proposizionali in $s$
\State \Return \Call{DPLL}{$clauses, symbols, \{\}$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{DPLL($clauses, symbols, model$)}
\begin{algorithmic}
\If{ogni clausola in $clauses$ è vera in $model$} \Return $true$ \EndIf \Comment{terminazione anticipata}
\If{qualche clausola in $clauses$ è falsa in $model$} \Return $false$ \EndIf \Comment{terminazione anticipata}
\State $P, value \gets$ \Call{Find-Pure-Symbol}{$symbols, clauses, model$} \Comment{simboli puri}
\If{$P$ non è nullo} \Return \Call{DPLL}{$clauses, symbols - P, model \cup \{P = value\}$} \EndIf
\State $P, value \gets$ \Call{Find-Unit-Clause}{$clauses, model$} \Comment{clausole unitarie}
\If{$P$ non è nullo} \Return \Call{DPLL}{$clauses, symbols - P, model \cup \{P = value\}$} \EndIf
\State $P \gets$ \Call{First}{$symbols$}; $rest \gets$ \Call{Rest}{$symbols$}
\State \Return \Call{DPLL}{$clauses, rest, model \cup \{P = true\}$} \textbf{or} \Call{DPLL}{$clauses, rest, model \cup \{P = false\}$}
\end{algorithmic}
\end{algorithm}
```

> [!example] DPLL: esempio (p. 35)
> $KB$: $\{\lnot B_{1,1},P_{1,2},P_{2,1}\}\ \{\lnot P_{1,2},B_{1,1}\}\ \{\lnot P_{2,1},B_{1,1}\}\ \{\lnot B_{1,1}\}\models\{\lnot P_{1,2}\}$? Si aggiunge $\{P_{1,2}\}$ (la negazione della formula da dimostrare) e si controlla se l'insieme è insoddisfacibile. Le cinque clausole sono numerate 1-5.
> - La 5 è unitaria: $P_{1,2}=\mathit{True}$; la prima clausola e la 5 sono soddisfatte.
> - La 2 diventa unitaria: $B_{1,1}=\mathit{True}$; la 2 e la 3 sono soddisfatte, ma la 4 no: **Fail**.
>
> Non esistono modelli con $P_{1,2}$ vero, quindi $\lnot P_{1,2}$ è conseguenza logica della $KB$.

### Metodi locali: WalkSAT
> [!quote] Metodi locali per SAT: formulazione e algoritmi (pp. 36-37)
> - Gli stati sono gli **assegnamenti completi**; l'obiettivo è un assegnamento di valori di verità alle proposizioni che soddisfa **tutte** le clausole. Si parte da un assegnamento casuale e a ogni passo si cambia il valore di una proposizione (*flip*).
> - **Euristica**: gli stati sono valutati contando il numero di clausole soddisfatte (più sono, meglio è), oppure quelle non soddisfatte.
> - Ci sono molti minimi locali, per sfuggire ai quali serve introdurre **perturbazioni casuali**: hill climbing con riavvio casuale, simulated annealing. Molta sperimentazione per trovare il miglior compromesso tra il grado di avidità e quello di casualità. **WalkSAT** è uno degli algoritmi più semplici ed efficaci.

**WalkSAT** (p. 38): a ogni passo sceglie a caso una clausola non ancora soddisfatta; poi sceglie un simbolo da modificare (*flip*), con probabilità $p$ (di solito $0{,}5$) tra due modi: un simbolo a caso (**passo casuale**), oppure quello che rende più clausole soddisfatte (**passo di ottimizzazione**, simile a *min-conflicts*). Si arrende dopo un certo numero di flip predefinito. La p. 39, «conflitti tra variabili», riporta la figura 6.9 del libro (soluzione in due passi di un problema delle otto regine con min-conflicts, con il numero di regine che attaccano scritto in ogni casella: la regina viene spostata nella casella con meno conflitti).

```pseudo
\begin{algorithm}
\caption{WalkSAT($clauses, p, max\text{-}flips$)}
\begin{algorithmic}
\State $model \gets$ un assegnamento casuale di $true/false$ ai simboli in $clauses$
\For{$i = 1$ \textbf{to} $max\text{-}flips$}
  \If{$model$ soddisfa $clauses$} \Return $model$ \EndIf
  \State $clause \gets$ una clausola scelta a caso tra quelle di $clauses$ false in $model$
  \State \textbf{con probabilità} $p$: cambia il valore in $model$ di un simbolo scelto a caso da $clause$ \Comment{passo casuale}
  \State \textbf{altrimenti}: cambia il simbolo di $clause$ che massimizza il numero di clausole soddisfatte \Comment{passo di ottimizzazione}
\EndFor
\State \Return $failure$
\end{algorithmic}
\end{algorithm}
```

> [!example] WalkSAT: un esempio (pp. 41-44)
> Clausole: 1 $\{\lnot B_{1,1},P_{1,2},P_{2,1}\}$, 2 $\{\lnot P_{1,2},B_{1,1}\}$, 3 $\{\lnot P_{2,1},B_{1,1}\}$, 4 $\{\lnot B_{1,1}\}$. Le coppie sono nell'ordine $[B_{1,1},P_{1,2},P_{2,1}]$.
> 1. $[F,T,T]$: sono false la 2 e la 3; scelgo la 2; passo a caso: flip $B_{1,1}$.
> 2. $[T,T,T]$: è falsa la 4; scelgo la 4; flip $B_{1,1}$.
> 3. $[F,T,T]$: sono false la 2 e la 3; scelgo la 2; passo a caso: flip $P_{1,2}$.
> 4. $[F,F,T]$: è falsa la 3; scelgo la 3; passo di ottimizzazione: flip $P_{2,1}$ dà $[4]$, flip $B_{1,1}$ dà $[3]$, quindi scelgo $P_{2,1}$.
> 5. $[F,F,F]$: **modello**.
>
> La slide colora in rosso i passi casuali e in verde quelli di ottimizzazione. I numeri tra parentesi quadre non sono spiegati nella slide: tornano come numero di clausole soddisfatte dopo il flip (ad esempio, dopo il flip di $P_{2,1}$ tutte e quattro le clausole sono soddisfatte).

> [!warning] Analisi di WalkSAT (p. 45)
> - Se $max\text{-}flips=\infty$ e l'insieme di clausole è soddisfacibile, prima o poi **termina**.
> - Va bene per cercare un modello, sapendo che c'è; se è insoddisfacibile non termina. **Non può essere usato per verificare l'insoddisfacibilità**.
> - Il problema è decidibile, ma l'algoritmo **non è completo**.

### Problemi SAT difficili
> [!info] Problemi SAT difficili (pp. 46-48)
> - Se un problema ha molte soluzioni è più probabile che WalkSAT ne trovi una (problema **sotto-vincolato**). Esempio della slide: 16 soluzioni su 32, un assegnamento ha il 50% di probabilità di essere giusto, quindi servono 2 passi in media.
> - Quello che conta è il rapporto $m/n$, con $m$ il numero di clausole (vincoli) e $n$ il numero di simboli (esempio: $5/5=1$). Più grande il rapporto, più vincolato è il problema. Le regine sono facili perché il problema è sotto-vincolato (poche regine e molte caselle).
> - **Probabilità di soddisfacibilità in funzione di $m/n$** (p. 47): $m$ varia, $n=50$ simboli, 3 letterali per clausola, media su 100 problemi generati a caso. Il grafico mostra una probabilità di soddisfacibilità vicina a 1 per i rapporti bassi e a 0 per quelli alti; i **problemi difficili** sono nella zona di transizione, indicata nella slide con un riquadro tra circa 3,5 e 5,5.
> - **Confronto tra DPLL e WalkSAT** (p. 48), su problemi soddisfacibili ma difficili: il grafico del tempo di esecuzione in funzione di $m/n$ mostra che nella zona difficile il tempo di DPLL è molto più alto di quello di WalkSAT.

## Inferenza come deduzione
> [!quote] Inferenza come deduzione (pp. 49-51)
> Un altro modo per decidere se $KB\models A$ è dare delle **regole di inferenza**. Si scrive $KB\vdash A$ ($A$ è **deducibile** da $KB$), da distinguere da $KB\models A$ ($A$ è conseguenza logica di $KB$). Le regole di inferenza:
> - dovrebbero derivare **solo** formule che sono conseguenza logica;
> - dovrebbero derivare **tutte** le formule che sono conseguenza logica.
>
> **Correttezza** (*soundness*): se $KB\vdash A$ allora $KB\models A$. Tutto ciò che è derivabile è conseguenza logica: le regole preservano la verità.
> **Completezza**: se $KB\models A$ allora $KB\vdash A$. Tutto ciò che è conseguenza logica è ottenibile tramite il meccanismo di inferenza. Non sempre è possibile.

(La slide scrive «CORRETTEZZA» e «COMPLETEZZA»; il termine inglese *soundness* non è nella slide.)

### Regole di inferenza
Le regole sono schemi deduttivi del tipo «premesse su conclusione» (p. 52):
- **Modus ponens** (o eliminazione dell'implicazione): da $\alpha\Rightarrow\beta$ e $\alpha$ si ricava $\beta$;
- **eliminazione dell'AND**: da $\alpha\land\beta$ si ricava $\alpha$;
- **eliminazione e introduzione della doppia implicazione**: da $\alpha\Leftrightarrow\beta$ si ricava $(\alpha\Rightarrow\beta)\land(\beta\Rightarrow\alpha)$, e viceversa.

### Meta-teoremi utili
> [!quote] Meta-teoremi (p. 53)
> - $A$ è valida sse $\lnot A$ è insoddisfacibile.
> - **Teorema di deduzione**: $A\models B$ sse $(A\Rightarrow B)$ è valida.
> - **Teorema di refutazione**: $A\models B$ sse $(A\land\lnot B)$ è insoddisfacibile (corrisponde alla dimostrazione per assurdo o per refutazione).

### Una rappresentazione per il mondo del Wumpus
> [!example] Il mondo del Wumpus in CPROP (pp. 54-58)
> - $R_1$: $\lnot P_{1,1}$ (non ci sono pozzi in $[1,1]$).
> - C'è brezza nelle caselle adiacenti ai pozzi: $R_2$: $B_{1,1}\Leftrightarrow(P_{1,2}\lor P_{2,1})$; $R_3$: $B_{2,1}\Leftrightarrow(P_{1,1}\lor P_{2,2}\lor P_{3,1})$.
> - Percezioni: $R_4$: $\lnot B_{1,1}$ (non c'è brezza in $[1,1]$); $R_5$: $B_{2,1}$ (c'è brezza in $[2,1]$).
>
> $KB=\{R_1,R_2,R_3,R_4,R_5\}$; le domande sono $KB\models\lnot P_{2,2}$? (p. 54) e $KB\models\lnot P_{1,2}$? (p. 55), con le stesse figure degli otto mondi della conseguenza logica (pp. 56-57).

**Dimostrazione di $KB\models\lnot P_{1,2}$** (p. 58), con le regole della sezione precedente:
- $R_6$: $(B_{1,1}\Rightarrow(P_{1,2}\lor P_{2,1}))\land((P_{1,2}\lor P_{2,1})\Rightarrow B_{1,1})$, da $R_2$ (eliminazione di $\Leftrightarrow$);
- $R_7$: $(P_{1,2}\lor P_{2,1})\Rightarrow B_{1,1}$, da $R_6$ (eliminazione di $\land$);
- $R_8$: $\lnot B_{1,1}\Rightarrow\lnot(P_{1,2}\lor P_{2,1})$, da $R_7$ (contrapposizione);
- $R_9$: $\lnot(P_{1,2}\lor P_{2,1})$, da $R_4$ e $R_8$ (modus ponens);
- $R_{10}$: $\lnot P_{1,2}\land\lnot P_{2,1}$, da $R_9$ (De Morgan);
- $R_{11}$: $\lnot P_{1,2}$, da $R_{10}$ (eliminazione di $\land$).

### Dimostrazione come ricerca
> [!quote] Dimostrazione come ricerca (pp. 59-61)
> Problema: come decidere a ogni passo qual è la regola di inferenza da applicare, e a quali premesse? Come evitare l'esplosione combinatoria? È un problema di **esplorazione di uno spazio di stati**. Una procedura di dimostrazione definisce la **direzione della ricerca** e la **strategia di ricerca**.
>
> **Direzione**: nella dimostrazione di teoremi conviene procedere **all'indietro**. Con una lettura *in avanti* delle regole, da $A, B$: $A\land B > A\land(A\land B) > \dots > A\land(A\land(A\land B))\dots$ (non si arriva mai a niente di utile). All'indietro: se si vuole dimostrare $A\land B$, si cerca di dimostrare $A$ e poi $B$; se si vuole dimostrare $A\Rightarrow B$, si assume $A$ e si cerca di dimostrare $B$; e così via.
>
> **Strategia**: *completezza*: le regole della **deduzione naturale** sono un insieme di regole di inferenza completo (due per ogni connettivo: di introduzione, ad esempio $A,B\vdash A\land B$, e di eliminazione, ad esempio $A\land B\vdash A$ e $A\land B\vdash B$); se l'algoritmo di ricerca è completo si è a posto. *Efficienza*: la complessità è alta, è un problema decidibile ma **NP-completo**.

## Risoluzione
### La regola di risoluzione
> [!quote] Regola di risoluzione per PROP (p. 63)
> E se avessimo un'**unica** regola di inferenza (senza rinunciare alla completezza)? La regola di risoluzione presuppone la forma a clausole:
> $$\frac{\{P,Q\}\qquad\{\lnot P,R\}}{\{Q,R\}}\qquad\text{ossia}\qquad\frac{P\lor Q,\ \ \lnot P\lor R}{Q\lor R}$$
> È **corretta**: basta pensare ai modelli. È preferita la notazione insiemistica delle clausole. Gli eventuali duplicati si eliminano.

**La regola in generale** (p. 64): date le clausole $\{l_1,l_2,\dots,l_i,\dots,l_k\}$ e $\{m_1,m_2,\dots,m_j,\dots,m_n\}$, si ottiene
$$\{l_1,\dots,l_{i-1},l_{i+1},\dots,l_k,\ m_1,\dots,m_{j-1},m_{j+1},\dots,m_n\}$$
dove gli $l$ e gli $m$ sono **letterali** (simboli di proposizione positivi o negativi) e $l_i$ e $m_j$ sono uguali e in opposizione logica (uno è la negazione dell'altro). **Caso particolare**: da $\{P\}$ e $\{\lnot P\}$ si ottiene $\{\ \}$, la **clausola vuota**.

> [!example] Il grafo di risoluzione (p. 65)
> Le clausole di partenza sono quelle già viste: $\{\lnot B_{1,1},P_{1,2},P_{2,1}\}\ \{\lnot P_{1,2},B_{1,1}\}\ \{\lnot P_{2,1},B_{1,1}\}\ \{\lnot B_{1,1}\}$. Il grafo disegna le risolventi ottenute: tre sono **tautologie** ($\{P_{1,2},P_{2,1},\lnot P_{1,2}\}$, $\{\lnot B_{1,1},P_{2,1},B_{1,1}\}$, $\{\lnot B_{1,1},P_{1,2},B_{1,1}\}$) e due sono $\{\lnot P_{1,2}\}$, indicata come **Goal**, e $\{\lnot P_{2,1}\}$.

> [!warning] Attenzione: un passo alla volta (p. 66)
> Da $\{P,Q\}$ e $\{\lnot P,\lnot Q\}$ **non** si ottiene $\{\ \}$: non è contraddittorio (esempio della slide: «bianco o nero» e «non bianco o non nero»). Risolvendo su $P$ si ottiene $\{Q,\lnot Q\}$, risolvendo su $Q$ si ottiene $\{P,\lnot P\}$, e lì ci si ferma. Va eliminato **un solo letterale alla volta**.

### Completezza e refutazione
> [!quote] Ma siamo sicuri che basti una regola? (p. 67)
> - **Completezza**: se $KB\models\alpha$, allora $KB\vdash_{res}\alpha$? **Non sempre**: ad esempio $KB\models\{A,\lnot A\}$ ma non è vero che $KB\vdash_{res}\{A,\lnot A\}$.
> - **Teorema di risoluzione** (*ground*): se $KB$ è insoddisfacibile, allora $KB\vdash_{res}\{\ \}$. Questa è la completezza (per refutazione).
> - **Teorema di refutazione** offre un modo alternativo: $KB\models\alpha$ sse $KB\cup\{\lnot\alpha\}$ è insoddisfacibile.
> - **Nell'esempio**: $KB\cup FC(\lnot(A\lor\lnot A))$ è insoddisfacibile? Sì, perché $KB\cup\{A\}\cup\{\lnot A\}\vdash\{\ \}$ in un passo e la regola di risoluzione è corretta. Quindi $KB\models\{A,\lnot A\}$. ($FC$ = forma clausale.)

> [!example] Refutazione (p. 68)
> Dalle stesse clausole, con il **goal negato** $\{P_{1,2}\}$ aggiunto: da $\{\lnot P_{1,2},B_{1,1}\}$ e $\{P_{1,2}\}$ si ottiene $\{B_{1,1}\}$; da $\{B_{1,1}\}$ e $\{\lnot B_{1,1}\}$ si ottiene la **clausola vuota** $\{\ \}$. Quindi $KB\models\lnot P_{1,2}$.

### Il teorema di risoluzione ground
> [!quote] Il teorema di risoluzione ground (p. 69)
> Sia $RC(S)$ l'insieme (**chiusura per risoluzione**) ottenuto applicando in tutti i modi possibili la regola di risoluzione a $S$. $RC(S)$ è **finito**.
> **Teorema**: se $S$ è insoddisfacibile allora $RC(S)$ contiene $\{\ \}$.
>
> **Dimostrazione** (della slide): se $RC(S)$ non contenesse $\{\ \}$ si potrebbe costruire un modello di $S$. Sia $P_1,P_2,\dots,P_k$ un ordinamento delle proposizioni; si assegnano valori procedendo con $i=1,\dots,k$ così: se in una clausola c'è $\lnot P_i$ e gli altri letterali sono falsi in base agli assegnamenti già fatti, si assegna *False* a $P_i$, altrimenti si assegna *True* a $P_i$. Se fosse $\{\mathit{false},\mathit{false},\dots,\mathit{false},\lnot P_i\}$ e $\{\mathit{false},\mathit{false},\dots,\mathit{false},P_i\}$, allora la clausola vuota $\{\ \}$ sarebbe in $RC(S)$.

> [!info] Non è nella slide
> La slide non dà lo pseudocodice di un algoritmo di risoluzione (come il PL-RESOLUTION del libro), né parla di clausole di Horn o di concatenazione in avanti e all'indietro: l'unico richiamo è alla ricerca **all'indietro** della p. 60 e, nel riepilogo (p. 81), al *backward chaining* con la deduzione naturale. Il procedimento di refutazione è quello degli esempi di pp. 65 e 68.

## Applicazione al planning: il mondo del Wumpus
Planning nel mondo del Wumpus come deduzione logica della sequenza di azioni ottime (p. 70).

### Regole nel CPROP
> [!example] Il Wumpus World con PROP: regole (p. 71)
> - Regola generale «c'è brezza nelle caselle adiacenti ai pozzi»: $B_{x,y}\Leftrightarrow P_{x,y+1}\lor P_{x,y-1}\lor P_{x+1,y}\lor P_{x-1,y}$ per ogni $x$ e $y$: **16 asserzioni** di questo tipo in un mondo $4\times4$.
> - C'è **esattamente un Wumpus**: $W_{1,1}\lor W_{1,2}\lor W_{1,3}\lor\dots\lor W_{4,4}$ (almeno uno) e $\lnot W_{i,j}\lor\lnot W_{k,m}$ per ogni coppia di caselle (al più uno): $16\cdot15/2=120$ asserzioni per dire che ce n'è al più uno.

### Locazione, orientamento e tempo
La slide di p. 72: per tenere traccia della locazione, $L_{1,1}\land\mathit{FacingRight}\land\mathit{Forward}\Rightarrow L_{2,1}$ **non va bene**, perché $L_{2,1}\land L_{1,1}$ è inconsistente: serve una **dimensione temporale**, cioè $L^1_{1,1}\land\mathit{FacingRight}^1\land\mathit{Forward}^1\Rightarrow L^2_{2,1}$. Lo stesso per l'orientamento: $\mathit{FacingRight}^1\land\mathit{TurnLeft}^1\Rightarrow\mathit{FacingUp}^2$.

**La rappresentazione del tempo** (p. 73):
- **fluenti** (fatti che variano nel tempo): $L^t_{x,y}\Rightarrow(\mathit{Breeze}^t\Leftrightarrow B_{x,y})$ e $L^t_{x,y}\Rightarrow(\mathit{Stench}^t\Leftrightarrow S_{x,y})$; un esempio di effetto di un'azione: $L^0_{1,1}\land\mathit{FacingEast}^0\land\mathit{Forward}^0\Rightarrow(L^1_{2,1}\land\lnot L^1_{1,1})$;
- **assiomi di stato**: $F^{t+1}\Leftrightarrow\mathit{ActionCausesF}^t\lor(F^t\land\lnot\mathit{ActionCausesNotF}^t)$. Esempi: $\mathit{HaveArrow}^{t+1}\Leftrightarrow(\mathit{HaveArrow}^t\land\lnot\mathit{Shoot}^t)$ e
$$L^{t+1}_{1,1}\Leftrightarrow\big(L^t_{1,1}\land(\lnot\mathit{Forward}^t\lor\mathit{Bump}^{t+1})\big)\lor\big(L^t_{1,2}\land(\mathit{South}^t\land\mathit{Forward}^t)\big)\lor\big(L^t_{2,1}\land(\mathit{West}^t\land\mathit{Forward}^t)\big)$$

### Sicurezza e limiti del CPROP
> [!quote] Il Wumpus World con PROP (p. 74)
> - Una casella $[i,j]$ è **sicura** se $KB\models(\lnot P_{i,j}\land\lnot W_{i,j})$.
> - Una casella $[i,j]$ **potrebbe essere considerata sicura** se $KB\cup\{P_{i,j},W_{i,j}\}$ è insoddisfacibile (nella slide la base di conoscenza è unita all'insieme delle due formule, con il simbolo $\cup$).
> - Con tutti questi simboli di proposizione: $n$ fluenti $\Rightarrow$ $2^n$ stati fisici al tempo $t$, quindi $2^{2^n}$ credenze possibili.
> - Servono procedure di inferenza **efficienti** (TT-Entails e DPLL non sono praticabili).
> - **Serve un linguaggio più espressivo!** (la slide non dice quale: il linguaggio più espressivo che si usa dopo è quello della [[05 - Logica del primo ordine]]; il collegamento non è scritto nella slide).

### Planning come ricerca
Le pp. 75-77 riportano la figura 7.20 del libro, un **agente ibrido** per il Wumpus: usa una base di conoscenza proposizionale per inferire lo stato del mondo, e una combinazione di ricerca (problem solving) e codice specifico del dominio per decidere le azioni.

```pseudo
\begin{algorithm}
\caption{Hybrid-Wumpus-Agent($percept$)}
\begin{algorithmic}
\State \textbf{input:} $percept$, una lista $[stench, breeze, glitter, bump, scream]$
\State \textbf{persistenti:} $KB$, una base di conoscenza, inizialmente la «fisica del Wumpus» atemporale; $t$, un contatore del tempo, inizialmente 0; $plan$, una sequenza di azioni, inizialmente vuota
\State \Call{Tell}{$KB$, \Call{Make-Percept-Sentence}{$percept, t$}}
\State \Call{Tell}{$KB$, le formule temporali della «fisica» per il tempo $t$}
\State $safe \gets \{[x,y] : \Call{Ask}{KB, OK^t_{x,y}} = true\}$
\If{\Call{Ask}{$KB, Glitter^t$} $= true$}
  \State $plan \gets [Grab] + $ \Call{Plan-Route}{$current, \{[1,1]\}, safe$} $+ [Climb]$
\EndIf
\If{$plan$ è vuoto}
  \State $unvisited \gets \{[x,y] : \Call{Ask}{KB, L^{t'}_{x,y}} = false$ per ogni $t' \le t\}$
  \State $plan \gets$ \Call{Plan-Route}{$current, unvisited \cap safe, safe$}
\EndIf
\If{$plan$ è vuoto \textbf{and} \Call{Ask}{$KB, HaveArrow^t$} $= true$}
  \State $possible\_wumpus \gets \{[x,y] : \Call{Ask}{KB, \lnot W_{x,y}} = false\}$
  \State $plan \gets$ \Call{Plan-Shot}{$current, possible\_wumpus, safe$}
\EndIf
\If{$plan$ è vuoto} \Comment{non c'è scelta: bisogna correre un rischio}
  \State $not\_unsafe \gets \{[x,y] : \Call{Ask}{KB, \lnot OK^t_{x,y}} = false\}$
  \State $plan \gets$ \Call{Plan-Route}{$current, unvisited \cap not\_unsafe, safe$}
\EndIf
\If{$plan$ è vuoto}
  \State $plan \gets$ \Call{Plan-Route}{$current, \{[1,1]\}, safe$} $+ [Climb]$
\EndIf
\State $action \gets$ \Call{Pop}{$plan$}
\State \Call{Tell}{$KB$, \Call{Make-Action-Sentence}{$action, t$}}
\State $t \gets t + 1$
\State \Return $action$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Plan-Route($current, goals, allowed$)}
\begin{algorithmic}
\State \textbf{input:} $current$, la posizione dell'agente; $goals$, un insieme di caselle (si cerca di pianificare un percorso verso una di esse); $allowed$, un insieme di caselle che possono far parte del percorso
\State $problem \gets$ \Call{Route-Problem}{$current, goals, allowed$}
\State \Return \Call{A*-Graph-Search}{$problem$}
\end{algorithmic}
\end{algorithm}
```

La slide non descrive `Plan-Shot`, `Route-Problem` e le formule della «fisica» temporale: l'agente è riportato come nel libro.

### Planning con un SAT solver (SATplan)
> [!quote] Come usare il PROP per pianificare (pp. 78-79)
> Creare una formula che descriva lo stato iniziale, le possibili continuazioni e il goal; fornire la formula a un **SAT solver**; se la soluzione esiste, il modello di essa contiene assegnazioni di valori di verità alle azioni che in ordine costituiscono il piano; oppure la soluzione e il piano sono impossibili.
>
> **In dettaglio**:
> 1. La formula iniziale in CPROP include: (a) $\mathit{Init}_0$, la collezione di asserzioni riguardo lo stato iniziale; (b) $\mathit{Transition}_1,\dots,\mathit{Transition}_t$, gli assiomi di transizione *successor-state* per tutte le possibili azioni in ogni tempo $t$ fino a un tempo massimo $t$; (c) l'asserzione che il goal sia raggiunto al tempo $t$: $\mathit{HaveGold}_t\land\mathit{ClimbedOut}_t$.
> 2. Applicare un SAT solver: se la soluzione esiste allora il goal è soddisfacibile, altrimenti il planning problem non ha soluzioni.
> 3. Assumendo che il modello sia stato trovato, estrarre da esso le variabili che rappresentano le azioni e che sono assegnate a True dalla soluzione: rappresentano (in ordine) il piano che risolve il problema, cioè raggiunge il goal.

**Un algoritmo per il SATplan** (p. 80, figura 7.22 del libro: il problema di planning è tradotto in una formula CNF in cui il goal vale a un passo temporale fissato $t$, con gli assiomi per ogni passo fino a $t$; se l'algoritmo di soddisfacibilità trova un modello si estrae il piano guardando i simboli che si riferiscono ad azioni e sono veri nel modello; se non esiste un modello il procedimento si ripete spostando il goal di un passo più avanti):

```pseudo
\begin{algorithm}
\caption{SATplan($init, transition, goal, T_{max}$)}
\begin{algorithmic}
\State \textbf{input:} $init, transition, goal$ descrivono il problema; $T_{max}$ è un limite superiore alla lunghezza del piano
\For{$t = 0$ \textbf{to} $T_{max}$}
  \State $cnf \gets$ \Call{Translate-To-SAT}{$init, transition, goal, t$}
  \State $model \gets$ \Call{SAT-Solver}{$cnf$}
  \If{$model$ non è nullo}
    \State \Return \Call{Extract-Solution}{$model$}
  \EndIf
\EndFor
\State \Return $failure$
\end{algorithmic}
\end{algorithm}
```

## Riepilogo della slide
Il riepilogo (p. 81, *SummarAIzing*) elenca: sintassi e semantica del calcolo proposizionale; una rappresentazione proposizionale del mondo (esempio: il mondo del Wumpus); conseguenza logica e inferenza nel PROP; algoritmi per la soddisfacibilità delle formule (enumerazione delle tabelle di verità con TT-Entails, l'algoritmo di Davis-Putnam, WalkSAT); dimostrazione automatica (deduzione naturale e backward chaining, la risoluzione); il mondo del Wumpus e l'uso della risoluzione.
