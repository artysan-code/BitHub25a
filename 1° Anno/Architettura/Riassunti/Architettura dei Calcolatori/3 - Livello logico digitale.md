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

### 3.3.1 - Latch

### 3.3.2 - Flip-Flop

### 3.3.3 - Registri

### 3.3.4 - Organizzazione della memoria

### 3.3.5 - Chip di memoria

### 3.3.6 - RAM e ROM

## 3.4 - Chip della CPU e bus

### 3.4.1 - Chip della CPU

### 3.4.2 - Bus del calcolatore

### 3.4.3 - Ampiezza del bus

### 3.4.4 - Temporizzazione del bus

### 3.4.5 - Arbitraggio del bus

### 3.4.6 - Operazioni del bus

## 3.5 - Esempi di chip della CPU

### 3.5.1 - Intel Core i7

### 3.5.2 - Texas Instruments OMAP4430

### 3.5.3 - Il microcontrollore Atmel ATmega168

## 3.6 - Esempi di bus

### 3.6.1 - Bus PCI

### 3.6.2 - PCI Express

### 3.6.3 - Universal Serial Bus

## 3.7 - Interfacce

### 3.7.1 - Interfacce di I/O

### 3.7.2 - Decodifica dell'indirizzo
