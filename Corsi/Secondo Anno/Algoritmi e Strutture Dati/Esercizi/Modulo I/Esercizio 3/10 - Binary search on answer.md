---
tags:
  - algoritmi
---
# Binary search on answer
Esercizio 3 (Modellazione) — pattern [[Casistiche d'Esame Modulo I]], checklist [[Piano Esame ASD - Modulo I]]; ripasso: [[08 - Grafi e Visite]].

> [!question] Traccia — 02/02/2026
> Dato un grafo orientato $G=(V,E)$ con $n$ nodi e $m$ archi, un nodo sorgente $s\in V$ e interi $h,k\ge 1$. A ogni arco $e\in E$ è associato un livello $\lambda(e)\in\{1,\ldots,k\}$. Un abbonamento di livello $\ell$ consente di percorrere solo gli archi con $\lambda(e)\le\ell$. Determinare il minimo livello $\ell^*\in\{1,\ldots,k\}$ tale che, con un abbonamento di livello $\ell^*$, ogni nodo $v\in V$ sia raggiungibile da $s$ in al più $h$ archi. Se nessun $\ell$ è sufficiente, restituire $-1$.

**Modellazione.** La fattibilità è **monotona rispetto al livello**: se con $\ell$ ogni nodo è raggiungibile da $s$ in $\le h$ hop, allora con $\ell+1$ si dispone di più archi e la proprietà rimane vera. La monotonia consente di applicare la tecnica **binary search on answer**: ricerca binaria su $\{1,\ldots,k\}$ del minimo $\ell$ fattibile, chiamando l'oracolo $O(\log k)$ volte.

L'oracolo per un candidato $\ell$:
1. Costruisce il **grafo filtrato** $G_\ell=(V,\,E_\ell)$ con $E_\ell=\{e\in E:\lambda(e)\le\ell\}$ — stessi $n$ nodi, al più $m$ archi.
2. Esegue BFS da $s$ su $G_\ell$; le distanze $d[v]$ contano il numero di hop (non i pesi).
3. Risponde **sì** se e solo se $\forall v\in V:\,d[v]\le h$.

```pseudo
\begin{algorithm}
\caption{AbbonamentoMinimo($G$, $s$, $h$, $k$) → intero}
\begin{algorithmic}
\State $lo \gets 1$,\; $hi \gets k$,\; $ris \gets -1$
\While{$lo \le hi$}
  \State $mid \gets \lfloor(lo + hi)/2\rfloor$
  \If{\Call{Fattibile}{$G$, $s$, $h$, $mid$}}
    \State $ris \gets mid$
    \State $hi \gets mid - 1$
  \Else
    \State $lo \gets mid + 1$
  \EndIf
\EndWhile
\State \Return $ris$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Fattibile($G$, $s$, $h$, $\ell$) → booleano}
\begin{algorithmic}
\State $G_\ell \gets (V,\; \{e \in E : \lambda(e) \le \ell\})$ \Comment{grafo filtrato per livello}
\State $d \gets$ \Call{BFS}{$G_\ell$, $s$} \Comment{$d[v]$ = numero di hop da $s$ a $v$}
\For{ogni $v \in V$}
  \If{$d[v] = \infty$ o $d[v] > h$}
    \State \Return falso
  \EndIf
\EndFor
\State \Return vero
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O((n+m)\log k)$: ogni chiamata a `Fattibile` costa $O(n+m)$ (costruzione di $G_\ell$ più BFS), ripetuta $O(\log k)$ volte. Con pre-ordinamento degli archi per livello in $O(m\log m)$ e $k\le m$, il costo totale è $O(m\log m)$.
**Trappola:** la monotonicità della fattibilità va verificata (non è automatica in ogni problema); nel BFS filtrare con $\lambda(e)\le\ell$ e non $\lambda(e)=\ell$; il numero di hop $h$ è il numero di archi percorsi, non il peso del cammino.
