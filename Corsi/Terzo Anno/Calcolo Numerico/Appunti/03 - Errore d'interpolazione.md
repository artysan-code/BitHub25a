---
tags:
  - calcolo-numerico
  - interpolazione
  - errore-di-interpolazione
slide: []
---
# Errore d'interpolazione
Nella lezione precedente si è costruito il polinomio d'interpolazione ([[02 - Polinomi di Lagrange#Polinomio d'interpolazione]]) e si è visto sul grafico di $\sin x$ che approssima bene la funzione vicino ai nodi e male lontano da essi ([[02 - Polinomi di Lagrange#Grafico e qualità dell'approssimazione]]). Qui si risponde alla domanda rimasta aperta: quanto vale l'errore che si commette approssimando $f(x)$ con il suo polinomio d'interpolazione $p(x)$? La differenza $f(x)-p(x)$ si chiama **errore** o **resto** dell'interpolazione polinomiale.
## Funzioni di classe $C^{n+1}$
> [!quote] Definizione (classe $C^{n+1}[a,b]$)
> $$C^{n+1}[a,b]=\{g:[a,b]\to\mathbb{R}\ \mid\ g \text{ è derivabile } n+1 \text{ volte su } [a,b] \text{ e le derivate } g',g'',\dots,g^{(n+1)} \text{ sono funzioni continue su } [a,b]\}$$

- Non basta che le derivate esistano: le funzioni derivate, fino alla $(n+1)$-esima inclusa, devono essere **continue**. Va bene anche se $g$ ha derivate di ordine superiore: l'importante è che ci siano almeno quelle fino a $n+1$.
- Una funzione derivabile è continua. Quindi se $g^{(n+1)}$ esiste ed è continua, $g^{(n)}$ è derivabile e dunque continua, e così via a ritroso fino a $g$: basterebbe chiedere che sia continua l'ultima derivata.
- I polinomi sono di classe $C^\infty$: si possono derivare infinite volte, con tutte le derivate continue (da un certo ordine in poi sono nulle).
## Teorema
> [!quote] Teorema (errore d'interpolazione)
> Sia $f:[a,b]\to\mathbb{R}$ una funzione di classe $C^{n+1}[a,b]$ e sia $p(x)$ il polinomio d'interpolazione di $f(x)$ sugli $n+1$ nodi distinti $x_0,x_1,\dots,x_n\in[a,b]$. Allora $\forall x\in[a,b]\ \exists\,\xi=\xi(x)\in(a,b)$ tale che
> $$f(x)-p(x)=\frac{f^{(n+1)}(\xi)}{(n+1)!}(x-x_0)(x-x_1)\cdots(x-x_n)\qquad(\star)$$

- $p(x)$ è **l'unico polinomio di grado $\leq n$** tale che $p(x_i)=f(x_i)\ \forall i=0,\dots,n$: va ripetuto ogni volta, perché all'orale è la domanda su cui si sbaglia di più (vedi [[02 - Polinomi di Lagrange#Polinomio d'interpolazione]]).
- La notazione $\xi(x)$ ricorda che il punto $\xi$ **dipende da $x$**: per ogni $x$ esiste il suo $\xi$ che fa valere la $(\star)$, ma cambiando $x$ cambia anche $\xi$. Non c'è un unico $\xi$ che va bene per tutti gli $x$.
- La derivata $f^{(n+1)}$ esiste ed è continua perché $f\in C^{n+1}[a,b]$.
- $\xi$ sta nell'intervallo **aperto** $(a,b)$.
## Dimostrazione
Sia $x\in[a,b]$ fissato. Bisogna produrre un $\xi\in(a,b)$ che faccia valere la $(\star)$.
### Caso 1: $x$ coincide con uno dei nodi
In tal caso la formula $(\star)$ vale con un **qualsiasi** $\xi\in(a,b)$:
- il membro di sinistra è nullo per definizione di polinomio d'interpolazione, perché $p(x_i)=f(x_i)$;
- il membro di destra è nullo a prescindere dalla scelta di $\xi$, perché il fattore $(x-x_0)(x-x_1)\cdots(x-x_n)$ è zero.

Si ottiene $0=0$ per ogni $\xi$. Attenzione però: $\xi$ deve comunque stare in $(a,b)$ (non si può prendere $\xi=0$ se $0\notin(a,b)$).
### Caso 2: $x$ non coincide con uno dei nodi
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
### Teorema di Rolle
> [!quote] Teorema (Rolle)
> Sia $g:[a,b]\to\mathbb{R}$ continua su $[a,b]$ e derivabile su $(a,b)$, e supponiamo che $g(a)=g(b)$. Allora $\exists\,c\in(a,b)$ tale che $g'(c)=0$.

Geometricamente: c'è un punto interno in cui la retta tangente al grafico è orizzontale.
### Applicazione ripetuta di Rolle
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
### Calcolo di $z^{(n+1)}$
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
### Conclusione
Valutando nel punto $\xi$ in cui $z^{(n+1)}$ si annulla, e dimenticando $z$ che era solo una funzione ausiliaria:
$$0=z^{(n+1)}(\xi)=f^{(n+1)}(\xi)-\frac{r(x)}{\pi(x)}\,(n+1)!$$
$$\iff\quad\frac{r(x)}{\pi(x)}\,(n+1)!=f^{(n+1)}(\xi)$$
$$\iff\quad\underbrace{r(x)}_{f(x)-p(x)}=\frac{f^{(n+1)}(\xi)}{(n+1)!}\,\pi(x)$$
che è la $(\star)$, perché $\pi(x)=(x-x_0)(x-x_1)\cdots(x-x_n)$. $\blacksquare$

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il teorema sull'errore d'interpolazione. Traccia: caso in cui $x$ è un nodo; funzioni ausiliarie $\pi$, $r$, $z$ e perché $z$ ha almeno $n+2$ zeri; applicazione ripetuta di Rolle fino a $z^{(n+1)}$; calcolo di $p^{(n+1)}=0$ e $\pi^{(n+1)}=(n+1)!$.
## Come si usa il teorema
### Scelta dell'intervallo $[a,b]$
Il teorema garantisce che $\xi$ sta in $(a,b)$: più piccolo è l'intervallo, più precisa è l'informazione su $\xi$ e quindi migliore la stima. Conviene applicarlo sul **più piccolo intervallo che contiene i nodi e il punto $x$** in cui si vuole stimare l'errore. Non si può barare: i nodi devono stare in $[a,b]$ per ipotesi, e anche $x$, se si vuole una tesi su $x$.
### Moduli
Si usa spesso la proprietà del modulo di un prodotto: $\forall\alpha,\beta\in\mathbb{C}$
$$|\alpha\beta|=|\alpha|\cdot|\beta|$$
e più in generale $\forall\alpha_1,\dots,\alpha_k\in\mathbb{C}$, $|\alpha_1\alpha_2\cdots\alpha_k|=|\alpha_1|\cdot|\alpha_2|\cdots|\alpha_k|$. Quando si può (perché il segno di un fattore è noto), conviene **togliere i moduli**.
## Esempio 1: $\sin t$ sui nodi $0,\pi/6,\pi/4$
> [!example] Esempio
> Fissiamo un punto $t\in[0,1]$. Stimare l'errore che si commette approssimando $\sin(t)$ con $p(t)$, dove $p(x)$ è il polinomio d'interpolazione della funzione $\sin(x)$ sui nodi $x_0=0,\ x_1=\frac{\pi}{6},\ x_2=\frac{\pi}{4}$.

È il polinomio calcolato in [[02 - Polinomi di Lagrange#Forma di Lagrange]]. Si applica il teorema con $f(x)=\sin(x)\in C^\infty(\mathbb{R})$, $n=2$, $x=t$ e $[a,b]=[0,1]$, il più piccolo intervallo che contiene i nodi $x_0,x_1,x_2$ e il punto $t$ (si noti che $\frac{\pi}{4}<1$). Dal teorema si ha
$$|\sin(t)-p(t)|=\left|\frac{f'''(\xi)}{3!}(t-x_0)(t-x_1)(t-x_2)\right|\qquad(\xi\in(0,1))$$
Le derivate del seno sono cicliche con periodo 4: $f'=\cos$, $f''=-\sin$, $f'''=-\cos$. Quindi
$$|\sin(t)-p(t)|=\left|\frac{-\cos(\xi)}{6}\,t\left(t-\frac{\pi}{6}\right)\left(t-\frac{\pi}{4}\right)\right|$$
### Stima grezza
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
### Stima più precisa
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
### Osservazioni
> [!info] Non serve conoscere $p(x)$
> In nessuna delle due stime si è usata l'espressione esplicita di $p(x)$: l'errore si può stimare **prima** di calcolare il polinomio.

> [!warning] Quale stima usare all'esame
> Il docente consiglia la **stima grezza**, più semplice. La stima più precisa vale qualche punto bonus: conviene farla alla fine, se avanza tempo. Ma ha un limite: si è potuta fare perché $\omega$ ha grado 3, quindi $\omega'$ ha grado 2 e se ne trovano gli zeri. Con 4 nodi $\omega'$ avrebbe grado 3, e le sue radici non si calcolano facilmente. Il metodo raffinato funziona solo quando $\omega$ ha grado al massimo 3; quello grezzo funziona sempre.
## Esempio 2: $e^{x^2}$ sui nodi $0,\frac12,1$
> [!example] Esempio
> Consideriamo $f(x)=e^{x^2}$ e sia $p(x)$ il suo polinomio d'interpolazione sui nodi $x_0=0,\ x_1=\frac12,\ x_2=1$.
> (a) Fornire una stima dell'errore d'interpolazione $|f(x)-p(x)|\ \forall x\in[0,1]$, cioè determinare una costante $C$ tale che $|f(x)-p(x)|\leq C\ \forall x\in[0,1]$.
> (b) Stimare l'errore che si commette approssimando $\sqrt[9]{e}$ con $p\left(\frac13\right)$ senza calcolare né $\sqrt[9]{e}$ né $p\left(\frac13\right)$.

Nella (a) si chiede una **maggiorazione uniforme**: una sola costante $C$ che sta sopra il grafico di $|f(x)-p(x)|$ per tutti gli $x\in[0,1]$.
### (a)
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
### (b)
Si osserva che $\sqrt[9]{e}=e^{1/9}=e^{(1/3)^2}=f\left(\frac13\right)$. Ci sono due modi.
- **Usare la stima di (a).** Poiché $x=\frac13\in[0,1]$, vale la stima uniforme:
$$\left|\sqrt[9]{e}-p\left(\tfrac13\right)\right|=\left|e^{(1/3)^2}-p\left(\tfrac13\right)\right|\leq\frac{20e}{6}\cdot\frac{\sqrt3}{36}\approx0{,}436$$
- **Applicare il teorema direttamente con $x=\frac13$** (la cosa migliore), sempre sull'intervallo $[0,1]$, il più piccolo che contiene $x=\frac13$ e i nodi $x_0,x_1,x_2$:
$$\left|\sqrt[9]{e}-p\left(\tfrac13\right)\right|=\left|e^{(1/3)^2}-p\left(\tfrac13\right)\right|=\left|\frac{f'''(\xi)}{3!}\left(\frac13-0\right)\left(\frac13-\frac12\right)\left(\frac13-1\right)\right|$$
$$=\frac{|f'''(\xi)|}{6}\cdot\frac13\cdot\frac16\cdot\frac23\leq\frac{20e}{6}\cdot\frac13\cdot\frac16\cdot\frac23\approx0{,}336$$

Qui il miglioramento non è eccezionale, ma in generale applicare il teorema direttamente nel punto che interessa è la strategia migliore e può dare guadagni notevoli.
## Esercizi
Esercizi lasciati per la lezione successiva:
- **1.4** Data $f(x)=\arctan(x)$: (a) scrivere in forma di Lagrange e in forma canonica il polinomio d'interpolazione $p(x)$ di $f(x)$ sui nodi $x_0=0,\ x_1=1,\ x_2=\sqrt3$; (b) fissato $t\in[0,2]$, stimare l'errore $|f(t)-p(t)|$.
- **1.5** Per ogni fissato $t\in[0,1]$, stimare l'errore che si commette approssimando $\sin(t)$ con $p(t)$, dove $p(x)$ interpola $\sin(x)$ sui nodi $0,\ \frac{\pi}{10},\ \frac{\pi}{6},\ \frac{\pi}{4},\ \frac{3\pi}{10}$. Confrontare con le stime dell'esempio 1; per risolverlo non serve conoscere $p(x)$.
- **1.6** Stimare l'errore che si commette approssimando $\sqrt2$ con $p(2)$, dove $p(x)$ interpola $\sqrt x$ sui nodi $1{,}69;\ 1{,}7689;\ 1{,}8769;\ 1{,}96;\ 2{,}0449;\ 2{,}1609;\ 2{,}25$, senza calcolare né $\sqrt2$ né $p(2)$.
- **1.7** Stimare l'errore che si commette approssimando $\cos(1)$ con $p(1)$, dove $p(x)$ interpola $\cos(x)$ sui nodi $0,\ \frac{\pi}{6},\ \frac{\pi}{4},\ \frac{\pi}{3},\ \frac{\pi}{2}$, senza calcolare né $\cos(1)$ né $p(1)$.
