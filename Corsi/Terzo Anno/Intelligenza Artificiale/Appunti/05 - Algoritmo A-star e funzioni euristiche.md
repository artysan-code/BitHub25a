---
tags:
  - intelligenza-artificiale
  - ricerca
  - euristiche
slide: []
---
# Algoritmo A* e funzioni euristiche
Lezione 4 (19/10/2026): si chiude la famiglia di algoritmi di [[04 - Ricerca non informata e ricerca euristica#Ricerca euristica|ricerca euristica]] con le proprietà di A\*: euristiche ammissibili e consistenti, completezza, ottimalità e consumo di memoria, con le varianti a memoria limitata. Poi si discute come confrontare e come costruire le euristiche (dominanza, fattore di ramificazione effettivo, problemi rilassati, pattern database, apprendimento). Si chiude con un primo esercizio di traduzione di frasi italiane in formule logiche, che prepara la parte del corso sulla conoscenza.
## Le esercitazioni: confrontare le euristiche
Nell'ultima esercitazione (un labirinto) la prima euristica che viene in mente, la **distanza di Manhattan**, basta già a risolvere il problema. Chi finisce presto è invitato a **confrontare euristiche diverse**: ad esempio la distanza **euclidea**, più vicina al costo vero e applicabile anche in spazi non discreti (su una mappa geografica Manhattan è meno naturale). Il confronto interessante riguarda la **memoria occupata** e il **numero di operazioni** necessarie per arrivare alla soluzione.
## A*
Si riprende l'algoritmo introdotto nella lezione precedente: una ricerca con coda con priorità ordinata per

$$f(n) = g(n) + h(n)$$

dove $g(n)$ è il costo, noto, del cammino dalla radice a $n$ e $h(n) \geq 0$ è la stima del costo da $n$ all'obiettivo. Con $h = 0$ si torna alla [[04 - Ricerca non informata e ricerca euristica#Ricerca a costo uniforme|ricerca a costo uniforme]]; con $h > 0$ si possono ordinare meglio le alternative. Sugli stati obiettivo deve valere $h = 0$.

> [!example] A* sulla Romania
> Con $h$ = distanza in linea d'aria da Bucarest (Arad 366, Sibiu 253, Fagaras 176, Rimnicu Vilcea 193, Pitesti 100), da Arad si generano Sibiu, Timisoara e Zerind. Sibiu ha $f = 140 + 253 = 393$, il valore migliore, anche se costa qualche chilometro: è una strada nella direzione giusta. Da Sibiu si generano Arad, Fagaras, Oradea e Rimnicu Vilcea, e si espande Rimnicu Vilcea ($f = 220 + 193 = 413$). Fagaras resta competitiva e viene espansa, e genera Bucarest con $f = 450$. Ma Pitesti ($f = 317 + 100 = 417$) è ancora più promettente, e da lì si raggiunge Bucarest con $f = 418$. Il nodo obiettivo con $f = 450$ resta in frontiera e non viene mai estratto: A\* restituisce il cammino ottimo da 418 km.

Perché l'ordinamento della coda abbia senso, $g$ e $h$ devono **significare qualcosa** per il problema: $h$ deve essere un'informazione vera sulla distanza dall'obiettivo, e i costi delle azioni devono essere **non nulli**. Se un'azione sbagliata non costa niente, si possono commettere errori all'infinito senza che la coda lo registri, come chi fa clic mille volte su un sistema bloccato invece di fermarsi.
### Completezza
Serve che il costo degli archi non possa diventare arbitrariamente piccolo: deve esistere $\varepsilon > 0$ con $c(n, a, n') \geq \varepsilon$ (vedi il [[03 - Risoluzione di problemi mediante ricerca#Il costo del cammino|costo del cammino]]). Se i costi si dividessero per 10 a ogni passo, la loro somma convergerebbe a un valore finito anche lungo un cammino infinito, e la coda resterebbe "ferma" su quel cammino. Con il limite $\varepsilon$, invece, $g$ cresce senza limite lungo ogni cammino infinito.

L'idea della dimostrazione: sia $n_0, n_1, \dots, n_k$ un cammino ottimo verso l'obiettivo $n_k$, e sia $n^*$ il primo nodo del cammino che sta in frontiera. I nodi con $f$ minore di quello di $n^*$ sono in numero **finito** (lo garantiscono $\varepsilon$ e un fattore di ramificazione finito), quindi dopo un numero finito di espansioni tocca a $n^*$. Espanderlo mette in frontiera il suo successore sul cammino, e per lo stesso motivo anche quello verrà espanso. Per induzione lungo il cammino si arriva a $n_k$: se una soluzione esiste, A\* la trova.
### Ammissibilità e ottimalità
Non basta trovare **una** soluzione: si vuole che la prima trovata sia la **migliore**. Si confronta $h$ con l'euristica ideale.

> [!quote] Euristica perfetta
> $h^*(n)$ è il costo **esatto** del cammino minimo da $n$ a un obiettivo, e $f^*(n) = g(n) + h^*(n)$ è il costo della migliore soluzione vincolata a passare per $n$, se $g(n)$ è il costo del cammino minimo fino a $n$.

$h^*$ è un'astrazione matematica: se la si conoscesse si avrebbe un algoritmo in forma chiusa e non servirebbe cercare. Il gioco dell'IA è **approssimarla bene**. Perché $g$ sia quello del cammino minimo, quando un nodo entra in frontiera deve puntare al padre da cui lo si raggiunge nel modo **più conveniente**.

> [!quote] Euristica ammissibile
> Un'euristica $h$ è **ammissibile** se non sovrastima mai il costo per raggiungere l'obiettivo:
> $$0 \leq h(n) \leq h^*(n) \quad \text{per ogni } n$$
> Un algoritmo A con euristica ammissibile si chiama **A\***.

Le euristiche viste finora sono ammissibili: la distanza in linea d'aria non può superare quella stradale, perché il segmento è il cammino più breve possibile; la distanza di Manhattan su una griglia non può superare il numero di passi effettivi in un labirinto con muri. Con un'euristica ammissibile, il primo nodo obiettivo estratto dalla coda è anche quello di costo minimo.

> [!info] Domanda a lezione: e se $h$ sovrastima?
> L'algoritmo trova comunque una soluzione, ma è solo un algoritmo A e la soluzione **può non essere ottima**. Una sovrastima sbagliata su un nodo può invertire l'ordine di due soluzioni nella coda: l'informazione non è più correlata con il problema. Se tutte le stime fossero sbagliate dello **stesso** fattore basterebbe riscalarle, ma per farlo bisognerebbe conoscere lo spazio degli stati. Nei problemi geometrici è facile restare ammissibili; in spazi come quello delle parole che un LLM può scegliere, $h$ è spesso stimata brutalmente dai dati.
### Consistenza
L'ammissibilità basta quando lo spazio di ricerca è un **albero**. Su un **grafo**, dove si scartano gli stati già esplorati, serve una condizione più forte.

> [!quote] Euristica consistente (monotona)
> Un'euristica $h$ è **consistente** se per ogni nodo $n$ e ogni successore $n'$ generato con l'azione $a$:
> $$h(n) \leq c(n, a, n') + h(n')$$
> e $h(G) = 0$ per ogni obiettivo $G$.

È una **disuguaglianza triangolare**: la stima da $n$ non può superare il costo di un passo verso $n'$ più la stima da $n'$, quindi la stima non può "crollare" passando a un nodo intermedio. Ne segue che $f$ è **non decrescente** lungo ogni cammino:

$$f(n') = g(n) + c(n, a, n') + h(n') \geq g(n) + h(n) = f(n)$$

Ogni euristica consistente è anche ammissibile. Con un'euristica consistente, e l'insieme degli stati già esplorati che evita i cicli, A\* è ottimo anche sui grafi: i nodi vengono espansi in ordine di $f$ non decrescente, quindi il primo obiettivo che emerge è il meno costoso.
### Contorni e bilancio
Poiché $f$ è non decrescente, A\* espande i nodi per **contorni** di $f$ crescente attorno allo stato iniziale, come le curve di livello di una mappa. Se $C^*$ è il costo ottimo, A\* espande tutti i nodi con $f(n) < C^*$, alcuni con $f(n) = C^*$ e nessuno con $f(n) > C^*$: questi ultimi vengono **potati**. Con euristiche migliori i contorni si allungano verso l'obiettivo invece di allargarsi in cerchio.

> [!quote] Proprietà di A*
> - **Completo**, se il fattore di ramificazione è finito e i costi sono almeno $\varepsilon > 0$.
> - **Ottimo**, con euristica ammissibile (alberi) o consistente (grafi).
> - **Ottimamente efficiente**: tra gli algoritmi che usano la stessa euristica ed estendono cammini dalla radice, nessuno garantisce l'ottimo espandendo meno nodi.
> - **Tempo** esponenziale nel caso peggiore, $O(b^d)$, con una base che dipende dalla qualità di $h$.
> - **Spazio** esponenziale: è il vero limite.

A\* è un buon compromesso tra l'avidità di chi guarda in avanti ($h$) e la memoria del cammino già fatto ($g$). Il suo problema è la memoria: tiene la frontiera, che in un labirinto $1000 \times 1000$ contiene moltissimi nodi, e anche tutti gli stati già esplorati (i nodi "rossi" delle animazioni).
### Varianti a memoria limitata
- **IDA\*** (*iterative deepening A\**): come l'[[04 - Ricerca non informata e ricerca euristica#Profondità limitata e approfondimento iterativo|approfondimento iterativo]], ma il limite è sul valore di $f$ invece che sulla profondità. A ogni iterazione si espandono i cammini entro la soglia corrente, e la si alza solo quanto serve. Non si memorizza la storia dell'intera ricerca.
- **A\* a memoria limitata** (*memory-bounded*, ad esempio SMA\*): si esegue A\* finché la memoria basta. Quando la frontiera supera il budget, si **eliminano i nodi peggiori** in fondo alla coda con priorità e si tengono i più promettenti.
- **Beam search**: si tiene sempre solo un numero fissato $k$ di nodi migliori. La ricerca diventa guidata dal limite di memoria più che dalla garanzia di ottimalità.

> [!question] Domanda tipica d'esame
> Quando A\* è completo e quando è ottimo? Definisci euristica ammissibile ed euristica consistente, spiega perché la consistenza implica che $f$ sia non decrescente lungo i cammini, e mostra con un esempio cosa succede se $h$ sovrastima.
## Qualità di un'euristica
### Dominanza
Con $h = 0$ l'algoritmo guarda solo i cammini già fatti e non guarda avanti; con $h = h^*$ va dritto alla soluzione. Ogni euristica ammissibile sta **in mezzo**, e conviene quella più vicina a $h^*$.

> [!quote] Dominanza
> Se $h_1$ e $h_2$ sono ammissibili e $h_2(n) \geq h_1(n)$ per ogni $n$, si dice che $h_2$ **domina** $h_1$. A\* con $h_2$ non espande mai più nodi di A\* con $h_1$ (a parità di gestione dei pareggi).

Nel [[04 - Ricerca non informata e ricerca euristica#Euristiche per il gioco dell'8|gioco dell'8]], $h_1$ conta le tessere fuori posto e $h_2$ somma le distanze di Manhattan. Una tessera fuori posto contribuisce 1 a $h_1$ e almeno 1 a $h_2$, quindi $h_2 \geq h_1$ sempre (nell'esempio, 18 contro 8). Scrivere 8 comprime molta conoscenza su come si passa da una configurazione all'altra; 18 viene da verifiche più fini, che distinguono e ordinano meglio gli stati. $h_2$ è **più informata**, resta ammissibile, e quindi è preferibile.

Più l'euristica è informata, più scende il costo della **ricerca**. Il costo complessivo, però, comprende anche il costo di **calcolare** l'euristica e quello di eseguire la soluzione: un'euristica molto informata ma costosissima da calcolare non è necessariamente un affare.
### Fattore di ramificazione effettivo
Per misurare la qualità di un'euristica si usa il **fattore di ramificazione effettivo** $b^*$: se A\* genera $N$ nodi per trovare una soluzione a profondità $d$, $b^*$ è il fattore di ramificazione di un albero **uniforme** di profondità $d$ con $N + 1$ nodi:

$$N + 1 = 1 + b^* + (b^*)^2 + \dots + (b^*)^d$$

Ad esempio, una soluzione a profondità 5 trovata generando 52 nodi dà $b^* \approx 1{,}92$. Più $b^*$ è vicino a 1, più la ricerca è vicina a un andamento lineare: si toglie un nodo dalla frontiera e se ne aggiunge circa uno. Con $b^*$ vicino a 2 il numero di nodi raddoppia a ogni livello.

> [!example] Gioco dell'8, soluzioni a profondità 14
> | Algoritmo | Nodi generati | $b^*$ |
> |---|---|---|
> | Approfondimento iterativo | 3 473 941 | 2,83 |
> | A\* con $h_1$ | 539 | 1,42 |
> | A\* con $h_2$ | 113 | 1,24 |
>
> Si passa da un numero di nodi intrattabile a uno piccolissimo, e la differenza cresce con la profondità.

> [!warning] Da verificare
> Dalla registrazione i valori della tabella mostrata a lezione non sono leggibili (si sentono 1,38, 1,44 e 1,79). I numeri sopra sono quelli di AIMA (3ª ed., fig. 3.29): confrontarli con le slide quando saranno pubblicate.

In problemi a crescita esponenziale, come il riconoscimento del parlato, la scelta della parola successiva o gli scacchi, **migliorare di poco l'euristica** permette di risolvere problemi molto più grandi con la stessa macchina.
## Come si inventano le euristiche
### Problemi rilassati
Si toglie qualche vincolo al problema e si calcola il costo **esatto** della soluzione del problema **rilassato**. Il costo ottimo di un rilassamento è un'euristica ammissibile per il problema originale (togliere vincoli può solo rendere le soluzioni più economiche), e rilassando allo stesso modo tutte le alternative si ottengono stime confrontabili tra loro.

> [!example] Rilassamenti del gioco dell'8
> La regola è: una tessera si può spostare da A a B se A e B sono adiacenti e B è vuota.
> - Se una tessera può andare **ovunque** (la si stacca e la si incastra al suo posto), il costo esatto è il numero di tessere fuori posto: $h_1$.
> - Se una tessera può andare in una casella **adiacente** anche se occupata, il costo esatto è la somma delle distanze di Manhattan: $h_2$.
>
> $h_2$ viene da un rilassamento più **debole**, cioè più vicino al problema vero, ed è per questo più informata.
### Massimo di più euristiche
Se si hanno più euristiche ammissibili $h_1, \dots, h_k$ (ad esempio, nei problemi geometrici, le distanze $L_1$, $L_2$ e in generale le metriche $L_p$), nessuna domina le altre su tutti i nodi. Si prende nodo per nodo la più grande:

$$h(n) = \max\{h_1(n), \dots, h_k(n)\}$$

Il massimo di euristiche ammissibili è ancora **ammissibile** e le domina tutte: è un modo adattivo, quasi una votazione, di usare a ogni nodo il punto di vista più informato.
### Pattern database
Molte configurazioni ricorrono localmente. Si risolvono in modo esatto dei **sottoproblemi** (ad esempio, nel gioco dell'8, portare a posto le tessere 1-4 ignorando le altre, indicate con un asterisco) e se ne memorizza il costo in un **database di pattern**. Durante la ricerca si cerca il pattern dello stato corrente e se ne usa il costo come euristica: è un *caching* di soluzioni di cui si conosce il costo ottimo, un po' come fa un giocatore esperto che riconosce le configurazioni già viste. Il problema è l'**interferenza**: le mosse che risolvono un pattern possono spostare le tessere di un altro, e sommare i costi di pattern diversi può far perdere l'ammissibilità. Si usano allora pattern **disgiunti**, che contano solo le mosse delle proprie tessere.
### Apprendere l'euristica dall'esperienza
Si risolvono molte istanze del problema e si raccolgono le coppie (stato, costo esatto della soluzione da quello stato), cioè campioni di $h^*$. Su questi dati si addestra un **regressore** (una legge lineare, quadratica, una rete neurale) che, per uno stato mai visto, stima $h$. È un'ipotesi appresa che approssima $h^*$: un **modello dell'euristica**. Una regressione di questo tipo non garantisce l'ammissibilità.
### Combinazioni lineari
Invece del massimo si può usare una combinazione pesata di **caratteristiche** (*feature*) dello stato:

$$h(n) = c_1\,x_1(n) + c_2\,x_2(n) + \dots$$

ad esempio $x_1$ = tessere fuori posto e $x_2$ = coppie di tessere adiacenti scambiate nel gioco dell'8, oppure il vantaggio di pezzi e i pezzi sotto attacco negli scacchi. Fissare i pesi $c_i$ a mano è tentare di scrivere la legge a occhio; con il machine learning si **apprende** la combinazione migliore, che può fare meglio del massimo. Si guarda il problema da più punti di vista e si impara a combinarli.

> [!example] Un percorso terapeutico
> Nella scelta del farmaco successivo in una terapia, si possono considerare separatamente gli effetti collaterali, l'efficacia, l'età del paziente: euristiche separate. Nessuna da sola risolve il problema; la loro combinazione sì. È anche il modo di procedere della scienza: si formulano ipotesi diverse, si misura nella direzione che suggeriscono e si combinano quelle che funzionano.

> [!question] Domanda tipica d'esame
> Quando un'euristica è più informata di un'altra e perché conviene usarla? Come si ottengono euristiche ammissibili dai problemi rilassati? Mostralo sul gioco dell'8 ricavando $h_1$ e $h_2$, e spiega perché il massimo di euristiche ammissibili è ancora ammissibile.
## Dal linguaggio alla logica
Per costruire un'euristica, o un qualunque modello di un problema, bisogna leggere la definizione del problema e tradurla in modo rigoroso: come nell'analisi dei requisiti di una base di dati, a ogni frase $S_i$ si associa una formula $F_i$ tale che, quando si crede vera la frase, l'**interpretazione** della formula è *vera*. Cosa sia un'interpretazione si vedrà più avanti nel corso.

> [!example] «Tutti i libri sono di storia»
> - **Con gli insiemi**: dire che l'insieme dei libri $L$ e quello delle cose di storia $S$ coincidono è troppo. Lo schema linguistico "tutti gli X sono Y" (come "tutti i gatti sono mammiferi") indica un'**inclusione**: $L \subseteq S$. Poiché "di storia" sta per "libri di storia", e i libri di storia sono libri, vale anche $S \subseteq L$, quindi in questo caso gli insiemi coincidono.
> - **Con i quantificatori**: $\forall x\; x \in L \Rightarrow x \in S$, oppure, trasformando gli insiemi in **predicati**,
> $$\forall x\; \mathit{Libro}(x) \Rightarrow \mathit{LibroDiStoria}(x)$$
> e, aggiungendo il verso opposto, $\forall x\; \mathit{Libro}(x) \Leftrightarrow \mathit{LibroDiStoria}(x)$.

> [!example] «I libri nuovi e i libri rari sono molto costosi»
> Si sceglie un vocabolario di predicati, che è un impegno verso un modello concettuale (come uno schema ER):
> - $\mathit{Libro}(x)$;
> - $\mathit{Prezzo}(x, p)$: l'oggetto $x$ ha prezzo $p$. Vale per qualunque cosa si venda, non solo per i libri;
> - $\mathit{Costoso}(x) \equiv \mathit{Prezzo}(x, p) \land p > \text{soglia}$;
> - $\mathit{Pubblicato}(x, d)$: $x$ è stato pubblicato alla data $d$, e $\mathit{Nuovo}(x) \equiv \mathit{Pubblicato}(x, d) \land d > \text{data soglia}$;
> - $\mathit{Raro}(x)$: una proprietà vera o falsa.
>
> La traduzione corretta è
> $$\forall x\; \mathit{Libro}(x) \land \big(\mathit{Nuovo}(x) \lor \mathit{Raro}(x)\big) \Rightarrow \mathit{Costoso}(x)$$
> La "e" della frase è un **inganno linguistico**: non si parla dei libri che sono insieme nuovi e rari, ma di quelli nuovi **e anche** di quelli rari. Basta una delle due proprietà, quindi in logica diventa una **disgiunzione**.

Lo stesso tipo di ambiguità rende vaghi i prompt: se non si specifica se due condizioni valgono insieme o in alternativa, un LLM può interpretare in modo diverso, e a volte bisogna chiederglielo esplicitamente. In IA la scelta dei predicati è la scelta delle proprietà degli stati che si contano per stimare le distanze. Il **modello relazionale** del problema serve anche a estrarre le feature per un sistema di machine learning: logica e machine learning non sono in contrapposizione, perché ogni problema di ML parte da una rappresentazione logica dell'informazione.

> [!example] Esercizio proposto a lezione
> Tradurre in formule le altre frasi dell'esercizio, che il docente pubblica sulla pagina web del corso (tra queste una sui libri di architettura), introducendo tutti i predicati necessari: ad esempio $\mathit{Argomento}(x, \mathit{architettura})$ invece di un predicato diverso per ogni materia. Per "alcuni libri sono rari" si può provare anche una versione **probabilistica**: un libro è raro se la probabilità di trovarlo entrando in una libreria è inferiore all'1%. Se ne riparla nella lezione successiva.

> [!warning] Da verificare
> Dalla registrazione non si ricavano il testo completo delle frasi dell'esercizio né la seconda frase, che il docente dice di aver già discusso: integrare quando l'esercizio sarà sulla pagina del corso.
## Prossimi passi
La prossima lezione chiude la ricerca con gli algoritmi per **ambienti che cambiano**, in cui il piano non si può decidere una volta per tutte come con A\* e va **ripianificato** dinamicamente. L'esercitazione del venerdì successivo è un labirinto con un oggetto in movimento, che costringe l'agente a cambiare direzione e ripianificare a ogni istante.
