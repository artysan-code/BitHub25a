---
tags:
  - algoritmi
  - grafi
---
# Forte connettività con modifica locale
Esercizio di **modellazione**: la proprietà richiesta ("ogni nodo raggiunge ogni altro") è la **forte connessione**, testabile con l'algoritmo delle componenti fortemente connesse; si prova la configurazione base e poi ogni modifica locale ammessa. Ripasso: [[09 - Applicazioni della DFS#Componenti fortemente connesse|componenti fortemente connesse]].
## Traccia
> [!question] Traccia — 24/09/2024
> Un sistema di smistamento bagagli è un grafo orientato $G=(V,E)$ con $n$ hub e $m$ nastri; il nastro $e=(u,v)$ sposta un bagaglio da $u$ a $v$. Alcuni hub sono **configurabili** ($C\subseteq V$): configurare $x\in C$ **inverte la direzione di tutti i nastri incidenti a $x$** (sia entranti sia uscenti), ottenendo $G_x$. Si vuole che da ogni hub si possa raggiungere ogni altro hub. Progettare un algoritmo che decide se, cambiando la configurazione di **al più un** hub configurabile, la proprietà è garantita. Analizzare la complessità.

"Da ogni hub raggiungere ogni altro" è la definizione di grafo **fortemente connesso**. La modifica ammessa è locale: invertire i nastri incidenti a un singolo hub configurabile. Bisogna decidere se $G$ è già fortemente connesso, oppure lo diventa con una di queste inversioni.
## Idea risolutiva
Si usa come scatola nera l'algoritmo **componenti fortemente connesse** (CFC): un grafo è fortemente connesso se e solo se ha **una sola** componente. Si prova prima $G$; se non basta, per ogni hub configurabile $x\in C$ si costruisce $G_x$ (riscandendo $E$ e invertendo ogni arco con un estremo in $x$, $O(n+m)$) e si ritesta. Il primo $x$ che rende $G_x$ fortemente connesso è la risposta; se nessuno funziona (e $G$ non lo era), è impossibile.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciGx($G$, $x$) → grafo}
\begin{algorithmic}
\State $G_x \gets$ grafo con nodi $V$ e archi vuoti
\ForAll{arco $(u,v) \in E$}
  \If{$u = x$ o $v = x$}
    \State aggiungi $(v,u)$ a $G_x$ \Comment{nastro incidente a $x$: invertito}
  \Else
    \State aggiungi $(u,v)$ a $G_x$
  \EndIf
\EndFor
\State \Return $G_x$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{hubRisolutore($G$, $C$) → hub $\in C$, "già FC", oppure null}
\begin{algorithmic}
\If{$|\Call{ComponentiFortementeConnesse}{G}| = 1$}
  \State \Return "già FC"
\EndIf
\ForAll{$x \in C$}
  \State $G_x \gets \Call{costruisciGx}{G, x}$
  \If{$|\Call{ComponentiFortementeConnesse}{G_x}| = 1$}
    \State \Return $x$
  \EndIf
\EndFor
\State \Return null \Comment{nessun hub rende il sistema fortemente connesso}
\end{algorithmic}
\end{algorithm}
```
## Complessità
Il test iniziale su $G$ costa $O(n+m)$. Per ciascuno dei $|C|$ hub, `costruisciGx` scandisce tutti gli archi ($O(n+m)$) e le componenti fortemente connesse su $G_x$ costano $O(n+m)$. Totale **$O(|C|\,(n+m))$** (nel peggiore $|C|=n$ → $O(n(n+m))$).
## Correttezza
Per definizione, il sistema soddisfa la richiesta con al più una modifica **se e solo se** vale una fra: (a) $G$ è già fortemente connesso; (b) esiste $x\in C$ tale che $G_x$ è fortemente connesso. L'algoritmo verifica esattamente (a) e, in caso negativo, prova ogni $x\in C$ per (b). Il test di forte connessione è corretto perché un grafo orientato è fortemente connesso se e solo se ha una sola componente fortemente connessa. Quindi l'algoritmo risponde correttamente. $\blacksquare$

> [!warning] Invertire entrambi i lati
> Configurare $x$ inverte **sia** i nastri entranti **sia** quelli uscenti di $x$: nella costruzione va invertito ogni arco con almeno un estremo uguale a $x$. Invertirne solo metà produce un grafo diverso da $G_x$. Utile anche il test preliminare su $G$: evita di cercare un hub quando non serve.
