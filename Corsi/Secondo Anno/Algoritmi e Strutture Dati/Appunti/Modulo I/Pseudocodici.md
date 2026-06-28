---
tags:
  - algoritmi
  - strutture-dati
---
# Pseudocodici — Formulario (Modulo I)
Raccolta di **tutti** gli pseudocodici del Modulo I in sintassi `pseudo` (plugin `pseudocode-in-obs`), pensata come **formulario d'esame**: da consultare per l'**Esercizio 1.C** (problema → algoritmo → costo), l'**Esercizio 2** (progettazione con pseudocodice) e l'**Esercizio 3** (modellazione). Ogni gruppo rimanda alla nota che lo spiega per esteso. Per le complessità complete vedi il [[#Riepilogo complessità]] in fondo.
## Convenzioni di lettura
Array **1-based**; $A[i;f]$ è il sottovettore dagli indici $i$ a $f$; $\gets$ è l'assegnazione; `null` il puntatore nullo; $\lfloor\cdot\rfloor$ la parte intera inferiore. Le keyword strutturali (`for`/`while`/`if`…) sono in inglese (sintassi pseudocode.js stile LaTeX `algorithmic`); i connettori (`e`, `o`, `scambia … con …`) restano in italiano come testo. Il nome e la firma di ogni procedura stanno nel `\caption`.
## Ricorsione: il problema di Fibonacci
Sei modi di calcolare $F_n$, dalla formula chiusa alla potenza di matrice logaritmica. → [[01 - Il Problema di Fibonacci]]
### fibonacci1 — Formula di Binet
Formula chiusa con il rapporto aureo $\phi$; $O(1)$ aritmetico ma instabile numericamente.
```pseudo
\begin{algorithm}
\caption{fibonacci1($n$) → intero}
\begin{algorithmic}
\State \Return $\frac{1}{\sqrt{5}} \cdot (\phi^n - \hat{\phi}^n)$
\end{algorithmic}
\end{algorithm}
```
### fibonacci2 — Ricorsione diretta
Definizione ricorsiva pura; tempo esponenziale $O(\phi^n)$ per i sottoproblemi ripetuti.
```pseudo
\begin{algorithm}
\caption{fibonacci2($n$) → intero}
\begin{algorithmic}
\If{$n \leq 2$}
  \State \Return $1$
\Else
  \State \Return \Call{fibonacci2}{$n-1$} $+$ \Call{fibonacci2}{$n-2$}
\EndIf
\end{algorithmic}
\end{algorithm}
```
### fibonacci3 — Programmazione dinamica (array)
Memorizza i risultati in un array; tempo $\Theta(n)$, spazio $\Theta(n)$.
```pseudo
\begin{algorithm}
\caption{fibonacci3($n$) → intero}
\begin{algorithmic}
\State sia $Fib$ un array di $n$ interi
\State $Fib[1] \gets 1$; $Fib[2] \gets 1$
\For{$i \gets 3$ \To $n$}
  \State $Fib[i] \gets Fib[i-1] + Fib[i-2]$
\EndFor
\State \Return $Fib[n]$
\end{algorithmic}
\end{algorithm}
```
### fibonacci4 — Iterativo con spazio costante
Tiene solo gli ultimi due valori; tempo $\Theta(n)$, spazio $\Theta(1)$.
```pseudo
\begin{algorithm}
\caption{fibonacci4($n$) → intero}
\begin{algorithmic}
\State $a \gets 1$; $b \gets 1$; $c \gets 1$
\For{$i \gets 3$ \To $n$}
  \State $c \gets a + b$
  \State $a \gets b$
  \State $b \gets c$
\EndFor
\State \Return $c$
\end{algorithmic}
\end{algorithm}
```
### fibonacci5 — Potenza di matrice (iterativa)
Usa $\begin{psmallmatrix}1&1\\1&0\end{psmallmatrix}^{\,n-1}$; ancora $\Theta(n)$ prodotti di matrici.
```pseudo
\begin{algorithm}
\caption{fibonacci5($n$) → intero}
\begin{algorithmic}
\State $M \gets [[1,1],[1,0]]$
\State $R \gets [[1,0],[0,1]]$ \Comment{matrice identità}
\For{$i \gets 1$ \To $n-1$}
  \State $R \gets R \cdot M$
\EndFor
\State \Return $R[0][0]$ \Comment{$R[0][0] = F_n$}
\end{algorithmic}
\end{algorithm}
```
### fibonacci6 — Elevamento al quadrato veloce
Potenza di matrice per quadrati ripetuti; tempo $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{fibonacci6($n$) → intero}
\begin{algorithmic}
\State $M \gets [[1,1],[1,0]]$
\State $R \gets$ \Call{potenzaDiMatrice}{$M, n-1$}
\State \Return $R[0][0]$
\end{algorithmic}
\end{algorithm}

\begin{algorithm}
\caption{potenzaDiMatrice($A$, $k$) → matrice}
\begin{algorithmic}
\If{$k = 0$}
  \State \Return $[[1,0],[0,1]]$ \Comment{identità}
\EndIf
\State $P \gets$ \Call{potenzaDiMatrice}{$A, \lfloor k/2 \rfloor$}
\State $P \gets P \cdot P$
\If{$k$ è dispari}
  \State $P \gets P \cdot A$
\EndIf
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```
## Ricerca in un vettore
Mattoni elementari dell'Esercizio 1.C. *(Implementazioni standard; la ricorrenza della ricerca binaria, $T(n)=T(n/2)+O(1)$, è in [[03 - Equazioni di Ricorrenza]].)*
### RicercaSequenziale
Scorre tutto il vettore; $O(n)$, unico metodo possibile su vettore **non ordinato**.
```pseudo
\begin{algorithm}
\caption{RicercaSequenziale($A, k$) — indice di $k$ in $A[1;n]$, o $null$}
\begin{algorithmic}
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = k$}
    \State \Return $i$
  \EndIf
\EndFor
\State \Return $null$
\end{algorithmic}
\end{algorithm}
```
### RicercaBinaria (iterativa)
Dimezza l'intervallo di ricerca; richiede $A$ **ordinato**; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{RicercaBinaria($A, k$) — indice di $k$ in $A[1;n]$ ordinato, o $null$}
\begin{algorithmic}
\State $i \gets 1$; $f \gets n$
\While{$i \leq f$}
  \State $m \gets \lfloor (i+f)/2 \rfloor$
  \If{$A[m] = k$}
    \State \Return $m$
  \ElsIf{$A[m] < k$}
    \State $i \gets m+1$
  \Else
    \State $f \gets m-1$
  \EndIf
\EndWhile
\State \Return $null$
\end{algorithmic}
\end{algorithm}
```
### RicercaBinaria (ricorsiva)
Stessa idea in forma ricorsiva: ricorrenza $T(n) = T(n/2) + O(1) = O(\log n)$.
```pseudo
\begin{algorithm}
\caption{RicercaBinariaRic($A, k, i, f$) — cerca $k$ in $A[i;f]$ ordinato}
\begin{algorithmic}
\If{$i > f$}
  \State \Return $null$
\EndIf
\State $m \gets \lfloor (i+f)/2 \rfloor$
\If{$A[m] = k$}
  \State \Return $m$
\ElsIf{$A[m] < k$}
  \State \Return \Call{RicercaBinariaRic}{$A, k, m+1, f$}
\Else
  \State \Return \Call{RicercaBinariaRic}{$A, k, i, m-1$}
\EndIf
\end{algorithmic}
\end{algorithm}
```
## Ordinamento
I quadratici, i divide-et-impera, l'ordinamento per confronti ($\Omega(n\log n)$) e i lineari per chiavi intere. → [[04 - Algoritmi di Ordinamento]]
### SelectionSort
Seleziona ripetutamente il minimo del suffisso e lo porta in testa; $\Theta(n^2)$ sempre.
```pseudo
\begin{algorithm}
\caption{SelectionSort($A$)}
\begin{algorithmic}
\For{$k \gets 0$ \To $n-2$}
  \State $m \gets k+1$
  \For{$j \gets k+2$ \To $n$}
    \If{$A[j] < A[m]$}
      \State $m \gets j$
    \EndIf
  \EndFor
  \State scambia $A[m]$ con $A[k+1]$
\EndFor
\end{algorithmic}
\end{algorithm}
```
### InsertionSort
Inserisce ogni elemento nella parte già ordinata a sinistra; $O(n^2)$, ma $\Omega(n)$ se quasi ordinato.
```pseudo
\begin{algorithm}
\caption{InsertionSort($A$)}
\begin{algorithmic}
\For{$k \gets 1$ \To $n-1$}
  \State $x \gets A[k+1]$
  \State $j \gets k$
  \While{$j > 0$ e $A[j] > x$}
    \State $A[j+1] \gets A[j]$
    \State $j \gets j-1$
  \EndWhile
  \State $A[j+1] \gets x$
\EndFor
\end{algorithmic}
\end{algorithm}
```
### BubbleSort
Scambi di adiacenti finché l'array è ordinato; $O(n^2)$.
```pseudo
\begin{algorithm}
\caption{BubbleSort($A$)}
\begin{algorithmic}
\For{$k \gets 1$ \To $n-1$}
  \For{$j \gets 1$ \To $n-k$}
    \If{$A[j] > A[j+1]$}
      \State scambia $A[j]$ con $A[j+1]$
    \EndIf
  \EndFor
\EndFor
\end{algorithmic}
\end{algorithm}
```
### MergeSort
Divide a metà, ordina ricorsivamente, fonde; $\Theta(n\log n)$ sempre, stabile, non in loco.
```pseudo
\begin{algorithm}
\caption{MergeSort($A, i, f$) — ordina $A[i;f]$}
\begin{algorithmic}
\If{$i < f$}
  \State $m \gets \lfloor (i+f)/2 \rfloor$
  \State \Call{MergeSort}{$A, i, m$}
  \State \Call{MergeSort}{$A, m+1, f$}
  \State \Call{Merge}{$A, i, m, f$}
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Merge
Fonde due sottovettori ordinati contigui usando un array ausiliario; $\Theta(f_2 - i_1)$.
```pseudo
\begin{algorithm}
\caption{Merge($A, i_1, f_1, f_2$) — fonde $A[i_1;f_1]$ e $A[f_1+1;f_2]$, output in $A[i_1;f_2]$}
\begin{algorithmic}
\State Sia $X$ un array ausiliario di lunghezza $f_2 - i_1 + 1$
\State $i \gets 1$; $k_1 \gets i_1$; $k_2 \gets f_1+1$
\While{$k_1 \leq f_1$ e $k_2 \leq f_2$}
  \If{$A[k_1] \leq A[k_2]$}
    \State $X[i] \gets A[k_1]$; incrementa $i$ e $k_1$
  \Else
    \State $X[i] \gets A[k_2]$; incrementa $i$ e $k_2$
  \EndIf
\EndWhile
\If{$k_1 \leq f_1$}
  \State copia $A[k_1;f_1]$ alla fine di $X$
\Else
  \State copia $A[k_2;f_2]$ alla fine di $X$
\EndIf
\State copia $X$ in $A[i_1;f_2]$
\end{algorithmic}
\end{algorithm}
```
### QuickSort
Partiziona attorno a un perno e ordina ricorsivamente le due parti; $\Theta(n\log n)$ medio, $O(n^2)$ peggiore.
```pseudo
\begin{algorithm}
\caption{QuickSort($A, i, f$) — ordina $A[i;f]$}
\begin{algorithmic}
\If{$i < f$}
  \State $m \gets$ \Call{Partition}{$A, i, f$}
  \State \Call{QuickSort}{$A, i, m-1$}
  \State \Call{QuickSort}{$A, m+1, f$}
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Partition
Partiziona $A[i;f]$ rispetto al perno $A[i]$ e ne restituisce la posizione finale; $\Theta(f-i)$.
```pseudo
\begin{algorithm}
\caption{Partition($A, i, f$) — partiziona $A[i;f]$ rispetto ad $A[i]$}
\begin{algorithmic}
\State $x \gets A[i]$
\State $inf \gets i$
\State $sup \gets f+1$
\While{$\mathrm{true}$}
  \Repeat
    \State $inf \gets inf+1$
  \Until{$inf > f$ o $A[inf] > x$}
  \Repeat
    \State $sup \gets sup-1$
  \Until{$A[sup] \leq x$}
  \If{$inf < sup$}
    \State scambia $A[inf]$ e $A[sup]$
  \Else
    \State \textbf{break}
  \EndIf
\EndWhile
\State scambia $A[i]$ e $A[sup]$ \Comment{posiziona il perno}
\State \Return $sup$ \Comment{restituisce la posizione del perno}
\end{algorithmic}
\end{algorithm}
```
### HeapSort
Costruisce un max-heap e ne estrae il massimo $n-1$ volte; $O(n\log n)$, in loco. *(Per `Heapify`/`fixHeap` vedi [[#Heap e code con priorità]].)*
```pseudo
\begin{algorithm}
\caption{HeapSort($A$)}
\begin{algorithmic}
\State \Call{Heapify}{$A$} \Comment{costruisce il max-heap: $O(n)$}
\State $\mathit{heapsize}[A] \gets n$
\For{$i \gets n$ downto $2$} \Comment{$n-1$ estrazioni}
  \State scambia $A[1]$ e $A[i]$ \Comment{sposta il massimo nella posizione $i$}
  \State $\mathit{heapsize}[A] \gets \mathit{heapsize}[A]-1$ \Comment{riduce l'heap}
  \State \Call{fixHeap}{$1, A$} \Comment{ripristina la proprietà heap: $O(\log n)$}
\EndFor
\end{algorithmic}
\end{algorithm}
```
### IntegerSort (Counting Sort)
Ordina chiavi in $\{1,\dots,k\}$ contando le occorrenze; $O(n+k)$, lineare se $k = O(n)$.
```pseudo
\begin{algorithm}
\caption{IntegerSort($X, k$)}
\begin{algorithmic}
\State Sia $Y$ un array di dimensione $k$
\For{$i \gets 1$ \To $k$} \Comment{$O(k)$: inizializza contatori}
  \State $Y[i] \gets 0$
\EndFor
\For{$i \gets 1$ \To $n$} \Comment{$O(n)$: conta le occorrenze}
  \State incrementa $Y[X[i]]$
\EndFor
\State $j \gets 1$
\For{$i \gets 1$ \To $k$} \Comment{$O(n+k)$: ricostruisce $X$}
  \While{$Y[i] > 0$}
    \State $X[j] \gets i$
    \State incrementa $j$
    \State decrementa $Y[i]$
  \EndWhile
\EndFor
\end{algorithmic}
\end{algorithm}
```
### BucketSort
Distribuisce i record in $k$ bucket per chiave e li concatena; $O(n+k)$, stabile.
```pseudo
\begin{algorithm}
\caption{BucketSort($X, k$)}
\begin{algorithmic}
\State Sia $Y$ un array di dimensione $k$
\For{$i \gets 1$ \To $k$} \Comment{$O(k)$}
  \State $Y[i] \gets$ lista vuota
\EndFor
\For{$i \gets 1$ \To $n$} \Comment{$O(n)$}
  \State appendi il record $X[i]$ alla lista $Y[\mathit{chiave}(X[i])]$
\EndFor
\For{$i \gets 1$ \To $k$} \Comment{$O(n+k)$}
  \State copia ordinatamente in $X$ gli elementi della lista $Y[i]$
\EndFor
\end{algorithmic}
\end{algorithm}
```
### Oracolo per range counting — costruzione
Somme prefisse dei conteggi: precalcolo $O(n+k)$ per poi contare quante chiavi cadono in $[a,b]$ in $O(1)$.
```pseudo
\begin{algorithm}
\caption{CostruisciOracolo($X, k$)}
\begin{algorithmic}
\State Sia $Y$ un array di dimensione $k$
\For{$i \gets 1$ \To $k$}
  \State $Y[i] \gets 0$
\EndFor
\For{$i \gets 1$ \To $n$} \Comment{conta le occorrenze (come IntegerSort)}
  \State incrementa $Y[X[i]]$
\EndFor
\For{$i \gets 2$ \To $k$} \Comment{somme prefisse}
  \State $Y[i] \gets Y[i] + Y[i-1]$
\EndFor
\State \Return $Y$
\end{algorithmic}
\end{algorithm}
```
### Oracolo per range counting — interrogazione
Risponde "quante chiavi in $[a,b]$" con una sottrazione di prefissi; $O(1)$.
```pseudo
\begin{algorithm}
\caption{InterrogaOracolo($Y, k, a, b$)}
\begin{algorithmic}
\If{$b > k$}
  \State $b \gets k$
\EndIf
\If{$a \leq 1$}
  \State \Return $Y[b]$
\Else
  \State \Return $Y[b] - Y[a-1]$
\EndIf
\end{algorithmic}
\end{algorithm}
```
## Strutture dati elementari
Pila e coda come array; tutte le operazioni in $O(1)$. → [[05 - Strutture Dati Elementari e Dizionari]]
### Pila — push
Inserimento in cima (LIFO); $O(1)$.
```pseudo
\begin{algorithm}
\caption{push($P$, $e$)}
\begin{algorithmic}
\State $P.\text{top} \gets P.\text{top} + 1$
\State $P[P.\text{top}] \gets e$
\end{algorithmic}
\end{algorithm}
```
### Pila — pop
Estrazione dalla cima; $O(1)$.
```pseudo
\begin{algorithm}
\caption{pop($P$)}
\begin{algorithmic}
\State $e \gets P[P.\text{top}]$
\State $P.\text{top} \gets P.\text{top} - 1$
\State \Return $e$
\end{algorithmic}
\end{algorithm}
```
### Coda — enqueue
Inserimento in coda su array circolare (FIFO); $O(1)$.
```pseudo
\begin{algorithm}
\caption{enqueue($C$, $e$)}
\begin{algorithmic}
\State $C[C.\text{tail}] \gets e$
\State $C.\text{tail} \gets (C.\text{tail} + 1) \bmod n$
\end{algorithmic}
\end{algorithm}
```
### Coda — dequeue
Estrazione dalla testa su array circolare; $O(1)$.
```pseudo
\begin{algorithm}
\caption{dequeue($C$)}
\begin{algorithmic}
\State $e \gets C[C.\text{head}]$
\State $C.\text{head} \gets (C.\text{head} + 1) \bmod n$
\State \Return $e$
\end{algorithmic}
\end{algorithm}
```
## Alberi: visite e attraversamenti
Visite di un albero (binario o generico con figli) e operazioni ricorsive elementari; tutte $\Theta(n)$. → [[05 - Strutture Dati Elementari e Dizionari]]
### DFS iterativa (con pila)
Visita in profondità con pila esplicita; spinge prima il figlio destro per visitare prima il sinistro.
```pseudo
\begin{algorithm}
\caption{DFS($r$)}
\begin{algorithmic}
\State Pila $S$
\State \Call{S.push}{$r$}
\While{$S$ non vuota}
  \State $u \gets$ \Call{S.pop}{}
  \If{$u \neq \text{null}$}
    \State \Call{visita}{$u$}
    \State \Call{S.push}{figlio destro di $u$}
    \State \Call{S.push}{figlio sinistro di $u$}
  \EndIf
\EndWhile
\end{algorithmic}
\end{algorithm}
```
### DFS ricorsiva (pre / in / post-order)
La posizione della `visita` determina l'ordine: preordine, simmetrico, postordine.
```pseudo
\begin{algorithm}
\caption{DFS\_ricorsiva($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return
\EndIf
\State [\Call{visita}{$r$}] \Comment{preordine: radice prima}
\State \Call{DFS\_ricorsiva}{figlio sinistro di $r$}
\State [\Call{visita}{$r$}] \Comment{simmetrica: radice in mezzo}
\State \Call{DFS\_ricorsiva}{figlio destro di $r$}
\State [\Call{visita}{$r$}] \Comment{postordine: radice dopo}
\end{algorithmic}
\end{algorithm}
```
### BFS (per livelli, con coda)
Visita in ampiezza di un albero con una coda; $\Theta(n)$.
```pseudo
\begin{algorithm}
\caption{BFS($r$)}
\begin{algorithmic}
\State Coda $Q$
\State \Call{Q.enqueue}{$r$}
\While{$Q$ non vuota}
  \State $u \gets$ \Call{Q.dequeue}{}
  \State \Call{visita}{$u$}
  \ForAll{figlio $v$ di $u$ (non null)}
    \State \Call{Q.enqueue}{$v$}
  \EndFor
\EndWhile
\end{algorithmic}
\end{algorithm}
```
### CalcolaAltezza
Altezza come $1 + \max$ delle altezze dei figli; foglia $= 0$, vuoto $= -1$.
```pseudo
\begin{algorithm}
\caption{CalcolaAltezza($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $-1$
\EndIf
\State $sin \gets$ \Call{CalcolaAltezza}{figlio sinistro di $r$}
\State $des \gets$ \Call{CalcolaAltezza}{figlio destro di $r$}
\State \Return $1 + \max\{sin, des\}$
\end{algorithmic}
\end{algorithm}
```
### CalcolaNumFoglie
Conta le foglie sommando ricorsivamente i due sottoalberi.
```pseudo
\begin{algorithm}
\caption{CalcolaNumFoglie($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $0$
\EndIf
\If{$r$ è una foglia}
  \State \Return $1$
\EndIf
\State $sin \gets$ \Call{CalcolaNumFoglie}{figlio sinistro di $r$}
\State $des \gets$ \Call{CalcolaNumFoglie}{figlio destro di $r$}
\State \Return $sin + des$
\end{algorithmic}
\end{algorithm}
```
### CalcolaGradoMedio
Grado medio dei nodi interni $=$ somma dei gradi / numero di nodi interni.
```pseudo
\begin{algorithm}
\caption{CalcolaGradoMedio($r$)}
\begin{algorithmic}
\State $n \gets$ numero di nodi dell'albero
\State $nfoglie \gets$ \Call{CalcolaNumFoglie}{$r$}
\If{$r \neq \text{null}$}
  \State \Return \Call{SommaGradi}{$r$} $/ (n - nfoglie)$
\EndIf
\end{algorithmic}
\end{algorithm}
```
### SommaGradi
Somma dei gradi (numero di figli) dei nodi interni.
```pseudo
\begin{algorithm}
\caption{SommaGradi($r$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $0$
\EndIf
\If{$r$ è una foglia}
  \State \Return $0$
\EndIf
\State $S \gets$ numero figli di $r$ $+$ \Call{SommaGradi}{figlio sinistro di $r$} $+$ \Call{SommaGradi}{figlio destro di $r$}
\State \Return $S$
\end{algorithmic}
\end{algorithm}
```
### CercaElemento (albero generico)
Ricerca lineare di una chiave in un albero **non** di ricerca: visita entrambi i sottoalberi.
```pseudo
\begin{algorithm}
\caption{CercaElemento($r$, $k$)}
\begin{algorithmic}
\If{$r = \text{null}$}
  \State \Return $\text{null}$
\EndIf
\If{$\text{chiave}(r) = k$}
  \State \Return $r$
\EndIf
\State $sin \gets$ \Call{CercaElemento}{figlio sinistro di $r$, $k$}
\If{$sin \neq \text{null}$}
  \State \Return $sin$
\EndIf
\State \Return \Call{CercaElemento}{figlio destro di $r$, $k$}
\end{algorithmic}
\end{algorithm}
```
### RiRadica (vettore dei padri)
Inverte i puntatori al padre lungo il cammino da $j$ alla vecchia radice; $O(\text{lunghezza cammino})$.
```pseudo
\begin{algorithm}
\caption{RiRadica($T$, $j$)}
\begin{algorithmic}
\State $x \gets j$
\State $px \gets T[j].\text{parent}$
\State $T[j].\text{parent} \gets \text{null}$
\While{$px \neq \text{null}$}
  \State $y \gets T[px].\text{parent}$
  \State $T[px].\text{parent} \gets x$
  \State $x \gets px$
  \State $px \gets y$
\EndWhile
\end{algorithmic}
\end{algorithm}
```
## Heap e code con priorità
Due rappresentazioni dello stesso concetto: **heap su array** (max-heap, usato da HeapSort) e **heap come albero quasi completo** (min-heap, coda con priorità). → [[07 - Code con Priorità e Heap]]
### fixHeap (heap su array, max-heap)
Spinge verso il basso il nodo $i$ scambiandolo col figlio maggiore finché la proprietà di max-heap è ripristinata; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{fixHeap($i, A$) — ripristina il max-heap nel sottoalbero radicato in $i$}
\begin{algorithmic}
\State $max \gets i$
\State $sx \gets 2i$; $dx \gets 2i+1$
\If{$sx \leq \mathit{heapsize}[A]$ e $A[sx] > A[max]$}
  \State $max \gets sx$
\EndIf
\If{$dx \leq \mathit{heapsize}[A]$ e $A[dx] > A[max]$}
  \State $max \gets dx$
\EndIf
\If{$max \neq i$}
  \State scambia $A[i]$ e $A[max]$
  \State \Call{fixHeap}{$max, A$}
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Heapify (costruzione del heap, $O(n)$)
Applica `fixHeap` ai nodi interni dal basso verso l'alto; costo $O(n)$ (non $O(n\log n)$).
```pseudo
\begin{algorithm}
\caption{Heapify($A$) — costruisce un max-heap da $A[1;n]$}
\begin{algorithmic}
\State $\mathit{heapsize}[A] \gets n$
\For{$i \gets \lfloor n/2 \rfloor$ downto $1$}
  \State \Call{fixHeap}{$i, A$}
\EndFor
\end{algorithmic}
\end{algorithm}
```
### muoviAlto (sift-up)
Risale lo heap (min-heap come albero) finché il nodo è $\geq$ del padre; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{muoviAlto($T, v$) — analogo a MoveUp}
\begin{algorithmic}
\While{$v \neq \text{radice}(T)$ and $\text{chiave}(v) < \text{chiave}(\text{padre}(v))$}
  \State scambia di posto $v$ e $\text{padre}(v)$ in $T$
  \State $v \gets \text{padre}(v)$
\EndWhile
\end{algorithmic}
\end{algorithm}
```
### muoviBasso (sift-down)
Scende verso il figlio di chiave minima finché la proprietà di min-heap è ripristinata; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{muoviBasso($T, v$) — analogo a FixHeap}
\begin{algorithmic}
\While{\text{vero}}
  \State sia $u$ il figlio di $v$ con chiave minima (se esiste)
  \If{$v$ non ha figli or $\text{chiave}(v) \leq \text{chiave}(u)$}
    \State \textbf{break}
  \EndIf
  \State scambia di posto $v$ e $u$ in $T$
  \State $v \gets u$
\EndWhile
\end{algorithmic}
\end{algorithm}
```
### findMin
Il minimo è la radice; $O(1)$.
```pseudo
\begin{algorithm}
\caption{findMin($T$)}
\begin{algorithmic}
\State \Return $\text{elem}(\text{radice}(T))$
\end{algorithmic}
\end{algorithm}
```
### insert (coda con priorità)
Aggiunge una foglia e la fa risalire; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{insert($T, e, k$)}
\begin{algorithmic}
\State crea un nuovo nodo $F$ con $\text{elem} \gets e$, $\text{chiave} \gets k$
\State aggiungi $F$ come ultima foglia di $T$
\State \Call{muoviAlto}{$T, F$}
\end{algorithmic}
\end{algorithm}
```
### delete (coda con priorità)
Scambia con l'ultima foglia, rimuove, e ripristina la proprietà heap; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{delete($T, v$)}
\begin{algorithmic}
\State scambia $v$ con l'ultima foglia $u$ di $T$
\State rimuovi $v$ (ora in ultima posizione)
\State ripristina la proprietà di heap su $u$: \Call{muoviAlto}{$T, u$} o \Call{muoviBasso}{$T, u$}
\end{algorithmic}
\end{algorithm}
```
### decreaseKey
Diminuisce la chiave e fa risalire; $O(\log n)$. Operazione chiave per Dijkstra.
```pseudo
\begin{algorithm}
\caption{decreaseKey($T, v, d$)}
\begin{algorithmic}
\State $\text{chiave}(v) \gets \text{chiave}(v) - d$
\State \Call{muoviAlto}{$T, v$}
\end{algorithmic}
\end{algorithm}
```
### increaseKey
Aumenta la chiave e fa scendere; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{increaseKey($T, v, d$)}
\begin{algorithmic}
\State $\text{chiave}(v) \gets \text{chiave}(v) + d$
\State \Call{muoviBasso}{$T, v$}
\end{algorithmic}
\end{algorithm}
```
### Heap binomiale — ristruttura
Fonde alberi binomiali dello stesso ordine appendendo la radice maggiore sotto la minore.
```pseudo
\begin{algorithm}
\caption{ristruttura($H$)}
\begin{algorithmic}
\State $i \gets 0$
\While{esistono due $B_i$ nella foresta}
  \State sia $T_1, T_2$ i due $B_i$ con radici $r_1, r_2$
  \If{$\text{chiave}(r_1) \leq \text{chiave}(r_2)$}
    \State poni $r_2$ come figlio di $r_1$
  \Else
    \State poni $r_1$ come figlio di $r_2$
  \EndIf
  \State $i \gets i + 1$
\EndWhile
\end{algorithmic}
\end{algorithm}
```
### Heap binomiale — deleteMin
Rimuove la radice minima e fonde i suoi figli con l'heap; $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{deleteMin($H$)}
\begin{algorithmic}
\State trova la radice $r$ con chiave minima (scorre le radici) in $O(\log n)$
\State rimuovi $r$ dalla lista delle radici di $H$
\State $H' \gets$ heap binomiale formato dai figli di $r$ (in ordine: $B_{h-1}, \ldots, B_0$)
\State \Return \Call{merge}{$H, H'$}
\end{algorithmic}
\end{algorithm}
```
## BST e AVL
Dizionario via albero binario di ricerca: tutte le operazioni costano $O(h)$, garantito $O(\log n)$ con l'auto-bilanciamento AVL. Convenzione del prof: chiavi **uguali a sinistra** ($\leq$ a sinistra, $>$ a destra). → [[06 - Alberi di Ricerca BST e AVL]]
### Search (BST)
Scende confrontando $k$ con la chiave corrente; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Search($T, k$) — ricerca la chiave $k$ nel BST $T$}
\begin{algorithmic}
\State $curr \gets T.radice$
\While{$curr \neq null$ e $k \neq chiave(curr)$}
  \If{$k \leq chiave(curr)$}
    \State $curr \gets curr.sx$
  \Else
    \State $curr \gets curr.dx$
  \EndIf
\EndWhile
\State \Return $curr$
\end{algorithmic}
\end{algorithm}
```
### Min (BST)
Segue sempre i puntatori sinistri; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Min($u$) — nodo con chiave minima nel sottoalbero di $u$}
\begin{algorithmic}
\State $curr \gets u$
\While{$curr.sx \neq null$}
  \State $curr \gets curr.sx$
\EndWhile
\State \Return $curr$
\end{algorithmic}
\end{algorithm}
```
### Max (BST)
Simmetrica a `Min`: segue sempre i puntatori destri; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Max($u$) — nodo con chiave massima nel sottoalbero di $u$}
\begin{algorithmic}
\State $curr \gets u$
\While{$curr.dx \neq null$}
  \State $curr \gets curr.dx$
\EndWhile
\State \Return $curr$
\end{algorithmic}
\end{algorithm}
```
### Successore (BST)
Minimo del sottoalbero destro, oppure il primo antenato di cui $u$ sta a sinistra; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Successore($u$) — restituisce il successore del nodo $u$}
\begin{algorithmic}
\If{$u.dx \neq null$}
  \State \Return \Call{Min}{$u.dx$}
\EndIf
\State $p \gets u.padre$
\While{$p \neq null$ e $u = p.dx$}
  \State $u \gets p$
  \State $p \gets p.padre$
\EndWhile
\State \Return $p$
\end{algorithmic}
\end{algorithm}
```
### Predecessore (BST)
Simmetrica al `Successore`: massimo del sottoalbero sinistro, oppure il primo antenato di cui $u$ sta a destra; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Predecessore($u$) — restituisce il predecessore del nodo $u$}
\begin{algorithmic}
\If{$u.sx \neq null$}
  \State \Return \Call{Max}{$u.sx$}
\EndIf
\State $p \gets u.padre$
\While{$p \neq null$ e $u = p.sx$}
  \State $u \gets p$
  \State $p \gets p.padre$
\EndWhile
\State \Return $p$
\end{algorithmic}
\end{algorithm}
```
### Insert (BST)
Scende fino a una foglia e aggancia il nuovo nodo; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Insert($T, e, k$) — inserisce l'elemento $e$ con chiave $k$ nel BST $T$}
\begin{algorithmic}
\State $u \gets$ nuovo nodo con $elem = e$, $chiave = k$
\State $padre \gets null$, $curr \gets T.radice$
\While{$curr \neq null$}
  \State $padre \gets curr$
  \If{$k \leq chiave(curr)$}
    \State $curr \gets curr.sx$
  \Else
    \State $curr \gets curr.dx$
  \EndIf
\EndWhile
\State $u.padre \gets padre$
\If{$padre = null$}
  \State $T.radice \gets u$ \Comment{albero era vuoto}
\ElsIf{$k \leq chiave(padre)$}
  \State $padre.sx \gets u$
\Else
  \State $padre.dx \gets u$
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Delete (BST)
Tre casi (0/1/2 figli); con due figli si rimuove fisicamente il successore e se ne copia il contenuto; $O(h)$.
```pseudo
\begin{algorithm}
\caption{Delete($T, u$) — rimuove il nodo $u$ dal BST $T$}
\begin{algorithmic}
\If{$u.sx = null$ o $u.dx = null$}
  \State $y \gets u$ \Comment{0 o 1 figlio: rimuovi $u$}
\Else
  \State $y \gets$ \Call{Successore}{$u$} \Comment{2 figli: rimuovi il successore}
\EndIf
\State \Comment{$y$ è il nodo da rimuovere fisicamente (ha al più 1 figlio)}
\If{$y.sx \neq null$}
  \State $x \gets y.sx$
\Else
  \State $x \gets y.dx$
\EndIf
\If{$x \neq null$}
  \State $x.padre \gets y.padre$
\EndIf
\If{$y.padre = null$}
  \State $T.radice \gets x$
\ElsIf{$y = y.padre.sx$}
  \State $y.padre.sx \gets x$
\Else
  \State $y.padre.dx \gets x$
\EndIf
\If{$y \neq u$}
  \State copia $elem$ e $chiave$ di $y$ in $u$ \Comment{caso 3: copia il contenuto}
\EndIf
\end{algorithmic}
\end{algorithm}
```
### AggiornaAltezza (AVL)
Ricalcola altezza e fattore di bilanciamento $\beta(v) = h_{sx} - h_{dx}$ di un nodo; $O(1)$.
```pseudo
\begin{algorithm}
\caption{AggiornaAltezza($v$) — aggiorna altezza e fattore di bilanciamento di $v$}
\begin{algorithmic}
\State $h_{sx} \gets altezza(v.sx)$ \Comment{$-1$ se $v.sx = null$}
\State $h_{dx} \gets altezza(v.dx)$ \Comment{$-1$ se $v.dx = null$}
\State $v.altezza \gets 1 + \max(h_{sx}, h_{dx})$
\State $\beta(v) \gets h_{sx} - h_{dx}$
\end{algorithmic}
\end{algorithm}
```
### RuotaDestra (AVL)
Rotazione semplice a destra attorno al nodo critico $v$ (caso SS); $O(1)$. *(Implementazione standard di riferimento.)*
```pseudo
\begin{algorithm}
\caption{RuotaDestra($T, v$) — $v.sx$ sale, $v$ scende a destra}
\begin{algorithmic}
\State $u \gets v.sx$
\State $v.sx \gets u.dx$
\If{$u.dx \neq null$}
  \State $u.dx.padre \gets v$
\EndIf
\State $u.padre \gets v.padre$
\If{$v.padre = null$}
  \State $T.radice \gets u$
\ElsIf{$v = v.padre.sx$}
  \State $v.padre.sx \gets u$
\Else
  \State $v.padre.dx \gets u$
\EndIf
\State $u.dx \gets v$; $v.padre \gets u$
\State \Call{AggiornaAltezza}{$v$}; \Call{AggiornaAltezza}{$u$}
\end{algorithmic}
\end{algorithm}
```
### RuotaSinistra (AVL)
Simmetrica a `RuotaDestra` (caso DD): $v.dx$ sale, $v$ scende a sinistra; $O(1)$.
```pseudo
\begin{algorithm}
\caption{RuotaSinistra($T, v$) — $v.dx$ sale, $v$ scende a sinistra}
\begin{algorithmic}
\State $u \gets v.dx$
\State $v.dx \gets u.sx$
\If{$u.sx \neq null$}
  \State $u.sx.padre \gets v$
\EndIf
\State $u.padre \gets v.padre$
\If{$v.padre = null$}
  \State $T.radice \gets u$
\ElsIf{$v = v.padre.sx$}
  \State $v.padre.sx \gets u$
\Else
  \State $v.padre.dx \gets u$
\EndIf
\State $u.sx \gets v$; $v.padre \gets u$
\State \Call{AggiornaAltezza}{$v$}; \Call{AggiornaAltezza}{$u$}
\end{algorithmic}
\end{algorithm}
```
### Insert (AVL)
Inserimento BST seguito da ribilanciamento sul nodo critico più profondo; $O(\log n)$. I quattro casi SS/DD/SD/DS si risolvono con una rotazione semplice (SS→destra, DD→sinistra) o doppia (SD→sinistra+destra, DS→destra+sinistra).
```pseudo
\begin{algorithm}
\caption{Insert($T, e, k$) — inserimento AVL con ribilanciamento}
\begin{algorithmic}
\State crea un nuovo nodo $u$ con $elem = e$, $chiave = k$
\State inserisci $u$ come in un BST
\State ricalcola i fattori di bilanciamento nel cammino da $u$ alla radice
\State sia $v$ il nodo critico più profondo (il primo con $|\beta(v)| = 2$)
\If{$v$ esiste}
  \State determina il caso (SS / DD / SD / DS)
  \State esegui la rotazione opportuna su $v$
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Delete (AVL)
Cancellazione BST seguita da ribilanciamento risalendo verso la radice (lo sbilanciamento può propagarsi); $O(\log n)$.
```pseudo
\begin{algorithm}
\caption{Delete($T, e$) — cancellazione da AVL con ribilanciamento}
\begin{algorithmic}
\State cancella il nodo contenente $e$ come in un BST (3 casi)
\State $curr \gets$ padre del nodo eliminato fisicamente
\While{$curr \neq null$}
  \State ricalcola $\beta(curr)$
  \If{$|\beta(curr)| = 2$}
    \State determina il caso e applica la rotazione opportuna su $curr$
    \If{altezza del sottoalbero di $curr$ uguale a prima della cancellazione}
      \State \textbf{break} \Comment{sbilanciamento non si propaga, termina}
    \EndIf
  \EndIf
  \State $curr \gets curr.padre$
\EndWhile
\end{algorithmic}
\end{algorithm}
```
## Grafi: visite
Visite di un grafo $G=(V,E)$ con $n=|V|$, $m=|E|$; con liste di adiacenza costano $O(n+m)$. → [[08 - Grafi e Visite]]
### visitaBFS
Visita in ampiezza da $s$: calcola distanze in numero di archi e l'albero BFS; $O(n+m)$.
```pseudo
\begin{algorithm}
\caption{visitaBFS($s$) — visita BFS da sorgente $s$, restituisce l'albero $T$}
\begin{algorithmic}
\State rendi tutti i nodi non marcati
\State sia $T$ un albero con unico nodo $s$
\State sia $F$ una coda vuota
\State marca il vertice $s$, poni $\mathrm{dist}(s) \gets 0$
\State \Call{F.enqueue}{$s$}
\While{$F$ non è vuota}
  \State $u \gets$ \Call{F.dequeue}{}
  \ForAll{arco $(u, v) \in G$}
    \If{$v$ non è marcato}
      \State marca $v$
      \State $\mathrm{dist}(v) \gets \mathrm{dist}(u) + 1$
      \State rendi $u$ padre di $v$ in $T$
      \State \Call{F.enqueue}{$v$}
    \EndIf
  \EndFor
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```
### visitaDFSRicorsiva
Passo ricorsivo della DFS: marca, visita, ricorre sui vicini non marcati.
```pseudo
\begin{algorithm}
\caption{visitaDFSRicorsiva($v$, $T$) — visita DFS ricorsiva da $v$, estende $T$}
\begin{algorithmic}
\State marca e visita il vertice $v$
\ForAll{arco $(v, w) \in G$}
  \If{$w$ non è marcato}
    \State aggiungi l'arco $(v, w)$ all'albero $T$
    \State \Call{visitaDFSRicorsiva}{$w, T$}
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```
### visitaDFS (da sorgente)
Inizializza e lancia la DFS ricorsiva da una sorgente $s$.
```pseudo
\begin{algorithm}
\caption{visitaDFS($s$) — DFS da sorgente $s$, restituisce l'albero $T$}
\begin{algorithmic}
\State $T \gets$ albero vuoto
\State rendi tutti i nodi non marcati
\State \Call{visitaDFSRicorsiva}{$s, T$}
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```
### visitaDFS (completa, foresta)
Itera su tutti i nodi per coprire anche le componenti non raggiungibili; restituisce la foresta DFS.
```pseudo
\begin{algorithm}
\caption{visitaDFS($G$) — DFS completa su $G$, restituisce la foresta $F$}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State imposta $v$ come non marcato
\EndFor
\State $F \gets$ foresta vuota
\ForAll{nodo $v \in V$}
  \If{$v$ non è marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $F$
  \EndIf
\EndFor
\State \Return $F$
\end{algorithmic}
\end{algorithm}
```
### visitaDFSIterativa
DFS con pila esplicita; si marca alla `pop` (un nodo può entrare più volte nella pila).
```pseudo
\begin{algorithm}
\caption{visitaDFSIterativa($s$) — DFS iterativa con pila esplicita, restituisce $T$}
\begin{algorithmic}
\State rendi tutti i nodi non marcati
\State $T \gets$ albero con unico nodo $s$
\State sia $P$ una pila vuota
\State \Call{P.push}{$s$}
\While{$P$ non è vuota}
  \State $u \gets$ \Call{P.top}{}; \Call{P.pop}{}
  \If{$u$ non è marcato}
    \State marca $u$
    \ForAll{arco $(u, v) \in G$}
      \If{$v$ non è marcato}
        \State rendi $u$ padre di $v$ in $T$
        \State \Call{P.push}{$v$}
      \EndIf
    \EndFor
  \EndIf
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```
## Applicazioni della DFS
Tempi pre/post, ordinamento topologico e componenti fortemente connesse; tutto $O(n+m)$. → [[09 - Applicazioni della DFS]]
### visitaDFSRicorsiva (con clock)
DFS arricchita con i tempi di scoperta `pre(v)` e di fine `post(v)`.
```pseudo
\begin{algorithm}
\caption{visitaDFSRicorsiva($v$, $T$) — arricchita con clock}
\begin{algorithmic}
\State marca $v$
\State $\text{pre}(v) \gets \text{clock}$; $\text{clock} \gets \text{clock} + 1$
\ForAll{arco $(v, w) \in G$}
  \If{$w$ non è marcato}
    \State aggiungi $(v, w)$ a $T$
    \State \Call{visitaDFSRicorsiva}{$w, T$}
  \EndIf
\EndFor
\State $\text{post}(v) \gets \text{clock}$; $\text{clock} \gets \text{clock} + 1$
\end{algorithmic}
\end{algorithm}
```
### VisitaDFS (con clock, foresta)
Versione completa che inizializza il `clock` e copre tutti i nodi.
```pseudo
\begin{algorithm}
\caption{VisitaDFS($G$) — gestisce nodi non raggiungibili}
\begin{algorithmic}
\ForAll{nodo $v \in G$}
  \State imposta $v$ come non marcato
\EndFor
\State $\text{clock} \gets 1$
\State $F \gets$ foresta vuota
\ForAll{nodo $v \in G$}
  \If{$v$ è non marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $F$
  \EndIf
\EndFor
\State \Return $F$
\end{algorithmic}
\end{algorithm}
```
### OrdinamentoTopologico
Ordina un DAG per `post(v)` decrescente; $O(n+m)$.
```pseudo
\begin{algorithm}
\caption{OrdinamentoTopologico($G$)}
\begin{algorithmic}
\State $\text{top} \gets n$; $L \gets$ lista vuota
\State esegui \Call{VisitaDFS}{$G$}, ma al momento di impostare $\text{post}(v)$:
\State \hspace{1em} $\sigma(v) \gets \text{top}$
\State \hspace{1em} $\text{top} \gets \text{top} - 1$
\State \hspace{1em} aggiungi $v$ in testa alla lista $L$
\State \Return $L$ e $\sigma$
\end{algorithmic}
\end{algorithm}
```
### ComponentiFortementeConnesse (Kosaraju)
Due DFS: una su $G^R$ per ordinare i nodi per `post` decrescente, una su $G$ per estrarre le SCC; $O(n+m)$.
```pseudo
\begin{algorithm}
\caption{ComponentiFortementeConnesse($G$)}
\begin{algorithmic}
\State calcola $G^R$ \Comment{grafo con archi invertiti}
\State \Call{VisitaDFS}{$G^R$} \Comment{calcola i valori $\text{post}(v)$ in $G^R$}
\State \Return \Call{CompConnesse}{$G$}
\end{algorithmic}
\end{algorithm}
```
### CompConnesse
Visita i nodi in ordine di `post` decrescente (calcolato su $G^R$) ed estrae un albero per SCC.
```pseudo
\begin{algorithm}
\caption{CompConnesse($G$)}
\begin{algorithmic}
\ForAll{nodo $v \in G$}
  \State imposta $v$ come non marcato
\EndFor
\State $\text{Comp} \gets$ insieme vuoto
\ForAll{nodo $v$ in ordine decrescente di $\text{post}(v)$ calcolato su $G^R$}
  \If{$v$ è non marcato}
    \State $T \gets$ albero vuoto
    \State \Call{visitaDFSRicorsiva}{$v, T$}
    \State aggiungi $T$ a $\text{Comp}$
  \EndIf
\EndFor
\State \Return $\text{Comp}$
\end{algorithmic}
\end{algorithm}
```
## Cammini minimi
Cammini minimi da sorgente singola con pesi **non negativi**. → [[10 - Cammini Minimi e Dijkstra]]
### Dijkstra
Espande il nodo più vicino non ancora definitivo usando una coda con priorità; $O(m\log n)$ con heap.
```pseudo
\begin{algorithm}
\caption{Dijkstra($G, s$) — albero dei cammini minimi da $s$}
\begin{algorithmic}
\ForAll{$v \in G$}
  \State $v.dist \gets +\infty$
\EndFor
\State $s.dist \gets 0$
\State $T \gets$ albero con radice $s$ (senza archi)
\State $X \gets \emptyset$
\State $CP \gets$ nuova CodaConPriorità
\State \Call{CP.insert}{$s, 0$}
\While{non \Call{CP.isEmpty}{}}
  \State $u \gets$ \Call{CP.deleteMin}{}
  \State $X \gets X \cup \{u\}$
  \ForAll{arco $(u,v) \in G$}
    \If{$v.dist = +\infty$}
      \State $v.dist \gets u.dist + w(u, v)$
      \State \Call{CP.insert}{$v, v.dist$}
      \State rendi $u$ padre di $v$ in $T$
    \ElsIf{$u.dist + w(u,v) < v.dist$}
      \State \Call{CP.decreaseKey}{$v, u.dist + w(u,v)$}
      \State $v.dist \gets u.dist + w(u, v)$
      \State rendi $u$ nuovo padre di $v$ in $T$
    \EndIf
  \EndFor
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```
## Riepilogo complessità
Tabellone di riferimento ($n$ = elementi/nodi, $m$ = archi, $k$ = ampiezza del dominio delle chiavi, $h$ = altezza dell'albero).
| Algoritmo | Tempo | Note |
|---|---|---|
| Fibonacci ricorsivo | $O(\phi^n)$ | esponenziale |
| Fibonacci DP / iterativo | $\Theta(n)$ | spazio $\Theta(1)$ nella v. iterativa |
| Fibonacci potenza di matrice | $O(\log n)$ | con esponenziazione veloce |
| RicercaSequenziale | $O(n)$ | vettore non ordinato |
| RicercaBinaria | $O(\log n)$ | vettore ordinato |
| SelectionSort | $\Theta(n^2)$ | in loco, non stabile |
| InsertionSort | $O(n^2)$, $\Omega(n)$ | in loco, stabile, ottimo se quasi ordinato |
| BubbleSort | $O(n^2)$ | in loco, stabile |
| MergeSort | $\Theta(n\log n)$ | stabile, non in loco |
| QuickSort | $\Theta(n\log n)$ medio, $O(n^2)$ peggiore | in loco, non stabile |
| HeapSort | $O(n\log n)$ | in loco, non stabile |
| IntegerSort / Counting | $O(n+k)$ | stabile; lineare se $k=O(n)$ |
| BucketSort | $O(n+k)$ | stabile |
| Pila / Coda (push, pop, enqueue, dequeue) | $O(1)$ | array (circolare per la coda) |
| Visite di alberi (DFS, BFS, altezza, foglie, …) | $\Theta(n)$ | |
| Heap: insert, delete, decreaseKey, increaseKey | $O(\log n)$ | |
| Heap: findMin | $O(1)$ | |
| Heap: Heapify (costruzione) | $O(n)$ | non $O(n\log n)$ |
| BST: search, insert, delete, min, successore | $O(h)$ | $O(n)$ nel caso peggiore |
| AVL: tutte le operazioni | $O(\log n)$ | altezza garantita $O(\log n)$ |
| BFS / DFS su grafo | $O(n+m)$ | liste di adiacenza |
| Ordinamento topologico | $O(n+m)$ | solo su DAG |
| Componenti fortemente connesse (Kosaraju) | $O(n+m)$ | due DFS |
| Dijkstra | $O(m\log n)$ | heap binario; pesi non negativi |
## Trappole ricorrenti
Errori che costano punti all'esame.

> [!warning] Casi peggiori e pre-condizioni
> - **RicercaBinaria**: richiede il vettore **ordinato**; su uno non ordinato non vale $O(\log n)$.
> - **QuickSort**: $O(n^2)$ se il perno è sempre il minimo/massimo (es. array già ordinato con perno $A[i]$).
> - **IntegerSort/Counting/Bucket**: lineari solo se $k = O(n)$; non sono ordinamenti per confronti, quindi aggirano il lower bound $\Omega(n\log n)$.
> - **BST non bilanciato**: le operazioni sono $O(h)$, che degenera a $O(n)$; l'AVL garantisce $h = O(\log n)$.
> - **Dijkstra**: corretto **solo con pesi non negativi**; con pesi negativi serve Bellman-Ford (Modulo II).
