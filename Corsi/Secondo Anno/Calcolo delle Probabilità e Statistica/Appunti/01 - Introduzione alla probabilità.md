# Introduzione alla probabilità
## Fenomeni aleatori e spazio di probabilità
Un fenomeno è detto "fenomeno aleatorio" se il suo esito è incerto.
L'insieme dei possibili esiti (in genere "numerico", eventualmente multidimensionale) viene indicato con $\Omega$ 
$$\begin{array}{}
 & \nearrow \text{DISCRETO se }\Omega \text{ è finito o numerabile}\\
\text{fenomeno aleatorio} &  \\
 & \searrow\text{CONTINUO se }\Omega \text{ è più che numerabile}
\end{array}$$
Esempi:
- discreti: $\Omega$ finito (possibili risultati del lancio di un dado, $\Omega=\{1,\dots,6\}$); $\Omega$ numerabile (numero di telefonate ricevute da un centralino in un intervallo di tempo, $\Omega=\{0,1,2,\dots\}$);
- continuo: tempo di funzionamento di una lampadina rispetto a una certa unità di misura, $\Omega=(0,\infty)$.

In genere si introduce una "famiglia di eventi" $\mathcal{A}$ che viene individuata da una famiglia di sottoinsiemi di $\Omega$. Tornando agli esempi: "esce un numero pari" $\leftrightarrow\{2,4,6\}\subset\{1,\dots,6\}$; "il centralino riceve al più 2 telefonate" $\leftrightarrow\{0,1,2\}\subset\{0,1,2,\dots\}$; "la lampadina si fulmina dopo il tempo $t=5$" $\leftrightarrow(5,\infty)\subset(0,\infty)$.

Vi è una corrispondenza naturale tra operazioni logiche tra eventi e operazioni insiemistiche:

| operazione logica | operazione insiemistica |
|---|---|
| somma logica $A\vee B$ | unione $A\cup B$ |
| prodotto logico $A\wedge B$ | intersezione $A\cap B$ |
| negazione $\bar A$ | complementare $A^{c}=\Omega\setminus A$ |

Si vuole fare riferimento a "famiglie di eventi con buone proprietà": si intende che, facendo operazioni insiemistiche in elementi di $\mathcal{A}$, si ottiene ancora un elemento di $\mathcal{A}$.
### Definizione ($\sigma$-algebra)
Sia $\Omega$ un insieme non vuoto e sia $\mathcal{A}\subset\mathcal{P}(\Omega)$ (dove $\mathcal{P}(\Omega)$ è l'insieme delle parti di $\Omega$). Allora $\mathcal{A}$ è una $\sigma$-algebra (di eventi) se:
1) $\Omega\in\mathcal{A}$
2) $\forall A\in\mathcal{A}\implies A^c\in\mathcal{A}$ ^96616b
3) $\forall\{A_{n}\}_{n\geq1}\subset\mathcal{A}\implies\underset{n\geq 1}{\bigcup}A_{n}\in\mathcal{A}$

Definiamo $\mathcal{P}(\Omega)$ l'insieme delle parti di $\Omega$.
#### Osservazione
Si vede facilmente che anche $\varnothing\in\mathcal{A}$ e che $\underset{n\geq 1}{\bigcap}A_{n}\in\mathcal{A}$ nel punto 3) della definizione. 
#### Osservazione
La richiesta della numerabilità viene fatta per semplificare alcune cose successivamente (non trattato nel corso).
#### Osservazione
Si può prendere $\mathcal{A}=\mathcal{P}(\Omega)$. Questa scelta dà altri problemi se $\Omega$ è *più che numerabile* (non trattato nel corso). Per questo motivo il caso di $\Omega$ *discreto* viene trattato più diffusamente nel corso.
### Definizione (Misure di Probabilità)
Sia $\Omega$ un insieme non vuoto e $\mathcal{A}$ una $\sigma$-[[01 - Introduzione alla probabilità#Definizione ($\sigma$-algebra)|algebra di eventi]] allora una funzione $P:\mathcal{A}\to[0,\infty)$ è una **misura di probabilità** se:
1) $P(\Omega)=1$
2) $$\begin{matrix} 
\forall\{A_{n}\}_{n\geq 1}\subset\mathcal{A}\quad \text{tale che}\\ \\
{\left[\begin{array}{}
A_{m}\cap A_{n}=\varnothing \\
\text{per } m\not=n
\end{array}\right]}\quad
\text{disgiunti a due a due} \\\\
\text{si ha}\quad P\left(\underset{n\geq 1}{\bigcup}A_{n}\right)=\displaystyle\sum_{n\geq 1}P(A_{n})\quad
\end{matrix}$$ ^c9a1d2

**Terminologia**: la terna $(\Omega,\mathcal{A},P)$ è detta *spazio di probabilità*.
##### Commenti
- La misura di probabilità $P:\mathcal{A}\to[0,\infty)$ in realtà assume valori in $[0,1]$; questo sarà chiarito successivamente (conseguenza 3.2).
- La richiesta $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$, cioè "insiemi disgiunti a due a due", è più forte della condizione $\underset{n\geq 1}{\bigcap}A_{n}=\varnothing$
  Per fissare le idee consideriamo una famiglia di 3 insiemi $A,B,C$ (diagramma di Venn in $\Omega$: tre insiemi che si sovrappongono a due a due, ma senza alcun punto comune a tutti e tre); allora in questo caso $$\begin{array}{ll}
A\cap B\neq\varnothing & \\
A\cap C\neq\varnothing & A\cap B\cap C=\varnothing \\
B\cap C\neq\varnothing &
\end{array}$$
  cioè vale $\bigcap A_{n}=\varnothing$ ma gli insiemi non sono disgiunti a due a due.

> [!question] Domanda tipica d'esame
> Dare la definizione di $\sigma$-algebra di eventi e di misura di probabilità; perché la condizione $A_{m}\cap A_{n}=\varnothing$ per $m\neq n$ è più forte di $\bigcap_{n\geq1}A_{n}=\varnothing$?
> Risposta: $\mathcal{A}\subset\mathcal{P}(\Omega)$ contiene $\Omega$, è chiusa per complementare e per unione numerabile; $P:\mathcal{A}\to[0,\infty)$ con $P(\Omega)=1$ e $P(\bigcup A_{n})=\sum P(A_{n})$ per eventi disgiunti a due a due. Tre insiemi $A,B,C$ con $A\cap B$, $A\cap C$, $B\cap C$ non vuoti ma $A\cap B\cap C=\varnothing$ soddisfano la seconda condizione senza essere disgiunti a due a due.
## Conseguenze della Definizione di Misura di Probabilità
1) $P(\varnothing)=0$
   infatti se consideriamo $A_{n}=\varnothing\quad\forall\ n\geq 1$,si ha $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$ o $m=n$  da cui segue $$\begin{cases}
  P\left(\underset{n\geq 1}{\bigcup}A_{n}\right)=P\left(\underset{n\geq 1}{\bigcup}\varnothing\right)=P(\varnothing) \\
 \displaystyle\sum_{n\geq 1}P(A_{n})
\end{cases}\implies P(\varnothing)=\sum_{n\geq 1}P(\varnothing)$$Questa condizione non può essere vera se $P(\varnothing)>0$; infatti il secondo membro sarebbe infinito ( e il primo finito).

2) Sia $h\geq 1$ intero e $B_{1},\dots,B_{h}\in\mathcal{A}$ con $B_{m}\cap B_{n}=\varnothing$ per $m\not=n$ allora $P(\overset{h}{\underset{n=1}{\cup}}B_{n})=\displaystyle\sum_{n=1}^{h}P(B_{n})$.
   Infatti basta fare riferimento alla condizione [[#^c9a1d2|2)]] nella definizione di misura di probabilità con $A_{1}=B_{1},\dots,A_{h}=B_{h},A_{h+1}=A_{h+2}=\dots=\varnothing$. 
   Infatti con queste scelte (e per ipotesi), si ha $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$ e si ha $P(\underset{n\geq1}{\cup}A_{n})=\displaystyle\sum_{n\geq 1}P(A_{n})$ da cui segue: $$\begin{cases}
\underset{n\geq 1}{\cup}A_{n}=B_{1}\cup\dots \cup B_{h}\cup\varnothing\cup \varnothing\cup\varnothing\dots= \overset{h}{\underset{n= 1}{\cup}B_{n}}\implies P(\underset{n\geq 1}{\cup}A_{n})=P(\overset{h}{\underset{n= 1}{\cup}}B_{n}) \\ \\
\displaystyle\sum_{n\geq 1}P(A_{n})=P(B_{1})+\dots+P(B_{h})+P(\varnothing)+\dots=\sum_{n=1}^{h}P(B_{n})
\end{cases}$$e quindi si ottiene $P(\overset{h}{\underset{n= 1}{\cup}}B_{n})=\displaystyle\sum_{n=1}^{h}P(B_{n})$
 ^95909c
3) Specializziamo l'uguaglianza appena verificata prendendo $E,F\in\mathcal{A},h=2$,$B_{1}=E\cap F$,$B_{2}=E\cap F^{c}$. Allora $$\begin{array}{l}
\underline{P((E\cap F)\cup(E\cap F^{c}))}=P(E\cap F)+P(E\cap F^{c})\implies P(E)=P(E\cap F)+P(E\cap F^{c}) \\
\quad\quad\Downarrow \\
=P(E)
\end{array}$$
3) .1 
   con $E=\Omega$
   $1=P(F)+P(F^c)\quad\forall\ F\in\mathcal{A}$
   quindi  $$\begin{cases}
P(F)=1-P(F^{c}) \\
P(F^{c})=1-P(F)
\end{cases}$$
3) .2 
   con $F\subset E\quad(E\cap F=F)$
   quindi 
   $P(E)=P(F)+\underset{\geq 0}{\underbrace{P(E\cap F^{c})}}\geq P(F)\implies P(E)\geq P(F)$
   da questo segue che $P(A)\leq P(\Omega)=1\quad\forall\ A\in \mathcal{A}$

3) .3
   Specializzando la formula al punto [[#^95909c|2)]] con $E,F\in\mathcal{A},h=3$,$B_{1}=E\cap F^{c},B_{2}=E\cap F,B_{3}=F\cap E^{c}$
   ovviamente $B_{1}\cup B_{2}\cup B_{3}=E\cup F$ e quindi $$\begin{array}{l}
P(E\cup F)=P(B_{1})+P(B_{2})+P(B_{3})= \\
\quad\quad\quad\quad\ =P(E\cap F^{c})+P(E\cap F)+P(F\cap E^{c})= \\
=\underset{=P(E)}{\underbrace{P(E\cap F^{c})+P(E\cap F)}}+\underset{=P(F)}{\underbrace{P(F\cap E^{c})+P(E\cap F)}}-P(E\cap F) \\
\implies P(E\cup F)=P(E)+P(F)-P(E\cap F)
\end{array}$$ ^813f60
#### Osservazione
L'uguaglianza ottenuta ha un'interpretazione naturale.
Prendendo $P(E)+P(F)$ si ha che $P(E\cap F)$ viene "preso due volte" e quindi dobbiamo sottrarre la stessa quantità.
Se $E\cap F=\varnothing$ ritroviamo la [[#^95909c|2)]] con $h=2,B_{1}=E,B_{2}=F$.

La formula ottenuta nella [[#^813f60|3).3]] si estende al caso di più di due eventi (**Identità di Bonferroni**).
Qui richiamo quella per $n=3$; $\quad\forall\ E,F,G\in \mathcal{A}$
$P(E\cup F\cup G)=P(E)+P(F)+P(G)-P(E\cap F)-P(E\cap G)-P(F\cap G)+P(E\cap F\cap G)$
#### Commento generale
Le proprietà della [[01 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|misura di probabilità]] sono svincolate dalla costruzione del modello, e quindi da come si definisce la misura di probabilità in questione per descrivere il [[01 - Introduzione alla probabilità#Fenomeni aleatori e spazio di probabilità|fenomeno aleatorio]] (tale definizione può dipendere dallo stato di conoscenza dell'osservatore).

> [!question] Domanda tipica d'esame
> Dimostrare che $P(\varnothing)=0$ e che $P(E\cup F)=P(E)+P(F)-P(E\cap F)$.
> Risposta: con $A_{n}=\varnothing$ per ogni $n$ si ottiene $P(\varnothing)=\sum_{n\geq1}P(\varnothing)$, impossibile se $P(\varnothing)>0$. Per la seconda, $E\cup F$ è unione disgiunta di $E\cap F^{c}$, $E\cap F$, $F\cap E^{c}$, e $P(E)=P(E\cap F^{c})+P(E\cap F)$, $P(F)=P(F\cap E^{c})+P(E\cap F)$: sommando e sottraendo $P(E\cap F)$ si ottiene la formula.
## Spazio di Probabilità Uniforme Discreto
Questa terminologia si usa nel caso in cui si ha la seguente situazione:
- $\Omega$ insieme finito
- $\mathcal{A}=\mathcal{P}(\Omega)$
- $\forall\ A\in\mathcal{A}$
  $P(A)=\frac{\#A}{\#\Omega}=\frac{\#A}{n}\quad\quad$ (# indica la cardinalità dell'insieme)
Questa situazione viene fuori imponendo la seguente condizione $\forall\ \omega\in\Omega\quad\quad P(\{\omega\})$ assume sempre lo stesso valore, infatti se questo valore lo indichiamo con $p$, allora abbiamo le seguenti uguaglianze $$\begin{array}{l}
1=P(\Omega)\underset{\Uparrow}{=}P(\underset{\omega\in\Omega}{\cup}\{\omega\})=\displaystyle\sum_{\omega\in\Omega}\underset{=p}{\underbrace{P(\{\omega\})}}=\sum_{\omega\in\Omega}p=n\ p \implies p=\frac{1}{n} \\
\text{cioè se }\Omega=\{\omega_{1},\dots,\omega_{n}\} \\
\text{allora }\Omega=\{\omega_{1}\}\cup\{\omega_{2}\}\cup\dots \cup \{\omega_{n}\}
\end{array}$$allora, per ogni $A\in\mathcal{A}$, si ha 
$P(A)=P(\underset{\omega\in A}{\cup}\{\omega\})=\displaystyle\sum_{\omega\in A} P(\{\omega\})=p\cdot\#A=\frac{\#A}{n}$
##### Commenti
1) In questo caso $P(A)=0$ se e solo se $A=\varnothing$.
2) Questa situazione esce fuori quando si compiono "estrazioni a caso da un insieme di $n$ oggetti".
3) Questa costruzione non può essere fatta nel caso in cui $\Omega$ è infinito numerabile perché si avrebbe infinito a denominatore quindi $P(A)=0$ sempre.
   In altri termini non si riesce a modellare il caso di estrazioni a caso da un insieme infinito numerabile di oggetti.
4) Questo modello si può usare nel caso del lancio di un dado equo con $n=6$ e $\Omega=\{1,2,3,4,5,6\}$
### Definizione
Sia $\Omega,\mathcal{A},P$ uno [[01 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|spazio di probabilità]]. Siano $A,B\in\mathcal{A}$ con $P(B)\not=0$ allora si definisce "probabilità condizionata di $A$ dato $B$" (oppure sapendo che si è verificato l'evento $B$) la seguente quantità: $$P(A|B)=\frac{P(A\cap B)}{P(B)}$$
#### Motivazione
Nel voler definire $P(A|B)$ è naturale considerare una quantità che dipende da $P(A\cap B)$ proporzionalmente, con una costante di proporzionalità che non dipende da $A$ (ma da $B$): $$P(A|B)=c_{B}\cdot P(A\cap B)$$
Inoltre si vuole fare in modo che ($\Omega,\mathcal{A},P(\cdot|B)$) sia uno spazio di probabilità. Quindi per $A=\Omega$ si ha $$\underset{=1}{\underbrace{P(\Omega|B)}}=c_{B}\underset{=P(B)}{\underbrace{P(\Omega\cap B)}}\implies c_{B}=\frac{1}{P(B)}\implies P(A|B)=\frac{P(A\cap B)}{P(B)}$$
##### Commento
La costruzione fatta nella "motivazione" consente di trovare un valore per $c_{B}$ solo se $P(B)\not=0$;
Infatti se fosse $P(B)=0$ si avrebbe $1=c_{B}\cdot 0$
Quindi si riesce a dare significato alla probabilità condizionata per $P(B)\not=0$ ma questa restrizione non è grave.
##### Commento
Supponiamo che $P(B)=1$. Allora $P(A|B)=\frac{P(A\cap B)}{P(B)}=\frac{P(A\cap B)}{1}=P(A\cap B)$ 
inoltre $P(A)=P(A\cap B)+P(A\cap B^{c})$ dove $0\leq P(A\cap B^{c})\overset{(A\cap B^{c})\subset B^{c}}{\leq} P(B^{c})=0$
quindi $P(A)=P(A\cap B)$ e sostituendo nell'uguaglianza precedente si ha: $P(A|B)=P(A)$

**Spiegazione**
Il verificarsi di un evento di probabilità 1 è una informazione "banale" e quindi la probabilità condizionata coincide con quella che si ha senza il condizionamento.
##### Commento (**Prob. Condizionata per Spazio di Prob. Uniforme Discreto**)
Sia $B\in\mathcal{A}$ tale che $P(B)\not=0$, quindi $B\not=\varnothing$. 
Allora $P(A|B)=\frac{P(A\cap B)}{P(B)}=\frac{\#(A\cap B/\not n)}{\#B/\not n}=\frac{\#(A\cap B)}{\#B}\quad\quad\forall\ A\in\mathcal{A}$
##### Esempio
Un urna ha 10 palline numerate da 1 a 10. Si estrae una pallina a caso.
1) Calcolare la probabilità di estrarre un numero maggiore di 5 sapendo che è stato estratto un numero pari.
2) Calcolare la stessa probabilità nel caso in cui vengono aggiunte 2 palline (1,10)

Risposta
$A=\{6,7,8,9,10\}$ e $B=\{2,4,6,8,10\}\implies A\cap B=\{6,8,10\}$
1) [[01 - Introduzione alla probabilità#Spazio di Probabilità Uniforme Discreto|Spazio di probabilità discreto]]$\implies P(A|B)=\frac{\#A\cap B}{\#B}=\frac{3}{5}$
2) $P(A|B)=\frac{P(A\cap B)}{P(B)}=\frac{P(\{6,8,10\})}{P(\{2,4,6,8,10\})}=\frac{\frac{1+1+2}{\not{12}}}{\frac{1+1+1+1+2}{\not{12}}}=\frac{4}{6}=\frac{2}{3}$

> [!question] Domanda tipica d'esame
> Come si definisce $P(A|B)$ e perché si pone $c_{B}=\frac{1}{P(B)}$? Calcolare $P(A|B)$ con $A=\{6,\dots,10\}$, $B=\{2,4,6,8,10\}$ in uno spazio uniforme su $\{1,\dots,10\}$.
> Risposta: $P(A|B)=\frac{P(A\cap B)}{P(B)}$ per $P(B)\neq0$; $c_{B}$ è fissato dalla richiesta $P(\Omega|B)=1$, cioè $1=c_{B}P(B)$. Nel caso uniforme $P(A|B)=\frac{\#(A\cap B)}{\#B}=\frac{3}{5}$.

<----- Fine lezione 1 ----->
## Formule legate alle probabilità condizionate
1) [[01 - Introduzione alla probabilità#Regola del Prodotto|Regola del prodotto]] (o Formula Inversa)
2) [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|Formula delle Probabilità Totali]]
3) [[01 - Introduzione alla probabilità#Formula di Bayes|Formula di Bayes]]
### Regola del Prodotto
A partire da $P(A|B)=\frac{P(A\cap B)}{P(B)}$ si ottiene $$P(A\cap B)=P(A|B)P(B)$$
#### Osservazione
Vale anche su $P(B)=0$ perché $A\cap B\subset B\implies P(A\cap B)=0$ e quindi $0=0$ anche se $P(A|B)$ è indeterminato

Questa formula è utile quando la [[01 - Introduzione alla probabilità#Motivazione|probabilità condizionata]] segue dal testo dell'esercizio e la probabilità dell'intersezione è la grandezza da calcolare. Questa formula può essere usata anche per l'intersezione di più di due eventi. Ad esempio, nel caso di 3 eventi, si ha $P(A\cap B\cap C)=P(A|B\cap C)P(B\cap C)$ e quindi $$P(A\cap B\cap C)=P(A|B\cap C)P(B|C)P(C)$$
##### Esempio
Un urna contiene 2 palline bianche, 3 rosse e 4 nere.
Si estraggono 3 palline a caso, una alla volta e senza reinserimento.
1) Calcolare la probabilità di ottenere la sequenza (rosso, non rosso) sulle prime 2 estrazioni
2) Calcolare la probabilità di ottenere la sequenza (rosso, bianco, rosso)

**Risposte**
In questi casi si deve scegliere bene quali sono gli eventi per applicare le formule; infatti, se si scelgono male, otteniamo uguaglianze non utili per ottenere i valori numerici che cerchiamo.
Tipicamente si fa riferimento al "condizionamento rispetto alle estrazioni precedenti".
1) $P(R_{1}\cap R_{2}^{c})=P(R_{2}^{c}|R_{1})P(R_{1})=\frac{6}{8}\cdot \frac{3}{9}=\frac{1}{4}$
2) $P(R_{1}\cap B_{2}\cap R_{3})=P(R_{3}|R_{1}\cap B_{2})P(B_{2}|R_{1})P(R_{1})=\frac{2}{7}\cdot \frac{2}{8}\cdot \frac{3}{9}=\frac{1}{42}$
###### Osservazione 
1) Supponiamo di "scegliere male" gli eventi. Ad esempio possiamo scrivere $$P(R_{1}\cap B_{2}\cap R_{3})=P(R_{3}|B_{2}\cap R_{1})\underset{=P(R_{1}\cap B_{2})}{\underbrace{P(R_{1}|B_{2})P(B_{2})}}$$
   questa uguaglianza è vera ma non è direttamente utilizzabile perché non sappiamo dare un valore numerico per $P(R_{1}|B_{2})$ e per $P(B_{2})$ in maniera diretta
   
2) Le probabilità di certe sequenze di risultati non cambiano se consideriamo un ordine diverso dai risultati stessi. Ad esempio calcoliamo la probabilità di ottenere la sequenza (bianco, rosso, nero) e (nero, bianco, rosso) allora: $$\begin{array}{}
P(B_{1}\cap R_{2}\cap N_{3})=P(N_{3}|R_{2}\cap B_{1})P(R_{2}|B_{1})P(B_{1})=\frac{4}{7}\cdot \frac{3}{8}\cdot \frac{2}{9}=\frac{1}{21} \\
P(N_{1}\cap B_{2}\cap R_{3})=P(R_{3}|N_{1}\cap B_{2})P(B_{2}|N_{1})P(N_{1})=\frac{3}{7}\cdot \frac{2}{8} \cdot \frac{4}{9}=\frac{1}{21}
\end{array}$$
### Formula delle Probabilità Totali
Supponiamo di avere una **partizione di eventi** finita o numerabile $$\{E_{i}:i\in I\}\quad\quad(I=\{1,\dots,n\}\text{ o }I=\{1,2,3,\dots\})$$
Questo significa che $\underset{i\in I}{\cup} E_{i}=\Omega$ e che $E_{i}\cap E_{j}=\varnothing$ per $i\not=j$
Inoltre sia $A$ un altro evento $$\begin{array}{l}
\text{Si usa questa formula per calcolare }P(A)\text{ quando} \\
\text{si conoscono } \{P(E_{i})\}_{i\in I}\ \text{ e }\ 
\underset{\begin{array}{}
\text{per i valori in cui} \\
P(E_{i})\not=0\text{(in ogni caso} \\
\text{la cosa si aggira)}
\end{array}}{\underbrace{\{P(A|E_{i})\}_{i\in I}}}\end{array}$$
Allora 
$\underset{A=A\cap\Omega}{P(A)}=P(A\cap\Omega)=P(A\cap(\underset{i\in I}{\cup} E_{i}))\underset{\text{Prop. distr.}}{=}P(\underset{i\in I}{\cup}(A\cap E_{i}))\underset{\underset{i\not=j}{(A\cap E_{i})\cap(A\cap E_{j})=\varnothing}}{=}\displaystyle\sum_{i\in I}P(A\cap E_{i})$ 
ora per ciascun addendo per cui $P(E_{i})\neq 0$ si ha $P(A\cap E_{i})=P(A|E_{_{i}})P(E_{i})$
#### Osservazione
In ogni caso, se fosse $P(E_{i})=0$, si avrebbe $P(A\cap E_{i})=0$ e vale l'uguaglianza anche se $P(A|E_{i})$ non è definita.

In conclusione $$P(A)=\sum_{i\in I}P(A|E_{i})P(E_{i})$$
Un caso particolare è quello in cui la partizione è costituita da due eventi: $$\begin{cases}
E_{1}=E \\
E_{2}=E^{c}
\end{cases}\quad \text{ allora } P(A)=P(A|E)P(E)+P(A|E^{c})P(E^{c})$$
### Diagramma ad albero associato alla formula delle Prob. Totali
Si può costruire un diagramma ad albero associato dove ogni diagramma fa riferimento ad una [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|partizione]] (ogni diagramma considera tutti i casi possibili). Ad ogni arco si associa una probabilità. Per fissare le idee consideriamo il caso $I=\{1,2,3\}$ $$\begin{matrix}
 &  &  &  &  & A \\
 &  &  &  & \ \ \ / & \leftarrow P(A|E_{1}) \\
 & \ulcorner & - & E_{1} & \langle &  \\
 & | &  &  & \ \ \ \backslash & \leftarrow P(A^{c}|E_{1}) \\
P(E_{1})\rightarrow & | &  &  &  & A^{c} \\
 & | &  &  &  & A \\
 & | & P(E_{2})\downarrow &  & \ \ \ / & \leftarrow P(A|E_{2}) \\
 & + & - & E_{2} & \langle &  \\
 & | &  &  & \ \ \ \backslash & \leftarrow P(A^{c}|E_{2}) \\
P(E_{3})\rightarrow & | &  &  &  & A^{c} \\
 & | &  &  &  & A \\
 & | &  &  & \ \ \ / & \leftarrow P(A|E_{3}) \\
 & \llcorner & - & E_{3} & \langle &  \\
 &  &  &  & \ \ \ \backslash & \leftarrow P(A^{c}|E_{3}) \\
 &  &  &  &  & A^{c} \\
\end{matrix}$$
Siamo interessati a tutte le foglie che finiscono con A. 
Si deve considerare la somma dei pesi dei cammini che finiscono con A ottenuti con i prodotti dei pesi dei rami $P(A)=P(A|E_{1})P(E_{1})+P(A|E_{2})P(E_{2})+P(A|E_{3})P(E_{3})$
#### Esempio
Una urna ha 2 palline bianche e 1 nera.
Si lancia un dado equo:
- se esce il numero 1 si mettono 2 palline bianche nell'urna
- se escono 2 o 3 si mettono 1 pallina bianca e 1 nera
- se escono 4,5 o 6 si mettono 2 palline nere
Poi si estrae una pallina a caso dall'urna.
Calcolare la probabilità di estrarre una pallina bianca.

**Risposta**
Siamo interessati all'esito dell'evento $B=\{\text{estratta pallina bianca}\}$.
Possiamo calcolare le probabilità di $B$ se conosciamo quale dei 3 "casi" si è verificato. I 3 "casi" costituiscono una *partizione* $$\begin{matrix}
E_{1}=\{[1]\} & E_{2}=\{[2]\text{ o }[3]\} & E_{3}=\{[4]\text{ o }[5]\text{ o }[6]\} & \text{ e si ha:} \\
\begin{cases}
P(E_{1})=\frac{1}{6} \\
P(B|E_{1})=\frac{4}{5}
\end{cases} & \begin{cases}
P(E_{2})=\frac{2}{6} \\
P(B|E_{2})=\frac{3}{5}
\end{cases} & \begin{cases}
P(E_{3})=\frac{3}{6} \\
P(B|E_{3})=\frac{2}{5}
\end{cases} \\
\begin{array}{c|c}
4 & 1 \\
B & N \\
\hline
\end{array} & \begin{array}{c|c}
3 & 2 \\
B & N \\
\hline
\end{array} & \begin{array}{c|c}
2 & 3 \\
B & N \\
\hline
\end{array}
\end{matrix}$$
In conclusione $P(B|E_{1})P(E_{1})+P(B|E_{2})P(E_{2})+P(B|E_{3})P(E_{3})=\frac{4}{5}\cdot \frac{1}{6}+\frac{3}{5}\cdot \frac{2}{6}+\frac{2}{5}\cdot \frac{3}{6}=\frac{8}{15}$
#### Osservazione
Sappiamo che la probabilità di estrarre nera è $P(B^{c})=1-P(B)=1-\frac{8}{15}=\frac{7}{15}$
Questo risultato si ottiene anche con la [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|formula delle probabilità totali]]: 
$P(B^{c})=P(B^{c}|E_{1})P(E_{1})+P(B^{c}|E_{2})P(E_{2})+P(B^{c}|E_{3})P(E_{3})=\frac{1}{5}\cdot \frac{1}{6}+\frac{2}{5}\cdot \frac{2}{6}+\frac{3}{5}\cdot \frac{3}{6}=\frac{1+4+9}{30}=\frac{14}{30}=\frac{7}{15}$
### Formula di Bayes
Sappiamo che $P(A|B)=\frac{P(A\cap B)}{P(B)}$ con l'ipotesi $P(B)\neq 0$
Inoltre $A\cap B$ e $B\cap A$ sono lo stesso evento; quindi $P(A\cap B)=P(B\cap A)=P(B|A)P(A)$
Quindi, sostituendo nella formula iniziale, si ha $$P(A|B)=\frac{P(B|A)P(A)}{P(B)}$$
Questa formula si usa quando viene chiesta una *[[01 - Introduzione alla probabilità#Motivazione|probabilità condizionata]]* $P(A|B)$ e la probabilità condizionata $P(B|A)$(cioè quella in cui $A$ e $B$ si scambiano) si calcola facilmente, e comunque questo è più agevole rispetto a valutare l'evento intersezione $A\cap B$.

Prima degli esempi, si vuole sottolineare che negli esercizi questa formula si usa combinandola con la [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|formula delle probabilità totali]] per calcolare il denominatore $P(B)$.
In altri termini negli esercizi si potrà fare riferimento ad una [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|partizione]] $\{E_{n}\}_{n\in I}$ per cui si sa calcolare $P(B|E_{n})$, e verrà chiesto di calcolare la probabilità condizionale del tipo $P(E_{n}|B)_{n\in I}$.
Quindi tipicamente si avrà $$P(E_{n}|B)=\frac{P(B|E_{n})P(E_{n})}{\displaystyle\sum_{i\in I}P(B|E_{i})P(E_{i})}\quad\quad\text{ per }n\in I$$
#### Esempio
Consideriamo l'esempio visto per la formula delle probabilità totali $$\begin{matrix}
E_{1}\rightarrow & \ulcorner & - & [1] & \begin{array}{c|c}
4 & 1 \\
B & N \\
\hline
\end{array} \\
 & | & \underset{\downarrow}{E_{2}} &  &  \\
\text{lancio dado equo} & + & - & [2]\text{ o }[3] & \begin{array}{c|c}
3 & 2 \\
B & N \\
\hline
\end{array} \\
 & | &  &  &  \\
E_{3}\rightarrow & \llcorner & - & [4]\text{ o }[5]\text{ o }[6] & \begin{array}{c|c}
2 & 3 \\
B & N \\
\hline
\end{array}
\end{matrix}$$
Supponiamo che venga chiesto di calcolare la seguente probabilità condizionata.
"Calcolare la probabilità che sia uscito $[2]$ o $[3]$ nel lancio sapendo di aver estratto una pallina bianca"
Quindi viene chiesto di calcolare $P(E_{2}|B)$; ricordare che come conseguenza del testo si ha: $$\begin{cases}
P(E_{1})=\frac{1}{6},P(E_{2})=\frac{2}{6},P(E_{3})=\frac{3}{6} \\
P(B|E_{1})=\frac{4}{5},P(B|E_{2})=\frac{3}{5},P(B|E_{3})=\frac{2}{5}
\end{cases}$$
Quindi si calcola immediatamente dal testo $P(B|E_{2})$ e viene chiesta $P(E_{2}|B)$. Allora si usa la formula di Bayes $$\begin{array}{l}
P(E_{2}|B)=\frac{P(B|E_{2})P(E_{2})}{P(B)}= \\
=\frac{P(B|E_{2})P(E_{2})}{P(B|E_{1})P(E_{1})+P(B|E_{2})P(E_{2})+P(B|E_{3})P(E_{3})}= \\
=\frac{\frac{3}{5}\cdot \frac{2}{6}}{\frac{4}{5}\cdot \frac{1}{6}+\frac{3}{5}\cdot \frac{2}{6}+\frac{2}{5}\frac{3}{6}}=\frac{3}{8}
\end{array}$$
Altre possibili domande sono:
"Calcolare la probabilità che sia uscito $[1]$ sapendo di aver estratto una bianca"
"Calcolare la probabilità che sia uscito $[4],[5]$ o $[6]$ sapendo di aver estratto una bianca"
In questi due casi le probabilità richieste sono $P(E_{1}|B)$ e $P(E_{3}|B)$ quindi $$\begin{array}{}
P(E_{1}|B)=\frac{P(B|E_{1})P(E_{1})}{P(B)}=\frac{1}{4} \\
P(E_{3}|B)=\frac{P(B|E_{3})P(E_{3})}{P(B)}=\frac{3}{8}
\end{array}$$
#### Osservazione
Abbiamo ottenuto che $$P(E_{i}|B)=\begin{cases}
\frac{2}{8}\quad i=1 \\
\frac{3}{8}\quad i=2 \\
\frac{3}{8}\quad i=3
\end{cases}$$
Quindi $P(E_{1}|B)+P(E_{2}|B)+P(E_{3}|B)=1$.
Questo è in accordo con il fatto che la somma delle probabilità degli eventi di una partizione è sempre uguale a 1 e che $P(\cdot|B)$ è una [[01 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|misura di probabilità]].

"Calcolare la probabilità che sia uscito $[2]$ o $[3]$ sapendo di aver estratto una nera"
"Calcolare la probabilità che esca un numero dispari nel lancio sapendo di aver estratto una bianca"

**Calcolare la probabilità che sia uscito $[2]$ o $[3]$ sapendo di aver estratto una pallina nera.**
Si chiede $P(E_{2}|B^{c})=\frac{P(B^{c}|E_{2})P(E_{2})}{P(B^{c})}$. Sotto $E_{2}$ l'urna ha 3 bianche e 2 nere, quindi $P(B^{c}|E_{2})=\frac{2}{5}$ (del resto $1-\frac{3}{5}$ perché $P(\cdot|E_{2})$ è una misura di probabilità). Inoltre $P(B^{c})=\frac{7}{15}$. Dunque $$P(E_{2}|B^{c})=\frac{\frac{2}{5}\cdot\frac{2}{6}}{\frac{7}{15}}=\frac{2}{7}.$$
*Osservazione.* In generale non è vero che $P(E_{2}|B)+P(E_{2}|B^{c})=1$: infatti $\frac{3}{8}+\frac{2}{7}=\frac{37}{56}$.

**Calcolare la probabilità che esca un numero dispari sapendo di aver estratto una pallina bianca.**
La partizione $E_{1},E_{2},E_{3}$ non serve. Si considera $\{F_{1},\dots,F_{6}\}$ con $F_{k}=\{\text{esce }[k]\}$, $P(F_{k})=\frac{1}{6}$ e $$P(B|F_{k})=\begin{cases}\frac{4}{5}&k=1\\ \frac{3}{5}&k=2,3\\ \frac{2}{5}&k=4,5,6\end{cases}\quad(*)$$
Si chiede $P(D|B)$ con $D=F_{1}\cup F_{3}\cup F_{5}$. La formula $P(D|B)=\frac{P(B|D)P(D)}{P(B)}$ è vera ma poco utile (non sappiamo calcolare $P(B|D)$). Si procede così: $P(D|B)=P(F_{1}|B)+P(F_{3}|B)+P(F_{5}|B)$ con $$P(F_{k}|B)=\frac{P(B|F_{k})P(F_{k})}{P(B)}=P(B|F_{k})\cdot\frac{1}{6}\cdot\frac{15}{8}=P(B|F_{k})\cdot\frac{5}{16}=\begin{cases}\frac{1}{4}&k=1\\ \frac{3}{16}&k=2,3\\ \frac{1}{8}&k=4,5,6\end{cases}$$
($P(B)=\sum_{k=1}^{6}P(B|F_{k})P(F_{k})=\frac{8}{15}$ già calcolato; verifica: $\sum_{k}P(F_{k}|B)=\frac{4+3+3+2+2+2}{16}=1$, come deve essere per una partizione; la slide scrive per refuso $4+6+6+\dots$.)
Quindi $P(D|B)=\frac{1}{4}+\frac{3}{16}+\frac{1}{8}=\frac{4+3+2}{16}=\frac{9}{16}$, e $P(D^{c}|B)=1-\frac{9}{16}=\frac{7}{16}$ (oppure $P(F_{2}|B)+P(F_{4}|B)+P(F_{6}|B)=\frac{3+2+2}{16}$).

--->esercizi svolti sul pdf del professore da pagina 8 a pagina 10<---

> [!question] Domanda tipica d'esame
> Enunciare la formula delle probabilità totali e la formula di Bayes. Nell'esempio dado+urna, calcolare $P(E_{2}|B)$.
> Risposta: $P(A)=\sum_{i\in I}P(A|E_{i})P(E_{i})$ per una partizione $\{E_{i}\}$; $P(A|B)=\frac{P(B|A)P(A)}{P(B)}$, con $P(B)$ dato dalle probabilità totali. Si ha $P(E_{2}|B)=\frac{\frac{3}{5}\cdot\frac{2}{6}}{\frac{8}{15}}=\frac{3}{8}$.
## Indipendenza tra Eventi
Iniziamo con il caso di due eventi. 
Siamo interessati al caso in cui $P(A|B)=P(A)$ se $P(B)\neq 0$ (e si potrebbe dire "$A$ indipendente da $B$"), oppure al caso $P(B|A)=P(B)$ se $P(A)\neq 0$ (e si potrebbe dire "$B$ indipendente da $A$")

In questo senso abbiamo due concetti apparentemente diversi. Inoltre sembra che si debbano escludere in qualche caso gli eventi di probabilità zero.
In realtà la trattazione è più semplice e consideriamo la seguente definizione dove gli eventi di probabilità zero sono consentiti.
### Definizione (Indipendenza tra due eventi)
$A,B\in\mathcal{A}$ sono indipendenti se $P(A\cap B)=P(A)P(B)$
#### Osservazione
Se $A$ e $B$ sono indipendenti, allora lo sono anche $B$ e $A$.
Infatti $A\cap B=B\cap A$ e il prodotto tra due numeri è commutativo.
Quindi quello che si dimostra per $A$ e $B$ in un certi ordine, si dimostra anche per $A$ e $B$ presi in ordine inverso.
#### Proposizione
Siano $A,B\in\mathcal{A}$ con $P(B)\neq 0$, allora $$A\text{ e }B\text{ sono indipendenti}\iff P(A|B)=P(A)$$
**Dimostrazione**
Si ha $$\begin{array}{}
\text{A e B indipendenti}\overset{def}{\iff}P(A\cap B)=P(A)P(B)\iff \\
\iff \frac{P(A\cap B)}{P(B)}=\frac{P(A)P(B)}{P(B)}\overset{def}{\iff} P(A|B)=P(A)\Box
\end{array}$$
Per quanto osservato prima sulla simmetria tra A e B nella definizione di indipendenza si ha anche la seguente proposizione che si dimostra in maniera analoga.
#### Proposizione
Siano $A,B\in\mathcal{A}$ con $P(A)\neq 0$ allora $$\text{A e B sono indipendenti}\iff P(B|A)=P(B)$$

**Conseguenze**
1) Se un evento ha probabilità zero, allora è indipendente da qualunque altro. Infatti se prendiamo $A,B\in\mathcal{A}$ con $P(A)=0$, si ha $$\begin{cases}
0\leq P(A\cap B)\underset{(A\cap B)\subset A}{\leq} P(A)=0 & \implies P(A\cap B)=0 \\
P(A)P(B)=0\cdot P(B)=0
\end{cases}$$
e quindi $\underset{=0}{\underbrace{P(A\cap B)}}=\underset{=0}{\underbrace{P(A)P(B)}}$
2) supponiamo che $A$ e $B$ siano indipendenti
   Allora, se uno dei due eventi, o entrambi, vengono complementati, allora abbiamo ancora eventi indipendenti:
   $A^{c}$,$B$ indipendenti; $A$,$B^c$ indipendenti; $A^c$,$B^c$ indipendenti.
   Iniziamo verificando la prima relazione:
   - Si ha $P(A\cap B)=P(A)P(B)$ per ipotesi, allora 
    $P(A^{c}\cap B)\underset{\underset{{P(A\cap B)+P(A^{c}\cap B)=P(B)}}{\downarrow}}{=}P(B)-P(A\cap B)\underset{\text{ipotesi}}{=}P(B)-P(A)P(B)=$
    $=P(B)(1-P(A))=P(B)P(A^{c})=P(A^{c})P(B)$    
   - L'uguaglianza $P(A\cap B^{c})=P(A)P(B^{c})$ si dimostra in maniera analoga (del resto dato che si può scambiare il ruolo di $A$ e $B$ per simmetria nella definizione, quel che vale complementando solo il primo evento vale anche complementando solo il secondo)
   - Infine $$\begin{array}{}
A\text{ e }B\text{ sono indipendenti} & \implies A\text{ e }B^{c}\text{ sono indipendenti} \\
 & \implies A^{c}\text{ e }B^{c}\text{ sono indipendenti}
\end{array}$$
3) Mettendo insieme le conseguenze 1) e 2) si ha che
   se un evento ha probabilità 1, allora è indipendente da qualunque altro. Del resto abbiamo già visto in passato che $$P(B)=1\implies P(A|B)=P(A)$$

<----- Fine lezione 2 ----->

Ora consideriamo l'indipendenza tra più eventi.
### Definizione
Sia $\{A_{i}\}_{i\in I}$ una famiglia di eventi.
Allora si ha una famiglia di eventi indipendenti se:
- se la famiglia è finita(es. $\{A_{1},\dots,A_{n}\}$) ogni sottofamiglia di almeno due insiemi $\{A_{i_{1}},\dots,A_{i_{k}}\}$ con $k\geq 2$ si ha $$P(A_{i_{1}}\cap\dots\cap A_{i_{k}})=P(A_{i_{1}})\dots P(A_{i_{k}})$$
- se la famiglia è infinita, ogni sottofamiglia finita lo è in accordo con quanto detto sopra (cioè è una famiglia finita di eventi indipendenti).
#### Esempio (Famiglia di 3 eventi non indipendenti, ma indipendenti a due a due)
**Premessa**
Consideriamo 3 eventi $\{A_{1},A_{2},A_{3}\}$ allora c'è indipendenza se: $$\begin{array}{}
P(A_{1}\cap A_{2})=P(A_{1})P(A_{2}) \\
P(A_{1}\cap A_{3})=P(A_{1})P(A_{3}) & \text{e }P(A_{1}\cap A_{2}\cap A_{3})=P(A_{1})P(A_{2})P(A_{3}) \\
P(A_{2}\cap A_{3})=P(A_{2})P(A_{3})
\end{array}$$

Consideriamo la seguente situazione 
Una urna ha 4 carte numerate come segue e si estrae una carta a caso.
$$\begin{array}{|c|c|}
[1] & [2]  \\
[3] & [123] \\
\hline
\end{array}$$
Consideriamo gli eventi $A_{i}=\{$la carta estratta ha il numero $i\}_{i=1,2,3}$, allora $$\begin{array}{l}
P(A_{1})= P(A_{2})=P(A_{3})\overset{\overset{[i]\ \ [123]}{\downarrow}}{=}\frac{2}{4}=\frac{1}{2}\\
P(A_{1}\cap A_{2})= P(A_{1}\cap A_{3})=P(A_{2}\cap A_{3})\overset{\overset{[123]}{\downarrow}}{=}\frac{1}{4}\\
P(A_{1}\cap A_{2}\cap A_{3})\overset{\overset{[123]}{\downarrow}}{=}\frac{1}{4}
\end{array}$$
quindi $\underset{\frac{1}{4}}{P(A_{1}\cap A_{2})}\underset{=}{=}\underset{\frac{1}{2}\cdot \frac{1}{2}}{P(A_{1})P(A_{2})},\quad\underset{\frac{1}{4}}{P(A_{1}\cap A_{3})}\underset{=}{=}\underset{\frac{1}{2}\cdot \frac{1}{2}}{P(A_{1})P(A_{3})},\quad\underset{\frac{1}{4}}{P(A_{2}\cap A_{3})}\underset{=}{=}\underset{\frac{1}{2}\cdot \frac{1}{2}}{P(A_{2})P(A_{3})}$
e $P(A_{1}\cap A_{2}\cap A_{3})\neq P(A_{1})P(A_{2})P(A_{3})\quad$ (si ha $\frac{1}{4}\neq \frac{1}{8}$)

**Conclusione**
Eventi non indipendenti ma indipendenti a due a due
### Proposizione (senza dimostrazione)
Se $\{A_{i}\}_{i\in I}$ è una famiglia di eventi indipendenti, allora lo è anche qualsiasi altra famiglia ottenuta considerando il complementare di alcuni (o tutti) gli eventi.
#### Commento (con esempio)
L'ipotesi di indipendenza spesso segue dal modello in esame. 
Ad esempio si hanno eventi indipendenti nel caso di eventi legati a diversi lanci di moneta, diversi lanci di dado, diverse estrazioni da un insieme di oggetti (urna con palline, mazzo di carte, ecc) con reinserimento.
In altri casi gli eventi indipendenti escono fuori in maniera opportuna. Consideriamo il seguente esempio.
Si lanciano 3 monete eque e consideriamo i seguenti eventi $$A=\{\text{esce testa al 1° lancio}\}\quad\quad B=\{\text{escono esattamente 2 teste consecutive}\}$$
l'insieme di riferimento è $$\Omega=\{(T,T,T),(T,T,C),(T,C,T),(T,C,C),(C,T,T),(C,T,C),(C,C,T),(C,C,C)\}$$
Ognuno di questi 8 elementi ha probabilità $\frac{1}{2}\cdot \frac{1}{2}\cdot \frac{1}{2}=\frac{1}{8}\implies(\text{ spazio di probabilità uniforme ottenuto})$
perché i lanci di moneta sono indipendenti.
Si ha $$\begin{array}{l}
P(A)=P(\{(T,T,T),(T,T,C),(T,C,T),(T,C,C)\})=\frac{4}{8}=\frac{1}{2} \\
P(B)=P(\{(T,T,C),(C,T,T)\})= \frac{2}{8}=\frac{1}{4}\\
P(A\cap B)=P(\{(T,T,C)\})=\frac{1}{8} \\
P(A)P(B)=\frac{1}{2}\cdot\frac{1}{4}=\frac{1}{8}
\end{array}$$
Quindi $A$ e $B$ sono indipendenti e non era prevedibile a priori

> [!question] Domanda tipica d'esame
> Due eventi $A$ e $B$ sono indipendenti: lo sono anche $A^{c}$ e $B$? Tre eventi indipendenti a due a due lo sono anche a tre a tre?
> Risposta: sì, $P(A^{c}\cap B)=P(B)-P(A\cap B)=P(B)(1-P(A))=P(A^{c})P(B)$. No: con le 4 carte $[1],[2],[3],[123]$ si ha $P(A_{1}\cap A_{2}\cap A_{3})=\frac{1}{4}\neq\frac{1}{8}=P(A_{1})P(A_{2})P(A_{3})$.
## Cenni di calcolo combinatorio
Consideriamo un insieme di $n\geq 1$ elementi; senza perdere di generalità supponiamo che sia l'insieme $\{1,\dots,n\}$.
Siamo interessati al seguente insieme (**Disposizioni semplici**) $$D_{n,k}=\{(i_{1},\dots,i_{k})\}$$
sequenza ordinata di elementi in $\{1,\dots,n\}$, senza ripetizioni, di lunghezza $k\in\{1,\dots,n\}$

Ci si chiede quanto vale $\#D_{n,k}$

**Risposta**
Si hanno $n$ scelte per $i_{1},n-1$ scelte per $i_{2},\dots$ fino ad avere $n-(k-1)$ scelte per $i_{k}$. Quindi $$\#D_{n,k}=n(n-1)\dots(n-(k-1))=n(n-1)\dots(n-k+1)$$
Se si vuole fare riferimento al fattoriale si ha $$\#D_{n,k}=n(n-1)\dots(n-k+1)\quad \frac{(n-k)!}{(n-k)!}= \frac{n!}{(n-k)!}$$
nel caso $k=n$ si ha $$\#D_{n,k}=\frac{n!}{(n-k)!}= \frac{n!}{0!}=n!$$
in questo caso gli elementi si dicono permutazioni di $\{1,\dots,n\}$

Ora consideriamo il seguenti insieme: $$C_{n,k}=\{\{i_{1},\dots,i_{k}\}\}$$
sottoinsiemi di $\{1,\dots,n\}$ di $k$  elementi distinti (**Combinazioni semplici**)
Ci si chiede quanto vale $\#C_{n,k}$

Si ha $C_{n,0}=\{\varnothing\}\implies\#C_{n,0}=1$
e $C_{n,n}=\{\{1,\dots,n\}\}\implies\#C_{n,n}=1$
ora consideriamo $k$ con $k\in\{1,\dots,n-1\}$ allora preso un sottoinsieme $\{i_{1},\dots,i_{k}\}$, considerando tutte le permutazioni di $\{i_{1},\dots,i_{k}\}$ danno origine a particolari sequenze ordinate in $D_{n,k}$; poi tutti gli elementi di $D_{n,k}$, possono essere visti come una particolare permutazione di elementi di un certo insieme.
#### Esempio
$$\begin{array}{}
n=4\quad k=2 & C_{n,k}= & \{\{1,2\}, & \{1,3\}, & \{1,4\}, & \{2,3\}, & \{2,4\}, & \{3,4\}\} \\
\text{elementi di }D_{4,2} & \rightarrow &  (1,2) & (1,3) & (1,4) & (2,3) & (2,4) & (3,4) \\
 &  & \underset{\uparrow }{(2,1)} & \underset{}{(3,1)} & \underset{}{(4,1)} & (3,2) & (4,2) & (4,3) \\
 &  & (k!=2!=2 & \underset{\text{permutazioni}}{} & \underset{\text{per ogni}}{} & \underset{\text{elemento di }}{} & C_{4,2})
\end{array}$$
In effetti $\#D_{4,2}=\frac{4!}{(4-2)!}=\frac{4\cdot 3\cdot 2}{2}=12$
*(extra, non da slide)* Analogamente per $n=4$, $k=3$: $D_{4,3}$ ha $\frac{4!}{1!}=24$ elementi; ciascun sottoinsieme di $C_{4,3}=\{\{1,2,3\},\{1,2,4\},\{1,3,4\},\{2,3,4\}\}$ dà origine a $3!=6$ sequenze di $D_{4,3}$, quindi $\#C_{4,3}=\frac{4!}{3!\,1!}=4$.

A partire da questo esempio possiamo dire che $\#C_{n,k}\cdot k!=\#D_{n,k}$
da cui segue $$\#C_{n,k}=\frac{\#D_{n,k}}{k!}=\frac{n!}{k!(n-k)!}$$
l'espressione ottenuta è il coefficiente binomiale e si usa la notazione $\binom{n}{k}=\frac{n!}{k!(n-k)!}$. Questa formula vale anche per $k=0$ e per $k=n$.
#### Commenti
In generale si ha $$\binom{n}{k}=\binom{n}{n-k}$$
ad ogni sottoinsieme di $k$ elementi corrisponde il suo complementare di $n-k$ elementi; quindi $\#C_{n,k}=\#C_{n,n-k}$ 
Perché $$\binom{n}{n-k}=\frac{n!}{(n-k)!(n-(n-k))!}=\frac{n!}{(n-k)!k!}=\binom{n}{k}$$
In particolare per $k=0$ e $k=1$ si ha $$\begin{array}{l}
\binom{n}{0}=\binom{n}{n}=\frac{n!}{n!(n-n)!}=\frac{\not n!}{\not n!\ 0!}=1 & \leftarrow\underset{\text{con }n\text{ elementi c'è solo }\{1,\dots,n\}}{\text{con 0 elementi c'è solo }\varnothing} \\
\binom{n}{1}=\binom{n}{n-1}=\frac{n!}{1!(n-1)!}=\frac{n(n-1)!}{1\cdot(n-1)!}=n & \leftarrow\underset{\text{con }n-1\text{ elementi ci sono i loro complementari}}{\text{con 1 elemento ci sono }\{1\},\{2\},\dots,\{n\}}
\end{array}$$

#### Spiegazione del termine "coefficiente binomiale"
Il nome segue dalla formula del binomio di Newton: $$(a+b)^{n}=\sum_{k=0}^{n}\binom{n}{k}a^{k}b^{n-k}$$
Infatti $(a+b)^{n}=\underbrace{(a+b)\cdots(a+b)}_{n\text{ volte}}$ e per ogni $k\in\{0,1,\dots,n\}$ si hanno termini del tipo $a^{k}b^{n-k}$; contando quanti ce ne sono si vede che compare il coefficiente binomiale.

> [!question] Domanda tipica d'esame
> Quanto valgono $\#D_{n,k}$ e $\#C_{n,k}$? Perché $\binom{n}{k}=\binom{n}{n-k}$?
> Risposta: $\#D_{n,k}=\frac{n!}{(n-k)!}$ (sequenze ordinate senza ripetizioni); ogni sottoinsieme di $k$ elementi ha $k!$ permutazioni, quindi $\#C_{n,k}=\frac{\#D_{n,k}}{k!}=\binom{n}{k}$. A ogni sottoinsieme di $k$ elementi corrisponde il suo complementare di $n-k$ elementi.
## Applicazione di formule di calcolo combinatorio:
### Estrazioni casuali in blocco
Abbiamo oggetti di 2 tipi: $n_{1}$ di tipo 1, $n_{2}$ di tipo 2 $$\begin{array}{|c|c|}
n_{1} & n_{2} \\
1 & 2 \\
\hline
\end{array}$$
Si estraggano a caso in blocco (cioè contemporaneamente) $n$ oggetti, dove $n<n_{1}+n_{2}$.

Quanto vale la probabilità di estrarre $k$ oggetti di tipo 1?
(quindi contemporaneamente si estraggono $n-k$ oggetti di tipo 2).

Indichiamo questa probabilità con $p_{k}$ e si ha $$p_{k}=\begin{cases}
0 & \text{se }k>n_{1}\text{ oppure se }n-k>n_{2} \\
\text{"da calcolare"} & \text{se } \begin{cases}
0\leq k\leq n_{1} \\
0\leq n-k\leq n_{2}
\end{cases}
\end{cases}$$
Bisogna osservare che in generale abbiamo $\binom{n_{1}+n_{2}}{n}$ casi possibili e tutti equiparabili da tutti i sottoinsiemi di $n$ elementi a partire da $n_{1}+n_{2}$ elementi.
I casi favorevoli all'evento di "estrarre $k$ oggetti di tipo 1 e $n-k$ di tipo 2" devono essere pensati come sottoinsiemi del tipo $$\{\underset{\text{sottoinsieme di }\{1,\dots,n_{1}\}}{\underbrace{i_{1},\dots,i_{k}}},\underset{\text{sottoinsieme di }\{n_{1}+1,\dots,n_{1}+n_{2}\}}{\underbrace{j_{1},\dots,j_{n-k}}}\}$$
Abbiamo $\binom{n_{1}}{k}$ scelte per $\{i_{1},\dots,i_{k}\}$ e $\binom{n_{2}}{n-k}$ scelte per $\{j_{1},\dots,j_{n-k}\}$.
In conclusione il numero di casi favorevoli è dato dal prodotto $\binom{n_{1}}{k}\binom{n_{2}}{n-k}$ e quindi $$p_{k}=\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}$$
#### Osservazione
Questa formula vale anche se $k>n_{1}$ oppure $n-k>n_{2}$ usando la convenzione che $\binom{a}{b}=0$ quando $b>a$
#### Esempio
$$\begin{matrix}
n_{1}=3,n_{2}=2,n=3 & \binom{n_{1}+n_{2}}{n}=\binom{3+2}{3}=\binom{5}{3}=\frac{5\cdot 4\cdot 3!}{3!\cdot2!}=\frac{5\cdot 4}{2}=10 \\
\begin{array}{|c|c|}
3 & 2 \\
1 & 2 \\
\hline
\end{array} & \text{convenzione }\begin{cases}
\text{tipo }1 & 1,2,3 \\
\text{tipo }2 & 4,5
\end{cases}
\end{matrix}$$
In quello che segue scrivo i $\binom{5}{3}=10$ sottoinsiemi e indico accanto il numero di elementi del tipo 1 $$\begin{array}{}
\{1,2,3\}\rightarrow3 & \{1,2,4\}\rightarrow2 & \{1,2,5\}\rightarrow2 \\
\{1,3,4\}\rightarrow2 & \{1,3,5\}\rightarrow2 & \{1,4,5\}\rightarrow1 \\
\{2,3,4\}\rightarrow2 & \{2,3,5\}\rightarrow2 & \{2,4,5\}\rightarrow1 \\
\{3,4,5\}\rightarrow1
\end{array}$$Quindi $p_{0}=0,p_{1}=\frac{3}{10},p_{2}=\frac{6}{10},p_{3}=\frac{1}{10}$ (perché i 10 casi hanno tutti probabilità $\frac{1}{10}$)
Questi valori sono in accordo con la formula $$p_{k}=\frac{\binom{3}{k}\binom{2}{3-k}}{\binom{5}{3}}=\frac{\binom{3}{k}\binom{2}{3-k}}{10}=\begin{cases}
k=0 & 0\text{ perché }\binom{2}{3}=0 & \text{almeno 1 elemento di tipo 1} \\
k=1 & \frac{3\cdot1}{10}=\frac{3}{10} \\
k=2 & \frac{3\cdot2}{10}=\frac{6}{10} \\
k=3 & \frac{1\cdot1}{10}=\frac{1}{10}
\end{cases}$$
### Estensione al caso con più di 2 tipi
Supponiamo di avere $$\begin{array}{|c|c|}
n_{1} & \dots & n_{r} \\
1 & \dots & r \\
\hline
\end{array}$$
e di estrarre a caso $n$ [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|oggetti in blocco]] con $n<n_{1}+n_{2}+\dots+n_{r}$

Quanto vale la probabilità di estrarre $k_{1}\text{ oggetti tipo 1},\dots,k_{r}\text{ oggetti tipo }r$, dove $k_{1}+\dots+k_{r}=n$?

Con ragionamenti simili si vede che $$p_{k_{1},\dots,k_{r}}=\frac{\binom{n_{1}}{k_{1}}\cdot\dots \cdot\binom{n_{r}}{k_{r}}}{\binom{n_{1}+\dots+n_{r}}{n}}\quad\quad\text{con }\binom{a}{b}=0\text{ per }b>a$$

> [!question] Domanda tipica d'esame
> Si estraggono in blocco $n$ oggetti da $n_{1}$ di tipo 1 e $n_{2}$ di tipo 2: qual è la probabilità di $k$ oggetti di tipo 1? Calcolarla per $n_{1}=3$, $n_{2}=2$, $n=3$, $k=2$.
> Risposta: $p_{k}=\frac{\binom{n_{1}}{k}\binom{n_{2}}{n-k}}{\binom{n_{1}+n_{2}}{n}}$ (con $\binom{a}{b}=0$ per $b>a$); $p_{2}=\frac{\binom{3}{2}\binom{2}{1}}{\binom{5}{3}}=\frac{6}{10}$.
## Esercizi riepilogo del capitolo
Presenti sul pdf Lezione 03 a pagina 8 e 9

#### Esercizio
Un'urna ha 3 palline bianche e 4 nere. Si estraggono 2 palline a caso, una alla volta e **con** reinserimento.
1) Calcolare la probabilità di estrarre due colori uguali.
2) Calcolare la probabilità di estrarre almeno una pallina nera.

**Svolgimento.** $B_{k}=\{k\text{-esima estratta bianca}\}$, $N_{k}=\{k\text{-esima estratta nera}\}$, $k=1,2$ (quindi $B_{k}=N_{k}^{c}$). Gli eventi di estrazioni diverse sono indipendenti perché le estrazioni sono con reinserimento; inoltre $P(B_{1})=P(B_{2})$ e $P(N_{1})=P(N_{2})$ perché l'urna è composta sempre allo stesso modo.
1) $P((B_{1}\cap B_{2})\cup(N_{1}\cap N_{2}))=P(B_{1}\cap B_{2})+P(N_{1}\cap N_{2})$ (intersezione vuota) $=P(B_{1})P(B_{2})+P(N_{1})P(N_{2})=\frac{3}{7}\cdot\frac{3}{7}+\frac{4}{7}\cdot\frac{4}{7}=\frac{25}{49}$.
2) $1^{\circ}$ modo: $P(N_{1}\cup N_{2})=P(N_{1})+P(N_{2})-P(N_{1}\cap N_{2})=\frac{4}{7}+\frac{4}{7}-\frac{4}{7}\cdot\frac{4}{7}=\frac{56-16}{49}=\frac{40}{49}$.
$2^{\circ}$ modo (De Morgan): $P(N_{1}\cup N_{2})=1-P(N_{1}^{c}\cap N_{2}^{c})=1-P(B_{1}\cap B_{2})=1-\frac{3}{7}\cdot\frac{3}{7}=\frac{40}{49}$.

**Osservazione (senza reinserimento).** Non c'è più indipendenza tra estrazioni diverse. Per le probabilità totali ($\{B_{1},N_{1}\}$ è una partizione) $P(B_{2})=\frac{2}{6}\cdot\frac{3}{7}+\frac{3}{6}\cdot\frac{4}{7}=\frac{18}{42}=\frac{3}{7}=P(B_{1})$ (accade sempre, per questo tipo di urna), quindi $P(N_{2})=\frac{4}{7}$.
1) $P(B_{1}\cap B_{2})+P(N_{1}\cap N_{2})=\frac{2}{6}\cdot\frac{3}{7}+\frac{3}{6}\cdot\frac{4}{7}=\frac{3}{7}$.
2) $P(N_{1}\cup N_{2})=\frac{4}{7}+\frac{4}{7}-\frac{3}{6}\cdot\frac{4}{7}=\frac{8}{7}-\frac{12}{42}=\frac{36}{42}=\frac{6}{7}$ (oppure $1-P(B_{2}|B_{1})P(B_{1})=1-\frac{2}{6}\cdot\frac{3}{7}=\frac{6}{7}$).

*Commento.* La distribuzione ipergeometrica (anticipazione: si vedrà in [[02 - Modelli discreti#Distribuzioni binomiale e ipergeometrica]]) si può usare anche per estrazioni casuali senza reinserimento: $P(B_{1}\cap B_{2})=\frac{\binom{3}{2}\binom{4}{0}}{\binom{7}{2}}=\frac{1}{7}$ e $P(N_{1}\cap N_{2})=\frac{\binom{3}{0}\binom{4}{2}}{\binom{7}{2}}=\frac{2}{7}$, che coincidono con i valori ottenuti sopra.

<----- Fine lezione 3 ----->

> [!question] Domanda tipica d'esame
> Da un'urna con $3$ bianche e $4$ nere si estraggono $2$ palline. Calcolare la probabilità di estrarre almeno una nera con e senza reinserimento.
> **Risposta.** Con reinserimento le estrazioni sono indipendenti: $1-P(B_{1}\cap B_{2})=1-\frac{3}{7}\cdot\frac{3}{7}=\frac{40}{49}$. Senza reinserimento $1-P(B_{2}|B_{1})P(B_{1})=1-\frac{2}{6}\cdot\frac{3}{7}=\frac{6}{7}$.
## Esercizi della lezione 4
#### Esercizio (difetti di una fabbrica)
Gli elementi prodotti da una fabbrica possono avere due tipi di difetti: il difetto 1 con probabilità $\frac{3}{100}$, il difetto 2 con probabilità $\frac{7}{100}$. I due difetti si possono considerare indipendenti. Si sceglie un elemento prodotto a caso.
1) Calcolare la probabilità che siano presenti entrambi i difetti.
2) Calcolare la probabilità che l'elemento sia difettoso (sia presente almeno uno dei due difetti).
3) Calcolare la probabilità che l'elemento abbia il difetto 1 sapendo che è difettoso.
4) Calcolare la probabilità che l'elemento abbia un solo difetto sapendo che è difettoso.

**Svolgimento.** $D_{k}=\{\text{l'elemento ha il difetto }k\}$, $k=1,2$, indipendenti con $P(D_{1})=\frac{3}{100}$, $P(D_{2})=\frac{7}{100}$.
1) $P(D_{1}\cap D_{2})=P(D_{1})P(D_{2})=\frac{21}{10000}$.
2) $P(D_{1}\cup D_{2})=P(D_{1})+P(D_{2})-P(D_{1})P(D_{2})=\frac{300+700-21}{10000}=\frac{979}{10000}$. Metodo alternativo: $1-P(D_{1}^{c}\cap D_{2}^{c})=1-P(D_{1}^{c})P(D_{2}^{c})=1-\frac{97\cdot93}{10000}=\frac{10000-9021}{10000}=\frac{979}{10000}$ (indipendenza dei complementari).
3) Poiché $D_{1}\subset D_{1}\cup D_{2}$: $P(D_{1}|D_{1}\cup D_{2})=\frac{P(D_{1})}{P(D_{1}\cup D_{2})}=\frac{3/100}{979/10000}=\frac{300}{979}$.
4) Sia $E=$"un solo difetto" ($E\subset D_{1}\cup D_{2}$, $P(D_{1}\cup D_{2})=P(E)+P(D_{1}\cap D_{2})$). $P(E|D_{1}\cup D_{2})=\frac{P(E)}{P(D_{1}\cup D_{2})}=1-\frac{P(D_{1}\cap D_{2})}{P(D_{1}\cup D_{2})}=1-\frac{21}{979}=\frac{958}{979}$.

#### Esercizio (urna con tre tipi di monete)
Un'urna ha $n_{1}$ monete con due teste, $n_{2}$ con due croci, $n_{3}$ con una testa e una croce. Si sceglie una moneta a caso e si scopre una faccia a caso della moneta ed è testa. Calcolare la probabilità che l'altra faccia (non scoperta) sia testa.

**Svolgimento.** $T_{1}=\{\text{la faccia scoperta è testa}\}$, $T_{2}=\{\text{la faccia non scoperta è testa}\}$, $M_{i}=\{\text{scelta moneta di tipo }i\}$. Si chiede $P(T_{2}|T_{1})=\frac{P(T_{2}\cap T_{1})}{P(T_{1})}$; si ha $M_{1}=T_{1}\cap T_{2}$ e per $P(T_{1})$ si usa la [[#Formula delle Probabilità Totali|formula delle probabilità totali]] sulla partizione $M_{1},M_{2},M_{3}$: $$P(T_{2}|T_{1})=\frac{\frac{n_{1}}{n_{1}+n_{2}+n_{3}}}{1\cdot\frac{n_{1}}{n_{1}+n_{2}+n_{3}}+0\cdot\frac{n_{2}}{n_{1}+n_{2}+n_{3}}+\frac{1}{2}\cdot\frac{n_{3}}{n_{1}+n_{2}+n_{3}}}=\frac{n_{1}}{n_{1}+\frac{n_{3}}{2}}=\frac{2n_{1}}{2n_{1}+n_{3}}.$$
*Interpretazione:* è il rapporto tra il numero di facce testa delle monete di tipo 1 e il numero di facce testa totali.

#### Esercizio (terno al lotto)
Un'urna ha 90 palline numerate da 1 a 90. Un giocatore gioca il terno $1,2,3$ nel caso di estrazione a caso di 5 palline in blocco.
1) Calcolare la probabilità di fare terno.
2) Calcolare la probabilità di fare terno con l'urna truccata aggiungendo 3 palline con i numeri $1,2,3$.
3) Calcolare la probabilità che il trucco venga scoperto.

**Svolgimento** (si omettono i calcoli dei coefficienti binomiali).
1) $P(\text{terno senza trucco})=\frac{\binom{3}{3}\binom{87}{2}}{\binom{90}{5}}=\frac{87\cdot43}{\binom{90}{5}}$.
2) $P(\text{terno con trucco})=\frac{\binom{2}{1}\binom{2}{1}\binom{2}{1}\binom{87}{2}}{\binom{93}{5}}=\frac{2\cdot2\cdot2\cdot87\cdot43}{\binom{93}{5}}$. Dai valori numerici si vede che con l'urna truccata la probabilità aumenta, anche se è comunque piccola. *(extra, non da slide)* La formula, come nella slide, conta solo le cinquine con una sola copia di ciascun numero $1,2,3$; con l'urna truccata si fa terno anche estraendo entrambe le copie di un numero. Il conteggio completo dei casi favorevoli è $8\binom{87}{2}+3\cdot2\cdot2\cdot87+3\cdot2=29928+1044+6=30978$ (una copia per numero; un numero doppio e una pallina qualsiasi; due numeri doppi e il terzo singolo), quindi $P(\text{terno con trucco})=\frac{30978}{\binom{93}{5}}$.
3) $E_{k}=\{\text{estratte le due palline con il numero }k\}$, $k=1,2,3$. Si chiede $P(E_{1}\cup E_{2}\cup E_{3})=\sum P(E_{i})-\sum P(E_{i}\cap E_{j})+P(E_{1}\cap E_{2}\cap E_{3})$ (identità di Bonferroni, vedi [[#Conseguenze della Definizione di Misura di Probabilità]]). $P(E_{1})=\frac{\binom{2}{2}\binom{91}{3}}{\binom{93}{5}}=P(E_{2})=P(E_{3})$; $P(E_{1}\cap E_{2})=\frac{\binom{4}{4}\binom{89}{1}}{\binom{93}{5}}=\frac{89}{\binom{93}{5}}$ (uguale per le altre coppie); $P(E_{1}\cap E_{2}\cap E_{3})=0$ perché servirebbero 6 palline e ne vengono estratte 5. Quindi $$P(E_{1}\cup E_{2}\cup E_{3})=\frac{3}{\binom{93}{5}}\left[\binom{91}{3}-89\right].$$

#### Esercizio (tre urne e $n$ palline)
Tre urne inizialmente vuote e $n$ palline; ogni pallina sceglie a caso una delle tre urne dove andare, indipendentemente dalle altre. Calcolare la probabilità che almeno un'urna resti vuota (dopo che tutte le palline hanno scelto l'urna).

**Svolgimento.** $E_{k}=\{\text{l'urna }k\text{ resta vuota}\}$, $k=1,2,3$. Si chiede $P(E_{1}\cup E_{2}\cup E_{3})$ con l'identità di Bonferroni. $P(E_{1})=P(E_{2})=P(E_{3})=\left(\frac{2}{3}\right)^{n}$; $P(E_{i}\cap E_{j})=\left(\frac{1}{3}\right)^{n}$; $P(E_{1}\cap E_{2}\cap E_{3})=0$ (non possono restare vuote tutte). Allora $$P(E_{1}\cup E_{2}\cup E_{3})=3\left[\left(\frac{2}{3}\right)^{n}-\left(\frac{1}{3}\right)^{n}\right].$$
Verifica: per $n=1$ si ha $3\left[\frac{2}{3}-\frac{1}{3}\right]=1$ e per $n=2$ si ha $3\left[\frac{4}{9}-\frac{1}{9}\right]=1$, come ci si aspetta.

#### Esercizio (estrazioni senza reinserimento fino a svuotare l'urna)
Un'urna ha 2 palline rosse e 4 nere. Si estraggono a caso palline, una alla volta e senza reinserimento, fino a svuotare l'urna.
1) Calcolare la probabilità che l'ultima pallina estratta sia rossa.
2) Calcolare la probabilità che l'ultima pallina estratta sia rossa sapendo che la prima estratta è rossa.
3) Calcolare la probabilità che prima e ultima estratte siano rosse.

**Svolgimento.** Conviene fare riferimento allo [[#Spazio di Probabilità Uniforme Discreto|spazio di probabilità uniforme discreto]] $\Omega=D_{6,6}=\{\omega=(\omega_{1},\dots,\omega_{6})\}$ con $P(\{\omega\})=\frac{1}{\#D_{6,6}}=\frac{1}{6!}$; le palline 1,2 sono rosse e 3,4,5,6 sono nere.
1) $P(\{\omega_{6}=1\}\cup\{\omega_{6}=2\})=\frac{5!}{6!}+\frac{5!}{6!}=\frac{1}{6}+\frac{1}{6}=\frac{1}{3}$ (unione disgiunta; coincide con la probabilità che la 1ª estratta sia rossa, $\frac{2}{6}$; in generale la $i$-esima estratta è rossa con probabilità $\frac{1}{3}$).
2) $P(\text{ultima rossa}|\text{1ª rossa})=\frac{P(\{1^{a}\text{ e ultima rosse}\})}{P(1^{a}\text{ rossa})}$; $P(1^{a}\text{ e ultima rosse})=\frac{4!}{6!}+\frac{4!}{6!}=\frac{2}{30}=\frac{1}{15}$. Quindi $\frac{1/15}{1/3}=\frac{1}{5}$ (dopo la 1ª rossa resta 1 rossa su 5 palline).
3) $P(1^{a}\text{ e ultima rosse})=\frac{1}{15}$. Interpretazione: le posizioni delle due rosse sono i $\binom{6}{2}=15$ sottoinsiemi equiprobabili di $\{1,\dots,6\}$, e a noi serve $\{1,6\}$.

#### Esercizio (due numeri consecutivi)
Un'urna contiene $n\geq2$ palline numerate da 1 a $n$. Si estraggono a caso due palline, una alla volta e senza reinserimento. Calcolare la probabilità di estrarre due numeri consecutivi.

**Svolgimento.** Due modi; $E$ è l'evento di interesse.
$1^{\circ}$ modo: partizione $E_{k}=\{\text{il }1^{\circ}\text{ numero estratto è }k\}$, $k=1,\dots,n$, $P(E_{k})=\frac{1}{n}$; $P(E|E_{k})=\frac{1}{n-1}$ per $k=1,n$ e $\frac{2}{n-1}$ per $k=2,\dots,n-1$. Per le probabilità totali: $P(E)=\frac{1}{n}\left(\frac{1}{n-1}+\frac{2}{n-1}(n-2)+\frac{1}{n-1}\right)=\frac{2(n-2)+2}{n(n-1)}=\frac{2}{n}$.
$2^{\circ}$ modo: le sequenze ordinate senza ripetizioni sono $n(n-1)$, equiprobabili (spazio uniforme discreto); $\#E=\#\{(1,2),(2,1),(2,3),(3,2),\dots,(n-1,n),(n,n-1)\}=2(n-1)$. Quindi $P(E)=\frac{2(n-1)}{n(n-1)}=\frac{2}{n}$.

#### Esercizio (due dadi)
Si considera il lancio di due dadi equi (due volte lo stesso dado, o anche due dadi diversi: non c'è differenza).
1) Calcolare la probabilità di ottenere due numeri minori o uguali a 4.
2) Calcolare la probabilità dello stesso evento della domanda precedente sapendo che la somma dei due numeri ottenuti è uguale a 7.

**Svolgimento.**
1) Gli eventi di lanci di dadi diversi sono indipendenti. Per $(\omega_{1},\omega_{2})\in\Omega=\{1,\dots,6\}\times\{1,\dots,6\}$ si ha $P(\{\omega\})=\frac{1}{6}\cdot\frac{1}{6}=\frac{1}{36}$; quindi, essendo $\#\Omega=36$, si ha uno spazio di probabilità uniforme discreto. $P(A)=\frac{\#A}{36}=\frac{16}{36}=\frac{4}{9}$ (i 16 elementi sono le coppie $(i,j)$ con $i,j\in\{1,\dots,4\}$). Oppure: $A_{k}=\{\text{si ha}\leq4\text{ nel lancio del }k\text{-esimo dado}\}$, $k=1,2$, indipendenti, $A=A_{1}\cap A_{2}$ e $P(A)=\frac{4}{6}\cdot\frac{4}{6}=\frac{4}{9}$.
2) $E=\{\text{somma }7\}=\{(1,6),(6,1),(2,5),(5,2),(3,4),(4,3)\}$; $P(A|E)=\frac{\#(A\cap E)}{\#E}=\frac{\#\{(3,4),(4,3)\}}{6}=\frac{1}{3}$.

*Osservazione.* $A_{1}$ e $A_{2}$ sono indipendenti; lo sono anche sotto $E$? Dovrebbe essere $P(A_{1}\cap A_{2}|E)=P(A_{1}|E)P(A_{2}|E)$. Si ha $P(A_{1}\cap A_{2}|E)=P(A|E)=\frac{1}{3}$, mentre $P(A_{1}|E)=\frac{\#\{(1,6),(2,5),(3,4),(4,3)\}}{6}=\frac{2}{3}$, $P(A_{2}|E)=\frac{\#\{(6,1),(5,2),(4,3),(3,4)\}}{6}=\frac{2}{3}$ e il prodotto vale $\frac{4}{9}\neq\frac{1}{3}$. La risposta è **NO**: l'indipendenza non si conserva condizionando.

<----- Fine lezione 4 ----->

> [!question] Domanda tipica d'esame
> Si lanciano due dadi equi. Gli eventi $A_{k}=\{\text{il }k\text{-esimo dado dà un numero}\leq4\}$, $k=1,2$, sono indipendenti; restano indipendenti condizionando all'evento $E=\{\text{somma }7\}$?
> **Risposta.** No: $P(A_{1}\cap A_{2}|E)=\frac{2}{6}=\frac{1}{3}$, mentre $P(A_{1}|E)P(A_{2}|E)=\frac{2}{3}\cdot\frac{2}{3}=\frac{4}{9}$. L'indipendenza non si conserva condizionando.
