## Es2 — Probabilità condizionata
Secondo esercizio dello scritto: un esperimento a **due fasi**, dove la prima fase sceglie a caso lo scenario — quale urna, quale moneta, quale dado — e la seconda fase produce l'evento osservato. La teoria di riferimento è la [[Cap 2 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|probabilità condizionata]].
### Prima di tutto: cosa vuol dire "condizionata"
$P(E\mid H)$ si legge *"probabilità di $E$ **sapendo che** è accaduto $H$"*: la barra $\mid$ è "sapendo che", e ciò che le sta **dopo** è la condizione — l'informazione che già possiedi, che restringe lo spazio ai soli casi in cui $H$ è vero. Attenzione al verso: $P(E\mid H)$ e $P(H\mid E)$ sono numeri **diversi**, ed è proprio su questa distinzione che è costruito tutto l'esercizio.
### Le due domande possibili, e come distinguerle
Tutto Es2 si riduce a capire **in che verso** va la domanda:

1. **Dalla causa all'effetto** → «calcolare la probabilità di estrarre una pallina bianca», «di vincere il gioco», «che esca testa». Si conosce cosa succede in ciascuno scenario, si vuole la probabilità complessiva → **formula delle probabilità totali**.
2. **Dall'effetto alla causa** → «calcolare la probabilità di aver scelto la seconda urna **sapendo** di aver estratto una bianca», «di aver lanciato due monete **sapendo** di aver ottenuto tutte teste». Si osserva il risultato e si risale allo scenario → **formula di Bayes**.

> [!info] Bayes contiene le probabilità totali
> Il denominatore di Bayes **è** la formula delle probabilità totali. Quindi non sono due esercizi diversi: in Bayes fai lo stesso conto del caso 1 e poi lo metti sotto una frazione. Se sai fare il primo, il secondo è un passo in più.

### Le formule
Sia $\{H_1,\dots,H_n\}$ una **partizione** dello spazio (gli scenari possibili: le urne, le monete) e sia $E$ l'evento osservato.
Formula delle probabilità totali — vedi [[Cap 2 - Introduzione alla probabilità#Formula delle Probabilità Totali|prob. totali]]:
$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$
Formula di Bayes — vedi [[Cap 2 - Introduzione alla probabilità#Formula di Bayes|Bayes]]:
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

Il [[Cap 2 - Introduzione alla probabilità#Diagramma ad albero associato alla formula delle Prob. Totali|diagramma ad albero]] è il modo più sicuro di non perdersi: primo livello gli scenari, secondo livello l'evento, e ogni percorso è il prodotto delle probabilità lungo i rami.
### Esercizi svolti — formato 2025-2026
#### Probabilità totali con due urne — appello del 6 Febbraio 2026
Due urne: la prima con due palline bianche e due nere, la seconda con tre bianche e tre nere. Si sceglie un'urna a caso e si estraggono due palline **in blocco** dall'urna scelta. Calcolare la probabilità di estrarre due palline di colori diversi.
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** La richiesta — «calcolare la probabilità di estrarre due palline di colori diversi» — parte dalla causa (l'urna scelta) e chiede l'effetto complessivo, senza che compaia «sapendo» o «dato che»: è il verso causa→effetto, quindi si usa la **formula delle probabilità totali**.

**Passo 2 — definire gli scenari e le probabilità a priori.** La prima fase dell'esperimento è la scelta dell'urna: gli scenari sono $U_1$ = "si sceglie la prima urna" e $U_2$ = "si sceglie la seconda", con $P(U_1)=P(U_2)=\frac{1}{2}$ perché la scelta è a caso fra le due. L'evento osservato nella seconda fase è $E$ = "le due palline estratte hanno colori diversi".

**Passo 3 — calcolare le condizionate.** $P(E|U_k)$ si calcola guardando *dentro* una sola urna alla volta ed è un conteggio **in blocco** preso di peso da [[Es1 - Probabilità discreta elementare|Es1]]. "Colori diversi" fra due palline estratte senza ordine significa **una bianca e una nera**: è la densità **ipergeometrica** valutata in $k=1$ (una bianca sulle due estratte). Con $N$ = palline totali nell'urna, $K$ = bianche, $N-K$ = nere e $n=2$ estratte, la formula generale è
$$P(E|U_k)=\frac{\binom{K}{1}\binom{N-K}{1}}{\binom{N}{2}},$$
dove al **denominatore** $\binom{N}{2}$ sono tutti i modi di scegliere 2 palline su $N$ senza ordine, e al **numeratore** si sceglie 1 bianca fra le $K$ **e** 1 nera fra le $N-K$. La prima urna ha 2 bianche e 2 nere ($N=4$, $K=2$), la seconda 3 e 3 ($N=6$, $K=3$):
$$P(E|U_1)=\frac{\binom{2}{1}\binom{2}{1}}{\binom{4}{2}}=\frac{2\cdot2}{6}=\frac{4}{6}\qquad P(E|U_2)=\frac{\binom{3}{1}\binom{3}{1}}{\binom{6}{2}}=\frac{3\cdot3}{15}=\frac{9}{15}$$

**Passo 4 — applicare la formula generale e semplificare.** La formula delle probabilità totali è
$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$
e si legge così: la probabilità complessiva dell'evento è la media delle probabilità condizionate nei vari scenari, pesata con le rispettive probabilità a priori. Con i due scenari $U_1,U_2$ e i valori dei Passi 2 e 3:
$$P(E)=\frac{4}{6}\cdot\frac{1}{2}+\frac{9}{15}\cdot\frac{1}{2}=\frac{1}{3}+\frac{3}{10}=\frac{10+9}{30}=\frac{19}{30}$$
Nota che le due urne hanno la **stessa proporzione** di bianche e nere, ma danno probabilità condizionate diverse: senza reinserimento la numerosità conta, non solo la proporzione. È lo stesso fenomeno della correzione per popolazione finita vista in [[Es1 - Probabilità discreta elementare|Es1]].
#### Bayes con tre urne — appello del 20 Febbraio 2026
Tre urne: la prima con quattro bianche e due nere, la seconda con tre e tre, la terza con due bianche e quattro nere. Si sceglie un'urna a caso e si estrae una pallina. Calcolare la probabilità di aver scelto la **seconda** urna sapendo di aver estratto una bianca.
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** La domanda chiede la probabilità di aver scelto la seconda urna **sapendo** di aver estratto una pallina bianca: si parte dall'effetto osservato (la bianca) e si risale alla causa (quale urna). È il verso effetto→causa, quindi la formula da usare è quella di **Bayes**.

**Passo 2 — definire gli scenari.** Scenari $U_1,U_2,U_3$ = "si sceglie la prima, la seconda, la terza urna", che formano una partizione (si sceglie **una sola** urna a caso fra le tre elencate), con probabilità a priori uniformi $P(U_1)=P(U_2)=P(U_3)=\frac{1}{3}$. Evento osservato: $B$ = "esce una pallina bianca".

**Passo 3 — calcolare le condizionate.** Qui il conteggio è più semplice del caso a due urne: c'è **una sola estrazione**, quindi dentro ogni scenario la probabilità di bianca è semplicemente (bianche)/(totale palline) di quell'urna, letta *senza* mescolarla con le altre. Ognuna delle tre urne ha 6 palline in totale, perciò il denominatore è sempre 6 e cambia solo il numero di bianche (4, 3, 2):
$$P(B|U_1)=\frac{4}{6}\qquad P(B|U_2)=\frac{3}{6}\qquad P(B|U_3)=\frac{2}{6}$$

**Passo 4 — applicare Bayes e semplificare.** La formula generale di Bayes per lo scenario $H_j$ dato l'evento osservato $E$ è
$$P(H_j|E)=\frac{P(E|H_j)P(H_j)}{\sum_{k=1}^{n}P(E|H_k)P(H_k)}$$
si legge così: al numeratore c'è il "ramo" dello scenario che interessa — condizionata per probabilità a priori — mentre al denominatore c'è la somma su **tutti** gli scenari, cioè la probabilità totale di $E$, che funge da fattore di normalizzazione. Qui interessa lo scenario $U_2$ dato $B$:
$$P(U_2|B)=\frac{P(B|U_2)P(U_2)}{\sum_{k=1}^{3}P(B|U_k)P(U_k)}=\frac{\frac{3}{6}\cdot\frac{1}{3}}{\frac{4}{6}\cdot\frac{1}{3}+\frac{3}{6}\cdot\frac{1}{3}+\frac{2}{6}\cdot\frac{1}{3}}=\frac{3}{4+3+2}=\frac{3}{9}=\frac{1}{3}$$
I fattori $\frac{1}{3}$ e i denominatori $6$ si semplificano tutti: resta il rapporto fra i **numeri di palline bianche**. Quando le urne hanno lo stesso totale e le probabilità a priori sono uniformi, Bayes si riduce a questo.

> [!question] L'osservazione che fa il prof
> $P(U_2|B)=\frac{1}{3}=P(U_2)$: sapere che è uscita una bianca **non cambia** la probabilità di aver scelto la seconda urna, quindi $U_2$ e $B$ sono [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenti]].
>
> Non è un caso: la seconda urna è quella "media", con la stessa proporzione di bianche della media delle tre. Se un risultato di Bayes ti restituisce esattamente la probabilità a priori, non è un errore — è indipendenza, e vale la pena scriverlo.

#### Monete truccate — appello del 19 Giugno 2026
Si lancia un dado equo. Se esce 1 si lancia una moneta con due teste, se esce 2 una moneta con due croci, se esce 3, 4, 5 o 6 una moneta equa. Calcolare la probabilità che esca testa.
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** La traccia chiede "calcolare la probabilità che esca testa": si conosce già cosa succede in ciascuno scenario (che moneta si lancia) e si vuole la probabilità dell'evento finale. Non compare né "sapendo" né "dato che", quindi il verso è dalla causa all'effetto → **formula delle probabilità totali**.

**Passo 2 — definire gli scenari e le probabilità a priori.** La partizione **non è** sui sei numeri del dado ma sui tre tipi di moneta che il dado seleziona: $E_1$ = "esce 1" (si lancia la moneta con due teste), $E_2$ = "esce 2" (moneta con due croci), $E_3$ = "esce 3, 4, 5 o 6" (moneta equa). Le probabilità a priori si contano sulle facce del dado equo, ognuna con probabilità $\frac{1}{6}$: $E_1$ ed $E_2$ corrispondono a una sola faccia, mentre $E_3$ ne raccoglie quattro (le facce $\{3,4,5,6\}$), quindi la sua probabilità è $4\cdot\frac{1}{6}=\frac{4}{6}$:
$$P(E_1)=\frac{1}{6}\qquad P(E_2)=\frac{1}{6}\qquad P(E_3)=\frac{4}{6}$$

**Passo 3 — calcolare le condizionate.** Dentro ciascuno scenario la moneta è fissata, quindi $P(T|E_k)$ è semplicemente la probabilità di testa di *quella* moneta. Le due monete truccate sono **deterministiche**, cioè l'esito è sicuro: quella con due teste dà testa a ogni lancio, quindi la probabilità è **certa** e vale $1$; quella con due croci non può dare testa, quindi è **impossibile** e vale $0$; la moneta equa dà testa in un caso su due, cioè $\frac{1}{2}$:
$$P(T|E_1)=1\qquad P(T|E_2)=0\qquad P(T|E_3)=\frac{1}{2}$$

**Passo 4 — applicare la formula generale e sostituire.** La formula delle probabilità totali è
$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$
e si legge così: per ogni scenario si pesa la probabilità condizionata dell'evento per la probabilità a priori di trovarsi in quello scenario, e si sommano i contributi su tutta la partizione. Qui gli scenari sono $E_1,E_2,E_3$ del Passo 2 e l'evento è $T$ = "esce testa", con le condizionate del Passo 3:
$$P(T)=P(T|E_1)P(E_1)+P(T|E_2)P(E_2)+P(T|E_3)P(E_3)=1\cdot\frac{1}{6}+0\cdot\frac{1}{6}+\frac{1}{2}\cdot\frac{4}{6}=\frac{1+0+2}{6}=\frac{3}{6}=\frac{1}{2}$$
Le due monete truccate si compensano esattamente e resta la probabilità della moneta equa. Anche qui: risultato "troppo pulito" non vuol dire sbagliato.
### Esercizi svolti — varianti dagli appelli precedenti
#### Bayes con un numero variabile di lanci — appello del 3 Febbraio 2025
Si lancia un dado equo. Se esce un numero minore di 5 si lanciano **due** monete eque; se esce 5 o 6 si lancia **una** moneta equa. Calcolare la probabilità di aver lanciato le due monete sapendo di aver ottenuto **tutte teste** nei lanci effettuati (due o uno).
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** La traccia chiede la probabilità di aver lanciato le due monete **sapendo** di aver ottenuto tutte teste: si parte dall'effetto osservato (l'esito dei lanci) e si risale alla causa (quante monete sono state lanciate). È il verso di Bayes, non delle probabilità totali. La difficoltà in più è che l'evento osservato **cambia forma** a seconda dello scenario: "tutte teste" vuol dire due teste nel primo caso, una sola nel secondo.

**Passo 2 — definire gli scenari e le probabilità a priori.** Con due soli scenari possibili la partizione è semplicemente $\{D,D^c\}$: non serve inventare nomi separati, basta il complementare. Sia $D$ = "si lanciano due monete" (esce al dado un numero minore di 5) e $T$ = "tutte teste" nei lanci effettuati. Le probabilità a priori si contano sulle facce del dado equo: "un numero minore di 5" sono le facce $\{1,2,3,4\}$, cioè 4 su 6, quindi $P(D)=\frac{4}{6}$; le facce rimaste sono $\{5,6\}$, cioè $P(D^c)=\frac{2}{6}$.

**Passo 3 — calcolare le condizionate.** Dentro ciascuno scenario "tutte teste" cambia significato. Nello scenario $D$ si lanciano **due** monete eque: i due lanci sono **indipendenti** (uno non influenza l'altro), e per eventi indipendenti la probabilità che accadano *entrambi* è il **prodotto** delle singole probabilità, quindi due teste valgono $\frac{1}{2}\cdot\frac{1}{2}=\left(\frac{1}{2}\right)^2$. Nello scenario $D^c$ si lancia una sola moneta, quindi "tutte teste" è una singola testa, di probabilità $\frac{1}{2}$:
$$P(T|D)=\left(\frac{1}{2}\right)^2=\frac{1}{4}\qquad P(T|D^c)=\frac{1}{2}$$

**Passo 4 — applicare la formula di Bayes.** La formula generale è
$$P(H_j|E)=\frac{P(E|H_j)P(H_j)}{\sum_{k=1}^{n}P(E|H_k)P(H_k)}$$
e si legge così: al numeratore la condizionata e la priori dello scenario che interessa ($H_j=D$), al denominatore la somma su **tutti** gli scenari — cioè la stessa espressione delle probabilità totali. Con due soli scenari il denominatore ha due addendi:
$$P(D|T)=\frac{P(T|D)P(D)}{P(T|D)P(D)+P(T|D^c)P(D^c)}=\frac{\frac{1}{4}\cdot\frac{4}{6}}{\frac{1}{4}\cdot\frac{4}{6}+\frac{1}{2}\cdot\frac{2}{6}}=\frac{1/6}{1/6+1/6}=\frac{1}{2}$$

> [!warning] Trappola dell'evento che cambia forma
> Osservare "tutte teste" con due monete è **più difficile** che con una ($\frac{1}{4}$ contro $\frac{1}{2}$), quindi l'osservazione sposta la credenza verso lo scenario a una moneta. Il risultato $\frac{1}{2}$ è il pareggio esatto fra il vantaggio a priori dei due lanci ($\frac{4}{6}$) e il loro svantaggio a posteriori.

#### Due fasi con i dadi — appello del 20 Febbraio 2025
Si lancia un dado: se esce 1 o 2 si lanciano due dadi e si vince se la somma è 7; se esce 3, 4, 5 o 6 si lanciano due dadi e si vince se entrambi i numeri sono minori di 4. Calcolare la probabilità di vincere.
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** «Calcolare la probabilità di vincere» va dalla causa (quale coppia di regole seleziona il primo lancio del dado) all'effetto (vincere o no): nella traccia non compare né «sapendo» né «dato che», quindi serve la formula delle probabilità totali, non Bayes.

**Passo 2 — definire gli scenari.** Il primo lancio del dado sceglie fra due scenari, ma **raggruppati** e non sui sei singoli valori: $H_1=\{X\le2\}$ (esce 1 o 2) e $H_2=\{X>2\}$ (esce 3, 4, 5 o 6), dove $X$ è il numero uscito al primo lancio, con $P(H_1)=\frac{2}{6}$ e $P(H_2)=\frac{4}{6}$ — come per la partizione raggruppata già vista con le monete truccate, $H_1$ e $H_2$ restano disgiunti e coprono tutto lo spazio. Sia $V$ = "si vince" l'evento osservato.

**Passo 3 — calcolare le condizionate.** Dentro ciascuno scenario si lanciano due dadi: è un mini-[[Es1 - Probabilità discreta elementare|Es1]] di conteggio su **spazio uniforme**, un solo scenario alla volta. I due dadi danno $6\times6=36$ coppie ordinate — ordinate perché i dadi sono distinguibili, quindi $(1,6)$ e $(6,1)$ contano come esiti diversi — tutte equiprobabili perché i dadi sono equi; ogni probabilità è (coppie favorevoli)/36.
Dentro $H_1$ si vince se la somma è 7: elencando le coppie favorevoli sono $(1,6),(2,5),(3,4),(4,3),(5,2),(6,1)$, cioè 6. Dentro $H_2$ si vince se **entrambi** i numeri sono minori di 4, cioè ciascun dado deve stare in $\{1,2,3\}$: ci sono 3 valori possibili per il primo dado e, indipendentemente, 3 per il secondo, quindi per il principio di moltiplicazione $3\times3=9$ coppie favorevoli:
$$P(V|H_1)=\frac{6}{36}\qquad P(V|H_2)=\frac{9}{36}$$

**Passo 4 — applicare la formula generale e semplificare.** La formula delle probabilità totali
$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$
si legge così: la probabilità complessiva dell'evento è la media delle probabilità condizionate in ciascuno scenario, pesata per quanto è probabile trovarsi in quello scenario. Con i due soli scenari $H_1,H_2$:
$$P(V)=P(V|H_1)P(H_1)+P(V|H_2)P(H_2)=\frac{6}{36}\cdot\frac{2}{6}+\frac{9}{36}\cdot\frac{4}{6}=\frac{1}{18}+\frac{3}{18}=\frac{4}{18}=\frac{2}{9}$$
Il prof nella soluzione **elenca le coppie** invece di ragionare a formule: con 36 esiti conviene, ed è meno soggetto a errori.
#### Parametro simbolico e richiesta di verifica — appello del 21 Giugno 2025
Sia $p\in(0,1)$ fissato. Due monete: la prima dà testa con probabilità $p$, la seconda con probabilità $1-p$. Si sceglie una moneta a caso e la si lancia **due volte**. Verificare che la probabilità di ottenere due teste è $\frac{1-2p+2p^2}{2}$.
**Svolgimento**
**Passo 1 — riconoscere il verso della domanda.** "Calcolare la probabilità di ottenere due teste" va dalla causa (quale moneta viene scelta) all'effetto (l'esito dei lanci): non compare né "sapendo" né "dato che", quindi il verso è quello delle **probabilità totali**, non di Bayes. La particolarità di questa traccia è che chiede di **verificare** un risultato già dato, $\frac{1-2p+2p^2}{2}$: il compito non è arrivarci per la prima volta, ma ricostruire i passaggi che ci portano esattamente a quell'espressione.

**Passo 2 — definire gli scenari.** Gli scenari sono le due monete: $M_1$ = "si sceglie la prima moneta" (quella che dà testa con probabilità $p$) e $M_2$ = "si sceglie la seconda" (quella con probabilità $1-p$). La scelta fra le due è a caso, quindi le probabilità a priori sono uniformi:
$$P(M_1)=P(M_2)=\frac{1}{2}$$

**Passo 3 — calcolare le condizionate.** Sia $E$ = "escono due teste nei due lanci". Dentro ciascuno scenario la moneta è fissata e i due lanci sono **indipendenti** (il lancio non altera la moneta), quindi la probabilità che escano *entrambe* teste è il **prodotto** delle due probabilità di testa. Con la prima moneta la testa ha probabilità $p$, quindi due teste valgono $p\cdot p=p^2$; con la seconda la testa ha probabilità $1-p$, quindi $(1-p)\cdot(1-p)=(1-p)^2$:
$$P(E|M_1)=p^2\qquad P(E|M_2)=(1-p)^2$$

**Passo 4 — applicare la formula generale e semplificare.** La formula delle probabilità totali
$$P(E)=\sum_{k=1}^{n}P(E|H_k)P(H_k)$$
si legge così: per ogni scenario si moltiplica la probabilità dell'evento *dentro* quello scenario per la probabilità a priori dello scenario, poi si sommano i contributi di tutti gli scenari. Con i due scenari del Passo 2 e le condizionate del Passo 3 (e ricordando che il quadrato $(1-p)^2$ si espande in $1-2p+p^2$):
$$P(E)=p^2\cdot\frac{1}{2}+(1-p)^2\cdot\frac{1}{2}=\frac{p^2+1-2p+p^2}{2}=\frac{1-2p+2p^2}{2}$$
che è esattamente il risultato che la traccia chiedeva di verificare.

> [!info] «Verificare che» non è «calcolare»
> Quando la traccia fornisce già il risultato, il punto non è arrivarci ma **mostrare i passaggi**. Il risultato è dato apposta: serve a controllare di non aver sbagliato strada, non a saltare il lavoro. Scrivere solo l'ultima uguaglianza non vale nulla.

### Trappole ricorrenti
- **Verso della condizionata**: $P(E|H)$ e $P(H|E)$ sono numeri diversi. Se la traccia contiene la parola **«sapendo»** o **«dato che»**, quello che segue è la condizione, cioè ciò che sta **dopo** la barra.
- **Le condizionate si leggono dentro lo scenario**: $P(B|U_2)$ si calcola guardando *solo* la seconda urna, come se le altre non esistessero. È l'errore più comune: mescolare le palline di urne diverse in un unico conteggio.
- **Partizione mal fatta**: se gli scenari si sovrappongono o non coprono tutto, la formula dà risultati senza senso. Controllo veloce: $\sum_k P(H_k)$ deve fare 1.
- **Scenari con probabilità non uniformi**: se il dado seleziona gli scenari, i pesi sono $\frac{2}{6}$ e $\frac{4}{6}$, non $\frac{1}{2}$ e $\frac{1}{2}$. Le due fasi hanno pesi indipendenti l'uno dall'altro.
- **Risultati "troppo puliti"** ($\frac{1}{2}$, oppure $P(H|E)=P(H)$): quasi sempre sono corretti e segnalano una simmetria o un'indipendenza. Vale la pena commentarlo, come fa il prof.
### Collegamenti
- Teoria: [[Cap 2 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|probabilità condizionate]], [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]], [[Cap 2 - Introduzione alla probabilità#Formula delle Probabilità Totali|probabilità totali]], [[Cap 2 - Introduzione alla probabilità#Formula di Bayes|Bayes]], [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenza]].
- Slot vicini: [[Es1 - Probabilità discreta elementare]] fornisce i conteggi che servono dentro ogni scenario; [[Es3 - Densità congiunta discreta]] usa le condizionate su variabili aleatorie invece che su eventi.
