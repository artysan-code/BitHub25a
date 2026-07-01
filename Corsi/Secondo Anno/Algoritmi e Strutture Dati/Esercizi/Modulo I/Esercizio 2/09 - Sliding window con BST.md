---
tags:
  - algoritmi
  - strutture-dati
---
# Sliding window con BST
Esercizio di **progettazione** con struttura dati: una **finestra scorrevole** di ampiezza fissa $k$ mantenuta con un **BST bilanciato aumentato**, così che entrata e uscita di un elemento e la query sul contenuto costino $O(\log k)$. Ripasso: [[06 - Alberi di Ricerca BST e AVL#Alberi AVL|BST bilanciato/AVL]], [[05 - Strutture Dati Elementari e Dizionari#Il Tipo di Dato Dizionario|dizionario]].
## Traccia
> [!question] Traccia — 13/06/2024
> Sia $S[1..n]$ una sequenza di interi (tipi di evento, con ripetizioni) e $1\leq k\leq n$. Scegliere la finestra di $k$ elementi consecutivi che **massimizza il numero di eventi distinti** che contiene, e restituire l'indice di inizio di tale finestra. Complessità $O(n\log k)$.

Ogni finestra di $k$ elementi ha un certo numero di valori distinti; scorrendola di una posizione entra un elemento a destra ed esce quello a sinistra. Serve una struttura che, a ogni scorrimento, aggiorni in fretta il conteggio dei distinti — non ricalcolarlo da zero (sarebbe $O(nk)$).
## Idea risolutiva
Si mantiene un BST bilanciato $T$ **aumentato**: una chiave per ogni valore *presente nella finestra*, con un contatore $T[v].\mathit{cnt}$ delle sue occorrenze, e un campo globale $T.\mathit{distinct}$ = numero di chiavi = numero di distinti nella finestra. Scorrere la finestra da $i$ a $i+1$ è **una** `InsertWindow`$(S[i])$ + **una** `DeleteWindow`$(S[i-k])$. Il contatore è essenziale: togliendo $S[i-k]$ la chiave va rimossa **solo se era l'ultima copia** ($\mathit{cnt}$ scende a $0$). Al più $k$ chiavi → ogni operazione $O(\log k)$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{InsertWindow($T$, $v$)}
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
\caption{DeleteWindow($T$, $v$)}
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
\caption{finestraPiuVariegata($S$, $n$, $k$) → intero}
\begin{algorithmic}
\State $T \gets$ BST vuoto con $T.\mathit{distinct} \gets 0$
\For{$i \gets 1$ \To $k$}
  \State \Call{InsertWindow}{$T$, $S[i]$}
\EndFor
\State $\mathit{best} \gets T.\mathit{distinct}$; $\mathit{start} \gets 1$
\For{$i \gets k+1$ \To $n$}
  \State \Call{InsertWindow}{$T$, $S[i]$}
  \State \Call{DeleteWindow}{$T$, $S[i-k]$}
  \If{$T.\mathit{distinct} > \mathit{best}$}
    \State $\mathit{best} \gets T.\mathit{distinct}$; $\mathit{start} \gets i-k+1$
  \EndIf
\EndFor
\State \Return $\mathit{start}$
\end{algorithmic}
\end{algorithm}
```

`InsertWindow`/`DeleteWindow` usano `search`/`insert`/`delete` del BST bilanciato (scatole nere, $O(\log k)$); l'inserimento e la rimozione aggiornano $\mathit{distinct}$ solo quando una chiave nasce o sparisce davvero.
## Complessità
Inizializzazione: $k$ `InsertWindow`, $O(k\log k)$. Scorrimento: $n-k$ passi, ciascuno una `InsertWindow` + una `DeleteWindow`, $O(\log k)$ (il BST ha al più $k$ chiavi). Totale $O(k\log k)+O(n\log k)=$ **$O(n\log k)$**, come richiesto; spazio $O(k)$.
## Correttezza
> [!quote] Invariante — $T$ riflette la finestra corrente
> Prima di valutare la finestra che inizia in $i-k+1$, $T$ contiene una chiave per ogni valore **distinto** presente in $S[i-k+1..i]$, con $T[v].\mathit{cnt}$ = numero di sue occorrenze nella finestra, e $T.\mathit{distinct}$ = numero di valori distinti nella finestra.

**Dimostrazione.** Dopo l'inizializzazione $T$ descrive $S[1..k]$: ogni `InsertWindow` crea la chiave alla prima occorrenza (incrementando $\mathit{distinct}$) e incrementa il contatore alle successive. *Passo*: assumendo l'invariante per la finestra $[i-k, i-1]$, passare a $[i-k+1, i]$ significa aggiungere $S[i]$ e togliere $S[i-k]$: `InsertWindow`$(S[i])$ aggiorna correttamente contatore/distinti per l'ingresso; `DeleteWindow`$(S[i-k])$ decrementa il contatore e rimuove la chiave **solo se** era l'ultima copia, mantenendo $\mathit{distinct}$ pari al numero di valori ancora presenti. $\blacksquare$

Per l'invariante, a ogni passo $T.\mathit{distinct}$ è esattamente il numero di distinti della finestra corrente; l'algoritmo tiene il massimo di questi valori e l'indice di inizio corrispondente, quindi restituisce l'inizio della finestra con più eventi distinti. $\blacksquare$

> [!warning] Il contatore per chiave è indispensabile
> Senza $\mathit{cnt}$, rimuovere $S[i-k]$ cancellerebbe la chiave anche quando altre copie di quel valore restano nella finestra, sottostimando i distinti. Una hash table semplice, oltre a essere **fuori programma**, non garantisce il conteggio in $O(\log k)$.
