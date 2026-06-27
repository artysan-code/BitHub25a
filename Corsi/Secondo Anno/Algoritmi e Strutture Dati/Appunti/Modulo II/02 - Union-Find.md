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
| Operazione | Tempo |
|---|---|
| `makeSet` | $O(1)$ |
| `find` | $O(1)$ |
| `union` | $O(n)$ nel caso peggiore |

> [!warning] Sequenze di union inefficienti in QuickFind
> Particolari sequenze di `union` possono essere molto costose. Considerando le union:
> $$\text{union}(2,1),\ \text{union}(3,2),\ \ldots,\ \text{union}(n, n-1)$$
> la prima costa $1$ cambio di puntatore, la seconda $2$, ..., la $(k)$-esima costa $k$. Il costo totale è $1 + 2 + \cdots + (n-1) = \Theta(n^2)$.
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
## Applicazione: algoritmo di Kruskal
Il caso d'uso principale della struttura Union-Find è l'[[03 - Minimum Spanning Tree|algoritmo di Kruskal]] per il **Minimum Spanning Tree**. L'algoritmo ordina gli archi per peso crescente e aggiunge un arco $(u, v)$ all'albero solo se $u$ e $v$ appartengono a componenti connesse distinte — verifica realizzata tramite `find(u) != find(v)` — e poi esegue `union` per fondere le due componenti.

Con $n$ nodi e $m$ archi, Kruskal esegue:
- $n$ `makeSet`,
- $m$ `find` (due per ogni arco esaminato),
- al più $n-1$ `union`.

Con Union-Find ottimale (rank + path compression), il costo totale della gestione degli insiemi è $O(m \cdot \alpha(m, n))$, praticamente lineare.
> [!info] Collegamento con il Modulo I
> La struttura Union-Find è un esempio avanzato di [[05 - Strutture Dati Elementari e Dizionari|struttura dati]] progettata per operazioni specifiche. L'analisi ammortizzata su sequenze di operazioni riprende il tipo di ragionamento visto per le [[07 - Code con Priorità e Heap|code con priorità]].
## Domande tipiche d'esame
> [!example] Differenza tra QuickFind e QuickUnion
> D: Qual è la differenza tra QuickFind e QuickUnion? Quali euristiche li migliorano e con che costo ammortizzato?
> R: **QuickFind** usa alberi di altezza 1: `find` è $O(1)$, `union` è $O(n)$ nel caso peggiore ($\Theta(n^2)$ per sequenze degeneri). L'euristica **union by size** porta il costo ammortizzato di `union` a $O(\log n)$, con costo totale $O(m + n \log n)$ per $m$ find e $n$ union.
> **QuickUnion** usa alberi di altezza variabile: `union` è $O(1)$, `find` è $O(n)$ nel caso peggiore ($O(mn)$ per sequenze degeneri). L'euristica **union by size/rank** porta la `find` a $O(\log n)$ — grazie al lemma $s \geq 2^h$ — con costo totale $O(n + m \log n)$. Aggiungendo la **compressione dei cammini** a union by rank, il costo ammortizzato di `find` diventa $O(\alpha(m,n))$, praticamente costante, con costo totale $O(n + m \cdot \alpha(m+n,n))$ (Tarjan & van Leeuwen).

> [!example] Union by size: limite al numero di cambi di padre
> D: Perché con union by size in QuickFind ogni nodo cambia padre al più $O(\log n)$ volte?
> R: Per l'euristica, quando un nodo $x$ cambia padre, l'insieme a cui appartiene dopo la `union` ha cardinalità **almeno doppia** rispetto a quella dell'insieme da cui proveniva (si attacca sempre il più piccolo al più grande). Quindi:
> - al momento della creazione $x$ è in un insieme di dimensione $1 = 2^0$;
> - al primo cambio di padre è in un insieme di dimensione $\geq 2 = 2^1$;
> - all'$i$-esimo cambio è in un insieme di dimensione $\geq 2^i$.
> La dimensione massima è $n$, quindi $2^i \leq n$ implica $i \leq \log_2 n$: ogni nodo cambia padre al più $\log_2 n$ volte. Il costo totale delle union sull'intera sequenza è perciò $O(n \log n)$.
