### Problema 1
Progettare un algoritmo efficiente per il seguente problema
input: vettore ordinato $A[1:n]$ di n bit, ovvero $A[i]\in\{0,1\}$
output: l’indice k dell’ultimo 0 (numero di zeri)

goal: $O(\log n)$


Idea: uso approccio di ricerca binaria
$$\begin{array}{l}
\text{algoritmo2: UltimoZeroRic}(A,i,j) \\
 \text{if } i>j\text{ then} \\
\quad \text{return }-1 \\
m=\left\lfloor  \frac{i+j}{2}  \right\rfloor  \\
\text{if }A[m=0]\text{ e }A[m+1]=1\text{ then} \\
\quad \text{return }m \\
\text{if } A[m]=1 \text{ then} \\
\quad \text{return UltimoZeroRic}(A,i,m-1) \\
\text{else } \\
\quad\text{return UltimoZeroRic}(A,m+1,j)
\end{array}$$

$$\begin{array}{\quad l}
\text{algoritmo1: UltimoZero}(A) \\
n=len(A) \\
\text{if }A[n]=0\text{ then} \\
\quad\text{return }n \\
\text{else}
\quad\text{return UltimoZeroRic}(A,1,n-1)
\end{array}$$

questo ha costo $O(\log n)$
dando un indice $k$ riusciamo a fare $O(\log k)$?

### Problema 2
Progettare un algoritmo efficiente per il seguente problema
Input: vettore $A[1:n]$ di n bit, ovvero $A[i]\in\{0,1\}$
Output: un indice k tale che # di zeri in $A[1:k]$= # di uni in $A[k+1:n]$

goal: $O(n)$


possibile soluzione
parto con due contatori i e j, rispettivamente da sinistra e destra
aumento i fino a quando trovo 0, una volta trovato decremento j fino a quando trovo 1
ripeto fino a quando 