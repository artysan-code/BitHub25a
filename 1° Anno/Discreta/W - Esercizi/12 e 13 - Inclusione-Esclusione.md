## Es. (RSA)
Sia $n\in\mathbb{P}$ il parametro pubblico di un RSA. Dimostrare che, se $\Phi(n)$ è noto, allora posso posso rompere l'RSA.

Abbiamo che 
$$\begin{array}{l}
n=p\cdot q\quad\quad\quad\Phi(n)=(p-1)(q-1) \\
\implies p=\frac{n}{q}\implies\Phi(n)=\left( \frac{n}{q}-1\right)(q-1) \\
\implies q\cdot\Phi(n)=(n-q)(q-1) \\
\implies q\cdot\Phi(n)=nq-q^2-n+q \\
\implies q^2+q(\Phi(n)-n-1)+n=0 \\
\implies q=\frac{n+1-\Phi(n)\pm\sqrt{(\Phi(n)-n-1)^2-4n}}{2} \\
\implies p=\frac{n}{q}
\end{array}$$

## Es. (binomiale)
Quanti sottoinsiemi di $[7]$ ci sono di cardinalità 4?

Sappiamo dalla teoria che il numero è $\binom{7}{4}=\frac{7\cdot6\cdot5\cdot4}{4!}=7\cdot5=35$
Possiamo calcolarlo anche con la F.G.:
$$\begin{array}{l}
(1+x)^7=(1+x)^3(1+x)^3(1+x) \\
=(1+3x+3x^2+x^3)(1+3x+3x^2+x^3)(1+x) \\
=(1+3x+3x^2+x^3+3x+9x^2+9x^3+3x^4+3x^2+9x^3+9x^4+3x^5+x^3+3x^4+3x^5+x^6)(x+1) \\
=(1+6x+15x^2+20x^3+15x^4+6x^5+x^6)(1+x) \\
=1+6x+15x^2+20x^3+15x^4+6x^5+x^6+x+6x^2+15x^3+20x^4+15x^5+6x^6+x^7 \\
=\underset{\binom{7}{4}}{\underset{\uparrow}{\underbrace{1+7x+21x^2+35x^3+35x^4+21x^5+7x^6+x^7}}}
\end{array}$$

## Es. (inclusione-esclusione)
Calcolare $|\{A\subseteq[9]:2\notin A \text{ o } 8 \notin A\}|$

Abbiamo che $\{A\subseteq[9]:2\notin A \text{ o } 8 \notin A\}=X\cup Y$
dove 
$X=\{A\subseteq[9]:2\not\in A\}$
e
$Y=\{A\subseteq[9]:8\not\in A\}$

Dobbiamo calcolare $|X\cup Y|\implies$ uso I.E. e abbiamo
$|X\cup Y|=|X|+|Y|-|X\cap Y|$
ma
$|X|=|\{A\subseteq[9]:2\not\in A\}|=|\{1,3,4,5,6,7,8,9\}|=2^8$
e 
$|Y|=|\{A\subseteq[9]:8\not\in A\}|=|\{1,2,3,4,5,6,7,9\}|=2^8$
infine
$|X\cap Y|=|\{A\subseteq[9]:2\not\in A\text{ e } 8\not\in A\}|=|\{1,3,4,5,6,7,9\}|=2^7$
quindi 
$|\{A\subseteq[9]:2\not\in A\text{ e } 8\not\in A\}=|X\cup Y|=2^8+2^8-2^7=2^7(2+2-1)=3\cdot2^7$

## Es. (inclusione-esclusione)
Calcolare $|\{f\in S_{9}:f(2)\not=2\text{ e }f(4)\not= 4\}|$

Ragionamento Euristico: "e"$\implies$ intersezione. 
Facile? non direi. 
Principio di I.E.? impossibile.
Quindi?    De Morgan

Abbiamo che 
$\{f\in S_{9}:f(2)\not=2\text{ e }f(4)\not=4\}=S_{9}\backslash\{f\in S_{9}:f(2)\not=2\text{ o }f(4)\not=4\}$
Calcoliamo quindi
$|\{f\in S_{9}:f(2)\not=2\text{ o }f(4)\not=4\}|$

Dobbiamo calcolare $|X\cup Y|$ dove
$X=\{f\in S_{9}:f(2)=2\}$
e
$Y=\{f\in S_{9}:f(4)=4\}$
Applichiamo l'I.E. dobbiamo calcolare $|X|,|Y|,|X\cap Y|$

Abbiamo che 
$|X|=|\{f\in S_{9}:f(2)=2\}|=(f=x_{1}2x_{3}x_{4}x_{5}x_{6}x_{7}x_{8}x_{9})=8!$
e similmente
$|Y|=|\{f\in S_{9}:f(4)=4\}|=(f=x_{1}x_{2}x_{3}4x_{5}x_{6}x_{7}x_{8}x_{9})=8!$
infine
$|X\cap Y|=|\{f\in S_{9}:f(2)=2\text{ e }f(4)=4\}|=(f=x_{1}2x_{3}4x_{5}x_{6}x_{7}x_{8}x_{9})=7!$
pertanto
$|X\cup Y|=8!+8!-7!$

Concludendo
$|\{f\in S_{9}:f(2)\not=2\text{ e }f(4)\not=4\}|=9!-(|X\cup Y)=9!-8!-8!+7!=7!(9\cdot8-8-8+1)=57\cdot 7!$

## Es. (inclusione-esclusion)
Quanti numeri di cellulare ci sono che hanno tre cifre consecutive uguali?

Vogliamo calcolare 
$|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{i}=x_{i+1}=x_{i+2} \text{ per qualche }1\leq i\leq 5\}|$
($[0,9]=\{0,1,2,3,4,5,6,7,8,9\}$)

Poniamo
$A_{1}=\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}\}$
$A_{2}=\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{2}=x_{3}=x_{4}\}$
$A_{3}=\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{3}=x_{4}=x_{5}\}$
$A_{4}=\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{4}=x_{5}=x_{6}\}$
$A_{5}=\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{5}=x_{6}=x_{7}\}$

Dobbiamo quindi calcolare 
$|A_{1}\cup A_{2}\cup A_{3}\cup A_{4}\cup A_{5}|$

Applichiamo I.E.
$$\begin{array}{l}
|A_{1}\cup A_{2}\cup A_{3}\cup A_{4}\cup A_{5}|= \\
=|A_{1}|+|A_{2}|+|A_{3}|+|A_{4}|+|A_{5}|-|A_{1}\cap A_{2}|-|A_{1}\cap A_{3}|-|A_{1}\cap A_{4}|-|A_{1}\cap A_{5}|- \\
-|A_{2}\cap A_{3}|-|A_{2}\cap A_{4}|-|A_{2}\cap A_{5}|-|A_{3}\cap A_{4}|-|A_{3}\cap A_{5}|-|A_{4}\cap A_{5}|+|A_{1}\cap A_{2}\cap A_{3}|+ \\
+|A_{1}\cap A_{2}\cap A_{4}|+|A_{1}\cap A_{2}\cap A_{5}|+|A_{1}\cap A_{3}\cap A_{4}|+|A_{1}\cap A_{3}\cap A_{5}|+|A_{1}\cap A_{4}\cap A_{5}|+ \\
+|A_{2}\cap A_{3}\cap A_{4}|+|A_{2}\cap A_{3}\cap A_{5}|+|A_{2}\cap A_{4}\cap A_{5}|+|A_{3}\cap A_{4}\cap A_{5}|- \\
-|A_{1}\cap A_{2}\cap A_{3}\cap A_{4}|-|A_{1}\cap A_{2}\cap A_{3}\cap A_{5}|-|A_{1}\cap A_{2}\cap A_{4}\cap A_{5}|-|A_{1}\cap A_{3}\cap A_{4}\cap A_{5}|- \\
-|A_{2}\cap A_{3}\cap A_{4}\cap A_{5}|+|A_{1}\cap A_{2}\cap A_{3}\cap A_{4}\cap A_{5}|
\end{array}$$

Abbiamo che
$|A_{1}|=|A_{2}|=|A_{3}|=|A_{4}|=|A_{5}|=10^5$
$|A_{1}\cap A_{2}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}\}|=10^4$
similmente
$|A_{2}\cap A_{3}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{2}=x_{3}=x_{4}=x_{5}\}|=10^4$
$|A_{3}\cap A_{4}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{3}=x_{4}=x_{5}=x_{6}\}|=10^4$
$|A_{4}\cap A_{5}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{4}=x_{5}=x_{6}=x_{7}\}|=10^4$
anche
$A_{1}\cap A_{3}=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}=x_{5}\}|=10^3$
$A_{2}\cap A_{4}=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{2}=x_{3}=x_{4}=x_{5}=x_{6}\}|=10^3$
$A_{3}\cap A_{5}=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{3}=x_{4}=x_{5}=x_{6}=x_{7}\}|=10^3$
anche 
$|A_{1}\cap A_{4}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}=x_{5}=x_{6}\}|=10^3$
e similmente
$|A_{2}\cap A_{5}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{2}=x_{3}=x_{4}=x_{5}=x_{6}=x_{7}\}|=10^3$
anche 
$|A_{1}\cap A_{5}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}=x_{5}=x_{6}=x_{7}\}|=10^3$
inoltre
$|A_{1}\cap A_{2}\cap A_{3}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}=x_{5}\}|=10^3$
e similmente 
$|A_{1}\cap A_{2}\cap A_{4}|=|\{(x_{1},\dots,x_{7})\in[0,9]^7:x_{1}=x_{2}=x_{3}=x_{4}=x_{5}=x_{6}\}|=10^2$
$|A_{1}\cap A_{2}\cap A_{5}|=10^2$,$|A_{1}\cap A_{3}\cap A_{4}|=10^2$
$|A_{1}\cap A_{3}\cap A_{5}|=10$,$|A_{1}\cap A_{4}\cap A_{5}|=10^2$
$|A_{2}\cap A_{3}\cap A_{4}|=10^3$,$|A_{2}\cap A_{3}\cap A_{5}|=10^2$
$|A_{2}\cap A_{4}\cap A_{5}|=10^2$,$|A_{3}\cap A_{4}\cap A_{5}|=10^3$
anche 
$|A_{1}\cap A_{2}\cap A_{3}\cap A_{4}|=10^2$,$|A_{1}\cap A_{2}\cap A_{3}\cap A_{5}|=10$
$|A_{1}\cap A_{2}\cap A_{4}\cap A_{5}|=10$,$|A_{1}\cap A_{3}\cap A_{4}\cap A_{5}|=10$
$|A_{2}\cap A_{3}\cap A_{4}\cap A_{5}|=10^2$
infine
$|A_{1}\cap A_{2}\cap A_{3}\cap A_{4}\cap A_{5}|=10$

Concludendo
$$\begin{array}{l}
|A_{1}\cup A_{2}\cup A_{3}\cup A_{4}\cup A_{5}|= \\
=5\cdot 10^5-(4\cdot10^4+3\cdot10^3+2\cdot10^3+10^3)+ \\
+(10^3+2\cdot10^2+4\cdot10^2+2\cdot10^3+10)-(3\cdot10+2\cdot10^2)+10= \\
=5\cdot10^5-4\cdot10^4-3\cdot10^3+4\cdot10^2-10= \\
=457390
\end{array}$$

