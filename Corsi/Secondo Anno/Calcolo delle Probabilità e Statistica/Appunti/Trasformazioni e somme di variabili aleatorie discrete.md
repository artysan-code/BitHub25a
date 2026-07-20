# Trasformazioni e somme di variabili aleatorie discrete
Come si calcola la densità discreta di $\underline{Y}=f(\underline{X})$, con il caso particolare delle **somme** di v.a. indipendenti (binomiali e poissoniane).
> [!info] Notazione
> In questa parte si considerano v.a. discrete multidimensionali, e quindi con le notazioni di vettore $\underline{X}=(X_{1},\dots,X_{m})$. Poi, se la dimensione è 1 (quindi $m=1$), si recupera il caso "non multidimensionale" come caso particolare.

## Proposizione (densità di una trasformazione)
Sia $\underline{X}:\ohm\to \mathbb{R}^{m}$ una v.a. discreta $m$-dimensionale. Poi sia $f:A\subset \mathbb{R}^{m}\to \mathbb{R}^{n}$ una funzione. Allora, se $\delta_{\underline{X}}\subset A$, la funzione $\underline{Y}=f\circ \underline{X}:\ohm\to \mathbb{R}^{n}$ è una v.a. **discreta** $n$-dimensionale ($\underline{Y}$ è detta **trasformazione** della v.a. $\underline{X}$).
Inoltre per le densità discrete di $\underline{X}$ e $\underline{Y}$ vale la seguente uguaglianza: $$\begin{bmatrix}
P_{\underline{Y}}(\underline{y})=\sum_{\underline{x}\in \delta_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}P_{\underline{X}}(\underline{x})
\end{bmatrix}\quad\quad\forall\ \underline{y}\in \mathbb{R}^{n}$$
### Dimostrazione
Per ogni $\underline{y}\in \mathbb{R}^{n}$ si ha $$P_{\underline{Y}}(\underline{y})=P(\underline{Y}=\underline{y})=P\left( \bigcup_{\underline{x}\in \delta_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}\{\underline{X}=\underline{x}\} \right)\overset{(\star)}{=}\sum_{\underline{x}\in \delta_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}P(\underline{X}=\underline{x})=\sum_{\underline{x}\in \delta_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}P_{\underline{X}}(\underline{x})$$dove in $(\star)$ si ha un'unione al più numerabile di eventi disgiunti a due a due, e si applica la $\sigma$-additività. Questa è l'uguaglianza che volevamo ottenere $\Box$
### Esempio (con $m=3$ e $n=2$)
Sia $P_{\underline{X}}$ definita come segue: $$P_{\underline{X}}(0,0,0)=\frac{2}{8};\quad P_{\underline{X}}(0,0,1)=P_{\underline{X}}(0,1,0)=P_{\underline{X}}(1,0,0)=P_{\underline{X}}(1,0,1)=P_{\underline{X}}(1,1,0)=P_{\underline{X}}(0,1,1)=\frac{1}{8}$$Inoltre sia $\underline{Y}=f(\underline{X})$, dove $$f(\underline{x})=f(x_{1},x_{2},x_{3})=(x_{1}+x_{2},\ x_{2}\cdot x_{3})\quad\quad\forall\ \underline{x}=(x_{1},x_{2},x_{3})\in \mathbb{R}^{3}$$Vogliamo usare l'uguaglianza $P_{\underline{Y}}(\underline{y})=\sum_{\underline{x}\ :\ f(\underline{x})=\underline{y}}P_{\underline{X}}(\underline{x})$.
Osserviamo che $\delta_{\underline{Y}}\subset\{0,1,2\}\times\{0,1\}$; quindi calcoleremo $P_{\underline{Y}}(\underline{y})$ per $\underline{y}\in\{0,1,2\}\times\{0,1\}$ (sappiamo che $P_{\underline{Y}}(\underline{y})=0$ se $\underline{y}\not\in \delta_{\underline{Y}}$). Quindi $$\begin{array}{ll}
P_{\underline{Y}}(0,0)=P_{\underline{X}}(0,0,0)+P_{\underline{X}}(0,0,1)=\frac{2}{8}+\frac{1}{8}=\frac{3}{8} & P_{\underline{Y}}(0,1)=0 \\
P_{\underline{Y}}(1,0)=P_{\underline{X}}(0,1,0)+P_{\underline{X}}(1,0,0)+P_{\underline{X}}(1,0,1)=\frac{1}{8}+\frac{1}{8}+\frac{1}{8}=\frac{3}{8} & P_{\underline{Y}}(1,1)=P_{\underline{X}}(0,1,1)=\frac{1}{8} \\
P_{\underline{Y}}(2,0)=P_{\underline{X}}(1,1,0)=\frac{1}{8} & P_{\underline{Y}}(2,1)=0
\end{array}$$(la somma fa 1, come deve essere).
### Esempio (con $m=2$ e $n=1$)
Essendo $n=1$ si può scrivere $Y$ anziché $\underline{Y}$. Supponiamo di avere $$P_{\underline{X}}(0,0)=\frac{2}{20};\quad P_{\underline{X}}(0,1)=P_{\underline{X}}(1,0)=P_{\underline{X}}(1,1)=\frac{3}{20};\quad P_{\underline{X}}(0,2)=P_{\underline{X}}(2,0)=\frac{1}{20};\quad P_{\underline{X}}(2,2)=\frac{7}{20}$$Sia $Y=(X_{1}+X_{2})^{2}$; allora $\delta_{Y}=\{0,1,4,16\}$, ed inoltre $$\begin{array}{l}
P_{Y}(0)=P_{\underline{X}}(0,0)=\frac{2}{20} \\
P_{Y}(1)=P_{\underline{X}}(0,1)+P_{\underline{X}}(1,0)=\frac{3}{20}+\frac{3}{20}=\frac{6}{20} \\
P_{Y}(4)=P_{\underline{X}}(1,1)+P_{\underline{X}}(0,2)+P_{\underline{X}}(2,0)=\frac{3}{20}+\frac{1}{20}+\frac{1}{20}=\frac{5}{20} \\
P_{Y}(16)=P_{\underline{X}}(2,2)=\frac{7}{20}
\end{array}$$(la somma fa 1, come deve essere).
## Una classe generale di esempi: somme di v.a.
Vogliamo trattare il caso in cui $n=1$ e $$f(x_{1},\dots,x_{m})=x_{1}+\dots+x_{m}\quad\quad\forall\ (x_{1},\dots,x_{m})\in \mathbb{R}^{m}$$Quindi si ha $$\begin{bmatrix}
P_{Y}(y)=\sum_{\underline{x}\in \delta_{\underline{X}}\ :\ x_{1}+\dots+x_{m}=y}P_{\underline{X}}(\underline{x})
\end{bmatrix}$$Vedremo ora alcuni casi specifici con $m=2$; in particolare, per alcuni casi tra questi, il passaggio da $m=2$ a $m$ generico sarà semplice procedendo per induzione.
> [!warning] Nota sulla notazione dei parametri
> Nei casi 2 e 3 che seguono il numero di prove delle binomiali è indicato qui con $n_{1},n_{2}$ (e $n_{1},\dots,n_{m}$ nel caso generale), per non confonderlo con la dimensione $m$ del vettore. Sulle slide manoscritte la lettera usata per questi parametri è la stessa impiegata per la dimensione.

### Caso specifico 1 (lancio di due dadi equi)
$$P_{\underline{X}}(x_{1},x_{2})=\frac{1}{36}\quad\quad\forall\ \underline{x}=(x_{1},x_{2})\in\{1,\dots,6\}\times\{1,\dots,6\}$$Sia $Y=X_{1}+X_{2}$, con $\delta_{Y}=\{2,3,4,5,6,7,8,9,10,11,12\}$. Allora $$P_{Y}(y)=\sum_{\underline{x}\in\{1,\dots,6\}\times\{1,\dots,6\}\ :\ x_{1}+x_{2}=y}P_{\underline{X}}(\underline{x})=\frac{\#\{(x_{1},x_{2}):x_{1}+x_{2}=y\}}{36}$$e recuperiamo i risultati già visti in passato: $$\begin{array}{lll}
P_{Y}(2)=P_{Y}(12)=\frac{1}{36}, & P_{Y}(3)=P_{Y}(11)=\frac{2}{36}, & P_{Y}(4)=P_{Y}(10)=\frac{3}{36}, \\
P_{Y}(5)=P_{Y}(9)=\frac{4}{36}, & P_{Y}(6)=P_{Y}(8)=\frac{5}{36}, & P_{Y}(7)=\frac{6}{36}
\end{array}$$La somma vale $2\cdot \frac{1}{36}+2\cdot \frac{2}{36}+2\cdot \frac{3}{36}+2\cdot \frac{4}{36}+2\cdot \frac{5}{36}+\frac{6}{36}=\frac{2+4+6+8+10+6}{36}=\frac{36}{36}=1$.
### Caso specifico 2 (somma di 2 binomiali indipendenti con lo stesso parametro $p$)
Siano $X_{1}\sim BIN(n_{1},p)$ e $X_{2}\sim BIN(n_{2},p)$ **indipendenti**. Allora, per la [[Variabili aleatorie multidimensionali discrete#Proposizione (condizione necessaria e sufficiente)|caratterizzazione dell'indipendenza]], $$P_{\underline{X}}(x_{1},x_{2})=P_{X_{1}}(x_{1})P_{X_{2}}(x_{2})=\binom{n_{1}}{x_{1}}p^{x_{1}}(1-p)^{n_{1}-x_{1}}\binom{n_{2}}{x_{2}}p^{x_{2}}(1-p)^{n_{2}-x_{2}}=\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}p^{x_{1}+x_{2}}(1-p)^{n_{1}+n_{2}-(x_{1}+x_{2})}$$per ogni $(x_{1},x_{2})\in\{0,1,\dots,n_{1}\}\times\{0,1,\dots,n_{2}\}$.
Sia $Y=X_{1}+X_{2}$, con $\delta_{Y}=\{0,1,\dots,n_{1}+n_{2}\}$. Allora, per ogni $y\in \delta_{Y}$, $$P_{Y}(y)=\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}p^{\overset{=y}{\overbrace{x_{1}+x_{2}}}}(1-p)^{n_{1}+n_{2}-\overset{=y}{\overbrace{(x_{1}+x_{2})}}}=p^{y}(1-p)^{n_{1}+n_{2}-y}\underset{=\binom{n_{1}+n_{2}}{y}}{\underbrace{\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}}}=\binom{n_{1}+n_{2}}{y}p^{y}(1-p)^{n_{1}+n_{2}-y}$$dove per la somma dei prodotti di coefficienti binomiali si usano le formule viste per l'[[Distribuzioni binomiale e ipergeometrica#Caso 2): distribuzione ipergeometrica|ipergeometrica]].
> [!quote] Commento
> $$Y=X_{1}+X_{2}\sim BIN(n_{1}+n_{2},p)$$

#### Altri commenti (1ª parte): estensione a $m$ addendi
Il risultato si estende al caso di $m$ addendi indipendenti: $$\begin{cases}
X_{1}\sim BIN(n_{1},p) \\
\quad\vdots \\
X_{m}\sim BIN(n_{m},p)
\end{cases}\text{indip.}\quad\implies\quad X_{1}+\dots+X_{m}\sim BIN(n_{1}+\dots+n_{m},p)$$Il risultato non sorprende: ognuna delle v.a. $X_{i}$ (per $i\in\{1,\dots,m\}$) conta il numero di successi su $n_{i}$ prove indipendenti, tutte con probabilità di successo $p$; quindi, se consideriamo la somma (e gli addendi sono indipendenti), è come se contassimo il numero di successi su $n_{1}+\dots+n_{m}$ prove tutte con probabilità di successo $p$.
Quindi è importante che **il parametro $p$ sia sempre lo stesso**; e senza l'ipotesi di indipendenza il risultato non è vero.
#### Altri commenti (2ª parte): controesempio senza indipendenza
> [!question] Segnalato dal prof come "un po' difficile"

Sia $p\in(0,1)$, cioè $p\neq 0$ e $p\neq 1$; siano $m=2$, $X_{1}\sim BIN(n,p)$ e $X_{2}=X_{1}$. Quindi in particolare $X_{2}\sim BIN(n,p)$. Allora si ha $$\begin{cases}
P(\{X_{1}=0\}\cap\{X_{2}=0\})=P(X_{1}=0)=(1-p)^{n} \\
P(X_{1}=0)P(X_{2}=0)=(1-p)^{n}(1-p)^{n}=(1-p)^{2n}
\end{cases}\text{diversi tra loro}\implies X_{1},X_{2}\text{ non sono indipendenti}$$Inoltre $X_{1}+X_{2}=2X_{1}$, e quindi $P(X_{1}+X_{2}\in\{\text{numeri dispari}\})=0$; quindi "$X_{1}+X_{2}\sim BIN(\underset{=2n}{\underbrace{n+n}},p)$" è **falsa**, perché tutti i valori in $\{0,1,2,\dots,2n-1,2n\}$ dovrebbero avere probabilità positiva.
### Caso specifico 3 (somma di 2 poissoniane indipendenti)
Siano $X_{1}\sim POISSON(\lambda_{1})$ e $X_{2}\sim POISSON(\lambda_{2})$ **indipendenti**. Allora $$P_{\underline{X}}(x_{1},x_{2})=P_{X_{1}}(x_{1})P_{X_{2}}(x_{2})=\frac{\lambda_{1}^{x_{1}}}{x_{1}!}e^{-\lambda_{1}}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-\lambda_{2}}=\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-(\lambda_{1}+\lambda_{2})}$$per ogni $(x_{1},x_{2})\in\{0,1,2,\dots\}\times\{0,1,2,\dots\}$.
Sia $Y=X_{1}+X_{2}$, con $\delta_{Y}=\{0,1,2,\dots\}$. Allora $$\begin{array}{ll}
P_{Y}(y) & =\displaystyle\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-(\lambda_{1}+\lambda_{2})}=e^{-(\lambda_{1}+\lambda_{2})}\sum_{x_{1}=0}^{y}\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{y-x_{1}}}{(y-x_{1})!} \\
 & =\frac{e^{-(\lambda_{1}+\lambda_{2})}}{y!}\displaystyle\sum_{x_{1}=0}^{y}\underset{=\binom{y}{x_{1}}}{\underbrace{\frac{y!}{x_{1}!(y-x_{1})!}}}\lambda_{1}^{x_{1}}\lambda_{2}^{y-x_{1}}\overset{\text{binomio di Newton}}{=}\frac{e^{-(\lambda_{1}+\lambda_{2})}}{y!}(\lambda_{1}+\lambda_{2})^{y}=\frac{(\lambda_{1}+\lambda_{2})^{y}}{y!}e^{-(\lambda_{1}+\lambda_{2})}
\end{array}$$
> [!quote] Commento
> $$Y=X_{1}+X_{2}\sim POISSON(\lambda_{1}+\lambda_{2})$$

#### Altri commenti
Il risultato si estende al caso di $m$ addendi indipendenti (simile a quello per le binomiali visto prima): $$\begin{cases}
X_{1}\sim POISSON(\lambda_{1}) \\
\quad\vdots \\
X_{m}\sim POISSON(\lambda_{m})
\end{cases}\text{indip.}\quad\implies\quad X_{1}+\dots+X_{m}\sim POISSON(\lambda_{1}+\dots+\lambda_{m})$$Senza l'ipotesi di indipendenza il risultato non è vero in generale. Un controesempio è il seguente: $m=2$, $X_{1}\sim POISSON(\lambda)$ e $X_{2}=X_{1}$ (allora $X_{2}\sim POISSON(\lambda)$). Si ha $$\begin{cases}
P(\{X_{1}=0\}\cap\{X_{2}=0\})=P(X_{1}=0)=e^{-\lambda} \\
P(X_{1}=0)P(X_{2}=0)=e^{-\lambda}\cdot e^{-\lambda}=e^{-2\lambda}
\end{cases}\implies X_{1},X_{2}\text{ non sono indipendenti}$$Inoltre $X_{1}+X_{2}=2X_{1}$ e quindi $P(X_{1}+X_{2}\in\{\text{numeri dispari}\})=0$; quindi "$X_{1}+X_{2}\sim POISSON(\lambda+\lambda)=POISSON(2\lambda)$" è **falsa**, perché tutti gli interi non negativi dovrebbero avere probabilità positiva.
> [!info] Esercizi della lezione 11
> Le pp. 13-26 della lezione 11 contengono esercizi su densità congiunte discrete, marginali e indipendenza (fra cui una congiunta del tipo $P_{\underline{X}}(x_{1},x_{2})=(1-p_{2})^{x_{2}-1}(1-p_{1})^{x_{1}-x_{2}}p_{1}p_{2}$ per $x_{1}\geq x_{2}\geq 1$). Sono esercizi puri: la loro sede è la cartella `Esercizi/`.
> Vale però la pena ricordare la **tecnica** usata per verificare che una congiunta a supporto "triangolare" è ben posta: si può sommare fissando $x_{1}$ e variando $x_{2}$ (sulle verticali), oppure fissando $x_{2}$ e variando $x_{1}$ (sulle orizzontali). Per usare le formule sulle [[Distribuzione geometrica#Formula della serie geometrica|serie geometriche]] conviene la seconda.

--- Fine lezione 11 ---

---
Nota precedente: [[Variabili aleatorie multidimensionali discrete]]. Nota successiva: [[Massimi e minimi di variabili aleatorie discrete]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
