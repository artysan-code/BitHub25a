primo modulo sono 3 esercizi
1 (16 punti) studiare bene
2 (8 punti) 
3 (8 punti)

impostare bene 2 e 3 esercizio con il primo fatto bene porta a 18 

per fare bene 2 e 3 non basta solo studiare (sono di progettazione di algoritmi)


### Esercizio 1

Input un array A[1,...,n] A[i]$\in \mathbb{Z}\quad \forall i= 1,\dots,n\quad\exists\ m=1,\dots,n$:
1) A[i]<A[m]    $1\leq i\leq m$
   A[i]<A[m]    $m<i\leq n$
2) A[i]<A[i+1]    $1\leq i<m$
   A[i+1]<A[i]    $m\leq i<n$

richieste:
1) trovare m in tempo $\circ(n)$
2) ordinare A in tempo $\circ(n\log n)$ 

esempio:
$A[2,4,20,13,9,6,5,2]$
m= 20

Esempio:
$A[2,3,6,9,20,21,30]$
m=30

```
max.unimodale(A)
	if A[1]>A[2]:
		return 1
	else if A[n]>A[n-1]:
		return n
	else
		BS.unimodale(A,2,(n-1))
```

```
BS.unimodale(A,i,j)
	if i>j
		return -1
	m=|(i+j)/2|
	if A[m]>A[m-1] && A[m]>A[m+1]
		return m
	else if A[m] > A[m-1]
		return BS.unimodale(A,i,m-1)
	else
		return BS.unimodale(A,m+1)
```


```
sort.unimodale(A)
	m=max.unimodale(A)
	if m != n
		inverti(A,m+1,n)
		if m != 1
			merge(A,1,m,n)
```

Per casa
Definire le funzioni inverti (o(n)) e merge (o(n))

### Esercizio 2

A[1,...,n] A[i]$\in \mathbb{N}$
trovare i*, j* ,    i*<j*
$\forall\ i,j\quad i<j\quad A[j*]-A[i*]>A[j]-A[i]$

A = [20, 11, 2, 5, 4, 10, 9, 21]

max[k]= indice del massimo in A[k,n]

max[1, 2, 6, 6, 6, 6, 7, 8]

max(A[:-1...n]=max{A[i+1],max(A[i,...,n])})
```
max[1,...,n]
max[n]=n    O(n)
for i=n-1,...,1
	if A[i]>A[max[i+1]]
		max[i]=i
	else
			max[i]=max[i+1]
```

```
alg(A)
	calcola max    O(n)
	i*=1
	j*=max[i]
	delta=A[j*]-A[i*]
	for i=2,...,n-1    O(n)
		if (A[max[i+1]]-A[i]>delta)    O(1)
			i*=i
			j*=max[i+1]
			delta=A[i*]-A[j*]
```