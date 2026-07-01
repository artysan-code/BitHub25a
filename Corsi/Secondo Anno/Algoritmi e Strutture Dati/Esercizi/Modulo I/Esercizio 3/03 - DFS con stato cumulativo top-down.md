---
tags:
  - algoritmi
  - strutture-dati
---
# DFS con stato cumulativo top-down
Esercizio di **modellazione** su alberi: una singola DFS trasporta verso il basso lo stato del cammino radice→nodo (nei parametri) e aggrega risalendo (nel valore di ritorno). Ripasso: [[08 - Grafi e Visite#Visita in profondità — DFS|DFS]], [[05 - Strutture Dati Elementari e Dizionari#Visite di Alberi|visite di alberi]].
## A · Foglia buona per massimo antenato
> [!question] Traccia — 13/06/2024
> Sia $T$ un albero binario in cui ogni nodo $v$ ha un valore $v.\text{val}\geq 0$. Una foglia $v$ è **buona** se **esiste un antenato** $u$ di $v$ tale che $v.\text{val}+u.\text{val}\geq 100$. Restituire il numero di foglie buone. Complessità $O(n)$.

"Esiste un antenato $u$ con $v.\text{val}+u.\text{val}\geq 100$" equivale a "il **massimo** valore fra gli antenati di $v$, sommato a $v.\text{val}$, è $\geq 100$": conviene quindi portare giù, durante la discesa, il massimo valore visto sul cammino.
### Idea risolutiva
Una DFS top-down passa come parametro $M$ = massimo valore fra gli antenati **stretti** di $v$ (radice: $M=-\infty$, nessun antenato). Su una foglia si conta $1$ se $M+v.\text{val}\geq 100$. Ricorrendo sui figli si aggiorna $M'=\max(M,\,v.\text{val})$: il nodo corrente diventa antenato dei figli, non di sé stesso. I conteggi dei due sottoalberi si sommano.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{foglieBuone($r$) → intero}
\begin{algorithmic}
\State \Return \Call{conta}{$r$, $-\infty$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{conta($v$, $M$) → intero}
\begin{algorithmic}
\If{$v = $ null} \State \Return $0$ \EndIf
\If{$v.\text{sx} = $ null e $v.\text{dx} = $ null} \Comment{$v$ è foglia}
  \If{$M + v.\text{val} \geq 100$} \State \Return $1$ \Else \State \Return $0$ \EndIf
\EndIf
\State $M' \gets \max(M,\, v.\text{val})$ \Comment{$v$ è antenato dei figli}
\State \Return \Call{conta}{$v.\text{sx}, M'$} $+$ \Call{conta}{$v.\text{dx}, M'$}
\end{algorithmic}
\end{algorithm}
```
### Complessità
Una chiamata per nodo, lavoro $O(1)$: **$O(n)$** tempo; spazio $O(h)$ per la pila di ricorsione.
### Correttezza
> [!quote] Invariante — $M$ è il massimo antenato
> A ogni chiamata `conta($v$, $M$)` con $v\neq\text{null}$, $M$ è il massimo valore fra gli antenati stretti di $v$ (o $-\infty$ se $v$ è la radice).

**Dimostrazione** (induzione sulla profondità). *Base*: radice, $M=-\infty$, nessun antenato. *Passo*: un figlio di $v$ riceve $M'=\max(M,v.\text{val})$ = massimo fra (antenati di $v$) e $v$ = massimo fra gli antenati del figlio. $\blacksquare$

Per l'invariante, su una foglia $v$ la condizione $M+v.\text{val}\geq 100$ vale se e solo se esiste un antenato con quella somma (il massimo la realizza). Sommando i contributi delle foglie (ognuna visitata una volta) si ottiene il numero di foglie buone. $\blacksquare$

> [!warning] $M$ non include $v$
> L'aggiornamento $M'=\max(M,v.\text{val})$ serve **solo** per i figli e va fatto **dopo** il test foglia (che usa $M$, non $M'$): il nodo non è antenato di sé stesso, contarlo sommerebbe $v.\text{val}$ due volte.
## B · Nodo speciale raggiungibile (top-down + bottom-up)
> [!question] Traccia — 18/07/2022
> Albero binario di $n$ nodi con nomi distinti in $\{1,\dots,n\}$; ogni nodo ha $v.\text{val}\geq 0$ e un flag $v.\text{speciale}$. Un nodo $v$ **può raggiungere** un nodo speciale $u$ se $u$ è antenato o discendente di $v$ e il cammino $v\!-\!u$ non passa per altri nodi speciali oltre $u$. Costruire $V[1..n]$ con $V[i]$ = massimo valore fra i nodi speciali raggiungibili dal nodo di nome $i$. Complessità $O(n)$.
### Idea risolutiva
Da $v$ sono raggiungibili solo: il **più vicino antenato speciale** (quelli più in alto sono schermati) e, per ogni ramo, il **primo speciale scendendo** (quelli più in basso sono schermati). Un nodo già speciale raggiunge **solo sé stesso**. Una sola DFS combina due canali: *top-down* $\text{anc}$ = valore del più vicino antenato speciale (diventa $v.\text{val}$ per i figli se $v$ è speciale); *bottom-up* $\text{nsd}(v)$ = valore del più vicino speciale discendente ($v.\text{val}$ se $v$ speciale, altrimenti il massimo degli $\text{nsd}$ dei figli). Per ogni nodo: se speciale $V[v.\text{nome}]=v.\text{val}$, altrimenti $V[v.\text{nome}]=\max(\text{anc},\ \text{nsd}(sx),\ \text{nsd}(dx))$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{costruisciV($T$) → array $V[1..n]$}
\begin{algorithmic}
\State \Call{DFS}{$T.\text{radice}$, $-\infty$}
\State \Return $V$
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{DFS($v$, $\text{anc}$) → nsd($v$)}
\begin{algorithmic}
\If{$v = $ null} \State \Return $-\infty$ \EndIf
\State $\text{ancFigli} \gets (v.\text{speciale}\ ?\ v.\text{val} : \text{anc})$
\State $sx \gets$ \Call{DFS}{$v.\text{sx}, \text{ancFigli}$}; \; $dx \gets$ \Call{DFS}{$v.\text{dx}, \text{ancFigli}$}
\State $\text{giù} \gets \max(sx, dx)$
\If{$v.\text{speciale}$}
  \State $V[v.\text{nome}] \gets v.\text{val}$; \; \Return $v.\text{val}$
\Else
  \State $V[v.\text{nome}] \gets \max(\text{anc}, \text{giù})$; \; \Return $\text{giù}$
\EndIf
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Una visita, $O(1)$ per nodo → **$O(n)$**; pila $O(h)$. Correttezza: un nodo speciale **blocca** la propagazione in entrambe le direzioni, quindi $\text{anc}$ resta il primo speciale salendo e $\text{nsd}$ il primo scendendo; per un nodo non speciale i raggiungibili sono esattamente questi, e $V$ ne prende il massimo. Un nodo speciale raggiunge solo sé stesso perché ogni cammino verso un altro speciale passerebbe per lui. $\blacksquare$

> [!warning] Blocco bidirezionale
> $\text{anc}$ passato ai figli diventa $v.\text{val}$ **solo se $v$ è speciale**; un nodo speciale interrompe sia la catena verso il basso sia quella verso l'alto. Se nessuno speciale è raggiungibile, $V[i]$ resta $-\infty$ (sentinella da sostituire con la convenzione richiesta).
## C · Cammini radice-foglia alternati
> [!question] Traccia — 09/09/2024
> Albero binario con $v.\text{col}\in\{1,2\}$. Un cammino radice–foglia è **alternato** se non ha mai due nodi adiacenti dello stesso colore. Restituire, separatamente, il numero di cammini radice–foglia alternati che terminano su una foglia di colore $1$ e quelli che terminano su una foglia di colore $2$. Complessità $O(n)$.
### Idea risolutiva
L'alternanza è locale: basta confrontare il colore di ogni nodo con quello del **padre**, portato giù dalla DFS. Appena un nodo ha il colore del padre, il cammino è già non alternato e si **pota** il sottoalbero restituendo $(0,0)$. Su una foglia raggiunta con cammino alternato si conta $1$ nel bucket del suo colore. I risultati dei due sottoalberi si sommano come coppia.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{contaAlternati($T$) → coppia $(c_1, c_2)$}
\begin{algorithmic}
\State \Return \Call{conta}{$T.\text{radice}$, $0$} \Comment{$0$ = padre fittizio (radice)}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{conta($v$, $\text{colPadre}$) → coppia $(c_1, c_2)$}
\begin{algorithmic}
\If{$v = $ null} \State \Return $(0, 0)$ \EndIf
\If{$\text{colPadre} \neq 0$ e $v.\text{col} = \text{colPadre}$} \State \Return $(0, 0)$ \Comment{alternanza rotta: pota} \EndIf
\If{$v.\text{sx} = $ null e $v.\text{dx} = $ null} \Comment{foglia, cammino alternato}
  \If{$v.\text{col} = 1$} \State \Return $(1, 0)$ \Else \State \Return $(0, 1)$ \EndIf
\EndIf
\State $(l_1, l_2) \gets$ \Call{conta}{$v.\text{sx}, v.\text{col}$}; \; $(r_1, r_2) \gets$ \Call{conta}{$v.\text{dx}, v.\text{col}$}
\State \Return $(l_1+r_1,\ l_2+r_2)$
\end{algorithmic}
\end{algorithm}
```
### Complessità e correttezza
Un nodo per visita, $O(1)$ → **$O(n)$**. Correttezza: il confronto col colore del padre (stato top-down) rileva localmente la rottura dell'alternanza; potando, nessuna foglia sotto una rottura viene contata (coerente: il suo cammino contiene la stessa coppia adiacente). Su una foglia con cammino alternato si somma $1$ nel bucket del **suo** colore; l'aggregazione bottom-up delle coppie somma i cammini dei due sottoalberi. $\blacksquare$

> [!warning] Colore del padre, non globale
> Il test è sull'adiacenza col padre, non un controllo globale; il bucket è deciso dal colore della **foglia**; la radice non ha padre (colore fittizio $0$) e non genera mai rottura.
