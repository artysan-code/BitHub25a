---
tags:
  - algoritmi
  - flussi
  - esercizi
nota: "[[08 - Applicazioni dei Flussi di Rete]]"
---
# Esercizi — Applicazioni dei Flussi di Rete
Palestra della nota [[08 - Applicazioni dei Flussi di Rete]]. Le risposte sono in callout **collassato**: leggi la domanda, rispondi a penna, poi apri.
> [!warning] Nessuna di queste domande viene da una traccia
> Le applicazioni dei flussi — matching bipartito, cammini disgiunti, image segmentation, baseball elimination — **non compaiono** nelle tracce d'esame raccolte, in nessuna posizione. Tutti gli item qui sotto sono quindi `Domanda costruita`, formulati sulla forma che l'Esercizio 2 usa per le riduzioni.
> Questo **non** le rende materiale di scarto: sono programma pieno ed esigibili **all'orale**, dove la riduzione a Max-Flow è una domanda naturale. La formula corretta è «nel campione non è chiesto così, allenalo per l'orale», non «puoi saltarlo».

> [!info] Regola — le riduzioni si espongono sempre in quattro mosse
> Ogni applicazione risponde allo stesso schema, ed è quello da riprodurre a voce o sul foglio:
> 1. **Costruire** la rete che codifica l'istanza (chi sono $s$, $t$, i nodi, e quali capacità portano gli archi);
> 2. **Calcolare** il massimo flusso — o il taglio minimo, se il problema è di minimizzazione;
> 3. **Interpretare** il risultato come soluzione del problema originale;
> 4. **Dimostrare** la corrispondenza biunivoca fra soluzioni del problema e flussi (o tagli) della rete.
>
> Il passo 4 poggia quasi sempre sul **teorema di integralità**: è quello che garantisce che il flusso massimo si possa prendere intero, e quindi che ogni arco a capacità unitaria porti 0 o 1 — cioè che il flusso si legga come una scelta discreta.
## Bipartite Matching
### Riduzione del Bipartite Matching al Max-Flow
> [!question] Domanda costruita — Riduzione del Bipartite Matching al Max-Flow
> **D:** Come si riduce il Bipartite Matching al Max-Flow? Descrivere la costruzione e dimostrare la correttezza.

> [!info]- Risposta modello
> **Costruzione.** Si costruisce $G' = (L \cup R \cup \{s,t\}, E')$: arco $s \to u$ di capacità 1 per ogni $u \in L$, arco $v \to t$ di capacità 1 per ogni $v \in R$, arco $u \to v$ di capacità 1 (o $\infty$, equivalente) per ogni $(u,v) \in E$.
>
> **Correttezza.** Esiste una corrispondenza biunivoca fra matching di cardinalità $k$ in $G$ e flussi interi di valore $k$ in $G'$.
> ($\Rightarrow$) Da un matching $M$ si invia 1 unità su ogni cammino $s \to u \to v \to t$ con $(u,v) \in M$: nessun nodo è saturato due volte perché $M$ è un matching, quindi la conservazione del flusso è rispettata.
> ($\Leftarrow$) Il teorema di integralità garantisce un flusso massimo intero $f$: per le capacità unitarie su $s\to L$ e $R\to t$, ogni arco porta 0 o 1. Si pone $M = \{(u,v) : f(u,v)=1\}$: ogni $u \in L$ e ogni $v \in R$ vi compaiono al più una volta.
>
> **Complessità.** Con Ford-Fulkerson: al più $n = \min(|L|,|R|)$ aumenti (il flusso massimo è limitato dal grado di $s$ o di $t$), ciascuno $O(m)$ con BFS/DFS sul residuo — totale $O(mn)$.
### Teorema di König e collegamento col Max-Flow
> [!question] Domanda costruita — Teorema di König e collegamento col Max-Flow
> **D:** Perché la cardinalità del matching massimo in un grafo bipartito è uguale alla dimensione del vertex cover minimo? Come si collega questo risultato al Max-Flow?

> [!info]- Risposta modello
> **Impostazione.** È il teorema di König (1931): in un grafo bipartito il matching massimo e il vertex cover minimo hanno la stessa cardinalità. La dimostrazione sfrutta la rete $G'$ della riduzione (sorgente $s$, $L$, $R$, pozzo $t$; capacità 1 su $s \to L$ e $R \to t$; capacità $\infty$ su $L \to R$): un taglio minimo non può contenere archi $L \to R$, che hanno capacità infinita, quindi taglia solo archi $s \to L$ o $R \to t$.
>
> **Costruzione del vertex cover.** Sia $(A,B)$ un taglio minimo con $s \in A$. Si definisce $C = (L \setminus A) \cup (R \cap A)$; la tesi è che $C$ è un vertex cover di $G$.
>
> **Dimostrazione (per assurdo).** Sia $(u,v) \in E$ con $u \in L$, $v \in R$ non coperto da $C$: allora $u \notin C$, cioè $u \in A$ (dato che $u \notin L\setminus A$). Se fosse $v \in B$, l'arco $u \to v$ attraverserebbe il taglio — ma è un arco $L \to R$ di capacità $\infty$, che non può comparire in un taglio minimo, assurdo. Dunque $v \in A$, cioè $v \in R \cap A \subseteq C$: contraddice l'ipotesi che $(u,v)$ non fosse coperto.
>
> **Conclusione.** $|C|$ è pari alla capacità del taglio minimo, perché conta solo archi $s \to L$ o $R \to t$ (ciascuno di capacità 1). Per il teorema Max-Flow Min-Cut la capacità del taglio minimo è il flusso massimo, cioè il matching massimo: matching massimo e vertex cover minimo coincidono.
## Cammini Disgiunti
### Massimo numero di cammini arco-disgiunti
> [!question] Domanda costruita — Massimo numero di cammini arco-disgiunti
> **D:** Come si calcola il massimo numero di cammini arco-disgiunti tra $s$ e $t$ in un grafo diretto $G$?

> [!info]- Risposta modello
> **Costruzione.** Si assegna capacità 1 a ogni arco di $G$, lasciando la struttura invariata: la rete $G'$ coincide con $G$.
>
> **Criterio (teorema di Menger).** Il valore del Max-Flow $s \to t$ in $G'$ è uguale sia al massimo numero di cammini arco-disgiunti $s \leadsto t$ sia alla dimensione del minimo taglio archi (minimo numero di archi la cui rimozione disconnette $s$ da $t$) — le due quantità coincidono per il teorema Max-Flow Min-Cut applicato a capacità unitarie.
>
> **Procedura.** Dal flusso massimo intero $f$ (teorema di integralità) si estraggono i cammini seguendo, da ogni arco uscente da $s$ con $f=1$, un arco successivo non ancora usato con $f=1$ fino a raggiungere $t$; gli eventuali cicli residui si eliminano con la *flow decomposition* in $O(mn)$.
>
> **Complessità.** Con Ford-Fulkerson su capacità unitarie: al più $n$ aumenti (il flusso non supera il grado di $s$), ciascuno $O(m)$ — totale $O(mn)$.
### Riduzione dei cammini nodo-disgiunti al Max-Flow
> [!question] Domanda costruita — Riduzione dei cammini nodo-disgiunti al Max-Flow
> **D:** Come si riduce il problema dei cammini nodo-disgiunti al Max-Flow?

> [!info]- Risposta modello
> **Idea.** Un insieme di cammini nodo-disgiunti non può attraversare due volte lo stesso nodo interno, ma la rete originale non ha capacità sui nodi — solo sugli archi. Serve quindi introdurre un collo di bottiglia per ogni nodo.
>
> **Costruzione (node splitting).** Ogni nodo $v \neq s,t$ si sdoppia in $v_{in}$ e $v_{out}$, collegati da un arco interno $(v_{in}, v_{out})$ di capacità 1: al più 1 unità di flusso può attraversare $v$. Ogni arco originale $(u,v)$ diventa $(u_{out}, v_{in})$ con capacità $+\infty$, così i vincoli restano solo sui nodi.
>
> **Correttezza.** Vale lo stesso argomento di corrispondenza biunivoca dei cammini arco-disgiunti: un flusso intero di valore $k$ (teorema di integralità) satura $k$ archi interni distinti, quindi individua $k$ nodi interni distinti attraversati da $k$ cammini $s \leadsto t$ nodo-disgiunti, e viceversa. Il Max-Flow sulla rete sdoppiata vale dunque quanto il massimo numero di cammini nodo-disgiunti nel grafo originale.
>
> **Da riconoscere.** Il node splitting è la mossa generale con cui si trasforma un **vincolo sui nodi** in un **vincolo sugli archi**: vale ogni volta che la traccia limita quante volte un nodo può essere usato.
## Image Segmentation
### Riduzione di Image Segmentation al Min-Cut
> [!question] Domanda costruita — Riduzione di Image Segmentation al Min-Cut
> **D:** In che senso il Min-Cut risolve il problema di Image Segmentation? Come si costruisce la rete?

> [!info]- Risposta modello
> **Trasformazione.** Massimizzare $\text{qualità}(A,B) = \sum_{i\in A} a_i + \sum_{j\in B} b_j - \sum p_{ij}$ equivale a minimizzare $\text{costo}(A,B) = \sum_{i\in A} b_i + \sum_{j\in B} a_j + \sum p_{ij}$: si somma la costante $\sum_i(a_i+b_i)$ e si inverte il segno, il che non cambia chi ottimizza.
>
> **Costruzione della rete.** Sorgente $s$ = foreground, pozzo $t$ = background; per ogni pixel $i$ arco $(s,i)$ di capacità $a_i$ e arco $(i,t)$ di capacità $b_i$; per ogni coppia di pixel adiacenti $\{i,j\}$ due archi antiparalleli $(i,j)$ e $(j,i)$ di capacità $p_{ij}$.
>
> **Correttezza.** In un taglio $(A,B)$ con $s\in A$ (foreground) e $t\in B$ (background): l'arco $(s,i)$ è tagliato se $i\in B$ e contribuisce $a_i$; l'arco $(i,t)$ è tagliato se $i\in A$ e contribuisce $b_i$; fra pixel adiacenti su lati diversi si paga $p_{ij}$ una sola volta grazie all'antiparallelismo. La capacità del taglio coincide quindi esattamente con $\text{costo}(A,B)$: il Min-Cut taglia gli archi corrispondenti alle assegnazioni sbagliate e alle frontiere fra regioni, cioè minimizza il costo e massimizza la qualità.
>
> **Da riconoscere.** È l'unica delle quattro applicazioni che si legge sul **taglio** e non sul flusso: quando il problema è di minimizzazione e chiede di **partizionare**, la risposta è Min-Cut.
## Baseball Elimination
### Eliminazione matematica via Max-Flow
> [!question] Domanda costruita — Eliminazione matematica via Max-Flow
> **D:** Come si usa il Max-Flow per determinare se un team $z$ è matematicamente eliminato nel baseball?

> [!info]- Risposta modello
> **Caso banale (da escludere prima).** Se esiste un team $x$ con $w_x > W^* = w_z + r_z$, $z$ è eliminato banalmente senza costruire alcuna rete: la capacità $x \to t$ pari a $W^* - w_x$ sarebbe negativa, quindi va verificato e scartato a priori.
>
> **Costruzione della rete.** Sorgente $s$, pozzo $t$; un nodo-partita $g_{xy}$ per ogni coppia $x,y \in S' = S\setminus\{z\}$ con $r_{xy}>0$, con arco $s \to g_{xy}$ di capacità $r_{xy}$ e archi $g_{xy}\to x$, $g_{xy}\to y$ di capacità $\infty$; un nodo-team $x$ per ogni $x\in S'$ con arco $x \to t$ di capacità $W^*-w_x$.
>
> **Criterio.** $z$ non è eliminato se e solo se il Max-Flow satura tutti gli archi uscenti da $s$, cioè il flusso massimo vale $\sum_{x,y\in S'} r_{xy}$: per il teorema di integralità ogni unità di flusso su $g_{xy}$ assegna quella partita a $x$ o a $y$ senza far mai superare a nessun team il tetto $W^*$.
>
> **Certificato di eliminazione.** Se il flusso non satura, il taglio minimo individua un sottoinsieme $T \subseteq S'$ tale che $w_z + r_z < \frac{1}{|T|}\left(\sum_{x\in T} w_x + \sum_{x,y\in T} r_{xy}\right)$: i team di $T$ devono complessivamente distribuirsi più vittorie di quante $z$ possa mai raggiungere.
## Riepilogo — le quattro costruzioni
| Problema | Nodi speciali | Capacità archi | Soluzione letta da |
|---|---|---|---|
| **Bipartite Matching** | $s$, $t$, nodi $L \cup R$ | $s \to L$: 1; $L \to R$: $\infty$; $R \to t$: 1 | Archi $L \to R$ con flusso 1 (matching) |
| **Edge-disjoint Paths** | $s$, $t$ già nel grafo | Tutti gli archi: 1 | Decomposizione del flusso in cammini |
| **Image Segmentation** | $s$ (fg), $t$ (bg), pixel | $s \to i$: $a_i$; $i \to t$: $b_i$; $i \to j$: $p_{ij}$ | Taglio: $A$ = foreground, $B$ = background |
| **Baseball Elimination** | $s$, $t$, nodi-partita, nodi-team | $s \to g_{xy}$: $r_{xy}$; $g_{xy} \to x,y$: $\infty$; $x \to t$: $W^*-w_x$ | Flusso massimo $= \sum r_{xy}$? (no $\Rightarrow$ eliminato) |
