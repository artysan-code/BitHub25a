---
tags:
  - algoritmi
  - strutture-dati
---
# Scansione lineare con prefix sum
Esercizio di **progettazione** su array: la proprietà cercata dipende dalla somma di un prefisso, che si mantiene in **un solo accumulatore** durante una scansione — $O(n)$ tempo e $O(1)$ spazio, senza array ausiliari. Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|somme di prefisso]].
## Traccia
> [!question] Traccia — 19/02/2024
> Sia $A[1..n]$ un vettore di $n$ numeri **positivi**. Progettare un algoritmo che in tempo $O(n)$ e **memoria ausiliaria costante** trova il più piccolo indice $i$ tale che la somma dei primi $i$ elementi di $A$ è maggiore della somma dei restanti elementi in $A[i+1..n]$.

Detta $S$ la somma totale, per un indice $i$ il prefisso vale $\sum_{j=1}^{i} A[j]$ e il suffisso $S - (\text{prefisso})$: si cerca il **primo** $i$ in cui il prefisso supera il suffisso. Il vincolo forte è la **memoria ausiliaria costante**: niente vettore dei prefissi: basta trascinare un accumulatore scalare. Poiché i numeri sono positivi, il prefisso cresce a ogni passo, quindi un tale $i$ esiste sempre (al più $i=n$, dove il suffisso è vuoto).
## Idea risolutiva
Con una prima scansione si calcola la somma totale $S$. Con una seconda scansione si tiene un solo accumulatore $\text{prefix}$: dopo il passo $i$ vale $\text{prefix}=\sum_{j=1}^{i}A[j]$, e il suffisso è $S-\text{prefix}$ **senza ricalcolo**. La condizione $\text{prefix} > S-\text{prefix}$ si riscrive come $2\cdot\text{prefix} > S$, che evita perfino la sottrazione. Al primo $i$ che la soddisfa si restituisce $i$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{prefissoMaggiore($A$, $n$) → intero}
\begin{algorithmic}
\State $S \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $S \gets S + A[j]$
\EndFor
\State $\text{prefix} \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $\text{prefix} \gets \text{prefix} + A[i]$
  \If{$2 \cdot \text{prefix} > S$}
    \State \Return $i$
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

Due sole variabili scalari ($S$ e $\text{prefix}$): nessun array ausiliario, memoria $O(1)$. La riscrittura $2\cdot\text{prefix} > S$ è algebricamente identica a $\text{prefix} > S - \text{prefix}$ (suffisso), ma non richiede di sottrarre né di ricalcolare la coda dell'array.
## Complessità
Due scansioni lineari indipendenti di $A$, ciascuna $O(n)$ con lavoro $O(1)$ per elemento (una somma, un confronto). Complessità **$O(n)$** tempo; memoria ausiliaria **$O(1)$** (le due variabili $S$ e $\text{prefix}$), come richiesto.
## Correttezza
La correttezza segue da un'invariante sul secondo ciclo.

> [!quote] Invariante — $\text{prefix}$ è la somma del prefisso
> All'inizio dell'iterazione $i$ del secondo ciclo, dopo l'aggiornamento $\text{prefix} \gets \text{prefix}+A[i]$, vale $\text{prefix}=\sum_{j=1}^{i}A[j]$.

**Dimostrazione.** Prima del ciclo $\text{prefix}=0=\sum_{j=1}^{0}A[j]$. Se all'inizio del passo $i$ vale $\text{prefix}=\sum_{j=1}^{i-1}A[j]$, dopo $\text{prefix}\gets\text{prefix}+A[i]$ vale $\sum_{j=1}^{i}A[j]$: l'invariante si mantiene. $\blacksquare$

Per l'invariante, al passo $i$ la condizione $2\cdot\text{prefix} > S$ equivale a $\sum_{j=1}^{i}A[j] > S-\sum_{j=1}^{i}A[j]=\sum_{j=i+1}^{n}A[j]$, cioè "prefisso $>$ suffisso". Scandendo $i=1,2,\dots$ e restituendo il **primo** $i$ che la soddisfa, l'algoritmo restituisce il minimo indice cercato. L'esistenza è garantita: essendo $A[j]>0$, per $i=n$ si ha $2S>S$ (poiché $S>0$), quindi il ciclo termina sempre con un `return`. $\blacksquare$

> [!warning] Non ricalcolare il suffisso
> Ricalcolare $\sum_{j=i+1}^{n}A[j]$ con un ciclo interno a ogni $i$ porterebbe a $O(n^2)$. La chiave è ottenerlo in $O(1)$ come $S-\text{prefix}$, avendo calcolato $S$ una volta sola; così basta un accumulatore e la memoria resta $O(1)$.
