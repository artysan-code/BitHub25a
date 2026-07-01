---
tags:
  - algoritmi
  - grafi
---
# Multi-run Dijkstra
Esercizio di **modellazione**: un obiettivo che sembra accoppiare più punti si **fattorizza** in poche esecuzioni di Dijkstra (spesso una da una sorgente e una sul grafo trasposto $G^T$ per le distanze *verso* un nodo), seguite da una scansione che combina i risultati. Ripasso: [[10 - Cammini Minimi e Dijkstra#Algoritmo di Dijkstra|Dijkstra]], [[08 - Grafi e Visite#Rappresentazioni in memoria|grafo trasposto]].
## A · Cambio di mezzo in una stazione
> [!question] Traccia — 20/02/2023
> La città è un grafo orientato pesato $G=(V,E,w)$; siete in $s$ e dovete raggiungere $t$. In bici attraversare l'arco $e$ costa $w(e)$. In un insieme $X\subseteq V$ di stazioni si può affittare **un solo** mezzo: per $x\in X$ si conoscono il tempo di scambio $\tau_x$ e il fattore di speed-up $\sigma_x\leq 1$ (col mezzo preso in $x$, l'arco $e$ costa $\sigma_x\,w(e)$). Calcolare in tempo $O(m+n\log n)$ la strategia più veloce per arrivare a $t$.

La strategia con cambio in $x$ costa $d(s,x)$ (in bici) $+\ \tau_x$ (scambio) $+\ \sigma_x\,d(x,t)$ (col mezzo): poiché $\sigma_x$ scala **uniformemente** ogni arco, il tratto ottimo $x\to t$ col mezzo costa $\sigma_x$ volte la distanza in bici $d(x,t)$. Si può anche non affittare (solo bici, costo $d(s,t)$).
### Idea risolutiva
I tre termini si ottengono con **due** Dijkstra:

- $d(s,x)$ per ogni $x$: una Dijkstra da $s$ su $G$ → array $d_s$;

- $d(x,t)$ per ogni $x$: coincide con la distanza da $t$ a $x$ nel **trasposto** $G^T$ → una Dijkstra da $t$ su $G^T$ → array $d_t$ con $d_t[x]=d(x,t)$.

Poi una scansione di $X$ valuta $c(x)=d_s[x]+\tau_x+\sigma_x\,d_t[x]$ e tiene il minimo, confrontato con l'opzione "solo bici" $d_s[t]$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{minTempo($G$, $s$, $t$, $X$, $\tau$, $\sigma$, $w$) → reale}
\begin{algorithmic}
\State $d_s \gets$ \Call{Dijkstra}{$G$, $s$, $w$} \Comment{$d_s[v]=d(s,v)$}
\State $d_t \gets$ \Call{Dijkstra}{\Call{Trasposto}{$G$}, $t$, $w$} \Comment{$d_t[v]=d(v,t)$}
\State $\mathit{opt} \gets d_s[t]$ \Comment{opzione: solo bici}
\ForAll{$x \in X$}
  \State $c \gets d_s[x] + \tau[x] + \sigma[x] \cdot d_t[x]$
  \If{$c < \mathit{opt}$} \State $\mathit{opt} \gets c$ \EndIf
\EndFor
\State \Return $\mathit{opt}$
\end{algorithmic}
\end{algorithm}
```
### Complessità
Due Dijkstra $O(m+n\log n)$ (con heap), $O(n)$ per il trasposto, $O(|X|)\subseteq O(n)$ per la scansione. Totale **$O(m+n\log n)$**.
### Correttezza
Ogni strategia che cambia mezzo in $x$ è un cammino $s\rightsquigarrow x\rightsquigarrow t$; il suo costo minimo è $d(s,x)+\tau_x+\sigma_x\,d(x,t)$ perché il primo tratto usa i pesi $w$ e il secondo i pesi $\sigma_x w$ (e $\sigma_x$ costante fa sì che il cammino minimo scalato sia $\sigma_x\,d(x,t)$). Dijkstra calcola correttamente $d_s$ e, tramite $G^T$, $d_t[x]=d(x,t)$. Il minimo su $X$ (più l'opzione solo-bici $d_s[t]$) è il tempo ottimo. $\blacksquare$

> [!warning] $G^T$ per le distanze *verso* $t$
> $d(x,t)$ si ottiene con **una** Dijkstra da $t$ su $G^T$, non con $|X|$ Dijkstra separate (che darebbero $O(|X|(m+n\log n))$). Occorre trasporre **tutti** gli archi, non solo quelli delle stazioni.
## B · Incontro di Alice e Bob
> [!question] Traccia — 04/07/2023
> Grafo orientato $G=(V,E)$. Alice parte da $s_A$ con $\Delta_A$ monete di tipo A, Bob da $s_B$ con $\Delta_B$ di tipo B; l'arco $e$ costa $c^A_e$ ad Alice e $c^B_e$ a Bob. Trovare, se esiste, un nodo in cui i due possono incontrarsi rispettando i budget. Complessità $O(m+n\log n)$.
### Idea e pseudocodice
Due Dijkstra sullo **stesso** grafo con **funzioni di peso diverse**: da $s_A$ con $c^A$ → $d_A$, da $s_B$ con $c^B$ → $d_B$. Un nodo $v$ è valido se $d_A[v]\leq\Delta_A$ **e** $d_B[v]\leq\Delta_B$.
```pseudo
\begin{algorithm}
\caption{incontro($G$, $s_A$, $s_B$, $c^A$, $c^B$, $\Delta_A$, $\Delta_B$) → nodo oppure null}
\begin{algorithmic}
\State $d_A \gets$ \Call{Dijkstra}{$G$, $s_A$, $c^A$}; \; $d_B \gets$ \Call{Dijkstra}{$G$, $s_B$, $c^B$}
\ForAll{$v \in V$}
  \If{$d_A[v] \leq \Delta_A$ e $d_B[v] \leq \Delta_B$} \State \Return $v$ \EndIf
\EndFor
\State \Return null
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Due Dijkstra $O(m+n\log n)$ + scansione $O(n)$ → **$O(m+n\log n)$**. Il nodo d'incontro deve soddisfare **entrambi** i vincoli (non minimizzare la somma); nessuna trasposizione, perché ciascuno va *verso* il nodo d'incontro partendo dalla propria sorgente. $\blacksquare$
## C · Consegna con due regimi di traffico
> [!question] Traccia — 19/02/2024
> Grafo orientato $G$; casa in $s$, magazzini $M\subseteq V$, filiali $F\subseteq V$. Percorso $s\to m\to f\to s$ con $m\in M$, $f\in F$ a scelta: l'andata $s\to m\to f$ usa i pesi $w_1$, il ritorno $f\to s$ usa $w_2$. Minimizzare il tempo totale.
### Idea e pseudocodice
Obiettivo $\min_{m,f}[d_{w_1}(s,m)+d_{w_1}(m,f)+d_{w_2}(f,s)]$. Il termine centrale accoppia $m$ e $f$; si disaccoppia con una **super-sorgente $S$** con archi $S\to m$ di peso $A[m]=d_{w_1}(s,m)$: una Dijkstra da $S$ dà $g(f)=\min_m(A[m]+d_{w_1}(m,f))$.
```pseudo
\begin{algorithm}
\caption{consegnaOttima($G$, $s$, $M$, $F$, $w_1$, $w_2$) → reale}
\begin{algorithmic}
\State $A \gets$ \Call{Dijkstra}{$G$, $s$, $w_1$} \Comment{$A[m]=d_{w_1}(s,m)$}
\State costruisci $G^+$: aggiungi $S$ con archi $S\to m$ di peso $A[m]$ per ogni $m\in M$
\State $g \gets$ \Call{Dijkstra}{$G^+$, $S$, $w_1$} \Comment{$g[f]=\min_m(A[m]+d_{w_1}(m,f))$}
\State $B \gets$ \Call{Dijkstra}{\Call{Trasposto}{$G$}, $s$, $w_2$} \Comment{$B[f]=d_{w_2}(f,s)$}
\State $\mathit{opt} \gets +\infty$
\ForAll{$f \in F$} \If{$g[f]+B[f] < \mathit{opt}$} \State $\mathit{opt} \gets g[f]+B[f]$ \EndIf \EndFor
\State \Return $\mathit{opt}$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Tre Dijkstra $O(m+n\log n)$ + scansioni $O(n)$ → **$O(m+n\log n)$**. Gli archi $S\to m$ pesano $A[m]$ (distanza iniziale), non $0$, altrimenti si ignora il tratto $s\to m$; il ritorno usa $G^T$ con $w_2$ (distanza *da $f$ a casa* nel secondo regime). $\blacksquare$
## D · Taxi: massimo guadagno
> [!question] Traccia — 18/02/2025
> Grafo orientato $G$ con costo benzina $c(e)$; il taxi è in $x$. Ci sono $k$ richieste $(s_i,p_i)$: lo studente $i$ è in $s_i$ e paga $p_i$; tutti vanno in $t$. Si serve **un solo** studente (lo si raggiunge da $x$ e lo si porta a $t$). Calcolare il massimo guadagno $p_i-(d(x,s_i)+d(s_i,t))$.
### Idea e pseudocodice
Servire $i$ costa $d(x,s_i)+d(s_i,t)$: due Dijkstra bastano — da $x$ su $G$ (→ $d_x$) e da $t$ su $G^T$ (→ $d_t$ con $d_t[v]=d(v,t)$). Poi si massimizza $p_i-(d_x[s_i]+d_t[s_i])$.
```pseudo
\begin{algorithm}
\caption{maxGuadagno($G$, $x$, $t$, \text{richieste}) → reale}
\begin{algorithmic}
\State $d_x \gets$ \Call{Dijkstra}{$G$, $x$}; \; $d_t \gets$ \Call{Dijkstra}{\Call{Trasposto}{$G$}, $t$}
\State $\mathit{best} \gets -\infty$
\ForAll{richiesta $(s_i, p_i)$}
  \State $\mathit{g} \gets p_i - (d_x[s_i] + d_t[s_i])$
  \If{$\mathit{g} > \mathit{best}$} \State $\mathit{best} \gets \mathit{g}$ \EndIf
\EndFor
\State \Return $\mathit{best}$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Due Dijkstra $O(m+n\log n)$ + scansione $O(k)$ → **$O(m+n\log n+k)$**. $d(s_i,t)$ si ottiene con **una** Dijkstra da $t$ su $G^T$, non con $k$ separate; è una massimizzazione del guadagno (non un cammino minimo puro): se tutti i guadagni sono negativi si restituisce il massimo comunque. $\blacksquare$
