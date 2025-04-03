Due insiemi $A$ e $B$ hanno lo stesso numero di elementi ($|A|=|B|$) se riusciamo a "svuotarli" insieme

$|A|=|B|\quad \text{ se }\exists \text{ biiezione }b:A\to B$
$\forall\ a\in A\ \exists!\ b\in B:b=\beta(a)$
$\forall\ b\in B\ \exists!\ a\in A:b=\beta(a)$

$\not \exists \text{ biiezione } \beta:\mathbb{N}\to[0,1]$
$\forall\ n\in \mathbb{N}\quad f(n)=\frac{1}{n} \in[0,1]$
$|\mathbb{N}|=\aleph_{0}$ (aleph 0)
$\eth\subset \mathbb{N}\implies|\eth|=|\mathbb{N}|$ 
$|\mathbb{L}|>|\mathbb{T}|\implies|\mathbb{T}|=|\mathbb{N}|$

$T\to\rho_{T}=b(\omega_{0})-b(\omega_{A})-b(\omega_{R})\otimes b(\omega_{1_{1}})-s_{1_{1}}-s_{1_{2}}-b(\omega_{1_{2}})-m_{1}\oplus b(\omega_{2_{1}})-s_{2_{1}}-s_{2_{2}}-b(\omega_{2_{2}})-m_{2}\oplus$
$P=\{P_{1},P_{2},\dots,P_{R}\}$
$\varphi=<q_{i_1},s_{i_{1}},s_{i_{2}},\omega_{i_{2}},m_{i}>$

volendo si possono sostituire i separatori con caratteri numerici
$T\to\rho_{T}=b(\omega_{0})2b(\omega_{A})2b(\omega_{R})3 b(\omega_{1_{1}})2s_{1_{1}}2s_{1_{2}}2b(\omega_{1_{2}})2\{5,6,7\}4 b(\omega_{2_{1}})2s_{2_{1}}2s_{2_{2}}2b(\omega_{2_{2}})2\{5,6,7\}4$
$2=-;\quad 3=\otimes;\quad 4=\oplus;\quad\{5,6,7\}=\{S,F,D\};\quad8=\Box$

In questo modo ad ogni parola composta ho un numero diverso:
esempio
0011 e' una parola binaria
011
11
ma scritti cosi sono tutti uguali, in quanto gli 0 se sono all'inizio li togliamo, quindi mettiamo un 9 davanti
per non confonderle con altre macchine di Turing mettiamo un 9 all'inizio che identifica il linguaggio:
90011
9011
911

Quindi ad ogni $T\to n$ e quindi $T$ sono tante i numeri $\mathbb{N}$
$h_{1}$ sara il modo di chiamare il numero che rappresenta la prima macchina di Turing $h_{2},h_{3},\dots$ e cosi via:

$$(T_{h_{i}},x_{j})=\begin{cases}
1 & \text{se }T_{h_{i}}(x_{j})\text{ accetta} \\
0 & \text{altrimenti}
\end{cases}$$

|             | $x_{1}$ | $x_{2}$ | $x_{3}$ | $x_{4}$ | ... |
| ----------- | ------- | ------- | ------- | ------- | --- |
| $T_{h_{1}}$ | 1       | 0       | 0       | 1       | 0   |
| $T_{h_{2}}$ | 0       | 0       | 1       | 0       | 1   |
| $T_{h_{3}}$ | 1       | 0       | 1       | 0       | 0   |
| $T_{h_{4}}$ | 0       | 1       | 0       | 1       | 0   |
| ...         |         |         |         |         |     |

$D=10110\dots$
$\overline{D}=01001\dots$
$\overline{L}=\{x_{2},x_{5}$

$T_{h_{1}}(x_{1})=q_{A}$
$T_{h_{2}}(x_{2})=q_{R}$
$$T_{h_{i}}(x_{i})=\begin{cases}
1 & \text{se }x_{i}\in L_{i} \\
0 & \text{altrimenti}
\end{cases}\quad\quad x_{i}\in\overline{L}\iff x_{i}\notin L_{i}$$
Abbiamo cosi dimostrato che esistono linguaggi non accettabili, lavorando sull'infinito al finito



$L_{H}=\{(i,x)\in \mathbb{N}\times \mathbb{N}:i\text{ e' la codifica di una TM }\ T_{i}\ \text{ e }T_{i}(x)\text{ termina}\}$


THM: $L_{H}$ e' accettabile
$V'$:  con input $(i,x)$
1) verifica se $i$ e' la codifica di una TM: 
   se no $\implies$ rigetta, altrimenti 2)
2) simula $U(i,x)$: se  $o_{U}(i,x)\in\{o_{i_{a}},q_{R}\}\implies$ accetta   $$\begin{array}{}
L_{H}\text{ e' accettabile} \\
 & \implies L_{H}^{c}\text{ non e' accettabile} \\
L_{H}\text{e' non decidibile}
\end{array}$$
