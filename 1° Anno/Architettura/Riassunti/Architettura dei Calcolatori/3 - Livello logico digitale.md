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

### 3.2.3 - Circuiti per l'aritmetica

### 3.2.4 - Clock

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
