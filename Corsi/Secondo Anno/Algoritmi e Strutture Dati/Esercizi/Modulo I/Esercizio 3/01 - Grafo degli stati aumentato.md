---
tags:
  - algoritmi
---
# Grafo degli stati aumentato
Esercizio 3 (Modellazione) — pattern [[Casistiche d'Esame Modulo I]], checklist [[Piano Esame ASD - Modulo I]]; ripasso: [[08 - Grafi e Visite]], [[10 - Cammini Minimi e Dijkstra]], [[07 - Code con Priorità e Heap]], [[05 - Strutture Dati Elementari e Dizionari]].

> [!question] Traccia — 16/07/2024
> Dato un grafo orientato $G=(V,E)$ con $n$ nodi e $m$ archi, a ogni arco $e$ è associata un'etichetta temporale $\lambda(e)\in\{1,\ldots,5\}$ che indica l'unico istante in cui quell'arco può essere percorso. Si vuole trovare il cammino da $s$ a $t$ con il minimo numero di archi tale che le etichette degli archi attraversati siano non decrescenti; un vertice può essere visitato più volte e si può restare fermi in attesa dell'istante opportuno.

**Modellazione.** La posizione da sola non distingue due cammini che raggiungono lo stesso nodo a "hop" diversi con timestamp correnti diversi. Lo **stato** rilevante è la coppia $(v,\tau)$ = nodo corrente + istante corrente.
Si costruisce il **grafo espanso** $G'=(V',E')$:
- **Nodi:** $(v,\tau)$ per ogni $v\in V$, $\tau\in\{1,\ldots,5\}$; dimensione $|V'|=5n$.
- **Archi di attesa:** $((v,\tau),(v,\tau+1))$ per ogni $v\in V$, $\tau\in\{1,\ldots,4\}$; sono $4n$ archi e modellano la sosta in loco con avanzamento del clock.
- **Archi temporali:** $((u,\tau),(v,\tau))$ per ogni $(u,v)\in E$ con $\lambda(u,v)=\tau$; sono $m$ archi e corrispondono ai passi reali nel grafo originale.
- **Dimensione totale:** $|E'|=4n+m=O(n+m)$.

Tutti gli archi di $G'$ hanno peso uniforme, quindi si usa **BFS** da $(s,1)$. La risposta è $\min_{\tau\in\{1,\ldots,5\}} d_{G'}[(s,1),(t,\tau)]$.

```pseudo
\begin{algorithm}
\caption{CamminoTemporale($G$, $\lambda$, $s$, $t$) → distanza minima}
\begin{algorithmic}
\Comment{Costruzione di $G'=(V',E')$}
\State $V' \gets \{(v,\tau) : v\in V,\ \tau\in\{1,\ldots,5\}\}$
\State $E' \gets \emptyset$
\For{ogni $v\in V$ e ogni $\tau\in\{1,\ldots,4\}$}
  \State $E' \gets E' \cup \{((v,\tau),(v,\tau+1))\}$ \Comment{arco di attesa}
\EndFor
\For{ogni arco $(u,v)\in E$}
  \State $\tau \gets \lambda(u,v)$
  \State $E' \gets E' \cup \{((u,\tau),(v,\tau))\}$ \Comment{arco temporale}
\EndFor
\State $d \gets$ \Call{BFS}{$G'$, $(s,1)$}
\State $\textit{ans} \gets +\infty$
\For{$\tau = 1$ \To $5$}
  \If{$d[(t,\tau)] < \textit{ans}$}
    \State $\textit{ans} \gets d[(t,\tau)]$
  \EndIf
\EndFor
\State \Return $\textit{ans}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n+m)$ per la costruzione di $G'$ ($|V'|=5n$, $|E'|=O(n+m)$) e $O(|V'|+|E'|)=O(n+m)$ per la BFS; totale $O(n+m)$.
**Trappola:** omettere gli archi di attesa $((v,\tau),(v,\tau+1))$ rende impossibile aspettare l'istante giusto; la BFS va inizializzata da $(s,1)$ soltanto, non da tutti i $(s,\tau)$, altrimenti si ammettono cammini che partono a timestamp arbitrario.
