# Distribuzioni binomiale e ipergeometrica
Schemi successo-fallimento su un numero finito di prove: distribuzione bernoulliana, binomiale e ipergeometrica.
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

Talvolta si scrive $X\sim BIN(n,p)$.
#### Osservazioni
1) Si deve avere $\displaystyle\sum_{k=0}^{n}P_{X}(k)=1$. In effetti, per il **binomio di Newton**, $\displaystyle\sum_{k=0}^{n}\binom{n}{k}p^{k}(1-p)^{n-k}=(p+(1-p))^{n}=1^{n}=1$
2) Per $p=\frac{1}{2}$ si ha $1-p=\frac{1}{2}$; quindi la formula si semplifica un po': $$P_{X}(k)=\binom{n}{k}\left( \frac{1}{2} \right)^{n}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$
3) Per $p=0$ si ha $P_{X}(0)=1$ e $P_{X}(k)=0$ per $k\neq 0$.
   Per $p=1$ si ha $P_{X}(n)=1$ e $P_{X}(k)=0$ per $k\neq n$.
   (Come ci si aspetta; qui si usa la regola $0^{0}=1$.)
   Inoltre, se $0<p<1$, si ha $P_{X}(k)>0$ per ogni $k\in\{0,1,\dots,n\}$.
#### Digressione: perché si dice che $0^{0}=1$
La giustificazione data a lezione (lavagna aggiuntiva) è un calcolo di limite: $$\lim_{x\to 0^{+}}x^{x}=\lim_{x\to 0^{+}}e^{x\log x}\overset{(1)}{=}e^{\overset{(*)}{\overbrace{\lim_{x\to 0^{+}}x\log x}}}=e^{0}=1$$dove in $(1)$ si è usato che $f(x)=e^{x}$ è una funzione continua, e dove il limite $(*)$ si calcola con il teorema di de l'Hôpital: $$(*)=\lim_{x\to 0^{+}}\frac{\log x}{1/x}=\lim_{x\to 0^{+}}\frac{1/x}{-1/x^{2}}=\lim_{x\to 0^{+}}-\frac{x^{2}}{x}=\lim_{x\to 0^{+}}-x=0$$
### Caso 2): distribuzione ipergeometrica
Supponiamo di avere $n_{1}$ oggetti di "tipo 1" e $n_{2}$ oggetti di "tipo 2". Si estraggono a caso $n$ oggetti (dove $n<n_{1}+n_{2}$), una alla volta e **senza** reinserimento: quindi *non* c'è indipendenza, a differenza del caso di estrazioni con reinserimento.
La convenzione è: $$\begin{array}{l}
\text{successo} & \longleftrightarrow & \text{"estrazione di un oggetto di tipo 1"} \\
\text{fallimento} & \longleftrightarrow & \text{"estrazione di un oggetto di tipo 2"}
\end{array}$$
Consideriamo il caso della sequenza $$w=(\underset{k\text{ volte}}{\underbrace{1,\dots,1}},\underset{n-k\text{ volte}}{\underbrace{0,\dots,0}})$$Si ha $P(\{w\})=0$ se $k>n_{1}$ oppure $n-k>n_{2}$ (ovvio: non ci sono abbastanza oggetti di quel tipo).
Al contrario, se $0\leq k\leq n_{1}$ e $0\leq n-k\leq n_{2}$, si ha $$P(\{w\})=\underset{\text{prob. 1}^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}}{n_{1}+n_{2}}}}\cdot\underset{\text{prob. 2}^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}-1}{n_{1}+n_{2}-1}}}\cdot\ \dots\ \cdot\underset{\text{prob. }k^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{1}-(k-1)}{n_{1}+n_{2}-(k-1)}}}\cdot\underset{\text{prob. }(k+1)^{\text{a}}\text{ estr.}}{\underbrace{\frac{n_{2}}{n_{1}+n_{2}-k}}}\cdot\frac{n_{2}-1}{n_{1}+n_{2}-k-1}\cdot\ \dots\ \cdot\frac{n_{2}-(n-k-1)}{n_{1}+n_{2}-(n-1)}$$dove ogni fattore dal secondo in poi è una probabilità condizionata "sapendo il passato" (si veda la [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]).
#### Osservazione
Se si cambia sequenza (sempre con $k$ volte "1" e $n-k$ volte "0") si ottiene sempre lo stesso valore: i denominatori sono gli stessi, cambia solo l'ordine dei fattori a numeratore.
Quindi siamo nella condizione di dire che, per ogni $k\in\{0,1,\dots,n\}$, esiste $q_{k}$ tale che $X(w)=k\implies P(\{w\})=q_{k}$, dove $$q_{k}=\begin{cases}
0 & \text{se }k>n_{1}\text{ oppure }n-k>n_{2} \\
\frac{n_{1}}{n_{1}+n_{2}}\cdot\dots\cdot\frac{n_{1}-(k-1)}{n_{1}+n_{2}-(k-1)}\cdot\frac{n_{2}}{n_{1}+n_{2}-k}\cdot\dots\cdot\frac{n_{2}-(n-k-1)}{n_{1}+n_{2}-(n-1)} & \text{altrimenti}
\end{cases}$$
Il secondo caso si riscrive in termini di coefficienti binomiali: $$q_{k}=\frac{\frac{n_{1}!}{(n_{1}-k)!}\cdot\frac{n_{2}!}{(n_{2}-(n-k))!}}{\frac{(n_{1}+n_{2})!}{(n_{1}+n_{2}-n)!}}=\frac{\overset{}{\frac{n_{1}!}{k!(n_{1}-k)!}}k!\cdot \frac{n_{2}!}{(n-k)!(n_{2}-(n-k))!}(n-k)!}{\frac{(n_{1}+n_{2})!}{n!(n_{1}+n_{2}-n)!}n!}=\frac{\binom{n_{1}}{k}k!\binom{n_{2}}{n-k}(n-k)!}{\binom{n_{1}+n_{2}}{n}n!}=\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}\binom{n}{k}}$$
#### Osservazione
Questa formula si estende anche al caso $k>n_{1}$ e $n-k>n_{2}$ con la regola $\binom{a}{b}=0$ per $b>a$ (già incontrata nelle [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]]).
In conclusione, con riferimento alla formula ($\diamondsuit$), si ha $$P_{X}(k)=\cancel{\binom{n}{k}}\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}\cancel{\binom{n}{k}}}=\begin{bmatrix}
\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}
\end{bmatrix}\quad\quad\forall\ k\in\{0,1,\dots,n\}$$Questa è la densità discreta delle v.a. con **distribuzione ipergeometrica**.
Qui abbiamo tre parametri: $n_{1},n_{2}\geq 1$ interi, e $n$ intero con $n<n_{1}+n_{2}$.
#### Osservazioni
1) Si può verificare che $\displaystyle\sum_{k=0}^{n}P_{X}(k)=1$ (il prof omette i dettagli).
2) A differenza del caso della distribuzione binomiale si può avere qualche caso con $P_{X}(k)=0$ "non banale": si tratta di trovare valori di $k$ tali che $k>n_{1}$ oppure $n-k>n_{2}$. In qualche caso si riesce a trovarli, in altri no: dipende da $n_{1}$ e $n_{2}$.
#### Osservazione (raccordo con il Cap 2)
Ritroviamo esattamente la formula delle [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni casuali in blocco]], come anticipato: estrarre $n$ oggetti uno alla volta senza reinserimento e contare i successi dà la stessa distribuzione che estrarli in blocco.
### Un commento sulla validità della formula ($\diamondsuit$)
La formula ($\diamondsuit$) segue dall'ipotesi $$\forall\ k\in\{0,1,\dots,n\}\ \text{ esiste }q_{k}\text{ tale che }X(w)=k\implies P(\{w\})=q_{k}\quad\quad(\bullet\bullet)$$cioè dal fatto che *ogni sequenza con esattamente $k$ successi ha la stessa probabilità*.
Ora presentiamo un esempio dove $(\bullet\bullet)$ **non** è vera. Prendiamo $n=2$ prove indipendenti, con probabilità di successo $p_{1}$ e $p_{2}$ diverse tra loro ($p_{1}\neq p_{2}$). Si ha $$\begin{array}{ll}
P(\{(0,0)\})=(1-p_{1})(1-p_{2}), & P(\{(1,0)\})=p_{1}(1-p_{2}), \\
P(\{(0,1)\})=(1-p_{1})p_{2}, & P(\{(1,1)\})=p_{1}p_{2}
\end{array}$$Se per assurdo si avesse $(\bullet\bullet)$, per $k=1$ si avrebbe $P(\{(1,0)\})=P(\{(0,1)\})$ da cui seguirebbe $$p_{1}(1-p_{2})=p_{2}(1-p_{1})\implies p_{1}-p_{1}p_{2}=p_{2}-p_{1}p_{2}\implies p_{1}=p_{2}$$contro l'ipotesi $p_{1}\neq p_{2}$.
In questo caso si ha (calcolando direttamente, senza ($\diamondsuit$)) $$\begin{cases}
P_{X}(0)=(1-p_{1})(1-p_{2}) \\
P_{X}(1)=p_{1}(1-p_{2})+p_{2}(1-p_{1}) \\
P_{X}(2)=p_{1}p_{2}
\end{cases}$$
### Esempio: confronto binomiale / ipergeometrica
Un'urna ha 3 palline bianche e 6 nere. Si estraggono a caso 4 palline, una alla volta.
1) **Con reinserimento**: trovare la densità discreta della v.a. $X$ che conta il numero di palline bianche estratte.
   Si ha $X\sim BIN\left( n=4,p=\frac{3}{9}=\frac{1}{3} \right)$, e per $k\in\{0,1,2,3,4\}$ $$P_{X}(k)=\binom{4}{k}\left( \frac{1}{3} \right)^{k}\left( 1-\frac{1}{3} \right)^{4-k}=\binom{4}{k}\left( \frac{1}{3} \right)^{k}\left( \frac{2}{3} \right)^{4-k}=\begin{cases}
16/81 & k=0 \\
32/81 & k=1 \\
24/81 & k=2 \\
8/81 & k=3 \\
1/81 & k=4
\end{cases}$$(la somma fa 1).
2) **Senza reinserimento**: $X$ è ipergeometrica con $n_{1}=3$, $n_{2}=6$, $n=4$, e per $k\in\{0,1,2,3,4\}$ $$P_{X}(k)=\frac{\binom{3}{k}\binom{6}{4-k}}{\binom{9}{4}}=\begin{cases}
15/126 & k=0 \\
60/126 & k=1 \\
45/126 & k=2 \\
6/126 & k=3 \\
0 & k=4
\end{cases}$$(la somma fa 1). Qui si ha zero per $k=4$ perché $k>n_{1}$ ($4>3$): in effetti $\binom{n_{1}}{k}=\binom{3}{4}=0$.
### Esempio: schema binomiale "nascosto" (4 urne)
Abbiamo 4 urne, tutte con 2 palline bianche e 3 rosse. Da ogni urna si estraggono a caso 2 palline, una alla volta e **senza** reinserimento.
1) Trovare la densità discreta della v.a. $X_{1}$ che conta il numero di urne dalle quali si estraggono 2 palline di colori diversi.
2) Trovare la densità discreta della v.a. $X_{2}$ che conta il numero di urne dalle quali si estraggono una pallina rossa e una bianca *in quest'ordine*.

**Svolgimento.** Le estrazioni da urne diverse non si influenzano, e quindi definiscono famiglie di eventi [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenti]]. Quindi in entrambi i casi si tratta di contare il numero di successi su 4 prove indipendenti, tutte con la stessa probabilità di successo: $$\begin{array}{ll}
X_{1}\sim BIN(n=4,p_{1}) & p_{1}=\text{prob. di estrarre colori diversi da una singola urna} \\
X_{2}\sim BIN(n=4,p_{2}) & p_{2}=\text{prob. di estrarre la sequenza }(R,B)\text{ da una singola urna}
\end{array}$$
1) Calcolo $p_{1}$ in due modi diversi: $$\begin{array}{ll}
1^{\circ}\text{ modo} & p_{1}=\frac{\binom{2}{1}\binom{3}{1}}{\binom{5}{2}}=\frac{2\cdot 3}{10}=\frac{3}{5} \\
2^{\circ}\text{ modo} & p_{1}=P(R_{2}|B_{1})P(B_{1})+P(B_{2}|R_{1})P(R_{1})=\frac{3}{4}\cdot \frac{2}{5}+\frac{2}{4}\cdot \frac{3}{5}=\frac{3}{10}+\frac{3}{10}=\frac{6}{10}=\frac{3}{5}
\end{array}$$da cui, per $k\in\{0,1,2,3,4\}$, $$P_{X_{1}}(k)=\binom{4}{k}p_{1}^{k}(1-p_{1})^{4-k}=\begin{cases}
16/625 & k=0 \\
96/625 & k=1 \\
216/625 & k=2 \\
216/625 & k=3 \\
81/625 & k=4
\end{cases}$$
2) Calcolo $p_{2}$ come segue: $p_{2}=P(B_{2}|R_{1})P(R_{1})=\frac{2}{4}\cdot \frac{3}{5}=\frac{3}{10}$, da cui $$P_{X_{2}}(k)=\binom{4}{k}p_{2}^{k}(1-p_{2})^{4-k}=\begin{cases}
2401/10000 & k=0 \\
4116/10000 & k=1 \\
2646/10000 & k=2 \\
756/10000 & k=3 \\
81/10000 & k=4
\end{cases}$$
### Esempio: ipergeometrica con $n_{1}+n_{2}$ "molto più grande" di $n$
Un'urna ha 500 palline bianche e 500 nere. Si estraggono 3 palline a caso, una alla volta e **senza** reinserimento. Trovare la densità della v.a. $X$ che conta il numero di palline bianche estratte. $$P_{X}(k)=\frac{\binom{500}{k}\binom{500}{3-k}}{\binom{1000}{3}}=\begin{cases}
\frac{500\cdot 499\cdot 498}{1000\cdot 999\cdot 998}\approx \frac{1}{2}\cdot \frac{1}{2}\cdot \frac{1}{2}=\frac{1}{8} & \text{per }k=0\text{ e }k=3 \\
3\cdot \frac{1}{2}\cdot \frac{1}{2}\cdot \frac{1}{2}\approx\frac{3}{8} & \text{per }k=1\text{ e }k=2
\end{cases}$$
#### Commento
Se si considerasse il caso di estrazioni **con** reinserimento si avrebbe $X\sim BIN\left( n=3,p=\frac{500}{1000}=\frac{1}{2} \right)$ e si avrebbe $$P_{X}(k)=\binom{3}{k}\left( \frac{1}{2} \right)^{3}=\begin{cases}
1/8 & \text{per }k=0\text{ e }k=3 \\
3/8 & \text{per }k=1\text{ e }k=2
\end{cases}$$Quando $n_{1}+n_{2}$ è "molto più grande" di $n$ si ha una situazione **molto vicina al caso di estrazioni con reinserimento**.
> [!info] Esercizi conclusivi della lezione 06
> Le ultime pagine della lezione 06 (pp. 20–23) contengono due esercizi di riepilogo "con agganci con argomenti passati" (lanci ripetuti di un dado equo; lanci ripetuti di una coppia di dadi), che combinano distribuzione binomiale, indipendenza e probabilità condizionata. Sono esercizi puri e non aggiungono teoria: la loro sede è la cartella `Esercizi/`.

--- Fine lezione 06 ---

---
Nota precedente: [[Variabili aleatorie discrete]]. Nota successiva: [[Distribuzione multinomiale]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
