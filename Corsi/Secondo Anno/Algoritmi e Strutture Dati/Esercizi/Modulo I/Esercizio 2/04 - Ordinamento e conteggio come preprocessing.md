---
tags:
  - algoritmi
---
# Ordinamento e conteggio come preprocessing
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]] in cui il cuore della soluzione è **ordinare o contare** in fase di preprocessing, dopodiché una passata lineare (greedy, due puntatori, interleaving) risolve il problema. Ripasso: [[04 - Algoritmi di Ordinamento]] (Integer Sort, MergeSort); checklist [[Piano Esame ASD - Modulo I]].
## Pattern A — Integer Sort con pochi outlier
> [!question] Traccia — 22/06/2022
> Sia $A[1..n]$ un vettore di interi tale che **tutti gli elementi tranne $O(n^{2/3})$** sono compresi fra $1$ e $10n$. Progettare un algoritmo di complessità **lineare** che ordina $A$.

**Idea.** Si separa $A$ in due parti con una scansione: gli elementi *in range* ($1 \le x \le 10n$) e i $O(n^{2/3})$ *outlier* fuori range. Le due parti si ordinano con algoritmi diversi e poi si fondono:
1. **In range** con [[04 - Algoritmi di Ordinamento|Integer Sort]]: il range è $[1, 10n]$, quindi un array di contatori di taglia $10n$ ordina questi elementi in $O(n + 10n) = O(n)$.
2. **Outlier** con un ordinamento per confronto (es. MergeSort): sono $O(n^{2/3})$ elementi, costo $O(n^{2/3}\log n^{2/3}) = O(n^{2/3}\log n) = o(n)$.
3. **Merge** delle due sequenze ordinate con due puntatori in $O(n)$.

Il totale è $O(n)$ perché ogni fase è $O(n)$ o $o(n)$.
```pseudo
\begin{algorithm}
\caption{ordinaConOutlier($A$, $n$) → array ordinato}
\begin{algorithmic}
\State $\text{IN} \gets [\,]$; $\text{OUT} \gets [\,]$
\For{$i \gets 1$ \To $n$}
  \If{$1 \leq A[i]$ e $A[i] \leq 10n$}
    \State aggiungi $A[i]$ a $\text{IN}$
  \Else
    \State aggiungi $A[i]$ a $\text{OUT}$ \Comment{$|\text{OUT}| = O(n^{2/3})$}
  \EndIf
\EndFor
\State \Call{IntegerSort}{$\text{IN}$, range $[1,10n]$} \Comment{$O(n)$}
\State \Call{MergeSort}{$\text{OUT}$} \Comment{$O(n^{2/3}\log n) = o(n)$}
\State \Return \Call{Merge}{$\text{IN}$, $\text{OUT}$} \Comment{fusione a due puntatori, $O(n)$}
\end{algorithmic}
\end{algorithm}
```
**Complessità:** $O(n)$ tempo; spazio $O(n)$ per i contatori e gli array.
**Trappola:** ordinare *tutto* $A$ con un confronto darebbe $O(n\log n)$, non lineare; e Integer Sort sul vettore intero fallisce perché gli outlier possono avere valori arbitrariamente grandi (range non limitato da $10n$). La taglia dell'array dei contatori deve essere il range **effettivo** degli elementi in input ($10n+1$ celle), non $n$.
## Pattern B — ordina + due puntatori
> [!question] Traccia — 21/01/2025
> Dato un array $A[1..n]$ di $n$ interi positivi con $n$ pari, determinare se è possibile partizionare gli $n$ elementi in $n/2$ coppie tali che ogni coppia abbia la stessa somma; in caso affermativo restituire le coppie, altrimenti dichiarare impossibile. Punteggio pieno per $o(n^2)$.

**Idea.** Se la partizione esiste, ogni coppia vale $t = 2S/n$ con $S = \sum_i A[i]$. Si procede in tre passi:
1. Calcola $S$ e verifica $2S \bmod n = 0$; altrimenti impossibile (target non intero).
2. Ordina $A$ con MergeSort. Per *exchange argument*, l'elemento più piccolo deve accoppiarsi col più grande, il secondo minimo col secondo massimo, ecc.: ogni altra assegnazione produce almeno una coppia con somma diversa da $t$.
3. Verifica $A[i] + A[n+1-i] = t$ per $i = 1, \ldots, n/2$; se tutte passano le coppie $(A[i], A[n+1-i])$ sono la risposta.
```pseudo
\begin{algorithm}
\caption{CoppieSommaFissa($A$, $n$) → lista di coppie oppure "impossibile"}
\begin{algorithmic}
\State $S \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $S \gets S + A[i]$
\EndFor
\If{$2S \bmod n \neq 0$}
  \State \Return impossibile \Comment{target non intero}
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
**Complessità:** $O(n \log n)$, dominata dal MergeSort ($o(n^2)$, punteggio pieno); $S$ e le scansioni di verifica/ricostruzione sono $O(n)$.
**Trappola:** verificare che $t$ sia intero **prima** di ordinare; altrimenti si esegue inutilmente il MergeSort su un'istanza già impossibile.
## Pattern C — conteggio frequenze + interleaving
> [!question] Traccia — 09/09/2024
> Dato un array $A[1..n]$ ($n$ pari), permutare gli elementi in modo che non ci siano mai due elementi uguali adiacenti, oppure dichiarare correttamente che è impossibile. Spazio $O(n)$.

**Idea.** Si contano le frequenze dei valori distinti. Una permutazione senza uguali adiacenti esiste **se e solo se** la frequenza massima $f_{\max}$ non supera $\lceil n/2 \rceil = n/2$ (con $n$ pari): un valore più frequente non potrebbe essere separato. Se ammissibile, si **interleava**: si dispongono gli elementi in ordine di frequenza decrescente nelle posizioni pari $0,2,4,\dots$ e poi in quelle dispari $1,3,5,\dots$. Così le copie di uno stesso valore (contigue nell'ordine per frequenza) finiscono a distanza $\geq 2$.
```pseudo
\begin{algorithm}
\caption{permutaSenzaAdiacenti($A$, $n$) → array B oppure "impossibile"}
\begin{algorithmic}
\State conta le frequenze dei valori distinti di $A$ \Comment{hash map o Integer Sort, $O(n)$}
\State $f_{\max} \gets$ frequenza massima
\If{$f_{\max} > n/2$}
  \State \Return impossibile
\EndIf
\State $\text{ord} \gets$ elementi di $A$ ordinati per frequenza decrescente (copie dello stesso valore contigue)
\State alloca $B[0..n-1]$; $pos \gets 0$
\For{$t \gets 0$ \To $n-1$}
  \State $B[pos] \gets \text{ord}[t]$
  \State $pos \gets pos + 2$
  \If{$pos \geq n$} \State $pos \gets 1$ \EndIf \Comment{esaurite le pari, si passa alle dispari}
\EndFor
\State \Return $B$
\end{algorithmic}
\end{algorithm}
```
**Complessità:** $O(n\log n)$ per l'ordinamento per frequenza (o $O(n)$ con Integer Sort se il range dei valori è limitato); spazio $O(n)$ per i contatori e per $B$.
**Trappola:** la condizione di ammissibilità è $f_{\max} \leq n/2$, non $f_{\max} < n$; e l'interleaving deve riempire **prima tutte** le posizioni pari e poi le dispari — invertendo l'ordine, due copie del valore più frequente possono cadere adiacenti a cavallo del passaggio pari→dispari.
