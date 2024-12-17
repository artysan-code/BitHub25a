### Tipo di dato vs Struttura Dati
Un **tipo di dato** è una specifica collezioni di oggetti e di operazioni eseguibili su di essi (Es. dizionario mantiene un insieme di elementi con chiavi associate per op. di inserimento, cancellazione e ricerca).

Una **struttura dati** è, invece, un'organizzazione dei dati che permette di memorizzare la collezione e supportare operazioni di un tipo di dato usando meno risorse di calcolo possibili.

Per progettare una struttura dati bisogna poter eseguire efficientemente le seguenti operazioni:
- Dato un array A, generare velocemente H
- Trovare il più grande oggetti in H
- Cancellare il più grande oggetto da H
### Heap Sort
Ha lo stesso approccio incrementale del Selection-Sort, seleziona gli elementi dal più grande al più piccolo usando una **struttura di dati efficiente** (estrazione in tempo $O(\log(n))$ massimo.

Per questo usiamo la struttura dati **heap** associata ad un insieme S, cioè un albero binario radicato con le seguenti proprietà:
- Completo fino al penultimo livello (struttura rafforzata, sull'ultimo livello tutte sono compattate a sinistra).
- Gli elementi di S sono memorizzati nei nodi dell'albero, ogni nodo memorizza un solo elemento, denotato con chiave (v).
- $chiave(padre(v)) \geq chiave(v)$ per ogni nodo v diverso dalla radice.

Un heap ha le seguenti **proprietà salienti**:
- Il massimo è contenuto nella radice.
- L'albero con n nodi ha altezza $O(\log(n))$.
- Grazie alla struttura rafforzata può essere rappresentato tramite un array di dimensione n.

Rispettando quindi tutte queste proprietà, l'heap ottiene le seguenti relazioni (i è la posizione dell'elemento da relazionare):
- Il **figlio sinistro** di un elemento è in posizione $2i$.
- Il **figlio destro** di un elemento è in posizione $2i + 1$.
- Il **padre** di un elemento si trova in $\left\lfloor  \frac{i}{2}  \right\rfloor$.

Il vettore che lo rappresenta generalmente è più grande del numero di elementi (che scriviamo nello pseudo-codice come $heapsize[A]$), perlopiù il primo di solito contiene la grandezza dell'heap
#### Funzione Fix-Heap
Data v la radice dell'Heap, si assume che i sotto alberi destri e sinistri siano heap, ma la proprietà di ordinamento delle chiavi non vale.
> $\text{fixHeap}(nodo\ v,\ heap\ H)$
> 1.   $\text{if }(\text{v non è una foglia})\text{ then}$
> 2.     $\text{sia u il figlio di v con chiave massima}$ 
> 3.     $\text{if }(chiave(v) < chiave(u))\text{ then}$
> 4. 		$\text{scambia chiave(v) con chiave(u)}$
> 5.          $\text{fixHeap}(u,\ H)$

L'algoritmo non fa altro che spostare le chiavi che non rispettano l'heap verso il basso, con la chiave del figlio con valore minore. Essendo che nel caso peggiore deve spostare v alla fine dell'albero, dovrà fare almeno $O(\log(n))$ operazioni di spostamento, che valgono ciascuna $O(1)$. Quindi in totale la complessità è $O(\log(n))$.

Questa funzione può essere chiamata **solo se vi è una anomalia nella radice**, ma gli alberi destri e sinistri **devono essere heap**.
#### Estrazione del massimo
Per estrarre il massimo devo:
- Copiare nella radice la chiave contenuta nella foglia più a destra (quindi nell'ultimo elemento dell'heap che si trova alla grandezza dell'heap).
- Rimuovi la foglia (quindi decrementiamo la grandezza dell'heap)
- Ripristiniamo l'ordinamento tramite fixHeap sulla radice
#### Costruzione dell'Heap (Heapify)
Heapify
#### Complessità Heapify
Data h l'altezza di un heap con n elementi e sia $n^{'} \geq n$ l'intero tale che un heap con $n^{'}$ elementi ha:
- altezza h
- è completo fino all'ultimo livello

Vale quindi che:$$T(n) \leq T(n^{'})\quad n^{'} \leq 2n$$
Quindi il tempo di esecuzione è:$$T(n^{'})=2T\left( \frac{n^{'}-1}{2} \right)+O(\log(n^{'}))\leq 2T\left( \frac{n^{'}}{2} \right)+ O(\log(n^{'}))$$
Dal teorema master possiamo dire che $T(n')=O(n^{'})$ e quindi:$$T(n) \leq T(n^{'})=O(n^{'})=O(2n)=O(n)$$
#### Max-Heap e Min-Heap
Se volessimo una struttura dati che tira fuori velocemente il minimo dell'heap invece che il massimo, basterebbe semplicemente invertire la proprietà di ordinamento delle chiavi così che:$$chiave(padre(v))\leq chiave(v)\quad\quad \forall\ v\ diverso\ dalla\ radice$$
E perché abbiamo progettato un max-heap e non un min-heap?
#### HeapSort
Il codice finale, unendo tutte le funzioni precedente, rispetta i seguenti step:
- Costruiamo un heap tramite heapify.
- Estraiamo ripetutamente il massimo per n-1 volte. Memorizziamo il massimo nella posizione appena liberata.

Quindi lo pseudo-codice è il seguente:
```
heapSort(A)
1. heapify(A)
2. heapsize[A] = n
3. for i=n down to 2 do
	1. scambia A[1] e A[i]
	2. heapsize[A] = heapsize[A] - 1
	3. fixHeap(1, A)
```

Ordina in loco $O(n\cdot \log(n))$
