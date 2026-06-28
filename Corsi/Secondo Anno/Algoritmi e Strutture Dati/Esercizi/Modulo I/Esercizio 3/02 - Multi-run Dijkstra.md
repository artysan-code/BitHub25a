---
tags:
  - algoritmi
---
# Multi-run Dijkstra
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 3 (Modellazione)]] di ASD. Ripasso: [[10 - Cammini Minimi e Dijkstra]], [[08 - Grafi e Visite]], [[07 - Code con Priorità e Heap]], [[05 - Strutture Dati Elementari e Dizionari]]. Checklist: [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 20/02/2023
> Dato un grafo orientato pesato $G=(V,E,w)$ con $w:E\to\mathbb{R}_{\ge 0}$, un nodo sorgente $s$, un nodo destinazione $t$ e un insieme $X\subseteq V$ di stazioni di noleggio, si vuole trovare il cammino di costo minimo da $s$ a $t$ che prevede un cambio di mezzo in esattamente una stazione $x\in X$: il tratto $s\to x$ è percorso in bici (costi su $G$), poi si noleggia un veicolo alla stazione $x$ con costo fisso $\tau_x\ge 0$ e costo proporzionale $\sigma_x>0$ per unità di distanza; il tratto $x\to t$ con il veicolo noleggiato ha quindi costo $\sigma_x\cdot d(x,t)$. Il costo totale passando per $x$ è
> $$c(x)=d(s,x)+\tau_x+\sigma_x\cdot d(x,t).$$
> Trovare $\min_{x\in X}\,c(x)$ in tempo $O(m+n\log n)$.

**Modellazione.** L'obiettivo si fattorizza in tre termini indipendenti:
- $d(s,x)$ per ogni $x\in X$: si ottiene con una singola esecuzione di Dijkstra su $G$ dalla sorgente $s$; l'array $d_s[\cdot]$ contiene le distanze da $s$ verso tutti i nodi.
- $d(x,t)$ per ogni $x\in X$: la distanza da $x$ a $t$ in $G$ coincide con la distanza da $t$ a $x$ nel grafo trasposto $G^T$ (stessi pesi, archi invertiti). Una singola esecuzione di Dijkstra su $G^T$ dalla sorgente $t$ restituisce l'array $d_t[\cdot]$ con $d_t[x]=d_{G^T}(t,x)=d_G(x,t)$.
- $\tau_x$ e $\sigma_x$: dati di input per ogni stazione $x\in X$.

Dopo le due esecuzioni di Dijkstra, una scansione lineare su $X$ calcola $c(x)$ e tiene traccia del minimo. Non occorre costruire alcun grafo aumentato: la struttura del problema si riduce a valutare una formula chiusa su ciascun candidato $x\in X$.

```pseudo
\begin{algorithm}
\caption{MinCostoNoleggio($G$, $s$, $t$, $X$, $\tau$, $\sigma$) → reale}
\begin{algorithmic}
\State $d_s \gets$ \Call{Dijkstra}{$G$, $s$} \Comment{$d_s[v] = d_G(s,v)$ per ogni $v$}
\State $G^T \gets$ \Call{Trasposto}{$G$}
\State $d_t \gets$ \Call{Dijkstra}{$G^T$, $t$} \Comment{$d_t[v] = d_G(v,t)$ per ogni $v$}
\State $\text{opt} \gets +\infty$
\For{ogni $x \in X$}
  \State $c \gets d_s[x] + \tau[x] + \sigma[x] \cdot d_t[x]$
  \If{$c < \text{opt}$}
    \State $\text{opt} \gets c$
  \EndIf
\EndFor
\State \Return $\text{opt}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O((n+m)\log n)$ per ciascuna delle due esecuzioni di Dijkstra (con heap binario) su $G$ e $G^T$, entrambi con $n$ nodi e $m$ archi; $O(n)$ per costruire $G^T$; $O(|X|)\subseteq O(n)$ per la scansione finale. Totale: $O(m+n\log n)$.
**Trappola:** $d_t[x]$ si calcola con Dijkstra da $t$ su $G^T$, non con $|X|$ esecuzioni separate di Dijkstra su $G$ — quello porterebbe a $O(|X|\cdot(m+n\log n))$. Occorre trasporre TUTTI gli archi di $G$, non solo quelli incidenti ai nodi di $X$. Nel caso di Dijkstra multi-sorgente (variante con più stazioni di partenza aggregate), ogni sorgente $m\in X$ va inizializzata con la sua distanza $d_s[m]$ nella coda con priorità, non con $0$: inizializzare con $0$ equivale a ignorare il tratto $s\to m$ e produce distanze errate.
