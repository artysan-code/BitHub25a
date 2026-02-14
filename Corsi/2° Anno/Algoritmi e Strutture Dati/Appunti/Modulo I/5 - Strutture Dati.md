> [!abstract] Tipi di Dato vs Strutture Dati
> - **Tipo di Dato Astratto (ADT):** Specifica _cosa_ è una collezione di dati e quali operazioni supporta (es. `insert`, `delete`, `search`), senza dire _come_ è implementata.
> - **Struttura Dati:** L'implementazione concreta (es. array, lista concatenata, albero) che organizza i dati in memoria per supportare le operazioni dell'ADT in modo efficiente.
> 
> **Obiettivo:** Progettare strutture dati che minimizzano le risorse di calcolo (tempo e spazio) necessarie per le operazioni richieste.

## 1. Strutture Dati Elementari
### Pila (Stack)
> [!definition] LIFO (Last In First Out)
> L'ultimo elemento inserito è il primo ad essere estratto.
> 
> **Operazioni Principali:**
> - `push(e)`: Inserisce l'elemento `e` in cima.
> - `pop()`: Rimuove e restituisce l'elemento in cima.
> - `top()`: Legge l'elemento in cima senza rimuoverlo.

|Implementazione|Spazio|Push|Pop|Note|
|:--|:-:|:-:|:-:|:--|
|**Array (Dim. fissa)**|$O(n)$|$O(1)$|$O(1)$|Limite dimensione prefissato.|
|**Array Dinamico**|$O(n)$|$O(1)$*|$O(1)$|*Ammortizzato con raddoppio.|
|**Lista Concatenata**|$O(n)$|$O(1)$|$O(1)$|Nessun limite di dimensione.|

### Coda (Queue)
> [!definition] FIFO (First In First Out)
> Il primo elemento inserito è il primo ad essere estratto.
> 
> **Operazioni Principali:**
> - `enqueue(e)`: Inserisce `e` in coda.
> - `dequeue()`: Rimuove e restituisce l'elemento in testa.
> - `first()`: Legge l'elemento in testa senza rimuoverlo.

| Implementazione       | Spazio | Enqueue | Dequeue | Note                       |
| :-------------------- | :----: | :-----: | :-----: | :------------------------- |
| **Array Circolare**   | $O(n)$ | $O(1)$  | $O(1)$  | Usa indici modulo $n$.     |
| **Lista Concatenata** | $O(n)$ | $O(1)$  | $O(1)$  | Puntatori `head` e `tail`. |

### Dizionario
> [!definition] Tipo di Dato Dizionario
> Mantiene un insieme di elementi identificati da una **chiave**.
> 
> **Operazioni:**
> - `insert(e, k)`: Aggiunge l'elemento `e` con chiave `k`.
> - `delete(k)`: Rimuove l'elemento con chiave `k`.
> - `search(k)`: Restituisce l'elemento con chiave `k` (o `null` se non presente).

| Implementazione        |   Search    |   Insert    |   Delete    | Note                                               |
| :--------------------- | :---------: | :---------: | :---------: | :------------------------------------------------- |
| **Array Non Ordinato** |   $O(n)$    |   $O(1)$    |   $O(n)$    | Insert in coda. Delete richiede search.            |
| **Array Ordinato**     | $O(\log n)$ |   $O(n)$    |   $O(n)$    | Ricerca binaria. Shift costoso.                    |
| **Lista Non Ordinata** |   $O(n)$    |   $O(1)$    |   $O(n)$    | Insert in testa. Non permette ricerca binaria.     |
| **Lista Ordinata**     |   $O(n)$    |   $O(n)$    |   $O(n)$    | Non permette ricerca binaria (no accesso diretto). |
| **AVL**                | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Ottimo compromesso (vedi sezione BST/AVL).         |

> [!note] Confronto Array vs Lista
> - **Array:** Accesso diretto O(1), ma inserimento/cancellazione richiedono shift O(n)
> - **Lista:** Inserimento/cancellazione O(1) se si ha il puntatore, ma no accesso diretto

## 2. Alberi e Rappresentazioni
> [!info] Definizioni Base
> - **Radice (Root):** Nodo senza padre.
> - **Foglia (Leaf):** Nodo senza figli.
> - **Nodo Interno:** Nodo con almeno un figlio.
> - **Grado:** Numero di figli di un nodo.
> - **Livello:** Distanza dalla radice (radice ha livello 0).
> - **Altezza:** Massima distanza tra radice e foglie (altezza albero vuoto = -1).
> - **Profondità di un nodo:** Distanza dalla radice.

### Tecniche di Rappresentazione
Come memorizzare la topologia di un albero in memoria.

| Rappresentazione        | Struttura                                   | Padre(u) | Figlio $i$-esimo | Ideale per                        |
| :---------------------- | :------------------------------------------ | :------: | :--------------: | :-------------------------------- |
| **Vettore dei Padri**   | Array $P$ dove $P[i]$ è il padre di $i$     |  $O(1)$  |      $O(n)$      | Algoritmi bottom-up (Union-Find)  |
| **Vettore Posizionale** | Nodi in array per livelli (radice in 1)     |  $O(1)$  |      $O(1)$      | Alberi quasi completi (Heap)      |
| **Puntatori ai Figli**  | Ogni nodo ha array/lista di puntatori figli | $O(1)$*  |      $O(1)$      | Alberi generici o binari standard |

*Richiede puntatore `parent` esplicito nel nodo per accesso al padre in $O(1)$.

### Visite di Alberi
Algoritmi per accedere sistematicamente a tutti i nodi. Costo: $O(n)$ per $n$ nodi.

> [!code] DFS - Visita in Profondità
> Usa uno **Stack** (o ricorsione implicita).
> 
> **Tre ordini possibili (per alberi binari):**
> - **Pre-ordine:** Radice → Sinistro → Destro
> - **Simmetrica (In-order):** Sinistro → Radice → Destro _(ordina i BST!)_
> - **Post-ordine:** Sinistro → Destro → Radice _(utile per cancellazione o calcolo altezza)_
> 
> **Pseudocodice Ricorsivo (Pre-ordine):**
> ```text
> DFS-Preorder(nodo u)
> 1. if u ≠ null then
> 2.   visita(u)
> 3.   DFS-Preorder(figlio_sinistro(u))
> 4.   DFS-Preorder(figlio_destro(u))
> ```
> 
> **Pseudocodice Iterativo (con Stack):**
> ```text
> DFS-Iterativo(radice r)
> 1. S = Stack vuoto
> 2. push(S, r)
> 3. while S non vuoto do
> 4.   u = pop(S)
> 5.   visita(u)
> 6.   if figlio_destro(u) ≠ null then push(S, figlio_destro(u))
> 7.   if figlio_sinistro(u) ≠ null then push(S, figlio_sinistro(u))
> ```

> [!code] BFS - Visita in Ampiezza
> Usa una **Coda**. Visita i nodi livello per livello (distanza crescente dalla radice).
> 
> **Pseudocodice:**
> ```text
> BFS(radice r)
> 8. Q = Coda vuota
> 9. enqueue(Q, r)
> 10. while Q non vuota do
> 11.   u = dequeue(Q)
> 12.   visita(u)
> 13.   for each figlio v di u do
> 14.     enqueue(Q, v)
> ```

> [!note] Quando Usare DFS vs BFS
> - **DFS:** Quando serve esplorazione profonda (es. trovare cammini, topological sort)
> - **BFS:** Quando serve distanza minima, livelli, o elaborazione per livello
> - **In-order (DFS simmetrica):** Per stampare BST in ordine crescente

## 3. Code con Priorità - Introduzione
> [!definition] Coda con Priorità (ADT)
> Una struttura dati che mantiene un insieme $S$ di elementi, ciascuno con una **chiave** (priorità).
> 
> **Operazioni Base:**
> - `insert(e, k)`: Inserisce un elemento con priorità $k$.
> - `findMin()` / `findMax()`: Restituisce l'elemento con priorità minima/massima.
> - `deleteMin()` / `deleteMax()`: Rimuove e restituisce il minimo/massimo.
> - `delete(e)`: Rimuove un elemento specifico.
> - `decreaseKey(x, k)` / `increaseKey(x, k)`: Aggiorna la priorità di un elemento.
> - `merge(Q1, Q2)`: Fonde due code con priorità.

> [!success] Applicazioni Pratiche
> - Gestione code in risorse condivise (scheduler CPU)
> - Gestione priorità in processi concorrenti
> - Algoritmi su grafi: Dijkstra, Prim (MST)
> - Ordinamento: HeapSort
> - Simulazione eventi discreti

## 4. Heap Binari
### Definizione e Proprietà
> [!info] Proprietà Fondamentali
> Un **Heap Binario** è un albero binario che soddisfa due proprietà:
> 1. **Proprietà Strutturale:** È un albero binario **quasi completo**
>     - Tutti i livelli sono pieni tranne l'ultimo
>     - L'ultimo livello è riempito da sinistra a destra
>     - _Conseguenza:_ Altezza $h = \lfloor \log_2 n \rfloor$
> 2. **Proprietà di Ordinamento:**
>     - **Max-Heap:** Per ogni nodo $v \neq \text{radice}$: $\text{key}(\text{parent}(v)) \ge \text{key}(v)$ → Il **massimo** è nella radice
>     - **Min-Heap:** Per ogni nodo $v \neq \text{radice}$: $\text{key}(\text{parent}(v)) \le \text{key}(v)$ → Il **minimo** è nella radice

### Rappresentazione (Vettore Posizionale)
Grazie alla struttura quasi completa, **non servono puntatori**. Si usa un array `A`.

> [!note] Formule per gli Indici
> Gli indici dipendono dalla base scelta (0 o 1):
> 
> |Relazione|Indici Base 1|Indici Base 0|
> |:--|:-:|:-:|
> |**Radice**|`1`|`0`|
> |**Figlio Sinistro di i**|`2*i`|`2*i + 1`|
> |**Figlio Destro di i**|`2*i + 1`|`2*i + 2`|
> |**Padre di i**|`⌊i/2⌋`|`⌊(i-1)/2⌋`|

**Convenzione del prof:** Usa base 1 (A[1..n])

### Operazioni e Implementazione (Max-Heap)
#### 1. FixHeap (Heapify-Down)
> [!tip] Idea
> Ripristina la proprietà heap se violata in un nodo `i`, **assumendo** che i sottoalberi sinistro e destro siano già heap validi.
> 
> Fa "scendere" l'elemento fuori posto scambiandolo con il figlio maggiore, finché la proprietà è ripristinata.

> [!code] Pseudocodice FixHeap (A[1..n])
> ```text
> fixHeap(A, i, heapsize)
> 1. s = 2*i
> 2. d = 2*i + 1
> 3. if s <= heapsize and A[s] > A[i] then massimo = s
> 4. else massimo = i
> 5. if d <= heapsize and A[d] > A[massimo] then massimo = d
> 6. if massimo ≠ i then
> 7.   scambia A[i] con A[massimo]
> 8.   fixHeap(A, massimo, heapsize)
> ```

> [!success] Complessità
> $T(n) = O(\log n)$ - scende al massimo fino alle foglie (altezza dell'albero)

#### 2. Heapify (Costruzione Bottom-Up)
> [!tip] Idea
> Costruisce un heap partendo da un array disordinato.
> 
> Strategia: Chiama `fixHeap` su tutti i nodi interni, **dal basso verso l'alto** (dall'ultimo nodo interno verso la radice).

> [!code] Pseudocodice Heapify (Iterativo)
> ```text
> heapify(A, n)
> 1. heapsize[A] = n
> 2. for i = ⌊n/2⌋ downto 1 do
> 3.   fixHeap(A, i, n)
> ```

> [!success] Complessità
> **$T(n) = O(n)$** - NON $O(n \log n)$!
> 
> **Dimostrazione intuitiva:**
> - La maggior parte dei nodi sono vicini alle foglie (altezza bassa)
> - Pochi nodi hanno altezza alta
> - Somma pesata: $\sum_{h=0}^{\log n} \frac{n}{2^{h+1}} \cdot h = O(n)$

#### 3. Insert
> [!tip] Idea
> Inserisce un nuovo elemento mantenendo la proprietà heap.
> 
> Strategia: Aggiungi in fondo (come foglia più a destra), poi fallo "salire" (MoveUp) finché la proprietà è soddisfatta.

> [!code] Pseudocodice Insert
> ```text
> insert(A, x)
> 1. heapsize[A] = heapsize[A] + 1
> 2. A[heapsize[A]] = x
> 3. MoveUp(A, heapsize[A])
> 
> MoveUp(A, i)
> 4. while i > 1 and A[⌊i/2⌋] < A[i] do
> 5.   scambia A[i] con A[⌊i/2⌋]
> 6.   i = ⌊i/2⌋
> ```

> [!success] Complessità
> $T(n) = O(\log n)$ - sale al massimo dalla foglia alla radice

#### 4. ExtractMax (DeleteMax)
> [!tip] Idea
> Rimuove e restituisce la radice (elemento massimo).
> 
> Strategia:
> 1. Copia l'ultima foglia (A[heapsize]) nella radice
> 2. Decrementa heapsize
> 3. Ripristina la proprietà con FixHeap sulla radice

> [!code] Pseudocodice ExtractMax
> ```text
> extractMax(A)
> 4. if heapsize[A] < 1 then error "heap vuoto"
> 5. max = A[1]
> 6. A[1] = A[heapsize[A]]
> 7. heapsize[A] = heapsize[A] - 1
> 8. fixHeap(A, 1, heapsize[A])
> 9. return max
> ```

> [!success] Complessità
> $T(n) = O(\log n)$ - dominato da FixHeap

#### 5. IncreaseKey (per Max-Heap)
> [!tip] Idea
> Aumenta la chiave di un elemento in posizione `i`. Dopo l'aumento, l'elemento potrebbe violare la proprietà heap verso l'alto → fallo salire.

> [!code] Pseudocodice IncreaseKey
> ```text
> increaseKey(A, i, newKey)
> 1. if newKey < A[i] then error "nuova chiave minore della corrente"
> 2. A[i] = newKey
> 3. MoveUp(A, i)
> ```

> [!success] Complessità
> $T(n) = O(\log n)$

### Riepilogo Complessità Heap Binario
|Operazione|Complessità|
|:--|:-:|
|Heapify (Costruzione)|$O(n)$|
|FixHeap|$O(\log n)$|
|Insert|$O(\log n)$|
|ExtractMax/Min|$O(\log n)$|
|FindMax/Min|$O(1)$|
|IncreaseKey / DecreaseKey|$O(\log n)$|
|Delete|$O(\log n)$|

## 5. d-ary Heap
> [!definition] Generalizzazione
> Un **d-ary Heap** è un heap in cui ogni nodo ha **fino a $d$ figli** (invece di 2).
> 
> - Albero $d$-ario quasi completo
> - Stessa proprietà di ordinamento (max-heap o min-heap)
> - Altezza: $h = \Theta(\log_d n)$

### Formule per gli Indici
> [!note] Relazioni Padre-Figli
> **Base 0:**
> - Figlio $j$-esimo di $i$ (con $j \in \{1, 2, \ldots, d\}$): $d \cdot i + j$
> - Padre di $i$: $\lfloor (i-1)/d \rfloor$
> 
> **Base 1:**
> - Figlio $j$-esimo di $i$: $d(i-1) + j + 1$
> - Padre di $i$: $\lfloor (i-2)/d \rfloor + 1$

### Performance
> [!success] Complessità Operazioni
> 
> |Operazione|Complessità|
> |:--|:-:|
> |Insert / IncreaseKey|$O(\log_d n)$ - salita più corta|
> |ExtractMax / FixHeap|$O(d \log_d n)$ - scelta tra $d$ figli|
> |Heapify|$O(n)$ - indipendente da $d$|

> [!tip] Quando Usare d-ary Heap
> Conviene aumentare $d$ quando:
> - Le operazioni `insert` e `increaseKey` sono **molto più frequenti** di `extractMax`
> - L'altezza diminuisce ($\log_d n$) → salite più veloci
> - Ma attenzione: FixHeap costa $O(d)$ per ogni livello (cerca il massimo tra $d$ figli)

> [!example] Esempio
> Con $d = 4$ e operazioni 90% insert, 10% extractMax → d-ary heap conviene!

## 6. Alberi Binari di Ricerca (BST)
> [!definition] Binary Search Tree (BST)
> Un albero binario dove **per ogni nodo $u$**:
> - Tutte le chiavi nel **sottoalbero sinistro** $\le$ `key(u)`
> - Tutte le chiavi nel **sottoalbero destro** $>$ `key(u)`
> 
> Questa proprietà vale ricorsivamente per ogni sottoalbero.

> [!info] Proprietà Chiave
> **Visita in ordine simmetrico (in-order) di un BST produce le chiavi in ordine crescente!**
> ```text
> In-Order(u):
>   if u ≠ null:
>     In-Order(figlio_sinistro(u))
>     stampa key(u)
>     In-Order(figlio_destro(u))
> ```

### Operazioni Base
#### 1. Search (Ricerca)
> [!tip] Idea
> Scendi nell'albero confrontando la chiave cercata con quella del nodo corrente:
> - Se $k <$ `key(u)`: vai a sinistra
> - Se $k >$ `key(u)`: vai a destra
> - Se $k =$ `key(u)`: trovato!

> [!code] Pseudocodice Search
> ```text
> search(BST T, chiave k)
> 1. u = T.root
> 2. while u ≠ null and k ≠ key(u) do
> 3.   if k < key(u) then u = figlio_sinistro(u)
> 4.   else u = figlio_destro(u)
> 5. return u
> ```

> [!success] Complessità
> - **Caso medio:** $O(\log n)$ - albero bilanciato
> - **Caso peggiore:** $O(n)$ - albero degenere (lista)

#### 2. Min e Max
> [!tip] Idea
> - **Minimo:** Scendi sempre a sinistra fino alla foglia
> - **Massimo:** Scendi sempre a destra fino alla foglia

> [!code] Pseudocodice Min
> ```text
> min(BST T)
> 1. u = T.root
> 2. while figlio_sinistro(u) ≠ null do
> 3.   u = figlio_sinistro(u)
> 4. return u
> ```

> [!success] Complessità
> $O(h)$ dove $h$ è l'altezza dell'albero

#### 3. Successor e Predecessor
> [!definition] Definizioni
> - **Successore di $u$:** Nodo $v$ con **minima chiave** $>$ `key(u)`
> - **Predecessore di $u$:** Nodo $v$ con **massima chiave** $<$ `key(u)`

> [!tip] Come Trovare il Successore
> **Caso 1:** Se $u$ ha figlio destro
> - Successor($u$) = `min(figlio_destro(u))`
> 
> **Caso 2:** Se $u$ NON ha figlio destro
> - Risali finché sei figlio sinistro
> - Il successore è il primo antenato di cui sei nel sottoalbero sinistro

> [!code] Pseudocodice Successor
> ```text
> successor(u)
> 1. if figlio_destro(u) ≠ null then
> 2.   return min(figlio_destro(u))
> 3. y = parent(u)
> 4. while y ≠ null and u == figlio_destro(y) do
> 5.   u = y
> 6.   y = parent(y)
> 7. return y
> ```

> [!note] Predecessor
> Simmetrico al successore: usa sottoalbero sinistro e `max` invece di `min`.

#### 4. Insert (Inserimento)
> [!tip] Idea
> Simula una ricerca per trovare dove dovrebbe stare l'elemento, poi inseriscilo come foglia in quella posizione.

> [!code] Pseudocodice Insert
> ```text
> insert(BST T, elem e, chiave k)
> 1. z = crea nuovo nodo con elem=e, key=k
> 2. y = null
> 3. x = T.root
> 4. while x ≠ null do
> 5.   y = x
> 6.   if k < key(x) then x = figlio_sinistro(x)
> 7.   else x = figlio_destro(x)
> 8. parent(z) = y
> 9. if y == null then T.root = z
> 10. else if k < key(y) then figlio_sinistro(y) = z
> 11. else figlio_destro(y) = z
> ```

> [!success] Complessità
> $O(h)$ - dominato dalla discesa nell'albero

> [!info] Correttezza
> Dopo l'inserimento, la proprietà BST è mantenuta: per costruzione, ogni antenato di $z$ si ritrova $z$ nel sottoalbero corretto.

#### 5. Delete (Cancellazione)
> [!warning] Operazione Più Complessa
> La cancellazione ha **3 casi** da gestire, a seconda del numero di figli del nodo da cancellare.

> [!tip] I 3 Casi
> **Caso 1: Nodo Foglia (0 figli)**
> - Cancella direttamente il nodo
> - Aggiorna il puntatore del padre a `null`
> 
> **Caso 2: Nodo con 1 Figlio**
> - "Bypassa" il nodo
> - Collega il padre direttamente all'unico figlio
> 
> **Caso 3: Nodo con 2 Figli**
> - Trova il **successore** $s$ (minimo del sottoalbero destro)
> - Copia `key(s)` ed `elem(s)` nel nodo da cancellare
> - Cancella $s$ (che ha al più 1 figlio destro) → ricorsione sul Caso 1 o 2

> [!code] Pseudocodice Delete (semplificato)
> ```text
> delete(BST T, nodo z)
> 1. if z è foglia then
> 2.   rimuovi z e aggiorna parent(z)
> 3. else if z ha 1 solo figlio then
> 4.   collega parent(z) con l'unico figlio di z
> 5.   rimuovi z
> 6. else  // z ha 2 figli
> 7.   s = successor(z)  // min del sottoalbero destro
> 8.   copia key(s) ed elem(s) in z
> 9.   delete(T, s)  // s ha al più figlio destro
> ```

> [!success] Complessità
> $O(h)$ - ricerca + eventuale ricerca successore

> [!example] Esempio Caso 3
> Cancellare 15 da questo BST:
> ```
>        15
>       /  \
>      6    18
>     / \   / \
>    3   8 17  20
> ```
> 10. Trova successor(15) = 17 (minimo sottoalbero destro)
> 11. Sostituisci 15 con 17
> 12. Cancella il vecchio nodo 17 (che è foglia)
> ```
>        17
>       /  \
>      6    18
>     / \     \
>    3   8    20
> ```

### Riepilogo Complessità BST
|Operazione|Caso Medio|Caso Peggiore|
|:--|:-:|:-:|
|Search|$O(\log n)$|$O(n)$|
|Insert|$O(\log n)$|$O(n)$|
|Delete|$O(\log n)$|$O(n)$|
|Min / Max|$O(\log n)$|$O(n)$|
|Successor / Predecessor|$O(\log n)$|$O(n)$|

> [!warning] Problema del BST
> Se inseriamo elementi **già ordinati** (es. 1, 2, 3, 4, 5), l'albero degenera in una **lista**:
> ```
> 1
>  \
>   2
>    \
>     3
>      \
>       4
>        \
>         5
> ```
> Altezza $h = n$ → tutte le operazioni degradano a $O(n)$!
> 
> **Soluzione:** Alberi bilanciati (AVL, Red-Black Trees)

## 7. Alberi AVL (Alberi Bilanciati)
> [!definition] Alberi AVL
> Un **BST** è **AVL** se per **ogni** nodo $v$, il **fattore di bilanciamento** soddisfa:
> $$\beta(v) = h(\text{sottoalbero sinistro di } v) - h(\text{sottoalbero destro di } v) \in \{-1, 0, +1\}$$
> 
> Dove $h(\text{albero vuoto}) = -1$ per convenzione.

> [!success] Garanzia Fondamentale
> **Teorema:** Un albero AVL con $n$ nodi ha altezza $h = O(\log n)$.
> 
> **Conseguenza:** Tutte le operazioni (search, insert, delete) costano $O(\log n)$ garantito!

> [!info] Mantenimento del Bilanciamento
> Generalmente $\beta(v)$ è mantenuto come **informazione addizionale** nel record di ogni nodo (oppure si memorizza l'altezza del sottoalbero).

### Fattore di Bilanciamento
> [!note] Interpretazione
> - $\beta(v) = +1$: sottoalbero sinistro più alto di 1
> - $\beta(v) = 0$: sottoalberi bilanciati
> - $\beta(v) = -1$: sottoalbero destro più alto di 1
> - $|\beta(v)| = 2$: **SBILANCIATO** → serve ribilanciamento!

> [!example] Esempi
> ```
>      15           ← β = 0
>     /  \
>    6    18        ← β(6) = 0, β(18) = -1
>   / \     \
>  3   8    20      ← tutti β ∈ {-1,0,+1} → AVL ✓
> ```
> ```
>      20           ← β = +2 → NON AVL! ✗
>     /
>    17
>   /
>  16
> ```

### Ribilanciamento tramite Rotazioni
> [!warning] Quando Serve Ribilanciare
> Dopo un `insert` o `delete`, se un nodo $v$ ha $|\beta(v)| = 2$, dobbiamo applicare rotazioni.
> 
> **Nodo Critico:** Il nodo più profondo con $|\beta(v)| = 2$

> [!info] I 4 Casi di Rotazione
> A seconda della **direzione dello sbilanciamento**, abbiamo 4 casi (simmetrici a coppie):
> 
> |Caso|β(v)|Sottocaso|Rotazione|
> |:--|:-:|:--|:--|
> |**SS** (Sinistra-Sinistra)|$+2$|Sbilanciamento nel sottoalbero sinistro del figlio sinistro|Rotazione semplice **DESTRA**|
> |**DD** (Destra-Destra)|$-2$|Sbilanciamento nel sottoalbero destro del figlio destro|Rotazione semplice **SINISTRA**|
> |**SD** (Sinistra-Destra)|$+2$|Sbilanciamento nel sottoalbero destro del figlio sinistro|Rotazione **DOPPIA** (sx su figlio, dx su v)|
> |**DS** (Destra-Sinistra)|$-2$|Sbilanciamento nel sottoalbero sinistro del figlio destro|Rotazione **DOPPIA** (dx su figlio, sx su v)|

### Rotazione Semplice (Destra su v)
> [!code] Pseudocodice Rotazione Destra
> ```text
> rotazioneDestra(v)
> 1. u = figlio_sinistro(v)
> 2. figlio_sinistro(v) = figlio_destro(u)
> 3. if figlio_destro(u) ≠ null then
> 4.   parent(figlio_destro(u)) = v
> 5. parent(u) = parent(v)
> 6. if parent(v) == null then root = u
> 7. else if v == figlio_sinistro(parent(v)) then
> 8.   figlio_sinistro(parent(v)) = u
> 9. else figlio_destro(parent(v)) = u
> 10. figlio_destro(u) = v
> 11. parent(v) = u
> 12. aggiorna β(v) e β(u)
> ```

> [!success] Proprietà Rotazioni
> - **Mantengono la proprietà BST** (ordine delle chiavi preservato)
> - **Costo:** $O(1)$ - solo aggiornamenti puntatori locali
> - **Aggiornamento β:** $O(1)$ - solo i nodi coinvolti cambiano

> [!note] Rotazione Sinistra
> Simmetrica alla rotazione destra (scambia "sinistro" ↔ "destro")

### Caso SS (Sinistra-Sinistra)
> [!example] Esempio Caso SS
> ```
> Sbilanciamento:          Dopo rotazione destra su v:
>       v (β=+2)                    u (β=0)
>      /                           / \
>     u (β≥0)         →          T1  v (β=0)
>    / \                             / \
>   T1  T2                          T2  T3
>       /
>      T3
> ```
> **Applicazione:** Rotazione semplice **DESTRA** su $v$

> [!info] Osservazioni Importanti
> - **Insert:** Provoca solo il sottocaso dove l'altezza dell'albero diminuisce → **1 rotazione basta**
> - **Delete:** Può provocare entrambi i sottocasi → altezza potrebbe non diminuire → sbilanciamento si propaga

### Caso DD (Destra-Destra)
> [!example] Esempio Caso DD
> ```
> Sbilanciamento:          Dopo rotazione sinistra su v:
>    v (β=-2)                    u (β=0)
>     \                         / \
>      u (β≤0)      →          v   T3
>     / \                     / \
>    T2  T3                  T1  T2
>   /
>  T1
> ```
> **Applicazione:** Rotazione semplice **SINISTRA** su $v$

### Caso SD (Sinistra-Destra)
> [!tip] Strategia
> Lo sbilanciamento è "a zigzag" → serve rotazione **DOPPIA**:
> 1. Prima rotazione **SINISTRA** sul figlio sinistro di $v$ (nodo $z$)
> 2. Poi rotazione **DESTRA** su $v$

> [!example] Esempio Caso SD
> ```
> Sbilanciamento:               Dopo rotazione sx su z:        Dopo rotazione dx su v:
>       v (β=+2)                       v (β=+2)                      w (β=0)
>      /                              /                            /   \
>     z (β=-1)         →             w (β=+1)         →           z     v
>    / \                            /                            / \   / \
>   T1  w                          z                           T1 T2 T3 T4
>      / \                        / \
>     T2  T3                     T1  T2
>        /                              \
>       T4                               T3
>                                       /
>                                      T4
> ```
> **Applicazione:**
> 1. RotazioneSinistra(z)
> 2. RotazioneDestra(v)

### Caso DS (Destra-Sinistra)
> [!example] Esempio Caso DS
> Simmetrico al caso SD:
> 1. Prima rotazione **DESTRA** sul figlio destro di $v$
> 2. Poi rotazione **SINISTRA** su $v$

### Operazioni AVL
#### Insert
> [!tip] Strategia Insert AVL
> 1. Inserisci come in un BST normale (come foglia)
> 2. Risali verso la radice aggiornando i fattori di bilanciamento
> 3. Trova il **primo** nodo critico $v$ (con $|\beta(v)| = 2$)
> 4. Determina il caso (SS, DD, SD, DS) e applica la rotazione appropriata

> [!code] Pseudocodice Insert AVL
> ```text
> insert(AVL T, elem e, chiave k)
> 1. Crea nuovo nodo z con elem=e, key=k
> 2. Inserisci z come in un BST
> 3. Ricalcola β dei nodi nel cammino da z alla radice
> 4. Sia v il più profondo nodo con β(v) = ±2 (nodo critico)
> 5. if v esiste then
> 6.   Determina il caso (SS/DD/SD/DS)
> 7.   Esegui la rotazione opportuna su v
> ```

> [!success] Complessità Insert
> $O(\log n)$:
> - Inserimento BST: $O(\log n)$
> - Ricalcolo β: $O(\log n)$ nodi nel cammino
> - Rotazione: $O(1)$
> - **Numero rotazioni:** Al massimo **1** (semplice o doppia)

> [!note] Perché 1 Rotazione Basta per Insert
> Dopo la rotazione, l'altezza del sottoalbero ruotato torna uguale a quella che aveva **prima** dell'inserimento → nessun altro nodo si sbilancia verso l'alto.

#### Delete
> [!tip] Strategia Delete AVL
> 1. Cancella come in un BST normale (3 casi)
> 2. Ricalcola β del padre del nodo eliminato fisicamente
> 3. Se $|\beta| = 2$, applica rotazione
> 4. **Continua a risalire** verso la radice controllando β ad ogni livello
> 5. Applica rotazioni se necessario fino alla radice

> [!code] Pseudocodice Delete AVL
> ```text
> delete(AVL T, elem e)
> 6. Cancella il nodo come in un BST
> 7. u = padre del nodo eliminato fisicamente
> 8. while u ≠ null do
> 9.   Ricalcola β(u)
> 10.   if |β(u)| == 2 then
> 11.     Determina il caso e applica rotazione su u
> 12.     if l'altezza del sottoalbero di u è uguale a prima then
> 13.       break  // terminazione anticipata
> 14.   u = parent(u)
> ```

> [!success] Complessità Delete
> $O(\log n)$:
> - Cancellazione BST: $O(\log n)$
> - Ricalcolo β e rotazioni: $O(\log n)$ nel peggiore
> - **Numero rotazioni:** Fino a $O(\log n)$ rotazioni (una per livello)

> [!warning] Differenza Insert vs Delete
> - **Insert:** 1 rotazione basta (altezza ritorna come prima)
> - **Delete:** Fino a $O(\log n)$ rotazioni (sbilanciamento può propagarsi verso l'alto)

#### Search
> [!note] Search in AVL
> Identico al BST normale: $O(\log n)$ garantito (grazie al bilanciamento)

### Campo Altezza nei Nodi
> [!info] Implementazione Pratica
> Per implementare efficientemente un AVL, ogni nodo deve contenere un campo aggiuntivo:
> - **Opzione 1:** `altezza` del sottoalbero radicato nel nodo
> - **Opzione 2:** `β` (fattore di bilanciamento) direttamente
> 
> **Proprietà richieste:**
> 1. Dato un nodo $v$, calcolare $\beta(v)$ in $O(1)$
> 2. Dopo insert/delete, ricalcolare $\beta$ lungo il cammino in $O(\log n)$
> 3. Durante le rotazioni, aggiornare $\beta$ dei nodi coinvolti in $O(\log n)$

> [!code] Aggiornamento Altezza
> ```text
> aggiornaAltezza(v)
> 4. h_sx = altezza(figlio_sinistro(v))  // -1 se null
> 5. h_dx = altezza(figlio_destro(v))     // -1 se null
> 6. altezza(v) = 1 + max(h_sx, h_dx)
> 7. β(v) = h_sx - h_dx
> ```

### Riepilogo AVL
|Operazione|Complessità|Note|
|:--|:-:|:--|
|Search|$O(\log n)$|Come BST normale|
|Insert|$O(\log n)$|Al massimo 1 rotazione|
|Delete|$O(\log n)$|Fino a $O(\log n)$ rotazioni|
|Min / Max|$O(\log n)$|Come BST normale|

> [!success] Vantaggi AVL
> - **Garanzia** $O(\log n)$ per tutte le operazioni
> - Più bilanciato di Red-Black Trees (altezza minore)

> [!warning] Svantaggi AVL
> - Più rotazioni durante delete (vs Red-Black)
> - Overhead memoria per memorizzare β o altezza
> - Ribilanciamenti più frequenti

## 8. Heap Binomiali
> [!abstract] Motivazione
> Gli heap binari hanno un problema: **merge** di due heap costa $O(n)$.
> 
> Gli **heap binomiali** risolvono questo problema garantendo **merge in $O(\log n)$**!

### Alberi Binomiali
> [!definition] Definizione Ricorsiva
> Un **albero binomiale** $B_i$ è definito ricorsivamente:
> 1. **$B_0$** consiste di un **unico nodo**
> 2. **$B_{i+1}$** si ottiene **fondendo** due alberi $B_i$, ponendo la radice dell'uno come **figlia** della radice dell'altro
> 
> Esempio:
> ```
> B₀:  •
> 
> B₁:  •          (fusione di due B₀)
>      |
>      •
> 
> B₂:  •          (fusione di due B₁)
>     / \
>    •   •
>    |
>    •
> 
> B₃:  •          (fusione di due B₂)
>     /|\
>    • • •
>    |  /\
>    • • •
>      |
>      •
> ```

> [!info] Proprietà Alberi Binomiali
> Per ogni $i \ge 0$:
> 
> |Proprietà|Valore|
> |:--|:-:|
> |**Numero di nodi**|$2^i$|
> |**Altezza**|$i$|
> |**Grado della radice**|$i$ (ha $i$ figli)|
> |**Nodi a livello $k$**|$\binom{i}{k}$ (coefficiente binomiale)|
> 
> **Da cui il nome "binomiale"!**

### Definizione Heap Binomiale
> [!definition] Heap Binomiale
> Un **heap binomiale** è una **foresta** (collezione) di alberi binomiali che soddisfa:
> 1. **Unicità:** Per ogni intero $i \ge 0$, esiste **al più** un $B_i$ nella foresta
> 2. **Contenuto informativo:** Ogni nodo $v$ contiene un elemento `elem(v)` e una chiave `key(v)`
> 3. **Ordinamento a heap:** `key(v)` $\ge$ `key(parent(v))` per ogni nodo $v$ diverso da una radice → Il **minimo** è in una delle radici (per min-heap)

> [!example] Esempio Heap Binomiale (n=13)
> ```
> n = 13 = 8 + 4 + 1 = 2³ + 2² + 2⁰
> In binario: 13 = 1101₂
> 
> Foresta: B₃, B₂, B₀
> 
>     10        1        6
>    /|\       /        (radice B₀)
>   ...       ...
> (B₃)       (B₂)
> 
> Le chiavi delle radici: {10, 1, 6} → minimo = 1
> ```

> [!success] Proprietà Topologiche
> - Un heap binomiale con $n$ nodi ha **al più $\lfloor \log_2 n \rfloor + 1$ alberi**
> - Gli alberi presenti corrispondono agli **1 nella rappresentazione binaria** di $n$
> - Ogni albero ha **altezza e grado** $O(\log n)$

### Rappresentazione
> [!note] Struttura Dati
> Un heap binomiale è rappresentato come:
> - **Lista di radici:** Collegamenti tra le radici degli alberi binomiali (ordinati per grado crescente)
> - **Ogni nodo contiene:**
>     - `key`: chiave
>     - `parent`: puntatore al padre
>     - `degree`: grado (numero di figli)
>     - `child`: puntatore al primo figlio
>     - `sibling`: puntatore al prossimo fratello

### Operazioni Heap Binomiali
#### 1. FindMin
> [!tip] Idea
> Il minimo è in una delle radici. Scorri le radici e trova il minimo.

> [!success] Complessità
> $O(\log n)$ - al più $\log n$ radici da controllare

#### 2. Merge (Fusione)
> [!tip] Idea Chiave
> Fondere due heap binomiali è come **sommare due numeri binari**!
> 
> Procedura:
> 1. Fondi le due liste di radici in una lista ordinata per grado
> 2. Scorri la lista e "porta il riporto": se trovi due $B_i$, fondili in un $B_{i+1}$
> 3. Mantieni la proprietà di unicità (al più un $B_i$ per ogni $i$)

> [!code] Algoritmo Merge (semplificato)
> ```text
> merge(H1, H2)
> 4. Fondi le liste di radici di H1 e H2 in ordine di grado
> 5. Scorri la lista risultante:
> 6. while ci sono due alberi Bi consecutivi with stesso grado:
> 7.   Fondi i due Bi in un Bi+1 (radice minore diventa padre)
> 8.   Rimuovi uno dei due Bi dalla lista
> 9. return la lista finale
> ```

> [!success] Complessità Merge
> **$O(\log n)$** dove $n = n_1 + n_2$ (dimensione totale)
> 
> - Fusione liste: $O(\log n)$ - al più $\log n_1 + \log n_2$ radici
> - Portare il riporto: $O(\log n)$ - ogni fusione diminuisce di 1 il numero di alberi

> [!note] Merge è la Killer Feature
> Questa è la ragione principale per usare heap binomiali: **merge logaritmico** invece di lineare!

#### 3. Insert
> [!tip] Idea
> Inserire un elemento = creare un heap con solo quell'elemento ($B_0$) e fare merge con l'heap esistente.

> [!code] Pseudocodice Insert
> ```text
> insert(H, elem e, chiave k)
> 1. Crea heap H' con un solo nodo (B₀) contenente e, k
> 2. return merge(H, H')
> ```

> [!success] Complessità
> $O(\log n)$ - dominato da merge

#### 4. DeleteMin (ExtractMin)
> [!tip] Idea
> 1. Trova il minimo (in una radice) in $O(\log n)$
> 2. Rimuovi quella radice
> 3. I figli della radice rimossa formano un heap binomiale $H'$
> 4. Fai merge dell'heap originale (senza la radice) con $H'$

> [!code] Pseudocodice DeleteMin
> ```text
> deleteMin(H)
> 1. Trova la radice r con chiave minima
> 2. Rimuovi r dalla lista delle radici
> 3. H' = heap formato dai figli di r (invertiti in ordine di grado)
> 4. return merge(H, H')
> ```

> [!success] Complessità
> $O(\log n)$:
> - FindMin: $O(\log n)$
> - Merge: $O(\log n)$

#### 5. DecreaseKey / IncreaseKey
> [!tip] Idea
> Simile a heap binario: dopo aver modificato la chiave, ripristina la proprietà heap facendo "salire" (DecreaseKey) o "scendere" (IncreaseKey) il nodo.

> [!success] Complessità
> $O(\log n)$ - al massimo risali/scendi dall'altezza $O(\log n)$

#### 6. Delete
> [!tip] Idea
> 1. DecreaseKey del nodo a $-\infty$ (diventa minimo)
> 2. DeleteMin

> [!success] Complessità
> $O(\log n)$ - dominato da DeleteMin

### Riepilogo Heap Binomiali
|Operazione|Complessità|
|:--|:-:|
|FindMin|$O(\log n)$|
|Insert|$O(\log n)$|
|DeleteMin|$O(\log n)$|
|DecreaseKey / IncreaseKey|$O(\log n)$|
|Delete|$O(\log n)$|
|**Merge**|**$O(\log n)$** ← Vantaggio chiave!|

## 9. Heap di Fibonacci (Cenni)
> [!abstract] Idea
> Gli **heap di Fibonacci** sono una versione "rilassata" degli heap binomiali che ottiene **complessità ammortizzate** migliori.
> 
> **Due rilassamenti:**
> 1. **Heap binomiale rilassato:** Rilassa la proprietà di unicità (possono esserci più $B_i$)
> 2. **Heap di Fibonacci:** Rilassa anche la struttura degli alberi (non sono più necessariamente binomiali)

> [!info] Filosofia "Pigra" (Lazy)
> "Perché ristrutturare subito la foresta quando potremmo farlo dopo?"
> - Insert diventa molto veloce (aggiungi e basta, senza merge immediato)
> - Il lavoro viene "ammortizzato" su più operazioni

### Complessità Ammortizzate
> [!warning] Complessità Ammortizzata
> Le complessità per heap di Fibonacci sono **ammortizzate**, cioè:
> 
> **Tempo ammortizzato** = $\frac{\text{Costo totale di } n \text{ operazioni}}{n}$
> 
> Singole operazioni possono costare di più, ma in media su molte operazioni il costo è quello indicato.

|Operazione|Heap Fibonacci (Ammortizzata)|Heap Binomiale|
|:--|:-:|:-:|
|FindMin|$O(1)$|$O(\log n)$|
|Insert|$O(1)$|$O(\log n)$|
|Merge|$O(1)$|$O(\log n)$|
|DecreaseKey|$O(1)$*|$O(\log n)$|
|DeleteMin|$O(\log n)$*|$O(\log n)$|
|Delete|$O(\log n)$*|$O(\log n)$|

*Complessità ammortizzata

### Applicazione Importante: Dijkstra
> [!example] Algoritmo di Dijkstra
> L'heap di Fibonacci è particolarmente efficiente per l'algoritmo di Dijkstra (cammini minimi):
> 
> **Operazioni in Dijkstra su grafo con $n$ nodi e $m$ archi:**
> - $n$ Insert
> - $n$ DeleteMin
> - Fino a $m$ DecreaseKey
> 
> **Complessità totale:**
> - Con heap binario/binomiale: $O((n+m) \log n) = O(m \log n)$
> - Con heap di Fibonacci: $O(n \log n + m)$ ← **Meglio su grafi densi!**

## 10. Tabella Riassuntiva - Code con Priorità
> [!success] Confronto Completo Implementazioni
> Tutte le complessità nel **caso peggiore**, tranne heap Fibonacci (ammortizzate*).

|Struttura|FindMin|Insert|Delete|DeleteMin|DecKey|IncKey|Merge|
|:--|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**Array Non Ordinato**|$\Theta(n)$|$O(1)$|$O(1)$|$\Theta(n)$|$O(1)$|$O(1)$|$O(n)$|
|**Array Ordinato**|$O(1)$|$O(n)$|$O(n)$|$O(1)$|$O(n)$|$O(n)$|$O(n)$|
|**Lista Non Ordinata**|$\Theta(n)$|$O(1)$|$O(1)$|$\Theta(n)$|$O(1)$|$O(1)$|$O(1)$|
|**Lista Ordinata**|$O(1)$|$O(n)$|$O(1)$|$O(1)$|$O(n)$|$O(n)$|$O(n)$|
|**Heap Binario**|$O(1)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(n)$|
|**d-Heap**|$O(1)$|$O(\log_d n)$|$O(d \log_d n)$|$O(d \log_d n)$|$O(\log_d n)$|$O(d \log_d n)$|$O(n)$|
|**Heap Binomiale**|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|
|**Heap Fibonacci**|$O(1)$|$O(1)$|$O(\log n)$*|$O(\log n)$*|$O(1)$*|$O(\log n)$*|$O(1)$|

## 11. Quando Usare Quale Struttura Dati
> [!tip] Guida alla Scelta

### Per Code con Priorità:
**Heap Binario:**
- Caso d'uso generale
- Semplice da implementare
- Buone performance pratiche

**d-ary Heap ($d > 2$):**
- Quando Insert/IncreaseKey sono **molto più frequenti** di DeleteMin
- Esempio: $d=4$ con 90% insert, 10% deleteMin

**Heap Binomiale:**
- Quando serve **merge** frequente tra code
- Esempio: unire code di eventi da fonti diverse

**Heap di Fibonacci:**
- Algoritmi avanzati su grafi (Dijkstra, Prim)
- Quando DecreaseKey è molto frequente
- Solo se $m >> n \log n$ (grafo denso)

### Per Dizionari:
**Array Non Ordinato:**
- Pochi elementi
- Insert molto più frequente di Search

**Array Ordinato:**
- Pochi elementi
- Search frequente, Insert raro

**Lista:**
- Dimensione variabile
- Insert/Delete in testa frequenti

**BST (non bilanciato):**
- Dati casuali (non ordinati)
- Caso medio accettabile

**AVL:**
- Serve garanzia $O(\log n)$
- Search molto frequente (più di Insert/Delete)
- Dati potrebbero arrivare ordinati

**Red-Black Tree:** (non nel programma, ma utile sapere)
- Compromesso tra AVL e BST semplice
- Delete più frequente (meno rotazioni di AVL)

## 12. Domande Tipiche d'Esame
> [!example] Esercizio 1.C - "Quale algoritmo/struttura useresti?"

**Domanda tipo:** "Costruire un heap binomiale contenente $n$ elementi"

**Risposta:**
- **Metodo 1:** $n$ Insert → $O(n \log n)$
- **Metodo 2:** Costruzione bottom-up → $O(n)$ (non richiesto)
- **Risposta esame:** $O(n \log n)$

**Domanda tipo:** "Fare il merge di due heap binomiali di dimensione $n_1$ e $n_2$"

**Risposta:** $O(\log(n_1 + n_2))$ ← Questo è il vantaggio degli heap binomiali!

**Domanda tipo:** "Implementare una coda con priorità che supporta merge frequente"

**Risposta:** Heap binomiale, perché merge costa $O(\log n)$ invece di $O(n)$

**Domanda tipo:** "Implementare un dizionario con $n$ elementi garantendo Search in $O(\log n)$ nel caso peggiore"

**Risposta:** AVL (o qualsiasi BST bilanciato), perché garantisce altezza $O(\log n)$

## Note Finali
> [!abstract] Riepilogo Generale
> **Strutture Dati Elementari:**
> - Pila: LIFO, $O(1)$ per push/pop
> - Coda: FIFO, $O(1)$ per enqueue/dequeue
> - Dizionario: varie implementazioni, trade-off search vs insert
> 
> **Alberi:**
> - BST: $O(h)$ operazioni, problema: $h$ può essere $n$
> - AVL: $h = O(\log n)$ garantito, rotazioni per bilanciare
> 
> **Code con Priorità:**
> - Heap binario: semplice, $O(\log n)$, merge $O(n)$
> - d-ary Heap: insert più veloce se $d$ grande
> - Heap binomiale: merge $O(\log n)$ ← vantaggio chiave
> - Heap Fibonacci: complessità ammortizzate migliori

> [!success] Cosa Studiare per l'Esame
> 1. **Priorità ALTA:**
>     - BST: operazioni, successor, delete con 3 casi
>     - AVL: 4 casi rotazione, insert (1 rot) vs delete (O(log n) rot)
>     - Heap binario: tutte le operazioni
>     - Tabella riassuntiva code con priorità
> 2. **Priorità MEDIA:**
>     - Heap binomiali: definizione, proprietà, merge
>     - Pila/Coda: implementazioni
>     - d-ary Heap: quando conviene
> 3. **Priorità BASSA:**
>     - Heap Fibonacci: solo tabella complessità
>     - Rappresentazioni alberi: vettore padri, posizionale