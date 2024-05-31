La progettazione della microarchitettura dipende non solo dall'ISA da implementare, ma anche dagli obiettivi di costo e prestazioni del calcolatore. Molti ISA moderni, specialmente le architetture RISC, includono istruzioni semplici eseguibili in un ciclo di clock. Invece, ISA più complessi come quello del Core i7 possono richiedere più cicli per eseguire un'istruzione, dovendo localizzare gli operandi in memoria, leggerli e memorizzare il risultato. Questa complessità comporta una strategia di controllo diversa rispetto agli ISA più semplici.
(pagine riassunte: 0.5)
## 4.1 - Esempio di microarchitettura
Ogni ISA è unico: usando un sottoinsieme della Java Virtual Machine, chiamato **IJVM** (contenente solo istruzioni su interi), studieremo un'esempio pratico.

Per implementare IJVM, descriveremo la microarchitettura necessaria. Le architetture con istruzioni complesse spesso usano la microprogrammazione. Nonostante IJVM sia piccolo, è un buon punto di partenza per descrivere controllo e ordinamento delle istruzioni.

La nostra microarchitettura includerà un microprogramma in una ROM per prelevare, decodificare ed eseguire le istruzioni IJVM. Per progettare una microarchitettura, è bene concepirla come un problema di programmazione, in cui ogni istruzione del livello ISA è una funzione richiamata in un loop che gira all'infinito.

Il microprogramma ha variabili che rappresentano lo **stato** del calcolatore, cambiato da ogni funzione. Il _Program Counter_ (PC) è una di queste variabili e punta all indirizzo di memoria della prossima istruzione da eseguire, avanzando (ovvero puntando sempre all istruzione successiva) durante l'esecuzione.

Le istruzioni IJVM sono corte, composte da campi specifici. Ad esempio, il primo campo è il  **codice operativo** (opcode): identifica il tipo di istruzione, ovvero se è di tipo ADD, BRANCH, ecc. Questo modello di esecuzione, chiamato **fetch-decodifica-esecuzione**, è utile a livello astratto e può essere la base per implementare ISA complessi come IJVM. L'insieme delle microistruzioni formano il microprogramma, e ciascuna di loro ha il controllo del percorso dati durante un ciclo.

(pagine riassunte: 1)
### 4.1.1 - Percorso dati
Il **percorso dati** della CPU contiene la ALU, i suoi input e output. Il nostro percorso dati ha registri a 32 bit (chiamati PC, SP, MDR) , accessibili solo a livello di microarchitettura. La maggior parte dei registri può inviare il contenuto sul bus B, collegato all'input della ALU, il cui output guida lo _shifter_, che invia il risultato sul bus C. 
I valori del bus C possono essere scritti simultaneamente in uno o più registri. Al momento, non c'è un bus A.

Figura 4.1

La ALU è controllata da sei linee: $F_{0}$ e $F_{1}$ determinano l'operazione, ENA e ENB abilitano gli input, INVA inverte l'input sinistro e INC forza la presenza di un riporto nel bit meno significativo. Non tutte le 64 combinazioni delle linee della ALU hanno un ruolo significativo. 
La ALU richiede due dati in ingresso, ovvero un input sinistro (A) e uno destro (B).
1) L'input sinistro è collegato un registro H, ovvero un registro holding, di mantenimento.
2) L'input destro è collegato il bus B, che può essere caricato con i valori di una qualsiasi delle nove sorgenti collegate al bus B.

 È possibile caricare un valore in H scegliendo una funzione della ALU, il cui compito è semplicemente quello di far passare l'input destro (dal bus B), direttamente nel suo output, senza modificarlo. 
 (si può ottenere lo stesso risultato disabilitando l'input input sinistro, forzandolo ad essere 0, tramite il registro ENA).
 L'output della ALU è gestito da altre due linee di controllo, SLL8 e SRA1.
 1) SLL8 trasla a sinistra di un byte, impostando a 0 gli 8 bit meno significativi
 2) SRA1 trasla a destra di un bit, mantenendo il bit più significativo.

È possibile leggere e scrivere lo stesso registro in un ciclo: questo è possibile perché anche se avviene nello stesso ciclo, avviene in momenti diversi (sempre nello stesso ciclo di clock).
Per incrementare SP di 1, è possibile portare il valore di SP sul bus B, disabilitando l'input sinistro della ALU, abilitando INC e si memorizza il risultato (incrementato di 1) di nuovo in SP. Quando un registro è selezionato come input destro della ALU, i suoi valori vengono mantenuti sul bus B per tutto il ciclo. 
La ALU opera e il risultato arriva al bus C attraverso lo shifter. Verso la fine del ciclo (ovvero quando gli output della ALU e dello shifter sono sicuramente stabili), un segnale di clock da il via alla memorizzazione del contenuto del bus C in uno o più registri, che può essere lo stesso registro di input di B. Questa temporizzazione precisa permette di leggere e scrivere lo stesso registro in un ciclo.

(pagine riassunte: 3)
#### 4.1.1.1 - Temporizzazione del percorso dati
All'inizio di ogni ciclo di clock viene generato un breve impulso, sincronizzato con il clock principale. Al fronte di discesa dell'impulso, i bit di controllo delle porte logiche vengono impostati, operazione che richiede un tempo $\Delta w$. Successivamente, il registro selezionato invia il suo contenuto sul bus B, stabilizzandosi dopo un tempo $\Delta x$. A questo punto, la ALU e lo shifter operano sui dati, con output stabili dopo un tempo $\Delta y$. Dopo un ulteriore tempo $\Delta z$, i risultati si propagano lungo il bus C fino ai registri, che vengono caricati al fronte di salita dell'impulso successivo. Questo caricamento è rapido, garantendo che le modifiche degli input non influenzino immediatamente il bus C.

Figura 4.3

All'interno del percorso dati, c'è un tempo di propagazione finito, anche senza elementi da memorizzare. Una modifica sul bus B non altererà istantaneamente il bus C, se non dopo un tot di tempo determinato. Quindi, anche se un'operazione di scrittura modifica un registro di input, il valore sarà reinserito in modo sicuro prima che il nuovo valore possa influenzare la ALU.

Per far funzionare questa architettura, è necessaria una temporizzazione rigida: un ciclo di clock lungo, un ritardo di propagazione della ALU noto e un caricamento veloce dei registri dal bus C. Con un'attenta progettazione, il percorso dati può funzionare correttamente in ogni momento, come accade nelle macchine reali.

Il ciclo del percorso dati può essere visto come diviso in sottocicli, con l'inizio del sottociclo 1 guidato dal fronte di discesa del clock:

1. Impostazione dei segnali di controllo ($\Delta w$)
2. Caricamento dei registri nel bus B ($\Delta x$)
3. Operazioni della ALU e dello shifter ($\Delta y$)
4. Propagazione dei risultati lungo il bus C e caricamento nei registri ($\Delta z$)

L'intervallo dopo $\Delta z$ ha una certa tolleranza. Al fronte di salita del ciclo successivo, i risultati sono memorizzati nei registri.

I sottocicli non sono definiti esplicitamente, poiché nessun impulso di clock segnala alle ALU e allo shifter di funzionare continuamente; i loro input sono inconsistenti fino a $\Delta w+\Delta x$ dopo il fronte di discesa del clock, e i loro output sono inconsistenti fino a $\Delta w+\Delta x+\Delta y$. 
L'unico segnali espliciti che guidano il percorso dati sono il fronte di salita/discesa, che rispettivamente fanno partire il percorso dati e caricano i registri.
È responsabilità dell'ingegnere progettista assicurarsi che $\Delta w+\Delta x+\Delta y+\Delta z$ sia sufficientemente breve rispetto al fronte di salita del clock, garantendo il corretto caricamento dei registri.

(pagine riassunte: 2)
#### 4.1.1.1.1\ - Operazioni della memoria
La nostra macchina ha due modalità di comunicazione con la memoria: una porta a 32 bit con indirizzi espressi in parole e una porta a 8 bit con indirizzi espressi in byte. La porta a 32 bit è controllata dai registri MAR (Memory Address Register) e MDR (Memory Data Register), mentre la porta a 8 bit è controllata dal registro PC, che legge un byte negli 8 bit meno significativi di MBR. La porta a 8 bit può solo leggere dati dalla memoria.

Ogni registro è controllato da uno o due **segnali di controllo**. Una freccia bianca sotto un registro indica un segnale di controllo che abilita l'output del registro verso il bus B. Una freccia nera indica un segnale di controllo che scrive nel registro un valore proveniente dal bus C. Per iniziare una lettura o una scrittura, bisogna caricare il registro di memoria appropriato e inviare un segnale di scrittura alla memoria.

Le due modalità di accesso sono necessarie perché MAR e PC si riferiscono a diverse parti della memoria. MAR/MDR sono utilizzati per leggere e scrivere parole di dati a livello ISA, mentre PC/MBR leggono il programma eseguibile a livello ISA, che consiste in un flusso di byte.

Nelle implementazioni reali, esiste una sola memoria orientata al byte. MAR può contare il numero di parole, anche se gli indirizzi sono espressi in byte. Quando MAR viene portato sul bus degli indirizzi, i suoi 32 bit non sono mappati direttamente sulle 32 linee. I 2 bit più alti di MAR vengono scartati perché inutili per la nostra macchina, che ha un limite di indirizzamento di 4 GB. Così, quando MAR vale 1, sul bus viene posto l'indirizzo 4; quando MAR vale 2, l'indirizzo 8, e così via.

Per convertire il registro MBR a 8 bit in una parola a 32 bit, si tratta il valore con segno compreso tra -128 e +127, utilizzando un processo chiamato **estensione del segno**. Questo consiste nel duplicare il bit del segno di MBR nei 24 bit più alti del bus B. La scelta tra convertire gli 8 bit di MBR in un valore a 32 bit con o senza segno è determinata dal segnale di controllo. La presenza delle due frecce giustifica la necessità di distinguere tra queste due opzioni.

(pagine riassunte: 2)
### 4.1.2 - Microistruzioni
Per controllare il percorso dati della figura 4.1, utilizziamo 29 segnali, suddivisi in cinque gruppi funzionali:

1. 9 segnali per controllare la scrittura dei dati dal bus C ai registri.
2. 9 segnali per abilitare i registri sul bus B come input per la ALU.
3. 8 segnali per controllare le funzioni della ALU e dello shifter.
4. 2 segnali (non mostrati) per indicare alla memoria di leggere o scrivere attraverso MAR e MDR.
5. 1 segnale (non mostrato) per indicare il prelievo dalla memoria attraverso PC o MBR.

Questi 29 segnali specificano le operazioni da eseguire durante un ciclo del percorso dati, che include:

1. Portare i valori dei registri sul bus B.
2. Propagare i segnali attraverso ALU e shifter.
3. Guidare i risultati sul bus C.
4. Scrivere i risultati nei registri appropriati.

Se viene asserito il segnale per una lettura dalla memoria, l'operazione inizia alla fine del ciclo del percorso dati, dopo il caricamento di MAR. Una lettura della memoria avviata alla fine del ciclo k+1 trasmette dati utilizzabili solo a partire dal ciclo k+2. In altre parole, carichiamo MAR alla fine del ciclo e avviamo l'operazione di memoria subito dopo. Poiché la memoria richiede un ciclo di clock, i dati non saranno disponibili in MDR all'inizio del ciclo successivo, soprattutto con impulsi di clock brevi. Deve quindi trascorrere un ciclo completo del percorso dati tra l'inizio di una lettura della memoria e l'utilizzo del risultato. Durante questo ciclo è possibile eseguire altre operazioni che non richiedono dati dalla memoria.

In alcuni casi può essere utile scrivere l'output del bus C in più di un registro, mentre non ha senso abilitare più di un registro sul bus B contemporaneamente.

Per controllare il percorso dati, utilizziamo 24 segnali (bit):

- 9 per la scrittura dal bus C ai registri.
- 9 per abilitare i registri sul bus B.
- 8 per controllare ALU e shifter.
- 2 per le operazioni di memoria.
- 1 per il prelievo dalla memoria attraverso PC o MBR.

Questi bit controllano il percorso dati solo per un ciclo. Per determinare le operazioni del ciclo successivo, aggiungiamo due campi: NEXT_ADDRESS e JAM. Questi permettono di descrivere le operazioni da eseguire nel ciclo successivo, combinando i 24 bit di controllo con informazioni aggiuntive.

L'ordinamento dei gruppi nella figura 4.6 è stato scelto per minimizzare l'incrocio delle linee, che nei diagrammi schematici spesso corrisponde a collegamenti incrociati sui chip. Minimizzare questi incroci facilita il progetto dei chip.

(pagine riassunte 3)
### 4.1.3 - Unità di controllo microprogrammata: Mic-1

Finora abbiamo descritto come viene controllato il microprogramma, ma non abbiamo ancora spiegato come si decide quale dei segnali di controllo abilitare durante ciascun ciclo. Ciò è determinato da un **sequenzializzatore** che ha la responsabilità di far avanzare passo passo la sequenza di operazioni necessarie per eseguire una singola istruzione ISA. Durante ogni ciclo, il sequenzializzatore deve produrre due tipi di informazioni:

1. Lo stato di ogni segnale di controllo del sistema.
2. L'indirizzo della microistruzione da eseguire subito dopo.

La Figura 4.6 è un diagramma a blocchi dettagliato dell’intera microarchitettura della nostra macchina di esempio, chiamata Mic-1. Il diagramma è composto da due parti principali: il percorso dati, sulla sinistra, e la sezione di controllo, sulla destra. 

figura 4.6
##### Memoria di Controllo
L’elemento più grande e importante della sezione di controllo è la memoria di controllo. Questa memoria contiene l'intero microprogramma. È una memoria dedicata che memorizza le microistruzioni anziché le istruzioni ISA. Ogni microistruzione specifica esplicitamente il proprio successore, offrendo maggiore flessibilità rispetto alle istruzioni della memoria principale, che sono eseguite in ordine sequenziale.
##### Registri della Memoria di Controllo
La memoria di controllo necessita di un proprio registro di indirizzo e di un proprio registro dei dati:
- **MPC (MicroProgram Counter)**: è il registro degli indirizzi della memoria di controllo.
- **MIR (MicroInstruction Register)**: è il registro dei dati della memoria di controllo, che memorizza la microistruzione corrente. I bit di MIR determinano i segnali di controllo che guidano il percorso dati.
##### Funzionamento del Ciclo di Clock
1. **Sottociclo 1**:
    - All’inizio di un ciclo di clock, la parola contenuta nella memoria di controllo puntata da MPC viene trasferita in MIR. Il tempo necessario per questa operazione è $\Delta w$. MIR viene caricato durante il primo sottociclo.
2. **Sottociclo 2**:
    - Dopo che MIR è stato caricato, i vari segnali di controllo si propagano nel percorso dati. Dopo $\Delta w + \Delta x$, gli input della ALU diventano stabili.
3. **Sottociclo 3**:
    - Dopo un altro $\Delta y$, gli output della ALU e dello shifter diventano stabili. I valori di N e Z vengono salvati in flip-flop verso la fine del ciclo, in corrispondenza del fronte di salita del clock.
4. **Sottociclo 4**:
    - Dopo un ulteriore $\Delta z$, l’output dello shifter raggiunge i registri attraverso il bus C. I registri vengono caricati verso la fine del ciclo. Nel sottociclo 4 vengono caricati anche i flip-flop N e Z. Alla fine del ciclo, MPC viene caricato con il prossimo indirizzo.
#### Calcolo dell'Indirizzo della Microistruzione Successiva
Il microprogramma non segue necessariamente un ordine sequenziale nella memoria di controllo. Il campo **NEXT_ADDRESS** della microistruzione corrente indica l'indirizzo della microistruzione successiva. Il campo **JAM** determina ulteriori azioni da intraprendere:

- **JAMN**: Se abilitato, il flip-flop N viene combinato con il bit più significativo di MPC tramite OR.
- **JAMZ**: Se abilitato, il flip-flop Z viene combinato con il bit più significativo di MPC tramite OR.
- **JMPC**: Se abilitato, gli 8 bit di MBR vengono combinati in OR con gli 8 bit meno significativi di NEXT_ADDRESS.

Quando tutti i bit di JAM sono zero, l'indirizzo della microistruzione successiva è semplicemente il valore nel campo NEXT_ADDRESS o NEXT_ADDRESS in OR con 1. Altrimenti, ci sono due potenziali indirizzi: NEXT_ADDRESS e NEXT_ADDRESS calcolato in OR con 0x100. 

Ad esempio, se la microistruzione corrente ha il campo NEXT_ADDRESS = 0x92 e JAMZ impostato a 1, l'indirizzo successivo dipende dal bit Z. Se Z vale 0, la microistruzione successiva sarà all'indirizzo 0x92; altrimenti, sarà all'indirizzo 0x192.
#### Efficienza del Salto Condizionale
Il bit JMPC consente un salto efficiente utilizzando il contenuto di MBR per determinare l'indirizzo della microistruzione successiva. Questo metodo è utile per gestire rapidamente i salti basati sui codici operativi appena prelevati.
#### Conclusione
Ogni ciclo del microprogramma è autocontenuto: specifica cosa andrà sul bus B, quali operazioni la ALU e lo shifter devono eseguire, dove verrà memorizzato il bus C e quale sarà il successivo valore di MPC. La figura 4.6 semplifica la temporizzazione implementando MPC come un registro virtuale, riducendo la complessità del progetto e migliorando l'efficienza operativa.

(pagine riassunte: 6)
## 4.2 - Esempio di ISA: IJVM
Ci riferiremo all'architettura dell'insieme d'istruzioni (ISA) con il termine **macroarchitettura**, in contrapposizione con la microarchitettura.
### 4.2.1 - Stack
Le variabili locali delle procedure vengono memorizzate in una struttura dati chiamata **stack** (o "pila") della memoria. Questo approccio risolve il problema dell'allocazione di memoria per le variabili locali in modo che non interferiscano tra loro, specialmente quando una procedura richiama se stessa o altre procedure.

figura 4.8
#### Organizzazione della Memoria con lo Stack
##### Stack e Registri
- **LV (Local Variables pointer)**: Registro che punta alla base delle variabili locali della procedura corrente.
- **SP (Stack Pointer)**: Registro che punta alla cima dello stack.
#### Funzionamento dello Stack
##### Esempio di Chiamate di Procedure
1. **Chiamata di Procedura A**:
   - Quando la procedura A viene invocata, le sue variabili locali (ad esempio, a1, a2, a3) vengono allocate nello stack.
   - LV punta alla base delle variabili locali di A, mentre SP punta alla cima dello stack, dopo l'allocazione delle variabili di A.
2. **Chiamata di Procedura B da A**:
   - Quando A chiama B, il registro LV viene aggiornato per puntare alla base delle variabili locali di B e SP viene incrementato per allocare spazio per le variabili locali di B.
3. **Chiamata di Procedura C da B**:
   - Analogamente, quando B chiama C, LV e SP vengono nuovamente aggiornati per le variabili di C.
4. **Terminazione delle Procedure**:
   - Quando C termina, il controllo ritorna a B, e LV e SP vengono riportati allo stato precedente, permettendo a B di continuare l'esecuzione.
   - Quando B termina, il controllo ritorna ad A, riportando LV e SP allo stato iniziale di A.

Questo metodo permette di usare la memoria in modo efficiente, rilasciando lo spazio occupato dalle variabili locali non appena la procedura termina.
##### Uso dello Stack per Operazioni Aritmetiche
Oltre a memorizzare le variabili locali, lo stack può essere utilizzato come **stack degli operandi** per eseguire operazioni aritmetiche.
- **Esempio**: Calcolo di `a1 = a2 + a3` in procedura A:
  1. A inserisce `a2` nello stack, incrementando SP.
  2. A inserisce `a3` nello stack, incrementando nuovamente SP.
  3. Una istruzione preleva `a2` e `a3` dallo stack, li somma, e inserisce il risultato nuovamente nello stack.
  4. Il risultato viene prelevato dallo stack e memorizzato in `a1`.
#### Vantaggi dell'Uso dello Stack
- **Flessibilità**: Ogni chiamata di procedura ha il proprio blocco di variabili locali, evitando interferenze tra le chiamate.
- **Efficienza di Memoria**: La memoria viene allocata e rilasciata dinamicamente, a seconda delle necessità delle procedure attive.
- **Facilità di Implementazione delle Procedure Ricorsive**: Ogni chiamata ricorsiva ha il proprio contesto di esecuzione separato.
#### Considerazioni Finali
Mentre tutte le macchine utilizzano uno stack per memorizzare le variabili locali delle procedure, non tutte lo utilizzano per le operazioni aritmetiche. Tuttavia, macchine come la JVM e IJVM utilizzano uno stack degli operandi, il che dimostra la versatilità dello stack nella gestione della memoria e dell'esecuzione delle operazioni.

(pagine riassunte: 2.5)
### 4.2.2 - Modello della memoria di IJVM
#### Architettura di IJVM
L'architettura di IJVM è concepita in modo da separare chiaramente le diverse aree di memoria utilizzate durante l'esecuzione di un programma. Ecco una descrizione dettagliata delle diverse componenti e il loro funzionamento.
##### 4.2.2.1 - Memoria
La memoria in IJVM può essere vista come:
- **Array di 4.294.967.296 byte (4 GB)**
- **Array di 1.073.741.824 parole da 4 byte**
A differenza di molti altri ISA, IJVM utilizza puntatori e indirizzi impliciti per accedere alla memoria, il che consente una gestione più sicura e strutturata dei dati.
##### 4.2.2.2 - Aree di Memoria
**a. Porzione Costante di Memoria**
- **Contenuto**: Costanti, stringhe e puntatori ad altre aree di memoria.
- **Accesso**: Sola lettura (i programmi IJVM non possono scrivere in quest'area).
**b. Blocco delle Variabili Locali**
- **Funzione**: Memorizza le variabili locali di ogni metodo invocato.
- **Contenuto**: All'inizio di questo blocco sono memorizzati i parametri con cui è stato invocato il metodo.
- **Separazione**: Non comprende lo stack degli operandi.
**c. Stack degli Operandi**
- **Funzione**: Utilizzato per memorizzare gli operandi durante il calcolo delle espressioni aritmetiche e altre operazioni temporanee.
- **Dimensione**: Ha una dimensione massima stabilita in anticipo dal compilatore Java.
- **Registro Implicito**: Un registro contiene l'indirizzo della parola in cima allo stack.
**d. Area dei Metodi**
- **Contenuto**: Il codice del programma, organizzato come un array di byte.
- **Registro PC (Program Counter)**: Punta all'istruzione corrente da eseguire, espresso in byte.
##### 4.2.2.3 - Puntatori e Registri
**Puntatori a Parole**
- **CPP (Constant Pool Pointer)**: Punta alla costante di memoria.
- **LV (Local Variables Pointer)**: Punta alla base delle variabili locali del metodo corrente.
- **SP (Stack Pointer)**: Punta alla cima dello stack degli operandi.
**Indirizzi e Spiazzamenti**
- **Parole**: I registri come LV e SP sono puntatori a parole. Gli spiazzamenti sono espressi in numero di parole.
  - Esempio: LV, LV + 1 e LV + 2 fanno riferimento alle prime tre parole del blocco delle variabili locali.
  - Esempio: LV, LV + 4 e LV + 8 fanno riferimento a parole a intervalli di quattro parole (16 byte).
**Puntatore a Byte**
- **PC (Program Counter)**: Contiene un indirizzo espresso in byte.
  - Esempio: Incrementare PC di uno corrisponde a prelevare il byte successivo.
  - Esempio: Incrementare SP di uno corrisponde a prelevare la parola successiva.
#### Esempio di Funzionamento
1. **Invocazione di un Metodo**
   - Quando un metodo viene invocato, viene allocato un nuovo blocco di variabili locali nello stack.
   - LV viene aggiornato per puntare alla base di questo nuovo blocco.
2. **Esecuzione di Istruzioni**
   - Le istruzioni vengono prelevate dall'area dei metodi utilizzando il PC.
   - Le operazioni aritmetiche utilizzano lo stack degli operandi, con SP che punta alla cima dello stack.
3. **Chiusura di un Metodo**
   - Al termine dell'esecuzione di un metodo, lo stack viene aggiornato per rimuovere il blocco delle variabili locali.
   - LV e SP vengono riportati allo stato precedente.
4. **Esempio di Accesso a Variabili Locali**
   - Se una variabile locale deve essere accessibile, il registro LV viene utilizzato con uno spiazzamento.
   - Esempio: Per accedere alla prima variabile locale, si utilizza LV + 0; per la seconda variabile, LV + 1, e così via.
#### Conclusione
L'architettura di IJVM è progettata per gestire in modo efficiente la memoria durante l'esecuzione di programmi Java. Utilizzando puntatori a parole per variabili locali e stack degli operandi, e puntatori a byte per il codice dei metodi, IJVM garantisce una gestione sicura e strutturata della memoria, facilitando l'implementazione di linguaggi ad alto livello come Java.

(pagine riassunte: 1.5)
### 4.2.3 - Insieme d'istruzioni IJVM
La gestione delle istruzioni in IJVM, in particolare l'invocazione di metodi (`INVOKEVIRTUAL`) e il ritorno dai metodi (`IRETURN`), segue una sequenza precisa di operazioni per assicurare un corretto funzionamento. Qui di seguito è descritta nel dettaglio questa sequenza, con attenzione alle operazioni di push e pop dello stack, la gestione dei puntatori e la memorizzazione dei valori di ritorno.
#### Esecuzione dell'istruzione INVOKEVIRTUAL
Quando un metodo viene invocato utilizzando l'istruzione `INVOKEVIRTUAL`, avviene la seguente sequenza di operazioni:
1. **Preparazione dei Parametri**:
   - Il chiamante inserisce sullo stack un riferimento all'oggetto da chiamare (`OBJREF`).
   - Successivamente, vengono inseriti sullo stack i parametri del metodo, ad esempio `Parametro 1`, `Parametro 2`, `Parametro 3`, ecc.
2. **Codice Operativo e Spiazzamento**:
   - L'istruzione `INVOKEVIRTUAL` include uno spiazzamento che punta a una posizione nella porzione costante di memoria, dove è memorizzato l'indirizzo del metodo da invocare.
3. **Lettura dell'Area dei Metodi**:
   - Nei primi 4 byte dell'area dei metodi puntata, si trovano:
	 - Il numero di parametri del metodo (incluso `OBJREF` come parametro 0).
	 - La dimensione del blocco delle variabili locali necessario per il metodo.
4. **Calcolo del Nuovo Blocco delle Variabili Locali**:
   - L'indirizzo base del nuovo blocco delle variabili locali viene calcolato sottraendo il numero di parametri dal puntatore allo stack (`SP`).
   - Il registro `LV` viene impostato per puntare a `OBJREF`.
5. **Memorizzazione dei Puntatori**:
   - In `OBJREF` viene memorizzato l'indirizzo della locazione in cui si trova il vecchio `PC`.
   - Immediatamente sopra, viene memorizzato il vecchio `LV`.
6. **Impostazione del Nuovo Stack**:
   - Il nuovo stack per la procedura invocata inizia subito sopra il vecchio `LV`.
   - Il registro `SP` viene impostato per puntare al vecchio `LV`.
7. **Impostazione del Contatore di Programma (PC)**:
   - Infine, il registro `PC` viene impostato in modo da puntare al quinto byte nell'area del codice del metodo da eseguire.
#### Esecuzione dell'istruzione IRETURN
Quando il metodo termina, l'istruzione `IRETURN` inverte la sequenza di operazioni effettuate da `INVOKEVIRTUAL`. Ecco come:
1. **Accesso al Puntatore di Collegamento (Link Pointer)**:
   - L'istruzione `IRETURN` accede al puntatore di collegamento, che è la parola identificata dal puntatore `LV` corrente. Questo permette di ripristinare i puntatori `PC` e `LV` ai loro valori precedenti.
2. **Deallocazione dello Spazio Utilizzato**:
   - Lo spazio utilizzato dal metodo viene deallocato. Questo significa che `OBJREF` (ora sovrascritto) e tutti i parametri vengono estratti dallo stack.
3. **Gestione del Valore di Ritorno**:
   - Il valore di ritorno del metodo, memorizzato in cima allo stack, viene copiato nella locazione in cui era originariamente memorizzato `OBJREF`.
   - Il registro `SP` viene reimpostato per puntare a questa locazione.
4. **Restituzione del Controllo**:
   - Il controllo viene restituito all'istruzione immediatamente successiva a `INVOKEVIRTUAL`.

Questo meccanismo garantisce che il flusso del programma continui senza interruzioni e che i valori di ritorno siano correttamente gestiti, permettendo una gestione efficace delle chiamate e dei ritorni dai metodi.

(pagine riassunte: 4)
## 4.6 - Esempi del livello di microarchitettura
### 4.6.1 - Microarchitettura della CPU Core i7
Il Core i7 sembra un processore CISC tradizionale con un ampio set di istruzioni complesse, operazioni su interi a 8, 16 e 32 bit, e operazioni in virgola mobile a 32 e 64 bit. Le istruzioni variano in lunghezza da 1 a 17 byte e ci sono solo otto registri visibili.

Tuttavia, all'interno, il Core i7 utilizza un nucleo RISC moderno, semplice ed efficace con architettura pipeline. Questo consente una velocità di clock estremamente elevata, che continuerà probabilmente ad aumentare.

Questa dualità permette di combinare la ricchezza funzionale delle istruzioni CISC con l'efficienza e la velocità del nucleo RISC, garantendo compatibilità con software legacy e alte prestazioni per nuovi applicativi.
#### 4.6.1.1 - Descrizione della microarchitettura Sandy Bridge del Core i7
La microarchitettura Core i7, chiamata **Sandy Bridge**, rappresenta un notevole perfezionamento delle precedenti microarchitetture Intel, tra cui P6 e P4. È costituita da quattro parti principali: il sottosistema di memoria, il front end, il controllo dell'esecuzione fuori sequenza e le unità esecutive.
##### Sottosistema di Memoria
Ogni processore Core i7 include una cache L2 unificata e la logica per l'accesso alla cache L3. La cache L2 è di 256 KB, organizzata come cache associativa a 8 vie con linee da 64 byte. Tutti i processori condividono una cache L3, che varia da 1 a 20 MB. Se un accesso alla cache L3 fallisce, la richiesta viene inoltrata alla RAM esterna attraverso il bus DDR3.
##### Front End
Il front end preleva le istruzioni dal sottosistema di memoria, le decodifica in micro-operazioni RISC e le memorizza in due cache istruzioni. La cache L1 è di 32 KB. Le micro-operazioni decodificate alimentano la cache delle micro-operazioni (L0), che memorizza le micro-operazioni decodificate per evitare ulteriori decodifiche.
##### Predizione dei Salti
Il front end include meccanismi di predizione dei salti che migliorano le prestazioni monitorando i salti precedenti e utilizzando queste informazioni per fare previsioni future.
##### Esecuzione Fuori Sequenza
Le istruzioni vengono trasferite allo scheduler fuori-sequenza, che esegue le istruzioni non necessariamente nell'ordine originale, permettendo l'esecuzione parallela delle istruzioni pronte.
##### Unità Esecutive
Le unità esecutive processano istruzioni su interi, in virgola mobile e altre operazioni specializzate. Funzionano in parallelo, ottenendo i dati dall’insieme dei registri e dalla cache dati L1.

In sintesi, Sandy Bridge del Core i7 combina la complessità di una CISC con l'efficienza di un nucleo RISC, migliorando le prestazioni e l'efficienza energetica.

(pagine riassunte: 3)
#### 4.6.1.2 - Pipeline Sandy Bridge del Core i7

### 4.6.2 - Microarchitettura della CPU OMAP4430

### 4.6.3 - Microarchitettura del microcontrollore ATmega168


(pagine riassunte: )