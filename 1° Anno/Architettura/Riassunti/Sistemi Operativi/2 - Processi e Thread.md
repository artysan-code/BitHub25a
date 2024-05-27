## 2.4 - Scheduling
Generalmente in un computer multiprogrammato, abbiamo molteplici processi o thread che competono per ottenere la CPU nello stesso istante. L'elemento che sceglie su cosa lavorare in quell'istante si chiama **scheduler** ed utilizza un **algoritmo di scheduling**.

(Pagine riassunte: 0.5)
### 2.4.1 - Introduzione allo scheduling
Nei sistemi attuali, con diversi utenti e richieste, lo scheduler è un elemento fondamentale per ottimizzare le risorse e il tempo di esecuzione dei task.

Con l'avvento dei Personal Computer, la situazione si è evoluta in due modi:

- Quando l'utente utilizza funzioni singole. Ad esempio, in Word, l'utente scrive ma non può esportare contemporaneamente il file come PDF (anche se esiste il salvataggio automatico, non avviene simultaneamente alla scrittura).
- I computer sono diventati così veloci che spesso non sono gli utenti ad aspettare la risposta della CPU, ma il contrario (la CPU aspetta l'input dell'utente).

In questi casi, lo scheduler non è così fondamentale.

Tuttavia, in sistemi come i server di rete, dove molti processi richiedono la CPU contemporaneamente, lo scheduler deve non solo organizzare tutte le richieste, ma anche sfruttare al meglio la CPU.

(Pagine riassunte: 1)

#### Comportamento dei processi
Tracciando un grafico dei momenti di utilizzo della CPU e delle attese causate dall'I/O, noteremo che esistono situazioni in cui gli intervalli di carico della CPU sono più lunghi e separati da brevi intervalli di attesa I/O, e viceversa.

Gli intervalli lunghi di utilizzo della CPU con brevi attese I/O sono chiamati **CPU-bound** o **compute-bound**. Al contrario, gli intervalli brevi di utilizzo della CPU con lunghe attese I/O sono detti **I/O-bound**.

Attualmente, i casi di I/O-bound sono più comuni, poiché la velocità della CPU è migliorata più rapidamente rispetto alla tecnologia di storage.

(Pagine riassunte: 1)

#### Quando effettuare lo scheduling
Esistono diverse situazioni in cui ha senso eseguire lo scheduling:

- Quando viene creato un nuovo processo e bisogna scegliere se eseguire il processo padre o il processo figlio.
- Al termine di un processo, per decidere quale processo eseguire successivamente.
- Quando un processo, chiamato A, attende il risultato di un altro processo, chiamato B. Ad esempio, se A ha bisogno di B per continuare, lo scheduler dovrebbe eseguire B prima di A, anche se A è più importante. Tuttavia, lo scheduler spesso non dispone delle informazioni necessarie per applicare questa logica.
- Durante un interrupt I/O, che costringe lo scheduler a scegliere se continuare o cambiare il processo in esecuzione.

Esistono due tipi di algoritmi di scheduling:

- Gli algoritmi **non preemptive** eseguono un processo senza interromperlo forzatamente. Anche se si verificano interrupt del clock, il processo viene ripreso immediatamente dopo.
- Gli algoritmi **preemptive** eseguono un processo per un determinato periodo di tempo e, se non termina entro questo periodo, viene sospeso per lasciare spazio a un altro processo.

(Pagine riassunte: 1)
#### Categorie di algoritmi di scheduling
Per ogni tipologia di ambiente abbiamo diverse soluzioni e le categorizzeremo qui sotto riassumendo tutto il possibile.
##### Sistemi Batch
I sistemi batch sono sistemi in cui non vi è urgenza di risposta immediata e i processi non devono essere eseguiti in modo interattivo. Questi sistemi sono tipicamente utilizzati in contesti bancari o finanziari per eseguire enormi calcoli in maniera sequenziale. In tali contesti, la sequenza delle operazioni è ben definita e può essere eseguita in modo preciso senza necessità di interventi dinamici.

Gli algoritmi utilizzati per elaborare i sistemi batch sono i seguenti.

###### First-come, first-served
Si presenta come l'algoritmo più semplice. Presenta una coda di processi in stato pronto che vengono eseguiti in maniera sequenziale. Quando il job in esecuzione si blocca, viene eseguito il prossimo job in lista; quando torna pronto viene messo in coda alla lista.

In un algoritmo first-come first-served, un processo CPU-bound viene eseguito per 1 secondo alla volta, mentre molti processi I/O-bound richiedono molte letture dal disco per completare il lavoro. Il problema sorge quando il processo CPU-bound, dopo 1 secondo di esecuzione, richiede un blocco di disco. Durante l'attesa del blocco, tutti i processi I/O-bound iniziano le loro letture. Una volta ottenuto il blocco, il processo CPU-bound si esegue per altri 1 secondo, seguito rapidamente da tutti i processi I/O-bound. Questo può causare ritardi significativi nei processi I/O-bound, poiché devono attendere l'esecuzione del processo CPU-bound prima di poter procedere.

In conclusione, con l'algoritmo first-come first-served, ogni processo I/O-bound impiegherebbe 1000 secondi per completare le letture dal disco. Tuttavia, con un algoritmo di scheduling che preleva il processo CPU-bound ogni 10 millisecondi, i processi I/O-bound potrebbero completare il loro lavoro in soli 10 secondi anziché 1000. Questo avviene senza rallentare significativamente il processo CPU-bound, consentendo quindi un'efficienza molto maggiore nell'utilizzo delle risorse. 
###### Shortest job first
Quando nella coda di input si trovano parecchi job di pari importanza in attesa di essere avviati, lo scheduler preleva per primo il job più breve (**shortest job first**). Nel caso di quattro job con tempi di esecuzione rispettivamente di a, b, c e d, l'algoritmo shortest job first garantisce tempi di turnaround ottimali. Ad esempio, se consideriamo i job A, B, C e D con tempi di esecuzione di 8, 4, 4 e 4 minuti rispettivamente, l'esecuzione secondo shortest job first produce tempi di turnaround di 4, 8, 12 e 20 minuti, con una media di 11 minuti. Questo dimostra l'efficacia e l'ottimalità dell'algoritmo shortest job first nel minimizzare i tempi di turnaround.

L'algoritmo shortest job first è ottimale solo quando tutti i job sono disponibili contemporaneamente. Tuttavia, se i job arrivano in momenti diversi, potrebbe non essere la scelta migliore. Ad esempio, considerando cinque job con tempi di esecuzione e tempi di arrivo differenti, l'esecuzione nell'ordine di arrivo produce una media di 4.6, mentre eseguendo nell'ordine B, C, D, E e A si ottiene una media di 4.4. Questo dimostra che in certi contesti l'ordine di arrivo può influenzare l'efficacia dell'algoritmo.
###### Shortest remaining time
Una versione preemptive dell'algoritmo shortest job first è l'algoritmo **shortest remaining time next**. In questo schema, lo scheduler seleziona sempre il processo che richiederà il minor tempo per completare l'esecuzione. È necessario conoscere in anticipo il tempo di esecuzione dei processi. Quando arriva un nuovo job, il suo tempo totale viene confrontato con il tempo rimanente del processo attualmente in esecuzione. Se il nuovo job richiede meno tempo per terminare rispetto al processo attuale, quest'ultimo viene sospeso e il nuovo job viene avviato. Questo approccio consente ai lavori brevi di ottenere un servizio rapido.

##### Sistemi Interattivi

##### Sistemi Real-Time

(Pagine riassunte: 10)
