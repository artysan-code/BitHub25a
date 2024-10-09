## Lezione I (Introduzione)
#### Algoritmi e Programmi
- Ogni algoritmo fornisce il procedimento per giungere alla soluzione di un dato problema di calcolo (essenza computazionale).
- L'algoritmo è diverso da un programma
	- Il programma è la codifica di un algoritmo
	- L'algoritmo è un programma distillato dal linguaggio di programmazione.

L'**algoritmo "buono"** deve essere:
- *Corretto*: fare ciò per cui è stato progettato.
- *Efficiente*: usano poche risorse di calcolo, tempo e memoria (algoritmi veloci). Alcuni algoritmi necessitano velocità per funzionare. L'efficienza si può usare per "pagare altre caratteristiche".

L'algoritmica è un linguaggio che ci permette di descrivere i problemi e le loro soluzioni.

Ogni algoritmo ha due componenti fondamentali:
- Identificazione della appropriata tecnica di progetto algoritmico.
- Individuazione del nucleo matematico del problema stesso.
#### Concetti fondamentali dell'algoritmo
I costrutti con cui definiamo un algoritmo sono i seguenti:
- **Istanza**: un input del problema.
- **Dimensione dell'istanza**: la quantità di istanze che vi sono nel problema desiderato (che viene generalmente identificato con il valore n).

Ogni configurazione di input può avere istanze e dimensioni d'istanza diverse.

- **Modello di calcolo**: specifica che operazioni possiamo svolgere (es. delle monete la bilancia).

L'algoritmo allora è la strategia di risoluzione (la strategia di pesatura per il nostro es.), con descrizione comprensibile e compatta. Deve poter eseguire dei passi per risolvere l'algoritmo in una generica istanza.

- **La correttezza dell'algoritmo**: impone che l'algoritmo funzioni per ogni generica istanza. (trova la moneta falsa a prescindere dalla posizione, da quante monete sono, etc...)
- **La complessità temporale**: il numero di passi eseguiti prima di identificare la soluzione. Dipende dall'istanza e dalla dimensione della stessa.
- **La complessità temporale nel caso peggiore**: invece corrisponde al # massimo di istruzioni che deve eseguire su una istanza di una certa dimensione. E' una delimitazione superiore a quanto costa risolvere una generica istanza.
- **L'efficienza dell'algoritmo**: velocità dell'algoritmo.
#### Esempio della moneta falsa
###### Algoritmo Uno
Uso la prima moneta e la confronto con le altre.

``` Copy
Alg1 (X=[x_1, x_2, ...])
	for i=2 to n do
		if peso(x_1) > peso(x_i) then return x_1
		if peso(x_1) < peso(x_i) then return x_i
```

E' corretto, ma quante pesate fa? Nel caso peggiore fa n-1 pesate.
E' efficiente l'algoritmo? La domanda da fare sarebbe **posso fare di meglio**? Si

Osserviamo che l'ultima pesata non serve, quindi il caso peggiore diventerebbe n-2. Ma questo non basta.
###### Algoritmo Due
Peso le monete a coppie confrontandole.
```
Alg2 (X=[x_1, x_2, ...])
	k = [n/2]
	for i=1 to k do
		if peso(x_2i-1) > peso (x_2i) then return x_2i-1
		if peso(x_2i-1) < peso (x_2i) then return x_2i
	return x_n
```

E' corretto? Si
Quante istruzioni fa nel caso peggiore? N/2
E' efficiente? Ma ancora meglio **si può fare di meglio**? Si
###### Algoritmo Tre
Peso le monete dividendole ogni volta in due gruppi
```
Alg3 (X=[x_1, x_2, ...])
	if( |X|=1 ) then return x_1

	dividi X in due gruppi X_1 e X_2 e se |X| è dispari una ulteriore moneta y

	if peso(X_1) = peso(X_2) then return y

	if peso(X_1) > peso(X_2) then return Alg3(X_1) else return Alg3(X_2)
```
Corretto? SI, istruzioni nel caso peggiore? $\lfloor log_2(n)\rfloor$
Complessità? Allora:

P(n): # di passi che Alg3 esegue nel caso peggiore su un'istanza di dimensione n

$P(n) = P(\lfloor\frac{n}{2}\rfloor) + 1\quad\quad\quad P(1) = 0$

$P(n) = P(\lfloor\frac{n}{2}\rfloor) + 1 = P(\lfloor\frac{n}{2}\lfloor\frac{n}{2}\rfloor\rfloor)) + 2 \leq P(\lfloor\frac{n}{4}\rfloor) + 2 \leq\ ...\ \leq P(\lfloor\frac{n}{2^i}\rfloor) + i \leq P(1) + \lfloor log_2(n)\rfloor = \lfloor log_2(n)\rfloor$
Quando $\lfloor\frac{n}{2^i}\rfloor = 1$? Per $i = \lfloor log_2(n)\rfloor$

Efficiente? Si può fare di meglio.

###### Algoritmo quattro
Posso dividere in tre gruppi invece che due.
```Copy
Alg4(X):
	if (|X|=!) then return unica moneta in X
	
	dividi X in tre gruppi X_1, X_2, X_3 di dimensione bilanciata con X_1 e X_2 i
	gruppi con la stessa dimensione.
	
	if peso(X_1) = peso(X_2) then return Alg4(X_3)
	if peso(X_1) > peso(X_2) then return Alg4(X_1)
	else return Alg4(X_2)
```

Corretto? Si
Pesate nel caso peggiore? $\lceil log_{_3}(n)\rceil$
Efficiente? Non saprei... però meglio di Alg3
Complessità? Beh:

$P(n)$: numero di pesate che Alg4 esegue nel caso peggiore su un'istanza di dimensione n

$P(n)=P(\lceil \frac{n}{3} \rceil) + 1\quad\quad\quad P(1)=0\quad\quad\quad\text{Oss. }P(x) \text{ è una funzione non decrescente in x}$

$\text{Sia k il più piccolo intero tale che } 3^k\geq n\implies n^{'}=3^k \implies k \geq log_{_3}(n)\implies^{k\ intero}\ k=\lceil log_{_3}(n)\rceil$

$P(n) \leq P(n^{'})=k=\lceil log_{_3}(n)\rceil$

$P(n^{'})=P(\frac{n^{'}}{3})+1 =$
$= P(\frac{n^{'}}{3^i})+i = P(1) + k = k$ 

Molto più veloce degli altri.

#### Lower Bound
Il **lower bound** è la delimitazione inferiore alla complessità di un problema (non si può andare più veloci).

Un qualsiasi algoritmo che correttamente individua la moneta falsa
fra n monete deve effettuare nel caso peggiore almeno $\lceil log_{_3}(n)\rceil$
pesate.

Alg4 è un algoritmo ottimo per il problema.
#### Da fare
- Implementare immagini e schemi

## Lezione II (Introduzione informale agli algoritmi)
#### Problema "i numeri di Fibonacci"
Passiamo quindi ora ad un modello di calcolo più simile la computer e ragioniamo in modo più qualitativo rispetto alla complessità temporale degli algoritmi.
##### L'isola dei conigli
Quanto velocemente si riprodurrebbe una popolazione di conigli in certe condizioni? Questa è la domanda che si è fatto Leonardo da Pisa, partendo da un isola deserta con due conigli.

Le regole ci permettono di studiare meglio questo problema sono le seguenti:
- Una coppia di conigli concepisce due coniglietti di sesso diverso ogni anno, i quali formeranno una nuova coppia.
- La gestazione dura un anno.
- I conigli cominciano a riprodursi soltanto al secondo anno dopo la loro nascita.
- I conigli sono immortali.

Possiamo descrivere questa riproduzione con il seguente albero:

![[Pasted image 20241009091317.png]]

##### La regola di espansione
Abbiamo che nell'anno $n$ ci sono tutte le coppie dell'anno precedente e una nuova coppia di conigli per ogni coppia presente due anni prima. Chiamiamo allora $F_n$ il numero di coppie rispetto all'anno n e imponiamo la seguente relazione di ricorrenza:$$t$$
#### Ma come calcoliamo $F_n$?
##### Algoritmo Uno
Possiamo usare un approccio numerico che calcoli direttamente i numeri di Fibonacci.
![[Pasted image 20241009091702.png]]

Quindi l'algoritmo uno è:

![[Pasted image 20241009091900.png]]

Ma questo algoritmo è corretto? Beh... 

A causa dell'approssimazione dei due $\phi$ non riusciamo ad approssimare sempre al valore corretto. Aumentando però l'approssimazione troveremo sempre verso infinito un numero che verrà approssimato in maniera errata.

##### Algoritmo Due
Usando invece una funzione ricorsiva possiamo fare:

```
algoritmo fibonacci2(intero n) -> intero
	if (n <= 2) then return 1
	else return fibonacci2(n-1) + fibonacci2(n-2)
```

Questa tecnica rispetta il *divide et impera*. Però grazie a questa tecnica ora l'algoritmo è **corretto**!

Ma è efficiente?

In ogni modello di calcolo rudimentale ogni linea di codice costa un'unità di tempo. Di conseguenza calcoliamo le linee di codice mandate in esecuzione:
- Se $n\leq 2$ allora abbiamo una linea di codice
- Se $n = 3$ ci sono quattro linee di codice, due per la chiamata fibonacci2(3) e una per fibonacci2(2) e fibonacci2(1)
- Se invece è $n$? Cerchiamo di studiarlo tramite una funzione $f(n)$.

Quindi definendo $f(n)$ come $\text{\# di linee di codice eseguite dall'algoritmo sull'input n}$.

Quindi $f(n)=2+f(n-1)+f(n-2)$  e  $f(1)=f(2)=1$ ma a cosa corrisponde? Dobbiamo risolvere questa **equazione di ricorrenza**.

Per risolverlo usiamo un **albero della ricorsione**:
![[Pasted image 20241009093520.png]]

I nodi alla base dell'albero sono i **casi base**, in quanto non eseguono ricorsioni. Per dedurre una formula dobbiamo capire quante foglie e nodi interni possiede l'albero.

##### Primo Lemma 
Il numero di foglie dell'albero della ricorsione di *fibonacci2(n)* è pari a $F_n$. ( #lemma1 )
**Dimostrazione**
guarda il file
##### Secondo Lemma
Il numero di nodi interni di un albero in cui ogni nodo interno ha due figli è pari al numero di foglie - 1. ( #lemma2 )
**Dimostrazione**
(Per induzione sul numero di nodi dell'albero n)

In totale le linee di codice eseguite sono:$$F_n + 2(F_n -1)=3F_n-2$$
fibonacci2 è molto lento...

Infatti già a n=100 sarà impossibile calcolare il numero.

##### Algoritmo Tre
L'idea è di memorizzare i valori calcolati per permettere a "calcoli di Fibonacci successivi" di essere semplificati in linea di tempo.
```
algoritmo fibonacci3(intero n) -> intero
	sia Fib un array di n interi
	Fib[1] <- 1; Fib[2] <- 1
	for i = 3 to n do
		Fib[i] <- Fib[i - 1] + Fib[i - 2]
	return Fib[n]
```

Tempo di esecuzione? Beh

La prima, la seconda e l'ultima riga di codice vengono eseguite una sola volta, mentre la terza e la quarta linea vengono eseguite n volte. Quindi:$$T(n)\leq n+n+3=2n + 3$$
fibonacci3 impiega un tempo lineare (proporzionale a n) rispetto a fibonacci2 che invece impiega un tempo esponenziale.
##### Algoritmo Quattro
Proviamo ad ottimizzare lo spazio occupato dall'algoritmo precedente

#### Notazione Asintotica
Vogliamo esprimere $T(n)$ in modo qualitativo anche perdendo un po' di **precisione**, ma guadagnando semplicità.

Ignorando le costanti moltiplicative e i termini di ordine inferiore, otteniamo:$$\begin{array}{}
T(n) = 5n + 3 = O(n)\\
T(n) = 5n^2 + 5n - 3 = O(n^2)
\end{array}$$
Ma è comunque sensato misurare la complessità di un algoritmo contando le righe di codice eseguite? si vedrà!

Si dice che $f(n)=O(g(n))$ se $f(n) \leq c(g(n))$ con c che è una costante e n che è abbastanza grande.

Si può sperare di calcolare $F_n$ in un tempo minore a $O(n)$?

##### Lemma Tre
$$\begin{pmatrix}1&1\\1&0\end{pmatrix}^n=\begin{pmatrix}F_{n+1}&F_n\\F_n&F_{n-1}\end{pmatrix}$$
##### Algoritmo Cinque
