# Variabili aleatorie discrete
Nozioni generali sulle variabili aleatorie: definizione, funzione di distribuzione, densità discreta.
In questo capitolo tratteremo essenzialmente Variabili Aleatorie Discrete (spesso definite su spazi di probabilità ($\ohm,\mathcal{A},P$) con $r$ discreto, cioè finito o numerabile).

In ogni caso nella parte iniziale di questa lezione diremo alcune cose sulle variabili aleatorie in generale. Spesso useremo l'abbreviazione "v.a.".

In generale una v.a. (definita su uno spazio di probabilità ($\ohm,\mathcal{A},P$)) è una funzione del tipo $$X:\ohm\to\mathcal{X}$$dove $\mathcal{X}$ è un qualche insieme, e con certe proprietà.

In questo corso tratteremo il caso in cui $X=\mathbb{R}$ (o un suo sottoinsieme); in qualche caso considereremo il caso $\mathcal{X}=\mathbb{R}^{n}$ per qualche $n\geq 2$ (però solo per v.a. discrete).

Il concetto di v.a. è utile perché spesso gli eventi di interesse negli esercizi sono esprimibili tramite v.a.. Consideriamo un esempio.
#### Esempio
Si lanciano due dadi equi e consideriamo l'evento "la somma dei due numeri ottenuti è uguale a 5". Allora è utile fare riferimento alla seguente scelta dell'insieme $\ohm$: $$\ohm=\{1,\dots,6\}\times\{1,\dots,6\}=\{w=(w_{1},w_{2}):w_{1},w_{2}\in\{1,\dots,6\}\}$$Essendo $\ohm$ un insieme finito, non ci sono problemi nello scegliere $\mathcal{A}=P(\ohm)$

Inoltre è opportuno considerare la seguente funzione $X:\ohm\to\mathbb{R}$ (che è una v.a.) definita come segue: $$\begin{array}{}
X(w)=X(w_{1},w_{2})=w_{1}+w_{2} & (\forall\ w=(w_{1},w_{2})\in\ohm)
\end{array}$$Allora l'evento di interesse è $$\{w=(w_{1},w_{2})\in\ohm:X(w)=5\}$$
### Definizione
Sia $(\ohm,\mathcal{A},P)$ uno spazio di probabilità. Inoltre sia $X:\ohm\to \mathbb{R}$ una funzione.
Allora la funzione $X$ è una v.a. (reale) se vale la seguente condizione $$\forall\ t\in\mathbb{R}\quad\quad\{w\in\ohm:X(w)\leq t\}\in\mathcal{A}$$In altri termini si richiede che le controimmagini delle semirette del tipo $(-\infty,t]$ (al variare di $t\in\mathbb{R}$), che sono sottoinsiemi di $\ohm$, siano elementi della $\delta$-algebra $\mathcal{A}$.

Questo consente di dire che, per queste controimmagini, è possibile definire la probabilità.
Quindi possiamo dire che, per ogni $t\in\mathbb{R}$, $P(\{w\in\ohm:X(w)\leq t\})$ è un numero ben definito.

Quindi si richiede che, se $B=(-\infty,t]$ per una qualsiasi scelta di $t\in\mathbb{R}$, $$\{w\in\ohm:X(w)\in B\}\in\mathcal{A}\quad\quad\quad(*)$$A partire da questa richiesta, condizione di $(*)$ vale anche per le altre scelte di $B$ "naturali" da considerare: $$\begin{array}{l|l}
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
C'è una parte dei libri (una minoranza) che definisce la funzione di distribuzione in questo modo: $$F_{X}(t)=P(X<t)\quad\quad(\text{per ogni }t\in\mathbb{R})$$In questo caso le proprietà viste prima continuano a valere, tranne che la continuità a destra. In questo caso si ha che $F_{X}$ è continua a sinistra $$\lim_{t\to t_{0}^{-}}F_{X}(t)=F_{X}(t_{0})$$
### Variabili aleatorie discrete
Sia $X:\ohm\to \mathbb{R}$ una v.a. (reale) definita su uno spazio di probabilità $(\ohm,\mathcal{A},P)$.
Indichiamo con $\delta_{\mathcal{X}}$ l'insieme dei valori assunti da $X$, cioè l'immagine di $X$ vista come funzione.

La definizione di questo insieme in termini matematici è la seguente: $$\delta_{\mathcal{X}}=\{x\in\mathbb{R}: \exists\ w\in\ohm\text{ tale che }X(w)=x\}$$
### Definizione
Una v.a. (reale) $X$ è una v.a. discreta se l'insieme $\delta_{\mathcal{X}}$ è discreto (cioè $\delta_{\mathcal{X}}$ è finito o numerabile).
#### Osservazione
Se $\ohm$ è discreto, allora $X$ è una v.a. discreta.
In generale non vale il viceversa:  ad esempio si pensi al caso in cui, per qualche $c\in\mathbb{R}$ si ha $$X(w)=c\quad\quad\forall\ w\in\ohm$$(quindi $\delta_{\mathcal{X}}=\{c\}$) e $X$ non è un insieme discreto.



Quando $X$ è una v.a. discreta, allora possiamo pensare di avere $$\delta_{\mathcal{X}}=\{x_{i}\}_{i\in I}\quad\quad I\text{ è  un insieme discreto}$$In corrispondenza, per ogni $B\in\mathbb{R}$ si ha $$\begin{array}{}
P(X\in B)=P(X\in B\cap \delta_{\mathcal{X}})=P(X\in B\cap(\underset{i\in I}{\cup}\{x_{i}\}))=\displaystyle\sum_{i\in I}P(X\in B\cap\{x_{i}\})= \\
\underset{\underset{\text{somme finite o semi}\Rightarrow}{}}{=}\displaystyle\sum_{x_{i}\in\delta_{\mathcal{X}}\cap B}P(X=x_{i})
\end{array}$$Quindi la distribuzione di una v.a. discreta $X$, cioè la conoscenza dei valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$, è individuata dalla conoscenza di $\delta_{X}=\{x_{i}\}_{i\in I}$ e delle probabilità $\{P(X=x_{i})\}_{i\in I}$.

Si osservi anche che, per $B=\mathbb{R}$, si ha $$\underset{=1}{\underbrace{P(X\in\mathbb{R})}} =\displaystyle\sum_{x_{i}\in\underset{=\delta_{\mathcal{X}}}{\underbrace{\delta_{\mathcal{X}}\cap\mathbb{R}}}}$$da cui segue $$\begin{bmatrix}
\displaystyle\sum_{x_{i}\in\delta_{\mathcal{X}}}P(X=x_{i})=1
\end{bmatrix}$$
#### Osservazione
Possiamo anche dire che $$\displaystyle\sum_{\begin{array}{}
x_{i}\in\delta_{\mathcal{X}} \\
P(X=x_{i})>0
\end{array}}P(X=x_{i})=1$$



Più in generale si può considerare la funzione $P_{\mathcal{X}}:\mathbb{R}\to[0,1]$ così definita: $$ P_{\mathcal{X}}(x)=P(X=x)\quad\quad\forall\ x\in\mathbb{R}$$Tale funzione è detta **Densità Discreta** della v.a. $X$.
### Proposizione 
$x\not\in\delta_{X}\implies P_{X}(x)=0$
#### Dimostrazione 
Si ha $$P_{X}(x)=P(\underset{=\varnothing\ (\ x\ \not\in\ \delta_{X})}{\underbrace{\{w\in\ohm:X(w)=x\}}})=P(\varnothing)=0$$Come vedremo successivamente la funzione di distribuzione ha maggiore interesse quando la v.a. $X$ è continua.
In ogni caso vedremo come è fatta $F_{X}$ nel caso di v.a. discrete. Iniziamo con il caso in cui $\delta_{X}$ è un *insieme finito*; ad esempio $\delta_{X}=\{x_{1},\dots,x_{n}\}$ con $x_{1}<\dots<x_{n}$.
In questo grafico si ha $n=3$ 

--- pagina 12 pdf 05 ---
#### Osservazione
Dal grafico (caso $n=3$) si vede che $$\underset{=P_{X}(x_{1})+P_{X}(x_{2})+P_{X}(x_{3})}{\underbrace{\displaystyle\sum_{i=1}^{n}P_{X}(x_{i})}}=1$$


Nel caso in cui $\delta_{X}$ è *infinito numerabile* la casistica è più varia e ci possono essere casi molto complicati. Qui faccio riferimento a due casi (soprattutto il primo ci interessa in vista di ciò che vedremo con le distribuzioni di Poisson e geometriche)
1) $\delta_{X}=\{x_{e},x_{e}+1,x_{e}+2,\dots\}$
2) $\delta_{X}=\left\{ 1,\frac{1}{2},\frac{1}{3},\dots,\frac{1}{n},\dots\right\}$

---
Nota successiva: [[Distribuzioni binomiale e ipergeometrica]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
