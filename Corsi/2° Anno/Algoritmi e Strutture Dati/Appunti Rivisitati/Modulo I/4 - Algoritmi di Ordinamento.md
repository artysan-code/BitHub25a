> [!abstract] Introduzione
> Gli **algoritmi di ordinamento** sono procedure fondamentali in informatica che permettono di riorganizzare una sequenza di elementi secondo un determinato criterio di ordinamento. Esistono numerose strategie per risolvere questo problema, ciascuna con caratteristiche, vantaggi e svantaggi specifici.

### Problema dell'Ordinamento
> [!question] Definizione del Problema
> Dato un insieme $S$ di $n$ oggetti presi da un dominio totalmente **ordinato**, ordinare $S$.

**Input:** n numeri

**Output:** una *permutazione* dell'input ordinata in maniera crescente o decrescente.

> [!note]
> Vi sono diversi metodi per farlo e hanno ottimizzazioni e casi diversi. In particolare, distinguiamo tra **algoritmi basati su confronti** e **algoritmi non basati su confronti**.

---
### Delimitazioni inferiori e superiori
#### Complessità di un algoritmo
> Un algoritmo $A$ ha complessità (costo di esecuzione) $O(f(n))$ rispetto ad una certa risorsa di calcolo, se la quantità $r(n)$ di risorsa usata da $A$ nel caso peggiore su $n$ istanze rispetta la relazione $r(n)=O(f(n))$.

> Un algoritmo $A$ ha complessità (costo di esecuzione) $\Omega$(f(n)) rispetto ad una certa risorsa di calcolo, se la quantità $r(n)$ di risorsa usata da $A$ nel caso peggiore su $n$ istanze verifica la relazione $r(n)= \Omega(f(n))$.
#### Complessità di un problema
> Un problema $P$ ha una complessità $O(f(n))$ rispetto ad una risorsa di calcolo se **esiste** un algoritmo che risolve $P$ il cui costo di esecuzione rispetto quella risorsa è $O(f(n))$.

> Un problema $P$ ha una complessità $\Omega(f(n))$ rispetto ad una risorsa di calcolo se **ogni algoritmo** che risolve $P$ ha costo di esecuzione nel caso peggiore $\Omega(f(n))$ rispetto quella risorsa.
### Algoritmo Ottimo
Dato un problema $P$ con complessità $\Omega(f(n))$ rispetto ad una risorsa di calcolo, un algoritmo che risolve $P$ è (asintoticamente) **ottimo** se ha costo di esecuzione $O(f(n))$ rispetto a quella risorsa.
###  Complessità temporale del problema dell'ordinamento
- Upper bound: $O(n^2)$
	- InsertionSort, SelectionSort, QuickSort, BubbleSort.
- Un Upper bound **migliore**: $O(n\log n)$
	- MergeSort, HeapSort.
- Lower bound: $\Omega(n)$
	- Banale: ogni algoritmo che ordina n elementi li deve almeno leggere tutti

Abbiamo un gap di $\log n$ tra upper e lower bound. Si può fare di meglio?

---
### Ordinamento per confronti

> [!info] Introduzione agli algoritmi basati su confronti
> Gli **algoritmi di ordinamento per confronti** determinano l'ordine degli elementi esclusivamente confrontando coppie di elementi. Questa è la classe più comune di algoritmi di ordinamento.

**Operazioni permesse:**
Dati due elementi $a_{i}$ ed $a_{j}$, per determinarne l'ordinamento relativo effettuiamo una delle seguenti operazioni di confronto:

$$a_{i}<a_{j};\quad a_{i}\leq a_{j};\quad a_{i}=a_{j};\quad a_{i}\geq a_{j};\quad a_{i}>a_{j}$$

Non si possono esaminare i valori degli elementi o ottenere informazioni sul loro ordine in altro modo.

> [!important] Proprietà fondamentale
> Ogni algoritmo basato su confronti che ordina $n$ elementi deve fare nel caso peggiore $\Omega(n\log n)$ confronti quindi il $\#\text{ di confronti}$ che un algoritmo esegue è un lower bound del $\#\text{ di passi elementari}$ che esegue.

> [!success] Algoritmi ottimi
> Il MergeSort e il QuickSort sono algoritmi ottimi (almeno dentro la classe di algoritmi basati su confronti).

---
#### Albero di decisione
Gli algoritmi di ordinamento per confronto posso essere descritti in modo astratto tramite gli **alberi di decisione**.

Generalmente un algoritmo di confronto lavora in questo modo:
- Confronta due elementi $a_{i}$ e $a_{j}$.
- Riordina e passa al successivo.

Quindi descrive i confronti di un algoritmo su un determinato input, guardando ogni casistica possibile di confronto. Vengono ignorati i movimenti di dati. Quindi:
- Descrive le diverse sequenze di confronti che A potrebbe fare su un input n.
- Ogni **nodo interno** ha un confronto di tipo $i:j$ con due possibilità.
- Ogni **nodo foglia** è un risultato di un determinato caso.

L'albero di decisione non **è legato al problema** e non è **associato solo ad un algoritmo**.
![](assets/l81.png)
L'albero di decisione è però legato ad un algoritmo e ad una dimensione di istanza, descrivendo le diverse casistiche che possono avvenire di output su una generica istanza di dimensione n. Corrisponde ad una descrizione alternativa di un algoritmo.

##### Proprietà
- I confronti eseguiti sull'algoritmo rappresentano un cammino radice-foglia.
- Un cammino ha caratteristiche diverse a seconda dell'istanza e quindi l'istanza peggiore è il cammino più lungo.
- Il numero di confronti nel caso peggiore è pari all'**altezza dell'albero di decisione**.
- Un albero di decisione di un *algoritmo corretto* che riordina per confronto n elementi deve necessariamente avere **n! foglie**.

> Un **albero binario T** con k foglie ha altezza almeno $\log_{2}(n)$.

##### Il Lower Bound $\Omega(n\log(n))$
Considerando un *qualsiasi algoritmo* che risolve un problema di ordinamento per confronto di n elementi, l'altezza dell'albero di decisione di almeno $\log_{2}(n!)$. Quindi dalla [[4.5 Prodotti#^0c4ae5|Formula di Stirling]] sappiamo che:$$n!=\sqrt{ 2\pi n }\cdot\left( \frac{n}{e} \right)^n$$
Allora possiamo dedurre che:$$h\geq \log_{2}(n!)>\log_{2}\left( \frac{n}{e} \right)^n=n\log_{2}(n)-n\log_{2}(e)=\Omega(n\log(n))$$

---
#### Algoritmi di Ordinamento Quadratico
> [!info] Caratteristiche
> Algoritmi semplici da capire ed implementare, ma poco efficienti. Hanno complessità temporale $O(n^2)$.

##### Selection Sort
> [!tip] Idea dell'algoritmo
> In questo algoritmo, in modo iterativo, cerco l'elemento minimo dell'array e lo sostituisco con la k-esima posizione (quindi estendiamo l'ordinamento a k+1).
>
> Ovviamente in questo algoritmo k risulta essere la posizione su cui abbiamo ordinato.

![](assets/m14.png)

**Pseudo-codice:**
> $\text{SelectionSort}(array\ A)$
> 1.   $\text{for } k=0\text{ to } n-2 \text{ do}$
> 2.      $m = k + 1$
> 3.      $\text{for }j=k+2\text{ to }n\text{ do}$
> 4.         $\text{if }(A[j] < A[m])\text{ then }m=j$
> 5.      $\text{scambia }A[m]\text{ con }A[k+1]$

**Implementazione Python:**
```python
def selection_sort(array: list):
	for i in range(1, len(array)):
		key = arr[i]
		j = i-1
		while j >= 0 and key < arr[j]:
			arr[j + 1] = arr[j]
			j -= 1
		arr[j + 1] = key
	return arr
```

> [!check] Correttezza
> L'algoritmo è banalmente **corretto** e mantiene le seguenti **invarianti**:
> - I primi k+1 elementi sono ordinati.
> - I primi k+1 elementi sono i più piccoli dell'array.

###### Analisi del costo
Chiamiamo:
$$
\begin{array}{r}
T(n)=\text{\# operazioni elementari sul modello RAM a costi uniformi} \\
\text{eseguite dall'algoritmo nel caso peggiore su istanze di dimensione n}
\end{array}
$$

Se ogni linea di codice costa $O(1)$ e ogni ciclo (come si può vedere) viene eseguito al più n volte, avendo due cicli:
$$T(n)\leq 5n^2\cdot O(1)=\Theta (n^2) \implies T(n) =O(n^2)$$

> [!question] Ma l'analisi è **stretta**?

Cioè, $T(n)=\Theta(n^2)$? Analizziamo la linea più importante nel codice che corrisponde a: `if (A[j] < A[m]) then m=j`. Quindi:

$$T(n)\geq \displaystyle\sum_{k=0}^{n-2} (n-k-1)=\displaystyle\sum_{k=0}^{n-1} \frac{n(n-1)}{2}=\Theta (n^2)\quad \implies\quad T(n) = \Omega (n^2)$$

> [!success] Conclusione
> $$T(n)=\Theta (n^2)$$

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
##### Insertion Sort
> [!tip] Idea dell'algoritmo
> Estendiamo l'ordinamento da k a k+1 elementi, posizioniamo l'elemento (k+1)-esimo nella posizione corretta rispetto ai primi k elementi.

![](assets/m15.png)

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
##### Bubble Sort
> [!tip] Idea dell'algoritmo
> Eseguiamo n-1 scansioni, dove ad ogni scansione guardiamo le coppie di elementi adiacenti e li scambiamo nell'ordine corretto.

![](assets/m16.png)

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
#### Algoritmi di Ordinamento Sub-quadratico
> [!info] Caratteristiche
> Algoritmi più complessi ma molto più efficienti, con complessità temporale $O(n\log n)$.

##### Merge Sort
> [!tip] Tecnica utilizzata: Divide et Impera
> Per questo algoritmo usiamo la tecnica **divide et impera**:
> - **Divide:** dividi l'array a metà
> - **Risolvi** i due problemi ricorsivamente
> - **Impera:** fondi le due sotto-sequenze ordinate

**Pseudo-codice principale:**
> $\text{MergeSort}(array A,\ int\ i,\ int\ f)$
> 1.   $\text{if }(i < f)\text{ then}$
> 2.      $\displaystyle m = \left\lfloor  \frac{i+f}{2}  \right\rfloor$
> 3.      $\text{MergeSort}(A,\ i,\ m)$
> 4.      $\text{MergeSort}(A,\ m+1,\ f)$
> 5.      $\text{Merge}(A, i, m, f)$

**Albero di ricorsione:**
![](assets/l64.png)

> [!info] Come funziona
> Avendo un array di dimensione `n`, lo dividiamo a metà, eseguiamo la chiamata ricorsiva sulla metà e quando ritorna sarà ordinata, uguale per l'altra metà. Quando entrambe sono ordinate vengono unite tramite il **merge**.

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

###### Procedura merge
> [!tip] Idea della procedura
> Dati due array ordinati A e B, essi possono essere fusi rapidamente:
> - Estrai ripetutamente il minimo di A e B e copialo nell'array di output fino a che A o B non diventa vuoto.
> - Copia gli elementi dell'array non vuoto alla fine dell'array di output.

**Pseudo-codice:**
> $\text{Merge}(A,\ left,\ mid,\ right)$
> 1.   $\text{Sia X un array ausiliario di lunghezza }f_2 - i_1 + 1$
> 2.   $i = 1;\ left_c = left;\ right_c=mid+1$
> 3.  $\text{while }(left_{c} \leq mid\ and\ right_{c} \leq right) do$
> 4.      $\text{if }(A[left_{c}] \leq A[right_{c}])$
> 5.         $\text{them }X[i] = A[left_{c}]\text{ e incrementa i e }left_c$
> 6.      $\text{else }X[i] = A[k_2]\text{ e incrementa i e }right_{c}$
> 7.   $\text{if }(left_{c} \leq mid)\text{ then copia }A[left_{c},\ mid]\text{ alla fine di X}$
> 8.   $\text{else copia }A[right_{c},\ right]\text{ alla fine di X}$
> 9.  $\text{copia X in }A[left,\ right]$

> [!note] Costo della procedura
> Quanto costa però? Fondendo le due sequenze ordinate costerà $\Theta(n_{1}+n_{2})$ essendo che deve **consumare** uno alla volta ogni elemento degli array.

###### Merge Sort (Tempo di esecuzione)
La complessità temporale del merge sort è descritta dalla seguente relazione di ricorsiva, caratterizzata dal costo di ogni ricorsione e il numero di ricorsioni:

$$T(n)=2\left( T\left( \frac{n}{2} \right) \right)+ O(n)$$

Usando il teorema master otteniamo:

$$T(n)=O(n\cdot \log(n))$$

###### Merge Sort (Memoria Ausiliaria)
> [!info] Complessità spaziale
> La complessità spaziale del Merge Sort è di $\Theta (n)$:
> - La procedura di merge usa memoria pari alla dimensione totale da fondere.
> - Non sono mai attive due procedure di merge contemporaneamente.
> - Ogni chiamata del Merge Sort usa memoria costante (esclusa la parte di merge).
> - Il numero di chiamate attive contemporaneamente è di $O(\log(n))$.

> [!warning]
> Il Merge Sort **non ordina in loco**.

---
##### Quick Sort
^ea3233

> [!info]
> Vi sono diverse versioni del quick sort: caso peggiore, caso medio e versione randomizzata.

> [!tip] Tecnica utilizzata: Divide et Impera
> Generalmente però, usa la tecnica del **divide et impera**:
> - **Divide**: scegli un elemento x della sequenza (perno) e partiziona la sequenza in elementi $\leq x$ e in elementi $>x$.
> - **Risolvi** i due problemi ricorsivamente.
> - **Impera**: restituisci la concatenazione delle due sotto-sequenze ordinate.

###### Funzione Partizione
> [!tip] Come funziona
> La funzione partizione usa un **perno** (ad esempio il primo elemento), scorrendo l'array in parallelo da sinistra verso destra fermandosi su un elemento maggiore del perno e viceversa fermandoci su uno minore del perno, scambia gli elementi e riprendi la scansione.
>
> Fermati quando i due indici sono incrociati.

![](assets/l65.png)

**Pseudo-codice:**
> $\text{Partition}(array\ A,\ int\ i,\ int\ f)\to int$
> 1.   $x=A[i]$
> 2.   $inf = i$
> 3.   $sup = f + 1$
> 4.   $\text{while }(true)\text{ do}$
> 5.      $\text{do }(inf = inf + 1)\text{ while } (inf \leq f\ \ and\ \ A[inf] \leq x)$
> 6.      $\text{do }(sup = sup - 1)\text{ while }(A[sup] > x)$
> 7.       $\text{if }(inf < sup)\text{ then scambia }A[inf] e A[sup]$
> 8.      $\textbf{else break}$
> 9.    $\text{scambia }A[i]\text{ e }A[sup]\text{ // mette il perno al centro}$
> 10.  $\textbf{return}\text{ sup // restituisce la posizione del perno}$

> [!note] Invariante
> Abbiamo una proprietà **invariante**: in ogni istante gli elementi $A[i],\ \dots,\ A[inf-1]$ sono $\leq$ del perno, mentre gli altri ($A[sup+1],\ \dots,\ A[f]$) sono $>$ del perno.

> [!info] Complessità
> Che complessità ha? Beh dovendo leggere tutto l'array il tempo di esecuzione è $O(n)$.

###### Implementazione Quick Sort
**Pseudo-codice completo:**
> $\text{QuickSort}(array A,\ int\ i,\ int\ f)$
> 1.   $\text{if }(i < f)\text{ then}$
> 2.     $m = \text{Partition}(A,\ i,\ f)$
> 3.     $\text{QuickSort}(A,\ i,\ m - 1)$
> 4.     $\text{QuickSort}(A,\ m + 1,\ f)$

**Visualizzazione:**
![](assets/l66.png)

> [!check] Corretto? Certamente!
> Dopo Partition $A[i:m-1]$ contiene $elem \leq perno$, $A[m]$ il perno, $A[m+1:f]\ \ elementi > perno$. Le chiamate ricorsive ordinano $A[i:f]$.

###### Complessità nel caso peggiore o migliore
> [!warning] Caso Peggiore
> Ogni volta che invochiamo partition posiziona almeno un elemento in modo corretto (il perno). Quindi dopo n invocazioni di partition, con costo ognuna di costo $O(n)$ ho un array ordinato. Quindi il costo complessivo è $O(n^{2})$.

Questo si verifica quando il perno scelto ad ogni passo è il minimo o il massimo degli elementi dell'array. La complessità in questo caso è:

$$
\begin{array}{l}
T(n) & = T(n-1)+T(0) + O(n) \\
 & = T(n-1) + O(1) + O(n) \\
& = T(n-1) + O(n) \\
 &  & T(n) = O(n^2)
\end{array}
$$

> [!success] Caso Migliore
> Se fosse perfettamente bilanciato allora nel caso migliore avremmo $O(n\cdot \log(n))$.

![](assets/l67.png)

###### Intuizioni nel caso medio
> [!question] Ma nel caso medio?

La partizione può essere sbilanciata, ma più è bilanciata più è veloce, dovremmo trovare ogni volta un perno pessimo per rovinare l'ottimizzazione dell'algoritmo. Sbilanciando però anche a 99-1, sembrando quindi molto instabile, troviamo che...

![](assets/l68.png)

> [!success] Sorpresa!
> La complessità è sempre $O(n\log(n))$!

> [!tip] Randomizzazione
> E se le istanze non sono equiprobabili? Possiamo randomizzare la scelta del perno x. Nella nostra implementazione infatti abbiamo usato un algoritmo Quick Sort Randomizzato.

###### QuickSort Randomizzato
> [!theorem] Complessità QuickSort Randomizzato
> L'algoritmo **QuickSort** randomizzato ordina in loco un array di lunghezza n in tempo $O(n^2)$ nel caso peggiore e $O(n \cdot \log (n))$ con alta probabilità, ovvero con probabilità almeno $\displaystyle1 - \frac{1}{n}$.

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
### Ordinamento senza confronto

> [!info] Introduzione agli algoritmi non basati su confronti
> Gli **algoritmi di ordinamento senza confronto** non determinano l'ordine degli elementi attraverso confronti diretti, ma sfruttano proprietà specifiche dei dati (come valori numerici limitati) per ottenere complessità temporale lineare in certi casi. Questi algoritmi possono superare il limite $\Omega(n\log n)$ degli algoritmi basati su confronti.

**Caratteristiche principali:**
- Non usano confronti diretti tra elementi
- Possono raggiungere complessità $O(n)$ o $O(n+k)$ in certi casi
- Richiedono informazioni specifiche sui dati (es. range di valori)
- Sono particolarmente efficienti quando $k=O(n)$ dove $k$ è il range dei valori

---
#### IntegerSort

> [!tip] Idea dell'algoritmo
> IntegerSort ordina n interi con valori da 1 a k utilizzando un **array di contatori**. L'algoritmo conta quante volte appare ogni valore e poi ricostruisce l'array ordinato.

**Funzionamento:**
1. Manteniamo un *array Y* di contatori dove $Y[x]=\text{numero di volte che appare }x\text{ in X}$
2. Scorriamo l'array ausiliario Y
3. Scriviamo $Y[x]$ volte ogni valore in ordine crescente

**Visualizzazione:**
![](assets/l82.png)
![](assets/l83.png)

**Pseudo-codice:**
> $IntergerSort(X,\ k)$
> 1.  $\text{Sia Y un array di }k\text{ elementi}$
> 2.  $\textbf{for }i=1\textbf{ to}\text{ k}\textbf{ do }Y[i]=0$
> 3.  $\textbf{for }i=1\textbf{ to}\text{ n}\textbf{ do }\text{ incrementa }X[Y[i]]$
> 4.  $j=1$
> 5.  $\textbf{for }i=1\textbf{ to}\text{ k}\textbf{ do }$
> 6.    $\textbf{while }(Y[i]>0)\textbf{ do}$
> 7.      $X[j]=i$
> 8.      $\text{incrementa j}$
> 9.      $\text{decrementa }Y[i]$

##### Analisi della complessità

Fissato i abbiamo **# volte eseguite** è al più $1+Y[i]$ quindi:

$$\displaystyle\sum_{i=1}^{k}(1+Y[i])=\sum_{i+1}^{k}1+\sum_{i+1}^{k}Y[i]=k+n\implies O(k+n)$$

**Costi delle operazioni:**
- $O(k)$ per creare l'array ausiliario Y con valori a 0
- $O(n)$ per calcolare i valori dei contatori
- $O(n+k)$ per ricostruire X

> [!success] Complessità temporale
> Abbiamo un tempo **lineare** $O(n)$ se $k=O(n)$, che supera il Lower Bound $\Omega(n\log(n))$ degli algoritmi basati su confronti!

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
#### BucketSort

> [!tip] Idea dell'algoritmo
> BucketSort estende IntegerSort per ordinare n **record** con chiavi intere in [1,k]. Invece di usare contatori, utilizza un **array di liste** per mantenere anche le informazioni satellite associate ad ogni elemento.

**Applicazioni tipiche:**
Ordinare record con campi multipli, ad esempio:
- nome, cognome, anno di nascita, matricola, etc.
- Ordinamento per matricola o anno di nascita mantenendo gli altri dati

**Input del problema:**
- n record mantenuti in un array
- ogni elemento dell'array è un record con:
	- **campo chiave** (rispetto al quale ordinare)
	- **altri campi** associati alla chiave (informazione satellite)

**Funzionamento:**
1. Manteniamo un array di liste Y, anziché di contatori
2. La lista Y[i] conterrà tutti gli elementi con chiave uguale a i
3. Alla fine concateniamo le liste in ordine

> [!info] Complessità
> Otteniamo un tempo $O(n+k)$ come per IntegerSort.

**Pseudo-codice:**
> $BucketSort (X,\ k)$
> 1.  $\text{Sia Y un array di dimensione k}$
> 2.  $\textbf{for }i=1\text{ to }k\textbf{ do }Y[i]=\text{lista vuota}$
> 3.  $\textbf{for }i=1\text{ to }n\textbf{ do}$
> 4.    $\text{appendi il record }X[i]\text{ alla lista }Y[chiave(X[i])]$
> 5.  $\textbf{for }i=1\text{ to }k\textbf{ do}$
> 6.    $\text{copia ordinatamente in X gli elementi della lista }Y[i]$

##### Stabilità

> [!question] Definizione di stabilità
> Un algoritmo è **stabile** se preserva l'ordine iniziale tra gli elementi con la stessa chiave.

> [!check] BucketSort è stabile?
> Il BucketSort può essere definito **stabile** se appendiamo gli elementi di X *in coda* alla lista Y[i].

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
#### RadixSort

> [!tip] Idea dell'algoritmo
> RadixSort ordina n interi con valori in [1,k] rappresentandoli in una certa base b ed eseguendo una serie di BucketSort **stabili** sulle singole cifre.

**Strategia:**
Partiamo dalla **cifra meno significativa** verso quella **più significativa**:
- Ordinamento per l'i-esima cifra con una passata di BucketSort (stabile)
- L'i-esima cifra è la **chiave**, il numero completo è l'**informazione satellite**
- L'i-esima cifra è un intero in [0, b-1]

**Esempio di funzionamento:**
$$\begin{matrix} \\
& & 2397 &  & 5924 &  & 5924 &  & 4368 &  & 2397 \\
\text{per }b=10 & & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 \\
& & 5924 &  & 4368 &  & 2397 &  & 5924 &  & 5924
\end{matrix}$$

##### Correttezza

> [!check] Dimostrazione di correttezza
> **Caso 1:** Se x e y hanno una diversa t-esima cifra, la t-esima passata di BucketSort li ordina correttamente.
>
> **Caso 2:** Se x e y hanno la stessa t-esima cifra, la proprietà di **stabilità** del BucketSort li mantiene ordinati correttamente.
>
> **Invariante:** Dopo la t-esima passata di BucketSort, i numeri sono correttamente ordinati rispetto alle t cifre meno significative.

##### Tempo di esecuzione

**Analisi:**
- Numero di passate: $O(\log_{b}k)$
  - Corrisponde al numero di cifre per rappresentare il valore massimo k in base b
- Costo per passata: $O(n+b)$
  - In ogni passata la chiave è un intero in [0, b-1]

**Complessità totale:**
$$O((n+b)\log_{b}k)$$

**Ottimizzazione:**
Se scegliamo $b=\Theta(n)$, si ha:

$$\displaystyle O(n\log_{n}k)=O\left( n \frac{\log k}{\log n} \right)$$

> [!success] Tempo lineare
> Abbiamo tempo **lineare** $O(n)$ se $k=O(n^c)$, con c costante.

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---