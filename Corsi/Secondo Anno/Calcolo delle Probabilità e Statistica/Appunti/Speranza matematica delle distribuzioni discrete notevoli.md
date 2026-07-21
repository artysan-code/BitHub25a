# Speranza matematica delle distribuzioni discrete notevoli
Calcolo di $\mathbb{E}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica (e traslata), binomiale negativa (e traslata).
> [!quote] Tabella riassuntiva
> $$\begin{array}{ll}
> X\sim B(p) & \mathbb{E}[X]=p \\
> X\sim BIN(n,p) & \mathbb{E}[X]=np \\
> X\text{ ipergeometrica}(n_{1},n_{2},n) & \mathbb{E}[X]=n\frac{n_{1}}{n_{1}+n_{2}} \\
> X\sim POISSON(\lambda) & \mathbb{E}[X]=\lambda \\
> X\sim Geo(p) & \mathbb{E}[X]=\frac{1}{p}-1 \\
> Y\sim GeoTraslata(p) & \mathbb{E}[Y]=\frac{1}{p} \\
> X\sim BIN\text{-}NEG(r,p) & \mathbb{E}[X]=r\left( \frac{1}{p}-1 \right) \\
> Y\sim BIN\text{-}NEG\text{-}traslata(r,p) & \mathbb{E}[Y]=\frac{r}{p}
> \end{array}$$

## 1) Distribuzione bernoulliana: $X\sim B(p)$
$\delta_{X}=\{0,1\}$ è un insieme finito, quindi la [[Speranza matematica di una variabile aleatoria discreta#Definizione|condizione $(*)$]] è verificata. Con $P_{X}(0)=1-p$ e $P_{X}(1)=p$ si ha $$\mathbb{E}[X]=0\cdot P_{X}(0)+1\cdot P_{X}(1)=0\cdot(1-p)+1\cdot p=\begin{bmatrix}p\end{bmatrix}$$
> [!quote] Conseguenza importante
> Se $X=1_{A}$ (funzione indicatrice dell'evento $A\in\mathcal{A}$), allora $$\mathbb{E}[1_{A}]=P(A)$$

## 2) Distribuzione binomiale: $X\sim BIN(n,p)$
$\delta_{X}=\{0,1,\dots,n\}$ è un insieme finito, quindi $(*)$ è verificata. Si ha $$\begin{array}{ll}
\mathbb{E}[X] & =\displaystyle\sum_{k=0}^{n}k\binom{n}{k}p^{k}(1-p)^{n-k}=\sum_{k=1}^{n}\cancel{k}\frac{n!}{\cancel{k!}(n-k)!}p^{k}(1-p)^{n-k} \\
 & =\displaystyle\sum_{k=1}^{n}\frac{n(n-1)!}{(k-1)!(n-1-(k-1))!}p^{k-1+1}(1-p)^{n-1-(k-1)} \\
 & \underset{h=k-1}{=}np\displaystyle\sum_{h=0}^{n-1}\binom{n-1}{h}p^{h}(1-p)^{n-1-h}\overset{\text{binomio di Newton}}{=}np(p+1-p)^{n-1}=\begin{bmatrix}np\end{bmatrix}
\end{array}$$
### Dimostrazione alternativa (con la linearità)
Il risultato $X\sim BIN(n,p)\implies \mathbb{E}[X]=np$ si può dimostrare in maniera alternativa come segue.
Ricordiamo che una maniera canonica per ottenere una $X\sim BIN(n,p)$ è la seguente: $$\ohm=\underset{n\text{ volte}}{\underbrace{\{0,1\}\times\dots\times\{0,1\}}}\quad\quad P(\{w\})=p^{X(w)}(1-p)^{n-X(w)}\quad\text{dove }X(w)=\sum_{i=1}^{n}w_{i}$$per ogni $w=(w_{1},\dots,w_{n})\in\ohm$. Allora possiamo considerare le v.a. più semplici $X_{1},\dots,X_{n}:\ohm\to \mathbb{R}$ tali che $X_{i}(w)=w_{i}$ per ogni $w\in\ohm$, con $i=1,\dots,n$.
In corrispondenza si ha $$\begin{cases}
X=X_{1}+\dots+X_{n} & (\text{per costruzione}) \\
\mathbb{E}[X_{i}]=P(X_{i}=1)=p & (\text{per quanto detto nella bernoulliana, }\forall\ i=1,\dots,n)
\end{cases}$$Allora, per la [[Speranza matematica di una variabile aleatoria discreta#Alcune proprietà di $\mathbb{E}[X]$|linearità]], $$\mathbb{E}[X]=\mathbb{E}[X_{1}+\dots+X_{n}]=\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{n}]=\underset{n\text{ volte}}{\underbrace{p+\dots+p}}=np$$
## 3) Distribuzione ipergeometrica
$\delta_{X}=\{0,1,\dots,n\}$ è un insieme finito, quindi $(*)$ è verificata. Per definizione si avrebbe $$\mathbb{E}[X]=\sum_{k=0}^{n}k\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}$$ma anche qui bisognerebbe gestire l'espressione con i fattoriali: **il prof non lo fa**.
Consideriamo invece il procedimento alternativo visto per la binomiale. Anche in questo caso (pensando alle estrazioni **senza** reinserimento) si ha $X=X_{1}+\dots+X_{n}$ dove $$X_{i}=\begin{cases}
1 & \text{estratta pallina di tipo 1} \\
0 & \text{estratta pallina di tipo 2}
\end{cases}\ \sim B\left( \frac{n_{1}}{n_{1}+n_{2}} \right)\quad\quad\forall\ i\in\{1,\dots,n\}$$Allora, per la linearità, $$\mathbb{E}[X]=\mathbb{E}[X_{1}+\dots+X_{n}]=\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{n}]=\underset{n\text{ volte}}{\underbrace{\frac{n_{1}}{n_{1}+n_{2}}+\dots+\frac{n_{1}}{n_{1}+n_{2}}}}=\begin{bmatrix}n\frac{n_{1}}{n_{1}+n_{2}}\end{bmatrix}$$
### Commenti
- C'è una **differenza** tra i due approcci alternativi visti per binomiale e ipergeometrica: $$\begin{cases}
X_{1},\dots,X_{n}\text{ indipendenti nel 1° caso} \\
X_{1},\dots,X_{n}\ \textbf{non}\text{ indipendenti nel 2° caso}
\end{cases}$$Questo non ha influenza sui risultati, che coincidono se poniamo $p=\frac{n_{1}}{n_{1}+n_{2}}$. Al contrario ci sarà una differenza nel caso della **varianza**, di cui si parlerà prossimamente.
- I risultati ottenuti ci dicono che, nel caso di un numero finito di estrazioni casuali, **la media della v.a. che conta il numero di oggetti di un certo tipo estratti non cambia se le estrazioni sono con o senza reinserimento**.
- In generale $\mathbb{E}[X]$ dipende dalla **distribuzione** di $X$, e non da come è fatta $X:\ohm\to \mathbb{R}$. In effetti, nel caso discreto (l'unico visto finora), $\mathbb{E}[X]$ dipende solo dalla densità discreta $P_{X}$. Quindi quel che abbiamo visto per l'ipergeometrica, con riferimento alle estrazioni casuali senza reinserimento, vale anche per le [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]].
## 4) Distribuzione di Poisson: $X\sim POISSON(\lambda)$
$\delta_{X}=\{0,1,2,\dots\}$ è un insieme **non finito**, quindi la condizione $(*)$ va verificata: $\sum_{k\geq 0}|k|P_{X}(k)<\infty$.
> [!info] Qui il valore assoluto è superfluo
> I valori assunti sono tutti $\geq 0$, quindi si può calcolare la serie senza valore assoluto.

$$\sum_{k\geq 0}k\frac{\lambda^{k}}{k!}e^{-\lambda}=\sum_{k\geq 1}\cancel{k}\frac{\lambda^{k-1+1}}{\cancel{k}\cdot(k-1)!}e^{-\lambda}=\lambda\sum_{k\geq 1}\frac{\lambda^{k-1}}{(k-1)!}e^{-\lambda}\underset{h=k-1}{=}\lambda\underset{=1}{\underbrace{\sum_{h\geq 0}\frac{\lambda^{h}}{h!}e^{-\lambda}}}=\lambda$$Quindi vale $(*)$ perché $\lambda<\infty$, ed inoltre $\begin{bmatrix}\mathbb{E}[X]=\lambda\end{bmatrix}$.
## 5) Distribuzione geometrica: $X\sim Geo(p)$
$\delta_{X}=\{0,1,2,\dots\}$ è un insieme non finito; anche qui il valore assoluto è superfluo perché i valori assunti sono $\geq 0$.
Partiamo dalla condizione di normalizzazione: $$\sum_{k\geq 0}(1-p)^{k}p=1\implies p\sum_{k\geq 0}(1-p)^{k}=1\implies \sum_{k\geq 0}(1-p)^{k}=\frac{1}{p}$$Allora, **derivando rispetto a $p$** (questo è un caso in cui la derivata della serie coincide con la serie delle derivate), si ha $$\sum_{k\geq 0}k(1-p)^{k-1}(-1)=-p^{-2}\quad\underset{\text{i segni meno si cancellano}}{\implies}\quad\sum_{k\geq 0}k(1-p)^{k-1}=\frac{1}{p^{2}}$$e moltiplicando membro a membro per $p(1-p)$ si ottiene $$\sum_{k\geq 0}k(1-p)^{k}p=\frac{(1-p)p}{p^{2}}=\frac{1-p}{p}=\frac{1}{p}-1$$Quindi vale $(*)$ perché $\frac{1}{p}-1<\infty$ (si osservi che $p\neq 0$), ed inoltre $\begin{bmatrix}\mathbb{E}[X]=\frac{1}{p}-1\end{bmatrix}$.
## 6) Distribuzione geometrica traslata: $Y\sim GeoTraslata(p)$
Qui, invece di procedere con la definizione (si dovrebbe fare riferimento alla serie $\sum_{k\geq 1}k(1-p)^{k-1}p$, sia per la condizione $(*)$ sia per il calcolo di $\mathbb{E}[Y]$), osserviamo che $$Y=X+1\quad\text{con }X\sim Geo(p)$$Allora, per la linearità, $$\mathbb{E}[Y]=\mathbb{E}[X+1]=\underset{=\frac{1}{p}-1\ (\text{calcolato prima})}{\underbrace{\mathbb{E}[X]}}+\underset{=1}{\underbrace{\mathbb{E}[1]}}=\frac{1}{p}-1+1=\begin{bmatrix}\frac{1}{p}\end{bmatrix}$$
## 7) Binomiale negativa e binomiale negativa traslata
Anche in questo caso non faremo riferimento alla definizione (si dovrebbero considerare le serie $\sum_{k\geq 0}k\binom{k+r-1}{r-1}p^{r}(1-p)^{k}$ e $\sum_{h\geq r}h\binom{h-1}{r-1}p^{r}(1-p)^{h-r}$).
Al contrario consideriamo le [[Distribuzione binomiale negativa#Un legame tra binomiale negativa (traslata) e geometrica (traslata)|somme di geometriche (e geometriche traslate)]] opportune viste in passato, e usiamo la linearità: $$\begin{array}{ll}
X=\underset{Geo(p)\text{ indip.}}{\underbrace{X_{1}+\dots+X_{r}}} & \implies\ \mathbb{E}[X]\overset{\text{lin.}}{=}\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{r}]=\underset{r\text{ volte}}{\underbrace{\frac{1}{p}-1+\dots+\frac{1}{p}-1}}=\begin{bmatrix}r\left( \frac{1}{p}-1 \right)\end{bmatrix} \\
Y=\underset{GeoTraslata(p)\text{ indip.}}{\underbrace{Y_{1}+\dots+Y_{r}}} & \implies\ \mathbb{E}[Y]\overset{\text{lin.}}{=}\mathbb{E}[Y_{1}]+\dots+\mathbb{E}[Y_{r}]=\underset{r\text{ volte}}{\underbrace{\frac{1}{p}+\dots+\frac{1}{p}}}=\begin{bmatrix}\frac{r}{p}\end{bmatrix}
\end{array}$$
### Verifica di coerenza
I valori ottenuti $\mathbb{E}[Y]=\frac{r}{p}$ e $\mathbb{E}[X]=r\left( \frac{1}{p}-1 \right)$ sono in accordo con altre formule. Infatti si ha $Y=X+r$, da cui segue (per linearità) $\mathbb{E}[Y]=\mathbb{E}[X+r]=\mathbb{E}[X]+r$. In effetti $$\underset{=\frac{r}{p}}{\underbrace{\mathbb{E}[Y]}}=\underset{=r\left( \frac{1}{p}-1 \right)=\frac{r}{p}-\cancel{r}+\cancel{r}}{\underbrace{\mathbb{E}[X]+r}}\quad\text{ok}$$
--- Fine parte sulle speranze notevoli (lezione 13, pp. 1-9) ---

---
Nota precedente: [[Speranza matematica di una variabile aleatoria discreta]]. Nota successiva: [[Varianza e momenti di una variabile aleatoria discreta]]. Indice del blocco: [[Speranza matematica e momenti]].
