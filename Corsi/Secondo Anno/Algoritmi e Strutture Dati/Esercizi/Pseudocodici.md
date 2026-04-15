## Selection Sort
```pseudocodice
SelectionSort(A)
1. for k=1 to n-1 do
2.   m = k
3.   for j=k+1 to n do
4.     if A[j] < A[m] then m=j
5.   scambia A[m] con A[k]
```
## Insertion Sort
```pseudocodice
InsertionSort(A)
1. for k=2 to n do
2.   chiave = A[k]
3.   j = k-1
4.   while j>=1 and A[j] > chiave do
5.     A[j+1] = A[j]
6.     j = j - 1
7.   A[j+1] = chiave
```
## Bubble Sort
```pseudocodice
BubbleSort(A)
1. for k=1 to n-1 do
2.   for j=1 to n-k do
3.     if A[j] > A[j+1] then
4.       scambia A[j] con A[j+1]
```
## Merge Sort
```pseudocodice
MergeSort(A, i, f)
1.  if i < f then
2.    m <- media tra i e f (intero inferiore)
3.    MergeSort(A, i , m)
4.    MergeSort(A, m+1, f)
5.    Merge(A, i, m, f)

Merge(A, init, fin1, fin2)
1.  X <- Array ausiliario di dimensione fin2 - init + 1
2.  i = 0
3.  k1 = init
4.  k2 = fin1 + 1
5.  while (k1 <= fin1) and (k2 <= fin2)
6.    if A[k1] < A[k2] then X[i] = A[k1] e incrementa k1
7.    else X[i] = A[k2] e incrementa k2
8.    incrementa i
9.  if k1 <= fin1 then copia A[k1, fin1] alla fine di X
10. else copia A[k2, fin2] alla fine di X
11. copia X in A[init, fin2]
```
## IntergerSort
```pseudocodice
IntegerSort (A, k)
1.  Dato Y un array di dimensione K
2.  for i=1 to k do Y[i]=0
3.  for i=1 to n do incrementa Y[A[i]]
4.  j = 1
5.  for i=1 to k do
6.    while Y[i] > 0
7.      A[j] = i
8.      j++
9.      Y[i]--
```