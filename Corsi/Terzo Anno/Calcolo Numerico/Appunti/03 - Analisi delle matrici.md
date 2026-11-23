---
tags:
  - calcolo-numerico
  - analisi-delle-matrici
  - algebra-lineare
  - gershgorin
  - norme
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
## Matrici hermitiane, definite positive e polinomi di matrici
Lezione 9 (03/11/2026): matrici hermitiane e realtà dei loro autovalori, matrici definite positive (parte reale di una matrice, caratterizzazione per matrici hermitiane con le sottomatrici principali di testa), polinomi di matrici e loro autovalori.

La lezione comincia dall'ultima parte del ripasso di algebra lineare, le **matrici hermitiane**, rimandata dalla lezione precedente per non sforare ([[03 - Analisi delle matrici#Richiami di algebra lineare]]). Il docente osserva che già le matrici hermitiane non sono proprio un ripasso; le **matrici definite positive** sono invece un argomento nuovo, appena accennato nei corsi di algebra lineare.
### Matrici hermitiane
#### Trasposta coniugata
Data $A\in\mathbb{C}^{m\times n}$ (anche rettangolare), si indica con
$$A^*=\text{trasposta coniugata di }A=\overline{A^T}$$
cioè si fa prima la trasposta (la prima riga diventa la prima colonna, la seconda riga la seconda colonna, ...) e poi si coniugano tutti gli elementi.

> [!info] Il coniugato di un numero complesso
> Se $z=a+bi$, il **coniugato** è $\bar z=a-bi$: si cambia segno alla **parte immaginaria**. Nel piano complesso (parte reale in ascissa, parte immaginaria in ordinata) $\bar z$ è il **riflesso** di $z$ rispetto all'asse delle ascisse. Un numero reale coincide con il suo coniugato.

> [!example] Esempio
> $$A=\begin{bmatrix}1&1+3i\\2i&-2+2i\end{bmatrix}$$

Prima la trasposta, poi si coniugano gli elementi ($\bar1=1$, $\overline{2i}=-2i$, $\overline{1+3i}=1-3i$, $\overline{-2+2i}=-2-2i$):
$$A^*=\overline{A^T}=\overline{\begin{bmatrix}1&2i\\1+3i&-2+2i\end{bmatrix}}=\begin{bmatrix}1&-2i\\1-3i&-2-2i\end{bmatrix}$$

> [!quote] Definizione (matrice hermitiana)
> Una matrice $A\in\mathbb{C}^{n\times n}$ si dice **hermitiana** se $A^*=A$.

(Il docente si accorge di non averla scritta solo a metà dei ragionamenti successivi, e la aggiunge: andava data subito dopo aver definito $A^*$.)

> [!quote] Proprietà
> Se $A,B$ sono matrici **moltiplicabili**, allora
> $$(AB)^T=B^TA^T,\qquad(AB)^*=B^*A^*$$

Due matrici sono moltiplicabili (si può fare $AB$) quando il numero di colonne della prima è uguale al numero di righe della seconda. Come per l'inversa del prodotto, l'ordine si **inverte**. La proprietà servirà nella dimostrazione più sotto.

> [!quote] Osservazione
> Se $A\in\mathbb{R}^{m\times n}$, allora $A^*=\overline{A^T}=A^T$.

Il coniugato non fa nulla sui numeri reali: per una matrice reale la stella è semplicemente la trasposta. In particolare una matrice reale è hermitiana se e solo se è **simmetrica** ($A^T=A$).
#### Elementi diagonali e autovalori
> [!quote] Proprietà
> Gli elementi diagonali di una matrice hermitiana sono **reali**, perché sono uguali ai loro complessi coniugati.

Si vede su una $2\times2$: se
$$\begin{bmatrix}a_{11}&a_{12}\\a_{21}&a_{22}\end{bmatrix}\text{ è hermitiana, allora è uguale a }\begin{bmatrix}\overline{a_{11}}&\overline{a_{21}}\\\overline{a_{12}}&\overline{a_{22}}\end{bmatrix}$$
e confrontando la diagonale $a_{11}=\overline{a_{11}}$, $a_{22}=\overline{a_{22}}$. Un numero coincide con il suo riflesso rispetto all'asse delle ascisse solo se sta sull'asse, cioè se è reale.

> [!quote] Proprietà
> Gli **autovalori** di una matrice hermitiana sono **reali**.

È più impegnativa delle precedenti.

**Dimostrazione.** Sia $A\in\mathbb{C}^{n\times n}$ hermitiana e sia $\lambda$ un autovalore **generico** di $A$ (la dimostrazione deve valere per tutti gli autovalori). Prendiamo $x\neq0$ autovettore di $A$ relativo a $\lambda$ (gli autovettori sono sempre diversi dal vettore nullo):
$$Ax=\lambda x$$
**Il trucco.** $Ax$ e $\lambda x$ sono vettori colonna. Li si moltiplica a sinistra per il vettore riga $x^*$: un vettore colonna è una matrice $n\times1$, quindi $x^*$ è il vettore riga con le componenti coniugate di $x$. Vettore riga per vettore colonna dà un **numero**:
$$x^*Ax=x^*(\lambda x)=\lambda\,x^*x=\lambda\sum_{i=1}^n\overline{x_i}\,x_i=\lambda\sum_{i=1}^n|x_i|^2$$
(l'uguaglianza resta vera moltiplicando entrambi i membri per $x^*$; $\lambda$ è uno scalare e si porta fuori).

> [!info] $\bar z z=|z|^2$
> Se $z=a+bi$, allora $\bar zz=(a-bi)(a+bi)=a^2+abi-abi+b^2=a^2+b^2=|z|^2$: il modulo è $\sqrt{a^2+b^2}$, quindi qui c'è il suo **quadrato**.

Si divide per $\sum_{i=1}^n|x_i|^2$ per isolare l'autovalore. Si può, perché questa somma è diversa da $0$: siccome $x\neq0$ almeno una componente $x_i$ è non nulla, e una somma di numeri $\geq0$ con almeno un addendo positivo è positiva. Quindi
$$\lambda=\frac{x^*Ax}{\sum_{i=1}^n|x_i|^2}$$
Il denominatore è reale e $>0$. Resta da dimostrare che il **numeratore** $x^*Ax$ è reale, e lo si fa mostrando che coincide con il suo coniugato (i numeri reali sono esattamente quelli uguali al proprio coniugato):
$$\overline{x^*Ax}=x^*Ax$$
Il numero $x^*Ax$ si può vedere come una **matrice $1\times1$**. Per una matrice $1\times1$ la trasposta non fa niente, quindi la stella si riduce al coniugato. Allora, usando $(AB)^*=B^*A^*$ due volte e $(x^*)^*=x$ (l'operazione stella è **involutoria**: applicata due volte riporta al punto di partenza),
$$\overline{x^*Ax}=\big(x^*(Ax)\big)^*=(Ax)^*(x^*)^*=x^*A^*x=x^*Ax$$
dove l'ultimo passaggio usa l'ipotesi **$A$ hermitiana** ($A^*=A$). È qui, e solo qui, che interviene l'ipotesi: i passaggi precedenti valgono per tutte le matrici.

Dunque $\lambda$ è un rapporto fra due numeri reali, e quindi $\lambda\in\mathbb{R}$. $\blacksquare$

> [!info] Un'idea suggerita da uno studente
> Lo studente Filippo propone di usare direttamente la proprietà $(AB)^*=B^*A^*$; il docente spiega che è proprio quello che si fa, ma per poterla applicare bisogna prima "procurarsi una stella esterna", ed è a questo che serve guardare il numero come matrice $1\times1$.

Fine del ripasso di algebra lineare.
### Matrici definite positive
> [!quote] Definizione (matrice definita positiva)
> Una matrice $A\in\mathbb{C}^{n\times n}$ si dice **definita positiva** se
> $$\operatorname{Re}(x^*Ax)>0\qquad\forall x\in\mathbb{C}^n\setminus\{0\}$$

Il vettore nullo va escluso perché per $x=0$ si ottiene sicuramente $0$. Si noti che la definizione **non** chiede che $A$ sia hermitiana, e usa la **parte reale** di $x^*Ax$, lo stesso numero della dimostrazione precedente.
#### Parte reale e parte immaginaria di una matrice
> [!info] Parte reale e immaginaria di un numero complesso
> Se $z=a+bi$ e $\bar z=a-bi$:
> $$\operatorname{Re}(z)=a=\frac{z+\bar z}{2},\qquad\operatorname{Im}(z)=b=\frac{z-\bar z}{2i},\qquad z=\operatorname{Re}(z)+i\operatorname{Im}(z),\qquad\operatorname{Re}(z),\operatorname{Im}(z)\in\mathbb{R}$$
> ($z-\bar z=2bi$, quindi bisogna dividere per $2i$, non per $2$.)

Notiamo che per ogni $A\in\mathbb{C}^{n\times n}$ e per ogni $x\in\mathbb{C}^n$ (anche $x=0$):
$$\operatorname{Re}(x^*Ax)=\frac{x^*Ax+\overline{x^*Ax}}{2}=\frac{x^*Ax+x^*A^*x}{2}=x^*\left(\frac{A+A^*}{2}\right)x=x^*\operatorname{Re}(A)\,x\tag{eq. rossa}$$
Nel secondo passaggio si usano i passaggi della dimostrazione precedente **che valevano per tutte le matrici**, cioè $\overline{x^*Ax}=x^*A^*x$, fermandosi prima dell'ultimo (qui $A$ non è supposta hermitiana). Poi si raccoglie $x^*$ a sinistra e $x$ a destra; attenzione a non perdere il diviso $2$ (uno studente propone $AA^*$: è $\frac{A+A^*}{2}$).

> [!quote] Definizione (parte reale e parte immaginaria di una matrice)
> Per $A\in\mathbb{C}^{n\times n}$:
> $$\operatorname{Re}(A)=\frac{A+A^*}{2},\qquad\operatorname{Im}(A)=\frac{A-A^*}{2i}$$
> e vale
> $$A=\operatorname{Re}(A)+i\operatorname{Im}(A)$$

I nomi vengono proprio dall'analogia con i numeri: per un numero $\bar z=z^*$ (è una matrice $1\times1$), quindi $\operatorname{Re}(z)=\frac{z+z^*}{2}$. "Il mondo delle matrici si avvicina a quello dei numeri." E come la parte reale e la parte immaginaria di un numero sono **reali**, le parti reale e immaginaria di una matrice sono **hermitiane**: essere hermitiana ($A^*=A$) è il corrispondente, per le matrici, di essere reale ($\bar z=z$).

**Esercizio** (dalla lezione). Dimostrare che per ogni $A\in\mathbb{C}^{n\times n}$, $\operatorname{Re}(A)$ e $\operatorname{Im}(A)$ sono matrici hermitiane. *Suggerimento:* usare la proprietà $(aX)^*=\bar a\,X^*$ per ogni $a\in\mathbb{C}$ e ogni matrice $X$.

> [!info] Traccia della soluzione (nostra aggiunta)
> $\operatorname{Re}(A)^*=\frac{A^*+A^{**}}{2}=\frac{A^*+A}{2}=\operatorname{Re}(A)$; $\operatorname{Im}(A)^*=\overline{\left(\tfrac{1}{2i}\right)}(A-A^*)^*=\frac{1}{-2i}(A^*-A)=\frac{A-A^*}{2i}=\operatorname{Im}(A)$.

**Osservazione 1.** L'eq. rossa dice che per ogni $A\in\mathbb{C}^{n\times n}$ e ogni $x\in\mathbb{C}^n$, il numero $x^*\operatorname{Re}(A)\,x$ è **reale**, perché è uguale a una parte reale. Lo si può vedere anche in un secondo modo: $\operatorname{Re}(A)$ è hermitiana (per l'esercizio), e per una matrice hermitiana $H$ si è visto nella dimostrazione precedente che $x^*Hx$ è reale.

**Osservazione 2** (cruciale). Per ogni matrice $A\in\mathbb{C}^{n\times n}$ vale che
$$\begin{aligned}A\text{ è definita positiva}&\overset{\text{def}}{\iff}\operatorname{Re}(x^*Ax)>0\quad\forall x\in\mathbb{C}^n\setminus\{0\}\\&\overset{\text{eq. rossa}}{\iff}x^*\operatorname{Re}(A)\,x>0\quad\forall x\in\mathbb{C}^n\setminus\{0\}\\&\overset{\text{oss. 1}}{\iff}\operatorname{Re}\big(x^*\operatorname{Re}(A)\,x\big)>0\quad\forall x\in\mathbb{C}^n\setminus\{0\}\\&\overset{\text{def}}{\iff}\operatorname{Re}(A)\text{ è definita positiva}\end{aligned}$$
Il terzo passaggio, quello "finissimo": $x^*\operatorname{Re}(A)\,x$ è reale (oss. 1), quindi coincide con la propria parte reale. L'ultima riga è esattamente la definizione di matrice definita positiva applicata a $\operatorname{Re}(A)$.

> [!quote] Conclusione
> $A\in\mathbb{C}^{n\times n}$ è definita positiva $\iff$ $\operatorname{Re}(A)$ è definita positiva.

Perché è interessante: $A$ può essere una matrice qualsiasi, mentre $\operatorname{Re}(A)$ è **sempre hermitiana**, e fra poco c'è un teorema che stabilisce quando una matrice **hermitiana** è definita positiva.
#### Autovalori di una matrice definita positiva
> [!quote] Proprietà
> Ogni autovalore di una matrice definita positiva ha parte reale **strettamente** positiva. In particolare, ogni matrice definita positiva è **invertibile**, perché non ha lo $0$ fra i suoi autovalori.

Il docente corregge più volte la formulazione: "ogni matrice definita positiva ha autovalori con parte reale positiva" potrebbe far pensare che ne abbia *alcuni* con parte reale positiva, per cui scrive "ogni autovalore". La parte "in particolare" segue da $A$ invertibile $\iff$ $0$ non è autovalore di $A$ ([[03 - Analisi delle matrici#Richiami di algebra lineare#Matrici invertibili]]); uno studente risponde anche con il determinante, prodotto degli autovalori, che non può essere nullo. Basta quindi dimostrare la prima parte.

**Dimostrazione.** Sia $A\in\mathbb{C}^{n\times n}$ definita positiva e sia $\lambda$ un generico autovalore di $A$. Indichiamo con $x\neq0$ un corrispondente autovettore. Esattamente come prima:
$$Ax=\lambda x\implies x^*Ax=x^*(\lambda x)=\lambda\,x^*x=\lambda\sum_{i=1}^n\overline{x_i}\,x_i=\lambda\sum_{i=1}^n|x_i|^2\implies\lambda=\frac{x^*Ax}{\sum_{i=1}^n|x_i|^2}$$
Ora però si deve dimostrare che la **parte reale** di $\lambda$ è positiva, e si prende la parte reale.

> [!info] Parte reale di un quoziente per un reale
> Se $z=\frac{w}{a}$ con $w\in\mathbb{C}$, $a\in\mathbb{R}$, $a\neq0$, allora $\operatorname{Re}(z)=\frac{\operatorname{Re}(w)}{a}$. Infatti, se $w=\alpha+\beta i$,
> $$z=\frac{\alpha+\beta i}{a}=\frac{\alpha}{a}+\frac{\beta}{a}i$$
> con $\frac{\alpha}{a}=\operatorname{Re}(z)$ e $\frac{\beta}{a}=\operatorname{Im}(z)$, entrambi reali.

Siccome il denominatore è un numero reale (addirittura positivo):
$$\operatorname{Re}(\lambda)=\frac{\operatorname{Re}(x^*Ax)}{\sum_{i=1}^n|x_i|^2}>0$$
perché il numeratore è $>0$ dato che $A$ è definita positiva (definizione) e il denominatore è $>0$. Un rapporto di due numeri positivi è positivo. $\blacksquare$
#### Criterio per le matrici hermitiane
> [!quote] Teorema (3.1 nelle dispense)
> Supponiamo che $A\in\mathbb{C}^{n\times n}$ sia una matrice **hermitiana** e siano
> $$A_1=\begin{bmatrix}a_{11}\end{bmatrix},\quad A_2=\begin{bmatrix}a_{11}&a_{12}\\a_{21}&a_{22}\end{bmatrix},\quad A_3=\begin{bmatrix}a_{11}&a_{12}&a_{13}\\a_{21}&a_{22}&a_{23}\\a_{31}&a_{32}&a_{33}\end{bmatrix},\quad\dots,\quad A_n=A$$
> le **sottomatrici principali di testa** di $A$. Allora le seguenti condizioni sono equivalenti:
> 1. $A$ è definita positiva;
> 2. $x^*Ax>0$ per ogni $x\in\mathbb{C}^n\setminus\{0\}$;
> 3. gli autovalori di $A$ sono reali e positivi;
> 4. $\det(A_k)>0$ per ogni $k=1,\dots,n$.

Le sottomatrici principali di testa sono come le **matriosche**: una contenuta nell'altra, partendo da $a_{11}$ e allargandosi di una riga e una colonna alla volta fino a "mangiare" tutta la matrice. Il teorema **non si dimostra** perché la dimostrazione è complicata. Nella condizione 3 "positivo" sottintende già "reale" (per un numero complesso non ha senso), ma il docente preferisce specificarlo.

> [!warning] Solo per matrici hermitiane
> Il docente sottolinea che è **fondamentale**: il teorema vale **solo per matrici hermitiane**, non per tutte le matrici del mondo, e all'esame spesso lo si sbaglia. Se non si sa in partenza che la matrice è hermitiana, il teorema non si può applicare così com'è.

**Esercizio** (dalla lezione). Dimostrare $1\iff2$ e $1\implies3$. Sono le implicazioni facili (basta mettere insieme cose già viste); le altre sono più difficili e non si dimostrano.

> [!info] Traccia della soluzione (nostra aggiunta)
> Per $A$ hermitiana $x^*Ax$ è reale (dimostrazione sugli autovalori delle hermitiane), quindi $\operatorname{Re}(x^*Ax)=x^*Ax$: questo dà $1\iff2$. Per $1\implies3$: gli autovalori di una hermitiana sono reali, e quelli di una definita positiva hanno parte reale $>0$; un numero reale con parte reale positiva è positivo.

**Come si usa il teorema anche per matrici non hermitiane.** Per stabilire se una matrice hermitiana è definita positiva si usa la condizione 4, la più operativa: si calcolano i determinanti delle sottomatrici principali di testa e si controlla che siano tutti positivi. Se $A$ **non** è hermitiana non si è spacciati: per l'osservazione 2, $A$ è definita positiva se e solo se lo è $\operatorname{Re}(A)$, che è **sempre hermitiana**. Quindi:
- se $A$ è hermitiana, si applica il teorema direttamente ad $A$;
- se $A$ non è hermitiana, si applica il teorema a $\operatorname{Re}(A)$.

In entrambi i casi il teorema permette di stabilire se una matrice è definita positiva. (A lezione il docente enuncia per sbaglio l'osservazione 2 come "$A$ è hermitiana se e solo se la sua parte reale è hermitiana" e si corregge subito.)

> [!example] Esempio
> Dire se
> $$A=\begin{bmatrix}2&-1&1\\-1&2&0\\1&0&1\end{bmatrix}$$
> è definita positiva.

**Soluzione.** $A$ è hermitiana perché è reale e simmetrica (scambiando righe e colonne non cambia: gli elementi simmetrici rispetto alla diagonale sono uguali), quindi $A^*=\overline{A^T}=A^T=A$. Possiamo dunque applicare il teorema precedente e dire che $A$ è definita positiva se e solo se $\det(A_k)>0$ per $k=1,2,3$:
$$\det(A_1)=2>0,\qquad\det(A_2)=\begin{vmatrix}2&-1\\-1&2\end{vmatrix}=3>0$$
$$\det(A_3)=\begin{vmatrix}2&-1&1\\-1&2&0\\1&0&1\end{vmatrix}=+1\begin{vmatrix}-1&1\\2&0\end{vmatrix}+1\begin{vmatrix}2&-1\\-1&2\end{vmatrix}=-2+3=1>0$$
(sviluppo con Laplace lungo l'**ultima riga**, segni $+,-,+$; il termine con lo $0$ non conta). Tutti e tre positivi $\implies$ $A$ è definita positiva.

> [!example] Esempio
> Dire se
> $$A=\begin{bmatrix}2&0&2\\-2&2&0\\0&0&1\end{bmatrix}$$
> è definita positiva.

(A lezione il docente scrive prima $0$ al posto del $2$ in posizione $(2,2)$ e poi corregge: è l'esempio delle dispense.)

**Soluzione.** $A$ è reale ma **non è hermitiana**, perché non è simmetrica; dunque non posso applicare direttamente il teorema ad $A$. Però dall'osservazione 2 sappiamo che $A$ è definita positiva se e solo se
$$\operatorname{Re}(A)=\frac{A+A^*}{2}=\frac{A+A^T}{2}=\begin{bmatrix}2&-1&1\\-1&2&0\\1&0&1\end{bmatrix}$$
è definita positiva ($A^*=A^T$ perché $A$ è reale). Il calcolo elemento per elemento: in posizione $(1,1)$ $\frac{2+2}{2}=2$, in $(1,2)$ $\frac{0+(-2)}{2}=-1$, in $(1,3)$ $\frac{2+0}{2}=1$, e così via; il risultato è simmetrico, come deve essere.

Inoltre $\operatorname{Re}(A)$ è hermitiana (è sempre così, non solo in questo caso), quindi posso applicare il teorema a $\operatorname{Re}(A)$: calcolo i tre determinanti delle sottomatrici principali di testa di $\operatorname{Re}(A)$. Se sono tutti e tre positivi, $\operatorname{Re}(A)$ è definita positiva e quindi anche $A$; se almeno uno non è positivo, $\operatorname{Re}(A)$ non è definita positiva e quindi neanche $A$.

Non serve fare i conti: $\operatorname{Re}(A)$ è la matrice dell'esempio di prima (il docente l'ha scelta apposta), quindi sappiamo già che è definita positiva $\implies$ $A$ è definita positiva.
#### Esercizi
**Esercizio 3.5.** Sia $A\in\mathbb{C}^{n\times n}$ una matrice hermitiana definita positiva. Dimostrare che gli elementi diagonali di $A$ sono tutti positivi, cioè $a_{ii}>0$ per ogni $i=1,\dots,n$.
*Suggerimento.* Ricordiamo che, per il Teorema 3.1 (il teorema precedente), si ha $x^*Ax>0$ per ogni $x\in\mathbb{C}^n\setminus\{0\}$. Indichiamo con $e_1,\dots,e_n$ i vettori della base canonica di $\mathbb{C}^n$, nel senso che $e_i$ è il vettore con tutte le componenti uguali a $0$ tranne quella in posizione $i$-esima che vale $1$. Fissati due indici $i,j\in\{1,\dots,n\}$, che cos'è $e_i^*Ae_j$? E che cos'è dunque $e_i^*Ae_i$?

Il docente lo raccomanda: è un esercizio teorico importante.

**Esercizio 3.6.** Dire quali fra le seguenti matrici sono definite positive.
$$A=\begin{bmatrix}2&-1&1\\-1&2&1\\1&1&0\end{bmatrix},\quad B=\begin{bmatrix}3&-4&1\\0&3&1\\1&1&3\end{bmatrix},\quad C=\begin{bmatrix}4&2+i&1\\2-i&2&0\\1&0&1\end{bmatrix},\quad D=\begin{bmatrix}2&0&-1\\1&1&-2\\-1&-1&1\end{bmatrix}$$

**Esercizio 3.7.** Stabilire per quali valori di $\alpha\in\mathbb{R}$ la seguente matrice $A$ risulta definita positiva:
$$A=\begin{bmatrix}2&0&-1\\1&1&-2\\-1&\alpha&1\end{bmatrix}$$

"Non sono esercizi difficili, però fateli." Per le matrici non hermitiane (in 3.6 $B$ e $D$, e la matrice di 3.7, che non è simmetrica per nessun $\alpha$) si passa alla parte reale come nel secondo esempio (osservazione nostra).
### Polinomi di matrici
> [!quote] Definizione (polinomio di una matrice)
> Se $p(\lambda)=a_0+a_1\lambda+a_2\lambda^2+\dots+a_m\lambda^m$ è un polinomio e $A\in\mathbb{C}^{n\times n}$ è una matrice, definiamo la matrice
> $$p(A)=a_0I+a_1A+a_2A^2+\dots+a_mA^m\in\mathbb{C}^{n\times n}$$

Al posto della variabile del polinomio (qui $\lambda$, ma si può chiamare $x$, $t$, ...) si sostituisce la matrice $A$. Davanti ad $a_0$ c'è $\lambda^0$, e $A^0=I$, la matrice identità.

> [!example] Esempio
> Se $p(\lambda)=1-2\lambda+\lambda^3$, allora $p(A)=I-2A+A^3$.

**Dimensione.** $A^2,A^3,\dots$ sono $n\times n$, quindi $p(A)$, somma di matrici $n\times n$, è una tranquillissima matrice $n\times n$ come $A$. Il grado $m$ del polinomio **non c'entra niente** con la dimensione $n$: si può avere $m=5$ e $n$ pari a due miliardi, o una matrice $2\times2$ e un polinomio di grado $5000$. Per questo si usano due lettere diverse.

> [!quote] Teorema
> Sia $p(\lambda)$ un polinomio e sia $A\in\mathbb{C}^{n\times n}$ una matrice con autovalori $\lambda_1,\dots,\lambda_n$. Allora gli autovalori di $p(A)$ sono
> $$p(\lambda_1),\dots,p(\lambda_n)$$

Come sempre, nella lista $\lambda_1,\dots,\lambda_n$ ogni autovalore compare tante volte quanto la sua molteplicità algebrica. Gli autovalori di $p(A)$ sono le **valutazioni del polinomio negli autovalori** di $A$: ad esempio, per una $3\times3$ con autovalori $\lambda_1,\lambda_2,\lambda_3$, gli autovalori di $p(A)$ sono $p(\lambda_1),p(\lambda_2),p(\lambda_3)$.
#### Dimostrazione (in tre casi)
Si dimostra il teorema **solo in tre casi**: la dimostrazione completa è troppo complicata.

**Caso 1: $p(\lambda)=a_0$ costante** (grado $0$). Allora
$$p(A)=a_0I=\begin{bmatrix}a_0&&\\&\ddots&\\&&a_0\end{bmatrix}$$
È una matrice diagonale, e gli autovalori di una matrice triangolare (in particolare diagonale) sono i suoi elementi diagonali ([[03 - Analisi delle matrici#Richiami di algebra lineare#Traccia, determinante, raggio spettrale e autovalori#Esercizi|esercizio 3.1]]). Quindi gli autovalori di $p(A)$ sono $a_0,\dots,a_0$ ($n$ volte). Non si sa quali siano gli autovalori di $A$, ma qualunque siano il polinomio costante li manda tutti in $a_0$: $p(\lambda_1)=\dots=p(\lambda_n)=a_0$. Quindi gli autovalori di $p(A)$ sono $p(\lambda_1),\dots,p(\lambda_n)$.

**Caso 2: $p(\lambda)=a_0+a_1\lambda$ di grado $1$** (quindi $a_1\neq0$). In tal caso il polinomio caratteristico di $p(A)$ e quello di $A$ sono legati dalla seguente relazione: per ogni $\lambda\in\mathbb{C}$,
$$\begin{aligned}C_{p(A)}(\lambda)&=\det\big(\lambda I-p(A)\big)=\det\big(\lambda I-(a_0I+a_1A)\big)=\det\big((\lambda-a_0)I-a_1A\big)\\&=\det\left(a_1\left(\frac{\lambda-a_0}{a_1}I-A\right)\right)=a_1^n\det\left(\frac{\lambda-a_0}{a_1}I-A\right)=a_1^n\,C_A\!\left(\frac{\lambda-a_0}{a_1}\right)\end{aligned}$$
Si è raccolta l'identità, poi $a_1$ (dividendo per $a_1$ per far tornare i conti). Si è usata la proprietà dei determinanti
$$\det(aX)=a^n\det(X)\qquad\forall a\in\mathbb{C},\ \forall X\in\mathbb{C}^{n\times n}$$
che viene dalla **multilinearità** del determinante: $a$ moltiplica tutte le $n$ righe, e portandolo fuori da ciascuna riga esce $a^n$ (come nella prima dimostrazione con la matrice di Vandermonde, [[01 - Interpolazione polinomiale#Esistenza e unicità del polinomio d'interpolazione]], dove però la costante era diversa su ogni riga). L'ultimo determinante è il polinomio caratteristico di $A$, $C_A(\mu)=\det(\mu I-A)$, calcolato in $\mu=\frac{\lambda-a_0}{a_1}$ invece che in $\lambda$.

Dunque gli autovalori di $p(A)$, cioè le radici del suo polinomio caratteristico, sono (siccome $a_1^n\neq0$)
$$\begin{aligned}\{\lambda\in\mathbb{C}:C_{p(A)}(\lambda)=0\}&=\left\{\lambda\in\mathbb{C}:C_A\!\left(\frac{\lambda-a_0}{a_1}\right)=0\right\}=\left\{\lambda\in\mathbb{C}:\frac{\lambda-a_0}{a_1}=\lambda_1,\lambda_2,\dots,\lambda_n\right\}\\&=\{\lambda\in\mathbb{C}:\lambda=a_0+a_1\lambda_1,\ a_0+a_1\lambda_2,\dots,\ a_0+a_1\lambda_n\}\\&=\{a_0+a_1\lambda_1,\ a_0+a_1\lambda_2,\dots,\ a_0+a_1\lambda_n\}=\{p(\lambda_1),p(\lambda_2),\dots,p(\lambda_n)\}\end{aligned}$$
Il passaggio chiave: il polinomio caratteristico di $A$ si annulla **solo** negli autovalori di $A$, quindi $\frac{\lambda-a_0}{a_1}$ deve essere per forza uno di $\lambda_1,\dots,\lambda_n$. $\blacksquare$

> [!info] Molteplicità (nostra aggiunta)
> L'uguaglianza tra insiemi non tiene conto delle molteplicità. Dalla stessa relazione si ricavano anche quelle: se $C_A(\mu)=\prod_{i=1}^n(\mu-\lambda_i)$, allora $C_{p(A)}(\lambda)=a_1^n\prod_{i=1}^n\left(\frac{\lambda-a_0}{a_1}-\lambda_i\right)=\prod_{i=1}^n\big(\lambda-(a_0+a_1\lambda_i)\big)$.

**Caso 3: $A$ diagonalizzabile.** Nei casi 1 e 2 si è imposta una condizione sulla forma del polinomio; ora il polinomio è qualsiasi e la condizione è sulla matrice. In tal caso ([[03 - Analisi delle matrici#Richiami di algebra lineare#Matrici diagonalizzabili]]) esistono $X\in\mathbb{C}^{n\times n}$ invertibile e $D\in\mathbb{C}^{n\times n}$ diagonale, avente sulla diagonale gli autovalori di $A$ ($D=\operatorname{diag}(\lambda_1,\lambda_2,\dots,\lambda_n)$), tali che
$$A=XDX^{-1}$$
Le potenze di $A$:
$$A^2=XDX^{-1}\cdot XDX^{-1}=XD^2X^{-1},\qquad A^3=XDX^{-1}\cdot XDX^{-1}\cdot XDX^{-1}=XD^3X^{-1}$$
perché i prodotti $X^{-1}X$ in mezzo fanno l'identità, elemento neutro del prodotto, e spariscono. Andando avanti,
$$A^k=XD^kX^{-1}\qquad\forall k\geq0$$
anche per $k=0$, perché $A^0=I=XD^0X^{-1}$ ($D^0=I$ e $XX^{-1}=I$).

Ma allora, fissato un polinomio qualsiasi $p(\lambda)=a_0+a_1\lambda+a_2\lambda^2+\dots+a_m\lambda^m$,
$$\begin{aligned}p(A)&=a_0I+a_1A+a_2A^2+\dots+a_mA^m=a_0XIX^{-1}+a_1XDX^{-1}+a_2XD^2X^{-1}+\dots+a_mXD^mX^{-1}\\&=X\big(a_0I+a_1D+a_2D^2+\dots+a_mD^m\big)X^{-1}=X\,p(D)\,X^{-1}\end{aligned}$$
raccogliendo $X$ a sinistra e $X^{-1}$ a destra (in mezzo resta $a_0I$, non lo scalare $a_0$: il docente corregge la lavagna).

**Chi è $p(D)$.** Il quadrato di una matrice diagonale è diagonale con i **quadrati** degli elementi diagonali (prodotto righe per colonne), e così via per le potenze: $D^k=\operatorname{diag}(\lambda_1^k,\dots,\lambda_n^k)$. Quindi
$$p(D)=a_0\begin{bmatrix}1&&\\&\ddots&\\&&1\end{bmatrix}+a_1\begin{bmatrix}\lambda_1&&\\&\ddots&\\&&\lambda_n\end{bmatrix}+a_2\begin{bmatrix}\lambda_1^2&&\\&\ddots&\\&&\lambda_n^2\end{bmatrix}+\dots+a_m\begin{bmatrix}\lambda_1^m&&\\&\ddots&\\&&\lambda_n^m\end{bmatrix}=\begin{bmatrix}p(\lambda_1)&&\\&\ddots&\\&&p(\lambda_n)\end{bmatrix}$$
È una combinazione lineare di matrici diagonali, quindi diagonale, e l'elemento $(1,1)$ è $a_0+a_1\lambda_1+a_2\lambda_1^2+\dots+a_m\lambda_1^m=p(\lambda_1)$; analogamente gli altri.

La scrittura $p(A)=X\,p(D)\,X^{-1}$ ci dice che $p(A)$ è **diagonalizzabile**, che $p(\lambda_1),\dots,p(\lambda_n)$ sono gli autovalori di $p(A)$ e inoltre che le colonne di $X$ sono i corrispondenti autovettori. $\blacksquare$

> [!info] Più della tesi
> Nel caso 3 si è dimostrato più di quanto richiesto, ma sotto l'ipotesi aggiuntiva che $A$ sia diagonalizzabile (che il teorema non presuppone): se $A$ è diagonalizzabile, anche $p(A)$ lo è, e siccome le colonne di $X$ sono anche gli autovettori di $A$, **gli autovettori di $p(A)$ sono gli stessi di $A$**. Cambiano solo gli autovalori, da $\lambda_1,\dots,\lambda_n$ a $p(\lambda_1),\dots,p(\lambda_n)$.
#### Esempio
> [!example] Esempio
> Sia
> $$A=\begin{bmatrix}1&-2&5\\0&-3&-7\\0&0&1\end{bmatrix}$$
> Calcolare gli autovalori della matrice $B=2I+A-3A^7$.

Una soluzione "bovina" sarebbe scrivere $B$, calcolarne il polinomio caratteristico e trovarne le radici: ma bisognerebbe calcolare $A^7$. Se all'esame compare un $A^7$, probabilmente la strategia prevista non è calcolarlo.

**Soluzione.** Osserviamo che $B$ è un polinomio di $A$: infatti
$$B=p(A)\quad\text{con}\quad p(\lambda)=2+\lambda-3\lambda^7$$
(qui il ragionamento è al contrario: dato $p(A)$, si trova il polinomio). Quindi per il teorema gli autovalori di $B$ sono le valutazioni di $p(\lambda)$ negli autovalori di $A$. Siccome $A$ è una matrice triangolare superiore, gli autovalori di $A$ sono gli elementi diagonali di $A$, cioè $1,-3,1$. Dunque gli autovalori di $B$ sono
$$p(1)=2+1-3\cdot1^7=0,\qquad p(-3)=2-3-3\cdot(-3)^7=6560,\qquad p(1)=0$$

> [!info] Invertibilità
> $A$ è invertibile (i suoi autovalori sono tutti diversi da $0$), mentre $B=p(A)$ **non** lo è: ha ben due autovalori uguali a $0$.

> [!question] Domanda tipica d'esame
> Dare la definizione di matrice hermitiana e dimostrare che i suoi autovalori sono reali. Traccia: $Ax=\lambda x$ con $x\neq0$; moltiplicare a sinistra per $x^*$ e ottenere $\lambda=\frac{x^*Ax}{\sum_i|x_i|^2}$ (denominatore reale $>0$ perché $x\neq0$); dimostrare che $x^*Ax$ è reale vedendolo come matrice $1\times1$: $\overline{x^*Ax}=(x^*Ax)^*=x^*A^*x=x^*Ax$, usando $(AB)^*=B^*A^*$ e $A^*=A$.

> [!question] Domanda tipica d'esame
> Definire le matrici definite positive e dimostrare che $A$ è definita positiva se e solo se $\operatorname{Re}(A)$ lo è; dimostrare che ogni autovalore di una matrice definita positiva ha parte reale strettamente positiva (e quindi che la matrice è invertibile). Traccia: $\operatorname{Re}(x^*Ax)=\frac{x^*Ax+x^*A^*x}{2}=x^*\operatorname{Re}(A)x$, che è reale e quindi uguale alla propria parte reale; per gli autovalori, $\operatorname{Re}(\lambda)=\frac{\operatorname{Re}(x^*Ax)}{\sum_i|x_i|^2}>0$.

> [!question] Domanda tipica d'esame
> Stabilire se una matrice data è definita positiva. Traccia: se è hermitiana (per una reale: simmetrica) applicare il Teorema 3.1, condizione 4, cioè controllare $\det(A_k)>0$ per tutte le sottomatrici principali di testa; se non è hermitiana calcolare $\operatorname{Re}(A)=\frac{A+A^*}{2}$ e applicare il teorema a $\operatorname{Re}(A)$. Mai applicare il teorema a una matrice non hermitiana.

> [!question] Domanda tipica d'esame
> Enunciare il teorema sugli autovalori di $p(A)$ e dimostrarlo nel caso $A$ diagonalizzabile (o per $p$ di grado $\leq1$); calcolare gli autovalori di una matrice del tipo $B=2I+A-3A^7$ con $A$ triangolare. Traccia: $A^k=XD^kX^{-1}$, quindi $p(A)=X\,p(D)\,X^{-1}$ con $p(D)=\operatorname{diag}(p(\lambda_1),\dots,p(\lambda_n))$; nell'esempio riconoscere $B=p(A)$ e valutare $p$ negli elementi diagonali di $A$.

La lezione sfora di circa 13 minuti. Il docente propone come regola indicativa circa due ore e mezza il martedì e un'ora e mezza il giovedì, perché il giovedì il tempo è più tirato.
## Matrici irriducibili e teoremi di Gershgorin
Lezione 10 (05/11/2026): grafi, grafo associato a una matrice e matrici irriducibili; inizio della localizzazione degli autovalori con i cerchi di Gershgorin e i tre teoremi di Gershgorin (il primo con dimostrazione, il terzo in versione forte e debole), con un esempio vero/falso.

Finita nella lezione precedente la parte sui polinomi di matrici, ci si muove verso la **localizzazione degli autovalori**, che è il prossimo argomento. Per farlo serve prima la nozione di **matrice irriducibile**, che compare nell'ipotesi del terzo teorema di Gershgorin. Già in questa lezione si arriva alla prima parte della localizzazione.
### Matrici irriducibili
#### Grafi
Il docente richiama le nozioni sui grafi (gli informatici dovrebbero conoscerle) soprattutto per fissare la notazione. Le definizioni sono "amichevoli", non formali.

- Un **grafo** è un diagramma formato da un certo numero di **nodi** e un certo numero di **archi**.
- Un **arco** è una freccia che parte da un nodo e arriva a un altro (che può essere anche il nodo di partenza: in questo caso l'arco è un **cappio**).
- Se il grafo possiede $n$ nodi, li indichiamo con $1,\dots,n$, mentre l'arco che va dal nodo $i$ al nodo $j$ lo indichiamo con $i\to j$.
- Un **cammino** all'interno di un grafo è un percorso che parte da un nodo $i$ e, seguendo gli archi del grafo, arriva a un altro nodo $j$. Se il nodo di arrivo $j$ coincide con il nodo di partenza $i$, allora il cammino si chiama **ciclo**.

> [!quote] Definizione (grafo fortemente connesso)
> Un grafo si dice **fortemente connesso** se per ogni coppia di nodi $i$ e $j$ esiste un cammino nel grafo che va da $i$ a $j$.
>
> Equivalentemente, un grafo è fortemente connesso se esiste un **ciclo** nel grafo che **tocca tutti i nodi**.

Cioè, partendo da un qualsiasi nodo $i$ e seguendo le frecce, si riesce ad arrivare in qualsiasi nodo $j$. Uno studente chiede se il ciclo può passare più volte per lo stesso nodo: sì, non c'è problema.

**Esercizio** (dalla lezione). Dimostrare l'equivalenza delle due condizioni: se per ogni coppia di nodi $i,j$ esiste un cammino da $i$ a $j$, allora esiste un ciclo che tocca tutti i nodi; viceversa, se esiste un ciclo che tocca tutti i nodi, allora per ogni coppia di nodi $i,j$ esiste un cammino da $i$ a $j$.

> [!example] Esempio
> Due grafi con nodi $1,2,3$:
> - il primo ha gli archi $1\to2$, $2\to1$, $2\to2$ (cappio), $2\to3$, $3\to2$;
> - il secondo è lo stesso grafo **senza l'arco** $3\to2$.

Il primo è **fortemente connesso**: c'è il ciclo
$$1\to2\to3\to2\to1$$
che tocca tutti i nodi. Il secondo **non è fortemente connesso**: dal nodo $3$ non esce nessuna freccia, quindi da $3$ non si può andare da nessuna parte (ad esempio non si può andare in $2$). Basta togliere un solo arco nel posto sbagliato perché il grafo smetta di essere fortemente connesso.
#### Grafo associato a una matrice e matrici irriducibili
> [!quote] Definizione (grafo associato a una matrice $A\in\mathbb{C}^{n\times n}$)
> Data $A\in\mathbb{C}^{n\times n}$, il **grafo associato ad $A$** è il grafo così definito:
> - i nodi sono $1,\dots,n$;
> - gli archi sono le frecce $i\to j$ tali che $a_{ij}\neq0$.

Cioè: a ogni elemento non nullo della matrice corrisponde un arco. Gli informatici hanno visto la matrice di adiacenza di un grafo, ma non il grafo associato a una matrice qualsiasi.

> [!quote] Definizione (matrice irriducibile)
> Una matrice $A\in\mathbb{C}^{n\times n}$ si dice **irriducibile** se il grafo associato ad $A$ è fortemente connesso.

Se una matrice non è irriducibile si dice **riducibile**. Il docente osserva che "non irriducibile" è una doppia negazione ("non non riducibile"): irriducibile è il termine più importante, riducibile è solo il suo contrario.

> [!example] Esempio
> Stabilire se
> $$A=\begin{bmatrix}0&i&0\\1&1&4\\0&i&0\end{bmatrix},\qquad B=\begin{bmatrix}0&-1&0\\i&2&-3\\0&0&0\end{bmatrix}$$
> sono irriducibili.

Bisogna imparare a costruire i grafi associati alle matrici. Il docente consiglia di **procedere per righe**: la riga $i$ riguarda il nodo $i$ e dice dove si può andare partendo da $i$ (c'è la freccia $i\to j$ se e solo se $a_{ij}\neq0$).

**Grafo di $A$.** La matrice è $3\times3$, quindi ci sono tre nodi $1,2,3$.
- Riga 1, $(0,\ i,\ 0)$: da $1$ non si va in $1$ (niente cappio, $a_{11}=0$), si va in $2$ ($a_{12}=i\neq0$), non si va in $3$ ($a_{13}=0$).
- Riga 2, $(1,\ 1,\ 4)$: tutti gli elementi sono non nulli, quindi da $2$ si va dappertutto: $2\to1$, $2\to2$ (cappio), $2\to3$.
- Riga 3, $(0,\ i,\ 0)$: da $3$ si va soltanto in $2$.

È esattamente il primo grafo dell'esempio precedente: è fortemente connesso (c'è il ciclo $1\to2\to3\to2\to1$ che tocca tutti i nodi), quindi **$A$ è irriducibile**.

**Grafo di $B$.** La prima riga ha gli zeri nelle stesse posizioni di quella di $A$, quindi da $1$ si va solo in $2$. La seconda riga ha tutti elementi non nulli, quindi da $2$ si va dappertutto (cappio compreso). La terza riga è tutta nulla: da $3$ non si va da nessuna parte. È il secondo grafo dell'esempio precedente: non è fortemente connesso (da $3$ non si può andare in $2$, e neanche in $1$), quindi **$B$ non è irriducibile** (è riducibile).

**Esercizio 3.8.** Stabilire quali delle seguenti matrici sono irriducibili.
$$A=\begin{bmatrix}0&-1&0&0\\1&0&1&i\\1+i&0&0&-1\\-2&7&10&3i\end{bmatrix},\qquad B=\begin{bmatrix}1&0&3&4\\0&1&1&-1\\0&0&4&7\\0&-i&0&1\end{bmatrix},\qquad C=\begin{bmatrix}0&0&0&0&1\\1&0&0&0&0\\0&1&0&0&0\\0&0&1&0&0\\0&0&0&1&0\end{bmatrix}$$

Il docente anticipa che $C$, anche se è piena di zeri, è irriducibile, perché i suoi uni stanno "al posto giusto"; mentre forse una delle altre due, pur avendo pochi zeri, è riducibile. **Non è una questione di quanti zeri ci sono**, ma di dove sono piazzati gli elementi non nulli: devono permettere un ciclo che tocca tutti i nodi.

> [!info] Soluzione dell'esercizio 3.8 (nostra aggiunta, non svolta in classe)
> - **$A$**: archi $1\to2$; $2\to1,\,2\to3,\,2\to4$; $3\to1,\,3\to4$; $4\to1,\,4\to2,\,4\to3,\,4\to4$. C'è il ciclo $1\to2\to3\to4\to1$ che tocca tutti i nodi: $A$ è **irriducibile**.
> - **$B$**: nella prima colonna l'unico elemento non nullo è $b_{11}$, quindi nessuna freccia entra nel nodo $1$ da un altro nodo: da $2,3,4$ non si può mai arrivare in $1$. $B$ è **riducibile**.
> - **$C$**: archi $1\to5$, $2\to1$, $3\to2$, $4\to3$, $5\to4$. C'è il ciclo $1\to5\to4\to3\to2\to1$: $C$ è **irriducibile**.

> [!warning] Il raggio spettrale non è mai negativo
> Aneddoto raccontato in classe (all'arrivo in ritardo di uno studente): a un esame una matrice $2\times2$ aveva autovalori $-1$ e $\frac12$, e alla domanda "qual è il raggio spettrale?" lo studente rispose $-1$. **Sbagliato**: il raggio spettrale è il **massimo dei moduli** degli autovalori ([[03 - Analisi delle matrici#Richiami di algebra lineare#Traccia, determinante, raggio spettrale e autovalori]]), quindi qui $\rho=\max(|-1|,|\tfrac12|)=1$. $-1$ è l'autovalore di modulo più grande, ma $\rho$ è il suo modulo. Il raggio spettrale non può mai essere negativo: al minimo è $0$ (quando tutti gli autovalori sono $0$).
### Localizzazione degli autovalori
Secondo il docente è un argomento importante del corso. Gli autovalori sono oggetti importanti di una matrice (riguardano lo spettro, hanno applicazioni in fisica), ed è importante, data una matrice, riuscire a **localizzarli**: non calcolarli esattamente, che è difficilissimo, ma capire **dove stanno**.

> [!info] Perché si lavora in $\mathbb{C}$
> Gli autovalori sono in generale numeri complessi, **anche se la matrice ha tutte le componenti reali**. Per questo si considerano matrici in $\mathbb{C}^{n\times n}$: da una parte comprendono quelle in $\mathbb{R}^{n\times n}$, quindi la teoria è più generale; dall'altra, anche partendo da una matrice reale, si finisce comunque nei complessi. Tanto vale partire subito da $\mathbb{C}$, che ha la proprietà di **chiusura algebrica**: per il teorema fondamentale dell'algebra ogni polinomio di grado $n$ ha $n$ radici in $\mathbb{C}$ (contate con molteplicità), quindi ogni matrice $n\times n$ ha esattamente $n$ autovalori nel campo complesso, mentre in $\mathbb{R}$ non è detto. Gli autovalori stanno quindi nel piano complesso, e il problema è sapere dove.
#### Cerchi di Gershgorin
Prima una notazione. Per ogni $z_0\in\mathbb{C}$ e per ogni $r\geq0$ definiamo
$$\mathcal{C}(z_0,r)=\{z\in\mathbb{C}:\ |z-z_0|\leq r\}$$
il **cerchio** (chiuso) nel piano complesso di centro $z_0$ e raggio $r$. Infatti $|z-z_0|=\operatorname{dist}(z,z_0)$ è la distanza tra $z$ e $z_0$: il cerchio è l'insieme dei numeri complessi la cui distanza da $z_0$ è al più $r$. Alla lavagna, il disegno nel piano complesso con assi $\operatorname{Re}(z)$ e $\operatorname{Im}(z)$, il centro $z_0$, il raggio $r$ e un punto $z$ interno.

> [!quote] Definizione (cerchi di Gershgorin)
> Per ogni $A\in\mathbb{C}^{n\times n}$ definiamo i **cerchi di Gershgorin di $A$** come i cerchi $K_1,\dots,K_n$ definiti come segue: per ogni $i=1,\dots,n$,
> $$K_i=\mathcal{C}\big(a_{ii},\ |a_{i1}|+\dots+|a_{i,i-1}|+|a_{i,i+1}|+\dots+|a_{in}|\big)=\mathcal{C}\Big(a_{ii},\ \sum_{\substack{j=1\\j\neq i}}^n|a_{ij}|\Big)$$

Ci sono $n$ cerchi, uno per ogni riga. Il **centro** di $K_i$ è l'elemento diagonale della riga $i$; il **raggio** è la somma dei **moduli** degli altri elementi della stessa riga, escluso quello diagonale.

Per brevità il docente propone il "patto" di abbreviare Gershgorin con **G** ("cerchi di G", "teoremi di G").

> [!quote] Definizione (cerchi di Gershgorin per riga e per colonna)
> $K_1,\dots,K_n$ si chiamano anche **cerchi di G per riga di $A$**. Questo serve a distinguerli dai **cerchi di G per colonna di $A$**, che sono i cerchi $H_1,\dots,H_n$ così definiti: per ogni $j=1,\dots,n$,
> $$H_j=\mathcal{C}\Big(a_{jj},\ \sum_{\substack{i=1\\i\neq j}}^n|a_{ij}|\Big)$$

Per $H_j$ il centro è l'elemento diagonale della colonna $j$ e il raggio è la somma dei moduli degli altri elementi della colonna $j$ (attenzione agli indici: si somma su $i$, saltando $i=j$). La forma l'hanno indovinata gli studenti.

> [!warning] Convenzione
> **Se non si specifica niente, quando si parla dei cerchi di G di $A$ s'intendono quelli per riga.** Per parlare dei cerchi per colonna bisogna dirlo esplicitamente ogni volta.

> [!info] Sulle dispense
> Il docente non distribuisce le dispense (alcuni studenti le hanno recuperate dagli anni passati): non contengono tutte le spiegazioni date a lezione, e chi studia solo sulle dispense tende ad andare peggio di chi prende appunti. Il metodo consigliato è scrivere a lezione.

> [!example] Esempio
> Sia
> $$A=\begin{bmatrix}0&-1&0&0\\1&0&1&i\\1+i&0&0&-1\\-2&7&10&3i\end{bmatrix}$$
> Quali sono i cerchi di G di $A$?

(È la stessa matrice $A$ dell'esercizio 3.8.) Non si specifica niente, quindi si intendono i cerchi per riga: quattro cerchi, uno per riga. I centri sono gli elementi diagonali $0,0,0,3i$.
$$K_1=\mathcal{C}(0,\,|-1|)=\mathcal{C}(0,1)$$
$$K_2=\mathcal{C}(0,\,|1|+|1|+|i|)=\mathcal{C}(0,3)$$
$$K_3=\mathcal{C}(0,\,|1+i|+|-1|)=\mathcal{C}(0,\,1+\sqrt2)$$
$$K_4=\mathcal{C}(3i,\,|-2|+|7|+|10|)=\mathcal{C}(3i,19)$$
Si usa $|i|=1$ e, in generale, $|a+bi|=\sqrt{a^2+b^2}$: ad esempio $|1+i|=\sqrt{1^2+1^2}=\sqrt2$.

> [!warning] La somma dei moduli
> Errori fatti in classe: per $K_2$ uno studente propone raggio $2+i$, e per $K_4$ qualcuno propone $15$ ($=-2+7+10$). Il raggio è la somma dei **moduli**: $|i|=1$, non $i$, quindi il raggio di $K_2$ è $3$; per $K_4$ è $|-2|+|7|+|10|=19$. Senza i moduli si potrebbe ottenere un raggio complesso o negativo, che non ha senso.
#### Primo teorema di Gershgorin
Ci sono tre teoremi di Gershgorin per la localizzazione degli autovalori; il più importante è il primo, ed è l'unico che si dimostra.

> [!quote] Teorema (1° di Gershgorin)
> Gli autovalori di una matrice $A\in\mathbb{C}^{n\times n}$ stanno tutti nell'**unione** dei cerchi di G di $A$:
> $$\lambda\text{ autovalore di }A\implies\lambda\in K_1\cup\dots\cup K_n$$

> [!warning] Unione, non "un autovalore per cerchio"
> Uno studente chiede se ogni cerchio contiene un autovalore. **No**: il teorema dice solo che stanno tutti nell'unione. Potrebbero anche stare tutti in un solo cerchio.
##### Dimostrazione
Sia $\lambda$ un generico autovalore di $A$. Dimostro che $\lambda$ appartiene almeno ad un cerchio di G di $A$ (e quindi sta nell'unione dei cerchi di G di $A$). Siccome $\lambda$ è generico, il discorso vale per tutti gli autovalori.

Prendiamo $u\neq0$ autovettore di $A$ relativo a $\lambda$:
$$Au=\lambda u\iff(Au)_i=(\lambda u)_i\quad\forall i=1,\dots,n\iff\sum_{j=1}^na_{ij}u_j=\lambda u_i\quad\forall i=1,\dots,n\tag{$\ast$}$$
Un'uguaglianza tra vettori vale se e solo se vale componente per componente. La componente $i$ di $Au$ è la riga $i$ di $A$ per il vettore $u$, cioè $a_{i1}u_1+a_{i2}u_2+\dots=\sum_ja_{ij}u_j$; la componente $i$ di $\lambda u$ è $\lambda u_i$, perché $\lambda$ è uno scalare che moltiplica il vettore.

Seleziono un indice $i_0\in\{1,\dots,n\}$ corrispondente a una componente $u_{i_0}$ di $u$ di **modulo massimo**:
$$|u_{i_0}|=\max\big(|u_1|,|u_2|,\dots,|u_n|\big)$$
(se ce n'è più di una di modulo massimo, ne basta una). Inoltre $u_{i_0}\neq0$, perché se fosse $u_{i_0}=0$, essendo di modulo massimo, tutte le componenti sarebbero nulle e avremmo $u=0$, che è impossibile.

L'equazione $(\ast)$ con $i=i_0$ ci dice che
$$\sum_{j=1}^na_{i_0j}u_j=\lambda u_{i_0}$$
Si tira fuori dalla sommatoria il termine con $j=i_0$, cioè $a_{i_0i_0}u_{i_0}$, lo si porta a destra e si raccoglie $u_{i_0}$:
$$\sum_{\substack{j=1\\j\neq i_0}}^na_{i_0j}u_j=(\lambda-a_{i_0i_0})\,u_{i_0}$$
Prendendo i moduli di entrambi i membri (scrivendo prima quello di destra):
$$\big|(\lambda-a_{i_0i_0})\,u_{i_0}\big|=\Big|\sum_{\substack{j=1\\j\neq i_0}}^na_{i_0j}u_j\Big|$$
Servono due proprietà dei numeri complessi (il docente promette di ricordarle "fino alla noia"):
- $|\alpha\beta|=|\alpha|\,|\beta|$ per ogni $\alpha,\beta\in\mathbb{C}$ (il modulo di un prodotto è il prodotto dei moduli);
- $\big|\sum_{j=1}^n\alpha_j\big|\leq\sum_{j=1}^n|\alpha_j|$ per ogni $\alpha_1,\dots,\alpha_n\in\mathbb{C}$ (**disuguaglianza triangolare**).

Allora, un passaggio per volta:
$$|\lambda-a_{i_0i_0}|\cdot|u_{i_0}|=\Big|\sum_{\substack{j=1\\j\neq i_0}}^na_{i_0j}u_j\Big|\overset{\text{disug. tri.}}{\leq}\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}u_j|=\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}|\cdot|u_j|\leq\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}|\cdot|u_{i_0}|=|u_{i_0}|\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}|$$
- la prima uguaglianza usa $|\alpha\beta|=|\alpha||\beta|$ al primo membro;
- poi la disuguaglianza triangolare, e di nuovo il modulo del prodotto per separare $|a_{i_0j}|$ da $|u_j|$;
- il **passaggio cruciale**: $i_0$ era stato scelto come indice di una componente di modulo massimo, quindi $|u_j|\leq|u_{i_0}|$ qualunque sia $j$;
- infine $|u_{i_0}|$ non dipende dall'indice di sommazione $j$, è una costante, e si porta fuori dalla sommatoria.

Si è ottenuto
$$|\lambda-a_{i_0i_0}|\cdot|u_{i_0}|\leq|u_{i_0}|\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}|$$
Dividendo entrambi i membri di questa disuguaglianza per $|u_{i_0}|>0$ (è un modulo, ed è diverso da $0$ perché $u_{i_0}\neq0$; dividendo per un numero positivo il verso non cambia):
$$\underbrace{|\lambda-a_{i_0i_0}|}_{\operatorname{dist}(\lambda,\,a_{i_0i_0})}\leq\underbrace{\sum_{\substack{j=1\\j\neq i_0}}^n|a_{i_0j}|}_{\text{raggio di }K_{i_0}}$$
dove $a_{i_0i_0}$ è il **centro di $K_{i_0}$**. La distanza di $\lambda$ dal centro di $K_{i_0}$ è minore o uguale al raggio di $K_{i_0}$, cioè $\lambda$ sta dentro il cerchio:
$$\lambda\in K_{i_0}\implies\lambda\in K_1\cup\dots\cup K_n\qquad\blacksquare$$

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare il primo teorema di Gershgorin. Traccia: definire i cerchi $K_i=\mathcal{C}(a_{ii},\sum_{j\neq i}|a_{ij}|)$; preso $\lambda$ autovalore con autovettore $u\neq0$, scrivere $Au=\lambda u$ per componenti; scegliere $i_0$ con $|u_{i_0}|$ massimo (e quindi $u_{i_0}\neq0$); isolare il termine diagonale nell'equazione $i_0$, ottenendo $(\lambda-a_{i_0i_0})u_{i_0}=\sum_{j\neq i_0}a_{i_0j}u_j$; passare ai moduli, usare disuguaglianza triangolare e $|u_j|\leq|u_{i_0}|$; dividere per $|u_{i_0}|>0$ e concludere $\lambda\in K_{i_0}$.
#### Secondo teorema di Gershgorin
> [!quote] Teorema (2° di Gershgorin)
> Supponiamo che l'unione di $k$ cerchi di G di $A\in\mathbb{C}^{n\times n}$ sia **disgiunta** dall'unione degli altri $n-k$ cerchi. Allora $k$ autovalori di $A$ stanno nella prima unione e gli altri $n-k$ autovalori stanno nella seconda unione.

Cioè: se gli $n$ cerchi si possono separare in due gruppi, $k$ da una parte e $n-k$ dall'altra, con le due unioni disgiunte, allora **esattamente** $k$ autovalori (contati con molteplicità) stanno nell'unione che contiene $k$ cerchi e $n-k$ nell'altra. Non si dimostra.
#### Terzo teorema di Gershgorin (forte)
Il docente lo presenta come un teorema "challenging", dalla formulazione piuttosto complessa: non va dimostrato ma va capito. Esiste in versione **forte** e **debole**; se non si dice niente si intende quella forte. Nel corso la versione forte servirà in **un solo caso**, per questo va enunciata; negli esercizi si userà sempre quella debole, più facile da capire.

> [!quote] Teorema (3° di Gershgorin, forte)
> Supponiamo che $A\in\mathbb{C}^{n\times n}$ sia **irriducibile**. Allora i punti che
> 1. stanno sul bordo di quei cerchi di G a cui appartengono, ma
> 2. non stanno sul bordo di tutti i cerchi di G
>
> non sono autovalori di $A$.

È un **teorema esclusivo**: serve per **escludere** alcuni punti dai possibili autovalori di $A$. Si applica **solo alle matrici irriducibili**: se la matrice non è irriducibile non si può usare.

> [!example] Esempio (il quadrifoglio)
> Immaginiamo una matrice $A\in\mathbb{C}^{5\times5}$ **irriducibile** con i cerchi di G come in figura: quattro cerchi uguali (le "foglie", verdi) disposti come un quadrifoglio, che passano tutti per il centro $q$ del quadrifoglio, più un quinto cerchio piccolo (rosso) contenuto all'interno di una delle foglie (la "foglia mangiata dal baco"). Il numero dei cerchi è uguale alla dimensione della matrice, quindi la matrice è $5\times5$.

Guardiamo il punto $q$, il centro del quadrifoglio:
1. $q$ sta sul bordo di tutti i cerchi di G a cui appartiene? **Sì**: $q$ appartiene ai cerchi verdi e sta sul bordo di essi (non appartiene al cerchio rosso).
2. $q$ sta sul bordo di tutti i cerchi di G? **No**, perché non sta sul cerchio rosso.

Siccome $A$ è irriducibile, si può applicare il terzo teorema: **$q$ non è un autovalore di $A$**. È sorprendente: il primo teorema direbbe soltanto che gli autovalori stanno nel quadrifoglio (l'unione dei cerchi, tutta "colorata di verde"), e proprio il centro viene escluso.

Si possono escludere anche tutti i punti del **bordo esterno** del quadrifoglio (cioè del bordo dell'unione). Ad esempio un punto $w$ sul bordo esterno di una foglia: appartiene a un solo cerchio e sta sul suo bordo (condizione 1), ma non sta sul bordo di tutti i cerchi (condizione 2), quindi è escluso. $q$ invece è un punto "eccezionale": non sta sul bordo dell'unione, ma viene escluso lo stesso dalla versione forte.

> [!example] Esempio (due cerchi)
> Una matrice irriducibile con solo **due cerchi** di G che si intersecano. Uno dei due punti di intersezione dei bordi sta sul bordo dell'unione, ma sta anche **sul bordo di tutti i cerchi** (sono due, e sta sul bordo di entrambi): la condizione 2 non vale e il terzo teorema **non lo può escludere** (non è detto che sia un autovalore, ma non si può escludere). Un punto del bordo dell'unione che sta sul bordo di uno solo dei due cerchi, invece, si esclude.

Quindi, in risposta a una domanda in classe: tendenzialmente i punti del bordo dell'unione vengono esclusi, ma non quelli che stanno sul bordo di tutti i cerchi.
#### Terzo teorema di Gershgorin (debole)
> [!warning] All'esame solo la versione debole
> Il "patto" con gli studenti: **anche all'esame usate solo il terzo teorema debole.** Uno studente che ha voluto usare la versione forte "si è incastrato e ha fatto un casino". Con la versione debole si escludono comunque tutti i punti che servono. Il "massimo delle conoscenze" per gli esercizi sono il primo teorema, il secondo e il terzo debole.

> [!quote] Teorema (3° di Gershgorin, debole)
> Supponiamo che $A\in\mathbb{C}^{n\times n}$ sia **irriducibile** e sia $\mathcal{B}$ il **bordo dell'unione** dei cerchi di G di $A$. Allora i punti di $\mathcal{B}$ che non stanno sul bordo di tutti i cerchi non sono autovalori di $A$.

> [!warning] Il bordo dell'unione, non i bordi dei cerchi
> Molti studenti sbagliano: $\mathcal{B}$ è il bordo **dell'unione**. Prima si fa l'unione, poi se ne prende il bordo. Non si devono prendere singolarmente i bordi dei singoli cerchi: gli archi di cerchio che stanno **dentro** l'unione (dentro un altro cerchio) non fanno parte di $\mathcal{B}$. Nel quadrifoglio, $\mathcal{B}$ è solo il contorno esterno; $q$ non è un punto di $\mathcal{B}$. Il consiglio per non sbagliare: immaginare di colorare uniformemente tutti i cerchi e guardare il bordo della parte colorata.
#### Esempio: vero o falso con i teoremi di Gershgorin
> [!example] Esempio
> Supponiamo che una matrice $A\in\mathbb{C}^{5\times5}$ sia irriducibile e che i suoi cerchi di G siano
> $$K_1=\mathcal{C}(1,1),\quad K_2=\mathcal{C}(-i,1),\quad K_3=\mathcal{C}(4i,1),\quad K_4=\mathcal{C}(1+i,1),\quad K_5=\mathcal{C}(-1,1)$$
> Avendo solo queste informazioni a disposizione, dire se le seguenti affermazioni sono vere o false, motivando la risposta.
> 1. $0$ non è un autovalore di $A$.
> 2. $A$ è invertibile.
> 3. $1$ potrebbe essere un autovalore di $A$.
> 4. $-1+4i$ potrebbe essere un autovalore di $A$.
> 5. $K_3$ privato del suo bordo contiene esattamente un autovalore di $A$.
> 6. $3<\rho(A)<5$.

Per prima cosa si **disegnano i cerchi** nel piano complesso (tutti di raggio $1$):
- $K_1$ centrato in $1$, $K_5$ centrato in $-1$, $K_2$ centrato in $-i$: passano tutti per l'origine;
- $K_4$ centrato in $1+i$: passa per $1$ e per $i$;
- $K_3$ centrato in $4i$, in alto, **isolato** dagli altri.

Poi si individua il bordo dell'unione $\mathcal{B}$ (in rosso alla lavagna): il contorno esterno del gruppo $K_1,K_2,K_4,K_5$ (compreso un piccolo tratto vicino all'origine, dove l'unione ha una "rientranza") più tutta la circonferenza di $K_3$.

**1. VERA.** Infatti $0\in\mathcal{B}$ (bordo dell'unione dei cerchi), ma $0$ non sta sul bordo di tutti i cerchi (non sta sul bordo di $K_3$, $K_4$). Quindi per il 3° teorema di G debole (**applicabile perché $A$ è irriducibile**), $0$ non è autovalore di $A$.

**2. VERA.** Infatti $0$ non è autovalore di $A$ per il punto 1, quindi $A$ è invertibile ($A$ invertibile $\iff$ $0$ non è autovalore di $A$, [[03 - Analisi delle matrici#Richiami di algebra lineare#Matrici invertibili]]). Lo ha osservato uno studente.

**3. VERA.** Infatti $1$ sta nell'unione dei cerchi di G, quindi in linea di principio potrebbe essere autovalore di $A$ per il 1° teorema di G, a meno che non venga escluso dal 3° teorema di G (debole). Ma il 3° teorema di G debole non può escludere $1$, perché $1\notin\mathcal{B}$: $1$ sta sul bordo di $K_4$, ma è il centro di $K_1$, quindi è interno all'unione e non è un punto del bordo dell'unione.

> [!info] Neanche la versione forte esclude $1$
> Il docente aggiunge, "per farsi del male": nemmeno il 3° teorema forte potrebbe escludere $1$, perché non ne soddisfa la condizione 1. $1$ appartiene a due cerchi, $K_1$ e $K_4$; sta sul bordo di $K_4$ ma **non** sul bordo di $K_1$ (ne è il centro). Quindi non è vero che sta sul bordo di quei cerchi a cui appartiene.

**4. FALSA.** Infatti $-1+4i$ non può essere autovalore di $A$ per lo stesso motivo per cui $0$ non può essere autovalore di $A$: $-1+4i$ sta sulla circonferenza di $K_3$ (dista $1$ da $4i$), quindi appartiene a $\mathcal{B}$, ma non sta sul bordo di tutti i cerchi.

**5. VERA.** Infatti $K_3$ è disgiunto dall'unione degli altri quattro cerchi, quindi $K_3$ contiene esattamente un autovalore di $A$ per il 2° teorema di G (con $k=1$), e gli altri $4$ stanno in $K_1\cup K_2\cup K_4\cup K_5$ (dove potrebbero anche stare, ad esempio, tutti in $K_4$). Inoltre questo autovalore non può stare sul bordo di $K_3$, perché ogni punto del bordo di $K_3$ è escluso dai possibili autovalori di $A$ grazie al 3° teorema di G debole (è lo stesso ragionamento fatto per $-1+4i$, che vale per tutti i punti della circonferenza di $K_3$). Quindi l'autovalore sta in $K_3$ privato del suo bordo.

**6.** Rimandata alla lezione successiva, perché un po' più impegnativa da scrivere.

> [!warning] Errore alla lavagna
> Nella risposta 5 il docente scrive prima "per il terzo teorema" e si corregge: che $K_3$ contenga esattamente un autovalore viene dal **secondo** teorema; il terzo serve solo a togliere il bordo.

> [!question] Domanda tipica d'esame
> Date le informazioni su una matrice irriducibile e i suoi cerchi di Gershgorin, dire se affermazioni del tipo "$z_0$ non è un autovalore", "$A$ è invertibile", "$z_0$ potrebbe essere un autovalore", "un cerchio privato del bordo contiene esattamente un autovalore" sono vere o false. Traccia: disegnare i cerchi e il bordo dell'unione $\mathcal{B}$; 1° teorema per dire dove possono stare gli autovalori; 2° teorema per contarli nelle componenti disgiunte; 3° teorema **debole** (solo se $A$ è irriducibile, da dichiarare) per escludere i punti di $\mathcal{B}$ che non stanno sul bordo di tutti i cerchi; per l'invertibilità, $A$ invertibile $\iff0$ non è autovalore.

> [!question] Domanda tipica d'esame
> Definire il grafo associato a una matrice e la matrice irriducibile; stabilire se una matrice data è irriducibile. Traccia: nodi $1,\dots,n$, arco $i\to j$ se e solo se $a_{ij}\neq0$; irriducibile se il grafo è fortemente connesso, cioè se esiste un ciclo che tocca tutti i nodi; costruire il grafo per righe e cercare il ciclo (o un nodo da cui non si può raggiungere un altro).

La lezione finisce qualche minuto prima (il punto 6 resta per la volta dopo): come al solito si finisce un po' prima il giovedì e si sfora un po' il martedì. Prossima lezione martedì.
## Esercizi sui teoremi di Gershgorin
Lezione 11 (10/11/2026): conclusione dell'esempio della lezione precedente (punto 6, raggio spettrale), un vero/falso su una matrice reale con l'argomento delle coppie complesse coniugate, ripresa dell'esempio del quadrifoglio (terzo teorema forte), cerchi per colonna tramite $A^T$ e un esempio completo di localizzazione "nel modo più preciso possibile".

Lezione del martedì, un po' più lunga di quella del giovedì; è sforata di circa venti minuti perché all'inizio bisognava finire il punto 6 dell'esempio rimasto in sospeso. Il docente annuncia che lezioni così lunghe non dovrebbero ripetersi, e che il giovedì si finisce un po' prima.

> [!info] Richiamo
> Gli enunciati dei tre teoremi di Gershgorin (il terzo in versione forte e debole) sono nella lezione precedente: [[03 - Analisi delle matrici#Primo teorema di Gershgorin]], [[03 - Analisi delle matrici#Secondo teorema di Gershgorin]], [[03 - Analisi delle matrici#Terzo teorema di Gershgorin (forte)]] e [[03 - Analisi delle matrici#Terzo teorema di Gershgorin (debole)]]. Con $\mathcal{C}(c,r)$ si indica il cerchio di centro $c$ e raggio $r$.

> [!warning] Il "patto segreto"
> Il docente ribadisce il patto: negli esercizi si applica **sempre e solo il terzo teorema debole**, mai quello forte ("ascoltate i consigli paterni"), perché a voler strafare con il forte si sbaglia. L'unica eccezione vista è l'esempio del quadrifoglio. Anche i testi degli esercizi delle dispense dicono "del terzo solo la versione debole". In ogni caso, per applicare il terzo teorema bisogna **prima verificare che $A$ sia irriducibile**: senza questa ipotesi non si può usare.

### Conclusione dell'esempio precedente (punto 6)
L'esempio, iniziato nella lezione 10:

> [!example] Esempio
> Supponiamo che una matrice $A\in\mathbb{C}^{5\times5}$ sia irriducibile e che i suoi cerchi di Gershgorin siano
> $$K_1=\mathcal{C}(1,1),\quad K_2=\mathcal{C}(-i,1),\quad K_3=\mathcal{C}(4i,1),\quad K_4=\mathcal{C}(1+i,1),\quad K_5=\mathcal{C}(-1,1)$$
> Avendo solo queste informazioni a disposizione, dire se le seguenti affermazioni sono vere o false, motivando la risposta.
> 1. $0$ non è un autovalore di $A$.
> 2. $A$ è invertibile.
> 3. $1$ potrebbe essere un autovalore di $A$.
> 4. $-1+4i$ potrebbe essere un autovalore di $A$.
> 5. $K_3$ privato del suo bordo contiene esattamente un autovalore di $A$.
> 6. $3<\rho(A)<5$.

I punti 1–5 sono stati risolti nella lezione 10; in particolare il punto 5 è **vero**: $K_3$ è isolato dagli altri cerchi, quindi contiene esattamente un autovalore (2° teorema), e tutto il suo bordo fa parte di $\mathcal{B}$ senza stare sul bordo di tutti i cerchi, quindi è escluso (3° teorema debole).

**6. VERA.** Uno studente ha l'idea giusta: tracciare (in azzurro) i cerchi di centro l'origine e raggio $3$ e $5$. Il punto $3i$ e il punto $5i$ hanno modulo $3$ e $5$ (il modulo è la distanza da $0$), e sono i punti di $K_3$ più vicino e più lontano dall'origine. Il cerchio piccolo $\mathcal{C}(0,3)$ contiene $K_1,K_2,K_4,K_5$; il cerchio grande $\mathcal{C}(0,5)$ contiene $K_3$.

Infatti
$$\rho(A)=\max\big(|\lambda_1|,|\lambda_2|,|\lambda_3|,|\lambda_4|,|\lambda_5|\big)$$
dove $\lambda_1,\dots,\lambda_5$ sono gli autovalori di $A$. Diciamo che $\lambda_3$ è quello (unico, per il punto 5) che sta in $K_3$. Allora:
- siccome $\lambda_1,\lambda_2,\lambda_4,\lambda_5$ stanno in $K_1\cup K_2\cup K_4\cup K_5\subset\mathcal{C}(0,3)$ privato del bordo (ci stanno strettamente dentro), si ha
$$|\lambda_1|,|\lambda_2|,|\lambda_4|,|\lambda_5|<3$$
- invece l'autovalore $\lambda_3$ sta fuori da $\mathcal{C}(0,3)$ (l'unico punto di contatto, $3i$, è sul bordo di $K_3$ ed è escluso), quindi $|\lambda_3|>3$;
- dunque è $\lambda_3$ a realizzare il raggio spettrale:
$$\rho(A)=|\lambda_3|>3$$
- infine $\lambda_3\in\mathcal{C}(0,5)$ privato del bordo: il cerchio grande tocca $K_3$ solo nel punto $5i$, che sta sul bordo (rosso) di $K_3$, tutto escluso dal punto 5. Quindi $\rho(A)=|\lambda_3|<5$. $\blacksquare$

### Esempio vero/falso: matrice reale
Il docente ama i vero/falso, ma **motivati**: senza motivazione sarebbero troppo facili (con due opzioni si indovina spesso), mentre motivare ogni risposta li rende esercizi impegnativi, possibili come esercizi di un tema d'esame.

> [!example] Esempio
> Supponiamo che $A\in\mathbb{R}^{4\times4}$ (quindi $a_{ij}\in\mathbb{R}$ per ogni $i,j=1,\dots,4$) e supponiamo che $A$ sia irriducibile con cerchi di Gershgorin
> $$K_1=\mathcal{C}(-3,2),\quad K_2=\mathcal{C}(-1,1),\quad K_3=\mathcal{C}(2,1),\quad K_4=\mathcal{C}(7,1)$$
> Avendo a disposizione solo queste informazioni, dire se le seguenti affermazioni sono vere o false e motivare la risposta.
> 1. $0$ non è un autovalore di $A$ e $A$ è invertibile.
> 2. Un autovalore di $A$ potrebbe trovarsi sul bordo di $K_3$.
> 3. Un autovalore di $A$ potrebbe trovarsi sul bordo di $K_2$.
> 4. Due autovalori di $A$ si trovano nell'unione $K_1\cup K_2$ privata del bordo, un autovalore di $A$ si trova nell'intervallo $(1,3)$ e un autovalore di $A$ si trova nell'intervallo $(6,8)$.
> 5. $6<\rho(A)<8$ e inoltre esiste un autovalore di $A$ esattamente uguale al raggio spettrale.

L'ipotesi $A\in\mathbb{R}^{4\times4}$ (componenti reali, nessuna componente complessa non reale) è sottolineata alla lavagna perché sarà **cruciale** per il punto 4.

**Figura.** Prima cosa da fare: il disegno nel piano complesso (asse orizzontale = parte reale, asse verticale = parte immaginaria; non è il piano cartesiano $\mathbb{R}^2$).
- $K_1$: centro $-3$, raggio $2$, tra $-5$ e $-1$;
- $K_2$: centro $-1$, raggio $1$, tra $-2$ e $0$;
- $K_3$: centro $2$, raggio $1$, tra $1$ e $3$;
- $K_4$: centro $7$, raggio $1$, tra $6$ e $8$.

$K_1$ e $K_2$ si intersecano; $K_3$ e $K_4$ sono isolati. Conviene segnare subito in rosso $\mathcal{B}$ = bordo di $K_1\cup K_2\cup K_3\cup K_4$.

> [!warning] Il bordo dell'unione, non dei singoli cerchi
> $\mathcal{B}$ è il bordo **dell'unione**: tutto il bordo di $K_3$ e di $K_4$ ne fa parte (sono separati dagli altri), ma l'arco del bordo di $K_2$ che sta dentro $K_1$ (segnato in blu alla lavagna) **non** fa parte di $\mathcal{B}$, e così l'arco del bordo di $K_1$ che sta dentro $K_2$.

**1. VERA.** Infatti $A$ è irriducibile ($\Rightarrow$ posso applicare il 3° teorema di Gershgorin debole). Inoltre $0\in\mathcal{B}$ (è il punto più a destra di $K_2$), ma $0$ non sta sul bordo di tutti i cerchi $\Rightarrow$ $0$ non è autovalore di $A$ per il 3° teorema debole, e $A$ è invertibile di conseguenza (una matrice è invertibile se e solo se $0$ non è un suo autovalore, [[03 - Analisi delle matrici#Matrici invertibili]]).

**2. FALSA.** Infatti ogni punto del bordo di $K_3$ è un punto di $\mathcal{B}$, ma non sta sul bordo di tutti i cerchi $\Rightarrow$ ogni punto del bordo di $K_3$ non può essere autovalore di $A$ ($A$ irriducibile) per il 3° teorema debole.

**3. VERA.** Infatti un autovalore di $A$ potrebbe trovarsi sulla parte blu del bordo di $K_2$, perché i punti della parte blu del bordo di $K_2$ non fanno parte di $\mathcal{B}$, e quindi non posso escluderli dai possibili autovalori di $A$. "Potrebbe": non è detto che ci sia, ma non si può escludere.

**4. VERA.** È il punto principale dell'esercizio: l'affermazione è la **migliore localizzazione possibile** degli autovalori di $A$ con le informazioni date. Se un esercizio chiede "la localizzazione migliore", la risposta attesa è proprio una frase come questa.

Il 2° teorema parla di **due** unioni disgiunte, ma qui le "isole" sono tre ($K_1\cup K_2$, $K_3$, $K_4$). Come suggerisce uno studente ("ricorsivamente"), basta applicarlo **due volte** con due raggruppamenti diversi:
- **(a)** Applicando il 2° teorema di Gershgorin prima alle unioni $\{K_1\cup K_2\cup K_3,\ K_4\}$ (un autovalore in $K_4$, tre negli altri) e poi alle unioni $\{K_1\cup K_2\cup K_4,\ K_3\}$ (un autovalore in $K_3$, tre negli altri), si deduce che
	- 2 autovalori di $A$ stanno in $K_1\cup K_2$ privato del bordo (rosso),
	- 1 autovalore di $A$ sta in $K_3$ privato del bordo (rosso),
	- 1 autovalore di $A$ sta in $K_4$ privato del bordo (rosso).
- **(b)** Applicando il 3° teorema di Gershgorin debole scopriamo "l'azzurro", cioè le precisazioni "privato del bordo (rosso)" scritte in azzurro sopra: tutto $\mathcal{B}$ va escluso per lo stesso motivo dei punti 1 e 2.

Resta da capire perché l'autovalore in $K_3$ sta nell'**intervallo reale** $(1,3)$, cioè perché è **reale**: non è affatto scontato.

> [!example] Una matrice reale può avere autovalori non reali
> Uno studente obietta che una matrice a componenti reali ha autovalori reali. **No**: sia
> $$B=\begin{bmatrix}0&1\\-1&0\end{bmatrix}\in\mathbb{R}^{2\times2}$$
> Il polinomio caratteristico è
> $$c_B(\lambda)=\det(\lambda I-B)=\begin{vmatrix}\lambda&-1\\1&\lambda\end{vmatrix}=\lambda^2+1$$
> che non ha radici reali. Con la formula risolutiva (che funziona sempre, anche se qui si poteva fare più in fretta):
> $$\lambda_{1,2}=\frac{-0\pm\sqrt{0^2-4}}{2}=\frac{\pm\sqrt{-4}}{2}=\frac{\pm2i}{2}=\pm i$$
> ($\sqrt{-4}=\sqrt{-1}\cdot\sqrt4=2i$, e infatti $(2i)^2=-4$). Nessuno dei due autovalori è reale: se i complessi non servissero, "non avrebbero ragione di esistere".

> [!warning] L'argomento più sbagliato all'esame
> Il docente lo dichiara "l'argomento che negli esami viene sbagliato più di tutti" (è al minuto 35 circa della registrazione). L'idea: se $A$ ha coefficienti **reali**, il polinomio caratteristico ha coefficienti reali, e le sue radici non reali compaiono **in coppie complesse coniugate**. Se l'autovalore in $K_3$ fosse non reale, ci sarebbe anche il suo coniugato, che starebbe anch'esso in $K_3$ (il centro è reale): due autovalori in $K_3$, impossibile. L'errore tipico: applicarlo a una matrice che ha **qualche componente complessa**. In quel caso "è finito tutto": il polinomio caratteristico non ha più coefficienti reali e l'argomento non vale.

Il seguito della dimostrazione del punto 4, come scritto alla lavagna:

**(c)** Il polinomio caratteristico di $A$ ha coefficienti reali perché $A$ ha coefficienti reali **per ipotesi** (l'ipotesi cruciale: senza, salta tutto). Di conseguenza, se $\lambda$ è un autovalore di $A$, anche $\bar\lambda$ è un autovalore di $A$, perché le radici (non reali) di un polinomio a coefficienti reali compaiono sempre in coppie complesse coniugate: non può esserci un numero senza il suo coniugato. È una regola senza eccezioni.

Infatti, se
$$p(x)=a_0+a_1x+a_2x^2+\dots+a_nx^n$$
è un polinomio a coefficienti reali $a_0,a_1,\dots,a_n\in\mathbb{R}$ e $\lambda$ è una radice di $p(x)$, allora anche $\bar\lambda$ è radice di $p(x)$, perché
$$p(\bar\lambda)=a_0+a_1\bar\lambda+a_2\bar\lambda^2+\dots+a_n\bar\lambda^n=\bar a_0+\bar a_1\bar\lambda+\bar a_2\overline{\lambda^2}+\dots+\bar a_n\overline{\lambda^n}=\overline{a_0+a_1\lambda+\dots+a_n\lambda^n}=\overline{p(\lambda)}=\bar0=0$$
- Nel secondo passaggio si usa $a_0,\dots,a_n\in\mathbb{R}$, quindi $a_k=\bar a_k$, e $\bar\lambda^k=\overline{\lambda^k}$.
- Nel terzo si usa che il coniugato di una somma è la somma dei coniugati e il coniugato di un prodotto è il prodotto dei coniugati.

Le proprietà usate, "nel ritaglino a margine": per ogni $z,w\in\mathbb{C}$
$$\overline{zw}=\bar z\,\bar w\quad\text{(esercizio)},\qquad\overline{z+w}=\bar z+\bar w$$
e quindi, applicandole ripetutamente,
$$\overline{z^3}=\overline{z\cdot z\cdot z}=\overline{z\cdot z}\cdot\bar z=\bar z\cdot\bar z\cdot\bar z=\bar z^3$$
e lo stesso vale per ogni potenza: $\overline{z^k}=\bar z^k$.

**Esercizio** (dalla lezione). Dimostrare che $\overline{zw}=\bar z\,\bar w$ per ogni $z,w\in\mathbb{C}$. Suggerimento: scrivere $z=a+ib$, $w=c+id$ e fare i conti (non è così ovvio, va fatto un attimo di conto).

**(d)** L'autovalore $\lambda_3$ di $A$ che si trova in $K_3$ è per forza reale (e quindi sta in $(1,3)$: un numero reale di $K_3$ privato del bordo sta nel segmento dell'asse reale dentro $K_3$, estremi $1$ e $3$ esclusi). Infatti, se $\lambda_3$ non fosse reale, allora $\bar\lambda_3\neq\lambda_3$ e $\bar\lambda_3$ sarebbe un altro autovalore di $A$ (per il punto (c)), e $\bar\lambda_3\in K_3$, perché $\bar\lambda_3$ è il riflesso di $\lambda_3$ rispetto all'asse reale e $K_3$ ha centro reale, quindi è simmetrico rispetto all'asse reale. Per cui avremmo che $K_3$ contiene 2 autovalori di $A$; ciò non è possibile per il 2° teorema di Gershgorin.

**(e)** L'autovalore $\lambda_4$ di $A$ che si trova in $K_4$ è per forza reale (e quindi sta in $(6,8)$), per lo stesso motivo di $\lambda_3$. $\blacksquare$

> [!info] Riflessione rispetto a quale asse
> A voce il docente dice una volta "riflessione rispetto all'asse immaginario", ma il disegno alla lavagna e la frase successiva ("rispetto all'asse $x$, l'asse delle ascisse") chiariscono: il coniugato $\bar z$ è il riflesso di $z$ rispetto all'**asse reale**.

> [!info] Perché non vale per $K_1\cup K_2$ (nostra aggiunta)
> L'argomento funziona per $K_3$ e $K_4$ perché ciascuno contiene **un solo** autovalore. In $K_1\cup K_2$ ce ne sono due, che possono benissimo essere una coppia $\mu,\bar\mu$ non reale: per questo l'affermazione 4 non dice nulla di più su di loro.

**5. VERA.** Uno studente risponde subito: l'autovalore in $K_4$ è reale, sta in $(6,8)$, quindi è positivo e il suo modulo è lui stesso. Infatti, per lo stesso discorso dell'esempio precedente (punto 6), tracciando i cerchi di centro l'origine e raggio $6$ e $8$ (in azzurro alla lavagna): $K_1\cup K_2\cup K_3$ sta dentro $\mathcal{C}(0,6)$, quindi gli altri tre autovalori hanno modulo $<6$, mentre $\lambda_4\in(6,8)$. L'autovalore $\lambda_4\in(6,8)$ è dunque tale che
$$\rho(A)=|\lambda_4|=\lambda_4\in(6,8)$$
dove $|\lambda_4|=\lambda_4$ perché $\lambda_4$ è reale $>0$. Quindi $6<\rho(A)<8$ e l'autovalore $\lambda_4$ è esattamente uguale al raggio spettrale. $\blacksquare$

> [!info] Organizzazione: gli appunti all'esame
> All'esame si possono usare gli **appunti presi a lezione**, ma **non la tavoletta** (né altri dispositivi, che potrebbero servire a comunicare): l'esame si fa su fogli di carta, con la penna. Chi prende appunti su tablet può esportarli in PDF e stamparli.

### Esempio del quadrifoglio (ripreso)
Esempio già visto nella lezione 10, ripreso perché è l'unico caso in cui serve il terzo teorema **forte**.

> [!example] Esempio (quadrifoglio)
> Supponiamo che una matrice $A\in\mathbb{C}^{5\times5}$ sia irriducibile e che i suoi cerchi di Gershgorin siano
> $$K_1=\mathcal{C}(1,1),\quad K_2=\mathcal{C}(i,1),\quad K_3=\mathcal{C}(-1,1),\quad K_4=\mathcal{C}(-i,1),\quad K_5=\mathcal{C}(1,\tfrac14)$$
> Dimostrare che $A$ è invertibile.

$K_1,\dots,K_4$ sono le quattro foglie (verdi), che passano tutte per l'origine; $K_5$ è la "foglia mangiata dal baco", un cerchietto (rosso) dentro $K_1$.

**Una possibile $A$.** Esiste davvero una matrice con questi cerchi (non è l'unica):
$$A=\begin{bmatrix}1&1&0&0&0\\0&i&1&0&0\\0&0&-1&1&0\\0&0&0&-i&1\\\frac14&0&0&0&1\end{bmatrix}$$
I centri dei cerchi danno gli elementi diagonali ($1,i,-1,-i,1$); ogni riga ha un solo elemento fuori diagonale, di modulo pari al raggio ($1,1,1,1,\frac14$). L'$\frac14$ va messo **nell'angolino** in basso a sinistra (e non, ad esempio, accanto alla diagonale) per avere l'irriducibilità. Il grafo di $A$ ha gli archi $i\to i$ (elementi diagonali non nulli) e
$$1\to2\to3\to4\to5\to1$$
che è un ciclo che tocca tutti i nodi $\Rightarrow$ $A$ è irriducibile.

**Soluzione.** Devo dimostrare che $0$ non è autovalore di $A$. Uso il 3° teorema di Gershgorin **forte** per escludere lo $0$ dai possibili autovalori di $A$ (non posso usare il 3° teorema debole perché $0\notin\mathcal{B}$ = bordo dell'unione $K_1\cup K_2\cup K_3\cup K_4\cup K_5$: lo $0$ è il centro del quadrifoglio, all'interno dell'unione, e il teorema debole riguarda solo i punti di $\mathcal{B}$). Verifico le due ipotesi:
- **$0$ sta sul bordo di tutti quei cerchi a cui appartiene?** Sì, perché $0$ appartiene a $K_1,K_2,K_3,K_4$ e sta sul bordo di essi.
- **È vero che $0$ non sta sul bordo di tutti i cerchi?** Sì, perché $0\notin\partial K_5$.

$\Rightarrow$ per il 3° teorema di Gershgorin forte, $0$ non è autovalore di $A$, e quindi $A$ è invertibile. $\blacksquare$

> [!info] Il simbolo $\partial$
> Il bordo di un insieme $K$ si indica con $\partial K$, lo stesso simbolo (una "d storta") delle derivate parziali $\frac{\partial f}{\partial x}$.

> [!info] Osservazione: senza la foglia mangiata (detta solo a voce, è anche nelle dispense)
> Se togliamo $K_5$, cioè $A\in\mathbb{C}^{4\times4}$ con i soli cerchi $K_1,\dots,K_4$, lo $0$ **non** si può escludere: verifica la prima ipotesi (sta sul bordo di tutti i cerchi a cui appartiene), ma non la seconda, perché ora $0$ sta sul bordo di tutti i cerchi. È proprio $K_5$, che non passa per lo $0$, a permettere di applicare il teorema.

### Cerchi per colonna: Gershgorin applicato ad $A^T$
> [!quote] Osservazione
> Gli autovalori di una matrice $A\in\mathbb{C}^{n\times n}$ e della sua trasposta $A^T$ coincidono, perché i polinomi caratteristici di $A$ e $A^T$ coincidono:
> $$c_{A^T}(\lambda)=\det(\lambda I-A^T)=\det\big((\lambda I)^T-A^T\big)=\det\big((\lambda I-A)^T\big)=\det(\lambda I-A)=c_A(\lambda)$$

I passaggi:
- $(\lambda I)^T=\lambda I$: la trasposta di una matrice diagonale è se stessa (gli elementi diagonali restano fermi);
- $(B+C)^T=B^T+C^T$ (e lo stesso per la differenza, che è una somma con $-C$): "un'ovvietà";
- $\det(B^T)=\det(B)$, visto nei richiami di algebra lineare ([[03 - Analisi delle matrici#Teorema di Binet e determinante della trasposta]]). "Si possono non ricordare le cose dei corsi precedenti, però non si può non ricordare le cose del mio corso."

Quindi possiamo applicare i teoremi di Gershgorin non solo ad $A$ ma anche ad $A^T$, per ottenere una localizzazione migliore degli autovalori di $A$.

Le righe di $A^T$ sono le colonne di $A$: il primo cerchio di Gershgorin (per riga) di $A^T$ si costruisce con la prima colonna di $A$, e così via. I cerchi di Gershgorin $H_1,\dots,H_n$ di $A^T$ sono quindi i **cerchi di Gershgorin per colonna** di $A$ (la notazione $H$ è quella già usata per i cerchi per colonna). Quando non si specifica, "cerchi di Gershgorin" vuol dire quelli per riga.

> [!quote] Primo teorema di Gershgorin per righe e per colonne
> Gli autovalori di una matrice $A\in\mathbb{C}^{n\times n}$ stanno tutti **sia** nell'unione dei cerchi di Gershgorin $K_1,\dots,K_n$ di $A$, **sia** nell'unione dei cerchi di Gershgorin per colonna $H_1,\dots,H_n$ di $A$; quindi stanno tutti nell'intersezione delle 2 unioni
> $$(K_1\cup K_2\cup\dots\cup K_n)\cap(H_1\cup H_2\cup\dots\cup H_n)$$

> [!warning] Prima le unioni, poi l'intersezione
> L'intersezione è l'operazione **finale** (per questo le parentesi): prima si costruisce l'unione dei $K$, poi l'unione degli $H$, e solo alla fine si intersecano i due insiemi. **Non** si fa $K_1\cap H_1$, $K_2\cap H_2$, ecc. Il trucco del docente, che consiglia di venire all'esame **con i pastelli**: colorare di **blu** l'unione dei $K$, poi di **giallo** l'unione degli $H$; dove si vede **verde** c'è l'intersezione.

Per una localizzazione il più precisa possibile vanno applicati ad $A^T$ anche il 2° e il 3° teorema. Per il 3° serve l'irriducibilità di $A^T$:

> [!quote] Sotto-osservazione
> In vista dell'applicazione del 3° teorema di Gershgorin ad $A^T$, notiamo che
> $$A\in\mathbb{C}^{n\times n}\text{ è irriducibile}\iff A^T\text{ è irriducibile}$$

Basta dimostrare un'implicazione ($\Rightarrow$): l'altra segue applicandola ad $A^T$, perché $(A^T)^T=A$.

**Esercizio** (dalla lezione). Dimostrare l'equivalenza. Suggerimento del docente: trasporre la matrice **inverte il verso degli archi** del grafo. Ad esempio, con
$$A=\begin{bmatrix}1&2&0\\5&0&7\\0&0&0\end{bmatrix},\qquad A^T=\begin{bmatrix}1&5&0\\2&0&0\\0&7&0\end{bmatrix}$$
l'elemento $7$ in posizione $(2,3)$ di $A$ dà l'arco $2\to3$; in $A^T$ passa in posizione $(3,2)$ e dà l'arco $3\to2$. Il docente avverte che all'orale potrebbe chiedere anche gli esercizi assegnati.

### Esempio: localizzazione nel modo più preciso possibile
> [!example] Esempio
> Sia
> $$A=\begin{bmatrix}7&2&2&2\\0&-1&0&\frac12\\0&0&1&\frac i2\\1&0&-1&-i\end{bmatrix}$$
> - (a) Localizzare lo spettro di $A$ nel modo più preciso possibile.
> - (b) Sulla base delle informazioni spettrali ottenute, dimostrare che $\alpha I+A$ è invertibile $\forall\alpha\geq2$.

Il punto (a) è una tipica domanda da tema d'esame. Lo **spettro** di $A$ è l'insieme dei suoi autovalori (qui 4, eventualmente ripetuti).

#### (a) Localizzazione
Dovendo localizzare lo spettro di $A$ nel modo più preciso possibile, consideriamo sia i cerchi di Gershgorin per riga che quelli per colonna (cioè applichiamo i teoremi anche ad $A^T$): limitarsi ai cerchi per riga non darebbe la localizzazione migliore.

| Per riga | Per colonna |
|---|---|
| $K_1=\mathcal{C}(7,6)$ | $H_1=\mathcal{C}(7,1)$ |
| $K_2=\mathcal{C}(-1,\frac12)$ | $H_2=\mathcal{C}(-1,2)$ |
| $K_3=\mathcal{C}(1,\frac12)$ | $H_3=\mathcal{C}(1,3)$ |
| $K_4=\mathcal{C}(-i,2)$ | $H_4=\mathcal{C}(-i,3)$ |

I centri degli $H$ sono gli stessi dei $K$ (sono sempre gli elementi diagonali); cambiano solo i raggi. Ad esempio:
- $K_1$: raggio $|2|+|2|+|2|=6$;
- $K_3$: raggio $|\frac i2|=\sqrt{0^2+(\frac12)^2}=\frac12$, con $|a+ib|=\sqrt{a^2+b^2}$ ("ve lo dico tante volte, ma mi sembra che non vi entra nella mente");
- $K_4$: raggio $|1|+|0|+|-1|=2$, **non** $0$: si sommano i **moduli**, non gli elementi;
- $H_1$: raggio $|0|+|0|+|1|=1$; $H_3$: $|2|+|0|+|-1|=3$; $H_4$: $|2|+|\frac12|+|\frac i2|=3$.

**Applicazione 1° teorema di G (ad $A$ e $A^T$, cioè "per righe e per colonne").** Gli autovalori di $A$ stanno in
$$(K_1\cup K_2\cup K_3\cup K_4)\cap(H_1\cup H_2\cup H_3\cup H_4)=\text{insieme verde in figura}$$
La figura (preparata dal docente al calcolatore e incollata sulla lavagna) ha in blu i cerchi per riga e in giallo quelli per colonna: il grande cerchio blu $K_1$ (da $1$ a $13$ sull'asse reale), il piccolo $H_1$ isolato intorno a $7$ (da $6$ a $8$), e a sinistra un gruppo di cerchi intorno all'origine ($K_2,K_3,K_4,H_2,H_3,H_4$). L'insieme verde è formato da $H_1$ (che sta tutto dentro $K_1$) e da una regione intorno all'origine.

> [!warning] Dire qual è l'intersezione
> All'esame non basta scrivere "gli autovalori stanno nell'intersezione delle due unioni": è un risultato generale, che vale sempre. Bisogna dire **concretamente** qual è l'intersezione in quel caso (va bene anche "insieme verde in figura", con la figura), altrimenti non si dimostra di aver capito.

**Applicazione 2° teorema di G (ad $A$ e $A^T$).**
- Il 2° teorema di G non si può applicare a $K_1,K_2,K_3,K_4$ (non ci sono unioni disgiunte): l'unione dei cerchi blu è un unico blocco connesso.
- Il 2° teorema di G applicato ai cerchi $H_1,H_2,H_3,H_4$ (cioè ad $A^T$) ci dice che 1 autovalore di $A$ sta in $H_1$ e 3 autovalori di $A$ in $H_2\cup H_3\cup H_4$ (cioè nella **parte verde** di $H_2\cup H_3\cup H_4$: l'informazione del 1° teorema resta valida, non si può uscire dal verde).

Gli autovalori di $A^T$ sono quelli di $A$, quindi le conclusioni su $A^T$ valgono per $A$.

**Applicazione 3° teorema di G debole (ad $A$ e $A^T$).** $A$ è irriducibile perché il suo grafo (righe: $1\to1,2,3,4$; $2\to2,4$; $3\to3,4$; $4\to1,3,4$) contiene
$$1\to2\to4\to3\to4\to1$$
ciclo che tocca tutti i nodi: grafo fortemente connesso. Quindi anche $A^T$ è irriducibile, per l'esercizio.

3° teorema debole applicato ad $A$: siccome nessun punto del bordo di $K_1\cup K_2\cup K_3\cup K_4$ sta sul bordo di tutti i cerchi $K_1,K_2,K_3,K_4$ (ad esempio non sta sul bordo dei due cerchietti $K_2,K_3$ contenuti all'interno), nessun punto del bordo di $K_1\cup K_2\cup K_3\cup K_4$ può essere autovalore di $A$.

3° teorema debole applicato ad $A^T$: allo stesso modo nessun punto del bordo di $H_1\cup H_2\cup H_3\cup H_4$ sta sul bordo di tutti i cerchi $H_1,\dots,H_4$ (ad esempio per via di $H_1$, isolato), quindi nessun punto del bordo di $H_1\cup H_2\cup H_3\cup H_4$ può essere autovalore di $A^T$, cioè di $A$.

Il bordo della regione verde è fatto in parte da archi del bordo dell'unione blu e in parte da archi del bordo dell'unione gialla (alla lavagna il docente li tratteggia di colori diversi): il primo passaggio esclude i primi, il secondo esclude gli altri (compreso tutto il bordo di $H_1$). Il resto dei bordi esclusi sta già fuori dal verde e non interessa. Usando prima le righe e poi le colonne si esclude così **tutto** il bordo della regione verde.

**Conclusione.** Gli autovalori di $A$ stanno nella regione verde in figura privata del bordo; più precisamente 1 autovalore sta in $H_1$ privato del bordo e 3 autovalori stanno nell'altra parte verde (quella intorno all'origine), privata del bordo.

> [!warning] Da verificare
> La figura non è riproducibile qui; il docente consiglia di non perdere tempo a ridisegnarla a mano (la si trova verso la fine della registrazione, il docente cita le 16:56). Dalle formule (nostra aggiunta): la parte verde a sinistra è $(K_2\cup K_3\cup K_4)\cap(H_2\cup H_3\cup H_4)$ unita a $K_1\cap(H_2\cup H_3\cup H_4)$, e il suo punto più a sinistra è $-2-i$ (punto più a sinistra di $K_4$, che sta dentro $H_2\cup H_4$). Conviene ricontrollare sulla figura delle dispense o della registrazione.

#### (b) Invertibilità di $\alpha I+A$
Alla lavagna si traccia la retta **verticale** nera che passa per $-2$ (a voce il docente la chiama una volta "orizzontale"): la regione verde si trova tutta a destra di questa retta.

Gli autovalori di $\alpha I+A=p(A)$, con $p(\lambda)=\alpha+\lambda$, sono
$$\alpha+\lambda_1,\quad\alpha+\lambda_2,\quad\alpha+\lambda_3,\quad\alpha+\lambda_4$$
dove $\lambda_1,\lambda_2,\lambda_3,\lambda_4$ sono gli autovalori di $A$: ho applicato il teorema sui polinomi di matrici (gli autovalori di $p(A)$ sono i $p(\lambda_i)$; è l'unico teorema sui polinomi di matrici visto nel corso).

Siccome gli autovalori stanno nella regione verde privata del bordo, essi stanno tutti a destra della retta nera, e quindi hanno parte reale $>-2$ (strettamente: il bordo è escluso). $\Rightarrow$ $\forall i=1,2,3,4$
$$\operatorname{Re}(\alpha+\lambda_i)=\underbrace{\operatorname{Re}(\alpha)}_{\geq2}+\underbrace{\operatorname{Re}(\lambda_i)}_{>-2}>2-2=0\ \Rightarrow\ \alpha+\lambda_i\neq0\quad\forall i=1,2,3,4\quad(\text{se }\alpha\geq2)$$
(la parte reale di una somma è la somma delle parti reali, [[03 - Analisi delle matrici#Esempio: autovalori dalla traccia]]; $\alpha\geq2$ è l'ipotesi, senza la quale cade tutto).

$\Rightarrow$ se $\alpha\geq2$ allora $\alpha I+A$ non ha $0$ come autovalore, e dunque è invertibile. $\blacksquare$

> [!info] Soluzione alternativa (proposta da uno studente)
> Si possono guardare direttamente i cerchi di Gershgorin di $\alpha I+A$: sommare $\alpha I$ cambia solo gli elementi diagonali, quindi i cerchi hanno gli stessi raggi e i centri **spostati a destra** di $\alpha$. Il docente la accetta; ha preferito sfruttare i cerchi già disegnati e mostrare lo spostamento sulla parte reale degli autovalori.

### Esercizi
Il docente consiglia di cominciare da questi due, propedeutici all'esame (quelli d'esame sono un po' più difficili, con qualche dettaglio in più); il secondo "non è così semplice" e potrebbe stare in un esame. Altri esercizi si trovano nei temi d'esame sulla pagina web del docente, spostata su **GitHub** per via dei continui attacchi hacker al sito precedente (le "57 pagine per le vacanze di Natale").

**Esercizio 3.10.** Si consideri la matrice
$$A=\begin{bmatrix}2&i&0&0&0\\0&2&i&0&0\\0&0&2&i&0\\0&0&0&2&i\\\frac1{10}&\frac12&\frac12&1&2\end{bmatrix}$$
- (a) Usando i teoremi di Gershgorin (del terzo solo la versione debole), localizzare lo spettro di $A$ nel modo più preciso possibile.
- (b) Sulla base delle informazioni spettrali ottenute, è possibile dire se $A$ è invertibile oppure no?
- (c) Sulla base delle informazioni spettrali ottenute, fornire la stima più precisa possibile per il raggio spettrale $\rho(A)$.

**Esercizio 3.11.** Sia data la matrice $A\in\mathbb{C}^{n\times n}$ di elementi $a_{jj}=3$ per $j=1,\dots,n$, $a_{jk}=-1$ per $j,k\geq2$ con $|j-k|=1$, $a_{1k}=a_{k1}=1/2^k$ per $k=2,\dots,n$, e $a_{jk}=0$ per tutte le altre coppie di indici $(j,k)$.
- (a) Usando i teoremi di Gershgorin (del terzo solo la versione debole), localizzare lo spettro di $A$ nel modo più preciso possibile.
- (b) Sulla base delle informazioni spettrali ottenute, dimostrare che la matrice $A$ è invertibile. È vero che $A$ è definita positiva?

> [!question] Domanda tipica d'esame
> Data una matrice irriducibile **reale** di cui si conoscono solo i cerchi di Gershgorin, alcuni dei quali isolati e con centro reale, fornire la migliore localizzazione possibile degli autovalori (o dire se affermazioni del tipo "un autovalore sta nell'intervallo $(a,b)$" sono vere o false, motivando). Traccia: disegno e bordo $\mathcal{B}$ dell'unione; 2° teorema applicato più volte con raggruppamenti diversi per contare gli autovalori in ogni componente; 3° teorema debole per togliere $\mathcal{B}$ (dopo aver verificato l'irriducibilità); per un cerchio isolato con centro reale che contiene un solo autovalore: $A$ reale $\Rightarrow$ polinomio caratteristico a coefficienti reali $\Rightarrow$ autovalori non reali in coppie coniugate, e $\bar\lambda$ starebbe nello stesso cerchio $\Rightarrow$ l'autovalore è reale; dimostrare che $p(\bar\lambda)=\overline{p(\lambda)}$ per $p$ a coefficienti reali.

> [!question] Domanda tipica d'esame
> Data una matrice $A$, localizzarne lo spettro nel modo più preciso possibile con i teoremi di Gershgorin (del terzo solo la versione debole) e usare la localizzazione per dedurre l'invertibilità di $A$ o di una matrice come $\alpha I+A$, o una stima di $\rho(A)$. Traccia: cerchi per riga $K_i$ e per colonna $H_i$ (= cerchi di $A^T$, che ha gli stessi autovalori perché $c_{A^T}=c_A$); 1° teorema: intersezione delle due unioni, descritta concretamente; 2° teorema per righe e per colonne; verificare l'irriducibilità di $A$ (quindi di $A^T$) e applicare il 3° teorema debole a entrambe per togliere il bordo della regione; per $\alpha I+A$: autovalori $\alpha+\lambda_i$ (polinomi di matrici) e $\operatorname{Re}(\alpha+\lambda_i)=\operatorname{Re}(\alpha)+\operatorname{Re}(\lambda_i)$.

La lezione finisce con lo sforamento annunciato; ci si rivede il giovedì, con una lezione un po' più corta.
## Matrici a diagonale dominante e norme vettoriali
Lezione 12 (12/11/2026): matrici a diagonale dominante (per righe e per colonne, anche in senso stretto) lette con i cerchi di Gershgorin, teorema di invertibilità con dimostrazione tramite il terzo teorema di Gershgorin forte, poi norme vettoriali, la loro equivalenza e la convergenza delle successioni di vettori.

Finiti i teoremi di Gershgorin sulla localizzazione degli autovalori (lezioni 10 e 11, [[03 - Analisi delle matrici#Matrici irriducibili e teoremi di Gershgorin]] e [[03 - Analisi delle matrici#Esercizi sui teoremi di Gershgorin]]), la lezione comincia con un argomento collegato ai cerchi: le **matrici a diagonale dominante**. Seguono l'unico teorema del corso in cui serve il terzo teorema di Gershgorin in versione **forte** e poi un argomento del tutto nuovo, le **norme vettoriali**. Il docente avverte che sono argomenti facili: la parte più difficile è saper calcolare i moduli dei numeri complessi.

Si ricorda la notazione dei cerchi di Gershgorin, che alla lavagna resta sulla destra: il cerchio per riga $i$ è
$$K_i=\mathcal{G}\Big(a_{ii},\sum_{\substack{j=1\\j\neq i}}^n|a_{ij}|\Big)$$
cioè il cerchio di centro $a_{ii}$ e raggio uguale alla somma dei moduli degli altri elementi della riga $i$. I cerchi per colonna si indicano con $H_1,\dots,H_n$.
### Matrici a diagonale dominante
#### Definizioni
> [!quote] Definizione (matrice a diagonale dominante e a diagonale dominante in senso stretto)
> Sia $A\in\mathbb{C}^{n\times n}$.
> - Si dice che $A$ è **a diagonale dominante (per righe)** se
>   - (a) $\displaystyle|a_{ii}|\geq\sum_{\substack{j=1\\j\neq i}}^n|a_{ij}|\quad\forall i=1,\dots,n$;
>   - (b) $\displaystyle\exists k\in\{1,\dots,n\}$ t.c. $\displaystyle|a_{kk}|>\sum_{\substack{j=1\\j\neq k}}^n|a_{kj}|$.
> - Si dice che $A$ è **a diagonale dominante per colonne** se
>   - (a') $\displaystyle|a_{jj}|\geq\sum_{\substack{i=1\\i\neq j}}^n|a_{ij}|\quad\forall j=1,\dots,n$;
>   - (b') $\displaystyle\exists k\in\{1,\dots,n\}$ t.c. $\displaystyle|a_{kk}|>\sum_{\substack{i=1\\i\neq k}}^n|a_{ik}|$.
> - Si dice che $A$ è **a diagonale dominante in senso stretto (per righe)** se
>   $$|a_{ii}|>\sum_{\substack{j=1\\j\neq i}}^n|a_{ij}|\qquad\forall i=1,\dots,n$$
> - Si dice che $A$ è **a diagonale dominante in senso stretto per colonne** se
>   $$|a_{jj}|>\sum_{\substack{i=1\\i\neq j}}^n|a_{ij}|\qquad\forall j=1,\dots,n$$

In parole: nella diagonale dominante (per righe), su **ogni** riga il modulo dell'elemento diagonale è maggiore o uguale della somma dei moduli degli altri elementi della riga, e su **almeno una** riga vale il maggiore stretto. In senso stretto, il maggiore stretto vale su **tutte** le righe. Per le colonne si scambiano i ruoli di $i$ e $j$.

"Per righe" è tra parentesi perché, come per i cerchi di Gershgorin, se non si dice niente si intende per righe; "per colonne" invece va **sempre** specificato. Si abbrevia "diagonale dominante" con **d.d.**

Ovviamente una matrice a d.d. in senso stretto (per righe o per colonne) è anche a d.d. (per righe o per colonne, rispettivamente).
#### Lettura con i cerchi di Gershgorin
Le definizioni sono date apposta pensando ai cerchi di Gershgorin. La sommatoria $\sum_{j\neq i}|a_{ij}|$ è il **raggio** di $K_i$, mentre $|a_{ii}|$, il modulo del **centro**, è la **distanza del centro dall'origine** (il modulo di un numero complesso è la sua distanza dall'origine). Quindi la disuguaglianza $|a_{ii}|\geq\text{raggio}$ dice che lo $0$ non sta all'interno di $K_i$ (al massimo sul bordo), e $|a_{ii}|>\text{raggio}$ dice che $K_i$ non contiene lo $0$. Le condizioni si traducono così (in rosso e in verde alla lavagna):
- (a): **nessuno** dei cerchi di Gershgorin $K_1,\dots,K_n$ contiene lo $0$ al suo interno (al limite $0$ può stare sul bordo);
- (b): il cerchio di Gershgorin $K_k$ **non contiene** lo $0$;
- (a'): nessuno dei cerchi di Gershgorin per colonna $H_1,\dots,H_n$ contiene lo $0$ al suo interno (al limite $0$ può stare sul bordo);
- (b'): il cerchio di Gershgorin per colonna $H_k$ non contiene lo $0$;
- d.d. in senso stretto (per righe): **nessun** cerchio di Gershgorin contiene lo $0$, nemmeno sul bordo;
- d.d. in senso stretto per colonne: nessuno dei cerchi di Gershgorin per colonna contiene lo $0$.

> [!info] All'orale
> Quando all'orale il docente chiede la definizione di matrice a diagonale dominante, si può dare a scelta quella con gli indici ("brutta") oppure quella geometrica con i cerchi di Gershgorin.

> [!warning] Il pedice $k$
> Nella condizione (b) il cerchio è $K_k$: la $K$ maiuscola è il nome del cerchio, la $k$ minuscola al pedice è l'indice della riga. Il docente la scrive in modo calligrafico per non confonderle.
#### Esempio
> [!example] Esempio
> Discutere le proprietà di dominanza diagonale per righe e per colonne di
> $$A=\begin{bmatrix}3&1&-2\\0&-3&1\\1-2i&-1&5\end{bmatrix}$$

**Righe.**
$$|3|=|1|+|-2|=3$$
$$|-3|>|0|+|1|=1$$
$$|5|>|1-2i|+|-1|=\sqrt5+1$$
dove $|1-2i|=\sqrt{1^2+(-2)^2}=\sqrt5\approx2{,}2$. Vale il $\geq$ su tutte le righe e il $>$ su almeno una (anzi su due), ma sulla prima riga vale l'uguale. Quindi $A$ è a d.d. per righe ma **non** a d.d. in senso stretto per righe.

**Colonne.**
$$|3|>|0|+|1-2i|=\sqrt5$$
$$|-3|>|1|+|-1|=2$$
$$|5|>|-2|+|1|=3$$
Il maggiore stretto vale su tutte le colonne, quindi $A$ è a d.d. in senso stretto per colonne (e quindi anche a d.d. per colonne).

Su domanda di uno studente, in termini di cerchi: dove vale l'uguale (la prima riga) il cerchio $K_1$ ha lo $0$ **sul bordo**; dove vale il maggiore stretto (le altre due righe) il cerchio corrispondente non contiene affatto lo $0$. Per colonne, nessuno dei cerchi $H_1,H_2,H_3$ contiene lo $0$.
### Teorema di invertibilità per le matrici a diagonale dominante
È l'**unico teorema del corso** in cui serve il **terzo teorema di Gershgorin in versione forte**. Alcuni docenti presentano solo la versione debole, ma allora questo teorema non si può dimostrare (o se ne può dimostrare solo una versione più debole). Dopo questo teorema la versione forte si può dimenticare: **negli esercizi si usa solo quella debole**.

> [!quote] Teorema
> Supponiamo che la matrice $A\in\mathbb{C}^{n\times n}$ soddisfi almeno una di queste condizioni:
> - $A$ è a d.d. e irriducibile;
> - $A$ è a d.d. in senso stretto;
> - $A$ è a d.d. per colonne e irriducibile;
> - $A$ è a d.d. in senso stretto per colonne.
>
> Allora $A$ è invertibile.

Richiamo chiesto alla classe: $A$ è **irriducibile** quando il grafo associato ad $A$ è **fortemente connesso**. Il docente lo descrive come "c'è un ciclo che tocca tutti i nodi".

> [!info] Le due definizioni coincidono
> Nella [[03 - Analisi delle matrici#Matrici irriducibili|lezione 10]] "fortemente connesso" è definito come "per ogni coppia di nodi $i,j$ c'è un cammino da $i$ a $j$", ed equivalentemente "c'è un ciclo che tocca tutti i nodi", dove il ciclo può ripassare più volte per lo stesso nodo. Con questa convenzione le due condizioni sono equivalenti.

Che $A$ sia invertibile equivale a dire che **$0$ non è un autovalore** di $A$ ([[03 - Analisi delle matrici#Matrici invertibili]]): è questo che si dimostra.
#### Dimostrazione
Nel caso in cui $A$ soddisfi la **prima** ipotesi (d.d. e irriducibile); la dimostrazione negli altri casi è un esercizio.

Devo dimostrare che $0$ non è un autovalore di $A$. Uso il terzo teorema di Gershgorin forte.

L'ipotesi che $A$ sia a d.d. mi dice che:
- $0$ sta sul bordo di quei cerchi di Gershgorin a cui appartiene. Infatti per la condizione (a) vale $|a_{ii}|\geq\sum_{j\neq i}|a_{ij}|$ su tutte le righe: nessun cerchio $K_i$ contiene lo $0$ al suo interno, quindi se $0$ appartiene a un cerchio ci sta sul bordo;
- $0$ non sta sul bordo di tutti i cerchi: infatti per la condizione (b) esiste un cerchio $K_k$ in cui $0$ non ci sta proprio (né dentro né sul bordo).

Sono le due ipotesi del terzo teorema di Gershgorin forte. Siccome $A$ è irriducibile (l'altra ipotesi del teorema, senza la quale non lo si può applicare), per il terzo teorema di Gershgorin forte $0$ non è autovalore di $A$. Quindi $A$ è invertibile. $\blacksquare$

**Esercizio** (dalla lezione). Dimostrare il teorema negli altri tre casi.

> [!info] Gli altri casi (nostra aggiunta)
> Per **d.d. per colonne e irriducibile** si ripete la stessa dimostrazione con i cerchi per colonna $H_1,\dots,H_n$ (oppure si applica il primo caso ad $A^T$, che ha gli stessi autovalori di $A$, ha come cerchi per riga i cerchi per colonna di $A$ ed è irriducibile se e solo se lo è $A$). Per **d.d. in senso stretto** basta il terzo teorema di Gershgorin **debole**, o anche il primo: nessun cerchio contiene lo $0$, quindi $0$ non sta nell'unione dei cerchi e non può essere un autovalore; lo stesso per colonne con i cerchi $H_i$.
#### Osservazione: perché serve la versione forte
Usando solo il terzo teorema di Gershgorin debole questo teorema non si potrebbe dimostrare. Lo mostra l'esempio del **quadrifoglio** visto nella lezione precedente, riscritto alla lavagna:
$$A=\begin{bmatrix}1&1&&&\\&i&1&&\\&&-1&1&\\&&&-i&1\\\frac14&&&&1\end{bmatrix}$$
(gli elementi non scritti sono nulli).
- È **irriducibile**: l'elemento $(1,2)$ dice che da $1$ si va in $2$, l'elemento $(2,3)$ che da $2$ si va in $3$, poi $(3,4)$ da $3$ a $4$, $(4,5)$ da $4$ a $5$ e infine $(5,1)$ da $5$ si torna in $1$. Anche se ci sono tanti zeri, gli elementi non nulli stanno nelle posizioni giuste.
- È **a d.d.** sia per righe che per colonne, ma non in senso stretto: $|1|=|i|=|-1|=|-i|=1$, quindi sulle prime quattro righe vale l'uguale, mentre sull'ultima $|1|>\frac14$ (è la "foglia mangiata dal baco"). Per colonne vale l'uguale su tutte le colonne tranne la prima, dove $|1|>\frac14$.

Quindi $A$ è a d.d. e irriducibile, ed è invertibile per il teorema; ma col solo terzo teorema di Gershgorin debole non si riesce a escludere che $0$ sia un autovalore, e quindi non si potrebbe dimostrare che è invertibile.

Con questo si chiude il discorso sui teoremi di Gershgorin e sulle matrici a diagonale dominante.

> [!question] Domanda tipica d'esame
> Dare la definizione di matrice a diagonale dominante (per righe e per colonne, anche in senso stretto) e interpretarla con i cerchi di Gershgorin. Enunciare il teorema di invertibilità e dimostrarlo nel caso d.d. e irriducibile. Traccia: $|a_{ii}|$ è la distanza del centro di $K_i$ dall'origine, la sommatoria è il raggio; (a) dice che $0$ sta al più sul bordo dei cerchi, (b) che esiste $K_k$ che non contiene $0$; con l'irriducibilità si applica il terzo teorema di Gershgorin forte, quindi $0$ non è autovalore e $A$ è invertibile. Il quadrifoglio mostra che la versione debole non basta.
### Norme vettoriali
Argomento completamente nuovo (alla lavagna si apre una nuova whiteboard). Anche qui niente di difficile.
#### Motivazione
> [!example] Esempio
> Consideriamo il sistema lineare
> $$\begin{bmatrix}8&1&1\\1&5&-1\\1&-1&5\end{bmatrix}\begin{bmatrix}x_1\\x_2\\x_3\end{bmatrix}=\begin{bmatrix}26\\7\\7\end{bmatrix}$$
> che ha soluzione $\underline{x}=\begin{bmatrix}3\\1\\1\end{bmatrix}$. Supponiamo di aver ottenuto per $\underline{x}$ due approssimazioni
> $$\underline{y}=\begin{bmatrix}2.99972\\1.00023\\1.00030\end{bmatrix},\qquad\underline{z}=\begin{bmatrix}3.00027\\0.99971\\0.99955\end{bmatrix}$$
> Come faccio a stabilire quale delle due è più vicina a $\underline{x}$?

I vettori si indicano sottolineati (notazione già introdotta). Approssimare la soluzione di un sistema lineare con i **metodi iterativi** sarà l'argomento della parte finale del corso.

Guardando le componenti una per una non si conclude: sulla prima componente $|2.99972-3|=0.00028$ e $|3.00027-3|=0.00027$, quindi vince $\underline{z}$; sulla seconda $|1.00023-1|=0.00023$ e $|0.99971-1|=0.00029$, quindi vince $\underline{y}$. Uno studente propone di prendere la media delle due, un altro di prendere le componenti migliori di ciascuna; ma un procedimento automatico, come un metodo iterativo, restituisce un vettore: bisogna scegliere o l'uno o l'altro.

Mi occorre un **concetto di distanza sullo spazio dei vettori** per poi misurare le distanze da $\underline{x}$ a $\underline{y}$ e da $\underline{x}$ a $\underline{z}$: la soluzione approssimata che ha distanza minore da $\underline{x}$ sarà la più vicina a $\underline{x}$, cioè la migliore. Sui numeri questo concetto è il **modulo**; la **norma** ne è la generalizzazione ai vettori.
#### Definizione
> [!quote] Definizione (norma vettoriale)
> Una funzione $\|\cdot\|:\mathbb{C}^n\to\mathbb{R}$ si dice **norma vettoriale** se soddisfa le seguenti proprietà:
> - (a) $\|\underline{x}\|\geq0\ \ \forall\underline{x}\in\mathbb{C}^n$ e $\|\underline{x}\|=0$ se e solo se $\underline{x}=\underline{0}$ [**positività**];
> - (b) $\|\alpha\underline{x}\|=|\alpha|\cdot\|\underline{x}\|\ \ \forall\alpha\in\mathbb{C}\ \ \forall\underline{x}\in\mathbb{C}^n$ [**omogeneità**];
> - (c) $\|\underline{x}+\underline{y}\|\leq\|\underline{x}\|+\|\underline{y}\|\ \ \forall\underline{x},\underline{y}\in\mathbb{C}^n$ [**disuguaglianza triangolare**].
>
> Data una norma vettoriale $\|\cdot\|:\mathbb{C}^n\to\mathbb{R}$, definiamo la **distanza** fra due vettori $\underline{x},\underline{y}\in\mathbb{C}^n$ come $\|\underline{x}-\underline{y}\|$.

Si usano due stanghette per non confonderla con il modulo, che ne ha una. Interpretazione: $\|\underline{x}\|$ è la distanza di $\underline{x}$ dall'origine. Allora (a) dice che la distanza dall'origine è nulla solo per $\underline{x}=\underline{0}$ (il vettore nullo, cioè l'origine); (b) dice ad esempio che sia $3\underline{x}$ che $-3\underline{x}$ distano dall'origine $3$ volte quanto $\underline{x}$.

> [!example] Esempio (la distanza euclidea nel piano)
> Siano $\underline{x}=(2,1)$ e $\underline{y}=(-1,-3)$. La loro distanza, la lunghezza del segmento che li congiunge, è
> $$\|\underline{x}-\underline{y}\|=\sqrt{(2-(-1))^2+(1-(-3))^2}=\sqrt{9+16}=\sqrt{25}=5$$
> mentre $\|\underline{x}\|=\sqrt{4+1}=\sqrt5$ è la distanza di $\underline{x}$ dall'origine, cioè $\|\underline{x}-\underline{0}\|$.

> [!warning] Norma, non modulo
> Alcuni studenti chiamano "modulo" la lunghezza di un vettore (come fanno i fisici, che parlano di "modulo del vettore"). Il modulo è definito per i numeri; per i vettori il nome corretto è **norma** (qui norma euclidea, distanza euclidea). Ci si intende comunque.
#### Le tre norme principali
> [!quote] Definizione (norme $1$, $2$, $\infty$)
> Le norme vettoriali più importanti in $\mathbb{C}^n$ sono tre, definite $\forall\underline{x}\in\mathbb{C}^n$ come segue:
> $$\|\underline{x}\|_1=|x_1|+|x_2|+\dots+|x_n|\qquad\text{(norma }1\text{)}$$
> $$\|\underline{x}\|_2=\sqrt{|x_1|^2+|x_2|^2+\dots+|x_n|^2}\qquad\text{(norma }2\text{ o euclidea)}$$
> $$\|\underline{x}\|_\infty=\max\big(|x_1|,|x_2|,\dots,|x_n|\big)\qquad\text{(norma }\infty\text{)}$$

Non si dimostra che sono norme; chi vuole può farlo, non è particolarmente difficile. La norma $2$ è quella classica, usata nell'esempio del piano.

**Ritorno all'esempio iniziale.** Le differenze sono
$$\underline{x}-\underline{y}=\begin{bmatrix}0.00028\\-0.00023\\-0.00030\end{bmatrix},\qquad\underline{x}-\underline{z}=\begin{bmatrix}-0.00027\\0.00029\\0.00045\end{bmatrix}$$
Un concetto di distanza naturale è guardare l'**errore massimo** commesso sulle componenti. Usando come concetto di distanza sui vettori la norma $\infty$, risulta
$$\|\underline{x}-\underline{y}\|_\infty=\max\big(|x_1-y_1|,|x_2-y_2|,|x_3-y_3|\big)=0.00030$$
$$\|\underline{x}-\underline{z}\|_\infty=\max\big(|x_1-z_1|,|x_2-z_2|,|x_3-z_3|\big)=0.00045$$
quindi $\underline{z}$ è più lontano da $\underline{x}$ di $\underline{y}$, e si sceglie l'approssimazione $\underline{y}$.

> [!info] Con le altre norme (nostra aggiunta)
> Il confronto dipende dalla norma scelta. Qui $\|\underline{x}-\underline{y}\|_1=0.00081<\|\underline{x}-\underline{z}\|_1=0.00101$ e $\|\underline{x}-\underline{y}\|_2\approx0.00047<\|\underline{x}-\underline{z}\|_2\approx0.00060$, quindi anche con le norme $1$ e $2$ vince $\underline{y}$; ma in generale norme diverse possono dare risposte diverse.
#### La norma 1 come distanza di Manhattan
La norma $1$ si chiama anche **norma di Manhattan**. A Manhattan le strade formano una griglia di isolati: per andare da $\underline{x}$ (voi) a $\underline{y}$ (la casa della nonna) non si può andare in linea d'aria, a meno di avere un elicottero privato (allora interesserebbe la distanza euclidea). Si possono fare percorsi diversi lungo le strade (alla lavagna in rosso, verde e blu), ma tutti hanno la stessa lunghezza: un tratto orizzontale lungo $|y_1-x_1|$ e uno verticale lungo $|y_2-x_2|$. Se vi interessa la benzina consumata, la distanza giusta è
$$\|\underline{x}-\underline{y}\|_1=|y_1-x_1|+|y_2-x_2|$$
(alla lavagna in $\mathbb{R}^2$, ma vale lo stesso in $\mathbb{C}^2$).
### Equivalenza delle norme vettoriali
> [!quote] Teorema (equivalenza delle norme)
> Tutte le norme vettoriali in $\mathbb{C}^n$ sono equivalenti, nel senso che se prendiamo $2$ norme vettoriali $\|\cdot\|',\|\cdot\|'':\mathbb{C}^n\to\mathbb{R}$ allora si ha
> $$\alpha\|\underline{x}\|''\leq\|\underline{x}\|'\leq\beta\|\underline{x}\|''\qquad\forall\underline{x}\in\mathbb{C}^n$$
> dove $\alpha,\beta>0$ sono due costanti indipendenti da $\underline{x}$.

Non si dimostra perché è complicato. Le costanti possono essere qualsiasi (ad esempio $\frac14$ e $17$): la cosa fondamentale è che sono **indipendenti da $\underline{x}$** e la limitazione vale **per tutti** gli $\underline{x}$.

> [!warning] "Equivalenti" non vuol dire "una vale l'altra"
> L'equivalenza è nel senso degli analisti, cioè solo nel senso del teorema, che è un senso debole. All'esame è capitato che qualche studente dicesse "le norme sono equivalenti, quindi uso l'una e vale l'altra": è sbagliato. A Manhattan bisogna usare la norma $1$, perché per la vostra benzina la norma $1$ e la norma $2$ non sono affatto equivalenti. Quando si usa l'equivalenza delle norme la si usa **in questo senso**.

Uno studente osserva che le norme sono tutte "$\Theta$" l'una dell'altra, nel senso della notazione asintotica: il docente conferma che è proprio questo, sono comprese tra due costanti, e che la cosa diventa importante con le successioni di vettori.
#### Norma 1 e norma ∞
Vediamo ad esempio che $\|\cdot\|_1$ e $\|\cdot\|_\infty$ sono equivalenti in $\mathbb{C}^n$, cioè troviamo le costanti $\alpha$ e $\beta$. Mettiamo in mezzo la norma $1$. $\forall\underline{x}\in\mathbb{C}^n$ risulta
$$1\cdot\max\big(|x_1|,|x_2|,\dots,|x_n|\big)\leq|x_1|+|x_2|+\dots+|x_n|\leq n\max\big(|x_1|,|x_2|,\dots,|x_n|\big)$$
- A destra: ciascun $|x_i|$ è $\leq$ del massimo, che è la norma $\infty$; sommando gli $n$ termini si ottiene $n$ volte il massimo (la costante $n$ è stata trovata da uno studente).
- A sinistra: la somma di tutti i moduli è più grande del massimo, che è uno di essi.

In termini di norme:
$$\|\underline{x}\|_\infty\leq\|\underline{x}\|_1\leq n\|\underline{x}\|_\infty,\qquad\alpha=1,\ \beta=n$$
Le costanti non dipendono da $\underline{x}$.

**Invertire le disuguaglianze.** Non è che la norma $1$ stia "in mezzo" e la norma $\infty$ no: la coppia di disuguaglianze si può invertire. Dalla prima, $\|\underline{x}\|_\infty\leq\|\underline{x}\|_1$; dalla seconda, dividendo per $n$, $\frac1n\|\underline{x}\|_1\leq\|\underline{x}\|_\infty$. Quindi
$$\frac1n\|\underline{x}\|_1\leq\|\underline{x}\|_\infty\leq\|\underline{x}\|_1,\qquad\alpha=\frac1n,\ \beta=1$$
Le costanti dipendono dalla prospettiva, cioè da quale norma si mette al centro.
#### Norma 2 e norma ∞
Verifichiamo che $\|\cdot\|_2$ e $\|\cdot\|_\infty$ sono equivalenti in $\mathbb{C}^n$. Mettiamo al centro la norma $2$. $\forall\underline{x}\in\mathbb{C}^n$:
$$1\cdot\|\underline{x}\|_\infty\leq\|\underline{x}\|_2=\sqrt{|x_1|^2+|x_2|^2+\dots+|x_n|^2}\leq\sqrt{n\|\underline{x}\|_\infty^2}=\sqrt n\,\|\underline{x}\|_\infty$$
- A sinistra: tra i quadrati sotto radice c'è quello del modulo massimo, quindi la somma è $\geq\|\underline{x}\|_\infty^2$ e, sotto radice, $\|\underline{x}\|_2\geq\|\underline{x}\|_\infty$.
- A destra: ogni $|x_i|^2$ è $\leq\|\underline{x}\|_\infty^2$, quindi la somma è $\leq n\|\underline{x}\|_\infty^2$.

Dunque $\alpha=1$, $\beta=\sqrt n$. Invertendo, con la norma $\infty$ al centro:
$$\frac{1}{\sqrt n}\|\underline{x}\|_2\leq\|\underline{x}\|_\infty\leq\|\underline{x}\|_2,\qquad\alpha=\frac{1}{\sqrt n},\ \beta=1$$
### Successioni di vettori
"Al volo", l'ultimo argomento della lezione. L'indice della successione si scrive **all'apice tra parentesi tonde**, $\underline{x}^{(k)}$, per non confonderlo con le componenti: $x_1$ è la prima componente del vettore $\underline{x}$.

> [!quote] Definizione (convergenza in norma)
> Una successione di vettori $\underline{x}^{(0)},\underline{x}^{(1)},\underline{x}^{(2)},\dots$ in $\mathbb{C}^n$ si dice **convergente al vettore $\underline{x}\in\mathbb{C}^n$ rispetto alla norma $\|\cdot\|$** se
> $$\|\underline{x}^{(k)}-\underline{x}\|\to0\quad\text{per }k\to\infty$$

Cioè la distanza di $\underline{x}^{(k)}$ da $\underline{x}$ tende a $0$.

> [!quote] Teorema
> Poiché tutte le norme vettoriali in $\mathbb{C}^n$ sono equivalenti, se una successione di vettori $\{\underline{x}^{(k)}\}_{k=0,1,2,\dots}\subseteq\mathbb{C}^n$ converge a $\underline{x}$ rispetto a una norma $\|\cdot\|$, allora converge a $\underline{x}$ rispetto a tutte le norme.

È questa l'importanza dell'equivalenza delle norme.
#### Dimostrazione
Supponiamo che $\{\underline{x}^{(k)}\}_{k=0,1,2,\dots}$ converga a $\underline{x}$ rispetto alla norma $\|\cdot\|$ e sia $\|\cdot\|'$ un'altra norma. Poiché $\|\cdot\|$ e $\|\cdot\|'$ sono equivalenti, $\exists\,\alpha,\beta>0$ costanti t.c.
$$\alpha\|\underline{y}\|\leq\|\underline{y}\|'\leq\beta\|\underline{y}\|\qquad\forall\underline{y}\in\mathbb{C}^n$$
Le costanti non dipendono da $\underline{y}$. Applicando questa proprietà con $\underline{y}=\underline{x}^{(k)}-\underline{x}$ (le costanti $\alpha,\beta$ restano le stesse), $\forall k=0,1,2,\dots$:
$$\alpha\|\underline{x}^{(k)}-\underline{x}\|\leq\|\underline{x}^{(k)}-\underline{x}\|'\leq\beta\|\underline{x}^{(k)}-\underline{x}\|$$
Per ipotesi $\|\underline{x}^{(k)}-\underline{x}\|\to0$ per $k\to\infty$. Le costanti $\alpha$ e $\beta$ non dipendono da $k$, quindi anche il primo membro $\alpha\|\underline{x}^{(k)}-\underline{x}\|$ e l'ultimo $\beta\|\underline{x}^{(k)}-\underline{x}\|$ tendono a $0$ per $k\to\infty$. Allora
$$\|\underline{x}^{(k)}-\underline{x}\|'\xrightarrow{k\to\infty}0$$
per il **teorema dei due carabinieri** (o del sandwich): la quantità in mezzo è incastrata tra due "carabinieri" che tendono entrambi a $0$. $\blacksquare$

> [!warning] Quale norma tende a zero
> A lezione il docente ha detto per un attimo "la norma tende a zero" e si è corretto: quella che si **dimostra** tendere a $0$ è la norma **primo**, $\|\cdot\|'$, quella incastrata in mezzo; quella senza apice tende a $0$ per ipotesi.
#### Convergenza componente per componente
La convergenza "facile" di vettori è quella componente per componente.

> [!quote] Definizione (convergenza componente per componente)
> Una successione di vettori $\underline{x}^{(0)},\underline{x}^{(1)},\underline{x}^{(2)},\dots$ in $\mathbb{C}^n$ si dice **convergente (componente per componente)** al vettore $\underline{x}\in\mathbb{C}^n$ se $\underline{x}^{(k)}\to\underline{x}$ componente per componente, cioè se
> $$x_1^{(k)}\to x_1,\quad x_2^{(k)}\to x_2,\quad\dots,\quad x_n^{(k)}\to x_n$$

"Componente per componente" è tra parentesi per lo stesso motivo di "per righe": se di una successione di vettori si dice solo che è convergente, si intende componente per componente, la convergenza standard.

Le componenti sono numeri, quindi
$$\begin{cases}x_1^{(k)}\to x_1\\x_2^{(k)}\to x_2\\\ \vdots\\x_n^{(k)}\to x_n\end{cases}\iff\begin{cases}|x_1^{(k)}-x_1|\to0\\|x_2^{(k)}-x_2|\to0\\\ \vdots\\|x_n^{(k)}-x_n|\to0\end{cases}\iff\max\big(|x_1^{(k)}-x_1|,|x_2^{(k)}-x_2|,\dots,|x_n^{(k)}-x_n|\big)\to0\iff\|\underline{x}^{(k)}-\underline{x}\|_\infty\to0$$
Il penultimo passaggio: dire che tutti i moduli tendono a $0$ è lo stesso che dire che il loro massimo tende a $0$.

Vediamo quindi che la convergenza componente per componente **coincide con la convergenza in $\|\cdot\|_\infty$**. Quindi, ricordando quanto detto poco fa, dire che $\underline{x}^{(k)}\to\underline{x}$ componente per componente è lo stesso che dire che $\underline{x}^{(k)}\to\underline{x}$ in una qualsiasi norma: in norma $1$, in norma $2$, in norma $\infty$, o in qualsiasi altra norma ci si voglia inventare. Il docente accenna che esistono le norme $\|\cdot\|_p$ per ogni $p\geq1$ (ad esempio la norma $500$ o la norma $\sqrt2$).

> [!info] Le norme $p$ (nostra aggiunta)
> Per $p\geq1$ la norma $p$ è $\|\underline{x}\|_p=\big(|x_1|^p+\dots+|x_n|^p\big)^{1/p}$; per $p=1$ e $p=2$ si ritrovano le norme $1$ e $2$, e per $p\to\infty$ si ottiene la norma $\infty$, da cui il nome.

> [!question] Domanda tipica d'esame
> Dare la definizione di norma vettoriale e delle norme $1$, $2$, $\infty$. Enunciare il teorema di equivalenza delle norme e verificarlo per $\|\cdot\|_1$ e $\|\cdot\|_\infty$ (oppure $\|\cdot\|_2$ e $\|\cdot\|_\infty$). Traccia: positività, omogeneità, disuguaglianza triangolare; $\alpha\|\underline{x}\|''\leq\|\underline{x}\|'\leq\beta\|\underline{x}\|''$ con $\alpha,\beta>0$ indipendenti da $\underline{x}$; $\|\underline{x}\|_\infty\leq\|\underline{x}\|_1\leq n\|\underline{x}\|_\infty$ e $\|\underline{x}\|_\infty\leq\|\underline{x}\|_2\leq\sqrt n\|\underline{x}\|_\infty$, maggiorando ogni componente con il massimo. Ricordare che "equivalenti" vale solo in questo senso.

> [!question] Domanda tipica d'esame
> Dimostrare che se una successione di vettori converge a $\underline{x}$ rispetto a una norma, allora converge a $\underline{x}$ rispetto a tutte le norme, e che la convergenza componente per componente coincide con la convergenza in norma $\infty$. Traccia: equivalenza applicata a $\underline{y}=\underline{x}^{(k)}-\underline{x}$ con costanti indipendenti da $k$, teorema dei due carabinieri; tutti i $|x_i^{(k)}-x_i|\to0$ se e solo se il loro massimo $\|\underline{x}^{(k)}-\underline{x}\|_\infty\to0$.

A metà della parte sull'equivalenza delle norme è saltato il proiettore dell'aula; la lezione è proseguita dopo il ripristino. Il docente consiglia di portare sempre un computer per sicurezza, da condividere con i compagni. La lezione era compressa perché subito dopo c'era un'altra lezione, ed è finita in anticipo, verso le 15:40, nonostante il ritardo d'inizio.
## Norme matriciali e potenze di una matrice
Lezione 13 (17/11/2026): norme matriciali, la norma $|\cdot|_\infty$ che non è submoltiplicativa, norme matriciali indotte e loro proprietà (con dimostrazione), formule per le norme $1,2,\infty$ con un esempio, equivalenza delle norme matriciali, successioni di matrici e teorema $A^k\to O\iff\rho(A)<1$.

La lezione precedente si era chiusa con le **norme vettoriali**, un modo per misurare la distanza tra due vettori; quelle che interessano sono tre: la norma $1$, la norma $\infty$ e la norma $2$ (euclidea). Ora si passa alle **norme matriciali**, per misurare la distanza tra matrici. È l'ultima lezione sull'analisi delle matrici: il teorema finale sulle potenze di una matrice è, nelle parole del docente, l'ultimo teorema di questa parte del corso e un teorema fondamentale dell'analisi delle matrici. Dalla lezione successiva comincia la **risoluzione dei sistemi lineari con metodi iterativi**.
### Norme matriciali
> [!quote] Definizione (norma matriciale)
> Una funzione $\|\cdot\|:\mathbb{C}^{n\times n}\to\mathbb{R}$ si dice **norma matriciale** se soddisfa le seguenti proprietà:
> - (a) $\|A\|\geq0$ per ogni $A\in\mathbb{C}^{n\times n}$, e $\|A\|=0\iff A=O$ [**positività**];
> - (b) $\|\alpha A\|=|\alpha|\,\|A\|$ per ogni $\alpha\in\mathbb{C}$ e per ogni $A\in\mathbb{C}^{n\times n}$ [**omogeneità**];
> - (c) $\|A+B\|\leq\|A\|+\|B\|$ per ogni $A,B\in\mathbb{C}^{n\times n}$ [**disuguaglianza triangolare**].
>
> Qui $O$ è la **matrice nulla**, con tutte le componenti uguali a $0$.

La definizione è praticamente identica a quella di norma vettoriale: cambiano solo gli oggetti a cui si applica (matrici invece di vettori). Il docente aggiunge in un secondo momento il quantificatore "per ogni $A\in\mathbb{C}^{n\times n}$" nella (a), sottolineando che è importante. La disuguaglianza triangolare è, dice, la proprietà più importante delle tre.

Data una norma matriciale $\|\cdot\|:\mathbb{C}^{n\times n}\to\mathbb{R}$, si definisce la **distanza** fra due matrici $A,B\in\mathbb{C}^{n\times n}$ come
$$\|A-B\|$$
esattamente come per i vettori: la norma gioca il ruolo del modulo, e la distanza tra due numeri è il modulo della differenza.

> [!info] Solo matrici quadrate
> Uno studente chiede perché ci si limiti alle matrici quadrate. Le norme si potrebbero definire anche sulle matrici rettangolari, ma al corso non interessa; inoltre la norma $2$ per matrici non quadrate sarebbe più complicata da calcolare (servirebbero i valori singolari).
#### Un modo naturale: la matrice come vettore
Un modo **naturale** per definire una norma su $\mathbb{C}^{n\times n}$ consiste nel riguardare ogni matrice $A\in\mathbb{C}^{n\times n}$ come un vettore di $n^2$ componenti (ad esempio mettendo in fila tutte le colonne) e usare una qualsiasi norma vettoriale come norma di $A$.

> [!example] Esempio (norma $\infty$ delle matrici $|\cdot|_\infty$)
> Ricordiamo che per $x\in\mathbb{C}^n$ la norma infinito è $\|x\|_\infty=\max_{i=1,\dots,n}|x_i|$, il massimo dei moduli delle componenti. L'analogo per le matrici: data $A\in\mathbb{C}^{n\times n}$ si definisce
> $$|A|_\infty=\max_{i,j=1,\dots,n}|a_{ij}|$$
> cioè il massimo dei moduli delle componenti della matrice (con due indici perché le componenti hanno due indici).

Allo stesso modo si potrebbero definire una norma $|\cdot|_1$ e una norma $|\cdot|_2$ delle matrici, applicando la norma $1$ o $2$ al vettore delle $n^2$ componenti.

> [!warning] Una stanghetta sola
> Questa norma si indica con **una stanghetta sola**, $|\cdot|_\infty$, apposta: il simbolo con due stanghette $\|\cdot\|_\infty$ è **riservato** alla "vera" norma infinito delle matrici, quella indotta dalla norma vettoriale $\|\cdot\|_\infty$, che si vedrà tra poco ed è diversa.

$|\cdot|_\infty$ è una norma (soddisfa (a), (b), (c)), ma "**non si comporta bene**" rispetto al prodotto di matrici, perché **non è submoltiplicativa**: non soddisfa la proprietà
$$|AB|_\infty\leq|A|_\infty\,|B|_\infty\qquad\forall A,B\in\mathbb{C}^{n\times n}$$
Infatti, se
$$A=\begin{bmatrix}1&1\\0&1\end{bmatrix},\qquad B=\begin{bmatrix}1&0\\1&1\end{bmatrix},\qquad\text{allora}\qquad AB=\begin{bmatrix}2&1\\1&1\end{bmatrix}$$
e quindi
$$|AB|_\infty=2,\qquad|A|_\infty=1,\qquad|B|_\infty=1\qquad\big(|AB|_\infty>|A|_\infty|B|_\infty\,!\big)$$
La **submoltiplicatività** ("la norma del prodotto è minore o uguale del prodotto delle norme") è l'analogo per il prodotto di quello che la disuguaglianza triangolare è per la somma. Le proprietà (a), (b), (c) in teoria bastano, ma le norme matriciali che interessano davvero devono essere anche submoltiplicative: sono le **norme matriciali indotte**.
### Norme matriciali indotte
> [!quote] Definizione (norma matriciale indotta)
> Data una norma vettoriale $\|\cdot\|:\mathbb{C}^n\to\mathbb{R}$ e una matrice $A\in\mathbb{C}^{n\times n}$, definiamo il numero
> $$\|A\|=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|}{\|x\|}$$
> Si può dimostrare che $\|\cdot\|:\mathbb{C}^{n\times n}\to\mathbb{R}$ è una norma matriciale nel senso della definizione precedente. Questa norma matriciale si chiama **norma matriciale indotta dalla norma vettoriale** $\|\cdot\|$ e **per regolamento** si denota con lo stesso simbolo della norma vettoriale che la induce.

- $Ax$ è un vettore (colonna), quindi $\|Ax\|$ è la norma vettoriale di un vettore, che sappiamo calcolare; lo stesso per $\|x\|$ al denominatore.
- Si esclude $x=0$ perché altrimenti il denominatore sarebbe $0$.
- Che sia una norma matriciale **non si dimostra** ("credetemi che è così").
- Il docente insiste sulla convenzione del simbolo: "è una regola che tutto il mondo rispetta, nessuno si permetterebbe mai di violarla". In teoria scrivere $\|A\|$ con la norma vettoriale sarebbe un abuso, perché quella si applica ai vettori; ma la norma indotta si denota esattamente come la norma che la induce. Ad esempio $\|A\|_\infty$ è la norma matriciale indotta dalla norma vettoriale $\|\cdot\|_\infty$: per questo prima non si poteva usare quel simbolo per $|A|_\infty$.
#### Un'altra espressione: il massimo sui vettori di norma 1
Pochi passaggi mostrano che la norma indotta si può scrivere in un'altra forma. Siccome $\|Ax\|$ è un numero, si scrive il rapporto come uno scalare che moltiplica; poi si usa l'**omogeneità** della norma vettoriale per portare lo scalare dentro, e la **linearità** del prodotto matrice-vettore per farlo passare "dentro" $A$:
$$\|A\|=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|}{\|x\|}=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{1}{\|x\|}\,\|Ax\|=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\Big\|\frac{1}{\|x\|}Ax\Big\|=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\Big\|A\Big(\underbrace{\frac{1}{\|x\|}\,x}_{y}\Big)\Big\|$$
Il vettore $y=\frac{1}{\|x\|}x$ ha norma $1$: usando di nuovo l'omogeneità (questa volta per portare lo scalare **fuori**),
$$\|y\|=\Big\|\frac{1}{\|x\|}\,x\Big\|=\frac{1}{\|x\|}\,\|x\|=1$$
Quindi, quando $x$ varia fra tutti i vettori non nulli, $y$ varia solo fra i vettori di norma $1$ (pensando alla norma come distanza dall'origine, i vettori sulla "sfera" di raggio $1$). Con un cambio di variabile:
$$\|A\|=\max_{\substack{y\in\mathbb{C}^n\\\|y\|=1}}\|Ay\|$$
È un'altra espressione, molto importante, della norma indotta.

> [!info] Ogni vettore di norma 1 si ottiene (nostra aggiunta)
> Per il cambio di variabile serve anche che ogni $y$ con $\|y\|=1$ sia della forma $\frac{x}{\|x\|}$: basta prendere $x=y$. Quindi i due massimi sono fatti esattamente sugli stessi valori.
### Proprietà delle norme indotte
> [!quote] Teorema
> Sia $\|\cdot\|:\mathbb{C}^{n\times n}\to\mathbb{R}$ una norma matriciale indotta dalla norma vettoriale $\|\cdot\|$ e siano $A,B\in\mathbb{C}^{n\times n}$. Allora valgono le seguenti:
> 1. $\|I\|=1$;
> 2. $\|Ax\|\leq\|A\|\cdot\|x\|$ per ogni $x\in\mathbb{C}^n$;
> 3. $\|A\|$ è la più piccola costante $C$ che soddisfa $\|Ax\|\leq C\|x\|$ **per ogni** $x\in\mathbb{C}^n$;
> 4. $\|AB\|\leq\|A\|\cdot\|B\|$ [**submoltiplicatività**];
> 5. $\rho(A)\leq\|A\|$.

- Nella 2, a sinistra c'è la norma vettoriale di $Ax$, a destra la norma matriciale di $A$ per la norma vettoriale di $x$. Non è ancora la submoltiplicatività, che riguarda il prodotto matrice per matrice.
- Nella 3 il docente sottolinea il "per ogni $x$": per **qualche** $x$ potrebbe esserci una costante più piccola di $\|A\|$ che soddisfa la disuguaglianza, ma una costante più piccola che la soddisfa **per tutti** gli $x\in\mathbb{C}^n$ non esiste.
- Nella 5, $\rho(A)$ è il raggio spettrale, il massimo dei moduli degli autovalori ([[03 - Analisi delle matrici#Traccia, determinante, raggio spettrale e autovalori]]): la più grande distanza dall'origine di un autovalore di $A$ nel piano complesso. È minore o uguale di **qualunque** norma indotta di $A$.

Le norme indotte sono quindi quelle "che ci piacciono", perché si comportano bene rispetto al prodotto; nel mondo delle matrici si usano quasi solo queste. Il teorema "è un po' lungo ma tutti i punti sono abbastanza facili".
#### Dimostrazione
**1.** Si usa la seconda espressione (il massimo sui vettori di norma $1$). L'identità applicata a un vettore lo lascia invariato ($Ix=x$: la prima riga di $I$ per $x$ dà il primo elemento, la seconda il secondo, ecc.), quindi
$$\|I\|\overset{\text{def}}{=}\max_{\substack{x\in\mathbb{C}^n\\\|x\|=1}}\|Ix\|=\max_{\substack{x\in\mathbb{C}^n\\\|x\|=1}}\underbrace{\|x\|}_{=1}=1$$
perché si fa il massimo di quantità tutte uguali a $1$.

**2.** Per ogni fissato $x\in\mathbb{C}^n\setminus\{0\}$ vale che
$$\frac{\|Ax\|}{\|x\|}\leq\max_{\substack{y\in\mathbb{C}^n\\y\neq0}}\frac{\|Ay\|}{\|y\|}\overset{\text{def}}{=}\|A\|$$
perché il rapporto calcolato in un $x$ fissato è minore o uguale del massimo di tutti i rapporti. Moltiplicando entrambi i membri per $\|x\|$:
$$\|Ax\|\leq\|A\|\cdot\|x\|$$
Questo è stato dimostrato solo per $x\neq0$, perché bisognava dividere per $\|x\|$. Ma la tesi dice "per ogni $x\in\mathbb{C}^n$", compreso il vettore nullo. Si fa una **verifica diretta**: la disuguaglianza ottenuta vale anche se $x=0$, nel qual caso entrambi i membri sono $=0$ ($A\,0=0$ e la norma del vettore nullo è $0$).

> [!info] Escludere un caso e reincluderlo
> È uno schema tipico in matematica: si esclude un caso perché lì la dimostrazione non funziona (qui non si può dividere per $0$), e alla fine lo si reinclude con una verifica diretta: la dimostrazione non funziona in quel caso, ma il risultato vale lo stesso.

**3.** Per il punto 2, $\|A\|$ è **una** costante $C$ che soddisfa $\|Ax\|\leq C\|x\|$ per ogni $x\in\mathbb{C}^n$. Bisogna dimostrare che è la più piccola.

Supponiamo che $C$ sia un'altra costante che soddisfa
$$\|Ax\|\leq C\|x\|\qquad\forall x\in\mathbb{C}^n$$
Ne segue che, per ogni $x\in\mathbb{C}^n\setminus\{0\}$, dividendo ambo i membri della disequazione per $\|x\|$ si ottiene
$$\frac{\|Ax\|}{\|x\|}\leq C\qquad\forall x\in\mathbb{C}^n\setminus\{0\}$$
Siccome tutti i rapporti sono $\leq C$, anche il loro massimo lo è (il massimo è uno di loro):
$$\|A\|\overset{\text{def}}{=}\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|}{\|x\|}\leq C$$
Quindi $\|A\|$ è la più piccola costante $C$ tale che $\|Ax\|\leq C\|x\|$ per ogni $x\in\mathbb{C}^n$.

> [!info] Perché qui lo $0$ non va reincluso
> Uno studente chiede perché in questo punto, a differenza del punto 2, non si verifichi alla fine il caso $x=0$. Nel punto 2 lo $0$ faceva parte della **tesi** ("per ogni $x\in\mathbb{C}^n$"), quindi andava reincluso. Qui la tesi è "$\|A\|\leq C$", e lo $0$ è stato escluso solo in un passaggio intermedio, per poter dividere: si parte da una qualsiasi $C$ che soddisfa la disuguaglianza per ogni $x$ e si arriva a $\|A\|\leq C$.

**4.** Per ogni fissato $x\in\mathbb{C}^n$ vale
$$\|ABx\|=\|A(Bx)\|\overset{2}{\leq}\|A\|\cdot\|Bx\|\overset{2}{\leq}\|A\|\cdot\|B\|\cdot\|x\|$$
- Nel primo passaggio si usa la proprietà 2 con la matrice $A$ e il vettore $y=Bx\in\mathbb{C}^n$ (la proprietà 2 vale per tutti i vettori di $\mathbb{C}^n$, quindi anche per $Bx$).
- Nel secondo si usa ancora la proprietà 2, con la matrice $B$ e il vettore $x$.

Allora:
- da qui si deduce che $\|A\|\cdot\|B\|$ (che non dipende da $x$) è **una** costante $C$ che soddisfa $\|(AB)x\|\leq C\|x\|$ per ogni $x\in\mathbb{C}^n$;
- ma dal punto 3 (applicato alla matrice $AB$) sappiamo che $\|AB\|$ è la **più piccola** costante $C$ che soddisfa $\|ABx\|\leq C\|x\|$ per ogni $x\in\mathbb{C}^n$.

Mettendo insieme le due affermazioni:
$$\|AB\|\leq\|A\|\cdot\|B\|$$

**5.** Sia $\lambda$ un autovalore di $A$ tale che $|\lambda|=\rho(A)$ (un autovalore di modulo massimo; potrebbero essercene più di uno, se ne prende uno). Sia $x\neq0$ un autovettore corrispondente, cioè $Ax=\lambda x$. Passando alle norme e usando l'omogeneità:
$$Ax=\lambda x\implies\|Ax\|=\|\lambda x\|=|\lambda|\cdot\|x\|=\rho(A)\,\|x\|$$
Siccome $x\neq0$, si può dividere per $\|x\|$:
$$\rho(A)=\frac{\|Ax\|}{\|x\|}\leq\max_{\substack{y\in\mathbb{C}^n\\y\neq0}}\frac{\|Ay\|}{\|y\|}\overset{\text{def}}{=}\|A\|$$
perché il massimo su tutti gli $y$ è maggiore o uguale del valore ottenuto prendendo l'autovettore $x$. $\blacksquare$

> [!question] Domanda tipica d'esame
> Dare la definizione di norma matriciale indotta da una norma vettoriale ed enunciare e dimostrare le sue proprietà ($\|I\|=1$, $\|Ax\|\leq\|A\|\|x\|$, $\|A\|$ più piccola costante, submoltiplicatività, $\rho(A)\leq\|A\|$). Traccia: per $\|I\|$ usare il massimo sui vettori di norma $1$; per la 2 confrontare il rapporto in un $x$ fissato con il massimo e reincludere $x=0$ con una verifica diretta; per la 3 dividere per $\|x\|$ e passare al massimo; per la 4 applicare due volte la 2 e poi la 3 alla matrice $AB$; per la 5 prendere un autovettore dell'autovalore di modulo massimo.

> [!question] Domanda tipica d'esame
> Mostrare con un esempio che la norma $|A|_\infty=\max_{i,j}|a_{ij}|$ non è submoltiplicativa, e spiegare perché si usano le norme indotte. Traccia: $A=\begin{bmatrix}1&1\\0&1\end{bmatrix}$, $B=\begin{bmatrix}1&0\\1&1\end{bmatrix}$, $|AB|_\infty=2>1=|A|_\infty|B|_\infty$; le norme indotte sono submoltiplicative (punto 4 del teorema).
### Le norme 1, 2, ∞
Le norme matriciali più importanti per noi (e le uniche che si useranno) sono le norme indotte dalle norme vettoriali $1$, $2$, $\infty$:
$$\|A\|_1=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|_1}{\|x\|_1},\qquad\|A\|_2=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|_2}{\|x\|_2},\qquad\|A\|_\infty=\max_{\substack{x\in\mathbb{C}^n\\x\neq0}}\frac{\|Ax\|_\infty}{\|x\|_\infty}$$
Notazione (riquadro alla lavagna): per $A\in\mathbb{C}^{n\times n}$, $A^{[1]},\dots,A^{[n]}$ sono le **colonne** di $A$ (indice in alto) e $A_{[1]},\dots,A_{[n]}$ sono le **righe** di $A$ (indice in basso).

> [!quote] Teorema
> Per ogni $A\in\mathbb{C}^{n\times n}$:
> $$\|A\|_1=\max_{j=1,\dots,n}\sum_{i=1}^n|a_{ij}|=\max\big(\|A^{[1]}\|_1,\|A^{[2]}\|_1,\dots,\|A^{[n]}\|_1\big)$$
> $$\|A\|_2=\sqrt{\rho(A^*A)}$$
> $$\|A\|_\infty=\max_{i=1,\dots,n}\sum_{j=1}^n|a_{ij}|=\max\big(\|A_{[1]}\|_1,\|A_{[2]}\|_1,\dots,\|A_{[n]}\|_1\big)$$

Il teorema **non si dimostra**.
- $\|A\|_1$ è il **massimo delle somme per colonna** (in modulo): per ogni colonna si fa la norma $1$ (somma dei moduli delle componenti), poi si prende la più grande.
- $\|A\|_\infty$ è speculare: il **massimo delle somme per riga**, cioè il massimo delle norme $1$ delle righe.
- $\|A\|_2$ è la radice quadrata del raggio spettrale di $A^*A$, dove $A^*$ è la **trasposta coniugata** di $A$.

Le norme $1$ e $\infty$ sono facili: si calcolano guardando le componenti della matrice. La norma $2$ è "più antipatica", perché richiede un raggio spettrale.

> [!example] Esempio
> Calcolare le norme $1,2,\infty$ di
> $$A=\begin{bmatrix}2&-2\\-3&-1\end{bmatrix}$$

**Norma 1** (massimo delle norme $1$ delle colonne): la prima colonna dà $2+|-3|=5$, la seconda $|-2|+|-1|=3$.
$$\|A\|_1=\max\big(\|A^{[1]}\|_1,\|A^{[2]}\|_1\big)=\max(5,3)=5$$
**Norma $\infty$** (massimo delle norme $1$ delle righe): entrambe le righe danno $4$.
$$\|A\|_\infty=\max\big(\|A_{[1]}\|_1,\|A_{[2]}\|_1\big)=\max(4,4)=4$$
**Norma 2.** La matrice è reale, quindi coniugare non cambia nulla e $A^*=A^T$:
$$A^*A=A^TA=\begin{bmatrix}2&-3\\-2&-1\end{bmatrix}\begin{bmatrix}2&-2\\-3&-1\end{bmatrix}=\begin{bmatrix}13&-1\\-1&5\end{bmatrix}$$
$A^TA$ è simmetrica, come deve essere. Il polinomio caratteristico è
$$C_{A^*A}(\lambda)=\det(\lambda I-A^*A)=\begin{vmatrix}\lambda-13&1\\1&\lambda-5\end{vmatrix}=(\lambda-13)(\lambda-5)-1=\lambda^2-18\lambda+64$$
e con la formula ridotta
$$\lambda_{1,2}=\frac{9\pm\sqrt{81-64}}{1}=9\pm\sqrt{17}$$
Entrambi gli autovalori sono positivi, quindi coincidono con i loro moduli e il più grande è quello con il $+$:
$$\|A\|_2=\sqrt{\rho(A^*A)}=\sqrt{9+\sqrt{17}}$$

> [!warning] Il coniugato di un numero reale
> Uno studente pensa che il coniugato di $2$ sia $-2$. **No**: il coniugato di un numero reale è sempre se stesso, perché non c'è parte immaginaria (il coniugato di $-2$ è $-2$). Non farsi ingannare dai segni: per una matrice reale $A^*$ è semplicemente la trasposta $A^T$, cioè le righe di $A$ diventano le colonne.

> [!warning] Somme in modulo
> Nella norma $1$ della prima colonna si fa $2+|-3|=5$, **non** $2+(-3)$: la norma $1$ è la somma dei **moduli** delle componenti. Anche nel prodotto $A^TA$ uno studente scrive $12$ invece di $4+9=13$ per l'elemento in alto a sinistra.

> [!info] La formula ridotta
> Per $ax^2+bx+c=0$ le radici si possono scrivere come
> $$x_{1,2}=\frac{-\frac b2\pm\sqrt{\left(\frac b2\right)^2-ac}}{a}$$
> È la formula usuale con numeratore e denominatore divisi per $2$; è comoda quando $b$ è pari. Qui $a=1$, $\frac b2=-9$, $c=64$.
#### Esercizio
**Esercizio 3.13.** Calcolare le norme $1,2,\infty$ delle seguenti matrici:
$$A=\begin{bmatrix}2&-1\\-1&0\end{bmatrix},\qquad B=\begin{bmatrix}2&0&-1\\-1&-3&2\\0&-2&1\end{bmatrix}$$
Calcolare inoltre $\rho(A)$ e $\rho(B)$, e verificare che
$$\rho(A)\leq\|A\|_1,\|A\|_2,\|A\|_\infty,\qquad\rho(B)\leq\|B\|_1,\|B\|_2,\|B\|_\infty$$
La verifica finale è il punto 5 del teorema sulle norme indotte: il raggio spettrale è minore o uguale di **qualsiasi** norma indotta, e le norme $1,2,\infty$ lo sono.

> [!info] Risultati parziali (nostra aggiunta, non fatti a lezione)
> Per $A$: $\|A\|_1=\|A\|_\infty=3$; $A$ è reale simmetrica, gli autovalori sono $1\pm\sqrt2$, quindi $\rho(A)=1+\sqrt2\approx2{,}41$ e $A^*A=A^2$ ha autovalori $(1\pm\sqrt2)^2$, da cui $\|A\|_2=1+\sqrt2$. Per $B$: $\|B\|_1=\max(3,5,4)=5$ e $\|B\|_\infty=\max(3,6,3)=6$; $\|B\|_2$ e $\rho(B)$ restano da calcolare.
### Equivalenza delle norme matriciali
Il docente la presenta rapidamente (solo l'enunciato), ma serve per quello che segue.

> [!quote] Teorema (equivalenza delle norme matriciali)
> Tutte le norme matriciali in $\mathbb{C}^{n\times n}$ sono equivalenti, nel senso che se prendiamo due norme matriciali $\|\cdot\|',\|\cdot\|'':\mathbb{C}^{n\times n}\to\mathbb{R}$ allora si ha
> $$\alpha\|A\|''\leq\|A\|'\leq\beta\|A\|''\qquad\forall A\in\mathbb{C}^{n\times n}$$
> dove $\alpha,\beta>0$ sono costanti **indipendenti da $A$**.

È lo stesso teorema di equivalenza già visto per le norme vettoriali. Le cose fondamentali sono il "per ogni $A$" e che le costanti non dipendano da $A$: le stesse costanti (ad esempio "$1$ e $75$") vanno bene per tutte le matrici.
### Successioni di matrici
> [!quote] Definizione (convergenza rispetto a una norma)
> Una successione di matrici $A^{(0)},A^{(1)},A^{(2)},\dots$ in $\mathbb{C}^{n\times n}$ si dice **convergente** alla matrice $A\in\mathbb{C}^{n\times n}$ rispetto alla norma matriciale $\|\cdot\|$ se
> $$\|A^{(k)}-A\|\to0\qquad\text{per }k\to\infty$$
> cioè se la distanza tra $A^{(k)}$ e $A$ secondo quella norma tende a $0$.

Siccome tutte le norme matriciali sono equivalenti, **se una successione di matrici converge ad $A$ rispetto a una norma, allora converge ad $A$ rispetto a tutte le norme** [dim. = esercizio]. Si fa esattamente come per i vettori, con il teorema dei carabinieri: va ripercorsa quella dimostrazione nel caso delle matrici, e non cambia sostanzialmente niente.

> [!info] Traccia della dimostrazione (nostra aggiunta)
> Se $\|A^{(k)}-A\|''\to0$, per l'equivalenza $0\leq\|A^{(k)}-A\|'\leq\beta\|A^{(k)}-A\|''\to0$, e per i carabinieri $\|A^{(k)}-A\|'\to0$.

> [!quote] Definizione (convergenza componente per componente)
> Una successione di matrici $\{A^{(k)}\}_{k=0,1,2,\dots}$ in $\mathbb{C}^{n\times n}$ si dice **convergente (componente per componente)** alla matrice $A\in\mathbb{C}^{n\times n}$ se $A^{(k)}\to A$ componente per componente quando $k\to\infty$, cioè se
> $$a^{(k)}_{ij}\to a_{ij}\qquad\forall i,j=1,\dots,n$$

Quando si parla di successione di matrici convergente senza specificare altro, si intende sempre la convergenza componente per componente (il docente tenderà comunque a specificarlo). Si ha:
$$a^{(k)}_{ij}\to a_{ij}\ \ \forall i,j=1,\dots,n\iff|a^{(k)}_{ij}-a_{ij}|\to0\ \ \forall i,j=1,\dots,n\iff\max_{i,j=1,\dots,n}|a^{(k)}_{ij}-a_{ij}|\to0\iff|A^{(k)}-A|_\infty\to0$$
L'equivalenza col massimo vale nei due versi: se tutte le componenti tendono a $0$ tende a $0$ anche il massimo, e se tende a $0$ il massimo (cioè la componente più grande) ci tendono anche tutte le altre. L'ultima espressione è proprio la norma $|\cdot|_\infty$ "con una stanghetta" di inizio lezione.

Quindi la convergenza componente per componente è la convergenza rispetto alla norma $|\cdot|_\infty$. Dunque, ricordando l'equivalenza di tutte le norme, **dire che $A^{(k)}\to A$ componente per componente è lo stesso che dire che $A^{(k)}\to A$ in una qualsiasi norma** (anche nella norma $\|\cdot\|_\infty$ con due stanghette, che è diversa da $|\cdot|_\infty$).

> [!info] La norma che non ci piaceva
> La norma $|\cdot|_\infty$, scartata perché non submoltiplicativa, torna utile qui: è la norma che descrive la convergenza componente per componente.
### Teorema sulle potenze di una matrice
> [!quote] Teorema
> Sia $A\in\mathbb{C}^{n\times n}$. Allora
> $$A^k\to O\iff\rho(A)<1$$

- Qui $A^k$ è proprio la **potenza** $k$-esima: $A^0=I$, $A^1=A$, $A^2$, $A^3$, ... Prima, per le successioni generiche, l'indice era scritto tra parentesi, $A^{(k)}$, proprio per non farlo sembrare una potenza.
- Tutte le potenze sono matrici $n\times n$, come $A$.
- $A^k\to O$ significa che la successione delle potenze tende, componente per componente (o equivalentemente in qualsiasi norma), alla matrice nulla.
- È un'equivalenza: se $\rho(A)<1$ le potenze tendono alla matrice nulla; se $\rho(A)\geq1$ (anche $\rho(A)=1$ non va bene) non ci tendono.
#### Dimostrazione (nel caso in cui A è diagonalizzabile)
La dimostrazione si fa solo in questo caso, altrimenti sarebbe troppo difficile.

In tal caso ([[03 - Analisi delle matrici#Matrici diagonalizzabili]]) esistono $X\in\mathbb{C}^{n\times n}$ invertibile e $D=\operatorname{diag}(\lambda_1,\lambda_2,\dots,\lambda_n)\in\mathbb{C}^{n\times n}$ diagonale, contenente sulla diagonale gli autovalori di $A$ (come dimostrato nella proposizione su $A=XDX^{-1}$), tali che
$$A=XDX^{-1}$$
Allora, siccome $X^{-1}X=I$ e moltiplicare per l'identità non cambia nulla,
$$A^2=XD\underbrace{X^{-1}X}_{I}DX^{-1}=XD^2X^{-1}$$
$$A^3=XD\underbrace{X^{-1}X}_{I}D\underbrace{X^{-1}X}_{I}DX^{-1}=XD^3X^{-1}$$
e in generale
$$A^k=XD^kX^{-1}\qquad\forall k\geq0\tag{$\ast$}$$
Il caso $k=0$ si può includere: $D^0=I$ e $XX^{-1}=I=A^0$. È lo stesso "giochino" già usato per i polinomi di matrice.

**Calcolo di $\|D^k\|_\infty$.** Si usa la norma $\infty$ perché è **submoltiplicativa** (è indotta) e perché si sa calcolare facilmente (massimo delle norme $1$ delle righe). Moltiplicando una matrice diagonale per se stessa gli elementi diagonali vengono elevati al quadrato; quindi per ogni $k\geq0$
$$D=\begin{bmatrix}\lambda_1&&O\\&\ddots&\\O&&\lambda_n\end{bmatrix}\implies D^k=\begin{bmatrix}\lambda_1^k&&O\\&\ddots&\\O&&\lambda_n^k\end{bmatrix}$$
Ogni riga di $D^k$ ha un solo elemento non nullo, quindi la sua norma $1$ è il modulo di quell'elemento:
$$\|D^k\|_\infty=\max\big(\|(D^k)_{[1]}\|_1,\dots,\|(D^k)_{[n]}\|_1\big)=\max\big(|\lambda_1^k|,\dots,|\lambda_n^k|\big)=\max\big(|\lambda_1|^k,\dots,|\lambda_n|^k\big)=\max\big(|\lambda_1|,\dots,|\lambda_n|\big)^k=\rho(A)^k$$
Si sono usati due fatti:
- per ogni $\alpha\in\mathbb{C}$ e $k\geq0$, $|\alpha^k|=|\alpha|^k$, perché il modulo di un prodotto è il prodotto dei moduli ($|\alpha^2|=|\alpha\cdot\alpha|=|\alpha|\,|\alpha|$, e così via);
- per numeri **non negativi** la potenza esce dal massimo: ad esempio $\max(3^2,7^2,9^2)=9^2=\max(3,7,9)^2$. Con numeri negativi non funzionerebbe (con potenza pari un negativo diventa positivo), ma qui ci sono dei moduli.

**($\Leftarrow$)** Supponiamo che $\rho(A)<1$. Allora, per ogni $k\geq0$, applicando la submoltiplicatività due volte (prima al prodotto di $XD^k$ e $X^{-1}$, poi a $XD^k$):
$$0\leq\|A^k\|_\infty=\|XD^kX^{-1}\|_\infty\leq\|X\|_\infty\,\|D^k\|_\infty\,\|X^{-1}\|_\infty=\|X\|_\infty\,\rho(A)^k\,\|X^{-1}\|_\infty$$
Siccome $0\leq\rho(A)<1$, si ha $\rho(A)^k\to0$ (ad esempio $\frac12,\frac14,\frac18,\frac1{16},\dots$). I fattori $\|X\|_\infty$ e $\|X^{-1}\|_\infty$ non dipendono da $k$: sono costanti, magari grandi ("$500$ e $2$ milioni"), ma costanti. Quindi il membro di destra tende a $0$, e per i **carabinieri** ($0\leq\|A^k\|_\infty\leq\dots\to0$)
$$\|A^k\|_\infty\to0\implies A^k\to O$$
perché $\|A^k\|_\infty=\|A^k-O\|_\infty$ è la distanza di $A^k$ dalla matrice nulla, e la convergenza in una norma equivale alla convergenza componente per componente.

> [!warning] Serve $0\leq\rho(A)<1$
> Le potenze di un numero tendono a $0$ se il numero è minore di $1$ **e** non negativo: $(-5)^k$ vale $25,-125,\dots$ e non tende a $0$. Per il raggio spettrale non c'è problema, perché è sempre $\geq0$.

**($\Rightarrow$)** Supponiamo che $A^k\to O$. Moltiplicando a sinistra per $X^{-1}$ e a destra per $X$ entrambi i membri della $(\ast)$ (così a destra si "mangiano" $X$ e $X^{-1}$) si ottiene
$$X^{-1}A^kX=D^k\qquad\forall k\geq0$$
Allora, usando il calcolo di $\|D^k\|_\infty$ e ancora la submoltiplicatività (due volte):
$$0\leq\rho(A)^k=\|D^k\|_\infty=\|X^{-1}A^kX\|_\infty\leq\|X^{-1}\|_\infty\,\|A^k\|_\infty\,\|X\|_\infty$$
Il fattore in mezzo $\|A^k\|_\infty\to0$ perché $A^k\to O$, e gli altri due sono costanti; quindi il membro di destra tende a $0$. Per i carabinieri (a sinistra lo $0$, costante, a destra una quantità che tende a $0$)
$$\rho(A)^k\to0\implies\rho(A)<1$$
Infatti:
- se $\rho(A)=1$, allora $\rho(A)^k=1$ per ogni $k$, che non tende a $0$;
- se $\rho(A)>1$, allora $\rho(A)^k\to\infty$ (ad esempio $2,4,8,16,\dots$);
- $\rho(A)$ è sempre $\geq0$, quindi non ci sono altre possibilità: l'unica compatibile con $\rho(A)^k\to0$ è $0\leq\rho(A)<1$. $\blacksquare$

> [!info] Perché la submoltiplicatività è così importante
> Il docente lo fa notare: in entrambe le direzioni la submoltiplicatività (applicata due volte) è il passaggio chiave. È il motivo per cui si usano le norme indotte e non, ad esempio, $|\cdot|_\infty$.

> [!warning] Da verificare
> A lezione il teorema è dimostrato solo per $A$ diagonalizzabile; l'enunciato vale per ogni $A\in\mathbb{C}^{n\times n}$, ma la dimostrazione generale non è stata fatta (né detto dove trovarla).

> [!question] Domanda tipica d'esame
> Enunciare il teorema $A^k\to O\iff\rho(A)<1$ e dimostrarlo nel caso di $A$ diagonalizzabile. Traccia: $A=XDX^{-1}\Rightarrow A^k=XD^kX^{-1}$; $\|D^k\|_\infty=\rho(A)^k$; ($\Leftarrow$) $\|A^k\|_\infty\leq\|X\|_\infty\rho(A)^k\|X^{-1}\|_\infty\to0$ e carabinieri; ($\Rightarrow$) $\rho(A)^k=\|X^{-1}A^kX\|_\infty\leq\|X^{-1}\|_\infty\|A^k\|_\infty\|X\|_\infty\to0$, carabinieri, e quindi $\rho(A)<1$ (se fosse $=1$ resterebbe $1$, se $>1$ divergerebbe).

> [!question] Domanda tipica d'esame
> Definire la convergenza di una successione di matrici rispetto a una norma e componente per componente, e spiegare perché sono equivalenti. Traccia: la convergenza componente per componente è la convergenza in $|\cdot|_\infty$ (passando per il massimo dei moduli delle differenze); per l'equivalenza delle norme matriciali, la convergenza in una norma equivale alla convergenza in tutte.

Con questo teorema si chiude l'analisi delle matrici. Dalla lezione successiva (giovedì 19/11, che si terrà **online**) comincia la risoluzione dei sistemi lineari con metodi iterativi. Il docente definisce la lezione di giovedì "impiccata" (con poco tempo) e dice che, per chi segue online, dovrà comunque arrivare fino in fondo.

> [!warning] Da verificare
> La parte finale della registrazione sull'organizzazione di giovedì (lezione online, durata) è poco comprensibile.
