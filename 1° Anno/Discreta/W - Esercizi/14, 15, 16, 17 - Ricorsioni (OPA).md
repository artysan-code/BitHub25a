## Es. 
Sia $n\in\mathbb{P}$. Calcolare il numero di sottoinsiemi di $[n]$ che contengono due interi consecutivi.

Per esempio :
$n=1\implies [1]\implies\varnothing,\{1\}\implies2$
$n=2\implies[2]\implies\varnothing,\{1\},\{2\}\implies3$
$n=3\implies[3]\implies \varnothing,\{1\},\{2\},\{3\},\{1,3\}\implies5$
$n=4\implies[4]\implies\dots \implies8$

Sia $f(n)$ il numero cercato ($\implies f(1)=2,f(2)=3,f(3)=5,f(4)=8$)
Sembra la sequenza di Fibonacci pensiamo quindi che 
$f(n)=f(n-1)+f(n-2)\quad\quad\forall\ n\geq 3$

Cerchiamo di dimostrarlo. Abbiamo che
$f(n)=|\{S\subseteq[n]:1\leq i\leq n-i\quad i\in S\implies i+1\not\in S\}|$
ma
$$\begin{array}{l}
\{S\subseteq[n]:1\leq i\leq n-i\quad i\in S\implies i+1\not\in S\}= \\
\{S\subseteq[n]:S\text{ sparso, }n\in S\}\cup\{S\subseteq[n]:S \text{ sparso, }n\not\in S\}
\end{array}$$
dove $S$ è sparso se e solo se $1\leq i\leq n-1,\ i\in S\implies i+1\not\in S$
D'altronde
$\{S\subseteq[n]:S\text{ sparso, }n\in S\}=\{S\subseteq[n]: S\text{ sparso, }n\in S,\ n-1\not\in S\}$
e
$\{S\subseteq[n]:S\text{ sparso, }n\not\in S\}=\{S\subseteq[n-1]: S\text{ sparso}\}$
quindi
$|\{S\subseteq[n]:S\text{ scarso, }n\not\in S\}|=|\{S\subseteq[n-1]:S\text{ scarso}\}|\overset{(def)}{=}f(n-1)\quad\quad(*)$
inoltre la funzione
$S\mapsto S\cup\{n\}$ 
è una biiezione da
$\{S\subseteq[n-2]:S\text{ sparso}\}$
a
$\{T\subseteq[n]:T\text{ sparso, }n\in T,\ n-1\not\in T\}$

quindi
$|\{T\subseteq[n]:T\text{ sparso, }n\in T,\ n-1\not\in T\}|=|\{S\subseteq[n-2]:S\text{ sparso}\}|\overset{\text{def di }f}{=}f(n-2)\quad\quad(**)$
pertanto$f(n)=|\{S\subseteq[n]:S\text{ sparso}\}|=|\{S\subseteq[n]:S\text{ sparso, }n\not\in S\}|+|\{S\subseteq[n]:S\text{ sparso, }n\in S\}|\underset{(**)}{\overset{(*)}{=}}$$\underset{(**)}{\overset{(*)}{=}}f(n-1)+f(n-2)$

Quindi
$f(2)=3,f(1)=2$
e
$f(n)=f(n-1)+f(n-2)$ se $n\geq 3$

## Es. (Ric. lin. a coeff. cost.)
Risolvere la ricorsione lineare a coefficienti costanti $$\begin{array}{}
f(n)=2f(n-1)+f(n-2) & \forall\ n\geq 2 & (*) \\
\end{array}$$Condizioni iniziali
$f(0)=1,\ f(1)=3$

Portiamo la ricorsione in forma standard:
$$f(n+2)=2f(n+1)+f(n)\quad\quad\forall\ n\geq 0$$

L'equazione caratteristica è $x^2-2x-1=0$
Le sue radici sono: $$x=\frac{2\pm\sqrt{(-2)^2+4}}{2}=\frac{2\pm\sqrt{8}}{2}=\frac{2\pm2\sqrt{2}}{2} $$e quindi $$\begin{array}{}
\delta_{1}=\frac{1+\sqrt{2}}{1} & \delta_{2}=\frac{1-\sqrt{2}}{1}
\end{array}$$di molteplicità $d_{1}=1$ e $d_{2}=1$ (in effetti $x^2-2x-1=(x-(1+\sqrt{2})^1)(x-(1-\sqrt{2}))^1$).

Sappiamo dalla teoria che $\exists\ P_{1}(x),P_{2}(x)\in\mathbb{C}[x]$ tali che $deg(P_{1})\leq d_{1}-1,\ deg(P_{2}\leq d_{2}-1)$ e $$f(n)=P_{1}(n)\cdot(\delta_{1})^n+P_{2}(n)\cdot(\delta_{2})^n\quad\quad\forall\ n\geq 0$$Quindi $\exists\ a,b\in\mathbb{C}$ tali che $$f(n)=a\cdot(1+\sqrt{2})^n+b\cdot(1-\sqrt{2})^n\quad\quad\forall\ n\geq 0$$
per trovare $a$ e $b$ usiamo le C.I.. Abbiamo $$\begin{cases}
1=f(0)=a+b \\
3=f(1)=a\cdot(1+\sqrt{2})+b\cdot(1-\sqrt{2})
\end{cases}$$quindi $$\begin{array}{}
b=1-a \\
\Downarrow \\
3=a\cdot(1+\sqrt{2})+(1-a)\cdot(1-\sqrt{2}) \\
\Downarrow \\
3-1+\sqrt{2}=a(1+\sqrt{2}-1+\sqrt{2}) \\
\Downarrow \\
a=\frac{2+\sqrt{2}}{2\sqrt{2}}=\frac{2\sqrt{2}+2}{4}=\frac{1+\sqrt{2}}{2} \\
\Downarrow \\
b=1-a=1-\frac{1+\sqrt{2}}{2}=\frac{1-\sqrt{2}}{2}
\end{array}$$
concludendo
$f(n)=\frac{1+\sqrt{2}}{2}\cdot(1+\sqrt{2})^n+\frac{1-\sqrt{2}}{2}(1-\sqrt{2})^n\quad\quad\forall\ n\in\mathbb{N}$

## Es. (Ric. lin. a coeff. cost.)
Risolvere la ricorsione lineare a coefficienti costanti $$f(n+3)=-2f(n+2)-2f(n+1)-4f(n)\quad\quad\forall\ n\in\mathbb{N}$$con le condizioni iniziali 
$f(0)=0, f(1)=2, f(2)=0$

La ricorsione è già in forma standard. L'equazione caratteristica è 
$x^3=-2x^2-2x-4\implies x^3+2x^2+2x+4=0\quad\quad(*)$

Vediamo che $x=-2$ è una radice di $(*)$, usiamo Ruffini
$$\begin{array}{c|ccc|c}
 & 1 & +2 & +2 & +4 \\
 -2&  & -2 & 0 & -4\\
\hline
 & 1 & 0 & 2 & 0
\end{array}$$
quindi abbiamo $x^3+2x^2+2x+4=0=(x^2+2)^2(x+2)$

Risolviamo $x^2+2=0$:$$\begin{array}{}
x=\frac{-0\pm\sqrt{0^2-4\cdot2}}{2}=\frac{\pm\sqrt{-8}}{2}=\frac{\pm\sqrt{4(-2)}}{2}= \\
=\pm\frac{\sqrt{4}\cdot\sqrt{-2}}{2}=\pm\frac{2\cdot\sqrt{-2}}{2}=\pm\sqrt{-2}= \\
=\pm\sqrt{2}\cdot\sqrt{-1}=\pm\ i\cdot\sqrt{2}
\end{array}$$
Pertanto le radice dell'equazione sono $$\begin{array}{}
\delta_{1}=-2, & \delta_{2}=i\sqrt{2}, & \delta_{3}=-i\sqrt{2}
\end{array}$$di molteplicità $d_{1}=1,\ d_{2}=1,\ d_{3}=1$. Sappiamo dalla teoria che $\exists\ P_{1}(x),P_{2}(x),P_{3}(x)\in\mathbb{C}$ tali che $deg(P_{1})\leq d_{1}-1,\ deg(P_{2})\leq d_{2}-1,\ deg(P_{3})\leq d_{3}-1$ e $$f(n)=P_{1}(n)\cdot(\delta_{1})^n+P_{2}(n)\cdot(\delta_{2})^n+P_{3}(n)\cdot(\delta_{3})^n\quad\quad\forall\ n\in\mathbb{N}$$
Quindi $\exists\ a,b,c\in\mathbb{C}$ tali che $$f(n)=a\cdot(-2)^n+b\cdot(i\sqrt{2})^n+c\cdot(-i\sqrt{2})^n\quad\quad\forall\ n\in\mathbb{N}$$
Per trovare $a,b,c\in\mathbb{C}$ usiamo le C.I.
$$\begin{array}{l}
0=f(0)=a+b+c \\
2=f(1)=a(-2)+b(i\sqrt{2})+c(-i\sqrt{2}) \\
0=f(2)=a(-2)^2+b(i\sqrt{2})^2+c(-i\sqrt{2})^2 \\ \\
\begin{cases}
a+b+c=0 \\
-2a+i\sqrt{2}\cdot b-i\cdot c\cdot\sqrt{2}=2 \\
4a+(-2)b+(-2)c=0
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\ 
a=-b-c \\
\begin{cases}
-2(-b-c)+i\sqrt{2}\cdot b-c(-i\sqrt{2})=2 \\
4(-b-c)+(-2)b+(-2)c=0
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b(2+i\sqrt{2})+c(2-i\sqrt{2})=2 \\
b(-6)+c(-6)=0
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b(2+i\sqrt{2})+c(2-i\sqrt{2})=2 \\
b+c=0
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
b=-c \\
\begin{cases}
-c(2+i\sqrt{2})+c(2-i\sqrt{2}=2)
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
c(-2i\sqrt{2})=2
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
c=\frac{2}{-2i\sqrt{2}}=\frac{1}{-i\sqrt{2}}=\frac{i}{\sqrt{2}} \\
\quad\quad\quad\quad\quad\Downarrow \\
b=\frac{-i}{\sqrt{2}} \\
\quad\quad\quad\quad\quad\Downarrow \\
a=b-c=\frac{-i}{\sqrt{2}}-\frac{i}{\sqrt{2}}=0
\end{array}$$

Concludendo $f(n)=\frac{-i}{\sqrt{2}}(i\sqrt{2})^n+\frac{i}{\sqrt{2}}(-i\sqrt{2})^n\quad\quad\forall\ n\in\mathbb{N}$

## Es. 
$n=6$ $$f(5)=|\{(2,2,1),()\}|$$

## Es. (successione di Fibonacci)
Trovare una formula per la successione di Fibonacci.
Sappiamo che la successione di Fibonacci $\{f_{n}\}_{n=0,1,\dots}$ è tale che $$F_{n}=F_{n-1}+F_{n-2}\quad\quad\forall\ n\in\mathbb{N},\ n\geq 2\quad\quad(*)$$
con condizioni iniziali  $F_{0}=F_{1}=1$

Risolviamo la ricorsione lineare a coefficienti costanti $(*)$.
L'equazione caratteristica è 
$x^2=x+1$

Le radici sono $$x=\frac{1\pm \sqrt{1^2+4}}{2}=\frac{1\pm \sqrt{5}}{2}=\begin{cases}
\frac{1+\sqrt{5}}{2} \\ \\
\frac{1-\sqrt{5}}{2}
\end{cases}$$
Quindi abbiamo $\delta_{1}=\frac{1+\sqrt{5}}{2},\ \delta_{2}=\frac{1-\sqrt{5}}{2}$(in effetti $x^2-x-1=(x-\frac{1+\sqrt{5}}{2})^1(x-\frac{1-\sqrt{5}}{2})^2$)

Sappiamo dalla teoria che $\exists\ P_{1}(x),P_{2}(x)\in\mathbb{R}[x]$ tali che $deg(P_{1})\leq 1-1$ e $deg(P_{2})\leq 1-1$ e $$F_{n}=P_{1}(n)\cdot(\delta_{1})^n+P_{2}(n)\cdot(\delta_{2})^n\quad\quad\forall\ n\in\mathbb{N}$$
Quindi $\exists\ a,b\in\mathbb{C}$ tali che $$F_{n}=a(\frac{1+\sqrt{5}}{2})^n+b(\frac{1-\sqrt{5}}{2})^n\quad\quad\forall\ n\in\mathbb{N}$$
Per trovare $a$ e $b$ usiamo le condizioni iniziali. Abbiamo $$\begin{array}{l}
\begin{cases}
1=F_{0}=a+b \\
1=F_{1}=a(\frac{1+\sqrt{5}}{2})+b(\frac{1-\sqrt{5}}{2})
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
a+b=1 \\
a(\frac{1+\sqrt{5}}{2})+b(\frac{1-\sqrt{5}}{2})=1
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b=1-a \\
a(1+\sqrt{5})+(1-a)(1-\sqrt{5})=2
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b=1-a \\
a(1+\sqrt{5}-1+\sqrt{5})=2-1+\sqrt{5}
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b=1-a \\
a(2\sqrt{5})=1+\sqrt{5}
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b=1-a \\
a=\frac{1+\sqrt{5}}{2\sqrt{5}}
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
b=1-\frac{1+\sqrt{5}}{2\sqrt{5}}=\frac{\sqrt{5}-1}{2\sqrt{5}}
\end{array}$$
concludendo $$F_{n}=\frac{1+\sqrt{5}}{2\sqrt{5}}(\frac{1+\sqrt{5}}{2})^n+\frac{\sqrt{5}-1}{2\sqrt{5}}(\frac{1-\sqrt{5}}{2})^n\quad\quad\forall\ n\in\mathbb{N}$$

## Es.
Dieci persone  si dividono in 5 gruppi, ognuno di 2 persone. In quanti modi può avvenire questo? Le persone sono tra loro distinguibili. Quindi $$\begin{array}{}
\{\text{Persone}\}\leftrightarrow[10] & \text{e} & \{\text{Gruppi}\}\leftrightarrow\{\text{Scatole}\}
\end{array}$$
Pertanto il numero è $$\binom{10}{2,2,2,2,2}=\frac{10\cdot9\cdot8\cdot7\cdot6\cdot5\cdot4\cdot3\cdot2}{2\cdot2\cdot2\cdot2\cdot2}=5\cdot9\cdot7\cdot3\cdot5\cdot2\cdot3\cdot4$$
## Es. (Ric. lin. a coeff. cost. (molteplicità 2))
Risolvere la ricorsione lineare a coefficienti costanti 
$$f(n+3)=-3f(n+2)+4f(n)$$
con condizioni iniziali $f(0)=5,\ f(1)=-5,\ f(2)=9$

Portiamo la ricorsione in forma standard:$$f(n+3)+3f(n+2)-4f(n)=0$$$$x^3+3x^2-4=0$$
Usiamo Ruffini: $$\begin{array}{c|ccc|c}
 & 1 & +3 & 0 & - 4 \\
 -2&  & -2 & -2 & +4\\
\hline
 & 1 & 1 & -2 & 0
\end{array}$$
quindi abbiamo $x^3+3x^2-4=(x+2)(x^2+x-2)$

Troviamo le radici $$x=\frac{-1\pm \sqrt{1^2+8}}{2}=\frac{1\pm3}{2}=\begin{cases}
\frac{2}{2}=1 \\ \\
\frac{-4}{2}=-2
\end{cases}$$
Quindi abbiamo come radici $\delta_{1}=-2$ e $\delta_{2}=1$ le cui molteplicità sono $d_{1}=2$ e $d_{2}=1$. Sappiamo dalla teoria che $\exists\ P_{1}(x),P_{2}(x)\in\mathbb{C}$ tali che $deg(P_{1})\leq d_{1}-1,\ deg(P_{2})\leq d_{2}-1$ e $$f(n)=P_{1}(n)(\delta_{1})^n+P_{2}(n)(\delta_{3})^n\quad\quad\forall\ n\in\mathbb{N}$$
Quindi $\exists\ a,b,c\in\mathbb{C}$ tali che
$$f(n)=(a+b\cdot n)(\delta_{1})^n+c(\delta_{3})^n\quad\quad\forall\ n\in\mathbb{N}$$
Per trovare $a,b,c$ usiamo le C.I. $$\begin{array}{l}
\begin{cases}
5=f(0)=a+c \\
-5=f(1)=(a+b\cdot 1)(-2)+c(1) \\
9=f(2)=(a+b\cdot 2)(-2)^2+c(1)^2
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
5=a+c \\
-5=-2a-2b+c \\
9=4a+8b+c
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
a=5-c \\
\begin{cases}
-5=-2(5-c)-2b+c \\
9=4(5-c)+8b+c
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
-5=-10+3c-2b \\
9=20-3c+8b
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
c=\frac{2b+5}{3} \\
9=20-\not3(\frac{2b+5}{\not3})+8b
\end{cases}\\\quad\quad\quad\quad\quad\Downarrow \\
\begin{cases}
c=\frac{-2+5}{3} \\
b=-1
\end{cases} \\\quad\quad\quad\quad\quad\Downarrow \\
c=\frac{3}{3}=1\\\quad\quad\quad\quad\quad\Downarrow \\
a=5-c=5-1=4
\end{array}$$
concludendo $$f(n)=(4+(-1)\cdot n)(-2)^n+1(1)^n$$

## Es. 

