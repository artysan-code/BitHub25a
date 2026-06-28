---
tags:
  - algoritmi
---
# Selezione online con max-heap
Esercizio di modellazione che compare nelle casistiche tipiche di [[Casistiche d'Esame Modulo I]] e nella checklist [[Piano Esame ASD - Modulo I]]; per il ripasso della struttura heap vedere [[07 - Code con Priorità e Heap]] e [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 14/09/2022
> Dati in input $n$ interi (con $n$ molto grande, non interamente memorizzabili) e un parametro $k = \Theta(\sqrt{n})$, progettare un algoritmo che legge la sequenza in streaming una sola volta e restituisce i $k$ valori minimi. La memoria disponibile è $O(k) = O(\sqrt{n})$.

**Modellazione.**
L'idea chiave è mantenere un max-heap $H$ di taglia esattamente $k$: la radice $H[1]$ è sempre il massimo tra i $k$ candidati minimi correnti. Ogni nuovo elemento $a_i$ viene confrontato con la radice $H[1]$:
- se $a_i < H[1]$, allora $a_i$ è migliore del peggior candidato corrente → si sovrascrive la radice ($H[1] \gets a_i$) e si ripristina il max-heap con `fixHeap`;
- altrimenti $a_i \ge H[1]$, quindi $a_i$ non può far parte dei $k$ minimi → scartato.

Inizializzazione: si costruisce $H$ coi primi $k$ elementi con una singola chiamata a `Heapify`. Le routine `Heapify` e `fixHeap` sono quelle standard del max-heap su array di [[07 - Code con Priorità e Heap]]. Dopo la scansione di tutta la sequenza, $H$ contiene esattamente i $k$ minimi.

```pseudo
\begin{algorithm}
\caption{$k$Minimi($A$, $n$, $k$) → max-heap}
\begin{algorithmic}
\State $H \gets$ \Call{Heapify}{$A[1;k]$} \Comment{max-heap su array, $O(k)$}
\For{$i \gets k+1$ \To $n$}
  \If{$A[i] < H[1]$} \Comment{$H[1]$ = massimo corrente (radice)}
    \State $H[1] \gets A[i]$ \Comment{sovrascrive il peggiore dei $k$ candidati}
    \State \Call{fixHeap}{$1$, $H$} \Comment{ripristina il max-heap, $O(\log k)$}
  \EndIf
\EndFor
\State \Return $H$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** La fase di inizializzazione costa $O(k)$ con Heapify. Per ciascuno degli $n - k$ elementi rimanenti, nel caso peggiore si sovrascrive la radice e si chiama `fixHeap`, $O(\log k)$. Il costo totale è $O(k + (n-k)\log k) = O(n\log k)$. Con $k = \Theta(\sqrt{n})$ si ottiene $O(n\log\sqrt{n}) = O\!\left(\tfrac{n\log n}{2}\right) = O(n\log n)$, che è comunque $o(n\sqrt{n})$ poiché $\log n = o(\sqrt{n})$. La memoria occupata è $O(k) = O(\sqrt{n})$.
**Trappola:** usare un min-heap al posto di un max-heap. Con un min-heap la radice è il minimo corrente: il confronto $a_i < H.\text{min}$ non identifica mai elementi da scartare e la struttura perde la proprietà di tenere traccia del $k$-esimo minimo corrente. Serve il max-heap proprio perché la radice rappresenta il "peggiore tra i migliori" visti finora: se un nuovo elemento batte questa soglia, merita di entrare.
