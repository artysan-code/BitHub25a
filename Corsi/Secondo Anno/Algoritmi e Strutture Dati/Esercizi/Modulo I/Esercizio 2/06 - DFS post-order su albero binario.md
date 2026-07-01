---
tags:
  - algoritmi
  - strutture-dati
---
# DFS post-order su albero binario
Esercizio di **progettazione** in cui l'informazione **risale** dalle foglie verso la radice (*aggregazione bottom-up*): ogni nodo ha bisogno dei risultati dei due figli per calcolare il proprio, quindi si ricorre **prima** sui figli e si elabora il nodo **dopo** — una DFS in **post-order**. Il canale con cui i figli comunicano col padre è il **valore di ritorno**. Ripasso: [[08 - Grafi e Visite#Visita in profondità — DFS|DFS]], [[05 - Strutture Dati Elementari e Dizionari#Visite di Alberi|visite di alberi]].
## Traccia
> [!question] Traccia — 28/09/2022
> Sia $T$ un albero binario in cui ogni nodo $v$ ha un colore $v.\text{col} \in \{B, G\}$ (Blu o Giallo). Dati due interi $b, g \geq 0$, progettare un algoritmo che restituisca il numero di nodi $v$ di $T$ che hanno **almeno $b$ discendenti blu e almeno $g$ discendenti gialli**. $T$ è rappresentato con record e puntatori (campo $v.\text{col}$, puntatori $v.\text{sx}$ e $v.\text{dx}$). Complessità richiesta $O(n)$.

I **discendenti** di $v$ sono i nodi del sottoalbero radicato in $v$, **escluso $v$ stesso**. Per decidere se $v$ è qualificato servono due numeri che dipendono da ciò che sta **sotto** $v$: quanti discendenti blu e quanti gialli. La condizione è una **congiunzione** (servono entrambe le soglie). L'informazione non è disponibile in discesa — si conosce solo dopo aver esplorato i due sottoalberi — quindi va calcolata *bottom-up*.
## Idea risolutiva
Ogni chiamata su $v$ visita **prima** i due figli e **poi** elabora $v$ (post-order), restituendo al padre una **tripla** $(q,\, nb,\, ng)$ che riassume tutto ciò che del sottoalbero di $v$ serve più in alto:

- $q$ = numero di nodi **qualificati** nel sottoalbero di $v$ (la risposta parziale);
- $nb$ = numero di nodi **blu** nel sottoalbero di $v$, **incluso** $v$;
- $ng$ = numero di nodi **gialli** nel sottoalbero di $v$, **incluso** $v$.

Al nodo $v$ si procede in tre fasi: **(1) ricorsione** sui figli per ottenere le loro triple; **(2) aggregazione** — si sommano i conteggi dei figli per avere blu e gialli fra i *discendenti* di $v$: $nb_{desc} = nb_{sx} + nb_{dx}$, $ng_{desc} = ng_{sx} + ng_{dx}$ (escludono $v$, perché le triple dei figli coprono i loro sottoalberi ma non $v$); **(3) verifica e risalita** — $v$ è qualificato se $nb_{desc} \geq b$ e $ng_{desc} \geq g$, poi si costruisce la tripla da restituire aggiungendo il colore di $v$ **solo ora**. Le soglie $b, g$ sono costanti: le trattiamo come globali. Caso base $v = \text{null}$: tripla $(0, 0, 0)$.
## Pseudocodice
```pseudo
\begin{algorithm}
\caption{conta($v$) → tripla $(q, nb, ng)$ del sottoalbero di $v$; $b, g$ soglie globali}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $(0,\; 0,\; 0)$ \Comment{sottoalbero vuoto}
\EndIf
\State $(q_{sx},\, nb_{sx},\, ng_{sx}) \gets$ \Call{conta}{$v.\text{sx}$}
\State $(q_{dx},\, nb_{dx},\, ng_{dx}) \gets$ \Call{conta}{$v.\text{dx}$}
\State $nb_{desc} \gets nb_{sx} + nb_{dx}$ \Comment{blu fra i discendenti di $v$ ($v$ escluso)}
\State $ng_{desc} \gets ng_{sx} + ng_{dx}$ \Comment{gialli fra i discendenti di $v$ ($v$ escluso)}
\State $good \gets 0$
\If{$nb_{desc} \geq b$ e $ng_{desc} \geq g$}
  \State $good \gets 1$ \Comment{$v$ è qualificato}
\EndIf
\State $q \gets q_{sx} + q_{dx} + good$
\State $nb \gets nb_{desc} + [\,v.\text{col} = B\,]$ \Comment{aggiungo $v$ solo ora, per il padre}
\State $ng \gets ng_{desc} + [\,v.\text{col} = G\,]$
\State \Return $(q,\; nb,\; ng)$
\end{algorithmic}
\end{algorithm}
```

Chiamata iniziale `conta(T.radice)`; la risposta è il **primo campo** $q$ della tripla finale. La scrittura $[\,v.\text{col} = B\,]$ è la **parentesi di Iverson** ($1$ se vero, $0$ altrimenti). Il colore di $v$ entra nei conteggi $nb, ng$ **dopo** il test, così $v$ non viene contato fra i propri discendenti ma è visibile al padre come discendente.
## Complessità
Ogni nodo riceve **una sola** chiamata `conta` e vi svolge lavoro $O(1)$ oltre alle due ricorsioni (due somme per l'aggregazione, un confronto, la costruzione della tripla). Detto $k$ il numero di nodi del sottoalbero sinistro:
$$T(n) = T(k) + T(n-k-1) + O(1) = \Theta(n),$$
la somma dei lavori $O(1)$ sugli $n$ nodi (più $\le n+1$ chiamate su `null`, ognuna $O(1)$). Complessità **$O(n)$**, come richiesto; spazio $O(h)$ per la pila di ricorsione ($h$ = altezza, $O(n)$ nel caso peggiore).
## Correttezza
Il punto delicato: un nodo **non è discendente di sé stesso**, quindi la verifica su $v$ deve usare i soli figli, e il colore di $v$ va aggiunto solo per il padre. Lo si dimostra con un'invariante sul valore di ritorno.

> [!quote] Invariante — la tripla riassume il sottoalbero
> Per ogni nodo $v$, `conta($v$)` restituisce $(q, nb, ng)$ dove $nb$ e $ng$ sono il numero di nodi blu e gialli nel sottoalbero di $v$ **incluso $v$**, e $q$ è il numero di nodi qualificati nel sottoalbero di $v$.

**Dimostrazione** (induzione sulla struttura del sottoalbero). *Base*: $v = \text{null}$, sottoalbero vuoto, tripla $(0,0,0)$: corretto. *Passo*: per ipotesi induttiva le chiamate sui figli restituiscono le triple corrette dei rispettivi sottoalberi. Allora $nb_{desc} = nb_{sx} + nb_{dx}$ conta i blu dei due sottoalberi figli, cioè esattamente i **discendenti** blu di $v$ ($v$ escluso); idem $ng_{desc}$. Dunque $good = 1$ se e solo se $v$ ha $\geq b$ discendenti blu e $\geq g$ gialli — la condizione della traccia. Il conteggio $q = q_{sx} + q_{dx} + good$ somma i qualificati dei due sottoalberi e aggiunge $v$ se qualificato: corretto per il sottoalbero di $v$. Infine $nb = nb_{desc} + [\,v.\text{col}=B\,]$ è il numero di blu nel sottoalbero di $v$ incluso $v$; idem $ng$. L'invariante vale su $v$. $\blacksquare$

Applicata alla radice, l'invariante dà $q = $ numero totale di nodi qualificati di $T$, che è il valore restituito. $\blacksquare$

> [!example] Esempio — la tripla che risale ($b = 1$, $g = 1$)
> ```
>         v1 (B)
>        /    \
>     v2 (G)  v3 (B)
>      /
>    v4 (B)
> ```
> Si cercano i nodi con almeno $1$ discendente blu **e** almeno $1$ giallo.
> - **v4** (B), foglia → discendenti $(0,0)$ → non qualificato → risale $(0,\; 1,\; 0)$.
> - **v3** (B), foglia → risale $(0,\; 1,\; 0)$.
> - **v2** (G): dal figlio sx $(0,1,0)$, dx `null` → $nb_{desc}=1, ng_{desc}=0$ → $0 \geq 1$? no → risale $(0,\; 1,\; 1)$.
> - **v1** (B): dai figli $(0,1,1)$ e $(0,1,0)$ → $nb_{desc}=2, ng_{desc}=1$ → $2 \geq 1$ e $1 \geq 1$ → **qualificato** → risale $(1,\; 3,\; 1)$.
>
> Risultato = primo campo della radice = **1** (solo $v_1$ ha sia un blu sia un giallo fra i discendenti).

> [!warning] Il nodo non è discendente di sé
> La verifica usa $nb_{desc}, ng_{desc}$ (somma dei *soli* figli) e il colore di $v$ si aggiunge **dopo** il test, solo nella tripla per il padre. Aggiungerlo prima conterebbe $v$ fra i propri discendenti, falsando la condizione. Secondo errore tipico: restituire solo $q$ dimenticando $nb, ng$, così il padre perde i conteggi aggregati.
