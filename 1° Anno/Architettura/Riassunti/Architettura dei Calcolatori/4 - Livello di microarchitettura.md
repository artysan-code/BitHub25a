La progettazione della microarchitettura dipende non solo dall'ISA da implementare, ma anche dagli obiettivi di costo e prestazioni del calcolatore. Molti ISA moderni, specialmente le architetture RISC, includono istruzioni semplici eseguibili in un ciclo di clock. Invece, ISA più complessi come quello del Core i7 possono richiedere più cicli per eseguire un'istruzione, dovendo localizzare gli operandi in memoria, leggerli e memorizzare il risultato. Questa complessità comporta una strategia di controllo diversa rispetto agli ISA più semplici.

(pagine riassunte: 0.5)
## 4.1 - Esempio di microarchitettura
Ogni ISA è unico, quindi analizzeremo un esempio pratico dettagliato. Abbiamo scelto un sottoinsieme della Java Virtual Machine, chiamato **IJVM**, che contiene solo istruzioni su interi.

Per implementare IJVM, descriveremo la microarchitettura necessaria. Le architetture con istruzioni complesse spesso usano la microprogrammazione. Sebbene IJVM sia piccolo, è un buon punto di partenza per descrivere controllo e ordinamento delle istruzioni.

La nostra microarchitettura includerà un microprogramma in una ROM per prelevare, decodificare ed eseguire le istruzioni IJVM. Non useremo l'interprete Oracle JVM, scritto in C, perché non può controllare l'hardware. Invece, seguiremo un modello convenzionale: ogni istruzione ISA è una funzione richiamata dal programma principale, un ciclo infinito che determina, richiama e ripete le funzioni.

Il microprogramma ha variabili che rappresentano lo **stato** del calcolatore, cambiato da ogni funzione. Il _Program Counter_ (PC) è una di queste variabili e punta alla locazione di memoria della prossima istruzione da eseguire, avanzando durante l'esecuzione.

Le istruzioni IJVM sono semplici, composte da campi con il primo campo come **codice operativo** (opcode), identificando il tipo di istruzione (ADD, BRANCH, ecc.). Questo modello di esecuzione, chiamato **fetch-decodifica-esecuzione**, è utile e può essere la base per implementare ISA complessi come IJVM. Le microistruzioni formano il microprogramma, ciascuna controllando il percorso dati durante un ciclo.

(pagine riassunte: 1)
### 4.1.1 - Percorso dati
Il **percorso dati** della CPU include la ALU, i suoi input e output. Anche se ottimizzato per i programmi IJVM, è simile ai percorsi dati di altre macchine. Il nostro percorso dati ha registri a 32 bit, accessibili solo a livello di microarchitettura. La maggior parte dei registri può inviare il contenuto sul bus B, collegato all'input della ALU, il cui output guida lo _shifter_, che invia il risultato sul bus C. I valori del bus C possono essere scritti simultaneamente in uno o più registri. Al momento, non c'è un bus A.

Figura 4.1

La ALU è controllata da sei linee: $F_{0}$ e $F_{1}$ determinano l'operazione, ENA e ENB abilitano gli input, INVA inverte l'input sinistro e INC aggiunge un riporto al risultato. Non tutte le 64 combinazioni di controllo sono utilizzate. Queste funzioni saranno utili per l'intero insieme JVM. La ALU richiede due input: sinistro (A) e destro (B), con il bus B collegato a sinistra.

Un valore può essere caricato in H scegliendo una funzione della ALU che trasferisca l'input destro senza modificarlo. L'output della ALU è gestito da altre due linee di controllo: SLL8 trasla a sinistra di un byte, impostando a 0 gli 8 bit meno significativi, e SRA1 trasla a destra di un bit, mantenendo il bit più significativo.

È possibile leggere e scrivere lo stesso valore in un ciclo. Per incrementare SP di 1, si porta il valore di SP sul bus B, si disabilita l'input sinistro della ALU, si abilita INC e si memorizza il risultato in SP. Quando un registro è selezionato come input destro della ALU, i suoi valori vengono mantenuti sul bus B per tutto il ciclo. La ALU opera e il risultato arriva al bus C attraverso lo shifter. Alla fine del ciclo, un segnale di clock memorizza il contenuto del bus C in uno o più registri, che può essere lo stesso registro di input di B. Questa temporizzazione precisa permette di leggere e scrivere lo stesso registro in un ciclo.

(pagine riassunte: 3)
#### 4.1.1.1 - Temporizzazione del percorso dati
All'inizio di ogni ciclo di clock viene generato un breve impulso, sincronizzato con il clock principale. Al fronte di discesa dell'impulso, i bit di controllo delle porte logiche vengono impostati, operazione che richiede un tempo $\Delta w$. Successivamente, il registro selezionato invia il suo contenuto sul bus B, stabilizzandosi dopo un tempo $\Delta x$. A questo punto, la ALU e lo shifter operano sui dati, con output stabili dopo un tempo $\Delta y$. Dopo un ulteriore tempo $\Delta z$, i risultati si propagano lungo il bus C fino ai registri, che vengono caricati al fronte di salita dell'impulso successivo. Questo caricamento è rapido, garantendo che le modifiche degli input non influenzino immediatamente il bus C.

Figura 4.1

All'interno del percorso dati, c'è un tempo di propagazione anche senza elementi di memorizzazione. Il bus C non cambia immediatamente dopo una modifica del bus B. Quindi, anche se un'operazione di scrittura modifica un registro di input, il valore sarà reinserito in modo sicuro prima che il nuovo valore possa influenzare la ALU.

Per far funzionare questa architettura, è necessaria una temporizzazione rigida: un ciclo di clock lungo, un ritardo di propagazione della ALU noto e un caricamento veloce dei registri dal bus C. Con un'attenta progettazione, il percorso dati può funzionare correttamente in ogni momento, come accade nelle macchine reali.

Il ciclo del percorso dati può essere visto come diviso in sottocicli, con l'inizio del sottociclo 1 guidato dal fronte di discesa del clock:

1. Impostazione dei segnali di controllo ($\Delta w$)
2. Caricamento dei registri nel bus B ($\Delta x$)
3. Operazioni della ALU e dello shifter ($\Delta y$)
4. Propagazione dei risultati lungo il bus C e caricamento nei registri ($\Delta z$)

L'intervallo dopo $\Delta z$ ha una certa tolleranza. Al fronte di salita del ciclo successivo, i risultati sono memorizzati nei registri.

I sottocicli non sono definiti esplicitamente, poiché nessun impulso di clock segnala alle ALU e allo shifter di funzionare continuamente; i loro input sono inconsistenti fino a $\Delta w+\Delta x$ dopo il fronte di discesa del clock, e i loro output sono inconsistenti fino a $\Delta w+\Delta x+\Delta y$. È responsabilità dell'ingegnere progettista assicurarsi che $\Delta w+\Delta x+\Delta y+\Delta z$ sia sufficientemente breve rispetto al fronte di salita del clock, garantendo il corretto caricamento dei registri.

(pagine riassunte: 2)
#### 4.1.1.2 - Operazioni della memoria
La nostra macchina ha due modalità di comunicazione con la memoria: una porta a 32 bit con indirizzi espressi in parole e una porta a 8 bit con indirizzi espressi in byte. La porta a 32 bit è controllata dai registri MAR (Memory Address Register) e MDR (Memory Data Register), mentre la porta a 8 bit è controllata dal registro PC, che legge un byte negli 8 bit meno significativi di MBR. La porta a 8 bit può solo leggere dati dalla memoria.

Ogni registro è controllato da uno o due **segnali di controllo**. Una freccia bianca sotto un registro indica un segnale di controllo che abilita l'output del registro verso il bus B. Una freccia nera indica un segnale di controllo che scrive nel registro un valore proveniente dal bus C. Per iniziare una lettura o una scrittura, bisogna caricare il registro di memoria appropriato e inviare un segnale di scrittura alla memoria.

Le due modalità di accesso sono necessarie perché MAR e PC si riferiscono a diverse parti della memoria. MAR/MDR sono utilizzati per leggere e scrivere parole di dati a livello ISA, mentre PC/MBR leggono il programma eseguibile a livello ISA, un flusso di byte.

Nelle implementazioni reali, esiste una sola memoria orientata al byte. MAR conta il numero di parole anche se gli indirizzi sono espressi in byte. Quando MAR viene portato sul bus degli indirizzi, i suoi 32 bit non sono mappati direttamente sulle 32 linee. I 2 bit più alti di MAR vengono scartati perché inutili per la nostra macchina, che ha un limite di indirizzamento di 4 GB. Così, quando MAR vale 1, sul bus viene posto l'indirizzo 4; quando MAR vale 2, l'indirizzo 8, e così via.

Per convertire il registro MBR a 8 bit in una parola a 32 bit, si tratta il valore con segno compreso tra -128 e +127, utilizzando un processo chiamato **estensione del segno**. Questo consiste nel duplicare il bit del segno di MBR nei 24 bit più alti del bus B. La scelta tra convertire gli 8 bit di MBR in un valore a 32 bit con o senza segno è determinata dal segnale di controllo. La presenza delle due frecce giustifica la necessità di distinguere tra queste due opzioni.

(pagine riassunte: 2)
### 4.1.2 - Microistruzioni

### 4.1.3 - Unità di controllo microprogrammata: Mic-1

## 4.2 - Esempio di ISA: IJVM
### 4.2.1 - Stack

### 4.2.2 - Modello della memoria di IJVM

### 4.2.3 - Insieme d'istruzioni IJVM

### 4.2.4 - Compilazione da Java a IJVM

## 4.6 - Esempi del livello di microarchitettura
### 4.6.1 - Microarchitettura della CPU Core i7

### 4.6.2 - Microarchitettura della CPU OMAP4430

### 4.6.3 - Microarchitettura del microcontrollore ATmega168


(pagine riassunte: )