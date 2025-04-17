### BucketSort
Questo algoritmo ordina n **record** con chiavi intere in [1,k]. Un esempio dell'ordinare n record con campi può essere:
- nome, cognome, anno di nascita, matricola, etc... Supponendo di voler ordinare per matricola o anno di nascita.

Quindi l'input del problema è il seguente:
- n record mantenuti in un array
- ogni elemento dell'array e' un record con
	- campo chiave (rispetto al quale ordinare)
	- altri campi associati alla chiave (informazione satellite)

Infine basta mantenere un array di liste, anziché di contatori, ed operare come per IntegerSort. La lista Y[i] conterrà gli elementi con chiave uguale a i e infine concateniamo le liste.

Otteniamo un tempo O(n+k) come per IntegerSort. L'algoritmo può essere descritto quindi così:
> $BucketSort (X,\ k)$ 
> 1.  $\text{Sia Y un array di dimensione k}$
> 2.  $\textbf{for }i=1\text{ to }k\textbf{ do }Y[i]=\text{lista vuota}$ 
> 3.  $\textbf{for }i=1\text{ to }n\textbf{ do}$
> 4.    $\text{appendi il record }X[i]\text{ alla lista }Y[chiave(X[i])]$ 
> 5.  $\textbf{for }i=1\text{ to }k\textbf{ do}$
> 6.    $\text{copia ordinatamente in X gli elementi della lista }Y[i]$
#### Stabilità
 Un algoritmo è stabile se preserva l'ordine iniziale tra gli elementi con la stessa chiave. Quindi lo è il BucketSort?

Il BucketSort può essere definito stabile se appendiamo gli elementi di **X** *in coda* ad Y[i].
### RadixSort
Ordina n interi con valori in [1,k]

Rappresentano gli elementi in base b, ed eseguiamo una serie di BucketSort

Partiamo dalla cifra meno significativa verso quella più significativa:
- ordinamento per l'i-esima cifra con una passata di BucketSort (stabile)
- i-esima cifra e' la chiave, il numero info satellite
- i-esima cifra e' un intero in [0,b-1]

$$\begin{matrix} \\
& & 2397 &  & 5924 &  & 5924 &  & 4368 &  & 2397 \\
\text{per }b=10 & & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 & \Rightarrow & 2397 & \Rightarrow & 4368 \\
& & 5924 &  & 4368 &  & 2397 &  & 5924 &  & 5924
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

