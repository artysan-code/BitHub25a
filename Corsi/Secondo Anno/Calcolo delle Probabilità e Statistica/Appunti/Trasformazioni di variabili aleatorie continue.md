# Trasformazioni di variabili aleatorie continue
Come ottenere la densità di $Y=f(X)$ quando $X$ è continua: non c'è una formula generale, ma il caso di $f$ affine non costante si tratta una volta per tutte.
## Impostazione
Si fa riferimento al caso in cui si hanno v.a. $Y$ del tipo $Y=f(X)$, dove
- $X$ è una v.a. continua;
- $f:D\subseteq \mathbb{R}\to \mathbb{R}$ per qualche insieme $D$ (dominio della funzione).

In generale, a differenza di quel che accade quando $X$ è discreta, la $Y$ è una v.a. (cioè $\{w\in\ohm:Y(w)\leq t\}\in\mathcal{A}$ per ogni $t\in \mathbb{R}$) solo se $f$ soddisfa certe proprietà. Questo aspetto va oltre gli scopi del corso; nei casi che tratteremo la funzione $f$ avrà sempre le proprietà richieste affinché $Y$ sia una v.a.
> [!warning] $Y=f(X)$ può non essere continua
> **Esempio 1** ($f$ costante): $f(x)=c$ per ogni $x$. Allora $Y=c$ è una v.a. **discreta** ($\delta_{Y}=\{c\}$, $P_{Y}(y)=1$ se $y=c$, $0$ altrimenti).
> **Esempio 2** ($f$ parte intera): $f(x)=[x]$. Allora $Y=[X]$ è **discreta** ($\delta_{Y}\subseteq \mathbb{Z}$, $P_{Y}(y)=P(y\leq X<y+1)$ se $y\in \mathbb{Z}$).

Una casistica degli esercizi proposti farà riferimento al caso in cui $Y$ è **continua** e si deve trovare la densità $f_{Y}$ (che dipenderà da $f$ e da $f_{X}$).
> [!info] Nessuna formula generale
> Non presenteremo una formula generale per ottenere $f_{Y}$ da $f$ e $f_{X}$. L'unico caso che tratteremo in generale è quello di $f$ **affine** ($f(x)=ax+b$), escludendo $a=0$ (altrimenti $f$ sarebbe costante). Per evitare esercizi troppo complicati, in generale $f$ sarà **monotona** su un sottoinsieme $S$ di $D$ con $P(X\in S)=1$, oppure avrà proprietà di simmetria (si veda [[Trasformazioni monotone di variabili aleatorie continue|il procedimento caso per caso]]).

## Il caso di funzione affine non costante
Sia $f(x)=ax+b$ con $a,b\in \mathbb{R}$ tale che $a\neq 0$. Studiamo la funzione di distribuzione di $Y=f(X)$: $$F_{Y}(y)=P(Y\leq y)=P(aX+b\leq y)=P(aX\leq y-b)=\begin{cases}
P\left( X\leq \dfrac{y-b}{a} \right)=F_{X}\left( \dfrac{y-b}{a} \right) & \text{se }a>0 \\[3mm]
P\left( X\geq \dfrac{y-b}{a} \right)=1-F_{X}\left( \dfrac{y-b}{a} \right) & \text{se }a<0
\end{cases}$$Nel caso $a<0$ si è diviso per $a<0$ (il verso della disuguaglianza si inverte) e si è usato che $X$ è continua, quindi $P\left( X\geq \frac{y-b}{a} \right)=P\left( X>\frac{y-b}{a} \right)=1-F_{X}\left( \frac{y-b}{a} \right)$.
Allora possiamo concludere derivando membro a membro rispetto a $y$: $$f_{Y}(y)=\begin{cases}
f_{X}\left( \dfrac{y-b}{a} \right)\cdot \dfrac{1}{a} & \text{se }a>0 \\[3mm]
-f_{X}\left( \dfrac{y-b}{a} \right)\cdot \dfrac{1}{a} & \text{se }a<0
\end{cases}=\begin{bmatrix}\dfrac{1}{|a|}f_{X}\left( \dfrac{y-b}{a} \right)\end{bmatrix}$$
## Esercizio (una trasformazione affine di un'uniforme resta uniforme)
Sia $X\sim U(0,1)$ e sia $Y=aX+b$ con $a\neq 0$. Verificare che $Y\sim U(b,a+b)$ se $a>0$, e $Y\sim U(a+b,b)$ se $a<0$.
Si ha $f_{X}(x)=\frac{1}{1-0}1_{(0,1)}(x)=1_{(0,1)}(x)$. Con la formula precedente $$f_{Y}(y)=\frac{1}{|a|}f_{X}\left( \frac{y-b}{a} \right)=\frac{1}{|a|}1_{(0,1)}\left( \frac{y-b}{a} \right)$$Dobbiamo studiare la condizione $\frac{y-b}{a}\in(0,1)$ per capire com'è fatta $1_{(0,1)}\left( \frac{y-b}{a} \right)$:
- **se $a>0$**: $0<\frac{y-b}{a}<1\iff 0<y-b<a\iff b<y<a+b$, quindi $$f_{Y}(y)=\frac{1}{a}1_{(b,a+b)}(y)=\frac{1}{(a+b)-b}1_{(b,a+b)}(y)\implies Y\sim U(b,a+b)$$
- **se $a<0$**: $0<\frac{y-b}{a}<1\iff 0>y-b>a\iff b>y>a+b$, quindi $$f_{Y}(y)=\frac{1}{-a}1_{(a+b,b)}(y)=\frac{1}{b-(a+b)}1_{(a+b,b)}(y)\implies Y\sim U(a+b,b)$$

## Esercizio ($Y=\frac{\pi}{2}-X$)
Sia $X$ una v.a. con densità continua $f_{X}(x)=\sin x\cdot 1_{(0,\pi/2)}(x)$. Trovare la densità continua di $Y=\frac{\pi}{2}-X$.
È il caso con $a=-1$ e $b=\frac{\pi}{2}$. Quindi $$f_{Y}(y)=\frac{1}{|-1|}f_{X}\left( \frac{y-\frac{\pi}{2}}{-1} \right)=f_{X}\left( \frac{\pi}{2}-y \right)=\sin\left( \frac{\pi}{2}-y \right)1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)=\cos y\cdot 1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)$$(si è usato $\sin\left( \frac{\pi}{2}-y \right)=\cos y$). Studiamo la funzione $1_{(0,\pi/2)}\left( \frac{\pi}{2}-y \right)$: $$0<\frac{\pi}{2}-y<\frac{\pi}{2}\iff 0>y-\frac{\pi}{2}>-\frac{\pi}{2}\iff \frac{\pi}{2}>y>0$$Quindi $$\begin{bmatrix}f_{Y}(y)=\cos y\cdot 1_{(0,\pi/2)}(y)\end{bmatrix}$$

--- Fine parte sulle trasformazioni affini (lezione 16, pp. 4-10) ---

---
Nota precedente: [[Quantili di una variabile aleatoria continua]]. Nota successiva: [[Trasformazioni monotone di variabili aleatorie continue]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
