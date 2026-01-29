> [!abstract] Introduzione
> Le **strutture dati** sono organizzazioni fondamentali per memorizzare e gestire dati in modo efficiente. Una buona scelta della struttura dati può migliorare drasticamente le prestazioni di un algoritmo.

### Tipi di dato e Strutture di Dati
> [!info] Definizioni fondamentali
> **Tipo di dato:** Una specifica collezione di oggetti e di operazioni eseguibili su di essi.
> - Esempio: un dizionario mantiene un insieme di elementi con chiavi associate per operazioni di inserimento, cancellazione e ricerca
>
> **Struttura dati:** Un'organizzazione dei dati che permette di memorizzare la collezione e supportare operazioni di un tipo di dato usando meno risorse di calcolo possibili.

**Obiettivi nella progettazione:**
Per progettare una **struttura dati efficiente** bisogna poter eseguire efficientemente le seguenti operazioni:
- Dato un array A, generare velocemente la struttura H
- Trovare il più grande oggetto in H
- Cancellare il più grande oggetto da H

---
### Heap e Heap Sort
> [!tip] Idea generale
> L'**Heap Sort** ha lo stesso approccio incrementale del Selection Sort: seleziona gli elementi dal più grande al più piccolo usando una **struttura di dati efficiente** (heap) che permette estrazione del massimo in tempo $O(\log(n))$.

#### Struttura dati Heap

> [!note] Prerequisiti: Alberi d-ari
> Un **albero d-ario** è un albero con al più d figli per ogni nodo. Un **albero binario** è quindi un albero 2-ario (due figli per nodo).
>
> Un albero d-ario è **completo** se tutti i nodi interni hanno esattamente d figli e le foglie sono tutte allo stesso livello.

**Definizione di Heap:**

Un **heap** associato ad un insieme S è un albero binario radicato con le seguenti proprietà:

1. **Struttura rafforzata:** Completo fino al penultimo livello, con l'ultimo livello compattato a sinistra
2. **Memorizzazione:** Gli elementi di S sono memorizzati nei nodi dell'albero, ogni nodo memorizza un solo elemento con una chiave
3. **Proprietà di ordinamento:** $chiave(padre(v)) \geq chiave(v)$ per ogni nodo v diverso dalla radice

> [!success] Proprietà salienti dell'Heap
> - Il **massimo** è sempre contenuto nella radice
> - Un albero con n nodi ha altezza $O(\log(n))$
> - Può essere rappresentato tramite un **array di dimensione n** grazie alla struttura rafforzata

**Rappresentazione indicizzata:**

Rispettando le proprietà dell'heap, possiamo usare un array dove la posizione $i$ contiene un elemento e valgono le seguenti relazioni:
- **Figlio sinistro** di $i$: posizione $2i$
- **Figlio destro** di $i$: posizione $2i + 1$
- **Padre** di $i$: posizione $\left\lfloor  \frac{i}{2}  \right\rfloor$

> [!note] Implementazione
> Il vettore che rappresenta l'heap è generalmente più grande del numero di elementi. La dimensione effettiva è indicata con $heapsize[A]$.

---
#### Funzione Fix-Heap

> [!tip] Scopo della funzione
> Ripristina la proprietà di ordinamento dell'heap quando c'è un'anomalia nella radice, assumendo che i sottoalberi destro e sinistro siano già heap validi.

**Pseudo-codice:**
> $\text{fixHeap}(nodo\ v,\ heap\ H)$
> 1.    $s=sin(i)$
> 2.     $d=des(i)$
> 3.     $\textbf{if }(s\leq heapsize[A]\text{ e }A[s]>A[i]) \textbf{ then }massimo=s$
> 4.     $\textbf{else }massimo=i$
> 5.     $\textbf{if }(d\leq heapsize[A]\text{ e }A[d]>A[massimo]) \textbf{ then }massimo=d$
> 6.     $\textbf{if }(massimo\not=i)$
> 7.         $\textbf{then }\text{scambia }A[i]\text{ e }A[massimo]$
> 8.            $fixHeap(massimo,\ A)$

**Come funziona:**

L'algoritmo sposta verso il basso le chiavi che non rispettano la proprietà di heap, scambiandole con il figlio di valore maggiore.

**Complessità:**
Nel caso peggiore deve spostare il nodo fino alla fine dell'albero, eseguendo $\log(n)$ operazioni, ciascuna di costo $O(1)$.

> [!success] Complessità temporale
> $$T(n) = O(\log(n))$$

> [!warning] Precondizione
> Questa funzione può essere chiamata **solo se** i sottoalberi destro e sinistro sono già heap validi.

---
#### Estrazione del massimo

> [!tip] Procedura di estrazione
> Operazione fondamentale per estrarre l'elemento con chiave massima dall'heap mantenendo la proprietà di heap.

**Passi dell'algoritmo:**
1. **Sostituisci la radice:** Copia nella radice la chiave contenuta nella foglia più a destra (ultimo elemento dell'heap)
2. **Rimuovi la foglia:** Decrementa $heapsize[A]$ per rimuovere l'ultima foglia
3. **Ripristina l'heap:** Chiama $fixHeap$ sulla radice per ripristinare la proprietà di ordinamento

> [!info] Complessità
> L'operazione richiede tempo $O(\log(n))$ dovuto alla chiamata di fixHeap.

---
#### Costruzione dell'Heap (Heapify)

> [!tip] Tecnica utilizzata: Divide et Impera
> Costruiamo un heap valido da un array arbitrario usando la strategia divide et impera.

**Pseudo-codice:**
> $heapify(\text{heap\ H})$
> 1.  $\textbf{if}(\text{H non è vuoto})\textbf{ then}$
> 2.   $heapify(\text{sottoalbero sinistro di H})$
> 3.   $heapify(\text{sottoalbero destro di H})$
> 4.   $fixHeap(\text{radice di H, H})$

**Strategia:**
- **Dividi:** Considera ricorsivamente i sottoalberi sinistro e destro
- **Risolvi:** Trasforma ricorsivamente i sottoalberi in heap
- **Combina:** Usa fixHeap sulla radice per completare l'heap

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
#### Complessità Heapify

**Analisi:**

Data $h$ l'altezza di un heap con $n$ elementi e sia $n^{'} \geq n$ l'intero tale che un heap con $n^{'}$ elementi ha:
- altezza $h$
- è completo fino all'ultimo livello

Vale quindi che:
$$T(n) \leq T(n^{'})\quad \text{dove}\quad n^{'} \leq 2n$$

Il tempo di esecuzione è:
$$T(n^{'})=2T\left( \frac{n^{'}-1}{2} \right)+O(\log(n^{'}))\leq 2T\left( \frac{n^{'}}{2} \right)+ O(\log(n^{'}))$$

**Applicando il Teorema Master:**

Dal teorema master possiamo dire che $T(n')=O(n^{'})$ e quindi:
$$T(n) \leq T(n^{'})=O(n^{'})=O(2n)=O(n)$$

> [!success] Complessità temporale di Heapify
> $$T(n) = O(n)$$
> Sorprendentemente, costruire un heap da zero richiede tempo **lineare**!

---
#### Max-Heap e Min-Heap

> [!info] Varianti dell'Heap
> Esistono due varianti principali della struttura heap, a seconda dell'elemento che si vuole estrarre rapidamente.

**Max-Heap (visto finora):**
- Proprietà: $chiave(padre(v)) \geq chiave(v)$ per ogni nodo v diverso dalla radice
- Il massimo è nella radice

**Min-Heap:**
- Proprietà: $chiave(padre(v)) \leq chiave(v)$ per ogni nodo v diverso dalla radice
- Il minimo è nella radice

> [!question] Perché usiamo un Max-Heap per HeapSort?
> Perché tramite l'HeapSort con Max-Heap possiamo ordinare **in loco** con memoria costante, posizionando il massimo estratto alla fine dell'array.

---
#### HeapSort

> [!tip] Algoritmo completo
> L'**HeapSort** combina tutte le operazioni viste per creare un algoritmo di ordinamento efficiente che ordina in loco.

**Strategia:**
1. Costruiamo un heap tramite heapify
2. Estraiamo ripetutamente il massimo per n-1 volte
3. Memorizziamo ogni massimo estratto nella posizione appena liberata (dalla destra verso sinistra)

**Pseudo-codice:**
> $heapSort(A)$
> 1.  $heapify(A)$
> 2.  $heapsize[A] = n$
> 3.  $\textbf{for } i=n\text{ down to 2} \textbf{ do}$
> 4.    $\text{scambia }A[1]\text{ e }A[i]$
> 5.    $heapsize[A] = heapsize[A] - 1$
> 6.    $fixHeap(1, A)$

**Complessità:**
- Heapify: $O(n)$
- n-1 estrazioni, ciascuna $O(\log n)$: $O(n \log n)$

> [!success] Caratteristiche di HeapSort
> - **Complessità:** $O(n\cdot \log(n))$ nel caso peggiore
> - **Ordinamento in loco:** usa memoria costante $O(1)$
> - **Non stabile:** non preserva l'ordine relativo di elementi con chiavi uguali

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---

### Rappresentazione dei dati
> [!info] Paradigmi di rappresentazione
> La rappresentazione dei dati, quindi il modo in cui vengono salvati, rappresenta una grande svolta in molte situazioni.
> 
> Esistono due approcci fondamentali per rappresentare strutture dati in memoria, ciascuno con caratteristiche, vantaggi e svantaggi specifici.

#### Rappresentazioni indicizzate
**Caratteristiche:**
- Usano **array e matrici** sfruttando l'indicizzazione diretta
- Gli indici delle celle sono numeri consecutivi
- Accesso in tempo costante $O(1)$ tramite indice

**Vantaggi:**
- Accesso molto rapido agli elementi
- Semplicità di implementazione
- Cache-friendly (località spaziale)

**Svantaggi:**
- **Dimensione fissa:** non è possibile aggiungere nuove celle ad un array
- Spreco di memoria se la dimensione è sovrastimata
- Inserimento/cancellazione costosi (richiedono spostamenti)

---
#### Rappresentazioni collegate

**Caratteristiche:**
- Usano **record collegati** tramite puntatori
- I record possono essere creati e distrutti dinamicamente
- Gli indirizzi in memoria non sono necessariamente consecutivi

**Vantaggi:**
- **Dimensione dinamica:** possiamo aggiungere e togliere record facilmente
- Inserimento/cancellazione efficienti in posizioni note
- Uso efficiente della memoria (alloca solo ciò che serve)

**Svantaggi:**
- Accesso sequenziale più lento
- Overhead di memoria per i puntatori
- Minore località spaziale (peggiore per la cache)

---
### Struttura dati Dizionario

^4be009

> [!info] Tipo di dato astratto
> Un **dizionario** è una struttura dati che mantiene un insieme S di coppie (elemento, chiave) e permette operazioni di inserimento, ricerca e cancellazione basate sulle chiavi.

**Operazioni fondamentali:**
- **Insert(e, k):** Aggiunge ad S una nuova coppia (elemento e, chiave k)
- **Delete(k):** Cancella da S l'elemento con chiave k
- **Search(k):** Restituisce l'elemento nel dizionario con chiave k, oppure null se non esiste

Vi sono diverse tipologie di implementazioni, a seconda di come viene strutturata la collezione e ciascuna ha i suoi costi:
- Il metodo più semplice è **l'array non ordinato** dove le operazioni sono organizzate nella seguente maniera:
	- $\text{Insert}\implies O(1)$
	- $\text{Search}\implies O(n)$
	- $\text{Delete}\implies O(n)$
- Abbiamo l'implementazione con **l'array ordinato** che però, a causa della struttura dell'array, ha praticamente gli stessi costi del primo (se non peggiori):
	- $\text{Insert}\implies \text{Search + Spostamento}\implies O(\log(n))+O(n)\implies O(n)$
	- $\text{Search}\implies \text{Ricerca Binaria}\implies O(\log (n))$
	- $\text{Delete}\implies O(n)$
- Con le liste la situazione si stabilizza, soprattutto con **la lista non ordinata**:
	- $\text{Insert}\implies O(1)$
	- $\text{Search}\implies O(n)$
	- $\text{Delete}\implies O(n)$
- Mentre per **la lista ordinata** abbiamo la problematica di doverla mantenere ordinata e non poter usare la **Ricerca Binaria**. Ricordare che la ricerca binaria sfrutta gli indici che non sono disponibili in una rappresentazione a liste concatenate:
	- $\text{Insert}\implies O(n)$
	- $\text{Search}\implies O(n)$
	- $\text{Delete}\implies O(n)$

> [!note] Implementazione
> Le implementazioni complete delle varie strutture sono disponibili in `/Esercizi/`

---
### Struttura dati Pila (Stack)

> [!info] Tipo di dato astratto
> Una **pila** (stack) è una struttura dati che gestisce una sequenza di elementi seguendo la politica **LIFO** (Last In, First Out): l'ultimo elemento inserito è il primo ad essere estratto.

**Operazioni fondamentali:**
- **isEmpty() → boolean:** Restituisce `true` se S è vuota, `false` altrimenti
- **push(elem e):** Aggiunge e come ultimo elemento di S (in cima alla pila)
- **pop() → elem:** Rimuove l'ultimo elemento di S e lo restituisce
- **top() → elem:** Restituisce l'ultimo elemento di S senza rimuoverlo

**Applicazioni tipiche:**
- Gestione della ricorsione
- Valutazione di espressioni
- Backtracking negli algoritmi
- Navigazione della cronologia (es. "indietro" nel browser)

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
### Struttura dati Coda (Queue)

> [!info] Tipo di dato astratto
> Una **coda** (queue) è una struttura dati che gestisce una sequenza di elementi seguendo la politica **FIFO** (First In, First Out): il primo elemento inserito è il primo ad essere estratto.

**Operazioni fondamentali:**
- **isEmpty() → boolean:** Restituisce `true` se S è vuota, `false` altrimenti
- **enqueue(elem e):** Aggiunge e come ultimo elemento di S (in coda)
- **dequeue() → elem:** Rimuove il primo elemento di S e lo restituisce
- **first() → elem:** Restituisce il primo elemento di S senza rimuoverlo

**Applicazioni tipiche:**
- Gestione di processi e task scheduling
- Buffer per I/O
- Algoritmi di visita in ampiezza (BFS)
- Gestione di richieste in sistemi distribuiti

> [!note] Implementazione
> L'implementazione completa è disponibile in `/Esercizi/`

---
### Organizzazione gerarchica dei dati

> [!info] Alberi come strutture gerarchiche
> L'organizzazione **gerarchica** dei dati usa gli **alberi** per rappresentare relazioni padre-figlio tra elementi. Questa struttura è fondamentale per molti algoritmi e applicazioni.

**Definizioni aggiuntive per gli alberi:**
- **Grado di un nodo:** il numero dei suoi figli
- **Antenato:** u è antenato di v se è raggiungibile da v risalendo di padre in padre
- **Discendente:** v è discendente di u se u è un antenato di v

**Visualizzazione:**
![](assets/l121.png)

---
#### Rappresentazioni indicizzate di alberi

> [!question] Come rappresentare un albero con array?
> Esistono diverse strategie per rappresentare alberi usando array, ciascuna con trade-off diversi tra spazio e tempo.

##### Vettore dei padri

**Idea:**
Associamo ad ogni cella l'informazione di un nodo e la posizione del padre, usando un vettore di dimensione n.

**Struttura:**
Una generica cella contiene la coppia `(info, parent)` dove:
- **info:** il contenuto informativo del nodo i
- **parent:** l'indice nell'array del padre

**Complessità delle operazioni:**
- Ricerca di un **padre:** $O(1)$
- Ricerca di un **figlio:** $O(n)$

> [!success] Uso ottimale
> Questa rappresentazione è efficiente quando le operazioni più frequenti richiedono di risalire l'albero verso la radice.

---
##### Vettore posizionale

> [!warning] Da completare
> Questa sezione richiede ulteriori approfondimenti.

> [!note] Implementazioni
> Le implementazioni complete delle strutture ad albero sono disponibili in `/Esercizi/`
