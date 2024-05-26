(Pagine riassunte: 29)

A differenza degli altri livelli, il _linguaggio assemblativo_ è implementato mediante la _traduzione_ anziché l'interpretazione.

Il **traduttore** è il programma che si occupa di convertire un programma utente, scritto in _linguaggio sorgente_, in un _linguaggio di destinazione_. Questo processo viene utilizzato quando si dispone di un processore per il linguaggio di destinazione ma non per quello sorgente. Il programma sorgente non viene eseguito direttamente; invece, viene tradotto in un programma chiamato _oggetto_ o _eseguibile binario_, che poi viene eseguito.

(Pagine riassunte: 1)
## 7.1 - Introduzione al linguaggio assemblativo
Possiamo suddividere i traduttori in due categorie principali: gli assemblatori, che convertono i linguaggi sorgente simbolici in linguaggi macchina numerici, e i compilatori, che trasformano i linguaggi sorgente di alto livello in linguaggi macchina numerici o in una rappresentazione simbolica.

(Pagine riassunte: 0.25)
### 7.1.1 - Che cos'è un linguaggio assemblativo
Una linea di codice in linguaggio assemblatore corrisponde direttamente a una riga di codice in linguaggio macchina. Pertanto, un programma sorgente composto da _n_ linee produrrà un codice macchina di _n_ linee. 

I programmatori utilizzano il linguaggio assembly per sfruttare simboli mnemonici come ADD, SUB, e MUL, che sono più facili da ricordare rispetto ai codici ottali o esadecimali corrispondenti. Ugualmente per gli indirizzi, assegnando nomi che sarà compito dell'assemblatore di decodificare.

Un programmatore che utilizza il linguaggio assemblativo ha accesso a tutte le funzionalità della macchina, diversamente da un programmatore che usa linguaggi di alto livello (che può manipolare i dati a livello di bit). Tuttavia, un programma scritto in linguaggio assemblativi è specifico per una particolare macchina, mentre i programmi scritti in linguaggi di alto livello possono essere compilati per diverse piattaforme.

(Pagine riassunte: 1)
### 7.1.2 - Perché usare il linguaggio assemblativo 
Analizziamo nel dettaglio la seguente domanda: _perché programmare in linguaggio assembly?_ Ci sono due principali motivi: **prestazioni** e **funzionalità**.

Un programmatore esperto, che conosce a fondo il linguaggio assemblativo e i metodi di codifica ottimali, può creare un codice più piccolo e veloce rispetto a un codice scritto in linguaggi di alto livello. Inoltre, ci sono particolari situazioni che possono essere implementate solo utilizzando il linguaggio assembly, poiché offre un accesso più diretto all'hardware della macchina. Basta pensare ai programmi del BIOS, dei driver e dei firmware.

(Pagine riassunte: 0.75)
### 7.1.3 - Formato delle istruzioni del linguaggio assemblativo
La struttura delle istruzioni nei linguaggi assembly è generalmente composta da quattro parti: _campo etichetta_, _codice operativo (opcode)_, _campo operandi_ e _campo commenti_. A livello educativo, si tratta comunemente di processori x86, anche se noi lavoriamo su ARMv7.

Le **etichette** vengono utilizzate per assegnare un nome simbolico a un indirizzo e definire le destinazioni per le istruzioni di salto, oltre a permettere l'accesso ai dati memorizzati mediante nomi simbolici.

In questa architettura, così come in altre, vengono assegnati nomi simbolici agli indirizzi, come ad esempio _EAX_, _EBX_, _ECX_ e così via.

L'**opcode** contiene un'abbreviazione simbolica del codice operativo o un comando per l'assemblatore. Ad esempio, _MOV_ serve per caricare o memorizzare un registro, mentre _DD_ (Define Double) serve a definire uno spazio per una variabile (in questa architettura la parola è definita a 16 bit quindi double sta per parola doppia a 32 bit).

Il **campo operandi** contiene gli operandi dell'istruzione definita dall'opcode. Ad esempio, per un'istruzione di somma, conterrà i registri da sommare e il registro in cui inserire il risultato (su ARM, ad esempio).

Infine, il **campo commenti** è una zona dove i programmatori possono fornire informazioni sull'istruzione o sulla funzione, senza che queste vengano considerate dall'assemblatore.

(Pagine riassunte: 2)
### 7.1.4 - Pseudoistruzioni
Nei linguaggi assembly, le istruzioni dirette all'assemblatore sono chiamate pseudoistruzioni o direttive dell'assemblatore. Un esempio di pseudoistruzione è l'opcode DD, che indica all'assemblatore di definire uno spazio per una doppia parola, quindi 32 bit. Esistono molti altri esempi e diverse pseudoistruzioni, ma per evitare di trattare un'architettura diversa da quella che stiamo studiando, consideriamo il seguente esempio:

```assembly_x86
WORDSIZE EQU 32
IF WORDSIZE GT 32
WSIZE: DD 64
ELSE
WSIZE: DD 32
ENDIF
```

In questo codice, vediamo un'allocazione controllata da una condizione. In base al valore di _WORDSIZE_ (in questo caso 32), alloca uno spazio per una parola di 64 o 32 bit. Questa è una tecnica efficace che rende il codice adattabile a diverse situazioni, evitando la necessità di compilare codici separati per ogni caso specifico.

(Pagine riassunte: 2.5)
## 7.2 - Macroistruzioni
Molti programmatori si trovano a dover riscrivere ripetutamente la stessa sequenza di codice. Grazie alle **macro** o **macroistruzioni**, questo problema viene risolto, poiché permettono di trasformare una sequenza di codice in una _procedura_ che può essere richiamata quando necessario (verrà chiarita la differenza tra procedura e macro più tardi). Tuttavia, se le sequenze sono brevi, il richiamo della procedura può introdurre un lavoro aggiuntivo che rallenta il programma.

(Pagine riassunte: 0.25)
### 7.2.1 - Definizione, chiamata ed espansione di macro
Nei linguaggi assembly, quando viene definita una macro (delimitata da _MACRO_ e _ENDM_ in x86), l'assemblatore prende la sequenza di codice e la inserisce nella tabella delle definizioni di macro per un utilizzo successivo. Un esempio di codice macro è il seguente:

```
SWAP    MACRO
		MOV EAX, P
		MOV EBX, Q
		MOV Q, EAX
		MOV P, EBX
		ENDM
		
		SWAP
		
		SWAP
```

All'inizio troviamo _SWAP_, che crea un **alias** o **etichetta** per la macro, usato per richiamare il codice in seguito, e una sequenza di codice definita nel blocco da _MACRO_ a _ENDM_.

Durante l'assemblaggio del codice, l'assemblatore rimuove la macro e la inserisce nella tabella delle macro, sostituendo poi nelle **chiamate di macro** (dove troviamo _SWAP_) il codice memorizzato nella tabella. Questo processo di sostituzione del codice è chiamato **espansione di macro**. È importante non confondere una macro con una procedura, poiché la macro viene espansa durante l'assemblaggio, mentre la procedura viene chiamata durante l'esecuzione, rendendo quindi la macro il metodo più efficiente.

(Pagine riassunte: 2)
### 7.2.2 - Macro con parametri
Le macro descritte precedentemente si espandono in una sequenza di codice definita e perfettamente identica all'originale. Nel caso in cui volessimo rendere più dinamico l'utilizzo delle macro possiamo definire nella macro dei **parametri formali** che verranno sostituiti durante l'espansione dai **parametri attuali** forniti nella chiamata di macro, come nel seguente codice:

```
CHANGE      MACRO P1, P2
			MOV EAX, P1
			MOV EBX, P2
			MOV P2, EAX
			MOV P1, EBX
			ENDM
			
			CHANGE P, Q
			
			CHANGE R, S
```

(Pagine riassunte: 1)
### 7.2.3 - Caratteristiche avanzate
Le architetture degli assemblatori sono progettate con metodi avanzati per prevenire paradossi o errori che potrebbero portare il processore a malfunzionamenti o loop infiniti. Un esempio di queste tecniche è l'uso delle macro.

Consideriamo il seguente codice:

```assembly
M1  MACRO
	IF WORDSIZE GT 16
M2      MACRO
		...
		ENDM
	ELSE
M2	    MACRO
		...
		ENDM
	ENDIF
		ENDM
```

Come gestirà l'assemblatore le macro M2? In teoria, dovrebbe aggiungere due sequenze di codice diverse alla stessa etichetta, il che non è possibile. In questo caso, l'assemblatore genererà etichette diverse per ogni situazione ed espanderà solo la macro necessaria (per 16 bit o per 32 bit).

Inoltre, una macro può richiamare un'altra macro o anche sé stessa. Le macro ricorsive devono avere un parametro che cambia ad ogni chiamata e devono essere progettate per terminare dopo un numero finito di ricorsioni per evitare loop infiniti.

(Pagine riassunte: 0.75)
### 7.2.4 - Implementazione delle funzionalità macro negli assemblatori
Analizziamo in dettaglio il funzionamento delle macro in alcuni assemblatori.

L'assemblatore mantiene una tabella contenente i nomi delle macro e puntatori alle loro definizioni memorizzate. Alcuni assemblatori utilizzano una tabella separata per i nomi delle macro, mentre altri integrano questa tabella con quella delle istruzioni macchina e delle pseudoistruzioni.

Quando viene definita una macro, l'assemblatore aggiunge un elemento alla tabella che contiene il nome della macro, il numero di parametri formali e un puntatore a una seconda tabella. Questa seconda tabella contiene il corpo della macro, rappresentato come una stringa con istruzioni separate da ";" (punto e virgola).

Durante la prima fase dell'assemblaggio, l'assemblatore cerca gli opcode ed espande le macro. Quando incontra una macro, interrompe la lettura dell'input e legge il corpo della macro precedentemente memorizzato, sostituendo i parametri formali con quelli forniti. L'uso del simbolo "&" prima dei parametri formali aiuta l'assemblatore a riconoscerli facilmente.

(Pagine riassunte: 0.75)
## 7.3 - Processo di assemblaggio
### 7.3.1 - Assemblatori a due passate
Si potrebbe pensare che un programma in fase di assemblaggio traduca ogni istruzione direttamente in linguaggio macchina, ma questo non è sempre possibile a causa del **problema dei riferimenti avanti**, dove un simbolo viene utilizzato prima della sua definizione.

Un primo metodo per risolvere questo problema è l'uso di assemblatori a **due passate**, dove ogni passata rappresenta una lettura completa del codice sorgente. Nella prima passata, l'assemblatore raccoglie tutti i riferimenti delle etichette e le informazioni necessarie per la seconda passata, che compila effettivamente il codice istruzione per istruzione. Questo metodo è semplice e diretto.

Un secondo metodo esegue una prima passata convertendo il codice sorgente in una forma intermedia, memorizzata nella tabella della memoria. La seconda passata lavora solo su questa tabella, risparmiando tempo e riducendo l'uso delle operazioni I/O, specialmente se non è necessaria la generazione del listato.

(Pagine riassunte: 1)
### 7.3.2 - Prima passata
Nella prima passata, l'assemblatore ha il compito principale di costruire la **tabella dei simboli** dove un simbolo è un'etichetta o un valore assegnato tramite una pseudoistruzione.

Per tenere traccia della posizione dell'istruzione, l'assemblatore utilizza una variabile chiamata **ILC** (Instruction Location Counter). Nella maggior parte degli assemblatori, la prima passata utilizza tre tabelle interne: una per i simboli, una per le pseudoistruzioni e una per i codici operativi.

I simboli vengono definiti nella tabella quando c'è una definizione esplicita, come con _EQU_, o quando sono usati come etichette. A ciascun simbolo viene associato il valore numerico dell'ILC e altre informazioni opzionali.

La tabella dei codici operativi include per ogni riga un opcode con i dettagli, come gli operandi, il codice esadecimale dell'istruzione, la lunghezza dell'istruzione e soprattutto la _classe di istruzione_, un valore numerico associato a ogni combinazione di operando e operandi nell'istruzione.

Alcuni assemblatori supportano le **istruzioni pseudoimmediate**, che permettono l'uso dell'indirizzamento immediato anche se non implementato dal linguaggio di destinazione.

Le costanti per le quali l'assemblatore riserva automaticamente la memoria sono chiamate **letterali**, migliorando la leggibilità e l'interpretazione del codice. Nella prima passata, i letterali vengono letti e inseriti in una tabella specifica, che successivamente viene riordinata e ripulita dai duplicati.

(Pagine riassunte: 4)
### 7.3.3 - Seconda passata
Nella seconda passata, l'assemblatore compie operazioni simili alla prima; ogni linea viene codificata una alla volta senza ulteriori elaborazioni, utilizzando le informazioni già presenti nelle tabelle create.

La generazione del codice viene eseguita da funzioni specifiche che gestiscono i vari _schemi di istruzione_ e producono il codice binario, scritto su un file in grandi porzioni per ridurre il traffico di dati verso il disco.

Infine, il codice sorgente può essere stampato insieme al codice oggetto o inserito in un file di _buffer_ per la stampa successiva. Questo processo presuppone che il codice sia privo di errori, un'abilità in cui i programmatori eccellono.

(Pagine riassunte: 1.5)
### 7.3.4 - Tabella dei simboli
Ora analizziamo i metodi per strutturare le tabelle dei simboli, che generalmente rappresentano una **memoria associativa** in cui ogni simbolo è associato a un valore.

Il metodo più semplice è lento, poiché richiede la lettura di metà della tabella in media per trovare un elemento. Un metodo più efficiente è l'**algoritmo di ricerca dicotomica**: si confronta l'elemento cercato con quello al centro della tabella. Se l'elemento cercato è alfabeticamente successivo, si cerca nella seconda metà della tabella, altrimenti nella prima. Questo algoritmo si applica ricorsivamente fino a trovare l'elemento, impiegando un tempo di $\log_{2}{n}$.

Un altro metodo efficace è la **codifica hash** o **hashing**, utilizzata nei dizionari con liste di trabocco. Una funzione hash mappa i simboli nell'intervallo di interi da 0 a k−1 (dove k è la lunghezza della tabella). Ogni elemento, chiamato _bucket_, punta a una lista concatenata che contiene i riferimenti al simbolo e al valore. Il metodo di mapping è casuale.

(Pagine riassunte: 2)
## 7.4 - Collegamento e caricamento
Abbiamo studiato come l'assemblatore crea programmi oggetto (o procedure) uno alla volta. Ma come vengono gestiti i collegamenti tra queste procedure?

Diversi strumenti collegano i **moduli oggetto**, tra cui il **linker**, il **linking loader** e il **linkage editor**. Il compito del linker è creare il programma eseguibile binario finale e completo.

Perché dividere questo compito? Se l'assemblatore trasformasse direttamente il codice in linguaggio macchina, ogni modifica richiederebbe la ricompilazione completa di ogni modulo. La divisione in moduli consente di ricompilare solo quelli modificati e di collegarli successivamente.

(Pagine riassunte: 1)
### 7.4.1 - Compiti dei linker


(Pagine riassunte: 3)
### 7.4.2 - Struttura di un modulo oggetto
### 7.4.3 - Rilocazione a tempo del biding e dinamica
### 7.4.4 - Collegamento dinamico