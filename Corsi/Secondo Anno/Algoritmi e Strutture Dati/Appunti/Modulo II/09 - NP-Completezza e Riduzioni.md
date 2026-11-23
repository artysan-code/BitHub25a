---
tags:
  - algoritmi
  - np-completezza
slide: "8"
capitolo: "Kleinberg-Tardos cap. 8"
---
# NP-Completezza e Riduzioni
La teoria dell'intrattabilità studia quali problemi computazionali non ammettono algoritmi efficienti — cioè polinomiali nel tempo — e perché. Invece di sperare di trovare un algoritmo ottimo per ciascuno, l'idea fondamentale è classificare i problemi rispetto alla loro **difficoltà relativa** tramite le **riduzioni polinomiali**: se so risolvere Y efficientemente, riesco a risolvere anche X? Le nozioni di classe P, NP e NP-completezza nascono da questa domanda e hanno implicazioni concrete per la progettazione di algoritmi. Questa nota è strettamente collegata a [[04 - Programmazione Dinamica I (Weighted Independent Set)]], dove il problema Independent Set su grafi generali emerge come variante intrattabile di quello su grafi a intervalli.
## Pattern e anti-pattern nella progettazione
Il corso ha presentato vari **pattern** algoritmici: greedy ([[01 - Greedy e Interval Scheduling]]), divide et impera ([[03 - Equazioni di Ricorrenza|equazioni di ricorrenza]]), programmazione dinamica ([[04 - Programmazione Dinamica I (Weighted Independent Set)]], [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]], [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]]), dualità e flussi ([[07 - Flussi di Rete (Max-Flow e Min-Cut)]]), riduzioni e ricerca locale. Accanto ai pattern esistono però degli **anti-pattern**, ovvero famiglie di problemi per le quali certe garanzie sono verosimilmente irraggiungibili:

| Anti-pattern | Significato |
|---|---|
| **NP-completezza** | un algoritmo $O(n^k)$ è improbabile |
| PSPACE-completezza | un algoritmo di certificazione $O(n^k)$ è improbabile |
| Indecidibilità | nessun algoritmo è possibile |
Questa nota si concentra sulla prima categoria.
## Classificare i problemi: l'approccio per efficienza
> [!quote] Definizione — Problema trattabile (working definition)
> Un problema è **trattabile** se esiste un algoritmo che lo risolve in tempo **polinomiale** nella dimensione dell'input: $O(n^k)$ per qualche costante $k$.

La scelta "polinomiale = efficiente" è sia teoricamente robusta (stessa su Turing machine, RAM uniforme, circuiti) sia pratica: le costanti tendono ad essere piccole, e gli algoritmi polinomiali scalano su input enormi.

La tabella seguente mostra coppie di problemi simili dove uno è trattabile e l'altro probabilmente no:

| Problema trattabile | Problema (probabilmente) intrattabile |
|---|---|
| [[10 - Cammini Minimi e Dijkstra\|Cammino minimo (shortest path)]] | Cammino più lungo (longest path) |
| Min Cut ([[07 - Flussi di Rete (Max-Flow e Min-Cut)]]) | Max Cut |
| 2-Soddisfacibilità (2-SAT) | 3-Soddisfacibilità (3-SAT) |
| 4-Colorabilità planare | 3-Colorabilità planare |
| Vertex Cover su grafi bipartiti | Vertex Cover su grafi generali |
| Matching | 3-Dimensional Matching |
| Test di primalità | Fattorizzazione |
| Programmazione lineare | Programmazione lineare intera |
## Riduzioni polinomiali
> [!quote] Definizione — Riduzione polinomiale ($\leq_P$)
> Il problema $X$ si **riduce polinomialmente** al problema $Y$ (scritto $X \leq_P Y$) se ogni istanza di $X$ può essere risolta usando:
> - un numero **polinomiale** di passi computazionali standard, più
> - un numero **polinomiale** di chiamate a un **oracolo** che risolve $Y$ in un singolo passo.
>
> Le istanze inviate all'oracolo devono avere dimensione polinomiale nell'input originale.

Lo schema concettuale è:

```
istanza I (di X)  -->  [Algoritmo per X]  -->  oracolo per Y  -->  soluzione S di I
```

> [!warning] Errore frequente — direzione della riduzione
> $X \leq_P Y$ significa che $X$ **non è più difficile** di $Y$: se so risolvere $Y$, so risolvere anche $X$. **Non** significa che $Y$ è più facile di $X$. Confondere la direzione è l'errore più comune.

Le riduzioni servono a tre scopi:
1. **Progettare algoritmi**: se $X \leq_P Y$ e $Y$ è risolvibile in tempo polinomiale, allora anche $X$ lo è.
2. **Stabilire intrattabilità**: se $X \leq_P Y$ e $X$ non è risolvibile in tempo polinomiale, allora nemmeno $Y$ lo è.
3. **Stabilire equivalenza**: se $X \leq_P Y$ e $Y \leq_P X$, scriviamo $X \equiv_P Y$: i due problemi hanno la stessa difficoltà computazionale.

> [!quote] Proprietà — Transitività delle riduzioni
> Se $X \leq_P Y$ e $Y \leq_P Z$, allora $X \leq_P Z$.
>
> **Idea della dimostrazione**: componiamo i due algoritmi di riduzione. L'algoritmo per $X$ chiama l'oracolo per $Y$; ogni chiamata all'oracolo per $Y$ è simulata dall'algoritmo che riduce $Y$ a $Z$, che a sua volta chiama l'oracolo per $Z$. Il numero totale di passi rimane polinomiale.

> [!question] Domanda tipica d'esame — Definizione formale di riduzione polinomiale
> **D:** «Si definisca formalmente il concetto di riduzione polinomiale fra problemi. (Max 5 righe.)» *(chiesto il 16/07/2024)*
> **R:**
> **Definizione.** $X$ si riduce polinomialmente a $Y$ (scritto $X \leq_P Y$) se esiste un algoritmo che risolve ogni istanza di $X$ usando un numero **polinomiale** di passi di calcolo standard, più un numero **polinomiale** di chiamate a un **oracolo** che risolve $Y$ in un singolo passo.
>
> **Vincolo di dimensione.** Ogni istanza passata all'oracolo deve avere dimensione **polinomiale** rispetto a quella originale di $X$: senza questa condizione l'oracolo potrebbe nascondere lavoro esponenziale nella sola costruzione dell'istanza da passargli, e la definizione perderebbe significato.
>
> **Interpretazione.** $X \leq_P Y$ vuol dire che $X$ non è più difficile di $Y$: un ipotetico algoritmo polinomiale per $Y$, composto con l'algoritmo di riduzione, produce immediatamente un algoritmo polinomiale per $X$.
>
> ⏱️ **Se la traccia dà 5 righe**: scrivi la definizione con i due conteggi polinomiali e il vincolo di dimensione sull'oracolo (2-3 righe), chiudi con l'interpretazione «$X$ non più difficile di $Y$» (1 riga). **Il vincolo di dimensione polinomiale sull'istanza passata all'oracolo non va mai omesso**: senza di esso la definizione è vuota, perché l'oracolo potrebbe fare lavoro esponenziale mascherato nella costruzione dell'istanza.

> [!question] Domanda tipica d'esame — Riduzioni come evidenza di intrattabilità
> **D:** «Si argomenti su come è possibile utilizzare le riduzioni polinomiali per dare evidenza che un problema è computazionalmente difficile. (Max 5 righe.)» *(chiesto il 16/07/2024)*
> **R:**
> **Idea.** Si usa la contronominale della definizione di riduzione: se $X \leq_P Y$ e $Y$ fosse risolvibile in tempo polinomiale, lo sarebbe anche $X$.
>
> **Argomento per assurdo.** Dimostrato $X \leq_P Y$ con $X$ (ritenuto) intrattabile: se esistesse un algoritmo polinomiale per $Y$, componendolo con l'algoritmo di riduzione si otterrebbe un algoritmo polinomiale anche per $X$ — contraddizione con l'ipotesi su $X$. Quindi anche $Y$ deve essere intrattabile.
>
> **Applicazione a catena.** Concatenando riduzioni a partire da un problema NP-completo "capostipite" (tipicamente 3-SAT, per Cook-Levin) si trasferisce questa evidenza a un'intera famiglia di problemi: si dimostra che sono tutti NP-hard senza dover trovare per ciascuno una dimostrazione diretta e indipendente di intrattabilità.
>
> ⏱️ **Se la traccia dà 5 righe**: enuncia l'idea della contronominale (1 riga), l'argomento per assurdo in forma sintetica «un algoritmo poli per $Y$ + riduzione darebbe un algoritmo poli per $X$» (2 righe), chiudi con l'applicazione a catena da 3-SAT (1-2 righe). **La direzione della contronominale non si può omettere**: è il punto che distingue l'uso corretto della riduzione da quello invertito, l'errore più comune su questo argomento.
## Classi P e NP
> [!quote] Definizione — Classe P
> Un problema decisionale $X$ è un insieme di stringhe e un'istanza $s$ è una stringa. Un algoritmo $A$ **risolve** $X$ se $A(s) = \text{yes}$ per $s \in X$ e $A(s) = \text{no}$ per $s \notin X$. $A$ è **polinomiale** se per ogni stringa $s$ termina in al più $p(|s|)$ «passi», con $p(\cdot)$ un polinomio e $|s|$ la lunghezza di $s$.
>
> **P** è l'insieme dei problemi decisionali per cui esiste un algoritmo polinomiale (su macchina di Turing deterministica).

Esempi di problemi in P (dalla slide):

| Problema | Domanda | Algoritmo polinomiale |
|---|---|---|
| MULTIPLE | $x$ è multiplo di $y$? | divisione scolastica |
| REL-PRIME | $x$ e $y$ sono coprimi? | algoritmo di Euclide |
| PRIMES | $x$ è primo? | Agrawal–Kayal–Saxena (2002) |
| EDIT-DISTANCE | la edit distance tra $x$ e $y$ è minore di 5? | Needleman–Wunsch |
| L-SOLVE | esiste un vettore $x$ con $Ax = b$? | eliminazione di Gauss–Edmonds |
| U-CONN | il grafo non orientato $G$ è connesso? | visita in profondità (DFS) |

> [!quote] Definizione — Certificatore e classe NP
> Un algoritmo $C(s,t)$ è un **certificatore** per il problema $X$ se per ogni stringa $s$: $s \in X$ se e solo se esiste una stringa $t$ tale che $C(s,t) = \text{yes}$. La stringa $t$ è il **certificato** (o *witness*).
>
> **NP** è l'insieme dei problemi decisionali per cui esiste un certificatore polinomiale:
> - $C(s,t)$ è un algoritmo polinomiale;
> - il certificato ha dimensione polinomiale: $|t| \leq p(|s|)$ per qualche polinomio $p(\cdot)$.

> [!info] Intuizione: NP come "facile da verificare"
> Trovare una soluzione può essere difficile; verificarne la correttezza è spesso facile. Per Independent Set: dato un sottoinsieme $S$ di vertici, basta controllare che nessuna coppia in $S$ sia adiacente — tempo $O(k^2)$ o $O(m)$.

Esempi di certificati (dalla slide), accanto a quello di Vertex Cover (dimostrato più sotto):

| Problema | Certificato $t$ | Certificatore $C(s,t)$ |
|---|---|---|
| COMPOSITES ($x$ è composto?) | un fattore non banale: per $s = 437669$, $t = 541$ ($437669 = 541 \times 809$) | divisione scolastica |
| SAT, 3-SAT | un assegnamento di verità alle variabili | controlla che ogni clausola di $\Phi$ abbia almeno un letterale vero |
| HAMILTON-PATH (esiste un cammino semplice che visita ogni nodo?) | una permutazione $\pi$ degli $n$ nodi | controlla che $\pi$ contenga ogni nodo di $V$ esattamente una volta e che $G$ abbia un arco tra ogni coppia di nodi adiacenti in $\pi$ |

Quindi SAT, 3-SAT e HAMILTON-PATH sono in NP.

> [!quote] Proposizione — $\mathrm{P} \subseteq \mathrm{NP} \subseteq \mathrm{EXP}$
> **EXP** è l'insieme dei problemi decisionali per cui esiste un algoritmo di tempo esponenziale.
>
> **P $\subseteq$ NP.** Sia $X \in \mathrm{P}$: per definizione esiste un algoritmo polinomiale $A(s)$ che risolve $X$. Si prende come certificato la stringa vuota $t = \varepsilon$ e come certificatore $C(s,t) = A(s)$. $\square$
>
> **NP $\subseteq$ EXP.** Sia $X \in \mathrm{NP}$: esiste un certificatore polinomiale $C(s,t)$ con $|t| \leq p(|s|)$ per un polinomio $p(\cdot)$. Per risolvere l'istanza $s$ si esegue $C(s,t)$ su **tutte** le stringhe $t$ con $|t| \leq p(|s|)$ e si risponde yes se e solo se $C(s,t)$ restituisce yes per almeno uno di questi potenziali certificati. $\square$

**Fatto.** $\mathrm{P} \neq \mathrm{EXP} \Rightarrow$ $\mathrm{P} \neq \mathrm{NP}$, oppure $\mathrm{NP} \neq \mathrm{EXP}$, o entrambe.

### Riduzione di Cook e trasformazione di Karp
> [!quote] Definizione — Riduzione di Cook e trasformazione di Karp
> - Il problema $X$ si riduce (**Cook**) in tempo polinomiale al problema $Y$ se ogni istanza di $X$ si risolve con un numero polinomiale di passi standard più un numero polinomiale di chiamate a un oracolo per $Y$ (la definizione di riduzione vista sopra).
> - Il problema $X$ si trasforma (**Karp**) in tempo polinomiale in $Y$ se, data una qualsiasi istanza $x$ di $X$, si può costruire un'istanza $y$ di $Y$ tale che $x$ è un'istanza yes di $X$ se e solo se $y$ è un'istanza yes di $Y$. Si richiede che $|y|$ sia polinomiale in $|x|$.

La trasformazione di Karp è una riduzione con **una sola chiamata** all'oracolo per $Y$, fatta alla fine dell'algoritmo per $X$. Quasi tutte le riduzioni viste finora hanno questa forma (3-SAT $\leq_P$ Independent Set, Vertex Cover $\leq_P$ Set Cover, ...).

> [!warning] Uso dei simboli
> Domanda aperta: i due concetti coincidono rispetto a NP? La slide osserva che si abusa della notazione $\leq_P$ e si sfuma la distinzione: lo stesso simbolo indica sia la riduzione di Cook sia la trasformazione di Karp.

### NP-completo
> [!quote] Definizione — NP-completo
> Un problema $Y$ è **NP-completo** se $Y \in \mathrm{NP}$ e per ogni problema $X \in \mathrm{NP}$ vale $X \leq_P Y$.

> [!info] NP-hard *(extra, non da slide)*
> Un problema $Y$ è **NP-hard** se ogni $X \in \mathrm{NP}$ soddisfa $X \leq_P Y$, senza richiedere $Y \in \mathrm{NP}$: $Y$ è NP-completo se è NP-hard **e** appartiene a NP. Nelle slide di Intractability II compare solo la definizione di NP-completo; il termine NP-hard è usato nelle slide di approssimazione per i problemi di ottimizzazione.

> [!quote] Proposizione — $Y$ NP-completo: $Y \in \mathrm{P}$ se e solo se $\mathrm{P} = \mathrm{NP}$
> **Dimostrazione ($\Leftarrow$):** se $\mathrm{P} = \mathrm{NP}$, allora $Y \in \mathrm{P}$ perché $Y \in \mathrm{NP}$.
>
> **Dimostrazione ($\Rightarrow$):** sia $Y \in \mathrm{P}$ e sia $X \in \mathrm{NP}$ qualsiasi. Poiché $X \leq_P Y$, anche $X \in \mathrm{P}$. Quindi $\mathrm{NP} \subseteq \mathrm{P}$; già sappiamo che $\mathrm{P} \subseteq \mathrm{NP}$, dunque $\mathrm{P} = \mathrm{NP}$. $\square$

Domanda fondamentale: esistono problemi NP-completi «naturali»?

> [!quote] Teorema — Cook-Levin (Cook 1971, Levin 1973)
> Il problema **SAT** (soddisfacibilità booleana in forma normale congiuntiva) è NP-completo.
>
> È il «primo» problema NP-completo: dimostrare che tutti i problemi di NP si riducono a SAT.

> [!quote] Ricetta — dimostrare che $Y$ è NP-completo
> Una volta stabilito il primo problema NP-completo «naturale», gli altri cadono come domino:
> 1. **Passo 1.** Mostrare che $Y \in \mathrm{NP}$.
> 2. **Passo 2.** Scegliere un problema NP-completo $X$.
> 3. **Passo 3.** Dimostrare che $X \leq_P Y$.
>
> **Proposizione.** Se $X$ è NP-completo, $Y \in \mathrm{NP}$ e $X \leq_P Y$, allora $Y$ è NP-completo.
>
> **Dimostrazione:** sia $W \in \mathrm{NP}$ qualsiasi. Per definizione di NP-completo $W \leq_P X$, e per ipotesi $X \leq_P Y$. Per transitività $W \leq_P Y$. Quindi $Y$ è NP-completo. $\square$

> [!info] P vs NP — la grande domanda aperta
> Se anche un solo problema NP-completo fosse risolvibile in tempo polinomiale, allora **P = NP** e tutti i problemi di NP lo sarebbero (proposizione sopra): algoritmi efficienti per 3-SAT, TSP, VERTEX-COVER, FACTOR, ... Se invece $\mathrm{P} \neq \mathrm{NP}$, per questi problemi non esistono algoritmi efficienti. La domanda è attribuita a Cook 1971, Edmonds, Levin, Yablonski, Gödel; l'opinione prevalente è **P ≠ NP**, ma non è dimostrato. Per il progettista di algoritmi la lezione pratica è: se un problema è NP-completo, non cercare un algoritmo esatto polinomiale — passa ad approssimazioni, euristiche o algoritmi parametrizzati.

### Certificatori in pratica: Vertex Cover in NP
> [!question] Domanda tipica d'esame — Certificatore efficiente, classe NP e Vertex Cover
> **D:** «Si definisca formalmente cos'è un Certificatore efficiente (Efficient Certifier) e si usi tale concetto per definire la classe di problemi NP. Infine, si definisca la versione decisionale del problema del Minimum Vertex Cover indicando come è fatta una generica istanze di input e quale è la domanda del problema. Si dimostri che tale problema appartiene alla classe NP.» *(chiesto il 27/09/2023)*
> **R:**
> **Certificatore efficiente.** Per un problema decisionale $X$, è un algoritmo $B(s, t)$ che prende in input un'istanza $s$ e un **certificato** $t$ (una presunta prova/soluzione), gira in tempo **polinomiale** in $|s|$, ed è tale che $s \in X$ se e solo se esiste un certificato $t$ con $|t|$ **polinomiale** in $|s|$ per cui $B(s,t)$ = "sì". Un certificatore non deve trovare la soluzione: deve solo verificarla, in modo rapido, quando qualcuno gliela mostra.
>
> **Classe NP.** È la classe dei problemi decisionali che ammettono un certificatore efficiente: problemi per cui, pur non sapendo (in generale) risolvere l'istanza in tempo polinomiale, sappiamo verificarne una soluzione candidata in tempo polinomiale.
>
> **Minimum Vertex Cover (decisionale) — istanza e domanda.** Istanza $(G=(V,E), k)$ con $k$ intero. Domanda: esiste un sottoinsieme $C \subseteq V$ con $|C| \leq k$ tale che ogni arco di $E$ abbia almeno un estremo in $C$?
>
> **Dimostrazione — Vertex Cover $\in$ NP.** Si usa come certificato l'insieme $C$ stesso: $|C| \leq |V|$, quindi la dimensione del certificato è polinomiale in $|V|$. Il certificatore verifica in tempo $O(|V| + |E|)$ che $|C| \leq k$ e che, scorrendo tutti gli archi di $E$, ciascuno abbia almeno un estremo in $C$ (test di appartenenza in $O(1)$ con un vettore booleano indicizzato sui vertici). Poiché sia la dimensione del certificato sia il tempo di verifica sono polinomiali nella dimensione dell'istanza, Vertex Cover $\in$ NP.
### Asimmetria di NP e co-NP
Per i problemi in NP servono certificati brevi **solo per le istanze yes**. Per SAT si prova che una formula è soddisfacibile mostrando un assegnamento, ma non è chiaro come provare che una formula **non** lo è (UN-SAT). Stesso discorso per HAMILTON-CYCLE (si mostra una permutazione dei nodi) contro NO-HAMILTON-CYCLE. SAT e HAMILTON-CYCLE sono NP-completi e $\text{SAT} \equiv_P \text{UN-SAT}$, $\text{HAMILTON-CYCLE} \equiv_P \text{NO-HAMILTON-CYCLE}$, ma né UN-SAT né NO-HAMILTON-CYCLE sono noti in NP. Altri due problemi che probabilmente non stanno in NP: CHECKERS (in una scacchiera $n \times n$, il nero può garantirsi la vittoria?) e CO-LONGEST-PATH (la lunghezza del cammino semplice più lungo è $\leq k$?).

> [!quote] Definizione — Complemento e co-NP
> Dato un problema decisionale $X$, il suo **complemento** $\overline{X}$ è lo stesso problema con le risposte yes e no invertite. Esempio: $X = \{4, 6, 8, 9, 10, 12, 14, 15, \dots\}$ (i numeri composti), $\overline{X} = \{2, 3, 5, 7, 11, 13, 17, 23, 29, \dots\}$ (i primi, ignorando 0 e 1).
>
> **co-NP** è la classe dei complementi dei problemi in NP. Esempi: UN-SAT, NO-HAMILTON-CYCLE, PRIMES.

> [!info] NP = co-NP ?
> È una domanda aperta fondamentale: le istanze yes hanno certificati succinti sse li hanno le istanze no? L'opinione prevalente è di no.

> [!quote] Teorema — $\text{NP} \neq \text{co-NP} \Rightarrow \text{P} \neq \text{NP}$
> **Idea della dimostrazione:** P è chiusa per complemento (basta invertire la risposta dell'algoritmo polinomiale). Se $\text{P} = \text{NP}$, allora anche NP è chiusa per complemento, cioè $\text{NP} = \text{co-NP}$. Questa è la contronominale del teorema. $\square$

### Problemi NP-intermedi
Nella pratica quasi tutti i problemi in NP si sa che sono in P oppure NP-completi. Candidati a essere **NP-intermedi** (né in P né NP-completi): FACTOR, DISCRETE-LOG, GRAPH-ISOMORPHISM.

> [!quote] Teorema (Ladner 1975)
> A meno che $\text{P} = \text{NP}$, esistono problemi in NP che non sono né in P né NP-completi.
## Problemi di packing e covering
### Independent Set
> [!quote] Definizione — Independent Set
> Dato un grafo $G = (V, E)$ e un intero $k$, il problema **Independent Set** chiede: esiste un sottoinsieme $S \subseteq V$ di $|S| \geq k$ vertici tale che nessun arco di $E$ abbia entrambi gli estremi in $S$?

Gli $n$ vertici di $S$ sono **indipendenti**: nessuna coppia è collegata da un arco.

```
  a --- b --- c
  |         /
  d ------- e
```
Esempio: $\{a, c, d\}$ non è indipendente ($a$–$d$ è un arco); $\{b, d\}$ è indipendente.

Questo problema si collega direttamente a [[04 - Programmazione Dinamica I (Weighted Independent Set)]]: lì il grafo è un **cammino** (struttura a intervalli), il che lo rende risolvibile in tempo polinomiale con DP. Su grafi generali diventa NP-completo.
### Vertex Cover
> [!quote] Definizione — Vertex Cover
> Dato un grafo $G = (V, E)$ e un intero $k$, il problema **Vertex Cover** chiede: esiste un sottoinsieme $C \subseteq V$ di $|C| \leq k$ vertici tale che ogni arco di $E$ abbia **almeno un** estremo in $C$?

I vertici in $C$ "coprono" tutti gli archi.
### Equivalenza tra Independent Set e Vertex Cover
> [!quote] Teorema — INDEPENDENT-SET $\equiv_P$ VERTEX-COVER
> $S$ è un independent set di dimensione $k$ **se e solo se** $V \setminus S$ è un vertex cover di dimensione $n - k$.

**Dimostrazione ($\Rightarrow$):** Sia $S$ un independent set di dimensione $k$; $V \setminus S$ ha dimensione $n - k$. Per ogni arco $(u, v) \in E$: poiché $S$ è indipendente, $u \notin S$ o $v \notin S$ (o entrambi), ovvero $u \in V \setminus S$ o $v \in V \setminus S$. Quindi $V \setminus S$ copre ogni arco. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $V \setminus S$ un vertex cover di dimensione $n - k$; quindi $|S| = k$. Per ogni arco $(u,v) \in E$: poiché $V \setminus S$ è un vertex cover, $u \in V \setminus S$ o $v \in V \setminus S$, ovvero $u \notin S$ o $v \notin S$. Quindi $S$ è indipendente. $\square$

> [!info] Schema di riduzione: equivalenza semplice
> La riduzione è banale ($O(1)$ lavoro aggiuntivo): dato $(G, k)$ per Independent Set, costruiamo $(G, n-k)$ per Vertex Cover, e viceversa. La stessa istanza del grafo funziona per entrambi. Questo è il pattern **"equivalenza semplice"** nelle riduzioni.
### Set Cover
> [!quote] Definizione — Set Cover
> Dato un universo $U$ di elementi, una collezione $\mathcal{S}$ di sottoinsiemi di $U$ e un intero $k$, il problema **Set Cover** chiede: esistono $\leq k$ sottoinsiemi in $\mathcal{S}$ la cui unione è $U$?

**Esempio:** $U = \{1,2,3,4,5,6,7\}$, $S_a = \{3,7\}$, $S_b = \{2,4\}$, $S_c = \{3,4,5,6\}$, $S_d = \{5\}$, $S_e = \{1\}$, $S_f = \{1,2,6,7\}$, $k = 2$: si cerca una coppia di insiemi che copra tutto $U$.

**Applicazione pratica:** dati $m$ software e $n$ funzionalità desiderate, ogni software fornisce un sottoinsieme di funzionalità; si vuole ottenere tutte le $n$ funzionalità usando il minor numero di software.

**Un altro esempio:** $U = \{1,2,3,4,5,6,7\}$, $S_a = \{1,4,6\}$, $S_b = \{1,6,7\}$, $S_c = \{1,2,3,6\}$, $S_d = \{1,3,5,7\}$, $S_e = \{2,6,7\}$, $S_f = \{3,4,5\}$. La dimensione minima di un set cover è **3** (per esempio $\{S_a, S_d, S_e\}$ ha unione $U$; nessuna coppia di insiemi copre $U$).
### Riduzione: Vertex Cover $\leq_P$ Set Cover
> [!quote] Teorema — VERTEX-COVER $\leq_P$ SET-COVER
> **Costruzione:** data un'istanza $(G, k)$ di Vertex Cover, costruiamo l'istanza $(U, \mathcal{S}, k)$ di Set Cover come segue:
> - Universo: $U = E$ (gli archi del grafo).
> - Per ogni vertice $v \in V$, definiamo $S_v = \{e \in E : e \text{ è incidente a } v\}$.
>
> **Lemma:** $G$ ha un vertex cover di dimensione $k$ se e solo se $(U, \mathcal{S}, k)$ ha un set cover di dimensione $k$.

**Dimostrazione ($\Rightarrow$):** Sia $X \subseteq V$ un vertex cover di dimensione $k$. Allora $\{S_v : v \in X\}$ è un set cover: ogni arco $e \in E$ è incidente a qualche $v \in X$ (per definizione di vertex cover), quindi $e \in S_v$, cioè $e$ è coperto. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $\mathcal{Y} \subseteq \mathcal{S}$ un set cover di dimensione $k$. Allora $X = \{v : S_v \in \mathcal{Y}\}$ è un vertex cover: per ogni arco $e \in E$, esiste $S_v \in \mathcal{Y}$ con $e \in S_v$, cioè $e$ è incidente a $v \in X$. $\square$

> [!info] Schema di riduzione: caso speciale → caso generale
> Vertex Cover è un caso speciale di Set Cover in cui ogni insieme $S_v$ corrisponde agli archi incidenti a un vertice. Il pattern **"caso speciale → caso generale"** è una strategia comune: si mostra che istanze del problema semplice corrispondono a istanze del problema più generale.
## Problemi di soddisfacibilità
### SAT e 3-SAT
> [!quote] Definizione — SAT e 3-SAT
> Un **letterale** è una variabile booleana $x_i$ o la sua negazione $\overline{x_i}$. Una **clausola** è una disgiunzione di letterali. La **forma normale congiuntiva** (CNF) è una congiunzione di clausole.
>
> **SAT**: data una formula CNF $\Phi$, esiste un assegnamento di verità che soddisfa $\Phi$?
>
> **3-SAT**: come SAT, ma ogni clausola contiene **esattamente 3 letterali** distinti.

**Esempio di istanza 3-SAT soddisfacibile:**
$$\Phi = (x_1 \vee x_2 \vee \overline{x_3}) \wedge (\overline{x_1} \vee x_2 \vee x_4) \wedge (\overline{x_2} \vee \overline{x_3} \vee \overline{x_4})$$
Assegnamento soddisfacente: $x_1 = \top, x_2 = \top, x_3 = \bot, x_4 = \bot$.

> [!quote] Ipotesi scientifica — 3-SAT è intrattabile
> Non esiste un algoritmo polinomiale per 3-SAT. Questa ipotesi è **equivalente** alla congettura $\mathrm{P} \neq \mathrm{NP}$.

3-SAT è NP-completo (Intractability II, p. 28), a partire dal teorema di Cook-Levin su SAT.

**Applicazioni:** il SAT è alla base dell'**Electronic Design Automation** (EDA): la verifica formale di circuiti digitali si riduce spesso a problemi di soddisfacibilità.
## La riduzione chiave: 3-SAT $\leq_P$ Independent Set
> [!quote] Teorema — 3-SAT $\leq_P$ INDEPENDENT-SET
> **Costruzione:** data un'istanza $\Phi$ di 3-SAT con $m$ clausole, costruiamo $(G, k)$ con $k = m$ come segue:
> - Per ogni clausola, inserire 3 nodi (uno per letterale) collegati in un **triangolo**.
> - Collegare ogni nodo al nodo corrispondente alla sua **negazione** nelle altre clausole.

Schema ASCII per una formula con 3 clausole $(x_1 \vee x_2 \vee \overline{x_3})$, $(\overline{x_1} \vee x_3 \vee x_4)$, $(\overline{x_2} \vee \overline{x_3} \vee x_4)$:

```
Clausola 1       Clausola 2        Clausola 3
  x1 -- x2       x1b -- x3       x2b -- x3b
   \   /    ...   \   /    ...    \    /
   x3b            x4              x4
(triangoli interni; archi tra letterali opposti tra clausole diverse)
```

> [!quote] Lemma — Correttezza della riduzione 3-SAT $\leq_P$ INDEPENDENT-SET
> $\Phi$ è soddisfacibile se e solo se $G$ contiene un independent set di dimensione $k = |\Phi|$ (numero di clausole).

**Dimostrazione ($\Rightarrow$):** Sia $\alpha$ un assegnamento soddisfacente. Da ogni triangolo (clausola) scegliamo **un** letterale reso vero da $\alpha$; otteniamo $k$ nodi. I nodi scelti sono indipendenti: (a) provengono da triangoli *distinti*, quindi non ci sono archi intra-triangolo tra coppie scelte; (b) non ci sono archi di negazione tra nodi scelti: se avessimo selezionato sia $\ell$ che $\overline{\ell}$, $\alpha$ dovrebbe rendere veri entrambi — impossibile. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $S$ un independent set di dimensione $k$. Poiché i nodi di ogni triangolo formano un $K_3$ (ogni coppia è collegata da un arco), $S$ non può contenere più di un nodo per triangolo. Essendoci $k$ triangoli e $|S|=k$, $S$ contiene **esattamente un** nodo per triangolo. Assegnare "vero" ai letterali selezionati in $S$ (completando l'assegnamento in modo consistente per le variabili non selezionate) soddisfa ogni clausola. Non ci sono contraddizioni perché $S$ non può contenere sia $\ell$ che $\overline{\ell}$: sarebbero collegati da un arco di negazione, violando l'indipendenza di $S$. $\square$

> [!info] Schema di riduzione: codifica con gadget
> Questo è il pattern **"codifica con gadget"**: si costruisce una struttura locale (il triangolo) che "forza" la scelta di esattamente un elemento, e archi tra gadget che codificano i vincoli logici (la negazione). È il meccanismo più potente e comune nelle riduzioni NP.

> [!question] Domanda tipica d'esame — Definizioni formali di 3-SAT e Independent Set
> **D:** «1. Si definiscano formalmente i problemi decisionali 3-SAT e Independet Set. (Max 5 righe).» *(chiesto il 09/09/2024)*
> **R:**
> **3-SAT.** Data una formula booleana $\Phi$ in forma normale congiuntiva (CNF), in cui ogni clausola contiene esattamente 3 letterali distinti, esiste un assegnamento di verità alle variabili che soddisfa $\Phi$, cioè rende vero almeno un letterale in ciascuna clausola?
>
> **Independent Set.** Dato un grafo $G=(V,E)$ e un intero $k$, esiste un sottoinsieme $S \subseteq V$ con $|S| \geq k$ tale che nessun arco di $E$ abbia entrambi gli estremi in $S$ (i vertici di $S$ sono a due a due non adiacenti)?
>
> ⏱️ **Se la traccia dà 5 righe**: una definizione per riga (istanza + domanda), senza esempi né commenti. **Non omettere mai** la condizione "esattamente 3 letterali distinti" per 3-SAT e "$|S| \geq k$" con "nessun arco con entrambi gli estremi in $S$" per Independent Set: sono le clausole che rendono la definizione formale, non solo intuitiva.

> [!question] Domanda tipica d'esame — Da Independent Set polinomiale a 3-SAT polinomiale
> **D:** «2. Si mostri come è possibile utilizzare un (ipotetico) algoritmo polinomiale per Independet Set per risolvere 3-SAT. (Max 5 righe)» *(chiesto il 09/09/2024)*
> **R:**
> **Idea.** Si sfrutta la riduzione standard 3-SAT $\leq_P$ Independent Set: un ipotetico algoritmo polinomiale per Independent Set, composto con l'algoritmo di riduzione, dà un algoritmo polinomiale per 3-SAT.
>
> **Costruzione.** Da $\Phi$ (con $m$ clausole) si costruisce $(G, k=m)$: per ogni clausola un triangolo di 3 nodi (uno per letterale), più un arco fra ogni nodo e il nodo del suo letterale complementare nelle altre clausole. La costruzione richiede tempo polinomiale in $|\Phi|$.
>
> **Procedura.** Si invoca l'algoritmo ipotetico su $(G, k)$: se restituisce un independent set di dimensione $k$, $\Phi$ è soddisfacibile (l'assegnamento si ricostruisce dai letterali scelti in $S$); altrimenti $\Phi$ non lo è.
>
> **Complessità.** Costruzione e chiamata all'oracolo sono entrambe polinomiali, quindi il tempo totale resta polinomiale: si decide 3-SAT in tempo polinomiale.
>
> ⏱️ **Se la traccia dà 5 righe**: enuncia la riduzione con la costruzione del gadget a triangoli (2 righe), la chiamata all'algoritmo ipotetico e come interpretarne l'output (2 righe), chiudi con "tempo totale polinomiale" (1 riga). **Non omettere mai** che anche la costruzione dell'istanza $(G,k)$ deve essere polinomiale: è ciò che rende la riduzione, e non solo l'oracolo, innocua ai fini della complessità.
## La catena di riduzioni
Le riduzioni viste compongono grazie alla transitività in una **catena**:
$$\text{3-SAT} \leq_P \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER} \leq_P \text{SET-COVER}$$
Per la ricetta (si veda sopra) un problema $Y$ è NP-completo se (1) $Y \in$ NP e (2) si riduce da un problema NP-completo. Per tutti i problemi della catena vale (2): 3-SAT è NP-completo e, per transitività, si riduce a ciascuno di essi. Per (1) basta un certificato verificabile in tempo polinomiale: l'insieme di vertici scelto per Independent Set e Vertex Cover (già visto sopra), l'elenco dei sottoinsiemi scelti per Set Cover *(i certificati di Independent Set e Set Cover sono extra, non da slide)*. Perciò, come afferma la slide (Intractability II, p. 28), Independent Set, Vertex Cover e Set Cover sono NP-completi.

> [!info] Mappa delle riduzioni (dal deck)
> Il deck di Kevin Wayne mostra una mappa più ampia dei problemi NP-completi, suddivisa per categoria:
>
> - **Packing/Covering**: 3-SAT → Independent Set → Vertex Cover → Set Cover
> - **Sequencing**: 3-SAT → Directed Ham Cycle → Ham Cycle
> - **Partitioning**: 3-SAT → 3-Coloring
> - **Numerical**: 3-SAT → Subset Sum → Knapsack (si veda [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] per la versione trattabile con DP — ma la versione decisionale su interi arbitrari è NP-completa)
>
> La radice comune è sempre 3-SAT, il problema NP-completo "progenitore" da cui si dipartono tutte le catene.
## Problemi decisionali, di ricerca e di ottimizzazione
I problemi possono essere formulati in tre modi diversi ma equivalenti:

> [!quote] Definizione — Varianti di un problema
> - **Decisionale**: esiste una soluzione con valore $\leq k$ (o $\geq k$)?
> - **Di ricerca**: trova una soluzione con valore $\leq k$.
> - **Di ottimizzazione**: trova la soluzione con valore minimo (o massimo).

> [!quote] Teorema — Equivalenza polinomiale delle varianti
> Le tre varianti di Vertex Cover soddisfano:
> $$\text{VERTEX-COVER (dec)} \equiv_P \text{FIND-VERTEX-COVER (ric)} \equiv_P \text{FIND-MIN-VERTEX-COVER (ott)}$$

**Dimostrazione (VERTEX-COVER $\equiv_P$ FIND-VERTEX-COVER):**
- ($\leq_P$) Il problema decisionale è un caso speciale del problema di ricerca.
- ($\geq_P$) Per trovare un vertex cover di dimensione $\leq k$: si determina con il problema decisionale se ne esiste uno di dimensione $\leq k$; poi si cerca un vertice $v$ tale che $G - \{v\}$ abbia un vertex cover di dimensione $\leq k-1$ (qualsiasi vertice di un vertex cover di dimensione $\leq k$ ha questa proprietà; $G - \{v\}$ elimina $v$ e gli archi incidenti). Si include $v$ nel cover e si cerca ricorsivamente un vertex cover di dimensione $\leq k-1$ in $G - \{v\}$. Ogni passo usa il problema decisionale; in totale si effettuano $O(n)$ chiamate, ciascuna polinomiale. $\square$

**Dimostrazione (FIND-VERTEX-COVER $\equiv_P$ FIND-MIN-VERTEX-COVER):**
- ($\leq_P$) Il problema di ricerca è un caso speciale del problema di ottimizzazione.
- ($\geq_P$) Per trovare un vertex cover di dimensione minima: si cerca la dimensione $k^*$ del vertex cover minimo con una **ricerca binaria** (o lineare) su $k$, poi si risolve il problema di ricerca per $k^*$. Con la ricerca binaria sono $O(\log n)$ chiamate, ciascuna polinomiale. $\square$

> [!question] Domanda tipica d'esame — Perché la NP-completezza si definisce su problemi decisionali
> **D:** Perché ci concentriamo su problemi decisionali per definire NP-completezza, invece che di ottimizzazione?
> **R:**
> **Motivo formale.** La risposta sì/no dei problemi decisionali è facilmente catturata dal modello teorico standard (macchina di Turing non deterministica), su cui sono costruite le definizioni di NP e NP-completezza.
>
> **Motivo di non perdita di generalità.** Le tre varianti — decisionale, di ricerca, di ottimizzazione — sono polinomialmente equivalenti (vedi il teorema sopra per Vertex Cover): un algoritmo polinomiale per una qualsiasi delle tre ne dà uno per le altre due, tramite selezione sequenziale dei vertici o ricerca binaria sul parametro $k$.
>
> **Conclusione.** Scegliere il decisionale semplifica la teoria senza restringere la portata dei risultati: dimostrare NP-completezza per la versione decisionale certifica implicitamente la difficoltà anche delle versioni di ricerca e ottimizzazione.
## Significato pratico per la progettazione
Quando si dimostra che un problema è NP-completo, le opzioni per la progettazione cambiano radicalmente. Si rinuncia a una di tre caratteristiche (Apx I, p. 3): tempo polinomiale, istanze arbitrarie, soluzione ottima.
1. **Algoritmi di approssimazione** (rinuncia alla soluzione ottima): in tempo polinomiale, su istanze arbitrarie, con una soluzione entro un fattore $\alpha$ dall'ottimo (sezione successiva).
2. **Algoritmi parametrizzati** (*FPT*) *(extra, non da slide)*: risolvere esattamente ma in tempo $f(k) \cdot n^{O(1)}$, dove $k$ è un parametro "piccolo" (es. dimensione della soluzione).
3. **Casi speciali trattabili** (rinuncia alle istanze arbitrarie): come in [[04 - Programmazione Dinamica I (Weighted Independent Set)]] (grafi a intervalli) o [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] (Knapsack con $W$ piccolo), trovare restrizioni del problema risolvibili in poly-time.
4. **Euristiche** *(extra, non da slide)*: sacrificare le garanzie formali per soluzioni buone in pratica.

> [!warning] Attenzione alle ipotesi implicite *(extra, non da slide)*
> La NP-completezza presuppone istanze **nel caso peggiore**. Un problema NP-completo può avere istanze pratiche risolvibili velocemente (es. SAT su formule reali è spesso facile per i SAT solver moderni). La difficoltà teorica non esclude la trattabilità pratica su distribuzioni di input ristrette.
## Algoritmi di approssimazione (cenni)
Quando un problema di ottimizzazione è NP-hard, gli **algoritmi di approssimazione** offrono un compromesso: tempo polinomiale, ma con garanzia di qualità sulla soluzione.

Un problema NP-hard di ottimizzazione impone di rinunciare a una di tre caratteristiche: (i) tempo polinomiale, (ii) istanze arbitrarie, (iii) soluzione ottima. Un algoritmo di approssimazione rinuncia alla terza: la **sfida** è dimostrare che il valore della soluzione è vicino all'ottimo senza nemmeno conoscere il valore ottimo.

> [!quote] Definizione — $\alpha$-approssimazione
> Un **algoritmo di $\alpha$-approssimazione** per un problema di ottimizzazione è un algoritmo polinomiale che, per ogni istanza del problema, produce una soluzione il cui valore è entro un fattore $\alpha$ dal valore di una soluzione ottima. $\alpha$ si chiama *rapporto* (o *fattore*) *di approssimazione*.
> - **Minimizzazione:** $\alpha \geq 1$; per ogni istanza $x$ la soluzione restituita ha costo $\leq \alpha \cdot \text{OPT}(x)$.
> - **Massimizzazione:** $\alpha \leq 1$; per ogni istanza $x$ la soluzione restituita ha valore $\geq \alpha \cdot \text{OPT}(x)$.

Nell'introduzione la slide scrive $\rho$-approssimazione (soluzione «entro un rapporto $\rho$ dall'ottimo»), nella definizione formale usa $\alpha$: è lo stesso concetto.
### Load Balancing — 2-approssimazione
**Problema:** date $m$ macchine identiche e $n$ job con tempi $t_j$, assegnare ogni job a una macchina minimizzando il **makespan** $L = \max_i L_i$ (massimo carico tra le macchine), dove $L_i = \sum_{j \in S_i} t_j$.

**Limiti inferiori sull'ottimo:**
- $L^* \geq t_k$ per ogni job $k$ (qualche macchina deve eseguire il job più lungo).
- $L^* \geq \frac{1}{m} \sum_k t_k$ (il lavoro totale va distribuito su $m$ macchine).

> [!quote] Teorema — Load Balancing è NP-hard già con $m = 2$ macchine
> **Dimostrazione:** PARTITION $\leq_P$ LOAD-BALANCE (PARTITION è NP-completo per l'esercizio 8.26 del libro). Data un'istanza di PARTITION, cioè dei numeri da dividere in due gruppi di somma uguale, si crea un job per ogni numero con $t_j$ pari al numero, e si usano $m = 2$ macchine. Esiste uno schedule in cui entrambe le macchine finiscono a $L = \frac{1}{2}\sum_j t_j$ se e solo se i numeri si possono dividere in due gruppi di somma uguale. $\square$ *(La slide riporta solo la figura con le due macchine che terminano a $L$: i passaggi della costruzione sono extra, non da slide.)*
**`List-Scheduling`** — algoritmo greedy: assegna ogni job, nell'ordine dato, alla macchina con carico minimo corrente.

```pseudo
\begin{algorithm}
\caption{List-Scheduling($M[1..m], J[1..n]$)}
\begin{algorithmic}
\For{$i \gets 1$ \To $m$}
  \State $L[i] \gets 0$, $S[i] \gets \emptyset$
\EndFor
\For{$j \gets 1$ \To $n$}
  \State $i^* \gets \arg\min_i L[i]$ \Comment{macchina con carico minimo}
  \State $S[i^*] \gets S[i^*] \cup \{j\}$
  \State $L[i^*] \gets L[i^*] + t_j$
\EndFor
\State \Return $S$
\end{algorithmic}
\end{algorithm}
```

**Implementazione.** Con una coda con priorità per i carichi $L[k]$ il costo è $O(n \log m)$.

> [!quote] Teorema (Graham 1966) — List-Scheduling è una 2-approssimazione
> L'algoritmo List-Scheduling produce un makespan $L \leq 2 \cdot L^*$.
>
> **Dimostrazione:** sia $i^*$ la macchina con carico massimo e $j$ l'**ultimo** job assegnato a $i^*$. Quando $j$ viene assegnato, $i^*$ aveva il carico minimo: $L_{i^*} - t_j \leq L_i$ per ogni $i$. Sommando su tutte le macchine:
> $$L_{i^*} - t_j \leq \frac{1}{m}\sum_{i} L_i = \frac{1}{m}\sum_k t_k \leq L^*$$
> Quindi $L = L_{i^*} = (L_{i^*} - t_j) + t_j \leq L^* + L^* = 2L^*$. $\square$

> [!info] L'analisi è stretta (essenzialmente)
> Esempio: $m$ macchine, i primi $m(m-1)$ job hanno lunghezza 1 e l'ultimo ha lunghezza $m$. List-Scheduling distribuisce i job unitari in parti uguali ($m-1$ per macchina) e poi mette il job lungo su una macchina qualsiasi: makespan $(m-1) + m = 2m-1$ (per $m=10$: 19, con le altre 9 macchine inattive alla fine). L'ottimo mette il job lungo da solo su una macchina e i $m(m-1)$ job unitari sulle altre $m-1$ macchine: $L^* = m$ (per $m=10$: 10). Il rapporto $\frac{2m-1}{m}$ tende a 2.

**`LPT-List-Scheduling`** (*Longest Processing Time*): si ordinano i job in ordine **decrescente** di tempo di processamento e si esegue List-Scheduling.

```pseudo
\begin{algorithm}
\caption{LPT-List-Scheduling($M[1..m], J[1..n]$)}
\begin{algorithmic}
\State ordina i job e rinumerali in modo che $t_1 \geq t_2 \geq \dots \geq t_n$
\For{$i \gets 1$ \To $m$}
  \State $L[i] \gets 0$, $S[i] \gets \emptyset$
\EndFor
\For{$j \gets 1$ \To $n$}
  \State $i^* \gets \arg\min_i L[i]$ \Comment{macchina con carico minimo}
  \State $S[i^*] \gets S[i^*] \cup \{j\}$
  \State $L[i^*] \gets L[i^*] + t_j$
\EndFor
\State \Return $S$
\end{algorithmic}
\end{algorithm}
```

> [!info] Osservazione — bottleneck con un solo job
> Se la macchina bottleneck ha **un solo job**, la soluzione è ottima: qualsiasi soluzione deve schedulare quel job.

> [!quote] Lemma 3
> Se ci sono più di $m$ job, allora $L^* \geq 2\,t_{m+1}$.
>
> **Dimostrazione:** si considerano i primi $m+1$ job, con $t_1 \geq t_2 \geq \dots \geq t_{m+1}$. Ognuno dura almeno $t_{m+1}$. Ci sono $m+1$ job e $m$ macchine, quindi per il principio dei cassetti almeno una macchina ne riceve due: $L^* \geq 2\,t_{m+1}$. $\square$

> [!quote] Teorema — LPT è una $\frac{3}{2}$-approssimazione
> L'algoritmo LPT produce un makespan $L \leq \frac{3}{2} L^*$.
>
> **Dimostrazione** (simile a quella per List-Scheduling): sia $i$ la macchina bottleneck e $j$ l'ultimo job schedulato su $i$. Se $i$ ha un solo job, la soluzione è ottima per l'osservazione. Altrimenti $i$ ha almeno 2 job e quindi $j \geq m+1$ (i primi $m$ job vanno su macchine distinte), da cui $t_j \leq t_{m+1} \leq \frac{1}{2} L^*$ per il Lemma 3. Come nella dimostrazione precedente $L[i] - t_j \leq L^*$, quindi
> $$L = L[i] = (L[i] - t_j) + t_j \leq L^* + \tfrac{1}{2} L^* = \tfrac{3}{2} L^*. \quad \square$$

> [!quote] Teorema (Graham 1969) — LPT è una $\frac{4}{3}$-approssimazione
> L'analisi $\frac{3}{2}$ non è stretta: con un'analisi più sofisticata dello stesso algoritmo si ottiene il fattore $\frac{4}{3}$, che invece è essenzialmente stretto. Esempio: $m$ macchine, $n = 2m+1$ job, due job di lunghezza $m, m+1, \dots, 2m-1$ e un ultimo job di lunghezza $m$; allora $L / L^* = \frac{4m-1}{3m}$.

### Vertex Cover — 2-approssimazione

*(extra, non da slide)* Questa sezione non compare in nessuna slide 2025/26: viene da una traccia d'esame (25/07/2023), per questo resta nella nota.
Un algoritmo greedy elementare fornisce una 2-approssimazione per Vertex Cover (problema di minimizzazione):

```pseudo
\begin{algorithm}
\caption{Approx-Vertex-Cover($G$)}
\begin{algorithmic}
\State $C \gets \emptyset$
\State $E' \gets E$ \Comment{copia degli archi}
\While{$E' \neq \emptyset$}
  \State scegli un arco $(u, v) \in E'$
  \State $C \gets C \cup \{u, v\}$
  \State rimuovi da $E'$ tutti gli archi incidenti a $u$ o $v$
\EndWhile
\State \Return $C$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema — Approx-Vertex-Cover è una 2-approssimazione
> Sia $M$ l'insieme degli archi selezionati al passo 4 (un **matching** massimale). Ogni arco di $M$ richiede almeno un vertice nel vertex cover ottimo, quindi $|M| \leq \text{OPT}$. L'algoritmo aggiunge entrambi gli estremi per ogni arco in $M$: $|C| = 2|M| \leq 2 \cdot \text{OPT}$.

> [!question] Domanda tipica d'esame — V/F: un solo nodo per arco di M?
> **D:** *(Vero o Falso)* «ESERCIZIO N. 2. Si consideri l'algoritmo ALG(G=(V,E)), 2-approssimante per il problema Min-Vertex Cover,  basato sul calcolo di un Maximal Matching M di G(V,E). Si selezioni tutte e sole le affermazioni che si ritengano vere.
> a) L'algoritmo calcola un Maximal Matching M del grafo in input G e poi inserisce, nella soluzione C, un solo nodo per ogni arco di M.» *(chiesto il 25/07/2023)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Lo pseudocodice di Approx-Vertex-Cover inserisce in $C$ **entrambi** gli estremi $u$ e $v$ di ogni arco selezionato di $M$ ($C \gets C \cup \{u,v\}$), non uno solo.
>
> **Controesempio.** Inserire un solo nodo per arco non garantirebbe la copertura: l'estremo escluso potrebbe non comparire in $C$ per nessun'altra ragione, lasciando scoperti gli archi di $G$ incidenti **solo** a lui.
>
> **Osservazione.** È proprio l'inserimento di entrambi gli estremi a produrre il fattore 2: $|C| = 2|M| \leq 2 \cdot \text{OPT}$, dato che $|M| \leq \text{OPT}$.

> [!question] Domanda tipica d'esame — V/F: matching generico vs matching massimale
> **D:** *(Vero o Falso)* «b) La sola proprietà di essere un Matching, da parte del sottoinsieme di archi M generato da ALG, garantisce che la soluzione C prodotta da ALG sia una soluzione ammissibile per G.» *(chiesto il 25/07/2023)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Essere un semplice matching (archi a due a due senza estremi in comune) non basta: se $M$ non fosse **massimale**, potrebbero esistere archi di $G$ non incidenti a nessun vertice di $M$, quindi non coperti da $C$.
>
> **Controesempio.** Un matching qualunque, non massimale, lascia fuori archi "isolati" rispetto a $M$: nessuno dei loro estremi finisce in $C$, che quindi non copre $G$.
>
> **Osservazione.** È la massimalità — nessun arco è aggiungibile a $M$ restando un matching — a garantire che ogni arco di $G$ sia incidente ad almeno un vertice di $M$ (altrimenti sarebbe aggiungibile), e quindi che $C$ copra tutti gli archi. Il ciclo `while` dell'algoritmo, che continua finché $E'$ non è vuoto, è ciò che assicura la massimalità di $M$.

> [!question] Domanda tipica d'esame — V/F: |M| come lower bound dell'ottimo
> **D:** *(Vero o Falso)* «c) Il rapporto di approssimazione 2 è dovuto al fatto che, essendo M un matching di G, la cardinalità |M| è un lower bound alla cardinalità del vertex cover ottimo per G.» *(chiesto il 25/07/2023)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Poiché $M$ è un matching, i suoi archi sono a due a due privi di estremi in comune: per coprire ciascuno di essi il vertex cover ottimo deve contenere almeno un vertice, e vertici usati per archi diversi di $M$ non possono coincidere (gli archi non condividono estremi). Servono dunque almeno $|M|$ vertici distinti nell'ottimo, cioè $|M| \leq \text{OPT}$.
>
> **Osservazione.** Questo è esattamente il lower bound usato nella dimostrazione del fattore 2: combinato con $|C| = 2|M|$ (l'algoritmo inserisce entrambi gli estremi di ogni arco di $M$), dà $|C| \leq 2 \cdot \text{OPT}$.

> [!question] Domanda tipica d'esame — V/F: tempo polinomiale o pseudopolinomiale se M è dato in input?
> **D:** *(Vero o Falso)* «d) L'algoritmo ALG(G) ha tempo polinomiale in |V| se M viene dato in input altrimenti possiamo solo dire che il tempo è pseudopolinomiale in |V|.» *(chiesto il 25/07/2023)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** L'algoritmo è polinomiale in $|V|$ (anzi in $|E|$) **in ogni caso**, sia che $M$ venga dato in input sia che venga calcolato dall'algoritmo stesso: calcolare un Maximal Matching è già un'operazione polinomiale, $O(|E|)$, scorrendo gli archi e aggiungendoli greedily quando non condividono estremi con quelli già scelti.
>
> **Controesempio.** L'affermazione confonde una distinzione che qui non si applica: non c'è alcuna componente pseudopolinomiale in gioco, perché Vertex Cover non ha parametri numerici la cui codifica binaria possa causare una dipendenza dal *valore* (anziché dalla dimensione in bit) dell'input — la firma tipica della pseudopolinomialità.
>
> **Osservazione.** Il contrasto è con Knapsack (si veda [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]), dove il tempo $O(nW)$ dipende dal *valore* $W$, non dai suoi $\log W$ bit: lì sì che ha senso parlare di pseudopolinomialità.

> [!question] Domanda tipica d'esame — V/F: connessione del sottografo indotto G[M]
> **D:** *(Vero o Falso)* «e) Il sottografo G[M] indotto da M è sempre un sottografo connesso di G. Si ricordi che G[M] è il sottografo composto da tutti gli archi di G che hanno entrambi gli estremi in M.» *(chiesto il 25/07/2023)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Essendo $M$ un matching, i suoi archi sono a due a due disgiunti sui vertici: gli archi *di $M$ stessi* formano già $|M|$ componenti separate all'interno di $G[M]$, a meno che non esistano in $G$ altri archi, esterni a $M$, che colleghino vertici di coppie diverse di $M$.
>
> **Controesempio.** Non c'è nessuna garanzia che tali archi aggiuntivi esistano: $G[M]$ può benissimo essere sconnesso, ed è tipicamente così, essendo per costruzione un'unione di $|M|$ componenti indipendenti più eventuali archi accessori.
>
> **Osservazione.** La connessione di $G[M]$ non gioca nessun ruolo nella dimostrazione del fattore 2, che si basa solo su $|M| \leq \text{OPT}$ e $|C| = 2|M|$: la sua eventuale sconnessione è irrilevante per la correttezza dell'algoritmo.

> [!question] Domanda tipica d'esame — 2-approssimazione e NP-completezza non si contraddicono
> **D:** Perché Vertex Cover ammette una 2-approssimazione ma è NP-completo?
> **R:**
> **Cosa garantisce la NP-completezza.** Riguarda la soluzione **esatta**: non è noto (né ritenuto possibile) un algoritmo polinomiale che trovi sempre il vertex cover di cardinalità minima esatta.
>
> **Cosa garantisce l'approssimazione.** Approx-Vertex-Cover rinuncia all'ottimalità: in tempo polinomiale restituisce una soluzione ammissibile di cardinalità al più $2 \cdot \text{OPT}$, non necessariamente $\text{OPT}$.
>
> **Perché non c'è contraddizione.** Le due proprietà riguardano bersagli diversi — "trovare l'ottimo esatto" contro "trovare una soluzione garantita entro un fattore fisso dall'ottimo" — e la NP-completezza esclude solo il primo in tempo polinomiale, non il secondo.

> [!question] Domanda tipica d'esame — Struttura della catena di riduzioni
> **D:** Qual è la struttura della catena di riduzioni 3-SAT → Independent Set → Vertex Cover → Set Cover?
> **R:**
> **Catena.** $\text{3-SAT} \leq_P \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER} \leq_P \text{SET-COVER}$.
>
> **Riduzioni impiegate.** Tre tipi diversi: **codifica con gadget** (3-SAT → Independent Set, tramite i triangoli per clausola), **equivalenza semplice** (Independent Set ↔ Vertex Cover, tramite il complemento $V \setminus S$), **caso speciale → caso generale** (Vertex Cover → Set Cover, ogni $S_v$ è l'insieme degli archi incidenti a $v$).
>
> **Transitività.** Poiché 3-SAT è NP-completo (Cook-Levin) e ogni freccia della catena è una riduzione polinomiale, la transitività di $\leq_P$ garantisce che tutti i problemi a destra siano **NP-hard**; essendo ciascuno anche verificabile in tempo polinomiale (in NP), sono **NP-completi**.
## Riepilogo
| Problema | Classe | Strategia |
|---|---|---|
| Independent Set (grafi a intervalli) | P | DP ([[04 - Programmazione Dinamica I (Weighted Independent Set)]]) |
| Independent Set (grafi generali) | NP-completo | — |
| Vertex Cover | NP-completo ($\equiv_P$ Indep. Set) | 2-approx greedy *(extra, non da slide)* |
| Set Cover | NP-completo (da Vertex Cover) | greedy logaritmico *(extra, non da slide)* |
| 3-SAT | NP-completo (Cook-Levin su SAT) | — |
| Knapsack (W intero) | pseudo-polinomiale | DP ([[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]) |
| Load Balancing | NP-hard (ottimizzazione) | 2-approx (List-Scheduling), $\frac{3}{2}$-approx e $\frac{4}{3}$-approx (LPT) |

> [!info] Collegamento con i flussi *(extra, non da slide)*
> Vertex Cover su grafi **bipartiti** è risolvibile in tempo polinomiale tramite il Teorema di König (equivalente al Max-Flow Min-Cut per reti bipartite, si veda [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] e [[08 - Applicazioni dei Flussi di Rete]]). Questo dimostra che la struttura del grafo può rendere un problema NP-completo trattabile: ciò che è difficile su grafi generali può essere facile su classi ristrette.
