---
tags:
  - algoritmi
  - strutture-dati
slide: "8"
capitolo: "Demetrescu cap. 3"
---
# Strutture Dati Elementari e Dizionari
Questo capitolo introduce la distinzione fondamentale tra **tipo di dato** e **struttura dati**, e analizza le implementazioni elementari dei tipi di dato Dizionario, Pila e Coda. Le complessità sono espresse con la notazione asintotica di [[02 - Notazioni Asintotiche]]. Si esaminano poi le principali tecniche di rappresentazione degli alberi in memoria e gli algoritmi di visita (DFS e BFS), con applicazioni pratiche e pseudocodice tratto direttamente dalle slide del corso. Gli argomenti più avanzati — BST, AVL, heap e code con priorità — sono trattati nelle note successive [[06 - Alberi di Ricerca BST e AVL]] e [[07 - Code con Priorità e Heap]].
## Tipo di Dato vs Struttura Dati
> [!quote] Definizione — Tipo di Dato
> Un **tipo di dato** specifica una collezione di oggetti e le operazioni di interesse su tale collezione (es. `insert`, `delete`, `search`). Definisce *cosa* si può fare, non *come*.

> [!quote] Definizione — Struttura Dati
> Una **struttura dati** è un'organizzazione dei dati che permette di memorizzare la collezione e supportare le operazioni di un tipo di dato usando meno risorse di calcolo possibile. Definisce *come* i dati sono organizzati in memoria.

L'obiettivo del progettista è scegliere la struttura dati che minimizza il costo (tempo e spazio) delle operazioni richieste dal tipo di dato.
## Rappresentazioni Indicizzate e Collegate
Le strutture dati si dividono in due grandi famiglie.

**Rappresentazioni indicizzate** — i dati sono contenuti principalmente in array.
- Proprietà forte: gli indici delle celle sono numeri *consecutivi*.
- Proprietà debole: non è possibile aggiungere nuove celle (dimensione fissa; riallocazione richiede tempo lineare).
- Pro: accesso diretto ai dati in $O(1)$ tramite indice.
- Contro: dimensione fissa.

**Rappresentazioni collegate** — i dati sono in record collegati da puntatori.
- Proprietà forte: è possibile aggiungere e togliere record individualmente in $O(1)$.
- Proprietà debole: gli indirizzi dei record non sono necessariamente consecutivi.
- Pro: dimensione variabile.
- Contro: accesso sequenziale (no accesso diretto).

Esempi di strutture collegate: lista semplice, lista doppiamente collegata, lista circolare doppiamente collegata.
## Il Tipo di Dato Dizionario
> [!quote] Definizione — Dizionario
> Il tipo di dato **Dizionario** mantiene un insieme $S$ di coppie (elem, chiave) e supporta le seguenti operazioni:
> - `insert(elem e, chiave k)` — aggiunge a $S$ la coppia $(e, k)$.
> - `delete(chiave k)` — cancella da $S$ l'elemento con chiave $k$.
> - `search(chiave k)` — restituisce l'elemento con chiave $k$ se presente in $S$, altrimenti `null`.
### Implementazioni elementari del Dizionario
Di seguito le quattro implementazioni elementari con le relative complessità nel caso peggiore.
#### Array non ordinato
Metodo più semplice: array sovradimensionato, elementi inseriti in coda.
- `insert` → $O(1)$: inserisco dopo l'ultimo elemento.
- `search` → $O(n)$: devo scorrere tutto l'array.
- `delete` → $O(n)$: delete = search + cancellazione.
#### Array ordinato
- `search` → $O(\log n)$: ricerca binaria sfrutta l'ordine.
- `insert` → $O(n)$: $O(\log n)$ confronti per trovare la posizione + $O(n)$ trasferimenti per mantenere l'ordine (e $O(n) + O(\log n) = O(n)$).
- `delete` → $O(n)$: analogo a insert.
#### Lista non ordinata
- `search` → $O(n)$.
- `insert` → $O(1)$: inserisco in testa.
- `delete` → $O(n)$.
#### Lista ordinata
Non è possibile usare la ricerca binaria su una lista (manca accesso diretto), quindi:
- `search` → $O(n)$.
- `insert` → $O(n)$: devo mantenere la lista ordinata.
- `delete` → $O(n)$.
#### Tabella riassuntiva
| Implementazione | `search` | `insert` | `delete` |
|:---|:---:|:---:|:---:|
| Array non ordinato | $O(n)$ | $O(1)$ | $O(n)$ |
| Array ordinato | $O(\log n)$ | $O(n)$ | $O(n)$ |
| Lista non ordinata | $O(n)$ | $O(1)$ | $O(n)$ |
| Lista ordinata | $O(n)$ | $O(n)$ | $O(n)$ |
| **BST/AVL** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |

L'ultima riga anticipa il risultato degli [[06 - Alberi di Ricerca BST e AVL]]: per garantire $O(\log n)$ su tutte le operazioni occorrono strutture più sofisticate.

> [!warning] Lista ordinata non migliora la search
> L'ordinamento nella lista non porta vantaggi per la ricerca: senza accesso diretto alle celle non si può applicare la ricerca binaria. Si paga il costo di insert e delete senza guadagnare su search.
## Il Tipo di Dato Pila
> [!quote] Definizione — Pila (Stack)
> La **Pila** è un tipo di dato con politica LIFO (*Last In First Out*): l'ultimo elemento inserito è il primo ad essere estratto.
> Operazioni principali:
> - `push(e)` — inserisce l'elemento $e$ in cima.
> - `pop()` — rimuove e restituisce l'elemento in cima.
> - `top()` — restituisce l'elemento in cima senza rimuoverlo.
### Implementazione con array (indicizzata)
Si mantiene un indice `top` che punta all'ultimo elemento inserito.

```pseudo
\begin{algorithm}
\caption{push($P$, $e$)}
\begin{algorithmic}
\State $P.\text{top} \gets P.\text{top} + 1$
\State $P[P.\text{top}] \gets e$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{pop($P$)}
\begin{algorithmic}
\State $e \gets P[P.\text{top}]$
\State $P.\text{top} \gets P.\text{top} - 1$
\State \Return $e$
\end{algorithmic}
\end{algorithm}
```

Complessità: `push` → $O(1)$, `pop` → $O(1)$, `top` → $O(1)$.

> [!info] Pila con lista collegata
> In alternativa si usa una lista con inserimento e rimozione in testa: `push` = inserimento in testa $O(1)$, `pop` = rimozione in testa $O(1)$. Dimensione non prefissata.
## Il Tipo di Dato Coda
> [!quote] Definizione — Coda (Queue)
> La **Coda** è un tipo di dato con politica FIFO (*First In First Out*): il primo elemento inserito è il primo ad essere estratto.
> Operazioni principali:
> - `enqueue(e)` — inserisce $e$ in fondo alla coda.
> - `dequeue()` — rimuove e restituisce l'elemento in testa.
> - `first()` — restituisce l'elemento in testa senza rimuoverlo.
### Implementazione con array circolare
Si usano due indici, `head` e `tail`, in un array di dimensione $n$ con aritmetica modulo $n$.

```pseudo
\begin{algorithm}
\caption{enqueue($C$, $e$)}
\begin{algorithmic}
\State $C[C.\text{tail}] \gets e$
\State $C.\text{tail} \gets (C.\text{tail} + 1) \bmod n$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{dequeue($C$)}
\begin{algorithmic}
\State $e \gets C[C.\text{head}]$
\State $C.\text{head} \gets (C.\text{head} + 1) \bmod n$
\State \Return $e$
\end{algorithmic}
\end{algorithm}
```

Complessità: `enqueue` → $O(1)$, `dequeue` → $O(1)$, `first` → $O(1)$.

> [!info] Coda con lista collegata
> In alternativa: lista con due puntatori `head` e `tail`. `enqueue` inserisce in fondo ($O(1)$ con puntatore `tail`), `dequeue` rimuove dalla testa ($O(1)$).

> [!question] Domanda tipica d'esame — Pila e Coda
> D: Progettare strutture dati indicizzate e collegate per Pila e Coda con tutte le operazioni in $O(1)$.
> R: Con array, la Pila usa un indice `top` (push/pop in $O(1)$); la Coda usa un array circolare con indici `head` e `tail` (enqueue/dequeue in $O(1)$). Con liste, sia Pila che Coda inseriscono/rimuovono in testa/coda in $O(1)$ mantenendo i puntatori opportuni.
## Alberi: Definizioni e Terminologia
Un **albero radicato** è un'organizzazione gerarchica dei dati: i dati sono contenuti nei nodi, le relazioni gerarchiche sono definite dagli archi.
- **Radice** — nodo senza padre.
- **Foglia** — nodo senza figli.
- **Nodo interno** — nodo con almeno un figlio.
- **Grado di un nodo** — numero dei suoi figli.
- **Altezza** — massima distanza tra la radice e una foglia; per convenzione l'albero vuoto ha altezza $-1$.
- **Antenato/Discendente** — $u$ è antenato di $v$ se $u$ è raggiungibile da $v$ risalendo di padre in padre; $v$ è discendente di $u$ se $u$ è antenato di $v$.
- **Albero $d$-ario** — albero in cui ogni nodo ha al più $d$ figli; **albero $d$-ario completo** se ogni nodo interno ha esattamente $d$ figli e tutte le foglie sono allo stesso livello.
## Tecniche di Rappresentazione degli Alberi
### Vettore dei padri
Per un albero con $n$ nodi si usa un array $P$ di dimensione almeno $n$. Ogni cella $i$ contiene una coppia $(\text{info}, \text{parent})$:
- `P[i].info` — contenuto informativo del nodo $i$.
- `P[i].parent` — indice nell'array del nodo padre di $i$ (la radice ha `parent = null`).

Complessità delle operazioni:
- trovare il padre di un nodo: $O(1)$ (accesso diretto a `P[i].parent`).
- trovare i figli di un nodo: $O(n)$ (bisogna scorrere l'intero array).

Numero di figli: arbitrario (nessun vincolo sulla struttura dell'albero).

> [!info] Utilizzo tipico del vettore dei padri
> Il vettore dei padri è ideale per algoritmi bottom-up come Union-Find (struttura Disjoint Set). Si veda anche l'esercizio di ri-radicazione più avanti.
### Vettore posizionale (per alberi $d$-ari quasi completi)
I nodi sono disposti nell'array per livelli successivi (la radice al livello 0 è in posizione 0 o 1 a seconda della convenzione). Dato un nodo $i$:

Con indici a partire da **0**:
- $j$-esimo figlio (con $j \in \{1, \dots, d\}$): posizione $d \cdot i + j$.
- padre di $i$: posizione $\lfloor (i-1)/d \rfloor$.

Con indici a partire da **1**:
- $j$-esimo figlio: posizione $d(i-1) + j + 1$.
- padre di $i$: posizione $\lfloor (i-2)/d \rfloor + 1$.

Complessità: trovare padre e figlio $j$-esimo entrambi in $O(1)$.

> [!warning] Spreco di spazio su alberi non completi
> Il vettore posizionale funziona bene solo per alberi completi o quasi completi. Un albero di $n$ nodi che è una catena (ogni nodo ha al più un figlio) ha altezza $n-1$: l'albero binario completo di altezza $n-1$ ha $2^n - 1$ nodi, quindi la dimensione del vettore posizionale cresce esponenzialmente nel numero di nodi. Il vettore posizionale è la struttura usata per gli [[07 - Code con Priorità e Heap|heap]].
### Rappresentazioni collegate (puntatori ai figli)
Per alberi con numero **limitato** di figli si usa un record per nodo con puntatori diretti ai figli (es. figlio sinistro e destro per alberi binari).

Per alberi con numero **arbitrario** di figli:
- lista di puntatori ai figli: il nodo contiene un puntatore alla lista dei propri figli.
- rappresentazione primo figlio–fratello successivo: ogni nodo ha due puntatori, uno al primo figlio e uno al fratello successivo.

Tutte le rappresentazioni collegate possono essere arricchite con un puntatore al padre in ogni nodo, per accedere al padre in $O(1)$.
### Tabella riassuntiva delle rappresentazioni
| Rappresentazione | Padre$(u)$ | Figlio $j$-esimo$(u)$ | Numero figli | Ideale per |
|:---|:---:|:---:|:---:|:---|
| Vettore dei padri | $O(1)$ | $O(n)$ | arbitrario | algoritmi bottom-up |
| Vettore posizionale | $O(1)$ | $O(1)$ | esattamente $d$ | alberi $d$-ari quasi completi (heap) |
| Puntatori ai figli | $O(1)^*$ | $O(1)$ | limitato (es. binari) | alberi binari, BST, AVL |
| Lista puntatori / primo figlio–fratello | $O(1)^*$ | $O(\text{grado})$ | arbitrario | alberi generici |

$^*$ Richiede puntatore `parent` esplicito nel nodo.
## Visite di Alberi
> [!quote] Definizione — Visita di un Albero
> Gli **algoritmi di visita** consentono l'accesso sistematico a tutti i nodi e gli archi di un albero. Si distinguono in base all'ordine in cui i nodi vengono visitati.
### Visita in Profondità (DFS)
L'algoritmo di visita in profondità (**DFS**, *Depth-First Search*) parte dalla radice $r$ e procede visitando nodi di figlio in figlio fino a raggiungere una foglia. Retrocede poi al primo antenato con figli non visitati e ripete.

**Versione iterativa** con Pila (per alberi binari; nella pila vengono inseriti anche i nodi `null`):

```pseudo
\begin{algorithm}
\caption{DFS($r$)}
\begin{algorithmic}
\State Pila $S$
\State \Call{S.push}{$r$}
\While{$S$ non vuota}
  \State $u \gets$ \Call{S.pop}{}
  \If{$u \neq \text{null}$}
    \State \Call{visita}{$u$}
    \State \Call{S.push}{figlio destro di $u$}
    \State \Call{S.push}{figlio sinistro di $u$}
  \EndIf
\EndWhile
\end{algorithmic}
\end{algorithm}
```

Complessità: ogni nodo (e ogni `null`) è inserito ed estratto dalla pila una sola volta → $O(1)$ per nodo → $T(n) = O(n)$.

**Versione ricorsiva** con i tre ordini di visita (per alberi binari):

```pseudo
\begin{algorithm}
\caption{DFSRicorsiva($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return
\EndIf
\State \Call{visita}{$r$} \Comment{preordine}
\State \Call{DFSRicorsiva}{figlio sinistro di $r$}
\State \Call{DFSRicorsiva}{figlio destro di $r$}
\end{algorithmic}
\end{algorithm}
```

Lo pseudocodice mostra la **visita in preordine**; spostando l'unica riga `visita(r)` si ottengono gli altri due ordini (come sulle slide del corso):
- **Preordine**: `visita(r)` *prima* delle due chiamate ricorsive → radice → sottoalbero sinistro → sottoalbero destro.
- **Visita simmetrica** (in-order): `visita(r)` *tra* le due chiamate → sottoalbero sinistro → radice → sottoalbero destro.
- **Postordine**: `visita(r)` *dopo* entrambe le chiamate → sottoalbero sinistro → sottoalbero destro → radice.

> [!example] Ordini di visita sull'albero di esempio
> Considerare l'albero binario con radice A, figlio sinistro L (con figli E e R) e figlio destro B (con figlio destro O):
> ```
>        A
>       / \
>      L   B
>     / \   \
>    E   R   O
> ```
> Preordine:    A, L, E, R, B, O
> Simmetrica:   E, L, R, A, B, O
> Postordine:   E, R, L, O, B, A
### Visita in Ampiezza (BFS)
L'algoritmo di visita in ampiezza (**BFS**, *Breadth-First Search*) parte dalla radice e visita i nodi per livelli successivi. Un nodo al livello $i$ viene visitato solo dopo che tutti i nodi al livello $i-1$ sono stati visitati.

**Versione iterativa** con Coda (nella coda vengono inseriti solo nodi non `null`):

```pseudo
\begin{algorithm}
\caption{BFS($r$)}
\begin{algorithmic}
\State Coda $Q$
\State \Call{Q.enqueue}{$r$}
\While{$Q$ non vuota}
  \State $u \gets$ \Call{Q.dequeue}{}
  \State \Call{visita}{$u$}
  \ForAll{figlio $v$ di $u$ (non null)}
    \State \Call{Q.enqueue}{$v$}
  \EndFor
\EndWhile
\end{algorithmic}
\end{algorithm}
```

Complessità: ogni nodo è inserito ed estratto dalla coda una sola volta → $O(1)$ per nodo → $T(n) = O(n)$.

> [!example] Ordine di visita BFS
> Sull'albero dell'esempio precedente: A, L, B, E, R, O (livello per livello).

> [!info] DFS vs BFS — ruolo delle strutture dati
> La DFS usa una **Pila** (o la pila di sistema della ricorsione): elabora in profondità. La BFS usa una **Coda**: elabora per larghezza. Questo dualismo Pila/DFS e Coda/BFS ricompare nella visita dei grafi in [[08 - Grafi e Visite]].
## Applicazioni delle Visite
### Calcolo dell'altezza
L'altezza si calcola con una visita in postordine (bottom-up): prima si calcolano le altezze dei sottoalberi, poi si combina.

```pseudo
\begin{algorithm}
\caption{CalcolaAltezza($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $-1$
\EndIf
\State $sin \gets$ \Call{CalcolaAltezza}{figlio sinistro di $r$}
\State $des \gets$ \Call{CalcolaAltezza}{figlio destro di $r$}
\State \Return $1 + \max\{sin, des\}$
\end{algorithmic}
\end{algorithm}
```

Caso base: nodo `null` restituisce $-1$. Una foglia (entrambi i figli `null`) restituisce $1 + \max(-1, -1) = 0$.

Complessità: $O(n)$ — ogni nodo visitato esattamente una volta.
### Calcolo del numero di foglie (Problema 3.6.1)
```pseudo
\begin{algorithm}
\caption{CalcolaNumFoglie($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $0$
\EndIf
\If{$r$ è una foglia}
  \State \Return $1$
\EndIf
\State $sin \gets$ \Call{CalcolaNumFoglie}{figlio sinistro di $r$}
\State $des \gets$ \Call{CalcolaNumFoglie}{figlio destro di $r$}
\State \Return $sin + des$
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(n)$.
### Calcolo del grado medio (Problema 3.6.2)
Il **grado medio** dei nodi non foglia è il rapporto tra la somma dei gradi di tutti i nodi e il numero di nodi interni ($n - n_{\text{foglie}}$).

```pseudo
\begin{algorithm}
\caption{CalcolaGradoMedio($r$)}
\begin{algorithmic}
\State $n \gets$ numero di nodi dell'albero
\State $nfoglie \gets$ \Call{CalcolaNumFoglie}{$r$}
\If{$r \neq \text{null}$}
  \State \Return \Call{SommaGradi}{$r$} $/ (n - nfoglie)$
\EndIf
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{SommaGradi($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $0$
\EndIf
\If{$r$ è una foglia}
  \State \Return $0$
\EndIf
\State $S \gets$ numero figli di $r$ $+$ \Call{SommaGradi}{figlio sinistro di $r$} $+$ \Call{SommaGradi}{figlio destro di $r$}
\State \Return $S$
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(n)$.
### Ricerca di un elemento (Problema 3.6.3)
Ricerca in un albero generico (non BST): visita DFS, si esplora prima il sottoalbero sinistro e, solo se non trovato, il destro (cortocircuito).

```pseudo
\begin{algorithm}
\caption{CercaElemento($r$, $k$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $\text{null}$
\EndIf
\If{$\text{chiave}(r) = k$}
  \State \Return $r$
\EndIf
\State $sin \gets$ \Call{CercaElemento}{figlio sinistro di $r$, $k$}
\If{$sin \neq \text{null}$}
  \State \Return $sin$
\EndIf
\State \Return \Call{CercaElemento}{figlio destro di $r$, $k$}
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(n)$ nel caso peggiore (chiave assente).
### Ri-radicazione con vettore dei padri (Esercizio)
Dato un albero $T$ con vettore dei padri e radice $r$, si vuole restituire il vettore dei padri di $T$ radicato in un nuovo nodo $r'$.

**Osservazione chiave**: i soli nodi che cambiano padre sono quelli lungo il cammino da $r'$ a $r$. L'algoritmo inverte i puntatori lungo questo cammino.

```pseudo
\begin{algorithm}
\caption{RiRadica($T$, $j$)}
\begin{algorithmic}
\State $x \gets j$
\State $px \gets T[j].\text{parent}$
\State $T[j].\text{parent} \gets \text{null}$
\While{$px \neq \text{null}$}
  \State $y \gets T[px].\text{parent}$
  \State $T[px].\text{parent} \gets x$
  \State $x \gets px$
  \State $px \gets y$
\EndWhile
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(h)$, dove $h$ è l'altezza di $T$ rispetto alla radice $r$ originale (si percorre al più il cammino radice–$r'$).

> [!question] Domanda tipica d'esame — Ricostruzione dell'albero dalle visite (Problema 3.7)
> D: Dati gli ordini di visita simmetrica `G D H B A E C J I K F` e preordine `A B D G H C E F I J K`, ricostruire l'albero binario $T$.
> R: La radice è il primo nodo del preordine (A). La simmetrica divide i nodi in sottoalbero sinistro (G D H B) e destro (E C J I K F) rispetto ad A. Si procede ricorsivamente: il secondo nodo del preordine (B) è radice del sottoalbero sinistro; nella simmetrica B separa (G D H) a sinistra e vuoto a destra. E così via. La radice del sottoalbero destro è C (terzo nodo del preordine dopo aver esaurito il ramo sinistro).

> [!warning] Preordine + postordine non bastano in generale
> Con preordine e postordine non è sempre possibile ricostruire univocamente l'albero binario: se un nodo ha un solo figlio, non si riesce a determinare se è figlio sinistro o destro. Servono preordine + simmetrica oppure simmetrica + postordine.
