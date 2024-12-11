### Strutture dati per rappresentare grafi
- grafi non diretti
	- matrice di adiacenza ($O(n^{2})$)
	- liste di adiacenza ($O(n+m)$)
- grafi diretti
	- matrice di adiacenza ($O(n^{2})$)
	- liste di adiacenza ($O(n+m)$)

### Algoritmi di visita di un grafo
- una visita di un grafo G permette di esaminare i nodi e gli archi di G in modo sistematico
- genera un albero di visita
- problema di base in molte applicazioni
- esistono vari tipi di visite con diverse proprietà:
	- visita in ampiezza (BFS)
	- visita in profondità (DFS)

### Visita in ampiezza
Dato un grafo G (non pesato) e un nodo s, trova tutte le distanza/cammini minimi da s verso ogni altro nodo v
