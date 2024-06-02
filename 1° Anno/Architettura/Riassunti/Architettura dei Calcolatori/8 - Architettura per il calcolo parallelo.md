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
Quando un riferimento di memoria fallisce nella prima e nella seconda cache, la CPU deve attendere che i dati necessari vengano recuperati dalla memoria principale. Questo intervallo di attesa rappresenta uno spreco di tempo per la CPU. Per ovviare a questo problema, esistono diversi metodi di **multithreading nel chip** che permettono di mantenere la CPU occupata su un secondo thread mentre attende i dati per il primo.

Il primo approccio è chiamato **multithreading a grana fine**. In questo metodo, per utilizzare al massimo l'hardware, si usa un rapido cambio di contesto. I gruppi di thread (cioè gruppi di processi che devono essere eseguiti in una determinata sequenza) vengono eseguiti ciclicamente. Questo approccio è illustrato nel libro a pagina 570, figura 8.7 a-b-c-d.

Il secondo approccio è il **multithreading a grana grossa**, che opera in modo speculare rispetto al precedente. In questo caso, il cambio di contesto avviene ad ogni stallo del thread. Sebbene sia meno efficiente del multithreading a grana fine, se implementato con un algoritmo che prevede possibili stalli, può cambiare contesto in modo efficiente, mantenendo la CPU occupata con un numero ridotto di thread.

Un ulteriore vantaggio del multithreading a grana grossa è la possibilità di svuotare la pipeline ad ogni commutazione, mantenendo così l'identità del thread chiara e riducendo il rischio di confusione tra thread durante il cambio di contesto. Questo è particolarmente utile nei processori che emettono un numero maggiore di istruzioni.

Esiste anche un terzo metodo chiamato **multithreading simultaneo**. In questo approccio, ciascun thread emette due istruzioni e, in caso di stallo, si verifica un cambio di contesto verso il thread successivo. Questo metodo è un miglioramento del multithreading a grana grossa ed è considerato il più efficiente per i processori moderni.
#### Hyperthreading nel Core i7
Un'applicazione pratica del principio di multithreading si trova nei processori Intel, che durante la produzione del Pentium 4 furono progettati per supportare un principio di multithreading chiamato **hyperthreading** (il primo vero processore a implementarlo fu lo Xeon del 2002).

A livello fisico, diventava sempre più difficile migliorare l'hardware: aggiungere core, moduli, aumentare la frequenza del clock e allungare la pipeline portavano tutti a inefficienze termiche, di architettura e di predizione delle istruzioni. Il multithreading, invece, migliorava le prestazioni del processore del 25% aumentando solo del 5% la superficie del chip.

Il principio alla base dell'hyperthreading è eseguire due thread contemporaneamente, in modo simile ad avere due processori con memoria e cache condivisa. Proprio per questa condivisione, Intel ha identificato diversi metodi per la gestione logica dei thread, che ora vediamo:
- **Condivisione ripartita delle risorse**: Le risorse hardware e gli intervalli di esecuzione vengono divisi equamente in maniera forzata, evitando così che i thread entrino in conflitto.
- **Condivisione totale delle risorse**: L'opposto del metodo precedente, senza un algoritmo di selezione, in cui il primo thread che arriva utilizza tutte le risorse disponibili. Se un thread riempie le risorse, la coda di attesa dei thread successivi si riempie e il thread principale rischia di non avere più spazio per le risorse successive.
- **Condivisione a soglia**: Un thread può acquisire risorse dinamicamente, ma senza superare 3/4 della coda di attesa. In questo modo, un thread lento e uno veloce possono essere eseguiti in autonomia senza bloccarsi a vicenda (evitando il fenomeno dello starving).
- **Duplicazione delle risorse**: Poiché le risorse hardware devono essere maggiori per eseguire due thread contemporaneamente, i metodi di condivisione implicano un principio di duplicazione.

Le modalità utilizzate vengono selezionate dinamicamente a seconda della situazione per rendere più efficiente ogni casistica (per ulteriori dettagli, vedere l'esempio nella figura 8.9 del libro).

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