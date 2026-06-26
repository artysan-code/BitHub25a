---
tags:
  - algoritmi
  - heap
slide: "10"
capitolo: "Demetrescu cap. 8"
---
# Code con Priorità e Heap
Una **coda con priorità** è un tipo di dato astratto che generalizza la coda standard: anziché restituire gli elementi nell'ordine di arrivo, estrae sempre quello con **chiave minima** (o massima, a seconda della convenzione). Questa struttura è fondamentale in moltissimi algoritmi — dall'ordinamento ([[04 - Algoritmi di Ordinamento#Heap Sort|Heap Sort]]) al calcolo dei [[10 - Cammini Minimi e Dijkstra|cammini minimi con Dijkstra]] — e studiarne le implementazioni mostra perché le scelte strutturali impattano direttamente sulla complessità degli algoritmi che le usano.
## ADT CodaPriorità
> [!quote] Definizione — Coda con Priorità
> Una **coda con priorità** è una struttura dati che mantiene un insieme $S$ di $n$ elementi di tipo `elem`, ciascuno associato a una **chiave** presa da un dominio totalmente ordinato. Supporta le seguenti operazioni:
> - `findMin()` → restituisce l'elemento con chiave minima
> - `insert(elem e, chiave k)` → inserisce $e$ con chiave $k$
> - `delete(elem e)` → cancella $e$ da $S$ (richiede riferimento diretto all'elemento)
> - `deleteMin()` → cancella e restituisce il minimo
> - `decreaseKey(elem e, chiave d)` → decrementa di $d$ la chiave di $e$
> - `increaseKey(elem e, chiave d)` → incrementa di $d$ la chiave di $e$
> - `merge(CodaPriorità c1, CodaPriorità c2)` → restituisce $c_1 \cup c_2$

**Applicazioni principali:** gestione code in risorse condivise, scheduling di processi, algoritmi su grafi (Dijkstra, Prim), HeapSort, simulazione di eventi discreti.
## Implementazioni elementari
Prima di introdurre strutture avanzate conviene capire i limiti delle implementazioni banali. Le operazioni di base (`findMin`, `insert`, `delete`, `deleteMin`) si analizzano su quattro strutture semplici. La chiave del trade-off è: *tenere i dati ordinati* rende rapida l'estrazione ma lento l'inserimento, e viceversa.

> [!info] Ipotesi per delete in O(1)
> Il prof. Gualà assume che per `delete(e)` venga fornito un **riferimento diretto** all'elemento da cancellare. Questo permette di eliminarlo senza cercarlo prima.
### Array non ordinato
Si alloca un array di dimensione sufficiente e si tiene traccia di $n$ in una variabile.
- `findMin`: $\Theta(n)$ — bisogna scorrere tutti gli elementi
- `insert`: $O(1)$ — si aggiunge in fondo
- `delete`: $O(1)$ — si sovrascrive la posizione con l'ultimo elemento
- `deleteMin`: $\Theta(n)$ — si cerca il minimo in $\Theta(n)$, poi si cancella in $O(1)$
### Array ordinato
Si tiene l'array ordinato in ordine **decrescente** (il minimo sta in fondo).
- `findMin`: $O(1)$
- `insert`: $O(n)$ — posizione trovata in $\Theta(\log n)$ con ricerca binaria, ma gli spostamenti costano $O(n)$
- `delete`: $O(n)$ — richiede spostamenti
- `deleteMin`: $O(1)$ — basta rimuovere l'ultimo elemento
### Lista non ordinata
Lista bidirezionale; il riferimento diretto all'elemento rende `delete` immediato.
- `findMin`: $\Theta(n)$
- `insert`: $O(1)$ — in testa o in coda
- `delete`: $O(1)$ — aggiornamento puntatori
- `deleteMin`: $\Theta(n)$
### Lista ordinata
Lista bidirezionale ordinata in ordine crescente (il minimo è in testa).
- `findMin`: $O(1)$
- `insert`: $O(n)$ — trovare la posizione costa $O(n)$ (no accesso diretto), inserimento $O(1)$
- `delete`: $O(1)$
- `deleteMin`: $O(1)$
### Tabella riepilogativa — implementazioni elementari
Nessuna di queste strutture evita costi lineari. L'obiettivo delle implementazioni evolute è portare **tutte le operazioni** a costo al più logaritmico.

| Struttura | FindMin | Insert | Delete | DeleteMin | IncKey | DecKey | Merge |
|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Array non ord. | $\Theta(n)$ | $O(1)$ | $O(1)$ | $\Theta(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| Array ordinato | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| Lista non ord. | $\Theta(n)$ | $O(1)$ | $O(1)$ | $\Theta(n)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| Lista ordinata | $O(1)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
## d-Heap
> [!quote] Definizione — d-Heap
> Un **d-heap** è un albero radicato d-ario con le seguenti proprietà:
> 1. **Struttura**: è completo almeno fino al penultimo livello; le foglie sull'ultimo livello sono compattate verso sinistra.
> 2. **Contenuto informativo**: ogni nodo $v$ contiene un elemento `elem(v)` e una chiave `chiave(v)` da un dominio totalmente ordinato.
> 3. **Ordinamento parziale (min-heap)**: $\text{chiave}(v) \ge \text{chiave}(\text{parent}(v))$ per ogni nodo $v$ diverso dalla radice.

Un **heap binario** è il caso $d = 2$. Il concetto di FixHeap usato in [[04 - Algoritmi di Ordinamento|HeapSort]] è esattamente la procedura `muoviBasso` sui 2-heap.

> [!quote] Proprietà — d-Heap
> 1. Un d-heap con $n$ nodi ha altezza $\Theta(\log_d n)$.
> 2. La radice contiene l'elemento con chiave minima.
> 3. Può essere rappresentato implicitamente tramite **vettore posizionale** grazie alla proprietà di struttura.
### Rappresentazione con vettore posizionale
Un d-heap con $n$ nodi può essere memorizzato in un array senza puntatori espliciti, sfruttando la struttura quasi-completa. Con indici a partire da $1$ (convenzione del corso):
- **Radice**: posizione $1$
- **$j$-esimo figlio del nodo $i$** ($1 \le j \le d$): posizione $d(i-1) + 1 + j$
- **Padre del nodo $i$**: posizione $\lceil (i-1)/d \rceil$

Con indici a partire da $0$:
- **$j$-esimo figlio del nodo $i$** ($1 \le j \le d$): posizione $d \cdot i + j$
- **Padre del nodo $i$**: posizione $\lfloor (i-1)/d \rfloor$

Non sono necessari puntatori: la struttura è **implicita** nel vettore. Questo garantisce ottima *cache locality*.
### Procedure ausiliarie
Le due procedure seguenti ripristinano la proprietà di ordinamento a heap su un nodo che la violi.

**muoviAlto** (analogo a MoveUp):

```text
muoviAlto(heap T, nodo v)
1. while v ≠ radice(T) and chiave(v) < chiave(padre(v)) do
2.   scambia di posto v e padre(v) in T
3.   v = padre(v)
```

$T(n) = O(\log_d n)$ — si risale al massimo per tutta l'altezza dell'albero.

**muoviBasso** (analogo a FixHeap):

```text
muoviBasso(heap T, nodo v)
1. repeat
2.   sia u il figlio di v con chiave minima (se esiste)
3.   if v non ha figli or chiave(v) ≤ chiave(u) then break
4.   scambia di posto v e u in T
5.   v = u
```

$T(n) = O(d \log_d n)$ — ad ogni livello occorre confrontare $d$ figli per trovare il minimo.
### Operazioni e complessità
**findMin**

```text
findMin(heap T)
1. return elem(radice(T))
```

$T(n) = O(1)$ — la radice è il minimo per definizione.

**insert**

```text
insert(heap T, elem e, chiave k)
1. crea un nuovo nodo F con elem = e, chiave = k
2. aggiungi F come ultima foglia di T
3. muoviAlto(T, F)
```

$T(n) = O(\log_d n)$ — dominato da `muoviAlto`.

**delete e deleteMin**

```text
delete(heap T, nodo v)
1. scambia v con l'ultima foglia u di T
2. rimuovi v (ora in ultima posizione)
3. ripristina la proprietà di heap su u: muoviAlto(T, u) o muoviBasso(T, u)
```

$T(n) = O(\log_d n)$ oppure $O(d \log_d n)$ a seconda che si esegua `muoviAlto` o `muoviBasso`. `deleteMin` si implementa come `delete` sulla radice: costo $O(d \log_d n)$.

**decreaseKey**

```text
decreaseKey(heap T, nodo v, chiave d)
1. chiave(v) = chiave(v) - d
2. muoviAlto(T, v)
```

$T(n) = O(\log_d n)$.

**increaseKey**

```text
increaseKey(heap T, nodo v, chiave d)
1. chiave(v) = chiave(v) + d
2. muoviBasso(T, v)
```

$T(n) = O(d \log_d n)$.

> [!question] Domanda tipica d'esame — decreaseKey e increaseKey
> **D:** Perché `decreaseKey` usa `muoviAlto` e `increaseKey` usa `muoviBasso`?
> **R:** `decreaseKey` riduce una chiave, che potrebbe diventare inferiore a quella del padre, violando la proprietà dal basso verso l'alto → si corregge salendo con `muoviAlto`. `increaseKey` aumenta una chiave, che potrebbe superare quella di un figlio → si corregge scendendo con `muoviBasso`.
### Heapify — costruzione in O(n)
L'operazione `heapify` costruisce un heap d-ario da un array disordinato di $n$ elementi in tempo $O(n)$, molto più efficiente dei $n$ inserimenti successivi che costerebbero $O(n \log n)$.

L'idea generalizza `fixHeap` (vedi [[04 - Algoritmi di Ordinamento|HeapSort]]): si rendono heap ricorsivamente i $d$ sottoalberi della radice, poi si chiama `muoviBasso` sulla radice stessa. L'equazione di ricorrenza è:
$$T(n) = d \cdot T(n/d) + O(d \log_d n)$$
Per il **caso 1 del Teorema Master** ([[03 - Equazioni di Ricorrenza]]):
$$T(n) = \Theta(n)$$

> [!warning] Heapify vs inserimenti ripetuti
> Costruire un heap con $n$ inserimenti successivi costa $O(n \log n)$. `Heapify` bottom-up costa $O(n)$. La differenza è rilevante quando si costruisce la struttura una sola volta (come in HeapSort) e si vuole massimizzare l'efficienza della fase di costruzione.
### Merge con d-heap
Ci sono due approcci per fondere due d-heap $c_1$ e $c_2$:

1. **Costruire da zero** (generalizzazione di `heapify`): si crea un nuovo d-heap contenente tutti gli elementi di $c_1$ e $c_2$. Costo: $\Theta(n)$ dove $n = |c_1| + |c_2|$.
2. **Inserimenti ripetuti**: si inserisce ogni elemento della coda più piccola in quella più grande. Sia $k = \min\{|c_1|, |c_2|\}$ e $n = |c_1| + |c_2|$. Costo: $O(k \log n)$. Conviene quando $k = o(n/\log n)$.

> [!info] Limite del d-heap per merge
> In entrambi i casi il costo nel caso peggiore è $\Omega(n)$: i d-heap non permettono merge efficiente. Questo motiva lo studio degli heap binomiali.
### Quando conviene d > 2?
Aumentare $d$ riduce l'altezza dell'albero (da $\log_2 n$ a $\log_d n$), accelerando le operazioni che **salgono** (`insert`, `decreaseKey`). Tuttavia, ad ogni livello occorre confrontare $d$ figli, rallentando le operazioni che **scendono** (`deleteMin`, `muoviBasso`, `increaseKey`, `delete`).

> [!question] Domanda tipica d'esame — quando usare d > 2
> **D:** In quale scenario conviene usare un d-heap con $d > 2$?
> **R:** Quando le operazioni di salita (`insert`, `decreaseKey`) sono molto più frequenti delle operazioni di discesa (`deleteMin`, `increaseKey`). Esempio: nell'algoritmo di Dijkstra su grafi densi si eseguono molti più `decreaseKey` che `deleteMin`, quindi un 4-heap (o un heap di Fibonacci) migliora le prestazioni pratiche rispetto a un 2-heap.
## Heap Binomiali
L'obiettivo è implementare `merge` in tempo sublineare. Gli heap d-ari non lo permettono; gli **heap binomiali** lo garantiscono in $O(\log n)$.
### Alberi binomiali
> [!quote] Definizione — Albero Binomiale $B_i$
> Un **albero binomiale** $B_i$ è definito ricorsivamente:
> 1. $B_0$ consiste di un unico nodo.
> 2. Per $i > 0$, $B_{i+1}$ si ottiene fondendo due alberi $B_i$: la radice dell'uno diventa **figlia** della radice dell'altro (si sceglie come padre la radice con chiave minore, per rispettare l'ordinamento a heap).

> [!quote] Proprietà — Alberi Binomiali
> Per ogni $i \ge 0$:
> - **Numero di nodi**: $|B_i| = 2^i$
> - **Altezza**: $h(B_i) = i$
> - **Grado della radice**: $i$ (ha esattamente $i$ figli)
> - **Nodi al livello $k$**: $\binom{i}{k}$ (da cui il nome "binomiale")
> - **Sottoalberi della radice di $B_i$**: i figli sono $B_0, B_1, \ldots, B_{i-1}$

> [!example] Struttura degli alberi $B_0$–$B_3$
> $B_0$: nodo singolo. $B_1$: radice con un figlio ($B_0$). $B_2$: radice con due figli ($B_1$ e $B_0$). $B_3$: radice con tre figli ($B_2$, $B_1$, $B_0$). In $B_3$ il numero di nodi al livello $k$ è $\binom{3}{k}$: 1, 3, 3, 1.
### Definizione di heap binomiale
> [!quote] Definizione — Heap Binomiale
> Un **heap binomiale** è una **foresta** (collezione) di alberi binomiali con le seguenti proprietà:
> 1. **Unicità**: per ogni intero $i \ge 0$, esiste **al più** un $B_i$ nella foresta.
> 2. **Contenuto informativo**: ogni nodo $v$ contiene `elem(v)` e `chiave(v)` da un dominio totalmente ordinato.
> 3. **Ordinamento a heap**: $\text{chiave}(v) \ge \text{chiave}(\text{parent}(v))$ per ogni nodo $v$ diverso da una radice.

La proprietà di unicità stabilisce una corrispondenza diretta con la **rappresentazione binaria** di $n$: un heap binomiale di $n$ elementi è formato dagli alberi $B_{i_0}, B_{i_1}, \ldots, B_{i_h}$ dove $i_0, i_1, \ldots, i_h$ sono le posizioni degli $1$ nella rappresentazione binaria di $n$.

> [!example] Heap binomiale con n = 13 nodi
> $13 = 1101_2 = 2^3 + 2^2 + 2^0$. La foresta contiene $B_3$ (8 nodi), $B_2$ (4 nodi), $B_0$ (1 nodo). Il minimo globale è in una delle tre radici. Vi sono al massimo $\lfloor \log_2 13 \rfloor + 1 = 4$ alberi.

> [!quote] Proprietà — Topologiche degli Heap Binomiali
> In un heap binomiale con $n$ nodi:
> - vi sono **al più $\lfloor \log_2 n \rfloor + 1$ alberi** binomiali
> - ogni albero presente ha grado e altezza $O(\log n)$
### Rappresentazione collegata
Ogni nodo contiene: chiave, elemento, puntatore al padre, puntatore al primo figlio, puntatore al fratello successivo (in ordine decrescente di grado). La foresta è rappresentata come una lista delle radici ordinata per indice crescente.
### Procedura ausiliaria: ristruttura
La procedura `ristruttura` ripristina la proprietà di unicità fondendo coppie di $B_i$ con lo stesso grado, analogamente alla somma di due numeri binari con riporti.

```text
ristruttura(heap binomiale H)
1. i = 0
2. while esistono due B(i) nella foresta do
3.   sia T1, T2 i due B(i) con radici r1, r2
4.   if chiave(r1) ≤ chiave(r2) then poni r2 come figlio di r1
5.   else poni r1 come figlio di r2
6.   i = i + 1
```

$T(n)$: lineare nel numero di alberi binomiali in input (ogni fusione riduce di 1 il numero di alberi).

> [!info] Analogia con la somma binaria
> `merge` di due heap binomiali corrisponde esattamente alla **somma di due numeri binari**: ogni coppia di $B_i$ genera un "riporto" $B_{i+1}$. Questo è il motivo per cui il costo è $O(\log n)$ anziché $O(n)$.
### Operazioni sugli heap binomiali
**findMin**: si scorre la lista delle radici (al più $\lfloor \log_2 n \rfloor + 1$) e si restituisce il minimo. $T(n) = O(\log n)$.

**merge**: si fondono le due liste di radici in ordine crescente di grado, poi si chiama `ristruttura`. $T(n) = O(\log n)$ — analoga alla somma di due numeri binari di $O(\log n)$ bit.

**insert**: si crea un heap con un solo nodo ($B_0$) e si esegue `merge` con l'heap originale. $T(n) = O(\log n)$.

**deleteMin**:

```text
deleteMin(heap binomiale H)
1. trova la radice r con chiave minima (scorre le radici) in O(log n)
2. rimuovi r dalla lista delle radici di H
3. H' = heap binomiale formato dai figli di r (in ordine: B(h-1), ..., B(0))
4. return merge(H, H')
```

Rimuovendo la radice di $B_h$, i suoi $h$ figli $B_0, B_1, \ldots, B_{h-1}$ formano un nuovo heap binomiale. Si fonde con il resto dell'heap. $T(n) = O(\log n)$.

**decreaseKey**: si decrementa la chiave e si ripristina la proprietà di heap spingendo il nodo verso l'alto tramite scambi con il padre. $T(n) = O(\log n)$.

**increaseKey**: si chiama `delete(e)` poi `insert(e, k + d)`. $T(n) = O(\log n)$.

**delete**: si chiama `decreaseKey` con $-\infty$ per portare il nodo in cima, poi `deleteMin`. $T(n) = O(\log n)$.

> [!question] Domanda tipica d'esame — merge heap binomiali
> **D:** Perché merge di due heap binomiali costa $O(\log n)$ invece di $O(n)$ come per i d-heap?
> **R:** Negli heap binomiali le due foreste si fondono simulando la **somma binaria**: si scorrono le due liste di radici ($O(\log n)$ alberi in totale) e si fondono le coppie di $B_i$ con lo stesso grado, generando "riporti" verso gradi superiori. Ogni fusione richiede $O(1)$ e ci sono al più $O(\log n)$ fusioni totali.
>
> **D:** Quanti alberi binomiali può avere al massimo un heap binomiale con $n$ nodi?
> **R:** Al massimo $\lfloor \log_2 n \rfloor + 1$ alberi. Questo segue dalla proprietà di unicità e dalla corrispondenza con la rappresentazione binaria di $n$: ogni bit a $1$ nella rappresentazione corrisponde a un albero $B_i$ nella foresta.
## Heap di Fibonacci (cenni)
Gli **heap di Fibonacci** (Fredman, Tarjan 1987) si ottengono rilassando progressivamente la struttura degli heap binomiali in due passi:
- **Heap binomiale rilassato**: si rilassa la proprietà di **unicità** dei $B_i$ e si adotta un atteggiamento "pigro" (*lazy*) durante `insert` — anziché ristrutturare subito la foresta, si aggiunge il nuovo nodo e si rinvia la ristrutturazione.
- **Heap di Fibonacci**: si indebolisce anche la proprietà di **struttura** dei $B_i$, che non sono più necessariamente alberi binomiali.

L'analisi è **ammortizzata**: si divide il costo complessivo di una sequenza di operazioni per il numero di operazioni. Singole operazioni possono costare di più, ma la media su qualsiasi sequenza rispetta i limiti indicati. Questo differisce dal costo medio probabilistico: non c'è distribuzione di probabilità, l'algoritmo è deterministico.

> [!quote] Teorema — Heap di Fibonacci (Fredman-Tarjan)
> Usando un heap di Fibonacci, una qualsiasi sequenza di $n$ `insert`, $d$ `delete`, $f$ `findMin`, $m$ `deleteMin`, $\alpha$ `increaseKey`, $\delta$ `decreaseKey`, $\mu$ `merge` richiede tempo (nel caso peggiore):
> $$O\!\left(n + f + \mu + \delta + (d + m + \alpha)\log n\right)$$

In pratica: `insert`, `findMin`, `merge` e `decreaseKey` costano $O(1)$ ammortizzato; `delete` e `deleteMin` costano $O(\log n)$ ammortizzato.

> [!info] Applicazione — Dijkstra con heap di Fibonacci
> Nell'algoritmo di [[10 - Cammini Minimi e Dijkstra|Dijkstra]] su un grafo con $n$ nodi e $m$ archi si eseguono $n$ `insert`, $n$ `deleteMin` e fino a $m$ `decreaseKey`.
> - Con heap binario o binomiale: $O((n + m) \log n) = O(m \log n)$
> - Con heap di Fibonacci: $O(n \log n + m)$ — vantaggio sostanziale su grafi densi dove $m \gg n \log n$
## Tabella riassuntiva completa
Le complessità di d-Heap e Heap Binomiali sono nel **caso peggiore**; quelle con asterisco per Heap Fibonacci sono **ammortizzate**.

| Struttura | FindMin | Insert | Delete | DeleteMin | IncKey | DecKey | Merge |
|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Array non ord. | $\Theta(n)$ | $O(1)$ | $O(1)$ | $\Theta(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| Array ordinato | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| Lista non ord. | $\Theta(n)$ | $O(1)$ | $O(1)$ | $\Theta(n)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| Lista ordinata | $O(1)$ | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **d-Heap** (d cost.) | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(n)$ |
| **Heap Binomiale** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |
| **Heap Fibonacci** | $O(1)$ | $O(1)^*$ | $O(\log n)^*$ | $O(\log n)^*$ | $O(\log n)^*$ | $O(1)^*$ | $O(1)$ |

> [!warning] FindMin in heap binomiale
> A differenza dei d-heap (dove la radice è il minimo globale in $O(1)$), in un heap binomiale il minimo può essere in **qualsiasi** radice della foresta. Occorre scorrerle tutte: costo $O(\log n)$. Si può ottimizzare mantenendo un puntatore al minimo corrente.

> [!question] Domanda tipica d'esame — scelta della struttura
> **D:** Qual è la struttura più adatta se `merge` di code è un'operazione frequente?
> **R:** L'**heap binomiale**, che garantisce `merge` in $O(\log n)$ contro $O(n)$ di d-heap e liste. Se si accettano costi ammortizzati, l'heap di Fibonacci offre `merge` in $O(1)$ ammortizzato.
>
> **D:** Si vuole eseguire HeapSort su un array di $n$ elementi. Qual è la struttura e la complessità totale?
> **R:** Si usa un **2-heap** (heap binario) con `heapify` in $O(n)$ e poi $n$ estrazioni del minimo in $O(\log n)$ ciascuna: costo totale $O(n \log n)$. Vedi [[04 - Algoritmi di Ordinamento|HeapSort]].
