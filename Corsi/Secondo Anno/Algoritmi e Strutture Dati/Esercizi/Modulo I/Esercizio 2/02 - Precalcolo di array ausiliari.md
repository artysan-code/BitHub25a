---
tags:
  - algoritmi
---
# Precalcolo di array ausiliari
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]]: una o più **scansioni lineari** che riempiono array di supporto (run, vicino più prossimo, prima/ultima occorrenza), poi una passata finale calcola la risposta. Tempo $O(n)$ (o $O(n+k)$ se si indicizza per valore). Ripasso: [[04 - Algoritmi di Ordinamento]]; checklist [[Piano Esame ASD - Modulo I]].
## Pattern A — run crescenti/decrescenti (left[] e right[])
> [!question] Traccia — 25/07/2023
> Dato un array $A[1..n]$ di interi positivi, si dice che $m$ è un *$k$-picco* se esistono almeno $k$ elementi consecutivi strettamente crescenti che terminano in $A[m]$ e almeno $k$ elementi consecutivi strettamente decrescenti che partono da $A[m]$. Trovare il massimo $k$ per cui esiste un $k$-picco in $A$. L'algoritmo deve operare in $O(n)$.

**Idea.** Si costruiscono due array ausiliari con due scansioni lineari indipendenti:
- $\text{left}[m]$ = lunghezza della massima run strettamente crescente di elementi consecutivi che **termina in** $m$ (incluso $m$); si calcola con una scansione sinistra $\to$ destra;
- $\text{right}[m]$ = lunghezza della massima run strettamente decrescente di elementi consecutivi che **parte da** $m$ (incluso $m$); si calcola con una scansione destra $\to$ sinistra.

Il $k$-picco in $m$ vale $\min(\text{left}[m],\, \text{right}[m]) - 1$ (si sottrae $1$ perché $m$ viene conteggiato in entrambi gli array). La risposta è $\max_{m}\!\bigl(\min(\text{left}[m],\, \text{right}[m]) - 1\bigr)$.
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
**Complessità:** $\Theta(n)$ tempo (tre scansioni lineari); $\Theta(n)$ spazio per $\text{left}$ e $\text{right}$.
**Trappola:** $\text{left}[m]$ conta la run che **termina in** $m$ stesso (incluso): il $k$-picco è quindi $\min(\text{left}[m], \text{right}[m]) - 1$, non $\min(\text{left}[m], \text{right}[m])$.
## Pattern B — vicino più prossimo (prev[] e next[])
> [!question] Traccia — 16/07/2024
> Un'autostrada lunga $n$ km è descritta da un vettore booleano $A[1..n]$ con $A[i]=1$ se al km $i$ c'è una colonnina SOS. Calcolare $B[i]$ = il km della colonnina SOS **più vicina** al km $i$, per ogni $i$. Complessità $O(n)$.

**Idea.** Si calcolano due array con due scansioni: $\text{prev}[i]$ = km della colonnina più vicina a sinistra (o in $i$ stesso), $\text{next}[i]$ = km della più vicina a destra (o in $i$). Poi una passata finale sceglie per ogni $i$ il più vicino fra i due confrontando le distanze $i - \text{prev}[i]$ e $\text{next}[i] - i$. Quando da un lato non esiste alcuna colonnina si usa un sentinella ($-\infty$ a sinistra, $+\infty$ a destra) così il confronto sceglie automaticamente l'altro lato.
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
**Complessità:** $O(n+k)$ tempo ($O(n)$ per la scansione di $H$, $O(k)$ per inizializzazione e passata finale), $O(k)$ spazio.
**Trappola:** indicizzare per **valore** ($1..k$) e non per posizione è ciò che dà $O(n+k)$ invece di $O(n^2)$ confrontando tutte le coppie; l'area dipende solo da prima e ultima occorrenza, le occorrenze intermedie sono irrilevanti perché aumentano la larghezza $j-i$ solo agli estremi.
