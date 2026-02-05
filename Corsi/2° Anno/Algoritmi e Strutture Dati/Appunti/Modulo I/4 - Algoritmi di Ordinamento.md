> [!abstract] Introduzione agli Algoritmi di Ordinamento
> L'ordinamento è uno dei problemi più studiati in informatica. Consiste nel riorganizzare una sequenza di $n$ elementi in modo che rispettino una relazione di ordine totale (crescente o decrescente).
>
> **Obiettivo:** Analizzare diverse strategie (confronto vs lineari) per comprendere i limiti teorici e le prestazioni pratiche in base alle caratteristiche dell'input.

### Il Problema dell'Ordinamento
> [!definition] Definizione Formale
> **Input:** Una sequenza di $n$ numeri $\langle a_1, a_2, \dots, a_n \rangle$.
> **Output:** Una permutazione $\langle a'_1, a'_2, \dots, a'_n \rangle$ della sequenza di input tale che $a'_1 \le a'_2 \le \dots \le a'_n$.

### Delimitazioni di Complessità
> [!info] Upper e Lower Bound
> - **Upper Bound:** Esistono algoritmi che risolvono il problema in $O(n^2)$ (semplici) e $O(n \log n)$ (ottimi per confronto).
> - **Lower Bound:** È dimostrato che ogni algoritmo basato su confronti richiede almeno $\Omega(n \log n)$ operazioni nel caso peggiore.
> - **Algoritmo Ottimo:** Un algoritmo la cui complessità nel caso peggiore uguaglia il lower bound del problema.

### 1. Ordinamento per Confronti (Quadratici)
Algoritmi semplici da implementare ma inefficienti su grandi dataset ($O(n^2)$).

#### Selection Sort
> [!tip] Idea
> Ad ogni passo $k$, cerca l'elemento minimo nella parte non ordinata dell'array e scambialo con l'elemento in posizione $k$.

> [!code] Selection Sort
> **Pseudocodice**
> ```text
> funzione SelectionSort(A):
>     n = lunghezza(A)
>     per k = 0 a n-2:
>         min_idx = k
>         per j = k+1 a n-1:
>             se A[j] < A[min_idx]:
>                 min_idx = j
>         scambia A[k] con A[min_idx]
> ```
> **Implementazione (Python)**
> ```python
> def selection_sort(arr):
>     n = len(arr)
>     for i in range(n):
>         min_idx = i
>         for j in range(i+1, n):
>             if arr[j] < arr[min_idx]:
>                 min_idx = j
>         arr[i], arr[min_idx] = arr[min_idx], arr[i]
>     return arr
> ```

> [!success] Complessità
> $T(n) = \displaystyle\sum_{k=0}^{n-2} (n-k-1) = \frac{n(n-1)}{2} = \Theta(n^2)$ in tutti i casi.

> [!info] Invariante di Ciclo (Correttezza)
> Per dimostrare che Selection Sort funziona, usiamo un invariante:
> "All'inizio dell'iterazione $k$, il sottoarray $A[0 \dots k-1]$ contiene i $k$ elementi più piccoli dell'array ordinati."
> - **Inizializzazione:** Per $k=0$ è vero (vuoto).
> - **Conservazione:** Troviamo il minimo nel resto e lo mettiamo in $k$. Ora i primi $k+1$ sono i minimi ordinati.
> - **Terminazione:** Alla fine ($k=n-1$), l'array è ordinato.

#### Insertion Sort
> [!tip] Idea
> Simile a come si ordinano le carte in mano: prendi un elemento e inseriscilo nella posizione corretta tra gli elementi già ordinati alla sua sinistra.

> [!code] Insertion Sort
> **Pseudocodice**
> ```text
> funzione InsertionSort(A):
>     per i = 1 a n-1:
>         chiave = A[i]
>         j = i - 1
>         mentre j >= 0 e A[j] > chiave:
>             A[j+1] = A[j]
>             j = j - 1
>         A[j+1] = chiave
> ```
> **Implementazione (Python)**
> ```python
> def insertion_sort(arr):
>     for i in range(1, len(arr)):
>         key = arr[i]
>         j = i-1
>         while j >= 0 and key < arr[j]:
>             arr[j + 1] = arr[j]
>             j -= 1
>         arr[j + 1] = key
>     return arr
> ```

> [!success] Complessità
> - Caso Peggiore: $\Theta(n^2)$ (array ordinato al contrario).
> - Caso Migliore: $\Theta(n)$ (array già ordinato).

#### Bubble Sort
> [!tip] Idea
> Esegui più scansioni dell'array, scambiando coppie di elementi adiacenti se non sono in ordine. Gli elementi più grandi "risalgono" come bolle verso la fine.

> [!code] Bubble Sort
> **Pseudocodice**
> ```text
> funzione BubbleSort(A):
>     per i = 0 a n-1:
>         per j = 0 a n-i-2:
>             se A[j] > A[j+1]:
>                 scambia A[j] con A[j+1]
> ```
> **Implementazione (Python)**
> ```python
> def bubble_sort(arr):
>     n = len(arr)
>     for i in range(n):
>         for j in range(0, n-i-1):
>             if arr[j] > arr[j+1]:
>                 arr[j], arr[j+1] = arr[j+1], arr[j]
>     return arr
> ```

### 2. Ordinamento per Confronti (Ottimi)
Sfruttano la tecnica **Divide et Impera** per raggiungere $O(n \log n)$.

#### Merge Sort
> [!tip] Idea
> Dividi l'array a metà, ordina ricorsivamente le due metà e poi fondile (merge) mantenendo l'ordine.

> [!code] Merge Sort
> **Pseudocodice**
> ```text
> funzione MergeSort(A, i, f):
>     se i < f:
>         m = floor((i+f)/2)
>         MergeSort(A, i, m)
>         MergeSort(A, m+1, f)
>         Merge(A, i, m, f)
> 
> funzione Merge(A, i, m, f):
>     X = array ausiliario di dimensione (f - i + 1)
>     k1 = i; k2 = m + 1; j = 0
>     mentre k1 <= m e k2 <= f:
>         se A[k1] <= A[k2]: X[j++] = A[k1++]
>         altrimenti:        X[j++] = A[k2++]
>     copia A[k1...m] in coda a X
>     copia A[k2...f] in coda a X
>     copia X in A[i...f]
> ```
> **Implementazione (Python)**
> ```python
> def merge_sort(arr, i, f):
>     if i < f:
>         m = (i + f) // 2
>         merge_sort(arr, i, m)
>         merge_sort(arr, m + 1, f)
>         merge(arr, i, m, f)
> 
> def merge(arr, i, m, f):
>     L = arr[i : m+1]
>     R = arr[m+1 : f+1]
>     k1, k2, j = 0, 0, i
>     
>     while k1 < len(L) and k2 < len(R):
>         if L[k1] <= R[k2]: arr[j] = L[k1]; k1 += 1
>         else:              arr[j] = R[k2]; k2 += 1
>         j += 1
>         
>     while k1 < len(L): arr[j] = L[k1]; k1 += 1; j += 1
>     while k2 < len(R): arr[j] = R[k2]; k2 += 1; j += 1
> ```

> [!warning] Note
> Il Merge Sort **non ordina in loco** poiché la procedura di fusione richiede memoria aggiuntiva $\Theta(n)$. È però stabile.

#### Quick Sort
> [!tip] Idea
> Scegli un elemento (pivot), partiziona l'array mettendo a sinistra gli elementi $\le$ pivot e a destra quelli $>$, poi ordina ricorsivamente le due parti.

> [!code] Quick Sort
> **Pseudocodice**
> ```text
> funzione QuickSort(A, p, r):
>     se p < r:
>         q = Partition(A, p, r)
>         QuickSort(A, p, q-1)
>         QuickSort(A, q+1, r)
> 
> funzione Partition(A, p, r):
>     x = A[r] // Pivot
>     i = p - 1
>     per j = p a r-1:
>         se A[j] <= x:
>             i = i + 1
>             scambia A[i] con A[j]
>     scambia A[i+1] con A[r]
>     ritorna i + 1
> ```
> **Implementazione (Python - Randomizzato)**
> ```python
> import random
> def quick_sort(arr, low, high):
>     if low < high:
>         pivot_idx = partition(arr, low, high)
>         quick_sort(arr, low, pivot_idx - 1)
>         quick_sort(arr, pivot_idx + 1, high)
> 
> def partition(arr, low, high):
>     rand_idx = random.randint(low, high)
>     arr[low], arr[rand_idx] = arr[rand_idx], arr[low]
>     pivot = arr[low]
>     i = low + 1
>     for j in range(low + 1, high + 1):
>         if arr[j] <= pivot:
>             arr[i], arr[j] = arr[j], arr[i]
>             i += 1
>     arr[low], arr[i-1] = arr[i-1], arr[low]
>     return i - 1
> ```

> [!success] Complessità
> - Caso Peggiore: $\Theta(n^2)$ (pivot sempre pessimo).
> - Caso Medio/Migliore: $\Theta(n \log n)$.
> - La versione randomizzata evita il caso peggiore con alta probabilità. Ordina **in loco** ma non è stabile.

### 3. Lower Bound dell'Ordinamento
> [!theorem] Teorema del Lower Bound
> Ogni algoritmo basato su confronti che ordina $n$ elementi deve eseguire almeno $\Omega(n \log n)$ confronti nel caso peggiore. 
> 
> **Dimostrazione (Albero di Decisione):**
> - Un algoritmo di ordinamento può essere visto come un albero binario dove ogni nodo interno è un confronto $a_i \le a_j$.
> - Per ordinare $n$ elementi, l'albero deve avere almeno $n!$ foglie (una per ogni possibile permutazione).
> - L'altezza $h$ di un albero binario con $L$ foglie è $h \ge \log_2 L$.
> - Quindi $h \ge \log_2(n!) \approx n \log_2 n - n \log_2 e = \Omega(n \log n)$.

### 4. Ordinamento Lineare (Senza Confronti)

È possibile superare il limite $\Omega(n \log n)$ se si hanno informazioni aggiuntive sui dati (es. range limitato).

#### Integer Sort (Counting Sort)
> [!tip] Idea
> Se i numeri sono nell'intervallo $[0, k]$, conta quante volte appare ogni numero e ricostruisci l'array.

> [!code] Integer Sort
> **Pseudocodice**
> ```text
> funzione IntegerSort(A, k):
>     Sia Y un array di dimensione k+1 inizializzato a 0
>     per ogni x in A: Y[x]++
>     pos = 0
>     per i = 0 a k:
>         mentre Y[i] > 0:
>             A[pos] = i
>             pos++
>             Y[i]--
> ```
> **Implementazione (Python)**
> ```python
> def integer_sort(arr):
>     if not arr: return arr
>     max_val = max(arr)
>     count = [0] * (max_val + 1)
>     for x in arr: count[x] += 1
>     output = []
>     for i, c in enumerate(count):
>         output.extend([i] * c)
>     return output
> ```

> [!success] Complessità
> $T(n) = \Theta(n + k)$. Se $k = O(n)$, la complessità è lineare $\Theta(n)$.

#### Bucket Sort
> [!tip] Idea
> Distribuisci gli elementi in $k$ "secchi" (bucket) in base al valore della chiave, ordina ogni bucket (es. con Insertion Sort) e concatena.

#### Radix Sort
> [!tip] Idea
> Ordina i numeri cifra per cifra, partendo dalla meno significativa (LSD), usando un algoritmo di ordinamento stabile (come Bucket Sort) ad ogni passo.

> [!success] Complessità
> $T(n) = \Theta(d(n + b))$ dove $d$ è il numero di cifre e $b$ la base.

---

### 5. Applicazione: L'Oracolo (Range Counting)
> [!example] Il Problema
> Dato un array $A$ di $n$ interi in $[0, k]$, vogliamo costruire una struttura dati ("Oracolo") che risponda in $O(1)$ alla domanda:
> *"Quanti numeri nell'array cadono nell'intervallo $[a, b]$?"*

**Strategia (Prefix Sums):**
1. **Preprocessing (Costruzione):** Usiamo la logica dell'Integer Sort.
   - Costruiamo l'array delle frequenze $C$ (come in Integer Sort).
   - Costruiamo l'array delle somme prefisse $P$, dove $P[x]$ contiene il numero di elementi $\le x$.
   - $P[x] = P[x-1] + C[x]$.
   - Costo: $O(n + k)$.

2. **Query (Risposta):**
   - Il numero di elementi in $[a, b]$ è semplicemente $P[b] - P[a-1]$.
   - Costo: $O(1)$.

> [!code] Implementazione Oracolo
> **Pseudocodice**
> ```text
> funzione CostruisciOracolo(A, k):
>     C = array di zeri dimensione k+1
>     P = array di zeri dimensione k+1
>     per x in A: C[x]++
>     P[0] = C[0]
>     per i = 1 a k:
>         P[i] = P[i-1] + C[i]
>     return P
> 
> funzione Query(P, a, b):
>     se a > 0: return P[b] - P[a-1]
>     altrimenti: return P[b]
> ```
