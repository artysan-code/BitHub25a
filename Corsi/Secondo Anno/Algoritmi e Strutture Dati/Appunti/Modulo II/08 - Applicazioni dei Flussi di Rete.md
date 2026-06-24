# Applicazioni dei Flussi di Rete
Il **paradigma della riduzione** consiste nel trasformare un problema $P$ in un'istanza di un problema $Q$ già risolto, ricavando la soluzione di $P$ dalla soluzione di $Q$. I problemi di [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] si prestano naturalmente a questo schema: dalla segmentazione di immagini all'eliminazione nel baseball, moltissimi problemi si formulano come ricerca del massimo flusso o del taglio minimo su una rete opportunamente costruita. Questa nota esplora le quattro applicazioni principali del deck (Bipartite Matching, cammini disgiunti, image segmentation, baseball elimination) mostrandone la costruzione della rete e la correttezza della riduzione.
## Schema generale di riduzione al Max-Flow
> [!info] Tecnica — Riduzione al Max-Flow
> Dato un problema $P$, la riduzione al Max-Flow segue quattro passi canonici:
> 1. **Costruire** un grafo di flusso $G' = (V', E')$ che codifica le istanze di $P$ (nodi sorgente $s$, pozzo $t$, capacità degli archi).
> 2. **Calcolare** il flusso massimo $f^*$ in $G'$ tramite Ford-Fulkerson o algoritmi migliori.
> 3. **Interpretare** $f^*$ (o il taglio minimo corrispondente) come soluzione di $P$.
> 4. **Dimostrare** la corrispondenza biunivoca tra le soluzioni di $P$ e i flussi/tagli in $G'$.
>
> La **correttezza** dipende dal **Teorema di integralità**: se tutte le capacità sono intere, esiste un flusso massimo intero; da questo si ricostruisce la soluzione combinatoriale.
## Bipartite Matching
### Definizioni
> [!quote] Definizione — Matching
> Dato un grafo $G = (V, E)$, un sottoinsieme $M \subseteq E$ è un **matching** (abbinamento) se ogni nodo appare in **al più** un arco di $M$. Un matching è **perfetto** se ogni nodo appare in **esattamente** un arco di $M$.

> [!quote] Definizione — Grafo bipartito
> Un grafo $G = (V, E)$ è **bipartito** se i nodi possono essere partizionati in due insiemi disgiunti $L$ e $R$ tali che ogni arco connette un nodo di $L$ con un nodo di $R$. Si scrive $G = (L \cup R, E)$.

Il **problema del Bipartite Matching** chiede: dato $G = (L \cup R, E)$ bipartito, trovare un matching di cardinalità massima.
**Esempio pratico:** $L$ = insieme di studenti, $R$ = insieme di laboratori; un arco $(u, v)$ indica che lo studente $u$ è compatibile con il laboratorio $v$. Un matching massimo assegna il massimo numero di studenti a laboratori compatibili.
### Costruzione della rete
Per risolvere il Bipartite Matching tramite Max-Flow si costruisce il grafo diretto $G' = (L \cup R \cup \{s, t\},\ E')$ come segue:
- Ogni arco $(u, v) \in E$ (con $u \in L$, $v \in R$) diventa un arco **diretto** da $u$ a $v$ con capacità $+\infty$ (o 1 — equivalente poiché i flussi risulteranno 0/1).
- Si aggiunge un arco da $s$ a ogni nodo $u \in L$ con capacità $1$.
- Si aggiunge un arco da ogni nodo $v \in R$ a $t$ con capacità $1$.

```
       capacità 1          capacità 1
  s ─────────► u₁ ──────► v₁' ─────────► t
  │            u₂ ──┐  ┌► v₂' ──────────► t
  │            u₃   └──┘  v₃' ──────────► t
  └──────────► u₄ ──────► v₄' ──────────► t
               L           R
```
### Correttezza (corrispondenza biunivoca)
> [!quote] Teorema — Bipartite Matching = Max-Flow
> Esiste una corrispondenza biunivoca tra i matching di cardinalità $k$ in $G$ e i flussi **interi** di valore $k$ in $G'$.

**Dimostrazione ($\Rightarrow$):** Sia $M$ un matching di cardinalità $k$. Si definisce il flusso $f$ inviando $1$ unità su ciascun cammino $s \to u \to v \to t$ per ogni arco $(u,v) \in M$. Poiché $M$ è un matching, nessun nodo di $L$ né di $R$ è saturato due volte: la conservazione del flusso è rispettata e il valore è $k$.
**Dimostrazione ($\Leftarrow$):** Sia $f$ un flusso intero di valore $k$ in $G'$. Per integralità ogni arco trasporta $0$ o $1$ unità. L'insieme $M = \{(u,v) \in E : f(u,v) = 1\}$ è un matching: ogni $u \in L$ ha un solo arco entrante (da $s$, capacità 1), ogni $v \in R$ ha un solo arco uscente (verso $t$, capacità 1). La cardinalità di $M$ vale $k$ per il lemma del valore del flusso applicato al taglio $(L \cup \{s\}, R \cup \{t\})$.

**Corollario.** Poiché esiste sempre un flusso massimo intero (Teorema di integralità), il flusso massimo in $G'$ corrisponde al matching massimo in $G$.
### Complessità
| Algoritmo | Aumenti | Tempo totale |
|---|---|---|
| Ford-Fulkerson | al più $n = \min(|L|, |R|)$ | $O(mn)$ |

Con Ford-Fulkerson ogni aumentazione incrementa il flusso di 1 (le capacità sono unitarie), quindi al più $n$ aumentazioni, ciascuna $O(m)$ con BFS/DFS sul grafo residuo (cfr. [[08 - Grafi e Visite]]).
### Teorema di König e Teorema di Hall
> [!quote] Teorema — König (1931)
> In un grafo bipartito, la **cardinalità del matching massimo** è uguale alla **dimensione del vertex cover minimo** (minimo insieme di nodi che copre tutti gli archi).

Questo risultato è una conseguenza diretta del teorema Max-Flow Min-Cut: il taglio minimo nella rete $G'$ ha capacità pari alla dimensione del vertex cover minimo, e il flusso massimo vale il matching massimo. Le due quantità coincidono per la dualità flusso-taglio.
> [!quote] Teorema — Hall (condizione di matrimonio, 1935)
> Un grafo bipartito $G = (L \cup R, E)$ ammette un **matching perfetto** che satura tutti i nodi di $L$ se e solo se, per ogni sottoinsieme $S \subseteq L$, il vicinato $N(S) \subseteq R$ soddisfa $|N(S)| \geq |S|$.

> [!example] Domanda tipica d'esame
> **D:** Come si riduce il Bipartite Matching al Max-Flow? Descrivere la costruzione e dimostrare la correttezza.
> **R:** Si costruisce $G'$ aggiungendo sorgente $s$ collegata a ogni nodo di $L$ con capacità 1, pozzo $t$ raggiunto da ogni nodo di $R$ con capacità 1, e si orientano gli archi da $L$ a $R$ con capacità 1 (o $\infty$). Per il Teorema di integralità, il flusso massimo intero in $G'$ è in corrispondenza biunivoca con il matching massimo in $G$: ogni cammino $s \to u \to v \to t$ con flusso 1 corrisponde all'arco $(u,v)$ nel matching.
## Cammini Disgiunti (Disjoint Paths)
### Definizioni
> [!quote] Definizione — Cammini arco-disgiunti
> Due cammini in un grafo sono **arco-disgiunti** (*edge-disjoint*) se non condividono nessun arco. Il problema dei **cammini arco-disgiunti** chiede: dato un grafo $G = (V, E)$ e due nodi $s$ e $t$, trovare il massimo numero di cammini $s \leadsto t$ arco-disgiunti.

La motivazione pratica è la **robustezza delle reti di comunicazione**: quanti cammini indipendenti esistono tra $s$ e $t$? Se $k$ cammini sono arco-disgiunti, la rete resiste alla rimozione di $k-1$ archi qualsiasi.
### Costruzione della rete (grafo diretto)
La riduzione al Max-Flow è immediata: assegnare **capacità 1 a ogni arco** del grafo $G$, mantenendo la stessa struttura. La rete $G'$ coincide con $G$ con tutte le capacità unitarie.

```
         2 ──────► 5
        ↗ ╲       ↗ ╲
       /   ↘     /   ↘
s ──────► 3 ────────► 6 ──────► t
       ╲   ↗     ╲   ↗
        ↘ /       ↘ /
         4 ──────► 7
```

Nel grafo sopra esistono 2 cammini arco-disgiunti: ad esempio $s \to 2 \to 5 \to t$ e $s \to 4 \to 7 \to t$.
### Correttezza
> [!quote] Teorema — Cammini disgiunti = Max-Flow
> Esiste una corrispondenza biunivoca tra $k$ cammini arco-disgiunti $s \leadsto t$ in $G$ e flussi **interi** di valore $k$ in $G'$ (con capacità unitarie).

**Dimostrazione ($\Rightarrow$):** Siano $P_1, \ldots, P_k$ cammini arco-disgiunti. Si pone $f(e) = 1$ se $e$ appartiene ad almeno un $P_i$, altrimenti $f(e) = 0$. Poiché i cammini sono arco-disgiunti, ogni arco è usato al più una volta: le capacità unitarie sono rispettate. La conservazione del flusso vale per ogni nodo intermedio (ogni $P_i$ entra ed esce da ogni nodo interno). Il flusso totale è $k$.
**Dimostrazione ($\Leftarrow$):** Sia $f$ un flusso intero di valore $k$. Si consideri ogni arco $(s, u)$ con $f(s,u) = 1$: per la conservazione esiste un arco $(u, v)$ con $f(u,v) = 1$; continuando si arriva sempre a $t$ (scegliendo sempre un arco inutilizzato). Si ottengono $k$ cammini, non necessariamente semplici — i cicli si possono eliminare in $O(mn)$ con la *flow decomposition*.
> [!quote] Teorema — Menger (1927)
> Il massimo numero di cammini arco-disgiunti $s \leadsto t$ in $G$ è uguale alla **cardinalità del minimo taglio archi** (minimum edge cut): il minimo numero di archi la cui rimozione disconnette $s$ da $t$.

Questo è direttamente il teorema Max-Flow Min-Cut applicato a $G'$: la capacità del taglio minimo (con archi unitari) conta gli archi del minimo taglio, e il flusso massimo conta i cammini arco-disgiunti.
### Cammini disgiunti in grafi non diretti
Per grafi **non orientati**, si sostituisce ogni arco $\{u, v\}$ con **due archi diretti antiparalleli** $(u, v)$ e $(v, u)$, ciascuno con capacità 1. Il risultato di Max-Flow sulla rete così costruita fornisce il massimo numero di cammini arco-disgiunti nel grafo originale non orientato.

> [!warning] Cammini nodo-disgiunti
> Il problema dei **cammini nodo-disgiunti** (vertex-disjoint paths, nessun nodo interno in comune) si riduce al Max-Flow con una tecnica di **node splitting**: ogni nodo $v$ (eccetto $s$ e $t$) viene rimpiazzato da due nodi $v_{in}$ e $v_{out}$ collegati da un arco $(v_{in}, v_{out})$ di capacità 1. Ogni arco $(u,v)$ del grafo originale diventa $(u_{out}, v_{in})$ con capacità $+\infty$. Il massimo flusso nella rete risultante corrisponde al massimo numero di cammini nodo-disgiunti.
### Complessità
Con Ford-Fulkerson su capacità unitarie: al più $n$ aumentazioni (il flusso massimo non può eccedere il grado di $s$), ciascuna $O(m)$, per un totale di $O(mn)$.
> [!example] Domanda tipica d'esame
> **D:** Come si calcola il massimo numero di cammini arco-disgiunti tra $s$ e $t$ in un grafo diretto $G$?
> **R:** Si assegna capacità 1 a ogni arco e si calcola il Max-Flow da $s$ a $t$. Per il Teorema di Menger, il valore del flusso massimo è uguale al massimo numero di cammini arco-disgiunti, ed è anche uguale alla dimensione del minimo taglio archi (minimo numero di archi da rimuovere per disconnettere $s$ da $t$).
## Image Segmentation
### Il problema
**Image segmentation** è il problema di dividere un'immagine in regioni coerenti, tipicamente separando oggetti di interesse (primo piano, *foreground*) dallo sfondo (*background*). È un problema centrale nell'elaborazione delle immagini: un'applicazione concreta è la segmentazione di organi in immagini mediche (es. fegato e vascolarizzazione epatica).
La formulazione di **foreground/background segmentation** è:
- $V$ = insieme dei pixel dell'immagine.
- $E$ = coppie di pixel **vicini** (adiacenti, tipicamente 4-connessione o 8-connessione).
- $a_i \geq 0$: **verosimiglianza** che il pixel $i$ appartenga al foreground.
- $b_i \geq 0$: **verosimiglianza** che il pixel $i$ appartenga al background.
- $p_{ij} \geq 0$: **penalità di separazione** per assegnare i due pixel $i$ e $j$ adiacenti a classi diverse.

L'obiettivo è trovare una partizione $(A, B)$ con $A \cup B = V$, $A \cap B = \emptyset$ che **massimizza**:
$$\text{qualità}(A, B) = \sum_{i \in A} a_i + \sum_{j \in B} b_j - \sum_{\substack{(i,j) \in E \\ |\{A,B\} \cap \{i,j\}| = 2}} p_{ij}$$
dove il termine sottratto penalizza ogni coppia di pixel adiacenti assegnata a classi diverse.
### Trasformazione in minimizzazione
La massimizzazione di $\text{qualità}(A,B)$ è equivalente alla minimizzazione di:
$$\text{costo}(A, B) = \sum_{i \in A} b_i + \sum_{j \in B} a_j + \sum_{\substack{(i,j) \in E \\ |\{A,B\} \cap \{i,j\}| = 2}} p_{ij}$$
(si somma la costante $\sum_i (a_i + b_i)$ e si inverte il segno). Questa è la formulazione del **Min-Cut**.
### Costruzione della rete
Si costruisce il grafo $G' = (V', E')$ come segue:
- Un nodo per ogni pixel $i \in V$.
- La **sorgente** $s$ rappresenta il foreground; il **pozzo** $t$ rappresenta il background.
- Per ogni pixel $i$: arco $(s, i)$ con capacità $a_i$ e arco $(i, t)$ con capacità $b_i$.
- Per ogni coppia di pixel adiacenti $\{i, j\} \in E$: **due archi antiparalleli** $(i, j)$ e $(j, i)$, ciascuno con capacità $p_{ij}$.

```
          a_i              p_ij
    s ──────────► [i] ──────────► [j]
    │              │    ◄──────── /    p_ij
    │    a_j       │             /
    └──────────────────────────►/
                   │             │
              b_i  │             │ b_j
                   ▼             ▼
                   t             t
```

In parole: ogni pixel $i$ riceve un arco da $s$ di capacità $a_i$ (verosimiglianza foreground) e manda un arco a $t$ di capacità $b_i$ (verosimiglianza background). Ogni coppia adiacente $\{i,j\}$ genera due archi antiparalleli $(i \to j)$ e $(j \to i)$ di capacità $p_{ij}$ (penalità di separazione).
### Correttezza (interpretazione del taglio)
> [!quote] Teorema — Image Segmentation = Min-Cut
> Il taglio minimo $(A, B)$ in $G'$ (con $s \in A$, $t \in B$) corrisponde alla partizione dei pixel che minimizza il costo, cioè massimizza la qualità.

**Interpretazione degli archi nel taglio:** Considerando un taglio $(A, B)$ con $A$ = pixel foreground:
- L'arco $(s, i)$ è nel taglio se $i \in B$ (pixel background): contribuisce $a_i$ al costo (penalità per non mettere $i$ nel foreground dove era più verosimile).
- L'arco $(i, t)$ è nel taglio se $i \in A$ (pixel foreground): contribuisce $b_i$ al costo (penalità per non mettere $i$ nel background dove era più verosimile).
- L'arco $(i, j)$ è nel taglio se $i \in A$ e $j \in B$ (pixel adiacenti su lati diversi): contribuisce $p_{ij}$. Poiché gli archi sono antiparalleli, se $i \in A$ e $j \in B$ si conta solo $(i,j)$; se $j \in A$ e $i \in B$ si conta solo $(j,i)$. In entrambi i casi si paga $p_{ij}$ esattamente una volta.

La capacità del taglio è dunque:
$$\text{cap}(A,B) = \sum_{i \in B} a_i + \sum_{i \in A} b_i + \sum_{\substack{(i,j) \in E \\ i \in A,\, j \in B}} p_{ij}$$
che è esattamente il **costo** da minimizzare.

> [!info] Applicazione reale — GrabCut
> L'algoritmo **GrabCut** (Rother, Kolmogorov, Blake, 2004) usa ripetutamente Min-Cut per la segmentazione interattiva di immagini. L'utente disegna un rettangolo attorno all'oggetto; l'algoritmo stima iterativamente i modelli di foreground e background (con distribuzioni gaussiane miste) e risolve Min-Cut ad ogni iterazione.

> [!example] Domanda tipica d'esame
> **D:** In che senso il Min-Cut risolve il problema di Image Segmentation? Come si costruisce la rete?
> **R:** Il problema di massimizzare la qualità della segmentazione si trasforma in minimizzare il costo, che è esattamente la capacità di un taglio $(s$-$t)$ in una rete apposita: sorgente $s$ = foreground, pozzo $t$ = background; arco $(s,i)$ di capacità $a_i$ (verosimiglianza foreground), arco $(i,t)$ di capacità $b_i$ (verosimiglianza background), archi antiparalleli $(i,j)$ e $(j,i)$ di capacità $p_{ij}$ (penalità di separazione). Il Min-Cut taglia gli archi che corrispondono alle assegnazioni sbagliate e alle frontiere tra regioni.
## Baseball Elimination
### Il problema
Il problema di **Baseball Elimination** chiede: dato lo stato attuale della stagione (vittorie accumulate, partite rimanenti, calendario delle sfide tra coppie), il team $z$ può ancora finire la stagione con il numero massimo di vittorie (cioè a pari merito con il primo)?

**Notazione:**
- $S$ = insieme di team; $z \in S$ il team di interesse.
- $w_x$ = vittorie già accumulate dal team $x$.
- $r_x$ = partite rimanenti del team $x$ (contro qualsiasi avversario).
- $r_{xy}$ = numero di partite rimanenti tra il team $x$ e il team $y$.

> [!quote] Definizione — Baseball Elimination
> Il team $z$ è **matematicamente eliminato** se, indipendentemente dall'esito di tutte le partite rimanenti, non può mai terminare la stagione con un numero di vittorie maggiore o uguale a quello di ogni altro team.
### Caso banale
Se $w_z + r_z < w_x$ per qualche team $x$, allora $z$ è eliminato banalmente: anche vincendo tutte le partite restanti, non raggiungerebbe le vittorie già accumulate da $x$. Questo è il caso di cui parlano normalmente i commentatori sportivi — ma **non è l'unico caso**.
**Esempio (dalle slide):**
| Team | Vinte ($w$) | Perse | Da giocare ($r$) | ATL | PHI | NYM | MON |
|---|---|---|---|---|---|---|---|
| Atlanta (0) | 83 | 71 | 8 | — | 1 | 6 | 1 |
| Philly (1) | 80 | 79 | 3 | 1 | — | 0 | 2 |
| New York (2) | 78 | 78 | 6 | 6 | 0 | — | 0 |
| Montreal (3) | 77 | 82 | 3 | 1 | 2 | 0 | — |

Montreal è eliminato **banalmente**: anche vincendo tutte le 3 restanti arriverebbe a 80, ma Atlanta ha già 83 vittorie. Questo è l'unico caso di cui parlano normalmente i commentatori sportivi, ma non è l'unico scenario possibile.
Philly è eliminato **non banalmente**: anche vincendo tutte le 3 restanti arriverebbe a 83 ($= w_z + r_z$). Tuttavia ATL e NYM devono ancora giocarsi 6 partite: qualunque sia l'esito, una delle due arriverà ad almeno $83 + 1 = 84$ vittorie totali, superando Philly. La rimozione di questo caso richiede Max-Flow.
### Costruzione della rete (caso generale)
Si vuole stabilire se il team $z$ può vincere. Si assume w.l.o.g. che $z$ vinca tutte le partite rimanenti: il suo totale massimo è $W^* = w_z + r_z$. L'obiettivo è distribuire le vittorie delle restanti partite tra i team di $S' = S \setminus \{z\}$ in modo che nessun team superi $W^*$.
Si costruisce la rete $G'$ con le seguenti componenti:
- **Sorgente** $s$ e **pozzo** $t$.
- **Nodi-partita** $g_{xy}$ per ogni coppia $x, y \in S'$ (con $r_{xy} > 0$): rappresentano le $r_{xy}$ partite rimanenti tra $x$ e $y$.
- **Nodi-team** $x$ per ogni $x \in S'$: rappresentano ogni team diverso da $z$.
- Arco $(s, g_{xy})$ con capacità $r_{xy}$: le partite tra $x$ e $y$ da distribuire.
- Archi $(g_{xy}, x)$ e $(g_{xy}, y)$ con capacità $+\infty$: le vittorie possono andare a $x$ o $y$.
- Arco $(x, t)$ con capacità $W^* - w_x = w_z + r_z - w_x$: massimo numero di vittorie aggiuntive che $x$ può ottenere senza superare $W^*$.

```
                        ∞               W*-w₁
              ┌──────► [g₁₂] ──────► 1 ──────────────► t
    r₁₂       │          └────∞────► 2 ──────────────► t  W*-w₂
s ────────────┤
    r₁₃       │          ┌────∞────► 1 (stesso nodo)
              └──────► [g₁₃] ──────► 3 ──────────────► t  W*-w₃
    r₂₃       │          ∞
              └──────► [g₂₃] ──────► 2 (stesso nodo)
                          └────∞────► 3 (stesso nodo)
```

Ogni coppia $(x,y)$ con $r_{xy}>0$ contribuisce un nodo-partita $g_{xy}$ con capacità in ingresso $r_{xy}$ e capacità uscenti $\infty$ verso i nodi-team $x$ e $y$. I nodi-team (1, 2, 3, …) sono condivisi tra tutti i nodi-partita che li coinvolgono.
### Correttezza
> [!quote] Teorema — Baseball Elimination = Max-Flow
> Il team $z$ **non è eliminato** se e solo se il massimo flusso in $G'$ **satura tutti gli archi uscenti da** $s$, cioè il flusso massimo è uguale a $\sum_{x,y \in S'} r_{xy}$.

**Interpretazione:**
- Il **Teorema di integralità** garantisce che il flusso massimo è intero: ogni unità di flusso che attraversa il nodo $g_{xy}$ va o a $x$ o a $y$, assegnando quella partita a uno dei due team.
- Le capacità $(x, t)$ con valore $W^* - w_x$ limitano le vittorie aggiuntive di ogni team, assicurando che nessun team superi $W^*$.
- Se il flusso **non** riesce a saturare tutti gli archi uscenti da $s$, significa che non esiste nessun modo di distribuire tutte le partite senza che un team superi $W^*$: $z$ è eliminato.

**Interpretazione del taglio minimo:** Il taglio minimo individua un sottoinsieme $T \subseteq S'$ di team che collettivamente "giocheranno troppe partite":
$$w_z + r_z < \frac{1}{|T|}\left(\sum_{x \in T} w_x + \sum_{x,y \in T} r_{xy}\right)$$
Questa disuguaglianza è la **condizione di eliminazione combinatoria**: il numero medio di vittorie che i team in $T$ devono distribuirsi è superiore a $W^*$.

> [!info] Certificato di eliminazione
> Quando $z$ è eliminato, il taglio minimo fornisce un **certificato esplicito**: il sottoinsieme $T$ di team che "dimostrano" l'eliminazione di $z$. Questo è il tipo di spiegazione che, ad esempio, può apparire in un articolo sportivo: "anche se Philly vincesse tutte le partite, la combinazione Atlanta–New York ne ha già vinte 161 in 6 partite, garantendo che una delle due supererà Philly".

> [!example] Domanda tipica d'esame
> **D:** Come si usa Max-Flow per determinare se un team $z$ è matematicamente eliminato nel baseball?
> **R:** Si costruisce una rete con: nodi-partita $g_{xy}$ per ogni coppia di team $x,y \neq z$ (con arco $s \to g_{xy}$ di capacità $r_{xy}$ e archi $g_{xy} \to x$, $g_{xy} \to y$ di capacità $\infty$); nodi-team $x$ con arco $x \to t$ di capacità $w_z + r_z - w_x$. Il team $z$ non è eliminato se e solo se il Max-Flow satura tutti gli archi uscenti da $s$ (cioè il flusso massimo è $\sum_{x<y} r_{xy}$). Se il flusso non satura, il taglio minimo individua il sottoinsieme $T$ che certifica l'eliminazione.
## Riepilogo: costruzioni delle reti
| Problema | Nodi speciali | Capacità archi | Soluzione letta da |
|---|---|---|---|
| **Bipartite Matching** | $s$, $t$, nodi $L \cup R$ | $s \to L$: 1; $L \to R$: $\infty$; $R \to t$: 1 | Archi $L \to R$ con flusso 1 (matching) |
| **Edge-disjoint Paths** | $s$, $t$ già nel grafo | Tutti gli archi: 1 | Decomposizione del flusso in cammini |
| **Image Segmentation** | $s$ (fg), $t$ (bg), pixel | $s \to i$: $a_i$; $i \to t$: $b_i$; $i \to j$: $p_{ij}$ | Taglio: $A$ = foreground, $B$ = background |
| **Baseball Elimination** | $s$, $t$, nodi-partita, nodi-team | $s \to g_{xy}$: $r_{xy}$; $g_{xy} \to x,y$: $\infty$; $x \to t$: $W^*-w_x$ | Flusso massimo = $\sum r_{xy}$? (no $\Rightarrow$ eliminato) |

> [!info] Collegamento con [[09 - NP-Completezza e Riduzioni]]
> Le riduzioni studiate in questa nota sono **riduzioni polinomiali** verso Max-Flow, un problema risolvibile in tempo polinomiale. Nella [[09 - NP-Completezza e Riduzioni|teoria della NP-completezza]] si studierà invece come ridurre problemi verso problemi presumibilmente intrattabili (NP-difficili). La struttura della riduzione (costruzione + correttezza + complessità) è identica in entrambi i casi.
