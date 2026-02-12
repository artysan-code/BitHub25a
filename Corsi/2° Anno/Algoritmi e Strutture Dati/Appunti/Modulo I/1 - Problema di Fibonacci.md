 > [!abstract] Introduzione al Problema
> Come modello di calcolo per permetterci di analizzare in maniera più qualitativa la complessità temporale e spaziale, studiamo il **Problema di Fibonacci**. 
> L'obiettivo è analizzare diverse strategie risolutive per comprendere il trade-off tra tempo, spazio e correttezza.

### L'isola dei conigli
> [!example] Il quesito di Leonardo da Pisa
> Quanto velocemente si riprodurrebbe una popolazione di conigli in certe condizioni?
> Partendo da un'isola deserta con una coppia di conigli, seguiamo queste regole:
> - Una coppia concepisce due coniglietti di sesso diverso ogni anno (una nuova coppia).
> - La gestazione dura un anno.
> - I conigli si riproducono dal secondo anno di vita.
> - I conigli sono immortali.

> [!definition] Relazione di Ricorrenza
> Nell'anno $n$ sono presenti tutte le coppie dell'anno precedente ($F_{n-1}$) più una nuova coppia per ogni coppia presente due anni prima ($F_{n-2}$).
> $F_{n}=\begin{cases}F_{n-1} + F_{n-2}&se\ n\geq 3 \\1&se\ n =1,2\end{cases}$

### Strategie Risolutive
#### Algoritmo 1: Formula Diretta
> [!warning] Problema di Correttezza
> Basato sulla formula chiusa di Binet. A causa dell'approssimazione dei numeri irrazionali ($\sqrt{5}$), l'algoritmo produce errori per valori di $n$ elevati. **Non è corretto** per ogni $n$.

$F_{n}=\frac{1}{\sqrt{5}}(\phi^n-\hat{\phi}^n) \quad \text{con } \phi \approx 1.618, \hat{\phi} \approx -0.618$

> [!code] Algoritmo 1: Formula di Binet
> **Pseudocodice**
> ```text
> alg fibonacci1(intero n) -> intero
> 	phi = (1 + sqrt(5)) / 2
> 	hat_phi = (1 - sqrt(5)) / 2
> 	return (phi^n - hat_phi^n) / sqrt(5)
> ```
> **Implementazione (Python)**
> ```python
> def fibonacci1(n: int) -> int:
> 	return int((pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n)) / sqrt(5))
> ```

#### Algoritmo 2: Ricorsione Diretta
> [!code] Algoritmo 2: Ricorsione
> Applica direttamente la definizione del problema tramite la tecnica *Divide et Impera*.
>
> **Pseudocodice**
> ```text
> alg fibonacci2(intero n) -> intero
> 	if n <= 2 then return 1
> 	else return fibonacci2(n-1) + fibonacci2(n-2)
> ```
> **Implementazione (Python)**
> ```python
> def fibonacci2(n: int) -> int:
> 	if n <= 2:
> 		return 1
> 	else:
> 		return fibonacci2(n-1) + fibonacci2(n-2)
> ```

> [!warning] Analisi della Complessità
> Sebbene corretto, l'algoritmo è estremamente inefficiente. Il numero di chiamate ricorsive cresce come i numeri di Fibonacci stessi.
> **Tempo:** $T(n) \approx \Theta(\phi^n)$ (Esponenziale)
> **Spazio:** $O(n)$ (dovuto allo stack delle chiamate attive)

#### Algoritmo 3: Metodo di caching (Array)
> [!tip] Caching (Memoization)
> Memorizziamo i valori calcolati in un array per evitare ricalcoli inutili.

> [!code] Algoritmo 3: Memoization
> **Pseudocodice**
> ```text
> alg fibonacci3(intero n) -> intero
> 	Sia Fib un array di dimensione n
> 	Fib[1] <- 1
> 	Fib[2] <- 1
> 	for i = 3 to n do
> 		Fib[i] <- Fib[i-1] + Fib[i-2]
> 	return Fib[n]
> ```
> **Implementazione (Python)**
> ```python
> def fibonacci3(n: int) -> int:
> 	Fib = [0, 1, 1]
> 	for i in range(3, n + 1):
> 		Fib.append(Fib[i-1] + Fib[i-2])
> 	return Fib[n]
> ```

> [!success] Valutazione
> **Tempo:** $O(n)$ (Lineare) - Un miglioramento enorme rispetto all'esponenziale.
> **Spazio:** $O(n)$ - Occupazione di memoria proporzionale all'input, non sempre ottimale come cosa.

#### Algoritmo 4: Metodo di caching (Ottimizzato)
> [!tip] Ottimizzazione Spazio
> Notiamo che per calcolare $F_n$ servono solo $F_{n-1}$ e $F_{n-2}$. Possiamo usare solo due variabili.

> [!code] Algoritmo 4: Spazio Costante
> **Pseudocodice**
> ```text
> alg fibonacci4(intero n) -> intero
> 	a <- 1
> 	b <- 1
> 	for i = 3 to n do
> 		c <- a + b
> 		a <- b
> 		b <- c
> 	return c
> ```
> **Implementazione (Python)**
> ```python
> def fibonacci4(n: int) -> int:
> 	a, b = 1, 1
> 	for i in range(3, n + 1):
> 		c = a + b
> 		a, b = b, c
> 	return c
> ```

> [!success] Valutazione
> **Tempo:** $O(n)$ come il precedente.
> **Spazio:** $O(1)$ (Costante), ottimale rispetto al precedente.

#### Algoritmo 6: Potenza Veloce di Matrici
> [!abstract] Approccio Avanzato
> Possiamo calcolare l'n-esimo numero di Fibonacci elevando alla potenza $n$ una particolare matrice $2 \times 2$. Sfruttando l'algoritmo di elevamento a potenza veloce (Binary Exponentiation), riduciamo il numero di moltiplicazioni da $n$ a $\log n.
>
> **Logica:** L'idea è che se $n$ è pari, $A^n = (A^{n/2})^2$, dimezzando i passaggi. Se $n$ è dispari, moltiplichiamo una volta in più per $A$. Questa strategia trasforma un processo lineare in uno logaritmico.

> [!theorem] Proprietà delle Matrici
> $\begin{pmatrix}1&1\\1&0\end{pmatrix}^n=\begin{pmatrix}F_{n+1}&F_n\\F_n&F_{n-1}\end{pmatrix}$

> [!code] Algoritmo 6: Matrice Logaritmica
> **Pseudocodice**
> ```text
> alg fibonacci6(intero n) -> intero
> 	A <- [[1, 1], [1, 0]]
> 	M <- potenzaDiMatrice(A, n-1)
> 	return M[0][0]
> 
> func potenzaDiMatrice(Matrice A, intero k) -> Matrice
> 	if k = 0 return MatriceIdentità
> 	M <- potenzaDiMatrice(A, floor(k/2))
> 	M <- M * M  // Moltiplicazione riga per colonna
> 	if k è dispari then M <- M * A
> 	return M
> ```
> **Implementazione (Python)**
> ```python
> def fibonacci6(n: int) -> int:
> 	A = np.array([[1, 1], [1, 0]])
> 	M = potenzadiMatrice(A, n - 1)
> 	return M[0][0]
> 
> def potenzadiMatrice(A, k: int):
> 	if k == 0: return np.eye(2)
> 	M = potenzadiMatrice(A, k // 2)
> 	M = np.dot(M, M)
> 	if k % 2 == 1: M = np.dot(M, A)
> 	return M
> ```

> [!success] Risultato Finale
> **Tempo:** $O(\log n)$ - Il più efficiente per valori di $n$ molto grandi.
> **Spazio:** $O(\log n)$ (dovuto alla ricorsione).

### Lemmi e Proprietà Fondamentali
> [!theorem] Lemma 1: Foglie dell'albero di ricorsione
> Il numero di foglie dell'albero della ricorsione di *fibonacci2(n)* è esattamente $F_n$.

> [!theorem] Lemma 2: Nodi Interni
> In un albero dove ogni nodo interno ha due figli, il numero di nodi interni è pari al numero di foglie - 1.

> [!info] Tecnica di Elevamento al Quadrato
> Per calcolare $A^n$, se $n$ è pari calcoliamo $(A^{n/2})^2$. Se $n$ è dispari calcoliamo $A \cdot (A^{n/2})^2$. Questa tecnica riduce le moltiplicazioni da $n$ a $\log n$.

### Riepilogo Confronto
| Algoritmo  | Complessità Temporale | Occupazione Spazio | Note                         |
| :--------- | :-------------------- | :----------------- | :--------------------------- |
| fibonacci2 | $\Theta(\phi^n)$      | $O(n)$             | Inutilizzabile per $n > 40$  |
| fibonacci3 | $O(n)$                | $O(n)$             | Semplice, ma spreca memoria  |
| fibonacci4 | $O(n)$                | $O(1)$             | Ottimo per uso comune        |
| fibonacci6 | $O(\log n)$           | $O(\log n)$        | Ottimale per calcoli massivi |
