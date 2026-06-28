---
tags:
  - algoritmi
---
# DFS post-order su albero binario
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]] con aggregazione bottom-up; schemi e checklist in [[Piano Esame ASD - Modulo I]]. Ripasso: [[08 - Grafi e Visite]], [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 28/09/2022
> Dato un albero binario i cui nodi sono colorati B (blu) o G (giallo), e dati due interi $b, g \geq 0$, scrivere un algoritmo efficiente che conti il numero di nodi $v$ tali che nel sottoalbero radicato in $v$, escludendo $v$ stesso, vi siano almeno $b$ nodi blu e almeno $g$ nodi gialli.

**Idea.** Si visita l'albero con una DFS post-order (bottom-up): ogni chiamata riceve un nodo $v$ e restituisce al padre una tripla $(\mathit{count},\, n_B,\, n_G)$, dove $n_B$ e $n_G$ sono il numero totale di nodi blu e gialli nel sottoalbero di $v$ **incluso** $v$ stesso (così il padre può contarli tra i propri discendenti), e $\mathit{count}$ è il numero di nodi qualificati trovati nel sottoalbero.

Al nodo $v$ il processing avviene in tre fasi:
1. **Ricorsione**: si ricorre prima su $v.\text{sx}$ e $v.\text{dx}$, ottenendo $(c_{sx}, b_{sx}, g_{sx})$ e $(c_{dx}, b_{dx}, g_{dx})$.
2. **Aggregazione discendenti**: $b_{desc} = b_{sx} + b_{dx}$ e $g_{desc} = g_{sx} + g_{dx}$ rappresentano i discendenti blu e gialli di $v$ (escludono $v$).
3. **Verifica e aggiornamento**: si controlla se $b_{desc} \geq b$ e $g_{desc} \geq g$; il colore di $v$ viene aggiunto **dopo** la verifica, nei valori restituiti al padre.

```pseudo
\begin{algorithm}
\caption{visit($v$, $b$, $g$) → (intero, intero, intero)}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $(0,\; 0,\; 0)$
\EndIf
\State $(c_{sx},\, b_{sx},\, g_{sx}) \gets$ \Call{visit}{$v.\text{sx}$, $b$, $g$}
\State $(c_{dx},\, b_{dx},\, g_{dx}) \gets$ \Call{visit}{$v.\text{dx}$, $b$, $g$}
\State $b_{desc} \gets b_{sx} + b_{dx}$
\State $g_{desc} \gets g_{sx} + g_{dx}$
\State $good \gets 0$
\If{$b_{desc} \geq b$ e $g_{desc} \geq g$}
  \State $good \gets 1$
\EndIf
\State \Return $(c_{sx} + c_{dx} + good,\; b_{desc} + [\,v.\text{col} = B\,],\; g_{desc} + [\,v.\text{col} = G\,])$
\end{algorithmic}
\end{algorithm}
```

La chiamata iniziale è `visit(T.radice, b, g)`; il risultato da restituire è il primo elemento della tripla.

**Complessità:** $T(n) = T(k) + T(n-k-1) + O(1) = O(n)$, dove $k$ è la dimensione del sottoalbero sinistro. Ogni nodo è visitato esattamente una volta con lavoro $O(1)$.

**Trappola:** il nodo non è discendente di sé stesso — la verifica usa $b_{desc} = b_{sx} + b_{dx}$ (il colore di $v$ non è ancora incluso) e il colore di $v$ viene aggiunto soltanto nei valori restituiti al padre. Dimenticare il `return` della tripla causa la perdita di tutte le informazioni aggregate verso il padre.
