In questo capitolo tratteremo essenzialmente Variabili Aleatorie Discrete (spesso definite su spazi di probabilità ($\ohm,\mathcal{A},P$) con $r$ discreto, cioè finito o numerabile).

In ogni caso nella parte iniziale di questa lezione diremo alcune cose sulle variabili aleatorie in generale. Spesso useremo l'abbreviazione "v.a.".

In generale una v.a. (definita su uno spazio di probabilità ($\ohm,\mathcal{A},P$)) è una funzione del tipo $$X:\ohm\to\mathcal{X}$$dove $\mathcal{X}$ è un qualche insieme, e con certe proprietà.

In questo corso tratteremo il caso in cui $X=\mathbb{R}$ (o un suo sottoinsieme); in qualche caso considereremo il caso $\mathcal{X}=\mathbb{R}^{n}$ per qualche $n\geq 2$ (però solo per v.a. discrete).

Il concetto di v.a. è utile perché spesso gli eventi di interesse negli esercizi sono esprimibili tramite v.a.. Consideriamo un esempio.

#### Esempio
Si lanciano due dadi equi e consideriamo l'evento "la somma dei due numeri ottenuti è uguale a 5". Allora è utile fare riferimento alla seguente scelta dell'insieme $\ohm$: $$\ohm=\{1,\dots,6\}\times\{1,\dots,6\}=\{w=(w_{1},w_{2}):w_{1},w_{2}\in\{1,\dots,6\}\}$$Essendo $\ohm$ un insieme finito, non ci sono problemi nello scegliere $\mathcal{A}=P(\ohm)$

Inoltre è opportuno considerare la seguente funzione $X:\ohm\to\mathbb{R}$ (che è una v.a.) definita come segue: $$\begin{array}{}
X(w)=X(w_{1},w_{2})=w_{1}+w_{2} & (\forall\ w=(w_{1},w_{2})\in\ohm)
\end{array}$$Allora l'evento di interesse è $$\{w=(w_{1},w_{2})\in\ohm:X(w)=5\}$$
### Definizione
Sia $(\ohm,\mathcal{A},P)$ uno spazio di probabilità. Inoltre sia $X:\ohm\to \mathbb{R}$ una funzione.
Allora la funzione $X$ è una v.a. (reale) se vale la seguente condizione $$\forall\ t\in\mathbb{R}\quad\quad\{w\in\ohm:X(w)\leq t\}\in\mathcal{A}$$In altri termini si richiede che le controimmagini delle semirette del tipo $(-\infty,t]$ (al variare di $t\in\mathbb{R}$), che sono sottoinsiemi di $\ohm$, siano elementi della $\delta$-algebra $\mathcal{A}$.

Questo consente di dire che, per queste controimmagini, è possibile definire la probabilità.
Quindi possiamo dire che, per ogni $t\in\mathbb{R}$, $P(\{w\in\ohm:X(w)\leq t\})$ è un numero ben definito.

Quindi si richiede che, se $B=(-\infty,t]$ per una qualsiasi scelta di $t\in\mathbb{R}$, $$\{w\in\ohm:X(w)\in B\}\in\mathcal{A}\quad\quad\quad(*)$$A partire da questa richiesta, condizione di $(*)$ vale anche per le altre scelte di $B$ "naturali" da considerare: $$\begin{array}{l|l}
B=[t,+\infty) &  \\
B=(t,+\infty) & \text{per ogni }t\in\mathbb{R} \\
B=(-\infty,t)
\end{array}$$$B=[s,t], B=(s,t), B=[s,t), B=(s,t]$ per ogni $s,t\in\mathbb{R}$ con $s<t$
$B=\{t\}$ per ogni $t\in\mathbb{R}$

$B$ unione finita o numerabile di insiemi dei tipi indicati sopra. 
(es. $B=(0,1)\cup\{2\}\cup[4,5)\cup[6,+\infty)$)

#### Notazioni che useremo
$\{w\in\ohm:X(w)\in B\}\longrightarrow$ useremo la notazione $\{X\in B\}$
$P(\{w\in\ohm:X(w)\in B\})\longrightarrow$ useremo la notazione $P(\{X\in B\})$, o anche $P(X\in B)$

### Distribuzione o legge di una v.a. reale
È la corrispondenza tra "gli insiemi della retta $B$ per cui $\{X\in B\}\in\mathcal{A}$" e i valori $P(\{X\in B\})$ relativi.

### Funzione di distribuzione di una v.a. reale
È la funzione $F_{X}:\mathbb{R}\to[e,1]$ così definita: $F_{X}(t)=P(X\leq t)$

#### Commento (importante)
La conoscenza di $F_{X}$ consente di individuare la distribuzione di una v.a. $X$.
Quindi, se uno conosce i valori di $P(X\in B)$ per $B=(-\infty,t]$ (al variare di tutti i valori di $t\in\mathbb{R}$), è possibile conoscere tutti i valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$

### Proprietà della funzione di distribuzione $F_{X}$
1) $F_{X}$ non è decrescente, cioè  $F_{X}(t_{1})\leq F_{X}(t_{2})\quad\quad\forall\ t_{1},t_{2}\in\mathbb{R}$ tali che $t_{1}\leq t_{2}$
   Questo si verifica facilmente osservando che
   $t_{1}\leq t_{2}\implies(-\infty,t_{1}]\subset(-\infty,t_{2}]\implies P(X\leq t_{1})\leq P(X\leq t_{2})\implies F_{X}(t_{1})\leq F_{X}(t_{2})$
   
2) $\displaystyle\lim_{t\to-\infty}F_{X}(t)=0$ e $\displaystyle\lim_{t\to+\infty}F_{X}(t)=1$
   
3) $F_{X}$ è continua a destra, cioè $\forall\ t_{0}\in\mathbb{R}\quad\quad\displaystyle\lim_{t\to t_{0}^{+}}F_{X}(t)=F_{X}(t_{0})$
-- Da inserire immagine da pagina 6 pdf lezione 5--

#### Digressione
C'è una parte dei libri (una minoranza) che definisce la funzione di distribuzione in questo modo: $$F_{X}(t)=P(X<t)\quad\quad(\text{per ogni }t\in\mathbb{R})$$In questo caso le proprietà viste prima continuano a valere, tranne che la continuità a destra. In questo caso si ha che $F_{X}$ è continua a sinistra $$\lim_{t\to t_{0}^{-}}F_{X}(t)=F_{X}(t_{0})$$

### Variabili aleatorie discrete
Sia $X:\ohm\to \mathbb{R}$ una v.a. (reale) definita su uno spazio di probabilità $(\ohm,\mathcal{A},P)$.
Indichiamo con $\delta_{\mathcal{X}}$ l'insieme dei valori assunti da $X$, cioè l'immagine di $X$ vista come funzione.

La definizione di questo insieme in termini matematici è la seguente: $$\delta_{\mathcal{X}}=\{x\in\mathbb{R}: \exists\ w\in\ohm\text{ tale che }X(w)=x\}$$

### Definizione
Una v.a. (reale) $X$ è una v.a. discreta se l'insieme $\delta_{\mathcal{X}}$ è discreto (cioè $\delta_{\mathcal{X}}$ è finito o numerabile).

#### Osservazione
Se $\ohm$ è discreto, allora $X$ è una v.a. discreta.
In generale non vale il viceversa:  ad esempio si pensi al caso in cui, per qualche $c\in\mathbb{R}$ si ha $$X(w)=c\quad\quad\forall\ w\in\ohm$$(quindi $\delta_{\mathcal{X}}=\{c\}$) e $X$ non è un insieme discreto.



Quando $X$ è una v.a. discreta, allora possiamo pensare di avere $$\delta_{\mathcal{X}}=\{x_{i}\}_{i\in I}\quad\quad I\text{ è  un insieme discreto}$$In corrispondenza, per ogni $B\in\mathbb{R}$ si ha $$\begin{array}{}
P(X\in B)=P(X\in B\cap \delta_{\mathcal{X}})=P(X\in B\cap(\underset{i\in I}{\cup}\{x_{i}\}))=\displaystyle\sum_{i\in I}P(X\in B\cap\{x_{i}\})= \\
\underset{\underset{\text{somme finite o semi}\Rightarrow}{}}{=}\displaystyle\sum_{x_{i}\in\delta_{\mathcal{X}}\cap B}P(X=x_{i})
\end{array}$$Quindi la distribuzione di una v.a. discreta $X$, cioè la conoscenza dei valori di $P(X\in B)$ al variare di $B\subset \mathbb{R}$, è individuata dalla conoscenza di $\delta_{X}=\{x_{i}\}_{i\in I}$ e delle probabilità $\{P(X=x_{i})\}_{i\in I}$.

Si osservi anche che, per $B=\mathbb{R}$, si ha $$\underset{=1}{\underbrace{P(X\in\mathbb{R})}} =\displaystyle\sum_{x_{i}\in\underset{=\delta_{\mathcal{X}}}{\underbrace{\delta_{\mathcal{X}}\cap\mathbb{R}}}}$$da cui segue $$\begin{bmatrix}
\displaystyle\sum_{x_{i}\in\delta_{\mathcal{X}}}P(X=x_{i})=1
\end{bmatrix}$$

#### Osservazione
Possiamo anche dire che $$\displaystyle\sum_{\begin{array}{}
x_{i}\in\delta_{\mathcal{X}} \\
P(X=x_{i})>0
\end{array}}P(X=x_{i})=1$$



Più in generale si può considerare la funzione $P_{\mathcal{X}}:\mathbb{R}\to[0,1]$ così definita: $$ P_{\mathcal{X}}(x)=P(X=x)\quad\quad\forall\ x\in\mathbb{R}$$Tale funzione è detta **Densità Discreta** della v.a. $X$.

### Proposizione 
$x\not\in\delta_{X}\implies P_{X}(x)=0$

#### Dimostrazione 
Si ha $$P_{X}(x)=P(\underset{=\varnothing\ (\ x\ \not\in\ \delta_{X})}{\underbrace{\{w\in\ohm:X(w)=x\}}})=P(\varnothing)=0$$Come vedremo successivamente la funzione di distribuzione ha maggiore interesse quando la v.a. $X$ è continua.
In ogni caso vedremo come è fatta $F_{X}$ nel caso di v.a. discrete. Iniziamo con il caso in cui $\delta_{X}$ è un *insieme finito*; ad esempio $\delta_{X}=\{x_{1},\dots,x_{n}\}$ con $x_{1}<\dots<x_{n}$.
In questo grafico si ha $n=3$ 

--- pagina 12 pdf 05 ---

#### Osservazione
Dal grafico (caso $n=3$) si vede che $$\underset{=P_{X}(x_{1})+P_{X}(x_{2})+P_{X}(x_{3})}{\underbrace{\displaystyle\sum_{i=1}^{n}P_{X}(x_{i})}}=1$$


Nel caso in cui $\delta_{X}$ è *infinito numerabile* la casistica è più varia e ci possono essere casi molto complicati. Qui faccio riferimento a due casi (soprattutto il primo ci interessa in vista di ciò che vedremo con le distribuzioni di Poisson e geometriche)
1) $\delta_{X}=\{x_{e},x_{e}+1,x_{e}+2,\dots\}$
2) $\delta_{X}=\left\{ 1,\frac{1}{2},\frac{1}{3},\dots,\frac{1}{n},\dots\right\}$


### Introduzione alle distribuzioni notevoli
Si parla di "distribuzione notevole" quando queste hanno certe espressioni (eventualmente dipendente da qualche parametro), un po' come accade per i prodotti notevoli nel calcolo letterale.

Per le v.a. discrete tipicamente ci si riferisce alla espressione delle densità discrete. Talvolta si fa riferimento ad alcune situazioni pratiche (modalità di "effettuare prove", ad esempio estrazioni casuali di oggetti).

Per le v.a. continue tipicamente ci si riferisce alle espressioni delle funzioni di distribuzioni o, equivalentemente (più o meno) alle densità continue $[$ancora non abbiamo parlato di densità continue$]$


### Distribuzione Bernoulliana
Si usa questo termine quando $\delta_{X}=\{0,1\}$.
Talvolta è utile pensare ad un evento $B\in \mathcal{A}$ tale che $$\begin{array}{l}
X=1 & \iff & \text{l'evento }B\text{ si verifica} \\
X=0 & \iff & \text{l'evento }B\text{ non si verifica}
\end{array}$$Talvolta si usa anche la notazione $X=1_{B}$
In questo caso si ha $$\begin{cases}
P_{X}(1)=P(X=1)=P(B) \\
P_{X}(0)=P(X=0)=P(B^{c})
\end{cases}$$
Quindi 
- se $0<P(B)<1$ (e quindi $0<P(B^{c})<1$)
  --- vedere primo grafico pag 16 pdf lezione05 ---
- se $P(B)=1$ (e quindi $P(B^{c})=0$)
  --- vedere secondo grafico pag 16 pdf lezione05 ---
- se $P(B)=0$ (e quindi $P(B^{c})=1$)
  --- vedere terzo grafico pag 16 pdf lezione05 ---

### Schemi Successo-Fallimento su un numero finito di prove
Si tratta di una premessa comune per due casi che vedremo nella prossima lezione:
1) **Distribuzione Binomiale** (caso di $n$ prove indipendenti, tutte con la stessa probabilità di successo $P$)
2) **Distribuzione Ipergeometrica** (caso di $n$ estrazioni casuali di un oggetto alle volte senza reinserimento (un caso particolare senza avere prove indipendenti)) ^8912f8

#### Osservazione
Nel caso [[#^8912f8|2)]] otterremo nuovamente le formule delle estrazioni casuali in blocco già viste in passato


In entrambi i casi si vuole studiare la v.a. $X$ che conta il numero di successi.
Nel caso [[#^8912f8|2)]] gli oggetti sono di due tipi, e si ha successo con l'estrazione di oggetti di un certo tipo. Ad esempio: 
oggetti colorati con un certo colore,
oggetti numerati con un certo numero,
ecc.

In entrambi i casi conviene fare riferimento all'insieme $\ohm$ così definito: $$\ohm=\underset{n\text{ volte}}{\underbrace{\{0,1\}\times\dots\times\{0,1\}}}= \{w=(w_{1},\dots,w_{n}):w_{1},\dots,w_{n}\in\{0,1\}\}$$Ogni punto $w\in\ohm$ ???? i possibili risultati (successi o fallimenti) nelle $n$ prove.
Sceglieremo $\mathcal{A}=P(\ohm)$.
Avremo due diverse misure di probabilità $P$ per i casi 1) e 2).

#### Osservazione
- Per $n=1$ abbiamo ovviamente una distribuzione Bernoulliana
- In generale si dovrà avere $\delta_{X}=\{0,1,\dots,n\}$ e questo è quel che accadrà.



Noi siamo interessati a contare successi (cioè quanti "1") ci sono nella stringa dei risultati. 
Allora è opportuno considerare le v.a. così definite: $$X(w)=w_{1}+\dots+w_{n}\quad\quad\forall\ w=(w_{1},\dots,w_{n})\in\ohm$$
#### Osservazione
Ad esempio la v.a. $Y$ che conta il numero di fallimenti è $Y$ così definita: $$Y(w)=n-X(w)\quad\quad\forall\ w=(w_{1},..,w_{n})\in\ohm$$
Del resto $Y(w)=(1+\dots+1)-(w_{1}+\dots+w_{n})=1-w_{1}+\dots+1-w_{n}$ (che in effetti conta il numero di "0" nella stringa dei risultati)

Nella prossima lezione vedremo come definire le misure di probabilità $P$ su $(\ohm,\mathcal{A})=(\ohm,P(\ohm))$ a partire dagli insiemi costruiti dai singoli punti, cioè a partire dalle seguenti quantità: $$P(\{w\})=P(\{(w_{1},\dots,w_{n})\})\quad\quad\forall\ w=(w_{1},\dots,w_{n})\in\ohm$$Due diverse situazioni per i casi 1) e 2).

Dopo aver fatto questo troveremo la densità discreta di $X$:
per $k\in\{0,1,\dots,n\}\quad\quad P_{X}(K)=P(X=K)=P(\{w\in\ohm:X(w)=K\})=\displaystyle\sum_{w:X(w)=K}P(\{w\})$
Per fissare le idee consideriamo il caso $n=3$.
Abbiamo $\ohm=\{0,1\}\times\{0,1\}\times\{0,1\}=\{w=(w_{1},w_{2},w_{3}):w_{1},w_{2},w_{3}\in\{0,1\}\}$

Allora "le sequenze $w$ per cui $X(w)=K$" sono: $$\begin{array}{l}
\text{per }k=0 & &  (0,0,0) \\
\text{per }k=1 & &  (0,0,1),(0,1,0),(1,0,0) \\
\text{per }k=2 & &  (0,1,1),(1,0,1),(1,1,0) \\
\text{per }k=3 & &  (1,1,1) \\
\end{array}$$Quindi $$\begin{array}{l}
P_{X}(0)=P(\{(0,0,0)\}) \\
P_{X}(1)=P(\{(0,0,1)\})+P(\{(0,1,0)\})+P(\{(1,0,0,)\}) \\
P_{X}(2)=P(\{(0,1,1)\})+P(\{(1,0,1)\})+P(\{(1,1,0)\}) \\
P_{X}(3)=P(\{(1,1,1)\})
\end{array}$$

--- Fine lezione 05 ---


Qui abbiamo un altra cosa che accadrà nei due casi che vedremo, nei casi 1) e 2) avremo che: $$X(w)=X(w')\implies P(\{w\}=P(\{w'\}))$$Cioè, date due qualsiasi sequenza $w$ e $w'$ con lo stesso numero di successi, le rispettive probabilità coincidono

Allora sarà conveniente dire che $$\begin{array}{}
\forall\ k\in\delta_{X}=\{0,1,\dots,n\},\quad\quad\text{esiste }q_{k}\text{ tale che} \\
X(w)=k\implies P(\{w\})=q_{k}
\end{array}$$
#### Esempio
con $n=3$, esistono $q_{0},q_{1},q_{2},q_{2}\geq 0$ tali che $$\begin{cases}
P(\{0,0,0\})=q_{0} \\
P(\{1,0,0\})=P(\{(0,1,0)\})=P(\{0,0,1\})=q_{1} \\
P(\{1,1,0\})=P(\{(1,0,1)\})=P(\{(0,1,1)\})=q_{2} \\
P(\{(1,1,1)\})=q_{3}
\end{cases}$$Ovviamente si dovrà avere $q_{0}+3q_{1}+3q_{2}+q_{3}=1$

In corrispondenza, se poniamo (nuova notazione)$$r_{n,k}=\#\{w:X(w)=k\}$$per ogni $k\in\delta_{X}=\{0,1,\dots,n\}$ si ha $$P_{X}(k)\overset{(*)}{=}\sum_{w:X(w)=k}P(\{w\})=\sum_{w:X(w)=k}q_{k}=\underset{r_{n,k}\text{ volte}}{\underbrace{q_{k}+\dots+q_{k}}}=r_{n,k}\cdot q_{k}$$Il valore di $q_{k}$ verrà determinato dalle ipotesi dei casi 1) e 2)
Il valore di $r_{n,k}$ possiamo calcolarlo facilmente e si ha: $r_{n,k}=\binom{n}{k}$
Quindi nei casi 1) e 2) avremmo $$P_{X}(k)=\binom{n}{k}q_{k}\quad\quad\text{ per }k\in\{0,1,\dots,n\}\quad\quad(\diamondsuit)$$

#### Proposizione
Si ha $r_{n,k}=\binom{n}{k}$

**Dimostrazione**
Ad ogni sequenza di lunghezza $n$ e con esattamente $k$ volte "1" possiamo abbinare il sottoinsieme di $\{1,\dots,n\}$ delle posizioni degli "1": $$\begin{array}{}
w=(w_{1},\dots,w_{n}) & \longleftrightarrow & \{i_{1},\dots,i_{k}\}\subset\{1,\dots,n\} \\
\text{osservazione 1} &  & \text{osservazione 2}
\end{array}$$
#### Osservazione 1
Il numero di stringhe di "questo tipo" è proprio $r_{n,k}=\#\{w:X(w)=k\}$

#### Osservazione 2
Noi sappiamo che i sottoinsiemi di "questo tipo" sono in tutto $\binom{n}{k}$



Si ha una **corrispondenza biunivoca** tra l'insieme di sequenze e l'insieme dei sottoinsiemi. Essendo una corrispondenza biunivoca tra due insiemi finiti, hanno lo stesso numero di elementi $\Box$ 


#### Esempio (corrispondenza biunivoca)
$n=4$,$k=2$ $$\begin{array}{}
\text{sequenze} &  & \text{sottoinsiemi} & (\text{sono }\binom{4}{2}=6) \\
(1,1,0,0) & \longleftrightarrow & \{1,2\} \\
(1,0,1,0) & \longleftrightarrow & \{1,3\} \\
(1,0,0,1) & \longleftrightarrow & \{1,4\} \\
(0,1,1,0) & \longleftrightarrow & \{2,3\} \\
(0,1,0,1) & \longleftrightarrow & \{2,4\} \\
(0,0,1,1) & \longleftrightarrow & \{3,4\}
\end{array}$$Questo spiega che abbiamo $r_{4,2}=6$ sequenze binarie di lunghezza 4 e con esattamente 2 volte "1".

### Caso 1): distribuzione binomiale
Si usa per le v.a. che conta il numero di successi su $n$ prove indipendenti, con probabilità di successo $p$ in ogni prova (quindi in ogni prova c'è una probabilità di fallimento $1-p$)

#### Esempi:
- $n$ lanci di moneta (o lanci di $n$ monete dello stesso tipo) e il successo è "esce testa" (oppure "esce croce")
- $n$ lanci di dado (o lanci di $n$ dadi dello stesso tipo) e il successo è "esce un numero in $S$" dove $S\subset\{1,2,3,4,5,6\}$ fissato
- $n$ estrazioni casuali di un oggetto alla volta con reinserimento da un insieme di $n_{1}$ oggetti di tipo 1 e $n_{2}$ oggetti di tipo 2; e il successo è "estratto il tipo 1" (oppure "estratto il tipo 2")

Dobbiamo attribuire i valori $P(\{w\})$ per $w\in\ohm$

#### Osservazione
$\#\ohm=2^{n}$



Per fissare le idee consideriamo il caso $n=3$. Si ha $\#\ohm=2^{3}=8$. $$\begin{array}{rrl}
P(\{(0,0,0)\})= & (1-p)(1-p)(1-p)= & (1-p)^{3}\\
P(\{(1,0,0)\})= & p(1-p)(1-p)= & p(1-p)^{2} \\
P(\{(0,1,0)\})= & (1-p)p(1-p)= & p(1-p)^{2} \\
P(\{(0,0,1)\})= & (1-p)(1-p)p= & p(1-p)^{2} \\
P(\{(1,1,0)\})= & p\cdot p(1-p)= & (1-p)p^{2} \\
P(\{(1,0,1)\})= & p(1-p)p= & (1-p)p^{2}\\
P(\{(0,1,1)\})= & (1-p)p\cdot p= & (1-p)p^{2} \\
P(\{(1,1,1)\})= & p\cdot p\cdot p= & p^{3}
\end{array}$$Si vede che $$\begin{array}{l}
X(w)=0\implies P(\{w\})=(1-p)^{3} & \longleftrightarrow  q_{0} \\
X(w)=1\implies P(\{w\})=p(1-p)^{2} & \longleftrightarrow q_{1} \\
X(w)=2\implies P(\{w\})=p^{2}(1-p) & \longleftrightarrow q_{2} \\
X(w)=3\implies P(\{w\})=p^{3} & \longleftrightarrow q_{3} \\
\end{array}$$

Ora consideriamo il caso generale. Si ha $$\begin{array}{}
P(w)= & \underset{1^{\text{a}}\text{ prova}}{\underbrace{p^{w_{1}}(1-p)^{1-w_{1}}}}\quad \underset{2^{\text{a}}\text{ prova}}{\underbrace{p^{w_{2}}(1-p)^{1-w_{2}}}}\quad\dots\quad\underset{n^{\text{a}}\text{ prova}}{\underbrace{p^{w_{n}}(1-p)^{1-w_{n}}}} \\
 & =p^{w_{1}+\dots+w_{n}}(1-p)^{1-w_{1}+1-w_{2}+\dots+1-w_{n}\quad\longleftrightarrow(n-(w_{1}+\dots+w_{n}))} \\
 & =p^{X(w)}(1-p)^{n-X(w)}
\end{array}$$

#### Osservazione
Per ogni $k\in\delta_{X}=\{0,1,\dots,n\}$ possiamo dire che:
per ogni $w$ tale che $X(w)=k$ si ha $$P(\{w\})=p^{k}(1-p)^{n-k}$$Quindi per ogni sequenza di $n$ prove con esattamente $k$ successi si ha la stessa probabilità.
Il valore $p^{k}(1-p)^{n-k}$ rappresenta il valore $q_{n}$ introdotto in passato.
A questo punto, con riferimento alla formula ($\diamondsuit$), si ha $$P_{X}(k)=\binom{n}{k}\underset{=q_{k}}{\underbrace{p^{k}(1-p)^{n-k}}}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$Questa è la densità discreta delle v.a. con distribuzione binomiale.
Abbiamo due parametri:$$\begin{cases}
n=\# \text{ delle prove indipendenti} \\
p=\text{probabilità di successo di ogni prova}
\end{cases}$$

#### Osservazioni
1) Si deve avere $\displaystyle\sum_{n=0}^{n}P_{X}(k)=1$. In effetti $\displaystyle\sum_{n=0}^{n}\binom{n}{k}p^{k}(1-p)^{n-k}=(p+(1-p))^{n}=1^{n}=1$
2) Per $p=\frac{1}{2}$