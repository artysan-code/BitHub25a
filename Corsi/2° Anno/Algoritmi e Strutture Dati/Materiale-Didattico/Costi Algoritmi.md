## Generali

| Nome Algoritmo | Costo (memoria) | Tempo           | Descrizione          |
| -------------- | --------------- | --------------- | -------------------- |
| Fibonacci 2    | $O(n)$          | $O(\phi^{n})$   | Formula matematica   |
| Fibonacci 3    | $O(n)$          | $O(n)$          | Array                |
| Fibonacci 4    | $O(1)$          | $O(n)$          | Variabili Temporanee |
| Fibonacci 5    | $O(1)$          | $O(n)$          | Matrici              |
| Fibonacci 6    | $O(\log_{2} n)$ | $O(\log_{2} n)$ | Potenza Matrici      |
|                |                 |                 |                      |
|                |                 |                 |                      |
|                |                 |                 |                      |

## Ordinamento Confronto

| Nome Algoritmo | Costo (memoria) | Tempo             | Caso Migliore      | Caso Peggiore   |
| -------------- | --------------- | ----------------- | ------------------ | --------------- |
| Selection Sort | $O(1)$          | $\Theta(n^{2})$   | $\Theta(n^{2})$    | $\Theta(n^{2})$ |
| Insertion Sort | $O(1)$          | $\Theta(n^{2})$   | $\Omega (n)$       | $O(n^{2})$      |
| Merge Sort     | $O(n)$          | $\Theta(n\log n)$ | $\Theta (n\log n)$ | $\Theta(n^{2})$ |
| Quick Sort     | $O(\log n)$     | $\Theta(n\log n)$ | $\Theta (n\log n)$ | $O(n^{2})$      |
| Quick sort rnd | $O(\log n)$     | $\Theta(n\log n)$ | $\Theta (n\log n)$ | $O(n^{2})$      |


## Ordinamento non Confronto

| Nome Algoritmo | Costo (memoria) | Tempo             | Caso Migliore      | Caso Peggiore     |
| -------------- | --------------- | ----------------- | ------------------ | ----------------- |
| Heap Sort      | $O(1)$          | $\Theta(n\log n)$ | $\Theta (n\log n)$ | $\Theta(n\log n)$ |
| Integer Sort   | $\Theta(k)$     | $\Theta(n+k)$     | $\Theta (n+k)$     | $\Theta(n+k)$     |
| Bucket Sort    | $\Theta(n+k)$   | $\Theta(n+k)$     | $\Theta (n+k)$     | $O(n^{2})$        |
| Radix Sort     | $O(n+b)$        | $\Theta(d(n+b))$  | $\Theta(d(n+b))$   | $\Theta(d(n+b))$  |

## Heap

| Nome Funzione | Costo (memoria) | Tempo         | Caso Migliore | Caso Peggiore | Descrizione                                      |
| ------------- | --------------- | ------------- | ------------- | ------------- | ------------------------------------------------ |
| fixHeap       | $O(1)$          | $O(\log(n))$  | X             | X             | Ripara l'Heap                                    |
| extractMax    | $O(1)$          | $O(\log(n))$  | X             | X             | Salva il massimo (radice) e lo rimuove dall'heap |
| heapify       | $O(1)$          | $O(n)$        | X             | X             | Costruisce un Heap usando ricorsivamente fixHeap |
| heapSort      | $O(n)$          | $O(n\log(n))$ | X             | X             | Heapify + n volte extractMax                     |
## Dizionario
| Nome Funzione | Costo (Array Non Ord.) | Costo (Array Ord.) | Costo (Array Ord.) (Lista) | Costo (Array Non Ord.) (Lista) |
| ------------- | ---------------------- | ------------------ | -------------------------- | ------------------------------ |
| insert        | $O(1)$                 | $O(n)$             | $O(n)$                     | $O(1)$                         |
| delete        | $O(n)$                 | $O(n)$             | $O(n)$                     | $O(n)$                         |
| search        | $O(n)$                 | $O(\log(n))$       | $O(n)$                     | $O(n)$                         |
## Visite Alberi

| Tipo di Visita                 | Costo Temporale |
| ------------------------------ | --------------- |
| Visita DFS (Depth)             | $O(n)$          |
| Visita BFS (Breatdh)           | $O(n)$          |
| Calcolo Altezza Albero B.      | $O(n)$          |
| Calcola num foglie             | $O(n)$          |
| Calcolo grado medio            | $O(n)$          |
| Somma gradi                    | $O(n)$          |
| Ricerca elemento dentro albero | $O(n)$          |

