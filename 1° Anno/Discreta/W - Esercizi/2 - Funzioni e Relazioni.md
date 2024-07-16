## Es. 5
$f: A\rightarrow B,g:B\rightarrow C,f$ suriettiva, $g$ iniettiva 
$g\circ f$ iniettiva? 

Sia $A=[7],B=[5],C=[6]$
$f:A\rightarrow B$ definita
$f(1)=2,f(2)=1,f(3)=1,f(4)=4,f(5)=2,f(6)=3,f(7)=5$

$g:B\rightarrow C$ definita
$g(1)=5,g(2)=1,g(3)=2,g(4)=6,g(5)=4$

allora $f$ é suriettiva e $g$ é iniettiva, ma 
$(g\circ f)(1)=g(f(1))=g(2)=1$
$(g\circ f)(5)=g(f(5))=g(2)=1$
$\implies g\circ f$ non é iniettiva $\implies$ no

## Es.6
$f:A\rightarrow B\quad X,Y\subseteq A$ é vero che 
$f(X)\cap f(Y)=f(X\cap Y)\quad?$

Sia $A[6],B=[5]$ e $f:A\rightarrow B$ definita
$f(1)=2,f(2)=1,f(3)=4,f(4)=2,f(5)=2,f(6)=4$
e
$X=\{1,2,3\},Y=\{3,4,5\}$
allora
$f(X)=\{f(1),f(2),f(3)\}=\{2,1,4\}$
$f(Y)=\{f(3),f(4),f(5)\}=\{4,2\}$
$f(X\cap Y)=\{f(3)\}=\{4\}$
$f(X)\cap f(Y)=\{2,4\}$
$\implies$ No

Dimostriamo che $f(X\cap Y)\subseteq f(X)\cap f(Y)$

Sia $a\in f(X\cap Y)\implies \exists b\in X\cap Y$ tale che $f(b)=a$;
ma $b\in Y\implies f(b)\in f(Y)\implies a\in f(Y) \implies a\in f(X)\cap f(Y)\Box$

## Es. 8
Chi é $(\mathbb{N}\times\mathbb{Z})\cap(\mathbb{Z}\times\mathbb{P})$ ?

Sia $(x,y)\in(\mathbb{N}\times\mathbb{Z})\cap(\mathbb{Z}\times\mathbb{P})\implies(x,y)\in(\mathbb{N}\times \mathbb{Z})$ e $(x,y)\in(\mathbb{Z}\times\mathbb{P})\implies$
$x\in \mathbb{N},y\in\mathbb{Z}$ e $x\in \mathbb{Z},y\in\mathbb{P}\implies x\in\mathbb{N}\cap \mathbb{Z}$ e $y\in \mathbb{Z}\cap \mathbb{P}\implies x\in\mathbb{N}$ e $y\in\mathbb{P}\implies$$(x,y)\in\mathbb{N}\times \mathbb{P}$

Viceversa
Sia $(x,y)\in \mathbb{N}\times \mathbb{P}\implies x\in\mathbb{N}$ e $y\in\mathbb{P}\implies x\in\mathbb{Z}$ e $y\in\mathbb{Z}\implies$
$(x,y)\in \mathbb{N}\times \mathbb{P}$ e $(x,y)\in\mathbb{Z}\times \mathbb{P}\implies (x,y)\in(\mathbb{N}\times \mathbb{Z})\cap(\mathbb{Z}\times \mathbb{P})\Box$

## Es.9
$f:A\rightarrow B,\quad X,Y\subseteq B$ dimostrare che $f^{-1}(X/Y)=f^{-1}(X)/f^{-1}(Y)$

Dimostrazione
Sia $a\in f^{-1}(X/Y)\implies f(a)\in X/Y\implies f(a)\in X$ e $f(a)\notin Y\implies a\in f^{-1}(X)$ e $a\notin f^{-1}(Y)\implies a\in f^{-1}(X)/f^{-1}(Y)$

Viceversa
Sia $a\in f^{-1}(X)/f^{-1}(Y)\implies a\in f^{-1}(X)$ e $a\notin f^{-1}(Y)\implies f(a)\in X$ e $f(a)\notin Y\implies$$f(a)\in X/Y\implies a\in f^{-1}(X/Y)\Box$