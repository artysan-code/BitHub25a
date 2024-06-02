Le industrie, siano esse scientifiche, fisiche o mediche, richiedono agli ingegneri potenze di calcolo strabilianti che, a causa dei **limiti fisici** (come la velocità della luce e gli atomi), non possono essere raggiunte con le tecnologie tradizionali.

Per questo motivo, in questa epoca si sta cercando di ottimizzare il **parallelismo** per permettere di elaborare una quantità elevata di istruzioni in un intervallo di tempo ridotto. Esistono diversi livelli di parallelismo, ma verranno trattati tutti in maniera adeguata nei capitoli successivi.

Generalmente, però, infrastrutture con **multicomputer** o **multiprocessori** possono essere **legati strettamente** (elevata larghezza di banda e ritardo trascurabile) o **legati debolmente** (bassa larghezza di banda e ritardo notevole, svolgono i calcoli in modo poco interattivo).

(Pagine riassunte: 2)
## 8.1 - Parallelismo nel chip
Tratteremo generalmente il parallelismo interno al chip, nelle sue maniere più astratte come quello a livello di istruzioni, fino alla coabitazione di CPU nello stesso chip.
### 8.1.1 - Parallelismo a livello di istruzioni
I due principali tipi di parallelismo a livello di istruzioni sono i seguenti:
- **Processori superscalari**: Questi processori dispongono di un hardware particolare che consente di emettere più istruzioni simultaneamente verso l'unità di esecuzione. Tuttavia, il loro utilizzo è limitato dai costi elevati dovuti alla complessità dell'hardware necessario.
- **Processori VLIW (Very Long Instruction Word)**: Come suggerisce il nome, questi processori eseguono istruzioni molto lunghe (fino a 136 bit), che possono contenere diverse operazioni per le varie unità funzionali. Tuttavia, risultano poco flessibili poiché è difficile utilizzare appieno tutte le unità funzionali con ogni istruzione. Nei calcolatori moderni, si adotta un principio di **pacchetto**, determinato da un **marcatore di pacchetto**, che equivale effettivamente a un blocco di istruzioni da eseguire. Questo approccio consente al programmatore di stabilire quali istruzioni eseguire prima e contemporaneamente, migliorando l'efficienza dell'esecuzione.

(Vi è la spiegazione del processore VLIW TriMedia, dubito possa servire)

(Pagine riassunte: 1.5)
### 8.1.2 - Multithreading nel chip
Quando un riferimento di memoria fallisce nella prima e nella seconda cache, bisogna attendere la richiesta in memoria dei dati necessari. Questo intervallo risulta uno spreco di tempo per la CPU, proprio per questo esistono diversi metodi di **multithreading nel chip** che permettono di tenere la CPU occupata su un secondo *thread* mentre attende i dati per il primo. 

Il primo approccio si chiama **multithreading a grana fine** dove per utilizzare al massimo l'hardware si usa un *cambio di contesto rapido*; le famiglie di thread (cioè gruppi di processi che necessitano di essere eseguiti nella maniera prefissata) vengono eseguite in maniera ciclica (Vedere es. sul libro pag. 570 fig. 8.7 a-b-c-d).

Il secondo invece si chiama **multithread a grana grossa** che impone un principio specchiato al precedente; viene eseguito il *cambio di contesto ogni stallo* ottenuto dal thread (vedere figura 8.7 e). Meno efficiente del precedente, ma se implementato con un giusto algoritmo che prevede possibili stalli, può direttamente cambiare contesto, sembrando così più vicino al precedente e preservando il suo principale obiettivo, cioè tenere la CPU occupata con *meno thread possibili*.

Un'altra ottima modalità del grana grossa è di poter svuotare la *pipeline* ad ogni commutazione, così da poter tenere sempre presente *l'identità del thread* (l'identità del thread è sconosciuta alla CPU e con diversi thread che eseguono cambio di contesto si può perdere). Ovviamente nel caso di processori a emissioni di istruzioni maggiori i precedenti metodi funzionano più velocemente.

Esiste però un terzo metodo chiamato **multithreading simultaneo** dove ciascun thread emette due istruzioni e in caso di stallo vi è un cambio di contesto verso il successivo thread. Corrisponde ad una miglioria del grana grossa, che sembra essere la più efficiente per i processori moderni.

#### Hyperthreading nel Core i7
Un applicazione effettiva di questo principio la troviamo nei processori intel che durante la produzione del Pentium quattro vennero progettati per supportare un principio di multithreading chiamato **hyperthreading** (Il primo vero processore ad averlo fu lo Xeon del 2002). 

A livello fisico oramai diventava difficile migliorare l'hardware: aggiungere core, moduli, migliorare il clock, aumentare la pipeline, portavano tutti a maggiore inefficiente termica, di architettura e di predizione delle istruzioni. Il multithreading migliorava il processore del 25% aumentando solo del 5% la superficie del chip.

Il principio alla base dell'hyperthreading è di eseguire due thread contemporaneamente, che risulta similmente ad avere due processori con memoria e cache condivisa. Proprio per questa condivisione, intel ha identificato dei metodi per la gestione logica dei thread che ora vediamo:
- Il primo è la **condivisione ripartita delle risorse**, dove le risorse hardware e gli intervalli di esecuzione vengono divisi equamente in maniera forzata, non mandando quindi i thread in conflitto.
- Il secondo è la **condivisone totale delle risorse**, l'opposto del precedente che però non ha un algoritmo di selezione, quindi il primo che arriva si serve da sé. Se un thread riempie le risorse utilizzate, la coda di attesa dei thread successivi si riempie e il thread principale rischia di non avere più spazio per le risorse successive.
- Il terzo è la **condivisione a soglia**, dove un thread può acquisire risorse dinamicamente ma senza superare 3/4 della coda di attesa. In questa maniera un thread lento e uno veloce verranno eseguiti in autonomia senza fermarsi (non entrare in *starving*).
- I precedenti implicano però anche un principio di **duplicazione** in quanto le risorse hardware devono essere maggiori per eseguire due thread thread contemporaneamente.

Le modalità utilizzate vengono selezionate dinamicamente a seconda della situazione per rendere più efficiente ogni casistica. (Per l'esempio fig. 8.9 sul libro)

(Pagine riassunte: 6.5)
### 8.1.3 - Multiprocessori in un solo chip


(Pagine riassunte: 6.25)
## 8.2 - Coprocessori
### 8.2.1 - Processori di rete
### 8.2.2 - Processori grafici
### 8.2.3 - Crittoprocessori
## 8.3 - Multiprocessori con memoria condivisa
### 8.3.1 - Multiprocessori e multicomputer a confronto
### 8.3.2 - Semantica della memoria
### 8.3.3 - Architetture di multiprocessori simmetrici UMA
### 8.3.4 - Multiprocessori NUMA
### 8.3.5 - Multiprocessori COMA
## 8.4 - Multicomputer a scambio di messaggi
### 8.4.1 - Reti d'interconnessione
### 8.4.2 - Massive Parallel Processors
### 8.4.3 - Cluster
### 8.4.4 - Software di comunicazione per multicomputer
### 8.4.5 - Scheduling
### 8.4.6 - Memoria condivisa a livello applicativo
### 8.4.7 - Prestazioni
## 8.5 - Grid Computing