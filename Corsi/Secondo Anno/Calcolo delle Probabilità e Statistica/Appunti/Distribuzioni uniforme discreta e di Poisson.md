# Distribuzioni uniforme discreta e di Poisson
Distribuzione uniforme discreta, distribuzione di Poisson e approssimazione poissoniana della binomiale.
### Prossimi argomenti (altre distribuzioni discrete notevoli)
- **Distribuzione uniforme discreta**
- **Distribuzione di Poisson** (nome di un matematico francese)
- **Distribuzione geometrica e distribuzioni collegate** (nelle prossime lezioni)
#### Osservazione
Spesso saranno definite a partire dall'espressione della distribuzione (o della densità discreta) senza fare riferimento a $(\ohm,\mathcal{A},P)$.
### Distribuzione uniforme discreta
Si tratta del caso in cui, per un insieme finito $E=\{x_{1},\dots,x_{n}\}\subset \mathbb{R}$ (lettere minuscole), si ha $$P(X\in B)=\frac{\#(B\cap E)}{\#E}=\frac{\#(B\cap E)}{n}\quad\quad\forall\ B\subset \mathbb{R}$$
#### Esempio
Si ha questa distribuzione con $E=\{1,2,3,4,5,6\}$ se $X$ è la v.a. che indica il numero che esce lanciando un dado equo.
### Distribuzione di Poisson
Una v.a. $X$ ha **distribuzione di Poisson con parametro $\lambda>0$** (in qualche caso scriveremo $X\sim POISSON(\lambda)$) se si ha $$\begin{bmatrix}
P_{X}(k)=\frac{\lambda^{k}}{k!}e^{-\lambda}
\end{bmatrix}\quad\quad\forall\ k\in\{0,1,2,3,\dots\}$$
#### Osservazione
La definizione è ben posta se $\displaystyle\sum_{k=0}^{\infty}P_{X}(k)=1$. In effetti si ha $$\sum_{k=0}^{\infty}P_{X}(k)=\sum_{k=0}^{\infty}\frac{\lambda^{k}}{k!}e^{-\lambda}=e^{-\lambda}\underset{=e^{\lambda}\text{ per definizione}}{\underbrace{\sum_{k=0}^{\infty}\frac{\lambda^{k}}{k!}}}=e^{-\lambda}\cdot e^{\lambda}=1$$
#### Esempio (Poisson e condizionamento)
Sia $X\sim POISSON(\lambda=4)$.
1) Calcolare $P(X>2)$. Per eventi di questo tipo si deve passare alla probabilità dell'evento complementare: $$P(X>2)=1-P(X\leq 2)=1-\sum_{k=0}^{2}P_{X}(k)=1-\left( \frac{4^{0}}{0!}e^{-4}+\frac{4^{1}}{1!}e^{-4}+\frac{4^{2}}{2!}e^{-4} \right)=1-(1+4+8)e^{-4}=1-13e^{-4}$$
2) Calcolare $P(X=k|X\leq 2)$ per ogni $k\geq 0$ intero. Si ha $$P(X=k|X\leq 2)=\frac{P(\{X=k\}\cap\{X\leq 2\})}{P(X\leq 2)}=\begin{cases}
\frac{P(X=k)}{P(X\leq 2)} & \text{per }k\in\{0,1,2\}\quad(\text{perché }\{X=k\}\subset\{X\leq 2\}) \\
0 & \text{per }k\geq 3\quad(\text{perché }\{X=k\}\cap\{X\leq 2\}=\varnothing)
\end{cases}$$ed inoltre, per $k=0,1,2$, $$\frac{P(X=k)}{P(X\leq 2)}=\frac{\frac{4^{k}}{k!}\cancel{e^{-4}}}{\left( \frac{4^{0}}{0!}+\frac{4^{1}}{1!}+\frac{4^{2}}{2!} \right)\cancel{e^{-4}}}=\begin{cases}
1/13 & \text{per }k=0 \\
4/13 & \text{per }k=1 \\
8/13 & \text{per }k=2
\end{cases}$$   **Osservazione.** Gli eventi $\{\{X=k\}:k\geq 0\}$ costituiscono una partizione numerabile, quindi si deve avere $\displaystyle\sum_{k=0}^{\infty}P(X=k|X\leq 2)=1$. In effetti, trascurando gli addendi per $k\geq 3$ (tutti uguali a zero), $$\sum_{k=0}^{\infty}P(X=k|X\leq 2)=\sum_{k=0}^{2}P(X=k|X\leq 2)=\frac{1+4+8}{13}=1$$
### Approssimazione della binomiale con la Poisson
Sia $\lambda>0$ e sia $n\geq\lambda$ intero; in questo modo $\frac{\lambda}{n}\in[0,1]$, e non è restrittivo perché poi siamo interessati a considerare un limite per $n\to+\infty$.
Prendiamo le densità di $X\sim BIN\left( n,p_{n}=\frac{\lambda}{n} \right)$. Allora, per $k\in\{0,1,\dots,n\}$, si ha $$\begin{array}{ll}
P_{X}(k) & =\binom{n}{k}\left( \frac{\lambda}{n} \right)^{k}\left( 1-\frac{\lambda}{n} \right)^{n-k}=\frac{n!}{k!(n-k)!}\cdot \frac{\lambda^{k}}{n^{k}}\left( 1-\frac{\lambda}{n} \right)^{n}\left( 1-\frac{\lambda}{n} \right)^{-k} \\
 & =\frac{\lambda^{k}}{k!}\underset{=\left( 1-\frac{1}{n} \right)\cdot\ \dots\ \cdot\left( 1-\frac{k-1}{n} \right)\ \longrightarrow\ 1}{\underbrace{\frac{n(n-1)\cdot\dots\cdot(n-k+1)}{n\cdot n\cdot\dots\cdot n}}}\underset{\longrightarrow\ e^{-\lambda}}{\underbrace{\left( 1-\frac{\lambda}{n} \right)^{n}}}\underset{\longrightarrow\ 1}{\underbrace{\left( 1-\frac{\lambda}{n} \right)^{-k}}}\quad\underset{n\to\infty}{\longrightarrow}\quad \frac{\lambda^{k}}{k!}e^{-\lambda}
\end{array}$$dove si è usato $\frac{n!}{(n-k)!}=n(n-1)\cdot\dots\cdot(n-k+1)$, e dove il limite finale è la densità discreta di una $POISSON(\lambda)$.
#### Osservazione
Per ogni $k\geq 0$ intero esiste $n$ tale che $n\geq k$, e quindi questo limite vale per ogni $k\geq 0$ intero.
Ricapitolando, per $X=X_{n}\sim BIN\left( n,p_{n}=\frac{\lambda}{n} \right)$ e $Z\sim POISSON(\lambda)$, si ha $$\begin{bmatrix}
\lim_{n\to\infty}P_{X_{n}}(k)=P_{Z}(k)\quad\quad\forall\ k\geq 0\text{ intero}
\end{bmatrix}$$(limite delle densità discrete).
#### Commento
Questo limite ha un interesse teorico che non approfondiremo. Al contrario c'è un **interesse pratico**: serve per calcolare valori approssimati di probabilità di eventi legati a v.a. con distribuzione binomiale "con $n$ grande e $p$ piccolo".
#### Esempio 1
Sia $X\sim BIN\left( n=1000,p=\frac{3}{500} \right)$; calcolare $P(X\geq 5)$.
(Si può pensare di fare riferimento a un'urna con 500 palline numerate da 1 a 500; si compiono 1000 estrazioni casuali **con** reinserimento e si vuole la probabilità di estrarre almeno 5 volte uno dei numeri 1, 2, 3.)
Il valore esatto è $$P(X\geq 5)=\sum_{k=5}^{1000}\binom{1000}{k}\left( \frac{3}{500} \right)^{k}\left( 1-\frac{3}{500} \right)^{1000-k}=1-\sum_{k=0}^{4}\binom{1000}{k}\left( \frac{3}{500} \right)^{k}\left( 1-\frac{3}{500} \right)^{1000-k}$$ma non è semplice calcolarne un valore approssimato. Facciamo quindi riferimento all'approssimazione Poissoniana della binomiale: si ha $P_{X}(k)\approx P_{Z}(k)$ (per $k\geq 0$ intero) dove $Z\sim POISSON\left( \lambda=np=1000\cdot \frac{3}{500}=6 \right)$. Allora $$P(X\geq 5)=1-P(X\leq 4)=1-\sum_{k=0}^{4}P(X=k)\overset{\text{approx.}}{\approx}1-\sum_{k=0}^{4}\frac{6^{k}}{k!}e^{-6}=1-(1+6+18+36+54)e^{-6}=1-115e^{-6}$$
#### Esempio 2
Stessa urna dell'esempio precedente. Si estraggono 200 palline, una alla volta e **con** reinserimento. Calcolare la probabilità di estrarre al più 2 volte uno dei numeri 1, 2, 3, 4, 5, 6, 7.
La probabilità richiesta è $P(Y\leq 2)$ dove $Y\sim BIN\left( n=200,p=\frac{7}{500} \right)$, cioè $P(Y\leq 2)=\sum_{k=0}^{2}\binom{200}{k}\left( \frac{7}{500} \right)^{k}\left( 1-\frac{7}{500} \right)^{200-k}$.
Si ha $P_{Y}(k)\approx P_{Z}(k)$ (per ogni $k\geq 0$ intero) dove $Z\sim POISSON\left( \lambda=np=200\cdot \frac{7}{500}=\frac{14}{5} \right)$. Allora $$P(Y\leq 2)=\sum_{k=0}^{2}P(Y=k)\overset{\text{approx.}}{\approx}\sum_{k=0}^{2}\frac{(14/5)^{k}}{k!}e^{-14/5}=\left( 1+\frac{14}{5}+\frac{98}{25} \right)e^{-14/5}=\frac{193}{25}e^{-14/5}$$

--- Fine lezione 07 ---
### Esercizio teorico: un numero aleatorio di lanci (Poisson "assottigliata")
> [!question] Esercizio segnalato dal prof come "teorico, un po' difficile"
> È un risultato notevole: se il **numero di prove** è a sua volta aleatorio con distribuzione di Poisson, il numero di successi resta di Poisson, con parametro riscalato da $p$.

Sia $N\sim POISSON(\lambda)$ per qualche $\lambda>0$. Si lancia una moneta $N$ volte: per ogni lancio esce testa con probabilità $p\in(0,1)$ ed esce croce con probabilità $1-p$. Sia $X$ la v.a. che conta il numero di teste ottenute.
1) Trovare la densità discreta di $X$.
2) Calcolare $P(N=n|X=k)$ per $n\geq k\geq 0$.
#### Osservazioni preliminari
- Si escludono i casi $p=0$ e $p=1$ per evitare casi banali.
- Se si verifica l'evento $\{N=0\}$ (non si lanciano monete), allora si verifica $\{X=0\}$ (non escono teste).
#### Svolgimento
1) La v.a. $X$ assume valori interi non negativi. Conviene fare riferimento alla [[Cap 2 - Introduzione alla probabilità#Formula delle Probabilità Totali|formula delle probabilità totali]] con la partizione $\{\{N=n\}:n\geq 0\}$: $$\forall\ k\geq 0\text{ (intero)}\quad\quad P_{X}(k)=P(X=k)=\sum_{n=0}^{\infty}\underset{(*)}{\underbrace{P(X=k|N=n)}}\ \underset{=\frac{\lambda^{n}}{n!}e^{-\lambda}}{\underbrace{P(N=n)}}$$dove $$(*)=P(X=k|N=n)=\begin{cases}
0 & \text{se }k>n \\
\binom{n}{k}p^{k}(1-p)^{n-k} & \text{se }0\leq k\leq n
\end{cases}$$Quindi (la somma parte da $n=k$ perché gli addendi con $n<k$ sono nulli) $$\begin{array}{ll}
P_{X}(k) & =\displaystyle\sum_{n=k}^{\infty}\binom{n}{k}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{n!}e^{-\lambda}=e^{-\lambda}\sum_{n=k}^{\infty}\frac{\cancel{n!}}{k!(n-k)!}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{\cancel{n!}} \\
 & =e^{-\lambda}\frac{p^{k}}{k!}\displaystyle\sum_{n=k}^{\infty}\frac{(1-p)^{n-k}}{(n-k)!}\lambda^{\overset{}{n-k+k}}=e^{-\lambda}\frac{p^{k}}{k!}\lambda^{k}\sum_{n=k}^{\infty}\frac{\lambda^{n-k}(1-p)^{n-k}}{(n-k)!} \\
 & =e^{-\lambda}\frac{(\lambda p)^{k}}{k!}\underset{\text{cambio di indice }h=n-k}{\underbrace{\displaystyle\sum_{h=0}^{\infty}\frac{(\lambda(1-p))^{h}}{h!}}}=e^{-\lambda}\frac{(\lambda p)^{k}}{k!}e^{\lambda(1-p)}=\begin{bmatrix}
\frac{(\lambda p)^{k}}{k!}e^{-\lambda p}
\end{bmatrix}
\end{array}$$   **Osservazione.** Possiamo dire che $X\sim POISSON(\lambda p)$.
2) Per calcolare $P(N=n|X=k)$ usiamo la [[Cap 2 - Introduzione alla probabilità#Formula di Bayes|formula di Bayes]], perché conosciamo $P(X=k|N=n)$ (l'espressione $(*)$ vista sopra). Quindi, per $n\geq k$ intero, $$\begin{array}{ll}
P(N=n|X=k) & =\frac{P(X=k|N=n)P(N=n)}{P(X=k)}=\frac{\binom{n}{k}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{n!}e^{-\lambda}}{\frac{(\lambda p)^{k}}{k!}e^{-\lambda p}}=\frac{\frac{\cancel{n!}}{\cancel{k!}(n-k)!}\cancel{p^{k}}(1-p)^{n-k}\frac{\lambda^{n}}{\cancel{n!}}e^{-\lambda}}{\frac{\lambda^{k}\cancel{p^{k}}}{\cancel{k!}}e^{-\lambda p}} \\
 & =\frac{(1-p)^{n-k}}{(n-k)!}\lambda^{n-k}e^{-\lambda+\lambda p}=\frac{(\lambda(1-p))^{n-k}}{(n-k)!}e^{-\lambda(1-p)}
\end{array}$$   **Osservazione.** Possiamo dire che $$p(n)=\begin{cases}
\frac{(\lambda(1-p))^{n-k}}{(n-k)!}e^{-\lambda(1-p)} & \text{per }n\geq k\text{ intero} \\
0 & \text{altrimenti}
\end{cases}$$è la densità discreta di $Z+k$, dove $Z\sim POISSON(\lambda(1-p))$.

---
Nota precedente: [[Distribuzione multinomiale]]. Nota successiva: [[Distribuzione geometrica]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
