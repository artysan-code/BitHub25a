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
# 4.1 - Rango e Ripasso Strategico
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
# 5 - Sistemi Lineari: Teoria
