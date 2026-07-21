# Retta di regressione
Retta che approssima meglio il legame tra due variabili aleatorie con il metodo dei minimi quadrati, con le formule per i coefficienti ed esempi.
## Impostazione
Supponiamo di avere una v.a. bidimensionale $\underline{X}=(X_{1},X_{2})$; in questo corso pensiamo al caso discreto, ma si possono considerare casi più generali. Si vuole trovare la retta che approssima meglio possibile il legame tra $X_{1}$ e $X_{2}$. Ci sono due rette (in generale diverse):
- **regressione di $X_{2}$ rispetto a $X_{1}$**: $\quad r_{21}:\ x_{2}=ax_{1}+b$
- **regressione di $X_{1}$ rispetto a $X_{2}$**: $\quad r_{12}:\ x_{1}=cx_{2}+d$

Ci soffermeremo principalmente su $r_{21}$; in maniera analoga si ottengono le formule per $r_{12}$.
## Metodo dei minimi quadrati
Si cercano $\alpha,\beta\in \mathbb{R}$ tali che $$\min_{\alpha,\beta\in \mathbb{R}}\mathbb{E}[(X_{2}-(\alpha X_{1}+\beta))^{2}]=\mathbb{E}[(X_{2}-(aX_{1}+b))^{2}]$$
> [!info] Interpretazione geometrica
> Nel caso discreto i "punti" $(x_{1},x_{2})$ con densità $P_{X_{1},X_{2}}(x_{1},x_{2})>0$ formano una nube. Per ciascuno si considera lo scarto verticale dalla retta $x_{2}=\alpha x_{1}+\beta$: si vuole **minimizzare la media dei quadrati** di questi scarti.

Sviluppando con la [[Speranza matematica di una variabile aleatoria discreta#Alcune proprietà di $\mathbb{E}[X]$|linearità]]: $$\begin{array}{ll}
\mathbb{E}[(X_{2}-(\alpha X_{1}+\beta))^{2}] & =\mathbb{E}[X_{2}^{2}]+\mathbb{E}[(\alpha X_{1}+\beta)^{2}]-2\mathbb{E}[X_{2}(\alpha X_{1}+\beta)] \\
 & =\mathbb{E}[X_{2}^{2}]+\alpha^{2}\mathbb{E}[X_{1}^{2}]+2\alpha\beta\mathbb{E}[X_{1}]+\beta^{2}-2\alpha\mathbb{E}[X_{1}X_{2}]-2\beta\mathbb{E}[X_{2}]
\end{array}$$Si impone che le **derivate parziali** rispetto ad $\alpha$ e $\beta$ siano uguali a zero, ottenendo un sistema di due equazioni nelle due incognite.
## Le formule per i coefficienti
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
## Commento sui segni
I coefficienti angolari $a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}$ e $c=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}$ hanno lo **stesso segno** della covarianza. Quindi:
- $a,c,\text{Cov}(X_{1},X_{2})>0$: rette **crescenti**;
- $a,c,\text{Cov}(X_{1},X_{2})<0$: rette **decrescenti**;
- $a=c=\text{Cov}(X_{1},X_{2})=0$: rette **parallele agli assi**, cioè $x_{2}=\mathbb{E}[X_{2}]$ (orizzontale) e $x_{1}=\mathbb{E}[X_{1}]$ (verticale).

In ogni caso entrambe le rette passano per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])$.
## Esempio con covarianza nulla
Riprendiamo il caso [[Indipendenza e covarianza#Esempio numerico|già visto]] dove la covarianza è nulla: $X_{1}=X$, $X_{2}=X^{2}$ con $$P_{X}(-2)=P_{X}(2)=\frac{1}{10},\quad P_{X}(-1)=P_{X}(1)=\frac{3}{10},\quad P_{X}(0)=\frac{2}{10}$$Si ha $\mathbb{E}[X]=0$ e $\mathbb{E}[X^{2}]=(-2)^{2}\cdot \frac{1}{10}+(-1)^{2}\cdot \frac{3}{10}+0^{2}\cdot \frac{2}{10}+1^{2}\cdot \frac{3}{10}+2^{2}\cdot \frac{1}{10}=\frac{14}{10}=\frac{7}{5}$. Essendo $\text{Cov}(X,X^{2})=0$, le rette di regressione sono parallele agli assi: $$\begin{cases}
x_{2}=\mathbb{E}[X^{2}]=\frac{7}{5} \\
x_{1}=\mathbb{E}[X]=0\quad(\text{coincide con l'asse delle ordinate})
\end{cases}$$
## Esercizio
Consideriamo la seguente densità congiunta discreta: $$P_{\underline{X}}(0,0)=P_{\underline{X}}(3,2)=\frac{1}{6},\qquad P_{\underline{X}}(1,1)=P_{\underline{X}}(2,1)=\frac{1}{3}$$Trovare le rette di regressione $x_{2}=ax_{1}+b$ e $x_{1}=cx_{2}+d$.
**Marginale di $X_{1}$ e relativi momenti.** $$\begin{cases}
P_{X_{1}}(0)=P_{\underline{X}}(0,0)=\frac{1}{6} \\
P_{X_{1}}(1)=P_{\underline{X}}(1,1)=\frac{1}{3} \\
P_{X_{1}}(2)=P_{\underline{X}}(2,1)=\frac{1}{3} \\
P_{X_{1}}(3)=P_{\underline{X}}(3,2)=\frac{1}{6}
\end{cases}\quad\begin{array}{l}
\mathbb{E}[X_{1}]=0\cdot \frac{1}{6}+1\cdot \frac{1}{3}+2\cdot \frac{1}{3}+3\cdot \frac{1}{6}=\frac{3}{2} \\[1mm]
\text{Var}[X_{1}]=\mathbb{E}[X_{1}^{2}]-\mathbb{E}^{2}[X_{1}]=0^{2}\cdot \frac{1}{6}+1^{2}\cdot \frac{1}{3}+2^{2}\cdot \frac{1}{3}+3^{2}\cdot \frac{1}{6}-\left( \frac{3}{2} \right)^{2}=\frac{11}{12}
\end{array}$$
**Marginale di $X_{2}$ e relativi momenti.** $$\begin{cases}
P_{X_{2}}(0)=P_{\underline{X}}(0,0)=\frac{1}{6} \\
P_{X_{2}}(1)=P_{\underline{X}}(1,1)+P_{\underline{X}}(2,1)=\frac{1}{3}+\frac{1}{3}=\frac{2}{3} \\
P_{X_{2}}(2)=P_{\underline{X}}(3,2)=\frac{1}{6}
\end{cases}\quad\begin{array}{l}
\mathbb{E}[X_{2}]=0\cdot \frac{1}{6}+1\cdot \frac{2}{3}+2\cdot \frac{1}{6}=1 \\[1mm]
\text{Var}[X_{2}]=\mathbb{E}[X_{2}^{2}]-\mathbb{E}^{2}[X_{2}]=0^{2}\cdot \frac{1}{6}+1^{2}\cdot \frac{2}{3}+2^{2}\cdot \frac{1}{6}-1^{2}=\frac{1}{3}
\end{array}$$
**Covarianza.** Con $\mathbb{E}[X_{1}X_{2}]=0\cdot 0\cdot \frac{1}{6}+1\cdot 1\cdot \frac{1}{3}+2\cdot 1\cdot \frac{1}{3}+3\cdot 2\cdot \frac{1}{6}=2$ si ha $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=2-\frac{3}{2}\cdot 1=\frac{4-3}{2}=\frac{1}{2}$$
**Retta $r_{21}$.** $$a=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{1}]}=\frac{1/2}{11/12}=\frac{6}{11},\qquad b=\mathbb{E}[X_{2}]-a\mathbb{E}[X_{1}]=1-\frac{6}{11}\cdot \frac{3}{2}=1-\frac{9}{11}=\frac{2}{11}$$da cui $r_{21}:\ x_{2}=\frac{6}{11}x_{1}+\frac{2}{11}$.
**Retta $r_{12}$.** $$c=\frac{\text{Cov}(X_{1},X_{2})}{\text{Var}[X_{2}]}=\frac{1/2}{1/3}=\frac{3}{2},\qquad d=\mathbb{E}[X_{1}]-c\mathbb{E}[X_{2}]=\frac{3}{2}-\frac{3}{2}\cdot 1=0$$da cui $r_{12}:\ x_{1}=\frac{3}{2}x_{2}$.
## Commenti conclusivi sull'esercizio
Le due rette ottenute non coincidono, ma passano entrambe per $(\mathbb{E}[X_{1}],\mathbb{E}[X_{2}])=\left( \frac{3}{2},1 \right)$. Le due rette **coincidono se e solo se i punti sono tutti allineati** sulla stessa retta; qui i punti non lo sono, quindi ci si aspetta due rette diverse.
Però in qualche senso i punti sono "abbastanza vicini" a una situazione di allineamento perfetto su una retta crescente, quindi ci si aspetta il [[Coefficiente di correlazione|coefficiente di correlazione]] $\rho$ vicino a $+1$. In effetti $$\rho=\frac{\text{Cov}(X_{1},X_{2})}{\sqrt{\text{Var}[X_{1}]\text{Var}[X_{2}]}}=\frac{1/2}{\sqrt{\frac{11}{12}\cdot \frac{1}{3}}}=\frac{1/2}{\sqrt{\frac{11}{36}}}=\frac{1/2}{\sqrt{11}/6}=\frac{3}{\sqrt{11}}=0{,}9045\dots$$

--- Fine lezione 14 ---

---
Nota precedente: [[Coefficiente di correlazione]]. Nota successiva: da trascrivere (lezione 15). Indice del blocco: [[Speranza matematica e momenti]].
