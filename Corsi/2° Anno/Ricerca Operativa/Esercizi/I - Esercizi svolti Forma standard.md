# Esercizio 1
$$\begin{array}{}
max\quad 5(-3x_{1}+5x_{2}-7x_{3})+34 \\
-2x_{1}+7x_{2}+6x_{3}-2x_{1}\leq 5 \\
-3x_{1}+x_{3}+12\geq 13 \\
x_{1}+x_{2}\leq-2 \\
x_{1}\leq 0 \\
x_{2}\geq 0
\end{array}$$
$x_{3}$ non è vincolato quindi $x_{3}=x_{3}^{+}-x_{3}^{-}$
$x_{1}\leq 0$ e deve essere $\geq 0$ quindi $-x_{1}=\hat{x}_{1}$
$$max\rightarrow min\quad (-3x_{1}+5x_{2}-7x_{3})(-1)\rightarrow min -3\hat{x}_{1}-5x_{2}+7x_{3}^{+}-7x_{3}^{-}$$
1° vincolo
$$\begin{array}{}
-2x_{1}+7x_{2}+6x_{3}-2x_{1}\leq 5\quad\rightarrow\quad-4x_{1}+7x_{2}+6x_{3}\leq 5 \\
-4x_{1}+7x_{2}+6x_{3}+s_{1}=5\quad\rightarrow\quad 4\hat{x}_{1}
+7x_{2}+6x_{3}^{+}-6x_{3}^{-}+s_{1}\leq 5\end{array}$$
2° vincolo
$$\begin{array}{}
-3x_{1}+x_{3}+12\geq 13\quad\rightarrow\quad-3x_{1}+x_{3}+12-s_{2}=13 \\
3\hat{x}_{1}+x_{3}^{+}-x_{3}^{-}-s_{2}=13-12\quad\rightarrow\quad 3\hat{x}_{1}+x_{3}^{+}-x_{3}^{-}-s_{2}=1
\end{array}$$
3° vincolo
$$\begin{array}{}
x_{1}+x_{2}\leq-2\quad\text{il termine noto deve essere } \geq 0 \quad\rightarrow \\
-x_{1}-x_{2}\geq 2\quad\rightarrow\quad -x_{1}-x_{2}-s_{3}=2\quad\rightarrow \\
\hat{x}_{1}-x_{2}-s_{3}=2
\end{array}$$
variabili $\geq 0$
$$\hat{x}_{1}\geq 0,x_{2}\geq 0,x_{3}^{+}\geq 0,x_{3}^{-}\geq 0,s_{1}\geq 0,s_{2}\geq 0,s_{3}\geq 0,$$
quindi il risultato è
$$\begin{array}{}
min\quad-3\hat{x}_{1}-5x_{2}+7x_{3}^{+}-7x_{3}^{-} \\
4\hat{x}_{1} +7x_{2}+6x_{3}^{+}-6x_{3}^{-}+s_{1}= 5 \\
3\hat{x}_{1}+x_{3}^{+}-x_{3}^{-}-s_{2}=1 \\
\hat{x}_{1}-x_{2}-s_{3}=2 \\
\hat{x}_{1}\geq 0,x_{2}\geq 0,x_{3}^{+}\geq 0,x_{3}^{-}\geq 0,s_{1}\geq 0,s_{2}\geq 0,s_{3}\geq 0,
\end{array}$$

# Esercizio 2

$$\begin{array}{}
min\quad-13x_{1}-20x_{2}+5x_{3}+x_{4} \\
-4x_{1}+x_{2}\geq 1 \\
5x_{2}+3x_{3}=4 \\
3x_{1}+12x_{3}-x_{4}\geq-2 \\
x_{2}+x_{3}+50x_{4}\leq 3 \\
x_{1}\geq 0,x_{2}\geq 0,x_{3}\geq 0
\end{array}$$
$x_{4}$ non vincolato quindi lo divido in $x_{4}=x_{4}^{+}-x_{4}^{-}$
1° vincolo
$$-4x_{1}+x_{2}\geq 1\quad\rightarrow\quad-4x_{1}+x_{2}-s_{1}=1$$
2° vincolo non abbiamo nulla da cambiare
3° vincolo
$$\begin{array}{}
3x_{1}+12x_{3}-x_{4}\geq-2\quad\rightarrow\quad \text{il } -2\not\geq 0 \text{ quindi moltiplico per } (-1) \\
-3x_{1}-12x_{3}+x_{4}\leq 2\quad\rightarrow\quad -3x_{1}-12x_{3}+x_{4}^{+}-x_{4}^{-}+s_{2}=2
\end{array}$$
4° vincolo
$$\begin{array}{}
x_{2}+x_{3}+50x_{4}\leq 3\quad\rightarrow\quad x_{2}+x_{3}+50x_{4}^{+}-50x_{4}^{-}+s_{3}=3
\end{array}$$

Risultato
$$\begin{array}{}
min\quad-13x_{1}-20x_{2}+5x_{3}+x_{4}^{+}-x_{4}^{-} \\
-4x_{1}+x_{2}-s_{1}=1 \\
5x_{2}+3x_{3}=4 \\
-3x_{1}-12x_{3}+x_{4}^{+}-x_{4}^{-}+s_{2}=2 \\
x_{2}+x_{3}+50x_{4}^{+}-50x_{4}^{-}+s_{3}=3\\
x_{1}\geq 0,x_{2}\geq 0,x_{3}\geq 0,x_{4}^{+}\geq 0,x_{4}^{-}\geq 0,s_{1}\geq 0,s_{2}\geq 0,s_{3}\geq 0,
\end{array}$$

[[II - SBA Esempio spiegazione|Prossimo Argomento]]