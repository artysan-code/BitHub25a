---
tags:
  - algoritmi
---
# DFS post-order su albero binario
Casistica dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]] in cui l'informazione **risale** dalle foglie verso la radice (*aggregazione bottom-up*): ogni nodo ha bisogno dei risultati dei due figli per calcolare il proprio, quindi si ricorre **prima** sui figli e si elabora il nodo **dopo** — una DFS in **post-order**. Il canale con cui i figli comunicano col padre è il **valore di ritorno** della funzione. Schemi e checklist in [[Piano Esame ASD - Modulo I]]; ripasso delle visite in [[08 - Grafi e Visite#Visita in profondità — DFS|DFS]] e delle strutture ad albero in [[05 - Strutture Dati Elementari e Dizionari]].

> [!question] Traccia — 28/09/2022
> Dato un albero binario i cui nodi sono colorati B (blu) o G (giallo), e dati due interi $b, g \geq 0$, scrivere un algoritmo efficiente che conti il numero di nodi $v$ tali che nel sottoalbero radicato in $v$, **escludendo** $v$ stesso, vi siano almeno $b$ nodi blu e almeno $g$ nodi gialli.

**Idea.** Per decidere se un nodo $v$ è qualificato servono due numeri che dipendono dai suoi discendenti: quanti blu e quanti gialli stanno **sotto** $v$. Sono informazioni note solo dopo aver esplorato i sottoalberi, quindi si calcolano **bottom-up**: ogni chiamata visita prima i figli e poi restituisce al padre una **tripla** che riassume tutto ciò che serve del sottoalbero di $v$. Le soglie $b$ e $g$ sono i due interi dati dalla traccia: restano costanti per tutta la visita, quindi le trattiamo come globali invece di ripeterle a ogni chiamata.

> [!info] Cosa contiene la tripla $(q,\, nb,\, ng)$ restituita da ogni nodo
> Ogni chiamata su un sottoalbero restituisce tre numeri:
> - $q$ = quanti **nodi qualificati** ci sono nel sottoalbero di $v$ (la risposta parziale, ciò che alla fine ci interessa);
> - $nb$ = **numero di nodi blu** nel sottoalbero di $v$, **incluso** $v$;
> - $ng$ = **numero di nodi gialli** nel sottoalbero di $v$, **incluso** $v$.
>
> I conteggi $nb$ e $ng$ includono $v$ apposta: così il **padre** di $v$, sommando le triple dei figli, ottiene esattamente il numero di blu/gialli fra i propri discendenti. Da non confondere con le soglie $b$ e $g$: $nb, ng$ sono *quanti ne ho trovati*, mentre $b, g$ sono *quanti me ne servono*.

**Le tre fasi al nodo $v$.** (1) **Ricorsione**: si chiama `conta` sui due figli, ottenendo le triple $(q_{sx}, nb_{sx}, ng_{sx})$ e $(q_{dx}, nb_{dx}, ng_{dx})$. (2) **Aggregazione**: si sommano i conteggi dei due figli per ottenere blu e gialli fra i **discendenti** di $v$ — $nb_{desc} = nb_{sx} + nb_{dx}$ e $ng_{desc} = ng_{sx} + ng_{dx}$; questi escludono $v$, perché le triple dei figli includono i figli ma non $v$. (3) **Verifica e risalita**: si controlla la condizione $nb_{desc} \geq b$ e $ng_{desc} \geq g$ (è qui che $v$ può diventare qualificato); poi si costruisce la tripla da restituire, aggiungendo il colore di $v$ **solo ora** ai conteggi destinati al padre.

```pseudo
\begin{algorithm}
\caption{conta($v$) — tripla $(q, nb, ng)$ del sottoalbero di $v$; $b, g$ soglie globali}
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

La chiamata iniziale è `conta(T.radice)`; la risposta cercata è il **primo campo** $q$ della tripla finale. La notazione $[\,v.\text{col} = B\,]$ è la parentesi di Iverson: vale $1$ se $v$ è blu, $0$ altrimenti.

Albero d'esempio (soglie $b = 1$, $g = 1$):

```
        v1 (B)
       /    \
    v2 (G)  v3 (B)
     /
   v4 (B)
```

> [!example] Esempio — la tripla che risale
> Si cerca ogni nodo che abbia, fra i discendenti, almeno $1$ blu **e** almeno $1$ giallo.
> - **v4** (B), foglia: i figli `null` danno $(0,0,0)$ → discendenti $nb_{desc}=0,\ ng_{desc}=0$ → $0 \geq 1$? no → risale $(0,\; 1,\; 0)$.
> - **v3** (B), foglia: come sopra → risale $(0,\; 1,\; 0)$.
> - **v2** (G): dal figlio sinistro arriva $(0,1,0)$, il destro è `null` $(0,0,0)$ → discendenti $nb_{desc}=1,\ ng_{desc}=0$ → $0 \geq 1$? no → non qualificato → risale $(0,\; 1,\; 1)$.
> - **v1** (B): dai figli $(0,1,1)$ e $(0,1,0)$ → discendenti $nb_{desc}=2,\ ng_{desc}=1$ → $2 \geq 1$ e $1 \geq 1$ → **qualificato** → risale $(1,\; 3,\; 1)$.
>
> Risultato = primo campo della tripla della radice = **1** (solo $v_1$ ha sia un blu sia un giallo fra i discendenti).

**Complessità:** $T(n) = T(k) + T(n-k-1) + O(1) = O(n)$, con $k$ dimensione del sottoalbero sinistro. Ogni nodo è visitato una sola volta e fa lavoro $O(1)$ (somme e confronti sulle triple).

**Trappola:** un nodo **non è discendente di sé stesso**. Per questo la verifica usa $nb_{desc}, ng_{desc}$ (somma dei *soli* figli) e il colore di $v$ si aggiunge **dopo** il controllo, solo nella tripla restituita al padre — aggiungerlo prima conterebbe $v$ tra i propri discendenti, falsando la condizione. Secondo errore tipico: restituire solo $q$ (o dimenticare il `return` della tripla), facendo perdere al padre i conteggi $nb, ng$ aggregati.
