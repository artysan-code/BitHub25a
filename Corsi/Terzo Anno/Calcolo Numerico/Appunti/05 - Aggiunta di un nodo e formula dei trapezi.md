---
tags:
  - calcolo-numerico
  - interpolazione
  - differenze-divise
  - integrazione-numerica
slide: []
---
# Aggiunta di un nodo e formula dei trapezi
La lezione chiude la parte sull'interpolazione polinomiale: prima un esempio completo dell'algoritmo di valutazione visto in [[04 - Forma di Newton del polinomio d'interpolazione#Algoritmo di valutazione in un punto del polinomio d'interpolazione]], poi l'**aggiunta di un nodo d'interpolazione**, il caso in cui la forma di Newton è la più conveniente. Nell'ultima mezz'ora comincia il secondo argomento del corso, l'**integrazione numerica**, con la derivazione della **formula dei trapezi**.
## Esempio: valutazione con l'algoritmo di Newton
> [!example] Esempio
> Consideriamo i dati
> $$(x_0,y_0)=(0,0),\quad(x_1,y_1)=(1,3),\quad(x_2,y_2)=(2,1),\quad(x_3,y_3)=(3,1)$$
> Calcolare mediante l'algoritmo descritto il valore in $t=2{,}3$ del polinomio $p(x)$ d'interpolazione di questi dati.

Il polinomio d'interpolazione di questi dati è l'unico polinomio $p(x)$ di grado $\leq3$ tale che $p(x_i)=y_i$ per ogni $i=0,1,2,3$. Il docente lo fa ripetere ancora una volta perché è una domanda tipica dell'orale ([[02 - Polinomi di Lagrange#Polinomio d'interpolazione]]).

Non è data una funzione, ma come osservato in [[04 - Forma di Newton del polinomio d'interpolazione#Osservazione: dati senza una funzione]] la si può sempre immaginare. Sia $f:[0,3]\to\mathbb{R}$ una qualsiasi funzione tale che $f(x_i)=y_i$ $\forall i=0,1,2,3$ (l'intervallo $[0,3]$ è il più piccolo che contiene tutti i nodi). Il polinomio $p(x)$ del testo è dunque il polinomio d'interpolazione di $f(x)$ sui nodi $x_0,x_1,x_2,x_3$ e si scrive in forma di Newton nel modo seguente:
$$p(x)=\boxed{f[x_0]}+\boxed{f[x_0,x_1]}(x-x_0)+\boxed{f[x_0,x_1,x_2]}(x-x_0)(x-x_1)+\boxed{f[x_0,x_1,x_2,x_3]}(x-x_0)(x-x_1)(x-x_2)$$
### Prima parte: tabella delle differenze divise
La prima parte dell'algoritmo calcola le differenze divise riquadrate (in blu alla lavagna) usando la tabella delle differenze divise, colonna per colonna. La prima colonna contiene i dati:
$$f[x_0]=y_0=\boxed{0}\qquad f[x_1]=y_1=3\qquad f[x_2]=y_2=1\qquad f[x_3]=y_3=1$$
**Seconda colonna** (sono rapporti incrementali):
$$f[x_0,x_1]=\frac{f[x_1]-f[x_0]}{x_1-x_0}=\frac{3-0}{1}=\boxed{3}\qquad f[x_0,x_2]=\frac{f[x_2]-f[x_0]}{x_2-x_0}=\frac12\qquad f[x_0,x_3]=\frac{f[x_3]-f[x_0]}{x_3-x_0}=\frac13$$
**Terza colonna:**
$$f[x_0,x_1,x_2]=\frac{f[x_0,x_2]-f[x_0,x_1]}{x_2-x_1}=\frac{\frac12-3}{1}=\boxed{-\frac52}\qquad f[x_0,x_1,x_3]=\frac{f[x_0,x_3]-f[x_0,x_1]}{x_3-x_1}=\frac{\frac13-3}{2}=-\frac43$$
**Quarta colonna:**
$$f[x_0,x_1,x_2,x_3]=\frac{f[x_0,x_1,x_3]-f[x_0,x_1,x_2]}{x_3-x_2}=\frac{-\frac43+\frac52}{1}=\boxed{\frac76}$$
### Seconda parte: Ruffini–Horner
Si applica la ricorsione $h_n=f[x_0,\dots,x_n]$, $h_i=f[x_0,\dots,x_i]+(t-x_i)\,h_{i+1}$ con $t=2{,}3$:
$$\begin{aligned}
h_3&=f[x_0,x_1,x_2,x_3]=\frac76\\
h_2&=f[x_0,x_1,x_2]+(t-x_2)\,h_3=-\frac52+(2{,}3-2)\,\frac76=-\frac{43}{20}\\
h_1&=f[x_0,x_1]+(t-x_1)\,h_2=3+(2{,}3-1)\left(-\frac{43}{20}\right)=\frac{41}{200}\\
h_0&=f[x_0]+(t-x_0)\,h_1=0+(2{,}3-0)\,\frac{41}{200}=\frac{943}{2000}=p(2{,}3)
\end{aligned}$$
I conti si fanno comodamente scrivendo $2{,}3=\frac{23}{10}$; all'esame si può usare la calcolatrice.
## Aggiunta di un nodo d'interpolazione
Nella pratica capita spesso che ai dati già interpolati se ne aggiunga uno nuovo, ad esempio per una nuova rilevazione: si vuole allora il polinomio d'interpolazione che passa anche per il nuovo dato. La forma di Newton è particolarmente conveniente quando ai dati d'interpolazione $(x_0,y_0),\dots,(x_n,y_n)$ ne viene aggiunto uno nuovo $(x_{n+1},y_{n+1})$ con $x_{n+1}\neq x_0,\dots,x_n$ (il nuovo nodo deve essere distinto dai precedenti).
### Perché conviene la forma di Newton
Sia $f(x)$ una qualsiasi funzione tale che $f(x_i)=y_i$ $\forall i=0,\dots,n+1$, nuovo nodo compreso: serve solo per poter scrivere le differenze divise, non va esplicitata. Il polinomio d'interpolazione $p(x)$ dei dati vecchi $(x_0,y_0),\dots,(x_n,y_n)$ si scrive in forma di Newton come
$$p(x)=f[x_0]+f[x_0,x_1](x-x_0)+f[x_0,x_1,x_2](x-x_0)(x-x_1)+\dots+f[x_0,\dots,x_n](x-x_0)\cdots(x-x_{n-1})$$
e il polinomio d'interpolazione $q(x)$ dei dati $(x_0,y_0),\dots,(x_{n+1},y_{n+1})$ si scrive in forma di Newton come
$$q(x)=p(x)+f[x_0,\dots,x_n,x_{n+1}](x-x_0)\cdots(x-x_n)$$
La forma di Newton è **incrementale**: partendo dal polinomio sui nodi precedenti basta aggiungere un termine. Con la forma canonica invece bisognerebbe ricalcolare tutti i coefficienti da capo, risolvendo un nuovo sistema con la matrice di Vandermonde.

> [!info] E se $p(x)$ fosse in forma canonica?
> A lezione è stato chiesto se basti aggiungere l'ultimo termine anche avendo $p(x)$ in forma canonica. L'uguaglianza $q(x)=p(x)+f[x_0,\dots,x_{n+1}](x-x_0)\cdots(x-x_n)$ vale comunque, ma per calcolare il nuovo coefficiente servono le differenze divise diagonali, che la forma canonica non fornisce: andrebbero ricalcolate tutte, il che equivale a calcolare prima la forma di Newton, e il guadagno sparisce.
### Costo del nuovo coefficiente
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
## Esempio: $\cos(\pi x)+x^2$ con aggiunta di un nodo
> [!example] Esempio
> Consideriamo $f(x)=\cos(\pi x)+x^2$.
> - (a) Scrivere il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0=-1,\ x_1=0,\ x_2=2$ e calcolare $p\left(\frac12\right)$.
> - (b) Scrivere il polinomio d'interpolazione $q(x)$ della funzione $f(x)$ sui nodi precedenti a cui si aggiunge $x_3=1$, e calcolare $q\left(\frac12\right)$.

> [!warning] Leggere tutto il testo prima di scegliere la forma
> Il testo dice solo "scrivere il polinomio d'interpolazione", quindi si può usare la forma che si vuole. Ma il punto (b) parla di aggiunta di un nodo: conviene la forma di Newton. Secondo il docente, chi vuole farsi del male usa la forma canonica, chi vuole farsene meno (ma comunque) quella di Lagrange, chi vuole farsi del bene quella di Newton.
### Punto (a)
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
### Punto (b)
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
## Esercizi
- **1.10** Tramite l'algoritmo descritto, valutare in $t=\frac12$ e $t=4$ il polinomio d'interpolazione della funzione $f(x)=x\sqrt x$ sui nodi $x_0=0,\ x_1=1,\ x_2=4,\ x_3=9$. La prima parte dell'algoritmo (le differenze divise) si fa una volta sola; la seconda si ripete per ciascuno dei due punti (si veda la valutazione in $m$ punti in [[04 - Forma di Newton del polinomio d'interpolazione#Algoritmo di valutazione in un punto del polinomio d'interpolazione]]).
- **1.12** Si consideri la funzione $f(x)=\sin(\pi x)$.
	- (a) Determinare il polinomio d'interpolazione $p(x)$ della funzione $f(x)$ sui nodi $x_0=0,\ x_1=\frac12,\ x_2=1$ e calcolare $p(t)$ per $t=\frac14$ e $t=\frac13$.
	- (b) Determinare il polinomio d'interpolazione $q(x)$ della funzione $f(x)$ sui nodi precedenti ai quali si aggiunge un nuovo nodo $x_3=\frac34$ e calcolare $q(t)$ per $t=\frac14$ e $t=\frac13$.

Con questo finisce la parte sull'interpolazione polinomiale.
## Integrazione numerica
L'integrazione numerica è la branca dell'analisi numerica che si occupa di approssimare gli integrali, che molto raramente si riescono a calcolare in modo esatto (come $\int_0^1\sqrt{\cos x}\,dx$). Esistono molti metodi; nel corso se ne vede uno solo, la **formula dei trapezi**.
## Formula dei trapezi
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
