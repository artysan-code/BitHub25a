# Speranza matematica di una variabile aleatoria discreta
Definizione di $\mathbb{E}[X]$, condizione di esistenza, proprietà (linearità, monotonia) e formula per la speranza di una trasformazione.
> [!info] Sinonimi
> "Speranza matematica", **media**, **valore medio**, **attesa**, **valore atteso**.
## Motivazione
Questa grandezza si introduce per definire una grandezza analoga al **baricentro** per una distribuzione di masse in fisica, il cui ruolo è giocato dalla distribuzione della v.a. (non necessariamente discreta).
Inoltre, se la speranza matematica esiste finita, possiamo dire che fornisce un **valore riassuntivo** della distribuzione della v.a. (anche se questo fa perdere delle informazioni rispetto alla conoscenza della distribuzione stessa).
## Definizione
Sia $X$ una v.a. discreta con densità $P_{X}$. Allora si dice che $X$ ha **speranza matematica finita** se $$\sum_{x_{k}\in \delta_{X}}|x_{k}|P_{X}(x_{k})<\infty\quad\quad(*)$$In corrispondenza, se vale $(*)$, allora la speranza matematica di $X$ è definita come segue: $$\begin{bmatrix}
\mathbb{E}[X]=\sum_{x_{k}\in \delta_{X}}x_{k}P_{X}(x_{k})
\end{bmatrix}$$
### Commento (quando $(*)$ è automaticamente verificata)
La condizione $(*)$ è verificata se l'insieme $\delta_{X}$ è **limitato**, cioè se esiste $M>0$ tale che $$|x_{k}|\leq M\quad\forall\ x_{k}\in \delta_{X}\quad\quad\iff\quad -M\leq x_{k}\leq M\quad\quad(**)$$Infatti in corrispondenza si ha $$\sum_{x_{k}\in \delta_{X}}|x_{k}|P_{X}(x_{k})\leq M\underset{=1}{\underbrace{\sum_{x_{k}\in \delta_{X}}P_{X}(x_{k})}}=M<\infty$$Osserviamo che $$\delta_{X}\text{ finito}\implies \delta_{X}\text{ limitato}$$perché, se $\delta_{X}=\{x_{1},\dots,x_{n}\}$ per qualche $n$, vale $(**)$ con $M=\max\{|x_{1}|,\dots,|x_{n}|\}$.
Al contrario esistono insiemi limitati non finiti: si pensi a intervalli limitati (es. $[a,b]$) o, se vogliamo un caso di insieme al più numerabile, all'insieme $\left\{ \frac{1}{n}:n\geq 1 \right\}=\left\{ 1,\frac{1}{2},\frac{1}{3},\dots \right\}$ dove vale $(**)$ con $M=1$.
## Alcune proprietà di $\mathbb{E}[X]$
> [!info] Valgono in generale
> Queste proprietà valgono **non solo** per il caso in cui $X$ è discreta.

- **(Terminologia)** $X$ si dice **centrata** se $\mathbb{E}[X]=0$.
- **(Linearità)** Siano $X_{1},\dots,X_{n}$ v.a. definite su uno stesso spazio di probabilità, con speranza matematica finita. Siano $a_{1},\dots,a_{n}\in \mathbb{R}$. Allora anche $a_{1}X_{1}+\dots+a_{n}X_{n}$ ha speranza matematica finita e si ha $$\mathbb{E}[a_{1}X_{1}+\dots+a_{n}X_{n}]=a_{1}\mathbb{E}[X_{1}]+\dots+a_{n}\mathbb{E}[X_{n}]$$(come caso particolare possiamo considerare $X_{1}+\dots+X_{n}$ ponendo $a_{1}=\dots=a_{n}=1$).
- **(Prodotto di v.a. indipendenti)** Siano $X_{1},\dots,X_{n}$ definite su uno stesso spazio di probabilità, con speranza matematica finita, e **indipendenti**. Allora $X_{1}\cdot\dots\cdot X_{n}$ ha speranza matematica finita e si ha $$\mathbb{E}[X_{1}\cdot\dots\cdot X_{n}]=\mathbb{E}[X_{1}]\cdot\dots\cdot \mathbb{E}[X_{n}]$$
- **(Monotonia)** Supponiamo che $X(w)\geq Y(w)$ per ogni $w\in\ohm$. Allora, se $X$ e $Y$ hanno speranza matematica finita, si ha $\mathbb{E}[X]\geq \mathbb{E}[Y]$. (In realtà basta avere $P(X\geq Y)=1$.)
> [!warning] Attenzione
> La linearità **non** richiede l'indipendenza; la formula del prodotto **sì**.

## Proposizione (speranza di una trasformazione)
Sia $\underline{X}$ una v.a. discreta $m$-dimensionale con densità congiunta $P_{\underline{X}}$. Sia $f:\mathbb{R}^{m}\to \mathbb{R}$ e sia $Y=f(\underline{X})$. Allora, se $Y$ ha speranza matematica finita, si ha $$\begin{bmatrix}
\mathbb{E}[Y]=\sum_{\underline{x}_{k}\in \delta_{\underline{X}}}f(\underline{x}_{k})P_{\underline{X}}(\underline{x}_{k})
\end{bmatrix}$$(per $m=1$ si ha una densità discreta non congiunta, perché $\underline{X}$ è una v.a. unidimensionale).
> [!quote] Commento
> In altri termini **non serve conoscere esplicitamente la densità discreta $P_{Y}$ della v.a. $Y$**, ma basta fare riferimento a $P_{\underline{X}}$ (oltre che ad $f$).

### Dimostrazione
Si ha $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{y_{h}\in \delta_{Y}}y_{h}\underset{=P(Y=y_{h})}{\underbrace{P_{Y}(y_{h})}}=\sum_{y_{h}\in \delta_{Y}}y_{h}P\left( \bigcup_{\underline{x}_{k}\in \delta_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}\{\underline{X}=\underline{x}_{k}\} \right) \\
 & \overset{(\star)}{=}\displaystyle\sum_{y_{h}\in \delta_{Y}}y_{h}\sum_{\underline{x}_{k}\in \delta_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}P_{\underline{X}}(\underline{x}_{k})=\sum_{y_{h}\in \delta_{Y}}\sum_{\underline{x}_{k}\in \delta_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}y_{h}P_{\underline{X}}(\underline{x}_{k}) \\
 & \overset{(\dagger)}{=}\displaystyle\sum_{y_{h}\in \delta_{Y}}\sum_{\underline{x}_{k}\in \delta_{\underline{X}}\ :\ f(\underline{x}_{k})=y_{h}}f(\underline{x}_{k})P_{\underline{X}}(\underline{x}_{k})=\sum_{\underline{x}_{k}\in \delta_{\underline{X}}}f(\underline{x}_{k})P_{\underline{X}}(\underline{x}_{k})\qquad\Box
\end{array}$$dove in $(\star)$ si ha un'unione finita o numerabile (perché $\delta_{\underline{X}}$ è un insieme discreto) di eventi disgiunti a due a due, e in $(\dagger)$ si è sostituito $y_{h}$ con $f(\underline{x}_{k})$.
Nell'ultimo passaggio si osservi che prima tutti i valori $\underline{x}_{k}$ erano "raggruppati" in base al valore $y_{h}$ assunto da $f(\underline{x}_{k})$; alla fine non sono più raggruppati.
### Esempio ($\mathbb{E}[X^{2}]$ senza calcolare $P_{Y}$)
Consideriamo una v.a. $X$ con la seguente densità discreta: $$P_{X}(-2)=\frac{1}{10},\quad P_{X}(-1)=\frac{3}{10},\quad P_{X}(0)=\frac{1}{10},\quad P_{X}(1)=\frac{4}{10},\quad P_{X}(2)=\frac{1}{10}$$Calcolare $\mathbb{E}[Y]$ dove $Y=X^{2}$.
La v.a. $Y$ assume valori in un insieme finito, cioè $\delta_{Y}=\{0,1,4\}$, e $\mathbb{E}[Y]=0\cdot P_{Y}(0)+1\cdot P_{Y}(1)+4\cdot P_{Y}(4)$. Però **non è necessario** calcolare i valori di $P_{Y}(y)$; infatti per la proposizione precedente (con $m=1$) si ha $$\mathbb{E}[Y]=\mathbb{E}[X^{2}]=(-2)^{2}\cdot \frac{1}{10}+(-1)^{2}\cdot \frac{3}{10}+0^{2}\cdot \frac{1}{10}+1^{2}\cdot \frac{4}{10}+2^{2}\cdot \frac{1}{10}=\frac{4}{10}+\frac{3}{10}+0+\frac{4}{10}+\frac{4}{10}=\frac{15}{10}=\frac{3}{2}$$
### Esempio (somma di due dadi, in tre modi)
Consideriamo il lancio di due dadi equi e sia $Y=X_{1}+X_{2}$ la v.a. che indica la somma dei due numeri estratti. Calcolare $\mathbb{E}[Y]$.
**1° modo (dalla densità di $Y$).** Facendo riferimento alla [[Trasformazioni e somme di variabili aleatorie discrete#Caso specifico 1 (lancio di due dadi equi)|densità discreta di $Y$ vista in passato]]: $$\mathbb{E}[Y]=\sum_{k=2}^{12}kP_{Y}(k)=2\cdot \frac{1}{36}+3\cdot \frac{2}{36}+4\cdot \frac{3}{36}+5\cdot \frac{4}{36}+6\cdot \frac{5}{36}+7\cdot \frac{6}{36}+8\cdot \frac{5}{36}+9\cdot \frac{4}{36}+10\cdot \frac{3}{36}+11\cdot \frac{2}{36}+12\cdot \frac{1}{36}=\frac{252}{36}=7$$
**2° modo (con la proposizione).** Con $m=2$, $f(x_{1},x_{2})=x_{1}+x_{2}$ e $P_{\underline{X}}(x_{1},x_{2})=\frac{1}{36}$ per $x_{1},x_{2}\in\{1,\dots,6\}$: $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{x_{1},x_{2}=1}^{6}(x_{1}+x_{2})\underset{=1/36}{\underbrace{P_{\underline{X}}(x_{1},x_{2})}}=\frac{1}{36}\sum_{x_{1},x_{2}=1}^{6}(x_{1}+x_{2})=\frac{1}{36}\left\{ \sum_{x_{2}=1}^{6}\sum_{x_{1}=1}^{6}x_{1}+\sum_{x_{1}=1}^{6}\sum_{x_{2}=1}^{6}x_{2} \right\} \\
 & =\frac{1}{36}\left\{ \displaystyle\sum_{x_{2}=1}^{6}\underset{\text{non dipende da }x_{2}}{\underbrace{(1+2+3+4+5+6)}}+\sum_{x_{1}=1}^{6}\underset{\text{non dipende da }x_{1}}{\underbrace{(1+2+3+4+5+6)}} \right\} \\
 & =\frac{1}{36}\{6\cdot 21+6\cdot 21\}=\frac{2\cdot 6\cdot 21}{36}=\frac{252}{36}=7
\end{array}$$
**3° modo (con la linearità).** In realtà in questo caso $\mathbb{E}[Y]$ si calcola ancora più facilmente con la linearità (con $n=2$ e $a_{1}=a_{2}=1$): $\mathbb{E}[X_{1}+X_{2}]=\mathbb{E}[X_{1}]+\mathbb{E}[X_{2}]$. Infatti entrambe le v.a. $X_{1}$ e $X_{2}$ hanno [[Distribuzioni uniforme discreta e di Poisson#Distribuzione uniforme discreta|distribuzione uniforme discreta]] su $\{1,\dots,6\}$ e quindi $$\mathbb{E}[X_{i}]=\sum_{k=1}^{6}k\underset{=1/6}{\underbrace{P_{X_{i}}(k)}}=\frac{1+2+3+4+5+6}{6}=\frac{21}{6}=\frac{7}{2}\quad\text{per }i=1,2$$da cui $\mathbb{E}[X_{1}+X_{2}]=\frac{7}{2}+\frac{7}{2}=7$.
### Esempio (differenza tra massimo e minimo)
Un'urna ha 4 palline numerate da 1 a 4. Si estraggono 2 palline a caso, una alla volta e **senza** reinserimento. Siano $X_{1}$ e $X_{2}$ le v.a. che indicano il massimo e il minimo tra i due numeri estratti. Calcolare $\mathbb{E}[Y]$ dove $Y=X_{1}-X_{2}$.
Abbiamo $\ohm=\{w=(w_{1},w_{2}):w_{1},w_{2}\in\{1,2,3,4\}\text{ con }w_{1}\neq w_{2}\}$ (le estrazioni sono senza reinserimento), e $$X_{1}(w)=\max\{w_{1},w_{2}\},\quad X_{2}(w)=\min\{w_{1},w_{2}\},\quad Y(w)=X_{1}(w)-X_{2}(w)\quad\quad\forall\ w\in\ohm$$Per ogni $w=(w_{1},w_{2})$ abbiamo $$P(\{w\})=\underset{=1/4}{\underbrace{P(\text{estrarre }w_{1})}}\ \underset{=1/3}{\underbrace{P(\text{estrarre }w_{2}|\text{è stato estratto }w_{1})}}=\frac{1}{12}$$ed inoltre $\#\ohm=12$. In dettaglio: $$\begin{array}{c|ccc}
w & X_{1}(w) & X_{2}(w) & Y(w) \\
\hline
(1,2),(2,1) & 2 & 1 & 1 \\
(1,3),(3,1) & 3 & 1 & 2 \\
(1,4),(4,1) & 4 & 1 & 3 \\
(2,3),(3,2) & 3 & 2 & 1 \\
(2,4),(4,2) & 4 & 2 & 2 \\
(3,4),(4,3) & 4 & 3 & 1
\end{array}\quad\quad P_{Y}(y)=\begin{cases}
6/12 & \text{per }y=1 \\
4/12 & \text{per }y=2 \\
2/12 & \text{per }y=3
\end{cases}$$da cui $\mathbb{E}[Y]=1\cdot \frac{6}{12}+2\cdot \frac{4}{12}+3\cdot \frac{2}{12}=\frac{6+8+6}{12}=\frac{20}{12}=\frac{5}{3}$.
Usando la proposizione possiamo **evitare di trattare con $P_{Y}(y)$** e possiamo limitarci a $P_{\underline{X}}(\underline{x})$, che è la seguente (si hanno le 6 coppie che si ottengono dalle 12 coppie precedenti, ordinate come (massimo, minimo); tutte con probabilità $\frac{2}{12}$): $$P_{\underline{X}}(2,1)=P_{\underline{X}}(3,1)=P_{\underline{X}}(4,1)=P_{\underline{X}}(3,2)=P_{\underline{X}}(4,2)=P_{\underline{X}}(4,3)=\frac{2}{12}$$Allora $$\begin{array}{ll}
\mathbb{E}[Y] & =\displaystyle\sum_{(x_{1},x_{2})}(x_{1}-x_{2})P_{\underline{X}}(x_{1},x_{2}) \\
 & =(2-1)\frac{2}{12}+(3-1)\frac{2}{12}+(4-1)\frac{2}{12}+(3-2)\frac{2}{12}+(4-2)\frac{2}{12}+(4-3)\frac{2}{12} \\
 & =\frac{1\cdot 2+2\cdot 2+3\cdot 2+1\cdot 2+2\cdot 2+1\cdot 2}{12}=\frac{2+4+6+2+4+2}{12}=\frac{20}{12}=\frac{5}{3}
\end{array}$$
> [!warning] Refuso nelle slide
> Nell'elenco dei valori di $P_{\underline{X}}$ (lezione 12, ultima pagina) la coppia $(3,1)$ compare due volte: la prima delle sei deve essere $(2,1)$, come conferma il calcolo successivo, dove il primo addendo è $(2-1)\frac{2}{12}$.

--- Fine lezione 12 ---

---
Nota precedente: [[Massimi e minimi di variabili aleatorie discrete]]. Nota successiva: [[Speranza matematica delle distribuzioni discrete notevoli]]. Indice del blocco: [[Speranza matematica e momenti]].
