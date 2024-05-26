Questo capitolo descrive il livello di architettura dell'insieme d'istruzioni (ISA), posizionato tra la microarchitettura e il sistema operativo. L'ISA è fondamentale per i progettisti di sistemi perché costituisce l'interfaccia tra software e hardware.

I progettisti traducono i linguaggi di alto livello nell'ISA e costruiscono l'hardware per eseguirlo. Quando si sviluppa una nuova macchina, è cruciale mantenere la compatibilità con i modelli precedenti, sia per il sistema operativo che per le applicazioni. Questo garantisce che i vecchi programmi funzionino sui nuovi processori, preservando l'investimento degli utenti nel loro software.

Gli ISA devono essere efficienti per essere economicamente vantaggiosi. Un buon ISA richiede meno risorse hardware e supporta una compilazione del codice efficace, rendendo più semplice per i compilatori generare codice ottimizzato. In sintesi, l'ISA deve soddisfare le esigenze sia dei progettisti hardware che software.

(pagine riassunte: 3)
## 5.1 - Panoramica del livello ISA
Per iniziare lo studio del livello ISA, chiediamoci cos'è. Sebbene sembri una domanda semplice, essa presenta diverse complicazioni. Esamineremo alcune questioni controverse e poi analizzeremo modelli di memoria, registri e istruzioni.
### 5.1.1 - Proprietà del livello ISA
Il livello ISA può essere definito come la rappresentazione della macchina per i programmatori, emersa dall'output dei compilatori. Include informazioni sulla memoria, registri, tipi di dati e istruzioni disponibili. In alcune architetture, è formalmente specificato da documenti di definizione, come nel caso di ARM, per garantire l'interoperabilità tra diverse implementazioni hardware. Questi documenti non dettagliano la microarchitettura ma stabiliscono il comportamento delle istruzioni.

I documenti di definizione includono sezioni normative e informative, delineando requisiti e raccomandazioni. Ad esempio, il documento di definizione per ARM v7 assicura che tutti i chip ARM eseguano lo stesso codice. Tali documenti possono essere estesi, come nel caso del Core i7 di Intel, che conta 4161 pagine.

Un'altra caratteristica chiave del livello ISA è la presenza di più modalità di esecuzione, come la **modalità kernel** per il sistema operativo e la **modalità utente** per le applicazioni, con restrizioni sull'uso di alcune istruzioni sensibili.

(pagine riassunte: 1.5)
### 5.1.2 - Modelli della memoria
I computer dividono la memoria in celle consecutive, comunemente di 8 bit, chiamate byte o **ottetti**. I byte sono spesso raggruppati in parole di 4 o 8 byte, con istruzioni specifiche per manipolare intere parole. L'allineamento dei dati è importante per l'efficienza della memoria, come nel caso del Core i7 che richiede accessi allineati a 64 bit.

La capacità di leggere parole da indirizzi arbitrari richiede funzionalità logiche aggiuntive nel chip, rendendolo più grande e costoso. Molti processori hanno uno spazio lineare degli indirizzi, ma alcune macchine separano gli spazi degli indirizzi per istruzioni e dati, offrendo vantaggi come la prevenzione di sovrascritture accidentali del programma e la resistenza agli attacchi malware.

La semantica della memoria è importante, ad esempio, ci si aspetta che un'istruzione LOAD restituisca il valore memorizzato da un'istruzione STORE nello stesso indirizzo. I progettisti possono scegliere tra approcci che vanno dalla serializzazione di tutte le richieste d'accesso alla memoria, con prestazioni ridotte ma semantica più semplice, all'assenza di garanzie, dove il programma deve usare istruzioni SYNC per forzare un ordine sulla memoria.

Modelli di memoria intermedi sono anche possibili, dove l'hardware blocca automaticamente alcuni accessi alla memoria ma non altri. Nonostante le complicazioni, questa tendenza è diffusa a causa delle implementazioni sottostanti come il riordinamento delle microistruzioni, le pipeline profonde e i livelli di cache multipli.

(pagine riassunte: 2)
### 5.1.3 - Registri
I computer dispongono di registri visibili a livello ISA, utilizzati per il controllo dell'esecuzione del programma e per contenere risultati temporanei. Questi registri possono essere specializzati, come il program counter e il puntatore allo stack, o d'uso generale, destinati a variabili locali e risultati parziali del calcolo. Le macchine RISC tendono ad avere almeno 32 registri d'uso generale, spesso simmetrici e intercambiabili.

I registri del livello ISA sono implementati a livello microarchitetturale e sono sempre visibili a entrambi i livelli. Esistono anche registri specializzati visibili solo in modalità kernel, utilizzati per il controllo di cache, memoria e dispositivi di I/O, e non accessibili ai compilatori o agli utenti.

Il **registro di flag**, o PSW (Program Status Word), contiene tutti i possibili bit di condizione, come N (risultato negativo), Z (risultato zero), V (overflow), C (carry), A (carry oltre il terzo bit) e P (parità nulla). Questi bit sono importanti per le istruzioni di confronto e salto condizionato. Il PSW può anche includere informazioni sulla modalità di macchina, priorità della CPU e stato degli interrupt, con alcuni campi leggibili in modalità utente e altri scrivibili solo in modalità kernel.

(pagine riassunte: 1.5)
### 5.1.4 - Istruzioni
La caratteristica principale del livello ISA è l'insieme di istruzioni macchina che definisce ciò che la macchina può fare. Questo comprende sempre istruzioni come STORE e LOAD per il trasferimento di dati tra registri e memoria, nonché MOVE per la copia di dati tra registri. Aringhiera sempre istruzioni aritmetiche, booleane e di confronto dei dati con salto condizionato. Abbiamo già visto alcune istruzioni ISA comuni e ne vedremo molte altre in questo capitolo.
### 5.1.5 - Panoramica del livello ISA del Core i7
Il Core i7, frutto dell'evoluzione di molte generazioni di processori Intel, ha un ISA che mantiene il completo supporto per programmi scritti per l'8086 e l'8088, con reminiscenze dell'8080. Dal punto di vista del software, sia l'8086 che l'8088 erano macchine a 16 bit effettivi. L'80386 fu la prima macchina a 32 bit della famiglia Intel, e tutti i processori successivi mantengono l'architettura IA-32, mentre la x86-64 estende la dimensione dei calcoli e degli indirizzi virtuali a 64 bit.

Il Core i7 opera in tre modalità: la **modalità reale**, che lo fa funzionare come un 8088; la **modalità virtuale 8086**, che consente l'esecuzione protetta di vecchi programmi 8088; e la **modalità protetta**, in cui il Core i7 funziona come un Pentium 4. Il Core i7 dispone di un enorme spazio degli indirizzi, diviso in segmenti, sebbene la maggior parte dei sistemi operativi supporti un solo segmento, offrendo uno spazio degli indirizzi lineare di $2^{32}$ byte.

I registri del Core i7 includono EAX, EBX, ECX ed EDX, utilizzati per operazioni aritmetiche, puntatori, cicli e moltiplicazioni/divisioni. ESI, EDI ed EBP sono utilizzati per puntatori alla memoria e per il registro dello stack. Il gruppo successivo di registri, da CS a GS, comprende i registri di segmento.

(pagine riassunte: 2)
### 5.1.6 - Panoramica del livello ISA dell'OMAP4430 ARM
L'architettura ARM è stata introdotta per la prima volta nel 1985 da Acorn Computer, ispirata dalle ricerche svolte a Berkeley negli anni '80. La versione originale, ARM2, era a 32 bit e supportava uno spazio degli indirizzi a 26 bit. L'OMAP4430 utilizza la microarchitettura ARM Cortex A9, che implementa la versione 7 dell'architettura ARM.

La struttura della memoria dell'OMAP4430 è un vettore di 23 byte. I processori ARM sono bi-endian, consentendo l'accesso alla memoria nei due ordini big-endian e little-endian. È importante che l'ISA preveda uno spazio degli indirizzi più grande delle necessità implementative per consentire l'espansione futura della memoria.

L'ISA ARM versione 8 è stata recentemente pubblicata per supportare uno spazio di indirizzamento a 64 bit, affrontando le preoccupazioni riguardanti lo spazio degli indirizzi limitato a 32 bit delle versioni precedenti.

L'ISA ARM presenta due gruppi principali di registri: 16 registri d'uso generale da 32 bit e, se supportato, 32 registri in virgola mobile da 32 bit. I registri d'uso generale vanno da R0 a R15 e sono utilizzati per operazioni aritmetiche e di memoria. I registri in virgola mobile possono essere trattati come valori in virgola mobile a precisione singola o doppia, a seconda dell'istruzione utilizzata.

L'architettura ARM è load/store, il che significa che le uniche operazioni che accedono direttamente alla memoria sono load e store, mentre le operazioni logiche e aritmetiche operano solo su registri o operandi all'interno dell'istruzione stessa.

I registri speciali includono il registro IP utilizzato per chiamate di funzione, il registro SP che indica la posizione dello stack, il registro LP utilizzato per mantenere l'indirizzo di ritorno e il registro **PSR** che mantiene lo stato delle precedenti operazioni dell'ALU.

In generale, l'ISA ARM è progettata per offrire un'architettura efficiente e flessibile, consentendo l'accesso rapido alla memoria e operazioni aritmetiche e logiche su registri dedicati.

(pagine riassunte: 3)
### 5.1.7 - Panoramica del livello ISA dell'ATmega168 AVR
L'ATmega168 è un microcontrollore utilizzato in sistemi integrati come semafori e radiosveglie, gestendo varie funzioni come il controllo dei pulsanti, delle luci e altre parti dell'interfaccia utente. Dal punto di vista dell'ISA, l'ATmega168 ha una sola modalità operativa e nessuna protezione hardware, poiché non esegue programmi di utenti potenzialmente ostili.

La sua struttura di memoria è semplice: 16 KB per i programmi e 1 KB per i dati, entrambi separati. Questa divisione consente di implementare i programmi in memoria flash e i dati in SRAM.

L'ATmega168 utilizza un'organizzazione di memoria a due livelli per offrire maggiore sicurezza. La memoria flash del programma è divisa in sezione di bootloader e sezione di applicazioni, con dimensioni determinate da bit programmabili al primo avvio. Solo il codice del bootloader può aggiornare la memoria flash per motivi di sicurezza. Questo sistema consente di eseguire solo il codice approvato e firmato digitalmente da un distributore fidato.

Il microcontrollore ha 32 registri a uso generale da 8 bit (R0 - R31), che sono anche presenti nello spazio di memoria. Ad esempio, il byte 0 dello spazio dati corrisponde a R0 e così via. Questa organizzazione facilita l'accesso ai registri tramite l'indirizzamento di memoria.

Altri registri specializzati includono il registro di stato, che contiene bit di abilitazione degli interrupt, bit ausiliario di riporto, bit di segno, bit di overflow e altri, e il registro del puntatore dello stack (SP), che mantiene l'indirizzo corrente dello spazio dati per le istruzioni di PUSH e POP.

Inoltre, ci sono 64 byte di registri dedicati ai dispositivi di I/O, e il registro di stato gestisce anche l'attivazione e la disattivazione degli interrupt globali tramite il bit I. Il puntatore dello stack (SP) è composto da due locazioni di memoria consecutive per indirizzare correttamente la memoria dati.

(pagine riassunte: 2)
## 5.2 - Tipi di dati
La rappresentazione dei dati all'interno di un computer è fondamentale per il corretto funzionamento dei sistemi di calcolo. A livello ISA, sono disponibili diversi tipi di dati che possono essere manipolati dalle istruzioni del processore. Tuttavia, una delle questioni fondamentali riguarda il supporto hardware per un particolare tipo di dati.

Il supporto hardware implica che una o più istruzioni si aspettano che i dati siano rappresentati in un formato specifico e l'utente non è libero di scegliere un formato diverso. Ad esempio, nel caso degli interi, l'hardware potrebbe aspettarsi che il bit più significativo rappresenti il segno del numero, e se questo formato non viene rispettato, il funzionamento del sistema potrebbe essere compromesso.

Immaginate, ad esempio, se un responsabile del centro di calcolo di uno studio di contabilità decidesse di invertire il modo in cui i computer rappresentano i numeri negativi. Questo potrebbe causare errori nei calcoli, poiché il software è stato progettato per gestire i numeri in un formato specifico.

In un contesto diverso, ad esempio per la valutazione del debito pubblico, potrebbero essere necessari numeri molto più grandi di quelli supportati nativamente dall'hardware. In questi casi, potrebbe essere necessario implementare una gestione software per la rappresentazione e l'aritmetica di numeri di dimensioni maggiori, ad esempio utilizzando due interi di 32 bit per rappresentare un singolo numero (64 bit in totale), noto come **precisione doppia**.

Il concetto di "precisione doppia" si riferisce alla capacità di rappresentare e manipolare numeri con una maggiore precisione rispetto ai numeri interi a 32 bit standard. Questo è particolarmente utile in applicazioni che richiedono una maggiore precisione numerica, come nel caso di calcoli scientifici o finanziari complessi.

Nei prossimi paragrafi, esamineremo i tipi di dati supportati dall'hardware, inclusa la precisione doppia, per i quali sono richiesti formati specifici di rappresentazione per garantire il corretto funzionamento delle istruzioni di elaborazione.

(pagine riassunte: 1)
### 5.2.1 - Tipi di dati numerici
I tipi di dati possono essere suddivisi in due categorie principali: numerici e non numerici. Iniziamo con i dati numerici, che comprendono gli interi e i numeri in virgola mobile.

Gli interi sono utilizzati per contare oggetti, identificare elementi, e per una varietà di altri scopi. Possono essere di diverse lunghezze, tipicamente 8, 16, 32 e 64 bit. La rappresentazione più comune degli interi avviene in notazione binaria in complemento a due, che permette di rappresentare sia numeri positivi che negativi. Ad esempio, un intero senza segno di 32 bit può rappresentare valori compresi tra 0 e $2^{32}-1$, mentre un intero con segno di 32 bit può gestire numeri compresi tra -$2^{31}$ e $2^{31}-1$.

Per rappresentare numeri che non possono essere espressi come interi, come ad esempio 3,5, si utilizzano i numeri in virgola mobile. Questi numeri sono solitamente di lunghezza 32, 64 o 128 bit e consentono la rappresentazione di valori con parte intera e parte frazionaria. La maggior parte dei computer moderni dispone di istruzioni dedicate per l'aritmetica in virgola mobile e spesso hanno registri separati per operandi interi e in virgola mobile.

Alcuni linguaggi di programmazione, come il COBOL, supportano anche un tipo di dati per i numeri decimali. Questi numeri vengono spesso rappresentati nell'hardware utilizzando la codifica binaria dei decimali (BCD), dove ogni cifra decimale viene codificata con 4 bit. Tuttavia, l'aritmetica dei numeri decimali impacchettati può comportare delle complicazioni, quindi possono essere necessarie istruzioni aggiuntive per la correzione dell'aritmetica decimale. Ad esempio, il problema del "millennium bug" o Y2K è stato causato in parte dalla rappresentazione a due cifre degli anni nei sistemi COBOL, che utilizzavano solo 8 bit per rappresentare l'anno, causando problemi al passaggio al nuovo millennio.

(pagine riassunte: 1)
### 5.2.2 - Tipi di dati non numerici
Sebbene i primi computer abbiano fatto fortuna elaborando principalmente numeri, i moderni sistemi informatici sono spesso utilizzati per una vasta gamma di applicazioni non numeriche, come l'invio di email, la navigazione su Internet, la fotografia digitale, la creazione e la riproduzione di contenuti multimediali. Queste applicazioni richiedono tipi di dati diversi, che possono essere supportati dalle istruzioni del livello ISA.

Tra questi, i caratteri giocano un ruolo centrale. I computer utilizzano comunemente codici carattere come ASCII e UNICODE, che definiscono rispettivamente caratteri di 7 e 16 bit. Le stringhe di caratteri, ovvero sequenze di caratteri, sono spesso gestite tramite istruzioni speciali nel livello ISA. Le stringhe possono essere delimitate da un carattere speciale di fine stringa o possono essere dotate di un campo lunghezza per indicare la loro estensione.

I valori booleani, che possono essere solo vero o falso, sono altrettanto importanti. Sebbene teoricamente un solo bit sarebbe sufficiente per rappresentare un dato booleano, in pratica spesso si utilizzano interi byte per consentire un accesso più semplice. Comunemente, si associa il valore 0 al falso e tutti gli altri valori al vero. Tuttavia, quando si tratta di memorizzare array di booleani, spesso si adotta un approccio a "bit map", in cui una parola di 32 bit può contenere 32 valori binari.

Infine, i puntatori rappresentano un altro tipo di dato importante, essenzialmente un indirizzo di memoria. Sono comunemente usati per accedere a variabili o dati memorizzati in una certa posizione di memoria. Tuttavia, l'uso dei puntatori richiede estrema cura, poiché errori nella loro gestione possono causare gravi problemi nel programma.

(pagine riassunte: 1)
### 5.2.3 - Tipi di dati del Core i7
Il Core i7 supporta una varietà di tipi di dati, inclusi gli interi con segno in complemento a due, gli interi senza segno, i numeri decimali in codifica binaria e i numeri in virgola mobile nel formato IEEE 754. A causa delle sue origini come macchina a 8/16 bit, il Core i7 gestisce, oltre agli interi a 32 bit, anche interi di 8 e 16 bit, offrendo numerose istruzioni per la loro aritmetica, operazioni booleane e confronti. Il processore può anche essere utilizzato in modalità a 64 bit, supportando registri e operazioni a 64 bit. Sebbene gli operandi non debbano necessariamente essere allineati in memoria, l'allineamento degli indirizzi delle parole su multipli di 4 byte può migliorare le prestazioni.

Il Core i7 è ben equipaggiato per la manipolazione dei caratteri ASCII a 8 bit, disponendo di istruzioni speciali per la copia e la ricerca di stringhe di caratteri. Queste istruzioni sono applicabili sia alle stringhe di lunghezza nota che a quelle terminate da un carattere di fine stringa e sono frequentemente utilizzate nelle librerie che manipolano le stringhe.

(pagine riassunte: 0.5)
### 5.2.4 - Tipi di dati dell'OMAP4430 ARM
La CPU OMAP4430 supporta un ampio spettro di formati di dati. Per quanto riguarda i soli interi, può gestire operandi da 8, 16 e 32 bit, con o senza segno. La gestione dei tipi di dato piccoli nell’OMAP4430 è più intelligente rispetto a quella del Core i7. Internamente, l’OMAP4430 è una macchina a 32 bit con un percorso dati e istruzioni da 32 bit. Un programma può specificare la dimensione e il segno di un valore da caricare; ad esempio, per caricare un byte con segno si usa l'istruzione LDRSB, che converte il valore caricato nel corrispondente valore a 32 bit. Analogamente, anche le istruzioni di memorizzazione specificano la dimensione e il segno del valore da scrivere in memoria e accedono solamente alla porzione specificata del registro di input.

Gli interi con segno utilizzano il formato in complemento a due. Sono disponibili operandi in virgola mobile a 32 e 64 bit che rispettano lo standard IEEE 754. Tutti gli operandi devono essere allineati in memoria per garantire il corretto funzionamento delle operazioni.

A differenza del Core i7, l'OMAP4430 non dispone di istruzioni hardware speciali per il supporto di tipi di dati carattere e stringa; la loro manipolazione è gestita completamente via software.

(pagine riassunte: 0.5)
### 5.2.5 - Tipi di dati dell'ATmega168
L'ATmega168 dispone di una varietà di tipi di dati molto limitata. Tutti i registri sono lunghi 8 bit, con una sola eccezione, e così anche gli interi sono di 8 bit, così come i caratteri. In pratica, il solo tipo di dati le cui operazioni aritmetiche sono realmente supportate dall'hardware è il byte di 8 bit, come si evince dalla Figura 5.8.

Per facilitare l'accesso alla memoria, l'ATmega168 include anche un supporto limitato a puntatori senza segno di 16 bit. I puntatori da 16 bit X, Y e Z sono formati dalla concatenazione delle coppie di registri di 8 bit R26/R27, R28/R29 e R30/R31 rispettivamente. Quando un'istruzione di caricamento utilizza X, Y o Z come operando per l'indirizzo, il processore può incrementare o decrementare il valore a seconda della necessità.

(pagine riassunte: 0.5)
## 5.3 - Formati d'istruzione
Un’istruzione consiste in un opcode (codice operativo), di solito corredato da altre informazioni quali la provenienza degli operandi e la destinazione dei risultati. L’argomento generale che tratta della provenienza degli operandi (cioè il loro indirizzo) è detto indirizzamento e verrà illustrato in dettaglio nel prosieguo di questo paragrafo. Un’istruzione è dotata di un opcode che ne specifica il comportamento, e può contenere nessuno, uno, due o tre indirizzi.

Alcune macchine hanno tutte le istruzioni della stessa lunghezza, altre dispongono d’istruzioni di lunghezza diversa. Le istruzioni possono essere più corte, altrettanto lunghe o più lunghe della dimensione di parola. La scelta di avere tutte le istruzioni della stessa lunghezza semplifica la loro decodifica, ma spesso implica uno spreco di spazio, visto che tutte le istruzioni devono essere lunghe quanto la più lunga. Sono anche possibili altri compromessi.

(pagine riassunte: 0.5)
### 5.3.1 - Criteri progettuali per i formati d'istruzoni

### 5.3.2 - Codice operativo espandibile

### 5.3.3 - Formati delle istruzioni del Core i7

### 5.3.4 - Formati delle istruzioni dell'OMAP4430 ARM

### 5.3.5 - Formati delle istruzioni dell'ATmega168

## 5.4 - Indirizzamento 
### 5.4.1 - Modalità d'indirizzamento

### 5.4.2 - Indirizzamento immediato

### 5.4.3 - Indirizzamento diretto

### 5.4.4 - Indirizzamento a registro

### 5.4.5 - Indirizzamento a registro indiretto

### 5.4.6 - Indirizzamento indicizzato

### 5.4.7 - Indirizzamento indicizzato esteso

### 5.4.8 - Indirizzamento a stack

### 5.4.9 - Modalità d'indirizzamento per istruzioni di salto

### 5.4.10 - Modalità d'indirizzamento dei codici operativi e delle modalità d'indirizzamento

### 5.4.11 - Modalità d'indirizzamento del Core i7

### 5.4.12 - Modalità d'indirizzamento dell'OMAP4430

### 5.4.13 - Modalità d'indirizzamento dell'ATmega168 AVR

### 5.4.14 - Analisi delle modalità d'indirizzamento

## 5.5 - Tipi d'istruzioni
### 5.5.1 - Istruzioni di trasferimento dati

### 5.5.2 - Operazioni binarie

### 5.5.3 - Operazioni unarie

### 5.5.4 - Confronti e salti condizionati

### 5.5.5 - Invocazione di procedura

### 5.5.6 - Istruzioni di ciclo

### 5.5.7 - Input/Output

### 5.5.8 - Istruzioni del Core i7

### 5.5.9 - Istruzioni della CPU ARM OMAP4430

### 5.5.10 - Istruzioni dell'ATmega168 AVR

### 5.5.11 - Insieme d'istruzioni a confronto

## 5.6 - Controllo del flusso
### 5.6.1 - Flusso sequenziale e diramazioni

### 5.6.2 - Procedure

### 5.6.3 - Coroutine

### 5.6.4 - Trap

### 5.6.5 - Interrupt

## 5.8 - Architettura IA-64 e Itanium 2
### 5.8.1 - Il problema dell'ISA IA-32

### 5.8.2 - Modello IA-64 e calcolo che utilizza il parallelismo esplicito

### 5.8.3 - Riduzione degli accessi in memoria

### 5.8.4 - Scheduling delle istruzioni

### 5.8.5 - Riduzione dei salti condizionati: attribuzione di predicati

### 5.8.6 - Caricamenti speculativi

