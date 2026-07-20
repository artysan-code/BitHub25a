## Es4 — Trasformazione di variabile continua
Quarto esercizio dello scritto. Viene data la densità $f_X$ di una variabile aleatoria **continua** e si chiede la **funzione di distribuzione** $F_Y$ di una trasformazione $Y=g(X)$.

È lo slot più ripetitivo dei sei: il procedimento è identico in ogni appello, cambia solo la funzione $g$ (radice, quadrato, esponenziale, logaritmo, valore assoluto). Imparato lo schema, si risolve a memoria.

> [!info] Non c'è ancora una nota di teoria sul continuo
> Gli appunti di [[Cap 3 - Modelli Discreti|teoria]] coprono per ora solo le variabili aleatorie discrete: il prof introduce le continue più avanti nel corso. Finché quelle note non arrivano, questa è autosufficiente.

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

$X$ vive su $(-1,1)$, quindi $\lvert X\rvert$ vive su $[0,1]$: $P(0\le Y\le1)=1$ e lo scheletro è

$$F_Y(y)=\begin{cases}0 & \text{se } y\le0\\ (*) & \text{se } 0<y<1\\ 1 & \text{se } y\ge1\end{cases}$$

Il valore assoluto è **non monotono**: la condizione $\lvert X\rvert\le y$ equivale a $-y\le X\le y$. E poiché la densità è definita a tratti, l'integrale si spezza in $(-y,0)$ e $(0,y)$, dove $f_X$ ha due espressioni diverse:

$$(*)=P(-y\le X\le y)=\int_{-y}^{0}\frac{1}{2}\,dx+\int_{0}^{y}x\,dx=\frac{y}{2}+\frac{y^2}{2}=\frac{y+y^2}{2}$$

Controllo: per $y=1$ viene $\frac{1+1}{2}=1$, coerente con il fatto che $F_Y$ deve raggiungere 1 alla fine del supporto. **Questo controllo va sempre fatto**: costa un secondo e intercetta gli errori di integrazione.
#### Radice di una uniforme — appello del 20 Febbraio 2026
Siano $b>a>0$. Sia $X\sim U(a^4,b^4)$. Trovare la funzione di distribuzione di $Y=\sqrt{X}$.

**Svolgimento**

La densità di una uniforme su $(a^4,b^4)$ è $f_X(x)=\frac{1}{b^4-a^4}$ su quell'intervallo. La radice manda $(a^4,b^4)$ in $(a^2,b^2)$, quindi $P(a^2\le Y\le b^2)=1$.

Per $a^2<y<b^2$, isolando $X$:

$$(*)=P(\sqrt{X}\le y)=P(X\le y^2)=\int_{a^4}^{y^2}\frac{1}{b^4-a^4}\,dx=\frac{y^2-a^4}{b^4-a^4}$$

L'integrale parte da $a^4$, non da $-\infty$: sotto $a^4$ la densità è nulla. Scriverlo come $\int_{-\infty}^{y^2}$ è corretto ma poi va comunque ristretto al supporto.
#### Esponenziale di una potenza — appello del 19 Giugno 2026
Sia $\alpha>0$ e $f_X(x)=\alpha x^{\alpha-1}\mathbb{1}_{(0,1)}(x)$. Trovare la funzione di distribuzione di $Y=e^{\beta X}$ per $\beta>0$.

**Svolgimento**

$X$ vive su $(0,1)$, quindi $Y=e^{\beta X}$ vive su $(e^0,e^{\beta})=(1,e^{\beta})$.

Per $1<y<e^{\beta}$ si isola $X$ passando ai logaritmi — $\beta>0$ garantisce che il verso non cambi:

$$(*)=P(e^{\beta X}\le y)=P(\beta X\le\log y)=P\left(X\le\frac{1}{\beta}\log y\right)=\int_{0}^{\frac{1}{\beta}\log y}\alpha x^{\alpha-1}dx=\left[x^{\alpha}\right]_{0}^{\frac{1}{\beta}\log y}=\left(\frac{1}{\beta}\log y\right)^{\alpha}$$

Controllo agli estremi: per $y=e^{\beta}$ si ottiene $\left(\frac{\beta}{\beta}\right)^{\alpha}=1$. Torna.
### Esercizi svolti — varianti dagli appelli precedenti
#### Trasformazione decrescente: il verso si ribalta — appello del 20 Giugno 2023
Sia $b>0$ e $f_X(x)=\frac{e^{x}}{e^{b}-1}\mathbb{1}_{(0,b)}(x)$. Trovare la funzione di distribuzione di $Y=-\log\left(\frac{X}{b}\right)$.

**Svolgimento**

$X$ vive su $(0,b)$: quando $X\to b$ si ha $Y\to0$, quando $X\to0^+$ si ha $Y\to+\infty$. Quindi $P(Y>0)=1$ e $F_Y(y)=0$ per $y\le0$, senza estremo destro finito.

Per $y>0$, isolando $X$ — e qui il logaritmo con il segno meno **inverte** la disuguaglianza:

$$P(Y\le y)=P\left(-\log\frac{X}{b}\le y\right)=P\left(\log\frac{X}{b}\ge-y\right)=P\left(X\ge be^{-y}\right)$$

$$=\int_{be^{-y}}^{b}\frac{e^{x}}{e^{b}-1}dx=\left[\frac{e^{x}}{e^{b}-1}\right]_{be^{-y}}^{b}=\frac{e^{b}-e^{be^{-y}}}{e^{b}-1}$$

> [!question] Come accorgersi del ribaltamento
> Se $g$ è **decrescente**, valori grandi di $X$ danno valori piccoli di $Y$: l'evento $\{Y\le y\}$ corrisponde alla **coda destra** di $X$. Un modo veloce per non sbagliare: chiedersi «se $X$ è grande, $Y$ è grande o piccolo?» prima di scrivere l'integrale.

#### Trasformazione con radice e densità esponenziale — appello del 20 Febbraio 2025
Sia $f_X(x)=\frac{e^{-x}}{1-e^{-b}}\mathbb{1}_{(0,b)}(x)$. Trovare la funzione di distribuzione di $Y=\sqrt{X}$.

**Svolgimento**

$X$ vive su $(0,b)$, quindi $Y$ vive su $(0,\sqrt{b})$.

Per $0<y<\sqrt{b}$:

$$(*)=P(\sqrt{X}\le y)=P(X\le y^{2})=\int_{0}^{y^{2}}\frac{e^{-x}}{1-e^{-b}}dx=\frac{\left[-e^{-x}\right]_{0}^{y^{2}}}{1-e^{-b}}=\frac{1-e^{-y^{2}}}{1-e^{-b}}$$

Il denominatore $1-e^{-b}$ è la **costante di normalizzazione**: serve perché la densità esponenziale è stata troncata a $(0,b)$ e deve comunque integrare a 1. Non va toccata durante il calcolo, si trascina fino alla fine.
#### Con calcolo della mediana — appello del 12 Luglio 2022
Sia $f_X(x)=2x\,\mathbb{1}_{(0,1)}(x)$. **D7)** Trovare la funzione di distribuzione di $Y=e^{X}-1$. **D8)** Detta $m$ la mediana di $Y$ (il valore per cui $F_Y(m)=\frac{1}{2}$), verificare che $m=e^{1/\sqrt{2}}-1$.

**Svolgimento**

**D7)** $X$ vive su $(0,1)$, quindi $Y$ vive su $(e^0-1,e^1-1)=(0,e-1)$. Per $y$ in quell'intervallo:

$$F_Y(y)=P(e^{X}-1\le y)=P(e^{X}\le y+1)=P\big(X\le\log(y+1)\big)=\int_{0}^{\log(y+1)}2x\,dx=\log^{2}(y+1)$$

**D8)** La mediana si trova risolvendo $F_Y(m)=\frac{1}{2}$:

$$\log^{2}(m+1)=\frac{1}{2}\ \Rightarrow\ \log(m+1)=\frac{1}{\sqrt{2}}\ \Rightarrow\ m+1=e^{1/\sqrt{2}}\ \Rightarrow\ m=e^{1/\sqrt{2}}-1$$

Il prof propone anche la **verifica diretta**, che è più sicura quando il risultato è dato: si sostituisce e si controlla che $F_Y(e^{1/\sqrt{2}}-1)=\log^2(e^{1/\sqrt{2}})=\left(\frac{1}{\sqrt{2}}\right)^2=\frac{1}{2}$.
### Se viene chiesta la densità $f_Y$
Nel formato 2025-2026 la richiesta è sempre la **funzione di distribuzione**, ma se una traccia chiedesse la densità basta derivare:

$$f_Y(y)=F_Y'(y)$$

sull'intervallo dove $F_Y$ è data da $(*)$, e $f_Y(y)=0$ fuori. Non si deriva mai la parte costante: lì la densità è nulla.
### Trappole ricorrenti
- **Saltare lo scheletro a tre casi**: la risposta è $F_Y$ su tutto $\mathbb{R}$, non solo l'espressione centrale.

- **Supporto sbagliato**: si ottiene applicando $g$ agli estremi del supporto di $X$. Con $g$ decrescente gli estremi si **scambiano**.

- **Verso della disuguaglianza** con $g$ decrescente ($-\log$, $1/X$, $-X$).

- **Non monotonia** ($X^2$, $\lvert X\rvert$): la condizione diventa un intervallo simmetrico. Con densità a tratti, l'integrale si spezza.

- **Estremi di integrazione**: si integra sull'intersezione fra $\{g(x)\le y\}$ e il **supporto di $f_X$**, non su tutto $\mathbb{R}$.

- **Costanti di normalizzazione** ($\frac{1}{1-e^{-b}}$, $\frac{1}{b^4-a^4}$): si portano avanti fino in fondo, non si semplificano per distrazione.

- **Controllo finale**: $F_Y$ calcolata all'estremo destro del supporto deve dare **esattamente 1**. È il test più rapido che esista su questo esercizio.
### Collegamenti
- Lo stesso meccanismo nel discreto: [[Es3 - Densità congiunta discreta]], dove $Y=g(X_1,X_2)$ si ottiene raggruppando le coppie invece di integrare.

- Slot gemello: [[Es5 - Speranza di variabile continua]], che usa la stessa $f_X$ ma chiede una media anziché una distribuzione.

- [[Es6 - Normale e teorema del limite centrale]] usa $\Phi$, che è la funzione di distribuzione della Normale standard — stesso oggetto, calcolato una volta per tutte.
