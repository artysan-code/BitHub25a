---
tags:
  - algoritmi
  - grafi
---
# Grafo degli stati aumentato
Esercizio di **modellazione**: quando la posizione (il nodo) non basta a determinare le mosse future — perché conta anche un "contesto" (tempo, parità, colore, risorse) — si costruisce un **grafo espanso** i cui nodi sono coppie *(nodo, stato)*, e vi si applica un algoritmo noto (BFS se i costi sono unitari, Dijkstra se pesati). Ripasso: [[08 - Grafi e Visite#Visita in ampiezza — BFS|BFS]], [[10 - Cammini Minimi e Dijkstra#Algoritmo di Dijkstra|Dijkstra]].
## A · Grafo temporale: esistenza di un cammino temporale
> [!question] Traccia — 16/07/2024
> Un **grafo temporale** è un grafo **non orientato** $G$ in cui ogni arco $e$ ha un'etichetta $\lambda(e)$ che indica l'istante in cui $e$ può essere percorso. Un **cammino temporale** da $s$ a $t$ è un cammino le cui etichette, nell'ordine di percorrenza, sono **non decrescenti**. Con $\lambda(e)\in\{1,2,3,4,5\}$, progettare un algoritmo che, dati $G$, $s$, $t$, decide **se esiste** un cammino temporale da $s$ a $t$. Complessità $O(n+m)$.

La sola posizione non basta: raggiungere un nodo "al tempo $\tau$" vincola quali archi si potranno ancora usare (solo quelli con etichetta $\geq\tau$). Lo **stato** rilevante è la coppia $(v,\tau)$ = nodo + istante corrente.
### Idea risolutiva
Si costruisce il grafo espanso $G'$ con nodi $(v,\tau)$, $\tau\in\{1,\dots,5\}$ ($|V'|=5n$):

- **archi di attesa** $((v,\tau),(v,\tau+1))$ per $\tau\in\{1,\dots,4\}$: restare fermi facendo avanzare il tempo ($4n$ archi);

- **archi temporali**: per ogni arco non orientato $\{u,v\}$ con $\lambda=\tau$, i due archi $((u,\tau),(v,\tau))$ e $((v,\tau),(u,\tau))$ ($2m$ archi).

Un cammino in $G'$ percorre archi in ordine di $\tau$ non decrescente (le attese aumentano $\tau$, gli archi temporali lo mantengono): corrisponde esattamente a un cammino temporale. L'esistenza si riduce alla **raggiungibilità**: si lancia una BFS (o DFS) da $(s,1)$ e si controlla se un qualsiasi $(t,\tau)$ è raggiunto.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{esisteCamminoTemporale($G$, $\lambda$, $s$, $t$) → booleano}
\begin{algorithmic}
\State $V' \gets \{(v,\tau) : v\in V,\ \tau\in\{1,\dots,5\}\}$; \; $E' \gets \emptyset$
\ForAll{$v\in V$ e $\tau\in\{1,\dots,4\}$}
  \State $E' \gets E' \cup \{((v,\tau),(v,\tau+1))\}$ \Comment{attesa}
\EndFor
\ForAll{arco $\{u,v\}\in E$ con $\tau = \lambda(\{u,v\})$}
  \State $E' \gets E' \cup \{((u,\tau),(v,\tau)),\ ((v,\tau),(u,\tau))\}$ \Comment{non orientato: entrambi i versi}
\EndFor
\State $R \gets$ \Call{visitaBFS}{$(V',E')$, $(s,1)$} \Comment{insieme dei raggiungibili da $(s,1)$}
\State \Return $\exists\,\tau\in\{1,\dots,5\}:\ (t,\tau)\in R$
\end{algorithmic}
\end{algorithm}
```
### Complessità
$|V'|=5n=O(n)$, $|E'|=4n+2m=O(n+m)$; costruzione $O(n+m)$ e BFS $O(|V'|+|E'|)=O(n+m)$. Totale **$O(n+m)$**.
### Correttezza
> [!quote] Invariante — cammini in $G'$ = cammini temporali
> Esiste un cammino da $(s,1)$ a $(t,\tau)$ in $G'$ per qualche $\tau$ **se e solo se** esiste un cammino temporale da $s$ a $t$ in $G$.

**Dimostrazione.** ($\Leftarrow$) Un cammino temporale usa archi con etichette $\tau_1\le\tau_2\le\cdots$: lo si simula in $G'$ partendo da $(s,1)$, aspettando (archi di attesa) fino a $\tau_1$, attraversando l'arco temporale a livello $\tau_1$, aspettando fino a $\tau_2$, ecc. ($\Rightarrow$) In $G'$ le uniche mosse sono attese (che aumentano $\tau$) e archi temporali (che mantengono $\tau$ e corrispondono a un arco reale percorso all'istante $\tau$); lungo un cammino $\tau$ non decresce mai, quindi gli archi reali percorsi hanno etichette non decrescenti. $\blacksquare$

Quindi la raggiungibilità di un qualche $(t,\tau)$ da $(s,1)$, calcolata dalla BFS, decide l'esistenza del cammino temporale. $\blacksquare$

> [!warning] Attese obbligatorie e partenza da $(s,1)$
> Senza gli archi di attesa non si potrebbe "aspettare" l'istante giusto; la BFS parte **solo** da $(s,1)$, non da tutti i $(s,\tau)$, altrimenti si ammetterebbero partenze a un istante arbitrario. Il grafo è non orientato → ogni arco temporale va inserito in **entrambi** i versi.
## B · Bottoni che invertono gli archi (parità)
> [!question] Traccia — 25/07/2023
> Grafo orientato $G=(V,E)$; ogni arco $e$ ha stato $\sigma(e)\in\{\text{on},\text{off}\}$ e si percorrono solo gli archi **on**. Su un insieme $B\subseteq V$ c'è un bottone: stando su $b\in B$ lo si preme e **tutti** gli archi invertono lo stato. Trovare, se esiste, una strategia da $s$ a $t$. Complessità $O(n+m)$.
### Idea e pseudocodice
Dopo $p$ pressioni gli stati sono invertiti sse e solo se $p$ è **dispari**: conta solo la **parità**. Stato $(v,p)$, $p\in\{0,1\}$ ($|V'|=2n$). Un arco $e=(u,v)$ è percorribile a parità $0$ se $\sigma(e)=\text{on}$, a parità $1$ se $\sigma(e)=\text{off}$; i bottoni cambiano parità restando sul nodo. Pesi unitari (sola raggiungibilità) → BFS da $(s,0)$.
```pseudo
\begin{algorithm}
\caption{strategiaBottoni($G$, $\sigma$, $B$, $s$, $t$) → booleano}
\begin{algorithmic}
\State $V' \gets \{(v,p) : v\in V,\ p\in\{0,1\}\}$; \; $E' \gets \emptyset$
\ForAll{arco $e=(u,v) \in E$}
  \If{$\sigma(e) = \text{on}$} \State $E' \mathrel{+}= ((u,0),(v,0))$
  \Else \State $E' \mathrel{+}= ((u,1),(v,1))$ \EndIf
\EndFor
\ForAll{$b \in B$}
  \State $E' \mathrel{+}= ((b,0),(b,1)),\ ((b,1),(b,0))$ \Comment{premere il bottone}
\EndFor
\State $R \gets$ \Call{visitaBFS}{$(V',E')$, $(s,0)$}
\State \Return $(t,0)\in R$ o $(t,1)\in R$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
$|V'|=2n$, $|E'|=m+2|B|=O(n+m)$; BFS $O(n+m)$. Bastano $2$ layer perché conta la parità, non il conteggio esatto; ogni arco entra nel solo layer in cui è percorribile; la parità d'arrivo in $t$ è irrilevante (si accettano $(t,0)$ e $(t,1)$). $\blacksquare$
## C · Costo del nodo per colore dell'arco entrante
> [!question] Traccia — 21/01/2025
> Grafo orientato $G$; ogni arco $e$ ha peso $w(e)\geq 0$ e colore $\text{col}(e)\in\{c_1,c_2\}$; ogni nodo $v$ ha due costi $w_1(v), w_2(v)$, dove $w_i(v)$ è il costo di attraversare $v$ se vi si arriva con un arco di colore $c_i$. Il costo di un cammino è la somma dei pesi degli archi più i costi di attraversamento dei nodi. Calcolare il cammino minimo $s\to t$. Complessità $O(m+n\log n)$.
### Idea e pseudocodice
Il costo di $v$ dipende dal **colore dell'arco entrante**: lo stato è $(v,c)$ = nodo + colore d'ingresso ($|V'|=2n$). Il costo del nodo si paga **all'ingresso**: per ogni arco $e=(u,v)$ di colore $c$, da **entrambe** le copie di $u$ si entra in $(v,c)$ con peso $w(e)+w_c(v)$. Dijkstra dalle due copie di $s$ (che non paga ingresso).
```pseudo
\begin{algorithm}
\caption{camminoColorato($G$, $w$, $\text{col}$, $w_1$, $w_2$, $s$, $t$) → reale}
\begin{algorithmic}
\State $V' \gets \{(v,c) : v\in V,\ c\in\{c_1,c_2\}\}$; \; $E' \gets \emptyset$
\ForAll{arco $e=(u,v) \in E$ di colore $c$}
  \State $\text{peso} \gets w(e) + w_c(v)$ \Comment{arco + costo di $v$ per il colore $c$}
  \State $E' \mathrel{+}= ((u,c_1),(v,c)),\ ((u,c_2),(v,c))$ di peso $\text{peso}$
\EndFor
\State $d \gets$ \Call{Dijkstra}{$(V',E')$, $\{(s,c_1),(s,c_2)\}$} \Comment{due sorgenti, distanza iniziale $0$}
\State \Return $\min(d[(t,c_1)],\ d[(t,c_2)])$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
$|V'|=2n$, $|E'|=2m$ → Dijkstra **$O(m+n\log n)$**. Il costo del nodo si carica sull'arco che **entra** in $(v,c)$ (dipende dal colore entrante), non sugli uscenti; $s$ parte a costo $0$ da entrambe le copie (nessun arco entrante); serve il $\min$ sulle due copie di $t$. $\blacksquare$
## D · Penalità a ogni cambio di colore
> [!question] Traccia — 09/09/2025
> Grafo orientato $G$; ogni arco $e$ ha costo $w(e)$ e colore $c(e)\in\{1,2,3\}$. Il costo di un cammino è la somma dei costi degli archi più una penalità $\sigma>0$ ogni volta che il cammino **cambia colore** fra archi consecutivi. Calcolare il cammino di costo minimo $s\to t$.
### Idea e pseudocodice
La penalità dipende dal colore dell'**ultimo arco percorso**: stato $(v,c_{\text{prec}})$ con $c_{\text{prec}}\in\{1,2,3,\bot\}$ ($\bot$ = ancora nessun arco; $|V'|=4n$). Da $(u,c_{\text{prec}})$, l'arco $e=(u,v)$ di colore $c$ porta a $(v,c)$ con peso $w(e)+\sigma\cdot[\,c_{\text{prec}}\neq\bot \wedge c\neq c_{\text{prec}}\,]$. Dijkstra da $(s,\bot)$.
```pseudo
\begin{algorithm}
\caption{camminoMinPenalita($G$, $w$, $c$, $\sigma$, $s$, $t$) → reale}
\begin{algorithmic}
\State $V' \gets \{(v,c_{\text{prec}}) : v\in V,\ c_{\text{prec}}\in\{1,2,3,\bot\}\}$; \; $E' \gets \emptyset$
\ForAll{arco $e=(u,v) \in E$ di colore $c(e)$}
  \ForAll{$c_{\text{prec}} \in \{1,2,3,\bot\}$}
    \State $\text{pen} \gets \sigma$ se $(c_{\text{prec}} \neq \bot$ e $c(e) \neq c_{\text{prec}})$, altrimenti $0$
    \State $E' \mathrel{+}= ((u,c_{\text{prec}}),(v,c(e)))$ di peso $w(e)+\text{pen}$
  \EndFor
\EndFor
\State $d \gets$ \Call{Dijkstra}{$(V',E')$, $(s,\bot)$}
\State \Return $\min_{c \in \{1,2,3\}} d[(t,c)]$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
$|V'|=4n$, $|E'|=O(m)$ (fattore $4$) → Dijkstra **$O(m+n\log n)$**. La penalità si paga sul **cambio** di colore, non a ogni arco; il primo arco non paga (stato $\bot$); il fattore costante $4$ non altera l'ordine. $\blacksquare$
## E · Teletrasporti a uso limitato
> [!question] Traccia — 23/09/2025
> Grafo orientato $G$; si parte da $s$ con riserva di forza $\Delta$ e ogni arco $e$ costa $c(e)$. Un insieme $U\subseteq V$ di stanze consente, per ogni coppia $x,y\in U$, di teletrasportarsi $x\to y$ al costo $\gamma(x,y)$ la **prima** volta, $5\gamma(x,y)$ la **seconda**; un terzo teletrasporto è fatale. Decidere se si raggiunge $t$ con forza $\leq\Delta$.
### Idea e pseudocodice
Il costo del teletrasporto dipende da **quanti** se ne sono già fatti: stato $(v,k)$, $k\in\{0,1,2\}$ = nodo + teletrasporti usati ($|V'|=3n$, tre layer). Gli archi normali restano nello stesso layer; i teletrasporti **salgono** di un layer. Pesi $\geq 0$ → Dijkstra da $(s,0)$; si esce se $\min_k d[(t,k)]\leq\Delta$.
```pseudo
\begin{algorithm}
\caption{esciConForza($G$, $c$, $U$, $\gamma$, $s$, $t$, $\Delta$) → booleano}
\begin{algorithmic}
\State $V' \gets \{(v,k) : v\in V,\ k\in\{0,1,2\}\}$; \; $E' \gets \emptyset$
\ForAll{arco $e=(u,v) \in E$}
  \For{$k \gets 0$ \To $2$} \State $E' \mathrel{+}= ((u,k),(v,k))$ di peso $c(e)$ \Comment{camminare: stesso layer} \EndFor
\EndFor
\ForAll{coppia $x,y \in U$}
  \State $E' \mathrel{+}= ((x,0),(y,1))$ di peso $\gamma(x,y)$ \Comment{1º teletrasporto}
  \State $E' \mathrel{+}= ((x,1),(y,2))$ di peso $5\gamma(x,y)$ \Comment{2º teletrasporto}
\EndFor
\State $d \gets$ \Call{Dijkstra}{$(V',E')$, $(s,0)$}
\State \Return $\min_{k \in \{0,1,2\}} d[(t,k)] \leq \Delta$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
$|V'|=3n$, $|E'|=3m+2|U|^2$ → Dijkstra **$O((m+|U|^2)\log n)$**. Il numero d'usi è codificato nel layer $k$ ($\gamma$ poi $5\gamma$); dal layer $2$ non esce alcun teletrasporto (il terzo è fatale); la risposta confronta la distanza minima col budget $\Delta$ (raggiungibilità con vincolo di costo). $\blacksquare$
