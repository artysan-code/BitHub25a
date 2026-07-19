---
tags:
  - algoritmi
  - greedy
  - esercizi
---
# Teoria — Interval Scheduling e Interval Partitioning
*Esercizio 2 · Interval Scheduling e Interval Partitioning · 8 domande da 4 appelli (21/01/2025 · 18/02/2025 · 09/09/2025 · 30/06/2026).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 21/01/2025, 18/02/2025, 09/09/2025, 30/06/2026.*
## Come leggere questo file
In questi quattro appelli l'Esercizio 2 segue quasi sempre lo stesso schema: tre domande aperte di teoria su un problema greedy, peso crescente dal richiamo mnemonico alla dimostrazione vera. Tre compiti su quattro (18/02/2025, 09/09/2025, 30/06/2026) vertono su **Interval Partitioning (IP)**; solo uno (21/01/2025) su **Interval Scheduling (IS)**. L'errore più costoso di questo slot non è dimenticare una formula: è confondere i due problemi, che condividono input e notazione ma hanno obiettivo, criterio d'ordine e tecnica dimostrativa **opposti**. IS *massimizza* il numero di intervalli compatibili su un'unica risorsa (ordina per tempo di **fine**, earliest finish time); IP *minimizza* il numero di aule necessarie a servire **tutti** gli intervalli (ordina per tempo di **inizio**, earliest start time). Scambiare uno di questi tre elementi tra i due problemi azzera i punti anche quando lo schema superficiale — ordina, poi scandisci — resta corretto in superficie.

Il peso dei tre punti segue quasi sempre lo stesso schema crescente. La **definizione formale** (5 righe) è la componente più meccanica — input, ammissibilità, misura, e nient'altro — ma proprio per questo è dove si perdono punti per fretta, tipicamente omettendo la clausola "a due a due" o l'esplicito "minimizzare $d$". Il **criterio o controesempio** (2-5 righe) sembra un richiamo mnemonico, ma il correttore verifica sempre un elemento concreto: la formula di compatibilità per IS, l'istanza numerica con conteggio delle aule per IP. La **dimostrazione** (10 righe, dove tipicamente si gioca il punteggio) richiede una prova vera — induzione più assurdo per IS, doppia disuguaglianza per IP — non un riassunto discorsivo dell'algoritmo.

La definizione di IP è la domanda più riciclata dell'intero slot: esce **identica nella sostanza** in tre appelli su quattro, cambiando solo la prosa. È un punto quasi gratuito se si scrivono le tre componenti per esteso, ma "a due a due" e l'obiettivo esplicito "minimizzare $d$" sono le prime cose che saltano quando si scrive di fretta. Il controesempio al criterio "finish time" per IP torna invece due volte con un registro diverso — "si motivi perché" contro "si mostri che": la sostanza (istanza numerica, esecuzione passo passo, conteggio aule) non cambia, ma "mostrare" pretende la costruzione scritta per intero, non solo evocata.

Sulla dimostrazione di ottimalità, la scelta della tecnica vale già metà del voto. IS si dimostra con *greedy stays ahead* (confronto indice per indice fra un'unica sequenza greedy e un'unica sequenza ottima, per induzione più assurdo); IP non ammette questo schema, perché la soluzione greedy è ripartita su $d$ aule costruite in parallelo — serve invece l'argomento "a tenaglia" sulla profondità ($d\geq\text{depth}$ per ammissibilità, $\text{depth}\geq d$ per costruzione del greedy). Applicare lo schema sbagliato al problema sbagliato, anche con conti corretti, non prende il punteggio della dimostrazione.
## Definizione formale di Interval Scheduling
La definizione di IS compare una sola volta in questi quattro appelli: è l'unico compito della cartella sull'Interval Scheduling.

*21/01/2025 · Es. 2, punto A*

> A. Si definisca formalmente IS. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dato un insieme di $n$ intervalli $I_1,\ldots,I_n$, ciascuno con tempo di inizio $s_i$ e tempo di fine $f_i$, una **soluzione ammissibile** è un sottoinsieme $S$ di intervalli **a due a due compatibili**, ovvero tale che per ogni $I_i,I_j\in S$ risulti $f_i\leq s_j$ oppure $f_j\leq s_i$ (non si sovrappongono). La **misura** da **massimizzare** è la cardinalità $|S|$, cioè il numero di intervalli (job) schedulabili sull'unica risorsa disponibile.

> [!info]- Spiegazione
> Le tre componenti — input, ammissibilità, misura — vanno tenute distinte e tutte e tre presenti: è lo schema con cui ogni problema di ottimizzazione va definito formalmente ([[01 - Greedy e Interval Scheduling#Interval Scheduling#Definizione del problema|teoria]]).
>
> **La formula di compatibilità $f_i\leq s_j\ \lor\ f_j\leq s_i$ non va mai omessa**: è l'unico punto della definizione realmente verificabile da un correttore. Scrivere a parole "non si sovrappongono" senza la formula lascia ambiguo il caso di confine $f_i=s_j$ (intervalli che si toccano, compatibili per convenzione).
>
> **Il punto critico rispetto a IP.** Qui la misura è $|S|$ **da massimizzare**, e $S$ è un **sottoinsieme** di intervalli (quelli non scelti restano semplicemente scartati). In IP invece si assegna un'etichetta a **ogni** intervallo (nessuno scartato) e si minimizza il **numero di etichette** — cfr. [[#Definizione formale di Interval Partitioning]]. Le due definizioni condividono input e nozione di compatibilità, ma differiscono radicalmente su cosa sia "soluzione ammissibile" e su cosa vada ottimizzato.
>
> **Dove si perdono punti:** omettere la formula di compatibilità; scrivere "minimizzare le risorse" invece di "massimizzare $|S|$" — è la definizione di IP, non di IS.
## Definizione formale di Interval Partitioning
La domanda più riciclata dello slot: esce, con la stessa sostanza, in tre dei quattro appelli — cambia solo la prosa.

*citazione: 18/02/2025 · Es. 2, punto 1 · e 09/09/2025 · Es. 2, punto 1 · e 30/06/2026 · Es. 2, punto 1*

*18/02/2025:*

> 1. Si definisca formalmente il problema di IP. *(Max 5 righe.)*

*09/09/2025 e 30/06/2026 (testo identico fra loro):*

> 1. Si definisca formalmente il problema. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dato un insieme di $n$ intervalli $I_1,\ldots,I_n$ (con $I_i=[s_i,f_i)$), il problema dell'**Interval Partitioning** chiede una **partizione** degli intervalli in classi (aule) $C_1,\ldots,C_d$ tali che ogni classe contenga solo intervalli **a due a due compatibili** — cioè per ogni $I_i,I_j$ nella stessa classe vale $f_i\leq s_j$ oppure $f_j\leq s_i$ — di **numero di classi $d$ minimo** fra tutte le partizioni ammissibili.
>
> **Formulazione equivalente, ammessa in alternativa:** assegnare a ogni intervallo un'**etichetta** (la classe) tale che due intervalli sovrapposti ricevano etichette diverse — la stessa condizione vista come colorazione del grafo di intersezione invece che come partizione.

> [!info]- Spiegazione
> Stesso schema della definizione di [[#Definizione formale di Interval Scheduling|IS]] — input, ammissibilità, misura — con obiettivo **rovesciato**: IS *seleziona* un sottoinsieme massimo su un'unica risorsa (può scartare intervalli), IP *serve tutti* gli intervalli minimizzando le risorse (non può scartare nulla). Cfr. [[01 - Greedy e Interval Scheduling#Confronto riassuntivo|tabella di confronto]].
>
> **«A due a due compatibili» dentro ogni classe** è la clausola che rende la definizione verificabile: non basta dire che una classe "non ha sovrapposizioni" in senso vago, serve il confronto a coppie $f_i\leq s_j\lor f_j\leq s_i$ per ogni coppia della stessa classe — la stessa formula di compatibilità di IS, riusata qui dentro ciascuna classe invece che su un unico insieme.
>
> **La minimizzazione non va data per scontata.** Senza l'obiettivo esplicito "minimizzare $d$" la definizione descrive solo un problema di *decisione* ("è possibile partizionare con $d$ classi?"), non il problema di ottimizzazione richiesto.
>
> **Le tre occorrenze cambiano solo la prosa** — con o senza "il problema di IP" esplicito, "classi" o "aule" — mai il contenuto: input, compatibilità a due a due, misura da minimizzare restano sempre le stesse tre componenti.
>
> **Dove si perdono punti:** omettere "a due a due" nella condizione di compatibilità; dimenticare di scrivere esplicitamente che $d$ va minimizzato, oppure scrivere "massimizzare" per abitudine presa da IS; scrivere "minimizzare le sovrapposizioni" invece di "minimizzare il numero di classi $d$" — è un'altra forma dello stesso errore, sostituire l'obiettivo esplicito con una parafrasi vaga.
## Criteri di ordinamento e perché quelli sbagliati falliscono
Due domande diverse ma con lo stesso spirito: dato un criterio "naturale" ma sbagliato, va esibito un controesempio concreto — mai solo una descrizione qualitativa.
### Il criterio corretto per Interval Scheduling (e perché gli altri falliscono)
*21/01/2025 · Es. 2, punto B*

> B. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema. *(Max 2 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Ordine crescente di tempo di fine $f(j)$ (*earliest finish time first*): si scandiscono gli intervalli in quest'ordine e si aggiunge a $S$ ognuno che sia compatibile con l'ultimo intervallo già selezionato.

> [!info]- Spiegazione
> Il criterio va enunciato **e** collegato alla regola di selezione ("compatibile con l'ultimo scelto") — il solo nome "earliest finish time" senza dire *come* si usa per costruire $S$ è incompleto, anche se sta in una riga.
>
> **Perché gli altri tre criteri "naturali" falliscono**, ciascuno con un controesempio noto ([[01 - Greedy e Interval Scheduling#Interval Scheduling#Schemi greedy candidati e controesempi|teoria]]):
>
> - *Earliest start time* (ordine crescente di $s(j)$): un job lunghissimo tipo $[0,100]$ viene scelto per primo e blocca tutti i job compatibili fra loro che partono dopo, come $[1,2],[3,4],\ldots$
>
> - *Shortest interval* (durata minima $f(j)-s(j)$): dati $[0,3]$, $[3,6]$, $[2,4]$, il job corto $[2,4]$ (durata 2, la minima) si sovrappone a entrambi gli altri e viene scelto per primo; la soluzione greedy si ferma a **1** job, contro i **2** di $\{[0,3],[3,6]\}$ (compatibili: $f=3\leq s=3$).
>
> - *Fewest conflicts* (minor numero di sovrapposizioni $c_j$): **non condivide** il controesempio precedente — su $\{[0,3],[3,6],[2,4]\}$ il job $[2,4]$ ha anzi il **maggior** numero di conflitti (2, contro 1 ciascuno per $[0,3]$ e $[3,6]$), quindi lì il criterio sceglierebbe correttamente. Il fallimento richiede un'istanza diversa, in cui il job "centrale" che blocca due job compatibili ha pochi conflitti solo perché gli altri job coinvolti ne accumulano molti altrove.
>
> Citare **uno solo** di questi controesempi rafforza già la risposta oltre il nudo nome del criterio, restando dentro le 2 righe se scritto in forma sintetica.
>
> **Dove si perdono punti:** scrivere solo "earliest finish time" senza la regola di selezione greedy che lo accompagna; oppure sforare le 2 righe elencando sul compito tutti e quattro gli schemi candidati — quell'elenco appartiene alla spiegazione, non alla soluzione.
### Perché earliest finish time fallisce per Interval Partitioning
*citazione: 09/09/2025 · Es. 2, punto 2 · e 30/06/2026 · Es. 2, punto 2* — stesso controesempio, consegna con registro diverso.

*09/09/2025 ("si motivi perché"):*

> 2. Si motivi perché un algoritmo greedy che ordina gli intervalli per finish time non trova la soluzione ottima. *(Max 5 righe.)*

*30/06/2026 ("si mostri che"):*

> 2. Si mostri che l'algoritmo greedy che ordina gli intervalli per tempo di fine non trova sempre la soluzione ottima. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Controesempio.** $A=[0,4)$, $B=[1,2)$, $C=[3,7)$, $D=[5,6)$: la profondità è $2$ (mai più di due intervalli sovrapposti nello stesso istante), quindi l'ottimo usa $2$ aule, ad es. $\{A,D\}$ e $\{B,C\}$.
>
> Ordinando per **tempo di fine** ($B,A,D,C$): $B$ apre l'aula 1 (libera a $2$); $A$ ($s{=}0<2$) è incompatibile e apre l'aula 2 (libera a $4$); $D$ ($s{=}5\geq2$) entra nell'aula 1, ora libera a $6$; $C$ ($s{=}3$) è incompatibile sia con l'aula 1 ($3<6$) sia con l'aula 2 ($3<4$) e apre una **terza** aula.
>
> Il greedy per finish time usa $3$ aule contro le $2$ ottime: non è corretto, perché ordinare per tempo di fine ignora *quando* un intervallo diventa disponibile.

> [!info]- Spiegazione
> **Causa strutturale.** $A$ inizia a $0$, prestissimo, ma finendo tardi ($f=4$) viene processato *dopo* $B$ (che inizia più tardi ma finisce prima): nel frattempo il greedy ha già aperto l'aula 1 per $B$, e $A$ la trova incompatibile aprendone una seconda. È lo stesso criterio **corretto** per [[#Il criterio corretto per Interval Scheduling (e perché gli altri falliscono)|Interval Scheduling]] ma **sbagliato** qui — i due problemi hanno obiettivo opposto.
>
> **Perché serve il min-heap per vedere il fallimento.** Al passo di $D$ sia l'aula 1 (fine $2$) sia l'aula 2 (fine $4$) sono compatibili con $s(D)=5$; l'implementazione corretta assegna sempre la classe con finish time **minimo** fra quelle compatibili (FIND-MIN sull'heap), quindi $D$ va nell'aula 1, non nella 2. È questa scelta non arbitraria a lasciare l'aula 2 ferma a fine $4$ e a rendere $C$ incompatibile con **entrambe**.
>
> **Perché serve la quarta lezione $D$.** Con soli tre intervalli (togliendo $D$) il greedy per finish time raggiungerebbe comunque la profondità corretta in questo caso: serve $D$ a occupare l'aula 1 al momento giusto perché l'aula 2 resti "intrappolata" a fine $4$ e il conteggio salga a $3$. Serve un'istanza minima ma **completa**, non un abbozzo a cui manca il pezzo decisivo.
>
> **La sfumatura fra "si motivi perché" e "si mostri che".** Sono verbi diversi ma la sostanza coincide: entrambi vogliono un controesempio esplicito, non una descrizione qualitativa. "Motivare" enfatizza leggermente di più il *perché* strutturale, "mostrare" pretende la costruzione — istanza, esecuzione passo passo, conteggio — scritta per intero; in pratica la risposta piena copre entrambe le richieste con lo stesso contenuto.
>
> **Dove si perdono punti:** dare solo la spiegazione qualitativa senza costruire l'istanza numerica; scegliere un'istanza a tre intervalli che per caso non fa scattare il fallimento; scrivere "si può dimostrare che esistono controesempi" senza esibirne uno.
## Depth e lower bound strutturale
La depth non è solo una definizione: è il nucleo dell'intera dimostrazione di ottimalità di IP, qui chiesta in forma compatta — definizione più perché conta, non ancora la prova completa a due disuguaglianze.

*18/02/2025 · Es. 2, punto 2*

> 2. Si definisca il concetto di depth di un'istanza di IP e si discuta perché è importante per analizzare l'algoritmo greedy che risolve IP. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> La **depth** di un'istanza è il massimo, su tutti gli istanti $t$, del numero di intervalli che contengono $t$: $\text{depth}=\max_{t}\bigl|\{I_i:s_i\le t<f_i\}\bigr|$. È importante perché fornisce un **lower bound strutturale**: in ogni soluzione ammissibile gli intervalli sovrapposti in uno stesso istante devono stare in classi distinte, quindi **ogni** soluzione — non solo quella ottima — usa almeno $\text{depth}$ classi. Si dimostra poi che l'algoritmo greedy earliest-start-time-first ne usa **esattamente** $\text{depth}$: combinando le due disuguaglianze $d\geq\text{depth}$ e $\text{depth}\geq d$, si ottiene $d=\text{depth}$, il minimo possibile.

> [!info]- Spiegazione
> **Perché il lower bound è "banale" e proprio per questo potente.** Se $d$ intervalli si sovrappongono nell'istante $t$, nessuna coppia fra loro è compatibile, quindi nessuna coppia può stare nella stessa classe: servono $d$ classi distinte in quell'istante, qualunque algoritmo si usi — anche uno non ancora inventato. È un argomento di conteggio puro, valido per **ogni** soluzione ammissibile.
>
> **Perché il greedy raggiunge esattamente $\text{depth}$.** Quando earliest-start-time-first apre la sua $d$-esima classe per una lezione $j$, lo fa perché $j$ è incompatibile con l'ultima lezione di **ciascuna** delle $d-1$ classi già aperte. Processando in ordine di inizio crescente, quelle $d-1$ lezioni hanno inizio $\leq s(j)$ e, essendo incompatibili con $j$, finiscono dopo $s(j)$: sono quindi tutte attive nell'istante $s(j)$, insieme a $j$ — $d$ lezioni simultaneamente attive, dunque $\text{depth}\geq d$. Dettaglio completo in [[#Interval Partitioning — la tenaglia sulla depth]].
>
> **Perché questo schema sostituisce "greedy stays ahead" qui.** La dimostrazione di IS confronta, passo per passo, un'**unica** sequenza greedy con un'unica sequenza ottima. In IP **non esiste** una sequenza unica da confrontare indice per indice: il greedy costruisce $d$ classi in parallelo. Lo schema alternativo è: (1) lower bound strutturale, valido per ogni soluzione e indipendente dall'algoritmo; (2) l'algoritmo greedy **raggiunge** esattamente quel bound. Le due direzioni si "stringono a tenaglia" sullo stesso valore, e questo *è* la dimostrazione. Cfr. [[01 - Greedy e Interval Scheduling#Tecniche di dimostrazione dell'ottimalità|le due tecniche standard]].
>
> **Depth non è il numero di conflitti.** È un errore ricorrente leggere "depth" come "quante coppie di intervalli si sovrappongono in totale": è invece un **picco di contemporaneità** in un singolo istante. Attenzione a come si costruisce il controesempio: **tre** intervalli a due a due sovrapposti hanno *sempre* un punto in comune (proprietà di Helly per intervalli su una retta — cfr. $[1,4],[2,5],[3,6]$ nella teoria, dove infatti depth $=3$), quindi non bastano per separare depth da numero di conflitti. Serve una catena di almeno **quattro** intervalli: $I_1=[0,2),\,I_2=[1,3),\,I_3=[2,4),\,I_4=[3,5)$ ha tre coppie sovrapposte ma mai più di due intervalli attivi nello stesso istante ($I_1,I_3$ sono compatibili: $f_1=2\le s_3=2$) → depth $=2$, non $3$.
>
> **Dove si perdono punti:** enunciare solo $d\geq\text{depth}$ (il lower bound banale) e fermarsi lì — da sola dice solo che nessun algoritmo può fare meglio, non che *questo* greedy è ottimo: manca $\text{depth}\geq d$, che è ciò che il testo chiede esplicitamente ("perché è importante per **analizzare l'algoritmo greedy**").
## Dimostrazioni di ottimalità
IS e IP si dimostrano ottimi con due tecniche completamente diverse: riconoscere quale delle due si sta usando è il primo modo per accorgersi di aver confuso i due problemi.
### Interval Scheduling — greedy stays ahead
*21/01/2025 · Es. 2, punto C*

> C. Si dimostri a grandi linee perché l'algoritmo del punto (B) trova sempre una soluzione ottima del problema. *(Max 10 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Si usa la tecnica *greedy stays ahead*, confrontando i job scelti dal greedy $i_1,\ldots,i_k$ con quelli di una soluzione ottima $j_1,\ldots,j_m$, entrambe le sequenze ordinate per tempo di fine.
>
> **Lemma** (induzione su $r$): per ogni $r=1,\ldots,k$ vale $f(i_r)\leq f(j_r)$. *Base* ($r=1$): il greedy sceglie subito il job con finish time minimo in assoluto, quindi non può essere battuto da nessun $j_1$. *Passo* ($r>1$): la compatibilità di $j_r$ con $j_{r-1}$ dà $s(j_r)\geq f(j_{r-1})$, che con l'ipotesi induttiva $f(i_{r-1})\leq f(j_{r-1})$ implica $s(j_r)\geq f(i_{r-1})$: $j_r$ era quindi compatibile anche con $i_1,\ldots,i_{r-1}$, cioè un candidato disponibile per il greedy al passo $r$, che sceglie sempre il candidato con finish time minimo — dunque $f(i_r)\leq f(j_r)$.
>
> **Teorema** (per assurdo): se fosse $m>k$, il job aggiuntivo $j_{k+1}$ dell'ottimo sarebbe compatibile con tutta la soluzione greedy (dal lemma con $r=k$: $s(j_{k+1})\geq f(j_k)\geq f(i_k)$), e il greedy lo avrebbe quindi incluso proseguendo la scansione — contraddizione. Dunque $m=k$: il greedy è ottimo. $\blacksquare$

> [!info]- Spiegazione
> **Perché greedy stays ahead e non l'exchange argument.** La soluzione greedy cresce per aggiunta incrementale (un job alla volta, mai rimesso in discussione): è esattamente il caso in cui *greedy stays ahead* è la tecnica naturale ([[01 - Greedy e Interval Scheduling#Tecniche di dimostrazione dell'ottimalità|teoria]]). È stato messo alla prova anche come V/F il 12/09/2023: l'affermazione che la dimostrazione usi l'exchange argument è **falsa**, sia per la tecnica sbagliata sia perché più soluzioni ottime di cardinalità uguale possono coesistere (quindi non è vero che ogni altra soluzione ammissibile abbia valore *strettamente* inferiore).
>
> **Il nucleo tecnico è il confronto indice per indice.** Il lemma non dice che ogni $i_r$ sia buono "in assoluto", ma che finisce **non più tardi** del corrispondente $j_r$ nella *stessa posizione* della sequenza ordinata per finish time — è questo confronto sincronizzato, non un confronto libero fra le due soluzioni, a reggere l'intera induzione.
>
> **Il passo per assurdo è dove si vince o si perde il punto.** Applicare il lemma con $r=k$ non basta da solo: bisogna usarlo per mostrare che $j_{k+1}$ sarebbe stato **compatibile con l'intera $S$ greedy**, e che quindi il greedy stesso lo avrebbe raccolto proseguendo la scansione. Senza questo ultimo passaggio la dimostrazione resta un lemma isolato, non una prova di ottimalità.
>
> **Il contrasto con IP rafforza la lettura corretta.** IP non si dimostra con *greedy stays ahead* ma con il lower bound sulla profondità più un matching upper bound raggiunto dall'algoritmo — cfr. [[#Interval Partitioning — la tenaglia sulla depth]]. Riconoscere quale dei due schemi si sta usando è il primo modo per accorgersi di aver confuso IS con IP.
>
> **Dove si perdono punti:** descrivere l'algoritmo (ordina per finish time, scandisci, aggiungi se compatibile) invece di dimostrarlo — nessun lemma, nessuna induzione, nessun assurdo; oppure enunciare il lemma e fermarsi lì, senza il passo finale che lo trasforma in una dimostrazione di ottimalità globale.
### Interval Partitioning — la tenaglia sulla depth
*30/06/2026 · Es. 2, punto 3* — versione "adulta" (10 righe, dimostrazione completa) della domanda sulla depth chiesta in forma ridotta il 18/02/2025 → [[#Depth e lower bound strutturale]].

> 3. Si argomenti sulla correttezza dell'algoritmo greedy che ordina gli intervalli per tempo di inizio. *(Max 10 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Sia $d$ il numero di aule aperte dal greedy e $\text{depth}$ la profondità dell'istanza. Si mostra $d=\text{depth}$ per doppia disuguaglianza.
>
> **$d\geq\text{depth}$.** Il greedy non assegna mai due intervalli incompatibili alla stessa aula, quindi la sua soluzione è ammissibile; per il lower bound strutturale, ogni soluzione ammissibile usa almeno $\text{depth}$ aule (gli intervalli sovrapposti in un istante devono stare in aule distinte).
>
> **$\text{depth}\geq d$.** Si consideri l'istante in cui il greedy apre l'ultima aula, la $d$-esima, per un intervallo $j$: ciò accade solo perché $j$ è incompatibile con l'ultimo intervallo di **ciascuna** delle $d-1$ aule già aperte, cioè nessuna di esse è ancora terminata a $s(j)$. Poiché il greedy processa in ordine di **inizio crescente**, ognuna di quelle $d-1$ aule ospita un intervallo iniziato prima di $s(j)$ e non ancora finito: è quindi attivo nell'istante $s(j)$. Con $j$ stesso, sono $d$ intervalli mutuamente sovrapposti in $s(j)$, dunque $\text{depth}\geq d$.
>
> Dalle due disuguaglianze, $d=\text{depth}$: il greedy usa il minimo numero di aule possibile, quindi è ottimo. $\blacksquare$

> [!info]- Spiegazione
> **Uno schema diverso dai due standard.** Non è *greedy stays ahead* (non c'è un'unica sequenza greedy da confrontare indice per indice con un'unica soluzione ottima — qui la soluzione è ripartita su $d$ aule parallele) né un *exchange argument*. È un terzo schema, "a tenaglia": si esibisce un **lower bound** valido per ogni soluzione ammissibile, indipendente dall'algoritmo ($d\geq\text{depth}$), e si mostra che il greedy lo **raggiunge** esattamente ($\text{depth}\geq d$). Confronto diretto con l'altro schema in [[#Interval Scheduling — greedy stays ahead]].
>
> **Il passaggio che regge tutto è l'ordine di processamento.** "Le $d-1$ aule sono attive in $s(j)$" non è ovvio: serve che quelle aule contengano intervalli già **iniziati** prima di $s(j)$, e questo è garantito **solo** perché il greedy scandisce per tempo di inizio crescente. Con un ordine diverso (per esempio per tempo di fine — [[#Perché earliest finish time fallisce per Interval Partitioning|che infatti fallisce]]) l'argomento crolla.
>
> **Perché "incompatibile con ciascuna delle $d-1$ aule" implica "attivo in $s(j)$".** Un'aula è incompatibile con $j$ se il suo ultimo intervallo finisce **dopo** $s(j)$; combinato con "è iniziato prima di $s(j)$" (dall'ordine di processamento), l'intervallo soddisfa $\text{inizio}\leq s(j)<\text{fine}$, cioè è per definizione attivo in quell'istante.
>
> **Dove si perdono punti:** dimostrare solo $d\geq\text{depth}$ (il lower bound, valido ma non specifico all'algoritmo) e fermarsi — è la metà facile; oppure asserire $\text{depth}\geq d$ senza giustificare perché le $d-1$ aule già aperte contengono intervalli ancora attivi in $s(j)$, che è il punto in cui entra in gioco l'ordine di inizio crescente.
## Complessità degli algoritmi
L'unica domanda dello slot che vieta esplicitamente la dimostrazione di correttezza: qui si valutano solo la descrizione dell'algoritmo e il conteggio dei costi.

*09/09/2025 · Es. 2, punto 3*

> 3. Si descriva invece l'algoritmo greedy ottimo per il problema discutendone la complessità computazionale *(non si discuta invece la correttezza)*. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Algoritmo (earliest-start-time-first).** Si ordinano gli intervalli per tempo di **inizio** $s_i$ crescente. Si mantiene un **min-heap delle aule aperte**, con chiave = tempo di fine dell'ultimo intervallo assegnato a ciascuna. Per ogni intervallo $i$, nell'ordine: si guarda il minimo del heap (FIND-MIN); se $f_{\min}\leq s_i$ l'aula è compatibile, vi si assegna $i$ e si aggiorna la chiave a $f_i$ (INCREASE-KEY); altrimenti si apre una nuova aula con chiave $f_i$ (INSERT).
>
> **Complessità.** Ordinamento iniziale: $O(n\log n)$. Le $n$ operazioni sul min-heap costano $O(\log n)$ ciascuna (FIND-MIN/INSERT/INCREASE-KEY) $\Rightarrow O(n\log n)$. **Totale: $O(n\log n)$.**

> [!info]- Spiegazione
> **Perché basta guardare il minimo del heap.** L'unica aula che può accogliere l'intervallo corrente $i$ è quella che si libera *prima*: se nemmeno la più favorevole (il minimo del heap) è compatibile con $s_i$, nessuna delle altre — che si liberano ancora più tardi — può esserlo. Questo è ciò che rende sufficiente un confronto $O(1)$ con FIND-MIN invece di scandire tutte le aule aperte. Pseudocodice completo in [[01 - Greedy e Interval Scheduling#Interval Partitioning#Algoritmo earliest-start-time-first|teoria]].
>
> **Perché qui serve un heap e in Interval Scheduling no.** IS confronta ogni candidato con un'unica variabile $j^*$ (l'ultimo intervallo scelto), $O(1)$ per confronto, perché la soluzione è una sequenza su un'unica risorsa. Qui le "risorse" (aule) sono molte e aperte in parallelo, quindi serve una struttura che restituisca velocemente *quale* aula è la più favorevole: da qui il min-heap e il fattore $O(\log n)$ per intervallo.
>
> **Perché la traccia vieta la correttezza qui.** La dimostrazione — le due disuguaglianze $d\geq\text{depth}$ e $\text{depth}\geq d$, cfr. [[#Interval Partitioning — la tenaglia sulla depth]] — è materia separata, già chiesta per esteso il 30/06/2026 come punto a sé (max 10 righe): impacchettarla comunque in questo punto da 5 righe non aggiunge punti — la consegna la esclude esplicitamente — e sottrae spazio alla descrizione dell'algoritmo e al conteggio della complessità, che sono ciò che viene valutato qui.
>
> **Dove si perdono punti:** scrivere la dimostrazione di ottimalità nonostante il divieto esplicito della traccia, sottraendo righe a algoritmo e complessità; oppure confondere l'ordine (start time, qui) con quello — sbagliato per questo problema — del [[#Perché earliest finish time fallisce per Interval Partitioning|controesempio per finish time]].
