---
tags:
  - algoritmi
---
# Grafo degli stati aumentato
Esercizio 3 (Modellazione) — pattern [[Casistiche d'Esame Modulo I]], checklist [[Piano Esame ASD - Modulo I]]; ripasso: [[08 - Grafi e Visite]], [[10 - Cammini Minimi e Dijkstra]], [[07 - Code con Priorità e Heap]], [[05 - Strutture Dati Elementari e Dizionari]].
## Svolgimento — esame 16/07/2024
> [!question] Traccia — 16/07/2024
> Dato un grafo orientato $G=(V,E)$ con $n$ nodi e $m$ archi, a ogni arco $e$ è associata un'etichetta temporale $\lambda(e)\in\{1,\ldots,5\}$ che indica l'unico istante in cui quell'arco può essere percorso. Si vuole trovare il cammino da $s$ a $t$ con il minimo numero di archi tale che le etichette degli archi attraversati siano non decrescenti; un vertice può essere visitato più volte e si può restare fermi in attesa dell'istante opportuno.

**Modellazione.** La posizione da sola non distingue due cammini che raggiungono lo stesso nodo a "hop" diversi con timestamp correnti diversi. Lo **stato** rilevante è la coppia $(v,\tau)$ = nodo corrente + istante corrente.
Si costruisce il **grafo espanso** $G'=(V',E')$:
- **Nodi:** $(v,\tau)$ per ogni $v\in V$, $\tau\in\{1,\ldots,5\}$; dimensione $|V'|=5n$.
- **Archi di attesa:** $((v,\tau),(v,\tau+1))$ per ogni $v\in V$, $\tau\in\{1,\ldots,4\}$; sono $4n$ archi e modellano la sosta in loco con avanzamento del clock.
- **Archi temporali:** $((u,\tau),(v,\tau))$ per ogni $(u,v)\in E$ con $\lambda(u,v)=\tau$; sono $m$ archi e corrispondono ai passi reali nel grafo originale.
- **Dimensione totale:** $|E'|=4n+m=O(n+m)$.

Tutti gli archi di $G'$ hanno peso uniforme, quindi si usa la visita **`visitaBFS`** (da [[08 - Grafi e Visite]]) da $(s,1)$. La risposta è $\min_{\tau\in\{1,\ldots,5\}} d_{G'}[(s,1),(t,\tau)]$.

```pseudo
\begin{algorithm}
\caption{CamminoTemporale($G$, $\lambda$, $s$, $t$) → distanza minima}
\begin{algorithmic}
\Comment{Costruzione di $G'=(V',E')$}
\State $V' \gets \{(v,\tau) : v\in V,\ \tau\in\{1,\ldots,5\}\}$
\State $E' \gets \emptyset$
\For{ogni $v\in V$ e ogni $\tau\in\{1,\ldots,4\}$}
  \State $E' \gets E' \cup \{((v,\tau),(v,\tau+1))\}$ \Comment{arco di attesa}
\EndFor
\For{ogni arco $(u,v)\in E$}
  \State $\tau \gets \lambda(u,v)$
  \State $E' \gets E' \cup \{((u,\tau),(v,\tau))\}$ \Comment{arco temporale}
\EndFor
\State $d \gets$ \Call{visitaBFS}{$G'$, $(s,1)$} \Comment{distanze in numero di archi da $(s,1)$ su $G'$}
\State $\textit{ans} \gets +\infty$
\For{$\tau = 1$ \To $5$}
  \If{$d[(t,\tau)] < \textit{ans}$}
    \State $\textit{ans} \gets d[(t,\tau)]$
  \EndIf
\EndFor
\State \Return $\textit{ans}$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n+m)$ per la costruzione di $G'$ ($|V'|=5n$, $|E'|=O(n+m)$) e $O(|V'|+|E'|)=O(n+m)$ per la BFS; totale $O(n+m)$.
**Trappola:** omettere gli archi di attesa $((v,\tau),(v,\tau+1))$ rende impossibile aspettare l'istante giusto; la BFS va inizializzata da $(s,1)$ soltanto, non da tutti i $(s,\tau)$, altrimenti si ammettono cammini che partono a timestamp arbitrario.
## Variante — bottoni che invertono gli archi (25/07/2023)
> [!question] Traccia — 25/07/2023
> Sia $G=(V,E)$ un grafo orientato con $n$ nodi e $m$ archi. Ogni arco $e$ ha uno stato iniziale $\sigma(e)\in\{\text{on},\text{off}\}$ e si possono attraversare solo gli archi *on*. Un sottoinsieme $B\subseteq V$ di nodi contiene un bottone: stando su $b\in B$ lo si può premere e **tutti** gli archi invertono il loro stato. Determinare, se esiste, una strategia che porta da $s$ a $t$. Complessità $O(n+m)$.

**Modellazione.** Dopo $p$ pressioni gli stati sono invertiti se e solo se $p$ è dispari: conta solo la **parità** di $p$. Lo stato è la coppia $(v,p)$ con $p\in\{0,1\}$; si costruisce $G'$ con $|V'|=2n$ nodi:
- **Archi di movimento:** un arco $e=(u,v)$ è percorribile a parità $0$ se $\sigma(e)=\text{on}$, a parità $1$ se $\sigma(e)=\text{off}$. Si aggiunge quindi $((u,0),(v,0))$ se $\sigma(e)=\text{on}$, oppure $((u,1),(v,1))$ se $\sigma(e)=\text{off}$: un arco per ogni $e$, in totale $m$.
- **Archi bottone:** per ogni $b\in B$ gli archi $((b,0),(b,1))$ e $((b,1),(b,0))$ (premere il bottone cambia parità restando sul nodo); in totale $2|B|$.

Tutti gli archi hanno peso unitario e serve la sola raggiungibilità: si lancia `visitaBFS` da $(s,0)$. Esiste una strategia se e solo se $(t,0)$ oppure $(t,1)$ è raggiungibile.

```pseudo
\begin{algorithm}
\caption{CianoVince($G$, $\sigma$, $B$, $s$, $t$) → booleano}
\begin{algorithmic}
\Comment{Costruzione di $G'$ con stati $(v, p)$, $p \in \{0,1\}$}
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$}
  \If{$\sigma(e) = \text{on}$}
    \State $E' \gets E' \cup \{((u,0),(v,0))\}$
  \Else
    \State $E' \gets E' \cup \{((u,1),(v,1))\}$
  \EndIf
\EndFor
\For{ogni $b \in B$}
  \State $E' \gets E' \cup \{((b,0),(b,1)),\ ((b,1),(b,0))\}$
\EndFor
\State $d \gets$ \Call{visitaBFS}{$G'$, $(s,0)$}
\State \Return $d[(t,0)] < \infty$ o $d[(t,1)] < \infty$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=2n$ e $|E'|=m+2|B|=O(n+m)$; costruzione e `visitaBFS` costano $O(n+m)$.
**Trappola:** conta la *parità* del numero di pressioni, non il conteggio esatto ($2$ layer bastano); ogni arco va inserito nel solo layer di parità in cui è percorribile; gli archi-bottone esistono solo per $b\in B$; la parità d'arrivo in $t$ è irrilevante, quindi si accetta sia $(t,0)$ sia $(t,1)$.
## Variante — costo del nodo per colore dell'arco entrante (21/01/2025)
> [!question] Traccia — 21/01/2025
> Sia $G=(V,E)$ un grafo orientato. Ogni arco $e$ ha peso $w(e)\ge 0$ e colore $\text{col}(e)\in\{c_1,c_2\}$; ogni nodo $v$ ha due costi $w_1(v), w_2(v)$, dove $w_i(v)$ è il costo di attraversare $v$ se vi si arriva con un arco di colore $c_i$. Il costo di un cammino è la somma dei pesi degli archi più la somma dei costi di attraversamento dei nodi. Calcolare il cammino di costo minimo da $s$ a $t$. Complessità $O(m+n\log n)$.

**Modellazione.** Il costo di "stare in $v$" dipende dal colore dell'arco con cui ci si arriva: lo stato è la coppia $(v, c)$ con $c$ = colore dell'arco entrante. Ogni nodo si **sdoppia** in $(v,c_1)$ e $(v,c_2)$; $|V'|=2n$. Per ogni arco $e=(u,v)$ di colore $c$ e peso $w(e)$ si aggiungono $((u,c_1),(v,c))$ e $((u,c_2),(v,c))$, entrambi di peso $w(e)+w_c(v)$: da entrambe le copie di $u$ si entra nella copia di $v$ etichettata col colore di $e$, pagando l'arco più il costo di $v$ relativo a quel colore. Sono $2m$ archi. Si esegue Dijkstra su $G'$ da entrambe le copie di $s$ (peso iniziale $0$: $s$ non ha arco entrante e quindi non paga costo d'attraversamento). Risposta: $\min(d[(t,c_1)], d[(t,c_2)])$.

```pseudo
\begin{algorithm}
\caption{CamminoColorato($G$, $w$, $\text{col}$, $w_1$, $w_2$, $s$, $t$) → reale}
\begin{algorithmic}
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$ di colore $c$}
  \State $\text{peso} \gets w(e) + w_c(v)$
  \State aggiungi a $E'$ gli archi $((u,c_1),(v,c))$ e $((u,c_2),(v,c))$ di peso $\text{peso}$
\EndFor
\State $d \gets$ \Call{Dijkstra}{$G'$, $\{(s,c_1),(s,c_2)\}$} \Comment{due sorgenti, distanza iniziale $0$}
\State \Return $\min(d[(t,c_1)],\ d[(t,c_2)])$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=2n$, $|E'|=2m$; una Dijkstra $O(m+n\log n)$.
**Trappola:** il costo del nodo si paga **all'ingresso** in $(v,c)$ e dipende dal colore dell'arco entrante, quindi va caricato sull'arco che entra in $(v,c)$, non su quelli uscenti; $s$ parte a costo $0$ da entrambe le copie (nessun arco entrante); serve il $\min$ sulle due copie di $t$.
## Variante — penalità a ogni cambio di colore (09/09/2025)
> [!question] Traccia — 09/09/2025
> Sia $G=(V,E)$ un grafo orientato. Ogni arco $e$ ha un costo $w(e)$ e un colore $c(e)\in\{1,2,3\}$. Il costo di un cammino da $s$ a $t$ è la somma dei costi degli archi più una penalità $\sigma>0$ per ogni *cambio di colore* fra archi consecutivi. Calcolare il cammino di costo totale minimo.

**Modellazione.** La penalità dipende dal colore dell'**ultimo arco percorso**: lo stato è la coppia $(v, c_{\text{prec}})$ con $c_{\text{prec}}\in\{1,2,3,\bot\}$ ($\bot$ = nessun arco ancora percorso, per la sorgente). Da $(u, c_{\text{prec}})$, percorrere $e=(u,v)$ di colore $c$ porta a $(v,c)$ con peso $w(e)$ più $\sigma$ se $c_{\text{prec}}\neq\bot$ e $c\neq c_{\text{prec}}$, altrimenti $0$. $|V'|=4n$; ogni arco genera $\le 4$ archi (uno per colore precedente) → $O(m)$ archi. Dijkstra da $(s,\bot)$; risposta $\min_{c\in\{1,2,3\}} d[(t,c)]$.

```pseudo
\begin{algorithm}
\caption{CamminoMinPenalita($G$, $w$, $c$, $\sigma$, $s$, $t$) → reale}
\begin{algorithmic}
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$ di colore $c(e)$}
  \For{ogni $c_{\text{prec}} \in \{1,2,3,\bot\}$}
    \State $\text{pen} \gets (c_{\text{prec}} \neq \bot \text{ e } c(e) \neq c_{\text{prec}})\ ?\ \sigma : 0$
    \State aggiungi a $E'$ l'arco $((u,c_{\text{prec}}),(v,c(e)))$ di peso $w(e)+\text{pen}$
  \EndFor
\EndFor
\State $d \gets$ \Call{Dijkstra}{$G'$, $(s,\bot)$}
\State \Return $\min_{c \in \{1,2,3\}} d[(t,c)]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=4n$, $|E'|=O(m)$ (fattore costante $4$); una Dijkstra $O(m+n\log n)$.
**Trappola:** la penalità si paga sul **cambio** di colore, non a ogni arco; il primo arco non paga penalità (stato $\bot$); con $3$ colori lo stato cresce di un fattore costante, quindi l'ordine di complessità di Dijkstra non cambia.
## Variante — labirinto con teletrasporti a uso limitato (23/09/2025)
> [!question] Traccia — 23/09/2025
> Sia $G=(V,E)$ un grafo orientato; si parte da $s$ con una riserva di forza $\Delta$ e ogni arco $e$ costa $c(e)$ unità. Un sottoinsieme $U\subseteq V$ di stanze speciali consente, per ogni coppia $x,y\in U$, un teletrasporto $x\to y$ che costa $\gamma(x,y)$ la **prima** volta e $5\gamma(x,y)$ la **seconda**; un terzo teletrasporto è fatale. Determinare se si riesce a raggiungere $t$ da $s$ con forza $\le\Delta$.

**Modellazione.** Il costo di un teletrasporto dipende da **quanti** se ne sono già usati: lo stato è la coppia $(v, k)$ con $k\in\{0,1,2\}$ = numero di teletrasporti effettuati. Si hanno $3$ layer ($|V'|=3n$):
- **Archi normali:** $e=(u,v)$ di costo $c(e)$, replicato in ogni layer: $((u,k),(v,k))$ per $k\in\{0,1,2\}$.
- **Teletrasporti:** per ogni $x,y\in U$, $((x,0),(y,1))$ di peso $\gamma(x,y)$ (primo uso) e $((x,1),(y,2))$ di peso $5\gamma(x,y)$ (secondo uso). Nessun teletrasporto esce dal layer $k=2$ (il terzo è fatale).

Si esegue Dijkstra da $(s,0)$; si raggiunge $t$ con forza sufficiente se e solo se $\min_{k\in\{0,1,2\}} d[(t,k)]\le\Delta$.

```pseudo
\begin{algorithm}
\caption{UsciDalLabirinto($G$, $c$, $U$, $\gamma$, $s$, $t$, $\Delta$) → booleano}
\begin{algorithmic}
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$}
  \For{$k \gets 0$ \To $2$}
    \State aggiungi a $E'$ l'arco $((u,k),(v,k))$ di peso $c(e)$
  \EndFor
\EndFor
\For{ogni coppia $x,y \in U$}
  \State aggiungi a $E'$ l'arco $((x,0),(y,1))$ di peso $\gamma(x,y)$
  \State aggiungi a $E'$ l'arco $((x,1),(y,2))$ di peso $5\gamma(x,y)$
\EndFor
\State $d \gets$ \Call{Dijkstra}{$G'$, $(s,0)$}
\State \Return $\min_{k \in \{0,1,2\}} d[(t,k)] \le \Delta$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=3n$; $|E'|=3m+2|U|^2$ (i teletrasporti collegano ogni coppia di $U$); Dijkstra $O\big((m+|U|^2)\log n\big)$.
**Trappola:** il costo del teletrasporto dipende dal numero d'usi ($\gamma$ poi $5\gamma$), da codificare nel layer $k$; non esistono teletrasporti dal layer $2$ (il terzo è fatale); la risposta confronta la distanza minima con il budget $\Delta$ (raggiungibilità con vincolo di costo, non solo cammino minimo).
