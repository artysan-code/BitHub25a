[[2° Anno/Algoritmi/Appunti/1 - Introduzione|Torna alla lezione precedente]]
[[3 - Modelli di calcolo e Notazione Asintotica|Continua alla lezione successiva.]]
## Problema di Fibonacci
Passiamo quindi ora ad un modello di calcolo più simile la computer e ragioniamo in modo più qualitativo rispetto alla complessità temporale degli algoritmi.
### L'isola dei conigli
Quanto velocemente si riprodurrebbe una popolazione di conigli in certe condizioni? Questa è la domanda che si è fatto Leonardo da Pisa, partendo da un isola deserta con due conigli.

Le regole ci permettono di studiare meglio questo problema sono le seguenti:
- Una coppia di conigli concepisce due coniglietti di sesso diverso ogni anno, i quali formeranno una nuova coppia.
- La gestazione dura un anno.
- I conigli cominciano a riprodursi soltanto al secondo anno dopo la loro nascita.
- I conigli sono immortali.

Possiamo descrivere questa riproduzione con il seguente albero:
![[l22.png]]

### La regola di espansione
Abbiamo che nell'anno $n$ ci sono tutte le coppie dell'anno precedente e una nuova coppia di conigli per ogni coppia presente due anni prima. Chiamiamo allora $F_n$ il numero di coppie rispetto all'anno n e imponiamo la seguente relazione di ricorrenza:$$
F_{n}=
\begin{cases}
F_{n-1} + F_{n-2}&&se\ n\geq 3 \\
1&&se\ n =1,2
\end{cases}$$
## Come si calcola $F_n$?
### Algoritmo Uno

^66510c

Possiamo usare un approccio numerico che calcoli direttamente i numeri di Fibonacci.
$\displaystyle F_{n}=\frac{1}{\sqrt{5}}(\phi^n-\hat{\phi^n})$ dove
$\displaystyle \phi = \frac{1 + \sqrt{ 5 }}{2} \approx +1.618$
$\displaystyle \hat{\phi} = \frac{1 - \sqrt{ 5 }}{2} \approx -0.618$

L'algoritmo quindi è descrivibile con il seguente pseudo-codice:
> $\displaystyle\text{algoritmo fibonacci1(int n)} \to \text{int}:$
> 	$\displaystyle\text{return }\left( \frac{\phi^n-\hat{\phi}^n}{\sqrt{ 5 }} \right)$

Dato lo pseudo-codice una possibile implementazione in python è la seguente:
```python
def fibonacci1(n: int) -> int:
	return int((pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n)) / sqrt(5))
```

Ma questo algoritmo è corretto? Beh... 

A causa dell'approssimazione dei due $\phi$ non riusciamo ad approssimare sempre al valore corretto. Aumentando però l'approssimazione troveremo sempre verso infinito un numero che verrà approssimato in maniera errata.
### Algoritmo Due

^2bb139
Questo algoritmo è quello che viene generalmente studiato in matematica.

> $\text{algoritmo fibonacci2(int n)} \to \text{int}:$
> 	$\text{if } (n\leq 2) \text{ then return 1}$
> 	$\text{else return fibonacci}(n-1)+\text{fibonacci2}(n-2)$

Usando invece una funzione ricorsiva possiamo fare:
```python
def fibonacci2(n: int) -> int:
	if n < 2:
		return n
	else:
		return fibonacci2(n-1) + fibonacci2(n-2)
```

Questa tecnica rispetta il *divide et impera*. Però grazie a questa tecnica ora l'algoritmo è **corretto**!

Ma è efficiente?

In ogni modello di calcolo rudimentale ogni linea di codice costa un'unità di tempo. Di conseguenza calcoliamo le linee di codice mandate in esecuzione:
- Se $n\leq 2$ allora abbiamo una linea di codice
- Se $n = 3$ ci sono quattro linee di codice, due per la chiamata fibonacci2(3) e una per fibonacci2(2) e fibonacci2(1)
- Se invece è $n$? Cerchiamo di studiarlo tramite una funzione $f(n)$.

Quindi definendo $f(n)$ come *# di linee di codice eseguite dall'algoritmo sull'input n*.

Quindi $f(n)=2+f(n-1)+f(n-2)$  e  $f(1)=f(2)=1$ ma a cosa corrisponde? Questa è quella che chiamiamo **equazione di ricorrenza**.

Per risolverla usiamo un **albero della ricorsione**:
![[l23.png]]

I nodi alla base dell'albero sono i **casi base**, in quanto non eseguono ricorsioni. Per dedurre una formula dobbiamo capire quante foglie e nodi interni possiede l'albero.

### Primo Lemma 

^bcd178

> Il numero di foglie dell'albero della ricorsione di *fibonacci2(n)* è pari a $F_n$.

> ![[l24.png]]
### Secondo Lemma

^9ac909

>Il numero di nodi interni di un albero in cui ogni nodo interno ha due figli è pari al numero di foglie - 1.

**Dimostrazione**
Per induzione sul numero di nodi dell'albero (n)
f = # foglie
i = # nodi interni

con $n\leq 2$         i=0, f=1

con $n>2$         per costruzione i' = i-1 e f' = f-1

per ipotesi induttiva:
	i'=f'-1

quindi:
i-1=f-1-1 
cioè i=f-1



In totale le linee di codice eseguite sono:$$F_n + 2(F_n -1)=3F_n-2$$
fibonacci2 è molto lento...

Infatti già a n=100 sarà impossibile calcolare il numero.

### Algoritmo Tre
L'idea è di memorizzare i valori calcolati per permettere a "calcoli di Fibonacci successivi" di essere semplificati in linea di tempo.

> $\text{algoritmo fibonacci3(int n)} \to \text{int}$
> 	$\text{sia Fib un array di interi}$
> 	$Fib[1] \gets 1,Fib[2]\gets 1$
> 	for $i=3$ to $n$ do
> 		$Fib[i]\gets Fib[i-1]+Fib[i-2]$
> 	return $Fib[n]$

```python
def fibonacci3(n: int) -> int:
	Fib = [0, 1]
	for i in range(3, n):
		Fib.append(Fib[i-1] + Fib[i-2])
	return Fib[n-1]
```
Prendiamo il valore a $n-1$ in quanto l'array in programmazione inizia da 0 e non da 1 come nello pseudo-codice.

Tempo di esecuzione? Beh...

La prima, la seconda e l'ultima riga di codice vengono eseguite una sola volta, mentre la terza e la quarta linea vengono eseguite n volte. Quindi:$$T(n)\leq n+n+3=2n + 3$$
fibonacci3 impiega un tempo lineare (proporzionale a n) rispetto a fibonacci2 che invece impiega un tempo esponenziale. L'altra faccia della medaglia però è lo spazio occupato, che sarà proporzionale all'input.
### Algoritmo Quattro
Proviamo ad ottimizzare lo spazio occupato dall'algoritmo precedente:

>algoritmo fibonacci4(intero $n$)$\to$ intero
>	$a\gets 1,b\gets 1$
>	for $i$=3 to $n$ do 
>		$c\gets a+b$
>		$a\gets b$
>		$b\gets c$
>	return $c$

```python
def fibonacci4(n: int) -> int:
	a = 1 # F_n-1
	b = 1 # F_n-2
	i = 3
	while (i<=n):
		c = a + b # F_n
		a = b
		b = c
		i += 1
	return c
```

Non è il miglior algoritmo possibile e possiamo usare il **lemma tre** per poter ottimizzare l'algoritmo.
### Notazione Asintotica
Vogliamo esprimere $T(n)$ in modo qualitativo anche perdendo un po' di **precisione**, ma guadagnando semplicità.

Ignorando le costanti moltiplicative e i termini di ordine inferiore, otteniamo:$$\begin{array}{}
T(n) = 5n + 3 = O(n)\\
T(n) = 5n^2 + 5n - 3 = O(n^2)
\end{array}$$
Ma è comunque sensato misurare la complessità di un algoritmo contando le righe di codice eseguite? si vedrà!

Si dice che $f(n)=O(g(n))$ se $f(n) \leq c(g(n))$ con c che è una costante e n che è abbastanza grande.

Si può sperare di calcolare $F_n$ in un tempo minore a $O(n)$?
### Algoritmo Cinque
#### Terzo Lemma
>Grazie alle proprietà delle matrici, è dimostrabile che:$$\begin{pmatrix}1&1\\1&0\end{pmatrix}^n=\begin{pmatrix}F_{n+1}&F_n\\F_n&F_{n-1}\end{pmatrix}$$

Dimostrazione:
![[l27.png]]
![[l28.png]]
#### Algoritmo

![[l25.png]]

```python
def fibonacci5(n: int) -> int:
	N = np.array([[1, 1], [1, 0]])
	M = np.array([[1, 0], [0, 1]])
	for _ in range(1, n):
		M = np.dot(M, N)
	return M[0][0]
```
Usiamo la libreria numpy come np in quanto ci permette di eseguire le moltiplicazioni tra matrici.

Il risultato non sembra aver ottimizzato niente, eppure:
#### Calcolo di potenze
Si può calcolare l'ennesima potenza, elevando al quadrato la $\left\lfloor  \frac{n}{2}  \right\rfloor$-esima potenza. Se n è dispari basta eseguire un'ulteriore moltiplicazione.$$\begin{array}{}
3^2=9 & 3^4=9^2=81 & 3^8=81^2=6561
\end{array}$$
Abbiamo eseguito 3 prodotti invece che 7!
### Algoritmo Sei

![[l26.png]]

```python
def fibonacci6(n: int) -> int:
	A = np.array([[1, 1], [1, 0]])
	M = potenzadiMatrice(A, n - 1)
return M[0][0]

def potenzadiMatrice(A: np.array, k: int) -> np.array:
	if k == 0: return np.array([[1, 0], [0, 1]])
	else:
		M = potenzadiMatrice(A, k // 2)
		M = np.dot(M, M)
	if k % 2 == 1: M = np.dot(M, A)
	return M
```

Iniziamo a notare andando avanti con gli algoritmi che, pur sembrando più righe l'algoritmo invece è sempre più veloce. Infatti:
- Il tempo speso dentro `potenzadiMatrice` è costante (Per definizione).
- Si esegue una chiamata ricorsiva di `potenzadiMatrice` con input $\left\lfloor  \frac{n}{2}  \right\rfloor$ 

L'equazione di ricorrenza è pertanto (Metodo dell'iterazione, che vedremo successivamente):$$\begin{array}{l}
\displaystyle T(n) \leq T\left( \left\lfloor  \frac{n}{2}  \right\rfloor  \right)+c \\
\displaystyle T(n) \leq T\left( \left\lfloor  \frac{n}{4}  \right\rfloor  \right)+2c \\
\displaystyle T(n) \leq T\left( \left\lfloor  \frac{n}{8}  \right\rfloor  \right)+3c \\
\displaystyle T(n) \leq i\cdot c + T\left( \left\lfloor  \frac{n}{2^i}  \right\rfloor  \right)
\end{array}$$
Quindi, per $i=\lfloor \log_{2}(n) \rfloor$ si ottiene:$$T(n) \leq c \cdot \lfloor \log_{2}(2) \rfloor + T(1) = O(\log_{2}(n))$$
Molto più veloce rispetto ai precedenti!
### Quanta memoria usa un algoritmo?
- **Algoritmo non ricorsivo**: dipende dalla memoria allocata (variabili, array, matrici e strutture dati).
- **Algoritmo ricorsivo**: dipende dalla memoria allocata ad ogni chiamata e dal numero di chiamate che sono contemporaneamente attive.

- Ogni chiamata usa almeno **memoria costante** (anche senza variabili).
- Per analizzare le ricorsioni è bene usare sempre **l'albero delle ricorsioni**.

Esempio in **fibonacci2** le chiamate attive formano un cammino (P) radice-nodo, dove P ha al più n nodi.

Mentre in **fibonacci6** l'albero ha un'altezza $O(\log(n))$, ogni nodo/chiamata usa memoria costante, quindi lo spazio è $O(\log(n))$.
### Riepilogo finale
Dal riepilogo finale:

|            | Tempo di Esecuzione | Occupazione di Memoria |
| ---------- | ------------------- | ---------------------- |
| fibonacci2 | $$O(\phi^n)$$       | $$O(n)$$               |
| fibonacci3 | $$O(n)$$            | $$O(n)$$               |
| fibonacci4 | $$O(n)$$            | $$O(1)$$               |
| fibonacci5 | $$O(n)$$            | $$O(1)$$               |
| fibonacci6 | $$O(\log_{2}(n))$$  | $$O(\log_{2}(n))$$     |
Possiamo notare quello che è stato detto precedentemente, nell'ottimizzazione si può dover "spendere" dello spazio per ottenere del tempo o viceversa.