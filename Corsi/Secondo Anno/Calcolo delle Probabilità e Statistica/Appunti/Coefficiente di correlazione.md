# Coefficiente di correlazione
Versione normalizzata della covarianza, sempre compresa tra $-1$ e $1$, che misura il grado di relazione lineare tra due variabili aleatorie.
## Definizione
Siano $X_{1},X_{2}$ due v.a. definite su uno stesso spazio di probabilità, con medie e varianze finite e **non costanti** (quindi $\text{Var}[X_{1}]>0$ e $\text{Var}[X_{2}]>0$). Si definisce **coefficiente di correlazione** tra $X_{1}$ e $X_{2}$ la quantità $$\begin{bmatrix}
\rho(X_{1},X_{2})=\frac{\text{Cov}(X_{1},X_{2})}{\sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}}
\end{bmatrix}$$
> [!info] Segno
> Poiché il denominatore è positivo, $\rho(X_{1},X_{2})\gtrless 0\iff \text{Cov}(X_{1},X_{2})\gtrless 0$: il coefficiente di correlazione ha lo **stesso segno** della covarianza.

## Proprietà
### 1) $|\rho(X_{1},X_{2})|\leq 1$
Cioè $-1\leq\rho(X_{1},X_{2})\leq 1$, perché si può dimostrare che $$|\text{Cov}(X_{1},X_{2})|\leq \sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}$$
> [!quote] Cauchy-Schwarz
> Questa può essere vista come una versione della disuguaglianza di **Cauchy-Schwarz** per spazi vettoriali, $|\langle v_{1},v_{2}\rangle|\leq\|v_{1}\|\,\|v_{2}\|$, con la covarianza nel ruolo del prodotto scalare e la varianza in quello del quadrato della norma.

### 2) $\rho(X_{1},X_{2})=1\iff X_{2}=aX_{1}+b$ con $a>0$
### 3) $\rho(X_{1},X_{2})=-1\iff X_{2}=aX_{1}+b$ con $a<0$
Quindi $|\rho|=1$ corrisponde al caso di **perfetta relazione affine** tra $X_{1}$ e $X_{2}$: i punti $(x_{1},x_{2})$ con densità positiva sono tutti allineati su una retta, crescente se $\rho=1$ ($a>0$) e decrescente se $\rho=-1$ ($a<0$).
> [!info] Perché servono v.a. non costanti
> La richiesta $\text{Var}[X_{1}]>0$ e $\text{Var}[X_{2}]>0$ serve a rendere ben definito il denominatore: se una delle due v.a. fosse costante il coefficiente di correlazione non avrebbe senso.

Quanto $\rho$ è vicino a $\pm 1$ è una misura di quanto la nube dei punti è vicina a una situazione di allineamento perfetto su una retta (crescente o decrescente); si veda [[Retta di regressione#Commenti conclusivi sull'esercizio|l'esercizio sulle rette di regressione]] per un caso con $\rho$ vicino a $+1$.

--- Fine parte sul coefficiente di correlazione (lezione 14, pp. 15-16) ---

---
Nota precedente: [[Varianza delle distribuzioni discrete notevoli]]. Nota successiva: [[Retta di regressione]]. Indice del blocco: [[Speranza matematica e momenti]].
