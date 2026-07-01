---
tags:
  - algoritmi
  - ordinamento
---
# Ordinamento con binary search o merge
Esercizio di **modellazione**: si **ordina** l'input come preprocessing, poi si usano algoritmi noti — ricerca binaria per le ricerche ripetute, merge a due puntatori per confrontare due insiemi. Ripasso: [[04 - Algoritmi di Ordinamento#Merge Sort|MergeSort]], [[05 - Strutture Dati Elementari e Dizionari#Il Tipo di Dato Dizionario|array ordinato e ricerca binaria]].
## A · Ricerca ripetuta di un valore derivato
> [!question] Traccia — 12/09/2023
> Sia $A[1..n]$ un vettore di interi **positivi**. Un elemento $A[i]$ è **felice al quadrato** se esiste un indice $j$ tale che $A[j]=A[i]^2$. Progettare un algoritmo che, in tempo $O(n\log n)$, dica **se esiste** almeno un elemento felice al quadrato.

La domanda è di esistenza (booleano). L'approccio ingenuo cerca $A[i]^2$ in $A$ con una scansione per ogni $i$: $O(n^2)$. Ordinando $A$ una volta, ogni ricerca costa $O(\log n)$.
### Idea risolutiva
Si **ordina** $A$ con MergeSort ($O(n\log n)$); poi, per ogni $A[i]$, si cerca $A[i]^2$ nell'array ordinato con **ricerca binaria** ($O(\log n)$). Appena una ricerca ha successo si restituisce `true`; se nessuna la trova, `false`. Con interi positivi $A[i]^2\geq A[i]>0$: nessun caso speciale, la ricerca binaria opera sull'array ordinato.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{esisteFeliceAlQuadrato($A$, $n$) → booleano}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}
\For{$i \gets 1$ \To $n$}
  \If{\Call{RicercaBinaria}{$A$, $A[i]^2$} $\neq$ null}
    \State \Return true
  \EndIf
\EndFor
\State \Return false
\end{algorithmic}
\end{algorithm}
```
### Complessità
MergeSort $O(n\log n)$; $n$ ricerche binarie da $O(\log n)$ → $O(n\log n)$. Totale **$O(n\log n)$**, dominato dall'ordinamento.
### Correttezza
L'ordinamento è una permutazione di $A$: non aggiunge né toglie valori, quindi "$x$ è presente in $A$" è invariato. La ricerca binaria su array ordinato restituisce un elemento uguale a $A[i]^2$ se e solo se tale valore è presente. Perciò l'algoritmo restituisce `true` se e solo se esiste $i$ con $A[i]^2\in A$, cioè un elemento felice al quadrato. $\blacksquare$

> [!warning] Match esatto
> La ricerca binaria deve confermare che il valore trovato sia **esattamente** $A[i]^2$: un lower bound che si ferma sul più vicino darebbe un falso positivo. Deve restituire null se il valore non è presente.
## B · Intersezione e unione: coefficiente di Jaccard
> [!question] Traccia — 28/09/2022
> Dati due insiemi $A$ e $B$ di $n$ elementi ciascuno, calcolare il coefficiente di Jaccard $J(A,B)=\dfrac{|A\cap B|}{|A\cup B|}$ in tempo $o(n^2)$.
### Idea risolutiva
Calcolare intersezione e unione con scansioni annidate è $O(n^2)$. Ordinando entrambi gli array si usa un **merge a due puntatori**: si avanza il puntatore col valore minore; a un match si incrementano sia $|\cap|$ sia $|\cup|$ e si avanzano entrambi, altrimenti si incrementa solo $|\cup|$ e avanza il minore. I rimanenti di un array contribuiscono tutti all'unione.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{jaccard($A$, $B$, $n$) → reale}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}; \Call{MergeSort}{$B$}
\State $i \gets 1$; $j \gets 1$; $\mathit{int} \gets 0$; $\mathit{uni} \gets 0$
\While{$i \leq n$ e $j \leq n$}
  \If{$A[i] = B[j]$}
    \State $\mathit{int} \gets \mathit{int}+1$; $\mathit{uni} \gets \mathit{uni}+1$; $i \gets i+1$; $j \gets j+1$
  \ElsIf{$A[i] < B[j]$}
    \State $\mathit{uni} \gets \mathit{uni}+1$; $i \gets i+1$
  \Else
    \State $\mathit{uni} \gets \mathit{uni}+1$; $j \gets j+1$
  \EndIf
\EndWhile
\State $\mathit{uni} \gets \mathit{uni} + (n-i+1) + (n-j+1)$ \Comment{elementi residui di un array}
\State \Return $\mathit{int} / \mathit{uni}$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Due MergeSort $O(n\log n)$ più un merge lineare $O(n)$: totale **$O(n\log n)=o(n^2)$**. Correttezza: su array ordinati, avanzare il puntatore col valore minore garantisce che ogni valore comune sia incontrato come match (conta $1$ in $\cap$ e $1$ in $\cup$), mentre i valori presenti in uno solo dei due contano $1$ in $\cup$; i residui finali sono tutti nell'unione. Quindi $\mathit{int}=|A\cap B|$ e $\mathit{uni}=|A\cup B|$. $\blacksquare$

> [!warning] Avanzare il minore, contare una volta
> A un match si avanzano **entrambi** i puntatori (per non contare due volte il valore comune nell'unione); quando i valori differiscono avanza **solo** quello col valore minore. Trattandosi di insiemi non ci sono duplicati interni.
