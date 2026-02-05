> [!abstract] Tipi di Dato vs Strutture Dati
> - **Tipo di Dato (ADT):** Specifica *cosa* è una collezione di dati e quali operazioni supporta (es. `insert`, `delete`, `search`), senza dire *come* è implementata.
> - **Struttura Dati:** L'implementazione concreta (es. array, lista concatenata, albero) che organizza i dati in memoria per supportare le operazioni dell'ADT in modo efficiente.

---

### 1. Strutture Dati Elementari
#### Pila (Stack)
> [!definition] LIFO (Last In First Out)
> L'ultimo elemento inserito è il primo ad essere estratto.
> **Operazioni Principali:**
> - `push(e)`: Inserisce l'elemento `e` in cima.
> - `pop()`: Rimuove e restituisce l'elemento in cima.
> - `top()`: Legge l'elemento in cima senza rimuoverlo.

| Implementazione | Spazio | Push | Pop | Note |
| :--- | :---: | :---: | :---: | :--- |
| **Array (Dim. fissa/dinamica)** | $O(n)$ | $O(1)$* | $O(1)$ | *Ammortizzato se array dinamico. |
| **Lista Concatenata** | $O(n)$ | $O(1)$ | $O(1)$ | Nessun limite di dimensione. |

#### Coda (Queue)
> [!definition] FIFO (First In First Out)
> Il primo elemento inserito è il primo ad essere estratto.
> **Operazioni Principali:**
> - `enqueue(e)`: Inserisce `e` in coda.
> - `dequeue()`: Rimuove e restituisce l'elemento in testa.
> - `first()`: Legge l'elemento in testa.

| Implementazione | Spazio | Enqueue | Dequeue | Note |
| :--- | :---: | :---: | :---: | :--- |
| **Array Circolare** | $O(n)$ | $O(1)$ | $O(1)$ | Usa indici modulo $n$. |
| **Lista Concatenata** | $O(n)$ | $O(1)$ | $O(1)$ | Puntatori `head` e `tail`. |

#### Dizionario
> [!definition] Tipo di Dato Dizionario
> Mantiene un insieme di elementi identificati da una **chiave**.
> **Operazioni:**
> - `insert(e, k)`: Aggiunge l'elemento `e` con chiave `k`.
> - `delete(k)`: Rimuove l'elemento con chiave `k`.
> - `search(k)`: Restituisce l'elemento con chiave `k`.

| Implementazione | Search | Insert | Delete | Note |
| :--- | :---: | :---: | :---: | :--- |
| **Array Non Ordinato** | $O(n)$ | $O(1)$ | $O(n)$ | Inserimento in coda. Cancellazione pigra o swap. |
| **Array Ordinato** | $O(\log n)$ | $O(n)$ | $O(n)$ | Ricerca Binaria. Shift costoso. |
| **Lista Concatenata** | $O(n)$ | $O(1)$ | $O(n)$ | Non permette ricerca binaria. |
| **BST (Bilanciato)** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Ottimo compromesso (vedi sez. 5). |

---

### 2. Alberi e Rappresentazioni
> [!info] Definizioni Base
> - **Radice (Root):** Nodo senza padre.
> - **Foglia (Leaf):** Nodo senza figli.
> - **Grado:** Numero di figli di un nodo.
> - **Altezza:** Massimo livello di una foglia (cammino più lungo dalla radice).

#### Tecniche di Rappresentazione
Come memorizzare la topologia di un albero in memoria.

| Rappresentazione        | Struttura                                | Padre(u) | Figlio $i$-esimo | Ideale per                              |
| :---------------------- | :--------------------------------------- | :------: | :--------------: | :-------------------------------------- |
| **Vettore dei Padri**   | Array $P$ dove $P[i]$ è il padre di $i$. |  $O(1)$  |      $O(n)$      | Algoritmi "bottom-up" (es. Union-Find). |
| **Vettore Posizionale** | Nodi in array per livelli (radice in 1). |  $O(1)$  |      $O(1)$      | Alberi quasi completi (es. Heap).       |
| **Puntatori ai Figli**  | Nodo contiene array/lista di puntatori.  | $O(1)$*  |      $O(1)$      | Alberi generici o binari standard.      |
*(Richiede puntatore `parent` esplicito per $O(1)$)*.

#### Visite di Alberi
Algoritmi per accedere sistematicamente a tutti i nodi ($n$ nodi). Costo $O(n)$.

> [!code] DFS - Visita in Profondità
> Usa uno **Stack** (o ricorsione).
> - **Pre-ordine:** Radice $\to$ Sinistro $\to$ Destro.
> - **Simmetrica:** Sinistro $\to$ Radice $\to$ Destro (ordina i BST!).
> - **Post-ordine:** Sinistro $\to$ Destro $\to$ Radice (utile per cancellazione o calcolo altezza).

> [!code] BFS - Visita in Ampiezza
> Usa una **Coda**.
> Visita i nodi livello per livello (distanza crescente dalla radice).

---

### 3. Heap e Code con Priorità

> [!definition] Coda con Priorità (ADT)
> Una struttura dati che mantiene un insieme $S$ di elementi, ciascuno con una **chiave** (priorità).
> **Operazioni Base:**
> - `insert(e, k)`: Inserisce un elemento.
> - `max()` / `min()`: Restituisce l'elemento con priorità massima/minima.
> - `extractMax()` / `extractMin()`: Rimuove e restituisce il massimo/minimo.
> - `increaseKey(x, k)` / `decreaseKey(x, k)`: Aggiorna la priorità di un nodo.

#### L'Heap Binario (Binary Heap)
La struttura dati più comune per implementare le code con priorità.

> [!info] Proprietà Fondamentali
> Un Heap Binario è un albero binario che soddisfa due proprietà:
> 1.  **Proprietà Strutturale:** È un albero binario **quasi completo** (tutti i livelli pieni tranne l'ultimo, riempito da sinistra a destra).
>     *   *Conseguenza:* Altezza $h = \lfloor \log_2 n \rfloor$.
> 2.  **Proprietà di Ordinamento:**
>     *   **Max-Heap:** Per ogni nodo $v \neq \text{radice}$, $key(parent(v)) \ge key(v)$. Il massimo è nella radice.
>     *   **Min-Heap:** Per ogni nodo $v \neq \text{radice}$, $key(parent(v)) \le key(v)$. Il minimo è nella radice.

**Rappresentazione (Vettore Posizionale):**
Grazie alla struttura quasi completa, non servono puntatori. Si usa un array `A` (1-based per semplicità):
- **Radice:** `A[1]`
- **Figlio Sinistro di `i`:** `2*i`
- **Figlio Destro di `i`:** `2*i + 1`
- **Padre di `i`:** `floor(i/2)`

---

#### Operazioni e Implementazione (Max-Heap)

**1. FixHeap (o Heapify-Down)**
Ripristina la proprietà di heap se violata in un nodo `i` (presupponendo che i sottoalberi sx e dx siano heap validi). Fa "scendere" l'elemento.
*   **Costo:** $O(h) = O(\log n)$.

> [!code] Pseudocodice FixHeap
> ```text
> funzione FixHeap(A, i, heapsize):
>     sx = 2*i; dx = 2*i + 1
>     max = i
>     // Trova il più grande tra i, sx e dx
>     se sx <= heapsize e A[sx] > A[max]: max = sx
>     se dx <= heapsize e A[dx] > A[max]: max = dx
>     
>     se max != i:
>         scambia A[i] con A[max]
>         FixHeap(A, max, heapsize) // Ricorsione
> ```

**2. Heapify (Costruzione)**
Costruisce un heap partendo da un array disordinato.
*   **Strategia:** Chiama `FixHeap` su tutti i nodi interni, partendo dall'ultimo livello verso la radice ($n/2$ fino a 1).
*   **Costo:** **$O(n)$** (Non $n \log n$! La dimostrazione usa la convergenza di serie).

> [!code] Pseudocodice Heapify
> ```text
> funzione Heapify(A):
>     heapsize = A.length
>     per i = floor(heapsize/2) scendendo a 1:
>         FixHeap(A, i, heapsize)
> ```

**3. Extract-Max**
Rimuove e restituisce la radice.
1.  Salva `A[1]` (il massimo).
2.  Sposta l'ultima foglia `A[n]` nella radice `A[1]`.
3.  Decrementa `heapsize`.
4.  Chiama `FixHeap(A, 1)` per far scendere la nuova radice al posto giusto.
*   **Costo:** $O(\log n)$.

**4. Insert**
Inserisce un nuovo elemento.
1.  Aggiunge il nuovo elemento come nuova foglia in fondo all'array (`A[n+1]`).
2.  **MuoviAlto (Heapify-Up):** Se l'elemento è maggiore del padre, li scambia. Ripete risalendo verso la radice finché la proprietà è ripristinata.
*   **Costo:** $O(\log n)$.

**5. Increase/Decrease Key**
Modifica la priorità di un nodo noto.
*   `increaseKey` (aumenta valore): Può violare la proprietà col padre -> **MuoviAlto** ($O(\log n)$).
*   `decreaseKey` (diminuisce valore): Può violare la proprietà coi figli -> **FixHeap** ($O(\log n)$).

---

#### Varianti di Heap

| Tipo di Heap | Struttura | Insert | Extract-Max/Min | Increase/Decr Key | Merge | Note |
| :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **Binary Heap** | Albero binario quasi completo | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(n)$ | Implementazione standard su array. |
| **d-ary Heap** | Albero $d$-ario quasi completo | $O(\log_d n)$ | $d \cdot O(\log_d n)$ | $O(\log_d n)$ | $O(n)$ | Ottimo se insert > extract (es. Dijkstra su grafi densi). Altezza ridotta. |
| **Binomial Heap** | Foresta di alberi binomiali | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | **$O(\log n)$** | Supporta fusione (merge) veloce. |
| **Fibonacci Heap** | Foresta di alberi (rilassata) | $O(1)$* | $O(\log n)$* | **$O(1)$*** | $O(1)$* | *Costi ammortizzati. Teoricamente ottimo per Dijkstra ($O(m + n \log n)$). |

---

### 4. Alberi Binari di Ricerca (BST)
> [!definition] BST
> Albero binario dove per ogni nodo $u$:
> - Chiavi nel sottoalbero **sinistro** $\le$ `key(u)`.
> - Chiavi nel sottoalbero **destro** $>$ `key(u)`.
>
> Permette di implementare un Dizionario efficiente.

| Operazione | Logica | Costo (Medio) | Costo (Peggiore) |
| :--- | :--- | :---: | :---: |
| `search(k)` | Scendi a sx se $k < key$, a dx se $k > key$. | $O(\log n)$ | $O(n)$ |
| `insert(k)` | Come search, inserisci come foglia dove cadi (null). | $O(\log n)$ | $O(n)$ |
| `delete(k)` | 3 casi: **Foglia** (rimuovi); **1 Figlio** (bypass); **2 Figli** (sostituisci con successore/predecessore e rimuovi quello). | $O(\log n)$ | $O(n)$ |
| `min/max` | Scendi sempre a sx (min) o sempre a dx (max). | $O(\log n)$ | $O(n)$ |

> [!warning] Problema del BST
> Se inseriamo elementi già ordinati (es. 1, 2, 3, 4), l'albero diventa una lista (degenere). Altezza $h = n$. Per garantire $h = \log n$, servono alberi bilanciati (AVL).

---

### 5. Alberi AVL (Alberi Bilanciati)
> [!definition] Proprietà AVL
> Un BST è AVL se per **ogni** nodo $v$, il fattore di bilanciamento $\beta(v) = h(sx) - h(dx)$ è in $\{-1, 0, +1\}$.
> **Garanzia:** L'altezza è sempre $h = \Theta(\log n)$.

#### Ribilanciamento (Rotazioni)
Dopo un inserimento o cancellazione, se $\beta(v)$ diventa $\pm 2$, si applicano rotazioni per ripristinare l'equilibrio.

1.  **Rotazione Semplice (Verso Destra/Sinistra):**
    *   Applicata quando lo sbilanciamento è "esterno" (Sinistra-Sinistra o Destra-Destra).
    *   Costo: $O(1)$.
2.  **Rotazione Doppia (Sinistra-Destra o Destra-Sinistra):**
    *   Applicata quando lo sbilanciamento è "interno" (es. figlio sx troppo alto, ma il suo sbilanciamento è a dx).
    *   Equivale a due rotazioni semplici consecutive.
    *   Costo: $O(1)$.

#### Costi Operazioni AVL
Tutte le operazioni base (`search`, `insert`, `delete`) impiegano tempo proporzionale all'altezza. Grazie al bilanciamento:
*   **Search:** $O(\log n)$
*   **Insert:** $O(\log n)$ (Search + 1 o 2 rotazioni).
*   **Delete:** $O(\log n)$ (Search + possibili rotazioni a cascata fino alla radice).
