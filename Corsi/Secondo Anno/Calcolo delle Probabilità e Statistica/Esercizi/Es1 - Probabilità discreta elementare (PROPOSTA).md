## Es1 — Probabilità discreta elementare

> [!abstract] A che serve questa pagina
> Questo è **sempre il primo esercizio dello scritto**. Non c'è teoria da esporre: tutto il lavoro consiste nel **riconoscere quale modello discreto** descrive l'esperimento (un'urna, dei dadi, delle monete) e applicarne le formule. La pagina non dà per scontato che tu sappia già farlo: prima costruiamo il **metodo di riconoscimento**, poi spieghiamo **una per una** le distribuzioni con l'intuizione dietro la formula, e infine risolviamo **passo-passo tutti gli Es1 realmente usciti** negli appelli 2024-25 e 2025-26. Se leggi solo una cosa, leggi la sezione [§1](#1-il-metodo-le-quattro-domande-che-scelgono-il-modello): è la mappa che decide tutto il resto.

### Com'è fatto l'Es1 all'esame
Il formato è cambiato tra i due anni, e conviene saperlo perché cambia **quanto** ti viene chiesto, non **come** si risolve:

- **Appelli 2025-2026** → Es1 con **una sola domanda**. Corta, ma spesso con una piccola trappola (un «diverso dal secondo», un condizionamento nascosto).
- **Appelli fino al 2024-2025** → Es1 con **tre sotto-domande** `D1) D2) D3)`, di solito sullo stesso esperimento. Coprono più casi (una probabilità, una media/varianza, una condizionata), quindi sono un ottimo allenamento: se sai fare gli Es1 del 24-25, gli Es1 del 25-26 sono un suo sottoinsieme.

Le tecniche sono **identiche** nei due anni. Qui sotto usiamo tracce di entrambi.

---

### 1. Il metodo: le quattro domande che scelgono il modello
Davanti a una traccia di Es1, **prima di scrivere qualsiasi formula**, rispondi a queste quattro domande in ordine. Ognuna elimina delle possibilità: alla fine resta un solo modello.

> [!tip] Domanda 1 — Le prove sono indipendenti? (con o senza reinserimento)
> È il bivio che decide tutto. Chiediti: *quello che succede a un'estrazione cambia le probabilità della successiva?*
>
> - **Con reinserimento** (rimetto la pallina) oppure **dadi/monete** (non si consumano) → la composizione non cambia mai, le prove sono **indipendenti** e hanno tutte la **stessa** probabilità di successo $p$.
> - **Senza reinserimento** → ogni estrazione modifica l'urna, le prove sono **dipendenti**.
>
> Il lancio ripetuto di dadi e monete è **sempre** con reinserimento: il dado non si consuma, ogni lancio riparte da zero.

> [!tip] Domanda 2 — Cosa conta la variabile aleatoria?
> Due famiglie completamente diverse:
>
> - conto il **numero di successi** in un numero di prove **fissato** $n$ → distribuzione del gruppo **binomiale / ipergeometrica**;
> - conto **quante prove servono** perché accada qualcosa (il primo successo, l'$r$-esimo) → gruppo **geometrica / binomiale negativa**.
>
> «Quante volte esce 4 in 3 lanci» e «quanti lanci servono per il primo 4» sono due domande diverse con due distribuzioni diverse.

> [!tip] Domanda 3 — L'ordine conta?
> «Estrarre la **sequenza** (bianco, nero, bianco)» è una cosa; «estrarre **due bianche e una nera**» (in qualunque ordine) è un'altra.
>
> - ordine **fissato** → si moltiplicano le probabilità passo-passo (indipendenza o [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]), niente coefficienti binomiali;
> - ordine **libero** → bisogna includere **quanti** ordinamenti sono possibili ($\binom{n}{k}$ o i binomiali dell'ipergeometrica).

> [!tip] Domanda 4 — Quanti esiti distinti mi interessano?
> - **due** (successo / insuccesso, bianco / non-bianco) → binomiale o ipergeometrica a due classi;
> - **più di due** che voglio distinguere tutti (bianco / rosso / nero) → **multinomiale** (con reinserimento) o conteggio con più binomiali (senza).
>
> Attenzione: se la domanda distingue **solo una categoria dalle altre** («quante rosse»), conviene raggruppare in «rosse / non-rosse» e tornare al caso a **due** classi, molto più rapido.

> [!info] Notazione: il coefficiente binomiale
> $\binom nk=\dfrac{n!}{k!\,(n-k)!}$ è il **numero di modi di scegliere $k$ elementi tra $n$ senza contare l'ordine**. Compare in quasi tutte le formule qui sotto; per i richiami di combinatoria vedi [[Cap 2 - Introduzione alla probabilità#Cenni di calcolo combinatorio|calcolo combinatorio]].

> [!warning] La quinta possibilità: nessuna distribuzione notevole
> Non tutti gli Es1 hanno un modello dietro. Quando la domanda riguarda una **somma di dadi**, una **differenza**, o un evento «strano», spesso la strada giusta è la più elementare: elencare lo **spazio campionario** $\Omega$ (fatto di esiti equiprobabili) e contare i casi favorevoli. Su uno spazio uniforme, ogni probabilità è
> $$P(A)=\frac{\#A}{\#\Omega}\qquad\text{(casi favorevoli su casi totali).}$$
> Lo vediamo negli esercizi [G](#g--nessuna-distribuzione-conteggio-diretto-su-spazio-uniforme).

#### Lo schema in una riga
```
indipendenti? ── sì ─┬─ conto successi (n fisso) ──────── BINOMIALE
   (reinserim.)      ├─ conto prove al 1° successo ────── GEOMETRICA traslata
                     ├─ conto prove all'r-esimo successo  BINOMIALE NEGATIVA traslata
                     └─ >2 esiti da distinguere ───────── MULTINOMIALE
        ── no ──────┬─ conto successi (n fisso) ───────── IPERGEOMETRICA
   (senza reins.)   └─ sequenza ordinata ──────────────── catena di condizionate
        ── nessun modello ──────────────────────────────── conteggio su Ω uniforme
```

---

### 2. Le distribuzioni, spiegate (non solo la formula)
Qui non troverai solo una tabella: prima capiamo **da dove nasce** ogni formula, così non devi impararla a memoria ma sai **ricostruirla**. Le costruzioni complete stanno negli appunti di [[Cap 3 - Modelli Discreti]]; qui teniamo l'intuizione utile all'esame.

#### Binomiale $(n,p)$ — «quanti successi in $n$ prove»
$n$ prove **indipendenti e identiche**, ognuna con probabilità $p$ di «successo». $X$ conta i successi.
$$p_X(k)=\binom{n}{k}p^k(1-p)^{n-k},\qquad k=0,1,\dots,n.$$
**Perché è fatta così.** Una **singola** sequenza con $k$ successi e $n-k$ insuccessi ha probabilità $p^k(1-p)^{n-k}$ (moltiplico, perché indipendenti). Ma i $k$ successi possono cadere in posizioni diverse: i modi sono $\binom{n}{k}$. Moltiplico le due cose. Il binomiale è **soltanto** il conteggio degli ordinamenti.
$$\mathbb{E}[X]=np,\qquad \text{Var}[X]=np(1-p).$$
La media si legge da sola: $n$ prove, ciascuna dà in media $p$ successi.

#### Ipergeometrica $(N,K,n)$ — «quanti buoni estraggo senza reinserimento»
$N$ oggetti di cui $K$ «buoni»; ne estraggo $n$ **senza reinserimento**. $X$ conta i buoni estratti.
$$p_X(k)=\frac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}.$$
**Perché è fatta così.** È puro *casi favorevoli / casi totali* su estrazioni **in blocco**: al denominatore i $\binom{N}{n}$ modi di scegliere $n$ oggetti su $N$; al numeratore scelgo $k$ buoni tra i $K$ **e** $n-k$ non-buoni tra gli $N-K$.
$$\mathbb{E}[X]=n\frac{K}{N},\qquad \text{Var}[X]=n\frac{K}{N}\Big(1-\frac{K}{N}\Big)\cdot\underbrace{\frac{N-n}{N-1}}_{\text{correzione}}.$$
La media è **la stessa** della binomiale. La varianza no: c'è il fattore $\frac{N-n}{N-1}<1$, la **correzione per popolazione finita**. È ciò che distingue l'ipergeometrica dalla binomiale: senza reinserimento la variabilità è **minore** (le estrazioni «si compensano»). È l'unica formula del gruppo che *non* si ricostruisce al volo — vale la pena saperla a memoria.

#### Geometrica traslata $(p)$ — «quante prove fino al primo successo»
Prove indipendenti con probabilità $p$; $X$ = numero di prove **fino al primo successo compreso**, $k\ge 1$.
$$p_X(k)=(1-p)^{k-1}p,\qquad \mathbb{E}[X]=\frac{1}{p},\qquad \text{Var}[X]=\frac{1-p}{p^2}.$$
**Perché è fatta così.** Per avere il primo successo esattamente alla prova $k$ servono $k-1$ insuccessi di fila $(1-p)^{k-1}$ e poi un successo $p$. La media $\frac1p$ è intuitiva: se il successo ha probabilità $p$, in media serve **una prova ogni $p$**, cioè $\frac1p$ prove.

#### Binomiale negativa traslata $(r,p)$ — «quante prove fino all'$r$-esimo successo»
Generalizza la geometrica: $X$ = numero di prove fino all'$r$-esimo successo.
$$\mathbb{E}[X]=\frac{r}{p}.$$
Con $r=1$ si ricade nella geometrica. La media $\frac rp$ è la geometrica $\times r$: per $r$ successi serve $r$ volte il tempo di uno.

#### Multinomiale — «più di due esiti, con reinserimento»
$n$ prove indipendenti con $m$ esiti possibili di probabilità $p_1,\dots,p_m$; conto quanti $k_1,\dots,k_m$ di ciascuno:
$$P=\frac{n!}{k_1!\cdots k_m!}\,p_1^{k_1}\cdots p_m^{k_m}.$$

#### Poisson $(\lambda)$ e uniforme discreta — comprimari
Compaiono più spesso in Es3 che in Es1. Poisson: $p_X(k)=\frac{\lambda^k}{k!}e^{-\lambda}$, media e varianza entrambe $\lambda$. Uniforme discreta: tutti gli esiti equiprobabili (è il modello del conteggio diretto su $\Omega$).

> [!warning] La trappola più costosa: traslata vs non traslata
> Le versioni **traslate** contano il **numero di prove** e partono da $k=1$ (o $k=r$). Esistono anche versioni **non traslate** che contano il **numero di insuccessi prima** del successo e partono da $k=0$. La differenza sulla media è tra $\frac1p$ e $\frac{1-p}{p}$: esattamente **una prova**, quella riuscita. È l'errore che costa più punti perché il risultato resta plausibile. Il prof Macci usa **sempre** le traslate e le nomina esplicitamente («binomiale negativa traslata»): [[Distribuzione binomiale negativa]].

#### Cheat-sheet finale
Una volta capite sopra, tienile compatte qui:

| Distribuzione | Quando | Densità | Media | Varianza |
|---|---|---|---|---|
| **Binomiale**$(n,p)$ | $n$ prove indip., conta i successi | $\binom{n}{k}p^k(1-p)^{n-k}$ | $np$ | $np(1-p)$ |
| **Ipergeometrica**$(N,K,n)$ | $n$ estratte senza reins. da $N$ ($K$ buoni) | $\dfrac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}$ | $n\frac{K}{N}$ | $n\frac{K}{N}\!\left(1-\frac{K}{N}\right)\!\frac{N-n}{N-1}$ |
| **Geometrica traslata**$(p)$ | prove fino al **1°** successo, $k\ge1$ | $(1-p)^{k-1}p$ | $\dfrac1p$ | $\dfrac{1-p}{p^2}$ |
| **Bin. negativa traslata**$(r,p)$ | prove fino all'**$r$-esimo** successo | $\binom{k-1}{r-1}p^r(1-p)^{k-r}$ | $\dfrac rp$ | $\dfrac{r(1-p)}{p^2}$ |
| **Multinomiale** | $n$ prove, **>2** esiti | $\dfrac{n!}{k_1!\cdots k_m!}p_1^{k_1}\cdots p_m^{k_m}$ | — | — |
| **Poisson**$(\lambda)$ | conteggi rari | $\dfrac{\lambda^k}{k!}e^{-\lambda}$ | $\lambda$ | $\lambda$ |

Costruzioni e dimostrazioni: [[Distribuzioni binomiale e ipergeometrica]], [[Distribuzione geometrica]], [[Distribuzione binomiale negativa]], [[Distribuzione multinomiale]], [[Distribuzioni uniforme discreta e di Poisson]].

---

### 3. Le mosse ricorrenti
Poche tecniche tornano in quasi tutti gli Es1. Impararle qui, isolate, ti evita di re-inventarle sotto esame.

**«Almeno uno» → passa al complementare.** «Almeno un successo» calcolato direttamente sono tanti addendi; il contrario «nessun successo» è **uno solo**. Scrivi subito
$$P(\text{almeno uno})=1-P(\text{nessuno}).$$
Conviene quando i casi da escludere sono **meno** di quelli da sommare. (Se però «almeno due su tre» è comunque due addendi come il diretto, il complementare non aiuta: valutalo, non applicarlo a occhi chiusi.)

**Sequenza ordinata → catena di probabilità.** Se l'ordine è fissato, moltiplica prova per prova: con reinserimento è $P(B_1)P(N_2)P(B_3)$ (indipendenza); senza reinserimento è $P(B_1)\,P(N_2|B_1)\,P(B_3|B_1\cap N_2)$, aggiornando l'urna a ogni passo.

**Condizionata dentro l'Es1 → definizione + inclusione.** Anche il primo esercizio può contenere un $P(A|B)$. Applica la definizione $P(A|B)=\frac{P(A\cap B)}{P(B)}$. La mossa che semplifica quasi sempre è riconoscere un'**inclusione**: se l'evento $A$ è **contenuto** in $B$ (per esempio $\{(2,2,2)\}\subset\{\text{tre pari}\}$), allora $A\cap B=A$ e il numeratore diventa $P(A)$.

**Condizionata su spazio uniforme → conta e basta.** Se lo spazio è uniforme, $P(A|B)=\dfrac{\#(A\cap B)}{\#B}$: non servono le probabilità, solo i conteggi.

**Serie geometrica → costruisci l'evento come unione disgiunta.** Quando l'evento vive su **infinite** prove («la prima testa esce a un lancio pari»), non c'è formula da tabella: scrivi l'evento come unione **disgiunta** $\bigcup_k\{X=\dots\}$, somma le probabilità e usa
$$\sum_{k\ge h}r^k=\frac{r^h}{1-r}\qquad(|r|<1).$$
Il punto delicato **non è la formula**, è **da dove parte l'indice $h$**. Leggi bene la richiesta prima di fissare $h$.

**Densità discreta completa → elenca tutto il supporto e verifica.** Se la domanda è «trovare la densità discreta di $X$», devi dare **tutti** i valori del supporto (non la formula generica), e la somma **deve fare 1**. Sommare e controllare costa dieci secondi e intercetta quasi tutti gli errori di conteggio: è anche il rigore che il prof si aspetta di vedere sul foglio.

---

### 4. Esercizi svolti passo-passo — tracce reali d'esame
Ogni esercizio è **realmente uscito**: indico appello e data. Per ciascuno seguiamo sempre lo stesso rituale: **(1) riconoscimento** — quali parole della traccia scelgono il modello; **(2) svolgimento** con i passaggi spiegati; **(3) controllo** di plausibilità.

#### A — Binomiale: contare i successi
##### A.1 «Almeno due» su tre lanci — *appello 6 Febbraio 2026 (25-26)*
> Si lancia tre volte un dado equo. Calcolare la probabilità che il numero 4 esca almeno due volte.

**Riconoscimento.** Tre lanci → **indipendenti**, numero di prove **fissato** ($n=3$), due soli esiti che ci interessano («esce 4» / «non esce 4»). Domanda 2 → conto i successi → **binomiale**. Sia $X$ = numero di volte che esce il 4: $X\sim\text{Bin}\!\left(3,\frac16\right)$.

**Svolgimento.** «Almeno due su tre» significa due **oppure** tre — due addendi. Qui il complementare *non* conviene (anche $P(X\le1)$ sarebbe due addendi), quindi calcolo diretto:
$$P(X\ge2)=\sum_{k=2}^{3}\binom{3}{k}\Big(\tfrac16\Big)^k\Big(\tfrac56\Big)^{3-k}=\underbrace{3\cdot\tfrac{1}{36}\cdot\tfrac56}_{k=2}+\underbrace{\tfrac{1}{216}}_{k=3}=\frac{15+1}{216}=\frac{16}{216}=\frac{2}{27}.$$

**Controllo.** $\frac{2}{27}\approx0{,}074$: piccolo, coerente col fatto che il 4 è raro ($\frac16$) e chiederne almeno due su tre è chiedere molto.

##### A.2 Media con $n$ generico, poi probabilità con $n$ fissato — *appello 8 Settembre 2025 (24-25)*
> Si lancia $n$ volte un dado equo ($n\ge1$).
> **D1)** Calcolare $\mathbb{E}[X]$ con $X$ = numero di volte che esce un numero pari (con $n$ generico).
> **D2)** Sia $n=5$. Calcolare la probabilità di ottenere 2 volte un numero pari.

**Riconoscimento.** «Pari» ha probabilità $\frac{3}{6}=\frac12$; lanci indipendenti, $n$ fissato → $X\sim\text{Bin}\!\left(n,\frac12\right)$. Nota che tenere $n$ **simbolico** non cambia niente: è lo stesso esercizio senza numeri.

**Svolgimento.**
$$\textbf{D1)}\quad \mathbb{E}[X]=np=\frac n2.$$
$$\textbf{D2)}\quad n=5:\ P(X=2)=\binom{5}{2}\Big(\tfrac12\Big)^2\Big(\tfrac12\Big)^3=\binom{5}{2}\Big(\tfrac12\Big)^5=\frac{10}{32}=\frac{5}{16}.$$
(Con $p=\frac12$ i due fattori si fondono in $\left(\frac12\right)^5$: succede solo quando successo e insuccesso sono equiprobabili.)

##### A.3 «Al massimo un successo» — *appello 20 Giugno 2025 (24-25), D1*
> Si lanciano 3 dadi equi. Per ogni lancio è «successo» l'uscita di un numero $\le 2$. Calcolare la probabilità di avere al massimo un successo.

**Riconoscimento.** $p=\frac{2}{6}=\frac13$, $X\sim\text{Bin}\!\left(3,\frac13\right)$. «Al massimo uno» $=\{X\le1\}=\{X=0\}\cup\{X=1\}$.
$$P(X\le1)=\binom30\Big(\tfrac13\Big)^0\Big(\tfrac23\Big)^3+\binom31\Big(\tfrac13\Big)^1\Big(\tfrac23\Big)^2=\frac{8}{27}+\frac{12}{27}=\frac{20}{27}.$$

#### B — «Verificare che…»: la richiesta con la risposta già scritta
##### B.1 Dimostrare una formula in $n$ — *appello 22 Settembre 2025 (24-25), D1*
> Si lancia il dado $n$ volte. Verificare che la probabilità di ottenere **al massimo una volta** un numero pari è $\dfrac{1+n}{2^n}$.

**Come si affronta.** Quando la traccia ti **dà** il risultato, l'esercizio è mostrare i passaggi che ci arrivano — niente scorciatoie a occhio. Pari ha $p=\frac12$, $X\sim\text{Bin}\!\left(n,\frac12\right)$:
$$P(X\le1)=\binom n0\Big(\tfrac12\Big)^n+\binom n1\Big(\tfrac12\Big)^n=\Big(\tfrac12\Big)^n+n\Big(\tfrac12\Big)^n=\frac{1+n}{2^n}.\qquad\checkmark$$
Il trucco è raccogliere $\left(\frac12\right)^n$: con $p=\frac12$ **ogni** sequenza ha la stessa probabilità $\left(\frac12\right)^n$, e la formula conta soltanto quante sequenze hanno 0 o 1 pari, cioè $1+n$.

#### C — Geometrica e serie geometriche
##### C.1 Prima testa a un lancio pari «diverso dal secondo» — *appello 20 Febbraio 2026 (25-26)*
> Si lancia ripetutamente una moneta equa. Calcolare la probabilità che esca testa **per la prima volta** a un lancio pari **diverso dal secondo** (al quarto, al sesto, all'ottavo, ecc.).

**Riconoscimento.** «Per la prima volta» + «numero di lanci necessari» → **geometrica traslata**. Sia $X$ = numero di lanci fino alla prima testa: $P(X=k)=\left(\frac12\right)^{k-1}\frac12=\left(\frac12\right)^{k}$.

**Svolgimento.** L'evento raccoglie infiniti casi **disgiunti** (la prima testa esce a un lancio solo): si sommano. I lanci ammessi sono $4,6,8,\dots$, cioè $2k$ con $k\ge 2$ (il $k=1$ darebbe il secondo lancio, **escluso**):
$$P\!\left(\bigcup_{k\ge2}\{X=2k\}\right)=\sum_{k\ge2}\Big(\tfrac12\Big)^{2k}=\sum_{k\ge2}\Big(\tfrac14\Big)^{k}=\frac{(1/4)^2}{1-1/4}=\frac{1}{16}\cdot\frac43=\frac{1}{12}.$$

> [!question] Dove si sbaglia (e quanto costa)
> Far partire l'indice da $k=1$ include il secondo lancio e dà $\frac13$ invece di $\frac{1}{12}$. **Tutta** la difficoltà dell'esercizio sta in quel «diverso dal secondo»: la formula è la stessa, cambia solo $h$. È l'esempio perfetto del perché la serie geometrica va **costruita** leggendo la traccia, non applicata a memoria.

##### C.2 La stessa struttura, con un dado — *appello 22 Settembre 2025 (24-25), D2*
> Si lancia ripetutamente un dado equo. Calcolare la probabilità di ottenere per la prima volta uno dei numeri di $\{1,2,3\}$ a un lancio pari dal quarto in poi.

Identica a C.1 con $p=P(\{1,2,3\})=\frac36=\frac12$. Sia $Y$ = lanci fino al primo esito in $\{1,2,3\}$:
$$P\!\left(\bigcup_{h\ge2}\{Y=2h\}\right)=\sum_{h\ge2}\Big(\tfrac12\Big)^{2h}=\sum_{h\ge2}\Big(\tfrac14\Big)^h=\frac{1}{12}.$$
Riconoscere che è «la stessa di prima con un vestito diverso» è metà del lavoro all'esame.

#### D — Condizionamenti dentro l'Es1
##### D.1 Geometrica + condizionata + inclusione — *appello 19 Giugno 2026 (25-26)*
> Si lancia ripetutamente un dado equo. $X$ = numero di lanci fino al primo 6. Per $i,j\in\{1,\dots,5\}$, sia $E_{ij}$ = «esce $i$ al primo lancio e $j$ al secondo». Calcolare $P(E_{ij}\mid X=3)$.

**Riconoscimento.** $\{X=3\}$ = «primi due lanci non-6, terzo lancio 6». L'evento $E_{ij}$ (con $i,j\ne6$) fissa i primi due lanci; se poi il terzo è 6, allora $E_{ij}\cap\{X=3\}$ è proprio «$(i,j,6)$». Applico la definizione:
$$P(E_{ij}\mid X=3)=\frac{P(E_{ij}\cap\{X=3\})}{P(X=3)}=\frac{\left(\frac16\right)\left(\frac16\right)\left(\frac16\right)}{\left(\frac56\right)^{2}\cdot\frac16}=\frac{1/36}{25/36}=\frac{1}{25}.$$

**Controllo (l'interpretazione che piace al prof).** Dato $X=3$, i primi due lanci sono uniformi sui **5** valori non-6 ciascuno: $5\times5=25$ coppie equiprobabili, e $E_{ij}$ ne è una. Ecco perché $\frac{1}{25}$, senza fare conti.

##### D.2 Condizionata con evento complementare — *appello 22 Settembre 2025 (24-25), D3*
> Si lancia 3 volte il dado. Calcolare la probabilità di ottenere **almeno un** numero pari sapendo di **non** aver ottenuto tre numeri pari.

**Svolgimento.** $Z\sim\text{Bin}\!\left(3,\frac12\right)$ conta i pari. «Almeno uno» $=\{Z\ge1\}$, «non tre pari» $=\{Z\ne3\}$. L'intersezione è $\{1\le Z\le 2\}$:
$$P(Z\ge1\mid Z\ne3)=\frac{P(Z=1)+P(Z=2)}{P(Z=0)+P(Z=1)+P(Z=2)}=\frac{\binom31+\binom32}{\binom30+\binom31+\binom32}=\frac{3+3}{1+3+3}=\frac{6}{7}.$$
(Con $p=\frac12$ i fattori $\left(\frac12\right)^3$ si semplificano tra numeratore e denominatore: restano solo i coefficienti binomiali, cioè i **conteggi**.)

##### D.3 Condizionata come rapporto di sequenze ordinate — *appello 20 Giugno 2025 (24-25), D3*
> Si lanciano 3 dadi. Calcolare la probabilità che **non esca 6** nei primi due lanci sapendo che esce **per la prima volta un dispari** al terzo lancio.

$F=$ «primi due pari, terzo dispari»; $E=$ «nessun 6 nei primi due». $E\cap F=$ «primi due in $\{2,4\}$, terzo dispari». Su lanci indipendenti moltiplico le probabilità di ciascuna posizione:
$$P(E\mid F)=\frac{P(E\cap F)}{P(F)}=\frac{\left(\frac26\right)\left(\frac26\right)\left(\frac36\right)}{\left(\frac36\right)\left(\frac36\right)\left(\frac36\right)}=\frac{2\cdot2}{3\cdot3}=\frac49.$$
Il prof lo rilegge come rapporto di conteggi: coppie $\{2,4\}^2$ (sono 4) sulle coppie di pari $\{2,4,6\}^2$ (sono 9). Stesso $\frac49$.

#### E — Ipergeometrica: estrazioni senza reinserimento
##### E.1 Stesso colore, varianza, sequenza — *appello 25 Luglio 2025 (24-25)* — soluzione ufficiale
> Un'urna ha 4 palline bianche e 4 nere. Si estraggono 3 palline, una alla volta e **senza reinserimento**.
> **D1)** Probabilità che siano tutte dello stesso colore. **D2)** Varianza del numero $X$ di bianche estratte. **D3)** Probabilità della sequenza (bianco, nero, bianco).

**Riconoscimento.** Senza reinserimento + due tipi di oggetto → $X\sim\text{Ipergeometrica}$ con $N=8$, $K=4$, $n=3$.

**D1)** «Tutte dello stesso colore» $=\{X=0\}\cup\{X=3\}$, casi disgiunti:
$$P=\frac{\binom40\binom43}{\binom83}+\frac{\binom43\binom40}{\binom83}=\frac{4+4}{56}=\frac17.$$
> [!note] Via alternativa senza ricordare l'ipergeometrica
> Con la catena di condizionate: $P(\text{3 bianche})+P(\text{3 nere})=\frac48\frac37\frac26+\frac48\frac37\frac26=\frac{1}{14}+\frac{1}{14}=\frac17$. Se sotto esame non ricordi la formula ipergeometrica, questa strada ci arriva comunque.

**D2)** La varianza ipergeometrica è l'unica formula da sapere a memoria (vedi §2):
$$\text{Var}[X]=n\frac KN\Big(1-\frac KN\Big)\frac{N-n}{N-1}=3\cdot\frac12\cdot\frac12\cdot\frac{5}{7}=\frac{15}{28}.$$
Il fattore $\frac{5}{7}=\frac{N-n}{N-1}$ è la correzione per popolazione finita: senza reinserimento c'è meno variabilità.

**D3)** La sequenza è **ordinata** → niente binomiali, si condiziona passo-passo aggiornando l'urna:
$$P(B_1\cap N_2\cap B_3)=\frac48\cdot\frac47\cdot\frac36=\frac17.$$

##### E.2 Solo una categoria conta → ipergeometrica a due classi — *Simulazione 1 (24-25), D2*
> Urna con 3 bianche, 3 rosse, 2 nere. Si estraggono 2 palline senza reinserimento. Probabilità di estrarre **due rosse**.

Ci sono tre colori, ma la domanda distingue solo «rossa / non-rossa»: raggruppo e torno a due classi ($K=3$ rosse su $N=8$):
$$P=\frac{\binom32\binom50}{\binom82}=\frac{3}{28}.$$

#### F — Con vs senza reinserimento sullo stesso problema + binomiale negativa
##### F.1 Tre domande, tre tecniche — *appello 10 Febbraio 2025 (24-25)*
> Un'urna ha 9 palline bianche e 18 nere (27 in tutto).
> **D1)** Estraggo 2 palline **senza** reinserimento: probabilità che siano dello stesso colore.
> **D2)** Estraggo 3 palline **con** reinserimento: probabilità della sequenza (bianco, nero, bianco).
> **D3)** Estraggo con reinserimento finché esce la **seconda** bianca; $X$ = numero di estrazioni. Calcolare $\mathbb{E}[X]$.

Questo esercizio è una piccola antologia: le tre domande usano tre modelli diversi sullo **stesso** esperimento. Riconoscerli è l'obiettivo.

**D1) Senza reinserimento → condizionate.** $P(B_1B_2)+P(N_1N_2)$, aggiornando l'urna:
$$\frac{9}{27}\cdot\frac{8}{26}+\frac{18}{27}\cdot\frac{17}{26}=\frac13\cdot\frac{8}{26}+\frac23\cdot\frac{17}{26}=\frac{8+34}{78}=\frac{42}{78}=\frac{7}{13}.$$
(In blocco darebbe lo stesso: $\frac{\binom92+\binom{18}2}{\binom{27}2}=\frac{36+153}{351}=\frac{7}{13}$.)

**D2) Con reinserimento → indipendenza.** L'urna non cambia mai, $P(\text{bianca})=\frac{9}{27}=\frac13$ costante:
$$P(B_1\cap N_2\cap B_3)=\frac13\cdot\frac23\cdot\frac13=\frac{2}{27}.$$

**D3) «Fino alla seconda bianca» → binomiale negativa traslata.** Con reinserimento le prove sono indipendenti, $p=\frac13$, e conto le prove fino al **secondo** successo ($r=2$):
$$\mathbb{E}[X]=\frac rp=\frac{2}{1/3}=6.$$
**Controllo.** In media serve un'estrazione ogni tre per una bianca; per averne due, sei estrazioni. Torna.

#### G — Nessuna distribuzione: conteggio diretto su spazio uniforme
##### G.1 Evento, media/varianza, condizionata su $\Omega$ — *Simulazione 2 (24-25)*
> Si lancia due volte un dado equo. $\Omega=\{1,\dots,6\}^2$, 36 coppie equiprobabili.
> **D1)** Probabilità che escano un numero $<3$ e uno $>4$, in qualsiasi ordine.
> **D2)** $X$ = quante volte esce un numero $>2$. Media e varianza.
> **D3)** Probabilità che i due numeri siano uguali sapendo che la somma è 8.

**D1)** Elenco le coppie favorevoli ($\{1,2\}$ accoppiato con $\{5,6\}$, nei due ordini):
$$E=\{(1,5),(1,6),(2,5),(2,6),(5,1),(5,2),(6,1),(6,2)\},\quad \#E=8\ \Rightarrow\ P(E)=\frac{8}{36}=\frac29.$$

**D2)** Qui invece **c'è** un modello: $>2$ significa $\{3,4,5,6\}$, $p=\frac46=\frac23$, $X\sim\text{Bin}\!\left(2,\frac23\right)$:
$$\mathbb{E}[X]=np=\frac43,\qquad \text{Var}[X]=np(1-p)=2\cdot\frac23\cdot\frac13=\frac49.$$
(Lezione: nello **stesso** Es1 una domanda è conteggio bruto e un'altra è binomiale. Il metodo di §1 va applicato a **ogni** sotto-domanda separatamente.)

**D3)** $A=$ «due uguali» (le 6 doppiette), $B=$ «somma 8» $=\{(2,6),(3,5),(4,4),(5,3),(6,2)\}$. Spazio uniforme → conto e basta:
$$A\cap B=\{(4,4)\}\ \Rightarrow\ P(A\mid B)=\frac{\#(A\cap B)}{\#B}=\frac{1}{5}.$$

#### H — Densità discreta completa + media + condizionata
##### H.1 $X=\max-\min$ su urna numerata — *appello 24 Febbraio 2025 (24-25)* — soluzione ufficiale
> Un'urna ha 4 palline numerate da 1 a 4. Si estraggono 2 palline **in blocco**; $X$ = differenza tra il massimo e il minimo dei due numeri.
> **D1)** Densità discreta di $X$. **D2)** $\mathbb{E}[X]$. **D3)** Probabilità di aver estratto la pallina 1 sapendo $\{X=1\}$.

**Riconoscimento.** «In blocco» → sottoinsiemi non ordinati, spazio **uniforme** con $\binom42=6$ esiti, ciascuno di probabilità $\frac16$:
$$\Omega=\{\{1,2\},\{1,3\},\{1,4\},\{2,3\},\{2,4\},\{3,4\}\}.$$

**D1)** Per ogni valore di $X$ elenco i sottoinsiemi che lo realizzano:
$$p_X(1)=P(\{\{1,2\},\{2,3\},\{3,4\}\})=\frac36,\quad p_X(2)=P(\{\{1,3\},\{2,4\}\})=\frac26,\quad p_X(3)=P(\{\{1,4\}\})=\frac16.$$
> [!check] Verifica obbligatoria: $\frac36+\frac26+\frac16=1$. La densità è completa. Dieci secondi che valgono punti.

**D2)** $\displaystyle \mathbb{E}[X]=\sum_{k=1}^{3}k\,p_X(k)=\frac{1\cdot3+2\cdot2+3\cdot1}{6}=\frac{10}{6}=\frac53.$

**D3)** $E=$ «estratta la pallina 1». L'unico sottoinsieme con $X=1$ che contiene l'1 è $\{1,2\}$, quindi $E\cap\{X=1\}=\{\{1,2\}\}$:
$$P(E\mid X=1)=\frac{P(\{\{1,2\}\})}{p_X(1)}=\frac{1/6}{3/6}=\frac13.$$

---

### 5. Trappole ricorrenti
- **Sequenza ordinata vs conteggio.** «(bianco, nero, bianco)» ≠ «due bianche e una nera». Nel primo caso l'ordine è fissato (moltiplichi le condizionate); nel secondo includi il numero di ordinamenti.
- **Traslata vs non traslata.** L'errore che costa più punti perché il risultato resta plausibile: media $\frac1p$ (traslata) vs $\frac{1-p}{p}$. Il prof usa sempre le traslate.
- **Con vs senza reinserimento.** Cambia tutto: indipendenza e binomiale/geometrica di là, dipendenza e ipergeometrica/condizionate di qua. È la **Domanda 1** del metodo, non un dettaglio.
- **Più di due colori.** Non è più binomiale né ipergeometrica a due classi. Ma se distingui **una** categoria dalle altre, raggruppa in «X / non-X» e torna a due classi (molto più rapido, vedi E.2).
- **Media/varianza vs densità completa.** Per media o varianza basta quasi sempre la formula della distribuzione riconosciuta: calcolare la densità completa e poi $\sum_k k\,p_X(k)$ è corretto ma è la strada lunga.
- **«Verificare che…».** Il risultato è dato: devi mostrare i **passaggi**, non convincerti a occhio (vedi B.1).
- **Parametri simbolici** ($n$ palline, $p$ generica). Il conto è identico, resta in forma letterale. Non è più difficile: è lo stesso esercizio senza numeri.
- **Ogni sotto-domanda è a sé.** Nello stesso Es1 possono convivere conteggio bruto, binomiale e condizionata (vedi G.1): applica il metodo di §1 a ciascuna, non trascinare il modello della D1 sulla D2.

### 6. Collegamenti
- **Teoria di base:** [[Variabili aleatorie discrete]], [[Cap 3 - Modelli Discreti]], [[Cap 2 - Introduzione alla probabilità#Cenni di calcolo combinatorio|calcolo combinatorio]], [[Cap 2 - Introduzione alla probabilità#Estrazioni casuali in blocco|estrazioni in blocco]].
- **Distribuzioni:** [[Distribuzioni binomiale e ipergeometrica]], [[Distribuzione geometrica]], [[Distribuzione binomiale negativa]], [[Distribuzione multinomiale]], [[Distribuzioni uniforme discreta e di Poisson]].
- **Slot vicini:** [[Es2 - Probabilità condizionata]] quando l'esperimento ha due fasi; [[Es3 - Densità congiunta discreta]] che riusa le stesse distribuzioni su due variabili.
