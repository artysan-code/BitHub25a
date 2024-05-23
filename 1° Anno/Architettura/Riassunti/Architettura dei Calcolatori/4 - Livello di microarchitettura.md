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
#### 4.1.1.1 - Temporizzazione del percorso dati

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