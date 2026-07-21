# Distribuzione uniforme continua
Prima distribuzione notevole continua: densità costante su un intervallo limitato, con il calcolo di probabilità tramite il metodo delle lunghezze.
## Definizione
Una v.a. $X$ ha **distribuzione uniforme continua** su un intervallo limitato $(a,b)$ se $$F_{X}(t)=\begin{cases}
0 & t<a \\
\dfrac{t-a}{b-a} & a\leq t\leq b \\
1 & t>b
\end{cases}$$In simboli scriveremo $X\sim U(a,b)$.
## Densità
La funzione $F_{X}$ non è derivabile per $t=a$ e $t=b$. Negli altri punti lo è e si ha $$F_{X}'(t)=\begin{cases}
\dfrac{1}{b-a} & a<t<b \\
0 & \text{altrimenti (per }t<a\text{ e }t>b)
\end{cases}$$Quindi possiamo dire ad esempio che $$f_{X}(t)=\begin{cases}
\dfrac{1}{b-a} & a<t<b \\
0 & \text{altrimenti}
\end{cases}=\begin{bmatrix}\dfrac{1}{b-a}1_{(a,b)}(t)\end{bmatrix}$$dove $1_{A}(x)=\begin{cases}1 & x\in A \\ 0 & x\notin A\end{cases}$ (per $A\subseteq \mathbb{R}$).
> [!info] Estremi irrilevanti
> Per la [[Variabili aleatorie continue#Non unicità della densità (esempio)|non unicità della densità]], al posto di $(a,b)$ si poteva mettere $[a,b]$, $[a,b)$ oppure $(a,b]$: i valori negli estremi non cambiano $F_{X}$.

### Verifica della normalizzazione
Verifichiamo che $\int_{-\infty}^{\infty}f_{X}(x)\,dx=1$ (quindi $\frac{1}{b-a}$ può essere vista come una costante di normalizzazione): $$\int_{-\infty}^{\infty}f_{X}(x)\,dx=\underset{=0}{\underbrace{\int_{-\infty}^{a}f_{X}(x)\,dx}}+\int_{a}^{b}f_{X}(x)\,dx+\underset{=0}{\underbrace{\int_{b}^{\infty}f_{X}(x)\,dx}}=\int_{a}^{b}\frac{1}{b-a}\,dx=\left[ \frac{x}{b-a} \right]_{x=a}^{x=b}=\frac{b-a}{b-a}=1$$In accordo con il fatto che l'area del rettangolo di base $(a,b)$ e altezza $\frac{1}{b-a}$ è uguale a 1.
## Esercizio ($U(0,5)$)
Sia $X\sim U(0,5)$. Calcolare $P(4\leq X\leq 6)$ e $P(2\leq X\leq 4\mid 1\leq X\leq 3)$.
**Prima probabilità (due modi).** $$P(4\leq X\leq 6)=\int_{4}^{6}f_{X}(x)\,dx=\int_{4}^{6}\frac{1}{5-0}1_{(0,5)}(x)\,dx=\int_{4}^{5}\frac{1}{5}\,dx=\frac{1}{5}[x]_{x=4}^{x=5}=\frac{5-4}{5}=\frac{1}{5}$$oppure, con la funzione di distribuzione, $$P(4\leq X\leq 6)=F_{X}(6)-F_{X}(4)=1-\frac{4-0}{5-0}=1-\frac{4}{5}=\frac{1}{5}$$
**Probabilità condizionata.** $$P(2\leq X\leq 4\mid 1\leq X\leq 3)=\frac{P(\{2\leq X\leq 4\}\cap\{1\leq X\leq 3\})}{P(\{1\leq X\leq 3\})}=\frac{P(2\leq X\leq 3)}{P(1\leq X\leq 3)}=\frac{\int_{2}^{3}\frac{1}{5}\,dx}{\int_{1}^{3}\frac{1}{5}\,dx}=\frac{[x]_{2}^{3}}{[x]_{1}^{3}}=\frac{3-2}{3-1}=\frac{1}{2}$$
## Metodo delle lunghezze
I risultati precedenti possono essere ottenuti senza fare troppi calcoli, con un procedimento adattabile a tutti i casi con distribuzione uniforme: per $X\sim U(a,b)$ la probabilità di un intervallo è il rapporto tra la sua lunghezza (intersecata con $(a,b)$) e la lunghezza di $(a,b)$. Infatti, per $X\sim U(0,5)$, $$P(4\leq X\leq 6)=\frac{\text{lunghezza}((4,6)\cap(0,5))}{\text{lunghezza}(0,5)}=\frac{\text{lunghezza}(4,5)}{5}=\frac{1}{5}$$ $$P(2\leq X\leq 4\mid 1\leq X\leq 3)=\frac{\text{lunghezza}((2,4)\cap(1,3)\cap(0,5))}{\text{lunghezza}((1,3)\cap(0,5))}=\frac{\text{lunghezza}(2,3)}{\text{lunghezza}(1,3)}=\frac{3-2}{3-1}=\frac{1}{2}$$(le divisioni per $\text{lunghezza}(0,5)$ a numeratore e denominatore si semplificano).
### Un altro esempio ($U(3,10)$)
Sia $X\sim U(3,10)$. Calcolare $P(6\leq X\leq 11)$ e $P(6\leq X\leq 11\mid 5\leq X\leq 9)$. Con il metodo delle lunghezze: $$P(6\leq X\leq 11)=\frac{\text{lunghezza}((6,11)\cap(3,10))}{\text{lunghezza}(3,10)}=\frac{\text{lunghezza}(6,10)}{10-3}=\frac{10-6}{7}=\frac{4}{7}$$ $$P(6\leq X\leq 11\mid 5\leq X\leq 9)=\frac{\text{lunghezza}((6,11)\cap(5,9)\cap(3,10))}{\text{lunghezza}((5,9)\cap(3,10))}=\frac{\text{lunghezza}(6,9)}{\text{lunghezza}(5,9)}=\frac{9-6}{9-5}=\frac{3}{4}$$

--- Fine parte sulla distribuzione uniforme continua (lezione 15, pp. 9-12) ---

---
Nota precedente: [[Variabili aleatorie continue]]. Nota successiva: [[Distribuzione esponenziale]]. Indice del blocco: [[Cap 4 - Modelli Continui]].
