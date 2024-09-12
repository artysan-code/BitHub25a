## Esercizio 1
Un’urna ha 4 palline con in numeri 0, 1, 2, 3. Si estraggono a caso 2 palline in blocco. 
1) Calcolare la probabilità di estrarre un numero pari e un numero dispari in un qualsiasi ordine. 
2) Trovare la densità della variabile aleatoria $X$ che indica il prodotto dei due numeri estratti. 
3) Si ripeta più volte il procedimento indicato fino a quando viene estratto per la prima volta l’insieme di numeri $\{1,\ 2\}$. Calcolare la probabilità che il procedimento venga ripetuto un numero pari di volte (due volte, quattro volte, sei volte, ecc.).

### Soluzione
1) La probabilità richiesta è $\displaystyle\frac{\binom{2}{1}\binom{2}{1}}{\binom{4}{2}}=\frac{2\cdot 2}{6}=\frac{2}{3}$
2) Ciascuno dei 6 sottoinsiemi $\{0,1\},\{0,2\},\{0,3\},\{1,2\},\{1,3\},\{2,3\}$ ha probabilità $\frac{1}{6}$ di essere estratto. Quindi $$\begin{cases}
p_{X}(0)= P(\{0,1\},\{0,2\},\{0,3\})=\frac{3}{6}=\frac{1}{2} \\
p_{X}(2)= P(\{1,2\})=\frac{1}{6} \\
p_{X}(3)= P(\{1,3\})=\frac{1}{6} \\
p_{X}(6)= P(\{2,3\})=\frac{1}{6}
\end{cases}$$
3) La probabilità richiesta fa riferimento ad una distribuzione geometrica traslata di parametro $p=P(\{1,2\})=\frac{1}{6}$. Si ha $$\begin{array}{}
\displaystyle\sum_{h\geq 1}(1-p)^{2h-1}p=\frac{p}{1-p} \frac{(1-p)^{2}}{1-(1-p)^{2}}=\frac{p(1-p)}{1-(1-2p-p^{2})}= \\
\displaystyle=\frac{1-p}{2-p} =\frac{1-\frac{1}{6}}{2-\frac{1}{6}}=\frac{\frac{5}{6}}{\frac{11}{6}}=\frac{5}{11}
\end{array}$$

## Esercizio 2
Si lancia un dado equo. Se esce il numero 1 si lanciano due monete eque, se esce un numero diverso da 1 si lanciano due monete le cui probabilità che esca testa lanciandole è uguale a $\frac{1}{3}$. 
1) Calcolare la probabilità che sia uscito il numero 1 nel lancio del dado sapendo di aver ottenuto due teste nei due lanci di moneta

### Soluzione
1) Con notazioni ovvie viene chiesto di calcolare una probabilità condizionata $P(U|T)$. Per la formula di Bayes (e la formula delle probabilità totali per $P(T)$) si ha $$P(U|T)=\frac{P(T|U)P(U)}{P(T)}=\frac{\left(\frac{1}{2}\right)\left(\frac{1}{2}\right)\left(\frac{1}{6}\right)}{\left(\frac{1}{2}\right)\left(\frac{1}{2}\right)\left(\frac{1}{6}\right)+\left(\frac{1}{3}\right)\left(\frac{1}{3}\right)\left(\frac{5}{6}\right)}=\frac{\frac{1}{24}}{\frac{1}{24}+\frac{5}{54}}=\dots=\frac{9}{29}$$

## Esercizio 3
Siano $q,r\in(0, 1)$ arbitrariamente fissati. Consideriamo la seguente densità congiunta discreta: $$\begin{array}{l}
\displaystyle p_{X_{1},X_{2}}(k,k)=\frac{1}{2}q^{k}(1-q) & \text{ per }k\geq 0\text{ intero} \\
\displaystyle p_{X_{1},X_{2}}(h,3h)=\frac{1}{2}(1-r)^{h-1}r & \text{ per }h\geq 1
 \text{ intero}
\end{array}$$
1) Calcolare $P(X_1 = X_2)$ e verificare che non dipende da $q$ e $r$.
2) Verificare che $P(X_{1}=3|X_{2}=3)=\frac{q^{3}(1-q)}{q^{3}(1-q)+r}$

### Soluzione
1) Si ha $$P(X_{1}=X_{2})=\sum_{k\geq 0}p_{X_{1},X_{2}}(k,k)=\frac{1-q}{2}\sum_{k\geq 0}q^{k}=\frac{1-q}{2}\frac{q^{0}}{1-q}=\frac{1}{2}$$
2) Si ha $$\begin{array}{c}
 P(X_{1}=3|X_{2}=3) & \displaystyle=\frac{P(\{X_{1}=3\}\cap\{X_{2}=3\})}{P(X_{2}=3)}= \\
 & \displaystyle=\frac{p_{X_{1},X_{2}}(3,3)}{p_{X_{1},X_{2}}(3,3)+p_{X_{1},X_{2}}(1,3)}= \\
 & \displaystyle=\frac{\frac{1}{2}q^{3}(1-q)}{\frac{1}{2}q^{3}(1-q)+\frac{1}{2}(1-r)^{1-1}r}= \\
 & \displaystyle=\frac{q^{3}(1-q)}{q^{3}(1-q)+r}
\end{array}$$

## Esercizio 4
Sia $a>e$ arbitrariamente fissato. Inoltre sia $X$ una variabile aleatoria con densità continua $\displaystyle f_X(x)=\frac{2x}{a^{2}-e^{2}}1_{(e,a)}(x)$
1) Trovare la funzione di distribuzione di $Y=\log X$
2) Verificare che $\displaystyle\mathbb{E}[e^{-2Y}]=\frac{2\log a-1}{a^{2}-e^{2}}$

### Soluzione
1) Si ha $P(1\leq Y\leq\log a)=1$ e quindi $$F_{Y}(y)=\begin{cases}
0 & \text{ se }y\leq 1\\
(*) & \text{ se } 1\leq t\leq \log a\\
1 & \text{ se }y\geq \log a
\end{cases}$$
   Per $y\in(1,\log a)$ si ha $$\begin{array}{}
(*)=P(\log X\leq y)=P(X\leq e^{y})=\displaystyle\int^{e^{y}}_{e} \frac{2x}{a^{2}-e^{2}}\,dx= \\
=\displaystyle\left[\frac{x^{2}}{a^{2}-e^{2}}\right]_{x=e}^{x=e^{y}}=\frac{e^{2y}-e^{2}}{a^{2}-e^{2}}
\end{array}$$
2) A partire dalla risposta precedente si ha che $f_{Y}(y)=\frac{2e^{2y}}{a^{2}-e^{2}}1_{(1,\log a)}(y)$. Quindi $$\displaystyle\mathbb{E}[e^{-2y}]=\int_{1}^{\log a} e^{-2y} \frac{2e^{2y}}{a^{2}-e^{2}}\, dy= \frac{2}{a^{2}-e^{2}}\int_{1}^{\log a}\,dy= \frac{2}{a^{2}-e^{2}}[y]_{y=1}^{y=\log a}=\frac{2(\log a-1)}{a^{2}-e^{2}}$$
   #### Osservazione
   In realtà non serve fare riferimento alla risposta precedente osservando che $e^{-2Y}=e^{-2\log X}=X^{-2}$. Infatti si ha $$\begin{array}{r}
\displaystyle\mathbb{E}[e^{-2Y}]=\mathbb{E}[X^{-2}]=\int_{e}^{a}x^{-2} \frac{2x}{a^{2}-e^{2}}\,dx= \frac{2}{a^{2}-e^{2}} \int_{e}^{a}x^{-1}\,dx= \\
\displaystyle=\frac{2}{a^{2}-e^{2}}[\log x]_{x=e}^{x=a}=\frac{2(\log a-1)}{a^{2}-e^{2}}
\end{array}$$

## Esercizio 5
Poniamo $\displaystyle\Phi(y)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{y}e^{- \frac{x^{2}}{2}}\,dx$. 
Sia $X$ una variabile aleatoria Normale con media 2 e varianza 9.
1) Calcolare $P(1<X<5)$ esprimendo il risultato con la funzione $\Phi$ con argomenti positivi   
Siano $X_{1},\dots,X_{400}$ variabili aleatorie i.i.d. con media 6 e varianza 4.
2) Calcolare $P(X_{1}+\dots+X_{400}<2390)$ con l'approssimazione Normale esprimendo il risultato con la funzione $\Phi$ con argomenti positivi.
### Soluzione
1) La standardizzata di $X$ è $X^*=\frac{X-2}{\sqrt{9}}=\frac{X-2}{3}$; quindi si ha $$\begin{array}{r}
P(1<X<5)=P\left( \frac{1-2}{3}<\frac{X-2}{3}<\frac{5-2}{3} \right)=P\left( -\frac{1}{3}<X^{*}<1 \right)= \\
=\Phi(1)-\Phi\left( -\frac{1}{3} \right)=\Phi(1)-\left( 1-\Phi\left( \frac{1}{3} \right) \right)=\Phi(1)+\Phi\left( \frac{1}{3} \right)-1
\end{array}$$
2) Si ha $$\begin{array}{r}
\displaystyle P(X_{1}+\dots+X_{400}<2390)=P\left( \frac{X_{1}+\dots+X_{400}-6\cdot 400}{\sqrt{4}\sqrt{400}}< \frac{2390-6\cdot 400}{\sqrt{4}\sqrt{400}} \right)\approx \\
\displaystyle\approx\Phi\left( -\frac{10}{40} \right)=1-\Phi\left( \frac{1}{4} \right)
\end{array}$$
