---
tags:
  - algoritmi
  - strutture-dati
---
# Prefix sums 1D
Esercizio di **modellazione**: un oracolo con preprocessing $O(n)$ e query $O(1)$, ottenuto precalcolando somme di prefisso (eventualmente con una trasformazione $+1/-1$) o estensioni direzionali. Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|prefix sum e oracoli]].
## A · Differenza uni/zeri su un range
> [!question] Traccia — 30/01/2024
> Sia $A[1..n]$ un vettore di bit. Progettare un oracolo, costruibile in $O(n)$, che risponda in tempo **costante** a $\text{Differenza}(i,j)$: la differenza in modulo tra il numero di $1$ e il numero di $0$ nel sottovettore $A[i..j]$.

Si vuole $|\#1_{[i,j]}-\#0_{[i,j]}|$ in $O(1)$ per ogni $(i,j)$. Contare zeri e uni scandendo il range costerebbe $O(n)$ a query: serve precalcolare una quantità che si differenzi tra prefissi.
### Idea risolutiva
Con la trasformazione $+1/-1$ ($1\to+1$, $0\to-1$) si definisce $P[0]=0$, $P[k]=\sum_{h=1}^{k}(2A[h]-1)$: così $P[k]$ è la differenza cumulata (uni meno zeri) su $A[1..k]$. Per un range,
$$\sum_{h=i}^{j}(2A[h]-1)=P[j]-P[i-1]=\#1_{[i,j]}-\#0_{[i,j]},$$
quindi $\text{Differenza}(i,j)=|P[j]-P[i-1]|$: una sottrazione e un valore assoluto, $O(1)$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciOracolo($A$, $n$) → array P}
\begin{algorithmic}
\State $P[0] \gets 0$
\For{$k \gets 1$ \To $n$}
  \State $P[k] \gets P[k-1] + (2 \cdot A[k] - 1)$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Differenza($P$, $i$, $j$) → intero}
\begin{algorithmic}
\State \Return $|P[j] - P[i-1]|$
\end{algorithmic}
\end{algorithm}
```
### Complessità
Preprocessing $\Theta(n)$ tempo e spazio (una scansione); query $O(1)$.
### Correttezza
> [!quote] Invariante — $P[k]$ è la differenza cumulata
> $P[k]=\#1_{[1,k]}-\#0_{[1,k]}$ per ogni $k$, con $P[0]=0$.

**Dimostrazione.** $P[0]=0$ (range vuoto). Se $P[k-1]=\#1_{[1,k-1]}-\#0_{[1,k-1]}$, aggiungere $2A[k]-1$ (che vale $+1$ se $A[k]=1$, $-1$ se $A[k]=0$) aggiorna la differenza esattamente col contributo di $A[k]$. $\blacksquare$

Per l'invariante $P[j]-P[i-1]=(\#1_{[1,j]}-\#0_{[1,j]})-(\#1_{[1,i-1]}-\#0_{[1,i-1]})=\#1_{[i,j]}-\#0_{[i,j]}$; il valore assoluto dà la differenza in modulo. $\blacksquare$

> [!warning] La trasformazione $+1/-1$ e l'off-by-one
> Sommare i valori grezzi darebbe $\#1_{[i,j]}$, non la differenza: serve la codifica $2A[h]-1$. E nella query si usa $P[i-1]$ (non $P[i]$), altrimenti si esclude il contributo di $A[i]$.
## B · BlockSize — blocco di zeri contenente $i$
> [!question] Traccia — 27/09/2023
> Sia $A[1..n]$ un vettore di bit. Progettare un oracolo, costruibile in $O(n)$, che risponda in $O(1)$ a $\text{BlockSize}(i)$: la lunghezza del più grande blocco di zeri contigui che contiene $i$; se $A[i]=1$, la risposta è $0$.
### Idea risolutiva
Il blocco di zeri che contiene $i$ è la somma di due estensioni: quanti zeri consecutivi **terminano** in $i$ (verso sinistra) e quanti **iniziano** in $i$ (verso destra). Si precalcolano con due scansioni opposte, stile prefisso/suffisso ([[02 - Precalcolo di array ausiliari]]): $\text{le}[i]$ (zeri che terminano in $i$) e $\text{re}[i]$ (zeri che iniziano in $i$). Per $A[i]=0$ la lunghezza del blocco è $\text{le}[i]+\text{re}[i]-1$ ($i$ è contato in entrambe le estensioni).
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciOracolo($A$, $n$) → array L}
\begin{algorithmic}
\State $\text{le}[0] \gets 0$
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = 0$} \State $\text{le}[i] \gets \text{le}[i-1] + 1$ \Else \State $\text{le}[i] \gets 0$ \EndIf
\EndFor
\State $\text{re}[n+1] \gets 0$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 0$} \State $\text{re}[i] \gets \text{re}[i+1] + 1$ \Else \State $\text{re}[i] \gets 0$ \EndIf
\EndFor
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = 0$} \State $L[i] \gets \text{le}[i] + \text{re}[i] - 1$ \Else \State $L[i] \gets 0$ \EndIf
\EndFor
\State \Return $L$
\end{algorithmic}
\end{algorithm}
```

La query restituisce direttamente $L[i]$.
### Complessità e correttezza
Preprocessing $\Theta(n)$ (tre scansioni), $O(n)$ spazio; query $O(1)$. Correttezza: per induzione, $\text{le}[i]$ conta gli zeri consecutivi che terminano in $i$ ($\text{le}[i-1]+1$ se $A[i]=0$, riparte a $0$ altrimenti), simmetrico $\text{re}[i]$. Per $A[i]=0$ il blocco che contiene $i$ va da $\text{le}[i]$ posizioni a sinistra (incluso $i$) a $\text{re}[i]$ a destra (incluso $i$): lunghezza $\text{le}[i]+\text{re}[i]-1$, avendo tolto il doppio conteggio di $i$. $\blacksquare$

> [!warning] Direzioni opposte e $-1$
> Le due estensioni vanno calcolate in versi opposti (una sinistra→destra, l'altra destra→sinistra) e si sottrae $1$ per non contare due volte $i$; per $A[i]=1$ la risposta è $0$ per definizione.
