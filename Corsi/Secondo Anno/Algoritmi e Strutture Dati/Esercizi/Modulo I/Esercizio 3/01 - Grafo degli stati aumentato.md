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
\State $G' \gets (V', E')$
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
\State $V' \gets \{(v,p) : v\in V,\ p\in\{0,1\}\}$
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
\State $G' \gets (V', E')$
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

**Modellazione.** Il costo di attraversare un nodo $v$ non è fisso: dipende dal **colore dell'arco con cui vi si arriva** ($w_1(v)$ se l'arco entrante ha colore $c_1$, $w_2(v)$ se ha colore $c_2$). Due cammini che arrivano in $v$ con archi di colore diverso pagano $v$ in modo diverso, quindi il solo nodo non basta a determinare il costo: lo **stato** è la coppia $(v,c)$ = nodo + colore dell'arco d'ingresso. Ogni nodo si **sdoppia** nelle due copie $(v,c_1)$ e $(v,c_2)$, una per colore d'ingresso ($|V'|=2n$).
Gli archi vanno costruiti in modo che il costo di $v$ si paghi **all'ingresso**, in base al colore dell'arco che entra. Per ogni $e=(u,v)$ di colore $c$ e peso $w(e)$, da **entrambe** le copie di $u$ si entra nella copia $(v,c)$ etichettata col colore di $e$: si aggiungono $((u,c_1),(v,c))$ e $((u,c_2),(v,c))$, entrambi di peso $w(e)+w_c(v)$ (peso dell'arco + costo d'attraversamento di $v$ per il colore $c$). Sono $2m$ archi.
Si esegue Dijkstra dalle **due** copie di $s$ con distanza iniziale $0$: $s$ non ha arco entrante, quindi non paga alcun costo d'attraversamento. Risposta: $\min(d[(t,c_1)], d[(t,c_2)])$, l'uscita su una qualsiasi delle due copie.

```pseudo
\begin{algorithm}
\caption{CamminoColorato($G$, $w$, $\text{col}$, $w_1$, $w_2$, $s$, $t$) → reale}
\begin{algorithmic}
\State $V' \gets \{(v,c) : v\in V,\ c\in\{c_1,c_2\}\}$
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$ di colore $c$}
  \State $\text{peso} \gets w(e) + w_c(v)$ \Comment{arco + costo di $v$ per il colore $c$, pagato all'ingresso}
  \State aggiungi a $E'$ gli archi $((u,c_1),(v,c))$ e $((u,c_2),(v,c))$ di peso $\text{peso}$ \Comment{da entrambe le copie di $u$ alla copia $(v,c)$}
\EndFor
\State $G' \gets (V', E')$
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

**Modellazione.** La penalità $\sigma$ non si paga a ogni arco, ma solo quando il colore **cambia** rispetto all'arco precedente: per sapere se il prossimo arco fa scattare la penalità serve ricordare il colore dell'**ultimo arco percorso**. Il solo nodo non basta, quindi lo **stato** è la coppia $(v, c_{\text{prec}})$ = nodo corrente + colore dell'ultimo arco usato, con $c_{\text{prec}}\in\{1,2,3,\bot\}$ ($\bot$ = nessun arco ancora percorso, lo stato della sorgente). Quattro valori → $|V'|=4n$.
- **Archi:** da $(u, c_{\text{prec}})$, percorrere $e=(u,v)$ di colore $c$ porta a $(v,c)$ (il nuovo "ultimo colore" è $c$) con peso $w(e)$, più $\sigma$ se $c_{\text{prec}}\neq\bot$ e $c\neq c_{\text{prec}}$ (cambio di colore), altrimenti $0$. Ogni arco originale genera così $\le 4$ archi, uno per ciascun colore precedente possibile → $O(m)$ archi.

Si esegue Dijkstra da $(s,\bot)$ (la sorgente non ha ancora percorso archi). Risposta: $\min_{c\in\{1,2,3\}} d[(t,c)]$, il minimo sull'ultimo colore con cui si entra in $t$.

```pseudo
\begin{algorithm}
\caption{CamminoMinPenalita($G$, $w$, $c$, $\sigma$, $s$, $t$) → reale}
\begin{algorithmic}
\State $V' \gets \{(v,c_{\text{prec}}) : v\in V,\ c_{\text{prec}}\in\{1,2,3,\bot\}\}$
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$ di colore $c(e)$}
  \For{ogni $c_{\text{prec}} \in \{1,2,3,\bot\}$}
    \State $\text{pen} \gets (c_{\text{prec}} \neq \bot \text{ e } c(e) \neq c_{\text{prec}})\ ?\ \sigma : 0$ \Comment{penalità solo se cambia colore}
    \State aggiungi a $E'$ l'arco $((u,c_{\text{prec}}),(v,c(e)))$ di peso $w(e)+\text{pen}$ \Comment{il nuovo ultimo colore è $c(e)$}
  \EndFor
\EndFor
\State $G' \gets (V', E')$
\State $d \gets$ \Call{Dijkstra}{$G'$, $(s,\bot)$} \Comment{la sorgente non ha ancora percorso archi}
\State \Return $\min_{c \in \{1,2,3\}} d[(t,c)]$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=4n$, $|E'|=O(m)$ (fattore costante $4$); una Dijkstra $O(m+n\log n)$.
**Trappola:** la penalità si paga sul **cambio** di colore, non a ogni arco; il primo arco non paga penalità (stato $\bot$); con $3$ colori lo stato cresce di un fattore costante, quindi l'ordine di complessità di Dijkstra non cambia.
## Variante — labirinto con teletrasporti a uso limitato (23/09/2025)
> [!question] Traccia — 23/09/2025
> Sia $G=(V,E)$ un grafo orientato; si parte da $s$ con una riserva di forza $\Delta$ e ogni arco $e$ costa $c(e)$ unità. Un sottoinsieme $U\subseteq V$ di stanze speciali consente, per ogni coppia $x,y\in U$, un teletrasporto $x\to y$ che costa $\gamma(x,y)$ la **prima** volta e $5\gamma(x,y)$ la **seconda**; un terzo teletrasporto è fatale. Determinare se si riesce a raggiungere $t$ da $s$ con forza $\le\Delta$.

**Modellazione.** Il costo di un teletrasporto non dipende solo da *dove* ci si trova, ma da **quanti** se ne sono già fatti: il prossimo costa $\gamma$ se è il primo, $5\gamma$ se è il secondo, ed è fatale se è il terzo. Due cammini che arrivano sullo stesso nodo $v$ con un numero diverso di teletrasporti alle spalle **non sono equivalenti**, perché da lì in avanti li pagheranno in modo diverso: l'informazione mancante va quindi inserita nello **stato**, la coppia $(v,k)$ con $k\in\{0,1,2\}$ = nodo corrente + numero di teletrasporti già usati.
Si costruisce il **grafo espanso** $G'$ replicando il grafo su **3 layer**, uno per ogni valore di $k$ ($|V'|=3n$); ogni layer è una copia identica del labirinto:
- **Archi normali** (camminare): non cambiano $k$, quindi collegano nodi dello **stesso** layer. Ogni $e=(u,v)$ di costo $c(e)$ diventa $((u,k),(v,k))$ per ogni $k\in\{0,1,2\}$.
- **Teletrasporti** (cambiano $k$): fanno **salire di un layer**. Per ogni coppia $x,y\in U$ si aggiungono $((x,0),(y,1))$ di peso $\gamma(x,y)$ (primo uso) e $((x,1),(y,2))$ di peso $5\gamma(x,y)$ (secondo uso). Dal layer $k=2$ non esce alcun teletrasporto: il terzo è fatale.

I pesi sono tutti $\ge 0$, quindi si esegue Dijkstra da $(s,0)$ (si parte da $s$ con zero teletrasporti usati). Si riesce a uscire se e solo se l'uscita $t$ è raggiungibile su **un layer qualsiasi** entro la forza disponibile: $\min_{k\in\{0,1,2\}} d[(t,k)]\le\Delta$.

```pseudo
\begin{algorithm}
\caption{UsciDalLabirinto($G$, $c$, $U$, $\gamma$, $s$, $t$, $\Delta$) → booleano}
\begin{algorithmic}
\State $V' \gets \{(v,k) : v\in V,\ k\in\{0,1,2\}\}$
\State $E' \gets \emptyset$
\For{ogni arco $e=(u,v) \in E$}
  \For{$k \gets 0$ \To $2$}
    \State aggiungi a $E'$ l'arco $((u,k),(v,k))$ di peso $c(e)$ \Comment{camminare: si resta nello stesso layer}
  \EndFor
\EndFor
\For{ogni coppia $x,y \in U$}
  \State aggiungi a $E'$ l'arco $((x,0),(y,1))$ di peso $\gamma(x,y)$ \Comment{1º teletrasporto: layer $0\to1$}
  \State aggiungi a $E'$ l'arco $((x,1),(y,2))$ di peso $5\gamma(x,y)$ \Comment{2º teletrasporto: layer $1\to2$}
\EndFor
\State $G' \gets (V', E')$
\State $d \gets$ \Call{Dijkstra}{$G'$, $(s,0)$}
\State \Return $\min_{k \in \{0,1,2\}} d[(t,k)] \le \Delta$ \Comment{uscita su un layer qualsiasi entro $\Delta$}
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $|V'|=3n$; $|E'|=3m+2|U|^2$ (i teletrasporti collegano ogni coppia di $U$); Dijkstra $O\big((m+|U|^2)\log n\big)$.
**Trappola:** il costo del teletrasporto dipende dal numero d'usi ($\gamma$ poi $5\gamma$), da codificare nel layer $k$; non esistono teletrasporti dal layer $2$ (il terzo è fatale); la risposta confronta la distanza minima con il budget $\Delta$ (raggiungibilità con vincolo di costo, non solo cammino minimo).
