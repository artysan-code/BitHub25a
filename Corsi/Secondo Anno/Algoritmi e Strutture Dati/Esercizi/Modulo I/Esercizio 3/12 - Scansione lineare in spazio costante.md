---
tags:
  - algoritmi
  - strutture-dati
---
# Scansione lineare in spazio costante
Esercizio di **modellazione**: si riscrive un suffisso come *totale meno prefisso*, così da rispondere in una scansione con **due soli scalari** — $O(n)$ tempo, $O(1)$ spazio. Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|prefix sum]].
## Traccia
> [!question] Traccia — 30/01/2023
> Dati due vettori $A[1..n]$ e $B[1..n]$ di numeri positivi, calcolare il più piccolo indice $i\in\{1,\dots,n\}$ tale che $\sum_{k=1}^{i}A[k] > \sum_{k=i}^{n}B[k]$. L'algoritmo deve avere complessità $O(n)$; il punteggio pieno richiede anche **memoria ausiliaria costante**.

Si confronta il prefisso di $A$ (fino a $i$ incluso) con il suffisso di $B$ (da $i$ incluso). Ricalcolare il suffisso di $B$ da capo a ogni $i$ costerebbe $O(n^2)$; il vincolo forte è la memoria $O(1)$, che vieta di precalcolare un array di suffissi.
## Idea risolutiva
Il suffisso si scompone tramite la somma totale di $B$, precalcolata una volta:
$$\sum_{k=i}^{n}B[k] = \underbrace{\sum_{k=1}^{n}B[k]}_{\text{total\_B}} - \underbrace{\sum_{k=1}^{i-1}B[k]}_{\text{prefB}}.$$
Una prima passata calcola $\text{total\_B}$ in $O(n)$, $O(1)$ spazio. Nella seconda passata si tengono due scalari: $\text{prefA}=\sum_{k=1}^{i}A[k]$ (aggiornato **prima** del test, con $A[i]$) e $\text{prefB}=\sum_{k=1}^{i-1}B[k]$ (aggiornato **dopo** il test, con $B[i]$). Il confronto diventa $\text{prefA} > \text{total\_B}-\text{prefB}$ in $O(1)$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{primoIndice($A$, $B$, $n$) → intero}
\begin{algorithmic}
\State $\text{total\_B} \gets 0$
\For{$j \gets 1$ \To $n$} \State $\text{total\_B} \gets \text{total\_B} + B[j]$ \EndFor
\State $\text{prefA} \gets 0$; $\text{prefB} \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $\text{prefA} \gets \text{prefA} + A[i]$
  \If{$\text{prefA} > \text{total\_B} - \text{prefB}$}
    \State \Return $i$
  \EndIf
  \State $\text{prefB} \gets \text{prefB} + B[i]$ \Comment{aggiornato dopo il test: resta $\sum_{k=1}^{i-1}B$ al confronto}
\EndFor
\State \Return $-1$ \Comment{nessun indice soddisfa la condizione}
\end{algorithmic}
\end{algorithm}
```
## Complessità
Due passate lineari, lavoro $O(1)$ per elemento: **$O(n)$** tempo; memoria ausiliaria **$O(1)$** (tre scalari $\text{total\_B}$, $\text{prefA}$, $\text{prefB}$), che è il punteggio pieno.
## Correttezza
> [!quote] Invariante — i due prefissi al momento del test
> All'iterazione $i$, dopo l'aggiornamento di $\text{prefA}$ e prima di quello di $\text{prefB}$, vale $\text{prefA}=\sum_{k=1}^{i}A[k]$ e $\text{prefB}=\sum_{k=1}^{i-1}B[k]$.

**Dimostrazione.** $\text{prefA}$ è aggiunto $A[i]$ all'inizio del passo $i$, quindi accumula $A[1..i]$. $\text{prefB}$ viene aggiornato con $B[i]$ solo **in coda** al passo $i$: al momento del test contiene ancora $B[1..i-1]$. $\blacksquare$

Per l'invariante, $\text{total\_B}-\text{prefB}=\sum_{k=1}^{n}B-\sum_{k=1}^{i-1}B=\sum_{k=i}^{n}B[k]$, quindi il test $\text{prefA}>\text{total\_B}-\text{prefB}$ è esattamente la condizione della traccia. Scandendo $i$ crescente e restituendo il primo che la soddisfa, si ottiene il minimo indice. $\blacksquare$

> [!warning] L'ordine di aggiornamento di prefB
> $\sum_{k=i}^{n}B[k]$ **include** $B[i]$: quindi $\text{prefB}$ deve valere $\sum_{k=1}^{i-1}B[k]$ al confronto, cioè va aggiornato **dopo** il test. Aggiornarlo prima includerebbe $B[i]$ nel prefisso e confronterebbe con $\sum_{k=i+1}^{n}B[k]$, saltando un elemento.
