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
Il multithreading in alcuni ambiti non fornisce abbastanza performance. Proprio per questo una tecnologia che suscita tutt'ora interesse è quella del **multiprocessore in un chip**.
#### Multiprocessori Omogenei in un solo chip
Questo metodo è principalmente utilizzato nei server farm che raggruppano molti server web. Vi sono due possibili implementazioni:
1. **Due pipeline con una sola CPU**: Questo approccio permette potenzialmente di raddoppiare il throughput. Consente la condivisione di alcune risorse, ma presenta una maggiore complessità di progettazione.
2. **Due core con una sola pipeline**: In questo caso, il core corrisponde a un grande circuito che comprende una CPU, un controller I/O e una cache, che può essere inserito in un chip in maniera modulare. Questo approccio è più semplice da implementare ed è attualmente utilizzato in molte architetture moderne che supportano più core (n core).
#### Multiprocessore a singolo chip Core i7
Un processore Core i7 presenta 4 o più core, dove ogni core è dotato di tre cache private: due di primo livello per istruzioni e dati, e una di secondo livello, unificata.

Il livello successivo della gerarchia è occupato dalla cache di livello 3, condivisa tra tutti i core, che si connette al livello sottostante tramite una **rete ad anello**. Una richiesta di comunicazione che entra nella rete viene trasmessa al nodo successivo, dove si verifica se la richiesta ha raggiunto il suo nodo di destinazione. Questo design consente una maggiore larghezza di banda, ma introduce anche una maggiore latenza.
#### Multiprocessori eterogenei in un solo chip
Tutte queste tecniche non sono applicabili in ogni ambito. Diversi dispositivi elettronici, come lettori CD, telefoni, e altri, necessitano di metodologie e applicativi differenti per rendere il prodotto ottimale per le prestazioni richieste.

Ad esempio, i telefoni cellulari richiedono un multiprocessore eterogeneo, concentrato sulla gestione modulo per modulo, a causa della varietà di funzioni che svolgono: telecamera, schermo, audio input e output, rete internet mobile e Wi-Fi, ecc. I dispositivi audiovisivi, invece, necessitano principalmente di moduli di memoria per elaborare grandi quantità di dati rapidamente.

Quali tecniche sono utilizzate per un processore eterogeneo? La gestione dei moduli (o core) è fondamentale. 

Si può utilizzare un semplice bus, che però diventa un collo di bottiglia per sistemi più grandi. In alternativa, si possono usare più bus o un sistema ad anello che attraversa tutti i core. Ogni passaggio viene gestito tramite un **token** che arbitra le comunicazioni tra i core (viene preso da un core e poi rilasciato nell'anello).

Un esempio di interconnessione nel chip di tipo eterogenea è il **CoreConnect** della IBM, che, a differenza del bus PCI, non presenta problemi di retrocompatibilità. È composto da tre bus:
- Un bus per il **processore**, veloce, sincrono e a pipeline con dati a 32, 64 e 128 bit, temporizzati a 66, 133 o 183 MHz. Ha una velocità massima di trasferimento di 23,4 Gbps, contro i 4,2 Gbps del PCI. La tecnologia a pipeline permette di trasferire diverse richieste da diversi core, ottimizzato per connettere core veloci e trasferire blocchi corti.
- Un bus per i **dispositivi I/O** più lenti, con interfaccia a 8, 16 e 32 bit, che può contenere non più di qualche centinaio di porte logiche. Ha una velocità massima di trasferimento di 300 Mbps.
- Un bus per i **registri di periferica**, molto lento, che serve esclusivamente per fare riferimento ai registri delle periferiche.

*(in questo capitolo chiedo un possibile secondo parere in quanto c'ho capito ben poco)*

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