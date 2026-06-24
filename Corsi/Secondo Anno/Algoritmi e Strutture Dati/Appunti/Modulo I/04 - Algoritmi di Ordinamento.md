# Algoritmi di Ordinamento
L'ordinamento è uno dei problemi fondamentali dell'informatica e costituisce la subroutine di moltissimi algoritmi. Conoscere i limiti teorici del problema — non solo le soluzioni pratiche — permette di capire quando un algoritmo è ottimo e quando è invece possibile fare meglio cambiando modello computazionale. In questa nota si presentano gli algoritmi basati su confronti (quadratici e ottimi), il lower bound $\Omega(n \log n)$ (la cui notazione è formalizzata in [[02 - Notazioni Asintotiche]]), e gli algoritmi lineari che operano al di fuori del modello a confronti.
## Il problema dell'ordinamento
> [!quote] Definizione — Problema dell'Ordinamento
> **Input:** una sequenza di $n$ numeri $\langle a_1, a_2, \dots, a_n \rangle$.
> **Output:** una permutazione $\langle a'_1, a'_2, \dots, a'_n \rangle$ della sequenza di input tale che $a'_1 \le a'_2 \le \dots \le a'_n$.

L'insieme degli elementi deve provenire da un **dominio totalmente ordinato**. Il problema ha diretta applicazione nelle ricerche: un array ordinato si può visitare in $O(\log n)$ con la ricerca binaria.
### Upper e lower bound del problema
> [!quote] Proprietà — Upper e Lower Bound dell'Ordinamento
> - **Upper bound $O(n^2)$:** Selection Sort, Insertion Sort, Bubble Sort, Quick Sort (caso peggiore).
> - **Upper bound $O(n \log n)$:** Merge Sort, Heap Sort.
> - **Lower bound banale $\Omega(n)$:** ogni algoritmo deve almeno leggere tutti gli $n$ elementi.
> - **Lower bound $\Omega(n \log n)$:** per qualsiasi algoritmo basato su confronti (dimostrato con l'albero di decisione — vedi §[[#Lower bound per confronti: l'albero di decisione]]).

Tra l'upper bound $O(n \log n)$ e il lower bound $\Omega(n \log n)$ non c'è gap: Merge Sort e Heap Sort sono **algoritmi ottimi** nella classe degli algoritmi basati su confronti.
## Ordinamento quadratico
Gli algoritmi quadratici usano un **approccio incrementale**: estendono l'ordinamento da $k$ a $k+1$ elementi, un passo alla volta. Sono semplici da implementare ma inefficienti su istanze grandi.
### Selection Sort
**Approccio incrementale:** al passo $k$, cerca il minimo tra gli elementi non ancora ordinati $A[k+1], \dots, A[n]$ e lo mette in posizione $k+1$.

**SelectionSort**
```text
SelectionSort(A)
1.  for k = 0 to n-2 do
2.      m = k+1
3.      for j = k+2 to n do
4.          if A[j] < A[m] then m = j
5.      scambia A[m] con A[k+1]
```
> [!quote] Proprietà — Invariante del Selection Sort
> Dopo la fase $k$ (per $k = 0, \dots, n-2$):
> 1. i primi $k+1$ elementi sono ordinati;
> 2. sono i $k+1$ elementi più piccoli dell'array.

**Complessità:** il ciclo interno esegue esattamente $n-k-1$ confronti al passo $k$, quindi
$$T(n) = \sum_{k=0}^{n-2}(n-k-1) = \sum_{j=1}^{n-1} j = \frac{n(n-1)}{2} = \Theta(n^2).$$
La complessità è $\Theta(n^2)$ in tutti i casi (l'analisi è stretta: si contano i confronti).
> [!info] Proprietà del Selection Sort
> - **In loco:** sì — usa $O(1)$ memoria ausiliaria.
> - **Stabile:** no — uno scambio può alterare l'ordine relativo di elementi uguali.
> - **Complessità:** $\Theta(n^2)$ in ogni caso (migliore = peggiore = medio).
### Insertion Sort
**Approccio incrementale:** al passo $k$, inserisce l'elemento $(k+1)$-esimo nella posizione corretta rispetto ai primi $k$ elementi già ordinati.

**InsertionSort**
```text
InsertionSort(A)
1.  for k = 1 to n-1 do
2.      x = A[k+1]
3.      j = k
4.      while j > 0 e A[j] > x do
5.          A[j+1] = A[j]
6.          j = j-1
7.      A[j+1] = x
```
> [!quote] Proprietà — Invariante del Insertion Sort
> All'inizio dell'iterazione $k$, il sottoarray $A[1 \dots k]$ contiene gli stessi $k$ elementi originali in ordine crescente.

**Complessità:**
- **Caso peggiore** (array ordinato al contrario): $T(n) = \Theta(n^2)$.
- **Caso migliore** (array già ordinato): $T(n) = \Theta(n)$ — solo $n-1$ confronti, nessuno spostamento.
- **Caso medio:** $\Theta(n^2)$.
> [!info] Proprietà del Insertion Sort
> - **In loco:** sì.
> - **Stabile:** sì — l'elemento viene inserito *dopo* tutti gli uguali già presenti.
> - **Utile in pratica** per array piccoli o quasi ordinati.
### Bubble Sort
**Approccio incrementale:** esegue $n-1$ scansioni; ad ogni scansione confronta coppie di elementi adiacenti e li scambia se sono fuori ordine. Alla $k$-esima scansione il $k$-esimo massimo "risale" in posizione.

**BubbleSort**
```text
BubbleSort(A)
1.  for k = 1 to n-1 do
2.      for j = 1 to n-k do
3.          if A[j] > A[j+1] then
4.              scambia A[j] con A[j+1]
```
**Complessità:** $\Theta(n^2)$ in tutti i casi (stessa analisi del Selection Sort sul conteggio dei confronti).
> [!info] Proprietà del Bubble Sort
> - **In loco:** sì.
> - **Stabile:** sì — lo scambio avviene solo con $>$ stretto.
> - **Complessità:** $\Theta(n^2)$ sempre.
## Ordinamento ottimo: Divide et Impera
Questi algoritmi usano la tecnica [[03 - Equazioni di Ricorrenza|Divide et Impera]] per ottenere $\Theta(n \log n)$ o $O(n \log n)$.
### Merge Sort
**Schema Divide et Impera:**
1. **Divide:** dividi l'array $A[i \,;\, f]$ a metà calcolando $m = \lfloor(i+f)/2\rfloor$.
2. **Risolvi** ricorsivamente i due sottoproblemi $A[i \,;\, m]$ e $A[m+1 \,;\, f]$.
3. **Impera:** fondi le due sottosequenze ordinate con la procedura Merge.

Rispetto al Quick Sort, la fase di *divide* è banale e quella di *impera* (Merge) è la parte complessa.

**MergeSort**
```text
MergeSort(A, i, f)                  -- ordina A[i;f]
1.  if i < f then
2.      m = ⌊(i+f)/2⌋
3.      MergeSort(A, i, m)
4.      MergeSort(A, m+1, f)
5.      Merge(A, i, m, f)
```
Chiamata iniziale: `MergeSort(A, 1, n)`.
> [!quote] Lemma — Complessità di Merge
> La procedura Merge fonde due sequenze ordinate di lunghezza $n_1$ e $n_2$ in tempo $\Theta(n_1 + n_2)$.
>
> **Dimostrazione:** ogni confronto "consuma" un elemento di una delle due sequenze; ogni posizione dell'array ausiliario $X$ è riempita in tempo costante; anche la copia finale di $X$ costa $\Theta(n_1+n_2)$.

**Merge**
```text
Merge(A, i1, f1, f2)               -- fonde A[i1;f1] e A[f1+1;f2], output in A[i1;f2]
1.  Sia X un array ausiliario di lunghezza f2-i1+1
2.  i = 1;  k1 = i1;  k2 = f1+1
3.  while k1 ≤ f1 e k2 ≤ f2 do
4.      if A[k1] ≤ A[k2]
5.      then X[i] = A[k1];  incrementa i e k1
6.      else X[i] = A[k2];  incrementa i e k2
7.  if k1 ≤ f1 then copia A[k1;f1] alla fine di X
8.  else copia A[k2;f2] alla fine di X
9.  copia X in A[i1;f2]
```
> [!quote] Teorema — Complessità del Merge Sort
> La complessità temporale del Merge Sort soddisfa la ricorrenza
> $$T(n) = 2\,T(n/2) + O(n).$$
> Applicando il [[03 - Equazioni di Ricorrenza#4. Teorema Master|Teorema Master]] (caso 2, con $a=b=2$, $f(n)=O(n)$) si ottiene $T(n) = \Theta(n \log n)$.

**Complessità spaziale:** il Merge Sort **non ordina in loco** — utilizza $\Theta(n)$ memoria ausiliaria (l'array $X$ nelle chiamate attive non è mai sovrapposto; le chiamate ricorsive attive contemporaneamente sono $O(\log n)$, ciascuna con memoria costante esclusa quella di Merge).
> [!info] Proprietà del Merge Sort
> - **In loco:** no — $\Theta(n)$ memoria ausiliaria.
> - **Stabile:** sì — il Merge usa $\le$ (non $<$) per favorire l'elemento di sinistra in caso di parità.
> - **Complessità:** $\Theta(n \log n)$ in ogni caso.
### Quick Sort
**Schema Divide et Impera:**
1. **Divide:** scegli un elemento $x$ (il **perno**) e partiziona $A[i \,;\, f]$ in elementi $\le x$ e elementi $> x$.
2. **Risolvi** ricorsivamente le due parti.
3. **Impera:** la concatenazione è implicita — l'array è già in loco.

Rispetto al Merge Sort, la fase di *divide* (Partition) è la parte complessa, mentre la fase di *impera* è banale.

**QuickSort**
```text
QuickSort(A, i, f)                  -- ordina A[i;f]
1.  if i < f then
2.      m = Partition(A, i, f)
3.      QuickSort(A, i, m-1)
4.      QuickSort(A, m+1, f)
```
Chiamata iniziale: `QuickSort(A, 1, n)`.
#### La procedura Partition
Il perno è scelto come $x = A[i]$ (primo elemento). Due indici scorrono l'array in parallelo: `inf` da sinistra verso destra si ferma sul primo elemento $> x$; `sup` da destra verso sinistra si ferma sul primo elemento $\le x$. Quando entrambi si sono fermati si scambiano i due elementi; si continua finché i due indici non si incrociano. Alla fine, il perno viene posizionato al centro.

**Partition**
```text
Partition(A, i, f)                  -- partiziona A[i;f] rispetto ad A[i]
1.  x = A[i]
2.  inf = i
3.  sup = f+1
4.  while true do
5.      do (inf = inf+1) while (inf ≤ f e A[inf] ≤ x)
6.      do (sup = sup-1) while (A[sup] > x)
7.      if inf < sup then scambia A[inf] e A[sup]
8.      else break
9.  scambia A[i] e A[sup]          -- posiziona il perno
10. return sup                      -- restituisce la posizione del perno
```
> [!quote] Proprietà — Invariante di Partition
> In ogni istante, gli elementi $A[i], \dots, A[\text{inf}-1]$ sono $\le$ del perno, mentre gli elementi $A[\text{sup}+1], \dots, A[f]$ sono $>$ del perno.

Tempo di esecuzione di Partition: $O(n)$.

**Correttezza del Quick Sort:** dopo Partition, $A[i \,;\, m-1]$ contiene elementi $\le$ del perno, $A[m]$ è il perno nella sua posizione definitiva, $A[m+1 \,;\, f]$ contiene elementi $>$ del perno. Le chiamate ricorsive completano l'ordinamento.
#### Analisi della complessità
**Caso peggiore:** il perno è sempre il minimo o il massimo degli elementi (ad esempio, array già ordinato con perno = primo elemento). La partizione è massimamente sbilanciata:
$$T(n) = T(n-1) + T(0) + O(n) = T(n-1) + O(n) \implies T(n) = O(n^2).$$
**Caso migliore:** il perno divide sempre perfettamente a metà: $T(n) = 2T(n/2) + O(n) = O(n \log n)$.

**Caso medio:** si può dimostrare che, assumendo distribuzione uniforme sulle istanze, Quick Sort ha complessità media $O(n \log n)$. Anche con partizioni sistematicamente sbilanciate (es. 9-a-1 o 99-a-1) la complessità resta $O(n \log n)$.
> [!warning] Caso peggiore del Quick Sort
> Il caso peggiore $O(n^2)$ si verifica su input specifici (es. array già ordinato con perno = primo elemento). Per evitarlo si usa la **versione randomizzata**.
#### Versione randomizzata
Anziché scegliere il perno come $A[i]$, lo si estrae a caso tra gli elementi $A[i], \dots, A[f]$.
> [!quote] Teorema — Quick Sort Randomizzato
> L'algoritmo Quick Sort randomizzato ordina in loco un array di lunghezza $n$ in tempo $O(n^2)$ nel caso peggiore e $O(n \log n)$ **con alta probabilità**, ovvero con probabilità almeno $1 - 1/n$.

I vantaggi rispetto alla versione deterministica:
- non si fa alcuna assunzione sulla distribuzione delle istanze;
- non esiste un input specifico che provochi sistematicamente il caso peggiore;
- il caso peggiore dipende solo dal generatore di numeri casuali.
> [!info] Proprietà del Quick Sort
> - **In loco:** sì.
> - **Stabile:** no — gli scambi di Partition non preservano l'ordine relativo.
> - **Complessità:** $O(n^2)$ nel caso peggiore, $O(n \log n)$ atteso/con alta probabilità (versione randomizzata).
### Heap Sort
Heap Sort adotta lo stesso **approccio incrementale** del Selection Sort — seleziona iterativamente il massimo — ma usa un **max-heap** come struttura dati ausiliaria per ridurre il costo di ogni estrazione da $O(n)$ a $O(\log n)$.

Per la definizione di heap, le proprietà strutturali, la procedura `fixHeap` e la costruzione tramite `heapify` si rimanda a [[07 - Code con Priorità e Heap]]. Si richiamano qui solo le proprietà essenziali:
- il massimo è nella radice;
- l'altezza di un heap con $n$ nodi è $O(\log n)$;
- `fixHeap` ripristina la proprietà heap in $O(\log n)$;
- `heapify` costruisce un heap in tempo $O(n)$.

**HeapSort**
```text
HeapSort(A)
1.  Heapify(A)                      -- costruisce il max-heap: O(n)
2.  heapsize[A] = n
3.  for i = n downto 2 do           -- n-1 estrazioni
4.      scambia A[1] e A[i]         -- sposta il massimo nella posizione i
5.      heapsize[A] = heapsize[A]-1 -- riduce l'heap
6.      fixHeap(1, A)               -- ripristina la proprietà heap: O(log n)
```
> [!info] Perché max-heap e non min-heap?
> L'uso del **max-heap** implementato con vettore posizionale permette di ordinare in loco usando **solo memoria ausiliaria costante**: il massimo estratto va nella posizione $A[i]$ appena liberata. Con un min-heap si otterrebbe l'ordine decrescente, non crescente, a meno di un'inversione finale.

> [!quote] Teorema — Complessità di Heap Sort
> L'algoritmo Heap Sort ordina in loco un array di lunghezza $n$ in tempo $O(n \log n)$ **nel caso peggiore**.
>
> **Dimostrazione:** `Heapify` costa $O(n)$; ogni delle $n-1$ chiamate a `fixHeap` costa $O(\log n)$; quindi $T(n) = O(n) + (n-1) \cdot O(\log n) = O(n \log n)$.
> [!info] Proprietà di Heap Sort
> - **In loco:** sì — a differenza del Merge Sort, usa solo $O(1)$ memoria ausiliaria.
> - **Stabile:** no.
> - **Complessità:** $O(n \log n)$ nel caso peggiore (garanzia più forte del Quick Sort non randomizzato).
## Lower bound per confronti: l'albero di decisione
Un **algoritmo di ordinamento per confronti** può accedere ai dati solo tramite confronti del tipo $a_i \le a_j$, $a_i < a_j$, ecc. Tutti gli algoritmi visti finora (Selection, Insertion, Bubble, Merge, Quick, Heap Sort) rientrano in questa classe.
> [!quote] Definizione — Albero di Decisione
> L'**albero di decisione** di un algoritmo di ordinamento per confronti, fissata la dimensione $n$ dell'input, è un albero binario in cui:
> - ogni **nodo interno** etichettato $i\!:\!j$ modella il confronto tra $a_i$ e $a_j$;
> - ogni **foglia** modella un possibile output (permutazione degli elementi).
>
> Un cammino radice–foglia corrisponde alla sequenza di confronti eseguiti su una particolare istanza. Il caso peggiore è il cammino più lungo, cioè l'**altezza** dell'albero.

**Osservazioni chiave:**
- L'albero di decisione dipende dall'algoritmo *e* dalla dimensione $n$ dell'input (non è associato solo al problema).
- Un algoritmo corretto deve produrre un output distinto per ciascuna delle $n!$ permutazioni possibili → l'albero deve avere **almeno $n!$ foglie**.
> [!quote] Lemma — Altezza di un albero binario
> Un albero binario $T$ con $k$ foglie ha altezza almeno $\log_2 k$.
>
> **Dimostrazione** (induzione su $k$): per $k=1$ l'altezza è $0 = \log_2 1$. Per $k > 1$, considera il nodo interno $v$ più vicino alla radice che ha due figli; il sottoalbero radicato in un figlio di $v$ ha almeno $\lceil k/2 \rceil$ foglie e meno di $k$ foglie, quindi per ipotesi induttiva ha altezza $\ge \log_2\lceil k/2 \rceil$; l'altezza di $T$ è almeno $1 + \log_2\lceil k/2 \rceil \ge \log_2 k$.
> [!quote] Teorema — Lower Bound $\Omega(n \log n)$
> Ogni algoritmo basato su confronti che ordina $n$ elementi deve effettuare nel caso peggiore $\Omega(n \log n)$ confronti.
>
> **Dimostrazione:** l'altezza $h$ dell'albero di decisione è almeno $\log_2(n!)$. Per la formula di Stirling $n! \ge (n/e)^n$, quindi
> $$h \ge \log_2(n!) \ge \log_2\!\left(\frac{n}{e}\right)^{\!n} = n\log_2 n - n\log_2 e = \Omega(n \log n).$$
> [!quote] Corollario
> Merge Sort e Heap Sort sono **algoritmi ottimi** all'interno della classe degli algoritmi basati su confronti.
> [!example] Domanda tipica d'esame
> D: Perché il lower bound $\Omega(n \log n)$ non contraddice la possibilità di ordinare in $O(n)$?
>
> R: Il lower bound vale **solo per gli algoritmi basati su confronti**. Algoritmi come Integer Sort o Radix Sort non usano confronti tra elementi ma sfruttano le proprietà numeriche dei valori — quindi operano fuori dalla classe a cui si applica il lower bound.
## Ordinamento lineare (senza confronti)
Uscendo dalla classe degli algoritmi basati su confronti è possibile superare il limite $\Omega(n \log n)$, a patto di avere **informazioni aggiuntive** sui dati (es. range limitato).
> [!warning] Il lower bound non si applica
> Integer Sort e Bucket Sort non sono algoritmi basati su confronti: non esaminano l'ordine relativo degli elementi tramite $\le$ o $<$, ma sfruttano i valori numerici come indici. Pertanto la dimostrazione dell'albero di decisione non li riguarda.
### Integer Sort (Counting Sort)
Ordina $n$ **interi** con valori in $[1, k]$ mantenendo un array $Y$ di $k$ contatori: $Y[x]$ = numero di occorrenze del valore $x$ in $X$.

**IntegerSort**
```text
IntegerSort(X, k)
1.  Sia Y un array di dimensione k
2.  for i = 1 to k do Y[i] = 0          -- O(k): inizializza contatori
3.  for i = 1 to n do incrementa Y[X[i]] -- O(n): conta le occorrenze
4.  j = 1
5.  for i = 1 to k do                    -- O(n+k): ricostruisce X
6.      while Y[i] > 0 do
7.          X[j] = i
8.          incrementa j
9.          decrementa Y[i]
```
**Analisi del ciclo riga 5–9:**
$$\sum_{i=1}^{k}(1 + Y[i]) = k + \sum_{i=1}^{k} Y[i] = k + n \implies O(n+k).$$
> [!quote] Proprietà — Complessità di Integer Sort
> $T(n) = O(n+k)$. **Lineare se $k = O(n)$.**
>
> Se $k = \Theta(n^c)$ con $c > 1$, allora $T(n) = \Theta(n^c) = \omega(n \log n)$: non conviene.
> [!info] Proprietà di Integer Sort
> - **In loco:** no — array ausiliario $Y$ di dimensione $k$.
> - **Stabile:** no nella versione base (sovrascrive $X$); diventa stabile con il Bucket Sort.
> - **Condizione di linearità:** $k = O(n)$.
### Bucket Sort
Estende Integer Sort al caso di **record** con chiave intera in $[1, k]$ e informazioni satellite. Anziché contatori, mantiene un array $Y$ di **liste**: la lista $Y[i]$ contiene tutti i record con chiave $= i$.

**BucketSort**
```text
BucketSort(X, k)
1.  Sia Y un array di dimensione k
2.  for i = 1 to k do Y[i] = lista vuota -- O(k)
3.  for i = 1 to n do                     -- O(n)
4.      appendi il record X[i] alla lista Y[chiave(X[i])]
5.  for i = 1 to k do                     -- O(n+k)
6.      copia ordinatamente in X gli elementi della lista Y[i]
```
Tempo totale: $O(n+k)$, lineare se $k = O(n)$.
> [!quote] Proprietà — Stabilità del Bucket Sort
> Il Bucket Sort è **stabile** se gli elementi vengono appesi **in coda** alla lista $Y[i]$ (non in testa): l'ordine di inserimento è preservato tra elementi con la stessa chiave.

La stabilità è fondamentale perché il Radix Sort usa Bucket Sort come subroutine stabile.
### Radix Sort
Ordina $n$ interi con valori in $[1, k]$ **rappresentandoli in base $b$** ed eseguendo una serie di passate di Bucket Sort, dalla cifra **meno significativa** alla più significativa.

**Algoritmo:**
1. Rappresenta ogni elemento con $d = \lceil \log_b k \rceil$ cifre in base $b$.
2. Per $t = 1, \dots, d$: esegui un Bucket Sort stabile usando la $t$-esima cifra come chiave (la chiave è un intero in $[0, b-1]$).
> [!quote] Proprietà — Correttezza del Radix Sort
> - Se $x$ e $y$ differiscono alla cifra $t$, la $t$-esima passata li ordina correttamente.
> - Se $x$ e $y$ coincidono alla cifra $t$, la **stabilità** del Bucket Sort garantisce che il loro ordine relativo (stabilito dalle passate precedenti) venga preservato.
>
> Invariante: dopo la $t$-esima passata, gli elementi sono correttamente ordinati rispetto alle $t$ cifre meno significative.

**Complessità:** $O(\log_b k)$ passate, ciascuna di costo $O(n + b)$, quindi
$$T(n) = O\!\left((n+b)\log_b k\right).$$
Usando la conversione di base $\log_b k = \dfrac{\log_2 k}{\log_2 b}$:
$$T(n) = O\!\left((n+b)\cdot\frac{\log k}{\log b}\right).$$
Con la scelta ottimale $b = \Theta(n)$:
$$T(n) = O\!\left(n \cdot \frac{\log k}{\log n}\right).$$
**Lineare se $k = O(n^c)$** con $c$ costante (numero di cifre $d$ costante).
> [!example] Scelta della base per 32 bit
> Si vogliono ordinare $10^6 \approx 2^{20}$ numeri da 32 bit ($k = 2^{32}$).
> Scegliendo $b = 2^{16}$: servono $\lceil 32/16 \rceil = 2$ passate, ciascuna di costo $O(n + 2^{16}) = O(n)$. Totale: $O(n)$.
> [!info] Proprietà del Radix Sort
> - **Stabile:** sì (richiede Bucket Sort stabile come subroutine).
> - **In loco:** no.
> - **Condizione di linearità:** $k = O(n^c)$, $c$ costante.
## Applicazione: Oracolo per Range Counting
> [!quote] Definizione — Problema dell'Oracolo
> Dato un vettore $X$ di $n$ interi in $[1, k]$, costruire in tempo $O(n+k)$ una struttura dati che risponda in tempo $O(1)$ a query del tipo: **"quanti interi di $X$ cadono nell'intervallo $[a, b]$?"**

**Soluzione 1 — risposta al volo:** costruzione $O(1)$, query $\Theta(n)$. Troppo lenta.

**Soluzione 2 — precalcolo di tutte le query:** costruzione $\Omega(k^2)$, query $O(1)$. Troppo pesante in costruzione.

**Soluzione ottimale — prefix sums:**
> [!quote] Proprietà — Costruzione dell'Oracolo con Somme Prefisse
> Si costruisce un array $Y$ di dimensione $k$ dove $Y[i]$ = numero di elementi di $X$ che sono $\le i$ (somma prefissa dei contatori).

**CostruisciOracolo**
```text
CostruisciOracolo(X, k)
1.  Sia Y un array di dimensione k
2.  for i = 1 to k do Y[i] = 0
3.  for i = 1 to n do incrementa Y[X[i]]   -- conta le occorrenze (come IntegerSort)
4.  for i = 2 to k do Y[i] = Y[i] + Y[i-1] -- somme prefisse
5.  return Y
```
**InterrogaOracolo**
```text
InterrogaOracolo(Y, k, a, b)
1.  if b > k then b = k
2.  if a ≤ 1 then return Y[b]
3.  else return Y[b] - Y[a-1]
```
> [!quote] Proprietà — Complessità dell'Oracolo
> - **Costruzione:** $O(n+k)$.
> - **Ogni query:** $O(1)$ — una sola sottrazione.
> - **Spazio:** $O(k)$.

La correttezza si basa sul fatto che $Y[b] - Y[a-1]$ conta esattamente gli elementi in $[a, b]$: $Y[b]$ è il numero di elementi $\le b$, e $Y[a-1]$ è il numero di elementi $\le a-1$ (ovvero $< a$).
> [!example] Domanda tipica d'esame
> D: Dato un vettore $A$ di $n$ numeri reali arbitrari, è possibile costruire un oracolo per range counting con costruzione $O(n \log n)$ e query $O(\log n)$?
>
> R: Sì. Si ordina $A$ con Merge Sort o Heap Sort in $O(n \log n)$, poi si risponde a ogni query $[a, b]$ con due ricerche binarie (trovare il primo elemento $\ge a$ e l'ultimo $\le b$), ciascuna in $O(\log n)$. (Non è richiesto che i valori siano interi né che il range sia limitato.)
## Tabella riassuntiva
| Algoritmo | Caso migliore | Caso peggiore | Caso medio | In loco | Stabile |
|---|---|---|---|---|---|
| Selection Sort | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | No |
| Insertion Sort | $\Theta(n)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | Sì |
| Bubble Sort | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | Sì | Sì |
| Merge Sort | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $\Theta(n \log n)$ | No | Sì |
| Quick Sort | $\Theta(n \log n)$ | $O(n^2)$ | $\Theta(n \log n)$ | Sì | No |
| Quick Sort rand. | $\Theta(n \log n)$ | $O(n^2)$ | $\Theta(n \log n)$ atteso | Sì | No |
| Heap Sort | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $\Theta(n \log n)$ | Sì | No |
| Integer Sort | $\Theta(n+k)$ | $\Theta(n+k)$ | $\Theta(n+k)$ | No | No |
| Bucket Sort | $\Theta(n+k)$ | $\Theta(n+k)$ | $\Theta(n+k)$ | No | Sì |
| Radix Sort | $\Theta((n+b)\log_b k)$ | $\Theta((n+b)\log_b k)$ | $\Theta((n+b)\log_b k)$ | No | Sì |

> [!info] Algoritmi ottimi
> Merge Sort e Heap Sort sono ottimi nella classe dei confronti: raggiungono il lower bound $\Theta(n \log n)$ nel caso peggiore. Integer Sort, Bucket Sort e Radix Sort operano fuori da tale classe e possono essere lineari sotto ipotesi sul range dei valori.
