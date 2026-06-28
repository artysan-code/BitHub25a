---
tags:
  - algoritmi
---
# Binary search su prefix sums monotone
Casistica "binary search su struttura monotona" tratta in [[Casistiche d'Esame Modulo I]]; per la checklist di preparazione vedi [[Piano Esame ASD - Modulo I]] e il ripasso su [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 22/06/2022
> Dato un array $A[1..n]$ di interi non negativi e un intero $\alpha \ge 0$, progettare una struttura dati che, con preprocessing $O(n)$, risponda in $O(\log n)$ alla seguente query con parametro $\alpha$: trovare il minimo indice $k \in \{1,\ldots,n\}$ tale che
> $$P[k] + \alpha\cdot[k=1] \;\ge\; \frac{S+\alpha}{2},$$
> dove $P[k]=\sum_{h=1}^{k}A[h]$ è il prefix sum in posizione $k$ e $S=P[n]$ è la somma totale. (L'esame usa questa struttura come oracolo per il problema del "taglio bilanciato": trovare la posizione di taglio che distribuisce il peso $S$ più $\alpha$ in modo bilanciato, con $\alpha$ elemento che può stare solo nella metà sinistra.)

**Modellazione.** Il problema si fonda su due osservazioni.

**Monotonicità di $P$.** Poiché $A[i]\ge 0$ per ogni $i$, la sequenza $P[0]\le P[1]\le\cdots\le P[n]$ è non decrescente. Questa proprietà rende la condizione $P[k]\ge\text{soglia}$ monotona su $k$: se è vera per un certo $k^*$ lo è per ogni $k>k^*$. La ricerca binaria è quindi applicabile su $P$.

**Caso $k=1$ separato.** Il termine $\alpha\cdot[k=1]$ è non nullo solo per $k=1$, abbassando la soglia effettiva per quell'unico indice rispetto a tutti gli altri. Si fissa la soglia comune $\text{soglia}=(S+\alpha)/2$ e si distinguono due rami:
- $k=1$: verificare direttamente $P[1]+\alpha\ge\text{soglia}$;
- $k\ge 2$: binary search sul suffisso $P[2..n]$, condizione $P[k]\ge\text{soglia}$.

Il preprocessing calcola $P[0..n]$ con una scansione sinistra→destra in $O(n)$:

```pseudo
\begin{algorithm}
\caption{Preprocessing($A$, $n$) → array $P[0..n]$}
\begin{algorithmic}
\State $P[0] \gets 0$
\For{$k \gets 1$ \To $n$}
  \State $P[k] \gets P[k-1] + A[k]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

La query identifica il minimo $k$ tramite controllo diretto su $k=1$ e ricerca binaria per $k\ge 2$:

```pseudo
\begin{algorithm}
\caption{TaglioBilanciato($P$, $n$, $\alpha$) → intero}
\begin{algorithmic}
\State $S \gets P[n]$
\State $\mathit{soglia} \gets (S + \alpha) / 2$
\If{$P[1] + \alpha \ge \mathit{soglia}$}
  \State \Return $1$
\EndIf
\State $\mathit{basso} \gets 2$
\State $\mathit{alto} \gets n$
\While{$\mathit{basso} < \mathit{alto}$}
  \State $\mathit{mid} \gets \lfloor (\mathit{basso} + \mathit{alto}) / 2 \rfloor$
  \If{$P[\mathit{mid}] \ge \mathit{soglia}$}
    \State $\mathit{alto} \gets \mathit{mid}$
  \Else
    \State $\mathit{basso} \gets \mathit{mid} + 1$
  \EndIf
\EndWhile
\State \Return $\mathit{basso}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** preprocessing $O(n)$ tempo e $O(n)$ spazio per $P$; ogni query $O(\log n)$ per la ricerca binaria su $P[2..n]$ monotono.
**Trappola:** (1) Non gestire $k=1$ separatamente introduce un falso negativo: il test $P[1]\ge\mathit{soglia}$ è più severo di $P[1]+\alpha\ge\mathit{soglia}$, e si perde il caso in cui $P[1]<\mathit{soglia}$ ma $P[1]+\alpha\ge\mathit{soglia}$. (2) Se anche un solo $A[i]<0$, il prefix sum perde la monotonicità e la ricerca binaria restituisce risultati errati silenziosamente: il prerequisito $A[i]\ge 0$ deve essere verificato prima di applicare l'algoritmo.
