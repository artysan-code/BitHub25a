# Modelli discreti
Appunti sui **modelli discreti** del corso (lezioni 05-12), organizzati nelle seguenti sezioni:
1. [[02 - Modelli discreti#Variabili aleatorie discrete|Variabili aleatorie discrete]] — definizione di v.a., funzione di distribuzione $F_{X}$, densità discreta.
2. [[02 - Modelli discreti#Distribuzioni binomiale e ipergeometrica|Distribuzioni binomiale e ipergeometrica]] — schemi successo-fallimento su $n$ prove.
3. [[02 - Modelli discreti#Distribuzione multinomiale|Distribuzione multinomiale]] — il caso di $r$ risultati possibili per prova.
4. [[02 - Modelli discreti#Distribuzioni uniforme discreta e di Poisson|Distribuzioni uniforme discreta e di Poisson]] — con l'approssimazione poissoniana della binomiale.
5. [[02 - Modelli discreti#Distribuzione geometrica|Distribuzione geometrica]] — geometrica e geometrica traslata, mancanza di memoria.
6. [[02 - Modelli discreti#Distribuzione binomiale negativa|Distribuzione binomiale negativa]] — generalizzazione al successo $r$-simo.
7. [[02 - Modelli discreti#Variabili aleatorie multidimensionali discrete|Variabili aleatorie multidimensionali discrete]] — densità congiunta e marginali, indipendenza.
8. [[02 - Modelli discreti#Trasformazioni e somme di variabili aleatorie discrete|Trasformazioni e somme di variabili aleatorie discrete]] — densità di $f(\underline{X})$, somme di binomiali e di poissoniane.
9. [[02 - Modelli discreti#Massimi e minimi di variabili aleatorie discrete|Massimi e minimi di variabili aleatorie discrete]] — densità di $\max$ e $\min$ tra v.a. indipendenti.
## Nota sulla struttura
Il prof tratta questi argomenti come un unico capitolo (Capitolo 3). I marcatori `--- Fine lezione NN ---` all'interno delle sezioni conservano la corrispondenza con i PDF delle lezioni in `Materiale Didattico/Slide/6 CFU/`.
## Variabili aleatorie discrete
Nozioni generali sulle variabili aleatorie: definizione, funzione di distribuzione, densità discreta.
In questo capitolo tratteremo essenzialmente Variabili Aleatorie Discrete (spesso definite su [[01 - Introduzione alla probabilità#Fenomeni aleatori e spazio di probabilità|spazi di probabilità]] ($\Omega,\mathcal{A},P$) con $\Omega$ discreto, cioè finito o numerabile).

In ogni caso nella parte iniziale di questa lezione diremo alcune cose sulle variabili aleatorie in generale. Spesso useremo l'abbreviazione "v.a.".

In generale una v.a. (definita su uno spazio di probabilità ($\Omega,\mathcal{A},P$)) è una funzione del tipo $$X:\Omega\to\mathcal{X}$$dove $\mathcal{X}$ è un qualche insieme, e con certe proprietà.

In questo corso tratteremo il caso in cui $\mathcal{X}=\mathbb{R}$ (o un suo sottoinsieme); in qualche caso considereremo il caso $\mathcal{X}=\mathbb{R}^{n}$ per qualche $n\geq 2$ (però solo per v.a. discrete).

Il concetto di v.a. è utile perché spesso gli eventi di interesse negli esercizi sono esprimibili tramite v.a.. Consideriamo un esempio.
##### Esempio
Si lanciano due dadi equi e consideriamo l'evento "la somma dei due numeri ottenuti è uguale a 5". Allora è utile fare riferimento alla seguente scelta dell'insieme $\Omega$: $$\Omega=\{1,\dots,6\}\times\{1,\dots,6\}=\{\omega=(\omega_{1},\omega_{2}):\omega_{1},\omega_{2}\in\{1,\dots,6\}\}$$Essendo $\Omega$ un insieme finito, non ci sono problemi nello scegliere $\mathcal{A}=\mathcal{P}(\Omega)$ (l'insieme delle parti di $\Omega$).

Inoltre è opportuno considerare la seguente funzione $X:\Omega\to\mathbb{R}$ (che è una v.a.) definita come segue: $$\begin{array}{}
X(\omega)=X(\omega_{1},\omega_{2})=\omega_{1}+\omega_{2} & (\forall\ \omega=(\omega_{1},\omega_{2})\in\Omega)
\end{array}$$Allora l'evento di interesse è $$\{\omega=(\omega_{1},\omega_{2})\in\Omega:X(\omega)=5\}$$
#### Definizione
Sia $(\Omega,\mathcal{A},P)$ uno spazio di probabilità. Inoltre sia $X:\Omega\to \mathbb{R}$ una funzione.
Allora la funzione $X$ è una v.a. (reale) se vale la seguente condizione $$\forall\ t\in\mathbb{R}\quad\quad\{\omega\in\Omega:X(\omega)\leq t\}\in\mathcal{A}$$In altri termini si richiede che le controimmagini delle semirette del tipo $(-\infty,t]$ (al variare di $t\in\mathbb{R}$), che sono sottoinsiemi di $\Omega$, siano elementi della $\sigma$-algebra $\mathcal{A}$.

Questo consente di dire che, per queste controimmagini, è possibile definire la probabilità.
Quindi possiamo dire che, per ogni $t\in\mathbb{R}$, $P(\{\omega\in\Omega:X(\omega)\leq t\})$ è un numero ben definito.

Quindi si richiede che, se $B=(-\infty,t]$ per una qualsiasi scelta di $t\in\mathbb{R}$, $$\{\omega\in\Omega:X(\omega)\in B\}\in\mathcal{A}\quad\quad\quad(*)$$A partire da questa richiesta, la condizione $(*)$ vale anche per le altre scelte di $B$ "naturali" da considerare:
- $B=[t,+\infty)$, $B=(t,+\infty)$, $B=(-\infty,t)$ per ogni $t\in\mathbb{R}$;
- $B=[s,t]$, $B=(s,t)$, $B=[s,t)$, $B=(s,t]$ per ogni $s,t\in\mathbb{R}$ con $s<t$;
- $B=\{t\}$ per ogni $t\in\mathbb{R}$;
- $B$ unione finita o numerabile di insiemi dei tipi indicati sopra (es. $B=(0,1)\cup\{2\}\cup[4,5)\cup[6,+\infty)$).
##### Notazioni che useremo
$\{\omega\in\Omega:X(\omega)\in B\}\longrightarrow$ useremo la notazione $\{X\in B\}$
$P(\{\omega\in\Omega:X(\omega)\in B\})\longrightarrow$ useremo la notazione $P(\{X\in B\})$, o anche $P(X\in B)$
#### Distribuzione o legge di una v.a. reale
È la corrispondenza tra "gli insiemi della retta $B$ per cui $\{X\in B\}\in\mathcal{A}$" e i valori $P(\{X\in B\})$ relativi.
#### Funzione di distribuzione di una v.a. reale
È la funzione $F_{X}:\mathbb{R}\to[0,1]$ così definita: $F_{X}(t)=P(X\leq t)$
##### Commento (importante)
La conoscenza di $F_{X}$ consente di individuare la distribuzione di una v.a. $X$.
Quindi, se uno conosce i valori di $P(X\in B)$ per $B=(-\infty,t]$ (al variare di tutti i valori di $t\in\mathbb{R}$), è possibile conoscere tutti i valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$

> [!note] Nota del prof
> Detto così non è preciso, ma per quel che vedremo in questo corso può andare bene.
#### Proprietà della funzione di distribuzione $F_{X}$
1) $F_{X}$ non è decrescente, cioè  $F_{X}(t_{1})\leq F_{X}(t_{2})\quad\quad\forall\ t_{1},t_{2}\in\mathbb{R}$ tali che $t_{1}\leq t_{2}$
   Questo si verifica facilmente osservando che
   $t_{1}\leq t_{2}\implies(-\infty,t_{1}]\subset(-\infty,t_{2}]\implies P(X\leq t_{1})\leq P(X\leq t_{2})\implies F_{X}(t_{1})\leq F_{X}(t_{2})$
   
2) $\displaystyle\lim_{t\to-\infty}F_{X}(t)=0$ e $\displaystyle\lim_{t\to+\infty}F_{X}(t)=1$
   
3) $F_{X}$ è continua a destra, cioè $\forall\ t_{0}\in\mathbb{R}\quad\quad\displaystyle\lim_{t\to t_{0}^{+}}F_{X}(t)=F_{X}(t_{0})$

> [!note] Grafico (lezione 05, p. 6)
> Nei punti di discontinuità accade quel che è rappresentato nel grafico: in $t_{0}$ la curva di $F_{X}$ fa un **salto verso l'alto**. Il valore $F_{X}(t_{0})$ è quello del punto più alto (pallino pieno), cioè coincide con il limite da destra: per questo $F_{X}$ è continua a destra. Il limite da sinistra, $\lim_{t\to t_{0}^{-}}F_{X}(t)=P(X<t_{0})$, è invece più basso. *(extra, non da slide)* L'ampiezza del salto è $P(X=t_{0})$.
##### Digressione
C'è una parte dei libri (una minoranza) che definisce la funzione di distribuzione in questo modo: $$F_{X}(t)=P(X<t)\quad\quad(\text{per ogni }t\in\mathbb{R})$$In questo caso le proprietà viste prima continuano a valere, tranne che la continuità a destra. In questo caso si ha che $F_{X}$ è continua a sinistra $$\lim_{t\to t_{0}^{-}}F_{X}(t)=F_{X}(t_{0})$$

> [!note] Grafico (lezione 05, p. 7)
> Nei punti di discontinuità, con $F_{X}(t)=P(X<t)$, il valore $F_{X}(t_{0})$ coincide con il limite da sinistra (pallino pieno all'estremo destro del tratto basso, in $t_{0}$), mentre il tratto alto riparte con estremo vuoto.
#### Variabili aleatorie discrete
Sia $X:\Omega\to \mathbb{R}$ una v.a. (reale) definita su uno spazio di probabilità $(\Omega,\mathcal{A},P)$.
Indichiamo con $S_{X}$ l'insieme dei valori assunti da $X$, cioè l'immagine di $X$ vista come funzione.

La definizione di questo insieme in termini matematici è la seguente: $$S_{X}=\{x\in\mathbb{R}: \exists\ \omega\in\Omega\text{ tale che }X(\omega)=x\}$$
#### Definizione
Una v.a. (reale) $X$ è una v.a. discreta se l'insieme $S_{X}$ è discreto (cioè $S_{X}$ è finito o numerabile).
##### Osservazione
Se $\Omega$ è discreto, allora $X$ è una v.a. discreta.
In generale non vale il viceversa:  ad esempio si pensi al caso in cui, per qualche $c\in\mathbb{R}$ si ha $$X(\omega)=c\quad\quad\forall\ \omega\in\Omega$$(quindi $S_{X}=\{c\}$) e $\Omega$ non è un insieme discreto.

Quando $X$ è una v.a. discreta, allora possiamo pensare di avere $$S_{X}=\{x_{i}\}_{i\in I}\quad\quad I\text{ è  un insieme discreto}$$In corrispondenza, per ogni $B\subset\mathbb{R}$ si ha $$\begin{array}{}
P(X\in B)=P(X\in B\cap S_{X})=P(X\in B\cap(\underset{i\in I}{\cup}\{x_{i}\}))=\displaystyle\sum_{i\in I}P(X\in B\cap\{x_{i}\})= \\
\underset{\underset{\text{somme finite o serie}\Rightarrow}{}}{=}\displaystyle\sum_{x_{i}\in S_{X}\cap B}P(X=x_{i})
\end{array}$$Quindi la distribuzione di una v.a. discreta $X$, cioè la conoscenza dei valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$, è individuata dalla conoscenza di $S_{X}=\{x_{i}\}_{i\in I}$ e delle probabilità $\{P(X=x_{i})\}_{i\in I}$.

Si osservi anche che, per $B=\mathbb{R}$, si ha $$\underset{=1}{\underbrace{P(X\in\mathbb{R})}} =\displaystyle\sum_{x_{i}\in\underset{=S_{X}}{\underbrace{S_{X}\cap\mathbb{R}}}}P(X=x_{i})$$da cui segue $$\begin{bmatrix}
\displaystyle\sum_{x_{i}\in S_{X}}P(X=x_{i})=1
\end{bmatrix}$$
##### Osservazione
Possiamo anche dire che $$\displaystyle\sum_{\begin{array}{}
x_{i}\in S_{X} \\
P(X=x_{i})>0
\end{array}}P(X=x_{i})=1$$

Più in generale si può considerare la funzione $p_{X}:\mathbb{R}\to[0,1]$ così definita: $$ p_{X}(x)=P(X=x)\quad\quad\forall\ x\in\mathbb{R}$$Tale funzione è detta **Densità Discreta** della v.a. $X$.
#### Proposizione 
$x\not\in S_{X}\implies p_{X}(x)=0$
##### Dimostrazione 
Si ha $$p_{X}(x)=P(\underset{=\varnothing\ (\ x\ \not\in\ S_{X})}{\underbrace{\{\omega\in\Omega:X(\omega)=x\}}})=P(\varnothing)=0$$

Come vedremo successivamente la funzione di distribuzione ha maggiore interesse quando la v.a. $X$ è continua.
In ogni caso vedremo come è fatta $F_{X}$ nel caso di v.a. discrete. Iniziamo con il caso in cui $S_{X}$ è un *insieme finito*; ad esempio $S_{X}=\{x_{1},\dots,x_{n}\}$ con $x_{1}<\dots<x_{n}$.
In questo grafico si ha $n=3$ (con $x_{1},x_{2},x_{3}$ minuscoli): $F_{X}$ è una funzione a gradini, $$F_{X}(t)=\begin{cases}0 & t<x_{1} \\ p_{X}(x_{1}) & x_{1}\leq t<x_{2} \\ p_{X}(x_{1})+p_{X}(x_{2}) & x_{2}\leq t<x_{3} \\ 1 & t\geq x_{3}\end{cases}$$e il gradino in $x_{i}$ ha altezza $p_{X}(x_{i})$ (pallino pieno all'inizio di ogni tratto: continuità a destra).
##### Osservazione
Dal grafico (caso $n=3$) si vede che $$\underset{=p_{X}(x_{1})+p_{X}(x_{2})+p_{X}(x_{3})}{\underbrace{\displaystyle\sum_{i=1}^{n}p_{X}(x_{i})}}=1$$

Nel caso in cui $S_{X}$ è *infinito numerabile* la casistica è più varia e ci possono essere casi molto complicati. Qui faccio riferimento a due casi (soprattutto il primo ci interessa in vista di ciò che vedremo con le distribuzioni di Poisson e geometriche)
1) $S_{X}=\{x_{0},x_{0}+1,x_{0}+2,\dots\}$
2) $S_{X}=\left\{ 1,\frac{1}{2},\frac{1}{3},\dots,\frac{1}{n},\dots\right\}$

Dai grafici delle slide (lezione 05, p. 13): nel caso 1) $F_{X}$ è a gradini con salti in $x_{0},x_{0}+1,x_{0}+2,\dots$ e cresce verso $1$ senza raggiungerlo; nel caso 2) i gradini si infittiscono avvicinandosi a $0$ da destra, $F_{X}(t)=0$ per $t\leq 0$ e $F_{X}(t)=1$ per $t\geq1$.

> [!question] Domanda tipica d'esame
> Definire la funzione di distribuzione $F_{X}$ di una v.a. reale e dire quali proprietà ha.
> **Risposta.** $F_{X}(t)=P(X\leq t)$, per $t\in\mathbb{R}$. È non decrescente, tende a $0$ per $t\to-\infty$ e a $1$ per $t\to+\infty$, ed è continua a destra. (Con la convenzione $P(X<t)$ sarebbe continua a sinistra.)
## Distribuzioni binomiale e ipergeometrica
Schemi successo-fallimento su un numero finito di prove: distribuzione bernoulliana, binomiale e ipergeometrica.
#### Introduzione alle distribuzioni notevoli
Si parla di "distribuzione notevole" quando queste hanno certe espressioni (eventualmente dipendente da qualche parametro), un po' come accade per i prodotti notevoli nel calcolo letterale.

Per le v.a. discrete tipicamente ci si riferisce alla espressione delle densità discrete. Talvolta si fa riferimento ad alcune situazioni pratiche (modalità di "effettuare prove", ad esempio estrazioni casuali di oggetti).

Per le v.a. continue tipicamente ci si riferisce alle espressioni delle funzioni di distribuzioni o, equivalentemente (più o meno) alle densità continue $[$ancora non abbiamo parlato di densità continue$]$
#### Distribuzione Bernoulliana
Si usa questo termine quando $S_{X}=\{0,1\}$.
Talvolta è utile pensare ad un evento $B\in \mathcal{A}$ tale che $$\begin{array}{l}
X=1 & \iff & \text{l'evento }B\text{ si verifica} \\
X=0 & \iff & \text{l'evento }B\text{ non si verifica}
\end{array}$$Talvolta si usa anche la notazione $X=1_{B}$
In questo caso si ha $$\begin{cases}
p_{X}(1)=P(X=1)=P(B) \\
p_{X}(0)=P(X=0)=P(B^{c})
\end{cases}$$
Quindi 
- se $0<P(B)<1$ (e quindi $0<P(B^{c})<1$)
  $F_{X}(t)=0$ per $t<0$; $F_{X}(t)=P(B^{c})$ per $0\leq t<1$; $F_{X}(t)=1$ per $t\geq1$ (salti di altezza $P(B^{c})$ in $0$ e $P(B)$ in $1$)
- se $P(B)=1$ (e quindi $P(B^{c})=0$)
  $F_{X}(t)=0$ per $t<1$ e $F_{X}(t)=1$ per $t\geq1$ (unico salto, di altezza $P(B)=1$, in $t=1$)
- se $P(B)=0$ (e quindi $P(B^{c})=1$)
  $F_{X}(t)=0$ per $t<0$ e $F_{X}(t)=1$ per $t\geq0$ (unico salto, di altezza $P(B^{c})=1$, in $t=0$)
#### Schemi Successo-Fallimento su un numero finito di prove
Si tratta di una premessa comune per due casi che vedremo nella prossima lezione:
1) **[[02 - Modelli discreti#Caso 1): distribuzione binomiale|Distribuzione Binomiale]]** (caso di $n$ prove indipendenti, tutte con la stessa probabilità di successo $p$)
2) **[[02 - Modelli discreti#Caso 2): distribuzione ipergeometrica|Distribuzione Ipergeometrica]]** (caso di $n$ estrazioni casuali di un oggetto alla volta senza reinserimento (un caso particolare senza avere prove indipendenti)) ^8912f8
##### Osservazione
Nel caso [[#^8912f8|2)]] otterremo nuovamente le formule delle [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]] già viste in passato

In entrambi i casi si vuole studiare la v.a. $X$ che conta il numero di successi.
Nel caso [[#^8912f8|2)]] gli oggetti sono di due tipi, e si ha successo con l'estrazione di oggetti di un certo tipo. Ad esempio: 
oggetti colorati con un certo colore,
oggetti numerati con un certo numero,
ecc.

In entrambi i casi conviene fare riferimento all'insieme $\Omega$ così definito: $$\Omega=\underset{n\text{ volte}}{\underbrace{\{0,1\}\times\dots\times\{0,1\}}}= \{\omega=(\omega_{1},\dots,\omega_{n}):\omega_{1},\dots,\omega_{n}\in\{0,1\}\}$$Ogni punto $\omega\in\Omega$ descrive i possibili risultati (successi o fallimenti) nelle $n$ prove.
Sceglieremo $\mathcal{A}=\mathcal{P}(\Omega)$.
Avremo due diverse [[01 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|misure di probabilità]] $P$ per i casi 1) e 2).
##### Osservazione
- Per $n=1$ abbiamo ovviamente una [[02 - Modelli discreti#Distribuzione Bernoulliana|distribuzione Bernoulliana]]
- In generale si dovrà avere $S_{X}=\{0,1,\dots,n\}$ e questo è quel che accadrà.

Noi siamo interessati a contare successi (cioè quanti "1") ci sono nella stringa dei risultati. 
Allora è opportuno considerare le v.a. così definite: $$X(\omega)=\omega_{1}+\dots+\omega_{n}\quad\quad\forall\ \omega=(\omega_{1},\dots,\omega_{n})\in\Omega$$Da qui si vede bene che $S_{X}=\{0,1,\dots,n\}$.
##### Osservazione
Ad esempio la v.a. $Y$ che conta il numero di fallimenti è $Y$ così definita: $$Y(\omega)=n-X(\omega)\quad\quad\forall\ \omega=(\omega_{1},..,\omega_{n})\in\Omega$$
Del resto $Y(\omega)=(1+\dots+1)-(\omega_{1}+\dots+\omega_{n})=1-\omega_{1}+\dots+1-\omega_{n}$ (che in effetti conta il numero di "0" nella stringa dei risultati)

Nella prossima lezione vedremo come definire le misure di probabilità $P$ su $(\Omega,\mathcal{A})=(\Omega,\mathcal{P}(\Omega))$ a partire dagli insiemi costruiti dai singoli punti, cioè a partire dalle seguenti quantità: $$P(\{\omega\})=P(\{(\omega_{1},\dots,\omega_{n})\})\quad\quad\forall\ \omega=(\omega_{1},\dots,\omega_{n})\in\Omega$$Due diverse situazioni per i casi 1) e 2).

Dopo aver fatto questo troveremo la densità discreta di $X$:
per $k\in\{0,1,\dots,n\}\quad\quad p_{X}(k)=P(X=k)=P(\{\omega\in\Omega:X(\omega)=k\})=\displaystyle\sum_{\omega:X(\omega)=k}P(\{\omega\})\quad\quad(*)$
Per fissare le idee consideriamo il caso $n=3$.
Abbiamo $\Omega=\{0,1\}\times\{0,1\}\times\{0,1\}=\{\omega=(\omega_{1},\omega_{2},\omega_{3}):\omega_{1},\omega_{2},\omega_{3}\in\{0,1\}\}$

Allora "le sequenze $\omega$ per cui $X(\omega)=k$" sono: $$\begin{array}{l}
\text{per }k=0 & &  (0,0,0) \\
\text{per }k=1 & &  (0,0,1),(0,1,0),(1,0,0) \\
\text{per }k=2 & &  (0,1,1),(1,0,1),(1,1,0) \\
\text{per }k=3 & &  (1,1,1) \\
\end{array}$$Quindi $$\begin{array}{l}
p_{X}(0)=P(\{(0,0,0)\}) \\
p_{X}(1)=P(\{(0,0,1)\})+P(\{(0,1,0)\})+P(\{(1,0,0)\}) \\
p_{X}(2)=P(\{(0,1,1)\})+P(\{(1,0,1)\})+P(\{(1,1,0)\}) \\
p_{X}(3)=P(\{(1,1,1)\})
\end{array}$$

--- Fine lezione 05 ---

Qui abbiamo un altra cosa che accadrà nei due casi che vedremo, nei casi 1) e 2) avremo che: $$X(\omega)=X(\omega')\implies P(\{\omega\})=P(\{\omega'\})$$Cioè, date due qualsiasi sequenza $\omega$ e $\omega'$ con lo stesso numero di successi, le rispettive probabilità coincidono

Allora sarà conveniente dire che $$\begin{array}{}
\forall\ k\in S_{X}=\{0,1,\dots,n\},\quad\quad\text{esiste }q_{k}\text{ tale che} \\
X(\omega)=k\implies P(\{\omega\})=q_{k}
\end{array}$$
##### Esempio
con $n=3$, esistono $q_{0},q_{1},q_{2},q_{3}\geq 0$ tali che $$\begin{cases}
P(\{(0,0,0)\})=q_{0} \\
P(\{(1,0,0)\})=P(\{(0,1,0)\})=P(\{(0,0,1)\})=q_{1} \\
P(\{(1,1,0)\})=P(\{(1,0,1)\})=P(\{(0,1,1)\})=q_{2} \\
P(\{(1,1,1)\})=q_{3}
\end{cases}$$Ovviamente si dovrà avere $q_{0}+3q_{1}+3q_{2}+q_{3}=1$

In corrispondenza, se poniamo (nuova notazione)$$r_{n,k}=\#\{\omega:X(\omega)=k\}$$per ogni $k\in S_{X}=\{0,1,\dots,n\}$ si ha $$p_{X}(k)\overset{(*)}{=}\sum_{\omega:X(\omega)=k}P(\{\omega\})=\sum_{\omega:X(\omega)=k}q_{k}=\underset{r_{n,k}\text{ volte}}{\underbrace{q_{k}+\dots+q_{k}}}=r_{n,k}\cdot q_{k}$$Il valore di $q_{k}$ verrà determinato dalle ipotesi dei casi 1) e 2)
Il valore di $r_{n,k}$ possiamo calcolarlo facilmente e si ha: $r_{n,k}=\binom{n}{k}$
Quindi nei casi 1) e 2) avremo $$p_{X}(k)=\binom{n}{k}q_{k}\quad\quad\text{ per }k\in\{0,1,\dots,n\}\quad\quad(\diamondsuit)$$
##### Proposizione
Si ha $r_{n,k}=\binom{n}{k}$

**Dimostrazione**
Ad ogni sequenza di lunghezza $n$ e con esattamente $k$ volte "1" possiamo abbinare il sottoinsieme di $\{1,\dots,n\}$ delle posizioni degli "1": $$\begin{array}{}
\omega=(\omega_{1},\dots,\omega_{n}) & \longleftrightarrow & \{i_{1},\dots,i_{k}\}\subset\{1,\dots,n\} \\
\text{osservazione 1} &  & \text{osservazione 2}
\end{array}$$
##### Osservazione 1
Il numero di stringhe di "questo tipo" è proprio $r_{n,k}=\#\{\omega:X(\omega)=k\}$
##### Osservazione 2
Noi sappiamo che i sottoinsiemi di "questo tipo" sono in tutto $\binom{n}{k}$

Si ha una **corrispondenza biunivoca** tra l'insieme di sequenze e l'insieme dei sottoinsiemi. Essendo una corrispondenza biunivoca tra due insiemi finiti, hanno lo stesso numero di elementi $\Box$ 
##### Esempio (corrispondenza biunivoca)
$n=4$,$k=2$ $$\begin{array}{}
\text{sequenze} &  & \text{sottoinsiemi} & (\text{sono }\binom{4}{2}=6) \\
(1,1,0,0) & \longleftrightarrow & \{1,2\} \\
(1,0,1,0) & \longleftrightarrow & \{1,3\} \\
(1,0,0,1) & \longleftrightarrow & \{1,4\} \\
(0,1,1,0) & \longleftrightarrow & \{2,3\} \\
(0,1,0,1) & \longleftrightarrow & \{2,4\} \\
(0,0,1,1) & \longleftrightarrow & \{3,4\}
\end{array}$$Questo spiega che abbiamo $r_{4,2}=6$ sequenze binarie di lunghezza 4 e con esattamente 2 volte "1".
#### Caso 1): distribuzione binomiale
Si usa per la v.a. che conta il numero di successi su $n$ prove indipendenti, con probabilità di successo $p$ in ogni prova (quindi in ogni prova c'è una probabilità di fallimento $1-p$)
##### Esempi:
- $n$ lanci di moneta (o lanci di $n$ monete dello stesso tipo) e il successo è "esce testa" (oppure "esce croce")
- $n$ lanci di dado (o lanci di $n$ dadi dello stesso tipo) e il successo è "esce un numero in $S$" dove $S\subset\{1,2,3,4,5,6\}$ fissato
- $n$ estrazioni casuali di un oggetto alla volta con reinserimento da un insieme di $n_{1}$ oggetti di tipo 1 e $n_{2}$ oggetti di tipo 2; e il successo è "estratto il tipo 1" (oppure "estratto il tipo 2")

Dobbiamo attribuire i valori $P(\{\omega\})$ per $\omega\in\Omega$
##### Osservazione
$\#\Omega=2^{n}$

Per fissare le idee consideriamo il caso $n=3$. Si ha $\#\Omega=2^{3}=8$. $$\begin{array}{rrl}
P(\{(0,0,0)\})= & (1-p)(1-p)(1-p)= & (1-p)^{3}\\
P(\{(1,0,0)\})= & p(1-p)(1-p)= & p(1-p)^{2} \\
P(\{(0,1,0)\})= & (1-p)p(1-p)= & p(1-p)^{2} \\
P(\{(0,0,1)\})= & (1-p)(1-p)p= & p(1-p)^{2} \\
P(\{(1,1,0)\})= & p\cdot p(1-p)= & (1-p)p^{2} \\
P(\{(1,0,1)\})= & p(1-p)p= & (1-p)p^{2}\\
P(\{(0,1,1)\})= & (1-p)p\cdot p= & (1-p)p^{2} \\
P(\{(1,1,1)\})= & p\cdot p\cdot p= & p^{3}
\end{array}$$Si vede che $$\begin{array}{l}
X(\omega)=0\implies P(\{\omega\})=(1-p)^{3} & \longleftrightarrow  q_{0} \\
X(\omega)=1\implies P(\{\omega\})=p(1-p)^{2} & \longleftrightarrow q_{1} \\
X(\omega)=2\implies P(\{\omega\})=p^{2}(1-p) & \longleftrightarrow q_{2} \\
X(\omega)=3\implies P(\{\omega\})=p^{3} & \longleftrightarrow q_{3} \\
\end{array}$$

Ora consideriamo il caso generale. Si ha $$\begin{array}{}
P(\omega)= & \underset{1^{\text{a}}\text{ prova}}{\underbrace{p^{\omega_{1}}(1-p)^{1-\omega_{1}}}}\quad \underset{2^{\text{a}}\text{ prova}}{\underbrace{p^{\omega_{2}}(1-p)^{1-\omega_{2}}}}\quad\dots\quad\underset{n^{\text{a}}\text{ prova}}{\underbrace{p^{\omega_{n}}(1-p)^{1-\omega_{n}}}} \\
 & =p^{\omega_{1}+\dots+\omega_{n}}(1-p)^{1-\omega_{1}+1-\omega_{2}+\dots+1-\omega_{n}\quad\longleftrightarrow(n-(\omega_{1}+\dots+\omega_{n}))} \\
 & =p^{X(\omega)}(1-p)^{n-X(\omega)}
\end{array}$$
##### Osservazione
Per ogni $k\in S_{X}=\{0,1,\dots,n\}$ possiamo dire che:
per ogni $\omega$ tale che $X(\omega)=k$ si ha $$P(\{\omega\})=p^{k}(1-p)^{n-k}$$Quindi per ogni sequenza di $n$ prove con esattamente $k$ successi si ha la stessa probabilità.
Il valore $p^{k}(1-p)^{n-k}$ rappresenta il valore $q_{k}$ introdotto in passato.
A questo punto, con riferimento alla formula ($\diamondsuit$), si ha $$p_{X}(k)=\binom{n}{k}\underset{=q_{k}}{\underbrace{p^{k}(1-p)^{n-k}}}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$Questa è la densità discreta delle v.a. con distribuzione binomiale.
Abbiamo due parametri:$$\begin{cases}
n=\# \text{ delle prove indipendenti} \\
p=\text{probabilità di successo di ogni prova}
\end{cases}$$

Talvolta si scrive $X\sim BIN(n,p)$.
##### Osservazioni
1) Si deve avere $\displaystyle\sum_{k=0}^{n}p_{X}(k)=1$. In effetti, per il **binomio di Newton**, $\displaystyle\sum_{k=0}^{n}\binom{n}{k}p^{k}(1-p)^{n-k}=(p+(1-p))^{n}=1^{n}=1$
2) Per $p=\frac{1}{2}$ si ha $1-p=\frac{1}{2}$; quindi la formula si semplifica un po': $$p_{X}(k)=\binom{n}{k}\left( \frac{1}{2} \right)^{n}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$
3) Per $p=0$ si ha $p_{X}(0)=1$ e $p_{X}(k)=0$ per $k\neq 0$.
   Per $p=1$ si ha $p_{X}(n)=1$ e $p_{X}(k)=0$ per $k\neq n$.
   (Come ci si aspetta; qui si usa la regola $0^{0}=1$.)
   Inoltre, se $0<p<1$, si ha $p_{X}(k)>0$ per ogni $k\in\{0,1,\dots,n\}$.
##### Digressione: perché si dice che $0^{0}=1$
La giustificazione data a lezione è un calcolo di limite (dalla foto della lavagna `zero-alla-zero-uguale-a-1-spiegazione.jpg`, in `Materiale Didattico/Slide/6 CFU/`; le slide dicono solo «regola: $0^{0}=1$»): $$\lim_{x\to 0^{+}}x^{x}=\lim_{x\to 0^{+}}e^{x\log x}\overset{(1)}{=}e^{\overset{(*)}{\overbrace{\lim_{x\to 0^{+}}x\log x}}}=e^{0}=1$$dove in $(1)$ si è usato che $f(x)=e^{x}$ è una funzione continua, e dove il limite $(*)$ si calcola con il teorema di de l'Hôpital: $$(*)=\lim_{x\to 0^{+}}\frac{\log x}{1/x}=\lim_{x\to 0^{+}}\frac{1/x}{-1/x^{2}}=\lim_{x\to 0^{+}}-\frac{x^{2}}{x}=\lim_{x\to 0^{+}}-x=0$$
#### Caso 2): distribuzione ipergeometrica
Supponiamo di avere $n_{1}$ oggetti di "tipo 1" e $n_{2}$ oggetti di "tipo 2". Si estraggono a caso $n$ oggetti (dove $n<n_{1}+n_{2}$), una alla volta e **senza** reinserimento: quindi *non* c'è [[01 - Introduzione alla probabilità#Definizione (Indipendenza tra due eventi)|indipendenza]], a differenza del caso di estrazioni con reinserimento.
La convenzione è: $$\begin{array}{l}
\text{successo} & \longleftrightarrow & \text{"estrazione di un oggetto di tipo 1"} \\
\text{fallimento} & \longleftrightarrow & \text{"estrazione di un oggetto di tipo 2"}
\end{array}$$
Consideriamo il caso della sequenza $$\omega=(\underset{k\text{ volte}}{\underbrace{1,\dots,1}},\underset{n-k\text{ volte}}{\underbrace{0,\dots,0}})$$Si ha $P(\{\omega\})=0$ se $k>n_{1}$ oppure $n-k>n_{2}$ (ovvio: non ci sono abbastanza oggetti di quel tipo).
Al contrario, se $0\leq k\leq n_{1}$ e $0\leq n-k\leq n_{2}$, si ha $$P(\{\omega\})=\underset{\text{prob. 1}^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}}{n_{1}+n_{2}}}}\cdot\underset{\text{prob. 2}^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}-1}{n_{1}+n_{2}-1}}}\cdot\ \dots\ \cdot\underset{\text{prob. }k^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}-(k-1)}{n_{1}+n_{2}-(k-1)}}}\cdot\underset{\text{prob. }(k+1)^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{2}}{n_{1}+n_{2}-k}}}\cdot\frac{n_{2}-1}{n_{1}+n_{2}-k-1}\cdot\ \dots\ \cdot\frac{n_{2}-(n-k-1)}{n_{1}+n_{2}-(n-1)}$$dove ogni fattore dal secondo in poi è una probabilità condizionata "sapendo il passato" (si veda la [[01 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]). *(extra, non da slide)*
##### Osservazione
Se si cambia sequenza (sempre con $k$ volte "1" e $n-k$ volte "0") si ottiene sempre lo stesso valore: i denominatori sono gli stessi, cambia solo l'ordine dei fattori a numeratore.
Quindi siamo nella condizione di dire che, per ogni $k\in\{0,1,\dots,n\}$, esiste $q_{k}$ tale che $X(\omega)=k\implies P(\{\omega\})=q_{k}$, dove $$q_{k}=\begin{cases}
0 & \text{se }k>n_{1}\text{ oppure }n-k>n_{2} \\
\frac{n_{1}}{n_{1}+n_{2}}\cdot\dots\cdot\frac{n_{1}-(k-1)}{n_{1}+n_{2}-(k-1)}\cdot\frac{n_{2}}{n_{1}+n_{2}-k}\cdot\dots\cdot\frac{n_{2}-(n-k-1)}{n_{1}+n_{2}-(n-1)} & \text{altrimenti}
\end{cases}$$
Il secondo caso si riscrive in termini di [[01 - Introduzione alla probabilità#Cenni di calcolo combinatorio|coefficienti binomiali]]: $$q_{k}=\frac{\frac{n_{1}!}{(n_{1}-k)!}\cdot\frac{n_{2}!}{(n_{2}-(n-k))!}}{\frac{(n_{1}+n_{2})!}{(n_{1}+n_{2}-n)!}}=\frac{\overset{}{\frac{n_{1}!}{k!(n_{1}-k)!}}k!\cdot \frac{n_{2}!}{(n-k)!(n_{2}-(n-k))!}(n-k)!}{\frac{(n_{1}+n_{2})!}{n!(n_{1}+n_{2}-n)!}n!}=\frac{\binom{n_{1}}{k}k!\binom{n_{2}}{n-k}(n-k)!}{\binom{n_{1}+n_{2}}{n}n!}=\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}\binom{n}{k}}$$
##### Osservazione
Questa formula si estende anche al caso $k>n_{1}$ oppure $n-k>n_{2}$ con la regola $\binom{a}{b}=0$ per $b>a$ (già incontrata nelle [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]]).
In conclusione, con riferimento alla formula ($\diamondsuit$), si ha $$p_{X}(k)=\cancel{\binom{n}{k}}\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}\cancel{\binom{n}{k}}}=\begin{bmatrix}
\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}
\end{bmatrix}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$Questa è la densità discreta delle v.a. con **distribuzione ipergeometrica**.
Qui abbiamo tre parametri: $n_{1},n_{2}\geq 1$ interi, e $n$ intero con $n<n_{1}+n_{2}$.
##### Osservazioni
1) Si può verificare che $\displaystyle\sum_{k=0}^{n}p_{X}(k)=1$ (il prof omette i dettagli).
2) A differenza del caso della distribuzione binomiale si può avere qualche caso con $p_{X}(k)=0$ "non banale": si tratta di trovare valori di $k$ tali che $k>n_{1}$ oppure $n-k>n_{2}$. In qualche caso si riesce a trovarli, in altri no: dipende da $n_{1}$ e $n_{2}$.
##### Osservazione (raccordo con le estrazioni in blocco della nota 01)
Ritroviamo esattamente la formula delle [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]], come anticipato: estrarre $n$ oggetti uno alla volta senza reinserimento e contare i successi dà la stessa distribuzione che estrarli in blocco.
#### Un commento sulla validità della formula ($\diamondsuit$)
La formula ($\diamondsuit$) segue dall'ipotesi $$\forall\ k\in\{0,1,\dots,n\}\ \text{ esiste }q_{k}\text{ tale che }X(\omega)=k\implies P(\{\omega\})=q_{k}\quad\quad(\bullet\bullet)$$cioè dal fatto che *ogni sequenza con esattamente $k$ successi ha la stessa probabilità*.
Ora presentiamo un esempio dove $(\bullet\bullet)$ **non** è vera. Prendiamo $n=2$ prove indipendenti, con probabilità di successo $p_{1}$ e $p_{2}$ diverse tra loro ($p_{1}\neq p_{2}$). Si ha $$\begin{array}{ll}
P(\{(0,0)\})=(1-p_{1})(1-p_{2}), & P(\{(1,0)\})=p_{1}(1-p_{2}), \\
P(\{(0,1)\})=(1-p_{1})p_{2}, & P(\{(1,1)\})=p_{1}p_{2}
\end{array}$$Se per assurdo si avesse $(\bullet\bullet)$, per $k=1$ si avrebbe $P(\{(1,0)\})=P(\{(0,1)\})$ da cui seguirebbe $$p_{1}(1-p_{2})=p_{2}(1-p_{1})\implies p_{1}-p_{1}p_{2}=p_{2}-p_{1}p_{2}\implies p_{1}=p_{2}$$contro l'ipotesi $p_{1}\neq p_{2}$.
In questo caso si ha (calcolando direttamente, senza ($\diamondsuit$)) $$\begin{cases}
p_{X}(0)=(1-p_{1})(1-p_{2}) \\
p_{X}(1)=p_{1}(1-p_{2})+p_{2}(1-p_{1}) \\
p_{X}(2)=p_{1}p_{2}
\end{cases}$$
##### Esempio (materiale aggiuntivo della lezione 05)
Sia $\Omega=\{\omega=(\omega_{1},\omega_{2}):\omega_{1},\omega_{2}\in\{0,1\}\}$, $X(\omega)=\omega_{1}+\omega_{2}$ e $$P(\{(0,0)\})=\tfrac{1}{5},\quad P(\{(0,1)\})=\tfrac{2}{5},\quad P(\{(1,0)\})=\tfrac{1}{5},\quad P(\{(1,1)\})=\tfrac{1}{5}.$$Allora $p_{X}(0)=P(\{(0,0)\})=\frac{1}{5}$, $p_{X}(1)=P(\{(0,1)\})+P(\{(1,0)\})=\frac{3}{5}$, $p_{X}(2)=P(\{(1,1)\})=\frac{1}{5}$. *(Commento, non da slide:)* qui due sequenze con lo stesso numero di successi, $(0,1)$ e $(1,0)$, hanno probabilità diverse ($\frac{2}{5}\neq\frac{1}{5}$), quindi non vale $(\bullet\bullet)$.
#### Esempio: confronto binomiale / ipergeometrica
Un'urna ha 3 palline bianche e 6 nere. Si estraggono a caso 4 palline, una alla volta.
1) **Con reinserimento**: trovare la densità discreta della v.a. $X$ che conta il numero di palline bianche estratte.
   Si ha $X\sim BIN\left( n=4,p=\frac{3}{9}=\frac{1}{3} \right)$, e per $k\in\{0,1,2,3,4\}$ $$p_{X}(k)=\binom{4}{k}\left( \frac{1}{3} \right)^{k}\left( 1-\frac{1}{3} \right)^{4-k}=\binom{4}{k}\left( \frac{1}{3} \right)^{k}\left( \frac{2}{3} \right)^{4-k}=\begin{cases}
16/81 & k=0 \\
32/81 & k=1 \\
24/81 & k=2 \\
8/81 & k=3 \\
1/81 & k=4
\end{cases}$$(la somma fa 1).
2) **Senza reinserimento**: $X$ è [[02 - Modelli discreti#Caso 2): distribuzione ipergeometrica|ipergeometrica]] con $n_{1}=3$, $n_{2}=6$, $n=4$, e per $k\in\{0,1,2,3,4\}$ $$p_{X}(k)=\frac{\binom{3}{k}\binom{6}{4-k}}{\binom{9}{4}}=\begin{cases}
15/126 & k=0 \\
60/126 & k=1 \\
45/126 & k=2 \\
6/126 & k=3 \\
0 & k=4
\end{cases}$$(la somma fa 1). Qui si ha zero per $k=4$ perché $k>n_{1}$ ($4>3$): in effetti $\binom{n_{1}}{k}=\binom{3}{4}=0$.
#### Esempio: schema binomiale "nascosto" (4 urne)
Abbiamo 4 urne, tutte con 2 palline bianche e 3 rosse. Da ogni urna si estraggono a caso 2 palline, una alla volta e **senza** reinserimento.
1) Trovare la densità discreta della v.a. $X_{1}$ che conta il numero di urne dalle quali si estraggono 2 palline di colori diversi.
2) Trovare la densità discreta della v.a. $X_{2}$ che conta il numero di urne dalle quali si estraggono una pallina rossa e una bianca *in quest'ordine*.

**Svolgimento.** Le estrazioni da urne diverse non si influenzano, e quindi definiscono famiglie di eventi [[01 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenti]]. Quindi in entrambi i casi si tratta di contare il numero di successi su 4 prove indipendenti, tutte con la stessa probabilità di successo: $$\begin{array}{ll}
X_{1}\sim BIN(n=4,p_{1}) & p_{1}=\text{prob. di estrarre colori diversi da una singola urna} \\
X_{2}\sim BIN(n=4,p_{2}) & p_{2}=\text{prob. di estrarre la sequenza }(R,B)\text{ da una singola urna}
\end{array}$$
1) Calcolo $p_{1}$ in due modi diversi (dove $R_{i}$ e $B_{i}$ sono gli eventi "alla $i$-esima estrazione esce una pallina rossa" e "...bianca"): $$\begin{array}{ll}
1^{\circ}\text{ modo} & p_{1}=\frac{\binom{2}{1}\binom{3}{1}}{\binom{5}{2}}=\frac{2\cdot 3}{10}=\frac{3}{5} \\
2^{\circ}\text{ modo} & p_{1}=P(R_{2}|B_{1})P(B_{1})+P(B_{2}|R_{1})P(R_{1})=\frac{3}{4}\cdot \frac{2}{5}+\frac{2}{4}\cdot \frac{3}{5}=\frac{3}{10}+\frac{3}{10}=\frac{6}{10}=\frac{3}{5}
\end{array}$$da cui, per $k\in\{0,1,2,3,4\}$, $$p_{X_{1}}(k)=\binom{4}{k}p_{1}^{k}(1-p_{1})^{4-k}=\begin{cases}
16/625 & k=0 \\
96/625 & k=1 \\
216/625 & k=2 \\
216/625 & k=3 \\
81/625 & k=4
\end{cases}$$
2) Calcolo $p_{2}$ come segue: $p_{2}=P(B_{2}|R_{1})P(R_{1})=\frac{2}{4}\cdot \frac{3}{5}=\frac{3}{10}$, da cui $$p_{X_{2}}(k)=\binom{4}{k}p_{2}^{k}(1-p_{2})^{4-k}=\begin{cases}
2401/10000 & k=0 \\
4116/10000 & k=1 \\
2646/10000 & k=2 \\
756/10000 & k=3 \\
81/10000 & k=4
\end{cases}$$
#### Esempio: ipergeometrica con $n_{1}+n_{2}$ "molto più grande" di $n$
Un'urna ha 500 palline bianche e 500 nere. Si estraggono 3 palline a caso, una alla volta e **senza** reinserimento. Trovare la densità della v.a. $X$ che conta il numero di palline bianche estratte. $$p_{X}(k)=\frac{\binom{500}{k}\binom{500}{3-k}}{\binom{1000}{3}}=\begin{cases}
\frac{500\cdot 499\cdot 498}{1000\cdot 999\cdot 998}\approx \frac{1}{2}\cdot \frac{1}{2}\cdot \frac{1}{2}=\frac{1}{8} & \text{per }k=0\text{ e }k=3 \\
3\cdot \frac{1}{2}\cdot \frac{1}{2}\cdot \frac{1}{2}\approx\frac{3}{8} & \text{per }k=1\text{ e }k=2
\end{cases}$$
##### Commento
Se si considerasse il caso di estrazioni **con** reinserimento si avrebbe $X\sim BIN\left( n=3,p=\frac{500}{1000}=\frac{1}{2} \right)$ e si avrebbe $$p_{X}(k)=\binom{3}{k}\left( \frac{1}{2} \right)^{3}=\begin{cases}
1/8 & \text{per }k=0\text{ e }k=3 \\
3/8 & \text{per }k=1\text{ e }k=2
\end{cases}$$Quando $n_{1}+n_{2}$ è "molto più grande" di $n$ si ha una situazione **molto vicina al caso di estrazioni con reinserimento**.

> [!info] Esercizi conclusivi della lezione 06
> Le ultime pagine della lezione 06 (pp. 20-23) contengono due esercizi di riepilogo "con agganci con argomenti passati" (lanci ripetuti di un dado equo; lanci ripetuti di una coppia di dadi), che combinano distribuzione binomiale, indipendenza e probabilità condizionata; sono svolti qui sotto.
#### Esercizio: lanci ripetuti di un dado (lezione 06, pp. 20-21)
Si lancia $4$ volte un dado equo. Calcolare la probabilità che: 1) esca almeno una volta il numero $1$; 2) esca al più una volta un numero $\leq2$; 3) esca la sequenza (pari, $1$, dispari, $1$ oppure $2$); 4) esca la sequenza ($1$, dispari, pari, pari) sapendo che il numero $1$ è uscito esattamente una volta.

**Svolgimento.** I lanci di dadi diversi non si influenzano: eventi legati a lanci diversi sono indipendenti.
1) $X=\#$ di volte che esce $1$, $X\sim BIN(n=4,p=\frac{1}{6})$. Conviene il complementare rispetto a $\sum_{k=1}^{4}p_{X}(k)$: $P(X\geq1)=1-P(X=0)=1-\left(\frac{5}{6}\right)^{4}=1-\frac{625}{1296}=\frac{671}{1296}$.
2) $Y=\#$ di volte che esce $1$ o $2$, $Y\sim BIN(4,\frac{1}{3})$. $P(Y\leq1)=\left(\frac{2}{3}\right)^{4}+4\cdot\frac{1}{3}\left(\frac{2}{3}\right)^{3}=\frac{16+32}{81}=\frac{48}{81}=\frac{16}{27}$.
3) Per indipendenza: $\frac{3}{6}\cdot\frac{1}{6}\cdot\frac{3}{6}\cdot\frac{2}{6}=\frac{1}{72}$.
4) $E=\{\text{esce }(1,\text{dispari},\text{pari},\text{pari})\}$ e $X$ come in 1): $$P(E|X=1)=\frac{P(E\cap\{X=1\})}{P(X=1)}=\frac{\frac{1}{6}\cdot\frac{2}{6}\cdot\frac{3}{6}\cdot\frac{3}{6}}{4\cdot\frac{1}{6}\left(\frac{5}{6}\right)^{3}}=\frac{2\cdot3\cdot3}{4\cdot5^{3}}=\frac{9}{250}$$(al numeratore l'evento è $(1,\,3\text{ o }5,\,\text{pari},\,\text{pari})$).

#### Esercizio: lanci ripetuti di una coppia di dadi (lezione 06, pp. 22-23)
Si considerano lanci ripetuti di una coppia di dadi. 1) Calcolare la probabilità che, su tre lanci, esca "somma $7$" al più $2$ volte. 2) Calcolare la probabilità che, su due lanci, esca ((pari, dispari), (dispari, pari)) sapendo che esce due volte "somma $11$".

**Svolgimento.**
1) $X=\#$ di volte che esce "somma $7$" su $3$ lanci. La somma $7$ si ottiene con $(1,6),(6,1),(2,5),(5,2),(3,4),(4,3)$, quindi $p=\frac{6}{36}=\frac{1}{6}$ e $X\sim BIN(3,\frac{1}{6})$. Allora $P(X\leq2)=1-P(X>2)=1-P(X=3)=1-\binom{3}{3}\left(\frac{1}{6}\right)^{3}=\frac{215}{216}$.
2) $E=\{\text{esce }((\text{pari},\text{dispari}),(\text{dispari},\text{pari}))\}$ e $Y=\#$ di volte che esce "somma $11$" su $2$ lanci (casi $(6,5),(5,6)$, $p=\frac{2}{36}=\frac{1}{18}$), $Y\sim BIN(2,\frac{1}{18})$. Allora $$P(E|Y=2)=\frac{P(\text{esce }((6,5),(5,6)))}{P(Y=2)}=\frac{\left(\frac{1}{6}\right)^{4}}{\left(\frac{1}{18}\right)^{2}}=\frac{18\cdot18}{36\cdot36}=\frac{1}{4}.$$

--- Fine lezione 06 ---

> [!question] Domanda tipica d'esame
> Quando si usa la binomiale e quando l'ipergeometrica? Quando l'una approssima l'altra?
> **Risposta.** Binomiale: $n$ prove indipendenti con la stessa probabilità di successo (es. estrazioni **con** reinserimento). Ipergeometrica: $n$ estrazioni **senza** reinserimento da $n_{1}$ oggetti di tipo 1 e $n_{2}$ di tipo 2, $p_{X}(k)=\binom{n_{1}}{k}\binom{n_{2}}{n-k}/\binom{n_{1}+n_{2}}{n}$. Se $n_{1}+n_{2}$ è molto più grande di $n$ la situazione è molto vicina a quella con reinserimento.
## Distribuzione multinomiale
Generalizzazione della binomiale a $r$ risultati possibili per prova, e coefficiente multinomiale.
#### Distribuzione multinomiale
Consideriamo $n$ prove indipendenti. Per ogni prova abbiamo $r$ risultati possibili: $$\begin{cases}
\text{risultato }1 & \text{con probabilità }p_{1}\geq 0 \\
\quad\vdots &  \\
\text{risultato }r & \text{con probabilità }p_{r}\geq 0
\end{cases}$$I valori $p_{1},\dots,p_{r}$ sono gli stessi per ogni prova; inoltre $p_{1}+\dots+p_{r}=1$.
In generale saremo interessati a calcolare probabilità di questo tipo: $$P\begin{pmatrix}
k_{1}\text{ volte risultato }1 \\
\vdots \\
k_{r}\text{ volte risultato }r
\end{pmatrix}\quad\quad\text{dove }\begin{cases}
k_{1},\dots,k_{r}\geq 0\text{ interi} \\
k_{1}+\dots+k_{r}=n
\end{cases}$$
##### Osservazione
Se si ha $r=2$ si recupera il caso della [[02 - Modelli discreti#Caso 1): distribuzione binomiale|binomiale]]; ad esempio risultato 1 $\longleftrightarrow$ successo ($p_{1}=p$) e risultato 2 $\longleftrightarrow$ fallimento ($p_{2}=1-p$), perché $p_{1}+p_{2}=1$.
Consideriamo la seguente sequenza di risultati: $$(\underset{k_{1}\text{ volte}}{\underbrace{R_{1},\dots,R_{1}}},\underset{k_{2}\text{ volte}}{\underbrace{R_{2},\dots,R_{2}}},\ \dots\ ,\underset{k_{r}\text{ volte}}{\underbrace{R_{r},\dots,R_{r}}})$$Allora, per indipendenza delle prove, questa sequenza ha probabilità $p_{1}^{k_{1}}\cdot\dots\cdot p_{r}^{k_{r}}$. Ovviamente si ottiene la stessa probabilità per qualsiasi altra sequenza con "$k_{1}$ volte $R_{1}$, …, $k_{r}$ volte $R_{r}$". Quindi la grandezza che vogliamo calcolare è $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
\vdots \\
k_{r}\text{ volte }R_{r}
\end{pmatrix}=\#\{\text{sequenze con "}k_{1}\text{ volte }R_{1},\dots,k_{r}\text{ volte }R_{r}\text{"}\}\cdot p_{1}^{k_{1}}\cdot\dots\cdot p_{r}^{k_{r}}$$e si può verificare che il numero di tali sequenze vale $$\begin{bmatrix}
\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}
\end{bmatrix}$$detto **coefficiente multinomiale** (per $r=2$ è un [[01 - Introduzione alla probabilità#Cenni di calcolo combinatorio|coefficiente binomiale]]).
##### Osservazione (risultati equiprobabili)
Se in ogni prova i risultati $R_{1},\dots,R_{r}$ sono equiprobabili, cioè $p_{1}=\dots=p_{r}=\frac{1}{r}$, si ha $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
\vdots \\
k_{r}\text{ volte }R_{r}
\end{pmatrix}=\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}\left( \frac{1}{r} \right)^{\overset{=n}{\overbrace{k_{1}+\dots+k_{r}}}}=\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}\left( \frac{1}{r} \right)^{n}$$È l'analogo di quanto visto per $X\sim BIN\left( n,p=\frac{1}{2} \right)$, dove si ha $p_{X}(k)=\binom{n}{k}\left( \frac{1}{2} \right)^{n}$.
##### Osservazione (si recupera la binomiale)
Per $r=2$, usando $p_{1}=1-p_{2}$ (perché $p_{1}+p_{2}=1$) e $k_{2}=n-k_{1}$ (perché $k_{1}+k_{2}=n$), si ha $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
k_{2}\text{ volte }R_{2}
\end{pmatrix}=\frac{n!}{k_{1}!(n-k_{1})!}p_{1}^{k_{1}}(1-p_{1})^{n-k_{1}}=\binom{n}{k_{1}}p_{1}^{k_{1}}(1-p_{1})^{n-k_{1}}\quad\quad(0\leq k_{1}\leq n)$$
#### Esempio: urna con tre colori (con e senza reinserimento)
Un'urna contiene 3 palline bianche, 3 rosse e 2 nere. Si estraggono 4 palline a caso, una alla volta e **con** reinserimento. Calcolare le probabilità dei seguenti eventi:
1) viene estratta la sequenza di colori (rossa, nera, nera, bianca);
2) vengono estratte esattamente 2 palline rosse e 1 nera in qualsiasi ordine;
3) vengono estratte esattamente 2 palline rosse in un qualsiasi ordine.

> [!info] Convenzione del corso
> Negli esercizi generalmente si sottintendono "esattamente" e "in qualsiasi ordine".

**Svolgimento.** Si hanno prove indipendenti perché le estrazioni sono **con** reinserimento. In ogni prova abbiamo 3 risultati con probabilità $p_{B}=\frac{3}{8}$, $p_{R}=\frac{3}{8}$, $p_{N}=\frac{2}{8}$ (uso notazioni diverse da $p_{1},p_{2},p_{3}$).
1) Con notazioni ovvie ($B_{i},R_{i},N_{i}$ = "esce bianca, rossa, nera all'$i$-esima estrazione"): $$P(R_{1}\cap N_{2}\cap N_{3}\cap B_{4})=P(R_{1})P(N_{2})P(N_{3})P(B_{4})=p_{B}p_{R}p_{N}^{2}=\frac{3}{8}\cdot \frac{3}{8}\left( \frac{2}{8} \right)^{2}=\frac{36}{4096}$$   **Osservazione.** L'espressione $p_{B}p_{R}p_{N}^{2}$ può essere vista come $p_{1}^{k_{1}}p_{2}^{k_{2}}p_{3}^{k_{3}}$ con $k_{1}=1,k_{2}=1,k_{3}=2$: abbiamo una parte della formula della multinomiale **senza** il coefficiente multinomiale (del resto è una sequenza fissata).
2) $$P(\text{"2R e 1N"})=P(\text{"1B, 2R, 1N"})=\underset{=\frac{4\cdot 3\cdot 2}{2}=12}{\underbrace{\frac{4!}{1!\,2!\,1!}}}\left( \frac{3}{8} \right)^{1}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{1}=\frac{648}{4096}$$(si sono estratte 4 palline: se 2 sono rosse e 1 nera, la quarta è necessariamente bianca).
3) Qui conviene contare solo "rosse" e "non rosse" (senza distinguere tra bianche e nere): il numero di rosse estratte è $\sim BIN\left( n=4,p=p_{R}=\frac{3}{8} \right)$, quindi $$P(\text{"2R"})=\binom{4}{2}\left( \frac{3}{8} \right)^{2}\left( 1-\frac{3}{8} \right)^{4-2}=6\left( \frac{3}{8} \right)^{2}\left( \frac{5}{8} \right)^{2}=\frac{1350}{4096}$$   **Osservazione.** Se volessimo tenere conto dei 3 colori si ha $$P(\text{"2R"})=P(\text{"2R, 1B, 1N"})+P(\text{"2R, 2B"})+P(\text{"2R, 2N"})=\frac{648+486+216}{4096}=\frac{1350}{4096}$$dove $P(\text{"2R, 2B"})=\frac{4!}{2!\,2!\,0!}\left( \frac{3}{8} \right)^{2}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{0}$ e $P(\text{"2R, 2N"})=\frac{4!}{0!\,2!\,2!}\left( \frac{3}{8} \right)^{0}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{2}$. Calcoli più complicati: metodo meno conveniente.
##### Lo stesso esercizio con estrazioni "senza reinserimento"
1) Qui non c'è indipendenza e si usa la [[01 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]: $$P(R_{1}\cap N_{2}\cap N_{3}\cap B_{4})=\underset{=\frac{3}{8}}{\underbrace{P(R_{1})}}\ \underset{=\frac{2}{7}}{\underbrace{P(N_{2}|R_{1})}}\ \underset{=\frac{1}{6}}{\underbrace{P(N_{3}|R_{1}\cap N_{2})}}\ \underset{=\frac{3}{5}}{\underbrace{P(B_{4}|R_{1}\cap N_{2}\cap N_{3})}}=\frac{3}{280}$$
2) Si usano le formule delle [[01 - Introduzione alla probabilità#Estensione al caso con più di 2 tipi|estrazioni in blocco con più di 2 tipi]]: $$P(\text{"2R e 1N"})=P(\text{"1B, 2R, 1N"})=\frac{\binom{3}{1}\binom{3}{2}\binom{2}{1}}{\binom{8}{4}}=\frac{3\cdot 3\cdot 2}{70}=\frac{18}{70}=\frac{9}{35}$$dove $\binom{8}{4}=\frac{8!}{4!\,4!}=\frac{8\cdot7\cdot6\cdot5}{4\cdot3\cdot2}=70$.
3) Contando "rosse" e "non rosse": $$P(\text{"2R"})=\frac{\binom{3}{2}\binom{5}{2}}{\binom{8}{4}}=\frac{3\cdot 10}{70}=\frac{30}{70}=\frac{3}{7}$$e in effetti, distinguendo i tre colori, $$P(\text{"2R"})=\underset{=\frac{18}{70}}{\underbrace{P(\text{"2R, 1B, 1N"})}}+\underset{=\frac{\binom{3}{2}\binom{3}{2}\binom{2}{0}}{\binom{8}{4}}=\frac{9}{70}}{\underbrace{P(\text{"2R, 2B"})}}+\underset{=\frac{\binom{3}{0}\binom{3}{2}\binom{2}{2}}{\binom{8}{4}}=\frac{3}{70}}{\underbrace{P(\text{"2R, 2N"})}}=\frac{18+9+3}{70}=\frac{30}{70}=\frac{3}{7}$$
#### Esempio: raggruppare i risultati (5 lanci di un dado)
Si lancia 5 volte un dado equo. Calcolare la probabilità che escano (esattamente) "2 volte $1$ e 1 volta $3$" (in un qualsiasi ordine).
**Risposta.** Abbiamo 5 prove indipendenti (i 5 lanci) e **3 risultati** in ogni prova: $$\begin{array}{lll}
\boxed{1} & \text{con prob. }p_{1}=\frac{1}{6} & (2\text{ volte}) \\
\boxed{3} & \text{con prob. }p_{2}=\frac{1}{6} & (1\text{ volta}) \\
\boxed{2}\ \boxed{4}\ \boxed{5}\ \boxed{6} & \text{con prob. }p_{3}=\frac{4}{6} & (2\text{ volte, dedotto})
\end{array}$$La probabilità richiesta è (applicazione diretta della formula della multinomiale) $$\frac{5!}{2!\,1!\,2!}\left( \frac{1}{6} \right)^{2}\left( \frac{1}{6} \right)^{1}\left( \frac{4}{6} \right)^{2}=\frac{5\cdot 4\cdot 3\cdot 2}{2\cdot 2}\cdot \frac{1}{6^{3}}\cdot \frac{4}{9}=\frac{5\cdot 4}{36\cdot 9}=\frac{5}{81}$$
##### Osservazione (modo alternativo, molto più complicato)
Pensiamo a 6 risultati possibili tutti con probabilità $\frac{1}{6}$. Abbiamo le due seguenti situazioni: $$\begin{array}{ll}
\text{per }k=2,4,5,6\ (4\text{ casi}) & P(\text{"2 volte }\boxed{1}\text{, 1 volta }\boxed{3}\text{, 2 volte }\boxed{k}\text{"})=\frac{5!}{2!\,1!\,2!\,0!\,0!\,0!}\left( \frac{1}{6} \right)^{5}=\frac{5}{1296} \\
\text{per }\{k,h\}\subset\{2,4,5,6\}\ \left( \binom{4}{2}=6\text{ casi} \right) & P(\text{"2 volte }\boxed{1}\text{, 1 volta }\boxed{3}\text{, 1 volta }\boxed{k}\text{, 1 volta }\boxed{h}\text{"})=\frac{5!}{2!\,1!\,1!\,1!\,0!\,0!}\left( \frac{1}{6} \right)^{5}=\frac{10}{1296}
\end{array}$$La probabilità richiesta è $$4\cdot \frac{5}{1296}+6\cdot \frac{10}{1296}=\frac{20+60}{1296}=\frac{80}{1296}=\frac{5}{81}$$che è lo stesso risultato visto prima.

> [!question] Domanda tipica d'esame
> Qual è la probabilità di ottenere $k_{1}$ volte il risultato $R_{1}$, $\dots$, $k_{r}$ volte il risultato $R_{r}$ in $n$ prove indipendenti? Che cosa si ottiene per $r=2$?
> **Risposta.** $\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}p_{1}^{k_{1}}\cdot\dots\cdot p_{r}^{k_{r}}$ (con $k_{1}+\dots+k_{r}=n$ e $p_{1}+\dots+p_{r}=1$), dove $\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}$ è il numero di sequenze (coefficiente multinomiale). Per $r=2$ si ritrova la binomiale $\binom{n}{k_{1}}p_{1}^{k_{1}}(1-p_{1})^{n-k_{1}}$.
## Distribuzioni uniforme discreta e di Poisson
Distribuzione uniforme discreta, distribuzione di Poisson e approssimazione poissoniana della [[02 - Modelli discreti#Caso 1): distribuzione binomiale|binomiale]].
#### Prossimi argomenti (altre distribuzioni discrete notevoli)
- **Distribuzione uniforme discreta**
- **Distribuzione di Poisson** (nome di un matematico francese)
- **[[02 - Modelli discreti#Distribuzione geometrica|Distribuzione geometrica]] e distribuzioni collegate** (nelle prossime lezioni)
##### Osservazione
Spesso saranno definite a partire dall'espressione della distribuzione (o della densità discreta) senza fare riferimento a $(\Omega,\mathcal{A},P)$.
#### Distribuzione uniforme discreta
Si tratta del caso in cui, per un insieme finito $E=\{x_{1},\dots,x_{n}\}\subset \mathbb{R}$ ($x_{1},\dots,x_{n}$ in minuscolo), si ha $$P(X\in B)=\frac{\#(B\cap E)}{\#E}=\frac{\#(B\cap E)}{n}\quad\quad\forall\ B\subset \mathbb{R}$$
##### Esempio
Si ha questa distribuzione con $E=\{1,2,3,4,5,6\}$ se $X$ è la v.a. che indica il numero che esce lanciando un dado equo.
#### Distribuzione di Poisson
Una v.a. $X$ ha **distribuzione di Poisson con parametro $\lambda>0$** (in qualche caso scriveremo $X\sim POISSON(\lambda)$) se si ha $$\begin{bmatrix}
p_{X}(k)=\frac{\lambda^{k}}{k!}e^{-\lambda}
\end{bmatrix}\quad\quad\forall\ k\in\{0,1,2,3,\dots\}$$
##### Osservazione
La definizione è ben posta se $\displaystyle\sum_{k=0}^{\infty}p_{X}(k)=1$. In effetti si ha $$\sum_{k=0}^{\infty}p_{X}(k)=\sum_{k=0}^{\infty}\frac{\lambda^{k}}{k!}e^{-\lambda}=e^{-\lambda}\underset{=e^{\lambda}\text{ per definizione}}{\underbrace{\sum_{k=0}^{\infty}\frac{\lambda^{k}}{k!}}}=e^{-\lambda}\cdot e^{\lambda}=1$$
##### Esempio (Poisson e condizionamento)
Sia $X\sim POISSON(\lambda=4)$.
1) Calcolare $P(X>2)$. Per eventi di questo tipo si deve passare alla probabilità dell'evento complementare: $$P(X>2)=1-P(X\leq 2)=1-\sum_{k=0}^{2}p_{X}(k)=1-\left( \frac{4^{0}}{0!}e^{-4}+\frac{4^{1}}{1!}e^{-4}+\frac{4^{2}}{2!}e^{-4} \right)=1-(1+4+8)e^{-4}=1-13e^{-4}$$
2) Calcolare $P(X=k|X\leq 2)$ per ogni $k\geq 0$ intero. Si ha $$P(X=k|X\leq 2)=\frac{P(\{X=k\}\cap\{X\leq 2\})}{P(X\leq 2)}=\begin{cases}
\frac{P(X=k)}{P(X\leq 2)} & \text{per }k\in\{0,1,2\}\quad(\text{perché }\{X=k\}\subset\{X\leq 2\}) \\
0 & \text{per }k\geq 3\quad(\text{perché }\{X=k\}\cap\{X\leq 2\}=\varnothing)
\end{cases}$$ed inoltre, per $k=0,1,2$, $$\frac{P(X=k)}{P(X\leq 2)}=\frac{\frac{4^{k}}{k!}\cancel{e^{-4}}}{\left( \frac{4^{0}}{0!}+\frac{4^{1}}{1!}+\frac{4^{2}}{2!} \right)\cancel{e^{-4}}}=\begin{cases}
1/13 & \text{per }k=0 \\
4/13 & \text{per }k=1 \\
8/13 & \text{per }k=2
\end{cases}$$   **Osservazione.** Gli eventi $\{\{X=k\}:k\geq 0\}$ costituiscono una partizione numerabile, quindi si deve avere $\displaystyle\sum_{k=0}^{\infty}P(X=k|X\leq 2)=1$. In effetti, trascurando gli addendi per $k\geq 3$ (tutti uguali a zero), $$\sum_{k=0}^{\infty}P(X=k|X\leq 2)=\sum_{k=0}^{2}P(X=k|X\leq 2)=\frac{1+4+8}{13}=1$$
#### Approssimazione della binomiale con la Poisson
Sia $\lambda>0$ e sia $n\geq\lambda$ intero; in questo modo $\frac{\lambda}{n}\in[0,1]$, e non è restrittivo perché poi siamo interessati a considerare un limite per $n\to+\infty$.
Prendiamo le densità di $X\sim BIN\left( n,p_{n}=\frac{\lambda}{n} \right)$. Allora, per $k\in\{0,1,\dots,n\}$, si ha $$\begin{array}{ll}
p_{X}(k) & =\binom{n}{k}\left( \frac{\lambda}{n} \right)^{k}\left( 1-\frac{\lambda}{n} \right)^{n-k}=\frac{n!}{k!(n-k)!}\cdot \frac{\lambda^{k}}{n^{k}}\left( 1-\frac{\lambda}{n} \right)^{n}\left( 1-\frac{\lambda}{n} \right)^{-k} \\
 & =\frac{\lambda^{k}}{k!}\underset{=\left( 1-\frac{1}{n} \right)\cdot\ \dots\ \cdot\left( 1-\frac{k-1}{n} \right)\ \longrightarrow\ 1}{\underbrace{\frac{n(n-1)\cdot\dots\cdot(n-k+1)}{n\cdot n\cdot\dots\cdot n}}}\underset{\longrightarrow\ e^{-\lambda}}{\underbrace{\left( 1-\frac{\lambda}{n} \right)^{n}}}\underset{\longrightarrow\ 1}{\underbrace{\left( 1-\frac{\lambda}{n} \right)^{-k}}}\quad\underset{n\to\infty}{\longrightarrow}\quad \frac{\lambda^{k}}{k!}e^{-\lambda}
\end{array}$$dove si è usato $\frac{n!}{(n-k)!}=n(n-1)\cdot\dots\cdot(n-k+1)$, e dove il limite finale è la densità discreta di una $POISSON(\lambda)$.
##### Osservazione
Per ogni $k\geq 0$ intero esiste $n$ tale che $n\geq k$, e quindi questo limite vale per ogni $k\geq 0$ intero.
Ricapitolando, per $X=X_{n}\sim BIN\left( n,p_{n}=\frac{\lambda}{n} \right)$ e $Z\sim POISSON(\lambda)$, si ha $$\begin{bmatrix}
\lim_{n\to\infty}p_{X_{n}}(k)=p_{Z}(k)\quad\quad\forall\ k\geq 0\text{ intero}
\end{bmatrix}$$(limite delle densità discrete).
##### Commento
Questo limite ha un interesse teorico che non approfondiremo. Al contrario c'è un **interesse pratico**: serve per calcolare valori approssimati di probabilità di eventi legati a v.a. con distribuzione binomiale "con $n$ grande e $p$ piccolo".
##### Esempio 1
Sia $X\sim BIN\left( n=1000,p=\frac{3}{500} \right)$; calcolare $P(X\geq 5)$.
(Si può pensare di fare riferimento a un'urna con 500 palline numerate da 1 a 500; si compiono 1000 estrazioni casuali **con** reinserimento e si vuole la probabilità di estrarre almeno 5 volte uno dei numeri 1, 2, 3.)
Il valore esatto è $$P(X\geq 5)=\sum_{k=5}^{1000}\binom{1000}{k}\left( \frac{3}{500} \right)^{k}\left( 1-\frac{3}{500} \right)^{1000-k}=1-\sum_{k=0}^{4}\binom{1000}{k}\left( \frac{3}{500} \right)^{k}\left( 1-\frac{3}{500} \right)^{1000-k}$$ma non è semplice calcolarne un valore approssimato. Facciamo quindi riferimento all'[[02 - Modelli discreti#Approssimazione della binomiale con la Poisson|approssimazione Poissoniana della binomiale]]: si ha $p_{X}(k)\approx p_{Z}(k)$ (per $k\geq 0$ intero) dove $Z\sim POISSON\left( \lambda=np=1000\cdot \frac{3}{500}=6 \right)$. Allora $$P(X\geq 5)=1-P(X\leq 4)=1-\sum_{k=0}^{4}P(X=k)\overset{\text{approx.}}{\approx}1-\sum_{k=0}^{4}\frac{6^{k}}{k!}e^{-6}=1-(1+6+18+36+54)e^{-6}=1-115e^{-6}$$
##### Esempio 2
Stessa urna dell'esempio precedente. Si estraggono 200 palline, una alla volta e **con** reinserimento. Calcolare la probabilità di estrarre al più 2 volte uno dei numeri 1, 2, 3, 4, 5, 6, 7.
La probabilità richiesta è $P(Y\leq 2)$ dove $Y\sim BIN\left( n=200,p=\frac{7}{500} \right)$, cioè $P(Y\leq 2)=\sum_{k=0}^{2}\binom{200}{k}\left( \frac{7}{500} \right)^{k}\left( 1-\frac{7}{500} \right)^{200-k}$.
Si ha $p_{Y}(k)\approx p_{Z}(k)$ (per ogni $k\geq 0$ intero) dove $Z\sim POISSON\left( \lambda=np=200\cdot \frac{7}{500}=\frac{14}{5} \right)$. Allora $$P(Y\leq 2)=\sum_{k=0}^{2}P(Y=k)\overset{\text{approx.}}{\approx}\sum_{k=0}^{2}\frac{(14/5)^{k}}{k!}e^{-14/5}=\left( 1+\frac{14}{5}+\frac{98}{25} \right)e^{-14/5}=\frac{193}{25}e^{-14/5}$$

--- Fine lezione 07 ---
#### Esercizio teorico: un numero aleatorio di lanci (Poisson "assottigliata")

> [!info] Esercizio segnalato dal prof come "teorico, un po' difficile"
> È un risultato notevole: se il **numero di prove** è a sua volta aleatorio con [[02 - Modelli discreti#Distribuzione di Poisson|distribuzione di Poisson]], il numero di successi resta di Poisson, con parametro riscalato da $p$. *(extra, non da slide)*

Sia $N\sim POISSON(\lambda)$ per qualche $\lambda>0$. Si lancia una moneta $N$ volte: per ogni lancio esce testa con probabilità $p\in(0,1)$ ed esce croce con probabilità $1-p$. Sia $X$ la v.a. che conta il numero di teste ottenute.
1) Trovare la densità discreta di $X$.
2) Calcolare $P(N=n|X=k)$ per $n\geq k\geq 0$.
##### Osservazioni preliminari
- Si escludono i casi $p=0$ e $p=1$ per evitare casi banali.
- Se si verifica l'evento $\{N=0\}$ (non si lanciano monete), allora si verifica $\{X=0\}$ (non escono teste).
##### Svolgimento
1) La v.a. $X$ assume valori interi non negativi. Conviene fare riferimento alla [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|formula delle probabilità totali]] con la partizione $\{\{N=n\}:n\geq 0\}$: $$\forall\ k\geq 0\text{ (intero)}\quad\quad p_{X}(k)=P(X=k)=\sum_{n=0}^{\infty}\underset{(*)}{\underbrace{P(X=k|N=n)}}\ \underset{=\frac{\lambda^{n}}{n!}e^{-\lambda}}{\underbrace{P(N=n)}}$$dove $$(*)=P(X=k|N=n)=\begin{cases}
0 & \text{se }k>n \\
\binom{n}{k}p^{k}(1-p)^{n-k} & \text{se }0\leq k\leq n
\end{cases}$$Quindi (la somma parte da $n=k$ perché gli addendi con $n<k$ sono nulli) $$\begin{array}{ll}
p_{X}(k) & =\displaystyle\sum_{n=k}^{\infty}\binom{n}{k}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{n!}e^{-\lambda}=e^{-\lambda}\sum_{n=k}^{\infty}\frac{\cancel{n!}}{k!(n-k)!}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{\cancel{n!}} \\
 & =e^{-\lambda}\frac{p^{k}}{k!}\displaystyle\sum_{n=k}^{\infty}\frac{(1-p)^{n-k}}{(n-k)!}\lambda^{\overset{}{n-k+k}}=e^{-\lambda}\frac{p^{k}}{k!}\lambda^{k}\sum_{n=k}^{\infty}\frac{\lambda^{n-k}(1-p)^{n-k}}{(n-k)!} \\
 & =e^{-\lambda}\frac{(\lambda p)^{k}}{k!}\underset{\text{cambio di indice }h=n-k}{\underbrace{\displaystyle\sum_{h=0}^{\infty}\frac{(\lambda(1-p))^{h}}{h!}}}=e^{-\lambda}\frac{(\lambda p)^{k}}{k!}e^{\lambda(1-p)}=\begin{bmatrix}
\frac{(\lambda p)^{k}}{k!}e^{-\lambda p}
\end{bmatrix}
\end{array}$$   **Osservazione.** Possiamo dire che $X\sim POISSON(\lambda p)$.
2) Per calcolare $P(N=n|X=k)$ usiamo la [[01 - Introduzione alla probabilità#Formula di Bayes|formula di Bayes]], perché conosciamo $P(X=k|N=n)$ (l'espressione $(*)$ vista sopra). Quindi, per $n\geq k$ intero, $$\begin{array}{ll}
P(N=n|X=k) & =\frac{P(X=k|N=n)P(N=n)}{P(X=k)}=\frac{\binom{n}{k}p^{k}(1-p)^{n-k}\frac{\lambda^{n}}{n!}e^{-\lambda}}{\frac{(\lambda p)^{k}}{k!}e^{-\lambda p}}=\frac{\frac{\cancel{n!}}{\cancel{k!}(n-k)!}\cancel{p^{k}}(1-p)^{n-k}\frac{\lambda^{n}}{\cancel{n!}}e^{-\lambda}}{\frac{\lambda^{k}\cancel{p^{k}}}{\cancel{k!}}e^{-\lambda p}} \\
 & =\frac{(1-p)^{n-k}}{(n-k)!}\lambda^{n-k}e^{-\lambda+\lambda p}=\frac{(\lambda(1-p))^{n-k}}{(n-k)!}e^{-\lambda(1-p)}
\end{array}$$   **Osservazione.** Possiamo dire che $$p(n)=\begin{cases}
\frac{(\lambda(1-p))^{n-k}}{(n-k)!}e^{-\lambda(1-p)} & \text{per }n\geq k\text{ intero} \\
0 & \text{altrimenti}
\end{cases}$$è la densità discreta di $Z+k$, dove $Z\sim POISSON(\lambda(1-p))$.

> [!question] Domanda tipica d'esame
> Come si approssima una binomiale con una Poisson?
> **Risposta.** Per $n$ grande e $p$ piccolo, $BIN(n,p)\approx POISSON(\lambda=np)$, perché $\lim_{n\to\infty}p_{X_{n}}(k)=\frac{\lambda^{k}}{k!}e^{-\lambda}$ per $p_{n}=\frac{\lambda}{n}$.
## Distribuzione geometrica
Distribuzione geometrica e geometrica traslata: densità, formula per la coda, mancanza di memoria.
#### Distribuzione geometrica (e distribuzione geometrica traslata)
Supponiamo di avere una **successione** di prove indipendenti, tutte con probabilità di successo $p\in(0,1]$. Siamo interessati all'istante del "1° successo" e, per questo motivo, escludiamo il caso $p=0$.
Consideriamo le seguenti v.a.: $$\begin{array}{ll}
X=\#\text{ fallimenti prima del "1° successo"} & (\text{assume valori in }\{0,1,2,\dots\}) \\
Y=\#\text{ prove per avere il "1° successo"} & (\text{assume valori in }\{1,2,3,\dots\})
\end{array}$$Queste v.a. sono legate tra loro perché $Y=X+1$ e $X=Y-1$.
##### Esempio
Se si ha la sequenza di risultati $F,F,S,\dots$ si verificano gli eventi $\{X=2\}$ e $\{Y=3\}$.
##### Terminologia
Si considera la seguente terminologia: $$\begin{array}{l}
X\text{ ha distribuzione geometrica di parametro }p \\
Y\text{ ha distribuzione geometrica traslata di parametro }p
\end{array}$$(in simboli scriveremo $X\sim Geo(p)$ e $Y\sim GeoTraslata(p)$).

> [!warning] Attenzione ai libri
> In alcuni libri la terminologia delle due distribuzioni è **scambiata**, e quella usata in questo corso è in minoranza. Comunque, per non confonderci, si potrebbe dire che:
> - $X$ ha distribuzione geometrica "che parte da zero" (di parametro $p$);
> - $Y$ ha distribuzione geometrica "che parte da uno" (di parametro $p$).
##### Osservazioni sui casi limite
- Abbiamo detto che si esclude il caso $p=0$: infatti non si avrebbe mai il "1° successo" perché si avrebbe **sempre fallimento**. Per aggirare il problema si potrebbe considerare questa situazione: $$\begin{array}{ll}
X:\Omega\to \mathbb{R}\cup\{\infty\}\ (\text{anziché }X:\Omega\to \mathbb{R}) & \text{e}\quad P(X=\infty)=1 \\
Y:\Omega\to \mathbb{R}\cup\{\infty\}\ (\text{anziché }Y:\Omega\to \mathbb{R}) & \text{e}\quad P(Y=\infty)=1
\end{array}$$
- Nel caso $p=1$ non ci sono problemi; però possiamo dire che abbiamo **sempre successo** e quindi $P(X=0)=1$ e $P(Y=1)=1$.
##### Calcolo delle densità discrete di $X$ e $Y$
- Per $k\geq 0$ intero si ha $$p_{X}(k)=P(\underset{k\text{ volte}}{\underbrace{F\dots F}}S)=\underset{k\text{ volte}}{\underbrace{(1-p)\cdot\dots\cdot(1-p)}}\cdot p=\begin{bmatrix}
(1-p)^{k}p
\end{bmatrix}$$(per indipendenza delle prove; vale banalmente anche per $k=0$).
- Per $h\geq 1$ intero si ha $$p_{Y}(h)=P(\underset{h-1\text{ volte}}{\underbrace{F\dots F}}S)=\underset{h-1\text{ volte}}{\underbrace{(1-p)\cdot\dots\cdot(1-p)}}\cdot p=\begin{bmatrix}
(1-p)^{h-1}p
\end{bmatrix}$$(vale banalmente anche per $h=1$), oppure, a partire da $p_{X}$, $$p_{Y}(h)=P(Y=h)=P(Y-1=h-1)=P(X=h-1)=p_{X}(h-1)=(1-p)^{h-1}p$$(essendo $h\geq 1$, si ha $h-1\geq 0$).
##### Osservazione (spiegazione del termine "geometrica")
Il rapporto tra due valori consecutivi della densità è costante, come nelle progressioni geometriche: $$\begin{array}{ll}
\text{per }k\geq 0\text{ intero} & \frac{p_{X}(k+1)}{p_{X}(k)}=\frac{(1-p)^{k+1}p}{(1-p)^{k}p}=1-p\quad\text{costante rispetto a }k \\
\text{per }h\geq 1\text{ intero} & \frac{p_{Y}(h+1)}{p_{Y}(h)}=\frac{(1-p)^{h+1-1}p}{(1-p)^{h-1}p}=1-p\quad\text{costante rispetto ad }h
\end{array}$$
#### Formula della serie geometrica
Per ogni $h\geq 0$ intero e per ogni $r$ tale che $|r|<1$ (cioè $-1<r<1$) si ha $$\begin{bmatrix}
\displaystyle\sum_{k=h}^{\infty}r^{k}=\frac{r^{h}}{1-r}
\end{bmatrix}$$(spesso la useremo per $0\leq r<1$).
##### Dimostrazione
Si ha $$\sum_{k=h}^{\infty}r^{k}=r^{h}+r^{h+1}+r^{h+2}+\dots\overset{(*)}{=}r^{h}(1+r+r^{2}+\dots)=\,?\quad\text{(si calcola la somma tra parentesi)}$$Inoltre si ha $1-r^{k}=(1-r)(1+r+r^{2}+\dots+r^{k-1})$ (basta fare i prodotti a secondo membro), da cui segue $$1+r+r^{2}+\dots+r^{k-1}=\frac{1-r^{k}}{1-r}\quad\underset{k\to\infty}{\longrightarrow}\quad \frac{1}{1-r}\quad\text{perché }|r|<1$$Allora, poiché la serie è il limite delle somme parziali, si ha $$\sum_{k=h}^{\infty}r^{k}\overset{(*)}{=}r^{h}\lim_{k\to\infty}(1+\dots+r^{k-1})=r^{h}\cdot \frac{1}{1-r}=\frac{r^{h}}{1-r}\qquad\Box$$
#### Formula per la "coda" di una v.a. geometrica (e per la traslata)
- Sia $X\sim Geo(p)$. Allora, per $j\geq 0$, si ha ([[02 - Modelli discreti#Formula della serie geometrica|formula della serie geometrica]] con $r=1-p$) $$P(X\geq j)=\sum_{k=j}^{\infty}p_{X}(k)=\sum_{k=j}^{\infty}(1-p)^{k}p=p\sum_{k=j}^{\infty}(1-p)^{k}=\cancel{p}\ \frac{(1-p)^{j}}{1-(1-p)}=\cancel{p}\ \frac{(1-p)^{j}}{\cancel{p}}=\begin{bmatrix}
(1-p)^{j}
\end{bmatrix}$$   **Osservazione.** In particolare (per $j=0$) $P(X\geq 0)=(1-p)^{0}=1$, in accordo con quanto ci si aspetta dalla teoria.
- Sia $Y\sim GeoTraslata(p)$. Allora, per $j\geq 1$, si ha $$P(Y\geq j)=\sum_{h=j}^{\infty}p_{Y}(h)=\sum_{h=j}^{\infty}(1-p)^{h-1}p=\frac{p}{1-p}\sum_{h=j}^{\infty}(1-p)^{h}=\frac{\cancel{p}}{1-p}\cdot \frac{(1-p)^{j}}{\cancel{p}}=\begin{bmatrix}
(1-p)^{j-1}
\end{bmatrix}$$   **Osservazione.** In particolare (per $j=1$) $P(Y\geq 1)=(1-p)^{1-1}=(1-p)^{0}=1$, in accordo con quanto ci si aspetta e con la teoria. *(extra, non da slide)* Il passaggio con $\frac{p}{1-p}$ presuppone $p<1$; per $p=1$ si ha direttamente $P(Y=1)=1$ e $P(Y\geq j)=0$ per $j\geq2$, in accordo con $(1-p)^{j-1}$ (con la regola $0^{0}=1$).
#### Proprietà della "mancanza di memoria"
Per ogni $k,h\geq 0$ interi si ha $$\begin{bmatrix}
P(X=k+h|X\geq h)=P(X=k)
\end{bmatrix}$$

> [!info] Commento
> Sapendo di aver avuto $h$ fallimenti, la probabilità di avere altri $k$ fallimenti prima del 1° successo è la stessa di avere $k$ fallimenti prima del 1° successo partendo dall'inizio (cioè **senza condizionare**).
##### Dimostrazione
$$P(X=k+h|X\geq h)=\frac{P(\{X=k+h\}\cap\{X\geq h\})}{P(X\geq h)}\underset{\{X=k+h\}\subset\{X\geq h\}}{=}\frac{P(X=k+h)}{P(X\geq h)}\overset{(\star)}{=}\frac{(1-p)^{k+h}p}{(1-p)^{h}}=(1-p)^{k}p=P(X=k)\qquad\Box$$dove in $(\star)$ si è usata al denominatore la formula per la coda vista prima.
##### Commenti
- La proprietà di mancanza di memoria mette in guardia dalle teorie sui **numeri ritardatari** per le estrazioni dei numeri al lotto.
- Si può dimostrare che, se $X$ è una v.a. a valori in $\{0,1,2,3,\dots\}$ e soddisfa la proprietà di mancanza di memoria, allora $X$ ha distribuzione geometrica (è quindi una **caratterizzazione**).
- Si può dare un enunciato analogo per la v.a. $Y$. Infatti, per $k,h\geq 1$ interi, si ha $$P(Y=k+h|Y>h)=\frac{P(\{Y=k+h\}\cap\{Y>h\})}{P(Y>h)}\underset{\{Y=k+h\}\subset\{Y>h\}}{=}\frac{P(Y=k+h)}{P(Y\geq h+1)}=\frac{(1-p)^{k+h-1}p}{(1-p)^{h+1-1}}=(1-p)^{k-1}p=P(Y=k)$$

> [!info] Esercizi conclusivi della lezione 08
> Le pp. 13-21 della lezione 08 contengono tre esercizi sulla geometrica traslata (lanci ripetuti di un dado equo; urna con 5 palline numerate; lanci ripetuti di due dadi equi), risolti con la formula per la coda e con la somma di serie geometriche su sottoinsiemi di indici (numeri pari, dispari, multipli di 3); sono svolti qui sotto.
#### Esercizi sulla geometrica traslata (lezione 08, pp. 13-21)
In ogni risposta si fa riferimento a una opportuna v.a. $Y\sim GeoTraslata(p)$.

**(a) Si lancia ripetutamente un dado equo.**
1) Probabilità di avere per la 1ª volta un numero $\leq2$ nei primi $3$ lanci: $Y\sim GeoTraslata(p=\frac{2}{6}=\frac{1}{3})$ e $P(Y\leq3)=\sum_{h=1}^{3}(1-p)^{h-1}p=\frac{1}{3}\left(1+\frac{2}{3}+\frac{4}{9}\right)=\frac{1}{3}\cdot\frac{9+6+4}{9}=\frac{19}{27}$. Osservazione: è anche $P(Z\geq1)=1-P(Z=0)$ con $Z\sim BIN(n=3,p=\frac{1}{3})$, cioè $1-\left(\frac{2}{3}\right)^{3}=\frac{19}{27}$.
2) Probabilità di avere per la 1ª volta il $5$ dopo il $3$° lancio (dal $4$° in poi): $Y\sim GeoTraslata(p=\frac{1}{6})$ e $P(Y\geq4)=\left(1-\frac{1}{6}\right)^{4-1}=\left(\frac{5}{6}\right)^{3}=\frac{125}{216}$ (formula per la coda; in alternativa $1-P(Y<4)=1-\sum_{k=1}^{3}P(Y=k)$).
3) Probabilità di avere per la 1ª volta un numero $\leq4$ a un lancio pari: $Y\sim GeoTraslata(p=\frac{4}{6}=\frac{2}{3})$ e $$P(Y\in\{2,4,6,\dots\})=\sum_{h=1}^{\infty}p_{Y}(2h)=\sum_{h\geq1}\left(\tfrac{1}{3}\right)^{2h-1}\tfrac{2}{3}=2\sum_{h\geq1}\left(\tfrac{1}{9}\right)^{h}=2\cdot\frac{1/9}{1-1/9}=\frac{1}{4}.$$

**(b) Urna con $5$ palline numerate da $1$ a $5$, estrazioni a caso con reinserimento.**
1) Probabilità di estrarre per la 1ª volta il $4$ alla 3ª estrazione: $Y\sim GeoTraslata(\frac{1}{5})$ e $P(Y=3)=\left(\frac{4}{5}\right)^{2}\frac{1}{5}=\frac{16}{125}$.
2) Probabilità di estrarre per la 1ª volta un numero dispari a un'estrazione pari dalla quarta in poi: $Y\sim GeoTraslata(\frac{3}{5})$ (dispari: $1,3,5$) e $$P(Y\in\{4,6,8,\dots\})=\sum_{h\geq2}\left(\tfrac{2}{5}\right)^{2h-1}\tfrac{3}{5}=\frac{3}{2}\sum_{h\geq2}\left(\tfrac{4}{25}\right)^{h}=\frac{3}{2}\cdot\frac{(4/25)^{2}}{1-4/25}=\frac{8}{175}.$$
3) Probabilità di estrarre due numeri dispari alle prime due estrazioni sapendo di avere estratto per la 1ª volta il $5$ alla 3ª estrazione: $E=\{\text{due dispari nelle prime due estrazioni}\}$ e $F=\{\text{esce }5\text{ per la 1ª volta alla 3ª estrazione}\}$; $$P(E|F)=\frac{P(E\cap F)}{P(F)}=\frac{P((1\text{ o }3,\,1\text{ o }3,\,5))}{\left(1-\frac{1}{5}\right)^{3-1}\frac{1}{5}}=\frac{\frac{2}{5}\cdot\frac{2}{5}\cdot\frac{1}{5}}{\left(\frac{4}{5}\right)^{2}\frac{1}{5}}=\frac{1}{4}.$$ Osservazione: rispetto a $P(\cdot|F)$, per le prime due estrazioni si hanno $4$ casi (dispari, dispari), (dispari, pari), (pari, dispari), (pari, pari), tutti di probabilità $\frac{1}{4}$ perché dispari $\leftrightarrow\{1,3\}$ e pari $\leftrightarrow\{2,4\}$.

**(c) Lanci ripetuti di due dadi equi.**
1) Probabilità di avere per la 1ª volta una coppia di numeri $\leq3$ a un lancio dispari, dal terzo in poi: le coppie sono $9$ su $36$, quindi $p=\frac{9}{36}=\frac{1}{4}$ (oppure, per indipendenza, $\frac{3}{6}\cdot\frac{3}{6}$), e $$P(Y\in\{3,5,7,\dots\})=\sum_{h\geq2}p_{Y}(2h-1)=\frac{1}{4}\sum_{h\geq2}\left(\tfrac{3}{4}\right)^{2h-2}=\frac{1}{4}\sum_{h\geq2}\left(\tfrac{9}{16}\right)^{h-1}=\frac{1}{4}\cdot\frac{9/16}{1-9/16}=\frac{9}{28}.$$
2) Probabilità che esca per la 1ª volta "somma $7$" al $k$-esimo lancio ($k\in\{1,2,3\}$) sapendo che questo accade in uno dei primi $3$ lanci: "somma $7$" si ottiene in $6$ casi su $36$, quindi $p=\frac{1}{6}$, e (poiché $\{Y=k\}\subset\{Y\leq3\}$) $$P(Y=k|Y\leq3)=\frac{P(Y=k)}{P(Y\leq3)}=\frac{(1-p)^{k-1}}{1+(1-p)+(1-p)^{2}}=\frac{(5/6)^{k-1}}{91/36},$$cioè $\frac{36}{91},\frac{30}{91},\frac{25}{91}$ per $k=1,2,3$ (somma $1$, in accordo con la teoria).
3) Probabilità che esca per la 1ª volta (dispari, dispari) a un lancio multiplo di $3$, sapendo che ciò accade a un lancio pari: le coppie sono $9$ su $36$, $p=\frac{1}{4}$. I multipli di $3$ pari sono i multipli di $6$: $$P(Y\in\{\text{multipli di }3\}|Y\in\{\text{pari}\})=\frac{P(Y\in\{6,12,\dots\})}{P(Y\in\{2,4,\dots\})}=(1-p)^{4}\,\frac{1-(1-p)^{2}}{1-(1-p)^{6}}=\frac{81}{256}\cdot\frac{7/16}{3367/4096}=\frac{567}{3367}$$(le due serie geometriche hanno ragione $(1-p)^{6}$ e $(1-p)^{2}$ rispettivamente).

--- Fine lezione 08 ---

> [!question] Domanda tipica d'esame
> Qual è la differenza tra geometrica e geometrica traslata?
> **Risposta.** $X$ = $\#$ fallimenti prima del 1° successo, con valori in $\{0,1,2,\dots\}$ e $p_{X}(k)=(1-p)^{k}p$; $Y=X+1$ = $\#$ prove per avere il 1° successo, con valori in $\{1,2,\dots\}$ e $p_{Y}(h)=(1-p)^{h-1}p$. In altri libri i nomi possono essere scambiati.

> [!question] Domanda tipica d'esame
> Enunciare la mancanza di memoria della geometrica e dimostrarla.
> **Risposta.** Per $k,h\geq0$ interi, $P(X=k+h|X\geq h)=P(X=k)$. Dimostrazione: $\{X=k+h\}\subset\{X\geq h\}$, quindi il quoziente è $\frac{(1-p)^{k+h}p}{(1-p)^{h}}=(1-p)^{k}p=P(X=k)$, usando $P(X\geq h)=(1-p)^{h}$ (formula per la coda).
## Distribuzione binomiale negativa
Generalizzazione della [[02 - Modelli discreti#Distribuzione geometrica|geometrica]] al "successo $r$-simo": densità discreta, versione traslata e recupero della geometrica per $r=1$.
### Impostazione
Vogliamo considerare una generalizzazione di quel che abbiamo visto per la [[02 - Modelli discreti#Distribuzione geometrica|geometrica (e la geometrica traslata)]] facendo riferimento al "successo $r$-simo", dove $r\geq 1$ è un intero fissato. Nel caso $r=1$ si dovrà recuperare quel che abbiamo visto, come caso particolare.
Quindi consideriamo ancora una successione di prove indipendenti con probabilità di successo $p\in(0,1]$ e di fallimento $1-p\in[0,1)$. Siamo interessati alle due seguenti v.a.: $$\begin{cases}
X=\#\text{ fallimenti prima di avere il successo }r\text{-simo} & (\text{è a valori in }\{0,1,2,\dots\}) \\
Y=\#\text{ prove per avere il successo }r\text{-simo} & (\text{è a valori in }\{r,r+1,r+2,\dots\})
\end{cases}$$In analogia a quanto visto in passato, si ha $X=Y-r$ e $Y=X+r$.
#### Esempio specifico con $r=4$
$$\underset{\substack{\uparrow \\ 1°\text{ succ.}}}{S}\ F\ F\ F\ \underset{\substack{\uparrow \\ 2°\text{ succ.}}}{S}\ \underset{\substack{\uparrow \\ 3°\text{ succ.}}}{S}\ F\ F\ F\ F\ \underset{\substack{\uparrow \\ 4°\text{ succ.}}}{S}$$Abbiamo 7 simboli "$F$" e 11 simboli in totale. Quindi si ha $X=7$ e $Y=11$ (questi valori sono in accordo con $X=Y-r$ e $Y=X+r$, dove $r=4$).
#### Terminologia
$$\begin{cases}
X\text{ ha distribuzione }\mathbf{\text{binomiale negativa}}\text{ con parametri }r\text{ e }p & (X\sim BIN\text{-}NEG(r,p)) \\
Y\text{ ha distribuzione }\mathbf{\text{binomiale negativa traslata}}\text{ con parametri }r\text{ e }p & (Y\sim BIN\text{-}NEG\text{-}traslata(r,p))
\end{cases}$$

> [!warning] Attenzione ai libri
> In altri libri le terminologie potrebbero essere scambiate (stessa avvertenza già vista per la [[02 - Modelli discreti#Terminologia|geometrica]]). Per evitare ambiguità possiamo distinguere i due casi con riferimento al fatto che **$X$ parte da zero** e **$Y$ parte da $r$**.
#### Osservazioni sui casi limite
- Il caso $p=0$ si esclude per i motivi visti nel caso della geometrica e della geometrica traslata (in generale si avrà certamente fallimento in ogni prova, e quindi non si arriverà mai al successo $r$-simo).
- Il caso $p=1$ è consentito ma è banale. Infatti si avrà certamente successo in ogni prova, e quindi $P(X=0)=1$ e $P(Y=r)=1$: $$\underset{r\text{ volte}}{\underbrace{S,\dots,S}}\quad\quad\begin{array}{l}
X=0\text{ perché non c'è nessuna }F \\
Y=r\text{ perché la "stringa" ha }r\text{ simboli in totale}
\end{array}$$
### Calcolo delle densità discrete di $X$ e $Y$
Iniziamo da $p_{X}(k)=P(X=k)$ per $k\geq 0$ intero.
Consideriamo la sequenza $(\underset{k\text{ volte}}{\underbrace{F,\dots,F}},\underset{r\text{ volte}}{\underbrace{S,\dots,S}})$; è un caso particolare dell'evento che ci interessa. Per indipendenza delle prove la probabilità di questa sequenza è $p^{r}(1-p)^{k}$.
Ci si convince che ogni altra sequenza con $k$ volte "$F$" e $r$ volte "$S$" ha la stessa probabilità. Quindi $$p_{X}(k)=\underset{b_{r,k}\text{ volte}}{\underbrace{p^{r}(1-p)^{k}+\dots+p^{r}(1-p)^{k}}}=b_{r,k}\,p^{r}(1-p)^{k}\quad\quad(\forall\ k\geq 0\text{ intero})$$dove $b_{r,k}=\#$ sequenze con $k$ volte "$F$" e $r$ volte "$S$", **e che finiscono con "$S$"**.

> [!info] Perché "che finiscono con S" *(extra, non da slide)*
> L'evento $\{X=k\}$ richiede che il successo $r$-simo cada esattamente all'ultima prova: se la sequenza finisse con $F$, il successo $r$-simo si sarebbe già verificato prima e i fallimenti contati non sarebbero quelli "prima del successo $r$-simo".
#### Calcolo di $b_{r,k}$
Consideriamo la seguente corrispondenza biunivoca: $$\left\{ \begin{array}{l}
\text{stringhe con }k\text{ volte "}F\text{" e }r\text{ volte "}S\text{"} \\
\text{che finiscono con "}S\text{"}
\end{array} \right\}\quad\longleftrightarrow\quad\left\{ \begin{array}{l}
\text{i sottoinsiemi di }\{1,\dots,k+r-1\}\text{ con }r-1 \\
\text{elementi, che indicano i posti delle "}S\text{"} \\
(\text{esclusa l'ultima "}S\text{"})
\end{array} \right\}$$Infatti una stringa di questo tipo si scrive come $$(\underbrace{-,-,\ \dots\ ,-}_{k+r-1\text{ simboli, di cui }k\text{ volte "}F\text{" e }r-1\text{ volte "}S\text{"}},S)$$e il secondo insieme ha $\binom{k+r-1}{r-1}$ elementi. Quindi $$b_{r,k}=\binom{k+r-1}{r-1}=\binom{k+r-1}{k}$$dove l'ultima uguaglianza vale per le proprietà dei coefficienti binomiali.
In conclusione $$\begin{bmatrix}
p_{X}(k)=\binom{k+r-1}{r-1}p^{r}(1-p)^{k}=\binom{k+r-1}{k}p^{r}(1-p)^{k}\quad\quad\forall\ k\geq 0\text{ intero}
\end{bmatrix}$$
#### Esempio della corrispondenza biunivoca
Prendiamo $r=3$ e $k=2$; allora $k+r-1=2+3-1=4$ e $r-1=2$: $$\begin{array}{lcl}
\text{sequenze con 2 volte "}F\text{" e 3 volte "}S\text{" che finiscono con "}S\text{"} &  & \text{sottoinsiemi} \\
(F,F,S,S,S) & \longleftrightarrow & \{3,4\} \\
(F,S,F,S,S) & \longleftrightarrow & \{2,4\} \\
(F,S,S,F,S) & \longleftrightarrow & \{2,3\} \\
(S,F,F,S,S) & \longleftrightarrow & \{1,4\} \\
(S,F,S,F,S) & \longleftrightarrow & \{1,3\} \\
(S,S,F,F,S) & \longleftrightarrow & \{1,2\}
\end{array}$$e in effetti si hanno 6 elementi, in accordo con $\binom{k+r-1}{r-1}=\binom{4}{2}=6$ e $\binom{k+r-1}{k}=\binom{4}{2}=6$.
#### Densità discreta di $Y$
La densità discreta di $Y$ si può ottenere con un ragionamento simile, oppure a partire dalla densità discreta di $X$ (questo è quello che facciamo di seguito). Per ogni $h\geq r$ intero (si osservi che $h-r\geq 0$ è intero) $$\begin{array}{ll}
p_{Y}(h)=P(Y=h)=P(X+r=h)=P(X=h-r)=p_{X}(h-r) & \overset{(*)}{=}\binom{(h-r)+r-1}{r-1}p^{r}(1-p)^{h-r}=\binom{h-1}{r-1}p^{r}(1-p)^{h-r} \\
 & \overset{(*)}{=}\binom{(h-r)+r-1}{h-r}p^{r}(1-p)^{h-r}=\binom{h-1}{h-r}p^{r}(1-p)^{h-r}
\end{array}$$dove in $(*)$ si è usata la formula ottenuta prima con $k=h-r$. Quindi $$\begin{bmatrix}
p_{Y}(h)=\binom{h-1}{r-1}p^{r}(1-p)^{h-r}=\binom{h-1}{h-r}p^{r}(1-p)^{h-r}\quad\quad\forall\ h\geq r\text{ intero}
\end{bmatrix}$$
##### Commento
Si può verificare che $\displaystyle\sum_{k=0}^{\infty}p_{X}(k)=1$ e $\displaystyle\sum_{h=r}^{\infty}p_{Y}(h)=1$. Il prof non dà dettagli su come si verificano.
### Caso $r=1$: recupero della geometrica e della geometrica traslata
$$\begin{array}{l|l}
\text{Per ogni }k\geq 0\text{ intero} & \text{Per }h\geq 1\text{ intero} \\
p_{X}(k)=\binom{k+1-1}{1-1}p^{1}(1-p)^{k}=(1-p)^{k}p & p_{Y}(h)=\binom{h-1}{1-1}p^{1}(1-p)^{h-1}=(1-p)^{h-1}p \\
\text{oppure} & \text{oppure} \\
p_{X}(k)=\binom{k+1-1}{k}p^{1}(1-p)^{k}=(1-p)^{k}p & p_{Y}(h)=\binom{h-1}{h-1}p^{1}(1-p)^{h-1}=(1-p)^{h-1}p
\end{array}$$Si ritrovano esattamente le densità di [[02 - Modelli discreti#Calcolo delle densità discrete di $X$ e $Y$|$Geo(p)$ e $GeoTraslata(p)$]], come ci si aspettava.

> [!info] Esercizi della lezione 09
> Le pp. 9-20 della lezione 09 contengono esercizi sulla binomiale negativa; sono svolti qui sotto.
#### Esempi svolti (lezione 09, pp. 9-20)
**Dado, terzo "4".** Si lancia ripetutamente un dado equo fino alla 3ª uscita del numero $4$. Si calcola la probabilità che escano 1) $5$ numeri diversi da $4$, 2) almeno $2$ numeri diversi da $4$. Le prove sono indipendenti con probabilità di successo (uscita del $4$) $p=\frac{1}{6}$; $X=\#$ fallimenti (numeri diversi da $4$) prima del 3° successo, quindi $X\sim BIN\text{-}NEG(r=3,p=\frac{1}{6})$ e si cercano $P(X=5)$ e $P(X\geq2)$.
1) $P(X=5)=p_{X}(5)=\binom{5+3-1}{3-1}\left(\frac{1}{6}\right)^{3}\left(1-\frac{1}{6}\right)^{5}=\binom{7}{2}\left(\frac{1}{6}\right)^{3}\left(\frac{5}{6}\right)^{5}=21\cdot\frac{5^{5}}{6^{8}}=\frac{65625}{1679616}=\frac{21875}{559872}\approx0{,}039$.
2) La serie $P(X\geq2)=\sum_{k=2}^{\infty}p_{X}(k)$ è difficile da trattare; il problema si aggira passando al complementare: $$P(X\geq2)=1-P(X\leq1)=1-\left(p_{X}(0)+p_{X}(1)\right)=1-\left[\left(\tfrac{1}{6}\right)^{3}+3\left(\tfrac{1}{6}\right)^{3}\tfrac{5}{6}\right]=1-\tfrac{7}{2}\left(\tfrac{1}{6}\right)^{3}=\frac{1275}{1296}.$$
*Controllo a mano:* $p_{X}(0)=P((4,4,4))=\left(\frac{1}{6}\right)^{3}$; $p_{X}(1)$ è la somma delle $3$ sequenze con un solo "non $4$" prima del terzo $4$ (che chiude la sequenza), ciascuna di probabilità $\frac{5}{6}\left(\frac{1}{6}\right)^{3}$, quindi $p_{X}(1)=3\left(\frac{1}{6}\right)^{3}\frac{5}{6}$.

> [!warning] Refuso nelle slide
> Alla p. 10 della lezione 09 il risultato di $P(X=5)$ è scritto $\frac{21875}{279936}$; ricalcolando, $21\cdot\frac{3125}{1679616}=\frac{65625}{1679616}=\frac{21875}{559872}$ (il denominatore corretto è $559872$). Qui si usa il valore ricalcolato.

**Moneta, 5ª testa al 7° lancio.** Si lancia ripetutamente una moneta equa; si vuole la probabilità di ottenere testa per la 5ª volta al 7° lancio. Sia $Y=\#$ lanci per avere la 5ª testa: $Y\sim BIN\text{-}NEG\text{-}traslata(r=5,p=\frac{1}{2})$ e $$P(Y=7)=p_{Y}(7)=\binom{7-1}{5-1}\left(\frac{1}{2}\right)^{5}\left(1-\frac{1}{2}\right)^{7-5}=\binom{6}{4}\left(\frac{1}{2}\right)^{7}=\frac{15}{128}.$$

**Urna con 2 bianche e 3 nere, con reinserimento.** Si estraggono palline a caso, una alla volta e con reinserimento. Si vuole la probabilità di ottenere la sequenza $(B,N,B)$ nelle prime tre estrazioni sapendo che la 2ª pallina nera viene estratta alla 4ª estrazione. Sia $E$ l'evento "esce $(B,N,B)$ nelle prime tre estrazioni" e $Y=\#$ estrazioni necessarie per avere per la 2ª volta una pallina nera ($Y\sim BIN\text{-}NEG\text{-}traslata(2,\frac{3}{5})$). Si chiede $P(E|Y=4)$: $$P(E|Y=4)=\frac{P(E\cap\{Y=4\})}{P(Y=4)}=\frac{P(\text{esce }(B,N,B,N))}{\binom{4-1}{2-1}\left(\frac{3}{5}\right)^{2}\left(1-\frac{3}{5}\right)^{4-2}}=\frac{\frac{2}{5}\cdot\frac{3}{5}\cdot\frac{2}{5}\cdot\frac{3}{5}}{3\left(\frac{3}{5}\right)^{2}\left(\frac{2}{5}\right)^{2}}=\frac{1}{3}.$$ *Commento.* Con $F=(B,B,N)$ e $G=(N,B,B)$ al posto di $E$ si trova lo stesso valore $P(F|Y=4)=P(G|Y=4)=\frac{1}{3}$; quindi $P(E|Y=4)+P(F|Y=4)+P(G|Y=4)=1$, e questo non sorprende perché $\{Y=4\}=(E\cap\{Y=4\})\cup(F\cap\{Y=4\})\cup(G\cap\{Y=4\})$ ed $E,F,G$ sono disgiunti a due a due.

**Esercizio teorico.** Si consideri una successione di prove indipendenti con probabilità di successo $p\in(0,1]$ e sia $Z_{j}=\#$ prove per avere il $j$-simo successo ($j=1,2$). Si calcola $P(Z_{1}=k|Z_{2}=n)$ per $n\geq2$ e $1\leq k\leq n-1$. Si ha $\{Z_{1}=k\}\cap\{Z_{2}=n\}=\{(F,\dots,F,S,F,\dots,F,S)\}$ con $S$ al $k$-simo e all'$n$-simo posto, di probabilità $(1-p)^{n-2}p^{2}$, e $Z_{2}\sim BIN\text{-}NEG\text{-}traslata(r=2,p)$ con $p_{Z_{2}}(n)=\binom{n-1}{2-1}p^{2}(1-p)^{n-2}$. Quindi $$P(Z_{1}=k|Z_{2}=n)=\frac{(1-p)^{n-2}p^{2}}{\binom{n-1}{1}p^{2}(1-p)^{n-2}}=\frac{1}{n-1}\quad\quad\text{per ogni }k\in\{1,\dots,n-1\}.$$ Commenti: (1) i valori $k\in\{1,\dots,n-1\}$ sono tutti equiprobabili (probabilità $\frac{1}{n-1}$) e il risultato non dipende da $p$: questo sembra non sorprendente per la proprietà di [[02 - Modelli discreti#Proprietà della "mancanza di memoria"|mancanza di memoria]]; (2) per $n=2$ è certo che il 1° successo sia alla 1ª prova, infatti $P(Z_{1}=1|Z_{2}=2)=1$; (3) se $p=1$ si deve avere $n=2$: per $n\geq3$ si ha $P(Z_{2}=n)=0$ e "non si può condizionare".

**Gioco dado + moneta** (sulle geometriche traslate e argomenti passati). Si lancia un dado equo e sia $X$ il numero ottenuto; poi si lancia $X$ volte una moneta equa e si vince il gioco se esce almeno una testa. Sia $V=\{\text{vince il gioco}\}$.
1) Per la formula delle probabilità totali, con $P(V|X=k)=1-\left(\frac{1}{2}\right)^{k}$ (complementare dell'uscita di $k$ croci) e $P(X=k)=\frac{1}{6}$: $$P(V)=\sum_{k=1}^{6}\left[1-\left(\tfrac{1}{2}\right)^{k}\right]\frac{1}{6}=\frac{1}{6}\left(6-\frac{32+16+8+4+2+1}{64}\right)=1-\frac{1}{6}\cdot\frac{63}{64}=1-\frac{21}{128}=\frac{107}{128}.$$
2) Per la formula di Bayes, $P(X=k|V)=\frac{P(V|X=k)P(X=k)}{P(V)}=\frac{\left(1-2^{-k}\right)\frac{1}{6}}{107/128}$, cioè $\frac{32}{321},\frac{48}{321},\frac{56}{321},\frac{60}{321},\frac{62}{321},\frac{63}{321}$ per $k=1,\dots,6$. La somma fa $1$ in accordo con la teoria, perché gli eventi $\{X=1\},\dots,\{X=6\}$ formano una partizione; inoltre $P(X=k|V)$ è crescente rispetto a $k$ perché $P(V|X=k)=1-\left(\frac{1}{2}\right)^{k}$ lo è.
3) Si ripete il gioco più volte e sia $Y\sim GeoTraslata(p=P(V))$ il numero di tentativi per la 1ª vittoria; si calcola la probabilità di vincere per la 1ª volta a un tentativo dispari: $$P(Y\in\{1,3,5,\dots\})=\sum_{h=1}^{\infty}p_{Y}(2h-1)=p\sum_{h=1}^{\infty}(1-p)^{2h-2}=p\sum_{j=0}^{\infty}\left[(1-p)^{2}\right]^{j}=\frac{p}{1-(1-p)^{2}}=\frac{1}{2-p}$$(con $j=h-1$; in alternativa si raccoglie $\frac{p}{(1-p)^{2}}\sum_{h\geq1}(1-p)^{2h}$, con lo stesso risultato). Con $p=\frac{107}{128}$ si ottiene $\frac{1}{2-\frac{107}{128}}=\frac{128}{149}$.

--- Fine parte sulla binomiale negativa (lezione 09, pp. 1-20) ---
La lezione 09 prosegue a p. 21 con un argomento nuovo: le [[02 - Modelli discreti#Variabili aleatorie multidimensionali discrete|variabili aleatorie multidimensionali]].
### Un legame tra binomiale negativa (traslata) e geometrica (traslata)

> [!info] Ripreso nella lezione 12 (pp. 9-10)
> Questa sezione arriva più avanti nel corso, dopo aver introdotto le [[02 - Modelli discreti#Trasformazioni e somme di variabili aleatorie discrete|somme di v.a. indipendenti]]; è raccolta qui perché tematicamente appartiene alla binomiale negativa.

Consideriamo lo schema della binomiale negativa (traslata), con $$\begin{array}{l}
X=\#\text{ fallimenti prima del successo }r\text{-simo} \\
Y=\#\text{ prove per avere il successo }r\text{-simo}
\end{array}$$Possiamo considerare le v.a. "a blocchi": $$\begin{array}{ll}
X_{i}=\#\text{ fallimenti tra il successo }(i-1)°\text{ e il successo }i° & i=1,\dots,r \\
Y_{i}=\#\text{ prove dopo il successo }(i-1)°\text{ per avere il successo }i° & i=1,\dots,r
\end{array}$$Quindi $$\begin{cases}
Y_{1}+\dots+Y_{r}=Y \\
Y_{i}=X_{i}+1\iff X_{i}=Y_{i}-1 \\
X_{1}+\dots+X_{r}=X
\end{cases}$$
#### Esempio ($r=4$)
$$F\ S\ F\ F\ F\ S\ S\ F\ F\ S\quad\quad\text{con }X=6\text{ e }Y=10$$Nel caso dell'esempio si ha $$\begin{array}{lll}
X_{1}=1,\ X_{2}=3,\ X_{3}=0,\ X_{4}=2 & \longrightarrow & \text{somma}=6\quad\text{ok} \\
Y_{1}=2,\ Y_{2}=4,\ Y_{3}=1,\ Y_{4}=3 & \longrightarrow & \text{somma}=10\quad\text{ok}
\end{array}$$
#### Il risultato
Allora: $$\begin{array}{ll}
Y=Y_{1}+\dots+Y_{r} & \text{e si può dimostrare che }Y_{1},\dots,Y_{r}\text{ sono indipendenti }GeoTraslata(p) \\
X=X_{1}+\dots+X_{r} & \text{e si può dimostrare che }X_{1},\dots,X_{r}\text{ sono indipendenti }Geo(p)
\end{array}$$

> [!quote] In sintesi *(extra, non da slide)*
> Una binomiale negativa (traslata) di parametri $r$ e $p$ è la **somma di $r$ geometriche (traslate) indipendenti** di parametro $p$. È coerente con la [[02 - Modelli discreti#Proprietà della "mancanza di memoria"|mancanza di memoria]]: dopo ogni successo il conteggio "riparte da zero".
#### Rivisitazione di un esercizio fatto in passato
Avevamo dimostrato (nell'esercizio teorico della lezione 09, riportato negli [[02 - Modelli discreti#Esempi svolti (lezione 09, pp. 9-20)|esempi svolti]]) che $$P(Y_{1}=k|Y_{1}+Y_{2}=n)=\frac{1}{n-1}\quad\quad\text{per }k\in\{1,\dots,n-1\}\text{ con }n\geq 2$$Ora recuperiamo questo risultato tenendo conto di quanto detto qui: essendo $Y_{1},Y_{2}$ indipendenti $GeoTraslata(p)$, la somma $Y_{1}+Y_{2}$ è una $BIN\text{-}NEG\text{-}traslata(r=2,p)$ e quindi $P(Y_{1}+Y_{2}=n)=\binom{n-1}{2-1}p^{2}(1-p)^{n-2}=(n-1)p^{2}(1-p)^{n-2}$. Allora $$\begin{array}{ll}
P(Y_{1}=k|Y_{1}+Y_{2}=n) & =\frac{P(\{Y_{1}=k\}\cap\{Y_{1}+Y_{2}=n\})}{P(Y_{1}+Y_{2}=n)}=\frac{P(\{Y_{1}=k\}\cap\{Y_{2}=n-k\})}{\binom{n-1}{2-1}p^{2}(1-p)^{n-2}}\underset{\text{indip.}}{=}\frac{P(Y_{1}=k)P(Y_{2}=n-k)}{(n-1)p^{2}(1-p)^{n-2}} \\
 & =\frac{(1-p)^{k-1}\cancel{p}(1-p)^{n-k-1}\cancel{p}}{(n-1)\cancel{p^{2}}(1-p)^{n-2}}=\frac{\cancel{(1-p)^{n-2}}}{(n-1)\cancel{(1-p)^{n-2}}}=\frac{1}{n-1}
\end{array}$$in accordo con quanto già dimostrato.

> [!question] Domanda tipica d'esame
> Come è definita la binomiale negativa (traslata) e qual è la sua densità? Come si lega alla geometrica?
> **Risposta.** In una successione di prove indipendenti con probabilità di successo $p\in(0,1]$, $X=\#$ fallimenti prima del successo $r$-simo è $BIN\text{-}NEG(r,p)$ con $p_{X}(k)=\binom{k+r-1}{r-1}p^{r}(1-p)^{k}$ per $k\geq0$; $Y=X+r=\#$ prove per avere il successo $r$-simo è $BIN\text{-}NEG\text{-}traslata(r,p)$ con $p_{Y}(h)=\binom{h-1}{r-1}p^{r}(1-p)^{h-r}$ per $h\geq r$. Per $r=1$ si ritrovano $Geo(p)$ e $GeoTraslata(p)$; in generale $Y$ è la somma di $r$ geometriche traslate indipendenti di parametro $p$.
## Variabili aleatorie multidimensionali discrete
Densità congiunta e densità marginali, legame tra le due, e indipendenza tra variabili aleatorie discrete.

> [!info] Perimetro del corso
> Per le v.a. multidimensionali **si tratta solo il caso discreto**.
### Definizione
Date $m$ v.a. discrete (come quelle viste finora) $X_{1},\dots,X_{m}$ definite su uno stesso spazio di probabilità, quindi $X_{i}:\Omega\to \mathbb{R}$ con opportune proprietà, vogliamo considerare la funzione $\underline{X}=(X_{1},\dots,X_{m}):\Omega\to \mathbb{R}^{m}$ così definita: $$\underline{X}(\omega)=(X_{1}(\omega),\dots,X_{m}(\omega))\quad\quad\forall\ \omega\in\Omega$$L'insieme dei valori assunti dalla v.a. $\underline{X}$, che indicheremo con $S_{\underline{X}}$, soddisfa la seguente condizione: $$S_{\underline{X}}\subset\underset{\text{prodotto cartesiano di insiemi finiti o numerabili}}{\underbrace{S_{X_{1}}\times\dots\times S_{X_{m}}}}$$Quindi l'insieme $S_{\underline{X}}$ è finito o numerabile, e la funzione $\underline{X}:\Omega\to \mathbb{R}^{m}$ è una v.a. **multidimensionale** (anzi **$m$-dimensionale**) **discreta**.
#### Esempio
Si lanciano due dadi e sia $\Omega=\{1,\dots,6\}\times\{1,\dots,6\}$. (Se i dadi sono equi si ha $P(A)=\frac{\#A}{36}$ per ogni $A\subset \Omega$, cioè uno [[01 - Introduzione alla probabilità#Spazio di Probabilità Uniforme Discreto|spazio di probabilità uniforme discreto]].)
Vogliamo considerare la v.a. di dimensione 2 che indica la somma e il prodotto dei due numeri ottenuti. Allora avremo $$\underline{X}(\omega)=\underline{X}(\omega_{1},\omega_{2})=(\underset{=X_{1}(\omega_{1},\omega_{2})}{\underbrace{\omega_{1}+\omega_{2}}},\underset{=X_{2}(\omega_{1},\omega_{2})}{\underbrace{\omega_{1}\cdot \omega_{2}}})\quad\quad\forall\ \omega=(\omega_{1},\omega_{2})\in\Omega$$
#### Osservazioni
- Spesso, quando tratteremo le v.a. discrete multidimensionali, avremo a che fare con **sommatorie con più indici**.
- Nel caso continuo (dove in generale avremo integrali al posto di sommatorie) si dovrebbe fare riferimento agli **integrali multipli**; per questo motivo tratteremo il caso multidimensionale solo nel discreto, mentre tratteremo solo le v.a. continue unidimensionali.
  (In realtà non sempre servono integrali multipli, ma nei "casi facili" è così.)
### Densità congiunta e densità marginali
A questo punto possiamo definire la densità discreta di $\underline{X}$ come si fa per le v.a. discrete unidimensionali: $$p_{\underline{X}}:\mathbb{R}^{m}\to[0,1]\quad\quad p_{\underline{X}}(\underline{x})=P(\underline{X}=\underline{x})\quad\quad\text{dove }\underline{x}=(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$$(si noti l'uso delle **lettere minuscole** per i valori).
La densità discreta di $\underline{X}=(X_{1},\dots,X_{m})$ è detta **congiunta** perché descrive congiuntamente il comportamento delle v.a. $X_{1},\dots,X_{m}$. Per le v.a. $X_{1},\dots,X_{m}$, e per le loro densità discrete, si usa il termine **marginali**.
#### Proprietà della densità congiunta
Per la densità congiunta $p_{\underline{X}}$ si mantengono alcune proprietà viste per il caso unidimensionale:
- se $\underline{x}\not\in S_{\underline{X}}$, allora $p_{\underline{X}}(\underline{x})=0$;
- per ogni $A\subset \mathbb{R}^{m}$ $$P(\underline{X}\in A)=\sum_{\underline{x}\in A\cap S_{\underline{X}}}p_{\underline{X}}(\underline{x})$$da cui (ponendo $A=\mathbb{R}^{m}$) si ottiene $$\begin{bmatrix}
\sum_{\underline{x}\in S_{\underline{X}}}p_{\underline{X}}(\underline{x})=1
\end{bmatrix}$$   **Osservazione.** Ovviamente qui la sommatoria può essere ristretta ai vettori $\underline{x}$ per cui $p_{\underline{X}}(\underline{x})>0$.
#### Legame tra congiunta e marginali
Note le congiunte, si possono ricavare le marginali. Al contrario, **note le marginali non è possibile ricavare la congiunta**.
Questo per certi versi non sorprende: le marginali descrivono il comportamento di $X_{1},\dots,X_{m}$ prese *separatamente*; la congiunta descrive il comportamento *congiunto* delle v.a. $X_{1},\dots,X_{m}$ e contiene più informazioni delle marginali.
--- Fine lezione 09 ---
#### Proposizione (le marginali si ottengono dalla congiunta)
Sia $\underline{X}=(X_{1},\dots,X_{m})$ una v.a. $m$-dimensionale con densità congiunta $p_{\underline{X}}$ e con densità marginali $p_{X_{1}},\dots,p_{X_{m}}$. Allora, per ogni $i\in\{1,\dots,m\}$, si ha $$\begin{bmatrix}
p_{X_{i}}(x_{i})=\sum_{\underline{x}\in S_{\underline{X}}}p_{\underline{X}}(\underline{x})
\end{bmatrix}$$dove, quando si scrive $\underline{x}$, si pensa a $\underline{x}=(x_{1},\dots,x_{m})$ **la cui coordinata $i$-sima coincide con il valore $x_{i}$ fissato**.
Quindi, note le congiunte, abbiamo una formula che consente di ottenere ciascuna delle $m$ marginali.
##### Dimostrazione
Per ogni $i\in\{1,\dots,m\}$ si ha $$\begin{array}{ll}
p_{X_{i}}(x_{i})=P(X_{i}=x_{i}) & =P\left( \bigcup_{\underline{x}\in S_{\underline{X}}}\{\underline{X}=\underline{x}\} \right)=P\left( \bigcup_{\underline{x}\in S_{\underline{X}}}(\{X_{1}=x_{1}\}\cap\dots\cap\{X_{m}=x_{m}\}) \right) \\
 & \overset{(\star)}{=}\displaystyle\sum_{\underline{x}\in S_{\underline{X}}}P(\{X_{1}=x_{1}\}\cap\dots\cap\{X_{m}=x_{m}\})=\sum_{\underline{x}\in S_{\underline{X}}}P(\underline{X}=\underline{x})=\sum_{\underline{x}\in S_{\underline{X}}}p_{\underline{X}}(\underline{x})
\end{array}$$dove in $(\star)$ si è usato che l'insieme $S_{\underline{X}}$ è al più numerabile, e quindi si ha un'unione al più numerabile di eventi disgiunti a due a due (si applica la [[01 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|$\sigma$-additività]]) $\Box$
#### Esempio: due congiunte diverse con le stesse marginali
Presentiamo due diverse densità congiunte $m$-dimensionali, in particolare con $m=2$, per cui si ha $$\begin{cases}
\text{"}p_{X_{1}}\text{ della 1}^{\text{a}}\text{ congiunta" coincidente con "}p_{X_{1}}\text{ della 2}^{\text{a}}\text{ congiunta"} \\
\text{"}p_{X_{2}}\text{ della 1}^{\text{a}}\text{ congiunta" coincidente con "}p_{X_{2}}\text{ della 2}^{\text{a}}\text{ congiunta"}
\end{cases}$$In entrambi i casi avremo $m=2$ e $$S_{\underline{X}}=\{0,1\}\times\{0,1\}=\{(0,0),(0,1),(1,0),(1,1)\}$$
**Congiunta n. 1:** $p_{\underline{X}}(0,0)=p_{\underline{X}}(0,1)=p_{\underline{X}}(1,0)=p_{\underline{X}}(1,1)=\frac{1}{4}$ (è ben posta). Le marginali sono $$\begin{array}{l|l}
p_{X_{1}}(0)=p_{\underline{X}}(0,0)+p_{\underline{X}}(0,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} & p_{X_{2}}(0)=p_{\underline{X}}(0,0)+p_{\underline{X}}(1,0)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} \\
p_{X_{1}}(1)=p_{\underline{X}}(1,0)+p_{\underline{X}}(1,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} & p_{X_{2}}(1)=p_{\underline{X}}(0,1)+p_{\underline{X}}(1,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2}
\end{array}$$Quindi le marginali di $X_{1}$ e $X_{2}$ coincidono, cioè $p_{X_{1}}=p_{X_{2}}$; inoltre in entrambi i casi si ha la [[02 - Modelli discreti#Distribuzione Bernoulliana|distribuzione bernoulliana]] di parametro $p=\frac{1}{2}$.
**Congiunta n. 2:** $p_{\underline{X}}(0,0)=p_{\underline{X}}(1,1)=\frac{1}{3}$ e $p_{\underline{X}}(1,0)=p_{\underline{X}}(0,1)=\frac{1}{6}$ (è ben posta). Le marginali sono $$\begin{array}{l|l}
p_{X_{1}}(0)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} & p_{X_{2}}(0)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} \\
p_{X_{1}}(1)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2} & p_{X_{2}}(1)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2}
\end{array}$$Quindi abbiamo le stesse marginali che avevamo ottenuto con la congiunta precedente.

> [!quote] Conclusione
> Abbiamo ottenuto ciò che volevamo: **due scelte diverse per $p_{\underline{X}}$** per cui "$p_{X_{i}}$ della 1ª congiunta" coincide con "$p_{X_{i}}$ della 2ª congiunta" per ogni $i=1,\dots,m$. È la prova che dalle marginali non si può risalire alla congiunta.
> (Poi nel caso specifico, dove $m=2$, per entrambe le congiunte si ha anche $p_{X_{1}}=p_{X_{2}}$; questo non era richiesto.)
### Indipendenza tra variabili aleatorie
#### Definizione
Una famiglia finita di v.a. **discrete** $X_{1},\dots,X_{m}$, con $m\geq 2$, è una famiglia di **v.a. indipendenti** se $$\forall\ A_{1},\dots,A_{m}\subset \mathbb{R}\quad\quad P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\})=P(X_{1}\in A_{1})\cdot\dots\cdot P(X_{m}\in A_{m})$$Una famiglia **infinita** di v.a. discrete è una famiglia di v.a. indipendenti se questo accade per qualsiasi sottofamiglia finita.
#### Proposizione (gli eventi associati sono indipendenti)
Sia $X_{1},\dots,X_{m}$, con $m\geq 2$, una famiglia finita di v.a. indipendenti. Allora, per ogni $A_{1},\dots,A_{m}\subset \mathbb{R}$, gli eventi $\{X_{1}\in A_{1}\},\dots,\{X_{m}\in A_{m}\}$ sono [[01 - Introduzione alla probabilità#Indipendenza tra Eventi|eventi indipendenti]].
##### Dimostrazione
Per ogni $\{i_{1},\dots,i_{k}\}\subset\{1,\dots,m\}$ con $k\geq 2$ si deve avere $$P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\})=P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})$$Si vede subito che questo è vero se $k=m$, e quindi $\{i_{1},\dots,i_{k}\}=\{1,\dots,m\}$. Vediamo cosa succede nel caso in cui $2\leq k\leq m-1$.
Sia $\{j_{1},\dots,j_{m-k}\}$ il complementare di $\{i_{1},\dots,i_{k}\}$; quindi $$\{i_{1},\dots,i_{k}\}\cup\{j_{1},\dots,j_{m-k}\}=\{1,\dots,m\}\quad\quad(\text{con intersezione vuota})$$Allora, completando con gli eventi certi $\{X_{j}\in \mathbb{R}\}=\Omega$, $$\begin{array}{ll}
P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\}) & =P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\}\cap\overset{=\Omega}{\overbrace{\{X_{j_{1}}\in \mathbb{R}\}}}\cap\dots\cap\overset{=\Omega}{\overbrace{\{X_{j_{m-k}}\in \mathbb{R}\}}}) \\
 & \overset{(\star)}{=}P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})\underset{=P(\Omega)=1}{\underbrace{P(X_{j_{1}}\in \mathbb{R})}}\cdot\dots\cdot\underset{=P(\Omega)=1}{\underbrace{P(X_{j_{m-k}}\in \mathbb{R})}} \\
 & =P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})
\end{array}$$dove in $(\star)$ si è usata l'indipendenza delle v.a.; e questa è l'uguaglianza desiderata $\Box$
#### Proposizione (condizione necessaria e sufficiente)
Sia $\underline{X}=(X_{1},\dots,X_{m})$ una v.a. $m$-dimensionale, con $m\geq 2$. Allora $$X_{1},\dots,X_{m}\text{ è una famiglia di v.a. discrete indipendenti}\iff\begin{bmatrix}
p_{\underline{X}}(x_{1},\dots,x_{m})=p_{X_{1}}(x_{1})\cdot\dots\cdot p_{X_{m}}(x_{m})
\end{bmatrix}$$per ogni $(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$.

> [!quote] Commento
> **La congiunta è il prodotto delle marginali.**
##### Dimostrazione
$(\implies)$ Consideriamo la definizione di famiglia di v.a. indipendenti scegliendo, per ogni $(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$, gli insiemi $A_{1}=\{x_{1}\},\dots,A_{m}=\{x_{m}\}$. Allora, poiché si ha $$\underset{=P(\underline{X}=\underline{x})=p_{\underline{X}}(\underline{x})}{\underbrace{P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\})}}=\underset{=P(X_{1}=x_{1})\cdot\dots\cdot P(X_{m}=x_{m})=p_{X_{1}}(x_{1})\cdot\dots\cdot p_{X_{m}}(x_{m})}{\underbrace{P(X_{1}\in A_{1})\cdot\dots\cdot P(X_{m}\in A_{m})}}$$abbiamo quanto desideravamo.
$(\impliedby)$ Supponiamo che la densità congiunta sia uguale al prodotto delle densità marginali. Allora, per ogni $A_{1},\dots,A_{m}\subset \mathbb{R}$, $$\begin{array}{ll}
P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\}) & =P((X_{1},\dots,X_{m})\in A_{1}\times\dots\times A_{m})=\displaystyle\sum_{\underline{x}\in(A_{1}\times\dots\times A_{m})\cap S_{\underline{X}}}p_{\underline{X}}(\underline{x}) \\
 & =\displaystyle\sum_{\underline{x}\in(A_{1}\times\dots\times A_{m})\cap S_{\underline{X}}}p_{X_{1}}(x_{1})\cdot\dots\cdot p_{X_{m}}(x_{m}) \\
 & \overset{(\star)}{=}\underset{=P(X_{1}\in A_{1})}{\underbrace{\displaystyle\sum_{x_{1}\in A_{1}\cap S_{X_{1}}}p_{X_{1}}(x_{1})}}\cdot\ \dots\ \cdot\underset{=P(X_{m}\in A_{m})}{\underbrace{\displaystyle\sum_{x_{m}\in A_{m}\cap S_{X_{m}}}p_{X_{m}}(x_{m})}}
\end{array}$$dove in $(\star)$ si è usato che, sotto queste ipotesi, si può supporre $S_{\underline{X}}=S_{X_{1}}\times\dots\times S_{X_{m}}$ (e quindi la somma sul prodotto cartesiano si fattorizza). Questa è l'uguaglianza che volevamo per dire che $X_{1},\dots,X_{m}$ è una famiglia di v.a. discrete indipendenti $\Box$

> [!warning] Come si usa in pratica
> Per stabilire se c'è indipendenza si verifica la condizione $p_{\underline{X}}(x_{1},x_{2})=p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})$ solo sui punti del supporto: in tutti gli altri casi si ha $0=0\cdot 0$ e la condizione è automaticamente verificata.
> In generale, **se c'è una sola coppia per cui non vale l'uguaglianza richiesta, allora non c'è indipendenza**.
#### Commento generale (criterio del prodotto cartesiano)
Se l'insieme $\{(x_{1},\dots,x_{m}):p_{\underline{X}}(x_{1},\dots,x_{m})>0\}$ **non** è un prodotto cartesiano, allora **non** c'è indipendenza.
In generale non vale il viceversa: cioè è possibile costruire esempi in cui non c'è indipendenza ma quell'insieme è un prodotto cartesiano.

> [!info] Perché il criterio funziona *(extra, non da slide)*
> Se manca un "punto" per completare il prodotto cartesiano, in quel punto si ha $p_{\underline{X}}(\underline{x})=0$ mentre il prodotto delle marginali è $\neq 0$ (perché ciascun fattore è $\neq 0$): la condizione di indipendenza è quindi violata proprio lì.
##### Esempio (il viceversa non vale)
Presi $a,b\in \mathbb{R}$ con $a<b$, sia $$p_{\underline{X}}(a,a)=p_{\underline{X}}(b,b)=\frac{1}{3}\quad\quad p_{\underline{X}}(a,b)=p_{\underline{X}}(b,a)=\frac{1}{6}$$(è ben posta). Le marginali di $X_{1}$ e $X_{2}$ sono $$\begin{array}{l|l}
p_{X_{1}}(a)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} & p_{X_{2}}(a)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} \\
p_{X_{1}}(b)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2} & p_{X_{2}}(b)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2}
\end{array}$$Qui l'insieme dove la congiunta è positiva **è** il prodotto cartesiano $\{a,b\}\times\{a,b\}$; tuttavia osserviamo che $$\underset{=1/3}{\underbrace{p_{\underline{X}}(a,a)}}\neq\underset{=\frac{1}{2}\cdot \frac{1}{2}=1/4}{\underbrace{p_{X_{1}}(a)p_{X_{2}}(a)}}$$Quindi $X_{1}$ e $X_{2}$ **non** sono indipendenti.

> [!info] Esercizi della lezione 10
> Le pp. 10-13 e 16-23 della lezione 10 contengono esercizi su densità congiunte discrete, marginali e verifica dell'indipendenza (fra cui l'urna con le palline $0,1,1,2$ e una congiunta di tipo geometrico); sono svolti qui sotto.
#### Esempi svolti (lezione 10, pp. 10-23)
**Indipendenza con supporto prodotto cartesiano.** $p_{\underline{X}}(1,j)=\frac{1}{12}$ e $p_{\underline{X}}(2,j)=\frac{1}{4}$ per $j=1,2,3$ (è ben posta). Marginali: $p_{X_{1}}(1)=\frac{1}{4}$, $p_{X_{1}}(2)=\frac{3}{4}$; $p_{X_{2}}(j)=\frac{1}{3}$ per $j=1,2,3$ (somme $=1$). Per l'indipendenza basta verificare la condizione sui $6$ punti di $\{1,2\}\times\{1,2,3\}$ (negli altri casi si ha $0=0\cdot 0$): $\frac{1}{12}=\frac{1}{4}\cdot\frac{1}{3}$ e $\frac{1}{4}=\frac{3}{4}\cdot\frac{1}{3}$. Quindi $X_{1},X_{2}$ sono indipendenti.

**Supporto non prodotto cartesiano.** $p_{\underline{X}}(1,1)=\frac{10}{29}$, $p_{\underline{X}}(1,2)=\frac{2}{29}$, $p_{\underline{X}}(1,3)=\frac{7}{29}$, $p_{\underline{X}}(2,1)=p_{\underline{X}}(2,2)=\frac{5}{29}$ (è ben posta). Marginali: $p_{X_{1}}(1)=\frac{19}{29}$, $p_{X_{1}}(2)=\frac{10}{29}$; $p_{X_{2}}(1)=\frac{15}{29}$, $p_{X_{2}}(2)=\frac{7}{29}$, $p_{X_{2}}(3)=\frac{7}{29}$. I $5$ punti non formano un prodotto cartesiano (aggiungendo il "punto mancante" $(2,3)$ si otterrebbe $\{1,2\}\times\{1,2,3\}$) e in quel punto $p_{\underline{X}}(2,3)=0\neq p_{X_{1}}(2)p_{X_{2}}(3)=\frac{10}{29}\cdot\frac{7}{29}$: non c'è indipendenza.

**Urna $\{0,1,1,2\}$, 2 palline in blocco.** $X_{1}$ = somma e $X_{2}$ = prodotto dei due numeri estratti. Gli esiti sono $\binom{4}{2}=6$ equiprobabili (bisogna distinguere le due palline con il numero $1$: $1_{A},1_{B}$). Coppie $(X_{1},X_{2})$: $\{0,1_{A}\},\{0,1_{B}\}\to(1,0)$; $\{0,2\}\to(2,0)$; $\{1_{A},1_{B}\}\to(2,1)$; $\{1_{A},2\},\{1_{B},2\}\to(3,2)$. Quindi $$p_{\underline{X}}(1,0)=\tfrac{2}{6},\quad p_{\underline{X}}(2,0)=\tfrac{1}{6},\quad p_{\underline{X}}(2,1)=\tfrac{1}{6},\quad p_{\underline{X}}(3,2)=\tfrac{2}{6}.$$
- $P(\{X_{1}\geq2\}\cap\{X_{2}\leq1\})=p_{\underline{X}}(2,0)+p_{\underline{X}}(2,1)=\frac{1}{3}$ (le coppie $(1,0)$ e $(3,2)$ non soddisfano l'evento).
- $P(X_{1}=1|X_{2}=0)=\frac{p_{\underline{X}}(1,0)}{p_{\underline{X}}(1,0)+p_{\underline{X}}(2,0)}=\frac{2/6}{3/6}=\frac{2}{3}$ (al denominatore solo le coppie con $x_{2}=0$).

**Congiunta di tipo geometrico.** Sia $q\in(0,1)$ e $p_{\underline{X}}(k,0)=q\left(\frac{1}{2}\right)^{k+1}$ per $k\geq0$ intero, $p_{\underline{X}}(h,1)=(1-q)\left(\frac{3}{4}\right)^{h-1}\frac{1}{4}$ per $h\geq1$ intero. È ben posta: $q\cdot\frac{1/2}{1-1/2}+\frac{1-q}{4}\cdot\frac{1}{1-3/4}=q+(1-q)=1$.
1) $P(X_{1}=X_{2}|X_{1}\geq1)$: le uniche coppie con $x_{1}=x_{2}$ sono $(0,0)$ e $(1,1)$, e l'unico punto con $x_{1}<1$ è $(0,0)$. Quindi $=\frac{p_{\underline{X}}(1,1)}{1-p_{\underline{X}}(0,0)}=\frac{(1-q)/4}{1-q/2}=\frac{1-q}{2(2-q)}$.
2) I punti con $p_{\underline{X}}>0$ non formano un prodotto cartesiano: manca il punto $(0,1)$ (si ha $\{0,1,2,\dots\}\times\{0,1\}$). Quindi $p_{\underline{X}}(0,1)=0\neq p_{X_{1}}(0)p_{X_{2}}(1)$, con $p_{X_{1}}(0)=p_{\underline{X}}(0,0)=\frac{q}{2}\neq0$ (perché $q>0$) e $p_{X_{2}}(1)=\sum_{h\geq1}(1-q)\left(\frac{3}{4}\right)^{h-1}\frac{1}{4}=1-q\neq0$ (perché $q<1$). Non c'è indipendenza.
3) Con $D=\{1,3,5,7,\dots\}$ (numeri dispari): $P(X_{1}\in D|X_{2}=0)=\frac{\sum_{k\geq1}p_{\underline{X}}(2k-1,0)}{\sum_{k\geq0}p_{\underline{X}}(k,0)}=\frac{\sum_{k\geq1}(1/4)^{k}}{\sum_{k\geq0}(1/2)^{k+1}}=\frac{1/3}{1}=\frac{1}{3}$. Per il complementare si ottiene $P(X_{1}\in D^{c}|X_{2}=0)=\frac{2}{3}=1-\frac{1}{3}$, come previsto dalla teoria.

**Congiunta su $\{1,2,3\}^{2}$.** $p_{\underline{X}}(1,1)=\frac{2}{10}$ e $p_{\underline{X}}(x_{1},x_{2})=\frac{1}{10}$ negli altri $8$ punti.
1) $P(X_{1}+X_{2}\geq5)=p_{\underline{X}}(3,3)+p_{\underline{X}}(3,2)+p_{\underline{X}}(2,3)=\frac{3}{10}$.
2) $P(X_{1}=1|X_{2}=1)=\frac{p_{\underline{X}}(1,1)}{p_{\underline{X}}(1,1)+p_{\underline{X}}(2,1)+p_{\underline{X}}(3,1)}=\frac{2/10}{4/10}=\frac{1}{2}$.
3) $P(X_{1}=X_{2}|X_{1}+X_{2}\geq5)=\frac{p_{\underline{X}}(3,3)}{3/10}=\frac{1}{3}$ (è come se si ripartisse da un modello uniforme sui $3$ punti rimasti).

> [!question] Domanda tipica d'esame
> Come si ottengono le marginali dalla congiunta? Si può fare il contrario?
> **Risposta.** $p_{X_{i}}(x_{i})=\sum_{\underline{x}\in S_{\underline{X}}\ \text{con }i\text{-sima coordinata }x_{i}}p_{\underline{X}}(\underline{x})$. Il contrario no: due congiunte diverse possono avere le stesse marginali (esempio: $\frac{1}{4},\frac{1}{4},\frac{1}{4},\frac{1}{4}$ contro $\frac{1}{3},\frac{1}{6},\frac{1}{6},\frac{1}{3}$ su $\{0,1\}^{2}$).

> [!question] Domanda tipica d'esame
> Come si verifica se $X_{1},X_{2}$ discrete sono indipendenti? Qual è un criterio rapido di non indipendenza?
> **Risposta.** Vale $p_{\underline{X}}(x_{1},x_{2})=p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})$ per ogni coppia (basta verificarla sui punti del supporto); una sola coppia che non verifica l'uguaglianza esclude l'indipendenza. Se $\{p_{\underline{X}}>0\}$ non è un prodotto cartesiano non c'è indipendenza; il viceversa è falso (esempio con $a<b$ e probabilità $\frac{1}{3},\frac{1}{6},\frac{1}{6},\frac{1}{3}$).

--- Fine lezione 10 ---
## Trasformazioni e somme di variabili aleatorie discrete
Come si calcola la densità discreta di $\underline{Y}=f(\underline{X})$, con il caso particolare delle **somme** di v.a. indipendenti (binomiali e poissoniane).

> [!info] Notazione
> In questa parte si considerano v.a. discrete multidimensionali, e quindi con le notazioni di vettore $\underline{X}=(X_{1},\dots,X_{m})$. Poi, se la dimensione è 1 (quindi $m=1$), si recupera il caso "non multidimensionale" come caso particolare.
### Proposizione (densità di una trasformazione)
Sia $\underline{X}:\Omega\to \mathbb{R}^{m}$ una v.a. discreta $m$-dimensionale. Poi sia $f:A\subset \mathbb{R}^{m}\to \mathbb{R}^{n}$ una funzione. Allora, se $S_{\underline{X}}\subset A$, la funzione $\underline{Y}=f\circ \underline{X}:\Omega\to \mathbb{R}^{n}$ è una v.a. **discreta** $n$-dimensionale ($\underline{Y}$ è detta **trasformazione** della v.a. $\underline{X}$).
Inoltre per le densità discrete di $\underline{X}$ e $\underline{Y}$ vale la seguente uguaglianza: $$\begin{bmatrix}
p_{\underline{Y}}(\underline{y})=\sum_{\underline{x}\in S_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}p_{\underline{X}}(\underline{x})
\end{bmatrix}\quad\quad\forall\ \underline{y}\in \mathbb{R}^{n}$$
#### Dimostrazione
Per ogni $\underline{y}\in \mathbb{R}^{n}$ si ha $$p_{\underline{Y}}(\underline{y})=P(\underline{Y}=\underline{y})=P\left( \bigcup_{\underline{x}\in S_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}\{\underline{X}=\underline{x}\} \right)\overset{(\star)}{=}\sum_{\underline{x}\in S_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}P(\underline{X}=\underline{x})=\sum_{\underline{x}\in S_{\underline{X}}\ :\ f(\underline{x})=\underline{y}}p_{\underline{X}}(\underline{x})$$dove in $(\star)$ si ha un'unione al più numerabile di eventi disgiunti a due a due, e si applica la $\sigma$-additività. Questa è l'uguaglianza che volevamo ottenere $\Box$
#### Esempio (con $m=3$ e $n=2$)
Sia $p_{\underline{X}}$ definita come segue: $$p_{\underline{X}}(0,0,0)=\frac{2}{8};\quad p_{\underline{X}}(0,0,1)=p_{\underline{X}}(0,1,0)=p_{\underline{X}}(1,0,0)=p_{\underline{X}}(1,0,1)=p_{\underline{X}}(1,1,0)=p_{\underline{X}}(0,1,1)=\frac{1}{8}$$Inoltre sia $\underline{Y}=f(\underline{X})$, dove $$f(\underline{x})=f(x_{1},x_{2},x_{3})=(x_{1}+x_{2},\ x_{2}\cdot x_{3})\quad\quad\forall\ \underline{x}=(x_{1},x_{2},x_{3})\in \mathbb{R}^{3}$$Vogliamo usare l'uguaglianza $p_{\underline{Y}}(\underline{y})=\sum_{\underline{x}\ :\ f(\underline{x})=\underline{y}}p_{\underline{X}}(\underline{x})$.
Osserviamo che $S_{\underline{Y}}\subset\{0,1,2\}\times\{0,1\}$; quindi calcoleremo $p_{\underline{Y}}(\underline{y})$ per $\underline{y}\in\{0,1,2\}\times\{0,1\}$ (sappiamo che $p_{\underline{Y}}(\underline{y})=0$ se $\underline{y}\not\in S_{\underline{Y}}$). Quindi $$\begin{array}{ll}
p_{\underline{Y}}(0,0)=p_{\underline{X}}(0,0,0)+p_{\underline{X}}(0,0,1)=\frac{2}{8}+\frac{1}{8}=\frac{3}{8} & p_{\underline{Y}}(0,1)=0 \\
p_{\underline{Y}}(1,0)=p_{\underline{X}}(0,1,0)+p_{\underline{X}}(1,0,0)+p_{\underline{X}}(1,0,1)=\frac{1}{8}+\frac{1}{8}+\frac{1}{8}=\frac{3}{8} & p_{\underline{Y}}(1,1)=p_{\underline{X}}(0,1,1)=\frac{1}{8} \\
p_{\underline{Y}}(2,0)=p_{\underline{X}}(1,1,0)=\frac{1}{8} & p_{\underline{Y}}(2,1)=0
\end{array}$$(la somma fa 1, come deve essere).
#### Esempio (con $m=2$ e $n=1$)
Essendo $n=1$ si può scrivere $Y$ anziché $\underline{Y}$. Supponiamo di avere $$p_{\underline{X}}(0,0)=\frac{2}{20};\quad p_{\underline{X}}(0,1)=p_{\underline{X}}(1,0)=p_{\underline{X}}(1,1)=\frac{3}{20};\quad p_{\underline{X}}(0,2)=p_{\underline{X}}(2,0)=\frac{1}{20};\quad p_{\underline{X}}(2,2)=\frac{7}{20}$$Sia $Y=(X_{1}+X_{2})^{2}$; allora $S_{Y}=\{0,1,4,16\}$, ed inoltre $$\begin{array}{l}
p_{Y}(0)=p_{\underline{X}}(0,0)=\frac{2}{20} \\
p_{Y}(1)=p_{\underline{X}}(0,1)+p_{\underline{X}}(1,0)=\frac{3}{20}+\frac{3}{20}=\frac{6}{20} \\
p_{Y}(4)=p_{\underline{X}}(1,1)+p_{\underline{X}}(0,2)+p_{\underline{X}}(2,0)=\frac{3}{20}+\frac{1}{20}+\frac{1}{20}=\frac{5}{20} \\
p_{Y}(16)=p_{\underline{X}}(2,2)=\frac{7}{20}
\end{array}$$(la somma fa 1, come deve essere).
### Una classe generale di esempi: somme di v.a.
Vogliamo trattare il caso in cui $n=1$ e $$f(x_{1},\dots,x_{m})=x_{1}+\dots+x_{m}\quad\quad\forall\ (x_{1},\dots,x_{m})\in \mathbb{R}^{m}$$Quindi si ha $$\begin{bmatrix}
p_{Y}(y)=\sum_{\underline{x}\in S_{\underline{X}}\ :\ x_{1}+\dots+x_{m}=y}p_{\underline{X}}(\underline{x})
\end{bmatrix}$$Vedremo ora alcuni casi specifici con $m=2$; in particolare, per alcuni casi tra questi, il passaggio da $m=2$ a $m$ generico sarà semplice procedendo per induzione.

> [!warning] Nota sulla notazione dei parametri
> Nei casi 2 e 3 che seguono il numero di prove delle binomiali è indicato qui con $n_{1},n_{2}$ (e $n_{1},\dots,n_{m}$ nel caso generale), per non confonderlo con la dimensione $m$ del vettore. Sulle slide manoscritte la lettera usata per questi parametri è la stessa impiegata per la dimensione.
#### Caso specifico 1 (lancio di due dadi equi)
$$p_{\underline{X}}(x_{1},x_{2})=\frac{1}{36}\quad\quad\forall\ \underline{x}=(x_{1},x_{2})\in\{1,\dots,6\}\times\{1,\dots,6\}$$Sia $Y=X_{1}+X_{2}$, con $S_{Y}=\{2,3,4,5,6,7,8,9,10,11,12\}$. Allora $$p_{Y}(y)=\sum_{\underline{x}\in\{1,\dots,6\}\times\{1,\dots,6\}\ :\ x_{1}+x_{2}=y}p_{\underline{X}}(\underline{x})=\frac{\#\{(x_{1},x_{2}):x_{1}+x_{2}=y\}}{36}$$e recuperiamo i risultati già visti in passato: $$\begin{array}{lll}
p_{Y}(2)=p_{Y}(12)=\frac{1}{36}, & p_{Y}(3)=p_{Y}(11)=\frac{2}{36}, & p_{Y}(4)=p_{Y}(10)=\frac{3}{36}, \\
p_{Y}(5)=p_{Y}(9)=\frac{4}{36}, & p_{Y}(6)=p_{Y}(8)=\frac{5}{36}, & p_{Y}(7)=\frac{6}{36}
\end{array}$$La somma vale $2\cdot \frac{1}{36}+2\cdot \frac{2}{36}+2\cdot \frac{3}{36}+2\cdot \frac{4}{36}+2\cdot \frac{5}{36}+\frac{6}{36}=\frac{2+4+6+8+10+6}{36}=\frac{36}{36}=1$.
#### Caso specifico 2 (somma di 2 binomiali indipendenti con lo stesso parametro $p$)
Siano $X_{1}\sim BIN(n_{1},p)$ e $X_{2}\sim BIN(n_{2},p)$ **indipendenti**. Allora, per la [[02 - Modelli discreti#Proposizione (condizione necessaria e sufficiente)|caratterizzazione dell'indipendenza]], $$p_{\underline{X}}(x_{1},x_{2})=p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})=\binom{n_{1}}{x_{1}}p^{x_{1}}(1-p)^{n_{1}-x_{1}}\binom{n_{2}}{x_{2}}p^{x_{2}}(1-p)^{n_{2}-x_{2}}=\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}p^{x_{1}+x_{2}}(1-p)^{n_{1}+n_{2}-(x_{1}+x_{2})}$$per ogni $(x_{1},x_{2})\in\{0,1,\dots,n_{1}\}\times\{0,1,\dots,n_{2}\}$.
Sia $Y=X_{1}+X_{2}$, con $S_{Y}=\{0,1,\dots,n_{1}+n_{2}\}$. Allora, per ogni $y\in S_{Y}$, $$p_{Y}(y)=\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}p^{\overset{=y}{\overbrace{x_{1}+x_{2}}}}(1-p)^{n_{1}+n_{2}-\overset{=y}{\overbrace{(x_{1}+x_{2})}}}=p^{y}(1-p)^{n_{1}+n_{2}-y}\underset{=\binom{n_{1}+n_{2}}{y}}{\underbrace{\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}}}=\binom{n_{1}+n_{2}}{y}p^{y}(1-p)^{n_{1}+n_{2}-y}$$dove per la somma dei prodotti di coefficienti binomiali, $\sum_{x_{1}+x_{2}=y}\binom{n_{1}}{x_{1}}\binom{n_{2}}{x_{2}}=\binom{n_{1}+n_{2}}{y}$ (identità di Vandermonde), si usano le formule viste per l'[[02 - Modelli discreti#Caso 2): distribuzione ipergeometrica|ipergeometrica]].

> [!quote] Commento
> $$Y=X_{1}+X_{2}\sim BIN(n_{1}+n_{2},p)$$
##### Altri commenti (1ª parte): estensione a $m$ addendi
Il risultato si estende al caso di $m$ addendi indipendenti: $$\begin{cases}
X_{1}\sim BIN(n_{1},p) \\
\quad\vdots \\
X_{m}\sim BIN(n_{m},p)
\end{cases}\text{indip.}\quad\implies\quad X_{1}+\dots+X_{m}\sim BIN(n_{1}+\dots+n_{m},p)$$Il risultato non sorprende: ognuna delle v.a. $X_{i}$ (per $i\in\{1,\dots,m\}$) conta il numero di successi su $n_{i}$ prove indipendenti, tutte con probabilità di successo $p$; quindi, se consideriamo la somma (e gli addendi sono indipendenti), è come se contassimo il numero di successi su $n_{1}+\dots+n_{m}$ prove tutte con probabilità di successo $p$.
Quindi è importante che **il parametro $p$ sia sempre lo stesso**; e senza l'ipotesi di indipendenza il risultato non è vero.
##### Altri commenti (2ª parte): controesempio senza indipendenza

> [!info] Segnalato dal prof come "un po' difficile"

Sia $p\in(0,1)$, cioè $p\neq 0$ e $p\neq 1$; siano $m=2$, $X_{1}\sim BIN(n,p)$ e $X_{2}=X_{1}$. Quindi in particolare $X_{2}\sim BIN(n,p)$. Allora si ha $$\begin{cases}
P(\{X_{1}=0\}\cap\{X_{2}=0\})=P(X_{1}=0)=(1-p)^{n} \\
P(X_{1}=0)P(X_{2}=0)=(1-p)^{n}(1-p)^{n}=(1-p)^{2n}
\end{cases}\text{diversi tra loro}\implies X_{1},X_{2}\text{ non sono indipendenti}$$Inoltre $X_{1}+X_{2}=2X_{1}$, e quindi $P(X_{1}+X_{2}\in\{\text{numeri dispari}\})=0$; quindi "$X_{1}+X_{2}\sim BIN(\underset{=2n}{\underbrace{n+n}},p)$" è **falsa**, perché tutti i valori in $\{0,1,2,\dots,2n-1,2n\}$ dovrebbero avere probabilità positiva.
#### Caso specifico 3 (somma di 2 poissoniane indipendenti)
Siano $X_{1}\sim POISSON(\lambda_{1})$ e $X_{2}\sim POISSON(\lambda_{2})$ **indipendenti**. Allora $$p_{\underline{X}}(x_{1},x_{2})=p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})=\frac{\lambda_{1}^{x_{1}}}{x_{1}!}e^{-\lambda_{1}}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-\lambda_{2}}=\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-(\lambda_{1}+\lambda_{2})}$$per ogni $(x_{1},x_{2})\in\{0,1,2,\dots\}\times\{0,1,2,\dots\}$.
Sia $Y=X_{1}+X_{2}$, con $S_{Y}=\{0,1,2,\dots\}$. Allora $$\begin{array}{ll}
p_{Y}(y) & =\displaystyle\sum_{(x_{1},x_{2})\ :\ x_{1}+x_{2}=y}\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{x_{2}}}{x_{2}!}e^{-(\lambda_{1}+\lambda_{2})}=e^{-(\lambda_{1}+\lambda_{2})}\sum_{x_{1}=0}^{y}\frac{\lambda_{1}^{x_{1}}}{x_{1}!}\frac{\lambda_{2}^{y-x_{1}}}{(y-x_{1})!} \\
 & =\frac{e^{-(\lambda_{1}+\lambda_{2})}}{y!}\displaystyle\sum_{x_{1}=0}^{y}\underset{=\binom{y}{x_{1}}}{\underbrace{\frac{y!}{x_{1}!(y-x_{1})!}}}\lambda_{1}^{x_{1}}\lambda_{2}^{y-x_{1}}\overset{\text{binomio di Newton}}{=}\frac{e^{-(\lambda_{1}+\lambda_{2})}}{y!}(\lambda_{1}+\lambda_{2})^{y}=\frac{(\lambda_{1}+\lambda_{2})^{y}}{y!}e^{-(\lambda_{1}+\lambda_{2})}
\end{array}$$

> [!quote] Commento
> $$Y=X_{1}+X_{2}\sim POISSON(\lambda_{1}+\lambda_{2})$$
##### Altri commenti
Il risultato si estende al caso di $m$ addendi indipendenti (simile a quello per le [[02 - Modelli discreti#Caso specifico 2 (somma di 2 binomiali indipendenti con lo stesso parametro $p$)|binomiali]] visto prima): $$\begin{cases}
X_{1}\sim POISSON(\lambda_{1}) \\
\quad\vdots \\
X_{m}\sim POISSON(\lambda_{m})
\end{cases}\text{indip.}\quad\implies\quad X_{1}+\dots+X_{m}\sim POISSON(\lambda_{1}+\dots+\lambda_{m})$$Senza l'ipotesi di indipendenza il risultato non è vero in generale. Un controesempio è il seguente: $m=2$, $X_{1}\sim POISSON(\lambda)$ e $X_{2}=X_{1}$ (allora $X_{2}\sim POISSON(\lambda)$). Si ha $$\begin{cases}
P(\{X_{1}=0\}\cap\{X_{2}=0\})=P(X_{1}=0)=e^{-\lambda} \\
P(X_{1}=0)P(X_{2}=0)=e^{-\lambda}\cdot e^{-\lambda}=e^{-2\lambda}
\end{cases}\implies X_{1},X_{2}\text{ non sono indipendenti}$$Inoltre $X_{1}+X_{2}=2X_{1}$ e quindi $P(X_{1}+X_{2}\in\{\text{numeri dispari}\})=0$; quindi "$X_{1}+X_{2}\sim POISSON(\lambda+\lambda)=POISSON(2\lambda)$" è **falsa**, perché tutti gli interi non negativi dovrebbero avere probabilità positiva.

> [!info] Esercizi della lezione 11
> Le pp. 13-26 della lezione 11 contengono esercizi su densità congiunte discrete, marginali e indipendenza; sono svolti qui sotto.
> Vale la pena ricordare la **tecnica** usata per verificare che una congiunta a supporto "triangolare" è ben posta: si può sommare fissando $x_{1}$ e variando $x_{2}$ (sulle verticali), oppure fissando $x_{2}$ e variando $x_{1}$ (sulle orizzontali). Per usare le formule sulle [[02 - Modelli discreti#Formula della serie geometrica|serie geometriche]] conviene la seconda.
#### Esempi svolti (lezione 11, pp. 13-26)
**Congiunta con supporto triangolare.** Siano $p_{1},p_{2}\in(0,1)$ e $$p_{\underline{X}}(x_{1},x_{2})=(1-p_{2})^{x_{2}-1}(1-p_{1})^{x_{1}-x_{2}}p_{1}p_{2}\quad\quad\text{per }x_{1}\geq x_{2}\geq 1\text{ interi.}$$
1) *Ben posta.* Si deve verificare che $\sum_{x_{1}\geq x_{2}\geq 1}p_{\underline{X}}(x_{1},x_{2})=1$. Si fissa $x_{2}$ e si somma sulle orizzontali (con $h=x_{1}-x_{2}\geq 0$): $$p_{1}p_{2}\sum_{x_{2}=1}^{\infty}(1-p_{2})^{x_{2}-1}\underset{=\frac{1}{p_{1}}}{\underbrace{\sum_{h=0}^{\infty}(1-p_{1})^{h}}}=p_{2}\sum_{x_{2}=1}^{\infty}(1-p_{2})^{x_{2}-1}=p_{2}\cdot\frac{1}{p_{2}}=1.$$
2) *Marginale di $X_{2}$.* Per $x_{2}\geq 1$ intero, con lo stesso calcolo, $p_{X_{2}}(x_{2})=p_{1}p_{2}(1-p_{2})^{x_{2}-1}\cdot\frac{1}{p_{1}}=(1-p_{2})^{x_{2}-1}p_{2}$; quindi $X_{2}\sim GeoTraslata(p_{2})$.
3) *Non c'è indipendenza.* I punti del supporto non formano un prodotto cartesiano: ci sono infiniti "punti mancanti", per esempio $(1,2)$. Infatti $p_{\underline{X}}(1,2)=0$, mentre $p_{X_{1}}(1)=p_{\underline{X}}(1,1)=p_{1}p_{2}\neq 0$ e $p_{X_{2}}(2)=(1-p_{2})p_{2}\neq 0$ (perché $0<p_{1},p_{2}<1$).
4) *$P(X_{1}+X_{2}\leq 4)$.* I punti con $x_{1}+x_{2}\leq 4$ nel supporto sono $(1,1),(2,1),(3,1),(2,2)$: $$P(X_{1}+X_{2}\leq 4)=p_{1}p_{2}\left[1+(1-p_{1})+(1-p_{1})^{2}+(1-p_{2})\right].$$
5) *Marginale di $X_{1}$ con $p_{1}=p_{2}=p$.* Per $x_{1}\geq 1$ intero, $$p_{X_{1}}(x_{1})=p^{2}\sum_{x_{2}=1}^{x_{1}}(1-p)^{x_{1}-1}=p^{2}x_{1}(1-p)^{x_{1}-1}$$perché l'addendo non dipende da $x_{2}$. Questa densità non è una delle distribuzioni notevoli viste; per verificare che $\sum_{x_{1}\geq1}p_{X_{1}}(x_{1})=1$ si parte da $\sum_{x\geq 1}(1-p)^{x}=\frac{1-p}{p}=\frac{1}{p}-1$ e si deriva membro a membro rispetto a $p$ (lecito per le serie di potenze, nel raggio di convergenza: la derivata della serie è la serie delle derivate): $-\sum_{x\geq1}x(1-p)^{x-1}=-\frac{1}{p^{2}}$, cioè $p^{2}\sum_{x\geq1}x(1-p)^{x-1}=1$.

**Costante di normalizzazione.** $p_{\underline{X}}(x_{1},x_{2})=c\left(\frac{1}{2}\right)^{x_{1}}\left(\frac{3}{4}\right)^{x_{2}}$ per $x_{1},x_{2}\geq 1$ interi, con $c>0$ da determinare.
1) Si ha il prodotto di due serie geometriche: $$1=c\sum_{x_{1}\geq1}\left(\tfrac{1}{2}\right)^{x_{1}}\sum_{x_{2}\geq1}\left(\tfrac{3}{4}\right)^{x_{2}}=c\cdot\frac{1/2}{1-1/2}\cdot\frac{3/4}{1-3/4}=c\cdot 1\cdot 3\quad\Longrightarrow\quad c=\frac{1}{3}.$$
2) $P(X_{2}=2X_{1})=\sum_{k=1}^{\infty}p_{\underline{X}}(k,2k)=\frac{1}{3}\sum_{k\geq1}\left(\frac{1}{2}\right)^{k}\left(\frac{3}{4}\right)^{2k}=\frac{1}{3}\sum_{k\geq1}\left(\frac{9}{32}\right)^{k}=\frac{1}{3}\cdot\frac{9/32}{1-9/32}=\frac{1}{3}\cdot\frac{9}{23}=\frac{3}{23}$. Compaiono due potenze: bisogna ridurle a un'unica potenza prima di usare la formula della serie geometrica.
3) $P(X_{2}\geq 3X_{1})$: si sommano i valori nei punti del semipiano "sopra" la retta, prendendoli "in verticale" (si risolve prima la serie più interna, quella in $x_{2}$ per $x_{1}$ fissato, e poi si porta tutto a un'unica potenza): $$\frac{1}{3}\sum_{x_{1}\geq1}\left(\tfrac{1}{2}\right)^{x_{1}}\sum_{x_{2}\geq3x_{1}}\left(\tfrac{3}{4}\right)^{x_{2}}=\frac{1}{3}\sum_{x_{1}\geq1}\left(\tfrac{1}{2}\right)^{x_{1}}\frac{(3/4)^{3x_{1}}}{1/4}=\frac{4}{3}\sum_{x_{1}\geq1}\left(\frac{27}{128}\right)^{x_{1}}=\frac{4}{3}\cdot\frac{27/128}{101/128}=\frac{36}{101}.$$

**Congiunta "geometrica $\times$ Poisson".** $p_{\underline{X}}(x_{1},x_{2})=\left(\frac{3}{4}\right)^{x_{1}-1}\frac{1}{4}\cdot\frac{2^{x_{2}}}{x_{2}!}e^{-2}$ per $x_{1}\geq 1$ e $x_{2}\geq 0$ interi.
1) $P(X_{2}\leq X_{1}-1)$: si sommano i valori sotto la retta, conviene "prenderli in orizzontale" ($x_{2}\geq 0$, $x_{1}\geq x_{2}+1$) e si usa la serie esponenziale: $$\frac{e^{-2}}{4}\sum_{x_{2}\geq0}\frac{2^{x_{2}}}{x_{2}!}\sum_{x_{1}\geq x_{2}+1}\left(\tfrac{3}{4}\right)^{x_{1}-1}=\frac{e^{-2}}{4}\cdot\frac{1}{1-3/4}\sum_{x_{2}\geq0}\frac{(2\cdot\frac{3}{4})^{x_{2}}}{x_{2}!}=e^{-2}e^{3/2}=e^{-1/2}.$$
2) $P(X_{1}\leq 2|X_{2}\leq X_{1}-1)$: il denominatore è il valore appena calcolato; l'intersezione $\{X_{1}\leq2\}\cap\{X_{2}\leq X_{1}-1\}$ contiene solo i tre punti $(1,0),(2,0),(2,1)$, quindi $$\frac{\left(\frac{1}{4}+\frac{3}{16}+\frac{3}{16}\cdot2\right)e^{-2}}{e^{-1/2}}=\frac{13}{16}e^{-3/2}.$$
3) Marginali: $p_{X_{1}}(x_{1})=\left(\frac{3}{4}\right)^{x_{1}-1}\frac{1}{4}$ per $x_{1}\geq1$ (serie esponenziale $\sum_{x_{2}\geq0}\frac{2^{x_{2}}}{x_{2}!}=e^{2}$), cioè $X_{1}\sim GeoTraslata(\frac{1}{4})$; $p_{X_{2}}(x_{2})=\frac{2^{x_{2}}}{x_{2}!}e^{-2}$ per $x_{2}\geq0$, cioè $X_{2}\sim POISSON(2)$. Poiché $p_{\underline{X}}(x_{1},x_{2})=p_{X_{1}}(x_{1})p_{X_{2}}(x_{2})$ per ogni $(x_{1},x_{2})$, le v.a. $X_{1},X_{2}$ sono indipendenti.

--- Fine lezione 11 ---

#### Esempi svolti (lezione 12, pp. 1-4)
**Somma e differenza.** Sia $\underline{X}=(X_{1},X_{2})$ con $$p_{\underline{X}}(1,0)=p_{\underline{X}}(2,0)=p_{\underline{X}}(0,2)=\frac{1}{6};\quad p_{\underline{X}}(0,0)=p_{\underline{X}}(0,1)=p_{\underline{X}}(1,1)=p_{\underline{X}}(2,1)=p_{\underline{X}}(1,2)=p_{\underline{X}}(2,2)=\frac{1}{12}.$$ Si cercano le densità discrete di $Z=X_{1}+X_{2}$ e di $W=X_{1}-X_{2}$, con la formula $p_{Z}(z)=\sum_{\underline{x}:\ x_{1}+x_{2}=z}p_{\underline{X}}(\underline{x})$ (e analoga per $W$).
- $p_{Z}(0)=p_{\underline{X}}(0,0)=\frac{1}{12}$; $p_{Z}(1)=p_{\underline{X}}(0,1)+p_{\underline{X}}(1,0)=\frac{1}{12}+\frac{1}{6}=\frac{3}{12}$; $p_{Z}(2)=p_{\underline{X}}(0,2)+p_{\underline{X}}(1,1)+p_{\underline{X}}(2,0)=\frac{1}{6}+\frac{1}{12}+\frac{1}{6}=\frac{5}{12}$; $p_{Z}(3)=p_{\underline{X}}(1,2)+p_{\underline{X}}(2,1)=\frac{2}{12}$; $p_{Z}(4)=p_{\underline{X}}(2,2)=\frac{1}{12}$. La somma fa $1$.
- $p_{W}(-2)=p_{\underline{X}}(0,2)=\frac{2}{12}$; $p_{W}(-1)=p_{\underline{X}}(1,2)+p_{\underline{X}}(0,1)=\frac{2}{12}$; $p_{W}(0)=p_{\underline{X}}(0,0)+p_{\underline{X}}(1,1)+p_{\underline{X}}(2,2)=\frac{3}{12}$; $p_{W}(1)=p_{\underline{X}}(1,0)+p_{\underline{X}}(2,1)=\frac{3}{12}$; $p_{W}(2)=p_{\underline{X}}(2,0)=\frac{2}{12}$. La somma fa $1$.

> [!info] Rimando
> Su questa stessa congiunta la lavagna aggiuntiva della lezione 12 calcola $\mathbb{E}[X_{1}+X_{2}]=\frac{18}{5}$ con tre metodi diversi: si veda la nota [[03 - Speranza matematica e momenti]], perché è un'applicazione della speranza.

**Lanci di una moneta con numero aleatorio di lanci.** Sia $N\sim POISSON(\lambda)$; si lancia $N$ volte una moneta con $P(\text{testa})=p\in(0,1)$, con $X_{1}=\#$ teste e $X_{2}=\#$ croci (quindi $N=X_{1}+X_{2}$). Si cerca la densità congiunta di $(X_{1},X_{2})$.
*Osservazione preliminare.* Nell'[[02 - Modelli discreti#Esercizio teorico: un numero aleatorio di lanci (Poisson "assottigliata")|esercizio già visto]] si è ottenuto $X_{1}\sim POISSON(\lambda p)$; scambiando i ruoli di teste e croci (cioè di successi e fallimenti) si ha $X_{2}\sim POISSON(\lambda(1-p))$. Quindi $p_{X_{1}}(x_{1})=\frac{(\lambda p)^{x_{1}}}{x_{1}!}e^{-\lambda p}$ e $p_{X_{2}}(x_{2})=\frac{(\lambda(1-p))^{x_{2}}}{x_{2}!}e^{-\lambda(1-p)}$ per $x_{1},x_{2}\geq0$ interi.
*Congiunta.* Per ogni $(x_{1},x_{2})\in\{0,1,2,\dots\}^{2}$, per la formula delle probabilità totali, $$p_{\underline{X}}(x_{1},x_{2})=\sum_{n=0}^{\infty}P(\{X_{1}=x_{1}\}\cap\{X_{2}=x_{2}\}|N=n)\,P(N=n),\quad P(N=n)=\frac{\lambda^{n}}{n!}e^{-\lambda}.$$ Il fattore condizionato vale $0$ se $x_{1}+x_{2}\neq n$, e se $x_{1}+x_{2}=n$ (quindi $x_{2}=n-x_{1}$) è il caso particolare di binomiale $\binom{n}{x_{1}}p^{x_{1}}(1-p)^{n-x_{1}}$ (con $\binom{n}{x_{1}}=\binom{n}{x_{2}}$). Quindi la serie si riduce a un unico addendo, quello con $n=x_{1}+x_{2}$: $$p_{\underline{X}}(x_{1},x_{2})=\binom{x_{1}+x_{2}}{x_{1}}p^{x_{1}}(1-p)^{x_{2}}\frac{\lambda^{x_{1}+x_{2}}}{(x_{1}+x_{2})!}e^{-\lambda}\quad\quad\forall\ x_{1},x_{2}\geq 0\text{ interi}.$$ Svolgendo il coefficiente binomiale e usando $\lambda^{x_{1}+x_{2}}=\lambda^{x_{1}}\lambda^{x_{2}}$ e $e^{-\lambda}=e^{-\lambda p}e^{-\lambda(1-p)}$, $$p_{\underline{X}}(x_{1},x_{2})=\frac{p^{x_{1}}(1-p)^{x_{2}}}{x_{1}!\,x_{2}!}\lambda^{x_{1}}\lambda^{x_{2}}e^{-\lambda p}e^{-\lambda(1-p)}=\frac{(\lambda p)^{x_{1}}}{x_{1}!}e^{-\lambda p}\cdot\frac{(\lambda(1-p))^{x_{2}}}{x_{2}!}e^{-\lambda(1-p)}=p_{X_{1}}(x_{1})\,p_{X_{2}}(x_{2}).$$

> [!quote] Conclusione
> $X_{1}$ e $X_{2}$ sono **indipendenti**. Anche se condizionatamente a $N$ le due v.a. sono fortemente legate (perché $X_{1}+X_{2}=N$), quando $N$ è aleatoria con $N\sim POISSON(\lambda)$ c'è indipendenza; se $N$ è aleatoria con un'altra distribuzione non c'è indipendenza.

> [!question] Domanda tipica d'esame
> Come si ricava la densità di $Y=f(\underline{X})$ dalla congiunta? Qual è la densità di $X_{1}+X_{2}$ se $X_{1}\sim BIN(n_{1},p)$ e $X_{2}\sim BIN(n_{2},p)$ sono indipendenti? E per due Poisson? Che cosa succede senza indipendenza?
> **Risposta.** $p_{\underline{Y}}(\underline{y})=\sum_{\underline{x}\in S_{\underline{X}}:\ f(\underline{x})=\underline{y}}p_{\underline{X}}(\underline{x})$. Con indipendenza: $X_{1}+X_{2}\sim BIN(n_{1}+n_{2},p)$ (stesso $p$) e $X_{1}+X_{2}\sim POISSON(\lambda_{1}+\lambda_{2})$. Senza indipendenza il risultato è falso: con $X_{2}=X_{1}$ si ha $X_{1}+X_{2}=2X_{1}$, che non assume mai valori dispari.
## Massimi e minimi di variabili aleatorie discrete
Come calcolare la densità discreta di $\max\{X_{1},X_{2}\}$ e $\min\{X_{1},X_{2}\}$ passando per le [[02 - Modelli discreti#Funzione di distribuzione di una v.a. reale|funzioni di distribuzione]].
### Impostazione
Per semplicità consideriamo il caso di $\underline{X}=(X_{1},X_{2})$ e consideriamo le seguenti v.a.: $$\begin{array}{l}
Y=\max\{X_{1},X_{2}\} \\
W=\min\{X_{1},X_{2}\}
\end{array}$$Inoltre supponiamo che le v.a. $X_{1}$ e $X_{2}$ assumano **valori interi**; allora lo stesso si può dire per le v.a. $Y$ e $W$.
Per quel che segue è utile fare riferimento alle seguenti formule: $$\begin{array}{ll}
(*) & p_{Y}(y)=P(Y=y)=P(Y\leq y)-P(Y\leq y-1) \\
(**) & p_{W}(w)=P(W=w)=P(W\geq w)-P(W\geq w+1)
\end{array}$$(valgono perché i valori assunti sono interi: fra $y-1$ e $y$ non ci sono altri valori possibili).
### Le formule per il massimo e per il minimo
Per spiegare questo osserviamo che $$\{Y\leq y\}=\{\max\{X_{1},X_{2}\}\leq y\}=\{X_{1}\leq y\}\cap\{X_{2}\leq y\}$$(il massimo è $\leq y$ **se e solo se** entrambe lo sono), da cui $$\begin{array}{ll}
p_{Y}(y)\overset{(*)}{=}P(Y\leq y)-P(Y\leq y-1) & =P(\{X_{1}\leq y\}\cap\{X_{2}\leq y\})-P(\{X_{1}\leq y-1\}\cap\{X_{2}\leq y-1\}) \\
 & \underset{\text{se }X_{1},X_{2}\text{ indip.}}{=}P(X_{1}\leq y)P(X_{2}\leq y)-P(X_{1}\leq y-1)P(X_{2}\leq y-1)
\end{array}$$Analogamente $$\{W\geq w\}=\{\min\{X_{1},X_{2}\}\geq w\}=\{X_{1}\geq w\}\cap\{X_{2}\geq w\}$$(il minimo è $\geq w$ **se e solo se** entrambe lo sono), da cui $$\begin{array}{ll}
p_{W}(w)\overset{(**)}{=}P(W\geq w)-P(W\geq w+1) & =P(\{X_{1}\geq w\}\cap\{X_{2}\geq w\})-P(\{X_{1}\geq w+1\}\cap\{X_{2}\geq w+1\}) \\
 & \underset{\text{se }X_{1},X_{2}\text{ indip.}}{=}P(X_{1}\geq w)P(X_{2}\geq w)-P(X_{1}\geq w+1)P(X_{2}\geq w+1)
\end{array}$$

> [!info] L'idea *(extra, non da slide)*
> Per il **massimo** conviene passare dalla funzione di distribuzione $P(\cdot\leq\cdot)$, per il **minimo** dalla "coda" $P(\cdot\geq\cdot)$: in entrambi i casi l'evento si spezza in un'**intersezione**, che sotto indipendenza si fattorizza.
### Esempio di applicazione delle formule
Si lanciano due dadi equi. Siano $X_{1}$ e $X_{2}$ le v.a. che indicano i numeri che escono, e sappiamo che sono **indipendenti**. Allora $$\begin{array}{l}
Y=\max\{X_{1},X_{2}\}\text{ assume valori in }S_{Y}=\{1,2,3,4,5,6\} \\
W=\min\{X_{1},X_{2}\}\text{ assume valori in }S_{W}=\{1,2,3,4,5,6\}
\end{array}$$
**Massimo.** Per $y\in\{1,\dots,6\}$ si ha $P(X_{i}\leq y)=\frac{y}{6}$, quindi $$p_{Y}(y)=P(X_{1}\leq y)P(X_{2}\leq y)-P(X_{1}\leq y-1)P(X_{2}\leq y-1)=\frac{y}{6}\cdot \frac{y}{6}-\frac{y-1}{6}\cdot \frac{y-1}{6}=\frac{y^{2}-(y-1)^{2}}{36}=\frac{y^{2}-(y^{2}-2y+1)}{36}=\frac{2y-1}{36}$$cioè $$p_{Y}(y)=\begin{cases}
1/36 & \text{per }y=1 \\
3/36 & \text{per }y=2 \\
5/36 & \text{per }y=3 \\
7/36 & \text{per }y=4 \\
9/36 & \text{per }y=5 \\
11/36 & \text{per }y=6
\end{cases}$$(la somma fa 1, come deve essere).
**Minimo.** Per $w\in\{1,\dots,6\}$ si ha $P(X_{i}\geq w)=\frac{6-w+1}{6}=\frac{7-w}{6}$, quindi $$p_{W}(w)=\frac{6-w+1}{6}\cdot \frac{6-w+1}{6}-\frac{6-(w+1)+1}{6}\cdot \frac{6-(w+1)+1}{6}=\frac{(7-w)^{2}}{36}-\frac{(6-w)^{2}}{36}=\frac{49-14w+w^{2}-(36-12w+w^{2})}{36}=\frac{13-2w}{36}$$cioè $$p_{W}(w)=\begin{cases}
11/36 & \text{per }w=1 \\
9/36 & \text{per }w=2 \\
7/36 & \text{per }w=3 \\
5/36 & \text{per }w=4 \\
3/36 & \text{per }w=5 \\
1/36 & \text{per }w=6
\end{cases}$$(la somma fa 1, come deve essere).

> [!info] Lettura geometrica
> Sul piano cartesiano dei 36 esiti, $\{Y=y\}$ è la "squadra" (riga + colonna) di vertice $(y,y)$, e $\{W=w\}$ è la squadra di vertice $(w,w)$ aperta verso l'alto a destra: da qui i conteggi $2y-1$ e $13-2w$.

> [!question] Domanda tipica d'esame
> Come si calcola la densità di $\max\{X_{1},X_{2}\}$ e $\min\{X_{1},X_{2}\}$ (valori interi, indipendenti)? Che cosa si ottiene con due dadi?
> **Risposta.** $p_{Y}(y)=P(X_{1}\leq y)P(X_{2}\leq y)-P(X_{1}\leq y-1)P(X_{2}\leq y-1)$ e $p_{W}(w)=P(X_{1}\geq w)P(X_{2}\geq w)-P(X_{1}\geq w+1)P(X_{2}\geq w+1)$. Con due dadi equi: $p_{Y}(y)=\frac{2y-1}{36}$ e $p_{W}(w)=\frac{13-2w}{36}$ per $y,w\in\{1,\dots,6\}$.

--- Fine parte su massimi e minimi (lezione 12, pp. 5-8) ---

## Esercizi di riepilogo (lezione 23)
Esercizi della lezione 23 (pp. 1-15 e 21-28) che riassumono i modelli discreti: binomiale, multinomiale, ipergeometrica, geometrica, binomiale negativa traslata, approssimazione di Poisson, congiunte e probabilità condizionate. Per media e varianza si usano le formule viste in [[03 - Speranza matematica e momenti]].
### Urna riempita con $X\sim BIN(n,p)$ palline bianche (lezione 23, pp. 1-3)
Un'urna è inizialmente vuota e una moneta ha probabilità $p\in(0,1)$ di dare testa. La moneta viene lanciata $n$ volte e $X$ conta le teste; poi si mettono nell'urna $X$ palline bianche e $n-X$ nere e infine si estrae una pallina a caso. Sia $B$ l'evento "la pallina estratta è bianca".
1) Calcolare $P(B)$. 2) Calcolare la probabilità di aver messo esattamente $k$ palline bianche sapendo di aver estratto una pallina bianca, al variare di $k\in\{0,1,\dots,n\}$.

**Svolgimento.**
1) Per la formula delle probabilità totali, con $P(B|X=k)=\frac{k}{n}$ e $P(X=k)=\binom{n}{k}p^{k}(1-p)^{n-k}$ (perché $X\sim BIN(n,p)$), $$P(B)=\sum_{k=0}^{n}P(B|X=k)P(X=k)=\frac{1}{n}\sum_{k=0}^{n}k\binom{n}{k}p^{k}(1-p)^{n-k}=\frac{1}{n}\,\mathbb{E}[X]=\frac{1}{n}\cdot np=p,$$dove $\mathbb{E}[X]=np$ è un risultato già visto.
2) Si chiede $P(X=k|B)$ e si usa la formula di Bayes, con $P(B)=p$ calcolata prima: $$P(X=k|B)=\frac{P(B|X=k)P(X=k)}{P(B)}=\frac{\frac{k}{n}\binom{n}{k}p^{k}(1-p)^{n-k}}{p}=\begin{cases}0 & k=0 \\ \binom{n-1}{k-1}p^{k-1}(1-p)^{n-1-(k-1)} & k=1,\dots,n\end{cases}$$perché per $k\geq1$ si ha $\frac{k}{n}\cdot\frac{n!}{k!(n-k)!}=\frac{(n-1)!}{(k-1)!(n-k)!}$, e $p^{k}/p=p^{k-1}$, $n-k=n-1-(k-1)$.
*Commenti.* $P(X=0|B)=0$ è in accordo con $\{X=0\}\cap B=\varnothing$ (se $X=0$ l'urna ha tutte palline nere e $B$ non si può verificare). Con $h=k-1\in\{0,1,\dots,n-1\}$ si ha $P(X-1=h|B)=\binom{n-1}{h}p^{h}(1-p)^{n-1-h}$: in conclusione $X\sim BIN(n,p)$ e $X-1\,|\,B\sim BIN(n-1,p)$. Insomma, se $B$ si verifica, una moneta ha dato testa e, per gli altri $n-1$ lanci, il numero di teste ha ancora una distribuzione binomiale, come se ci fosse un lancio in meno.
### Estrazioni con reinserimento: multinomiale (lezione 23, pp. 4-8)
Un'urna ha $6$ palline bianche, $2$ rosse e $1$ nera; si estraggono $3$ palline a caso, una alla volta e **con** reinserimento. In ogni prova $p_{B}=\frac{6}{9}=\frac{2}{3}$, $p_{R}=\frac{2}{9}$, $p_{N}=\frac{1}{9}$. Calcolare la probabilità di: 1) $3$ colori tutti diversi; 2) $3$ colori tutti uguali; 3) la sequenza $(B,R,B)$; 4) $2$ bianche e $1$ rossa complessivamente; 5) trovare la densità di $X$ = numero di palline bianche estratte, con media e varianza.
1) Si intende "$1B,1R,1N$ in qualsiasi ordine": per la multinomiale $\frac{3!}{1!\,1!\,1!}\cdot\frac{6}{9}\cdot\frac{2}{9}\cdot\frac{1}{9}=6\cdot\frac{12}{729}=\frac{8}{81}$.
2) Unione disgiunta di "$3B$ o $3R$ o $3N$": $\left(\frac{6}{9}\right)^{3}+\left(\frac{2}{9}\right)^{3}+\left(\frac{1}{9}\right)^{3}=\frac{216+8+1}{729}=\frac{225}{729}=\frac{25}{81}$.
3) Con notazioni ovvie $P(B_{1}\cap R_{2}\cap B_{3})=P(B_{1})P(R_{2})P(B_{3})=\left(\frac{6}{9}\right)^{2}\frac{2}{9}=\frac{8}{81}$ (eventi legati a estrazioni diverse sono indipendenti, perché c'è reinserimento).
4) "$2B$ e $1R$" equivale a "$2B,1R,0N$": $\frac{3!}{2!\,1!\,0!}\left(\frac{6}{9}\right)^{2}\frac{2}{9}\left(\frac{1}{9}\right)^{0}=3\cdot\frac{4}{9}\cdot\frac{2}{9}=\frac{24}{81}=\frac{8}{27}$.
5) Non importa distinguere tra rosse e nere, ma tra bianche e non bianche: $X\sim BIN(n=3,p=\frac{6}{9}=\frac{2}{3})$ e $$p_{X}(k)=\binom{3}{k}\left(\tfrac{2}{3}\right)^{k}\left(1-\tfrac{2}{3}\right)^{3-k}=\begin{cases}1/27 & k=0 \\ 6/27 & k=1 \\ 12/27 & k=2 \\ 8/27 & k=3\end{cases}\quad(\text{somma }1).$$ Per le formule della binomiale $\mathbb{E}[X]=np=3\cdot\frac{2}{3}=2$ e $\mathrm{Var}[X]=np(1-p)=3\cdot\frac{2}{3}\cdot\frac{1}{3}=\frac{2}{3}$; del resto $\mathbb{E}[X]=\frac{0+6+24+24}{27}=2$ e $\mathrm{Var}[X]=\mathbb{E}[X^{2}]-\mathbb{E}^{2}[X]=\frac{0+6+48+72}{27}-4=\frac{126-108}{27}=\frac{2}{3}$.

*Commento.* Dalla domanda 4) $P(2B,1R)=\frac{8}{27}$ e in modo analogo $P(2B,1N)=\frac{3!}{2!\,0!\,1!}\left(\frac{6}{9}\right)^{2}\left(\frac{1}{9}\right)=\frac{12}{81}=\frac{4}{27}$; dalle proprietà della misura di probabilità $P(2B)=P(2B,1R)+P(2B,1N)=\frac{8}{27}+\frac{4}{27}=\frac{12}{27}=p_{X}(2)$, come nella risposta 5).
### Estrazioni senza reinserimento: ipergeometrica (lezione 23, pp. 9-13)
Un'urna ha $3$ palline bianche, $2$ rosse e $3$ nere; si estraggono $3$ palline a caso, una alla volta e **senza** reinserimento. Calcolare la probabilità di: 1) $3$ colori tutti diversi; 2) $3$ colori tutti uguali; 3) la sequenza $(R,R,B)$; 4) $1$ bianca e $2$ rosse complessivamente; 5) almeno una rossa; 6) una pallina bianca; 7) media e varianza di $X$, numero di palline bianche estratte.
1) "$1B,1R,1N$ in qualsiasi ordine": $\frac{\binom{3}{1}\binom{2}{1}\binom{3}{1}}{\binom{8}{3}}=\frac{18}{56}=\frac{9}{28}$.
2) Unione disgiunta di "$3B$ o $3R$ o $3N$" (il caso $3R$ è impossibile, perché le rosse sono $2$): $\frac{\binom{3}{3}\binom{2}{0}\binom{3}{0}}{\binom{8}{3}}+0+\frac{\binom{3}{0}\binom{2}{0}\binom{3}{3}}{\binom{8}{3}}=\frac{1}{56}+\frac{1}{56}=\frac{1}{28}$.
3) Con la regola del prodotto $P(R_{1}\cap R_{2}\cap B_{3})=P(R_{1})P(R_{2}|R_{1})P(B_{3}|R_{1}\cap R_{2})=\frac{2}{8}\cdot\frac{1}{7}\cdot\frac{3}{6}=\frac{1}{56}$.
4) "$1B,2R,0N$": $\frac{\binom{3}{1}\binom{2}{2}\binom{3}{0}}{\binom{8}{3}}=\frac{3}{56}$.
5) Conviene il complementare, pensando a palline rosse e non rosse (senza distinguere bianche e nere): $1-P(0\text{ rosse})=1-\frac{\binom{6}{3}\binom{2}{0}}{\binom{8}{3}}=1-\frac{20}{56}=\frac{36}{56}=\frac{9}{14}$.
6) Si pensa a bianche e non bianche: $\frac{\binom{3}{1}\binom{5}{2}}{\binom{8}{3}}=\frac{30}{56}=\frac{15}{28}$.
7) $X$ è ipergeometrica con $n=3$, $n_{1}=3$ (bianche) e $n_{1}+n_{2}=8$ totali: $\mathbb{E}[X]=3\cdot\frac{3}{8}=\frac{9}{8}$ (stessa media della "binomiale associata") e $$\mathrm{Var}[X]=3\cdot\frac{3}{8}\left(1-\frac{3}{8}\right)\cdot\frac{8-3}{8-1}=3\cdot\frac{3}{8}\cdot\frac{5}{8}\cdot\frac{5}{7}=\frac{225}{448}$$dove $\frac{8-3}{8-1}$ è il fattore correttivo ($8$ palline totali e $3$ estratte).

*Commento.* Dalle domande 1) e 4) $P(1B,1R,1N)=\frac{18}{56}$ e $P(1B,2R)=\frac{3}{56}$; con la stessa formula $P(1B,2N)=\frac{\binom{3}{1}\binom{2}{0}\binom{3}{2}}{\binom{8}{3}}=\frac{9}{56}$. Per le proprietà della misura di probabilità $P(1B)=P(1B,2R)+P(1B,2N)+P(1B,1R,1N)=\frac{3+9+18}{56}=\frac{30}{56}$, come nella risposta 6).
### Geometrica, binomiale negativa traslata, approssimazione di Poisson (lezione 23, pp. 14-15)
Un'urna ha $100$ palline numerate da $1$ a $100$; si estraggono palline a caso, una alla volta e **con** reinserimento. 1) Calcolare la probabilità di non estrarre i numeri da $1$ a $10$ nelle prime $5$ estrazioni. 2) Calcolare $\mathbb{E}[Z]$ e $\mathrm{Var}[Z]$, con $Z$ numero di estrazioni necessarie per avere per la 4ª volta un numero pari. 3) Calcolare la probabilità di estrarre $6$ volte il numero $79$ nelle prime $100$ estrazioni, usando l'approssimazione poissoniana della binomiale.
1) Sia $Y=\#$ estrazioni per avere per la 1ª volta un numero da $1$ a $10$: $Y\sim GeoTraslata(p=\frac{10}{100}=\frac{1}{10})$ e la probabilità richiesta è $P(Y\geq6)=\left(1-\frac{1}{10}\right)^{6-1}=\left(\frac{9}{10}\right)^{5}$ (formula per la coda; in forma di serie, $\sum_{h\geq6}\left(\frac{9}{10}\right)^{h-1}\frac{1}{10}=\frac{1}{10}\cdot\frac{(9/10)^{5}}{1-9/10}$).
2) $Z\sim BIN\text{-}NEG\text{-}traslata(r=4,p=\frac{50}{100}=\frac{1}{2})$, quindi $\mathbb{E}[Z]=r\cdot\frac{1}{p}=4\cdot2=8$ e $\mathrm{Var}[Z]=r\cdot\frac{1-p}{p^{2}}=4\cdot\frac{1/2}{1/4}=8$.
3) La probabilità richiesta è $P(X=6)$ con $X\sim BIN(n=100,p=\frac{1}{100})$, cioè $\binom{100}{6}\left(\frac{1}{100}\right)^{6}\left(\frac{99}{100}\right)^{94}$. Con l'approssimazione poissoniana ($\lambda=np=1$): $$P(X=6)\approx\frac{\left(100\cdot\frac{1}{100}\right)^{6}}{6!}e^{-100\cdot\frac{1}{100}}=\frac{e^{-1}}{720}\approx5{,}1\cdot10^{-4}.$$

> [!warning] Correzione alla slide 15
> Nella slide 15 della lezione 23 erano scritti $\mathrm{Var}[Z]=2$ e $P(X=6)\approx\frac{e^{-1}}{120}$; il foglio `lezione23-correzioni-slide-15.pdf` li corregge in $\mathrm{Var}[Z]=8$ (infatti $4\cdot\frac{1/2}{1/4}=8$) e $P(X=6)\approx\frac{e^{-1}}{720}$ (perché $6!=720$, non $120$). Qui sono riportati i valori corretti.
### Due giocatori con geometriche indipendenti (lezione 23, pp. 24-25)
Due giocatori: il primo lancia ripetutamente una moneta equa fino a quando esce per la 1ª volta testa; il secondo lancia ripetutamente due monete eque fino a quando escono per la 1ª volta due teste. Siano $X_{1}$ e $X_{2}$ i numeri di lanci effettuati dal primo e dal secondo giocatore. Calcolare: 1) $P(X_{1}=2X_{2})$; 2) $P(X_{1}+X_{2}=4)$; 3) $P(X_{1}\geq X_{2})$; 4) $P(X_{1}=X_{2}|X_{1}+X_{2}=4)$.

**Svolgimento.** $X_{1}$ e $X_{2}$ sono indipendenti e geometriche traslate di parametri $p_{1}=\frac{1}{2}$ e $p_{2}=\frac{1}{4}$. Quindi $$p_{\underline{X}}(x_{1},x_{2})=\left(1-\tfrac{1}{2}\right)^{x_{1}-1}\tfrac{1}{2}\left(1-\tfrac{1}{4}\right)^{x_{2}-1}\tfrac{1}{4}=\left(\tfrac{1}{2}\right)^{x_{1}}\left(\tfrac{3}{4}\right)^{x_{2}-1}\tfrac{1}{4}\quad\quad\text{per }x_{1},x_{2}\geq1\text{ interi.}$$
1) $P(X_{1}=2X_{2})=\sum_{k=1}^{\infty}p_{\underline{X}}(2k,k)=\sum_{k\geq1}\left(\tfrac{1}{2}\right)^{2k}\left(\tfrac{3}{4}\right)^{k-1}\tfrac{1}{4}=\frac{1/4}{3/4}\sum_{k\geq1}\left(\tfrac{1}{4}\cdot\tfrac{3}{4}\right)^{k}=\frac{1}{3}\cdot\frac{3/16}{1-3/16}=\frac{1}{13}$.
2) $P(X_{1}+X_{2}=4)=p_{\underline{X}}(1,3)+p_{\underline{X}}(2,2)+p_{\underline{X}}(3,1)=\frac{1}{2}\cdot\frac{9}{16}\cdot\frac{1}{4}+\frac{1}{4}\cdot\frac{3}{4}\cdot\frac{1}{4}+\frac{1}{8}\cdot1\cdot\frac{1}{4}=\frac{9+6+4}{128}=\frac{19}{128}$.
3) $P(X_{1}\geq X_{2})=\sum_{x_{2}\geq1}\sum_{x_{1}\geq x_{2}}\left(\tfrac{1}{2}\right)^{x_{1}}\left(\tfrac{3}{4}\right)^{x_{2}-1}\tfrac{1}{4}$: si somma prima in $x_{1}$ (serie geometrica $\sum_{x_{1}\geq x_{2}}(\frac{1}{2})^{x_{1}}=\frac{(1/2)^{x_{2}}}{1/2}$) e poi in $x_{2}$: $=\frac{1/4}{3/4}\cdot\frac{1}{1/2}\sum_{x_{2}\geq1}\left(\tfrac{3}{8}\right)^{x_{2}}=\frac{2}{3}\cdot\frac{3/8}{5/8}=\frac{2}{5}$.
4) $P(X_{1}=X_{2}|X_{1}+X_{2}=4)=\frac{P(\{X_{1}=X_{2}\}\cap\{X_{1}+X_{2}=4\})}{P(X_{1}+X_{2}=4)}=\frac{p_{\underline{X}}(2,2)}{19/128}=\frac{3/64}{19/128}=\frac{6}{19}$ (il numeratore è $p_{\underline{X}}(2,2)=\frac{3}{64}$ calcolato in 2)).
### Congiunta con due famiglie di punti (lezione 23, pp. 21-23)
Si consideri la densità congiunta $$p_{\underline{X}}(k,k)=\left(\tfrac{1}{2}\right)^{k+1}\text{ per }k\geq1\text{ intero};\qquad p_{\underline{X}}(k,1)=\left(\tfrac{1}{2}\right)^{k}\text{ per }k\geq2\text{ intero}$$(i punti sono sulla diagonale e sulla retta $x_{2}=1$; è ben posta, perché $\sum_{k\geq1}(\frac{1}{2})^{k+1}=\frac{1}{2}$ e $\sum_{k\geq2}(\frac{1}{2})^{k}=\frac{1}{2}$). Calcolare: 1) $P(X_{1}=X_{2})$; 2) $P(X_{2}=1)$; 3) $P(X_{1}=X_{2}|X_{2}=1)$; 4) $P(X_{2}=1|X_{1}=X_{2})$; 5) la densità di $Y=X_{1}+X_{2}$.
1) $P(X_{1}=X_{2})=\sum_{k\geq1}p_{\underline{X}}(k,k)=\frac{1}{2}\sum_{k\geq1}\left(\tfrac{1}{2}\right)^{k}=\frac{1}{2}$.
2) $P(X_{2}=1)=p_{\underline{X}}(1,1)+\sum_{k\geq2}\left(\tfrac{1}{2}\right)^{k}=\frac{1}{4}+\frac{1/4}{1/2}=\frac{1}{4}+\frac{1}{2}=\frac{3}{4}$.
3) $P(X_{1}=X_{2}|X_{2}=1)=\frac{p_{\underline{X}}(1,1)}{P(X_{2}=1)}=\frac{1/4}{3/4}=\frac{1}{3}$.
4) $P(X_{2}=1|X_{1}=X_{2})=\frac{p_{\underline{X}}(1,1)}{P(X_{1}=X_{2})}=\frac{1/4}{1/2}=\frac{1}{2}$.
5) $Y$ assume valori interi $\geq2$ (il valore $2$ si ottiene come $1+1$; poi i valori sono maggiori). Per $h\geq2$ dispari $\{Y=h\}=\{X_{1}=h-1\}\cap\{X_{2}=1\}$; per $h=2$ $\{Y=2\}=\{X_{1}=1\}\cap\{X_{2}=1\}$; per $h>2$ pari $\{Y=h\}=\left(\{X_{1}=\frac{h}{2}\}\cap\{X_{2}=\frac{h}{2}\}\right)\cup\left(\{X_{1}=h-1\}\cap\{X_{2}=1\}\right)$. Quindi $$p_{Y}(h)=\begin{cases}\left(\frac{1}{2}\right)^{h-1} & h\geq3\text{ dispari} \\ \frac{1}{4} & h=2 \\ \left(\frac{1}{2}\right)^{\frac{h}{2}+1}+\left(\frac{1}{2}\right)^{h-1} & h>2\text{ pari}\end{cases}$$e, come controllo, $\sum_{h\geq2}p_{Y}(h)=\frac{1}{4}+\sum_{j\geq2}\left[\left(\tfrac{1}{2}\right)^{j+1}+\left(\tfrac{1}{2}\right)^{2j-1}\right]+\sum_{j\geq1}\left(\tfrac{1}{2}\right)^{2j}=\frac{1}{4}+\frac{1}{4}+\frac{1}{6}+\frac{1}{3}=1$.
### $P(E|\,\cdot\,)$ non è una misura di probabilità (lezione 23, pp. 26-28)
Un'urna ha $6$ palline numerate da $1$ a $6$; si estraggono $3$ palline a caso, una alla volta e **senza** reinserimento. Sia $X$ il numero di palline estratte con numero dispari e $E=\{\text{estratta la pallina }1\text{ alla 1ª estrazione}\}$, con $P(E)=\frac{1}{6}$. 1) Trovare la densità di $X$. 2) Calcolare $P(X=k|E)$ e $P(E|X=k)$ per $k\in\{0,1,2,3\}$.

**Svolgimento.**
1) $X$ è ipergeometrica: $p_{X}(k)=\frac{\binom{3}{k}\binom{3}{3-k}}{\binom{6}{3}}$, cioè $\frac{1}{20}$ per $k=0,3$ e $\frac{9}{20}$ per $k=1,2$ (somma $\frac{1}{20}+\frac{9}{20}+\frac{9}{20}+\frac{1}{20}=1$).
2) Si calcolano prima i numeratori $P(\{X=k\}\cap E)$: $$\begin{cases}P(\{X=0\}\cap E)=0 & \text{(intersezione vuota)} \\ P(\{X=1\}\cap E)=P(\{(1,\text{pari},\text{pari})\})=\frac{1}{6}\cdot\frac{3}{5}\cdot\frac{2}{4}=\frac{1}{20} \\ P(\{X=2\}\cap E)=P(\{(1,3\text{ o }5,\text{pari})\})+P(\{(1,\text{pari},3\text{ o }5)\})=\frac{1}{6}\cdot\frac{2}{5}\cdot\frac{3}{4}+\frac{1}{6}\cdot\frac{3}{5}\cdot\frac{2}{4}=\frac{1}{20}+\frac{1}{20}=\frac{1}{10} \\ P(\{X=3\}\cap E)=P(\{(1,3,5)\})+P(\{(1,5,3)\})=2\cdot\frac{1}{6}\cdot\frac{1}{5}\cdot\frac{1}{4}=\frac{1}{60}\end{cases}$$Quindi $P(X=k|E)=\frac{P(\{X=k\}\cap E)}{1/6}=6\,P(\{X=k\}\cap E)$, cioè $0,\frac{3}{10},\frac{6}{10},\frac{1}{10}$ per $k=0,1,2,3$. La somma è $\frac{0+3+6+1}{10}=1$, in accordo con la teoria, perché $\{\{X=k\}:k\in\{0,1,2,3\}\}$ è una partizione e $P(\cdot|E)$ è una misura di probabilità.
   Per $P(E|X=k)=\frac{P(E\cap\{X=k\})}{P(X=k)}$ gli stessi numeratori hanno denominatori $p_{X}(k)$ (che cambiano): $$P(E|X=k)=\begin{cases}0 & k=0 \\ \frac{1/20}{9/20}=\frac{1}{9} & k=1 \\ \frac{1/10}{9/20}=\frac{2}{9} & k=2 \\ \frac{1/60}{1/20}=\frac{1}{3} & k=3\end{cases}$$e la somma è $0+\frac{1}{9}+\frac{2}{9}+\frac{1}{3}=\frac{2}{3}\neq1$.

> [!question] Domanda tipica d'esame
> La somma $\sum_{k}P(E|X=k)$ sulla partizione $\{\{X=k\}\}_{k}$ deve valere $1$?
> **Risposta.** No. Vale $\sum_{k}P(\{X=k\}|E)=1$, perché $P(\cdot|E)$ è una misura di probabilità e $\{\{X=k\}\}_{k}$ è una partizione; invece $P(E|\,\cdot\,)$ (con $E$ fissato e il condizionamento che varia) non è una misura di probabilità e non c'è alcun motivo per cui la somma sia $1$. Nell'esercizio si ottiene $0+\frac{1}{9}+\frac{2}{9}+\frac{1}{3}=\frac{2}{3}\neq1$.
