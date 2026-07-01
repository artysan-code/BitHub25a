---
tags:
  - algoritmi
  - strutture-dati
---
# Binary search su prefix sums monotone
Esercizio di **modellazione**: si riconosce una struttura **monotona** (i prefix sum di valori non negativi) e la si interroga con la **ricerca binaria**, algoritmo già noto. Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|prefix sum]], [[05 - Strutture Dati Elementari e Dizionari#Il Tipo di Dato Dizionario|array ordinato e ricerca binaria]].
## Traccia
> [!question] Traccia — 22/06/2022
> Sia $A[1..n]$ un vettore di $n$ numeri positivi. Un indice $k\in\{1,\dots,n\}$ è il **taglio bilanciato** di $A$ se è il minimo indice tale che la somma dei primi $k$ elementi è almeno la somma dei restanti. Progettare un oracolo, costruibile in $O(n)$, che risponda in $O(\log n)$ a $\text{TaglioBilanciato}(\alpha)$: il taglio bilanciato del vettore ottenuto da $A$ **aggiungendo $\alpha\geq 0$ al primo elemento**.

Il taglio bilanciato è il primo punto in cui il prefisso "pareggia o supera" il suffisso. La query cambia il solo primo elemento ($A[1]\to A[1]+\alpha$) e chiede il nuovo taglio: si vuole rispondere in $O(\log n)$ **senza** ricostruire i prefissi ogni volta.
## Idea risolutiva
Sia $P[k]=\sum_{h=1}^{k}A[h]$ e $S=P[n]$. Aggiungere $\alpha$ ad $A[1]$ significa $A'[1]=A[1]+\alpha$: poiché $A[1]$ compare in **ogni** prefisso, si ha $P'[k]=P[k]+\alpha$ per ogni $k\geq 1$, e la nuova somma totale è $S'=S+\alpha$. Il taglio bilanciato di $A'$ è il minimo $k$ con prefisso $\geq$ suffisso:
$$P'[k]\ \geq\ S'-P'[k] \iff P[k]+\alpha \ \geq\ S-P[k] \iff P[k]\ \geq\ \frac{S-\alpha}{2}.$$
Poiché $A[i]>0$, $P$ è **strettamente crescente**, quindi il predicato $P[k]\geq(S-\alpha)/2$ è **monotono** in $k$: falso per i piccoli $k$, poi vero. Si trova il minimo $k$ che lo soddisfa con una **ricerca binaria** su $P$. Il preprocessing calcola $P$ una volta; ogni query è solo una ricerca binaria con soglia dipendente da $\alpha$ — nessun caso speciale su $k=1$ ($\alpha$ entra in tutti i prefissi, non solo nel primo).
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciOracolo($A$, $n$) → array P}
\begin{algorithmic}
\State $P[0] \gets 0$
\For{$k \gets 1$ \To $n$}
  \State $P[k] \gets P[k-1] + A[k]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{TaglioBilanciato($P$, $n$, $\alpha$) → intero}
\begin{algorithmic}
\State $\mathit{soglia} \gets (P[n] - \alpha) / 2$
\State $lo \gets 1$; $hi \gets n$
\While{$lo < hi$}
  \State $mid \gets \lfloor (lo + hi)/2 \rfloor$
  \If{$P[mid] \geq \mathit{soglia}$} \State $hi \gets mid$
  \Else \State $lo \gets mid + 1$ \EndIf
\EndWhile
\State \Return $lo$
\end{algorithmic}
\end{algorithm}
```

La soglia $(P[n]-\alpha)/2$ incorpora $\alpha$ una volta sola; la ricerca binaria restringe $[lo,hi]$ al minimo $k$ con $P[k]\geq\mathit{soglia}$.
## Complessità
Preprocessing $\Theta(n)$ (una scansione) e $\Theta(n)$ spazio per $P$; ogni query è una ricerca binaria su $P$ monotono, $O(\log n)$. Le query non ricostruiscono $P$: sfruttano che $\alpha$ sposta solo la soglia, non l'array.
## Correttezza
> [!quote] Invariante — monotonia del predicato
> Con $A[i]>0$, $P$ è strettamente crescente; quindi esiste una soglia $k^\*$ tale che $P[k]\geq\mathit{soglia}$ è **falso** per $k<k^\*$ e **vero** per $k\geq k^\*$. La ricerca binaria mantiene l'invariante "$P[hi]\geq\mathit{soglia}$ e $P[lo-1]<\mathit{soglia}$", convergendo a $lo=k^\*$.

**Dimostrazione.** La derivazione dell'Idea mostra che il taglio bilanciato di $A'$ è il minimo $k$ con $P[k]\geq(S-\alpha)/2=\mathit{soglia}$. Per la monotonia di $P$, tale insieme di indici è un suffisso $\{k^\*,\dots,n\}$; la ricerca binaria classica su predicato monotono restituisce il suo estremo sinistro $k^\*$. L'esistenza è garantita: a $k=n$, $P[n]=S\geq(S-\alpha)/2$ poiché $\alpha\geq 0$. $\blacksquare$

> [!warning] Nessun caso speciale su $k=1$
> $\alpha$ è aggiunto all'**elemento** $A[1]$, quindi compare in ogni prefisso $P'[k]=P[k]+\alpha$: la soglia si abbassa **uniformemente** per tutti i $k$, non solo per $k=1$. Trattare $k=1$ a parte (come se $\alpha$ contasse solo lì) falsa il risultato. E serve $A[i]\geq 0$: con valori negativi $P$ non è monotono e la ricerca binaria non è applicabile.
