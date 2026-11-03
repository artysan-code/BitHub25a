---
tags:
  - intelligenza-artificiale
  - logica
  - rappresentazione-della-conoscenza
slide:
  - "004_Knowldege_and_Logic_2026_27_v1.4.pdf"
---
# Agenti basati sulla conoscenza
## Dal linguaggio alla logica
Lezione 5 (19/10/2026), ultima parte: un primo esercizio di traduzione di frasi italiane in formule logiche, che prepara la parte del corso sulla conoscenza. Slide: nessuna, l'esercizio non è nelle slide di 004_Knowldege_and_Logic (che iniziano con la rappresentazione della conoscenza).
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
## Rappresentazione della conoscenza e agenti basati sulla conoscenza
Lezione 8 (28/10/2026): si introduce la **rappresentazione della conoscenza**. La ricerca soffre di problemi di complessità e ha bisogno di euristiche sofisticate, e per costruirle l'agente deve avere un **modello del mondo** esplicito, scritto in un linguaggio logico, da cui **dedurre** nuove credenze. Si vedono il mondo del Wumpus, l'agente basato sulla conoscenza con le operazioni TELL e ASK, la conseguenza logica, il confronto con le basi di dati e con il machine learning, e il valore di una conoscenza **dichiarativa** e trasparente. Slide 004_Knowldege_and_Logic, pp. 1-35.
### Perché rappresentare la conoscenza
Un'euristica è una funzione $h(x)$ che, per ogni $x$ (osservazioni più informazioni di stato), stima il costo della soluzione da lì in poi ([[03 - Risoluzione di problemi mediante ricerca#Ricerca euristica]]). Le funzioni numeriche funzionano bene quando le $x$ sono organizzate in modo **regolare** (continuità, derivabilità, una distanza tra $x_1$ e $x_2$ che permette di usare l'informazione locale di $x_1$ per prevedere $x_2$). Nei problemi reali, spesso discreti, questa regolarità manca: senza una struttura bisognerebbe **enumerare** ogni situazione una per una.

Per questo l'agente si costruisce un'immagine interna del mondo, la **rappresentazione della conoscenza**: non solo l'enumerazione dei valori, ma **strutture** che dicono che certe $x$ appartengono a insiemi con certe proprietà. Si descrivono non le singole istanze ma **forme strutturate** di istanze con proprietà, e la soluzione si cerca sfruttando le proprietà del mondo. Le domande che interessano a un informatico:
1. come si **memorizza** la conoscenza;
2. cosa si **può esprimere** con un certo linguaggio e cosa no;
3. come si ricavano **automaticamente** le conseguenze utili per la ricerca, cioè il **ragionamento automatico**, e con quale complessità.

Due temi ricorrenti:
- l'**ontologia** del dominio: il termine viene dalla filosofia, ma qui indica qualcosa di preciso, cioè come si descrivono gli oggetti del mondo in cui l'agente si muove;
- la **dinamica del mondo**: quando il mondo cambia, una formula che prima era un teorema può smettere di esserlo. La logica classica è **monotona** (i teoremi restano tali aggiungendo conoscenza) e servono meccanismi che gestiscano anche il cambiamento.

Gli **agenti basati sulla conoscenza** non hanno la conoscenza "cablata" nel codice: la procedura di decisione è nel programma, ma la conoscenza è **esterna**, in una base di conoscenza che si interroga come una base di dati. È lo stesso principio dell'**indipendenza logica** nelle basi di dati: se cambia la base di dati, lo stesso software dà risposte diverse.

> [!info] Dalle slide (pp. 3-4)
> Fin qui si sono visti agenti con stato e con obiettivo, più razionali dei reattivi, con stati e azioni descrivibili in modo semplice, e la ricerca con osservabilità parziale (dove si è sottolineata la necessità di modellare le **credenze**). Il mondo è complesso e serve una rappresentazione **parziale e incompleta** di una sua astrazione utile agli scopi dell'agente. Per gli ambienti parzialmente osservabili servono linguaggi di rappresentazione più espressivi e capacità inferenziali. La maggior parte dei problemi di IA è *knowledge intensive*, tanto che "sistemi basati sulla conoscenza" è quasi sinonimo di "sistemi di IA".
### Il mondo del Wumpus
È il gioco usato dal libro di testo: un cavaliere si muove in una griglia sconosciuta per prendere l'oro senza farsi mangiare dal **Wumpus** (un mostro) e senza cadere nelle **buche**. L'ambiente non è osservabile per intero, ma dà percezioni esplicite:
- in ogni cella adiacente a una buca si sente una **brezza**;
- in ogni cella adiacente al Wumpus si sente una **puzza**.

L'agente non ha la mappa: usa le percezioni e la conoscenza di come le percezioni sono legate al mondo, cioè che la brezza indica una possibile buca e la puzza un possibile Wumpus. Questa conoscenza si scrive come regole del tipo $A\Rightarrow B$. Indicando con $B_{i,j}$ "c'è brezza nella cella $(i,j)$" e con $P_{i,j}$ "c'è una buca in $(i,j)$":
$$B_{i,j}\Rightarrow P_{i+1,j}\lor P_{i-1,j}\lor P_{i,j+1}\lor P_{i,j-1}$$
Le formule le scrive il progettista e rappresentano ciò che sa del mondo (un'altra parte dell'IA studia come **apprenderle**). Arrivato in $(i,j)$ e percepita la brezza, l'agente aggiunge il fatto $B_{i,j}$ e con il **modus ponens** ([[03 - Risoluzione di problemi mediante ricerca#Dimostrazione di teoremi]]) da $A\Rightarrow B$ e $A$ ricava la disgiunzione delle buche possibili. Non sa quale sia vera, ma ora sa che una lo è.

Allo stesso modo si definisce cosa è **sicuro**: una cella è $\mathit{OK}$ se non c'è una buca e non c'è il Wumpus,
$$\mathit{OK}_{i,j}\Leftrightarrow\lnot P_{i,j}\land\lnot W_{i,j}$$
Se in una cella non si sente né brezza né puzza, le celle adiacenti sono sicure. L'euristica di esplorazione diventa: vai nelle celle sicure, e se non ce ne sono torna indietro. Una cella che **potrebbe** contenere una buca non è necessariamente pericolosa, ma non ha più la proprietà di essere sicura: è la differenza tra lo **stato del mondo** e le **credenze** dell'agente. Le credenze si combinano: percezioni (cosa è successo, celle già visitate, che restano vere se il mondo non cambia) e regole (come immaginare il mondo dove si sta per andare).

> [!info] Il mondo del Wumpus nelle slide (pp. 5-9, dalle slide)
> - **Misura delle prestazioni**: $+1000$ se trova l'oro, torna in $[1,1]$ ed esce; $-1000$ se muore; $-1$ per ogni azione; $-10$ se usa la freccia.
> - **Percezioni**: puzzo nelle caselle adiacenti al Wumpus; brezza in quelle adiacenti alle buche; luccichio nella casella con l'oro; *bump* se sbatte in un muro; urlo se il Wumpus viene ucciso. L'agente **non percepisce la propria posizione**.
> - **Azioni**: avanti, a destra o a sinistra di 90°, afferra un oggetto, scaglia la freccia (una sola), esce.
> - Gli ambienti sono generati a caso, con $[1,1]$ sempre sicura.
>
> Scenario delle slide: né brezza né puzzo in $[1,1]$, quindi $[1,2]$ e $[2,1]$ sono sicure; l'agente va in $[2,1]$ e percepisce una brezza, quindi c'è una buca in $[2,2]$ o in $[3,1]$; torna in $[1,1]$ e va in $[1,2]$, dove sente puzzo ma non brezza: il Wumpus non può essere in $[1,1]$ né in $[2,2]$ (altrimenti si sentirebbe puzzo in $[2,1]$), quindi è in $[1,3]$, e la buca è in $[3,1]$. Allora $[2,2]$ è sicura; l'agente vi si sposta, poi va in $[2,3]$, dove percepisce un luccichio, afferra l'oro e torna indietro percorrendo caselle sicure. Le coordinate delle slide sono $[colonna,riga]$.
### Un esempio diagnostico
A lezione si è chiesto a ChatGPT come la logica proposizionale entra in un problema di diagnosi medica. I **fatti osservati** (la percezione del medico: la febbre misurata, la tosse riferita dal paziente) sono simboli proposizionali veri o falsi per quel paziente. Le **regole** sono implicazioni come
$$\mathit{Febbre}\land\mathit{Tosse}\Rightarrow\mathit{Influenza}$$
e altre regole possono escludere una diagnosi quando i fatti la contraddicono. Nella slide (p. 10, dalle slide) le regole sono tre: $(\mathit{Febbre}\land\mathit{Tosse})\Rightarrow\mathit{Influenza}$, $(\mathit{MalDiGola}\land\mathit{NasoCheCola})\Rightarrow\mathit{Raffreddore}$ e $\mathit{Influenza}\Rightarrow\lnot\mathit{Raffreddore}$; il sistema conclude che il paziente ha l'influenza e non il raffreddore. È un esempio di **IA simbolica**: la macchina ragiona con regole logiche esplicite invece di basarsi solo su dati e correlazioni, come il machine learning puro. Nella competenza reale serve anche "potrebbe": non solo vero o falso, ma una **probabilità** che una proposizione sia vera.

La logica serve a:
- **descrivere** il mondo con un linguaggio: ci si fermerà poco alla logica proposizionale e si userà la **logica del primo ordine**;
- il **ragionamento automatico**: da una base di conoscenza e da fatti certi, generare nuove formule;
- la **verifica di coerenza**: si toglie una formula $P$ dalla base e si cerca di dimostrare $\lnot P$; se ci si riesce, aggiungere $P$ renderebbe la base **inconsistente** (vere sia $P$ sia $\lnot P$). Con centinaia di migliaia di regole trovare a mano la regola che ne contraddice un'altra è impossibile, e automatizzarlo è essenziale. Gli LLM non hanno un meccanismo di verifica di coerenza, ed è uno dei motivi per cui a volte danno risposte inconsistenti;
- la **spiegazione**: le regole sono scritte in chiaro. Se si è dimostrato $B$ usando $A\Rightarrow B$, e $A$ usando $D\Rightarrow A$ con $D$ vero, alla domanda "perché $B$?" si risponde ripercorrendo la catena di modus ponens. Un sistema logico sa sempre **spiegare** le sue decisioni.

> [!info] Dalle slide (p. 11)
> La slide, anch'essa una risposta di ChatGPT a "perché useresti la logica per problemi di IA?", elenca cinque motivi: rappresentazione della conoscenza (regole e relazioni formali "se $A$ allora $B$"), ragionamento automatico (dedurre nuove informazioni, come un detective con le prove), verifica e coerenza (contraddizioni ed errori nei dati o nei modelli), spiegabilità (medicina, diritto, finanza) e **integrazione con il machine learning** (IA *neuro-simbolica*, più robusta). Corrisponde ai punti sopra più il confronto con il machine learning della sezione seguente.
### Logica e machine learning
Un sistema di machine learning apprende un'ipotesi $h(\mathbf x)$ che approssima la funzione ideale $f(\mathbf x)$, dove $\mathbf x=(x_1,\dots,x_n)$ è un vettore (la scacchiera e la storia della partita, per decidere la prossima mossa). Una rete neurale è un "macchinario" in cui entrano $x_1,\dots,x_n$ ed esce il valore, o un vettore di $k$ valori di cui si prende il massimo (come la parola successiva in un LLM). Si passa da una rappresentazione **discreta** (simboli di un alfabeto finito, formule, regole) a una rappresentazione nel **continuo**, in $\mathbb{R}^n$: è questo il senso delle "rappresentazioni distribuite" (*distribuito* significa che l'informazione sta in posti diversi, su più componenti).

> [!warning] Il machine learning non è l'opposto della logica
> Ogni applicazione di machine learning elenca le dimensioni $x_1,x_2,\dots,x_n$, e questo è un **impegno** (*commitment*) su cosa rappresenta ciascuna: una relazione espressa numericamente, come lo schema di una tabella. Un'immagine diventa un vettore leggendo i pixel in un ordine fisso, tre numeri RGB per pixel; se l'ordine cambiasse da un'immagine all'altra, la rete vedrebbe immagini "follemente diverse" e non potrebbe apprendere nessuna legge regolare. Allo stesso modo, nel labirinto le prime due componenti saranno sempre la posizione $x$ e $y$ del cavaliere. Se il modello logico è sbagliato non c'è niente da apprendere: un sistema fermo al 55% su un problema semplice spesso ha un dato iniziale formalizzato male. Prima si conosce e si rappresenta il problema, poi si apprende.
### L'agente basato sulla conoscenza
Un agente basato sulla conoscenza ha una **base di conoscenza** (KB), un insieme di formule in un linguaggio logico: fatti specifici (dall'esperienza o da un'enciclopedia del dominio) e fatti generali (regole). Nelle slide (p. 27) la base di conoscenza è una rappresentazione esplicita, parziale e compatta in un linguaggio simbolico, e ciò che la caratterizza è la capacità di **inferire nuovi fatti** da quelli memorizzati: da "Socrate è un uomo" e "tutti gli uomini sono mortali" si ricava "Socrate è mortale". Due operazioni:
- **TELL**: aggiunge una formula alla base, ad esempio un fatto appena percepito. È una scrittura permanente, come in una base di dati;
- **ASK**: chiede se una formula è vera, ad esempio se una cella è sicura. La base risponde sì o no deducendo dalle sue formule.
- **RETRACT** (dalle slide, p. 12): ritira una formula dalla base, corrispondente a `retract` in Prolog. Le slide la indicano come funzione possibile accanto a TELL e ASK.

Le risposte di ASK devono essere tali che $\alpha$ sia una conseguenza logica della base (slide pp. 12-13).

In Prolog, TELL corrisponde a `assert` e ASK a una query. Il programma agente, che dall'ambiente riceve una percezione e restituisce un'azione ([[02 - Agenti intelligenti#Il programma agente]]), diventa:

```pseudo
\begin{algorithm}
\caption{KB-Agent($percept$)}
\begin{algorithmic}
\State \textbf{persistenti:} $KB$, la base di conoscenza; $t$, un contatore del tempo, inizialmente 0
\State \Call{Tell}{$KB$, \Call{Make-Percept-Sentence}{$percept, t$}}
\State $action \gets$ \Call{Ask}{$KB$, \Call{Make-Action-Query}{$t$}}
\State \Call{Tell}{$KB$, \Call{Make-Action-Sentence}{$action, t$}}
\State $t \gets t + 1$
\State \Return $action$
\end{algorithmic}
\end{algorithm}
```

- La percezione al tempo $t$ si trasforma in una formula e si scrive nella base (ad esempio "in $(i,j)$ c'è brezza").
- L'azione migliore si ottiene chiedendo alla base, aggiornata con l'ultima percezione, un'azione che rispetti i vincoli del mondo (le regole sulla sicurezza) e sia utile per lo scopo: è una deduzione, come una query Prolog.
- Anche l'azione scelta si scrive nella base, per ricordare a ogni passo cosa si sta facendo.

Il lavoro sta nell'inventare un linguaggio per le percezioni e un algoritmo logico che risponda alle richieste.
#### Conseguenza logica
Rispondere a ASK significa calcolare la **conseguenza logica**:
$$KB\models\alpha$$
$\alpha$ è conseguenza logica di $KB$ se $\alpha$ è vera in **tutti i mondi** in cui sono vere tutte le formule di $KB$. Non vuol dire che $\alpha$ sia vera sempre, ma che lo è in tutti gli stati del mondo compatibili con ciò che l'agente crede: sono gli **stati credenza** visti nella ricerca, tutti gli stati possibili che non si possono distinguere osservando. Il simbolo $\models$ va tenuto distinto dall'implicazione $\Rightarrow$, che è un simbolo del linguaggio. Più l'agente sa, più mondi esclude e più precise sono le risposte. Un processo di risposta che preserva questi mondi **preserva la verità**: si dice consistente (in senso tecnico, *corretto*).

> [!example] Tutti gli uomini sono mortali
> $\forall x\ \mathit{Uomo}(x)\Rightarrow\mathit{Mortale}(x)$ restringe i mondi a quelli in cui gli uomini muoiono. In un romanzo di fantascienza con un immortale la formula è falsa: con una teoria si sceglie di ragionare solo sui mondi che rappresentano la verità che interessa, qui quella biologica.
### Conoscenza dichiarativa
La conoscenza deve essere **dichiarativa**, come nelle basi di dati: nessuna procedura che descriva il mondo, ma un insieme di fatti che ne stabiliscono le proprietà (matricola, nome, cognome...). Conta l'informazione, non come la si costruisce. Una base dichiarativa è:
- **modulare e riusabile**: la regola sulla puzza vale per tutte le celle, e la teoria di un labirinto serve anche in altri labirinti;
- **ispezionabile**: con milioni di regole, la leggibilità dipende dal contenuto linguistico delle formule, come i nomi delle variabili in un programma;
- **modificabile in modo incrementale**: si ritratta un valore e se ne afferma uno nuovo (`retract` e `assert`), come faceva l'algoritmo di apprendimento in tempo reale che aggiornava le stime dell'euristica.

Le slide (pp. 15 e 24-25, dalle slide) elencano gli stessi vantaggi: l'alternativa **procedurale** ha il processo decisionale cablato una volta per tutte, quella dichiarativa è più semplice da ispezionare per valutare la razionalità dell'agente, più facile da arricchire incrementalmente e da modificare a partire dall'esperienza. Aggiungono la **manutenzione semplificata**: se qualcosa va storto (ad esempio "l'erba non è verde"), l'insieme dei fatti da modificare è minimo, e la messa a punto e il raffinamento delle strategie (ad esempio per gestire nuove credenze).
#### Differenza con le basi di dati
> [!example] La distinta base del triciclo
> Una relazione "parte di" dice che un triciclo ha tre ruote, una ruota è fatta di cerchione e copertone, un copertone contiene una camera d'aria. La struttura è **ricorsiva**. In SQL ogni query scende di un numero fissato di livelli: per sapere quante camere d'aria ci sono in un triciclo serve una query diversa a seconda della distanza tra le due parti, e non c'è una sola query che calcoli la **chiusura ricorsiva** della relazione per qualunque profondità. In logica, invece, la dimostrazione attraversa le implicazioni quante volte serve: è una ricerca ricorsiva.

Le slide (pp. 17-19, dalle slide) usano un esempio analogo, *Ferrari ZX600*: "siamo a corto di qualche parte?", "qual è il costo totale di componenti e assemblaggio?". La tabella `Assembly(part, subpart, number)` contiene `trike-wheel-3`, `trike-frame-1`, `frame-seat-1`, `frame-pedal-1`, `wheel-spoke-2`, `wheel-tire-1`, `tire-rim-1`, `tire-tube-1`. Per trovare le componenti serve un join di `Assembly` con se stessa per ogni livello della gerarchia: per ogni interrogazione relazionale (algebra relazionale, SQL-92) è facile trovare un'istanza che lasci fuori qualche componente, inserendola a un livello più basso del numero di join dell'espressione. Estendere SQL si può, introducendo il trattamento **ricorsivo** dei vincoli.

> [!warning] SQL ricorsivo
> Il discorso vale per l'algebra relazionale e l'SQL di base. Dallo standard SQL:1999 esistono le query ricorsive (`WITH RECURSIVE`), che calcolano proprio questo tipo di chiusura: è un'aggiunta al linguaggio per superare il limite descritto a lezione.

Altre differenze: una base di dati vive in un mondo **statico** e adotta l'**ipotesi del mondo chiuso**: ciò che non è dichiarato è falso, e esistono solo gli oggetti memorizzati. Non può generare fatti nuovi perché non ha regole generali che vadano oltre le tuple. Una base di conoscenza, con le sue regole, **deduce** nuovi fatti. Dalle slide (p. 28): le basi di dati contengono solo **fatti specifici e positivi** (tuple come `('Rossi','Paolo', ..., 'Roma')`); la conoscenza è assunta completa (*closed world assumption*), quindi se "Verdi Paolo" non è nella base, l'affermazione che abbia un certo codice fiscale è falsa; i **vincoli di integrità** gestiscono solo la consistenza dei fatti inseriti.
#### Due programmi che fanno la stessa cosa
Due programmi Prolog che stampano il colore di un oggetto (l'esempio è quello di Brachman e Levesque, *Knowledge Representation and Reasoning*):

```prolog
printColor(snow) :- !, write("It's white.").
printColor(grass) :- !, write("It's green.").
printColor(sky) :- !, write("It's yellow.").
printColor(X) :- write("Beats me.").
```

```prolog
printColor(X) :- color(X, Y), !, write("It's "), write(Y), write(".").
printColor(X) :- write("Beats me.").

color(snow, white).
color(sky, yellow).
color(X, Y) :- madeof(X, Z), color(Z, Y).
madeof(grass, vegetation).
color(vegetation, green).
```

Per l'erba il secondo programma trova che è fatta di vegetazione e che la vegetazione è verde. I due programmi sono **funzionalmente identici**, anche negli errori: entrambi dicono che il cielo è giallo. La differenza è che il secondo **sa di più**:
- il primo è anche cattiva programmazione (con infiniti oggetti servirebbero infinite stringhe), ma soprattutto alla domanda "perché è bianco?" può solo rispondere "perché è neve";
- il secondo risponde "perché bianco è il colore della neve": la stampa è ricondotta a una **teoria del mondo** fatta di oggetti, colori e materiali (dalle slide, pp. 20-22: se `color(snow,white)` fosse rimosso dalla base, il programma non stamperebbe più il colore corretto della neve, mentre nel primo programma andrebbe riscritta una regola di stampa). `color` ha come chiave l'identificativo dell'oggetto e come valore un elemento del dizionario dei colori: è un modello **relazionale**, come una tabella, ma che ammette la ricorsione.

Il secondo programma è **trasparente epistemologicamente**. L'epistemologia è la parte della filosofia che studia la realtà non per quello che è, ma per come viene percepita e conosciuta da chi la osserva (come quando si scopre che un amico è diverso da come lo si conosceva all'inizio: cambia la conoscenza, con l'esperienza). Scrivere il codice in questo modo rende evidente perché il programma agisce come agisce: è la base della manutenibilità di un sistema di IA e della **spiegabilità** (*explainable AI*).

> [!quote] Cosa rende un programma basato sulla conoscenza (dalle slide, p. 22)
> Non lo rendono tale l'uso di un linguaggio logico come Prolog, la verità dei fatti rappresentati (`color(sky,yellow)` è falso) né la quantità o la complessità strutturale dei fatti. Lo rende tale la **rappresentazione esplicita** delle conoscenze usate nel processo di calcolo del programma. Il secondo programma, secondo le slide, è più adeguato perché è trasparente epistemologicamente, distingue chiaramente ciò che si conosce da ciò che deve essere eseguito e non dipende da ciò che il sistema sa del *printing* ma da ciò che sa su neve e colori, cioè sull'ambiente.

> [!info] Ragiona passo per passo
> Una delle tecniche con cui gli LLM danno spiegazioni è simulare a parole questo processo logico: scrivendo nel prompt "ragiona passo per passo", il modello non dà subito la risposta ma genera i passi intermedi della decisione. È però un comportamento appreso: il ragionamento esposto può non corrispondere a quello che il sistema ha davvero fatto.
#### L'atteggiamento intenzionale
Il filosofo Daniel Dennett chiama **atteggiamento intenzionale** (*intentional stance*) il descrivere un sistema separando ciò che sa da ciò che fa: "stampo il colore perché conosco il colore", cioè l'azione è giustificata dalla conoscenza. Uno dei motivi per cui agli LLM si contesta di essere davvero intelligenti è che le loro spiegazioni non corrispondono a una catena deduttiva: il modo in cui decidono e la storia che raccontano sul perché non coincidono. In un sistema logico con le regole in chiaro coincidono, e per questo questi sistemi venivano considerati **agenti intenzionali**. Una parte della storia dell'IA ha perseguito questa strada: agenti che decidono come i matematici, per deduzione rigorosa. Nelle slide (pp. 23 e 26, dalle slide) il riferimento è a Dennett (1991, *Intentional Systems*) e i sistemi basati sulla conoscenza sono quelli per cui le posizioni intenzionali sono giustificate dalla rappresentazione in simboli sin dal progetto; la logica ne è una possibile implementazione, con la **rappresentazione** (enunciati di logica proposizionale o del primo ordine) e il **ragionamento** (dedurre le conseguenze logiche dei fatti e degli assiomi).

Rispetto ai [[02 - Agenti intelligenti#Tipi di agente|tipi di agente]] (reattivi, basati su modello, con utilità, che apprendono), l'idea è che il **modello** dell'agente, per prevedere bene le credenze, va espresso in una rappresentazione logica della conoscenza.
### Interpretazione e significato
Ci sono due mondi: quello della **rappresentazione**, nella memoria dell'agente, e il **mondo reale**, l'ambiente. Una formula come $\mathit{Color}(\mathit{snow},\mathit{white})$ parla di un aspetto del mondo. Dare significato a una formula non vuol dire dichiararla vera o falsa, ma avere un modo di leggerla (ad esempio fissare il significato di variabili e quantificatori) e di confrontarla con il mondo: è l'**interpretazione**. A seconda di come è fatto il mondo la formula è vera o falsa: $\mathit{Color}(\mathit{sky},\mathit{yellow})$ è falsa, $\mathit{Color}(\mathit{sky},\mathit{blue})$ è vera, salvo nuvole.

Il vantaggio è questo: se le formule della base sono vere nel mondo e il sistema deduce che una formula nuova ne è conseguenza logica, allora la nuova formula, con la stessa interpretazione, è una proprietà vera del mondo, **ottenuta senza andare nel mondo**. Un robot può ragionare in astratto su cosa succederebbe se facesse certe azioni, prima di farle: è il vantaggio che abbiamo sugli animali, che conoscono il mondo solo facendone esperienza.

I linguaggi diventeranno via via più espressivi: con le **variabili** pochi simboli esprimono molta informazione implicita e descrivono insiemi di mondi senza sapere esattamente in quale ci si trova ("la moglie di Rossi" può essere Paola, Maria, Giuseppina...). Ma più espressività significa un calcolo della conseguenza logica più difficile: le interpretazioni possibili crescono in modo esponenziale, 
### Espressività e complessità
Sezione integrata dalle slide (pp. 29-35), in parte già toccata sopra con l'esempio della moglie di Rossi.
- **Formalismo per la rappresentazione della conoscenza** (p. 34): ha tre componenti, una **sintassi** (vocabolario e regole per formare gli enunciati), una **semantica** (corrispondenza tra enunciati e fatti del mondo: se un enunciato è nella base, l'agente crede che il fatto corrispondente sia vero) e un **meccanismo inferenziale** (con o senza regole di inferenza) che permette di inferire nuovi fatti, cioè la conseguenza logica. Lo schema delle pp. 29 e 35 è quello di sopra: formule e nuove formule da un lato (conseguenza logica), aspetti reali del mondo e nuovi aspetti reali, cioè veri, dall'altro, collegati dalla semantica.
- **Trade-off fondamentale** (p. 30): trovare il giusto compromesso tra **espressività** del linguaggio e **complessità** del meccanismo inferenziale; si vogliono linguaggi espressivi ma anche efficienti, e i due obiettivi sono in contrasto.
- **Espressività come imprecisione** (pp. 31-33): un linguaggio più espressivo permette di essere vaghi, esprimere conoscenza parziale, omettere dettagli; determina non tanto ciò che si può dire quanto ciò che si può **lasciare non detto**. Nelle basi di dati si esprime solo `Moglie(Rossi, Paola)`; con linguaggi più espressivi si dice $\exists x\;\mathit{Moglie}(\mathit{Rossi},x)$ (Rossi ha una moglie), $\lnot\mathit{Operaio}(\mathit{Rossi})$, $\mathit{Moglie}(\mathit{Rossi},\mathit{Anna})\lor\mathit{Moglie}(\mathit{Rossi},\mathit{Paola})$, $\forall y\;(\exists x\;\mathit{Moglie}(y,x))\Rightarrow\mathit{Coniugato}(y)$.
- **Complessità inferenziale** (p. 33): dai fatti $\exists x\;\mathit{Moglie}(\mathit{Rossi},x)$ e dalla regola sui coniugati si deduce $\mathit{Coniugato}(\mathit{Rossi})$; lo si deduce anche dalla disgiunzione $\mathit{Moglie}(\mathit{Rossi},\mathit{Anna})\lor\mathit{Moglie}(\mathit{Rossi},\mathit{Paola})$, ma è più complicato perché richiede un **ragionamento per casi**. Nelle basi di dati nessuna deduzione è possibile, solo recupero.

> [!question] Domanda tipica d'esame
> Cos'è un agente basato sulla conoscenza? Descrivi le operazioni TELL e ASK, il programma KB-Agent e cosa significa $KB\models\alpha$. Perché una conoscenza dichiarativa è preferibile a una procedurale? Traccia: base di conoscenza esterna al codice, percezioni come formule, azioni dedotte, conseguenza logica come verità in tutti i mondi che soddisfano la base; modularità, ispezionabilità, spiegabilità (i due programmi Prolog sul colore).
### Prossimi passi
Venerdì c'è un'esercitazione in aula, di nuovo in Python. La lezione riprende lunedì da qui: come combinare le formule della base di conoscenza per calcolare la conseguenza logica.
## Logiche, ontologie e logica proposizionale
Lezione 9 (02/11/2026): la conoscenza permette di calcolare gli stati possibili del mondo e le loro proprietà **prima** dell'esperienza, cioè di ragionare non sul mondo che si vede ma su come sarà dopo le proprie azioni, riducendo i tentativi: è di nuovo un'**euristica fondata sulla conoscenza**. Si fa una panoramica delle logiche e dei problemi che pongono (incertezza, credenze, non monotonia), si introduce il concetto di **ontologia**, si scrive in Prolog il mondo dei blocchi e si ripassano sintassi e semantica della **logica proposizionale**, fino a conseguenza logica, model checking e regola di **risoluzione** (AIMA cap. 7). Slide 004_Knowldege_and_Logic, pp. 36-48 e 53-54 (blocchi in Prolog), saltando gli esercizi alle pp. 51-52 e 55. La parte su sintassi, semantica, model checking e risoluzione della logica proposizionale **non è in questo PDF** (le slide si fermano a "che cosa vedremo", p. 48): va confrontata con le slide successive.
### Due linguaggi
- **Logica proposizionale**: i simboli (lettere maiuscole) sono **proposizioni** vere o false, e i connettivi costruiscono formule di complessità arbitraria. Il calcolo della conseguenza logica è **decidibile**, e se ne vedranno gli algoritmi (dalle slide, p. 39: il problema è decidibile ma **intrattabile**, NP).
- **Logica del primo ordine** (*first order logic*): descrive le **relazioni** tra gli individui $x,y$ di un dominio, che possono o no avere certe proprietà; si predica sul singolo individuo, con variabili e quantificatori. Una procedura che sia veloce, efficiente e completa e dia sempre una risposta **non esiste**.

> [!warning] Precisazione dalle slide
> Le slide (p. 39) dicono più precisamente che il problema $KB\models\alpha$ in logica del primo ordine è solo **semidecidabile**: il meccanismo inferenziale non è decidibile (esiste una procedura che termina se $\alpha$ è conseguenza, ma non sempre se non lo è). L'affermazione a lezione va letta in questo senso.

Più cose si possono dire, meno efficiente è il calcolo della conseguenza logica: si paga uno scotto in complessità. Per questo bisogna saper **strutturare** la conoscenza del dominio, usando meno formule possibili; esistono tecniche come le **reti semantiche** e i **frame**, template di conoscenza riutilizzabili in molti domini, come i pattern nella programmazione.

Dalle slide (p. 40) i modi per ottenere linguaggi più efficienti sono due: contrarre il primo ordine verso **linguaggi a inferenza limitata** con proprietà computazionali migliori (la programmazione logica, le **logiche descrittive**) oppure usare linguaggi che **strutturano** la conoscenza per guadagnare efficienza su forme particolari di inferenza (reti semantiche e connettività, frame e aggregazione, ereditarietà), lasciando il primo ordine per la semantica. Le slide (p. 41) citano tre limiti di espressività della logica del primo ordine nel ragionamento di senso comune: atteggiamenti proposizionali, ragionamento incerto, ragionamento non monotono, trattati sotto.
### Oltre il vero e il falso
- **Ragionamento incerto**: "è molto probabile che i prezzi salgano ad aprile" non si scrive in logica senza un modello di incertezza. Le slide (p. 43) citano come esempi "sicuramente pioverà" e "Aldo è alto", e i modi per superare la dicotomia vero/falso: logiche a più valori (vero, falso, non so), ragionamento probabilistico ($P(a)$), vero con un grado di fiducia $c$, logica fuzzy (proprietà sfumate, ad esempio "alto" come aspettativa nell'intervallo tra 1 m e 2,30 m). Si può pensare che, tra i mondi possibili ad aprile, la maggior parte siano quelli in cui i prezzi salgono. Gran parte della ricerca ha costruito teorie complesse in logica del primo ordine aggiungendo poi le probabilità con un'euristica; si possono anche immaginare linguaggi che includono direttamente la probabilità.
- **Atteggiamenti proposizionali e logiche epistemiche**: "credo che $P$", "sono sicuro di $P$". Non si dichiara qualcosa su un individuo, ma su come sono fatti i mondi in cui gli individui vivono, secondo un soggetto: una semantica **soggettiva**, in cui le credenze di agenti diversi vanno tenute separate. Le slide (p. 42, dalle slide) distinguono atteggiamenti **epistemici** (conoscenze, credenze) e **motivazionali** (desideri, obiettivi, intenzioni): l'oggetto del discorso non sono più solo fatti o regole ma intere proposizioni, con $\mathit{Bel}(P)$ (operatori e logiche modali) oppure $\mathit{Bel}('P')$ (**reificazione**, o meta-livello).
- **Logiche modali**: "in tutti i mondi possibili $P$" (necessità). Il ragionamento sui mondi possibili è complicato: "il Cavaliere", "Silvio Berlusconi" e "il Presidente del Consiglio" indicano la stessa persona in certi mondi, ma in un mondo in cui non avesse vinto le elezioni non più. Credere che qualcosa accada significa restringersi ai mondi in cui accade.
- **Logiche a tre valori**: oltre a vero e falso c'è "non so" (ad esempio $0{,}5$), e gli operatori vanno ridefiniti anche su quel valore, come per i `NULL` nelle basi di dati: la negazione di "non so" resta "non so"?
- **Ragionamento probabilistico**: a ogni regola si associa la probabilità che sia vera, e combinando due regole bisogna sapere come si propaga l'incertezza. Conviene privilegiare le inferenze che restano probabili: partire da regole affidabili e arrivare a combinazioni pochissimo probabili rende il ragionamento inaffidabile. La probabilità **frequentista** è la frequenza dei successi su molte prove (il dado, o il meccanico che ha visto rompersi il radiatore nel 90% dei casi); quella **soggettiva** è un grado di fiducia che non viene da nessuna frequenza (i concorrenti di "Affari tuoi" che scelgono un pacco).
- **Logica fuzzy** (della vaghezza): una formula è vera con un **grado** tra 0 e 1 che non è una probabilità (non somma a 1), ma ordina le regole dalla più certa alla meno certa.
### Ragionamento non monotono
> [!example] La gallina Giuseppina
> Una base di conoscenza contiene $\forall x\ \mathit{Uccello}(x)\Rightarrow\mathit{Vola}(x)$ e $\forall x\ \mathit{Gallina}(x)\Rightarrow\mathit{Uccello}(x)$. Si aggiunge $\mathit{Gallina}(\mathit{Giuseppina})$, e in due passi si deduce $\mathit{Vola}(\mathit{Giuseppina})$. Ma le galline non volano: aggiungendo un fatto, una base che era corretta descrive male il mondo.

La logica classica è **monotona** (dalle slide, p. 44: se $KB\models\alpha$ allora $KB\cup\{\beta\}\models\alpha$): aggiungendo conoscenza i teoremi possono solo aumentare. Il senso comune non lo è: aggiungere un fatto può **ridurre** quello che si può concludere, perché regole vere "in generale" hanno eccezioni. Due strategie:
- **default**: in mancanza di altre informazioni un uccello vola, ma per le galline vale l'eccezione $\lnot\mathit{Vola}$; si ragiona per default a meno di trovarsi in un caso di eccezione;
- **mondo chiuso**: tutto ciò che non si sa è falso, come nelle basi di dati. Le slide usano l'esempio di Tweety (gli uccelli tipicamente volano, Tweety è un uccello, quindi vola) per il default, e osservano che con l'assunzione di mondo chiuso un nuovo fatto può invalidare le vecchie conclusioni.

Le slide di riepilogo (pp. 49-50, dalle slide, non visto a lezione) collegano la non monotonia al *frame problem* e indicano come soluzioni le tecniche che estendono la logica classica, come gli atteggiamenti proposizionali e le logiche di default.

> [!info] Non monotonia e machine learning
> Una rete neurale apprende dai dati una funzione euristica che dipende dal contesto, ed evita di ragionare in modo monotono: un sistema come ChatGPT si comporta diversamente con "gallina" e con "uccello" perché ha imparato i due comportamenti istanza per istanza. Avendo visto molte galline, il default è già incorporato nella teoria appresa, e non serve una regola generale come "tutti gli uccelli volano". Se ne riparlerà con il machine learning.
### Ontologia
Lo schema logico di una base di dati è un **modello del mondo**: dire che uno studente ha matricola (chiave, non nulla, univoca), nome, cognome e residenza è una teoria assiomatica del tipo "ogni studente esiste con una matricola che lo descrive così", un vincolo che ogni dato scritto in memoria deve rispettare (un requisito, nell'analisi dei requisiti). Per un agente che vive dentro quella memoria, il mondo è **solo** quello: ciò che non sta nello schema non esiste, e due schemi diversi creano due mondi tra cui è difficile trasferire dati. Lo stesso vale in piccolo per le strutture dati di un qualunque programma.

In filosofia l'**ontologia** studia i caratteri universali dell'essere in quanto tale, a prescindere da come appare (Kant e le sue categorie). La filosofia analitica, da Leibniz con la sua *characteristica universalis*, ha cercato un linguaggio formale in cui scrivere il pensiero per calcolarne automaticamente la verità. In informatica un'ontologia è la **rappresentazione formale** di un dominio (la medicina, una partita di scacchi): un insieme di concetti e di relazioni possibili tra concetti, che costituisce l'unico perimetro del mondo in cui l'agente può muoversi. Logiche più ricche hanno ontologie più complesse: per tutti i mondi possibili (logiche modali), o temporali (formule vere in certi istanti e non in altri).

Ad esempio la regola Prolog del colore vista nella [[04 - Agenti basati sulla conoscenza#Due programmi che fanno la stessa cosa|lezione precedente]] in logica dei predicati diventa
$$\forall x\,\forall y\ \big(\exists z\ \mathit{MadeOf}(x,z)\land\mathit{Color}(z,y)\big)\Rightarrow\mathit{Color}(x,y)$$
È una **regola ontologica**: dice che un oggetto ha un colore o direttamente o dal materiale di cui è fatto (con un default: a meno di conoscerne già il colore). E dice anche che cosa **esiste**: le costanti `snow`, `sky`, `grass`, `vegetation`, `green`, a cui si è dato un nome. In un programma logico esiste ciò che è citato come costante.

Dalle slide (pp. 45-47, dalle slide):
- ogni linguaggio per la rappresentazione della conoscenza fa **assunzioni ontologiche** diverse su come è fatto il mondo: nel calcolo proposizionale è popolato di fatti veri o falsi; nel calcolo dei predicati di oggetti con proprietà e relazioni; logiche specializzate assumono ontologie più ricche (stati e azioni nel *calcolo di situazioni*, il tempo nelle logiche temporali, concetti o categorie nelle logiche descrittive);
- un programma logico definisce formalmente ciò che esiste (esiste `snow`? sì; il `wumpus`? no), ciò che lo caratterizza (il colore di `sky` è `yellow`) e le relazioni tra le cose (`grass` è `madeof` `vegetation`).
### Il mondo dei blocchi
Cinque blocchi $A,B,C,D,E$ in due pile: $A$ su $B$ su $C$, e $D$ su $E$. Per descriverlo serve un linguaggio:
- un **vocabolario di costanti** `a`, `b`, `c`, `d`, `e`: un patto tra programmatore e utente per cui la costante `a` indica il blocco $A$. Non è l'unica scelta possibile, ma ogni costante sta al posto di un'entità della realtà. Un simbolo non ha un'interpretazione banale: in C il carattere `'1'` e il numero `1` sono cose diverse;
- un predicato **binario** `on(X, Y)`, "$X$ è direttamente sopra $Y$", definito **estensivamente** come insieme di coppie: `on(a, b)`, `on(b, c)`, `on(d, e)`. Definire un predicato significa definire una relazione, un sottoinsieme del prodotto cartesiano del vocabolario con se stesso, come nelle basi di dati;
- predicati **unari** (proprietà di un oggetto): `clear(a)`, `clear(d)` (nulla sopra), `isablock(X)` per tutti e cinque, e `table(c)`, `table(e)` (appoggiati sul tavolo, dalle slide, p. 37).

Le slide (p. 37) introducono l'esempio con un **dominio** $\{a,b,c,d,e\}$, le **funzioni** (ad esempio $\mathit{Hat}$, che dato un blocco dà quello che ci sta sopra: $\mathit{Hat}(b)=a$) e le **relazioni**: $\mathit{On}/2=\{\langle a,b\rangle,\langle b,c\rangle,\langle d,e\rangle\}$, $\mathit{Clear}/1=\{a,d\}$, $\mathit{Table}/1=\{c,e\}$, $\mathit{Block}/1=\{a,b,c,d,e\}$.

Prima di scrivere `on(a, b)` bisogna sapere come i simboli si interpretano nel mondo: nel mondo non si trovano `a` e `b`, ma i blocchi. Con queste definizioni si possono fare domande: quali blocchi si possono prendere (`takeable(X) :- clear(X).`, che dà `a` e poi `d`), oppure su cosa sta $A$ (`on(a, X)`, risposta `X = b`). Le slide (p. 54, dalle slide, non visto a lezione) aggiungono `movable(Origin, End) :- takeable(Origin), takeable(End), Origin \== End.`, che risponde a "quali blocchi posso muovere, e come?".

La relazione "sopra", non solo a contatto diretto, è la **chiusura transitiva** di `on`, e si definisce in modo induttivo:

```prolog
above(X, Y) :- on(X, Y).
above(X, Y) :- on(X, Z), above(Z, Y).
```

> [!warning] Attenzione all'ordine
> Scrivere la seconda regola come `above(X, Y) :- above(X, Z), on(Z, Y).` porta a una **ricorsione infinita**: l'interprete Prolog fa una ricerca in profondità e richiama `above` prima di aver consumato un fatto. È il programmatore a dover essere sveglio e mettere prima `on`, che trova un blocco a contatto diretto, e poi la chiamata ricorsiva.

Se si cambia la disposizione dei blocchi cambiano solo i **fatti** (`on`, `clear`), non le regole (`takeable`, `above`): la teoria resta la stessa e dà conseguenze diverse in un mondo possibile diverso. La logica resta fissa, e cambiano la verità e la falsità di alcune proprietà al cambiare del mondo.
#### Grounding
Dalle slide (pp. 36 e 38, dalle slide, non visto a lezione): come sappiamo che la base è vera nel mondo reale e come l'agente forma le credenze? Attraverso i **sensori** si crea la connessione con il mondo, e le credenze sono il risultato di percezioni: nel mondo dei blocchi si accettano fatti come $\mathit{Clear}(a)$, $\mathit{On}(d,e)$, $\mathit{Table}(c)$ ma non $\mathit{Clear}(c)$, $\mathit{On}(c,a)$, $\mathit{Table}(b)$. Le regole sono invece il risultato di un processo di **apprendimento** (ad esempio il ricordo di osservazioni precedenti, come in LRTA\*), che può essere fallibile: il ragionamento induttivo per esempi può portare a generalizzazioni sbagliate o a inferenze inconsistenti, e le osservazioni possono avere rumore.
### Sintassi della logica proposizionale
Una formula è **atomica** o **complessa**:
- atomiche: le costanti $\mathit{True}$ e $\mathit{False}$ (vere o false in qualunque stato del mondo, a differenza di un simbolo come $T$ che può essere vero o falso) e i simboli proposizionali;
- complesse: $(\varphi)$, $\lnot\varphi$, $\varphi\land\psi$, $\varphi\lor\psi$, $\varphi\Rightarrow\psi$ (con antecedente e conseguente, *left hand side* e *right hand side*), $\varphi\Leftrightarrow\psi$ (vere nelle stesse condizioni).

La **precedenza** degli operatori, dalla più alta: $\lnot$, $\land$, $\lor$, $\Rightarrow$, $\Leftrightarrow$. Ad esempio $\lnot P\lor Q\land R\Rightarrow S$ si legge $\big((\lnot P)\lor(Q\land R)\big)\Rightarrow S$: un albero con le proposizioni nelle foglie e i connettivi nei nodi interni.
### Semantica, modelli e conseguenza logica
Dare un valore di verità a una formula non è "far girare il programma": il progettista della base di conoscenza deve sapere cosa significa ogni simbolo nel mondo (se $P$ è "la temperatura è alta"). Un'**interpretazione** assegna un valore di verità a ogni simbolo proposizionale in base allo stato del mondo; il valore di una formula complessa si calcola da quello delle componenti, risalendo l'albero come con le tabelle di verità. Un'interpretazione che rende vera una formula è un **modello** della formula.

Nel mondo del Wumpus $P_{3,1}$ significa "c'è un pozzo nella cella $(3,1)$", $W_{1,3}$ "c'è il Wumpus in $(1,3)$". La semantica non viene da noi, ma dallo stato del mondo: le regole sono vere in tutti i mondi, i fatti si verificano con l'esperienza (sono in una cella vicina a un pozzo e sento la brezza: aggiungo il fatto).

> [!quote] Conseguenza logica
> $KB\models\alpha$ se e solo se ogni modello di $KB$ è anche un modello di $\alpha$:
> $$M(KB)\subseteq M(\alpha)$$

Restringendosi ai modelli della base di conoscenza (gli assiomi in cui si crede), $\alpha$ resta vera. Come in analisi: un teorema vale per le funzioni continue su un intervallo chiuso e limitato, e fuori dalle ipotesi può succedere di tutto. Se $KB$ è inconsistente (contiene ad esempio $P\land\lnot P$) non ha modelli.

> [!example] Pozzi nel mondo del Wumpus
> La base di conoscenza contiene le regole del Wumpus e le percezioni: nessuna brezza in $(1,1)$, brezza in $(2,1)$. Le celle incerte sono $(1,2)$, $(2,2)$ e $(3,1)$, quindi i mondi possibili sono $2^3=8$, e la base di conoscenza è vera in 3 di essi.
> - $\alpha_1=\lnot P_{1,2}$ (nessun pozzo in $(1,2)$, cioè la cella è sicura) è vera in tutti e 3: $KB\models\alpha_1$.
> - $\alpha_2=\lnot P_{2,2}$ è falsa in 2 dei 3 modelli della base: $KB\not\models\alpha_2$, e non si può dedurre.
>
> Può sembrare strano: i modelli di $\alpha_2$ non includono quelli della base, mentre quelli di $\alpha_1$ sì. Ma non interessano gli altri mondi: interessa solo che, stando dentro i modelli della base, la formula non possa essere falsa.

Il problema computazionale è che per decidere se $KB\models\alpha$ enumerando i mondi bisogna considerarne un numero **esponenziale**: servono algoritmi migliori.
### Equivalenze, validità e soddisfacibilità
Due formule sono **logicamente equivalenti** se hanno gli stessi modelli: si può riscrivere l'una nell'altra senza cambiare significato. Ad esempio $\lnot\lnot\alpha\equiv\alpha$, $\alpha\Leftrightarrow\beta\equiv(\alpha\Rightarrow\beta)\land(\beta\Rightarrow\alpha)$, $\alpha\Rightarrow\beta\equiv\lnot\alpha\lor\beta$, le leggi di **De Morgan** $\lnot(\alpha\land\beta)\equiv\lnot\alpha\lor\lnot\beta$ e $\lnot(\alpha\lor\beta)\equiv\lnot\alpha\land\lnot\beta$ (le stesse del complemento di intersezione e unione di insiemi), commutatività, associatività, distributività. Le si dà per note dal corso di logica; dimostrarle significa calcolare esplicitamente la semantica.

Una base di conoscenza è un insieme di assiomi $A_1,\dots,A_n$, ma equivale a una sola formula, la congiunzione $A_1\land\dots\land A_n$.
- Una formula è **valida** (una tautologia) se è vera in **tutti** i mondi possibili.
- Una formula è **soddisfacibile** se è vera in **almeno un** mondo (almeno una situazione del Wumpus la rende vera); è **insoddisfacibile** se tutte le interpretazioni la rendono falsa.
- $\alpha$ è valida se e solo se $\lnot\alpha$ è insoddisfacibile: sono due modi di dire la stessa proprietà.
### Model checking
L'inferenza si può fare per **enumerazione dei modelli** (*model checking*): con un vocabolario di $n$ simboli si costruiscono le $2^n$ righe della tabella di verità, si tengono solo quelle in cui la base di conoscenza (la congiunzione delle sue formule) è vera, e si controlla che in tutte sia vera anche $\alpha$.

> [!example] Esempio
> Con $KB=(A\lor C)\land(B\lor\lnot C)$ e $\alpha=A\lor B$: tre simboli, 8 interpretazioni. La base di conoscenza è vera in 4 righe, e in tutte e 4 è vera anche $A\lor B$, quindi $KB\models\alpha$.

> [!warning] Da verificare
> Dalla registrazione non si ricava con certezza la formula dell'esempio alla lavagna, che ha una base di conoscenza formata da due disgiunzioni e un'$\alpha$ disgiuntiva. Quello sopra è l'esempio standard della stessa forma. Le slide 004_Knowldege_and_Logic non contengono il model checking: confrontarlo con le slide successive della logica proposizionale.

È l'algoritmo più costoso possibile, $2^n$ interpretazioni: sostanzialmente forza bruta, non applicabile su basi di conoscenza grandi.
### Deduzione e risoluzione
L'alternativa è il **metodo deduttivo**: si applicano regole di inferenza alle formule della base di conoscenza, riscrivendole, finché si ottiene $\alpha$. È di nuovo un processo di ricerca, che enumera teoremi finché incontra $\alpha$. Si scrive $KB\vdash\alpha$ ($\alpha$ è **derivabile**), distinto da $KB\models\alpha$ (semantico). Le regole devono:
- essere **corrette** (*sound*): riscrivere senza cambiare il significato, cioè derivare solo conseguenze logiche;
- essere **complete**: per ogni $\alpha$ che è conseguenza logica deve esistere una derivazione che la trova.

I metodi visti nel corso di logica (tabelle di verità, deduzione naturale, tableaux) hanno molte regole, e scegliere quale applicare lascia troppo non determinismo. In IA si vuole **una sola regola**, da applicare sempre, concentrando il non determinismo nella scelta di dove applicarla: la **risoluzione**.

Il modus ponens ne è un caso particolare: $P\Rightarrow R$ equivale a $\lnot P\lor R$, e da $P$ e $\lnot P\lor R$ si ottiene $R$, perché $P$ e $\lnot P$ non possono essere veri insieme. In generale, date due **clausole** (disgiunzioni di letterali) che contengono un letterale e la sua negazione:
$$\frac{P\lor Q\qquad\lnot P\lor R}{Q\lor R}$$
la clausola risolvente è la disgiunzione di ciò che resta. A ogni passo un letterale sparisce; dato che i letterali sono finiti, o non si può più andare avanti, o si arriva alla **clausola vuota**, una disgiunzione senza letterali, sempre falsa: una **contraddizione**. La risoluzione si usa per **confutazione**, come fa Prolog: per dimostrare $\alpha$ si cerca una contraddizione in $KB\land\lnot\alpha$. Il metodo riduce rapidamente i simboli in gioco, e con la gestione delle variabili sarà il meccanismo usato per la logica del primo ordine. È corretto (non cambia i modelli) e completo: regalato a un agente, gli permette di ragionare in modo efficiente.

> [!info] A cosa serve in IA
> La logica qui non serve a studiare le formule in sé, ma a calcolare una soluzione come cammino di azioni nei mondi possibili: predicati come `on`, `takeable`, `clear`, `above` servono a calcolare in fretta, euristicamente, le configurazioni utili.
### Esercizi proposti dalle slide
Dalle slide, non visti a lezione (pp. 51-52 e 55):
- scrivere in Prolog la **mappa della Romania**: città come costanti in minuscolo, archi come relazione binaria `PArco/2`, ambiente come fatto sullo stato (posizione dell'agente, costo del cammino), azioni come transizioni su `PArco/2`, piano come lista ordinata di `PArco/2`, algoritmo di ricerca come query Prolog;
- descrivere in modo relazionale in Prolog il gioco del 15, il Vacuum Cleaner e le otto regine, e scrivere la formula di una delle euristiche viste per ciascuno; descrivere in Prolog il mondo dei blocchi e rispondere a "quali blocchi posso prendere?" e "su quale blocco è posizionato $A$?" (fatto a lezione);
- le slide riportano anche la soluzione delle **torri di Hanoi** in Prolog (`move/5`, `hanoi/5`): per spostare $N$ dischi da $X$ a $Z$ si spostano prima $N-1$ dischi da $X$ a $Y$, poi il disco più grande da $X$ a $Z$, infine gli $N-1$ dischi da $Y$ a $Z$, concatenando i tre piani con `append`; per $N=3$ il piano è `[[X,Z],[X,Y],[Z,Y],[X,Z],[Y,X],[Y,Z],[X,Z]]`.

> [!question] Domanda tipica d'esame
> Cosa significa $KB\models\alpha$? Mostralo nel mondo del Wumpus con i modelli. Qual è la differenza tra validità e soddisfacibilità, e tra conseguenza logica e derivabilità? Cosa significa che un sistema deduttivo è corretto e completo? Enuncia la regola di risoluzione e spiega perché si usa per confutazione.
### Prossimi passi
Mercoledì si riprende dall'inferenza deduttiva, guardando il calcolo della conseguenza logica come in un tableau.
