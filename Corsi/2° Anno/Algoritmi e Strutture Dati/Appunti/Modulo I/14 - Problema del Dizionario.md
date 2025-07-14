Data la struttura dati del [[Algoritmi e Strutture Dati#^4be009|Dizionario]] analizziamo una sua buona implementazione dove ogni operazione è garantita di avere $O(\log(n))$. Le idee sono:
- Definire un albero binario tale che ogni operazione richiede $O(altezza\ albero)$
- Fare in modo che l'altezza dell'albero sia sempre $\log(n)$ 
### Alberi binari di ricerca (BST)
Un **BST** rispetta le seguenti proprietà:
- Ogni *nodo v* contiene un elemento $elem(v)$ cui è associata una chiave $chiave(v)$ presa da un dominio totalmente ordinato.
- Per ogni nodo v vale che:
	- Le chiavi che si trovano nel sotto-albero sinistro di v sono $\leq$ $chiave(v)$.
	- Le chiavi che si trovano nel sotto-albero destro di v sono $>$ $chiave(v)$.

