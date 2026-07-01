---
tags:
  - algoritmi
  - strutture-dati
---
# Precalcolo di array ausiliari
Esercizio di **progettazione** su array: quando la proprietà di ogni posizione dipende da una **scansione direzionale** (run, distanza, occorrenza), si precalcolano uno o più array di supporto con una **ricorrenza locale** (il valore in $i$ deriva dal vicino), poi una passata finale combina. Trasforma un approccio ingenuo $O(n^2)$ in $O(n)$ (o $O(n+k)$ se si indicizza per valore). Ripasso: [[04 - Algoritmi di Ordinamento#Applicazione: Oracolo per Range Counting|somme/array di supporto]].
## A · Run crescenti e decrescenti (left[] e right[])
> [!question] Traccia — 25/07/2023
> Sia $A[1..n]$ un vettore di $n$ numeri. Un **$k$-picco** in $A$ è un indice $m \in \{k+1, \dots, n-k\}$ tale che la sequenza $A[m-k..m]$ è strettamente crescente e la sequenza $A[m..m+k]$ è strettamente decrescente. Progettare un algoritmo che, dato $A$, calcola il più grande valore di $k$ per cui $A$ contiene un $k$-picco. Complessità $O(n)$.

Un $k$-picco in $m$ chiede $k$ **salite** consecutive che finiscono in $m$ (gli elementi $A[m-k..m]$, cioè $k+1$ elementi in salita) e $k$ **discese** consecutive che partono da $m$. Vogliamo il massimo $k$ per cui *qualche* $m$ è un $k$-picco.
### Idea risolutiva
Con due scansioni si costruiscono:

- $\text{left}[m]$ = lunghezza (in numero di elementi) della massima run **strettamente crescente** di elementi consecutivi che **termina in** $m$; scansione sinistra → destra;

- $\text{right}[m]$ = lunghezza della massima run **strettamente decrescente** che **parte da** $m$; scansione destra → sinistra.

$m$ è un $k$-picco se e solo se ha almeno $k$ salite a sinistra ($\text{left}[m] \geq k+1$) e $k$ discese a destra ($\text{right}[m] \geq k+1$); il massimo $k$ ammesso da $m$ è dunque $\min(\text{left}[m], \text{right}[m]) - 1$ (il $-1$ perché $m$ è contato in entrambe le run). La risposta è il massimo su tutti gli $m$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{kPiccoMassimo($A$, $n$) → intero}
\begin{algorithmic}
\State $\text{left}[1] \gets 1$
\For{$i \gets 2$ \To $n$}
  \If{$A[i] > A[i-1]$} \State $\text{left}[i] \gets \text{left}[i-1] + 1$
  \Else \State $\text{left}[i] \gets 1$ \EndIf
\EndFor
\State $\text{right}[n] \gets 1$
\For{$i \gets n-1$ downto $1$}
  \If{$A[i] > A[i+1]$} \State $\text{right}[i] \gets \text{right}[i+1] + 1$
  \Else \State $\text{right}[i] \gets 1$ \EndIf
\EndFor
\State $\text{best} \gets 0$
\For{$m \gets 1$ \To $n$}
  \State $\text{best} \gets \max(\text{best},\; \min(\text{left}[m], \text{right}[m]) - 1)$
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```

Le prime due `for` riempiono gli array con la ricorrenza locale (ogni cella dal vicino, in $O(1)$); la terza cerca il massimo.
### Complessità
Tre scansioni lineari, lavoro $O(1)$ per elemento: tempo **$\Theta(n)$**; spazio $\Theta(n)$ per $\text{left}$ e $\text{right}$.
### Correttezza
> [!quote] Invariante — $\text{left}[i]$ è la run crescente che termina in $i$
> Dopo la prima `for`, $\text{left}[i]$ è il numero di elementi della massima sequenza strettamente crescente di indici consecutivi che termina in $i$ (simmetricamente $\text{right}[i]$ per le decrescenti che partono da $i$).

**Dimostrazione** (induzione su $i$). $\text{left}[1]=1$ (un solo elemento). Se $A[i]>A[i-1]$ la run crescente che termina in $i-1$ si estende di uno: $\text{left}[i]=\text{left}[i-1]+1$; altrimenti la salita si interrompe e riparte da $i$: $\text{left}[i]=1$. $\blacksquare$

Per l'invariante, $m$ ammette esattamente $\min(\text{left}[m],\text{right}[m])-1$ salite-e-discese simmetriche, cioè è un $k$-picco per ogni $k \leq \min(\text{left}[m],\text{right}[m])-1$ e per nessun $k$ maggiore. Il massimo globale su $m$ è quindi il più grande $k$ per cui esiste un $k$-picco. $\blacksquare$

> [!example] Esempio — $A = [2, 5, 8, 6, 1]$
> | | $2$ | $5$ | $8$ | $6$ | $1$ |
> |:--|:-:|:-:|:-:|:-:|:-:|
> | $\text{left}$ | $1$ | $2$ | $3$ | $1$ | $1$ |
> | $\text{right}$ | $1$ | $1$ | $3$ | $2$ | $1$ |
> | $\min-1$ | $0$ | $0$ | $\mathbf{2}$ | $0$ | $0$ |
>
> Vince $m=3$ (valore $8$): salita $2,5,8$ e discesa $8,6,1$ → $k=2$.
## B · Vicino più prossimo (prev[] e next[])
> [!question] Traccia — 16/07/2024
> Un'autostrada è lunga $n$ chilometri ($1..n$); $A[i]=1$ se al km $i$ c'è una colonnina SOS, $0$ altrimenti. Calcolare un vettore $B$ tale che $B[i]$ = il chilometro della colonnina SOS **più vicina** al km $i$, per ogni $i$. Complessità $O(n)$.
### Idea risolutiva
Si calcolano due array: $\text{prev}[i]$ = km dell'ultima colonnina vista scandendo da **sinistra** fino a $i$ (o $i$ stesso se $A[i]=1$); $\text{next}[i]$ = il simmetrico da **destra**. Poi una passata sceglie per ogni $i$ il più vicino confrontando le distanze $i-\text{prev}[i]$ e $\text{next}[i]-i$. Sentinelle $-\infty$ / $+\infty$ rendono la distanza dal lato mancante sempre peggiore, così il confronto sceglie da solo il lato esistente senza casi speciali.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{colonninaPiuVicina($A$, $n$) → array B}
\begin{algorithmic}
\State $ult \gets -\infty$
\For{$i \gets 1$ \To $n$}
  \If{$A[i] = 1$} \State $ult \gets i$ \EndIf
  \State $\text{prev}[i] \gets ult$
\EndFor
\State $pross \gets +\infty$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 1$} \State $pross \gets i$ \EndIf
  \State $\text{next}[i] \gets pross$
\EndFor
\For{$i \gets 1$ \To $n$}
  \If{$i - \text{prev}[i] \leq \text{next}[i] - i$} \State $B[i] \gets \text{prev}[i]$
  \Else \State $B[i] \gets \text{next}[i]$ \EndIf
\EndFor
\State \Return $B$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Tre scansioni lineari → **$\Theta(n)$** tempo, $\Theta(n)$ spazio. Invariante: durante la prima `for`, $ult$ è l'indice dell'ultima colonnina vista fino a $i$, quindi $\text{prev}[i]$ è la colonnina più vicina a sinistra (o $i$ stesso); simmetrico per $\text{next}$. Il confronto delle due distanze restituisce quindi la colonnina globalmente più vicina. $\blacksquare$

> [!warning] Le sentinelle
> Inizializzare $ult=-\infty$, $pross=+\infty$ così che la distanza dal lato mancante risulti $+\infty$; senza sentinella il primo/ultimo tratto privo di colonnine a un lato darebbe un indice indefinito. A parità di distanza qui si privilegia il lato sinistro.
## C · Indicizzazione per valore (first[] e last[])
> [!question] Traccia — 18/02/2025
> $n$ segmenti verticali su una retta, a distanza $1$; il segmento $i$ ha altezza intera $h_i \in [1,k]$, in $H[1..n]$. Se $h_i = h_j = h$ si forma un rettangolo di area $h\cdot(j-i)$. Trovare l'area massima ottenibile. Complessità $O(n+k)$.
### Idea risolutiva
Per un'altezza fissata $h$ il rettangolo più ampio usa la **prima** e l'**ultima** occorrenza di $h$: area $h\cdot(\text{last}[h]-\text{first}[h])$. Si allocano due array **indicizzati per valore** $\text{first}[1..k]$ e $\text{last}[1..k]$, riempiti con una sola scansione di $H$; la risposta è il massimo su $h$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{rettangoloMassimo($H$, $n$, $k$) → intero}
\begin{algorithmic}
\For{$h \gets 1$ \To $k$}
  \State $\text{first}[h] \gets 0$; $\text{last}[h] \gets 0$ \Comment{0 = altezza non ancora vista}
\EndFor
\For{$i \gets 1$ \To $n$}
  \State $h \gets H[i]$
  \If{$\text{first}[h] = 0$} \State $\text{first}[h] \gets i$ \EndIf
  \State $\text{last}[h] \gets i$
\EndFor
\State $\text{best} \gets 0$
\For{$h \gets 1$ \To $k$}
  \If{$\text{first}[h] \neq 0$}
    \State $\text{best} \gets \max(\text{best},\; h \cdot (\text{last}[h] - \text{first}[h]))$
  \EndIf
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Inizializzazione $O(k)$, scansione di $H$ $O(n)$, passata finale $O(k)$: tempo **$O(n+k)$**, spazio $O(k)$. Correttezza: per un'altezza $h$ l'area cresce con la larghezza $j-i$, massima fra prima e ultima occorrenza; se $h$ compare una sola volta $\text{first}[h]=\text{last}[h]$ → area $0$ (mai vincente), quindi il vincolo "almeno due occorrenze" si gestisce da sé. Il massimo su $h$ è l'area cercata. $\blacksquare$

> [!example] Esempio — $H = [3, 1, 3, 2, 1]$, $k = 3$
> | altezza $h$ | $1$ | $2$ | $3$ |
> |:--|:-:|:-:|:-:|
> | $\text{first}[h]$ | $2$ | $4$ | $1$ |
> | $\text{last}[h]$ | $5$ | $4$ | $3$ |
> | area | $3$ | $0$ | $\mathbf{6}$ |
>
> Vince $h=3$: prima in $1$, ultima in $3$ → alto $3$, largo $2$, **area $6$**.

> [!warning] Indice = valore, non posizione
> Indicizzare $\text{first}/\text{last}$ **per altezza** ($1..k$) e non per posizione è ciò che dà $O(n+k)$ invece di confrontare tutte le coppie ($O(n^2)$); le occorrenze intermedie di un'altezza sono irrilevanti.
