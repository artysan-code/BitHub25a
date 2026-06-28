---
tags:
  - algoritmi
---
# Prefix sums 1D
Casistica "preprocessing $O(n)$, query $O(1)$" tratta in [[Casistiche d'Esame Modulo I]]; per la checklist di preparazione vedi [[Piano Esame ASD - Modulo I]] e il ripasso su [[05 - Strutture Dati Elementari e Dizionari]].
## Svolgimento — esame 30/01/2024
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
## Variante — BlockSize (27/09/2023)
> [!question] Traccia — 27/09/2023
> Dato un array binario $A[1..n]$ con $A[i]\in\{0,1\}$, progettare una struttura dati che, dopo un preprocessing in $O(n)$, risponda in $O(1)$ a query $\text{BlockSize}(i)$: la lunghezza del più grande blocco di zeri contigui che contiene l'indice $i$; se $A[i]=1$ la risposta è $0$.

**Modellazione.** Il blocco di zeri che contiene $i$ si misura come somma di due estensioni unidimensionali: quanti zeri consecutivi *terminano* in $i$ (verso sinistra) e quanti *iniziano* in $i$ (verso destra). Si calcolano con due scansioni in direzioni opposte, nello stile del precalcolo prefisso/suffisso ([[02 - Precalcolo di array ausiliari]]):
- $\text{le}[i]$ = numero di zeri consecutivi che terminano in $i$: vale $\text{le}[i-1]+1$ se $A[i]=0$, altrimenti $0$ (scansione sinistra→destra);
- $\text{re}[i]$ = numero di zeri consecutivi che iniziano in $i$: vale $\text{re}[i+1]+1$ se $A[i]=0$, altrimenti $0$ (scansione destra→sinistra).

Per $A[i]=0$ la lunghezza del blocco che contiene $i$ è $\text{le}[i]+\text{re}[i]-1$: l'indice $i$ è contato una volta in ciascuna estensione, quindi si sottrae $1$.

```pseudo
\begin{algorithm}
\caption{Preprocessing($A$, $n$) → array $L[1..n]$}
\begin{algorithmic}
\State $\text{le}[0] \gets 0$
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = 0$}
    \State $\text{le}[i] \gets \text{le}[i-1] + 1$
  \Else
    \State $\text{le}[i] \gets 0$
  \EndIf
\EndFor
\State $\text{re}[n+1] \gets 0$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 0$}
    \State $\text{re}[i] \gets \text{re}[i+1] + 1$
  \Else
    \State $\text{re}[i] \gets 0$
  \EndIf
\EndFor
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = 0$}
    \State $L[i] \gets \text{le}[i] + \text{re}[i] - 1$
  \Else
    \State $L[i] \gets 0$
  \EndIf
\EndFor
\State \Return $L$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{BlockSize($L$, $i$) → intero}
\begin{algorithmic}
\State \Return $L[i]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** preprocessing $\Theta(n)$ (tre scansioni lineari) e $O(n)$ spazio per $\text{le}$, $\text{re}$, $L$; query $O(1)$.
**Trappola:** sottrarre $1$ in $\text{le}[i]+\text{re}[i]-1$ per non contare due volte la posizione $i$; le due estensioni vanno calcolate in *direzioni opposte* (una sinistra→destra, l'altra destra→sinistra), non entrambe nello stesso verso; per $A[i]=1$ la risposta è $0$ per definizione.
