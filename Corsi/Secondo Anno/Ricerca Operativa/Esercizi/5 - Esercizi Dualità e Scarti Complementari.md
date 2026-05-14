# Esempio

$$\begin{array}{}
\underset{x,y}{min}\quad c^{T}x-d^{T}y \\
Ax\leq a \\
By\leq b \\
Cx+Dy=d \\
x\geq 0,\ y=0
\end{array}$$
svolgendo:
$$\begin{array}{}
\begin{cases}
a \\ b \\ d
\end{cases}\implies au_{1}+bu_{2}+du_{3} \\ \\
\begin{cases}
Ax+Cx \\
By+Dy
\end{cases}\implies \begin{cases}
Au_{1}+Cu_{3} \\
Bu_{2}+Du_{3}
\end{cases} \\ \\
x\geq 0,\ y=0 \implies \begin{cases}
\dots\leq\dots \\
\dots=\dots
\end{cases} \\ \\
cx-dt\implies \begin{cases}
\dots c \\
\dots-d
\end{cases} \\ \\
\begin{cases}
\dots\leq\dots \\
\dots\leq\dots \\
\dots=\dots
\end{cases}\implies u_{1}\leq 0,\ u_{2}\leq 0,\ u_{3}=0
\end{array}$$
quindi il risultato è
$$\begin{array}{}
\underset{u}{max}\quad a^{T}u_{1}+b^{T}u_{2}+d^{T}u_{3} \\
A^{T}u_{1}+C^{T}u_{3} \leq c\\
B^{T}u_{2}+D^{T}u_{3} = -d \\
u_{1}\leq 0,\ u_{2}\leq 0,\ u_{3}=0
\end{array}$$
Viene aggiunta la $^{T}$ per rappresentare che è stata trasposta

# Esempio 2

$$\begin{array}{}
\underset{x,y}{max}\quad c^{T}x-d^{T}y \\
Ax\leq a \\
By\leq b \\
Cx+Dy=d \\
x\geq 0,\ y=0
\end{array}$$
svolgendo$$\begin{array}{}
\begin{cases}
A \\ B \\ C
\end{cases}\implies au_{1}+bu_{2}+du_{3} \\ \\
\begin{cases}
Ax+Cx \\
By+Dy
\end{cases}\implies \begin{cases}
Au_{1}+Cu_{3} \\
Bu_{2}+Du_{3}
\end{cases} \\ \\
x\geq 0,\ y=0 \implies \begin{cases}
\dots\geq\dots \\
\dots=\dots
\end{cases} \\ \\
cx-dt\implies \begin{cases}
\dots c \\
\dots-d
\end{cases} \\ \\
\begin{cases}
\dots\leq\dots \\
\dots\leq\dots \\
\dots=\dots
\end{cases}\implies u_{1}\geq 0,\ u_{2}\geq 0,\ u_{3}=0
\end{array}$$quindi il risultato è $$\begin{array}{}
\underset{u}{min}\quad a^{T}u_{1}+b^{T}u_{2}+d^{T}u_{3} \\
A^{T}u_{1}+C^{T}u_{3} \geq c\\
B^{T}u_{2}+D^{T}u_{3} = -d \\
u_{1}\geq 0,\ u_{2}\geq 0,\ u_{3}=0
\end{array}$$

# Esempio 3

$$\begin{array}{}
\underset{x,y}{max}\quad 4x_{1}+3x_{2}+2x_{3} \\
x_{1}+2x_{2}+3x_{3}\leq 8 \\
2x_{1}\quad\quad\ \ \ -x_{3}\leq 7 \\
3x_{1}+4x_{2}-x_{3}\leq 5 \\
\quad\quad\ +x_{2}+x_{3}\leq 6 \\
x_{2}\geq 0
\end{array}$$
svolgendo $$\begin{array}{}
\begin{cases}
\dots 8 \\ \dots 7 \\
\dots 5 \\ \dots 6
\end{cases}\implies 8u_{1}+7u_{2}+5u_{3}+6u_{4} \\ \\
\begin{cases}
x_{1}+2x_{1}+3x_{1} \\
2x_{2}+4x_{2}+x_{2} \\
3x_{3}- x_{3}-x_{3}+x_{3}
\end{cases}\implies \begin{cases}
u_{1}+2x_{2}+3u_{3} \\
2u_{1}+4u_{3}+u_{4} \\
3u_{1}-u_{2}-u_{3}+u_{4}
\end{cases} \\ \\
\text{ dato che }x_{1}\text{ e }x_{3}\text{ non esistono, sono libere, quindi equivalgono a }x_{1}=0\text{ e } x_{3}=0  \\
x_{2}\geq 0\implies \begin{cases}
\dots=\dots \\
\dots\geq\dots \\
\dots=\dots
\end{cases} \\ \\
4x_{1}+3x_{2}+2x_{3}\implies \begin{cases}
\dots 4 \\
\dots 3 \\
\dots 2
\end{cases} \\ \\
\begin{cases}
\dots\leq\dots \\
\dots\leq\dots \\
\dots\leq\dots \\
\dots\leq\dots
\end{cases}\implies u_{1}\geq 0,\ u_{2}\geq 0,\ u_{3}\geq 0,u_{4}\geq 0
\end{array}$$
quindi il risultato è $$\begin{array}{}
\underset{u}{max}\quad 8u_{1}+7u_{2}+5u_{3}+6u_{4} \\
u_{1}+2x_{2}+3u_{3}= 4 \\
2u_{1}+4u_{3}+u_{4}=3 \\
3u_{1}-u_{2}-u_{3}+u_{4}=2 \\
u_{1}\geq 0,\ u_{2}\geq 0,\ u_{3}\geq 0,u_{4}\geq 0
\end{array}$$
