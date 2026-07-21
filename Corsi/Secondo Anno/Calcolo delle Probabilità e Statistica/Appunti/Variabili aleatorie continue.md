# Variabili aleatorie continue
Definizione di v.a. continua tramite la densità, relazione $F_{X}'=f_{X}$ quasi ovunque e confronto sistematico con il caso discreto.
## Definizione
Una v.a. $X$ è una **v.a. continua** se esiste una funzione $f_{X}$ tale che $$\begin{bmatrix}
F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx\qquad\forall\ t\in \mathbb{R}
\end{bmatrix}\qquad(\square)$$dove $F_{X}$ è la [[Variabili aleatorie discrete#Funzione di distribuzione|funzione di distribuzione]]. In tal caso la funzione $f_{X}$ (lettera minuscola) è detta **densità continua**.
## Osservazioni su $f_{X}$ e $F_{X}$
- In generale $f_{X}$ **non è unica**: possiamo avere un'altra $g_{X}$ che realizza la condizione $(\square)$ in maniera un po' diversa da $f_{X}$ (si veda [[#Non unicità della densità (esempio)|l'esempio più avanti]]).
- In generale $f_{X}$ **non è continua** (vedremo esempi specifici). Però, se vale $(\square)$, allora $F_{X}$ è continua.
- È possibile costruire casi per cui $F_{X}$ è continua ma la condizione $(\square)$ non è verificata; la costruzione va oltre gli scopi del corso.

## $F_{X}'=f_{X}$ quasi ovunque
In generale $F_{X}$ è derivabile in "quasi tutti i punti", perché $F_{X}$ è una funzione **non decrescente**. L'insieme dei punti dove $F_{X}$ non è derivabile è un insieme "trascurabile" (spesso negli esercizi è un insieme finito o numerabile). Nei punti $t$ dove $F_{X}$ è derivabile si ha $F_{X}'(t)=f_{X}(t)$. In conclusione $$F_{X}'(t)=f_{X}(t)\quad\text{in "quasi tutti i punti }t\in \mathbb{R}\text{"}$$(le affermazioni tra virgolette si potrebbero precisare con strumenti matematici oltre gli scopi del corso).
## Analogie e differenze tra densità discrete e continue
Il punto di partenza comune è $F_{X}(t)=P(X\leq t)$, che si scrive $$F_{X}(t)=P(X\leq t)=\underset{x_{k}\leq t}{\sum_{x_{k}\in \delta_{X}}}P_{X}(x_{k})\quad(\text{caso discreto})\qquad\qquad F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx\quad(\text{caso continuo})$$
### Analogie
$$\begin{array}{ll}
\text{caso discreto} & \text{caso continuo} \\
\hline
P_{X}(x)\geq 0 & f_{X}(x)\geq 0 \\
\displaystyle\sum_{x_{k}\in \delta_{X}}P_{X}(x_{k})=1 & \displaystyle\int_{-\infty}^{\infty}f_{X}(x)\,dx=1 \\
\displaystyle P(X\in A)=\underset{x_{k}\in A}{\sum_{x_{k}\in \delta_{X}}}P_{X}(x_{k})\ (\forall A\subseteq \mathbb{R}) & \displaystyle P(X\in A)=\int_{A}f_{X}(x)\,dx\ (\forall A\subseteq \mathbb{R}\text{ per cui ha senso l'integrale})
\end{array}$$
### Differenze
$$\begin{array}{ll}
\text{caso discreto} & \text{caso continuo} \\
\hline
P(X=x)=0\ \forall x\in \mathbb{R}\ \text{è \textbf{falso}} & P(X=x)=0\ \forall x\in \mathbb{R}\ \text{è \textbf{vero}} \\
\text{(non vero per }x\in \delta_{X}\text{)} & \\
P(a\leq X\leq b),\ P(a\leq X<b),\dots\text{ possono differire} & P(a\leq X\leq b)=P(a\leq X<b)=P(a<X\leq b)=P(a<X<b) \\
P_{X}\text{ definita in maniera univoca} & f_{X}\ \textbf{non}\text{ definita in maniera univoca}
\end{array}$$La differenza sulle probabilità degli intervalli segue dal fatto che nel continuo $P(X=a)=P(X=b)=0$: aggiungere o togliere gli estremi non cambia la probabilità.
## Non unicità della densità (esempio)
In generale, se $f_{X}$ è una densità continua, lo è anche una qualsiasi altra funzione $g_{X}$ per cui $\{x\in \mathbb{R}:f_{X}(x)\neq g_{X}(x)\}$ è finito o numerabile. Consideriamo $$f_{X}(x)=1_{[0,1]}(x)=\begin{cases}1 & x\in[0,1] \\ 0 & \text{altrimenti}\end{cases}\qquad g_{X}(x)=1_{(0,1)}(x)=\begin{cases}1 & x\in(0,1) \\ 0 & \text{altrimenti}\end{cases}$$Quindi $\{x:g_{X}(x)\neq f_{X}(x)\}=\{0,1\}$. In corrispondenza si vede che $$F_{X}(t)=\int_{-\infty}^{t}f_{X}(x)\,dx=\int_{-\infty}^{t}g_{X}(x)\,dx=\begin{cases}0 & t<0 \\ t & 0\leq t\leq 1 \\ 1 & t>1\end{cases}$$In entrambi i casi si ottiene la stessa $F_{X}$, perché contano le **aree** disegnate e non i valori di $f_{X}$ e $g_{X}$ nei punti $x=0$ e $x=1$. In effetti $F_{X}$ è una funzione di distribuzione: è non decrescente, $F_{X}(x)\to 1$ per $x\to+\infty$, $F_{X}(x)\to 0$ per $x\to-\infty$, ed è continua (quindi anche continua a destra).
> [!info] Abuso di linguaggio
> Si parla di "densità continua $f_{X}(x)$ di una v.a. $X$ continua" per abuso di linguaggio: in realtà ci sono **infinite versioni** della densità continua (che differiscono in insiemi trascurabili di punti) e definiscono la stessa $F_{X}$. In questo esempio $f_{X}$ non è continua (discontinuità in $x=0$ e $x=1$); lo stesso vale per $g_{X}$.

## Verso le distribuzioni notevoli continue
Introdurremo i primi esempi di distribuzioni notevoli continue: la [[Distribuzione uniforme continua|distribuzione uniforme]] e la [[Distribuzione esponenziale|distribuzione esponenziale]]; più avanti la distribuzione Gamma e la distribuzione Normale (o Gaussiana).
> [!info] Differenza con il caso discreto
> Le distribuzioni notevoli continue vengono definite **a partire dalle espressioni di $F_{X}$ e $f_{X}$**; questo è un po' diverso dal caso discreto, dove si traeva ispirazione da qualche "caso pratico".

--- Fine parte sulle variabili aleatorie continue (lezione 15, pp. 1-8) ---

---
Nota successiva: [[Distribuzione uniforme continua]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
