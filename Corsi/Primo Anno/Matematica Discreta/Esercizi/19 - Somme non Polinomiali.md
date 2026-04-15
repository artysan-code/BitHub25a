## Es. 
Trovare una formula chiusa o asintoticamente chiusa per $$\sum_{k=1}^{n}(2k\ln(k))$$La funzione $f(x)=2x\ln(x)$ non è un polinomio ma è continua per $x>0$ e Monotona Crescente per $x>0$. 

Sappiamo dalla teoria che $$\int^{n}_{1}2x\ln(x)\,dx\leq \sum_{k=0}^n2k\ln(k)\leq 2n\ln(n)+\int^{n}_{1}2x\ln(x)\,dx \quad\quad\forall\ n\in\mathbb{P}$$ma $$\int^{n}_{1}2x\ln(x)\,dx=\left[ x^2\ln(x)-\frac{x^2}{2} \right]_{1}^n=\left(n^2\ln(n)-\frac{n^2}{2}\right)\left(\frac{1}{2}\right)$$
Pertanto $$n^2\ln(n)-\frac{n^2}{2}+\frac{1}{2}\leq \sum_{k=0}^n2k\ln (k)\leq 2n\ln(n)+n^2\ln(n)-\frac{n^2}{2}+\frac{1}{2}\quad\quad\forall\ n\in\mathbb{P}$$
Il termine che va più velocemente a $n\to+\infty$ a sinistra è $n^2\ln(n)$ e a destra pure. Quindi $$1-\frac{1}{2\ln(n)}+\frac{1}{2n^2\ln(n)}\leq\frac{\displaystyle\sum^n_{k=0}2k\ln(k)}{n^2\ln(n)}\leq \frac{2}{n}+1-\frac{1}{2\ln(n)}+\frac{1}{2n^2\ln(n)}$$
Pertanto per il teorema del confronto $$\lim_{n\to\infty}{\frac{\displaystyle\sum_{k=0}^n2k\ln(k)}{n^2\ln(n)}}=1$$
pertanto $$\sum_{k=0}^n2k\ln(k)\approx n^2\ln(n)\quad\quad\text{per }n\to+\infty$$