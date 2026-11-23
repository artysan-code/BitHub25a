---
tags:
  - calcolo-numerico
  - metodi-iterativi
  - sistemi-lineari
slide: []
---
# Metodi iterativi per sistemi lineari
## Metodi iterativi stazionari: consistenza e convergenza
Lezione 14 (19/11/2026): inizio dell'ultimo argomento del corso, i metodi iterativi stazionari per sistemi lineari, con le definizioni di consistenza e convergenza, la condizione necessaria e sufficiente di convergenza $\rho(P)<1$, una condizione sufficiente (norma indotta) e due condizioni necessarie (traccia e determinante), e due esempi.

Finita l'analisi delle matrici ([[03 - Analisi delle matrici]]), comincia l'**ultimo argomento** del corso: la risoluzione dei sistemi lineari con **metodi iterativi**. Gli strumenti della lezione precedente (raggio spettrale, norme matriciali indotte, il teorema su $P^k\to O$) vengono usati subito.
### Il problema
È dato un sistema lineare
$$Ax=b\tag{S}$$
dove $b\in\mathbb{C}^n$ (che può avere anche tutte le componenti reali, perché $\mathbb{C}^n\supset\mathbb{R}^n$) e $A\in\mathbb{C}^{n\times n}$ è **invertibile**. In tal caso il sistema (S) ha un'**unica soluzione**
$$x=A^{-1}b$$
che si ottiene moltiplicando entrambi i membri di (S) a sinistra per $A^{-1}$: $A^{-1}Ax=Ix=x$.

> [!info] Perché $A$ invertibile
> Per un sistema quadrato $n\times n$, il **teorema di Rouché–Capelli** (dal corso di geometria, che per i matematici è "algebra lineare") dice che se $A$ è invertibile la soluzione esiste ed è unica. Se $A$ non è invertibile ci sono solo due possibilità: il sistema non ha **nessuna** soluzione, oppure ne ha **infinite**. Un sistema lineare non può avere, ad esempio, esattamente due soluzioni: o una, o zero, o infinite.

Ci si propone di risolvere (S) con un **metodo iterativo**, cioè un metodo che, a partire da un vettore iniziale $x^{(0)}\in\mathbb{C}^n$ scelto dall'utente (l'*initial guess*, un input del metodo), costruisce una successione di vettori
$$x^{(0)},\ x^{(1)},\ x^{(2)},\ \dots$$
applicando una certa regola, quella del metodo: l'utente fornisce solo $x^{(0)}$, tutti gli altri termini li calcola il metodo. Da questa successione si vogliono due cose:
- **deve essere facile da costruire**: i termini $x^{(1)},x^{(2)},\dots$ devono essere facili da calcolare. Se fosse complicato, tanto varrebbe risolvere direttamente il sistema con il metodo di Gauss;
- **deve convergere (componente per componente) alla soluzione $x=A^{-1}b$, qualunque sia $x^{(0)}$**.

> [!info] Convergenza componente per componente e "qualunque sia $x^{(0)}$"
> - Quando non si specifica, "convergere" vuol dire convergere **componente per componente**. Come visto nelle lezioni sulle norme, la convergenza componente per componente è la convergenza in norma $\infty$, e siccome tutte le norme vettoriali sono equivalenti equivale alla convergenza in una **qualsiasi** norma: è un concetto "assoluto".
> - "Qualunque sia $x^{(0)}$" è un'aggiunta importante. L'utente in generale non ha informazioni sulla soluzione e sceglie $x^{(0)}$ a caso; vuole la garanzia che la successione converga a $x$ comunque scelga $x^{(0)}$. Se poi ha qualche informazione e sceglie un $x^{(0)}$ già vicino a $x$, la successione ci metterà poco ad arrivarci, ma ci si vuole "coprire le spalle".
### Metodi iterativi stazionari
Si vedranno metodi iterativi per la soluzione di (S) di questa forma:
$$\begin{cases}x^{(0)}\ \text{dato}\\x^{(k+1)}=Px^{(k)}+q,\qquad k=0,1,2,\dots\end{cases}\tag{M}$$
dove $P\in\mathbb{C}^{n\times n}$ è una matrice fissata detta **matrice d'iterazione** e $q\in\mathbb{C}^n$ è un vettore fissato (che non ha un nome particolare). (S) sta per *sistema*, (M) per *metodo*.

Un metodo della forma (M) si chiama **metodo iterativo stazionario**: "stazionario" perché a ogni iterazione fa sempre la stessa operazione (prende il vettore precedente, lo moltiplica per $P$ e somma $q$). I metodi **non stazionari**, in cui ad esempio la matrice $P_k$ cambia a ogni iterazione, sono più complicati e non si vedono nel corso.
### Consistenza
#### Osservazione
Supponiamo che una successione $\{x^{(k)}\}_{k=0,1,2,\dots}$ generata dal metodo (M) converga a un vettore (qualsiasi)
$$x^{(\infty)}=\lim_{k\to\infty}x^{(k)}$$
(limite componente per componente). Allora, siccome anche $x^{(k+1)}\to x^{(\infty)}$ e $x^{(k+1)}$ è dato dalla regola del metodo,
$$x^{(\infty)}=\lim_{k\to\infty}x^{(k+1)}=\lim_{k\to\infty}\left(Px^{(k)}+q\right)=Px^{(\infty)}+q$$
L'ultima uguaglianza ($Px^{(k)}+q\to Px^{(\infty)}+q$) si verifica componente per componente. Per la prima componente, con il prodotto righe per colonne (prima riga di $P$ per $x^{(k)}$):
$$\left(Px^{(k)}+q\right)_1=\left(Px^{(k)}\right)_1+q_1=p_{11}x_1^{(k)}+p_{12}x_2^{(k)}+\dots+p_{1n}x_n^{(k)}+q_1$$
$$\xrightarrow{k\to\infty}\ p_{11}x_1^{(\infty)}+p_{12}x_2^{(\infty)}+\dots+p_{1n}x_n^{(\infty)}+q_1=\left(Px^{(\infty)}+q\right)_1$$
perché sono somme di numeri e ogni $x_i^{(k)}\to x_i^{(\infty)}$. Analogamente per le altre componenti (cambia solo l'indice di riga).

**Conclusione.** Se la soluzione $x$ di (S) **non** soddisfa l'equazione
$$x=Px+q$$
allora **non è possibile** che una successione generata dal metodo (M) converga ad $x$: se ci convergesse, $x$ dovrebbe soddisfare l'equazione appena trovata.

Quindi la condizione $x=Px+q$ è **imprescindibile**: senza di essa il metodo "si può prendere e buttare via", perché non c'entra niente con il sistema che si sta risolvendo. Le successioni che produce possono convergere a qualcos'altro, non convergere a niente, divergere: di certo non convergono alla soluzione di (S).
#### Definizione
> [!quote] Definizione (consistenza di un metodo iterativo)
> Il metodo (M) si dice **consistente** con il sistema (S) se la soluzione $x$ di (S) (unica, perché $A$ è invertibile) soddisfa l'equazione
> $$x=Px+q\qquad\text{(equazione di consistenza)}$$
### Convergenza
> [!quote] Definizione (convergenza di un metodo iterativo)
> Il metodo (M) per risolvere il sistema (S) si dice **convergente** se per ogni scelta di $x^{(0)}\in\mathbb{C}^n$ la successione prodotta dal metodo a partire da $x^{(0)}$ converge alla soluzione $x$ di (S).

È esattamente quello che si voleva all'inizio. Per l'osservazione precedente, un metodo convergente deve essere come minimo consistente; ma la consistenza non basta, serve una condizione in più, data dal teorema seguente.

> [!info] CNS, CS, CN
> **CNS** = condizione necessaria e sufficiente (un "se e solo se"); **CS** = condizione solo sufficiente; **CN** = condizione solo necessaria.
#### Teorema (CNS di convergenza)
> [!quote] Teorema (CNS di convergenza)
> Supponiamo che il metodo (M) sia consistente con il sistema (S). Allora il metodo (M) è convergente se e solo se
> $$\rho(P)<1$$

Il docente lo definisce un teorema **importantissimo, fondamentale** per i metodi iterativi. L'ipotesi di consistenza va sempre messa, "se no non andiamo da nessuna parte". Se $\rho(P)<1$ il metodo converge; se $\rho(P)\geq1$ il metodo non converge.
#### Dimostrazione
Si dimostra **solo** l'implicazione $(\Leftarrow)$: se $\rho(P)<1$ allora il metodo è convergente.

Supponiamo dunque che $\rho(P)<1$ (cioè, siccome $\rho(P)$ è il massimo dei moduli degli autovalori di $P$, tutti gli autovalori di $P$ hanno modulo $<1$) e fissiamo un qualsiasi vettore $x^{(0)}\in\mathbb{C}^n$. Dimostriamo che, indipendentemente dalla scelta di $x^{(0)}$, la successione $\{x^{(k)}\}_{k=0,1,2,\dots}$ prodotta dal metodo (M) converge alla soluzione $x$ di (S).

Per l'ipotesi di consistenza,
$$x=Px+q$$
Inoltre, $\forall k=0,1,2,\dots$ vale l'equazione del metodo, cioè
$$x^{(k+1)}=Px^{(k)}+q,\qquad\forall k=0,1,2,\dots$$
Sottraendo membro a membro si ottiene ($q$ si semplifica e si raccoglie $P$)
$$\underbrace{x^{(k+1)}-x}_{e^{(k+1)}}=\left(Px^{(k)}+q\right)-\left(Px+q\right)=P\underbrace{\left(x^{(k)}-x\right)}_{e^{(k)}},\qquad\forall k=0,1,2,\dots$$
dove $e^{(k)}=x^{(k)}-x$ è l'**errore** al passo $k$. Quindi
$$e^{(k+1)}=Pe^{(k)}\qquad\forall k=0,1,2,\dots\qquad\text{(equazione dell'errore)}$$
**Sviluppo ricorsivo.** Applicando ricorsivamente l'equazione dell'errore fino all'errore iniziale $e^{(0)}$:
$$e^{(k+1)}=P^1e^{(k)}=P^2e^{(k-1)}=P^3e^{(k-2)}=\dots=P^{k+1}e^{(0)}\qquad\forall k=0,1,2,\dots$$
Per trovare l'esponente finale si guarda l'**invariante** della ricorsione: la somma dell'esponente di $P$ e dell'indice dell'errore è sempre $k+1$ ($1+k$, $2+(k-1)$, $3+(k-2)$, ...), quindi quando l'indice dell'errore è $0$ l'esponente di $P$ è $k+1$. Questa ricorsione non velocizza il metodo: serve solo a capire la relazione tra $e^{(0)}$ ed $e^{(k+1)}$.

Scrivendo $k$ al posto di $k+1$ si include anche il caso $k=0$, perché $P^0=I$ e $e^{(0)}=P^0e^{(0)}$:
$$\boxed{e^{(k)}=P^ke^{(0)}\qquad\forall k=0,1,2,\dots}$$
Poiché $\rho(P)<1$, per il teorema ultimo della lezione scorsa si ha che $P^k\xrightarrow{k\to\infty}O$ (la matrice nulla). Allora
$$e^{(k)}=P^ke^{(0)}\xrightarrow{k\to\infty}O\,e^{(0)}=0\quad\Longrightarrow\quad x^{(k)}-x\to0\quad\Longrightarrow\quad x^{(k)}\to x$$
(tutte convergenze componente per componente). $\blacksquare$

Nella dimostrazione non importa quale sia $x^{(0)}$: cambiando $x^{(0)}$ cambia l'errore iniziale $e^{(0)}$, ma qualunque sia $e^{(0)}$ si ha $P^ke^{(0)}\to0$ perché $P^k\to O$. Quindi si ha convergenza come da definizione, a prescindere dal dato iniziale scelto dall'utente.

> [!info] L'implicazione $(\Rightarrow)$ (nostra aggiunta, non fatta a lezione)
> Se $\rho(P)\geq1$, esiste un autovalore $\lambda$ di $P$ con $|\lambda|\geq1$ e autovettore $v\neq0$. Scegliendo $x^{(0)}=x+v$ si ha $e^{(0)}=v$ e quindi $e^{(k)}=P^kv=\lambda^kv$, che non tende a $0$ perché $|\lambda^k|=|\lambda|^k\geq1$. Dunque per questo $x^{(0)}$ la successione non converge a $x$ e il metodo non è convergente.

> [!info] Il teorema usato
> Il "teorema ultimo della lezione scorsa" è [[03 - Analisi delle matrici#Teorema sulle potenze di una matrice]]: $P^k\to O$ se e solo se $\rho(P)<1$.
#### Corollario (CS di convergenza)
> [!quote] Corollario (CS di convergenza)
> Supponiamo che il metodo (M) sia consistente con il sistema (S). Se esiste una norma matriciale **indotta** $\|\cdot\|$ tale che $\|P\|<1$, allora il metodo è convergente.

È una conseguenza del teorema e una condizione **solo sufficiente**: se è soddisfatta si ha convergenza, ma si può avere convergenza anche se non lo è. In pratica si provano le norme indotte che si conoscono: $\|\cdot\|_1$, $\|\cdot\|_2$, $\|\cdot\|_\infty$.

**Dimostrazione.** Poiché $\rho(P)\leq\|P\|$ per ogni norma matriciale indotta (teorema visto la lezione scorsa), se $\|P\|<1$ allora
$$\rho(P)\leq\|P\|<1$$
e il metodo è convergente per il teorema precedente. $\blacksquare$

> [!warning] La norma deve essere indotta
> Il docente sottolinea **indotta**: ad esempio la norma $\|\cdot\|_\infty$ "con una stanghetta" (il massimo dei moduli degli elementi della matrice) non è una norma matriciale indotta (non è submoltiplicativa, mentre tutte le norme indotte lo sono), e per essa la disuguaglianza $\rho(P)\leq\|P\|$ non è garantita. Quella da usare è $\|\cdot\|_\infty$ con la doppia stanghetta, la norma indotta.
#### Corollario (CN di convergenza)
> [!quote] Corollario (CN di convergenza)
> Supponiamo che il metodo (M) sia consistente con il sistema (S) (con $A\in\mathbb{C}^{n\times n}$).
> - Se $|\operatorname{traccia}(P)|\geq n$, allora il metodo **non** è convergente.
> - Se $|\det(P)|\geq1$, allora il metodo **non** è convergente.
>
> Equivalentemente: le condizioni
> $$|\operatorname{traccia}(P)|<n\qquad\text{e}\qquad|\det(P)|<1$$
> sono **necessarie** per la convergenza del metodo (M).

Sono condizioni **solo necessarie**: se non valgono il metodo non converge e "i giochi sono fatti", ma se valgono non si può concludere niente. Ad esempio una $P$ con traccia $\frac12$ e determinante $\frac1{10}$ soddisfa entrambe, ma non per questo il metodo converge.

> [!info] Quando usarle
> Il docente le userebbe solo quando "si vedono": soprattutto la **traccia**, che si calcola a colpo d'occhio sommando gli elementi diagonali. Non conviene invece calcolare un determinante per poi scoprire magari che è $<1$ e non concludere niente.
#### Dimostrazione
**Primo punto.** Supponiamo che $|\operatorname{traccia}(P)|\geq n$. Dimostro che $\rho(P)\geq1$, per cui il metodo non converge per il teorema precedente. A tal fine dimostro che esiste almeno un autovalore di $P$ di modulo $\geq1$ (allora anche $\rho(P)$, che è il massimo dei moduli degli autovalori, è $\geq1$).

Infatti, siano $\lambda_1,\dots,\lambda_n$ gli autovalori di $P$. Se per assurdo tutti gli autovalori di $P$ fossero di modulo $<1$, allora, siccome la traccia è la somma degli autovalori e usando la disuguaglianza triangolare,
$$|\operatorname{traccia}(P)|=|\lambda_1+\lambda_2+\dots+\lambda_n|\leq|\lambda_1|+|\lambda_2|+\dots+|\lambda_n|<n$$
assurdo! Quindi $\exists\,\lambda_i$ di modulo $|\lambda_i|\geq1$, e dunque $\rho(P)\geq1$. $\blacksquare$

L'idea: gli autovalori sono $n$; se fossero tutti più piccoli di $1$ in modulo, la loro somma non potrebbe avere modulo $\geq n$.

**Secondo punto.** La dimostrazione è identica: si cambia solo l'ipotesi, $|\det(P)|\geq1$ al posto di $|\operatorname{traccia}(P)|\geq n$, e la riga dell'assurdo. Se per assurdo tutti gli autovalori di $P$ fossero di modulo $<1$, siccome il determinante è il prodotto degli autovalori,
$$|\det(P)|=|\lambda_1\lambda_2\cdots\lambda_n|=|\lambda_1|\,|\lambda_2|\cdots|\lambda_n|<1$$
(prodotto di numeri tutti $<1$), assurdo! Il resto è uguale. $\blacksquare$

> [!warning] Modulo del prodotto e modulo della somma
> Per la somma si usa la disuguaglianza triangolare ($\leq$); per il prodotto non c'è nessuna disuguaglianza: il modulo di un prodotto è **esattamente uguale** al prodotto dei moduli.

> [!info] Il caso $n=1$
> Uno studente osserva che per una matrice $1\times1$ la cosa è ovvia: il modulo della traccia è proprio il raggio spettrale. Il punto del corollario è che vale per ogni $n$: per una $50\times50$ con $|\operatorname{traccia}(P)|\geq50$ non è a priori ovvio che $\rho(P)\geq1$, ma lo è per l'argomento per assurdo.
### Esempi
Il docente annuncia tre esempi: i primi due si fanno in questa lezione, il terzo è rimandato alla prossima. I due esempi hanno lo stesso sistema e metodi quasi uguali, e mostrano come una piccola modifica renda convergente un metodo che non lo era.
#### Esempio 1: un metodo consistente ma non convergente
> [!example] Esempio
> Consideriamo il sistema lineare
> $$Ax=b,\qquad A=\begin{bmatrix}2&1\\1&2\end{bmatrix},\qquad b=\begin{bmatrix}1\\1\end{bmatrix}\qquad(\det(A)=3\neq0)$$
> e il metodo iterativo
> $$\begin{cases}x^{(0)}\in\mathbb{C}^2\ \text{dato}\\x^{(k+1)}=(I-A)x^{(k)}+b,\qquad k=0,1,2,\dots\end{cases}$$
> - (i) Stabilire se il metodo è consistente con il sistema dato.
> - (ii) Stabilire se il metodo è convergente.
> - (iii) Calcolare le prime 5 iterazioni del metodo partendo da $x^{(0)}=(0,0)^T$ e confrontarle con la soluzione esatta.

Siccome $\det(A)=4-1=3\neq0$, il sistema è invertibile e ha un'unica soluzione.

**(i)** Il metodo assegnato è della forma (M) con $P=I-A$ e $q=b$. La soluzione $x$ non la si conosce (altrimenti il problema sarebbe già risolto), ma si sa che soddisfa $Ax=b$. Strategia: si sostituisce la soluzione $x$ del sistema dato nell'equazione del metodo al posto di $x^{(k)}$ e $x^{(k+1)}$ e si controlla, con passaggi equivalenti, se si ottiene un'identità verificata. Si ottiene
$$x=(I-A)x+b\iff x=x-Ax+b\iff Ax=b\qquad\text{VERO!}$$
Ho ottenuto un'identità verificata, dunque il metodo è consistente con il sistema dato.

> [!warning] Come si verifica la consistenza
> L'uguaglianza $x=(I-A)x+b$ si scrive "materialmente", ma non si sa ancora se è vera: va trasformata con passaggi **equivalenti** ($\iff$) fino a qualcosa che si sa essere vero, cioè $Ax=b$. Se invece si arriva a qualcosa di falso, il metodo non è consistente.

**(ii)** La matrice d'iterazione del metodo è
$$P=I-A=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\ \Longrightarrow\ |\operatorname{traccia}(P)|=|-2|=2\geq2=n$$
e quindi il metodo **non è convergente** per il corollario precedente (CN di convergenza; vale anche il caso di uguaglianza, perché la condizione è $\geq n$). In linea di principio si dovrebbe calcolare il raggio spettrale (la CNS), ma qui la traccia basta.

**(iii)** Si calcola la soluzione esatta con il metodo di Gauss. Il sistema in forma espansa è
$$\begin{cases}2x_1+x_2=1\\x_1+2x_2=1\end{cases}\ \overset{R_2\to R_2-\frac12R_1}{\iff}\ \begin{cases}2x_1+x_2=1\\\frac32x_2=\frac12\end{cases}\iff\begin{cases}x_1=\frac13\\x_2=\frac13\end{cases}\iff x=\begin{bmatrix}1/3\\1/3\end{bmatrix}$$
(la prima equazione non si tocca; per sostituzione all'indietro $x_2=\frac13$ e $x_1=\frac{1-\frac13}{2}=\frac13$). L'equazione del metodo è
$$x^{(k+1)}=Px^{(k)}+b=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}x^{(k)}+\begin{bmatrix}1\\1\end{bmatrix}$$
e le prime 5 iterazioni partendo da $x^{(0)}=\begin{bmatrix}0\\0\end{bmatrix}$ sono
$$x^{(1)}=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\begin{bmatrix}0\\0\end{bmatrix}+\begin{bmatrix}1\\1\end{bmatrix}=\begin{bmatrix}1\\1\end{bmatrix}$$
$$x^{(2)}=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\begin{bmatrix}1\\1\end{bmatrix}+\begin{bmatrix}1\\1\end{bmatrix}=\begin{bmatrix}-1\\-1\end{bmatrix}$$
$$x^{(3)}=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\begin{bmatrix}-1\\-1\end{bmatrix}+\begin{bmatrix}1\\1\end{bmatrix}=\begin{bmatrix}3\\3\end{bmatrix}$$
$$x^{(4)}=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\begin{bmatrix}3\\3\end{bmatrix}+\begin{bmatrix}1\\1\end{bmatrix}=\begin{bmatrix}-5\\-5\end{bmatrix}$$
$$x^{(5)}=\begin{bmatrix}-1&-1\\-1&-1\end{bmatrix}\begin{bmatrix}-5\\-5\end{bmatrix}+\begin{bmatrix}1\\1\end{bmatrix}=\begin{bmatrix}11\\11\end{bmatrix}$$
Le iterazioni oscillano allontanandosi sempre di più da $\frac13$: come previsto, il metodo non converge.

> [!info] Verifica (nostra aggiunta)
> Gli autovalori di $P=I-A$ sono $0$ e $-2$, quindi $\rho(P)=2\geq1$, coerente con la CNS. Inoltre $P\begin{bmatrix}1\\1\end{bmatrix}=-2\begin{bmatrix}1\\1\end{bmatrix}$ e $e^{(0)}=-\frac13\begin{bmatrix}1\\1\end{bmatrix}$, quindi $e^{(k)}=P^ke^{(0)}=-\frac13(-2)^k\begin{bmatrix}1\\1\end{bmatrix}$, cioè ogni componente di $x^{(k)}$ vale $\frac13-\frac13(-2)^k$: per $k=1,\dots,5$ si ritrovano $1,-1,3,-5,11$.
#### Esempio 2: un metodo convergente
Stesso sistema e stesso metodo, con un $\frac12$ davanti ad $A$ e uno davanti a $b$: con questa piccola modifica il metodo diventa convergente.

> [!example] Esempio
> Consideriamo il sistema lineare
> $$Ax=b,\qquad A=\begin{bmatrix}2&1\\1&2\end{bmatrix},\qquad b=\begin{bmatrix}1\\1\end{bmatrix}\qquad(\det(A)=3\neq0)$$
> e il metodo iterativo
> $$\begin{cases}x^{(0)}\in\mathbb{C}^2\ \text{dato}\\x^{(k+1)}=\left(I-\frac12A\right)x^{(k)}+\frac12b,\qquad k=0,1,2,\dots\end{cases}$$
> - (i) Stabilire se il metodo è consistente con il sistema dato.
> - (ii) Stabilire se il metodo è convergente.
> - (iii) Calcolare le prime 5 iterazioni del metodo partendo da $x^{(0)}=\begin{bmatrix}0\\0\end{bmatrix}$ e confrontarle con la soluzione esatta $x=\begin{bmatrix}1/3\\1/3\end{bmatrix}$.

**(i)** Il metodo è della forma (M) con matrice d'iterazione
$$P=I-\frac12A=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}$$
e vettore $q=\frac12b$. Sostituendo la soluzione $x$ del sistema nell'equazione del metodo al posto di $x^{(k)}$ e $x^{(k+1)}$ si ottiene
$$x=\left(I-\frac12A\right)x+\frac12b\iff x=x-\frac12Ax+\frac12b\iff\frac12Ax=\frac12b\qquad\text{VERO!}$$
perché $Ax=b$. Ho ottenuto un'identità verificata $\Rightarrow$ il metodo è consistente con il sistema dato.

**(ii)** Qui $\operatorname{traccia}(P)=0$ e $\det(P)=-\frac14$, quindi le condizioni necessarie sono soddisfatte; ma, essendo solo necessarie, non permettono di dire che il metodo converge. Per concludere con certezza si usa la condizione sufficiente, cercando una norma indotta con $\|P\|<1$ (le norme a disposizione sono $\|\cdot\|_1$, $\|\cdot\|_2$, $\|\cdot\|_\infty$). Si ricorda che $\|P\|_\infty$ è il **massimo** delle norme $1$ delle righe di $P$ (indicate con $P_{[1]}$, $P_{[2]}$). Poiché
$$\|P\|_\infty=\max\left(\|P_{[1]}\|_1,\|P_{[2]}\|_1\right)=\max\left(|0|+\left|-\tfrac12\right|,\ \left|-\tfrac12\right|+|0|\right)=\max\left(\tfrac12,\tfrac12\right)=\tfrac12<1$$
e poiché $\|\cdot\|_\infty$ è una norma matriciale indotta, concludiamo per il corollario della CS che il metodo è convergente. Si ottiene anche una stima del raggio spettrale:
$$\rho(P)\leq\|P\|_\infty=\frac12$$

> [!info] Anche la norma 1
> Andava bene anche $\|P\|_1$, il massimo delle norme $1$ delle colonne: anche qui viene $\frac12$. Il docente preferisce la norma $\infty$. Specificare che la norma usata è **indotta** non fa male: è una riga e dimostra che si è capito perché si può applicare il corollario.

**(iii)** L'equazione del metodo è
$$x^{(k+1)}=Px^{(k)}+q=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}x^{(k)}+\begin{bmatrix}1/2\\1/2\end{bmatrix},\qquad k=0,1,2,\dots$$
Le prime 5 iterazioni partendo da $x^{(0)}=\begin{bmatrix}0\\0\end{bmatrix}$ sono (a destra il valore decimale delle componenti, che sono uguali)
$$x^{(1)}=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}\begin{bmatrix}0\\0\end{bmatrix}+\begin{bmatrix}1/2\\1/2\end{bmatrix}=\begin{bmatrix}1/2\\1/2\end{bmatrix}\qquad0{,}5$$
$$x^{(2)}=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}\begin{bmatrix}1/2\\1/2\end{bmatrix}+\begin{bmatrix}1/2\\1/2\end{bmatrix}=\begin{bmatrix}1/4\\1/4\end{bmatrix}\qquad0{,}25$$
$$x^{(3)}=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}\begin{bmatrix}1/4\\1/4\end{bmatrix}+\begin{bmatrix}1/2\\1/2\end{bmatrix}=\begin{bmatrix}3/8\\3/8\end{bmatrix}\qquad0{,}375$$
$$x^{(4)}=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}\begin{bmatrix}3/8\\3/8\end{bmatrix}+\begin{bmatrix}1/2\\1/2\end{bmatrix}=\begin{bmatrix}5/16\\5/16\end{bmatrix}\qquad0{,}3125$$
$$x^{(5)}=\begin{bmatrix}0&-1/2\\-1/2&0\end{bmatrix}\begin{bmatrix}5/16\\5/16\end{bmatrix}+\begin{bmatrix}1/2\\1/2\end{bmatrix}=\begin{bmatrix}11/32\\11/32\end{bmatrix}\qquad0{,}34375$$
Ad esempio $x^{(3)}$: $-\frac12\cdot\frac14=-\frac18$ e $\frac12-\frac18=\frac48-\frac18=\frac38$; $x^{(5)}$: $-\frac12\cdot\frac5{16}=-\frac5{32}$ e $\frac{16}{32}-\frac5{32}=\frac{11}{32}$.

La soluzione esatta è $\frac13=0{,}\overline{3}$: le iterazioni oscillano intorno a $\frac13$ avvicinandosi sempre di più (come osservato a lezione, $\frac38$ è "quasi" $\frac39=\frac13$, $\frac5{16}$ è "quasi" $\frac5{15}=\frac13$, $\frac{11}{32}$ è "quasi" $\frac{11}{33}=\frac13$: si manca sempre "di un pelo", ma il denominatore cresce). Con $x^{(3)}$ si "prende" la prima cifra decimale, e manca poco a guadagnare la seconda: si vede chiaramente che il metodo converge, come previsto.

> [!info] Verifica (nostra aggiunta)
> Gli autovalori di $P$ sono $\pm\frac12$, quindi $\rho(P)=\frac12$: la stima $\rho(P)\leq\|P\|_\infty=\frac12$ è in questo caso un'uguaglianza. Inoltre $P\begin{bmatrix}1\\1\end{bmatrix}=-\frac12\begin{bmatrix}1\\1\end{bmatrix}$, quindi ogni componente di $x^{(k)}$ vale $\frac13-\frac13\left(-\frac12\right)^k$: l'errore si dimezza in modulo e cambia segno a ogni iterazione (per $k=5$: $\frac13+\frac1{96}=\frac{11}{32}$).

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare la condizione necessaria e sufficiente di convergenza per un metodo iterativo stazionario $x^{(k+1)}=Px^{(k)}+q$ consistente con $Ax=b$ (almeno l'implicazione $\rho(P)<1\Rightarrow$ convergenza). Traccia: definizioni di consistenza ($x=Px+q$) e di convergenza (per ogni $x^{(0)}$); sottrarre membro a membro equazione di consistenza ed equazione del metodo per ottenere l'equazione dell'errore $e^{(k+1)}=Pe^{(k)}$; sviluppo ricorsivo $e^{(k)}=P^ke^{(0)}$; $\rho(P)<1\Rightarrow P^k\to O\Rightarrow e^{(k)}\to0$, qualunque sia $e^{(0)}$.

> [!question] Domanda tipica d'esame
> Enunciare e dimostrare la condizione sufficiente (norma indotta) e le condizioni necessarie (traccia e determinante) di convergenza. Traccia: $\rho(P)\leq\|P\|<1$ per una norma **indotta**; per assurdo, se tutti gli autovalori avessero modulo $<1$ si avrebbe $|\operatorname{traccia}(P)|\leq\sum|\lambda_i|<n$ (disuguaglianza triangolare) e $|\det(P)|=\prod|\lambda_i|<1$.

> [!question] Domanda tipica d'esame
> Dati un sistema $Ax=b$ e un metodo iterativo stazionario, stabilire se il metodo è consistente, se è convergente, e calcolare alcune iterazioni confrontandole con la soluzione esatta. Traccia: sostituire $x$ nell'equazione del metodo e ridursi con passaggi equivalenti a $Ax=b$; individuare $P$ e controllare prima la traccia ($|\operatorname{traccia}(P)|\geq n\Rightarrow$ non converge), poi una norma indotta ($\|P\|_\infty$ o $\|P\|_1<1\Rightarrow$ converge), altrimenti il raggio spettrale; soluzione esatta con Gauss.

La lezione finisce circa un quarto d'ora prima del solito, così gli studenti possono seguire la lezione successiva (online). Il terzo esempio è rimandato alla prossima lezione, martedì: il docente ricorda la promessa di non sforare il giovedì, in cambio della possibilità di sforare un po' il martedì.
