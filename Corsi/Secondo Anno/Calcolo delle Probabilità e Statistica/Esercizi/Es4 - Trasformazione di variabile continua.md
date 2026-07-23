## Es4 — Trasformazione di variabile continua
Quarto esercizio dello scritto: si dà la densità $f_X$ di una variabile aleatoria **continua** e si chiede la **funzione di distribuzione** $F_Y$ di una trasformazione $Y=g(X)$ (radice, quadrato, esponenziale, logaritmo, valore assoluto).
### Prima di tutto: cosa ti viene chiesto
La **funzione di distribuzione** è, per definizione, $F_Y(y)=P(Y\le y)$: una macchina che per ogni $y$ risponde *"con che probabilità $Y$ esce $\le y$?"*. È **esattamente** ciò che l'esercizio chiede, non un oggetto diverso da calcolare a parte — e il risultato **resta una funzione di $y$** (al contrario della speranza di [[Es5 - Speranza di variabile continua|Es5]], che è un numero).
Il problema pratico: non conosci $Y$ direttamente, hai solo la densità di $X$. Ma $Y=g(X)$, quindi
$$P(Y\le y)=P\big(g(X)\le y\big)$$
e questo è il **ponte**: traduce una domanda su $Y$ (che non sai calcolare) in una su $X$ (dove hai la densità e sai integrare). **Isolare $X$** dentro la disuguaglianza serve solo a trovare gli **estremi dell'integrale**.
### Lo schema che Macci usa sempre
Le sue soluzioni hanno **tutte** questa forma, parola per parola:

> Si ha $P(a\le Y\le b)=1$, da cui segue
> $$F_Y(y)=\begin{cases}0 & \text{se } y\le a\\ (*) & \text{se } a<y<b\\ 1 & \text{se } y\ge b\end{cases}$$
> Inoltre per $a<y<b$ si ha $(*)=\dots$

Quindi l'esercizio si scompone in **due mosse**, e la prima vale metà del voto:

1. **Trovare il supporto di $Y$**, cioè i valori $a$ e $b$ fra cui $Y$ vive di sicuro. Si ottengono applicando $g$ agli estremi del supporto di $X$.
2. **Calcolare $(*)$** solo nell'intervallo intermedio, riportando la condizione su $Y$ a una condizione su $X$ e integrando $f_X$.

> [!warning] Il supporto non è un dettaglio formale
> Scrivere solo l'espressione centrale senza lo scheletro a tre casi è una risposta incompleta: $F_Y$ è definita su tutto $\mathbb{R}$, e fuori dal supporto vale 0 o 1.
>
> Esempi: se $X$ vive su $(0,1)$ e $Y=e^{\beta X}$, allora $Y$ vive su $(1,e^{\beta})$. Se $X\sim U(a^4,b^4)$ e $Y=\sqrt{X}$, allora $Y$ vive su $(a^2,b^2)$.

### Il passaggio centrale, in dettaglio
$$(*)=P(Y\le y)=P\big(g(X)\le y\big)=P\big(X\in g^{-1}((-\infty,y])\big)=\int_{\{x\,:\,g(x)\le y\}}f_X(x)\,dx$$
In pratica: si **isola $X$** dentro la disuguaglianza, e poi si integra la densità sull'insieme risultante.

| $Y=g(X)$ | La condizione $g(X)\le y$ diventa | Attenzione |
|---|---|---|
| $\sqrt{X}$ | $X\le y^2$ | $y>0$ |
| $X^2$ | $-\sqrt{y}\le X\le\sqrt{y}$ | non monotona |
| $\lvert X\rvert$ | $-y\le X\le y$ | non monotona |
| $e^{\beta X}$ | $X\le\frac{1}{\beta}\log y$ | $\beta>0$ |
| $-\log(X/b)$ | $X\ge be^{-y}$ | **il verso si inverte** |

> [!warning] Le due trappole del passaggio
> **Funzione decrescente** → la disuguaglianza si **ribalta**: da $-\log(X/b)\le y$ si arriva a $X\ge be^{-y}$, e l'integrale va da $be^{-y}$ a $b$, non da 0.
>
> **Funzione non monotona** ($X^2$, $\lvert X\rvert$) → la condizione diventa un intervallo **simmetrico**, non una semiretta: $P(-y\le X\le y)$. Se la densità è definita a tratti, l'integrale si spezza in più pezzi.

### Esercizi svolti — formato 2025-2026
#### Trasformazione non monotona, densità a tratti — appello del 6 Febbraio 2026
Sia $X$ con densità
$$f_X(x)=\begin{cases}1/2 & \text{se }-1<x<0\\ x & \text{se } 0<x<1\\ 0 & \text{altrimenti}\end{cases}$$
Trovare la funzione di distribuzione di $Y=\lvert X\rvert$.
**Svolgimento**
**Passo 1 — trovare il supporto di $Y$.** La densità è definita a tratti su $(-1,0)$ e $(0,1)$, quindi il supporto di $X$ è l'unione $(-1,0)\cup(0,1)$, che ai fini della funzione di distribuzione si tratta come l'intervallo $(-1,1)$ (il singolo punto $x=0$ ha probabilità zero, come per ogni variabile continua). Qui però $g(x)=\lvert x\rvert$ è **non monotona** su $(-1,1)$: non si può applicare $g$ ai soli due estremi $-1$ e $1$ come se la funzione fosse crescente o decrescente, perché $g(-1)=g(1)=1$: applicare $g$ ai due estremi darebbe lo stesso valore e nasconderebbe il resto del range. Bisogna invece guardare il minimo e il massimo di $\lvert x\rvert$ al variare di $x$ in $(-1,1)$: il minimo è $0$, raggiunto (nel limite) quando $x\to0$; il massimo si avvicina a $1$ quando $x\to-1$ oppure $x\to1$. Quindi $\lvert X\rvert$ vive su $[0,1]$, cioè $P(0\le Y\le1)=1$, e secondo lo [[#Lo schema che Macci usa sempre|schema generale dei tre casi]] si scrive subito lo scheletro
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ (*) & \text{se } 0<y<1\\ 1 & \text{se } y\ge1\end{cases}$$
che si legge così: sotto $0$ è impossibile che $Y\le y$ (perché $Y\ge0$ sempre), quindi $F_Y(y)=0$; sopra o a $1$ è certo che $Y\le y$ (perché $Y\le1$ sempre), quindi $F_Y(y)=1$; tutto il lavoro sta nel calcolare $(*)$ per $y$ strettamente fra $0$ e $1$.

**Passo 2 — isolare $X$ nella disuguaglianza $\lvert X\rvert\le y$.** Applicando lo schema del [[#Il passaggio centrale, in dettaglio|passaggio centrale]] generale, $(*)=P(\lvert X\rvert\le y)$, e va riscritta come una condizione su $X$ soltanto. Qui interviene la trappola della **funzione non monotona**, già segnalata nella tabella e nell'avviso di questa nota: per $y\ge0$, la disuguaglianza $\lvert X\rvert\le y$ non diventa una semiretta come nei casi monotoni ($\sqrt X$, $e^{\beta X}$), ma un **intervallo simmetrico attorno a $0$**,
$$\lvert X\rvert\le y\iff-y\le X\le y,$$
perché il valore assoluto di un numero è $\le y$ esattamente quando quel numero sta fra $-y$ e $y$ (sia che $X$ sia positivo, negativo o nullo). Quindi
$$(*)=P(-y\le X\le y)=\int_{-y}^{y}f_X(x)\,dx.$$

**Passo 3 — spezzare l'integrale sui due pezzi della densità.** L'intervallo di integrazione $[-y,y]$, per $0<y<1$, attraversa il punto $x=0$ dove $f_X$ cambia espressione: a sinistra di $0$ vale $\frac12$, a destra vale $x$. Non si può quindi scrivere un unico integrale con una sola formula: bisogna **spezzare** l'intervallo esattamente nel punto dove la densità cambia, ottenendo due pezzi $(-y,0)$ e $(0,y)$, ciascuno interamente contenuto in una delle due metà del supporto (dato che $0<y<1$, si ha $-1<-y<0$ e $0<y<1$, quindi nessuno dei due pezzi esce dal supporto):
$$\int_{-y}^{y}f_X(x)\,dx=\int_{-y}^{0}\underbrace{\frac12}_{f_X\text{ su }(-1,0)}dx+\int_{0}^{y}\underbrace{x}_{f_X\text{ su }(0,1)}dx.$$

**Passo 4 — calcolare i due integrali.** Il primo integrale è quello di una costante su un intervallo di ampiezza $y$ (da $-y$ a $0$), quindi vale semplicemente $\frac12\cdot y$; il secondo è l'integrale immediato di $x$:
$$\int_{-y}^{0}\frac12\,dx=\frac12\big[x\big]_{-y}^{0}=\frac12\big(0-(-y)\big)=\frac{y}{2},\qquad\int_{0}^{y}x\,dx=\left[\frac{x^2}{2}\right]_0^{y}=\frac{y^2}{2}.$$
Sommando i due pezzi:
$$(*)=\frac{y}{2}+\frac{y^2}{2}=\frac{y+y^2}{2}.$$

**Passo 5 — controllo finale.** Come sempre in questo esercizio, si verifica che $F_Y$ raggiunga $1$ all'estremo destro del supporto: sostituendo $y=1$ nell'espressione trovata,
$$\frac{1+1^2}{2}=\frac{2}{2}=1,$$
coerente con lo scheletro del Passo 1, dove $F_Y(y)=1$ per $y\ge1$. **Questo controllo va sempre fatto**: costa un secondo e intercetta gli errori di integrazione. Mettendo insieme i tre pezzi dello scheletro, la funzione di distribuzione completa è
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ \dfrac{y+y^2}{2} & \text{se } 0<y<1\\ 1 & \text{se } y\ge1\end{cases}$$
#### Radice di una uniforme — appello del 20 Febbraio 2026
Siano $b>a>0$. Sia $X\sim U(a^4,b^4)$. Trovare la funzione di distribuzione di $Y=\sqrt{X}$.
**Svolgimento**
**Passo 1 — leggere la densità di partenza.** La traccia dà $X\sim U(a^4,b^4)$, con $b>a>0$: è una v.a. uniforme sull'intervallo $(a^4,b^4)$, quindi la sua densità è costante su quell'intervallo e nulla fuori,
$$f_X(x)=\begin{cases}\dfrac{1}{b^4-a^4} & \text{se } a^4<x<b^4\\ 0 & \text{altrimenti}\end{cases}$$
la costante $\frac{1}{b^4-a^4}$ è quella che rende l'area sotto $f_X$ pari a 1: è la lunghezza dell'intervallo, $b^4-a^4$, messa al denominatore, non un dato a parte.

**Passo 2 — trovare il supporto di $Y$ applicando $g$ agli estremi, e scrivere lo scheletro a tre casi.** Per lo [[#Lo schema che Macci usa sempre|schema generale]] di questo esercizio, il supporto di $Y=\sqrt X$ si ottiene applicando $g(x)=\sqrt x$ ai due estremi del supporto di $X$:
$$g(a^4)=\sqrt{a^4}=a^2\qquad g(b^4)=\sqrt{b^4}=b^2$$
Qui non c'è nessun valore assoluto da gestire: $\sqrt{a^4}=a^2$ vale per ogni $a$ reale, dato che $a^4=(a^2)^2$ e $a^2$ è già non negativo. Il vincolo $b>a>0$ serve a un'altra cosa: garantisce che $b^4>a^4$, cioè che l'intervallo $(a^4,b^4)$ sia ben ordinato e non vuoto (con $a$ negativo l'ordine tra le quarte potenze potrebbe rovesciarsi). La radice quadrata è una funzione **crescente** su $[0,+\infty)$ — non è il caso non monotono di $X^2$ o $\lvert X\rvert$ della [[#Il passaggio centrale, in dettaglio|tabella]] di questa nota — quindi manda l'estremo sinistro del supporto di $X$ nell'estremo sinistro del supporto di $Y$, e l'estremo destro nell'estremo destro, senza scambiarli: $(a^4,b^4)$ diventa $(a^2,b^2)$. Dunque $P(a^2\le Y\le b^2)=1$, e siccome $F_Y$ è definita su **tutto** $\mathbb{R}$ (non solo sul supporto di $Y$), fuori da quell'intervallo vale 0 o 1:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le a^2\\ (*) & \text{se } a^2<y<b^2\\ 1 & \text{se } y\ge b^2\end{cases}$$
Resta da calcolare $(*)$ solo per $a^2<y<b^2$: è lì che serve il lavoro vero.

**Passo 3 — isolare $X$ nella disuguaglianza $\sqrt X\le y$.** Il passaggio centrale della nota dice che si riporta la condizione su $Y$ a una condizione su $X$:
$$(*)=P(Y\le y)=P(\sqrt X\le y)=P\big(X\in\{x:\sqrt x\le y\}\big)$$
Nell'intervallo $a^2<y<b^2$ il valore $y$ è **positivo** (perché $a>0$ implica $a^2>0$, e $y>a^2$), quindi si possono elevare al quadrato entrambi i membri **senza cambiare il verso** della disuguaglianza: la radice è crescente e sia $\sqrt X$ che $y$ sono non negativi, non c'è alcun ribaltamento come nel caso decrescente della tabella,
$$\sqrt X\le y\ \Longleftrightarrow\ X\le y^{2}$$
quindi $(*)=P(X\le y^{2})$.

**Passo 4 — impostare l'integrale con gli estremi giusti.** Per calcolare $P(X\le y^2)$ si integra $f_X$ sull'insieme $\{x:x\le y^2\}$; ma $f_X$ è nulla per $x\le a^4$, quindi l'integrale deve partire da $a^4$ — l'estremo sinistro del supporto, dove la densità comincia a essere diversa da zero — non da $-\infty$:
$$(*)=\int_{a^4}^{y^2}f_X(x)\,dx=\int_{a^4}^{y^2}\frac{1}{b^4-a^4}\,dx$$
Qui non serve spezzare l'integrale a tratti: a differenza di altri esercizi di questa nota, $f_X$ ha un'unica espressione su tutto $(a^4,b^4)$, quindi basta un solo integrale fra $a^4$ e $y^2$, con $a^4<y^2<b^4$ quando $a^2<y<b^2$ (elevando al quadrato la disuguaglianza $a^2<y<b^2$, che preserva il verso perché tutti i termini sono positivi).

**Passo 5 — calcolare l'integrale.** L'integrando è costante rispetto a $x$, quindi si porta fuori dal segno di integrale e resta solo la lunghezza dell'intervallo di integrazione:
$$(*)=\frac{1}{b^4-a^4}\int_{a^4}^{y^2}dx=\frac{1}{b^4-a^4}\Big[x\Big]_{a^4}^{y^2}=\frac{y^{2}-a^{4}}{b^{4}-a^{4}}$$

**Passo 6 — comporre il risultato finale e controllare.** Sostituendo $(*)$ nello scheletro del Passo 2 si ottiene la funzione di distribuzione completa:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le a^2\\ \dfrac{y^{2}-a^{4}}{b^{4}-a^{4}} & \text{se } a^2<y<b^2\\ 1 & \text{se } y\ge b^2\end{cases}$$
Controllo: per $y=b^2$ si ottiene $\dfrac{b^4-a^4}{b^4-a^4}=1$, coerente con il fatto che $F_Y$ deve raggiungere 1 all'estremo destro del supporto — il conto torna.

Nota a margine: scrivere l'integrale come $\int_{-\infty}^{y^2}\frac{1}{b^4-a^4}\,dx$ non sarebbe sbagliato in sé, perché sotto $a^4$ la densità è comunque nulla; ma va comunque **ristretto** al supporto per poter essere calcolato, spezzandolo in $\int_{-\infty}^{a^4}0\,dx+\int_{a^4}^{y^2}\frac{1}{b^4-a^4}\,dx$ — che è esattamente l'integrale scritto al Passo 4.
#### Esponenziale di una potenza — appello del 19 Giugno 2026
Sia $\alpha>0$ e $f_X(x)=\alpha x^{\alpha-1}\mathbb{1}_{(0,1)}(x)$. Trovare la funzione di distribuzione di $Y=e^{\beta X}$ per $\beta>0$.
**Svolgimento**
**Passo 1 — trovare il supporto di $Y$.** Si applica $g(x)=e^{\beta x}$ agli estremi del supporto di $X$, che è $(0,1)$. Poiché $\beta>0$, la funzione $e^{\beta x}$ è **crescente**, quindi mantiene l'ordine: l'estremo sinistro $x=0$ va nell'estremo sinistro $g(0)=e^{0}=1$, e l'estremo destro $x=1$ va nell'estremo destro $g(1)=e^{\beta}$. Dunque $Y=e^{\beta X}$ vive su $(1,e^{\beta})$: $P(1<Y<e^{\beta})=1$. Ma $F_Y$ è comunque definita su **tutto** $\mathbb{R}$, non solo dentro il supporto: fuori da $(1,e^{\beta})$ vale semplicemente 0 o 1, e lo scheletro completo a tre casi è

$$F_Y(y)=\begin{cases}0 & \text{se } y\le1\\ (*) & \text{se } 1<y<e^{\beta}\\ 1 & \text{se } y\ge e^{\beta}\end{cases}$$

**Passo 2 — isolare $X$ nella disuguaglianza.** Nell'intervallo intermedio, per il passaggio centrale del metodo,

$$(*)=P(Y\le y)=P\big(e^{\beta X}\le y\big)$$

e per calcolarla si isola $X$ un passo alla volta. Primo passo: si applica il logaritmo a entrambi i membri. Il logaritmo è una funzione **crescente**, quindi applicarlo non cambia il verso della disuguaglianza:
$$e^{\beta X}\le y \iff \log\left(e^{\beta X}\right)\le\log y \iff \beta X\le\log y$$
Secondo passo: si divide per $\beta$. Qui è essenziale che $\beta>0$: dividere per un numero **positivo** non cambia il verso della disuguaglianza. Se fosse $\beta<0$, la funzione $e^{\beta X}$ diventerebbe **decrescente** in $X$ e, per lo stesso motivo per cui ogni trasformazione decrescente ribalta il verso (principio illustrato nella traccia del 20 Giugno 2023 qui sotto, dove è l'intera funzione $-\log(X/b)$ a essere decrescente, non un coefficiente), a questo punto il verso si ribalterebbe e si dovrebbe scrivere $X\ge\dots$. Con $\beta>0$ invece:
$$\beta X\le\log y \iff X\le\frac{1}{\beta}\log y$$
Quindi la condizione su $X$ è $X\le\frac{1}{\beta}\log y$, cioè $(*)=P\left(X\le\dfrac{1}{\beta}\log y\right)$.

**Passo 3 — impostare e calcolare l'integrale.** Per il principio $(*)=\int_{\{x\,:\,g(x)\le y\}}f_X(x)\,dx$, si integra $f_X$ sull'insieme trovato al Passo 2, intersecato con il supporto di $X$:
$$(*)=\int_{0}^{\frac{1}{\beta}\log y}\alpha x^{\alpha-1}\,dx$$
L'estremo inferiore è $0$ e non $-\infty$: sotto $0$ la densità $f_X$ è nulla, perché il supporto di $X$ è $(0,1)$. Qui $f_X$ ha un'unica espressione su tutto l'intervallo — a differenza dell'esercizio del 6 Febbraio 2026 sopra, non serve spezzare l'integrale in più pezzi. Si calcola con la primitiva: siccome $\frac{d}{dx}x^{\alpha}=\alpha x^{\alpha-1}$,
$$\int_{0}^{\frac{1}{\beta}\log y}\alpha x^{\alpha-1}\,dx=\left[x^{\alpha}\right]_{0}^{\frac{1}{\beta}\log y}=\left(\frac{1}{\beta}\log y\right)^{\alpha}-0^{\alpha}=\left(\frac{1}{\beta}\log y\right)^{\alpha}$$

**Passo 4 — assemblare $F_Y$ e verificare agli estremi.** Sostituendo $(*)$ nello scheletro del Passo 1:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le1\\ \left(\dfrac{1}{\beta}\log y\right)^{\alpha} & \text{se } 1<y<e^{\beta}\\ 1 & \text{se } y\ge e^{\beta}\end{cases}$$
Controllo: $F_Y$ deve raggiungere 1 all'estremo destro del supporto, $y=e^{\beta}$. Sostituendo,
$$F_Y(e^{\beta})=\left(\frac{1}{\beta}\log e^{\beta}\right)^{\alpha}=\left(\frac{\beta}{\beta}\right)^{\alpha}=1^{\alpha}=1$$
Torna: il controllo agli estremi intercetta eventuali errori di segno o di integrazione.
### Esercizi svolti — varianti dagli appelli precedenti
#### Trasformazione decrescente: il verso si ribalta — appello del 20 Giugno 2023
Sia $b>0$ e $f_X(x)=\frac{e^{x}}{e^{b}-1}\mathbb{1}_{(0,b)}(x)$. Trovare la funzione di distribuzione di $Y=-\log\left(\frac{X}{b}\right)$.
**Svolgimento**
**Passo 1 — trovare il supporto di $Y$, con $g$ decrescente.** $X$ vive su $(0,b)$: per trovare dove vive $Y=g(X)=-\log(X/b)$ si applica $g$ agli estremi del supporto di $X$. Ma qui $g$ è **decrescente**, e una funzione decrescente **scambia l'ordine** degli estremi: l'estremo sinistro di $X$ non produce l'estremo sinistro di $Y$, produce quello destro, e viceversa. Quando $X\to b^{-}$ (il valore più grande che $X$ può assumere) si ha $g(X)\to-\log(1)=0$; quando $X\to0^{+}$ (il valore più piccolo) si ha $g(X)\to-\log(0^{+})=+\infty$. Quindi $Y$ vive su $(0,+\infty)$: c'è un estremo sinistro finito, $0$, ma **nessun estremo destro finito**.

Lo scheletro a tre casi resta lo stesso principio di sempre — $F_Y$ è definita su tutto $\mathbb{R}$ e vale $0$ sotto il supporto — ma senza un estremo destro $b$ finito il terzo caso "$1$ se $y\ge b$" non esiste come caso a sé stante: si riduce a due soli casi,
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ (*) & \text{se } y>0\end{cases}$$
e sarà il controllo del Passo 4 a verificare che, coerentemente, $(*)\to1$ quando $y\to+\infty$ — l'analogo del "vale 1 all'estremo destro", spostato al limite perché quell'estremo è infinito.

**Passo 2 — isolare $X$ nella disuguaglianza: qui il verso si ribalta.** Per $y>0$ si parte dalla definizione $(*)=P(Y\le y)=P(g(X)\le y)$ e si isola $X$:
$$-\log\frac{X}{b}\le y$$
Si moltiplicano entrambi i membri per $-1$ per eliminare il segno meno davanti al logaritmo — e moltiplicare una disuguaglianza per un numero negativo **ne inverte il verso**:
$$\log\frac{X}{b}\ge-y$$
Ora si esponenzia: l'esponenziale è una funzione **crescente**, quindi applicarla a entrambi i membri non cambia (una seconda volta) il verso della disuguaglianza:
$$\frac{X}{b}\ge e^{-y}\ \Rightarrow\ X\ge be^{-y}$$
Il risultato è una condizione "$X\ge\dots$", cioè una **coda destra** di $X$ — non una coda sinistra, come capiterebbe con una $g$ crescente. Il modo per non sbagliare senza rifare il conto ogni volta: se $g$ è decrescente, i valori grandi di $X$ danno i valori piccoli di $Y$; quindi l'evento $\{Y\le y\}$, che raccoglie i valori piccoli di $Y$, corrisponde ai valori **grandi** di $X$.

**Passo 3 — tradurre in integrale, con la sua costante di normalizzazione.** Sostituendo la condizione del Passo 2 nella definizione di $(*)$:
$$(*)=P(X\ge be^{-y})=\int_{be^{-y}}^{b}f_X(x)\,dx$$
Gli estremi dell'integrale sono i due punti tra cui $X$ deve stare: quello **inferiore** è $be^{-y}$, appena isolato al Passo 2; quello **superiore** è $b$, l'estremo *destro* del supporto di $X$ — non $+\infty$, perché fuori da $(0,b)$ la densità $f_X$ è nulla e non contribuirebbe comunque all'integrale. Sostituendo l'espressione di $f_X$:
$$(*)=\int_{be^{-y}}^{b}\frac{e^{x}}{e^{b}-1}\,dx=\frac{1}{e^{b}-1}\left[e^{x}\right]_{be^{-y}}^{b}=\frac{e^{b}-e^{be^{-y}}}{e^{b}-1}$$
Il fattore $\dfrac{1}{e^{b}-1}$ non dipende da $x$: esce dall'integrale invariato, ed è la **costante di normalizzazione** che rende $f_X$ una densità vera, dato che $\int_{0}^{b}e^{x}\,dx=e^{b}-1$ e quindi $\int_0^b f_X=1$. Si trascina fino in fondo al calcolo senza toccarla.

**Passo 4 — controllo ai due estremi.** Poiché il supporto di $Y$ non ha un estremo destro finito, il controllo che di solito si fa sostituendo l'estremo diventa un **limite**. Per $y\to0^{+}$ si ha $be^{-y}\to b$, quindi $(*)\to\dfrac{e^{b}-e^{b}}{e^{b}-1}=0$: coerente con il raccordo al caso $y\le0$ dello scheletro del Passo 1. Per $y\to+\infty$ si ha $be^{-y}\to0^{+}$, quindi $e^{be^{-y}}\to e^{0}=1$ e
$$(*)\longrightarrow\frac{e^{b}-1}{e^{b}-1}=1,$$
esattamente il comportamento atteso da una funzione di distribuzione il cui supporto si estende all'infinito. In conclusione:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\[4pt] \dfrac{e^{b}-e^{be^{-y}}}{e^{b}-1} & \text{se } y>0\end{cases}$$

> [!question] Come accorgersi del ribaltamento
> Se $g$ è **decrescente**, valori grandi di $X$ danno valori piccoli di $Y$: l'evento $\{Y\le y\}$ corrisponde alla **coda destra** di $X$. Un modo veloce per non sbagliare: chiedersi «se $X$ è grande, $Y$ è grande o piccolo?» prima di scrivere l'integrale.

#### Trasformazione con radice e densità esponenziale — appello del 20 Febbraio 2025
Sia $f_X(x)=\frac{e^{-x}}{1-e^{-b}}\mathbb{1}_{(0,b)}(x)$. Trovare la funzione di distribuzione di $Y=\sqrt{X}$.
**Svolgimento**
**Passo 1 — trovare il supporto di $Y$.** Il supporto si ottiene applicando $g$ agli estremi del supporto di $X$: qui $X$ vive su $(0,b)$ (è lì che $f_X$ è diversa da zero) e $g(x)=\sqrt{x}$ è crescente, quindi manda l'estremo sinistro $0$ in $g(0)=0$ e l'estremo destro $b$ in $g(b)=\sqrt{b}$. Dunque $P(0\le Y\le\sqrt{b})=1$, e come sempre in questo esercizio va scritto lo scheletro completo a tre casi — $F_Y$ è definita su **tutto** $\mathbb{R}$, non solo sul supporto di $Y$:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ (*) & \text{se } 0<y<\sqrt{b}\\ 1 & \text{se } y\ge\sqrt{b}\end{cases}$$
Si legge così: sotto il supporto $F_Y(y)=P(Y\le y)=0$ perché $Y$ non scende mai sotto $0$; sopra il supporto $F_Y(y)=1$ perché $Y$ è certamente $\le y$ non appena $y\ge\sqrt b$; resta da calcolare solo $(*)$, il valore intermedio.

**Passo 2 — il passaggio centrale, in generale.** Come per ogni traccia di questo esercizio ([[#Il passaggio centrale, in dettaglio|passaggio centrale]]), $(*)$ si ottiene sempre riportando la condizione su $Y$ a una condizione su $X$ e integrando $f_X$ su quell'insieme:
$$(*)=P(Y\le y)=P\big(g(X)\le y\big)=P\big(X\in\{x: g(x)\le y\}\big)=\int_{\{x\,:\,g(x)\le y\}}f_X(x)\,dx$$
In pratica servono due mosse, nell'ordine: prima **isolare $X$** dentro la disuguaglianza $g(X)\le y$, poi **integrare** $f_X$ sull'insieme di $x$ così ottenuto.

**Passo 3 — isolare $X$ per $g(x)=\sqrt{x}$.** Nell'intervallo intermedio $y>0$, sia $\sqrt{X}$ sia $y$ sono quantità non negative: elevare al quadrato ambo i membri di una disuguaglianza fra numeri non negativi **preserva il verso**, quindi
$$\sqrt{X}\le y\ \Longleftrightarrow\ X\le y^{2}.$$
Qui non scattano le due trappole tipiche di questo esercizio: $g$ è **monotona** (a differenza di $X^2$, dove la condizione diventerebbe l'intervallo simmetrico $-\sqrt{y}\le X\le\sqrt{y}$, o di $\lvert X\rvert$, dove sarebbe $-y\le X\le y$) ed è **crescente**, non decrescente (a differenza di $-\log(X/b)$, dove la disuguaglianza si sarebbe ribaltata). Basta isolare $X$ così com'è, senza cambiare verso né spezzare in due code.

**Passo 4 — impostare e calcolare l'integrale.** Sostituendo la condizione del Passo 3 nella formula del Passo 2, $(*)=P(X\le y^2)$ diventa l'integrale di $f_X$ a partire da dove il supporto di $X$ **comincia** — cioè da $0$, l'estremo sinistro al di sotto del quale $f_X$ è nulla, non da $-\infty$ — fino a $y^2$:
$$(*)=P(X\le y^{2})=\int_{0}^{y^{2}}\frac{e^{-x}}{1-e^{-b}}\,dx$$
Il fattore $\dfrac{1}{1-e^{-b}}$ non dipende da $x$: è la **costante di normalizzazione**, necessaria perché la densità esponenziale $e^{-x}$ è stata **troncata** all'intervallo $(0,b)$ invece di vivere su tutto $(0,+\infty)$, ed è scelta apposta perché $\int_0^b\frac{e^{-x}}{1-e^{-b}}\,dx=1$. Essendo costante rispetto a $x$, si porta fuori dal segno di integrale e si trascina **invariata** fino al risultato finale:
$$(*)=\frac{1}{1-e^{-b}}\int_{0}^{y^{2}}e^{-x}\,dx=\frac{\big[-e^{-x}\big]_{0}^{y^{2}}}{1-e^{-b}}=\frac{-e^{-y^{2}}-(-e^{0})}{1-e^{-b}}=\frac{1-e^{-y^{2}}}{1-e^{-b}}$$

**Passo 5 — comporre $F_Y$ e controllo finale.** Si sostituisce $(*)$ nello scheletro del Passo 1:
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ \dfrac{1-e^{-y^{2}}}{1-e^{-b}} & \text{se } 0<y<\sqrt{b}\\ 1 & \text{se } y\ge\sqrt{b}\end{cases}$$
Controllo: per $y=\sqrt b$ si ha $y^2=b$, quindi $(*)=\dfrac{1-e^{-b}}{1-e^{-b}}=1$ — esattamente il valore che lo scheletro impone all'estremo destro del supporto. **Questo controllo va sempre fatto**: costa un secondo e conferma che la costante di normalizzazione è stata portata avanti correttamente fino in fondo.
#### Con calcolo della mediana — appello del 12 Luglio 2022
Sia $f_X(x)=2x\,\mathbb{1}_{(0,1)}(x)$. **D7)** Trovare la funzione di distribuzione di $Y=e^{X}-1$. **D8)** Detta $m$ la mediana di $Y$ (il valore per cui $F_Y(m)=\frac{1}{2}$), verificare che $m=e^{1/\sqrt{2}}-1$.
**Svolgimento**
**Passo 1 — enunciare lo schema generale.** Come per ogni traccia di questo esercizio (vedi [[#Lo schema che Macci usa sempre|lo schema che Macci usa sempre]]), se $g$ manda il supporto di $X$ in un intervallo $(a,b)$ allora $F_Y$ si scrive sempre con lo stesso scheletro a tre casi
$$F_Y(y)=\begin{cases}0 & \text{se } y\le a\\ (*) & \text{se } a<y<b\\ 1 & \text{se } y\ge b\end{cases}$$
e il valore centrale si ottiene isolando $X$ nella disuguaglianza e integrando $f_X$ sull'insieme risultante (vedi [[#Il passaggio centrale, in dettaglio|il passaggio centrale]]):
$$(*)=P(Y\le y)=P\big(g(X)\le y\big)=P\big(X\in\{x:g(x)\le y\}\big)=\int_{\{x:g(x)\le y\}}f_X(x)\,dx.$$
Si legge così: la prima mossa — sempre — è trovare $a$ e $b$ applicando $g$ agli estremi del supporto di $X$; questo fissa i due rami esterni, perché $F_Y$ è definita su **tutto** $\mathbb{R}$ e fuori dal supporto di $Y$ vale $0$ o $1$. Solo dopo si calcola $(*)$, e solo nell'intervallo intermedio.
**D7) Trovare la funzione di distribuzione di $Y=e^{X}-1$.** La densità è $f_X(x)=2x\,\mathbb{1}_{(0,1)}(x)$, quindi $X$ vive sul supporto $(0,1)$. Si applica $g(x)=e^{x}-1$ ai due estremi: $g(0)=e^{0}-1=0$ e $g(1)=e^{1}-1=e-1$. La funzione $g$ è **strettamente crescente** su $(0,1)$ (perché $e^{x}$ lo è), quindi manda l'intervallo $(0,1)$ esattamente nell'intervallo $(0,e-1)$, senza ribaltamenti: $P(0<Y<e-1)=1$, e lo scheletro del Passo 1 si concretizza in
$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ (*) & \text{se } 0<y<e-1\\ 1 & \text{se } y\ge e-1\end{cases}$$
Per $0<y<e-1$ si isola $X$ nella disuguaglianza $g(X)\le y$: essendo $g$ crescente, e il logaritmo — usato per disfare l'esponenziale — a sua volta crescente, il verso della disuguaglianza **non cambia**, a differenza dei casi con trasformazione decrescente dove passare al logaritmo la ribalta:
$$(*)=P(e^{X}-1\le y)=P(e^{X}\le y+1)=P\big(X\le\log(y+1)\big).$$
Resta da integrare $f_X$ sull'insieme trovato. L'integrale parte dall'estremo sinistro del supporto di $X$, cioè $0$ (non da $-\infty$: sotto $0$ la densità è nulla), e arriva a $\log(y+1)$, che per $0<y<e-1$ sta proprio dentro $(0,1)$:
$$(*)=\int_{0}^{\log(y+1)}2x\,dx=\Big[x^{2}\Big]_{0}^{\log(y+1)}=\log^{2}(y+1).$$
Quindi $F_Y(y)=\log^{2}(y+1)$ per $0<y<e-1$. Controllo agli estremi: per $y=e-1$ si ha $\log(y+1)=\log e=1$, dunque $F_Y(e-1)=1^{2}=1$, coerente con l'estremo destro del supporto di $Y$ trovato sopra.
**D8) Trovare la mediana di $Y$.** Per definizione la mediana $m$ è il valore per cui $F_Y(m)=\frac{1}{2}$, cioè il punto che divide la probabilità di $Y$ esattamente a metà. Poiché $F_Y$ cresce con continuità da $0$ a $1$ sull'intervallo $(0,e-1)$ (D7), un tale $m$ esiste unico ed è interno a quell'intervallo: si può quindi usare l'espressione $(*)=\log^{2}(y+1)$ trovata sopra, ponendo $y=m$:
$$\log^{2}(m+1)=\frac{1}{2}.$$
Si risolve un passo alla volta. Prima si estrae la radice quadrata: poiché $m>0$ implica $m+1>1$ e quindi $\log(m+1)>0$, si prende la radice **positiva**:
$$\log(m+1)=\frac{1}{\sqrt{2}}.$$
Poi si applica l'esponenziale a entrambi i membri, che disfa il logaritmo:
$$m+1=e^{1/\sqrt{2}}\quad\Longrightarrow\quad m=e^{1/\sqrt{2}}-1.$$
Il prof propone anche la **verifica diretta**, più sicura quando il risultato è già dato dalla traccia: si sostituisce $m=e^{1/\sqrt2}-1$ dentro $F_Y$ e si controlla che venga $\frac12$:
$$F_Y\big(e^{1/\sqrt{2}}-1\big)=\log^{2}\big(e^{1/\sqrt{2}}\big)=\left(\frac{1}{\sqrt{2}}\right)^{2}=\frac{1}{2}.$$
Torna: nel penultimo passaggio $\log\big(e^{1/\sqrt2}\big)=\frac{1}{\sqrt{2}}$ perché logaritmo ed esponenziale sono funzioni inverse.
### Se viene chiesta la densità $f_Y$
Nel formato 2025-2026 la richiesta è sempre la **funzione di distribuzione**, ma se una traccia chiedesse la densità basta derivare:
$$f_Y(y)=F_Y'(y)$$
sull'intervallo dove $F_Y$ è data da $(*)$, e $f_Y(y)=0$ fuori. Non si deriva mai la parte costante: lì la densità è nulla.
### Collegamenti
- Lo stesso meccanismo nel discreto: [[Es3 - Densità congiunta discreta]], dove $Y=g(X_1,X_2)$ si ottiene raggruppando le coppie invece di integrare.
- Slot gemello: [[Es5 - Speranza di variabile continua]], che usa la stessa $f_X$ ma chiede una media anziché una distribuzione.
- [[Es6 - Normale e teorema del limite centrale]] usa $\Phi$, che è la funzione di distribuzione della Normale standard — stesso oggetto, calcolato una volta per tutte.
