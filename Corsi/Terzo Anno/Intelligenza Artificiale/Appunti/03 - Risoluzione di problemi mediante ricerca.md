---
tags:
  - intelligenza-artificiale
  - ricerca
  - problem-solving
  - euristiche
slide:
  - "0030_Search_26_27_v2.1.pdf"
  - "0031_InformedSearch_aa_26_27_v1.2.1.pdf"
  - "0032_AdvancedSearch_26_27_v1.5.pdf"
---
# Risoluzione di problemi mediante ricerca
## Problemi come ricerca nello spazio degli stati
Lezione 3 (12/10/2026): come si trasforma un problema in un problema di ricerca nello spazio degli stati (obiettivo, formulazione, soluzione come piano), i cinque elementi della formulazione, alcuni problemi giocattolo e reali (Romania, aspirapolvere, gioco dell'8, otto regine, dimostrazione di teoremi) e lo schema generale della ricerca ad albero con la frontiera. Riprende l'[[02 - Agenti intelligenti#Agente con obiettivo|agente con obiettivo]] della lezione precedente e corrisponde alla prima parte del capitolo 3 di AIMA. Slide: 0030_Search, pp. 1-31 e 37 (i lucidi del docente sono intitolati "Problem-solving & Ricerca delle soluzioni").
### Le esercitazioni: il codice non basta
> [!info] Cosa conta in una consegna
> Il solo codice dice poco: si può testarlo, ma non spiega **perché** è stato scritto così (copiato, generato da un assistente e accettato dopo due prove, o progettato discutendo con l'IA). Chi rilascia un programma ci mette la firma e deve saperne motivare le scelte. Si chiede quindi di consegnare anche la **discussione** della soluzione, preferibilmente in un **notebook** che alterna codice e commenti, scritto per un "cliente" che conosce la matematica ma non Python; è anche una preparazione all'orale. Secondo il docente, soluzioni corrette senza commenti valgono la sufficienza, notebook ben documentati vanno verso il 27-30 anche con qualche piccolo errore.
### Risolvere problemi come ricerca
Il cuore del lavoro di un agente è il **problem solving**: costruire la soluzione di un problema come **avvicinamento progressivo e incrementale** alla soluzione finale. Ogni passo è una possibile evoluzione della soluzione parziale, e cercare questi stati intermedi significa costruire la soluzione.
- Vincere una partita a scacchi significa trovare una **sequenza di mosse**; ogni mossa dell'avversario cambia lo stato dell'ambiente e la mossa successiva dipende dalle precedenti e dalle nuove condizioni.
- Anche un **LLM** che genera una risposta sta cercando: la risposta è la frase "ottima" per la domanda, costruita con passi discreti (una parola dopo l'altra) scelti nel vocabolario.

Quindi **cercare nei grafi equivale a risolvere problemi**. Il guaio è il costo: le frasi che un LLM può generare crescono esponenzialmente con la lunghezza, con base pari alla dimensione del vocabolario (decine di migliaia di parole). Gran parte dell'IA consiste nel rendere **efficiente** la navigazione di spazi degli stati così grandi.

(Dalle slide, p. 3) Gli agenti risolutori di problemi sono agenti **con modello** che adottano una rappresentazione **atomica** dello stato (vedi [[02 - Agenti intelligenti#Agente con obiettivo|agente con obiettivo]]), e in particolare agenti con obiettivo che **pianificano l'intera sequenza di mosse prima di agire**.
#### Le fasi del problem solving
1. **Formulazione dell'obiettivo**: l'obiettivo è un **sottoinsieme di stati** in cui il problema si considera risolto. Il taxi che da Tor Vergata va a Piazza del Popolo ha finito in qualunque punto della piazza (o al Muro Torto, da cui il cliente entra a piedi).
2. **Formulazione del problema**: si sceglie un linguaggio formale per gli stati (una specifica algebrica, come una tupla relazionale, e una struttura dati in Python o C) e le **azioni**, che portano da uno stato a un altro.
3. **Ricerca della soluzione**: noti stato iniziale e stati obiettivo, si cerca la sequenza di azioni che porta dall'uno agli altri.
4. **Esecuzione**: la sequenza trovata, detta **piano**, viene eseguita.

> [!quote] Soluzione
> Una **soluzione** è una sequenza di azioni che porta dallo stato iniziale a uno stato obiettivo. Una soluzione **ottima** è quella di costo minimo tra tutte le soluzioni.

La concezione del piano è **separata** dalla sua esecuzione: l'agente costruisce la soluzione nella propria memoria, su una rappresentazione interna del mondo, e solo dopo agisce nella realtà un passo alla volta.

> [!info] Domanda a lezione: e se un'azione porta in un vicolo cieco?
> Durante la ricerca l'agente **non si sta muovendo**: allunga un piano immaginario $s_0, \dots, s$ e, se un'aggiunta si rivela un punto senza uscita, la toglie e prova altro. In un **labirinto sconosciuto**, invece, non si può pianificare: si fa un passo, si osserva e si torna indietro fisicamente. È la differenza tra un ambiente **noto e osservabile** e uno che va esplorato.
#### Le ipotesi sull'ambiente
Per ora si assume un ambiente (vedi le [[02 - Agenti intelligenti#Proprietà dell'ambiente|proprietà dell'ambiente]]):
- **statico**: mentre l'agente pianifica il mondo non cambia (la rete stradale di Roma resta quella, salvo eccezioni);
- **osservabile**: l'agente conosce lo stato a ogni passo, quindi sa anche se sta tornando su uno stato già visto (un ciclo);
- **discreto**: gli stati sono enumerabili $s_0, s_1, \dots, s_n$, cioè indicizzabili con i naturali (sulla mappa, ad esempio, gli incroci), e da ogni stato è possibile un **sottoinsieme finito** di azioni (con il Muro Torto a destra non si può girare a destra);
- **deterministico**: in uno stato un'azione ha sempre lo stesso effetto, quindi il piano si può eseguire anche "a occhi chiusi".
### Formulazione di un problema
Un problema di ricerca è definito da cinque elementi.

> [!quote] Problema di ricerca
> 1. **Stato iniziale** $s_0$, descritto nel linguaggio di rappresentazione scelto.
> 2. **Azioni**: per ogni stato $s$, l'insieme $\text{Actions}(s)$ delle azioni applicabili in $s$.
> 3. **Modello di transizione**: la funzione $\text{Result}(s, a) = s'$ che restituisce lo stato raggiunto eseguendo l'azione $a$ nello stato $s$. Lo stato $s'$ si chiama **successore** di $s$.
> 4. **Test obiettivo**: una funzione $\text{Goal-Test}(s) \in \{\text{true}, \text{false}\}$ che dice se $s$ è uno stato obiettivo.
> 5. **Costo del cammino**: la somma dei **costi di passo** $c(s, a, s')$ delle azioni del cammino.
>
> I primi tre elementi definiscono implicitamente lo **spazio degli stati**: un grafo orientato i cui nodi sono stati e i cui archi sono azioni.
#### Il test obiettivo
Il test obiettivo è un'**etichettatura** degli stati: vale *true* sugli stati obiettivo e *false* sugli altri. Esprime la competenza dell'agente nel capire, dalle percezioni, di essere arrivato (a Piazza del Popolo, vedendo la Porta del Popolo o il Pincio).
- A volte gli stati obiettivo si possono **enumerare**: in un calcio "a celle", il goal della squadra 1 è l'unico stato in cui il pallone sta nella cella della porta avversaria.
- Altre volte si definiscono **funzionalmente**: negli scacchi gli stati di scacco matto (il re avversario è sotto scacco e non ha mosse) sono troppi per elencarli, e si usa una funzione che risponde "hai vinto?".
#### Il costo del cammino
Ogni azione, cioè ogni arco, ha un costo strettamente positivo:

$$c(s, a, s') \geq \varepsilon > 0$$

Se un'azione costasse zero si potrebbe ripeterla all'infinito: andare avanti e indietro tra due stanze a costo nullo darebbe infinite soluzioni "ottime". Con un costo minimo $\varepsilon$ ogni azione in più si paga, e la soluzione di costo $c$ si distingue sempre da quella di costo $c + \varepsilon$.

> [!info] Costo della ricerca e costo dell'esecuzione
> Il costo totale per un agente che risolve un problema è la somma di due componenti: il **costo della ricerca** (tempo e memoria per trovare la soluzione) e il **costo del cammino** trovato (quanto costa eseguirlo). Si può trovare velocissimamente una soluzione che costa moltissimo da eseguire, o viceversa: si cerca un compromesso che minimizzi la somma.
### Problemi giocattolo
#### Viaggio in Romania
È il *running example* di AIMA: su una mappa della Romania si deve andare da **Arad** a **Bucarest**. Da Arad sono raggiungibili Sibiu, Timisoara e Zerind.
- **Stati** (dalle slide): le città, ad esempio $\mathit{In}(\mathit{Pitesti})$.
- **Stato iniziale**: $\mathit{In}(\mathit{Arad})$. È una formula logica: un predicato $\mathit{In}$ applicato a una costante, vero per Arad e falso per ogni altra città. Come nelle basi di dati, dove una formula è vera se la tupla è in tabella.
- **Azioni**: $\text{Actions}(\mathit{In}(\mathit{Arad})) = \{\mathit{Go}(\mathit{Sibiu}), \mathit{Go}(\mathit{Timisoara}), \mathit{Go}(\mathit{Zerind})\}$. Un'azione è applicabile solo se appartiene a questo insieme.
- **Modello di transizione**: $\text{Result}(\mathit{In}(\mathit{Arad}), \mathit{Go}(\mathit{Zerind})) = \mathit{In}(\mathit{Zerind})$, in generale $\text{Result}(\mathit{In}(x), \mathit{Go}(y)) = \mathit{In}(y)$.
- **Test obiettivo**: $\mathit{In}(\mathit{Bucarest})$.
- **Costo del cammino**: la somma delle distanze in chilometri.

Lo spazio degli stati coincide con la rete di collegamenti tra le città (dalle slide). L'esempio mostra che per ragionare sugli stati il grafo non basta: serve un **linguaggio** che dica cosa è vero e cosa è falso nel mondo rispetto a ciascun nodo.
#### Il mondo dell'aspirapolvere
È l'[[02 - Agenti intelligenti#Agente reattivo semplice|aspirapolvere]] della lezione precedente, con due stanze. Nelle slide le percezioni sono *Sporco* e *NonSporco* e le azioni Sinistra (L), Destra (R), Aspira (S).
- **Stati**: lo stato è determinato da tre variabili booleane: la posizione dell'aspirapolvere (sinistra o destra) e lo stato di ciascuna stanza (sporca o pulita). Ci sono quindi $2^3 = 8$ stati.
- **Stato iniziale**: uno qualunque degli otto.
- **Azioni**: `Left`, `Right`, `Suck`.
- **Modello di transizione**: `Left` e `Right` spostano l'aspirapolvere (nessun effetto se è già nella stanza più a sinistra o più a destra), `Suck` pulisce la stanza corrente.
- **Test obiettivo**: entrambe le stanze pulite; sono gli stati 7 (aspirapolvere a sinistra) e 8 (a destra).
- **Costo del cammino**: ogni azione costa 1.

Nel grafo degli stati si vedono "livelli" di distanza dalla soluzione: gli stati 1 e 2 (entrambe le stanze sporche), poi quelli con una stanza sporca, infine gli obiettivi. Da uno stato con due stanze sporche, `Suck`, spostamento, `Suck` è una soluzione ottima di tre azioni.
#### Il gioco dell'8
Otto tessere numerate da 1 a 8 su una griglia $3 \times 3$ con una casella vuota; spostando le tessere si deve raggiungere una configurazione ordinata.
- **Stati**: la posizione di ciascuna tessera e della casella vuota (9 simboli, uno per cella: 0 per la vuota). Le disposizioni sono $9! = 362\,880$, di cui solo metà raggiungibili da una data configurazione.
- **Stato iniziale**: una configurazione qualunque, ad esempio dopo aver mescolato le tessere.
- **Azioni**: invece di spostare le tessere (molte mosse diverse per stato), si modella lo spostamento della **casella vuota**: `Left`, `Right`, `Up`, `Down`. Da ogni stato escono al più quattro mosse. Se la casella vuota va su, la tessera sopra di essa scende.
- **Modello di transizione**: lo scambio tra la casella vuota e la tessera adiacente nella direzione scelta.
- **Test obiettivo**: la configurazione ordinata.
- **Costo del cammino**: ogni passo costa 1.

Lo spazio degli stati è un grafo **con cicli**: si torna facilmente su una configurazione già vista.
#### Le otto regine
Si devono disporre otto regine su una scacchiera in modo che nessuna ne attacchi un'altra (stessa riga, colonna o diagonale). Conta solo la configurazione finale, non il cammino, quindi il costo del cammino non interessa (nelle slide vale zero, con la domanda "perché?"). Si vedono più formulazioni.
- **Formulazione incrementale ingenua**: stati come disposizioni di 0-8 regine, stato iniziale la scacchiera vuota, azione "aggiungi una regina in una casella vuota", obiettivo otto regine non sotto attacco. Le sequenze da esaminare sono $64 \cdot 63 \cdots 57 \approx 1{,}8 \times 10^{14}$.
- **Formulazione incrementale migliore**: si aggiunge una regina alla volta nella prima colonna libera (partendo da un lato), in una casella **non attaccata** dalle regine già messe. Lo stato iniziale è la scacchiera vuota; gli stati sono disposizioni di $n \leq 8$ regine, una per colonna nelle prime $n$ colonne, nessuna sotto attacco. Gli stati scendono a **2057** (le slide parlano di "sole 2057 sequenze da considerare").
- **Formulazione a stato completo**: si parte da una scacchiera con una regina per colonna messa a caso e si spostano le regine lungo la propria colonna, cercando di ridurre il numero di coppie che si attaccano. Nelle slide l'azione è "sposta una regina nella sua colonna, se è minacciata". Ogni spostamento è un vantaggio se riduce gli attacchi, uno svantaggio se li aumenta. La si riprende con la ricerca locale.
#### Dimostrazione di teoremi
Anche il ragionamento logico è un problema di ricerca. Dalle tavole di verità si sa che, se $A$ e $A \Rightarrow B$ sono vere, in ogni mondo in cui valgono è vera anche $B$: è il **modus ponens**,

$$\frac{A \qquad A \Rightarrow B}{B}$$

Data una base di conoscenza di fatti semplici e implicazioni, chiedersi se una formula $Q$ è vera significa cercare una sequenza di applicazioni del modus ponens che la derivi.
- **Stati**: insiemi di formule proposizionali (la base di conoscenza corrente).
- **Stato iniziale**: le premesse, cioè le formule considerate vere (l'assiomatizzazione del problema).
- **Azioni**: applicare il modus ponens, che **aggiunge** una formula derivata; ogni formula nuova può renderne applicabili altre.
- **Test obiettivo**: lo stato contiene la formula da dimostrare.

> [!example] Una derivazione (dalle slide, pp. 19-21)
> Premesse $\{s,\ t,\ q \Rightarrow p,\ r \Rightarrow p,\ v \Rightarrow q,\ t \Rightarrow r,\ s \Rightarrow v\}$, formula da dimostrare $p$. Dallo stato iniziale il modus ponens può aggiungere $v$ (da $s$ e $s \Rightarrow v$) oppure $r$ (da $t$ e $t \Rightarrow r$). Nel primo ramo si aggiunge poi $q$ (da $v$ e $v \Rightarrow q$) e infine $p$ (da $q$ e $q \Rightarrow p$); nel secondo ramo basta un passo, $p$ da $r$ e $r \Rightarrow p$. Gli stati che contengono $p$ soddisfano il test obiettivo: nel secondo ramo lo si raggiunge in due applicazioni, nel primo in tre.

> [!warning] Da verificare
> A lezione è stato mostrato un esercizio d'esame del prof. Zanzotto con una base di conoscenza su una slide non ancora pubblicata; dalla registrazione non si riesce a ricostruire l'insieme esatto di formule né la formula da dimostrare. L'esempio qui sopra è quello delle slide del corso (pp. 19-21) e non è detto che coincida con l'esercizio d'esame citato.

Le basi di conoscenza reali (ad esempio i sistemi esperti in medicina) contengono centinaia di formule: trovare la derivazione giusta è come cercare un ago in un pagliaio.

> [!info] Come lavora l'interprete Prolog
> Prolog indicizza i simboli predicativi e le costanti e ragiona **all'indietro**: per soddisfare $P$ cerca le regole $Q \Rightarrow P$ e prende $Q$ come nuovo obiettivo, fino ai fatti.
### Problemi reali
- **Navigazione dei robot**, vista nell'esercitazione del venerdì.
- Altri esempi elencati nelle slide (p. 22, non commentati a lezione): pianificazione di viaggi aerei, problema del commesso viaggiatore, configurazione VLSI, progettazione di proteine, riconoscimento delle categorie grammaticali delle parole in un testo, classificazione tematica di tweet o documenti.
- **Ranking delle risposte di un motore di ricerca**: tra i documenti recuperati si cerca l'ordinamento che mette in prima pagina i più utili. Google non usa solo il PageRank, che è un ingrediente di modelli di machine learning complessi: la ricerca si combina con l'**apprendimento** della funzione di ranking.
### Cercare la soluzione: alberi di ricerca
Si parte dallo stato iniziale e si applicano le azioni: da Arad si generano Sibiu, Timisoara e Zerind, i **successori** candidati all'espansione. La scelta non è indifferente: Zerind porta verso nord-ovest, Sibiu verso est, cioè verso Bucarest, e una ricerca **informata** dovrebbe tenerne conto.

Espandendo ripetutamente i successori si sviluppa un **albero di ricerca**, con lo stato iniziale alla radice. Quando un nodo generato supera il test obiettivo ci si ferma e si ricostruisce la soluzione risalendo l'albero.

> [!info] Domanda a lezione: si minimizza il numero di azioni o il costo?
> Il **costo**. Il piano è costruito in astratto, e ciò che interessa è quanto costerà eseguirlo: un singolo arco tra due città a 1500 km di distanza è un'azione sola, ma costa 1500 km. Le priorità con cui si sceglie quale nodo espandere sono legate al costo, non al numero di passi.
#### La frontiera
> [!quote] Frontiera
> La **frontiera** è l'insieme dei nodi generati ma non ancora espansi, cioè le foglie dell'albero di ricerca in un dato momento. Separa la regione già esplorata dello spazio degli stati da quella inesplorata.

Nell'esempio della Romania, dopo aver espanso Arad e poi Sibiu, la frontiera contiene Timisoara, Zerind, Arad, Fagaras, Oradea e Rimnicu Vilcea. Che Arad ricompaia è un problema: espanderlo di nuovo equivale a ripartire dal via. Bisogna quindi gestire gli **stati ripetuti** (i cicli); per ora si trascurano e si riprendono più avanti.

Lo schema generale della ricerca ad albero:

```pseudo
\begin{algorithm}
\caption{Tree-Search(problem)}
\begin{algorithmic}
\State inizializza la frontiera con lo stato iniziale di $problem$
\Loop
  \If{la frontiera è vuota}
    \State \Return fallimento
  \EndIf
  \State scegli una foglia $n$ e rimuovila dalla frontiera
  \If{$n$ contiene uno stato obiettivo}
    \State \Return la soluzione corrispondente
  \EndIf
  \State espandi $n$ e aggiungi i nodi risultanti alla frontiera
\EndLoop
\end{algorithmic}
\end{algorithm}
```

Se la frontiera si svuota si restituisce il **fallimento**: il problema non è risolubile, ad esempio perché lo stato iniziale e gli obiettivi stanno in due componenti diverse del grafo. Tutto il comportamento dell'algoritmo dipende da **quale** foglia si sceglie, cioè da come si gestisce la frontiera: è la **strategia di ricerca**.
#### Nodi e stati
Un nodo dell'albero di ricerca è una struttura dati (in Python, un oggetto o un dizionario) con quattro componenti:
- $n.\mathit{State}$: lo stato a cui corrisponde il nodo, che fa anche da identificatore (Sibiu, Bucarest, oppure un numero);
- $n.\mathit{Parent}$: il nodo che lo ha generato; risalendo di padre in padre fino alla radice si ricostruisce il cammino. Se uno stato è raggiungibile con più cammini, il padre da tenere è quello del cammino **meno costoso**;
- $n.\mathit{Action}$: l'azione applicata al padre per generarlo;
- $n.\mathit{Path\text{-}Cost}$: il costo del cammino dallo stato iniziale al nodo, indicato con $g(n)$.

La funzione $\text{Child-Node}(problem, parent, action)$ costruisce il figlio: stato $\text{Result}(parent.\mathit{State}, action)$, padre $parent$, azione $action$ e costo $g(parent)$ più il costo del passo.

> [!example] Un nodo del gioco dell'8
> Un nodo ha come stato una configurazione della griglia, come padre il nodo della configurazione precedente e come azione `Right`, perché la casella vuota è stata spostata a destra. Quando si raggiunge la configurazione ordinata, risalendo i padri si ottiene la sequenza delle azioni: il piano da consegnare all'agente per l'esecuzione.

Stato e nodo non sono la stessa cosa: lo stato è una configurazione del mondo, il nodo è un elemento dell'albero di ricerca che tiene traccia di come ci si è arrivati. Più nodi possono contenere lo stesso stato.
#### Strutture dati per la frontiera
La frontiera non è un insieme ma una **lista ordinata**: i nodi vi entrano con proprietà diverse e alcuni vanno trattati prima di altri. Servono tre operazioni: $\text{Empty?}(\mathit{frontier})$, che dice se è vuota (e quindi se restituire il fallimento); $\text{Pop}(\mathit{frontier})$, che estrae il prossimo nodo; $\text{Insert}(n, \mathit{frontier})$, che inserisce un nodo. Secondo come sono realizzate si ha:
- **coda FIFO** (*first in, first out*): si estrae il nodo inserito per primo, si inserisce in coda;
- **pila LIFO** (*last in, first out*): si estrae l'ultimo inserito, come da una pila di monete; si approfondisce un ramo prima di allargarsi agli altri;
- **coda con priorità**: si estrae il nodo con priorità più alta secondo una funzione di valutazione (dopo l'inserimento dei nuovi nodi si riordina). La priorità si può modulare, e sarà la chiave delle strategie più efficaci.

> [!quote] Strategia di ricerca
> La strategia di ricerca è determinata interamente dall'**ordine** in cui i nodi della frontiera vengono estratti, cioè da come vengono inseriti nella frontiera.
#### Ricerca in ampiezza
Con una coda FIFO si ottiene la ricerca in ampiezza (*Breadth-First Search*), che espande i nodi livello per livello. Nelle slide (p. 30) lo stesso pseudocodice è presentato come quiz, "Che tipo di ricerca è?", e riproposto a p. 37 con il nome di ricerca in ampiezza. In questa versione il test obiettivo si fa quando un nodo viene **generato**: se lo stato iniziale è già un obiettivo si restituisce subito, come se all'inizio della partita il pallone fosse già in porta.

```pseudo
\begin{algorithm}
\caption{Breadth-First-Search(problem)}
\begin{algorithmic}
\State $node \gets$ un nodo con $\mathit{State} = problem.\mathit{Initial\text{-}State}$, $\mathit{Path\text{-}Cost} = 0$
\If{\Call{Goal-Test}{$node.\mathit{State}$}}
  \State \Return \Call{Solution}{$node$}
\EndIf
\State $frontier \gets$ coda FIFO con $node$ come unico elemento
\Loop
  \If{\Call{Empty?}{$frontier$}}
    \State \Return fallimento
  \EndIf
  \State $node \gets$ \Call{Pop}{$frontier$}
  \For{$action \in$ \Call{Actions}{$node.\mathit{State}$}}
    \State $child \gets$ \Call{Child-Node}{$problem, node, action$}
    \If{\Call{Goal-Test}{$child.\mathit{State}$}}
      \State \Return \Call{Solution}{$child$}
    \EndIf
    \State $frontier \gets$ \Call{Insert}{$child, frontier$}
  \EndFor
\EndLoop
\end{algorithmic}
\end{algorithm}
```


> [!info] Notazione
> Lo pseudocodice segue AIMA. Ampiezza, profondità e costo uniforme si danno per noti dai corsi di algoritmi.
### Verso la ricerca euristica
La prossima lezione riprende due idee:
- la **ricerca ad approfondimento iterativo**, che combina ampiezza e profondità: si fa una ricerca in profondità con un **limite** sul numero di livelli, aumentandolo a ogni iterazione ($1, 2, 3, \dots$). Così non si diverge scendendo alla cieca, si esplorano tutti i nodi di un livello come in ampiezza e si risparmia la memoria della frontiera;
- le **strategie di ricerca euristica**: si usa come priorità della frontiera una funzione che stima quanto un nodo è **promettente**, cioè dà un punteggio numerico per avvicinarsi al cammino di costo minimo. Inventare buone funzioni euristiche per problemi diversi, da ChatGPT al taxi agli scacchi, è il modo principale per contenere la complessità del grafo generato.

> [!question] Domanda tipica d'esame
> Come si formula un problema di ricerca? Elenca i cinque elementi (stato iniziale, azioni, modello di transizione, test obiettivo, costo del cammino) e applicali a un esempio (Romania, aspirapolvere, gioco dell'8). Perché i costi di passo devono essere maggiori di un $\varepsilon > 0$?

> [!question] Domanda tipica d'esame
> Qual è la differenza tra stato e nodo? Descrivi lo schema generale della ricerca ad albero, il ruolo della frontiera e come la struttura dati scelta (FIFO, LIFO, coda con priorità) determina la strategia di ricerca.
## Ricerca non informata e ricerca euristica
Lezione 4 (14/10/2026): i criteri con cui si valuta una strategia di ricerca (completezza, ottimalità, complessità in tempo e spazio), le strategie non informate (ampiezza, costo uniforme, profondità, profondità limitata e approfondimento iterativo, ricerca bidirezionale), la gestione degli stati ripetuti e l'introduzione alla ricerca euristica: best-first, greedy best-first, A\* e le euristiche del gioco dell'8. Prosegue la [[03 - Risoluzione di problemi mediante ricerca#Verso la ricerca euristica|lezione precedente]] e corrisponde al resto del capitolo 3 di AIMA. Slide: 0030_Search, pp. 32-72 (valutazione e strategie non informate, stati ripetuti, esercizi); 0031_InformedSearch, pp. 3-9, 12-18 e 41-42 (introduzione alla ricerca euristica, greedy, A\*, euristiche del gioco dell'8).
### Valutare una strategia di ricerca
Una strategia di ricerca è definita dall'ordine in cui si estraggono i nodi dalla [[03 - Risoluzione di problemi mediante ricerca#La frontiera|frontiera]]. Per confrontare strategie diverse si usano quattro criteri.

> [!quote] Criteri di valutazione
> - **Completezza**: se una soluzione esiste, l'algoritmo la trova sempre (disponendo di risorse sufficienti).
> - **Ottimalità** (le slide la chiamano anche *ammissibilità*): la prima soluzione trovata è garantita essere di costo minimo.
> - **Complessità in tempo**: quanto tempo serve per trovare la soluzione, misurato come numero di nodi generati.
> - **Complessità in spazio**: quanta memoria serve durante la ricerca, misurata come numero massimo di nodi in memoria.

L'ottimalità riguarda la soluzione che si **eseguirà**; le due complessità riguardano invece la fase **precedente**, quella in cui si cerca. Tempo e spazio sono dimensioni diverse: si può andare più veloci verso la soluzione memorizzando più informazioni, per non ripetere operazioni inutili.

Le complessità si esprimono con tre grandezze:
- $b$, il **fattore di ramificazione**: il numero (medio o massimo) di successori di un nodo;
- $d$, la **profondità** del nodo obiettivo più vicino alla radice;
- $m$, la **lunghezza massima** di un cammino nello spazio degli stati (può essere infinita).

> [!info] Perché in IA l'ottimo è raro
> Nei problemi completamente osservabili e noti, con risorse sufficienti, le garanzie formali sono raggiungibili. In IA succede raramente, per due motivi:
> 1. **non sempre esiste una formulazione matematica dell'ottimo**: per un motore di ricerca, qual è la sequenza ottima di risultati? Ottima per chi, per tutti gli utenti, per chi vive in una certa zona, per chi ha usato certe parole? Spesso non si conosce nemmeno la funzione che descrive il task, e il machine learning serve proprio a costruire funzioni che approssimano quella ottima senza conoscerla;
> 2. **le risorse non bastano**: l'esplosione combinatoria degli stati impedisce di esplorare tutti i casi, quindi si accettano soluzioni **subottime** che siano buone approssimazioni. Anche un decoder che genera una frase stato dopo stato raggiunge una soluzione che può non essere ottima.
>
> Si ragiona quindi su **quanto è buona l'approssimazione** dell'ottimo, più che su come garantirlo.
### Strategie di ricerca non informata
Le strategie **non informate** (o "cieche") usano solo le informazioni della formulazione del problema: sanno generare successori e riconoscere un obiettivo, ma non sanno dire se uno stato non obiettivo è "più promettente" di un altro. Ampiezza e profondità si danno per note dai corsi di algoritmi; qui interessano le loro proprietà come strategie di ricerca.
#### Ricerca in ampiezza
La [[03 - Risoluzione di problemi mediante ricerca#Problemi come ricerca nello spazio degli stati#Ricerca in ampiezza|ricerca in ampiezza]] usa una frontiera **FIFO**: espande prima la radice, poi tutti i suoi successori, poi i successori di questi, livello per livello.

> [!example] Evoluzione della frontiera
> In un albero binario con radice $A$, figli $B$ e $C$, nipoti $D, E$ (di $B$) e $F, G$ (di $C$): si espande $A$ e la frontiera è $[B, C]$; si estrae $B$ e si accodano $D$ ed $E$ **dopo** $C$, quindi la frontiera è $[C, D, E]$; il nodo estratto dopo è $C$, non $D$.

- **Completa**: sì, se $b$ è finito. Si visitano tutti i nodi di un livello prima di passare al successivo, quindi non si può "saltare" una soluzione a profondità $d$.
- **Ottima**: sì, se tutte le azioni hanno lo stesso costo $k$, cioè $g(n) = k \cdot \text{depth}(n)$ (dalle slide). Se la soluzione più vicina è a profondità $d$, non ne esistono a profondità minore (altrimenti sarebbero state trovate prima, essendo entrate prima nella coda). Con costi diversi la soluzione meno profonda non è necessariamente la meno costosa.
- **Tempo**: $b + b^2 + \dots + b^d = O(b^d)$ nodi generati (con il test obiettivo fatto alla generazione).
- **Spazio**: $O(b^d)$, perché la frontiera deve contenere un intero livello.

Il vero limite è la **memoria**. Con $b = 10$, un milione di nodi al secondo e un kilobyte per nodo, a profondità 10 servono ore e terabyte di memoria; a profondità 16 servono anni ed exabyte. In giochi come gli scacchi, o nella guida autonoma, il numero di azioni possibili e la profondità delle soluzioni rendono l'ampiezza inutilizzabile anche su architetture moderne.

> [!example] Tempo e memoria dell'ampiezza (dalle slide, p. 40)
> Con $b = 10$, un milione di nodi generati al secondo e 1000 byte per nodo:
>
> | Profondità | Nodi | Tempo | Memoria |
> |---|---|---|---|
> | 2 | 110 | 0,11 ms | 107 kilobyte |
> | 4 | 11 100 | 11 ms | 10,6 megabyte |
> | 6 | $10^6$ | 1,1 s | 1 gigabyte |
> | 8 | $10^8$ | 2 min | 103 gigabyte |
> | 10 | $10^{10}$ | 3 ore | 10 terabyte |
> | 12 | $10^{12}$ | 13 giorni | 1 petabyte |
> | 14 | $10^{14}$ | 3,5 anni | 10 exabyte |
#### Ricerca a costo uniforme
Se gli archi hanno costi diversi, conviene espandere per primo il nodo raggiunto con il cammino **meno costoso** fin lì: da $S$ con successori $A$, $B$, $C$, se l'arco $S \to A$ costa meno degli altri si parte da $A$. La frontiera diventa una **coda con priorità** ordinata per $g(n)$, il costo del cammino dalla radice a $n$: l'inserimento è ordinato, e il `Pop` restituisce il nodo con $g$ minimo.

Due accorgimenti rispetto all'ampiezza:
- il **test obiettivo** si fa quando un nodo viene **estratto** per l'espansione, non quando viene generato: il primo nodo obiettivo generato potrebbe stare su un cammino più costoso di un altro non ancora scoperto;
- se uno stato già in frontiera viene raggiunto con un cammino **più economico**, si sostituisce il nodo in frontiera con quello nuovo. Se uno stato $G$ è raggiungibile sia da $A$ sia da $B$, si tiene il padre che dà il cammino più breve.

```pseudo
\begin{algorithm}
\caption{Uniform-Cost-Search(problem)}
\begin{algorithmic}
\State $node \gets$ un nodo con $\mathit{State} = problem.\mathit{Initial\text{-}State}$, $\mathit{Path\text{-}Cost} = 0$
\State $frontier \gets$ coda con priorità ordinata per $\mathit{Path\text{-}Cost}$, con $node$ come unico elemento
\State $explored \gets \emptyset$
\Loop
  \If{\Call{Empty?}{$frontier$}}
    \State \Return fallimento
  \EndIf
  \State $node \gets$ \Call{Pop}{$frontier$}
  \If{\Call{Goal-Test}{$node.\mathit{State}$}}
    \State \Return \Call{Solution}{$node$}
  \EndIf
  \State aggiungi $node.\mathit{State}$ a $explored$
  \For{$action \in$ \Call{Actions}{$node.\mathit{State}$}}
    \State $child \gets$ \Call{Child-Node}{$problem, node, action$}
    \If{$child.\mathit{State} \notin explored$ e $child.\mathit{State}$ non è in $frontier$}
      \State $frontier \gets$ \Call{Insert}{$child, frontier$}
    \ElsIf{$child.\mathit{State}$ è in $frontier$ con $\mathit{Path\text{-}Cost}$ maggiore}
      \State sostituisci quel nodo di $frontier$ con $child$
    \EndIf
  \EndFor
\EndLoop
\end{algorithmic}
\end{algorithm}
```

L'insieme $explored$ ricorda gli stati già espansi, per evitare cicli. Il costo $g$ è il **passato**: si usa il cammino già fatto per decidere dove cercare nel futuro.
- **Completa**: sì, se ogni passo costa almeno $\varepsilon > 0$ (vedi il [[03 - Risoluzione di problemi mediante ricerca#Il costo del cammino|costo del cammino]]).
- **Ottima**: sì. I nodi vengono espansi in ordine di $g$ crescente, quindi il primo obiettivo estratto è quello di costo minimo.
- **Tempo e spazio**: $O\big(b^{1 + \lfloor C^*/\varepsilon \rfloor}\big)$, dove $C^*$ è il costo della soluzione ottima. Più gli archi costano poco rispetto a $C^*$, più livelli si esplorano. Con costi tutti uguali si riduce a $O(b^{d+1})$.

È una strategia "golosa" e locale: preferisce i cammini localmente più brevi anche quando non vanno nella direzione giusta. Per andare da Roma a Milano non conviene passare per Frascati solo perché è la città più vicina. Fa quindi esplorazioni inutili, ma la soluzione che restituisce è ottima. Nelle slide (p. 45) $\lfloor C^*/\varepsilon \rfloor$ è il numero di mosse nel caso peggiore;.

> [!info] Le dimostrazioni delle complessità
> Il docente non le dimostra: chiede di ricostruirle sui libri di algoritmica o discutendole con un LLM, e di condividere i prompt migliori.
#### Ricerca in profondità
La ricerca in profondità usa una frontiera **LIFO**: espande sempre il nodo più profondo. Dopo aver espanso $B$ in $D$ ed $E$, invece di passare a $C$ approfondisce $D$, e torna indietro solo quando un ramo è esaurito.
- **Completa**: no. Su spazi infiniti, o con cicli se non si controllano gli stati ripetuti, può scendere all'infinito lungo un ramo senza soluzione.
- **Ottima**: no. Restituisce la prima soluzione che incontra scendendo, che può essere più profonda (e costosa) di un'altra in un ramo non ancora esplorato.
- **Tempo**: $O(b^m)$. Dipende dalla profondità massima $m$, non da quella della soluzione: se $m \gg d$ può cercare troppo a lungo.
- **Spazio**: $O(b\,m)$. In memoria ci sono solo il cammino corrente e, per ogni nodo del cammino, i fratelli non ancora espansi: al più $b$ nodi per ciascuno degli $m$ livelli. La memoria **non cresce esponenzialmente**.

È questo il suo vantaggio: a profondità 16, con le stesse ipotesi di prima, la memoria passa dai 10 exabyte dell'ampiezza a circa 156 kilobyte (dalle slide, p. 50).

> [!warning] Slide e tabella non concordano sulla profondità
> Nella slide 50 la complessità in tempo della profondità è scritta $O(b^{m+1})$ e la memoria "proporzionale a $b\,m + 1$", e $m$ è descritta come "distanza massima della soluzione"; nella tabella di confronto (slide 58) compaiono invece $O(b^m)$ e $O(b\,m)$, con $m$ lunghezza massima dei cammini (la definizione di AIMA, usata in queste note). Si riportano i valori di AIMA e della tabella: la differenza di un livello è irrilevante nell'ordine di grandezza.
#### Profondità limitata e approfondimento iterativo
Un compromesso è la ricerca in profondità con un **limite** $\ell$: i nodi a profondità $\ell$ si trattano come se non avessero successori. Se $\ell < d$ la soluzione non si trova; se $\ell$ è molto più grande di $d$ si torna ai difetti della profondità. Un limite superiore alla profondità della soluzione a volte si conosce: nel route-finding, ad esempio, è il numero di città meno 1 (dalle slide, p. 51). Con tempo $O(b^\ell)$ e spazio $O(b\,\ell)$ la ricerca non è ottima.

> [!warning] Completezza della profondità limitata
> Una versione precedente di queste note la dava "non completa". Le slide (pp. 51 e 58) la dichiarano invece **completa** per i problemi in cui si conosce un limite superiore alla profondità della soluzione, quindi se $\ell \geq d$ (le slide scrivono $\ell > d$; con $\ell = d$ la soluzione è comunque raggiunta). Per $\ell < d$ non lo è. La slide 51 scrive anche spazio $O(b^\ell)$, ma la tabella (slide 58) e AIMA riportano $O(b\,\ell)$, che è il valore corretto per una visita in profondità.

La **ricerca ad approfondimento iterativo** (*iterative deepening*) risolve il problema della scelta di $\ell$: esegue la ricerca a profondità limitata con $\ell = 0, 1, 2, \dots$ finché non trova una soluzione.

```pseudo
\begin{algorithm}
\caption{Iterative-Deepening-Search(problem)}
\begin{algorithmic}
\For{$\ell = 0, 1, 2, \dots$}
  \State $result \gets$ \Call{Depth-Limited-Search}{$problem, \ell$}
  \If{$result \neq$ cutoff}
    \State \Return $result$
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!example] Le prime iterazioni
> Con $\ell = 0$ si controlla solo $A$. Con $\ell = 1$ si generano $B$ e $C$, ma non si può scendere oltre: è come una visita in ampiezza del primo livello. Con $\ell = 2$ si riparte da $A$ in profondità: $B$ viene espanso in $D$ ed $E$, che si controllano **prima** di $C$, come in profondità; $C$ si espande solo se $D$ ed $E$ non portano alla soluzione.

Combina i vantaggi delle due visite: la frontiera resta piccola come in profondità e cresce solo se la soluzione è lontana, mentre l'esplorazione per livelli la rende completa come l'ampiezza.
- **Completa**: sì, se $b$ è finito: quando $\ell$ raggiunge $d$ la soluzione viene trovata, purché la memoria basti.
- **Ottima**: sì se le azioni hanno tutte lo stesso costo, come l'ampiezza.
- **Spazio**: $O(b\,d)$.
- **Tempo**: $O(b^d)$. I livelli vicini alla radice vengono rigenerati a ogni iterazione, ma il costo resta dominato dall'ultimo livello:

$$N(\text{IDS}) = d\,b + (d-1)\,b^2 + \dots + 1 \cdot b^d = O(b^d)$$

Con $b = 10$ e $d = 5$ si generano $50 + 400 + 3000 + 20\,000 + 100\,000 = 123\,450$ nodi contro i $111\,110$ dell'ampiezza (ricalcolati): lo spreco è piccolo, perché la maggior parte dei nodi sta comunque nell'ultimo livello. Le slide (p. 53) la definiscono il **miglior compromesso** tra ampiezza e profondità.

> [!warning] Da verificare
> A lezione l'approfondimento iterativo è stato detto "non ottimo". Le slide (pp. 53, 58 e 71) e AIMA lo danno invece ottimo con costi di passo tutti uguali (la tabella di p. 58 ha la nota (\*) "se gli operatori hanno tutti lo stesso costo"), e non ottimo in generale con costi diversi. Qui si riporta questa versione.
#### Ricerca bidirezionale
Un problema si può risolvere **in avanti**, dallo stato iniziale verso l'obiettivo (ricerca guidata dai dati), oppure **all'indietro**, dall'obiettivo verso lo stato iniziale (ricerca guidata dall'obiettivo): si immaginano gli stati da cui l'obiettivo è raggiungibile, e se si ritrova $s_0$ si è ricostruito il cammino al contrario.

> [!example] Le dimostrazioni per assurdo
> In analisi, per dimostrare l'unicità del limite si suppone che ci siano due limiti $L_1 \neq L_2$ e si arriva a contraddire un'ipotesi: si parte dalla negazione della tesi e si ragiona all'indietro.

Quale direzione conviene dipende dalla **struttura dello spazio di ricerca**: conviene procedere nella direzione in cui il fattore di ramificazione è **minore** (dalle slide, p. 55). Se attorno all'obiettivo ci sono pochi stati e attorno al punto di partenza moltissimi, andare all'indietro è più rapido. Nella dimostrazione automatica di teoremi (pochi dati, molte regole) si procede di solito all'indietro, come fa l'[[03 - Risoluzione di problemi mediante ricerca#Dimostrazione di teoremi|interprete Prolog]]; nella progettazione di un circuito o nella pianificazione di un robot esploratore si procede in avanti.

> [!info] Quando all'indietro e quando in avanti (dalle slide, p. 55)
> - **All'indietro** quando l'obiettivo è chiaramente definito (ad esempio nel theorem proving) o si può formulare un numero limitato di ipotesi, e quando i dati del problema non sono noti e la loro acquisizione può essere guidata dall'obiettivo.
> - **In avanti** quando gli obiettivi possibili sono molti (design, planning) e si dispone di dati da cui partire (la funzione di costo).

La **ricerca bidirezionale** esegue le due ricerche insieme, con due frontiere, e si ferma quando le frontiere si **intersecano**: lo stato in comune collega il cammino in avanti da $s_0$ e quello all'indietro dall'obiettivo. Ciascuna ricerca arriva solo a metà profondità, quindi

$$b^{d/2} + b^{d/2} \ll b^d$$

Il test di intersezione costa tempo costante con una tabella hash, e in memoria devono stare almeno tutti i nodi di una direzione (ad esempio usando l'ampiezza): tempo e spazio sono $O(b^{d/2})$. Serve però saper calcolare i **predecessori** di uno stato, e l'obiettivo deve essere esplicito (con un test obiettivo solo funzionale, come lo scacco matto, o con troppi stati obiettivo, è difficile partire dal fondo).
#### Confronto tra le strategie
| Criterio | Ampiezza | Costo uniforme | Profondità | Profondità limitata | Approfondimento iterativo | Bidirezionale |
|---|---|---|---|---|---|---|
| Completa | sì¹ | sì¹ ² | no | sì⁵ | sì¹ | sì¹ ⁴ |
| Ottima | sì³ | sì | no | no | sì³ | sì³ ⁴ |
| Tempo | $O(b^d)$ | $O(b^{1+\lfloor C^*/\varepsilon \rfloor})$ | $O(b^m)$ | $O(b^\ell)$ | $O(b^d)$ | $O(b^{d/2})$ |
| Spazio | $O(b^d)$ | $O(b^{1+\lfloor C^*/\varepsilon \rfloor})$ | $O(b\,m)$ | $O(b\,\ell)$ | $O(b\,d)$ | $O(b^{d/2})$ |

¹ se $b$ è finito; ² se ogni passo costa almeno $\varepsilon > 0$; ³ se i passi hanno tutti lo stesso costo; ⁴ se in entrambe le direzioni si usa l'ampiezza; ⁵ se si conosce un limite alla profondità della soluzione e $\ell \geq d$.

> [!question] Domanda tipica d'esame
> Il docente ha detto esplicitamente che all'orale chiederà di discutere questa tabella. Per ogni casella si deve saper spiegare il perché: ad esempio, perché la ricerca in profondità non è ottima o non è completa. Per negare una proprietà basta un **controesempio**: un albero in cui la profondità trova prima una soluzione più profonda di un'altra, o un ramo infinito da cui non esce.

> [!info] Esercizi proposti nelle slide (p. 72)
> Dalle slide, non visti a lezione: formulare come problemi di ricerca (con la quintupla $\langle S, A, T, G, C\rangle$) task tipici dell'IA (guida autonoma, aspirapolvere in più stanze, gioco dell'8, motore di ricerca), calcolare la dimensione dello spazio degli stati, confrontare ampiezza, profondità e approfondimento iterativo e discutere l'origine della complessità; dimostrare le proprietà delle slide 51 e 57 (profondità limitata e ricerca bidirezionale), da soli o discutendole con un LLM e registrando la discussione. Coincide con l'invito del docente a ricostruire le [[03 - Risoluzione di problemi mediante ricerca#Ricerca a costo uniforme|dimostrazioni delle complessità]].
### Stati ripetuti
Se lo spazio degli stati non è un albero ma un grafo, la ricerca ad albero può ripetere gli stessi stati: per i cicli (in profondità può non terminare) o semplicemente perché lo stesso stato è raggiungibile con cammini diversi, e l'albero di ricerca si riempie di duplicati. Tre rimedi, dal più economico al più completo:
1. non tornare nello stato da cui si proviene (non generare il padre come successore);
2. non generare successori che siano **antenati** del nodo, cioè controllare il cammino dalla radice (evita i cicli);
3. non generare stati **già visitati**: si ricorda ogni stato espanso in una struttura con accesso rapido, tipicamente una **tabella hash**, e lo si scarta se ricompare. È l'insieme $explored$ della ricerca a costo uniforme. Costa memoria $O(s)$, con $s$ il numero di stati possibili.

Dalle slide (pp. 59-65): i cammini ciclici rendono infiniti gli alberi di ricerca, e le ridondanze compaiono anche senza cicli (ad esempio nelle griglie). C'è un compromesso tra spazio e tempo: ricordare gli stati visitati occupa spazio ma evita lavoro inutile, e "gli algoritmi che dimenticano la propria storia sono destinati a ripeterla". La **ricerca su grafi** mantiene la lista dei nodi visitati (lista chiusa) e non espande un nodo il cui stato è già stato incontrato; è ottima solo se il nuovo cammino non costa più di quello già trovato. Le slide (pp. 67-68) danno le versioni su grafo di ampiezza (il figlio si inserisce solo se il suo stato non è né in $explored$ né in frontiera) e di costo uniforme (la stessa del [[03 - Risoluzione di problemi mediante ricerca#Ricerca a costo uniforme|pseudocodice sopra]]).

> [!info] Programma
> Le varianti per i grafi (*graph search*) sono state presentate come facoltative e non fanno parte del programma d'esame.
### Ricerca euristica
Una strategia **informata** usa conoscenza specifica del problema, oltre alla sua definizione, per capire quali successori sono più **promettenti** verso l'obiettivo. Anche un LLM, mentre genera una frase un pezzo alla volta, non procede a caso: sa che la frase finale deve avere certe caratteristiche e orienta la ricerca verso di essa. Le slide (0031, p. 3) precisano che la conoscenza euristica (dal greco "eureka") **non evita la ricerca ma la riduce**, consente in genere di trovare una buona soluzione in tempi accettabili e, sotto certe condizioni, garantisce completezza e ottimalità.
#### Best-first e funzione di valutazione
Nella ricerca **best-first** si usa lo schema della ricerca a costo uniforme, ma la priorità della frontiera è data da una **funzione di valutazione** $f(n)$, e si espande il nodo con $f$ migliore.
- Se $f$ misura un vantaggio (quanto è buona, utile, elegante la soluzione), va **massimizzata**.
- Se $f$ è un costo, come una distanza dall'obiettivo, va **minimizzata**. È il caso usuale.

La ricerca a costo uniforme è il caso $f(n) = g(n)$. Nelle slide (p. 5) la funzione di valutazione è $f : n \to \mathbb{R}$: si applica al nodo ma dipende solo dallo stato $n.\mathit{State}$; è implementata da una coda con priorità.

> [!quote] Funzione euristica
> Una **funzione euristica** $h(n)$ stima il costo del cammino più economico dallo stato del nodo $n$ a uno stato obiettivo. Dipende dal problema, e vale $h(n) = 0$ se $n$ è un nodo obiettivo.

$g(n)$ è **nota**: durante la ricerca si sa esattamente quanto è costato arrivare a $n$. $h(n)$ è un'**ipotesi** sul futuro, una legge inventata per approssimare una verità che non si conosce (se si conoscesse il costo esatto verso l'obiettivo, il problema sarebbe già risolto). Il nome viene dalla stessa idea del machine learning, dove $h$ è l'ipotesi con cui si approssima una funzione sconosciuta a partire dai dati.

> [!example] Euristiche
> - **Navigazione stradale**: la distanza **in linea d'aria** dalla destinazione. Per andare da Roma a Milano, una città a sud come Frascati ha distanza maggiore di una a nord, come Civitavecchia. Non serve conoscere tutta la rete stradale: bastano le coordinate geografiche. È una **sottostima** del costo vero, perché raramente c'è una strada in linea retta.
> - **Gioco dell'8**: il numero di tessere fuori posto.
> - **Scacchi**: il numero di pezzi avversari che si mettono sotto scacco (le slide, p. 6, indicano invece il vantaggio in pezzi nella dama o negli scacchi).
>
> Sono imprecise come il passante che, a chi chiede il distributore, risponde "è avanti un paio di chilometri": dice la direzione giusta, ma i chilometri magari sono otto.
#### Greedy best-first
La ricerca **greedy best-first** usa $f(n) = h(n)$: dimentica il passato e sceglie il nodo che **sembra** più vicino all'obiettivo.

> [!example] Da Arad a Bucarest
> Con $h$ = distanza in linea d'aria da Bucarest, la greedy best-first va Arad → Sibiu → Fagaras → Bucarest (450 km), mentre il cammino ottimo è Arad → Sibiu → Rimnicu Vilcea → Pitesti → Bucarest (418 km). Fagaras sembra più vicina all'obiettivo, ma la strada da lì costa di più.

Non è quindi ottima (e, senza controllo degli stati ripetuti, nemmeno completa: le slide, p. 17, mostrano il percorso da Iasi a Fagaras, in cui la greedy ha una "falsa partenza" o cicla); ma l'idea di guardare **in avanti** è buona e riduce molto l'esplorazione.

> [!info] Terminologia
> A lezione la ricerca a costo uniforme è stata chiamata anche "best-first" e la variante con $h$ "greedy best-first". In AIMA *best-first* è lo schema generale con una qualunque $f$; costo uniforme ($f = g$) e greedy ($f = h$) ne sono casi particolari.
#### A\*
L'idea degli algoritmi ottimi è combinare passato e futuro:

$$f(n) = g(n) + h(n)$$

cioè il costo stimato della migliore soluzione che passa per $n$: quanto è costato arrivare fin lì più quanto si spera manchi. L'idea, secondo le slide (0031, p. 18), è evitare di espandere cammini che siano già costosi. L'algoritmo è identico alla ricerca a costo uniforme (coda con priorità, controllo all'inserimento in frontiera, insieme degli stati esplorati); cambia solo $f$. Con una **buona euristica** questo algoritmo, detto **A\***, è **completo e ottimo**: con costi positivi, $f$ cresce lungo i cammini e il primo obiettivo estratto è quello di costo minimo. Le condizioni su $h$ si vedono nella prossima lezione.

> [!example] Labirinto
> In una simulazione su un labirinto di circa $40 \times 40$ celle (fattore di ramificazione 4), A\* visita solo una piccola parte delle celle che esplorerebbe una ricerca cieca. È lo stesso tipo di problema dell'esercitazione: il piano si calcola prima di muovere il robot.

> [!info] Il riconoscimento del parlato come ricerca
> In un dizionario, i successori di un fonema sono migliaia invece di 4, e una frase di poche decine di parole è fatta di molte decine di fonemi, senza silenzi che separano le parole: bisogna anche decidere dove segmentare. Un assistente vocale che non sa in che lingua si parla combina la probabilità della lingua e quella dei fonemi. È una ricerca in cui l'euristica è la **probabilità di una stringa in una lingua**, stimata ad esempio con i bigrammi di fonemi.
#### Euristiche per il gioco dell'8
Per il [[03 - Risoluzione di problemi mediante ricerca#Il gioco dell'8|gioco dell'8]] si usano due euristiche classiche:
- $h_1$, il **numero di tessere fuori posto**. Si calcola facilmente, vale 0 solo nella configurazione obiettivo, e dice almeno quante mosse servono: ogni tessera fuori posto va mossa almeno una volta;
- $h_2$, la **distanza di Manhattan**: la somma, su tutte le tessere, del numero di righe e colonne che separano ciascuna dalla sua posizione finale.

> [!example] Lo stato iniziale di AIMA
> Nello stato iniziale dell'esempio del libro nessuna tessera è al suo posto, quindi $h_1 = 8$. Sommando le distanze di Manhattan delle otto tessere (nelle slide, p. 42: $3+1+2+2+2+3+3+2$) si ottiene $h_2 = 18$ (ricalcolato: la somma è 18). A p. 23 un altro esempio usa $f = \#\text{mosse fatte} + \#\text{caselle fuori posto}$, con $f(\text{Start}) = 0 + 7$ e, dopo quattro mosse, $f = 4 + 7$.

$h_2$ è sempre maggiore o uguale a $h_1$, quindi stima il costo vero in modo più preciso, distingue meglio tra continuazioni diverse e porta prima alla soluzione ottima.

> [!warning] Da verificare
> A lezione $h_2$ è stata descritta come una "sovrastima" del costo. Entrambe le euristiche sono in realtà **sottostime** del numero reale di mosse (le slide, p. 41, le presentano sotto il titolo "Euristiche ammissibili"): $h_2$ è solo più vicina al valore vero. Se ne riparlerà nella lezione sulle proprietà delle euristiche.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra ricerca a costo uniforme, greedy best-first e A\*? Spiega il ruolo di $g(n)$ e di $h(n)$, mostra con l'esempio della Romania perché la greedy best-first non è ottima, e proponi un'euristica per il gioco dell'8.
## Algoritmo A* e funzioni euristiche
Lezione 5 (19/10/2026): si chiude la famiglia di algoritmi di [[03 - Risoluzione di problemi mediante ricerca#Ricerca euristica|ricerca euristica]] con le proprietà di A\*: euristiche ammissibili e consistenti, completezza, ottimalità e consumo di memoria, con le varianti a memoria limitata. Poi si discute come confrontare e come costruire le euristiche (dominanza, fattore di ramificazione effettivo, problemi rilassati, pattern database, apprendimento). Si chiude con un primo esercizio di traduzione di frasi italiane in formule logiche, che prepara la parte del corso sulla conoscenza ([[04 - Agenti basati sulla conoscenza#Dal linguaggio alla logica]]). Slide: 0031_InformedSearch, pp. 22-82 (pp. 46-63 e 84-88 solo in parte o non visti a lezione).
### Le esercitazioni: confrontare le euristiche
Nell'ultima esercitazione (un labirinto) la prima euristica che viene in mente, la **distanza di Manhattan**, basta già a risolvere il problema. Chi finisce presto è invitato a **confrontare euristiche diverse**: ad esempio la distanza **euclidea**, più vicina al costo vero e applicabile anche in spazi non discreti (su una mappa geografica Manhattan è meno naturale). Il confronto interessante riguarda la **memoria occupata** e il **numero di operazioni** necessarie per arrivare alla soluzione.
### A*
Si riprende l'algoritmo introdotto nella lezione precedente: una ricerca con coda con priorità ordinata per

$$f(n) = g(n) + h(n)$$

dove $g(n)$ è il costo, noto, del cammino dalla radice a $n$ e $h(n) \geq 0$ è la stima del costo da $n$ all'obiettivo. Con $h = 0$ si torna alla [[03 - Risoluzione di problemi mediante ricerca#Ricerca a costo uniforme|ricerca a costo uniforme]]; con $h > 0$ si possono ordinare meglio le alternative. Sugli stati obiettivo deve valere $h = 0$.

> [!quote] Algoritmo A (dalle slide, p. 22)
> Un **algoritmo A** è un algoritmo best-first con funzione di valutazione $f(n) = g(n) + h(n)$, con $h(n) \geq 0$ e $h(\text{goal}) = 0$. Casi particolari: con $h(n) = 0$ si ha la ricerca a costo uniforme, con $g(n) = 0$ la greedy best-first.

> [!example] A* sulla Romania
> Con $h$ = distanza in linea d'aria da Bucarest (Arad 366, Sibiu 253, Fagaras 176, Rimnicu Vilcea 193, Pitesti 100), da Arad si generano Sibiu, Timisoara e Zerind. Sibiu ha $f = 140 + 253 = 393$, il valore migliore, anche se costa qualche chilometro: è una strada nella direzione giusta. Da Sibiu si generano Arad, Fagaras, Oradea e Rimnicu Vilcea, e si espande Rimnicu Vilcea ($f = 220 + 193 = 413$). Fagaras resta competitiva e viene espansa, e genera Bucarest con $f = 450$. Ma Pitesti ($f = 317 + 100 = 417$) è ancora più promettente, e da lì si raggiunge Bucarest con $f = 418$. Il nodo obiettivo con $f = 450$ resta in frontiera e non viene mai estratto: A\* restituisce il cammino ottimo da 418 km.

Perché l'ordinamento della coda abbia senso, $g$ e $h$ devono **significare qualcosa** per il problema: $h$ deve essere un'informazione vera sulla distanza dall'obiettivo, e i costi delle azioni devono essere **non nulli**. Se un'azione sbagliata non costa niente, si possono commettere errori all'infinito senza che la coda lo registri, come chi fa clic mille volte su un sistema bloccato invece di fermarsi.
#### Completezza
Serve che il costo degli archi non possa diventare arbitrariamente piccolo: deve esistere $\varepsilon > 0$ con $c(n, a, n') \geq \varepsilon$ (vedi il [[03 - Risoluzione di problemi mediante ricerca#Il costo del cammino|costo del cammino]]). Se i costi si dividessero per 10 a ogni passo, la loro somma convergerebbe a un valore finito anche lungo un cammino infinito, e la coda resterebbe "ferma" su quel cammino. Con il limite $\varepsilon$, invece, $g$ cresce senza limite lungo ogni cammino infinito. Nelle slide (p. 30) il teorema chiede $g(n) \geq d(n) \cdot \varepsilon$, con $d(n)$ profondità del nodo e $\varepsilon > 0$ costo minimo di un arco: sono escluse le situazioni "strane" come costi $0{,}9,\ 0{,}09,\ 0{,}009, \dots$.

L'idea della dimostrazione: sia $n_0, n_1, \dots, n_k$ un cammino ottimo verso l'obiettivo $n_k$, e sia $n^*$ il primo nodo del cammino che sta in frontiera. I nodi con $f$ minore di quello di $n^*$ sono in numero **finito** (lo garantiscono $\varepsilon$ e un fattore di ramificazione finito), quindi dopo un numero finito di espansioni tocca a $n^*$. Espanderlo mette in frontiera il suo successore sul cammino, e per lo stesso motivo anche quello verrà espanso. Per induzione lungo il cammino si arriva a $n_k$: se una soluzione esiste, A\* la trova. Le slide (p. 36) precisano: completo a meno che non vi sia un numero infinito di nodi con $f \leq f(G)$.
#### Ammissibilità e ottimalità
Non basta trovare **una** soluzione: si vuole che la prima trovata sia la **migliore**. Si confronta $h$ con l'euristica ideale.

> [!quote] Euristica perfetta
> $h^*(n)$ è il costo **esatto** del cammino minimo da $n$ a un obiettivo, e $f^*(n) = g(n) + h^*(n)$ è il costo della migliore soluzione vincolata a passare per $n$, se $g(n)$ è il costo del cammino minimo fino a $n$.

$h^*$ è un'astrazione matematica: se la si conoscesse si avrebbe un algoritmo in forma chiusa e non servirebbe cercare. Il gioco dell'IA è **approssimarla bene**. Perché $g$ sia quello del cammino minimo, quando un nodo entra in frontiera deve puntare al padre da cui lo si raggiunge nel modo **più conveniente**.

> [!quote] Euristica ammissibile
> Un'euristica $h$ è **ammissibile** se non sovrastima mai il costo per raggiungere l'obiettivo:
> $$0 \leq h(n) \leq h^*(n) \quad \text{per ogni } n$$
> Un algoritmo A con euristica ammissibile si chiama **A\***. Le slide (p. 33) enunciano il teorema "gli algoritmi A\* sono ottimali" e il corollario che ampiezza e costo uniforme lo sono ($h = 0$ è ammissibile).

Le euristiche viste finora sono ammissibili: la distanza in linea d'aria non può superare quella stradale, perché il segmento è il cammino più breve possibile; la distanza di Manhattan su una griglia non può superare il numero di passi effettivi in un labirinto con muri. Con un'euristica ammissibile, il primo nodo obiettivo estratto dalla coda è anche quello di costo minimo.

> [!info] Osservazioni sulle sottostime (dalle slide, p. 37)
> 1. Una sottostima può far compiere lavoro inutile, ma non fa perdere il cammino migliore.
> 2. La componente $g$ fa abbandonare i cammini che vanno troppo in profondità.
> 3. Una funzione che qualche volta sovrastima può far perdere la soluzione ottima.

> [!info] Domanda a lezione: e se $h$ sovrastima?
> L'algoritmo trova comunque una soluzione, ma è solo un algoritmo A e la soluzione **può non essere ottima**. Una sovrastima sbagliata su un nodo può invertire l'ordine di due soluzioni nella coda: l'informazione non è più correlata con il problema. Se tutte le stime fossero sbagliate dello **stesso** fattore basterebbe riscalarle, ma per farlo bisognerebbe conoscere lo spazio degli stati. Nei problemi geometrici è facile restare ammissibili; in spazi come quello delle parole che un LLM può scegliere, $h$ è spesso stimata brutalmente dai dati.
#### Consistenza
L'ammissibilità basta quando lo spazio di ricerca è un **albero**. Su un **grafo**, dove si scartano gli stati già esplorati, serve una condizione più forte.

> [!quote] Euristica consistente (monotona)
> Un'euristica $h$ è **consistente** se per ogni nodo $n$ e ogni successore $n'$ generato con l'azione $a$:
> $$h(n) \leq c(n, a, n') + h(n')$$
> e $h(G) = 0$ per ogni obiettivo $G$.

È una **disuguaglianza triangolare**: la stima da $n$ non può superare il costo di un passo verso $n'$ più la stima da $n'$, quindi la stima non può "crollare" passando a un nodo intermedio. Ne segue che $f$ è **non decrescente** lungo ogni cammino:

$$f(n') = g(n) + c(n, a, n') + h(n') \geq g(n) + h(n) = f(n)$$

Ogni euristica consistente è anche ammissibile (teorema delle slide, p. 40); esistono euristiche ammissibili non consistenti, ma sono rare. Con un'euristica consistente, e l'insieme degli stati già esplorati che evita i cicli, A\* è ottimo anche sui grafi: i nodi vengono espansi in ordine di $f$ non decrescente, quindi il primo obiettivo che emerge è il meno costoso. Le slide (p. 43) lo dimostrano in due passi: (1) con la consistenza $f$ non decresce lungo i cammini, sommando $g(n)$ a entrambi i membri di $h(n) \leq c(n,a,n') + h(n')$ e usando $g(n) + c(n,a,n') = g(n')$; (2) ogni volta che A\* seleziona un nodo per l'espansione, il cammino ottimo verso quel nodo è già stato trovato, altrimenti ci sarebbe sulla frontiera un nodo $n'$ del cammino ottimo con $f$ minore, che sarebbe già stato espanso.
#### Contorni e bilancio
Poiché $f$ è non decrescente, A\* espande i nodi per **contorni** di $f$ crescente attorno allo stato iniziale, come le curve di livello di una mappa. Se $C^*$ è il costo ottimo, A\* espande tutti i nodi con $f(n) < C^*$, alcuni con $f(n) = C^*$ e nessuno con $f(n) > C^*$: questi ultimi vengono **potati**. Con euristiche migliori i contorni si allungano verso l'obiettivo invece di allargarsi in cerchio.

> [!quote] Proprietà di A*
> - **Completo**, se il fattore di ramificazione è finito e i costi sono almeno $\varepsilon > 0$.
> - **Ottimo**, con euristica ammissibile (alberi) o consistente (grafi).
> - **Ottimamente efficiente**: tra gli algoritmi che usano la stessa euristica ed estendono cammini dalla radice, nessuno garantisce l'ottimo espandendo meno nodi.
> - **Tempo** esponenziale nel caso peggiore, con una base che dipende dalla qualità di $h$.
> - **Spazio** esponenziale: mantiene tutti i nodi in memoria (nelle slide, p. 45, $O(b^{d+1})$). È il vero limite.

A\* è un buon compromesso tra l'avidità di chi guarda in avanti ($h$) e la memoria del cammino già fatto ($g$). Il suo problema è la memoria: tiene la frontiera, che in un labirinto $1000 \times 1000$ contiene moltissimi nodi, e anche tutti gli stati già esplorati (i nodi "rossi" delle animazioni).
#### Varianti a memoria limitata
- **IDA\*** (*iterative deepening A\**): come l'[[03 - Risoluzione di problemi mediante ricerca#Profondità limitata e approfondimento iterativo|approfondimento iterativo]], ma il limite (*f-limit*) è sul valore di $f$ invece che sulla profondità. A ogni iterazione si espandono i cammini entro la soglia corrente, e la si alza solo quanto serve. Non si memorizza la storia dell'intera ricerca. Dalle slide (pp. 55-58): con costi costanti $k$ il limite cresce di $k$; con costi variabili cresce almeno del costo minimo degli archi $\varepsilon$, oppure si fissa al **minimo $f$ tra i nodi scartati** all'iterazione precedente. È completo e ottimo in questi casi, con memoria $O(b\,d)$ come la profondità.
- **A\* a memoria limitata** (*memory-bounded*, ad esempio SMA\*): si esegue A\* finché la memoria basta. Quando la frontiera supera il budget, si **eliminano i nodi peggiori** in fondo alla coda con priorità e si tengono i più promettenti. Nelle slide (p. 62) SMA\* (*Simplified Memory-bounded A\**) dimentica il nodo peggiore **dopo aver aggiornato il valore del padre**; a parità di $f$ sceglie il nodo migliore più recente e dimentica il peggiore più vecchio; è ottimo se il cammino soluzione sta in memoria.
- **Beam search**: si tiene sempre solo un numero fissato $k$ di nodi migliori. La ricerca diventa guidata dal limite di memoria più che dalla garanzia di ottimalità. Non è completa (slide, p. 47); $k$ è l'ampiezza del raggio (*beam*). La beam search come ricerca locale è ripresa nella [[03 - Risoluzione di problemi mediante ricerca#Beam search locale|lezione 6]].
- **Best-first ricorsiva** (RBFS), dalle slide (pp. 59-61), non vista a lezione: simile a una profondità ricorsiva che usa meno memoria facendo più lavoro. Tiene traccia a ogni livello del migliore percorso alternativo e, invece di fare backtracking al fallimento, interrompe l'esplorazione quando trova un nodo meno promettente secondo $f$ (limite $f$ = minimo tra il limite corrente e il valore dell'alternativa); tornando indietro ricorda il miglior nodo trovato nel sottoalbero, per poterci eventualmente ritornare.

Le slide (p. 63) avvertono che con memoria limitata (IDA\*, SMA\*) si può compiere molto lavoro inutile, che il tempo effettivo è difficile da stimare e che la limitazione può rendere un problema intrattabile.

Dalle slide (pp. 52-54, non viste a lezione), la beam search si applica ai compiti di trasduzione *sequence-to-sequence* (decodifica di sequenze), come il riconoscimento del parlato e la traduzione automatica; è lo stesso schema dell'[[03 - Risoluzione di problemi mediante ricerca#Beam search locale|esempio sul parlato]]. Anche la modalità con $w = 2$ e $w = 3$ è mostrata con esempi alle pp. 50-51.

> [!question] Domanda tipica d'esame
> Quando A\* è completo e quando è ottimo? Definisci euristica ammissibile ed euristica consistente, spiega perché la consistenza implica che $f$ sia non decrescente lungo i cammini, e mostra con un esempio cosa succede se $h$ sovrastima.
### Qualità di un'euristica
#### Dominanza
Con $h = 0$ l'algoritmo guarda solo i cammini già fatti e non guarda avanti; con $h = h^*$ va dritto alla soluzione. Ogni euristica ammissibile sta **in mezzo**, e conviene quella più vicina a $h^*$.

> [!quote] Dominanza
> Se $h_1$ e $h_2$ sono ammissibili e $h_2(n) \geq h_1(n)$ per ogni $n$, si dice che $h_2$ **domina** $h_1$. A\* con $h_2$ non espande mai più nodi di A\* con $h_1$ (a parità di gestione dei pareggi): i nodi espansi con $h_2$ sono un sottoinsieme di quelli espansi con $h_1$ (teorema delle slide, p. 65). In generale $0 \leq h(n) \leq h^*(n)$, con $h = 0$ minimo di informazione e $h^*$ massimo (oracolo).

Nel [[03 - Risoluzione di problemi mediante ricerca#Euristiche per il gioco dell'8|gioco dell'8]], $h_1$ conta le tessere fuori posto e $h_2$ somma le distanze di Manhattan. Una tessera fuori posto contribuisce 1 a $h_1$ e almeno 1 a $h_2$, quindi $h_2 \geq h_1$ sempre (nell'esempio, 18 contro 8). Scrivere 8 comprime molta conoscenza su come si passa da una configurazione all'altra; 18 viene da verifiche più fini, che distinguono e ordinano meglio gli stati. $h_2$ è **più informata**, resta ammissibile, e quindi è preferibile.

Più l'euristica è informata, più scende il costo della **ricerca**. Il costo complessivo, però, comprende anche il costo di **calcolare** l'euristica e quello di eseguire la soluzione: un'euristica molto informata ma costosissima da calcolare non è necessariamente un affare. Le slide (p. 67, da Nilsson 1980) lo mostrano con due curve in funzione del grado di informazione: il costo della strategia cresce e quello della ricerca scende, e il costo complessivo ha un minimo intermedio. Nella slide 66 lo stato di esempio ha $h_1 = 7$ e $h_2 = 4+2+2+2+2+0+3+3 = 18$ (somma ricalcolata), diverso da quello delle slide 41-42 ($h_1 = 8$).
#### Fattore di ramificazione effettivo
Per misurare la qualità di un'euristica si usa il **fattore di ramificazione effettivo** $b^*$: se A\* genera $N$ nodi per trovare una soluzione a profondità $d$, $b^*$ è il fattore di ramificazione di un albero **uniforme** di profondità $d$ con $N + 1$ nodi:

$$N + 1 = 1 + b^* + (b^*)^2 + \dots + (b^*)^d$$

Ad esempio, una soluzione a profondità 5 trovata generando 52 nodi dà $b^* \approx 1{,}92$ (le slide, p. 68, danno lo stesso esempio).

> [!warning] Il termine 1 nella formula delle slide
> Le slide scrivono $N + 1 = b^* + (b^*)^2 + \dots + (b^*)^d$, senza il termine $1$ (la radice) a destra. Con il termine $1$, che serve perché l'albero uniforme ha $N + 1$ nodi in tutto, per $N = 52$ e $d = 5$ si ottiene $b^* \approx 1{,}917$, cioè 1,92 come nell'esempio; senza il termine si avrebbe 1,926. Il valore è tondo in entrambi i casi, ma la formula corretta è quella di AIMA qui riportata (ricalcolato con Python).
 Sperimentalmente una buona euristica ha $b^*$ abbastanza vicino a 1 (le slide indicano $\lesssim 1{,}5$). Più $b^*$ è vicino a 1, più la ricerca è vicina a un andamento lineare: si toglie un nodo dalla frontiera e se ne aggiunge circa uno. Con $b^*$ vicino a 2 il numero di nodi raddoppia a ogni livello.

> [!example] Gioco dell'8: nodi generati e fattore di ramificazione effettivo (dalle slide, p. 69)
> Nodi generati, tra parentesi $b^*$; medie su 100 istanze per ogni profondità $d$.
>
> | $d$ | Approfondimento iterativo | A\* con $h_1$ | A\* con $h_2$ |
> |---|---|---|---|
> | 2 | 10 (2,43) | 6 (1,79) | 6 (1,79) |
> | 4 | 112 (2,87) | 13 (1,48) | 12 (1,45) |
> | 6 | 680 (2,73) | 20 (1,34) | 18 (1,30) |
> | 8 | 6384 (2,80) | 39 (1,33) | 25 (1,24) |
> | 10 | 47 127 (2,79) | 93 (1,38) | 39 (1,22) |
> | 12 | 3 644 035 (2,78) | 227 (1,42) | 73 (1,24) |
> | 14 | non riportato | 539 (1,44) | 113 (1,23) |
>
> Si passa da un numero di nodi intrattabile a uno piccolissimo, e la differenza cresce con la profondità.

> [!warning] Valori della tabella corretti con le slide
> Una versione precedente di queste note riportava per $d = 14$ i valori della seconda edizione di AIMA (approfondimento iterativo 3 473 941 con 2,83; $h_1$ con 1,42; $h_2$ con 1,24). I valori delle slide, che seguono la terza edizione, sono quelli della tabella sopra: per $d = 14$, 1,44 e 1,23. Il dato dell'approfondimento iterativo a $d = 14$ non compare nelle slide (indicato con un trattino).

Le slide (pp. 70-71) osservano che con $b = 2$ servono circa 100 nodi a $d = 6$ e circa 10 000 a $d = 12$, mentre con $b = 1{,}5$ si afferma che $d = 12$ e $d = 24$ corrispondono alle stesse quantità: "migliorando di poco l'euristica si riesce, a parità di nodi espansi, a raggiungere una profondità doppia". Ricalcolando $b + b^2 + \dots + b^d$ con Python si ha 126 e 8190 per $b = 2$ ($d = 6, 12$), ma 386 nodi per $b = 1{,}5$ e $d = 12$ e circa 50 500 per $d = 24$: i valori delle slide sono ordini di grandezza, e la profondità raggiungibile con lo stesso numero di nodi circa raddoppia, come affermato. Tutti i problemi dell'IA, o quasi, sono di complessità esponenziale, "ma c'è esponenziale ed esponenziale".

In problemi a crescita esponenziale, come il riconoscimento del parlato, la scelta della parola successiva o gli scacchi, **migliorare di poco l'euristica** permette di risolvere problemi molto più grandi con la stessa macchina.
### Come si inventano le euristiche
#### Problemi rilassati
Si toglie qualche vincolo al problema e si calcola il costo **esatto** della soluzione del problema **rilassato**. Il costo ottimo di un rilassamento è un'euristica ammissibile per il problema originale (togliere vincoli può solo rendere le soluzioni più economiche), e rilassando allo stesso modo tutte le alternative si ottengono stime confrontabili tra loro.

> [!example] Rilassamenti del gioco dell'8
> La regola è: una tessera si può spostare da A a B se A e B sono adiacenti e B è vuota.
> - Se una tessera può andare **ovunque** (la si stacca e la si incastra al suo posto), il costo esatto è il numero di tessere fuori posto: $h_1$.
> - Se una tessera può andare in una casella **adiacente** anche se occupata, il costo esatto è la somma delle distanze di Manhattan: $h_2$.
>
> $h_2$ viene da un rilassamento più **debole**, cioè più vicino al problema vero, ed è per questo più informata.
#### Massimo di più euristiche
Se si hanno più euristiche ammissibili $h_1, \dots, h_k$ (ad esempio, nei problemi geometrici, le distanze $L_1$, $L_2$ e in generale le metriche $L_p$), nessuna domina le altre su tutti i nodi. Si prende nodo per nodo la più grande:

$$h(n) = \max\{h_1(n), \dots, h_k(n)\}$$

Il massimo di euristiche ammissibili è ancora **ammissibile** e le domina tutte: è un modo adattivo, quasi una votazione, di usare a ogni nodo il punto di vista più informato.
#### Pattern database
Molte configurazioni ricorrono localmente. Si risolvono in modo esatto dei **sottoproblemi** (ad esempio, nel gioco dell'8, portare a posto le tessere 1-4 ignorando le altre, indicate con un asterisco) e se ne memorizza il costo in un **database di pattern**. Durante la ricerca si cerca il pattern dello stato corrente e se ne usa il costo come euristica: è un *caching* di soluzioni di cui si conosce il costo ottimo, un po' come fa un giocatore esperto che riconosce le configurazioni già viste. Il problema è l'**interferenza**: le mosse che risolvono un pattern possono spostare le tessere di un altro, e sommare i costi di pattern diversi può far perdere l'ammissibilità. Si usano allora pattern **disgiunti**, che contano solo le mosse delle proprie tessere. Dalle slide (pp. 75-77): il costo ottimo di un sottoproblema (ad esempio sistemare 1, 2, 3, 4) è una sottostima del costo totale; con più sottoproblemi (5-6-7-8, 2-4-6-8, ...) il **massimo** dei loro valori è ancora un'euristica ammissibile, mentre la somma lo è solo con i pattern disgiunti (euristiche additive), molto efficaci: il gioco del 15 si risolve in pochi millisecondi.
#### Apprendere l'euristica dall'esperienza
Si risolvono molte istanze del problema e si raccolgono le coppie (stato, costo esatto della soluzione da quello stato), cioè campioni di $h^*$. Su questi dati si addestra un **regressore** (una legge lineare, quadratica, una rete neurale) che, per uno stato mai visto, stima $h$. È un'ipotesi appresa che approssima $h^*$: un **modello dell'euristica**. Una regressione di questo tipo non garantisce l'ammissibilità.
#### Combinazioni lineari
Invece del massimo si può usare una combinazione pesata di **caratteristiche** (*feature*) dello stato:

$$h(n) = c_1\,x_1(n) + c_2\,x_2(n) + \dots$$

ad esempio $x_1$ = tessere fuori posto e $x_2$ = coppie di tessere adiacenti scambiate nel gioco dell'8, oppure il vantaggio di pezzi e i pezzi sotto attacco negli scacchi. Fissare i pesi $c_i$ a mano è tentare di scrivere la legge a occhio; con il machine learning si **apprende** la combinazione migliore, che può fare meglio del massimo. Si guarda il problema da più punti di vista e si impara a combinarli.

> [!example] Un percorso terapeutico
> Nella scelta del farmaco successivo in una terapia, si possono considerare separatamente gli effetti collaterali, l'efficacia, l'età del paziente: euristiche separate. Nessuna da sola risolve il problema; la loro combinazione sì. È anche il modo di procedere della scienza: si formulano ipotesi diverse, si misura nella direzione che suggeriscono e si combinano quelle che funzionano.

> [!question] Domanda tipica d'esame
> Quando un'euristica è più informata di un'altra e perché conviene usarla? Come si ottengono euristiche ammissibili dai problemi rilassati? Mostralo sul gioco dell'8 ricavando $h_1$ e $h_2$, e spiega perché il massimo di euristiche ammissibili è ancora ammissibile.
### Altri esempi dalle slide
Dalle slide, non visti a lezione.
- **Minimum spanning tree** con la best-first (0031, pp. 10-11): un esempio su un grafo pesato mostra, passo per passo, che la best-first in generale **non è completa né ottimale**.
- **Delivery robot** (pp. 84-88): il robot deve andare dall'esterno della stanza 103 all'interno della 123; i luoghi di interesse hanno etichette (r101, ...), e il grafo di ricerca presenta cicli. Un'euristica ammissibile è la **distanza euclidea** da r123, come nell'[[03 - Risoluzione di problemi mediante ricerca#Le esercitazioni: confrontare le euristiche|esercitazione sul labirinto]].
### Prossimi passi
La prossima lezione chiude la ricerca con gli algoritmi per **ambienti che cambiano**, in cui il piano non si può decidere una volta per tutte come con A\* e va **ripianificato** dinamicamente. L'esercitazione del venerdì successivo è un labirinto con un oggetto in movimento, che costringe l'agente a cambiare direzione e ripianificare a ogni istante.
## Ricerca locale e ambienti non deterministici
Lezione 6 (21/10/2026): si va oltre la ricerca classica (AIMA cap. 4). Gli algoritmi visti finora pianificano offline un cammino ottimo in un ambiente osservabile e deterministico; qui si rinuncia a qualcuna di queste ipotesi. La **ricerca locale** non tiene in memoria i cammini ma solo lo stato corrente, guidata da una funzione obiettivo: hill climbing, le sue varianti stocastiche, il simulated annealing e la beam search locale. Alla fine si introducono le **azioni non deterministiche**, i **piani contingenti** e gli **stati credenza**. Slide: 0032_AdvancedSearch, pp. 1-29 (le slide sono intitolate "Algoritmi avanzati di Ricerca").
### Oltre le ipotesi della ricerca classica
Con A\* il piano si genera **offline** e poi si esegue, assumendo che l'ambiente non cambi tra pianificazione ed esecuzione e che le azioni siano **deterministiche**. Si possono anche avere più obiettivi in sequenza, generare offline con A\* il piano migliore per ciascuno e scegliere l'ordine che minimizza il costo totale. Ma spesso l'ambiente reagisce in modo non prevedibile:
- un robot su una superficie poco aderente **slitta** e deve ripetere l'azione;
- nel vecchio gioco del 15 di plastica una tessera incastrata male faceva saltare anche le altre.

Il piano, matematicamente ottimo, quando lo si esegue non funziona. Si distinguono allora:
- **ricerca locale**: non mantiene memoria dell'intero piano, risolve localmente e tollera situazioni non previste;
- **ricerca online**: pianificazione ed esecuzione si alternano, la decisione e l'azione avvengono in tempo reale. Non si restituisce un cammino: lo si è già eseguito;
- **ambienti parzialmente osservabili o sconosciuti**: alzarsi di notte nella propria stanza, di cui si ricorda vagamente la mappa ma che non si vede; se si sbaglia di qualche grado girando, si trova il muro prima del previsto.

Per questi casi servono **piani condizionali** (che contengono dei "se") e la possibilità per l'agente di memorizzare le proprie **credenze** sull'ambiente: una copia interna di come crede che sia il mondo.
### Completezza prima dell'ottimalità
In molti problemi reali conta **raggiungere l'obiettivo**, non che la sequenza di azioni sia la migliore possibile: un matematico che dimostra una congettura non esplora tutte le dimostrazioni, segue l'intuizione, e una volta trovata la dimostrazione il risultato vale per sempre. Lo stesso per un LLM: se trova una buona continuazione, il fatto che la risposta sia corretta è già tanto, anche se nessuno sa spiegare analiticamente perché la massimizzazione di quella probabilità funzioni.

In informatica tempo e spazio "sono come Dio": se una finestra si apre mille volte al giorno, deve essere efficiente. Ma fuori dalla macchina, in medicina o in finanza, se un algoritmo impiega cinque minuti in più ma analizza meglio un'immagine diagnostica e salva più vite, è quello da usare: si ottimizza la qualità delle decisioni nel mondo reale, non il calcolo. Un assistente vocale in auto a volte sbaglia, ma è utile. In questi problemi la **completezza** diventa più importante dell'**ottimalità**.
### Ricerca locale
Gli algoritmi di ricerca locale:
- tengono in memoria solo il **nodo corrente** (rischiando di ripercorrere stati già visti, ma con la stessa memoria affrontano problemi molto più grandi);
- **non tengono traccia dei cammini**;
- sono guidati da una **funzione obiettivo**, che dice non solo quando fermarsi ma anche, localmente, come proseguire e quali candidati trascurare.

Dalle slide (pp. 5-6): sono adatti ai problemi in cui la **sequenza di azioni non conta** e importa solo lo stato finale, con tutti gli elementi della soluzione già nello stato ma alcuni vincoli violati (come le regine nella [[03 - Risoluzione di problemi mediante ricerca#Problemi giocattolo#Le otto regine|formulazione a stato completo]]). Non sono sistematici, sono efficienti in memoria e utili per i problemi di **ottimizzazione**: trovare lo stato migliore secondo una funzione obiettivo o lo stato di costo minore.

Lo spazio degli stati si immagina come un **paesaggio**: a ogni stato si associa il valore della funzione obiettivo. Se è un'utilità la si **massimizza**, se è un costo la si **minimizza**. Il problema tipico è il **massimo locale**: uno stato migliore di tutti i suoi vicini ma non il migliore globale (le slide, p. 13, elencano anche gli **altipiani** o *plateau* e i **crinali** o creste, come difficoltà per la salita). Lì ogni mossa peggiora, e una strategia puramente locale si ferma come se avesse raggiunto l'obiettivo: è un vicolo cieco, e il problema non è risolto.

Dall'analisi matematica, la direzione da privilegiare per salire più velocemente è quella del **gradiente**: per una funzione $f(x_1,x_2)$ la direzione di massima pendenza è data dalle derivate parziali $\frac{\partial f}{\partial x_1}$ e $\frac{\partial f}{\partial x_2}$ (come nel metodo di Newton per gli zeri di un polinomio si segue la tangente). Qui si mettono insieme un processo **discreto** (il robot sa fare quattro azioni) e una **funzione di qualità nel continuo**: un piano diventa una spezzata che cambia direzione quando cambiano le derivate. Gli algoritmi che massimizzano un'utilità sono di **risalita della collina** (*hill climbing*), quelli che minimizzano un costo di **discesa del gradiente**. Le reti neurali si addestrano proprio così: si misura l'errore con una funzione di costo e lo si minimizza, perché in futuro la rete sbagli meno.
### Hill climbing
Si sceglie sempre il successore **migliore** dello stato corrente, e ci si ferma quando nessun successore migliora:

```pseudo
\begin{algorithm}
\caption{Hill-Climbing($problem$)}
\begin{algorithmic}
\State $current \gets$ \Call{Make-Node}{$problem.$\textsc{Initial-State}}
\Loop
	\State $neighbor \gets$ un successore di $current$ con il valore più alto
	\If{$neighbor.$\textsc{Value} $\leq current.$\textsc{Value}}
		\State \Return $current.$\textsc{State} \Comment{un massimo, forse solo locale}
	\EndIf
	\State $current \gets neighbor$
\EndLoop
\end{algorithmic}
\end{algorithm}
```

È un comportamento **deterministico**, e proprio per questo si blocca nei massimi locali: arrivato lì non sa nemmeno di esserci, perché non ha guardato altrove. Quando si ferma, dice all'ambiente "sono arrivato", ma è l'ambiente, con la percezione, a dire se l'obiettivo è davvero raggiunto (come quando il navigatore dice "sei arrivato" e bisogna ancora trovare il ristorante nella piazza).

> [!example] Le otto regine con l'hill climbing
> Formulazione a stato completo: le otto regine stanno ciascuna su una colonna diversa. Ogni regina si può spostare in una delle altre 7 celle della sua colonna, quindi ogni stato ha $8\times7=56$ successori. L'euristica $h$ è il numero di **coppie di regine che si attaccano** (la relazione è simmetrica: ogni coppia si conta una volta); va **minimizzata**, e la soluzione ha $h=0$. L'hill climbing sceglie tra i 56 successori quello con $h$ più basso. Dalle slide (pp. 10-12): in uno stato di esempio $h = 17$ e il migliore dei 56 successori ha $h = 12$; tra più successori migliori si sceglie a caso. Esiste anche una configurazione con $h = 1$ in cui tutti i successori peggiorano: l'algoritmo si blocca (e in media si blocca dopo circa 4 passi). Se nessuno migliora, ci si è bloccati in uno stato in cui spostare una sola regina non basta: servirebbe spostarne temporaneamente due, o fare backtracking, che però richiede di ricordare gli stati precedenti.
>
> Partendo da una configurazione casuale, l'hill climbing puro fallisce nell'86% dei casi. Ripetendo l'esperimento abbastanza volte si risolvono comunque molte istanze.

> [!warning] Da verificare
> Le percentuali dettate a lezione si sentono male nella registrazione. Le slide (pp. 12, 14, 15) le confermano: l'hill climbing puro fallisce nell'86% dei casi (risolve il 14%); consentendo un numero limitato di **mosse laterali** il successo sale al 94%, con in media 21 passi. Il dato di 100 mosse laterali consecutive e dei 64 passi medi per i fallimenti viene dal libro (AIMA, 3ª ed., par. 4.1.1), non dalle slide.
#### Varianti
Per uscire dai massimi locali si rinuncia a scegliere sempre il migliore e si inietta un po' di **casualità**, come nelle variazioni genetiche che in natura si affermano per caso:
- **mosse laterali** con un **budget**: un numero limitato di volte si accetta deliberatamente un successore non migliore, per esplorare il paesaggio in altre direzioni (sui plateau). È stabile in memoria e in tempo, perché il numero di "errori" è fissato (ad esempio al più 1500 errori su un milione di mosse);
- **hill climbing stocastico**: tra i successori migliorativi si sceglie **a caso**, con una probabilità che dipende da quanto è ripida la salita; la casualità è continua. Converge più lentamente, ma a volte trova soluzioni migliori (dalle slide);
- **first-choice**: si generano successori a caso e si prende il **primo** che migliora, invece del migliore; utile quando i successori sono moltissimi;
- **riavvio casuale** (*random restart*): se ci si blocca, si riparte da una nuova configurazione iniziale casuale (nelle otto regine, un'altra disposizione), sperando che da lì la soluzione sia più facile da raggiungere. È "un po' di forza bruta": la strategia non si adatta al problema, si limita a ritentare. Dalle slide (p. 15): se la probabilità di successo è $p$ servono in media $1/p$ ripartenze (per le otto regine con $p = 0{,}14$, circa 7 iterazioni); il random restart è tendenzialmente **completo** (basta insistere) e per le regine risolve istanze con 3 milioni di configurazioni in meno di un minuto, ma il risultato dipende molto dalla forma del panorama degli stati.

Gli **algoritmi genetici** alternano novità (le variazioni) e selezione secondo una funzione di *fitness*. Secondo il docente non c'è evidenza che siano superiori agli altri metodi, e non li si studia.

> [!warning] Algoritmi genetici: hill climbing o beam search?
> A lezione sono stati presentati come una variante dell'hill climbing stocastico. Le slide (p. 24) li definiscono invece **varianti della beam search stocastica** in cui gli stati successori sono ottenuti **combinando due stati padre** anziché per evoluzione di un solo stato. Vale la definizione delle slide; le due letture sono comunque vicine, perché entrambe iniettano casualità e selezione.
### Simulated annealing
Il nome (*tempra simulata* nelle slide, dall'articolo di Kirkpatrick, Gelatt e Vecchi del 1983) viene dalla **ricottura** dei metalli: ad alta temperatura il metallo si può modellare come si vuole, raffreddandosi si irrigidisce. L'algoritmo sceglie un successore **a caso**:
- se migliora lo stato corrente, lo accetta;
- altrimenti lo accetta con probabilità $e^{\Delta E/T}$, dove $\Delta E<0$ è il peggioramento della funzione obiettivo e $T$ è la **temperatura**.

La temperatura **scende** nel tempo secondo un programma (*schedule*). A temperatura alta $\Delta E/T$ è vicino a zero e la probabilità di accettare una mossa peggiorativa è alta: il sistema esplora, uscendo dagli intorni dei massimi. A temperatura bassa la probabilità tende a zero e l'algoritmo si comporta come l'hill climbing, convergendo verso un massimo. Se $T$ decresce abbastanza lentamente, si trova il massimo globale con probabilità che tende a 1. Di solito la temperatura iniziale si sceglie in modo che all'inizio le mosse peggiorative siano accettate con probabilità intorno a 0,5, cioè quasi come lanciare una moneta.

```pseudo
\begin{algorithm}
\caption{Simulated-Annealing($problem$, $schedule$)}
\begin{algorithmic}
\State $current \gets$ \Call{Make-Node}{$problem.$\textsc{Initial-State}}
\For{$t = 1$ \textbf{to} $\infty$}
	\State $T \gets schedule(t)$
	\If{$T = 0$}
		\State \Return $current$
	\EndIf
	\State $next \gets$ un successore di $current$ scelto a caso
	\State $\Delta E \gets next.$\textsc{Value} $- current.$\textsc{Value}
	\If{$\Delta E > 0$}
		\State $current \gets next$
	\Else
		\State $current \gets next$ con probabilità $e^{\Delta E/T}$
	\EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

È una tecnica euristica che si colloca a metà tra le varianti precedenti: c'è una legge probabilistica per scegliere, ma la scelta è casuale. Anche ChatGPT ha un parametro chiamato temperatura, con lo stesso significato: più è alta, più le continuazioni scelte sono "nuove".
### Beam search locale
Invece di un solo stato si tengono **$k$ stati**: a ogni passo si generano i successori di tutti e $k$ e si tengono i $k$ migliori. Non è come fare $k$ riavvii indipendenti, perché i $k$ stati scelti possono venire tutti dai successori dello stesso stato. È una forma di **taglio con budget** della frontiera, già vista tra le [[03 - Risoluzione di problemi mediante ricerca#Varianti a memoria limitata|varianti a memoria limitata]]: la memoria non supera mai $k$ soluzioni, quindi si possono esplorare problemi con fattori di ramificazione enormi.

> [!example] Riconoscimento del parlato
> Per trascrivere il segnale vocale «ciao mamma sto arrivando» il sistema deve scegliere tra molte segmentazioni del segnale in parole. Procede da sinistra a destra e si porta dietro le $k$ trascrizioni parziali più **probabili** come frase italiana, buttando le altre; quando il segnale finisce, restituisce la più probabile. Le probabilità vengono da collezioni di testi: non si possono conoscere per tutte le frasi possibili, quindi si approssimano con modelli in cui ogni parola dipende solo dalle due precedenti,
> $$P(w_i\mid w_{i-2},w_{i-1})$$
> e la probabilità di una frase è il prodotto. Le parti già calcolate si riusano, e serve conoscere molti meno valori; ma con 10.000 parole nel vocabolario le triple sono comunque moltissime. Questi modelli markoviani si usano dalla fine degli anni '80; il limite è che la stessa parola ha significati diversi a seconda del contesto ("l'impresa di Ulisse" e "l'impresa di Musk"), e per modellare il contesto arriveranno le reti neurali.

Dalle slide (pp. 23-24): se tra i successori c'è un obiettivo ci si ferma, altrimenti si prosegue con i $k$ migliori. Nella variante **stocastica** si scelgono $k$ successori a caso, con probabilità maggiore per i migliori, come in un processo di selezione naturale (organismo, progenie, *fitness*).

Il compromesso: si cerca dentro un "cono" di soluzioni, sperando che il cammino ottimo, o almeno uno buono, ci stia dentro. Se la funzione usata per ordinare non è buona, si è costretti a ricominciare.
### Azioni non deterministiche e piani contingenti
Nella **ricerca online** non si può sfruttare la piena osservabilità né il determinismo: quando l'ambiente cambia non ci si può fidare di quello che succederà, e si è costretti ad alternare **percezione, scelta dell'azione ed esecuzione**. Le strategie di un agente che non ha un piano deterministico, ma azioni condizionate a certe condizioni, si chiamano **piani contingenti**.

> [!example] L'aspirapolvere imprevedibile
> Nel [[03 - Risoluzione di problemi mediante ricerca#Il mondo dell'aspirapolvere|mondo dell'aspirapolvere]] l'azione $\mathit{Aspira}$ a volte pulisce anche la stanza accanto, e in una stanza pulita a volte rilascia sporco (un pavimento con i peli del cane). Il **modello di transizione** non restituisce più uno stato ma un **insieme di stati** possibili: dopo aver aspirato nello stato 1 ci si può trovare in uno stato in cui è pulita solo la stanza corrente o in uno in cui sono pulite entrambe. Il piano deve allora prevedere entrambi i casi.

Quando il modello di transizione restituisce insiemi, si ragiona su **insiemi di stati** possibili, cioè sugli stati che l'agente immagina potrebbero verificarsi dopo aver agito: sono gli **stati credenza**. Anche un aspirapolvere **cieco**, senza sensori, se conosce bene il modello del mondo può calcolare una sequenza di azioni (ad esempio aspira, vai a destra, aspira) che lo porta comunque in uno stato obiettivo, partendo dall'insieme di tutti gli stati possibili. Gli insiemi di stati raggiungibili con la stessa sequenza di azioni sono classi di equivalenza.

Per descrivere gli stati credenza in modo compatto si useranno la **logica** e il modello relazionale: invece di elencare gli stati si scrivono le **proprietà comuni** (ad esempio "la stanza sinistra è pulita", qualunque sia lo stato della destra), e un'azione come "vai a destra" cambia solo la proprietà della posizione. Così con una formula si gestisce un numero enorme di stati diversi, e si potrà pianificare in spazi molto complicati.

> [!info] Da leggere
> Questa parte corrisponde al capitolo 4 della terza edizione di AIMA (nella quarta edizione gli stessi argomenti sono distribuiti diversamente).
## Ricerca AND-OR, stati credenza e ricerca online
Lezione 7 (26/10/2026): si completa il capitolo 4 di AIMA. Con azioni **non deterministiche** il piano diventa un albero di contingenze, calcolato con la **ricerca AND-OR**. Senza percezioni si cerca nello spazio degli **stati credenza**, e con percezioni parziali le osservazioni restringono le credenze. Infine la **ricerca online**, in cui l'agente non conosce l'ambiente e deve alternare pianificazione ed esecuzione, con l'algoritmo **LRTA\***. Slide: 0032_AdvancedSearch, pp. 30-80.
### Piani contingenti e ricerca AND-OR
Un agente che si muove al buio procede con un piano che non è una sequenza di azioni ma un piano con **biforcazioni**: successioni di azioni diverse, controllate dalle condizioni che si osservano durante l'esecuzione.

> [!example] L'aspirapolvere imprevedibile
> Nel mondo dell'aspirapolvere con azioni non deterministiche, $\mathit{Aspira}$ in una stanza sporca la pulisce e a volte pulisce anche l'altra; in una stanza pulita a volte la sporca. Partendo dallo stato 1 (aspirapolvere a sinistra, entrambe le stanze sporche), aspirando si può finire nello stato 5 (pulita solo la sinistra) o nello stato 7 (pulite entrambe, un obiettivo). Il piano deve risolvere **entrambi** i casi:
> $$[\mathit{Aspira},\ \textbf{if } \mathit{Stato}=5 \textbf{ then } [\mathit{Destra},\mathit{Aspira}] \textbf{ else } [\ ]]$$
> Aspirare di nuovo a sinistra potrebbe risporcare la stanza e riportare allo stato 1: conviene spostarsi a destra e aspirare. Nelle slide (p. 29) $\mathrm{Risultato}(\mathit{Aspira}, 1) = \{5, 7\}$ e il piano è lo stesso.

L'albero di ricerca ha due tipi di nodi:
- **nodi OR**: l'agente sceglie un'azione, e ne basta **una** che funzioni;
- **nodi AND**: l'ambiente sceglie l'esito, e il piano deve funzionare per **tutti** gli stati possibili.

Una soluzione è un sottoalbero con un obiettivo in ogni foglia, un'azione in ogni nodo OR e tutti i rami in ogni nodo AND. Se per qualche contingenza non funziona, non è un piano.

La ricerca parte con $\textsc{Or-Search}(problem.\textsc{Initial-State}, problem, [\,])$.

```pseudo
\begin{algorithm}
\caption{Or-Search($state$, $problem$, $path$)}
\begin{algorithmic}
\If{$problem.$\Call{Goal-Test}{$state$}}
	\State \Return il piano vuoto
\EndIf
\If{$state$ è in $path$}
	\State \Return $failure$ \Comment{ciclo}
\EndIf
\For{$action \in problem.$\Call{Actions}{$state$}}
	\State $plan \gets$ \Call{And-Search}{\Call{Results}{$state, action$}, $problem$, $[state \mid path]$}
	\If{$plan \neq failure$}
		\State \Return $[action \mid plan]$
	\EndIf
\EndFor
\State \Return $failure$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{And-Search($states$, $problem$, $path$)}
\begin{algorithmic}
\For{$s_i \in states$}
	\State $plan_i \gets$ \Call{Or-Search}{$s_i, problem, path$}
	\If{$plan_i = failure$}
		\State \Return $failure$
	\EndIf
\EndFor
\State \Return $[\textbf{if } s_1 \textbf{ then } plan_1 \textbf{ else if } s_2 \textbf{ then } plan_2 \dots \textbf{ else } plan_n]$
\end{algorithmic}
\end{algorithm}
```

- **Or-Search** parte dallo stato iniziale con un cammino vuoto. Se lo stato è un obiettivo non c'è niente da fare; se è già sul cammino c'è un **ciclo** e quel piano non si può usare. Altrimenti prova le azioni: il risultato di un'azione non è uno stato ma un **insieme di stati**, le contingenze, e la soluzione è valida se ce n'è una per ciascuna.
- **And-Search** risolve ricorsivamente ogni stato raggiunto con Or-Search: se uno fallisce, fallisce tutto e si torna a cercare un'altra azione (una sorta di backtracking); altrimenti compone il piano condizionale "se sei in $s_1$ applica $plan_1$, se sei in $s_2$ applica $plan_2$...".

La notazione $[action \mid plan]$ è quella delle liste di Prolog: la barra concatena un elemento in testa a una lista. Con liste di liste si rappresentano bene i nodi AND e OR.

Il problema di questi algoritmi è la **memoria**: bisogna ricordare tutti gli stati per decidere se una soluzione vale per tutti i cammini.
#### Piani ciclici
Se il non determinismo consiste nel fatto che un'azione a volte **non ha effetto** (l'aspirapolvere slitta e resta dov'è), nessun piano aciclico garantisce di arrivare: servono **piani ciclici**, del tipo "ripeti finché non ti sei spostato". Il piano termina solo se l'azione prima o poi riesce. Le slide (pp. 34-35) lo mostrano con l'**aspirapolvere slittante**: lo spostamento può non avere effetto, $\mathrm{Risultato}(\mathit{Destra}, 1) = \{1, 2\}$, e il piano è $[\mathit{Aspira},\ L_1: \mathit{Destra},\ \textbf{if } \mathit{Stato}=5 \textbf{ then } L_1 \textbf{ else } \mathit{Aspira}]$, scrivibile anche con un $\textbf{while } \mathit{Stato}=5 \textbf{ do } L_1$. Va distinto dal caso in cui non si osserva l'esito: un personaggio che prova ad aprire una porta con una chiave non può ripetere all'infinito, perché la chiave può semplicemente non essere quella giusta. Un agente razionale deve anche saper **smettere**: "ho finito le risorse".
### Ricerca senza osservazioni
Il caso estremo è l'agente **senza sensori** (*sensorless*, o *conformante* nelle slide, p. 38). Anche senza percezione può avere un'immagine interna del mondo fatta delle proprie **credenze**, come chi si alza di notte nella propria casa: non vede, ma conosce la mappa, e per questo non accende la luce (a casa di un amico è meglio restare a letto).

Uno **stato credenza** (*belief state*) è un insieme di stati fisici in cui l'agente crede di poter essere: "il telefono è sulla scrivania di destra oppure su quella di sinistra". Lo stato credenza $\{1,3\}$ corrisponde alla formula $\mathit{Stato}_1\lor\mathit{Stato}_3$. Le credenze non sono la verità oggettiva dell'ambiente, ma ciò in cui l'agente crede.

Il problema si riformula nello spazio degli stati credenza:
- **stati**: tutti i sottoinsiemi degli stati fisici; con $N$ stati fisici sono $2^N$;
- **stato iniziale**: tipicamente l'insieme di tutti gli stati (non so niente, ma so di non sapere);
- **azioni**: quelle legali in almeno uno degli stati della credenza (l'unione delle azioni; se le azioni illecite in uno stato hanno effetti dannosi è meglio l'**intersezione**, dalle slide, p. 40);
- **modello di transizione**: l'insieme degli stati raggiungibili applicando l'azione a ciascuno stato della credenza. Con azioni deterministiche la credenza non cresce; con azioni non deterministiche si ha un'**esplosione dei casi** (da $\{1,3\}$ con $\mathit{Destra}$ che può slittare si arriva a $\{1,2,3,4\}$);
- **test obiettivo**: la credenza è un obiettivo se **tutti** i suoi stati lo sono. Non so dove sono finito, ma qualunque sia lo stato, ho raggiunto l'obiettivo.

> [!example] L'aspirapolvere cieco
> Con 8 stati fisici gli stati credenza sono $2^8=256$, ma da quello iniziale (tutti gli stati) ne sono raggiungibili solo 12. Il piano $[\mathit{Destra},\mathit{Aspira},\mathit{Sinistra},\mathit{Aspira}]$ porta comunque allo stato 7, entrambe le stanze pulite: già il primo $\mathit{Aspira}$ garantisce che la stanza in cui ci si trova sia pulita.

Dalle slide (pp. 39-45): nello spazio degli stati credenza l'ambiente è **osservabile per definizione**, perché l'agente conosce le proprie credenze. Si può fare una ricerca su grafo scartando una credenza già incontrata e **potare** di più: se $s' \subseteq s$ con $s'$ già incontrata si trascura $s$, e se $s \subseteq s'$ e da $s'$ si è trovata una soluzione si trascura $s$. I limiti sono l'efficienza (lo spazio è molto più grande e la rappresentazione atomica obbliga a elencare tutti gli stati) e il fatto che una soluzione si può cercare **incrementalmente**: si trova una soluzione per lo stato 1, si controlla che funzioni per gli altri e, se no, se ne cerca un'altra per lo stato 1; i fallimenti si scoprono presto, ma serve un'unica soluzione valida per tutti gli stati. Il costo del cammino si assume indipendente dallo stato.

Rappresentare le credenze per enumerazione diventa presto insostenibile. Serve un **linguaggio** che con pochi simboli descriva insiemi enormi di stati, come $\forall x\ x>4$ descrive con quattro simboli infiniti numeri naturali: è il ruolo della **logica**, che verrà nella parte sulla conoscenza.

> [!info] Credenze e allucinazioni
> Il docente collega le credenze alle **allucinazioni** degli LLM: dove non ha informazione, il sistema entra in uno stato di incompletezza e agisce secondo le sue credenze, scegliendo euristicamente la risposta più probabile. Spesso la domanda non specifica tutta la natura del problema ("come faccio pace con la mia fidanzata?" senza dire niente di lei). L'IA non elimina magicamente il non determinismo: lo governa sulla base di conoscenza, credenze e rischio.
### Osservabilità parziale
Con sensori locali la percezione restringe le credenze. La funzione $\mathit{Percept}(s)$ dà la percezione nello stato $s$; con sensori completi $\mathit{Percept}(s)=s$, con nessun sensore è nulla. Con l'aspirapolvere a **percezione locale** la percezione $[A,\mathit{Sporco}]$ dice solo che l'agente è nella stanza sinistra ed è sporca, cioè che lo stato è 1 oppure 3.

La transizione tra credenze diventa un processo in tre fasi:
1. **predizione**: lo stato credenza raggiunto con l'azione, come senza sensori;
2. **osservazioni possibili**: le percezioni che si potrebbero ricevere negli stati predetti;
3. **aggiornamento**: per ogni percezione possibile, la credenza si restringe agli stati compatibili con quella percezione.

Dato che le osservazioni possibili sono più di una, il problema è di nuovo non deterministico e si risolve con la ricerca AND-OR sugli stati credenza. Nelle slide (p. 48) $\mathit{Percezioni}(s)$ è nulla nei problemi senza sensori, uguale a $s$ negli ambienti osservabili, altrimenti le percezioni possibili in $s$; con $[A,\mathit{Sporco}]$ lo stato iniziale è $\{1,3\}$. La transizione è $b'' = \textsc{Aggiorna}(\textsc{Predizione}(b,a), o)$ (p. 49).

> [!example] Aspirapolvere con sensori locali (dalle slide, p. 51)
> Il piano $[\mathit{Aspira},\ \mathit{Destra},\ \textbf{if } \mathit{statoCredenza}=\{6\} \textbf{ then } \mathit{Aspira} \textbf{ else } [\,]]$ si appoggia sulla percezione dopo lo spostamento per decidere se aspirare ancora.
### Ricerca online
Nei problemi **online** l'agente deve **alternare** la scelta dell'azione e la sua esecuzione: un'azione va eseguita perché si possa pianificare quella successiva. Succede quando:
- l'ambiente è **dinamico** e cambia alla stessa velocità del calcolo: finita la pianificazione ottima, l'ambiente è cambiato o l'obiettivo si è spostato;
- l'ambiente è **sconosciuto**, e non si può decidere senza agire;
- il non determinismo è così forte che considerare tutte le situazioni possibili non è trattabile.

Le slide (pp. 54-59) vedono i **problemi di esplorazione** come casi estremi di problemi con contingenza: solo lo stato corrente è osservabile, l'ambiente è ignoto, l'effetto e il costo delle azioni non si conoscono prima di eseguirle e servono azioni esplorative. Nell'esempio di Teseo nel labirinto, con la mappa (e le $h$ scritte in ogni cella) si possono usare tutti gli algoritmi di pianificazione visti; senza mappa Teseo non può pianificare ma solo **esplorare** nel modo più razionale possibile: è la ricerca online.

L'idea fondamentale è l'**esplorazione**. Anche gli LLM, i "pappagalli stocastici" che generano una parola alla volta, procedono così: non calcolano tutta la risposta in anticipo, ma risolvono localmente alternando pianificazione ed esecuzione.

L'agente conosce solo:
- le **azioni legali** nello stato corrente, $\mathit{Actions}(s)$: nella metafora del grafo, gli archi uscenti dal nodo;
- il **costo** di un'azione, ma solo **dopo** averla eseguita (in una città in collina, 200 metri in linea d'aria possono costare molto di più);
- il **test obiettivo**: una percezione che dice se si è arrivati (in cucina al buio, la mano sul frigorifero).

Può avere un'euristica, ad esempio la distanza in linea d'aria dall'uscita, che sente dal rumore della finestra aperta.

> [!quote] Rapporto competitivo
> La qualità di un agente online si misura con il **rapporto competitivo**: il costo del cammino effettivamente percorso diviso il costo del cammino che l'agente percorrerebbe se conoscesse l'ambiente in anticipo. Vale 1 per un agente perfetto ed è maggiore di 1 se l'esplorazione fa fare mosse inutili; può essere **infinito**, se l'agente non esce mai da un ciclo.

> [!warning] Ambienti esplorabili in sicurezza
> In uno spazio con **vicoli ciechi** (*dead end*), stati da cui non si può tornare indietro (cadere in un pozzo, essere mangiati dal drago), nessun agente online può garantire di arrivare: ci finisce per caso. Negli esercizi e all'esame si assume che l'ambiente sia **esplorabile in sicurezza** (*safely explorable*): l'obiettivo è raggiungibile da ogni stato raggiungibile, cioè tutte le azioni sono reversibili.
#### Agente online in profondità
Senza mappa, l'agente può esplorare sistematicamente in profondità: prova la prima azione non ancora tentata, se trova un muro torna indietro (**backtrack**) ed esplora la successiva. Per farlo memorizza, per ogni coppia (stato, azione), lo stato di arrivo osservato, e per ogni stato gli stati da cui ci è arrivato, per poterci tornare. Nel caso peggiore percorre ogni arco due volte (nelle slide, p. 61, ogni casella due volte), ma arriva se l'obiettivo esiste. Le slide (p. 60) chiamano le strutture `nonProvate[s]` (le mosse ancora da esplorare in $s$), `Risultato[a, s]` $= s'$ e `backtrack[s]` (gli stati a cui si può tornare). Funziona solo con azioni reversibili, e non usa nessuna euristica.

Le alternative locali hanno problemi: l'hill climbing si blocca nei massimi locali, e il **riavvio casuale** non è possibile, perché un agente che agisce davvero non può teletrasportarsi in un altro stato ("come Harry Potter"). Una passeggiata casuale prima o poi arriva, ma con molte azioni inutili. Le slide (pp. 63-64) osservano che nella ricerca online il valore di $h$ si conosce solo dopo aver esplorato lo stato, quindi una best-first non funzionerebbe e serve un metodo locale; per sfuggire ai minimi locali propongono o il **random walk** (mosse casuali in discesa) o l'**apprendimento in tempo reale**, cioè aggiustare i valori dell'euristica esplorando, che è LRTA\*.
#### LRTA\*
L'idea migliore è **A\* con apprendimento durante l'azione**: *learning real-time A\**. L'agente mantiene una stima $H(s)$ del costo per raggiungere l'obiettivo da $s$, che parte dall'euristica $h(s)$ (ammissibile e consistente) e viene **aggiornata con l'esperienza**: $h$ sottostima il cammino reale, e $H$ cerca di stimarlo meglio mentre l'agente agisce. Come le persone, se si ripassa da una situazione già vista si evitano le scelte che hanno portato in vicoli ciechi.

Il costo stimato di un'azione $a$ da $s$ verso $s'$ è
$$\text{LRTA*-Cost}(s,a,s',H)=\begin{cases}h(s)&\text{se }s'\text{ non è ancora noto}\\c(s,a,s')+H(s')&\text{altrimenti}\end{cases}$$
Quando l'agente lascia $s$, aggiorna $H(s)$ al minimo, tra le azioni possibili, di questo costo; poi si sposta verso il vicino che lo minimizza. Gli stati non ancora esplorati sono considerati ottimisticamente vicini all'obiettivo, il che spinge a esplorarli.

```pseudo
\begin{algorithm}
\caption{LRTA*-Agent($s'$)}
\begin{algorithmic}
\State \textbf{persistenti:} $result$, tabella indicizzata da stato e azione, inizialmente vuota
\State \textbf{persistenti:} $H$, tabella delle stime dei costi indicizzata dallo stato, inizialmente vuota
\State \textbf{persistenti:} $s, a$, lo stato e l'azione precedenti, inizialmente nulli
\If{\Call{Goal-Test}{$s'$}}
	\State \Return $stop$
\EndIf
\If{$s'$ è un nuovo stato (non in $H$)}
	\State $H[s'] \gets h(s')$
\EndIf
\If{$s$ non è nullo}
	\State $result[s, a] \gets s'$
	\State $H[s] \gets \min_{b \in \textsc{Actions}(s)}$ \Call{LRTA*-Cost}{$s, b, result[s, b], H$}
\EndIf
\State $a \gets$ un'azione $b \in$ \Call{Actions}{$s'$} che minimizza \Call{LRTA*-Cost}{$s', b, result[s', b], H$}
\State $s \gets s'$
\State \Return $a$
\end{algorithmic}
\end{algorithm}
```

> [!example] Uscire da un minimo locale
> In un corridoio unidimensionale l'agente si trova in uno stato con $H=2$ tra due vicini che sembrano allontanarlo dall'obiettivo: per arrivarci deve superare una "cresta". Spostandosi aggiorna il nodo di partenza a $2+1=3$; tornando indietro e avanti aggiorna i valori a 4, poi a 5. Dopo qualche andata e ritorno i valori del minimo locale crescono abbastanza da rendere conveniente scavalcare la cresta, e l'agente prosegue verso l'uscita: anche sbagliando, torna indietro e procede. Nelle slide (p. 68) le sei celle passano dai valori $(8, 9, 2, 2, 4, 3)$ a $(8, 9, 5, 5, 4, 3)$ con la terza cella che va da 2 a 3 e poi a 5 e la quarta da 2 a 4 e poi a 5 (le righe (a)-(f) della figura).

Le slide (pp. 69-76) mostrano anche LRTA\* su una griglia $4 \times 4$ con $H$ aggiornata passo dopo passo; non è stata commentata a lezione.

> [!quote] Proprietà di LRTA\* (dalle slide, p. 77)
> LRTA\* cerca di simulare A\* con un metodo di ricerca locale, tenendo conto del costo delle mosse aggiornando al volo $H$. È **completo** in spazi esplorabili in sicurezza; nel caso pessimo visita tutti gli stati due volte, ma è mediamente più efficiente della profondità online. **Non è ottimo**, a meno di usare un'euristica perfetta: non basta $f = g + h$ con $h$ ammissibile.

> [!info] Per le esercitazioni
> Il docente suggerisce di usare LRTA\* nel lavoro sulla ricerca online: uscire dalla pianificazione totale, fingere di vedere solo una cella alla volta e aggiornare l'euristica $h$ in una $H$ durante l'esecuzione. L'algoritmo è sul libro (AIMA, 3ª ed., par. 4.5).

> [!question] Domanda tipica d'esame
> Cosa sono i piani contingenti e come li calcola la ricerca AND-OR? Cos'è uno stato credenza e quando un problema senza sensori è risolto? Cos'è il rapporto competitivo di un agente online e come funziona LRTA\*?
