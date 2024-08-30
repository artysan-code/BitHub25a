
In questo capitolo tratteremo essenzialmente Variabili Aleatorie Discrete (spesso definite su spazi di probabilità ($\ohm,\mathcal{A},P$) con $r$ discreto, cioè finito o numerabile)

In ogni caso nella parte iniziale di questa lezione diremo alcune cose sulle variabili aleatorie in generale. Spesso useremo l'abbreviazione "v.a.".

In generale una v.a. (definita su uno spazio di probabilità ($\ohm,\mathcal{A},P$)) è una funzione del tipo $$X:\ohm\to\mathcal{X}$$dove $\mathcal{X}$ è un qualche insieme, e con certe proprietà.

In questo corso tratteremo il caso in cui $X=\mathbb{R}$ (o un suo sottoinsieme); in qualche caso considereremo il caso $\mathcal{X}=\mathbb{R}^{n}$ per qualche $n\geq 2$ (però solo per v.a. discrete).

Il concetto di v.a. è utile perché spesso gli eventi di interesse negli esercizi sono esprimibili tramite v.a.. Consideriamo un esempio.

#### Esempio
Si lanciano due dadi equi e consideriamo l'evento "la somma dei due numeri ottenuti è uguale a 5". Allora è utile fare riferimento alla seguente scelta dell'insieme $\ohm$: $$\ohm=\{1,\dots,6\}\times\{1,\dots,6\}=\{w=(w_{1},w_{2}):w_{1},w_{2}\in\{1,\dots,6\}\}$$
Essendo $\ohm$ un insieme finito, non ci sono problemi nello scegliere $\mathcal{A}=P(\ohm)$

Inoltre è opportuno considerare la seguente funzione $X:\ohm\to\mathbb{R}$ (che è una v.a.) definita come segue: $$\begin{array}{}
X(w)=X(w_{1},w_{2})=w_{1}+w_{2} & (\forall\ w=(w_{1},w_{2})\in\ohm)
\end{array}$$
Allora l'evento di interesse è $$\{w=(w_{1},w_{2})\in\ohm:X(w)=5\}$$
### Definizione
Sia $(\ohm,\mathcal{A},P)$ uno spazio di probabilità. Inoltre sia $X:\ohm\to \mathbb{R}$ una funzione.
Allora la funzione $X$ è una v.a. (reale) se vale la seguente condizione $$\forall\ t\in\mathbb{R}\quad\quad\{w\in\ohm:X(w)\leq t\}\in\mathcal{A}$$
In altri termini si richiede che le controimmagini delle semirette del tipo $(-\infty,t]$ (al variare di $t\in\mathbb{R}$), che sono sottoinsiemi di $\ohm$, siano elementi della $\delta$-algebra $\mathcal{A}$.

Questo consente di dire che, per queste controimmagini, è possibile definire la probabilità.
Quindi possiamo dire che, per ogni $t\in\mathbb{R}$, $P(\{w\in\ohm:X(w)\leq t\})$ è un numero ben definito.

Quindi si richiede che, se $B=(-\infty,t]$ per una qualsiasi scelta di $t\in\mathbb{R}$, $$\{w\in\ohm:X(w)\in B\}\in\mathcal{A}\quad\quad\quad(*)$$
A partire da questa richiesta, condizione di $(*)$ vale anche per le altre scelte di $B$ "naturali" da considerare: $$\begin{array}{l|l}
B=[t,+\infty) &  \\
B=(t,+\infty) & \text{per ogni }t\in\mathbb{R} \\
B=(-\infty,t)
\end{array}$$$B=[s,t], B=(s,t), B=[s,t), B=(s,t]$ per ogni $s,t\in\mathbb{R}$ con $s<t$
$B=\{t\}$ per ogni $t\in\mathbb{R}$

$B$ unione finita o numerabile di insiemi dei tipi indicati sopra. 
(es. $B=(0,1)\cup\{2\}\cup[4,5)\cup[6,+\infty)$)

#### Notazioni che useremo
$\{w\in\ohm:X(w)\in B\}\longrightarrow$ useremo la notazione $\{X\in B\}$
$P(\{w\in\ohm:X(w)\in B\})\longrightarrow$ useremo la notazione $P(\{X\in B\})$, o anche $P(X\in B)$

### Distribuzione o legge di una v.a. reale
È la corrispondenza tra "gli insiemi della retta $B$ per cui $\{X\in B\}\in\mathcal{A}$" e i valori $P(\{X\in B\})$ relativi.

### Funzione di distribuzione di una v.a. reale
È la funzione $F_{X}:\mathbb{R}\to[e,1]$ così definita: $F_{X}(t)=P(X\leq t)$

#### Commento (importante)
La conoscenza di $F_{X}$ consente di individuare la distribuzione di una v.a. $X$.
Quindi, se uno conosce i valori di $P(X\in B)$ per $B=(-\infty,t]$ (al variare di tutti i valori di $t\in\mathbb{R}$), è possibile conoscere tutti i valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$

### Proprietà della funzione di distribuzione $F_{X}$
1) $F_{X}$ non è decrescente, cioè  $F_{X}(t_{1})\leq F_{X}(t_{2})\quad\quad\forall\ t_{1},t_{2}\in\mathbb{R}$ tali che $t_{1}\leq t_{2}$
   Questo si verifica facilmente osservando che
   $t_{1}\leq t_{2}\implies(-\infty,t_{1}]\subset(-\infty,t_{2}]\implies P(X\leq t_{1})\leq P(X\leq t_{2})\implies F_{X}(t_{1})\leq F_{X}(t_{2})$
   
2) $\displaystyle\lim_{t\to-\infty}F_{X}(t)=0$ e $\displaystyle\lim_{t\to+\infty}F_{X}(t)=1$
   
3) $F_{X}$ è continua a destra, cioè $\forall\ t_{0}\in\mathbb{R}\quad\quad\displaystyle\lim_{t\to t_{0}^{+}}F_{X}(t)=F_{X}(t_{0})$
-- Da inserire immagine da pagina 6 pdf lezione 5--

#### Digressione
C'è una parte dei libri (una minoranza) che definisce la funzione di distribuzione in questo modo: $$F_{X}(t)=P(X<t)\quad\quad(\text{per ogni }t\in\mathbb{R})$$
In questo caso le proprietà viste prima continuano a valere, tranne che la continuità a destra. In questo caso si ha che $F_{X}$ è continua a sinistra $$\lim_{t\to t_{0}^{-}}F_{X}(t)=F_{X}(t_{0})$$

### Variabili aleatorie discrete
