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

(Pagine riassunte: 1.5)
### 8.1.2 - Multithreading nel chip
### 8.1.3 - Multiprocessori in un solo chip
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