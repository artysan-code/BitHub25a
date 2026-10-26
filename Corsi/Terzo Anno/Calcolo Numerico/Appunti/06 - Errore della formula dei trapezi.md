---
tags:
  - calcolo-numerico
  - integrazione-numerica
slide: []
---
# Errore della formula dei trapezi
Nella lezione precedente si è ricavata la formula dei trapezi $I_n$ per approssimare $\int_a^bf(x)\,dx$ ([[05 - Aggiunta di un nodo e formula dei trapezi#Formula dei trapezi]]). Qui si vuole capire quale **errore** (o **resto**) si commette approssimando $\int_a^bf(x)\,dx$ con $I_n$. È una lezione teorica, definita dal docente "un pochino tosta": un lemma, che generalizza il teorema della media integrale, e il teorema sull'errore, la cui dimostrazione usa il lemma e il teorema sull'errore d'interpolazione ([[03 - Errore d'interpolazione#Teorema]]). Alla fine, un esempio con $\int_0^1\sqrt{\cos x}\,dx$.

> [!info] Lemma, teorema, corollario
> Il **teorema** è il risultato principale. Il **lemma** è un risultato ausiliario, usato per dimostrare un altro risultato; spesso è tecnico, ma può avere interesse proprio. Il **corollario** è una conseguenza di un teorema.
## Lemma
> [!quote] Lemma
> Siano $\omega,\alpha,\beta:[a,b]\to\mathbb{R}$ tali che:
> - $\omega(x)$ è continua e $\geq0$ su $[a,b]$;
> - $\alpha(x)$ e $\beta(x)\,\omega(x)$ sono continue su $[a,b]$;
> - $m\leq\beta(x)\leq M$ $\forall x\in[a,b]$, dove $m$ e $M$ sono il minimo e il massimo di $\alpha(x)$ su $[a,b]$.
>
> Allora $\exists\,\eta\in[a,b]$ tale che
> $$\int_a^b\beta(x)\,\omega(x)\,dx=\alpha(\eta)\int_a^b\omega(x)\,dx$$

- $\omega$ ha il ruolo di **funzione peso** (*weight*).
- Il minimo $m$ e il massimo $M$ di $\alpha$ esistono per il **teorema di Weierstrass**: una funzione continua su un intervallo chiuso e limitato vi assume massimo e minimo assoluti.
- Attenzione: si chiede che sia continuo il **prodotto** $\beta(x)\,\omega(x)$, non $\beta(x)$ da sola. Sarà essenziale nella dimostrazione del teorema.
### Il teorema della media integrale come caso particolare
> [!quote] Teorema (della media integrale)
> Sia $g:[a,b]\to\mathbb{R}$ una funzione continua. Allora $\exists\,\eta\in[a,b]$ tale che
> $$\int_a^bg(x)\,dx=g(\eta)\,(b-a)$$

Geometricamente: esiste un punto $\eta$ tale che l'area del rettangolo di base $[a,b]$ e altezza $g(\eta)$ è uguale all'area sottesa dal grafico di $g$. L'area che il rettangolo ha in più rispetto al grafico bilancia esattamente quella che ha in meno.

Il lemma è una **generalizzazione** del teorema della media integrale: per ottenerlo basta prendere nel lemma
$$\omega(x)=1,\qquad\beta(x)=\alpha(x)=g(x)$$
$\omega\equiv1$ è continua e $\geq0$, $\int_a^b1\,dx=b-a$; $\alpha=g$ e $\beta\,\omega=g$ sono continue; $\beta=\alpha$ sta ovviamente tra il minimo e il massimo di $\alpha$.
### Dimostrazione
Siccome $\omega(x)\geq0$ e $m\leq\beta(x)\leq M$ per ogni $x\in[a,b]$, moltiplicando i membri della disuguaglianza per $\omega(x)$ (che è $\geq0$, quindi non inverte le disuguaglianze) risulta
$$m\,\omega(x)\leq\beta(x)\,\omega(x)\leq M\,\omega(x)\qquad\forall x\in[a,b]$$
Graficamente, il grafico di $y=\beta(x)\,\omega(x)$ sta tra quelli di $y=m\,\omega(x)$ e $y=M\,\omega(x)$. Per la **monotonia dell'integrale** (se $g(x)\leq h(x)$ $\forall x\in[a,b]$ allora $\int_a^bg\leq\int_a^bh$):
$$m\int_a^b\omega(x)\,dx=\int_a^bm\,\omega(x)\,dx\leq\int_a^b\beta(x)\,\omega(x)\,dx\leq\int_a^bM\,\omega(x)\,dx=M\int_a^b\omega(x)\,dx$$
Sia ora $z:[a,b]\to\mathbb{R}$ la funzione ausiliaria
$$z(y)=\alpha(y)\int_a^b\omega(x)\,dx$$
dove $\int_a^b\omega(x)\,dx$ è una **costante** $\geq0$ (la variabile è $y$). $z$ è continua su $[a,b]$ perché $\alpha$ lo è per ipotesi, e siccome la costante è $\geq0$ il suo minimo è $m\int_a^b\omega$ e il suo massimo $M\int_a^b\omega$. Per il **teorema dei valori intermedi**, $z$ assume su $[a,b]$ tutti i valori compresi fra il suo minimo e il suo massimo. Per la disuguaglianza sopra, $\int_a^b\beta(x)\,\omega(x)\,dx$ è uno di questi valori, quindi $\exists\,\eta\in[a,b]$ tale che
$$z(\eta)=\alpha(\eta)\int_a^b\omega(x)\,dx=\int_a^b\beta(x)\,\omega(x)\,dx$$
che è la tesi. $\blacksquare$
## Teorema sull'errore della formula dei trapezi
> [!quote] Teorema (errore della formula dei trapezi)
> Sia $f:[a,b]\to\mathbb{R}$ di classe $C^2[a,b]$ e sia $I_n$ la formula dei trapezi di ordine $n$ e passo $h=\frac{b-a}{n}$ per approssimare $\int_a^bf(x)\,dx$. Allora $\exists\,\eta\in[a,b]$ tale che
> $$\int_a^bf(x)\,dx-I_n=-\frac{(b-a)\,f''(\eta)}{12}\,h^2$$

> [!info] Definizione di $C^2[a,b]$
> $C^2[a,b]$ è l'insieme delle funzioni derivabili due volte su $[a,b]$ con tutte le derivate fino alla seconda inclusa continue (basta chiedere che sia continua la derivata seconda: le precedenti, essendo derivabili, lo sono già). Il docente avverte che la definizione può essere chiesta all'orale. Non va confusa con i polinomi: $f$ è una funzione qualsiasi di classe $C^2$.

Il teorema dà la **differenza** tra valore esatto e approssimato, senza modulo, come il teorema sull'errore d'interpolazione. Il modulo si mette poi negli esercizi, quando si stima l'errore.
### Dimostrazione
Sia $x_j=a+jh$, $j=0,1,\dots,n$, e sia $s(x)$ la funzione **lineare a tratti** (la spezzata) che congiunge i punti $(x_j,f(x_j))$, per cui
$$I_n=\int_a^bs(x)\,dx$$
(è la definizione di $I_n$, prima di sviluppare i calcoli che portano alla formula finale).

> [!info] Osservazione cruciale
> Per ogni fissato indice $0\leq j\leq n-1$, la funzione $s(x)$ coincide sull'intervallo $[x_j,x_{j+1}]$ con il **polinomio d'interpolazione** di $f(x)$ relativo ai due nodi $x_j$ e $x_{j+1}$. Questo, ricordiamolo, è per definizione l'unico polinomio di grado $\leq1$ che nei nodi $x_j,x_{j+1}$ assume i valori $f(x_j),f(x_{j+1})$. Infatti $s(x)$ coincide su $[x_j,x_{j+1}]$ con la retta (un polinomio di grado $\leq1$) che passa per $(x_j,f(x_j))$ e $(x_{j+1},f(x_{j+1}))$, dunque per **unicità** deve coincidere con il polinomio d'interpolazione suddetto. Su tutto $[a,b]$ invece $s(x)$ non è un polinomio: ha dei punti angolosi.

Si porta tutto sotto un unico integrale e lo si spezza sui sottointervalli:
$$\int_a^bf(x)\,dx-I_n=\int_a^bf(x)\,dx-\int_a^bs(x)\,dx=\int_a^b\big[f(x)-s(x)\big]\,dx=\sum_{j=0}^{n-1}\int_{x_j}^{x_{j+1}}\big[f(x)-s(x)\big]\,dx$$
Su ogni $[x_j,x_{j+1}]$ si applica il teorema sull'errore d'interpolazione con due nodi (lecito perché $f\in C^2$): per ogni $x\in[x_j,x_{j+1}]$ esiste $\xi_j(x)\in(x_j,x_{j+1})$ tale che $f(x)-s(x)=\frac{f''(\xi_j(x))}{2!}(x-x_j)(x-x_{j+1})$. Quindi
$$=\sum_{j=0}^{n-1}\int_{x_j}^{x_{j+1}}\frac{f''(\xi_j(x))}{2}(x-x_j)(x-x_{j+1})\,dx$$
Il teorema si può applicare solo su $[x_j,x_{j+1}]$: fuori da lì $s(x)$ non è più quel polinomio d'interpolazione.

> [!warning] Perché $\xi_j(x)$ e non $\xi_j$
> Il punto $\xi_j(x)$ **dipende da $x$**: cambia $x$, cambia $\xi_j$. Scrivere solo $\xi_j$ fa venire la tentazione di portare $f''(\xi_j)$ fuori dall'integrale, cosa che non si può fare.

Per $x\in[x_j,x_{j+1}]$ il fattore $(x-x_j)(x-x_{j+1})$ è sempre $\leq0$ (positivo per negativo). Al lemma serve un peso $\geq0$; quello che conta davvero è che **non cambi segno** nell'intervallo, quindi basta portare fuori un meno e scaricarlo sul fattore negativo:
$$=-\sum_{j=0}^{n-1}\int_{x_j}^{x_{j+1}}\frac{f''(\xi_j(x))}{2}(x-x_j)(x_{j+1}-x)\,dx$$
#### Applicazione del lemma
Si applica il lemma sull'intervallo $[x_j,x_{j+1}]$ con
$$\omega(x)=\frac12(x-x_j)(x_{j+1}-x),\qquad\beta(x)=f''(\xi_j(x)),\qquad\alpha(x)=f''(x)$$
($\frac12$ è incluso in $\omega$, essendo positivo). $\beta$ e $\alpha$ sono funzioni **diverse**: $\beta$ è la composizione di $f''$ con $x\mapsto\xi_j(x)$, $\alpha$ è semplicemente $f''$. Verifica delle ipotesi:
- $\omega(x)$ è un polinomio di grado 2 (una parabola), quindi continua, ed è $\geq0$ su $[x_j,x_{j+1}]$ perché $x-x_j\geq0$ e $x_{j+1}-x\geq0$.
- $\alpha(x)=f''(x)$ è continua su $[x_j,x_{j+1}]$ perché $f\in C^2[a,b]$, e quindi a maggior ragione $f\in C^2[x_j,x_{j+1}]$.
- $\beta(x)\,\omega(x)$ è continua su $[x_j,x_{j+1}]$. Qui bisogna **guardare indietro** nei passaggi: per costruzione
$$\beta(x)\,\omega(x)=\frac{f''(\xi_j(x))}{2}(x-x_j)(x_{j+1}-x)=-\big[f(x)-s(x)\big]$$
ed $f$ (di classe $C^2$) e $s$ (un segmento su questo intervallo) sono continue.
- Per ogni $x\in[x_j,x_{j+1}]$ deve essere $m_j\leq\beta(x)\leq M_j$, dove $m_j$ e $M_j$ sono il minimo e il massimo di $\alpha$ su $[x_j,x_{j+1}]$. Questo è vero perché, fissato $x$, il punto $\xi_j(x)$ sta in $(x_j,x_{j+1})$, e quindi
$$m_j=\min_{y\in[x_j,x_{j+1}]}f''(y)\leq f''(\xi_j(x))\leq\max_{y\in[x_j,x_{j+1}]}f''(y)=M_j$$

> [!warning] L'errore tipico all'orale
> Il ragionamento sbagliato che il docente sente spesso all'orale: "$f''$ è continua e $\xi_j(x)$ sta in $[x_j,x_{j+1}]$, quindi $\beta(x)=f''(\xi_j(x))$ è continua, e moltiplicata per $\omega$ continua dà un prodotto continuo". L'errore è che **non è garantito che $x\mapsto\xi_j(x)$ sia continua**: del punto $\xi_j(x)$ si sa solo che sta nell'intervallo. Quindi non si sa se $\beta$ sia continua (si può dimostrare che esiste una scelta di $\xi_j(x)$ che la rende continua, ma servirebbe un altro lemma). Per questo il lemma chiede la continuità del prodotto $\beta\,\omega$, che si verifica guardando indietro: $\beta\,\omega=-(f-s)$.

Il lemma dà allora un punto $\eta_j\in[x_j,x_{j+1}]$ (da non confondere con l'$\eta$ della tesi del teorema) tale che
$$\int_{x_j}^{x_{j+1}}\frac{f''(\xi_j(x))}{2}(x-x_j)(x_{j+1}-x)\,dx=f''(\eta_j)\int_{x_j}^{x_{j+1}}\frac{(x-x_j)(x_{j+1}-x)}{2}\,dx$$
quindi
$$\int_a^bf(x)\,dx-I_n=-\sum_{j=0}^{n-1}f''(\eta_j)\int_{x_j}^{x_{j+1}}\frac{(x-x_j)(x_{j+1}-x)}{2}\,dx\qquad\eta_j\in[x_j,x_{j+1}]$$
Secondo il docente, superato questo passaggio il resto è facile.
#### Calcolo dell'integrale
L'integrale rimasto è quello di una parabola. Con la sostituzione $t=x-x_j$ ($dt=dx$, $x=t+x_j$; per $x=x_j$ è $t=0$, per $x=x_{j+1}$ è $t=x_{j+1}-x_j=h$) si ha $x_{j+1}-x=x_{j+1}-x_j-t=h-t$, quindi
$$\int_{x_j}^{x_{j+1}}\frac{(x-x_j)(x_{j+1}-x)}{2}\,dx=\int_0^h\frac{t(h-t)}{2}\,dt=\int_0^h\left(\frac h2t-\frac{t^2}{2}\right)dt=\left[\frac{ht^2}{4}-\frac{t^3}{6}\right]_0^h=\frac{h^3}{4}-\frac{h^3}{6}=\frac{h^3}{12}$$
Il risultato **non dipende da $j$**: si porta fuori dalla somma. Moltiplicando e dividendo per $n$:
$$\int_a^bf(x)\,dx-I_n=-\sum_{j=0}^{n-1}f''(\eta_j)\,\frac{h^3}{12}=-\frac{h^3\,n}{12}\cdot\frac1n\sum_{j=0}^{n-1}f''(\eta_j)$$
#### La media aritmetica
$\frac1n\sum_{j=0}^{n-1}f''(\eta_j)$ è la **media aritmetica** dei numeri $f''(\eta_0),\dots,f''(\eta_{n-1})$. Di questi numeri non si sa nulla, se non che sono valori di $f''$ in punti di $[a,b]$: stanno quindi tra il minimo $m$ e il massimo $M$ di $f''$ su $[a,b]$ (presi su tutto $[a,b]$, perché ogni $\eta_j$ sta in un sottointervallo diverso). Anche la loro media aritmetica sta tra $m$ e $M$, perché la media sta sempre tra il più piccolo e il più grande dei numeri di cui si fa la media. $f''$ è continua, quindi per il teorema dei valori intermedi $\exists\,\eta\in[a,b]$ tale che
$$\frac1n\sum_{j=0}^{n-1}f''(\eta_j)=f''(\eta)$$
Infine $h\,n=b-a$, quindi $h^3n=h^2(b-a)$ e
$$\int_a^bf(x)\,dx-I_n=-\frac{h^2(b-a)}{12}\,f''(\eta)\qquad\blacksquare$$
Secondo il docente è una delle dimostrazioni più difficili del corso (ce ne sarà una ancora più difficile alla fine): il lemma è un po' cervellotico e bisogna guardare indietro nei passaggi.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il teorema sull'errore della formula dei trapezi. Traccia: $s(x)$ coincide su ogni $[x_j,x_{j+1}]$ con il polinomio d'interpolazione di $f$ sui nodi $x_j,x_{j+1}$ (unicità); errore d'interpolazione con $\xi_j(x)$; cambio di segno; lemma con $\omega=\frac12(x-x_j)(x_{j+1}-x)$, $\beta=f''(\xi_j(x))$, $\alpha=f''$ e verifica delle ipotesi (continuità di $\beta\omega=-(f-s)$, non di $\beta$); integrale $\frac{h^3}{12}$; media aritmetica e valori intermedi.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il lemma che generalizza il teorema della media integrale, e mostrare come se ne ricava il teorema della media integrale.
## Esempio: $\int_0^1\sqrt{\cos x}\,dx$
> [!example] Esempio
> - (a) Calcolare l'approssimazione di $\int_0^1\sqrt{\cos x}\,dx$ con $I_{10}$, la formula dei trapezi di ordine 10.
> - (b) Stimare l'errore che si commette approssimando $\int_0^1\sqrt{\cos x}\,dx$ con $I_{10}$.

È l'integrale citato all'inizio del corso: nonostante l'apparenza innocua, $\sqrt{\cos x}$ non ha una primitiva elementare e l'integrale non si sa calcolare esattamente, va approssimato.
### Punto (a)
Si applica la formula
$$I_n=h\left[\frac{f(a)+f(b)}{2}+\sum_{j=1}^{n-1}f(x_j)\right],\qquad h=\frac{b-a}{n},\quad x_j=a+jh,\ j=0,\dots,n$$
con $[a,b]=[0,1]$, $f(x)=\sqrt{\cos x}$, $n=10$, $h=\frac1{10}$ e $x_j=jh=\frac{j}{10}$, $j=0,\dots,10$:
$$I_{10}=\frac1{10}\left[\frac{\sqrt{\cos0}+\sqrt{\cos1}}{2}+\sum_{j=1}^{9}\sqrt{\cos\frac{j}{10}}\right]=\frac1{10}\left[\frac{1+\sqrt{\cos1}}{2}+\sqrt{\cos\frac1{10}}+\sqrt{\cos\frac2{10}}+\sqrt{\cos\frac3{10}}+\dots+\sqrt{\cos\frac9{10}}\right]=0{,}9135078\ldots$$

> [!warning] Calcolatrice in radianti
> All'esame si ha la calcolatrice, ma va usata in **radianti**, non in gradi. Conviene anche non semplificare le frazioni ($\frac2{10}$, non $\frac15$): con lo stesso denominatore si sbaglia meno. Il docente avverte che c'è chi ha sbagliato il calcolo con la formula dei trapezi all'esame.
### Punto (b)
Per applicare il teorema serve $f\in C^2[0,1]$. In realtà $f(x)=\sqrt{\cos x}$ è di classe $C^\infty[0,1]$ come composizione delle funzioni
$$\cos x:[0,1]\to[\cos1,1]=[0{,}54\ldots,1]\qquad\text{e}\qquad\sqrt y:[\cos1,1]\to\mathbb{R}$$
entrambe di classe $C^\infty$ sui rispettivi domini $[0,1]$ e $[\cos1,1]$.

> [!info] Il punto delicato: la radice in 0
> $\sqrt y=y^{1/2}$ è derivabile infinite volte solo su $(0,\infty)$: in $0$ la tangente è verticale e $\frac{d}{dy}\sqrt y=\frac1{2\sqrt y}$ non è definita. Se $\cos x$ si annullasse in $[0,1]$ non si potrebbe concludere. Ma $\cos x$ si annulla in $\frac\pi2\approx1{,}57$, e su $[0,1]$ resta tra $\cos1\approx0{,}54$ e $1$: per questo i domini sono ristretti al minimo indispensabile, lontano dallo $0$ della radice.

Applicando il teorema sull'errore con $b-a=1$ e $h=\frac1{10}$, e usando $\left|\frac\alpha\beta\right|=\frac{|\alpha|}{|\beta|}$:
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_{10}\right|=\left|-\frac{1\cdot f''(\eta)}{12}\left(\frac1{10}\right)^2\right|=\frac{|f''(\eta)|}{1200}\qquad\eta\in[0,1]$$
Derivate:
$$f'(x)=\frac{1}{2\sqrt{\cos x}}\cdot(-\sin x)=-\frac{\sin x}{2\sqrt{\cos x}}$$
$$f''(x)=\frac{-\cos x\cdot2\sqrt{\cos x}-(-\sin x)\cdot2\cdot\frac{-\sin x}{2\sqrt{\cos x}}}{4\cos x}$$
Moltiplicando numeratore e denominatore per $\sqrt{\cos x}=(\cos x)^{1/2}$ e spezzando la frazione:
$$f''(x)=\frac{-2\cos^2x-\sin^2x}{4(\cos x)^{3/2}}=-\frac{(\cos x)^{1/2}}{2}-\frac{\sin^2x}{4(\cos x)^{3/2}}$$
**Stima uniforme.** Per ogni $x\in[0,1]$, con la **disuguaglianza triangolare** $|\alpha\pm\beta|\leq|\alpha|+|\beta|$:
$$|f''(x)|\leq\left|\frac{(\cos x)^{1/2}}{2}\right|+\left|\frac{\sin^2x}{4(\cos x)^{3/2}}\right|=\frac{(\cos x)^{1/2}}{2}+\frac{\sin^2x}{4(\cos x)^{3/2}}$$
(i moduli si tolgono perché su $[0,1]$ sia $\cos x$ sia $\sin x$ sono $\geq0$). Su $[0,1]$ il coseno è **decrescente** e il seno **crescente**:
- il primo termine è massimo dove il coseno è massimo, cioè in $0$;
- nel secondo, una frazione è tanto più grande quanto più è grande il numeratore e piccolo il denominatore: al numeratore si mette il valore più grande, $\sin^21$, al denominatore il più piccolo, $4(\cos1)^{3/2}$.

$$|f''(x)|\leq\frac{(\cos0)^{1/2}}{2}+\frac{\sin^21}{4(\cos1)^{3/2}}=0{,}9458\ldots\qquad\forall x\in[0,1]$$
In particolare vale per $x=\eta$, quindi
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_{10}\right|\leq\frac{0{,}9458}{1200}=0{,}000788\ldots$$

> [!warning] Differenze rispetto alla lavagna
> Il finale è stato scritto di corsa. Alla lavagna il secondo termine della stima compare con $\sin x$ al posto di $\sin^2x$ (la maggiorazione resterebbe valida, perché su $[0,1]$ è $0\leq\sin x\leq1$ e quindi $\sin^2x\leq\sin x$), ma il valore $0{,}9458$ è quello calcolato con $\sin^21$. Inoltre nell'ultima riga è scritto $\frac{0{,}9458}{12}$, mentre il denominatore giusto è $1200$, come nella riga precedente: il risultato $0{,}000788\ldots$ è infatti $\frac{0{,}9458}{1200}$. Il docente stesso consiglia di riascoltare la fine della registrazione.

> [!info] Tre regole per le stime
> Dal "finale rocambolesco" della lezione, tre cose da ricordare per le stime d'esame: usare la **disuguaglianza triangolare**, **togliere i moduli** quando si può, e per maggiorare una **frazione** rendere grande il numeratore e piccolo il denominatore.
