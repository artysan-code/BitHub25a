# Minimum Spanning Tree
Il **Minimum Spanning Tree** (MST), o **albero ricoprente minimo**, è uno dei problemi fondamentali su grafi pesati: dato un grafo connesso non orientato con pesi reali sugli archi, si cerca l'insieme di archi che connette tutti i nodi con costo totale minimo. Il problema è risolvibile in modo efficiente con algoritmi [[01 - Greedy e Interval Scheduling|greedy]], la cui correttezza si basa su due proprietà strutturali — la *cut property* e la *cycle property* — che stabiliscono quali archi possono o non possono appartenere a un MST. Questa nota tratta le definizioni fondamentali, le due proprietà con le relative dimostrazioni, l'algoritmo di Kruskal (basato su [[02 - Union-Find]]) e l'algoritmo di Prim (basato su [[07 - Code con Priorità e Heap]]). Un'applicazione al clustering gerarchico conclude la nota.
## Definizioni
> [!quote] Definizione — Minimum Spanning Tree
> Dato un grafo connesso non orientato $G = (V, E)$ con pesi reali $c_e$ sugli archi, un **albero ricoprente** (*spanning tree*) è un sottoinsieme $T \subseteq E$ tale che $T$ è un albero che connette tutti i vertici di $G$. Un **albero ricoprente minimo** (MST) è uno spanning tree che minimizza il costo totale:
> $$c(T) = \sum_{e \in T} c_e$$

> [!quote] Teorema — Numero di spanning tree (Cayley)
> Il grafo completo $K_n$ ha esattamente $n^{n-2}$ spanning tree distinti.

Il Teorema di Cayley mostra che il numero di spanning tree cresce esponenzialmente in $n$: la ricerca per forza bruta è impraticabile anche per grafi piccoli.
### Unicità dell'MST
L'MST **non è unico** in generale: se esistono archi con lo stesso peso, possono esistere più MST di costo uguale.
> [!quote] Proprietà — Unicità dell'MST
> Se tutti i pesi degli archi di $G$ sono **distinti**, allora l'MST è **unico**.

```
Esempio con pesi uguali (tre spanning tree diversi, stesso costo):

    B              B              B
1       1      1       1      1       1
A   1   C    A   1   C    A   1   C
```

> [!info] Tre algoritmi greedy per l'MST
> Il prof. Gualà presenta tre algoritmi:
> - **Kruskal**: parte da $T = \emptyset$, aggiunge archi in ordine crescente di costo se non formano ciclo.
> - **Reverse-Delete**: parte da $T = E$, rimuove archi in ordine decrescente se non disconnettono $T$.
> - **Prim**: parte da un nodo sorgente $s$, espande l'albero aggiungendo ad ogni passo l'arco di costo minimo che ha un solo estremo in $T$.
>
> Tutti e tre producono un MST; questa nota approfondisce Kruskal e Prim.
## Cicli, tagli e intersezione
Prima di dimostrare la correttezza degli algoritmi, introduciamo i concetti fondamentali di ciclo e taglio.
### Ciclo
> [!quote] Definizione — Ciclo
> Un **ciclo** è un insieme di archi della forma $a$-$b$, $b$-$c$, $\ldots$, $y$-$z$, $z$-$a$.

```
Esempio di ciclo C = {1-2, 2-3, 3-4, 4-5, 5-6, 6-1}:

    2 --- 3
   /       \
  1         4
   \       /
    6 --- 5
          |
          7 --- 8
```
### Taglio e cutset
> [!quote] Definizione — Taglio e cutset
> Un **taglio** (*cut*) è un sottoinsieme di nodi $S \subseteq V$ (equivalentemente, una partizione di $V$ in $S$ e $V \setminus S$). Il **cutset** $D$ associato al taglio $S$ è il sottoinsieme di archi con **esattamente un** estremo in $S$:
> $$D = \{(u,v) \in E : u \in S,\ v \notin S\}$$

```
Esempio con S = {4, 5, 8}:

    2 --- 3
   /       \
  1         4*
   \       /|
    6 --- 5*|
          | |
          7 --- 8*

Cutset D = {5-6, 5-7, 3-4, 3-5, 7-8}   (* = nodi in S)
```
### Intersezione ciclo-cutset
> [!quote] Proprietà — Intersezione ciclo-cutset
> Un ciclo $C$ e un cutset $D$ si intersecano in un **numero pari** di archi (eventualmente zero).

**Idea della dimostrazione.** Percorrendo il ciclo, ogni volta che lo attraversiamo da $S$ a $V \setminus S$ dobbiamo necessariamente rientrare in $S$ prima di completare il giro. Ogni "uscita" corrisponde a un arco del cutset, e ogni "entrata" corrisponde a un altro arco del cutset: le uscite e le entrate si bilanciano, producendo sempre un numero pari. In generale l'intersezione ha $2k$ archi per qualche $k \geq 0$.
## Cut property e Cycle property
Queste due proprietà sono il **cuore della correttezza** degli algoritmi greedy per l'MST.
### Cut property
> [!quote] Proprietà — Cut property (proprietà del taglio)
> Sia $S$ un qualsiasi sottoinsieme di nodi, e sia $e$ l'arco di **costo minimo** con esattamente un estremo in $S$ (l'arco di costo minimo che attraversa il taglio). Allora esiste un MST che **contiene** $e$.

**Dimostrazione (scambio di archi).** Sia $T^*$ un MST che non contiene $e = (u, v)$ con $u \in S$, $v \notin S$.
1. Aggiungendo $e$ a $T^*$ si crea un ciclo $C$.
2. Per la proprietà di intersezione ciclo-cutset, $C$ e il cutset $D$ di $S$ si intersecano in un numero pari $\geq 2$ di archi. Uno di questi è $e$; sia $f \neq e$ un altro arco nell'intersezione (anch'esso con un estremo in $S$ e uno in $V \setminus S$).
3. Costruiamo $T' = T^* \cup \{e\} \setminus \{f\}$: sostituiamo $f$ con $e$. $T'$ è ancora uno spanning tree (abbiamo rimosso un arco dal ciclo).
4. Poiché $e$ è l'arco di costo minimo che attraversa il taglio, $c_e \leq c_f$, quindi $c(T') \leq c(T^*)$.
5. Essendo $T^*$ un MST, $c(T') = c(T^*)$: $T'$ è un MST e contiene $e$. $\square$

```
Visuale dello scambio:

    S          V \ S
    .          .
    . u        .
    .   \  e   .
    .    o---->o  v
    .          .
    .    o---->o     <- f (altro arco del cutset nel ciclo C)
    .          .
    T' = T* + {e} - {f}
```
### Cycle property
> [!quote] Proprietà — Cycle property (proprietà del ciclo)
> Sia $C$ un qualsiasi ciclo in $G$, e sia $f$ l'arco di **costo massimo** in $C$. Allora esiste un MST che **non contiene** $f$.

**Dimostrazione (scambio di archi).** Sia $T^*$ un MST che contiene $f$.
1. Rimuovendo $f$ da $T^*$ si spezza $T^*$ in due componenti, creando un taglio $S$.
2. Per la proprietà di intersezione ciclo-cutset, il ciclo $C$ e il cutset $D$ di $S$ si intersecano in un numero pari $\geq 2$ di archi. Uno di questi è $f$; sia $e \neq f$ un altro arco nell'intersezione.
3. Costruiamo $T' = T^* \cup \{e\} \setminus \{f\}$: sostituiamo $f$ con $e$. $T'$ è ancora uno spanning tree.
4. Poiché $f$ è l'arco di costo massimo in $C$, $c_e \leq c_f$, quindi $c(T') \leq c(T^*)$.
5. Essendo $T^*$ un MST, $c(T') = c(T^*)$: $T'$ è un MST e non contiene $f$. $\square$

> [!example] Domanda tipica d'esame
> **D:** Enuncia la cut property e spiega perché un arco che non è il minimo che attraversa un taglio non può appartenere a *tutti* gli MST.
> **R:** La cut property afferma che l'arco di costo minimo che attraversa un qualsiasi taglio appartiene ad *almeno* un MST. Se invece un arco $f$ non è il minimo che attraversa un taglio (cioè esiste $e$ più economico con gli stessi estremi ai lati del taglio), allora per la cycle property applicata al ciclo che $f$ formerebbe con il cammino attraverso $e$ nell'albero, $f$ è l'arco massimo e può essere escluso: esiste un MST che non lo contiene.
## Algoritmo di Kruskal
L'algoritmo di **Kruskal** (1956) parte da $T = \emptyset$ e aggiunge gli archi uno alla volta in ordine crescente di costo, saltando quelli che formerebbero un ciclo.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Kruskal($G = (V, E, c)$) — restituisce l'MST $T$}
\begin{algorithmic}
\State $T \gets \emptyset$
\ForAll{vertice $v \in V$}
  \State \Call{UF.makeset}{$v$}
\EndFor
\State ordina gli archi $E$ in ordine crescente di costo
\ForAll{arco $(x, y) \in E$ in ordine crescente di costo}
  \State $T_x \gets$ \Call{UF.find}{$x$}
  \State $T_y \gets$ \Call{UF.find}{$y$}
  \If{$T_x \neq T_y$}
    \State \Call{UF.union}{$T_x, T_y$}
    \State aggiungi $(x, y)$ a $T$
  \EndIf
\EndFor
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

La struttura dati [[02 - Union-Find]] mantiene le **[[08 - Grafi e Visite|componenti connesse]]** di $T$ durante l'esecuzione:
- `makeset(v)`: inizializza la componente $\{v\}$.
- `find(x)`: restituisce il rappresentante della componente di $x$.
- `union(Tx, Ty)`: fonde le due componenti.

Il controllo `Tx ≠ Ty` rileva se $x$ e $y$ sono già nella stessa componente (aggiungere l'arco creerebbe un ciclo).
### Esempio di esecuzione
```
Grafo di esempio:
         B               F
    7        21      6

A       14       C  1              E
                           9
    30       10
         D               G

Archi ordinati per costo: (C,E,1), (E,F,6), (A,B,7), (E,G,9), (C,D,10),
                          (A,C,14), (B,C,21), (A,D,30)

Passo 1: (C,E,1)  → {C}∩{E} = ∅ → aggiungi. T={(C,E)}
Passo 2: (E,F,6)  → {C,E}∩{F} = ∅ → aggiungi. T={(C,E),(E,F)}
Passo 3: (A,B,7)  → {A}∩{B} = ∅ → aggiungi. T+={(A,B)}
Passo 4: (E,G,9)  → {C,E,F}∩{G} = ∅ → aggiungi. T+={(E,G)}
Passo 5: (C,D,10) → {C,E,F,G}∩{D} = ∅ → aggiungi. T+={(C,D)}
Passo 6: (A,C,14) → {A,B}∩{C,D,E,F,G} = ∅ → aggiungi (unisce le due componenti).
Passo 7: (B,C,21) → find(B)=find(C) → CICLO, skip.
Passo 8: (A,D,30) → find(A)=find(D) → CICLO, skip.
MST finale: {(C,E),(E,F),(A,B),(E,G),(C,D),(A,C)}, costo = 1+6+7+9+10+14 = 47
```
### Correttezza
La correttezza di Kruskal segue direttamente dalla **cut property** e dalla **cycle property**:
- Quando l'algoritmo **aggiunge** l'arco $(x, y)$: le componenti di $x$ e $y$ sono distinte; sia $S$ la componente di $x$. Tutti gli archi già esaminati (e saltati) avevano costo $\leq c_{xy}$. Dunque $(x, y)$ è l'arco di costo minimo che attraversa il taglio tra $S$ e $V \setminus S$: per la **cut property** appartiene ad un MST.
- Quando l'algoritmo **rifiuta** l'arco $(x, y)$: $x$ e $y$ sono già connessi in $T$, quindi $(x, y)$ forma un ciclo con il cammino esistente. Poiché gli archi sono esaminati in ordine crescente, $(x, y)$ è l'arco di costo massimo in quel ciclo: per la **cycle property** non appartiene ad alcun MST (se i pesi sono distinti).
### Complessità
| Operazione | Costo |
|---|---|
| Ordinamento degli archi | $O(m \log m) = O(m \log n)$ |
| $n$ `makeset` | $O(n)$ |
| $n-1$ `union` | dipende da UF |
| $2m$ `find` | dipende da UF |
| **Totale con QuickFind + union by size** | $O(m \log n + m + n \log n) = O(m \log n)$ |
| **Totale con QuickUnion + union by size** | $O(m \log n + m \log n + n) = O(m \log n)$ |
| **Totale complessivo** | $\mathbf{O(m \log n)}$ |

Nota: $\log m = O(\log n^2) = O(\log n)$ poiché $m \leq \binom{n}{2}$, quindi $O(m \log m) = O(m \log n)$. Per i dettagli sulle implementazioni di Union-Find e le loro complessità, si veda [[02 - Union-Find]].
## Algoritmo di Prim
L'algoritmo di **Prim** (Jarník 1930, Dijkstra 1957, Prim 1959) costruisce l'MST partendo da un nodo sorgente $s$ e crescendo l'albero un arco alla volta, scegliendo sempre l'arco di costo minimo che ha esattamente un estremo nell'albero corrente.
### Idea e correttezza
Ad ogni passo si ha un insieme $S$ di nodi già esplorati (inizialmente $S = \{s\}$). Si aggiunge il **nodo più economico** raggiungibile da $S$, cioè il nodo $v \notin S$ per cui esiste un arco $(u, v)$ con $u \in S$ e $c_{uv}$ minimo tra tutti gli archi del cutset.

**Correttezza:** La cut property applicata all'insieme $S$ garantisce che l'arco scelto a ogni passo appartiene ad almeno un MST. Poiché si usa la cut property esattamente $n-1$ volte (una per ogni arco aggiunto), l'albero finale è un MST.
### Implementazione con coda con priorità
L'implementazione naïve (per $n-1$ volte, scansione lineare di tutti gli archi) costa $O(nm)$. L'implementazione efficiente usa una [[07 - Code con Priorità e Heap|coda con priorità]] (**min-heap**):

Per ogni nodo non ancora esplorato $v$, si mantiene la chiave $a[v]$ = costo del **miglior arco** che collega $v$ a un nodo già in $S$ ($+\infty$ se nessun tale arco esiste).
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Prim($G, s$) — restituisce l'MST $T$ radicato in $s$}
\begin{algorithmic}
\ForAll{vertice $v \in V$}
  \State $a[v] \gets +\infty$
\EndFor
\State $a[s] \gets 0$
\State $Q \gets$ nuova coda con priorità (min-heap)
\ForAll{vertice $v \in V$}
  \State \Call{Q.insert}{$v, a[v]$}
\EndFor
\State $S \gets \emptyset$
\State $T \gets$ albero con radice $s$ (senza archi)
\While{$Q$ non è vuota}
  \State $u \gets$ \Call{Q.deleteMin}{}
  \State $S \gets S \cup \{u\}$
  \ForAll{arco $e = (u, v)$ incidente a $u$}
    \If{$v \notin S$ e $c_e < a[v]$}
      \State rendi $u$ genitore di $v$ in $T$
      \State \Call{Q.decreaseKey}{$v, c_e$}
      \State $a[v] \gets c_e$
    \EndIf
  \EndFor
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

> [!info] Analogia con Dijkstra
> La struttura di Prim è molto simile a quella di [[10 - Cammini Minimi e Dijkstra]]: entrambi usano una coda con priorità e un'operazione `decreaseKey`. La differenza chiave è la **chiave usata**. In Dijkstra la chiave di $v$ è la **distanza totale** da $s$ (costo del cammino da $s$ a $v$); in Prim la chiave di $v$ è il **costo del singolo arco** che collega $v$ all'albero corrente. Prim non cerca il cammino più corto da $s$, ma l'arco di attacco più economico.
### Esempio di esecuzione
```
Grafo (stesso esempio):
         B               F
    7        21      6

s=A     14       C  1         E
                           9
    30       10
         D               G

Passo 1: S={A}. Archi candidati: (A,B,7),(A,C,14),(A,D,30).
         Minimo: (A,B,7). Aggiungi B. T={(A,B)}.
Passo 2: S={A,B}. Candidati: (A,C,14),(A,D,30),(B,C,21).
         Minimo: (A,C,14). Aggiungi C. T={(A,B),(A,C)}.
Passo 3: S={A,B,C}. Candidati: (A,D,30),(C,D,10),(C,E,1).
         Minimo: (C,E,1). Aggiungi E. T+={(C,E)}.
Passo 4: S={A,B,C,E}. Candidati: (A,D,30),(C,D,10),(E,F,6),(E,G,9).
         Minimo: (E,F,6). Aggiungi F. T+={(E,F)}.
Passo 5: S={A,B,C,E,F}. Candidati: (A,D,30),(C,D,10),(E,G,9).
         Minimo: (E,G,9). Aggiungi G. T+={(E,G)}.
Passo 6: S={A,B,C,E,F,G}. Candidati: (A,D,30),(C,D,10).
         Minimo: (C,D,10). Aggiungi D.
MST = {(A,B,7),(A,C,14),(C,E,1),(E,F,6),(E,G,9),(C,D,10)}, costo=47
```

> [!warning] Chiave vs distanza: non confondere Prim con Dijkstra
> In Prim la chiave $a[v]$ rappresenta il costo del **miglior arco singolo** che connette $v$ all'albero — non il costo cumulativo del cammino da $s$ a $v$. Usare la distanza cumulativa al posto della chiave dell'arco produce Dijkstra (cammini minimi), non Prim (MST).
### Complessità
Le operazioni sulla coda con priorità determinano la complessità totale. Si eseguono $n$ insert, $n$ deleteMin, e al più $m$ decreaseKey:

| Struttura per la coda | Insert | DeleteMin | DecreaseKey | Totale Prim |
|---|---|---|---|---|
| Scansione lineare naïve (senza PQ) | — | $O(m)$ per step | — | $O(mn)$ |
| **Array non ordinato** | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| **Heap binario** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m \log n)$ |
| **[[07 - Code con Priorità e Heap\|Heap di Fibonacci]]** | $O(1)$ | $O(\log n)$ | $O(1)$ ammort. | $O(m + n \log n)$ |

Il calcolo con heap binario: $n \cdot O(\log n) + n \cdot O(\log n) + m \cdot O(\log n) = O(m \log n)$.
Il calcolo con heap di Fibonacci: $n \cdot O(1) + n \cdot O(\log n) + m \cdot O(1) = O(m + n \log n)$.
## Riepilogo e confronto degli algoritmi
| Algoritmo | Struttura dati | Complessità | Note |
|---|---|---|---|
| Kruskal | [[02 - Union-Find]] (Union by size) | $O(m \log n)$ | Ottimo su grafi sparsi; ordinamento domina |
| Prim (naïve) | Scansione lineare, senza PQ | $O(mn)$ | Semplice ma inefficiente |
| Prim (array) | Array non ordinato | $O(n^2)$ | Buono su grafi densi ($m=\Theta(n^2)$) |
| Prim (heap binario) | Min-heap binario | $O(m \log n)$ | Bilanciato; buono su grafi sparsi |
| Prim (Fibonacci) | [[07 - Code con Priorità e Heap\|Heap di Fibonacci]] | $O(m + n \log n)$ | Ottimale su grafi densi |

> [!info] Confronto Kruskal vs Prim
> Su grafi **sparsi** ($m = O(n)$) sia Kruskal che Prim con heap binario danno $O(n \log n)$; la scelta è indifferente. Su grafi **densi** ($m = \Theta(n^2)$), Kruskal richiede $O(n^2 \log n)$ (dominato dall'ordinamento), mentre Prim con array non ordinato dà $O(n^2)$ e Prim con heap di Fibonacci dà $O(n^2)$: in questo caso Prim è preferibile.
> Nota teorica: esistono algoritmi asintoticamente migliori — $O(m \log \log n)$ (Cheriton-Tarjan 1976, Yao 1975), $O(m \cdot \alpha(m,n))$ (Fredman-Tarjan 1987), $O(m)$ randomizzato (Karger-Klein-Tarjan 1995) — ma Kruskal e Prim rimangono gli algoritmi standard per il corso.

> [!example] Domanda tipica d'esame
> **D:** Descrivi l'algoritmo di Kruskal, spiega perché è corretto e calcolane la complessità.
> **R:** Kruskal ordina gli archi in senso crescente e li aggiunge a $T$ uno a uno, saltando quelli che formano un ciclo (rilevato tramite Union-Find). La correttezza si basa sulla cut property: quando si aggiunge $(x,y)$, la componente di $x$ forma il taglio $S$; poiché gli archi sono esaminati in ordine crescente, $(x,y)$ è il minimo che attraversa quel taglio, quindi appartiene a un MST. Complessità: $O(m \log n)$ — l'ordinamento domina, le operazioni Union-Find con union by size costano $O(m \log n)$ nel totale.

> [!example] Domanda tipica d'esame
> **D:** Qual è la differenza tra l'algoritmo di Prim e l'algoritmo di Dijkstra?
> **R:** Entrambi usano una coda con priorità e `decreaseKey`. La differenza è nella **chiave**: Dijkstra usa la distanza cumulativa da $s$ (per trovare i cammini minimi); Prim usa il costo del singolo arco di attacco (per trovare l'MST). Prim non produce un albero dei cammini minimi: un nodo distante da $s$ ma connesso all'albero tramite un arco molto economico viene incluso prima di nodi vicini ma raggiungibili solo con archi costosi.
## Applicazione: Clustering di massima spaziatura
Un'applicazione diretta di Kruskal è il **clustering gerarchico per single-linkage**.
> [!quote] Definizione — k-clustering di massima spaziatura
> Dato un insieme $U$ di $n$ oggetti con una funzione distanza $d$ (non negativa, simmetrica, con $d(p_i, p_j) = 0 \Leftrightarrow p_i = p_j$), un **$k$-clustering** è una partizione di $U$ in $k$ gruppi non vuoti. La **spaziatura** (*spacing*) è la minima distanza tra oggetti in cluster diversi. Il problema è trovare il $k$-clustering di **massima spaziatura**.

**Algoritmo (Single-linkage $k$-clustering):** si esegue Kruskal su un grafo completo con pesi pari alle distanze tra oggetti, fermandosi quando si raggiungono esattamente $k$ componenti connesse. Equivalentemente: si costruisce l'MST completo e si eliminano i $k-1$ archi più costosi.

> [!quote] Teorema — Ottimalità del k-clustering per single-linkage
> Il clustering $\mathcal{C}^*$ ottenuto eliminando i $k-1$ archi più costosi dall'MST è un $k$-clustering di **massima spaziatura**.

**Dimostrazione.** Sia $d^*$ la lunghezza del $(k-1)$-esimo arco più costoso dell'MST (cioè la spaziatura di $\mathcal{C}^*$). Sia $\mathcal{C}$ un qualsiasi altro $k$-clustering. Poiché $\mathcal{C}^* \neq \mathcal{C}$, esistono $p_i, p_j$ nello stesso cluster di $\mathcal{C}^*$ (diciamo $C^*_r$) ma in cluster diversi di $\mathcal{C}$. Il cammino da $p_i$ a $p_j$ in $C^*_r$ (nell'MST) attraversa un arco che separa i due cluster di $\mathcal{C}$; tutti gli archi del cammino hanno lunghezza $\leq d^*$ (Kruskal li ha scelti prima del $(k-1)$-esimo taglio). La spaziatura di $\mathcal{C}$ è quindi $\leq d^*$: $\mathcal{C}^*$ ha spaziatura maggiore o uguale a qualsiasi altro $k$-clustering. $\square$

> [!info] Clustering gerarchico
> Eseguendo Kruskal fino alla fine (senza fermarsi a $k$ componenti) si ottiene implicitamente un **clustering gerarchico**: per ogni $k = n, n-1, \ldots, 1$, i cluster sono le componenti connesse dopo aver eliminato i $k-1$ archi più costosi dall'MST. Questo produce un **dendrogramma** — una struttura ad albero che mostra come i cluster si fondono al crescere di $k$.

> [!example] Domanda tipica d'esame
> **D:** Come si usa l'MST per trovare il clustering di massima spaziatura? Perché funziona?
> **R:** Si calcola l'MST del grafo completo sugli oggetti (con pesi = distanze) e si eliminano i $k-1$ archi più costosi. Le $k$ componenti connesse risultanti sono il clustering ottimale. Funziona perché la spaziatura del clustering è la lunghezza del $(k-1)$-esimo arco più costoso dell'MST; qualsiasi altro clustering deve avere due oggetti in cluster diversi collegati da un percorso nell'MST i cui archi hanno tutti lunghezza $\leq$ quella spaziatura, quindi la spaziatura di qualsiasi altro clustering non può superare quella del clustering MST.
