---
tags:
  - algoritmi
---
# Ordinamento con binary search o merge
Casistica tipica dell'Es. 3 (Modellazione): vedi [[Casistiche d'Esame Modulo I]] per il quadro completo, [[Piano Esame ASD - Modulo I]] per la checklist, [[05 - Strutture Dati Elementari e Dizionari]] per la ricerca binaria e le strutture di supporto.
## Svolgimento — esame 12/09/2023
> [!question] Traccia — 12/09/2023
> Dato un array $A$ di $n$ interi, un elemento $A[i]$ si dice **felice al quadrato** se il valore $A[i]^2$ è anch'esso presente in $A$. Progettare un algoritmo che conti il numero di elementi felici al quadrato in $A$ con costo $O(n \log n)$.
**Modellazione.** L'approccio ingenuo controlla, per ogni $A[i]$, se $A[i]^2$ compare in $A$ con una scansione lineare: $O(n)$ per elemento, $O(n^2)$ in totale. Per abbattere il costo a $O(n \log n)$ si sfrutta l'ordinamento come preprocessing:
1. **Ordina** $A$ con MergeSort in $\Theta(n \log n)$.
2. **Cerca** per ogni $A[i]$ il valore $A[i]^2$ nell'array ordinato con RicercaBinaria in $O(\log n)$.
3. **Conta** le occorrenze positive e restituisci il totale.

Il totale diventa $\Theta(n \log n) + n \cdot O(\log n) = O(n \log n)$.

Si noti che $A[i]^2 \ge 0$ per ogni intero: se $A$ contiene valori negativi, il loro quadrato è positivo, quindi la ricerca binaria opera correttamente sull'array ordinato senza trattamenti speciali.

```pseudo
\begin{algorithm}
\caption{FeliciAlQuadrato($A$, $n$) → intero}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}
\State $\text{cont} \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $q \gets A[i]^2$
  \If{\Call{RicercaBinaria}{$A$, $q$} $\ne$ NIL}
    \State $\text{cont} \gets \text{cont} + 1$
  \EndIf
\EndFor
\State \Return $\text{cont}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n \log n)$ — dominata dal MergeSort; le $n$ ricerche binarie contribuiscono $O(n \log n)$ complessivamente.
**Trappola:** nella RicercaBinaria occorre verificare che il valore trovato sia **esattamente** $q$: un lower bound che si ferma sull'elemento più vicino (ma diverso) darebbe un falso positivo. La funzione deve restituire NIL se $q$ non è presente, non l'indice del più vicino.
## Variante — coefficiente di Jaccard (28/09/2022)
> [!question] Traccia — 28/09/2022
> Dati due insiemi di interi $A$ e $B$ di dimensione $n$ e $m$, calcolare il coefficiente di Jaccard $J = |A \cap B| / |A \cup B|$ con costo $O((n+m)\log(n+m))$.
**Modellazione.** Il calcolo diretto di $|A \cap B|$ e $|A \cup B|$ con scansioni nested è $O(nm)$. Ordinando entrambi gli array si può usare un merge a due puntatori:
1. **Ordina** $A$ con MergeSort in $O(n \log n)$ e $B$ in $O(m \log m)$.
2. **Merge a due puntatori**: avanza il puntatore con valore minore; se $A[i] = B[j]$ incrementa sia $|\text{intersez}|$ sia $|\text{unione}|$ e avanza entrambi; altrimenti incrementa solo $|\text{unione}|$ e avanza il puntatore minore. Gestisci i rimanenti alla fine.
3. **Restituisci** $|\text{intersez}| / |\text{unione}|$.

```pseudo
\begin{algorithm}
\caption{Jaccard($A$, $n$, $B$, $m$) → reale}
\begin{algorithmic}
\State \Call{MergeSort}{$A$}
\State \Call{MergeSort}{$B$}
\State $i \gets 1$; $j \gets 1$; $\text{intersez} \gets 0$; $\text{unione} \gets 0$
\While{$i \le n$ e $j \le m$}
  \If{$A[i] = B[j]$}
    \State $\text{intersez} \gets \text{intersez} + 1$
    \State $\text{unione} \gets \text{unione} + 1$
    \State $i \gets i + 1$; $j \gets j + 1$
  \ElsIf{$A[i] < B[j]$}
    \State $\text{unione} \gets \text{unione} + 1$; $i \gets i + 1$
  \Else
    \State $\text{unione} \gets \text{unione} + 1$; $j \gets j + 1$
  \EndIf
\EndWhile
\State $\text{unione} \gets \text{unione} + (n - i + 1) + (m - j + 1)$
\State \Return $\text{intersez} / \text{unione}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O((n+m)\log(n+m))$ — due MergeSort più un merge lineare $O(n+m)$.
**Trappola:** nel merge a due puntatori occorre avanzare il puntatore col valore **minore** (non entrambi); se i due valori sono uguali avanzarli entrambi per evitare di contare il duplicato due volte nell'unione.
