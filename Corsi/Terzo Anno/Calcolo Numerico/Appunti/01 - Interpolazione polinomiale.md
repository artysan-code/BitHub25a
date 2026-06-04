# Interpolazione polinomiale (approssimazione)

E' data da una funzione $f:[a,b]\to \mathbb{R}$ di cui sono noti i valori $f(x_{0}),f(x_{1}),\dots,f(x_{n})$ in $u + 1$ punti distinti $x_{0},x_{1},\dots,x_{n}\in[a,b]$
Si sceglie una classe $C$ di funzioni definite su $[a,b]$ a valori in $\mathbb{R}$ e si vuole approssimare la funzione $f(x)$ con una funzione $p:[a,b]\to \mathbb{R}$ che appartiene in $C$  e che nei punti $x_{0},x_{1},\dots,x_{n}$ assume i valori $f(x_{0}),f(x_{1}),\dots,f(x_{n})$.
Una scelta comune fatta bene e' quella di prendere $C$ come lo spazio vettoriale (reale) dei polinomi di grado $\leq u$:$$C=\mathbb{R}_{n}[x]=\{a_{0}+a_{1}x+a_{2}x^2+\dots+a_{n}x^n:a_{0},a_{1},\dots,a_{n}\in \mathbb{R}\}$$
con questa scelta di $C$ si può dimostrare che $\exists! p(x)\in \mathbb{R}_{n}[x]$ tale che $p(x_{i})=f(x_{i})\quad \forall i=0,1,\dots,n$.

## Teorema
Siano $(x_{0},y_{0}),(x_{1},y_{1}),\dots,(x_{n},y_{n})\in \mathbb{R}^2$ tali che $x_{0},x_{1},\dots,x_{n}$ sono tutti distinti. Allora  $\exists!\ p(x)\in \mathbb{R}_{n}[x]$ t.c. $p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n$
![[Pasted image 20251007153144.png]]

$\exists! p(x)\in \mathbb{R}_{3}[x]$ t.c. $p(x_{0})=y_{0},p(x_{1})=y_{1},p(x_{2})=y_{2},p(x_{3})=x_{3}$

## Dimostrazione 1

Osserviamo che un generico polinomio $p(x)$ in $\mathbb{R}_{n}[x]$ 
$p(x)=a_{0}+a_{1}x+a_{2}x^2+\dots+a_{n}x^n$
$p(x)$ soddisfa la condizione $p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n$ 
se e solo se $$\begin{rcases}{l}
a_{0}+a_{1}x_{0}+a_{2}x_{0}^2+\dots+a_{n}x_{0}^n= & y_{0} \\
a_{0}+a_{1}x_{1}+a_{2}x_{1}^2+\dots+a_{n}x_{1}^n= & y_{1} \\
a_{0}+a_{1}x_{2}+a_{2}x_{2}^2+\dots+a_{n}x_{0}^n= & y_{2} \\
\vdots +\vdots +\vdots +\dots+\vdots = & \vdots\\
a_{0}+a_{1}x_{n}+a_{2}x_{n}^2+\dots+a_{n}x_{n}^n= & y_{n}
\end{rcases}\iff 
\begin{pmatrix}
1 & x_{0} & x_{0}^2 & \dots  & x_{0}^n \\
1 & x_{1} & x_{1}^2 & \dots  & x_{1}^n \\
1 & x_{2} & x_{2}^2 & \dots  & x_{2}^n \\
\vdots & \vdots & \vdots & \ddots & \vdots\\
1 & x_{n} & x_{n}^2 & \dots  & x_{n}^n
\end{pmatrix}
\begin{pmatrix}
a_{0} \\
a_{1} \\
a_{2} \\
\vdots \\
a_{n}
\end{pmatrix}=
\begin{pmatrix}
y_{0} \\
y_{1} \\
y_{2} \\
\vdots \\
y_{n}
\end{pmatrix}$$
$$\begin{pmatrix}
1 & x_{0} & x_{0}^2 & \dots  & x_{0}^n \\
1 & x_{1} & x_{1}^2 & \dots  & x_{1}^n \\
1 & x_{2} & x_{2}^2 & \dots  & x_{2}^n \\
\vdots & \vdots & \vdots & \ddots & \vdots\\
1 & x_{n} & x_{n}^2 & \dots  & x_{n}^n
\end{pmatrix}=V(x_{0},x_{1},\dots,x_{n})=\text{matrice di Vandermonde sui nodi } x_{0},x_{1},\dots,x_{n}$$
la matrice su $x_{0},x_{1},\dots,x_{n}$ e' invertibile perche' tra poco dimostreremo che $$\det(V(x_{0},x_{1},\dots,x_{n}))=\begin{cases}
1 & \text{se }n=0 \\
\displaystyle\prod_{\begin{array}{}
i,j=0 \\
j<i
\end{array}}^n(x_{i},x_{j})=\begin{array}{l}
(x_{1}-x_{0})\cdot \\
(x_{2}-x_{0})\cdot(x_{2}-x_{1})\cdot \\
(x_{3}-x_{0})\cdot(x_{3}-x_{1})\cdot(x_{3}-x_{2})\cdot \\
(x_{n}-x_{0})\cdot(x_{n}-x_{1})\cdot\ldots \cdot(x_{n}-x_{n-1})
\end{array} & \text{se }n\geq_{1}
\end{cases}$$
e dunque $\det(V(x_{0},x_{1},\dots,x_{n})\neq 0$ perche' per ipotesi tutti i nodi $x_{0},x_{1},\dots,x_{n}$ sono tutti distinti.
Poiche' $V(x_{0},x_{1},\dots,x_{n})$ e' invertibile, il sistema lineare ($*$) ha una e un unica soluzione che e' $$\begin{pmatrix}
a_{0} \\
a_{1} \\
a_{2} \\
\vdots \\
a_{n}
\end{pmatrix}=[V(x_{0},x_{1},\dots,x_{n})]^{-1}\begin{pmatrix}
y_{0} \\
y_{1} \\
y_{2} \\
\vdots \\
y_{n}
\end{pmatrix}\implies$$
$\implies\exists!p(x)\in \mathbb{R}_{n}[x]$ che soddisfa $p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n$ e inoltre $p(x)$ e' dato da $p(x)=a_{0}+a_{1},x+a_{2}x^2+\dots+a_{n}x^n$ con vettore dei coefficienti $\begin{pmatrix}a_{0} \\ \vdots \\ a_{n}\end{pmatrix}$ dato dalla $(\$)$

Per concludere la dimostrazione resta solo da dimostrare la $(\star)$
## Dimostrazione di $\star$ per $n=3$
>Per $n=0$ la $\star$ e' ovvia perche' $V(x_{0})=[1]$ mentre per $n\geq1$ la dimostrazione e' identica a quella che facciamo per $n=3$

Devo calcolare il $\det(x_{0},x_{1},x_{2},x_{3})$

> [!todo] Appunti interrotti
> Continuare da videolezione 1, ora 01:07.
