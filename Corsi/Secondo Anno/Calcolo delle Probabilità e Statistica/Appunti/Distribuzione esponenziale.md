# Distribuzione esponenziale
Distribuzione notevole continua su $(0,\infty)$, caratterizzata dalla proprietà di mancanza di memoria e strettamente legata alla geometrica.
## Definizione
Una v.a. $X$ ha **distribuzione esponenziale** di parametro $\lambda>0$ se $$F_{X}(t)=\begin{cases}
1-e^{-\lambda t} & t\geq 0 \\
0 & t<0
\end{cases}$$In simboli scriveremo $X\sim Exp(\lambda)$. Il grafico di $F_{X}$ ha asintoto orizzontale $y=1$.
## Densità
La funzione $F_{X}$ non è derivabile per $t=0$. Negli altri punti lo è e si ha $$F_{X}'(t)=\begin{cases}
\lambda e^{-\lambda t} & t>0 \\
0 & \text{altrimenti (per }t<0)
\end{cases}$$Quindi possiamo dire ad esempio che $$f_{X}(t)=\begin{cases}
\lambda e^{-\lambda t} & t>0 \\
0 & \text{altrimenti}
\end{cases}=\begin{bmatrix}\lambda e^{-\lambda t}1_{(0,\infty)}(t)\end{bmatrix}$$(per la [[Variabili aleatorie continue#Non unicità della densità (esempio)|non unicità della densità]] si poteva anche usare $t\geq 0$ e $1_{[0,\infty)}$).
### Verifica della normalizzazione
Verifichiamo che $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$ (quindi $\lambda$ può essere vista come una costante di normalizzazione): $$\int_{-\infty}^{\infty}f_{X}(x)\,dx=\underset{=0}{\underbrace{\int_{-\infty}^{0}f_{X}(x)\,dx}}+\int_{0}^{\infty}\lambda e^{-\lambda x}\,dx=[-e^{-\lambda x}]_{x=0}^{x=\infty}=-\underset{=0}{\underbrace{e^{-\infty}}}-(-\underset{=1}{\underbrace{e^{0}}})=0+1=1$$(con abuso di notazione per $x=\infty$).
## Proprietà di mancanza di memoria
> [!quote] Mancanza di memoria
> Sia $X\sim Exp(\lambda)$. Allora $$\begin{bmatrix}P(X>t+s\mid X>s)=P(X>t)\qquad\forall\ t,s>0\end{bmatrix}$$

> [!info] Interpretazione
> Se $X$ rappresenta un **tempo di funzionamento**: dato che c'è funzionamento al tempo $s$, la probabilità di funzionare per un ulteriore tempo $t$ è la stessa che si avrebbe all'inizio (contando il tempo $t$ da zero). Quindi ci si può "dimenticare" che è trascorso il tempo $s$.

### Dimostrazione
Osserviamo che, per $\tau>0$, $$P(X>\tau)=1-\underset{=1-e^{-\lambda\tau}}{\underbrace{P(X\leq\tau)}}=e^{-\lambda\tau}$$Allora $$P(X>t+s\mid X>s)=\frac{P(\{X>t+s\}\cap\{X>s\})}{P(X>s)}\overset{(\star)}{=}\frac{P(X>t+s)}{P(X>s)}=\frac{e^{-\lambda(t+s)}}{e^{-\lambda s}}=e^{-\lambda t}=P(X>t)\qquad\Box$$dove in $(\star)$ si è usato $\{X>t+s\}\subseteq\{X>s\}$ (con $t,s>0$), quindi $\{X>t+s\}\cap\{X>s\}=\{X>t+s\}$.
> [!info] Caratterizzazione
> La distribuzione esponenziale è l'**unica** distribuzione continua su $(0,\infty)$ che soddisfa la proprietà di mancanza di memoria.

## Legame con la geometrica (parte intera)
Sia $X\sim Exp(\lambda)$ e poniamo $Y=[X]$, dove $[x]=\max\{k\in \mathbb{Z}:k\leq x\}$ è la "parte intera di $x$". Quindi $Y$ assume valori in un insieme al più numerabile. Troviamo la densità discreta di $Y$.
Per ogni $k\in \mathbb{Z}$ si ha $\{Y=k\}=\{k\leq X<k+1\}$ (vale anche se $X$ avesse una distribuzione diversa). Allora, per ogni $k\in \mathbb{Z}$, $$P_{Y}(k)=P(k\leq X<k+1)=\int_{k}^{k+1}f_{X}(x)\,dx=\begin{cases}
0 & k\leq -1 \\
\displaystyle\int_{k}^{k+1}\lambda e^{-\lambda x}\,dx=[-e^{-\lambda x}]_{x=k}^{x=k+1}=e^{-\lambda k}-e^{-\lambda(k+1)} & k\geq 0
\end{cases}$$In conclusione $$P_{Y}(k)=e^{-\lambda k}-e^{-\lambda(k+1)}\qquad\forall\ k\geq 0\text{ intero}$$
> [!quote] $Y=[X]$ è geometrica
> Se poniamo $p=1-e^{-\lambda}$, si ha $1-p=e^{-\lambda}$; quindi $$P_{Y}(k)=e^{-\lambda k}(1-e^{-\lambda})=(1-p)^{k}p\qquad\forall\ k\geq 0$$cioè $Y\sim Geo(p=1-e^{-\lambda})$. In altri termini $$X\sim Exp(\lambda)\ (\text{mancanza di memoria})\implies [X]\sim Geo(p=1-e^{-\lambda})\ (\text{mancanza di memoria})$$

Il legame conserva la [[Distribuzione geometrica|mancanza di memoria]]: la geometrica è la controparte discreta dell'esponenziale.

--- Fine parte sulla distribuzione esponenziale (lezione 15, pp. 13-18) ---

---
Nota precedente: [[Distribuzione uniforme continua]]. Nota successiva: [[Esercizi su densità continue]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
