struttura di un algoritmo:
- idea
- descrizione + pseudo-codice
- analisi
	- correttezza/complessità:
		insieme di proprietà che combinate implicano correttezza o il bound

per prossime volte gruppi da 3-5 persone

si impara come scrivere la correttezza con 2 modi :
- scrivere correttezza di algoritmi nuovi
- studiare le correttezze degli algoritmi in classe

il delta i ti permette di chiudere in tempo n
e il delta i preso uno più grande non va bene

Obbiettivi principali corso:
- introduzione alla analisi e progettazione di algoritmi
- nozioni necessarie
- costruire una prima "tool box" per analizzare e progettare
- esempi illustri per problemi/algoritmi/strutture dati
- nozioni di calcolo
	- modello di calcolo RAM a costo uniforme
	- complessità nel caso peggiore (e caso medio)
	- notazione asintotica
- problemi per fare esperienza
	- Paperone
		- $\lfloor\log_{2} n\rfloor$ pesate, $\lceil \log_{2} n \rceil$ pesate
	- Fibonacci
		- F.b2    $O(\phi^{n})$
		- F.b3 & 4   $O(n)$
		- F.b6    $O(\log n)$
- altro strumento utile (equazioni di ricorrenza)
	Molto utili:
	- teorema master
	- metodo iterazione
	- albero della ricorsione
- problema ordinamento 
	- selection sort    $\Theta(n^{2})$
	- merge sort     $\Theta(n\log n)$
		- tecnica D&C
	- quick sort    $\Theta(n^{2})$, $\Theta(n\log n)$ caso medio
		- tecnica D&C diversa
	- quick sort random    $O(n\log n)$ con prob $\displaystyle\left( 1-\frac{1}{n^{10}} \right)$ 
		- ricorda caso medio $\neq$ caso random
	- Heap Sort    $O(n\log n)$
	- lower bound ordinamento per alg su confronti
		- $\Omega(n\log n)$ confronti nel caso peggiore
	- integer sort (bucket sort)    $O(n+k)$
	- radix sort    $O(n)$ se $k=O(n^{c})$ 
- ??? alberi e visite
	- visita ampiezza BFS
	- visita profondità DFS
	- utilizzati per calcolare inf su alberi
- problemi dizionario
	- tipo di dato vs struttura dato 
	- BST    $O(h)\to$ AVL    $O(\log n)$
- problema coda con priorità
	- d-heap
	- heap binomiali
		- merge    $O(\log n)$
	- heap di Fibonacci (complessità)
		- DK    $O^{*}(1)$
	- complessita ammortizata
- grafi 
	- rappresentazione in memoria
	- matrici di adiacenza vs liste di adiacenza
		- $\Theta(n^{2})$ vs $O(n+m)$
	- visita BFS
		- calcolo  ShortestPathThree/ distanza singolo ???  (grafi non pesati)
	- visita DFS
		- trovare ordinamento topologico (DAG)
		- componenti fortemente connesse
	- algoritmo di Dijkstra (letto Daikstra)
		- SPT / ??? per  grafi pesati $\geq 0$   $O(n+???)$