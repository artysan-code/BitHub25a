---
tags:
  - intelligenza-artificiale
  - ricerca
  - problem-solving
slide: []
---
# Risoluzione di problemi mediante ricerca
Lezione 2 (12/10/2026): come si trasforma un problema in un problema di ricerca nello spazio degli stati (obiettivo, formulazione, soluzione come piano), i cinque elementi della formulazione, alcuni problemi giocattolo e reali (Romania, aspirapolvere, gioco dell'8, otto regine, dimostrazione di teoremi) e lo schema generale della ricerca ad albero con la frontiera. Riprende l'[[02 - Agenti intelligenti#Agente con obiettivo|agente con obiettivo]] della lezione precedente e corrisponde alla prima parte del capitolo 3 di AIMA.
## Le esercitazioni: il codice non basta
> [!info] Cosa conta in una consegna
> Il solo codice dice poco: si può testarlo, ma non spiega **perché** è stato scritto così (copiato, generato da un assistente e accettato dopo due prove, o progettato discutendo con l'IA). Chi rilascia un programma ci mette la firma e deve saperne motivare le scelte. Si chiede quindi di consegnare anche la **discussione** della soluzione, preferibilmente in un **notebook** che alterna codice e commenti, scritto per un "cliente" che conosce la matematica ma non Python; è anche una preparazione all'orale. Secondo il docente, soluzioni corrette senza commenti valgono la sufficienza, notebook ben documentati vanno verso il 27-30 anche con qualche piccolo errore.
## Risolvere problemi come ricerca
Il cuore del lavoro di un agente è il **problem solving**: costruire la soluzione di un problema come **avvicinamento progressivo e incrementale** alla soluzione finale. Ogni passo è una possibile evoluzione della soluzione parziale, e cercare questi stati intermedi significa costruire la soluzione.
- Vincere una partita a scacchi significa trovare una **sequenza di mosse**; ogni mossa dell'avversario cambia lo stato dell'ambiente e la mossa successiva dipende dalle precedenti e dalle nuove condizioni.
- Anche un **LLM** che genera una risposta sta cercando: la risposta è la frase "ottima" per la domanda, costruita con passi discreti (una parola dopo l'altra) scelti nel vocabolario.

Quindi **cercare nei grafi equivale a risolvere problemi**. Il guaio è il costo: le frasi che un LLM può generare crescono esponenzialmente con la lunghezza, con base pari alla dimensione del vocabolario (decine di migliaia di parole). Gran parte dell'IA consiste nel rendere **efficiente** la navigazione di spazi degli stati così grandi.
### Le fasi del problem solving
1. **Formulazione dell'obiettivo**: l'obiettivo è un **sottoinsieme di stati** in cui il problema si considera risolto. Il taxi che da Tor Vergata va a Piazza del Popolo ha finito in qualunque punto della piazza (o al Muro Torto, da cui il cliente entra a piedi).
2. **Formulazione del problema**: si sceglie un linguaggio formale per gli stati (una specifica algebrica, come una tupla relazionale, e una struttura dati in Python o C) e le **azioni**, che portano da uno stato a un altro.
3. **Ricerca della soluzione**: noti stato iniziale e stati obiettivo, si cerca la sequenza di azioni che porta dall'uno agli altri.
4. **Esecuzione**: la sequenza trovata, detta **piano**, viene eseguita.

> [!quote] Soluzione
> Una **soluzione** è una sequenza di azioni che porta dallo stato iniziale a uno stato obiettivo. Una soluzione **ottima** è quella di costo minimo tra tutte le soluzioni.

La concezione del piano è **separata** dalla sua esecuzione: l'agente costruisce la soluzione nella propria memoria, su una rappresentazione interna del mondo, e solo dopo agisce nella realtà un passo alla volta.

> [!info] Domanda a lezione: e se un'azione porta in un vicolo cieco?
> Durante la ricerca l'agente **non si sta muovendo**: allunga un piano immaginario $s_0, \dots, s$ e, se un'aggiunta si rivela un punto senza uscita, la toglie e prova altro. In un **labirinto sconosciuto**, invece, non si può pianificare: si fa un passo, si osserva e si torna indietro fisicamente. È la differenza tra un ambiente **noto e osservabile** e uno che va esplorato.
### Le ipotesi sull'ambiente
Per ora si assume un ambiente (vedi le [[02 - Agenti intelligenti#Proprietà dell'ambiente|proprietà dell'ambiente]]):
- **statico**: mentre l'agente pianifica il mondo non cambia (la rete stradale di Roma resta quella, salvo eccezioni);
- **osservabile**: l'agente conosce lo stato a ogni passo, quindi sa anche se sta tornando su uno stato già visto (un ciclo);
- **discreto**: gli stati sono enumerabili $s_0, s_1, \dots, s_n$, cioè indicizzabili con i naturali (sulla mappa, ad esempio, gli incroci), e da ogni stato è possibile un **sottoinsieme finito** di azioni (con il Muro Torto a destra non si può girare a destra);
- **deterministico**: in uno stato un'azione ha sempre lo stesso effetto, quindi il piano si può eseguire anche "a occhi chiusi".
## Formulazione di un problema
Un problema di ricerca è definito da cinque elementi.

> [!quote] Problema di ricerca
> 1. **Stato iniziale** $s_0$, descritto nel linguaggio di rappresentazione scelto.
> 2. **Azioni**: per ogni stato $s$, l'insieme $\text{Actions}(s)$ delle azioni applicabili in $s$.
> 3. **Modello di transizione**: la funzione $\text{Result}(s, a) = s'$ che restituisce lo stato raggiunto eseguendo l'azione $a$ nello stato $s$. Lo stato $s'$ si chiama **successore** di $s$.
> 4. **Test obiettivo**: una funzione $\text{Goal-Test}(s) \in \{\text{true}, \text{false}\}$ che dice se $s$ è uno stato obiettivo.
> 5. **Costo del cammino**: la somma dei **costi di passo** $c(s, a, s')$ delle azioni del cammino.
>
> I primi tre elementi definiscono implicitamente lo **spazio degli stati**: un grafo orientato i cui nodi sono stati e i cui archi sono azioni.
### Il test obiettivo
Il test obiettivo è un'**etichettatura** degli stati: vale *true* sugli stati obiettivo e *false* sugli altri. Esprime la competenza dell'agente nel capire, dalle percezioni, di essere arrivato (a Piazza del Popolo, vedendo la Porta del Popolo o il Pincio).
- A volte gli stati obiettivo si possono **enumerare**: in un calcio "a celle", il goal della squadra 1 è l'unico stato in cui il pallone sta nella cella della porta avversaria.
- Altre volte si definiscono **funzionalmente**: negli scacchi gli stati di scacco matto (il re avversario è sotto scacco e non ha mosse) sono troppi per elencarli, e si usa una funzione che risponde "hai vinto?".
### Il costo del cammino
Ogni azione, cioè ogni arco, ha un costo strettamente positivo:

$$c(s, a, s') \geq \varepsilon > 0$$

Se un'azione costasse zero si potrebbe ripeterla all'infinito: andare avanti e indietro tra due stanze a costo nullo darebbe infinite soluzioni "ottime". Con un costo minimo $\varepsilon$ ogni azione in più si paga, e la soluzione di costo $c$ si distingue sempre da quella di costo $c + \varepsilon$.

> [!info] Costo della ricerca e costo dell'esecuzione
> Il costo totale per un agente che risolve un problema è la somma di due componenti: il **costo della ricerca** (tempo e memoria per trovare la soluzione) e il **costo del cammino** trovato (quanto costa eseguirlo). Si può trovare velocissimamente una soluzione che costa moltissimo da eseguire, o viceversa: si cerca un compromesso che minimizzi la somma.
## Problemi giocattolo
### Viaggio in Romania
È il *running example* di AIMA: su una mappa della Romania si deve andare da **Arad** a **Bucarest**. Da Arad sono raggiungibili Sibiu, Timisoara e Zerind.
- **Stato iniziale**: $\mathit{In}(\mathit{Arad})$. È una formula logica: un predicato $\mathit{In}$ applicato a una costante, vero per Arad e falso per ogni altra città. Come nelle basi di dati, dove una formula è vera se la tupla è in tabella.
- **Azioni**: $\text{Actions}(\mathit{In}(\mathit{Arad})) = \{\mathit{Go}(\mathit{Sibiu}), \mathit{Go}(\mathit{Timisoara}), \mathit{Go}(\mathit{Zerind})\}$. Un'azione è applicabile solo se appartiene a questo insieme.
- **Modello di transizione**: $\text{Result}(\mathit{In}(\mathit{Arad}), \mathit{Go}(\mathit{Zerind})) = \mathit{In}(\mathit{Zerind})$, in generale $\text{Result}(\mathit{In}(x), \mathit{Go}(y)) = \mathit{In}(y)$.
- **Test obiettivo**: $\mathit{In}(\mathit{Bucarest})$.
- **Costo del cammino**: la somma delle distanze in chilometri.

L'esempio mostra che per ragionare sugli stati il grafo non basta: serve un **linguaggio** che dica cosa è vero e cosa è falso nel mondo rispetto a ciascun nodo.
### Il mondo dell'aspirapolvere
È l'[[02 - Agenti intelligenti#Agente reattivo semplice|aspirapolvere]] della lezione precedente, con due stanze.
- **Stati**: lo stato è determinato da tre variabili booleane: la posizione dell'aspirapolvere (sinistra o destra) e lo stato di ciascuna stanza (sporca o pulita). Ci sono quindi $2^3 = 8$ stati.
- **Stato iniziale**: uno qualunque degli otto.
- **Azioni**: `Left`, `Right`, `Suck`.
- **Modello di transizione**: `Left` e `Right` spostano l'aspirapolvere (nessun effetto se è già nella stanza più a sinistra o più a destra), `Suck` pulisce la stanza corrente.
- **Test obiettivo**: entrambe le stanze pulite; sono gli stati 7 (aspirapolvere a sinistra) e 8 (a destra).
- **Costo del cammino**: ogni azione costa 1.

Nel grafo degli stati si vedono "livelli" di distanza dalla soluzione: gli stati 1 e 2 (entrambe le stanze sporche), poi quelli con una stanza sporca, infine gli obiettivi. Da uno stato con due stanze sporche, `Suck`, spostamento, `Suck` è una soluzione ottima di tre azioni.
### Il gioco dell'8
Otto tessere numerate da 1 a 8 su una griglia $3 \times 3$ con una casella vuota; spostando le tessere si deve raggiungere una configurazione ordinata.
- **Stati**: la posizione di ciascuna tessera e della casella vuota (9 simboli, uno per cella: 0 per la vuota). Le disposizioni sono $9! = 362\,880$, di cui solo metà raggiungibili da una data configurazione.
- **Stato iniziale**: una configurazione qualunque, ad esempio dopo aver mescolato le tessere.
- **Azioni**: invece di spostare le tessere (molte mosse diverse per stato), si modella lo spostamento della **casella vuota**: `Left`, `Right`, `Up`, `Down`. Da ogni stato escono al più quattro mosse. Se la casella vuota va su, la tessera sopra di essa scende.
- **Modello di transizione**: lo scambio tra la casella vuota e la tessera adiacente nella direzione scelta.
- **Test obiettivo**: la configurazione ordinata.
- **Costo del cammino**: ogni passo costa 1.

Lo spazio degli stati è un grafo **con cicli**: si torna facilmente su una configurazione già vista.
### Le otto regine
Si devono disporre otto regine su una scacchiera in modo che nessuna ne attacchi un'altra (stessa riga, colonna o diagonale). Conta solo la configurazione finale, non il cammino, quindi il costo del cammino non interessa. Si vedono più formulazioni.
- **Formulazione incrementale ingenua**: stati come disposizioni di 0-8 regine, stato iniziale la scacchiera vuota, azione "aggiungi una regina in una casella vuota", obiettivo otto regine non sotto attacco. Le sequenze da esaminare sono $64 \cdot 63 \cdots 57 \approx 1{,}8 \times 10^{14}$.
- **Formulazione incrementale migliore**: si aggiunge una regina alla volta nella prima colonna libera (partendo da un lato), in una casella **non attaccata** dalle regine già messe. Lo stato iniziale è la scacchiera vuota; gli stati sono disposizioni di $n \leq 8$ regine, una per colonna nelle prime $n$ colonne, nessuna sotto attacco. Gli stati scendono a **2057**.
- **Formulazione a stato completo**: si parte da una scacchiera con una regina per colonna messa a caso e si spostano le regine lungo la propria colonna, cercando di ridurre il numero di coppie che si attaccano. Ogni spostamento è un vantaggio se riduce gli attacchi, uno svantaggio se li aumenta. La si riprende con la ricerca locale.
### Dimostrazione di teoremi
Anche il ragionamento logico è un problema di ricerca. Dalle tavole di verità si sa che, se $A$ e $A \Rightarrow B$ sono vere, in ogni mondo in cui valgono è vera anche $B$: è il **modus ponens**,

$$\frac{A \qquad A \Rightarrow B}{B}$$

Data una base di conoscenza di fatti semplici e implicazioni, chiedersi se una formula $Q$ è vera significa cercare una sequenza di applicazioni del modus ponens che la derivi.
- **Stati**: insiemi di formule proposizionali (la base di conoscenza corrente).
- **Stato iniziale**: le premesse, cioè le formule considerate vere (l'assiomatizzazione del problema).
- **Azioni**: applicare il modus ponens, che **aggiunge** una formula derivata; ogni formula nuova può renderne applicabili altre.
- **Test obiettivo**: lo stato contiene la formula da dimostrare.

> [!example] Una derivazione in due passi (esempio illustrativo)
> Base di conoscenza $\{S,\ S \Rightarrow V,\ V \Rightarrow Q\}$, obiettivo $Q$. Dal primo stato il modus ponens su $S$ e $S \Rightarrow V$ porta a uno stato con in più $V$; da questo, $V$ e $V \Rightarrow Q$ portano a uno stato che contiene $Q$, e il test obiettivo è soddisfatto.

> [!warning] Da verificare
> A lezione è stato mostrato un esercizio d'esame del prof. Zanzotto con una base di conoscenza su una slide non ancora pubblicata; dalla registrazione non si riesce a ricostruire l'insieme esatto di formule né la formula da dimostrare. L'esempio sopra è solo illustrativo: sostituirlo con quello della slide quando sarà disponibile.

Le basi di conoscenza reali (ad esempio i sistemi esperti in medicina) contengono centinaia di formule: trovare la derivazione giusta è come cercare un ago in un pagliaio.

> [!info] Come lavora l'interprete Prolog
> Prolog indicizza i simboli predicativi e le costanti e ragiona **all'indietro**: per soddisfare $P$ cerca le regole $Q \Rightarrow P$ e prende $Q$ come nuovo obiettivo, fino ai fatti.
## Problemi reali
- **Navigazione dei robot**, vista nell'esercitazione del venerdì.
- **Ranking delle risposte di un motore di ricerca**: tra i documenti recuperati si cerca l'ordinamento che mette in prima pagina i più utili. Google non usa solo il PageRank, che è un ingrediente di modelli di machine learning complessi: la ricerca si combina con l'**apprendimento** della funzione di ranking.
## Cercare la soluzione: alberi di ricerca
Si parte dallo stato iniziale e si applicano le azioni: da Arad si generano Sibiu, Timisoara e Zerind, i **successori** candidati all'espansione. La scelta non è indifferente: Zerind porta verso nord-ovest, Sibiu verso est, cioè verso Bucarest, e una ricerca **informata** dovrebbe tenerne conto.

Espandendo ripetutamente i successori si sviluppa un **albero di ricerca**, con lo stato iniziale alla radice. Quando un nodo generato supera il test obiettivo ci si ferma e si ricostruisce la soluzione risalendo l'albero.

> [!info] Domanda a lezione: si minimizza il numero di azioni o il costo?
> Il **costo**. Il piano è costruito in astratto, e ciò che interessa è quanto costerà eseguirlo: un singolo arco tra due città a 1500 km di distanza è un'azione sola, ma costa 1500 km. Le priorità con cui si sceglie quale nodo espandere sono legate al costo, non al numero di passi.
### La frontiera
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
### Nodi e stati
Un nodo dell'albero di ricerca è una struttura dati (in Python, un oggetto o un dizionario) con quattro componenti:
- $n.\mathit{State}$: lo stato a cui corrisponde il nodo, che fa anche da identificatore (Sibiu, Bucarest, oppure un numero);
- $n.\mathit{Parent}$: il nodo che lo ha generato; risalendo di padre in padre fino alla radice si ricostruisce il cammino. Se uno stato è raggiungibile con più cammini, il padre da tenere è quello del cammino **meno costoso**;
- $n.\mathit{Action}$: l'azione applicata al padre per generarlo;
- $n.\mathit{Path\text{-}Cost}$: il costo del cammino dallo stato iniziale al nodo, indicato con $g(n)$.

La funzione $\text{Child-Node}(problem, parent, action)$ costruisce il figlio: stato $\text{Result}(parent.\mathit{State}, action)$, padre $parent$, azione $action$ e costo $g(parent)$ più il costo del passo.

> [!example] Un nodo del gioco dell'8
> Un nodo ha come stato una configurazione della griglia, come padre il nodo della configurazione precedente e come azione `Right`, perché la casella vuota è stata spostata a destra. Quando si raggiunge la configurazione ordinata, risalendo i padri si ottiene la sequenza delle azioni: il piano da consegnare all'agente per l'esecuzione.

Stato e nodo non sono la stessa cosa: lo stato è una configurazione del mondo, il nodo è un elemento dell'albero di ricerca che tiene traccia di come ci si è arrivati. Più nodi possono contenere lo stesso stato.
### Strutture dati per la frontiera
La frontiera non è un insieme ma una **lista ordinata**: i nodi vi entrano con proprietà diverse e alcuni vanno trattati prima di altri. Servono tre operazioni: $\text{Empty?}(\mathit{frontier})$, che dice se è vuota (e quindi se restituire il fallimento); $\text{Pop}(\mathit{frontier})$, che estrae il prossimo nodo; $\text{Insert}(n, \mathit{frontier})$, che inserisce un nodo. Secondo come sono realizzate si ha:
- **coda FIFO** (*first in, first out*): si estrae il nodo inserito per primo, si inserisce in coda;
- **pila LIFO** (*last in, first out*): si estrae l'ultimo inserito, come da una pila di monete; si approfondisce un ramo prima di allargarsi agli altri;
- **coda con priorità**: si estrae il nodo con priorità più alta secondo una funzione di valutazione. La priorità si può modulare, e sarà la chiave delle strategie più efficaci.

> [!quote] Strategia di ricerca
> La strategia di ricerca è determinata interamente dall'**ordine** in cui i nodi della frontiera vengono estratti, cioè da come vengono inseriti nella frontiera.
### Ricerca in ampiezza
Con una coda FIFO si ottiene la ricerca in ampiezza (*Breadth-First Search*), che espande i nodi livello per livello. In questa versione il test obiettivo si fa quando un nodo viene **generato**: se lo stato iniziale è già un obiettivo si restituisce subito, come se all'inizio della partita il pallone fosse già in porta.

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
## Verso la ricerca euristica
La prossima lezione riprende due idee:
- la **ricerca ad approfondimento iterativo**, che combina ampiezza e profondità: si fa una ricerca in profondità con un **limite** sul numero di livelli, aumentandolo a ogni iterazione ($1, 2, 3, \dots$). Così non si diverge scendendo alla cieca, si esplorano tutti i nodi di un livello come in ampiezza e si risparmia la memoria della frontiera;
- le **strategie di ricerca euristica**: si usa come priorità della frontiera una funzione che stima quanto un nodo è **promettente**, cioè dà un punteggio numerico per avvicinarsi al cammino di costo minimo. Inventare buone funzioni euristiche per problemi diversi, da ChatGPT al taxi agli scacchi, è il modo principale per contenere la complessità del grafo generato.

> [!question] Domanda tipica d'esame
> Come si formula un problema di ricerca? Elenca i cinque elementi (stato iniziale, azioni, modello di transizione, test obiettivo, costo del cammino) e applicali a un esempio (Romania, aspirapolvere, gioco dell'8). Perché i costi di passo devono essere maggiori di un $\varepsilon > 0$?

> [!question] Domanda tipica d'esame
> Qual è la differenza tra stato e nodo? Descrivi lo schema generale della ricerca ad albero, il ruolo della frontiera e come la struttura dati scelta (FIFO, LIFO, coda con priorità) determina la strategia di ricerca.
