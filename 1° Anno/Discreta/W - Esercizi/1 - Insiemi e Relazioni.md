## Es. 10
Siano $A$,$B$,$C$ insiemi $$A\times(B\ \cup C)=(A \times B)\cup (A\times C)\quad?$$Dimostrazione
Sia $(x,y)\in A\times(B\ \cup C)\implies x\in A$ e $y\in (B\cup C)$.
	se $y\in B\implies(x,y)\in (A\times B)\implies(x,y)\in(A\times B)\cup(A\times C)$
	se $y\in C\implies(x,y)\in (A\times C)\implies(x,y)\in(A\times B)\cup(A\times C)$
Viceversa
Sia $(x,y)\in(A\times B)\cup(A\times C)\implies$ o $(x,y)\in (A\times B)$ o $(x,y)\in(A\times C)$
	se $(x,y)\in (A\times B)\implies x\in A$ e $y\in B\implies y\in (B\cup C)\implies(x,y)\in A\times(B\cup C)$
	se $(x,y)\in (A\times C)\implies x\in A$ e $y\in C\implies y\in (B\cup C)\implies(x,y)\in A\times(B\cup C)\Box$

## Es. 11
Quante $f:[3]\rightarrow[4]$ ci sono che sono iniettive?

Sia $f:[3]\rightarrow[4]$ allora ci sono 4 possibilità per $f(1)$;
quindi ci sono 3 possibilità per $f(2)$ (perché $f(1)\not=f(2)$);
quindi ci sono 2 possibilità per $f(3)$ (perché $f(3)\not=f(1)$ e $f(3)\not=f(2)$).

Pertanto in totale ci sono $4\times 3\times 2=24$ tali funzioni $f$.

## Es. 12
Siano $A$,$B$,$C$ insiemi, $C\subseteq A$.  $$(A\cap B)\cup C=A\cap(B\cup C)\quad?$$Dimostrazione
Sia $x\in(A\cap B)\cup C\implies$ o $x \in (A\cap B)$ o $x\in C$
	se $x\in (A\cap B)\implies x\in A$ e $x\in B\implies x\in A$ e $c\in (B\cup C)\implies x\in A\cap(B\cup C)$
	se $x\in C\implies x\in(B\cup C)\overset{C\subseteq A}{\implies}x\in A\cap(B\cup C)$
Viceversa
Sia $x\in A\cup (B\cap C)\implies$ $x \in A$ e $x\in (B\cup C)\implies$ o $x\in B$ o $x\in C$
	se $x\in B\implies x\in (A\cap B)\implies x\in (A\cap B)\cup C$
	se $x\in C\implies x\in(A\cap B)\cup C\quad\Box$

Osservazione
Non si usa $C\subseteq A$ nel viceversa

## Es.13
Sia $R$ una relazione su $\mathbb{Z}$ tale che $$mRn\Leftrightarrow \begin{array}{}
m=n \\ \text{o} \\ m+n=5
\end{array}\quad \forall m,n\in\mathbb{Z}$$
é una relazione di equivalenza (riflessiva, simmetrica e transitiva)? 

Riflessiva
Sia $m\in \mathbb{Z}\implies m=m\implies mRm$

Simmetrica
Sia $m,n \in \mathbb{Z}$ tali che $mRn\implies$ o $m=n$ o $m+n=5$
	se $m=n\implies n=m\implies nRm$
	se $m+n=5\implies n+m=5\implies nRm$

Transitiva
Sia $a,b,c \in \mathbb{Z}$ e sia $aRb,bRc$ allora ($a=b$  o  $a+b=5$) e ($b=c$  o  $b+c=5$)
	se $a=b$ e $b=c\implies a=c\implies aRc$
	se $a=b$ e $b+c=5\implies a+c=5\implies aRc$
	se $a+b=5$ e $b=c\implies a+c=5\implies aRc$
	se $a+b=5$ e $b+c=5\implies a=5-b$ e $c=5-b\implies a=c\implies aRc$

Quindi R é di equivalenza. $\Box$

Quali sono le classi di equivalenza?

Sia $a\in \mathbb{Z}$ allora 
$[a]_{R}=\{b\in\mathbb{Z}:aRb\}=\{b\in\mathbb{Z}:a=b \text{ o } a+b=5\}=\{a,5-a\}$
quindi
$[a]_{R}=\{a,5-a\}\quad\forall a\in \mathbb{Z}$ 
($\implies[14]_{R}=\{14,-9\}etc\dots$)

## Es. 14
Sia $R$ una relazione su $\mathbb{Z}\times(\mathbb{Z}\setminus\{0\})$ definita ponendo $$(a,b)R(c,d)\Leftrightarrow a\cdot d=b\cdot c\quad\quad\forall (a,b),(c,d)\in\mathbb{Z}\times\mathbb{Z}^{*}$$é una relazione di equivalenza?

Riflessiva
Sia $(a,b)\in\mathbb{Z}\times\mathbb{Z}^{*}\implies a\cdot b=a\cdot b\implies(a,b)R(a,b)$

Simmetrica
Sia $(a,b),(c,d)\in\mathbb{Z}\times\mathbb{Z}^{*}$ tali che 
$(a,b)R(c,d)\implies a\cdot d=b\cdot c\implies c\cdot b=a\cdot d\implies(c,d)R(a,b)$

Transitiva
Sia $(a,b),(c,d),(e,f)\in\mathbb{Z}\times\mathbb{Z}^{*}$ tali che 
$(a,b)R(c,d),(c,d)R(e,f)\implies a\cdot d=b\cdot c$  e  $c\cdot f=d\cdot e\implies a\cdot d\cdot f=b\cdot c\cdot f$  e  $b\cdot c\cdot f=b\cdot d\cdot e\implies a\cdot d\cdot f=b\cdot d\cdot e$  ma $d\not=0 (\text{ in }\mathbb{Z}^{*})\implies a\cdot f=b\cdot e\implies(a,b)R(e,f)$

Quindi é una relazione di equivalenza $\Box$