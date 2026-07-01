---
tags:
  - algoritmi
  - strutture-dati
---
# Struttura oracolo
Esercizio di **progettazione**: un **oracolo** separa un **preprocessing** $O(n)$, che costruisce una struttura ausiliaria una volta sola, da **query** ripetute velocissime ($O(1)$ o $O(\log n)$) che leggono quella struttura senza ripercorrere l'input. La domanda guida è: *qual è la più piccola informazione precalcolata che rende ogni query immediata?* Ripasso: [[05 - Strutture Dati Elementari e Dizionari#Rappresentazioni Indicizzate e Collegate|array indicizzati]], [[06 - Alberi di Ricerca BST e AVL#Proprietà chiave: visita in ordine simmetrico|ricerca binaria su ordinato]].
## A · Array next[] (scansione right-to-left)
> [!question] Traccia — 20/02/2023
> Sia $A[1..n]$ un vettore di bit ($A[i]\in\{0,1\}$). Progettare un oracolo costruibile in $O(n)$ che risponda in $O(1)$ a domande $q(i)$: dato $i$, restituire il più piccolo indice $j \geq i$ con $A[j]=1$, oppure $-1$ se non esiste. Fornire lo pseudocodice di costruzione e di query.

La query chiede, per ogni $i$, "il primo $1$ da $i$ in poi". Precalcolando la risposta per **ogni** $i$ in un array, ogni query diventa un accesso diretto.
### Idea risolutiva
Si alloca $\text{next}[1..n]$ con $\text{next}[i]$ = il minimo $j\geq i$ con $A[j]=1$ (o $-1$). La scansione **deve** andare **right-to-left**: per scrivere $\text{next}[i]$ serve l'informazione *a destra* di $i$, che così è già stata vista. Si mantiene $\text{pross}$ = ultimo indice con un $1$ incontrato, inizializzato a $-1$.
### Pseudocodici
```pseudo
\begin{algorithm}
\caption{costruisciOracolo($A$, $n$) → array next}
\begin{algorithmic}
\State $\text{pross} \gets -1$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 1$} \State $\text{pross} \gets i$ \EndIf
  \State $\text{next}[i] \gets \text{pross}$
\EndFor
\State \Return $\text{next}$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{query($\text{next}$, $i$) → intero}
\begin{algorithmic}
\State \Return $\text{next}[i]$
\end{algorithmic}
\end{algorithm}
```
### Complessità
Preprocessing $\Theta(n)$ (una scansione), query $O(1)$ (accesso diretto). Spazio $\Theta(n)$.
### Correttezza
> [!quote] Invariante — $\text{pross}$ è il prossimo $1$
> Dopo aver elaborato l'indice $i$ nella scansione right-to-left, $\text{pross}$ è il minimo $j \geq i$ con $A[j]=1$ (o $-1$ se non esiste), e viene copiato in $\text{next}[i]$.

**Dimostrazione.** All'inizio (nessun indice $> n$) $\text{pross}=-1$. Elaborando $i$: se $A[i]=1$ allora il minimo $j\geq i$ con $A[j]=1$ è $i$, e $\text{pross}\gets i$; altrimenti è il minimo $j\geq i+1$ con $A[j]=1$, che per l'iterazione precedente è già in $\text{pross}$. In entrambi i casi $\text{next}[i]=\text{pross}$ è corretto. $\blacksquare$

> [!warning] La direzione della scansione
> Costruire $\text{next}$ left-to-right è errato: elaborando $i$ i valori a destra non sono ancora stati visti. La scansione dev'essere right-to-left.
## B · Prefix sum + ricerca binaria
> [!question] Traccia — 24/09/2024
> Un'azienda ha capitale iniziale $L$; nel giorno $i$ incassa $A[i]\geq 0$ euro. Progettare una struttura, con preprocessing $o(n)$ per query, che risponda a $\text{query}(x)$: il **primo giorno** in cui la liquidità è **almeno $x$**, se esiste, altrimenti $-1$. Fornire i due pseudocodici e analizzarne le complessità.
### Idea risolutiva
La liquidità a fine giorno $i$ è $P[i]=L+\sum_{j=1}^{i}A[j]$, con $P[0]=L$. Poiché $A[i]\geq 0$, $P$ è **monotona non decrescente**: si può quindi trovare il minimo $i$ con $P[i]\geq x$ con una **ricerca binaria** su $P$ ($O(\log n)$, dunque $o(n)$). Se $P[n]<x$ la soglia non è mai raggiunta → $-1$.
### Pseudocodici
```pseudo
\begin{algorithm}
\caption{costruisciPrefix($A$, $n$, $L$) → array P}
\begin{algorithmic}
\State $P[0] \gets L$
\For{$i \gets 1$ \To $n$}
  \State $P[i] \gets P[i-1] + A[i]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{query($P$, $n$, $x$) → intero}
\begin{algorithmic}
\If{$P[n] < x$} \State \Return $-1$ \Comment{soglia mai raggiunta} \EndIf
\State $lo \gets 0$; $hi \gets n$
\While{$lo < hi$}
  \State $mid \gets \lfloor (lo + hi)/2 \rfloor$
  \If{$P[mid] \geq x$} \State $hi \gets mid$
  \Else \State $lo \gets mid + 1$ \EndIf
\EndWhile
\State \Return $lo$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Preprocessing $\Theta(n)$; query $O(\log n)=o(n)$. La ricerca binaria è valida **perché $P$ è monotona** (garantito da $A[i]\geq 0$): mantiene l'invariante "la risposta sta in $[lo,hi]$" restringendo l'intervallo finché $lo=hi$, il minimo indice con $P[i]\geq x$. Il caso $P[n]<x$ (liquidità finale sotto soglia) è gestito a parte con $-1$. $\blacksquare$

> [!warning] Serve la monotonia
> Con incassi eventualmente negativi $P$ non sarebbe crescente e la ricerca binaria darebbe un risultato errato: la monotonia è l'ipotesi che abilita l'oracolo.
## C · Conteggio per prefisso (query O(1) bidirezionale)
> [!question] Traccia — 09/09/2025
> Sia $V$ un vettore di $n$ bit. Progettare una struttura, costruzione $O(n)$, che risponda in $O(1)$ a $\text{query}(i,x)$: con $x\in\{s,d\}$, il numero di uni **strettamente a sinistra** di $i$ se $x=s$, **strettamente a destra** di $i$ se $x=d$.
### Idea risolutiva
Si precalcola il prefix sum dei bit, $P[i]=$ numero di uni in $V[1..i]$ (con $P[0]=0$). Allora gli uni strettamente a sinistra di $i$ sono $P[i-1]$ e quelli strettamente a destra sono $P[n]-P[i]$: entrambe differenze di due celle → $O(1)$.
### Pseudocodici
```pseudo
\begin{algorithm}
\caption{costruisciPrefix($V$, $n$) → array P}
\begin{algorithmic}
\State $P[0] \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $P[i] \gets P[i-1] + V[i]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{query($P$, $n$, $i$, $x$) → intero}
\begin{algorithmic}
\If{$x = s$} \State \Return $P[i-1]$ \Comment{uni in V[1..i-1]}
\Else \State \Return $P[n] - P[i]$ \Comment{uni in V[i+1..n]} \EndIf
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Preprocessing $\Theta(n)$, query $O(1)$. Correttezza: $P[i]$ = uni in $V[1..i]$; gli uni **strettamente** a sinistra di $i$ sono quelli in $V[1..i-1]=P[i-1]$, quelli strettamente a destra sono (totali) $-$ (fino a $i$ incluso) $=P[n]-P[i]$. In entrambi i casi l'estremo scelto **esclude** la posizione $i$. $\blacksquare$

> [!warning] L'errore di uno
> "Strettamente" impone di escludere $i$: si usa $P[i-1]$ (non $P[i]$) a sinistra e $P[n]-P[i]$ (non $P[n]-P[i-1]$) a destra. Sbagliare l'estremo include il bit in posizione $i$.
