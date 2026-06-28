---
tags:
  - algoritmi
---
# Prefix sums 1D
Casistica "preprocessing $O(n)$, query $O(1)$" tratta in [[Casistiche d'Esame Modulo I]]; per la checklist di preparazione vedi [[Piano Esame ASD - Modulo I]] e il ripasso su [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 30/01/2024
> Dato un array binario $A[1..n]$ con $A[i]\in\{0,1\}$, progettare una struttura dati che, dopo un preprocessing in $O(n)$, risponda in $O(1)$ a query della forma $\text{Differenza}(i,j)$, definita come la differenza assoluta tra il numero di valori $1$ e il numero di valori $0$ nel sottovettore $A[i..j]$, con $1\le i\le j\le n$.

**Modellazione.** Si vuole calcolare $|\#1_{[i,j]} - \#0_{[i,j]}|$ in $O(1)$ per ogni coppia $(i,j)$. Il punto chiave è la trasformazione $+1/-1$: si definisce l'array ausiliario $P[0..n]$ con

$$P[0] = 0, \qquad P[k] = \sum_{h=1}^{k}(2A[h]-1),$$

dove ogni contributo vale $+1$ se $A[h]=1$ e $-1$ se $A[h]=0$. Quindi $P[k]$ è la differenza cumulativa tra il numero di uni e il numero di zeri in $A[1..k]$.

Per un range $[i,j]$ si sfrutta la differenza di prefissi:

$$\sum_{h=i}^{j}(2A[h]-1) = P[j] - P[i-1] = \#1_{[i,j]} - \#0_{[i,j]},$$

da cui $\text{Differenza}(i,j) = |P[j] - P[i-1]|$: una sola sottrazione e un valore assoluto, costo $O(1)$.

Il preprocessing costruisce $P$ in una singola scansione:

```pseudo
\begin{algorithm}
\caption{Preprocessing($A$, $n$) → array $P[0..n]$}
\begin{algorithmic}
\State $P[0] \gets 0$
\For{$k \gets 1$ \To $n$}
  \State $P[k] \gets P[k-1] + (2 \cdot A[k] - 1)$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

La query si riduce a un accesso costante:

```pseudo
\begin{algorithm}
\caption{Differenza($P$, $i$, $j$) → intero}
\begin{algorithmic}
\State \Return $|P[j] - P[i-1]|$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n)$ tempo e spazio per il preprocessing; $O(1)$ per query.
**Trappola:** non usare i valori grezzi di $A$ — sommare gli uni nel range restituisce $\#1_{[i,j]}$, non la differenza $\#1_{[i,j]}-\#0_{[i,j]}$; nell'indice della query usare $P[i-1]$, non $P[i]$: un errore off-by-one escluderebbe il contributo di $A[i]$.
