---
tags:
  - algoritmi
  - ordinamento
---
# Ordinamento e conteggio come preprocessing
Esercizio di **progettazione** in cui il cuore della soluzione è **ordinare o contare** in fase di preprocessing (richiamando Integer Sort / MergeSort come scatole nere), dopodiché una passata lineare — greedy, due puntatori, interleaving — risolve il problema. Ripasso: [[04 - Algoritmi di Ordinamento#Integer Sort (Counting Sort)|Integer Sort]], [[04 - Algoritmi di Ordinamento#Merge Sort|MergeSort]].
## A · Integer Sort con pochi outlier
> [!question] Traccia — 22/06/2022
> Sia $A[1..n]$ un vettore di interi tale che **tutti gli elementi tranne $O(n^{2/3})$** sono compresi fra $1$ e $10n$. Progettare un algoritmo di complessità **lineare** che ordina $A$.

Gli elementi *in range* $[1,10n]$ hanno valori limitati (ordinabili in tempo lineare per conteggio), mentre i pochi *outlier* hanno valori arbitrari. La chiave è usare lo strumento giusto su ciascun gruppo e poi fondere.
### Idea risolutiva
Con una scansione si separa $A$ in $\text{IN}$ (elementi in $[1,10n]$) e $\text{OUT}$ (gli $O(n^{2/3})$ outlier). $\text{IN}$ si ordina con **Integer Sort** su range $[1,10n]$ in $O(n)$; $\text{OUT}$ con **MergeSort** in $O(n^{2/3}\log n)=o(n)$; infine si **fondono** le due sequenze ordinate con un merge a due puntatori in $O(n)$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{ordinaConOutlier($A$, $n$) → array ordinato}
\begin{algorithmic}
\State $\text{IN} \gets [\,]$; $\text{OUT} \gets [\,]$
\For{$i \gets 1$ \To $n$}
  \If{$1 \leq A[i]$ e $A[i] \leq 10n$} \State aggiungi $A[i]$ a $\text{IN}$
  \Else \State aggiungi $A[i]$ a $\text{OUT}$ \EndIf
\EndFor
\State \Call{IntegerSort}{$\text{IN}$, range $[1,10n]$} \Comment{$O(n)$}
\State \Call{MergeSort}{$\text{OUT}$} \Comment{$O(n^{2/3}\log n)=o(n)$}
\State \Return \Call{Merge}{$\text{IN}$, $\text{OUT}$} \Comment{due puntatori, $O(n)$}
\end{algorithmic}
\end{algorithm}
```
### Complessità
Partizione $O(n)$; Integer Sort $O(n+10n)=O(n)$; MergeSort sugli outlier $O(n^{2/3}\log n)=o(n)$; merge $O(n)$. Totale **$O(n)$**; spazio $O(n)$.
### Correttezza
Ogni elemento finisce in $\text{IN}$ o $\text{OUT}$ secondo il suo valore; entrambe le sottosequenze vengono ordinate correttamente dai rispettivi algoritmi (Integer Sort è corretto su $[1,10n]$, MergeSort su valori arbitrari) e il merge a due puntatori di due sequenze ordinate produce l'unione ordinata. Quindi l'output è $A$ ordinato. $\blacksquare$

> [!warning] Il range dei contatori
> Integer Sort sull'intero $A$ fallisce: gli outlier hanno valori illimitati → array dei contatori di taglia indefinita. E MergeSort su tutto $A$ darebbe $O(n\log n)$, non lineare. I contatori vanno dimensionati sul range **effettivo** in range ($10n+1$ celle), non su $n$.
## B · Ordina + due puntatori
> [!question] Traccia — 21/01/2025
> Sia $A[1..n]$ un vettore di $n$ numeri, con $n$ pari. Partizionare gli $n$ numeri in $n/2$ gruppi da $2$ in modo che la somma dei numeri all'interno di ogni gruppo sia **uguale** per tutti i gruppi. Restituire `true` se è possibile, `false` altrimenti. Punteggio pieno per $o(n^2)$.
### Idea risolutiva
Se una partizione esiste, ogni coppia vale $t = 2S/n$ con $S=\sum_i A[i]$ (somma totale divisa per il numero di coppie $n/2$). Se $2S$ non è multiplo di $n$, $t$ non è intero → impossibile. Altrimenti si **ordina** $A$ e si accoppiano gli estremi ($A[i]$ con $A[n+1-i]$): per *exchange argument* è l'unico accoppiamento possibile se una soluzione esiste. Si verifica che tutte le coppie estreme valgano $t$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{partizionePossibile($A$, $n$) → booleano}
\begin{algorithmic}
\State $S \gets 0$
\For{$i \gets 1$ \To $n$} \State $S \gets S + A[i]$ \EndFor
\If{$2S \bmod n \neq 0$} \State \Return false \Comment{somma per coppia non intera} \EndIf
\State $t \gets 2S / n$
\State \Call{MergeSort}{$A$}
\For{$i \gets 1$ \To $n/2$}
  \If{$A[i] + A[n+1-i] \neq t$} \State \Return false \EndIf
\EndFor
\State \Return true
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Dominata dal MergeSort: **$O(n\log n)=o(n^2)$** (punteggio pieno); somma e verifica sono $O(n)$. Correttezza: se una partizione a somma costante esiste, la sua somma comune è $t=2S/n$. Il minimo $A[1]$ deve accoppiarsi con $t-A[1]$; essendo $A[1]$ il minimo, $t-A[1]$ è il massimo valore-partner richiesto, cioè $A[n]$ — quindi min con max. Ripetendo l'argomento sui restanti, l'accoppiamento estremo $A[i]\!-\!A[n+1-i]$ è **forzato**. Dunque la partizione esiste se e solo se tutte le coppie estreme valgono $t$, che è esattamente ciò che l'algoritmo verifica. $\blacksquare$

> [!warning] Prima il test di divisibilità
> Verificare $2S \bmod n = 0$ **prima** di ordinare evita di eseguire il MergeSort su un'istanza già impossibile.
## C · Conteggio frequenze + interleaving
> [!question] Traccia — 09/09/2024
> Sia $A[1..n]$ ($n$ pari). Permutare gli elementi in modo che non ci siano mai due elementi **uguali adiacenti**, oppure dichiarare correttamente che è impossibile. Spazio $O(n)$.
### Idea risolutiva
Si contano le frequenze dei valori distinti. Una permutazione senza uguali adiacenti esiste **se e solo se** la frequenza massima $f_{\max} \leq n/2$. Se ammissibile, si **interleava**: si scrivono gli elementi ordinati per frequenza decrescente (copie dello stesso valore contigue) prima nelle posizioni pari $0,2,4,\dots$ e poi nelle dispari $1,3,5,\dots$; così due copie contigue nell'ordine cadono a distanza $\geq 2$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{permutaSenzaAdiacenti($A$, $n$) → array B oppure "impossibile"}
\begin{algorithmic}
\State conta le frequenze dei valori distinti di $A$ \Comment{Integer Sort / conteggio, $O(n)$}
\State $f_{\max} \gets$ frequenza massima
\If{$f_{\max} > n/2$} \State \Return impossibile \EndIf
\State $\text{ord} \gets$ elementi ordinati per frequenza decrescente (copie contigue)
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
### Complessità e correttezza
Conteggio e riempimento $O(n)$ (o $O(n\log n)$ se l'ordinamento per frequenza usa MergeSort); spazio $O(n)$ per contatori e $B$. Correttezza: se $f_{\max}>n/2$ un valore comparirebbe in più di metà delle posizioni e due sue copie sarebbero per forza adiacenti → impossibile. Se $f_{\max}\leq n/2$, l'interleaving colloca le $f$ copie di ogni valore in posizioni che distano $\geq 2$ (sono contigue in $\text{ord}$ e $pos$ avanza di $2$): il valore più frequente, con $\leq n/2$ copie, riempie al più tutte le pari senza tornare adiacente a sé. Quindi nessuna coppia uguale adiacente. $\blacksquare$

> [!example] Esempio — valori $\{a,a,b,c\}$, $n=4$
> Frequenze $a\!:2$, $b\!:1$, $c\!:1$; $f_{\max}=2\leq n/2$. $\text{ord}=[a,a,b,c]$.
> - $t=0$: $B[0]=a$, $pos\to2$; $t=1$: $B[2]=a$, $pos\to4\geq4$ → $pos=1$; $t=2$: $B[1]=b$, $pos\to3$; $t=3$: $B[3]=c$.
>
> $B=[a,b,a,c]$: le due $a$ in posizione $0$ e $2$ (distanza $2$). ✓

> [!warning] Ordine di riempimento
> La condizione è $f_{\max}\leq n/2$ (non $<n$); e l'interleaving deve riempire **prima tutte** le pari e poi le dispari — invertendo l'ordine, due copie del valore più frequente possono cadere adiacenti a cavallo del passaggio.
