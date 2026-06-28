---
tags:
  - algoritmi
---
# DFS con stato cumulativo top-down
Casistica tipica dell'Esercizio 3 (Modellazione) di ASD Modulo I; vedi [[Casistiche d'Esame Modulo I]] per la panoramica delle tipologie e [[Piano Esame ASD - Modulo I]] per la checklist. Ripasso: [[08 - Grafi e Visite]].
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
