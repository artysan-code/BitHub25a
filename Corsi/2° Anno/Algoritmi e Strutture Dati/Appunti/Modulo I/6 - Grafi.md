> [!abstract] Introduzione ai Grafi
> Un **grafo** è una struttura dati non lineare utilizzata per rappresentare relazioni tra coppie di oggetti. È composto da un insieme di nodi (o vertici) e un insieme di collegamenti (archi).

### Definizioni Fondamentali
> [!definition] Grafo Non Orientato (Undirected Graph)
> Un grafo $G = (V, E)$ dove:
> - $V$ è un insieme di **vertici** (nodi).
> - $E$ è un insieme di **archi** (coppie non ordinate di vertici).
> Se $(u, v) \in E$, allora l'arco collega $u$ e $v$ in entrambe le direzioni.

> [!definition] Grafo Orientato (Directed Graph / Digraph)
> Un grafo $G = (V, E)$ dove $E$ è un insieme di coppie ordinate. L'arco $(u, v)$ ha una direzione da $u$ (coda) a $v$ (testa).

> [!definition] Grafo Pesato
> Un grafo $G = (V, E, w)$ in cui ad ogni arco $e \in E$ è associato un peso $w(e)$ (solitamente un numero reale).

### Rappresentazioni in Memoria
> [!info] Scelta della Struttura
> La scelta dipende dalla densità del grafo ($m$ archi rispetto a $n$ nodi). In generale, $m$ può variare da $0$ a $n^2$.

#### 1. Matrice di Adiacenza
Un array bidimensionale $A$ di dimensione $n \times n$ dove $A[i][j] = 1$ se esiste un arco tra $i$ e $j$, $0$ altrimenti.
- **Spazio:** $\Theta(n^2)$
- **Verifica arco $(u, v)$:** $O(1)$
- **Elenco adiacenti di $u$:** $\Theta(n)$
- **Ideale per:** Grafi densi ($m \approx n^2$).

#### 2. Liste di Adiacenza
Un array di $n$ liste, dove la lista $i$ contiene tutti i nodi $j$ tali che $(i, j) \in E$.
- **Spazio:** $\Theta(n + m)$
- **Verifica arco $(u, v)$:** $O(grado(u))$
- **Elenco adiacenti di $u$:** $\Theta(grado(u))$
- **Ideale per:** Grafi sparsi ($m \ll n^2$).

### Algoritmi di Visita
> [!abstract] Scopo della Visita
> Esaminare i nodi e gli archi in modo sistematico, partendo da un nodo sorgente $s$.

#### Visita in Ampiezza (BFS - Breadth-First Search)
Esplora il grafo "a livelli": prima i vicini di $s$, poi i vicini dei vicini, e così via.
- **Struttura dati:** Coda (FIFO).
- **Proprietà:** Trova i **cammini minimi** (numero minimo di archi) da $s$ a ogni altro nodo in grafi non pesati.
- **Complessità:** $O(n + m)$ con liste di adiacenza.

#### Visita in Profondità (DFS - Depth-First Search)
Esplora il grafo andando il più lontano possibile lungo ogni ramo prima di tornare indietro (backtracking).
- **Struttura dati:** Pila (LIFO) o Ricorsione.
- **Timestamp:** Per ogni nodo $v$ si salvano il tempo di inizio visita ($d[v]$) e fine visita ($f[v]$).
- **Complessità:** $O(n + m)$.

### Applicazioni della DFS
> [!success] Risultati dell'analisi DFS
> 1. **Rilevamento Cicli:** In un grafo orientato, esiste un ciclo se e solo se la DFS trova un "arco all'indietro" (verso un antenato ancora in visita).
> 2. **Ordinamento Topologico:** Per un DAG (Grafo Orientato Aciclico), è un ordinamento dei nodi tale che se esiste $(u, v)$, $u$ appare prima di $v$. Si ottiene ordinando i nodi per tempo di fine visita $f[v]$ decrescente.
> 3. **Componenti Fortemente Connesse (SCC):** Sottoinsiemi di nodi in cui ogni nodo è raggiungibile da ogni altro (Algoritmo di Kosaraju o Tarjan).

### Cammini Minimi su Grafi Pesati
> [!definition] Algoritmo di Dijkstra
> Risolve il problema del cammino minimo da una sorgente singola $s$ in grafi con **pesi non negativi**.
> - **Tecnica:** Greedy.
> - **Funzionamento:** Mantiene una stima della distanza $d[v]$ e usa una **Coda con Priorità** per estrarre il nodo con distanza minima non ancora visitato.
> - **Rilassamento:** Se $d[u] + w(u, v) < d[v]$, allora $d[v] = d[u] + w(u, v)$.
> - **Complessità:** $O(m + n \log n)$ usando Heap di Fibonacci.
