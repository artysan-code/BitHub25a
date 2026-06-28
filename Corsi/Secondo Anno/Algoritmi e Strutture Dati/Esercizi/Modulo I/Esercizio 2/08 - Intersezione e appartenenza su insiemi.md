---
tags:
  - algoritmi
---
# Intersezione e appartenenza su insiemi
Esercizio di progettazione su insiemi (casistica [[Casistiche d'Esame Modulo I|intersezione e appartenenza su insiemi]]); ripasso: [[05 - Strutture Dati Elementari e Dizionari]] (hash table, insert/lookup), [[04 - Algoritmi di Ordinamento]] (MergeSort, merge con due puntatori); checklist [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 02/02/2026
> Una collezione completa conta $N$ figurine distinte, identificate da interi in $[1, N]$, con $N$ molto grande. Un collezionista riceve $p$ pacchetti; ogni pacchetto contiene un sottoinsieme (con possibili ripetizioni) di figurine. Determinare quante figurine mancano ancora alla collezione. **Vincolo:** la memoria disponibile è $o(N)$; è vietato allocare strutture di taglia $\Theta(N)$ come `boolean[1..N]`.

**Idea.** Un array `boolean[1..N]` richiederebbe $\Theta(N)$ bit, violando il vincolo. Si usa invece un **hash set** $H$ che memorizza solo le figurine effettivamente ricevute: $|H| \le n_{\text{dist}}$, dove $n_{\text{dist}}$ è il numero di figurine distinte tra tutti i pacchetti, tipicamente $\ll N$. Per ogni figurina $f$ di ogni pacchetto si chiama $\text{Insert}(H, f)$: se $f \in H$ l'inserimento è idempotente e la dimensione non cresce. Al termine la risposta è $N - |H|$.

```pseudo
\begin{algorithm}
\caption{figurineMancanti($P[1..p]$, $N$) → intero}
\begin{algorithmic}
\State $H \gets$ hash set vuoto
\For{$i \gets 1$ \To $p$}
  \For{ogni figurina $f$ nel pacchetto $P[i]$}
    \State \Call{Insert}{$H$, $f$} \Comment{inserisce $f$ solo se non già presente}
  \EndFor
\EndFor
\State \Return $N - |H|$
\end{algorithmic}
\end{algorithm}
```

> [!question] Traccia — 26/06/2025
> Dati due array $A[1..n]$ e $B[1..m]$ di interi (con possibili duplicati), calcolare l'*inclusion coefficient* $\Phi(A,B)=|A\cap B|/|A|$, dove l'intersezione è su insiemi (ogni valore distinto contato al più una volta), in tempo $o(n^2)$.

*Approccio (A) sort+merge — $O((n+m)\log(n+m))$:* ordinare $A$ e $B$ separatamente, poi scandire con due puntatori; ad ogni match avanzare entrambi saltando i duplicati dello stesso valore.

```pseudo
\begin{algorithm}
\caption{calcolaPhi($A[1..n]$, $B[1..m]$) → reale}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}; \Call{MergeSort}{$B$}
\State $i \gets 1$; $j \gets 1$; $\text{cnt} \gets 0$
\While{$i \le n$ e $j \le m$}
  \If{$A[i] = B[j]$}
    \State $v \gets A[i]$; $\text{cnt} \gets \text{cnt}+1$
    \While{$i \le n$ e $A[i] = v$} \State $i \gets i+1$ \EndWhile \Comment{salta duplicati in $A$}
    \While{$j \le m$ e $B[j] = v$} \State $j \gets j+1$ \EndWhile \Comment{salta duplicati in $B$}
  \ElsIf{$A[i] < B[j]$}
    \State $i \gets i+1$
  \Else
    \State $j \gets j+1$
  \EndIf
\EndWhile
\State \Return $\text{cnt}/n$
\end{algorithmic}
\end{algorithm}
```

*Approccio (B) hash set — $O(n+m)$ atteso:* inserire tutti gli elementi di $B$ in un hash set $H_B$; scansionare $A$ tenendo traccia dei valori già contati (oppure deduplicare $A$ preventivamente) e incrementare $\text{cnt}$ per ogni valore distinto di $A$ trovato in $H_B$.

**Complessità:** approccio hash set (figurine mancanti) $O(M)$ atteso con $M$ = numero totale di figurine nei $p$ pacchetti, memoria $O(n_{\text{dist}}) = o(N)$; sort+merge per $\Phi$ in $O((n+m)\log(n+m))$ tempo, $O(1)$ spazio extra; hash set per $\Phi$ in $O(n+m)$ atteso, $O(\min(n,m))$ memoria.
**Trappola:** allocare `boolean[1..N]` viola il vincolo $o(N)$ quando $N$ è molto grande; nel merge a due puntatori è obbligatorio saltare tutti i duplicati dopo ogni match — omettendolo si conta lo stesso valore distinto più volte, gonfiando $\text{cnt}$ oltre $|A\cap B|$.
