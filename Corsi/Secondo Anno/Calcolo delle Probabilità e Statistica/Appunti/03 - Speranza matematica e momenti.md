# Speranza matematica e momenti
Appunti sul secondo blocco del corso (lezioni 12-14) — valore medio, momenti, varianza, covarianza e regressione per variabili aleatorie discrete — organizzati nelle seguenti sezioni:
1. [[03 - Speranza matematica e momenti#Speranza matematica di una variabile aleatoria discreta|Speranza matematica di una variabile aleatoria discreta]] — definizione di $\mathbb{E}[X]$, condizione di esistenza, linearità e monotonia, speranza di una trasformazione.
2. [[03 - Speranza matematica e momenti#Speranza matematica delle distribuzioni discrete notevoli|Speranza matematica delle distribuzioni discrete notevoli]] — $\mathbb{E}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica e binomiale negativa.
3. [[03 - Speranza matematica e momenti#Varianza e momenti di una variabile aleatoria discreta|Varianza e momenti di una variabile aleatoria discreta]] — momenti e momento centrato, varianza, scarto quadratico medio, proprietà, disuguaglianza di Chebyshev e formule di calcolo.
4. [[03 - Speranza matematica e momenti#Covarianza di variabili aleatorie discrete|Covarianza di variabili aleatorie discrete]] — varianza di una somma, definizione di covarianza, formule, interpretazione geometrica ed esercizio riassuntivo.
5. [[03 - Speranza matematica e momenti#Indipendenza e covarianza|Indipendenza e covarianza]] — indipendenza $\implies$ covarianza nulla (e varianza di una somma di indipendenti), con controesempio per il viceversa.
6. [[03 - Speranza matematica e momenti#Varianza delle distribuzioni discrete notevoli|Varianza delle distribuzioni discrete notevoli]] — $\text{Var}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica e binomiale negativa, con confronto tra estrazioni con e senza reinserimento.
7. [[03 - Speranza matematica e momenti#Coefficiente di correlazione|Coefficiente di correlazione]] — covarianza normalizzata $\rho\in[-1,1]$, disuguaglianza di Cauchy-Schwarz e caratterizzazione di $\rho=\pm 1$.
8. [[03 - Speranza matematica e momenti#Retta di regressione|Retta di regressione]] — metodo dei minimi quadrati, formule per le due rette di regressione, passaggio per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$ ed esercizio completo.
9. [[03 - Speranza matematica e momenti#Esercizi di riepilogo (lezione 23)|Esercizi di riepilogo (lezione 23)]] — esercizi su speranza, varianza, covarianza e retta di regressione.
## Nota sulla struttura
Blocco successivo a [[02 - Modelli discreti]], che raccoglie i modelli discreti. I marcatori `--- Fine lezione NN ---` conservano la corrispondenza con i PDF in `Materiale Didattico/Slide/6 CFU/`.
## Speranza matematica di una variabile aleatoria discreta
Definizione di $\mathbb{E}[X]$, condizione di esistenza, proprietà (linearità, monotonia) e formula per la speranza di una trasformazione.

> [!info] Sinonimi
> "Speranza matematica", **media**, **valore medio**, **attesa**, **valore atteso**.
### Motivazione
Questa grandezza si introduce per definire una grandezza analoga al **baricentro** per una distribuzione di masse in fisica, il cui ruolo è giocato dalla distribuzione della v.a. (non necessariamente discreta).
Inoltre, se la speranza matematica esiste finita, possiamo dire che fornisce un **valore riassuntivo** della distribuzione della v.a. (anche se questo fa perdere delle informazioni rispetto alla conoscenza della distribuzione stessa).
### Definizione
Sia $X$ una v.a. discreta con densità $p_{X}$. Allora si dice che $X$ ha **speranza matematica finita** se $$\sum_{x_{k}\in S_{X}}|x_{k}|p_{X}(x_{k})<\infty\quad\quad(*)$$In corrispondenza, se vale $(*)$, allora la speranza matematica di $X$ è definita come segue: $$\begin{bmatrix}
\mathbb{E}[X]=\sum_{x_{k}\in S_{X}}x_{k}p_{X}(x_{k})
\end{bmatrix}$$
#### Commento (quando $(*)$ è automaticamente verificata)
La condizione $(*)$ è verificata se l'insieme $S_{X}$ è **limitato**, cioè se esiste $M>0$ tale che $$|x_{k}|\leq M\quad\forall\ x_{k}\in S_{X}\quad\quad\iff\quad -M\leq x_{k}\leq M\quad\quad(**)$$Infatti in corrispondenza si ha $$\sum_{x_{k}\in S_{X}}|x_{k}|p_{X}(x_{k})\leq M\underset{=1}{\underbrace{\sum_{x_{k}\in S_{X}}p_{X}(x_{k})}}=M<\infty$$Osserviamo che $$S_{X}\text{ finito}\implies S_{X}\text{ limitato}$$perché, se $S_{X}=\{x_{1},\dots,x_{n}\}$ per qualche $n$, vale $(**)$ con $M=\max\{|x_{1}|,\dots,|x_{n}|\}$.
Al contrario esistono insiemi limitati non finiti: si pensi a intervalli limitati (es. $[a,b]$) o, se vogliamo un caso di insieme al più numerabile, all'insieme $\left\{ \frac{1}{n}:n\geq 1 \right\}=\left\{ 1,\frac{1}{2},\frac{1}{3},\dots \right\}$ dove vale $(**)$ con $M=1$.
### Alcune proprietà della speranza matematica

> [!info] Valgono in generale
> Queste proprietà valgono **non solo** per il caso in cui $X$ è discreta.

- **(Terminologia)** $X$ si dice **centrata** se $\mathbb{E}[X]=0$.
- **(Linearità)** Siano $X_{1},\dots,X_{n}$ v.a. definite su uno stesso spazio di probabilità, con speranza matematica finita. Siano $a_{1},\dots,a_{n}\in \mathbb{R}$. Allora anche $a_{1}X_{1}+\dots+a_{n}X_{n}$ ha speranza matematica finita e si ha $$\mathbb{E}[a_{1}X_{1}+\dots+a_{n}X_{n}]=a_{1}\mathbb{E}[X_{1}]+\dots+a_{n}\mathbb{E}[X_{n}]$$(come caso particolare possiamo considerare $X_{1}+\dots+X_{n}$ ponendo $a_{1}=\dots=a_{n}=1$).
- **(Prodotto di v.a. [[02 - Modelli discreti#Indipendenza tra variabili aleatorie|indipendenti]])** Siano $X_{1},\dots,X_{n}$ definite su uno stesso spazio di probabilità, con speranza matematica finita, e **indipendenti**. Allora $X_{1}\cdot\dots\cdot X_{n}$ ha speranza matematica finita e si ha $$\mathbb{E}[X_{1}\cdot\dots\cdot X_{n}]=\mathbb{E}[X_{1}]\cdot\dots\cdot \mathbb{E}[X_{n}]$$
- **(Monotonia)** Supponiamo che $X(\omega)\geq Y(\omega)$ per ogni $\omega\in\Omega$. Allora, se $X$ e $Y$ hanno speranza matematica finita, si ha $\mathbb{E}[X]\geq \mathbb{E}[Y]$. (In realtà basta avere $P(X\geq Y)=1$.)

> [!warning] Attenzione
> La linearità **non** richiede l'indipendenza; la formula del prodotto **sì**.
### Proposizione (speranza di una trasformazione)
Sia $\underline{X}$ una v.a. discreta $m$-dimensionale con [[02 - Modelli discreti#Densità congiunta e densità marginali|densità congiunta]] $p_{\underline{X}}$. Sia $f:\mathbb{R}^{m}\to \mathbb{R}$ e sia $Y=f(\underline{X})$. Allora, se $Y$ ha speranza matematica finita, si ha $$\begin{bmatrix}
\mathbb{E}[Y]=\sum_{\underline{x}_{k}\in S_{\underline{X}}}f(\underline{x}_{k})p_{\underline{X}}(\underline{x}_{k})
\end{bmatrix}$$(per $m=1$ si ha una densità discreta non congiunta, perché $\underline{X}$ è una v.a. unidimensionale).

> [!quote] Commento
> In altri termini **non serve conoscere esplicitamente la densità discreta $p_{Y}$ della v.a. $Y$**, ma basta fare riferimento a $p_{\underline{X}}$ (oltre che ad $f$).
#### Dimostrazione
Si ha $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{y_{h}\in S_{Y}}y_{h}\underset{=P(Y=y_{h})}{\underbrace{p_{Y}(y_{h})}}=\sum_{y_{h}\in S_{Y}}y_{h}P\left( \bigcup_{\underline{x}_{k}\in S_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}\{\underline{X}=\underline{x}_{k}\} \right) \\
 & \overset{(\star)}{=}\displaystyle\sum_{y_{h}\in S_{Y}}y_{h}\sum_{\underline{x}_{k}\in S_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}p_{\underline{X}}(\underline{x}_{k})=\sum_{y_{h}\in S_{Y}}\sum_{\underline{x}_{k}\in S_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}y_{h}p_{\underline{X}}(\underline{x}_{k}) \\
 & \overset{(\dagger)}{=}\displaystyle\sum_{y_{h}\in S_{Y}}\sum_{\underline{x}_{k}\in S_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}f(\underline{x}_{k})p_{\underline{X}}(\underline{x}_{k})=\sum_{\underline{x}_{k}\in S_{\underline{X}}}f(\underline{x}_{k})p_{\underline{X}}(\underline{x}_{k})\qquad\Box
\end{array}$$dove in $(\star)$ si ha un'unione finita o numerabile (perché $S_{\underline{X}}$ è un insieme discreto) di eventi disgiunti a due a due, e in $(\dagger)$ si è sostituito $y_{h}$ con $f(\underline{x}_{k})$.
Nell'ultimo passaggio si osservi che prima tutti i valori $\underline{x}_{k}$ erano "raggruppati" in base al valore $y_{h}$ assunto da $f(\underline{x}_{k})$; alla fine non sono più raggruppati.
#### Esempio ($\mathbb{E}[X^{2}]$ senza calcolare $p_{Y}$)
Consideriamo una v.a. $X$ con la seguente densità discreta: $$p_{X}(-2)=\frac{1}{10},\quad p_{X}(-1)=\frac{3}{10},\quad p_{X}(0)=\frac{1}{10},\quad p_{X}(1)=\frac{4}{10},\quad p_{X}(2)=\frac{1}{10}$$Calcolare $\mathbb{E}[Y]$ dove $Y=X^{2}$.
La v.a. $Y$ assume valori in un insieme finito, cioè $S_{Y}=\{0,1,4\}$, e $\mathbb{E}[Y]=0\cdot p_{Y}(0)+1\cdot p_{Y}(1)+4\cdot p_{Y}(4)$. Però **non è necessario** calcolare i valori di $p_{Y}(y)$; infatti per la proposizione precedente (con $m=1$) si ha $$\mathbb{E}[Y]=\mathbb{E}[X^{2}]=(-2)^{2}\cdot \frac{1}{10}+(-1)^{2}\cdot \frac{3}{10}+0^{2}\cdot \frac{1}{10}+1^{2}\cdot \frac{4}{10}+2^{2}\cdot \frac{1}{10}=\frac{4}{10}+\frac{3}{10}+0+\frac{4}{10}+\frac{4}{10}=\frac{15}{10}=\frac{3}{2}$$
#### Esempio (somma di due dadi, in tre modi)
Consideriamo il lancio di due dadi equi e sia $Y=X_{1}+X_{2}$ la v.a. che indica la somma dei due numeri estratti. Calcolare $\mathbb{E}[Y]$.
**1° modo (dalla densità di $Y$).** Facendo riferimento alla [[02 - Modelli discreti#Caso specifico 1 (lancio di due dadi equi)|densità discreta di $Y$ vista in passato]]: $$\mathbb{E}[Y]=\sum_{k=2}^{12}kp_{Y}(k)=2\cdot \frac{1}{36}+3\cdot \frac{2}{36}+4\cdot \frac{3}{36}+5\cdot \frac{4}{36}+6\cdot \frac{5}{36}+7\cdot \frac{6}{36}+8\cdot \frac{5}{36}+9\cdot \frac{4}{36}+10\cdot \frac{3}{36}+11\cdot \frac{2}{36}+12\cdot \frac{1}{36}=\frac{252}{36}=7$$
**2° modo (con la proposizione).** Con $m=2$, $f(x_{1},x_{2})=x_{1}+x_{2}$ e $p_{\underline{X}}(x_{1},x_{2})=\frac{1}{36}$ per $x_{1},x_{2}\in\{1,\dots,6\}$: $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{x_{1},x_{2}=1}^{6}(x_{1}+x_{2})\underset{=1/36}{\underbrace{p_{\underline{X}}(x_{1},x_{2})}}=\frac{1}{36}\sum_{x_{1},x_{2}=1}^{6}(x_{1}+x_{2})=\frac{1}{36}\left\{ \sum_{x_{2}=1}^{6}\sum_{x_{1}=1}^{6}x_{1}+\sum_{x_{1}=1}^{6}\sum_{x_{2}=1}^{6}x_{2} \right\} \\
 & =\frac{1}{36}\left\{ \displaystyle\sum_{x_{2}=1}^{6}\underset{\text{non dipende da }x_{2}}{\underbrace{(1+2+3+4+5+6)}}+\sum_{x_{1}=1}^{6}\underset{\text{non dipende da }x_{1}}{\underbrace{(1+2+3+4+5+6)}} \right\} \\
 & =\frac{1}{36}\{6\cdot 21+6\cdot 21\}=\frac{2\cdot 6\cdot 21}{36}=\frac{252}{36}=7
\end{array}$$
**3° modo (con la [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|linearità]]).** In realtà in questo caso $\mathbb{E}[Y]$ si calcola ancora più facilmente con la linearità (con $n=2$ e $a_{1}=a_{2}=1$): $\mathbb{E}[X_{1}+X_{2}]=\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]$. Infatti entrambe le v.a. $X_{1}$ e $X_{2}$ hanno [[02 - Modelli discreti#Distribuzione uniforme discreta|distribuzione uniforme discreta]] su $\{1,\dots,6\}$ e quindi $$\mathbb{E}[X_{i}]=\sum_{k=1}^{6}k\underset{=1/6}{\underbrace{p_{X_{i}}(k)}}=\frac{1+2+3+4+5+6}{6}=\frac{21}{6}=\frac{7}{2}\quad\text{per }i=1,2$$da cui $\mathbb{E}[X_{1}+X_{2}]=\frac{7}{2}+\frac{7}{2}=7$.
#### Esempio (differenza tra massimo e minimo)
Un'urna ha 4 palline numerate da 1 a 4. Si estraggono 2 palline a caso, una alla volta e **senza** reinserimento. Siano $X_{1}$ e $X_{2}$ le v.a. che indicano [[02 - Modelli discreti#Massimi e minimi di variabili aleatorie discrete|il massimo e il minimo]] tra i due numeri estratti. Calcolare $\mathbb{E}[Y]$ dove $Y=X_{1}-X_{2}$.
Abbiamo $\Omega=\{\omega=(\omega_{1},\omega_{2}):\omega_{1},\omega_{2}\in\{1,2,3,4\}\text{ con }\omega_{1}\neq \omega_{2}\}$ (le estrazioni sono senza reinserimento), e $$X_{1}(\omega)=\max\{\omega_{1},\omega_{2}\},\quad X_{2}(\omega)=\min\{\omega_{1},\omega_{2}\},\quad Y(\omega)=X_{1}(\omega)-X_{2}(\omega)\quad\quad\forall\ \omega\in\Omega$$Per ogni $\omega=(\omega_{1},\omega_{2})$ abbiamo $$P(\{\omega\})=\underset{=1/4}{\underbrace{P(\text{estrarre }\omega_{1})}}\ \underset{=1/3}{\underbrace{P(\text{estrarre }\omega_{2}|\text{è stato estratto }\omega_{1})}}=\frac{1}{12}$$ed inoltre $\#\Omega=12$. In dettaglio: $$\begin{array}{c|ccc}
\omega & X_{1}(\omega) & X_{2}(\omega) & Y(\omega) \\
\hline
(1,2),(2,1) & 2 & 1 & 1 \\
(1,3),(3,1) & 3 & 1 & 2 \\
(1,4),(4,1) & 4 & 1 & 3 \\
(2,3),(3,2) & 3 & 2 & 1 \\
(2,4),(4,2) & 4 & 2 & 2 \\
(3,4),(4,3) & 4 & 3 & 1
\end{array}\quad\quad p_{Y}(y)=\begin{cases}
6/12 & \text{per }y=1 \\
4/12 & \text{per }y=2 \\
2/12 & \text{per }y=3
\end{cases}$$da cui $\mathbb{E}[Y]=1\cdot \frac{6}{12}+2\cdot \frac{4}{12}+3\cdot \frac{2}{12}=\frac{6+8+6}{12}=\frac{20}{12}=\frac{5}{3}$.
Usando la proposizione possiamo **evitare di trattare con $p_{Y}(y)$** e possiamo limitarci a $p_{\underline{X}}(\underline{x})$, che è la seguente (si hanno le 6 coppie che si ottengono dalle 12 coppie precedenti, ordinate come (massimo, minimo); tutte con probabilità $\frac{2}{12}$): $$p_{\underline{X}}(2,1)=p_{\underline{X}}(3,1)=p_{\underline{X}}(4,1)=p_{\underline{X}}(3,2)=p_{\underline{X}}(4,2)=p_{\underline{X}}(4,3)=\frac{2}{12}$$Allora $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{(x_{1},x_{2})}(x_{1}-x_{2})p_{\underline{X}}(x_{1},x_{2}) \\
 & =(2-1)\frac{2}{12}+(3-1)\frac{2}{12}+(4-1)\frac{2}{12}+(3-2)\frac{2}{12}+(4-2)\frac{2}{12}+(4-3)\frac{2}{12} \\
 & =\frac{1\cdot 2+2\cdot 2+3\cdot 2+1\cdot 2+2\cdot 2+1\cdot 2}{12}=\frac{2+4+6+2+4+2}{12}=\frac{20}{12}=\frac{5}{3}
\end{array}$$

> [!warning] Refuso nelle slide
> Nell'elenco dei valori di $p_{\underline{X}}$ (lezione 12, ultima pagina) la coppia $(3,1)$ compare due volte: la prima delle sei deve essere $(2,1)$, come conferma il calcolo successivo, dove il primo addendo è $(2-1)\frac{2}{12}$.
#### Esercizio (lavagna aggiuntiva: tre modi per $\mathbb{E}[X_{1}+X_{2}]$)
Si consideri la densità congiunta di $\underline{X}=(X_{1},X_{2})$ che vale $\frac{1}{10}$ nei punti $(1,1),(1,2),(1,3),(2,1),(3,1)$ e $\frac{1}{2}$ nel punto $(2,2)$. Calcolare $\mathbb{E}[X_{1}+X_{2}]$ (sia $Y=X_{1}+X_{2}$).
**1° modo (densità di $Y$).** $Y$ assume valori in $\{2,3,4\}$ e $$p_{Y}(2)=p_{\underline{X}}(1,1)=\frac{1}{10},\quad p_{Y}(3)=p_{\underline{X}}(1,2)+p_{\underline{X}}(2,1)=\frac{2}{10},\quad p_{Y}(4)=p_{\underline{X}}(1,3)+p_{\underline{X}}(2,2)+p_{\underline{X}}(3,1)=\frac{1}{10}+\frac{1}{2}+\frac{1}{10}=\frac{7}{10}$$(la somma fa 1). Quindi $$\mathbb{E}[Y]=2\cdot\frac{1}{10}+3\cdot\frac{2}{10}+4\cdot\frac{7}{10}=\frac{2+6+28}{10}=\frac{36}{10}=\frac{18}{5}$$
**2° modo (metodo alternativo, con la proposizione).** $$\mathbb{E}[Y]=(1+1)\tfrac{1}{10}+(1+2)\tfrac{1}{10}+(2+1)\tfrac{1}{10}+(3+1)\tfrac{1}{10}+(2+2)\tfrac{1}{2}+(1+3)\tfrac{1}{10}=\frac{2+3+3+4+20+4}{10}=\frac{36}{10}=\frac{18}{5}$$
**3° modo (metodo alternativo ulteriore, con la linearità).** $\mathbb{E}[Y]=\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]$; bisogna trovare le marginali: $p_{X_{1}}(1)=\frac{3}{10}$, $p_{X_{1}}(2)=\frac{6}{10}$, $p_{X_{1}}(3)=\frac{1}{10}$, e $X_{2}$ ha la stessa densità. Allora $$\mathbb{E}[X_{1}]=\mathbb{E}[X_{2}]=1\cdot\frac{3}{10}+2\cdot\frac{6}{10}+3\cdot\frac{1}{10}=\frac{3+12+3}{10}=\frac{18}{10}\ \implies\ \mathbb{E}[Y]=\frac{18}{10}+\frac{18}{10}=\frac{36}{10}=\frac{18}{5}$$

> [!question] Domanda tipica d'esame
> Come si calcola $\mathbb{E}[f(\underline{X})]$ senza conoscere la densità di $Y=f(\underline{X})$? Con quali metodi si ottiene $\mathbb{E}[X_{1}+X_{2}]$?
> **Risposta.** $\mathbb{E}[Y]=\sum_{\underline{x}_{k}\in S_{\underline{X}}}f(\underline{x}_{k})p_{\underline{X}}(\underline{x}_{k})$ (se $Y$ ha speranza finita). Per $\mathbb{E}[X_{1}+X_{2}]$: dalla densità di $Y$, con la formula precedente, oppure con la linearità $\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]$ (che non richiede l'indipendenza).

--- Fine lezione 12 ---
## Speranza matematica delle distribuzioni discrete notevoli
Calcolo di $\mathbb{E}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica (e traslata), binomiale negativa (e traslata). Le distribuzioni sono quelle definite in [[02 - Modelli discreti]].

> [!quote] Tabella riassuntiva *(extra, non da slide)*
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
### 1) Distribuzione bernoulliana: $X\sim B(p)$
$S_{X}=\{0,1\}$ è un insieme finito, quindi la [[03 - Speranza matematica e momenti#Definizione|condizione $(*)$]] è verificata. Con $p_{X}(0)=1-p$ e $p_{X}(1)=p$ si ha $$\mathbb{E}[X]=0\cdot p_{X}(0)+1\cdot p_{X}(1)=0\cdot(1-p)+1\cdot p=\begin{bmatrix}p\end{bmatrix}$$

> [!quote] Conseguenza importante
> Se $X=1_{A}$ (funzione indicatrice dell'evento $A\in\mathcal{A}$), allora $$\mathbb{E}[1_{A}]=P(A)$$
### 2) Distribuzione binomiale: $X\sim BIN(n,p)$
$S_{X}=\{0,1,\dots,n\}$ è un insieme finito, quindi $(*)$ è verificata. Si ha $$\begin{array}{ll}
\mathbb{E}[X] & =\displaystyle\sum_{k=0}^{n}k\binom{n}{k}p^{k}(1-p)^{n-k}=\sum_{k=1}^{n}\cancel{k}\frac{n!}{\cancel{k!}(n-k)!}p^{k}(1-p)^{n-k} \\
 & =\displaystyle\sum_{k=1}^{n}\frac{n(n-1)!}{(k-1)!(n-1-(k-1))!}p^{k-1+1}(1-p)^{n-1-(k-1)} \\
 & \underset{h=k-1}{=}np\displaystyle\sum_{h=0}^{n-1}\binom{n-1}{h}p^{h}(1-p)^{n-1-h}\overset{\text{binomio di Newton}}{=}np(p+1-p)^{n-1}=\begin{bmatrix}np\end{bmatrix}
\end{array}$$
#### Dimostrazione alternativa (con la linearità)
Il risultato $X\sim BIN(n,p)\implies \mathbb{E}[X]=np$ si può dimostrare in maniera alternativa come segue.
Ricordiamo che una maniera canonica per ottenere una $X\sim BIN(n,p)$ è la seguente: $$\Omega=\underset{n\text{ volte}}{\underbrace{\{0,1\}\times\dots\times\{0,1\}}}\quad\quad P(\{\omega\})=p^{X(\omega)}(1-p)^{n-X(\omega)}\quad\text{dove }X(\omega)=\sum_{i=1}^{n}\omega_{i}$$per ogni $\omega=(\omega_{1},\dots,\omega_{n})\in\Omega$. Allora possiamo considerare le v.a. più semplici $X_{1},\dots,X_{n}:\Omega\to \mathbb{R}$ tali che $X_{i}(\omega)=\omega_{i}$ per ogni $\omega\in\Omega$, con $i=1,\dots,n$.
In corrispondenza si ha $$\begin{cases}
X=X_{1}+\dots+X_{n} & (\text{per costruzione}) \\
\mathbb{E}[X_{i}]=P(X_{i}=1)=p & (\text{per quanto detto nella bernoulliana, }\forall\ i=1,\dots,n)
\end{cases}$$Allora, per la [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|linearità]], $$\mathbb{E}[X]=\mathbb{E}[X_{1}+\dots+X_{n}]=\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{n}]=\underset{n\text{ volte}}{\underbrace{p+\dots+p}}=np$$
### 3) Distribuzione ipergeometrica
$S_{X}=\{0,1,\dots,n\}$ è un insieme finito, quindi $(*)$ è verificata. La densità è $$p_{X}(k)=\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}\quad\text{per }k\in S_{X},\ \text{con }n<n_{1}+n_{2}$$Per definizione si avrebbe $$\mathbb{E}[X]=\sum_{k=0}^{n}k\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}$$ma anche qui bisognerebbe gestire l'espressione con i fattoriali: **il prof non lo fa**.
Consideriamo invece il procedimento alternativo visto per la [[02 - Modelli discreti#Caso 1): distribuzione binomiale|binomiale]]. Anche in questo caso (pensando alle estrazioni **senza** reinserimento) si ha $X=X_{1}+\dots+X_{n}$ dove $$X_{i}=\begin{cases}
1 & \text{estratta pallina di tipo 1} \\
0 & \text{estratta pallina di tipo 2}
\end{cases}\ \sim B\left( \frac{n_{1}}{n_{1}+n_{2}} \right)\quad\quad\forall\ i\in\{1,\dots,n\}$$Allora, per la linearità, $$\mathbb{E}[X]=\mathbb{E}[X_{1}+\dots+X_{n}]=\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{n}]=\underset{n\text{ volte}}{\underbrace{\frac{n_{1}}{n_{1}+n_{2}}+\dots+\frac{n_{1}}{n_{1}+n_{2}}}}=\begin{bmatrix}n\frac{n_{1}}{n_{1}+n_{2}}\end{bmatrix}$$
#### Commenti
- C'è una **differenza** tra i due approcci alternativi visti per binomiale e [[02 - Modelli discreti#Caso 2): distribuzione ipergeometrica|ipergeometrica]]: $$\begin{cases}
X_{1},\dots,X_{n}\text{ indipendenti nel 1° caso} \\
X_{1},\dots,X_{n}\ \textbf{non}\text{ indipendenti nel 2° caso}
\end{cases}$$Questo non ha influenza sui risultati, che coincidono se poniamo $p=\frac{n_{1}}{n_{1}+n_{2}}$. Al contrario ci sarà una differenza nel caso della **varianza**, di cui si parlerà prossimamente.
- I risultati ottenuti ci dicono che, nel caso di un numero finito di estrazioni casuali, **la media della v.a. che conta il numero di oggetti di un certo tipo estratti non cambia se le estrazioni sono con o senza reinserimento**.
- In generale $\mathbb{E}[X]$ dipende dalla **distribuzione** di $X$, e non da come è fatta $X:\Omega\to \mathbb{R}$. In effetti, nel caso discreto (l'unico visto finora), $\mathbb{E}[X]$ dipende solo dalla densità discreta $p_{X}$. Quindi quel che abbiamo visto per l'ipergeometrica, con riferimento alle estrazioni casuali senza reinserimento, vale anche per le [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]].
### 4) Distribuzione di Poisson: $X\sim POISSON(\lambda)$
$S_{X}=\{0,1,2,\dots\}$ è un insieme **non finito**, quindi la condizione $(*)$ va verificata: $\sum_{k\geq 0}|k|p_{X}(k)<\infty$.

> [!info] Qui il valore assoluto è superfluo
> I valori assunti sono tutti $\geq 0$, quindi si può calcolare la serie senza valore assoluto.

$$\sum_{k\geq 0}k\frac{\lambda^{k}}{k!}e^{-\lambda}=\sum_{k\geq 1}\cancel{k}\frac{\lambda^{k-1+1}}{\cancel{k}\cdot(k-1)!}e^{-\lambda}=\lambda\sum_{k\geq 1}\frac{\lambda^{k-1}}{(k-1)!}e^{-\lambda}\underset{h=k-1}{=}\lambda\underset{=1}{\underbrace{\sum_{h\geq 0}\frac{\lambda^{h}}{h!}e^{-\lambda}}}=\lambda$$Quindi vale $(*)$ perché $\lambda<\infty$, ed inoltre $\begin{bmatrix}\mathbb{E}[X]=\lambda\end{bmatrix}$.
### 5) Distribuzione geometrica: $X\sim Geo(p)$
$S_{X}=\{0,1,2,\dots\}$ è un insieme non finito; anche qui il valore assoluto è superfluo perché i valori assunti sono $\geq 0$.
Partiamo dalla condizione di normalizzazione: $$\sum_{k\geq 0}(1-p)^{k}p=1\implies p\sum_{k\geq 0}(1-p)^{k}=1\implies \sum_{k\geq 0}(1-p)^{k}=\frac{1}{p}$$Allora, **derivando rispetto a $p$** (questo è un caso in cui la derivata della serie coincide con la serie delle derivate), si ha $$\sum_{k\geq 0}k(1-p)^{k-1}(-1)=-p^{-2}\quad\underset{\text{i segni meno si cancellano}}{\implies}\quad\sum_{k\geq 0}k(1-p)^{k-1}=\frac{1}{p^{2}}$$e moltiplicando membro a membro per $p(1-p)$ si ottiene $$\sum_{k\geq 0}k(1-p)^{k}p=\frac{(1-p)p}{p^{2}}=\frac{1-p}{p}=\frac{1}{p}-1$$Quindi vale $(*)$ perché $\frac{1}{p}-1<\infty$ (si osservi che $p\neq 0$), ed inoltre $\begin{bmatrix}\mathbb{E}[X]=\frac{1}{p}-1\end{bmatrix}$.
### 6) Distribuzione geometrica traslata: $Y\sim GeoTraslata(p)$
Qui, invece di procedere con la definizione (si dovrebbe fare riferimento alla serie $\sum_{k\geq 1}k(1-p)^{k-1}p$, sia per la condizione $(*)$ sia per il calcolo di $\mathbb{E}[Y]$), osserviamo che $$Y=X+1\quad\text{con }X\sim Geo(p)$$Allora, per la linearità, $$\mathbb{E}[Y]=\mathbb{E}[X+1]=\underset{=\frac{1}{p}-1\ (\text{calcolato prima})}{\underbrace{\mathbb{E}[X]}}+\underset{=1}{\underbrace{\mathbb{E}[1]}}=\frac{1}{p}-1+1=\begin{bmatrix}\frac{1}{p}\end{bmatrix}$$
### 7) Binomiale negativa e binomiale negativa traslata
Anche in questo caso non faremo riferimento alla definizione (si dovrebbero considerare le serie $\sum_{k\geq 0}k\binom{k+r-1}{r-1}p^{r}(1-p)^{k}$ e $\sum_{h\geq r}h\binom{h-1}{r-1}p^{r}(1-p)^{h-r}$).
Al contrario consideriamo le [[02 - Modelli discreti#Un legame tra binomiale negativa (traslata) e geometrica (traslata)|somme di geometriche (e geometriche traslate)]] opportune viste in passato, e usiamo la linearità: $$\begin{array}{ll}
X=\underset{Geo(p)\text{ indip.}}{\underbrace{X_{1}+\dots+X_{r}}} & \implies\ \mathbb{E}[X]\overset{\text{lin.}}{=}\mathbb{E}[X_{1}]+\dots+\mathbb{E}[X_{r}]=\underset{r\text{ volte}}{\underbrace{\frac{1}{p}-1+\dots+\frac{1}{p}-1}}=\begin{bmatrix}r\left( \frac{1}{p}-1 \right)\end{bmatrix} \\
Y=\underset{GeoTraslata(p)\text{ indip.}}{\underbrace{Y_{1}+\dots+Y_{r}}} & \implies\ \mathbb{E}[Y]\overset{\text{lin.}}{=}\mathbb{E}[Y_{1}]+\dots+\mathbb{E}[Y_{r}]=\underset{r\text{ volte}}{\underbrace{\frac{1}{p}+\dots+\frac{1}{p}}}=\begin{bmatrix}\frac{r}{p}\end{bmatrix}
\end{array}$$
#### Verifica di coerenza
I valori ottenuti $\mathbb{E}[Y]=\frac{r}{p}$ e $\mathbb{E}[X]=r\left( \frac{1}{p}-1 \right)$ sono in accordo con altre formule. Infatti si ha $Y=X+r$, da cui segue (per linearità) $\mathbb{E}[Y]=\mathbb{E}[X+r]=\mathbb{E}[X]+r$. In effetti $$\underset{=\frac{r}{p}}{\underbrace{\mathbb{E}[Y]}}=\underset{=r\left( \frac{1}{p}-1 \right)=\frac{r}{p}-\cancel{r}+\cancel{r}}{\underbrace{\mathbb{E}[X]+r}}\quad\text{ok}$$

> [!question] Domanda tipica d'esame
> Come si ottiene la media di una ipergeometrica? Perché coincide con quella della binomiale?
> **Risposta.** Si scrive $X=X_{1}+\dots+X_{n}$ con $X_{i}\sim B\left(\frac{n_{1}}{n_{1}+n_{2}}\right)$ (non indipendenti) e per linearità $\mathbb{E}[X]=n\frac{n_{1}}{n_{1}+n_{2}}$, che è $np$ con $p=\frac{n_{1}}{n_{1}+n_{2}}$: la linearità non richiede l'indipendenza, quindi con o senza reinserimento la media è la stessa.

--- Fine parte sulle speranze notevoli (lezione 13, pp. 1-9) ---
## Varianza e momenti di una variabile aleatoria discreta
Definizione di momento e momento centrato, varianza e scarto quadratico medio, proprietà, disuguaglianza di Chebyshev e formule di calcolo.

> [!info] Valgono in generale
> Le definizioni che seguono possono essere date **anche se $X$ non è discreta**. Qui pensiamo solo al caso discreto (l'unico visto finora), ma i risultati valgono in generale.
### Momenti e momento centrato
Sia $X$ una v.a. e sia $k\geq 1$ intero.
- Il **momento $k$-esimo** di $X$ è (se esiste finito) $$\mathbb{E}[X^{k}]$$
- Il **momento centrato $k$-esimo** di $X$ è (se esiste finito) $$\mathbb{E}[(X-\mathbb{E}[X])^{k}]$$
### Varianza
La **varianza** di $X$ è (se esiste finita) il momento centrato di ordine $2$: $$\begin{bmatrix}
\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]
\end{bmatrix}$$

> [!info] Terminologia
> Si usa il termine **scarto quadratico medio** di una v.a. $X$ per $\sqrt{\text{Var}[X]}$.
### Proprietà della varianza
Per la [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|monotonia del valore medio]], ed essendo $(X-\mathbb{E}[X])^{2}\geq 0$, si ha $$\mathbb{E}[(X-\mathbb{E}[X])^{2}]\geq \mathbb{E}[0]\quad\implies\quad \text{Var}[X]\geq 0$$In realtà si può dire di più: $$\text{Var}[X]=0\iff X\text{ è una v.a. costante}\iff X=\mathbb{E}[X]$$dove per "costante" si intende il caso in cui esiste $x_{0}\in \mathbb{R}$ tale che $p_{X}(x_{0})=1$; in corrispondenza si ha $x_{0}=\mathbb{E}[X]$.

> [!info] Minimo ma non massimo
> La varianza ha un **valore minimo** (cioè $0$); al contrario **non** ammette un valore massimo.

In ogni modo possiamo dire che:
- varianza **piccola** $\to$ distribuzione concentrata vicino alla media;
- varianza **grande** $\to$ distribuzione non concentrata vicino alla media.
### Disuguaglianza di Chebyshev
Per comprendere meglio il legame tra varianza e concentrazione presentiamo il seguente risultato.

> [!quote] Disuguaglianza di Chebyshev
> Per ogni v.a. $X$ con media e varianza finite (vale anche per v.a. non discrete), si ha $$\begin{bmatrix}
> \forall\ a>0\qquad P(|X-\mathbb{E}[X]|\geq a)\leq \frac{\text{Var}[X]}{a^{2}}
> \end{bmatrix}$$

> [!info] Sul nome
> Pafnutij L'vovič Čebyšëv (1821-1894) è stato un matematico e statistico russo. Il suo nome si trova traslitterato in vari modi (Chebychev, Chebyshev, Cebisceff, Tchebycheff, …).

**Osservazione (quando è banale).** Se $\frac{\text{Var}[X]}{a^{2}}\geq 1$ (questo può accadere se $a$ è abbastanza vicino a zero) si ha una disuguaglianza banale, perché il primo membro è comunque in $[0,1]$.
**Osservazione (lettura dell'evento).** La disuguaglianza dice che l'evento $$\{|X-\mathbb{E}[X]|\geq a\}=\{X-\mathbb{E}[X]\geq a\}\cup\{X-\mathbb{E}[X]\leq -a\}=\{X\geq \mathbb{E}[X]+a\}\cup\{X\leq \mathbb{E}[X]-a\}$$(cioè "$X$ dista da $\mathbb{E}[X]$ almeno $a$") ha una probabilità che non può essere troppo grande, e diventa piccola se $\text{Var}[X]$ è piccola.
#### Dimostrazione (caso discreto)
Per il caso generale il procedimento è simile. Partiamo dalla definizione, usando la [[03 - Speranza matematica e momenti#Proposizione (speranza di una trasformazione)|formula per la speranza di una trasformazione di $X$]] e l'osservazione che $z^{2}=|z|^{2}$ per ogni $z\in \mathbb{R}$: $$\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\sum_{x_{k}\in S_{X}}(x_{k}-\mathbb{E}[X])^{2}p_{X}(x_{k})=\underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in S_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}p_{X}(x_{k})+\underset{|x_{k}-\mathbb{E}[X]|<a}{\sum_{x_{k}\in S_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}p_{X}(x_{k})$$Essendo le due sommatorie non negative (somme di quadrati), si ottiene una minorazione togliendo la seconda: $$\text{Var}[X]\geq \underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in S_{X}:}}|x_{k}-\mathbb{E}[X]|^{2}p_{X}(x_{k})\geq \underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in S_{X}:}}a^{2}p_{X}(x_{k})=a^{2}\underset{|x_{k}-\mathbb{E}[X]|\geq a}{\sum_{x_{k}\in S_{X}:}}p_{X}(x_{k})=a^{2}P(|X-\mathbb{E}[X]|\geq a)$$dove nella seconda disuguaglianza si è usato $|x_{k}-\mathbb{E}[X]|\geq a\implies|x_{k}-\mathbb{E}[X]|^{2}\geq a^{2}$. Dividendo membro a membro per $a^{2}$ si ottiene $$\frac{\text{Var}[X]}{a^{2}}\geq P(|X-\mathbb{E}[X]|\geq a)\qquad\Box$$
### Alcune formule per la varianza
Valgono non solo per il caso discreto.

> [!info] Notazione
> Nel seguito si scrive $\mathbb{E}^{2}[X]$ anziché $(\mathbb{E}[X])^{2}$.
#### 1) Formula alternativa per la varianza
$$\text{Var}[X]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\mathbb{E}[X^{2}-2X\cdot \mathbb{E}[X]+\mathbb{E}^{2}[X]]\overset{\text{lin.}}{=}\mathbb{E}[X^{2}]-2\underset{=\mathbb{E}^{2}[X]}{\underbrace{\mathbb{E}[X]\cdot \mathbb{E}[X]}}+\mathbb{E}^{2}[X]=\begin{bmatrix}\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]\end{bmatrix}$$(si è usata la [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|linearità]] e il fatto che $\mathbb{E}[X]$ è una costante).
#### 2) $\text{Var}[aX]=a^{2}\text{Var}[X]$ (per $a\in \mathbb{R}$)
**1° modo (dalla definizione).** $$\text{Var}[aX]=\mathbb{E}[(aX-\mathbb{E}[aX])^{2}]=\mathbb{E}[(aX-a\mathbb{E}[X])^{2}]=\mathbb{E}[a^{2}(X-\mathbb{E}[X])^{2}]\overset{\text{lin.}}{=}a^{2}\underset{=\text{Var}[X]}{\underbrace{\mathbb{E}[(X-\mathbb{E}[X])^{2}]}}=a^{2}\text{Var}[X]$$**2° modo (con la formula alternativa).** $$\text{Var}[aX]=\mathbb{E}[(aX)^{2}]-\mathbb{E}^{2}[aX]=\mathbb{E}[a^{2}X^{2}]-(a\mathbb{E}[X])^{2}=a^{2}\mathbb{E}[X^{2}]-a^{2}\mathbb{E}^{2}[X]=a^{2}(\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X])=a^{2}\text{Var}[X]$$
#### 3) Invarianza per traslazione della varianza
$$\text{Var}[X+a]=\mathbb{E}[(X+a-\underset{=\mathbb{E}[X]+a}{\underbrace{\mathbb{E}[X+a]}})^{2}]=\mathbb{E}[(X+\cancel{a}-\mathbb{E}[X]-\cancel{a})^{2}]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\text{Var}[X]$$(anche in questo caso si può fare una dimostrazione alternativa con la formula alternativa).

> [!quote] Interpretazione
> Traslando la v.a. di una costante $a$, la densità si sposta rigidamente (da $x_{k}$ a $x_{k}+a$) e la media si sposta con essa (da $\mathbb{E}[X]$ a $\mathbb{E}[X]+a$). In entrambi i casi la distribuzione si "disperde" rispetto alla propria media nello stesso modo: quindi non sorprende che si abbia la stessa varianza.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare (caso discreto) la disuguaglianza di Chebyshev.
> **Risposta.** Per ogni v.a. con media e varianza finite, $\forall\ a>0$: $P(|X-\mathbb{E}[X]|\geq a)\leq \frac{\text{Var}[X]}{a^{2}}$. Si spezza $\text{Var}[X]=\sum(x_{k}-\mathbb{E}[X])^{2}p_{X}(x_{k})$ nei termini con $|x_{k}-\mathbb{E}[X]|\geq a$ e con $<a$; si scarta il secondo (non negativo) e nel primo si usa $|x_{k}-\mathbb{E}[X]|^{2}\geq a^{2}$, ottenendo $\text{Var}[X]\geq a^{2}P(|X-\mathbb{E}[X]|\geq a)$ (si veda [[03 - Speranza matematica e momenti#Disuguaglianza di Chebyshev]]).
## Covarianza di variabili aleatorie discrete
Varianza di una somma, definizione di covarianza, formule di calcolo, interpretazione geometrica ed esercizio riassuntivo.
### Varianza di una somma e introduzione alla covarianza
Si vuole dare una formula per $\text{Var}[X_{1}+X_{2}]$, dove entrambe le v.a. sono **[[03 - Speranza matematica e momenti#Proprietà della varianza|non costanti]]** (se ad esempio $X_{2}$ fosse costante, per quanto [[03 - Speranza matematica e momenti#3) Invarianza per traslazione della varianza|visto in precedenza]] si avrebbe $\text{Var}[X_{1}]$). Si ha $$\begin{array}{ll}
\text{Var}[X_{1}+X_{2}] & =\mathbb{E}[(X_{1}+X_{2}-\underset{=\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]}{\underbrace{\mathbb{E}[X_{1}+X_{2}]}})^{2}]=\mathbb{E}[(\underset{\text{quadrato di binomio}}{\underbrace{(X_{1}-\mathbb{E}[X_{1}])+(X_{2}-\mathbb{E}[X_{2}])}})^{2}] \\
 & \overset{\text{lin.}}{=}\underset{=\text{Var}[X_{1}]}{\underbrace{\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])^{2}]}}+\underset{=\text{Var}[X_{2}]}{\underbrace{\mathbb{E}[(X_{2}-\mathbb{E}[X_{2}])^{2}]}}+2\underset{\overset{\text{def}}{=}\text{Cov}(X_{1},X_{2})}{\underbrace{\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]}}
\end{array}$$dove l'ultimo termine è per definizione la **covarianza** tra $X_{1}$ e $X_{2}$. Quindi $$\begin{bmatrix}
\text{Var}[X_{1}+X_{2}]=\text{Var}[X_{1}]+\text{Var}[X_{2}]+2\text{Cov}(X_{1},X_{2})
\end{bmatrix}$$

> [!info] Analogia
> La struttura ricalca il **quadrato di binomio** $(a+b)^{2}=a^{2}+b^{2}+2ab$.

Si ha una formula più generale nel caso di $m$ addendi: $$\text{Var}[X_{1}+\dots+X_{m}]=\sum_{i=1}^{m}\text{Var}[X_{i}]+2\underset{i<j}{\sum_{i,j=1}^{m}}\text{Cov}(X_{i},X_{j})$$(anche perché $\text{Cov}(\cdot,\cdot)$ è simmetrica, come si vede qui di seguito).
### Definizione di covarianza
La **covarianza** tra due v.a. $X_{1}$ e $X_{2}$ definite su uno stesso spazio di probabilità è (se esiste finita) $$\begin{bmatrix}
\text{Cov}(X_{1},X_{2})=\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]
\end{bmatrix}$$
### Alcune formule per la covarianza
Valgono non solo per il caso discreto.
#### 1) Formula alternativa per la covarianza
$$\begin{array}{ll}
\text{Cov}(X_{1},X_{2}) & =\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]=\mathbb{E}[X_{1}X_{2}-X_{1}\mathbb{E}[X_{2}]-X_{2}\mathbb{E}[X_{1}]+\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]] \\
 & \overset{\text{lin.}}{=}\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]+\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\begin{bmatrix}\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]\end{bmatrix}
\end{array}$$
#### 2) Simmetria: $\text{Cov}(X_{1},X_{2})=\text{Cov}(X_{2},X_{1})$
Dalla definizione, essendo il prodotto tra numeri reali commutativo: $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[(X_{1}-\mathbb{E}[X_{1}])(X_{2}-\mathbb{E}[X_{2}])]=\mathbb{E}[(X_{2}-\mathbb{E}[X_{2}])(X_{1}-\mathbb{E}[X_{1}])]=\text{Cov}(X_{2},X_{1})$$oppure, con la formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\mathbb{E}[X_{2}X_{1}]-\mathbb{E}[X_{2}]\mathbb{E}[X_{1}]=\text{Cov}(X_{2},X_{1})$.
#### 3) $\text{Cov}(X,X)=\text{Var}[X]$
$$\text{Cov}(X,X)=\mathbb{E}[(X-\mathbb{E}[X])(X-\mathbb{E}[X])]=\mathbb{E}[(X-\mathbb{E}[X])^{2}]=\text{Var}[X]$$oppure, con la formula alternativa: $\text{Cov}(X,X)=\mathbb{E}[X\cdot X]-\mathbb{E}[X]\cdot \mathbb{E}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=\text{Var}[X]$.

> [!info] Estensioni
> Si potrebbero dare altre formule per espressioni del tipo $\text{Cov}(a_{1}X_{1}+b_{1},a_{2}X_{2}+b_{2})$, con $a_{1},a_{2},b_{1},b_{2}\in \mathbb{R}$ costanti.

> [!warning] La covarianza può essere negativa
> A differenza della varianza, la covarianza può assumere **anche valori negativi**.
### Interpretazione geometrica (caso discreto)
Ci limitiamo al caso discreto, anche se ragionamenti simili valgono nel caso generale. Dalla [[03 - Speranza matematica e momenti#Definizione di covarianza|definizione]] si ha $$\text{Cov}(X_{1},X_{2})=\sum_{x_{1},x_{2}}(x_{1}-\mathbb{E}[X_{1}])(x_{2}-\mathbb{E}[X_{2}])\underset{\geq 0}{\underbrace{p_{X_{1},X_{2}}(x_{1},x_{2})}}$$Sul piano $(x_{1},x_{2})$ le rette $x_{1}=\mathbb{E}[X_{1}]$ e $x_{2}=\mathbb{E}[X_{2}]$ individuano quattro quadranti (numerati $\text{I}^{\circ},\text{II}^{\circ},\text{III}^{\circ},\text{IV}^{\circ}$ in senso antiorario a partire da quello in alto a destra *(extra, non da slide)*). Poiché la probabilità è $\geq 0$, il segno di ogni addendo dipende dal prodotto $(x_{1}-\mathbb{E}[X_{1}])(x_{2}-\mathbb{E}[X_{2}])$:
- addendi **positivi** $\to$ punti $(x_{1},x_{2})$ nel $\text{I}^{\circ}$ e nel $\text{III}^{\circ}$ quadrante;
- addendi **negativi** $\to$ punti nel $\text{II}^{\circ}$ e nel $\text{IV}^{\circ}$ quadrante;
- addendi **nulli** $\to$ punti sulle due rette.

Quindi $\text{Cov}(X_{1},X_{2})>0$ se gli addendi positivi prevalgono su quelli negativi, $\text{Cov}(X_{1},X_{2})<0$ se si ha il viceversa, e $\text{Cov}(X_{1},X_{2})=0$ se i due contributi si compensano.
### Esercizio (media, varianza e covarianza da una densità congiunta)
Sia $\underline{X}=(X_{1},X_{2})$ una v.a. discreta con la seguente densità congiunta: $$p_{\underline{X}}(0,1)=p_{\underline{X}}(0,2)=p_{\underline{X}}(1,0)=p_{\underline{X}}(2,0)=p_{\underline{X}}(3,0)=\frac{1}{5}$$Calcolare $\mathbb{E}[X_{1}]$, $\mathbb{E}[X_{2}]$, $\text{Var}[X_{1}]$, $\text{Var}[X_{2}]$, $\text{Cov}(X_{1},X_{2})$.
**Densità marginale di $X_{1}$** (si sommano le congiunte a $x_{1}$ fissato): $$\begin{cases}
p_{X_{1}}(0)=p_{\underline{X}}(0,1)+p_{\underline{X}}(0,2)=\frac{1}{5}+\frac{1}{5}=\frac{2}{5} \\
p_{X_{1}}(1)=p_{\underline{X}}(1,0)=\frac{1}{5} \\
p_{X_{1}}(2)=p_{\underline{X}}(2,0)=\frac{1}{5} \\
p_{X_{1}}(3)=p_{\underline{X}}(3,0)=\frac{1}{5}
\end{cases}$$da cui $$\mathbb{E}[X_{1}]=0\cdot \frac{2}{5}+1\cdot \frac{1}{5}+2\cdot \frac{1}{5}+3\cdot \frac{1}{5}=\frac{6}{5}$$ $$\text{Var}[X_{1}]=\mathbb{E}[X_{1}^{2}]-\mathbb{E}^{2}[X_{1}]=0^{2}\cdot \frac{2}{5}+1^{2}\cdot \frac{1}{5}+2^{2}\cdot \frac{1}{5}+3^{2}\cdot \frac{1}{5}-\left( \frac{6}{5} \right)^{2}=\frac{14}{5}-\frac{36}{25}=\frac{70-36}{25}=\frac{34}{25}$$
**Densità marginale di $X_{2}$**: $$\begin{cases}
p_{X_{2}}(0)=p_{\underline{X}}(1,0)+p_{\underline{X}}(2,0)+p_{\underline{X}}(3,0)=\frac{1}{5}+\frac{1}{5}+\frac{1}{5}=\frac{3}{5} \\
p_{X_{2}}(1)=p_{\underline{X}}(0,1)=\frac{1}{5} \\
p_{X_{2}}(2)=p_{\underline{X}}(0,2)=\frac{1}{5}
\end{cases}$$da cui $$\mathbb{E}[X_{2}]=0\cdot \frac{3}{5}+1\cdot \frac{1}{5}+2\cdot \frac{1}{5}=\frac{3}{5}$$ $$\text{Var}[X_{2}]=\mathbb{E}[X_{2}^{2}]-\mathbb{E}^{2}[X_{2}]=0^{2}\cdot \frac{3}{5}+1^{2}\cdot \frac{1}{5}+2^{2}\cdot \frac{1}{5}-\left( \frac{3}{5} \right)^{2}=\frac{5}{5}-\frac{9}{25}=\frac{25-9}{25}=\frac{16}{25}$$

> [!info] Coerenza *(extra, non da slide)*
> $\text{Var}[X_{2}]<\text{Var}[X_{1}]$ non sorprende: $X_{2}$ assume valori più concentrati ($\{0,1,2\}$) rispetto a $X_{1}$ ($\{0,1,2,3\}$).

**Covarianza.** Con la [[#1) Formula alternativa per la covarianza|formula alternativa]] serve $\mathbb{E}[X_{1}X_{2}]$: $$\mathbb{E}[X_{1}X_{2}]=\sum_{\underline{x}\in S_{\underline{X}}}x_{1}x_{2}p_{\underline{X}}(x_{1},x_{2})=0\cdot 1\cdot \frac{1}{5}+0\cdot 2\cdot \frac{1}{5}+1\cdot 0\cdot \frac{1}{5}+2\cdot 0\cdot \frac{1}{5}+3\cdot 0\cdot \frac{1}{5}=0$$(in ogni coppia con probabilità non nulla almeno una tra $x_{1}$ e $x_{2}$ è zero). Allora $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=0-\frac{6}{5}\cdot \frac{3}{5}=\begin{bmatrix}-\frac{18}{25}\end{bmatrix}$$

> [!info] Anticipazione
> Quando si parlerà di **rette di regressione** si potrà dire che $\text{Cov}(X_{1},X_{2})<0$ non sorprende.

> [!question] Domanda tipica d'esame
> Scrivere la formula per $\text{Var}[X_{1}+X_{2}]$ e la formula alternativa per la covarianza.
> **Risposta.** $\text{Var}[X_{1}+X_{2}]=\text{Var}[X_{1}]+\text{Var}[X_{2}]+2\text{Cov}(X_{1},X_{2})$ e $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$. La covarianza è simmetrica, $\text{Cov}(X,X)=\text{Var}[X]$ e può essere negativa.

--- Fine lezione 13 ---
## Indipendenza e covarianza
Legame tra indipendenza e covarianza nulla: l'implicazione vale in un verso solo, con un controesempio per il verso opposto.
### Proposizione (indipendenza $\implies$ covarianza nulla)
Siano $X_{1}$ e $X_{2}$ due v.a. definite su uno stesso spazio di probabilità, con medie finite e non necessariamente discrete. Allora $$\begin{bmatrix}
X_{1}\text{ e }X_{2}\text{ indipendenti}\implies \text{Cov}(X_{1},X_{2})=0
\end{bmatrix}$$
#### Dimostrazione
Segue da una [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|cosa detta in passato]], cioè $$X_{1}\text{ e }X_{2}\text{ indipendenti}\implies \mathbb{E}[X_{1}X_{2}]=\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$$e dalla [[03 - Speranza matematica e momenti#1) Formula alternativa per la covarianza|formula alternativa della covarianza]] $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=0\qquad\Box$$
### Conseguenza (varianza di una somma di v.a. indipendenti)
Se $X_{1},\dots,X_{m}$ sono **indipendenti**, allora nella [[03 - Speranza matematica e momenti#Varianza di una somma e introduzione alla covarianza|formula generale per la varianza di una somma]] tutti i termini $\text{Cov}(X_{i},X_{j})$ (con $i<j$) si annullano, e quindi $$\begin{bmatrix}
\text{Var}[X_{1}+\dots+X_{m}]=\sum_{i=1}^{m}\text{Var}[X_{i}]+2\underset{i<j}{\sum_{i,j=1}^{m}}\underset{=0}{\underbrace{\text{Cov}(X_{i},X_{j})}}=\sum_{i=1}^{m}\text{Var}[X_{i}]
\end{bmatrix}$$
### Il viceversa è falso: $\text{Cov}=0\ \not\Rightarrow\ $ indipendenza
Presentiamo una classe di controesempi (ce ne sono anche altri) per cui $$\text{Cov}(X_{1},X_{2})=0\quad\not\Rightarrow\quad X_{1}\text{ e }X_{2}\text{ sono indipendenti}$$Consideriamo $$X_{1}=X\qquad\text{e}\qquad X_{2}=X^{2}$$dove $X$ è una v.a. tale che:
- $X$ è una v.a. **simmetrica** (cioè tale che $X$ e $-X$ sono equidistribuite, cioè hanno la stessa distribuzione; se $X$ è discreta, $X$ e $-X$ hanno la stessa densità discreta);
- $X^{2}$ ha speranza matematica finita;
- $X^{2}$ **non** è una v.a. costante (infatti si può dimostrare che ogni v.a. costante è indipendente da qualunque altra v.a.).
#### I momenti dispari di una v.a. simmetrica sono nulli
Se $X$ è simmetrica si ha $\mathbb{E}[X^{k}]=0$ per ogni $k$ intero **dispari**. Infatti $$\mathbb{E}[X^{k}]=\sum_{x_{h}\in S_{X}}x_{h}^{k}p_{X}(x_{h})=0\quad\text{perché:}$$
- se si ha $x_{h}=0$, l'addendo $x_{h}^{k}p_{X}(x_{h})=0^{k}\cdot p_{X}(0)=0$;
- se si ha l'addendo $x_{h}^{k}p_{X}(x_{h})$ con $x_{h}>0$, c'è anche l'addendo con il suo opposto $\underset{=-x_{h}^{k}\ (k\text{ dispari})}{\underbrace{(-x_{h})^{k}}}\underset{=p_{X}(x_{h})\ (\text{simmetria})}{\underbrace{p_{X}(-x_{h})}}=-x_{h}^{k}p_{X}(x_{h})$ e quindi si semplifica con $x_{h}^{k}p_{X}(x_{h})$.
#### La covarianza è nulla
$$\text{Cov}(X_{1},X_{2})=\text{Cov}(X,X^{2})=\underset{=\mathbb{E}[X^{3}]=0}{\underbrace{\mathbb{E}[X\cdot X^{2}]}}-\underset{=0}{\underbrace{\mathbb{E}[X]}}\ \mathbb{E}[X^{2}]=0$$dove $\mathbb{E}[X^{3}]=0$ e $\mathbb{E}[X]=0$ perché $3$ e $1$ sono dispari (momenti dispari nulli).
#### Ma $X$ e $X^{2}$ non sono indipendenti
Basta trovare $x_{1},x_{2}$ tali che $p_{\underline{X}}(x_{1},x_{2})\neq p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})$. Prendiamo $x\in S_{X}$ con $p_{X}(x)>0$. Poiché $$\{X^{2}=x^{2}\}=\{X=x\}\cup\{X=-x\}\implies\{X=x\}\subseteq\{X^{2}=x^{2}\}$$per il primo membro si ha $$p_{X,X^{2}}(x,x^{2})=P(\{X=x\}\cap\{X^{2}=x^{2}\})=P(X=x)=p_{X}(x)\qquad(\ast)$$Allora, se $(\ast)$ fosse un caso di indipendenza, si avrebbe $p_{X}(x)=p_{X}(x)p_{X^{2}}(x^{2})$, e quindi $p_{X^{2}}(x^{2})=1$. Ma questo è impossibile, perché significherebbe che $X^{2}$ è una v.a. costante uguale a $x^{2}$. Quindi $X$ e $X^{2}$ **non** sono indipendenti.
#### Esempio numerico
Sia $X$ tale che $$p_{X}(2)=p_{X}(-2)=\frac{1}{10},\quad p_{X}(1)=p_{X}(-1)=\frac{3}{10},\quad p_{X}(0)=\frac{2}{10}$$($X$ è effettivamente simmetrica). La densità di $X^{2}$ è $$p_{X^{2}}(4)=p_{X}(2)+p_{X}(-2)=\frac{2}{10}=\frac{1}{5},\quad p_{X^{2}}(1)=p_{X}(1)+p_{X}(-1)=\frac{6}{10}=\frac{3}{5},\quad p_{X^{2}}(0)=p_{X}(0)=\frac{2}{10}=\frac{1}{5}$$(la somma fa 1). In generale, per $k$ dispari, il momento $k$-esimo è nullo: $$\mathbb{E}[X^{k}]=(-2)^{k}\cdot \frac{1}{10}+(-1)^{k}\cdot \frac{3}{10}+\underset{=0}{\underbrace{0\cdot \frac{2}{10}}}+1^{k}\cdot \frac{3}{10}+2^{k}\cdot \frac{1}{10}=-2^{k}\cdot \frac{1}{10}-\frac{3}{10}+0+\frac{3}{10}+2^{k}\cdot \frac{1}{10}=0$$In particolare $\mathbb{E}[X]=0$ e $\mathbb{E}[X^{3}]=0$, mentre $\mathbb{E}[X^{2}]=0\cdot \frac{1}{5}+1\cdot \frac{3}{5}+4\cdot \frac{1}{5}=\frac{7}{5}$. Quindi $$\text{Cov}(X,X^{2})=\underset{=\mathbb{E}[X^{3}]=0}{\underbrace{\mathbb{E}[X\cdot X^{2}]}}-\underset{=0}{\underbrace{\mathbb{E}[X]}}\ \mathbb{E}[X^{2}]=0$$Verifichiamo che **non** c'è indipendenza, ad esempio con la coppia $(2,4)$: $$p_{X,X^{2}}(2,4)=P(\{X=2\}\cap\{X^{2}=4\})=P(X=2)=\frac{1}{10}$$mentre $$p_{X}(2)\cdot p_{X^{2}}(4)=\frac{1}{10}\left( \frac{1}{10}+\frac{1}{10} \right)=\frac{1}{10}\cdot \frac{2}{10}=\frac{2}{100}\neq \frac{1}{10}$$Sono diversi, e questo basta. (Si può verificare anche con una coppia diversa da $(2,4)$: ad esempio $p_{X,X^{2}}(0,0)\neq p_{X}(0)p_{X^{2}}(0)$.)

> [!question] Domanda tipica d'esame
> Covarianza nulla implica indipendenza? Giustificare.
> **Risposta.** No: l'indipendenza implica $\text{Cov}=0$ (perché $\mathbb{E}[X_{1}X_{2}]=\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$), ma non viceversa. Controesempio: $X$ simmetrica con $X^{2}$ non costante e media finita; $\text{Cov}(X,X^{2})=\mathbb{E}[X^{3}]-\mathbb{E}[X]\mathbb{E}[X^{2}]=0$ (momenti dispari nulli) ma $p_{X,X^{2}}(x,x^{2})=p_{X}(x)\neq p_{X}(x)p_{X^{2}}(x^{2})$ (nell'esempio numerico con $x=2$: $\frac{1}{10}\neq\frac{2}{100}$).

--- Fine parte su indipendenza e covarianza (lezione 14, pp. 1-6) ---
## Varianza delle distribuzioni discrete notevoli
Calcolo di $\text{Var}[X]$ per bernoulliana, binomiale, ipergeometrica, Poisson, geometrica (e traslata), binomiale negativa (e traslata), con esempio sul confronto tra estrazioni con e senza reinserimento.

> [!quote] Tabella riassuntiva *(extra, non da slide)*
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

In tutti i calcoli si usa la [[03 - Speranza matematica e momenti#1) Formula alternativa per la varianza|formula alternativa]] $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$, con le [[03 - Speranza matematica e momenti#Speranza matematica delle distribuzioni discrete notevoli|medie già calcolate]].
### 1) Distribuzione bernoulliana: $X\sim B(p)$
Con $\mathbb{E}[X]=p$ (già visto) e $\mathbb{E}[X^{2}]=1^{2}\cdot p+0^{2}\cdot(1-p)=p$ si ha $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=p-p^{2}=\begin{bmatrix}p(1-p)\end{bmatrix}$$In particolare, se $X=1_{A}$, si ha $\text{Var}[1_{A}]=P(A)(1-P(A))$.

> [!info] Perché $\mathbb{E}[X^{2}]=\mathbb{E}[X]$
> Si vede che $X^{2}(\omega)=X(\omega)$ per ogni $\omega\in\Omega$, perché l'equazione $y^{2}=y$ ha soluzioni $y=0$ e $y=1$ (i soli valori assunti). Quindi $\mathbb{E}[X^{2}]=\mathbb{E}[X]=p$.
### 2) Distribuzione binomiale: $X\sim BIN(n,p)$
Il calcolo diretto di $\mathbb{E}[X^{2}]=\sum_{k=0}^{n}k^{2}\binom{n}{k}p^{k}(1-p)^{n-k}$ sarebbe un po' complicato. Usiamo invece il **metodo alternativo**: come visto per la media, $X=X_{1}+\dots+X_{n}$ dove $X_{1},\dots,X_{n}$ sono **i.i.d.** (indipendenti e identicamente distribuite) e [[02 - Modelli discreti#Distribuzione Bernoulliana|bernoulliane]] di parametro $p$. Allora, per l'[[03 - Speranza matematica e momenti#Conseguenza (varianza di una somma di v.a. indipendenti)|indipendenza]], $$\text{Var}[X]=\sum_{i=1}^{n}\text{Var}[X_{i}]=\underset{n\text{ volte}}{\underbrace{p(1-p)+\dots+p(1-p)}}=\begin{bmatrix}np(1-p)\end{bmatrix}$$
### 3) Distribuzione ipergeometrica
Ricordiamo lo schema: $n$ estrazioni **senza** reinserimento con $2\leq n<n_{1}+n_{2}$ (per $n=1$ non ha senso parlare di reinserimento), e $X=$ numero di oggetti di tipo 1 estratti. Con $p=\frac{n_{1}}{n_{1}+n_{2}}$ si avrebbe $\text{Var}[X]=\mathbb{E}[X^{2}]-(np)^{2}$, ma il calcolo diretto di $\mathbb{E}[X^{2}]$ è complicato.
Con il **metodo alternativo** (che non dimostriamo del tutto) si scrive $X=X_{1}+\dots+X_{n}$ con $X_{i}\sim B(p)$ ma **non** indipendenti. Allora $$\text{Var}[X]=\sum_{i=1}^{n}\underset{=p(1-p)}{\underbrace{\text{Var}[X_{i}]}}+2\underset{i<j}{\sum_{i,j=1}^{n}}\underset{\text{tutte uguali tra loro e negative}}{\underbrace{\text{Cov}(X_{i},X_{j})}}<np(1-p)$$Facendo i calcoli si dimostra che $$\begin{bmatrix}\text{Var}[X]=np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}\end{bmatrix}$$(avendo usato $1-p=\frac{n_{2}}{n_{1}+n_{2}}$).

> [!info] Confronto con e senza reinserimento
> Essendo $1<n<n_{1}+n_{2}$, si ha $\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}\in(0,1)$, in accordo con $\text{Var}[X]<np(1-p)$. Se $n_{1}+n_{2}$ è molto più grande di $n$ il rapporto è vicino a 1 ("poca differenza" con il caso con reinserimento). Quindi nel confronto tra estrazioni "con" e "senza" reinserimento si hanno **medie uguali** (valore comune $n\frac{n_{1}}{n_{1}+n_{2}}$) e **varianze diverse** (varianza più piccola nel caso senza reinserimento).
### 4) Distribuzione di Poisson: $X\sim POISSON(\lambda)$
Con $\mathbb{E}[X]=\lambda$ (già visto) e $\mathbb{E}[X^{2}]=\sum_{k\geq 0}k^{2}\frac{\lambda^{k}}{k!}e^{-\lambda}$, il risultato si prende per buono: $$\begin{bmatrix}\text{Var}[X]=\lambda\end{bmatrix}$$(quindi per la [[02 - Modelli discreti#Distribuzione di Poisson|Poisson]] media e varianza coincidono).
### 5) Distribuzione geometrica: $X\sim Geo(p)$
Con $\mathbb{E}[X]=\frac{1}{p}-1$ (già visto) e $\mathbb{E}[X^{2}]=\sum_{k\geq 0}k^{2}(1-p)^{k}p$, il risultato si prende per buono: $$\begin{bmatrix}\text{Var}[X]=\frac{1-p}{p^{2}}\end{bmatrix}$$
### 6) Distribuzione geometrica traslata: $Y\sim GeoTraslata(p)$
Ci riconduciamo al caso precedente: $Y=X+1$ con $X\sim Geo(p)$. Allora, essendo la [[03 - Speranza matematica e momenti#3) Invarianza per traslazione della varianza|varianza invariante per traslazione]], $$\text{Var}[Y]=\text{Var}[X+1]=\text{Var}[X]=\begin{bmatrix}\frac{1-p}{p^{2}}\end{bmatrix}$$
### 7) Binomiale negativa e binomiale negativa traslata
Il calcolo diretto a partire da $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$ sarebbe complicato. Facciamo invece riferimento alle [[02 - Modelli discreti#Un legame tra binomiale negativa (traslata) e geometrica (traslata)|decomposizioni in somme di $r$ geometriche indipendenti (o $r$ geometriche traslate indipendenti)]] viste in passato. Allora, per l'indipendenza, $$\begin{array}{ll}
X=\underset{\text{i.i.d.}\sim Geo(p)}{\underbrace{X_{1}+\dots+X_{r}}} & \implies\ \text{Var}[X]=\sum_{i=1}^{r}\text{Var}[X_{i}]=\underset{r\text{ volte}}{\underbrace{\frac{1-p}{p^{2}}+\dots+\frac{1-p}{p^{2}}}}=\begin{bmatrix}r\frac{1-p}{p^{2}}\end{bmatrix} \\
Y=\underset{\text{i.i.d.}\sim GeoTraslata(p)}{\underbrace{Y_{1}+\dots+Y_{r}}} & \implies\ \text{Var}[Y]=\sum_{i=1}^{r}\text{Var}[Y_{i}]=\underset{r\text{ volte}}{\underbrace{\frac{1-p}{p^{2}}+\dots+\frac{1-p}{p^{2}}}}=\begin{bmatrix}r\frac{1-p}{p^{2}}\end{bmatrix}
\end{array}$$

> [!info] Coerenza
> Si è ottenuto $\text{Var}[Y]=\text{Var}[X]$, in accordo con $Y=X+r$: sommando una costante la varianza non cambia.
### Esempio (urna, con e senza reinserimento)
Un'urna ha 3 palline bianche e 4 nere. Si estraggono 2 palline a caso, una alla volta e con/senza reinserimento. Sia $X$ la v.a. che conta il numero di palline bianche estratte. Calcolare $\mathbb{E}[X]$ e $\text{Var}[X]$.
Qui $n_{1}=3$, $n_{2}=4$, $n=2$, $p=\frac{n_{1}}{n_{1}+n_{2}}=\frac{3}{7}$. $$\begin{array}{l|ll}
 & \mathbb{E}[X] & \text{Var}[X] \\
\hline
\text{CON} & np=2\cdot \frac{3}{7}=\frac{6}{7} & np(1-p)=2\cdot \frac{3}{7}\cdot \frac{4}{7}=\frac{24}{49} \\
\text{SENZA} & np=2\cdot \frac{3}{7}=\frac{6}{7} & np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}=\frac{24}{49}\cdot \frac{7-2}{7-1}=\frac{24}{49}\cdot \frac{5}{6}=\frac{20}{49}
\end{array}$$
#### Verifica diretta dei valori numerici
**Caso con reinserimento** ($X\sim BIN(2,\frac{3}{7})$): con $p_{X}(k)=\binom{2}{k}\left( \frac{3}{7} \right)^{k}\left( \frac{4}{7} \right)^{2-k}$ si ha $p_{X}(0)=\frac{16}{49}$, $p_{X}(1)=\frac{24}{49}$, $p_{X}(2)=\frac{9}{49}$, da cui $$\mathbb{E}[X]=0\cdot \frac{16}{49}+1\cdot \frac{24}{49}+2\cdot \frac{9}{49}=\frac{42}{49}=\frac{6}{7}$$ $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=0^{2}\cdot \frac{16}{49}+1^{2}\cdot \frac{24}{49}+2^{2}\cdot \frac{9}{49}-\left( \frac{6}{7} \right)^{2}=\frac{60}{49}-\frac{36}{49}=\frac{24}{49}\quad\text{ok}$$
**Caso senza reinserimento** (ipergeometrica): con $p_{X}(k)=\frac{\binom{3}{k}\binom{4}{2-k}}{\binom{7}{2}}$ si ha $p_{X}(0)=\frac{6}{21}=\frac{2}{7}$, $p_{X}(1)=\frac{12}{21}=\frac{4}{7}$, $p_{X}(2)=\frac{3}{21}=\frac{1}{7}$, da cui $$\mathbb{E}[X]=0\cdot \frac{2}{7}+1\cdot \frac{4}{7}+2\cdot \frac{1}{7}=\frac{6}{7}$$ $$\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=0^{2}\cdot \frac{2}{7}+1^{2}\cdot \frac{4}{7}+2^{2}\cdot \frac{1}{7}-\left( \frac{6}{7} \right)^{2}=\frac{8}{7}-\frac{36}{49}=\frac{56-36}{49}=\frac{20}{49}\quad\text{ok}$$

> [!question] Domanda tipica d'esame
> Come si ottengono varianza di una binomiale e di una ipergeometrica con le somme di bernoulliane? Che differenza c'è?
> **Risposta.** $X=X_{1}+\dots+X_{n}$ con $X_{i}\sim B(p)$. Binomiale: $X_{i}$ indipendenti, quindi $\text{Var}[X]=np(1-p)$. Ipergeometrica ($p=\frac{n_{1}}{n_{1}+n_{2}}$): $X_{i}$ non indipendenti con covarianze negative, quindi $\text{Var}[X]=np(1-p)\frac{n_{1}+n_{2}-n}{n_{1}+n_{2}-1}<np(1-p)$; le medie coincidono.

--- Fine parte sulle varianze notevoli (lezione 14, pp. 7-14) ---
## Coefficiente di correlazione
Versione normalizzata della covarianza, sempre compresa tra $-1$ e $1$, che misura il grado di relazione lineare tra due variabili aleatorie.
### Definizione
Siano $X_{1},X_{2}$ due v.a. definite su uno stesso spazio di probabilità, con medie e varianze finite, **non necessariamente discrete** e **non costanti** (quindi $\text{Var}[X_{1}]>0$ e $\text{Var}[X_{2}]>0$). Si definisce **coefficiente di correlazione** tra $X_{1}$ e $X_{2}$ la quantità $$\begin{bmatrix}
\rho(X_{1},X_{2})=\frac{\text{Cov}(X_{1},X_{2})}{\sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}}
\end{bmatrix}$$

> [!info] Segno
> Poiché il denominatore è positivo, $\rho(X_{1},X_{2})\gtrless 0\iff \text{Cov}(X_{1},X_{2})\gtrless 0$: il coefficiente di correlazione ha lo **stesso segno** della covarianza.
### Proprietà
#### 1) $|\rho(X_{1},X_{2})|\leq 1$
Cioè $-1\leq\rho(X_{1},X_{2})\leq 1$, perché si può dimostrare che $$|\text{Cov}(X_{1},X_{2})|\leq \sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}$$

> [!quote] Cauchy-Schwarz
> Questa può essere vista come una versione della disuguaglianza di **Cauchy-Schwarz** per spazi vettoriali, $|\langle v_{1},v_{2}\rangle|\leq\|v_{1}\|\,\|v_{2}\|$, con la covarianza nel ruolo del prodotto scalare e la varianza in quello del quadrato della norma.
#### 2) $\rho(X_{1},X_{2})=1\iff X_{2}=aX_{1}+b$ con $a>0$
#### 3) $\rho(X_{1},X_{2})=-1\iff X_{2}=aX_{1}+b$ con $a<0$
Quindi $|\rho|=1$ corrisponde al caso di **perfetta relazione affine** tra $X_{1}$ e $X_{2}$: i punti $(x_{1},x_{2})$ con densità positiva sono tutti allineati su una retta, crescente se $\rho=1$ ($a>0$) e decrescente se $\rho=-1$ ($a<0$). *(extra, non da slide)*

> [!info] Perché servono v.a. non costanti *(extra, non da slide)*
> La richiesta $\text{Var}[X_{1}]>0$ e $\text{Var}[X_{2}]>0$ serve a rendere ben definito il denominatore: se una delle due v.a. fosse costante il coefficiente di correlazione non avrebbe senso.

> [!info] Situazioni escluse (non si può definire $\rho$)
> Non possiamo avere situazioni come queste, in cui il denominatore si annulla:
> - tutti i punti $(x_{1},x_{2})$ con densità positiva su una retta verticale: $\text{Var}[X_{1}]=0$ e $\text{Var}[X_{2}]>0$;
> - tutti su una retta orizzontale: $\text{Var}[X_{1}]>0$ e $\text{Var}[X_{2}]=0$;
> - un solo punto: $\text{Var}[X_{1}]=\text{Var}[X_{2}]=0$.

Quanto $\rho$ è vicino a $\pm 1$ è una misura di quanto la nube dei punti è vicina a una situazione di allineamento perfetto su una retta (crescente o decrescente); si veda [[03 - Speranza matematica e momenti#Commenti conclusivi sull'esercizio|l'esercizio sulle rette di regressione]] per un caso con $\rho$ vicino a $+1$.

> [!question] Domanda tipica d'esame
> Quali proprietà ha il coefficiente di correlazione e cosa significa $|\rho|=1$?
> **Risposta.** $\rho(X_{1},X_{2})=\frac{\text{Cov}(X_{1},X_{2})}{\sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}}$ ha il segno della covarianza e $|\rho|\leq 1$ (versione della disuguaglianza di Cauchy-Schwarz). $\rho=1\iff X_{2}=aX_{1}+b$ con $a>0$; $\rho=-1\iff X_{2}=aX_{1}+b$ con $a<0$.

--- Fine parte sul coefficiente di correlazione (lezione 14, pp. 15-16) ---
## Retta di regressione
Retta che approssima meglio il legame tra due variabili aleatorie con il metodo dei minimi quadrati, con le formule per i coefficienti ed esempi.
### Impostazione
Supponiamo di avere una v.a. bidimensionale $\underline{X}=(X_{1},X_{2})$; in questo corso pensiamo al caso discreto, ma si possono considerare casi più generali. Si vuole trovare la retta che approssima meglio possibile il legame tra $X_{1}$ e $X_{2}$. Ci sono due rette (in generale diverse):
- **regressione di $X_{2}$ rispetto a $X_{1}$**: $\quad r_{21}:\ x_{2}=ax_{1}+b$
- **regressione di $X_{1}$ rispetto a $X_{2}$**: $\quad r_{12}:\ x_{1}=cx_{2}+d$

Ci soffermeremo principalmente su $r_{21}$; in maniera analoga si ottengono le formule per $r_{12}$.
### Metodo dei minimi quadrati
Si cercano $\alpha,\beta\in \mathbb{R}$ tali che $$\min_{\alpha,\beta\in \mathbb{R}}\mathbb{E}[(X_{2}-(\alpha X_{1}+\beta))^{2}]=\mathbb{E}[(X_{2}-(aX_{1}+b))^{2}]$$

> [!info] Interpretazione geometrica
> Nel caso discreto i "punti" $(x_{1},x_{2})$ con densità $p_{X_{1},X_{2}}(x_{1},x_{2})>0$ formano una nube. Per ciascuno si considera lo scarto verticale dalla retta $x_{2}=\alpha x_{1}+\beta$: si vuole **minimizzare la media dei quadrati** di questi scarti.

Sviluppando con la [[03 - Speranza matematica e momenti#Alcune proprietà della speranza matematica|linearità]]: $$\begin{array}{ll}
\mathbb{E}[(X_{2}-(\alpha X_{1}+\beta))^{2}] & =\mathbb{E}[X_{2}^{2}]+\mathbb{E}[(\alpha X_{1}+\beta)^{2}]-2\mathbb{E}[X_{2}(\alpha X_{1}+\beta)] \\
 & =\mathbb{E}[X_{2}^{2}]+\alpha^{2}\mathbb{E}[X_{1}^{2}]+2\alpha\beta\mathbb{E}[X_{1}]+\beta^{2}-2\alpha\mathbb{E}[X_{1}X_{2}]-2\beta\mathbb{E}[X_{2}]
\end{array}$$Si impone che le **derivate parziali** rispetto ad $\alpha$ e $\beta$ siano uguali a zero, ottenendo un sistema di due equazioni nelle due incognite.
### Le formule per i coefficienti
Indicando con $a,b$ le soluzioni per $r_{21}$: $$\begin{cases}
a=\dfrac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]} \\[2mm]
\mathbb{E}[X_{2}]=a\,\mathbb{E}[X_{1}]+b
\end{cases}\implies\begin{bmatrix}
a=\dfrac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]} \\[2mm]
b=\mathbb{E}[X_{2}]-\dfrac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}\mathbb{E}[X_{1}]
\end{bmatrix}$$La seconda equazione $\mathbb{E}[X_{2}]=a\mathbb{E}[X_{1}]+b$ dice che la retta $r_{21}$ **passa per il punto** $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$.
Per la retta $r_{12}:\ x_{1}=cx_{2}+d$ si scambia il ruolo tra $X_{1}$ e $X_{2}$ e, ricordando che $\text{Cov}(X_{1},X_{2})=\text{Cov}(X_{2},X_{1})$, si ha $$\begin{bmatrix}
c=\dfrac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]} \\[2mm]
d=\mathbb{E}[X_{1}]-\dfrac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}\mathbb{E}[X_{2}]
\end{bmatrix}$$Anche l'equazione $\mathbb{E}[X_{1}]=c\mathbb{E}[X_{2}]+d$ dice che $r_{12}$ passa per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$.
### Commento sui segni
I coefficienti angolari $a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}$ e $c=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}$ hanno lo **stesso segno** della covarianza. Quindi:
- $a,c,\text{Cov}(X_{1},X_{2})>0$: rette **crescenti**;
- $a,c,\text{Cov}(X_{1},X_{2})<0$: rette **decrescenti**;
- $a=c=\text{Cov}(X_{1},X_{2})=0$: rette **parallele agli assi**, cioè $x_{2}=\mathbb{E}[X_{2}]$ (orizzontale) e $x_{1}=\mathbb{E}[X_{1}]$ (verticale).

In ogni caso entrambe le rette passano per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$. Nelle slide $r_{21}$ è disegnata in verde e $r_{12}$ in rosso.
### Esempio con covarianza nulla
Riprendiamo il caso [[03 - Speranza matematica e momenti#Esempio numerico|già visto]] dove la covarianza è nulla: $X_{1}=X$, $X_{2}=X^{2}$ con $$p_{X}(-2)=p_{X}(2)=\frac{1}{10},\quad p_{X}(-1)=p_{X}(1)=\frac{3}{10},\quad p_{X}(0)=\frac{2}{10}$$Si ha $\mathbb{E}[X]=0$ e $\mathbb{E}[X^{2}]=(-2)^{2}\cdot \frac{1}{10}+(-1)^{2}\cdot \frac{3}{10}+0^{2}\cdot \frac{2}{10}+1^{2}\cdot \frac{3}{10}+2^{2}\cdot \frac{1}{10}=\frac{14}{10}=\frac{7}{5}$. Essendo $\text{Cov}(X,X^{2})=0$, le rette di regressione sono parallele agli assi: $$\begin{cases}
x_{2}=\mathbb{E}[X^{2}]=\frac{7}{5} \\
x_{1}=\mathbb{E}[X]=0\quad(\text{coincide con l'asse delle ordinate})
\end{cases}$$I punti $(x,x^{2})$ stanno sulla parabola $x_{2}=x_{1}^{2}$, ma la retta di regressione di $X_{2}$ rispetto a $X_{1}$ è orizzontale: la covarianza misura solo il legame **lineare**. *(extra, non da slide)*
### Esercizio
Consideriamo la seguente densità congiunta discreta: $$p_{\underline{X}}(0,0)=p_{\underline{X}}(3,2)=\frac{1}{6},\qquad p_{\underline{X}}(1,1)=p_{\underline{X}}(2,1)=\frac{1}{3}$$Trovare le rette di regressione $x_{2}=ax_{1}+b$ e $x_{1}=cx_{2}+d$.
**Marginale di $X_{1}$ e relativi momenti.** $$\begin{cases}
p_{X_{1}}(0)=p_{\underline{X}}(0,0)=\frac{1}{6} \\
p_{X_{1}}(1)=p_{\underline{X}}(1,1)=\frac{1}{3} \\
p_{X_{1}}(2)=p_{\underline{X}}(2,1)=\frac{1}{3} \\
p_{X_{1}}(3)=p_{\underline{X}}(3,2)=\frac{1}{6}
\end{cases}\quad\begin{array}{l}
\mathbb{E}[X_{1}]=0\cdot \frac{1}{6}+1\cdot \frac{1}{3}+2\cdot \frac{1}{3}+3\cdot \frac{1}{6}=\frac{3}{2} \\[1mm]
\text{Var}[X_{1}]=\mathbb{E}[X_{1}^{2}]-\mathbb{E}^{2}[X_{1}]=0^{2}\cdot \frac{1}{6}+1^{2}\cdot \frac{1}{3}+2^{2}\cdot \frac{1}{3}+3^{2}\cdot \frac{1}{6}-\left( \frac{3}{2} \right)^{2}=\frac{11}{12}
\end{array}$$
**Marginale di $X_{2}$ e relativi momenti.** $$\begin{cases}
p_{X_{2}}(0)=p_{\underline{X}}(0,0)=\frac{1}{6} \\
p_{X_{2}}(1)=p_{\underline{X}}(1,1)+p_{\underline{X}}(2,1)=\frac{1}{3}+\frac{1}{3}=\frac{2}{3} \\
p_{X_{2}}(2)=p_{\underline{X}}(3,2)=\frac{1}{6}
\end{cases}\quad\begin{array}{l}
\mathbb{E}[X_{2}]=0\cdot \frac{1}{6}+1\cdot \frac{2}{3}+2\cdot \frac{1}{6}=1 \\[1mm]
\text{Var}[X_{2}]=\mathbb{E}[X_{2}^{2}]-\mathbb{E}^{2}[X_{2}]=0^{2}\cdot \frac{1}{6}+1^{2}\cdot \frac{2}{3}+2^{2}\cdot \frac{1}{6}-1^{2}=\frac{1}{3}
\end{array}$$
**Covarianza.** Con $\mathbb{E}[X_{1}X_{2}]=0\cdot 0\cdot \frac{1}{6}+1\cdot 1\cdot \frac{1}{3}+2\cdot 1\cdot \frac{1}{3}+3\cdot 2\cdot \frac{1}{6}=2$ si ha $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=2-\frac{3}{2}\cdot 1=\frac{4-3}{2}=\frac{1}{2}$$
**Retta $r_{21}$.** $$a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}=\frac{1/2}{11/12}=\frac{6}{11},\qquad b=\mathbb{E}[X_{2}]-a\mathbb{E}[X_{1}]=1-\frac{6}{11}\cdot \frac{3}{2}=1-\frac{9}{11}=\frac{2}{11}$$da cui $r_{21}:\ x_{2}=\frac{6}{11}x_{1}+\frac{2}{11}$.
**Retta $r_{12}$.** $$c=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}=\frac{1/2}{1/3}=\frac{3}{2},\qquad d=\mathbb{E}[X_{1}]-c\mathbb{E}[X_{2}]=\frac{3}{2}-\frac{3}{2}\cdot 1=0$$da cui $r_{12}:\ x_{1}=\frac{3}{2}x_{2}$.
### Commenti conclusivi sull'esercizio
Le due rette ottenute non coincidono, ma passano entrambe per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])=\left( \frac{3}{2},1 \right)$. Le due rette **coincidono se e solo se i punti sono tutti allineati** sulla stessa retta; qui i punti non lo sono, quindi ci si aspetta due rette diverse.
Però in qualche senso i punti sono "abbastanza vicini" a una situazione di allineamento perfetto su una retta crescente, quindi ci si aspetta il [[03 - Speranza matematica e momenti#Coefficiente di correlazione|coefficiente di correlazione]] $\rho$ vicino a $+1$. In effetti $$\rho=\frac{\text{Cov}(X_{1},X_{2})}{\sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}}=\frac{1/2}{\sqrt{\frac{11}{12}\cdot \frac{1}{3}}}=\frac{1/2}{\sqrt{\frac{11}{36}}}=\frac{1/2}{\sqrt{11}/6}=\frac{3}{\sqrt{11}}=0{,}9045\dots$$

> [!question] Domanda tipica d'esame
> Scrivere le rette di regressione di $X_{2}$ rispetto a $X_{1}$ e di $X_{1}$ rispetto a $X_{2}$ e dire in quale punto si incontrano.
> **Risposta.** $x_{2}=ax_{1}+b$ con $a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}$, $b=\mathbb{E}[X_{2}]-a\mathbb{E}[X_{1}]$; $x_{1}=cx_{2}+d$ con $c=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}$, $d=\mathbb{E}[X_{1}]-c\mathbb{E}[X_{2}]$. Entrambe passano per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$ e coincidono se e solo se i punti sono tutti allineati.

--- Fine lezione 14 ---

## Esercizi di riepilogo (lezione 23)
Esercizi della lezione 23 (pp. 16-20) su speranza, varianza, covarianza e retta di regressione.
### Esercizio (monete: $Z=XY$)
Si lancia 4 volte una moneta equa e consideriamo le v.a. $X=\#$ teste ottenute e $Y=\#$ croci ottenute. Calcolare $\mathbb{E}[Z]$ e $\text{Var}[Z]$ dove $Z=XY$.
**Svolgimento.** Osserviamo che $Y=4-X$ e quindi $Z=X(4-X)=4X-X^{2}$ con $X\sim BIN\left(n=4,p=\frac{1}{2}\right)$. Allora $$\begin{array}{c|c}
X & Z=4X-X^{2} \\
\hline
0 & 4\cdot 0-0^{2}=0 \\
1 & 4\cdot 1-1^{2}=3 \\
2 & 4\cdot 2-2^{2}=4 \\
3 & 4\cdot 3-3^{2}=3 \\
4 & 4\cdot 4-4^{2}=0
\end{array}$$Quindi la v.a. $Z$ assume i valori $\{0,3,4\}$ e $$p_{Z}(0)=P(X=0)+P(X=4)=p_{X}(0)+p_{X}(4),\quad p_{Z}(3)=p_{X}(1)+p_{X}(3),\quad p_{Z}(4)=p_{X}(2)$$Inoltre $p_{X}(k)=\binom{4}{k}\left( \frac{1}{2} \right)^{4}$ per $k=0,1,2,3,4$, e quindi $p_{X}(0)=p_{X}(4)=\frac{1}{16}$, $p_{X}(1)=p_{X}(3)=\frac{4}{16}$, $p_{X}(2)=\frac{6}{16}$. Allora $$p_{Z}(0)=\frac{1}{16}+\frac{1}{16}=\frac{2}{16}=\frac{1}{8},\quad p_{Z}(3)=\frac{4}{16}+\frac{4}{16}=\frac{8}{16}=\frac{4}{8},\quad p_{Z}(4)=\frac{6}{16}=\frac{3}{8}$$(la somma fa 1). Quindi $$\mathbb{E}[Z]=0\cdot \frac{1}{8}+3\cdot \frac{4}{8}+4\cdot \frac{3}{8}=\frac{0+12+12}{8}=\frac{24}{8}=3$$ $$\text{Var}[Z]=\mathbb{E}[Z^{2}]-\mathbb{E}^{2}[Z]=0^{2}\cdot \frac{1}{8}+3^{2}\cdot \frac{4}{8}+4^{2}\cdot \frac{3}{8}-3^{2}=\frac{0+36+48}{8}-9=\frac{84-72}{8}=\frac{12}{8}=\frac{3}{2}$$
#### Commento (calcolo di $\mathbb{E}[Z]$ senza usare le densità discrete di $Z$ e $X$)
Abbiamo visto che $Z=4X-X^{2}$ con $X\sim BIN\left(n=4,p=\frac{1}{2}\right)$. Allora, per la linearità, $\mathbb{E}[Z]=\mathbb{E}[4X-X^{2}]=4\mathbb{E}[X]-\mathbb{E}[X^{2}]$. Inoltre sappiamo che $\mathbb{E}[X]=np=4\cdot \frac{1}{2}=2$ e $\text{Var}[X]=np(1-p)=4\cdot \frac{1}{2}\left( 1-\frac{1}{2} \right)=4\cdot \frac{1}{2}\cdot \frac{1}{2}=1$, dove $\text{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]$, da cui $$\mathbb{E}[X^{2}]=\text{Var}[X]+\mathbb{E}^{2}[X]=1+2^{2}=5$$Allora $$\mathbb{E}[Z]=4\mathbb{E}[X]-\mathbb{E}[X^{2}]=4\cdot 2-5=8-5=3$$Qui abbiamo usato le formule di media e varianza di $X$ e la linearità di $\mathbb{E}[\cdot]$.
### Esercizio (densità congiunta e retta di regressione)
Consideriamo la seguente densità congiunta: $$p_{\underline{X}}(0,0)=\frac{1}{3},\qquad p_{\underline{X}}(0,1)=p_{\underline{X}}(0,2)=\frac{1}{6},\qquad p_{\underline{X}}(1,1)=p_{\underline{X}}(1,0)=p_{\underline{X}}(2,0)=\frac{1}{9}$$Rispondere alle seguenti domande.
1. Calcolare la retta di regressione di $X_{2}$ rispetto a $X_{1}$.
2. Trovare la densità discreta di $Y=\max\{X_{1},X_{2}\}$.
3. Trovare la densità discreta di $W=\min\{X_{1},X_{2}\}$.
4. Trovare la densità discreta di $Z=X_{1}+X_{2}$.
5. Calcolare $P(X_{1}=X_{2}\,|\,X_{1}+X_{2}=2)$.
6. Calcolare $P(X_{1}\geq X_{2})$.

**Svolgimento 1).** Marginale di $X_{1}$: $$p_{X_{1}}(0)=\frac{1}{3}+\frac{1}{6}+\frac{1}{6}=\frac{2+1+1}{6}=\frac{4}{6}=\frac{2}{3}=\frac{6}{9},\quad p_{X_{1}}(1)=\frac{1}{9}+\frac{1}{9}=\frac{2}{9},\quad p_{X_{1}}(2)=\frac{1}{9}$$(la somma fa 1). Marginale di $X_{2}$: $$p_{X_{2}}(0)=\frac{1}{3}+\frac{1}{9}+\frac{1}{9}=\frac{3+1+1}{9}=\frac{5}{9}=\frac{10}{18},\quad p_{X_{2}}(1)=\frac{1}{6}+\frac{1}{9}=\frac{3+2}{18}=\frac{5}{18},\quad p_{X_{2}}(2)=\frac{1}{6}=\frac{3}{18}$$(la somma fa 1). Allora $$\mathbb{E}[X_{1}]=0\cdot \frac{6}{9}+1\cdot \frac{2}{9}+2\cdot \frac{1}{9}=\frac{4}{9}$$ $$\text{Var}[X_{1}]=\mathbb{E}[X_{1}^{2}]-\mathbb{E}^{2}[X_{1}]=0^{2}\cdot \frac{6}{9}+1^{2}\cdot \frac{2}{9}+2^{2}\cdot \frac{1}{9}-\left( \frac{4}{9} \right)^{2}=\frac{6}{9}-\frac{16}{81}=\frac{54-16}{81}=\frac{38}{81}$$ $$\mathbb{E}[X_{2}]=0\cdot \frac{10}{18}+1\cdot \frac{5}{18}+2\cdot \frac{3}{18}=\frac{11}{18}$$ $$\mathbb{E}[X_{1}X_{2}]=0\cdot 0\cdot \frac{1}{3}+0\cdot 1\cdot \frac{1}{6}+0\cdot 2\cdot \frac{1}{6}+1\cdot 1\cdot \frac{1}{9}+1\cdot 0\cdot \frac{1}{9}+2\cdot 0\cdot \frac{1}{9}=\frac{1}{9}$$ $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=\frac{1}{9}-\frac{4}{9}\cdot \frac{11}{18}=\frac{1}{9}-\frac{44}{162}=\frac{18-44}{162}=-\frac{26}{162}$$

> [!quote] Osservazione
> L'insieme dei punti dove la densità congiunta è positiva **non** è un prodotto cartesiano; quindi $\text{Cov}(X_{1},X_{2})\neq 0$. Inoltre il "trend" dei punti fa pensare a una covarianza negativa.

La retta di regressione è $x_{2}=ax_{1}+b$ dove $$a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}=\frac{-26/162}{38/81}=-\frac{26}{162}\cdot \frac{81}{38}=-\frac{13}{38}$$ $$b=\mathbb{E}[X_{2}]-a\mathbb{E}[X_{1}]=\frac{11}{18}-\left( -\frac{13}{38} \right)\cdot \frac{4}{9}=\frac{11}{18}+\frac{26}{171}=\frac{209+52}{342}=\frac{261}{342}=\frac{29}{38}$$da cui $x_{2}=-\frac{13}{38}x_{1}+\frac{29}{38}$.
**Svolgimento 2), 3), 4).** $$\begin{array}{c|c|c|c}
(x_{1},x_{2}) & Y=\max\{X_{1},X_{2}\} & W=\min\{X_{1},X_{2}\} & Z=X_{1}+X_{2} \\
\hline
(0,0)\ \ \frac{1}{3} & 0 & 0 & 0 \\
(0,1)\ \ \frac{1}{6} & 1 & 0 & 1 \\
(0,2)\ \ \frac{1}{6} & 2 & 0 & 2 \\
(1,1)\ \ \frac{1}{9} & 1 & 1 & 2 \\
(1,0)\ \ \frac{1}{9} & 1 & 0 & 1 \\
(2,0)\ \ \frac{1}{9} & 2 & 0 & 2
\end{array}$$ $$p_{Y}(0)=\frac{1}{3}=\frac{6}{18},\quad p_{Y}(1)=\frac{1}{6}+\frac{1}{9}+\frac{1}{9}=\frac{3+2+2}{18}=\frac{7}{18},\quad p_{Y}(2)=\frac{1}{6}+\frac{1}{9}=\frac{3+2}{18}=\frac{5}{18}$$ $$p_{W}(0)=1-\frac{1}{9}=\frac{8}{9},\quad p_{W}(1)=\frac{1}{9}$$ $$p_{Z}(0)=\frac{1}{3}=\frac{6}{18},\quad p_{Z}(1)=\frac{1}{6}+\frac{1}{9}=\frac{5}{18},\quad p_{Z}(2)=\frac{1}{6}+\frac{1}{9}+\frac{1}{9}=\frac{7}{18}$$(si ha somma $1$ in ciascuno dei 3 casi).
**Svolgimento 5).** Essendo $\{X_{1}=X_{2}\}\cap\{X_{1}+X_{2}=2\}=\{X_{1}=1\}\cap\{X_{2}=1\}$, $$P(X_{1}=X_{2}\,|\,X_{1}+X_{2}=2)=\frac{P(\{X_{1}=X_{2}\}\cap\{X_{1}+X_{2}=2\})}{P(X_{1}+X_{2}=2)}=\frac{p_{\underline{X}}(1,1)}{p_{Z}(2)}=\frac{1/9}{7/18}=\frac{1}{9}\cdot \frac{18}{7}=\frac{2}{7}$$
**Svolgimento 6).** $$P(X_{1}\geq X_{2})=p_{\underline{X}}(0,0)+p_{\underline{X}}(1,1)+p_{\underline{X}}(1,0)+p_{\underline{X}}(2,0)=\frac{1}{3}+\frac{1}{9}+\frac{1}{9}+\frac{1}{9}=\frac{3+1+1+1}{9}=\frac{6}{9}=\frac{2}{3}$$

> [!question] Domanda tipica d'esame
> Come si calcola $\mathbb{E}[Z]$ per $Z=XY=4X-X^{2}$, con $X\sim BIN\left(4,\frac{1}{2}\right)$, senza trovare la densità discreta di $Z$?
> **Risposta.** Per la linearità $\mathbb{E}[Z]=4\mathbb{E}[X]-\mathbb{E}[X^{2}]$. Si ha $\mathbb{E}[X]=np=2$, $\text{Var}[X]=np(1-p)=1$ e $\mathbb{E}[X^{2}]=\text{Var}[X]+\mathbb{E}^{2}[X]=1+4=5$, quindi $\mathbb{E}[Z]=8-5=3$.
