---
tags:
  - algoritmi
---
# Intersezione e appartenenza su insiemi
Esercizio di progettazione su insiemi (casistica [[Casistiche d'Esame Modulo I|intersezione e appartenenza su insiemi]]); ripasso: [[05 - Strutture Dati Elementari e Dizionari]] (dizionario, BST/AVL), [[04 - Algoritmi di Ordinamento]] (MergeSort, merge con due puntatori); checklist [[Piano Esame ASD - Modulo I]].

> [!info] Gli strumenti in programma (e l'hash set, che non lo è)
> Per i problemi su insiemi gli strumenti **del corso** sono due: un **AVL** usato come dizionario ordinato (insert/search in $O(\log n)$ *deterministico*, memoria proporzionale agli elementi **distinti**) e **ordina + due puntatori** ($O(n\log n)$, spesso $O(1)$ spazio extra). La scelta dipende dal vincolo: memoria $o(N)$ → AVL (cresce solo con i distinti); confronto/intersezione di due insiemi → sort+merge. L'**hash set** ($O(1)$ atteso) sarebbe più comodo, ma è **fuori programma** (non compare nelle slide né in [[05 - Strutture Dati Elementari e Dizionari]]): all'esame non si usa.

> [!question] Traccia — 02/02/2026
> L'album completo è composto da $N$ figurine (musicisti), numerate da $1$ a $N$. Il collezionista possiede **già** un sottoinsieme $A$ di dimensione $n$, con $n\ll N$ (ad esempio $N=n^3$). Compra poi $k$ pacchetti $P_1,\ldots,P_k$, ognuno contenente $3$ figurine ($P_i\subseteq\{1,\ldots,N\}$). Presi in input $A, P_1,\ldots,P_k$, calcolare quante figurine **mancano ancora** all'album dopo l'apertura dei pacchetti. **Vincolo:** tempo $o(nk)$ e memoria ausiliaria $o(N)$ (vietato allocare strutture di taglia $\Theta(N)$ come `boolean[1..N]`).

**Idea.** Le figurine possedute alla fine sono l'unione $A\cup P_1\cup\cdots\cup P_k$: la risposta è $N$ meno il numero di figurine **distinte** in tale unione. Un array `boolean[1..N]` la calcolerebbe ma richiede $\Theta(N)$ bit, violando il vincolo. La struttura **in programma** che rispetta $o(N)$ è un **AVL** usato come dizionario: vi si inseriscono prima le figurine di $A$, poi quelle dei pacchetti, ignorando i duplicati (prima una `search`, poi `insert` se assente). Il numero di nodi è $n_{\text{dist}}$ = figurine **distinte** possedute $\le n+3k$, e con $n\ll N$ resta $\ll N$ → memoria $O(n_{\text{dist}}) = o(N)$. Al termine la risposta è $N - n_{\text{dist}}$. *(Un hash set darebbe lo stesso risultato in $O(1)$ atteso, ma è fuori programma.)*

> [!info] Perché l'AVL rispetta il vincolo $o(N)$
> - $T$ = AVL delle figurine **possedute** distinte (sia quelle di $A$ sia quelle uscite dai pacchetti). Non si traccia *cosa manca* (sarebbe $\Theta(N)$), ma *cosa si ha*: molto meno.
> - $n_{\text{dist}} \le n+3k \ll N$ → memoria $O(n_{\text{dist}}) = o(N)$: è il cuore della soluzione, perché `boolean[1..N]` è proprio ciò che la traccia vieta.
> - Si inserisce solo se assente (`search` prima di `insert`): nessun duplicato, quindi i nodi sono esattamente le figurine distinte possedute e le mancanti sono $N - (\#\text{nodi})$.
> - L'AVL garantisce le operazioni in $O(\log n_{\text{dist}})$ **deterministico** — l'$O(1)$ dell'hash è solo *atteso*, e comunque fuori programma.

```pseudo
\begin{algorithm}
\caption{figurineMancanti($A[1..n]$, $P[1..k]$, $N$) → intero}
\begin{algorithmic}
\State $T \gets$ AVL vuoto; $\mathit{dist} \gets 0$
\For{$j \gets 1$ \To $n$} \Comment{figurine già possedute: l'insieme $A$}
  \If{\Call{Search}{$T$, $A[j]$} $=$ null}
    \State \Call{Insert}{$T$, $A[j]$}; $\mathit{dist} \gets \mathit{dist} + 1$
  \EndIf
\EndFor
\For{$i \gets 1$ \To $k$}
  \For{ogni figurina $f$ nel pacchetto $P[i]$} \Comment{$3$ figurine per pacchetto}
    \If{\Call{Search}{$T$, $f$} $=$ null} \Comment{$f$ non ancora posseduta}
      \State \Call{Insert}{$T$, $f$}; $\mathit{dist} \gets \mathit{dist} + 1$
    \EndIf
  \EndFor
\EndFor
\State \Return $N - \mathit{dist}$ \Comment{$\mathit{dist}=|A\cup P_1\cup\cdots\cup P_k|$}
\end{algorithmic}
\end{algorithm}
```

> [!question] Traccia — 26/06/2025
> Dati due array $A[1..n]$ e $B[1..m]$ di interi (con possibili duplicati), calcolare l'*inclusion coefficient* $\Phi(A,B)=|A\cap B|/|A|$, dove l'intersezione è su insiemi (ogni valore distinto contato al più una volta), in tempo $o(n^2)$.

*Approccio (A) sort+merge — $O((n+m)\log(n+m))$ (è la soluzione da consegnare):* ordinare $A$ e $B$ separatamente, poi scandire con due puntatori; ad ogni match avanzare entrambi saltando i duplicati dello stesso valore.

> [!info] Le variabili del merge a due puntatori
> - $i,\ j$ = puntatori che avanzano in $A$ e $B$ (entrambi ordinati). Si confronta $A[i]$ con $B[j]$: chi è minore avanza; in caso di **match** si conta e si avanzano entrambi.
> - $\text{cnt}$ = numero di **valori distinti** presenti in entrambi ($|A\cap B|$). Diviso per $n$ alla fine dà $\Phi$.
> - **Salto dei duplicati**: dopo un match su valore $v$, i due `while` interni fanno avanzare $i$ e $j$ oltre *tutte* le copie di $v$. Senza questo, lo stesso valore comune verrebbe contato più volte (l'intersezione è su insiemi).

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

> [!example] Esempio — $A = [1, 2, 2, 3]$, $B = [2, 2, 4]$ (già ordinati)
> - $i=1,j=1$: $A[1]=1 < B[1]=2$ → $i=2$.
> - $i=2,j=1$: $A[2]=2 = B[1]=2$ → **match**, $v=2$, $\text{cnt}=1$. Salto duplicati: $i$ scorre $2\to3\to4$ (oltre le due copie di $2$), $j$ scorre $1\to2\to3$.
> - $i=4,j=3$: $A[4]=3 < B[3]=4$ → $i=5$. Ora $i>n$ → fine.
>
> $\text{cnt}=1$ (un solo valore distinto in comune, il $2$); $\Phi = \text{cnt}/n = 1/4$. Senza il salto dei duplicati il $2$ sarebbe stato contato due volte.

*Approccio (B) hash set — $O(n+m)$ atteso, **fuori programma**:* inserendo $B$ in un hash set si avrebbe tempo lineare atteso, ma la hash table non è trattata dal corso → non utilizzabile all'esame. Variante deterministica e in programma: un **AVL** sulle chiavi distinte di $B$ (lookup $O(\log m)$), poi si scandisce $A$ deduplicato contando i valori presenti in $B$ → $O((n+m)\log m)$. La soluzione canonica resta la (A).

**Complessità:** figurine mancanti con AVL $O((n+3k)\log n_{\text{dist}}) = O((n+k)\log(n+k))$ tempo ($n$ inserimenti per $A$ più $3k$ per i pacchetti, ciascuno su un AVL di taglia $\le n+3k$), che batte la scansione naive $O(nk)$ e rispetta il vincolo $o(nk)$; memoria $O(n_{\text{dist}}) = o(N)$. $\Phi$ con sort+merge $O((n+m)\log(n+m))$ tempo, $O(1)$ spazio extra (oppure AVL, $O((n+m)\log m)$). L'hash set darebbe tempi *attesi* migliori ($O(n+k)$, $O(n+m)$) ma è fuori programma.
**Trappola:** allocare `boolean[1..N]` viola il vincolo $o(N)$ quando $N$ è molto grande → si usa l'AVL (cresce solo con i distinti), **non** una hash table (fuori programma). Non dimenticare di inserire **anche le figurine di $A$ già possedute**: contare solo quelle dei pacchetti sovrastima le mancanti — la risposta è $N-|A\cup P_1\cup\cdots\cup P_k|$, non $N-|P_1\cup\cdots\cup P_k|$. Nel merge a due puntatori è obbligatorio saltare tutti i duplicati dopo ogni match — omettendolo si conta lo stesso valore distinto più volte, gonfiando $\text{cnt}$ oltre $|A\cap B|$.
