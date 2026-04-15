###### Esercizio svolto
Sia $A=[5],\quad B=[4]$ e sia 
$$f=\{(1,4),(2,1),(3,4),(4,2),(5,3)\}$$
$f$ è una funzione? è suriettiva? è iniettiva?
- è una funzione
- è suriettiva (ogni elemento di $B$ appare almeno una volta)
- NON è iniettiva (c'è qualche elemento di B che appare 2 volte)

###### Esercizio Svolto
$f(1)=4\quad f(2)=2\quad f(3)=1\quad f(4)=5\quad f(5)=2\quad$
$g(1)=4\quad g(2)=3\quad g(3)=5\quad g(4)=2\quad g(5)=1$

$f\circ g$ è iniettiva? è suriettiva?
$g\circ f$ è iniettiva? è suriettiva?
$$\begin{array}{}
	f\circ g\text{ è iniettiva}\\
	f\circ g\text{ è suriettiva}
\end{array}$$
$$\begin{array}{}
g\circ f\text{ non è iniettiva }((g\circ f)(2)=(g\circ f)(5)=3)\\
g\circ f\text{ non è suriettiva }(5\not=(g\circ f)(a))\quad\quad\forall\ a\in[5]
\end{array}$$
###### Esercizio svolto\[insiemi\]
A,B,C insiemi allora $$(B\cap C)\cup(C\cap A)=(A\cup C)\cap B$$
è sempre vero? è sempre falso? è sempre vera se $C\subseteq A$? è sempre vera se $A\subseteq C$?
- Non è sempre FALSO (se $A=B=C\implies$ gli insiemi a sinistra e a destra sono entrambi A)
  Tabella di verità 
  $$\begin{matrix}
	  A&B&C&||&B\cap C&C\cap A&(B\cap C)\cup(C\cap A)&A\cup C&(A\cup B)\cap B\\
	  -&-&-&\dashv\vdash&-&-&-&-&-\\
	  T&T&T&||&T&T&T&T&T\\
	  T&T&F&||&F&F&F&T&T\\
	  T&F&T&||&F&T&T&T&F\\
	  T&F&F&||&F&F&F&T&F\\
	  F&T&T&||&T&F&T&T&T\\
	  F&T&F&||&F&F&F&F&F\\
	  F&F&T&||&F&F&F&T&F\\
	  F&F&F&||&F&F&F&F&F\\
  \end{matrix}$$
- quindi NON è sempre VERO
- impossibile $A\subseteq C$, nelle righe 2 e 4 $\implies$ NON è sempre VERA se $A\subseteq C$
