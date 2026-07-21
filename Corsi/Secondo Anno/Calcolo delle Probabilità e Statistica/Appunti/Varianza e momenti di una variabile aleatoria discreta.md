# Varianza e momenti di una variabile aleatoria discreta
Definizione di momento e momento centrato, varianza e scarto quadratico medio, proprietà, disuguaglianza di Chebyshev e formule di calcolo.
> [!info] Valgono in generale
> Le definizioni che seguono possono essere date **anche se $X$ non è discreta**. Qui pensiamo solo al caso discreto (l'unico visto finora), ma i risultati valgono in generale.
## Momenti e momento centrato
Sia $X$ una v.a. e sia $k\geq 1$ intero.
- Il **momento $k$-esimo** di $X$ è (se esiste finito) $$\mathbb{E}[X^{k}]$$
- Il **momento centrato $k$-esimo** di $X$ è (se esiste finito) $$\mathbb{E}[(X-\mathbb{E}[X])^{k}]$$
## Varianza
La **varianza** di $X$ è (se esiste finita) il momento centrato di ordine $2$: $$\begin{bmatrix}
\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]
\end{bmatrix}$$
> [!info] Terminologia
> Si usa il termine **scarto quadratico medio** di una v.a. $X$ per $\sqrt{\text{Var}[X]}$.

## Proprietà della varianza
Per la [[Speranza matematica di una variabile aleatoria discreta#Alcune proprietà di $\mathbb{E}[X]$|monotonia del valore medio]], ed essendo $(X-\mathbb{E}[X])^{2}\geq 0$, si ha $$\mathbb{E}[(X-\mathbb{E}[X])^{2}]\geq \mathbb{E}[0]\quad\implies\quad \text{Var}[X]\geq 0$$In realtà si può dire di più: $$\text{Var}[X]=0\iff X\text{ è una v.a. costante}\iff X=\mathbb{E}[X]$$dove per "costante" si intende il caso in cui esiste $x_{0}\in \mathbb{R}$ tale che $P_{X}(x_{0})=1$; in corrispondenza si ha $x_{0}=\mathbb{E}[X]$.
> [!info] Minimo ma non massimo
> La varianza ha un **valore minimo** (cioè $0$); al contrario **non** ammette un valore massimo.

In ogni modo possiamo dire che:
- varianza **piccola** $\to$ distribuzione concentrata vicino alla media;
- varianza **grande** $\to$ distribuzione non concentrata vicino alla media.

## Disuguaglianza di Chebyshev
Per comprendere meglio il legame tra varianza e concentrazione presentiamo il seguente risultato.
> [!quote] Disuguaglianza di Chebyshev
> Per ogni v.a. $X$ con media e varianza finite (vale anche per v.a. non discrete), si ha $$\begin{bmatrix}
> \forall\ a>0\qquad P(|X-\mathbb{E}[X]|\geq a)\leq \frac{\text{Var}[X]}{a^{2}}
> \end{bmatrix}$$

> [!info] Sul nome
> Pafnutij L'vovič Čebyšëv (1821-1894) è stato un matematico e statistico russo. Il suo nome si trova traslitterato in vari modi (Chebychev, Chebyshev, Cebisceff, Tchebycheff, …).

**Osservazione (quando è banale).** Se $\frac{\text{Var}[X]}{a^{2}}\geq 1$ (questo può accadere se $a$ è abbastanza vicino a zero) si ha una disuguaglianza banale, perché il primo membro è comunque in $[0,1]$.
**Osservazione (lettura dell'evento).** La disuguaglianza dice che l'evento $$\{|X-\mathbb{E}[X]|\geq a\}=\{X-\mathbb{E}[X]\geq a\}\cup\{X-\mathbb{E}[X]\leq -a\}=\{X\geq \mathbb{E}[X]+a\}\cup\{X\leq \mathbb{E}[X]-a\}$$(cioè "$X$ dista da $\mathbb{E}[X]$ almeno $a$") ha una probabilità che non può essere troppo grande, e diventa piccola se $\text{Var}[X]$ è piccola.
### Dimostrazione (caso discreto)
Per il caso generale il procedimento è simile. Partiamo dalla definizione, usando la [[Speranza matematica di una variabile aleatoria discreta#Proposizione (speranza di una trasformazione)|formula per la speranza di una trasformazione di $X$]] e l'osservazione che $z^{2}=|z|^{2}$ per ogni $z\in \mathbb{R}$: $$\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\sum_{x_{k}\in \delta_{X}}(x_{k}-\mathbb{E}[X])^{2}P_{X}(x_{k})=\underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in \delta_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}P_{X}(x_{k})+\underset{|x_{k}-\mathbb{E}[X]|<a}{\sum_{x_{k}\in \delta_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}P_{X}(x_{k})$$Essendo le due sommatorie non negative (somme di quadrati), si ottiene una minorazione togliendo la seconda: $$\text{Var}[X]\geq \underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in \delta_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}P_{X}(x_{k})\geq \underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in \delta_{X}:}}a^{2}P_{X}(x_{k})=a^{2}\underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in \delta_{X}:}}P_{X}(x_{k})=a^{2}P(|X-\mathbb{E}[X]|\geq a)$$dove nella seconda disuguaglianza si è usato $|x_{k}-\mathbb{E}[X]|\geq a\implies|x_{k}-\mathbb{E}[X]|^{2}\geq a^{2}$. Dividendo membro a membro per $a^{2}$ si ottiene $$\frac{\text{Var}[X]}{a^{2}}\geq P(|X-\mathbb{E}[X]|\geq a)\qquad\Box$$
## Alcune formule per la varianza
Valgono non solo per il caso discreto.
> [!info] Notazione
> Nel seguito si scrive $\mathbb{E}^{2}[X]$ anziché $(\mathbb{E}[X])^{2}$.

### 1) Formula alternativa: $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$
$$\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\mathbb{E}[X^{2}-2X\cdot \mathbb{E}[X]+\mathbb{E}^{2}[X]]\overset{\text{lin.}}{=}\mathbb{E}[X^{2}]-2\underset{=\mathbb{E}^{2}[X]}{\underbrace{\mathbb{E}[X]\cdot \mathbb{E}[X]}}+\mathbb{E}^{2}[X]=\begin{bmatrix}\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]\end{bmatrix}$$(si è usata la [[Speranza matematica di una variabile aleatoria discreta#Alcune proprietà di $\mathbb{E}[X]$|linearità]] e il fatto che $\mathbb{E}[X]$ è una costante).
### 2) $\text{Var}[aX]=a^{2}\text{Var}[X]$ (per $a\in \mathbb{R}$)
**1° modo (dalla definizione).** $$\text{Var}[aX]=\mathbb{E}[(aX-\mathbb{E}[aX])^{2}]=\mathbb{E}[(aX-a\mathbb{E}[X])^{2}]=\mathbb{E}[a^{2}(X-\mathbb{E}[X])^{2}]\overset{\text{lin.}}{=}a^{2}\underset{=\text{Var}[X]}{\underbrace{\mathbb{E}[(X-\mathbb{E}[X])^{2}]}}=a^{2}\text{Var}[X]$$**2° modo (con la formula alternativa).** $$\text{Var}[aX]=\mathbb{E}[(aX)^{2}]-\mathbb{E}^{2}[aX]=\mathbb{E}[a^{2}X^{2}]-(a\mathbb{E}[X])^{2}=a^{2}\mathbb{E}[X^{2}]-a^{2}\mathbb{E}^{2}[X]=a^{2}(\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X])=a^{2}\text{Var}[X]$$
### 3) $\text{Var}[X+a]=\text{Var}[X]$ (per $a\in \mathbb{R}$)
$$\text{Var}[X+a]=\mathbb{E}[(X+a-\underset{=\mathbb{E}[X]+a}{\underbrace{\mathbb{E}[X+a]}})^{2}]=\mathbb{E}[(X+\cancel{a}-\mathbb{E}[X]-\cancel{a})^{2}]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\text{Var}[X]$$(anche in questo caso si può fare una dimostrazione alternativa con la formula alternativa).
> [!quote] Interpretazione
> Traslando la v.a. di una costante $a$, la densità si sposta rigidamente (da $x_{k}$ a $x_{k}+a$) e la media si sposta con essa (da $\mathbb{E}[X]$ a $\mathbb{E}[X]+a$). In entrambi i casi la distribuzione si "disperde" rispetto alla propria media nello stesso modo: quindi non sorprende che si abbia la stessa varianza.

---
Nota precedente: [[Speranza matematica delle distribuzioni discrete notevoli]]. Nota successiva: [[Covarianza di variabili aleatorie discrete]]. Indice del blocco: [[Speranza matematica e momenti]].
