---
tags:
  - algoritmi
  - dfs
slide: "13"
capitolo: "Dasgupta-Papadimitriou-Vazirani cap. 3"
---
# Applicazioni della DFS
Questa nota approfondisce gli usi meno scontati della visita in profondità, basandosi sul capitolo 3 del libro *Algorithms* di Dasgupta, Papadimitriou e Vazirani (McGraw-Hill). Vedremo come la [[08 - Grafi e Visite|DFS]], arricchita di un semplice contatore di tempo, permette di classificare gli archi di un grafo, rilevare cicli, calcolare ordinamenti topologici e trovare componenti fortemente connesse — tutto in tempo $\Theta(n+m)$ (notazione in [[02 - Notazioni Asintotiche]]).
## Tempi di visita: pre(v) e post(v)
Durante la DFS si mantiene una variabile globale **clock** inizializzata a 1. Ogni volta che si *scopre* un nodo $v$ si registra $\text{pre}(v) = \text{clock}$ e si incrementa clock; ogni volta che si *abbandona* $v$ (backtracking) si registra $\text{post}(v) = \text{clock}$ e si incrementa di nuovo.

```pseudo
\begin{algorithm}
\caption{visitaDFSRicorsiva($v$, $T$) — arricchita con clock}
\begin{algorithmic}
\State marca $v$
\State $\text{pre}(v) \gets \text{clock}$; $\text{clock} \gets \text{clock} + 1$
\ForAll{arco $(v, w) \in G$}
  \If{$w$ non è marcato}
    \State aggiungi $(v, w)$ a $T$
    \State \Call{visitaDFSRicorsiva}{$w, T$}
  \EndIf
\EndFor
\State $\text{post}(v) \gets \text{clock}$; $\text{clock} \gets \text{clock} + 1$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{VisitaDFS($G$) — gestisce nodi non raggiungibili}
\begin{algorithmic}
\ForAll{nodo $v \in G$}
  \State imposta $v$ come non marcato
\EndFor
\State $\text{clock} \gets 1$
\State $F \gets$ foresta vuota
\ForAll{nodo $v \in G$}
  \If{$v$ è non marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $F$
  \EndIf
\EndFor
\State \Return $F$
\end{algorithmic}
\end{algorithm}
```

- $\text{pre}(v)$: **tempo di scoperta** — quando la DFS entra in $v$ per la prima volta.
- $\text{post}(v)$: **tempo di abbandono** — quando la DFS finisce di esplorare $v$ e tutti i suoi discendenti.

> [!quote] Proprietà — Intervalli annidati
> Per ogni coppia di nodi $u$ e $v$, gli intervalli $[\text{pre}(u), \text{post}(u)]$ e $[\text{pre}(v), \text{post}(v)]$ o sono **disgiunti** o l'uno è **contenuto** nell'altro. Non possono sovrapporsi parzialmente.
> **Conseguenza:** $u$ è antenato di $v$ nell'albero DFS se e solo se
> $$\text{pre}(u) < \text{pre}(v) < \text{post}(v) < \text{post}(u).$$
## Classificazione degli archi
In un grafo **diretto**, ogni arco $(u, v)$ viene incontrato durante la DFS e può essere classificato in base ai valori $\text{pre}$ e $\text{post}$:
| Tipo di arco | Condizione sui tempi | Descrizione |
|---|---|---|
| **Arco dell'albero** | $u$ scopre $v$ direttamente | $(u,v)$ entra nell'albero DFS |
| **In avanti** | $\text{pre}(u) < \text{pre}(v) < \text{post}(v) < \text{post}(u)$ | $u$ è antenato di $v$, ma $(u,v)$ non è nell'albero |
| **All'indietro** | $\text{pre}(v) < \text{pre}(u) < \text{post}(u) < \text{post}(v)$ | $v$ è antenato di $u$ (arco che "risale") |
| **Trasversale** | $[\text{pre}(v), \text{post}(v)]$ disgiunto da $[\text{pre}(u), \text{post}(u)]$, con $\text{post}(v) < \text{pre}(u)$ | né antenato né discendente |

> [!info] Archi nei grafi non orientati
> In un grafo non orientato, la DFS produce solo archi dell'albero e **archi all'indietro** (non esistono archi in avanti né trasversali). Questo perché ogni arco $\{u,v\}$ viene percorso in entrambe le direzioni, e se $v$ è già marcato quando si visita da $u$, allora $v$ è necessariamente un antenato di $u$.
## Rilevamento di cicli
> [!quote] Proprietà — Cicli e archi all'indietro
> Un grafo diretto $G$ ha un **ciclo** se e solo se la visita DFS rivela almeno un **arco all'indietro**.

**Dimostrazione ($\Rightarrow$):** se esiste un arco all'indietro $(u, v)$ con $v$ antenato di $u$, allora il cammino da $v$ a $u$ nell'albero DFS, seguito dall'arco $(u, v)$, forma un ciclo.

**Dimostrazione ($\Leftarrow$):** sia $\langle v_0, v_1, \ldots, v_k = v_0 \rangle$ un ciclo. Sia $v_i$ il primo nodo del ciclo scoperto dalla DFS. Poiché $v_{i-1}$ è raggiungibile da $v_i$, la DFS visita $v_{i-1}$ prima di abbandonare $v_i$, quindi $v_i$ è ancora "aperto" quando si attraversa l'arco $(v_{i-1}, v_i)$, che risulta perciò un arco all'indietro.

> [!question] Domanda tipica d'esame — Rilevamento ciclo
> D: Come si verifica in tempo $\Theta(n+m)$ se un grafo diretto $G$ contiene un ciclo?
> R: Si esegue una visita DFS completa (dalla procedura `VisitaDFS` che gestisce nodi non raggiungibili). Durante la visita si controlla se viene incontrato un arco $(u, v)$ tale che $v$ è già marcato ma $\text{post}(v)$ non è ancora stato impostato (cioè $v$ è ancora "in pila"). Se sì, $(u,v)$ è un arco all'indietro e il grafo ha un ciclo. La complessità è $\Theta(n+m)$.
## Ordinamento topologico
> [!quote] Definizione — DAG
> Un **grafo diretto aciclico** (DAG, *Directed Acyclic Graph*) è un grafo diretto $G$ che non contiene cicli diretti.

> [!quote] Definizione — Ordinamento topologico
> Un **ordinamento topologico** di un grafo diretto $G = (V, E)$ è una funzione biettiva $\sigma: V \to \{1, 2, \ldots, n\}$ tale che per ogni arco $(u, v) \in E$ si abbia $\sigma(u) < \sigma(v)$.

Un ordinamento topologico rappresenta un modo di "linearizzare" i nodi del grafo rispettando tutte le dipendenze: se $u$ deve precedere $v$, allora $u$ appare prima. L'applicazione classica sono le **reti delle dipendenze**: i nodi sono compiti, e un arco $(u, v)$ significa che $u$ va eseguito prima di $v$.

Nodi particolari in un DAG:
- **Sorgente**: nodo con solo archi *uscenti* (in-degree 0).
- **Pozzo**: nodo con solo archi *entranti* (out-degree 0).

> [!quote] Teorema — Caratterizzazione dei DAG
> Un grafo diretto $G$ ammette un ordinamento topologico **se e solo se** $G$ è un DAG.
>
> **Dim ($\Rightarrow$):** per assurdo, se $G$ ammette un ordinamento $\sigma$ e contiene un ciclo $\langle v_0, v_1, \ldots, v_k = v_0 \rangle$, allora $\sigma(v_0) < \sigma(v_1) < \ldots < \sigma(v_{k-1}) < \sigma(v_k) = \sigma(v_0)$, contraddizione.
> **Dim ($\Leftarrow$):** costruttiva — vedi algoritmo sotto.
### Algoritmo via DFS (post-order decrescente)
L'idea chiave: in un DAG, il nodo che viene abbandonato per **ultimo** dalla DFS (il più alto valore $\text{post}$) deve essere una sorgente nell'ordinamento topologico. Basta quindi restituire i nodi in ordine **decrescente** di $\text{post}(v)$.

```pseudo
\begin{algorithm}
\caption{OrdinamentoTopologico($G$)}
\begin{algorithmic}
\State $\text{top} \gets n$; $L \gets$ lista vuota
\State esegui \Call{VisitaDFS}{$G$}, ma al momento di impostare $\text{post}(v)$:
\State \hspace{1em} $\sigma(v) \gets \text{top}$
\State \hspace{1em} $\text{top} \gets \text{top} - 1$
\State \hspace{1em} aggiungi $v$ in testa alla lista $L$
\State \Return $L$ e $\sigma$
\end{algorithmic}
\end{algorithm}
```

**Complessità temporale:** $\Theta(n+m)$ con liste di adiacenza (identico alla DFS base).

**Correttezza:** per ogni arco $(u, v)$ in un DAG non esistono archi all'indietro (dimostrato sopra), quindi quando si attraversa $(u, v)$ durante la DFS, $v$ viene completamente visitato prima di $u$, ovvero $\text{post}(v) < \text{post}(u)$. Nell'ordinamento per $\text{post}$ decrescente, $u$ precede $v$, soddisfacendo la condizione $\sigma(u) < \sigma(v)$.

> [!info] Algoritmo alternativo (rimozione iterativa di sorgenti)
> Si può calcolare l'ordinamento topologico anche senza DFS: si estrae ripetutamente un nodo senza archi entranti, lo si appende all'ordinamento e si rimuovono i suoi archi uscenti. Se il grafo non diventa vuoto al termine, il grafo contiene un ciclo.
> Complessità: $\Theta(n+m)$ se si mantiene una struttura dati per le sorgenti.

> [!question] Domanda tipica d'esame — Ordinamento topologico
> D: Dato un DAG $G$, si esegue `VisitaDFS`. Il nodo $v$ con il massimo valore $\text{post}(v)$ che posizione occupa nell'ordinamento topologico?
> R: Occupa la posizione 1 (la prima), ossia è una sorgente. Poiché non esistono archi all'indietro in un DAG, quando la DFS abbandona $v$ per ultima, significa che $v$ non è discendente di nessun altro nodo nell'albero DFS — quindi non esiste un arco entrante in $v$ da nodi non ancora completati. In un DAG questo implica che $v$ è una sorgente.
## Componenti fortemente connesse
> [!quote] Definizione — Componente fortemente connessa
> Una **componente fortemente connessa** (CFC) di un grafo diretto $G = (V, E)$ è un insieme **massimale** di vertici $C \subseteq V$ tale che per ogni coppia $u, v \in C$ esiste un cammino da $u$ a $v$ e da $v$ a $u$.
> *Massimale* significa che aggiungere qualunque altro vertice a $C$ viola la proprietà di mutua raggiungibilità.

Il **grafo delle componenti fortemente connesse** di $G$ ha un nodo per ogni CFC e un arco da $C$ a $C'$ se esiste almeno un arco in $G$ da un nodo di $C$ a un nodo di $C'$. Questo grafo è sempre un **DAG** (altrimenti le due componenti collasserebbero in una sola).

Una componente è **pozzo** se ha solo archi entranti nel grafo delle CFC; è **sorgente** se ha solo archi uscenti.
### Idea dell'algoritmo
L'algoritmo di Kosaraju si basa su tre proprietà:

**Proprietà 1:** se si esegue `visitaDFSRicorsiva` a partire da $u$, la procedura termina dopo aver visitato tutti i nodi raggiungibili da $u$ (e solo quelli).

**Proprietà 2:** se $C$ e $C'$ sono due CFC con un arco da $C$ verso $C'$, allora il massimo valore $\text{post}$ in $C$ è **maggiore** del massimo valore $\text{post}$ in $C'$.

> [!quote] Proprietà — Relazione tra post e componenti
> Siano $C$ e $C'$ due CFC tali che esiste un arco da un nodo di $C$ verso un nodo di $C'$. Allora $\max_{u \in C} \text{post}(u) > \max_{u \in C'} \text{post}(u)$.
> **Dim:** se la DFS visita prima $C'$ poi $C$: quando inizia $C$, tutti i nodi di $C'$ sono già completati, quindi il massimo $\text{post}$ di $C$ è più grande. Se la DFS visita prima $C$ poi $C'$: la DFS, partendo da un nodo di $C$, raggiunge $C'$ (c'è un arco), visita tutti i nodi di $C'$ e li chiude prima di chiudere il nodo di $C$ da cui è partita — quindi il massimo $\text{post}$ di $C$ è ancora più grande.

**Proprietà 3:** il nodo con il massimo valore $\text{post}$ globale appartiene a una **componente sorgente**.

L'idea è partire da una componente **pozzo** (più semplice da estrarre), fare una DFS da lì, raccoglierne tutti i nodi, e ripetere. Per trovare una componente pozzo senza cercarla direttamente, si usa il **grafo inverso** $G^R$: stesso insieme di nodi, stessi archi ma con direzione invertita.

> [!info] Grafo inverso e CFC
> Le CFC di $G^R$ sono le **stesse** di $G$ (la mutua raggiungibilità è simmetrica per inversione degli archi). Però le componenti sorgente di $G$ diventano componenti pozzo in $G^R$ e viceversa. Quindi il nodo con il massimo $\text{post}$ in $G^R$ appartiene a una **sorgente** di $G^R$, che corrisponde a un **pozzo** di $G$ — esattamente ciò di cui abbiamo bisogno.
### Algoritmo di Kosaraju
```pseudo
\begin{algorithm}
\caption{ComponentiFortementeConnesse($G$)}
\begin{algorithmic}
\State calcola $G^R$ \Comment{grafo con archi invertiti}
\State \Call{VisitaDFS}{$G^R$} \Comment{calcola i valori $\text{post}(v)$ in $G^R$}
\State \Return \Call{CompConnesse}{$G$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{CompConnesse($G$)}
\begin{algorithmic}
\ForAll{nodo $v \in G$}
  \State imposta $v$ come non marcato
\EndFor
\State $\text{Comp} \gets$ insieme vuoto
\ForAll{nodo $v$ in ordine decrescente di $\text{post}(v)$ calcolato su $G^R$}
  \If{$v$ è non marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $\text{Comp}$
  \EndIf
\EndFor
\State \Return $\text{Comp}$
\end{algorithmic}
\end{algorithm}
```

**Complessità temporale:** $\Theta(n+m)$ — si eseguono due DFS complete più la costruzione di $G^R$, ognuna $\Theta(n+m)$ con liste di adiacenza.

**Correttezza (schizzo):** all'iterazione $i$ di `CompConnesse`, il nodo $v$ non marcato con il più alto $\text{post}$ in $G^R$ appartiene a una CFC che è un **pozzo** in $G$ (per la Proprietà 3 applicata a $G^R$). La DFS da $v$ in $G$ non può uscire da questa CFC — uscire significherebbe raggiungere un'altra CFC con un arco uscente, ma quella CFC è già stata estratta nelle iterazioni precedenti (i suoi nodi sono marcati). Quindi la DFS raccoglie esattamente la CFC di $v$.

> [!example] Esercizio rielaborato — Identificare le CFC
> Sia dato il grafo diretto $G$ con nodi $\{A, B, C, D, E\}$ e archi:
> $(A,B), (B,C), (C,A), (B,D), (D,E), (E,D)$.
>
> 1. Individuare le CFC a mano.
> 2. Costruire $G^R$ e indicare l'ordine in cui `VisitaDFS(GR)` potrebbe visitare i nodi, mostrando i valori $\text{post}$.
> 3. Indicare in quale ordine `CompConnesse` visiterebbe le CFC in $G$.
>
> **Soluzione:**
> Le CFC sono: $C_1 = \{A, B, C\}$ (ciclo $A \to B \to C \to A$), $C_2 = \{D, E\}$ (ciclo $D \to E \to D$).
> Nel grafo delle CFC esiste l'arco $C_1 \to C_2$ (via $B \to D$), quindi $C_1$ è sorgente e $C_2$ è pozzo.
> In $G^R$ la situazione si inverte: $C_2$ diventa sorgente e $C_1$ diventa pozzo.
> `VisitaDFS(GR)` assegna il massimo $\text{post}$ a un nodo di $C_2$. Quindi `CompConnesse` visita prima $C_2$ in $G$ (componente pozzo), poi $C_1$.

> [!warning] Errore comune — Confondere il grafo su cui si calcolano i post
> I valori $\text{post}(v)$ nell'algoritmo di Kosaraju vengono calcolati su **$G^R$**, non su $G$. La seconda DFS (quella che raccoglie le componenti) viene eseguita invece su **$G$**, usando quell'ordinamento. Invertire i due grafi dà risultati errati.
## Riepilogo delle complessità
| Applicazione | Complessità | Note |
|---|---|---|
| Tempi $\text{pre}/\text{post}$ | $\Theta(n+m)$ | overhead costante sulla DFS base |
| Rilevamento cicli | $\Theta(n+m)$ | basta verificare archi all'indietro |
| Ordinamento topologico | $\Theta(n+m)$ | DFS + ordine $\text{post}$ decrescente |
| CFC (Kosaraju) | $\Theta(n+m)$ | due DFS + costruzione $G^R$ |

Tutti i risultati assumono rappresentazione con **liste di adiacenza**; con matrice di adiacenza le complessità diventano $\Theta(n^2)$.
