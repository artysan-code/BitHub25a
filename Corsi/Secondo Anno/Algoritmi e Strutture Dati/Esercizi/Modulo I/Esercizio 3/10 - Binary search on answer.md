---
tags:
  - algoritmi
  - grafi
---
# Binary search on answer
Esercizio di **modellazione**: la risposta (un livello/soglia) rende una proprietà **monotona** — vera da un certo valore in poi — quindi si cerca il minimo valore fattibile con una **ricerca binaria sul risultato**, testando ogni candidato con un algoritmo noto (qui una BFS). Ripasso: [[08 - Grafi e Visite#Visita in ampiezza — BFS|BFS]].
## Traccia
> [!question] Traccia — 02/02/2026
> La rete di trasporti è un grafo **non orientato** $G=(V,E)$ (nodi = stazioni). Ci sono $k$ livelli di abbonamento ($1..k$, costo crescente); ogni arco $e$ ha un livello $\lambda(e)$: la tratta è percorribile con un abbonamento di livello $\geq\lambda(e)$. Partendo dalla stazione $s$, trovare l'abbonamento **più economico** (minimo livello) che permetta di raggiungere ogni stazione in al più $h$ tratte. Punteggio pieno $O(m\log m)$.

Un abbonamento di livello $\ell$ abilita esattamente gli archi con $\lambda(e)\leq\ell$. Serve il minimo $\ell$ tale che, usando solo quegli archi, ogni nodo sia a distanza (in numero di tratte) $\leq h$ da $s$.
## Idea risolutiva
La fattibilità è **monotona in $\ell$**: se con $\ell$ ogni nodo è raggiungibile in $\leq h$ tratte, con $\ell+1$ si hanno **più** archi e la proprietà resta vera. Si applica quindi **binary search on answer** su $\{1,\dots,k\}$, con un oracolo di fattibilità chiamato $O(\log k)$ volte. L'oracolo per il candidato $\ell$: costruisce il grafo filtrato $G_\ell=(V,\{e:\lambda(e)\leq\ell\})$, esegue una **BFS** da $s$ (le distanze contano le tratte), e risponde sì se e solo se $d[v]\leq h$ per ogni $v$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{abbonamentoMinimo($G$, $s$, $h$, $k$) → intero}
\begin{algorithmic}
\State $lo \gets 1$; $hi \gets k$; $\mathit{ris} \gets -1$
\While{$lo \leq hi$}
  \State $mid \gets \lfloor (lo+hi)/2 \rfloor$
  \If{\Call{fattibile}{$G$, $s$, $h$, $mid$}}
    \State $\mathit{ris} \gets mid$; $hi \gets mid - 1$
  \Else
    \State $lo \gets mid + 1$
  \EndIf
\EndWhile
\State \Return $\mathit{ris}$ \Comment{$-1$ se nessun livello basta}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{fattibile($G$, $s$, $h$, $\ell$) → booleano}
\begin{algorithmic}
\State $G_\ell \gets (V,\ \{e \in E : \lambda(e) \leq \ell\})$ \Comment{grafo filtrato per livello}
\State $d \gets$ \Call{visitaBFS}{$G_\ell$, $s$} \Comment{$d[v]$ = numero di tratte da $s$}
\ForAll{$v \in V$}
  \If{$d[v] = \infty$ o $d[v] > h$} \State \Return falso \EndIf
\EndFor
\State \Return vero
\end{algorithmic}
\end{algorithm}
```
## Complessità
Ogni `fattibile` costruisce $G_\ell$ ed esegue una BFS: $O(n+m)$. La ricerca binaria la invoca $O(\log k)$ volte → $O((n+m)\log k)$. Con $k\leq m$ (i livelli utili sono al più quanti gli archi) e un grafo connesso ($m\geq n-1$), il costo è **$O(m\log m)$**, il punteggio pieno.
## Correttezza
> [!quote] Invariante — monotonia della fattibilità
> Se il livello $\ell$ è fattibile, lo è ogni $\ell'>\ell$: $G_{\ell'}\supseteq G_\ell$ ha tutti gli archi di $G_\ell$, quindi le distanze BFS da $s$ non aumentano e la condizione $d[v]\leq h$ continua a valere.

**Dimostrazione della correttezza.** Per la monotonia, l'insieme dei livelli fattibili è un suffisso $\{\ell^\*,\dots,k\}$ (eventualmente vuoto). La ricerca binaria classica su predicato monotono restituisce l'estremo sinistro $\ell^\*$ (il minimo fattibile) o $-1$ se nessun livello lo è. L'oracolo è corretto perché la BFS su $G_\ell$ calcola le distanze in numero di tratte da $s$, e "ogni stazione raggiungibile in $\leq h$ tratte" è esattamente $\forall v:\,d[v]\leq h$ (con $d[v]=\infty$ per gli irraggiungibili). $\blacksquare$

> [!warning] Filtro $\leq\ell$ e tratte, non pesi
> Il grafo filtrato include gli archi con $\lambda(e)\leq\ell$ (non $=\ell$); $h$ conta il **numero di tratte** (archi), quindi la BFS (pesi unitari) è l'algoritmo giusto, non Dijkstra. La monotonia va verificata: è ciò che legittima la binary search on answer.
