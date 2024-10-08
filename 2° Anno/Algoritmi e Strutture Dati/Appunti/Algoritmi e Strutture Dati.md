- Ogni algoritmo fornisce il procedimento per giungere alla soluzione di un dato problema di calcolo (essenza computazionale).
- L'algoritmo è diverso da un programma
	- Il programma è la codifica di un algoritmo
	- L'algoritmo è un programma distillato dal linguaggio di programmazione.

L'**algoritmo "buono"** deve essere:
- *Corretto*: fare ciò per cui è stato progettato.
- *Efficiente*: usano poche risorse di calcolo, tempo e memoria (algoritmi veloci). Alcuni algoritmi necessitano velocità per funzionare. L'efficienza si può usare per "pagare altre caratteristiche".

Gli algoritmi sono anche un linguaggio per descrivere.

Ogni algoritmo ha due componenti fondamentali:
- Identificazione della appropriata tecnica di progetto algoritmico.
- Individuazione del nucleo matematico del problema stesso.

Istanza di un problema è un input specifico di un problema.
Dimensione dell'istanza è quanto input abbiamo.

Ogni configurazione di input può avere istanze e dimensioni d'istanza diverse.

Modello di calcolo specifica che operazioni possiamo svolgere (es. delle monete la bilancia).

L'algoritmo allora è la strategia di risoluzione (la strategia di pesatura per il nostro es.), con descrizione comprensibile e compatta. Deve poter eseguire dei passi per risolvere l'algoritmo in una generica istanza.

La correttezza dell'algoritmo impone che l'algoritmo deve funzionare per ogni generica istanza. (trova la moneta falsa a prescindere dalla posizione, da quante monete sono, etc...)
 
La complessità temporale è la # di calcoli eseguiti prima di identificare la soluzione. Dipende dall'istanza e dalla dimensione della stessa.

La complessità temporale nel caso peggiore invece corrisponde al # massimo di istruzioni che deve eseguire su una istanza di una certa dimensione. E' una delimitazione superiore a quanto mi costa risolvere una generica istanza

L'efficienza dell'algoritmo, cioè deve essere veloce.

Algoritmo Uno
``` Copy
Alg1 (X=[x_1, x_2, ...])
	for i=2 to n do
		if peso(x_1) > peso(x_i) then return x_1
		if peso(x_1) < peso(x_i) then return x_i
```

E' corretto, ma quante pesate fa? Nel caso peggiore fa n-1 pesate.
E' efficiente l'algoritmo? La domanda da fare sarebbe **posso fare di meglio**? Si

Osserviamo che l'ultima pesata non serve, quindi il caso peggiore diventerebbe n-2.


Algoritmo Due
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

Algoritmo Tre
```
Alg3 (X=[x_1, x_2, ...])
	if( |X|=1 ) then return x_1

	dividi X in due gruppi X_1 e X_2 e se |X| è dispari una ulteriore moneta y

	if peso(X_1) = peso(X_2) then return y

	if peso(X_1) > peso(X_2) then return Alg3(X_1) else return Alg3(X_2)
```

Corretto? SI, istruzioni nel caso peggiore? parte-intera(log_2(n))
Efficiente? Si può fare di meglio.
Complessità? Allora:

P(n): # di passi che Alg3 esegue nel caso peggiore su un'istanza di dimensione n
P(n) = P(parte-intera(n/2)) + 1 

P(1) = 0
P(n) = P(parte-intera(n/2)) + 1 = P(parte-intera((1/2)parte-intera(n/2))) + 2 <= P(parte-intera(n/4)) + 2 <= ... <= P(parte-intera(/2^i)) + i

Quando parte-intera(n/2^i) = 1? quando i = parte-intera(log_2(n))

<= P(1) + parte-intera(log_2(n)) = parte-intera(log_2(n)) 