## Es1 — Probabilità discreta elementare
Primo esercizio dello scritto: riconoscere **quale distribuzione discreta** descrive un esperimento con urne, dadi o monete, e applicarne le formule per calcolare una probabilità, una densità, una media o una varianza. La teoria di riferimento è [[Variabili aleatorie discrete]] e le distribuzioni notevoli di [[Cap 3 - Modelli Discreti]].
### Riconoscere il modello
Prima di scrivere una formula, tre domande in quest'ordine:

1. **Le prove sono indipendenti?** L'esito di un'estrazione cambia le probabilità della successiva?
2. **L'ordine conta?** La sequenza $(B,N,B)$ è diversa da «due bianche e una nera».
3. **Cosa conta la variabile aleatoria?** Il **numero di successi** in $n$ prove fissate, oppure il **numero di prove** necessarie perché accada qualcosa?

L'albero riassume il tutto: la **prima** domanda (reinserimento) sceglie il ramo, la **terza** (cosa conta la variabile) sceglie la foglia.

```text
C'è reinserimento?  (dado / moneta = SEMPRE sì, non si consumano)
├─ SÌ → prove indipendenti, p costante
│   ├─ conto i successi su n prove FISSE ........ Binomiale(n, p)
│   ├─ quante prove fino al 1º successo ......... Geometrica traslata(p)
│   ├─ quante prove fino all'rº successo ........ Bin. negativa traslata(r, p)
│   └─ più di 2 esiti (3 colori, ...) ........... Multinomiale
├─ NO (senza reinserimento) → prove dipendenti
│   ├─ 2 tipi, conto i "buoni" estratti ......... Ipergeometrica(N, K, n)
│   ├─ ordine FISSATO (una sequenza precisa) .... catena di condizionate
│   └─ più di 2 colori .......................... favorevoli/totali con binomiali
└─ nessun modello (somma dei dadi, max, ...) .... conteggio diretto |A|/|Ω|
```

> [!warning] Il bivio del reinserimento decide la distribuzione
> **Con reinserimento** → l'urna non cambia, prove indipendenti, $p$ costante → **binomiale** se conti i successi, **geometrica** o **binomiale negativa** se conti quante prove servono.
>
> **Senza reinserimento** → ogni estrazione modifica l'urna, prove dipendenti → **ipergeometrica**, oppure catena di condizionate $P(A_1)P(A_2|A_1)P(A_3|A_1\cap A_2)$ con la [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]].
>
> **In blocco** (tutte insieme, senza ordine) → sottoinsiemi non ordinati, si conta con $\binom{n}{k}$: [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni in blocco]].
>
> Dadi e monete sono **sempre** con reinserimento: il dado non si consuma.

### Distribuzioni discrete notevoli
Da avere a memoria; costruzione e dimostrazioni nei link sotto la tabella.

| Distribuzione                          | Quando                                                             | Densità $p_X(k)$                                       | Media          | Varianza                                                |
| -------------------------------------- | ------------------------------------------------------------------ | ------------------------------------------------------ | -------------- | ------------------------------------------------------- |
| **Bernoulli**$(p)$                     | una sola prova, successo/insuccesso                                | $p_X(1)=p,\ p_X(0)=1-p$                                | $p$            | $p(1-p)$                                                |
| **Binomiale**$(n,p)$                   | $n$ prove indipendenti, conta i successi                           | $\binom{n}{k}p^k(1-p)^{n-k}$                           | $np$           | $np(1-p)$                                               |
| **Ipergeometrica**$(N,K,n)$            | $n$ estratte senza reinserimento da $N$ oggetti di cui $K$ "buoni" | $\dfrac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}$   | $n\frac{K}{N}$ | $n\frac{K}{N}\left(1-\frac{K}{N}\right)\frac{N-n}{N-1}$ |
| **Geometrica traslata**$(p)$           | numero di prove **fino al primo** successo, $k\ge1$                | $(1-p)^{k-1}p$                                         | $\dfrac{1}{p}$ | $\dfrac{1-p}{p^2}$                                      |
| **Binomiale negativa traslata**$(r,p)$ | numero di prove **fino all'$r$-esimo** successo                    | $\binom{k-1}{r-1}p^r(1-p)^{k-r}$                       | $\dfrac{r}{p}$ | $\dfrac{r(1-p)}{p^2}$                                   |
| **Multinomiale**                       | $n$ prove indipendenti con **più di due** esiti                    | $\dfrac{n!}{k_1!\cdots k_m!}p_1^{k_1}\cdots p_m^{k_m}$ | —              | —                                                       |
| **Poisson**$(\lambda)$                 | conteggi rari                                                      | $\dfrac{\lambda^k}{k!}e^{-\lambda}$                    | $\lambda$      | $\lambda$                                               |

Costruzioni: [[Distribuzioni binomiale e ipergeometrica]], [[Distribuzione geometrica]], [[Distribuzione binomiale negativa]], [[Distribuzione multinomiale]], [[Distribuzioni uniforme discreta e di Poisson]].

> [!warning] Traslata o no: l'errore che costa più punti
> Le versioni **traslate** contano il **numero di prove** e partono da $k=1$ (o $k=r$); le versioni non traslate contano il **numero di insuccessi prima** del successo e partono da $k=0$. La differenza sulla media è tra $\frac{1}{p}$ e $\frac{1-p}{p}$ — esattamente una prova. Macci scrive sempre *"binomiale negativa traslata"*: [[Distribuzione binomiale negativa#Calcolo delle densità discrete di $X$ e $Y$|densità di X e Y]].

### Le serie da riconoscere
Quando l'evento coinvolge **infinite** prove, la risposta è una serie da costruire, non una formula da tabella.
**Serie geometrica** — dimostrata in [[Distribuzione geometrica#Formula della serie geometrica|serie geometrica]]:
$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad (|r|<1)$$
Il punto delicato è **da dove parte l'indice $h$**: si scrive l'evento come unione disgiunta $\bigcup_k\{X=\dots\}$ e solo dopo si somma. Per «servono almeno $j$ prove» c'è già la formula della coda $P(Y\ge j)=(1-p)^{j-1}$: [[Distribuzione geometrica#Formula per la "coda" di una v.a. geometrica (e per la traslata)|formula della coda]].
### Esercizi svolti — formato 2025-2026
#### Binomiale — appello del 6 Febbraio 2026
Si lancia tre volte un dado equo. Calcolare la probabilità che il numero 4 esca almeno due volte.
**Svolgimento**
**Passo 1 — riconoscere il modello.** Tre lanci sono indipendenti (il dado non si consuma), gli esiti che interessano sono due — "esce 4" oppure "non esce 4" — e il numero di prove è **fissato** a 3. Contiamo *quanti successi* su un numero di prove fisso: è una **binomiale**. Sia $X$ il numero di volte che esce il 4, allora $X\sim\text{Bin}\left(3,\frac{1}{6}\right)$.

**Passo 2 — scrivere la densità generale.** Per la binomiale di parametri $n$ (prove) e $p$ (probabilità di successo in una prova),
$$P(X=k)=\binom{n}{k}p^{k}(1-p)^{n-k}.$$
Si legge così: $p^{k}$ sono i $k$ successi, $(1-p)^{n-k}$ sono i restanti $n-k$ insuccessi, e $\binom{n}{k}$ conta **in quanti ordini diversi** quei $k$ successi possono disporsi tra le $n$ prove — perché "due 4 su tre lanci" può accadere come $(4,4,\bar4)$, $(4,\bar4,4)$ o $(\bar4,4,4)$.

**Passo 3 — calcolare.** Qui $n=3$ e $p=\frac{1}{6}$. "Almeno due volte" su tre lanci significa $k=2$ oppure $k=3$, due casi disgiunti che si sommano:
$$P(X\ge2)=\sum_{k=2}^{3}\binom{3}{k}\left(\frac{1}{6}\right)^k\left(\frac{5}{6}\right)^{3-k}=3\cdot\frac{1}{36}\cdot\frac{5}{6}+\frac{1}{216}=\frac{15+1}{216}=\frac{16}{216}=\frac{2}{27}$$
Il complementare non conviene: $P(X\le1)$ sarebbe comunque due addendi. La regola «almeno uno → complementare» vale quando i casi da escludere sono **meno** di quelli da sommare.
#### Geometrica e serie — appello del 20 Febbraio 2026
Si lancia ripetutamente una moneta equa. Calcolare la probabilità che esca testa per la prima volta a un lancio pari **diverso dal secondo** (al quarto, al sesto, all'ottavo, ecc.).
**Svolgimento**
**Passo 1 — riconoscere il modello.** Le parole chiave sono "per la prima volta" e "numero di lanci necessari": non contiamo quanti successi in $n$ prove fissate (sarebbe binomiale), ma *quante prove servono* prima che il successo accada. Le prove possibili sono infinite, quindi il modello è la **geometrica traslata**.

**Passo 2 — scrivere la densità generale.** Per la geometrica traslata di parametro $p$, la probabilità che il primo successo arrivi esattamente alla prova $k$ è
$$P(X=k)=(1-p)^{k-1}\,p\qquad k\ge1.$$
Si legge così: servono $k-1$ **insuccessi** consecutivi — ciascuno con probabilità $1-p$, e sono indipendenti quindi si moltiplicano — seguiti da **un** successo alla $k$-esima prova, di probabilità $p$. L'esponente $k-1$ è esattamente "quante volte ho fallito prima di riuscire".

**Passo 3 — calare sul caso concreto.** Qui il successo è "esce testa" con moneta equa, quindi $p=\frac{1}{2}$ e anche $1-p=\frac{1}{2}$. La densità si semplifica molto:
$$P(X=k)=\left(\frac{1}{2}\right)^{k-1}\frac{1}{2}=\left(\frac{1}{2}\right)^{k}.$$

**Passo 4 — tradurre l'evento in un insieme di indici.** "Prima testa a un lancio pari diverso dal secondo" significa che $X$ può valere $4,6,8,\dots$ — tutti i pari **tranne** il 2. Questi si scrivono come $2k$ con $k\ge2$: l'indice parte da 2 proprio perché $k=1$ darebbe $2k=2$, il lancio escluso. Gli eventi $\{X=4\},\{X=6\},\dots$ sono a due a due **disgiunti** — la prima testa esce a un solo lancio, non a due contemporaneamente — quindi la probabilità dell'unione è la **somma** delle probabilità:
$$P\left(\bigcup_{k\ge2}\{X=2k\}\right)=\sum_{k\ge2}P(X=2k)=\sum_{k\ge2}\left(\frac{1}{2}\right)^{2k}=\sum_{k\ge2}\left(\frac{1}{4}\right)^{k}.$$
Il passaggio $\left(\frac{1}{2}\right)^{2k}=\left(\frac{1}{4}\right)^{k}$ è la mossa che trasforma la densità in una potenza pura $r^{k}$: la ragione diventa $r=\left(\frac{1}{2}\right)^{2}=\frac{1}{4}$, **non** $\frac{1}{2}$. È qui che si sbaglia il denominatore.

**Passo 5 — applicare la serie geometrica.** Ora è un calcolo puramente meccanico. La formula generale è
$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad(|r|<1),$$
cioè "ragione elevata al primo indice, diviso $1-r$". Con $r=\frac{1}{4}$ e primo indice $h=2$:
$$\sum_{k\ge2}\left(\frac{1}{4}\right)^{k}=\frac{(1/4)^{2}}{1-1/4}=\frac{1/16}{3/4}=\frac{1}{16}\cdot\frac{4}{3}=\frac{1}{12}.$$

> [!question] Dove si sbaglia
> Il punto delicato è **da dove parte l'indice** ($h$). Facendo partire la somma da $k=1$ si include $2k=2$, cioè il secondo lancio, che la traccia esclude: verrebbe $\sum_{k\ge1}\left(\frac{1}{4}\right)^{k}=\frac{1/4}{3/4}=\frac{1}{3}$. Tutta la difficoltà dell'esercizio sta in quel «diverso dal secondo»: la densità e la serie sono identiche, cambia **solo** l'indice di partenza $h$.

### Esercizi svolti — varianti dagli appelli precedenti
Le tracce fino al 2024-25 hanno **tre sotto-domande per esercizio**, quindi coprono più casi con le stesse tecniche.
#### Ipergeometrica e varianza — appello del 19 Luglio 2025
Un'urna ha 4 palline bianche e 4 nere. Si estraggono 3 palline, una alla volta e **senza reinserimento**. Sia $X$ il numero di bianche estratte. **D1)** Probabilità che siano tutte dello stesso colore. **D2)** $\text{Var}[X]$. **D3)** Probabilità della sequenza $(B,N,B)$.
**Svolgimento**
**Passo 1 — riconoscere il modello.** L'estrazione è **senza reinserimento**: ogni pallina tolta cambia la composizione dell'urna, quindi le prove *non* sono indipendenti e la binomiale è esclusa. Con due soli tipi di oggetto (bianche/nere) e un numero fisso di estratte, il modello è l'**ipergeometrica**: $X\sim\text{Ipergeometrica}$ con $N=8$ oggetti totali, $K=4$ "buoni" (le bianche), $n=3$ estratti — [[Distribuzioni binomiale e ipergeometrica#Caso 2): distribuzione ipergeometrica|caso ipergeometrico]].

**Passo 2 — densità generale.** La probabilità di estrarre esattamente $k$ bianche è
$$P(X=k)=\frac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}.$$
Al denominatore, $\binom{N}{n}$ sono tutti i modi di scegliere $n$ oggetti su $N$ (spazio uniforme, estrazione in blocco); al numeratore si scelgono le $k$ bianche fra le $K$ disponibili **e** le restanti $n-k$ fra le $N-K$ nere. È un conteggio di casi favorevoli su casi totali.
**D1) Tutte dello stesso colore.** "Tutte bianche" ($X=3$) e "tutte nere" ($X=0$) sono eventi **disgiunti**, quindi le probabilità si sommano; ciascuna si ottiene dalla densità del Passo 2:
$$P(\{X=0\}\cup\{X=3\})=\frac{\binom{4}{0}\binom{4}{3}}{\binom{8}{3}}+\frac{\binom{4}{3}\binom{4}{0}}{\binom{8}{3}}=\frac{4+4}{56}=\frac{1}{7}$$
Via alternativa con le condizionate (non richiede la formula ipergeometrica): $\frac{4}{8}\cdot\frac{3}{7}\cdot\frac{2}{6}+\frac{4}{8}\cdot\frac{3}{7}\cdot\frac{2}{6}=\frac{1}{14}+\frac{1}{14}=\frac{1}{7}$. Usa quella che ricordi con più sicurezza.
**D2) Varianza.** La varianza ipergeometrica è l'unica formula della tabella che *non* si ricostruisce al volo — va tenuta a memoria:
$$\text{Var}[X]=n\frac{K}{N}\left(1-\frac{K}{N}\right)\frac{N-n}{N-1}=3\cdot\frac{1}{2}\cdot\frac{1}{2}\cdot\frac{5}{7}=\frac{15}{28}$$
Il fattore $\frac{N-n}{N-1}$ è la **correzione per popolazione finita**: distingue l'ipergeometrica dalla binomiale e vale meno di 1 perché senza reinserimento la variabilità è minore.
**D3) Sequenza $(B,N,B)$.** Qui l'ordine è **fissato**, quindi non si usano i binomiali ma si moltiplicano le probabilità passo passo con la [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]:
$$P(A_1\cap A_2\cap A_3)=P(A_1)\,P(A_2\mid A_1)\,P(A_3\mid A_1\cap A_2).$$
A ogni estrazione il denominatore cala di 1 (una pallina in meno nell'urna) e il numeratore segue il colore richiesto — bianca (4 su 8), poi nera (4 su 7), poi bianca (3 su 6):
$$P(B_1\cap N_2\cap B_3)=\frac{4}{8}\cdot\frac{4}{7}\cdot\frac{3}{6}=\frac{1}{7}$$
#### Binomiale negativa — appello del 3 Febbraio 2025
Un'urna ha 9 palline bianche e 18 nere. Si estraggono palline una alla volta **con reinserimento**. Sia $X$ il numero di palline estratte fino a quando esce per la **seconda** volta una bianca. Calcolare $E[X]$.
**Svolgimento**
**Passo 1 — riconoscere il modello.** Con reinserimento l'urna torna sempre uguale, quindi le prove sono **indipendenti** e $p=P(\text{bianca})=\frac{9}{27}=\frac{1}{3}$ resta costante. Non contiamo i successi su prove fisse, ma *quante prove servono* per arrivare al **secondo** successo: è la **binomiale negativa traslata** con $r=2$ (il caso $r=1$ è la geometrica: [[Distribuzione binomiale negativa#Caso $r=1$: recupero della geometrica e della geometrica traslata|con r = 1 si ricade nella geometrica]]).

**Passo 2 — media generale.** La media della binomiale negativa traslata è
$$E[X]=\frac{r}{p},$$
e si capisce a intuito: se ogni successo richiede in media $\frac{1}{p}$ prove (è la media della geometrica), per collezionarne $r$ ne servono in media $r$ volte tante. Con $r=2$ e $p=\frac{1}{3}$:
$$E[X]=\frac{r}{p}=\frac{2}{1/3}=6$$
Controllo a occhio: se in media serve un'estrazione ogni tre per una bianca, per averne due ne servono in media sei. Il controllo di plausibilità funziona quasi sempre sulle medie.
#### «Almeno uno» al complementare — appello del 9 Febbraio 2021
Mazzo di 8 carte numerate da 1 a 8, estrazioni **con reinserimento**. **D1)** In 4 estrazioni, probabilità di estrarre almeno una carta tra $\{1,2,3,4\}$. **D2)** In 11 estrazioni, speranza del numero di carte estratte tra $\{1,2,3,4,5\}$.
**Svolgimento**
**D1) Almeno una carta tra $\{1,2,3,4\}$.** Farlo in modo diretto vorrebbe dire sommare i casi "esattamente 1, 2, 3 o 4 carte buone": quattro addendi. Conviene il **complementare**, che è un solo conto. La formula generale è
$$P(\text{almeno uno})=1-P(\text{nessuno})=1-(1-p)^{n},$$
dove $(1-p)^{n}$ è la probabilità di mancare il successo in **tutte** le $n$ prove indipendenti. Qui il successo è "carta in $\{1,2,3,4\}$" con $p=\frac{4}{8}=\frac{1}{2}$, su $n=4$ estrazioni:
$$P(\text{almeno una})=1-\left(\frac{1}{2}\right)^{4}=1-\frac{1}{16}=\frac{15}{16}$$
**D2)** $X\sim\text{Bin}\left(11,\frac{5}{8}\right)$, quindi $E[X]=np=11\cdot\frac{5}{8}=\frac{55}{8}$.

> [!info] Regola pratica
> Ogni volta che compare **«almeno uno»**, scrivere subito $1-P(\text{nessuno})$. Vale anche senza reinserimento, dove $P(\text{nessuno})$ diventa una catena di condizionate.

#### Urna a tre colori: multinomiale — appello del 7 Febbraio 2020
Un'urna ha 2 palline bianche, 2 gialle e 2 rosse. Si estraggono 3 palline, una alla volta e **senza reinserimento**. **D1)** Probabilità di estrarre le due gialle. **D2)** Probabilità di estrarre le due gialle e una rossa, in un qualsiasi ordine.
**Svolgimento**
**Passo 1 — impostare lo spazio.** Ci sono **tre** tipi di oggetto (bianche, gialle, rosse), quindi non basta una binomiale/ipergeometrica a due colori: si conta *quante prenderne da ciascun colore*. L'estrazione è in blocco, spazio uniforme, e i modi di scegliere 3 palline su 6 sono $\binom{6}{3}=20$ — [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazione in blocco]].

**Passo 2 — formula generale.** Ogni probabilità è (casi favorevoli)/(casi totali):
$$P(A)=\frac{\text{favorevoli}}{\binom{6}{3}},$$
e i favorevoli si contano **colore per colore**, un binomiale per ciascuno, poi moltiplicati (come nell'ipergeometrica multivariata): quante bianche fra le bianche, quante gialle fra le gialle, quante rosse fra le rosse.
$$\textbf{D1)}\quad \frac{\binom{2}{2}\binom{4}{1}}{\binom{6}{3}}=\frac{4}{20}=\frac{1}{5}\qquad\qquad \textbf{D2)}\quad \frac{\binom{2}{2}\binom{2}{1}\binom{2}{0}}{\binom{6}{3}}=\frac{2}{20}=\frac{1}{10}$$
In D1 il terzo posto è libero fra le 4 non gialle; in D2 è vincolato a rossa. Lo stesso esercizio **con e senza reinserimento** è in [[Distribuzione multinomiale#Esempio: urna con tre colori (con e senza reinserimento)|urna con tre colori]].

> [!info] Convenzione del corso
> «Vengono estratte 2 rosse» sottintende sempre **esattamente** 2 e **in un qualsiasi ordine**, salvo indicazione contraria. Se la traccia elenca una sequenza fra parentesi, l'ordine è fissato.

#### Conteggio diretto: nessuna distribuzione — appello del 21 Febbraio 2020
Si lancia 3 volte un dado equo. Calcolare la probabilità che la somma dei tre numeri sia uguale a 4.
**Svolgimento**
La somma dei dadi non segue nessuna distribuzione notevole: si torna alla definizione di **spazio uniforme**, $P(A)=\frac{|A|}{|\Omega|}$, con $|\Omega|=6^{3}=216$ sequenze equiprobabili. Basta elencare le favorevoli: la somma 4 esce solo da $(2,1,1)$, $(1,2,1)$, $(1,1,2)$, ciascuna di probabilità $\frac{1}{6^{3}}$:
$$P(\text{somma}=4)=\frac{3}{6^3}=\frac{3}{216}=\frac{1}{72}$$
Quando i casi favorevoli sono pochi, elencarli è più veloce e più sicuro che cercare una formula.
#### Condizionata dentro Es1 — appello del 21 Febbraio 2020, D3
Sempre sui 3 lanci: probabilità che esca la sequenza $(2,2,2)$ **sapendo** di aver ottenuto 3 numeri pari.
**Svolgimento**
Anche il primo esercizio può contenere una condizionata (non è esclusiva di [[Es2 - Probabilità condizionata|Es2]]). Si parte dalla definizione
$$P(E\mid F)=\frac{P(E\cap F)}{P(F)}.$$
La semplificazione chiave: l'evento $E=\{(2,2,2)\}$ è **contenuto** in $F=\{X=3\text{ pari}\}$, quindi $E\cap F=E$ e resta solo $P(E)/P(F)$:
$$P(E|X=3)=\frac{P(E)}{P(X=3)}=\frac{(1/6)^3}{(1/2)^3}=\frac{8}{216}=\frac{1}{27}$$
Il riconoscimento dell'inclusione $E\subset\{X=3\}$ è la mossa che semplifica.
#### Parametro simbolico ed estrazione in blocco — simulazione 2019-2020
Un'urna ha $n$ palline numerate da 1 a $n$. Si estraggono 2 palline **in blocco**. **D1)** Probabilità che venga estratto il numero $k$. **D2)** Probabilità che il massimo tra i due numeri estratti sia $k$.
**Svolgimento**
"In blocco" → sottoinsiemi non ordinati: gli esiti equiprobabili sono $\binom{n}{2}=\frac{n(n-1)}{2}$, spazio uniforme discreto, ogni probabilità è (favorevoli)/(totali).
**D1)** Fissato $k$, l'altra pallina è una qualsiasi delle $n-1$ rimanenti:
$$\frac{\binom{n-1}{1}}{\binom{n}{2}}=\frac{n-1}{n(n-1)/2}=\frac{2}{n}$$
**D2)** Il massimo è $k$ quando $k$ è estratto **e** l'altra è minore di $k$ (una delle $k-1$ sottostanti):
$$P(\max=k)=\frac{k-1}{n(n-1)/2}=\frac{2(k-1)}{n(n-1)}$$

> [!info] Il controllo che fa il prof
> Verifica che $\sum_{k=1}^{n}\frac{2(k-1)}{n(n-1)}=1$ usando $\sum_{k=1}^{n-1}k=\frac{(n-1)n}{2}$. Quando la richiesta è una **densità discreta completa**, sommare e controllare che faccia 1 intercetta quasi tutti gli errori di conteggio.

### Collegamenti
- Teoria di base: [[Variabili aleatorie discrete]], [[Cap 2 - Introduzione alla probabilità#Cenni di calcolo combinatorio|calcolo combinatorio]], [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni in blocco]].
- Distribuzioni: [[Distribuzioni binomiale e ipergeometrica]], [[Distribuzione geometrica]], [[Distribuzione binomiale negativa]], [[Distribuzione multinomiale]], [[Distribuzioni uniforme discreta e di Poisson]].
- Slot vicini: [[Es2 - Probabilità condizionata]] quando l'esperimento ha due fasi; [[Es3 - Densità congiunta discreta]] che riusa le stesse distribuzioni su due variabili.
