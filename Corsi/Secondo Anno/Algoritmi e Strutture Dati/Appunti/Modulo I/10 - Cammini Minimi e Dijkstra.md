# Cammini Minimi e Dijkstra
In molti problemi applicativi — navigazione stradale, instradamento di rete, pianificazione — si vuole trovare il percorso di costo minimo tra due nodi di un grafo pesato. Questa nota studia il **problema dei cammini minimi a singola sorgente** (SSSP, *Single-Source Shortest Path*) su grafi con pesi non negativi, e l'**algoritmo di Dijkstra** che lo risolve con un approccio greedy. Prerequisiti: [[08 - Grafi e Visite]] (definizioni, BFS, rappresentazioni), [[07 - Code con Priorità e Heap]] (heap binario, heap di Fibonacci, operazione `decreaseKey`) e [[02 - Notazioni Asintotiche]] (notazione $O$, $\Theta$, $\Omega$).
## Definizioni fondamentali
> [!quote] Definizione — Costo di un cammino
> Sia $G = (V, E, w)$ un grafo orientato o non orientato con pesi $w$ reali sugli archi. Il **costo** (o **lunghezza**) di un cammino $\pi = \langle v_0, v_1, \ldots, v_k \rangle$ è:
> $$w(\pi) = \sum_{i=1}^{k} w(v_{i-1}, v_i)$$

> [!quote] Definizione — Cammino minimo e distanza
> Un **cammino minimo** tra $x$ e $y$ è un cammino di costo minore o uguale a quello di ogni altro cammino tra gli stessi vertici. La **distanza** $d_G(u, v)$ da $u$ a $v$ in $G$ è il costo di un qualsiasi cammino minimo da $u$ a $v$. Il cammino minimo non è necessariamente unico.

Attenzione: la distanza non è sempre finita o ben definita.

- Se non esiste nessun cammino da $u$ a $v$: $d(u, v) = +\infty$.
- Se esiste un cammino che percorre un **ciclo di costo negativo** raggiungibile da $u$ verso $v$: $d(u, v) = -\infty$.

> [!info] Osservazione — Pesi negativi e cicli
> Se $G$ non contiene cicli negativi, i cammini minimi sono sempre **cammini semplici** (senza nodi ripetuti). Con pesi non negativi i cicli non possono mai abbreviare un cammino, quindi Dijkstra funziona correttamente; con pesi negativi ma senza cicli negativi serve invece l'algoritmo di Bellman-Ford (fuori programma).
### Proprietà strutturali dei cammini minimi
> [!quote] Proprietà — Sottostruttura ottima
> Ogni **sottocammino** di un cammino minimo è a sua volta un cammino minimo.

**Dimostrazione (cut & paste).** Sia $\pi = \langle u, \ldots, x, \ldots, y, \ldots, v \rangle$ un cammino minimo da $u$ a $v$, e sia $\pi_{xy}$ il sottocammino da $x$ a $y$. Se esistesse un cammino $\pi'_{xy}$ con $w(\pi'_{xy}) < w(\pi_{xy})$, sostituendo $\pi_{xy}$ con $\pi'_{xy}$ in $\pi$ si otterrebbe un cammino da $u$ a $v$ più corto di $\pi$: contraddizione. $\square$

> [!quote] Proprietà — Disuguaglianza triangolare
> Per ogni $u, v, x \in V$ vale:
> $$d(u, v) \leq d(u, x) + d(x, v)$$

Il cammino che passa per $x$ è un cammino nel grafo, quindi il suo costo è almeno il costo del cammino minimo da $u$ a $v$.
## Il problema SSSP e l'albero dei cammini minimi
> [!quote] Definizione — Problema SSSP
> Dato $G = (V, E, w)$ e una sorgente $s \in V$, il problema SSSP ha due varianti equivalenti:
> 1. Calcolare $d_G(s, v)$ per ogni $v \in V$ (le **distanze** da $s$).
> 2. Calcolare un **albero dei cammini minimi** (Shortest Path Tree, SPT) di $G$ radicato in $s$.

> [!quote] Definizione — Albero dei cammini minimi (SPT)
> $T$ è un albero dei cammini minimi con sorgente $s$ di $G = (V, E, w)$ se:
> - $T$ è un albero radicato in $s$.
> - Per ogni $v \in V$ vale $d_T(s, v) = d_G(s, v)$: la distanza di $v$ da $s$ nell'albero $T$ coincide con la distanza nel grafo $G$.

Le due varianti del problema sono **essenzialmente equivalenti**: dall'SPT si ricavano le distanze in tempo lineare scorrendo l'albero; dalle distanze si costruisce l'SPT in tempo lineare scegliendo, per ogni nodo $v \neq s$, un arco $(u, v)$ tale che $d(s, u) + w(u, v) = d(s, v)$.

> [!info] Caso non pesato
> Per grafi non pesati, l'SPT radicato in $s$ coincide con l'**albero BFS** radicato in $s$ (vedi [[08 - Grafi e Visite]]).
## Algoritmo di Dijkstra
L'algoritmo di **Dijkstra** (1959) risolve il problema SSSP su grafi con **pesi non negativi** ($w(u, v) \geq 0$ per ogni arco) usando un approccio **greedy**.
### Idea intuitiva
L'intuizione fisica è quella di pompare acqua nella sorgente $s$ su un grafo in cui gli archi sono tubi di lunghezza proporzionale al peso. L'acqua scorre a velocità costante: il primo nodo raggiunto ha la distanza minima da $s$, poi il secondo, e così via. L'algoritmo simula esattamente questo processo: scopre i nodi in ordine di distanza crescente da $s$.
### Approccio greedy: stima e rilassamento
> [!quote] Definizione — Operazione di rilassamento
> Dato un arco $(u, v)$ con peso $w(u, v)$, il **rilassamento** dell'arco aggiorna la stima $D_{sv}$ del nodo $v$ se il cammino passante per $u$ è più corto:
> $$\text{se } D_{su} + w(u, v) < D_{sv} \text{ allora } D_{sv} \leftarrow D_{su} + w(u, v)$$

L'algoritmo mantiene le seguenti strutture:
- $D_{sv}$: **stima per eccesso** della distanza $d(s, v)$ per ogni nodo $v$. Inizialmente $D_{ss} = 0$ e $D_{sv} = +\infty$ per $v \neq s$.
- $X \subseteq V$: insieme dei nodi per cui la stima è **definitivamente esatta**. Inizialmente $X = \{s\}$.
- $T$: **albero dei cammini minimi** costruito incrementalmente verso i nodi in $X$. Inizialmente senza archi.
- Una **[[07 - Code con Priorità e Heap|coda con priorità]]** (min-heap) contenente i nodi di $V \setminus X$ scoperti, con priorità pari alla loro stima corrente $D_{sv}$.

Ad ogni passo:
1. Si estrae dalla coda il nodo $u \notin X$ con stima minima: questo nodo viene aggiunto a $X$ e il suo arco "arancione" viene aggiunto a $T$.
2. Per ogni vicino $v$ di $u$ con $(u, v) \in E$, si **rilassa** l'arco $(u, v)$: se $D_{su} + w(u, v) < D_{sv}$, si aggiorna $D_{sv}$ e si aggiorna (o inserisce) $v$ nella coda.

La stima di un nodo $y \in V \setminus X$ nella coda è:
$$D_{sy} = \min\{D_{sx} + w(x, y) : (x, y) \in E,\ x \in X\}$$
L'arco $(x, y)$ che fornisce il minimo è l'arco "arancione" di $y$, cioè il candidato a entrare in $T$ per portare $y$ nell'albero.
### Pseudocodice
**Dijkstra(grafo $G$, nodo $s$) $\to$ albero $T$**

```text
1.  for each nodo v in G do
2.      v.dist = +inf
3.  s.dist = 0
4.  T = albero con radice s (senza archi)
5.  X = insieme vuoto
6.  CP = nuova CodaConPriorità
7.  CP.insert(s, 0)
8.  while not CP.isEmpty() do
9.      u = CP.deleteMin()
10.     X = X ∪ {u}
11.     for each arco (u,v) in G do
12.         if v.dist == +inf then
13.             v.dist = u.dist + w(u, v)
14.             CP.insert(v, v.dist)
15.             rendi u padre di v in T
16.         else if u.dist + w(u,v) < v.dist then
17.             CP.decreaseKey(v, u.dist + w(u,v))
18.             v.dist = u.dist + w(u, v)
19.             rendi u nuovo padre di v in T
20. return T
```

> [!info] Nota sull'implementazione — puntatore per decreaseKey
> L'operazione `decreaseKey` sugli heap richiede un **puntatore diretto** all'elemento nella coda. Si mantiene semplicemente un array di puntatori indicizzato per nodo: durante l'`insert` del nodo $v$ si memorizza il puntatore all'elemento nella coda, così `decreaseKey` è immediatamente localizzabile.

> [!example] Esecuzione su un grafo di esempio
> Si consideri il grafo orientato con nodi $\{s, A, B, C, D, E\}$ dal corso (slide 37–53):
>
> | Passo | Nodo estratto | $D_{sB}$ | $D_{sA}$ | $D_{sC}$ | $D_{sD}$ | $D_{sE}$ |
> |---|---|---|---|---|---|---|
> | Inizio | — | $+\infty$ | $+\infty$ | $+\infty$ | $+\infty$ | $+\infty$ |
> | 1 | $s$ (dist=0) | $10$ | $1$ | $3$ | $+\infty$ | $+\infty$ |
> | 2 | $C$ (dist=3) | $7$ | $1$ | — | $+\infty$ | $5$ |
> | 3 | $A$ (dist=1) | $7$ | — | — | $+\infty$ | $5$ |
> | 4 | $E$ (dist=5) | $7$ | — | — | $9$ | — |
> | 5 | $B$ (dist=7) | — | — | — | $9$ | — |
> | 6 | $D$ (dist=9) | — | — | — | — | — |
>
> Le distanze finali da $s$ sono: $d(s,A)=1$, $d(s,B)=7$, $d(s,C)=3$, $d(s,D)=9$, $d(s,E)=5$.
## Correttezza
La correttezza si basa sul seguente lemma, dimostrato per assurdo.

> [!quote] Lemma — Correttezza dell'estrazione
> Quando un nodo $v$ viene estratto dalla coda con priorità, vale:
> 1. $D_{sv} = d(s, v)$ (la stima è esatta).
> 2. Il cammino da $s$ a $v$ nell'albero $T$ corrente ha costo $d(s, v)$ (è un cammino minimo in $G$).

**Dimostrazione (per assurdo).** Sia $v$ il **primo** nodo per cui l'algoritmo sbaglia, e sia $(u, v)$ l'arco aggiunto a $T$ quando $v$ viene estratto, con $D_{su} = d(s, u)$ (per ipotesi, $u$ non è stato sbagliato). Supponiamo esista un cammino $\pi^*$ da $s$ a $v$ con $w(\pi^*) < D_{su} + w(u, v)$.

Sia $(x, y)$ il primo arco di $\pi^*$ tale che $x \in X$ e $y \notin X$ (tale arco esiste perché $s \in X$ e $v \notin X$). Poiché $x \in X$ per ipotesi $D_{sx} = d(s, x)$, e poiché i pesi sono **non negativi**, il sotto-cammino da $y$ a $v$ ha costo $\geq 0$, quindi:
$$D_{sy} \leq d(s, x) + w(x, y) \leq w(\pi^*) < D_{su} + w(u, v) = D_{sv}$$
Ma allora $D_{sy} < D_{sv}$, e l'algoritmo avrebbe estratto $y$ prima di $v$ (o $v$ avrebbe avuto stima più piccola): contraddizione con l'ipotesi che $v$ sia estratto con stima $D_{sv}$. $\square$

> [!warning] Perché Dijkstra non funziona con pesi negativi
> Con un arco di peso negativo, dopo che un nodo $v$ è stato estratto dalla coda (e si suppone $D_{sv}$ definitivo), potrebbe esistere un cammino più corto che passa per un nodo ancora non estratto e poi percorre l'arco negativo verso $v$. La garanzia "pesi non negativi $\Rightarrow$ costo residuo $\geq 0$" che regge la dimostrazione sopra viene meno, e l'algoritmo può restituire distanze errate.
## Analisi della complessità
Escluse le operazioni sulla coda con priorità, il corpo dell'algoritmo visita ogni arco al più una volta (scansione delle liste di adiacenza) e ogni nodo al più una volta: il costo è $O(n + m)$.

Le operazioni sulla coda con priorità determinano la complessità totale. Con $n$ nodi tutti connessi a $s$ si eseguono:
- $n$ **insert** (una per nodo),
- $n$ **deleteMin** (una per nodo estratto),
- al più $m$ **decreaseKey** (una per ogni arco rilassato).

La tabella seguente riassume i costi per le principali implementazioni della [[07 - Code con Priorità e Heap|coda con priorità]]:

| Struttura | insert | deleteMin | decreaseKey | Totale Dijkstra |
|---|---|---|---|---|
| Array non ordinato | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| Array ordinato | $O(n)$ | $O(1)$ | $O(n)$ | $O(m \cdot n)$ |
| Lista non ordinata | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| Lista ordinata | $O(n)$ | $O(1)$ | $O(n)$ | $O(m \cdot n)$ |
| **Heap binario** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m \log n)$ |
| Heap binomiale | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m \log n)$ |
| **[[07 - Code con Priorità e Heap\|Heap di Fibonacci]]** | $O(1)^*$ | $O(\log n)^*$ | $O(1)^*$ | $O(m + n \log n)$ |

$^*$ costo ammortizzato.

Il calcolo esplicito con heap binario:
$$n \cdot O(\log n) + n \cdot O(\log n) + m \cdot O(\log n) = O(m \log n)$$

Il calcolo con heap di Fibonacci:
$$n \cdot O(1) + n \cdot O(\log n) + m \cdot O(1) = O(m + n \log n)$$
### Confronto e quando conviene quale struttura
> [!info] Confronto heap binario vs heap di Fibonacci
> - **Heap binario** — complessità $O(m \log n)$. Semplice da implementare. Conveniente su **grafi sparsi** dove $m = O(n)$: si ottiene $O(n \log n)$, uguale all'heap di Fibonacci.
> - **[[07 - Code con Priorità e Heap|Heap di Fibonacci]]** — complessità $O(m + n \log n)$. Più complesso da implementare ma **mai peggiore** dell'heap binario, e **strettamente migliore** su grafi densi. Su grafi densi con $m = \Theta(n^2)$: heap binario dà $O(n^2 \log n)$, heap di Fibonacci dà $O(n^2)$.
> - Per confronto: con un array non ordinato si ottiene $O(n^2)$, che sulle stesse reti dense è **migliore** dell'heap binario ma peggiore dell'heap di Fibonacci.

La scelta pratica dipende dalla densità del grafo:
- $m \ll n^2$ (grafo sparso) $\Rightarrow$ heap binario o Fibonacci equivalenti; heap binario preferito per semplicità.
- $m = \Theta(n^2)$ (grafo denso) $\Rightarrow$ heap di Fibonacci ottimale ($O(n^2)$) oppure array non ordinato ($O(n^2)$, più semplice di Fibonacci).

> [!example] Domanda tipica d'esame
> **D:** Qual è la complessità dell'algoritmo di Dijkstra con heap binario e con heap di Fibonacci? In quale caso conviene l'uno o l'altro?
> **R:** Con **heap binario** la complessità è $O(m \log n)$: si eseguono $n$ insert, $n$ deleteMin e al più $m$ decreaseKey, ciascuna a costo $O(\log n)$. Con **heap di Fibonacci** la complessità è $O(m + n \log n)$: insert e decreaseKey costano $O(1)$ ammortizzato, solo le $n$ deleteMin costano $O(\log n)$ ammortizzato. L'heap di Fibonacci è **mai peggiore** e conveniente su grafi densi ($m = \Theta(n^2)$): in quel caso dà $O(n^2)$ contro $O(n^2 \log n)$ dell'heap binario. Su grafi sparsi ($m = O(n)$) le due strutture sono equivalenti e si preferisce l'heap binario per semplicità implementativa.

> [!example] Domanda tipica d'esame
> **D:** Perché l'algoritmo di Dijkstra non è corretto in presenza di archi con peso negativo?
> **R:** La correttezza di Dijkstra si basa sul fatto che, con pesi non negativi, estrarre il nodo $v$ con stima minima garantisce che il costo residuo di qualunque cammino alternativo sia $\geq 0$, quindi nessun cammino futuro potrà migliorare la stima di $v$. Con un arco di peso negativo questa garanzia cade: un cammino che passa per nodi ancora non estratti e poi percorre un arco negativo verso $v$ potrebbe avere costo inferiore a $D_{sv}$, ma l'algoritmo ha già "chiuso" $v$ restituendo una distanza potenzialmente errata.
