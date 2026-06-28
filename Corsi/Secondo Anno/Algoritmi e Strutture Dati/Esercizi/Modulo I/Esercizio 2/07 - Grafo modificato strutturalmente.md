---
tags:
  - algoritmi
---
# Grafo modificato strutturalmente
Esercizio di progettazione su grafi (casistica [[Casistiche d'Esame Modulo I|grafo modificato strutturalmente]]); ripasso: [[08 - Grafi e Visite]]; checklist [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 18/07/2022
> Dato un grafo diretto $G=(V,E)$ con $n$ nodi e $m$ archi e un sottoinsieme $S\subseteq V$ di nodi "speciali", si definisce il grafo $G'=(V,E')$ in cui $E'$ contiene tutti gli archi di $E$ e, per ogni arco $(v,x)\in E$ con $x\in S$, anche l'arco inverso $(x,v)$. Determinare se $G'$ è fortemente connesso. L'algoritmo deve operare in $O(n+m)$.

**Idea.** Si costruisce $G'$ scandendo $E$ una sola volta: ogni arco $(v,x)$ viene copiato in $E'$; se $x\in S$ (test $O(1)$ con array booleano o hash set su $S$) si aggiunge anche l'arco inverso $(x,v)$. Ogni arco originale genera al più un arco extra, quindi $|E'|=O(m)$ e $|V'|=n$: le dimensioni del grafo non esplodono. Su $G'$ si esegue Kosaraju: se restituisce una sola SCC il grafo è fortemente connesso.

```pseudo
\begin{algorithm}
\caption{GrafoModificato($G$, $S$) → booleano}
\begin{algorithmic}
\State $E' \gets \emptyset$
\For{ogni arco $(v,x)\in E$}
  \State aggiungi $(v,x)$ a $E'$
  \If{$x\in S$}
    \State aggiungi $(x,v)$ a $E'$ \Comment{mossa inversa: nodo speciale}
  \EndIf
\EndFor
\State $G' \gets (V,\,E')$
\State $\mathit{scc} \gets$ \Call{Kosaraju}{$G'$}
\State \Return $|\mathit{scc}| = 1$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n+m)$ — la costruzione di $G'$ scandisce $E$ in $O(m)$; Kosaraju opera in $O(n+m)$ su $G'$ che ha $n$ nodi e $O(m)$ archi.
**Trappola:** aggiungere l'arco inverso per *ogni* coppia $(x,v)$ con $x\in S$ e $v\in V$ (indipendentemente dall'esistenza di $(v,x)$ in $E$) farebbe esplodere $|E'|$ a $O(n\cdot|S|)=O(n^2)$; la regola si applica esclusivamente agli archi già presenti in $E$.
