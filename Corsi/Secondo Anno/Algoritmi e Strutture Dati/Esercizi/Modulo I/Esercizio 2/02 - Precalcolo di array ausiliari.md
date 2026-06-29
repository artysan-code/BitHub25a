---
tags:
  - algoritmi
---
# Precalcolo di array ausiliari
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]]: una o più **scansioni lineari** che riempiono array di supporto (run, vicino più prossimo, prima/ultima occorrenza), poi una passata finale calcola la risposta. Tempo $O(n)$ (o $O(n+k)$ se si indicizza per valore). Ripasso: [[04 - Algoritmi di Ordinamento]]; checklist [[Piano Esame ASD - Modulo I]].

> [!info] Schema comune del pattern
> Quando la proprietà di ogni posizione dipende da una **scansione direzionale** (run, distanza, occorrenza), si precalcola un array da sinistra e/o uno da destra con una **ricorrenza locale** (il valore in $i$ si ottiene da quello del vicino), poi una passata finale combina. Trasforma un approccio ingenuo $O(n^2)$ — riscandire per ogni posizione — in $O(n)$. Cambia solo *cosa* si mette negli array: lunghezze di run (A), indici del vicino più prossimo (B), prima/ultima occorrenza per valore (C).
## Pattern A — run crescenti/decrescenti (left[] e right[])
> [!question] Traccia — 25/07/2023
> Dato un array $A[1..n]$ di interi positivi, si dice che $m$ è un *$k$-picco* se esistono almeno $k$ elementi consecutivi strettamente crescenti che terminano in $A[m]$ e almeno $k$ elementi consecutivi strettamente decrescenti che partono da $A[m]$. Trovare il massimo $k$ per cui esiste un $k$-picco in $A$. L'algoritmo deve operare in $O(n)$.

**Idea.** Si costruiscono due array ausiliari con due scansioni lineari indipendenti:
- $\text{left}[m]$ = lunghezza della massima run strettamente crescente di elementi consecutivi che **termina in** $m$ (incluso $m$); si calcola con una scansione sinistra $\to$ destra;
- $\text{right}[m]$ = lunghezza della massima run strettamente decrescente di elementi consecutivi che **parte da** $m$ (incluso $m$); si calcola con una scansione destra $\to$ sinistra.

Il $k$-picco in $m$ vale $\min(\text{left}[m],\, \text{right}[m]) - 1$ (si sottrae $1$ perché $m$ viene conteggiato in entrambi gli array). La risposta è $\max_{m}\!\bigl(\min(\text{left}[m],\, \text{right}[m]) - 1\bigr)$.

> [!info] Come si costruiscono in $O(n)$ e perché il $-1$
> - **Ricorrenza locale** (è ciò che rende lineare ogni array): $\text{left}[i] = \text{left}[i-1] + 1$ se $A[i] > A[i-1]$, altrimenti $\text{left}[i] = 1$ (la salita riparte). Simmetrica per $\text{right}$, scandendo da destra: $\text{right}[i] = \text{right}[i+1] + 1$ se $A[i] > A[i+1]$, altrimenti $1$.
> - **$\min$**: il $k$-picco richiede salita *e* discesa lunghe almeno $k$ → comanda il lato più corto.
> - **$-1$**: il vertice $m$ è contato sia in $\text{left}[m]$ sia in $\text{right}[m]$, quindi va tolto una volta.

```pseudo
\begin{algorithm}
\caption{kPiccoMassimo($A$, $n$) → intero}
\begin{algorithmic}
\State \Comment{Costruzione left[] — scansione sinistra → destra}
\State $\text{left}[1] \gets 1$
\For{$i \gets 2$ to $n$}
  \If{$A[i] > A[i-1]$}
    \State $\text{left}[i] \gets \text{left}[i-1] + 1$
  \Else
    \State $\text{left}[i] \gets 1$
  \EndIf
\EndFor
\State \Comment{Costruzione right[] — scansione destra → sinistra}
\State $\text{right}[n] \gets 1$
\For{$i \gets n-1$ downto $1$}
  \If{$A[i] > A[i+1]$}
    \State $\text{right}[i] \gets \text{right}[i+1] + 1$
  \Else
    \State $\text{right}[i] \gets 1$
  \EndIf
\EndFor
\State \Comment{Scansione finale: calcolo del massimo k-picco}
\State $\text{best} \gets 0$
\For{$m \gets 1$ to $n$}
  \State $k \gets \min(\text{left}[m],\; \text{right}[m]) - 1$
  \If{$k > \text{best}$}
    \State $\text{best} \gets k$
  \EndIf
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```

> [!example] Esempio — $A = [2, 5, 8, 6, 1]$
> | | $2$ | $5$ | $8$ | $6$ | $1$ |
> |:--|:-:|:-:|:-:|:-:|:-:|
> | $\text{left}$ | $1$ | $2$ | $3$ | $1$ | $1$ |
> | $\text{right}$ | $1$ | $1$ | $3$ | $2$ | $1$ |
> | $\min - 1$ | $0$ | $0$ | $\mathbf{2}$ | $0$ | $0$ |
>
> Vince $m = 3$ (valore $8$): salita $2,5,8$ e discesa $8,6,1$, vertice condiviso → $k = 2$. Risposta $\text{best} = 2$.

**Complessità:** $\Theta(n)$ tempo (tre scansioni lineari); $\Theta(n)$ spazio per $\text{left}$ e $\text{right}$.
**Trappola:** $\text{left}[m]$ conta la run che **termina in** $m$ stesso (incluso): il $k$-picco è quindi $\min(\text{left}[m], \text{right}[m]) - 1$, non $\min(\text{left}[m], \text{right}[m])$.
## Pattern B — vicino più prossimo (prev[] e next[])
> [!question] Traccia — 16/07/2024
> Un'autostrada lunga $n$ km è descritta da un vettore booleano $A[1..n]$ con $A[i]=1$ se al km $i$ c'è una colonnina SOS. Calcolare $B[i]$ = il km della colonnina SOS **più vicina** al km $i$, per ogni $i$. Complessità $O(n)$.

**Idea.** Si calcolano due array con due scansioni: $\text{prev}[i]$ = km della colonnina più vicina a sinistra (o in $i$ stesso), $\text{next}[i]$ = km della più vicina a destra (o in $i$). Poi una passata finale sceglie per ogni $i$ il più vicino fra i due confrontando le distanze $i - \text{prev}[i]$ e $\text{next}[i] - i$. Quando da un lato non esiste alcuna colonnina si usa un sentinella ($-\infty$ a sinistra, $+\infty$ a destra) così il confronto sceglie automaticamente l'altro lato.

> [!info] Le variabili
> - $\text{prev}[i]$ = indice dell'ultima colonnina vista scandendo da **sinistra** fino a $i$ (la più vicina a sinistra, o $i$ stesso se $A[i]=1$); $\text{next}[i]$ il simmetrico da **destra**.
> - $ult$ / $pross$ = la posizione dell'ultima colonnina incontrata durante la scansione corrente; è lo "stato" che si trascina e si copia in $\text{prev}/\text{next}$ ad ogni passo.
> - I **sentinella** $-\infty$ e $+\infty$ rendono la distanza dal lato mancante sempre $+\infty$ (peggiore), così il confronto finale sceglie da solo il lato che esiste, senza casi speciali.

```pseudo
\begin{algorithm}
\caption{colonninaPiuVicina($A$, $n$) → array B}
\begin{algorithmic}
\State \Comment{prev[i]: ultima colonnina vista scandendo sinistra → destra}
\State $ult \gets -\infty$
\For{$i \gets 1$ to $n$}
  \If{$A[i] = 1$} \State $ult \gets i$ \EndIf
  \State $\text{prev}[i] \gets ult$
\EndFor
\State \Comment{next[i]: prima colonnina vista scandendo destra → sinistra}
\State $pross \gets +\infty$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 1$} \State $pross \gets i$ \EndIf
  \State $\text{next}[i] \gets pross$
\EndFor
\For{$i \gets 1$ to $n$}
  \If{$i - \text{prev}[i] \leq \text{next}[i] - i$}
    \State $B[i] \gets \text{prev}[i]$
  \Else
    \State $B[i] \gets \text{next}[i]$
  \EndIf
\EndFor
\State \Return $B$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $\Theta(n)$ tempo, $\Theta(n)$ spazio.
**Trappola:** inizializzare i sentinella in modo che la distanza dal lato mancante risulti sempre peggiore ($i-(-\infty)=+\infty$, $(+\infty)-i=+\infty$); senza sentinella il primo/ultimo tratto privo di colonnine a un lato darebbe un indice indefinito. A parità di distanza la traccia non vincola la scelta: qui si privilegia il lato sinistro.
## Pattern C — indicizzazione per valore (first[] e last[])
> [!question] Traccia — 18/02/2025
> $n$ segmenti verticali su una retta, a distanza $1$ l'uno dall'altro; il segmento $i$ ha altezza intera $h_i \in [1,k]$, memorizzata in $H[1..n]$. Se $h_i = h_j = h$ si può formare un rettangolo di area $h\cdot(j-i)$. Trovare l'area massima ottenibile. Complessità $O(n+k)$.

**Idea.** Per una data altezza $h$ il rettangolo più ampio usa la **prima** e l'**ultima** occorrenza di $h$: area $= h\cdot(\text{last}[h] - \text{first}[h])$. Si allocano quindi due array indicizzati per valore, $\text{first}[1..k]$ e $\text{last}[1..k]$, riempiti con una sola scansione di $H$ (la prima volta che si incontra l'altezza $h$ si fissa $\text{first}[h]$, ogni volta si aggiorna $\text{last}[h]$). La risposta è il massimo su $h\in[1,k]$ con almeno due occorrenze.

> [!info] L'idea chiave: indice = valore, non posizione
> - $\text{first}[h]$ / $\text{last}[h]$ sono indicizzati **per altezza** ($1..k$), non per posizione ($1..n$): è questo a dare $O(n+k)$ invece di confrontare tutte le coppie ($O(n^2)$).
> - Per un'altezza fissata, l'area cresce con la **larghezza** $j-i$: i due segmenti più larghi sono il primo e l'ultimo di quell'altezza; le occorrenze intermedie sono inutili.
> - Se un'altezza compare **una sola volta**, $\text{first}[h] = \text{last}[h]$ → area $0$ → non vince mai: il vincolo "almeno due occorrenze" si gestisce da sé.

```pseudo
\begin{algorithm}
\caption{rettangoloMassimo($H$, $n$, $k$) → intero}
\begin{algorithmic}
\For{$h \gets 1$ to $k$}
  \State $\text{first}[h] \gets 0$; $\text{last}[h] \gets 0$ \Comment{0 = altezza non ancora vista}
\EndFor
\For{$i \gets 1$ to $n$}
  \State $h \gets H[i]$
  \If{$\text{first}[h] = 0$} \State $\text{first}[h] \gets i$ \EndIf
  \State $\text{last}[h] \gets i$
\EndFor
\State $\text{best} \gets 0$
\For{$h \gets 1$ to $k$}
  \If{$\text{first}[h] \neq 0$}
    \State $area \gets h \cdot (\text{last}[h] - \text{first}[h])$
    \If{$area > \text{best}$} \State $\text{best} \gets area$ \EndIf
  \EndIf
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```

> [!example] Esempio — $H = [3, 1, 3, 2, 1]$, $k = 3$
> | altezza $h$ | $1$ | $2$ | $3$ |
> |:--|:-:|:-:|:-:|
> | $\text{first}[h]$ | $2$ | $4$ | $1$ |
> | $\text{last}[h]$ | $5$ | $4$ | $3$ |
> | area $h\cdot(\text{last}-\text{first})$ | $3$ | $0$ | $\mathbf{6}$ |
>
> Vince $h = 3$: prima occorrenza in $1$, ultima in $3$ → rettangolo alto $3$, largo $2$, **area $6$**.

**Complessità:** $O(n+k)$ tempo ($O(n)$ per la scansione di $H$, $O(k)$ per inizializzazione e passata finale), $O(k)$ spazio.
**Trappola:** indicizzare per **valore** ($1..k$) e non per posizione è ciò che dà $O(n+k)$ invece di $O(n^2)$ confrontando tutte le coppie; l'area dipende solo da prima e ultima occorrenza, le occorrenze intermedie sono irrilevanti perché aumentano la larghezza $j-i$ solo agli estremi.
