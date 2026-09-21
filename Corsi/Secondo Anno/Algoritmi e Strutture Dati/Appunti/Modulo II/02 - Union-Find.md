---
tags:
  - algoritmi
  - union-find
slide: ["02"]
capitolo: "Demetrescu cap. 9"
---
# Union-Find
Il **tipo di dato Union-Find** (o *gestione degli insiemi disgiunti*) mantiene una collezione di insiemi disgiunti su cui è possibile eseguire efficientemente tre operazioni: creazione di un insieme, fusione di due insiemi e ricerca dell'insieme di appartenenza di un elemento. Strutture di questo tipo sono fondamentali nell'algoritmo di [[03 - Minimum Spanning Tree|Kruskal]] e nel calcolo degli antenati comuni minimi. Gli item d'esame su questa struttura stanno nella palestra [[Esercizi 02 - Union-Find]], richiamata sezione per sezione.
## Il problema Union-Find
Si vuole mantenere una collezione di insiemi disgiunti contenenti elementi distinti (ad esempio interi in $1 \ldots n$) durante l'esecuzione di una sequenza arbitraria delle seguenti operazioni:

> [!quote] Definizione — Operazioni Union-Find
> - **`makeSet(x)`**: crea il nuovo insieme $\{x\}$ di nome $x$ (l'elemento è anche il nome/rappresentante dell'insieme).
> - **`union(A, B)`**: unisce gli insiemi $A$ e $B$ in un unico insieme di nome $A$; distrugge i vecchi insiemi $A$ e $B$. Si suppone di accedere direttamente ai due insiemi.
> - **`find(x)`**: restituisce il nome dell'insieme contenente l'elemento $x$. Si suppone di accedere direttamente all'elemento $x$.
>
> Le firme distinguono **due tipi diversi**: `union` prende **nomi di insiemi**, `find` prende un **elemento** e restituisce un **nome**. Alla creazione i due coincidono — `makeSet(x)` fa di $x$ sia l'elemento sia il nome — ma **dopo una union possono divergere**, e in QuickUnion il nome può finire su una radice che è un nodo con un'altra lettera.

> [!info] Regola — quante union sono possibili
> Con $n$ elementi si possono eseguire al più $n-1$ operazioni `union`, poiché ogni `union` riduce di uno il numero di insiemi e si parte da $n$ insiemi singoletto.

L'obiettivo è progettare una struttura dati che sia efficiente su **sequenze arbitrarie** di operazioni. L'idea generale è rappresentare gli insiemi disgiunti con una **foresta di alberi radicati**: ogni albero corrisponde a un insieme, la radice contiene il nome (elemento rappresentativo) dell'insieme.

> [!quote] Proprietà — Lower bound $\Omega(m+n)$ *(non enunciato sulle slide; chiesto all'esame il 16/07/2024 e il 18/02/2025)*
> Qualunque struttura dati, per eseguire una sequenza di $n$ `makeSet`, $n-1$ `union` e $m$ `find`, richiede nel caso peggiore tempo $\Omega(m+n)$.
> **Dimostrazione (diretta).** Le $n$ `makeSet` devono creare $n$ insiemi distinti, e questo richiede $\Omega(n)$ solo per allocarli; le $m$ `find` devono restituire una risposta ciascuna, quindi $\Omega(m)$. Nessuna struttura può evitare di toccare ogni elemento creato e ogni interrogazione ricevuta. $\square$

Il bound spiega perché **tutte** le implementazioni viste più sotto hanno un termine additivo $n$ o $m$ nella complessità totale: nessuna scende sotto $\Omega(m+n)$, e le migliori vi si avvicinano aggiungendo solo un fattore $\alpha(m,n)$ praticamente costante.

→ **Palestra**: [[Esercizi 02 - Union-Find#Lower bound per qualunque struttura Union-Find|lower bound $\Omega(m+n)$ — 16/07/2024, 18/02/2025]]
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
\caption{union(nome $A$, nome $B$)}
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
\caption{find(elemento $e$) $\to$ nome}
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

union(4,2): le foglie di {2} passano a puntare alla radice di {4}
            (il nome del risultato è il primo argomento: A = 4)

   [1]         [4]
    |         / | \
    1        2  3  4

find(2) -> segue foglia 2 -> radice [4] -> restituisce "4"
```

![[uf_quickfind_esempio.png]]
Stato finale dell'esempio, dalla slide: i cerchi verdi sono gli elementi, il nodo in cima a ogni albero porta il **nome dell'insieme**. Due cose da guardare: dopo `union(4,2)` l'insieme si chiama **4** e non 2 — il nome è sempre il primo argomento — e ogni albero ha **altezza 1**, che è ciò che rende la `find` $O(1)$.

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

![[uf_union_costo_lineare.png]]
La stessa sequenza sulla slide, con il conteggio dei cambi di puntatore affiancato a ciascuna union: 1, 2, 3, … fino a $n-1$. Il punto che il testo da solo non rende è che **il costo non è di una singola union** — ognuna presa da sola è $O(n)$ e sembra innocua — ma della **somma sull'intera sequenza**, che è $\Theta(n^2)$.

> [!info] Regola — il costo di una union lo paga il secondo argomento
> In QuickFind base `union($A,B$)` rietichetta **sempre e solo** le foglie del **secondo** argomento, qualunque siano le dimensioni relative dei due insiemi. È il fatto strutturale da cui discendono sia le sequenze costose sia i controesempi richiesti all'esame: basta passare come secondo argomento un insieme già grande per pagare $\Theta(n)$ a ogni chiamata. Con la union by size questo non vale più — a essere rietichettato è sempre il più piccolo dei due, indipendentemente dall'ordine degli argomenti.

→ **Palestra**: [[Esercizi 02 - Union-Find#Tre union ciascuna di costo Θ(n)|tre union da $\Theta(n)$ — 18/07/2022, max 5 righe]]
### Euristica union by size (QuickFind)
**Idea**: evitare che un nodo cambi padre troppo spesso. Nell'unione di $A$ e $B$, si attaccano gli elementi dell'insieme di **cardinalità minore** a quello di cardinalità maggiore; se necessario si aggiorna la radice per mantenere il nome corretto. Ogni insieme mantiene esplicitamente la propria **size** (numero di elementi).

![[uf_union_by_size_quickfind.png]]
La regola sulla slide: `union(A,B)` con $\text{size}(A) < \text{size}(B)$ sposta gli elementi di $A$ sotto la radice di $B$, non il contrario. Il dettaglio che sfugge è in basso a sinistra nella figura: la radice di arrivo viene **rinominata** $A$ (il tratteggio), perché il nome del risultato resta il **primo argomento** anche quando è l'insieme piccolo. Senza quel passaggio l'euristica cambierebbe il nome dell'insieme, che è un effetto collaterale non ammesso.

```pseudo
\begin{algorithm}
\caption{union(nome $A$, nome $B$) — con union by size}
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

![[uf_union_costo.png]]
Il costo di una singola `union`, dalla slide: due insiemi da $n/2$ elementi, e rietichettarne uno costa $\Theta(n)$. Le due domande in fondo alla slide sono l'ossatura dell'analisi ammortizzata — cambiare padre a **un** nodo costa tempo costante, ma **quante volte** un nodo può cambiare padre è al più $\log n$. È da lì che esce il bound $O(m + n\log n)$ sull'intera sequenza, non sulla singola operazione.

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

→ **Palestra**: [[Esercizi 02 - Union-Find#QuickFind + union by size: altezza degli alberi|l'altezza resta 1 — 16/07/2024]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Cambi di padre e raddoppio della size|cambi di padre e raddoppio della size — 16/07/2024]]

→ **Palestra**: [[Esercizi 02 - Union-Find#QuickFind + union by size: costo della sequenza completa|il bound $O(m+n\log n)$ — 16/07/2024, 18/02/2025]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Enunciare le prestazioni della struttura|enunciato delle prestazioni — 18/07/2022, max 5 righe]]
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
\caption{union(nome $A$, nome $B$)}
\begin{algorithmic}
\State imposta un puntatore dalla radice dell'albero $B$ alla radice dell'albero $A$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{find(elemento $e$) $\to$ nome}
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

union(4,2):  radice di {2} punta a radice di {4}   (nome del risultato: A = 4)

   1    4
        |
        2
        |
        3

union(4,1):  union(A=4, B=1) -> radice di {1} punta a radice di {4}

        4
       / \
      2   1
      |
      3

find(3): 3 -> 2 -> 4 -> (radice) = "4"
```

![[uf_quickunion_esempio.png]]
Lo stesso esempio in QuickUnion, dalla slide: qui gli alberi possono avere **altezza maggiore di 1**, e infatti 3 sta sotto 2 che sta sotto 4. È la differenza che ribalta i costi rispetto a QuickFind — `union` diventa $O(1)$, `find` diventa proporzionale all'altezza.

> [!warning] Sequenze di union che degenerano in lista in QuickUnion
> Le union:
> $$\text{union}(2,1),\ \text{union}(3,2),\ \ldots,\ \text{union}(n, n-1)$$
> producono un albero di altezza $n-1$ (una lista). Se si eseguono poi $m$ `find`, il costo totale è $O(n + (n-1) + mn) = O(mn)$, che può essere $O(n^2)$ se $m = \Theta(n)$.

![[uf_find_costo_lineare.png]]
La catena che ne risulta, dalla slide. Da notare: è **la stessa sequenza di union** della figura in QuickFind qualche sezione più su — cambia solo dove si paga il conto. Lì ogni union rietichettava le foglie e il costo era $\Theta(n^2)$ sulle union; qui ogni union costa $O(1)$ e il prezzo si sposta interamente sulle $m$ `find`, che risalgono una lista lunga $n-1$.

**Complessità**

| Operazione | Tempo |
|---|---|
| `makeSet` | $O(1)$ |
| `union` | $O(1)$ |
| `find` | $O(n)$ nel caso peggiore |
### Euristica union by size (QuickUnion)
**Idea**: mantenere gli alberi di altezza piccola. Nell'unione di $A$ e $B$, la radice dell'albero con **meno nodi** diventa figlia della radice dell'albero con **più nodi**.

![[uf_bilanciamento_quickunion.png]]
I tre pannelli della slide: **(a)** `makeSet(x)` crea un nodo isolato; **(b)** `union(A,B)` con $\text{size}(A) < \text{size}(B)$ appende la radice di $A$ sotto quella di $B$; **(c)** `find(x)` risale il cammino. Il riquadro giallo in **(b)** è la cosa da fissare: **il nome di quel nodo diventa $A$** — la radice resta fisicamente quella di $B$, ma l'insieme si chiama $A$. È esattamente ciò che rende `union(a,e)` diverso da `union(a,b)` nell'esempio qui sotto: gli argomenti sono **nomi di insiemi**, non radici di alberi.

```pseudo
\begin{algorithm}
\caption{union(nome $A$, nome $B$) — con union by size}
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

> [!warning] Nodo, radice e nome dell'insieme sono tre cose diverse
> In QuickUnion il nome di un insieme è memorizzato **nella radice**, ma dopo una union-by-size la radice può essere un nodo la cui lettera è diversa dal nome. Nell'esempio qui sotto, dopo `union(e,b)` esiste un insieme **di nome `e`** la cui **radice è il nodo `b`**, e il nodo `e` sta in fondo come figlia.
>
> Da qui due conseguenze che l'esempio rende facili da sbagliare:
> - **gli argomenti della `union` sono nomi di insiemi**, cioè quello che restituirebbe una `find` — non radici di alberi. Per questo l'ultima operazione si scrive `union(a,e)` e non `union(a,b)`: un insieme di nome `b` in quel momento non esiste;
> - in `union(a,e)` le due decisioni sono **indipendenti**: chi scende sotto chi lo decide la *size* (il nodo `a` scende sotto `b` perché $2 < 3$), come si chiama il risultato lo decide la regola del **primo argomento** (il nome `a` sale sulla radice `b`). Nodo e nome si muovono in direzioni opposte.
>
> **Nessun elemento viene mai eliminato** da una union: il nodo `a` perde solo il ruolo di radice e resta nell'albero come nodo interno, con `c` ancora appesa sotto di sé.

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
             l'insieme ora si chiama "e", ma la sua radice è il nodo b

   a    b   <- nome "e"
   |   / \
   c  d   e

union(a,e):  size(a)=2 < size(e)=3, la radice di {a} scende sotto la radice di {e}
             il nome del risultato è il primo argomento: "a"

        b   <- nome "a"
       /|\
      a  d  e
      |
      c
```

![[uf_ubs_quickunion_sequenza.png]]
Le quattro tappe della stessa sequenza, dalle slide pp. 58-63 *(composizione di quattro ritagli)*. L'intestazione di ogni riquadro elenca le operazioni già eseguite, quindi si legge da sinistra a destra e dall'alto in basso. Il dettaglio che sfugge è la **scritta rossa sopra la radice**: è il **nome dell'insieme**, che dopo una union puo' essere diverso dal nodo che sta in cima. Nel terzo riquadro la radice e' $b$ ma l'insieme si chiama $e$; nel quarto la radice e' ancora $b$ e l'insieme si chiama $a$. È per questo che l'ultima operazione si scrive `union(a,e)` e non `union(a,b)`: gli argomenti della union sono **nomi di insiemi**, non radici di alberi.

> [!quote] Lemma — Altezza in QuickUnion con union by size
> Con la **union by size**, dato un albero QuickUnion con $s$ nodi (size) e altezza $h$, vale che $s \geq 2^h$.
> **Corollario**: la `find` richiede tempo $O(\log n)$, e l'intera sequenza di operazioni costa $O(n + m \log n)$.

Sulla slide il lemma è enunciato e lasciato come esercizio («dim: provate a dimostrarlo voi»); la dimostrazione che segue è quella da saper produrre.

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

→ **Palestra**: [[Esercizi 02 - Union-Find#QuickUnion + union by size: altezza degli alberi|l'altezza non è 1 — 18/02/2025]]

> [!warning] È un bound sul caso peggiore, non ammortizzato
> Il lemma $s \geq 2^h$ vincola l'altezza di **ogni** albero, in **ogni** momento: con la sola union by size la `find` costa $O(\log n)$ nel **caso peggiore**, non «in media» o «ammortizzato». Una singola `find` non può mai costare $\Theta(n)$ finché l'euristica è attiva — quel caso appartiene a QuickUnion **senza** euristiche, dove la sequenza $\text{union}(2,1), \text{union}(3,2), \ldots$ produce una lista. La distinzione fra *caso peggiore* e *ammortizzato* è la coppia di affermazioni su cui le tracce insistono di più.

→ **Palestra**: [[Esercizi 02 - Union-Find#QuickUnion + union by size: find ammortizzato e caso peggiore|caso peggiore contro ammortizzato — 18/02/2025]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Costruire un albero di altezza Θ(log n)|costruire un albero di altezza $\Theta(\log n)$ — 16/07/2024, max 5 righe]]

![[uf_union_by_size_quickunion.png]]
Union by size in QuickUnion, dalla slide: la radice dell'albero con **meno nodi** diventa figlia della radice dell'altro. È l'euristica che tiene l'altezza a $O(\log n)$ — e si noti che agisce sulla *forma* dell'albero, al contrario di quanto fa in QuickFind, dove l'altezza resta 1 comunque.
### Euristica compressione dei cammini (path compression)
**Idea**: durante l'esecuzione di `find(x)`, mentre si risale il cammino da $x$ alla radice, si **comprimono tutti i nodi del cammino rendendoli figli diretti della radice**. La prima `find(x)` ha lo stesso costo (lineare nella lunghezza del cammino), ma le `find` successive su quegli stessi nodi costeranno $O(1)$.

```pseudo
\begin{algorithm}
\caption{find(elemento $x$) $\to$ nome — con compressione dei cammini}
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

![[uf_path_compression.png]]
La compressione dei cammini, dalla slide: a sinistra il cammino da $x$ alla radice $D$ prima della `find`, a destra dopo. **Tutti** i nodi attraversati diventano figli diretti della radice, non solo $x$; i triangoli sono i sottoalberi che restano appesi dove sono. La `find` che comprime costa comunque quanto il cammino percorso: il guadagno è sulle `find` successive.
### Euristica union by rank *(extra, non da slide)*
Le slide nominano la **union by rank** solo dentro l'enunciato del teorema di Tarjan & van Leeuwen, senza definirla. Questa sezione la sviluppa: non serve allo scritto, ma è la domanda che segue naturalmente all'orale.

> [!quote] Definizione — Rank e union by rank
> Il **rank** è un intero associato a ogni **radice**, che vale come **limite superiore all'altezza** del suo albero.
> - `makeSet(x)` pone $\text{rank}(x) = 0$;
> - `union(A,B)` attacca la radice di **rank minore** sotto quella di **rank maggiore**; se i due rank sono **uguali**, se ne sceglie una arbitrariamente come nuova radice e **le si incrementa il rank di 1**.
>
> Unire due alberi di rank uguale è l'**unico** caso in cui il rank cresce: è l'unico in cui l'altezza può aumentare.

> [!quote] Lemma — Rank e numero di nodi *(extra, non da slide)*
> Un albero la cui radice ha rank $r$ contiene almeno $2^r$ nodi.
> **Corollario.** Da $2^r \leq n$ segue $r \leq \log_2 n$: l'altezza è $O(\log n)$ e la `find` costa $O(\log n)$ — la stessa garanzia della union by size.

> [!info] Regola — perché il rank e non la size, quando c'è la compressione
> Senza compressione dei cammini le due euristiche sono **equivalenti**: entrambe danno altezza $O(\log n)$.
>
> Con la compressione la size non diventa *sbagliata* — il numero di elementi resta esatto — ma diventa un **cattivo indicatore dell'altezza**, che è l'uso che se ne fa. La compressione appiattisce l'albero senza togliergli un solo elemento: ci si ritrova un albero da $1000$ nodi ormai piatto e uno da $900$ ancora alto, e la union by size attaccherebbe il piatto sotto l'alto, cioè la mossa sbagliata.
>
> Il rank regge perché **la compressione può solo ridurre l'altezza vera, mai aumentarla**: un rank che era un limite superiore prima resta un limite superiore dopo, anche se diventa più lasco. Non lo si tiene aggiornato e stretto — serve solo che sia **monotono e valido**, e tanto basta perché l'analisi ammortizzata funzioni.
>
> In una riga: **la size misura quanti elementi ci sono, il rank stima quanto è alto l'albero — e la compressione cambia la seconda cosa senza toccare la prima.**
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
| $i=3$ | $16$ | torre di **16** esponenti $2$ | torre alta $A(3,2)$, cioè quanto la cella precedente | torre alta $A(3,3)$ |

> [!info] Come si legge — la tabella di $A(i,j)$
> **Convenzione**, dichiarata dalla slide prima della tabella: $a^{b^c}$ significa $a^{(b^c)}$, non $(a^b)^c$. Senza questa lettura le torri non hanno senso.
>
> La riga $i=2$ segue $A(2,j)=A(1,A(2,j-1))=2^{A(2,j-1)}$: ogni valore è $2$ elevato al precedente — $A(2,1)=4$, $A(2,2)=16$, $A(2,3)=65536$, $A(2,4)=2^{65536}$ (circa $2\times 10^{19727}$ cifre). In breve: **$A(2,k)$ è una torre di $k$ due**.
>
> La riga $i=3$ segue $A(3,j)=A(2,A(3,j-1))$: ogni cella è una **torre di due la cui altezza è la cella precedente**. Da $A(3,1)=16$ segue $A(3,2)=A(2,16)$, una torre di **16** due; poi $A(3,3)=A(2,A(3,2))$, alta quanto quel numero. Non è «più rapida» in senso quantitativo: cambia livello di operazione a ogni riga.

La **funzione inversa** $\alpha(m, n)$ è definita come:
$$\alpha(m, n) = \min\!\left\{i > 0 : A\!\left(i,\, \left\lfloor m/n \right\rfloor\right) > \log_2 n\right\}$$

> [!quote] Proprietà — $\alpha(m,n)$
> 1. Per $n$ fissato, $\alpha(m,n)$ è **monotonicamente decrescente** al crescere di $m$.
> 2. $\alpha(n,n) \to \infty$ per $n \to \infty$, ma con crescita **estremamente lenta**.

> [!info] Come si legge — perché $\alpha$ si tratta come una costante
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

> [!info] Regola — dove si paga il costo: QuickFind contro QuickUnion
> Le due strutture rappresentano lo stesso insieme in due modi opposti, e ciascuna sposta il costo su un'operazione diversa.
> - **QuickFind** tiene alberi di **altezza 1**: la `find` segue un solo puntatore ed è $O(1)$, ma la `union` deve rietichettare tutte le foglie di un insieme, quindi $O(n)$ nel caso peggiore. L'euristica **union by size** porta la union a $O(\log n)$ **ammortizzato**, lasciando l'altezza a 1 e la find a $O(1)$.
> - **QuickUnion** tiene alberi di **altezza variabile**: la `union` ricollega due radici ed è $O(1)$, ma la `find` risale un cammino, quindi $O(n)$ nel caso peggiore. L'euristica **union by size** porta la find a $O(\log n)$ nel caso peggiore, grazie al lemma $s \geq 2^h$; aggiungendo la **compressione dei cammini** si scende a $O(\alpha(m,n))$ ammortizzato.
>
> Nessuna delle due domina l'altra: la scelta dipende dal rapporto fra numero di `union` e numero di `find` nella sequenza.
## Applicazione: algoritmo di Kruskal
Il caso d'uso principale della struttura Union-Find è l'[[03 - Minimum Spanning Tree|algoritmo di Kruskal]] per il **Minimum Spanning Tree**. L'algoritmo ordina gli archi per peso crescente e aggiunge un arco $(u, v)$ all'albero solo se $u$ e $v$ appartengono a componenti connesse distinte — verifica realizzata tramite `find(u) != find(v)` — e poi esegue `union` per fondere le due componenti.

Con $n$ nodi e $m$ archi, Kruskal esegue:
- $n$ `makeSet`,
- $m$ `find` (due per ogni arco esaminato),
- al più $n-1$ `union`.

Con Union-Find ottimale (rank + path compression), il costo totale della gestione degli insiemi è $O(m \cdot \alpha(m, n))$, praticamente lineare.

> [!info] Collegamento — Modulo I
> La struttura Union-Find è un esempio avanzato di [[05 - Strutture Dati Elementari e Dizionari|struttura dati]] progettata per operazioni specifiche. L'analisi ammortizzata su sequenze di operazioni riprende il tipo di ragionamento visto per le [[07 - Code con Priorità e Heap|code con priorità]].

> [!info] Regola — la complessità di Kruskal si somma su tre voci, non su una
> Ogni domanda d'esame su «Kruskal implementato con \<struttura\>» si risolve sommando **tre** addendi e guardando quale domina:
> 1. **ordinamento** degli archi, $O(m\log m) = O(m\log n)$ — sparisce **solo** se la traccia dice che gli archi sono già ordinati;
> 2. **$O(m)$ find**, al costo della struttura scelta;
> 3. **$n-1$ union**, al costo della struttura scelta.
>
> L'errore che le tracce cercano è dimenticare il primo addendo: senza euristiche si risponde $O(n^2)$ guardando solo le union, mentre su grafo denso è l'ordinamento a dominare. Il secondo errore è credere che velocizzare la struttura velocizzi Kruskal: finché gli archi vanno ordinati, il costo resta $\Omega(m\log m)$ comunque.

→ **Palestra**: [[Esercizi 02 - Union-Find#Quale struttura, quali operazioni, come si usano|struttura, operazioni e uso in Kruskal — 19/02/2024, max 10 righe]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Kruskal con QuickFind senza euristica|QuickFind senza euristica — 13/06/2024]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Kruskal senza union by size con O(n^{3/2}) archi|$O(n^{3/2})$ archi — 27/09/2023, 1 riga]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Kruskal con QuickFind + union by size, archi già ordinati|QuickFind + ubs, archi ordinati — 18/02/2025]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Kruskal con QuickUnion + union by size, archi già ordinati|QuickUnion + ubs, archi ordinati — 16/07/2024]]

→ **Palestra**: [[Esercizi 02 - Union-Find#Kruskal con una Union-Find ipotetica|find $O(\log\log n)$ — 28/09/2022, max 5 righe]]
## Mappa nota ↔ slide
Riferimenti a `Materiale Didattico/Modulo II/Slide/02_Union_find_2025.pdf` (72 pagine), per studiare sulla slide tenendo la nota come riscontro. Il deck è **in italiano** e segue il Demetrescu, non Kleinberg-Tardos.

| Sezione della nota | Slide |
|---|---|
| Il problema Union-Find | **p. 2** (le tre operazioni) · p. 3 (esempio con $n=6$) · p. 4 (obiettivo) · **p. 5** (foresta di alberi radicati) · p. 6 (le due strategie) |
| QuickFind | **p. 7** (struttura: altezza 1) · **pp. 8-9** (realizzazione) · pp. 10-20 (demo passo-passo) · **p. 21** (complessità) · **p. 22** (union di costo lineare, $\Theta(n^2)$) |
| — Euristica union by size (QuickFind) | p. 23 (idea) · **p. 24** (union by size) · pp. 25-34 (demo) · **pp. 35-37** (realizzazione e tempo ammortizzato) · **p. 38** (complessità) · **p. 39** (la union che costa $\Theta(n)$) · **pp. 40-41** (analisi ammortizzata) |
| QuickUnion | p. 42 · **p. 43** (struttura: altezza $>1$) · **p. 44** (implementazioni) · pp. 45-51 (demo) · **p. 52** (complessità) · **p. 53** (find di costo lineare) |
| — Euristica union by size (QuickUnion) | p. 54 (idea) · **p. 55** (bilanciamento) · pp. 56-63 (demo) · **p. 64** (Lemma $s \geq 2^h$, lasciato come esercizio sulla slide) |
| — Euristica compressione dei cammini | **p. 65** (figura prima/dopo) |
| Analisi ottimale: la funzione inversa di Ackermann | **p. 66** (Tarjan & van Leeuwen) · **pp. 67-68** ($A(i,j)$ e la sua tabella) · **pp. 69-70** ($\alpha(m,n)$ e le sue proprietà) · **p. 71** ($\alpha \leq 4$) · **p. 72** (densità $m/n$ e $\log^*$) |
| Applicazione: algoritmo di Kruskal | — *(non in questo deck: le slide di Kruskal sono in `03_mst_2025.pdf`, pp. 13-15 e 29)* |

> [!info] Come si legge — metà del deck è animazione
> 35 pagine su 72 sono demo passo-passo delle stesse quattro sequenze (pp. 11-20, 25-34, 45-51, 56-63): scorrile in fila guardando come si trasformano gli alberi, non fermarti a leggerle una per una. Le pagine che contano davvero sono le nove in grassetto qui sopra.
