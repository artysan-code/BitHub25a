# Programmazione Dinamica II: Weighted Interval Scheduling, Segmented Least Squares, Knapsack e LIS
La programmazione dinamica consiste nello spezzare un problema in una serie di **sottoproblemi sovrapposti**, risolverli una volta sola e memorizzarne i risultati in una tabella per evitare il ricalcolo. Rispetto al greedy (confronto in [[01 - Greedy e Interval Scheduling]]) non impone scelte irrevocabili: esplora tutte le alternative possibili con costo polinomiale sfruttando la **sottostruttura ottima**. Questa nota copre quattro problemi classici — Weighted Interval Scheduling, Segmented Least Squares, Knapsack 0/1 e Longest Increasing Subsequence — più l'esercizio House Coloring. Per i fondamenti della tecnica si rimanda a [[04 - Programmazione Dinamica I (Weighted Independent Set)]].
## Schema generale della programmazione dinamica
> [!info] Schema DP in quattro passi
> 1. **Sottoproblemi**: identificare $O(\text{poly}(n))$ sottoproblemi distinti.
> 2. **Equazione di Bellman**: esprimere la soluzione di un sottoproblema come funzione delle soluzioni di sottoproblemi più piccoli.
> 3. **Calcolo bottom-up** (o memoization top-down): risolvere i sottoproblemi in ordine topologico, memorizzando i valori in una tabella.
> 4. **Ricostruzione**: risalire la tabella per ricavare la soluzione ottima (non solo il suo valore).
## Weighted Interval Scheduling
### Il problema
**Input**: $n$ job; il job $j$ inizia in $s_j$, termina in $f_j$ e ha **peso** $w_j > 0$.
Due job sono **compatibili** se non si sovrappongono. L'obiettivo è trovare il sottoinsieme di peso totale massimo di job mutualmente compatibili.
> [!info] Confronto con la versione unweighted
> La versione con pesi unitari ($w_j = 1$ per ogni $j$) si risolve in modo ottimo con l'algoritmo greedy *earliest-finish-time first* (vedi [[01 - Greedy e Interval Scheduling]]). Con pesi arbitrari il greedy può fallire drasticamente: un singolo job di peso $999$ viene ignorato a favore di due job di peso $1$ ciascuno.
### Struttura della soluzione ottima
**Convenzione**: i job sono ordinati in ordine crescente di finish time, $f_1 \le f_2 \le \cdots \le f_n$.
> [!quote] Definizione — Predecessore $p(j)$
> $p(j)$ è il più grande indice $i < j$ tale che il job $i$ è **compatibile** con il job $j$ (cioè $f_i \le s_j$). Se nessun job è compatibile con $j$, allora $p(j) = 0$.

**Esempi**: se i job sono disposti come nelle slide, $p(8) = 1$, $p(7) = 3$, $p(2) = 0$.
> [!quote] Definizione — $\text{OPT}(j)$
> $\text{OPT}(j)$ è il peso massimo di qualunque sottoinsieme di job mutualmente compatibili scelto tra i job $1, 2, \ldots, j$.

**Caso 1 — job $j$ non selezionato**: la soluzione coincide con $\text{OPT}(j-1)$.
**Caso 2 — job $j$ selezionato**: si raccoglie $w_j$, si escludono i job incompatibili $\{p(j)+1, \ldots, j-1\}$, e si considera la soluzione ottima sui job compatibili rimasti $1, \ldots, p(j)$.
> [!quote] Equazione di Bellman — Weighted Interval Scheduling
> $$\text{OPT}(j) = \begin{cases} 0 & j = 0 \\ \max\bigl\{\text{OPT}(j-1),\; w_j + \text{OPT}(p(j))\bigr\} & j \ge 1 \end{cases}$$

La correttezza si dimostra tramite **argomento di scambio** (exchange argument): qualunque soluzione ottima deve cadere in uno dei due casi; la proprietà di sottostruttura ottima garantisce che il sottoproblema residuo sia a sua volta ottimo.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Bottom-Up($n, s, f, w$)}
\begin{algorithmic}
\State ordina i job per finish time: $f[1] \leq f[2] \leq \cdots \leq f[n]$
\State calcola $p[j]$ per ogni $j$ (ricerca binaria su $f[1..j-1]$)
\State $M[0] \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $M[j] \gets \max(M[j-1],\; w[j] + M[p[j]])$
\EndFor
\State \Return $M[n]$
\end{algorithmic}
\end{algorithm}
```
### Algoritmo con memoization (top-down)
Il calcolo ricorsivo senza memoization ha $T(n) = T(n-1) + T(n-2) + O(1)$, che cresce come la sequenza di Fibonacci: **esponenziale**. La memoization elimina i ricalcoli.

```pseudo
\begin{algorithm}
\caption{Top-Down($n, s, f, w$)}
\begin{algorithmic}
\State ordina i job per finish time
\State calcola $p[j]$ per ogni $j$
\State $M[0] \gets 0$
\State \Return \Call{M-Compute-Opt}{$n$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{M-Compute-Opt($j$)}
\begin{algorithmic}
\If{$M[j]$ è non inizializzato}
  \State $M[j] \gets \max\bigl(\text{M-Compute-Opt}(j-1),\; w[j] + \text{M-Compute-Opt}(p[j])\bigr)$
\EndIf
\State \Return $M[j]$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Lemma — Complessità della memoization
> L'algoritmo con memoization esegue **al più $2n$ chiamate ricorsive** e ha complessità $O(n \log n)$.

**Dimostrazione.** Definiamo $\Phi$ = numero di celle $M[1..n]$ già inizializzate. Inizialmente $\Phi = 0$ e $\Phi \le n$ per tutto il calcolo. Ogni chiamata ricorsiva che inizializza una nuova cella aumenta $\Phi$ di 1 ed effettua al più 2 chiamate figlie. Le chiamate che trovano la cella già inizializzata costano $O(1)$ senza generare ulteriori chiamate. Quindi le chiamate totali sono $\le 2n$, con costo $O(n)$ ciascuna a costo $O(1)$. Il bottleneck è l'ordinamento e il calcolo di $p[j]$, entrambi $O(n \log n)$. $\square$
### Ricostruzione della soluzione
```pseudo
\begin{algorithm}
\caption{Find-Solution($j$)}
\begin{algorithmic}
\If{$j = 0$}
  \State \Return $\emptyset$
\ElsIf{$w[j] + M[p[j]] > M[j-1]$}
  \State \Return $\{j\} \cup \text{Find-Solution}(p[j])$
\Else
  \State \Return \Call{Find-Solution}{$j-1$}
\EndIf
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(n)$ — al più $n$ chiamate ricorsive.
### Complessità
| Fase | Complessità |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Calcolo $p[j]$ per ogni $j$ (ricerca binaria) | $O(n \log n)$ |
| Riempimento tabella (bottom-up) | $O(n)$ |
| Ricostruzione | $O(n)$ |
| **Totale** | $O(n \log n)$ |

> [!info] Bottom-up vs memoization
> | Aspetto | Top-down (memoization) | Bottom-up (tabulazione) |
> |---|---|---|
> | Calcola solo i sottoproblemi necessari | Sì | No (tutti) |
> | Overhead chiamate ricorsive | Sì | No |
> | Analisi complessità | Più delicata | Immediata |
> | Codice | Più intuitivo | Più compatto e cache-efficiente |

> [!question] Domanda tipica d'esame — Perché il greedy fallisce
> **D:** Perché l'algoritmo greedy *earliest-finish-time first* non funziona per il Weighted Interval Scheduling? Come si risolve correttamente?
> **R:** Il greedy seleziona il job che finisce prima, indipendentemente dal peso. Basta un controesempio: un job di peso $999$ che copre l'intervallo $[0, 11]$ viene ignorato se esistono due job di peso $1$ che coprono $[0, 5]$ e $[6, 11]$. Il greedy sceglie questi due e ottiene peso $2$, perdendo il job da $999$. La soluzione corretta usa la DP con l'equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$, che esplora entrambe le scelte e garantisce l'ottimo in $O(n \log n)$.

> [!question] Domanda tipica d'esame — Riduzione a WIS
> **D:** *(Vero o Falso)* «Trasformando opportunamente l'istanza I, è possibile darla in input all'algoritmo di Programmazione Dinamica per il Weighted Interval Scheduling ed ottenere la soluzione ottima per I.» *(chiesto il 12/09/2023)*
> **R:** Vero. La tecnica è la **riduzione**: si trasforma l'istanza I in un'istanza equivalente di WIS (job con intervalli $[s_j, f_j]$ e pesi $w_j$) tale che la soluzione ottima calcolata dall'algoritmo PD di WIS su questa istanza trasformata corrisponda esattamente alla soluzione ottima di I. L'esempio canonico è l'Interval Scheduling **non pesato** (vedi il confronto a inizio sezione): ponendo $w_j = 1$ per ogni job, l'equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ diventa $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, 1 + \text{OPT}(p(j))\}$, che calcola la cardinalità massima di un sottoinsieme di job compatibili — esattamente l'ottimo del problema non pesato. In generale, per mostrare che un problema P si risolve con l'algoritmo PD di WIS basta esibire una trasformazione polinomiale dell'istanza di P in un'istanza di intervalli pesati che preservi il valore ottimo.
## Segmented Least Squares
### Il problema
**Least Squares**: dati $n$ punti $(x_1, y_1), \ldots, (x_n, y_n)$ nel piano, trovare la retta $y = ax + b$ che minimizza la **somma degli scarti quadratici** (SSE):
$$\text{SSE} = \sum_{i=1}^{n} (y_i - ax_i - b)^2$$
La soluzione in forma chiusa si ricava dal calcolo, con complessità $O(n)$ per fissato insieme di punti.
**Segmented Least Squares**: i punti **non** sono approssimabili bene da un'unica retta, ma da una **sequenza di segmenti lineari**. Si vuole minimizzare:
$$f = E + c \cdot L$$
dove $E$ è la somma degli SSE di ciascun segmento, $L$ è il numero di rette usate, e $c > 0$ è una costante di penalità per la parsimonia.
> [!info] Bilanciamento accuratezza/parsimonia
> Il termine $c \cdot L$ penalizza le soluzioni con troppi segmenti. Con $c \to 0$ si usano $n$ segmenti con SSE $= 0$; con $c \to \infty$ si usa un unico segmento. Il valore di $c$ è scelto dall'utente in base al contesto.
### Struttura della soluzione ottima
**Notazione**: i punti sono ordinati per $x$, con $x_1 < x_2 < \cdots < x_n$. Indichiamo con $e_{ij}$ il SSE del migliore segmento che approssima i punti $p_i, p_{i+1}, \ldots, p_j$.
> [!quote] Definizione — $\text{OPT}(j)$
> $\text{OPT}(j)$ è il costo minimo per approssimare i punti $p_1, p_2, \ldots, p_j$ con una sequenza ottima di segmenti.

**Osservazione chiave**: l'**ultimo segmento** della soluzione ottima per i punti $1, \ldots, j$ copre necessariamente i punti $p_i, \ldots, p_j$ per qualche $1 \le i \le j$. Il suo costo è $e_{ij} + c$ (SSE più penalità per la retta). I punti $p_1, \ldots, p_{i-1}$ devono essere approssimati in modo ottimo con $\text{OPT}(i-1)$.
> [!quote] Equazione di Bellman — Segmented Least Squares
> $$\text{OPT}(j) = \begin{cases} 0 & j = 0 \\ \displaystyle\min_{1 \le i \le j}\bigl\{e_{ij} + c + \text{OPT}(i-1)\bigr\} & j \ge 1 \end{cases}$$

La **scelta multipla** (multiway choice) distingue questo problema da Weighted Interval Scheduling, dove la scelta era binaria.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Segmented-Least-Squares($n, p_1, \ldots, p_n, c$)}
\begin{algorithmic}
\For{$j \gets 1$ \To $n$}
  \For{$i \gets 1$ \To $j$}
    \State calcola $e[i][j]$ = SSE per i punti $p_i, \ldots, p_j$
  \EndFor
\EndFor
\State $M[0] \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $M[j] \gets \min_{1 \leq i \leq j} \{ e[i][j] + c + M[i-1] \}$
\EndFor
\State \Return $M[n]$
\end{algorithmic}
\end{algorithm}
```
> [!warning] Pre-calcolo degli SSE con somme cumulative
> Il calcolo naïf di tutti gli $e_{ij}$ richiede $O(n)$ per coppia $\Rightarrow O(n^3)$ in totale. Si può pre-calcolare le **somme cumulative** $\Sigma x$, $\Sigma y$, $\Sigma x^2$, $\Sigma xy$ in $O(n)$, e poi ogni $e_{ij}$ si ottiene in $O(1)$, riducendo il totale a $O(n^2)$.
### Ricostruzione della soluzione
La ricostruzione risale la tabella $M$: partendo da $j = n$, si trova l'indice $i^*$ che minimizza $\{e_{ij} + c + M[i-1]\}$, si emette il segmento $[i^*, j]$, e si ricorre su $j \leftarrow i^* - 1$ fino a $j = 0$.
### Complessità
| Fase | Complessità |
|---|---|
| Pre-calcolo $e_{ij}$ (naïf) | $O(n^3)$ |
| Pre-calcolo $e_{ij}$ (somme cumulative) | $O(n^2)$ |
| Riempimento tabella $M$ | $O(n^2)$ |
| Spazio (tabella $e_{ij}$) | $O(n^2)$ |
| **Totale (versione ottimizzata)** | $O(n^2)$ tempo, $O(n^2)$ spazio |

> [!quote] Teorema — Complessità Segmented Least Squares (Bellman 1961)
> L'algoritmo DP risolve il problema Segmented Least Squares in $O(n^3)$ tempo e $O(n^2)$ spazio (versione base), o in $O(n^2)$ tempo con pre-calcolo delle somme cumulative.

> [!question] Domanda tipica d'esame — Scelta binaria vs multipla
> **D:** Qual è la differenza strutturale tra l'equazione di Bellman per il Weighted Interval Scheduling e quella per il Segmented Least Squares?
> **R:** Nel WIS la scelta è **binaria**: includere o escludere il job $j$, con un'unica alternativa per ciascuno dei due casi. Nel SLS la scelta è **multipla** (multiway): l'ultimo segmento può coprire qualunque prefisso finale $[i, j]$ con $1 \le i \le j$, quindi si minimizza su $j$ alternative. Entrambe sfruttano la sottostruttura ottima, ma SLS richiede un ciclo interno aggiuntivo che porta la complessità a $O(n^2)$ invece di $O(n)$.
## Knapsack 0/1
### Il problema
**Input**: $n$ oggetti; l'oggetto $i$ ha **valore** $v_i > 0$ e **peso** $w_i > 0$ (interi). Uno zaino ha capacità $W$ (intero). **Obiettivo**: selezionare un sottoinsieme di oggetti di valore totale massimo senza superare il peso $W$.
**Assunzione**: i **pesi** $w_i$ e la capacità $W$ sono **interi positivi** — vincolo necessario per indicizzare la tabella DP. I valori $v_i$ sono anch'essi interi nell'istanza standard, ma come chiarito nella sezione sulla complessità, l'algoritmo rimane corretto anche con valori reali.
> [!warning] False start: un'unica variabile non basta
> La definizione $\text{OPT}(i)$ = valore ottimo usando i primi $i$ oggetti non è sufficiente. Quando si decide se includere l'oggetto $i$, non si sa la capacità residua disponibile: senza questa informazione non si può costruire la ricorrenza. **Serve una seconda variabile**.
### Struttura della soluzione ottima
> [!quote] Definizione — $\text{OPT}(i, w)$
> $\text{OPT}(i, w)$ è il valore massimo selezionabile dai primi $i$ oggetti con capacità residua $w$.

**Caso 1 — oggetto $i$ non selezionato** (o $w_i > w$): $\text{OPT}(i, w) = \text{OPT}(i-1, w)$.
**Caso 2 — oggetto $i$ selezionato**: si raccoglie $v_i$, la capacità scende a $w - w_i$, e si risolve ottimamente il sottoproblema sui primi $i-1$ oggetti con capacità $w - w_i$.
> [!quote] Equazione di Bellman — Knapsack 0/1
> $$\text{OPT}(i, w) = \begin{cases} 0 & i = 0 \\ \text{OPT}(i-1, w) & w_i > w \\ \max\bigl\{\text{OPT}(i-1, w),\; v_i + \text{OPT}(i-1, w - w_i)\bigr\} & w_i \le w \end{cases}$$

> [!question] Domanda tipica d'esame — Significato di OPT(j-1, w-wj)
> **D:** «B) Prefissato un qualsiasi ordinamento degli items {Ij : j= 1,...,n}, la funzione OPT(j-1,w-wj) calcolata da PD è uguale al valore ottimo relativo alla sottoistanza \<I1,...,Ij-1; w- wj \> ? Se SI, in che modo viene utilizzato questo valore nell'algoritmo PD? Se NO, quale/i valore/i della funzione OPT(j,w) vengono utilizzati da PD al generico passo ricorsivo?» *(chiesto il 14/09/2022)*
> **R:** Sì: per definizione $\text{OPT}(j,w)$ restituisce sempre il valore ottimo della sottoistanza formata dai primi $j$ item con capacità $w$ (vedi la definizione data in questa sezione), quindi $\text{OPT}(j-1, w-w_j)$ è per definizione il valore ottimo della sottoistanza $\langle I_1,\ldots,I_{j-1}; w-w_j \rangle$. Questo valore viene usato nel passo ricorsivo dell'equazione di Bellman $\text{OPT}(j,w) = \max\{\text{OPT}(j-1,w),\, v_j + \text{OPT}(j-1, w-w_j)\}$ (per $w_j \le w$; altrimenti $\text{OPT}(j,w) = \text{OPT}(j-1,w)$): corrisponde al **Caso 2** descritto sopra, cioè al ramo in cui l'item $I_j$ viene incluso nella soluzione ottima, per cui si somma $v_j$ al valore ottimo ottenibile dai primi $j-1$ item con la capacità residua $w-w_j$.

> [!question] Domanda tipica d'esame — Cosa rappresenta M(j,w)
> **D:** «C) Nella versione iterativa dell'algoritmo PD, l'entrata della matrice M(j,w) contiene la soluzione ottima formata da un qualsiasi sottoinsieme S di {I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) } tale che: |S| <= j e Σ_(k∉S) vk = w ?» *(chiesto il 14/09/2022)*
> **R:** No: l'affermazione è imprecisa su due punti. (1) $M(j,w)$ è definita sui **primi $j$ item** $\{I_1,\ldots,I_j\}$, non su un sottoinsieme $S$ qualunque estratto da **tutta** la lista $\{I_1,\ldots,I_n\}$ con $|S|\le j$: un sottoinsieme di $j$ item presi da posizioni arbitrarie (es. $\{I_2, I_7\}$ con $j=5$) non è ammissibile per $M(j,w)$, che considera solo $S \subseteq \{I_1,\ldots,I_j\}$. (2) Il vincolo sulla capacità è formulato in modo errato: deve valere $\sum_{k \in S} w_k \le w$ (il **peso totale degli item selezionati** non supera la capacità residua $w$), non $\sum_{k \notin S} v_k = w$ (somma dei *valori* degli item *esclusi*, priva di significato per il problema). La definizione corretta, coerente con quella data in questa nota, è $M(j,w) = \max\{\sum_{k\in S} v_k : S \subseteq \{I_1,\ldots,I_j\},\; \sum_{k \in S} w_k \le w\}$.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Knapsack($n, W, w_1, \ldots, w_n, v_1, \ldots, v_n$)}
\begin{algorithmic}
\For{$w \gets 0$ \To $W$}
  \State $M[0][w] \gets 0$
\EndFor
\For{$i \gets 1$ \To $n$}
  \For{$w \gets 0$ \To $W$}
    \If{$w_i > w$}
      \State $M[i][w] \gets M[i-1][w]$
    \Else
      \State $M[i][w] \gets \max(M[i-1][w],\; v_i + M[i-1][w - w_i])$
    \EndIf
  \EndFor
\EndFor
\State \Return $M[n][W]$
\end{algorithmic}
\end{algorithm}
```
### Tabella di esempio
Con gli oggetti $\{(v_1=1,w_1=1),\,(v_2=6,w_2=2),\,(v_3=18,w_3=5),\,(v_4=22,w_4=6),\,(v_5=28,w_5=7)\}$ e $W = 11$:

```
        w:   0   1   2   3   4   5   6   7   8   9  10  11
  {}         0   0   0   0   0   0   0   0   0   0   0   0
  {1}        0   1   1   1   1   1   1   1   1   1   1   1
  {1,2}      0   1   6   7   7   7   7   7   7   7   7   7
  {1,2,3}    0   1   6   7   7  18  19  24  25  25  25  25
  {1,2,3,4}  0   1   6   7   7  18  22  24  28  29  29  40
  {1,..5}    0   1   6   7   7  18  22  28  29  34  35  40
```

La soluzione ottima è $\text{OPT}(5, 11) = 40$ (sottoinsieme $\{3, 4\}$, peso $5+6=11$, valore $18+22=40$).
### Ricostruzione della soluzione
Si risale la tabella dall'angolo in basso a destra: l'oggetto $i$ **è incluso** nella soluzione ottima per $(i, w)$ se e solo se $M[i][w] > M[i-1][w]$ (cioè la selezione ha effettivamente aumentato il valore). In caso affermativo si ricorre su $(i-1, w - w_i)$, altrimenti su $(i-1, w)$.
### Complessità e pseudo-polinomialità
> [!quote] Teorema — Complessità Knapsack
> L'algoritmo DP risolve Knapsack 0/1 in $\Theta(nW)$ tempo e $\Theta(nW)$ spazio.

**Perché la complessità è pseudo-polinomiale?**

> [!warning] Knapsack è pseudo-polinomiale, non polinomiale
> $\Theta(nW)$ **non è** polinomiale nella **dimensione dell'input**. La dimensione dell'input è $O(n \log W + n \log v_{\max})$ bit (si codificano i numeri in binario). Il valore $W$ può essere esponenziale nel numero di bit che lo rappresentano: se $W = 2^k$, allora $k = \log_2 W$ bit bastano per rappresentarlo, ma l'algoritmo esegue $\Theta(n \cdot 2^k)$ operazioni — esponenziale in $k$.
>
> Un **algoritmo pseudo-polinomiale** ha complessità polinomiale nei *valori* (non nella *dimensione in bit*) dell'input. È efficiente quando $W$ è ragionevolmente piccolo, ma non garantisce costi polinomiali in generale.
>
> **Nota**: l'integrità dei pesi è essenziale. Con pesi reali arbitrari la tabella non è indicizzabile e l'approccio DP non funziona direttamente. L'integrità dei valori invece **non** è necessaria per la correttezza.

> [!question] Domanda tipica d'esame — Perché due variabili
> **D:** Perché per il Knapsack 0/1 è necessario definire il sottoproblema con due variabili $\text{OPT}(i, w)$ invece di una sola $\text{OPT}(i)$?
> **R:** Con una sola variabile $\text{OPT}(i)$ si fissa il prefisso di oggetti ma non si controlla la capacità residua. Quando si considera se aggiungere l'oggetto $i$, non si sa quanta capacità è ancora disponibile: senza questa informazione non è possibile scrivere una ricorrenza corretta. La variabile $w$ rappresenta la **capacità residua** e permette di esprimere la scelta in modo preciso: se $w_i > w$ l'oggetto non entra, altrimenti si massimizza tra escluderlo (costo $\text{OPT}(i-1,w)$) e includerlo (costo $v_i + \text{OPT}(i-1, w-w_i)$).

> [!question] Domanda tipica d'esame — Pseudo-polinomialità
> **D:** L'algoritmo DP per il Knapsack è polinomiale?
> **R:** No. La complessità è $\Theta(nW)$, che è **pseudo-polinomiale**: è polinomiale nei *valori* dell'input, ma non nella sua *dimensione in bit*. Se $W$ è rappresentato con $k$ bit allora $W = O(2^k)$, e l'algoritmo esegue $\Theta(n \cdot 2^k)$ operazioni — esponenziale in $k$. In effetti, Knapsack è un problema **NP-hard** (vedi [[09 - NP-Completezza e Riduzioni]]) e non si conosce un algoritmo polinomiale nella dimensione dell'input.

> [!question] Domanda tipica d'esame — K è in P?
> **D:** «ESERCIZIO 1. Si consideri il problema Knapsack (K) e si consideri l'algoritmo ottimale PD per K basato sulla Programmazione Dinamica. Si consideri una generica istanza X = \<I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) ; W\> di K, dove M = max{wj, vj, W : j=1,...,n}. Si risponda alle seguenti domande con al massimo quattro righe negli spazi appropriati, dando delle brevi spiegazioni. A) L'esistenza di un qualsiasi algoritmo che impiega tempo Θ(n^2 log^24(M)) mostrerebbe che il problema K è nella classe P?» *(chiesto il 14/09/2022)*
> **R:** Sì: $\Theta(n^2 \log^{24} M)$ è polinomiale nella **dimensione dell'input**, che è $O(n \log M)$ bit (ogni peso, valore e la capacità sono codificati in binario, quindi ciascuno occupa $O(\log M)$ bit). Un tempo $\Theta(n^2 \log^{24} M)$ è quindi polinomiale in $n$ e in $\log M$, cioè nella lunghezza della codifica dell'istanza: un tale algoritmo classificherebbe K in P. Questo contrasta con l'algoritmo PD standard di questa nota, che ha complessità $\Theta(nW)$: quest'ultima è polinomiale nel *valore* $W$ (quindi in $M$), non nella sua *dimensione in bit* $\log W$ — è **pseudo-polinomiale**, non polinomiale (vedi il riquadro sulla pseudo-polinomialità qui sopra). La distinzione è esattamente quella tra $\text{poly}(M)$ e $\text{poly}(\log M)$.
## Longest Increasing Subsequence (LIS)
### Il problema
**Input**: una sequenza $S[1], S[2], \ldots, S[n]$ di $n$ numeri reali. **Obiettivo**: trovare la **sottosequenza crescente più lunga** (LIS), cioè una sequenza di indici $i_1 < i_2 < \cdots < i_k$ tale che $S[i_1] < S[i_2] < \cdots < S[i_k]$, con $k$ massimo.
> [!example] Esempio motivante (dalle slide)
> Sequenza: $S = [4, 1, 8, 3, 4, 8, 2, 7, 5, 6, 9, 8]$
>
> La lunghezza della LIS ottima è $6$. Un esempio di LIS di lunghezza 6: $1, 3, 4, 5, 6, 9$ (indici $2, 4, 5, 9, 10, 11$).
### Primo tentativo fallito
Se si definisce $\text{OPT}[i]$ = lunghezza della LIS di $S[1], \ldots, S[i]$, non si riesce a scrivere una ricorrenza semplice: non si sa con quale valore termina la LIS di $S[1..i]$, e quindi non si può decidere se $S[i+1]$ può essere aggiunto.
> [!info] Tecnica: aggiungere un vincolo al sottoproblema
> Una soluzione classica consiste nel **restringere** la definizione del sottoproblema, aggiungendo il vincolo che la sottosequenza **termini obbligatoriamente con $S[i]$**. Questo abilita la ricorrenza.
### Struttura della soluzione ottima
> [!quote] Definizione — $\text{OPT}[i]$
> $\text{OPT}[i]$ è la lunghezza della sottosequenza crescente più lunga di $S[1], \ldots, S[i]$ **che termina con $S[i]$**.

**Soluzione**: $\max_{i = 1, \ldots, n} \text{OPT}[i]$ (il massimo su tutti i possibili ultimi elementi).
> [!quote] Equazione di Bellman — LIS
> $$\text{OPT}[i] = 1 + \max\Bigl(0,\; \max_{\substack{j = 1, \ldots, i-1 \\ S[j] < S[i]}} \text{OPT}[j]\Bigr)$$

**Lettura**: la LIS che termina in $S[i]$ è l'estensione della migliore LIS che termina in qualche $S[j] < S[i]$ con $j < i$. Se non esiste tale $j$, la LIS è di lunghezza $1$ (solo $S[i]$).
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{LIS($S[1..n]$)}
\begin{algorithmic}
\State $\text{OPT}[1] \gets 1$
\For{$i \gets 2$ \To $n$}
  \State $\text{OPT}[i] \gets 1 + \max\!\Bigl(0,\; \max_{\substack{j=1,\ldots,i-1 \\ S[j] < S[i]}} \text{OPT}[j]\Bigr)$
\EndFor
\State \Return $\max_{i=1,\ldots,n} \text{OPT}[i]$
\end{algorithmic}
\end{algorithm}
```
### Esempio di calcolo
Sequenza: $S = [4, 1, 8, 3, 4, 8, 2, 7, 5, 6, 9, 8]$, indici da $1$ a $12$.

```
i    :  1   2   3   4   5   6   7   8   9  10  11  12
S[i] :  4   1   8   3   4   8   2   7   5   6   9   8
OPT  :  1   1   2   2   3   4   2   4   4   5   6   5
```

La LIS ha lunghezza $\max = 6$ (ottenuta in $i = 11$, elemento $9$). Una LIS ottima è $1, 3, 4, 5, 6, 9$ (indici $2, 4, 5, 9, 10, 11$).
### Ricostruzione della soluzione
Per ricostruire la LIS, si mantiene un array `prev[i]` che memorizza l'indice $j$ usato nella ricorrenza per $\text{OPT}[i]$ (il predecessore nella LIS che finisce in $i$). A partire dall'indice $i^*$ con $\text{OPT}[i^*]$ massimo, si risale la catena dei predecessori.
### Complessità
| Fase | Complessità |
|---|---|
| Calcolo $\text{OPT}[i]$ per ogni $i$ (ciclo interno $O(i)$) | $O(n^2)$ |
| Ricerca del massimo | $O(n)$ |
| **Totale** | $O(n^2)$ |

**Spazio**: $O(n)$ per l'array $\text{OPT}$ (e $O(n)$ per `prev` in caso di ricostruzione).

> [!info] Esiste un algoritmo $O(n \log n)$ per LIS
> Con una struttura dati ausiliaria (patience sorting o albero di ricerca) è possibile risolvere LIS in $O(n \log n)$, ma l'approccio DP $O(n^2)$ è quello trattato in questo corso.

> [!question] Domanda tipica d'esame — Vincolo sull'ultimo elemento
> **D:** Perché per LIS è necessario aggiungere il vincolo che la sottosequenza termini con $S[i]$? Come cambia la ricorrenza?
> **R:** Senza il vincolo, $\text{OPT}[i]$ = lunghezza della LIS di $S[1..i]$ non ammette una ricorrenza semplice: non si sa quale sia l'ultimo elemento scelto, e quindi non si può decidere se $S[i+1]$ può prolungare la sottosequenza. Con il vincolo che la LIS **termini in $S[i]$**, la ricorrenza diventa precisa: $\text{OPT}[i] = 1 + \max(0, \max_{j<i, S[j]<S[i]} \text{OPT}[j])$. La soluzione globale si ottiene poi come $\max_i \text{OPT}[i]$.
## House Coloring (esercizio)
### Il problema
**Input**: $n$ case in fila, ognuna va dipinta di rosso (R), verde (G) o blu (B). Il costo di dipingere la casa $i$ del colore $c$ è $\text{cost}(i, c)$. **Vincolo**: nessuna casa adiacente ha lo stesso colore. **Obiettivo**: minimizzare il costo totale.
### Struttura della soluzione ottima
> [!quote] Definizione — $R[i]$, $G[i]$, $B[i]$
> - $R[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **rossa**.
> - $G[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **verde**.
> - $B[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **blu**.

La soluzione ottima è $\min\{R[n], G[n], B[n]\}$.
> [!quote] Equazione di Bellman — House Coloring
> $$R[i] = \text{cost}(i, \text{rosso}) + \min\{G[i-1],\, B[i-1]\}$$
> $$G[i] = \text{cost}(i, \text{verde}) + \min\{R[i-1],\, B[i-1]\}$$
> $$B[i] = \text{cost}(i, \text{blu}) + \min\{R[i-1],\, G[i-1]\}$$
> Casi base: $R[1] = \text{cost}(1, R)$, $G[1] = \text{cost}(1, G)$, $B[1] = \text{cost}(1, B)$.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{House-Coloring($n, \text{cost}$)}
\begin{algorithmic}
\State $R[1] \gets \text{cost}(1, R)$
\State $G[1] \gets \text{cost}(1, G)$
\State $B[1] \gets \text{cost}(1, B)$
\For{$i \gets 2$ \To $n$}
  \State $R[i] \gets \text{cost}(i, R) + \min(G[i-1],\; B[i-1])$
  \State $G[i] \gets \text{cost}(i, G) + \min(R[i-1],\; B[i-1])$
  \State $B[i] \gets \text{cost}(i, B) + \min(R[i-1],\; G[i-1])$
\EndFor
\State \Return $\min(R[n],\; G[n],\; B[n])$
\end{algorithmic}
\end{algorithm}
```

**Complessità**: $O(n)$ — un'unica passata con $O(1)$ lavoro per ogni casa.

> [!info] Generalizzazione a $k$ colori
> Con $k$ colori la stessa struttura si generalizza a $k$ array, con equazione $C_i[c] = \text{cost}(i, c) + \min_{c' \ne c} C_{i-1}[c']$. Pre-calcolando i due minimi globali della riga precedente in $O(k)$, ogni cella costa $O(1)$ e la complessità è $\Theta(nk)$ — che è già ottima, perché i costi in input sono $nk$ e vanno comunque letti tutti.

> [!question] Domanda tipica d'esame — Generalizzazione a k colori
> **D:** Qual è la complessità dell'algoritmo DP per House Coloring con 3 colori? Come si generalizza a $k$ colori?
> **R:** Con 3 colori la complessità è $O(n)$: si scorrono le $n$ case, e per ogni casa si calcolano 3 valori in tempo $O(1)$. Con $k$ colori si mantengono $k$ array e per ogni casa serve il minimo tra i $k-1$ colori alternativi: calcolarlo da zero per ogni cella costerebbe $O(k)$, per un totale di $O(nk^2)$. Pre-calcolando invece i **due** minimi più piccoli della riga precedente in $O(k)$ — il secondo serve per il caso in cui il minimo cada proprio sul colore $c$ escluso — ogni cella scende a $O(1)$, quindi $O(k)$ per riga e $\Theta(nk)$ in totale. Questo $\Theta(nk)$ **non è migliorabile**: l'input contiene $nk$ costi e un algoritmo corretto deve leggerli tutti (cambiare un solo $\text{cost}(i,c)$ può cambiare l'ottimo), quindi $\Omega(nk)$ è un lower bound.
## Riepilogo dei problemi trattati
| Problema | Sottoproblemi | Scelta | Equazione di Bellman | Complessità |
|---|---|---|---|---|
| Weighted Interval Scheduling | $O(n)$ | Binaria (includo/escludo job $j$) | $\max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ | $O(n \log n)$ |
| Segmented Least Squares | $O(n)$ | Multipla (quale ultimo segmento) | $\min_{i \le j}\{e_{ij} + c + \text{OPT}(i-1)\}$ | $O(n^2)$ |
| Knapsack 0/1 | $O(nW)$ | Binaria (includo/escludo oggetto $i$) | $\max\{\text{OPT}(i-1,w),\, v_i + \text{OPT}(i-1,w-w_i)\}$ | $\Theta(nW)$ pseudo-pol. |
| LIS | $O(n)$ | Multipla (quale predecessore $j$) | $1 + \max_{j<i,\,S[j]<S[i]} \text{OPT}[j]$ | $O(n^2)$ |
| House Coloring | $O(n)$ | Multipla (3 colori) | $\text{cost}(i,c) + \min_{c' \ne c} C[i-1][c']$ | $O(n)$ |

Per i problemi di sequenza alignment e Bellman-Ford, che usano la stessa tecnica DP con una seconda variabile, si veda [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].
