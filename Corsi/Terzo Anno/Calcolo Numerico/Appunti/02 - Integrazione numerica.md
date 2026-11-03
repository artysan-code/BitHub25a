---
tags:
  - calcolo-numerico
  - integrazione-numerica
slide: []
---
# Integrazione numerica
## Formula dei trapezi
Lezione 5 (20/10/2026), seconda parte: comincia il secondo argomento del corso.
L'integrazione numerica è la branca dell'analisi numerica che si occupa di approssimare gli integrali, che molto raramente si riescono a calcolare in modo esatto (come $\int_0^1\sqrt{\cos x}\,dx$). Esistono molti metodi; nel corso se ne vede uno solo, la **formula dei trapezi**.
È data una funzione integrabile $f:[a,b]\to\mathbb{R}$ e si vuole calcolare un'approssimazione di $\int_a^bf(x)\,dx$, cioè dell'area sottesa dal grafico di $f$. Si suddivide $[a,b]$ in $n\geq1$ sottointervalli della stessa ampiezza
$$h=\frac{b-a}{n}$$
e si pone
$$x_j=a+jh,\qquad j=0,\dots,n$$
In particolare $x_0=a$ e $x_n=a+n\frac{b-a}{n}=b$. Alla lavagna il disegno è nel caso $n=4$, con $h=\frac{b-a}{4}$ e nodi $x_0=a,\ x_1,\ x_2,\ x_3,\ x_4=b$.

Il valore che si prende come approssimazione di $\int_a^bf(x)\,dx$ è $\int_a^bs(x)\,dx$, dove $s(x)$ è la **spezzata** che congiunge con segmenti i punti $(x_j,f(x_j))$:
$$s(x)=f(x_j)+\frac{f(x_{j+1})-f(x_j)}{x_{j+1}-x_j}(x-x_j)\qquad\text{per }x\in[x_j,x_{j+1}],\quad 0\leq j\leq n-1$$
Su ogni sottointervallo è la retta per i due punti $(x_j,f(x_j))$ e $(x_{j+1},f(x_{j+1}))$: è un polinomio di grado 1 in $x$, in $x_j$ vale $f(x_j)$ e in $x_{j+1}$ vale $f(x_{j+1})$. Il denominatore $x_{j+1}-x_j=h$ non dipende da $j$, perché i nodi sono equispaziati.
### Derivazione
Si spezza l'integrale sui singoli sottointervalli e si usa l'espressione di $s(x)$:
$$I_n=\int_a^bs(x)\,dx=\sum_{j=0}^{n-1}\int_{x_j}^{x_{j+1}}s(x)\,dx=\sum_{j=0}^{n-1}\int_{x_j}^{x_{j+1}}\left[f(x_j)+\frac{f(x_{j+1})-f(x_j)}{x_{j+1}-x_j}(x-x_j)\right]dx$$
La variabile d'integrazione è solo $x$: $x_j$, $x_{j+1}$, $f(x_j)$, $f(x_{j+1})$ sono costanti. Come primitiva si sceglie
$$f(x_j)\,(x-x_j)+\frac{f(x_{j+1})-f(x_j)}{x_{j+1}-x_j}\,\frac{(x-x_j)^2}{2}$$
invece di quella "standard" $f(x_j)\,x+\dots$.

> [!info] Perché questa primitiva
> Le primitive di una funzione $g(x)$ sono $\int g(x)\,dx=G(x)+C$: si può aggiungere qualsiasi costante. Il docente sceglie $f(x_j)(x-x_j)$ invece di $f(x_j)\,x$ (cambia solo la costante $-f(x_j)x_j$) e $\frac{(x-x_j)^2}{2}$ invece di $\frac{x^2}{2}-x_jx$. Che sia una primitiva lo si verifica derivando: si riottiene la funzione integranda. Il vantaggio è che nell'estremo inferiore $x=x_j$ si annulla tutto, e resta da valutare solo l'estremo superiore. Si può vedere anche come la sostituzione $t=x-x_j$, ma non serve.

Valutando in $x_{j+1}$ (il quadrato $(x_{j+1}-x_j)^2$ si semplifica con il denominatore):
$$I_n=\sum_{j=0}^{n-1}\left[f(x_j)\,(x_{j+1}-x_j)+\frac{f(x_{j+1})-f(x_j)}{2}\,(x_{j+1}-x_j)\right]$$
Raccogliendo $x_{j+1}-x_j=h$:
$$I_n=\sum_{j=0}^{n-1}\frac{f(x_j)+f(x_{j+1})}{2}\,h=\frac h2\sum_{j=0}^{n-1}\left[f(x_j)+f(x_{j+1})\right]$$
Scrivendo la somma per esteso,
$$\frac h2\Big[f(x_0)+f(x_1)+f(x_1)+f(x_2)+f(x_2)+f(x_3)+\dots+f(x_{n-1})+f(x_n)\Big]$$
i valori nei nodi intermedi $x_1,\dots,x_{n-1}$ compaiono due volte, mentre $f(x_0)=f(a)$ e $f(x_n)=f(b)$ una volta sola:
$$I_n=\frac h2\left[f(a)+f(b)+2\sum_{j=1}^{n-1}f(x_j)\right]$$
Riportando dentro il $\frac12$, si ottiene la forma finale.

> [!quote] Formula dei trapezi
> Sia $f:[a,b]\to\mathbb{R}$ integrabile, $n\geq1$, $h=\frac{b-a}{n}$ e $x_j=a+jh$ per $j=0,\dots,n$. La **formula dei trapezi di ordine $n$** è
> $$I_n=h\left[\frac{f(a)+f(b)}{2}+\sum_{j=1}^{n-1}f(x_j)\right]$$
> $h$ si chiama **passo (di discretizzazione)** della formula $I_n$.
### Osservazione: l'area dei trapezi
Il nome viene dalla figura: su ogni sottointervallo la regione sotto la spezzata è un trapezio "messo in piedi", con basi $f(x_j)$ e $f(x_{j+1})$ e altezza $h$. La sua area, $\frac{(\text{base maggiore}+\text{base minore})\cdot\text{altezza}}{2}$, è proprio
$$\int_{x_j}^{x_{j+1}}s(x)\,dx=\frac{f(x_j)+f(x_{j+1})}{2}\,h$$
cioè si poteva saltare direttamente dal primo all'ultimo passaggio della derivazione. Non si può farlo a priori perché $f$ può essere negativa o tagliare l'asse $x$ in un sottointervallo, e allora non ci sono veri trapezi. La derivazione mostra però che la formula dell'area del trapezio funziona **sempre**, anche in quei casi.

> [!question] Domanda tipica d'esame
> Ricavare la formula dei trapezi di ordine $n$ per approssimare $\int_a^bf(x)\,dx$. Traccia: suddivisione in $n$ sottointervalli di ampiezza $h=\frac{b-a}{n}$, spezzata $s(x)$ che congiunge i punti $(x_j,f(x_j))$, integrale di $s(x)$ sui singoli sottointervalli, somma con i nodi intermedi contati due volte.
## Errore della formula dei trapezi
Lezione 6 (22/10/2026). Nella lezione precedente si è ricavata la formula dei trapezi $I_n$ per approssimare $\int_a^bf(x)\,dx$ ([[02 - Integrazione numerica#Formula dei trapezi]]). Qui si vuole capire quale **errore** (o **resto**) si commette approssimando $\int_a^bf(x)\,dx$ con $I_n$. È una lezione teorica, definita dal docente "un pochino tosta": un lemma, che generalizza il teorema della media integrale, e il teorema sull'errore, la cui dimostrazione usa il lemma e il teorema sull'errore d'interpolazione ([[01 - Interpolazione polinomiale#Errore d'interpolazione#Teorema]]). Alla fine, un esempio con $\int_0^1\sqrt{\cos x}\,dx$.

> [!info] Lemma, teorema, corollario
> Il **teorema** è il risultato principale. Il **lemma** è un risultato ausiliario, usato per dimostrare un altro risultato; spesso è tecnico, ma può avere interesse proprio. Il **corollario** è una conseguenza di un teorema.
### Lemma
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
#### Il teorema della media integrale come caso particolare
> [!quote] Teorema (della media integrale)
> Sia $g:[a,b]\to\mathbb{R}$ una funzione continua. Allora $\exists\,\eta\in[a,b]$ tale che
> $$\int_a^bg(x)\,dx=g(\eta)\,(b-a)$$

Geometricamente: esiste un punto $\eta$ tale che l'area del rettangolo di base $[a,b]$ e altezza $g(\eta)$ è uguale all'area sottesa dal grafico di $g$. L'area che il rettangolo ha in più rispetto al grafico bilancia esattamente quella che ha in meno.

Il lemma è una **generalizzazione** del teorema della media integrale: per ottenerlo basta prendere nel lemma
$$\omega(x)=1,\qquad\beta(x)=\alpha(x)=g(x)$$
$\omega\equiv1$ è continua e $\geq0$, $\int_a^b1\,dx=b-a$; $\alpha=g$ e $\beta\,\omega=g$ sono continue; $\beta=\alpha$ sta ovviamente tra il minimo e il massimo di $\alpha$.
#### Dimostrazione
Siccome $\omega(x)\geq0$ e $m\leq\beta(x)\leq M$ per ogni $x\in[a,b]$, moltiplicando i membri della disuguaglianza per $\omega(x)$ (che è $\geq0$, quindi non inverte le disuguaglianze) risulta
$$m\,\omega(x)\leq\beta(x)\,\omega(x)\leq M\,\omega(x)\qquad\forall x\in[a,b]$$
Graficamente, il grafico di $y=\beta(x)\,\omega(x)$ sta tra quelli di $y=m\,\omega(x)$ e $y=M\,\omega(x)$. Per la **monotonia dell'integrale** (se $g(x)\leq h(x)$ $\forall x\in[a,b]$ allora $\int_a^bg\leq\int_a^bh$):
$$m\int_a^b\omega(x)\,dx=\int_a^bm\,\omega(x)\,dx\leq\int_a^b\beta(x)\,\omega(x)\,dx\leq\int_a^bM\,\omega(x)\,dx=M\int_a^b\omega(x)\,dx$$
Sia ora $z:[a,b]\to\mathbb{R}$ la funzione ausiliaria
$$z(y)=\alpha(y)\int_a^b\omega(x)\,dx$$
dove $\int_a^b\omega(x)\,dx$ è una **costante** $\geq0$ (la variabile è $y$). $z$ è continua su $[a,b]$ perché $\alpha$ lo è per ipotesi, e siccome la costante è $\geq0$ il suo minimo è $m\int_a^b\omega$ e il suo massimo $M\int_a^b\omega$. Per il **teorema dei valori intermedi**, $z$ assume su $[a,b]$ tutti i valori compresi fra il suo minimo e il suo massimo. Per la disuguaglianza sopra, $\int_a^b\beta(x)\,\omega(x)\,dx$ è uno di questi valori, quindi $\exists\,\eta\in[a,b]$ tale che
$$z(\eta)=\alpha(\eta)\int_a^b\omega(x)\,dx=\int_a^b\beta(x)\,\omega(x)\,dx$$
che è la tesi. $\blacksquare$
### Teorema sull'errore della formula dei trapezi
> [!quote] Teorema (errore della formula dei trapezi)
> Sia $f:[a,b]\to\mathbb{R}$ di classe $C^2[a,b]$ e sia $I_n$ la formula dei trapezi di ordine $n$ e passo $h=\frac{b-a}{n}$ per approssimare $\int_a^bf(x)\,dx$. Allora $\exists\,\eta\in[a,b]$ tale che
> $$\int_a^bf(x)\,dx-I_n=-\frac{(b-a)\,f''(\eta)}{12}\,h^2$$

> [!info] Definizione di $C^2[a,b]$
> $C^2[a,b]$ è l'insieme delle funzioni derivabili due volte su $[a,b]$ con tutte le derivate fino alla seconda inclusa continue (basta chiedere che sia continua la derivata seconda: le precedenti, essendo derivabili, lo sono già). Il docente avverte che la definizione può essere chiesta all'orale. Non va confusa con i polinomi: $f$ è una funzione qualsiasi di classe $C^2$.

Il teorema dà la **differenza** tra valore esatto e approssimato, senza modulo, come il teorema sull'errore d'interpolazione. Il modulo si mette poi negli esercizi, quando si stima l'errore.
#### Dimostrazione
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
##### Applicazione del lemma
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
##### Calcolo dell'integrale
L'integrale rimasto è quello di una parabola. Con la sostituzione $t=x-x_j$ ($dt=dx$, $x=t+x_j$; per $x=x_j$ è $t=0$, per $x=x_{j+1}$ è $t=x_{j+1}-x_j=h$) si ha $x_{j+1}-x=x_{j+1}-x_j-t=h-t$, quindi
$$\int_{x_j}^{x_{j+1}}\frac{(x-x_j)(x_{j+1}-x)}{2}\,dx=\int_0^h\frac{t(h-t)}{2}\,dt=\int_0^h\left(\frac h2t-\frac{t^2}{2}\right)dt=\left[\frac{ht^2}{4}-\frac{t^3}{6}\right]_0^h=\frac{h^3}{4}-\frac{h^3}{6}=\frac{h^3}{12}$$
Il risultato **non dipende da $j$**: si porta fuori dalla somma. Moltiplicando e dividendo per $n$:
$$\int_a^bf(x)\,dx-I_n=-\sum_{j=0}^{n-1}f''(\eta_j)\,\frac{h^3}{12}=-\frac{h^3\,n}{12}\cdot\frac1n\sum_{j=0}^{n-1}f''(\eta_j)$$
##### La media aritmetica
$\frac1n\sum_{j=0}^{n-1}f''(\eta_j)$ è la **media aritmetica** dei numeri $f''(\eta_0),\dots,f''(\eta_{n-1})$. Di questi numeri non si sa nulla, se non che sono valori di $f''$ in punti di $[a,b]$: stanno quindi tra il minimo $m$ e il massimo $M$ di $f''$ su $[a,b]$ (presi su tutto $[a,b]$, perché ogni $\eta_j$ sta in un sottointervallo diverso). Anche la loro media aritmetica sta tra $m$ e $M$, perché la media sta sempre tra il più piccolo e il più grande dei numeri di cui si fa la media. $f''$ è continua, quindi per il teorema dei valori intermedi $\exists\,\eta\in[a,b]$ tale che
$$\frac1n\sum_{j=0}^{n-1}f''(\eta_j)=f''(\eta)$$
Infine $h\,n=b-a$, quindi $h^3n=h^2(b-a)$ e
$$\int_a^bf(x)\,dx-I_n=-\frac{h^2(b-a)}{12}\,f''(\eta)\qquad\blacksquare$$
Secondo il docente è una delle dimostrazioni più difficili del corso (ce ne sarà una ancora più difficile alla fine): il lemma è un po' cervellotico e bisogna guardare indietro nei passaggi.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il teorema sull'errore della formula dei trapezi. Traccia: $s(x)$ coincide su ogni $[x_j,x_{j+1}]$ con il polinomio d'interpolazione di $f$ sui nodi $x_j,x_{j+1}$ (unicità); errore d'interpolazione con $\xi_j(x)$; cambio di segno; lemma con $\omega=\frac12(x-x_j)(x_{j+1}-x)$, $\beta=f''(\xi_j(x))$, $\alpha=f''$ e verifica delle ipotesi (continuità di $\beta\omega=-(f-s)$, non di $\beta$); integrale $\frac{h^3}{12}$; media aritmetica e valori intermedi.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il lemma che generalizza il teorema della media integrale, e mostrare come se ne ricava il teorema della media integrale.
### Esempio: $\int_0^1\sqrt{\cos x}\,dx$
> [!example] Esempio
> - (a) Calcolare l'approssimazione di $\int_0^1\sqrt{\cos x}\,dx$ con $I_{10}$, la formula dei trapezi di ordine 10.
> - (b) Stimare l'errore che si commette approssimando $\int_0^1\sqrt{\cos x}\,dx$ con $I_{10}$.

È l'integrale citato all'inizio del corso: nonostante l'apparenza innocua, $\sqrt{\cos x}$ non ha una primitiva elementare e l'integrale non si sa calcolare esattamente, va approssimato.
#### Punto (a)
Si applica la formula
$$I_n=h\left[\frac{f(a)+f(b)}{2}+\sum_{j=1}^{n-1}f(x_j)\right],\qquad h=\frac{b-a}{n},\quad x_j=a+jh,\ j=0,\dots,n$$
con $[a,b]=[0,1]$, $f(x)=\sqrt{\cos x}$, $n=10$, $h=\frac1{10}$ e $x_j=jh=\frac{j}{10}$, $j=0,\dots,10$:
$$I_{10}=\frac1{10}\left[\frac{\sqrt{\cos0}+\sqrt{\cos1}}{2}+\sum_{j=1}^{9}\sqrt{\cos\frac{j}{10}}\right]=\frac1{10}\left[\frac{1+\sqrt{\cos1}}{2}+\sqrt{\cos\frac1{10}}+\sqrt{\cos\frac2{10}}+\sqrt{\cos\frac3{10}}+\dots+\sqrt{\cos\frac9{10}}\right]=0{,}9135078\ldots$$

> [!warning] Calcolatrice in radianti
> All'esame si ha la calcolatrice, ma va usata in **radianti**, non in gradi. Conviene anche non semplificare le frazioni ($\frac2{10}$, non $\frac15$): con lo stesso denominatore si sbaglia meno. Il docente avverte che c'è chi ha sbagliato il calcolo con la formula dei trapezi all'esame.
#### Punto (b)
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
> Dal "finale rocambolesco" della lezione, tre cose da ricordare per le stime d'esame: usare la **disuguaglianza triangolare**, **togliere i moduli** quando si può, e per maggiorare una **frazione** rendere grande il numeratore e piccolo il denominatore. Il passaggio è ripreso con calma nella lezione successiva: [[02 - Integrazione numerica#Scelta di n ed estrapolazione#La stima uniforme]].
## Scelta di n ed estrapolazione
Lezione 7 (27/10/2026): ripresa della stima dell'errore per $\int_0^1\sqrt{\cos x}\,dx$ (la stima uniforme di $|f''|$), esercizi in cui si fissa l'errore $\varepsilon$ e si cerca $n$, la forma generale $n(\varepsilon)=\frac{C}{\sqrt\varepsilon}$, il metodo di estrapolazione e un esempio completo con $\int_0^2xe^x\,dx$.

Lezione lunga (circa due ore e un quarto, con una pausa) ma, come annunciato dal docente, quasi tutta di esempi: l'unica parte teorica è l'estrapolazione, una decina di minuti.

> [!info] Appelli
> A inizio lezione il docente ha detto che ci saranno due appelli, uno a gennaio e uno a febbraio. C'è anche un appello straordinario a dicembre, pensato per gli studenti dell'anno scorso: ci si può iscrivere, visto che il corso finisce prima, a patto di **non sparire dagli altri corsi** per prepararlo.

> [!warning] Da verificare
> Nella registrazione la data dell'appello straordinario sembra il **21 dicembre**, ma non è chiaro chi la dica: controllare sulla pagina del docente.
### La stima uniforme
Si riprende il punto (b) dell'esempio della lezione precedente ([[02 - Integrazione numerica#Errore della formula dei trapezi#Punto (b)]]), il cui finale era stato troppo veloce. Il docente insiste perché sono le disuguaglianze che all'esame si sbagliano sempre.

Dal teorema sull'errore si era arrivati a
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_{10}\right|=\frac{|f''(\eta)|}{1200}\qquad\eta\in[0,1]$$
Di $\eta$ si sa **soltanto** che sta in $[0,1]$. Per stimare $|f''(\eta)|$ serve allora una stima che valga per tutti i punti dell'intervallo.

> [!quote] Stima uniforme
> Una **stima uniforme** di $|f''(x)|$ sull'intervallo $[a,b]$ è una costante $C$, **indipendente da $x$**, tale che
> $$|f''(x)|\leq C\qquad\forall x\in[a,b]$$

"Uniforme" vuol dire proprio questo: la stessa costante va bene per tutti gli $x$, e quindi anche per il punto $\eta$, di cui non si sa dove sia. Il docente raccomanda di ricordare il nome: è quello che va fatto per la derivata seconda in tutti questi esercizi.

Con $f''(x)=-\frac{(\cos x)^{1/2}}{2}-\frac{\sin^2x}{4(\cos x)^{3/2}}$, per ogni $x\in[0,1]$:
$$|f''(x)|=\left|-\frac{(\cos x)^{1/2}}{2}-\frac{\sin^2x}{4(\cos x)^{3/2}}\right|\overset{(1)}{\leq}\left|\frac{(\cos x)^{1/2}}{2}\right|+\left|\frac{\sin^2x}{4(\cos x)^{3/2}}\right|\overset{(2)}{=}\frac{(\cos x)^{1/2}}{2}+\frac{\sin^2x}{4(\cos x)^{3/2}}\overset{(3)}{\leq}\frac{(\cos0)^{1/2}}{2}+\frac{\sin^21}{4(\cos1)^{3/2}}=0{,}9457\ldots\leq0{,}9458$$
I tre passaggi, che alla lavagna sono segnati con asterischi di colori diversi:
1. **Disuguaglianza triangolare**: $|\alpha\pm\beta|\leq|\alpha|+|\beta|$ per ogni $\alpha,\beta\in\mathbb{C}$. Qui $\alpha=\frac{(\cos x)^{1/2}}{2}$ e $\beta=\frac{\sin^2x}{4(\cos x)^{3/2}}$; il meno davanti ad $\alpha$ non conta, perché il modulo "se lo mangia". Secondo il docente è una disuguaglianza che non si usa quasi mai ma che qui è fondamentale.
2. **Si tolgono i moduli**: per ogni $x\in[0,1]$ è $\cos x>0$ e $\sin x\geq0$, quindi entrambi i termini sono $\geq0$.
3. **Maggiorazione termine per termine**:
	- $\cos x$ è **decrescente** su $[0,1]$, quindi $(\cos x)^{1/2}$ è massimo in $x=0$;
	- il secondo termine è una **frazione positiva**: per trovare un numero sicuramente più grande serve un numero più grande del numeratore e uno più piccolo del denominatore. $\sin x$ è **crescente** su $[0,1]$, quindi il numeratore è al massimo $\sin^21$; il coseno è decrescente, quindi il denominatore è al minimo $4(\cos1)^{3/2}$.

La costante $C=0{,}9458$ vale per ogni $x\in[0,1]$, in particolare per $\eta$:
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_{10}\right|\leq\frac{0{,}9458}{1200}=0{,}000788\ldots$$

> [!warning] Non basta guardare gli estremi
> All'esame capita spesso di vedere sostituiti i due estremi dell'intervallo ($0$ e $1$) prendendo il valore più grande. Il ragionamento è corretto **solo se la funzione è monotona**: se il massimo sta in mezzo all'intervallo, gli estremi non bastano. Per questo alla lavagna "decrescente" e "crescente" sono sottolineati: sono la giustificazione del passaggio.

> [!warning] Differenze rispetto alla lavagna
> Anche in questa ripresa, nei riquadri del passaggio (3) il numeratore è scritto $\sin x$ e $\sin1$ invece di $\sin^2x$ e $\sin^21$ (vedi l'avvertenza in fondo a [[02 - Integrazione numerica#Errore della formula dei trapezi#Punto (b)]]). Con $\sin1$ la costante verrebbe $1{,}0297\ldots$: il valore $0{,}9458$ è quello con $\sin^21$ ($0{,}94572\ldots$, arrotondato per eccesso, il che va bene in una maggiorazione).
### Fissato l'errore, trovare n
> [!example] Esempio
> Fissato $\varepsilon=10^{-8}$, determinare un $n$ tale che la formula dei trapezi $I_n$ fornisca un'approssimazione di $\int_0^1\sqrt{\cos x}\,dx$ con errore $\left|\int_0^1\sqrt{\cos x}\,dx-I_n\right|\leq\varepsilon$.

Il "giochino" è capovolto rispetto all'esempio precedente: prima si fissava $n=10$, si calcolava $I_{10}$ e poi si stimava l'errore; ora si decide quale errore massimo si vuole commettere e si cerca un $n$ che lo garantisca.

Si usa sempre il teorema sull'errore ([[02 - Integrazione numerica#Errore della formula dei trapezi#Teorema sull'errore della formula dei trapezi]]): se $f\in C^2[a,b]$,
$$\int_a^bf(x)\,dx-I_n=-\frac{(b-a)\,f''(\eta)}{12}\,h^2,\qquad h=\frac{b-a}{n},\quad\eta\in[a,b]$$
Con $f(x)=\sqrt{\cos x}$ (già vista essere $C^\infty[0,1]$), $[a,b]=[0,1]$ e quindi $h=\frac1n$:
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_n\right|=\left|-\frac{f''(\eta)}{12n^2}\right|=\frac{|f''(\eta)|}{12n^2}\leq\frac{1}{12n^2}\qquad\eta\in[0,1]$$
Il docente raccomanda di scrivere sempre dove sta $\eta$. Si è usato:
- $\left|\frac\alpha\beta\right|=\frac{|\alpha|}{|\beta|}$ per ogni $\alpha,\beta\in\mathbb{C}$ con $\beta\neq0$;
- la stima uniforme già trovata, $|f''(x)|\leq0{,}9458$, ulteriormente maggiorata con $1$ per avere un numero più semplice da scrivere. Il lavoro difficile, cioè la stima uniforme, era già stato fatto.

Si **impone** che il maggiorante sia $\leq\varepsilon$. Moltiplicando per $n^2$ e dividendo per $\varepsilon$, che sono positivi e quindi non cambiano il verso:
$$\frac{1}{12n^2}\leq\varepsilon\iff n^2\geq\frac{1}{12\varepsilon}\iff n\geq\sqrt{\frac{1}{12\varepsilon}}=n(\varepsilon)$$
(l'ultima equivalenza perché $n$ è un intero positivo). $n(\varepsilon)$ è una funzione di $\varepsilon$: ad esempio $n(0{,}001)=\sqrt{\frac{1}{12\cdot0{,}001}}$.

**Conclusione**: se si prende $n\geq n(\varepsilon)$, si è sicuri che
$$\left|\int_0^1\sqrt{\cos x}\,dx-I_n\right|\leq\frac{1}{12n^2}\leq\varepsilon$$
Per $\varepsilon=10^{-8}$ si ha $n(10^{-8})=2886{,}75\ldots$, e prendendo $n=2887$ si è sicuri che l'errore è $\leq10^{-8}$.

> [!warning] Arrotondare per eccesso
> $n$ è il numero di sottointervalli, quindi deve essere un **intero**. Va preso $\geq n(\varepsilon)$: $2887$, non l'intero più vicino $2886$, che è più piccolo di $n(\varepsilon)$ e non garantisce nulla. Qualsiasi intero più grande (anche "200 miliardi") va bene lo stesso, ma si prende il più piccolo.

> [!info] Con la costante esatta
> Usando $0{,}9458$ invece di $1$ si otterrebbe $n(10^{-8})=\sqrt{\frac{0{,}9458}{12\cdot10^{-8}}}=2807{,}4\ldots$, cioè $n=2808$. Maggiorare $C$ con $1$ costa qualche nodo in più ma resta corretto. (Calcolo nostro, non fatto a lezione.)
### Esempio con il logaritmo
> [!example] Esempio
> Fissato $\varepsilon>0$, determinare un $n$ tale che la formula dei trapezi $I_n$ fornisca un'approssimazione di $\int_0^1\frac{x+2}{\log(x+2)}\,dx$ con errore $\left|\int_0^1\frac{x+2}{\log(x+2)}\,dx-I_n\right|\leq\varepsilon$. Quanto vale $n$ se $\varepsilon=10^{-8}$?

Qui va fatto tutto da zero, compresa la stima uniforme, e quindi è più faticoso. Prima si risponde per $\varepsilon$ qualsiasi, poi si sostituisce $\varepsilon=10^{-8}$.

> [!info] Il logaritmo
> In matematica $\log$ senza base indica il logaritmo **naturale** (in base $e$), quello che altrove si scrive $\ln$. In particolare $\frac{d}{dx}\log(x+2)=\frac{1}{x+2}$.

Sia $f(x)=\frac{x+2}{\log(x+2)}$. È un rapporto di funzioni $C^\infty$, quindi è di classe $C^\infty$ dove è definita, e in particolare è $C^\infty[0,1]$: si può applicare il teorema sull'errore.

> [!warning] Dominio di $f$
> A lezione si dice che $f$ è $C^\infty$ su $(-2,+\infty)$, dove è definito il logaritmo. Ma lì il **denominatore** $\log(x+2)$ si annulla per $x=-1$, quindi $f$ è definita e $C^\infty$ su $(-2,-1)\cup(-1,+\infty)$. Per l'esercizio non cambia niente, perché $[0,1]\subset(-1,+\infty)$.

Con $[a,b]=[0,1]$ e $h=\frac1n$:
$$\left|\int_0^1\frac{x+2}{\log(x+2)}\,dx-I_n\right|=\left|-\frac{1\cdot f''(\eta)}{12}\left(\frac1n\right)^2\right|=\frac{|f''(\eta)|}{12n^2}\qquad\eta\in[0,1]\tag{$\star$}$$
**Derivate.** Con la derivata del quoziente:
$$f'(x)=\frac{1\cdot\log(x+2)-(x+2)\cdot\frac{1}{x+2}}{\log^2(x+2)}=\frac{\log(x+2)-1}{\log^2(x+2)}$$
$$f''(x)=\frac{\frac{1}{x+2}\log^2(x+2)-\big(\log(x+2)-1\big)\cdot2\log(x+2)\cdot\frac{1}{x+2}}{\log^4(x+2)}=\frac{-\frac{1}{x+2}\log^2(x+2)+\frac{2\log(x+2)}{x+2}}{\log^4(x+2)}$$
Dividendo numeratore e denominatore per $\log(x+2)$ e moltiplicandoli per $x+2$:
$$f''(x)=\frac{2-\log(x+2)}{(x+2)\log^3(x+2)}$$
**Stima uniforme.** Per ogni $x\in[0,1]$:
- $x+2\in[2,3]$, quindi $x+2>0$ e $\log(x+2)\geq\log2>0$ (il logaritmo è negativo solo per argomenti minori di $1$): il **denominatore** è positivo;
- il logaritmo è crescente, quindi $\log(x+2)\leq\log3=1{,}0986\ldots<2$: anche il **numeratore** $2-\log(x+2)$ è positivo.

Si possono quindi togliere i moduli ("sbarazzarsi dei moduli", quando si può, va sempre fatto). Poi, come prima, si maggiora il numeratore e si minora il denominatore:
- $2-\log(x+2)$ è **decrescente** su $[0,1]$ (il logaritmo è crescente, col meno davanti diventa decrescente), quindi è al massimo in $x=0$: $2-\log2$;
- nel denominatore conviene guardare i due fattori separatamente: $x+2\geq0+2$, e $\log^3(x+2)$ è crescente (cubo di una funzione crescente e positiva), quindi $\log^3(x+2)\geq\log^3(0+2)$.

$$|f''(x)|=\frac{2-\log(x+2)}{(x+2)\log^3(x+2)}\leq\frac{2-\log2}{(0+2)\log^3(0+2)}=\frac{2-\log2}{2\log^32}=1{,}962\ldots\leq1{,}97\qquad\forall x\in[0,1]$$
Tornando a $(\star)$:
$$\left|\int_0^1\frac{x+2}{\log(x+2)}\,dx-I_n\right|\leq\frac{1{,}97}{12n^2}$$
Si impone
$$\frac{1{,}97}{12n^2}\leq\varepsilon\iff n^2\geq\frac{1{,}97}{12\varepsilon}\iff n\geq\sqrt{\frac{1{,}97}{12\varepsilon}}=n(\varepsilon)$$
**Conclusione**: se si prende $n\geq n(\varepsilon)$, si è sicuri che $\left|\int_0^1\frac{x+2}{\log(x+2)}\,dx-I_n\right|\leq\varepsilon$. Per $\varepsilon=10^{-8}$ si ha $n(10^{-8})=4051{,}74\ldots$, quindi si prende $n=4052$.
### Osservazione: la forma di n(ε)
Nei due esempi precedenti il valore $n(\varepsilon)$, quello che garantisce un errore $\leq\varepsilon$ se si prende $n\geq n(\varepsilon)$, è della forma
$$n(\varepsilon)=\frac{C}{\sqrt\varepsilon}\qquad\text{con }C\text{ costante}$$
Ad esempio nel secondo $n(\varepsilon)=\sqrt{\frac{1{,}97}{12\varepsilon}}=\frac{\sqrt{1{,}97/12}}{\sqrt\varepsilon}$. Non è un caso: è un fatto generale.

Sia infatti $K$ una costante tale che
$$|f''(x)|\leq K\qquad\forall x\in[a,b]$$
(la stima uniforme, che negli esempi si chiamava $C$). Per il teorema sull'errore, sostituendo $h=\frac{b-a}{n}$:
$$\left|\int_a^bf(x)\,dx-I_n\right|=\left|-\frac{(b-a)\,f''(\eta)}{12}\,h^2\right|=\frac{(b-a)^3\,|f''(\eta)|}{12n^2}\leq\frac{(b-a)^3K}{12n^2}$$
e quindi
$$\frac{(b-a)^3K}{12n^2}\leq\varepsilon\iff n^2\geq\frac{(b-a)^3K}{12\varepsilon}\iff n\geq\sqrt{\frac{(b-a)^3K}{12\varepsilon}}=n(\varepsilon)=\frac{C}{\sqrt\varepsilon},\qquad C=\sqrt{\frac{(b-a)^3K}{12}}$$
La parte difficile di tutto il discorso è sempre la stessa: trovare $K$, cioè la **stima uniforme** di $|f''|$. Il resto è meccanico.

> [!warning] Errore alla lavagna
> Nelle ultime due righe alla lavagna compare $(b-a)K$ invece di $(b-a)^3K$, sia nella disequazione sia nella costante $C=\sqrt{\frac{(b-a)K}{12}}$, mentre la riga sopra ha correttamente $\frac{(b-a)^3K}{12n^2}$. Negli esempi con $[0,1]$ non cambia nulla perché $b-a=1$, ma nell'esempio su $[0,2]$ ([[02 - Integrazione numerica#Scelta di n ed estrapolazione#Esempio di estrapolazione]]) il fattore è $(2-0)^3=8$, e infatti lì il docente usa $8$.

> [!info] Conseguenza pratica
> Da $n(\varepsilon)=\frac{C}{\sqrt\varepsilon}$: per ridurre l'errore garantito di un fattore $100$ (due cifre decimali in più) bisogna moltiplicare $n$ per $10$. È il motivo per cui nell'esempio di estrapolazione servirà un $n$ così grande. (Osservazione nostra, non fatta a lezione.)
### Esercizi sulla scelta di n
- **2.1** Fissato $\varepsilon>0$, determinare un $n$ tale che la formula dei trapezi $I_n$ fornisca un'approssimazione di $I$ con errore $|I-I_n|\leq\varepsilon$ nei seguenti casi:
	- $I=\int_0^1e^{-x^2}\,dx$;
	- $I=\int_0^2xe^x\,dx$;
	- $I=\int_0^3\frac{\log(1+x^2)}{\sqrt{2+\cos x}}\,dx$.

Il secondo integrale è proprio quello dell'esempio di estrapolazione qui sotto, dove la stima uniforme è svolta nel punto (d).
### Estrapolazione
Dopo la pausa, l'ultima parte riguarda ancora la formula dei trapezi, ma con un altro metodo che la migliora: il **metodo di estrapolazione**. Se ne dà poco più di un cenno.

Sia $f:[a,b]\to\mathbb{R}$ (integrabile, sottinteso) e siano $I_{n_0},I_{n_1},\dots,I_{n_m}$ le formule dei trapezi di ordini **distinti** $n_0,n_1,\dots,n_m$ e passi
$$h_0=\frac{b-a}{n_0},\quad h_1=\frac{b-a}{n_1},\quad\dots,\quad h_m=\frac{b-a}{n_m}$$
per approssimare $\int_a^bf(x)\,dx$. In pratica ci si è calcolati un certo numero, tendenzialmente piccolo, di formule dei trapezi: sono $m+1$ numeri. Sia $p(x)$ il polinomio d'interpolazione degli $m+1$ dati
$$(h_0^2,I_{n_0}),\quad(h_1^2,I_{n_1}),\quad\dots,\quad(h_m^2,I_{n_m})$$
Cioè, per definizione ([[01 - Interpolazione polinomiale#Polinomi di Lagrange#Polinomio d'interpolazione]]), $p(x)$ è l'unico polinomio in $\mathbb{R}_m[x]$ tale che
$$p(h_i^2)=I_{n_i}\qquad\forall i=0,\dots,m$$
I **nodi** sono i quadrati dei passi, $h_0^2,\dots,h_m^2$, e i valori sono le formule dei trapezi. Esiste ed è unico perché i nodi sono distinti: gli ordini $n_i$ sono distinti, quindi lo sono i passi $h_i$ e, essendo positivi, i loro quadrati. Per questo alla lavagna "distinti" è sottolineato.

> [!quote] Estrapolazione
> In base a risultati che non si dimostrano (perché un po' difficili), il valore $p(0)$ è un'approssimazione di $\int_a^bf(x)\,dx$ **molto più accurata** delle singole formule dei trapezi $I_{n_0},\dots,I_{n_m}$ usate per costruirlo.
>
> Il procedimento di valutare in $0$ il polinomio d'interpolazione si chiama **estrapolazione**, perché $p(x)$ viene valutato in un punto, $x=0$, che sta **fuori dal più piccolo intervallo che contiene i nodi** $h_0^2,\dots,h_m^2$ (i nodi sono tutti positivi, quindi quell'intervallo è fatto di numeri positivi e $0$ ne resta fuori). $p(0)$, il valore "magico" che "sconfigge clamorosamente" le singole formule, si chiama **valore estrapolato**.

La filosofia: si calcolano poche formule dei trapezi con $n$ modesti, si costruisce il polinomio (facile) e lo si valuta in $0$. Alla lavagna l'illustrazione è con $m=2$: sull'asse $x$ i nodi $h_2^2<h_1^2<h_0^2$, sopra i valori $I_{n_2},I_{n_1},I_{n_0}$, la parabola $y=p(x)$ che li interpola, e il valore $p(0)$ letto sull'asse $y$.

> [!info] Perché in 0 e perché $h^2$
> A fine lezione uno studente ha osservato che $p(0)$ è, concettualmente, la formula dei trapezi "con passo zero", cioè idealmente l'integrale esatto, e il docente ha confermato. Il motivo dei quadrati, non spiegato a lezione, è la **formula di Eulero–Maclaurin**: se $f$ è abbastanza regolare, l'errore della formula dei trapezi si sviluppa in potenze pari del passo, $I_n=\int_a^bf(x)\,dx+c_1h^2+c_2h^4+\dots$, con coefficienti che non dipendono da $h$. Come funzione di $h^2$, quindi, $I_n$ si comporta come un polinomio il cui termine noto è proprio l'integrale. Applicato a passi dimezzati successivi, il procedimento è il **metodo di Romberg**. (Aggiunta nostra dalla letteratura di analisi numerica, non vista a lezione.)
### Esempio di estrapolazione
> [!example] Esempio
> Sia $f(x)=xe^x$. Per ogni $n\geq1$ indichiamo con $I_n$ la formula dei trapezi di ordine $n$ per approssimare $\int_0^2f(x)\,dx=I$.
> - (a) Calcolare $I$.
> - (b) Calcolare $I_{12},I_{24},I_{30}$ e confrontarli con $I$.
> - (c) Calcolare $p(0)$, dove $p(x)$ è il polinomio d'interpolazione dei dati $(h_0^2,I_{12}),(h_1^2,I_{24}),(h_2^2,I_{30})$ e $h_0,h_1,h_2$ sono i passi di discretizzazione delle formule $I_{12},I_{24},I_{30}$. Confrontare $p(0)$ con $I$.
> - (d) Posto $\varepsilon=|p(0)-I|$, determinare un $n$ in modo tale che $I_n$ fornisca un'approssimazione di $I$ con errore $|I_n-I|\leq\varepsilon$.
#### Punto (a)
Un esercizio di analisi: si integra **per parti**, $\int g(x)h'(x)\,dx=g(x)h(x)-\int g'(x)h(x)\,dx$, con $g(x)=x$ e $h'(x)=e^x$ (quindi $h(x)=e^x$). Prima l'integrale indefinito:
$$\int xe^x\,dx=xe^x-\int1\cdot e^x\,dx=xe^x-e^x=e^x(x-1)$$
Poi
$$I=\int_0^2xe^x\,dx=\Big[e^x(x-1)\Big]_0^2=e^2\cdot1-e^0\cdot(-1)=e^2+1=8{,}3890560989\ldots$$

> [!warning] Attenzione al segno
> In $0$ la primitiva vale $-1$, e va **sottratta**: $-(-1)=+1$. Alla lavagna il docente scrive prima $e^2-1$ e poi si corregge.
#### Punto (b)
La formula è
$$I_n=h\left[\frac{f(a)+f(b)}{2}+\sum_{j=1}^{n-1}f(x_j)\right],\qquad x_j=a+jh,\quad h=\frac{b-a}{n}$$
I passi delle tre formule sono
$$h_0=\frac{2-0}{12}=\frac16,\qquad h_1=\frac{2-0}{24}=\frac1{12},\qquad h_2=\frac{2-0}{30}=\frac1{15}$$
In tutte e tre $\frac{f(0)+f(2)}{2}=\frac{0+2e^2}{2}=e^2$, che non dipende dal passo, mentre i nodi interni sono $x_j=jh$:
$$I_{12}=\frac16\left[e^2+\sum_{j=1}^{11}\frac j6e^{j/6}\right]=\frac16\left[e^2+\frac16e^{1/6}+\frac26e^{2/6}+\dots+\frac{11}6e^{11/6}\right]=8{,}4380178285\ldots$$
$$I_{24}=\frac1{12}\left[e^2+\sum_{j=1}^{23}\frac j{12}e^{j/12}\right]=8{,}4013033444\ldots$$
$$I_{30}=\frac1{15}\left[e^2+\sum_{j=1}^{29}\frac j{15}e^{j/15}\right]=8{,}3968948597\ldots$$
All'esame si ha la calcolatrice; con $30$ termini ci vuole pazienza, ma si fa. Uno studente chiede se si può portare fuori dalla somma il fattore $\frac16$ (o $\frac1{12}$, $\frac1{15}$) di $\frac j6$: sì, il docente lo riscrive solo per chiarezza.

**Confronto** (cioè il modulo della differenza):
$$|I_{12}-I|\approx4{,}9\cdot10^{-2},\qquad|I_{24}-I|\approx1{,}2\cdot10^{-2},\qquad|I_{30}-I|\approx7{,}8\cdot10^{-3}$$
Nessuna è entusiasmante: $I_{12}$ e $I_{24}$ sbagliano già la prima cifra decimale, $I_{30}$ la seconda.
#### Punto (c)
Si calcola $p(0)$ con la **forma di Lagrange** ([[01 - Interpolazione polinomiale#Polinomi di Lagrange#Forma canonica e forma di Lagrange]]) sui nodi $h_0^2,h_1^2,h_2^2$:
$$p(x)=I_{12}\frac{(x-h_1^2)(x-h_2^2)}{(h_0^2-h_1^2)(h_0^2-h_2^2)}+I_{24}\frac{(x-h_0^2)(x-h_2^2)}{(h_1^2-h_0^2)(h_1^2-h_2^2)}+I_{30}\frac{(x-h_0^2)(x-h_1^2)}{(h_2^2-h_0^2)(h_2^2-h_1^2)}$$
Sostituendo $x=0$:
$$p(0)=\frac{h_1^2h_2^2}{(h_0^2-h_1^2)(h_0^2-h_2^2)}I_{12}+\frac{h_0^2h_2^2}{(h_1^2-h_0^2)(h_1^2-h_2^2)}I_{24}+\frac{h_0^2h_1^2}{(h_2^2-h_0^2)(h_2^2-h_1^2)}I_{30}$$
e con $h_0=\frac16$, $h_1=\frac1{12}$, $h_2=\frac1{15}$:
$$p(0)=\frac4{63}I_{12}-\frac{64}{27}I_{24}+\frac{625}{189}I_{30}=8{,}3890561002\ldots$$
Confrontato con $I=8{,}3890560989\ldots$, coincidono tutte le cifre fino a $8{,}389056$, e anche dopo ($0989$ contro $1002$) la differenza è minima:
$$|I-p(0)|\approx1{,}3\cdot10^{-9}$$
Con tre approssimazioni "scarse", con errori dell'ordine di $10^{-2}$ e $10^{-3}$, combinate in questo modo si ottiene un'approssimazione strepitosa.

> [!info] Verifica
> I tre coefficienti hanno somma $\frac4{63}-\frac{64}{27}+\frac{625}{189}=1$, com'è giusto: la somma dei polinomi di Lagrange è $1$ (se tutte le $I_{n_i}$ fossero uguali a un valore $c$, $p$ sarebbe la costante $c$). Tutti i valori di questo esempio sono stati ricontrollati al calcolatore.
#### Punto (d)
Il senso: il valore magico ha sconfitto tutte le formule dei trapezi usate. Quanto deve essere grande $n$ perché una singola $I_n$ faccia altrettanto bene?

Sia $\varepsilon=|I-p(0)|\approx1{,}3\cdot10^{-9}$. Per il teorema sull'errore, con $[a,b]=[0,2]$ e $h=\frac{2-0}{n}$ (il passo di $I_n$, non quelli delle formule precedenti):
$$\left|\int_0^2xe^x\,dx-I_n\right|=\left|-\frac{(2-0)\,f''(\eta)}{12}\left(\frac{2-0}{n}\right)^2\right|=\frac{8\,|f''(\eta)|}{12n^2}=\frac{2\,|f''(\eta)|}{3n^2}\qquad\eta\in[0,2]$$
($|f''(\eta)|$ resta nel modulo perché non se ne conosce il segno.) Derivate, con la regola del prodotto:
$$f'(x)=e^x+xe^x=(1+x)e^x,\qquad f''(x)=e^x+(1+x)e^x=(2+x)e^x$$
Stima uniforme: per ogni $x\in[0,2]$, $2+x>0$ ed $e^x>0$, quindi si tolgono i moduli, e si maggiorano i due fattori separatamente: $2+x\leq4$ ed $e^x\leq e^2$ (l'esponenziale è crescente):
$$|f''(x)|=(2+x)e^x\leq4e^2\qquad\forall x\in[0,2]$$

> [!warning] La costante deve valere per tutti gli $x$
> Uno studente propone $2$ come costante per $2+x$: non va bene, perché ad esempio per $x=1$ è $2+x=3>2$. La costante deve maggiorare $2+x$ **qualunque sia** $x\in[0,2]$. Con le funzioni monotone è facile; bisogna stare attenti con quelle che non sono né crescenti né decrescenti.

Quindi
$$|I-I_n|\leq\frac{2\cdot4e^2}{3n^2}=\frac{8e^2}{3n^2}$$
e si impone
$$\frac{8e^2}{3n^2}\leq\varepsilon\iff n^2\geq\frac{8e^2}{3\varepsilon}\iff n\geq\sqrt{\frac{8e^2}{3\varepsilon}}=n(\varepsilon)$$
Se si prende $n\geq n(\varepsilon)$ si è sicuri che $|I-I_n|\leq\varepsilon$. Nel caso $\varepsilon=1{,}3\cdot10^{-9}$ si ha $n(\varepsilon)=123113{,}92\ldots$, e si prende $n=123114$.

Servono più di centomila sottointervalli, contro i $12$, $24$ e $30$ usati per costruire $p(0)$. Con i calcolatori di oggi non è un problema, ma il confronto mostra quanto conviene l'estrapolazione.

> [!info] Osservazioni sui numeri
> - Il valore esatto è $\varepsilon=1{,}323\ldots\cdot10^{-9}$. Usare $1{,}3\cdot10^{-9}$, che è più piccolo, dà un $n$ un po' più grande e quindi resta corretto; con il valore esatto verrebbe $n(\varepsilon)=122038{,}5\ldots$
> - Il teorema garantisce $|I-I_n|\leq\varepsilon$ per $n\geq n(\varepsilon)$, ma è una **stima**: non dice che per $n$ più piccoli l'errore sia più grande di $\varepsilon$.
### Esercizi sull'estrapolazione
- **2.3** Si considerino i due casi $f(x)=e^{-x}$ con $[a,b]=[0,1]$ e $f(x)=\log x$ con $[a,b]=[1,2]$. Per ciascuno, indichiamo con $I_n$ la formula dei trapezi di ordine $n$ per approssimare $I=\int_a^bf(x)\,dx$.
	- (a) Calcolare $I$.
	- (b) Calcolare $I_3,I_6,I_{12}$ e confrontarli con il valore esatto $I$.
	- (c) Calcolare $p(0)$, dove $p(x)$ è il polinomio d'interpolazione dei dati $(h_0^2,I_3),(h_1^2,I_6),(h_2^2,I_{12})$ e $h_0,h_1,h_2$ sono i passi di discretizzazione delle formule $I_3,I_6,I_{12}$. Confrontare inoltre $p(0)$ con il valore esatto $I$.
	- (d) Posto $\varepsilon=|p(0)-I|$, determinare un $n$ in modo tale che la formula dei trapezi $I_n$ fornisca un'approssimazione di $I$ con errore $|I_n-I|\leq\varepsilon$.

Le richieste sono le stesse dell'esempio svolto. L'esercizio 2.2 non è stato mostrato a lezione.

> [!question] Domanda tipica d'esame
> Fissato $\varepsilon>0$, determinare $n$ tale che $|I-I_n|\leq\varepsilon$ per un integrale dato. Traccia: verificare che $f\in C^2[a,b]$; teorema sull'errore con $h=\frac{b-a}{n}$; derivata seconda; **stima uniforme** $|f''(x)|\leq K$ per ogni $x\in[a,b]$ (disuguaglianza triangolare, togliere i moduli, monotonia dei singoli pezzi, frazione: numeratore grande e denominatore piccolo); imporre $\frac{(b-a)^3K}{12n^2}\leq\varepsilon$; prendere il primo intero $\geq n(\varepsilon)$.

> [!question] Domanda tipica d'esame
> Che cos'è il metodo di estrapolazione e perché si chiama così? Traccia: formule dei trapezi $I_{n_0},\dots,I_{n_m}$ di ordini distinti; polinomio d'interpolazione dei dati $(h_i^2,I_{n_i})$; $p(0)$ è un'approssimazione molto più accurata; si valuta $p$ fuori dal più piccolo intervallo che contiene i nodi.
