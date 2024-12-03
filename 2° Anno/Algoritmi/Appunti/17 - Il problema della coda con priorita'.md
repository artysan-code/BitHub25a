
>tipo CodaPriorita
>dati:
>	un insieme $S$ di $n$ elementi di tipo $elem$ a cui sono associate chiavi di tipo chiave prese da un universo totalmente ordinato
>operazioni
>	findMin()-> $elem$
>		restituisce l'elemento in $S$ con la chiave minima
>	insert($elem\ e, chiave\ k$)
>		aggiunge a $S$ un nuovo elemento $e$ con chiave $k$
>	delete($elem\ e$)
>		cancella da $S$ l'elemento $e$
>	deleteMin()
>		cancella da $S$ l'elemento con chiave minima

>	increaseKey($elem\ e, chiave\ d$)
>		incrementa della quantità $d$ la chiave dell'elemento $e$ in $S$
>	decreseKey($elem\ e,chiave\ d$)
>		decrementa della quantità $d$ la chiave dell'elemento $e$ in $S$
>	merge(CodaPriorita $e_1$,CodaPriorita $e_2$)-> CodaPriorita
>		restituisce una nuova coda con priorità $e_{3}=e_{1}\cup e_{2}$

Applicazioni:
Gestione code in risorse condivise gestione priorità in processi concorrenti, progettazione di algoritmi efficienti per diversi problemi fondamentali (es: calcolo cammini minimi in un grafo, minimo albero ricoprente, ordinamento, ecc.)

---

da completare

--- 
### d-heap
un d-heap e' un albero radicato d-ario con le seguenti proprietà:
1. struttura:
   completo almeno fino al penultimo livello e tutte le foglie sull'ultimo livello sono compattate verso sinistra
2. contenuto informativo
   ogni nodo v contiene un elevamento $elem(v)$ ed una chiave $chiave(v)$ presa da un domino totalmente ordinato
3. ordinamento parziale (inverso)  dell'heap (min-heap):
   $chiave(v)\geq chiave(partent(v))$per ogni nodo $v$ diverso dalla radice

#### Proprietà
1. Un d-heap con n nodi ha altezza $(\Theta\log_{d} n)$
2. La radice contiene l’elemento con chiave minima (per via della proprietà di ordinamento a heap) 
3. Può essere rappresentato implicitamente tramite vettore posizionale grazie alla proprietà di struttura

