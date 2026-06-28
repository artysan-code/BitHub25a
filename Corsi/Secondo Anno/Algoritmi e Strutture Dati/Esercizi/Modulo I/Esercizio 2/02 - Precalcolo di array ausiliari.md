---
tags:
  - algoritmi
---
# Precalcolo di array ausiliari
Esercizio di progettazione con scansioni lineari (casistica [[Casistiche d'Esame Modulo I|precalcolo di array ausiliari]]); ripasso: [[04 - Algoritmi di Ordinamento]]; checklist [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 25/07/2023
> Dato un array $A[1..n]$ di interi positivi, si dice che $m$ è un *$k$-picco* se esistono almeno $k$ elementi consecutivi strettamente crescenti che terminano in $A[m]$ e almeno $k$ elementi consecutivi strettamente decrescenti che partono da $A[m]$. Trovare il massimo $k$ per cui esiste un $k$-picco in $A$. L'algoritmo deve operare in $O(n)$.

**Idea.** Si costruiscono due array ausiliari con due scansioni lineari indipendenti:
- $\text{left}[m]$ = lunghezza della massima run strettamente crescente di elementi consecutivi che **termina in** $m$ (incluso $m$); si calcola con una scansione sinistra $\to$ destra;
- $\text{right}[m]$ = lunghezza della massima run strettamente decrescente di elementi consecutivi che **parte da** $m$ (incluso $m$); si calcola con una scansione destra $\to$ sinistra.

Il $k$-picco in $m$ vale $\min(\text{left}[m],\, \text{right}[m]) - 1$ (si sottrae $1$ perché $m$ viene conteggiato in entrambi gli array). La risposta è $\max_{m}\!\bigl(\min(\text{left}[m],\, \text{right}[m]) - 1\bigr)$.

```pseudo
\begin{algorithm}
\caption{kPiccoMassimo($A$, $n$) → intero}
\begin{algorithmic}
\State \Comment{Costruzione left[] — scansione sinistra → destra}
\State $\text{left}[1] \gets 1$
\For{$i \gets 2$ to $n$}
  \If{$A[i] > A[i-1]$}
    \State $\text{left}[i] \gets \text{left}[i-1] + 1$
  \Else
    \State $\text{left}[i] \gets 1$
  \EndIf
\EndFor
\State \Comment{Costruzione right[] — scansione destra → sinistra}
\State $\text{right}[n] \gets 1$
\For{$i \gets n-1$ downto $1$}
  \If{$A[i] > A[i+1]$}
    \State $\text{right}[i] \gets \text{right}[i+1] + 1$
  \Else
    \State $\text{right}[i] \gets 1$
  \EndIf
\EndFor
\State \Comment{Scansione finale: calcolo del massimo k-picco}
\State $\text{best} \gets 0$
\For{$m \gets 1$ to $n$}
  \State $k \gets \min(\text{left}[m],\; \text{right}[m]) - 1$
  \If{$k > \text{best}$}
    \State $\text{best} \gets k$
  \EndIf
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $\Theta(n)$ in tempo (tre scansioni lineari, ognuna $O(n)$); $\Theta(n)$ in spazio aggiuntivo per $\text{left}$ e $\text{right}$.
**Trappola:** $\text{left}[m]$ conta la run che **termina in** $m$ stesso (incluso): il $k$-picco è quindi $\min(\text{left}[m], \text{right}[m]) - 1$, non $\min(\text{left}[m], \text{right}[m])$. Per la variante prev/next (es. colonnina più vicina), ricordarsi di inizializzare il sentinella quando il vicino non esiste ($\text{prev}[i] = -\infty$ oppure $0$, a seconda del problema).
