[[3 - Modelli di calcolo e Notazione Asintotica|Torna alla lezione precedente]]
[[5 - Metodi di risoluzione equazioni ricorrenza|Continua alla lezione successiva.]]
## Studio della complessità
## Algoritmo Ricerca Sequenziale
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

Mentre nel caso medio abbiamo:$$T_{avg} = \frac{n+1}{2}$$
## Algoritmo Ricerca Sequenziale Array Ordinato
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
## Equazioni di ricorrenza
Un algoritmo ricorsivo è quello ad esempio di **fibonacci2**, analizziamolo quindi la sua **equazione di ricorrenza**. Essa sarà:
$T(n)=T(n-1)+T(n-2)+O(1)$

Mentre per l'algoritmo **alg4** per il peso delle monete? Beh:
$T(n)=T\left( \frac{n}{3} \right)+O(1)$

Allora per la **ricerca binaria**?
$T(n)=T\left( \frac{n}{2} \right) + O(1)$

Generalmente la **complessità computazionale** di un algoritmo ricorsivo è descrivibile tramite la sua **equazione di ricorrenza**.
## Metodo dell'iterazione (o srotolamento)

^40e417

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
## Tecnica dell'Albero della ricorsione

^dbadd5

Per disegnare l'albeo della ricorsione dobbiamo:
- disegnare l’albero delle chiamate ricorsive indicando la dimensione di ogni nodo
- stimare il tempo speso da ogni nodo dell’albero
- stimare il tempo complessivo “sommando” il tempo speso da ogni nodo

Per $T(n)=T(n-1)+1$ abbiamo che ogni nodo possibile costa **uno** ma, quanti nodi abbiamo?$$n \to n-1 \to n-2 \to n-i \to 2 \to 1$$ Quindi abbiamo n nodi, allora $\Theta(n)$.

Mentre per $T(n)=T(n-1)+n$ abbiamo che ogni nodo costa n a causa del termine n, ma quanti nodi abbiamo?$$n \to n-1 \to n-2 \to n-i \to 2 \to 1$$ 
Beh sempre n!
Quindi possiamo sicuramente fissare un **Upper Bound** con $O(n^2)$. Ma se calcoliamo solo la prima parte dell'albero generico che abbiamo fatto:$$n \to n-1 \to n-2 \to n-i$$
Abbiamo $\frac{n}{2}$ nodi e ognuno di loro costa almeno $\frac{n}{2}$, quindi:$$T(n)=\frac{n}{2}\cdot \frac{n}{2}=\frac{n^2}{4}$$
Avendo imposto che un dominio ridotto, corrisponde comunque a circa $n^2$ possiamo fissare un **Lower Bound** di $\Omega(n^2)$, che ci porta insieme all'upper bound a dire che l'algoritmo tende a $\Theta(n^2)$.

Ritorniamo ad una precedente equazione ricorsiva:$$T(n)=2T(n-1)+1$$
Sappiamo sicuramente che ogni chiamata costa uno, quindi ogni nodo costa uno. Sappiamo anche che l'altezza dell'albero è n-1:![[l42.png]]

Quanti nodi ha un albero binario completo di altezza h? $\displaystyle\sum_{i=0}^h 2^i=2^{h-1}-1$. Quindi possiamo dire che $T(n)\leq n2^n=\Theta(n2^n) \implies T(n)=O(n 2^n)$

Allora adesso arriviamo a ciò che volevamo analizzare **fibonacci2**:![[l43.png]]
Ogni nodo costa uno, ma quanti nodi ha? Lo sappiamo dalla definizione $\Theta(\phi^n)$ quindi $T(n)=o(2^n)$.
