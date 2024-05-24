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
### 7.2.3 - Caratteristiche avanzate
### 7.2.4 - Implementazione delle funzionalità macro negli assemblatori
## 7.3 - Processo di assemblaggio
### 7.3.1 - Assemblatori a due passate
### 7.3.2 - Prima passata
### 7.3.3 - Seconda passata
### 7.3.4 - Tabella dei simboli
## 7.4 - Collegamento e caricamento
### 7.4.1 - Compiti dei linker
### 7.4.2 - Struttura di un modulo oggetto
### 7.4.3 - Rilocazione a tempo del biding e dinamica
### 7.4.4 - Collegamento dinamico

(Pagine riassunte: 29)