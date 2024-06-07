Inizieremo il nostro studio partendo da questi componenti elementari c dalla particolare algebra a due valori (algebra di Boole) che si utilizza per analizzarli. Successivamente esamineremo alcuni circuiti fondamentali, tra cui quelli per eseguire calcoli aritmetici costruiti mediante semplici combinazioni di porte logiche. L’ argomento successivo sarà l’organizzazione della memoria, ovvero com’è possibile combinare le porte logiche per memorizzare informazioni. In seguito verrà affrontato il tema delle CPU e in particolare il modo in cui CPU composte da un unico chip si interfacciano con memoria e periferiche. Nella parte finale del capitolo saranno presentati, a titolo di esempio, numerosi prodotti reali.
## 3.1 - Porte logiche e algebra di Boole
I circuiti digitali possono essere costruiti combinando tra loro un piccolo numero di componenti elementari.
### 3.1.1 - Porte logiche
Un circuito digitale opera con due valori logici, rappresentati da segnali di tensione: tra 0 e 0,5 volt per il valore 0, e tra 1 e 1,5 volt per il valore 1. Le tensioni fuori da questi intervalli non sono ammesse. La base hardware dei calcolatori digitali è costituita dalle **porte logiche**, dispositivi che calcolano funzioni su questi segnali.

Le porte logiche funzionano con transistor, che hanno tre connessioni: **collettore**, **base** ed **emettitore**. Quando la tensione scende sotto un valore critico, il transistor si disabilita, comportandosi come una resistenza infinita. Le porte NOT sono anche chiamate **invertitori**, e trasformano un segnale alto (logico 1) in basso (logico 0) e viceversa.

Le principali tecnologie per la costruzione delle porte logiche sono **bipolare** e **MOS**. Le tecnologie bipolari più rilevanti sono **TTL**, per anni predominante nell'elettronica digitale, e **ECL**, usata per velocità elevate. Oggi, la tecnologia MOS è ampiamente utilizzata nei circuiti dei calcolatori per la sua minore potenza richiesta e dimensione ridotta, nonostante sia più lenta rispetto a TTL ed ECL.

(pagine riassunte: 2.5)
### 3.1.2 - Algebra di Boole
Per descrivere i circuiti costruiti con porte logiche, si utilizza l'**algebra di Boole**, dove variabili e funzioni assumono solo i valori 0 e 1. In particolare, si parla di **algebra booleana minimale**, anche se comunemente ci si riferisce semplicemente all'algebra booleana.

Una funzione booleana con *n* variabili può essere completamente descritta da una **tabella di verità** con $2^{n}$ righe, che mostra tutte le combinazioni possibili degli input e i rispettivi valori della funzione. Questa rappresentazione aiuta a determinare quali combinazioni di input producono il valore 1.

Una funzione booleana può essere espressa come una somma di prodotti logici di *n* variabili, facilitando l'implementazione della funzione con porte logiche standard. È fondamentale distinguere tra una funzione booleana astratta, descritta tramite variabili e operatori come AND, OR e NOT, e la sua implementazione circuitale, che utilizza segnali e porte logiche per rappresentare e calcolare tali funzioni.

(pagine riassunte: 2)
### 3.1.3 - Implementazione delle funzioni booleane
Implementare una funzione booleana come somma di prodotti è un metodo efficace. Ecco i passaggi per creare un circuito che realizzi qualsiasi funzione booleana:

1. Scrivi la tabella di verità della funzione.
2. Usa invertitori per generare la negazione di ciascun input.
3. Utilizza una porta AND per ogni combinazione di input che produce un risultato 1.
4. Collega le porte AND agli input appropriati.
5. Collega tutti gli output delle porte AND a una porta OR.

Questo metodo dimostra che ogni funzione booleana può essere implementata con le porte NOT, AND e OR. Tuttavia, può essere più vantaggioso utilizzare un solo tipo di porta logica, come le NAND o le NOR.

Per implementare una funzione booleana usando solo porte NAND o NOR, si può iniziare con le porte NOT, AND e OR e poi sostituirle con circuiti equivalenti a due ingressi. Ad esempio, $A + B + C + D$ può essere calcolato come $(A + B) + (C + D)$ usando tre porte logiche a due ingressi.

Sia le porte NAND che NOR sono funzionalmente complete, il che significa che qualsiasi funzione booleana può essere realizzata utilizzando solo uno di questi due tipi di porte. Questa proprietà le rende particolarmente utili nella costruzione dei circuiti.

(pagine riassunte: 2)
### 3.1.4 - Equivalenza di circuiti
I progettisti cercano di ridurre il numero di porte logiche nei circuiti per limitare le dimensioni delle schede, ridurre il consumo energetico e aumentare la velocità. Per farlo, devono trovare un circuito alternativo che calcoli la stessa funzione con meno porte.

Molte regole dell'algebra ordinaria valgono anche per l'algebra booleana, come la proprietà distributiva: $( AB + AC \implies A(B + C) )$. Due funzioni sono equivalenti se hanno lo stesso output per tutti gli input possibili, verificabile tramite tabelle di verità. Solitamente, i progettisti semplificano una formula usando le leggi dell'algebra di Boole prima di costruire il circuito finale.

È utile conoscere alcune identità fondamentali, molte delle quali hanno forme **duali** ottenibili scambiando AND con OR e 1 con 0. La legge di De Morgan può essere estesa a più variabili, per esempio $( ABC = A + B + C )$.

La stessa porta logica può calcolare diverse funzioni a seconda delle convenzioni di tensione adottate. Con la **logica positiva**, 0 volt rappresenta il valore logico 0 e 1,5 volt il valore logico 1, risultando in una funzione AND. Con la **logica negativa**, 0 volt rappresenta il valore logico 1 e 1,5 volt il valore logico 0, risultando in una funzione OR. D'ora in poi, salvo diversa indicazione, si utilizzerà la logica positiva.

(pagine riassunte: 3.5)
## 3.2 - Circuiti logici digitali elementari
Al giorno d’oggi nella costruzione di circuiti i componenti elementari sono generalmente rappresentati da moduli contenenti un certo numero di porte. Nei paragrafi successivi analizzeremo più da vicino questi blocchi elementari e vedremo come vengono utilizzati e come sono costruiti a partire da singole porte logiche.
### 3.2.1 - Circuiti integrati
Le porte logiche non sono vendute singolarmente ma come parte di **circuiti integrati** (**IC** o **chip**). Un circuito integrato è un pezzo rettangolare di silicio di dimensioni variabili in base al numero di porte necessarie. I circuiti più piccoli misurano circa 2 mm x 2 mm, mentre i più grandi possono arrivare a 18 mm x 18 mm.

I chip piccoli, come quelli utilizzati per microcontrollori domestici o RAM, usano un supporto **DIP** (*Dual In-line Package*) con due file di pin che si inseriscono in un alloggiamento sulla scheda madre. I circuiti integrati più grandi usano supporti **PGA** (*Pin Grid Arrays*) o **LGA** (*Land Grid Arrays*). I PGA hanno pin sul fondo che si inseriscono in un alloggiamento sulla scheda madre, spesso con un meccanismo per facilitare l'inserimento. I LGA hanno pad piatti sul fondo e una copertura sul socket LGA applica una forza verso il basso per assicurare il contatto tra i pad.

I DIP hanno una marcatura in un angolo che deve coincidere con un segno sul socket DIP. I PGA hanno in genere un pin mancante per l'orientamento. 

Per i nostri scopi, consideriamo le porte logiche ideali, con output immediato al voltaggio in input. Tuttavia, in realtà, i chip hanno un ritardo temporale finito, chiamato **ritardo della porta**, che include il tempo di propagazione del segnale e il tempo di commutazione, solitamente tra centinaia di picosecondi e pochi nanosecondi.

(pagine riassunte: 1.5)
### 3.2.2 - Reti combinatorie
Molte applicazioni della logica digitale richiedono un circuito, chiamato **rete combinatoria**, con più input e più output, in cui gli output sono unicamente determinati dagli input. Non tutti i circuiti hanno questa proprietà; un circuito contenente elementi di memoria può per esempio generare valori che dipendono non solo dalle variabili d’ingresso, ma anche dai valori memorizzati

(pagine riassunte:0.25)
#### 3.2.2.1 - Multiplexer
In logica digitale un ***multiplexer*** è un circuito con $2^{n}$ dati di input, un valore di output e *n* input di controllo; gli input di controllo permettono di selezionare uno dei dati di input, che viene instradato verso l'output. Un multiplexer con otto input ha tre linee di controllo. A, B e C, codificano un numero a 3 bit che specifica quale delle otto linee di input deve essere instradata verso la porta OR e quindi verso l’output. Indipendentemente dal valore definito dalle linee di controllo, sette delle porte AND genereranno sempre il valore 0, mentre quella rimanente produrrà in output 0 oppure 1, a seconda del valore della linea d’ingresso selezionata. Ciascuna porta AND può essere abilitata da una diversa combinazione degli input di controllo.

Un'altra delle possibili applicazioni è la conversione di dati da parallelo a seriale. Se si immettono 8 bit di dati nelle linee di input e se si fa variare il valore (binario) delle linee di controllo da 000 a 111, si ottengono sulla linea di output gli 8 bit in serie.

L’inverso del multiplexer è il **demultiplexer**, che redirige il suo segnale di input verso uno dei $2^{n}$ output in base ai valori delle linee di controllo; se il valore binario definito dalle linee di controllo è *k*, viene selezionato l’output *k*.

(pagine riassunte: 2)
#### 3.2.2.2 - Decodificatori
Come secondo esempio analizzeremo ora un circuito, chiamato **decodificatore** (*decoder*), che accetta come input un numero a *n* bit e lo utilizza per impostare a 1 una sola delle $2^{n}$ linee di output.

Per capire in quali situazioni può essere utile questo circuito immaginiamo una piccola memoria di otto chip, da 256 MB ciascuno. Gli indirizzi del chip 0 variano da 0 a 256 MB, quelli del chip 1 da 256 MB a 512 MB e così via. Quando si fornisce alla memoria un indirizzo, si utilizzano i suoi 3 bit più significativi per selezionare uno degli otto chip.

Ciascuna porta AND ha tre input, il primo dei quali è $A$ o $\overline{A}$, il secondo $B$ o $\overline{B}$ e il terzo $C$ o $\overline{C}$, e viene abilitata da una diversa combinazione dei valori di input: $D_{0}$  da  $\overline{A}\ \overline{B}\ \overline{C}, D_{1}$ da $\overline{A}\quad  \overline{B}\quad  C$ e così via.

(pagine riassunte: 1)
#### 3.2.2.3 - Comparatori
Un altro circuito particolarmente utile è il comparatore, che permette di confrontare due stringhe di bit. Il circuito è basato sulla porta logica XOR (EXCLUSIVE OR), che produce in output un valore 0 se i suoi input sono uguali e un valore 1 se sono diversi. Se due stringhe in ingresso sono uguali, tutte e quattro le porte XOR devono generare come risultato 0. Questi quattro segnali possono poi essere connessi a una stessa porta logica OR in modo da produrre un valore 0 quando gli input sono uguali e un valore 1 nel caso contrario

(pagine riassunte: 0.5)
#### 3.2.2.4 - Array logici programmabili
Un chip molto generale che permette di calcolare somme di prodotti è l’**array logico programmabile** o **PLA** (*Programmable Logic Array*). Questo chip ha 12 ingressi e al suo interno questi valori vengono invertiti; quindi il numero totale di segnali di input diventa 24.

L’uscita del circuito consiste in 6 porte OR, che possono avere fino a 50 input, corrispondenti agli output delle porte AND.

Nel caso di funzioni semplici il numero di variabili rappresenta un fattore vincolante, mentre per funzioni più complesse il limite potrebbe essere rappresentato dal numero di porte AND o OR.

Anche se i PLA *programmabili sul campo*, come quello appena descritto, vengono ancora utilizzati, oggi, in molte applicazioni, si preferisce impiegare dei PLA costruiti ad hoc. Questi ultimi sono più economici di quelli programmabili e, in caso di grandi volumi, vengono progettati sulla base delle specifiche del cliente.

(pagine riassunte: 1.5)
### 3.2.3 - Circuiti per l'aritmetica
Inizieremo con un semplice registro a scorrimento (*shifter*) a 8 bit. continueremo guardando com’è costruito un sommatore e infine esamineremo le unità aritmetico-logiche che svolgono un ruolo centrale all’interno di tutti i calcolatori.
#### 3.2.3.1 - Registri a scorrimento
Il primo circuito aritmetico MSI che analizziamo ha otto input e otto output. Gli input sono collegati alle linee $D_{0}, ..., D_{7}$ mentre l’output, corrispondente all’input traslato di un bit, risulta disponibile sulle linee $S_{0}, ..., S_{7}$ La linea di controllo, C, ha valore 0 se lo spostamento deve avvenire verso sinistra, e 1 in caso contrario. Nel caso di uno spostamento a sinistra si inserisce uno 0 nel bit 7, e nel caso di uno shift a destra si inserisce uno 0 nel bit 0. Quando $C = 1$ la porta che si trova a destra in ciascuna coppia viene abilitata, lasciando passare il bit corrispondente verso l’output. Dato che la porta AND è collegata all’input della porta OR alla sua destra, si ottiene uno scorrimento verso destra. Quando $C = 0$ è la porta AND di sinistra in ciascuna coppia a essere abilitata, producendo uno spostamento verso sinistra.

Figura 3.15
#### 3.2.3.2 - Sommatori
La Figura 3.16(b) mostra un **half adder** (*semisommatore*), che calcola il bit della somma e il bit del riporto. Questo circuito può sommare i bit meno significativi di due stringhe binarie, ma non gestisce il riporto da posizioni precedenti, quindi non può sommare correttamente gli altri bit. Per questo è necessario un **sommatore**.

In un sommatore, il riporto in uscita di un bit è usato come riporto in entrata per il bit successivo a sinistra. Il riporto in entrata del bit più a destra è impostato a 0. Questo tipo di sommatore è chiamato **sommatore a propagazione di riporto**, poiché nel caso peggiore, sommando 1 a 111...111, la somma si completa solo dopo che il riporto si è propagato lungo tutta la parola binaria. Esistono sommatori più veloci che non hanno questo ritardo.

Una modifica proposta consiste nell'avere due sommatori per i bit più significativi funzionanti in parallelo, *U0* e *U1*, insieme a un sommatore per i bit meno significativi. In *U0* il riporto è impostato a 0, mentre in *U1* è impostato a 1. Tutti e tre i sommatori iniziano contemporaneamente, ma solo uno tra *U0* e *U1* sarà corretto. Il sommatore corretto viene selezionato in base al riporto. Questo approccio, chiamato **sommatore a selezione del riporto**, dimezza il tempo necessario per l'addizione.
#### 3.2.3.3 - Unità aritmetico logiche
La maggior parte dei calcolatori contiene un unico circuito capace di effettuare operazioni AND, OR e somma di due parole. Questo circuito, chiamato **unità aritmetico logica** o **ALU** (*Arithmetic Logic Unit*), è composto da n circuiti identici per le singole posizioni dei bit e può calcolare una delle quattro funzioni: ( $A \ AND\ B$), ( $A \ OR\ B$), ($\overline{B}$ ) oppure ($A + B$), in base ai valori binari delle linee di selezione ($F_{0}$) e ($F_{1}$).

La Figura 3.18 mostra la struttura della ALU:
- **In basso a sinistra**: un decodificatore a 2 bit che genera i segnali di attivazione delle quattro operazioni in base ai segnali di controllo \( $F_{0}$ \) e \( $F_{1}$ \).
- **In alto a sinistra**: le porte logiche per calcolare ($A \ AND\ B$), ($A \ OR\ B$) e ($\overline{B}$). Solo uno di questi risultati viene passato alla porta logica finale OR, in base alle linee di attivazione.
- **In basso a destra**: un sommatore che calcola la somma di A e B e gestisce i riporti, permettendo a vari circuiti dello stesso tipo di collegarsi tra loro per operazioni su intere parole. Questi circuiti, chiamati **bit slices**, permettono di costruire ALU di larghezza arbitraria.

Figura 3.18

(pagine riassunte: 4.5)
### 3.2.4 - Clock
In molti circuiti digitali, l'ordine degli eventi è cruciale e viene gestito tramite **clock**, che emettono impulsi a intervalli costanti. L'intervallo tra due impulsi consecutivi è detto **ciclo di clock**.

Un calcolatore può eseguire più eventi durante un ciclo di clock. Per una risoluzione temporale più fine, si può ritardare il segnale del clock principale, generando un secondo segnale di clock con una fase traslata. Il diagramma di temporizzazione fornisce quattro riferimenti temporali per sincronizzare eventi discreti:

1. Fronte di salita di C1.
2. Fronte di discesa di C1.
3. Fronte di salita di C2.
4. Fronte di discesa di C2.

Associando eventi a questi quattro fronti, si può stabilire una sequenza desiderata. Se servono più di quattro riferimenti temporali in un ciclo di clock, si collegano altre linee secondarie al clock principale e si usano circuiti con ritardi diversi.
## 3.3 - Memoria
Una componente essenziale di ogni calcolatore è la memoria; se non ci fosse non potrebbe esistere nessun calcolatore, almeno nella forma in cui lo conosciamo. La memoria è utilizzata per conservare sia le istruzioni da eseguire sia i dati.
### 3.3.1 - Latch
Per creare una memoria a 1 bit è necessario disporre di un circuito che in qualche modo “ricordi" precedenti valori di input.

Il circuito **latch SR** e ha due input: $S$, per impostare il valore del latch e $R$ per azzerarlo. Il circuito ha anche due output, $Q$ e $\overline{Q}$, che, come vedremo tra poco, sono complementari Puno rispetto all’altro. Diversamente dalle reti combinatorie l’ output di un latch non è determinato unicamente dai valori di input correnti.

Quando $S$ è impostato temporaneamente a 1 lo stato del latch diventa $Q = 1$, indipendentemente dallo stato in cui si trovava precedentemente. Allo stesso modo quando si imposta temporaneamente $R$ a 1 si forza il latch a passare nello stato $Q = 0$. Il circuito “ricorda” quindi quale valore, se $S$ oppure $R$ è stato settato per ultimo; utilizzando questa proprietà è possibile costruire le memorie dei calcolatori.
#### 3.3.1.1 - Latch SR temporizzato
Per evitare che un latch cambi di stato in momenti non desiderati, si utilizza un **latch SR temporizzato**. Questo circuito include un input aggiuntivo, il clock, che solitamente vale 0. Quando il clock è 0, entrambe le porte AND generano un output di 0, impedendo al latch di cambiare stato indipendentemente dai valori di S e R. Quando il clock è 1, le porte AND permettono il passaggio dei segnali S e R, che possono quindi modificare lo stato del latch. I termini ***enable*** e ***strobe*** indicano che il clock è 1 e il circuito dipende dai valori di S e R.

Se sia S che R valgono 1, il circuito diventa non deterministico finché entrambi gli input non tornano a 0. L'unico stato consistente per ($S = R = 1$) è ($Q = \overline{Q} = 0$). Quando entrambi gli input ritornano a 0, il latch deve passare istantaneamente a uno dei suoi due stati stabili. Se uno degli input torna a 0 prima dell'altro, prevale quello che rimane a 1 più a lungo. Se entrambi gli input ritornano a 0 simultaneamente, il latch passa casualmente a uno dei due stati stabili.
#### 3.3.1.2 - Latch D temporizzato
Un buon modo per risolvere l'ambiguità dei latch SR è... evitare che si verifichi; con un circuito che ha un solo input, D. Dato che l’input della porta AND rappresentata in basso è sempre il complemento dell’input di quella superiore, non può mai accadere che entrambi gli input valgono 1. Questo circuito, chiamato **latch D temporizzato**, è una vera e propria memoria a 1 bit, in cui il valore memorizzato è sempre disponibile sulla linea Q. Per caricare in memoria il valore corrente di D occorre spedire un impulso positivo sulla linea del clock. Il circuito appena descritto richiede 11 transistor, esistono tuttavia circuiti più sofisticati che possono memorizzare 1 bit utilizzando solo sei transistor.

(pagine riassunte: 2.75)
### 3.3.2 - Flip-Flop
In molti circuiti è necessario campionare il valore di una certa linea in un particolare istante e memorizzarlo. In questi circuiti, chiamati **flip-flop**, la transizione di stato non si verifica quando il clock vale 1, ma durante la transizione del clock da 0 a 1 (fronte salita) oppure da 1 a 0 (fronte discesa). In questa situazione la lunghezza dell’impulso del clock non ha alcuna importanza, purché le transizioni si verifichino con sufficiente velocità.

Per sottolinearlo ulteriormente ripetiamo la differenza che c’è tra un flip-flop e un latch: un flip-flop è a **commutazione sul fronte**, mentre un latch è a **commutazione a livello**. Esistono vari approcci per progettare un flip-flop. Se per esempio esistesse un metodo per generare un impulso di lunghezza estremamente breve sul fronte di salita, si potrebbe immettere tale impulso in un latch D. Occorre sottolineare che il vantaggio dell’ architettura di questo flip-flop è di essere di facile comprensione; tuttavia nella realtà si ricorre di solito ad architetture più sofisticate.

(pagine riassunte: 2.25)
### 3.3.3 - Registri
I Flip-Flop possono essere combinati per creare dei registri che memorizzano dati composti da più bit. Otto flip-flop possono essere raggruppati per formare un registro da 8 bit. Il registro riceve in ingresso un valore di 8 bit (da IO a 17) quando vi è una transizione del clock CK. Per implementare un registro tutte le linee di clock sono collegate allo stesso segnale in ingresso CK, in modo che quando si ha una transizione di clock il registro riceve dal canale di ingresso il nuovo dato di 8 bit.

Una volta progettato un registro a 8 bit, lo si può utilizzare per costruire registri più grandi. Per esempio, un registro a 32 bit può essere costruito combinando due registri a 16 bit, unendo i loro segnali di clock CK e di cancellazione CLR.

(pagine riassunte: 1)
### 3.3.4 - Organizzazione della memoria
Per realizzare memorie di dimensioni maggiori, è necessaria un'organizzazione che consenta di indirizzare singole parole. Un esempio è una memoria con quattro parole a 3 bit, in cui ciascuna operazione legge o scrive un'intera parola. Questa memoria ha una capacità totale di 12 bit e richiede un numero inferiore di pin rispetto al flip-flop ottale. È anche facilmente estendibile a memorie più grandi, con il numero di parole sempre come potenza di 2.

Le otto linee di input sono divise in:
- Tre per i dati: ( $I_0$), ( $I_1$), ( $I_2$ ).
- Due per l'indirizzo: ( $A_0$ ), ( $A_1$).
- Tre per i controlli: CS (selezione del chip), RD (lettura/scrittura), OE (abilitazione dell'output).

Le tre linee di output (( $O_0$), ($O_1$), ($O_2$)) sono dedicate ai dati.

Per l'uso del chip:
- In lettura, CS e RD devono essere alti (logico 1).
- In scrittura, CS e RD devono essere bassi (logico 0).

Quando il chip è selezionato per la scrittura, la linea ( $CS \cdot \overline{RD}$ ) diventa alta, abilitando una delle quattro porte di scrittura in base ai segnali ( $A_0$ ) e ( $A_1$ ). I dati di input vengono caricati nei flip-flop della parola selezionata. Solo la parola selezionata è scritta, mentre le altre restano invariate.

In lettura, la decodifica dell'indirizzo avviene nello stesso modo, ma ( $CS \cdot \overline{RD}$ ) è basso, disabilitando le porte di scrittura. La parola selezionata invia i propri dati alle porte OR, poiché le altre parole generano output 0, il risultato delle porte OR è identico al valore memorizzato nella parola selezionata.

Per evitare che il chip tenti di inviare dati durante la scrittura, interferendo con i dati di input, si utilizza un **buffer non invertente**. Questo buffer ha un input di controllo: quando è alto, il buffer funge da collegamento; quando è basso, si comporta come un circuito aperto. Esiste anche il **buffer invertente**, che inverte il segnale quando l'input di controllo è alto e disconnette l'output quando è basso.

Entrambi i buffer sono **dispositivi a tre stati**: possono generare 0, 1 o nessuno dei due (circuito aperto). Amplificano il segnale e possono guidare più input contemporaneamente, spesso utilizzati anche quando non è richiesta l'inversione del segnale.

Figura 3.28

(pagine riassunte: 3)
### 3.3.5 - Chip di memoria
La memoria della Figura 3.28 può essere facilmente ampliata. L'esempio descritto è una memoria $4 \times 3$, composta da quattro parole di 3 bit ciascuna. Per espanderla a $4 \times 8$, basta aggiungere cinque colonne di quattro flip-flop ciascuna e le relative linee di input e output. Per passare a $8 \times 3$, si devono aggiungere quattro righe di tre flip-flop ciascuna e una linea di indirizzo aggiuntiva, ($A_2$). Idealmente, il numero di parole dovrebbe essere una potenza di 2 per massimizzare l'efficienza, mentre il numero di bit per parola può variare.

I chip di memoria di dimensioni maggiori non rendono necessariamente obsoleti quelli più piccoli, poiché bisogna bilanciare capacità, velocità, consumo energetico, prezzo e facilità di interfacciamento. I chip più grandi tendono ad essere più costosi per bit.

Le dimensioni dei chip di memoria sono generalmente espresse in bit. I segnali vengono detti **asseriti** quando attivano un'azione e **negati** quando non lo fanno. Un segnale chiamato $CS$ viene asserito con il valore alto, mentre uno chiamato $\overline{CS}$ è asserito con il valore basso. Il segnale ($\overline{WE}$) (*Write Enable*) distingue tra lettura e scrittura, mentre ($\overline{OE}$) (*Output Enable*) guida i segnali di output, scollegandoli quando non è asserito.

I chip di memoria più grandi sono spesso organizzati come matrici ($n \times n$) indirizzate da numeri di riga e colonna, riducendo il numero di pin necessari ma rallentando il chip perché richiede due cicli di indirizzamento. Per migliorare la velocità, alcuni chip permettono di specificare un indirizzo di riga seguito da una sequenza di indirizzi di colonna per accedere a bit consecutivi nella stessa riga.

La progettazione dei chip di memoria comporta due questioni chiave: la larghezza dell'output (il numero di bit trasmessi contemporaneamente) e se gli indirizzi vengono forniti tutti insieme su pin distinti o separatamente per righe e colonne. Un ingegnere deve rispondere a queste domande prima di progettare il chip.

(pagine riassunte: 3)
### 3.3.6 - RAM e ROM
Le memorie studiate finora possono essere lette e scritte, e sono chiamate **RAM** (*Random Access Memory*). Esistono due tipi di RAM: statiche e dinamiche. Le **RAM statiche** (SRAM) sono costruite con circuiti simili ai flip-flop D e mantengono il contenuto fintanto che sono alimentate, con tempi di accesso molto rapidi (nanosecondi). Le **RAM dinamiche** (DRAM) utilizzano un array di celle con un transistor e un piccolo condensatore per bit, richiedendo un refresh periodico per mantenere i dati, poiché la carica dei condensatori tende a disperdersi. Le DRAM hanno una densità elevata e sono utilizzate nella memoria centrale, ma sono più lente rispetto alle SRAM.

Esistono vari tipi di DRAM:
- **DRAM FPM** (*Fast Page Mode*): il tipo più datato, organizzato a matrice di bit e richiede indirizzi di riga e colonna separati.
- **DRAM EDO** (*Extended Data Output*): migliora la larghezza di banda della memoria avviando nuovi riferimenti alla memoria prima che quelli precedenti siano completati.
- **SDRAM** (*Synchronous DRAM*): una RAM ibrida, in parte statica e in parte dinamica, sincronizzata con il clock principale del sistema, eliminando la necessità di segnali di controllo aggiuntivi.
- **SDRAM DDR** (*Double Data Rate*): raddoppia il tasso di trasferimento dati producendo output sia sul fronte di salita che su quello di discesa del segnale di clock.

Questi tipi di RAM dinamica rappresentano un'evoluzione continua per soddisfare le esigenze di velocità dei processori sempre più rapidi.
#### 3.3.6.1 - Chip di memoria non volatile
Oltre alle RAM, esistono altri tipi di chip di memoria utilizzati per memorizzare permanentemente programmi e dati, anche in assenza di alimentazione. Questi sono chiamati **ROM** (*Read-Only Memory*), progettati per essere non modificabili e resistenti a cancellazioni accidentali o intenzionali. Le ROM sono programmate durante la fabbricazione e sono molto economiche per produzioni di grandi volumi, ma non sono flessibili poiché non possono essere modificate post-produzione.

Per risolvere questo problema, sono state sviluppate le **PROM** (*Programmable ROM*), che possono essere programmate una volta dal produttore. Successivamente, sono state create le **EPROM** (*Erasable PROM*), che permettono la cancellazione e la riprogrammazione dei dati, rendendole ideali per fasi di test estensive. Le EPROM richiedono l'esposizione alla luce ultravioletta per essere cancellate e devono essere rimosse dal circuito per la programmazione.

Le **EEPROM** (*Electrically Erasable PROM*) migliorano ulteriormente, permettendo la cancellazione tramite impulsi elettrici e la riprogrammazione senza rimuoverle dal circuito. Tuttavia, le EEPROM sono limitate in capacità, velocità e costi rispetto alle DRAM e SRAM.

Un tipo più recente di EEPROM è la **memoria flash**, che consente la cancellazione e riscrittura a blocchi. La memoria flash può essere cancellata e programmata senza essere rimossa dal circuito, combinando la flessibilità delle EEPROM con una maggiore capacità e velocità.
#### 3.3.6.2 - FPGA
Gli **FPGA** (*Field-Programmable Gate Array*) sono circuiti integrati programmabili che permettono di configurare circuiti logici arbitrari caricando dati di configurazione specifici. Questo consente la creazione di nuovi circuiti hardware in poche ore, rispetto ai mesi necessari per la fabbricazione di circuiti integrati personalizzati.

Gli FPGA contengono due componenti principali replicati molte volte: le **LUT** (*Look-Up Table*) e le **interconnessioni programmabili**. Le LUT sono piccole memorie programmabili che generano segnali di uscita, trasmessi poi alle interconnessioni programmabili e ai registri, permettendo di creare funzioni logiche arbitrarie. Ad esempio, una singola LUT a 4 ingressi può implementare un contatore a 3 bit con reset.

Un vantaggio significativo degli FPGA è la rapidità di prototipazione. Un progetto FPGA può essere sviluppato rapidamente, mentre un design completamente personalizzato richiede una lunga fabbricazione. Per utilizzare un FPGA, il progetto deve essere descritto mediante una rappresentazione del circuito o un linguaggio di descrizione hardware. Successivamente, un sintetizzatore mappa il progetto sull'architettura FPGA specifica. Tuttavia, a volte il progetto non può essere completamente mappato sull'FPGA disponibile, richiedendo FPGA con più LUT, che sono più costosi.

Progetti molto grandi potrebbero non rientrare nemmeno nei più grandi FPGA disponibili, costringendo il progettista a distribuire il progetto su più FPGA. Questo processo, sebbene più complesso, rimane molto più semplice rispetto alla progettazione di circuiti integrati personalizzati.

(pagine riassunte: 5)
## 3.4 - Chip della CPU e bus
In questo paragrafo analizzeremo inizialmente alcuni aspetti generali delle CPU dal punto di vista del livello logico digitale, **contatti** compresi, e forniremo anche un’introduzione all’architettura dei bus, dato che le CPU dipendono strettamente dal modo in cui questi sono progettati.

(pagine riassunte: 0.25)
### 3.4.1 - Chip della CPU
Le moderne CPU sono contenute in un unico chip e interagiscono con il resto del sistema tramite pin suddivisi in tre categorie principali: indirizzi, dati e controlli. Questi pin sono collegati alla memoria o ai chip di I/O tramite un bus parallelo. Per eseguire un'istruzione, la CPU imposta l'indirizzo sui pin di indirizzamento e utilizza le linee di controllo per comunicare con la memoria. Se l'istruzione coinvolge la lettura o scrittura di dati, il processo si ripete per ogni parola di dati.

Le prestazioni di una CPU dipendono in gran parte dal numero di pin di indirizzo e di dati. Un chip con *m* pin di indirizzo può indirizzare fino a ($2^m$) locazioni di memoria, mentre il numero di pin di dati (*n*) determina la dimensione della parola di dati che la CPU può leggere o scrivere in una singola operazione. Valori comuni per *m* sono 16, 20, 32 e 64.

Oltre ai pin di indirizzo e dati, le CPU possiedono pin di controllo per gestire il flusso e la temporizzazione dei dati, oltre a vari altri usi. I pin di controllo si dividono in sei categorie principali:

1. **Controllo del bus**: notificano quando la CPU vuole leggere o scrivere in memoria o compiere altre azioni.
2. **Interrupt**: input dalle periferiche per segnalare alla CPU l'inizio di un'operazione di I/O.
3. **Arbitraggio del bus**: regolano il traffico sul bus per evitare conflitti tra dispositivi che cercano di usarlo contemporaneamente.
4. **Comunicazione con il coprocessore**: per l'interazione con coprocessori come chip in virgola mobile o grafici.
5. **Stato**: per fornire o ricevere informazioni sullo stato del sistema.
6. **Altro**: per reset del calcolatore, operazioni di debugging o garantire compatibilità con chip di I/O più vecchi.

In sintesi, i pin della CPU sono fondamentali per la comunicazione con la memoria e altri dispositivi, influenzando direttamente le prestazioni e la funzionalità del sistema.
### 3.4.2 - Bus del calcolatore
Un **bus** è un collegamento elettrico che unisce diversi dispositivi, utilizzato sia internamente alla CPU per il trasferimento di dati con l'ALU, sia esternamente per collegare la CPU alla memoria o ai dispositivi di I/O. I primi PC avevano un unico bus esterno chiamato **bus di sistema**, costituito da 50 a 100 fili paralleli inseriti nella scheda madre. Modernamente, i personal computer hanno un bus specifico tra CPU e memoria e un altro per le periferiche.

All'interno della CPU, i progettisti possono utilizzare qualsiasi tipo di bus preferiscano, ma i bus esterni richiedono regole precise, dette **protocollo del bus**, e specifiche meccaniche ed elettriche per garantire compatibilità con le schede madri. Queste specifiche sono cruciali per permettere alle schede prodotte da terzi di funzionare correttamente.

Nonostante i numerosi sistemi incompatibili già esistenti rendano difficile una standardizzazione, i bus devono comunque gestire dispositivi attivi (*master*) e passivi (*slave*). I *master* possono iniziare un trasferimento dati, mentre gli *slave* rispondono alle richieste. Ad esempio, la CPU è un *master* quando comanda al controllore del disco di leggere o scrivere dati, mentre il controllore del disco diventa *master* quando trasferisce dati alla memoria, che è sempre uno *slave*.

I segnali digitali delle periferiche spesso non sono abbastanza forti per alimentare un bus lungo o con molti dispositivi collegati. Pertanto, i *master* sono collegati al bus tramite un **driver del bus**, che funge da amplificatore digitale, mentre gli *slave* usano un **ricevitore del bus**. Per periferiche che possono essere sia *master* sia *slave* si utilizza un **trasmettitore-ricevitore del bus**. Questi dispositivi di interfaccia sono spesso a tre stati per poter essere disconnessi quando non necessari, oppure possono utilizzare un **collettore aperto**, che permette un'organizzazione chiamata **OR-cablata** quando più dispositivi asseriscono la linea contemporaneamente.

Un bus ha i propri indirizzi, dati e linee di controllo, che non necessariamente corrispondono uno-a-uno con i pin della CPU. Le principali decisioni nella progettazione di un bus includono l’ampiezza, la temporizzazione, l’arbitraggio e le operazioni consentite, tutte influenzando significativamente la velocità e la larghezza di banda del bus.

(pagine riassunte: 2.5)
### 3.4.3 - Ampiezza del bus
Nella progettazione dei bus, uno dei parametri principali da considerare è l'ampiezza. Un numero maggiore di linee di indirizzo consente alla CPU di indirizzare direttamente più memoria: con *n* linee di indirizzo, la CPU può indirizzare $2^n$ locazioni di memoria. Tuttavia, bus più larghi richiedono più fili, occupano più spazio e necessitano di connettori più grandi, aumentando i costi. Ad esempio, un sistema con 64 linee di indirizzo e $2^{32}$ byte di memoria costerà più di uno con 32 linee di indirizzo e la stessa quantità di memoria, ma quest'ultimo non sarà espandibile in futuro.

Col tempo, non solo aumenta il numero di linee di indirizzo, ma anche quello delle linee di dati, per aumentare la larghezza di banda. Ci sono due modi per farlo: ridurre il periodo di clock del bus o aumentare la larghezza dei dati del bus. Un'altra opzione è aumentare la velocità del bus, ma ciò può causare **disallineamento del bus**: i segnali su linee diverse viaggiano a velocità leggermente diverse, problema che diventa più marcato con bus più veloci. Inoltre, velocizzare il bus può compromettere la retrocompatibilità.

Per ridurre l'ampiezza del bus senza compromettere troppo le prestazioni, si può optare per un **bus multiplexato**. In questa architettura, un certo numero di linee, ad esempio 32, è utilizzato sia per gli indirizzi sia per i dati. All'inizio di un'operazione, le linee sono utilizzate per gli indirizzi, e successivamente per i dati. Questo riduce l'ampiezza del bus, ma rende il sistema più lento. I progettisti devono quindi valutare attentamente queste opzioni per bilanciare costi, spazio e prestazioni.
### 3.4.4 - Temporizzazione del bus
I bus possono essere classificati in base alla loro temporizzazione in due categorie: **sincroni** e **asincroni**.
1. **Bus sincroni**: Hanno una linea pilotata da un oscillatore a cristalli che genera un segnale a onda quadra, con frequenze tipicamente comprese tra 5 e 100 MHz. Tutte le operazioni su questo tipo di bus richiedono un numero intero di cicli, detti **cicli di bus**.
2. **Bus asincroni**: Non dispongono di un orologio principale, quindi i cicli di bus possono avere lunghezze variabili e non devono essere necessariamente uguali durante la comunicazione tra dispositivi.
#### 3.4.4.1 - Bus sincroni
Figura 3.38

Il testo descrive il funzionamento di un bus sincrono utilizzando come esempio una temporizzazione specifica, illustrata nella Figura 3.38(a). Si considera un clock a 100 MHz, che corrisponde a un ciclo di bus di 10 ns. Anche se questo valore può sembrare lento rispetto alle velocità delle CPU moderne, molti bus, come il bus PCI, operano a velocità inferiori, tipicamente 33 MHz o 66 MHz. La lettura dalla memoria richiede 15 ns dal momento in cui l'indirizzo è stabile, il che implica che sono necessari tre cicli di bus per completare una lettura.

Nel dettaglio, il primo ciclo inizia con il fronte di salita di T1 e il terzo ciclo termina con il fronte di salita di T4. I segnali del clock, dell'indirizzo, dei dati e di controllo sono mostrati su una scala temporale comune, con cambiamenti di valore che richiedono 1 ns. Durante T1, la CPU fornisce l'indirizzo, che si stabilizza prima dell'inizio di T2. Le linee $\overline{MREQ}$ e $\overline{RD}$ vengono asserite per indicare una lettura dalla memoria. Poiché la memoria richiede 15 ns per fornire i dati, viene asserita la linea $\overline{WAIT}$ all'inizio di T2 per inserire uno stato di attesa. 

All'inizio di T3, $\overline{WAIT}$ viene negato e i dati sono disponibili sulla linea dati. Durante T3, la CPU legge i dati e quindi nega $\overline{MREQ}$ e $\overline{RD}$. Le specifiche di temporizzazione indicate nella Figura 3.38(b) comprendono vari intervalli temporali, come $T_{AD}$, $T_{DS}$, $T_{MH}$, $T_{RH}$ e $T_{DH}$, che garantiscono il corretto funzionamento del bus sincrono.

Ad esempio, $T_{AD}$ è il tempo massimo entro il quale la CPU deve stabilizzare l'indirizzo dopo il fronte di salita del clock, mentre $T_{DS}$ garantisce che i dati siano disponibili sulla linea almeno 2 ns prima del fronte di discesa del clock. Questi vincoli assicurano che una memoria con un tempo di accesso di 10 ns possa rispondere correttamente entro il ciclo T3. Tuttavia, una memoria più lenta potrebbe richiedere cicli di attesa aggiuntivi.

Infine, il testo sottolinea che la Figura 3.38 è una versione semplificata dei vincoli di temporizzazione reali e che la scelta dei livelli di asserzione dei segnali di controllo (alto o basso) è arbitraria, simile a una decisione di programmazione.
#### 3.4.4.2 - Bus asincroni
Figura 3.39

I bus sincroni funzionano con intervalli temporali definiti dal clock, il che semplifica la progettazione ma introduce alcuni problemi. Ad esempio, tutte le operazioni devono allinearsi ai cicli del clock. Se una CPU e una memoria possono completare un trasferimento in 3,1 cicli, devono comunque estendere il tempo a 4 cicli, poiché non sono consentite frazioni di ciclo. Inoltre, una volta scelto un ciclo di bus, è difficile trarre vantaggio dai progressi tecnologici successivi. Anche con memorie più veloci, il tempo di lettura minimo rimane vincolato ai cicli di clock, limitando il miglioramento delle prestazioni.

In un sistema con dispositivi di velocità diversa, il bus deve funzionare alla velocità del dispositivo più lento. Questo limita le prestazioni complessive, poiché i dispositivi più veloci non possono sfruttare il loro pieno potenziale.

Per gestire dispositivi con prestazioni diverse, si può usare un bus asincrono, che non dipende da un clock principale. In un bus asincrono, il master del bus asserisce un segnale di sincronizzazione ($\overline{MSYN}$) dopo aver impostato l'indirizzo e i segnali necessari. Lo slave esegue l'operazione richiesta alla massima velocità possibile e, una volta completata, asserisce un segnale di sincronizzazione ($\overline{SSYN}$). Il master, vedendo $\overline{SSYN}$ asserito, sa che i dati sono pronti e procede a memorizzarli, quindi nega i segnali di controllo e $\overline{MSYN}$. Lo slave, vedendo $\overline{MSYN}$ negato, sa che l'operazione è terminata e nega $\overline{SSYN}$, riportando il sistema allo stato iniziale.

I bus asincroni utilizzano un meccanismo chiamato **full handshake** per coordinare le operazioni tra master e slave, garantendo che ogni evento sia causato da un evento precedente, indipendentemente dalla temporizzazione del clock. Questo permette a dispositivi con velocità diverse di operare senza influenzarsi a vicenda.

Il principale vantaggio dei bus asincroni è la capacità di gestire dispositivi con prestazioni diverse in modo efficiente. Tuttavia, la maggior parte dei bus è sincrona perché più facile da progettare e implementare. I sistemi sincroni non richiedono feedback tra i dispositivi, semplificando la progettazione, ma a costo di una minore flessibilità e adattabilità ai progressi tecnologici.

(pagine riassunte: 4.5)
### 3.4.5 - Arbitraggio del bus
Nel contesto dei sistemi informatici, la CPU non è l'unico dispositivo che può agire come master del bus; anche i chip di I/O e i coprocessori devono diventare master per accedere alla memoria e gestire gli interrupt. Quando più dispositivi vogliono diventare master simultaneamente, è necessario un **arbitraggio del bus** per evitare conflitti.
#### Arbitraggio Centralizzato
In un sistema centralizzato, il bus ha una linea di richiesta OR-cablata che può essere asserita da più dispositivi. L'arbitro non può distinguere tra dispositivi specifici, solo tra "qualche richiesta" e "nessuna richiesta". Quando rileva una richiesta, concede il bus asserendo una linea di concessione. I dispositivi sono collegati in serie lungo questa linea in uno schema detto **collegamento a festone** (daisy chaining), dove il dispositivo più vicino all'arbitro ha la priorità di accesso al bus. Se questo dispositivo non ha richiesto il bus, la concessione viene propagata al dispositivo successivo, e così via, fino a che uno dei dispositivi accetta la concessione e prende il controllo del bus.

Per evitare che la priorità sia sempre assegnata al dispositivo più vicino, si possono definire **livelli di priorità**, con linee separate per richiesta e concessione. L'arbitro concede il bus al dispositivo con la priorità più alta. Tra dispositivi con la stessa priorità, si utilizza ancora il collegamento a festone.

Un altro miglioramento prevede una terza linea per la conferma dell'acquisizione del bus. Quando un dispositivo accetta la concessione, asserisce questa linea e può negare le altre linee di richiesta e concessione, permettendo agli altri dispositivi di richiedere il bus mentre il primo lo sta utilizzando. Questo permette una transizione più rapida tra dispositivi, migliorando l'utilizzo del bus.

Nei sistemi dove la memoria è sul bus principale, la CPU compete con i dispositivi di I/O. Una soluzione è assegnare alla CPU la priorità più bassa, permettendo l'uso del bus solo quando nessun altro lo richiede, poiché la CPU può solitamente aspettare, mentre i dispositivi di I/O hanno esigenze di temporizzazione più stringenti.
#### Arbitraggio Decentralizzato
Un'alternativa è l'arbitraggio decentralizzato, che può avere fino a 16 linee di richiesta con priorità diverse. Ogni dispositivo asserisce la propria linea quando richiede il bus. Questo metodo, sebbene richieda più linee, elimina il costo dell'arbitro centrale. Tuttavia, il numero di dispositivi è limitato dal numero di linee di richiesta.

Un altro schema decentralizzato utilizza solo tre linee: una linea OR-cablata per le richieste, una linea BUSY asserita dal master corrente, e una linea di arbitraggio a festone, mantenuta asserita da un'alimentazione di 5 volt. Questo sistema assegna il bus al dispositivo più a sinistra che richiede il bus, simile al collegamento a festone, ma senza un arbitro centrale. Questo rende il sistema più economico, veloce e meno suscettibile a guasti.

(pagine riassunte: 3)
### 3.4.6 - Operazioni del bus
Finora abbiamo esaminato i bus con un master, solitamente la CPU, che legge o scrive dalla memoria. Tuttavia, esistono altri tipi di bus che vedremo ora.

Spesso è più efficiente trasferire un intero blocco di dati in una volta sola, come quando si utilizza la cache. Il master comunica allo slave quanti dati trasferire e lo slave restituisce un dato per ciclo fino a quando il conteggio non si esaurisce. Questo schema permette di ridurre il numero di cicli di bus necessari per trasferire un blocco.

Nei sistemi multiprocessore, è importante evitare che più CPU accedano simultaneamente a dati critici in memoria. Si utilizza un ciclo di bus leggi-modifica-scrivi che consente a una CPU di leggere, analizzare e riscrivere dati senza rilasciare il bus, evitando interferenze da parte di altre CPU.

Un altro tipo di ciclo di bus gestisce gli interrupt. L'assegnazione delle priorità e l'arbitraggio sono necessari per gestire gli interrupt da dispositivi diversi. Tipicamente, un controllore di interrupt come il 8259A di Intel viene utilizzato per gestire gli interrupt da più dispositivi di I/O.

Il 8259A ha otto input che possono essere collegati a dispositivi di I/O e quando uno di essi genera un interrupt, il 8259A segnala alla CPU. La CPU risponde e il 8259A specifica quale dispositivo ha causato l'interrupt. Questo chip può essere cascato per gestire fino a 64 dispositivi di I/O.

Questi concetti forniscono una base per comprendere il funzionamento dei bus e la loro interazione con le CPU. Ora passeremo a esaminare alcune CPU commerciali e i loro bus per una comprensione più dettagliata.

(pagine riassunte: 2.5)
## 3.5 - Esempi di chip della CPU
In questo paragrafo esamineremo a livello hardware, in modo piuttosto dettagliato, i chip Intel Core i7, TI OMAP4430 e Atmel ATmega168.
### 3.5.1 - Intel Core i7
Il Core i7 rappresenta l'evoluzione diretta della CPU 8088 utilizzata nei primi PC IBM. La larghezza di linea dei chip, determinata dalla grandezza dei collegamenti tra i transistor, influisce sulla velocità e sulla capacità del chip stesso. Le versioni iniziali del Core i7 si basavano sull'architettura "Nahalem", mentre le successive su "Sandy Bridge", con una notevole crescita nella potenza di calcolo.

Questo processore è completamente compatibile con il 8088 e può eseguire i suoi programmi senza modifiche. È una macchina a 64 bit, multicore e *hyperthreaded*, consentendo l'esecuzione simultanea di più thread hardware. Internamente, il Core i7 è una macchina superscalare a 4 livelli, capace di eseguire fino a 4 istruzioni contemporaneamente.

La presenza di 3 livelli di cache migliora le prestazioni del processore, ma richiede più silicio, con modelli che possono raggiungere fino a 17 MB di cache. Per garantire la coerenza della memoria in sistemi multiprocessore, ogni CPU effettua uno **snooping** sul bus della memoria.

I Core i7 utilizzano due bus esterni principali: un bus di memoria DDR3 e un bus PCI Express per i dispositivi di I/O. Inoltre, dispongono di una porta **QPI**(*Quick Path Interconnect*) per la connessione a interconnessioni esterne e per la gestione del multiprocessore.

Il consumo energetico e il calore generato sono problematici, quindi il chip è progettato per essere raffreddato da dissipatori di calore e ventole. Per risparmiare energia, la CPU può entrare in stati di "riposo" o "sonno profondo" quando inattiva, con cinque stati intermedi tra l'esecuzione completa e il sonno profondo, dove alcune funzionalità sono disabilitate per ridurre il consumo energetico.
#### 3.5.1.1 - Disposizione logica dei contatti del Core i7
Il Core i7 ha 1155 pin, di cui 447 per segnali, 286 per alimentazione, 360 per terra, e 62 riservati per futuri utilizzi. Tuttavia, il numero effettivo di segnali distinti è 131, poiché alcuni segnali logici utilizzano più pin.

Ci sono cinque gruppi principali di segnali per il bus di memoria sul lato sinistro della figura. Questi includono segnali per indirizzo, dati, controllo e clock, utilizzati per interfacciarsi con le DRAM compatibili DDR3. Un altro gruppo è l'interfaccia PCI Express, che consente la connessione diretta delle periferiche alla CPU. Il Core i7 supporta un'interfaccia x16, che gestisce 16 corsie simultaneamente per una larghezza di banda aggregata di 16 GB/sec.

Il **DMI** (*Direct Media Interface*) è un altro bus utilizzato per il collegamento CPU-chipset, simile a PCI Express ma con una velocità dimezzata. Il chipset Core i7 utilizza i chip P67 e ICH10, che forniscono una vasta gamma di interfacce e circuiti, semplificando la costruzione di un PC completo.

Il Core i7 può essere configurato per utilizzare gli interrupt in modo simile all'8088 oppure tramite un dispositivo chiamato **APIC** (*Advanced Programmable Interrupt Controller*). È inoltre in grado di funzionare a diverse tensioni, ma richiede la conoscenza di quella utilizzata.

Nonostante una gestione avanzata dell'alimentazione, il Core i7 si riscalda notevolmente. Ogni chip contiene sensori di temperatura per la protezione dei circuiti, attivando la limitazione termica (*thermal throttling*) quando necessario.

Il segnale Clock fornisce il clock di sistema al processore, utilizzato internamente per generare clock basati su multipli o frazioni. Questo può essere fatto anche con un dispositivo chiamato **DLL** (*Delay-Locked Loop*).

Ci sono anche segnali per diagnostica, testing e debugging secondo lo standard IEEE 1149.1 dei test **JTAG**(*Joint Test Action Group*), oltre a vari altri segnali per utilizzi particolari.
#### 3.5.1.2 - Pipeline sul bus di memoria DDR3 del Core i7
Le moderne CPU come il Core i7 richiedono molto dalle memorie DRAM. I singoli processori possono generare richieste di accesso più rapidamente di quanto una DRAM lenta possa rispondere, e questo problema si amplifica con richieste simultanee da più processori. Per evitare che la CPU rimanga in attesa, è essenziale ottenere il massimo throughput dalla memoria, che può essere ottenuto attraverso l'architettura a pipeline delle memorie DRAM.

Le richieste di memoria del Core i7 seguono tre fasi:
1. **Fase di ACTIVATE**: "apre" una riga della DRAM per prepararla a successivi accessi.
2. **Fase di READ o WRITE**: permette accessi multipli a singole parole o a una sequenza di parole della riga aperta, utilizzando il burst mode.
3. **Fase di PRECHARGE**: "chiude" la riga corrente e prepara la memoria per il prossimo comando ACTIVATE.

Il segreto dell'efficacia dell'accesso alla memoria del Core i7 risiede nella struttura a più banchi della DRAM DDR3 sul chip. Una DRAM DDR3 è tipicamente composta da 8 banchi, e l'interfaccia DDR3 consente fino a quattro accessi concorrenti su un singolo canale. Gli accessi sono sovrapposti per permettere letture parallele sullo stesso chip.

L'interfaccia di memoria DDR3 ha quattro segnali principali: il *clock* del bus (CK), il segnale di *comando* (CMD), il segnale di *indirizzo* (ADDR) e quello di *dato* (DATA). Il segnale CK dirige tutte le attività del bus, CMD indica l'attività richiesta alla DRAM, e ACTIVATE specifica l'indirizzo della riga DRAM da aprire tramite ADDR.

Il parallelismo delle richieste di memoria si manifesta nelle richieste READ a distinti banchi di DRAM. Il Core i7 gestisce le tempistiche delle risposte alle richieste READ e l'inizio di nuove richieste grazie a un modello completo delle attività interne di ogni DRAM DDR3 collegata. Questo è possibile perché l'interfaccia DDR3 è una **sincrona di memoria**, con ogni attività che impiega un numero noto di cicli di bus DDR3.

(pagine riassunte: 7)
### 3.5.2 - Texas Instruments OMAP4430
Il **SoC** (*System-on-a-Chip*) Texas Instruments (TI) OMAP4430 è una CPU che implementa il set di istruzioni ARM, progettata per applicazioni mobili ed embedded come smartphone, tablet e dispositivi Internet. Questo SoC incorpora vari dispositivi per formare un sistema completo, comprendendo due Core ARM A9, tre acceleratori (un processore grafico PowerVR SGX540, un processore di segnale di immagine ISP e un processore video IVA3), e numerose interfacce per periferiche come touchscreen, DRAM, Flash, USB e HDMI.

Il SoC OMAP4430, lanciato nel 2011, ha due Core ARM A9 a 1 GHz, realizzati con tecnologia a 45 nanometri. È progettato per eseguire molti calcoli con basso consumo energetico, ideale per dispositivi mobili alimentati a batteria. Gli acceleratori programmabili SGX540, ISP e IVA3 consentono di eseguire compiti specifici in modo efficiente, riducendo il carico sui Core ARM A9 e risparmiando energia. A pieno carico, il SoC consuma solo 600 mW di potenza, una frazione di quella utilizzata da un Core i7 di fascia alta.

Il SoC OMAP4430 implementa tecniche di gestione dell'energia come la *scala dinamica di tensione* e il *power gating* per ridurre ulteriormente il consumo energetico. La scala dinamica di tensione permette ai componenti di funzionare a velocità e tensioni ridotte quando non è necessaria la massima velocità, mentre il power gating disattiva completamente i componenti non utilizzati, risparmiando energia. Ad esempio, il processore video IVA3 può essere spento quando non è in uso.

I Core ARM A9 dell'OMAP4430, nonostante il loro basso consumo energetico, sono capaci di decodificare ed eseguire fino a 2 istruzioni per ciclo. Il sistema di memoria dell'OMAP4430 comprende due cache L1 (32 KB ciascuna per istruzioni e dati per ogni Core) e una cache L2 condivisa da 1 MB, alimentate tramite due canali DRAM LPDDR2 a bassa potenza, ottimizzati per l'efficienza energetica. Le cache migliorano le prestazioni riducendo il tempo di accesso ai dati più frequentemente utilizzati.

Il SoC è distribuito in un supporto **PBGA** (*ball grid array*) con 547 pin, simile agli LGA ma con sfere di metallo invece di pad quadrati. La matrice rettangolare di sfere evita l'inserimento errato del chip nel socket BGA.

Confrontare il SoC OMAP4430 (architettura RISC) con il Core i7 (architettura CISC) basandosi solo sulla velocità di clock è difficile. Nonostante l'OMAP4430 possa eseguire quattro istruzioni per ciclo di clock come il Core i7, quest'ultimo opera a una frequenza di clock molto più alta (3,5 GHz contro 1 GHz) e dispone di più processori, rendendolo più veloce. Tuttavia, l'OMAP4430 consuma molta meno energia, rendendolo più efficiente in dispositivi alimentati a batteria.

(pagine riassunte: 3.75)
### 3.5.3 - Il microcontrollore Atmel ATmega168
Il Core i7 e l'OMAP4430 sono piattaforme ad alte prestazioni progettate per differenti tipi di dispositivi: il Core i7 è destinato principalmente alle applicazioni desktop, mentre l'OMAP4430 è rivolto alle applicazioni mobili. Tuttavia, esiste un altro settore molto vasto: quello dei sistemi integrati, dove il microcontrollore Atmel ATmega168 è particolarmente diffuso per il suo basso costo e versatilità.

L'ATmega168 è un microcontrollore con 28 pin, privo di linee di indirizzo e dati esterne, poiché tutta la memoria (SRAM e Flash) è integrata nel chip stesso. Questo microcontrollore dispone di 27 porte di I/O (8 ciascuna nelle porte B e D, 7 nella porta C), configurabili come input o output tramite software. Sei segnali della porta C possono anche essere configurati come I/O analogici per leggere o impostare livelli di tensione.

Internamente, l'ATmega168 è un SoC con 16 KB di memoria flash, 1 KB di EEPROM e 1 KB di SRAM. Il processore interno esegue 131 istruzioni AVR, ognuna lunga 16 bit, operando su dati a 8 bit con registri interni da 8 bit. Include anche un orologio in tempo reale e diverse interfacce, come collegamenti seriali, PWM, I2C e controllori di I/O digitale e analogico.
## 3.6 - Esempi di bus
I bus sono fondamentali per l'integrazione dei componenti nei sistemi di calcolo. Tra i più diffusi ci sono il bus PCI e l'Universal Serial Bus (USB). 
- **Bus PCI**: Utilizzato principalmente per il collegamento delle periferiche nei PC, esistono due versioni principali: il tradizionale PCI e il più recente e veloce PCI Express (PCIe).
  - **Universal Serial Bus (USB)**: Ideale per periferiche a bassa velocità come mouse e tastiere, ha guadagnato popolarità grazie alle sue nuove versioni, USB 2.0 e USB 3.0, che offrono velocità molto superiori.
Nei paragrafi successivi verranno analizzati in dettaglio questi bus per comprendere meglio il loro funzionamento.
### 3.6.1 - Bus PCI
I bus sono fondamentali per collegare i componenti nei sistemi di calcolo. In passato, il bus ISA, con una larghezza di banda massima di 16,7 MB/s, e il bus **EISA**, con 33,3 MB/s, erano utilizzati, ma non erano sufficienti per esigenze moderne come la visualizzazione di video a schermo intero. Intel ha quindi sviluppato il bus PCI (Peripheral Component Interconnect) con una larghezza di banda maggiore, fino a 528 MB/s, rendendo possibile il supporto di video Full HD.

Nonostante la larghezza di banda migliorata, il bus PCI aveva due problemi principali: non poteva essere usato come bus di memoria e non era compatibile con le vecchie schede ISA. Per risolvere questi problemi, Intel progettò sistemi con tre o più bus e sviluppò chip bridge per connettere la CPU, la memoria e i bus PCI e ISA.

Il bus PCI supporta diverse tensioni (5 volt per i sistemi più vecchi e 3,3 volt per quelli più recenti) e dispone di meccanismi per evitare l'inserimento errato delle schede. Negli anni '90, il bus ISA fu considerato obsoleto e sostituito dal bus **AGP** (*Accelerated Graphics Port*) per supportare risoluzioni grafiche più elevate.

Il bus PCI è sincrono, con tutte le transazioni tra un master (**iniziatore**) e uno slave (**destinatario**), e utilizza linee multiplexate per indirizzi e dati per ridurre il numero di pin. Le operazioni di lettura e scrittura richiedono almeno tre cicli, con possibilità di inserire stati di attesa e trasferimenti di blocchi di dimensione illimitata.
#### 3.6.1.1 - Arbitraggio del bus PCI
Prima di poter utilizzare il bus PCI, i dispositivi devono acquisirlo. Nella maggior parte delle architetture l'arbitro del bus è integrato in uno dei chip bridge. Ogni dispositivo PCI ha due linee dedicate che lo collegano all'arbitro: una, $REQ\#$, per richiedere il bus, e l’altra, $GNT\#$, per riceverne la concessione.

Per richiedere il bus un dispositivo PCI (compresa la CPU) deve asserire $REQ\#$ e attendere finché non veda che la linea $GNT\#$ è stata asserita dall’arbitro.

Il bus viene concesso per una transazione alla volta, anche se può avere lunghezza teoricamente illimitata. Se un dispositivo vuole effettuare una seconda transazione e nessun altro dispositivo sta richiedendo il bus, allora può continuare a utilizzarlo; tuttavia tra la prima e la seconda transazione deve spesso essere inserito un ciclo di inattività. L'arbitro può negare la linea $GNT\#$ nel caso in cui un master stia effettuando un trasferimento molto lungo e contemporaneamente qualche altro dispositivo richieda il bus. Dato che il master del bus deve monitorare la linea $GNT\#$, esso deve rilasciare il bus al ciclo successivo non appena vede che la linea è stata negata. Questo schema permette trasferimenti molto lunghi quando c'è un solo candidato master, ma allo stesso tempo continua a garantire una risposta veloce quando più dispositivi competono per l'utilizzo del bus.
#### 3.6.1.2 - Segnali del bus PCI
Il bus PCI è costituito da segnali obbligatori e opzionali. I segnali obbligatori includono $CLK$, che sincronizza il bus; $AD$, per indirizzi e dati; $PAR$, un segnale di parità per $AD$; $C/BE\#$, per comandi e byte validi; $FRAME\#$, per iniziare una transazione; $IRDY\#$, per indicare la disponibilità dei dati in ingresso; $IDSEL$, per selezionare un dispositivo PCI; e $DEVSEL\#$, per annunciare la prontezza dello slave.

I segnali asseriti dallo slave includono $TRDY\#$, per indicare la disponibilità dei dati in uscita; $STOP\#$, per annullare una transazione in caso di errore; $PERR\#$, per segnalare errori di parità sui dati; e $SERR\#$, per notificare errori di sistema.

I segnali $REQ64\#$ e $ACK64\#$ gestiscono le transazioni a 64 bit, mentre $LOCK$ permette di bloccare il bus. Altri segnali includono $INTx$ per richiedere interrupt, $JTAG$ per il testing e $M66EN$ per impostare la velocità di clock.
#### 3.6.1.3 - Transazioni del bus PCI
Figura 3.55

Il bus PCI è semplice nel funzionamento. Consideriamo il diagramma di temporizzazione di una transazione di lettura seguita da una di scrittura. Durante T1, al fronte di discesa del clock, il master inserisce l'indirizzo di memoria su $AD$ e il comando su $C/BE\#$, e asserisce $FRAME\#$ per iniziare la transazione.

In T2, il master rilascia l'indirizzo per permettere allo slave di pilotarlo in T3, e modifica $C/BE\#$ per indicare quali byte leggere. In T3, lo slave asserisce $DEVSEL\#$ per confermare la ricezione dell'indirizzo, scrive i dati su $AD$, e asserisce $TRDY\#$. Se lo slave non può rispondere immediatamente, deve comunque asserire $DEVSEL\#$ ma lasciare $TRDY\#$ negato fino a quando i dati sono pronti, inserendo stati di attesa se necessario.

Dopo un ciclo di inattività, in T5 il master inizia una scrittura, inserendo indirizzo e comando su $AD$ e $C/BE\#$ e asserendo i dati già in T6, senza bisogno di inversione del bus poiché il master continua a pilotare $AD$. In T7, la memoria accetta i dati.

(pagine riassunte: 8.75)
### 3.6.2 - PCI Express
Il bus PCI, pur essendo adeguato per molte applicazioni, non riesce a soddisfare la crescente domanda di larghezza di banda per l'I/O. La frequenza di clock non può essere ulteriormente aumentata a causa di problemi tecnici come il disallineamento del bus e le interferenze. Per i dispositivi di I/O troppo veloci, Intel ha aggiunto porte speciali nel chip bridge per bypassare il bus PCI, ma questa non è una soluzione sostenibile a lungo termine.

Un altro limite del bus PCI è la dimensione delle schede, che sono troppo grandi per laptop e dispositivi mobili. La soluzione vincente è stata il **PCI Express**, che, nonostante il nome, ha poco a che fare con il bus PCI tradizionale e non è un vero e proprio bus. Oggi, il PCI Express è lo standard nei computer.
#### 3.6.2.1 - Architettura di PCI Express
Il PCI Express (PCIe) si distingue radicalmente dal tradizionale bus PCI adottando un'architettura basata su connessioni seriali punto-a-punto ad alta velocità invece di un bus parallelo con molteplici master e slave. Questo approccio innovativo, ispirato dalla commutazione Ethernet nelle reti locali, fornisce un commutatore centrale per connettere i chip tramite collegamenti seriali.

Le principali differenze rispetto al bus PCI sono tre:
1. **Commutatore centralizzato**: Sostituisce il bus con un dispositivo centrale per gestire le connessioni.
2. **Connessioni seriali punto-a-punto**: Al posto del bus parallelo, ogni chip ha una connessione dedicata composta da due fili (uno per il segnale e uno per la terra) per migliorare l'immunità al rumore.
3. **Modello di trasferimento dati a pacchetti**: Anziché un master che comanda uno slave, il PCIe utilizza un modello in cui i dispositivi si scambiano pacchetti di dati, ciascuno contenente un'intestazione e un campo dati.

In aggiunta, il PCIe utilizza codici di rilevazione degli errori per maggiore affidabilità, supporta connessioni fino a 50 cm di lunghezza per un migliore partizionamento del sistema, permette l'espansione tramite ulteriori commutatori, e le connessioni seriali più piccole permettono dispositivi più compatti. In sostanza, PCIe rappresenta un significativo cambiamento rispetto al tradizionale bus PCI.
#### 3.6.2.2 - Pila di protocolli di PCI Express
Il sistema PCI Express (PCIe) adotta un'architettura stratificata di **protocolli**, ispirata al modello delle reti a commutazione di pacchetto. Una pila di protocolli è una gerarchia che separa le diverse funzioni di comunicazione in livelli distinti, favorendo una progettazione modulare e flessibile. Questo approccio, comune nel software delle reti, viene applicato qui all'hardware del bus.
##### Livello fisico
Il livello fisico gestisce la trasmissione dei bit lungo le connessioni punto-a-punto, composte da coppie di collegamenti simplex chiamate **corsie**. Ogni corsia ha due fili, uno per il segnale e uno per la terra, assicurando un'elevata immunità al rumore. A differenza dei bus tradizionali, PCIe non ha un clock principale; i dispositivi trasmettono dati non appena disponibili, utilizzando la **codifica 8b/10b** per distinguere i dati da un collegamento inattivo.
##### Livello di trasmissione
Il livello di trasmissione si occupa della trasmissione dei pacchetti. Aggiunge a ogni pacchetto un numero di sequenza e un codice **CRC** per la correzione degli errori. Il destinatario verifica il CRC e, se corretto, invia un **pacchetto di acknowledgment**. In caso contrario, richiede una ritrasmissione. Questo livello include anche un meccanismo di controllo di flusso per evitare il sovraccarico del destinatario.
##### Livello di transazione
Il livello di transazione gestisce le operazioni sul bus, suddividendo le connessioni in più **circuiti virtuali** per gestire diverse classi di traffico. Le transazioni possono riguardare quattro spazi di indirizzi:
1. **Spazio di memoria** per letture e scritture ordinarie.
2. **Spazio di I/O** per indirizzare i registri del dispositivo.
3. **Spazio di configurazione** per l'inizializzazione del sistema.
4. **Spazio dei messaggi** per segnalazioni e interrupt.
##### Livello software
Il livello software interfaccia il sistema PCIe con il sistema operativo, emulando il bus PCI per garantire la retrocompatibilità. Tuttavia, per sfruttare appieno le capacità di PCIe, i sistemi operativi devono essere aggiornati.
##### Processo di trasmissione
Quando un comando viene passato dal livello software, il livello di transazione lo riformula in termini di intestazione e campo dati. Il livello di trasmissione aggiunge il numero di sequenza e il CRC, mentre il livello fisico completa il pacchetto con le informazioni necessarie per la trasmissione. Il destinatario esegue l'operazione inversa per ricevere il pacchetto.

In sintesi, PCIe rappresenta un'evoluzione significativa rispetto ai tradizionali bus PCI, implementando una struttura a livelli simile a quella delle reti, ma interamente in hardware.

(pagine riassunte: 5)
### 3.6.3 - Universal Serial Bus
Il bus PCI e PCI Express sono ideali per collegare periferiche ad alta velocità al computer, ma risultano troppo costosi per dispositivi a bassa velocità come tastiere e mouse. Tradizionalmente, i dispositivi di I/O standard venivano connessi al computer in modo specifico, mentre gli slot ISA e PCI venivano lasciati liberi per l'aggiunta di nuovi dispositivi, creando spesso problemi.

Nel 1993, sette aziende si unirono per sviluppare un metodo migliore per collegare periferiche a bassa velocità. Questo sforzo culminò nel 1998 con l'introduzione dello standard **USB** (Universal Serial Bus), oggi largamente diffuso nei personal computer.
#### Obiettivi del Progetto USB:
1. Evitare la necessità di impostare interruttori e contatti sulle schede dei dispositivi.
2. Permettere l'installazione di nuovi dispositivi senza aprire il computer.
3. Utilizzare un solo tipo di cavo per tutti i dispositivi.
4. Fornire alimentazione ai dispositivi tramite il cavo.
5. Consentire il collegamento di fino a 127 dispositivi a un singolo computer.
6. Supportare dispositivi che operano in tempo reale (es. dispositivi audio, telefoni).
7. Consentire l'installazione di dispositivi a computer acceso.
8. Eliminare la necessità di riavviare il sistema dopo l'installazione di nuovi dispositivi.
9. Mantenere bassi i costi di produzione del nuovo bus e dei dispositivi di I/O.
#### Struttura e Funzionamento di USB:
- **Hub Principale:** Collegato al bus del sistema, con prese per cavi che connettono dispositivi di I/O o hub di espansione. La topologia è ad albero, con l'hub principale come radice.
- **Cavi USB:** Composti da quattro collegamenti: due per i dati, uno per l'alimentazione (+5 volt) e uno per la terra. La segnalazione trasmette uno 0 come una transizione di tensione e un 1 come l’assenza di transizione.
- **Rilevamento e Configurazione:** Quando si collega un nuovo dispositivo, l'hub principale lo rileva e interrompe il sistema operativo, che interroga il dispositivo e gli assegna un indirizzo univoco (1-127) se c'è sufficiente larghezza di banda.
- **Pipe Logiche:** Dal punto di vista logico, USB è un insieme di pipe (condotti) di bit che vanno dall'hub principale alle periferiche di I/O, con possibilità di suddividere ogni pipe in un massimo di 16 condotti per diversi tipi di dati.
- **Sincronizzazione:** L'hub principale invia un frame in broadcast ogni 1,00 ± 0,05 ms per mantenere sincronizzati tutti i dispositivi.
#### Tipi di Frame:
1. **Controllo:** Per configurare i dispositivi, assegnare comandi e interrogarli.
2. **Isocrono:** Per dispositivi in tempo reale che necessitano di dati a intervalli precisi, senza ritrasmissione in caso di errore.
3. **Bulk:** Per trasferimenti di grandi dimensioni non in tempo reale (es. stampanti).
4. **Interrupt:** Necessari poiché USB non supporta gli interrupt tradizionali.
#### Tipi di Pacchetti:
1. **Token:** Controllano il sistema, come il pacchetto SOF (Start of Frame) che marca l'inizio di ogni frame.
2. **Dati:** Contengono il campo dati, un identificatore del tipo di pacchetto e un CRC per rilevare errori.
3. **Handshake:** Confermano la corretta ricezione dei pacchetti (ACK), indicano errori (NAK) o segnalano occupazione (STALL).
4. **Speciali:** Per funzionalità specifiche del sistema.
#### Evoluzioni di USB:
- **USB 2.0:** Introdotto nel 1998 con differenze come l'interfaccia EHCI (Enhanced Host Controller Interface) per migliorare l'efficienza.
- **USB 3.0:** Annunciato otto anni dopo, supporta velocità fino a 5 Gbps e mantiene la retrocompatibilità con USB 2.0, adattandosi automaticamente alla velocità del cablaggio.

USB ha rivoluzionato la connessione di dispositivi di I/O a bassa velocità, rendendo l'installazione più semplice e il sistema più flessibile e scalabile.

(pagine riassunte: 4)
## 3.7 - Interfacce
Un classico calcolatore di piccole e medie dimensioni è composto da un chip della CPU, da un chipset, da alcuni chip di memoria e da alcuni dispositivi di I/O, tutti connessi fra loro mediante un bus. A volte tutti questi componenti vengono integrati in un unico SoC, come nel caso del TI OMAP4430. È giunto ora il momento di analizzare le interfacce di I/O; è attraverso queste porte che il calcolatore comunica con il mondo esterno.
### 3.7.1 - Interfacce di I/O
Numerose interfacce di I/O sono già disponibili e con il passare del tempo ne vengono introdotte sempre di nuove. Una **UART** (*Universal Asynchronous Receiver Transmitter*) è un’interfaccia che può leggere un byte da un bus di dati e generarlo in output, un bit alla volta, su una linea seriale per un terminale, oppure può ricevere input da un terminale. Le interfacce **USART** (*Universal Synchronous Asynchronous Receiver Transmitters*) possono gestire trasmissioni sincrone utilizzando vari protocolli, oltre a supportare tutte le funzionalità UART. Dato che le interfacce UART hanno perso importanza con la scomparsa dei modem telefonici, analizzeremo ora l’interfaccia parallela come esempio di chip di I/O.
#### 3.7.1.1 - Interfacce PIO
L'interfaccia **PIO** (*Parallel Input/Output*), basata sul progetto Intel 8255 A, è un esempio comune di interfaccia di input/output parallela. Dotata di una serie di linee di I/O, può connettere una varietà di dispositivi digitali come tastiere, interruttori, luci e stampanti, offrendo grande flessibilità al programma della CPU che può scrivere o leggere lo stato di ogni linea.

Solitamente utilizzata nei sistemi integrati, l'interfaccia PIO si configura tramite un registro di configurazione a 3 bit, che determina se le tre porte indipendenti a 8 bit devono funzionare in modalità input (0) o output (1). Ogni porta è associata a un registro latch a 8 bit, e la CPU può leggere direttamente il registro per utilizzare una porta in input.

È possibile realizzare interfacce PIO più avanzate, ad esempio per l'handshaking con dispositivi esterni. Dal diagramma funzionale del PIO, si notano 24 pin per le tre porte, più linee per il bus dati, la selezione del chip, lettura e scrittura, indirizzi e reset. Le linee d'indirizzo selezionano i quattro registri interni, corrispondenti alle porte A, B, C e al registro di configurazione.
### 3.7.2 - Decodifica dell'indirizzo
