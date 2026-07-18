# Programmazione Dinamica III: Sequence Alignment e Bellman-Ford
Questa nota estende la [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|programmazione dinamica]] a due problemi classici di natura molto diversa: il **Sequence Alignment** (allineamento di sequenze), che misura quanto sono simili due stringhe tramite la *distanza di edit*, e il **Bellman-Ford-Moore**, che risolve il problema dei cammini minimi su grafi con pesi arbitrari — anche negativi — dove l'algoritmo di [[10 - Cammini Minimi e Dijkstra|Dijkstra]] non è applicabile. Per entrambi si deriverà una ricorrenza DP, un algoritmo bottom-up e si analizzeranno tempo e spazio.
## Sequence Alignment
### Motivazione e modello dei costi
Dati due testi — ad esempio le parole `ocurrance` e `occurrence`, oppure due sequenze di DNA — si vuole quantificare quanto è costoso trasformare l'una nell'altra tramite inserzioni, cancellazioni e sostituzioni di caratteri. L'approccio formale consiste nell'allineare le due stringhe, eventualmente inserendo dei **gap** (carattere vuoto `–`), e sommare i costi delle differenze.
> [!quote] Definizione — Edit distance (Levenshtein 1966, Needleman–Wunsch 1970)
> Siano $X = x_1 x_2 \ldots x_m$ e $Y = y_1 y_2 \ldots y_n$ due stringhe. Il modello dei costi è:
> - **Gap penalty** $\delta \geq 0$: costo per lasciare un carattere senza corrispondenza (gap).
> - **Mismatch penalty** $\alpha_{pq} \geq 0$: costo per accoppiare il carattere $p$ con il carattere $q$; convenzionalmente $\alpha_{pp} = 0$.
> La **distanza di edit** tra $X$ e $Y$ è il costo minimo di un allineamento tra le due stringhe.

> [!quote] Definizione — Allineamento
> Un **allineamento** $M$ è un insieme di coppie ordinate $(x_i, y_j)$ tale che:
> 1. ogni carattere appare in **al più una** coppia;
> 2. non ci sono **incroci**: se $(x_i, y_j) \in M$ e $(x_{i'}, y_{j'}) \in M$ con $i < i'$, allora $j < j'$.
> Il **costo** dell'allineamento è:
> $$\text{cost}(M) = \sum_{(x_i,\, y_j)\in M} \alpha_{x_i y_j} \;+\; \delta \cdot |\{i : x_i \text{ non in }M\}| \;+\; \delta \cdot |\{j : y_j \text{ non in }M\}|$$

> [!example] Esempio — PALETTE vs PALATE ($\delta = 2$, $\alpha_{\text{mismatch}} = 1$)
> ```
>   P   A   L   E   T   T   E
>   P   A   L   –   A   T   E
> ```
> Costo = $\delta + \alpha_{EA}$ = $2 + 1 = 3$ (1 gap, 1 mismatch).
> Questo è l'allineamento ottimo per questi parametri.
### Struttura della sotto-soluzione ottima
**Definizione del sotto-problema.** Sia $\text{OPT}(i, j)$ il costo minimo dell'allineamento dei prefissi $x_1 \ldots x_i$ e $y_1 \ldots y_j$.
**Obiettivo.** Calcolare $\text{OPT}(m, n)$.
Fissato un allineamento ottimo di $x_1 \ldots x_i$ con $y_1 \ldots y_j$, l'ultimo carattere di ciascun prefisso deve cadere in uno dei tre casi:
- **Caso 1 — match/mismatch:** $x_i$ è accoppiato con $y_j$; si paga $\alpha_{x_i y_j}$ più il costo ottimo dell'allineamento dei prefissi rimanenti $x_1 \ldots x_{i-1}$ e $y_1 \ldots y_{j-1}$.
- **Caso 2a — gap su $X$:** $x_i$ è lasciato senza corrispondenza; si paga $\delta$ più il costo ottimo di $x_1 \ldots x_{i-1}$ con $y_1 \ldots y_j$.
- **Caso 2b — gap su $Y$:** $y_j$ è lasciato senza corrispondenza; si paga $\delta$ più il costo ottimo di $x_1 \ldots x_i$ con $y_1 \ldots y_{j-1}$.
La correttezza si dimostra per **exchange argument**: se il sotto-allineamento non fosse ottimo, si potrebbe sostituire con uno migliore, contraddicendo l'ottimalità del tutto.
> [!quote] Proprietà — Equazione di Bellman (Sequence Alignment)
> $$\text{OPT}(i,\,j) = \begin{cases} j\,\delta & \text{se } i = 0 \\ i\,\delta & \text{se } j = 0 \\ \min\!\bigl\{\,\alpha_{x_i y_j} + \text{OPT}(i-1,\,j-1),\;\; \delta + \text{OPT}(i-1,\,j),\;\; \delta + \text{OPT}(i,\,j-1)\,\bigr\} & \text{altrimenti} \end{cases}$$
### Algoritmo bottom-up
La ricorrenza ha la proprietà che $\text{OPT}(i, j)$ dipende solo da celle con indici strettamente minori: la matrice si riempie per righe (o per colonne) in modo che ogni cella sia già disponibile quando serve.
```pseudo
\begin{algorithm}
\caption{Sequence-Alignment($m, n, x_1, \ldots, x_m, y_1, \ldots, y_n, \delta, \alpha$)}
\begin{algorithmic}
\For{$i \gets 0$ \To $m$}
  \State $M[i, 0] \gets i \cdot \delta$
\EndFor
\For{$j \gets 0$ \To $n$}
  \State $M[0, j] \gets j \cdot \delta$
\EndFor
\For{$i \gets 1$ \To $m$}
  \For{$j \gets 1$ \To $n$}
    \State $M[i, j] \gets \min\{\, \alpha_{x_i y_j} + M[i-1, j-1],\;\; \delta + M[i-1, j],\;\; \delta + M[i, j-1] \,\}$
  \EndFor
\EndFor
\State \Return $M[m, n]$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema — Complessità Sequence Alignment
> L'algoritmo DP calcola la distanza di edit (e un allineamento ottimo tramite traceback) di due stringhe di lunghezze $m$ e $n$ in tempo $\Theta(mn)$ e spazio $\Theta(mn)$.

| Risorsa | Costo |
|---|---|
| Tempo | $\Theta(mn)$ — $mn$ celle, ciascuna in $O(1)$ |
| Spazio | $\Theta(mn)$ — intera matrice $M$ |
### Traceback per ricostruire l'allineamento
Dopo aver riempito la matrice, si ripercorre a ritroso da $M[m, n]$ a $M[0, 0]$: in ogni cella $(i, j)$ si identifica quale dei tre casi ha determinato il minimo e si segue la freccia corrispondente (diagonale, su, sinistra). I caratteri accoppiati generano match/mismatch; i movimenti orizzontali o verticali generano gap.

> [!example] Traceback — PALETTE ($m=7$) vs PALATE ($n=6$), $\delta=2$, $\alpha_{\text{mis}}=1$
> La matrice $M$ riempita per righe:
> ```
>        ε    P    A    L    A    T    E
>   ε    0    2    4    6    8   10   12
>   P    2    0    2    4    6    8   10
>   A    4    2    0    2    4    6    8
>   L    6    4    2    0    2    4    6
>   E    8    6    4    2    1    3    4
>   T   10    8    6    4    3    1    3
>   T   12   10    8    6    5    3    2
>   E   14   12   10    8    7    5    3
> ```
> Il traceback da $M[7,6]=3$ dà l'allineamento `PALETTE` / `PAL–ATE`: 1 gap + 1 mismatch, costo $2+1=3$.

> [!question] Domanda tipica d'esame — Complessità Sequence Alignment
> **D:** Qual è la complessità del Sequence Alignment e da dove deriva il vincolo sullo spazio?
> **R:** Tempo $\Theta(mn)$ perché si calcolano $mn$ sotto-problemi in $O(1)$ ciascuno; spazio $\Theta(mn)$ perché si mantiene l'intera matrice per poter eseguire il traceback. Se si vuole solo il valore della distanza (non l'allineamento), basta tenere due colonne adiacenti, riducendo lo spazio a $O(m + n)$.
## Algoritmo di Hirschberg (spazio lineare)
La matrice $\Theta(mn)$ può essere proibitiva per stringhe lunghe. Hirschberg (1975) ha dimostrato che si può ottenere sia l'allineamento che il valore ottimo in spazio $O(m + n)$, mantenendo il tempo $O(mn)$, combinando divide-et-impera con la DP.
> [!quote] Teorema — Hirschberg
> Esiste un algoritmo per trovare un allineamento ottimo in tempo $O(mn)$ e spazio $O(m + n)$.

**Prima osservazione — spazio $O(m+n)$ per il valore.**
Per calcolare la colonna $j$ della matrice basta la colonna $j-1$: si mantengono quindi solo due vettori di lunghezza $m+1$ (la colonna corrente e quella precedente), riducendo lo spazio a $O(m+n)$. Il problema è che questo non permette il traceback: si perde la struttura dell'allineamento.
**Grafo di edit.**
Si interpreta la matrice DP come un grafo orientato in cui ogni nodo $(i,j)$ ha:
- un arco diagonale verso $(i-1, j-1)$ di peso $\alpha_{x_i y_j}$,
- un arco verticale verso $(i-1, j)$ di peso $\delta$,
- un arco orizzontale verso $(i, j-1)$ di peso $\delta$.

Sia $f(i,j)$ la lunghezza del cammino minimo da $(0,0)$ a $(i,j)$ e $g(i,j)$ quella da $(i,j)$ a $(m,n)$ (calcolata invertendo gli archi e i ruoli dei due estremi). Si ha:
- $f(i,j) = \text{OPT}(i,j)$ per tutti $i,j$ (dim. per induzione forte su $i+j$);
- la lunghezza del cammino minimo che passa per $(i,j)$ è $f(i,j) + g(i,j)$;
- $f(\cdot, j)$ e $g(\cdot, j)$ si calcolano ognuna in tempo $O(mn)$ e spazio $O(m+n)$.

> [!quote] Proprietà — Osservazione 2 (Hirschberg)
> Sia $q^*$ l'indice che minimizza $f(q,\, n/2) + g(q,\, n/2)$ su tutti $q \in \{0,\ldots,m\}$. Allora esiste un cammino minimo da $(0,0)$ a $(m,n)$ che passa per $(q^*, n/2)$: questo nodo appartiene all'allineamento ottimo.

**Divide.** Si fissa la colonna centrale $n/2$. Si calcolano $f(q,\, n/2)$ e $g(q,\, n/2)$ per tutti $q$; si trova $q^*$ che minimizza la somma. Il nodo $(q^*, n/2)$ fa parte della soluzione.
**Conquer.** Si richiama ricorsivamente l'algoritmo su $(x_1\ldots x_{q^*},\; y_1\ldots y_{n/2})$ e su $(x_{q^*+1}\ldots x_m,\; y_{n/2+1}\ldots y_n)$.
```text
       (0,0) ─────── colonna n/2 ──────── (m,n)
                          │
                     (q*,n/2)  ← nodo dell'allineamento ottimo
                        /    \
            ricorsione sx    ricorsione dx
```

> [!quote] Teorema — Analisi di Hirschberg (tempo)
> Sia $T(m, n)$ il tempo di esecuzione. Vale per induzione forte su $m+n$:
> $$T(m, n) \leq T(q^*, n/2) + T(m - q^*, n/2) + O(mn)$$
> **Claim:** $T(m,n) \leq 2cmn$ per una costante $c$ opportuna.
> **Dim.** Casi base: $T(m,2) \leq cm$, $T(2,n) \leq cn$. Passo induttivo:
> $$T(m,n) \;\leq\; 2c q^* \frac{n}{2} + 2c(m-q^*)\frac{n}{2} + cmn = cq^*n + cmn - cq^*n + cmn = 2cmn \quad\square$$

> [!quote] Teorema — Analisi di Hirschberg (spazio)
> L'algoritmo usa spazio $\Theta(m+n)$.
> **Dim.** Ogni chiamata ricorsiva usa $\Theta(m)$ spazio per calcolare $f(\cdot, n/2)$ e $g(\cdot, n/2)$; si mantiene solo $\Theta(1)$ spazio per chiamata attiva; il numero di chiamate ricorsive è $\leq n$. $\square$

| Algoritmo | Tempo | Spazio |
|---|---|---|
| DP standard | $\Theta(mn)$ | $\Theta(mn)$ |
| Hirschberg | $O(mn)$ | $\Theta(m+n)$ |

> [!question] Domanda tipica d'esame — Idea e complessità di Hirschberg
> **D:** Qual è l'idea alla base dell'algoritmo di Hirschberg per il sequence alignment, e quali sono tempo e spazio risultanti rispetto alla DP standard?
> **R:** L'osservazione chiave è che il valore $\text{OPT}(i,j)$ si può calcolare mantenendo solo due colonne della matrice (quella corrente e la precedente), in spazio $O(m+n)$ — ma così si perde la possibilità di fare il traceback. Hirschberg recupera l'allineamento sfruttando il grafo di edit: si calcola $f(i,j)$ (cammino minimo da $(0,0)$ a $(i,j)$, che coincide con $\text{OPT}(i,j)$) e $g(i,j)$ (cammino minimo da $(i,j)$ a $(m,n)$), ciascuno in tempo $O(mn)$ e spazio $O(m+n)$. Sulla colonna centrale $n/2$ si trova l'indice $q^*$ che minimizza $f(q,n/2)+g(q,n/2)$: il nodo $(q^*,n/2)$ appartiene a un allineamento ottimo (Osservazione 2). Si applica poi divide-et-impera, risolvendo ricorsivamente i due sotto-problemi $(x_1\ldots x_{q^*}, y_1\ldots y_{n/2})$ e $(x_{q^*+1}\ldots x_m, y_{n/2+1}\ldots y_n)$. L'analisi mostra che il tempo resta $T(m,n) \leq 2cmn = O(mn)$ (per induzione forte su $m+n$), mentre lo spazio scende a $\Theta(m+n)$ perché ogni chiamata attiva usa solo $\Theta(m)$ spazio e il numero di chiamate ricorsive è limitato. Il vantaggio rispetto alla DP standard ($\Theta(mn)$ tempo e spazio) è quindi lo spazio: stesso ordine di tempo, spazio lineare invece che quadratico.
## Cammini minimi con pesi negativi: Bellman-Ford-Moore
### Perché Dijkstra non basta
L'algoritmo di [[10 - Cammini Minimi e Dijkstra|Dijkstra]] risolve il problema SSSP in tempo $O(m + n \log n)$ con pesi **non negativi**. In presenza di pesi negativi, la strategia greedy di Dijkstra — estrarre il nodo con distanza minima e fissarla definitivamente — non è più valida: un arco negativo potrebbe abbreviare un cammino già "chiuso".

> [!warning] Dijkstra fallisce con pesi negativi
> Consideriamo il grafo con nodi $s, t, v, w$ e archi:
> ```
>     s ──2──> t
>     s ──6──> v
>     v ──4──> t
>     v ──(−8)──> w
>     w ──3──> t
> ```
> Dijkstra estrae $s$, poi **subito $t$** (stima 2, minima in coda) e la **fissa definitivamente**. Solo dopo estrae $v$ (6) e $w$ ($6-8=-2$), scoprendo il cammino $s \to v \to w \to t$ di lunghezza $6 + (-8) + 3 = 1 < 2$. Ma $t$ è già chiuso: l'algoritmo termina restituendo $2$ invece del vero minimo $1$.
> Il punto delicato è che l'arco negativo deve trovarsi **oltre** un nodo estratto tardi: se il cammino alternativo partisse con un arco più leggero di quello diretto, Dijkstra lo esplorerebbe per primo e — su questo grafo — darebbe per caso la risposta giusta.
> **Reweighting:** Aggiungere una costante positiva $c$ a tutti i pesi non funziona — cambia le lunghezze relative tra cammini con numero diverso di archi, alterando quale è il minimo.

> [!question] Domanda tipica d'esame — Perché Dijkstra fallisce con pesi negativi
> **D:** Perché l'algoritmo di Dijkstra non funziona in presenza di archi con peso negativo, e perché non basta sommare una costante positiva a tutti i pesi per aggirare il problema?
> **R:** Dijkstra è greedy: ad ogni passo estrae il nodo con distanza stimata minima e la fissa come definitiva, assumendo implicitamente che nessun cammino scoperto in seguito possa essere più corto — un'assunzione valida solo se tutti i pesi sono non negativi, perché allora estendere un cammino non può mai diminuirne la lunghezza. Con pesi negativi questa assunzione cade: un arco negativo scoperto più tardi può abbreviare un cammino che termina in un nodo già "chiuso". Nell'esempio sopra Dijkstra fissa subito $t$ a 2 tramite l'arco diretto $s \to t$, e solo dopo scopre $s \to v \to w \to t$ di lunghezza $6 + (-8) + 3 = 1$: la risposta corretta è 1, ma $t$ è ormai chiuso e l'algoritmo restituisce 2. Il reweighting ingenuo — sommare una costante $c>0$ a ogni peso per renderli tutti non negativi — non risolve il problema perché penalizza i cammini in proporzione al numero di archi che contengono: un cammino con $k$ archi vede il proprio costo aumentare di $kc$, quindi cammini con più archi (magari quelli davvero minimi grazie ai pesi negativi) vengono relativamente penalizzati rispetto a cammini più corti in numero di archi ma di costo originario maggiore, alterando quale cammino risulta minimo.
### Cicli negativi
> [!quote] Definizione — Ciclo negativo
> Un **ciclo negativo** è un ciclo diretto $W = v_1 \to v_2 \to \ldots \to v_k \to v_1$ per cui
> $$\ell(W) = \sum_{e \in W} \ell_e < 0$$

> [!quote] Lemma 1 — Ciclo negativo e inesistenza del minimo
> Se un qualsiasi cammino da $v$ a $t$ contiene un ciclo negativo, allora **non esiste** un cammino minimo da $v$ a $t$.
> **Dim.** Percorrendo il ciclo negativo un numero arbitrario di volte si ottiene un cammino di lunghezza $\to -\infty$. $\square$

> [!quote] Lemma 2 — Assenza di cicli negativi e semplicità
> Se $G$ non ha cicli negativi, esiste un cammino minimo da $v$ a $t$ che è **semplice** (senza ripetizioni di nodi) e ha al più $n - 1$ archi.
> **Dim.** Tra tutti i cammini minimi, si prenda quello con il minor numero di archi. Se contenesse un ciclo $W$, quest'ultimo avrebbe peso $\ell(W) \geq 0$ (altrimenti esisterebbe un cammino più corto), e potrebbe essere rimosso senza aumentare il costo totale. $\square$
### Formulazione DP
**Definizione del sotto-problema.** Sia $\text{OPT}(i, v)$ la lunghezza del cammino minimo da $v$ a $t$ che usa **al più $i$ archi**.
**Obiettivo.** Calcolare $\text{OPT}(n-1, v)$ per ogni $v$ (per il Lemma 2, bastano $n-1$ archi se non ci sono cicli negativi).

Due casi per il cammino ottimo da $v$ a $t$ con $\leq i$ archi:
- **Caso 1:** il cammino usa $\leq i-1$ archi $\Rightarrow \text{OPT}(i,v) = \text{OPT}(i-1,v)$.
- **Caso 2:** il cammino usa esattamente $i$ archi; sia $(v,w)$ il primo arco $\Rightarrow \text{OPT}(i,v) = \ell_{vw} + \text{OPT}(i-1,w)$, scegliendo $w$ ottimale.

> [!quote] Proprietà — Equazione di Bellman (cammini minimi)
> $$\text{OPT}(i,\,v) = \begin{cases} 0 & \text{se } i = 0 \text{ e } v = t \\ +\infty & \text{se } i = 0 \text{ e } v \neq t \\ \min\!\Bigl(\text{OPT}(i-1,\,v),\;\; \min_{(v,w)\in E}\bigl\{\ell_{vw} + \text{OPT}(i-1,\,w)\bigr\}\Bigr) & \text{se } i > 0 \end{cases}$$

```pseudo
\begin{algorithm}
\caption{Shortest-Paths($V, E, \ell, t$) — algoritmo DP naïve}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State $M[0, v] \gets +\infty$
\EndFor
\State $M[0, t] \gets 0$
\For{$i \gets 1$ \To $n-1$}
  \ForAll{nodo $v \in V$}
    \State $M[i, v] \gets M[i-1, v]$
    \ForAll{arco $(v, w) \in E$}
      \State $M[i, v] \gets \min\{\, M[i, v],\;\; M[i-1, w] + \ell(v,w) \,\}$
    \EndFor
  \EndFor
\EndFor
\State \Return $M[n-1, \cdot]$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema 1 — Complessità dell'algoritmo DP
> Su un grafo $G = (V, E)$ senza cicli negativi, l'algoritmo calcola la lunghezza del cammino minimo da ogni $v$ a $t$ in tempo $\Theta(mn)$ e spazio $\Theta(n^2)$.
> **Dim.** La tabella $M$ ha $n$ righe e $n$ colonne: spazio $\Theta(n^2)$. Ogni iterazione $i$ esamina ogni arco una volta: costo $\Theta(m)$ per iterazione, $n-1$ iterazioni, totale $\Theta(mn)$. $\square$

**Ricostruzione del cammino.** Due approcci:
1. Mantenere `successor[i, v]` puntando al nodo successivo nel cammino minimo con $\leq i$ archi.
2. Dopo aver calcolato $M$, costruire il sotto-grafo degli archi "attivi" $\{(v,w) : M[i,v] = M[i-1,w] + \ell_{vw}\}$: ogni cammino diretto in tale sotto-grafo è un cammino minimo.
### Bellman-Ford-Moore: implementazione efficiente
Lo spazio $\Theta(n^2)$ è spesso inaccettabile. L'ottimizzazione chiave usa:
- Un vettore **$d[v]$** che mantiene la migliore stima corrente della distanza $v \leadsto t$.
- Un vettore **$\text{successor}[v]$** che punta al nodo successivo sul cammino corrente.
- **Ottimizzazione di prestazione:** alla passata $i$, l'arco $(v,w)$ viene considerato solo se $d[w]$ è stato aggiornato alla passata $i-1$ (non ha senso riesaminare nodi la cui distanza non è cambiata).

```pseudo
\begin{algorithm}
\caption{Bellman-Ford-Moore($V, E, \ell, t$)}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State $d[v] \gets +\infty$
  \State $\text{successor}[v] \gets \text{null}$
\EndFor
\State $d[t] \gets 0$
\For{$i \gets 1$ \To $n-1$}
  \ForAll{nodo $w \in V$}
    \If{$d[w]$ è stato aggiornato alla passata $i-1$}
      \ForAll{arco $(v, w) \in E$}
        \If{$d[v] > d[w] + \ell(v,w)$}
          \State $d[v] \gets d[w] + \ell(v,w)$
          \State $\text{successor}[v] \gets w$
        \EndIf
      \EndFor
    \EndIf
  \EndFor
  \If{nessun $d[\cdot]$ è cambiato in questa passata}
    \State \textbf{break}
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!info] Variante single-source
> Le slide impostano il problema come *single-destination* (trovare i cammini minimi da ogni $v$ verso $t$). La variante *single-source* (da $s$ verso ogni $v$) è del tutto equivalente: basta invertire gli archi e scambiare $s$ con $t$.
### Correttezza e analisi
> [!quote] Lemma 3
> Per ogni nodo $v$: $d[v]$ è la lunghezza di **qualche** cammino $v \leadsto t$ (non per forza minimo durante l'esecuzione).

> [!quote] Lemma 4
> Per ogni nodo $v$: $d[v]$ è **monotona non crescente** nel corso dell'algoritmo.

> [!quote] Lemma 5 — Invariante di passata
> Dopo la passata $i$, per ogni nodo $v$:
> $$d[v] \;\leq\; \text{lunghezza del cammino minimo da } v \text{ a } t \text{ che usa} \leq i \text{ archi}$$
> **Dim. (induzione su $i$).** Caso base $i=0$: $d[t]=0$, tutti gli altri $+\infty$. Passo induttivo: sia $P = v \to w \to \ldots \to t$ un cammino con $\leq i+1$ archi, $(v,w)$ il primo arco e $P'$ il sotto-cammino $w \leadsto t$. Per ipotesi induttiva, dopo la passata $i$, $d[w] \leq \ell(P')$. All'esame dell'arco $(v,w)$ nella passata $i+1$, si ottiene $d[v] \leq \ell_{vw} + d[w] \leq \ell_{vw} + \ell(P') = \ell(P)$; per il Lemma 4, $d[v]$ non aumenta. $\square$

> [!quote] Teorema 2 — Correttezza e complessità di Bellman-Ford-Moore
> Assumendo assenza di cicli negativi, l'algoritmo calcola la lunghezza del cammino minimo da ogni $v$ a $t$ in tempo $O(mn)$ e spazio $\Theta(n)$.
> **Dim.** Per il Lemma 2 esiste un cammino minimo semplice con $\leq n-1$ archi; per il Lemma 5, dopo $n-1$ passate $d[v]$ non supera tale lunghezza; per il Lemma 3 $d[v]$ non è mai inferiore alla lunghezza di un vero cammino. Lo spazio è $\Theta(n)$ (due vettori di dimensione $n$). $\square$

> [!info] Velocità pratica
> Bellman-Ford-Moore è tipicamente molto più veloce di $O(mn)$: l'arco $(v,w)$ viene considerato alla passata $i+1$ solo se $d[w]$ è stato aggiornato alla passata $i$. Se il cammino minimo ha $k$ archi, l'algoritmo termina dopo $\leq k$ passate.
### Ricostruzione e grafo dei successori
> [!warning] I puntatori successor non sono affidabili durante l'esecuzione
> **Durante** l'esecuzione, la catena `successor` può essere inconsistente. Esempio dalle slide (nodi in ordine $t, 1, 2, 3$):
> ```
>   Dopo passata 1:
>   successor[2] = 1,  d[2] = 20
>   successor[1] = 3,  d[1] = 2
>   successor[3] = t,  d[3] = 1
>   d[t] = 0
> ```
> Seguendo la catena da 2: $2 \to 1 \to 3 \to t$, lunghezza $d[2]=20$ ma il cammino ha lunghezza reale $\neq 20$. Pertanto la "claim" che seguire i successori restituisca un cammino di lunghezza $d[v]$ è **falsa** durante l'esecuzione.
> Solo **al termine** dell'algoritmo (quando nessun $d[\cdot]$ cambia più) la catena dei successori forma un cammino minimo.

> [!quote] Lemma 6 — Cicli nel grafo dei successori
> Qualsiasi ciclo diretto nel **grafo dei successori** è un ciclo negativo.
> **Dim.** Se `successor[v] = w`, allora $d[v] \geq d[w] + \ell_{vw}$ (con uguaglianza quando il successore viene impostato; $d[w]$ può solo decrescere; $d[v]$ decresce solo quando il successore viene reimpostato). Sia $v_1 \to v_2 \to \ldots \to v_k \to v_1$ un ciclo nel grafo dei successori, e $(v_k, v_1)$ l'ultimo arco aggiunto. Subito prima di tale aggiornamento:
> $$d[v_1] \geq d[v_2] + \ell(v_1,v_2), \quad d[v_2] \geq d[v_3] + \ell(v_2,v_3), \quad \ldots, \quad d[v_k] > d[v_1] + \ell(v_k,v_1)$$
> (l'ultima disuguaglianza è stretta perché stiamo aggiornando $d[v_k]$). Sommando:
> $$0 > \ell(v_1,v_2) + \ell(v_2,v_3) + \ldots + \ell(v_{k-1},v_k) + \ell(v_k,v_1) = \ell(W)$$
> Dunque $W$ è un ciclo negativo. $\square$

> [!quote] Teorema 3 — Correttezza dei successori a terminazione
> Assumendo assenza di cicli negativi, al termine di Bellman-Ford-Moore, seguendo i puntatori `successor` da ogni $v$ si ottiene un cammino minimo $v \leadsto t$ di lunghezza $d[v]$.
> **Dim.** Per il Lemma 6, il grafo dei successori non ha cicli (altrimenti ci sarebbero cicli negativi, contro l'ipotesi). Quindi seguire i successori da $v$ porta a $t$. Sia $v = v_1 \to v_2 \to \ldots \to v_k = t$ tale cammino $P$. A terminazione, per ogni arco $(v_i, v_{i+1})$ con `successor[v_i] = v_{i+1}` vale $d[v_i] = d[v_{i+1}] + \ell(v_i, v_{i+1})$ (i valori non cambiano più). Sommando lungo $P$:
> $$d[v] = d[t] + \ell(v_1,v_2) + \ldots + \ell(v_{k-1},v_k) = 0 + \ell(P)$$
> Per il Teorema 2, $d[v]$ è la lunghezza minima di qualsiasi cammino $v \leadsto t$, quindi $P$ è un cammino minimo. $\square$
### Rilevamento di cicli negativi
Per rilevare cicli negativi raggiungibili da $t$, si esegue una **passata aggiuntiva** ($i = n$) dopo le $n-1$ normali:

```pseudo
\begin{algorithm}
\caption{Bellman-Ford-Moore($V, E, \ell, t$) — con rilevamento dei cicli negativi}
\begin{algorithmic}
\State $\ldots$ \Comment{righe 1–12 di Bellman-Ford-Moore: inizializzazione e ciclo principale}
\ForAll{arco $(v, w) \in E$}
  \If{$d[v] > d[w] + \ell(v,w)$}
    \State \Return "esiste un ciclo negativo"
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!quote] Lemma — Correttezza del rilevamento
> Se esiste un ciclo negativo raggiungibile da $t$, la passata $n$ lo rileva.
> **Dim.** Se non ci fosse nessun ciclo negativo, la passata $n$ non cambierebbe nulla (le distanze sono già ottime dopo $n-1$ passate, per il Teorema 2). Se invece esiste un ciclo negativo $W = v_1 \to \ldots \to v_k \to v_1$, si assume per assurdo che la condizione di riga 14 sia sempre falsa. Allora $d[v_i] \leq d[v_{i+1}] + \ell(v_i, v_{i+1})$ per ogni $i$ (indici ciclici). Sommando lungo $W$: $\ell(W) \geq 0$, contraddizione. $\square$

> [!question] Domanda tipica d'esame — Rilevamento cicli negativi
> **D:** Come rileva Bellman-Ford-Moore un ciclo negativo?
> **R:** Dopo $n-1$ passate normali (sufficienti per i cammini semplici ottimi in assenza di cicli negativi), si esegue una passata $n$-esima. Se almeno un arco $(v,w)$ soddisfa ancora $d[v] > d[w] + \ell_{vw}$, significa che esiste un cammino che beneficia di più di $n-1$ archi, il che è possibile solo in presenza di un ciclo negativo raggiungibile da $t$.
### Esempio di esecuzione
Grafo con nodi $t, B, C, D, E$ (l'arco di ingresso dal nodo $A$ è implicito); ordine di visita delle slide: $t, D, C, B, E$.
```
                   2
           B ─────────── E
    -1    / \           / -3
         /   \   3     /
   t ───      ─────── ?
         \         1 /
    4     \─────── C ─────── D
                       5
```
> [!info] Nota sull'esempio
> Le slide mostrano il grafo eseguendo l'algoritmo con l'ordine $t, D, C, B, E$. Dopo poche passate l'algoritmo converge prima di $n-1$ iterazioni (terminazione anticipata), dimostrando che in pratica Bellman-Ford-Moore è spesso molto più veloce del worst-case $O(mn)$.
## Confronto Dijkstra vs Bellman-Ford-Moore
| Proprietà | [[10 - Cammini Minimi e Dijkstra\|Dijkstra]] | Bellman-Ford-Moore |
|---|---|---|
| Pesi negativi | No (fallisce) | Sì |
| Cicli negativi | — | Rilevati con passata $n$ |
| Tempo (con heap Fibonacci) | $O(m + n \log n)$ | $O(mn)$ |
| Spazio | $O(n)$ | $\Theta(n)$ |
| Tecnica | Greedy | Programmazione dinamica |
| Applicabilità | Pesi $\geq 0$ | Pesi arbitrari, no cicli neg. |

> [!info] Collegamento con le note precedenti
> - La tecnica DP di questa nota si innesta direttamente su [[04 - Programmazione Dinamica I (Weighted Independent Set)]] e [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]: stessa metodologia (sotto-struttura ottima, ricorrenza, bottom-up).
> - La visita del grafo e la nozione di cammino minimo rimandano a [[08 - Grafi e Visite]] e [[10 - Cammini Minimi e Dijkstra]].
> - Bellman-Ford-Moore è il fondamento teorico del protocollo di routing **RIP** (Routing Information Protocol) nelle reti di calcolatori.
