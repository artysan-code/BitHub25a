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

