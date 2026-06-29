---
tags:
  - algoritmi
  - strutture-dati
  - grafi
---
# Pseudocodici e Interfacce — Modulo I
**Prontuario operativo** per gli esercizi di progettazione (**Es 2**) e modellazione (**Es 3**) del Modulo I (corso del prof. Gualà): come **richiamare** le routine note senza riscriverle ([[#Interfacce: come usare le scatole nere]]), tutti gli **pseudocodici** di riferimento, e i **pattern** ricorrenti di Es 2 ed Es 3. Per teoria asintotica, ricorrenze e tabella decisionale dell'Es 1 → [[Formulario]].
## Come usarlo
1. **Interfacce** — cosa restituisce ogni algoritmo standard (`dist`, `pre`/`post`, vettore dei padri…), quanto costa, quando richiamarlo con `\Call`. È la parte che trasforma "so cosa fa l'algoritmo" in "so usarlo dentro un altro algoritmo".
2. **Pseudocodici** — le implementazioni complete, da consultare solo se devi *modificare* una routine, non per ricopiarla.
3. **Pattern Es 2 / Es 3** — gli schemi risolutivi: riconosci il pattern, istanzia lo scheletro.
## Convenzioni di lettura
Array **1-based**; $A[i;f]$ è il sottovettore dagli indici $i$ a $f$; $\gets$ è l'assegnazione; `null` il puntatore nullo; $\lfloor\cdot\rfloor$ la parte intera inferiore. Nelle complessità: $n$ = numero di elementi o nodi, $m=|E|$ = archi di un grafo, $h$ = altezza di un albero, $k$ = ampiezza del dominio delle chiavi. Le keyword strutturali (`for`/`while`/`if`…) sono in inglese (sintassi pseudocode.js stile LaTeX `algorithmic`); i connettori (`e`, `o`, `scambia … con …`) restano in italiano come testo. Il nome e la firma di ogni procedura stanno nel `\caption`.
## Interfacce: come usare le scatole nere
La difficoltà tipica dell'Es 2/3 non è conoscere DFS, BFS, Dijkstra o Heapify: è **usarli come mattoni** dentro la soluzione di un problema nuovo. Questa sezione ti dà esattamente questo — cosa entra, cosa esce, quanto costa — così scrivi solo la *logica nuova* e il resto lo richiami.
### Il principio: richiamare, non riscrivere
> [!info] Le routine note si invocano con `\Call`, non si riscrivono
> In un Es 2/3 le procedure standard (DFS, BFS, Dijkstra, Heapify, ordinamenti, Componenti Fortemente Connesse, operazioni su BST/AVL e heap…) sono **scatole nere**: le richiami con `\Call{Nome}{argomenti}` dando per noti comportamento e costo. Scrivi per esteso **solo** la parte di logica che il problema aggiunge. Mai `\Call` in prosa: vive solo dentro un blocco ` ```pseudo `.
```pseudo
\begin{algorithm}
\caption{EsempioUso($G$, $s$, $t$) — distanza minima $s \to t$ su grafo non pesato}
\begin{algorithmic}
\State $(dist, padre) \gets$ \Call{visitaBFS}{$G, s$} \Comment{scatola nera: $O(n+m)$}
\State \Return $dist[t]$ \Comment{la logica nuova è solo leggere il risultato}
\end{algorithmic}
\end{algorithm}
```
### Gli "output" che devi saper leggere
Tre vettori compaiono in quasi ogni problema su grafi/alberi. Sapere **cosa contengono** è ciò che ti permette di concatenare gli algoritmi.
> [!info] `dist[]` — vettore delle distanze
> `dist[v]` = costo del cammino minimo dalla **sorgente** a $v$. Lo producono:
> - **BFS** su grafo non pesato → `dist[v]` = numero di **archi** del cammino più corto $s \to v$;
> - **Dijkstra** su grafo con pesi $\ge 0$ → `dist[v]` = **somma dei pesi** del cammino minimo $s \to v$.
> Convenzione: si inizializza `dist[v]` $\gets +\infty$ per ogni $v$, poi `dist[s]` $\gets 0$; un `dist[v]` rimasto $+\infty$ significa "$v$ non raggiungibile da $s$". Per il cammino vero e proprio (non solo il costo) risali il vettore dei padri.

> [!info] `pre[]` e `post[]` — i tempi della DFS
> Con un *clock* globale incrementato a ogni evento, la DFS marca per ogni nodo $v$:
> - `pre[v]` = istante di **scoperta** (quando $v$ diventa grigio);
> - `post[v]` = istante di **fine** (quando $v$ diventa nero, finiti tutti i discendenti).
>
> A cosa servono: **classificare gli archi** (albero / avanti / indietro / attraversamento), **rilevare cicli** (in un orientato c'è un ciclo $\iff$ esiste un arco all'indietro), **ordinamento topologico** (ordine di `post` decrescente), **Componenti Fortemente Connesse**. Regola d'oro (annidamento): gli intervalli $[\,pre[v],\,post[v]\,]$ sono **disgiunti o annidati**, mai parzialmente sovrapposti; e $u$ è antenato di $v$ $\iff pre[u] < pre[v] < post[v] < post[u]$. → [[09 - Applicazioni della DFS]]

> [!info] `padre[]` (vettore dei padri) — l'albero della visita
> `padre[v]` = nodo da cui $v$ è stato **scoperto** durante la visita (`padre[s]` $=$ `null`). Risalendo `padre[]` da un nodo $t$ fino alla sorgente e invertendo, **ricostruisci il cammino** $s \to t$ (è il cammino *minimo* se il vettore viene da BFS o Dijkstra). È il modo standard per passare da "quanto costa" a "qual è il percorso".
### Catalogo delle scatole nere
Per ogni routine: firma, cosa restituisce, costo, quando usarla; implementazione completa al link.

**Grafi — visite e cammini**
- `visitaBFS(G, s)` → `dist[]` (in archi) + `padre[]`, $O(n+m)$ — distanze/raggiungibilità su grafo **non pesato**, visita per livelli. → [[#Grafi: visite]]
- `visitaDFS(G)` → `pre[]`, `post[]`, `padre[]`, $O(n+m)$ — tempi, cicli, classificazione degli archi. → [[#Applicazioni della DFS]]
- `OrdinamentoTopologico(G)` → lista di nodi ordinata, $O(n+m)$ — ordinare per dipendenze, verificare se è un DAG. → [[#Applicazioni della DFS]]
- `ComponentiFortementeConnesse(G)` → componente per ogni nodo, $O(n+m)$ — forte connettività, condensazione in DAG. → [[#Applicazioni della DFS]]
- `Dijkstra(G, s)` → `dist[]` (pesata) + `padre[]`, $O(m\log n)$ — cammini minimi con **pesi $\ge 0$**. → [[#Cammini minimi]]

**Heap e code con priorità**
- `Heapify(A)` → max-heap in loco, $O(n)$ — costruire un heap da $n$ elementi. → [[#Heap e code con priorità]]
- `insert` / `findMin` / `delete` → heap aggiornato / minimo, $O(\log n)$ — coda con priorità (inserisci/estrai). → [[#Heap e code con priorità]]

**Ordinamento**
- `MergeSort(A, 1, n)` → array ordinato, $O(n\log n)$ — ordinamento per confronti garantito. → [[#Ordinamento]]
- `IntegerSort(X, k)` → array ordinato, $O(n+k)$ — **lineare** se $k=O(n)$ (chiavi intere in $[1,k]$). → [[#Ordinamento]]

**Dizionario — BST / AVL**
- `Search` / `Min` / `Max` / `Successore` / `Predecessore` / `Insert` / `Delete` → nodo / albero aggiornato, $O(h)$ (AVL $O(\log n)$) — dizionario ordinato, navigazione locale. → [[#BST e AVL]]

> [!warning] Trappola — `dist` non è una cosa sola
> `dist` da **BFS** conta *archi* (grafo non pesato); `dist` da **Dijkstra** somma *pesi*. Se il problema ha pesi, BFS dà la risposta sbagliata; se non ha pesi (o pesi tutti uguali), Dijkstra funziona ma è sovradimensionato ($O(m\log n)$ invece di $O(n+m)$).
### Dall'idea allo pseudocodice — i 5 passi
Quando "sai cosa fare" ma non sai scriverlo, applica sempre questo schema:
> [!info] Metodo dei 5 passi
> 1. **Dichiara** input, output e il **bound** richiesto. Il bound suggerisce già la tecnica: $O(n)$ → scansione / prefix sum; $O(n\log n)$ → sort, heap o AVL; $O(n+m)$ → visita su grafo; $O(m\log n)$ → Dijkstra.
> 2. **Scegli la struttura dati** che rende possibile quel bound (è qui che "scegli tu l'AVL" se ti serve $O(\log n)$ per operazione).
> 3. **Spezza** il problema in *subroutine nota* (→ `\Call`) e *logica nuova* (→ la scrivi tu).
> 4. **Scrivi solo la logica nuova**; tutto il resto è una chiamata.
> 5. **Somma i costi** e verifica che rispettino il bound.

> [!info] Es 3 = riconoscere il pattern, non inventare
> L'Es 3 non chiede di inventare un algoritmo complesso: chiede di **riconoscere** a quale dei pochi pattern ricorrenti appartiene il problema e di **modellare** (decidere cosa sono i nodi/gli stati). Deciso il modello — es. *nodo = (posizione, informazione discreta)* — il codice è quasi scritto: costruisci il grafo espanso, `\Call` BFS/Dijkstra, leggi `dist`. Gli scheletri sono in [[#Esercizio 3 — pattern di modellazione]].
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
### Lower bound e confronto degli ordinamenti
> [!quote] Teorema — Lower Bound $\Omega(n \log n)$ per confronti
> Ogni **algoritmo di ordinamento basato su confronti** richiede $\Omega(n \log n)$ confronti nel caso peggiore.
>
> **Dimostrazione (albero di decisione):** l'**albero di decisione** di un algoritmo corretto su $n$ elementi è un albero binario in cui ogni nodo interno modella un confronto e ogni foglia un possibile output (una permutazione). Un algoritmo corretto deve produrre un output distinto per ognuna delle $n!$ permutazioni, quindi l'albero ha almeno $n!$ **foglie** e altezza
> $$h \ge \log_2(n!) \ge \log_2\!\left(\frac{n}{e}\right)^{\!n} = n \log_2 n - n \log_2 e = \Omega(n \log n)$$
> (formula di **Stirling**: $n! \ge (n/e)^n$). Il caso peggiore coincide con il cammino radice–foglia più lungo, di lunghezza $h$. → [[04 - Algoritmi di Ordinamento#Lower bound per confronti: l'albero di decisione]]
>
> **Algoritmi lineari:** IntegerSort (Counting Sort), BucketSort e RadixSort **non confrontano chiavi tra loro** — usano i valori come indici in array o bucket. La prova dell'albero di decisione presuppone che i dati siano accessibili *solo tramite confronti*: fuori da questa classe il bound non vale, e si può raggiungere $O(n+k)$ o $O\!\left(n \cdot \dfrac{\log k}{\log n}\right)$ (RadixSort con $b=\Theta(n)$) sfruttando il dominio finito delle chiavi.

| Algoritmo | Tempo medio / peggiore | In loco | Stabile | Quando si usa |
| --- | --- | --- | --- | --- |
| SelectionSort | $\Theta(n^2)$ | Sì | No | Solo didattica |
| InsertionSort | $\Theta(n^2)$ | Sì | Sì | Array quasi ordinati o $n$ piccolo (migliore: $\Theta(n)$) |
| BubbleSort | $\Theta(n^2)$ | Sì | Sì | Solo didattica |
| MergeSort | $\Theta(n \log n)$ | No | Sì | Garanzia $\Theta(n \log n)$ + stabilità; ordinamento esterno |
| QuickSort | medio $\Theta(n \log n)$ / peggiore $O(n^2)$ | Sì | No | Uso generale; randomizzare per evitare il caso peggiore |
| HeapSort | $\Theta(n \log n)$ | Sì | No | Garanzia $\Theta(n \log n)$ nel peggiore, in loco |
| IntegerSort / Counting | $\Theta(n+k)$ | No | No | Chiavi intere in $[1,k]$, $k=O(n)$, senza dati satellite |
| RadixSort | $\Theta\!\left((n+b)\dfrac{\log k}{\log b}\right)$ | No | Sì | Chiavi intere $[1,k]$ con $k=O(n^c)$; con o senza satellite |
| BucketSort | $\Theta(n+k)$ | No | Sì | Record con chiave intera in $[1,k]$, $k=O(n)$; subroutine stabile di RadixSort |

> [!question] Domanda tipica d'esame
> **D:** Il lower bound $\Omega(n \log n)$ implica che non si può ordinare in $O(n)$?
>
> **R:** No. Il lower bound vale **solo per gli algoritmi basati su confronti**. IntegerSort, BucketSort e RadixSort non confrontano chiavi tra loro ma usano i valori come indici, uscendo dalla classe a cui si applica la dimostrazione. Con $k=O(n)$ ordinano in $O(n)$; RadixSort con $k=O(n^c)$ raggiunge $O\!\left(n \cdot \dfrac{\log k}{\log n}\right)$.
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
## Dizionario: interfaccia e realizzazioni
Il **Dizionario** è il tipo di dato astratto che mantiene un insieme $S$ di coppie (elem, chiave) e supporta operazioni di ricerca, inserimento e cancellazione. La scelta della realizzazione determina il costo computazionale; le implementazioni elementari sono in [[05 - Strutture Dati Elementari e Dizionari]], le strutture ad albero in [[06 - Alberi di Ricerca BST e AVL]].
### Interfaccia
> [!quote] Definizione — Dizionario
> Il tipo di dato **Dizionario** mantiene un insieme $S$ di coppie (elem, chiave) e supporta:
> - `insert(elem e, chiave k)` — aggiunge a $S$ la coppia $(e, k)$.
> - `search(chiave k)` — restituisce l'elemento con chiave $k$ se presente in $S$, altrimenti `null`.
> - `delete(chiave k)` — cancella da $S$ l'elemento con chiave $k$.
### Realizzazioni a confronto
Complessità nel **caso peggiore**; $n$ = elementi in $S$, $h$ = altezza dell'albero.

| Realizzazione | Ricerca | Inserimento | Cancellazione | Note |
| :--- | :---: | :---: | :---: | :--- |
| Array non ordinato | $O(n)$ | $O(1)$ | $O(n)$ | inserimento in coda; delete = search + rimozione |
| Array ordinato | $O(\log n)$ | $O(n)$ | $O(n)$ | ricerca binaria; inserimento mantiene ordine ($O(n)$ spostamenti) |
| Lista non ordinata | $O(n)$ | $O(1)$ | $O(n)$ | inserimento in testa |
| Lista ordinata | $O(n)$ | $O(n)$ | $O(n)$ | nessun accesso diretto: ricerca binaria inapplicabile |
| BST | $O(h)$ | $O(h)$ | $O(h)$ | $h = \Theta(\log n)$ bilanciato, $h = \Theta(n)$ degenere |
| AVL | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $h = O(\log n)$ garantito; ribilanciamento con rotazioni |

> [!warning] Lista ordinata non migliora la ricerca
> Ordinare una lista non porta vantaggi su `search`: senza accesso diretto non è applicabile la ricerca binaria. Si paga $O(n)$ su `insert` e `delete` senza guadagnare sulla ricerca. → [[05 - Strutture Dati Elementari e Dizionari#Lista ordinata]]

> [!warning] BST degenera a $O(n)$ senza bilanciamento
> Le operazioni BST costano $O(h)$: inserendo chiavi in ordine crescente $h = \Theta(n)$ e il dizionario degrada a prestazioni di lista. L'AVL risolve garantendo $h = O(\log n)$ sempre. → [[06 - Alberi di Ricerca BST e AVL#Analisi del costo]]

> [!info] Operazioni aggiuntive su BST/AVL
> Il BST — e quindi l'AVL — supporta anche `min`, `max`, `successore` e `predecessore` in $O(h)$ (AVL: $O(\log n)$). I pseudocodici di tutte le operazioni (incluse rotazioni e casi SS/DD/SD/DS) sono nel [[#BST e AVL]].

> [!info] Hash table — fuori programma
> Le tabelle hash **non fanno parte del programma** del prof. Gualà e non compaiono nelle slide o nelle note del corso.
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

> [!info] Heap a colpo d'occhio
> **Proprietà di heap.** In un **max-heap** la chiave di ogni nodo padre è $\ge$ quella dei figli; in un **min-heap** è $\le$. La radice contiene sempre l'elemento con chiave massima (o minima).
>
> **Layout su array 1-based (heap binario, $d = 2$).** I figli del nodo $i$ stanno alle posizioni $2i$ e $2i+1$; il padre di $i$ sta in $\lfloor i/2\rfloor$. La struttura è un **albero binario quasi completo** (completo fino al penultimo livello, foglie dell'ultimo livello compattate a sinistra) di altezza $\Theta(\log n)$.
>
> **Costi del 2-heap (caso peggiore).**
>
> | Operazione | Costo |
> |:---|:---:|
> | findMin / findMax | $O(1)$ |
> | insert | $O(\log n)$ |
> | delete / deleteMin | $O(\log n)$ |
> | decreaseKey / increaseKey | $O(\log n)$ |
> | **Heapify** (costruzione bottom-up) | $O(n)$ — **non** $O(n \log n)$ |
>
> **Varianti.**
> - **Heap $d$-ario**: albero $d$-ario quasi completo di altezza $\Theta(\log_d n)$. Aumentare $d$ velocizza le operazioni di salita (`insert`, `decreaseKey`) ma rallenta quelle di discesa (`deleteMin`, `increaseKey`), che confrontano $d$ figli per livello.
> - **Heap binomiale**: foresta di alberi binomiali con al più $\lfloor \log_2 n \rfloor + 1$ alberi; garantisce **merge in $O(\log n)$** (nei d-heap il merge costa $\Omega(n)$); costruzione tramite $n$ inserimenti $O(n)$ ammortizzato per l'analogia con la somma binaria.
> - **Heap di Fibonacci** (Fredman-Tarjan 1987): struttura "pigra" con forma degli alberi rilassata; `decreaseKey` in $O(1)$ **ammortizzato** — cruciale per Dijkstra su grafi densi ($O(n \log n + m)$ invece di $O(m \log n)$); `insert` e `merge` $O(1)$ ammortizzato; `deleteMin` $O(\log n)$ ammortizzato.
>
> Riferimento: [[07 - Code con Priorità e Heap]]
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

> [!info] Proprietà BST
> **Proprietà d'ordine** (convenzione prof. Gualà, [[06 - Alberi di Ricerca BST e AVL#Alberi Binari di Ricerca (BST)]]): ogni nodo $v$ ha chiavi $\leq \text{chiave}(v)$ nel sottoalbero sinistro e chiavi $> \text{chiave}(v)$ nel sottoalbero destro; le chiavi uguali vanno **a sinistra**.
> La **visita in ordine simmetrico** (sinistra → radice → destra) restituisce le chiavi in ordine crescente.
> Tutte le operazioni (search, insert, delete, min, successore) costano $O(h)$, dove $h$ è l'altezza: $h = \Theta(\log n)$ nell'albero **bilanciato**, $h = \Theta(n)$ nell'albero **degenere** (lista — caso degli inserimenti già ordinati).

> [!info] Bilanciamento AVL
> Il **fattore di bilanciamento** di un nodo $v$ è $\beta(v) = h_{sx} - h_{dx}$ (con $h(\text{vuoto}) = -1$). Un **albero AVL** è un BST in cui $\beta(v) \in \{-1, 0, +1\}$ per ogni nodo; ciò garantisce $h = O(\log n)$ (dimostrazione via alberi di Fibonacci, [[06 - Alberi di Ricerca BST e AVL#Teorema sull'altezza degli AVL]]).
> Dopo insert/delete si ribilancia sul **nodo critico** $v$ (profondità massima con $|\beta(v)| = 2$) con una delle 4 rotazioni:
>
> | Caso | $\beta(v)$ | Causa | Rotazione |
> |:--|:-:|:--|:--|
> | **SS** | $+2$ | sottoalbero sx del figlio sx | semplice **destra** su $v$ |
> | **DD** | $-2$ | sottoalbero dx del figlio dx | semplice **sinistra** su $v$ |
> | **SD** | $+2$ | sottoalbero dx del figlio sx | doppia: **sinistra** su figlio, **destra** su $v$ |
> | **DS** | $-2$ | sottoalbero sx del figlio dx | doppia: **destra** su figlio, **sinistra** su $v$ |
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
## Grafi: rappresentazioni e costi
Riferimento: [[08 - Grafi e Visite]]. Un **grafo** $G=(V,E)$ ha $n=|V|$ **vertici** e $m=|E|$ **archi**; nei **grafi orientati** gli archi sono coppie ordinate $(u,v)$, **uscenti** da $u$ ed **entranti** in $v$.
### Definizioni rapide
> [!info] Glossario
> - **Grafo non orientato**: archi = coppie non ordinate $\{u,v\}$. **Grafo orientato**: archi = coppie ordinate $(u,v)$.
> - **Grado** $\delta(u)$ (non orientato): numero di archi incidenti a $u$. In un orientato: **grado uscente** $\delta_{out}(u)$ e **grado entrante** $\delta_{in}(u)$.
> - **Cammino** $v_0,v_1,\ldots,v_k$: ogni $(v_i,v_{i+1})\in E$; **lunghezza** $=k$ (numero di archi). In un orientato il verso degli archi deve essere rispettato.
> - **Ciclo**: cammino chiuso da un nodo a se stesso; grafo **aciclico** = senza cicli.
> - **Connesso** (non orientato): esiste un cammino tra ogni coppia di nodi. **Fortemente connesso** (orientato): per ogni coppia $(u,v)$ esiste un cammino orientato da $u$ a $v$ e uno da $v$ a $u$ → [[09 - Applicazioni della DFS]].
> - **DAG** *(Directed Acyclic Graph)*: grafo orientato privo di cicli; modella dipendenze tra compiti.
> - **Albero**: grafo connesso e aciclico, con $m=n-1$. **Foresta**: grafo aciclico (unione di alberi disgiunti).
### Relazioni utili
> [!quote] Proprietà — Handshake e limiti su $m$
> **Grafo non orientato** — lemma della stretta di mano:
> $$\sum_{v\in V}\delta(v)=2m$$
> Ogni arco $\{u,v\}$ contribuisce $+1$ al grado di entrambi i suoi estremi. Corollario: $m\le\binom{n}{2}=\frac{n(n-1)}{2}$ (al più un arco per coppia non ordinata).
> **Grafo orientato**: $\sum_{v\in V}\delta_{out}(v)=\sum_{v\in V}\delta_{in}(v)=m$ e $m\le n(n-1)$ (ogni coppia ordinata di nodi distinti può dare un arco).

> [!info] Sparso vs Denso
> - **Sparso**: $m\ll n^2$ — il caso tipico nelle applicazioni reali.
> - **Denso**: $m=\Theta(n^2)$ — vicino al grafo completo $K_n$ con $m=\frac{n(n-1)}{2}$.
> La densità orienta la scelta della rappresentazione in memoria.
### Confronto rappresentazioni
| Operazione | Liste di adiacenza | Matrice di adiacenza |
|---|---|---|
| **Spazio** | $O(n+m)$ | $O(n^2)$ |
| Test $(u,v)\in E$? (orientato) | $O(\delta_{out}(u))$ | $O(1)$ |
| Test $(u,v)\in E$? (non orientato) | $O(\min\{\delta(u),\delta(v)\})$ | $O(1)$ |
| Scorrere i vicini di $u$ | $O(\delta(u))$ | $O(n)$ |
| **Visita BFS / DFS** | $O(n+m)$ | $O(n^2)$ |

Con le **liste di adiacenza** BFS e DFS costano $O(n+m)$: ogni nodo viene estratto/marcato al più una volta ($O(n)$ totale); per ciascun nodo $u$ si scorrono i suoi $\delta(u)$ vicini, e la somma $\sum_{u}\delta(u)=2m$ (non orientato) o $m$ (orientato) dà il contributo $O(m)$ complessivo.

> [!info] Quale rappresentazione scegliere?
> - **Grafi sparsi** ($m\ll n^2$, il caso più comune): preferire le liste — spazio $O(n+m)$ vs $O(n^2)$, scansione vicini $O(\delta(u))$ vs $O(n)$.
> - **Grafi densi** ($m\approx n^2$): la matrice offre lookup $O(1)$ a costo di spazio comparabile alle liste.
> La maggior parte degli algoritmi (BFS, DFS, Dijkstra) è progettata su liste di adiacenza.

> [!question] Domanda tipica d'esame
> **D:** Perché BFS e DFS costano $O(n+m)$ con liste di adiacenza e $O(n^2)$ con la matrice?
> **R:** Con le liste ogni arco viene esaminato esattamente una volta e ogni nodo entra nella struttura (coda/pila) al più una volta: costo totale $O(n)+O(m)=O(n+m)$. Con la matrice, per trovare i vicini di $u$ si scorre l'intera riga di $n$ celle, pagando $O(n)$ per nodo e $O(n^2)$ complessivamente, anche quando il grafo è sparso.
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
\State esegui \Call{VisitaDFS}{$G$}, ma al momento di impostare $\text{post}(v)$ esegui anche:
\State $\sigma(v) \gets \text{top}$
\State $\text{top} \gets \text{top} - 1$
\State aggiungi $v$ in testa alla lista $L$
\State \Return $L$ e $\sigma$
\end{algorithmic}
\end{algorithm}
```
### ComponentiFortementeConnesse
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
### Varianti ricorrenti dei cammini minimi
Scegliere l'algoritmo in base alla struttura dei pesi e ai vincoli di percorso; Dijkstra$(G,s)$ e visitaBFS già nel formulario ([[#Dijkstra]], [[#visitaBFS]]). → [[10 - Cammini Minimi e Dijkstra]]

> [!info] Variante 1 — Grafo non pesato → BFS, $O(n+m)$
> **Quando:** nessun peso sugli archi (o pesi tutti uguali). **Idea:** visitaBFS da $s$; le distanze calcolate sono in numero di archi. **Costo:** $O(n+m)$.

> [!info] Variante 2 — Pesi in $\{0,1\}$ → 0-1 BFS con deque, $O(n+m)$
> **Quando:** $w(u,v)\in\{0,1\}$ per ogni arco. **Idea:** **deque** (coda a doppia estremità) al posto dello heap; arco peso $0$ → nodo in **testa** (distanza invariata), arco peso $1$ → nodo in **coda**. L'invariante di distanza non decrescente nella deque garantisce la correttezza senza costo logaritmico. **Costo:** $O(n+m)$, contro $O(m\log n)$ di Dijkstra. → [[06 - BFS su grafo implicito e 0-1 BFS]]

```pseudo
\begin{algorithm}
\caption{ZeroOneBFS($G, s$) — cammini minimi con $w\in\{0,1\}$}
\begin{algorithmic}
\ForAll{$v \in G$}
  \State $v.dist \gets +\infty$
\EndFor
\State $s.dist \gets 0$
\State sia $D$ una deque; inserisci $s$ in testa a $D$
\While{$D \neq \emptyset$}
  \State $u \gets$ estrai dalla testa di $D$
  \ForAll{arco $(u,v) \in G$}
    \If{$u.dist + w(u,v) < v.dist$}
      \State $v.dist \gets u.dist + w(u,v)$
      \If{$w(u,v) = 0$}
        \State inserisci $v$ in testa a $D$
      \Else
        \State inserisci $v$ in coda a $D$
      \EndIf
    \EndIf
  \EndFor
\EndWhile
\end{algorithmic}
\end{algorithm}
```

> [!info] Variante 3 — Pesi interi $\le C$ → Dial (bucket queue), $O(m+nC)$
> **Quando:** $w(u,v)\in\{0,\ldots,C\}$ interi con $C$ piccolo (es. $C\ll\log n$). **Idea:** sostituire lo heap con $nC+1$ **bucket** (array di $nC+1$ posizioni indicizzato per distanza); il cursore avanza monotonicamente sui bucket senza tornare indietro. Costo: $O(m)$ per gli inserimenti + $O(nC)$ per la scansione totale del cursore fino alla distanza massima $nC$. **Costo totale:** $O(m+nC)$. *(extra, non da slide)*

> [!info] Variante 4 — Vincolo $\le k$ archi o stato discreto → grafo espanso/a livelli
> **Quando:** il percorso ha un vincolo non codificabile dal solo nodo corrente: numero di archi $\le k$, parità degli archi attraversati, colore dell'ultimo arco, numero di usi di una risorsa. **Idea:** lo **stato** diventa la coppia $(v,\text{info})$ con $\text{info}\in D$ discreto; si costruisce il **grafo espanso** $G'=(V',E')$ con $|V'|=n\cdot|D|$. Gli archi di $G'$ codificano transizioni di stato (archi reali + eventuali archi di attesa/transizione). Poi visitaBFS (se $G'$ non pesato) o Dijkstra su $G'$ (se pesato). **Costo:** $O(|V'|+|E'|)$ con BFS; $O(|E'|\log|V'|)$ con Dijkstra. → [[01 - Grafo degli stati aumentato]]

> [!info] Variante 5 — Distanze inverse (verso un nodo fisso) → grafo trasposto $G^T$
> **Quando:** serve $d_G(v,t)$ per tutti i nodi $v$, con destinazione $t$ fissa. **Idea:** $d_G(v,t)=d_{G^T}(t,v)$; una sola esecuzione di Dijkstra$(G^T,t)$ (o visitaBFS se non pesato) restituisce tutte le distanze verso $t$. **Costo:** $O(m\log n)$ con heap binario, identico a Dijkstra su $G$. → [[02 - Multi-run Dijkstra]]

> [!info] Variante 6 — Multi-sorgente → super-sorgente $s^*$, un solo Dijkstra
> **Quando:** più sorgenti $S=\{s_1,\ldots,s_k\}$; si vogliono le distanze dal più vicino $s_i\in S$ a ogni nodo. **Idea:** aggiungere nodo fittizio $s^*$ con archi $s^*\to s_i$ di peso $0$ per ogni $s_i\in S$; un solo Dijkstra (o BFS) da $s^*$. Se le sorgenti hanno distanze iniziali $\delta_i$ precompilate (es. costo del tratto precedente), gli archi $s^*\to s_i$ hanno peso $\delta_i$ invece di $0$. **Costo:** $O(m\log n)$, un solo Dijkstra. → [[02 - Multi-run Dijkstra]]

> [!info] Variante 7 — Nodo intermedio obbligatorio $x$ → due Dijkstra
> **Quando:** il cammino da $s$ a $t$ deve passare per un nodo fissato $x$. **Idea:** $d(s,t\mid x)=d(s,x)+d(x,t)$; calcolare $d(s,x)$ con Dijkstra$(G,s)$ e $d(x,t)$ con Dijkstra$(G^T,t)$. Se $x$ è noto a priori, in alternativa si lancia Dijkstra$(G,x)$ e si legge $d(x,t)$ direttamente. **Costo:** due esecuzioni di Dijkstra → $O(m\log n)$. → [[02 - Multi-run Dijkstra]]
## Esercizio 2 — pattern di progettazione
Cheat-sheet per la progettazione di algoritmi in pseudocodice (8 pt); pattern in ordine decrescente di frequenza d'esame (vedi [[Piano Esame ASD - Modulo I]]). Richiama le routine standard (DFS, BFS, Dijkstra, Heapify, ComponentiFortementeConnesse, MergeSort, IntegerSort) **per nome** senza riscriverle; pseudocodice solo per la logica nuova del problema.
| Pattern | Come riconoscerlo | Schema + struttura dati | Costo | Svolto |
|---|---|---|---|---|
| **DFS top-down** su albero binario | "conta i nodi con almeno … antenati …"; condizione che dipende dal cammino radice→nodo; profondità, somma, flag, contatori di colore | DFS pre-order ricorsiva; ogni chiamata riceve dal padre uno **stato cumulativo**; ordine fisso: (1) **test** sul nodo con lo stato ricevuto, (2) **aggiornamento** con il contributo del nodo, (3) **ricorsione** ai figli con lo stato aggiornato; caso base `null → 0` | $O(n)$ | [[01 - DFS top-down su albero binario]] |
| **Precalcolo array ausiliari** | bound $O(n)$ su array; serve run crescente/decrescente più lunga, elemento più vicino, prima o ultima occorrenza di un valore | Due scansioni lineari indipendenti: sx→dx per `left[]` / `prev[]` / `first[]`; dx→sx per `right[]` / `next[]`; `first[]` e `last[]` per valore con unica passata sx→dx (Pattern C: `first[h]` fissato alla prima occorrenza, `last[h]` aggiornato ad ogni occorrenza); passata finale combina gli array | $\Theta(n)$; $O(n+k)$ se indicizzato per valore | [[02 - Precalcolo di array ausiliari]] |
| **Struttura oracolo** | "struttura con preprocessing $O(n)$ e query $O(1)$" oppure "query $O(\log n)$"; domande ripetute sullo stesso array dopo una fase di build | (A) scansione dx→sx → `next[i]` = primo $j \ge i$ con proprietà; query $O(1)$. (B) prefix sum monotona + ricerca binaria; query $O(\log n)$. (C) prefix sum bidirezionale: conteggi sinistra/destra in $O(1)$ | Preprocessing $\Theta(n)$; query $O(1)$ o $O(\log n)$ | [[03 - Struttura oracolo]] |
| **Ordinamento come preprocessing** | "trova coppie/partizioni" con bound $o(n^2)$; oppure array intero con pochi outlier e richiesta lineare | (A) **IntegerSort** sugli elementi in-range + MergeSort su $O(n^{2/3})$ outlier + Merge: $O(n)$ totale. (B) MergeSort + due puntatori simmetrici (min col max): $O(n\log n)$. (C) conteggio frequenze + interleaving posizioni pari→dispari: $O(n\log n)$ o $O(n)$ | $O(n)$ o $O(n\log n)$ | [[04 - Ordinamento e conteggio come preprocessing]] |
| **Grafo modificato strutturalmente** | "mosse inverse su nodi speciali", "teletrasporto verso un insieme $U$"; poi verifica forte connessione o calcolo cammino minimo | Aggiungere archi extra: $O(m)$ inversi sugli archi di $E$ verso nodi speciali (Pattern A) oppure $O(n)$ di teletrasporto da $p$ verso ogni $q\in U$ (Pattern B); in entrambi i casi $G'$ resta $O(n+m)$; poi ComponentiFortementeConnesse (se connessione) oppure Dijkstra (se pesi) | $O(n+m)$ con CFC; $O(m\log n)$ con Dijkstra | [[07 - Grafo modificato strutturalmente]] |
| **Intersezione/appartenenza su insiemi** | "memoria $o(N)$" con $N$ molto grande; "quanti elementi comuni tra due insiemi"; bound $o(n^2)$ | Con vincolo memoria: **AVL** come dizionario, cresce solo con gli elementi distinti visti ($\ll N$). Senza vincolo: MergeSort su entrambi + merge con due puntatori, saltando **tutti** i duplicati dopo ogni match. (Hash set $O(1)$ att. ma fuori programma.) | AVL: $O(M\log n_{\text{dist}})$; sort+merge: $O((n+m)\log(n+m))$ | [[08 - Intersezione e appartenenza su insiemi]] |
| **Scansione lineare con prefix sum** | "spazio $O(1)$"; confronto prefisso vs suffisso senza array ausiliario; trovare il primo indice che soddisfa una soglia sulla somma cumulata | Passata 1: somma totale $S$. Passata 2: accumulatore `prefix`; suffisso = $S - \text{prefix}$ in $O(1)$; condizione riscrivibile come $2\cdot\text{prefix} > S$ per evitare la sottrazione esplicita | $O(n)$ tempo, $O(1)$ spazio | [[05 - Scansione lineare con prefix sum]] |
| **DFS post-order** su albero binario | "nel sottoalbero di $v$, **escluso $v$ stesso**, ci sono almeno … nodi …"; proprietà che sale foglie→radice | DFS post-order ricorsiva; ogni chiamata restituisce al padre una **tupla** (count, aggregati_sx + aggregati_dx); il contributo di $v$ va aggiunto ai valori *restituiti al padre* ($b_\text{desc} + [v.\text{col}=B]$), non usato nel test locale che confronta solo $b_{sx}+b_{dx}$ | $O(n)$ | [[06 - DFS post-order su albero binario]] |
| **Sliding window con BST** | finestra di $k$ elementi consecutivi; massimizza/minimizza elementi **distinti** o statistiche d'ordine nella finestra | BST bilanciato **aumentato**: ogni chiave con contatore occorrenze, campo `distinct` globale; inizializza con $S[1..k]$ in $O(k\log k)$; scorre con InsertWindow + DeleteWindow, ognuna $O(\log k)$ | $O(n\log k)$ | [[09 - Sliding window con BST]] |

> [!info] Schema mentale — come scegliere il pattern
> - **Albero + proprietà sugli antenati**: top-down (stato scende radice→foglie).
> - **Albero + proprietà sui discendenti, escluso il nodo**: post-order (aggregazione sale foglie→radice).
> - **Array, serve vicino / run / prima-ultima occorrenza**: due scansioni → precalcolo `left/right`, `prev/next`, `first/last`.
> - **Build una volta + query ripetute**: oracolo (scansione dx→sx, prefix sum, prefix sum bidirezionale).
> - **Coppie/insiemi, bound $o(n^2)$, senza vincolo memoria**: ordina + due puntatori.
> - **Insiemi con $N$ molto grande e memoria $o(N)$**: AVL come dizionario (cresce solo coi distinti; l'hash set è fuori programma).
> - **Grafo con operazioni speciali**: aggiungi archi $O(m)$ o $O(n)$ ($G'$ resta $O(n+m)$), poi ComponentiFortementeConnesse o Dijkstra.
> - **Array, spazio $O(1)$, prefisso vs suffisso**: due passate lineari, nessun array ausiliario.
> - **Finestra fissa, statistiche su elementi distinti**: BST aumentato con contatori.

> [!warning] DFS — ordine critico: test → aggiornamento → ricorsione
> **Top-down**: il test usa lo stato *ricevuto dal padre* (prima di aggiungervi il contributo di $v$); lo stato aggiornato si passa ai *figli*, non si ri-usa per il nodo corrente. Invertire test e aggiornamento conta $v$ tra i propri antenati, sovrastimando il risultato. **Post-order**: il contributo di $v$ si aggiunge ai valori *restituiti*, non al test locale (che confronta solo $b_{sx}+b_{dx}$ con la soglia, escludendo $v$). Omettere il `return` della tupla azzerarebbe tutta l'aggregazione verso l'alto.

> [!warning] Trappole per pattern specifici
> - **Integer Sort con outlier**: taglia array contatori = range degli elementi in-range (es. $10n+1$ celle), non $n$. Ordinare tutto con confronto dà $O(n\log n)$; IntegerSort sugli outlier non è applicabile perché il loro range è illimitato.
> - **Oracolo `next[]`**: costruire con scansione **dx→sx** (sx→dx è errato: i valori a destra non sono ancora stati visitati quando si elabora $i$).
> - **Binary search su prefix sum**: valida solo se la sequenza è monotona, condizione garantita da $A[i] \ge 0$; con valori negativi il metodo è scorretto.
> - **Insiemi con vincolo $o(N)$**: `boolean[1..N]` occupa $\Theta(N)$ e viola il vincolo → si usa un **AVL** come dizionario (l'hash table è fuori programma). Nel sort+merge saltare *tutti* i duplicati dopo ogni match (non solo il primo), altrimenti lo stesso valore distinto viene contato più volte.
> - **Sliding window**: sostituire il BST con una hash table semplice non funziona — senza contatore per chiave, decrementare un'occorrenza farebbe eliminare la chiave anche se ne restano altre copie nella finestra corrente.
## Esercizio 3 — pattern di modellazione
Cheat-sheet di riconoscimento rapido: da "problema a parole" a schema efficiente. Le routine standard (visitaBFS, Dijkstra, DFS, MergeSort, RicercaBinaria, Heapify, Componenti Fortemente Connesse) si richiamano per nome senza riscriverle; i loro pseudocodici sono nelle sezioni precedenti del formulario. Svolti completi con pseudocodice nei wikilink.

| Pattern | Quando riconoscerlo | Schema (nodo / arco / stato / peso) | Costo | Freq. | Svolto |
| --- | --- | --- | --- | --- | --- |
| **Grafo degli stati aumentato** | cammino con vincolo che dipende dalla *storia*: parità, colore arco, timestamp, # usi di una risorsa | nodo $=(v,s)$, $s\in S$ discreto; $\lvert V'\rvert=n\lvert S\rvert$; archi intra-layer (mosse) + archi inter-layer (transizioni di stato) | BFS $O((n+m)\lvert S\rvert)$; Dijkstra $O((n+m)\lvert S\rvert\log(n\lvert S\rvert))$ | 🔴 5× | [[01 - Grafo degli stati aumentato]] |
| **Multi-run Dijkstra + $G^T$** | obiettivo separabile $f(d_s(x),\,d_t(x),\,\text{dati}_x)$ su candidati $x\in X$ | Dijkstra da $s$ su $G$ → $d_s[\,]$; Dijkstra da $t$ su $G^T$ → $d_t[\,]$; scansione lineare su $X$ | $O(m+n\log n)$ | 🔴 4× | [[02 - Multi-run Dijkstra]] |
| *↳ super-sorgente con distanze iniziali* | relay multi-hop: $\min_{m\in M}(d_s(m)+d_w(m,f))$ non separabile per $m$ e $f$ | nodo $S$ con archi $S\!\to\!m$ pesati $d_s(m)$; Dijkstra da $S$ → $g(f)=\min_m(\cdots)$ per ogni $f$ in una passata | $O(m+n\log n)$ | incl. 🔴 4× | [[02 - Multi-run Dijkstra]] |
| **DFS top-down / bottom-up su albero** | proprietà del nodo dipende dagli *antenati* (top-down) e/o dai *discendenti* (bottom-up) | stato scende come parametro per valore (massimo, somma, flag, colore padre); valore aggregato risale come return (count, max, coppia) | $\Theta(n)$ | 🔴 3× | [[03 - DFS con stato cumulativo top-down]] |
| **Prefix sums 1D** | range sum $[i,j]$ in $O(1)$; range difference $(\#1-\#0)$ con mappatura $v_k\mapsto 2v_k-1$ | $P[0]=0$; $P[k]=P[k-1]+v_k$; query: $P[j]-P[i-1]$ | preproc. $O(n)$, query $O(1)$ | 🟡 2× | [[04 - Prefix sums 1D]] |
| **Ordinamento + ricerca binaria o merge** | membership ripetuta su un insieme; intersezione/unione di due array | MergeSort; poi RicercaBinaria $O(\log n)$ per membership; oppure merge a due puntatori $O(n+m)$ per $\lvert A\cap B\rvert$, $\lvert A\cup B\rvert$ | $O(n\log n)$ | 🟡 2× | [[05 - Ordinamento con binary search o merge]] |
| **0-1 BFS / BFS su grafo implicito** | pesi $\in\{0,1\}$ → 0-1 BFS con deque; grafo a grado costante non esplicitato → BFS classica | nodi = stati (celle, posizioni); archi generati on-the-fly; 0-1 BFS: peso $0$→testa deque, peso $1$→coda | $O(\lvert V\rvert+\lvert E\rvert)$; grado $O(1)$$\Rightarrow$$O(n)$ | 🟡 2× | [[06 - BFS su grafo implicito e 0-1 BFS]] |
| **Ricerca binaria su prefix sums monotone** | trovare il min indice $k$ t.c. $P[k]\ge\text{soglia}$; richiede $A[i]\ge 0$ | preproc. $P$ in $O(n)$; caso $k=1$ verificato separatamente; RicercaBinaria su $P[2..n]$ (monotono) | preproc. $O(n)$, query $O(\log n)$ | ⚪ 1× | [[07 - Binary search su prefix sums monotone]] |
| **Selezione online $k$ minimi** | stream non memorizzabile; mantenere i $k$ migliori in spazio $O(k)$ | max-heap di taglia $k$; se $a_i<H[1]$: sostituisce radice + fixHeap; altrimenti scarta | $O(n\log k)$ — inizializzazione $O(k)$ con Heapify + $(n-k)$ fixHeap da $O(\log k)$ ciascuno | ⚪ 1× | [[08 - Selezione online con max-heap]] |
| **Forte connettività con modifica locale** | esiste $x\in C$ t.c. invertire tutti gli archi incidenti a $x$ rende $G$ FC? | per ogni $x$: costruisce $G_x$ (inverte archi con un estremo $= x$) + Componenti Fortemente Connesse; esito se 1 sola CFC | $O(\lvert C\rvert(n+m))$ | ⚪ 1× | [[09 - Forte connettività con modifica locale]] |
| **Binary search on answer** | minimizzare parametro $\ell$ a fattibilità monotona; oracolo grafo+BFS disponibile | BS su $\{1,\ldots,k\}$; oracolo: $G_\ell=(V,\{e:\lambda(e)\le\ell\})$ + visitaBFS; verifica $d[v]\le h$ per ogni $v\in V$ | $O((n+m)\log k)$ | ⚪ 1× | [[10 - Binary search on answer]] |
| **Prefix sums 2D** | range sum su rettangolo di matrice $n\times m$ in $O(1)$ | $P[i][j]=A[i][j]+P[i-1][j]+P[i][j-1]-P[i-1][j-1]$; query per inclusione-esclusione su 4 angoli | preproc. $O(nm)$, query $O(1)$ | ⚪ 1× | [[11 - Prefix sums 2D]] |
| **Scansione lineare spazio $O(1)$** | confrontare prefisso di $A$ con suffisso di $B$ senza array ausiliari | 1ª passata: `total_B`; 2ª: scalari `prefA`, `prefB`; $\sum_{k=i}^{n}B[k]=\text{total\_B}-\text{prefB}$ (aggiorna `prefB` *dopo* il test) | $O(n)$ tempo, $O(1)$ spazio | ⚪ 1× | [[12 - Scansione lineare in spazio costante]] |

> [!info] Grafo degli stati aumentato — costruzione del grafo espanso
> **Ricetta in 3 passi.**
> (1) Identificare lo stato discreto $s$ che distingue configurazioni diverse sullo stesso nodo: parità ($\lvert S\rvert=2$), colore arco ($\lvert S\rvert=$ num. colori), timestamp ($\lvert S\rvert=k$), contatore usi ($\lvert S\rvert=k+1$).
> (2) Costruire $G'=(V',E')$: nodi $V'=V\times S$ (un *layer* per valore di $s$); archi intra-layer per le mosse ordinarie; archi inter-layer per le transizioni (cambio parità, avanzamento clock, consumo risorsa).
> (3) Lanciare visitaBFS o Dijkstra da $(s_{\text{sorg}}, s_{\text{init}})$; risposta $=\min_{s\in S_{\text{ok}}} d[(t,s)]$ (o solo per certi valori di $s$, a seconda del vincolo).
>
> **Dimensioni:** $\lvert V'\rvert=n\lvert S\rvert$, $\lvert E'\rvert=O((n+m)\lvert S\rvert)$. Con $\lvert S\rvert=O(1)$ la complessità totale rimane $O(n+m)$ per BFS e $O(m+n\log n)$ per Dijkstra.

> [!info] Multi-run Dijkstra — disaccoppiamento dell'obiettivo e variante super-sorgente
> **Forma canonica:** costo $=f_1(d_s(x))+f_2(d_t(x))+g(x)$ per ogni candidato $x\in X$. Una Dijkstra da $s$ su $G$ → $d_s[\,]$; una Dijkstra da $t$ su $G^T$ → $d_t[\,]$; scansione $O(\lvert X\rvert)$ su $X$. Totale $O(m+n\log n)$.
>
> **Variante super-sorgente:** se l'obiettivo è $d_s(m)+d_{w_1}(m,f)$ con $m\in M$, $f\in F$, il termine centrale accoppia $m$ e $f$. Si aggiunge una super-sorgente $S$ con archi $S\!\to\!m$ pesati $d_s(m)$: Dijkstra da $S$ restituisce $g(f)=\min_{m\in M}(d_s(m)+d_{w_1}(m,f))$ per tutti gli $f$ in un'unica passata. Per il ritorno: Dijkstra da $t$ su $G^T$ con $w_2$ → $d_t[\,]$; risposta $=\min_{f\in F}(g(f)+d_t(f))$.

> [!info] DFS top-down / bottom-up — flusso di informazione
> **Top-down:** il parametro porta ai figli l'informazione sugli antenati (massimo, profondità, flag, colore del padre). Si aggiorna *dopo* aver processato il nodo corrente e *prima* delle chiamate ricorsive. Il nodo corrente **non** è antenato di sé stesso.
>
> **Bottom-up:** il return aggrega i contributi dei sottoalberi (count, max, coppia $(c_1,c_2)$). Le chiamate ricorsive precedono il calcolo locale.
>
> **Combinato:** la DFS porta giù `anc` (es. miglior antenato speciale) e risale `nsd` (es. miglior discendente speciale); per ogni nodo $V[v]=\max(\text{anc},\ \max_c \text{nsd}(c))$ — vedi [[03 - DFS con stato cumulativo top-down#Variante — nodo speciale raggiungibile (18/07/2022)]].

> [!warning] Trabocchetti frequenti — Esercizio 3
> - **Grafo espanso:** omettere gli archi inter-layer (es. archi di attesa $((v,\tau),(v,\tau+1))$) rende impossibili le transizioni di stato. Inizializzare BFS/Dijkstra da $(s_{\text{sorg}}, s_{\text{init}})$, non da tutti i layer di $s_{\text{sorg}}$.
> - **$G^T$ e multi-run:** evita $\lvert X\rvert$ Dijkstra separate su $G$ per calcolare $d(x,t)$ → $O(\lvert X\rvert(m+n\log n))$; una sola Dijkstra da $t$ su $G^T$ basta e costa $O(m+n\log n)$.
> - **Super-sorgente:** archi $S\!\to\!m$ pesati $d_s(m)$, **non** $0$: inizializzare con $0$ ignora il tratto $s\to m$ e produce distanze errate.
> - **DFS:** aggiornare il parametro top-down *per i figli* (non nel controllo del nodo corrente). Niente variabili globali: il backtracking le corrompe.
> - **Prefix sums 1D:** query $[i,j]$ usa $P[i-1]$, non $P[i]$ (off-by-one esclude $A[i]$). **2D:** il segno del termine angolare è $+P[i-1][j-1]$, **non** $-$ (inclusione-esclusione lo reintroduce una volta).
> - **0-1 BFS:** coda FIFO classica → distanze errate con pesi $\{0,1\}$; serve la deque (peso $0$→testa, peso $1$→coda).
> - **Selezione online:** serve il *max*-heap (non min-heap): la radice è il "peggior tra i migliori" visti finora.
> - **Forte connettività:** la modifica inverte *sia* gli archi entranti *sia* quelli uscenti di $x$, non solo metà.
> - **Binary search on answer:** filtrare $\lambda(e)\le\ell$ (non $=\ell$); verificare che la fattibilità sia effettivamente monotona rispetto a $\ell$ prima di applicare la BS.
