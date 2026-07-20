# Massimi e minimi di variabili aleatorie discrete
Come calcolare la densità discreta di $\max\{X_{1},X_{2}\}$ e $\min\{X_{1},X_{2}\}$ passando per le funzioni di distribuzione.
## Impostazione
Per semplicità consideriamo il caso di $\underline{X}=(X_{1},X_{2})$ e consideriamo le seguenti v.a.: $$\begin{array}{l}
Y=\max\{X_{1},X_{2}\} \\
W=\min\{X_{1},X_{2}\}
\end{array}$$Inoltre supponiamo che le v.a. $X_{1}$ e $X_{2}$ assumano **valori interi**; allora lo stesso si può dire per le v.a. $Y$ e $W$.
Per quel che segue è utile fare riferimento alle seguenti formule: $$\begin{array}{ll}
(*) & P_{Y}(y)=P(Y=y)=P(Y\leq y)-P(Y\leq y-1) \\
(**) & P_{W}(w)=P(W=w)=P(W\geq w)-P(W\geq w+1)
\end{array}$$(valgono perché i valori assunti sono interi: fra $y-1$ e $y$ non ci sono altri valori possibili).
## Le formule per il massimo e per il minimo
Per spiegare questo osserviamo che $$\{Y\leq y\}=\{\max\{X_{1},X_{2}\}\leq y\}=\{X_{1}\leq y\}\cap\{X_{2}\leq y\}$$(il massimo è $\leq y$ **se e solo se** entrambe lo sono), da cui $$\begin{array}{ll}
P_{Y}(y)\overset{(*)}{=}P(Y\leq y)-P(Y\leq y-1) & =P(\{X_{1}\leq y\}\cap\{X_{2}\leq y\})-P(\{X_{1}\leq y-1\}\cap\{X_{2}\leq y-1\}) \\
 & \underset{\text{se }X_{1},X_{2}\text{ indip.}}{=}P(X_{1}\leq y)P(X_{2}\leq y)-P(X_{1}\leq y-1)P(X_{2}\leq y-1)
\end{array}$$Analogamente $$\{W\geq w\}=\{\min\{X_{1},X_{2}\}\geq w\}=\{X_{1}\geq w\}\cap\{X_{2}\geq w\}$$(il minimo è $\geq w$ **se e solo se** entrambe lo sono), da cui $$\begin{array}{ll}
P_{W}(w)\overset{(**)}{=}P(W\geq w)-P(W\geq w+1) & =P(\{X_{1}\geq w\}\cap\{X_{2}\geq w\})-P(\{X_{1}\geq w+1\}\cap\{X_{2}\geq w+1\}) \\
 & \underset{\text{se }X_{1},X_{2}\text{ indip.}}{=}P(X_{1}\geq w)P(X_{2}\geq w)-P(X_{1}\geq w+1)P(X_{2}\geq w+1)
\end{array}$$
> [!info] L'idea
> Per il **massimo** conviene passare dalla funzione di distribuzione $P(\cdot\leq\cdot)$, per il **minimo** dalla "coda" $P(\cdot\geq\cdot)$: in entrambi i casi l'evento si spezza in un'**intersezione**, che sotto indipendenza si fattorizza.

## Esempio di applicazione delle formule
Si lanciano due dadi equi. Siano $X_{1}$ e $X_{2}$ le v.a. che indicano i numeri che escono, e sappiamo che sono **indipendenti**. Allora $$\begin{array}{l}
Y=\max\{X_{1},X_{2}\}\text{ assume valori in }\delta_{Y}=\{1,2,3,4,5,6\} \\
W=\min\{X_{1},X_{2}\}\text{ assume valori in }\delta_{W}=\{1,2,3,4,5,6\}
\end{array}$$
**Massimo.** Per $y\in\{1,\dots,6\}$ si ha $P(X_{i}\leq y)=\frac{y}{6}$, quindi $$P_{Y}(y)=P(X_{1}\leq y)P(X_{2}\leq y)-P(X_{1}\leq y-1)P(X_{2}\leq y-1)=\frac{y}{6}\cdot \frac{y}{6}-\frac{y-1}{6}\cdot \frac{y-1}{6}=\frac{y^{2}-(y-1)^{2}}{36}=\frac{y^{2}-(y^{2}-2y+1)}{36}=\frac{2y-1}{36}$$cioè $$P_{Y}(y)=\begin{cases}
1/36 & \text{per }y=1 \\
3/36 & \text{per }y=2 \\
5/36 & \text{per }y=3 \\
7/36 & \text{per }y=4 \\
9/36 & \text{per }y=5 \\
11/36 & \text{per }y=6
\end{cases}$$(la somma fa 1, come deve essere).
**Minimo.** Per $w\in\{1,\dots,6\}$ si ha $P(X_{i}\geq w)=\frac{6-w+1}{6}=\frac{7-w}{6}$, quindi $$P_{W}(w)=\frac{6-w+1}{6}\cdot \frac{6-w+1}{6}-\frac{6-(w+1)+1}{6}\cdot \frac{6-(w+1)+1}{6}=\frac{(7-w)^{2}}{36}-\frac{(6-w)^{2}}{36}=\frac{49-14w+w^{2}-(36-12w+w^{2})}{36}=\frac{13-2w}{36}$$cioè $$P_{W}(w)=\begin{cases}
11/36 & \text{per }w=1 \\
9/36 & \text{per }w=2 \\
7/36 & \text{per }w=3 \\
5/36 & \text{per }w=4 \\
3/36 & \text{per }w=5 \\
1/36 & \text{per }w=6
\end{cases}$$(la somma fa 1, come deve essere).
> [!info] Lettura geometrica
> Sul piano cartesiano dei 36 esiti, $\{Y=y\}$ è la "squadra" (riga + colonna) di vertice $(y,y)$, e $\{W=w\}$ è la squadra di vertice $(w,w)$ aperta verso l'alto a destra: da qui i conteggi $2y-1$ e $13-2w$.

--- Fine parte su massimi e minimi (lezione 12, pp. 5-8) ---

---
Nota precedente: [[Trasformazioni e somme di variabili aleatorie discrete]]. Nota successiva: [[Speranza matematica di una variabile aleatoria discreta]] (inizia un blocco nuovo). Indice del blocco: [[Cap 3 - Modelli Discreti]].
