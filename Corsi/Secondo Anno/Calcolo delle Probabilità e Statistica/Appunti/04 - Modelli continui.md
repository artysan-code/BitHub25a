# Modelli continui
Appunti sui **modelli continui** del corso (lezioni 15-21), organizzati nelle seguenti sezioni:
1. [[04 - Modelli continui#Variabili aleatorie continue|Variabili aleatorie continue]] — definizione di v.a. continua, densità continua, $F_{X}'=f_{X}$ quasi ovunque, analogie e differenze con il caso discreto.
2. [[04 - Modelli continui#Distribuzione uniforme continua|Distribuzione uniforme continua]] — $X\sim U(a,b)$, funzione di distribuzione e densità, calcolo di probabilità con il metodo delle lunghezze.
3. [[04 - Modelli continui#Distribuzione esponenziale|Distribuzione esponenziale]] — $X\sim Exp(\lambda)$, mancanza di memoria e legame con la geometrica.
4. [[04 - Modelli continui#Esercizi su densità continue|Esercizi su densità continue]] — determinazione della costante di normalizzazione e calcolo di probabilità.
5. [[04 - Modelli continui#Quantili di una variabile aleatoria continua|Quantili di una variabile aleatoria continua]] — quantile di ordine $\alpha$ e mediana, con esempi per uniforme ed esponenziale.
6. [[04 - Modelli continui#Trasformazioni di variabili aleatorie continue|Trasformazioni di variabili aleatorie continue]] — densità di $Y=f(X)$ nel caso di $f$ affine non costante.
7. [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|Trasformazioni monotone di variabili aleatorie continue]] — procedimento caso per caso per $f$ monotona, con esercizi.
8. [[04 - Modelli continui#Altri esercizi sulle trasformazioni monotone|Altri esercizi sulle trasformazioni monotone]] — $Y=\log X$ (con una probabilità in quattro modi), $Y=e^{X}$, $Y=\log(1+X)$ e la distribuzione di Cauchy.
9. [[04 - Modelli continui#Trasformazioni non monotone di variabili aleatorie continue|Trasformazioni non monotone di variabili aleatorie continue]] — metodo della controimmagine per $f$ non monotona, con esercizi e la distribuzione di Laplace.
10. [[04 - Modelli continui#Massimi e minimi di variabili aleatorie continue|Massimi e minimi di variabili aleatorie continue]] — indipendenza continua, distribuzione di $\max$ e $\min$, sistemi in serie/parallelo.
11. [[04 - Modelli continui#Distribuzione normale|Distribuzione normale]] — $N(0,1)$ e $N(\mu,\sigma^{2})$, standardizzazione, funzione $\Phi$ e half-normal (materia di **Es6**).
12. [[04 - Modelli continui#Distribuzione Gamma|Distribuzione Gamma]] — $Gamma(\alpha,\beta)$, funzione $\Gamma$, somma di esponenziali e processo di Poisson.
13. [[04 - Modelli continui#Speranza matematica per variabili aleatorie continue|Speranza matematica per variabili aleatorie continue]] — $\mathbb{E}[X]$, momenti e varianza, media/varianza delle notevoli e la formula $\mathbb{E}[g(X)]$ (materia di **Es5**).
14. [[04 - Modelli continui#Combinazioni lineari di normali indipendenti|Combinazioni lineari di normali indipendenti]] — ogni combinazione lineare di Normali indipendenti è Normale (materia di **Es6**).
## Nota sulla struttura
Il prof tratta questi argomenti come un unico capitolo (Capitolo 4, lezioni 15-21). I marcatori `--- Fine lezione NN ---` all'interno delle sezioni conservano la corrispondenza con i PDF delle lezioni in `Materiale Didattico/Lezioni/6 CFU/`. Blocco successivo a [[02 - Modelli discreti]] e a [[03 - Speranza matematica e momenti]]; prosegue in [[05 - Convergenze e approssimazioni]] (legge dei grandi numeri e teorema del limite centrale).

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
In generale, se $f_{X}$ è una densità continua, lo è anche una qualsiasi altra funzione $g_{X}$ per cui $\{x\in \mathbb{R}:f_{X}(x)\neq g_{X}(x)\}$ è finito o numerabile. Consideriamo $$f_{X}(x)=1_{[0,1]}(x)=\begin{cases}1 & x\in[0,1] \\ 0 & \text{altrimenti}\end{cases}\qquad g_{X}(x)=1_{(0,1)}(x)=\begin{cases}1 & x\in(0,1) \\ 0 & \text{altrimenti}\end{cases}$$Quindi $\{x:g_{X}(x)\neq f_{X}(x)\}=\{0,1\}$. In corrispondenza si vede che $$F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx=\int_{-\infty}^{t}g_{X}(x)\,dx=\begin{cases}0 & t<0 \\ t & 0\leq t\leq 1 \\ 1 & t>1\end{cases}$$In entrambi i casi si ottiene la stessa $F_{X}$, perché contano le **aree** disegnate e non i valori di $f_{X}$ e $g_{X}$ nei punti $x=0$ e $x=1$. In effetti $F_{X}$ è una [[02 - Modelli discreti#Proprietà della funzione di distribuzione $F_{X}$|funzione di distribuzione]]: è non decrescente, $F_{X}(x)\to 1$ per $x\to+\infty$, $F_{X}(x)\to 0$ per $x\to-\infty$, ed è continua (quindi anche continua a destra).
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
**[[01 - Introduzione alla probabilità#Motivazione|Probabilità condizionata]].** $$P(2\leq X\leq 4\mid 1\leq X\leq 3)=\frac{P(\{2\leq X\leq 4\}\cap\{1\leq X\leq 3\})}{P(\{1\leq X\leq 3\})}=\frac{P(2\leq X\leq 3)}{P(1\leq X\leq 3)}=\frac{\int_{2}^{3}\frac{1}{5}\,dx}{\int_{1}^{3}\frac{1}{5}\,dx}=\frac{[x]_{2}^{3}}{[x]_{1}^{3}}=\frac{3-2}{3-1}=\frac{1}{2}$$
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
Sia $X$ una v.a. continua con [[02 - Modelli discreti#Funzione di distribuzione di una v.a. reale|funzione di distribuzione]] $F_{X}$. Supponiamo che esista un intervallo $(m,M)$ dove $F_{X}$ è **strettamente crescente**; inoltre supponiamo che, se $t\notin(m,M)$, allora $F_{X}(t)=0$ oppure $F_{X}(t)=1$.
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
> **Esempio 2** ($f$ [[04 - Modelli continui#Legame con la geometrica (parte intera)|parte intera]]): $f(x)=[x]$. Allora $Y=[X]$ è **discreta** ($\delta_{Y}\subseteq \mathbb{Z}$, $P_{Y}(y)=P(y\leq X<y+1)$ se $y\in \mathbb{Z}$).

Una casistica degli esercizi proposti farà riferimento al caso in cui $Y$ è **continua** e si deve trovare la densità $f_{Y}$ (che dipenderà da $f$ e da $f_{X}$).
> [!info] Nessuna formula generale
> Non presenteremo una [[02 - Modelli discreti#Proposizione (densità di una trasformazione)|formula generale]] per ottenere $f_{Y}$ da $f$ e $f_{X}$. L'unico caso che tratteremo in generale è quello di $f$ **affine** ($f(x)=ax+b$), escludendo $a=0$ (altrimenti $f$ sarebbe costante). Per evitare esercizi troppo complicati, in generale $f$ sarà **monotona** su un sottoinsieme $S$ di $D$ con $P(X\in S)=1$, oppure avrà proprietà di simmetria (si veda [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|il procedimento caso per caso]]).

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
Si ha $f_{X}(x)=\frac{1}{1-0}1_{(0,1)}(x)=1_{(0,1)}(x)$. Con la [[04 - Modelli continui#Il caso di funzione affine non costante|formula precedente]] $$f_{Y}(y)=\frac{1}{|a|}f_{X}\left( \frac{y-b}{a} \right)=\frac{1}{|a|}1_{(0,1)}\left( \frac{y-b}{a} \right)$$Dobbiamo studiare la condizione $\frac{y-b}{a}\in(0,1)$ per capire com'è fatta $1_{(0,1)}\left( \frac{y-b}{a} \right)$:
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
Vediamo $f$ come [[04 - Modelli continui#Il procedimento|composizione]]: $x\mapsto y_{1}=x^{\alpha}$ (crescente, $\alpha>0$); $y_{1}\mapsto y_{2}=1-y_{1}$ (decrescente); $y_{2}\mapsto y_{3}=\log y_{2}$ (crescente); $y_{3}\mapsto y_{4}=-\frac{1}{\lambda}y_{3}$ (decrescente, $\lambda>0$). Ci sono **due inversioni** (due funzioni decrescenti), quindi $f$ è crescente e $Y$ assume valori in $$(f(0),f(1))=\left( -\tfrac{1}{\lambda}\log(1-0),\ -\tfrac{1}{\lambda}\log(1-1) \right)=(0,+\infty)$$Allora $F_{Y}(y)=0$ per $y\leq 0$, e per $y>0$ $$F_{Y}(y)=P\left( -\tfrac{1}{\lambda}\log(1-X^{\alpha})\leq y \right)=P\left( \log(1-X^{\alpha})\geq -\lambda y \right)=P\left( 1-X^{\alpha}\geq e^{-\lambda y} \right)=P\left( X\leq(1-e^{-\lambda y})^{1/\alpha} \right)=\int_{0}^{(1-e^{-\lambda y})^{1/\alpha}}1\,dx=(1-e^{-\lambda y})^{1/\alpha}$$(l'argomento $(1-e^{-\lambda y})^{1/\alpha}\in(0,1)$). Derivando ($F_{Y}$ non derivabile in $y=0$): $$f_{Y}(y)=\frac{1}{\alpha}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}(-e^{-\lambda y})(-\lambda)1_{(0,\infty)}(y)=\begin{bmatrix}\frac{\lambda}{\alpha}e^{-\lambda y}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}1_{(0,\infty)}(y)\end{bmatrix}$$
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

## Altri esercizi sulle trasformazioni monotone
Quattro esercizi che consolidano il [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|procedimento caso per caso]] per $f$ monotona (o monotona su un sottoinsieme $S$ con $P(X\in S)=1$), inclusi due casi che portano a distribuzioni notevoli.
### Esercizio ($Y=\log X$, con una probabilità in quattro modi)
Sia $X$ con densità continua $f_{X}(x)=c\,x^{-2}1_{(1,e^{2})}(x)$, $c>0$. Trovare $c$, la densità di $Y=\log X$ e $P(1\leq Y\leq 3)$.
**Costante.** Da $\int f_{X}=1$: $$1=c\int_{1}^{e^{2}}x^{-2}\,dx=c\left[ -\frac{1}{x} \right]_{1}^{e^{2}}=c\left( -\frac{1}{e^{2}}+1 \right)=c\frac{e^{2}-1}{e^{2}}\implies c=\frac{e^{2}}{e^{2}-1}$$
**Densità di $Y$.** $f(x)=\log x$ è crescente su $(1,e^{2})$, quindi $Y$ assume valori in $(\log 1,\log e^{2})=(0,2)$. Per $y\in(0,2)$ (quindi $e^{y}\in(1,e^{2})$) $$F_{Y}(y)=P(\log X\leq y)=P(X\leq e^{y})=\int_{1}^{e^{y}}\frac{e^{2}}{e^{2}-1}x^{-2}\,dx=\frac{e^{2}}{e^{2}-1}\left[ -\frac{1}{x} \right]_{1}^{e^{y}}=\frac{e^{2}}{e^{2}-1}(1-e^{-y})$$Derivando ($F_{Y}=0$ per $y\leq 0$, $=1$ per $y\geq 2$): $$f_{Y}(y)=\begin{bmatrix}\frac{e^{2}}{e^{2}-1}e^{-y}1_{(0,2)}(y)\end{bmatrix}$$(in particolare $F_{Y}(2)=\frac{e^{2}}{e^{2}-1}(1-e^{-2})=\frac{e^{2}-1}{e^{2}-1}=1$, ok).
**$P(1\leq Y\leq 3)=\frac{1}{e+1}$, in quattro modi.**
- **1° (da $f_{Y}$)**: $$P(1\leq Y\leq 3)=\int_{1}^{3}\frac{e^{2}}{e^{2}-1}e^{-y}1_{(0,2)}(y)\,dy=\frac{e^{2}}{e^{2}-1}\int_{1}^{2}e^{-y}\,dy=\frac{e^{2}}{e^{2}-1}(e^{-1}-e^{-2})=\frac{e^{2}}{e^{2}-1}\cdot\frac{e-1}{e^{2}}=\frac{e-1}{e^{2}-1}=\frac{1}{e+1}$$
- **2° (da $F_{Y}$)**: $P(1\leq Y\leq 3)=F_{Y}(3)-F_{Y}(1)=1-\frac{e^{2}}{e^{2}-1}(1-e^{-1})=1-\frac{e(e-1)}{e^{2}-1}=1-\frac{e}{e+1}=\frac{1}{e+1}$.
- **3° (via $X$)**: $P(1\leq \log X\leq 3)=P(e\leq X\leq e^{3})\underset{X\leq e^{2}}{=}P(e\leq X\leq e^{2})=\frac{e^{2}}{e^{2}-1}\int_{e}^{e^{2}}x^{-2}\,dx=\frac{e^{2}}{e^{2}-1}\left( \frac{1}{e}-\frac{1}{e^{2}} \right)=\frac{e-1}{e^{2}-1}=\frac{1}{e+1}$.
- **4° (via $F_{X}$)**: $P(e\leq X\leq e^{2})=F_{X}(e^{2})-F_{X}(e)$, che dà gli stessi calcoli del 3° modo, cioè $\frac{1}{e+1}$.

### Esercizio ($Y=e^{X}$: da una densità esponenziale a $U(1,e)$)
Sia $X$ con $f_{X}(x)=\frac{e^{x}}{e-1}1_{(0,1)}(x)$. Trovare la densità di $Y=e^{X}$ e calcolare $P\left( \frac{3}{2}\leq Y\leq 2 \right)$ e $P\left( 0\leq Y\leq \frac{e}{2} \right)$.
$f(x)=e^{x}$ è crescente su $(0,1)$, quindi $Y$ assume valori in $(e^{0},e^{1})=(1,e)$. Per $y\in(1,e)$ (quindi $\log y\in(0,1)$) $$F_{Y}(y)=P(e^{X}\leq y)=P(X\leq \log y)=\int_{0}^{\log y}\frac{e^{x}}{e-1}\,dx=\frac{1}{e-1}[e^{x}]_{0}^{\log y}=\frac{y-1}{e-1}$$Derivando: $$f_{Y}(y)=\frac{1}{e-1}1_{(1,e)}(y)\implies Y\sim U(1,e)$$Allora, ricordando che $Y$ assume valori in $(1,e)$: $$P\left( \tfrac{3}{2}\leq Y\leq 2 \right)=\int_{3/2}^{2}\frac{1}{e-1}\,dy=\frac{2-\frac{3}{2}}{e-1}=\begin{bmatrix}\frac{1}{2(e-1)}\end{bmatrix}$$ $$P\left( 0\leq Y\leq \tfrac{e}{2} \right)=\int_{1}^{e/2}\frac{1}{e-1}\,dy=\frac{\frac{e}{2}-1}{e-1}=\begin{bmatrix}\frac{\frac{e}{2}-1}{e-1}\end{bmatrix}$$(nel secondo si è usato $Y>1$ con probabilità 1, quindi $P(0\leq Y\leq \frac{e}{2})=P(1<Y\leq \frac{e}{2})$).
### Esercizio ($Y=\log(1+X)$ con densità $|x|$)
Sia $X$ con densità continua $f_{X}(x)=|x|\,1_{(-1,1)}(x)$. Trovare la densità di $Y=\log(1+X)$.
$f(x)=\log(1+x)$ è crescente su $(-1,1)$ (composizione di funzioni crescenti), quindi $Y$ assume valori in $(f(-1),f(1))=(\log 0,\log 2)=(-\infty,\log 2)$. Per $y<\log 2$ (quindi $e^{y}-1<1$) $$F_{Y}(y)=P(\log(1+X)\leq y)=P(1+X\leq e^{y})=P(X\leq e^{y}-1)=\int_{-1}^{e^{y}-1}|x|\,dx$$e qui ci sono **due sottocasi** (perché $|x|$ cambia formula in $x=0$):
- **$e^{y}-1\leq 0\iff y\leq 0$**: $\displaystyle\int_{-1}^{e^{y}-1}(-x)\,dx=\left[ -\frac{x^{2}}{2} \right]_{-1}^{e^{y}-1}=\frac{1-(e^{y}-1)^{2}}{2}$;
- **$e^{y}-1>0\iff 0<y<\log 2$**: $\displaystyle\int_{-1}^{0}(-x)\,dx+\int_{0}^{e^{y}-1}x\,dx=\frac{1}{2}+\frac{(e^{y}-1)^{2}}{2}=\frac{1+(e^{y}-1)^{2}}{2}$.

Quindi $$F_{Y}(y)=\begin{cases}
\dfrac{1-(e^{y}-1)^{2}}{2} & y<0 \\[2mm]
\dfrac{1+(e^{y}-1)^{2}}{2} & 0<y<\log 2 \\[1mm]
1 & y\geq \log 2
\end{cases}$$che è una funzione **continua a tratti** e si raccorda per continuità in $y=0$ e $y=\log 2$. Derivando: $$f_{Y}(y)=\begin{cases}
-(e^{y}-1)e^{y} & y<0 \\
(e^{y}-1)e^{y} & 0<y<\log 2 \\
0 & y\geq \log 2
\end{cases}=|e^{y}-1|\,e^{y}\,1_{(-\infty,\log 2)}(y)$$
### Esercizio ($Y=\tan X$: la distribuzione di Cauchy)
Sia $X\sim U\left( -\frac{\pi}{2},\frac{\pi}{2} \right)$. Trovare la densità di $Y=\tan X$.
$f(x)=\tan x$ **non** è monotona globalmente, ma è crescente su $S=\left( -\frac{\pi}{2},\frac{\pi}{2} \right)$, con $P(X\in S)=1$; la sua funzione inversa su tale intervallo è $g(x)=\arctan x$. Allora $Y$ assume valori in $\left( f\left( -\frac{\pi}{2} \right),f\left( \frac{\pi}{2} \right) \right)=(-\infty,\infty)$: in questo caso **non** c'è un sottointervallo fuori dal quale $F_{Y}=0$ oppure $F_{Y}=1$. Per ogni $y\in \mathbb{R}$ (quindi $\arctan y\in\left( -\frac{\pi}{2},\frac{\pi}{2} \right)$) $$F_{Y}(y)=P(\tan X\leq y)=P(X\leq \arctan y)=\int_{-\pi/2}^{\arctan y}\frac{1}{\frac{\pi}{2}-\left( -\frac{\pi}{2} \right)}\,dx=\frac{1}{\pi}\left( \arctan y+\frac{\pi}{2} \right)$$($F_{Y}$ è continua, $F_{Y}(y)\to 0$ per $y\to-\infty$ e $\to 1$ per $y\to+\infty$, ok). Derivando: $$\begin{bmatrix}f_{Y}(y)=\frac{1}{\pi}\cdot\frac{1}{1+y^{2}}\end{bmatrix}$$
> [!quote] Distribuzione di Cauchy
> La distribuzione di $Y$ è detta **distribuzione di Cauchy**: è un esempio di v.a. continua che **non ha media finita** (cosa significhi nel continuo si vedrà più avanti). Dall'espressione analitica si vede che $f_{Y}$ è una funzione **pari** ($f_{Y}(y)=f_{Y}(-y)$).

--- Fine parte sulle trasformazioni monotone (lezione 17) ---

## Trasformazioni non monotone di variabili aleatorie continue
Quando $f$ **non** è monotona nemmeno su un sottoinsieme $S$ con $P(X\in S)=1$ (ad esempio $f(x)=x^{2}$, $|x|$), non ci si può ricondurre all'inversa come nel [[04 - Modelli continui#Trasformazioni monotone di variabili aleatorie continue|caso monotono]]. Si procede così:
1. si individua un insieme $U$ con $P(Y\in U)=1$ (usando come cambia il codominio, tipicamente una "proiezione");
2. per $y\in U$ si calcola direttamente $F_{Y}(y)=P(f(X)\leq y)$ riscrivendo l'evento $\{f(X)\leq y\}$ come un evento su $X$ (spesso un intervallo o un'unione **simmetrica**) e integrando $f_{X}$ su di esso;
3. si deriva per ottenere $f_{Y}$.

### Esercizio ($Y=X^{2}$, densità triangolare)
Sia $X$ con densità continua $f_{X}(x)=(1-|x|)1_{(-1,1)}(x)$. Trovare la densità di $Y=X^{2}$.
$f(x)=x^{2}$ non è monotona (neppure su un $S$ con $P(X\in S)=1$). L'insieme $[-1,1]$ viene proiettato su $[0,1]$, quindi $P(Y\in U)=1$ con $U=[0,1]$. Per $y\in(0,1)$ (quindi $(-\sqrt{y},\sqrt{y})\subset(-1,1)$) $$(\ast)=P(X^{2}\leq y)=P(-\sqrt{y}\leq X\leq \sqrt{y})=\int_{-\sqrt{y}}^{\sqrt{y}}(1-|x|)\,dx$$
- **1° modo**: $\displaystyle\int_{-\sqrt{y}}^{0}(1+x)\,dx+\int_{0}^{\sqrt{y}}(1-x)\,dx=\left[ x+\frac{x^{2}}{2} \right]_{-\sqrt{y}}^{0}+\left[ x-\frac{x^{2}}{2} \right]_{0}^{\sqrt{y}}=\left( \sqrt{y}-\frac{y}{2} \right)+\left( \sqrt{y}-\frac{y}{2} \right)=2\sqrt{y}-y$;
- **2° modo (simmetria)**: $\displaystyle 2\int_{0}^{\sqrt{y}}(1-x)\,dx=2\left[ x-\frac{x^{2}}{2} \right]_{0}^{\sqrt{y}}=2\left( \sqrt{y}-\frac{y}{2} \right)=2\sqrt{y}-y$.

Quindi $F_{Y}(y)=0$ per $y\leq 0$, $=2\sqrt{y}-y$ per $y\in(0,1)$, $=1$ per $y\geq 1$. Derivando ($F_{Y}$ non derivabile in $y=0$ e $y=1$) $$f_{Y}(y)=\left( 2\cdot\frac{1}{2\sqrt{y}}-1 \right)1_{(0,1)}(y)=\begin{bmatrix}\left( \frac{1}{\sqrt{y}}-1 \right)1_{(0,1)}(y)\end{bmatrix}$$Verifica: $\int_{0}^{1}\left( \frac{1}{\sqrt{y}}-1 \right)dy=[2\sqrt{y}-y]_{0}^{1}=2-1=1$.
### Esercizio ($Y=X^{4}$, $X\sim U(-2,2)$)
Sia $X\sim U(-2,2)$. Trovare la funzione di distribuzione di $Y=X^{4}$.
$f(x)=x^{4}$ non è monotona su $(-2,2)$; la proiezione dà $P(0\leq Y\leq 16)=1$ (cioè $U=[0,16]$). Per $y\in(0,16)$ (quindi $(-\sqrt[4]{y},\sqrt[4]{y})\subset(-2,2)$) $$(\ast)=P(X^{4}\leq y)=P(-\sqrt[4]{y}\leq X\leq \sqrt[4]{y})=\int_{-\sqrt[4]{y}}^{\sqrt[4]{y}}\frac{1}{2-(-2)}\,dx=\frac{1}{4}\cdot 2\sqrt[4]{y}=\frac{\sqrt[4]{y}}{2}$$Quindi $$F_{Y}(y)=\begin{cases}0 & y\leq 0 \\ \dfrac{\sqrt[4]{y}}{2} & 0<y<16 \\ 1 & y\geq 16\end{cases}$$(derivando si otterrebbe $f_{Y}(y)=\frac{1}{8}y^{-3/4}1_{(0,16)}(y)$).
### Esercizio ($Y=2-|X|$)
Sia $X$ con densità continua $f_{X}(x)=\frac{e}{e^{2}-1}e^{x}1_{(-1,1)}(x)$. Trovare la densità di $Y=2-|X|$.
$f(x)=2-|x|$ non è monotona su $S=(-1,1)$. Poiché $|x|\in[0,1)$ su $(-1,1)$, si ha $2-|x|\in(1,2]$, quindi $P(Y\in U)=1$ con $U=(1,2)$. Per $y\in(1,2)$ (quindi $2-y\in(0,1)$) $$(\ast)=P(2-|X|\leq y)=P(|X|\geq 2-y)=\int_{-1}^{-(2-y)}\frac{e}{e^{2}-1}e^{x}\,dx+\int_{2-y}^{1}\frac{e}{e^{2}-1}e^{x}\,dx=\frac{e}{e^{2}-1}\left( e^{y-2}-e^{-1}+e-e^{2-y} \right)$$Quindi $F_{Y}(y)=0$ per $y\leq 1$, quell'espressione per $y\in(1,2)$, $=1$ per $y\geq 2$. Derivando $$f_{Y}(y)=\frac{e}{e^{2}-1}\left( e^{y-2}+e^{2-y} \right)1_{(1,2)}(y)$$
### Esercizio ($Y=|X|$: dalla distribuzione di Laplace all'esponenziale)
Sia $X$ con densità continua $f_{X}(x)=\frac{\lambda}{2}e^{-\lambda|x|}$, con $\lambda>0$. Trovare la densità di $Y=|X|$.
> [!info] Distribuzione di Laplace
> La densità $f_{X}(x)=\frac{\lambda}{2}e^{-\lambda|x|}$ (definita su tutto $\mathbb{R}$) è detta **distribuzione di Laplace** o **biesponenziale**.

$f(x)=|x|$ non è monotona su $S=\mathbb{R}$ (qui $P(X\in S)=1$ con $S=\mathbb{R}$). Essendo $|x|\geq 0$ si ha $U=(0,\infty)$. Per $y>0$ $$(\ast)=P(|X|\leq y)=P(-y\leq X\leq y)=\int_{-y}^{y}\frac{\lambda}{2}e^{-\lambda|x|}\,dx\overset{\text{simmetria}}{=}2\int_{0}^{y}\frac{\lambda}{2}e^{-\lambda x}\,dx=[-e^{-\lambda x}]_{0}^{y}=1-e^{-\lambda y}$$Quindi $F_{Y}(y)=0$ per $y\leq 0$, $=1-e^{-\lambda y}$ per $y>0$. Derivando $$f_{Y}(y)=\lambda e^{-\lambda y}1_{(0,\infty)}(y)\implies Y\sim Exp(\lambda)$$(prendendo il valore assoluto di una Laplace si ottiene un'esponenziale).

--- Fine lezione 17 ---

## Massimi e minimi di variabili aleatorie continue
Indipendenza per v.a. continue e distribuzione di $Z=\max\{X_{1},X_{2}\}$ e $W=\min\{X_{1},X_{2}\}$, con l'applicazione ai sistemi in serie e in parallelo.
### Indipendenza (caso continuo)
$X_{1},\dots,X_{m}$ si dicono **indipendenti** se $$\forall A_{1},\dots,A_{m}\subseteq \mathbb{R}\qquad P\big(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\}\big)=P(X_{1}\in A_{1})\cdots P(X_{m}\in A_{m})$$Basta richiederlo per $A_{1},\dots,A_{m}$ **intervalli** limitati; da qui segue anche per intervalli illimitati. In termini di densità congiunta vale (come nel discreto) che l'indipendenza equivale a "densità congiunta $=$ prodotto delle densità marginali" (la trattazione delle congiunte continue, con integrali multipli, va oltre gli scopi del corso).
> [!warning] Differenza con il caso discreto
> Se $X_{1},\dots,X_{m}$ sono **discrete**, allora $\underline{X}=(X_{1},\dots,X_{m})$ è discreta $m$-dimensionale. Se invece sono **continue**, in generale ciò **non** implica che $\underline{X}$ sia continua $m$-dimensionale.

### Distribuzione di $\max$ e $\min$
Siano $X_{1},X_{2}$ **indipendenti**, $Z=\max\{X_{1},X_{2}\}$, $W=\min\{X_{1},X_{2}\}$. Adattando il [[02 - Modelli discreti|caso discreto]]: $$\{Z\leq z\}=\{X_{1}\leq z\}\cap\{X_{2}\leq z\}\ \overset{\text{indip.}}{\implies}\ \begin{bmatrix}F_{Z}(z)=F_{X_{1}}(z)\,F_{X_{2}}(z)\end{bmatrix}$$ $$\{W>w\}=\{X_{1}>w\}\cap\{X_{2}>w\}\ \overset{\text{indip.}}{\implies}\ \begin{bmatrix}F_{W}(w)=F_{X_{1}}(w)+F_{X_{2}}(w)-F_{X_{1}}(w)F_{X_{2}}(w)\end{bmatrix}$$(la formula per $W$ segue da $1-F_{W}=(1-F_{X_{1}})(1-F_{X_{2}})$). Derivando: $$f_{Z}(z)=F_{X_{2}}(z)f_{X_{1}}(z)+F_{X_{1}}(z)f_{X_{2}}(z)\qquad f_{W}(w)=(1-F_{X_{2}}(w))f_{X_{1}}(w)+(1-F_{X_{1}}(w))f_{X_{2}}(w)$$
> [!info] Sistemi in serie e in parallelo
> Se $X_{1},X_{2}$ sono i **tempi di funzionamento** di due dispositivi indipendenti: $Z=\max$ è il tempo del sistema in **parallelo** (funziona finché almeno uno funziona); $W=\min$ è il tempo del sistema in **serie** (funziona finché entrambi funzionano).

### Esercizio (massimo e minimo di due esponenziali)
$X_{1}\sim Exp(\lambda_{1})$, $X_{2}\sim Exp(\lambda_{2})$ indipendenti. Il minimo è ancora esponenziale: $$f_{W}(w)=(\lambda_{1}+\lambda_{2})e^{-(\lambda_{1}+\lambda_{2})w}1_{(0,\infty)}(w)\implies \begin{bmatrix}W\sim Exp(\lambda_{1}+\lambda_{2})\end{bmatrix}$$Il massimo **non** è esponenziale: $$f_{Z}(z)=\left[ \lambda_{1}e^{-\lambda_{1}z}+\lambda_{2}e^{-\lambda_{2}z}-(\lambda_{1}+\lambda_{2})e^{-(\lambda_{1}+\lambda_{2})z} \right]1_{(0,\infty)}(z)$$

--- Fine lezione 18 (indipendenza, massimi e minimi continui) ---

## Distribuzione normale
Distribuzione Normale (o Gaussiana): caso standard $N(0,1)$ e caso generale $N(\mu,\sigma^{2})$, standardizzazione e la funzione $\Phi$ (materia di **Es6**).
### Normale standard e Normale generale
Una v.a. $X$ ha **distribuzione Normale standard** ($X\sim N(0,1)$) se ha densità $$f_{X}(x)=\frac{1}{\sqrt{2\pi}}e^{-\frac{x^{2}}{2}}$$Data $X\sim N(0,1)$, con $\sigma>0$ e $\mu\in \mathbb{R}$, la v.a. $Y=\sigma X+\mu$ ha **distribuzione Normale di parametri $\mu,\sigma^{2}$** ($Y\sim N(\mu,\sigma^{2})$). Per la [[04 - Modelli continui#Il caso di funzione affine non costante|formula affine]] (con $a=\sigma$, $b=\mu$): $$f_{Y}(y)=\frac{1}{\sigma}f_{X}\left( \frac{y-\mu}{\sigma} \right)=\begin{bmatrix}\frac{1}{\sqrt{2\pi\sigma^{2}}}e^{-\frac{(y-\mu)^{2}}{2\sigma^{2}}}\end{bmatrix}$$($\frac{1}{\sqrt{2\pi\sigma^{2}}}$ è la costante di normalizzazione; per $\mu=0,\sigma=1$ si ritrova il caso standard).
> [!info] Grafico "a campana"
> $f_{Y}$ è **simmetrica rispetto a $y=\mu$**, con area totale 1; al diminuire di $\sigma$ la curva si concentra attorno a $\mu$. Si vedrà che $\mu$ e $\sigma^{2}$ sono **media e varianza** di $Y$ (vedi [[04 - Modelli continui#Media e varianza delle distribuzioni notevoli continue|media e varianza delle notevoli]]).

### Standardizzazione
> [!quote] Standardizzazione
> Sia $Y\sim N(\mu,\sigma^{2})$ e $Y^{*}=\dfrac{Y-\mu}{\sigma}$. Allora $Y^{*}\sim N(0,1)$.

Si applica la formula affine con $a=\frac{1}{\sigma}$, $b=-\frac{\mu}{\sigma}$: si verifica $f_{Y^{*}}(x)=\frac{1}{\sqrt{2\pi}}e^{-x^{2}/2}$. La standardizzazione riconduce **ogni** Normale al caso standard.
### La funzione $\Phi$
Si indica con $\Phi$ la funzione di distribuzione di $X\sim N(0,1)$: $$\Phi(t)=P(X\leq t)=\int_{-\infty}^{t}\frac{1}{\sqrt{2\pi}}e^{-\frac{x^{2}}{2}}\,dx$$Per $Y\sim N(\mu,\sigma^{2})$, standardizzando: $$F_{Y}(t)=P(Y\leq t)=P\left( \frac{Y-\mu}{\sigma}\leq \frac{t-\mu}{\sigma} \right)=\begin{bmatrix}\Phi\left( \frac{t-\mu}{\sigma} \right)\end{bmatrix}$$
> [!info] Proprietà di $\Phi$
> $\Phi$ è crescente, continua e derivabile con $\Phi'(t)=\frac{1}{\sqrt{2\pi}}e^{-t^{2}/2}$, $\lim_{t\to-\infty}\Phi=0$, $\lim_{t\to+\infty}\Phi=1$. **Non** ha primitiva elementare, quindi non c'è formula chiusa per $\Phi(t)$: i valori si leggono da tavole. L'unico valore esatto notevole è $\Phi(0)=\frac{1}{2}$.

> [!quote] Simmetria di $\Phi$
> $$\Phi(t)=1-\Phi(-t)\qquad\forall t$$ (discende dalla simmetria della densità rispetto a $0$: le due code hanno aree uguali). Permette di ricondurre ogni valore a un **argomento positivo**.

> [!info] Quantili notevoli e nota d'esame
> Dalla tavola: $\Phi(1{,}96)=0{,}975$, quindi $q_{0{,}975}=1{,}96$; inoltre $q_{0{,}5}=0$ (mediana). **Per l'esame:** da qualche anno non si richiede l'uso delle tavole, solo di **esprimere il risultato tramite $\Phi$**, spesso con **argomento positivo** (es. $\Phi(-1)$ si scrive $1-\Phi(1)$).

### Calcolo di probabilità con $\Phi$
> [!example] $X\sim N(0,1)$: $P(|X|>2)$
> $$P(|X|>2)=(1-\Phi(2))+\underset{=1-\Phi(2)}{\underbrace{\Phi(-2)}}=2(1-\Phi(2))$$

> [!example] $Y\sim N(\mu=3,\sigma^{2}=25)$: $P(1\leq Y\leq 4)$
> Standardizzando ($\sigma=5$): $$P(1\leq Y\leq 4)=\Phi\left( \tfrac{1}{5} \right)-\Phi\left( -\tfrac{2}{5} \right)=\Phi\left( \tfrac{1}{5} \right)+\Phi\left( \tfrac{2}{5} \right)-1$$

> [!example] $X\sim N(\mu=2,\sigma^{2}=4)$: $P(X\geq 3)$ e ricerca di $z$ con $P(X\leq z)=P(X\geq 3)$
> $P(X\geq 3)=P\left( X^{*}\geq \tfrac{3-2}{2} \right)=1-\Phi\left( \tfrac{1}{2} \right)$. Cercando $z$: $P(X\leq z)=\Phi\left( \tfrac{z-2}{2} \right)$; imponendo $\Phi\left( \tfrac{z-2}{2} \right)=1-\Phi\left( \tfrac{1}{2} \right)=\Phi\left( -\tfrac{1}{2} \right)$ e usando l'iniettività di $\Phi$: $\frac{z-2}{2}=-\frac{1}{2}$, cioè $\begin{bmatrix}z=1\end{bmatrix}$.

### Esercizi ricorrenti: condizionamento e ricerca di un valore
> [!example] Probabilità condizionata con la Normale
> Ci si riduce a un **rapporto** e si standardizzano numeratore e denominatore; a volte il valore esce **esatto**. Es. $X\sim N(-2,16)$: $$P(-2\leq X\leq 0\mid -4\leq X\leq 0)=\frac{\Phi(\frac{1}{2})-\Phi(0)}{\Phi(\frac{1}{2})-\Phi(-\frac{1}{2})}=\frac{\Phi(\frac{1}{2})-\frac{1}{2}}{2\Phi(\frac{1}{2})-1}=\frac{1}{2}$$

> [!example] Ricerca di $z$ (iniettività di $\Phi$)
> $X\sim N(9,4)$, trovare $z<9$ con $P(9<X<10\mid z<X<10)=\frac{1}{2}$: si arriva a $\Phi(-\frac{1}{2})=\Phi(\frac{z-9}{2})$, da cui $\frac{z-9}{2}=-\frac{1}{2}$ e $\begin{bmatrix}z=8\end{bmatrix}$.

### Esercizio ($Y=|X|$ con $X\sim N(0,\sigma^{2})$: la "half-normal")
$\{|X|\leq y\}=\{-y\leq X\leq y\}$; $Y$ assume valori in $(0,\infty)$. Per $y>0$, standardizzando: $$F_{Y}(y)=\Phi\left( \tfrac{y}{\sigma} \right)-\Phi\left( -\tfrac{y}{\sigma} \right)=2\Phi\left( \tfrac{y}{\sigma} \right)-1$$Derivando: $$f_{Y}(y)=\begin{bmatrix}\frac{2}{\sqrt{2\pi\sigma^{2}}}e^{-\frac{y^{2}}{2\sigma^{2}}}1_{(0,\infty)}(y)\end{bmatrix}$$cioè la densità di $N(0,\sigma^{2})$ **raddoppiata e troncata su $(0,\infty)$** (distribuzione *half-normal*); la sua media è $\mathbb{E}[|X|]=\sigma\sqrt{\frac{2}{\pi}}$ (vedi [[04 - Modelli continui#Speranza matematica per variabili aleatorie continue|speranza continua]]).

--- Fine lezione 18-19 (distribuzione Normale) ---

## Distribuzione Gamma
Distribuzione $Gamma(\alpha,\beta)$ e funzione $\Gamma$, con l'esponenziale come caso particolare, la somma di Gamma indipendenti e il processo di Poisson.
### Definizione
Una v.a. $X$ ha **distribuzione Gamma** di parametri $\alpha,\beta>0$ ($X\sim Gamma(\alpha,\beta)$) se ha densità $$f_{X}(x)=\frac{\beta^{\alpha}}{\Gamma(\alpha)}x^{\alpha-1}e^{-\beta x}1_{(0,\infty)}(x)\qquad\text{dove}\qquad \Gamma(y)=\int_{0}^{\infty}z^{y-1}e^{-z}\,dz$$è la **funzione Gamma**. Col cambio $z=\beta x$ si verifica che $\frac{\beta^{\alpha}}{\Gamma(\alpha)}$ è la costante di normalizzazione ($\int_{0}^{\infty}f_{X}=1$).
> [!info] L'esponenziale è una Gamma con $\alpha=1$
> Per $\alpha=1$ ($\Gamma(1)=1$): $f_{X}(x)=\beta e^{-\beta x}1_{(0,\infty)}(x)$, cioè $X\sim Exp(\beta)$.

### La funzione $\Gamma$
Vale la **relazione fondamentale** $\Gamma(y)=(y-1)\Gamma(y-1)$ per $y>1$ (integrando per parti). Da $\Gamma(1)=1$ seguono i valori: **$y=n$ intero** $\Rightarrow\Gamma(n)=(n-1)!$; **$\Gamma\left( \frac{1}{2} \right)=\sqrt{\pi}$** (col cambio $z=\frac{s^{2}}{2}$ ci si riconduce all'integrale della densità $N(0,1)$); i semi-interi si iterano fino a $\Gamma\left( \frac{1}{2} \right)$. In generale non c'è valore esplicito; per $\alpha=n$ intero, integrando per parti: $$F_{X}(t)=1-e^{-\beta t}\sum_{k=0}^{n-1}\frac{(\beta t)^{k}}{k!}\qquad(t>0)$$
### Somma di Gamma indipendenti e scaling
> [!quote] Somma di Gamma con lo stesso $\beta$
> $X_{1},\dots,X_{m}$ indipendenti con $X_{i}\sim Gamma(\alpha_{i},\beta)$ $\implies X_{1}+\dots+X_{m}\sim Gamma(\alpha_{1}+\dots+\alpha_{m},\beta)$. **Corollario:** se sono tutte $\sim Exp(\beta)$ (cioè $\alpha_{i}=1$), allora $X_{1}+\dots+X_{m}\sim Gamma(m,\beta)$.

Inoltre (scaling) se $X\sim Gamma(\alpha,\beta)$ e $r>0$, allora $rX\sim Gamma\left( \alpha,\frac{\beta}{r} \right)$ (formula affine con $a=r$).
### Esercizio ($X^{2}$ di una Normale centrata è una Gamma)
Sia $X\sim N(0,\sigma^{2})$ e $Y=X^{2}$. Con il metodo della controimmagine e standardizzando $\frac{X}{\sigma}\sim N(0,1)$: per $y>0$, $$F_{Y}(y)=P(-\sqrt{y}\leq X\leq \sqrt{y})=2\Phi\left( \tfrac{\sqrt{y}}{\sigma} \right)-1$$Derivando: $f_{Y}(y)=\frac{1}{\sqrt{2\pi}\,\sigma}y^{\frac{1}{2}-1}e^{-\frac{y}{2\sigma^{2}}}1_{(0,\infty)}(y)$, che confrontata con la densità $Gamma$ dà $$\begin{bmatrix}Y=X^{2}\sim Gamma\left( \tfrac{1}{2},\tfrac{1}{2\sigma^{2}} \right)\end{bmatrix}$$(la costante coincide automaticamente, usando $\Gamma\left( \frac{1}{2} \right)=\sqrt{\pi}$).
### Il processo di Poisson
Sia $\{S_{m}:m\geq 1\}$ una successione di v.a. indipendenti tutte $\sim Exp(\lambda)$ (**tempi di inter-arrivo**), e $T_{m}=S_{1}+\dots+S_{m}$ (**istante dell'$m$-simo evento**). Il **processo di conteggio** è $N(t)=\#\{\text{eventi entro il tempo }t\}=\sum_{m\geq 1}1_{\{T_{m}\leq t\}}$. Si parla di **processo di Poisson di intensità $\lambda$**.
> [!quote] Le due leggi del processo di Poisson
> Per il corollario sulla somma di esponenziali, $T_{m}\sim Gamma(m,\lambda)$. Inoltre, dall'uguaglianza $\{T_{m}\leq t\}=\{N(t)\geq m\}$ si ricava $$N(t)\sim POISSON(\lambda t)\qquad P(N(t)=m)=\frac{(\lambda t)^{m}}{m!}e^{-\lambda t}$$ Cioè gli **istanti** $T_{m}$ sono Gamma (continue), il **conteggio** $N(t)$ è di Poisson (discreto).

> [!example] Processo di Poisson di intensità $\lambda=3$
> $P(N_{2}=1)=6e^{-6}$ ($N_{2}\sim POISSON(6)$); $P(N_{4}\geq 1)=1-e^{-12}$; $P(T_{3}\geq 10)=481e^{-30}$ ($T_{3}\sim Gamma(3,3)$, ovvero $P(N(10)\leq 2)$).

--- Fine lezione 19 (Gamma e processo di Poisson) ---

## Speranza matematica per variabili aleatorie continue
Speranza, momenti e varianza nel continuo, media e varianza delle distribuzioni notevoli e la formula per $\mathbb{E}[g(X)]$ (materia di **Es5**).
### Definizione
Una v.a. $X$ con densità continua $f_{X}$ ha **speranza matematica finita** se $\int_{-\infty}^{+\infty}|x|f_{X}(x)\,dx<\infty\ (*)$. In tal caso $$\begin{bmatrix}\mathbb{E}[X]=\int_{-\infty}^{+\infty}x\,f_{X}(x)\,dx\end{bmatrix}$$(sinonimi: media, valore atteso). Analogia col discreto: integrali al posto delle somme, $x\,f_{X}(x)$ al posto di $x_{k}P_{X}(x_{k})$. La $(*)$ è verificata se $f_{X}$ è positiva solo su un insieme **limitato**.
### Momenti e varianza
Come nel discreto, quando le grandezze esistono finite: **momento $k$-simo** $\mathbb{E}[X^{k}]=\int x^{k}f_{X}$, **momento centrato** $\mathbb{E}[(X-\mathbb{E}[X])^{k}]=\int (x-\mathbb{E}[X])^{k}f_{X}$, e la **varianza** è il caso $k=2$. Valgono linearità di $\mathbb{E}[\cdot]$ e la **formula alternativa** $$\begin{bmatrix}\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]\end{bmatrix}$$
> [!info] Covarianza e indipendenza nel continuo
> La covarianza si può considerare anche per v.a. continue (richiederebbe le congiunte, oltre gli scopi del corso). Vale però: $X_{1},\dots,X_{m}$ indipendenti con media finita $\Rightarrow\mathbb{E}[X_{1}\cdots X_{m}]=\mathbb{E}[X_{1}]\cdots\mathbb{E}[X_{m}]$, quindi $\text{Cov}(X_{1},X_{2})=0$. Il **viceversa non vale** (controesempi anche nel continuo).

> [!info] Densità simmetrica
> Se $X$ ha speranza finita e densità simmetrica rispetto a $x_{0}$ ($f(x_{0}-x)=f(x_{0}+x)$), allora $\mathbb{E}[X]=x_{0}$ (uniforme $\to\frac{a+b}{2}$; Normale $\to\mu$).

### Media e varianza delle distribuzioni notevoli continue
| Distribuzione | $\mathbb{E}[X]$ | $\text{Var}[X]$ |
|---|---|---|
| $U(a,b)$ | $\frac{a+b}{2}$ | $\frac{(b-a)^{2}}{12}$ |
| $Exp(\lambda)$ | $\frac{1}{\lambda}$ | $\frac{1}{\lambda^{2}}$ |
| $N(0,1)$ | $0$ | $1$ |
| $N(\mu,\sigma^{2})$ | $\mu$ | $\sigma^{2}$ |
| $Gamma(\alpha,\beta)$ | $\frac{\alpha}{\beta}$ | $\frac{\alpha}{\beta^{2}}$ |
- **Uniforme:** $\mathbb{E}[X]=\frac{1}{b-a}\int_{a}^{b}x\,dx=\frac{b+a}{2}$; da $\mathbb{E}[X^{2}]=\frac{b^{2}+ab+a^{2}}{3}$ segue $\text{Var}[X]=\frac{(b-a)^{2}}{12}$ (dipende solo dalla lunghezza).
- **Esponenziale:** per parti $\mathbb{E}[X]=\frac{1}{\lambda}$, $\mathbb{E}[X^{2}]=\frac{2}{\lambda^{2}}$, quindi $\text{Var}[X]=\frac{1}{\lambda^{2}}$.
- **Normale:** $X\sim N(0,1)$ ha densità **pari** $\Rightarrow\mathbb{E}[X]=0$; con $z=\frac{x^{2}}{2}$, $\text{Var}[X]=\mathbb{E}[X^{2}]=\frac{2}{\sqrt{\pi}}\Gamma\left( \frac{3}{2} \right)=\frac{2}{\sqrt{\pi}}\cdot\frac{1}{2}\sqrt{\pi}=1$. Per $Y=\sigma X+\mu\sim N(\mu,\sigma^{2})$: $\mathbb{E}[Y]=\sigma\cdot 0+\mu=\mu$, $\text{Var}[Y]=\sigma^{2}\cdot 1=\sigma^{2}$ (i parametri sono media e varianza).
- **Gamma:** riconducendosi ogni volta all'integrale di una densità Gamma, $\mathbb{E}[X]=\frac{\beta^{\alpha}}{\Gamma(\alpha)}\cdot\frac{\Gamma(\alpha+1)}{\beta^{\alpha+1}}=\frac{\alpha}{\beta}$ e $\mathbb{E}[X^{2}]=\frac{(\alpha+1)\alpha}{\beta^{2}}$, quindi $\text{Var}[X]=\frac{\alpha}{\beta^{2}}$ (per $\alpha=1$ si ritrova $Exp(\beta)$).

### Speranza di una trasformazione $\mathbb{E}[g(X)]$
> [!quote] Speranza di una trasformazione (senza dimostrazione)
> Se $X$ è continua e $Y=g(X)$ ha speranza finita, allora $\mathbb{E}[Y]=\int_{-\infty}^{+\infty}g(x)f_{X}(x)\,dx$ (si estende ai casi $\pm\infty$). Vantaggio: si calcola $\mathbb{E}[Y]$ **senza conoscere $f_{Y}$**.

> [!example] Esempi
> - $Y=e^{X}$ con $f_{X}=\frac{e^{x}}{e-1}1_{(0,1)}$: $\mathbb{E}[Y]=\frac{1}{e-1}\int_{0}^{1}e^{2x}dx=\frac{e+1}{2}$ (coerente con $Y\sim U(1,e)$).
> - $Y=X^{\beta}$ con $f_{X}=\alpha x^{\alpha-1}1_{(0,1)}$: $\mathbb{E}[Y]=\frac{\alpha}{\alpha+\beta}$.
> - $Y=e^{X}$ con $X\sim Exp(1)$: $\mathbb{E}[Y]=\int_{0}^{\infty}1\,dx=+\infty$ (caso con media infinita).
> - $\mathbb{E}[|X|]$ con $X\sim N(0,\sigma^{2})$: $\frac{2}{\sqrt{2\pi\sigma^{2}}}\int_{0}^{\infty}x\,e^{-x^{2}/2\sigma^{2}}dx=\sigma\sqrt{\frac{2}{\pi}}$ (media della *half-normal*, vedi [[04 - Modelli continui#Distribuzione normale|Normale]]). Trucco analogo: se $Z=\sqrt{X}$ allora $\mathbb{E}[e^{-Z^{2}}]=\mathbb{E}[e^{-X}]$.

--- Fine lezione 20 (speranza e momenti nel continuo) ---

## Combinazioni lineari di normali indipendenti
Ogni combinazione lineare di v.a. Normali **indipendenti** è ancora Normale (ricorrente in **Es6**).
### Premessa
In generale la somma di due Normali **non** è Normale; se però sono **indipendenti**, ogni combinazione lineare è Normale. Per contemplare coefficienti nulli si vede una costante come Normale degenere: $P(X=c)=1\Rightarrow X\sim N(c,0)$.
### La proposizione
> [!quote] Combinazione lineare di Normali indipendenti (dim. parziale)
> $a_{1},\dots,a_{n}\in \mathbb{R}$, $X_{1},\dots,X_{n}$ **indipendenti** con $X_{i}\sim N(\mu_{i},\sigma_{i}^{2})$. Allora $$\begin{bmatrix}a_{1}X_{1}+\dots+a_{n}X_{n}\sim N\big(a_{1}\mu_{1}+\dots+a_{n}\mu_{n},\ a_{1}^{2}\sigma_{1}^{2}+\dots+a_{n}^{2}\sigma_{n}^{2}\big)\end{bmatrix}$$

Non si dimostra la normalità; media e varianza seguono da **linearità** di $\mathbb{E}[\cdot]$ e, per l'indipendenza, dalla somma delle varianze con $\text{Var}[a_{i}X_{i}]=a_{i}^{2}\sigma_{i}^{2}$.
### Esercizi tipici
> [!example] $P(2X_{1}-3X_{2}\geq 0)$ con $X_{1}\sim N(1,1)$, $X_{2}\sim N(5,2)$ indipendenti
> $2X_{1}-3X_{2}\sim N(2\cdot 1-3\cdot 5,\ 2^{2}\cdot 1+3^{2}\cdot 2)=N(-13,22)$. Standardizzando: $$P(2X_{1}-3X_{2}\geq 0)=1-\Phi\left( \frac{13}{\sqrt{22}} \right)$$

> [!example] $X_{1},X_{2}\sim N(0,1)$ indipendenti
> $X_{1}-X_{2}\sim N(0,2)$. Allora $P(X_{1}-X_{2}\geq 0)=\frac{1}{2}$ (esatto) e $P(X_{1}-X_{2}>\frac{1}{2})=1-\Phi\left( \frac{1}{2\sqrt{2}} \right)$. In generale, per $Z\sim N(\mu,\sigma^{2})$, $P(Z>\mu)=P(Z<\mu)=\frac{1}{2}$.

--- Fine lezione 21 (combinazioni lineari di Normali) ---
