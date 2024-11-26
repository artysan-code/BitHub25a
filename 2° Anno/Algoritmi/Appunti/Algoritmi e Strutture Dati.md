
## Lezione V (Metodi di risoluzione equazioni ricorrenza)
Metodi per risolvere le equazioni di ricorrenza:
- iterazione
- albero della ricorsione
- sostituzione
- teorema Master
- cambiamento di variabile
### Metodo della sostituzione

^5d7100

Dobbiamo:
- Indovinare la forma della soluzione.
- Usare l'induzione matematica per provare che la soluzione è quella intuita

Esempio:$$T(n)=n+T\left( \frac{n}{2} \right),\ T(1)=1$$
Possiamo pensare che tenda a $T(n)=n\log_{2}(n)$ oppure $T(n)=n$ ma supponiamo di scegliere il secondo. Ora proviamo a dimostrare che $T(n)\leq c\cdot n$:$$\begin{array}{l}
\text{Passo base: } & T(1)=1 \leq c \cdot 1 \quad \forall\ c \geq 1 \\
\text{Passo induttivo: } \\
\text{Assumo che } T(k) \leq c \cdot k\quad \forall\ k<n \\
T(n)=n+T\left( \frac{n}{2} \right)\leq n+c \cdot \left( \frac{n}{2} \right) \implies T(n)=\left( \frac{c}{2} +1\right)n \\
\end{array}$$
Quindi abbiamo che:$$\left( \frac{c}{2}+1 \right) \leq c \implies c \geq 2$$

### Metodo del Teorema Master
### Metodo del cambiamento di variabile
## Lezione VI (Algoritmi di Ordinamento)
### Ordinamento
Dato un insieme S di n oggetti presi da un dominio totalmente **ordinato**, ordinare S.

### Problema dell'Ordinamento
Abbiamo un **input** di n numeri e vogliamo in **output** una *permutazione* del primo ordinata in maniera crescente o decrescente. Ci sono diversi metodi per farlo e hanno ottimizzazioni e casi diversi.

### Ordinare in tempo quadratico
#### Selection Sort
In questo algoritmo, in modo iterativo, cerco l'elemento minimo dell'array e lo sostituisco con la k-esima posizione (quindi estendiamo l'ordinamento a k+1).![[l61.png]]

Possiamo implementarlo nello pseudo-codice in questa maniera:
```
SelectionSort (A)
1.   for k=0 to n-2 do
2.      m = k + 1
3.      for j=k+2 to n do
4.         if (A[j] < A[m]) then m=j
5.      scambia A[m] con A[k+1]
```

L'algoritmo è banalmente **corretto** e mantiene le seguenti **invarianti***:
- I primi k+1 elementi sono ordinati.
- I primi k+1 elementi sono i più piccoli dell'array.

##### Analisi del costo
Chiamiamo:$$\begin{array}{r}
T(n)=\text{\# operazioni elementari sul modello RAM a costi uniformi} \\
\text{eseguite dall'algoritmo nel caso peggiore su istanze di dimensione n}
\end{array}$$
Se ogni linea di codice costa $O(1)$ e ogni ciclo (come si può vedere) viene eseguito al più n volte, avendo due cicli:$$T(n)\leq 5n^2\cdot O(1)=\Theta (n^2) \implies T(n) =O(n^2)$$
Ma l'analisi è **stretta**? Cioè, $T(n)=\Theta(n^2)$? Analizziamo la linea più importante nel codice che corrisponde a: `if (A[j] < A[m]) then m=j`. Quindi:$$T(n)\geq \displaystyle\sum_{k=0}^{n-2} (n-k-1)=\displaystyle\sum_{k=0}^{n-1} \frac{n(n-1)}{2}=\Theta (n^2) \implies T(n) = \Omega (n^2) \implies T(n)=\Theta (n^2)$$
#### Insertion Sort

^fccf0b

Estendiamo l'ordinamento da k a k+1 elementi, posizioniamo l'elemento (k+1)-esimo nella posizione corretta rispetto ai primi k elementi.![[l62.png]]
#### Bubble Sort

^0a2155

Eseguiamo n-1 scansioni, dove ad ogni scansione guardiamo le coppie di elementi adiacenti e li scambiamo nell'ordine corretto.![[l63.png]]
### Ordinare in tempo meno del quadratico
#### Merge Sort
Per questo algoritmo usiamo la tecnica **divide et impera**:
- Divide: dividi l'array a metà
- Risolvi i due problemi ricorsivamente
- Impera: fondi le due sotto-sequenze ordinate

```
MergeSort(A, i, f)
1.   if (1 < f) then
2.      m = |(i+f)/2| (parte intera inferiore)
3.      MergeSort(A, i, m)
4.      MergeSort(A, m+1, f)
5.      Merge(A, i, m, f)
```

Guardiamo l'albero di ricorsione:![[l64.png]]

Avendo un array di dimensione n, lo dividiamo a metà, eseguiamo la chiama ricorsiva sulla metà e quando ritorna sarà ordinata, uguale per l'altra metà. Quando entrambe sono ordinate vengono unite tramite il **merge**. Ma cosa fa il merge?

##### Procedura merge
Dati due array ordinati A e B, essi possono essere fusi rapidamente:
- Estrai ripetutamente il minimo di A e B e copialo nell'array di output fino a che A o B non diventa vuoto.
- Copia gli elementi dell'array non vuoto alla fine dell'array di output.

(Trovare un modo di inserire la procedura)

Il codice come funziona:
```
Merge(A, i_1, f_1, f_2)
1. Sia X un array ausiliario di lunghezza f_2 - i_1 + 1
2. i = 1; k_1 = i_1
3. k_2 = f_1 + 1
4. while (k_1 <= f_1 e k_2 <= f_2) do
	1. if (A[k_1] <= A[k_2])
	2. then X[i] = A[k_1] e incrementa i e k_1
	3. else X[i] = A[k_2] e incrementa i e k_2
5. if(k_1 <= f_1) then copia A[k_1, f_1] alla fine di X
6. else copia A[k_2, f_2] alla fine di X
7. copia X in A[i_1, f_2]
```

Quanto costa però? Fondendo le due sequenze ordinate costerà $\Theta(n_{1}+n_{2})$ essendo che deve **consumare** uno alla volta ogni elemento degli array.
##### Merge Sort (Tempo di esecuzione)
La complessità temporale del merge sort è descritta dalla seguente relazione di ricorsiva:$$T(n)=2\left( T\left( \frac{n}{2} \right) \right)+ O(n)$$
Usando il teorema master otteniamo:$$T(n)=O(n\cdot \log(n))$$
##### Merge Sort (Memoria Ausiliaria)
La complessità spaziale del Merge Sort è di $\Theta (n)$:
- La procedura di merge usa memoria pari alla dimensione totale da fondere.
- Non sono mai attive due procedure di merge contemporaneamente.
- Ogni chiamata del Merge Sort usa memoria costante (esclusa la parte di merge).
- Il numero di chiamate attive contemporaneamente è di $O(\log(n))$.

Il Merge Sort non **ordina in loco**.
### Algoritmo di Quick Sort
Vi sono diverse versioni del quick sort: caso peggiore, caso medio e versione randomizzata.

Generalmente però, usa la tecnica del **divide et impera**:
- **Divide**: scegli un elemento x della sequenza (perno) e partiziona la sequenza in elementi $\leq$ x e in elementi $\geq$ x.
- Risolvi i due problemi ricorsivamente.
- **Impera**: restituisci la concatenazione delle due sotto-sequenze ordinate.
#### Funzione Partizione
Scegli un **perno** (ad esempio il primo elemento), scorri l'array in parallelo da sinistra verso destra fermandoci su un elemento maggiore del perno e viceversa fermandoci su uno minore del perno, scambia gli elementi e riprendi la scansione. Fermati quando i due indici sono incrociati:![[l65.png]]
```
Partition (A, i, f)
1.  x=A[i]
2.  inf = i
3.  sup = f + 1
4.  while (true) do
5.    do (inf = inf + 1) while (inf <= f e A[inf] <= x)
6.    do (sup = sup - 1) while (A[sup] > x)
7.    if (inf < sup) then scambia A[inf] e A[sup]
8.    else break
9.  scambia A[i] e A[sup] // mette il perno al centro
10. return sup // restituisce la posizione del perno
```

Che tempo di esecuzione abbiamo? Beh dovendo leggere tutto l'array il tempo di esecuzione è $O(n)$.
#### Quick Sort (completo)
Allora impacchettiamo tutto, il quick sort corrisponde a:
```
QuickSort (A, i, f)
1. if (i < f) then
2.   m = Partition(A, i, f)
3.   QuickSort(A, i, m - 1)
4.   QuickSort(A, m + 1, f)
```

Quindi risulterà così:![[l66.png]]

Corretto? Certamente, dopo Partition $A[i:m-1]$ contiene $elem \leq perno$, $A[m]$ il perno, $A[m+1:f]\ \ elementi > perno$. Le chiamate ricorsive ritornano $A[i:f]$
Complessità?

##### Complessità nel caso peggiore
Ogni volta che invochiamo partition posiziona almeno un elemento in modo corretto (il perno). Quindi dopo n invocazioni di partition, con costo ognuna di $O(n)$ ho un array ordinato. Quindi il costo complessivo è $O(n^2)$.

Questo si verifica quando il perno scelto ad ogni passo è il minimo o il massimo degli elementi dell'array. La complessità in questo caso è:$$\begin{array}{l}
T(n) & = T(n-1)+T(0) + O(n) \\
 & = T(n-1) + O(1) + O(n) \\
& = T(n-1) + O(n) \\
 &  & T(n) = O(n^2)
\end{array}$$
Se fosse perfettamente bilanciato allora nel caso migliore avremmo $O(n\cdot \log(n))$. Ma nel caso medio?
##### Intuizioni nel caso medio
La partizione può essere sbilanciata, ma più è bilanciata più è veloce, dovremmo trovare ogni volta un perno pessimo per rovinare l'ottimizzazione dell'algoritmo. Sbilanciando però anche a 99-1 troviamo che...

La complessità è sempre $O(n\log(n))$!

E se le istanze non sono equiprobabili? Possiamo randomizzare la scelta del perno x.
##### Teorema
L'algoritmo **QuickSort** randomizzato ordina in loco un array di lunghezza n in tempo $O(n^2)$ nel caso peggiore e $O(n \cdot \log (n))$ con alta probabilità, ovvero con probabilità almeno 1 - 1/n.

> [!NOTE]
> Algoritmi randomizzati ampia e importante area di studio e ricerca, Pasquale è molto bravo in questo.

## Lezione VII (Progettare Algoritmi con strutture dati eff.)
### Tipo di dato vs Struttura Dati
Un **tipo di dato** è una specifica collezioni di oggetti e di operazioni eseguibili su di essi (Es. dizionario mantiene un insieme di elementi con chiavi associate per op. di inserimento, cancellazione e ricerca).

Una **struttura dati** è, invece, un'organizzazione dei dati che permette di memorizzare la collezione e supportare operazioni di u tipo di dato usando meno risorse di calcolo possibili.
### Heap Sort
Ha lo stesso approccio incrementale del Selection-Sort, seleziona gli elementi dal più grande al più piccolo usando una **struttura di dati efficiente** (estrazione in tempo $O(\log(n))$ massimo).

Quindi bisogna generare una struttura dati H che abbia i seguenti attributi:
- Dato un array A, generare velocemente H
- Trovare il più grande oggetto in H
- Cancellare il più grande oggetto in H

Per questo usiamo la struttura dati **heap** associata ad un insieme S, cioè un albero binario radicato con le seguenti proprietà:
- Completo fino al penultimo livello (struttura rafforzata, sull'ultimo livello tutte sono compattate a sinistra).
- Gli elementi di S sono memorizzati nei nodi dell'albero, ogni nodo memorizza un solo elemento, denotato con chiave (v).
- $chiave(padre(v)) \geq chiave(v)$ per ogni nodo v diverso dalla radice.

Un heap ha le seguenti **proprietà salienti**:
- Il massimo è contenuto nella radice.
- L'albero con n nodi ha **altezza $O(\log(n))$**
- Gli heap con struttura rafforzata possono essere rappresentati in array di dimensione n.

Rispettando quindi tutte queste proprietà, l'heap ottiene le seguenti relazioni (i è la posizione dell'elemento da relazionare):
- Il **figlio sinistro** di un elemento è in posizione $2i$.
- Il **figlio destro** di un elemento è in posizione $2i + 1$.
- Il **padre** di un elemento si trova in $\left\lfloor  \frac{i}{2}  \right\rfloor$.
#### Funzione Fix-Heap
Data v la radice dell'Heap, si assume che i sottoalberi destri e sinistri siano heap, ma la proprietà di ordinamento delle chiavi non vale.
```
fixHeap(nodo v, heap H):
	if (v non è una foglia) then
		sia u il figlio di v con chiave massima
		if chiave(v) < chiave(u) then
			scambia chiave(v) con chiave(u)
			fixHeap(u, H)
```

L'algoritmo non fa altro che spostare le chiavi che non rispettano l'heap verso il basso, con la chiave del figlio con valore minore. Essendo che nel caso peggiore deve spostare v alla fine dell'albero, dovrà fare almeno $O(\log(n))$ operazioni di spostamento, che valgono ciascuna $O(1)$. Quindi in totale la complessità è $O(\log(n))$.

Questa funzione può essere chiamata **solo se vi è una anomalia nella radice**, ma gli alberi destri e sinistri **devono essere heap**.
#### Estrazione del massimo
Per estrarre il massimo devo:
- Copiare nella radice la chiave contenuta nella foglia più a destra (quindi nell'ultimo elemento dell'heap che si trova alla grandezza dell'heap).
- Rimuovi la foglia (quindi decrementiamo la grandezza dell'heap)
- Ripristiniamo l'ordinamento tramite fixHeap sulla radice
#### Costruzione dell'Heap (Heapify)
Heapify
#### Complessità Heapify
Data h l'altezza di un heap con n elementi e sia $n^{'} \geq n$ l'intero tale che un heap con $n^{'}$ elementi ha:
- altezza h
- è completo fino all'ultimo livello

Vale quindi che:$$T(n) \leq T(n^{'})\quad n^{'} \leq 2n$$
Quindi il tempo di esecuzione è:$$T(n^{'})=2T\left( \frac{n^{'}-1}{2} \right)+O(\log(n^{'}))\leq 2T\left( \frac{n^{'}}{2} \right)+ O(\log(n^{'}))$$
Dal teorema master possiamo dire che $T(n')=O(n^{'})$ e quindi:$$T(n) \leq T(n^{'})=O(n^{'})=O(2n)=O(n)$$
#### Max-Heap e Min-Heap
Se volessimo una struttura dati che tira fuori velocemente il minimo dell'heap invece che il massimo, basterebbe semplicemente invertire la proprietà di ordinamento delle chiavi così che:$$chiave(padre(v))\leq chiave(v)\quad\quad \forall\ v\ diverso\ dalla\ radice$$
E perché abbiamo progettato un max-heap e non un min-heap?
#### HeapSort
Il codice finale, unendo tutte le funzioni precedente, rispetta i seguenti step:
- Costruiamo un heap tramite heapify.
- Estraiamo ripetutamente il massimo per n-1 volte. Memorizziamo il massimo nella posizione appena liberata.

Quindi lo pseudo-codice è il seguente:
```
heapSort(A)
1. heapify(A)
2. heapsize[A] = n
3. for i=n down to 2 do
	1. scambia A[1] e A[i]
	2. heapsize[A] = heapsize[A] - 1
	3. fixHeap(1, A)
```

Ordina in loco $O(n\cdot \log(n))$

## Lezione VIII (Lower Bound Alg. Ord. & Alg. Lineari)
### Sommario
- delimitazioni inferiori e superiori (di algoritmi e problemi)
- quanto velocemente si possono ordinare n elementi?
	- una soglia (asintotica) di velocità sotto la quale non si può scegliere: un lower bound
		- (per ciascuna classe di algoritmi ragionevoli - quelli basati su confronti)
	- una tecnica elegante che usa gli **alberi di decisione**
- e se si esce da questa classe di algoritmi?
	- integer sort e bucket sort (per interi "piccoli")
	- radix sort (per interi più "grandi")

### Delimitazioni inferiori e superiori

Un algoritmo A ha complessità (costo di esecuzione) O(f(n)) rispetto ad una certa risorsa di calcolo, se la quantità r(n) di risorsa usata da A nel caso peggiore su istanze di dimensione n verifica la relazione r(n)=O(f(n))


Un algoritmo A ha complessità (costo di esecuzione) $\Omega$(f(n)) rispetto ad una certa risorsa di calcolo, se la quantità r(n) di risorsa usata da A nel caso peggiore su istanze di dimensione n verifica la relazione r(n)= $\Omega$(f(n))

Un problema P ha una complessità O(f(n)) rispetto ad una risorsa di calcolo se **esiste** un algoritmo che risolve P il cui costo di esecuzione rispetto quella risorsa è O(f(n))

Un problema P ha una complessità $\Omega$(f(n)) rispetto ad una risorsa di calcolo se **ogni algoritmo** che risolve P ha costo di esecuzione nel caso peggiore $\Omega$(f(n)) rispetto quella risorsa

### Algoritmo Ottimo
Dato un problema P con complessità $\Omega$(f(n)) rispetto ad una risorsa di calcolo, un algoritmo che risolve P è (asintoticamente) **ottimo** se ha costo di esecuzione O(f(n)) rispetto a quella risorsa

###  Complessità temporale del problema dell'ordinamento
- Upper bound: $O(n^2)$
	- insertion sort, selection sort, quick sort, bubble sort
- Un upper bound **migliore**: $O(n\log n)$
	- merge sort, heap sort
- lower bound: $\Omega(n)$
	- banale: ogni algoritmo che ordina n elementi li deve almeno leggere tutti

abbiamo un gap di $\log n$ tra upper e lower bound. Si può fare di meglio?

### Ordinamento per confronti
Dati due elementi $a_{i}$ ed $a_{j}$ , per determinarne l’ordinamento relativo effettuiamo una delle seguenti operazioni di confronto: $$a_{i}<a_{j};\quad a_{i}\leq a_{j};\quad a_{i}=a_{j};\quad a_{i}\geq a_{j};\quad a_{i}>a_{j}$$Non si possono esaminare i valori degli elementi o ottenere informazioni sul loro ordine in altro modo.

Tutti gli algoritmi di prima sono algoritmi di ordinamento per confronto
#### Teorema
Ogni algoritmo basato su confronti che ordina n elementi deve fare nel caso peggiore $\Omega(n\log n)$ confronti


quindi il # di confronti che un algoritmo esegue e' un lower bound di # di passi elementari che esegue
#### Corollario
Il merge sort e il quick sort sono algoritmi ottimi (almeno dentro la classe di algoritmi basati su confronti)
### Albero di decisione
Gli algoritmi di ordinamento per confronto posso essere descritti in modo astratto tramite gli **alberi di decisione**.

Un generico algoritmo di confronto lavora in questo modo:
- Confronta due elementi $a_{i}$ e $a_{j}$.
- Riordina e passa al successivo.

Quindi descrive i confronti di un algoritmo su un determinato input, guardando ogni casistica possibile di confronto. Vengono ignorati i movimenti di dati. Quindi:
- Descrive le diverse sequenze di confronti che A potrebbe fare su un input n.
- Ogni **nodo interno** ha un confronto di tipo $i:j$ con due possibilità.
- Ogni **nodo foglia** è un risultato di un determinato caso.

L'albero di decisione non **è legato al problema** e non è **associato solo ad un algoritmo**.

### Algoritmi di ordinamento senza confronto
#### IntegerSort


## Lezione IX ()
### Sommario
- Delimitazioni inferiori e superiori (di algoritmi e problemi)
- Quanto velocemente si possono ordinare n elementi?
	- una soglia (asintotica ) di velocità sotto la quale non si può scendere: un lower bound
		- (per una classe di algoritmi ragionevoli - quelli basati su confronti)
	- una tecnica elegante che usa gli alberi di decisione
- E se si esce da questa classe di algoritmi?
	- integer sort e bucket sort (per interi "piccoli")
	- radix sort (per interi più "grandi")

### BucketSort
ordina n record con chiavi intere in [1,k]

per esempio ordinare n record con campi:
- nome, cognome, anno di nascita, matricola,...

Input del problema:
- n record mantenuti in un array
- ogni elemento dell'array e' un record con
	- campo chiave (rispetto al quale ordinare)
	- altri campi associati alla chiave (informazione satellite)

-  basta mantenere un array di liste, anziché di contatori, ed operare come per IntegerSort
- la lista Y[i] conterrà gli elementi con chiave uguale a i
- concatenare poi le liste

Tempo O(n+k) come per IntegerSort
``` 
BucketSort (X, k) 

Sia Y un array di dimensione k 
	for i=1 to k do Y[i]=lista vuota 
		for i=1 to n do 
			appendi il record X[i] alla lista Y[chiave(X[i])] 
		for i=1 to k do 
			copia ordinatamente in X gli elementi della lista Y[i]
```

### Stabilita
 un algoritmo e' stabile se preserva l'ordine iniziale tra gli elementi con la stessa chiave

### RadixSort
Ordina n interi con valori in [1,k]

Rappresentano gli elementi in base b, ed eseguiamo una serie di BucketSort

Partiamo dalla cifra meno significativa verso quella più significativa:
- ordinamento per l'i-esima cifra con una passata di BucketSort (stabile)
- i-esima cifra e' la chiave, il numero info satellite
- i-esima cifra e' un intero in [0,b-1]

$$\begin{matrix}
  & & 2397 &  & 5924 &  & 5924 &  & 4368 &  & 2397 \\
per  & & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 \\
b=10  & & 5924 &  & 4368 &  & 2397 &  & 5924 &  & 5924
\end{matrix}$$
### Correttezza
Se x e y hanno una diversa t-esima cifra, la t-esima passata di BucketSort li ordina

Se x e y hanno la stessa t-esima cifra, la proprietà di stabilita del BucketSort li mantiene ordinati correttamente


Dopo la t-esima passata di BucketSort, i numeri sono correttamente ordinati rispetto alle t cifra meno significative

### Tempo di esecuzione
$O(\log_{b}k)$ passate di BucketSort
-  # di cifre per rappresentare il valore massimo k in base b: 
Ciascuna passata richiede tempo $O(n+b)$
- in ogni passata la chiave e' un intero in [0,b-1]

quindi $O((n+b)\log_{b}k)$ 

Se $b=\Theta(n)$, si ha $\displaystyle O(n\log_{n}k)=O\left( n \frac{\log k}{\log n} \right)$

quindi abbiamo tempo lineare se $k=O(n^c)$, c costante


## Lezione X (Esercitazione 1 - 06-11-2024)

### Esercizio 1
Dimostrare o confutare la seguente affermazione:
Siano f(n) e g(n) due funzioni sempre non negative. Allora vale:
$$\displaystyle f(n)=O(g(n))\implies 2^{f(n)}=O(2^{g(n)})$$

caso 1
$f(n) = n$
$\displaystyle g(n)= \frac{n}{2}$

$\displaystyle 2^{n}\not= O\left( 2^{\frac{n}{2}} \right)$ 

### Esercizio 2
Progettare un algoritmo (efficiente) che, dato un array ordinato A[1:n] di n interi e un intero x, trova (se esistono) due indici i e j, i < j, tale che A[i]+A[j]=x

Soluzione ovvia provare tutte le coppie di indici i,j

```
Banale (A,x)
for i=1 to n-1 do
	for j=i+1 to n do 
		if (A[i]+A[j]=x) then return (i,j)
return (-1,-1)
```

complessità della soluzione ovvia $O(n^2)$
trovare una soluzione più efficiente

$A= [2,\ 5,\ 9,\ 14,\ 20,\ 21,\ 25,\ 40]$

## Lezione XI (Esercitazione 2 - 12-11-2024)
primo modulo sono 3 esercizi
1 (16 punti) studiare bene
2 (8 punti) 
3 (8 punti)

impostare bene 2 e 3 esercizio con il primo fatto bene porta a 18 

per fare bene 2 e 3 non basta solo studiare (sono di progettazione di algoritmi)


### Esercizio 1

Input un array A[1,...,n] A[i]$\in \mathbb{Z}\quad \forall i= 1,\dots,n\quad\exists\ m=1,\dots,n$:
1) A[i]<A[m]    $1\leq i\leq m$
   A[i]<A[m]    $m<i\leq n$
2) A[i]<A[i+1]    $1\leq i<m$
   A[i+1]<A[i]    $m\leq i<n$

richieste:
1) trovare m in tempo $\circ(n)$
2) ordinare A in tempo $\circ(n\log n)$ 

esempio:
$A[2,4,20,13,9,6,5,2]$
m= 20

Esempio:
$A[2,3,6,9,20,21,30]$
m=30

```
max.unimodale(A)
	if A[1]>A[2]:
		return 1
	else if A[n]>A[n-1]:
		return n
	else
		BS.unimodale(A,2,(n-1))
```

```
BS.unimodale(A,i,j)
	if i>j
		return -1
	m=|(i+j)/2|
	if A[m]>A[m-1] && A[m]>A[m+1]
		return m
	else if A[m] > A[m-1]
		return BS.unimodale(A,i,m-1)
	else
		return BS.unimodale(A,m+1)
```


```
sort.unimodale(A)
	m=max.unimodale(A)
	if m != n
		inverti(A,m+1,n)
		if m != 1
			merge(A,1,m,n)
```

Per casa
Definire le funzioni inverti (o(n)) e merge (o(n))

### Esercizio 2

A[1,...,n] A[i]$\in \mathbb{N}$
trovare i*, j* ,    i*<j*
$\forall\ i,j\quad i<j\quad A[j*]-A[i*]>A[j]-A[i]$

A = [20, 11, 2, 5, 4, 10, 9, 21]

max[k]= indice del massimo in A[k,n]

max[1, 2, 6, 6, 6, 6, 7, 8]

max(A[:-1...n]=max{A[i+1],max(A[i,...,n])})
```
max[1,...,n]
max[n]=n    O(n)
for i=n-1,...,1
	if A[i]>A[max[i+1]]
		max[i]=i
	else
			max[i]=max[i+1]
```

```
alg(A)
	calcola max    O(n)
	i*=1
	j*=max[i]
	delta=A[j*]-A[i*]
	for i=2,...,n-1    O(n)
		if (A[max[i+1]]-A[i]>delta)    O(1)
			i*=i
			j*=max[i+1]
			delta=A[i*]-A[j*]
```
## Lezione XII (Strutture dati elementari)
### Tipo di Dato e Struttura di Dati
### Struttura dati Dizionario

^4be009

Riceve un insieme S di coppie (e, k), cioè valore-chiave,  e supporta le seguenti **operazioni**:
- **Insert**, aggiungere ad S una nuova coppia (e, k).
- **Delete**, cancella da S l'elemento con chiave k.
- **Search**, fornisce l'elemento nel dizionario con chiave k, se non esiste restituisce null.
#### Implementazione
Vi sono diverse tipologie di implementazioni, a seconda di come viene strutturata la lista delle chiavi
### Struttura dati Pila
Riceve una sequenza S di *n elementi* e supporta le seguenti operazioni:
- **isEmpty() -> result**, restituisce *true* se S è vuota e *false* altrimenti.
- **push(elem e)**, aggiunge *e* come ultimo elemento di S.
- **pop() -> elem**, toglie l'ultimo elemento di S e lo restituisce.
- **top() -> elem**, restituisce l'ultimo elemento di S senza toglierlo.
### Struttura dati Coda
Riceve una sequenza S di *n elementi* e supporta le seguenti operazioni:
- **isEmpty() -> result**, restituisce *true* se S è vuota e *false* altrimenti.
- **enqueue(elem e)**, aggiunge e come ultimo elemento di S.
- **dequeue() -> elem**, toglie da S il primo elemento e lo restituisce.
- **first() -> elem**, restituisce il primo elemento da S, senza toglierlo.
### Rappresentazione dei dati
Esistono due tipologie fondamentali di rappresentazione dei dati:
- **Rappresentazioni indicizzate**, che usano array e matrici e sfruttano l'indicizzazione di essi. Possiede vantaggi e svantaggi:
	- Gli indici delle celle di un array sono numeri consecutivi.
	- Non è possibile aggiungere nuove celle ad un array.
- **Rappresentazione collegate**, che usano i record (costituenti di base) collegati fra loro tramite puntatori. I record possono essere distrutti e creati dinamicamente. Anche questo possiede vantaggi e svantaggi:
	- Possiamo aggiungere e togliere un record a una struttura collegata
	- Gli indirizzi dei record non sono necessariamente consecutivi.

### Organizzazione gerarchica dei dati
Consiste nell'organizzazione dei dati in una gerarchia e delle relazioni tramite gli alberi. Ci sono diverse definizioni aggiuntive per gli [[|alberi]]:
- Il grado di un nodo è il numero dei suoi figli.
- u antenato di v se u è raggiungibile da v risalendo di padre in padre v discendente di u se u è un antenato di v.
![[l121.png]]

Come possiamo rappresentare un albero in maniera indicizzata? (Quindi con array)
##### Vettore dei padri
L'idea è di associare ad ogni cella l'informazione di un nodo e la posizione del padre, in un vettore almeno di dimensione n. Quindi una generica cella contiene l'informazione (info, parent) dove:
- Info è il contenuto informativo del nodo i
- Parent è l'indice nell'array del padre.

Quindi le operazioni di ricerca hanno i seguenti costi:
- Ricerca di un padre **O(1)** mentre ricerca di un figlio **O(n)**.
##### Vettore posizionale (da fare)


## Lezione XIII (Esercitazione 3 - 19-11-2024)

### Problema 1
Avendo un albero binario T di n nodi e ogni nodo ha:
- valore $val(v)>0$
- colore $col(v)\in\{R,N\}$

Bisogna trovare il valore del cammino rosso di tipo radice-nodo di valore massimo

#### Definizione
Il valore di un cammino e' la somma dei valori dei nodi del cammino

#### Definizione
Un cammino e' rosso se tutti i suoi nodi sono di colore rosso

T viene rappresentato con record e puntatori:

|               P | (v)$\nearrow$   |
| --------------: | :-------------- |
|         val (v) | col(v)          |
| $\swarrow$sx(v) | dx(v)$\searrow$ |
#### Soluzione
MaxRosso(v)
restituisce il valore del cammino rosso di valore massimo di tipo v-discendente di v

- informazione che vengono "dal basso", calcolate rispetto al sottoalbero con radice v;
- possono essere usate per "passare informazioni" al padre di v

```
MaxRosso(v)
if v=null then return 0
if col(v)=N return 0
return val(v)+max{MaxRosso(sx(v)),MaxRosso(dx(v))}
```

complessita':
$O(n)$ dato che effettuiamo solamente una visita

### Problema 2
Avendo un albero binario T di n nodi (rappresentato con record e puntatori) e un intero $h\geq 0$

trovare il numero di nodi di T con profondità almeno h

#### Definizione
la profondità di un nodo e' la distanza (# di archi) dalla radice


## Lezione XIV (Problema del Dizionario)
Data la struttura dati del [[Algoritmi e Strutture Dati#^4be009|Dizionario]] analizziamo una sua buona implementazione dove ogni operazione è garantita di avere $O(\log(n))$. Le idee sono:
- Definire un albero binario tale che ogni operazione richiede $O(altezza\ albero)$
- Fare in modo che l'altezza dell'albero sia sempre $\log(n)$ 
### Alberi binari di ricerca (BST)
Un **BST** rispetta le seguenti proprietà:
- Ogni *nodo v* contiene un elemento $elem(v)$ cui è associata una chiave $chiave(v)$ presa da un dominio totalmente ordinato.
- Per ogni nodo v vale che:
	- Le chiavi che si trovano nel sotto-albero sinistro di v sono $\leq$ $chiave(v)$.
	- Le chiavi che si trovano nel sotto-albero destro di v sono $>$ $chiave(v)$.


## Lezione XV (Problem Set)

### Il problema del dizionario

```
tipo Dizionario:
dati un insieme S di coppie (elem,chiave)
operazioni
	insert(elem e,chiave k)
		aggiunge a S una nuova coppia (e,k)
	
	delete(elem e)
		cancella da S l'elemento e
	
	search(chiave k)--> elem
		se una chiave k e' presente in S restituiesce un element e ad essa
		associato e null altrimenti
```


## To Do List
- Aggiungere esempi per il [[#^5d7100|metodo della sostituzione]].