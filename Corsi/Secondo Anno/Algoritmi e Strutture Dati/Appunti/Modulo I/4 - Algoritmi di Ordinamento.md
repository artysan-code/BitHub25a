> [!abstract] Introduzione agli Algoritmi di Ordinamento
> L'ordinamento è uno dei problemi più studiati in informatica. Consiste nel riorganizzare una sequenza di $n$ elementi in modo che rispettino una relazione di ordine totale (crescente o decrescente).
>
> **Obiettivo:** Analizzare diverse strategie (confronto vs lineari) per comprendere i limiti teorici e le prestazioni pratiche in base alle caratteristiche dell'input.

> [!definition] **Il Problema dell'ordinamento** - Definizione Formale
> **Input:** Una sequenza di $n$ numeri $\langle a_1, a_2, \dots, a_n \rangle$.
> **Output:** Una permutazione $\langle a'_1, a'_2, \dots, a'_n \rangle$ della sequenza di input tale che $a'_1 \le a'_2 \le \dots \le a'_n$.

> [!info] Upper e Lower Bound
> - **Upper Bound:** Esistono algoritmi che risolvono il problema in $O(n^2)$ (semplici) e $O(n \log n)$ (ottimi per confronto).
> - **Lower Bound:** È dimostrato che ogni algoritmo basato su confronti richiede almeno $\Omega(n \log n)$ operazioni nel caso peggiore.
> - **Algoritmo Ottimo:** Un algoritmo la cui complessità nel caso peggiore uguaglia il lower bound del problema.

## Ordinamento per Confronti (Quadratici)
Algoritmi semplici da implementare ma inefficienti su grandi dataset ($O(n^2)$).

### Selection Sort
> [!tip] Idea
> Ad ogni passo $k$, cerca l'elemento minimo nella parte non ordinata dell'array e scambialo con l'elemento in posizione $k$.

> [!code] Selection Sort
> **Pseudocodice (A[1..n])**
> ```text
> SelectionSort(A)
> 1. for k=1 to n-1 do
> 2.   m = k
> 3.   for j=k+1 to n do
> 4.     if A[j] < A[m] then m = j
> 5.   scambia A[m] con A[k]
> ```
> 
> **Chiamata iniziale:** `SelectionSort(A)`

> [!success] Complessità
> $T(n) = \displaystyle\sum_{k=1}^{n-1} (n-k) = \frac{n(n-1)}{2} = \Theta(n^2)$ in tutti i casi.

> [!info] Invariante di Ciclo (Correttezza)
> Per dimostrare che Selection Sort funziona, usiamo un invariante:
> "All'inizio dell'iterazione $k$, il sottoarray $A[1 \dots k-1]$ contiene i $k-1$ elementi più piccoli dell'array ordinati."
> - **Inizializzazione:** Per $k=1$ è vero (vuoto).
> - **Conservazione:** Troviamo il minimo nel resto e lo mettiamo in $k$. Ora i primi $k$ sono i minimi ordinati.
> - **Terminazione:** Alla fine ($k=n$), l'array è ordinato.

> [!note] Proprietà
> - **Complessità:** $\Theta(n^2)$ sempre (peggiore, migliore, medio)
> - **In loco:** Sì, usa solo memoria $O(1)$
> - **Stabile:** No, può alterare l'ordine relativo di elementi uguali
> - **Quando usarlo:** Mai in pratica, solo didattico

### Insertion Sort
> [!tip] Idea
> Simile a come si ordinano le carte in mano: prendi un elemento e inseriscilo nella posizione corretta tra gli elementi già ordinati alla sua sinistra, spostando gli altri a destra.

> [!code] Insertion Sort
> **Pseudocodice (A[1..n])**
> ```text
> InsertionSort(A)
> 1. for k=2 to n do
> 2.   chiave = A[k]
> 3.   j = k - 1
> 4.   while j >= 1 and A[j] > chiave do
> 5.     A[j+1] = A[j]
> 6.     j = j - 1
> 7.   A[j+1] = chiave
> ```
> 
> **Chiamata iniziale:** `InsertionSort(A)`

> [!success] Complessità
> - **Caso Peggiore:** $\Theta(n^2)$ (array ordinato al contrario)
> - **Caso Migliore:** $\Theta(n)$ (array già ordinato)
> - **Caso Medio:** $\Theta(n^2)$

> [!info] Invariante di Ciclo
> "All'inizio dell'iterazione $k$, il sottoarray $A[1 \dots k-1]$ contiene gli stessi elementi che c'erano originariamente in $A[1 \dots k-1]$, ma in ordine."

> [!note] Proprietà
> - **Complessità:** $O(n^2)$ peggiore, $\Theta(n)$ migliore
> - **In loco:** Sì, usa solo memoria $O(1)$
> - **Stabile:** Sì, mantiene l'ordine relativo
> - **Quando usarlo:** Array piccoli (n < 50), array quasi ordinati, ordinamento online

### Bubble Sort
> [!tip] Idea
> Esegui più scansioni dell'array, scambiando coppie di elementi adiacenti se non sono in ordine. Gli elementi più grandi "risalgono" come bolle verso la fine.

> [!code] Bubble Sort
> **Pseudocodice (A[1..n])**
> ```text
> BubbleSort(A)
> 1. for k=1 to n-1 do
> 2.   for j=1 to n-k do
> 3.     if A[j] > A[j+1] then
> 4.       scambia A[j] con A[j+1]
> ```
> 
> **Chiamata iniziale:** `BubbleSort(A)`

> [!success] Complessità
> $T(n) = \displaystyle\sum_{k=1}^{n-1} (n-k) = \frac{n(n-1)}{2} = \Theta(n^2)$ in tutti i casi.

> [!note] Proprietà
> - **Complessità:** $\Theta(n^2)$ sempre (versione base)
> - **In loco:** Sì, usa solo memoria $O(1)$
> - **Stabile:** Sì, mantiene l'ordine relativo
> - **Quando usarlo:** Mai in pratica, ancora meno efficiente del Selection Sort

## Ordinamento per Confronti (Ottimi)
Sfruttano la tecnica **Divide et Impera** per raggiungere $O(n \log n)$.

### Merge Sort
> [!tip] Idea
> Dividi l'array a metà, ordina ricorsivamente le due metà e poi fondile (merge) mantenendo l'ordine. La fase di divide è semplice (taglio a metà), mentre la fase di merge è complessa (fusione ordinata).

> [!code] Merge Sort
> **Pseudocodice (A[1..n])**
> ```text
> MergeSort(A, i, f)
> 1. if i < f then
> 2.   m = ⌊(i+f)/2⌋
> 3.   MergeSort(A, i, m)
> 4.   MergeSort(A, m+1, f)
> 5.   Merge(A, i, m, f)
>
> Merge(A, init, fin1, fin2)
> 6.  X = array ausiliario di dimensione fin2 - init + 1
> 7.  i = 0
> 8.  k1 = init
> 9.  k2 = fin1 + 1
> 10.  while k1 <= fin1 and k2 <= fin2 do
> 11.    if A[k1] < A[k2] then
> 12.      X[i] = A[k1]
> 13.      k1 = k1 + 1
> 14.    else
> 15.     X[i] = A[k2]
> 16.     k2 = k2 + 1
> 17.   i = i + 1
> 18. if k1 <= fin1 then copia A[k1..fin1] alla fine di X
> 19. else copia A[k2..fin2] alla fine di X
> 20. copia X in A[init..fin2]
> ```
> 
> **Chiamata iniziale:** `MergeSort(A, 1, n)`

> [!success] Complessità
> **Ricorrenza:** $T(n) = 2T(n/2) + \Theta(n)$
> 
> Applicando il Teorema Master (caso 2): $T(n) = \Theta(n \log n)$
> 
> - **Caso Peggiore:** $\Theta(n \log n)$
> - **Caso Migliore:** $\Theta(n \log n)$
> - **Caso Medio:** $\Theta(n \log n)$

> [!info] Invariante
> Dopo ogni chiamata ricorsiva, il sottoarray $A[i..f]$ è ordinato.

> [!note] Proprietà
> - **Complessità:** $\Theta(n \log n)$ sempre
> - **Complessità spaziale:** $\Theta(n)$ per array ausiliario
> - **In loco:** No, richiede memoria aggiuntiva
> - **Quando usarlo:** Serve garanzia di $O(n \log n)$, liste collegate, dati esterni, quando serve stabilità

### Quick Sort
> [!tip] Idea
> Scegli un elemento (perno/pivot), partiziona l'array mettendo a sinistra gli elementi $\le$ perno e a destra quelli $>$ perno, poi ordina ricorsivamente le due parti. La fase di divide è complessa (partition), mentre la fase di merge è semplice (concatenazione).

> [!code] Quick Sort
> ***Pseudocodice (A[1..n])**
> 
> ```text
> QuickSort(A, i, f)
> 1. if i < f then
> 2.   m = Partition(A, i, f)
> 3.   QuickSort(A, i, m-1)
> 4.   QuickSort(A, m+1, f)
> 
> Partition(A, i, f)
> 1.  perno = A[i]
> 2.  sx = i
> 3.  dx = f + 1
> 4.  while true do
> 5.    do (sx = sx + 1) while (sx <= f and A[sx] <= perno)
> 6.    do (dx = dx - 1) while (A[dx] > perno)
> 7.    if sx < dx then scambia A[sx] e A[dx]
> 8.    else break
> 9.  scambia A[i] e A[dx]
> 10. return dx
> ```
> 
> **Chiamata iniziale:** `QuickSort(A, 1, n)`

> [!info] Come funziona Partition
> 1. Sceglie il perno `perno = A[i]` (primo elemento)
> 2. Due puntatori: `sx` parte da sinistra, `dx` parte da destra
> 3. `sx` cerca elementi `> x`, `dx` cerca elementi `<= x`
> 4. Quando trovati, li scambia
> 5. Quando si incrociano, posiziona il perno al centro
> 
> **Invariante:** In ogni istante, $A[i+1..sx-1]$ contiene elementi $\le x$ e $A[dx+1..f]$ contiene elementi $> perno$.

> [!success] Complessità
> **Caso Peggiore:** $T(n) = T(n-1) + \Theta(n) = O(n^2)$
> - Si verifica quando il perno è sempre il minimo o massimo (es. array già ordinato)
> 
> **Caso Migliore:** $T(n) = 2T(n/2) + \Theta(n) = \Theta(n \log n)$
> - Si verifica quando il perno divide sempre perfettamente a metà
> 
> **Caso Medio:** $\Theta(n \log n)$
> - Assumendo istanze equiprobabili

> [!warning] Versione Randomizzata
> Per evitare il caso peggiore su input specifici, si sceglie il perno **casualmente**.
> 
> **Teorema:** Il QuickSort randomizzato ordina in loco un array di lunghezza $n$ in:
> - Tempo $O(n^2)$ nel caso peggiore
> - Tempo $O(n \log n)$ atteso (indipendentemente dall'input)
> - Con alta probabilità (almeno $1-1/n$), il tempo è $O(n \log n)$

> [!note] Proprietà
> - **Complessità:** $O(n^2)$ peggiore, $O(n \log n)$ medio/migliore
> - **Complessità spaziale:** $O(\log n)$ stack ricorsione (medio), $O(n)$ (peggiore)
> - **In loco:** Sì, non richiede array ausiliario
> - **Stabile:** No
> - **Quando usarlo:** In pratica è il più usato (veloce, in loco, con randomizzazione evita caso peggiore)

### Heap Sort
> [!tip] Idea
> Utilizza una struttura dati efficiente (Max-Heap) per selezionare iterativamente il massimo. L'approccio è simile al Selection Sort, ma ottimizzato grazie all'uso delle proprietà dell'heap che permettono estrazioni in tempo logaritmico.

> [!code] Heap Sort
> **Pseudocodice (A[1..n])**
> ```text
> HeapSort(A)
> 1. Heapify(A)
> 2. heapsize[A] = n
> 3. for i = n downto 2 do
> 4.    scambia A[1] con A[i]
> 5.    heapsize[A] = heapsize[A] - 1
> 6.    fixHeap(1, A)
> ```
> *Le procedure `Heapify` e `fixHeap` sono descritte nel [[5 - Strutture Dati|file delle strutture dati]].*

> [!success] Complessità
> $T(n) = O(n) + (n-1) \cdot O(\log n) = \Theta(n \log n)$
> 
> - **Heapify:** $O(n)$
> - **Estrazioni (n-1 passate):** ogni `fixHeap` costa $O(\log n)$.
> - **Caso Peggiore:** $\Theta(n \log n)$
> - **Caso Migliore:** $\Theta(n \log n)$ (o $\Theta(n)$ se tutti gli elementi sono uguali, a seconda dell'implementazione).

> [!note] Proprietà
> - **Complessità:** $\Theta(n \log n)$ sempre.
> - **In loco:** Sì, ordina direttamente l'array di input senza memoria ausiliaria aggiuntiva (usa un Max-Heap per ordinare in modo crescente).
> - **Stabile:** No.
> - **Vantaggi:** Ottimo tempo nel caso peggiore e uso minimo di memoria. Spesso però QuickSort è più veloce in pratica a causa di fattori costanti minori e migliore localizzazione dei riferimenti.

## Lower Bound dell'Ordinamento
> [!theorem] Teorema del Lower Bound
> Ogni algoritmo basato su confronti che ordina $n$ elementi deve eseguire almeno $\Omega(n \log n)$ confronti nel caso peggiore.
> 
> **Dimostrazione (Albero di Decisione):**
> - Un algoritmo di ordinamento può essere visto come un albero binario dove ogni nodo interno è un confronto $a_i \le a_j$.
> - Per ordinare $n$ elementi, l'albero deve avere almeno $n!$ foglie (una per ogni possibile permutazione).
> - L'altezza $h$ di un albero binario con $L$ foglie è $h \ge \log_2 L$.
> - Quindi $h \ge \log_2(n!) \approx n \log_2 n - n \log_2 e = \Omega(n \log n)$.

> [!success] Conseguenza
> MergeSort e HeapSort sono **algoritmi ottimi** perché raggiungono il lower bound $\Theta(n \log n)$ nel caso peggiore.

## Ordinamento Lineare (Senza Confronti)
È possibile superare il limite $\Omega(n \log n)$ se si hanno informazioni aggiuntive sui dati (es. range limitato).

### Integer Sort (Counting Sort)
> [!tip] Idea
> Se i numeri sono nell'intervallo $[0, k]$, conta quante volte appare ogni numero in un array di frequenze, poi ricostruisci l'array ordinato.

> [!code] Integer Sort 
> **Pseudocodice (A[1..n], valori in [1..k])**
> 
> ```text
> IntegerSort(A, n, k)
> 1. Y = array di dimensione k
> 2. for i=1 to k do
> 3.   Y[i] = 0
> 4. for i=1 to n do
> 5.   Y[A[i]] = Y[A[i]] + 1
> 6. j = 1
> 7. for i=1 to k do
> 8.   while Y[i] > 0 do
> 9.     A[j] = i
> 10.    j = j + 1
> 11.    Y[i] = Y[i] - 1
> ```

> [!success] Complessità
> $T(n) = \Theta(n + k)$
> 
> - Se $k = O(n)$, la complessità è **lineare** $\Theta(n)$
> - Se $k >> n$, potrebbe essere inefficiente

> [!note] Proprietà
> - **Complessità:** $\Theta(n + k)$
> - **In loco:** No, richiede array ausiliario di dimensione $k$
> - **Stabile:** Sì
> - **Quando usarlo:** Quando i valori sono interi in un range limitato $k = O(n)$

### Bucket Sort
> [!tip] Idea
> Per ordinare $n$ record con chiavi intere in $[1, k]$, si mantiene un array di liste $Y$, anziché di contatori. Ogni lista $Y[i]$ conterrà gli elementi con chiave uguale a $i$. Al termine, si concatenano le liste.

> [!code] Bucket Sort
> **Pseudocodice (X[1..n], valori in [1..k])**
> ```text
> BucketSort(X, k)
> 1. Sia Y un array di dimensione k
> 2. for i=1 to k do Y[i] = lista vuota
> 3. for i=1 to n do
> 4.   appendi il record X[i] alla lista Y[chiave(X[i])]
> 5. for i=1 to k do
> 6.   copia ordinatamente in X gli elementi della lista Y[i]
> ```

> [!success] Complessità
> $T(n) = \Theta(n + k)$
> - Tempo $O(1)$ per inizializzare ogni lista ($k$ volte)
> - Tempo $O(1)$ per appendere ogni record ($n$ volte)
> - Tempo $O(n+k)$ per ricostruire l'array $X$ concatenando le liste.

> [!info] Stabilità
> Il Bucket Sort è **stabile** se gli elementi vengono appesi **in coda** alla lista $Y[i]$, preservando l'ordine originale tra elementi con la stessa chiave.

> [!note] Differenza con Integer Sort
> Mentre l'Integer Sort conta solo le occorrenze (va bene per semplici interi), il Bucket Sort gestisce **record** con chiavi e informazioni satellite associate.

### Radix Sort
> [!tip] Idea
> Ordina $n$ interi con valori in $[1, k]$ rappresentandoli in **base $b$**. L'algoritmo esegue una serie di passate di un algoritmo di ordinamento stabile (tipicamente **Bucket Sort**) partendo dalla cifra meno significativa verso quella più significativa.

> [!example] Funzionamento
> Per ordinare $\{2397, 4368, 5924\}$ in base 10:
> 1. Ordina per l'ultima cifra: `5924, 2397, 4368`
> 2. Ordina per la penultima cifra (stabile): `5924, 4368, 2397`
> 3. Ordina per la terzultima cifra: `2397, 4368, 5924`
> 4. Ordina per la cifra più significativa: `2397, 4368, 5924`

> [!success] Complessità
> $T(n) = \Theta(d \cdot (n + b))$ dove:
> - $d$ è il numero di cifre: $d = \lceil \log_b k \rceil$
> - $b$ è la base numerica
> - $(n+b)$ è il costo di una passata di Bucket Sort
> 
> **Analisi:** $T(n) = \Theta((n+b) \log_b k)$
> - Se scegliamo $b = \Theta(n)$, allora $T(n) = \Theta(n \frac{\log k}{\log n})$.
> - L'algoritmo è **lineare** $\Theta(n)$ se $k = O(n^c)$ per una costante $c$ (ovvero se il numero di cifre $d$ è costante).

> [!note] Proprietà
> - **Stabilità:** È **obbligatorio** che l'ordinamento intermedio sia stabile per non distruggere l'ordinamento ottenuto nelle passate precedenti.
> - **In loco:** No.
> - **Quando usarlo:** Per ordinare grandi quantità di interi (es. numeri a 32 o 64 bit) scegliendo una base $b$ opportuna per minimizzare le passate.

## Applicazione: L'Oracolo (Range Counting)
> [!example] Il Problema
> Dato un array $A$ di $n$ interi in $[0, k]$, vogliamo costruire una struttura dati ("Oracolo") che risponda in $O(1)$ alla domanda:
> *"Quanti numeri nell'array cadono nell'intervallo $[a, b]$?"*

> [!tip] Strategia (Prefix Sums)
> **Preprocessing (Costruzione):** Usiamo la logica dell'Integer Sort.
> 1. Costruiamo l'array delle frequenze $C$, dove $C[x]$ conta quante volte appare $x$
> 2. Costruiamo l'array delle somme prefisse $P$, dove $P[x]$ contiene il numero di elementi $\le x$
> 3. $P[x] = P[x-1] + C[x]$
> 4. Costo: $O(n + k)$
> 
> **Query (Risposta):**
> - Il numero di elementi in $[a, b]$ è semplicemente $P[b] - P[a-1]$
> - Costo: $O(1)$

> [!code] Implementazione Oracolo
> **Pseudocodice**
> ```text
> CostruisciOracolo(A, n, k)
> 1. C = array di zeri dimensione k+1
> 2. P = array di zeri dimensione k+1
> 3. for i=1 to n do
> 4.   C[A[i]] = C[A[i]] + 1
> 5. P[0] = C[0]
> 6. for i=1 to k do
> 7.   P[i] = P[i-1] + C[i]
> 8. return P
>
> Query(P, a, b)
> 1. if a > 0 then return P[b] - P[a-1]
> 2. else return P[b]
> ```

> [!success] Complessità Totale
> - **Preprocessing:** $O(n + k)$
> - **Ogni query:** $O(1)$
> - **Spazio:** $O(k)$ per gli array $C$ e $P$

## Tabella Riassuntiva Algoritmi di Ordinamento
| Algoritmo | Caso Migliore | Caso Peggiore | Caso Medio | In loco | Stabile | Note |
|-----------|---------------|---------------|------------|---------|---------|------|
| Selection Sort | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | No | Mai usare |
| Insertion Sort | $\Theta(n)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | Sì | Array piccoli/quasi ordinati |
| Bubble Sort | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | Sì | Mai usare |
| Merge Sort | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $\Theta(n \log n)$ | No | Sì | Garanzia di performance |
| Quick Sort | $\Theta(n \log n)$ | $O(n^2)$ | $\Theta(n \log n)$ | Sì | No | Più usato in pratica |
| Heap Sort | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $\Theta(n \log n)$ | Sì | No | Ottimo peggiore, in loco |
| Integer Sort | $\Theta(n+k)$ | $\Theta(n+k)$ | $\Theta(n+k)$ | No | Sì | Se $k = O(n)$ |
| Radix Sort | $\Theta(d(n+b))$ | $\Theta(d(n+b))$ | $\Theta(d(n+b))$ | No | Sì | Interi con $d$ cifre |
