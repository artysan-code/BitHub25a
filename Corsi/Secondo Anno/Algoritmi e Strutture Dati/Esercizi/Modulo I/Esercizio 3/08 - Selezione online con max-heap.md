---
tags:
  - algoritmi
  - heap
---
# Selezione online con max-heap
Esercizio di **modellazione**: si tiene un **max-heap di taglia fissa $k$** come "filtro" dei $k$ minimi visti in streaming, sfruttando che la radice del max-heap è il peggiore dei candidati correnti. Ripasso: [[07 - Code con Priorità e Heap#Heapify — costruzione in O(n)|Heapify]], [[07 - Code con Priorità e Heap#Operazioni e complessità|muoviBasso (sift-down)]].
## Traccia
> [!question] Traccia — 14/09/2022
> Vengono forniti $n$ numeri $a_1,\dots,a_n$ in modalità **online** (uno alla volta, non memorizzabili tutti); $k$ è un parametro con $k=\Theta(\sqrt n)$. Restituire i $k$ valori più piccoli usando memoria $O(k)$. Il punteggio pieno richiede tempo $o(n\sqrt n)$.

Il vincolo di memoria $O(k)\ll n$ vieta di conservare l'intera sequenza: bisogna tenere solo i $k$ candidati "migliori" visti finora e aggiornarli man mano che scorrono i numeri.
## Idea risolutiva
Si mantiene un **max-heap** $H$ di taglia esattamente $k$: la radice $H[1]$ è il **massimo** dei $k$ candidati correnti, cioè il "peggiore dei migliori". Inizializzato con i primi $k$ elementi (una `Heapify`, $O(k)$), per ogni nuovo $a_i$:

- se $a_i < H[1]$, allora $a_i$ è migliore del peggior candidato → si sovrascrive la radice ($H[1]\gets a_i$) e si ripristina il max-heap con `muoviBasso` ($O(\log k)$);

- altrimenti $a_i\geq H[1]$ non può entrare nei $k$ minimi → si scarta in $O(1)$.

Alla fine $H$ contiene esattamente i $k$ valori minimi. Serve un **max**-heap (non min): solo così la radice è la soglia da battere per entrare.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{kMinimi($A$, $n$, $k$) → max-heap dei k minimi}
\begin{algorithmic}
\State $H \gets$ \Call{Heapify}{$A[1..k]$} \Comment{max-heap, $O(k)$}
\For{$i \gets k+1$ \To $n$}
  \If{$A[i] < H[1]$} \Comment{$H[1]$ = massimo dei k candidati}
    \State $H[1] \gets A[i]$
    \State \Call{muoviBasso}{$H$, $1$} \Comment{ripristina il max-heap, $O(\log k)$}
  \EndIf
\EndFor
\State \Return $H$
\end{algorithmic}
\end{algorithm}
```
## Complessità
Inizializzazione $O(k)$ con `Heapify`; per ognuno degli $n-k$ elementi restanti, al più una sostituzione con `muoviBasso` in $O(\log k)$. Totale $O(k+(n-k)\log k)=O(n\log k)$. Con $k=\Theta(\sqrt n)$: $O(n\log\sqrt n)=O(n\log n)$, che è **$o(n\sqrt n)$** poiché $\log n=o(\sqrt n)$ — punteggio pieno. Memoria $O(k)=O(\sqrt n)$.
## Correttezza
> [!quote] Invariante — $H$ contiene i $k$ minimi del prefisso
> Dopo aver elaborato $a_1,\dots,a_i$ (con $i\geq k$), l'heap $H$ contiene i $k$ valori più piccoli fra $a_1,\dots,a_i$, e la sua radice $H[1]$ ne è il massimo.

**Dimostrazione** (induzione su $i$). *Base* $i=k$: `Heapify` dei primi $k$ dà proprio i $k$ minimi (sono tutti). *Passo*: supponiamo l'invariante per $i-1$. Arriva $a_i$. Se $a_i\geq H[1]$, allora $a_i$ non è più piccolo di nessuno dei $k$ correnti, quindi i $k$ minimi di $a_1..a_i$ restano gli stessi: si scarta correttamente. Se $a_i<H[1]$, il massimo corrente $H[1]$ non è più fra i $k$ minimi (c'è $a_i$ a batterlo) e va rimpiazzato da $a_i$; gli altri $k-1$ candidati restano i più piccoli: sovrascrivere la radice e ripristinare l'heap dà i $k$ minimi di $a_1..a_i$. $\blacksquare$

Applicata a $i=n$, l'invariante dà $H=$ i $k$ minimi dell'intera sequenza. $\blacksquare$

> [!warning] Max-heap, non min-heap
> Con un **min**-heap la radice sarebbe il minimo corrente: il confronto non individuerebbe mai l'elemento da scartare e servirebbe scorrere tutto l'heap per trovare il massimo ($O(k)$ per passo). Il max-heap dà la soglia di ammissione in $O(1)$ alla radice.
