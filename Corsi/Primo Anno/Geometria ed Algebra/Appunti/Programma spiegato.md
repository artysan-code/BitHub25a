# 1 - Fondamenti e vettori
L'algebra lineare non è altro che la **fusione** tra l'algebra (la manipolazione di equazioni e sistemi) e la geometria (lo studio di punti, rette, piani e forme nello spazio). Ogni concetto algebrico ha una controparte geometrica e viceversa.
## Vettori, operazioni, coordinate
Somma di vettori: $$(v+w)=(v_{x},v_{y})+(w_{x},w_{y})=(v_{x}+w_{x}),(v_{y}+w_{y})$$
Moltiplicazione per scalare$: $$k\cdot v=k\cdot(v_{x},v_{y})=(k\cdot v_{x},k\cdot v_{y})$$
## Equazioni di rette e piani
### Forma parametrica
Retta: $$P(t)=P_{0}+t\cdot v$$
Parti da un punto noto della retta ($P_{0}$), e muoviti lungo la direzione del vettore $v$. Il parametro $t$ ti dice "quanti passi" fare in quella direzione.

Piano: $$P(s,t)=P_{0}+s\cdot v+t\cdot w$$
Parti da un punto $P_{0}$ e sei libero di muoverti lungo due direzioni indipendenti ($v$ e $w$)

### Forma Cartesiana

Retta in $\mathbb{R}^{2}$: $$ax + by + c = 0$$
Piano in $\mathbb{R}^{3}$: $$ax + by + cz + d = 0$$
L'insieme di tutti i punti $(x, y, z)$  le cui coordinate soddisfano questa singola equazione. Il vettore $n = (a, b, c)$ è il **vettore normale** (perpendicolare) al piano


Rappresentano due filosofie opposte per descrivere un oggetto.
- **Parametrica (generativa):** Ti do gli ingredienti $(P_{0}, v, w)$ e le istruzioni per _costruire_ tutti i punti. È una visione dall'interno.
- **Cartesiana (restrittiva):** Ti do una regola $(ax + ... + d = 0)$ e verifico se un punto appartiene all'insieme o no. È una visione dall'esterno.
- **Connessione Profonda:** L'equazione cartesiana di un piano $a(x-x₀) + b(y-y₀) + c(z-z₀) = 0$ è equivalente a dire che il prodotto scalare tra il vettore normale $n = (a, b, c)$ e un qualsiasi vettore $(P - P₀)$ che giace sul piano è zero: $n ⋅ (P - P₀) = 0$. Questo significa che sono perpendicolari.

# 2 - Spazi vettoriali
L'obiettivo qui è generalizzare le regole che abbiamo visto in $\mathrm{R}^{2}$ e $\mathrm{R}^{3}$ a contesti molto più ampi.
## Spazio e sottospazio
### Spazio vettoriale
È un insieme $V$ di vettori su cui sono definite due operazioni (somma tra vettori e prodotto per scalare) che rispettano 8 **regole fondamentali**: 
- Chiusura della Somma: 
  Se $u$ e $v$ sono in $V$, allora anche la loro somma $u+v$ deve essere in$V$.
- Proprietà Associativa: 
  $(u+v)+w=u+(v+w)$
- Proprietà Commutativa: 
  $u+v=v+u$
- Esistenza dell'Elemento Neutro (Vettore Nullo):
  Esiste un vettore speciale, il **vettore nullo** $0V$​, tale che per ogni vettore $v$ in $V$ si ha: $v+0V​=v$.
- Esistenza dell'Opposto:
  Per ogni vettore $v$ in $V$, esiste un vettore opposto $−v$ tale che: $v+(−v)=0V$​.
- Chiusura del Prodotto per Scalare:
  Se $v$ è in $V$ e $k$ è uno scalare, allora anche il prodotto $k⋅v$ deve essere in $V$.
- Proprietà Distributiva (rispetto alla somma di vettori):
  $k⋅(u+v)=k⋅u+k⋅v$
- Proprietà Distributiva (rispetto alla somma di scalari):
  $(k+h)⋅v=k⋅v+h⋅v$
- Proprietà Associativa (del prodotto per scalare):
  $(k⋅h)⋅v=k⋅(h⋅v)$
- Esistenza dell'Elemento Neutro della Moltiplicazione:
  Lo scalare 1 agisce come elemento neutro: $1⋅v=v$.

### Sottospazio vettoriale
È un sottoinsieme $W$ di uno spazio vettoriale $V$ che è a sua volta uno spazio vettoriale. Per verificarlo, non devi controllare tutti gli 8 assiomi. Bastano 3 condizioni:
- Contiene il vettore nullo:
  $0\in W$
- Chiuso rispetto alla somma:
  Se $w_{1},w_{2}\in W$, allora $w_{1}+w_{2}\in W$.
- Chiuso rispetto al prodotto per scalare:
  Se $w\in W$ e $k$ è uno scalare, allora $k\cdot w\in W$.

## Combinazioni lineari e sottospazio generato
### Combinazione lineare
È una somma pesata di vettori. Dati i vettori $v_{1},v_{2},\dots,v_{k}$ e gli scalari $c_{1},c_{2},\dots,c_{k}$, una loro combinazione lineare è:$$w=c_{1}v_{1}+c_{2}v_{2}+\dots+c_{k}v_{k}$$
### Sottospazio generato (Span)
Lo $Span(v_{1},\dots,v_{k})$ è l'insieme di **tutte le possibili** combinazioni lineari che puoi formare con i vettori $v_{1},\dots,v_{k}$.
È l'insieme di tutti i punti che puoi raggiungere partendo dall'origine e potendoti muovere solo nelle direzioni $v_{1},\dots,v_{k}$.
Lo Span di un vettore non nullo è la **retta** passante per l'origine con quella direzione.
Lo Span di due vettori non paralleli è il **piano** passante per l'origine che li contiene.

>**Teorema chiave:** 
>Lo $Span(v_{1},\dots,v_{k})$ è sempre un **sottospazio vettoriale**.

# 3 - Il Cuore degli Spazi Vettoriali
Capire quando un insieme di vettori è linearmente dipendente o indipendente è la chiave per comprendere la struttura di uno spazio vettoriale.
## Dipendenza e Indipendenza Lineare
Immagina di avere un insieme di vettori in uno spazio vettoriale $V$. La domanda fondamentale che ci poniamo è: "Posso esprimere uno di questi vettori come una combinazione degli altri?"

>**Definizione (Indipendenza Lineare)**:
>Un insieme di vettori $\{v_{1},v_{2},…,v_{n}​\}$ in uno spazio vettoriale $V$ si dice **linearmente indipendente** se l'unica combinazione lineare di questi vettori che dà come risultato il vettore nullo è quella con tutti i coefficienti (scalari) nulli. $$c_{1}v_{1}​+c_{2}v_{2}​+⋯+c_{n}v_{n}=0 \implies c_{1}​=c_{2}​=⋯=c_{n}​=0$$

>**Definizione (Dipendenza Lineare)**:
>Un insieme di vettori è **linearmente dipendente** se non è linearmente indipendente. Questo significa che esiste almeno una combinazione lineare dei vettori che dà il vettore nullo, con almeno un coefficiente diverso da zero.

- **Ipotesi Comune**: Se ho tanti vettori, è più probabile che siano dipendenti.
- **Analisi**: Questa intuizione è corretta. In uno spazio di dimensione $n$, qualsiasi insieme di $n+1$ o più vettori è necessariamente linearmente dipendente. Pensa a $\mathbb{R}^{2}$ (il piano): se prendi tre vettori, uno sarà sempre "superfluo", esprimibile come combinazione degli altri due.
- **Contro argomentazione** :"Ma allora l'indipendenza è una proprietà rara?" No, è una proprietà *fondamentale*. I vettori linearmente indipendenti sono i "mattoni" essenziali e non ridondanti dello spazio. La dipendenza lineare indica semplicemente una ridondanza nell'insieme di vettori che stai considerando.

### Geometricamente parlando
**Due vettori:** Sono linearmente dipendenti se e solo se sono paralleli (uno è un multiplo scalare dell'altro). Giacciono sulla stessa retta passante per l'origine.

**Tre vettori:** Sono linearmente dipendenti se e solo se sono complanari (giacciono sullo stesso piano passante per l'origine).

**In generale:** Un insieme di vettori è linearmente dipendente se "collassa" in un sottospazio di dimensione inferiore a quanti sono i vettori.
## Concetto di Base di uno spazio vettoriale
Una base è l'insieme "perfetto" di vettori per descrivere uno spazio vettoriale. Non è né troppo piccolo (non genera tutto lo spazio) né troppo grande (contiene vettori ridondanti).

>**Definizione**: 
>Un insieme di vettori $B=\{v_{1},v_{2}​,…,v_{n}\}$ in uno spazio vettoriale $V$ è una **base** di $V$ se soddisfa due condizioni: 
>    - **Genera lo spazio:** 
>      Ogni vettore $v\in V$ può essere scritto come combinazione lineare dei vettori di $B$. (Si dice che $V=Span(B)$).
>    - **È linearmente indipendente:** I vettori in $B$ sono linearmente indipendenti.

**Ipotesi Comune**:"La base di uno spazio vettoriale è unica."
**Analisi**: Questo è un errore comune e fondamentale. Uno spazio vettoriale (tranne quello banale $\{0\}$) ha *infinite basi*.    
	**Esempio:** In $\mathbb{R}^{2}$, la base più comune è la *base canonica* $E=\{(1,0),(0,1)\}$. Ma anche $B_{1}=\{(1,1),(1,-1)\}$ è una base valida. E così anche $B_{2}=\{(2,3),(1,0)\}$.
**Contro argomentazione**: "Se ci sono infinite basi, a cosa serve il concetto? Sembra arbitrario." 
Il punto cruciale non è _quale_ base scegli, ma il fatto che, una volta scelta una base, ogni vettore dello spazio ha una *rappresentazione unica* come combinazione lineare dei vettori di quella base. Quei coefficienti unici sono chiamati le *coordinate* del vettore rispetto a quella base.

# 3.1 - Dimensione e Teoremi sulle Basi
Questi teoremi sono il collante che tiene insieme la teoria. Non sono solo risultati astratti, ma strumenti operativi potentissimi.
## Teorema della Dimensione (o di Grassmann)
Sebbene uno spazio vettoriale abbia infinite basi, tutte le basi di un dato spazio vettoriale hanno lo *stesso numero di vettori* . Questo numero è una proprietà intrinseca dello spazio e viene chiamato *dimensione*.

>**Definizione Dimensione**: La *dimensione* di uno spazio vettoriale V, denotata con dim(V), è il numero di vettori in una qualsiasi delle sue basi.
>	$dim(\mathbb{R}^{n})=n$
>	$dim(M_{m,n}​(\mathbb{R}))=m×n$ (lo spazio delle matrici m×n)
>	$dim(\mathbb{R}_{n}​[x])=n+1$ (lo spazio dei polinomi di grado al più n)

La costanza del numero di vettori in una base è una conseguenza diretta del **Teorema di Steinitz (o del Rimpiazzamento)**, che è il vero motore tecnico dietro a questi risultati. 
Esso afferma, in sostanza, che se hai un insieme di generatori e un insieme di vettori linearmente indipendenti, il numero di vettori indipendenti non può superare il numero di generatori.

## Teorema di Esistenza e di Completamento della Base
Questi due teoremi garantiscono che le basi non sono oggetti rari o difficili da trovare.

### Teorema di Esistenza della Base (o di Estrazione)
Da ogni insieme di generatori di uno spazio vettoriale $V$ è sempre possibile **estrarre** una base di $V$.

*Implicazione pratica*: Se hai un insieme di vettori che generano il tuo spazio, potresti avere della ridondanza. Questo teorema ti dice che puoi "buttare via" i vettori superflui (quelli linearmente dipendenti dagli altri) fino a rimanere con un insieme linearmente indipendente che genera ancora lo stesso spazio: una base.

### Teorema del Completamento a Base
Ogni insieme di vettori linearmente indipendenti in uno spazio vettoriale $V$ di dimensione finita può essere **esteso (o completato)** a una base di $V$.

*Implicazione pratica*: Se hai un insieme di vettori "buoni" ma non sufficienti a generare tutto lo spazio, questo teorema ti garantisce che puoi "pescare" altri vettori da V per completare il tuo set fino a formare una base.

**Contro argomentazione**: "Questi teoremi sembrano ovvi. Se ho dei generatori, tolgo quelli inutili. Se ho pochi vettori indipendenti, ne aggiungo altri. Dov'è la difficoltà?" La potenza di questi teoremi sta nel garantire che queste procedure *funzionano sempre* e *terminano* in un numero finito di passi (in spazi di dimensione finita). Non è scontato a priori che, eliminando un vettore dipendente, i rimanenti generino ancora lo stesso spazio, o che sia sempre possibile trovare un vettore "nuovo" da aggiungere che sia indipendente dai precedenti.

# 4 - Applicazioni Lineari e Matrici
L'idea centrale che unisce tutto è questa: le *applicazioni lineari* sono le funzioni "ben educate" degli spazi vettoriali, e le *matrici* sono lo strumento numerico con cui le descriviamo e le manipoliamo.
## Matrici e operazioni
Una **matrice** non è altro che una tabella rettangolare di numeri (reali o complessi). 
La indichiamo come $A\in M_{m,n}(k)$, dove $m$ è il numero di righe, $n$ il numero di colonne e $K$ è il campo numerico di riferimento (solitamente $\mathbb{R}$ o $\mathbb{C}$).
Le operazioni fondamentali sono:
- **Somma di matrici**: 
  Si possono sommare solo matrici con le **stesse dimensioni** $(m×n)$. La somma $C=A+B$ è definita elemento per elemento: $c_{ij}=a_{ij}+b_{ij}$
- **Prodotto per uno scalare**: Dato uno scalare $c\in K$, il prodotto $B=cA$ si ottiene moltiplicando ogni elemento di $A$ per $c:b_{ij}=ca_{ij}$​.
- **Prodotto tra matrici (righe per colonne)**: Questa è l'operazione più importante e meno intuitiva. Date due matrici $A\in M_{m,p}$ e $B\in M_{p,n}$​, il loro prodotto è una matrice $C=AB\in M_{m,n}$​. L'elemento $c_{ij}$​ della matrice prodotto si ottiene moltiplicando scalarmente la i-esima riga di $A$ per la j-esima colonna di $B$.$$c_{ij}=\sum_{k=1}^{p}a_{ik}b_{kj}$$ Questa definizione è costruita specificamente per rappresentare la **composizione di applicazioni lineari**. Se l'applicazione $f$ è rappresentata dalla matrice $A$ e l'applicazione $g$ dalla matrice $B$, allora l'applicazione composta $(g\circ f)(v)=g(f(v))$ è rappresentata dalla matrice prodotto $BA$. L'ordine è invertito, un dettaglio cruciale!
## Applicazioni Lineari (omomorfismi)
Un'**applicazione lineare** (o omomorfismo di spazi vettoriali) è una funzione $f:V\to W$ tra due spazi vettoriali $V$ e $W$ che "preserva le operazioni" di somma e prodotto per scalare. Formalmente, per ogni $v_{1},v_{2}\in V$ e ogni scalare $c\in K$:
1. $f(v_{1}+v_{2})=f(v_{1})+f(v_{2}​)$ (additività)
2. $f(cv_{1}​)=cf(v_{1})$ (omogeneità di primo grado)

Geometricamente, significa che la trasformazione non "distorce" lo spazio in modo selvaggio. Le rette vengono trasformate in rette (o in un punto, se la retta appartiene al nucleo), e l'origine dello spazio di partenza $V$ viene sempre mappata nell'origine dello spazio di arrivo $W$ (infatti,$f(0_V)=0_W$).
- Esempi di trasformazioni lineari: rotazioni, riflessioni, proiezioni, omotetie (scaling).
- Esempio di trasformazione *non* lineare: una traslazione, perché non manda l'origine in sé stessa.

*Il ponte tra Matrici e Applicazioni Lineari*: Fissata una base $BV$​ per $V$ e una base $BW$​ per $W$, ogni applicazione lineare $f:V\to W$ può essere rappresentata in modo univoco da una matrice $A$. Le colonne della matrice $A$ sono semplicemente le coordinate, rispetto alla base $BW$​, dei vettori ottenuti applicando $f$ ai vettori della base $BV$​.
## Nucleo (Ker) e Immagine (Im)
Questi sono due sottospazi fondamentali associati a ogni applicazione lineare $f:V\to W$.
- **Immagine (Im(f))**: È l'insieme di tutti i possibili risultati dell'applicazione. È un sottospazio del *codominio* $W$.$$\mathrm{Im}(f)=\{w\in W|\ \exists\ v\in V\text{ tale che }f(v)=w\}$$
- Se $A$ è la matrice associata a $f$, l'Immagine è lo spazio generato dai vettori colonna di $A$ (il cosiddetto "spazio delle colonne"). 
	  L'immagine ci dice "dove va a finire" lo spazio $V$ dopo essere stato trasformato da $f$. Se $f$ è una proiezione di $\mathbb{R}^{3}$ su un piano, la sua immagine è quel piano.

- **Nucleo (Kernel, Ker(f))**: È l'insieme di tutti i vettori del **dominio** $V$ che vengono mappati nel vettore nullo di $W$.$$\mathrm{Ker}(f)=\{v\in V|\ f(v)=0_W\}$$
  Il Nucleo è una misura di "quanta informazione viene persa" nella trasformazione.
	- Se $Ker(f)={0_V​}$ (contiene solo il vettore nullo), significa che nessun vettore non nullo viene annullato. La trasformazione è **iniettiva**: vettori distinti in $V$ vengono mandati in vettori distinti in $W$.
	- Se $Ker(f)$ ha dimensione maggiore di zero, l'applicazione "schiaccia" interi sottospazi di $V$ su un singolo punto (l'origine). La trasformazione *non* è *iniettiva*. Per esempio, nella proiezione da $\mathbb{R}^{3}$ a un piano, il nucleo è la retta perpendicolare al piano passante per l'origine.
# 4.1 - Rango
## Rango di un'applicazione lineare
Il **rango** (o caratteristica) di un'applicazione lineare $f$, denotato con $rank(f)$ o $rg(f)$, è semplicemente la **dimensione dello spazio Immagine**.$$rank(f)=dim(\mathrm{Im}(f))$$
- Il rango ci dice quante sono le "dimensioni effettive" dell'output. Una trasformazione può partire da uno spazio a 10 dimensioni ($V=\mathbb{R}^{10}$) e arrivare in uno spazio a 20 dimensioni ($W=\mathbb{R}^{20}$), ma se la sua immagine è un piano, il suo rango è 2. Ci dice quanto "complesso" o "dimensionale" è il risultato della trasformazione.
- Il rango di un'applicazione lineare è uguale al rango della sua matrice associata. Il rango di una matrice è il numero massimo di righe (o colonne) linearmente indipendenti.
## Teorema del Rango (o della dimensione)
Per un'applicazione lineare $f:V\to W$, dove $V$ ha dimensione finita, vale la seguente relazione: $$dim(V)=dim(Ker(f))+dim(\mathrm{Im}(f))$$
Usando la terminologia del rango, si scrive più comunemente: $$dim(V)=nullity(f)+rank(f)$$
dove $nullity(f)=dim(Ker(f))$ è la "nullità" di $f$.
Questo teorema esprime una sorta di "legge di conservazione della dimensione". Dice che la dimensione dello spazio di partenza si ripartisce esattamente in due parti:
1. La parte che viene "schiacciata" a zero (la dimensione del Nucleo).
2. La parte che "sopravvive" e forma l'output (la dimensione dell'Immagine, cioè il rango).

Supponiamo di avere $f:\mathbb{R}^{5}\to \mathbb{R}^{3}$. La dimensione del dominio è 5. 
Se scopriamo che il nucleo ha dimensione 2 (cioè, c'è un intero piano in $\mathbb{R}^{5}$ che viene mappato a zero in $\mathbb{R}^{3}$), il teorema ci garantisce _immediatamente_ che il rango deve essere 5−2=3. 
Questo significa che l'applicazione è **suriettiva** (la sua immagine copre tutto il codominio $\mathbb{R}^{3}$).
	Questo è estremamente utile: calcolare la dimensione del nucleo (risolvendo il sistema omogeneo $Ax=0$) è spesso molto più semplice che calcolare una base per l'immagine. 
	Il teorema ci regala la dimensione dell'immagine senza sforzo.
## Esercizi
#### Esercizio 1: Verifica di Indipendenza Lineare in $\mathbb{R}^{2}$  
I vettori $v_{1}​=(2,1)$ e $v_{2}​=(−4,−2)$ di $\mathbb{R}^{2}$ sono linearmente indipendenti o dipendenti?
**Soluzione Spiegata:** 
Per verificare l'indipendenza lineare, dobbiamo vedere se l'unica combinazione lineare dei vettori che dà il vettore nullo è quella con coefficienti tutti nulli. 
Impostiamo l'equazione: $c_{1}v_{1}+c_{2}v_{2}​=0$$$c_1 (2, 1) + c_2 (-4, -2) = (0, 0)$$
Questo si traduce nel sistema di equazioni lineari:$$\begin{cases} 2c_1 - 4c_2 = 0 \\ 1c_1 - 2c_2 = 0 \end{cases} $$ Notiamo subito che la prima equazione è esattamente il doppio della seconda. Questo significa che le due equazioni sono dipendenti e il sistema ha infinite soluzioni. Per esempio, dalla seconda equazione otteniamo $c_{1}=2c_{2}$​. Se scegliamo $c_{2}​=1$, allora $c_{1}​=2$. Infatti:$$2⋅(2,1)+1⋅(−4,−2)=(4,2)+(−4,−2)=(0,0)$$
Abbiamo trovato una soluzione non banale (con coefficienti non tutti nulli).

**Conclusione:** 
I vettori sono **linearmente dipendenti**. 
Geometricamente, questo significa che i due vettori giacciono sulla stessa retta passante per l'origine.

#### Esercizio 2: Verifica di Indipendenza Lineare in $\mathbb{R}^{3}$ 
Determinare se i vettori $u=(1,2,3)$, $v=(0,1,2)$ e $w=(2,0,1)$ in $\mathbb{R}^{3}$ sono linearmente indipendenti.
**Soluzione Spiegata:** 
Il metodo più rapido per 3 vettori in $\mathbb{R}^{3}$(o $n$ vettori in $\mathbb{R}^{n}$) è calcolare il **determinante** della matrice che ha questi vettori come colonne (o righe). 
Se il determinante è diverso da zero, i vettori sono linearmente indipendenti.
Costruiamo la matrice A:$$A=\begin{pmatrix}
1 & 0 & 2 \\
2 & 1 & 0 \\
3 & 2 & 1
\end{pmatrix}$$Calcoliamo il determinante (usando lo sviluppo di Laplace lungo la prima riga):
$$\begin{array}{l}
det(A)=1⋅(1⋅1−0⋅2)−0⋅(…)+2⋅(2⋅2−1⋅3) \\
det(A)=1⋅(1)+2⋅(4−3)=1+2⋅(1)=3
\end{array}$$
Poiché $det(A)=3\neq0$.
**Conclusione:** 
I vettori sono **linearmente indipendenti**. 
Questo implica anche che essi formano una **base** per $\mathbb{R}^{3}$, poiché sono 3 vettori linearmente indipendenti in uno spazio di dimensione 3.
#### Esercizio 3: I Vettori formano una Base?
I vettori $v_1 ​=(1,1,0)$, $v_2 ​=(1,0,1)$ e $v_3 ​=(0,1,−1)$ formano una base per $\mathbb{R}^{3}$?
**Soluzione Spiegata:** 
Per formare una base di $\mathbb{R}^{3}$, abbiamo bisogno di 3 vettori linearmente indipendenti. Come nell'esercizio precedente, usiamo il determinante.$$\begin{array}{l}
A=\begin{pmatrix}
1 & 1 & 0 \\
1 & 0 & 1 \\
0 & 1 & -1
\end{pmatrix} \\
det(A)=1⋅(0⋅(−1)−1⋅1)−1⋅(1⋅(−1)−1⋅0)+0⋅(…) \\
det(A)=1⋅(−1)−1⋅(−1)=−1+1=0
\end{array}$$Poiché il determinante è zero, i vettori non sono linearmente indipendenti.
**Conclusione:** 
I vettori **non formano una base** per $\mathbb{R}^{3}$. 
Infatti, esiste una relazione di dipendenza lineare tra loro: si può notare che $v_3 ​=v_1 ​−v_2$ ​.

#### Esercizio 4: Trovare le Coordinate di un Vettore rispetto a una Base
Data la base $B={b_{1}​=(1,1),b_{2}​=(1,−1)}$ di $\mathbb{R}^{2}$, trovare le coordinate del vettore $v=(3,5)$ rispetto a questa base.
**Soluzione Spiegata:** 
Cercare le coordinate di $v$ rispetto a $B$ significa trovare due scalari $c_1 ​,c_2$ ​ tali che: $v=c_1 ​b_1​+c_2 ​b_2$​$$(3, 5) = c_1 (1, 1) + c_2 (1, -1)$$Questo porta al sistema:$$\begin{cases} c_1 + c_2 = 3 \\ c_1 - c_2 = 5 \end{cases} $$Sommando le due equazioni, otteniamo:
$$2c_1 ​=8\implies c_1 ​=4$$
Sostituendo $c_1 ​=4$ nella prima equazione:$$4+c_2 ​=3\implies c_2 ​=−1$$Le coordinate di v rispetto alla base $B$ sono ($4,−1$).
**Conclusione:** 
Il vettore delle coordinate è $[v]_{\mathcal{B}}​=(4−1​)$.
#### Esercizio 5: Estrarre una Base da un Insieme di Generatori
Dato l'insieme di vettori $S=\{v_1 ​=(1,0,1),v_2 ​=(0,1,1),v_3 ​=(1,1,2),v_{4}=(2,1,3)\}$ in $\mathbb{R}^{3}$, trovare una base per il sottospazio $W=Span(S)$ e determinarne la dimensione.
**Soluzione Spiegata:** 
Per trovare una base, dobbiamo scartare i vettori che sono combinazione lineare degli altri. 
Disponiamo i vettori come colonne di una matrice e la riduciamo a scala (metodo di *eliminazione di Gauss*). 
Le colonne che conterranno i **pivot** corrisponderanno ai vettori linearmente indipendenti dell'insieme originale. $$A=\begin{pmatrix}
1 & 0 & 1 & 2 \\
0 & 1 & 1 & 1 \\
1 & 1 & 2 & 3
\end{pmatrix}$$Applichiamo le operazioni elementari sulle righe ($R_3 ​→R_3 ​−R_1$ ​ e poi $R_3 ​→R_3 ​−R_2$​): $$\begin{pmatrix}
1 & 0 & 1 & 2 \\
0 & 1 & 1 & 1 \\
1 & 1 & 2 & 3
\end{pmatrix}\overset{R_{3}-R_{1}}{\longrightarrow}
\begin{pmatrix}
1 & 0 & 1 & 2 \\
0 & 1 & 1 & 1 \\
0 & 1 & 1 & 1
\end{pmatrix}\overset{R_{3}-R_{2}}{\longrightarrow}
\begin{pmatrix}
\underline{1} & 0 & 1 & 2 \\
0 & \underline{1} & 1 & 1 \\
0 & 0 & 0 & 0
\end{pmatrix}$$La matrice ridotta a scala ha due pivot (gli elementi sottolineati), nelle colonne 1 e 2. Questo significa che i vettori originali corrispondenti a queste colonne, $v_1$ ​ e $v_2$ ​, formano una base per $W$.
**Conclusione:** 
Una base per $W$ è $\mathcal{B}_{W}​={(1,0,1),(0,1,1)}$. 
La dimensione di $W$ è il numero di vettori nella sua base, quindi $dim(W)=2$.

#### Esercizio 6: Completamento a Base
Dato il vettore $v_1 ​=(1,2,0)$ in $\mathbb{R}^{3}$, completarlo a una base di $\mathbb{R}^{3}$.
**Soluzione Spiegata:** 
Dobbiamo trovare altri due vettori, $v_2$ ​ e $v_3$ ​, tali che {$v_1 ​,v_2 ​,v_3$} sia un insieme di vettori linearmente indipendenti. 
Il modo più semplice è scegliere vettori "facili" (ad esempio dalla base canonica) e verificare l'indipendenza.
1. Aggiungiamo un vettore della base canonica, ad esempio $e_{1}​=(1,0,0)$. 
   I vettori $v_1 ​=(1,2,0)$ e $e_{1}​=(1,0,0)$ non sono uno multiplo dell'altro, quindi sono linearmente indipendenti.
2. Ora cerchiamo un terzo vettore $v_3$ ​ tale che il determinante della matrice formata da $v_1$ ​,$e_{1}$,$v_3$ ​ sia non nullo. 
	Proviamo con $e_{3}​=(0,0,1)$. $$A = \begin{pmatrix} 1 & 1 & 0 \ 2 & 0 & 0 \ 0 & 0 & 1 \end{pmatrix}$$
Calcoliamo il determinante sviluppando lungo la terza colonna: $$\det(A) = +1 \cdot \det \begin{pmatrix} 1 & 1 \\ 2 & 0 \end{pmatrix} = 1 \cdot (1 \cdot 0 - 1 \cdot 2) = -2$$Poiché $\det(A) = -2 \neq 0$, i tre vettori sono linearmente indipendenti. 
**Conclusione:** 
Una possibile base è $\mathcal{B} = \{ (1, 2, 0), (1, 0, 0), (0, 0, 1) \}$. 
La soluzione non è unica. 
#### Esercizio 7: Spazi di Polinomi
Nello spazio vettoriale $\mathbb{R}_2[x]$ dei polinomi di grado al più 2, determinare se i polinomi $p_1(x) = 1 + x$, $p_2(x) = x + x^2$ e $p_3(x) = 1 - x^2$ sono linearmente indipendenti. 
**Soluzione Spiegata:** 
Associamo a ogni polinomio il suo vettore di coordinate rispetto alla base canonica $\mathcal{C} = \{1, x, x^2\}$: * $$p_1(x) \implies [\mathbf{p}_1]_{\mathcal{C}} = (1, 1, 0)$$ $$p_2(x) \implies [\mathbf{p}_2]_{\mathcal{C}} = (0, 1, 1)$$ $$p_3(x) \implies [\mathbf{p}_3]_{\mathcal{C}} = (1, 0, -1)$$Ora il problema è diventato: i vettori $(1, 1, 0), (0, 1, 1), (1, 0, -1)$ sono linearmente indipendenti in $\mathbb{R}^3$? Calcoliamo il determinante della matrice associata:$$A = \begin{pmatrix} 1 & 0 & 1 \ 1 & 1 & 0 \ 0 & 1 & -1 \end{pmatrix}$$ $$\det(A) = 1(1 \cdot (-1) - 0 \cdot 1) - 0(\dots) + 1(1 \cdot 1 - 1 \cdot 0) = -1 + 1 = 0$$Il determinante è nullo. 
**Conclusione:**
I polinomi sono **linearmente dipendenti**. 
#### Esercizio 8: Indipendenza Lineare con un Parametro
Discutere al variare del parametro $k \in \mathbb{R}$ l'indipendenza lineare dei vettori $\mathbf{v}_1 = (1, k, 0)$, $\mathbf{v}_2 = (k, 1, 1)$, $\mathbf{v}_3 = (1, 1, k)$. Per quali valori di $k$ formano una base di $\mathbb{R}^3$? 
**Soluzione Spiegata:** 
I tre vettori formano una base di $\mathbb{R}^3$ se e solo se sono linearmente indipendenti, ovvero se il determinante della matrice che li ha per colonne è diverso da zero.$$A_k = \begin{pmatrix} 1 & k & 1 \ k & 1 & 1 \ 0 & 1 & k \end{pmatrix}$$Calcoliamo il determinante:$$\det(A_k) = 1(1 \cdot k - 1 \cdot 1) - k(k \cdot k - 1 \cdot 0) + 1(k \cdot 1 - 1 \cdot 0)$$$$\det(A_k) = k - 1 - k^3 + k = -k^3 + 2k - 1$$I vettori sono linearmente dipendenti quando $\det(A_k) = 0$, quindi risolviamo l'equazione $k^3 - 2k + 1 = 0$. 
Si nota per ispezione che $k=1$ è una radice. 
Dividendo il polinomio per $(k-1)$ (con la regola di Ruffini), otteniamo $(k-1)(k^2 + k - 1) = 0$. 
Le radici di $k^2 + k - 1 = 0$ sono $\displaystyle k = \frac{-1 \pm \sqrt{1^2 - 4(1)(-1)}}{2} = \frac{-1 \pm \sqrt{5}}{2}$. 
**Conclusione:** 
I vettori sono **linearmente dipendenti** (e non formano una base) per $\displaystyle k \in \{ 1, \frac{-1 + \sqrt{5}}{2}, \frac{-1 - \sqrt{5}}{2} \}$. 
I vettori sono **linearmente indipendenti** (e formano una base) per $\displaystyle k \in \mathbb{R} \setminus \{ 1, \frac{-1 \pm \sqrt{5}}{2} \}$. 
#### Esercizio 9: Dimensione e Base di un Sottospazio Intersezione
Siano $U = \text{Span}\{(1,1,0), (0,1,1)\}$ e $V = \text{Span}\{(1,0,1), (0,0,1)\}$ due sottospazi di $\mathbb{R}^3$. 
Trovare la dimensione e una base per il sottospazio intersezione $U \cap V$. 
**Soluzione Spiegata:** 
**Scriviamo le equazioni cartesiane dei sottospazi.** 
	Per $U$: un generico vettore $(x,y,z) \in U$ si scrive come $a(1,1,0) + b(0,1,1) = (a, a+b, b)$. 
	Da cui $x=a, z=b \implies y = x+z$. 
	L'equazione di $U$ è $x - y + z = 0$. 
	Per $V$: un generico vettore $(x,y,z) \in V$ si scrive come $c(1,0,1) + d(0,0,1) = (c, 0, c+d)$. 
	L'equazione di $V$ è chiaramente $y=0$. 2. 
	L'intersezione $U \cap V$ è l'insieme dei vettori che soddisfano entrambe le equazioni. 
	Mettiamo a sistema le equazioni cartesiane:$$\begin{cases} x - y + z = 0 \\ y = 0 \end{cases}$$Sostituendo la seconda nella prima otteniamo $x+z=0$, cioè $x=-z$. 
	Un generico vettore di $U \cap V$ ha quindi la forma $(x,y,z) = (-z, 0, z)$. 
	Possiamo scriverlo come $z(-1, 0, 1)$. 
**Conclusione:** 
	Una base per $U \cap V$ è $\displaystyle \mathcal{B}_{U \cap V} = \{ (-1, 0, 1) \}$. 
	La dimensione dell'intersezione è $\dim(U \cap V) = 1$. 
#### Esercizio 10: Spazio di Matrici
Nello spazio vettoriale $M_{2,2}(\mathbb{R})$ delle matrici $2 \times 2$, considerare il sottospazio $W$ delle matrici simmetriche. 
Trovare una base per $W$ e calcolarne la dimensione. 
**Soluzione Spiegata:** 
Una matrice $A \in M_{2,2}(\mathbb{R})$ è simmetrica se $A = A^T$. 
Una generica matrice $A$ si scrive come:$$A = \begin{pmatrix} a & b \\ c & d \end{pmatrix}$$La condizione $A = A^T$ implica $b=c$. Quindi, una generica matrice simmetrica $2 \times 2$ ha la forma:$$A = \begin{pmatrix} a & b \\ b & d \end{pmatrix}$$dove $a,b,d$ sono scalari reali arbitrari. Possiamo decomporre questa matrice generica come una combinazione lineare:$$\begin{pmatrix} a & b \\ b & d \end{pmatrix} = a \begin{pmatrix} 1 & 0 \\ 0 & 0 \end{pmatrix} + b \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix} + d \begin{pmatrix} 0 & 0 \\ 0 & 1 \end{pmatrix}$$
Le tre matrici che appaiono nella combinazione lineare generano lo spazio $W$ e sono anche linearmente indipendenti.
**Conclusione:**
Una base per il sottospazio $W$ delle matrici simmetriche $2\times2$ è $$\mathcal{B}_W = \left\{ \begin{pmatrix} 1 & 0 \\ 0 & 0 \end{pmatrix}, \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix}, \begin{pmatrix} 0 & 0 \\ 0 & 1 \end{pmatrix} \right\}$$
La $Dim(W)=3$.
# 5 - Sistemi Lineari
In questa sezione, esploreremo i concetti fondamentali relativi ai sistemi di equazioni lineari, dalla loro rappresentazione matriciale ai teoremi che ne governano le soluzioni, fino all'algoritmo pratico per risolverli.
## Sistemi Lineari - Teoria
### Formulazione Matriciale
Un qualsiasi sistema di $m$ equazioni lineari in $n$ incognite può essere scritto in una forma molto più compatta ed elegante utilizzando le matrici.

Consideriamo un generico sistema:
$$\begin{cases} a_{11}x_1 + a_{12}x_2 + \dots + a_{1n}x_n = b_1 \\ a_{21}x_1 + a_{22}x_2 + \dots + a_{2n}x_n = b_2 \\ \vdots \\ a_{m1}x_1 + a_{m2}x_2 + \dots + a_{mn}x_n = b_m \end{cases} $$Questo sistema può essere rappresentato come un'unica equazione matriciale: **$A\mathbf{x} = \mathbf{b}$** Dove: $A$ è la **matrice dei coefficienti**, una matrice di dimensione $m \times n$:
$$A = \begin{pmatrix} a\_{11} & a\_{12} & \dots & a\_{1n} \\
 a\_{21} & a\_{22} & \dots & a\_{2n} \\
 \vdots & \vdots & \ddots & \vdots \\
 a\_{m1} & a\_{m2} & \dots & a\_{mn}
\end{pmatrix} $$
- $\mathbf{x}$ è il **vettore colonna delle incognite**, di dimensione $n\times1$: $$\mathbf{x} = \begin{pmatrix} 
x\_1 \\
x\_2 \\
\vdots \\
x\_n
\end{pmatrix}$$
- $\mathbf{b}$ è il **vettore colonna dei termini noti**, di dimensione $m\times1$:
$$\mathbf{b} = \begin{pmatrix}
b\_1 \\
b\_2 \\
\vdots \\
b\_m \end{pmatrix}$$
Questa formulazione non è solo una notazione più comoda, ma è fondamentale perché permette di applicare tutta la potenza dell'algebra delle matrici per studiare e risolvere i sistemi.

### Teorema di Struttura per le Soluzioni
Questo teorema descrive come è fatto l'insieme di tutte le soluzioni di un sistema lineare $A\mathbf{x}=\mathbf{b}$.
Il teorema afferma che: 
La soluzione generale di un sistema **lineare non omogeneo** ($A\mathbf{x}=\mathbf{b}$) è data dalla somma di una soluzione particolare ($\mathbf{x}_p$) del sistema stesso e della soluzione generale del sistema omogeneo associato ($A\mathbf{x}=\mathbf{0}$).
In simboli: $\mathbf{x}_{gen}=\mathbf{x}_p+\mathbf{x}_0$
Dove:
- $\mathbf{x}_{gen}$ è l'insieme di *tutte* le possibili soluzioni del sistema $A\mathbf{x}=\mathbf{b}$.
- $\mathbf{x}_p$ è una *qualsiasi* soluzione che soddisfa l'equazione $A\mathbf{x}=\mathbf{b}$.
- $\mathbf{x}_0$ è l'insieme di tutte le soluzioni del **sistema omogeneo associato** $A\mathbf{x}=\mathbf{0}$. L'insieme di queste soluzioni forma uno spazio vettoriale, chiamato **spazio nullo** o **kernel** della matrice $A$.
#### In pratica, cosa significa?
Significa che se trovi anche solo *una* soluzione al tuo sistema, puoi trovare tutte le altre aggiungendo a quella le soluzioni del sistema omogeneo associato. Questo "sposta" geometricamente lo spazio nullo (che passa sempre per l'origine) facendolo passare per il punto rappresentato dalla soluzione particolare.

### Teorema di Rouché-Capelli
Questo è il teorema più importante per determinare se un sistema ammette soluzioni e, in caso affermativo, quante.
Per enunciarlo, abbiamo bisogno di due matrici:
1. La *matrice dei coefficienti* ($A$), come definita prima.
2. La *matrice completa* (o *orlata*) $[A|\mathbf{b}]$, ottenuta affiancando alla matrice $A$ la colonna dei termini noti $b$$$[A|\mathbf{b}] = \begin{pmatrix}
a\_{11} & \dots & a\_{1n} & | & b\_1 \\
\vdots & \ddots & \vdots & | & \vdots \\
a\_{m1} & \dots & a\_{mn} & | & b\_m \end{pmatrix}$$Il teorema afferma che:
3. **Esistenza delle soluzioni**: Un sistema lineare $A\mathbf{x}=\mathbf{b}$ ammette soluzioni *se e solo se* il rango della matrice dei coefficienti è uguale al rango della matrice completa. $$rg(A)=rg([A|\mathbf{b}])$$ 
   Se i ranghi sono diversi, il sistema è detto *impossibile*.
4. **Numero delle soluzioni**: Se il sistema ammette soluzioni (cioè $rg(A)=rg([A|\mathbf{b}])=r$), allora:
    - Se il rango $r$ è uguale al numero di incognite $n$ ($r=n$), il sistema ha **una e una sola soluzione**. (Sistema *determinato*)
    - Se il rango $r$ è minore del numero di incognite $n$ ($r<n$), il sistema ha **infinite soluzioni**. (Sistema *indeterminato*) 
      Le infinite soluzioni dipendono da $n−r$ parametri liberi. 
      Si dice che il sistema ha $\infty^{n-r}$ soluzioni.

## Sistemi Lineari - Pratica (Gauss)
### Algoritmo di Eliminazione di Gauss
L'algoritmo di Gauss (o metodo di eliminazione gaussiana) è una procedura sistematica per risolvere i sistemi lineari. L'idea è quella di trasformare, tramite operazioni elementari sulle righe, la matrice completa del sistema in una **matrice a scala** (o a gradini), dalla quale le soluzioni si possono ricavare facilmente.
Passaggi dell'algoritmo:

1. Scrivere la matrice completa $[A|\mathbf{b}]$ del sistema.
2. Trasformare la matrice in forma a scala usando le seguenti **mosse di Gauss** (operazioni elementari sulle righe), che non alterano le soluzioni del sistema:
    - *Scambiare* due righe tra loro.
    - *Moltiplicare* una riga per un numero diverso da zero.
    - *Sommare* a una riga un multiplo di un'altra riga.
    L'obiettivo è creare degli zeri sotto il primo elemento non nullo di ogni riga (chiamato **pivot**). Si procede colonna per colonna, da sinistra verso destra.
    - *Fase 1* (Prima colonna): 
      Usa la prima riga per annullare i primi elementi di tutte le righe sottostanti. Se il primo elemento della prima riga è zero, scambia la riga con una sottostante che abbia un primo elemento non nullo.
    - *Fase 2* (Seconda colonna): 
      Ignora la prima riga e la prima colonna. Ripeti il procedimento sulla sottomatrice rimanente, usando la seconda riga per annullare gli elementi della seconda colonna sotto di essa.
    - *Continuare* così finché la matrice non è in forma a scala.
3. **Analizzare e risolvere il sistema a scala:**
- Una volta ottenuta la matrice a scala, si riscrive il sistema di equazioni associato.
- Si applica il *Teorema di Rouché-Capelli* per verificare l'esistenza e il numero di soluzioni. 
  Il **rango** è semplicemente il numero di righe non nulle nella matrice a scala.
- Se il sistema è compatibile, si risolve partendo dall'ultima equazione e risalendo verso la prima (procedimento di **sostituzione all'indietro**). 
  Le incognite che non corrispondono a un pivot possono essere trattate come parametri liberi.

**Esempio pratico:** Risolviamo il sistema:
$$\begin{cases} x + 2y + z = 2 \\ 3x + 8y + z = 12 \\ 4y + z = 2 \end{cases} $$
1. **Matrice completa:**
$$\begin{pmatrix} 1 & 2 & 1 & | & 2 \\ 3 & 8 & 1 & | & 12 \\ 0 & 4 & 1 & | & 2 \end{pmatrix} $$
2. **Eliminazione di Gauss:**
   Vogliamo uno zero al posto del 3 nella seconda riga. Sostituiamo la seconda riga ($R_2$) con $R_2−3R_1$:   $$\begin{pmatrix} 1 & 2 & 1 & | & 2 \\ 0 & 2 & -2 & | & 6 \\ 0 & 4 & 1 & | & 2 \end{pmatrix}$$Vogliamo uno zero al posto del 4 nella terza riga. Sostituiamo la terza riga ($R_3$) con $R_3−2R_2$:$$\begin{pmatrix} 1 & 2 & 1 & | & 2 \\ 0 & 2 & -2 & | & 6 \\ 0 & 0 & 5 & | & -10 \end{pmatrix}$$La matrice è ora a scala.
3. **Risoluzione:**
   Il rango della matrice incompleta e completa è 3 ($r=3$). Il numero di incognite è 3 ($n=3$). Poiché $r=n$, il sistema ha **una sola soluzione**.
   Riscriviamo il sistema:$$\begin{cases} x + 2y + z = 2 \\ 2y - 2z = 6 \\ 5z = -10 \end{cases}$$ Risolviamo con sostituzione all'indietro:
    - Dalla terza equazione: $5z=-10\implies\mathbf{z}=−2$  
    - Sostituiamo z nella seconda: $2y-2(-2)=6\implies2y+4=6\implies2y=2\implies\mathbf{y}=1$  
    - Sostituiamo y e z nella prima: $x+2(1)+(-2)=2\implies x+2-2=2\implies\mathbf{x}=2$
    La soluzione è $(2,1,−2)$.

## Esercizi
#### 1. Sistema $2\times2$ Determinato
$$\begin{cases} 2x - 3y = 7 \\ x + 4y = -2 \end{cases} $$**Passaggi:** 
1. Matrice completa: $$\begin{pmatrix} 2 & -3 & | & 7 \\ 1 & 4 & | & -2 \end{pmatrix}$$
2. Scambiamo $R_1$ con $R_2$ per avere un pivot uguale a 1: $$\begin{pmatrix} 1 & 4 & | & -2 \\ 2 & -3 & | & 7 \end{pmatrix}$$
3.  Applichiamo $R\_2 \to R\_2 - 2R\_1$: $$\begin{pmatrix} 1 & 4 & | & -2 \\ 0 & -11 & | & 11 \end{pmatrix}$$
4. **Analisi:** $rg(A) = rg(A|b) = 2$. 
   Numero incognite $n=2$. 
   Poiché $r=n$, la soluzione è unica. 
5. **Soluzione:**
   Dall'ultima riga: $-11y = 11 \implies y = -1$ 
   Sostituendo nella prima: $x + 4(-1) = -2 \implies x - 4 = -2 \implies x = 2$ 
   **Soluzione:** $(2, -1)$ 
#### 2. Sistema $3\times3$ Determinato 
$$\begin{cases} x + y - z = 0 \\ 2x - y + 3z = 9 \\ -x + 2y + 2z = 3 \end{cases} $$**Passaggi:** 
1. Matrice completa: $\begin{pmatrix} 1 & 1 & -1 & | & 0 \\ 2 & -1 & 3 & | & 9 \\ -1 & 2 & 2 & | & 3 \end{pmatrix}$ 
2. Applichiamo $R_2 \to R_2 - 2R_1$ e $R_3 \to R_3 + R_1$: $\begin{pmatrix} 1 & 1 & -1 & | & 0 \\ 0 & -3 & 5 & | & 9 \\ 0 & 3 & 1 & | & 3 \end{pmatrix}$ 
3. Applichiamo $R_3 \to R_3 + R_2$: $\begin{pmatrix} 1 & 1 & -1 & | & 0 \\ 0 & -3 & 5 & | & 9 \\ 0 & 0 & 6 & | & 12 \end{pmatrix}$ 
4. **Analisi:** $rg(A) = rg(A|b) = 3$. 
   Numero incognite $n=3$.
   Soluzione unica. 
5. **Soluzione:** 
   $6z = 12 \implies z = 2$
   $-3y + 5(2) = 9 \implies -3y = -1 \implies y = 1/3$
   $x + (1/3) - 2 = 0 \implies x = 5/3$ 
6. **Soluzione:** $(5/3, 1/3, 2)$
#### 3. Sistema $3\times3$ Indeterminato
$$\begin{cases} x + 2y - z = 4 \\ 2x + y + 3z = 5 \\ x - y + 4z = 1 \end{cases} $$**Passaggi:**

1. Matrice completa: $$\begin{pmatrix} 1 & 2 & -1 & | & 4 \\ 2 & 1 & 3 & | & 5 \\ 1 & -1 & 4 & | & 1 \end{pmatrix}$$
2. Applichiamo $R_2\to R_2−2R_1$ e $R_3\to R_3-R_1$: $$\begin{pmatrix} 1 & 2 & -1 & | & 4 \\ 0 & -3 & 5 & | & -3 \\ 0 & -3 & 5 & | & -3 \end{pmatrix}$$
3. Applichiamo $R_3\to R_3-R_2$: $$\begin{pmatrix} 1 & 2 & -1 & | & 4 \\ 0 & -3 & 5 & | & -3 \\ 0 & 0 & 0 & | & 0 \end{pmatrix}$$
4. **Analisi:** $rg(A)=rg(A∣b)=2$. 
   Numero incognite $n=3$. 
   Poiché $r<n$, il sistema ha $\infty^{3-2}=\infty^{1}$ soluzioni.
5. **Soluzione:** 
   Poniamo $z=t$ (parametro libero).
   $−3y+5t=−3implies3y=5t+3impliesy=frac53t+1$
   $x+2\left( \frac{5}{3}t+1 \right)-t=4\implies x+ \frac{10}{3}t+2−t=4\implies x=2-\frac{7}{3}t$ 
- **Soluzione:** ($2-\frac{7}{3}t,1+\frac{5}{3}t,t$) per ogni $t\in\mathbb{R}$.

#### 4. Sistema $3\times3$ Impossibile
$$\begin{cases} x - y + 2z = 1 \\ x + y + z = 2 \\ 2x + 4z = 5 \end{cases} $$**Passaggi:**
1. Matrice completa: $$\begin{pmatrix} 1 & -1 & 2 & | & 1 \\ 1 & 1 & 1 & | & 2 \\ 2 & 0 & 4 & | & 5 \end{pmatrix}$$ 
2. Applichiamo $R_2\to R_2−R_1$ e $R_3toR_3−2R_1$: $$\begin{pmatrix} 1 & -1 & 2 & | & 1 \\ 0 & 2 & -1 & | & 1 \\ 0 & 2 & 0 & | & 3 \end{pmatrix}$$  
3. Applichiamo $R_3\to R_3−R_2$: $$\begin{pmatrix} 1 & -1 & 2 & | & 1 \\ 0 & 2 & -1 & | & 1 \\ 0 & 0 & 1 & | & 2 \end{pmatrix}$$  
4. **Errore nel calcolo precedente, ricalcoliamo:** 
   $R_3\to R_3−2R_1$ dà $(2,0,4,5)−2(1,−1,2,1)=(0,2,0,3)$. Corretto.
   $R_3\to R_3−R_2$ dà $(0,2,0,3)−(0,2,−1,1)=(0,0,1,2)$. Corretto. 
   **Rivediamo il sistema originale:** 
   $2x+4z=5$ è la somma di $2\times(x−y+2z=1)$ e $2\times(y−z=...)$? 
   Sommando le prime due equazioni: $2x+3z=3$. 
   Confrontando con la terza $2x+4z=5$, sottraendo si ottiene $z=2$. 
   Se $z=2, 2x+3(2)=3\implies2x=−3\implies x=−3/2$. 
   Dalla seconda eq: $−3/2+y+2=2\implies y=3/2$. 
   Dalla prima: $−3/2−3/2+2(2)=−3+4=1$. 
   La soluzione esiste ed è unica. **Il sistema è determinato, non impossibile. Correggiamo l'etichetta e la soluzione.**
5. **Analisi:** $rg(A)=rg(A∣b)=3, n=3$. Soluzione unica.
6. **Soluzione:**
    - $z=2$  
    - $2y−z=1\implies 2y−2=1\implies2y=3\implies y=3/2$  
    - $x−y+2z=1\implies x−3/2+4=1\implies x=1−4+3/2=−3+3/2=−3/2$ 
    **Soluzione:** $\left( -\frac{3}{2}, \frac{3}{2},2 \right)$  

#### 5. Sistema $2\times3$

$$\begin{cases} x + y - 2z = 5 \\ 2x - y - z = 1 \end{cases}$$ **Passaggi:** 
1. Matrice completa: $$\begin{pmatrix} 1 & 1 & -2 & | & 5 \\ 2 & -1 & -1 & | & 1 \end{pmatrix}$$ 
2. Applichiamo $R\_2 \to R\_2 - 2R\_1$:$ $$\begin{pmatrix} 1 & 1 & -2 & | & 5 \\ 0 & -3 & 3 & | & -9 \end{pmatrix}$$ 
3. Possiamo semplificare $R\_2 \to R\_2 / (-3)$: $$\begin{pmatrix} 1 & 1 & -2 & | & 5 \\ 0 & 1 & -1 & | & 3 \end{pmatrix}$$ 
4. **Analisi:** $rg(A) = rg(A|b) = 2$. Numero incognite $n=3$. Poiché $r < n$, il sistema ha $\infty^{3-2} = \infty^1$ soluzioni. 
5. **Soluzione:** Poniamo $z=t$. - $y - t = 3 \\implies y = t + 3$ - $x + (t+3) - 2t = 5 \\implies x - t + 3 = 5 \\implies x = t + 2$ 
6. **Soluzione:** $(t+2, t+3, t)$ per ogni $t \\in \\mathbb{R}$. 
#### 6\. Sistema $3\times2$ 
$$\begin{cases} x + y = 3 \\ 2x - y = 0 \\ x + 3y = 5 \end{cases} $$**Passaggi:** 
1. Matrice completa: $$\begin{pmatrix} 1 & 1 & | & 3 \\ 2 & -1 & | & 0 \\ 1 & 3 & | & 5 \end{pmatrix}$$ 
2. Applichiamo $R\_2 \\to R\_2 - 2R\_1$ e $R\_3 \\to R\_3 - R\_1$: $$\begin{pmatrix} 1 & 1 & | & 3 \\ 0 & -3 & | & -6 \\ 0 & 2 & | & 2 \end{pmatrix}$$ 
3. Semplifichiamo $R\_2 \\to R\_2 / (-3)$ e $R\_3 \\to R\_3 / 2$:$$\begin{pmatrix} 1 & 1 & | & 3 \\ 0 & 1 & | & 2 \\ 0 & 1 & | & 1 \end{pmatrix}$$
4. Applichiamo $R\_3 \\to R\_3 - R\_2$: $$\begin{pmatrix} 1 & 1 & | & 3 \\ 0 & 1 & | & 2 \\ 0 & 0 & | & -1 \end{pmatrix}$$
5. **Analisi:** L'ultima riga corrisponde a $0 = -1$, che è un'assurdità. $rg(A) = 2$ mentre $rg(A|b) = 3$. Il sistema è **impossibile**. 
6. **Soluzione:** Nessuna.
#### 7. Sistema Omogeneo
$$\begin{cases} x + 3y - 2z = 0 \\ 2x - y + 4z = 0 \\ x - 11y + 14z = 0 \end{cases}$$**Passaggi:**
1. Matrice dei coefficienti: $$\begin{pmatrix} 1 & 3 & -2 \\ 2 & -1 & 4 \\ 1 & -11 & 14 \end{pmatrix}$$  
2. Applichiamo $R_2\to R_2−2R_1$ e $R_3\to R_3−R_1$: $$\begin{pmatrix} 1 & 3 & -2 \\ 0 & -7 & 8 \\ 0 & -14 & 16 \end{pmatrix}$$  
3. Applichiamo$R_3\to R_3−2R_2$: $$\begin{pmatrix} 1 & 3 & -2 \\ 0 & -7 & 8 \\ 0 & 0 & 0 \end{pmatrix}$$
4. **Analisi:** $rg(A)=2$. 
   Numero incognite $n=3$. 
   Poiché $r<n$, il sistema omogeneo ha $\infty^{3−2}=\infty^1$ soluzioni (oltre a quella banale).
5. **Soluzione:** Poniamo $z=t$.
- $−7y+8t=0\implies7y=8t\implies y=\frac{8}{7}t$  
- $x+3\left( \frac{8}{7}t \right)−2t=0\implies x+ \frac{24}{7}t− \frac{14}{7}t=0\implies x=−\frac{10}{7}t$
**Soluzione:** ($-\frac{10}{7}t, \frac{8}{7}t,t$) per ogni $t\in\mathbb{R}$.

#### 8. Sistema $4\times4$
$$\begin{cases} x + y + w = 4 \ y + z = 3 \ x - z - w = -1 \ y + w = 3 \end{cases} $$**Passaggi:**
1. Matrice completa (ordine incognite $x,y,z,w$): $$\begin{pmatrix} 1 & 1 & 0 & 1 & | & 4 \\ 0 & 1 & 1 & 0 & | & 3 \\ 1 & 0 & -1 & -1 & | & -1 \\ 0 & 1 & 0 & 1 & | & 3 \end{pmatrix}$$  
2. Applichiamo $R_3\to R_3−R_1$: $$\begin{pmatrix} 1 & 1 & 0 & 1 & | & 4 \\ 0 & 1 & 1 & 0 & | & 3 \\ 0 & -1 & -1 & -2 & | & -5 \\ 0 & 1 & 0 & 1 & | & 3 \end{pmatrix}$$  
3. Applichiamo $R_3\to R_3+R_2$ e $R_4\to R_4−R_2$: $$\begin{pmatrix} 1 & 1 & 0 & 1 & | & 4 \\ 0 & 1 & 1 & 0 & | & 3 \\ 0 & 0 & 0 & -2 & | & -2 \\ 0 & 0 & -1 & 1 & | & 0 \end{pmatrix}$$  
4. Scambiamo $R_3$ e $R_4$: $$\begin{pmatrix} 1 & 1 & 0 & 1 & | & 4 \\ 0 & 1 & 1 & 0 & | & 3 \\ 0 & 0 & -1 & 1 & | & 0 \\ 0 & 0 & 0 & -2 & | & -2 \end{pmatrix}$$  
5. **Analisi:** $rg(A)=rg(A∣b)=4$. 
   Numero incognite $n=4$. 
   Soluzione unica.
6. **Soluzione:**
    - $−2w=−2\implies w=1$  
    - $−z+w=0\implies−z+1=0\implies z=1$  
    - $y+z=3\implies y+1=3\implies y=2$  
    - $x+y+w=4\implies x+2+1=4\implies x=1$ 
    **Soluzione:** $(1,2,1,1)$

#### 9. Sistema con parametro (k)
Discutere le soluzioni al variare di $k\in\mathbb{R}$:$$\begin{cases} x + y + kz = 1 \\ x + ky + z = 1 \\ kx + y + z = 1 \end{cases} $$**Passaggi:** 
1. Matrice completa: $$\begin{pmatrix}
1 & 1 & k & | & 1 \\
1 & k & 1 & | & 1 \\
k & 1 & 1 & | & 1
\end{pmatrix}$$
2. Eliminazione di Gauss (primo passo): 
   Applichiamo $R_2toR_2−R_1$ e $R_3toR_3−kR_1$:$$\begin{pmatrix} 1 & 1 & k & | & 1 \\ 0 & k-1 & 1-k & | & 0 \\ 0 & 1-k & 1-k^2 & | & 1-k \end{pmatrix}$$ 
3. Eliminazione di Gauss (secondo passo): 
   Applichiamo $R_3toR_3+R_2$:$$\begin{pmatrix} 1 & 1 & k & | & 1 \\ 0 & k-1 & 1-k & | & 0 \\ 0 & 0 & (1-k^2)+(1-k) & | & 1-k \end{pmatrix}$$ L'elemento in posizione (3,3) si semplifica in: $1−k^{2}+1−k=−k^{2}−k+2=−(k+2)(k−1)$.
4. Discussione:
    - **Caso 1**: $k\neq1$ e $k\neq−2$. 
      I pivot sulla diagonale sono tutti non nulli. Il rango della matrice dei coefficienti e della matrice completa è 3, uguale al numero di incognite. 
      Il sistema è **determinato** (ha una sola soluzione).
    - **Caso 2**: k=1. La matrice diventa:$$\begin{pmatrix} 1 & 1 & 1 & | & 1 \\ 0 & 0 & 0 & | & 0 \\ 0 & 0 & 0 & | & 0 \end{pmatrix}$$
      Il rango di entrambe le matrici è 1, minore del numero di incognite (3). 
      Il sistema è **indeterminato** con $\infty^{2}$ soluzioni, descritte dall'equazione $x+y+z=1$.
    - **Caso 3**: $k=−2$. La matrice diventa:$$\begin{pmatrix} 1 & 1 & -2 & | & 1 \\ 0 & -3 & 3 & | & 0 \\ 0 & 0 & 0 & | & 3 \end{pmatrix}$$
    - L'ultima riga corrisponde all'equazione impossibile $0=3$. 
      Il rango della matrice dei coefficienti è 2, mentre quello della matrice completa è 3. 
      Il sistema è **impossibile**.
**Soluzione Riassuntiva:**
- Se $k\neq1$ e $k\neq−2$: **Soluzione unica**.
- Se $k=1$: **Infinite soluzioni** date da $x=1−y−z$.
- Se $k=−2$: **Nessuna soluzione**.
#### 10. Sistema con parametro (a)

Discutere le soluzioni al variare di $a\in\mathbb{R}$:$$\begin{cases} x + y - z = 1 \\ 2x + 3y + az = 3 \\ x + ay + 3z = 2 \end{cases} $$**Passaggi:** 
1. Matrice completa: $$\begin{pmatrix}
1 & 1 & -1 & | & 1 \\
2 & 3 & a & | & 3 \\
1 & a & 3 & | & 2
\end{pmatrix}$$
2. Eliminazione di Gauss (primo passo): Applichiamo $R_2\to R_2−2R_1$ e R$_3\to R_3−R_1$:$$\begin{pmatrix} 1 & 1 & -1 & | & 1 \\ 0 & 1 & a+2 & | & 1 \\ 0 & a-1 & 4 & | & 1 \end{pmatrix}$$
3. Eliminazione di Gauss (secondo passo): Applichiamo $R_3\to R_3−(a−1)R_2$:$$\begin{pmatrix} 1 & 1 & -1 & | & 1 \\ 0 & 1 & a+2 & | & 1 \\ 0 & 0 & 4-(a-1)(a+2) & | & 1-(a-1) \end{pmatrix} $$
   L'elemento in posizione $(3,3)$ è $4−(a^{2}+a−2)=−a^{2}−a+6=−(a+3)(a−2)$. 
   Il termine noto nella terza riga è $1−(a−1)=2−a$.
4. **Discussione:**
    - **Caso 1**: $a\neq2$ e $a\neq−3$. 
      Il pivot in posizione (3,3) è non nullo. 
      Il rango di entrambe le matrici è 3. 
      Il sistema è **determinato**
    - **Caso 2**: $a=2$. 
      L'ultima riga della matrice diventa ($0,0,0,∣,0$). 
      Il rango di entrambe le matrici è 2, minore del numero di incognite (3). 
      Il sistema è **indeterminato** con $\infty^1$ soluzioni.
    - **Caso 3**: $a=−3$. 
      L'ultima riga della matrice diventa ($0,0,0,∣,5$). 
      Il rango della matrice dei coefficienti è 2, mentre quello della matrice completa è 3. 
      Il sistema è **impossibile**.
**Soluzione Riassuntiva:**
- Se $a\neq2$ e $a\neq−3$: **Soluzione unica**.
- Se $a=2$: **Infinite soluzioni**.
- Se $a=−3$: **Nessuna soluzione**.


# 6 - Determinanti e Invertibilità
Il **determinante** è un numero scalare associato a ogni matrice quadrata che ne descrive importanti proprietà algebriche e geometriche. Si indica con $det(A)$ o $|A|$.
## Proprietà Fondamentali del Determinante
1. **Matrice Identità**: $det(I) = 1$.
2. **Matrici Triangolari**: Il determinante è il *prodotto degli elementi sulla diagonale principale*.
3. **Scambio di Righe/Colonne**: Se si scambiano due righe (o colonne), il determinante *cambia di segno*. 
   Di conseguenza, se una matrice ha due righe/colonne identiche, il suo determinante è **zero**.
4. **Moltiplicazione per Scalare**: Se una _singola_ riga (o colonna) è moltiplicata per $k$, il determinante è moltiplicato per $k$. 
   Per una matrice $A$ di ordine $n$, $det(kA) = k^n * det(A)$.
5. **Righe/Colonne Nulle**: Se una matrice ha una riga o colonna di zeri, il suo determinante è **zero**.
6. **Dipendenza Lineare**: Se una riga (o colonna) è combinazione lineare di altre, il determinante è **zero**.
7. **Operazioni di Gauss**: Aggiungere a una riga un multiplo di un'altra **non altera il determinante**. Questa è la proprietà più utile per semplificare i calcoli.
## Calcolo: Sviluppo di Laplace
Il Teorema di Laplace fornisce un metodo ricorsivo per il calcolo. Si sceglie una riga $i$ o una colonna $j$ e si calcola:
- **Sviluppo lungo la riga i-esima**:$$det(A)=\sum_{j=1}^n​(−1)^{i+j}a_{ij}​M_{ij​}$$
- **Sviluppo lungo la colonna j-esima**:$$det(A)=\sum_{i=1}^n​(−1)^{i+j}a_{ij​}M_{ij}​$$
Dove:
- $a_{ij}$ è l'elemento in posizione $(i, j)$.
- $M_{ij}$ è il **minore complementare**, cioè il determinante della sottomatrice ottenuta eliminando la riga $i$ e la colonna $j$.
- Il termine $(-1)^{(i+j)}$ definisce il segno del cofattore.
**Consiglio**: Scegliere sempre la riga o la colonna con più zeri.
## Teorema di Binet
**Teorema di Binet**: Date due matrici quadrate $A$ e $B$ dello stesso ordine:$$det(A⋅B)=det(A)⋅det(B)$$
## Matrice inversa
**Invertibilità**: Una matrice quadrata $A$ è **invertibile** se e solo se **$det(A) ≠ 0$**. 
In tal caso, esiste un'unica matrice $A^{-1}$ tale che $A\cdot A^{-1}=A^{-1}\cdot A=I$.
La formula per l'inversa è:$$A^{-1}=\frac{1}{det(A)}\cdot agg(A)$$
dove $agg(A)$ è la **matrice aggiunta** (la trasposta della matrice dei cofattori).
# 7 - Autovalori e Autovettori
Questi concetti sono fondamentali per analizzare le direzioni "privilegiate" di una trasformazione lineare.
## Definizioni
Sia $A$ una matrice quadrata $n\times n$.
- **Autovettore**: Un vettore **non nullo** $v$ tale che la sua direzione non viene cambiata quando viene trasformato da $A$. Matematicamente:$$A\vec{v}=\lambda\vec{v}$$
- **Autovalore**: Lo scalare $\lambda$ che misura di quanto l'autovettore $v$ viene "stirato" o "compresso" dalla trasformazione.
- **Autospazio $V_\lambda$**: L'insieme di tutti gli autovettori associati a un autovalore $\lambda$, unito al vettore nullo. 
  È un sottospazio vettoriale.
## Calcolo dello Spettro
Per trovare gli autovalori e gli autovettori, si parte dall'equazione $A \vec{v} = \lambda \vec{v}$, che può essere riscritta come:$$(A−\lambda I)\vec{v}=\vec{0}$$
Poiché cerchiamo autovettori $v$ non nulli, il sistema omogeneo deve ammettere soluzioni non banali. 
Ciò accade se e solo se la matrice dei coefficienti $(A - \lambda I)$ è singolare, ovvero:$$det(A−\lambda I)=0$$
Questa è l'**equazione caratteristica**.
- **Polinomio Caratteristico** $p(\lambda)$: 
  È il polinomio nella variabile $\lambda$ ottenuto calcolando $det(A−\lambda I)$. 
  La sua importanza è cruciale non solo perché le sue radici sono esattamente gli autovalori della matrice $A$, ma anche perché il polinomio stesso è un **invariante per similitudine**. 
  Questo significa che se due matrici A e B sono simili (cioè $B=P^{-1}AP$ per una qualche matrice invertibile $P$), allora avranno lo stesso polinomio caratteristico. 
  Di conseguenza, matrici simili condividono gli stessi autovalori, la stessa traccia e lo stesso determinante. 
  Per una matrice $A$ di ordine $n$, il polinomio caratteristico $p(\lambda)$ ha sempre grado $n$. 
  I suoi coefficienti sono legati a importanti proprietà intrinseche della matrice che non cambiano al variare della base scelta per rappresentare la trasformazione lineare. 
  I due coefficienti più noti sono:
	- Il **termine noto** (coefficiente di $\lambda^{0}$), che è uguale a $p(0)=det(A−0⋅I)=det(A)$.
	- Il coefficiente di $\lambda^{n-1}$, che è uguale a $(-1)^{n-1}tr(A)$, dove $tr(A)$ è la **traccia** della matrice (la somma degli elementi sulla diagonale principale). 
	  Questa invarianza dei coefficienti è una proprietà potente, poiché ci permette di calcolare traccia e determinante, che sono proprietà fondamentali della trasformazione, indipendentemente dalla base scelta.
- **Autovalori**: Sono le radici del polinomio caratteristico, ovvero le soluzioni dell'equazione caratteristica $p(\lambda)=0$. 
  La molteplicità di un autovalore come radice del polinomio è detta **molteplicità algebrica**.
- **Spettro $\sigma(A)$**: È l'insieme di tutti gli autovalori di $A$.
## Procedura Pratica
1. **Costruire la matrice $(A - \lambda I)$**: Sottrai $\lambda$ da ogni elemento della diagonale principale di $A$.
2. **Calcolare $p(\lambda) = det(A - \lambda I)$**.
3. **Trovare gli autovalori**: Risolvi l'equazione $p(\lambda) = 0$ per trovare le radici $\lambda_i$.
4. **Trovare gli autospazi**: Per ogni autovalore $\lambda_i$, risolvi il sistema lineare omogeneo $(A - \lambda_i I)\vec{v} = \vec{0}$. Le soluzioni non nulle sono gli autovettori associati a $\lambda_i$.

**Esempio**: Sia $A = \begin{pmatrix} 2 & 1 \\ 1 & 2 \end{pmatrix}$.
1. **Polinomio caratteristico**: $det(A - \lambda I) = \begin{vmatrix} 2-\lambda& 1 \\ 1 & 2-\lambda\end{vmatrix} = (2-\lambda)^2 - 1 = \lambda^2 - 4\lambda+ 3$
2. **Autovalori**: $\lambda^2 - 4\lambda + 3 = 0 \implies (\lambda- 1)(\lambda- 3) = 0$ 
   Lo spettro è $σ(A) = {1, 3}$.
3. **Autospazi**:
    - Per $\lambda₁ = 1$: 
      Risolvi $(A - I)\vec{v} = \vec{0}$, ovvero $\begin{pmatrix} 1 & 1 \\ 1 & 1 \end{pmatrix} \begin{pmatrix} x \\ y \end{pmatrix} = \begin{pmatrix} 0 \\ 0 \end{pmatrix}$. 
      L'equazione è $x + y = 0$. 
      L'autospazio $V₁$ è generato da $(1, -1)$.
    - Per $\lambda₂ = 3$: 
      Risolvi $(A - 3I)\vec{v} = \vec{0}$, ovvero $\begin{pmatrix} -1 & 1 \\ 1 & -1 \end{pmatrix} \begin{pmatrix} x \\ y \end{pmatrix} = \begin{pmatrix} 0 \\ 0 \end{pmatrix}$. 
      L'equazione è $-x + y = 0$. 
      L'autospazio $V₃$ è generato da $(1, 1)$.