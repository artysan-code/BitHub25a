---
tags:
  - algoritmi
---
# Ordinamento e conteggio come preprocessing
Casistica ricorrente dell'[[Casistiche d'Esame Modulo I|Es. 2 — Progettazione]]; cfr. checklist [[Piano Esame ASD - Modulo I]] e ripasso su [[04 - Algoritmi di Ordinamento]].

> [!question] Traccia — 21/01/2025
> Dato un array $A[1..n]$ di $n$ interi positivi con $n$ pari, determinare se è possibile partizionare gli $n$ elementi in $n/2$ coppie tali che ogni coppia abbia la stessa somma. In caso affermativo restituire le coppie; altrimenti dichiarare impossibile.

**Idea.** Se una partizione in $n/2$ coppie a somma costante esiste, ogni coppia deve valere $t = 2S/n$ dove $S = \sum_{i=1}^{n} A[i]$. La soluzione procede in tre passi:
1. Calcola $S$ e verifica che $2S \bmod n = 0$; se no, impossibile — il target non è intero.
2. Ordina $A$ con MergeSort. Per exchange argument, nell'array ordinato l'elemento più piccolo deve accoppiarsi con il più grande, il secondo minimo col secondo massimo, ecc.: qualsiasi altra assegnazione produce almeno una coppia con somma diversa da $t$.
3. Verifica $A[i] + A[n+1-i] = t$ per $i = 1, \ldots, n/2$; se tutte le verifiche passano le coppie $(A[1], A[n]), (A[2], A[n-1]), \ldots$ sono la risposta.

```pseudo
\begin{algorithm}
\caption{CoppieSommaFissa($A$, $n$) → lista di coppie oppure "impossibile"}
\begin{algorithmic}
\State $S \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $S \gets S + A[i]$
\EndFor
\If{$2S \bmod n \neq 0$}
  \State \Return impossibile \Comment{target non intero: impossibile}
\EndIf
\State $t \gets 2S / n$
\State \Call{MergeSort}{$A$}
\For{$i \gets 1$ \To $n/2$}
  \If{$A[i] + A[n+1-i] \neq t$}
    \State \Return impossibile
  \EndIf
\EndFor
\State $P \gets $ lista vuota
\For{$i \gets 1$ \To $n/2$}
  \State aggiungi la coppia $\bigl(A[i],\; A[n+1-i]\bigr)$ a $P$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n \log n)$, dominata dal MergeSort; il calcolo di $S$ e le due scansioni di verifica e ricostruzione sono entrambe $O(n)$.

**Trappola:** verificare che $t$ sia intero **prima** di ordinare; altrimenti si esegue inutilmente il MergeSort su un'istanza già impossibile. Nella variante con CountingSort (array con $O(n^{2/3})$ outlier), l'array dei contatori deve avere taglia pari al range effettivo dei valori (es. $10n+1$), non $n$.
