# Varianza delle distribuzioni discrete notevoli
Calcolo di $\text{Var}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica (e traslata), binomiale negativa (e traslata), con esempio sul confronto tra estrazioni con e senza reinserimento.
> [!quote] Tabella riassuntiva
> $$\begin{array}{ll}
> X\sim B(p) & \text{Var}[X]=p(1-p) \\
> X\sim BIN(n,p) & \text{Var}[X]=np(1-p) \\
> X\text{ ipergeometrica}(n_{1},n_{2},n) & \text{Var}[X]=np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}\quad\left( p=\frac{n_{1}}{n_{1}+n_{2}} \right) \\
> X\sim POISSON(\lambda) & \text{Var}[X]=\lambda \\
> X\sim Geo(p) & \text{Var}[X]=\frac{1-p}{p^{2}} \\
> Y\sim GeoTraslata(p) & \text{Var}[Y]=\frac{1-p}{p^{2}} \\
> X\sim BIN\text{-}NEG(r,p) & \text{Var}[X]=r\frac{1-p}{p^{2}} \\
> Y\sim BIN\text{-}NEG\text{-}traslata(r,p) & \text{Var}[Y]=r\frac{1-p}{p^{2}}
> \end{array}$$

In tutti i calcoli si usa la [[Varianza e momenti di una variabile aleatoria discreta#1) Formula alternativa: $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$|formula alternativa]] $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$, con le [[Speranza matematica delle distribuzioni discrete notevoli|medie già calcolate]].
## 1) Distribuzione bernoulliana: $X\sim B(p)$
Con $\mathbb{E}[X]=p$ (già visto) e $\mathbb{E}[X^{2}]=1^{2}\cdot p+0^{2}\cdot(1-p)=p$ si ha $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=p-p^{2}=\begin{bmatrix}p(1-p)\end{bmatrix}$$In particolare, se $X=1_{A}$, si ha $\text{Var}[1_{A}]=P(A)(1-P(A))$.
> [!info] Perché $\mathbb{E}[X^{2}]=\mathbb{E}[X]$
> Si vede che $X^{2}(w)=X(w)$ per ogni $w\in\ohm$, perché l'equazione $y^{2}=y$ ha soluzioni $y=0$ e $y=1$ (i soli valori assunti). Quindi $\mathbb{E}[X^{2}]=\mathbb{E}[X]=p$.

## 2) Distribuzione binomiale: $X\sim BIN(n,p)$
Il calcolo diretto di $\mathbb{E}[X^{2}]=\sum_{k=0}^{n}k^{2}\binom{n}{k}p^{k}(1-p)^{n-k}$ sarebbe un po' complicato. Usiamo invece il **metodo alternativo**: come visto per la media, $X=X_{1}+\dots+X_{n}$ dove $X_{1},\dots,X_{n}$ sono **i.i.d.** (indipendenti e identicamente distribuite) e bernoulliane di parametro $p$. Allora, per l'[[Indipendenza e covarianza#Conseguenza (varianza di una somma di v.a. indipendenti)|indipendenza]], $$\text{Var}[X]=\sum_{i=1}^{n}\text{Var}[X_{i}]=\underset{n\text{ volte}}{\underbrace{p(1-p)+\dots+p(1-p)}}=\begin{bmatrix}np(1-p)\end{bmatrix}$$
## 3) Distribuzione ipergeometrica
Ricordiamo lo schema: $n$ estrazioni **senza** reinserimento con $2\leq n<n_{1}+n_{2}$ (per $n=1$ non ha senso parlare di reinserimento), e $X=$ numero di oggetti di tipo 1 estratti. Con $p=\frac{n_{1}}{n_{1}+n_{2}}$ si avrebbe $\text{Var}[X]=\mathbb{E}[X^{2}]-(np)^{2}$, ma il calcolo diretto di $\mathbb{E}[X^{2}]$ è complicato.
Con il **metodo alternativo** (che non dimostriamo del tutto) si scrive $X=X_{1}+\dots+X_{n}$ con $X_{i}\sim B(p)$ ma **non** indipendenti. Allora $$\text{Var}[X]=\sum_{i=1}^{n}\underset{=p(1-p)}{\underbrace{\text{Var}[X_{i}]}}+2\underset{i<j}{\sum_{i,j=1}^{n}}\underset{\text{tutte uguali tra loro e negative}}{\underbrace{\text{Cov}(X_{i},X_{j})}}<np(1-p)$$Facendo i calcoli si dimostra che $$\begin{bmatrix}\text{Var}[X]=np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}\end{bmatrix}$$(avendo usato $1-p=\frac{n_{2}}{n_{1}+n_{2}}$).
> [!info] Confronto con e senza reinserimento
> Essendo $1<n<n_{1}+n_{2}$, si ha $\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}\in(0,1)$, in accordo con $\text{Var}[X]<np(1-p)$. Se $n_{1}+n_{2}$ è molto più grande di $n$ il rapporto è vicino a 1 ("poca differenza" con il caso con reinserimento). Quindi nel confronto tra estrazioni "con" e "senza" reinserimento si hanno **medie uguali** (valore comune $n\frac{n_{1}}{n_{1}+n_{2}}$) e **varianze diverse** (varianza più piccola nel caso senza reinserimento).

## 4) Distribuzione di Poisson: $X\sim POISSON(\lambda)$
Con $\mathbb{E}[X]=\lambda$ (già visto) e $\mathbb{E}[X^{2}]=\sum_{k\geq 0}k^{2}\frac{\lambda^{k}}{k!}e^{-\lambda}$, il risultato si prende per buono: $$\begin{bmatrix}\text{Var}[X]=\lambda\end{bmatrix}$$(quindi per la Poisson media e varianza coincidono).
## 5) Distribuzione geometrica: $X\sim Geo(p)$
Con $\mathbb{E}[X]=\frac{1}{p}-1$ (già visto) e $\mathbb{E}[X^{2}]=\sum_{k\geq 0}k^{2}(1-p)^{k}p$, il risultato si prende per buono: $$\begin{bmatrix}\text{Var}[X]=\frac{1-p}{p^{2}}\end{bmatrix}$$
## 6) Distribuzione geometrica traslata: $Y\sim GeoTraslata(p)$
Ci riconduciamo al caso precedente: $Y=X+1$ con $X\sim Geo(p)$. Allora, essendo la [[Varianza e momenti di una variabile aleatoria discreta#3) $\text{Var}[X+a]=\text{Var}[X]$ (per $a\in \mathbb{R}$)|varianza invariante per traslazione]], $$\text{Var}[Y]=\text{Var}[X+1]=\text{Var}[X]=\begin{bmatrix}\frac{1-p}{p^{2}}\end{bmatrix}$$
## 7) Binomiale negativa e binomiale negativa traslata
Il calcolo diretto a partire da $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$ sarebbe complicato. Facciamo invece riferimento alle [[Distribuzione binomiale negativa#Un legame tra binomiale negativa (traslata) e geometrica (traslata)|decomposizioni in somme di $r$ geometriche indipendenti (o $r$ geometriche traslate indipendenti)]] viste in passato. Allora, per l'indipendenza, $$\begin{array}{ll}
X=\underset{\text{i.i.d.}\sim Geo(p)}{\underbrace{X_{1}+\dots+X_{r}}} & \implies\ \text{Var}[X]=\sum_{i=1}^{r}\text{Var}[X_{i}]=\underset{r\text{ volte}}{\underbrace{\frac{1-p}{p^{2}}+\dots+\frac{1-p}{p^{2}}}}=\begin{bmatrix}r\frac{1-p}{p^{2}}\end{bmatrix} \\
Y=\underset{\text{i.i.d.}\sim GeoTraslata(p)}{\underbrace{Y_{1}+\dots+Y_{r}}} & \implies\ \text{Var}[Y]=\sum_{i=1}^{r}\text{Var}[Y_{i}]=\underset{r\text{ volte}}{\underbrace{\frac{1-p}{p^{2}}+\dots+\frac{1-p}{p^{2}}}}=\begin{bmatrix}r\frac{1-p}{p^{2}}\end{bmatrix}
\end{array}$$
> [!info] Coerenza
> Si è ottenuto $\text{Var}[Y]=\text{Var}[X]$, in accordo con $Y=X+r$: sommando una costante la varianza non cambia.

## Esempio (urna, con e senza reinserimento)
Un'urna ha 3 palline bianche e 4 nere. Si estraggono 2 palline a caso, una alla volta e con/senza reinserimento. Sia $X$ la v.a. che conta il numero di palline bianche estratte. Calcolare $\mathbb{E}[X]$ e $\text{Var}[X]$.
Qui $n_{1}=3$, $n_{2}=4$, $n=2$, $p=\frac{n_{1}}{n_{1}+n_{2}}=\frac{3}{7}$. $$\begin{array}{l|ll}
 & \mathbb{E}[X] & \text{Var}[X] \\
\hline
\text{CON} & np=2\cdot \frac{3}{7}=\frac{6}{7} & np(1-p)=2\cdot \frac{3}{7}\cdot \frac{4}{7}=\frac{24}{49} \\
\text{SENZA} & np=2\cdot \frac{3}{7}=\frac{6}{7} & np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}=\frac{24}{49}\cdot \frac{7-2}{7-1}=\frac{24}{49}\cdot \frac{5}{6}=\frac{20}{49}
\end{array}$$
### Verifica diretta dei valori numerici
**Caso con reinserimento** ($X\sim BIN(2,\frac{3}{7})$): con $P_{X}(k)=\binom{2}{k}\left( \frac{3}{7} \right)^{k}\left( \frac{4}{7} \right)^{2-k}$ si ha $P_{X}(0)=\frac{16}{49}$, $P_{X}(1)=\frac{24}{49}$, $P_{X}(2)=\frac{9}{49}$, da cui $$\mathbb{E}[X]=0\cdot \frac{16}{49}+1\cdot \frac{24}{49}+2\cdot \frac{9}{49}=\frac{42}{49}=\frac{6}{7}$$ $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=0^{2}\cdot \frac{16}{49}+1^{2}\cdot \frac{24}{49}+2^{2}\cdot \frac{9}{49}-\left( \frac{6}{7} \right)^{2}=\frac{60}{49}-\frac{36}{49}=\frac{24}{49}\quad\text{ok}$$
**Caso senza reinserimento** (ipergeometrica): con $P_{X}(k)=\frac{\binom{3}{k}\binom{4}{2-k}}{\binom{7}{2}}$ si ha $P_{X}(0)=\frac{6}{21}=\frac{2}{7}$, $P_{X}(1)=\frac{12}{21}=\frac{4}{7}$, $P_{X}(2)=\frac{3}{21}=\frac{1}{7}$, da cui $$\mathbb{E}[X]=0\cdot \frac{2}{7}+1\cdot \frac{4}{7}+2\cdot \frac{1}{7}=\frac{6}{7}$$ $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=0^{2}\cdot \frac{2}{7}+1^{2}\cdot \frac{4}{7}+2^{2}\cdot \frac{1}{7}-\left( \frac{6}{7} \right)^{2}=\frac{8}{7}-\frac{36}{49}=\frac{56-36}{49}=\frac{20}{49}\quad\text{ok}$$

--- Fine parte sulle varianze notevoli (lezione 14, pp. 7-14) ---

---
Nota precedente: [[Indipendenza e covarianza]]. Nota successiva: [[Coefficiente di correlazione]]. Indice del blocco: [[Speranza matematica e momenti]].
