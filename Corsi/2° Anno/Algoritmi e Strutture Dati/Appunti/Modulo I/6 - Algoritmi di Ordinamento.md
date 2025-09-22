[[5 - Metodi di risoluzione equazioni ricorrenza|Torna alla lezione precedente]]
[[7 - Progettare Algoritmi con strutture dati eff.|Continua alla lezione successiva]]
Per quanto riguarda gli **algoritmi di ordinamento** analizziamo quelli di *confronto*:
- [[6 - Algoritmi di Ordinamento#^1b6cb2|Selection Sort]]
- [[6 - Algoritmi di Ordinamento#^fccf0b|Insertion Sort]]
- [[6 - Algoritmi di Ordinamento#^85319c|Bubble Sort]]
- [[6 - Algoritmi di Ordinamento#^ee0d19|Merge Sort]]
- [[6 - Algoritmi di Ordinamento#^ea3233|Quick Sort]]
### Problema dell'Ordinamento
Dato un insieme S di n oggetti presi da un dominio totalmente **ordinato**, ordinare S.

Abbiamo un **input** di n numeri e vogliamo in **output** una *permutazione* del primo ordinata in maniera crescente o decrescente. Vi sono diversi metodi per farlo e hanno ottimizzazioni e casi diversi.
### Ordinare in tempo quadratico
Algoritmi semplici da capire ed implementare, ma poco efficienti.
#### Selection Sort
^1b6cb2

In questo algoritmo, in modo iterativo, cerco l'elemento minimo dell'array e lo sostituisco con la k-esima posizione (quindi estendiamo l'ordinamento a k+1). Ovviamente in questo algoritmo k risulta essere la posizione su cui abbiamo ordinato.![[m14.png]]

Possiamo implementarlo nello pseudo-codice in questa maniera:
 > $\text{SelectionSort}(array\ A)$
 > 1.   $\text{for } k=0\text{ to } n-2 \text{ do}$
 > 2.      $m = k + 1$
 > 3.      $\text{for }j=k+2\text{ to }n\text{ do}$
 > 4.         $\text{if }(A[j] < A[m])\text{ then }m=j$
 > 5.      $\text{scambia }A[m]\text{ con }A[k+1]$

Mentre un'implementazione in Python è la seguente:
```Python
def insertion_sort(array: list):
	for i in range(1, len(array)):
		key = arr[i]
		j = i-1
		while j >= 0 and key < arr[j]:
			arr[j + 1] = arr[j]
			j -= 1
		arr[j + 1] = key
	return arr
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
Ma l'analisi è **stretta**? Cioè, $T(n)=\Theta(n^2)$? Analizziamo la linea più importante nel codice che corrisponde a: `if (A[j] < A[m]) then m=j`. Quindi:$$T(n)\geq \displaystyle\sum_{k=0}^{n-2} (n-k-1)=\displaystyle\sum_{k=0}^{n-1} \frac{n(n-1)}{2}=\Theta (n^2)\quad \implies\quad T(n) = \Omega (n^2) \quad\implies\quad T(n)=\Theta (n^2)$$
#### Insertion Sort
^fccf0b

Estendiamo l'ordinamento da k a k+1 elementi, posizioniamo l'elemento (k+1)-esimo nella posizione corretta rispetto ai primi k elementi. 
![[m15.png]]
#### Bubble Sort
^85319c

Eseguiamo n-1 scansioni, dove ad ogni scansione guardiamo le coppie di elementi adiacenti e li scambiamo nell'ordine corretto.
![[m16.png]]
### Ordinare in tempo meno che quadratico
#### Merge Sort
^ee0d19

Per questo algoritmo usiamo la tecnica **divide et impera**:
- Divide: dividi l'array a metà
- Risolvi i due problemi ricorsivamente
- Impera: fondi le due sotto-sequenze ordinate

Lo pseudo-codice della funzione principale di Merge Sort è la seguente:
> $\text{MergeSort}(array A,\ int\ i,\ int\ f)$
> 1.   $\text{if }(i < f)\text{ then}$
> 2.      $\displaystyle m = \left\lfloor  \frac{i+f}{2}  \right\rfloor$
> 3.      $\text{MergeSort}(A,\ i,\ m)$
> 4.      $\text{MergeSort}(A,\ m+1,\ f)$
> 5.      $\text{Merge}(A, i, m, f)$

Guardiamo l'albero di ricorsione:![[l64.png]]

Avendo un array di dimensione `n`, lo dividiamo a metà, eseguiamo la chiama ricorsiva sulla metà e quando ritorna sarà ordinata, uguale per l'altra metà. Quando entrambe sono ordinate vengono unite tramite il **merge**. Ma cosa fa il merge?

Troviamo l'implementazione nella sezione `Codici Algoritmi/Python`.
##### Procedura merge
Dati due array ordinati A e B, essi possono essere fusi rapidamente:
- Estrai ripetutamente il minimo di A e B e copialo nell'array di output fino a che A o B non diventa vuoto.
- Copia gli elementi dell'array non vuoto alla fine dell'array di output.

Quindi lo pseudo-codice risulta essere il seguente:
> $\text{Merge}(A,\ left,\ mid,\ right)$
> 1.   $\text{Sia X un array ausiliario di lunghezza }f_2 - i_1 + 1$
> 2.   $i = 1;\ left_c = left;\ right_c=mid+1$
> 3.  $\text{while }(left_{c} \leq mid\ and\ right_{c} \leq right) do$
> 4.      $\text{if }(A[left_{c}] \leq A[right_{c}])$
> 5.         $\text{them }X[i] = A[left_{c}]\text{ e incrementa i e }left_c$
> 6.      $\text{else }X[i] = A[k_2]\text{ e incrementa i e }right_{c}$
> 7.   $\text{if }(left_{c} \leq mid)\text{ then copia }A[left_{c},\ mid]\text{ alla fine di X}$
> 8.   $\text{else copia }A[right_{c},\ right]\text{ alla fine di X}$
> 9.  $\text{copia X in }A[left,\ right]$

Quanto costa però? Fondendo le due sequenze ordinate costerà $\Theta(n_{1}+n_{2})$ essendo che deve **consumare** uno alla volta ogni elemento degli array.
##### Merge Sort (Tempo di esecuzione)
La complessità temporale del merge sort è descritta dalla seguente relazione di ricorsiva, caratterizzata dal costo di ogni ricorsione e il numero di ricorsioni:$$T(n)=2\left( T\left( \frac{n}{2} \right) \right)+ O(n)$$
Usando il teorema master otteniamo:$$T(n)=O(n\cdot \log(n))$$
##### Merge Sort (Memoria Ausiliaria)
La complessità spaziale del Merge Sort è di $\Theta (n)$:
- La procedura di merge usa memoria pari alla dimensione totale da fondere.
- Non sono mai attive due procedure di merge contemporaneamente.
- Ogni chiamata del Merge Sort usa memoria costante (esclusa la parte di merge).
- Il numero di chiamate attive contemporaneamente è di $O(\log(n))$.

Il Merge Sort non **ordina in loco**.
####  Quick Sort
^ea3233

Vi sono diverse versioni del quick sort: caso peggiore, caso medio e versione randomizzata.
Generalmente però, usa la tecnica del **divide et impera**:
- **Divide**: scegli un elemento x della sequenza (perno) e partiziona la sequenza in elementi $\leq x$ e in elementi $>x$.
- Risolvi i due problemi ricorsivamente.
- **Impera**: restituisci la concatenazione delle due sotto-sequenze ordinate.
##### Funzione Partizione
La funzione partizione usa un **perno** (ad esempio il primo elemento), scorrendo l'array in parallelo da sinistra verso destra fermandosi su un elemento maggiore del perno e viceversa fermandoci su uno minore del perno, scambia gli elementi e riprendi la scansione. Fermati quando i due indici sono incrociati:![[l65.png]]

Lo pseudo-codice è appunto:
> $\text{Partition}(array\ A,\ int\ i,\ int\ f)\to int$
> 1.   $x=A[i]$
> 2.   $inf = i$
> 3.   $sup = f + 1$
> 4.   $\text{while }(true)\text{ do}$
> 5.      $\text{do }(inf = inf + 1)\text{ while } (inf \leq f\ \ and\ \ A[inf] \leq x)$
> 6.      $\text{do }(sup = sup - 1)\text{ while }(A[sup] > x)$
> 7.       $\text{if }(inf < sup)\text{ then scambia }A[inf] e A[sup]$
> 8.      $\textbf{else break}$
> 9.    $\text{scambia }A[i]\text{ e }A[sup]\text{ // mette il perno al centro}$
> 10.  $\textbf{return}\text{ sup // restituisce la posizione del perno}$

Abbiamo una proprietà **invariante**: in ogni istante gli elementi $A[i],\ \dots,\ A[inf-1]$ sono $\leq$ del perno, mentre gli altri ($A[sup+1],\ \dots,\ A[f]$) sono $>$ del perno.
 
Che complessità ha? Beh dovendo leggere tutto l'array il tempo di esecuzione è $O(n)$.
##### Implementazione Quick Sort
Allora impacchettiamo tutto, il quick sort corrisponde a:
> $\text{QuickSort}(\array A,\ int\ i,\ int\ f)$
> 1.   $\text{if }(i < f)\text{ then}$
> 2.     $m = \text{Partition}(A,\ i,\ f)$
> 3.     $\text{QuickSort}(A,\ i,\ m - 1)$
> 4.     $\text{QuickSort}(A,\ m + 1,\ f)$

Quindi risulterà così:![[l66.png]]

Corretto? Certamente!
Dopo Partition $A[i:m-1]$ contiene $elem \leq perno$, $A[m]$ il perno, $A[m+1:f]\ \ elementi > perno$. Le chiamate ricorsive ordinano $A[i:f]$.
Complessità?

##### Complessità nel caso peggiore o migliore
Ogni volta che invochiamo partition posiziona almeno un elemento in modo corretto (il perno). Quindi dopo n invocazioni di partition, con costo ognuna di costo $O(n)$ ho un array ordinato. Quindi il costo complessivo è $O(n^{2})$.

Questo si verifica quando il perno scelto ad ogni passo è il minimo o il massimo degli elementi dell'array. La complessità in questo caso è:$$\begin{array}{l}
T(n) & = T(n-1)+T(0) + O(n) \\
 & = T(n-1) + O(1) + O(n) \\
& = T(n-1) + O(n) \\
 &  & T(n) = O(n^2)
\end{array}$$
Se fosse perfettamente bilanciato allora nel caso migliore avremmo $O(n\cdot \log(n))$. 
![[l67.png]]
**Ma nel caso medio?**
##### Intuizioni nel caso medio
La partizione può essere sbilanciata, ma più è bilanciata più è veloce, dovremmo trovare ogni volta un perno pessimo per rovinare l'ottimizzazione dell'algoritmo. Sbilanciando però anche a 99-1, sembrando quindi molto instabile, troviamo che...![[l68.png]]
La complessità è sempre $O(n\log(n))$!

E se le istanze non sono equiprobabili? Possiamo randomizzare la scelta del perno x. Nella nostra implementazione infatti abbiamo usato un algoritmo Quick Sort Randomizzato.
##### Teorema
L'algoritmo **QuickSort** randomizzato ordina in loco un array di lunghezza n in tempo $O(n^2)$ nel caso peggiore e $O(n \cdot \log (n))$ con alta probabilità, ovvero con probabilità almeno $\displaystyle1 - \frac{1}{n}$.
