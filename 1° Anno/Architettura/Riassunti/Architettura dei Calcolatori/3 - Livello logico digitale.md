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

### 3.1.4 - Equivalenza di circuiti

## 3.2 - Circuiti logici digitali elementari

### 3.2.1 - Circuiti integrati

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
