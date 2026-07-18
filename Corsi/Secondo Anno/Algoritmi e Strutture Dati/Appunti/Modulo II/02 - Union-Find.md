# Union-Find
Il **tipo di dato Union-Find** (o *gestione degli insiemi disgiunti*) mantiene una collezione di insiemi disgiunti su cui è possibile eseguire efficientemente tre operazioni: creazione di un insieme, fusione di due insiemi e ricerca dell'insieme di appartenenza di un elemento. Strutture di questo tipo sono fondamentali nell'algoritmo di [[03 - Minimum Spanning Tree|Kruskal]] e nel calcolo degli antenati comuni minimi.
## Il problema Union-Find
Si vuole mantenere una collezione di insiemi disgiunti contenenti elementi distinti (ad esempio interi in $1 \ldots n$) durante l'esecuzione di una sequenza arbitraria delle seguenti operazioni:
> [!quote] Definizione — Operazioni Union-Find
> - **`makeSet(x)`**: crea il nuovo insieme $\{x\}$ di nome $x$ (l'elemento è anche il nome/rappresentante dell'insieme).
> - **`union(A, B)`**: unisce gli insiemi $A$ e $B$ in un unico insieme di nome $A$; distrugge i vecchi insiemi $A$ e $B$. Si suppone di accedere direttamente ai due insiemi.
> - **`find(x)`**: restituisce il nome dell'insieme contenente l'elemento $x$. Si suppone di accedere direttamente all'elemento $x$.

> [!info] Quante union sono possibili?
> Con $n$ elementi si possono eseguire al più $n-1$ operazioni `union`, poiché ogni `union` riduce di uno il numero di insiemi e si parte da $n$ insiemi singoletto.

L'obiettivo è progettare una struttura dati che sia efficiente su **sequenze arbitrarie** di operazioni. L'idea generale è rappresentare gli insiemi disgiunti con una **foresta di alberi radicati**: ogni albero corrisponde a un insieme, la radice contiene il nome (elemento rappresentativo) dell'insieme.

> [!question] Domanda tipica d'esame — Limite inferiore Ω(m+n) per qualunque struttura dati
> **D:** *(Vero o Falso)* «Ogni struttura dati, per eseguire una sequenza di n makeSet, n − 1 union e m find, deve impiegare nel caso peggiore tempo Ω(m + n).» *(chiesto il 16/07/2024 e 18/02/2025)*
> **R:** Vero. È un limite inferiore banale ma inevitabile: le $n$ `makeSet` devono creare $n$ nuovi insiemi (tempo $\Omega(n)$ solo per allocarli/inizializzarli) e le $m$ `find` devono restituire una risposta ciascuna (tempo $\Omega(1)$ per query, quindi $\Omega(m)$ in totale). Nessuna struttura dati, per quanto sofisticata, può evitare di "toccare" ogni elemento creato e ogni interrogazione ricevuta: da qui $\Omega(m+n)$. Il bound è coerente con tutte le implementazioni viste (QuickFind, QuickUnion, con o senza euristiche), che infatti presentano sempre un termine additivo $n$ o $m$ nella complessità totale.
## QuickFind
**Struttura**: una foresta di alberi di **altezza 1**. In ogni albero:
- la **radice** contiene il nome dell'insieme;
- le **foglie** sono gli elementi dell'insieme (incluso l'elemento rappresentativo, il cui valore è memorizzato anche nella radice).

```pseudo
\begin{algorithm}
\caption{makeSet($e$)}
\begin{algorithmic}
\State crea un nuovo albero con due nodi: una radice e un'unica foglia
\State memorizza $e$ sia nella foglia che come nome della radice
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{union($A, B$)}
\begin{algorithmic}
\State considera l'albero $A$ (insieme di nome $A$) e l'albero $B$ (insieme di nome $B$)
\ForAll{foglia di $B$}
  \State reindirizza il suo puntatore dalla radice di $B$ alla radice di $A$
\EndFor
\State cancella la vecchia radice di $B$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{find($e$)}
\begin{algorithmic}
\State accedi alla foglia corrispondente all'elemento $e$
\State segui il puntatore al padre (la radice)
\State \Return il nome memorizzato nella radice
\end{algorithmic}
\end{algorithm}
```

**Esempio**
```
makeSet(1)  makeSet(3)  makeSet(2)  makeSet(4)

   [1]         [3]         [2]         [4]      <- radici (nomi)
    |           |           |           |
    1           3           2           4       <- foglie

union(2,3): le foglie di {3} passano a puntare alla radice di {2}

   [1]         [2]         [4]
    |          / \          |
    1         2   3         4

union(4,2): le foglie di {4} passano a puntare alla radice di {2}

   [1]         [2]
    |         / | \
    1        2  3  4

find(2) -> segue foglia 2 -> radice [2] -> restituisce "2"
```

**Complessità**

| Operazione | Tempo                    |
| ---------- | ------------------------ |
| `makeSet`  | $O(1)$                   |
| `find`     | $O(1)$                   |
| `union`    | $O(n)$ nel caso peggiore |

> [!warning] Sequenze di union inefficienti in QuickFind
> Particolari sequenze di `union` possono essere molto costose. Considerando le union:
> $$\text{union}(2,1),\ \text{union}(3,2),\ \ldots,\ \text{union}(n, n-1)$$
> la prima costa $1$ cambio di puntatore, la seconda $2$, ..., la $(k)$-esima costa $k$. Il costo totale è $1 + 2 + \cdots + (n-1) = \Theta(n^2)$.

> [!question] Domanda tipica d'esame — Tre union, ciascuna di costo Θ(n) in QuickFind
> **D:** «Si fornisca un esempio di una sequenza di 3 operazioni di union in cui ogni singola operazione di union ha costo Θ(n). (Max 5 righe.)» *(chiesto il 18/07/2022)*
> **R:** Si considerino $n=4k$ elementi ripartiti (con `makeSet` e unioni preliminari non conteggiate) in quattro insiemi $A,B,C,D$ di $k=n/4$ elementi ciascuno. Poiché nella QuickFind base (senza union by size) `union($X,Y$)` rietichetta **sempre** le foglie del secondo argomento $Y$, indipendentemente dalla dimensione, bastano tre chiamate: `union($A,B$)` rietichetta $B$ ($k$ elementi, costo $\Theta(n)$); `union($C,D$)` rietichetta $D$ ($k$ elementi, costo $\Theta(n)$); `union($A,C$)` rietichetta $C$, che a questo punto contiene $C\cup D$, cioè $2k$ elementi (costo ancora $\Theta(n)$). Ogni singola union costa quindi $\Theta(n)$, semplicemente scegliendo come secondo argomento l'insieme grande da rietichettare.
### Euristica union by size (QuickFind)
**Idea**: evitare che un nodo cambi padre troppo spesso. Nell'unione di $A$ e $B$, si attaccano gli elementi dell'insieme di **cardinalità minore** a quello di cardinalità maggiore; se necessario si aggiorna la radice per mantenere il nome corretto. Ogni insieme mantiene esplicitamente la propria **size** (numero di elementi).

```pseudo
\begin{algorithm}
\caption{union($A, B$) — con union by size}
\begin{algorithmic}
\State considera l'albero $A$ e l'albero $B$
\If{$\text{size}(A) \geq \text{size}(B)$}
  \State reindirizza le foglie di $B$ verso la radice di $A$
  \State $\text{size}(A) \gets \text{size}(A) + \text{size}(B)$
\Else \Comment{$\text{size}(B) > \text{size}(A)$}
  \State reindirizza le foglie di $A$ verso la radice di $B$
  \State memorizza nella radice di $B$ il nome di $A$ \Comment{il nome dell'insieme diventa $A$}
  \State $\text{size}(B) \gets \text{size}(A) + \text{size}(B)$
\EndIf
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema — Analisi ammortizzata QuickFind con union by size
> Se si eseguono $m$ `find`, $n$ `makeSet` e al più $n-1$ `union`, il tempo richiesto dall'intera sequenza è $O(m + n \log n)$.

**Dimostrazione (idea)**:
- `find` e `makeSet` richiedono tempo $\Theta(m + n)$ in totale.
- Per le `union`, si concentra l'analisi su un singolo nodo: ogni volta che un nodo cambia padre, la cardinalità dell'insieme a cui apparterrà è **almeno doppia** rispetto a quella dell'insieme da cui viene:
  - all'inizio è in un insieme di dimensione $1$;
  - al primo cambio di padre è in un insieme di dimensione $\geq 2$;
  - all'$i$-esimo cambio è in un insieme di dimensione $\geq 2^i$.
- Poiché la dimensione massima è $n$, un nodo può cambiare padre al più $\log_2 n$ volte.
- Il tempo speso per un singolo nodo sull'intera sequenza è $O(\log n)$; su $n$ nodi è $O(n \log n)$.
- **Costo totale**: $O(m + n + n \log n) = O(m + n \log n)$.

**Complessità con union by size**

| Operazione | Caso peggiore | Ammortizzato |
|---|---|---|
| `makeSet` | $O(1)$ | $O(1)$ |
| `find` | $O(1)$ | $O(1)$ |
| `union` | $O(n)$ | $O(\log n)$ |
| Sequenza intera | — | $O(m + n \log n)$ |

> [!question] Domanda tipica d'esame — QuickFind + union by size: l'altezza resta 1
> **D:** *(Vero o Falso)* «Nella QuickFind con euristica union by size ogni insieme è rappresentato con un albero di altezza Θ(log n), dove n è il numero di makeSet, in modo che l'operazione di find richieda tempo logaritmico.» *(chiesto il 16/07/2024)*
> **R:** Falso. La union by size cambia **chi viene attaccato a chi** (l'insieme più piccolo viene rietichettato per unirsi a quello più grande), ma non cambia la forma degli alberi: in QuickFind ogni albero resta **sempre di altezza 1** (radice + foglie), con o senza euristica. È proprio questo che garantisce alla `find` un costo $O(1)$ costante, non logaritmico: si segue un unico puntatore dalla foglia alla radice. La union by size migliora invece il costo **ammortizzato** della `union` (da $O(n)$ nel caso peggiore a $O(\log n)$ ammortizzato), non la struttura né il costo della `find`.

> [!question] Domanda tipica d'esame — Union by size: limite al numero di cambi di padre
> **D:** Perché con union by size in QuickFind ogni nodo cambia padre al più $O(\log n)$ volte?
> **R:** Per l'euristica, quando un nodo $x$ cambia padre, l'insieme a cui appartiene dopo la `union` ha cardinalità **almeno doppia** rispetto a quella dell'insieme da cui proveniva (si attacca sempre il più piccolo al più grande). Quindi:
> - al momento della creazione $x$ è in un insieme di dimensione $1 = 2^0$;
> - al primo cambio di padre è in un insieme di dimensione $\geq 2 = 2^1$;
> - all'$i$-esimo cambio è in un insieme di dimensione $\geq 2^i$.
> La dimensione massima è $n$, quindi $2^i \leq n$ implica $i \leq \log_2 n$: ogni nodo cambia padre al più $\log_2 n$ volte. Il costo totale delle union sull'intera sequenza è perciò $O(n \log n)$.

> [!question] Domanda tipica d'esame — QuickFind + union by size: cambio etichetta e raddoppio della size
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickFind con euristica union by size, se in una sequenza di operazioni un elemento ha cambiato padre k volte allora appartiene ad un insieme che è grande almeno 2^k.» *(chiesto il 16/07/2024)*
> **R:** Vero — è la stessa proprietà vista sopra, qui enunciata come implicazione diretta anziché come limite superiore: per l'euristica union by size, ogni volta che un elemento cambia etichetta/radice, l'insieme in cui finisce ha cardinalità **almeno doppia** rispetto a quello da cui proveniva. Per induzione: alla nascita l'elemento è in un insieme di dimensione $1=2^0$; dopo il primo cambio è in un insieme di dimensione $\geq 2=2^1$; dopo il $k$-esimo cambio è in un insieme di dimensione $\geq 2^k$. È esattamente questo argomento a limitare a $O(\log n)$ il numero massimo di cambi per elemento, dato che la dimensione massima possibile è $n$.

> [!question] Domanda tipica d'esame — QuickFind + union by size: bound O(m + n log n)
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickFind con euristica union by size, ogni sequenza di n makeSet, n − 1 union e m find, richiede nel caso peggiore tempo O(m + n log n).» *(chiesto il 16/07/2024 e 18/02/2025)*
> **R:** Vero. È l'enunciato del teorema di analisi ammortizzata per QuickFind con union by size: gli $n$ `makeSet` e gli $m$ `find` costano $O(1)$ ciascuno, quindi $O(m+n)$ in totale; per le $n-1$ `union`, anche se una singola union può costare $O(n)$ nel caso peggiore, l'argomento del raddoppio della size mostra che ogni elemento cambia etichetta al più $O(\log n)$ volte, quindi il costo complessivo di tutte le union sull'intera sequenza è $O(n \log n)$. Sommando si ottiene $O(m+n+n\log n)=O(m+n\log n)$: è un bound sul **caso peggiore dell'intera sequenza** (non della singola operazione), valido per qualunque sequenza di quella forma.

> [!question] Domanda tipica d'esame — QuickFind + union by size: enunciato delle prestazioni
> **D:** «Si enunci in modo preciso le prestazioni della struttura dati, in termini di costi delle operazioni della struttura dati. (Max 5 righe.)» *(chiesto il 18/07/2022)*
> **R:** `find` costa $O(1)$ (lettura di un'etichetta). Ogni singola `union` costa $O(\text{dimensione dell'insieme più piccolo dei due unificati})$, quindi nel caso pessimo $O(n)$. Tuttavia, grazie alla union by size, ogni elemento cambia etichetta al più $O(\log n)$ volte (ogni volta che viene rietichettato la dimensione del suo insieme almeno raddoppia), quindi la sequenza delle (al più $n-1$) operazioni di `union` costa complessivamente $O(n \log n)$, e l'intera sequenza — $n$ `makeSet`, al più $n-1$ `union` e $m$ `find` — costa $O(m + n \log n)$.
## QuickUnion
**Struttura**: una foresta di alberi di **altezza anche maggiore di 1**. In ogni albero:
- la **radice** è l'elemento rappresentativo dell'insieme (il suo nome);
- i **nodi non radice** sono gli altri elementi dell'insieme.

```pseudo
\begin{algorithm}
\caption{makeSet($e$)}
\begin{algorithmic}
\State crea un nuovo albero con un unico nodo $e$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{union($A, B$)}
\begin{algorithmic}
\State imposta un puntatore dalla radice dell'albero $B$ alla radice dell'albero $A$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{find($e$)}
\begin{algorithmic}
\State a partire dal nodo $e$, risali i puntatori padre fino alla radice
\State \Return il nome memorizzato nella radice
\end{algorithmic}
\end{algorithm}
```

**Esempio**
```
makeSet(1) makeSet(3) makeSet(2) makeSet(4)

   1    3    2    4

union(2,3):  radice di {3} punta a radice di {2}

   1    2    4
        |
        3

union(4,2):  radice di {4} punta a radice di {2}

   1    2
       / \
      3   4

union(4,1):  union(A=4, B=1) -> radice di {1} punta a radice di {4}

        4
       / \
      2   1
      |\ 
      3  ...  (3 era figlio di 2)

find(3): 3 -> 2 -> 4 -> (radice) = "4"
```

> [!warning] Sequenze di union che degenerano in lista in QuickUnion
> Le union:
> $$\text{union}(2,1),\ \text{union}(3,2),\ \ldots,\ \text{union}(n, n-1)$$
> producono un albero di altezza $n-1$ (una lista). Se si eseguono poi $m$ `find`, il costo totale è $O(n + (n-1) + mn) = O(mn)$, che può essere $O(n^2)$ se $m = \Theta(n)$.

**Complessità**

| Operazione | Tempo |
|---|---|
| `makeSet` | $O(1)$ |
| `union` | $O(1)$ |
| `find` | $O(n)$ nel caso peggiore |
### Euristica union by size (QuickUnion)
**Idea**: mantenere gli alberi di altezza piccola. Nell'unione di $A$ e $B$, la radice dell'albero con **meno nodi** diventa figlia della radice dell'albero con **più nodi**.

```pseudo
\begin{algorithm}
\caption{union($A, B$) — con union by size}
\begin{algorithmic}
\If{$\text{size}(A) \geq \text{size}(B)$}
  \State rendi la radice di $B$ figlia della radice di $A$
\Else \Comment{$\text{size}(B) > \text{size}(A)$}
  \State rendi la radice di $A$ figlia della radice di $B$
  \State il nome del nuovo insieme è $A$ \Comment{memorizzato nella nuova radice}
\EndIf
\State aggiorna la size del nuovo albero radice
\end{algorithmic}
\end{algorithm}
```

**Esempio con union by size**
```
makeSet(a) makeSet(c) makeSet(b) makeSet(d) makeSet(e)

   a    c    b    d    e

union(b,d):  size uguale, b assorbe d

   a    c    b    e
             |
             d

union(a,c):  size uguale, a assorbe c

   a    b    e
   |    |
   c    d

union(e,b):  size(b)=2 > size(e)=1, b assorbe e

   a    b
   |   /|\
   c  d  e

union(a,b):  size(a)=2 < size(b)=3, b assorbe a; il nome dell'insieme diventa a

        b        <- nome "a" (aggiornato nella radice)
       /|\
      a  d  e
      |
      c
```

> [!quote] Lemma — Altezza in QuickUnion con union by size
> Con la **union by size**, dato un albero QuickUnion con $s$ nodi (size) e altezza $h$, vale che $s \geq 2^h$.
> **Corollario**: la `find` richiede tempo $O(\log n)$, e l'intera sequenza di operazioni costa $O(n + m \log n)$.

**Dimostrazione** (per induzione sulla sequenza di union): un albero nasce con $s=1, h=0$, e $1 \geq 2^0$. Quando un albero di altezza $h_1$ e size $s_1$ assorbe uno di altezza $h_2$ e size $s_2$ (con $s_1 \geq s_2$ per l'euristica):
- se $h_2 < h_1$: l'altezza non cresce, la size aumenta; la proprietà è preservata;
- se $h_2 \geq h_1$: la nuova altezza è $h_2 + 1$; la nuova size è $s_1 + s_2 \geq 2s_2 \geq 2 \cdot 2^{h_2} = 2^{h_2+1}$.

**Complessità con union by size (QuickUnion)**

| Operazione | Tempo |
|---|---|
| `makeSet` | $O(1)$ |
| `union` | $O(1)$ |
| `find` | $O(\log n)$ |
| Sequenza ($n$ makeSet, $n-1$ union, $m$ find) | $O(n + m \log n)$ |

> [!question] Domanda tipica d'esame — QuickUnion + union by size: l'altezza NON è 1
> **D:** *(Vero o Falso)* «Nella QuickUnion con euristica union by size ogni insieme è rappresentato con un albero di altezza 1, in modo che sia l'operazione di find che di union richiedano tempo logaritmico.» *(chiesto il 18/02/2025)*
> **R:** Falso, ed è sbagliata su due fronti. Primo: l'altezza 1 è una caratteristica di **QuickFind**, non di QuickUnion — in QuickUnion gli alberi possono avere altezza maggiore di 1 (con union by size il lemma $s\geq 2^h$ garantisce solo altezza $O(\log n)$, non altezza costante). Secondo: anche con altezza $O(\log n)$, la `union` in QuickUnion resta $O(1)$ (si limita a ricollegare due radici): è la `find` a costare $O(\log n)$, risalendo i puntatori padre fino alla radice.

> [!question] Domanda tipica d'esame — QuickUnion + union by size: find è O(log n) nel caso peggiore, non solo ammortizzato
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickUnion con euristica union by size, ogni operazione di find ha costo ammortizzato O(log n), dove n è il numero di makeSet. Eppure una singola operazione di find nel caso peggiore può costare anche Θ(n).» *(chiesto il 18/02/2025)*
> **R:** Falso. Con la sola union by size (senza compressione dei cammini), il lemma $s\geq 2^h$ garantisce che **ogni** albero con $n$ nodi ha altezza al più $O(\log n)$: è un bound **deterministico sul caso peggiore**, non solo ammortizzato. Di conseguenza anche la **singola** `find` costa $O(\log n)$ nel caso peggiore — non può mai costare $\Theta(n)$ con questa euristica attiva. (La confusione nasce forse pensando a QuickUnion **senza** alcuna euristica, dove sì una singola `find` può costare $\Theta(n)$ su una sequenza degenere che produce una lista.)

> [!question] Domanda tipica d'esame — QuickUnion + union by size: costruire un albero di altezza Θ(log n)
> **D:** «Si consideri la struttura dati QuickUnion con euristica union by size. Si mostri una sequenza di operazioni di n makeSet e n − 1 union in cui l'albero ottenuto abbia altezza Θ(log n) . (Max 5 righe.)» *(chiesto il 16/07/2024)*
> **R:** Con $n=2^k$ elementi, si eseguano gli $n$ `makeSet` e poi si uniscano gli alberi "a torneo", per round successivi: nel primo round si eseguono $n/2$ `union` tra coppie di singoletti (size 1 ciascuno), ottenendo $n/2$ alberi di altezza $1$; nel secondo round si uniscono a coppie i $n/2$ alberi di altezza $1$ (size uguale, quindi per il lemma $s\geq 2^h$ l'altezza cresce di 1), ottenendo $n/4$ alberi di altezza $2$; e così via. Dopo $k=\log_2 n$ round (un totale di $n-1$ union) resta un unico albero di altezza esattamente $k=\Theta(\log n)$: è il caso peggiore ammesso dal lemma, raggiunto unendo sempre alberi di size (e altezza) uguale. *(La stessa domanda, numerata «2.», è stata riproposta identica anche il 18/02/2025.)*
### Euristica compressione dei cammini (path compression)
**Idea**: durante l'esecuzione di `find(x)`, mentre si risale il cammino da $x$ alla radice, si **comprimono tutti i nodi del cammino rendendoli figli diretti della radice**. La prima `find(x)` ha lo stesso costo (lineare nella lunghezza del cammino), ma le `find` successive su quegli stessi nodi costeranno $O(1)$.

```pseudo
\begin{algorithm}
\caption{find($x$) — con compressione dei cammini}
\begin{algorithmic}
\If{$x$ è la radice}
  \State \Return $x$
\EndIf
\State $\mathit{radice} \gets$ \Call{find}{$\mathit{padre}[x]$} \Comment{risale ricorsivamente}
\State $\mathit{padre}[x] \gets \mathit{radice}$ \Comment{compressione: $x$ diventa figlio della radice}
\State \Return $\mathit{radice}$
\end{algorithmic}
\end{algorithm}
```

**Esempio**
```
Prima di find(x):             Dopo find(x):

      D                           D
      |                        /  |  \  \
      C                       A   B   C   x
      |
      B
      |
      A
      |
      x

Tutti i nodi sul cammino (x, A, B, C) diventano figli diretti di D
```

> [!info] Perché usare union by rank invece di union by size con path compression
> Con la compressione dei cammini la **size** degli alberi può risultare fuorviante (i nodi vengono spostati). Si preferisce usare il **rank** (un limite superiore all'altezza dell'albero, che non decresce mai). Con union by rank: nell'unione si attacca la radice di rank minore alla radice di rank maggiore; se i rank sono uguali si sceglie arbitrariamente e si incrementa il rank della nuova radice di 1.
## Analisi ottimale: la funzione inversa di Ackermann
Combinando **union by rank (o by size)** e **compressione dei cammini** si ottiene il risultato ottimale, dimostrato da Tarjan e van Leeuwen:
> [!quote] Teorema — Tarjan & van Leeuwen
> Usando in QuickUnion le euristiche di **union by rank** (o by size) e **compressione dei cammini**, una qualsiasi sequenza di $n$ `makeSet`, $n-1$ `union` e $m$ `find` ha un costo di
> $$O\bigl(n + m \cdot \alpha(m+n,\ n)\bigr)$$
> dove $\alpha(x, y)$ è la **funzione inversa della funzione di Ackermann**.

**La funzione di Ackermann** $A(i,j)$ (per interi $i,j \geq 1$) è definita con la ricorrenza $A(1,j)=2^j$, $A(i,1)=A(i-1,2)$ per $i \geq 2$, e $A(i,j)=A(i-1,A(i,j-1))$ per $i,j \geq 2$. Cresce in modo straordinariamente rapido:

| | $j=1$ | $j=2$ | $j=3$ | $j=4$ |
|---|---|---|---|---|
| $i=1$ | $2$ | $2^2=4$ | $2^3=8$ | $2^4=16$ |
| $i=2$ | $2^2=4$ | $2^4=16$ | $2^{16}=65536$ | $2^{65536}$ |
| $i=3$ | $16$ | torre di 4 esponenti $2$ | torre di 65536 esponenti $2$ | ancora più alta |
| $i=4$ | già astronomico | ... | ... | $> 10^{80}$ (atomi universo) |

> [!info] Come leggere la tabella
> La riga $i=2$ segue la ricorrenza $A(2,j)=A(1,A(2,j-1))=2^{A(2,j-1)}$: ogni valore è $2$ elevato al valore precedente. Così $A(2,1)=4$, $A(2,2)=2^4=16$, $A(2,3)=2^{16}=65536$, $A(2,4)=2^{65536}$ (un numero con circa $2\times 10^{19727}$ cifre). La riga $i=3$ cresce ancora più rapidamente: ogni valore è una torre esponenziale di altezza $A(2, \cdot)$.

La **funzione inversa** $\alpha(m, n)$ è definita come:
$$\alpha(m, n) = \min\!\left\{i > 0 : A\!\left(i,\, \left\lfloor m/n \right\rfloor\right) > \log_2 n\right\}$$
> [!quote] Proprietà — $\alpha(m,n)$
> 1. Per $n$ fissato, $\alpha(m,n)$ è **monotonicamente decrescente** al crescere di $m$.
> 2. $\alpha(n,n) \to \infty$ per $n \to \infty$, ma con crescita **estremamente lenta**.

> [!info] $\alpha(m,n) \leq 4$ per ogni scopo pratico
> $A(4, 1) = A(3, 2)$, che è già una torre di esponenti $2$ di altezza 16, ben oltre $10^{80}$ (stima del numero di atomi nell'universo). Quindi $\alpha(m,n) \leq 4$ per tutti gli $n < 2^{10^{80}}$: in pratica, $\alpha(m,n)$ si può considerare una **costante**.

La variante $\log^*$ (logaritmo iterato) permette di raffinare il bound. Si definisce:
$$\log^{(1)} n = \log_2 n, \quad \log^{(i)} n = \log_2\!\left(\log^{(i-1)} n\right), \quad \log^* n = \min\!\left\{i > 0 : \log^{(i)} n \leq 1\right\}$$
Per esempio, $\log^* 2^{65536} = 5$. Si può dimostrare che:
- $\alpha(m,n) \leq 1$ quando $m/n > \log_2 \log_2 n$;
- $\alpha(m,n) \leq 2$ quando $m/n > \log^* \log_2 n$.

**Riepilogo complessità di tutte le implementazioni**

| Implementazione | `makeSet` | `union` | `find` | Sequenza completa |
|---|---|---|---|---|
| QuickFind | $O(1)$ | $O(n)$ p.p. | $O(1)$ | $O(m + n^2)$ p.p. |
| QuickFind + union by size | $O(1)$ | $O(n)$ p.p., $O(\log n)$ amm. | $O(1)$ | $O(m + n \log n)$ |
| QuickUnion | $O(1)$ | $O(1)$ | $O(n)$ p.p. | $O(mn)$ p.p. |
| QuickUnion + union by size | $O(1)$ | $O(1)$ | $O(\log n)$ | $O(n + m \log n)$ |
| QuickUnion + rank + path compression | $O(1)$ | $O(1)$ | $O(\alpha(m,n))$ amm. | $O(n + m \cdot \alpha(m+n,n))$ |

*(p.p. = caso peggiore; amm. = ammortizzato)*

> [!question] Domanda tipica d'esame — Differenza tra QuickFind e QuickUnion
> **D:** Qual è la differenza tra QuickFind e QuickUnion? Quali euristiche li migliorano e con che costo ammortizzato?
> **R:** **QuickFind** usa alberi di altezza 1: `find` è $O(1)$, `union` è $O(n)$ nel caso peggiore ($\Theta(n^2)$ per sequenze degeneri). L'euristica **union by size** porta il costo ammortizzato di `union` a $O(\log n)$, con costo totale $O(m + n \log n)$ per $m$ find e $n$ union.
> **QuickUnion** usa alberi di altezza variabile: `union` è $O(1)$, `find` è $O(n)$ nel caso peggiore ($O(mn)$ per sequenze degeneri). L'euristica **union by size/rank** porta la `find` a $O(\log n)$ — grazie al lemma $s \geq 2^h$ — con costo totale $O(n + m \log n)$. Aggiungendo la **compressione dei cammini** a union by rank, il costo ammortizzato di `find` diventa $O(\alpha(m,n))$, praticamente costante, con costo totale $O(n + m \cdot \alpha(m+n,n))$ (Tarjan & van Leeuwen).
## Applicazione: algoritmo di Kruskal
Il caso d'uso principale della struttura Union-Find è l'[[03 - Minimum Spanning Tree|algoritmo di Kruskal]] per il **Minimum Spanning Tree**. L'algoritmo ordina gli archi per peso crescente e aggiunge un arco $(u, v)$ all'albero solo se $u$ e $v$ appartengono a componenti connesse distinte — verifica realizzata tramite `find(u) != find(v)` — e poi esegue `union` per fondere le due componenti.

Con $n$ nodi e $m$ archi, Kruskal esegue:
- $n$ `makeSet`,
- $m$ `find` (due per ogni arco esaminato),
- al più $n-1$ `union`.

Con Union-Find ottimale (rank + path compression), il costo totale della gestione degli insiemi è $O(m \cdot \alpha(m, n))$, praticamente lineare.
> [!info] Collegamento con il Modulo I
> La struttura Union-Find è un esempio avanzato di [[05 - Strutture Dati Elementari e Dizionari|struttura dati]] progettata per operazioni specifiche. L'analisi ammortizzata su sequenze di operazioni riprende il tipo di ragionamento visto per le [[07 - Code con Priorità e Heap|code con priorità]].

> [!question] Domanda tipica d'esame — Union-Find in Kruskal: quale struttura, quali operazioni
> **D:** «B. Si dica quale struttura dati viene utilizzata nell'implementazione efficiente dell'algoritmo di Kruskal, quali operazioni mette a disposizione la struttura dati e come queste vengono usate nell'algoritmo. (Max 10 righe.)» *(chiesto il 19/02/2024)*
> **R:** Si utilizza la struttura dati **Union-Find** (gestione di insiemi disgiunti), che mette a disposizione tre operazioni: `makeSet(x)` (crea un nuovo insieme singoletto $\{x\}$), `union(A,B)` (fonde due insiemi in uno) e `find(x)` (restituisce il nome dell'insieme che contiene $x$). In Kruskal, ogni insieme rappresenta una componente connessa dell'albero in costruzione: si esegue una `makeSet` per ciascuno degli $n$ nodi (ogni nodo parte come componente a sé), poi si scandiscono gli $m$ archi in ordine di peso crescente e per ciascun arco $(u,v)$ si esegue `find(u)` e `find(v)` per verificare se $u$ e $v$ appartengono già alla stessa componente; se le componenti sono distinte, l'arco viene aggiunto all'MST e si esegue `union` per fondere le due componenti, altrimenti l'arco viene scartato (chiuderebbe un ciclo). Con l'implementazione ottimale (union by rank/size + compressione dei cammini) il costo delle $O(m)$ `find` e delle $n-1$ `union` è $O(m\cdot\alpha(m,n))$, praticamente lineare.

> [!question] Domanda tipica d'esame — Kruskal con QuickFind senza euristica: non è (solo) O(n²)
> **D:** *(Vero o Falso)* «Se si implementa l'algoritmo di Kruskal con la struttura dati Quick-Find senza euristica di bilanciamento union-by-size, la complessità dell'algoritmo nel caso peggiore è O(n^2).» *(chiesto il 13/06/2024)*
> **R:** Falso. Con QuickFind senza union by size, le $n-1$ `union` costano $O(n)$ nel caso peggiore ciascuna, quindi $O(n^2)$ in totale, e le $O(m)$ `find` costano $O(1)$ ciascuna; ma Kruskal deve anche **ordinare gli $m$ archi**, operazione che costa $O(m\log m)$. La complessità corretta nel caso peggiore è quindi $O(m\log m + n^2)$, non semplicemente $O(n^2)$: se il grafo è denso (ad esempio $m=\Theta(n^2)$), il termine $m\log m = \Theta(n^2\log n)$ domina su $n^2$, rendendo l'affermazione falsa.

> [!question] Domanda tipica d'esame — Kruskal senza union by size con |E| = O(n^{3/2})
> **D:** «Qual è la complessità nel caso peggiore dell'algoritmo di Kruskal implementato con la struttura dati Union-Find senza l'uso dell'euristica union by size se il numero di archi |E| = O(n^{3/2})? [risposta in 1 riga]» *(chiesto il 27/09/2023)*
> **R:** $O(n^{5/2})$ — senza union by size il Find costa $O(n)$ nel caso peggiore (l'albero può degenerare in una lista), quindi il costo delle $O(|E|)$ `find` è $O(|E|\cdot n)=O(n^{3/2}\cdot n)=O(n^{5/2})$, che domina sia il costo di ordinamento $O(|E|\log|E|)=O(n^{3/2}\log n)$ sia quello delle `union`, dando complessità totale $O(n^{5/2})$.

> [!question] Domanda tipica d'esame — Kruskal con QuickFind + union by size, archi già ordinati
> **D:** *(Vero o Falso)* «Si assuma di implementare l'algoritmo di Kruskal usando una struttura dati QuickFind con euristica union by size. Si assuma inoltre di avere già gli archi del grafo ordinati in ordine non decrescente rispetto al loro peso. Allora l'esecuzione dell'algoritmo di Kruskal ha complessità temporale O(m + n log n).» *(chiesto il 18/02/2025)*
> **R:** Vero. Se gli archi sono già ordinati, Kruskal non deve più pagare il costo di ordinamento $O(m\log m)$: restano solo le $O(m)$ `find` (costo $O(1)$ ciascuna in QuickFind, quindi $O(m)$ in totale) e le $n-1$ `union`, il cui costo complessivo con union by size è $O(n\log n)$ (per l'argomento del raddoppio della size). Sommando si ottiene esattamente $O(m+n\log n)$, in linea con il bound generale della QuickFind con union by size.

> [!question] Domanda tipica d'esame — Kruskal con QuickUnion + union by size, archi già ordinati
> **D:** *(Vero o Falso)* «Si assuma di implementare l'algoritmo di Kruskal usando una struttura dati QuickUnion con euristica union by size. Si assuma inoltre di avere già gli archi del grafo ordinati in ordine non decrescente rispetto al loro peso. Allora l'esecuzione dell'algoritmo di Kruskal ha comunque complessità temporale O(m log n).» *(chiesto il 16/07/2024)*
> **R:** Vero. Con gli archi già ordinati si evita il costo di ordinamento; restano le $n$ `makeSet` ($O(n)$), le $n-1$ `union` (costo $O(1)$ ciascuna in QuickUnion, quindi $O(n)$ in totale) e le $O(m)$ `find`, ciascuna $O(\log n)$ grazie al lemma $s\geq 2^h$ della union by size. Il costo delle `find` domina: $O(m\log n)$. Complessivamente $O(n+m\log n)=O(m\log n)$ (essendo $m\geq n-1$ per la connessione del grafo), da cui la complessità dichiarata.

> [!question] Domanda tipica d'esame — Kruskal con una Union-Find ipotetica: makeSet/union O(1), find O(log log n)
> **D:** «2. Immaginate di implementare l'algoritmo di Kruskal con un'altra struttura dati Union-Find i cui costi delle operazioni sono: la MakeSet e l'operazione di Union hanno costo costante, mentre la Find costa O(log log n). Quale sarebbe la complessità dell'algoritmo di Kruskal? Giustificate la risposta. (Max 5 righe.)» *(chiesto il 28/09/2022)*
> **R:** $O(m\log m)$ (equivalentemente $O(m\log n)$, dato che $m<n^2$ implica $\log m=O(\log n)$): con $n$ `makeSet` e $n-1$ `union` a costo costante si spende $O(n)$, e con $O(m)$ `find` a costo $O(\log\log n)$ si spende $O(m\log\log n)$; ma Kruskal deve comunque ordinare gli $m$ archi, costo $O(m\log m)$, che domina asintoticamente sia $O(n)$ sia $O(m\log\log n)$ (essendo $\log\log n = o(\log m)$). La complessità della gestione degli insiemi diventa quindi irrilevante: è **l'ordinamento** a determinare il costo totale dell'algoritmo.
