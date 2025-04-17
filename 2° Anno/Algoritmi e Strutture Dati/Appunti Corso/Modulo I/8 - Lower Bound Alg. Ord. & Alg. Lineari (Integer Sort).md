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
### Ordinamento per confronti
Dati due elementi $a_{i}$ ed $a_{j}$ , per determinarne l’ordinamento relativo effettuiamo una delle seguenti operazioni di confronto: $$a_{i}<a_{j};\quad a_{i}\leq a_{j};\quad a_{i}=a_{j};\quad a_{i}\geq a_{j};\quad a_{i}>a_{j}$$Non si possono esaminare i valori degli elementi o ottenere informazioni sul loro ordine in altro modo.

> Ogni algoritmo basato su confronti che ordina $n$ elementi deve fare nel caso peggiore $\Omega(n\log n)$ confronti quindi il $\#\text{ di confronti}$ che un algoritmo esegue e' un lower bound di $\#\text{ di passi elementari}$ che esegue

> Il MergeSort e il QuickSort sono algoritmi ottimi (almeno dentro la classe di algoritmi basati su confronti)
### Albero di decisione
Gli algoritmi di ordinamento per confronto posso essere descritti in modo astratto tramite gli **alberi di decisione**.

Generalmente un algoritmo di confronto lavora in questo modo:
- Confronta due elementi $a_{i}$ e $a_{j}$.
- Riordina e passa al successivo.

Quindi descrive i confronti di un algoritmo su un determinato input, guardando ogni casistica possibile di confronto. Vengono ignorati i movimenti di dati. Quindi:
- Descrive le diverse sequenze di confronti che A potrebbe fare su un input n.
- Ogni **nodo interno** ha un confronto di tipo $i:j$ con due possibilità.
- Ogni **nodo foglia** è un risultato di un determinato caso.

L'albero di decisione non **è legato al problema** e non è **associato solo ad un algoritmo**.
![[l81.png]]
L'albero di decisione è però legato ad un algoritmo e ad una dimensione di istanza, descrivendo le diverse casistiche che possono avvenire di output su una generica istanza di dimensione n. Corrisponde ad una descrizione alternativa di un algoritmo.
#### Proprietà
- I confronti eseguiti sull'algoritmo rappresentano un cammino radice-foglia.
- Un cammino ha caratteristiche diverse a seconda dell'istanza e quindi l'istanza peggiore è il cammino più lungo.
- Il numero di confronti nel caso peggiore è pari all'**altezza dell'albero di decisione**.
- Un albero di decisione di un *algoritmo corretto* che riordina per confronto n elementi deve necessariamente avere **n! foglie**.

> Un **albero binario T** con k foglie ha altezza almeno $\log_{2}(n)$.
#### Il Lower Bound $\Omega(n\log(n))$
Considerando un *qualsiasi algoritmo* che risolve un problema di ordinamento per confronto di n elementi, l'altezza dell'albero di decisione di almeno $\log_{2}(n!)$. Quindi dalla [[4.5 Prodotti#^0c4ae5|Formula di Stirling]] sappiamo che:$$n!=\sqrt{ 2\pi n }\cdot\left( \frac{n}{e} \right)^n$$
Allora possiamo dedurre che:$$h\geq \log_{2}(n!)>\log_{2}\left( \frac{n}{e} \right)^n=n\log_{2}(n)-n\log_{2}(e)=\Omega(n\log(n))$$
### Algoritmi di ordinamento senza confronto
#### IntegerSort
L'algoritmo ordina n interi con i valori da 1 a k mantenendo un *array Y* di contatori dove possiamo definire che $Y[x]=\text{numero di volte che appare }x\text{ in X}$. Dopodiché scorriamo l'array ausiliario Y e scriviamo $Y[x]$ volte ogni valore in ordine.
![[l82.png]]
![[l83.png]]
Lo pseudo-codice è quindi il seguente:
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

Fissato i abbiamo **# volte eseguite** è al più $1+Y[i]$ quindi:$$\displaystyle\sum_{i=1}^{k}(1+Y[i])=\sum_{i+1}^{k}1+\sum_{i+1}^{k}Y[i]=k+n\implies O(k+n)$$
Abbiamo i seguenti costi quindi:
- $O(k)$ per creare l'array ausiliario Y con valori a 0.
- $O(n)$ per calcolare i valori dei contatori.
- $O(n+k)$ per ricostruire X.

Abbiamo però un tempo lineare se $k=O(n)$, che supera il Lower Bound $\Omega(n\log(n))$ in certe istanze non basandosi sui confronti. 

Implementazione in **Codici -> Sorting.py**.