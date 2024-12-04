### Problema dell'Ordinamento
Dato un insieme S di n oggetti presi da un dominio totalmente **ordinato**, ordinare S.

Abbiamo un **input** di n numeri e vogliamo in **output** una *permutazione* del primo ordinata in maniera crescente o decrescente. Vi sono diversi metodi per farlo e hanno ottimizzazioni e casi diversi.
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

^fccf0b

Estendiamo l'ordinamento da k a k+1 elementi, posizioniamo l'elemento (k+1)-esimo nella posizione corretta rispetto ai primi k elementi.![[l62.png]]
#### Bubble Sort

^0a2155

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
### Algoritmo di Quick Sort
Vi sono diverse versioni del quick sort: caso peggiore, caso medio e versione randomizzata.

Generalmente però, usa la tecnica del **divide et impera**:
- **Divide**: scegli un elemento x della sequenza (perno) e partiziona la sequenza in elementi $\leq$ x e in elementi $\geq$ x.
- Risolvi i due problemi ricorsivamente.
- **Impera**: restituisci la concatenazione delle due sotto-sequenze ordinate.
#### Funzione Partizione
Scegli un **perno** (ad esempio il primo elemento), scorri l'array in parallelo da sinistra verso destra fermandoci su un elemento maggiore del perno e viceversa fermandoci su uno minore del perno, scambia gli elementi e riprendi la scansione. Fermati quando i due indici sono incrociati:![[l65.png]]
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
