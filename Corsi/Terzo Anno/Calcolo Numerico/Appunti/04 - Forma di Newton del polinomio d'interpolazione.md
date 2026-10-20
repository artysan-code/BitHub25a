---
tags:
  - calcolo-numerico
  - interpolazione
  - differenze-divise
slide: []
---
# Forma di Newton del polinomio d'interpolazione
Finora si sono viste due forme del polinomio d'interpolazione, la forma canonica e la forma di Lagrange ([[02 - Polinomi di Lagrange#Forma canonica e forma di Lagrange]]), e l'errore che si commette usandolo per approssimare una funzione ([[03 - Errore d'interpolazione#Teorema]]). Qui si introduce una terza forma, la **forma di Newton**, costruita con le **differenze divise**. Negli esercizi si può partire da questa invece che da quella di Lagrange, e anche da qui la forma canonica si ottiene sviluppando i calcoli. In più la forma di Newton dà un algoritmo efficiente per **valutare** il polinomio in un punto, di cui si calcola il costo computazionale esatto.
## Differenze divise
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
## Teorema
> [!quote] Teorema (forma di Newton)
> Sia $f:[a,b]\to\mathbb{R}$ una funzione e siano $x_0,x_1,\dots,x_n\in[a,b]$ nodi distinti. Allora il polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0,x_1,\dots,x_n$ è dato da
> $$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+\dots+f[x_0,x_1,\dots,x_n](x-x_0)(x-x_1)\cdots(x-x_{n-1})\qquad(N)$$
> La $(N)$ si chiama **forma di Newton** di $p(x)$.

Il teorema non è stato dimostrato a lezione.
- L'ultimo prodotto si ferma a $(x-x_{n-1})$: se comparisse anche $(x-x_n)$ il polinomio avrebbe grado $n+1$.
- $p(x)$ è **l'unico polinomio di grado $\leq n$** tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$. Il docente ripete questa domanda a ogni lezione perché è tipica dell'orale; si veda [[02 - Polinomi di Lagrange#Polinomio d'interpolazione]].
### Le tre forme a confronto
Le tre forme scrivono lo stesso polinomio come combinazione lineare degli elementi di tre basi diverse di $\mathbb{R}_n[x]$.

| Forma | Base | Coefficienti |
|---|---|---|
| canonica: $p(x)=a_0+a_1x+a_2x^2+\dots+a_nx^n$ | base canonica $1,x,x^2,\dots,x^n$ | soluzione di $V(x_0,x_1,\dots,x_n)\begin{pmatrix}a_0\\\vdots\\a_n\end{pmatrix}=\begin{pmatrix}f(x_0)\\\vdots\\f(x_n)\end{pmatrix}$ |
| di Lagrange: $p(x)=f(x_0)L_0(x)+f(x_1)L_1(x)+\dots+f(x_n)L_n(x)$ | base di Lagrange $L_0(x),L_1(x),\dots,L_n(x)$ | i valori $f(x_0),\dots,f(x_n)$ |
| di Newton $(N)$ | base di Newton $1,\ x-x_0,\ (x-x_0)(x-x_1),\ \dots,\ (x-x_0)(x-x_1)\cdots(x-x_{n-1})$ | le differenze divise $f[x_0],\ f[x_0,x_1],\ \dots,\ f[x_0,\dots,x_n]$ |

Che gli elementi della base di Newton formino una base non è stato dimostrato, ma si può dimostrare. Nella pratica nessuno risolve il sistema con la matrice di Vandermonde: si scrive la forma di Lagrange o quella di Newton e si sviluppano i calcoli per ottenere la forma canonica.
## Corollario: simmetria delle differenze divise
> [!quote] Corollario
> Sia $f:[a,b]\to\mathbb{R}$ una funzione e siano $x_0,x_1,\dots,x_n\in[a,b]$ nodi distinti. Allora $f[x_0,x_1,\dots,x_n]$ non cambia se vengono permutati i suoi $n+1$ argomenti, cioè
> $$f[x_0,\dots,x_n]=f[x_{\sigma(0)},\dots,x_{\sigma(n)}]\qquad\forall\,\sigma \text{ permutazione di } \{0,\dots,n\}$$

In altre parole, l'ordine dei punti dentro le parentesi quadre non conta.
### Dimostrazione
Sia $\sigma$ una permutazione di $\{0,\dots,n\}$.
- Usando la $(N)$ del polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0,\dots,x_n$ si ottiene la $(N)$.
- Usando successivamente la $(N)$ con i nodi $x_{\sigma(0)},\dots,x_{\sigma(n)}$, si ottiene che il polinomio d'interpolazione di $f(x)$ sui nodi $x_{\sigma(0)},\dots,x_{\sigma(n)}$, che **coincide con il precedente** perché la definizione di polinomio d'interpolazione non dipende dall'ordine dei nodi, è dato da
$$p(x)=f[x_{\sigma(0)}]+f[x_{\sigma(0)},x_{\sigma(1)}](x-x_{\sigma(0)})+\dots+f[x_{\sigma(0)},x_{\sigma(1)},\dots,x_{\sigma(n)}](x-x_{\sigma(0)})(x-x_{\sigma(1)})\cdots(x-x_{\sigma(n-1)})$$

In entrambe le scritture il termine di grado massimo $x^n$ si ottiene solo dall'ultimo addendo, prendendo $x$ da tutti gli $n$ fattori. Vediamo dunque che $f[x_0,\dots,x_n]$ e $f[x_{\sigma(0)},\dots,x_{\sigma(n)}]$ sono entrambi il **coefficiente direttore** di $p(x)$, cioè il coefficiente $a_n$ davanti a $x^n$. Essendo il coefficiente direttore dello stesso polinomio, devono essere uguali:
$$f[x_0,\dots,x_n]=f[x_{\sigma(0)},\dots,x_{\sigma(n)}]\qquad\blacksquare$$
## Esempio: $\sqrt x$ sui nodi $0,\ 0{,}16,\ 0{,}64,\ 1$
> [!example] Esempio
> Scrivere in forma canonica e in forma di Newton il polinomio d'interpolazione $p(x)$ della funzione $f(x)=\sqrt x$ sui nodi $x_0=0,\ x_1=0{,}16,\ x_2=0{,}64,\ x_3=1$.

Si inizia dalla forma di Newton, da cui poi si otterrà la forma canonica semplicemente sviluppando i calcoli (come si faceva con la forma di Lagrange). Per il teorema, la forma di Newton di $p(x)$ è
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+f[x_0,x_1,x_2,x_3](x-x_0)(x-x_1)(x-x_2)\qquad(\star)$$
L'unica cosa da fare è calcolare le quattro differenze divise che fanno da coefficienti.
### La tabella delle differenze divise
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
### Calcolo
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
### Forma di Newton e forma canonica
Sostituendo i valori riquadrati nella $(\star)$ si ottiene la forma di Newton di $p(x)$ (il primo termine è nullo e si può eliminare):
$$p(x)=\frac52x-\frac{125}{48}x(x-0{,}16)+\frac{6875}{3024}x(x-0{,}16)(x-0{,}64)$$
Sviluppando i calcoli si ottiene la forma canonica:
$$p(x)=\frac{6875}{3024}x^3-\frac{13375}{3024}x^2+\frac{2381}{756}x$$
Manca il termine noto perché $x_0=0$ è un nodo e $p(0)=\sqrt0=0$. Si verifica che $p(0{,}16)=0{,}4$, $p(0{,}64)=0{,}8$, $p(1)=1$.
### Osservazione: dati senza una funzione
> [!info] Forma di Newton di dati qualsiasi
> Supponiamo che siano dati i punti $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)\in\mathbb{R}^2$ con $x_0,x_1,\dots,x_n$ distinti. I numeri $y_0,y_1,\dots,y_n$ possono **sempre** essere interpretati come i valori in $x_0,x_1,\dots,x_n$ di una qualche funzione $f:[a,b]\to\mathbb{R}$. Quindi ha perfettamente senso parlare di forma di Newton del polinomio d'interpolazione dei dati $(x_0,y_0),\dots,(x_n,y_n)$ anche quando non viene specificata una funzione $f(x)$ tale che $f(x_i)=y_i\ \forall i=0,\dots,n$: in tal caso basta immaginarsi una tale funzione. Non serve esplicitarla: della funzione si usano solo i valori nei nodi, che sono gli $y_i$, e con quelli si costruisce la tabella.

> [!warning] Da quale forma partire all'esame
> Quando si chiedono più forme dello stesso polinomio si può partire indifferentemente dalla forma di Lagrange o da quella di Newton, ricavare da quella la forma canonica sviluppando i calcoli e calcolare l'altra a parte. Non si parte mai dalla forma canonica, che è sempre la più sconveniente.
## Algoritmo di valutazione in un punto del polinomio d'interpolazione
Sia $f:[a,b]\to\mathbb{R}$, siano $x_0,\dots,x_n\in[a,b]$ nodi distinti e sia $t\in\mathbb{R}$. Si costruisce un algoritmo per calcolare $p(t)$, dove $p(x)$ è il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,\dots,x_n$. Valutare un polinomio in un punto sembra un'operazione banale, ma farlo in modo efficiente è fondamentale.

Per semplicità si vede l'algoritmo nel caso $n=3$, che basta a mostrare tutte le idee. La forma di Newton di $p(x)$ è in questo caso
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+f[x_0,x_1,x_2,x_3](x-x_0)(x-x_1)(x-x_2)\qquad(\nu)$$
($\nu$, "ni", è la $n$ greca, iniziale di Newton.)
### Prima parte: le differenze divise
La prima parte è **indipendente dal punto $t$** in cui si deve valutare $p(x)$. Consiste nel calcolare le differenze divise che fanno da coefficienti nella $(\nu)$, e lo si fa con la tabella delle differenze divise come nell'esempio precedente. Non c'è un modo più efficiente.

**Costo computazionale della prima parte.** La prima colonna della tabella contiene i dati e non è da calcolare. Nel caso $n=3$ si devono calcolare in totale $6$ differenze divise; in generale sono
$$\frac{n(n+1)}{2}=\sum_{i=1}^{n}i=\frac{n^2-n}{2}+n$$
cioè il numero di elementi della parte triangolare inferiore, **inclusa la diagonale**, di una matrice $n\times n$. I due modi di contarli:
- per righe: $1+2+\dots+n=\frac{n(n+1)}{2}$;
- la matrice ha $n^2$ elementi; togliendo gli $n$ della diagonale restano due metà uguali (parte strettamente inferiore e strettamente superiore), quindi $\frac{n^2-n}{2}$, a cui si riaggiunge la diagonale.

Per ogni differenza divisa si fanno **2 sottrazioni e 1 divisione**. Totale costo della prima parte:
- $n(n+1)$ sottrazioni (S);
- $\frac{n(n+1)}{2}$ divisioni (D).
### Seconda parte: il metodo di Ruffini–Horner
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
### Costo totale dell'algoritmo
$$C(n)=\underbrace{n(n+1)\,A+\frac{n(n+1)}{2}\,D}_{\text{1ª parte}}+\underbrace{2n\,A+n\,M}_{\text{2ª parte}}=(n^2+3n)\,A+n\,M+\left(\frac{n^2}{2}+\frac n2\right)D$$
$$\approx n^2\,A+\frac{n^2}{2}\,D\qquad\left(\approx\frac{3n^2}{2}\text{ operazioni}\right)$$
L'approssimazione trascura i termini di ordine inferiore ma conserva le **costanti** davanti a $n^2$.

> [!info] Perché le costanti contano
> Il docente preferisce calcolare il costo esatto invece di scrivere solo $O(n^2)$: $O(n^2)$ dice che il costo è limitato da una costante per $n^2$, ma una costante di 500 milioni è ben diversa da una di $\frac12$. Anche un algoritmo lineare con costante 5 miliardi può essere peggiore di uno quadratico con costante $\frac12$.
### Valutazione in $m$ punti
Poiché la prima parte dell'algoritmo consiste nel calcolo delle differenze divise ed è indipendente dal punto $t$ in cui deve essere valutato $p(x)$, per valutare $p(x)$ in $m$ punti $t_1,\dots,t_m\in\mathbb{R}$ si fa la prima parte **una volta sola** e poi si ripete $m$ volte la seconda parte. Costo complessivo:
$$C_m(n)=\underbrace{n(n+1)\,A+\frac{n(n+1)}{2}\,D}_{\text{1ª parte}}+\underbrace{m\,(2n\,A+n\,M)}_{\text{2ª parte}}=(n^2+2nm+n)\,A+nm\,M+\left(\frac{n^2}{2}+\frac n2\right)D$$
$$\approx(n^2+2nm)\,A+nm\,M+\frac{n^2}{2}\,D$$

> [!warning] Attenzione alle approssimazioni
> Nella stima di $C(n)$ le moltiplicazioni erano sparite, perché $n\,M$ è di ordine inferiore a $n^2$. Ma valutando in $m$ punti diventano $nm\,M$, e $m$ è una grandezza **indipendente** da $n$: con 20 nodi e 5000 punti di valutazione è $m$ a contare di più. Si può trascurare $n$ rispetto a $n^2$, ma non $nm$. Chi fosse partito dall'approssimazione $C(n)\approx n^2A+\frac{n^2}{2}D$ e l'avesse moltiplicata avrebbe perso le $nm$ moltiplicazioni, e l'algoritmo risulterebbe più lento del previsto.

> [!question] Domanda tipica d'esame
> Descrivere l'algoritmo per valutare in un punto $t$ il polinomio d'interpolazione usando la forma di Newton (tabella delle differenze divise e metodo di Ruffini–Horner) e calcolarne il costo computazionale. Come cambiano l'algoritmo e il costo se si deve valutare il polinomio in $m$ punti?
## Esercizi
Esercizi lasciati alla fine della parte sulla forma di Newton:
- **1.8** Scrivere in forma canonica e in forma di Newton il polinomio d'interpolazione di $f(x)=\cos\left(\frac{\pi}{2}x\right)\log_2(x)$ sui nodi $x_0=1,\ x_1=2,\ x_2=4,\ x_3=8$.
- **1.9** Scrivere in forma canonica, in forma di Lagrange e in forma di Newton il polinomio d'interpolazione dei valori $y_0=0,\ y_1=3,\ y_2=-3$ sui nodi $x_0=0,\ x_1=1,\ x_2=2$.
