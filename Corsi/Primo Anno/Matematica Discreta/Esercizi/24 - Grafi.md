## Es. (isomorfismo)
I grafi $G$ e $H$ sono isomorfi?
![[Es_Grafi.png|400]]

No perché $G$ ha cicli di lunghezza 4, mentre $H$ no.
Alternativamente, $G$ ha 2 cicli di lunghezza 5, $H$ ha (almeno) 7 cicli di lunghezza 5.

## Es. (colorazione a teoria)
Sia $G=([10]^3,E)$, dove $$\{(a_{1},a_{2},a_{3}),(b_{1},b_{2},b_{3})\}\in E\iff|\{i\in[3]:a_{i}\not=b_{i}\}|=1\quad\quad\forall(a_{1},a_{2},a_{3}),(b_{1},b_{2},b_{3})\in[10]^3$$
Quindi , per esempio, $\{(1,2,3),(3,2,3)\}\in E$, ma $\{(1,2,3),(6,2,10)\}\not\in E$.

è possibile colorare $G$ con 30 colori?

Sappiamo dalla teoria che $$\chi(G)\leq\underset{v\in V}{max}\{d(v)\}+1$$
Quindi è possibile colorare $G$ con $\underset{v\in V}{max}\{d(v)\}+1$ colori.
Sia $v=(a_{1},a_{2},a_{3})\in[10]^3$. Allora $$\begin{array}{l}
d(v)=|\{u\in V:\{u,v\}\in E\}| \\ \\
=|\{(b_{1},b_{2},b_{3})\in[10]^3:\{(a_{1},a_{2},a_{3}),(b_{1},b_{2},b_{3})\}\in E\}\}| \\ \\
=|\{(b_{1},b_{2},b_{3})\in[10]^3:|\{i\in[3]:a_{i}=b_{i}\}|=2\}| \\ \\
=|\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}\not=a_{1},\ b_{2}=a_{2},\ b_{3}=a_{3}\}\cup \\
\cup\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}=a_{1},\ b_{2}\not=a_{2},\ b_{3}=a_{3}\}\cup \\
\cup\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}=a_{1},\ b_{2}=a_{2},\ b_{3}\not=a_{3}\}|= \\ \\
=|\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}\not=a_{1},\ b_{2}=a_{2},\ b_{3}=a_{3}\}|+ \\
+|\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}=a_{1},\ b_{2}\not=a_{2},\ b_{3}=a_{3}\}|+ \\
+|\{(b_{1},b_{2},b_{3})\in[10]^3:b_{1}=a_{1},\ b_{2}=a_{2},\ b_{3}\not=a_{3}\}|= \\ \\
=9+9+9=27
\end{array}$$
Quindi $d(v)=27$. Ma $v$ è qualsiasi $\implies d(u)=27\quad\quad\forall\ u\in V$. Pertanto $$\underset{u\in V}{max}\{d(u)\}+1=27+1=28$$
Pertanto $\chi(G)\leq 28\implies G$ è colorabile con 28 colori $\implies$con 30 colori.

## Es. (accoppiamento a teoria)
Sia $G\in(V,E)$ un grafo bipartito, dove $V=A\uplus B$, $A$ e $B$ sono indipendenti, definito ponendo $$\begin{array}{l}
A\overset{def}{=}\binom{[n]}{2}, & B\overset{def}{=}\binom{[n]}{3} & (n\in \mathbb{N},n\geq 5) \\
\text{ e dove } \\
\{X,Y\}\in E \iff & X\subseteq Y & \forall\ X\in A, \forall\ Y\in B
\end{array}$$
Decidere se $\exists$ un accoppiamento di $A$ in $B$. 

Sappiamo dalla teoria che $$\begin{array}{}
d(X)\geq d(Y) &  & \exists \text{ un accoppiamento} \\
\forall\ X\in A,\forall\ Y\in B & \implies & \text{di } A \text{ in } B
\end{array}$$Sia $Y\in B\implies Y\subseteq[n]\text{ e }|Y|=3$ quindi $$\begin{array}{l}
d(y)=|\{X\in A:\{X,Y\}\in E\}| \\
=|\{X\subseteq[n]:|X|=2,X\subseteq Y\}| \\
=|\{X\subseteq Y:|X|=2\}| \\
=\displaystyle\binom{3}{2}=3
\end{array}$$Pertanto $d(X)=n-2\geq 3=d(Y)\quad\quad\forall\ X\in A,Y\in B\implies$ esiste un accoppiamento di $A$ in $B$.