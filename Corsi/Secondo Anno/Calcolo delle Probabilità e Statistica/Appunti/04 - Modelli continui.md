# Modelli continui
Appunti sui **modelli continui** del corso (lezioni 15-...), organizzati nelle seguenti sezioni:
1. [[04 - Modelli continui#Variabili aleatorie continue|Variabili aleatorie continue]] — definizione di v.a. continua, densità continua, $F_{X}'=f_{X}$ quasi ovunque, analogie e differenze con il caso discreto.
2. [[04 - Modelli continui#Distribuzione uniforme continua|Distribuzione uniforme continua]] — $X\sim U(a,b)$, funzione di distribuzione e densità, calcolo di probabilità con il metodo delle lunghezze.
3. [[04 - Modelli continui#Distribuzione esponenziale|Distribuzione esponenziale]] — $X\sim Exp(\lambda)$, mancanza di memoria e legame con la geometrica.
4. [[04 - Modelli continui#Esercizi su densità continue|Esercizi su densità continue]] — determinazione della costante di normalizzazione e calcolo di probabilità.
5. [[04 - Modelli continui#Quantili di una variabile aleatoria continua|Quantili di una variabile aleatoria continua]] — quantile di ordine $\alpha$ e mediana, con esempi per uniforme ed esponenziale.
6. [[04 - Modelli continui#Trasformazioni di variabili aleatorie continue|Trasformazioni di variabili aleatorie continue]] — densità di $Y=f(X)$ nel caso di $f$ affine non costante.
7. [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|Trasformazioni monotone di variabili aleatorie continue]] — procedimento caso per caso per $f$ monotona, con esercizi.
## Nota sulla struttura
Il prof tratta questi argomenti come un unico capitolo (Capitolo 4). I marcatori `--- Fine lezione NN ---` all'interno delle sezioni conservano la corrispondenza con i PDF delle lezioni in `Materiale Didattico/Lezioni/6 CFU/`. Blocco successivo a [[02 - Modelli discreti]] e a [[03 - Speranza matematica e momenti]].

## Variabili aleatorie continue
Definizione di v.a. continua tramite la densità, relazione $F_{X}'=f_{X}$ quasi ovunque e confronto sistematico con il caso discreto.
### Definizione
Una v.a. $X$ è una **v.a. continua** se esiste una funzione $f_{X}$ tale che $$\begin{bmatrix}
F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx\qquad\forall\ t\in \mathbb{R}
\end{bmatrix}\qquad(\square)$$dove $F_{X}$ è la [[02 - Modelli discreti#Funzione di distribuzione di una v.a. reale|funzione di distribuzione]]. In tal caso la funzione $f_{X}$ (lettera minuscola) è detta **densità continua**.
### Osservazioni su $f_{X}$ e $F_{X}$
- In generale $f_{X}$ **non è unica**: possiamo avere un'altra $g_{X}$ che realizza la condizione $(\square)$ in maniera un po' diversa da $f_{X}$ (si veda [[#Non unicità della densità (esempio)|l'esempio più avanti]]).
- In generale $f_{X}$ **non è continua** (vedremo esempi specifici). Però, se vale $(\square)$, allora $F_{X}$ è continua.
- È possibile costruire casi per cui $F_{X}$ è continua ma la condizione $(\square)$ non è verificata; la costruzione va oltre gli scopi del corso.

### $F_{X}'=f_{X}$ quasi ovunque
In generale $F_{X}$ è derivabile in "quasi tutti i punti", perché $F_{X}$ è una funzione **non decrescente**. L'insieme dei punti dove $F_{X}$ non è derivabile è un insieme "trascurabile" (spesso negli esercizi è un insieme finito o numerabile). Nei punti $t$ dove $F_{X}$ è derivabile si ha $F_{X}'(t)=f_{X}(t)$. In conclusione $$F_{X}'(t)=f_{X}(t)\quad\text{in "quasi tutti i punti }t\in \mathbb{R}\text{"}$$(le affermazioni tra virgolette si potrebbero precisare con strumenti matematici oltre gli scopi del corso).
### Analogie e differenze tra densità discrete e continue
Il punto di partenza comune è $F_{X}(t)=P(X\leq t)$, che si scrive $$F_{X}(t)=P(X\leq t)=\underset{x_{k}\leq t}{\sum_{x_{k}\in \delta_{X}}}P_{X}(x_{k})\quad(\text{caso discreto})\qquad\qquad F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx\quad(\text{caso continuo})$$
#### Analogie
$$\begin{array}{ll}
\text{caso discreto} & \text{caso continuo} \\
\hline
P_{X}(x)\geq 0 & f_{X}(x)\geq 0 \\
\displaystyle\sum_{x_{k}\in \delta_{X}}P_{X}(x_{k})=1 & \displaystyle\int_{-\infty}^{\infty}f_{X}(x)\,dx=1 \\
\displaystyle P(X\in A)=\underset{x_{k}\in A}{\sum_{x_{k}\in \delta_{X}}}P_{X}(x_{k})\ (\forall A\subseteq \mathbb{R}) & \displaystyle P(X\in A)=\int_{A}f_{X}(x)\,dx\ (\forall A\subseteq \mathbb{R}\text{ per cui ha senso l'integrale})
\end{array}$$
#### Differenze
$$\begin{array}{ll}
\text{caso discreto} & \text{caso continuo} \\
\hline
P(X=x)=0\ \forall x\in \mathbb{R}\ \text{è \textbf{falso}} & P(X=x)=0\ \forall x\in \mathbb{R}\ \text{è \textbf{vero}} \\
\text{(non vero per }x\in \delta_{X}\text{)} & \\
P(a\leq X\leq b),\ P(a\leq X<b),\dots\text{ possono differire} & P(a\leq X\leq b)=P(a\leq X<b)=P(a<X\leq b)=P(a<X<b) \\
P_{X}\text{ definita in maniera univoca} & f_{X}\ \textbf{non}\text{ definita in maniera univoca}
\end{array}$$La differenza sulle probabilità degli intervalli segue dal fatto che nel continuo $P(X=a)=P(X=b)=0$: aggiungere o togliere gli estremi non cambia la probabilità.
### Non unicità della densità (esempio)
In generale, se $f_{X}$ è una densità continua, lo è anche una qualsiasi altra funzione $g_{X}$ per cui $\{x\in \mathbb{R}:f_{X}(x)\neq g_{X}(x)\}$ è finito o numerabile. Consideriamo $$f_{X}(x)=1_{[0,1]}(x)=\begin{cases}1 & x\in[0,1] \\ 0 & \text{altrimenti}\end{cases}\qquad g_{X}(x)=1_{(0,1)}(x)=\begin{cases}1 & x\in(0,1) \\ 0 & \text{altrimenti}\end{cases}$$Quindi $\{x:g_{X}(x)\neq f_{X}(x)\}=\{0,1\}$. In corrispondenza si vede che $$F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx=\int_{-\infty}^{t}g_{X}(x)\,dx=\begin{cases}0 & t<0 \\ t & 0\leq t\leq 1 \\ 1 & t>1\end{cases}$$In entrambi i casi si ottiene la stessa $F_{X}$, perché contano le **aree** disegnate e non i valori di $f_{X}$ e $g_{X}$ nei punti $x=0$ e $x=1$. In effetti $F_{X}$ è una funzione di distribuzione: è non decrescente, $F_{X}(x)\to 1$ per $x\to+\infty$, $F_{X}(x)\to 0$ per $x\to-\infty$, ed è continua (quindi anche continua a destra).
> [!info] Abuso di linguaggio
> Si parla di "densità continua $f_{X}(x)$ di una v.a. $X$ continua" per abuso di linguaggio: in realtà ci sono **infinite versioni** della densità continua (che differiscono in insiemi trascurabili di punti) e definiscono la stessa $F_{X}$. In questo esempio $f_{X}$ non è continua (discontinuità in $x=0$ e $x=1$); lo stesso vale per $g_{X}$.

### Verso le distribuzioni notevoli continue
Introdurremo i primi esempi di distribuzioni notevoli continue: la [[04 - Modelli continui#Distribuzione uniforme continua|distribuzione uniforme]] e la [[04 - Modelli continui#Distribuzione esponenziale|distribuzione esponenziale]]; più avanti la distribuzione Gamma e la distribuzione Normale (o Gaussiana).
> [!info] Differenza con il caso discreto
> Le distribuzioni notevoli continue vengono definite **a partire dalle espressioni di $F_{X}$ e $f_{X}$**; questo è un po' diverso dal caso discreto, dove si traeva ispirazione da qualche "caso pratico".

--- Fine parte sulle variabili aleatorie continue (lezione 15, pp. 1-8) ---

## Distribuzione uniforme continua
Prima distribuzione notevole continua: densità costante su un intervallo limitato, con il calcolo di probabilità tramite il metodo delle lunghezze.
### Definizione
Una v.a. $X$ ha **distribuzione uniforme continua** su un intervallo limitato $(a,b)$ se $$F_{X}(t)=\begin{cases}
0 & t<a \\
\dfrac{t-a}{b-a} & a\leq t\leq b \\
1 & t>b
\end{cases}$$In simboli scriveremo $X\sim U(a,b)$.
### Densità
La funzione $F_{X}$ non è derivabile per $t=a$ e $t=b$. Negli altri punti lo è e si ha $$F_{X}'(t)=\begin{cases}
\dfrac{1}{b-a} & a<t<b \\
0 & \text{altrimenti (per }t<a\text{ e }t>b)
\end{cases}$$Quindi possiamo dire ad esempio che $$f_{X}(t)=\begin{cases}
\dfrac{1}{b-a} & a<t<b \\
0 & \text{altrimenti}
\end{cases}=\begin{bmatrix}\dfrac{1}{b-a}1_{(a,b)}(t)\end{bmatrix}$$dove $1_{A}(x)=\begin{cases}1 & x\in A \\ 0 & x\notin A\end{cases}$ (per $A\subseteq \mathbb{R}$).
> [!info] Estremi irrilevanti
> Per la [[04 - Modelli continui#Non unicità della densità (esempio)|non unicità della densità]], al posto di $(a,b)$ si poteva mettere $[a,b]$, $[a,b)$ oppure $(a,b]$: i valori negli estremi non cambiano $F_{X}$.

#### Verifica della normalizzazione
Verifichiamo che $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$ (quindi $\frac{1}{b-a}$ può essere vista come una costante di normalizzazione): $$\int_{-\infty}^{\infty}f_{X}(x)\,dx=\underset{=0}{\underbrace{\int_{-\infty}^{a}f_{X}(x)\,dx}}+\int_{a}^{b}f_{X}(x)\,dx+\underset{=0}{\underbrace{\int_{b}^{\infty}f_{X}(x)\,dx}}=\int_{a}^{b}\frac{1}{b-a}\,dx=\left[ \frac{x}{b-a} \right]_{x=a}^{x=b}=\frac{b-a}{b-a}=1$$In accordo con il fatto che l'area del rettangolo di base $(a,b)$ e altezza $\frac{1}{b-a}$ è uguale a 1.
### Esercizio ($U(0,5)$)
Sia $X\sim U(0,5)$. Calcolare $P(4\leq X\leq 6)$ e $P(2\leq X\leq 4\mid 1\leq X\leq 3)$.
**Prima probabilità (due modi).** $$P(4\leq X\leq 6)=\int_{4}^{6}f_{X}(x)\,dx=\int_{4}^{6}\frac{1}{5-0}1_{(0,5)}(x)\,dx=\int_{4}^{5}\frac{1}{5}\,dx=\frac{1}{5}[x]_{x=4}^{x=5}=\frac{5-4}{5}=\frac{1}{5}$$oppure, con la funzione di distribuzione, $$P(4\leq X\leq 6)=F_{X}(6)-F_{X}(4)=1-\frac{4-0}{5-0}=1-\frac{4}{5}=\frac{1}{5}$$
**Probabilità condizionata.** $$P(2\leq X\leq 4\mid 1\leq X\leq 3)=\frac{P(\{2\leq X\leq 4\}\cap\{1\leq X\leq 3\})}{P(\{1\leq X\leq 3\})}=\frac{P(2\leq X\leq 3)}{P(1\leq X\leq 3)}=\frac{\int_{2}^{3}\frac{1}{5}\,dx}{\int_{1}^{3}\frac{1}{5}\,dx}=\frac{[x]_{2}^{3}}{[x]_{1}^{3}}=\frac{3-2}{3-1}=\frac{1}{2}$$
### Metodo delle lunghezze
I risultati precedenti possono essere ottenuti senza fare troppi calcoli, con un procedimento adattabile a tutti i casi con distribuzione uniforme: per $X\sim U(a,b)$ la probabilità di un intervallo è il rapporto tra la sua lunghezza (intersecata con $(a,b)$) e la lunghezza di $(a,b)$. Infatti, per $X\sim U(0,5)$, $$P(4\leq X\leq 6)=\frac{\text{lunghezza}((4,6)\cap(0,5))}{\text{lunghezza}(0,5)}=\frac{\text{lunghezza}(4,5)}{5}=\frac{1}{5}$$ $$P(2\leq X\leq 4\mid 1\leq X\leq 3)=\frac{\text{lunghezza}((2,4)\cap(1,3)\cap(0,5))}{\text{lunghezza}((1,3)\cap(0,5))}=\frac{\text{lunghezza}(2,3)}{\text{lunghezza}(1,3)}=\frac{3-2}{3-1}=\frac{1}{2}$$(le divisioni per $\text{lunghezza}(0,5)$ a numeratore e denominatore si semplificano).
#### Un altro esempio ($U(3,10)$)
Sia $X\sim U(3,10)$. Calcolare $P(6\leq X\leq 11)$ e $P(6\leq X\leq 11\mid 5\leq X\leq 9)$. Con il metodo delle lunghezze: $$P(6\leq X\leq 11)=\frac{\text{lunghezza}((6,11)\cap(3,10))}{\text{lunghezza}(3,10)}=\frac{\text{lunghezza}(6,10)}{10-3}=\frac{10-6}{7}=\frac{4}{7}$$ $$P(6\leq X\leq 11\mid 5\leq X\leq 9)=\frac{\text{lunghezza}((6,11)\cap(5,9)\cap(3,10))}{\text{lunghezza}((5,9)\cap(3,10))}=\frac{\text{lunghezza}(6,9)}{\text{lunghezza}(5,9)}=\frac{9-6}{9-5}=\frac{3}{4}$$

--- Fine parte sulla distribuzione uniforme continua (lezione 15, pp. 9-12) ---

## Distribuzione esponenziale
Distribuzione notevole continua su $(0,\infty)$, caratterizzata dalla proprietà di mancanza di memoria e strettamente legata alla geometrica.
### Definizione
Una v.a. $X$ ha **distribuzione esponenziale** di parametro $\lambda>0$ se $$F_{X}(t)=\begin{cases}
1-e^{-\lambda t} & t\geq 0 \\
0 & t<0
\end{cases}$$In simboli scriveremo $X\sim Exp(\lambda)$. Il grafico di $F_{X}$ ha asintoto orizzontale $y=1$.
### Densità
La funzione $F_{X}$ non è derivabile per $t=0$. Negli altri punti lo è e si ha $$F_{X}'(t)=\begin{cases}
\lambda e^{-\lambda t} & t>0 \\
0 & \text{altrimenti (per }t<0)
\end{cases}$$Quindi possiamo dire ad esempio che $$f_{X}(t)=\begin{cases}
\lambda e^{-\lambda t} & t>0 \\
0 & \text{altrimenti}
\end{cases}=\begin{bmatrix}\lambda e^{-\lambda t}1_{(0,\infty)}(t)\end{bmatrix}$$(per la [[04 - Modelli continui#Non unicità della densità (esempio)|non unicità della densità]] si poteva anche usare $t\geq 0$ e $1_{[0,\infty)}$).
#### Verifica della normalizzazione
Verifichiamo che $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$ (quindi $\lambda$ può essere vista come una costante di normalizzazione): $$\int_{-\infty}^{\infty}f_{X}(x)\,dx=\underset{=0}{\underbrace{\int_{-\infty}^{0}f_{X}(x)\,dx}}+\int_{0}^{\infty}\lambda e^{-\lambda x}\,dx=[-e^{-\lambda x}]_{x=0}^{x=\infty}=-\underset{=0}{\underbrace{e^{-\infty}}}-(-\underset{=1}{\underbrace{e^{0}}})=0+1=1$$(con abuso di notazione per $x=\infty$).
### Proprietà di mancanza di memoria
> [!quote] Mancanza di memoria
> Sia $X\sim Exp(\lambda)$. Allora $$\begin{bmatrix}P(X>t+s\mid X>s)=P(X>t)\qquad\forall\ t,s>0\end{bmatrix}$$

> [!info] Interpretazione
> Se $X$ rappresenta un **tempo di funzionamento**: dato che c'è funzionamento al tempo $s$, la probabilità di funzionare per un ulteriore tempo $t$ è la stessa che si avrebbe all'inizio (contando il tempo $t$ da zero). Quindi ci si può "dimenticare" che è trascorso il tempo $s$.

#### Dimostrazione
Osserviamo che, per $\tau>0$, $$P(X>\tau)=1-\underset{=1-e^{-\lambda\tau}}{\underbrace{P(X\leq\tau)}}=e^{-\lambda\tau}$$Allora $$P(X>t+s\mid X>s)=\frac{P(\{X>t+s\}\cap\{X>s\})}{P(X>s)}\overset{(\star)}{=}\frac{P(X>t+s)}{P(X>s)}=\frac{e^{-\lambda(t+s)}}{e^{-\lambda s}}=e^{-\lambda t}=P(X>t)\qquad\Box$$dove in $(\star)$ si è usato $\{X>t+s\}\subseteq\{X>s\}$ (con $t,s>0$), quindi $\{X>t+s\}\cap\{X>s\}=\{X>t+s\}$.
> [!info] Caratterizzazione
> La distribuzione esponenziale è l'**unica** distribuzione continua su $(0,\infty)$ che soddisfa la proprietà di mancanza di memoria.

### Legame con la geometrica (parte intera)
Sia $X\sim Exp(\lambda)$ e poniamo $Y=[X]$, dove $[x]=\max\{k\in \mathbb{Z}:k\leq x\}$ è la "parte intera di $x$". Quindi $Y$ assume valori in un insieme al più numerabile. Troviamo la densità discreta di $Y$.
Per ogni $k\in \mathbb{Z}$ si ha $\{Y=k\}=\{k\leq X<k+1\}$ (vale anche se $X$ avesse una distribuzione diversa). Allora, per ogni $k\in \mathbb{Z}$, $$P_{Y}(k)=P(k\leq X<k+1)=\int_{k}^{k+1}f_{X}(x)\,dx=\begin{cases}
0 & k\leq -1 \\
\displaystyle\int_{k}^{k+1}\lambda e^{-\lambda x}\,dx=[-e^{-\lambda x}]_{x=k}^{x=k+1}=e^{-\lambda k}-e^{-\lambda(k+1)} & k\geq 0
\end{cases}$$In conclusione $$P_{Y}(k)=e^{-\lambda k}-e^{-\lambda(k+1)}\qquad\forall\ k\geq 0\text{ intero}$$
> [!quote] $Y=[X]$ è geometrica
> Se poniamo $p=1-e^{-\lambda}$, si ha $1-p=e^{-\lambda}$; quindi $$P_{Y}(k)=e^{-\lambda k}(1-e^{-\lambda})=(1-p)^{k}p\qquad\forall\ k\geq 0$$cioè $Y\sim Geo(p=1-e^{-\lambda})$. In altri termini $$X\sim Exp(\lambda)\ (\text{mancanza di memoria})\implies [X]\sim Geo(p=1-e^{-\lambda})\ (\text{mancanza di memoria})$$

Il legame conserva la [[02 - Modelli discreti#Distribuzione geometrica|mancanza di memoria]]: la geometrica è la controparte discreta dell'esponenziale.

--- Fine parte sulla distribuzione esponenziale (lezione 15, pp. 13-18) ---

## Esercizi su densità continue
Due esercizi tipo: determinare la costante di normalizzazione di una densità e calcolare probabilità sfruttando simmetria e aree.
### Esercizio 1 (parabola su $(0,1)$)
Sia $X$ una v.a. continua con densità continua $f_{X}(x)=cx(1-x)1_{(0,1)}(x)$, dove $c>0$ è una costante di normalizzazione. Trovare il valore di $c$.
Si deve trovare $c$ per cui $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$: $$1=\underset{=0}{\underbrace{\int_{-\infty}^{0}f_{X}(x)\,dx}}+\int_{0}^{1}f_{X}(x)\,dx+\underset{=0}{\underbrace{\int_{1}^{\infty}f_{X}(x)\,dx}}=\int_{0}^{1}cx(1-x)\,dx=c\int_{0}^{1}(x-x^{2})\,dx=c\left[ \frac{x^{2}}{2}-\frac{x^{3}}{3} \right]_{x=0}^{x=1}=c\left( \frac{1}{2}-\frac{1}{3} \right)=c\frac{3-2}{6}=\frac{c}{6}$$Quindi si ha $\frac{c}{6}=1$, da cui segue $\begin{bmatrix}c=6\end{bmatrix}$.
> [!info] Interpretazione
> La densità è una parabola ristretta su $[0,1]$, con la concavità verso il basso, che si annulla in $x=0$ e $x=1$. La costante $c>0$ è scelta in modo che l'area sottesa sia uguale a 1.

### Esercizio 2 (densità triangolare $b|t|$)
Sia $X$ una v.a. continua con densità $f_{X}(t)=b|t|\,1_{(-a,a)}(t)$, per $a,b>0$.
1. Dire quanto vale la costante di normalizzazione $b$ come funzione di $a$.
2. Verificare che in ogni caso $P(X>0)=\frac{1}{2}$.
3. Calcolare $P\left( X>\frac{1}{2} \right)$ per $a=1$.

#### 1) La costante di normalizzazione
Si deve avere $\int_{-\infty}^{\infty}f_{X}(t)\,dt=1$. Allora $$1=\underset{=0}{\underbrace{\int_{-\infty}^{-a}f_{X}}}+\int_{-a}^{a}f_{X}(t)\,dt+\underset{=0}{\underbrace{\int_{a}^{\infty}f_{X}}}=\int_{-a}^{a}b|t|\,dt=b\left( \int_{-a}^{0}\underset{=-t}{\underbrace{|t|}}\,dt+\int_{0}^{a}\underset{=t}{\underbrace{|t|}}\,dt \right)=b\left( -\left[ \frac{t^{2}}{2} \right]_{-a}^{0}+\left[ \frac{t^{2}}{2} \right]_{0}^{a} \right)=b\left( \frac{a^{2}}{2}+\frac{a^{2}}{2} \right)=ba^{2}$$da cui segue $\begin{bmatrix}b=\dfrac{1}{a^{2}}\end{bmatrix}$.
> [!info] Procedimento alternativo (simmetria)
> Poiché $|t|$ è una funzione **pari** ($|t|=|-t|$) e l'intervallo $(-a,a)$ è simmetrico rispetto all'origine, l'integrale su $(-a,a)$ è il doppio di quello su $(0,a)$: $$b\int_{-a}^{a}|t|\,dt=2b\int_{0}^{a}t\,dt=2b\left[ \frac{t^{2}}{2} \right]_{0}^{a}=ba^{2}$$e imponendo $=1$ si ritrova $b=\frac{1}{a^{2}}$ (l'area dei due triangoli è il doppio dell'area del triangolo di destra).

> [!info] Commento su $b=1/a^{2}$
> Non sorprende che $b$ sia **grande per $a$ piccolo** e **piccolo per $a$ grande**: il grafico di $f_{X}$ è formato da due triangoli e l'area totale deve restare uguale a 1, quindi se la base si stringe l'altezza deve crescere (e viceversa).

#### 2) $P(X>0)=\frac{1}{2}$
$$P(X>0)=\int_{0}^{\infty}f_{X}(t)\,dt=\int_{0}^{a}\underset{=\frac{1}{a^{2}}|t|=\frac{t}{a^{2}}}{\underbrace{f_{X}(t)}}\,dt+\underset{=0}{\underbrace{\int_{a}^{\infty}f_{X}}}=\frac{1}{a^{2}}\left[ \frac{t^{2}}{2} \right]_{0}^{a}=\frac{1}{a^{2}}\cdot \frac{a^{2}}{2}=\frac{1}{2}$$Qualunque sia $a$, il grafico di $f_{X}$ è costituito da due triangoli rettangoli con la stessa area, la cui somma è 1; quindi $P(X>0)$ è l'area del "triangolo di destra", cioè $\frac{1}{2}$.
#### 3) $P\left( X>\frac{1}{2} \right)$ per $a=1$
Essendo $a=1$ si ha $b=\frac{1}{a^{2}}=\frac{1}{1^{2}}=1$ (i due triangoli sono isosceli). Allora $$P\left( X>\frac{1}{2} \right)=\int_{1/2}^{\infty}f_{X}(t)\,dt=\int_{1/2}^{1}\underset{=t}{\underbrace{|t|}}\,dt+\underset{=0}{\underbrace{\int_{1}^{\infty}0\,dt}}=\int_{1/2}^{1}t\,dt=\left[ \frac{t^{2}}{2} \right]_{t=1/2}^{t=1}=\frac{1}{2}\left( 1^{2}-\left( \frac{1}{2} \right)^{2} \right)=\frac{1}{2}\left( 1-\frac{1}{4} \right)=\frac{1}{2}\cdot \frac{3}{4}=\frac{3}{8}$$

--- Fine lezione 15 ---

## Quantili di una variabile aleatoria continua
Valore che lascia alla propria sinistra una frazione $\alpha$ assegnata della probabilità; il caso $\alpha=\frac{1}{2}$ è la mediana.
### Definizione
Sia $X$ una v.a. continua con funzione di distribuzione $F_{X}$. Supponiamo che esista un intervallo $(m,M)$ dove $F_{X}$ è **strettamente crescente**; inoltre supponiamo che, se $t\notin(m,M)$, allora $F_{X}(t)=0$ oppure $F_{X}(t)=1$.
> [!info] Estremi infiniti ammessi
> Si ammette di poter avere $m=-\infty$ (allora non si avrà mai $F_{X}(t)=0$) e/o $M=+\infty$ (allora non si avrà mai $F_{X}(t)=1$).

Nelle ipotesi sopra, preso $\alpha\in(0,1)$, si definisce **quantile di ordine $\alpha$ di $X$** l'unico valore $q_{\alpha}\in(m,M)$ tale che $$\begin{bmatrix}F_{X}(q_{\alpha})=\alpha\end{bmatrix}$$
> [!info] Terminologia
> Il valore $q_{1/2}$ (cioè $q_{\alpha}$ per $\alpha=\frac{1}{2}$) è detto **mediana**.

### Esempio (uniforme)
$X\sim U(a,b)$. In questo caso $(m,M)=(a,b)$. Da $F_{X}(q_{\alpha})=\alpha$: $$\frac{q_{\alpha}-a}{b-a}=\alpha\implies q_{\alpha}-a=\alpha(b-a)\implies\begin{bmatrix}q_{\alpha}=a+\alpha(b-a)\end{bmatrix}$$Inoltre la mediana è $$q_{1/2}=a+\frac{1}{2}(b-a)=a-\frac{a}{2}+\frac{b}{2}=\frac{a}{2}+\frac{b}{2}=\frac{a+b}{2}$$cioè il **punto medio dell'intervallo**.
### Esempio (esponenziale)
$X\sim Exp(\lambda)$. In questo caso $(m,M)=(0,\infty)$. Da $F_{X}(q_{\alpha})=\alpha$: $$1-e^{-\lambda q_{\alpha}}=\alpha\implies e^{-\lambda q_{\alpha}}=1-\alpha\implies -\lambda q_{\alpha}=\log(1-\alpha)\implies\begin{bmatrix}q_{\alpha}=-\frac{1}{\lambda}\log(1-\alpha)\end{bmatrix}$$Inoltre la mediana è $$q_{1/2}=-\frac{1}{\lambda}\log\left( 1-\frac{1}{2} \right)=-\frac{1}{\lambda}\log\left( \frac{1}{2} \right)=\frac{1}{\lambda}\log 2$$(qui $\log$ è il logaritmo naturale).

--- Fine parte sui quantili (lezione 16, pp. 1-3) ---

## Trasformazioni di variabili aleatorie continue
Come ottenere la densità di $Y=f(X)$ quando $X$ è continua: non c'è una formula generale, ma il caso di $f$ affine non costante si tratta una volta per tutte.
### Impostazione
Si fa riferimento al caso in cui si hanno v.a. $Y$ del tipo $Y=f(X)$, dove
- $X$ è una v.a. continua;
- $f:D\subseteq \mathbb{R}\to \mathbb{R}$ per qualche insieme $D$ (dominio della funzione).

In generale, a differenza di quel che accade quando $X$ è discreta, la $Y$ è una v.a. (cioè $\{w\in\ohm:Y(w)\leq t\}\in\mathcal{A}$ per ogni $t\in \mathbb{R}$) solo se $f$ soddisfa certe proprietà. Questo aspetto va oltre gli scopi del corso; nei casi che tratteremo la funzione $f$ avrà sempre le proprietà richieste affinché $Y$ sia una v.a.
> [!warning] $Y=f(X)$ può non essere continua
> **Esempio 1** ($f$ costante): $f(x)=c$ per ogni $x$. Allora $Y=c$ è una v.a. **discreta** ($\delta_{Y}=\{c\}$, $P_{Y}(y)=1$ se $y=c$, $0$ altrimenti).
> **Esempio 2** ($f$ parte intera): $f(x)=[x]$. Allora $Y=[X]$ è **discreta** ($\delta_{Y}\subseteq \mathbb{Z}$, $P_{Y}(y)=P(y\leq X<y+1)$ se $y\in \mathbb{Z}$).

Una casistica degli esercizi proposti farà riferimento al caso in cui $Y$ è **continua** e si deve trovare la densità $f_{Y}$ (che dipenderà da $f$ e da $f_{X}$).
> [!info] Nessuna formula generale
> Non presenteremo una formula generale per ottenere $f_{Y}$ da $f$ e $f_{X}$. L'unico caso che tratteremo in generale è quello di $f$ **affine** ($f(x)=ax+b$), escludendo $a=0$ (altrimenti $f$ sarebbe costante). Per evitare esercizi troppo complicati, in generale $f$ sarà **monotona** su un sottoinsieme $S$ di $D$ con $P(X\in S)=1$, oppure avrà proprietà di simmetria (si veda [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|il procedimento caso per caso]]).

### Il caso di funzione affine non costante
Sia $f(x)=ax+b$ con $a,b\in \mathbb{R}$ tale che $a\neq 0$. Studiamo la funzione di distribuzione di $Y=f(X)$: $$F_{Y}(y)=P(Y\leq y)=P(aX+b\leq y)=P(aX\leq y-b)=\begin{cases}
P\left( X\leq \dfrac{y-b}{a} \right)=F_{X}\left( \dfrac{y-b}{a} \right) & \text{se }a>0 \\[3mm]
P\left( X\geq \dfrac{y-b}{a} \right)=1-F_{X}\left( \dfrac{y-b}{a} \right) & \text{se }a<0
\end{cases}$$Nel caso $a<0$ si è diviso per $a<0$ (il verso della disuguaglianza si inverte) e si è usato che $X$ è continua, quindi $P\left( X\geq \frac{y-b}{a} \right)=P\left( X>\frac{y-b}{a} \right)=1-F_{X}\left( \frac{y-b}{a} \right)$.
Allora possiamo concludere derivando membro a membro rispetto a $y$: $$f_{Y}(y)=\begin{cases}
f_{X}\left( \dfrac{y-b}{a} \right)\cdot \dfrac{1}{a} & \text{se }a>0 \\[3mm]
-f_{X}\left( \dfrac{y-b}{a} \right)\cdot \dfrac{1}{a} & \text{se }a<0
\end{cases}=\begin{bmatrix}\dfrac{1}{|a|}f_{X}\left( \dfrac{y-b}{a} \right)\end{bmatrix}$$
### Esercizio (una trasformazione affine di un'uniforme resta uniforme)
Sia $X\sim U(0,1)$ e sia $Y=aX+b$ con $a\neq 0$. Verificare che $Y\sim U(b,a+b)$ se $a>0$, e $Y\sim U(a+b,b)$ se $a<0$.
Si ha $f_{X}(x)=\frac{1}{1-0}1_{(0,1)}(x)=1_{(0,1)}(x)$. Con la formula precedente $$f_{Y}(y)=\frac{1}{|a|}f_{X}\left( \frac{y-b}{a} \right)=\frac{1}{|a|}1_{(0,1)}\left( \frac{y-b}{a} \right)$$Dobbiamo studiare la condizione $\frac{y-b}{a}\in(0,1)$ per capire com'è fatta $1_{(0,1)}\left( \frac{y-b}{a} \right)$:
- **se $a>0$**: $0<\frac{y-b}{a}<1\iff 0<y-b<a\iff b<y<a+b$, quindi $$f_{Y}(y)=\frac{1}{a}1_{(b,a+b)}(y)=\frac{1}{(a+b)-b}1_{(b,a+b)}(y)\implies Y\sim U(b,a+b)$$
- **se $a<0$**: $0<\frac{y-b}{a}<1\iff 0>y-b>a\iff b>y>a+b$, quindi $$f_{Y}(y)=\frac{1}{-a}1_{(a+b,b)}(y)=\frac{1}{b-(a+b)}1_{(a+b,b)}(y)\implies Y\sim U(a+b,b)$$

### Esercizio ($Y=\frac{\pi}{2}-X$)
Sia $X$ una v.a. con densità continua $f_{X}(x)=\sin x\cdot 1_{(0,\pi/2)}(x)$. Trovare la densità continua di $Y=\frac{\pi}{2}-X$.
È il caso con $a=-1$ e $b=\frac{\pi}{2}$. Quindi $$f_{Y}(y)=\frac{1}{|-1|}f_{X}\left( \frac{y-\frac{\pi}{2}}{-1} \right)=f_{X}\left( \frac{\pi}{2}-y \right)=\sin\left( \frac{\pi}{2}-y \right)1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)=\cos y\cdot 1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)$$(si è usato $\sin\left( \frac{\pi}{2}-y \right)=\cos y$). Studiamo la funzione $1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)$: $$0<\frac{\pi}{2}-y<\frac{\pi}{2}\iff 0>y-\frac{\pi}{2}>-\frac{\pi}{2}\iff \frac{\pi}{2}>y>0$$Quindi $$\begin{bmatrix}f_{Y}(y)=\cos y\cdot 1_{(0,\pi/2)}(y)\end{bmatrix}$$

--- Fine parte sulle trasformazioni affini (lezione 16, pp. 4-10) ---

## Trasformazioni monotone di variabili aleatorie continue
Procedimento caso per caso per la densità di $Y=f(X)$ quando $f$ è monotona ma non affine: si studia il codominio, si scrive $F_{Y}$ e si deriva.
### Il procedimento
Quando $f$ non è [[04 - Modelli continui#Il caso di funzione affine non costante|affine]] non c'è una formula generale. Se $f$ è **monotona** (su un sottoinsieme $S$ del dominio con $P(X\in S)=1$) si procede così:
1. **Codominio di $Y$**: usando la monotonia di $f$, si determina l'intervallo dei valori assunti da $Y=f(X)$. Se $f$ è crescente su $(m,M)$ con $P(X\in(m,M))=1$, allora $Y$ assume valori in $(f(m),f(M))$ (per $f$ decrescente in $(f(M),f(m))$).
2. **Funzione di distribuzione**: si scrive $F_{Y}(y)=P(f(X)\leq y)$, si "inverte" $f$ per ricondursi a una probabilità su $X$ e la si esprime tramite $F_{X}$ o un integrale di $f_{X}$.
3. **Derivazione**: si deriva $F_{Y}$ nei punti dove è derivabile per ottenere $f_{Y}$.

> [!info] Monotonia delle composizioni
> Ogni volta che si compone una funzione **crescente** la monotonia non cambia; ogni volta che si compone una funzione **decrescente** la monotonia si inverte. Contando il numero di inversioni si stabilisce se $f$ è crescente o decrescente.

### Esercizio ($Y=\sqrt{X}$, $X\sim U(4,9)$)
Sia $X\sim U(4,9)$ e sia $Y=\sqrt{X}$. Trovare la densità continua di $Y$.
Su $(4,9)$ la funzione $\sqrt{\cdot}$ è crescente, quindi $Y$ assume valori in $(\sqrt{4},\sqrt{9})=(2,3)$ e $P(Y\in(2,3))=1$. Allora $$F_{Y}(y)=\begin{cases}0 & y\leq 2 \\ (\ast) & 2<y<3 \\ 1 & y\geq 3\end{cases}$$dove, per $y\in(2,3)$ (quindi $y^{2}\in(4,9)$), $$(\ast)=P(Y\leq y)=P(\sqrt{X}\leq y)=P(X\leq y^{2})=\int_{4}^{y^{2}}\frac{1}{9-4}\,dx=\frac{1}{5}[x]_{x=4}^{x=y^{2}}=\frac{y^{2}-4}{5}$$La $F_{Y}$ è continua. Derivando ($F_{Y}$ non è derivabile in $y=2$ e $y=3$) si ha $$f_{Y}(y)=\begin{cases}0 & y<2 \\ \dfrac{2y}{5} & 2<y<3 \\ 0 & y>3\end{cases}=\frac{2y}{5}1_{(2,3)}(y)$$($f_{Y}$ è discontinua). In effetti si verifica che $\int_{2}^{3}\frac{2y}{5}\,dy=\frac{1}{5}[y^{2}]_{2}^{3}=\frac{9-4}{5}=1$.
### Esercizio ($X\sim U(0,1)$: due trasformazioni)
Sia $X\sim U(0,1)$, con $\alpha,\lambda>0$. Trovare la densità continua di $Y=-\frac{1}{\lambda}\log(1-X^{\alpha})$ e di $Z=e^{-\alpha X}$.
#### 1) $Y=-\frac{1}{\lambda}\log(1-X^{\alpha})$
Vediamo $f$ come composizione: $x\mapsto y_{1}=x^{\alpha}$ (crescente, $\alpha>0$); $y_{1}\mapsto y_{2}=1-y_{1}$ (decrescente); $y_{2}\mapsto y_{3}=\log y_{2}$ (crescente); $y_{3}\mapsto y_{4}=-\frac{1}{\lambda}y_{3}$ (decrescente, $\lambda>0$). Ci sono **due inversioni** (due funzioni decrescenti), quindi $f$ è crescente e $Y$ assume valori in $$(f(0),f(1))=\left( -\tfrac{1}{\lambda}\log(1-0),\ -\tfrac{1}{\lambda}\log(1-1) \right)=(0,+\infty)$$Allora $F_{Y}(y)=0$ per $y\leq 0$, e per $y>0$ $$F_{Y}(y)=P\left( -\tfrac{1}{\lambda}\log(1-X^{\alpha})\leq y \right)=P\left( \log(1-X^{\alpha})\geq -\lambda y \right)=P\left( 1-X^{\alpha}\geq e^{-\lambda y} \right)=P\left( X\leq(1-e^{-\lambda y})^{1/\alpha} \right)=\int_{0}^{(1-e^{-\lambda y})^{1/\alpha}}1\,dx=(1-e^{-\lambda y})^{1/\alpha}$$(l'argomento $(1-e^{-\lambda y})^{1/\alpha}\in(0,1)$). Derivando ($F_{Y}$ non derivabile in $y=0$): $$f_{Y}(y)=\frac{1}{\alpha}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}(-e^{-\lambda y})(-\lambda)1_{(0,\infty)}(y)=\begin{bmatrix}\frac{\lambda}{\alpha}e^{-\lambda y}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}1_{(0,\infty)}(y)\end{bmatrix}$$
> [!info] Caso particolare
> Per $\alpha=1$ si ha $f_{Y}(y)=\lambda e^{-\lambda y}1_{(0,\infty)}(y)$, cioè $Y\sim Exp(\lambda)$.

#### 2) $Z=e^{-\alpha X}$
$g(x)=e^{-\alpha x}$ è decrescente (perché $\alpha>0$), quindi $Z$ assume valori in $(g(1),g(0))=(e^{-\alpha},1)$. Allora $$F_{Z}(z)=\begin{cases}0 & z\leq e^{-\alpha} \\ (\ast) & z\in(e^{-\alpha},1) \\ 1 & z\geq 1\end{cases}$$dove, per $z\in(e^{-\alpha},1)$ (quindi $-\frac{1}{\alpha}\log z\in(0,1)$), $$(\ast)=P(e^{-\alpha X}\leq z)=P(-\alpha X\leq \log z)=P\left( X\geq -\tfrac{1}{\alpha}\log z \right)=\int_{-\frac{1}{\alpha}\log z}^{1}1\,dx=[x]_{x=-\frac{1}{\alpha}\log z}^{x=1}=1+\tfrac{1}{\alpha}\log z$$Derivando ($F_{Z}$ non derivabile in $z=e^{-\alpha}$ e $z=1$): $$f_{Z}(z)=\begin{cases}0 & z<e^{-\alpha} \\ \dfrac{1}{\alpha z} & z\in(e^{-\alpha},1) \\ 0 & z>1\end{cases}=\frac{1}{\alpha z}1_{(e^{-\alpha},1)}(z)$$Verifica: $\int_{e^{-\alpha}}^{1}\frac{1}{\alpha z}\,dz=\frac{1}{\alpha}[\log z]_{e^{-\alpha}}^{1}=\frac{1}{\alpha}(0-(-\alpha))=1$.
### Esercizio ($X$ con densità $\alpha x^{\alpha-1}$ su $(0,1)$: potenza e potenza inversa)
Sia $X$ con densità continua $f_{X}(x)=\alpha x^{\alpha-1}1_{(0,1)}(x)$, con $\alpha>0$ (è una densità: $\int_{0}^{1}\alpha x^{\alpha-1}\,dx=[x^{\alpha}]_{0}^{1}=1$). Con $\beta>0$, trovare la densità di $Y=X^{\beta}$ e di $Z=X^{-\beta}$.
#### 1) $Y=X^{\beta}$
$f(x)=x^{\beta}$ è crescente su $(0,1)$, quindi $Y$ assume valori in $(f(0),f(1))=(0,1)$. Allora $F_{Y}(y)=0$ per $y<0$, $=1$ per $y>1$, e per $y\in(0,1)$ (quindi $y^{1/\beta}\in(0,1)$) $$F_{Y}(y)=P(X^{\beta}\leq y)=P(X\leq y^{1/\beta})=\int_{0}^{y^{1/\beta}}\alpha x^{\alpha-1}\,dx=\left[ x^{\alpha} \right]_{0}^{y^{1/\beta}}=(y^{1/\beta})^{\alpha}=y^{\alpha/\beta}$$Derivando ($F_{Y}$ non derivabile in $y=0$ e $y=1$): $$f_{Y}(y)=\begin{bmatrix}\frac{\alpha}{\beta}y^{\frac{\alpha}{\beta}-1}1_{(0,1)}(y)\end{bmatrix}$$
> [!info] Caso particolare
> Se $\frac{\alpha}{\beta}=1$ (cioè $\alpha=\beta$) si ha $Y\sim U(0,1)$.

#### 2) $Z=X^{-\beta}$
$g(x)=x^{-\beta}$ è decrescente su $(0,1)$, quindi $Z$ assume valori in $(g(1),g(0))=(1^{-\beta},0^{-\beta})=(1,\infty)$. Allora $F_{Z}(z)=0$ per $z\leq 1$, e per $z>1$ (quindi $z^{-1/\beta}\in(0,1)$) $$F_{Z}(z)=P(X^{-\beta}\leq z)=P\left( X^{\beta}\geq \tfrac{1}{z} \right)=P(X\geq z^{-1/\beta})=\int_{z^{-1/\beta}}^{1}\alpha x^{\alpha-1}\,dx=[x^{\alpha}]_{z^{-1/\beta}}^{1}=1-(z^{-1/\beta})^{\alpha}=1-z^{-\alpha/\beta}$$Derivando ($F_{Z}$ non derivabile in $z=1$): $$f_{Z}(z)=\frac{\alpha}{\beta}z^{-\frac{\alpha}{\beta}-1}1_{(1,\infty)}(z)=\begin{bmatrix}\frac{\alpha}{\beta}z^{-\left( 1+\frac{\alpha}{\beta} \right)}1_{(1,\infty)}(z)\end{bmatrix}$$Verifica: $\int_{1}^{\infty}\frac{\alpha}{\beta}z^{-(1+\frac{\alpha}{\beta})}\,dz=\frac{\alpha}{\beta}\left[ \frac{z^{-\frac{\alpha}{\beta}}}{-\frac{\alpha}{\beta}} \right]_{1}^{\infty}=[-z^{-\frac{\alpha}{\beta}}]_{1}^{\infty}=-0+1=1$.

--- Fine lezione 16 ---
