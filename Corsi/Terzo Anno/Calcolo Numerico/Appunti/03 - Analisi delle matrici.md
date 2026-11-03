---
tags:
  - calcolo-numerico
  - analisi-delle-matrici
  - algebra-lineare
slide: []
---
# Analisi delle matrici
## Richiami di algebra lineare
Lezione 8 (29/10/2026): inizio del terzo argomento del corso. Richiami su determinante (metodo di Laplace, teorema di Binet), traccia, autovalori e raggio spettrale, matrici invertibili e calcolo dell'inversa, matrici diagonalizzabili.

Finiti l'interpolazione polinomiale ([[01 - Interpolazione polinomiale]]) e la formula dei trapezi ([[02 - Integrazione numerica]]), il terzo argomento è l'**analisi delle matrici**. Da una parte è propedeutico all'ultimo argomento del corso, la **risoluzione dei sistemi lineari con metodi iterativi**; dall'altra ha un interesse proprio, e occuperà qualche lezione. Questa prima lezione è fatta di richiami di algebra lineare che in gran parte si dovrebbero già sapere, con qualche cosa nuova (il raggio spettrale, la dimostrazione sulle matrici diagonalizzabili).

> [!info] $\mathbb{C}^{n\times n}$ contiene anche le matrici reali
> Con $A\in\mathbb{C}^{n\times n}$ si intendono le matrici $n\times n$ con componenti complesse, che però **possono essere anche tutte reali**, perché $\mathbb{R}\subset\mathbb{C}$. Il "contenitore" $\mathbb{C}^{n\times n}$ contiene tutte le matrici a componenti reali più quelle con alcune o tutte le componenti complesse: i risultati enunciati per $\mathbb{C}^{n\times n}$ valgono anche per le matrici reali.
### Calcolo dei determinanti
Il docente lo ripassa perché all'esame capita che i determinanti vengano sbagliati. Propone il **metodo di Laplace**, quello classico; all'esame si può usare quello che si vuole (ad esempio la regola di Sarrus per le $3\times3$).
#### Metodo di Laplace
1. Si sceglie una riga oppure una colonna di $A$.
2. Si sviluppa il determinante lungo quella riga o colonna: ogni elemento si moltiplica per il **sottodeterminante** che si ottiene cancellando la riga e la colonna dell'elemento, con il segno dato dalla **regola della scacchiera**.

La regola della scacchiera è la fonte principale di errori: si parte con un $+$ nell'angolo in alto a sinistra e si alternano i segni come le caselle di una scacchiera. Per una $3\times3$:
$$\begin{bmatrix}+&-&+\\-&+&-\\+&-&+\end{bmatrix}$$
In formule, il segno dell'elemento in riga $i$ e colonna $j$ è $(-1)^{i+j}$.

> [!example] Esempio
> Calcolare il determinante di
> $$A=\begin{bmatrix}1&3&2\\0&1&4\\2&5&10\end{bmatrix}$$

Scegliendo la **prima riga** (segni $+,-,+$):
$$\det(A)=+1\begin{vmatrix}1&4\\5&10\end{vmatrix}-3\begin{vmatrix}0&4\\2&10\end{vmatrix}+2\begin{vmatrix}0&1\\2&5\end{vmatrix}=1\cdot(10-20)-3\cdot(0-8)+2\cdot(0-2)=-10+24-4=10$$
Scegliendo la **seconda colonna** (segni $-,+,-$, quindi stavolta si parte con un meno):
$$\det(A)=-3\begin{vmatrix}0&4\\2&10\end{vmatrix}+1\begin{vmatrix}1&2\\2&10\end{vmatrix}-5\begin{vmatrix}1&2\\0&4\end{vmatrix}=24+6-20=10$$
Il risultato non cambia: si può scegliere la riga o la colonna che si vuole, purché si stia attenti ai segni. Conviene scegliere quella con più zeri.
#### Teorema di Binet e determinante della trasposta
> [!quote] Teorema di Binet
> Date due matrici $A,B\in\mathbb{C}^{n\times n}$,
> $$\det(AB)=\det(A)\det(B)$$

> [!quote] Proposizione
> Data $A\in\mathbb{C}^{n\times n}$,
> $$\det(A^T)=\det(A)$$

Si chiama proposizione perché è più semplice da dimostrare, ma non si dimostra: l'idea è che sviluppare con Laplace $\det(A^T)$ lungo la prima riga equivale a sviluppare $\det(A)$ lungo la prima colonna.

> [!example] Esempio
> Sia $\alpha\in\mathbb{R}$ e sia $U=\begin{bmatrix}2&\alpha\\1&3\end{bmatrix}$. Stabilire per quali valori di $\alpha$ la matrice $A=LU$ ha determinante nullo nei seguenti due casi:
> - $L=\begin{bmatrix}1&-3\\-4&12\end{bmatrix}$;
> - $L=\begin{bmatrix}1&0\\5&2\end{bmatrix}$.

$A$ è un prodotto, quindi per il teorema di Binet in entrambi i casi
$$\det(A)=\det(L)\det(U)=\det(L)\,(6-\alpha)$$
- Nel primo caso $\det(L)=12-(-3)(-4)=0$, quindi $\det(A)=0$ per ogni $\alpha\in\mathbb{R}$.
- Nel secondo caso $\det(L)=2\neq0$, quindi $\det(A)=0\iff\alpha=6$.

Non serve calcolare il prodotto $LU$.
### Traccia, determinante, raggio spettrale e autovalori
Una matrice $A\in\mathbb{C}^{n\times n}$ ha sempre **esattamente $n$ autovalori**, se ciascuno si conta con la sua molteplicità algebrica. Gli autovalori sono le radici del polinomio caratteristico, che ha grado $n$ e quindi $n$ radici, eventualmente coincidenti.

Sia dunque $A\in\mathbb{C}^{n\times n}$ con autovalori $\lambda_1,\dots,\lambda_n$, ciascuno dei quali compare in questa sequenza un numero di volte pari alla sua molteplicità algebrica come radice del polinomio caratteristico di $A$. Si ha:
$$\operatorname{traccia}(A)\overset{\text{def}}{=}a_{11}+a_{22}+\dots+a_{nn}=\lambda_1+\lambda_2+\dots+\lambda_n$$
$$\det(A)=\lambda_1\lambda_2\cdots\lambda_n$$
$$\rho(A)\overset{\text{def}}{=}\text{raggio spettrale di }A\overset{\text{def}}{=}\max\big(|\lambda_1|,|\lambda_2|,\dots,|\lambda_n|\big)$$
- La **traccia** è per definizione la somma degli elementi diagonali; che sia anche la somma degli autovalori è un **teorema** (non dimostrato).
- Che il determinante sia il prodotto degli autovalori è anch'esso un teorema: il determinante si definisce e si calcola in un altro modo (ad esempio con Laplace).
- Il **raggio spettrale** è una nozione nuova, molto importante per il seguito del corso. Lo **spettro** di $A$ è invece l'insieme dei suoi autovalori.

> [!warning] $\rho$ non è $p$
> Il raggio spettrale si indica con la lettera greca **rho**, $\rho$ (una "r" greca: r come raggio), più rotonda della $p$. Il docente trova spesso la $p$ nei compiti.

**Interpretazione.** Il modulo di un numero complesso è la sua **distanza dall'origine** nel piano complesso, e si calcola con il teorema di Pitagora:
$$|a+ib|=\sqrt{a^2+b^2}$$
Alla lavagna c'è il disegno con $n=3$: $\lambda_1$ reale negativo, $\lambda_2$ reale positivo e $\lambda_3=3+4i$, il più lontano dall'origine. Il cerchio centrato nell'origine e di raggio $|\lambda_3|$ contiene tutti gli autovalori, e
$$\rho(A)=|\lambda_3|=\sqrt{3^2+4^2}=\sqrt{25}=5$$
Il raggio spettrale è il raggio del più piccolo cerchio centrato nell'origine che contiene tutti gli autovalori.

> [!warning] Il modulo, non l'autovalore
> In questo esempio $\rho(A)$ è $|\lambda_3|=5$, **non** $\lambda_3$: $\lambda_3$ è un numero complesso, mentre il raggio spettrale è un numero reale $\geq0$.
#### Esempio: autovalori dalla traccia
> [!example] Esempio
> Sia
> $$A=\begin{bmatrix}2&4&-1&0\\0&1+i&0&7\\1&-1&1&-2i\\3&-1&0&-12\end{bmatrix}$$
> - (i) Dimostrare che $A$ possiede almeno un autovalore $\lambda$ non reale (cioè tale che $\operatorname{Im}(\lambda)\neq0$).
> - (ii) Dimostrare che $A$ possiede almeno un autovalore $\mu$ con parte reale minore o uguale a $-2$ (cioè tale che $\operatorname{Re}(\mu)\leq-2$).

Il docente aveva inizialmente copiato male l'ultimo elemento diagonale ($12$ invece di $-12$) e lo corregge. L'esercizio si risolve con la traccia, senza calcolare gli autovalori:
$$\operatorname{traccia}(A)=2+(1+i)+1+(-12)=-8+i$$
**(i)** La traccia $-8+i$ non è reale. Siccome $\operatorname{traccia}(A)=\lambda_1+\lambda_2+\lambda_3+\lambda_4$ è la somma degli autovalori, deve per forza esistere un autovalore $\lambda$ non reale di $A$: se tutti gli autovalori fossero reali, anche la loro somma sarebbe reale.

Gli autovalori sono $4$ perché la matrice è $4\times4$; nella somma un autovalore ripetuto va contato tante volte quanto la sua molteplicità.

**(ii)** Si usano due proprietà dei numeri complessi: per ogni $\alpha,\beta\in\mathbb{C}$
$$\operatorname{Re}(\alpha+\beta)=\operatorname{Re}(\alpha)+\operatorname{Re}(\beta),\qquad\operatorname{Im}(\alpha+\beta)=\operatorname{Im}(\alpha)+\operatorname{Im}(\beta)$$
Infatti, scrivendo $\alpha=a+ib$ e $\beta=c+id$, si ha $\alpha+\beta=(a+c)+i(b+d)$.

Supponiamo **per assurdo** che non esista $\mu$ autovalore di $A$ con $\operatorname{Re}(\mu)\leq-2$. Allora
$$\operatorname{Re}(\lambda_1),\operatorname{Re}(\lambda_2),\operatorname{Re}(\lambda_3),\operatorname{Re}(\lambda_4)>-2$$
e quindi
$$\operatorname{Re}\big(\operatorname{traccia}(A)\big)=\operatorname{Re}(\lambda_1+\lambda_2+\lambda_3+\lambda_4)=\operatorname{Re}(\lambda_1)+\operatorname{Re}(\lambda_2)+\operatorname{Re}(\lambda_3)+\operatorname{Re}(\lambda_4)>(-2)+(-2)+(-2)+(-2)=-8$$
Questo è assurdo, perché $\operatorname{Re}(\operatorname{traccia}(A))=-8$ esattamente. L'assurdo proviene dall'aver supposto che non esistesse $\mu$ autovalore di $A$ con $\operatorname{Re}(\mu)\leq-2$; dunque un tale $\mu$ deve esistere. $\blacksquare$

Il $-2$ non è casuale: è $\frac{-8}{4}$, la parte reale della traccia divisa per il numero di autovalori. Almeno un autovalore deve avere parte reale non più grande della **media** delle parti reali.

> [!info] Il verso della disuguaglianza
> Lo stesso ragionamento applicato alla parte immaginaria, $\operatorname{Im}(\operatorname{traccia}(A))=1$ (attenzione: la parte immaginaria è $1$, non $i$), dice che esiste almeno un autovalore con $\operatorname{Im}(\lambda)\geq\frac14$. Il verso si **rovescia** ($\geq$ invece di $\leq$) perché ora si ragiona sul massimo: se tutte le parti immaginarie fossero $<\frac14$, la loro somma sarebbe $<1$. È un'informazione più forte del punto (i): non solo esiste un autovalore non reale, ma la sua parte immaginaria è "di una certa consistenza". È lasciato come esercizio.

> [!info] Verifica numerica
> Calcolati al calcolatore (non a lezione), gli autovalori di $A$ sono circa $-10{,}887-0{,}063i$, $3{,}561+0{,}456i$, $-1{,}448+0{,}802i$ e $0{,}773-0{,}196i$: la somma è $-8+i$, quello con parte reale $\leq-2$ è il primo e quello con parte immaginaria $\geq\frac14$ è il terzo (anche il secondo).

> [!warning] Operazioni di Gauss e autovalori
> Uno studente chiede se la somma degli elementi diagonali resta la stessa dopo le operazioni sulle righe che portano la matrice in forma a scala. **No**: le operazioni dell'eliminazione di Gauss possono cambiare gli autovalori, e quindi la traccia. Il docente aggiunge che lasciano invariato il determinante; questo vale per le operazioni del tipo "a una riga si somma un multiplo di un'altra", mentre scambiare due righe cambia il segno del determinante e moltiplicare una riga per $c$ lo moltiplica per $c$. Esistono invece trasformazioni (di **Householder**, di **Givens**) che lasciano invariati gli autovalori: fanno parte dell'analisi numerica ma non c'è tempo per vederle nel corso.
#### Esercizi
**Esercizio** (dalla lezione). Usando lo stesso ragionamento del punto (ii), dimostrare che la matrice $A$ dell'esempio ha almeno un autovalore $\lambda$ con $\operatorname{Im}(\lambda)\geq\frac14$.

**Esercizio 3.1.** Si considerino le matrici
$$A=\begin{bmatrix}\frac{\sqrt3}{2}&0&-\frac12\\0&1&0\\\frac12&0&\frac{\sqrt3}{2}\end{bmatrix},\qquad B=\begin{bmatrix}1&-2&5&10\\0&-3&-7&0\\0&0&2&1\\0&0&0&5\end{bmatrix}$$
- (i) Calcolare gli autovalori di $A$ e $B$.
- (ii) Verificare che per $B$, come avviene per ogni matrice triangolare, gli autovalori sono gli elementi diagonali.
- (iii) Calcolare la traccia, il determinante e il raggio spettrale di $A$ e $B$.
- (iv) Verificare che sia per $A$ che per $B$ la somma degli autovalori è uguale alla traccia e il prodotto degli autovalori è uguale al determinante.

Il messaggio del punto (ii), importante al di là dell'esercizio: **gli autovalori di una matrice triangolare** (superiore o inferiore, quindi anche diagonale) **sono i suoi elementi diagonali**; per $B$ sono $1,-3,2,5$. Il punto (iv) è una verifica dei due teoremi su un caso particolare.
### Matrici invertibili
> [!quote] Definizione (matrice invertibile)
> Una matrice $A\in\mathbb{C}^{n\times n}$ si dice **invertibile** se esiste una matrice $B\in\mathbb{C}^{n\times n}$ tale che
> $$AB=BA=I$$
> dove $I$ è la matrice identità (uni sulla diagonale, zeri fuori). In tal caso la matrice $B$ è univocamente determinata, si chiama **inversa** di $A$ e si denota con $A^{-1}$.

Si ricorda che, per $A\in\mathbb{C}^{n\times n}$:
$$A\text{ è invertibile}\iff\det(A)\neq0\iff0\text{ non è un autovalore di }A$$
La seconda equivalenza viene da $\det(A)=\lambda_1\cdots\lambda_n$: il prodotto è nullo se e solo se uno degli autovalori è nullo. Altre condizioni equivalenti, ricordate dagli studenti: le righe (o le colonne) di $A$ sono linearmente indipendenti; $A$ ha rango $n$.

> [!warning] Invertibile non è diagonalizzabile
> Uno studente propone come condizione "gli autovalori sono tutti diversi". Ma avere autovalori **distinti tra loro** è una condizione sufficiente per la **diagonalizzabilità** ([[03 - Analisi delle matrici#Richiami di algebra lineare#Matrici diagonalizzabili]]), non per l'invertibilità. Per essere invertibile basta che gli autovalori siano tutti **diversi da $0$**, e possono anche essere tutti uguali: la matrice identità ha l'autovalore $1$ ripetuto $n$ volte (è diagonale, quindi i suoi autovalori sono gli elementi diagonali) ed è invertibile, con determinante $1$.

> [!quote] Proposizione (inversa del prodotto)
> Date $A,B\in\mathbb{C}^{n\times n}$, il prodotto $AB$ è invertibile se e solo se $A$ e $B$ sono entrambe invertibili. In tal caso
> $$(AB)^{-1}=B^{-1}A^{-1}$$

La prima parte si dimostra con il teorema di Binet: $\det(AB)=\det(A)\det(B)$ è diverso da $0$ se e solo se lo sono entrambi i fattori. Per la formula dell'inversa (le inverse dei singoli fattori, **in ordine scambiato**) basta verificare la definizione in entrambi i versi:
$$(B^{-1}A^{-1})(AB)=B^{-1}(A^{-1}A)B=B^{-1}IB=B^{-1}B=I$$
$$(AB)(B^{-1}A^{-1})=A(BB^{-1})A^{-1}=AIA^{-1}=AA^{-1}=I$$
Moltiplicare per l'identità non cambia la matrice: è l'elemento neutro del prodotto, come $1$ per i numeri.
#### Calcolo dell'inversa
> [!example] Esempio
> Verificare che
> $$A=\begin{bmatrix}1&2&-1\\-2&1&1\\1&0&4\end{bmatrix}$$
> è invertibile e calcolarne l'inversa.

**Invertibilità.** Si sviluppa il determinante lungo l'**ultima riga**, che contiene uno zero (segni $+,-,+$):
$$\det(A)=+1\begin{vmatrix}2&-1\\1&1\end{vmatrix}-0\begin{vmatrix}1&-1\\-2&1\end{vmatrix}+4\begin{vmatrix}1&2\\-2&1\end{vmatrix}=3+4\cdot5=23\neq0$$
quindi $A$ è invertibile.

**Inversa.** Il procedimento mostrato a lezione:
1. si scrive $\frac{1}{\det(A)}$ davanti a tutto;
2. si predispone una matrice $3\times3$ i cui elementi sono **nove determinanti** $3\times3$;
3. nei determinanti della **riga $i$** si sostituisce la **colonna $i$** di $A$ con i vettori della base canonica, che "scorrono" lungo la riga: $e_1=(1,0,0)^T$ nel primo, $e_2=(0,1,0)^T$ nel secondo, $e_3=(0,0,1)^T$ nel terzo; le altre colonne si ricopiano da $A$;
4. ciascun determinante si sviluppa lungo la colonna sostituita, che ha un solo elemento non nullo: resta un solo sottodeterminante $2\times2$, con il segno della scacchiera.

In formule, l'elemento di posto $(i,j)$ di $A^{-1}$ è
$$\left(A^{-1}\right)_{ij}=\frac{\det\big(A\text{ con la colonna }i\text{ sostituita da }e_j\big)}{\det(A)}$$
Ad esempio i primi due elementi della prima riga:
$$\begin{vmatrix}1&2&-1\\0&1&1\\0&0&4\end{vmatrix}=+1\cdot\begin{vmatrix}1&1\\0&4\end{vmatrix}=4,\qquad\begin{vmatrix}0&2&-1\\1&1&1\\0&0&4\end{vmatrix}=-1\cdot\begin{vmatrix}2&-1\\0&4\end{vmatrix}=-8$$
Gli altri sette, calcolati a turno dagli studenti, danno
$$A^{-1}=\frac{1}{23}\begin{bmatrix}4&-8&3\\9&5&1\\-1&2&5\end{bmatrix}$$
(risultato ricontrollato al calcolatore).

> [!warning] I segni
> Anche qui l'errore tipico è il segno: va preso dalla scacchiera **partendo dall'angolo in alto a sinistra con un $+$**, nella posizione dell'unico $1$ della colonna sostituita. Uno studente sbaglia proprio così.

Questo metodo si chiama **metodo dei cofattori**: viene dalla regola di Cramer per i sistemi lineari (la colonna $j$ di $A^{-1}$ è la soluzione di $Ax=e_j$, e la sua componente $i$ è data da Cramer). Ha il vantaggio di una formula esplicita, ma è meno efficiente dal punto di vista computazionale (nove determinanti).

> [!warning] Gauss–Jordan funziona sempre
> Gli studenti propongono il metodo di **eliminazione di Gauss–Jordan**, più efficiente. Il docente obietta che "non sempre funziona", perché a un certo punto si può incontrare un **pivot nullo**, e dice che si informerà. In realtà, come osservano gli studenti, il problema si risolve **scambiando le righe**: se $A$ è invertibile, nella colonna corrente sotto la diagonale c'è sempre un elemento non nullo da portare in posizione di pivot (altrimenti le colonne sarebbero linearmente dipendenti). Gli scambi di righe si applicano anche alla matrice identità affiancata, quindi alla fine non c'è nulla da ripermutare e si ottiene esattamente $A^{-1}$: il metodo è deterministico e non probabilistico. All'esame lo si può usare; il docente consiglia comunque di esercitarsi anche sul metodo dei cofattori.
#### Esercizio
**Esercizio 3.2.** Stabilire quali delle seguenti matrici sono invertibili e calcolarne l'inversa:
$$A=\begin{bmatrix}1&2&3\\-1&-2&0\\0&1&1\end{bmatrix},\qquad B=\begin{bmatrix}-2&4&1\\-1&2&7\\1&0&-1\end{bmatrix},\qquad C=\begin{bmatrix}1&4&2&0\\-1&2&1&-1\\-1&-3&-3&2\\-1&3&0&1\end{bmatrix}$$
### Matrici diagonalizzabili
Prima un richiamo, sotto forma di domanda ("da un euro").

> [!quote] Definizione (autovalore e autovettore)
> Data $A\in\mathbb{C}^{n\times n}$, $\lambda$ è un **autovalore** di $A$ con **autovettore** corrispondente $u\in\mathbb{C}^n$, $u\neq0$, se
> $$Au=\lambda u$$

Che $\lambda$ sia radice del polinomio caratteristico è una caratterizzazione, non la definizione. L'autovettore deve essere **diverso dal vettore nullo**: siccome $A\,0=0=\lambda\,0$ per ogni $\lambda$, altrimenti il vettore nullo sarebbe autovettore di qualsiasi numero.

> [!quote] Definizione (matrice diagonalizzabile)
> Data $A\in\mathbb{C}^{n\times n}$, si dice che $A$ è **diagonalizzabile** se esistono una matrice invertibile $X\in\mathbb{C}^{n\times n}$ e una matrice diagonale $D\in\mathbb{C}^{n\times n}$ tali che
> $$A=XDX^{-1}\tag{$\star$}$$

La scrittura $(\star)$ sembra non avere niente a che fare con autovalori e autovettori, ma in realtà contiene tutto. A lezione il docente pensava fosse un ripasso, ma la classe non l'aveva vista, e la dimostra per la prima volta.

> [!quote] Proposizione
> Nella $(\star)$ c'è scritto che, per ogni $i=1,\dots,n$, l'elemento diagonale $i$-esimo di $D$, chiamiamolo $\lambda_i$,
> $$D=\begin{bmatrix}\lambda_1&&&\\&\lambda_2&&\\&&\ddots&\\&&&\lambda_n\end{bmatrix}$$
> è un **autovalore** di $A$ con corrispondente **autovettore** $x_i=$ $i$-esima colonna di $X$.

Gli elementi diagonali vengono chiamati $\lambda_i$ invece di $d_i$ perché il nome richiama già quello che si vuole dimostrare.
#### Dimostrazione
Si moltiplicano entrambi i membri della $(\star)$ **a destra** per $X$, in modo da "mangiarsi" $X^{-1}$: $XDX^{-1}X=XDI=XD$, quindi
$$AX=XD$$
Si fissa ora $1\leq i\leq n$ (per fissare le idee, $i=1$) e si confrontano le colonne $i$ dei due membri. Si indica con $M^{(i)}$ la colonna $i$ di una matrice $M$.

**La colonna $i$ di $AX$.** Nel prodotto righe per colonne, la colonna $i$ del risultato si ottiene moltiplicando ciascuna riga di $A$ per la colonna $i$ di $X$. Con $n=3$ e $i=1$: il primo elemento è la prima riga di $A$ per la prima colonna di $X$, il secondo la seconda riga per la prima colonna, il terzo la terza riga per la prima colonna. Quindi
$$(AX)^{(i)}\overset{\text{def}}{=}\text{colonna }i\text{ di }AX=A\,X^{(i)}=A\,x_i$$
**La colonna $i$ di $XD$.** Allo stesso modo $(XD)^{(i)}=X\,D^{(i)}$. Ma la colonna $i$ di $D$ ha tutti zeri tranne $\lambda_i$ in posizione $i$; con $i=1$:
$$X\,D^{(1)}=\begin{bmatrix}x_{11}&x_{12}&x_{13}\\x_{21}&x_{22}&x_{23}\\x_{31}&x_{32}&x_{33}\end{bmatrix}\begin{bmatrix}\lambda_1\\0\\0\end{bmatrix}=\begin{bmatrix}\lambda_1x_{11}\\\lambda_1x_{21}\\\lambda_1x_{31}\end{bmatrix}=\lambda_1x_1$$
e in generale $(XD)^{(i)}=\lambda_ix_i$.

Siccome $AX=XD$, le colonne $i$ sono uguali:
$$Ax_i=\lambda_ix_i\qquad\forall i=1,\dots,n$$
cioè, per ogni $i=1,\dots,n$, $\lambda_i$ è un autovalore di $A$ con autovettore $x_i$. $\blacksquare$

> [!info] Il passaggio mancante: $x_i\neq0$
> Per la definizione di autovettore serve anche $x_i\neq0$, che a lezione non è stato detto esplicitamente. Vale perché $X$ è **invertibile**: una matrice con una colonna nulla ha determinante nullo (basta sviluppare con Laplace lungo quella colonna), quindi nessuna colonna di $X$ è nulla.

> [!question] Domanda tipica d'esame
> Dare la definizione di matrice diagonalizzabile e dimostrare che, se $A=XDX^{-1}$ con $X$ invertibile e $D$ diagonale, gli elementi diagonali di $D$ sono autovalori di $A$ con autovettori le colonne di $X$. Traccia: moltiplicare a destra per $X$ e ottenere $AX=XD$; la colonna $i$ di $AX$ è $Ax_i$, la colonna $i$ di $XD$ è $\lambda_ix_i$; confrontare le colonne; $x_i\neq0$ perché $X$ è invertibile.

> [!question] Domanda tipica d'esame
> Definire traccia e raggio spettrale di una matrice e dire come sono legati traccia e determinante agli autovalori. Usare la traccia per mostrare che una matrice data ha un autovalore non reale, o un autovalore con parte reale $\leq c$. Traccia: traccia = somma degli elementi diagonali = somma degli autovalori; $\det$ = prodotto degli autovalori; $\rho(A)=\max_i|\lambda_i|$; ragionamento per assurdo sulla parte reale (o immaginaria) della somma.

La lezione finisce qui, un quarto d'ora prima del solito, perché il giovedì dopo c'è un'altra lezione. Le **matrici hermitiane**, che il docente voleva cominciare, slittano alla lezione successiva. Il docente propone, come regola, di sforare un po' il martedì per recuperare il tempo perso il giovedì.
