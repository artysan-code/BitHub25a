supponiamo di avere i seguenti vincoli $$\begin{array}{}
x_{2}+3x_{3}\leq 5 \\
x_{1}+x_{2}+x_{3}\leq 8 \\
x_{1}-5x_{3}\leq 4 \\
x_{1},x_{2},x_{3}\geq 0
\end{array}\quad\stackrel{\text{forma standard}}{\longrightarrow}\quad
\begin{array}{}
x_{2}+3x_{3}+s_{1}=5 \\
x_{1}+x_{2}+x_{3}+s_{2}=8 \\
x_{1}-5x_{3}+s_{3}=4 \\
x_{1},x_{2},x_{3},s_{1},s_{2},s_{3}\geq 0
\end{array}$$
$$x^{1}=[3,5,0]$$
$$\begin{array}{l}
1(5)+3\cdot(0)=5\leq 5 & \text{ok} \\
(3)+(5)+(0)=8\leq 8 & \text{ok} \\
(3)-5\cdot(0)=3\leq 4 & \text{ok} \\ \\
x_{2}+3x_{3}+s_{1}=5: \\
 5+3\cdot 0+s_{1}=5\rightarrow 5+s_{1}=5\rightarrow s_{1}=0 \\
x_{1}+x_{2}+x_{3}+s_{2}=8: \\
3+5+0+s_{2}=8\rightarrow 8+s_{2}=8\rightarrow s_{2}=0 \\
x_{1}-5x_{3}+s_{3}=4: \\
3-5\cdot 0+s_{3}=4\rightarrow 3+s_{3}=4\rightarrow s_{3}=1 \\
\end{array}$$
$\implies x^{1}=[3,5,0,0,0,1]$ è SBA

In questo caso è SBA perché, all'interno del vettore, abbiamo 
#numero_variabili($\#x_{i}+\# s_{i}$)- #numero_vincoli= #numero_0
- $\#(x_{1}+x_{2}+x_{3}+s_{1}+s_{2}+s_{3})-\#(\text{vincolo}_{1}+\text{vincolo}_{2}+\text{vincolo}_{3})=3$
	quindi in questo caso dobbiamo avere 3 zeri nel vettore finale 
- inoltre il resto dei valori DEVE essere maggiore di 0 (>0)
dato che il nostro esempio rispetta entrambe le richieste è un SBA

$$x^{2}=\left[ \frac{7}{2}, \frac{9}{2},0 \right]$$
$$\begin{array}{l}
1\left( \frac{9}{2} \right)+3(0)=\frac{9}{2}\leq 5 & \text{ok} \\
1\left( \frac{7}{2} \right)+1\left( \frac{9}{2} \right)+\frac{1}{0}=\frac{16}{2}\leq 8 & \text{ok} \\
1\left( \frac{7}{2} \right)+5(0)=\frac{7}{2}\leq 4 & \text{ok} \\ \\
x_{2}+3x_{3}+s_{1}=5: \\
 \frac{9}{2}+3\cdot 0+s_{1}=5\rightarrow \frac{9}{2}+s_{1}=5\rightarrow s_{1}=\frac{1}{2} \\
x_{1}+x_{2}+x_{3}+s_{2}=8: \\
\frac{7}{2}+\frac{9}{2}+0+s_{2}=8\rightarrow 8+s_{2}=8\rightarrow s_{2}=0 \\
x_{1}-5x_{3}+s_{3}=4: \\
\frac{7}{2}-5\cdot 0+s_{3}=4\rightarrow s_{3}=\frac{1}{2} \\ \\
\end{array}$$
$\implies x^{2}=\left[ \frac{7}{2}, \frac{9}{2},0, \frac{1}{2},0, \frac{1}{2} \right]$ NON è SBA

In questo caso non lo è perché, all'interno del vettore, non rispetta:
- $\#(x_{1}+x_{2}+x_{3}+s_{1}+s_{2}+s_{3})-(\#(\text{vincolo}_{1}+\text{vincolo}_{2}+\text{vincolo}_{3}))=3$ 
	ma noi abbiamo solo 2 zeri e questo impedisce che sia un SBA ma solo una Soluzione di Base (**SB**)

[[III - Esercizi Simplesso|Esercizi]]

[[III - Teoria Simplesso|Prossimo Argomento]]