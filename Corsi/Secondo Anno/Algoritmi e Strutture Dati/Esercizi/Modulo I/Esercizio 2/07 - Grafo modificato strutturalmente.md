---
tags:
  - algoritmi
  - grafi
---
# Grafo modificato strutturalmente
Esercizio di **progettazione** su grafi: si **aggiungono archi** al grafo dato secondo la regola del problema, ottenendo $G'$, e poi vi si applica un algoritmo standard (forte connessione, BFS/Dijkstra) **richiamandolo** senza riscriverlo. Il punto è che gli archi extra restino $O(m)$ o $O(n)$, così le dimensioni non esplodono. Ripasso: [[08 - Grafi e Visite#Visita in profondità — DFS|visite]], [[09 - Applicazioni della DFS#Componenti fortemente connesse|componenti fortemente connesse]], [[10 - Cammini Minimi e Dijkstra#Algoritmo di Dijkstra|Dijkstra]].
## A · Archi inversi sui nodi speciali + forte connessione
> [!question] Traccia — 18/07/2022
> Si consideri il seguente gioco su un grafo diretto $G=(V,E)$ con $n$ nodi ed $m$ archi. Una pedina è posizionata inizialmente su un nodo $s$. È possibile spostare la pedina dalla posizione corrente $u$ su un nodo $v$ se esiste un arco diretto $(u,v)\in E$. Inoltre c'è un insieme di nodi speciali $X\subseteq V$: se la pedina si trova su un nodo speciale $x\in X$ è possibile muoverla anche lungo archi **entranti** in $x$, ovvero da $x$ a $v$ se e solo se $(v,x)\in E$ o $(x,v)\in E$. Progettare un algoritmo che in tempo $O(n+m)$ decide se, **indipendentemente dalla posizione iniziale $s$**, è sempre possibile spostare la pedina da $s$ a ogni altro nodo $t$ con un'opportuna sequenza di mosse.

Le mosse legali della pedina definiscono una **relazione di raggiungibilità**: da $u$ si raggiunge $v$ se $(u,v)\in E$; in più, quando $u\in X$, anche se $(v,u)\in E$ (si può risalire un arco entrante). La condizione «da ogni $s$ si raggiunge ogni $t$» è esattamente la **forte connessione** del grafo che descrive queste mosse. Il compito è quindi: costruire quel grafo e verificare che sia fortemente connesso.
### Idea risolutiva
Si costruisce $G'=(V,E')$ che rende esplicite le mosse legali: si copia ogni arco di $E$ e, per ogni arco $(v,x)\in E$ con $x\in X$, si aggiunge l'arco inverso $(x,v)$ (la mossa "risali l'entrante" da un nodo speciale). A questo punto la pedina può muoversi da $u$ a $v$ **se e solo se** $(u,v)\in E'$, quindi «da ogni $s$ ogni $t$ è raggiungibile» equivale a «$G'$ è fortemente connesso». Su $G'$ si richiama l'algoritmo delle **componenti fortemente connesse**: $G'$ è fortemente connesso se e solo se ha **una sola** componente. L'appartenenza $x\in X$ si testa in $O(1)$ con un array booleano `speciale[1..n]`, e ogni arco genera al più un inverso, quindi $|E'|\le 2m$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{sempreRaggiungibile($G$, $X$) → booleano}
\begin{algorithmic}
\State costruisci `speciale`$[1..n]$ da $X$ \Comment{$speciale[x]=$ true sse $x\in X$; $O(n)$}
\State $E' \gets \emptyset$
\ForAll{arco $(v,x) \in E$}
  \State aggiungi $(v,x)$ a $E'$
  \If{$speciale[x]$}
    \State aggiungi $(x,v)$ a $E'$ \Comment{mossa inversa da nodo speciale}
  \EndIf
\EndFor
\State $G' \gets (V, E')$
\State $\mathit{cfc} \gets$ \Call{ComponentiFortementeConnesse}{$G'$}
\State \Return $|\mathit{cfc}| = 1$
\end{algorithmic}
\end{algorithm}
```

Si richiama `ComponentiFortementeConnesse` come scatola nera (Kosaraju/DFS, $O(n+m)$): restituisce la partizione dei nodi in componenti, e $G'$ è fortemente connesso esattamente quando la partizione ha cardinalità $1$.
### Complessità
Costruire `speciale` è $O(n)$; la scansione di $E$ è $O(m)$ e aggiunge al più $m$ archi inversi, dunque $|E'|\le 2m = O(m)$ e $G'$ ha $n$ nodi. Le componenti fortemente connesse costano $O(n+|E'|)=O(n+m)$. Totale **$O(n+m)$**, come richiesto.
### Correttezza
La chiave è che $G'$ catturi **esattamente** le mosse del gioco.

> [!quote] Invariante — archi di $G'$ = mosse legali
> Per ogni coppia $(u,v)$, la pedina può muoversi da $u$ a $v$ in una mossa **se e solo se** $(u,v)\in E'$.

**Dimostrazione.** ($\Rightarrow$) Una mossa da $u$ a $v$ è legale in due casi: $(u,v)\in E$ — e allora $(u,v)$ è copiato in $E'$; oppure $u\in X$ e $(v,u)\in E$ — e allora la costruzione, elaborando l'arco $(v,u)$ con estremo speciale $u$, ha aggiunto $(u,v)$ a $E'$. In entrambi i casi $(u,v)\in E'$. ($\Leftarrow$) Ogni arco di $E'$ o è un arco $(u,v)\in E$ (mossa diretta), o è un inverso $(x,v)$ aggiunto perché $x\in X$ e $(v,x)\in E$ (mossa "risali l'entrante" da $x$ speciale): in entrambi i casi è una mossa legale. $\blacksquare$

Per l'invariante, una sequenza di mosse da $s$ a $t$ esiste **se e solo se** $t$ è raggiungibile da $s$ in $G'$. La condizione della traccia — per **ogni** $s$ e **ogni** $t$ esiste tale sequenza — equivale quindi a: $G'$ è fortemente connesso, cioè le sue componenti fortemente connesse sono una sola. L'algoritmo restituisce `true` esattamente in quel caso. $\blacksquare$

> [!warning] Aggiungere gli inversi solo per archi esistenti
> L'inverso $(x,v)$ va aggiunto **solo** se $(v,x)\in E$ e $x\in X$. Aggiungere $(x,v)$ per ogni $x\in X$ e ogni $v\in V$ farebbe esplodere $|E'|$ a $O(n\cdot|X|)=O(n^2)$, perdendo il bound. La regola si applica agli archi già presenti in $E$.
## B · Archi di teletrasporto + cammino minimo
> [!question] Traccia — 27/09/2023
> Un labirinto è modellato come un grafo non diretto $G=(V,E)$. Siete nel nodo $s$ e l'uscita è nel nodo $t$; percorrere un arco costa $1$ minuto. C'è un nodo speciale $p$ (teletrasporto) e un insieme $U\subseteq V$ di uscite del teletrasporto: se siete su $p$ potete teletrasportarvi in un qualsiasi $q\in U$ a vostra scelta, al costo di $3$ minuti. Progettare un algoritmo efficiente che calcoli la strategia più veloce, se esiste, per uscire dal labirinto.

Il costo di una strategia è la somma dei tempi delle mosse: $1$ minuto per arco del labirinto, $3$ minuti per un teletrasporto da $p$. Serve il **cammino di costo minimo** da $s$ a $t$ in un grafo che includa anche i "salti" del teletrasporto. Poiché i costi non sono tutti uguali ($1$ e $3$), è un problema di cammini minimi pesati.
### Idea risolutiva
Si costruisce un grafo pesato $G'$: gli archi del labirinto diventano archi (in entrambi i versi, essendo $G$ non orientato) di peso $1$; per ogni $q\in U$ si aggiunge un arco **diretto** $p\to q$ di peso $3$ (dal teletrasporto si esce verso $U$, non ci si entra magicamente). Su $G'$ si richiama **Dijkstra** da $s$ (pesi $\geq 0$): la risposta è $\text{dist}[t]$, oppure "nessuna uscita" se $\text{dist}[t]=+\infty$. Gli archi aggiunti sono $|U|=O(n)$, quindi $G'$ resta di taglia $O(n+m)$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{fugaDalLabirinto($G$, $s$, $t$, $p$, $U$) → intero oppure $+\infty$}
\begin{algorithmic}
\State $G' \gets G$ con ogni arco del labirinto di peso $1$
\ForAll{$q \in U$}
  \State aggiungi a $G'$ l'arco diretto $p \to q$ di peso $3$
\EndFor
\State $\text{dist} \gets$ \Call{Dijkstra}{$G'$, $s$}
\State \Return $\text{dist}[t]$ \Comment{$+\infty$ se $t$ non è raggiungibile}
\end{algorithmic}
\end{algorithm}
```

`Dijkstra` è richiamato come scatola nera: restituisce le distanze minime da $s$ su un grafo a pesi non negativi. Il valore $\text{dist}[t]$ è il numero minimo di minuti per uscire; $+\infty$ significa che non esiste strategia.
### Complessità
La costruzione di $G'$ è $O(n+m)$ (copia degli archi del labirinto + $|U|\le n$ archi di teletrasporto). Dijkstra con heap binario costa $O(m\log n)$ su $G'$, che ha $O(n+m)$ archi: è il termine dominante. Totale **$O(m\log n)$**.
### Correttezza
Ogni strategia di fuga corrisponde a un cammino $s\rightsquigarrow t$ in $G'$ e viceversa, con **costo uguale**: un passo nel labirinto è un arco di peso $1$, un teletrasporto da $p$ a $q\in U$ è l'arco $p\to q$ di peso $3$. Quindi il minimo costo di una strategia è la distanza minima $\text{dist}[t]$ in $G'$, che Dijkstra calcola correttamente perché tutti i pesi sono $\geq 0$. Se $t$ è irraggiungibile, $\text{dist}[t]=+\infty$ e non esiste alcuna strategia. $\blacksquare$

> [!warning] Archi diretti, peso $3$, e perché non BFS
> Gli archi di teletrasporto sono **diretti** ($p\to q$, non $q\to p$) e di **peso $3$**: una BFS assumerebbe archi unitari e darebbe distanze sbagliate. *Variante a peso unitario:* si può tornare a una BFS sostituendo ogni arco $p\to q$ di peso $3$ con una catena di tre archi unitari $p\to d_1\to d_2\to q$ (due nodi fittizi per uscita), riportando il grafo a pesi $1$ → costo $O(n+m)$.
