## Es. 
Trovare formula chiusa per $$\sum_{k=0}^{n}(k^2+k)$$
Sappiamo dalla teoria che $\exists\ f\in\mathbb{R}[x]$ tale che $deg(f(x))\leq 2+1$ e $$\sum^{n}_{k=0}(k^2+k)=f(n)\quad\quad\forall\ n\in\mathbb{N}$$Quindi $\exists\ a,b,c,d\in\mathbb{R}$ tali che $$\sum^{n}_{k=0}(k^2+k)=a\cdot n^3+b\cdot n^2+c\cdot n+d\quad\quad\forall\ n\in\mathbb{N}$$Ma allora $$\begin{array}{l}
\begin{cases}
0=d & (n=0) \\
2=a+b+c+d & (n=1) \\
2+6=8a+4b+2c+d & (n=2) \\
12+8=27a+9b+3c+d & (n=3) 
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
\begin{cases}
d=0 \\
a+b+c=2 \\
8a+4b+2c=8 \\
27a+9b+3c=20
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
c=2-a-b \\
\begin{cases}
8a+4b+2(2-a-b)=8 \\
27a+9b+3(2-a-b)=20
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
\begin{cases}
6a+2b=4 \\
24a+6b=14
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
\begin{cases}
3a+b=2 \\
12a+3b=7
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
\begin{cases}
b=2-3a \\
12a+3(2-3a)=7
\end{cases} \\\quad\quad\quad\quad\Downarrow \\
3a=1\implies a=\frac{1}{3} \\\quad\quad\quad\quad\Downarrow \\
b=2-3a=2-3\left(\frac{1}{3}\right)=1 \\\quad\quad\quad\quad\Downarrow \\
c=2-a-b=2-\frac{1}{3}-1=\frac{6-3-1}{3}=\frac{2}{3}
\end{array}$$
Concludendo $$\sum^{n}_{k=0}(k^2+k)=\frac{n^3}{3}+n^2+\frac{2}{3}n\quad\quad\forall\ n\in\mathbb{N}$$
