---
tags:
  - algoritmi
  - strutture-dati
---
# Prefix sums 2D
Esercizio di **modellazione**: si estende la tecnica dei prefix sum a **due dimensioni** per rispondere in $O(1)$ a somme su sottorettangoli. Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|prefix sum e oracoli di conteggio]].
## Traccia
> [!question] Traccia — 16/02/2026
> Sia $A$ una matrice $n\times m$ di bit ($A[i,j]\in\{0,1\}$). Progettare un oracolo, costruibile in $O(nm)$, che risponda in tempo **costante** a $\text{UniCoperti}(i,j,h)$: il numero di $1$ coperti da un quadrato di lato $h$ il cui angolo in alto a sinistra coincide con la cella $(i,j)$, cioè nella regione $A[i..i+h-1][j..j+h-1]$.

Serve la somma dei valori in un sottoquadrato, in $O(1)$ per query dopo un preprocessing $O(nm)$. La chiave è precalcolare le somme di tutti i rettangoli-prefisso $[1..i]\times[1..j]$.
## Idea risolutiva
Si costruisce $P[0..n][0..m]$ con riga $0$ e colonna $0$ a zero (sentinelle), dove $P[i][j]$ = somma di $A$ sul rettangolo $[1..i]\times[1..j]$. La ricorrenza per riempirlo in $O(nm)$ è
$$P[i][j] = A[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1],$$
dove il termine $-P[i-1][j-1]$ corregge il doppio conteggio del rettangolo in alto a sinistra. La somma di un rettangolo generico $[r_1..r_2]\times[c_1..c_2]$ si ottiene per **inclusione-esclusione**:
$$P[r_2][c_2] - P[r_1-1][c_2] - P[r_2][c_1-1] + P[r_1-1][c_1-1].$$
Per il quadrato di lato $h$ con angolo $(i,j)$: $r_1=i$, $r_2=i+h-1$, $c_1=j$, $c_2=j+h-1$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciOracolo($A$, $n$, $m$) → matrice P}
\begin{algorithmic}
\For{$j \gets 0$ \To $m$} \State $P[0][j] \gets 0$ \EndFor
\For{$i \gets 1$ \To $n$}
  \State $P[i][0] \gets 0$
  \For{$j \gets 1$ \To $m$}
    \State $P[i][j] \gets A[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]$
  \EndFor
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{UniCoperti($P$, $i$, $j$, $h$) → intero}
\begin{algorithmic}
\State $r_2 \gets i + h - 1$; $c_2 \gets j + h - 1$
\State \Return $P[r_2][c_2] - P[i-1][c_2] - P[r_2][j-1] + P[i-1][j-1]$
\end{algorithmic}
\end{algorithm}
```
## Complessità
Preprocessing $\Theta(nm)$ tempo e spazio (una passata sulla matrice, $O(1)$ per cella); query $O(1)$ (quattro accessi e tre operazioni). Rispetta i bound richiesti.
## Correttezza
> [!quote] Invariante — $P[i][j]$ è la somma del rettangolo-prefisso
> Dopo il preprocessing, $P[i][j]=\sum_{a\le i,\,b\le j}A[a][b]$ per ogni $i,j$.

**Dimostrazione** (induzione su $i+j$). Le sentinelle $P[0][\cdot]=P[\cdot][0]=0$ sono corrette (rettangolo vuoto). Per $i,j\geq 1$, assumendo corretti $P[i-1][j]$, $P[i][j-1]$, $P[i-1][j-1]$: la somma del rettangolo $[1..i]\times[1..j]$ è quella dei due rettangoli $[1..i-1]\times[1..j]$ e $[1..i]\times[1..j-1]$, che si sovrappongono su $[1..i-1]\times[1..j-1]$ (sottratto una volta), più la cella $A[i][j]$ — esattamente la ricorrenza. $\blacksquare$

Per l'invariante, la formula di inclusione-esclusione della query somma il rettangolo grande $P[r_2][c_2]$ e rimuove le due bande esterne, reintroducendo l'angolo comune $P[r_1-1][c_1-1]$: il risultato è la somma sul sotto-quadrato, cioè il numero di $1$ (i valori sono in $\{0,1\}$). $\blacksquare$

> [!warning] Segni e angolo del quadrato
> Il termine $+P[i-1][j-1]$ va **sommato** (reintroduce l'angolo tolto due volte); scriverlo con il meno dà risultati negativi. E l'angolo in basso a destra è $(i+h-1,\,j+h-1)$, non $(i+h,\,j+h)$: sforare di una riga/colonna conta celle fuori dal quadrato.
