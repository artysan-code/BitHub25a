---
tags:
  - calcolo-numerico
  - interpolazione
slide: []
---
# Interpolazione polinomiale (approssimazione)
E' data una funzione $f:[a,b]\to \mathbb{R}$ di cui sono noti i valori $f(x_{0}),f(x_{1}),\dots,f(x_{n})$ in $n + 1$ punti distinti $x_{0},x_{1},\dots,x_{n}\in[a,b]$.
Si sceglie una classe $C$ di funzioni definite su $[a,b]$ a valori in $\mathbb{R}$ e si vuole approssimare la funzione $f(x)$ con una funzione $p:[a,b]\to \mathbb{R}$ che appartiene a $C$ e che soddisfa la seguente proprietà:
$$p(x_{i})=f(x_{i})\quad \forall i=0,1,\dots,n\qquad(*)$$
cioè che nei punti $x_{0},x_{1},\dots,x_{n}$ assume gli stessi valori di $f$.
Una scelta opportuna per la classe $C$ è quella di prendere lo spazio vettoriale (reale) dei polinomi di grado $\leq n$:$$C=\mathbb{R}_{n}[x]=\{a_{0}+a_{1}x+a_{2}x^2+\dots+a_{n}x^n:a_{0},a_{1},\dots,a_{n}\in \mathbb{R}\}$$
scelta opportuna perché i polinomi sono funzioni facili da valutare in un punto (bastano somme, prodotti e potenze, niente funzioni trascendenti).
Con questa scelta di $C$ si può dimostrare che $\exists! p(x)\in \mathbb{R}_{n}[x]$ che soddisfa la $(*)$: il problema di interpolazione è quindi ben posto (la soluzione esiste ed è unica). Questo fatto è conseguenza del teorema seguente.
## Teorema
Siano $(x_{0},y_{0}),(x_{1},y_{1}),\dots,(x_{n},y_{n})\in \mathbb{R}^2$ tali che $x_{0},x_{1},\dots,x_{n}$ sono tutti distinti. Allora $\exists!\ p(x)\in \mathbb{R}_{n}[x]$ t.c. $$p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n\qquad(**)$$
Applicando il teorema con $y_{i}=f(x_{i})\ \forall i=0,\dots,n$ si ottiene l'asserto precedente.
Le $y_{i}$ possono anche coincidere tra loro, devono essere distinti solo i nodi $x_{i}$ (che non devono nemmeno essere ordinati).
![[Pasted image 20251007153144.png]]

Illustrazione del teorema nel caso $n=3$: $\exists! p(x)\in \mathbb{R}_{3}[x]$ t.c. $p(x_{0})=y_{0},p(x_{1})=y_{1},p(x_{2})=y_{2},p(x_{3})=y_{3}$
## Dimostrazione 1
Osserviamo che un generico polinomio $p(x)$ in $\mathbb{R}_{n}[x]$ 
$p(x)=a_{0}+a_{1}x+a_{2}x^2+\dots+a_{n}x^n$
soddisfa la proprietà $(**)$, cioè $p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n$,
se e solo se $$\begin{cases}
a_{0}+a_{1}x_{0}+a_{2}x_{0}^2+\dots+a_{n}x_{0}^n= y_{0} \\
a_{0}+a_{1}x_{1}+a_{2}x_{1}^2+\dots+a_{n}x_{1}^n= y_{1} \\
a_{0}+a_{1}x_{2}+a_{2}x_{2}^2+\dots+a_{n}x_{2}^n= y_{2} \\
\qquad\qquad\qquad\vdots \\
a_{0}+a_{1}x_{n}+a_{2}x_{n}^2+\dots+a_{n}x_{n}^n= y_{n}
\end{cases}$$
cioè se e solo se il suo vettore dei coefficienti $(a_{0},a_{1},\dots,a_{n})$ soddisfa questo sistema lineare, le cui incognite sono i coefficienti $a_{i}$ (nodi $x_{i}$ e valori $y_{i}$ sono dati noti). In forma matriciale:
$$\underbrace{\begin{pmatrix}
1 & x_{0} & x_{0}^2 & \dots  & x_{0}^n \\
1 & x_{1} & x_{1}^2 & \dots  & x_{1}^n \\
1 & x_{2} & x_{2}^2 & \dots  & x_{2}^n \\
\vdots & \vdots & \vdots & \ddots & \vdots\\
1 & x_{n} & x_{n}^2 & \dots  & x_{n}^n
\end{pmatrix}}_{V(x_{0},x_{1},\dots,x_{n})}
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
\end{pmatrix}\qquad(S)$$
La matrice $V(x_{0},x_{1},\dots,x_{n})$ si chiama **matrice di Vandermonde** sui nodi $x_{0},x_{1},\dots,x_{n}$.
Il teorema è vero se e solo se il sistema $(S)$ ha una e una sola soluzione, cioè se e solo se la matrice $V$ è invertibile, ovvero $\det V\neq 0$.
Noi ora dimostreremo che $V(x_{0},x_{1},\dots,x_{n})$ è invertibile perché $$\det(V(x_{0},x_{1},\dots,x_{n}))=\begin{cases}
1 & \text{se }n=0 \\
\displaystyle\prod_{\begin{array}{}
i,j=0 \\
j<i
\end{array}}^n(x_{i}-x_{j}) & \text{se }n\geq 1
\end{cases}\qquad(\text{£})$$
Nel caso $n\geq 1$ il prodotto, espanso, è
$$(x_{1}-x_{0})\cdot(x_{2}-x_{0})(x_{2}-x_{1})\cdot(x_{3}-x_{0})(x_{3}-x_{1})(x_{3}-x_{2})\cdot\ldots\cdot(x_{n}-x_{0})(x_{n}-x_{1})\cdot\ldots\cdot(x_{n}-x_{n-1})$$
(si fissa $i=1$ e $j$ assume solo il valore $0$, poi $i=2$ e $j=0,1$, e così via fino a $i=n$ con $j=0,\dots,n-1$).
Dunque $\det(V(x_{0},x_{1},\dots,x_{n}))\neq 0$ perché per ipotesi i nodi (così si chiamano le $x_{i}$ nell'interpolazione) $x_{0},x_{1},\dots,x_{n}$ sono tutti distinti, quindi nessuna differenza $x_{i}-x_{j}$ con $j<i$ è nulla.
**Conclusione 1.** Poiché $V(x_{0},x_{1},\dots,x_{n})$ è invertibile, il sistema lineare $(S)$ ha una e una sola soluzione, e tale soluzione è data da $$\begin{pmatrix}
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
\end{pmatrix}\qquad(C)$$
> [!info] Richiamo di algebra lineare
> La soluzione di $V\underline{a}=\underline{y}$ con $V$ invertibile è $\underline{a}=V^{-1}\underline{y}$: si moltiplicano entrambi i membri a sinistra per $V^{-1}$.

**Conclusione 2.** $\exists!\ p(x)\in \mathbb{R}_{n}[x]$ che soddisfa $(**)$ e tale polinomio $p(x)$ è precisamente quello che ha il vettore dei coefficienti $(a_{0},a_{1},\dots,a_{n})$ dato da $(C)$. La dimostrazione è quindi costruttiva.

Resta da dimostrare la $(\text{£})$.
## Dimostrazione della $(\text{£})$ per $n=3$
>Per $n=0$ la $(\text{£})$ è ovvia perché $V(x_{0})=[1]$ e $\det(V(x_{0}))=1$, mentre per $n\geq1$ la dimostrazione è identica a quella che facciamo per $n=3$.

Dimostro quindi che $$\det(V(x_{0},x_{1},x_{2},x_{3}))=(x_{1}-x_{0})\cdot(x_{2}-x_{0})(x_{2}-x_{1})\cdot(x_{3}-x_{0})(x_{3}-x_{2})(x_{3}-x_{1})$$
Per ogni $i=1,\dots,3$ definiamo $d_{i}=\det(V(x_{0},\dots,x_{i}))$ (il $3$ sta al posto di $n$, per mantenere la dimostrazione generale).
**Obiettivo**: calcolare $d_{3}$.
Si usa la proprietà dei determinanti per cui sommare a una riga o colonna un multiplo scalare di un'altra riga o colonna non cambia il determinante. Servirà a fare degli zeri.
$$d_{3}=\begin{vmatrix}
1 & x_{0} & x_{0}^2 & x_{0}^3 \\
1 & x_{1} & x_{1}^2 & x_{1}^3 \\
1 & x_{2} & x_{2}^2 & x_{2}^3 \\
1 & x_{3} & x_{3}^2 & x_{3}^3
\end{vmatrix}\overset{C_{4}\to C_{4}-x_{3}C_{3}}{=}\begin{vmatrix}
1 & x_{0} & x_{0}^2 & x_{0}^3-x_{0}^2x_{3} \\
1 & x_{1} & x_{1}^2 & x_{1}^3-x_{1}^2x_{3} \\
1 & x_{2} & x_{2}^2 & x_{2}^3-x_{2}^2x_{3} \\
1 & x_{3} & x_{3}^2 & 0
\end{vmatrix}$$
$$\overset{C_{3}\to C_{3}-x_{3}C_{2}}{=}\begin{vmatrix}
1 & x_{0} & x_{0}^2-x_{0}x_{3} & x_{0}^2(x_{0}-x_{3}) \\
1 & x_{1} & x_{1}^2-x_{1}x_{3} & x_{1}^2(x_{1}-x_{3}) \\
1 & x_{2} & x_{2}^2-x_{2}x_{3} & x_{2}^2(x_{2}-x_{3}) \\
1 & x_{3} & 0 & 0
\end{vmatrix}\overset{C_{2}\to C_{2}-x_{3}C_{1}}{=}\begin{vmatrix}
1 & x_{0}-x_{3} & x_{0}(x_{0}-x_{3}) & x_{0}^2(x_{0}-x_{3}) \\
1 & x_{1}-x_{3} & x_{1}(x_{1}-x_{3}) & x_{1}^2(x_{1}-x_{3}) \\
1 & x_{2}-x_{3} & x_{2}(x_{2}-x_{3}) & x_{2}^2(x_{2}-x_{3}) \\
1 & 0 & 0 & 0
\end{vmatrix}$$
Si sviluppa col metodo di Laplace lungo l'ultima riga (la riga $n+1$), che ha un solo elemento non nullo. Per la regola della scacchiera il segno davanti all'$1$ è $(-1)^{3}$, in generale $(-1)^{n}$: si parte da $(-1)^0$ nella prima riga e si arriva a $(-1)^n$ nella riga $n+1$. Il sottodeterminante si ottiene cancellando l'ultima riga e la prima colonna:
$$d_{3}=(-1)^3\begin{vmatrix}
x_{0}-x_{3} & x_{0}(x_{0}-x_{3}) & x_{0}^2(x_{0}-x_{3}) \\
x_{1}-x_{3} & x_{1}(x_{1}-x_{3}) & x_{1}^2(x_{1}-x_{3}) \\
x_{2}-x_{3} & x_{2}(x_{2}-x_{3}) & x_{2}^2(x_{2}-x_{3})
\end{vmatrix}$$
Ogni riga ha un fattore comune ($x_{0}-x_{3}$ nella prima, $x_{1}-x_{3}$ nella seconda, $x_{2}-x_{3}$ nella terza), e un fattore costante che moltiplica un'intera riga si può portare fuori dal determinante:
$$d_{3}=(-1)^3(x_{0}-x_{3})(x_{1}-x_{3})(x_{2}-x_{3})\begin{vmatrix}
1 & x_{0} & x_{0}^2 \\
1 & x_{1} & x_{1}^2 \\
1 & x_{2} & x_{2}^2
\end{vmatrix}$$
Si scarica un $-1$ su ciascuno dei tre fattori (in generale su ciascuno degli $n$ fattori, così da assorbire $(-1)^n$), e il determinante rimasto è proprio $d_{2}$:
$$d_{3}=(x_{3}-x_{0})(x_{3}-x_{1})(x_{3}-x_{2})\,d_{2}$$
Per ricorrenza, ripetendo gli stessi passaggi, $d_{2}$ si esprime in termini di $d_{1}$ e così via, e $d_{1}=x_{1}-x_{0}$ si prende come caso base:
$$d_{3}=(x_{3}-x_{0})(x_{3}-x_{1})(x_{3}-x_{2})\cdot d_{2}=(x_{3}-x_{0})(x_{3}-x_{1})(x_{3}-x_{2})\cdot(x_{2}-x_{0})(x_{2}-x_{1})\cdot d_{1}$$
$$=(x_{3}-x_{0})(x_{3}-x_{1})(x_{3}-x_{2})\cdot(x_{2}-x_{0})(x_{2}-x_{1})\cdot(x_{1}-x_{0})$$
che coincide con il prodotto della $(\text{£})$ (scritto in ordine inverso). $\blacksquare$
