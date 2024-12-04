
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
## Struttura dati d-heap
Un d-heap e' un albero radicato d-ario (heap minimo) con le seguenti proprietà:
1. Completo almeno fino al penultimo livello e tutte le foglie sull'ultimo livello sono compattate verso sinistra.
2. Ogni nodo v contiene un elevamento $elem(v)$ ed una chiave $chiave(v)$ presa da un domino totalmente ordinato.
3. Ha un ordinamento parziale (inverso) dell'heap: $chiave(v)\geq chiave(partent(v))$ per ogni nodo $v$ diverso dalla radice.

Inoltre possiamo definire proprietà più specifiche per l'utilizzo:
1. Un d-heap con n nodi ha altezza $(\Theta\log_{d} n)$.
2. La radice contiene l’elemento con chiave minima (per via della proprietà di ordinamento a heap). 
3. Può essere rappresentato implicitamente tramite vettore posizionale grazie alla proprietà di struttura.

### Procedure Ausiliare Ripristino Struttura
- **Procedura per spostare verso l'alto**. Costo $O(\log_{d}(n))$

> $\text{procedura muoviAlto}(v)$
> 	$\text{while}(v \not=\text{radice}(T)\quad \&\quad\text{chiave}(v)<\text{chiave}(\text{padre}(v)))\text{ do}$
> 		scambia posto a $v$ e $\text{padre}(v)$ in T

- **Procedura per spostare verso il basso**.

## Albero Binomiale
> Un albero binomiale $B_{i}$ è definito ricorsivamente con:
> - $B_{0}$ è un unico nodo e $B_{1}$ sono due nodi.
> - Dato $i>0$, $B_{i+1}$ è ottenuto fondendo due $B_{i}$ ponendo la radice dell’uno come figlia della radice dell’altro![[l171.png]]

Gode delle seguenti proprietà, dimostrabili per induzione su n:
- Dato $B_{h}$ possiede $2^h$ nodi.
- La radice ha grado $\log_{2}(n)$
- L'altezza $H(n)=h=\log_{2}(n)$
- I figli di $B_{h}$ sono $B_{0}\text{ fino a }B_{h-1}$
### Heap Binomiale
Corrisponde ad una **foresta di alberi binomiali**, che gode delle seguenti proprietà:
- *Unicità*, in quanto per ogni intero $i>0$ esiste al più un nodo $B_{i}$ nella foresta.
- *Contenuto informativo*, ogni nodo v contiene un elemento elem(v) ed una chiave chiave(v) presa da un dominio totalmente ordinato.
- *Ordinamento a heap*, $chiave(v)\geq chiave(partent(v))$ per ogni nodo $v$ diverso dalla radice.