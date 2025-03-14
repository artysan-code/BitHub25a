## Esercizio 1
Si lanciano due dadi: il primo è un dado equo, il secondo è un dado con i numeri 1, 2, 3, 4, 5, 5. Sia $X$ la variabile aleatoria che conta il numero di volte che esce il numero 5, e sia $Y$ la variable aleatoria che conta il numero di volte che esce un numero minore o uguale a 3.
1) Trovare la densità discreta di $X$
2) Trovare la densità discreta di $Y$
3) Sia $E$ l’evento "esce il 5 nel lancio del dado equo". Calcolare $P(E|X = 1)$.

#### Soluzione
1) Abbiamo due prove indipendenti con probabilità di successo $\frac{1}{6}$ e $\frac{2}{6}$ rispettivamente. Quindi $$\begin{cases}
p_{X}(0)=\left( 1- \frac{1}{6} \right)\left( 1- \frac{2}{6} \right)= \frac{20}{36}=\frac{5}{9} \\
p_{X}(1)=\frac{1}{6}\left( 1- \frac{2}{6} \right)+\left( 1-\frac{1}{6} \right) \frac{2}{6}=\frac{4+10}{36}=\frac{14}{36}=\frac{7}{18} \\
p_{X}(2)=\frac{1}{6}\cdot \frac{2}{6}=\frac{2}{36}=\frac{1}{18}
\end{cases}$$
2) Abbiamo due prove indipendenti, entrambe con probabilità di successo $\frac{3}{6}=\frac{1}{2}$. Quindi si ha una distribuzione Binomiale con parametri $n = 2$ e $p = \frac{1}{2}$, cioè $p_{Y}(k)=\binom{2}{k}\left(\frac{1}{2}\right)^{2}$  per $k\in\{0, 1, 2\}$, da cui segue $$\begin{cases}
p_{Y}(0)=\frac{1}{4}, \\
p_{Y}(1)=\frac{2}{4}=\frac{1}{2}, \\
p_{Y}(2)=\frac{1}{4}
\end{cases}$$
3) Tenendo conto del valore di $p_X(1)$ calcolato prima, la probabilità condizionata richiesta è $$P(E|X=1)=\frac{P(E\cap\{X=1\})}{P(X=1)}=\frac{\frac{1}{6}\left( 1-\frac{2}{6} \right)}{\frac{7}{18}}=\frac{2}{7}$$

## Esercizio 2
Abbiamo due urne. Entrambe hanno 2 palline bianche e 3 nere. Si estrae a caso una pallina dalla prima urna e la si mette nella seconda. Poi si estraggono a caso due palline in blocco dalla seconda urna.
1) Calcolare la probabilità di estrarre due palline dello stesso colore dalla seconda urna

#### Soluzione
1) Con notazioni ovvie, usando la formula delle probabilità totali si ha $$\begin{array}{l}
P(E) & =P(E|B_{1})P(B_{1})+P(E|B_{1}^{c})P(B_{1}^{c})= \\
 & =\left(\frac{\binom{3}{2}\binom{3}{0}}{\binom{6}{2}}+\frac{\binom{3}{0}\binom{3}{2}}{\binom{6}{2}}\right)\frac{2}{5}+\left( \frac{\binom{2}{2}\binom{4}{0}}{\binom{6}{2}}+\frac{\binom{2}{0}\binom{4}{2}}{\binom{6}{2}} \right) \frac{3}{5}= \\
 & =\left( \frac{3}{15}+\frac{3}{15} \right) \frac{2}{5}+\left( \frac{1}{15}+\frac{6}{15} \right) \frac{3}{5}= \\
 & =\frac{6}{15} \frac{2}{5}+\frac{7}{5} \frac{3}{5}=\frac{12+21}{75}=\frac{33}{75}=\frac{11}{25}
\end{array}$$

## Esercizio 3
Sia $k\geq1$ un numero intero arbitrariamente fissato. Consideriamo la seguente densità congiunta discreta:$$p_{X_{1},X_{2}}(x_{1},x_{2})=\left( \frac{1}{4} \right)^{1-k}\left( \frac{1}{2} \right)^{x_{1}+x_{2}}\quad\quad\text{per }x_{1},x_{2}\geq k\text{ interi}$$
1) Calcolare $P(X_2 = 2X_1)$.
2) Calcolare $P(\{X_1 = k\}\cap\{X_2=k+1\}|X_1+X_2=2k+1)$, verificando che il risultato non dipende da $k$.

#### Soluzione
1) Si ha $$\begin{array}{l}
P(X_{2}=2X_{1}) & =\displaystyle\sum_{h\geq k}p_{X_{1},X_{2}}(h,2h)=\sum_{h\geq k}\left(\frac{1}{4}\right)^{1-k}\left(\frac{1}{2}\right)^{h+2h}= \\
 & =\displaystyle\left( \frac{1}{4} \right)^{1-k}\sum_{h\geq k}\left( \frac{1}{8} \right)^{h}=\left( \frac{1}{4} \right)^{1-k} \frac{\left( \frac{1}{8} \right)^{k}}{1- \frac{1}{8}}= \\
 & =\frac{1}{4} \frac{8}{7}\left( \frac{1}{2} \right)^{k}=\frac{2}{7}\left( \frac{1}{2} \right)^{k}
\end{array}$$
2) Osserviamo che $$\{X_{1}=k\}\cap\{X_{2}=k+1\}\subset\{X_{1}+X_{2}=2k+1\}$$ e $$\{X_{1}+X_{2}=2k+1\}=(\{X_{1}=k\}\cap\{X_{2}=k+1\})\cup(\{X_{1}=k+1\}\cap \{X_{2}=k\})$$ed è una unione disgiunta. Quindi la probabilità condizionata richiesta è uguale a $$\begin{array}{}
\displaystyle\frac{p_{X_{1},X_{2}}(k,k+1)}{p_{X_{1},X_{2}}(k,k+1)+p_{X_{1},X_{2}}(k+1,k)}=\frac{\left(\frac{1}{4}\right)^{1-k}\left(\frac{1}{2}\right)^{2k+1}}{\left( \frac{1}{4} \right)^{1-k}\left( \frac{1}{2} \right)^{2k+1}+\left( \frac{1}{4} \right)^{1-k}\left( \frac{1}{2} \right)^{2k+1}}= \\
\displaystyle=\frac{\left( \frac{1}{4} \right)^{1-k}\left( \frac{1}{2} \right)^{ 2k+1}}{2\left( \frac{1}{4} \right)^{1-k}\left( \frac{1}{2} \right)^{2k+1}}=\frac{1}{2}
\end{array}$$e non dipende da $k$.


## Esercizio 4
Siano $a, b > 0$ con $a < b$ arbitrariamente fissati. Sia $X$ una variabile aleatoria con distribuzione uniforme su $(a^4,\ b^4)$.
1) Trovare la densità continua della variabile aleatoria $Y=\sqrt{X}$.
2) Sia m la mediana di $Y$ , cioè il valore $m$ per cui $F_Y(m)=\frac{1}{2}$ ; verificare che $m=\sqrt{\frac{a^{4}+b^{4}}{2}}$ .

#### Soluzione
1) Si ha $P(a^{2}\leq Y\leq b^{2})=1$ e quindi $$F_{Y}(y)=\begin{cases}
0 & \text{se }y\leq a^{2} \\
(*) & \text{se }a^{2}<y<b^{2} \\
1 & \text{se }y\geq b^{2}
\end{cases}$$
Per $y\in(a^{2},\ b^{2})$ si ha $$(*)=P(\sqrt{X}\leq y)=P(X\leq y^{2})=\displaystyle\int_{a^{4}}^{y^{2}}{\frac{1}{b^{4}-a^{4}}}\,dx=\left[\frac{x}{b^{4}-a^{4}}\right]_{x=a^{4}}^{x=y^{2}}=\frac{y^{2}-a^{4}}{b^{4}-a^{4}}$$
Quindi la densità richiesta è $$f_{Y}(y)=\frac{2y}{b^{4}-a^{4}}1_{(a^{2},\ b^{2})}(y)$$
2) Tenendo conto dell’espressione di $F_Y(y)$ calcolata prima, si ha l’equazione $$\frac{m^{2}-a^{4}}{b^{4}-a^{4}}=\frac{1}{2}$$
   da cui segue $m^{2}=a^{4}+\frac{b^{4}-a^{4}}{2}=\frac{2a^{4}+b^{4}-a^{4}}{2}=\frac{a^{4}+b^{4}}{2}$, e quindi $m=\sqrt{\frac{a^{4}+b^{4}}{2}}$

## Esercizio 5
Poniamo $\Phi(y)=\frac{1}{\sqrt{2\pi}}\displaystyle\int_{-\infty}^{y}e^{-\frac{x^{2}}{2}}\,dx$
1) Sia $X$ una variabile aleatoria Normale con media 1 e varianza 4. Trovare il valore di $z_{1}$ per cui si ha $P(1\leq X\leq z_{1})=\Phi(3/2) − 1/2$
   
2) Sia $\{X_{n}: n ≥ 1\}$ una successione di variabili aleatorie i.i.d. con media 1 e varianza 16. Dire per quale valore di $z_{2}$ si ha $$\displaystyle\lim_{n\to\infty}P\left(\frac{X_{1}+\dots+X_{n}}{n}-1> \frac{z_{2}}{\sqrt{n}}\right)=1-\Phi\left(\frac{1}{8}\right)$$

#### Soluzione
1) Ricordando che $\Phi(0)=\frac{1}{2}$, si ha $$P(1\leq X\leq z_{1})=\Phi\left( \frac{z_{1}-1}{\sqrt{4}} \right)-\Phi\left( \frac{1-1}{\sqrt{4}} \right)=\Phi\left( \frac{z_{1}-1}{2} \right)-\frac{1}{2}$$e quindi $$\Phi\left( \frac{3}{2} \right)-\frac{1}{2}=\Phi\left( \frac{z_{1}-1}{2} \right)-\frac{1}{2}$$
   da cui segue (poiché $\Phi$ è invertibile) $z_{1}-1=3$, e cioè $z_{1}=4$
   
2) Dividendo membro a membro per $\displaystyle\frac{\sqrt{16}}{\sqrt{n}}$ si ha $$\left\{ \frac{X_{1}+\dots+X_{n}}{n}-1> \frac{z_{2}}{\sqrt{n}} \right\}=\left\{ \frac{\frac{X_{1}+\dots+X_{n}}{n}-1}{\frac{\sqrt{16}}{\sqrt{n}}}> \frac{z_{2}}{\sqrt{16}} \right\}$$
   allora per il Teorema Limite Centrale e per la condizione imposta dal testo dell'esercizio si deve avere l'uguaglianza $$1-\Phi\left( \frac{z_{2}}{\sqrt{16}} \right)=1-\Phi\left( \frac{1}{8} \right)$$
   da cui segue (poiché $\Phi$ è invertibile) $\frac{z_{2}}{\sqrt{16}}=\frac{1}{8}$, e cioè $z_{2}=\frac{\sqrt{16}}{8}=\frac{4}{8}=\frac{1}{2}$