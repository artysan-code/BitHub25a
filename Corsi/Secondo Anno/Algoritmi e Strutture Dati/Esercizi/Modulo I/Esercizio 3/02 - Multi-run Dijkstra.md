---
tags:
  - algoritmi
---
# Multi-run Dijkstra
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 3 (Modellazione)]] di ASD. Ripasso: [[10 - Cammini Minimi e Dijkstra]], [[08 - Grafi e Visite]], [[07 - Code con Priorità e Heap]], [[05 - Strutture Dati Elementari e Dizionari]]. Checklist: [[Piano Esame ASD - Modulo I]].
## Svolgimento — esame 20/02/2023
> [!question] Traccia — 20/02/2023
> Dato un grafo orientato pesato $G=(V,E,w)$ con $w:E\to\mathbb{R}_{\ge 0}$, un nodo sorgente $s$, un nodo destinazione $t$ e un insieme $X\subseteq V$ di stazioni di noleggio, si vuole trovare il cammino di costo minimo da $s$ a $t$ che prevede un cambio di mezzo in esattamente una stazione $x\in X$: il tratto $s\to x$ è percorso in bici (costi su $G$), poi si noleggia un veicolo alla stazione $x$ con costo fisso $\tau_x\ge 0$ e costo proporzionale $\sigma_x>0$ per unità di distanza; il tratto $x\to t$ con il veicolo noleggiato ha quindi costo $\sigma_x\cdot d(x,t)$. Il costo totale passando per $x$ è
> $$c(x)=d(s,x)+\tau_x+\sigma_x\cdot d(x,t).$$
> Trovare $\min_{x\in X}\,c(x)$ in tempo $O(m+n\log n)$.

**Modellazione.** L'obiettivo si fattorizza in tre termini indipendenti:
- $d(s,x)$ per ogni $x\in X$: si ottiene con una singola esecuzione di Dijkstra su $G$ dalla sorgente $s$; l'array $d_s[\cdot]$ contiene le distanze da $s$ verso tutti i nodi.
- $d(x,t)$ per ogni $x\in X$: la distanza da $x$ a $t$ in $G$ coincide con la distanza da $t$ a $x$ nel grafo trasposto $G^T$ (stessi pesi, archi invertiti). Una singola esecuzione di Dijkstra su $G^T$ dalla sorgente $t$ restituisce l'array $d_t[\cdot]$ con $d_t[x]=d_{G^T}(t,x)=d_G(x,t)$.
- $\tau_x$ e $\sigma_x$: dati di input per ogni stazione $x\in X$.

Dopo le due esecuzioni di Dijkstra, una scansione lineare su $X$ calcola $c(x)$ e tiene traccia del minimo. Non occorre costruire alcun grafo aumentato: la struttura del problema si riduce a valutare una formula chiusa su ciascun candidato $x\in X$.

```pseudo
\begin{algorithm}
\caption{MinCostoNoleggio($G$, $s$, $t$, $X$, $\tau$, $\sigma$) → reale}
\begin{algorithmic}
\State $d_s \gets$ \Call{Dijkstra}{$G$, $s$} \Comment{$d_s[v] = d_G(s,v)$ per ogni $v$}
\State $G^T \gets$ \Call{Trasposto}{$G$}
\State $d_t \gets$ \Call{Dijkstra}{$G^T$, $t$} \Comment{$d_t[v] = d_G(v,t)$ per ogni $v$}
\State $\text{opt} \gets +\infty$
\For{ogni $x \in X$}
  \State $c \gets d_s[x] + \tau[x] + \sigma[x] \cdot d_t[x]$
  \If{$c < \text{opt}$}
    \State $\text{opt} \gets c$
  \EndIf
\EndFor
\State \Return $\text{opt}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O((n+m)\log n)$ per ciascuna delle due esecuzioni di Dijkstra (con heap binario) su $G$ e $G^T$, entrambi con $n$ nodi e $m$ archi; $O(n)$ per costruire $G^T$; $O(|X|)\subseteq O(n)$ per la scansione finale. Totale: $O(m+n\log n)$.
**Trappola:** $d_t[x]$ si calcola con Dijkstra da $t$ su $G^T$, non con $|X|$ esecuzioni separate di Dijkstra su $G$ — quello porterebbe a $O(|X|\cdot(m+n\log n))$. Occorre trasporre TUTTI gli archi di $G$, non solo quelli incidenti ai nodi di $X$. Nel caso di Dijkstra multi-sorgente (variante con più stazioni di partenza aggregate), ogni sorgente $m\in X$ va inizializzata con la sua distanza $d_s[m]$ nella coda con priorità, non con $0$: inizializzare con $0$ equivale a ignorare il tratto $s\to m$ e produce distanze errate.
## Variante — incontro di Alice e Bob (04/07/2023)
> [!question] Traccia — 04/07/2023
> Sia $G=(V,E)$ un grafo orientato con $n$ nodi e $m$ archi. Alice parte da $s_A$ con $\Delta_A$ monete di tipo A, Bob da $s_B$ con $\Delta_B$ monete di tipo B. Ogni arco $e$ ha due costi $c^A_e, c^B_e$ (monete che rispettivamente Alice e Bob spendono per attraversarlo). Trovare, se esiste, un nodo in cui Alice e Bob possono incontrarsi rispettando i rispettivi budget. Complessità $O(m+n\log n)$.

**Modellazione.** I due budget sono indipendenti e si valutano sullo stesso grafo orientato con due funzioni di peso diverse:
- Dijkstra da $s_A$ con pesi $c^A$ → $d_A[v]$ = costo minimo per Alice di raggiungere $v$;
- Dijkstra da $s_B$ con pesi $c^B$ → $d_B[v]$ = costo minimo per Bob di raggiungere $v$.

Un nodo $v$ è un punto d'incontro valido se e solo se $d_A[v]\le\Delta_A$ **e** $d_B[v]\le\Delta_B$. Una scansione lineare su $V$ trova un tale nodo (o riporta che non esiste).

```pseudo
\begin{algorithm}
\caption{Incontro($G$, $s_A$, $s_B$, $c^A$, $c^B$, $\Delta_A$, $\Delta_B$) → nodo oppure null}
\begin{algorithmic}
\State $d_A \gets$ \Call{Dijkstra}{$G$, $s_A$, $c^A$} \Comment{pesi di tipo A}
\State $d_B \gets$ \Call{Dijkstra}{$G$, $s_B$, $c^B$} \Comment{pesi di tipo B}
\For{ogni $v \in V$}
  \If{$d_A[v] \le \Delta_A$ e $d_B[v] \le \Delta_B$}
    \State \Return $v$
  \EndIf
\EndFor
\State \Return null
\end{algorithmic}
\end{algorithm}
```

**Complessità:** due esecuzioni di Dijkstra $O(m+n\log n)$ ciascuna più una scansione $O(n)$; totale $O(m+n\log n)$.
**Trappola:** i due cammini usano **funzioni di peso distinte** ($c^A$ e $c^B$) sullo stesso grafo orientato; il nodo d'incontro deve soddisfare **entrambi** i vincoli di budget, non minimizzare la somma $d_A[v]+d_B[v]$; entrambe le distanze partono dalle rispettive sorgenti (nessuna trasposizione: ciascuno va *verso* il nodo d'incontro).
## Variante — consegna con due regimi di traffico (19/02/2024)
> [!question] Traccia — 19/02/2024
> Sia $G=(V,E)$ un grafo orientato; casa nel nodo $s$, magazzini $M\subseteq V$, filiali $F\subseteq V$. Si parte da $s$, si passa per un magazzino $m\in M$ (a scelta), poi per una filiale $f\in F$ (a scelta), infine si torna a $s$. L'andata $s\to m\to f$ usa i pesi del primo regime $w_1$; il ritorno $f\to s$ usa il secondo regime $w_2$. Minimizzare il tempo totale.

**Modellazione.** L'obiettivo è $\min_{m\in M,\,f\in F}\big[d_{w_1}(s,m)+d_{w_1}(m,f)+d_{w_2}(f,s)\big]$. Il termine centrale $d_{w_1}(m,f)$ accoppia $m$ e $f$, ma si disaccoppia con il trucco della **super-sorgente con distanze iniziali**:
1. Dijkstra da $s$ in $w_1$ → $A[m]=d_{w_1}(s,m)$ per ogni magazzino.
2. Si aggiunge una super-sorgente $S$ con archi $S\to m$ di peso $A[m]$ per ogni $m\in M$; una sola Dijkstra da $S$ in $w_1$ dà $g(f)=\min_{m\in M}\big(A[m]+d_{w_1}(m,f)\big)$, il miglior costo di andata che tocca un magazzino e arriva a $f$.
3. Dijkstra da $s$ su $G^T$ in $w_2$ → $B[f]=d_{w_2}(f,s)$ (distanze *verso* casa nel secondo regime).
4. Risposta: $\min_{f\in F}\big(g(f)+B[f]\big)$.

```pseudo
\begin{algorithm}
\caption{ConsegnaOttima($G$, $s$, $M$, $F$, $w_1$, $w_2$) → reale}
\begin{algorithmic}
\State $A \gets$ \Call{Dijkstra}{$G$, $s$, $w_1$} \Comment{$A[m]=d_{w_1}(s,m)$}
\State costruisci $G^+$ aggiungendo $S$ e archi $S\to m$ di peso $A[m]$ per ogni $m\in M$
\State $g \gets$ \Call{Dijkstra}{$G^+$, $S$, $w_1$} \Comment{$g(f)=\min_{m}(A[m]+d_{w_1}(m,f))$}
\State $B \gets$ \Call{Dijkstra}{$G^T$, $s$, $w_2$} \Comment{$B[f]=d_{w_2}(f,s)$}
\State $\text{opt} \gets +\infty$
\For{ogni $f \in F$}
  \If{$g[f] + B[f] < \text{opt}$}
    \State $\text{opt} \gets g[f] + B[f]$
  \EndIf
\EndFor
\State \Return $\text{opt}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** tre esecuzioni di Dijkstra $O(m+n\log n)$ più scansioni $O(n)$; totale $O(m+n\log n)$.
**Trappola:** gli archi $S\to m$ vanno pesati con $A[m]=d_{w_1}(s,m)$ (distanza iniziale), non con $0$ — altrimenti si ignora il tratto $s\to m$; il ritorno usa $G^T$ con $w_2$ perché serve la distanza *da $f$ a casa* nel secondo regime; il tratto centrale $m\to f$ non si separa in modo indipendente da $m$ ed $f$, da qui la super-sorgente.
## Variante — taxi: massimo guadagno (18/02/2025)
> [!question] Traccia — 18/02/2025
> Sia $G=(V,E)$ un grafo orientato con costo $c(e)$ su ogni arco (benzina). Il taxi è nel nodo $x$. Ci sono $k$ richieste: la $i$-esima è una coppia $(s_i, p_i)$ con $s_i$ il nodo dello studente e $p_i$ il pagamento offerto. Tutti gli studenti vanno nel nodo $t$. Si può servire **un solo** studente: lo si raggiunge da $x$ e lo si porta a $t$. Calcolare il massimo guadagno $p_i - \big(d(x,s_i)+d(s_i,t)\big)$.

**Modellazione.** Servire lo studente $i$ costa $d(x,s_i)+d(s_i,t)$ (benzina per raggiungerlo e poi portarlo a destinazione). Le due famiglie di distanze si ottengono con due sole esecuzioni di Dijkstra:
- Dijkstra da $x$ su $G$ → $d_x[v]=d(x,v)$, quindi $d_x[s_i]$;
- Dijkstra da $t$ su $G^T$ → $d_t[v]=d(v,t)$, quindi $d_t[s_i]$ (distanze *verso* $t$).

Il guadagno della richiesta $i$ è $p_i-(d_x[s_i]+d_t[s_i])$; si restituisce il massimo sulle $k$ richieste.

```pseudo
\begin{algorithm}
\caption{MaxGuadagno($G$, $x$, $t$, $\text{richieste}$) → reale}
\begin{algorithmic}
\State $d_x \gets$ \Call{Dijkstra}{$G$, $x$} \Comment{$d_x[v]=d(x,v)$}
\State $d_t \gets$ \Call{Dijkstra}{$G^T$, $t$} \Comment{$d_t[v]=d(v,t)$}
\State $\text{best} \gets -\infty$
\For{ogni richiesta $(s_i, p_i)$}
  \State $\text{guad} \gets p_i - (d_x[s_i] + d_t[s_i])$
  \If{$\text{guad} > \text{best}$}
    \State $\text{best} \gets \text{guad}$
  \EndIf
\EndFor
\State \Return $\text{best}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** due esecuzioni di Dijkstra $O(m+n\log n)$ più scansione $O(k)$ delle richieste; totale $O(m+n\log n+k)$.
**Trappola:** $d(s_i,t)$ si ottiene con **una** Dijkstra da $t$ su $G^T$, non con $k$ Dijkstra (una per studente), che darebbe $O(k(m+n\log n))$; il problema è una **massimizzazione** del guadagno $p_i-\text{costi}$, non un cammino minimo puro; se tutti i guadagni sono negativi si restituisce comunque il massimo (il meno svantaggioso).
