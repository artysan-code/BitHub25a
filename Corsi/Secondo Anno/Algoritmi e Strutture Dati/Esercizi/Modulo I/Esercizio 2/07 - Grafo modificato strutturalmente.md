---
tags:
  - algoritmi
---
# Grafo modificato strutturalmente
Esercizio di progettazione su grafi (casistica [[Casistiche d'Esame Modulo I|grafo modificato strutturalmente]]): si **aggiungono archi** al grafo dato secondo una regola del problema e poi si applica un algoritmo standard (forte connessione, BFS/Dijkstra). Il punto chiave è che gli archi extra siano $O(m)$ o $O(n)$, così le dimensioni non esplodono. Ripasso: [[08 - Grafi e Visite]], [[10 - Cammini Minimi e Dijkstra]]; checklist [[Piano Esame ASD - Modulo I]].

> [!info] Schema comune del pattern
> Lo schema è sempre in due tempi: **(1) costruisci $G'$** aggiungendo a $G$ gli archi dettati dalla regola del problema; **(2) lancia un algoritmo standard** su $G'$ (Componenti Fortemente Connesse, BFS o Dijkstra), che si **richiama** senza riscriverlo. La parte da progettare è solo la costruzione di $G'$ e la cura che gli archi aggiunti siano $O(m)$ o $O(n)$: se esplodessero (es. $O(n^2)$) si perderebbe il bound. La logica del problema sta tutta in *quali* archi aggiungere e *con che peso/direzione*.
## Pattern A — archi inversi sui nodi speciali + forte connessione
> [!question] Traccia — 18/07/2022
> Dato un grafo diretto $G=(V,E)$ con $n$ nodi e $m$ archi e un sottoinsieme $S\subseteq V$ di nodi "speciali", si definisce il grafo $G'=(V,E')$ in cui $E'$ contiene tutti gli archi di $E$ e, per ogni arco $(v,x)\in E$ con $x\in S$, anche l'arco inverso $(x,v)$. Determinare se $G'$ è fortemente connesso. L'algoritmo deve operare in $O(n+m)$.

**Idea.** Si costruisce $G'$ scandendo $E$ una sola volta: ogni arco $(v,x)$ viene copiato in $E'$; se $x\in S$ (test $O(1)$ con array booleano su $S$, indicizzato per nodo) si aggiunge anche l'arco inverso $(x,v)$. Ogni arco originale genera al più un arco extra, quindi $|E'|=O(m)$ e $|V'|=n$: le dimensioni del grafo non esplodono. Su $G'$ si esegue l'algoritmo **Componenti Fortemente Connesse**: se restituisce una sola CFC il grafo è fortemente connesso.

> [!info] Le variabili e il conto degli archi
> - $E'$ = nuovo insieme di archi (copia di $E$ + gli inversi). $G' = (V, E')$ ha gli **stessi** $n$ nodi.
> - Test $x \in S$ in $O(1)$: si precalcola un array booleano `speciale[1..n]` da $S$ (i nodi sono interi in $[1,n]$, quindi l'array indicizzato per nodo basta — nessun hash).
> - **Conto chiave**: ogni arco originale produce al più $1$ inverso → $|E'| \le 2m = O(m)$. È questo a mantenere il costo $O(n+m)$.
> - $G'$ è fortemente connesso $\iff$ ha **una sola** componente fortemente connessa: si richiama `ComponentiFortementeConnesse` e si controlla $|\mathit{cfc}| = 1$.

```pseudo
\begin{algorithm}
\caption{GrafoModificato($G$, $S$) → booleano}
\begin{algorithmic}
\State $E' \gets \emptyset$
\For{ogni arco $(v,x)\in E$}
  \State aggiungi $(v,x)$ a $E'$
  \If{$x\in S$}
    \State aggiungi $(x,v)$ a $E'$ \Comment{mossa inversa: nodo speciale}
  \EndIf
\EndFor
\State $G' \gets (V,\,E')$
\State $\mathit{cfc} \gets$ \Call{ComponentiFortementeConnesse}{$G'$}
\State \Return $|\mathit{cfc}| = 1$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n+m)$ — la costruzione di $G'$ scandisce $E$ in $O(m)$; l'algoritmo Componenti Fortemente Connesse opera in $O(n+m)$ su $G'$ che ha $n$ nodi e $O(m)$ archi.
**Trappola:** aggiungere l'arco inverso per *ogni* coppia $(x,v)$ con $x\in S$ e $v\in V$ (indipendentemente dall'esistenza di $(v,x)$ in $E$) farebbe esplodere $|E'|$ a $O(n\cdot|S|)=O(n^2)$; la regola si applica esclusivamente agli archi già presenti in $E$.
## Pattern B — archi di teletrasporto + cammino minimo
> [!question] Traccia — 27/09/2023
> Un labirinto è un grafo non orientato $G=(V,E)$; si parte da $s$ e l'uscita è in $t$, ogni arco costa $1$ minuto. C'è un nodo speciale $p$ (teletrasporto) e un insieme $U\subseteq V$ di uscite del teletrasporto: stando su $p$ ci si può teletrasportare in un qualsiasi $q\in U$ al costo di $3$ minuti. Calcolare la strategia più veloce per uscire, se esiste.

**Idea.** Si aggiungono al grafo gli **archi di teletrasporto**: un arco *diretto* $p\to q$ di peso $3$ per ogni $q\in U$ (gli archi del labirinto restano non orientati, peso $1$). Sul grafo pesato risultante si esegue **Dijkstra** da $s$: la risposta è $\text{dist}[t]$, oppure "nessuna uscita" se $\text{dist}[t]=+\infty$. Gli archi extra sono $|U|=O(n)$, quindi il grafo resta di taglia $O(n+m)$.

> [!info] Direzione, peso e perché Dijkstra (non BFS)
> - Gli archi di teletrasporto sono **diretti** ($p \to q$, *non* $q \to p$: dal teletrasporto si esce, non si entra magicamente) e di **peso $3$**; gli archi del labirinto restano non orientati e di peso $1$.
> - Con pesi **non uniformi** ($1$ e $3$) serve **Dijkstra**: una BFS assume tutti gli archi di costo $1$ e darebbe distanze sbagliate.
> - $|U| = O(n)$ archi extra → il grafo resta $O(n+m)$.
> - *Variante a peso unitario*: si può tornare a una BFS sostituendo ogni arco $p\to q$ di peso $3$ con una catena di tre archi unitari $p\to d_1\to d_2\to q$ (nodi fittizi).

```pseudo
\begin{algorithm}
\caption{FugaDalLabirinto($G$, $s$, $t$, $p$, $U$) → intero oppure $+\infty$}
\begin{algorithmic}
\State $G' \gets G$ con tutti gli archi di peso $1$
\For{ogni $q \in U$}
  \State aggiungi a $G'$ l'arco diretto $p \to q$ di peso $3$
\EndFor
\State $\text{dist} \gets$ \Call{Dijkstra}{$G'$, $s$}
\State \Return $\text{dist}[t]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** costruzione $O(n+m)$; Dijkstra con heap binario $O(m\log n)$, che domina.
**Trappola:** gli archi di teletrasporto sono **diretti** ($p\to q$, non $q\to p$) e di peso $3$, non $1$: una BFS semplice darebbe distanze sbagliate perché assume archi unitari. *Variante a peso unitario:* si può evitare Dijkstra sostituendo ogni arco $p\to q$ di peso $3$ con una catena di tre archi unitari $p\to d_1\to d_2\to q$ (due nodi fittizi $d_1,d_2$ condivisi); il grafo torna a pesi unitari e basta una BFS in $O(n+m)$.
