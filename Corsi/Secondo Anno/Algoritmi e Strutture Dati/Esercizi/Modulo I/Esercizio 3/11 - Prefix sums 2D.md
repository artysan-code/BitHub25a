---
tags:
  - algoritmi
---
# Prefix sums 2D
Casistica "preprocessing $O(nm)$, query $O(1)$" su matrice, trattata in [[Casistiche d'Esame Modulo I]]; per la checklist di preparazione vedi [[Piano Esame ASD - Modulo I]] e il ripasso su [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 16/02/2026
> Data una matrice booleana $A[1..n][1..m]$ con $A[i][j]\in\{0,1\}$, progettare una struttura dati che, dopo un preprocessing in $O(nm)$, risponda in $O(1)$ alla query $\text{UniCoperti}(i,j,h)$: numero di valori $1$ nel sottoquadrato di lato $h$ con angolo in alto a sinistra $(i,j)$, ovvero nella regione $A[i..i+h-1][j..j+h-1]$.

**Modellazione.** Si estende la tecnica dei prefix sums da una a due dimensioni. Si costruisce la matrice $P[0..n][0..m]$, con riga $0$ e colonna $0$ interamente a $0$ (sentinelle), in modo che $P[i][j]$ rappresenti la somma di tutti gli elementi di $A$ nel rettangolo $[1..i]\times[1..j]$.

La relazione di ricorrenza è:

$$P[i][j] = A[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]$$

I due termini $P[i-1][j]$ e $P[i][j-1]$ coprono entrambi il rettangolo $[1..i-1]\times[1..j-1]$, che viene contato due volte; $-P[i-1][j-1]$ lo reintroduce una volta sola, eliminando il doppio conteggio.

La query su un rettangolo generico $[r_1..r_2]\times[c_1..c_2]$ si ricava per inclusione-esclusione:

$$\text{Somma}(r_1,c_1,r_2,c_2) = P[r_2][c_2] - P[r_1-1][c_2] - P[r_2][c_1-1] + P[r_1-1][c_1-1]$$

Per il quadrato di lato $h$ con angolo $(i,j)$: $r_1=i$, $r_2=i+h-1$, $c_1=j$, $c_2=j+h-1$.

Il preprocessing popola $P$ riga per riga in una scansione sinistra-destra:

```pseudo
\begin{algorithm}
\caption{Preprocessing($A$, $n$, $m$) → matrice $P[0..n][0..m]$}
\begin{algorithmic}
\For{$j \gets 0$ \To $m$}
  \State $P[0][j] \gets 0$ \Comment{riga sentinella}
\EndFor
\For{$i \gets 1$ \To $n$}
  \State $P[i][0] \gets 0$ \Comment{colonna sentinella}
  \For{$j \gets 1$ \To $m$}
    \State $P[i][j] \gets A[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]$
  \EndFor
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

La query è una combinazione costante di accessi a $P$:

```pseudo
\begin{algorithm}
\caption{UniCoperti($P$, $i$, $j$, $h$) → intero}
\begin{algorithmic}
\State $r_2 \gets i + h - 1$
\State $c_2 \gets j + h - 1$
\State \Return $P[r_2][c_2] - P[i-1][c_2] - P[r_2][j-1] + P[i-1][j-1]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** preprocessing $\Theta(nm)$ tempo e $\Theta(nm)$ spazio; query $O(1)$.
**Trappola:** il termine $+P[i-1][j-1]$ va SOMMATO, non sottratto — nella formula di inclusione-esclusione il rettangolo superiore-sinistro viene eliminato due volte dalle due sottrazioni e va reintrodotto esattamente una volta; scrivere $-P[i-1][j-1]$ porta a un risultato sempre negativo. Secondo errore classico: calcolare l'angolo inferiore-destro del quadrato come $(i+h,\,j+h)$ invece di $(i+h-1,\,j+h-1)$, sforando di una riga e una colonna.
