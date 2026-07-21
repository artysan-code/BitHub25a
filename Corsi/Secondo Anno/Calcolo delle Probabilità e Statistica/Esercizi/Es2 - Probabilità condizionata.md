## Es2 — Probabilità condizionata
Secondo esercizio dello scritto, e il più meccanico dei sei. Lo schema è **sempre lo stesso**: un esperimento a **due fasi**, dove la prima fase sceglie a caso in quale situazione ci si trova (quale urna, quale moneta, quale dado) e la seconda fase produce il risultato che si osserva.

Cambiano gli oggetti — urne, monete truccate, giochi con dadi — ma la struttura logica non cambia mai. Chiuso lo schema, l'esercizio è due formule.
### Le due domande possibili, e come distinguerle
Tutto Es2 si riduce a capire **in che verso** va la domanda:

1. **Dalla causa all'effetto** → «calcolare la probabilità di estrarre una pallina bianca», «di vincere il gioco», «che esca testa». Si conosce cosa succede in ciascuno scenario, si vuole la probabilità complessiva → **formula delle probabilità totali**.

2. **Dall'effetto alla causa** → «calcolare la probabilità di aver scelto la seconda urna **sapendo** di aver estratto una bianca», «di aver lanciato due monete **sapendo** di aver ottenuto tutte teste». Si osserva il risultato e si risale allo scenario → **formula di Bayes**.

> [!info] Bayes contiene le probabilità totali
> Il denominatore di Bayes **è** la formula delle probabilità totali. Quindi non sono due esercizi diversi: in Bayes fai lo stesso conto del caso 1 e poi lo metti sotto una frazione. Se sai fare il primo, il secondo è un passo in più.

### Le formule
Sia $\{H_1,\dots,H_n\}$ una **partizione** dello spazio (gli scenari possibili: le urne, le monete) e sia $E$ l'evento osservato.

**Formula delle probabilità totali** — vedi [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|prob. totali]]:

$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$

**Formula di Bayes** — vedi [[01 - Introduzione alla probabilità#Formula di Bayes|Bayes]]:

$$P(H_j|E)=\frac{P(E|H_j)P(H_j)}{\sum_{k=1}^{n}P(E|H_k)P(H_k)}$$

> [!warning] Gli scenari devono essere una partizione
> Gli $H_k$ devono essere **disgiunti** e la loro unione deve coprire tutto: ogni esito possibile deve stare in uno e uno solo scenario. È il motivo per cui negli esercizi le urne si scelgono "a caso" fra quelle elencate, e non ci sono altre possibilità.
>
> Se la traccia raggruppa gli esiti in modo strano — «se esce 1 o 2 …, se esce 3, 4, 5 o 6 …» — la partizione è quella, con $P(H_1)=\frac{2}{6}$ e $P(H_2)=\frac{4}{6}$: non serve tenere sei scenari separati.

### Il metodo operativo, sempre uguale
1. **Dare un nome agli scenari** e all'evento osservato. Macci scrive *«con notazioni ovvie»* e usa $U_1,U_2$ per le urne, $M_1,M_2$ per le monete, $E$ o $T$ o $V$ per l'evento. Fare lo stesso è già metà del lavoro.

2. **Scrivere le probabilità a priori** $P(H_k)$: quasi sempre uniformi, $\frac{1}{2}$ con due urne, $\frac{1}{3}$ con tre.

3. **Calcolare le condizionate** $P(E|H_k)$, cioè: *dentro* quello scenario, qual è la probabilità dell'evento? Questo passaggio è un mini-[[Es1 - Probabilità discreta elementare|Es1]] — estrazioni in blocco, conteggi, sequenze.

4. **Applicare la formula** e semplificare.

Il [[01 - Introduzione alla probabilità#Diagramma ad albero associato alla formula delle Prob. Totali|diagramma ad albero]] è il modo più sicuro di non perdersi: primo livello gli scenari, secondo livello l'evento, e ogni percorso è il prodotto delle probabilità lungo i rami.
### Esercizi svolti — formato 2025-2026
#### Probabilità totali con due urne — appello del 6 Febbraio 2026
Due urne: la prima con due palline bianche e due nere, la seconda con tre bianche e tre nere. Si sceglie un'urna a caso e si estraggono due palline **in blocco** dall'urna scelta. Calcolare la probabilità di estrarre due palline di colori diversi.

**Svolgimento**

Scenari: $U_1$ = "si sceglie la prima urna", $U_2$ = "la seconda", con $P(U_1)=P(U_2)=\frac{1}{2}$. Evento osservato: $E$ = "le due palline hanno colori diversi".

Le condizionate sono due conteggi in blocco, cioè due Es1 in miniatura: si sceglie una bianca fra quelle disponibili e una nera fra quelle disponibili, sul totale dei sottoinsiemi da 2:

$$P(E|U_1)=\frac{\binom{2}{1}\binom{2}{1}}{\binom{4}{2}}=\frac{4}{6}\qquad P(E|U_2)=\frac{\binom{3}{1}\binom{3}{1}}{\binom{6}{2}}=\frac{9}{15}$$

$$P(E)=\frac{4}{6}\cdot\frac{1}{2}+\frac{9}{15}\cdot\frac{1}{2}=\frac{1}{3}+\frac{3}{10}=\frac{10+9}{30}=\frac{19}{30}$$

Nota che le due urne hanno la **stessa proporzione** di bianche e nere, ma danno probabilità condizionate diverse: senza reinserimento la numerosità conta, non solo la proporzione. È lo stesso fenomeno della correzione per popolazione finita vista in [[Es1 - Probabilità discreta elementare|Es1]].
#### Bayes con tre urne — appello del 20 Febbraio 2026
Tre urne: la prima con quattro bianche e due nere, la seconda con tre e tre, la terza con due bianche e quattro nere. Si sceglie un'urna a caso e si estrae una pallina. Calcolare la probabilità di aver scelto la **seconda** urna sapendo di aver estratto una bianca.

**Svolgimento**

La domanda va dall'effetto (bianca) alla causa (quale urna): Bayes. Scenari $U_1,U_2,U_3$ con $P(U_k)=\frac{1}{3}$, evento $B$ = "esce bianca". Le condizionate si leggono direttamente dalla composizione: $P(B|U_1)=\frac{4}{6}$, $P(B|U_2)=\frac{3}{6}$, $P(B|U_3)=\frac{2}{6}$.

$$P(U_2|B)=\frac{P(B|U_2)P(U_2)}{\sum_{k=1}^{3}P(B|U_k)P(U_k)}=\frac{\frac{3}{6}\cdot\frac{1}{3}}{\frac{4}{6}\cdot\frac{1}{3}+\frac{3}{6}\cdot\frac{1}{3}+\frac{2}{6}\cdot\frac{1}{3}}=\frac{3}{4+3+2}=\frac{3}{9}=\frac{1}{3}$$

I fattori $\frac{1}{3}$ e i denominatori $6$ si semplificano tutti: resta il rapporto fra i **numeri di palline bianche**. Quando le urne hanno lo stesso totale e le probabilità a priori sono uniformi, Bayes si riduce a questo.

> [!question] L'osservazione che fa il prof
> $P(U_2|B)=\frac{1}{3}=P(U_2)$: sapere che è uscita una bianca **non cambia** la probabilità di aver scelto la seconda urna, quindi $U_2$ e $B$ sono [[01 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenti]].
>
> Non è un caso: la seconda urna è quella "media", con la stessa proporzione di bianche della media delle tre. Se un risultato di Bayes ti restituisce esattamente la probabilità a priori, non è un errore — è indipendenza, e vale la pena scriverlo.

#### Monete truccate — appello del 19 Giugno 2026
Si lancia un dado equo. Se esce 1 si lancia una moneta con due teste, se esce 2 una moneta con due croci, se esce 3, 4, 5 o 6 una moneta equa. Calcolare la probabilità che esca testa.

**Svolgimento**

Dalla causa all'effetto: probabilità totali. La partizione **non è** sui sei numeri del dado ma sui tre tipi di moneta: $E_1$ = "esce 1" con $P(E_1)=\frac{1}{6}$, $E_2$ = "esce 2" con $P(E_2)=\frac{1}{6}$, $E_3$ = "esce 3, 4, 5 o 6" con $P(E_3)=\frac{4}{6}$.

Le condizionate sono immediate perché le monete truccate sono deterministiche — $P(T|E_1)=1$ (due teste, testa certa) e $P(T|E_2)=0$ (due croci, testa impossibile):

$$P(T)=1\cdot\frac{1}{6}+0\cdot\frac{1}{6}+\frac{1}{2}\cdot\frac{4}{6}=\frac{1+0+2}{6}=\frac{3}{6}=\frac{1}{2}$$

Le due monete truccate si compensano esattamente e resta la probabilità della moneta equa. Anche qui: risultato "troppo pulito" non vuol dire sbagliato.
### Esercizi svolti — varianti dagli appelli precedenti
#### Bayes con un numero variabile di lanci — appello del 3 Febbraio 2025
Si lancia un dado equo. Se esce un numero minore di 5 si lanciano **due** monete eque; se esce 5 o 6 si lancia **una** moneta equa. Calcolare la probabilità di aver lanciato le due monete sapendo di aver ottenuto **tutte teste** nei lanci effettuati (due o uno).

**Svolgimento**

La difficoltà è che l'evento osservato cambia significato a seconda dello scenario: "tutte teste" vuol dire due teste nel primo caso, una sola nel secondo.

Sia $D$ = "si lanciano due monete", con $P(D)=\frac{4}{6}$ e $P(D^c)=\frac{2}{6}$, e sia $T$ = "tutte teste". Allora $P(T|D)=\left(\frac{1}{2}\right)^2=\frac{1}{4}$ e $P(T|D^c)=\frac{1}{2}$.

$$P(D|T)=\frac{P(T|D)P(D)}{P(T|D)P(D)+P(T|D^c)P(D^c)}=\frac{\frac{1}{4}\cdot\frac{4}{6}}{\frac{1}{4}\cdot\frac{4}{6}+\frac{1}{2}\cdot\frac{2}{6}}=\frac{1/6}{1/6+1/6}=\frac{1}{2}$$

Con due soli scenari la partizione è semplicemente $\{D,D^c\}$: non serve inventare nomi, il complementare basta.

> [!warning] Trappola dell'evento che cambia forma
> Osservare "tutte teste" con due monete è **più difficile** che con una ($\frac{1}{4}$ contro $\frac{1}{2}$), quindi l'osservazione sposta la credenza verso lo scenario a una moneta. Il risultato $\frac{1}{2}$ è il pareggio esatto fra il vantaggio a priori dei due lanci ($\frac{4}{6}$) e il loro svantaggio a posteriori.

#### Due fasi con i dadi — appello del 20 Febbraio 2025
Si lancia un dado: se esce 1 o 2 si lanciano due dadi e si vince se la somma è 7; se esce 3, 4, 5 o 6 si lanciano due dadi e si vince se entrambi i numeri sono minori di 4. Calcolare la probabilità di vincere.

**Svolgimento**

Scenari raggruppati: $\{X\le2\}$ con probabilità $\frac{2}{6}$ e $\{X>2\}$ con probabilità $\frac{4}{6}$, dove $X$ è il numero uscito al primo lancio.

Le condizionate sono conteggi su $36$ coppie ordinate. Somma 7: le coppie sono $(1,6),(2,5),(3,4),(4,3),(5,2),(6,1)$, quindi 6 casi. Entrambi minori di 4: $3\times3=9$ casi.

$$P(V)=\frac{6}{36}\cdot\frac{2}{6}+\frac{9}{36}\cdot\frac{4}{6}=\frac{1}{18}+\frac{3}{18}=\frac{4}{18}=\frac{2}{9}$$

Il prof nella soluzione **elenca le coppie** invece di ragionare a formule: con 36 esiti conviene, ed è meno soggetto a errori.
#### Parametro simbolico e richiesta di verifica — appello del 21 Giugno 2025
Sia $p\in(0,1)$ fissato. Due monete: la prima dà testa con probabilità $p$, la seconda con probabilità $1-p$. Si sceglie una moneta a caso e la si lancia **due volte**. Verificare che la probabilità di ottenere due teste è $\frac{1-2p+2p^2}{2}$.

**Svolgimento**

Scenari $M_1,M_2$ con $P(M_1)=P(M_2)=\frac{1}{2}$. Dentro ciascuno scenario i due lanci sono indipendenti, quindi le condizionate sono $p^2$ e $(1-p)^2$:

$$P(E)=p^2\cdot\frac{1}{2}+(1-p)^2\cdot\frac{1}{2}=\frac{p^2+1-2p+p^2}{2}=\frac{1-2p+2p^2}{2}$$

> [!info] «Verificare che» non è «calcolare»
> Quando la traccia fornisce già il risultato, il punto non è arrivarci ma **mostrare i passaggi**. Il risultato è dato apposta: serve a controllare di non aver sbagliato strada, non a saltare il lavoro. Scrivere solo l'ultima uguaglianza non vale nulla.

### Trappole ricorrenti
- **Verso della condizionata**: $P(E|H)$ e $P(H|E)$ sono numeri diversi. Se la traccia contiene la parola **«sapendo»** o **«dato che»**, quello che segue è la condizione, cioè ciò che sta **dopo** la barra.

- **Le condizionate si leggono dentro lo scenario**: $P(B|U_2)$ si calcola guardando *solo* la seconda urna, come se le altre non esistessero. È l'errore più comune: mescolare le palline di urne diverse in un unico conteggio.

- **Partizione mal fatta**: se gli scenari si sovrappongono o non coprono tutto, la formula dà risultati senza senso. Controllo veloce: $\sum_k P(H_k)$ deve fare 1.

- **Scenari con probabilità non uniformi**: se il dado seleziona gli scenari, i pesi sono $\frac{2}{6}$ e $\frac{4}{6}$, non $\frac{1}{2}$ e $\frac{1}{2}$. Le due fasi hanno pesi indipendenti l'uno dall'altro.

- **Risultati "troppo puliti"** ($\frac{1}{2}$, oppure $P(H|E)=P(H)$): quasi sempre sono corretti e segnalano una simmetria o un'indipendenza. Vale la pena commentarlo, come fa il prof.
### Collegamenti
- Teoria: [[01 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|probabilità condizionate]], [[01 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]], [[01 - Introduzione alla probabilità#Formula delle Probabilità Totali|probabilità totali]], [[01 - Introduzione alla probabilità#Formula di Bayes|Bayes]], [[01 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenza]].

- Slot vicini: [[Es1 - Probabilità discreta elementare]] fornisce i conteggi che servono dentro ogni scenario; [[Es3 - Densità congiunta discreta]] usa le condizionate su variabili aleatorie invece che su eventi.
