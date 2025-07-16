#### Esercizio Ricorsioni Lineari

^2bda40

Risolvere la ricorrenza lineare a coefficiente costanti$$\begin{array}{}
	f(n+3)=-f(n+2)+8f(n+1)+12f(n)\\
	....\\....\\
	x^3+x^2-8x-12=(x^2-3)(x+2)^2
\end{array}$$
Pertanto le radici dell'equazione caratteristica sono $\gamma_1=3\quad\gamma_2=-2$ con molteplicità $d_1=1\quad e\quad d_2=2$
in effetti $x^3+x^2-8x-12=(x-3)^1(x-(-2))^2$)
sappiamo dalla teoria che $\exists$ 2 polinomi $P_1(X),P_2(x)\in\textsf{C\kern-0.8ex C}[x]$ t.c. $$Deg(P_1)\leq1-1,\quad Deg(P_2)\leq2-1\quad e\quad f(n)=P_1(n)(\gamma_1)^n+P_2(n)(\gamma_2)^n\quad\quad\forall n\in\textsf{I\kern-0.1ex N}$$ nel nostro caso $\implies\exists\ a,b,c\in\textsf{C\kern-0.8ex C}$ t.c. $$f(n)=a(3)^n+(b+cn)(-2)^n\quad\quad\forall\ n\in \textsf{I\kern-0.1ex N}$$
per trovare $a,b,c\in\textsf{C\kern-0.8ex C}$ usiamo le C.I. abbiamo $$\begin{array}{}
	f(0)=0\quad\quad0=a+b\\
	f(1)=5\quad\quad5=a\cdot3+(b+c)(-2)\\
	f(2)=0\quad\quad0=a(3)^2+(b+2c)(-2)^2\\
	\begin{cases}
		0=a+b\\
		5=a\cdot3+(b+c)(-2)\\
		0=a(3)^2+(b+2c)(-2)^2
	\end{cases}\implies\begin{cases}
		a+b=0\\
		3a-2b-2c=5\\
		9a+4b+8c=0
	\end{cases}
	\\\implies a=-b\implies\\
	\begin{cases}
		-3b-2b-2c=5\\
		-9b+4b+8c=0
	\end{cases}\implies\begin{cases}
		-5b-2c=5\\
		-5b+8c=0
	\end{cases}\implies\\c-
	b=\frac{8c}{5}\implies-10c=5\implies c=-\frac{1}{2}\implies b=-\frac{4}{5}\implies a=-b=\frac{4}{5}
\end{array}$$
concludendo $$\begin{array}{}
f(n)=\frac{4}{5}(3)^n+(-\frac{4}{5}+(-\frac{1}{2})n)(-2)^n\quad\quad\forall\ n\in\textsf{I\kern-0.1ex N}\\
f(0)=\frac{4}{5}+(-\frac{4}{5}+0)(1)
\end{array}$$ ^bd1fc1
#### Esercizio Confronto Asintotico
Siano $f,g:N\to R_{>0}$ definite ponendo:
$$\begin{array}{} 
    f(n)\stackrel{def}=\log_{2}(n)  & \\
     &\forall x\in\textsf{I\kern-0.1ex P} \\
    g(n) \stackrel{def}= \log_{10}(n)&
\end{array}$$
$$\text{quale delle relazioni} \quad o, O, \ohm, \cong \quad\text{valgono tra}\quad f\quad\ e\ \quad g?$$
Abbiamo che:
$$\begin{array}{}
f(n)\frac{ln(n)}{\ln 2}\quad & g(n)\frac{ln(n)}{\ln 10}\quad & \forall n\in\textsf{I\kern-0.1ex P}
\end{array}$$
Quindi:
$$\lim_{n\to +\infty}\frac{f(n)}{g(n)}=\lim_{n\to +\infty}\frac{\ln(10)}{\ln(2)}=\frac{\ln(10)}{\ln(2)} (*)\implies f\not\cong g \quad \text{e} \quad f\not = g$$
$*\not=1$ quindi NON sono asintoticamente equivalenti
$\not=0\implies$ non è $\circ$ di $g$
similmente
$$\frac {f(n)}{g(n)}=\frac{\ln(2)}{\ln(10)}\implies g \not = \circ(f) $$
inoltre $(*)$ implica che $\exists\ N \in\textsf{I\kern-0.1ex P}$ tale che $$\frac{\ln(10)}{\ln(2)}-\frac{1}{2}\leq \frac{f(n)}{g(n)}\leq \frac{\ln(1)}{\ln(2)}+ \frac{1}{2}\quad\quad se\quad n>N$$
Pertanto
$$|f(n)|\leq \left(\frac{\ln(10)}{\ln(2)}+ \frac{1}{2}\right)g(n)\quad\quad se\quad n>N \implies f=O(g)$$

 Similmente
$$g=O(f) \implies g=\Omega(f) \quad\text{e}\quad f=\Omega(g)\quad\text{e}\quad f=\theta(g)$$
#### Esercizio Studio Asintotico
Sia $f:\textsf{I\kern-0.1ex N}\to \textsf{I\kern-0.1ex R}_{>0}$ definita da $$f(n)\stackrel{def}=n+\ln(n)+\ln(n)^2$$
quale delle seguenti affermazioni è vera?
$f=\theta(2^{n\ln(n)}),f=\theta(n),f=\theta(n^2),f=\theta(2^n),f=\theta(n^2\log_{10}(n))$?
- $f=\theta(2^n\ln(n))$?
  $$\begin{array}{}
    f(n)=n+\ln(n)+\ln(n)^2 \\
    \text{se }\quad f=\theta(2^{n\ln(n)})\implies 2^{n\ln(n)}=\bigcirc(f)\implies \exists\ c>0\quad e\quad \exists\ N\in\textsf{I\kern-0.1ex P} \\
    \text{t.c. }\quad \underset{||}{2^{n\ln(n)}}\leq c(n+\ln(n)+\ln(n)^2) \\
    \left(\begin{array}{}
    2^{\ln(n^n)}=e^{\ln(2^{\ln(n^n)})} \\
    =e^{\ln(n^n)\ln(2)} \\
    =(e^{\ln(n^n)})^{\ln(2)} \\
    =(n^n)^{\ln(2)}\end{array} \right)\quad\quad\quad\quad\quad\quad\quad\quad \\
    (n^n)^{\ln(2)}\leq c(n+\ln(n)+\ln(n)^2) \\
    \text{se }n>N\text{ cioè} \\
    \frac{(n^n)^{\ln(2)}}{n+\ln(n)+\ln(n)^2}\leq c\quad \text{ se } n>N \\
    \frac{\frac{1}{n}(n^n)^{\ln(2)}}{1+\frac{\ln(n)}{n}+\frac{\ln(n)^2}{n}}\leq c \\
    \text{se }n>N \text{ ma la parte sinistra tende a infinito se n tende a infinito }\implies \text{assurdo. Quindi} \\
    2^{n\ln(n)}\not=\bigcirc(f)\implies 2^{n\ln(n)}\not=\theta(f) 
\end{array}$$
- $f=\theta(n)?$
  $$\begin{array}{l}
    \text{cioè }\quad n+\ln(n)+\ln(n)^2=\theta(n) \\
    \text{ma }\quad \frac{n+\ln(n)+\ln(n)^2}{n}\to 1\quad \text{ se }\quad n\to+\infty \implies \\
    f\cong n\implies f=\bigcirc(n)\quad e\quad n=\bigcirc(f)\implies f=\theta(n) 
\end{array}$$
- $f=\theta(n^2)$?
   $$\begin{array}{l}
    \text{cioè }\quad n+\ln(n)+\ln(n)^2=\theta(n^2) \\
    \text{ma }\quad\displaystyle\lim_{ n \to \infty }\frac{n^2}{n+\ln(n)+\ln(n)^2}=+\infty \\
    \text{pertanto } n^2\not=\bigcirc(f)\quad(\text{se lo fosse }\implies\exists\ c>0\quad e\quad\exists\ N>0\quad\text{t.c.}\\
    n^2\leq c(n+\ln(n)+\ln(n)^2)\quad\quad\forall\ n>N\text{, assurdo)} 
\end{array}$$
- $f=\theta(2^n)$?
  $$\begin{array}{l}
    \text{cioè }\quad n+\ln(n)+\ln(n)^2=\theta(2^n) \\
    \text{poiché }\quad\displaystyle\lim_{n\to\infty}\frac{n^2\log_{10}(n)}{n+\ln(n)+\ln(n)^2}=+\infty \\
    \text{concludiamo come prima che }\quad f\not=\theta(2^n) 
\end{array}$$
- $f=\theta(n^2\log(n))$?
   $$\begin{array}{l}
    \text{cioè }\quad n+\ln(n)+\ln(n)^2=\theta(n^2\log_{10}(n)) \\
    \text{poiché }\quad\displaystyle\lim_{n\to\infty}\frac{n^2\log_{10}(n)}{n+\ln(n)+\ln(n)^2} =+\infty \\
    \implies f\not=\theta(n^2\log_{10}(n))
\end{array}$$
Concludendo $f=\theta(n)$
