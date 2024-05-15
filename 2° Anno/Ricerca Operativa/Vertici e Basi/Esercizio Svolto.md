Dato il poliedro descritto da $$\begin{array}{l}
7x_{1}-5x_{2}+x_{3}\leq 2 \\
-2x_{1}+3x_{2}+x_{3}\geq 1 \\
x_{1},x_{2},x_{3}\geq 0
\end{array}$$
Verificare se $x^{'}=[1\ 1\ 0]$ è un vertice

$$\begin{array}{l}
7x_{1}-5x_{2}+x_{3}\leq 2 \\
+2x_{1}-3x_{2}-x_{3}\leq -1
\end{array}$$

quindi $$A=\begin{bmatrix}
7 & -5 & 1 \\
2 & -3 & -1
\end{bmatrix}\quad\quad
b=\begin{bmatrix}
2 \\ 1
\end{bmatrix}$$
trovo le disuguaglianze attive $$\begin{array}{l}
7\cdot 1-(5\cdot 1)+1\cdot 0=7-5+0=2\quad\ \ \ \implies \text{attiva} \\
2\cdot 1-(3\cdot 1)-1\cdot 0=2-3-0=-1\quad\implies \text{attiva}
\end{array}$$
Siamo in $\textsf{I\kern-0.1ex R}^{3}\implies$ dobbiamo avere 3 disuguaglianze attive, avendone 2 dobbiamo moltiplicare $A\cdot (-Id)$ $$A=\begin{bmatrix}
7 & -5 & 1 \\
2 & -3 & -1 \\
-1 & 0 & 0 \\
0 & -1 & 0 \\
0 & 0 & -1
\end{bmatrix}\quad\quad
b=\begin{bmatrix}
2 \\ 1 \\
0 \\ 0 \\ 0
\end{bmatrix}$$
quindi cerchiamo una terza disuguaglianza attiva $$\begin{array}{r}
-1\cdot 1+0\cdot 1+0\cdot 0=-1\implies \text{non attiva} \\
0\cdot -1\cdot 1+0\cdot 0=-1\implies \text{non attiva} \\
0\cdot 1+0\cdot 1+0\cdot 0=0\implies\quad\quad\text{attiva}
\end{array}$$
le disuguaglianze attive che abbiamo sono $[1,2,5]\quad \textsf{I\kern-0.1ex R}^{3}$; ora controlliamo se $x^{'}=[1\ 1\ 0]$ è un vertice. Per farlo controlliamo se il determinante di $A \neq 0$ (indicando che sono linearmente indipendenti) $$\begin{array}{}
A=\begin{bmatrix}
7 & -5 & 1 \\
2 & -3 & -1
\end{bmatrix} \\
\downarrow \\
\text{sommo i prodotti delle diagonali primarie e} \\
\text{sottraggo i prodotti delle diagonali secondarie} \\
A=\begin{bmatrix}
7 & 2 & 0 & 7 & 2 \\
-5 & -3 & 0 & -5 & -3 \\
1 & -1 & -1 & 1 & -1
\end{bmatrix} \\
=(7(-3)(-1))+(2(0)(1))+(0(-5)(-1))-(1(-3)(0))-(-1(0)(7))-(-1(-5)(2))= \\
21+0+0-0-0-10= 11\neq 0\implies x^{'}=[1\ 1\ 0] \text{ è un vertice}
\end{array}$$