# Trasformazioni monotone di variabili aleatorie continue
Procedimento caso per caso per la densità di $Y=f(X)$ quando $f$ è monotona ma non affine: si studia il codominio, si scrive $F_{Y}$ e si deriva.
## Il procedimento
Quando $f$ non è [[Trasformazioni di variabili aleatorie continue#Il caso di funzione affine non costante|affine]] non c'è una formula generale. Se $f$ è **monotona** (su un sottoinsieme $S$ del dominio con $P(X\in S)=1$) si procede così:
1. **Codominio di $Y$**: usando la monotonia di $f$, si determina l'intervallo dei valori assunti da $Y=f(X)$. Se $f$ è crescente su $(m,M)$ con $P(X\in(m,M))=1$, allora $Y$ assume valori in $(f(m),f(M))$ (per $f$ decrescente in $(f(M),f(m))$).
2. **Funzione di distribuzione**: si scrive $F_{Y}(y)=P(f(X)\leq y)$, si "inverte" $f$ per ricondursi a una probabilità su $X$ e la si esprime tramite $F_{X}$ o un integrale di $f_{X}$.
3. **Derivazione**: si deriva $F_{Y}$ nei punti dove è derivabile per ottenere $f_{Y}$.

> [!info] Monotonia delle composizioni
> Ogni volta che si compone una funzione **crescente** la monotonia non cambia; ogni volta che si compone una funzione **decrescente** la monotonia si inverte. Contando il numero di inversioni si stabilisce se $f$ è crescente o decrescente.

## Esercizio ($Y=\sqrt{X}$, $X\sim U(4,9)$)
Sia $X\sim U(4,9)$ e sia $Y=\sqrt{X}$. Trovare la densità continua di $Y$.
Su $(4,9)$ la funzione $\sqrt{\cdot}$ è crescente, quindi $Y$ assume valori in $(\sqrt{4},\sqrt{9})=(2,3)$ e $P(Y\in(2,3))=1$. Allora $$F_{Y}(y)=\begin{cases}0 & y\leq 2 \\ (\ast) & 2<y<3 \\ 1 & y\geq 3\end{cases}$$dove, per $y\in(2,3)$ (quindi $y^{2}\in(4,9)$), $$(\ast)=P(Y\leq y)=P(\sqrt{X}\leq y)=P(X\leq y^{2})=\int_{4}^{y^{2}}\frac{1}{9-4}\,dx=\frac{1}{5}[x]_{x=4}^{x=y^{2}}=\frac{y^{2}-4}{5}$$La $F_{Y}$ è continua. Derivando ($F_{Y}$ non è derivabile in $y=2$ e $y=3$) si ha $$f_{Y}(y)=\begin{cases}0 & y<2 \\ \dfrac{2y}{5} & 2<y<3 \\ 0 & y>3\end{cases}=\frac{2y}{5}1_{(2,3)}(y)$$($f_{Y}$ è discontinua). In effetti si verifica che $\int_{2}^{3}\frac{2y}{5}\,dy=\frac{1}{5}[y^{2}]_{2}^{3}=\frac{9-4}{5}=1$.
## Esercizio ($X\sim U(0,1)$: due trasformazioni)
Sia $X\sim U(0,1)$, con $\alpha,\lambda>0$. Trovare la densità continua di $Y=-\frac{1}{\lambda}\log(1-X^{\alpha})$ e di $Z=e^{-\alpha X}$.
### 1) $Y=-\frac{1}{\lambda}\log(1-X^{\alpha})$
Vediamo $f$ come composizione: $x\mapsto y_{1}=x^{\alpha}$ (crescente, $\alpha>0$); $y_{1}\mapsto y_{2}=1-y_{1}$ (decrescente); $y_{2}\mapsto y_{3}=\log y_{2}$ (crescente); $y_{3}\mapsto y_{4}=-\frac{1}{\lambda}y_{3}$ (decrescente, $\lambda>0$). Ci sono **due inversioni** (due funzioni decrescenti), quindi $f$ è crescente e $Y$ assume valori in $$(f(0),f(1))=\left( -\tfrac{1}{\lambda}\log(1-0),\ -\tfrac{1}{\lambda}\log(1-1) \right)=(0,+\infty)$$Allora $F_{Y}(y)=0$ per $y\leq 0$, e per $y>0$ $$F_{Y}(y)=P\left( -\tfrac{1}{\lambda}\log(1-X^{\alpha})\leq y \right)=P\left( \log(1-X^{\alpha})\geq -\lambda y \right)=P\left( 1-X^{\alpha}\geq e^{-\lambda y} \right)=P\left( X\leq(1-e^{-\lambda y})^{1/\alpha} \right)=\int_{0}^{(1-e^{-\lambda y})^{1/\alpha}}1\,dx=(1-e^{-\lambda y})^{1/\alpha}$$(l'argomento $(1-e^{-\lambda y})^{1/\alpha}\in(0,1)$). Derivando ($F_{Y}$ non derivabile in $y=0$): $$f_{Y}(y)=\frac{1}{\alpha}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}(-e^{-\lambda y})(-\lambda)1_{(0,\infty)}(y)=\begin{bmatrix}\frac{\lambda}{\alpha}e^{-\lambda y}(1-e^{-\lambda y})^{\frac{1}{\alpha}-1}1_{(0,\infty)}(y)\end{bmatrix}$$
> [!info] Caso particolare
> Per $\alpha=1$ si ha $f_{Y}(y)=\lambda e^{-\lambda y}1_{(0,\infty)}(y)$, cioè $Y\sim Exp(\lambda)$.

### 2) $Z=e^{-\alpha X}$
$g(x)=e^{-\alpha x}$ è decrescente (perché $\alpha>0$), quindi $Z$ assume valori in $(g(1),g(0))=(e^{-\alpha},1)$. Allora $$F_{Z}(z)=\begin{cases}0 & z\leq e^{-\alpha} \\ (\ast) & z\in(e^{-\alpha},1) \\ 1 & z\geq 1\end{cases}$$dove, per $z\in(e^{-\alpha},1)$ (quindi $-\frac{1}{\alpha}\log z\in(0,1)$), $$(\ast)=P(e^{-\alpha X}\leq z)=P(-\alpha X\leq \log z)=P\left( X\geq -\tfrac{1}{\alpha}\log z \right)=\int_{-\frac{1}{\alpha}\log z}^{1}1\,dx=[x]_{x=-\frac{1}{\alpha}\log z}^{x=1}=1+\tfrac{1}{\alpha}\log z$$Derivando ($F_{Z}$ non derivabile in $z=e^{-\alpha}$ e $z=1$): $$f_{Z}(z)=\begin{cases}0 & z<e^{-\alpha} \\ \dfrac{1}{\alpha z} & z\in(e^{-\alpha},1) \\ 0 & z>1\end{cases}=\frac{1}{\alpha z}1_{(e^{-\alpha},1)}(z)$$Verifica: $\int_{e^{-\alpha}}^{1}\frac{1}{\alpha z}\,dz=\frac{1}{\alpha}[\log z]_{e^{-\alpha}}^{1}=\frac{1}{\alpha}(0-(-\alpha))=1$.
## Esercizio ($X$ con densità $\alpha x^{\alpha-1}$ su $(0,1)$: potenza e potenza inversa)
Sia $X$ con densità continua $f_{X}(x)=\alpha x^{\alpha-1}1_{(0,1)}(x)$, con $\alpha>0$ (è una densità: $\int_{0}^{1}\alpha x^{\alpha-1}\,dx=[x^{\alpha}]_{0}^{1}=1$). Con $\beta>0$, trovare la densità di $Y=X^{\beta}$ e di $Z=X^{-\beta}$.
### 1) $Y=X^{\beta}$
$f(x)=x^{\beta}$ è crescente su $(0,1)$, quindi $Y$ assume valori in $(f(0),f(1))=(0,1)$. Allora $F_{Y}(y)=0$ per $y<0$, $=1$ per $y>1$, e per $y\in(0,1)$ (quindi $y^{1/\beta}\in(0,1)$) $$F_{Y}(y)=P(X^{\beta}\leq y)=P(X\leq y^{1/\beta})=\int_{0}^{y^{1/\beta}}\alpha x^{\alpha-1}\,dx=\left[ x^{\alpha} \right]_{0}^{y^{1/\beta}}=(y^{1/\beta})^{\alpha}=y^{\alpha/\beta}$$Derivando ($F_{Y}$ non derivabile in $y=0$ e $y=1$): $$f_{Y}(y)=\begin{bmatrix}\frac{\alpha}{\beta}y^{\frac{\alpha}{\beta}-1}1_{(0,1)}(y)\end{bmatrix}$$
> [!info] Caso particolare
> Se $\frac{\alpha}{\beta}=1$ (cioè $\alpha=\beta$) si ha $Y\sim U(0,1)$.

### 2) $Z=X^{-\beta}$
$g(x)=x^{-\beta}$ è decrescente su $(0,1)$, quindi $Z$ assume valori in $(g(1),g(0))=(1^{-\beta},0^{-\beta})=(1,\infty)$. Allora $F_{Z}(z)=0$ per $z\leq 1$, e per $z>1$ (quindi $z^{-1/\beta}\in(0,1)$) $$F_{Z}(z)=P(X^{-\beta}\leq z)=P\left( X^{\beta}\geq \tfrac{1}{z} \right)=P(X\geq z^{-1/\beta})=\int_{z^{-1/\beta}}^{1}\alpha x^{\alpha-1}\,dx=[x^{\alpha}]_{z^{-1/\beta}}^{1}=1-(z^{-1/\beta})^{\alpha}=1-z^{-\alpha/\beta}$$Derivando ($F_{Z}$ non derivabile in $z=1$): $$f_{Z}(z)=\frac{\alpha}{\beta}z^{-\frac{\alpha}{\beta}-1}1_{(1,\infty)}(z)=\begin{bmatrix}\frac{\alpha}{\beta}z^{-\left( 1+\frac{\alpha}{\beta} \right)}1_{(1,\infty)}(z)\end{bmatrix}$$Verifica: $\int_{1}^{\infty}\frac{\alpha}{\beta}z^{-(1+\frac{\alpha}{\beta})}\,dz=\frac{\alpha}{\beta}\left[ \frac{z^{-\frac{\alpha}{\beta}}}{-\frac{\alpha}{\beta}} \right]_{1}^{\infty}=[-z^{-\frac{\alpha}{\beta}}]_{1}^{\infty}=-0+1=1$.

--- Fine lezione 16 ---

---
Nota precedente: [[Trasformazioni di variabili aleatorie continue]]. Nota successiva: da trascrivere (lezione 17). Indice del blocco: [[Cap 4 - Modelli Continui]].
