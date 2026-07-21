## Es1 — Probabilità discreta elementare
Primo esercizio dello scritto. Il contesto è sempre concreto — **urne** con palline colorate o numerate, **dadi** o **monete** lanciati una o più volte — e la richiesta è una probabilità, una densità discreta, oppure una media/varianza di una variabile aleatoria di conteggio.

Non c'è teoria da esporre: tutto l'esercizio consiste nel riconoscere **quale modello discreto** descrive l'esperimento e applicarne le formule. La teoria che sta sotto è quella di [[02 - Modelli discreti#Variabili aleatorie discrete|Variabili aleatorie discrete]] e delle distribuzioni notevoli; qui si tratta solo di scegliere la porta giusta e attraversarla in fretta.
### Il ragionamento in tre domande
Davanti a una traccia di Es1, prima di scrivere qualsiasi formula, rispondere in quest'ordine:

1. **Le prove sono indipendenti?** Cioè: quello che succede a un'estrazione cambia le probabilità della successiva?

2. **L'ordine conta?** «Estrarre la sequenza (bianco, nero, bianco)» è una cosa, «estrarre due bianche e una nera» è un'altra.

3. **Cosa conta la variabile aleatoria?** Il **numero di successi** in $n$ prove fissate, oppure il **numero di prove** necessarie perché accada qualcosa? Sono due famiglie diverse di distribuzioni.

> [!warning] La prima domanda è il bivio che decide tutto
> **Con reinserimento** → la composizione dell'urna non cambia mai, le prove sono indipendenti e hanno tutte la stessa probabilità di successo → **binomiale** se conti i successi, **geometrica** o **binomiale negativa** se conti quante prove servono.
>
> **Senza reinserimento** → ogni estrazione modifica l'urna, le prove sono dipendenti → **ipergeometrica**, oppure catena di condizionate $P(A_1)P(A_2|A_1)P(A_3|A_1\cap A_2)$ con la [[01 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]].
>
> **In blocco** (tutte insieme, senza ordine) → è equivalente a "senza reinserimento", ma conviene contare direttamente i sottoinsiemi con $\binom{n}{k}$: vedi [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni in blocco]].

Il lancio ripetuto di dadi e monete è **sempre** con reinserimento: il dado non si consuma, ogni lancio riparte da zero.

Per il confronto diretto tra i due schemi sullo stesso esercizio, la nota di teoria ha un esempio apposta: [[02 - Modelli discreti#Esempio: confronto binomiale / ipergeometrica|confronto binomiale / ipergeometrica]].
### Distribuzioni discrete da avere a memoria

| Distribuzione | Quando | Densità | Media | Varianza |
|---|---|---|---|---|
| **Bernoulli**$(p)$ | una sola prova, successo/insuccesso | $p_X(1)=p,\ p_X(0)=1-p$ | $p$ | $p(1-p)$ |
| **Binomiale**$(n,p)$ | $n$ prove indipendenti, conta i successi | $\binom{n}{k}p^k(1-p)^{n-k}$ | $np$ | $np(1-p)$ |
| **Ipergeometrica**$(N,K,n)$ | $n$ estratte senza reinserimento da $N$ oggetti di cui $K$ "buoni" | $\dfrac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}$ | $n\frac{K}{N}$ | $n\frac{K}{N}\left(1-\frac{K}{N}\right)\frac{N-n}{N-1}$ |
| **Geometrica traslata**$(p)$ | numero di prove **fino al primo** successo, $k\ge1$ | $(1-p)^{k-1}p$ | $\dfrac{1}{p}$ | $\dfrac{1-p}{p^2}$ |
| **Binomiale negativa traslata**$(r,p)$ | numero di prove **fino all'$r$-esimo** successo | $\binom{k-1}{r-1}p^r(1-p)^{k-r}$ | $\dfrac{r}{p}$ | $\dfrac{r(1-p)}{p^2}$ |
| **Multinomiale** | $n$ prove indipendenti con **più di due** esiti | $\dfrac{n!}{k_1!\cdots k_m!}p_1^{k_1}\cdots p_m^{k_m}$ | — | — |
| **Poisson**$(\lambda)$ | conteggi rari; compare più spesso in Es3 | $\dfrac{\lambda^k}{k!}e^{-\lambda}$ | $\lambda$ | $\lambda$ |

Costruzione e dimostrazioni: [[02 - Modelli discreti#Distribuzioni binomiale e ipergeometrica|Distribuzioni binomiale e ipergeometrica]], [[02 - Modelli discreti#Distribuzione geometrica|Distribuzione geometrica]], [[02 - Modelli discreti#Distribuzione binomiale negativa|Distribuzione binomiale negativa]], [[02 - Modelli discreti#Distribuzione multinomiale|Distribuzione multinomiale]], [[02 - Modelli discreti#Distribuzioni uniforme discreta e di Poisson|Distribuzioni uniforme discreta e di Poisson]].

> [!warning] Traslata o no: è la trappola più costosa della tabella
> Le versioni **traslate** contano il **numero di prove** e partono da $k=1$ (o $k=r$); le versioni non traslate contano il **numero di insuccessi prima** del successo e partono da $k=0$.
>
> La differenza sulla media è tra $\frac{1}{p}$ e $\frac{1-p}{p}$ — cioè esattamente una prova, quella riuscita. Macci nelle sue soluzioni scrive esplicitamente *"binomiale negativa traslata"*, e nella nota di teoria le due versioni sono costruite in parallelo come $X$ e $Y$: vedi [[02 - Modelli discreti#Calcolo delle densità discrete di $X$ e $Y$|densità di X e Y]].

> [!info] Media e varianza non sono ancora negli appunti di teoria
> Le note di [[02 - Modelli discreti]] costruiscono le densità ma non la **speranza matematica**, che il prof introduce più avanti nel corso. Finché quelle note non arrivano, la tabella qui sopra è l'unica fonte: le formule sono comunque quelle standard e coincidono con i risultati dei cenni alle soluzioni.

### Le serie che chiudono il conto
Quando la domanda riguarda un evento su **infinite** prove — «esce testa per la prima volta a un lancio pari», «il procedimento si ripete un numero pari di volte» — non c'è nessuna formula da tabella da applicare: la risposta è una **serie geometrica** che devi costruire tu.

$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad (|r|<1)$$

È la formula dimostrata in [[02 - Modelli discreti#Formula della serie geometrica|serie geometrica]]. Il punto delicato non è la formula, è **da dove parte l'indice $h$**: va letta la richiesta, scritto l'evento come unione disgiunta $\bigcup_k\{X=\dots\}$, e solo dopo sommato.

Se invece la domanda è del tipo «servono almeno $j$ prove», esiste già pronta la formula della coda, $P(Y\ge j)=(1-p)^{j-1}$ per la geometrica traslata: [[02 - Modelli discreti#Formula per la "coda" di una v.a. geometrica (e per la traslata)|formula della coda]].
### Esercizi svolti — formato 2025-2026
#### Binomiale — appello del 6 Febbraio 2026
Si lancia tre volte un dado equo. Calcolare la probabilità che il numero 4 esca almeno due volte.

**Svolgimento**

Tre lanci, ciascuno indipendente dagli altri, con due soli esiti che ci interessano ("esce 4" / "non esce 4"): è lo schema successo-fallimento su un numero **fissato** di prove, quindi binomiale. Sia $X$ il numero di volte che esce il 4: $X\sim\text{Bin}\left(3,\frac{1}{6}\right)$.

"Almeno due volte" su tre lanci significa due o tre:

$$P(X\ge2)=\sum_{k=2}^{3}\binom{3}{k}\left(\frac{1}{6}\right)^k\left(\frac{5}{6}\right)^{3-k}=3\cdot\frac{1}{36}\cdot\frac{5}{6}+\frac{1}{216}=\frac{15+1}{216}=\frac{16}{216}=\frac{2}{27}$$

Qui il complementare non conviene ($P(X\le1)$ sarebbe comunque due addendi): la regola «almeno uno → complementare» vale quando i casi da escludere sono **meno** di quelli da sommare.
#### Geometrica e serie — appello del 20 Febbraio 2026
Si lancia ripetutamente una moneta equa. Calcolare la probabilità che esca testa per la prima volta a un lancio pari **diverso dal secondo** (al quarto, al sesto, all'ottavo, ecc.).

**Svolgimento**

"Per la prima volta" e "numero di lanci necessari" sono le parole che identificano la geometrica traslata. Sia $X$ il numero di lanci fino alla prima testa:

$$P(X=k)=\left(\frac{1}{2}\right)^{k-1}\frac{1}{2}=\left(\frac{1}{2}\right)^{k}$$

L'evento richiesto raccoglie infiniti casi, tutti **disgiunti** tra loro (la prima testa esce a un lancio solo), quindi le probabilità si sommano. I lanci ammessi sono $4,6,8,\dots$, cioè $2k$ con $k\ge2$:

$$P\left(\bigcup_{k\ge2}\{X=2k\}\right)=\sum_{k\ge2}\left(\frac{1}{2}\right)^{2k}=\sum_{k\ge2}\left(\frac{1}{4}\right)^{k}=\frac{(1/4)^2}{1-1/4}=\frac{1}{16}\cdot\frac{4}{3}=\frac{1}{12}$$

> [!question] Dove si sbaglia
> Facendo partire l'indice da $k=1$ si include il secondo lancio, che la traccia esclude, e viene $\frac{1}{3}$. Tutta la difficoltà dell'esercizio sta in quel «diverso dal secondo»: la formula è la stessa, cambia solo $h$.

### Esercizi svolti — varianti dagli appelli precedenti
Le tracce fino al 2024-25 hanno **tre sotto-domande per esercizio** invece di una, quindi coprono più casi. Le tecniche sono le stesse, ma questi casi nel formato nuovo non sono ancora comparsi.
#### Senza reinserimento: ipergeometrica e varianza — appello del 19 Luglio 2025
Un'urna ha 4 palline bianche e 4 nere. Si estraggono 3 palline, una alla volta e **senza reinserimento**. Sia $X$ il numero di bianche estratte.

**D1)** Probabilità che siano tutte dello stesso colore. **D2)** $\text{Var}[X]$. **D3)** Probabilità della sequenza (bianco, nero, bianco).

**Svolgimento**

Senza reinserimento e con due soli tipi di oggetto: $X\sim\text{Ipergeometrica}$ con $N=8$, $K=4$, $n=3$ — la costruzione è in [[02 - Modelli discreti#Caso 2): distribuzione ipergeometrica|caso ipergeometrico]].

**D1)** I due casi (tutte bianche, tutte nere) sono disgiunti e si sommano:

$$P(\{X=0\}\cup\{X=3\})=\frac{\binom{4}{0}\binom{4}{3}}{\binom{8}{3}}+\frac{\binom{4}{3}\binom{4}{0}}{\binom{8}{3}}=\frac{4+4}{56}=\frac{1}{7}$$

Il prof dà anche la via alternativa con le condizionate, che non richiede di ricordare la formula ipergeometrica: $\frac{4}{8}\cdot\frac{3}{7}\cdot\frac{2}{6}+\frac{4}{8}\cdot\frac{3}{7}\cdot\frac{2}{6}=\frac{1}{14}+\frac{1}{14}=\frac{1}{7}$. Entrambe valgono: usa quella che ricordi con più sicurezza.

**D2)** Formula della varianza ipergeometrica — l'unica delle due che *non* si ricostruisce al volo, quindi va saputa:

$$\text{Var}[X]=n\frac{K}{N}\left(1-\frac{K}{N}\right)\frac{N-n}{N-1}=3\cdot\frac{1}{2}\cdot\frac{1}{2}\cdot\frac{5}{7}=\frac{15}{28}$$

Il fattore $\frac{N-n}{N-1}$ è la **correzione per popolazione finita**: è ciò che distingue l'ipergeometrica dalla binomiale, e vale meno di 1 perché senza reinserimento la variabilità è minore.

**D3)** La sequenza è **ordinata**, quindi non si usano i binomiali ma si condiziona passo passo:

$$P(B_1\cap N_2\cap B_3)=\frac{4}{8}\cdot\frac{4}{7}\cdot\frac{3}{6}=\frac{1}{7}$$

#### Con reinserimento: binomiale negativa — appello del 3 Febbraio 2025
Un'urna ha 9 palline bianche e 18 nere. Si estraggono palline una alla volta **con reinserimento**. Sia $X$ il numero di palline estratte fino a quando esce per la **seconda** volta una bianca. Calcolare $E[X]$.

**Svolgimento**

Con reinserimento le prove sono indipendenti, con $p=P(\text{bianca})=\frac{9}{27}=\frac{1}{3}$ costante. La variabile conta **quante prove servono** per arrivare all'$r$-esimo successo con $r=2$: è la binomiale negativa traslata, cioè la geometrica generalizzata a più successi ([[02 - Modelli discreti#Caso $r=1$: recupero della geometrica e della geometrica traslata|con $r=1$ si ricade nella geometrica]]).

$$E[X]=\frac{r}{p}=\frac{2}{1/3}=6$$

Il risultato ha senso a occhio: se in media serve un'estrazione ogni tre per pescare una bianca, per averne due servono in media sei estrazioni. Questo controllo di plausibilità funziona quasi sempre sulle medie.
#### «Almeno uno» si risolve al complementare — appello del 9 Febbraio 2021
Mazzo di 8 carte numerate da 1 a 8, estrazioni **con reinserimento**.

**D1)** In 4 estrazioni, probabilità di estrarre almeno una carta tra $\{1,2,3,4\}$. **D2)** In 11 estrazioni, speranza del numero di carte estratte tra $\{1,2,3,4,5\}$.

**Svolgimento**

**D1)** "Almeno una" calcolato direttamente sono tre addendi ($k=1,2,3,4$); il complementare è un solo conto. L'evento contrario è "nessuna delle 4 estratte sta in $\{1,2,3,4\}$", e a ogni estrazione la probabilità di mancarle è $\frac{4}{8}=\frac{1}{2}$:

$$P(\text{almeno una})=1-\binom{4}{0}\left(\frac{1}{2}\right)^{4}=1-\frac{1}{16}=\frac{15}{16}$$

**D2)** $X\sim\text{Bin}\left(11,\frac{5}{8}\right)$, quindi $E[X]=np=11\cdot\frac{5}{8}=\frac{55}{8}$.

> [!info] Regola pratica
> Ogni volta che compare **«almeno uno»**, scrivere subito $1-P(\text{nessuno})$. Vale anche senza reinserimento, dove $P(\text{nessuno})$ diventa una catena di condizionate.

#### Urna a tre colori: quando serve la multinomiale — appello del 7 Febbraio 2020
Un'urna ha 2 palline bianche, 2 gialle e 2 rosse. Si estraggono 3 palline, una alla volta e **senza reinserimento**.

**D1)** Probabilità che vengano estratte le due gialle. **D2)** Probabilità di estrarre le due gialle e una rossa, in un qualsiasi ordine.

**Svolgimento**

Con più di due tipi di oggetto la formula ipergeometrica a due classi non basta: si sceglie **quante prenderne da ciascun colore**, sui $\binom{6}{3}=20$ modi possibili di estrarre 3 palline su 6.

$$\textbf{D1)}\quad \frac{\binom{2}{2}\binom{4}{1}}{\binom{6}{3}}=\frac{4}{20}=\frac{1}{5}\qquad\qquad \textbf{D2)}\quad \frac{\binom{2}{2}\binom{2}{1}\binom{2}{0}}{\binom{6}{3}}=\frac{2}{20}=\frac{1}{10}$$

In D1 il terzo posto è libero fra le 4 palline non gialle; in D2 è vincolato a essere rossa, e infatti compare anche $\binom{2}{0}$ per le bianche — che sembra superfluo ma tiene la formula leggibile.

Lo stesso esercizio svolto **sia con sia senza reinserimento**, con il confronto tra i due metodi, è in [[02 - Modelli discreti#Esempio: urna con tre colori (con e senza reinserimento)|urna con tre colori]].

> [!info] Convenzione del corso
> Quando la traccia dice «vengono estratte 2 rosse», sottintende sempre **esattamente** 2 e **in un qualsiasi ordine**, salvo indicazione contraria. Se invece elenca una sequenza fra parentesi, l'ordine è fissato.

#### Nessuna distribuzione notevole: conteggio diretto — appello del 21 Febbraio 2020
Si lancia 3 volte un dado equo. Calcolare la probabilità che la somma dei tre numeri sia uguale a 4.

**Svolgimento**

Non tutti gli Es1 hanno una distribuzione dietro. Qui la somma non è binomiale né altro: si elencano le sequenze favorevoli. La somma 4 con tre dadi si ottiene solo con $(2,1,1)$, $(1,2,1)$, $(1,1,2)$, e ogni sequenza ordinata ha probabilità $\frac{1}{6^3}$:

$$P(\text{somma}=4)=\frac{3}{6^3}=\frac{3}{216}=\frac{1}{72}$$

Quando il numero di casi favorevoli è piccolo, elencarli è più veloce e più sicuro che cercare una formula.
#### Condizionamento dentro Es1 — appello del 21 Febbraio 2020, D3
Sempre sui 3 lanci: calcolare la probabilità che esca la sequenza $(2,2,2)$ **sapendo** di aver ottenuto 3 numeri pari.

**Svolgimento**

Anche il primo esercizio può contenere una condizionata — non è materiale esclusivo di [[Es2 - Probabilità condizionata|Es2]]. Si applica la definizione, notando che l'evento $E=\{(2,2,2)\}$ è **contenuto** in $\{X=3\}$ (se escono tre 2, sono usciti tre pari), quindi $E\cap\{X=3\}=E$:

$$P(E|X=3)=\frac{P(E\cap\{X=3\})}{P(X=3)}=\frac{P(E)}{P(X=3)}=\frac{(1/6)^3}{(1/2)^3}=\frac{8}{216}=\frac{1}{27}$$

Il riconoscimento dell'inclusione $E\subset\{X=3\}$ è la mossa che semplifica: è la stessa usata negli esercizi di [[01 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|Cap 2]].
#### Parametro simbolico ed estrazione in blocco — simulazione 2019-2020
Un'urna ha $n$ palline numerate da 1 a $n$. Si estraggono 2 palline **in blocco**.

**D1)** Probabilità che venga estratto il numero $k$. **D2)** Probabilità che il massimo tra i due numeri estratti sia $k$.

**Svolgimento**

"In blocco" significa **sottoinsiemi non ordinati**: gli esiti equiprobabili sono $\binom{n}{2}=\frac{n(n-1)}{2}$, ed è uno spazio uniforme discreto, quindi ogni probabilità è (casi favorevoli)/(casi totali).

**D1)** Fissato $k$, l'altra pallina può essere una qualsiasi delle $n-1$ rimanenti:

$$\frac{\binom{1}{1}\binom{n-1}{1}}{\binom{n}{2}}=\frac{n-1}{n(n-1)/2}=\frac{2}{n}$$

**D2)** Il massimo è $k$ quando $k$ viene estratto **e** l'altra pallina è minore di $k$, cioè una delle $k-1$ sottostanti:

$$P(\max=k)=\frac{k-1}{n(n-1)/2}=\frac{2(k-1)}{n(n-1)}$$

> [!info] Il controllo che fa il prof
> Nella soluzione verifica che $\sum_{k=1}^{n}\frac{2(k-1)}{n(n-1)}=1$, usando $\sum_{k=1}^{n-1}k=\frac{(n-1)n}{2}$.
>
> Quando una domanda chiede una **densità discreta completa**, sommare e controllare che faccia 1 costa dieci secondi e intercetta quasi tutti gli errori di conteggio. È anche il tipo di rigore che si aspetta di vedere sul foglio.

### Trappole ricorrenti
- **Sequenza ordinata vs conteggio**: «estrarre la sequenza (bianco, nero, bianco)» non è «estrarre due bianche e una nera». Nel primo caso l'ordine è fissato e si moltiplicano le condizionate; nel secondo va incluso il numero di ordinamenti possibili.

- **Più di due tipi di oggetto**: non è più binomiale né ipergeometrica a due classi, ma **multinomiale** (con reinserimento) o conteggio con più binomiali (senza). Se però la domanda distingue solo una categoria dalle altre — «quante rosse» — conviene raggruppare in "rosse / non rosse" e tornare al caso a due classi, che è molto più rapido.

- **Media o varianza richieste**: quasi sempre basta la formula della distribuzione riconosciuta. Calcolare la densità completa e poi sommare $\sum_k k\,p_X(k)$ è corretto ma è la strada lunga.

- **Densità completa vs singola probabilità**: se la richiesta è «trovare la densità discreta di $X$», vanno indicati **tutti** i valori del supporto, non solo la formula generica — e la somma deve fare 1.

- **Parametri simbolici** ($n$ palline, $p$ generica): il conto è identico, resta solo in forma letterale. Non è un esercizio più difficile, è lo stesso esercizio senza numeri.

- **Traslata vs non traslata**: vedi il callout nella tabella. È l'errore che costa più punti perché il risultato resta plausibile.
### Collegamenti
- Teoria di base: [[02 - Modelli discreti#Variabili aleatorie discrete|Variabili aleatorie discrete]], [[01 - Introduzione alla probabilità#Cenni di calcolo combinatorio|calcolo combinatorio]], [[01 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni in blocco]].

- Distribuzioni: [[02 - Modelli discreti#Distribuzioni binomiale e ipergeometrica|Distribuzioni binomiale e ipergeometrica]], [[02 - Modelli discreti#Distribuzione geometrica|Distribuzione geometrica]], [[02 - Modelli discreti#Distribuzione binomiale negativa|Distribuzione binomiale negativa]], [[02 - Modelli discreti#Distribuzione multinomiale|Distribuzione multinomiale]], [[02 - Modelli discreti#Distribuzioni uniforme discreta e di Poisson|Distribuzioni uniforme discreta e di Poisson]].

- Slot vicini: [[Es2 - Probabilità condizionata]] quando l'esperimento ha due fasi, [[Es3 - Densità congiunta discreta]] che riusa le stesse distribuzioni su due variabili.
