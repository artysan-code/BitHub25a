## Lezione I
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

## Lezione II