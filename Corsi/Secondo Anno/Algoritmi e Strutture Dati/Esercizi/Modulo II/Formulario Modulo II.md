---
tags:
  - algoritmi
  - greedy
  - union-find
  - mst
  - dp
  - flussi
  - np-completezza
  - esercizi
nota:
  - "[[01 - Greedy e Interval Scheduling]]"
  - "[[02 - Union-Find]]"
  - "[[03 - Minimum Spanning Tree]]"
  - "[[04 - Programmazione Dinamica I (Weighted Independent Set)]]"
  - "[[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]"
  - "[[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]]"
  - "[[07 - Flussi di Rete (Max-Flow e Min-Cut)]]"
  - "[[08 - Applicazioni dei Flussi di Rete]]"
  - "[[09 - NP-Completezza e Riduzioni]]"
---
# Formulario — ASD Modulo II
Solo ciò che si scrive sul compito: **definizioni** in forma d'esame, **enunciati**, **scheletri di dimostrazione** (i passi, non la prosa), **corollari**, **costi**. Niente esempi, niente metodo, niente esercizi. Fonte: slide del prof. Gualà; ciò che va oltre è marcato *(extra, non da slide)*.
Per §01-§03 e §07-§09 (Esercizi 1 e 2) il taglio è teoria; per §04-§06 (Esercizio 3) sono definizioni dei problemi, ricorrenze e costi. Notazione: $n = |V|$, $m = |E|$; $T$ è identificato col suo insieme di archi; $\text{OPT}$ è sempre il **valore** ottimo, non l'insieme che lo realizza.

## 01 · Greedy e Interval Scheduling
### Interval Scheduling
> [!quote] Definizione — Interval Scheduling (forma d'esame)
> - **Input**: $n$ intervalli $I_1,\ldots,I_n$, con $I_i$ di inizio $s_i$ e fine $f_i$.
> - **Ammissibile**: un sottoinsieme $S$ di intervalli a due a due **compatibili** ($f_i \leq s_j$ oppure $f_j \leq s_i$).
> - **Misura (max)**: $|S|$.

Criteri: earliest start ✗ · **earliest finish ✓** · shortest interval ✗ · fewest conflicts ✗.
**EFT-first**: ordina per $f(j)$ crescente, prendi $j$ se $s(j) \geq f(j^*)$ con $j^*$ ultimo selezionato (test $O(1)$). Costo **$O(n\log n)$**, dominato dall'ordinamento.

> [!quote] Lemma — Greedy stays ahead
> Greedy $i_1,\ldots,i_k$ e ottimo $j_1,\ldots,j_m$, ordinati per tempo di fine: $f(i_r) \leq f(j_r)$ per ogni $r$.
> **Dim. (induzione su $r$).** *Base*: il greedy prende il finish time minimo assoluto. *Passo*: $s(j_r) \geq f(j_{r-1}) \geq f(i_{r-1})$ per ip. induttiva, quindi $j_r$ era disponibile al greedy al passo $r$, che sceglie il finish minimo. $\square$

> [!quote] Teorema — Ottimalità di EFT-first
> EFT-first restituisce un insieme compatibile di cardinalità massima.
> **Dim. (per assurdo).** Sia $m > k$. Per il lemma $f(i_k) \leq f(j_k)$; l'ottimo ha $j_{k+1}$ con $s(j_{k+1}) \geq f(j_k) \geq f(i_k)$, dunque compatibile con **tutti** i job del greedy, che allora non si sarebbe fermato a $k$. $\square$
### Interval Partitioning
> [!quote] Definizione — Interval Partitioning (forma d'esame)
> - **Input**: $n$ intervalli $I_i = [s_i, f_i)$.
> - **Ammissibile**: partizione in classi $C_1,\ldots,C_d$ con intervalli a due a due compatibili dentro ogni classe (equivalentemente: due intervalli sovrapposti hanno etichette diverse).
> - **Misura (min)**: il numero di classi $d$.

> [!quote] Definizione — Profondità (depth) e lower bound
> $$\text{depth} = \max_{t}\bigl|\{I_i : s_i < t < f_i\}\bigr|$$
> È il **picco di contemporaneità**, non il numero di conflitti. Ogni soluzione ammissibile usa $\geq \text{depth}$ classi: nell'istante di picco quegli intervalli stanno in classi distinte.

Criterio corretto: **earliest start time** (gli altri tre hanno controesempi).
**EST-first**: ordina per $s(j)$, assegna a una classe compatibile se esiste, altrimenti aprine una nuova. Implementazione: **min-heap** di classi con chiave = finish dell'ultima lezione (`FIND-MIN`, poi `INCREASE-KEY` o `INSERT`); basta il min-heap perché se la classe più favorevole non accoglie $j$, nessuna lo fa. Costo **$O(n\log n)$**.

> [!quote] Teorema — Ottimalità di EST-first
> EST-first alloca esattamente $\text{depth}$ classi.
> **Dim. (doppia disuguaglianza).** *($d \geq \text{depth}$)* La soluzione è ammissibile e ogni ammissibile usa $\geq \text{depth}$ classi. *($\text{depth} \geq d$)* Quando si apre la $d$-esima classe per $j$, $j$ è incompatibile con l'ultima lezione di ciascuna delle $d-1$ classi aperte, che quindi finiscono dopo $s(j)$; processando per inizio crescente iniziano anche $\leq s(j)$. Quelle $d-1$ più $j$ sono attive in $s(j)+\epsilon$. $\square$

**Perché ordini diversi**: IS ha una risorsa sola e massimizza i job → conviene liberarla presto, *finish time*. IP serve tutte le lezioni e minimizza le risorse → conta quante devono coesistere, *start time*, e il picco è la depth.
Due tecniche di dimostrazione *(nome extra, contenuto da slide — Kleinberg-Tardos §4.1)*: **greedy stays ahead** (una misura $\phi(r)$ in cui il greedy non è mai indietro) ed **exchange argument** (si trasforma un ottimo nella soluzione greedy con scambi che non peggiorano).

## 02 · Union-Find
> [!quote] Definizione — Le tre operazioni
> - **`makeSet(x)`**: crea l'insieme $\{x\}$ di nome $x$.
> - **`union(nome A, nome B)`**: fonde i due insiemi in uno di nome **$A$**, distrugge i vecchi.
> - **`find(elemento x) → nome`**: restituisce il nome dell'insieme che contiene $x$.
>
> Le firme distinguono **nomi** ed **elementi**: coincidono alla creazione, divergono dopo una union. Con $n$ elementi si eseguono al più $n-1$ union.

**QuickFind** — alberi di **altezza 1**, radice = nome. `find` $O(1)$; `union` rietichetta tutte le foglie del secondo argomento, $O(n)$. Caso peggiore da costruire: $\text{union}(2,1), \text{union}(3,2), \ldots \Rightarrow 1+2+\cdots+(n-1) = \Theta(n^2)$.
**QuickUnion** — alberi di altezza qualsiasi, radice = rappresentante. `union` $O(1)$; `find` risale il cammino, $O(n)$. La stessa sequenza degenera in una lista: $m$ find costano $O(mn)$.
**Union by size** — si attacca il più piccolo al più grande. In QuickFind l'altezza resta 1 e migliora solo il costo **ammortizzato** della union; in QuickUnion riduce l'**altezza**.

> [!quote] Proprietà — Argomento del raddoppio (QuickFind + union by size)
> Ogni volta che un elemento cambia etichetta la size del suo insieme almeno **raddoppia**: dopo $k$ cambi sta in un insieme di $\geq 2^k$ elementi, e da $2^k \leq n$ segue $k \leq \log_2 n$. Le union costano $O(n\log n)$ sull'intera sequenza, il totale $O(m + n\log n)$.

> [!quote] Lemma — Altezza in QuickUnion con union by size
> Un albero con $s$ nodi e altezza $h$ soddisfa $s \geq 2^h$; quindi `find` costa $O(\log n)$ **nel caso peggiore** e la sequenza $O(n + m\log n)$. *(Sulla slide è lasciato come esercizio.)*
> **Dim. (induzione sulle union).** Nasce con $s=1$, $h=0$. Unendo $(s_1,h_1)$ e $(s_2,h_2)$ con $s_1 \geq s_2$: se $h_2 < h_1$ l'altezza non cresce e la size aumenta; se $h_2 \geq h_1$ la nuova altezza è $h_2+1$ e $s_1+s_2 \geq 2s_2 \geq 2^{h_2+1}$. $\square$

**Compressione dei cammini** — durante `find(x)` **tutti** i nodi del cammino diventano figli diretti della radice; non cambia né radice né nome, solo i puntatori al padre.
**Union by rank** *(extra, non da slide)* — intero sulla radice, limite superiore all'altezza: $0$ alla creazione, si attacca il rank minore sotto il maggiore, e **solo** a parità si incrementa di 1. Un albero di rank $r$ ha $\geq 2^r$ nodi. Si preferisce alla size **quando c'è la compressione**: questa abbassa l'altezza senza cambiare il numero di elementi, quindi la size smette di indicare l'altezza mentre il rank resta un limite superiore valido.

> [!quote] Teorema — Tarjan & van Leeuwen
> Con union by rank (o by size) **e** compressione dei cammini, $n$ `makeSet`, $n-1$ `union` e $m$ `find` costano $O\bigl(n + m\,\alpha(m+n, n)\bigr)$, con $\alpha$ inversa di Ackermann. Poiché $\alpha(m,n) \leq 4$ per ogni $n < 2^{10^{80}}$, è **praticamente lineare**.

| Implementazione | `makeSet` | `union` | `find` | Sequenza completa |
|---|---|---|---|---|
| QuickFind | $O(1)$ | $O(n)$ p.p. | $O(1)$ | $O(m + n^2)$ p.p. |
| QuickFind + union by size | $O(1)$ | $O(n)$ p.p., $O(\log n)$ amm. | $O(1)$ | $O(m + n\log n)$ |
| QuickUnion | $O(1)$ | $O(1)$ | $O(n)$ p.p. | $O(mn)$ p.p. |
| QuickUnion + union by size | $O(1)$ | $O(1)$ | $O(\log n)$ | $O(n + m\log n)$ |
| QuickUnion + rank + compressione | $O(1)$ | $O(1)$ | $O(\alpha(m,n))$ amm. | $O(n + m\,\alpha(m+n,n))$ |

*(p.p. = caso peggiore · amm. = ammortizzato)*

> [!warning] Le due trappole ricorrenti
> **Ammortizzato contro caso peggiore**: la singola `union` in QuickFind resta $\Theta(n)$; è la *sequenza* a costare $O(m+n\log n)$.
> **Union-Find travestita da Kruskal** (08/09/2026): in Kruskal il costo si somma su tre voci — ordinamento $O(m\log n)$, $O(m)$ find, $n-1$ union — e **domina l'ordinamento**: rendere la struttura più veloce non velocizza Kruskal.

> [!quote] Proprietà — Lower bound $\Omega(m+n)$ *(non sulle slide; chiesto il 16/07/2024 e il 18/02/2025)*
> Qualunque struttura dati, su $n$ `makeSet`, $n-1$ `union` e $m$ `find`, richiede $\Omega(m+n)$: le makeSet devono creare $n$ insiemi, le find devono rispondere $m$ volte.

## 03 · Minimum Spanning Tree
### Problema e struttura
> [!quote] Definizione — MST (forma d'esame)
> - **Input**: grafo non orientato, **connesso**, pesato $G=(V,E)$ con pesi reali $c_e$.
> - **Ammissibile**: uno spanning tree $T=(V,F)$, $F \subseteq E$, che raggiunge tutti i vertici ($n-1$ archi).
> - **Misura (min)**: $c(T) = \sum_{e \in F} c_e$.
>
> Le due voci che saltano scrivendo di fretta: **connesso** nell'input e la **misura**.

- Su $n$ vertici, *connesso* · *aciclico* · *$n-1$ archi*: **due qualsiasi implicano la terza**.
- Pesi **reali, anche negativi**: per l'MST non è un problema (a differenza dei cammini minimi).
- La minimalità è relativa **agli altri spanning tree**, non a sottografi arbitrari.
- Pesi in $\{1,2\}$: ogni spanning tree costa fra $n-1$ e $2n-2$; costo **esattamente** $n-1$ richiede che il sottografo dei soli archi di peso 1 sia connesso e ricoprente — vincolo di *connettività*, non di cardinalità.
- **Cayley**: $K_n$ ha esattamente $n^{n-2}$ spanning tree.
### Unicità
> [!quote] Proprietà — Pesi distinti ⇒ MST unico
> **Dim. (per assurdo, differenza simmetrica).** Siano $T_1 \neq T_2$ due MST.
> 1. Sia $e$ l'arco di peso **minimo** in $T_1 \triangle T_2$ (unico, pesi distinti), w.l.o.g. $e \in T_1 \setminus T_2$.
> 2. $T_2 \cup \{e\}$ crea un ciclo $C$; non tutti gli archi di $C \setminus \{e\}$ stanno in $T_1$, altrimenti $T_1$ avrebbe un ciclo.
> 3. Esiste dunque $f \in C \cap (T_2 \setminus T_1) \subseteq T_1 \triangle T_2$.
> 4. Per minimalità di $e$ e pesi distinti: $c_f > c_e$.
> 5. $T_2 \cup \{e\} \setminus \{f\}$ è uno spanning tree di peso $< c(T_2)$: assurdo. $\square$
>
> L'ipotesi serve al **passo 4**: con pesi ripetuti si ottiene solo $c_f \geq c_e$, cioè un **altro MST di pari costo**. Pesi distinti è **sufficiente ma non necessario**.

> [!quote] Criterio — Caratterizzazione dell'unicità
> $T$ è l'**unico** MST **se e solo se** ogni arco $f \notin T$ è di peso **strettamente** massimo nel proprio ciclo fondamentale (il ciclo che $f$ forma con $T$). Se un $f$ pareggia con un arco del suo ciclo, lo scambio dà un secondo MST di pari costo; viceversa ogni scambio aumenta strettamente il costo.
### Cicli, tagli, cutset
> [!quote] Definizione — Ciclo, taglio, cutset
> Un **ciclo** è un insieme di archi $a$-$b$, $b$-$c$, …, $z$-$a$ con nodi a due a due distinti.
> Un **taglio** è un sottoinsieme $S \subseteq V$; il suo **cutset** è
> $$D = \{\, e = \{u,v\} \in E \;:\; |e \cap S| = 1 \,\}$$
> cioè gli archi con **esattamente un** estremo in $S$. Significativo solo per $\emptyset \neq S \subset V$; $S$ **non deve essere connesso**, e il cutset non ha verso.

> [!quote] Proprietà — Intersezione ciclo-cutset
> Un ciclo $C$ e un cutset $D$ si intersecano in un numero **pari** di archi (anche zero).
> **Dim.** Percorrendo $C$ da un suo nodo e tornandovi, gli archi di $C \cap D$ sono esattamente quelli che **attraversano** il confine; essendo il percorso chiuso, le uscite da $S$ eguagliano le entrate: $|C \cap D| = 2k$. $\square$
> **Pari non vuol dire due**: può essere $0, 2, 4, \ldots$
### Cut property e Cycle property
> [!quote] Proprietà — Cut property
> Sia $\emptyset \neq S \subset V$ e sia $e$ **un** arco di costo minimo del cutset di $S$. Allora **esiste un** MST che **contiene** $e$.
> **Dim. (scambio).** Sia $T^*$ un MST; se $e \in T^*$ è fatto, altrimenti $e=(u,v)$ con $u \in S$, $v \notin S$:
> 1. $T^* \cup \{e\}$ crea un ciclo $C$.
> 2. $e \in C \cap D$, e $|C \cap D|$ è **pari** quindi $\geq 2$: esiste $f \in C \cap D$, $f \neq e$, con $f \in T^*$.
> 3. $T' = T^* \cup \{e\} \setminus \{f\}$ è uno spanning tree (togliere un arco da un ciclo non disconnette, restano $n-1$ archi).
> 4. $f$ attraversa il taglio ed $e$ è minimo nel cutset: $c_e \leq c_f$, dunque $c(T') \leq c(T^*)$.
> 5. $T^*$ è MST, quindi $c(T') = c(T^*)$: $T'$ è un MST che contiene $e$. $\square$
>
> I due passaggi che non possono mancare: la **parità** (garantisce l'esistenza di $f$) e la **chiusura** $c(T')=c(T^*)$ (dalla sola disuguaglianza non segue l'ottimalità). Non è per assurdo: si **costruisce** il testimone.
> **Corollario (minimo stretto)**: se $e$ è l'unico arco di peso minimo del taglio, appartiene a **ogni** MST.

> [!quote] Proprietà — Cycle property
> Sia $C$ un ciclo e $f$ **un** arco di costo massimo di $C$. Allora **esiste un** MST che **non contiene** $f$.
> **Dim. (scambio).** Sia $T^*$ un MST con $f \in T^*$:
> 1. $T^* \setminus \{f\}$ si spezza in due componenti; sia $S$ i nodi di una, con cutset $D$.
> 2. $f \in C \cap D$ e $|C \cap D| \geq 2$: esiste $e \in C \cap D$, $e \neq f$.
> 3. $T' = T^* \cup \{e\} \setminus \{f\}$ è uno spanning tree ($e$ attraversa il taglio e ricollega).
> 4. $e \in C$ ed $f$ è massimo in $C$: $c_e \leq c_f$, dunque $c(T') \leq c(T^*)$.
> 5. $T^*$ è MST, quindi $c(T') = c(T^*)$. $\square$
>
> Lo scambio è **identico** nelle due: cambia da dove viene $c_e \leq c_f$ (minimalità nel taglio / massimalità nel ciclo) e quale oggetto si crea per primo (ciclo / taglio).
> **Corollario (massimo stretto)**: se $f$ è l'unico arco di peso massimo del ciclo, non appartiene ad **alcun** MST.

> [!warning] Sono enunciati esistenziali
> «**Esiste un** MST che contiene $e$», «**esiste un** MST che non contiene $f$». Le forme «appartiene a ogni MST» / «non appartiene ad alcun MST» valgono **solo** con minimo o massimo **stretto**. Le tracce costruiscono le affermazioni false proprio su questo, e su **varianti gemelle a negazione invertita**: riconoscerle scarta due opzioni su cinque in un colpo.

> [!info] Mappa — quale proprietà per quale arco *(extra, non da slide)*
> | L'arco è… | Proprietà | Garantisce | Non garantisce |
> |---|---|---|---|
> | **dentro $T$** | cut property | è il minimo del **taglio** indotto dalla sua rimozione | nulla sui cicli |
> | **fuori da $T$** | cycle property | è il massimo del **ciclo fondamentale** indotto da $T$ | nulla sugli altri cicli che lo contengono |
>
> Il duale incrociato **non esiste**.
### Dalla proprietà locale alla correttezza globale
> [!quote] Invariante — Estendibilità
> Detto $F$ l'insieme degli archi selezionati dopo un numero qualsiasi di passi: **esiste un MST $T$ con $F \subseteq T$**.
> **Dim. (induzione sugli archi selezionati).** *Base*: $F=\emptyset$ è in qualunque MST, che esiste perché $G$ è connesso. *Passo*: sia $F \subseteq T$ e $e$ il prossimo arco, minimo di un taglio $(S, V\setminus S)$ **che nessun arco di $F$ attraversa**. Se $e \in T$ si conclude; altrimenti la cut property dà $f \in C \cap D$ con $c_e \leq c_f$ e $T' = T \cup \{e\} \setminus \{f\}$ MST; poiché $f$ attraversa il taglio e nessun arco di $F$ lo attraversa, $f \notin F$, dunque $F \cup \{e\} \subseteq T'$. *Conclusione*: alla terminazione $|F| = |T| = n-1$ e $F \subseteq T$, quindi $F = T$. $\square$
>
> Serve perché le due property sono **esistenziali su un singolo arco**: applicarle $n-1$ volte darebbe $n-1$ MST potenzialmente diversi. Il passo cruciale è $f \notin F$.
### Algoritmi
> [!info] Kruskal · Reverse-Delete · Prim
> **Kruskal** — da $T=\emptyset$, archi in ordine **crescente**, si inserisce $e$ a meno che non crei un ciclo (test «stessa componente?» con Union-Find).
> **Reverse-Delete** — da $T=E$, archi in ordine **decrescente**, si cancella $e$ a meno che non disconnetta. Correttezza dalla **cycle property**.
> **Prim** — da una sorgente $s$, si aggiunge l'arco di costo minimo con **esattamente un estremo** nell'albero corrente: $n$ `insert`, $n$ `deleteMin`, $\leq m$ `decreaseKey`, chiave = costo dell'arco di attacco.

> [!quote] Proprietà — Correttezza di Kruskal (usa entrambe le property)
> - **Arco accettato** $e=(u,v)$ — *cut property* con $S =$ componente connessa di $u$ nella foresta corrente. Un arco del cutset più leggero di $e$ sarebbe già stato esaminato: se accettato starebbe **dentro** $S$, se scartato avrebbe i due estremi nella stessa componente **anche adesso** (le componenti si fondono, non si spezzano mai). In entrambi i casi non attraverserebbe il taglio.
> - **Arco scartato** $f=(x,y)$ — *cycle property*: $x,y$ già connessi, quindi $f$ chiude un ciclo col cammino presente, i cui archi sono stati accettati **prima** e costano $\leq c_f$.
>
> **Prim** — il taglio da esibire è $S =$ **nodi già raggiunti**; l'arco scelto è minimo nel cutset e nessun arco già selezionato lo attraversa. Slide: «*immediate consequence of the cut property, used exactly $n-1$ times*».

| Prim — coda con priorità | Insert | DeleteMin | DecreaseKey | Totale |
|---|---|---|---|---|
| Array non ordinato | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| Heap binario | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m\log n)$ |
| Heap di Fibonacci | $O(1)$ | $O(\log n)$ | $O(1)$ amm. | $O(m + n\log n)$ |

**Kruskal** $= O(m\log m) = O(m\log n)$ per l'ordinamento ($m \leq \binom{n}{2}$) più $O(m)$ find e $n-1$ union: **totale $O(m\log n)$, dominato dall'ordinamento**. È lineare solo se gli archi arrivano già ordinati o sono ordinabili in tempo lineare.

> [!warning] Il $\log$ moltiplicativo e quello additivo
> In Kruskal il $\log n$ è **moltiplicativo** e non sparisce mai; in Prim-Fibonacci è **additivo**, quindi con $m = \Theta(n\sqrt n)$ il termine $n\log n$ è assorbito e Prim è $\Theta(m)$, lineare. Da qui le risposte **opposte** alle due domande gemelle (Kruskal 09/09/2025 falsa · Prim 23/09/2025 vera).

> [!warning] Prim non è Dijkstra, e l'MST non è l'albero dei cammini minimi
> Stessa scansione, **chiave diversa**: Prim usa il peso dell'**arco di attacco**, Dijkstra la **distanza dalla sorgente**. Se tutti i pesi sono **uguali** ogni albero dei cammini minimi è anche un MST, ma già con pesi in $\{1,2\}$ l'implicazione cade. Con **pesi distinti** l'MST è unico, quindi Kruskal e Prim calcolano lo **stesso** albero, qualunque sia la sorgente.
### Perturbazione dei pesi *(extra, non da slide)*
> [!quote] Lemma — Monotonia
> Se per ogni spanning tree $U$ vale $c'(T) - c(T) \leq c'(U) - c(U)$, allora $T$ MST di $G$ resta MST di $G'$.
> **Dim.** $c'(T) = c(T) + [c'(T)-c(T)] \leq c(U) + [c'(U)-c(U)] = c'(U)$. $\square$

| Perturbazione | Variazione di $T$ | Variazione di un $U$ qualsiasi | Esito |
|---|---|---|---|
| abbasso $c_e$ di $\Delta$, $e \in T$ | $-\Delta$ | $-\Delta$ se $e \in U$, $0$ altrimenti | $T$ resta MST |
| alzo $c_f$ di $\Delta$, $f \notin T$ | $0$ | $0$ se $f \notin U$, $+\Delta$ altrimenti | $T$ resta MST |
| $+1$ su ogni arco | $+(n-1)$ | $+(n-1)$, uguale per tutti | $T$ resta MST |
| $+1$ su ogni arco, **min-cut** | — | i tagli non hanno tutti la stessa cardinalità | il min-cut **può cambiare** |

**Famiglia sensitivity, lemma unico**: *se il costo di $T$ non aumenta più di quello di qualunque altro spanning tree, $T$ resta MST* — le quattro istanze si derivano da lì.
### Applicazione: clustering di massima spaziatura
> [!quote] Definizione e teorema — $k$-clustering di massima spaziatura
> Dato $U$ di $n$ oggetti con distanza $d$ (non negativa, simmetrica, nulla solo fra un oggetto e sé), un **$k$-clustering** è una suddivisione in $k$ gruppi non vuoti; la **spaziatura** è la minima distanza fra punti in cluster diversi, da **massimizzare**.
> **Teorema (single-linkage)**: eliminando i $k-1$ archi più costosi di un MST si ottiene il $k$-clustering di spaziatura massima, pari al costo $d^*$ del $(k-1)$-esimo arco più costoso.
> **Dim.** Sia $\mathcal{C} \neq \mathcal{C}^*$ un altro $k$-clustering: esistono $p_i, p_j$ nello stesso cluster di $\mathcal{C}^*$ ma in cluster diversi di $\mathcal{C}$. Il cammino MST che li unisce passa da un cluster all'altro, quindi contiene un arco $(p,q)$ con estremi in cluster diversi di $\mathcal{C}$; quell'arco non è stato eliminato, dunque costa $\leq d^*$ e la spaziatura di $\mathcal{C}$ è $\leq d^*$. $\square$

La procedura **è** Kruskal fermato a $k$ componenti; eseguito fino in fondo dà un clustering **gerarchico**.

## 04 · Programmazione Dinamica — impianto dell'Esercizio 3
> [!quote] Le due condizioni
> **Sottostruttura ottima** (senza, la ricorrenza è sbagliata) e **sottoproblemi sovrapposti** (senza, la tabella non serve). È la seconda a distinguere la DP dal divide-et-impera: in Merge Sort i sottoproblemi sono **disgiunti**.

> [!info] I cinque passi
> 1. **Sottoproblema** — cosa indicizza la tabella e cosa significa *esattamente* una cella, a parole prima che in formula; dichiara **quanti** sono.
> 2. **Ricorrenza** — la formula, i casi, e una riga: i casi sull'ultimo elemento sono **esaustivi** e in ciascuno il residuo è ottimo (*cut-and-paste*).
> 3. **Caso base.**
> 4. **Ordine di riempimento e dove si legge la risposta.**
> 5. **Complessità** — celle $\times$ costo per cella, tempo e spazio.
>
> Il passo difficile è **sempre il primo**. Priorità se il tempo stringe: sottoproblemi → ricorrenza → complessità. **Lo pseudocodice non è mai richiesto** dalla traccia (0 su 24).

> [!warning] Dove si legge la risposta — quasi mai «l'ultima cella»
> Non si risponde guardando la tabella, si risponde **rileggendo il passo 1**: quali celle sono soluzioni *complete e ammissibili*? Se la definizione contiene un vincolo («che termina con $i$», «con esattamente $r$ rosse», «con $v_i$ non ancora dominato»), va **sciolto** con un min/max finale. Quattro motivi: stato vincolato · insieme di arrivi più grande di un punto · stati finali inammissibili da escludere · aritmetica in più alla lettura.

> [!warning] Quando un indice non basta
> *«Per decidere sull'elemento $i$, cosa avrei bisogno di sapere sul passato che $\text{OPT}[i-1]$ non mi dice?»* — capacità residua (Knapsack), colore precedente (House Coloring), quanti contigui ho preso, quanto budget ho speso. Quella grandezza diventa un **indice**, non una condizione booleana. Se lo stato ha un numero **esponenziale** di valori, la definizione è sbagliata.

> [!info] Caso base — quando esce da solo
> Esce dalla ricorrenza **solo se l'insieme vuoto dei predecessori ha senso** (LIS: $1 + \max(0,\ldots) = 1$; somma su $d=0$ figli $=0$). Va scritto a mano quando «nessun predecessore» non è una configurazione (cammini su griglia, colorazioni): lì la formula darebbe $\pm\infty$. **Controllo**: sostituisci il valore degenere; se non ritrovi i casi base, o vanno dichiarati, o lo stato ha un buco.

**Costo** $=$ *numero di celle* $\times$ *costo per cella*, fattori indipendenti. Decisione **binaria** («prendo $j$ o no») → cella $O(1)$; **multipla** («l'ultimo blocco parte da $i$») → cella $O(j)$.

> [!info] Riconoscere il sottoproblema in un problema mai visto
> | Segnale nella traccia | Forma della tabella |
> |---|---|
> | oggetti in fila, prenderne uno esclude i vicini | $\text{OPT}[j]$ |
> | **budget** / capacità / tempo da non superare | $\text{OPT}[i][w]$, 2° indice = risorsa residua |
> | **due** sequenze da allineare | $\text{OPT}[i][j]$, un indice per sequenza |
> | serve sapere *con che cosa finisce* la soluzione parziale | $\text{OPT}[i]$ **vincolato** + $\max$ finale |
> | condizione locale con **poche** configurazioni (colore, energia, contigui) | $\text{OPT}[i][\text{stato}]$ |
>
> Pattern delle tracce recenti: **problema noto + un parametro di budget $k$ che diventa una dimensione della tabella**.

> [!warning] Pseudo-polinomiale, e quando invece non lo è
> Knapsack $\Theta(nW)$ è polinomiale nel **valore** $W$, non nella sua **dimensione in bit** ($O(n\log W + n\log v_{\max})$): con $W = 2^k$ fa $\Theta(n2^k)$ passi. L'integrità dei **pesi** è essenziale, quella dei valori no.
> Se invece il budget è limitato da una quantità legata a $n$ (quanti salti, quante case rosse, quanti cambi), si tronca a $k' = \min(k,\cdot)$ e resta **polinomiale**.
> **Lower bound gratis**: se l'input ha già dimensione $X$ e cambiarne un elemento cambia l'ottimo, allora $\Omega(X)$ — per House Coloring $\Omega(nk)$, quindi $\Theta(nk)$ è **ottimo**.

## 05 · I problemi DP — definizioni e ricorrenze
> [!quote] Definizioni dei problemi (forma d'esame)
> - **Insieme indipendente**: $S \subseteq V$ tale che nessuna coppia di nodi di $S$ è unita da un arco. **WIS su cammino**: cammino $v_1,\ldots,v_n$ con pesi $w_i \geq 0$, si massimizza $w(S) = \sum_{v_i \in S} w_i$ su $S$ indipendente.
> - **Weighted Interval Scheduling**: $n$ job, job $j$ con $(s_j, f_j)$ e **peso** $w_j > 0$; si massimizza il peso totale di un sottoinsieme di job mutualmente compatibili.
> - **Segmented Least Squares**: $n$ punti ordinati per $x$; si approssima con una sequenza di segmenti minimizzando $f = E + c\,L$ ($E$ somma degli SSE, $L$ numero di segmenti, $c$ penalità per segmento).
> - **Knapsack 0/1**: $n$ oggetti con valore $v_i>0$ e peso $w_i>0$ **interi**, capacità $W$ intera; si massimizza il valore senza superare $W$.
> - **LIS**: sequenza $S[1..n]$; si cerca la sottosequenza crescente più lunga, cioè $i_1 < \cdots < i_k$ con $S[i_1] < \cdots < S[i_k]$ e $k$ massimo.
> - **House Coloring**: $n$ case in fila, $k$ colori, costo $\text{cost}(i,c)$; nessuna coppia adiacente dello stesso colore, si minimizza il costo totale.

> [!quote] Definizione — Predecessore $p(j)$
> Job ordinati per tempo di fine. $p(j)$ è il **più grande** indice $i < j$ con $f_i \leq s_j$, e $0$ se nessuno è compatibile. **Non è $j-1$**: il salto da $j$ a $p(j)$ scarta in un colpo *tutti* i job incompatibili con $j$.

| Problema | Sottoproblema | Ricorrenza | Risposta | Tempo |
|---|---|---|---|---|
| WIS su cammino | $\text{OPT}[j]$ sui primi $j$ nodi | $\max\{\text{OPT}[j-1],\,w_j + \text{OPT}[j-2]\}$; $\text{OPT}[1]=w_1$, $\text{OPT}[2]=\max\{w_1,w_2\}$ | $\text{OPT}[n]$ | $\Theta(n)$ |
| WIS su albero | $A[v]$ senza vincoli, $B[v]$ con $v$ proibito | $B[v]=\sum_i A[u_i]$; $A[v]=\max\{B[v],\,w_v+\sum_i B[u_i]\}$ | $A[r]$ | $\Theta(n)$ |
| Weighted Interval Scheduling | $\text{OPT}(j)$ sui primi $j$ job | $\max\{\text{OPT}(j-1),\,w_j + \text{OPT}(p(j))\}$; $\text{OPT}(0)=0$ | $\text{OPT}(n)$ | $O(n\log n)$ |
| Segmented Least Squares | $\text{OPT}(j)$ sui primi $j$ punti | $\min_{1\leq i\leq j}\{e_{ij} + c + \text{OPT}(i-1)\}$; $\text{OPT}(0)=0$ | $\text{OPT}(n)$ | $O(n^2)$ |
| Knapsack 0/1 | $\text{OPT}(i,w)$: primi $i$ oggetti, capacità $w$ | $\max\{\text{OPT}(i-1,w),\,v_i+\text{OPT}(i-1,w-w_i)\}$; solo il 1° se $w_i > w$; $\text{OPT}(0,w)=0$ | $\text{OPT}(n,W)$ | $\Theta(nW)$ |
| LIS | $\text{OPT}[i]$: LIS **che termina con** $S[i]$ | $1 + \max\bigl(0,\ \max_{j<i,\ S[j]<S[i]} \text{OPT}[j]\bigr)$ | $\max_i \text{OPT}[i]$ | $O(n^2)$ |
| House Coloring | $C_i[c]$: case $1..i$, la $i$-esima di colore $c$ | $\text{cost}(i,c) + \min_{c' \neq c} C_{i-1}[c']$; $C_1[c]=\text{cost}(1,c)$ | $\min_c C_n[c]$ | $\Theta(nk)$ |
| Sequence Alignment | $\text{OPT}(i,j)$ sui prefissi | §06 | $\text{OPT}(m,n)$ | $\Theta(mn)$ |
| Bellman-Ford | $\text{OPT}(i,v)$: $\leq i$ archi da $v$ a $t$ | §06 | $\text{OPT}(n-1,v)$ | $\Theta(mn)$ |

**WIS su cammino** — il Caso 2 rimuove **due** nodi: con uno solo il residuo ottimo potrebbe contenere $v_{n-1}$ e riunirlo a $v_n$ darebbe un insieme non indipendente. Ricostruzione $\Theta(n)$: $v_j$ entra **sse** $w_j + \text{OPT}[j-2] > \text{OPT}[j-1]$ (sui pareggi si esclude).
**WIS su albero** — $A[v]$ è «la risposta senza vincoli», $B[v]$ «la risposta se $v$ è proibito», non «prendo / non prendo»: servono due perché il figlio deve rispondere a due domande diverse. Casi base gratis con $d=0$. Ordine **post-ordine** bottom-up: sul cammino l'ordine degli indici è già quello delle dipendenze, su un albero va procurato.
**Segmented Least Squares** — pre-calcolo degli $e_{ij}$: $O(n^3)$ naïf, $O(n^2)$ con le somme cumulative $\Sigma x, \Sigma y, \Sigma x^2, \Sigma xy$; spazio $O(n^2)$.
**House Coloring con $k$ colori** — pre-calcolando i **due** minimi della riga precedente ogni cella torna $O(1)$: $\Theta(nk)$ invece di $O(nk^2)$.

## 06 · Sequence Alignment, Hirschberg e Bellman-Ford
### Distanza di edit
> [!quote] Definizione — Allineamento e costo
> Con **gap penalty** $\delta \geq 0$ e **mismatch penalty** $\alpha_{pq} \geq 0$ ($\alpha_{pp}=0$), un **allineamento** $M$ fra $X = x_1\ldots x_m$ e $Y = y_1\ldots y_n$ è un insieme di coppie $(x_i,y_j)$ tale che (1) ogni carattere compare in **al più una** coppia e (2) non ci sono **incroci**: se $(x_i,y_j),(x_{i'},y_{j'}) \in M$ con $i<i'$ allora $j<j'$.
> $$\text{cost}(M) = \sum_{(x_i,y_j)\in M} \alpha_{x_i y_j} + \delta\,|\{i : x_i \notin M\}| + \delta\,|\{j : y_j \notin M\}|$$
> La **distanza di edit** è il costo minimo di un allineamento.

> [!quote] Equazione di Bellman — Sequence Alignment
> $$\text{OPT}(i,j) = \begin{cases} j\,\delta & i = 0 \\ i\,\delta & j = 0 \\ \min\bigl\{\alpha_{x_i y_j} + \text{OPT}(i-1,j-1),\; \delta + \text{OPT}(i-1,j),\; \delta + \text{OPT}(i,j-1)\bigr\} & \text{altrimenti}\end{cases}$$
> I tre casi sono esaustivi per la condizione di **non incrocio**: se $x_i$ e $y_j$ non sono accoppiati fra loro, almeno uno dei due non è accoppiato affatto. Sulla matrice: **diagonale** = consumo da entrambe, **sopra** = gap su $Y$, **sinistra** = gap su $X$.

Tempo $\Theta(mn)$, spazio $\Theta(mn)$. **Lo spazio quadratico lo chiede il traceback, non il valore**: per la sola distanza bastano due colonne adiacenti, $O(m+n)$.

> [!quote] Teorema — Hirschberg
> Allineamento ottimo in tempo $O(mn)$ e spazio $\Theta(m+n)$.
> **Osservazione 2**: sia $q^*$ il minimo di $f(q,n/2) + g(q,n/2)$, con $f$ costo minimo da $(0,0)$ a $(q,n/2)$ e $g$ da $(q,n/2)$ a $(m,n)$; allora un allineamento ottimo passa per $(q^*, n/2)$.
> **Divide**: si calcolano $f$ e $g$ sulla colonna centrale in spazio lineare. **Conquer**: ricorsione sui due rettangoli. $T(m,n) \leq T(q^*,n/2) + T(m-q^*,n/2) + O(mn) \Rightarrow T(m,n) \leq 2cmn = O(mn)$.
### Bellman-Ford-Moore
> [!quote] Definizione e lemmi — cicli negativi
> Un **ciclo negativo** è un ciclo diretto $W$ con $\ell(W) = \sum_{e\in W}\ell_e < 0$.
> **Lemma 1**: se un cammino $v \leadsto t$ contiene un ciclo negativo, **non esiste** un cammino minimo da $v$ a $t$ (ogni giro abbassa il costo, $\to -\infty$).
> **Lemma 2**: senza cicli negativi esiste un cammino minimo $v \leadsto t$ **semplice**, con $\leq n-1$ archi (un ciclo di peso $\geq 0$ si rimuove senza aumentare il costo).

Dijkstra fallisce con pesi negativi perché **fissa definitivamente** un nodo quando lo estrae. Il **reweighting** non salva: sommare una costante a ogni arco penalizza un cammino di $k$ archi di $k$ volte tanto, e il cammino minimo **cambia**.

> [!quote] Equazione di Bellman — cammini minimi (single-destination verso $t$)
> $\text{OPT}(i,v)$ = lunghezza del cammino minimo da $v$ a $t$ che usa **al più $i$ archi**.
> $$\text{OPT}(i,v) = \begin{cases} 0 & i=0,\ v=t \\ +\infty & i=0,\ v \neq t \\ \min\Bigl(\text{OPT}(i-1,v),\; \min_{(v,w)\in E}\bigl\{\ell_{vw} + \text{OPT}(i-1,w)\bigr\}\Bigr) & i>0\end{cases}$$
> Obiettivo $\text{OPT}(n-1,v)$. Versione tabellare $\Theta(mn)$ tempo, $\Theta(n^2)$ spazio; **BFM** $O(mn)$ tempo, $\Theta(n)$ spazio.

> [!quote] Teorema — Correttezza di Bellman-Ford-Moore
> **Lemma 3**: $d[v]$ è sempre la lunghezza di *qualche* cammino $v \leadsto t$ (quindi $\geq$ il minimo). **Lemma 4**: $d[v]$ è monotona non crescente. **Lemma 5** (invariante di passata): dopo la passata $i$, $d[v] \leq$ lunghezza del cammino minimo con $\leq i$ archi.
> **Dim.** Per il Lemma 2 il minimo ha $\leq n-1$ archi; dopo $n-1$ passate il Lemma 5 dà $d[v] \leq$ minimo e il Lemma 3 dà $d[v] \geq$ minimo. $\square$

> [!warning] Successori e rilevamento dei cicli negativi
> **Durante** l'esecuzione la catena `successor` può essere inconsistente, e con un ciclo negativo può contenere cicli: solo **a terminazione** dà un cammino minimo di lunghezza $d[v]$.
> **Lemma 6**: ogni ciclo diretto nel grafo dei successori è un ciclo negativo (sommando $d[v_i] \geq d[v_{i+1}] + \ell$ lungo il ciclo si ottiene $0 > \ell(W)$).
> **Rilevamento**: si esegue una passata $n$-esima; se qualche $d[\cdot]$ cambia ancora, esiste un ciclo negativo raggiungibile da $t$. *(Le slide numerano «Lemma 6» due enunciati diversi, pp. 46 e 50.)*

| | Dijkstra | Bellman-Ford-Moore |
|---|---|---|
| Pesi negativi | no (fallisce) | sì |
| Cicli negativi | — | rilevati con la passata $n$ |
| Tempo | $O(m + n\log n)$ (heap di Fibonacci) | $O(mn)$ |
| Spazio | $O(n)$ | $\Theta(n)$ |
| Tecnica | greedy | programmazione dinamica |

In pratica BFM termina prima: l'arco $(v,w)$ si riesamina alla passata $i+1$ solo se $d[w]$ è cambiato alla passata $i$, quindi se il cammino minimo ha $k$ archi bastano $\leq k$ passate.

## 07 · Flussi di Rete (Max-Flow e Min-Cut)
### Definizioni
> [!quote] Definizione — Massimo flusso (forma d'esame)
> **Dati**: rete $G=(V,E,s,t,c)$ con $(V,E)$ **orientato**, sorgente $s$, pozzo $t$, capacità $c: E \to \mathbb{R}_{\geq 0}$.
> **Flusso st**: $f: E \to \mathbb{R}$ con **vincolo di capacità** $0 \leq f(e) \leq c(e)$ per ogni arco e **conservazione** — per ogni $v \neq s,t$ il flusso entrante eguaglia l'uscente.
> **Valore**: $\operatorname{val}(f) = \sum_{e \text{ esce da } s} f(e) - \sum_{e \text{ entra in } s} f(e)$.
> **Obiettivo**: trovare $f^*$ di valore massimo.

> [!quote] Definizione — Taglio st e capacità
> Un **taglio st** è una partizione $(A,B)$ di $V$ con $s \in A$, $t \in B$; la sua **capacità** somma i soli archi **da $A$ a $B$**:
> $$\operatorname{cap}(A,B) = \sum_{e=(u,v),\; u \in A,\; v \in B} c(e)$$
> Gli archi da $B$ ad $A$ **non contano**. **Min-Cut**: taglio di capacità minima.

> [!quote] Definizione — Grafo residuo, cammino aumentante, bottleneck
> Per ogni $e=(u,v) \in E$: arco **diretto** $(u,v)$ con capacità $c(e)-f(e)$ se $f(e) < c(e)$, arco **inverso** $(v,u)$ con capacità $f(e)$ se $f(e) > 0$ — è il meccanismo di *undo* che manca al greedy.
> $$E_f = \{e \in E : f(e) < c(e)\} \;\cup\; \{e^{\text{rev}} : f(e) > 0\}$$
> Un **cammino aumentante** è un cammino semplice $s \leadsto t$ in $G_f$; il suo **bottleneck** è $\min_{e \in P} c_f(e)$, e aumentando lungo $P$ si ha $\operatorname{val}(f') = \operatorname{val}(f) + \operatorname{bottleneck}(G_f,P)$.
### Teoremi
> [!quote] Lemma — Valore del flusso su un taglio
> Per ogni $f$ e ogni taglio $(A,B)$:
> $$\operatorname{val}(f) = \sum_{e \text{ esce da } A} f(e) - \sum_{e \text{ entra in } A} f(e)$$

> [!quote] Proprietà — Dualità debole e certificato
> $\operatorname{val}(f) \leq \operatorname{cap}(A,B)$ per ogni $f$ e ogni taglio:
> $$\operatorname{val}(f) = \sum_{e \text{ esce da } A} f(e) - \sum_{e \text{ entra in } A} f(e) \leq \sum_{e \text{ esce da } A} f(e) \leq \sum_{e \text{ esce da } A} c(e) = \operatorname{cap}(A,B)$$
> **Corollario (certificato)**: se $\operatorname{val}(f) = \operatorname{cap}(A,B)$ allora $f$ è massimo **e** $(A,B)$ è minimo.

> [!quote] Teorema — Max-Flow Min-Cut e cammini aumentanti
> $$\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A,B)$$
> e $f$ è massimo **se e solo se** non esiste un cammino aumentante in $G_f$.
> **Dim. — tre condizioni equivalenti**: (1) esiste $(A,B)$ con $\operatorname{cap}(A,B)=\operatorname{val}(f)$; (2) $f$ è massimo; (3) non ci sono cammini aumentanti.
> - $[1 \Rightarrow 2]$ corollario della dualità debole.
> - $[2 \Rightarrow 3]$ contronominale: se esiste $P$, aumentare dà valore **strettamente** maggiore.
> - $[3 \Rightarrow 1]$ si **costruisce** il taglio: $A$ = nodi raggiungibili da $s$ in $G_f$; $s \in A$, $t \notin A$. Ogni arco $(u,v)$ con $u\in A, v\in B$ è **saturo** ($f(e)=c(e)$, altrimenti $v$ sarebbe raggiungibile); ogni arco $(v,u)$ con $v\in B, u\in A$ ha $f(e)=0$ (altrimenti l'inverso renderebbe $v$ raggiungibile). Per il lemma del valore $\operatorname{val}(f) = \sum_{e \text{ esce da } A} c(e) - 0 = \operatorname{cap}(A,B)$. $\square$
>
> I due passaggi che non possono mancare in $[3 \Rightarrow 1]$: **archi uscenti saturi** e **archi entranti a flusso nullo**.

> [!quote] Teorema — Integralità
> Con capacità **intere**, ogni $f(e)$ e $c_f(e)$ restano interi durante Ford-Fulkerson, quindi esiste sempre un flusso massimo **intero**. È la proprietà su cui poggiano tutte le riduzioni di §08.

**Min-cut da un flusso massimo**: una BFS/DFS da $s$ in $G_{f^*}$ dà $A$ in **$O(m)$**, e $B = V \setminus A$.
### Algoritmi
> [!quote] Teorema — Terminazione di Ford-Fulkerson
> Con capacità intere in $[1,C]$: al più $\operatorname{val}(f^*) \leq nC$ aumenti, ciascuno $O(m)$ (BFS/DFS su $G_f$), **totale $O(m \cdot \operatorname{val}(f^*)) = O(mnC)$**, **pseudo-polinomiale** (dipende dai *valori* delle capacità). Con scelta arbitraria dei cammini il numero di iterazioni può essere esponenziale (rete a farfalla con arco centrale di capacità 1: $2C$ aumenti da 1 unità); con capacità **irrazionali** può non terminare né convergere al massimo.

| Metodo | N. aumenti | Complessità |
|---|---|---|
| Ford-Fulkerson generico | $\leq nC$ | $O(mnC)$, pseudo-polinomiale |
| Shortest augmenting path (Edmonds-Karp, BFS) | $O(mn)$ | $O(m^2 n)$ |
| Capacity Scaling | $O(m\log C)$ | $O(m^2 \log C)$ |
| Improved Capacity Scaling (Gabow) | $O(m\log C)$ | $O(mn\log C)$ |

**Edmonds-Karp**: la distanza BFS da $s$ a $t$ in $G_f$ è **monotona non decrescente**, e ogni arco può essere critico $O(n)$ volte. **Capacity Scaling**: $1 + \lfloor\log_2 C\rfloor$ fasi, $\leq 2m$ aumenti per fase.

## 08 · Applicazioni dei flussi di rete
> [!info] Riduzione al Max-Flow in quattro passi
> **Costruire** la rete che codifica l'istanza · **calcolare** il massimo flusso (o il taglio minimo) · **interpretare** il risultato come soluzione · **dimostrare** la corrispondenza biunivoca. La correttezza poggia sempre sul **teorema di integralità**.

> [!quote] Definizione — Matching e grafo bipartito
> $M \subseteq E$ è un **matching** se ogni nodo compare in **al più** un arco di $M$; è **perfetto** se ogni nodo compare in **esattamente** un arco. $G$ è **bipartito** se $V = L \cup R$ con ogni arco fra $L$ e $R$.

| Problema | Costruzione della rete | Soluzione letta da |
|---|---|---|
| **Bipartite Matching** | $s \to L$ cap. 1; archi $L \to R$ cap. $\infty$; $R \to t$ cap. 1 | archi $L \to R$ con flusso 1 |
| **Cammini arco-disgiunti** | $s,t$ già nel grafo; **tutti** gli archi cap. 1 | decomposizione del flusso in cammini |
| **Cammini nodo-disgiunti** | *node splitting*: $v \to v_{in}, v_{out}$ con arco cap. 1; archi originali cap. $\infty$ | come sopra |
| **Image Segmentation** | $s \to i$ cap. $a_i$; $i \to t$ cap. $b_i$; $(i,j)$ cap. $p_{ij}$ | **taglio minimo**: $A$ = foreground, $B$ = background |
| **Baseball Elimination** | $s \to g_{xy}$ cap. $r_{xy}$; $g_{xy} \to x,y$ cap. $\infty$; $x \to t$ cap. $W^* - w_x$, con $W^* = w_z + r_z$ | $z$ **non** eliminato $\iff$ il flusso satura tutti gli archi da $s$, cioè vale $\sum r_{xy}$ |

**Bipartite Matching** — corrispondenza biunivoca fra matching di cardinalità $k$ e flussi **interi** di valore $k$: ($\Rightarrow$) 1 unità su ogni $s \to u \to v \to t$; ($\Leftarrow$) per integralità ogni arco porta 0 o 1, e le capacità unitarie su $s\to L$ e $R \to t$ impediscono che un nodo sia saturato due volte. Con Ford-Fulkerson: $\leq n = \min(|L|,|R|)$ aumenti, **$O(mn)$**.
**Image Segmentation** — la qualità $\sum_{i\in A} a_i + \sum_{j\in B} b_j - \sum p_{ij}$ si riscrive come costo da **minimizzare** $\operatorname{cap}(A,B) = \sum_{i\in B} a_i + \sum_{i\in A} b_i + \sum_{i\in A,\,j\in B} p_{ij}$: il taglio minimo è la segmentazione ottima.
**Baseball Elimination** — quando $z$ è eliminato il taglio minimo dà il **certificato**: il sottoinsieme $T$ di squadre che giocheranno troppe partite fra loro.

> [!quote] Teoremi di dualità combinatoria (casi particolari di Max-Flow Min-Cut)
> - **König (1931)** — in un grafo **bipartito**, matching massimo $=$ vertex cover minimo.
> - **Hall (1935)** — $G=(L\cup R,E)$ ha un matching che satura $L$ **sse** $|N(S)| \geq |S|$ per ogni $S \subseteq L$.
> - **Menger (1927)** — massimo numero di cammini $s \leadsto t$ arco-disgiunti $=$ minimo numero di archi la cui rimozione disconnette $s$ da $t$.

## 09 · NP-completezza, riduzioni e approssimazione
### Riduzioni e classi
> [!quote] Definizione — Riduzione polinomiale
> $X \leq_P Y$ se ogni istanza di $X$ si risolve con un numero **polinomiale** di passi standard più un numero polinomiale di chiamate a un **oracolo** per $Y$, su istanze di dimensione polinomiale.
> **Direzione** (errore più comune): $X \leq_P Y$ significa che $X$ **non è più difficile** di $Y$. **Transitività**: $X \leq_P Y$ e $Y \leq_P Z \Rightarrow X \leq_P Z$.

> [!quote] Definizione — P, NP, NP-hard, NP-completo
> - **P**: problemi decisionali risolvibili in tempo polinomiale da un algoritmo deterministico.
> - **NP**: problemi decisionali con un algoritmo di **certificazione** polinomiale — dato un certificato si verifica in tempo polinomiale che la risposta è «sì».
> - **NP-hard**: $Y$ tale che $X \leq_P Y$ per **ogni** $X \in$ NP. **NP-completo**: NP-hard **e** in NP.
> - **Cook-Levin (1971)**: SAT è NP-completo. Se un solo problema NP-completo fosse in P, allora P $=$ NP.

> [!quote] Definizione — I problemi del deck
> - **Independent Set** $(G,k)$: esiste $S \subseteq V$, $|S| \geq k$, senza archi interni?
> - **Vertex Cover** $(G,k)$: esiste $C \subseteq V$, $|C| \leq k$, tale che ogni arco abbia **almeno un** estremo in $C$?
> - **Set Cover** $(U,\mathcal{S},k)$: esistono $\leq k$ insiemi di $\mathcal{S}$ la cui unione è $U$?
> - **SAT / 3-SAT**: data una formula CNF (clausole di esattamente 3 letterali), esiste un assegnamento che la soddisfa?
### Le tre riduzioni
> [!quote] Teorema — Independent Set $\equiv_P$ Vertex Cover
> $S$ è independent set di dimensione $k$ **sse** $V \setminus S$ è vertex cover di dimensione $n-k$.
> **Dim.** ($\Rightarrow$) Per ogni arco $(u,v)$: $S$ indipendente ⇒ almeno uno fra $u,v$ sta in $V\setminus S$, che copre ogni arco. ($\Leftarrow$) $V\setminus S$ cover ⇒ almeno uno fra $u,v$ vi appartiene, cioè non entrambi stanno in $S$. $\square$
> Schema: **equivalenza semplice** — stesso grafo, $k \to n-k$, riduzione $O(1)$.

> [!quote] Teorema — Vertex Cover $\leq_P$ Set Cover
> **Costruzione**: $U = E$; per ogni $v \in V$, $S_v = \{e \in E : e \text{ incidente a } v\}$; stesso $k$.
> **Dim.** ($\Rightarrow$) Se $X$ è un vertex cover, $\{S_v : v \in X\}$ copre ogni arco. ($\Leftarrow$) Se $\mathcal{Y}$ è un set cover, $X = \{v : S_v \in \mathcal{Y}\}$ è un vertex cover. $\square$
> Schema: **caso speciale → caso generale**.

> [!quote] Teorema — 3-SAT $\leq_P$ Independent Set
> **Costruzione**: per ogni clausola 3 nodi (uno per letterale) collegati in un **triangolo**; un arco fra ogni nodo e i nodi della sua **negazione** nelle altre clausole; $k = m$ (numero di clausole).
> **Dim.** ($\Rightarrow$) Da un assegnamento soddisfacente si sceglie in ogni triangolo un letterale vero: i $k$ nodi vengono da triangoli distinti (niente archi interni) e non contengono $\ell$ e $\overline{\ell}$ insieme. ($\Leftarrow$) Ogni triangolo è un $K_3$, quindi $S$ ha **esattamente un** nodo per triangolo; assegnando «vero» ai letterali scelti ogni clausola è soddisfatta, senza contraddizioni perché $\ell$ e $\overline{\ell}$ sarebbero adiacenti. $\square$
> Schema: **codifica con gadget** — il triangolo forza «esattamente uno», gli archi di negazione codificano il vincolo logico.

$$\text{3-SAT} \leq_P \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER} \leq_P \text{SET-COVER}$$
La radice è sempre 3-SAT. Altre catene del deck: 3-SAT $\leq_P$ Directed Ham Cycle $\leq_P$ Ham Cycle · 3-SAT $\leq_P$ 3-Coloring · 3-SAT $\leq_P$ Subset Sum $\leq_P$ Knapsack.

> [!quote] Teorema — Decisionale, ricerca e ottimizzazione sono polinomialmente equivalenti
> $\text{VERTEX-COVER (dec)} \equiv_P \text{FIND-VERTEX-COVER (ric)} \equiv_P \text{FIND-MIN-VERTEX-COVER (ott)}$.
> *dec → ric*: si cerca un $v$ tale che $G-\{v\}$ abbia un cover di dimensione $\leq k-1$, lo si include e si ricorre — $O(n)$ chiamate. *ric → ott*: ricerca binaria su $k$, $O(\log n)$ chiamate.
### Approssimazione
> [!quote] Definizione — $\alpha$-approssimazione
> Algoritmo polinomiale che su ogni istanza di **minimizzazione** restituisce $C \leq \alpha \cdot \text{OPT}$ (per la massimizzazione $C \geq \alpha \cdot \text{OPT}$ con $\alpha \leq 1$).

> [!quote] Teorema — List-Scheduling è 2-approssimante per Load Balancing
> $m$ macchine identiche, $n$ job di durata $t_j$; si minimizza il **makespan** $L = \max_i L_i$ con $L_i = \sum_{j \in S_i} t_j$. L'algoritmo assegna ogni job, nell'ordine dato, alla macchina di carico minimo corrente.
> **Due limiti inferiori**: $L^* \geq t_k$ per ogni job $k$, e $L^* \geq \frac{1}{m}\sum_k t_k$.
> **Dim.** Sia $i^*$ la macchina di carico massimo e $j$ l'**ultimo** job assegnatole: quando gli è stato assegnato $i^*$ aveva carico minimo, quindi $L_{i^*} - t_j \leq L_i$ per ogni $i$ e, mediando, $L_{i^*} - t_j \leq \frac{1}{m}\sum_k t_k \leq L^*$. Allora $L = (L_{i^*} - t_j) + t_j \leq L^* + L^* = 2L^*$. $\square$
> **LPT**: ordinando i job per durata **decrescente** il fattore scende a $\tfrac{3}{2}$.

> [!quote] Teorema — Approx-Vertex-Cover è 2-approssimante
> L'algoritmo sceglie ripetutamente un arco $(u,v)$ non ancora coperto, mette **entrambi** gli estremi in $C$ e rimuove gli archi incidenti a $u$ o $v$: gli archi scelti formano un **matching massimale** $M$.
> **Dim.** Ogni arco di $M$ richiede almeno un vertice nel cover ottimo e gli archi di $M$ sono disgiunti, quindi $|M| \leq \text{OPT}$; l'algoritmo prende due vertici per arco, dunque $|C| = 2|M| \leq 2\,\text{OPT}$. $\square$
> **Trappola d'esame**: inserisce **entrambi** gli estremi di ogni arco di $M$, non uno solo.

> [!warning] Ipotesi implicita
> La NP-completezza parla del **caso peggiore**: un problema NP-completo può avere istanze pratiche facili. E la struttura conta — Vertex Cover su grafi **bipartiti** è polinomiale per König.

## Ripasso lampo — i costi del modulo
| Argomento | Algoritmo | Costo |
|---|---|---|
| Interval Scheduling | greedy earliest finish time | $O(n\log n)$ |
| Interval Partitioning | greedy earliest start time + min-heap | $O(n\log n)$, usa $\text{depth}$ aule |
| Union-Find | QuickUnion + rank + compressione | $O(n + m\,\alpha(m+n,n))$ |
| MST | Kruskal | $O(m\log n)$, dominato dall'ordinamento |
| MST | Prim, heap binario / Fibonacci | $O(m\log n)$ / $O(m + n\log n)$ |
| WIS su cammino e su albero | DP | $\Theta(n)$ |
| Weighted Interval Scheduling | DP | $O(n\log n)$ |
| Segmented Least Squares | DP | $O(n^2)$ |
| Knapsack 0/1 | DP | $\Theta(nW)$, pseudo-polinomiale |
| LIS | DP | $O(n^2)$ |
| House Coloring | DP | $\Theta(nk)$, ottimo |
| Sequence Alignment | DP / Hirschberg | $\Theta(mn)$ sp. $\Theta(mn)$ / $O(mn)$ sp. $\Theta(m+n)$ |
| Cammini minimi con pesi negativi | Bellman-Ford-Moore | $O(mn)$, spazio $\Theta(n)$ |
| Max-Flow | Ford-Fulkerson / Edmonds-Karp | $O(mnC)$ pseudo-pol. / $O(m^2 n)$ |
| Bipartite Matching | riduzione a Max-Flow | $O(mn)$ |
| Min-Cut da un flusso massimo | BFS/DFS in $G_{f^*}$ | $O(m)$ |
| Vertex Cover, Load Balancing | 2-approssimazione | polinomiale |