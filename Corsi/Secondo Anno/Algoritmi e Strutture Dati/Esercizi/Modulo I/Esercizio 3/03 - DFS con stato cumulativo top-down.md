---
tags:
  - algoritmi
---
# DFS con stato cumulativo top-down
Casistica tipica dell'Esercizio 3 (Modellazione) di ASD Modulo I; vedi [[Casistiche d'Esame Modulo I]] per la panoramica delle tipologie e [[Piano Esame ASD - Modulo I]] per la checklist. Ripasso: [[05 - Strutture Dati Elementari e Dizionari]] (visite ricorsive di alberi), [[08 - Grafi e Visite]].
## Svolgimento — esame 13/06/2024
> [!question] Traccia — 13/06/2024
> Dato un albero binario i cui nodi hanno un campo intero $\text{val}$, una foglia $v$ è detta **buona** se la somma del massimo valore tra i suoi antenati stretti (escluso $v$ stesso) e $v.\text{val}$ è $\geq 100$. Scrivere un algoritmo efficiente che restituisce il numero di foglie buone.

**Modellazione.** La proprietà di una foglia dipende dall'intera storia del cammino radice–foglia: occorre tenere traccia del massimo $M$ tra i valori degli antenati incontrati finora, passandolo come parametro alla ricorsione (non come variabile globale, per evitare side effect durante il backtracking). Si inizia con $M = -\infty$ (la radice non ha antenati). Quando si ricorre sui figli di $v$, si aggiorna $M' = \max(M, v.\text{val})$: il nodo corrente diventa antenato dei figli, non di sé stesso. Le chiamate ricorsive sui due sottoalberi contribuiscono con somma al conteggio complessivo (combinazione bottom-up).

**Dimensionamento.** L'albero ha $n$ nodi; nessuna struttura ausiliaria aggiuntiva è necessaria. Lo stack di ricorsione è profondo $O(h)$, con $h$ altezza dell'albero.

```pseudo
\begin{algorithm}
\caption{fogliBuone($r$) → intero}
\begin{algorithmic}
\State \Return \Call{contaFoglie}{$r$, $-\infty$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{contaFoglie($v$, $M$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\If{$v.\text{sx} = $ null e $v.\text{dx} = $ null} \Comment{$v$ è una foglia}
  \If{$M + v.\text{val} \geq 100$}
    \State \Return $1$
  \Else
    \State \Return $0$
  \EndIf
\EndIf
\State $M' \gets \max(M,\, v.\text{val})$ \Comment{$v$ è antenato dei suoi figli}
\State \Return \Call{contaFoglie}{$v.\text{sx},\, M'$} $+$ \Call{contaFoglie}{$v.\text{dx},\, M'$}
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $\Theta(n)$ — ogni nodo è visitato esattamente una volta.

**Trappola:** Il nodo corrente non è antenato di sé stesso. L'aggiornamento $M' = \max(M, v.\text{val})$ serve per ricorrere sui figli: va calcolato DOPO il controllo foglia (che usa $M$, non $M'$) e PRIMA delle chiamate ricorsive. Usare $M'$ al posto di $M$ nel controllo foglia darebbe un risultato scorretto contando $v.\text{val}$ due volte.
## Variante — nodo speciale raggiungibile (18/07/2022)
> [!question] Traccia — 18/07/2022
> Sia $T$ un albero binario di $n$ nodi con nomi distinti in $\{1,\ldots,n\}$. Ogni nodo $v$ ha un nome $v.\text{nome}$, un valore $v.\text{val}\ge 0$ e un flag $v.\text{speciale}$. Un nodo $v$ *può raggiungere* un nodo speciale $u$ se $u$ è antenato o discendente di $v$ e il cammino fra $v$ e $u$ non attraversa nodi speciali diversi da $u$. Costruire $V[1..n]$ con $V[i]$ = massimo valore tra i nodi speciali raggiungibili dal nodo di nome $i$. Complessità $O(n)$.

**Modellazione.** Dalla definizione, dal nodo $v$ sono raggiungibili soltanto: (i) il *più vicino antenato speciale* (gli speciali più in alto sono schermati da quest'ultimo), e (ii) per ciascun ramo discendente, il *primo nodo speciale incontrato* scendendo (gli speciali più in basso sono schermati). Un nodo $v$ già speciale raggiunge **solo sé stesso**, perché qualsiasi cammino verso un altro speciale passerebbe per $v$ stesso (speciale, diverso dalla meta).
Si risolve con una **singola DFS** che porta giù lo stato e aggrega risalendo:
- *top-down*: $\text{anc}$ = valore del più vicino antenato speciale (scende ai figli aggiornato a $v.\text{val}$ se $v$ è speciale, altrimenti invariato);
- *bottom-up*: $\text{nsd}(v)$ = valore del più vicino speciale discendente nel sottoalbero di $v$, pari a $v.\text{val}$ se $v$ è speciale, altrimenti al massimo degli $\text{nsd}$ dei figli.

Per ogni nodo: se $v$ è speciale $V[v.\text{nome}]=v.\text{val}$; altrimenti $V[v.\text{nome}]=\max(\text{anc},\ \max_{\text{figli } c}\text{nsd}(c))$.

```pseudo
\begin{algorithm}
\caption{CostruisciV($T$) → array $V[1..n]$}
\begin{algorithmic}
\State alloca $V[1..n]$
\State \Call{DFS}{$T.\text{radice}$, $-\infty$}
\State \Return $V$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{DFS($v$, $\text{anc}$) → nsd($v$)}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $-\infty$
\EndIf
\State $\text{ancFigli} \gets (v.\text{speciale}\ ?\ v.\text{val} : \text{anc})$
\State $sx \gets$ \Call{DFS}{$v.\text{sx}$, $\text{ancFigli}$}
\State $dx \gets$ \Call{DFS}{$v.\text{dx}$, $\text{ancFigli}$}
\State $\text{downDesc} \gets \max(sx, dx)$
\If{$v.\text{speciale}$}
  \State $V[v.\text{nome}] \gets v.\text{val}$
  \State \Return $v.\text{val}$
\Else
  \State $V[v.\text{nome}] \gets \max(\text{anc},\ \text{downDesc})$
  \State \Return $\text{downDesc}$
\EndIf
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $\Theta(n)$ — una sola visita, aggiornamento di $V$ in $O(1)$ per nodo; stack profondo $O(h)$.
**Trappola:** lo stato $\text{anc}$ passato ai figli usa $v.\text{val}$ **solo se $v$ è speciale** (altrimenti propaga l'antenato già noto); un nodo speciale *blocca* la propagazione sia verso l'alto sia verso il basso, quindi i suoi $\text{nsd}$ non scendono oltre; se nessuno speciale è raggiungibile $V[i]$ resta $-\infty$ (sentinella, da rimpiazzare con la convenzione richiesta — es. $0$).
## Variante — cammini radice-foglia alternati (09/09/2024)
> [!question] Traccia — 09/09/2024
> Sia $T$ un albero binario in cui ogni nodo $v$ ha un colore $v.\text{col}\in\{1,2\}$. Un cammino radice–foglia è *alternato* se non contiene mai due nodi adiacenti dello stesso colore. Restituire il numero di cammini radice–foglia alternati che terminano su una foglia di colore $1$ e, separatamente, quelli che terminano su una foglia di colore $2$. Complessità $O(n)$.

**Modellazione.** L'alternanza è una proprietà *locale propagata dall'alto*: basta confrontare il colore di ogni nodo con quello del padre. Una DFS top-down porta giù il colore del padre; appena un nodo ha lo stesso colore del padre il cammino radice→nodo è già non alternato e nessun cammino radice–foglia che passa di lì può esserlo: si pota l'intero sottoalbero restituendo $(0,0)$. Su una foglia raggiunta con cammino ancora alternato si conta $1$ nel bucket del suo colore. I conteggi dei due sottoalberi si sommano (aggregazione bottom-up di una coppia).

```pseudo
\begin{algorithm}
\caption{ContaAlternati($T$) → coppia $(c_1, c_2)$}
\begin{algorithmic}
\State \Return \Call{Conta}{$T.\text{radice}$, $0$} \Comment{$0$ = nessun padre (colore fittizio)}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{Conta($v$, $\text{colPadre}$) → coppia $(c_1, c_2)$}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $(0, 0)$
\EndIf
\If{$\text{colPadre} \neq 0$ e $v.\text{col} = \text{colPadre}$}
  \State \Return $(0, 0)$ \Comment{alternanza rotta: pota il sottoalbero}
\EndIf
\If{$v.\text{sx} = $ null e $v.\text{dx} = $ null} \Comment{$v$ è foglia, cammino alternato}
  \If{$v.\text{col} = 1$}
    \State \Return $(1, 0)$
  \Else
    \State \Return $(0, 1)$
  \EndIf
\EndIf
\State $(l_1, l_2) \gets$ \Call{Conta}{$v.\text{sx}$, $v.\text{col}$}
\State $(r_1, r_2) \gets$ \Call{Conta}{$v.\text{dx}$, $v.\text{col}$}
\State \Return $(l_1 + r_1,\ l_2 + r_2)$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $\Theta(n)$ — ogni nodo visitato una volta, lavoro $O(1)$ per nodo.
**Trappola:** il confronto è col colore del **padre** (stato top-down), non un controllo globale; un nodo che rompe l'alternanza pota tutto il sottoalbero (le foglie sotto non si contano); il bucket è deciso dal colore della **foglia**, non della radice; la radice non ha padre, quindi non genera mai rottura (colore fittizio $0$).
