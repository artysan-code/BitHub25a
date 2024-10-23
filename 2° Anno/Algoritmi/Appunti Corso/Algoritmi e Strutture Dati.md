## Lezione I (Introduzione)
### Algoritmi e Programmi
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
### Concetti fondamentali dell'algoritmo
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
### Esempio della moneta falsa
#### Algoritmo Uno
Uso la prima moneta e la confronto con le altre.

``` pseudo-codice
Alg1 (X=[x_1, x_2, ...])
	for i=2 to n do
		if peso(x_1) > peso(x_i) then return x_1
		if peso(x_1) < peso(x_i) then return x_i
```

E' corretto, ma quante pesate fa? Nel caso peggiore fa n-1 pesate.
E' efficiente l'algoritmo? La domanda da fare sarebbe **posso fare di meglio**? Si

Osserviamo che l'ultima pesata non serve, quindi il caso peggiore diventerebbe n-2. Ma questo non basta.
#### Algoritmo Due
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
#### Algoritmo Tre
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

#### Algoritmo quattro
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

$P(n^{'})=P(\frac{n^{'}}{3})+1 =P(\frac{n^{'}}{3^i})+i = P(1) + k = k$ 

Molto più veloce degli altri.

### Lower Bound
Il **lower bound** è la delimitazione inferiore alla complessità di un problema (non si può andare più veloci).

Un qualsiasi algoritmo che correttamente individua la moneta falsa
fra n monete deve effettuare nel caso peggiore almeno $\lceil log_{_3}(n)\rceil$
pesate.

Alg4 è un algoritmo ottimo per il problema.
## Lezione II (Introduzione informale agli algoritmi)
### Problema "i numeri di Fibonacci"
Passiamo quindi ora ad un modello di calcolo più simile la computer e ragioniamo in modo più qualitativo rispetto alla complessità temporale degli algoritmi.
#### L'isola dei conigli
Quanto velocemente si riprodurrebbe una popolazione di conigli in certe condizioni? Questa è la domanda che si è fatto Leonardo da Pisa, partendo da un isola deserta con due conigli.

Le regole ci permettono di studiare meglio questo problema sono le seguenti:
- Una coppia di conigli concepisce due coniglietti di sesso diverso ogni anno, i quali formeranno una nuova coppia.
- La gestazione dura un anno.
- I conigli cominciano a riprodursi soltanto al secondo anno dopo la loro nascita.
- I conigli sono immortali.

Possiamo descrivere questa riproduzione con il seguente albero:

![[l2-2.png]]

#### La regola di espansione
Abbiamo che nell'anno $n$ ci sono tutte le coppie dell'anno precedente e una nuova coppia di conigli per ogni coppia presente due anni prima. Chiamiamo allora $F_n$ il numero di coppie rispetto all'anno n e imponiamo la seguente relazione di ricorrenza:$$
F_{n}=
\begin{cases}
F_{n-1} + F_{n-2}&&se\ n\geq 3 \\
1&&se\ n =1,2
\end{cases}$$
### Ma come calcoliamo $F_n$?
#### Algoritmo Uno
Possiamo usare un approccio numerico che calcoli direttamente i numeri di Fibonacci.$$\begin{array}{l}
F_{n}=\frac{1}{\sqrt{5}}(\phi^n-\overset{\wedge}{\phi^n})&dove \\
\phi = \frac{1 + \sqrt{ 5 }}{2} \approx +1.618 \\
\overset{\wedge}{\phi} = \frac{1 - \sqrt{ 5 }}{2} \approx -0.618
\end{array}$$
Quindi l'algoritmo uno è:
```python
from math import sqrt

def fibonacci1(n: int) -> int:
	return int((pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n)) / sqrt(5))
```

Ma questo algoritmo è corretto? Beh... 

A causa dell'approssimazione dei due $\phi$ non riusciamo ad approssimare sempre al valore corretto. Aumentando però l'approssimazione troveremo sempre verso infinito un numero che verrà approssimato in maniera errata.

#### Algoritmo Due
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

Quindi definendo $f(n)$ come $\text{\# di linee di codice eseguite dall'algoritmo sull'input n}$.

Quindi $f(n)=2+f(n-1)+f(n-2)$  e  $f(1)=f(2)=1$ ma a cosa corrisponde? Dobbiamo risolvere questa **equazione di ricorrenza**.

Per risolverlo usiamo un **albero della ricorsione**:
![[l2-3.png]]

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

#### Algoritmo Tre
L'idea è di memorizzare i valori calcolati per permettere a "calcoli di Fibonacci successivi" di essere semplificati in linea di tempo.
```python
def fibonacci3(n: int) -> int:
	Fib = [0, 1]
	for i in range(3, n):
		Fib.append(Fib[i-1] + Fib[i-2])
	return Fib[n-1]
```
Prendiamo il valore a $n-1$ in quanto l'array in programmazione inizia da 0 e non da 1 come nello pseudo-codice.

Tempo di esecuzione? Beh

La prima, la seconda e l'ultima riga di codice vengono eseguite una sola volta, mentre la terza e la quarta linea vengono eseguite n volte. Quindi:$$T(n)\leq n+n+3=2n + 3$$
fibonacci3 impiega un tempo lineare (proporzionale a n) rispetto a fibonacci2 che invece impiega un tempo esponenziale. L'altra faccia della medaglia però è lo spazio occupato, che sarà proporzionale all'input.
#### Algoritmo Quattro
Proviamo ad ottimizzare lo spazio occupato dall'algoritmo precedente:
```python
def fibonacci4(n: int) -> int:
	a = 1 # F_n-1
	b = 1 # F_n-2
	for _ in range(3, n+1):
		c = a + b # F_n
		a = b
		b = c
	return c
```

Non è il miglior algoritmo possibile e possiamo usare il **lemma tre** per poter ottimizzare l'algoritmo.
##### Terzo Lemma
$$\begin{pmatrix}1&1\\1&0\end{pmatrix}^n=\begin{pmatrix}F_{n+1}&F_n\\F_n&F_{n-1}\end{pmatrix}$$
#### Notazione Asintotica
Vogliamo esprimere $T(n)$ in modo qualitativo anche perdendo un po' di **precisione**, ma guadagnando semplicità.

Ignorando le costanti moltiplicative e i termini di ordine inferiore, otteniamo:$$\begin{array}{}
T(n) = 5n + 3 = O(n)\\
T(n) = 5n^2 + 5n - 3 = O(n^2)
\end{array}$$
Ma è comunque sensato misurare la complessità di un algoritmo contando le righe di codice eseguite? si vedrà!

Si dice che $f(n)=O(g(n))$ se $f(n) \leq c(g(n))$ con c che è una costante e n che è abbastanza grande.

Si può sperare di calcolare $F_n$ in un tempo minore a $O(n)$?
#### Algoritmo Cinque
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

##### Calcolo di potenze
Si può calcolare l'ennesima potenza, elevando al quadrato la $\left\lfloor  \frac{n}{2}  \right\rfloor$-esima potenza. Se n è dispari basta eseguire un'ulteriore moltiplicazione.$$\begin{array}{}
3^2=9 & 3^4=9^2=81 & 3^8=81^2=6561
\end{array}$$
Abbiamo eseguito 3 prodotti invece che 7!
#### Algoritmo Sei
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
- Il tempo speso dentro `potenzadiMatrice` è costante.
- Si esegue una chiamata ricorsiva di `potenzadiMatrice` con input $\left\lfloor  \frac{n}{2}  \right\rfloor$ 

L'equazione di ricorrenza è pertanto:$$\begin{array}{}
T(n) \leq T\left( \left\lfloor  \frac{n}{2}  \right\rfloor  \right)+c \\
T(n) \leq T\left( \left\lfloor  \frac{n}{4}  \right\rfloor  \right)+2c \\
T(n) \leq T\left( \left\lfloor  \frac{n}{8}  \right\rfloor  \right)+3c \\
T(n) \leq i\cdot c + T\left( \left\lfloor  \frac{n}{2^i}  \right\rfloor  \right)
\end{array}$$
Quindi, per $i=\lfloor \log_{2}(n) \rfloor$ si ottiene:$$T(n) \leq c \cdot \lfloor \log_{2}(2) \rfloor + T(1) = O(\log_{2}(n))$$
Molto più veloce rispetto ai precedenti!

#### Quanta memoria usa un algoritmo?
- **Algoritmo non ricorsivo**: dipende dalla memoria allocata (variabili, array, matrici e strutture dati).
- **Algoritmo ricorsivo**: dipende dalla memoria allocata ad ogni chiamata e dal numero di chiamate che sono contemporaneamente attive.

- Ogni chiamata usa almeno **memoria costante** (anche senza variabili).
- Per analizzare le ricorsioni è bene usare sempre **l'albero delle ricorsioni**.

Esempio in **fibonacci2** le chiamate attive formano un cammino (P) radice-nodo, P ha al più n nodi.

Mentre in **fibonacci6** l'albero ha un'altezza $O(\log(n))$, ogni nodo/chiamata usa memoria costante, quindi lo spazio è $O(\log(n))$.
#### Riepilogo finale
Dal riepilogo finale:

|            | Tempo di Esecuzione | Occupazione di Memoria |
| ---------- | ------------------- | ---------------------- |
| fibonacci2 | $$O(\phi^n)$$       | $$O(n)$$               |
| fibonacci3 | $$O(n)$$            | $$O(n)$$               |
| fibonacci4 | $$O(n)$$            | $$O(1)$$               |
| fibonacci5 | $$O(n)$$            | $$O(1)$$               |
| fibonacci6 | $$O(\log_{2}(n))$$  | $$O(\log_{2}(n))$$     |
Possiamo notare quello che è stato detto precedentemente, nell'ottimizzazione si può dover "spendere" dello spazio per ottenere del tempo o viceversa.
## Lezione III
E' sensato misurare la complessità di un algoritmo contando il numero di linee di codice?
### Modelli di calcolo
Un modello utilizzato ampiamente nel passato era quello della **macchina di Turing**, che era composto di un meccanismo di controllo, un nastro di memorizzazione e una testina di lettura e scrittura. Questo modello però è poco vicino alla macchina che noi studiamo.

Un modello più realistico di calcolo è quello della **RAM**, cioè della macchina a registri. Possiede: un programma finito, un nastro di input/output, una memoria strutturata come array e una CPU esegue istruzioni.

Tramite questo modello analizziamo il programma basandoci sul concetto di **passo elementare**. I passi elementari su una **RAM** sono:
- Istruzione di ingresso/uscita (I/O).
- Operazione aritmetico/logica.
- Accesso/modifica contenuto in memoria.

Ma quanto costano queste operazioni? (Il metodo per calcolarlo nel generico è quello del **costo uniforme**)
##### Criterio di costo uniforme
Tutte le operazioni hanno lo stesso costo e la complessità temporale è misurata come **numero di passi elementari eseguiti**.
##### Criterio di costo logaritmico
Il costo dell'operazione singola dipende dalla dimensione degli operandi dell'istruzione. Quindi un'operazione con un operando di valore $x$ costerà $\log(x)$. Modella meglio la complessità di **algoritmi "numerici"**.z
### Caso peggiore e caso medio
Misurando il tempo di esecuzione di un algoritmo in funzione della dimensione n delle istanze, noteremo che **istanze diverse**, a parità di dimensione, potrebbero richiedere tempo diverso.

Ma cosa vuol dire caso medio e caso peggiore?

Sia **tempo(I)** il tempo di esecuzione di un algoritmo di sull'istanza **I**, il **caso peggiore**:$$T_{worst}(n)=max_{\text{ istanze I di dimensione n }}\{tempo(I)\}$$
Rappresenta quindi il tempo che viene impiegato quando le istanze di input comportano più lavoro all'algoritmo. Rappresenta una **garanzia** sul tempo di esecuzione.


Sia **P(I)** la probabilità di occorrenza dell'istanza **I**:$$\begin{array}{}
T_{avg}(n)=\displaystyle\sum_{I}^n\{P(I) tempo(I)\} & \text{dove I sono le istanze e n il numero di esse}
\end{array}$$
Quindi $T_{avg}(n)$ è intuitivamente il tempo di esecuzione nel **caso medio**, ovvero sulle istanze di input tipiche del problema. Ma come conosco la **distribuzione di probabilità sulle istanze?** Semplice! (di solito) Non puoi!

Bisogna fare una assunzione (spesso non realistica).
### Esercizio
Analizzare la complessità nel caso medio del primo algoritmo di pesatura (Alg1) presentato nella prima lezione. Rispetto alla distribuzione di probabilità sulle istanze, si assuma che la moneta falsa possa trovarsi in modo equiprobabile in una qualsiasi delle n posizioni.
### Notazione Asintotica
Esprimiamo la complessità computazionale di un algoritmo espressa con una funzione $T(n)$.$$T(n): \#\text{passi elementari eseguti su RAM nel caso peggiore su un'istanza di dimensione n}$$
L'idea è descrivere T(n) in modo qualitativo. Perdiamo un po’ in precisione (senza perdere l’essenziale) e guadagniamo semplicità.

Si ignorano:
- Costanti moltiplicative
- Termini di ordine inferiore

Tempi di esecuzione di differenti algoritmi per istanze di dimensioni crescenti su un processore che sa eseguire milioni di istruzioni di alto livello al secondo. L'indicazione **very long** indica che il tempo di calcolo supera $10^{25}$ anni.

|               |  $n$   | $n \log_n n$ |  $n^2$  |    $n^3$     |   $1,5^n$    |      $2^n$      |      $n!$       |
| :-----------: | :----: | :----------: | :-----: | :----------: | :----------: | :-------------: | :-------------: |
|    $n=10$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    <1 sec    |     <1 sec      |      4 sec      |
|    $n=30$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    <1 sec    |     18 min      | $10^{25}$ years |
|    $n=50$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    11 min    |    36 years     |    very long    |
|    $n=100$    | <1 sec |    <1 sec    | <1 sec  |    1 sec     | 12.892 years | $10^{17}$ years |    very long    |
|   $n=1.000$   | <1 sec |    <1 sec    |  1 sec  |    18 min    |  very long   |    very long    |    very long    |
|  $n=10.000$   | <1 sec |    <1 sec    |  2 min  |   12 days    |  very long   |    very long    |    very long    |
|  $n=100.000$  | <1 sec |    2 sec     | 3 hours |   32 years   |  very long   |    very long    |    very long    |
| $n=1.000.000$ | 1 sec  |    20 sec    | 12 days | 31.710 years |  very long   |    very long    |    very long    |

### Notazione asintotica O 
$f(n)=O(g(n))$ se $\exists$ due costanti $c>0\ e\ n_{0}\geq 0$ tali che $0\leq f(n) \leq g(n)\quad \forall n \geq n_{0}$. Quindi:

Sia $f(n)=2n^2+3n$ allora:
- $f(n)=O(n^3)\quad\quad\quad(c=1,n_{0}=3)$
- $f(n)=O(n^2)\quad\quad\quad (c=3,n_{0}=3)$
- $f(n)\not=O(n)$

Dire che $O(n^2)=4n^2+3n$ è un'abuso di notazione, si dovrebbe scrivere $4n^2+3n \in O(n^2)$.
Inoltre, se:$$\lim_{ n \to \infty  }\frac{f(n)}{g(n)}=0 \implies f(n)=O(g(n)) $$
Ma:$$\begin{array}{}
\displaystyle f(n)=O(g(n)) \centernot\implies\lim_{ n \to \infty } \frac{f(n)}{g(n)}=0 \\
\displaystyle f(n)=O(g(n)) \to \lim_{ n \to \infty } \frac{f(n)}{g(n)} < \infty \text{ (se esiste) }
\end{array}$$
### Notazione asintotica $\Omega$
Sia $f(n)=\Omega(g(n))\text{ se } \exists\ c>0\ \ e\ \ n_{0}\geq 0\ |\ f(n) \geq c\cdot g(n) \geq 0\text{ per ogni }n\geq n_{0}$.

Sia $f(n)=2n^2-3n$, allora 
- $f(n)=\Omega(n)\quad\quad\quad(c=1,n_{0}=2)$
- $f(n)=\Omega(n^2)\quad\quad\quad(c=1,n_{0}=3)$
- $f(n)\neq\Omega(n^3)$

Inoltre:$$\begin{array}{}
\displaystyle \lim_{ n \to \infty  }\frac{f(n)}{g(n)}=\infty \implies f(n)=\Omega (g(n)) \\
\displaystyle f(n)=\Omega(g(n)) \centernot\implies \lim_{ n \to \infty  }\frac{f(n)}{g(n)}= \infty \\
\displaystyle f(n)=\Omega(g(n)) \implies \lim_{ n \to \infty  }\frac{f(n)}{g(n)} > 0 \text{ (se esiste) }
\end{array}$$
### Notazione asintotica $\Theta$
$f(n)=\Theta (g(n))$ se $\exists$ tre costanti $c_{1}, c_{2} > 0$ e $n_{0}\geq 0$ tali che $c_{1}\cdot g(n) \leq f(n) \leq c_{2}\cdot g(n)$ per ogni $n\geq n_{0}$.

Ad esempio data $f(n)=2n^2-3n$ allora:
- $f(n)=\Theta(n^2)\quad\quad\quad (c_{1}=1,c_{2}=2,n_{0}=3)$
- $f(n)\not=\Theta(n)$
- $f(n)\not=\Theta(n^3)$

Inoltre:$$\begin{array}{}
f(n)=\Theta(g(n)) &  \overset{\text{non il contrario} }{\implies} & f(n)=O(g(n)) \\
f(n)=\Theta(g(n)) &  \overset{\text{non il contrario} }{\implies} & f(n)=\Omega(g(n)) \\
 & \text{ma} \\
f(n)=\Theta(g(n))  & \iff & f(n)=O(g(n))\ \ e\ \ f(n)=\Omega(g(n))
\end{array}$$
Infine, per studiare matematicamente meglio le funzioni, abbiamo anche che:$$\begin{array}{}
\displaystyle \text{Se } \lim_{ n \to \infty } \frac{f(n)}{g(n)}=c>0 \text{ allora } f(n)=\Theta(g(n))
\end{array}$$

### Proprietà della notazione asintotica
#### Transitività
$$\begin{matrix}
f(n)=\Theta(g(n)) & e & g(n)=\Theta(h(n)) & \implies & f(n)=\Theta(h(n)) \\
f(n)=O(g(n)) & e & g(n)=O(h(n)) & \implies & f(n)=O(h(n)) \\
f(n)=\Omega(g(n)) & e & g(n)=\Omega(h(n)) & \implies & f(n)=\Omega(h(n)) \\
f(n)=o(g(n)) & e & g(n)=o(h(n)) & \implies & f(n)=o(h(n)) \\
f(n)=\omega(g(n)) & e & g(n)=\omega(h(n)) & \implies & f(n)=\omega(h(n))
\end{matrix}$$
#### Riflessività
$$\begin{array}{}
f(n)=\Theta(f(n)) \\
f(n)=O(f(n)) \\
f(n)=\Omega(f(n))
\end{array}$$
#### Simmetria
$$\begin{array}{}
f(n)=\Theta(g(n)) & \iff & g(n)=\Theta(f(n))
\end{array}$$
#### Simmetria trasposta
$$\begin{array}{}
f(n)=O(g(n)) & \iff & g(n)=\Omega(f(n)) \\
f(n)=o(g(n)) & \iff & g(n)=\omega(f(n))
\end{array}$$
## Lezione IV
### Studio della complessità
#### Algoritmo Ricerca Sequenziale
Dato il seguente algoritmo, in cui cerchiamo un elemento in un array non ordinato:
```
algoritmo RicercaSequenziale(array L, elem x) → intero
1. n = lunghezza di L
2. i=1
3. for i=1 to n do
4. if (L[i]=x) then return i \\trovato
5. return -1 \\non trovato
```

Qual'è la sua complessità nel caso peggiore? Beh è $\Omega(n)$, in quanto non è possibile cercare un elemento se non li guardiamo tutti prima.

Mentre nel caso medio abbiamo 
#### Algoritmo Ricerca Sequenziale Array Ordinato
Dato invece un algoritmo in cui l'array è ordinato e dobbiamo trovare un elemento:
```
algoritmo RicercaBinariaRic(array L, elem x, int i, int j) → intero
1. if (i>j) then return -1
2. m= (i+j)/2
3. if (L[m]=x) then return m
4. if (L[m]>x) then return RicercaBinariaRic(L, x, i, m-1)
5. else return RicercaBinariaRic(L, x, m+1,j)
```

Si può usare l'algoritmo di **ricerca binaria**
### Algoritmi Ricorsivi
Un algoritmo ricorsivo è quello ad esempio di **fibonacci2**, analizziamolo quindi la sua **equazione di ricorrenza**. Essa sarà:
$T(n)=T(n-1)+T(n-2)+O(1)$

Mentre per l'algoritmo **alg4** per il peso delle monete? Beh:
$T(n)=T\left( \frac{n}{3} \right)+O(1)$

Allora per la **ricerca binaria**?
$T(n)=T\left( \frac{n}{2} \right) + O(1)$

Generalmente la **complessità computazionale** di un algoritmo ricorsivo è descrivibile tramite la sua **equazione di ricorrenza**.
#### Metodo dell'iterazione (o srotolamento)
Immaginiamo che la nostra equazione di ricorrenza è:$$T(n)=c+T\left( \frac{n}{2} \right) = 2c + T\left( \frac{n}{4} \right)=ic+T\left( \frac{n}{2^i} \right)$$
Quindi per $i=\log_{2}(n)$ abbiamo che $T(n)=c\log_{2}(n) + T(1) = \Theta(\log_{2}(n))$

Se $T(n)=T(n-1)+1$, allora:$$T(n)=T(n-1)+1=T(n-2)+1+1=T(n-i)+i$$
E se $i=n-1$ allora $T(n)=T(1)+n-1=\Theta(n)$

Vediamone uno un po' più difficile:$$\begin{array}{} \\
T(n)=2T(n-1)+1=2(2T(n-2)+1)+1=4T(n-2)+2+1= \\
=4(2T(n--3)+1)+2+1=8T(n-3)+4+2+1=2^iT(n-i)+\displaystyle \sum_{j=o}^{i-1}2^j
\end{array}$$
Quindi per $i=n-1$ abbiamo che:$$T(n)=2^{n-1} T(1)+\displaystyle\sum_{j=0}^{n-2}2^j=\Theta(2^n)$$

Allora per Fibonacci ricorsivo?$$\begin{array}{}
T(n)=T(n-1)+T(n-2)+1=T(n-1)+2T(n-3)+T(n-4)+3=\dots?
\end{array}$$
Possiamo provare ad analizzare con **l'albero della ricorsione**.
#### Tecnica dell'Albero della ricorsione
Per disegnare l'albero della ricorsione dobbiamo:
- disegnare l’albero delle chiamate ricorsive indicando la dimensione di ogni nodo
- stimare il tempo speso da ogni nodo dell’albero
- stimare il tempo complessivo “sommando” il tempo speso da ogni nodo

Per $T(n)=T(n-1)+1$ abbiamo che ogni nodo possibile costa **uno** ma, quanti nodi abbiamo?$$n \to n-1 \to n-2 \to n-i \to 2 \to 1$$ Quindi abbiamo n nodi, allora $\Theta(n)$.

Mentre per $T(n)=T(n-1)+n$ abbiamo che ogni nodo costa n a causa del termine n, ma quanti nodi abbiamo?$$n \to n-1 \to n-2 \to n-i \to 2 \to 1$$ 
Beh sempre n!
Quindi possiamo sicuramente fissare un **Upper Bound** con $O(n^2)$. Ma se calcoliamo solo la prima parte dell'albero generico che abbiamo fatto:$$n \to n-1 \to n-2 \to n-i$$
Abbiamo $\frac{n}{2}$ nodi e ognuno di loro costa almeno $\frac{n}{2}$, quindi:$$T(n)=\frac{n}{2}\cdot \frac{n}{2}=\frac{n^2}{4}$$
Quindi possiamo fissare un **Lower Bound** di $\Omega(n^2)$, che ci porta insieme all'upper bound a dire che l'algoritmo è $\Theta(n^2)$.

Ritorniamo ad una precedente equazione ricorsiva:$$T(n)=2T(n-1)+1$$
Sappiamo sicuramente che ogni chiamata costa uno, quindi ogni nodo costa uno. Sappiamo anche che l'altezza dell'albero è n-1:
![[Pasted image 20241016101318.png]]

Quanti nodi ha un albero binario completo di altezza h? $\displaystyle\sum_{i=0}^h 2^i=2^{h-1}-1$. Quindi possiamo dire che $T(n)\leq n2^n=\Theta(n2^n) \implies T(n)=O(n 2^n)$

Allora adesso arriviamo a ciò che volevamo analizzare **fibonacci2**:
![[Pasted image 20241016101756.png]]
Ogni nodo costa uno, ma quanti nodi ha? Lo sappiamo dalla definizione $\Theta(\phi^n)$ quindi $T(n)=o(2^n)$.

## Lezione V
Metodi per risolvere le equazioni di ricorrenza:
- iterazione
- albero della ricorsione
- sostituzione
- teorema Master
- cambiamento di variabile
### Metodo della sostituzione
Dobbiamo:
- Indovinare la forma della soluzione.
- Usare l'induzione matematica per provare che la soluzione è quella intuita

Esempio:$$T(n)=n+T\left( \frac{n}{2} \right),\ T(1)=1$$
Possiamo pensare che tenda a $T(n)=n\log_{2}(n)$ oppure $T(n)=n$ ma tra i due vince il secondo. Ora proviamo a dimostrare che $T(n)\leq c\cdot n$:$$\begin{array}{l}
\text{Passo base: } & T(1)=1 \leq c \cdot 1 \quad \forall\ c \geq 1 \\
\text{Passo induttivo: } \\
\text{Assumo che } T(k) \leq c \cdot k\quad \forall\ k<n \\
T(n)=n+T\left( \frac{n}{2} \right)\leq n+c \cdot \left( \frac{n}{2} \right)
\end{array}$$
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
Estendiamo l'ordinamento da k a k+1 elementi, posizioniamo l'elemento (k+1)-esimo nella posizione corretta rispetto ai primi k elementi.![[l62.png]]
#### Bubble Sort
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
### Algoritmo di Quick Sort (divide et impera)
Vi sono diverse versioni del quick sort: caso peggiore, caso medio e versione randomizzata.

Utilizza la tecnica del divide et impera:
- **Divide**: scegli un elemento x della sequenza (perno) e partiziona la sequenza in elementi $\leq$ x e in elementi $\geq$ x.
- Risolvi i due problemi ricorsivamente.
- **Impera**: restituisci la concatenazione delle due sotto-sequenze ordinate.
#### Partizione (perno)
Scegli un perno (ad esempio il primo elemento), scorri l'array in parallelo da sinistra verso destra fermandoci su un elemento maggiore del perno e viceversa fermandoci su uno minore del perno, scambia gli elementi e riprendi la scansione. Fermati quando i due indici sono incrociati:![[l65.png]]
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

## To Do List
- Aggiungere gli pseudo-codici in maniera consona accanto al codice python di ogni algoritmo.