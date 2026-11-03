---
tags:
  - calcolo-numerico
  - interpolazione
  - errore-di-interpolazione
  - differenze-divise
slide: []
---
# Interpolazione polinomiale
## Esistenza e unicità del polinomio d'interpolazione
Lezione 1 (06/10/2026).
E' data una funzione $f:[a,b]\to \mathbb{R}$ di cui sono noti i valori $f(x_{0}),f(x_{1}),\dots,f(x_{n})$ in $n + 1$ punti distinti $x_{0},x_{1},\dots,x_{n}\in[a,b]$.
Si sceglie una classe $C$ di funzioni definite su $[a,b]$ a valori in $\mathbb{R}$ e si vuole approssimare la funzione $f(x)$ con una funzione $p:[a,b]\to \mathbb{R}$ che appartiene a $C$ e che soddisfa la seguente proprietà:
$$p(x_{i})=f(x_{i})\quad \forall i=0,1,\dots,n\qquad(*)$$
cioè che nei punti $x_{0},x_{1},\dots,x_{n}$ assume gli stessi valori di $f$.
Una scelta opportuna per la classe $C$ è quella di prendere lo spazio vettoriale (reale) dei polinomi di grado $\leq n$:$$C=\mathbb{R}_{n}[x]=\{a_{0}+a_{1}x+a_{2}x^2+\dots+a_{n}x^n:a_{0},a_{1},\dots,a_{n}\in \mathbb{R}\}$$
scelta opportuna perché i polinomi sono funzioni facili da valutare in un punto (bastano somme, prodotti e potenze, niente funzioni trascendenti).
Con questa scelta di $C$ si può dimostrare che $\exists! p(x)\in \mathbb{R}_{n}[x]$ che soddisfa la $(*)$: il problema di interpolazione è quindi ben posto (la soluzione esiste ed è unica). Questo fatto è conseguenza del teorema seguente.
### Teorema
Siano $(x_{0},y_{0}),(x_{1},y_{1}),\dots,(x_{n},y_{n})\in \mathbb{R}^2$ tali che $x_{0},x_{1},\dots,x_{n}$ sono tutti distinti. Allora $\exists!\ p(x)\in \mathbb{R}_{n}[x]$ t.c. $$p(x_{i})=y_{i}\quad\forall i=0,1,\dots,n\qquad(**)$$
Applicando il teorema con $y_{i}=f(x_{i})\ \forall i=0,\dots,n$ si ottiene l'asserto precedente.
Le $y_{i}$ possono anche coincidere tra loro, devono essere distinti solo i nodi $x_{i}$ (che non devono nemmeno essere ordinati).
![[Pasted image 20251007153144.png]]

Illustrazione del teorema nel caso $n=3$: $\exists! p(x)\in \mathbb{R}_{3}[x]$ t.c. $p(x_{0})=y_{0},p(x_{1})=y_{1},p(x_{2})=y_{2},p(x_{3})=y_{3}$
### Dimostrazione 1
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
### Dimostrazione della $(\text{£})$ per $n=3$
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
## Polinomi di Lagrange
Lezione 2 (08/10/2026).
Si riprende il teorema di esistenza e unicità del polinomio interpolante visto in [[01 - Interpolazione polinomiale#Esistenza e unicità del polinomio d'interpolazione#Teorema]], di cui qui si dà una seconda dimostrazione. La prima, tramite la matrice di Vandermonde, è in [[01 - Interpolazione polinomiale#Dimostrazione 1]].
> [!quote] Teorema
> Siano $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ tali che $x_0,x_1,\dots,x_n$ sono distinti. Allora $\exists!\ p(x)\in\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\quad\forall i=0,\dots,n$.
### Dimostrazione 2
#### Polinomi di Lagrange
$\forall j=0,\dots,n$ si definisce
$$L_j(x)=\prod_{\substack{k=0\\k\neq j}}^{n}\frac{x-x_k}{x_j-x_k}=\frac{(x-x_0)\cdots(x-x_{j-1})(x-x_{j+1})\cdots(x-x_n)}{(x_j-x_0)\cdots(x_j-x_{j-1})(x_j-x_{j+1})\cdots(x_j-x_n)}$$
- Si salta il fattore $k=j$ (a numeratore e a denominatore): per $k=j$ il denominatore si annullerebbe.
- Ce n'è uno per ogni nodo: in totale $n+1$ polinomi.
- Il denominatore è una costante (prodotto di differenze di nodi); $x$ compare solo a numeratore, che è un prodotto di $n$ fattori di primo grado. Il termine di grado massimo si ottiene scegliendo $x$ in ogni fattore, quindi $x^n$.
- Gli $n+1$ polinomi $L_0(x),\dots,L_n(x)$ hanno tutti grado $n$, quindi appartengono a $\mathbb{R}_n[x]$.

Si dimostra che $L_0(x),\dots,L_n(x)$ sono una base di $\mathbb{R}_n[x]$.
#### Promemoria sulle basi di $\mathbb{R}_n[x]$
Una base di $\mathbb{R}_n[x]$ è un insieme di polinomi $\{v_1(x),\dots,v_r(x)\}$ che:
- sono **linearmente indipendenti**: se $\alpha_1v_1(x)+\dots+\alpha_rv_r(x)=0$ (polinomio nullo, cioè nullo per ogni $x$), allora $\alpha_1=\dots=\alpha_r=0$;
- **generano** tutto $\mathbb{R}_n[x]$: $\forall v(x)\in\mathbb{R}_n[x]\ \exists\alpha_1,\dots,\alpha_r\in\mathbb{R}$ tali che $v(x)=\alpha_1v_1(x)+\dots+\alpha_rv_r(x)$.

La base canonica di $\mathbb{R}_n[x]$ è data dai monomi $1,x,x^2,x^3,\dots,x^n$, che sono $n+1$. Tutte le basi di uno spazio vettoriale hanno lo stesso numero di elementi (la **dimensione**): quindi tutte le basi di $\mathbb{R}_n[x]$ hanno $n+1$ elementi e $n+1=\dim(\mathbb{R}_n[x])$.
> [!info] Indipendenza dei monomi
> Che i monomi generino $\mathbb{R}_n[x]$ è ovvio (i polinomi sono per definizione loro combinazioni lineari); la loro indipendenza lineare non è stata dimostrata a lezione, ma il docente consiglia di andare a vedere la dimostrazione.
>
> Inoltre, se in uno spazio di dimensione $n+1$ si hanno $n+1$ elementi, per dimostrare che sono una base basta dimostrare *una sola* tra indipendenza lineare e generazione dello spazio (l'altra segue).
#### Proprietà chiave dei polinomi di Lagrange
Gli $n+1$ polinomi di Lagrange sono nel numero giusto per essere una base, quindi basta dimostrare che sono linearmente indipendenti. Si mette in luce la proprietà $\forall i,j=0,\dots,n$:
$$L_j(x_i)=\begin{cases}1 & \text{se } i=j\\0 & \text{se } i\neq j\end{cases}\qquad(*)$$
- Se $i=j$ numeratore e denominatore coincidono, quindi $L_j(x_j)=1$.
- Se $i\neq j$ il numeratore contiene il fattore $x_i-x_i=0$, quindi $L_j(x_i)=0$.

I polinomi sono costruiti apposta perché valga la $(*)$, da cui discende tutto il resto.
#### Indipendenza lineare e base
Se $\alpha_0L_0(x)+\alpha_1L_1(x)+\dots+\alpha_nL_n(x)=0\quad\forall x\in\mathbb{R}$, allora in particolare, valutando nei nodi,
$$\alpha_0L_0(x_i)+\alpha_1L_1(x_i)+\dots+\alpha_nL_n(x_i)=0\qquad\forall i=0,\dots,n$$
Per la $(*)$ sopravvive solo il termine $i$-esimo:
$$\alpha_0L_0(x_i)+\dots+\alpha_nL_n(x_i)=\alpha_iL_i(x_i)=\alpha_i$$
Quindi $\alpha_i=0\ \forall i=0,\dots,n$: $L_0(x),\dots,L_n(x)$ sono linearmente indipendenti e, essendo $n+1$, sono una base di $\mathbb{R}_n[x]$.
#### Esistenza
Si definisce
$$p(x)=y_0L_0(x)+y_1L_1(x)+\dots+y_nL_n(x)\in\mathbb{R}_n[x]$$
(appartiene a $\mathbb{R}_n[x]$ perché combinazione lineare di elementi della base). $\forall i=0,\dots,n$, per la $(*)$:
$$p(x_i)=y_0L_0(x_i)+y_1L_1(x_i)+\dots+y_nL_n(x_i)=y_iL_i(x_i)=y_i$$
#### Unicità
Si suppone che $q(x)$ sia un altro polinomio **in $\mathbb{R}_n[x]$** con $q(x_i)=y_i\ \forall i=0,\dots,n$. Poiché $q(x)\in\mathbb{R}_n[x]$ e $L_0(x),\dots,L_n(x)$ sono una base, $\exists\beta_0,\dots,\beta_n\in\mathbb{R}$ tali che
$$q(x)=\beta_0L_0(x)+\beta_1L_1(x)+\dots+\beta_nL_n(x)$$
$\forall i=0,\dots,n$, usando di nuovo la $(*)$:
$$y_i=q(x_i)=\beta_0L_0(x_i)+\dots+\beta_nL_n(x_i)=\beta_iL_i(x_i)=\beta_i$$
Quindi $\beta_i=y_i$ e
$$q(x)=y_0L_0(x)+y_1L_1(x)+\dots+y_nL_n(x)=p(x)$$
Dunque $p(x)$ è l'unico polinomio in $\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\ \forall i=0,\dots,n$. $\blacksquare$
### Polinomio d'interpolazione
> [!quote] Definizione (polinomio d'interpolazione)
> Siano $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ con $x_0,x_1,\dots,x_n$ distinti. L'unico polinomio $p(x)\in\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\ \forall i=0,\dots,n$ si chiama **polinomio d'interpolazione dei dati** $(x_0,y_0),\dots,(x_n,y_n)$, o anche **polinomio d'interpolazione dei valori** $y_0,\dots,y_n$ **sui nodi** $x_0,\dots,x_n$.

> [!quote] Definizione (interpolazione di una funzione)
> Se gli $y_i$ sono i valori nei punti $x_i$ di una funzione $f:[a,b]\to\mathbb{R}$, cioè se $y_i=f(x_i)\ \forall i=0,\dots,n$, allora $p(x)$ si chiama anche **polinomio d'interpolazione della funzione** $f(x)$ **sui nodi** $x_0,\dots,x_n$.

> [!warning] Attenzione a "$\mathbb{R}_n[x]$"
> Il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,\dots,x_n$ è *quell'unico polinomio in $\mathbb{R}_n[x]$* tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$. Senza la specifica "in $\mathbb{R}_n[x]$", cioè di grado $\leq n$, l'unicità cade: tra tutti i polinomi ce ne sono infiniti che passano per quei punti.

> [!question] Domanda tipica d'esame
> Che cos'è il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0,\dots,x_n$? Il docente la ripete spesso all'orale perché mette in difficoltà: la risposta richiede di *rielaborare* la definizione, ed è quella dell'avviso qui sopra.
#### Forma canonica e forma di Lagrange
Il teorema è **costruttivo**: le due dimostrazioni costruiscono $p(x)$ in due modi.
- La prima dimostrazione ([[01 - Interpolazione polinomiale#Dimostrazione 1]]) dà la **forma canonica**
$$p(x)=a_0+a_1x+a_2x^2+\dots+a_nx^n\qquad\text{con}\qquad\begin{pmatrix}a_0\\a_1\\\vdots\\a_n\end{pmatrix}=[V(x_0,x_1,\dots,x_n)]^{-1}\begin{pmatrix}y_0\\y_1\\\vdots\\y_n\end{pmatrix}$$
cioè l'espressione di $p(x)$ come combinazione lineare degli elementi della base canonica $1,x,x^2,\dots,x^n$. I coefficienti sono la soluzione di un sistema lineare con la matrice di Vandermonde.
- La seconda dimostrazione dà la **forma di Lagrange**
$$p(x)=y_0L_0(x)+y_1L_1(x)+\dots+y_nL_n(x)$$
cioè l'espressione di $p(x)$ come combinazione lineare dei **polinomi di Lagrange relativi ai nodi** $x_0,\dots,x_n$
$$L_j(x)=\prod_{\substack{k=0\\k\neq j}}^{n}\frac{x-x_k}{x_j-x_k}\qquad\forall j=0,\dots,n$$
I coefficienti sono direttamente i valori $y_i$: la forma di Lagrange si scrive senza fatica, senza risolvere alcun sistema.

Per questo, in pratica, si parte dalla forma di Lagrange (o da quella di Newton, che si vedrà più avanti) e, se serve la forma canonica, la si ottiene come sottoprodotto sviluppando i calcoli e raccogliendo i coefficienti delle potenze di $x$: così si trova il vettore dei coefficienti canonici senza risolvere il sistema con $V$.
### Esempio: $\sin x$ nei nodi $0,\pi/6,\pi/4$
> [!example] Esempio
> Della funzione $\sin(x)$ sono noti i valori nei tre punti $x_0=0,\ x_1=\frac{\pi}{6},\ x_2=\frac{\pi}{4}$:
> $$\sin(x_0)=0,\qquad\sin(x_1)=\frac12,\qquad\sin(x_2)=\frac{\sqrt2}{2}$$
> Scrivere in forma canonica e in forma di Lagrange il polinomio d'interpolazione $p(x)$ di $\sin(x)$ sui nodi $x_0,x_1,x_2$.

Il polinomio cercato è l'unico $p(x)\in\mathbb{R}_2[x]$ tale che $p(0)=0$, $p(\pi/6)=\frac12$, $p(\pi/4)=\frac{\sqrt2}{2}$ (con $n=2$: tre nodi).
#### Forma di Lagrange
$$p(x)=\sin(x_0)L_0(x)+\sin(x_1)L_1(x)+\sin(x_2)L_2(x)$$
$$=\sin(x_0)\frac{(x-x_1)(x-x_2)}{(x_0-x_1)(x_0-x_2)}+\sin(x_1)\frac{(x-x_0)(x-x_2)}{(x_1-x_0)(x_1-x_2)}+\sin(x_2)\frac{(x-x_0)(x-x_1)}{(x_2-x_0)(x_2-x_1)}$$
Il primo termine si elimina, perché $\sin(x_0)=0$. Sostituendo i nodi:
$$p(x)=\frac12\cdot\frac{x\left(x-\frac{\pi}{4}\right)}{\frac{\pi}{6}\left(\frac{\pi}{6}-\frac{\pi}{4}\right)}+\frac{\sqrt2}{2}\cdot\frac{x\left(x-\frac{\pi}{6}\right)}{\frac{\pi}{4}\left(\frac{\pi}{4}-\frac{\pi}{6}\right)}$$
Poiché $\frac{\pi}{6}\left(\frac{\pi}{6}-\frac{\pi}{4}\right)=-\frac{\pi^2}{72}$ e $\frac{\pi}{4}\left(\frac{\pi}{4}-\frac{\pi}{6}\right)=\frac{\pi^2}{48}$:
$$p(x)=\frac12\cdot\frac{x\left(x-\frac{\pi}{4}\right)}{-\frac{\pi^2}{72}}+\frac{\sqrt2}{2}\cdot\frac{x\left(x-\frac{\pi}{6}\right)}{\frac{\pi^2}{48}}$$
> [!warning] Forma di Lagrange all'esame
> Se si chiede la forma di Lagrange, non si deve andare avanti a semplificare: devono restare **in evidenza i coefficienti** ($\frac12$ e $\frac{\sqrt2}{2}$) davanti ai polinomi di Lagrange. Portare il coefficiente dentro (per esempio moltiplicando $\frac12$ per $-\frac{\pi^2}{72}$) distrugge la forma di Lagrange. Si può semplificare solo il polinomio $L_j$ in sé. Il termine con $\sin(x_0)=0$ si può omettere: si capisce che il suo coefficiente è nullo.
#### Forma canonica
Una volta in forma di Lagrange ci si può staccare da essa e fare tutti i calcoli che si vogliono: si ribalta il denominatore, si sviluppano i prodotti e si raccolgono le potenze di $x$.
$$p(x)=-\frac{36}{\pi^2}\left(x^2-\frac{\pi}{4}x\right)+\frac{24\sqrt2}{\pi^2}\left(x^2-\frac{\pi}{6}x\right)=\frac{24\sqrt2-36}{\pi^2}x^2+\frac{9-4\sqrt2}{\pi}x$$
Il coefficiente di $x$ si ottiene da $\frac{36}{4\pi}-\frac{24\sqrt2}{6\pi}=\frac{9}{\pi}-\frac{4\sqrt2}{\pi}$. I coefficienti della forma canonica sono quindi
$$a_0=0\qquad a_1=\frac{9-4\sqrt2}{\pi}\qquad a_2=\frac{24\sqrt2-36}{\pi^2}$$
Il termine noto manca perché $x_0=0$ è un nodo e deve valere $p(0)=\sin(0)=0$. Si è ottenuto il vettore dei coefficienti canonici senza risolvere il sistema con la matrice di Vandermonde.
> [!info] Calcolatrice e angoli
> In matematica gli angoli si misurano sempre in **radianti**: non si scrive $\sin(30°)$ ma $\sin\frac{\pi}{6}$. Se si usa la calcolatrice scientifica, impostarla sui radianti (con i gradi si ottengono risultati sbagliati).
#### Grafico e qualità dell'approssimazione
Il grafico di $\sin x$ (blu) con i tre punti d'interpolazione e della parabola $p(x)$ (rossa), che è un polinomio di $\mathbb{R}_2[x]$, mostra che:
- vicino ai nodi $p(x)$ approssima bene $\sin x$;
- allontanandosi dai nodi l'approssimazione peggiora rapidamente.

L'interpolazione approssima la funzione nell'intervallo che contiene i nodi (qui $[0,\pi/4]$): si può uscire dall'intervallo ma di poco, altrimenti diventa troppo rischioso. Per approssimare meglio si aggiungono altri nodi. Se i nodi sono troppo lontani tra loro, in mezzo le cose possono andare male.

Per stimare l'errore commesso in un punto $x$, per esempio nell'approssimare $\sin\frac14$ con $p\left(\frac14\right)$, esiste una formula (errore d'interpolazione) che permette di maggiorare $\left|p\left(\frac14\right)-\sin\frac14\right|$ con una quantità del tipo $10^{-7}$: la si vedrà alla lezione successiva.
## Errore d'interpolazione
Lezione 3 (13/10/2026).
Nella lezione precedente si è costruito il polinomio d'interpolazione ([[01 - Interpolazione polinomiale#Polinomio d'interpolazione]]) e si è visto sul grafico di $\sin x$ che approssima bene la funzione vicino ai nodi e male lontano da essi ([[01 - Interpolazione polinomiale#Grafico e qualità dell'approssimazione]]). Qui si risponde alla domanda rimasta aperta: quanto vale l'errore che si commette approssimando $f(x)$ con il suo polinomio d'interpolazione $p(x)$? La differenza $f(x)-p(x)$ si chiama **errore** o **resto** dell'interpolazione polinomiale.
### Funzioni di classe $C^{n+1}$
> [!quote] Definizione (classe $C^{n+1}[a,b]$)
> $$C^{n+1}[a,b]=\{g:[a,b]\to\mathbb{R}\ \mid\ g \text{ è derivabile } n+1 \text{ volte su } [a,b] \text{ e le derivate } g',g'',\dots,g^{(n+1)} \text{ sono funzioni continue su } [a,b]\}$$

- Non basta che le derivate esistano: le funzioni derivate, fino alla $(n+1)$-esima inclusa, devono essere **continue**. Va bene anche se $g$ ha derivate di ordine superiore: l'importante è che ci siano almeno quelle fino a $n+1$.
- Una funzione derivabile è continua. Quindi se $g^{(n+1)}$ esiste ed è continua, $g^{(n)}$ è derivabile e dunque continua, e così via a ritroso fino a $g$: basterebbe chiedere che sia continua l'ultima derivata.
- I polinomi sono di classe $C^\infty$: si possono derivare infinite volte, con tutte le derivate continue (da un certo ordine in poi sono nulle).
### Teorema
> [!quote] Teorema (errore d'interpolazione)
> Sia $f:[a,b]\to\mathbb{R}$ una funzione di classe $C^{n+1}[a,b]$ e sia $p(x)$ il polinomio d'interpolazione di $f(x)$ sugli $n+1$ nodi distinti $x_0,x_1,\dots,x_n\in[a,b]$. Allora $\forall x\in[a,b]\ \exists\,\xi=\xi(x)\in(a,b)$ tale che
> $$f(x)-p(x)=\frac{f^{(n+1)}(\xi)}{(n+1)!}(x-x_0)(x-x_1)\cdots(x-x_n)\qquad(\star)$$

- $p(x)$ è **l'unico polinomio di grado $\leq n$** tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$: va ripetuto ogni volta, perché all'orale è la domanda su cui si sbaglia di più (vedi [[01 - Interpolazione polinomiale#Polinomio d'interpolazione]]).
- La notazione $\xi(x)$ ricorda che il punto $\xi$ **dipende da $x$**: per ogni $x$ esiste il suo $\xi$ che fa valere la $(\star)$, ma cambiando $x$ cambia anche $\xi$. Non c'è un unico $\xi$ che va bene per tutti gli $x$.
- La derivata $f^{(n+1)}$ esiste ed è continua perché $f\in C^{n+1}[a,b]$.
- $\xi$ sta nell'intervallo **aperto** $(a,b)$.
### Dimostrazione
Sia $x\in[a,b]$ fissato. Bisogna produrre un $\xi\in(a,b)$ che faccia valere la $(\star)$.
#### Caso 1: $x$ coincide con uno dei nodi
In tal caso la formula $(\star)$ vale con un **qualsiasi** $\xi\in(a,b)$:
- il membro di sinistra è nullo per definizione di polinomio d'interpolazione, perché $p(x_i)=f(x_i)$;
- il membro di destra è nullo a prescindere dalla scelta di $\xi$, perché il fattore $(x-x_0)(x-x_1)\cdots(x-x_n)$ è zero.

Si ottiene $0=0$ per ogni $\xi$. Attenzione però: $\xi$ deve comunque stare in $(a,b)$ (non si può prendere $\xi=0$ se $0\notin(a,b)$).
#### Caso 2: $x$ non coincide con uno dei nodi
Si definiscono le seguenti **funzioni ausiliarie**:
$$\pi(y)=(y-x_0)(y-x_1)\cdots(y-x_n)$$
$$r(y)=f(y)-p(y)$$
$$z(y)=r(y)-\frac{r(x)}{\pi(x)}\,\pi(y)\ :\ [a,b]\to\mathbb{R}$$
dove $\pi(x)\neq 0$ perché $x$ non è uno dei nodi.

> [!info] Perché la variabile è $y$ e non $x$
> $x$ è un punto **fissato** e non si può più usare come variabile per definire una funzione: le funzioni ausiliarie si definiscono in una variabile diversa ($y$, ma andrebbe bene anche $t$ o $u$). In $z(y)$ la quantità $\frac{r(x)}{\pi(x)}$ è una **costante**: $r(x)=f(x)-p(x)$ è proprio l'errore nel punto fissato $x$. Si vede anche perché il caso 1 andava trattato a parte: se $x$ fosse un nodo, $\pi(x)=0$ e $z$ non si potrebbe definire.

Proprietà di $z$:
- **$z$ è una funzione di classe $C^{n+1}[a,b]$, come $f$**. $\pi(y)$ e $p(y)$ sono polinomi, quindi $C^\infty$, e non creano problemi: $z$ eredita la classe di regolarità di $f$.
- **$z$ si annulla in almeno $n+2$ punti di $[a,b]$**: nei nodi $x_0,x_1,\dots,x_n$ e nel punto $x$. Infatti
$$z(x_0)=\underbrace{r(x_0)}_{=0\ \text{per def. di } p(y)}-\frac{r(x)}{\pi(x)}\underbrace{\pi(x_0)}_{=0}=0$$
e similmente $z(x_i)=0\ \forall i=0,\dots,n$; inoltre
$$z(x)=r(x)-\frac{r(x)}{\pi(x)}\pi(x)=0$$
La funzione $z$ è costruita apposta perché si annulli nei nodi e anche in $x$. Nella sostituzione si rimpiazza solo la variabile $y$, non la $x$, che è fissata.

![[resto-interpolazione-funzione-z.png]]

Esempio di possibile funzione $z$ nel caso $n=2$: tre nodi più il punto $x$, quindi $n+2=4$ zeri. Il grafico è liscio perché $z$ è derivabile $n+1$ volte.
#### Teorema di Rolle
> [!quote] Teorema (Rolle)
> Sia $g:[a,b]\to\mathbb{R}$ continua su $[a,b]$ e derivabile su $(a,b)$, e supponiamo che $g(a)=g(b)$. Allora $\exists\,c\in(a,b)$ tale che $g'(c)=0$.

Geometricamente: c'è un punto interno in cui la retta tangente al grafico è orizzontale.
#### Applicazione ripetuta di Rolle
Si applica Rolle su ciascun intervallo compreso tra due zeri consecutivi di $z$. Tra due zeri consecutivi c'è almeno uno zero della derivata, quindi a ogni derivazione si perde al più uno zero:
$$\begin{aligned}
z' &\ \text{si annulla in almeno } n+1 \text{ punti di } (a,b)\\
z'' &\ \text{si annulla in almeno } n \text{ punti di } (a,b)\\
z''' &\ \text{si annulla in almeno } n-1 \text{ punti di } (a,b)\\
&\ \ \vdots\\
z^{(n+1)} &\ \text{si annulla in almeno } 1 \text{ punto di } (a,b)\text{, che chiamiamo } \xi
\end{aligned}$$
- Già dalla prima derivata i punti sono nell'intervallo **aperto** $(a,b)$: Rolle dà sempre un punto interno, anche se qualche nodo coincide con $a$ o con $b$.
- Per trovare l'ordine dell'ultima derivata conviene cercare una "costante del moto": la somma tra l'ordine della derivata e il numero di zeri garantiti è sempre $n+2$. Quando gli zeri sono $1$, l'ordine è $n+1$.
#### Calcolo di $z^{(n+1)}$
Per la linearità della derivata (la costante $\frac{r(x)}{\pi(x)}$ resta dov'è):
$$z^{(n+1)}(y)=r^{(n+1)}(y)-\frac{r(x)}{\pi(x)}\,\pi^{(n+1)}(y)=f^{(n+1)}(y)-p^{(n+1)}(y)-\frac{r(x)}{\pi(x)}\,\pi^{(n+1)}(y)$$
- **$p^{(n+1)}(y)=0$**. $p(y)=a_0+a_1y+\dots+a_ny^n$ ha grado $\leq n$; a ogni derivazione gli esponenti scendono di uno:
$$p'(y)=a_1+\dots+na_ny^{n-1},\qquad\dots,\qquad p^{(n)}(y)=n!\,a_n,\qquad p^{(n+1)}(y)=0$$
È stato derivato troppe volte.
- **$\pi^{(n+1)}(y)=(n+1)!$**. $\pi$ ha $n+1$ fattori, quindi grado $n+1$:
$$\pi(y)=(y-x_0)(y-x_1)\cdots(y-x_n)=a_{n+1}y^{n+1}+q(y),\qquad q(y)\in\mathbb{R}_n[y]$$
$q$ muore con la derivata $(n+1)$-esima, e come per $p$ si ottiene $\pi^{(n+1)}(y)=(n+1)!\,a_{n+1}$. Il termine di grado massimo $y^{n+1}$ si ottiene in un solo modo: prendendo $y$ da **tutti** i fattori (se da un fattore si prende $-x_i$ il grado scende). Quindi $a_{n+1}=1$. Per convincersene basta provare con $n=1$: in $(y-x_0)(y-x_1)$ l'unico prodotto che dà $y^2$ è $y\cdot y$.

Quindi
$$z^{(n+1)}(y)=f^{(n+1)}(y)-\frac{r(x)}{\pi(x)}\,(n+1)!$$
#### Conclusione
Valutando nel punto $\xi$ in cui $z^{(n+1)}$ si annulla, e dimenticando $z$ che era solo una funzione ausiliaria:
$$0=z^{(n+1)}(\xi)=f^{(n+1)}(\xi)-\frac{r(x)}{\pi(x)}\,(n+1)!$$
$$\iff\quad\frac{r(x)}{\pi(x)}\,(n+1)!=f^{(n+1)}(\xi)$$
$$\iff\quad\underbrace{r(x)}_{f(x)-p(x)}=\frac{f^{(n+1)}(\xi)}{(n+1)!}\,\pi(x)$$
che è la $(\star)$, perché $\pi(x)=(x-x_0)(x-x_1)\cdots(x-x_n)$. $\blacksquare$

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il teorema sull'errore d'interpolazione. Traccia: caso in cui $x$ è un nodo; funzioni ausiliarie $\pi$, $r$, $z$ e perché $z$ ha almeno $n+2$ zeri; applicazione ripetuta di Rolle fino a $z^{(n+1)}$; calcolo di $p^{(n+1)}=0$ e $\pi^{(n+1)}=(n+1)!$.
### Come si usa il teorema
#### Scelta dell'intervallo $[a,b]$
Il teorema garantisce che $\xi$ sta in $(a,b)$: più piccolo è l'intervallo, più precisa è l'informazione su $\xi$ e quindi migliore la stima. Conviene applicarlo sul **più piccolo intervallo che contiene i nodi e il punto $x$** in cui si vuole stimare l'errore. Non si può barare: i nodi devono stare in $[a,b]$ per ipotesi, e anche $x$, se si vuole una tesi su $x$.
#### Moduli
Si usa spesso la proprietà del modulo di un prodotto: $\forall\alpha,\beta\in\mathbb{C}$
$$|\alpha\beta|=|\alpha|\cdot|\beta|$$
e più in generale $\forall\alpha_1,\dots,\alpha_k\in\mathbb{C}$, $|\alpha_1\alpha_2\cdots\alpha_k|=|\alpha_1|\cdot|\alpha_2|\cdots|\alpha_k|$. Quando si può (perché il segno di un fattore è noto), conviene **togliere i moduli**.
### Esempio 1: $\sin t$ sui nodi $0,\pi/6,\pi/4$
> [!example] Esempio
> Fissiamo un punto $t\in[0,1]$. Stimare l'errore che si commette approssimando $\sin(t)$ con $p(t)$, dove $p(x)$ è il polinomio d'interpolazione della funzione $\sin(x)$ sui nodi $x_0=0,\ x_1=\frac{\pi}{6},\ x_2=\frac{\pi}{4}$.

È il polinomio calcolato in [[01 - Interpolazione polinomiale#Forma di Lagrange]]. Si applica il teorema con $f(x)=\sin(x)\in C^\infty(\mathbb{R})$, $n=2$, $x=t$ e $[a,b]=[0,1]$, il più piccolo intervallo che contiene i nodi $x_0,x_1,x_2$ e il punto $t$ (si noti che $\frac{\pi}{4}<1$). Dal teorema si ha
$$|\sin(t)-p(t)|=\left|\frac{f'''(\xi)}{3!}(t-x_0)(t-x_1)(t-x_2)\right|\qquad(\xi\in(0,1))$$
Le derivate del seno sono cicliche con periodo 4: $f'=\cos$, $f''=-\sin$, $f'''=-\cos$. Quindi
$$|\sin(t)-p(t)|=\left|\frac{-\cos(\xi)}{6}\,t\left(t-\frac{\pi}{6}\right)\left(t-\frac{\pi}{4}\right)\right|$$
#### Stima grezza
Poiché $\xi\in(0,1)$ e $1<\frac{\pi}{2}\approx 1{,}57$, l'angolo $\xi$ (in radianti) sta tra $0$ e $\frac{\pi}{2}$ e $\cos\xi>0$: il modulo si mangia il segno meno. Separando tutti i fattori:
$$|\sin(t)-p(t)|=\frac{\cos\xi}{6}\,|t|\,\left|t-\frac{\pi}{6}\right|\,\left|t-\frac{\pi}{4}\right|$$
Ciascun fattore si maggiora per conto suo, sapendo che $t\in[0,1]$:
- $\cos\xi\leq 1$;
- $|t|\leq 1$ (massimo in $t=1$);
- $\left|t-\frac{\pi}{6}\right|$ ha il massimo in uno dei due estremi: vale $\frac{\pi}{6}$ in $0$ e $1-\frac{\pi}{6}$ in $1$. Poiché $\frac{\pi}{6}>\frac12$, vince $\frac{\pi}{6}$;
- $\left|t-\frac{\pi}{4}\right|$, allo stesso modo, ha il massimo $\frac{\pi}{4}$ in $0$.

![[resto-interpolazione-moduli-sin.png]]

Grafici di $|t|$ (blu), $\left|t-\frac{\pi}{6}\right|$ (rosso) e $\left|t-\frac{\pi}{4}\right|$ (verde): il grafico del modulo si ottiene ribaltando la parte negativa rispetto all'asse delle ascisse, e su $[0,1]$ il massimo di ciascuno sta in un estremo.
$$|\sin(t)-p(t)|\leq\frac16\cdot1\cdot\frac{\pi}{6}\cdot\frac{\pi}{4}\approx 0{,}0685$$
L'errore è dell'ordine di $10^{-2}$.
#### Stima più precisa
La partenza è la stessa, ma invece di separare tutti i fattori si separa solo quello con $\xi$ e si tengono insieme quelli con $t$:
$$|\sin(t)-p(t)|=\frac{\cos\xi}{6}\left|t\left(t-\frac{\pi}{6}\right)\left(t-\frac{\pi}{4}\right)\right|\leq\frac16\max_{y\in[0,1]}\Big|\underbrace{y\left(y-\frac{\pi}{6}\right)\left(y-\frac{\pi}{4}\right)}_{\omega(y)}\Big|\qquad(\text{€})$$
perché $t\in[0,1]$. Si calcola il massimo di $|\omega(y)|$ su $[0,1]$: bisogna cercare **tutti i massimi e i minimi relativi** di $\omega(y)$ su $[0,1]$ e scegliere il più grande di essi in modulo. Un minimo di $\omega$, col modulo, può diventare il massimo di $|\omega|$.

> [!quote] Teorema (analisi)
> I massimi e i minimi relativi di una funzione derivabile $\omega(y)$ su $[0,1]$ si trovano o nei punti di bordo dell'intervallo $[0,1]$ oppure nei punti stazionari di $\omega(y)$ in $[0,1]$, cioè i punti di $[0,1]$ in cui $\omega'(y)$ si annulla.

I bordi vanno sempre considerati: su un segmento il massimo e il minimo stanno agli estremi anche se la derivata non si annulla mai.
$$\omega(y)=y\left(y^2-\frac{5\pi}{12}y+\frac{\pi^2}{24}\right)=y^3-\frac{5\pi}{12}y^2+\frac{\pi^2}{24}y$$
$$\omega'(y)=3y^2-\frac{5\pi}{6}y+\frac{\pi^2}{24}$$
$$\omega'(y)=0\iff y=\frac{\frac{5\pi}{6}\pm\sqrt{\left(\frac{5\pi}{6}\right)^2-\frac{\pi^2}{2}}}{6}=\frac{5\pi}{36}\pm\frac{\sqrt7\,\pi}{36}=y_{1,2}$$
con $y_1$ il punto col $+$ e $y_2$ quello col $-$. Entrambi stanno in $[0,1]$ (si verifica con la calcolatrice: $y_1\approx0{,}667$, $y_2\approx0{,}205$) e dunque sono punti stazionari di $\omega$ in $[0,1]$. Allora
$$\max_{y\in[0,1]}|\omega(y)|=\max\big(\underbrace{|\omega(0)|}_{0},\ \underbrace{|\omega(1)|}_{0{,}10223\dots},\ \underbrace{|\omega(y_1)|}_{0{,}01132\dots},\ \underbrace{|\omega(y_2)|}_{0{,}03790\dots}\big)\leq 0{,}103$$
Tornando a $(\text{€})$:
$$|\sin(t)-p(t)|\leq\frac16\cdot0{,}103\approx0{,}0172$$
circa quattro volte meglio della stima grezza.

> [!warning] Il disegno di $\omega$ alla lavagna
> Il grafico qualitativo di $\omega(y)$ e $|\omega(y)|$ fatto a lezione (circa 01:25) serve solo a mostrare che il modulo ribalta i minimi in massimi. Il docente segnala che contiene un errore (01:35:49), senza dire quale. In effetti il segno non è quello di $\omega$: $\omega(y)=y\left(y-\frac{\pi}{6}\right)\left(y-\frac{\pi}{4}\right)$ è positiva su $\left(0,\frac{\pi}{6}\right)$, negativa su $\left(\frac{\pi}{6},\frac{\pi}{4}\right)$ e di nuovo positiva su $\left(\frac{\pi}{4},1\right]$, mentre il disegno la mostra negativa vicino a $0$. Per questo il disegno non è riportato.
#### Osservazioni
> [!info] Non serve conoscere $p(x)$
> In nessuna delle due stime si è usata l'espressione esplicita di $p(x)$: l'errore si può stimare **prima** di calcolare il polinomio.

> [!warning] Quale stima usare all'esame
> Il docente consiglia la **stima grezza**, più semplice. La stima più precisa vale qualche punto bonus: conviene farla alla fine, se avanza tempo. Ma ha un limite: si è potuta fare perché $\omega$ ha grado 3, quindi $\omega'$ ha grado 2 e se ne trovano gli zeri. Con 4 nodi $\omega'$ avrebbe grado 3, e le sue radici non si calcolano facilmente. Il metodo raffinato funziona solo quando $\omega$ ha grado al massimo 3; quello grezzo funziona sempre.
### Esempio 2: $e^{x^2}$ sui nodi $0,\frac12,1$
> [!example] Esempio
> Consideriamo $f(x)=e^{x^2}$ e sia $p(x)$ il suo polinomio d'interpolazione sui nodi $x_0=0,\ x_1=\frac12,\ x_2=1$.
> (a) Fornire una stima dell'errore d'interpolazione $|f(x)-p(x)|\ \forall x\in[0,1]$, cioè determinare una costante $C$ tale che $|f(x)-p(x)|\leq C\ \forall x\in[0,1]$.
> (b) Stimare l'errore che si commette approssimando $\sqrt[9]{e}$ con $p\left(\frac13\right)$ senza calcolare né $\sqrt[9]{e}$ né $p\left(\frac13\right)$.

Nella (a) si chiede una **maggiorazione uniforme**: una sola costante $C$ che sta sopra il grafico di $|f(x)-p(x)|$ per tutti gli $x\in[0,1]$.
#### (a)
Si applica il teorema con $f(x)=e^{x^2}$, $n=2$, $[a,b]=[0,1]$. $\forall x\in[0,1]$:
$$|f(x)-p(x)|=\left|\frac{f'''(\xi)}{3!}\,x\left(x-\frac12\right)(x-1)\right|\qquad(\xi\in(0,1))\qquad(\$)$$
Annotare sempre dove sta $\xi$: all'esame lo si dimentica spesso, ma serve per la stima. Si calcola $f'''(x)$ (derivata di funzione composta e di prodotti):
$$f'(x)=2x\,e^{x^2}$$
$$f''(x)=2e^{x^2}+2x\cdot2x\,e^{x^2}=(2+4x^2)\,e^{x^2}$$
$$f'''(x)=8x\,e^{x^2}+(2+4x^2)\,2x\,e^{x^2}=e^{x^2}(12x+8x^3)$$
Si maggiora $|f'''|$ uniformemente: $\forall x\in[0,1]$
$$|f'''(x)|=\left|e^{x^2}(12x+8x^3)\right|=\left|e^{x^2}\right|\cdot\left|12x+8x^3\right|=e^{x^2}(12x+8x^3)\leq e^1\,(12\cdot1+8\cdot1^3)=20e$$
- I moduli si tolgono: $e^{x^2}>0$ sempre, e $12x+8x^3\geq0$ per $x\in[0,1]$.
- Non serve il massimo esatto, basta una costante. $e^{x^2}$ è crescente su $[0,1]$, quindi $\leq e^1$; $12x$ e $8x^3$ sono crescenti, quindi la somma è $\leq 12+8$. Il ragionamento vale **perché** sono crescenti.

**Stima grezza.** Tornando a $(\$)$, poiché $\xi\in(0,1)$ si ha $|f'''(\xi)|\leq20e$, e su $[0,1]$ ciascun modulo ha il massimo in un estremo ($|x|\leq1$, $\left|x-\frac12\right|\leq\frac12$, $|x-1|\leq1$ con il massimo in $0$):
$$|f(x)-p(x)|=\frac{|f'''(\xi)|}{6}\,|x|\cdot\left|x-\frac12\right|\cdot|x-1|\leq\frac{20e}{6}\cdot1\cdot\frac12\cdot1\approx4{,}530$$

**Stima più precisa.** Dalla $(\$)$:
$$|f(x)-p(x)|=\frac{|f'''(\xi)|}{6}\left|x\left(x-\frac12\right)(x-1)\right|\leq\frac{20e}{6}\Big|\underbrace{x\left(x-\frac12\right)(x-1)}_{\omega(x)}\Big|\leq\frac{20e}{6}\max_{y\in[0,1]}|\omega(y)|\qquad(\text{£})$$
Come prima si calcola il massimo di $|\omega(y)|$ su $[0,1]$:
$$\omega(y)=y\left(y-\frac12\right)(y-1)=y\left(y^2-\frac32y+\frac12\right)=y^3-\frac32y^2+\frac12y$$
$$\omega'(y)=3y^2-3y+\frac12$$
$$\omega'(y)=0\iff y=\frac{3\pm\sqrt{9-6}}{6}=\frac{3\pm\sqrt3}{6}=y_{1,2}$$
$y_1,y_2\in[0,1]$, quindi
$$\max_{y\in[0,1]}|\omega(y)|=\max\big(\underbrace{|\omega(0)|}_{0},\ \underbrace{|\omega(1)|}_{0},\ |\omega(y_1)|,\ |\omega(y_2)|\big)=\frac{\sqrt3}{36}$$
I bordi qui non contano ($0$ e $1$ sono nodi), e $|\omega(y_1)|=|\omega(y_2)|=\frac{\sqrt3}{36}$ (con la calcolatrice va bene anche il valore approssimato). Tornando a $(\text{£})$:
$$|f(x)-p(x)|\leq\frac{20e}{6}\cdot\frac{\sqrt3}{36}\approx0{,}436$$
molto meglio della stima grezza.
#### (b)
Si osserva che $\sqrt[9]{e}=e^{1/9}=e^{(1/3)^2}=f\left(\frac13\right)$. Ci sono due modi.
- **Usare la stima di (a).** Poiché $x=\frac13\in[0,1]$, vale la stima uniforme:
$$\left|\sqrt[9]{e}-p\left(\tfrac13\right)\right|=\left|e^{(1/3)^2}-p\left(\tfrac13\right)\right|\leq\frac{20e}{6}\cdot\frac{\sqrt3}{36}\approx0{,}436$$
- **Applicare il teorema direttamente con $x=\frac13$** (la cosa migliore), sempre sull'intervallo $[0,1]$, il più piccolo che contiene $x=\frac13$ e i nodi $x_0,x_1,x_2$:
$$\left|\sqrt[9]{e}-p\left(\tfrac13\right)\right|=\left|e^{(1/3)^2}-p\left(\tfrac13\right)\right|=\left|\frac{f'''(\xi)}{3!}\left(\frac13-0\right)\left(\frac13-\frac12\right)\left(\frac13-1\right)\right|$$
$$=\frac{|f'''(\xi)|}{6}\cdot\frac13\cdot\frac16\cdot\frac23\leq\frac{20e}{6}\cdot\frac13\cdot\frac16\cdot\frac23\approx0{,}336$$

Qui il miglioramento non è eccezionale, ma in generale applicare il teorema direttamente nel punto che interessa è la strategia migliore e può dare guadagni notevoli.
### Esercizi
Esercizi lasciati per la lezione successiva:
- **1.4** Data $f(x)=\arctan(x)$: (a) scrivere in forma di Lagrange e in forma canonica il polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0=0,\ x_1=1,\ x_2=\sqrt3$; (b) fissato $t\in[0,2]$, stimare l'errore $|f(t)-p(t)|$.
- **1.5** Per ogni fissato $t\in[0,1]$, stimare l'errore che si commette approssimando $\sin(t)$ con $p(t)$, dove $p(x)$ interpola $\sin(x)$ sui nodi $0,\ \frac{\pi}{10},\ \frac{\pi}{6},\ \frac{\pi}{4},\ \frac{3\pi}{10}$. Confrontare con le stime dell'esempio 1; per risolverlo non serve conoscere $p(x)$.
- **1.6** Stimare l'errore che si commette approssimando $\sqrt2$ con $p(2)$, dove $p(x)$ interpola $\sqrt x$ sui nodi $1{,}69;\ 1{,}7689;\ 1{,}8769;\ 1{,}96;\ 2{,}0449;\ 2{,}1609;\ 2{,}25$, senza calcolare né $\sqrt2$ né $p(2)$.
- **1.7** Stimare l'errore che si commette approssimando $\cos(1)$ con $p(1)$, dove $p(x)$ interpola $\cos(x)$ sui nodi $0,\ \frac{\pi}{6},\ \frac{\pi}{4},\ \frac{\pi}{3},\ \frac{\pi}{2}$, senza calcolare né $\cos(1)$ né $p(1)$.
## Forma di Newton del polinomio d'interpolazione
Lezione 4 (15/10/2026).
Finora si sono viste due forme del polinomio d'interpolazione, la forma canonica e la forma di Lagrange ([[01 - Interpolazione polinomiale#Forma canonica e forma di Lagrange]]), e l'errore che si commette usandolo per approssimare una funzione ([[01 - Interpolazione polinomiale#Errore d'interpolazione#Teorema]]). Qui si introduce una terza forma, la **forma di Newton**, costruita con le **differenze divise**. Negli esercizi si può partire da questa invece che da quella di Lagrange, e anche da qui la forma canonica si ottiene sviluppando i calcoli. In più la forma di Newton dà un algoritmo efficiente per **valutare** il polinomio in un punto, di cui si calcola il costo computazionale esatto.
### Differenze divise
La definizione è **ricorsiva**, come quella del fattoriale: un caso base e un caso generale.
$$n!=\begin{cases}1 & \text{se } n=0\\ n\,(n-1)! & \text{se } n>0\end{cases}$$
> [!quote] Definizione (differenze divise)
> Sia $f:[a,b]\to\mathbb{R}$ una funzione.
> - Se $y\in[a,b]$, si definisce **differenza divisa** di $f(x)$ relativa a $y$ il numero
> $$f[y]=f(y)$$
> - Se $y_1,\dots,y_k\in[a,b]$ sono $k\geq2$ punti **distinti**, si definisce **differenza divisa** di $f(x)$ relativa a $y_1,\dots,y_k$ il numero
> $$f[y_1,\dots,y_k]=\frac{f[y_1,\dots,y_{k-2},y_k]-f[y_1,\dots,y_{k-1}]}{y_k-y_{k-1}}$$

Regola per ricordare la formula: al numeratore prima si **toglie il penultimo** punto, poi si sottrae la differenza divisa in cui si **toglie l'ultimo**; al denominatore si fa **ultimo meno penultimo**. I punti devono essere distinti, altrimenti il denominatore si annulla e la differenza divisa non è definita.

> [!warning] Ordine al numeratore
> A lezione la formula è stata scritta prima con i due termini del numeratore invertiti, poi corretta. Quella giusta è quella sopra: il termine **senza il penultimo** viene per primo. Il caso $k=2$ qui sotto permette di controllarlo.

> [!info] Due punti: il rapporto incrementale
> Se $k=2$, cioè con due punti distinti $y_1,y_2$:
> $$f[y_1,y_2]=\frac{f[y_2]-f[y_1]}{y_2-y_1}=\frac{f(y_2)-f(y_1)}{y_2-y_1}$$
> che è il **rapporto incrementale** relativo a $y_1,y_2$.
### Teorema
> [!quote] Teorema (forma di Newton)
> Sia $f:[a,b]\to\mathbb{R}$ una funzione e siano $x_0,x_1,\dots,x_n\in[a,b]$ nodi distinti. Allora il polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0,x_1,\dots,x_n$ è dato da
> $$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+\dots+f[x_0,x_1,\dots,x_n](x-x_0)(x-x_1)\cdots(x-x_{n-1})\qquad(N)$$
> La $(N)$ si chiama **forma di Newton** di $p(x)$.

Il teorema non è stato dimostrato a lezione.
- L'ultimo prodotto si ferma a $(x-x_{n-1})$: se comparisse anche $(x-x_n)$ il polinomio avrebbe grado $n+1$.
- $p(x)$ è **l'unico polinomio di grado $\leq n$** tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$. Il docente ripete questa domanda a ogni lezione perché è tipica dell'orale; si veda [[01 - Interpolazione polinomiale#Polinomio d'interpolazione]].
#### Le tre forme a confronto
Le tre forme scrivono lo stesso polinomio come combinazione lineare degli elementi di tre basi diverse di $\mathbb{R}_n[x]$.

| Forma | Base | Coefficienti |
|---|---|---|
| canonica: $p(x)=a_0+a_1x+a_2x^2+\dots+a_nx^n$ | base canonica $1,x,x^2,\dots,x^n$ | soluzione di $V(x_0,x_1,\dots,x_n)\begin{pmatrix}a_0\\\vdots\\a_n\end{pmatrix}=\begin{pmatrix}f(x_0)\\\vdots\\f(x_n)\end{pmatrix}$ |
| di Lagrange: $p(x)=f(x_0)L_0(x)+f(x_1)L_1(x)+\dots+f(x_n)L_n(x)$ | base di Lagrange $L_0(x),L_1(x),\dots,L_n(x)$ | i valori $f(x_0),\dots,f(x_n)$ |
| di Newton $(N)$ | base di Newton $1,\ x-x_0,\ (x-x_0)(x-x_1),\ \dots,\ (x-x_0)(x-x_1)\cdots(x-x_{n-1})$ | le differenze divise $f[x_0],\ f[x_0,x_1],\ \dots,\ f[x_0,\dots,x_n]$ |

Che gli elementi della base di Newton formino una base non è stato dimostrato, ma si può dimostrare. Nella pratica nessuno risolve il sistema con la matrice di Vandermonde: si scrive la forma di Lagrange o quella di Newton e si sviluppano i calcoli per ottenere la forma canonica.
### Corollario: simmetria delle differenze divise
> [!quote] Corollario
> Sia $f:[a,b]\to\mathbb{R}$ una funzione e siano $x_0,x_1,\dots,x_n\in[a,b]$ nodi distinti. Allora $f[x_0,x_1,\dots,x_n]$ non cambia se vengono permutati i suoi $n+1$ argomenti, cioè
> $$f[x_0,\dots,x_n]=f[x_{\sigma(0)},\dots,x_{\sigma(n)}]\qquad\forall\,\sigma \text{ permutazione di } \{0,\dots,n\}$$

In altre parole, l'ordine dei punti dentro le parentesi quadre non conta.
#### Dimostrazione
Sia $\sigma$ una permutazione di $\{0,\dots,n\}$.
- Usando la $(N)$ del polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0,\dots,x_n$ si ottiene la $(N)$.
- Usando successivamente la $(N)$ con i nodi $x_{\sigma(0)},\dots,x_{\sigma(n)}$, si ottiene che il polinomio d'interpolazione di $f(x)$ sui nodi $x_{\sigma(0)},\dots,x_{\sigma(n)}$, che **coincide con il precedente** perché la definizione di polinomio d'interpolazione non dipende dall'ordine dei nodi, è dato da
$$p(x)=f[x_{\sigma(0)}]+f[x_{\sigma(0)},x_{\sigma(1)}](x-x_{\sigma(0)})+\dots+f[x_{\sigma(0)},x_{\sigma(1)},\dots,x_{\sigma(n)}](x-x_{\sigma(0)})(x-x_{\sigma(1)})\cdots(x-x_{\sigma(n-1)})$$

In entrambe le scritture il termine di grado massimo $x^n$ si ottiene solo dall'ultimo addendo, prendendo $x$ da tutti gli $n$ fattori. Vediamo dunque che $f[x_0,\dots,x_n]$ e $f[x_{\sigma(0)},\dots,x_{\sigma(n)}]$ sono entrambi il **coefficiente direttore** di $p(x)$, cioè il coefficiente $a_n$ davanti a $x^n$. Essendo il coefficiente direttore dello stesso polinomio, devono essere uguali:
$$f[x_0,\dots,x_n]=f[x_{\sigma(0)},\dots,x_{\sigma(n)}]\qquad\blacksquare$$
### Esempio: $\sqrt x$ sui nodi $0,\ 0{,}16,\ 0{,}64,\ 1$
> [!example] Esempio
> Scrivere in forma canonica e in forma di Newton il polinomio d'interpolazione $p(x)$ della funzione $f(x)=\sqrt x$ sui nodi $x_0=0,\ x_1=0{,}16,\ x_2=0{,}64,\ x_3=1$.

Si inizia dalla forma di Newton, da cui poi si otterrà la forma canonica semplicemente sviluppando i calcoli (come si faceva con la forma di Lagrange). Per il teorema, la forma di Newton di $p(x)$ è
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+f[x_0,x_1,x_2,x_3](x-x_0)(x-x_1)(x-x_2)\qquad(\star)$$
L'unica cosa da fare è calcolare le quattro differenze divise che fanno da coefficienti.
#### La tabella delle differenze divise
Per calcolarle si usa la **tabella delle differenze divise**, da pensare come una matrice triangolare inferiore:
$$\begin{array}{cccc}
\boxed{f[x_0]} & & & \\
f[x_1] & \boxed{f[x_0,x_1]} & & \\
f[x_2] & f[x_0,x_2] & \boxed{f[x_0,x_1,x_2]} & \\
f[x_3] & f[x_0,x_3] & f[x_0,x_1,x_3] & \boxed{f[x_0,x_1,x_2,x_3]}
\end{array}$$
- La prima colonna contiene le differenze divise su un solo nodo, cioè i **valori** della funzione nei nodi.
- Ogni elemento si calcola dai due elementi della colonna precedente da cui escono le frecce nel disegno alla lavagna. Ad esempio $f[x_0,x_1,x_3]$ si ottiene da $f[x_0,x_3]$ e $f[x_0,x_1]$, e $f[x_0,x_1,x_2,x_3]$ da $f[x_0,x_1,x_3]$ e $f[x_0,x_1,x_2]$.
- Gli elementi che servono per la $(\star)$ sono quelli sulla **diagonale** (riquadrati). Non si può calcolare solo la diagonale: andando a ritroso, per ottenere l'ultimo elemento servono anche quelli fuori diagonale della colonna precedente, e così via. Bisogna calcolare tutta la tabella, procedendo **colonna per colonna**.
#### Calcolo
**Prima colonna:**
$$f[x_0]=f(x_0)=\sqrt0=\boxed{0}\qquad f[x_1]=f(x_1)=0{,}4\qquad f[x_2]=f(x_2)=0{,}8\qquad f[x_3]=f(x_3)=1$$
**Seconda colonna:**
$$f[x_0,x_1]=\frac{f[x_1]-f[x_0]}{x_1-x_0}=\frac{0{,}4}{0{,}16}=\boxed{\frac52}$$
$$f[x_0,x_2]=\frac{f[x_2]-f[x_0]}{x_2-x_0}=\frac{0{,}8}{0{,}64}=\frac54$$
$$f[x_0,x_3]=\frac{f[x_3]-f[x_0]}{x_3-x_0}=\frac11=1$$
**Terza colonna:**
$$f[x_0,x_1,x_2]=\frac{f[x_0,x_2]-f[x_0,x_1]}{x_2-x_1}=\frac{\frac54-\frac52}{0{,}64-0{,}16}=\boxed{-\frac{125}{48}}$$
$$f[x_0,x_1,x_3]=\frac{f[x_0,x_3]-f[x_0,x_1]}{x_3-x_1}=\frac{1-\frac52}{1-0{,}16}=-\frac{25}{14}$$
**Quarta colonna:**
$$f[x_0,x_1,x_2,x_3]=\frac{f[x_0,x_1,x_3]-f[x_0,x_1,x_2]}{x_3-x_2}=\frac{-\frac{25}{14}-\left(-\frac{125}{48}\right)}{1-0{,}64}=\boxed{\frac{6875}{3024}}$$
All'esame si può usare la calcolatrice.
#### Forma di Newton e forma canonica
Sostituendo i valori riquadrati nella $(\star)$ si ottiene la forma di Newton di $p(x)$ (il primo termine è nullo e si può eliminare):
$$p(x)=\frac52x-\frac{125}{48}x(x-0{,}16)+\frac{6875}{3024}x(x-0{,}16)(x-0{,}64)$$
Sviluppando i calcoli si ottiene la forma canonica:
$$p(x)=\frac{6875}{3024}x^3-\frac{13375}{3024}x^2+\frac{2381}{756}x$$
Manca il termine noto perché $x_0=0$ è un nodo e $p(0)=\sqrt0=0$. Si verifica che $p(0{,}16)=0{,}4$, $p(0{,}64)=0{,}8$, $p(1)=1$.
#### Osservazione: dati senza una funzione
> [!info] Forma di Newton di dati qualsiasi
> Supponiamo che siano dati i punti $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ con $x_0,x_1,\dots,x_n$ distinti. I numeri $y_0,y_1,\dots,y_n$ possono **sempre** essere interpretati come i valori in $x_0,x_1,\dots,x_n$ di una qualche funzione $f:[a,b]\to\mathbb{R}$. Quindi ha perfettamente senso parlare di forma di Newton del polinomio d'interpolazione dei dati $(x_0,y_0),\dots,(x_n,y_n)$ anche quando non viene specificata una funzione $f(x)$ tale che $f(x_i)=y_i\ \forall i=0,\dots,n$: in tal caso basta immaginarsi una tale funzione. Non serve esplicitarla: della funzione si usano solo i valori nei nodi, che sono gli $y_i$, e con quelli si costruisce la tabella.

> [!warning] Da quale forma partire all'esame
> Quando si chiedono più forme dello stesso polinomio si può partire indifferentemente dalla forma di Lagrange o da quella di Newton, ricavare da quella la forma canonica sviluppando i calcoli e calcolare l'altra a parte. Non si parte mai dalla forma canonica, che è sempre la più sconveniente.
### Algoritmo di valutazione in un punto del polinomio d'interpolazione
Sia $f:[a,b]\to\mathbb{R}$, siano $x_0,\dots,x_n\in[a,b]$ nodi distinti e sia $t\in\mathbb{R}$. Si costruisce un algoritmo per calcolare $p(t)$, dove $p(x)$ è il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,\dots,x_n$. Valutare un polinomio in un punto sembra un'operazione banale, ma farlo in modo efficiente è fondamentale.

Per semplicità si vede l'algoritmo nel caso $n=3$, che basta a mostrare tutte le idee. La forma di Newton di $p(x)$ è in questo caso
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+f[x_0,x_1,x_2,x_3](x-x_0)(x-x_1)(x-x_2)\qquad(\nu)$$
($\nu$, "ni", è la $n$ greca, iniziale di Newton.)
#### Prima parte: le differenze divise
La prima parte è **indipendente dal punto $t$** in cui si deve valutare $p(x)$. Consiste nel calcolare le differenze divise che fanno da coefficienti nella $(\nu)$, e lo si fa con la tabella delle differenze divise come nell'esempio precedente. Non c'è un modo più efficiente.

**Costo computazionale della prima parte.** La prima colonna della tabella contiene i dati e non è da calcolare. Nel caso $n=3$ si devono calcolare in totale $6$ differenze divise; in generale sono
$$\frac{n(n+1)}{2}=\sum_{i=1}^{n}i=\frac{n^2-n}{2}+n$$
cioè il numero di elementi della parte triangolare inferiore, **inclusa la diagonale**, di una matrice $n\times n$. I due modi di contarli:
- per righe: $1+2+\dots+n=\frac{n(n+1)}{2}$;
- la matrice ha $n^2$ elementi; togliendo gli $n$ della diagonale restano due metà uguali (parte strettamente inferiore e strettamente superiore), quindi $\frac{n^2-n}{2}$, a cui si riaggiunge la diagonale.

Per ogni differenza divisa si fanno **2 sottrazioni e 1 divisione**. Totale costo della prima parte:
- $n(n+1)$ sottrazioni (S);
- $\frac{n(n+1)}{2}$ divisioni (D).
#### Seconda parte: il metodo di Ruffini–Horner
Si calcola $p(t)$. Sostituire direttamente $t$ nella $(\nu)$ non è astuto: il fattore $(t-x_0)$ verrebbe moltiplicato più volte, e lo stesso $(t-x_1)$. Conviene invece **raccoglierli**, con parentesi annidate:
$$p(t)=f[x_0]+f[x_0,x_1](t-x_0)+f[x_0,x_1,x_2](t-x_0)(t-x_1)+f[x_0,x_1,x_2,x_3](t-x_0)(t-x_1)(t-x_2)$$
$$=f[x_0]+(t-x_0)\Big\{f[x_0,x_1]+(t-x_1)\Big[f[x_0,x_1,x_2]+(t-x_2)\,f[x_0,x_1,x_2,x_3]\Big]\Big\}$$
Si "mangia il panino" dall'interno, chiamando $h_3,h_2,h_1,h_0$ le espressioni dalla più interna alla più esterna:
$$\begin{aligned}
h_3&=f[x_0,x_1,x_2,x_3]\\
h_2&=f[x_0,x_1,x_2]+(t-x_2)\,h_3\\
h_1&=f[x_0,x_1]+(t-x_1)\,h_2\\
p(t)=h_0&=f[x_0]+(t-x_0)\,h_1
\end{aligned}$$
In generale l'algoritmo è ricorsivo, a ritroso:
$$h_n=f[x_0,\dots,x_n],\qquad h_i=f[x_0,\dots,x_i]+(t-x_i)\,h_{i+1}\quad i=n-1,\dots,0,\qquad p(t)=h_0$$
Così ogni fattore $(t-x_i)$ si moltiplica una volta sola.

```pseudo
\begin{algorithm}
\caption{ValutaNewton($x_0,\dots,x_n$, $f(x_0),\dots,f(x_n)$, $t$)}
\begin{algorithmic}
\State calcola $f[x_0],f[x_0,x_1],\dots,f[x_0,\dots,x_n]$ con la tabella delle differenze divise \Comment{prima parte}
\State $h \gets f[x_0,\dots,x_n]$ \Comment{$h_n$}
\For{$i = n-1$ \textbf{downto} $0$}
  \State $h \gets f[x_0,\dots,x_i] + (t - x_i)\cdot h$ \Comment{$h_i$}
\EndFor
\State \Return $h$ \Comment{$h_0 = p(t)$}
\end{algorithmic}
\end{algorithm}
```

**Costo computazionale della seconda parte.** Si devono calcolare $n$ numeri $h_{n-1},h_{n-2},\dots,h_0$: tutti tranne $h_n$, che è noto dalla prima parte. Il calcolo di ciascun $h_i$ richiede:
- 1 sottrazione (S), per $t-x_i$;
- 1 moltiplicazione (M), per $(t-x_i)\,h_{i+1}$;
- 1 addizione (A), per sommare la differenza divisa, già nota dalla prima parte.

> [!info] Quanto costano le operazioni
> Per il computer **1 S e 1 A costano uguale**, perché $\alpha-\beta=\alpha+(-\beta)$ e mettere un meno davanti a $\beta$ non costa niente (non deve fare nessuna operazione). Invece una divisione **non** costa come una moltiplicazione: $\frac{\alpha}{\beta}=\alpha\cdot\frac1\beta$, e calcolare l'inverso $\frac1\beta$ è un'operazione costosa. Quindi addizioni e sottrazioni si contano insieme, moltiplicazioni e divisioni separate.

Totale costo della seconda parte: $2n\,A+n\,M$.
#### Costo totale dell'algoritmo
$$C(n)=\underbrace{n(n+1)\,A+\frac{n(n+1)}{2}\,D}_{\text{1ª parte}}+\underbrace{2n\,A+n\,M}_{\text{2ª parte}}=(n^2+3n)\,A+n\,M+\left(\frac{n^2}{2}+\frac n2\right)D$$
$$\approx n^2\,A+\frac{n^2}{2}\,D\qquad\left(\approx\frac{3n^2}{2}\text{ operazioni}\right)$$
L'approssimazione trascura i termini di ordine inferiore ma conserva le **costanti** davanti a $n^2$.

> [!info] Perché le costanti contano
> Il docente preferisce calcolare il costo esatto invece di scrivere solo $O(n^2)$: $O(n^2)$ dice che il costo è limitato da una costante per $n^2$, ma una costante di 500 milioni è ben diversa da una di $\frac12$. Anche un algoritmo lineare con costante 5 miliardi può essere peggiore di uno quadratico con costante $\frac12$.
#### Valutazione in $m$ punti
Poiché la prima parte dell'algoritmo consiste nel calcolo delle differenze divise ed è indipendente dal punto $t$ in cui deve essere valutato $p(x)$, per valutare $p(x)$ in $m$ punti $t_1,\dots,t_m\in\mathbb{R}$ si fa la prima parte **una volta sola** e poi si ripete $m$ volte la seconda parte. Costo complessivo:
$$C_m(n)=\underbrace{n(n+1)\,A+\frac{n(n+1)}{2}\,D}_{\text{1ª parte}}+\underbrace{m\,(2n\,A+n\,M)}_{\text{2ª parte}}=(n^2+2nm+n)\,A+nm\,M+\left(\frac{n^2}{2}+\frac n2\right)D$$
$$\approx(n^2+2nm)\,A+nm\,M+\frac{n^2}{2}\,D$$

> [!warning] Attenzione alle approssimazioni
> Nella stima di $C(n)$ le moltiplicazioni erano sparite, perché $n\,M$ è di ordine inferiore a $n^2$. Ma valutando in $m$ punti diventano $nm\,M$, e $m$ è una grandezza **indipendente** da $n$: con 20 nodi e 5000 punti di valutazione è $m$ a contare di più. Si può trascurare $n$ rispetto a $n^2$, ma non $nm$. Chi fosse partito dall'approssimazione $C(n)\approx n^2A+\frac{n^2}{2}D$ e l'avesse moltiplicata avrebbe perso le $nm$ moltiplicazioni, e l'algoritmo risulterebbe più lento del previsto.

> [!question] Domanda tipica d'esame
> Descrivere l'algoritmo per valutare in un punto $t$ il polinomio d'interpolazione usando la forma di Newton (tabella delle differenze divise e metodo di Ruffini–Horner) e calcolarne il costo computazionale. Come cambiano l'algoritmo e il costo se si deve valutare il polinomio in $m$ punti?
### Esercizi
Esercizi lasciati alla fine della parte sulla forma di Newton:
- **1.8** Scrivere in forma canonica e in forma di Newton il polinomio d'interpolazione di $f(x)=\cos\left(\frac{\pi}{2}x\right)\log_2(x)$ sui nodi $x_0=1,\ x_1=2,\ x_2=4,\ x_3=8$.
- **1.9** Scrivere in forma canonica, in forma di Lagrange e in forma di Newton il polinomio d'interpolazione dei valori $y_0=0,\ y_1=3,\ y_2=-3$ sui nodi $x_0=0,\ x_1=1,\ x_2=2$.
## Valutazione e aggiunta di un nodo
Lezione 5 (20/10/2026), prima parte: si chiude l'interpolazione polinomiale con un esempio completo dell'algoritmo di valutazione visto in [[#Algoritmo di valutazione in un punto del polinomio d'interpolazione]] e con l'**aggiunta di un nodo d'interpolazione**, il caso in cui la forma di Newton è la più conveniente. Nell'ultima mezz'ora comincia l'integrazione numerica ([[02 - Integrazione numerica#Formula dei trapezi]]).
### Esempio: valutazione con l'algoritmo di Newton
> [!example] Esempio
> Consideriamo i dati
> $$(x_0,y_0)=(0,0),\quad(x_1,y_1)=(1,3),\quad(x_2,y_2)=(2,1),\quad(x_3,y_3)=(3,1)$$
> Calcolare mediante l'algoritmo descritto il valore in $t=2{,}3$ del polinomio $p(x)$ d'interpolazione di questi dati.

Il polinomio d'interpolazione di questi dati è l'unico polinomio $p(x)$ di grado $\leq3$ tale che $p(x_i)=y_i$ per ogni $i=0,1,2,3$. Il docente lo fa ripetere ancora una volta perché è una domanda tipica dell'orale ([[01 - Interpolazione polinomiale#Polinomio d'interpolazione]]).

Non è data una funzione, ma come osservato in [[01 - Interpolazione polinomiale#Osservazione: dati senza una funzione]] la si può sempre immaginare. Sia $f:[0,3]\to\mathbb{R}$ una qualsiasi funzione tale che $f(x_i)=y_i$ $\forall i=0,1,2,3$ (l'intervallo $[0,3]$ è il più piccolo che contiene tutti i nodi). Il polinomio $p(x)$ del testo è dunque il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,x_1,x_2,x_3$ e si scrive in forma di Newton nel modo seguente:
$$p(x)=\boxed{f[x_0]}+\boxed{f[x_0,x_1]}(x-x_0)+\boxed{f[x_0,x_1,x_2]}(x-x_0)(x-x_1)+\boxed{f[x_0,x_1,x_2,x_3]}(x-x_0)(x-x_1)(x-x_2)$$
#### Prima parte: tabella delle differenze divise
La prima parte dell'algoritmo calcola le differenze divise riquadrate (in blu alla lavagna) usando la tabella delle differenze divise, colonna per colonna. La prima colonna contiene i dati:
$$f[x_0]=y_0=\boxed{0}\qquad f[x_1]=y_1=3\qquad f[x_2]=y_2=1\qquad f[x_3]=y_3=1$$
**Seconda colonna** (sono rapporti incrementali):
$$f[x_0,x_1]=\frac{f[x_1]-f[x_0]}{x_1-x_0}=\frac{3-0}{1}=\boxed{3}\qquad f[x_0,x_2]=\frac{f[x_2]-f[x_0]}{x_2-x_0}=\frac12\qquad f[x_0,x_3]=\frac{f[x_3]-f[x_0]}{x_3-x_0}=\frac13$$
**Terza colonna:**
$$f[x_0,x_1,x_2]=\frac{f[x_0,x_2]-f[x_0,x_1]}{x_2-x_1}=\frac{\frac12-3}{1}=\boxed{-\frac52}\qquad f[x_0,x_1,x_3]=\frac{f[x_0,x_3]-f[x_0,x_1]}{x_3-x_1}=\frac{\frac13-3}{2}=-\frac43$$
**Quarta colonna:**
$$f[x_0,x_1,x_2,x_3]=\frac{f[x_0,x_1,x_3]-f[x_0,x_1,x_2]}{x_3-x_2}=\frac{-\frac43+\frac52}{1}=\boxed{\frac76}$$
#### Seconda parte: Ruffini–Horner
Si applica la ricorsione $h_n=f[x_0,\dots,x_n]$, $h_i=f[x_0,\dots,x_i]+(t-x_i)\,h_{i+1}$ con $t=2{,}3$:
$$\begin{aligned}
h_3&=f[x_0,x_1,x_2,x_3]=\frac76\\
h_2&=f[x_0,x_1,x_2]+(t-x_2)\,h_3=-\frac52+(2{,}3-2)\,\frac76=-\frac{43}{20}\\
h_1&=f[x_0,x_1]+(t-x_1)\,h_2=3+(2{,}3-1)\left(-\frac{43}{20}\right)=\frac{41}{200}\\
h_0&=f[x_0]+(t-x_0)\,h_1=0+(2{,}3-0)\,\frac{41}{200}=\frac{943}{2000}=p(2{,}3)
\end{aligned}$$
I conti si fanno comodamente scrivendo $2{,}3=\frac{23}{10}$; all'esame si può usare la calcolatrice.
### Aggiunta di un nodo d'interpolazione
Nella pratica capita spesso che ai dati già interpolati se ne aggiunga uno nuovo, ad esempio per una nuova rilevazione: si vuole allora il polinomio d'interpolazione che passa anche per il nuovo dato. La forma di Newton è particolarmente conveniente quando ai dati d'interpolazione $(x_0,y_0),\dots,(x_n,y_n)$ ne viene aggiunto uno nuovo $(x_{n+1},y_{n+1})$ con $x_{n+1}\neq x_0,\dots,x_n$ (il nuovo nodo deve essere distinto dai precedenti).
#### Perché conviene la forma di Newton
Sia $f(x)$ una qualsiasi funzione tale che $f(x_i)=y_i$ $\forall i=0,\dots,n+1$, nuovo nodo compreso: serve solo per poter scrivere le differenze divise, non va esplicitata. Il polinomio d'interpolazione $p(x)$ dei dati vecchi $(x_0,y_0),\dots,(x_n,y_n)$ si scrive in forma di Newton come
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+\dots+f[x_0,\dots,x_n](x-x_0)\cdots(x-x_{n-1})$$
e il polinomio d'interpolazione $q(x)$ dei dati $(x_0,y_0),\dots,(x_{n+1},y_{n+1})$ si scrive in forma di Newton come
$$q(x)=p(x)+f[x_0,\dots,x_n,x_{n+1}](x-x_0)\cdots(x-x_n)$$
La forma di Newton è **incrementale**: partendo dal polinomio sui nodi precedenti basta aggiungere un termine. Con la forma canonica invece bisognerebbe ricalcolare tutti i coefficienti da capo, risolvendo un nuovo sistema con la matrice di Vandermonde.

> [!info] E se $p(x)$ fosse in forma canonica?
> A lezione è stato chiesto se basti aggiungere l'ultimo termine anche avendo $p(x)$ in forma canonica. L'uguaglianza $q(x)=p(x)+f[x_0,\dots,x_{n+1}](x-x_0)\cdots(x-x_n)$ vale comunque, ma per calcolare il nuovo coefficiente servono le differenze divise diagonali, che la forma canonica non fornisce: andrebbero ricalcolate tutte, il che equivale a calcolare prima la forma di Newton, e il guadagno sparisce.
#### Costo del nuovo coefficiente
Chiamiamo **blu** i coefficienti $f[x_0],\ f[x_0,x_1],\ \dots,\ f[x_0,\dots,x_n]$ di $p(x)$ e **rosso** il nuovo coefficiente $f[x_0,\dots,x_{n+1}]$.

**Conclusione 1.** Avendo a disposizione $p(x)$ in forma di Newton, sono noti i coefficienti blu, quindi basta calcolare il coefficiente rosso per ottenere la forma di Newton di $q(x)$.

Nel caso $n=2$ la tabella delle differenze divise di $q(x)$ è quella di $p(x)$ con una riga in più (arancione alla lavagna):
$$\begin{array}{cccc}
\boxed{f[x_0]} & & & \\
f[x_1] & \boxed{f[x_0,x_1]} & & \\
f[x_2] & f[x_0,x_2] & \boxed{f[x_0,x_1,x_2]} & \\
\hline
f[x_3] & f[x_0,x_3] & f[x_0,x_1,x_3] & \mathbf{f[x_0,x_1,x_2,x_3]}
\end{array}$$
Il calcolo del coefficiente rosso richiede di calcolare **solo l'ultima riga** della tabella. Gli elementi non diagonali delle righe vecchie ($f[x_1]$, $f[x_2]$, $f[x_0,x_2]$, azzurri alla lavagna) non sono noti se si conosce solo $p(x)$, ma **non servono**: seguendo le linee della tabella, ogni elemento dell'ultima riga si calcola dall'elemento precedente della stessa riga e da un elemento **diagonale**, già noto. Ad esempio $f[x_0,x_1,x_3]$ usa $f[x_0,x_3]$ e $f[x_0,x_1]$, e $f[x_0,x_1,x_2,x_3]$ usa $f[x_0,x_1,x_3]$ e $f[x_0,x_1,x_2]$.

L'ultima riga ha $n+2$ elementi, ma il primo, $f[x_{n+1}]=y_{n+1}$, è il nuovo dato e non va calcolato. Restano $n+1$ differenze divise, ciascuna con 2 sottrazioni e 1 divisione:
$$2(n+1)\,A+(n+1)\,D$$
Il costo è **lineare** in $n$.

**Conclusione 2.** Avendo a disposizione $p(x)$ in forma di Newton e il suo valore $p(t)$ in un punto $t$, per calcolare
$$q(t)=p(t)+f[x_0,\dots,x_{n+1}](t-x_0)\cdots(t-x_n)$$
il costo è $2(n+1)\,A+(n+1)\,D$ per il coefficiente rosso, più ulteriori:
- $n+2$ addizioni: $n+1$ sottrazioni per i fattori $t-x_0,\dots,t-x_n$ e una somma finale con $p(t)$;
- $n+1$ moltiplicazioni: i fattori da moltiplicare sono $n+2$ (il coefficiente rosso e gli $n+1$ binomi), e per moltiplicare $k$ numeri servono $k-1$ moltiplicazioni.

$$\text{Totale: }(3n+4)\,A+(n+1)\,M+(n+1)\,D$$
Ancora un costo lineare in $n$.

> [!question] Domanda tipica d'esame
> Perché la forma di Newton è conveniente quando si aggiunge un nodo d'interpolazione? Quanto costa calcolare la forma di Newton del nuovo polinomio $q(x)$ e il suo valore $q(t)$, conoscendo $p(x)$ in forma di Newton e $p(t)$? Traccia: $q(x)=p(x)+f[x_0,\dots,x_{n+1}](x-x_0)\cdots(x-x_n)$; per il coefficiente nuovo basta l'ultima riga della tabella, calcolabile con i soli elementi diagonali; costi $2(n+1)A+(n+1)D$ e $(3n+4)A+(n+1)M+(n+1)D$.
### Esempio: $\cos(\pi x)+x^2$ con aggiunta di un nodo
> [!example] Esempio
> Consideriamo $f(x)=\cos(\pi x)+x^2$.
> - (a) Scrivere il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0=-1,\ x_1=0,\ x_2=2$ e calcolare $p\left(\frac12\right)$.
> - (b) Scrivere il polinomio d'interpolazione $q(x)$ della funzione $f(x)$ sui nodi precedenti a cui si aggiunge $x_3=1$, e calcolare $q\left(\frac12\right)$.

> [!warning] Leggere tutto il testo prima di scegliere la forma
> Il testo dice solo "scrivere il polinomio d'interpolazione", quindi si può usare la forma che si vuole. Ma il punto (b) parla di aggiunta di un nodo: conviene la forma di Newton. Secondo il docente, chi vuole farsi del male usa la forma canonica, chi vuole farsene meno (ma comunque) quella di Lagrange, chi vuole farsi del bene quella di Newton.
#### Punto (a)
Conviene scrivere $p(x)$ in forma di Newton in vista dell'aggiunta di un nodo del punto (b), e anche della valutazione di $p(x)$ in $t$ con Ruffini–Horner:
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)$$
Tabella delle differenze divise:
$$f[x_0]=f(-1)=\cos(-\pi)+1=\boxed{0}\qquad f[x_1]=f(0)=1\qquad f[x_2]=f(2)=\cos(2\pi)+4=5$$
$$f[x_0,x_1]=\frac{f[x_1]-f[x_0]}{x_1-x_0}=\frac{1-0}{1}=\boxed{1}\qquad f[x_0,x_2]=\frac{f[x_2]-f[x_0]}{x_2-x_0}=\frac{5}{3}$$
$$f[x_0,x_1,x_2]=\frac{f[x_0,x_2]-f[x_0,x_1]}{x_2-x_1}=\frac{\frac53-1}{2}=\boxed{\frac13}$$
Quindi
$$p(x)=(x+1)+\frac13(x+1)\,x$$
Calcoliamo $p(t)$ con $t=\frac12$ con Ruffini–Horner:
$$\begin{aligned}
h_2&=\frac13\\
h_1&=f[x_0,x_1]+(t-x_1)\,h_2=1+\frac12\cdot\frac13=\frac76\\
h_0&=f[x_0]+(t-x_0)\,h_1=0+\frac32\cdot\frac76=\frac74=p\left(\tfrac12\right)
\end{aligned}$$
Alla lavagna il docente ha prima scritto $t-x_0$ al posto di $t-x_1$ nel calcolo di $h_1$, poi ha corretto: in $h_i$ compare sempre il nodo con lo stesso indice $i$.
#### Punto (b)
Scriviamo $q(x)$ in forma di Newton sfruttando il calcolo di $p(x)$ già fatto al punto (a):
$$q(x)=p(x)+f[x_0,x_1,x_2,x_3](x-x_0)(x-x_1)(x-x_2)$$
Per calcolare $f[x_0,x_1,x_2,x_3]$ si aggiunge la riga arancione alla tabella usata per $p(x)$, usando solo gli elementi diagonali:
$$f[x_3]=f(1)=\cos\pi+1=0\qquad f[x_0,x_3]=\frac{f[x_3]-f[x_0]}{x_3-x_0}=0$$
$$f[x_0,x_1,x_3]=\frac{f[x_0,x_3]-f[x_0,x_1]}{x_3-x_1}=\frac{0-1}{1}=-1$$
$$f[x_0,x_1,x_2,x_3]=\frac{f[x_0,x_1,x_3]-f[x_0,x_1,x_2]}{x_3-x_2}=\frac{-1-\frac13}{1-2}=\boxed{\frac43}$$
Quindi
$$q(x)=p(x)+\frac43(x+1)\,x\,(x-2)$$
e, usando $p\left(\frac12\right)=\frac74$ già calcolato,
$$q\left(\tfrac12\right)=p\left(\tfrac12\right)+\frac43\cdot\frac32\cdot\frac12\cdot\left(-\frac32\right)=\frac74-\frac32=\frac14$$

> [!info] Una coincidenza
> $f\left(\frac12\right)=\cos\frac\pi2+\frac14=\frac14$, quindi $q\left(\frac12\right)=f\left(\frac12\right)$ esattamente. Non era scontato: $\frac12$ non è un nodo. Con l'aggiunta di questo nodo è successo "un miracolo".
### Esercizi
- **1.10** Tramite l'algoritmo descritto, valutare in $t=\frac12$ e $t=4$ il polinomio d'interpolazione della funzione $f(x)=x\sqrt x$ sui nodi $x_0=0,\ x_1=1,\ x_2=4,\ x_3=9$. La prima parte dell'algoritmo (le differenze divise) si fa una volta sola; la seconda si ripete per ciascuno dei due punti (si veda la valutazione in $m$ punti in [[01 - Interpolazione polinomiale#Algoritmo di valutazione in un punto del polinomio d'interpolazione]]).
- **1.12** Si consideri la funzione $f(x)=\sin(\pi x)$.
	- (a) Determinare il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0=0,\ x_1=\frac12,\ x_2=1$ e calcolare $p(t)$ per $t=\frac14$ e $t=\frac13$.
	- (b) Determinare il polinomio d'interpolazione $q(x)$ della funzione $f(x)$ sui nodi precedenti ai quali si aggiunge un nuovo nodo $x_3=\frac34$ e calcolare $q(t)$ per $t=\frac14$ e $t=\frac13$.

Con questo finisce la parte sull'interpolazione polinomiale.
