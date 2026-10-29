---
tags:
  - intelligenza-artificiale
  - rappresentazione-della-conoscenza
  - logica
slide: []
---
# Agenti basati sulla conoscenza
Lezione 10 (28/10/2026): si introduce la **rappresentazione della conoscenza**. La ricerca soffre di problemi di complessità e ha bisogno di euristiche sofisticate, e per costruirle l'agente deve avere un **modello del mondo** esplicito, scritto in un linguaggio logico, da cui **dedurre** nuove credenze. Si vedono il mondo del Wumpus, l'agente basato sulla conoscenza con le operazioni TELL e ASK, la conseguenza logica, il confronto con le basi di dati e con il machine learning, e il valore di una conoscenza **dichiarativa** e trasparente. Le lezioni 5-9 non sono presenti negli appunti.
## Perché rappresentare la conoscenza
Un'euristica è una funzione $h(x)$ che, per ogni $x$ (osservazioni più informazioni di stato), stima il costo della soluzione da lì in poi ([[04 - Ricerca non informata e ricerca euristica#Ricerca euristica]]). Le funzioni numeriche funzionano bene quando le $x$ sono organizzate in modo **regolare** (continuità, derivabilità, una distanza tra $x_1$ e $x_2$ che permette di usare l'informazione locale di $x_1$ per prevedere $x_2$). Nei problemi reali, spesso discreti, questa regolarità manca: senza una struttura bisognerebbe **enumerare** ogni situazione una per una.

Per questo l'agente si costruisce un'immagine interna del mondo, la **rappresentazione della conoscenza**: non solo l'enumerazione dei valori, ma **strutture** che dicono che certe $x$ appartengono a insiemi con certe proprietà. Si descrivono non le singole istanze ma **forme strutturate** di istanze con proprietà, e la soluzione si cerca sfruttando le proprietà del mondo. Le domande che interessano a un informatico:
1. come si **memorizza** la conoscenza;
2. cosa si **può esprimere** con un certo linguaggio e cosa no;
3. come si ricavano **automaticamente** le conseguenze utili per la ricerca, cioè il **ragionamento automatico**, e con quale complessità.

Due temi ricorrenti:
- l'**ontologia** del dominio: il termine viene dalla filosofia, ma qui indica qualcosa di preciso, cioè come si descrivono gli oggetti del mondo in cui l'agente si muove;
- la **dinamica del mondo**: quando il mondo cambia, una formula che prima era un teorema può smettere di esserlo. La logica classica è **monotona** (i teoremi restano tali aggiungendo conoscenza) e servono meccanismi che gestiscano anche il cambiamento.

Gli **agenti basati sulla conoscenza** non hanno la conoscenza "cablata" nel codice: la procedura di decisione è nel programma, ma la conoscenza è **esterna**, in una base di conoscenza che si interroga come una base di dati. È lo stesso principio dell'**indipendenza logica** nelle basi di dati: se cambia la base di dati, lo stesso software dà risposte diverse.
## Il mondo del Wumpus
È il gioco usato dal libro di testo: un cavaliere si muove in una griglia sconosciuta per prendere l'oro senza farsi mangiare dal **Wumpus** (un mostro) e senza cadere nelle **buche**. L'ambiente non è osservabile per intero, ma dà percezioni esplicite:
- in ogni cella adiacente a una buca si sente una **brezza**;
- in ogni cella adiacente al Wumpus si sente una **puzza**.

L'agente non ha la mappa: usa le percezioni e la conoscenza di come le percezioni sono legate al mondo, cioè che la brezza indica una possibile buca e la puzza un possibile Wumpus. Questa conoscenza si scrive come regole del tipo $A\Rightarrow B$. Indicando con $B_{i,j}$ "c'è brezza nella cella $(i,j)$" e con $P_{i,j}$ "c'è una buca in $(i,j)$":
$$B_{i,j}\Rightarrow P_{i+1,j}\lor P_{i-1,j}\lor P_{i,j+1}\lor P_{i,j-1}$$
Le formule le scrive il progettista e rappresentano ciò che sa del mondo (un'altra parte dell'IA studia come **apprenderle**). Arrivato in $(i,j)$ e percepita la brezza, l'agente aggiunge il fatto $B_{i,j}$ e con il **modus ponens** ([[03 - Risoluzione di problemi mediante ricerca#Dimostrazione di teoremi]]) da $A\Rightarrow B$ e $A$ ricava la disgiunzione delle buche possibili. Non sa quale sia vera, ma ora sa che una lo è.

Allo stesso modo si definisce cosa è **sicuro**: una cella è $\mathit{OK}$ se non c'è una buca e non c'è il Wumpus,
$$\mathit{OK}_{i,j}\Leftrightarrow\lnot P_{i,j}\land\lnot W_{i,j}$$
Se in una cella non si sente né brezza né puzza, le celle adiacenti sono sicure. L'euristica di esplorazione diventa: vai nelle celle sicure, e se non ce ne sono torna indietro. Una cella che **potrebbe** contenere una buca non è necessariamente pericolosa, ma non ha più la proprietà di essere sicura: è la differenza tra lo **stato del mondo** e le **credenze** dell'agente. Le credenze si combinano: percezioni (cosa è successo, celle già visitate, che restano vere se il mondo non cambia) e regole (come immaginare il mondo dove si sta per andare).
## Un esempio diagnostico
A lezione si è chiesto a ChatGPT come la logica proposizionale entra in un problema di diagnosi medica. I **fatti osservati** (la percezione del medico: la febbre misurata, la tosse riferita dal paziente) sono simboli proposizionali veri o falsi per quel paziente. Le **regole** sono implicazioni come
$$\mathit{Febbre}\land\mathit{Tosse}\Rightarrow\mathit{Influenza}$$
e altre regole possono escludere una diagnosi quando i fatti la contraddicono. Nella competenza reale serve anche "potrebbe": non solo vero o falso, ma una **probabilità** che una proposizione sia vera.

La logica serve a:
- **descrivere** il mondo con un linguaggio: ci si fermerà poco alla logica proposizionale e si userà la **logica del primo ordine**;
- il **ragionamento automatico**: da una base di conoscenza e da fatti certi, generare nuove formule;
- la **verifica di coerenza**: si toglie una formula $P$ dalla base e si cerca di dimostrare $\lnot P$; se ci si riesce, aggiungere $P$ renderebbe la base **inconsistente** (vere sia $P$ sia $\lnot P$). Con centinaia di migliaia di regole trovare a mano la regola che ne contraddice un'altra è impossibile, e automatizzarlo è essenziale. Gli LLM non hanno un meccanismo di verifica di coerenza, ed è uno dei motivi per cui a volte danno risposte inconsistenti;
- la **spiegazione**: le regole sono scritte in chiaro. Se si è dimostrato $B$ usando $A\Rightarrow B$, e $A$ usando $D\Rightarrow A$ con $D$ vero, alla domanda "perché $B$?" si risponde ripercorrendo la catena di modus ponens. Un sistema logico sa sempre **spiegare** le sue decisioni.
## Logica e machine learning
Un sistema di machine learning apprende un'ipotesi $h(\mathbf x)$ che approssima la funzione ideale $f(\mathbf x)$, dove $\mathbf x=(x_1,\dots,x_n)$ è un vettore (la scacchiera e la storia della partita, per decidere la prossima mossa). Una rete neurale è un "macchinario" in cui entrano $x_1,\dots,x_n$ ed esce il valore, o un vettore di $k$ valori di cui si prende il massimo (come la parola successiva in un LLM). Si passa da una rappresentazione **discreta** (simboli di un alfabeto finito, formule, regole) a una rappresentazione nel **continuo**, in $\mathbb{R}^n$: è questo il senso delle "rappresentazioni distribuite" (*distribuito* significa che l'informazione sta in posti diversi, su più componenti).

> [!warning] Il machine learning non è l'opposto della logica
> Ogni applicazione di machine learning elenca le dimensioni $x_1,x_2,\dots,x_n$, e questo è un **impegno** (*commitment*) su cosa rappresenta ciascuna: una relazione espressa numericamente, come lo schema di una tabella. Un'immagine diventa un vettore leggendo i pixel in un ordine fisso, tre numeri RGB per pixel; se l'ordine cambiasse da un'immagine all'altra, la rete vedrebbe immagini "follemente diverse" e non potrebbe apprendere nessuna legge regolare. Allo stesso modo, nel labirinto le prime due componenti saranno sempre la posizione $x$ e $y$ del cavaliere. Se il modello logico è sbagliato non c'è niente da apprendere: un sistema fermo al 55% su un problema semplice spesso ha un dato iniziale formalizzato male. Prima si conosce e si rappresenta il problema, poi si apprende.
## L'agente basato sulla conoscenza
Un agente basato sulla conoscenza ha una **base di conoscenza** (KB), un insieme di formule in un linguaggio logico: fatti specifici (dall'esperienza o da un'enciclopedia del dominio) e fatti generali (regole). Due operazioni:
- **TELL**: aggiunge una formula alla base, ad esempio un fatto appena percepito. È una scrittura permanente, come in una base di dati;
- **ASK**: chiede se una formula è vera, ad esempio se una cella è sicura. La base risponde sì o no deducendo dalle sue formule.

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
### Conseguenza logica
Rispondere a ASK significa calcolare la **conseguenza logica**:
$$KB\models\alpha$$
$\alpha$ è conseguenza logica di $KB$ se $\alpha$ è vera in **tutti i mondi** in cui sono vere tutte le formule di $KB$. Non vuol dire che $\alpha$ sia vera sempre, ma che lo è in tutti gli stati del mondo compatibili con ciò che l'agente crede: sono gli **stati credenza** visti nella ricerca, tutti gli stati possibili che non si possono distinguere osservando. Il simbolo $\models$ va tenuto distinto dall'implicazione $\Rightarrow$, che è un simbolo del linguaggio. Più l'agente sa, più mondi esclude e più precise sono le risposte. Un processo di risposta che preserva questi mondi **preserva la verità**: si dice consistente (in senso tecnico, *corretto*).

> [!example] Tutti gli uomini sono mortali
> $\forall x\ \mathit{Uomo}(x)\Rightarrow\mathit{Mortale}(x)$ restringe i mondi a quelli in cui gli uomini muoiono. In un romanzo di fantascienza con un immortale la formula è falsa: con una teoria si sceglie di ragionare solo sui mondi che rappresentano la verità che interessa, qui quella biologica.
## Conoscenza dichiarativa
La conoscenza deve essere **dichiarativa**, come nelle basi di dati: nessuna procedura che descriva il mondo, ma un insieme di fatti che ne stabiliscono le proprietà (matricola, nome, cognome...). Conta l'informazione, non come la si costruisce. Una base dichiarativa è:
- **modulare e riusabile**: la regola sulla puzza vale per tutte le celle, e la teoria di un labirinto serve anche in altri labirinti;
- **ispezionabile**: con milioni di regole, la leggibilità dipende dal contenuto linguistico delle formule, come i nomi delle variabili in un programma;
- **modificabile in modo incrementale**: si ritratta un valore e se ne afferma uno nuovo (`retract` e `assert`), come faceva l'algoritmo di apprendimento in tempo reale che aggiornava le stime dell'euristica.
### Differenza con le basi di dati
> [!example] La distinta base del triciclo
> Una relazione "parte di" dice che un triciclo ha tre ruote, una ruota è fatta di cerchione e copertone, un copertone contiene una camera d'aria. La struttura è **ricorsiva**. In SQL ogni query scende di un numero fissato di livelli: per sapere quante camere d'aria ci sono in un triciclo serve una query diversa a seconda della distanza tra le due parti, e non c'è una sola query che calcoli la **chiusura ricorsiva** della relazione per qualunque profondità. In logica, invece, la dimostrazione attraversa le implicazioni quante volte serve: è una ricerca ricorsiva.

> [!warning] SQL ricorsivo
> Il discorso vale per l'algebra relazionale e l'SQL di base. Dallo standard SQL:1999 esistono le query ricorsive (`WITH RECURSIVE`), che calcolano proprio questo tipo di chiusura: è un'aggiunta al linguaggio per superare il limite descritto a lezione.

Altre differenze: una base di dati vive in un mondo **statico** e adotta l'**ipotesi del mondo chiuso**: ciò che non è dichiarato è falso, e esistono solo gli oggetti memorizzati. Non può generare fatti nuovi perché non ha regole generali che vadano oltre le tuple. Una base di conoscenza, con le sue regole, **deduce** nuovi fatti.
### Due programmi che fanno la stessa cosa
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
- il secondo risponde "perché bianco è il colore della neve": la stampa è ricondotta a una **teoria del mondo** fatta di oggetti, colori e materiali. `color` ha come chiave l'identificativo dell'oggetto e come valore un elemento del dizionario dei colori: è un modello **relazionale**, come una tabella, ma che ammette la ricorsione.

Il secondo programma è **trasparente epistemologicamente**. L'epistemologia è la parte della filosofia che studia la realtà non per quello che è, ma per come viene percepita e conosciuta da chi la osserva (come quando si scopre che un amico è diverso da come lo si conosceva all'inizio: cambia la conoscenza, con l'esperienza). Scrivere il codice in questo modo rende evidente perché il programma agisce come agisce: è la base della manutenibilità di un sistema di IA e della **spiegabilità** (*explainable AI*).

> [!info] Ragiona passo per passo
> Una delle tecniche con cui gli LLM danno spiegazioni è simulare a parole questo processo logico: scrivendo nel prompt "ragiona passo per passo", il modello non dà subito la risposta ma genera i passi intermedi della decisione. È però un comportamento appreso: il ragionamento esposto può non corrispondere a quello che il sistema ha davvero fatto.
### L'atteggiamento intenzionale
Il filosofo Daniel Dennett chiama **atteggiamento intenzionale** (*intentional stance*) il descrivere un sistema separando ciò che sa da ciò che fa: "stampo il colore perché conosco il colore", cioè l'azione è giustificata dalla conoscenza. Uno dei motivi per cui agli LLM si contesta di essere davvero intelligenti è che le loro spiegazioni non corrispondono a una catena deduttiva: il modo in cui decidono e la storia che raccontano sul perché non coincidono. In un sistema logico con le regole in chiaro coincidono, e per questo questi sistemi venivano considerati **agenti intenzionali**. Una parte della storia dell'IA ha perseguito questa strada: agenti che decidono come i matematici, per deduzione rigorosa.

Rispetto ai [[02 - Agenti intelligenti#Tipi di agente|tipi di agente]] (reattivi, basati su modello, con utilità, che apprendono), l'idea è che il **modello** dell'agente, per prevedere bene le credenze, va espresso in una rappresentazione logica della conoscenza.
## Interpretazione e significato
Ci sono due mondi: quello della **rappresentazione**, nella memoria dell'agente, e il **mondo reale**, l'ambiente. Una formula come $\mathit{Color}(\mathit{snow},\mathit{white})$ parla di un aspetto del mondo. Dare significato a una formula non vuol dire dichiararla vera o falsa, ma avere un modo di leggerla (ad esempio fissare il significato di variabili e quantificatori) e di confrontarla con il mondo: è l'**interpretazione**. A seconda di come è fatto il mondo la formula è vera o falsa: $\mathit{Color}(\mathit{sky},\mathit{yellow})$ è falsa, $\mathit{Color}(\mathit{sky},\mathit{blue})$ è vera, salvo nuvole.

Il vantaggio è questo: se le formule della base sono vere nel mondo e il sistema deduce che una formula nuova ne è conseguenza logica, allora la nuova formula, con la stessa interpretazione, è una proprietà vera del mondo, **ottenuta senza andare nel mondo**. Un robot può ragionare in astratto su cosa succederebbe se facesse certe azioni, prima di farle: è il vantaggio che abbiamo sugli animali, che conoscono il mondo solo facendone esperienza.

I linguaggi diventeranno via via più espressivi: con le **variabili** pochi simboli esprimono molta informazione implicita e descrivono insiemi di mondi senza sapere esattamente in quale ci si trova ("la moglie di Rossi" può essere Paola, Maria, Giuseppina...). Ma più espressività significa un calcolo della conseguenza logica più difficile: le interpretazioni possibili crescono in modo esponenziale, e serviranno meccanismi di inferenza efficienti.

> [!question] Domanda tipica d'esame
> Cos'è un agente basato sulla conoscenza? Descrivi le operazioni TELL e ASK, il programma KB-Agent e cosa significa $KB\models\alpha$. Perché una conoscenza dichiarativa è preferibile a una procedurale? Traccia: base di conoscenza esterna al codice, percezioni come formule, azioni dedotte, conseguenza logica come verità in tutti i mondi che soddisfano la base; modularità, ispezionabilità, spiegabilità (i due programmi Prolog sul colore).
## Prossimi passi
Venerdì c'è un'esercitazione in aula, di nuovo in Python. La lezione riprende lunedì da qui: come combinare le formule della base di conoscenza per calcolare la conseguenza logica.
