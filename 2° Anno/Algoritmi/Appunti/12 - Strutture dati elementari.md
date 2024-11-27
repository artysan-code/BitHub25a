
### Tipo di Dato e Struttura di Dati
### Struttura dati Dizionario

^4be009

Riceve un insieme S di coppie (e, k), cioè valore-chiave,  e supporta le seguenti **operazioni**:
- **Insert**, aggiungere ad S una nuova coppia (e, k).
- **Delete**, cancella da S l'elemento con chiave k.
- **Search**, fornisce l'elemento nel dizionario con chiave k, se non esiste restituisce null.
#### Implementazione
Vi sono diverse tipologie di implementazioni, a seconda di come viene strutturata la lista delle chiavi
### Struttura dati Pila
Riceve una sequenza S di *n elementi* e supporta le seguenti operazioni:
- **isEmpty() -> result**, restituisce *true* se S è vuota e *false* altrimenti.
- **push(elem e)**, aggiunge *e* come ultimo elemento di S.
- **pop() -> elem**, toglie l'ultimo elemento di S e lo restituisce.
- **top() -> elem**, restituisce l'ultimo elemento di S senza toglierlo.
### Struttura dati Coda
Riceve una sequenza S di *n elementi* e supporta le seguenti operazioni:
- **isEmpty() -> result**, restituisce *true* se S è vuota e *false* altrimenti.
- **enqueue(elem e)**, aggiunge e come ultimo elemento di S.
- **dequeue() -> elem**, toglie da S il primo elemento e lo restituisce.
- **first() -> elem**, restituisce il primo elemento da S, senza toglierlo.
### Rappresentazione dei dati
Esistono due tipologie fondamentali di rappresentazione dei dati:
- **Rappresentazioni indicizzate**, che usano array e matrici e sfruttano l'indicizzazione di essi. Possiede vantaggi e svantaggi:
	- Gli indici delle celle di un array sono numeri consecutivi.
	- Non è possibile aggiungere nuove celle ad un array.
- **Rappresentazione collegate**, che usano i record (costituenti di base) collegati fra loro tramite puntatori. I record possono essere distrutti e creati dinamicamente. Anche questo possiede vantaggi e svantaggi:
	- Possiamo aggiungere e togliere un record a una struttura collegata
	- Gli indirizzi dei record non sono necessariamente consecutivi.

### Organizzazione gerarchica dei dati
Consiste nell'organizzazione dei dati in una gerarchia e delle relazioni tramite gli alberi. Ci sono diverse definizioni aggiuntive per gli [[|alberi]]:
- Il grado di un nodo è il numero dei suoi figli.
- u antenato di v se u è raggiungibile da v risalendo di padre in padre v discendente di u se u è un antenato di v.
![[l121.png]]

Come possiamo rappresentare un albero in maniera indicizzata? (Quindi con array)
##### Vettore dei padri
L'idea è di associare ad ogni cella l'informazione di un nodo e la posizione del padre, in un vettore almeno di dimensione n. Quindi una generica cella contiene l'informazione (info, parent) dove:
- Info è il contenuto informativo del nodo i
- Parent è l'indice nell'array del padre.

Quindi le operazioni di ricerca hanno i seguenti costi:
- Ricerca di un padre **O(1)** mentre ricerca di un figlio **O(n)**.
##### Vettore posizionale (da fare)

