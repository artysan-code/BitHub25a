## Esercizio  1
Un ”gioco” consiste nel lanciare 3 volte un dado equo.
1) Calcolare la probabilità che escano almeno due numeri dispari
2) Calcolare la probabilità che esca la sequenza (1, pari, dispari) sapendo che sono usciti esattamente due numeri dispari.
3) ) Consideriamo una sequenza di ”giochi”. Calcolare la probabilità che la sequenza (1, pari, dispari) esca per la prima volta ad un gioco pari (il secondo, il quarto, il sesto, l’ottavo, ecc.)

### Soluzione
1) Sia X la variabile aleatoria che conta il numero di volte che esce un numero dispari. Allora la probabilità richiesta è $P(X\geq 2)=P(X=2)+P(X=3)=\binom{3}{2}\left( \frac{1}{2} \right)^{3}+\binom{3}{2}\left( \frac{1}{2} \right)^{3}$
2) Sia $E$ l'evento ”esce la sequenza (1, pari, dispari)”. La probabilità richiesta è $\displaystyle P(E|X=2)=\frac{P(E\cap\{X=2\})}{P(X=2)}=\frac{P(E)}{\binom{3}{2}\left( \frac{1}{2} \right)^{3}}=\frac{\frac{1}{6} \frac{1}{2} \frac{1}{2}}{\frac{3}{8}}=\frac{1}{24} \frac{8}{3}=\frac{1}{9}$
3) ) La variabile aleatoria $Y$ che conta il numero di ”giochi” necessari per avere per la prima volta la sequenza (1, pari, dispari) ha distribuzione geometrica traslata con parametro $p=P(E)=\frac{1}{24}$. 
   Allora la probabilità richiesta è $\displaystyle P(Y\in\{2,4,6,8,\dots\})=p\sum_{k\geq 1}(1-p)^{2h-1}=\frac{p}{1-p}\sum_{h\geq 1}(1-p)^{2h}=$
   $\displaystyle=\frac{p}{1-p}\frac{(1-p)^{2}}{1-(1-p)^{2}}=\frac{p(1-p)}{1-(1-2p+p^{2})}=\frac{p(1-p)}{2p-p^{2}}=\frac{1-p}{2-p}=\frac{1-\frac{1}{24}}{2-\frac{1}{24}}=\frac{\frac{23}{24}}{\frac{47}{24}}=\frac{23}{47}$ 

## Esercizio  2
Abbiamo due urne: l’urna 1 con 9 palline bianche e 1 nera, e l’urna 2 con 19 palline bianche e 1 nera. Si lancia una moneta equa: se esce testa, si sceglie l’urna 1; se esce croce si sceglie l’urna 2. Infine si estrae a caso una pallina dall’urna scelta.
1) Calcolare la probabilità di estrarre una pallina bianca.

### Soluzione
1) ) Con notazioni ovvie, usando la formula delle probabilità totali si ha $$P(B)=P(B|T)P(T)+P(B|T^{c})P(T^{c})=\frac{9}{10} \frac{1}{2}+\frac{19}{20} \frac{1}{2}=\frac{9}{20}+\frac{19}{40}=\frac{18+19}{40}=\frac{37}{40}$$

## Esercizio  3
Consideriamo la seguente densità congiunta discreta: $$p_{X_{1},X_{2}}(0,0)=p_{X_{1},X_{2}}(0,1)=p_{X_{1},X_{2}}(1,0)=\frac{1}{5};\quad\quad p_{X_{1},X_{2}}(1,1)=\frac{2}{5}$$
1) Trovare la retta di regressione di $X_2$ rispetto a $X_1$.
2) Calcolare $P(X_1=1|X_1\neq X_2)$

### Soluzione
1) Le due variabili aleatorie $X_1$ e $X_2$ hanno entrambe distribuzione Bernoulliana (ovvio) ed entrambe con parametro $p=\frac{3}{5}$; infatti $P(X_{1}=1)=p_{X_{1},X_{2}}(1,0)+p_{X_{1},X_{2}}(1,1)=\frac{3}{5}$ e $P(X_{2}=1)=p_{X_{1},X_{2}}(0,1)+p_{X_{1},X_{2}}(1,1)=\frac{3}{5}$.
   Quindi $\mathbb{E}[X_{1}]=\mathbb{E}[X_{2}]=\frac{3}{5}$ e $Var[X_{1}]=\frac{3}{5}\left( 1- \frac{3}{5} \right)=\frac{6}{25}$.
   Inoltre (ci sono quattro addendi, e l’unico non nullo è quello per $(x_{1},x_{2})=(1,1)$) $\displaystyle\mathbb{E}[X_{1}X_{2}]=\sum_{x_{1},x_{2}=0}^{1}x_{1}x_{2}p_{X_{1},X_{2}}(x_{1},x_{2})=p_{X_{1},X_{2}}(1,1)=\frac{2}{5}$, e quindi $Cov(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\frac{2}{5}-\frac{3}{5} \frac{3}{5}=\frac{10-9}{25}=\frac{1}{25}$. Allora la retta di regressione richiesta è $x_{2}=ax_{1}+b$, dove $\displaystyle a=\frac{Cov(X_{1},X_{2})}{Var[X_{1}]}=\frac{\frac{1}{25}}{\frac{6}{25}}=\frac{1}{6}$ e $b=\mathbb{E}[X_{2}]-a\mathbb{E}[X_{1}]=\frac{3}{5}-\frac{1}{6} \frac{3}{5}=\frac{5}{6} \frac{3}{5}=\frac{3}{6}=\frac{1}{2}$
2) Si ha $\displaystyle P(X_{1}=1|X_{1}\neq X_{2})=\frac{P(\{X_{1}=1\}\cap\{X_{1}\neq X_{2}\})}{P(X_{1}\neq X_{2})}= \frac{p_{X_{1},X_{2}}(1,0)}{p_{X_{1},X_{2}}(1,0)+p_{X_{1},X_{2}}(0,1)}=\frac{\frac{1}{5}}{\frac{1+1}{5}}=\frac{1}{2}$ 

## Esercizio  4
Sia $X$ una variabile aleatoria con densità continua $$f_{X}(x)=\begin{cases}
x & \text{se }x\in(0,1) \\
x+1 & \text{se }x\in(-1,0) \\
0 & \text{altrimenti}
\end{cases}$$
1) Trovare la funzione di distribuzione della variabile aleatoria $Y = |X|$.
2) Verificare che $\mathbb{E}[X^{2k}]=\frac{1}{2k+1}$ per $k\geq 0$ intero.

### Soluzione
1) Si ha $P(0\leq Y\leq 1)=1$ e quindi $F_{Y}(y)=0$ per $y\leq 0$ e $F_{Y}(y)=1$ per $y\geq 1$. 
   Per $y\in(0,1)$ si ha $\displaystyle F_{Y}(y)=P(|X|\leq y)P(-y\leq X\leq y)=\int_{-y}^{0}x+1\, dx+\int_{0}^{y}x\,dx=$
   $\displaystyle=\left[ \frac{x^{2}}{2}+x \right]^{x=0}_{x=-y}+\left[ \frac{x^{2}}{2} \right]_{x=0}^{x=y}=0-\left( \frac{-y^{2}}{2}-y \right)+\frac{y^{2}}{2}-0=y$
   
   #### Osservazione
   La variabile aleatoria $Y$ ha distribuzione uniforme su $(0,1)$
2) Si ha $\displaystyle\mathbb{E}[X^{2k}]=\int_{-1}^{0}x^{2k}(x+1)\,dx+\int_{0}^{1}x^{2k}x\,dx=\int_{-1}^{0}x^{2k+1}+x^{2k}\,dx+\int_{0}^{1}x^{2k+1}\,dx=$
   $\displaystyle=\left[ \frac{x^{2k+2}}{2k+2}+ \frac{x^{2k+1}}{2k+1}\right]_{x=-1}^{x=0}+\left[ \frac{x^{2k+2}}{2k+2} \right]_{x=0}^{x=1}=0-\left( \frac{(-1)^{2k+2}}{2k+2}+\frac{(-1)^{2k+1}}{2k+1} \right)+\frac{1}{2k+2}-0=$
   $\displaystyle=-\frac{1}{2k+2}-\frac{-1}{2k+1}+\frac{1}{2k+2}=\frac{1}{2k+1}$
   
   #### Osservazione
   In accordo con la teoria si ha $\mathbb{E}[X]^{2k}\in[0,1]$ e $\mathbb{E}[X^{2\cdot 0}]=1$

## Esercizio  5
Poniamo $\Phi(y)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{y}e^{-\frac{x^{2}}{2}}\, dx$
1) Sia $X$ una variabile aleatoria Normale con media 1 e varianza 1. Dire per quale valore di $z>1$ si ha $\displaystyle P(\{0<X<1\}|\{0<X<z\})=\frac{1}{2}$
2) Sia $\{X_{n}:n\geq 1\}$ una successione di variabili aleatorie i.i.d. con distribuzione uniforme in $(-b,b)$ per qualche $b>0$. Dire per quale valore di $b$ si ha $$\lim_{n\to\infty}P\left(\frac{X_{1}+\dots+X_{n}}{\sqrt{n}}<\sqrt{3}\right)=\Phi(2)$$
### Soluzione
1) Si ha $$\begin{array}{r}
\displaystyle\frac{1}{2}=P(\{0<X<1\}|\{0<X<z\})=\frac{P(\{0<X<1\}\cap\{0<X<z\})}{P(0<X<x)}=\frac{P(0<X<1)}{P(0<X<z)}= \\
\displaystyle=\frac{P(0-1<X^{*}<1-1)}{P(0-1<X^{*}<z-1)}=\frac{\Phi(0)-\Phi(1)}{\Phi(z-1)-\Phi(-1)}=\frac{0.5-\Phi(-1)}{\Phi(z-1)-\Phi(-1)}
\end{array}$$da cui segue $$\begin{array}{l}
0.5(\Phi(z-1)-\Phi(-1))=0.5-\Phi(-1), \\
0.5\Phi(z-1)-0.5=-0.5\Phi(-1), \\
1 -\Phi(-1) = \Phi(z-1), \\
\Phi(1)=\Phi(z-1)
\end{array}$$e quindi $z=2$
2) ) Si deve applicare il Teorema Limite Centrale e, per proprietà della distribuzione uniforme, si ha $$\mu=\frac{-b+b}{2}=0\quad\quad\sigma=\sqrt{\frac{(b-(-b))^{2}}{12}}=\sqrt{\frac{4b^{2}}{12}}=\frac{b}{\sqrt{3}}$$quindi si ha $$\begin{array}{}
\displaystyle\lim_{n\to\infty}P\left( \frac{X_{1}+\dots+X_{n}}{\sqrt{n}}<\sqrt{3} \right)=\lim_{n\to\infty}P\left( \frac{X_{1}+\dots+X_{n}}{\sigma \sqrt{n}}< \frac{\sqrt{3}}{\sigma} \right)= \\
\displaystyle=\Phi\left( \frac{\sqrt{3}}{\sigma} \right)=\Phi\left( \frac{3}{b} \right)
\end{array}$$allora si deve avere $\frac{3}{b}=2$, da cui segue $b=\frac{3}{2}$