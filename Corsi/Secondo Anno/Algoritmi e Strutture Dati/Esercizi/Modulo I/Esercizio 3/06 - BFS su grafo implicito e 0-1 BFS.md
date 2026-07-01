---
tags:
  - algoritmi
  - grafi
---
# BFS su grafo implicito e 0-1 BFS
Esercizio di **modellazione**: il grafo non è dato esplicitamente ma ha struttura regolare (griglia, retta) con **grado costante**; lo si visita al volo con BFS (pesi unitari) o Dijkstra (pesi $\{0,1\}$) senza costruirlo per intero. Ripasso: [[08 - Grafi e Visite#Visita in ampiezza — BFS|BFS]], [[10 - Cammini Minimi e Dijkstra#Algoritmo di Dijkstra|Dijkstra]].
## A · Serpentone — annerire il minimo di caselle
> [!question] Traccia — 18/07/2025
> Serpentone è una griglia $n\times m$ di celle bianche o nere. Due celle sono **vicine** se adiacenti in verticale o orizzontale; $a$ e $b$ sono **connesse** se esiste un cammino fra celle vicine tutte **nere**. Date $a$ e $b$, annerire il **minimo numero** di caselle per rendere $a$ e $b$ connesse. Progettare un algoritmo efficiente.

Rendere $a$ e $b$ connesse significa scegliere un cammino di celle vicine da $a$ a $b$ e annerire quelle bianche che vi si trovano: il costo è il **numero di celle bianche sul cammino**. Si vuole il cammino che minimizza questo numero.
### Idea risolutiva
Si modella la griglia come grafo implicito: i nodi sono le celle, gli archi collegano celle vicine; **entrare** in una cella costa $0$ se è già nera, $1$ se è bianca (va annerita). Il minimo numero di caselle da annerire è la **distanza di cammino minimo** da $a$ a $b$ con questi pesi $\{0,1\}$, contando anche $a$ e $b$ se bianche. È un problema di cammini minimi a pesi non negativi → **Dijkstra** sul grafo implicito (i vicini si generano al volo, grado $\leq 4$).
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{serpentoneMin($\text{col}$, $n$, $m$, $a$, $b$) → intero}
\begin{algorithmic}
\State \Comment{grafo implicito: nodo = cella; peso d'ingresso in $c$ = $[\,\text{col}[c]=\text{bianco}\,]$}
\State $d[a] \gets [\,\text{col}[a] = \text{bianco}\,]$ \Comment{annerire $a$ se bianca}
\State $d \gets$ \Call{Dijkstra}{grafo implicito della griglia, $a$, con $d[a]$ iniziale}
\State \Return $d[b]$
\end{algorithmic}
\end{algorithm}
```

I vicini di $(i,j)$ sono $(i\pm1,j)$ e $(i,j\pm1)$ entro la griglia; l'arco verso la cella $c'$ ha peso $[\,\text{col}[c']=\text{bianco}\,]$. Dijkstra è invocato come scatola nera sul grafo implicito (nessuna costruzione esplicita).
### Complessità
$|V|=nm$ celle, $|E|=O(nm)$ archi (grado $\leq 4$). Dijkstra con heap binario costa **$O(nm\log(nm))$**.

> [!info] 0-1 BFS — ottimizzazione *(extra, non da slide)*
> Con pesi $\{0,1\}$ si può sostituire Dijkstra con la **0-1 BFS**: una coda a doppia estremità in cui un arco di peso $0$ inserisce in testa e uno di peso $1$ in coda, ottenendo $O(nm)$. La tecnica della deque non è nel programma del Modulo I, quindi la soluzione "da esame" è Dijkstra; la 0-1 BFS è il raffinamento ottimale.
### Correttezza
Ogni modo di connettere $a$ e $b$ corrisponde a un cammino di celle vicine $a\rightsquigarrow b$, e il numero di caselle da annerire è il numero di celle bianche che vi compaiono, cioè la somma dei pesi d'ingresso lungo il cammino (con $d[a]$ che conta $a$ se bianca). Minimizzare tale somma è un problema di cammino minimo a pesi $\geq 0$, risolto correttamente da Dijkstra. Quindi $d[b]$ è il minimo numero di caselle da annerire. $\blacksquare$
## B · Golf unidimensionale
> [!question] Traccia — 26/06/2025
> Un campo è un segmento di $n$ posizioni ($1..n$); la pallina parte in $1$, la buca è in $b$. Ogni posizione $i$ ha un tipo di terreno $t_i\in\{1,2,3\}$; ci sono $2$ mazze. Colpendo da $i$ con la mazza $j$, la pallina va in $i-d(t_i,j)$ oppure $i+d(t_i,j)$ (distanza intera positiva dipendente da terreno e mazza), purché entro il campo. Minimizzare il numero di colpi per arrivare in $b$. Complessità $O(n)$.
### Idea risolutiva
Grafo implicito unidimensionale: nodi le $n$ posizioni, e da $i$ al più $4$ archi (2 mazze $\times$ 2 direzioni) di **peso unitario** (un colpo). Grado costante → $|E|=O(n)$, pesi uguali → **BFS** classica dalla posizione $1$; la risposta è il numero di tratte fino a $b$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{golfMinColpi($t$, $d$, $n$, $b$) → intero}
\begin{algorithmic}
\State $G \gets$ grafo con nodi $\{1,\dots,n\}$ e archi vuoti
\For{$i \gets 1$ \To $n$}
  \For{$j \gets 1$ \To $2$} \Comment{le due mazze}
    \State $\delta \gets d(t[i], j)$
    \If{$i - \delta \geq 1$} \State aggiungi l'arco $(i,\ i-\delta)$ a $G$ \EndIf
    \If{$i + \delta \leq n$} \State aggiungi l'arco $(i,\ i+\delta)$ a $G$ \EndIf
  \EndFor
\EndFor
\State $dist \gets$ \Call{visitaBFS}{$G$, $1$} \Comment{numero di colpi da $1$}
\State \Return $dist[b]$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Costruzione $O(n)$ (grado $\leq 4$) e BFS $O(n+|E|)=O(n)$ → **$O(n)$**. Correttezza: i colpi legali da $i$ sono esattamente gli archi generati (mazze $\times$ direzioni, entro i limiti); i pesi sono unitari, quindi la BFS calcola il minimo numero di colpi da $1$ a ogni posizione, e $dist[b]$ è la risposta. $\blacksquare$

> [!warning] BFS solo perché i pesi sono unitari
> La BFS FIFO è corretta perché ogni colpo costa $1$: con costi diversi servirebbe Dijkstra. Il grado costante ($\leq 4$) è ciò che mantiene $|E|=O(n)$ e il tutto lineare.
