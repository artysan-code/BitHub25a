---
tags:
  - algoritmi
---
# Forte connettività con modifica locale
Esercizio 3 (Modellazione) — casistica [[Casistiche d'Esame Modulo I]], checklist [[Piano Esame ASD - Modulo I]]; ripasso: [[08 - Grafi e Visite]] (DFS, componenti fortemente connesse).

> [!question] Traccia — 24/09/2024
> Un network aeroportuale è modellato come un grafo orientato $G=(V,E)$ con $n$ nodi (scali) e $m$ archi (rotte). Un sottoinsieme $C\subseteq V$ contiene i cosiddetti *hub configurabili*: invertire la configurazione di un hub $x\in C$ significa invertire simultaneamente tutti gli archi incidenti a $x$ (sia entranti sia uscenti), ottenendo il grafo $G_x$. Progettare un algoritmo che determina se $G$ è già fortemente connesso, oppure se esiste un hub $x\in C$ tale che $G_x$ è fortemente connesso. Analizzare la complessità.

**Modellazione.**
Si usa come subroutine l'algoritmo **Componenti Fortemente Connesse** (CFC): $G$ è fortemente connesso (FC) se e solo se l'algoritmo restituisce un'unica CFC su $G$. Con $|\cdot|$ si indica il numero di CFC restituite.

Il grafo $G_x$ ha gli stessi $|V|=n$ nodi e $|E|=m$ archi di $G$: si ottiene riscandendo $E$ e invertendo ogni arco $(u,v)$ che ha almeno un estremo uguale a $x$. La costruzione costa $O(n+m)$ per ogni hub e non altera la dimensione del grafo.

*Algoritmo.* Si controlla dapprima se $G$ è già FC. In caso negativo, per ciascun $x\in C$ si costruisce $G_x$ e si verifica la FC con l'algoritmo Componenti Fortemente Connesse. Il primo hub che supera il test è la risposta.

```pseudo
\begin{algorithm}
\caption{CostruisciGx($G$, $x$) → grafo}
\begin{algorithmic}
\State $G_x \gets$ grafo con nodi $V$ e insieme archi vuoto
\For{ogni arco $(u,v) \in E$}
  \If{$u = x \lor v = x$}
    \State aggiungi $(v,u)$ ad $E(G_x)$ \Comment{arco incidente a $x$: si inverte}
  \Else
    \State aggiungi $(u,v)$ ad $E(G_x)$ \Comment{arco non incidente: invariato}
  \EndIf
\EndFor
\State \Return $G_x$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{HubFC($G$, $C$) → nodo $\in C$ oppure esito}
\begin{algorithmic}
\If{$|\Call{ComponentiFortementeConnesse}{G}| = 1$}
  \State \Return "già FC"
\EndIf
\For{ogni $x \in C$}
  \State $G_x \gets \Call{CostruisciGx}{G, x}$
  \If{$|\Call{ComponentiFortementeConnesse}{G_x}| = 1$}
    \State \Return $x$
  \EndIf
\EndFor
\State \Return "nessun hub risolve il problema"
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(|C|(n+m))$. Il test iniziale su $G$ costa $O(n+m)$ ed è dominato. Per ciascuno dei $|C|$ hub, CostruisciGx costa $O(n+m)$ (scansione di tutti gli archi) e l'algoritmo Componenti Fortemente Connesse su $G_x$ costa $O(n+m)$; il ciclo contribuisce quindi $O(|C|(n+m))$ in totale.
**Trappola:** omettere il controllo preliminare su $G$ porta a cercare un hub anche quando non serve; la modifica inverte *sia* gli archi entranti *sia* quelli uscenti di $x$, non solo uno dei due sottoinsiemi — invertirne solo metà produce un grafo diverso da $G_x$ e non garantisce la FC attesa.
