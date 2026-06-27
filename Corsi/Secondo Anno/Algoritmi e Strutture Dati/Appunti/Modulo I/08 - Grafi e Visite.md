---
tags:
  - algoritmi
  - grafi
slide: "11-12"
---
# Grafi e Visite
I **grafi** sono strutture dati non lineari che modellano relazioni tra oggetti: reti stradali, social network, dipendenze tra moduli software, cammini minimi su mappe. Introdotti storicamente da Eulero nel 1736 per risolvere il celebre problema dei sette ponti di Königsberg, sono oggi uno strumento fondamentale per descrivere e risolvere problemi algoritmici. Questa nota copre le definizioni essenziali, le due principali rappresentazioni in memoria e i due algoritmi di visita — BFS e DFS; le applicazioni avanzate della DFS (tempi pre/post, classificazione degli archi, ordinamento topologico, componenti fortemente connesse) sono trattate in [[09 - Applicazioni della DFS]], mentre i cammini minimi su grafi pesati sono in [[10 - Cammini Minimi e Dijkstra]]. Le complessità sono espresse con la notazione asintotica di [[02 - Notazioni Asintotiche]].
## Definizioni fondamentali
> [!quote] Definizione — Grafo non orientato
> Un **grafo non orientato** $G = (V, E)$ consiste in:
> - un insieme $V$ di **vertici** (o nodi);
> - un insieme $E$ di coppie **non ordinate** di vertici, detti **archi**.

> [!quote] Definizione — Grafo orientato (diretto)
> Un **grafo orientato** (o **diretto**) $D = (V, A)$ consiste in:
> - un insieme $V$ di **vertici** (o nodi);
> - un insieme $A$ di coppie **ordinate** di vertici, detti **archi diretti**.
> L'arco $(u, v)$ è **uscente** da $u$ ed **entrante** in $v$.

> [!quote] Definizione — Grafo pesato
> Un **grafo pesato** $G = (V, E, w)$ è un grafo in cui ad ogni arco $e \in E$ è associato un valore numerico (di solito reale) definito dalla **funzione peso** $w: E \to \mathbb{R}$.

Useremo le seguenti notazioni standard per tutto il corso:
- $n = |V|$ — numero di vertici;
- $m = |E|$ — numero di archi;
- due nodi $u, v$ con $(u,v) \in E$ si dicono **adiacenti** (o vicini);
- l'arco $(u,v)$ è **incidente** a $u$ e $v$, detti suoi **estremi**.
### Grado dei nodi
> [!quote] Definizione — Grado (grafo non orientato)
> Il **grado** $\delta(u)$ di un nodo $u$ in un grafo non orientato è il numero di archi incidenti a $u$. Il **grado del grafo** è $\max_{v \in V}\{\delta(v)\}$.

> [!quote] Definizione — Grado entrante e uscente (grafo orientato)
> In un grafo orientato, il **grado uscente** $\delta_{out}(u)$ è il numero di archi uscenti da $u$; il **grado entrante** $\delta_{in}(u)$ è il numero di archi entranti in $u$.

> [!quote] Proprietà — Somma dei gradi
> In ogni grafo non orientato:
> $$\sum_{v \in V} \delta(v) = 2m$$
> In ogni grafo orientato:
> $$\sum_{v \in V} \delta_{out}(v) = \sum_{v \in V} \delta_{in}(v) = m$$
> Corollario: in ogni grafo non orientato il numero di nodi di **grado dispari è pari**.

> [!question] Domanda tipica d'esame
> - **D:** Perché in un grafo non orientato la somma dei gradi vale $2m$? **R:** Ogni arco $(u,v)$ contribuisce $+1$ al grado di $u$ e $+1$ al grado di $v$, quindi viene contato due volte nella somma.
### Cammini, cicli e connessione
> [!quote] Definizione — Cammino, lunghezza, distanza
> Un **cammino** è una sequenza di nodi $v_0, v_1, \ldots, v_k$ tale che per ogni $i$ l'arco $(v_i, v_{i+1}) \in E$. La **lunghezza** del cammino è il numero di archi $k$. La **distanza** $\mathrm{dist}(u, v)$ è la lunghezza del cammino più corto tra $u$ e $v$. In un grafo orientato il cammino deve rispettare il verso degli archi.

> [!quote] Definizione — Ciclo, connessione, diametro
> Un **ciclo** è un cammino chiuso, ovvero da un vertice a se stesso. Un grafo è **connesso** se esiste un cammino per ogni coppia di vertici. Il **diametro** è la massima distanza tra due nodi: $\max_{u,v \in V} \mathrm{dist}(u,v)$; il diametro di un grafo non connesso è $\infty$.

> [!quote] Definizione — DAG
> Un **DAG** (Directed Acyclic Graph) è un grafo orientato **privo di cicli**. È la struttura tipica per modellare dipendenze tra compiti (es. propedeuticità tra esami, moduli software).
### Grafi particolari
Il **grafo totalmente sconnesso** ha $V \neq \emptyset$ e $E = \emptyset$. Il **grafo completo** $K_n$ ha un arco tra ogni coppia di nodi, con $m = \frac{n(n-1)}{2}$. In generale, un grafo senza cappi né archi paralleli ha:
$$0 \leq m \leq \frac{n(n-1)}{2} = \Theta(n^2)$$
### Alberi come grafi
> [!quote] Definizione — Albero (come grafo)
> Un **albero** è un grafo connesso e aciclico.

> [!quote] Teorema — Archi di un albero
> Sia $T = (V, E)$ un albero; allora $|E| = |V| - 1$.

**Dimostrazione** per induzione su $|V|$:
- *Caso base*: $|V| = 1 \Rightarrow |E| = 0 = |V| - 1$. ✓
- *Caso induttivo*: $|V| > 1$. Poiché $T$ è connesso e aciclico ha almeno una **foglia** (nodo di grado 1; se tutti avessero grado $\geq 2$ ci sarebbe un ciclo). Rimuovendo la foglia si ottiene un albero con $n-1$ nodi che, per ipotesi induttiva, ha $n-2$ archi. Quindi $T$ ha $n-1$ archi. ✓

Per un grafo connesso con $n$ nodi e $m$ archi vale quindi $n - 1 \leq m \leq \frac{n(n-1)}{2}$, cioè $m = \Omega(n)$ e $m = O(n^2)$.

> [!info] Attenzione: $m \geq n-1$ non implica connessione
> Se un grafo ha $m \geq n - 1$ archi, **non è detto** che sia connesso. Per garantire la connessione servono almeno $\binom{n-1}{2} + 1$ archi (i.e. un grafo completo su $n-1$ nodi più un nodo isolato ha $\frac{(n-1)(n-2)}{2}$ archi ma è sconnesso).
## Rappresentazioni in memoria
Dati $n = |V|$ e $m = |E|$, esistono due rappresentazioni standard per un grafo.
### Matrice di adiacenza
Un array bidimensionale $A[n][n]$ dove:
$$A[i][j] = \begin{cases} 1 & \text{se } (i,j) \in E \\ 0 & \text{altrimenti} \end{cases}$$
Per grafi non orientati la matrice è simmetrica; per grafi pesati si sostituisce $1$ con $w(i,j)$.
### Liste di adiacenza
Un array di $n$ liste, dove la lista del nodo $u$ contiene tutti i nodi $v$ adiacenti a $u$. Per grafi non orientati ogni arco compare in due liste; per grafi orientati solo nella lista del nodo uscente.
### Confronto spazio/tempo
| Operazione | Matrice di adiacenza | Liste di adiacenza |
|---|---|---|
| Spazio | $O(n^2)$ | $O(n + m)$ |
| Verifica $(u,v) \in E$? (non orientato) | $O(1)$ | $O(\min\{\delta(u), \delta(v)\})$ |
| Verifica $(u,v) \in E$? (orientato) | $O(1)$ | $O(\delta(u))$ |
| Elenco archi uscenti da $u$ | $O(n)$ | $O(\delta(u))$ |

> [!info] Quale rappresentazione scegliere?
> La scelta dipende dalla **densità** del grafo. Per **grafi densi** ($m \approx n^2$) le due rappresentazioni hanno costo simile e la matrice garantisce lookup $O(1)$. Per **grafi sparsi** ($m \ll n^2$, il caso più comune nelle applicazioni reali) le liste di adiacenza sono sia più efficienti in spazio sia più veloci per iterare sui vicini. La maggior parte degli algoritmi di visita assume liste di adiacenza.

> [!question] Domanda tipica d'esame
> - **D:** Quando conviene usare liste di adiacenza invece della matrice di adiacenza? **R:** Quando il grafo è **sparso** ($m = o(n^2)$): le liste occupano $O(n+m)$ invece di $O(n^2)$ e la visita dei vicini è $O(\delta(u))$ invece di $O(n)$, rendendo algoritmi come BFS e DFS più efficienti.
## Visita in ampiezza — BFS
Una **visita** di un grafo permette di esaminare sistematicamente nodi e archi a partire da una **sorgente** $s$. La **BFS** (Breadth-First Search, visita in ampiezza) esplora il grafo "a livelli": prima tutti i vicini di $s$ a distanza 1, poi quelli a distanza 2, e così via. Utilizza una **coda** (struttura FIFO, si veda [[05 - Strutture Dati Elementari e Dizionari]]) per tenere traccia dei nodi da visitare.
### Obiettivo e idea
Dato un grafo $G$ (non pesato) e un nodo sorgente $s$, la BFS trova le **distanze minime** (in numero di archi) da $s$ a ogni altro nodo raggiungibile.

L'idea di base: appena si scopre un nuovo nodo $v$ visitando un arco $(u, v)$, si sa che $\mathrm{dist}(s, v) = \mathrm{dist}(s, u) + 1$. Tenendo in coda i nodi nell'ordine di scoperta si garantisce che i nodi a distanza $k$ siano visitati prima di quelli a distanza $k+1$.
### Pseudocodice BFS
```pseudo
\begin{algorithm}
\caption{visitaBFS($s$) — visita BFS da sorgente $s$, restituisce l'albero $T$}
\begin{algorithmic}
\State rendi tutti i nodi non marcati
\State sia $T$ un albero con unico nodo $s$
\State sia $F$ una coda vuota
\State marca il vertice $s$, poni $\mathrm{dist}(s) \gets 0$
\State \Call{F.enqueue}{$s$}
\While{$F$ non è vuota}
  \State $u \gets$ \Call{F.dequeue}{}
  \ForAll{arco $(u, v) \in G$}
    \If{$v$ non è marcato}
      \State marca $v$
      \State $\mathrm{dist}(v) \gets \mathrm{dist}(u) + 1$
      \State rendi $u$ padre di $v$ in $T$
      \State \Call{F.enqueue}{$v$}
    \EndIf
  \EndFor
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

L'albero $T$ restituito si chiama **albero BFS** (o albero dei cammini minimi) radicato in $s$.

> [!example] Esempio — visita BFS
> Partendo dal nodo $s$, si visitano nell'ordine: prima i vicini diretti di $s$ (distanza 1), poi i vicini dei vicini non ancora marcati (distanza 2), e così via. Se $s$ ha vicini $A$ e $C$, e $A$ ha vicini $D$ (già a distanza 1 da $s$ tramite $C$), la coda assegna $\mathrm{dist}(D)$ correttamente alla prima volta che $D$ viene incontrato.
### Complessità della BFS
> [!quote] Teorema — Correttezza della BFS
> Per ogni nodo $v$, il livello di $v$ nell'albero BFS è pari alla **distanza** di $v$ dalla sorgente $s$ (vale sia per grafi orientati che non orientati).

| Rappresentazione | Complessità temporale |
|---|---|
| Liste di adiacenza | $O(n + m)$ |
| Matrice di adiacenza | $O(n^2)$ |

Con liste di adiacenza: il ciclo esterno considera ogni nodo al più una volta ($O(n)$ dequeue totali); per ciascun nodo $u$ si scorrono i suoi $\delta(u)$ vicini; la somma totale di tutte le iterazioni del ciclo interno è $\sum_{u \in V} \delta(u) = 2m$ (non orientato) o $m$ (orientato), per un totale $O(n + m)$.

> [!info] Osservazioni sulla complessità
> 1. Se il grafo è connesso, $m \geq n - 1$ e quindi $O(n + m) = O(m)$.
> 2. Poiché $m \leq \frac{n(n-1)}{2}$, si ha $O(n + m) = O(n^2)$ nel caso peggiore (grafo denso).
> 3. Per $m = o(n^2)$ (grafo sparso), le liste di adiacenza sono asintoticamente più efficienti della matrice.

> [!question] Domanda tipica d'esame
> - **D:** Qual è la complessità della BFS e da cosa dipende? **R:** Dipende dalla struttura dati usata: $O(n + m)$ con **liste di adiacenza** (ottimale per grafi sparsi), $O(n^2)$ con **matrice di adiacenza**. Il termine $n$ viene dai nodi estratti dalla coda; il termine $m$ dall'esplorazione di tutti gli archi.
> - **D:** Cosa garantisce la BFS sui cammini? **R:** La BFS trova il **cammino minimo in numero di archi** da $s$ a ogni nodo raggiungibile. Il livello di ogni nodo nell'albero BFS corrisponde esattamente alla sua distanza da $s$.
## Visita in profondità — DFS
La **DFS** (Depth-First Search, visita in profondità) esplora il grafo seguendo ogni percorso "fino in fondo" prima di tornare indietro (**backtracking**). Analogia classica: esplorare un labirinto con gesso (per segnare le strade già prese) e una corda (per tornare indietro). In termini algoritmici:
- il **gesso** corrisponde al marcatore booleano "visitato";
- la **corda** corrisponde alla **pila** (o alla catena di chiamate ricorsive).
### Versione ricorsiva
La formulazione naturale è ricorsiva: si visita un nodo $v$, poi si itera sui suoi vicini non ancora marcati, chiamando ricorsivamente la visita su ciascuno.

```pseudo
\begin{algorithm}
\caption{visitaDFSRicorsiva($v$, $T$) — visita DFS ricorsiva da $v$, estende $T$}
\begin{algorithmic}
\State marca e visita il vertice $v$
\ForAll{arco $(v, w) \in G$}
  \If{$w$ non è marcato}
    \State aggiungi l'arco $(v, w)$ all'albero $T$
    \State \Call{visitaDFSRicorsiva}{$w, T$}
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{visitaDFS($s$) — DFS da sorgente $s$, restituisce l'albero $T$}
\begin{algorithmic}
\State $T \gets$ albero vuoto
\State rendi tutti i nodi non marcati
\State \Call{visitaDFSRicorsiva}{$s, T$}
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

Per visitare **tutti** i nodi del grafo (anche quelli non raggiungibili da $s$, in grafi non connessi) si usa la versione che produce una **foresta DFS**:

```pseudo
\begin{algorithm}
\caption{visitaDFS($G$) — DFS completa su $G$, restituisce la foresta $F$}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State imposta $v$ come non marcato
\EndFor
\State $F \gets$ foresta vuota
\ForAll{nodo $v \in V$}
  \If{$v$ non è marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $F$
  \EndIf
\EndFor
\State \Return $F$
\end{algorithmic}
\end{algorithm}
```
### Versione iterativa
La versione ricorsiva può essere riscritta con una **pila esplicita** (utile per evitare overflow dello stack su grafi molto profondi).

```pseudo
\begin{algorithm}
\caption{visitaDFSIterativa($s$) — DFS iterativa con pila esplicita, restituisce $T$}
\begin{algorithmic}
\State rendi tutti i nodi non marcati
\State $T \gets$ albero con unico nodo $s$
\State sia $P$ una pila vuota
\State \Call{P.push}{$s$}
\While{$P$ non è vuota}
  \State $u \gets$ \Call{P.top}{}; \Call{P.pop}{}
  \If{$u$ non è marcato}
    \State marca $u$
    \ForAll{arco $(u, v) \in G$}
      \If{$v$ non è marcato}
        \State rendi $u$ padre di $v$ in $T$
        \State \Call{P.push}{$v$}
      \EndIf
    \EndFor
  \EndIf
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

> [!warning] Ordine di visita ricorsivo vs iterativo
> La versione iterativa con pila produce un albero DFS valido ma può visitare i nodi in **ordine diverso** rispetto alla versione ricorsiva, poiché i vicini vengono inseriti nella pila in ordine inverso rispetto a come verrebbero chiamati ricorsivamente.
### Esempio di visita DFS
Partendo da $s$, la DFS scende il più in profondità possibile lungo un ramo prima di risalire. L'albero DFS risultante ha in genere pochi nodi per livello e molta profondità, al contrario dell'albero BFS che è "largo" e "basso".

> [!example] Confronto albero BFS vs albero DFS
> Sul grafo con nodi $s, A, B, C, D, E, F, G$, la BFS produce un albero dove $A$ e $B$ (vicini di $s$) stanno entrambi al livello 1. La DFS invece scende: $s \to B \to A \to C \to D$, poi risale e scende su $E \to F \to G$, producendo un albero "a catena".
### Complessità della DFS
| Rappresentazione | Complessità temporale |
|---|---|
| Liste di adiacenza | $O(n + m)$ |
| Matrice di adiacenza | $O(n^2)$ |

L'analisi è analoga alla BFS: ogni nodo viene marcato al più una volta ($O(n)$ chiamate ricorsive totali) e ogni arco viene esaminato al più una volta nel ciclo interno ($O(m)$ totale). Con la versione su tutta la foresta la complessità rimane $O(n + m)$.
### Proprietà dell'albero DFS
> [!quote] Proprietà — Archi non-albero nella DFS
> Se il grafo è **non orientato**, per ogni arco $(u, v) \notin T$, i nodi $u$ e $v$ sono l'uno discendente o antenato dell'altro nell'albero DFS (non esistono "archi trasversali" tra rami diversi).
>
> Se il grafo è **orientato**, per ogni arco $(u, v) \notin T$ si ha:
> - $(u,v)$ è un **arco all'indietro** (da un nodo a un suo antenato), oppure
> - $(u,v)$ è un **arco in avanti** (da un nodo a un suo discendente), oppure
> - $(u,v)$ è un **arco trasversale a sinistra** (verso un sottoalbero già visitato prima di $u$).

> [!info] Applicazioni avanzate della DFS
> La DFS può essere arricchita con **tempi pre/post** (timestamp di scoperta e abbandono di ogni nodo) per classificare gli archi, rilevare cicli, eseguire l'**ordinamento topologico** di un DAG e trovare le **componenti fortemente connesse** di un grafo orientato. Tutte queste applicazioni sono trattate in dettaglio in [[09 - Applicazioni della DFS]].

> [!question] Domanda tipica d'esame
> - **D:** Qual è la struttura dati usata da BFS e DFS? Perché la differenza? **R:** BFS usa una **coda** (FIFO): estraendo sempre il nodo più "vecchio" si garantisce di visitare prima i nodi a distanza minore dalla sorgente. DFS usa una **pila** (LIFO) o la ricorsione: si segue ogni ramo fino in fondo prima di tornare indietro.
> - **D:** Qual è la complessità di BFS e DFS con liste di adiacenza? **R:** Entrambe $O(n + m)$: lineare nella dimensione del grafo (nodi + archi).
## Riepilogo
| | BFS | DFS |
|---|---|---|
| Struttura dati | Coda (FIFO) | Pila / Ricorsione |
| Complessità (liste) | $O(n + m)$ | $O(n + m)$ |
| Complessità (matrice) | $O(n^2)$ | $O(n^2)$ |
| Risultato principale | Distanze minime (archi) da $s$ | Albero/foresta di visita |
| Cammini minimi pesati | No (serve [[10 - Cammini Minimi e Dijkstra]]) | No |
| Applicazioni avanzate | Web crawling, garbage collection | Topological sort, SCC (→ [[09 - Applicazioni della DFS]]) |
