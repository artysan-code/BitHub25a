# Esercizi su densità continue
Due esercizi tipo: determinare la costante di normalizzazione di una densità e calcolare probabilità sfruttando simmetria e aree.
## Esercizio 1 (parabola su $(0,1)$)
Sia $X$ una v.a. continua con densità continua $f_{X}(x)=cx(1-x)1_{(0,1)}(x)$, dove $c>0$ è una costante di normalizzazione. Trovare il valore di $c$.
Si deve trovare $c$ per cui $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$: $$1=\underset{=0}{\underbrace{\int_{-\infty}^{0}f_{X}(x)\,dx}}+\int_{0}^{1}f_{X}(x)\,dx+\underset{=0}{\underbrace{\int_{1}^{\infty}f_{X}(x)\,dx}}=\int_{0}^{1}cx(1-x)\,dx=c\int_{0}^{1}(x-x^{2})\,dx=c\left[ \frac{x^{2}}{2}-\frac{x^{3}}{3} \right]_{x=0}^{x=1}=c\left( \frac{1}{2}-\frac{1}{3} \right)=c\frac{3-2}{6}=\frac{c}{6}$$Quindi si ha $\frac{c}{6}=1$, da cui segue $\begin{bmatrix}c=6\end{bmatrix}$.
> [!info] Interpretazione
> La densità è una parabola ristretta su $[0,1]$, con la concavità verso il basso, che si annulla in $x=0$ e $x=1$. La costante $c>0$ è scelta in modo che l'area sottesa sia uguale a 1.

## Esercizio 2 (densità triangolare $b|t|$)
Sia $X$ una v.a. continua con densità $f_{X}(t)=b|t|\,1_{(-a,a)}(t)$, per $a,b>0$.
1. Dire quanto vale la costante di normalizzazione $b$ come funzione di $a$.
2. Verificare che in ogni caso $P(X>0)=\frac{1}{2}$.
3. Calcolare $P\left( X>\frac{1}{2} \right)$ per $a=1$.

### 1) La costante di normalizzazione
Si deve avere $\int_{-\infty}^{\infty}f_{X}(t)\,dt=1$. Allora $$1=\underset{=0}{\underbrace{\int_{-\infty}^{-a}f_{X}}}+\int_{-a}^{a}f_{X}(t)\,dt+\underset{=0}{\underbrace{\int_{a}^{\infty}f_{X}}}=\int_{-a}^{a}b|t|\,dt=b\left( \int_{-a}^{0}\underset{=-t}{\underbrace{|t|}}\,dt+\int_{0}^{a}\underset{=t}{\underbrace{|t|}}\,dt \right)=b\left( -\left[ \frac{t^{2}}{2} \right]_{-a}^{0}+\left[ \frac{t^{2}}{2} \right]_{0}^{a} \right)=b\left( \frac{a^{2}}{2}+\frac{a^{2}}{2} \right)=ba^{2}$$da cui segue $\begin{bmatrix}b=\dfrac{1}{a^{2}}\end{bmatrix}$.
> [!info] Procedimento alternativo (simmetria)
> Poiché $|t|$ è una funzione **pari** ($|t|=|-t|$) e l'intervallo $(-a,a)$ è simmetrico rispetto all'origine, l'integrale su $(-a,a)$ è il doppio di quello su $(0,a)$: $$b\int_{-a}^{a}|t|\,dt=2b\int_{0}^{a}t\,dt=2b\left[ \frac{t^{2}}{2} \right]_{0}^{a}=ba^{2}$$e imponendo $=1$ si ritrova $b=\frac{1}{a^{2}}$ (l'area dei due triangoli è il doppio dell'area del triangolo di destra).

> [!info] Commento su $b=1/a^{2}$
> Non sorprende che $b$ sia **grande per $a$ piccolo** e **piccolo per $a$ grande**: il grafico di $f_{X}$ è formato da due triangoli e l'area totale deve restare uguale a 1, quindi se la base si stringe l'altezza deve crescere (e viceversa).

### 2) $P(X>0)=\frac{1}{2}$
$$P(X>0)=\int_{0}^{\infty}f_{X}(t)\,dt=\int_{0}^{a}\underset{=\frac{1}{a^{2}}|t|=\frac{t}{a^{2}}}{\underbrace{f_{X}(t)}}\,dt+\underset{=0}{\underbrace{\int_{a}^{\infty}f_{X}}}=\frac{1}{a^{2}}\left[ \frac{t^{2}}{2} \right]_{0}^{a}=\frac{1}{a^{2}}\cdot \frac{a^{2}}{2}=\frac{1}{2}$$Qualunque sia $a$, il grafico di $f_{X}$ è costituito da due triangoli rettangoli con la stessa area, la cui somma è 1; quindi $P(X>0)$ è l'area del "triangolo di destra", cioè $\frac{1}{2}$.
### 3) $P\left( X>\frac{1}{2} \right)$ per $a=1$
Essendo $a=1$ si ha $b=\frac{1}{a^{2}}=\frac{1}{1^{2}}=1$ (i due triangoli sono isosceli). Allora $$P\left( X>\frac{1}{2} \right)=\int_{1/2}^{\infty}f_{X}(t)\,dt=\int_{1/2}^{1}\underset{=t}{\underbrace{|t|}}\,dt+\underset{=0}{\underbrace{\int_{1}^{\infty}0\,dt}}=\int_{1/2}^{1}t\,dt=\left[ \frac{t^{2}}{2} \right]_{t=1/2}^{t=1}=\frac{1}{2}\left( 1^{2}-\left( \frac{1}{2} \right)^{2} \right)=\frac{1}{2}\left( 1-\frac{1}{4} \right)=\frac{1}{2}\cdot \frac{3}{4}=\frac{3}{8}$$

--- Fine lezione 15 ---

---
Nota precedente: [[Distribuzione esponenziale]]. Nota successiva: [[Quantili di una variabile aleatoria continua]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
