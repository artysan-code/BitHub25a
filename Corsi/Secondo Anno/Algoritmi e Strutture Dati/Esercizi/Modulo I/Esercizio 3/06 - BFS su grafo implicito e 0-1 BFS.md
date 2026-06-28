---
tags:
  - algoritmi
---
# BFS su grafo implicito e 0-1 BFS
Casistica tipica dell'Es. 3 (Modellazione): vedi [[Casistiche d'Esame Modulo I]] per il quadro completo, [[Piano Esame ASD - Modulo I]] per la checklist, [[08 - Grafi e Visite]] per BFS e grafi impliciti, [[07 - Code con Priorità e Heap]] per la deque e la 0-1 BFS, [[10 - Cammini Minimi e Dijkstra]] per il contesto dei cammini minimi con pesi piccoli.
## Svolgimento — esame 18/07/2025
> [!question] Traccia — 18/07/2025
> Data una griglia $n \times m$ di celle, ognuna colorata di nero o bianco, e due celle $a$ e $b$, trovare il percorso da $a$ a $b$ (con mosse nelle 4 direzioni cardinali) che minimizza il numero di celle bianche attraversate. Attraversare una cella nera ha costo $0$; attraversare una cella bianca (annerendola) ha costo $1$. Restituire il minimo numero di celle bianche da annerire.
**Modellazione.** Il grafo non è fornito esplicitamente, ma ha struttura regolare di griglia:
- **Nodi:** $n \cdot m$ celle $(i,j)$ con $1 \le i \le n$, $1 \le j \le m$; in totale $|V| = nm$.
- **Archi:** ogni cella interna ha esattamente $4$ vicini cardinali; le celle di bordo ne hanno $2$ o $3$. Grado costante $\Rightarrow$ $|E| = O(nm)$.
- **Pesi:** l'arco verso la cella $(i',j')$ ha peso $w = 0$ se $(i',j')$ è nera, $w = 1$ se bianca.

Poiché $w \in \{0,1\}$, Dijkstra su heap costerebbe $O(nm \log nm)$: si usa invece la **0-1 BFS con deque** che sfrutta i pesi binari per mantenere l'invariante di distanza non-decrescente in $O(nm)$. Un arco a costo $0$ non aumenta la distanza corrente: il nodo destinazione viene inserito in **testa** alla deque (come un'operazione BFS); un arco a costo $1$ lo inserisce in **coda**. In questo modo la deque è sempre ordinata per distanza crescente e l'algoritmo è corretto.

```pseudo
\begin{algorithm}
\caption{SerpentoneMinBianche($\text{col}$, $n$, $m$, $a$, $b$) → intero}
\begin{algorithmic}
\State $d[i][j] \gets \infty$ per ogni $(i,j) \in [1..n] \times [1..m]$
\State $d[a] \gets 0$
\State deque $D \gets \langle a \rangle$
\While{$D \neq \emptyset$}
  \State $(i,j) \gets$ estrai dalla testa di $D$
  \For{ogni vicino $(i',j')$ di $(i,j)$ nelle 4 direzioni cardinali}
    \State $w \gets [\,\text{col}[i'][j'] = \text{bianco}\,]$ \Comment{$0$ se nero, $1$ se bianco}
    \If{$d[i][j] + w < d[i'][j']$}
      \State $d[i'][j'] \gets d[i][j] + w$
      \If{$w = 0$}
        \State inserisci $(i',j')$ in testa a $D$
      \Else
        \State inserisci $(i',j')$ in coda a $D$
      \EndIf
    \EndIf
  \EndFor
\EndWhile
\State \Return $d[b]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(nm)$ — ogni cella viene estratta dalla deque al più due volte (l'algoritmo aggiorna $d[\cdot]$ solo se trova un valore migliore) e ogni arco è esaminato $O(1)$ volte; lo spazio per la deque è $O(nm)$.
**Trappola:** la 0-1 BFS non funziona con una coda FIFO normale. Inserire indiscriminatamente tutti i vicini in coda viola l'invariante di distanza non-decrescente: nodi a distanza $d$ e nodi a distanza $d+1$ si mescolerebbero, producendo distanze errate. Nella griglia si usano solo le 4 direzioni cardinali (no diagonali).
## Variante — golf 1D (26/06/2025)
> [!question] Traccia — 26/06/2025
> Una pallina si trova nella posizione $s \in \{1,\ldots,n\}$. Da ogni posizione $i$ sono disponibili al più $4$ mosse prestabilite (salti di lunghezza fissa in avanti o indietro, con destinazione valida entro $\{1,\ldots,n\}$); ogni mossa ha costo $1$. Trovare il minimo numero di mosse per raggiungere la posizione $t$.
**Modellazione.** Il grafo è implicito e unidimensionale:
- **Nodi:** $n$ posizioni $1, \ldots, n$; $|V| = n$.
- **Archi:** al più $4$ archi uscenti per nodo ⟹ $|E| = O(n)$.
- **Pesi:** tutti uguali a $1$ ⟹ BFS classica (pesi uniformi, nessuna deque).

Con $|E| = O(n)$ basta una BFS classica dalla sorgente: si costruisce la lista di adiacenza (grado $\le 4$) e si richiama la procedura standard.
```pseudo
\begin{algorithm}
\caption{GolfMinColpi($d$, $\text{tipo}$, $n$, $s$, $t$) → intero}
\begin{algorithmic}
\State $G \gets$ grafo con nodi $\{1,\dots,n\}$ e insieme archi vuoto
\For{$i \gets 1$ \To $n$}
  \For{$j \gets 1$ \To $2$}
    \State $\delta \gets d(\text{tipo}[i], j)$
    \If{$i - \delta \geq 1$}
      \State aggiungi l'arco $(i,\ i-\delta)$ a $G$
    \EndIf
    \If{$i + \delta \leq n$}
      \State aggiungi l'arco $(i,\ i+\delta)$ a $G$
    \EndIf
  \EndFor
\EndFor
\State \Return \Call{BFS}{$G$, $s$}$[t]$
\end{algorithmic}
\end{algorithm}
```
Non serve né Dijkstra né la 0-1 BFS: il grado costante è la chiave dell'efficienza.

**Complessità:** $O(n)$ — grafo implicito a grado $\le 4$, BFS lineare nella dimensione del grafo.
**Trappola:** la BFS classica (FIFO) è corretta solo perché tutti i pesi sono $1$; se le mosse avessero costi diversi occorrerebbe Dijkstra. Costruire la lista di adiacenza esplicitamente prima di lanciare BFS ha costo $O(n)$ e non peggiora la complessità, purché si generi solo un numero costante di archi per nodo.
