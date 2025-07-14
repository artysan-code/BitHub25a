I numeri hanno alla loro fine, come pedice, la base in cui vengono rappresentati
## Bin $\rightarrow$ Dec
Avendo un numero in binario, per esempio $110101111010_{2}$, per convertirlo in decimale bisogna moltiplicare i suoi valori singoli per $2^{\text{posizione del numero}}$ e sommare tutti i valori quindi: $$\begin{array}{c}
1 & 1 & 0 & 1 & 0 & 1 & 1 & 1 & 1 & 0 & 1 & 0 \\
\cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot & \cdot\\
2^{11} & 2^{10} & 2^{9} & 2^{8} & 2^{7} & 2^{6} & 2^{5} & 2^{4} & 2^{3} & 2^{2} & 2^{1} & 2^{0} \\
|| & || & || & || & || & || & || & || & || & || & || & || \\
2048+ & 1024+ & 0+ & 256+ & 0+ & 64+ & 32+ & 16+ & 8+ & 0+ & 2+ & 0 & =3450_{10}
\end{array}$$
## Bin $\rightarrow$ Ott
Avendo un numero in binario, per esempio $0101110101111010_{2}$ 
per convertirlo in ottale bisogna dividere il numero in gruppi da tre a partire da destra $$\begin{array}{c|c}
1\quad0\quad1 & 1\quad1\quad0 & 1\quad0\quad1 & 1\quad1\quad1 & 0\quad1\quad0 \\
\quad\cdot\quad\cdot\quad\cdot\quad & \quad\cdot\quad\cdot\quad\cdot\quad & \quad\cdot\quad\cdot\quad\cdot\quad & \quad\cdot\quad\cdot\quad\cdot\quad & \quad\cdot\quad\cdot\quad\cdot\quad \\
2^2\quad 2^1\quad 2^0 & 2^2\quad 2^1\quad 2^0 & 2^2\quad 2^1\quad 2^0 & 2^2\quad 2^1\quad 2^0 & 2^2\quad 2^1\quad 2^0 \\
||\quad||\quad|| & ||\quad||\quad|| & ||\quad||\quad|| & ||\quad||\quad|| & ||\quad||\quad|| \\
4+0+1 & 4+2+0 & 4+0+1 & 4+2+1 & 0+2+0 \\
|| & || & || & || & || \\
5 & 6 & 5 & 7 & 2
\end{array}$$il risultato è quindi $56572_{8}$ (letto cifra per cifra e non come il numero cinquantasei mila cinquecento settanta due)
## Bin $\rightarrow$ Hex
Prima di poter convertire in esadecimale bisogna aggiungere dei caratteri che rappresentano i valori maggiori di 9 fino a 15. Essi sono :
- A = 10
- B = 11
- C = 12
- D = 13
- E = 14
- F = 15
Per convertire da binario a esadecimale, similmente alla conversione bin $\rightarrow$ ott, bisogna raggruppare il numero a gruppi di 4 cifre partendo da destra, per esempio il numero $110101111010_{2}$ verrebbe convertito nel seguente modo:
$$\begin{array}{c|c}
1\quad1\quad0\quad1 & 0\quad1\quad1\quad1 & 1\quad0\quad1\quad0 \\
\cdot\quad\cdot\quad\cdot\quad\cdot\quad & \cdot\quad\cdot\quad\cdot\quad\cdot\quad & \cdot\quad\cdot\quad\cdot\quad\cdot\quad \\
2^3\quad 2^2\quad 2^1\quad 2^0 & 2^3\quad 2^2\quad 2^1\quad 2^0 & 2^3\quad 2^2\quad 2^1\quad 2^0 \\
||\quad||\quad||\quad|| & ||\quad||\quad||\quad|| & ||\quad||\quad||\quad|| \\
8+4+0+1 & 0+4+2+1 & 8+0+2+0 \\
|| & || & || \\
D & 7 & A \\
\end{array}$$
Il risultato è quindi $D7A_{H}$.
## Ott $\rightarrow$ Bin
Avendo un numero in base ottale, per esempio $56572_{8}$, per portarlo in binario bisogna separare ogni singola cifra e convertirla in binario considerandola come se fosse un numero in decimale:
$$\begin{array}{c|c}
5 & 6 & 5 & 7 & 2 \\
5/2\quad r=1 & 6/2\quad r=0 & 5/2\quad r=1 & 7/2\quad r=1 &2/2\quad r=0  \\
2/2\quad r=0 & 3/2\quad r=1 & 2/2\quad r=0 & 3/2\quad r=1 & 1/2\quad r=1 \\
1/2\quad r=1 & 1/2\quad r=1 & 1/2\quad r=1 & 1/2\quad r=1 & ----- \\
101 &  110 & 101 & 111 & 010 \\
\end{array}$$
dato che ogni cifra dell'ottale equivale a 3 cifre nel binario, nell'ultima colonna non possiamo far scalare il resto del numero altrimenti avremmo un valore diverso quindi completiamo la tripla con uno 0. Il valore finale sarà letto da sinistra a destra: $0101110101111010_{2}$
## Dec $\rightarrow$ Bin
Avendo un numero in decimale, per esempio $3450_{10}$, per convertirlo in binario bisogna dividere il numero per due e considerare il resto dell'operazione: $$\begin{array}{r}
3450\ /\ 2 = 1725 & \text{resto}= 0 \\
1725\ /\ 2 = 862  & \text{resto}= 1 \\
862 \ /\ 2 = 431  & \text{resto}= 0 \\
431 \ /\ 2 = 215  & \text{resto}= 1 \\
215 \ /\ 2 = 107  & \text{resto}= 1 \\
107 \ /\ 2 = 53   & \text{resto}= 1 \\
53  \ /\ 2 = 26   & \text{resto}= 1 \\
26  \ /\ 2 = 13   & \text{resto}= 0 \\
13  \ /\ 2 = 6    & \text{resto}= 1 \\
6   \ /\ 2 = 3    & \text{resto}= 0 \\
3   \ /\ 2 = 1    & \text{resto}= 1 \\
1   \ /\ 2 = 0    & \text{resto}= 1
\end{array}$$Leggendo i resti dal basso verso l'alto otteniamo il valore in binario: $110101111010_{2}$
## Dec $\rightarrow$ Ott
Per convertire da decimale a ottale bisogna prendere il valore decimale e dividerlo per 8 e considerare il resto. Prendiamo in considerazione il numero $3450_{10}$: $$\begin{array}{r l}
3450/8= 431 & \text{resto}=2 \\
431/8= 53 & \text{resto}= 7 \\
53/8= 6 & \text{resto}= 5 \\
6/8= 0 & \text{resto}=6
\end{array}$$
quindi il risultato, letto dal basso verso l'alto, è $6572_{}$
## Hex $\rightarrow$ Bin
Similmente alla conversione ott $\rightarrow$ bin, bisogna considerare cifra per cifra e trovare le sue 4 cifre in binario. Consideriamo il numero $D7A_{H}$
$$\begin{array}{r|r}
D & 7 & A \\
\hline D=13 & 7 & A=10 \\
13/2 \quad r=1 & 7/2 \quad r=1 & 10/2 \quad r=0 \\
6/2 \quad r=0 & 3/2 \quad r=1 & 5/2 \quad r=1 \\
3/2 \quad r=1 & 1/2 \quad r=1 & 2/2 \quad r=0 \\
1/2 \quad r=1 & ----- & 1/2 \quad r=1 \\
1101 & 0111 & 1010
\end{array}$$
Il valore in binario sarà $110101111010_{2}$
## Base n $\rightarrow$ Dec
Per convertire da una qualsiasi base *n* a decimale bisogna moltiplicare cifra per cifra per $n^{\text{posizione del numero}}$ ed infine sommarli. Prendiamo come esempio questo numero $D7A_{H}$ e portiamolo in decimale: $$\begin{array}{c|c}
D & 7 & A \\ 
\hline
D=13 & 7 & A=10 \\
\cdot & \cdot & \cdot \\
16^2 & 16^1 & 16^0 \\
|| & || & || \\
3328+ & 119+ & 10
\end{array}$$
Il risultato della somma è il valore convertito, in questo caso è $3450_{10}$