> [!abstract] Tipi di Dato vs Strutture Dati
> - **Tipo di Dato Astratto (ADT):** Specifica _cosa_ è una collezione di dati e quali operazioni supporta (es. `insert`, `delete`, `search`), senza dire _come_ è implementata.
> - **Struttura Dati:** L'implementazione concreta (es. array, lista concatenata, albero) che organizza i dati in memoria per supportare le operazioni dell'ADT in modo efficiente.
> 
> **Obiettivo:** Progettare strutture dati che minimizzano le risorse di calcolo (tempo e spazio) necessarie per le operazioni richieste.

## Strutture Dati Elementari
### Pila (Stack)
> [!definition] LIFO (Last In First Out)
> L'ultimo elemento inserito è il primo ad essere estratto.
> 
> **Operazioni Principali:**
> - `push(e)`: Inserisce l'elemento `e` in cima.
> - `pop()`: Rimuove e restituisce l'elemento in cima.
> - `top()`: Legge l'elemento in cima senza rimuoverlo.

|Implementazione|Spazio|Push|Pop|Note|
|:--|:-:|:-:|:-:|:--|
|**Array (Dim. fissa)**|$O(n)$|$O(1)$|$O(1)$|Limite dimensione prefissato.|
|**Array Dinamico**|$O(n)$|$O(1)$*|$O(1)$|*Ammortizzato con raddoppio.|
|**Lista Concatenata**|$O(n)$|$O(1)$|$O(1)$|Nessun limite di dimensione.|

### Coda (Queue)
> [!definition] FIFO (First In First Out)
> Il primo elemento inserito è il primo ad essere estratto.
> 
> **Operazioni Principali:**
> - `enqueue(e)`: Inserisce `e` in coda.
> - `dequeue()`: Rimuove e restituisce l'elemento in testa.
> - `first()`: Legge l'elemento in testa senza rimuoverlo.

| Implementazione       | Spazio | Enqueue | Dequeue | Note                       |
| :-------------------- | :----: | :-----: | :-----: | :------------------------- |
| **Array Circolare**   | $O(n)$ | $O(1)$  | $O(1)$  | Usa indici modulo $n$.     |
| **Lista Concatenata** | $O(n)$ | $O(1)$  | $O(1)$  | Puntatori `head` e `tail`. |

### Dizionario
> [!definition] Tipo di Dato Dizionario
> Mantiene un insieme di elementi identificati da una **chiave**.
> 
> **Operazioni:**
> - `insert(e, k)`: Aggiunge l'elemento `e` con chiave `k`.
> - `delete(k)`: Rimuove l'elemento con chiave `k`.
> - `search(k)`: Restituisce l'elemento con chiave `k` (o `null` se non presente).

| Implementazione        |   Search    |   Insert    |   Delete    | Note                                               |
| :--------------------- | :---------: | :---------: | :---------: | :------------------------------------------------- |
| **Array Non Ordinato** |   $O(n)$    |   $O(1)$    |   $O(n)$    | Insert in coda. Delete richiede search.            |
| **Array Ordinato**     | $O(\log n)$ |   $O(n)$    |   $O(n)$    | Ricerca binaria. Shift costoso.                    |
| **Lista Non Ordinata** |   $O(n)$    |   $O(1)$    |   $O(n)$    | Insert in testa. Non permette ricerca binaria.     |
| **Lista Ordinata**     |   $O(n)$    |   $O(n)$    |   $O(n)$    | Non permette ricerca binaria (no accesso diretto). |
| **AVL**                | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Ottimo compromesso (vedi sezione BST/AVL).         |

> [!note] Confronto Array vs Lista
> - **Array:** Accesso diretto O(1), ma inserimento/cancellazione richiedono shift O(n)
> - **Lista:** Inserimento/cancellazione O(1) se si ha il puntatore, ma no accesso diretto

## Alberi e Rappresentazioni
> [!info] Definizioni Base
> - **Radice (Root):** Nodo senza padre.
> - **Foglia (Leaf):** Nodo senza figli.
> - **Nodo Interno:** Nodo con almeno un figlio.
> - **Grado:** Numero di figli di un nodo.
> - **Livello:** Distanza dalla radice (radice ha livello 0).
> - **Altezza:** Massima distanza tra radice e foglie (altezza albero vuoto = -1).
> - **Profondità di un nodo:** Distanza dalla radice.

### Tecniche di Rappresentazione
Come memorizzare la topologia di un albero in memoria.

| Rappresentazione        | Struttura                                    | Padre(u) | Figlio $i$-esimo | Ideale per                        |
| :---------------------- | :------------------------------------------- | :------: | :--------------: | :-------------------------------- |
| **Vettore dei Padri**   | Array $P$ dove $P[i]$ contiene info e parent |  $O(1)$  |      $O(n)$      | Algoritmi bottom-up (Union-Find)  |
| **Vettore Posizionale** | Nodi in array per livelli (radice in 1)      |  $O(1)$  |      $O(1)$      | Alberi quasi completi (Heap)      |
| **Puntatori ai Figli**  | Ogni nodo ha array/lista di puntatori figli  | $O(1)$*  |      $O(1)$      | Alberi generici o binari standard |

*Richiede puntatore `parent` esplicito nel nodo per accesso al padre in $O(1)$.

### Visite di Alberi
Algoritmi per accedere sistematicamente a tutti i nodi. Costo: $O(n)$ per $n$ nodi.

> [!code] DFS - Visita in Profondità
> Usa uno **Stack** (o ricorsione implicita).
> 
> **Tre ordini possibili (per alberi binari):**
> - **Pre-ordine:** Radice → Sinistro → Destro
> - **Simmetrica (In-order):** Sinistro → Radice → Destro _(ordina i BST!)_
> - **Post-ordine:** Sinistro → Destro → Radice _(utile per cancellazione o calcolo altezza)_
> 
> **Pseudocodice Ricorsivo (Pre-ordine):**
> ```text
> DFS-Preorder(nodo curr)
> 1. if curr ≠ null then
> 2.   visita(curr)
> 3.   DFS-Preorder(curr.sx)
> 4.   DFS-Preorder(curr.dx)
> ```
> 
> **Pseudocodice Iterativo (con Pila):**
> ```text
> DFS-Iterativo(radice rad)
> 1. Pila S
> 2. S.push(rad)
> 3. while S non vuota do
> 4.   curr = S.pop()
> 5.   visita(curr)
> 6.   if curr.dx ≠ null then S.push(curr.dx)
> 7.   if curr.sx ≠ null then S.push(curr.sx)
> ```

> [!code] BFS - Visita in Ampiezza
> Usa una **Coda**. Visita i nodi livello per livello (distanza crescente dalla radice).
> 
> **Pseudocodice:**
> ```text
> BFS(radice rad)
> 1. Coda Q
> 2. Q.enqueue(rad)
> 3. while Q non vuota do
> 4.   curr = Q.dequeue()
> 5.   visita(curr)
> 6.   for each figlio v di curr do
> 7.     Q.enqueue(v)
> ```

> [!note] Quando Usare DFS vs BFS
> - **DFS:** Quando serve esplorazione profonda (es. trovare cammini, topological sort)
> - **BFS:** Quando serve distanza minima, livelli, o elaborazione per livello
> - **In-order (DFS simmetrica):** Per stampare BST in ordine crescente

### Esercizi sulle Visite di Alberi

#### Calcolo dell'Altezza
L'altezza di un albero è definita come la massima distanza tra la radice e una foglia. Viene calcolata tramite una **visita in post-ordine** (bottom-up), risolvendo ricorsivamente i problemi per i sottoalberi prima di combinare i risultati.

- **Logica:** L'altezza di un nodo è pari a $1 +$ il massimo tra le altezze dei suoi figli.
- **Caso Base:** Un nodo nullo restituisce $-1$. In questo modo, una foglia (nodo con figli nulli) avrà altezza $1 + \max(-1, -1) = 0$.
- **Complessità:** $O(n)$, poiché ogni nodo viene visitato esattamente una volta.

```text
CalcolaAltezza(nodo rad)
1. if rad == null then return -1
2. h_sx = CalcolaAltezza(rad.sx)
3. h_dx = CalcolaAltezza(rad.dx)
4. return 1 + max(h_sx, h_dx)
```

#### Calcolo Numero Foglie
Questo algoritmo conta i nodi terminali dell'albero. Sfrutta una **visita ricorsiva** aggregando i risultati parziali risalendo verso la radice.

- **Logica:** Il numero di foglie è la somma delle foglie nei sottoalberi. Un nodo è contato come $1$ solo se soddisfa il predicato di foglia (nessun figlio).
- **Caso Base:** Se il nodo è nullo restituisce $0$. Se il nodo è una foglia restituisce $1$.
- **Complessità:** $O(n)$.

```text
CalcolaNumFoglie(nodo rad)
1. if rad == null then return 0
2. if rad è una foglia then return 1
3. num_sx = CalcolaNumFoglie(rad.sx)
4. num_dx = CalcolaNumFoglie(rad.dx)
5. return num_sx + num_dx
```

#### Calcolo Grado Medio
Determina il numero medio di figli per ogni **nodo interno** (non foglia). È un indicatore della densità di ramificazione.

- **Logica:** Rapporto tra la somma dei gradi di tutti i nodi e il numero totale di nodi interni ($n - n_foglie$).
- **SommaGradi:** Utilizza una visita post-ordine per accumulare il numero di figli dei soli nodi che hanno almeno un discendente.
- **Complessità:** $O(n)$.

```text
CalcolaGradoMedio(nodo rad)
1. n = numero nodi dell'albero
2. n_foglie = CalcolaNumFoglie(rad)
3. if rad ≠ null and (n - n_foglie) > 0 then 
4.    return SommaGradi(rad) / (n - n_foglie)

SommaGradi(nodo rad)
1. if rad == null or rad è una foglia then return 0
2. somma = numero figli di rad + SommaGradi(rad.sx) + SommaGradi(rad.dx) 
3. return somma
```

#### Ricerca Elemento
Cerca una specifica chiave all'interno di un albero generico (non necessariamente di ricerca). Implementa una **visita DFS in pre-ordine**.

- **Logica:** Controlla la radice; se non corrisponde, cerca a sinistra. Se la ricerca a sinistra restituisce un valore non nullo, termina; altrimenti cerca a destra.
- **Complessità:** $O(n)$ nel caso peggiore (elemento assente o nell'ultima posizione visitata).

```text
CercaElemento(nodo rad, chiave k)
1. if rad == null then return null
2. if rad.chiave == k then return rad
3. trovato = CercaElemento(rad.sx, k)
4. if trovato ≠ null then return trovato
5. return CercaElemento(rad.dx, k)
```

#### Ri-Radicazione (RiRadica)
Questo algoritmo permette di cambiare la radice di un albero mantenuto tramite **vettore dei padri**. Dato un nodo $j$ che deve diventare la nuova radice, l'algoritmo inverte la direzione dei puntatori lungo il cammino che congiungeva la vecchia radice al nodo $j$.

- **Logica:** Si risale dal nodo $j$ verso la vecchia radice. Per ogni nodo nel cammino, il suo vecchio padre diventa il suo nuovo figlio.
- **Complessità:** $O(h)$, dove $h$ è la profondità del nodo $j$ rispetto alla radice originale.

```text
RiRadica(VettorePadri T, indice j)
1. curr = j
2. padre = T[j].padre
3. T[j].padre = null
4. while padre ≠ null do
5.   nonno = T[padre].padre
6.   T[padre].padre = curr
7.   curr = padre
8.   padre = nonno
```

## Alberi Binari di Ricerca (BST)
> [!abstract] Definizione e Proprietà
> Un **Albero Binario di Ricerca (BST)** è un'implementazione efficiente del tipo di dato astratto **Dizionario**. Sfrutta la struttura gerarchica dell'albero per mantenere un insieme di elementi identificati da chiavi appartenenti a un dominio totalmente ordinato.
> 
> **Proprietà Fondamentale (Proprietà di Ricerca):**
> Per ogni nodo `curr` dell'albero:
> 1. Tutte le chiavi nel **sottoalbero sinistro** di `curr` sono $\le$ `curr.key`.
> 2. Tutte le chiavi nel **sottoalbero destro** di `curr` sono $>$ `curr.key`.
> 
> > [!important] Implicazione sulle Visite
> > Una **visita in ordine simmetrico (in-order)** di un BST restituisce le chiavi in **ordine crescente**. Questo rende i BST ideali non solo per la ricerca, ma anche per mantenere i dati ordinati dinamicamente.

### Operazioni di Ricerca
Tutte le operazioni di ricerca in un BST hanno una complessità proporzionale all'altezza dell'albero: **$O(h)$**.

#### Search (Ricerca di una chiave)
Traccia un cammino dalla radice verso il basso. A ogni nodo, confronta la chiave cercata `k` con la chiave del nodo corrente:
- Se `k < curr.key`: prosegue nel sottoalbero sinistro.
- Se `k > curr.key`: prosegue nel sottoalbero destro.
- Se `k == curr.key`: elemento trovato.

```text
search(BST T, k)
1. curr = T.radice
2. while curr ≠ null and k ≠ curr.key do
3.   if k < curr.key then curr = curr.sx
4.   else curr = curr.dx
5. return curr
```

> [!success] Complessità
> - **Caso medio:** $O(\log n)$ - albero bilanciato
> - **Caso peggiore:** $O(n)$ - albero degenere (lista)

#### Minimo e Massimo
Grazie alla proprietà di ricerca:
- Il **minimo** si trova seguendo sempre i puntatori sinistri fino a raggiungere l'ultimo nodo.
- Il **massimo** si trova seguendo sempre i puntatori destri fino all'ultimo nodo.

```text
min(BST T)
1. curr = T.radice
2. while curr.sx ≠ null do curr = curr.sx
3. return curr
```

> [!success] Complessità
> $O(h)$ dove $h$ è l'altezza dell'albero

#### Successore e Predecessore
Il **successore** di un nodo `u` è il nodo `v` con la minima chiave strettamente maggiore di `u.key`.
- **Caso 1 (u ha figlio destro):** Il successore è il minimo del sottoalbero destro di `u`.
- **Caso 2 (u NON ha figlio destro):** Si risale l'albero verso la radice finché non si incontra un nodo che è figlio sinistro del proprio padre. Quel padre è il successore.

```text
successor(nodo)
1. if nodo.dx ≠ null then return min(nodo.dx)
2. padre = nodo.p
3. while padre ≠ null and nodo == padre.dx do
4.   nodo = padre
5.   padre = padre.p
6. return padre
```
*(Il predecessore è simmetrico: massimo del sottoalbero sinistro o primo antenato di cui si è figlio destro).*

### Operazioni di Modifica
#### Inserimento (Insert)
L'inserimento di un nuovo elemento avviene sempre come **foglia**, preservando la proprietà di ricerca.
1. Si simula una ricerca della chiave `k` per individuare la posizione corretta (un puntatore `null`).
2. Si mantiene un puntatore al `padre` dell'ultimo nodo visitato.
3. Si crea il nuovo nodo e lo si aggancia come figlio sinistro o destro del padre a seconda del confronto tra le chiavi.

```text
insert(BST T, e, k)
1. nuovo = crea nuovo nodo(elem=e, key=k)
2. padre = null, curr = T.radice
3. while curr ≠ null do
4.   padre = curr
5.   if k < curr.key then curr = curr.sx
6.   else curr = curr.dx
7. nuovo.p = padre
8. if padre == null then T.radice = nuovo
9. else if k < padre.key then padre.sx = nuovo
10. else padre.dx = nuovo
```

> [!success] Complessità
> $O(h)$ - dominato dalla discesa nell'albero

#### Cancellazione (Delete)
L'operazione più complessa, divisa in tre scenari basati sul numero di figli del nodo da eliminare:
1. **Caso 1 (Nodo foglia):** Si rimuove semplicemente il nodo aggiornando il puntatore del padre a `null`.
2. **Caso 2 (Un solo figlio):** Il nodo viene "scavalcato": il padre del nodo da eliminare punta direttamente all'unico figlio di quest'ultimo.
3. **Caso 3 (Due figli):** Non è possibile rimuovere il nodo direttamente. Si individua il suo **successore** (o predecessore), se ne copia il contenuto nel nodo da eliminare, e si procede alla rimozione fisica del successore (che ricadrà necessariamente nel Caso 1 o 2, avendo al massimo un figlio).

```text
delete(BST T, nodo)
1. if nodo.sx == null or nodo.dx == null then y = nodo
2. else y = successor(nodo)
3. // y è il nodo da rimuovere fisicamente (ha al più 1 figlio)
4. if y.sx ≠ null then x = y.sx else x = y.dx
5. if x ≠ null then x.p = y.p
6. if y.p == null then T.radice = x
7. else if y == y.p.sx then y.p.sx = x
8. else y.p.dx = x
9. if y ≠ nodo then (copia elem e key di y in nodo)
```

> [!success] Complessità
> $O(h)$ - ricerca + eventuale ricerca successore

### Analisi delle Prestazioni
> [!warning] Il Problema del Bilanciamento
> Tutte le operazioni sopra descritte hanno costo **$O(h)$**.
> - **Caso Ottimo (Albero bilanciato):** $h = \Theta(\log n) \implies$ Prestazioni logaritmiche eccellenti.
> - **Caso Peggiore (Albero degenere/linearizzato):** $h = \Theta(n) \implies$ Le prestazioni degradano a quelle di una lista collegata.
> 
> Questo accade tipicamente se gli elementi vengono inseriti già ordinati. La soluzione a questo problema è l'utilizzo di alberi che si auto-bilanciano, come gli **Alberi AVL**.
> 
> **Soluzione:** Alberi bilanciati (AVL, Red-Black Trees)

## Alberi AVL (Alberi Bilanciati)
> [!definition] Alberi AVL
> Un **BST** è **AVL** se per **ogni** nodo $v$, il **fattore di bilanciamento** soddisfa:
> $$\beta(v) = h(\text{sottoalbero sinistro di } v) - h(\text{sottoalbero destro di } v) \in \{-1, 0, +1\}$$
> 
> Dove $h(\text{albero vuoto}) = -1$ per convenzione.

> [!success] Garanzia Fondamentale
> **Teorema:** Un albero AVL con $n$ nodi ha altezza $h = O(\log n)$.
> 
> **Conseguenza:** Tutte le operazioni (search, insert, delete) costano $O(\log n)$ garantito!

> [!info] Mantenimento del Bilanciamento
> Generalmente $\beta(v)$ è mantenuto come **informazione addizionale** nel record di ogni nodo (oppure si memorizza l'altezza del sottoalbero).

### Fattore di Bilanciamento
> [!note] Interpretazione
> - $\beta(v) = +1$: sottoalbero sinistro più alto di 1
> - $\beta(v) = 0$: sottoalberi bilanciati
> - $\beta(v) = -1$: sottoalbero destro più alto di 1
> - $|\beta(v)| = 2$: **SBILANCIATO** → serve ribilanciamento!

> [!example] Esempi
> ```
>      15           ← β = 0
>     /  \
>    6    18        ← β(6) = 0, β(18) = -1
>   / \     \
>  3   8    20      ← tutti β ∈ {-1,0,+1} → AVL ✓
> ```
> ```
>      20           ← β = +2 → NON AVL! ✗
>     /
>    17
>   /
>  16
> ```

### Ribilanciamento tramite Rotazioni
> [!warning] Quando Serve Ribilanciare
> Dopo un `insert` o `delete`, se un nodo $v$ ha $|\beta(v)| = 2$, dobbiamo applicare rotazioni.
> 
> **Nodo Critico:** Il nodo più profondo con $|\beta(v)| = 2$

> [!info] I 4 Casi di Rotazione
> A seconda della **direzione dello sbilanciamento**, abbiamo 4 casi (simmetrici a coppie):
> 
> |Caso|β(v)|Sottocaso|Rotazione|
> |:--|:-:|:--|:--|
> |**SS** (Sinistra-Sinistra)|$+2$|Sbilanciamento nel sottoalbero sinistro del figlio sinistro|Rotazione semplice **DESTRA**|
> |**DD** (Destra-Destra)|$-2$|Sbilanciamento nel sottoalbero destro del figlio destro|Rotazione semplice **SINISTRA**|
> |**SD** (Sinistra-Destra)|$+2$|Sbilanciamento nel sottoalbero destro del figlio sinistro|Rotazione **DOPPIA** (sx su figlio, dx su v)|
> |**DS** (Destra-Sinistra)|$-2$|Sbilanciamento nel sottoalbero sinistro del figlio destro|Rotazione **DOPPIA** (dx su figlio, sx su v)|

### Rotazione Semplice (Destra su nodo)
> [!code] Pseudocodice Rotazione Destra
> ```text
> rotazioneDestra(nodo)
> 1. sx = nodo.sx
> 2. nodo.sx = sx.dx
> 3. if sx.dx ≠ null then
> 4.   sx.dx.p = nodo
> 5. sx.p = nodo.p
> 6. if nodo.p == null then T.radice = sx
> 7. else if nodo == nodo.p.sx then
> 8.   nodo.p.sx = sx
> 9. else nodo.p.dx = sx
> 10. sx.dx = nodo
> 11. nodo.p = sx
> 12. aggiorna β(nodo) e β(sx)
> ```

> [!success] Proprietà Rotazioni
> - **Mantengono la proprietà BST** (ordine delle chiavi preservato)
> - **Costo:** $O(1)$ - solo aggiornamenti puntatori locali
> - **Aggiornamento β:** $O(1)$ - solo i nodi coinvolti cambiano

> [!note] Rotazione Sinistra
> Simmetrica alla rotazione destra (scambia "sinistro" ↔ "destro")

### Caso SS (Sinistra-Sinistra)
> [!example] Esempio Caso SS
> ```
> Sbilanciamento:          Dopo rotazione destra su v:
>       v (β=+2)                    u (β=0)
>      /                           / \
>     u (β≥0)         →          T1  v (β=0)
>    / \                             / \
>   T1  T2                          T2  T3
>       /
>      T3
> ```
> **Applicazione:** Rotazione semplice **DESTRA** su $v$

> [!info] Osservazioni Importanti
> - **Insert:** Provoca solo il sottocaso dove l'altezza dell'albero diminuisce → **1 rotazione basta**
> - **Delete:** Può provocare entrambi i sottocasi → altezza potrebbe non diminuire → sbilanciamento si propaga

### Caso DD (Destra-Destra)
> [!example] Esempio Caso DD
> ```
> Sbilanciamento:          Dopo rotazione sinistra su v:
>    v (β=-2)                    u (β=0)
>     \                         / \
>      u (β≤0)      →          v   T3
>     / \                     / \
>    T2  T3                  T1  T2
>   /
>  T1
> ```
> **Applicazione:** Rotazione semplice **SINISTRA** su $v$

### Caso SD (Sinistra-Destra)
> [!tip] Strategia
> Lo sbilanciamento è "a zigzag" → serve rotazione **DOPPIA**:
> 1. Prima rotazione **SINISTRA** sul figlio sinistro di $v$ (nodo $z$)
> 2. Poi rotazione **DESTRA** su $v$

> [!example] Esempio Caso SD
> ```
> Sbilanciamento:               Dopo rotazione sx su z:        Dopo rotazione dx su v:
>       v (β=+2)                       v (β=+2)                      w (β=0)
>      /                              /                            /   \
>     z (β=-1)         →             w (β=+1)         →           z     v
>    / \                            /                            / \   / \
>   T1  w                          z                           T1 T2 T3 T4
>      / \                        / \
>     T2  T3                     T1  T2
>        /                              \
>       T4                               T3
>                                       /
>                                      T4
> ```
> **Applicazione:**
> 1. RotazioneSinistra(z)
> 2. RotazioneDestra(v)

### Caso DS (Destra-Sinistra)
> [!example] Esempio Caso DS
> Simmetrico al caso SD:
> 1. Prima rotazione **DESTRA** sul figlio destro di $v$
> 2. Poi rotazione **SINISTRA** su $v$

### Operazioni AVL
#### Insert
> [!tip] Strategia Insert AVL
> 1. Inserisci come in un BST normale (come foglia)
> 2. Risali verso la radice aggiornando i fattori di bilanciamento
> 3. Trova il **primo** nodo critico $v$ (con $|\beta(v)| = 2$)
> 4. Determina il caso (SS, DD, SD, DS) e applica la rotazione appropriata
> 
> > [!code] Pseudocodice Insert AVL
> > ```text
> > insert(AVL T, e, k)
> > 1. nuovo = crea nuovo nodo con elem=e, key=k
> > 2. Inserisci nuovo come in un BST
> > 3. Ricalcola β dei nodi nel cammino da nuovo alla radice
> > 4. Sia v il più profondo nodo con β(v) = ±2 (nodo critico)
> > 5. if v esiste then
> > 6.   Determina il caso (SS/DD/SD/DS)
> > 7.   Esegui la rotazione opportuna su v
> > ```

> [!success] Complessità Insert
> $O(\log n)$:
> - Inserimento BST: $O(\log n)$
> - Ricalcolo β: $O(\log n)$ nodi nel cammino
> - Rotazione: $O(1)$
> - **Numero rotazioni:** Al massimo **1** (semplice o doppia)

> [!note] Perché 1 Rotazione Basta per Insert
> Dopo la rotazione, l'altezza del sottoalbero ruotato torna uguale a quella che aveva **prima** dell'inserimento → nessun altro nodo si sbilancia verso l'alto.

#### Delete
> [!tip] Strategia Delete AVL
> 1. Cancella come in un BST normale (3 casi)
> 2. Ricalcola β del padre del nodo eliminato fisicamente
> 3. Se $|\beta| = 2$, applica rotazione
> 4. **Continua a risalire** verso la radice controllando β ad ogni livello
> 5. Applica rotazioni se necessario fino alla radice

> [!code] Pseudocodice Delete AVL
> ```text
> delete(AVL T, e)
> 6. Cancella il nodo come in un BST
> 7. curr = padre del nodo eliminato fisicamente
> 8. while curr ≠ null do
> 9.   Ricalcola β(curr)
> 10.   if |β(curr)| == 2 then
> 11.     Determina il caso e applica rotazione su curr
> 12.     if l'altezza del sottoalbero di curr è uguale a prima then
> 13.       break  // terminazione anticipata
> 14.   curr = curr.p
> ```

> [!success] Complessità Delete
> $O(\log n)$:
> - Cancellazione BST: $O(\log n)$
> - Ricalcolo β e rotazioni: $O(\log n)$ nel peggiore
> - **Numero rotazioni:** Fino a $O(\log n)$ rotazioni (una per livello)

> [!warning] Differenza Insert vs Delete
> - **Insert:** 1 rotazione basta (altezza ritorna come prima)
> - **Delete:** Fino a $O(\log n)$ rotazioni (sbilanciamento può propagarsi verso l'alto)

#### Search
> [!note] Search in AVL
> Identico al BST normale: $O(\log n)$ garantito (grazie al bilanciamento)

### Campo Altezza nei Nodi
> [!info] Implementazione Pratica
> Per implementare efficientemente un AVL, ogni nodo deve contenere un campo aggiuntivo:
> - **Opzione 1:** `altezza` del sottoalbero radicato nel nodo
> - **Opzione 2:** `β` (fattore di bilanciamento) direttamente
> 
> **Proprietà richieste:**
> 1. Dato un nodo, calcolare $\beta(nodo)$ in $O(1)$
> 2. Dopo insert/delete, ricalcolare $\beta$ lungo il cammino in $O(\log n)$
> 3. Durante le rotazioni, aggiornare $\beta$ dei nodi coinvolti in $O(\log n)$
> 
> > [!code] Aggiornamento Altezza
> > ```text
> > aggiornaAltezza(nodo)
> > 4. h_sx = altezza(nodo.sx)  // -1 se null
> > 5. h_dx = altezza(nodo.dx)  // -1 se null
> > 6. nodo.altezza = 1 + max(h_sx, h_dx)
> > 7. β(nodo) = h_sx - h_dx
> > ```

### Riepilogo AVL
|Operazione|Complessità|Note|
|:--|:-:|:--|
|Search|$O(\log n)$|Come BST normale|
|Insert|$O(\log n)$|Al massimo 1 rotazione|
|Delete|$O(\log n)$|Fino a $O(\log n)$ rotazioni|
|Min / Max|$O(\log n)$|Come BST normale|

> [!success] Vantaggi AVL
> - **Garanzia** $O(\log n)$ per tutte le operazioni
> - Più bilanciato di Red-Black Trees (altezza minore)

> [!warning] Svantaggi AVL
> - Più rotazioni durante delete (vs Red-Black)
> - Overhead memoria per memorizzare β o altezza
> - Ribilanciamenti più frequenti

## Code con Priorità
> [!definition] Coda con Priorità (ADT)
> Una struttura dati che mantiene un insieme $S$ di elementi, ciascuno con una **chiave** (priorità). A differenza di una coda standard (FIFO), l'estrazione non segue l'ordine di arrivo ma la priorità.
> 
> **Operazioni Base:**
> - `insert(e, k)`: Inserisce un elemento con priorità $k$.
> - `findMin()`: Restituisce l'elemento con priorità minima.
> - `deleteMin()`: Rimuove e restituisce il minimo.
> - `decreaseKey(x, k)`: Diminuisce la chiave del nodo $x$ al nuovo valore $k$.
> - `merge(Q1, Q2)`: Fonde due code con priorità.

### Implementazioni Base
Prima di analizzare strutture avanzate come gli Heap, vediamo come le strutture elementari si comportano nell'implementare una Coda con Priorità (assumendo di voler estrarre il minimo):

| Implementazione | `insert` | `findMin` | `deleteMin` | `merge` |
| :--- | :---: | :---: | :---: | :---: |
| **Array Non Ordinato** | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Array Ordinato** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| **Lista Non Ordinata** | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| **Lista Ordinata** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |

> [!note] Trade-off
> Come si nota, le implementazioni semplici costringono a scegliere tra un inserimento veloce e un'estrazione lenta, o viceversa. L'obiettivo delle strutture avanzate (Heap) è bilanciare questi costi portandoli entrambi a livello logaritmico.

> [!success] Applicazioni Pratiche
> - Gestione code in risorse condivise (scheduler CPU)
> - Algoritmi su grafi: Dijkstra (cammini minimi), Prim (MST)
> - Ordinamento: HeapSort
> - Simulazione eventi discreti

## Heap d-ari
> [!definition] Definizione
> Un **d-heap** (o heap d-ario) è un albero radicato d-ario che gode delle seguenti proprietà:
> 1.  **Struttura:** È completo almeno fino al penultimo livello, e tutte le foglie sull'ultimo livello sono compattate verso sinistra.
> 2.  **Contenuto Informativo:** Ogni nodo $v$ contiene un elemento `elem(v)` e una chiave `chiave(v)` presa da un dominio ordinato.
> 3.  **Ordinamento Parziale (Min-Heap):** Per ogni nodo $v$ diverso dalla radice, vale `chiave(v) >= chiave(parent(v))`.
>     *(Nota: Per i Max-Heap vale la relazione inversa).*
>
> **Nota:** Un **Heap Binario** è semplicemente un caso particolare di d-heap con **$d=2$**.

### Rappresentazione (Vettore Posizionale)
Un d-heap con $n$ nodi può essere rappresentato efficientemente in un array posizionale (senza puntatori espliciti).
Gli indici partono da $0$:
- **Radice:** indice $0$.
- **Figlio $j$-esimo di $i$** (con $j \in \{1, \dots, d\}$): indice $d \cdot i + j$.
- **Padre di $i$:** indice $\lfloor (i-1)/d \rfloor$.

> [!success] Altezza
> L'altezza di un d-heap con $n$ nodi è $\Theta(\log_d n)$.

### Procedure Ausiliarie
Queste procedure servono a ripristinare la proprietà di ordinamento (heap property) quando viene violata.

#### muoviAlto ((MoveUp / DecreaseKey interna) )
Ripristina l'ordinamento verso l'alto. Utile quando la chiave di un nodo diminuisce (diventa più piccola del padre).
```text
muoviAlto(i)
1. while i ≠ 0 and chiave(A[i]) < chiave(A[parent(i)]) do
2.   scambia A[i] con A[parent(i)]
3.   i = parent(i)
```
**Complessità:** $O(\log_d n)$ (altezza dell'albero).

#### muoviBasso (MoveDown / FixHeap)
Ripristina l'ordinamento verso il basso. Utile quando la chiave di un nodo aumenta (diventa più grande dei figli) o quando si sposta una foglia nella radice.
```text
muoviBasso(i)
1. while i non è una foglia do
2.   m = indice del figlio di i con chiave minima
3.   if chiave(A[i]) > chiave(A[m]) then
4.     scambia A[i] con A[m]
5.     i = m
6.   else break
```
**Complessità:** $O(d \log_d n)$. Ad ogni livello bisogna confrontare $d$ figli per trovare il minimo.

### Operazioni Principali
#### findMin
Restituisce l'elemento con chiave minima (la radice).
**Complessità:** $O(1)$.

#### insert
Inserisce un nuovo elemento.
1.  Aggiunge il nuovo nodo come ultima foglia (in fondo all'array).
2.  Chiama `muoviAlto` per portarlo nella posizione corretta.
```text
insert(elem e, chiave k)
1. A.heapsize = A.heapsize + 1
2. A[A.heapsize - 1] = (e, k)
3. muoviAlto(A.heapsize - 1)
```
**Complessità:** $O(\log_d n)$.

#### deleteMin (extractMin)
Rimuove e restituisce l'elemento minimo.
1.  Salva la radice (minimo).
2.  Sposta l'ultima foglia nella radice.
3.  Decrementa la dimensione.
4.  Chiama `muoviBasso` sulla nuova radice.
```text
deleteMin()
1. min = A[0]
2. A[0] = A[A.heapsize - 1]
3. A.heapsize = A.heapsize - 1
4. muoviBasso(0)
5. return min
```
**Complessità:** $O(d \log_d n)$.

#### decreaseKey
Riduce il valore della chiave di un elemento e ripristina la proprietà verso l'alto.
```text
decreaseKey(i, delta)
1. chiave(A[i]) = chiave(A[i]) - delta
2. muoviAlto(i)
```
**Complessità:** $O(\log_d n)$.

#### increaseKey
Aumenta il valore della chiave e ripristina verso il basso.
```text
increaseKey(i, delta)
1. chiave(A[i]) = chiave(A[i]) + delta
2. muoviBasso(i)
```
**Complessità:** $O(d \log_d n)$.

#### delete
Rimuove un elemento generico all'indice $i$.
1.  Chiama `decreaseKey(i, -\infty)` per portarlo in cima.
2.  Chiama `deleteMin`.
**Complessità:** $O(d \log_d n)$.

#### heapify (Costruzione)
Costruisce un heap a partire da un array disordinato.
Si chiama `muoviBasso` su tutti i nodi interni, partendo dall'ultimo genitore fino alla radice.
**Complessità:** $O(n)$ (lineare).

### Quando conviene usare d > 2?
Aumentare $d$ riduce l'altezza dell'albero ($\log_d n$), velocizzando le operazioni di salita (`insert`, `decreaseKey`). Tuttavia, rallenta le operazioni di discesa (`deleteMin`, `muoviBasso`) perché richiede più confronti per trovare il figlio minimo ($d$).
-   **Conviene** se le operazioni di inserimento/decreaseKey sono molto più frequenti delle estrazioni.
-   **Non conviene** se le estrazioni sono frequenti.


## Heap Binomiali
> [!abstract] Motivazione
> Gli heap binari hanno un problema: **merge** di due heap costa $O(n)$.
> 
> Gli **heap binomiali** risolvono questo problema garantendo **merge in $O(\log n)$**!

### Alberi Binomiali
> [!definition] Definizione Ricorsiva
> Un **albero binomiale** $B_i$ è definito ricorsivamente:
> 1. **$B_0$** consiste di un **unico nodo**
> 2. **$B_{i+1}$** si ottiene **fondendo** due alberi $B_i$, ponendo la radice dell'uno come **figlia** della radice dell'altro
> 
> Esempio:
> ```
> B₀:  •
> 
> B₁:  •          (fusione di due B₀)
>      |
>      •
> 
> B₂:  •          (fusione di due B₁)
>     / \
>    •   •
>    |
>    •
> 
> B₃:  •          (fusione di due B₂)
>     /|\
>    • • •
>    |  /\
>    • • •
>      |
>      •
> ```

> [!info] Proprietà Alberi Binomiali
> Per ogni $i \ge 0$:
> 
> |Proprietà|Valore|
> |:--|:-:|
> |**Numero di nodi**|$2^i$|
> |**Altezza**|$i$|
> |**Grado della radice**|$i$ (ha $i$ figli)|
> |**Nodi a livello $k$**|$\binom{i}{k}$ (coefficiente binomiale)|
> 
> **Da cui il nome "binomiale"!**

### Definizione Heap Binomiale
> [!definition] Heap Binomiale
> Un **heap binomiale** è una **foresta** (collezione) di alberi binomiali che soddisfa:
> 1. **Unicità:** Per ogni intero $i \ge 0$, esiste **al più** un $B_i$ nella foresta
> 2. **Contenuto informativo:** Ogni nodo $v$ contiene un elemento `elem(v)` e una chiave `key(v)`
> 3. **Ordinamento a heap:** `key(v)` $\ge$ `key(parent(v))` per ogni nodo $v$ diverso da una radice → Il **minimo** è in una delle radici (per min-heap)

> [!example] Esempio Heap Binomiale (n=13)
> ```
> n = 13 = 8 + 4 + 1 = 2³ + 2² + 2⁰
> In binario: 13 = 1101₂
> 
> Foresta: B₃, B₂, B₀
> 
>     10        1        6
>    /|\       /        (radice B₀)
>   ...       ...
> (B₃)       (B₂)
> 
> Le chiavi delle radici: {10, 1, 6} → minimo = 1
> ```

> [!success] Proprietà Topologiche
> - Un heap binomiale con $n$ nodi ha **al più $\lfloor \log_2 n \rfloor + 1$ alberi**
> - Gli alberi presenti corrispondono agli **1 nella rappresentazione binaria** di $n$
> - Ogni albero ha **altezza e grado** $O(\log n)$

### Rappresentazione
> [!note] Struttura Dati
> Un heap binomiale è rappresentato come:
> - **Lista di radici:** Collegamenti tra le radici degli alberi binomiali (ordinati per grado crescente)
> - **Ogni nodo contiene:**
>     - `key`: chiave
>     - `parent`: puntatore al padre
>     - `degree`: grado (numero di figli)
>     - `child`: puntatore al primo figlio
>     - `sibling`: puntatore al prossimo fratello

### Operazioni Heap Binomiali
#### FindMin
> [!tip] Idea
> Il minimo è in una delle radici. Scorri le radici e trova il minimo.

> [!success] Complessità
> $O(\log n)$ - al più $\log n$ radici da controllare

#### Merge (Fusione)
> [!tip] Idea Chiave
> Fondere due heap binomiali è come **sommare due numeri binari**!
> 
> Procedura:
> 1. Fondi le due liste di radici in una lista ordinata per grado
> 2. Scorri la lista e "porta il riporto": se trovi due $B_i$, fondili in un $B_{i+1}$
> 3. Mantieni la proprietà di unicità (al più un $B_i$ per ogni $i$)

> [!code] Algoritmo Merge (semplificato)
> ```text
> merge(H1, H2)
> 1. Fondi le liste di radici di H1 e H2 in ordine di grado
> 2. Scorri la lista risultante:
> 3. while ci sono due alberi Bi consecutivi with stesso grado:
> 4.   Fondi i due Bi in un Bi+1 (radice minore diventa padre)
> 5.   Rimuovi uno dei due Bi dalla lista
> 6. return la lista finale
> ```

> [!success] Complessità Merge
> **$O(\log n)$** dove $n = n_1 + n_2$ (dimensione totale)
> 
> - Fusione liste: $O(\log n)$ - al più $\log n_1 + \log n_2$ radici
> - Portare il riporto: $O(\log n)$ - ogni fusione diminuisce di 1 il numero di alberi

> [!note] Merge è la Killer Feature
> Questa è la ragione principale per usare heap binomiali: **merge logaritmico** invece di lineare!

#### Insert
> [!tip] Idea
> Inserire un elemento = creare un heap con solo quell'elemento ($B_0$) e fare merge con l'heap esistente.

> [!code] Pseudocodice Insert
> ```text
> insert(H, elem e, chiave k)
> 1. Crea heap H' con un solo nodo (B₀) contenente e, k
> 2. return merge(H, H')
> ```

> [!success] Complessità
> $O(\log n)$ - dominato da merge

#### DeleteMin (ExtractMin)
> [!tip] Idea
> 1. Trova il minimo (in una radice) in $O(\log n)$
> 2. Rimuovi quella radice
> 3. I figli della radice rimossa formano un heap binomiale $H'$
> 4. Fai merge dell'heap originale (senza la radice) con $H'$

> [!code] Pseudocodice DeleteMin
> ```text
> deleteMin(H)
> 1. Trova la radice r con chiave minima
> 2. Rimuovi r dalla lista delle radici
> 3. H' = heap formato dai figli di r (invertiti in ordine di grado)
> 4. return merge(H, H')
> ```

> [!success] Complessità
> $O(\log n)$:
> - FindMin: $O(\log n)$
> - Merge: $O(\log n)$

#### DecreaseKey / IncreaseKey
> [!tip] Idea
> Simile a heap binario: dopo aver modificato la chiave, ripristina la proprietà heap facendo "salire" (DecreaseKey) o "scendere" (IncreaseKey) il nodo.

> [!success] Complessità
> $O(\log n)$ - al massimo risali/scendi dall'altezza $O(\log n)$

#### Delete
> [!tip] Idea
> 1. DecreaseKey del nodo a $-\infty$ (diventa minimo)
> 2. DeleteMin

> [!success] Complessità
> $O(\log n)$ - dominato da DeleteMin

### Riepilogo Heap Binomiali
|Operazione|Complessità|
|:--|:-:|
|FindMin|$O(\log n)$|
|Insert|$O(\log n)$|
|DeleteMin|$O(\log n)$|
|DecreaseKey / IncreaseKey|$O(\log n)$|
|Delete|$O(\log n)$|
|**Merge**|**$O(\log n)$** ← Vantaggio chiave!|

## Heap di Fibonacci (Cenni)
> [!abstract] Idea
> Gli **heap di Fibonacci** sono una versione "rilassata" degli heap binomiali che ottiene **complessità ammortizzate** migliori.
> 
> **Due rilassamenti:**
> 1. **Heap binomiale rilassato:** Rilassa la proprietà di unicità (possono esserci più $B_i$)
> 2. **Heap di Fibonacci:** Rilassa anche la struttura degli alberi (non sono più necessariamente binomiali)

> [!info] Filosofia "Pigra" (Lazy)
> "Perché ristrutturare subito la foresta quando potremmo farlo dopo?"
> - Insert diventa molto veloce (aggiungi e basta, senza merge immediato)
> - Il lavoro viene "ammortizzato" su più operazioni

### Complessità Ammortizzate
> [!warning] Complessità Ammortizzata
> Le complessità per heap di Fibonacci sono **ammortizzate**, cioè:
> 
> **Tempo ammortizzato** = $\frac{\text{Costo totale di } n \text{ operazioni}}{n}$
> 
> Singole operazioni possono costare di più, ma in media su molte operazioni il costo è quello indicato.

|Operazione|Heap Fibonacci (Ammortizzata)|Heap Binomiale|
|:--|:-:|:-:|
|FindMin|$O(1)$|$O(\log n)$|
|Insert|$O(1)$|$O(\log n)$|
|Merge|$O(1)$|$O(\log n)$|
|DecreaseKey|$O(1)$*|$O(\log n)$|
|DeleteMin|$O(\log n)$*|$O(\log n)$|
|Delete|$O(\log n)$*|$O(\log n)$|

*Complessità ammortizzata

### Applicazione Importante: Dijkstra
> [!example] Algoritmo di Dijkstra
> L'heap di Fibonacci è particolarmente efficiente per l'algoritmo di Dijkstra (cammini minimi):
> 
> **Operazioni in Dijkstra su grafo con $n$ nodi e $m$ archi:**
> - $n$ Insert
> - $n$ DeleteMin
> - Fino a $m$ DecreaseKey
> 
> **Complessità totale:**
> - Con heap binario/binomiale: $O((n+m) \log n) = O(m \log n)$
> - Con heap di Fibonacci: $O(n \log n + m)$ ← **Meglio su grafi densi!**

## Tabella Riassuntiva - Code con Priorità
> [!success] Confronto Completo Implementazioni
> Tutte le complessità nel **caso peggiore**, tranne heap Fibonacci (ammortizzate*).

|Struttura|FindMin|Insert|Delete|DeleteMin|DecKey|IncKey|Merge|
|:--|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**Array Non Ordinato**|$\Theta(n)$|$O(1)$|$O(1)$|$\Theta(n)$|$O(1)$|$O(1)$|$O(n)$|
|**Array Ordinato**|$O(1)$|$O(n)$|$O(n)$|$O(1)$|$O(n)$|$O(n)$|$O(n)$|
|**Lista Non Ordinata**|$\Theta(n)$|$O(1)$|$O(1)$|$\Theta(n)$|$O(1)$|$O(1)$|$O(1)$|
|**Lista Ordinata**|$O(1)$|$O(n)$|$O(1)$|$O(1)$|$O(n)$|$O(n)$|$O(n)$|
|**Heap Binario**|$O(1)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(n)$|
|**d-Heap**|$O(1)$|$O(\log_d n)$|$O(d \log_d n)$|$O(d \log_d n)$|$O(\log_d n)$|$O(d \log_d n)$|$O(n)$|
|**Heap Binomiale**|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|$O(\log n)$|
|**Heap Fibonacci**|$O(1)$|$O(1)$|$O(\log n)$*|$O(\log n)$*|$O(1)$*|$O(\log n)$*|$O(1)$|

## Quando Usare Quale Struttura Dati
> [!tip] Guida alla Scelta

### Per Code con Priorità:
**Heap Binario:**
- Caso d'uso generale
- Semplice da implementare
- Buone performance pratiche

**d-ary Heap ($d > 2$):**
- Quando Insert/IncreaseKey sono **molto più frequenti** di DeleteMin
- Esempio: $d=4$ con 90% insert, 10% deleteMin

**Heap Binomiale:**
- Quando serve **merge** frequente tra code
- Esempio: unire code di eventi da fonti diverse

**Heap di Fibonacci:**
- Algoritmi avanzati su grafi (Dijkstra, Prim)
- Quando DecreaseKey è molto frequente
- Solo se $m >> n \log n$ (grafo denso)

### Per Dizionari:
**Array Non Ordinato:**
- Pochi elementi
- Insert molto più frequente di Search

**Array Ordinato:**
- Pochi elementi
- Search frequente, Insert raro

**Lista:**
- Dimensione variabile
- Insert/Delete in testa frequenti

**BST (non bilanciato):**
- Dati casuali (non ordinati)
- Caso medio accettabile

**AVL:**
- Serve garanzia $O(\log n)$
- Search molto frequente (più di Insert/Delete)
- Dati potrebbero arrivare ordinati

**Red-Black Tree:** (non nel programma, ma utile sapere)
- Compromesso tra AVL e BST semplice
- Delete più frequente (meno rotazioni di AVL)

## Domande Tipiche d'Esame
> [!example] Esercizio 1.C - "Quale algoritmo/struttura useresti?"

**Domanda tipo:** "Costruire un heap binomiale contenente $n$ elementi"

**Risposta:**
- **Metodo 1:** $n$ Insert → $O(n \log n)$
- **Metodo 2:** Costruzione bottom-up → $O(n)$ (non richiesto)
- **Risposta esame:** $O(n \log n)$

**Domanda tipo:** "Fare il merge di due heap binomiali di dimensione $n_1$ e $n_2$"

**Risposta:** $O(\log(n_1 + n_2))$ ← Questo è il vantaggio degli heap binomiali!

**Domanda tipo:** "Implementare una coda con priorità che supporta merge frequente"

**Risposta:** Heap binomiale, perché merge costa $O(\log n)$ invece di $O(n)$

**Domanda tipo:** "Implementare un dizionario con $n$ elementi garantendo Search in $O(\log n)$ nel caso peggiore"

**Risposta:** AVL (o qualsiasi BST bilanciato), perché garantisce altezza $O(\log n)$

## Note Finali
> [!abstract] Riepilogo Generale
> **Strutture Dati Elementari:**
> - Pila: LIFO, $O(1)$ per push/pop
> - Coda: FIFO, $O(1)$ per enqueue/dequeue
> - Dizionario: varie implementazioni, trade-off search vs insert
> 
> **Alberi:**
> - BST: $O(h)$ operazioni, problema: $h$ può essere $n$
> - AVL: $h = O(\log n)$ garantito, rotazioni per bilanciare
> 
> **Code con Priorità:**
> - Heap binario: semplice, $O(\log n)$, merge $O(n)$
> - d-ary Heap: insert più veloce se $d$ grande
> - Heap binomiale: merge $O(\log n)$ ← vantaggio chiave
> - Heap Fibonacci: complessità ammortizzate migliori

> [!success] Cosa Studiare per l'Esame
> 1. **Priorità ALTA:**
>     - BST: operazioni, successor, delete con 3 casi
>     - AVL: 4 casi rotazione, insert (1 rot) vs delete (O(log n) rot)
>     - Heap binario: tutte le operazioni
>     - Tabella riassuntiva code con priorità
> 2. **Priorità MEDIA:**
>     - Heap binomiali: definizione, proprietà, merge
>     - Pila/Coda: implementazioni
>     - d-ary Heap: quando conviene
> 3. **Priorità BASSA:**
>     - Heap Fibonacci: solo tabella complessità
>     - Rappresentazioni alberi: vettore padri, posizionale