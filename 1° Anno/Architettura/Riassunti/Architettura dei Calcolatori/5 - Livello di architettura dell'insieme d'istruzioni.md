Questo capitolo descrive il livello di architettura dell'insieme d'istruzioni (ISA), posizionato tra la microarchitettura e il sistema operativo. L'ISA è fondamentale per i progettisti di sistemi perché costituisce l'interfaccia tra software e hardware.

Quando si sviluppa una nuova macchina, è cruciale mantenere la **retrocompatibilità** con i modelli precedenti, sia per il sistema operativo che per le applicazioni. Questo garantisce che i vecchi programmi funzionino sui nuovi processori, preservando l'investimento degli utenti nel loro software.

Gli ISA devono essere efficienti per essere economicamente vantaggiosi. Un buon ISA richiede meno risorse hardware e supporta una compilazione del codice efficace, rendendo più semplice per i compilatori generare codice ottimizzato. In sintesi, l'ISA deve soddisfare le esigenze sia dei progettisti hardware che software.

(pagine riassunte: 3)
## 5.1 - Panoramica del livello ISA
Sembra banale, ma... cos'è un ISA? Di seguito esamineremo alcune questioni controverse e poi analizzeremo modelli di memoria, registri e istruzioni.
### 5.1.1 - Proprietà del livello ISA
Il codice di livello ISA è l'output di un compilatore. Per produrre questo codice, il proggettista del compilatore deve conoscere il modello di memoria, registri, tipi di dati e istruzioni disponibili. 
Per alcune architetture il livello ISA è specificato attraverso un documento formale di definizione: per esempio ARM v7 ha una definizione ufficiale pubblicata da ARM Ltd. 
Questi documenti non dettagliano la microarchitettura ma stabiliscono il comportamento delle istruzioni.

I documenti di definizione includono **sezioni normative** e **informative**, delineando requisiti e raccomandazioni. Ad esempio, il documento di definizione per ARM v7 assicura che tutti i chip ARM eseguano lo stesso codice. Tali documenti possono essere estesi, come nel caso del Core i7 di Intel, che conta 4161 pagine.

Un'altra caratteristica chiave del livello ISA è la presenza di più modalità di esecuzione, come la **modalità kernel** per il sistema operativo e la **modalità utente** per le applicazioni, con restrizioni sull'uso di alcune istruzioni sensibili.

(pagine riassunte: 1.5)
### 5.1.2 - Modelli della memoria
I computer dividono la memoria in celle consecutive, comunemente di 8 bit, chiamate byte o **ottetti**. I byte sono spesso raggruppati in parole di 4 o 8 byte, con istruzioni specifiche per manipolare intere parole. L'allineamento dei dati è importante per l'efficienza della memoria, come nel caso del Core i7 che richiede accessi allineati a 64 bit.

La capacità di leggere parole da indirizzi arbitrari richiede funzionalità logiche aggiuntive nel chip, rendendolo più grande e costoso. Molti processori hanno uno spazio lineare degli indirizzi, ma alcune macchine separano gli spazi degli indirizzi per istruzioni e dati, offrendo vantaggi come la prevenzione di sovrascritture accidentali del programma e la resistenza agli attacchi malware.

La semantica della memoria è estremamente importante: ci si aspetta che un'istruzione LOAD restituisca il valore memorizzato da un'istruzione STORE nello stesso indirizzo. Ma sappiamo (dal capitolo 4) che le istruzioni possono non essere eseguite in ordine, il che genera il pericolo concreto che la memoria esibisca comportamenti inattesi. Quindi, i progettisti possono scegliere tra approcci che vanno dalla serializzazione di tutte le richieste d'accesso alla memoria, con prestazioni ridotte ma semantica più semplice, all'assenza di garanzie, dove il programma deve usare istruzioni SYNC per forzare un ordine sulla memoria.

Esistono anche modelli di memoria intermedi, dove l'hardware blocca automaticamente alcuni accessi alla memoria ma non altri. Nonostante le complicazioni, questa tendenza è diffusa a causa delle implementazioni sottostanti come il riordinamento delle microistruzioni, le pipeline profonde e i livelli di cache multipli.

(pagine riassunte: 2)
### 5.1.3 - Registri
I computer dispongono di registri visibili a livello ISA, utilizzati per il controllo dell'esecuzione del programma e per contenere risultati temporanei. Questi registri possono essere specializzati, come il program counter e il puntatore allo stack, o d'uso generale, destinati a variabili locali e risultati parziali del calcolo. Le macchine RISC tendono ad avere almeno 32 registri d'uso generale, spesso simmetrici e intercambiabili.

I registri del livello ISA sono implementati a livello microarchitetturale e sono sempre visibili a entrambi i livelli. Esistono anche registri specializzati visibili solo in modalità kernel, utilizzati per il controllo di cache, memoria e dispositivi di I/O, e non accessibili ai compilatori o agli utenti.

Il **registro di flag**, o PSW (Program Status Word), contiene tutti i possibili bit di condizione:
1) N: vale 1 dopo un risultato negativo.
2) Z: vale 1 dopo un risultato uguale a zero.
3) V: vale 1 se il risultato causa overflow. 
4) C: vale 1 se il risultato ha causato un riporto oltre l'ultimo bit più significativo. 
5) A: vale 1 se si è verificato un riporto oltre il terzo bit.
6) P: vale 1 se il risultato è pari (parità nulla). 
Questi bit sono importanti per le istruzioni di confronto e salto condizionato. Il PSW può anche includere informazioni sulla modalità di macchina, priorità della CPU e stato degli interrupt, con alcuni campi leggibili in modalità utente e altri scrivibili solo in modalità kernel.

(pagine riassunte: 1.5)
### 5.1.4 - Istruzioni
La caratteristica principale del livello ISA è l'insieme di istruzioni macchina che definisce ciò che la macchina può fare. Questo comprende sempre istruzioni come STORE e LOAD per il trasferimento di dati tra registri e memoria, nonché MOVE per la copia di dati tra registri. Sono sempre presenti istruzioni aritmetiche, booleane e di confronto dei dati con salto condizionato.
### 5.1.5 - Panoramica del livello ISA del Core i7
Il Core i7 ha un ISA che mantiene il completo supporto per programmi scritti per l'8086, l'8088,  fino al'8080. Dal punto di vista del software, sia l'8086 che l'8088 erano macchine a 16 bit effettivi. L'80386 fu la prima macchina a 32 bit della famiglia Intel, e tutti i processori successivi mantengono l'architettura IA-32, mentre la x86-64 estende la dimensione dei calcoli e degli indirizzi virtuali a 64 bit. Stiamo parlando di questo perché, visto che il Core i7 supporta programmi scritti per processori più vecchi, ha un'architettura **estremamente simile**.

Il Core i7 opera in tre modalità: la **modalità reale**, che lo fa funzionare come un 8088; la **modalità virtuale 8086**, che consente l'esecuzione protetta di vecchi programmi 8088; e la **modalità protetta**, in cui il Core i7 funziona come un Pentium 4. Il Core i7 dispone di un enorme spazio degli indirizzi, diviso in segmenti (ben 16'384), sebbene la maggior parte dei sistemi operativi supporti un solo segmento, offrendo uno spazio degli indirizzi lineare di $2^{32}$ byte, anche se molto spesso parte di questo spazio è occupato dal sistema operativo.

I Core i7 ha molteplici registri, tra cui EAX, EBX, ECX ed EDX (registri a 32 bit), utilizzati per operazioni aritmetiche, puntatori, cicli e moltiplicazioni/divisioni. ESI, EDI ed EBP sono utilizzati per puntatori alla memoria e per il registro dello stack. Il gruppo successivo di registri, da CS a GS, comprende i registri di segmento. Poi abbiamo l'EIP (extended instruction pointer), ovvero il program counter. Infine troviamo EFLAGS, un registro analogo a PSW.

(pagine riassunte: 2)
### 5.1.6 - Panoramica del livello ISA dell'OMAP4430 ARM
L'architettura ARM è stata introdotta per la prima volta nel 1985 da Acorn Computer, ispirata dalle ricerche svolte a Berkeley negli anni '80. La versione originale, ARM2, era a 32 bit e supportava uno spazio degli indirizzi a 26 bit. L'OMAP4430 utilizza la microarchitettura ARM Cortex A9, che implementa la versione 7 dell'architettura ARM.

La struttura della memoria dell'OMAP4430 è chiara e semplice: la memoria indirizzabile è un vettore di 23 byte. I processori ARM sono bi-endian, consentendo l'accesso alla memoria nei due ordini big-endian e little-endian. È importante che l'ISA preveda uno spazio degli indirizzi più grande delle necessità implementative per consentire l'espansione futura della memoria.

L'architettura mappa il program counter nel banco dei registri come R15, per permettere la creazione di salti con operazioni dell'ALU aventi R15 come registro di destinazione.

L'ISA ARM ha **due gruppi principali di registri**: 16 registri d'uso generale da 32 bit e, se supportato, 32 registri in virgola mobile da 32 bit. I registri d'uso generale vanno da R0 a R15 e sono utilizzati per operazioni aritmetiche e di memoria. I registri in virgola mobile possono essere trattati come valori in virgola mobile a precisione singola o doppia, a seconda dell'istruzione utilizzata.

Lista dei registri:


| Registri | Nomi alternativi | Funzione                                                    |
| -------- | ---------------- | ----------------------------------------------------------- |
| R0 - R3  | A1 - A4          | Contengono i parametri della procedura che viene invocata.  |
| R4 - R11 | V1 - V8          | Contengono le variabili locali della procedura corrente.    |
| R12      | IP               | Registro chiamata intraprocedurale (per chiamate a 32 bit). |
| R13      | SP               | Puntatore allo stack.                                       |
| R14      | LR               | Contiene l'indirizzo di ritorno della funzione corrente.    |
| R15      | PC               | Program counter.                                            |


L'architettura ARM è load/store, il che significa che le uniche operazioni che accedono direttamente alla memoria sono load e store, mentre le operazioni logiche e aritmetiche operano solo su registri o operandi all'interno dell'istruzione stessa.

I registri speciali includono il registro IP utilizzato per chiamate di funzione, il registro SP che indica la posizione dello stack, il registro LP utilizzato per mantenere l'indirizzo di ritorno e il registro **PSR** che mantiene lo stato delle precedenti operazioni dell'ALU.

In generale, l'ISA ARM è progettata per offrire un'architettura efficiente e flessibile, consentendo l'accesso rapido alla memoria e operazioni aritmetiche e logiche su registri dedicati.

(pagine riassunte: 3)
### 5.1.7 - Panoramica del livello ISA dell'ATmega168 AVR
A differenza del Core i7 (usato prevalentemente nei desktop e nelle server farm) e dell'OMAP4430 (impiegato soprattutto nei telefoni, tablet e altri dispositivi mobili), l'ATmega168 è usato **nei sistemi integrati**, quali i semafori e le radiosveglie, per il loro controllo, la gestione dei pulsanti, delle luci e delle altre parti che costituiscono l'interfaccia utente.

L'ATmega168 ha **una sola modalità e nessuna protezione hardware**, poiché non si dà mai il caso che esegua programmi di utenti potenzialmente ostili. Anche il modello della memoria è estremamente semplice: c'è uno spazio di memoria di 16 KB per i programmi e uno, distinto, di 1 KB per i dati.
Gli spazi di programma e dati sono separati al fine di implementare lo spazio dei programmi in una memoria flash e lo spazio dei dati in una SRAM.

L'ATmega168 fa uso di un'organizzazione di **memoria a due livelli** per offrire una maggior sicurezza. La memoria flash del programma è divisa nella sezione del boot loader e nella sezione delle applicazioni
Per ragioni di sicurezza solo il codice della sezione del boot loader può aggiornare la memoria flash. Grazie a questa funzionalità un qualsiasi codice può essere posizionato nella sezione delle applicazioni con la certezza che non possa intaccare altro codice presente nel sistema. 

Per vincolare maggiormente il sistema, un distributore può firmare digitalmente il codice. 

Questo approccio è piuttosto flessibile e permette di sostituire anche il boot loader, a patto che il nuovo codice sia correttamente firmato. 

L'ATmega168 **contiene 32 registri** a uso generale da 8 bit, chiamati RO - R31, a cui le istruzioni accedono tramite un campo di 5 bit che specifica il numero del registro. Una peculiarità dei registri dell'ATmega168 è che essi sono anche presenti nello spazio di memoria. Il byte O dello spazio dati è equivalente al registro RO e quando un'istruzione modifica il registro RO e poi legge il byte 0 di memoria, trova in questa posizione il nuovo valore scritto in RO. Analogamente, il byte 1 nella memoria è R1, e così via fino al byte 31. 

Agli indirizzi di memoria da 32 a 95, immediatamente sopra ai 32 registri a uso generale, ci sono 64 byte riservati per l'accesso ai registri dei dispositivi di 1/0, inclusi i dispositivi interni al SoC.

L'ATmega168 dispone di un piccolo numero di registri specializzati. Il **registro di stato** contiene:
1) Bit di abilitazione di interrupt.
2) Bit ausiliario di riporto.
3) Bit di segno.
4) Bit di overflow.
5) Flag negativo.
6) Flag zero.
7) Bit di riporto.

Lo Stack Pointer (SP), mantiene l'indirizzo corrente dello spazio dei dati a cui le istruzioni di PUSH e POP accederanno. Lo stack pointer si trova all'indirizzo 80 della memoria di I/O.
(pagine riassunte: 2)
## 5.2 - Tipi di dati
A livello ISA, sono disponibili diversi tipi di dati che possono essere manipolati dalle istruzioni del processore. Tuttavia, una delle questioni fondamentali è la presenza o meno di supporto hardware per un particolare tipo di dati.

Il supporto hardware implica che una o più istruzioni si aspettano che i dati siano rappresentati in un formato specifico e l'utente non è libero di scegliere un formato diverso. Ad esempio, nel caso degli interi, l'hardware potrebbe aspettarsi che il bit più significativo rappresenti il segno del numero, e se questo formato non viene rispettato, il funzionamento del sistema potrebbe essere compromesso.

In alcuni contesti, ad esempio per la valutazione del debito pubblico, potrebbero essere necessari numeri molto più grandi di quelli supportati nativamente dall'hardware. In questi casi, potrebbe essere necessario implementare una gestione software per la rappresentazione e l'aritmetica di numeri di dimensioni maggiori, ad esempio utilizzando due interi di 32 bit per rappresentare un singolo numero (64 bit in totale), anche chiamato **precisione doppia**.

Il concetto di "precisione doppia" si riferisce alla capacità di rappresentare e manipolare numeri con una maggiore precisione rispetto ai numeri interi a 32 bit standard. Questo è particolarmente utile in applicazioni che richiedono una maggiore precisione numerica, come nel caso di calcoli scientifici o finanziari complessi.

(pagine riassunte: 1)
### 5.2.1 - Tipi di dati numerici
I tipi di dati possono essere suddivisi in due categorie principali: numerici e non numerici. Iniziamo con i dati numerici, che comprendono gli interi e i numeri in virgola mobile.

Gli interi sono utilizzati per contare oggetti, identificare elementi, e per una varietà di altri scopi. Possono essere di diverse lunghezze, tipicamente 8, 16, 32 e 64 bit. La rappresentazione più comune degli interi avviene in notazione binaria in complemento a due, che permette di rappresentare sia numeri positivi che negativi. Ad esempio, un intero senza segno di 32 bit può rappresentare valori compresi tra 0 e $2^{32}-1$, mentre un intero con segno di 32 bit può gestire numeri compresi tra -$2^{31}$ e $2^{31}-1$.

Per rappresentare numeri che non possono essere espressi come interi, come ad esempio 3,5, si utilizzano i numeri in virgola mobile. Questi numeri sono solitamente di lunghezza 32, 64 o 128 bit e consentono la rappresentazione di valori con parte intera e parte frazionaria. La maggior parte dei computer moderni dispone di istruzioni dedicate per l'aritmetica in virgola mobile e spesso hanno registri separati per operandi interi e in virgola mobile.

Alcuni linguaggi di programmazione, come il COBOL, supportano anche un tipo di dati per i numeri decimali. Questi numeri vengono spesso rappresentati nell'hardware utilizzando la codifica binaria dei decimali (BCD), dove ogni cifra decimale viene codificata con 4 bit. Tuttavia, l'aritmetica dei numeri decimali impacchettati può comportare delle complicazioni, quindi possono essere necessarie istruzioni aggiuntive per la correzione dell'aritmetica decimale. 
(pagine riassunte: 1)
### 5.2.2 - Tipi di dati non numerici
I primi computer macinavano numeri, mentre i computer moderni devono elaborare diversi tipi di dati, molto spesso non numerici.
#### 5.2.2.1 I caratteri
Tra questi, i caratteri giocano un ruolo centrale. I computer utilizzano comunemente codici carattere come ASCII e UNICODE, che definiscono rispettivamente caratteri di 7 e 16 bit. Le stringhe di caratteri, ovvero sequenze di caratteri, sono spesso gestite tramite istruzioni speciali nel livello ISA. Le stringhe possono essere delimitate da un carattere speciale di fine stringa o possono essere dotate di un campo lunghezza per indicare la loro estensione.
#### 5.2.2.2 I valori booleani
I valori booleani, che possono essere solo vero o falso, sono altrettanto importanti. Sebbene teoricamente un solo bit sarebbe sufficiente per rappresentare un dato booleano, in pratica spesso si utilizzano interi byte per consentire un accesso più semplice. Comunemente, si associa il valore 0 al falso e tutti gli altri valori al vero. Quando un valore booleano viene rappresentato dentro un'array, insieme ad altri valori booleani, si crea una struttura di dati detta #bit_map.
#### 5.2.2.3 I puntatori
Infine, i puntatori rappresentano un altro tipo di dato importante, essenzialmente un indirizzo di memoria. Sono comunemente usati per accedere a variabili o dati memorizzati in una certa posizione di memoria. Tuttavia, l'uso dei puntatori richiede estrema cura, poiché errori nella loro gestione possono causare gravi problemi nel programma.
(pagine riassunte: 1)
### 5.2.3 - Tipi di dati del Core i7
Il Core i7 supporta gli interi con segno in complemento a due, gli interi senza segno, i numeri decimali in codifica binaria e i numeri in virgola mobile nel formato IEEE 754.
Il Core i7 gestisce, oltre agli interi a 32 bit, anche gli interi di quelle lunghezze, e mette a disposizione numerose istruzioni per gestire la loro aritmetica, le operazioni booleane e i confronti su di loro. Il processore può opzionalmente essere utilizzato nella modalità a 64 bit che supporta registri e operazioni a 64 bit.

Il Core i7 è **ben equipaggiato** per la manipolazione dei caratteri ASCII a 8 bit: ci sono istruzioni speciali per la copia e la ricerca di stringhe di caratteri.

(pagine riassunte: 0.5)
### 5.2.4 - Tipi di dati dell'OMAP4430 ARM
La CPU OMAP4430 supporta un ampio spettro di formati di dati.
#### 5.2.4.1 I numeri interi
Per quanto riguarda i soli interi, può gestire operandi da 8, 16 e 32 bit, con o senza segno.
Internamente, l'OMAP4430 è una macchina a 32 bit con percorso dati e istruzioni da 32 bit. Un programma può specificare dimensione e segno di un valore da caricare e il valore viene convertito dalle istruzioni di caricamento nel corrispondente valore a 32 bit.
Gli interi con segno usano il formato in **complemento a due**. 
Sono disponibili operandi in virgola mobile di 32 e 64 che rispettano lo standard IEEE 754. Tutti gli operandi devono essere allineati in memoria.
#### 5.2.4.2 I caratteri
**Non ci sono** istruzioni hardware speciali per il supporto di tipi di dati carattere e stringa.
Sad, i know.
(pagine riassunte: 0.5)
### 5.2.5 - Tipi di dati dell'ATmega168
L'ATmega168 dispone di una varietà di tipi di dati molto limitata. Tutti i registri sono lunghi 8 bit, con una sola eccezione, e così anche gli interi sono di 8 bit, così come i caratteri. 

Per facilitare l'accesso alla memoria, l'ATmega168 include anche un supporto limitato a puntatori senza segno di 16 bit. I puntatori da 16 bit X, Y e Z sono formati dalla concatenazione delle coppie di registri di 8 bit R26/R27, R28/R29 e R30/R31 rispettivamente.
(pagine riassunte: 0.5)
## 5.3 - Formati d'istruzione
Un’istruzione consiste in un opcode (codice operativo), di solito corredato da altre informazioni quali la provenienza degli operandi e la destinazione dei risultati. L’argomento generale che tratta della provenienza degli operandi (cioè il loro indirizzo) è detto indirizzamento. Un’istruzione è dotata di un opcode che ne specifica il comportamento, e può contenere nessuno, uno, due o tre indirizzi.

Alcune macchine hanno tutte le istruzioni della stessa lunghezza, altre dispongono d’istruzioni di lunghezza diversa. Le istruzioni possono essere più corte, altrettanto lunghe o più lunghe della dimensione di parola. La scelta di avere tutte le istruzioni della stessa lunghezza semplifica la loro decodifica, ma spesso implica uno spreco di spazio, visto che tutte le istruzioni devono essere lunghe quanto la più lunga.

(pagine riassunte: 0.5)
### 5.3.1 - Criteri progettuali per i formati d'istruzioni
L'efficienza di un ISA dipende fortemente dalla tecnologia utilizzata nell'implementazione del computer. Ad esempio, un'architettura basata sullo stack può essere efficace se gli accessi in memoria sono veloci, mentre una con molti registri può essere preferibile in altri contesti.
Vista la sua importanza, ci sono 3 criteri che vengono affrontati nella progettazione dei formati d'istruzione:
#### 5.3.1.1 Primo criterio: Larghezza delle istruzioni.
La lunghezza delle istruzioni è un aspetto critico. Sebbene istruzioni più corte occupino meno spazio di memoria, possono essere più difficili da decodificare o sovrapporre. Tuttavia, istruzioni più brevi possono contribuire a velocizzare il processore, soprattutto quando si tratta di accedere alla memoria o alle cache. La dimensione delle istruzioni è quindi un compromesso tra spazio, decodifica, esecuzione e larghezza di banda della memoria.
#### 5.3.1.2 Secondo criterio: Quantità di spazio per le operazioni.
Un altro criterio progettuale riguarda lo spazio necessario per esprimere tutte le operazioni desiderate. È importante prevedere un numero sufficiente di codici operativi per supportare le funzionalità richieste, evitando così di rimanere vincolati dalle limitazioni del formato delle istruzioni.
#### 5.3.1.3 Terzo criterio: Numero di bit nel campo degli indirizzi.
Infine, il numero di bit in un campo degli indirizzi è cruciale. Maggiore risoluzione nell'accesso alla memoria può significare indirizzi più lunghi e istruzioni più complesse. Un compromesso è necessario per bilanciare la risoluzione dell'accesso alla memoria con la lunghezza delle istruzioni e le prestazioni complessive del sistema.

#### 5.3.1.4 Conclusioni
I computer moderni hanno raggiungo un compromesso... discutibile. Da un lato, si usano tanti bit quanti sono necessari per indirizzare individualmente i byte, dall'altra spesso si accede alla memoria per leggere una, due o addirittura quattro parole alla volta. 

(pagine riassunte: 2.5)
### 5.3.2 - Codice operativo espandibile
Introduciamo il concetto di  **codice operativo espandibile** attraverso un esempio. Si considera una macchina con istruzioni lunghe 16 bit e indirizzi di 4 bit. Se i progettisti necessitano di varie combinazioni di istruzioni con diversi numeri di indirizzi, possono utilizzare un'approccio in cui un opcode speciale (ad esempio 15) indica che i bit 8-15 contengono l'opcode effettivo, consentendo così di interpretare gli altri bit in modi diversi a seconda del contesto.

Nell'esempio, si osserva un incremento progressivo della dimensione dell'opcode, che passa da 4 bit per istruzioni con tre indirizzi fino a 16 bit per istruzioni senza indirizzi. Questo evidenzia il compromesso tra lo spazio riservato all'opcode e alle altre informazioni.

I codici operativi espandibili consentono di utilizzare dimensioni di opcode variabili, mantenendo costante la lunghezza delle istruzioni o minimizzando la lunghezza media delle istruzioni. Tuttavia, l'uso di opcode di lunghezza variabile con istruzioni di lunghezza diverse e non allineate al byte può essere controproducente a causa della necessità di decodificare rapidamente le istruzioni.

Infine, sebbene siano esistiti ISA con opcode di lunghezza variabile, come l'Intel 432, l'importanza dell'allineamento e della decodifica rapida spinge generalmente verso l'impiego di opcode allineati al byte.

Facciamo un'esempio: 
1) Opcode di 4 bit, con 15 istruzioni e tre indirizzi (x, y, z):

| 0000 (istruzione 1)  | xxxx | yyyy | zzzz |
| -------------------- | ---- | ---- | ---- |
| 0001                 | xxxx | yyyy | zzzz |
| ...                  | xxxx | yyyy | zzzz |
| 1110 (istruzione 15) | xxxx | yyyy | zzzz |


2) Opcode di 8 bit, con 14 istruzioni e due indirizzi (y, z):

| 1111 | 0000 (istruzione 1)  | yyyy | zzzz |
| ---- | -------------------- | ---- | ---- |
| 1111 | 0001                 | yyyy | zzzz |
| 1111 | ....                 | yyyy | zzzz |
| 1111 | 1101 (istruzione 14) | yyyy | zzzz |


3) Opcode di 12 bit, con 31 istruzioni e un indirizzo (z)

| 1111 | 1110 | 0000 (istruzione 1)  | zzzz |
| ---- | ---- | -------------------- | ---- |
| 1111 | 1110 | 0001                 | zzzz |
| 1111 | 1110 | ....                 | zzzz |
| 1111 | 1110 | 1111 (istruzione 16) | zzzz |
| 1111 | 1111 | 0000 (istruzione 17) | zzzz |
| 1111 | 1111 | 0001                 | zzzz |
| 1111 | 1111 | ....                 | zzzz |
| 1111 | 1111 | 1110 (istruzione 31) | zzzz |

4) Opcode di 16 bit, 16 istruzioni senza indirizzi

| 1111 | 1111 | 1111 | 0000 (istruzione 1)  |
| ---- | ---- | ---- | -------------------- |
| 1111 | 1111 | 1111 | 0001 (istruzione 2)  |
| 1111 | 1111 | 1111 | ...                  |
| 1111 | 1111 | 1111 | 1111 (istruzione 16) |


(pagine riassunte: 2.5)
### 5.3.3 - Formati delle istruzioni del Core i7
Il formato delle istruzioni del Core i7 è complesso e irregolare: questa complessità deriva dall'evoluzione dell'architettura attraverso molte generazioni e dalla necessità di mantenere la retrocompatibilità. Inizialmente, tutti i codici operativi erano lunghi un byte, ma il concetto di **byte prefisso** veniva ampiamente utilizzato per modificare alcune istruzioni. Un byte prefisso è un codice operativo supplementare posto all'inizio di un'istruzione per cambiarne il comportamento, come nel caso dell'istruzione WIDE dell'IJVM.

In seguito, Intel si trovò a esaurire gli opcode disponibili e scelse l'opcode 0xFF per designare un **codice di escape**, indicando la presenza di un secondo byte per specificare l'istruzione. L'opcode deve essere completamente decodificato per determinare quale classe di operazioni eseguire e quanto lunga sia l'istruzione corrispondente, il che peggiora la performance.

Nella maggior parte delle istruzioni che coinvolgono un operando in memoria, dopo il byte di opcode si trova un byte (di modo) contenente informazioni sull'operando. Questo byte è composto da un campo MOD da 2 bit e da due campi di 3 bit, REG e R / M. Il campo MOD consente quattro modalità d'indirizzamento degli operandi, ma almeno un operando deve essere un registro. Alcune modalità richiedono un bit supplementare chiamato **SIB** (Scala, Indice e Base) per ulteriori specificazioni.

Inoltre, alcune istruzioni possono essere seguite da 1, 2 o 4 byte aggiuntivi che specificano l'indirizzo di memoria (lo spiazzamento) e addirittura da ulteriori 1, 2 o 4 byte contenenti una costante (operando immediato).

(pagine riassunte: 1.5)
### 5.3.4 - Formati delle istruzioni dell'OMAP4430 ARM
L'ISA dell'OMAP4430 include istruzioni da 16 e 32 bit allineate in memoria. Le istruzioni sono progettate per essere semplici, con ciascuna che specifica una singola azione. Le istruzioni aritmetiche tipiche specificano due indirizzi come operandi sorgente e un solo registro come destinazione.

Le istruzioni a 16 bit sono versioni più snelle di quelle a 32 bit, ma hanno delle limitazioni: possono accettare solo due registri come operandi, e possono utilizzare soltanto i primi 8 registri. 
Questa versione ridotta dell'ISA ARM è chiamata  **Thumb ISA**. Alcune varianti aggiuntive permettono l'uso di costanti senza segno di varie dimensioni al posto di uno dei registri.

Il formato delle istruzioni ARM a 32 bit è complesso e comprende varie modalità di encoding. Ad esempio, i bit 26 e 27 di ogni istruzione determinano il formato dell'istruzione e indicano all'hardware dove trovare il resto del codice operativo. Il campo condizione nei bit più significativi rende ogni istruzione una istruzione predicato, eseguita solo se soddisfa determinate condizioni basate sul registro di stato del processore (PSR).

Nelle istruzioni a 32 bit, non è possibile includere una costante di 32 bit direttamente. L'istruzione MOVT imposta i 16 bit più significativi di un registro a 32 bit, mentre un'altra istruzione imposta i 16 bit rimanenti. Ogni istruzione a 32 bit ha un campo di 4 bit per il codice di condizione.

Il formato delle istruzioni di salto è speciale, in quanto sono necessari 24 bit per specificare l'indirizzo destinazione per i salti o le chiamate a procedura, ed ha un opcode di 3 bit.

L'approccio dei progettisti dell'ISA ARM era quello di utilizzare completamente ogni combinazione di bit, anche combinazioni illegali di operandi, per specificare le istruzioni. Questo rende la logica di decodifica delle istruzioni estremamente complicata, ma consente di massimizzare il numero di operazioni codificate in istruzioni di lunghezza fissa.

(pagine riassunte: 1.5)
### 5.3.5 - Formati delle istruzioni dell'ATmega168
L'ATmega168 AVR dispone di sei formati d'istruzioni semplici, che possono essere lunghe 2 o 4 byte.

1. **Primo formato:** Consiste in un opcode e due registri operandi, di cui uno è utilizzato solo in input e l'altro sia in input che in output. Ad esempio, l'istruzione ADD per i registri utilizza questo formato.

2. **Secondo formato:** È di 16 bit e include un opcode aggiuntivo e un numero di registro di 5 bit. Questo formato permette di aumentare il numero di operazioni codificate dall'ISA, ma riduce il numero di operandi a uno solo. Esempi di queste operazioni sono la negazione e l'incremento.

3. **Terzo formato:** Ha un operando immediato senza segno di 8 bit. Le istruzioni che utilizzano questa codifica possono avere un solo registro operando (utilizzato sia come input che come output) e il registro può appartenere solo all'insieme dei registri da R16 a R31. Il numero dei bit per l'opcode è dimezzato, permettendo solo a 4 istruzioni (SUBCI, SUBI, ORI, ANDI) di utilizzare questo formato.

4. **Quarto formato:** Codifica le istruzioni di load e store, che utilizzano un operando immediato senza segno di 6 bit. Il registro base è un registro fissato che non viene specificato nella codifica dell'istruzione, perché è implicito nell'opcode.

5. **Quinto e sesto formato:** Sono utilizzati per i salti e le chiamate di procedura. Il primo utilizza un valore immediato con segno di 12 bit che viene aggiunto al valore del registro PC per calcolare la destinazione del salto. L'ultimo formato espande lo spiazzamento a 22 bit, portando la dimensione dell'istruzione AVR a 32 bit.

(pagine riassunte: 0.5)
## 5.4 - Indirizzamento 
Molte istruzioni contengono operandi e si pone il problema di come specificarne la posizione. 
L'**indirizzamento** è l'argomento che tratta di queste problematiche.

### 5.4.1 - Modalità d'indirizzamento
Finora abbiamo trascurato l'interpretazione dei bit nei campi d'indirizzo per trovare gli operandi. È ora di esaminare più da vicino le modalità di indirizzamento. Vedremo che ci sono diverse modalità di implementazione. 
### 5.4.2 - Indirizzamento immediato
Il metodo più semplice per specificare un operando in un'istruzione è includere direttamente l'operando nel campo destinato all'indirizzo, anziché un indirizzo o altre informazioni sulla posizione. Questo tipo di operando è chiamato **immediato**, poiché viene ottenuto direttamente dalla memoria nel momento in cui viene eseguito il fetch dell'istruzione, rendendolo immediatamente disponibile per l'uso. Tuttavia, l'indirizzamento immediato ha l'inconveniente di poter fornire solo un operando alla volta e la dimensione del campo limita il valore dell'operando. Nonostante ciò, è una tecnica utilizzata in molte architetture per specificare piccole costanti intere.
ES:

| MOV | R1  | 4   |
| --- | --- | --- |

(pagine riassunte: 0.5)
### 5.4.3 - Indirizzamento diretto
L'indirizzamento diretto è un metodo per specificare un operando in memoria mediante l'uso dell'indirizzo completo. Tuttavia, presenta limitazioni simili a quelle dell'indirizzamento immediato: l'istruzione accede sempre alla stessa locazione di memoria, anche se il valore contenuto può cambiare. Questo rende l'indirizzamento diretto adatto solo per accedere a variabili globali il cui indirizzo è noto in fase di compilazione. Nonostante ciò, è ampiamente utilizzato nei programmi che definiscono variabili globali. Nelle prossime righe, esamineremo come il computer determina quali indirizzi sono immediati e quali sono diretti.

(pagine riassunte:0.5)
### 5.4.4 - Indirizzamento a registro
L'indirizzamento a registro è simile concettualmente all'indirizzamento diretto, ma specifica un registro anziché una locazione di memoria. È la modalità di indirizzamento più comune nella maggior parte dei computer, poiché i registri sono veloci nell'accesso e hanno indirizzi brevi. I compilatori spesso anticipano quali variabili verranno richiamate più frequentemente (come gli indici di ciclo) e le assegnano ai registri. Questa modalità è conosciuta semplicemente come "modalità a registro". 
Nelle architetture load/store come l'OMAP4430 ARM, quasi tutte le istruzioni utilizzano esclusivamente questa modalità di indirizzamento. L'unico caso in cui non viene utilizzata è quando un operando viene trasferito dalla memoria in un registro (istruzione LOAD) o da un registro in memoria (istruzione STORE). Anche in questi casi, uno degli operandi è un registro che contiene l'indirizzo della parola di memoria in lettura o scrittura.

(pagine riassunte: 0.5)
### 5.4.5 - Indirizzamento a registro indiretto
In questa modalità, l’operando è in memoria, ma il suo indirizzo è contenuto in un registro, non incorporato nell’istruzione come nell’indirizzamento diretto. Questo registro viene chiamato **puntatore**. L'indirizzamento a registro indiretto permette di referenziare la memoria senza incorporare l'intero indirizzo nell'istruzione e consente di usare diverse parole di memoria durante esecuzioni diverse della stessa istruzione.
Immaginiamo un ciclo che somma i 1024 elementi di un vettore d’interi nel registro R1. Due registri, R2 e R3, puntano rispettivamente al primo elemento dell’array e all’indirizzo subito dopo l’ultimo elemento. Se l'array inizia all'indirizzo A e contiene 1024 interi di 4 byte ciascuno, il primo indirizzo dopo l'array sarà A + 4096.
```
Codice:

		MOV R1,#0
		MOV R2,#A
		MOV R3,#A+4096
CICLO:  ADD R1,(R2)
		ADD R2,R3
		CMP R2,R3
		BLT CICLO
```
Il codice di esempio mostra diverse modalità di indirizzamento. Le prime tre istruzioni usano l’indirizzamento a registro per il primo operando e l’indirizzamento immediato per il secondo. La seconda istruzione copia l'indirizzo di A in R2, specificato con il simbolo #. La terza istruzione copia in R2 l'indirizzo della prima parola oltre l’array.
Il ciclo vero e proprio non contiene nessun indirizzo di memoria: usa l’indirizzamento a registro e quello a registro indiretto. Questo rende il ciclo conciso e veloce. Il rifiuto di usare indirizzi di memoria produce un codice efficiente. 
Un’altra soluzione potrebbe essere l'uso di un programma **auto-modificante**. Invece di usare l’indirizzamento a registro indiretto, l'istruzione nel ciclo potrebbe modificare sé stessa per sommare il prossimo elemento dell'array. Ad esempio, dopo una iterazione, l’istruzione

ADD R1, A
diventerebbe

ADD R1, A+4
I programmi auto-modificanti, proposti da John Von Neumann, erano utili sui primi computer, ma oggi sono considerati di pessimo stile, difficili da capire e incompatibili con le moderne architetture hardware, che presuppongono che i programmi non si auto-modifichino. Fortunatamente, questa pratica è scomparsa.

(pagine riassunte: 1.5)
### 5.4.6 - Indirizzamento indicizzato
L’indirizzamento indicizzato consente di referenziare una parola di memoria a un dato spiazzamento dal contenuto di un registro. Ad esempio, in IJVM le variabili locali sono referenziate specificando il loro spiazzamento rispetto a LV. Questa modalità combina un registro con un offset costante.
Consideriamo due vettori, A e B, di 1024 parole ciascuno. Vogliamo calcolare \($A_{i}$ AND $B_{i}$\) per ogni elemento e fare l’OR di questi risultati per verificare se c'è almeno una coppia di componenti non nulla. Possiamo salvare gli indirizzi di A e B in due registri e usare l’indirizzamento indicizzato per accedere agli elementi degli array.
```
codice: 
		MOV R1,#0
		MOV R2,#0
		MOV R3,#4096
CICLO:  MOV R4,A(R2)
		AND R4,B(R2)
		OR R1,R4
		ADD R2,#4
		CMP R2,R3
		BLT CICLO

```
Per questo programma, usiamo quattro registri:
1. R1 - contiene l’OR cumulativo dei prodotti logici.
2. R2 - l’indice *i* per visitare gli array.
3. R3 - la costante 4096, il primo valore di *i* da non considerare.
4. R4 - un registro di lavoro per il calcolo di ogni prodotto.
Il ciclo inizia con l’istruzione etichettata come CICLO. La prima istruzione effettua il fetch di $(A_{i})$ in R4 usando l’indirizzamento indicizzato: il valore di R2 viene sommato all’indirizzo base A. Ad esempio, la notazione:
MOV R4, A(R2)

significa che R4 (la destinazione) usa la modalità registro, mentre la sorgente usa la modalità indicizzata con offset A e registro R2. Se A vale 124300, l'istruzione diventa qualcosa come:
MOV R4, 124300(R2)

Alla prima iterazione, R2 vale 0, quindi la parola di memoria indicizzata è ($A_{0}$) all'indirizzo 124300, che viene salvata in R4. Alla seconda iterazione, R2 vale 4, quindi la parola di memoria indicizzata è ($A_{1}$) all'indirizzo 124304, e così via.
In questo esempio, l’offset nell’istruzione è l’indirizzo base A, e il registro contiene un piccolo intero incrementato ad ogni iterazione. Questa forma richiede un campo offset abbastanza grande nell’istruzione per contenere un indirizzo, ma spesso risulta la scelta migliore nonostante sia meno efficiente.

(pagine riassunte: 1.5)
### 5.4.7 - Indirizzamento indicizzato esteso
Alcune macchine dispongono della cosiddetta modalità d'**indirizzamento indicizzato esteso**, in cui l'indirizzo di memoria è calcolato sommando tra loro il contenuto di due registri più un offset (opzionale). Un registro funge da base e l'altro da indice. Nella pratica, le macchine che dispongono di questa modalità sono corredate della forma con offset di 8 o 16 bit.

(pagine riassunte: 0.5)
### 5.4.8 - Indirizzamento a stack
 Abbiamo già sottolineato che è molto consigliabile rendere le istruzioni macchina quanto più corte possibile. Il limite alla riduzione della lunghezza degli indirizzi equivale a non averne per nulla. In questo paragrafo analizziamo più da vicino l 'indirizzamento a stack.
#### 5.4.8.1 - Notazione polacca inversa
La forma con l’operatore “ in” mezzo è detta notazione infissa, mentre la forma con l’operatore dopo gli operandi si chiama postfissa o anche notazione polacca inversa, dal logico polacco J. Lukasiewicz (1958) che ne studiò le proprietà. Questo tipo di notazione è molto utilizzata grazie al fatto che qualsiasi formula si può scrivere senza l'utilizzo delle parentesi.

#### 5.4.8.2 -Valutazione delle formule in notazione polacca inversa
La notazione polacca inversa è la notazione ideale per la valutazione di una formula da parte di un computer dotato di stack. Una formula è costituita da $n$ simboli, ciascuno dei quali è un operando o un operatore. L’algoritmo che si avvale di uno stack per la valutazione di una formula in notazione polacca inversa è molto semplice: scorre la stringa da sinistra verso destra e, quando incontra un operando, lo impila sullo stack. Invece quando incontra un operatore ne esegue l'istruzione corrispondente. Il numero sulla cima dello stack è l’operando destro, non quello sinistro; questa precisazione è importante perché nella divisione e nella sottrazione l’ordine degli operandi conta (a differenza dell’addizione e della moltiplicazione). In altre parole, IDIV è stata definita appositamente in modo tale che, dopo aver fatto il push del numeratore e poi quello del denominatore, la sua esecuzione produca come risultato la divisione corretta. Si noti la semplicità di generazione del codice per l’IJVM: si scorre la notazione polacca inversa della formula e si restituisce un’istruzione per ciascun simbolo. Se il simbolo è una costante o una variabile, si restituisce un’istruzione di push sullo stack; se il simbolo è un operatore, si restituisce l’istruzione che esegue l’operazione.

(pagine riassunte: 3.5)
### 5.4.9 - Modalità d'indirizzamento per istruzioni di salto
Le istruzioni di salto necessitano di una modalità di indirizzamento per specificare l'indirizzo di destinazione.
#### 5.4.9.1 Indirizzamento diretto
L'indirizzamento diretto è un'opzione possibile, dato che l'indirizzo di destinazione viene semplicemente riportato per intero all'interno dell'istruzione.
#### 5.4.9.2 Indirizzamento a registro indiretto
L'indirizzamento a registro indiretto consente al programma di calcolare l'indirizzo di destinazione, scriverlo in un registro e quindi effettuare il salto. È la modalità più flessibile perché l'indirizzo di destinazione può essere calcolato durante l'esecuzione, ma è anche molto incline a generare bug.
#### 5.4.9.3 Modalità indicizzata e Indirizzamento relativo al PC
La modalità indicizzata specifica un certo offset rispetto all'indirizzo contenuto in un registro, ed ha le stesse proprietà della modalità a registro indiretto. 
L'indirizzamento relativo al PC (program counter) consiste in un offset (con segno) contenuto nell'istruzione stessa che viene sommato al program counter per ottenere l'indirizzo di destinazione.
### 5.4.10 - Modalità d'indirizzamento dei codici operativi e delle modalità d'indirizzamento

Dal punto di vista software, le istruzioni e l'indirizzamento devono avere una struttura regolare con pochi formati d'istruzioni per facilitare il lavoro del compilatore e produrre codice di qualità. Gli opcode dovrebbero supportare tutte le modalità d'indirizzamento sensate e ogni registro (inclusi FP, SP e PC) dovrebbe essere utilizzabile in tutte le modalità a registro.

### 5.4.10.1 Esempio di Macchina a tre indirizzi

Un esempio di progetto elegante è una macchina a tre indirizzi con istruzioni di 32 bit, supportando fino a 256 codici operativi. Il **formato 1** prevede due indirizzi sorgente e un indirizzo destinazione, usato per le istruzioni logico-aritmetiche. L'ultimo campo di 8 bit può essere utilizzato per distinguere ulteriormente le istruzioni, ad esempio per le operazioni in virgola mobile. Se il bit 23 è asserito, l'istruzione passa al **formato 2**, in cui il secondo operando è una costante immediata con segno di 13 bit, adatta per le istruzioni LOAD e STORE con indirizzamento indicizzato.

Il **formato 3** è per i salti condizionati e altre istruzioni simili, con un proprio opcode e 24 bit per l'offset relativo al PC, coprendo un intervallo di 32 MB. Alcuni opcode potrebbero essere riservati per istruzioni LOAD e STORE con un offset lungo, limitate però a operare su un registro specifico (ad esempio, R0).

### 5.4.10.2 Esempio di Macchina a due indirizzi

Una macchina a due indirizzi, può specificare parole di memoria per entrambi gli operandi. Questo progetto, semplice ed efficiente, è stato utilizzato nelle macchine PDP-11 e VAX, che hanno dominato la scena informatica per vent'anni. Gli opcode sono di 8 bit, con 12 bit per specificare la sorgente e altri 12 per la destinazione, inclusi 3 bit per la modalità, 5 per il registro e 4 per l'offset. Le modalità supportate includono immediata, diretta, a registro, a registro indiretto, indicizzata, a stack, con spazio per altre due modalità.

Tutti i registri d'uso generale, inclusi il program counter, il puntatore allo stack e il puntatore alle variabili locali, sono accessibili. Tuttavia, l'indirizzamento diretto richiede più bit per gli indirizzi. La soluzione del PDP-11 e del VAX era di aggiungere una parola supplementare per ogni indirizzo di operando diretto. Un'altra modalità potrebbe essere un offset di 32 bit posposto all'istruzione.

### Compromessi e considerazioni

Sommare due operandi in memoria, entrambi indirizzati direttamente o con una lunga forma indicizzata, richiederebbe 96 bit e tre cicli di bus. Inoltre, sarebbero necessari tre cicli aggiuntivi per prelevare i due operandi e scrivere il risultato. Tuttavia, molte architetture RISC richiederebbero almeno 96 bit e quattro cicli di bus per operazioni simili, a seconda della modalità di indirizzamento.

Per variabili oltre la sedicesima, sono necessari offset di 32 bit. Un'altra alternativa potrebbe essere un formato con un solo offset di 8 bit, riferito alla sorgente o alla destinazione. I progettisti devono bilanciare vari fattori per ottenere un progetto efficace, giocando con numerose possibilità e compromessi.

### 5.4.11 - Modalità d'indirizzamento del Core i7

### 5.4.12 - Modalità d'indirizzamento dell'OMAP4430

### 5.4.13 - Modalità d'indirizzamento dell'ATmega168 AVR

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

