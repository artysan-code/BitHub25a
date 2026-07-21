# Covarianza di variabili aleatorie discrete
Varianza di una somma, definizione di covarianza, formule di calcolo, interpretazione geometrica ed esercizio riassuntivo.
## Varianza di una somma e introduzione alla covarianza
Si vuole dare una formula per $\text{Var}[X_{1}+X_{2}]$, dove entrambe le v.a. sono **non costanti** (se ad esempio $X_{2}$ fosse costante, per quanto [[Varianza e momenti di una variabile aleatoria discreta#3) $\text{Var}[X+a]=\text{Var}[X]$ (per $a\in \mathbb{R}$)|visto in precedenza]] si avrebbe $\text{Var}[X_{1}]$). Si ha $$\begin{array}{ll}
\text{Var}[X_{1}+X_{2}] & =\mathbb{E}[(X_{1}+X_{2}-\underset{=\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]}{\underbrace{\mathbb{E}[X_{1}+X_{2}]}})^{2}]=\mathbb{E}[(\underset{\text{quadrato di binomio}}{\underbrace{(X_{1}-\mathbb{E}[X_{1}])+(X_{2}-\mathbb{E}[X_{2}])}})^{2}] \\
 & \overset{\text{lin.}}{=}\underset{=\text{Var}[X_{1}]}{\underbrace{\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])^{2}]}}+\underset{=\text{Var}[X_{2}]}{\underbrace{\mathbb{E}[(X_{2}-\mathbb{E}[X_{2}])^{2}]}}+2\underset{\overset{\text{def}}{=}\text{Cov}(X_{1},X_{2})}{\underbrace{\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]}}
\end{array}$$dove l'ultimo termine è per definizione la **covarianza** tra $X_{1}$ e $X_{2}$. Quindi $$\begin{bmatrix}
\text{Var}[X_{1}+X_{2}]=\text{Var}[X_{1}]+\text{Var}[X_{2}]+2\text{Cov}(X_{1},X_{2})
\end{bmatrix}$$
> [!info] Analogia
> La struttura ricalca il **quadrato di binomio** $(a+b)^{2}=a^{2}+b^{2}+2ab$.

Si ha una formula più generale nel caso di $m$ addendi: $$\text{Var}[X_{1}+\dots+X_{m}]=\sum_{i=1}^{m}\text{Var}[X_{i}]+2\underset{i<j}{\sum_{i,j=1}^{m}}\text{Cov}(X_{i},X_{j})$$(anche perché $\text{Cov}(\cdot,\cdot)$ è simmetrica, come si vede qui di seguito).
## Definizione
La **covarianza** tra due v.a. $X_{1}$ e $X_{2}$ definite su uno stesso spazio di probabilità è (se esiste finita) $$\begin{bmatrix}
\text{Cov}(X_{1},X_{2})=\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]
\end{bmatrix}$$
## Alcune formule per la covarianza
Valgono non solo per il caso discreto.
### 1) Formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$
$$\begin{array}{ll}
\text{Cov}(X_{1},X_{2}) & =\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]=\mathbb{E}[X_{1}X_{2}-X_{1}\mathbb{E}[X_{2}]-X_{2}\mathbb{E}[X_{1}]+\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]] \\
 & \overset{\text{lin.}}{=}\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]+\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\begin{bmatrix}\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]\end{bmatrix}
\end{array}$$
### 2) Simmetria: $\text{Cov}(X_{1},X_{2})=\text{Cov}(X_{2},X_{1})$
Dalla definizione, essendo il prodotto tra numeri reali commutativo: $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]=\mathbb{E}[(X_{2}-\mathbb{E}[X_{2}])(X_{1}-\mathbb{E}[X_{1}])]=\text{Cov}(X_{2},X_{1})$$oppure, con la formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\mathbb{E}[X_{2}X_{1}]-\mathbb{E}[X_{2}]\mathbb{E}[X_{1}]=\text{Cov}(X_{2},X_{1})$.
### 3) $\text{Cov}(X,X)=\text{Var}[X]$
$$\text{Cov}(X,X)=\mathbb{E}[(X-\mathbb{E}[X])(X-\mathbb{E}[X])]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\text{Var}[X]$$oppure, con la formula alternativa: $\text{Cov}(X,X)=\mathbb{E}[X\cdot X]-\mathbb{E}[X]\cdot \mathbb{E}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=\text{Var}[X]$.
> [!info] Estensioni
> Si potrebbero dare altre formule per espressioni del tipo $\text{Cov}(a_{1}X_{1}+b_{1},a_{2}X_{2}+b_{2})$, con $a_{1},a_{2},b_{1},b_{2}\in \mathbb{R}$ costanti.

> [!warning] La covarianza può essere negativa
> A differenza della varianza, la covarianza può assumere **anche valori negativi**.

## Interpretazione geometrica (caso discreto)
Ci limitiamo al caso discreto, anche se ragionamenti simili valgono nel caso generale. Dalla [[#1) Formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$|definizione]] si ha $$\text{Cov}(X_{1},X_{2})=\sum_{x_{1},x_{2}}(x_{1}-\mathbb{E}[X_{1}])(x_{2}-\mathbb{E}[X_{2}])\underset{\geq 0}{\underbrace{P_{X_{1},X_{2}}(x_{1},x_{2})}}$$Sul piano $(x_{1},x_{2})$ le rette $x_{1}=\mathbb{E}[X_{1}]$ e $x_{2}=\mathbb{E}[X_{2}]$ individuano quattro quadranti (numerati $\text{I}^{\circ},\text{II}^{\circ},\text{III}^{\circ},\text{IV}^{\circ}$ in senso antiorario a partire da quello in alto a destra). Poiché la probabilità è $\geq 0$, il segno di ogni addendo dipende dal prodotto $(x_{1}-\mathbb{E}[X_{1}])(x_{2}-\mathbb{E}[X_{2}])$:
- addendi **positivi** $\to$ punti $(x_{1},x_{2})$ nel $\text{I}^{\circ}$ e nel $\text{III}^{\circ}$ quadrante;
- addendi **negativi** $\to$ punti nel $\text{II}^{\circ}$ e nel $\text{IV}^{\circ}$ quadrante;
- addendi **nulli** $\to$ punti sulle due rette.

Quindi $\text{Cov}(X_{1},X_{2})>0$ se gli addendi positivi prevalgono su quelli negativi, $\text{Cov}(X_{1},X_{2})<0$ se si ha il viceversa, e $\text{Cov}(X_{1},X_{2})=0$ se i due contributi si compensano.
## Esercizio (media, varianza e covarianza da una densità congiunta)
Sia $\underline{X}=(X_{1},X_{2})$ una v.a. discreta con la seguente densità congiunta: $$P_{\underline{X}}(0,1)=P_{\underline{X}}(0,2)=P_{\underline{X}}(1,0)=P_{\underline{X}}(2,0)=P_{\underline{X}}(3,0)=\frac{1}{5}$$Calcolare $\mathbb{E}[X_{1}]$, $\mathbb{E}[X_{2}]$, $\text{Var}[X_{1}]$, $\text{Var}[X_{2}]$, $\text{Cov}(X_{1},X_{2})$.
**Densità marginale di $X_{1}$** (si sommano le congiunte a $x_{1}$ fissato): $$\begin{cases}
P_{X_{1}}(0)=P_{\underline{X}}(0,1)+P_{\underline{X}}(0,2)=\frac{1}{5}+\frac{1}{5}=\frac{2}{5} \\
P_{X_{1}}(1)=P_{\underline{X}}(1,0)=\frac{1}{5} \\
P_{X_{1}}(2)=P_{\underline{X}}(2,0)=\frac{1}{5} \\
P_{X_{1}}(3)=P_{\underline{X}}(3,0)=\frac{1}{5}
\end{cases}$$da cui $$\mathbb{E}[X_{1}]=0\cdot \frac{2}{5}+1\cdot \frac{1}{5}+2\cdot \frac{1}{5}+3\cdot \frac{1}{5}=\frac{6}{5}$$ $$\text{Var}[X_{1}]=\mathbb{E}[X_{1}^{2}]-\mathbb{E}^{2}[X_{1}]=0^{2}\cdot \frac{2}{5}+1^{2}\cdot \frac{1}{5}+2^{2}\cdot \frac{1}{5}+3^{2}\cdot \frac{1}{5}-\left( \frac{6}{5} \right)^{2}=\frac{14}{5}-\frac{36}{25}=\frac{70-36}{25}=\frac{34}{25}$$
**Densità marginale di $X_{2}$**: $$\begin{cases}
P_{X_{2}}(0)=P_{\underline{X}}(1,0)+P_{\underline{X}}(2,0)+P_{\underline{X}}(3,0)=\frac{1}{5}+\frac{1}{5}+\frac{1}{5}=\frac{3}{5} \\
P_{X_{2}}(1)=P_{\underline{X}}(0,1)=\frac{1}{5} \\
P_{X_{2}}(2)=P_{\underline{X}}(0,2)=\frac{1}{5}
\end{cases}$$da cui $$\mathbb{E}[X_{2}]=0\cdot \frac{3}{5}+1\cdot \frac{1}{5}+2\cdot \frac{1}{5}=\frac{3}{5}$$ $$\text{Var}[X_{2}]=\mathbb{E}[X_{2}^{2}]-\mathbb{E}^{2}[X_{2}]=0^{2}\cdot \frac{3}{5}+1^{2}\cdot \frac{1}{5}+2^{2}\cdot \frac{1}{5}-\left( \frac{3}{5} \right)^{2}=\frac{5}{5}-\frac{9}{25}=\frac{25-9}{25}=\frac{16}{25}$$
> [!info] Coerenza
> $\text{Var}[X_{2}]<\text{Var}[X_{1}]$ non sorprende: $X_{2}$ assume valori più concentrati ($\{0,1,2\}$) rispetto a $X_{1}$ ($\{0,1,2,3\}$).

**Covarianza.** Con la [[#1) Formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$|formula alternativa]] serve $\mathbb{E}[X_{1}X_{2}]$: $$\mathbb{E}[X_{1}X_{2}]=\sum_{\underline{x}\in \delta_{\underline{X}}}x_{1}x_{2}P_{\underline{X}}(x_{1},x_{2})=0\cdot 1\cdot \frac{1}{5}+0\cdot 2\cdot \frac{1}{5}+1\cdot 0\cdot \frac{1}{5}+2\cdot 0\cdot \frac{1}{5}+3\cdot 0\cdot \frac{1}{5}=0$$(in ogni coppia con probabilità non nulla almeno una tra $x_{1}$ e $x_{2}$ è zero). Allora $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=0-\frac{6}{5}\cdot \frac{3}{5}=\begin{bmatrix}-\frac{18}{25}\end{bmatrix}$$
> [!info] Anticipazione
> Quando si parlerà di **rette di regressione** si potrà dire che $\text{Cov}(X_{1},X_{2})<0$ non sorprende.

--- Fine lezione 13 ---

---
Nota precedente: [[Varianza e momenti di una variabile aleatoria discreta]]. Nota successiva: [[Indipendenza e covarianza]]. Indice del blocco: [[Speranza matematica e momenti]].
