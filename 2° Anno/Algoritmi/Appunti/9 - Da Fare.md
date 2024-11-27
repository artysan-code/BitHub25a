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

