---
tags:
  - algoritmi
---
# Sliding window con BST
Esercizio di progettazione con strutture dati (casistica [[Casistiche d'Esame Modulo I|sliding window con BST]]); ripasso: [[06 - Alberi di Ricerca BST e AVL]], [[05 - Strutture Dati Elementari e Dizionari]]; checklist [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 13/06/2024
> Data una sequenza $S[1..n]$ di interi e un intero $k$ con $1 \le k \le n$, trovare l'indice di inizio della finestra di $k$ elementi consecutivi che massimizza il numero di elementi distinti. Restituire tale indice di inizio.

**Idea.** Si usa una *finestra scorrevole* di ampiezza fissa $k$, mantenuta tramite un BST bilanciato aumentato: ogni chiave $v$ nel BST memorizza un contatore $T[v].\mathit{cnt}$ (numero di occorrenze di $v$ nella finestra corrente). Il numero di elementi distinti coincide con il numero di chiavi presenti nel BST, tenuto aggiornato nel campo $T.\mathit{distinct}$.

L'operazione **InsertWindow** controlla se $v$ è già presente nel BST: in caso affermativo incrementa $T[v].\mathit{cnt}$; altrimenti inserisce $v$ con contatore $1$ e incrementa $T.\mathit{distinct}$. L'operazione **DeleteWindow** decrementa $T[v].\mathit{cnt}$: se il contatore scende a $0$, rimuove la chiave dal BST e decrementa $T.\mathit{distinct}$. Entrambe le operazioni costano $O(\log k)$ perché il BST contiene al più $k$ chiavi contemporaneamente.

L'algoritmo principale inizializza il BST con $S[1..k]$ in $O(k \log k)$, poi scorre la finestra da $i = k+1$ fino a $n$: inserisce $S[i]$, rimuove $S[i-k]$ e aggiorna il candidato ottimo. Ogni passo vale $O(\log k)$, quindi la fase di scorrimento è $O(n \log k)$.

```pseudo
\begin{algorithm}
\caption{InsertWindow($T$, $v$) → void}
\begin{algorithmic}
\If{$v \in T$}
  \State $T[v].\mathit{cnt} \gets T[v].\mathit{cnt} + 1$
\Else
  \State inserisci $v$ in $T$ con $T[v].\mathit{cnt} \gets 1$
  \State $T.\mathit{distinct} \gets T.\mathit{distinct} + 1$
\EndIf
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{DeleteWindow($T$, $v$) → void}
\begin{algorithmic}
\State $T[v].\mathit{cnt} \gets T[v].\mathit{cnt} - 1$
\If{$T[v].\mathit{cnt} = 0$}
  \State rimuovi $v$ da $T$
  \State $T.\mathit{distinct} \gets T.\mathit{distinct} - 1$
\EndIf
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{SlidingWindowBST($S$, $n$, $k$) → intero}
\begin{algorithmic}
\State $T \gets$ BST vuoto con $T.\mathit{distinct} \gets 0$
\For{$i \gets 1$ \To $k$}
  \State \Call{InsertWindow}{$T$, $S[i]$}
\EndFor
\State $\mathit{best} \gets T.\mathit{distinct}$
\State $\mathit{start} \gets 1$
\For{$i \gets k+1$ \To $n$}
  \State \Call{InsertWindow}{$T$, $S[i]$}
  \State \Call{DeleteWindow}{$T$, $S[i-k]$}
  \If{$T.\mathit{distinct} > \mathit{best}$}
    \State $\mathit{best} \gets T.\mathit{distinct}$
    \State $\mathit{start} \gets i - k + 1$
  \EndIf
\EndFor
\State \Return $\mathit{start}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(k \log k)$ per l'inizializzazione $+$ $O(n \log k)$ per la fase di scorrimento $= O(n \log k)$.
**Trappola:** sostituire il BST con una hash table semplice non risolve il problema: la hash table non garantisce count-distinct in $O(\log k)$ e, senza un contatore per chiave, decrementare l'occorrenza di $v$ farebbe credere che $v$ non sia più nella finestra anche quando ne esistono altre copie nella finestra corrente.
