---
tags:
  - algoritmi
---
# Struttura oracolo
Esercizio di progettazione con struttura oracolo (casistica [[Casistiche d'Esame Modulo I|struttura oracolo]]): array ausiliario costruito in $O(n)$ che abilita query in $O(1)$ o $O(\log n)$; ripasso: [[05 - Strutture Dati Elementari e Dizionari]], [[04 - Algoritmi di Ordinamento]]; checklist [[Piano Esame ASD - Modulo I]].

> [!info] Cos'è un "oracolo" e come si progetta
> Un oracolo separa nettamente due fasi: un **preprocessing** $O(n)$ che costruisce una volta sola una struttura ausiliaria, e poi **query** ripetute velocissime ($O(1)$ o $O(\log n)$) che leggono quella struttura senza ripercorrere l'input. La domanda guida è sempre: *qual è la più piccola informazione precalcolata che rende ogni query immediata?* — qui un array `next` (A), un vettore di prefix sum (B, C).
## Pattern A — array next[] (scansione right-to-left)
> [!question] Traccia — 20/02/2023
> Dato un array binario $A[1..n]$ con valori in $\{0,1\}$, progettare una struttura dati con preprocessing in $O(n)$ che risponda in $O(1)$ alle query della forma: dato $i$, restituire il minimo indice $j \ge i$ tale che $A[j]=1$, oppure $-1$ se non esiste.

**Idea.** Si alloca un array ausiliario $\text{next}[1..n]$ dove $\text{next}[i]$ memorizza il minimo $j \ge i$ con $A[j]=1$ (oppure $-1$ se non esiste). La scansione è **right-to-left**: si mantiene una variabile $\text{pross}$ inizializzata a $-1$; per ogni $i$ da $n$ a $1$, se $A[i]=1$ si aggiorna $\text{pross}=i$, poi si scrive $\text{next}[i]=\text{pross}$. Al termine la risposta alla query $\text{query}(i)$ è semplicemente $\text{next}[i]$.

> [!info] Le variabili e perché right-to-left
> - $\text{next}[i]$ = risposta precalcolata per l'indice $i$ (il primo $1$ da $i$ in poi).
> - $\text{pross}$ = posizione dell'**ultimo** $1$ già incontrato durante la scansione; parte da $-1$ ("nessuno ancora").
> - La scansione **deve** andare da destra a sinistra: quando si scrive $\text{next}[i]$ servono le informazioni *a destra* di $i$, che right-to-left sono già state viste. Da sinistra non si saprebbe ancora dov'è il prossimo $1$.

```pseudo
\begin{algorithm}
\caption{CostruisciNext($A$, $n$) → array}
\begin{algorithmic}
\State alloca $\text{next}[1..n]$
\State $\text{pross} \gets -1$
\For{$i \gets n$ downto $1$}
  \If{$A[i] = 1$}
    \State $\text{pross} \gets i$
  \EndIf
  \State $\text{next}[i] \gets \text{pross}$
\EndFor
\State \Return $\text{next}$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Query($\text{next}$, $i$) → intero}
\begin{algorithmic}
\State \Return $\text{next}[i]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** preprocessing $\Theta(n)$ (una scansione right-to-left); query $O(1)$ (accesso diretto all'array).
**Trappola:** costruire $\text{next}$ con scansione left-to-right è errato — quando si elabora $i$, i valori a destra non sono ancora stati visitati, quindi non è noto il minimo $j>i$ con $A[j]=1$. La scansione deve essere obbligatoriamente right-to-left.
## Pattern B — prefix sum con binary search
> [!question] Traccia — 24/09/2024
> Un conto bancario parte con liquidità iniziale $L$. Nei giorni $1,\dots,n$ la liquidità aumenta di $A[i] \ge 0$ euro. Progettare una struttura con preprocessing $O(n)$ che risponda in $O(\log n)$ alla query: data una soglia $T$, trovare il primo giorno $i$ in cui la liquidità cumulata supera $T$, oppure $-1$ se la soglia non viene mai raggiunta.

**Idea.** Si calcola il vettore dei prefix sum $P[0..n]$ con $P[0]=L$ e $P[i]=P[i-1]+A[i]$. Poiché $A[i]\ge 0$, $P$ è monotona non decrescente: si può quindi applicare una binary search per trovare il minimo $i$ tale che $P[i]>T$.

> [!info] Le variabili e l'invariante della binary search
> - $P[i]$ = liquidità cumulata **alla fine del giorno $i$** ($P[0]=L$ è il punto di partenza). Essendo gli incrementi $\ge 0$, $P$ è **monotona non decrescente**: è questa monotonia ad abilitare la ricerca binaria.
> - $lo,\ hi$ = estremi dell'intervallo di ricerca; l'invariante è "la risposta sta in $[lo, hi]$". Si restringe finché $lo = hi$, che è l'indice cercato.
> - Il controllo $P[n] \le T$ all'inizio gestisce il caso "soglia mai superata" → $-1$, evitando una ricerca che fallirebbe.

```pseudo
\begin{algorithm}
\caption{CostruisciPrefixSum($A$, $n$, $L$) → array}
\begin{algorithmic}
\State alloca $P[0..n]$
\State $P[0] \gets L$
\For{$i \gets 1$ to $n$}
  \State $P[i] \gets P[i-1] + A[i]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{PrimoCheSupera($P$, $n$, $T$) → intero}
\begin{algorithmic}
\If{$P[n] \le T$}
  \State \Return $-1$ \Comment{la soglia non viene mai raggiunta}
\EndIf
\State $lo \gets 0$, $hi \gets n$
\While{$lo < hi$}
  \State $mid \gets \lfloor (lo + hi) / 2 \rfloor$
  \If{$P[mid] > T$}
    \State $hi \gets mid$
  \Else
    \State $lo \gets mid + 1$
  \EndIf
\EndWhile
\State \Return $lo$
\end{algorithmic}
\end{algorithm}
```

> [!example] Esempio — $L = 0$, $A = [10, 10, 10]$, soglia $T = 15$
> Prefix sum: $P = [\,0,\ 10,\ 20,\ 30\,]$. $P[3]=30 > 15$, quindi non è $-1$.
> - $lo=0,\ hi=3$ → $mid=1$, $P[1]=10 > 15$? no → $lo=2$.
> - $lo=2,\ hi=3$ → $mid=2$, $P[2]=20 > 15$? sì → $hi=2$.
> - $lo=2=hi$ → si restituisce $2$.
>
> Il primo giorno con cumulata $> 15$ è il **giorno 2** (cumulata $20$); il giorno 1 era a $10$. ✓

**Complessità:** preprocessing $\Theta(n)$; query $O(\log n)$ (binary search su $P$ monotona).
**Trappola:** la binary search è valida **solo se $P$ è monotona**, condizione garantita dall'ipotesi $A[i]\ge 0$. Con valori negativi $P$ non sarebbe crescente e la binary search produrrebbe un risultato errato.
## Pattern C — conteggio per prefisso (query O(1) bidirezionale)
> [!question] Traccia — 09/09/2025
> Sia $V$ un vettore di $n$ bit. Progettare una struttura dati con costruzione $O(n)$ che risponda in $O(1)$ alle query $\text{query}(i,x)$: dato un indice $i$ e una direzione $x\in\{s,d\}$, restituire il numero di uni **strettamente a sinistra** di $i$ se $x=s$, il numero di uni **strettamente a destra** di $i$ se $x=d$.

**Idea.** Si precalcola il prefix sum dei bit, $P[0..n]$ con $P[0]=0$ e $P[i]=P[i-1]+V[i]$: $P[i]$ è il numero di uni in $V[1..i]$. Allora gli uni strettamente a sinistra di $i$ sono $P[i-1]$ e quelli strettamente a destra sono $P[n]-P[i]$. Entrambe le risposte sono una differenza di due celle dell'array, quindi $O(1)$.

> [!info] Perché $P[i-1]$ a sinistra e $P[n]-P[i]$ a destra
> - $P[i]$ = numero di uni in $V[1..i]$ (prefisso **incluso** $i$).
> - Uni **strettamente a sinistra** di $i$ = uni in $V[1..i-1]$ = $P[i-1]$ (escludo $i$ usando $i-1$).
> - Uni **strettamente a destra** di $i$ = (tutti gli uni) − (uni in $V[1..i]$) = $P[n] - P[i]$ (sottraendo fino a $i$ incluso, escludo $i$).
> - In entrambi i casi l'estremo scelto serve a **escludere** la posizione $i$: è il punto in cui è facile sbagliare di uno.

```pseudo
\begin{algorithm}
\caption{CostruisciPrefix($V$, $n$) → array}
\begin{algorithmic}
\State alloca $P[0..n]$; $P[0] \gets 0$
\For{$i \gets 1$ to $n$}
  \State $P[i] \gets P[i-1] + V[i]$
\EndFor
\State \Return $P$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Query($P$, $n$, $i$, $x$) → intero}
\begin{algorithmic}
\If{$x = s$}
  \State \Return $P[i-1]$ \Comment{uni in V[1..i-1]}
\Else
  \State \Return $P[n] - P[i]$ \Comment{uni in V[i+1..n]}
\EndIf
\end{algorithmic}
\end{algorithm}
```

**Complessità:** preprocessing $\Theta(n)$ (una scansione); query $O(1)$.
**Trappola:** le due query sono **strettamente** a sinistra/destra, quindi escludono $i$: si usa $P[i-1]$ (non $P[i]$) a sinistra e $P[n]-P[i]$ (non $P[n]-P[i-1]$) a destra. Sbagliare l'estremo include erroneamente il bit in posizione $i$.
