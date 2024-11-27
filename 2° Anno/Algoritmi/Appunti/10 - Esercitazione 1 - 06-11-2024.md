### Esercizio 1
Dimostrare o confutare la seguente affermazione:
Siano f(n) e g(n) due funzioni sempre non negative. Allora vale:
$$\displaystyle f(n)=O(g(n))\implies 2^{f(n)}=O(2^{g(n)})$$

caso 1
$f(n) = n$
$\displaystyle g(n)= \frac{n}{2}$

$\displaystyle 2^{n}\not= O\left( 2^{\frac{n}{2}} \right)$ 

### Esercizio 2
Progettare un algoritmo (efficiente) che, dato un array ordinato A[1:n] di n interi e un intero x, trova (se esistono) due indici i e j, i < j, tale che A[i]+A[j]=x

Soluzione ovvia provare tutte le coppie di indici i,j

```
Banale (A,x)
for i=1 to n-1 do
	for j=i+1 to n do 
		if (A[i]+A[j]=x) then return (i,j)
return (-1,-1)
```

complessità della soluzione ovvia $O(n^2)$
trovare una soluzione più efficiente

$A= [2,\ 5,\ 9,\ 14,\ 20,\ 21,\ 25,\ 40]$
