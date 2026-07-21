# Quantili di una variabile aleatoria continua
Valore che lascia alla propria sinistra una frazione $\alpha$ assegnata della probabilità; il caso $\alpha=\frac{1}{2}$ è la mediana.
## Definizione
Sia $X$ una v.a. continua con funzione di distribuzione $F_{X}$. Supponiamo che esista un intervallo $(m,M)$ dove $F_{X}$ è **strettamente crescente**; inoltre supponiamo che, se $t\notin(m,M)$, allora $F_{X}(t)=0$ oppure $F_{X}(t)=1$.
> [!info] Estremi infiniti ammessi
> Si ammette di poter avere $m=-\infty$ (allora non si avrà mai $F_{X}(t)=0$) e/o $M=+\infty$ (allora non si avrà mai $F_{X}(t)=1$).

Nelle ipotesi sopra, preso $\alpha\in(0,1)$, si definisce **quantile di ordine $\alpha$ di $X$** l'unico valore $q_{\alpha}\in(m,M)$ tale che $$\begin{bmatrix}F_{X}(q_{\alpha})=\alpha\end{bmatrix}$$
> [!info] Terminologia
> Il valore $q_{1/2}$ (cioè $q_{\alpha}$ per $\alpha=\frac{1}{2}$) è detto **mediana**.

## Esempio (uniforme)
$X\sim U(a,b)$. In questo caso $(m,M)=(a,b)$. Da $F_{X}(q_{\alpha})=\alpha$: $$\frac{q_{\alpha}-a}{b-a}=\alpha\implies q_{\alpha}-a=\alpha(b-a)\implies\begin{bmatrix}q_{\alpha}=a+\alpha(b-a)\end{bmatrix}$$Inoltre la mediana è $$q_{1/2}=a+\frac{1}{2}(b-a)=a-\frac{a}{2}+\frac{b}{2}=\frac{a}{2}+\frac{b}{2}=\frac{a+b}{2}$$cioè il **punto medio dell'intervallo**.
## Esempio (esponenziale)
$X\sim Exp(\lambda)$. In questo caso $(m,M)=(0,\infty)$. Da $F_{X}(q_{\alpha})=\alpha$: $$1-e^{-\lambda q_{\alpha}}=\alpha\implies e^{-\lambda q_{\alpha}}=1-\alpha\implies -\lambda q_{\alpha}=\log(1-\alpha)\implies\begin{bmatrix}q_{\alpha}=-\frac{1}{\lambda}\log(1-\alpha)\end{bmatrix}$$Inoltre la mediana è $$q_{1/2}=-\frac{1}{\lambda}\log\left( 1-\frac{1}{2} \right)=-\frac{1}{\lambda}\log\left( \frac{1}{2} \right)=\frac{1}{\lambda}\log 2$$(qui $\log$ è il logaritmo naturale).

--- Fine parte sui quantili (lezione 16, pp. 1-3) ---

---
Nota precedente: [[Esercizi su densità continue]]. Nota successiva: [[Trasformazioni di variabili aleatorie continue]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
