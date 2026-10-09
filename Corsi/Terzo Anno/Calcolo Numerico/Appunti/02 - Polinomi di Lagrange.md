---
tags:
  - calcolo-numerico
  - interpolazione
slide: []
---
# Polinomi di Lagrange
Si riprende il teorema di esistenza e unicità del polinomio interpolante visto in [[01 - Interpolazione polinomiale#Teorema]], di cui qui si dà una seconda dimostrazione. La prima, tramite la matrice di Vandermonde, è in [[01 - Interpolazione polinomiale#Dimostrazione 1]].
> [!quote] Teorema
> Siano $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ tali che $x_0,x_1,\dots,x_n$ sono distinti. Allora $\exists!\ p(x)\in\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\quad\forall i=0,\dots,n$.
## Dimostrazione 2
### Polinomi di Lagrange
$\forall j=0,\dots,n$ si definisce
$$L_j(x)=\prod_{\substack{k=0\\k\neq j}}^{n}\frac{x-x_k}{x_j-x_k}=\frac{(x-x_0)\cdots(x-x_{j-1})(x-x_{j+1})\cdots(x-x_n)}{(x_j-x_0)\cdots(x_j-x_{j-1})(x_j-x_{j+1})\cdots(x_j-x_n)}$$
- Si salta il fattore $k=j$ (a numeratore e a denominatore): per $k=j$ il denominatore si annullerebbe.
- Ce n'è uno per ogni nodo: in totale $n+1$ polinomi.
- Il denominatore è una costante (prodotto di differenze di nodi); $x$ compare solo a numeratore, che è un prodotto di $n$ fattori di primo grado. Il termine di grado massimo si ottiene scegliendo $x$ in ogni fattore, quindi $x^n$.
- Gli $n+1$ polinomi $L_0(x),\dots,L_n(x)$ hanno tutti grado $n$, quindi appartengono a $\mathbb{R}_n[x]$.

Si dimostra che $L_0(x),\dots,L_n(x)$ sono una base di $\mathbb{R}_n[x]$.
### Promemoria sulle basi di $\mathbb{R}_n[x]$
Una base di $\mathbb{R}_n[x]$ è un insieme di polinomi $\{v_1(x),\dots,v_r(x)\}$ che:
- sono **linearmente indipendenti**: se $\alpha_1v_1(x)+\dots+\alpha_rv_r(x)=0$ (polinomio nullo, cioè nullo per ogni $x$), allora $\alpha_1=\dots=\alpha_r=0$;
- **generano** tutto $\mathbb{R}_n[x]$: $\forall v(x)\in\mathbb{R}_n[x]\ \exists\alpha_1,\dots,\alpha_r\in\mathbb{R}$ tali che $v(x)=\alpha_1v_1(x)+\dots+\alpha_rv_r(x)$.

La base canonica di $\mathbb{R}_n[x]$ è data dai monomi $1,x,x^2,x^3,\dots,x^n$, che sono $n+1$. Tutte le basi di uno spazio vettoriale hanno lo stesso numero di elementi (la **dimensione**): quindi tutte le basi di $\mathbb{R}_n[x]$ hanno $n+1$ elementi e $n+1=\dim(\mathbb{R}_n[x])$.
> [!info] Indipendenza dei monomi
> Che i monomi generino $\mathbb{R}_n[x]$ è ovvio (i polinomi sono per definizione loro combinazioni lineari); la loro indipendenza lineare non è stata dimostrata a lezione, ma il docente consiglia di andare a vedere la dimostrazione.
>
> Inoltre, se in uno spazio di dimensione $n+1$ si hanno $n+1$ elementi, per dimostrare che sono una base basta dimostrare *una sola* tra indipendenza lineare e generazione dello spazio (l'altra segue).
### Proprietà chiave dei polinomi di Lagrange
Gli $n+1$ polinomi di Lagrange sono nel numero giusto per essere una base, quindi basta dimostrare che sono linearmente indipendenti. Si mette in luce la proprietà $\forall i,j=0,\dots,n$:
$$L_j(x_i)=\begin{cases}1 & \text{se } i=j\\0 & \text{se } i\neq j\end{cases}\qquad(*)$$
- Se $i=j$ numeratore e denominatore coincidono, quindi $L_j(x_j)=1$.
- Se $i\neq j$ il numeratore contiene il fattore $x_i-x_i=0$, quindi $L_j(x_i)=0$.

I polinomi sono costruiti apposta perché valga la $(*)$, da cui discende tutto il resto.
### Indipendenza lineare e base
Se $\alpha_0L_0(x)+\alpha_1L_1(x)+\dots+\alpha_nL_n(x)=0\quad\forall x\in\mathbb{R}$, allora in particolare, valutando nei nodi,
$$\alpha_0L_0(x_i)+\alpha_1L_1(x_i)+\dots+\alpha_nL_n(x_i)=0\qquad\forall i=0,\dots,n$$
Per la $(*)$ sopravvive solo il termine $i$-esimo:
$$\alpha_0L_0(x_i)+\dots+\alpha_nL_n(x_i)=\alpha_iL_i(x_i)=\alpha_i$$
Quindi $\alpha_i=0\ \forall i=0,\dots,n$: $L_0(x),\dots,L_n(x)$ sono linearmente indipendenti e, essendo $n+1$, sono una base di $\mathbb{R}_n[x]$.
### Esistenza
Si definisce
$$p(x)=y_0L_0(x)+y_1L_1(x)+\dots+y_nL_n(x)\in\mathbb{R}_n[x]$$
(appartiene a $\mathbb{R}_n[x]$ perché combinazione lineare di elementi della base). $\forall i=0,\dots,n$, per la $(*)$:
$$p(x_i)=y_0L_0(x_i)+y_1L_1(x_i)+\dots+y_nL_n(x_i)=y_iL_i(x_i)=y_i$$
### Unicità
Si suppone che $q(x)$ sia un altro polinomio **in $\mathbb{R}_n[x]$** con $q(x_i)=y_i\ \forall i=0,\dots,n$. Poiché $q(x)\in\mathbb{R}_n[x]$ e $L_0(x),\dots,L_n(x)$ sono una base, $\exists\beta_0,\dots,\beta_n\in\mathbb{R}$ tali che
$$q(x)=\beta_0L_0(x)+\beta_1L_1(x)+\dots+\beta_nL_n(x)$$
$\forall i=0,\dots,n$, usando di nuovo la $(*)$:
$$y_i=q(x_i)=\beta_0L_0(x_i)+\dots+\beta_nL_n(x_i)=\beta_iL_i(x_i)=\beta_i$$
Quindi $\beta_i=y_i$ e
$$q(x)=y_0L_0(x)+y_1L_1(x)+\dots+y_nL_n(x)=p(x)$$
Dunque $p(x)$ è l'unico polinomio in $\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\ \forall i=0,\dots,n$. $\blacksquare$
## Polinomio d'interpolazione
> [!quote] Definizione (polinomio d'interpolazione)
> Siano $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ con $x_0,x_1,\dots,x_n$ distinti. L'unico polinomio $p(x)\in\mathbb{R}_n[x]$ tale che $p(x_i)=y_i\ \forall i=0,\dots,n$ si chiama **polinomio d'interpolazione dei dati** $(x_0,y_0),\dots,(x_n,y_n)$, o anche **polinomio d'interpolazione dei valori** $y_0,\dots,y_n$ **sui nodi** $x_0,\dots,x_n$.

> [!quote] Definizione (interpolazione di una funzione)
> Se gli $y_i$ sono i valori nei punti $x_i$ di una funzione $f:[a,b]\to\mathbb{R}$, cioè se $y_i=f(x_i)\ \forall i=0,\dots,n$, allora $p(x)$ si chiama anche **polinomio d'interpolazione della funzione** $f(x)$ **sui nodi** $x_0,\dots,x_n$.

> [!warning] Attenzione a "$\mathbb{R}_n[x]$"
> Il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,\dots,x_n$ è *quell'unico polinomio in $\mathbb{R}_n[x]$* tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$. Senza la specifica "in $\mathbb{R}_n[x]$", cioè di grado $\leq n$, l'unicità cade: tra tutti i polinomi ce ne sono infiniti che passano per quei punti.

> [!question] Domanda tipica d'esame
> Che cos'è il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0,\dots,x_n$? Il docente la ripete spesso all'orale perché mette in difficoltà: la risposta richiede di *rielaborare* la definizione, ed è quella dell'avviso qui sopra.
### Forma canonica e forma di Lagrange
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
## Esempio: $\sin x$ nei nodi $0,\pi/6,\pi/4$
> [!example] Esempio
> Della funzione $\sin(x)$ sono noti i valori nei tre punti $x_0=0,\ x_1=\frac{\pi}{6},\ x_2=\frac{\pi}{4}$:
> $$\sin(x_0)=0,\qquad\sin(x_1)=\frac12,\qquad\sin(x_2)=\frac{\sqrt2}{2}$$
> Scrivere in forma canonica e in forma di Lagrange il polinomio d'interpolazione $p(x)$ di $\sin(x)$ sui nodi $x_0,x_1,x_2$.

Il polinomio cercato è l'unico $p(x)\in\mathbb{R}_2[x]$ tale che $p(0)=0$, $p(\pi/6)=\frac12$, $p(\pi/4)=\frac{\sqrt2}{2}$ (con $n=2$: tre nodi).
### Forma di Lagrange
$$p(x)=\sin(x_0)L_0(x)+\sin(x_1)L_1(x)+\sin(x_2)L_2(x)$$
$$=\sin(x_0)\frac{(x-x_1)(x-x_2)}{(x_0-x_1)(x_0-x_2)}+\sin(x_1)\frac{(x-x_0)(x-x_2)}{(x_1-x_0)(x_1-x_2)}+\sin(x_2)\frac{(x-x_0)(x-x_1)}{(x_2-x_0)(x_2-x_1)}$$
Il primo termine si elimina, perché $\sin(x_0)=0$. Sostituendo i nodi:
$$p(x)=\frac12\cdot\frac{x\left(x-\frac{\pi}{4}\right)}{\frac{\pi}{6}\left(\frac{\pi}{6}-\frac{\pi}{4}\right)}+\frac{\sqrt2}{2}\cdot\frac{x\left(x-\frac{\pi}{6}\right)}{\frac{\pi}{4}\left(\frac{\pi}{4}-\frac{\pi}{6}\right)}$$
Poiché $\frac{\pi}{6}\left(\frac{\pi}{6}-\frac{\pi}{4}\right)=-\frac{\pi^2}{72}$ e $\frac{\pi}{4}\left(\frac{\pi}{4}-\frac{\pi}{6}\right)=\frac{\pi^2}{48}$:
$$p(x)=\frac12\cdot\frac{x\left(x-\frac{\pi}{4}\right)}{-\frac{\pi^2}{72}}+\frac{\sqrt2}{2}\cdot\frac{x\left(x-\frac{\pi}{6}\right)}{\frac{\pi^2}{48}}$$
> [!warning] Forma di Lagrange all'esame
> Se si chiede la forma di Lagrange, non si deve andare avanti a semplificare: devono restare **in evidenza i coefficienti** ($\frac12$ e $\frac{\sqrt2}{2}$) davanti ai polinomi di Lagrange. Portare il coefficiente dentro (per esempio moltiplicando $\frac12$ per $-\frac{\pi^2}{72}$) distrugge la forma di Lagrange. Si può semplificare solo il polinomio $L_j$ in sé. Il termine con $\sin(x_0)=0$ si può omettere: si capisce che il suo coefficiente è nullo.
### Forma canonica
Una volta in forma di Lagrange ci si può staccare da essa e fare tutti i calcoli che si vogliono: si ribalta il denominatore, si sviluppano i prodotti e si raccolgono le potenze di $x$.
$$p(x)=-\frac{36}{\pi^2}\left(x^2-\frac{\pi}{4}x\right)+\frac{24\sqrt2}{\pi^2}\left(x^2-\frac{\pi}{6}x\right)=\frac{24\sqrt2-36}{\pi^2}x^2+\frac{9-4\sqrt2}{\pi}x$$
Il coefficiente di $x$ si ottiene da $\frac{36}{4\pi}-\frac{24\sqrt2}{6\pi}=\frac{9}{\pi}-\frac{4\sqrt2}{\pi}$. I coefficienti della forma canonica sono quindi
$$a_0=0\qquad a_1=\frac{9-4\sqrt2}{\pi}\qquad a_2=\frac{24\sqrt2-36}{\pi^2}$$
Il termine noto manca perché $x_0=0$ è un nodo e deve valere $p(0)=\sin(0)=0$. Si è ottenuto il vettore dei coefficienti canonici senza risolvere il sistema con la matrice di Vandermonde.
> [!info] Calcolatrice e angoli
> In matematica gli angoli si misurano sempre in **radianti**: non si scrive $\sin(30°)$ ma $\sin\frac{\pi}{6}$. Se si usa la calcolatrice scientifica, impostarla sui radianti (con i gradi si ottengono risultati sbagliati).
### Grafico e qualità dell'approssimazione
Il grafico di $\sin x$ (blu) con i tre punti d'interpolazione e della parabola $p(x)$ (rossa), che è un polinomio di $\mathbb{R}_2[x]$, mostra che:
- vicino ai nodi $p(x)$ approssima bene $\sin x$;
- allontanandosi dai nodi l'approssimazione peggiora rapidamente.

L'interpolazione approssima la funzione nell'intervallo che contiene i nodi (qui $[0,\pi/4]$): si può uscire dall'intervallo ma di poco, altrimenti diventa troppo rischioso. Per approssimare meglio si aggiungono altri nodi. Se i nodi sono troppo lontani tra loro, in mezzo le cose possono andare male.

Per stimare l'errore commesso in un punto $x$, per esempio nell'approssimare $\sin\frac14$ con $p\left(\frac14\right)$, esiste una formula (errore d'interpolazione) che permette di maggiorare $\left|p\left(\frac14\right)-\sin\frac14\right|$ con una quantità del tipo $10^{-7}$: la si vedrà alla lezione successiva.
