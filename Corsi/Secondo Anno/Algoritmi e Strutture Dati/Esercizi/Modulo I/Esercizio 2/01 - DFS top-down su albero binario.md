---
tags:
  - algoritmi
---
# DFS top-down su albero binario
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]] basata su [[08 - Grafi e Visite|visite di alberi binari]]; utile per la preparazione con [[Piano Esame ASD - Modulo I]].
> [!question] Traccia — 14/09/2022
> Dato un albero binario i cui nodi sono colorati di bianco (W), blu (B) o giallo (G), e due interi $b, g \geq 0$, scrivere un algoritmo efficiente che conti il numero di nodi $v$ tali che $v$ abbia almeno $b$ antenati blu **oppure** almeno $g$ antenati gialli.

**Idea.** Si visita l'albero con una DFS top-down (pre-order): ogni chiamata riceve dal padre i contatori `blue_cnt` e `yellow_cnt`, che rappresentano il numero di antenati blu e gialli di $v$ **già incontrati** sul cammino dalla radice fino al padre di $v$ — il nodo $v$ stesso **non** è incluso. Il processing di $v$ avviene in tre fasi:
1. **Controllo**: si verifica $b\_cnt \geq b$ oppure $g\_cnt \geq g$ usando i contatori ricevuti; se la condizione vale, $v$ contribuisce $1$ al risultato.
2. **Aggiornamento**: si costruiscono i contatori da passare ai figli, aggiungendo il colore di $v$ stesso — $b' = b\_cnt + [\,v.\text{col} = B\,]$ e $g' = g\_cnt + [\,v.\text{col} = G\,]$.
3. **Ricorsione**: si ricorre su entrambi i sottoalberi con i contatori aggiornati e si somma il loro contributo.

Il caso base è $v = \text{null}$, che restituisce $0$.

```pseudo
\begin{algorithm}
\caption{contaQualificati($v$, $b\_cnt$, $g\_cnt$, $b$, $g$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\State $r \gets 0$
\If{$b\_cnt \geq b$ oppure $g\_cnt \geq g$}
  \State $r \gets 1$
\EndIf
\State $b' \gets b\_cnt + [\,v.\text{col} = B\,]$
\State $g' \gets g\_cnt + [\,v.\text{col} = G\,]$
\State \Return $r + {}$\Call{contaQualificati}{$v.\text{sx},\, b',\, g',\, b,\, g$} $+$ \Call{contaQualificati}{$v.\text{dx},\, b',\, g',\, b,\, g$}
\end{algorithmic}
\end{algorithm}
```

La chiamata iniziale è `contaQualificati(radice, 0, 0, b, g)`: la radice non ha antenati, quindi entrambi i contatori partono da $0$.

**Complessità:** $T(n) = T(k) + T(n-k-1) + O(1) = O(n)$, dove $k$ è la dimensione del sottoalbero sinistro. Ogni nodo viene visitato esattamente una volta e il lavoro per nodo è $O(1)$.

**Trappola:** aggiornare i contatori ($b'$, $g'$) **prima** di verificare la condizione su $v$ comporta di contare $v$ tra i propri antenati, sovrastimando il numero di nodi qualificati. I contatori vanno prima controllati, poi aggiornati e infine passati ai **figli**, non al nodo corrente. Un secondo errore frequente è dimenticare il `\Return $0$` nel caso base $v = \text{null}$, oppure omettere la ricorsione su uno dei due rami.
