---
tags:
  - algoritmi
  - dizionari
---
# Intersezione e appartenenza su insiemi
Esercizio di **progettazione** su insiemi. Gli strumenti **del corso** sono due: un **AVL** usato come dizionario ordinato (insert/search $O(\log n)$ *deterministico*, memoria proporzionale agli elementi **distinti**) e **ordina + due puntatori** ($O(n\log n)$, spesso $O(1)$ spazio extra). L'**hash set** ($O(1)$ atteso) sarebbe comodo ma è **fuori programma** (non è nelle slide né in [[05 - Strutture Dati Elementari e Dizionari#Il Tipo di Dato Dizionario|dizionario]]): all'esame non si usa. Ripasso: [[06 - Alberi di Ricerca BST e AVL#Alberi AVL|AVL]], [[04 - Algoritmi di Ordinamento#Merge Sort|MergeSort]].
## A · Appartenenza con vincolo di memoria — dizionario AVL
> [!question] Traccia — 02/02/2026
> L'album completo ha $N$ figurine ($1..N$). Il collezionista possiede già un sottoinsieme $A$ di dimensione $n$, con $n\ll N$ (es. $N=n^3$). Compra $k$ pacchetti $P_1,\dots,P_k$ di $3$ figurine ciascuno ($P_i\subseteq\{1,\dots,N\}$). Presi in input $A, P_1,\dots,P_k$, calcolare quante figurine **mancano** ancora dopo l'acquisto. Vincolo: tempo $o(nk)$ e memoria ausiliaria $o(N)$.

Le figurine possedute alla fine sono l'unione $A\cup P_1\cup\cdots\cup P_k$; la risposta è $N$ meno il numero di figurine **distinte** in tale unione. Un `boolean[1..N]` lo calcolerebbe ma usa $\Theta(N)$ memoria — proprio ciò che il vincolo $o(N)$ vieta.
### Idea risolutiva
Si usa un **AVL** come insieme delle figurine **possedute distinte**: si inseriscono le figurine di $A$ e poi quelle dei pacchetti, ognuna solo se assente (una `search`, poi `insert`). Il numero di nodi è $n_{\text{dist}}\leq n+3k \ll N$, quindi la memoria è $O(n_{\text{dist}})=o(N)$. La risposta è $N-n_{\text{dist}}$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{figurineMancanti($A[1..n]$, $P[1..k]$, $N$) → intero}
\begin{algorithmic}
\State $T \gets$ AVL vuoto; $\mathit{dist} \gets 0$
\For{$j \gets 1$ \To $n$}
  \If{\Call{Search}{$T$, $A[j]$} $=$ null}
    \State \Call{Insert}{$T$, $A[j]$}; $\mathit{dist} \gets \mathit{dist} + 1$
  \EndIf
\EndFor
\For{$i \gets 1$ \To $k$}
  \ForAll{figurina $f$ nel pacchetto $P[i]$}
    \If{\Call{Search}{$T$, $f$} $=$ null}
      \State \Call{Insert}{$T$, $f$}; $\mathit{dist} \gets \mathit{dist} + 1$
    \EndIf
  \EndFor
\EndFor
\State \Return $N - \mathit{dist}$
\end{algorithmic}
\end{algorithm}
```
### Complessità
$n+3k$ operazioni, ciascuna `Search`/`Insert` su un AVL di taglia $\leq n+3k$, cioè $O(\log(n+k))$: tempo $O((n+k)\log(n+k))$, che è $o(nk)$ (batte la scansione naive $O(nk)$ che confronta ogni figurina dei pacchetti con tutto $A$). Memoria $O(n_{\text{dist}})=o(N)$ poiché $n_{\text{dist}}\leq n+3k \ll N$.
### Correttezza
Inserendo solo se assente, l'AVL contiene esattamente le figurine **distinte** possedute (di $A$ e dei pacchetti), quindi $\mathit{dist}=|A\cup P_1\cup\cdots\cup P_k|$. Le figurine mancanti sono quelle di $\{1,\dots,N\}$ non possedute, cioè $N-\mathit{dist}$. $\blacksquare$

> [!warning] Tracciare il posseduto, non il mancante
> `boolean[1..N]` viola $o(N)$: si usa l'AVL, che cresce solo con i **distinti posseduti** (molti meno di $N$), **non** una hash table (fuori programma). E vanno inserite anche le figurine di $A$ già possedute: contare solo i pacchetti sovrastima le mancanti.
## B · Intersezione di due insiemi — sort + due puntatori
> [!question] Traccia — 26/06/2025
> Dati due insiemi $A$ e $B$ di $n$ elementi ciascuno, memorizzati in due vettori, calcolare l'*inclusion coefficient* $\Phi(A,B)=|A\cap B|/|A|$ in tempo $o(n^2)$.
### Idea risolutiva
Si **ordinano** $A$ e $B$ con MergeSort, poi si scandiscono con **due puntatori**: chi punta al valore minore avanza, e a ogni **match** si conta un elemento comune e si avanzano entrambi (saltando eventuali duplicati dello stesso valore, così l'intersezione è su insiemi). Alla fine $\Phi = \text{cnt}/n$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{inclusionCoefficient($A[1..n]$, $B[1..n]$) → reale}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}; \Call{MergeSort}{$B$}
\State $i \gets 1$; $j \gets 1$; $\text{cnt} \gets 0$
\While{$i \leq n$ e $j \leq n$}
  \If{$A[i] = B[j]$}
    \State $v \gets A[i]$; $\text{cnt} \gets \text{cnt}+1$
    \While{$i \leq n$ e $A[i] = v$} \State $i \gets i+1$ \EndWhile
    \While{$j \leq n$ e $B[j] = v$} \State $j \gets j+1$ \EndWhile
  \ElsIf{$A[i] < B[j]$} \State $i \gets i+1$
  \Else \State $j \gets j+1$ \EndIf
\EndWhile
\State \Return $\text{cnt} / n$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Dominata dai due MergeSort: **$O(n\log n)=o(n^2)$**; la scansione a due puntatori è $O(n)$. Correttezza: su due vettori ordinati, il merge avanza sempre il puntatore col valore minore, quindi ogni valore comune viene incontrato come match; i due `while` interni saltano tutte le copie del valore appena contato, così ogni valore distinto in $A\cap B$ è contato **una sola volta**. Perciò $\text{cnt}=|A\cap B|$ e $\Phi=\text{cnt}/n$. $\blacksquare$

> [!example] Esempio — $A=[1,2,2,3]$, $B=[2,2,4]$ (dopo l'ordinamento)
> - $A[1]=1<B[1]=2$ → $i=2$; $A[2]=2=B[1]$ → match, $v=2$, $\text{cnt}=1$; $i$ salta a $4$, $j$ a $3$.
> - $A[4]=3<B[3]=4$ → $i=5$ → fine.
>
> $\text{cnt}=1$ (solo il $2$ in comune). Senza il salto dei duplicati il $2$ sarebbe contato due volte.

> [!warning] Insiemi, non multi-insiemi
> Dopo ogni match vanno saltate **tutte** le copie del valore in entrambi i vettori: ometterlo conta lo stesso valore più volte, gonfiando $\text{cnt}$ oltre $|A\cap B|$. L'hash set darebbe $O(n)$ atteso ma è fuori programma.
