# NP-Completezza e Riduzioni
La teoria dell'intrattabilità studia quali problemi computazionali non ammettono algoritmi efficienti — cioè polinomiali nel tempo — e perché. Invece di sperare di trovare un algoritmo ottimo per ciascuno, l'idea fondamentale è classificare i problemi rispetto alla loro **difficoltà relativa** tramite le **riduzioni polinomiali**: se so risolvere Y efficientemente, riesco a risolvere anche X? Le nozioni di classe P, NP e NP-completezza nascono da questa domanda e hanno implicazioni concrete per la progettazione di algoritmi. Questa nota è strettamente collegata a [[04 - Programmazione Dinamica I (Weighted Independent Set)]], dove il problema Independent Set su grafi generali emerge come variante intrattabile di quello su grafi a intervalli.
## Pattern e anti-pattern nella progettazione
Il corso ha presentato vari **pattern** algoritmici: greedy ([[01 - Greedy e Interval Scheduling]]), divide et impera ([[03 - Equazioni di Ricorrenza|equazioni di ricorrenza]]), programmazione dinamica ([[04 - Programmazione Dinamica I (Weighted Independent Set)]], [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]], [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]]), dualità e flussi ([[07 - Flussi di Rete (Max-Flow e Min-Cut)]]), riduzioni e ricerca locale. Accanto ai pattern esistono però degli **anti-pattern**, ovvero famiglie di problemi per le quali certe garanzie sono verosimilmente irraggiungibili:
| Anti-pattern | Significato |
|---|---|
| **NP-completezza** | nessun algoritmo $O(n^k)$ è noto (e ritenuto possibile) |
| PSPACE-completezza | nessun algoritmo di certificazione polinomiale è noto |
| Indecidibilità | nessun algoritmo esiste in assoluto |
Questa nota si concentra sulla prima categoria.
## Classificare i problemi: l'approccio per efficienza
> [!quote] Definizione — Problema trattabile (working definition)
> Un problema è **trattabile** se esiste un algoritmo che lo risolve in tempo **polinomiale** nella dimensione dell'input: $O(n^k)$ per qualche costante $k$.

La scelta "polinomiale = efficiente" è sia teoricamente robusta (stessa su Turing machine, RAM uniforme, circuiti) sia pratica: le costanti tendono ad essere piccole, e gli algoritmi polinomiali scalano su input enormi.

La tabella seguente mostra coppie di problemi simili dove uno è trattabile e l'altro probabilmente no:
| Problema trattabile | Problema (probabilmente) intrattabile |
|---|---|
| [[10 - Cammini Minimi e Dijkstra\|Cammino minimo (shortest path)]] | Cammino più lungo (longest path) |
| Min Cut ([[07 - Flussi di Rete (Max-Flow e Min-Cut)]]) | Max Cut |
| 2-Soddisfacibilità (2-SAT) | 3-Soddisfacibilità (3-SAT) |
| 4-Colorabilità planare | 3-Colorabilità planare |
| Vertex Cover su grafi bipartiti | Vertex Cover su grafi generali |
| Matching | 3-Dimensional Matching |
| Test di primalità | Fattorizzazione |
| Programmazione lineare | Programmazione lineare intera |
## Riduzioni polinomiali
> [!quote] Definizione — Riduzione polinomiale ($\leq_P$)
> Il problema $X$ si **riduce polinomialmente** al problema $Y$ (scritto $X \leq_P Y$) se ogni istanza di $X$ può essere risolta usando:
> - un numero **polinomiale** di passi computazionali standard, più
> - un numero **polinomiale** di chiamate a un **oracolo** che risolve $Y$ in un singolo passo.
>
> Le istanze inviate all'oracolo devono avere dimensione polinomiale nell'input originale.

Lo schema concettuale è:

```
istanza I (di X)  -->  [Algoritmo per X]  -->  oracolo per Y  -->  soluzione S di I
```

> [!warning] Errore frequente — direzione della riduzione
> $X \leq_P Y$ significa che $X$ **non è più difficile** di $Y$: se so risolvere $Y$, so risolvere anche $X$. **Non** significa che $Y$ è più facile di $X$. Confondere la direzione è l'errore più comune.

Le riduzioni servono a tre scopi:
1. **Progettare algoritmi**: se $X \leq_P Y$ e $Y$ è risolvibile in tempo polinomiale, allora anche $X$ lo è.
2. **Stabilire intrattabilità**: se $X \leq_P Y$ e $X$ non è risolvibile in tempo polinomiale, allora nemmeno $Y$ lo è.
3. **Stabilire equivalenza**: se $X \leq_P Y$ e $Y \leq_P X$, scriviamo $X \equiv_P Y$: i due problemi hanno la stessa difficoltà computazionale.

> [!quote] Proprietà — Transitività delle riduzioni
> Se $X \leq_P Y$ e $Y \leq_P Z$, allora $X \leq_P Z$.
>
> **Idea della dimostrazione**: componiamo i due algoritmi di riduzione. L'algoritmo per $X$ chiama l'oracolo per $Y$; ogni chiamata all'oracolo per $Y$ è simulata dall'algoritmo che riduce $Y$ a $Z$, che a sua volta chiama l'oracolo per $Z$. Il numero totale di passi rimane polinomiale.
## Classi P e NP
> [!quote] Definizione — Classe P
> **P** è la classe dei problemi decisionali (risposta sì/no) risolvibili da un algoritmo deterministico in tempo **polinomiale**.

> [!quote] Definizione — Classe NP
> **NP** è la classe dei problemi decisionali per cui esiste un algoritmo di **certificazione** polinomiale: dato un candidato "certificato" (una presunta soluzione), è possibile verificare in tempo polinomiale se la risposta è "sì".

> [!info] Intuizione: NP come "facile da verificare"
> Trovare una soluzione può essere difficile; verificarne la correttezza è spesso facile. Per Independent Set: dato un sottoinsieme $S$ di vertici, basta controllare che nessuna coppia in $S$ sia adiacente — tempo $O(k^2)$ o $O(m)$.

> [!quote] Definizione — NP-hard e NP-completo
> Un problema $Y$ è **NP-hard** se ogni problema $X \in$ NP soddisfa $X \leq_P Y$: $Y$ è almeno difficile quanto tutti i problemi in NP.
>
> Un problema $Y$ è **NP-completo** se è NP-hard **e** appartiene a NP.

> [!quote] Teorema — Cook-Levin (1971)
> Il problema **SAT** (soddisfacibilità booleana in forma normale congiunta) è NP-completo.
>
> Questo è il primo risultato di NP-completezza: dimostrare che tutti i problemi di NP si riducono a SAT.

> [!info] P vs NP — la grande domanda aperta
> Se anche un solo problema NP-completo fosse risolvibile in tempo polinomiale, allora **P = NP** e tutti i problemi di NP lo sarebbero. La congettura dominante è **P ≠ NP**, ma non è dimostrata. Per il progettista di algoritmi la lezione pratica è: se un problema è NP-completo, non cercare un algoritmo esatto polinomiale — passa ad approssimazioni, euristiche o algoritmi parametrizzati.
## Problemi di packing e covering
### Independent Set
> [!quote] Definizione — Independent Set
> Dato un grafo $G = (V, E)$ e un intero $k$, il problema **Independent Set** chiede: esiste un sottoinsieme $S \subseteq V$ di $|S| \geq k$ vertici tale che nessun arco di $E$ abbia entrambi gli estremi in $S$?

Gli $n$ vertici di $S$ sono **indipendenti**: nessuna coppia è collegata da un arco.

```
  a --- b --- c
  |         /
  d ------- e
```
Esempio: $\{a, c, d\}$ non è indipendente ($a$–$d$ è un arco); $\{b, d\}$ è indipendente.

Questo problema si collega direttamente a [[04 - Programmazione Dinamica I (Weighted Independent Set)]]: lì il grafo è un **cammino** (struttura a intervalli), il che lo rende risolvibile in tempo polinomiale con DP. Su grafi generali diventa NP-completo.
### Vertex Cover
> [!quote] Definizione — Vertex Cover
> Dato un grafo $G = (V, E)$ e un intero $k$, il problema **Vertex Cover** chiede: esiste un sottoinsieme $C \subseteq V$ di $|C| \leq k$ vertici tale che ogni arco di $E$ abbia **almeno un** estremo in $C$?

I vertici in $C$ "coprono" tutti gli archi.
### Equivalenza tra Independent Set e Vertex Cover
> [!quote] Teorema — INDEPENDENT-SET $\equiv_P$ VERTEX-COVER
> $S$ è un independent set di dimensione $k$ **se e solo se** $V \setminus S$ è un vertex cover di dimensione $n - k$.

**Dimostrazione ($\Rightarrow$):** Sia $S$ un independent set di dimensione $k$; $V \setminus S$ ha dimensione $n - k$. Per ogni arco $(u, v) \in E$: poiché $S$ è indipendente, $u \notin S$ o $v \notin S$ (o entrambi), ovvero $u \in V \setminus S$ o $v \in V \setminus S$. Quindi $V \setminus S$ copre ogni arco. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $V \setminus S$ un vertex cover di dimensione $n - k$; quindi $|S| = k$. Per ogni arco $(u,v) \in E$: poiché $V \setminus S$ è un vertex cover, $u \in V \setminus S$ o $v \in V \setminus S$, ovvero $u \notin S$ o $v \notin S$. Quindi $S$ è indipendente. $\square$

> [!info] Schema di riduzione: equivalenza semplice
> La riduzione è banale ($O(1)$ lavoro aggiuntivo): dato $(G, k)$ per Independent Set, costruiamo $(G, n-k)$ per Vertex Cover, e viceversa. La stessa istanza del grafo funziona per entrambi. Questo è il pattern **"equivalenza semplice"** nelle riduzioni.
### Set Cover
> [!quote] Definizione — Set Cover
> Dato un universo $U$ di elementi, una collezione $\mathcal{S}$ di sottoinsiemi di $U$ e un intero $k$, il problema **Set Cover** chiede: esistono $\leq k$ sottoinsiemi in $\mathcal{S}$ la cui unione è $U$?

**Esempio:** $U = \{1,2,3,4,5,6,7\}$, $S_a = \{3,7\}$, $S_b = \{2,4\}$, $S_c = \{3,4,5,6\}$, $S_d = \{5\}$, $S_e = \{1\}$, $S_f = \{1,2,6,7\}$, $k = 2$: si cerca una coppia di insiemi che copra tutto $U$.

**Applicazione pratica:** dati $m$ software e $n$ funzionalità desiderate, ogni software fornisce un sottoinsieme di funzionalità; si vuole ottenere tutte le $n$ funzionalità usando il minor numero di software.
### Riduzione: Vertex Cover $\leq_P$ Set Cover
> [!quote] Teorema — VERTEX-COVER $\leq_P$ SET-COVER
> **Costruzione:** data un'istanza $(G, k)$ di Vertex Cover, costruiamo l'istanza $(U, \mathcal{S}, k)$ di Set Cover come segue:
> - Universo: $U = E$ (gli archi del grafo).
> - Per ogni vertice $v \in V$, definiamo $S_v = \{e \in E : e \text{ è incidente a } v\}$.
>
> **Lemma:** $G$ ha un vertex cover di dimensione $k$ se e solo se $(U, \mathcal{S}, k)$ ha un set cover di dimensione $k$.

**Dimostrazione ($\Rightarrow$):** Sia $X \subseteq V$ un vertex cover di dimensione $k$. Allora $\{S_v : v \in X\}$ è un set cover: ogni arco $e \in E$ è incidente a qualche $v \in X$ (per definizione di vertex cover), quindi $e \in S_v$, cioè $e$ è coperto. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $\mathcal{Y} \subseteq \mathcal{S}$ un set cover di dimensione $k$. Allora $X = \{v : S_v \in \mathcal{Y}\}$ è un vertex cover: per ogni arco $e \in E$, esiste $S_v \in \mathcal{Y}$ con $e \in S_v$, cioè $e$ è incidente a $v \in X$. $\square$

> [!info] Schema di riduzione: caso speciale → caso generale
> Vertex Cover è un caso speciale di Set Cover in cui ogni insieme $S_v$ corrisponde agli archi incidenti a un vertice. Il pattern **"caso speciale → caso generale"** è una strategia comune: si mostra che istanze del problema semplice corrispondono a istanze del problema più generale.
## Problemi di soddisfacibilità
### SAT e 3-SAT
> [!quote] Definizione — SAT e 3-SAT
> Un **letterale** è una variabile booleana $x_i$ o la sua negazione $\overline{x_i}$. Una **clausola** è una disgiunzione di letterali. La **forma normale congiuntiva** (CNF) è una congiunzione di clausole.
>
> **SAT**: data una formula CNF $\Phi$, esiste un assegnamento di verità che soddisfa $\Phi$?
>
> **3-SAT**: come SAT, ma ogni clausola contiene **esattamente 3 letterali** distinti.

**Esempio di istanza 3-SAT soddisfacibile:**
$$\Phi = (x_1 \vee x_2 \vee \overline{x_3}) \wedge (\overline{x_1} \vee x_2 \vee x_4) \wedge (\overline{x_2} \vee \overline{x_3} \vee \overline{x_4})$$
Assegnamento soddisfacente: $x_1 = \top, x_2 = \top, x_3 = \bot, x_4 = \bot$.

> [!quote] Teorema — 3-SAT è NP-completo
> La congettura scientifica che non esista un algoritmo polinomiale per 3-SAT è equivalente alla congettura **P $\neq$ NP**.

**Applicazioni:** il SAT è alla base dell'**Electronic Design Automation** (EDA): la verifica formale di circuiti digitali si riduce spesso a problemi di soddisfacibilità.
## La riduzione chiave: 3-SAT $\leq_P$ Independent Set
> [!quote] Teorema — 3-SAT $\leq_P$ INDEPENDENT-SET
> **Costruzione:** data un'istanza $\Phi$ di 3-SAT con $m$ clausole, costruiamo $(G, k)$ con $k = m$ come segue:
> - Per ogni clausola, inserire 3 nodi (uno per letterale) collegati in un **triangolo**.
> - Collegare ogni nodo al nodo corrispondente alla sua **negazione** nelle altre clausole.

Schema ASCII per una formula con 3 clausole $(x_1 \vee x_2 \vee \overline{x_3})$, $(\overline{x_1} \vee x_3 \vee x_4)$, $(\overline{x_2} \vee \overline{x_3} \vee x_4)$:

```
Clausola 1       Clausola 2        Clausola 3
  x1 -- x2       x1b -- x3       x2b -- x3b
   \   /    ...   \   /    ...    \    /
   x3b            x4              x4
(triangoli interni; archi tra letterali opposti tra clausole diverse)
```

> [!quote] Lemma — Correttezza della riduzione 3-SAT $\leq_P$ INDEPENDENT-SET
> $\Phi$ è soddisfacibile se e solo se $G$ contiene un independent set di dimensione $k = |\Phi|$ (numero di clausole).

**Dimostrazione ($\Rightarrow$):** Sia $\alpha$ un assegnamento soddisfacente. Da ogni triangolo (clausola) scegliamo **un** letterale reso vero da $\alpha$; otteniamo $k$ nodi. I nodi scelti sono indipendenti: (a) provengono da triangoli *distinti*, quindi non ci sono archi intra-triangolo tra coppie scelte; (b) non ci sono archi di negazione tra nodi scelti: se avessimo selezionato sia $\ell$ che $\overline{\ell}$, $\alpha$ dovrebbe rendere veri entrambi — impossibile. $\square$

**Dimostrazione ($\Leftarrow$):** Sia $S$ un independent set di dimensione $k$. Poiché i nodi di ogni triangolo formano un $K_3$ (ogni coppia è collegata da un arco), $S$ non può contenere più di un nodo per triangolo. Essendoci $k$ triangoli e $|S|=k$, $S$ contiene **esattamente un** nodo per triangolo. Assegnare "vero" ai letterali selezionati in $S$ (completando l'assegnamento in modo consistente per le variabili non selezionate) soddisfa ogni clausola. Non ci sono contraddizioni perché $S$ non può contenere sia $\ell$ che $\overline{\ell}$: sarebbero collegati da un arco di negazione, violando l'indipendenza di $S$. $\square$

> [!info] Schema di riduzione: codifica con gadget
> Questo è il pattern **"codifica con gadget"**: si costruisce una struttura locale (il triangolo) che "forza" la scelta di esattamente un elemento, e archi tra gadget che codificano i vincoli logici (la negazione). È il meccanismo più potente e comune nelle riduzioni NP.
## La catena di riduzioni
Le riduzioni viste compongono grazie alla transitività in una **catena**:
$$\text{3-SAT} \leq_P \text{INDEPENDENT-SET} \leq_P \text{VERTEX-COVER} \leq_P \text{SET-COVER}$$
Poiché 3-SAT è NP-completo (Teorema di Cook-Levin), per transitività tutti i problemi a destra della catena sono **NP-hard**. Poiché ciascuno è verificabile in tempo polinomiale, sono **NP-completi**.

> [!info] Mappa delle riduzioni (dal deck)
> Il deck di Kevin Wayne mostra una mappa più ampia dei problemi NP-completi, suddivisa per categoria:
>
> - **Packing/Covering**: 3-SAT → Independent Set → Vertex Cover → Set Cover
> - **Sequencing**: 3-SAT → Directed Ham Cycle → Ham Cycle
> - **Partitioning**: 3-SAT → 3-Coloring
> - **Numerical**: 3-SAT → Subset Sum → Knapsack (si veda [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] per la versione trattabile con DP — ma la versione decisionale su interi arbitrari è NP-completa)
>
> La radice comune è sempre 3-SAT, il problema NP-completo "progenitore" da cui si dipartono tutte le catene.
## Problemi decisionali, di ricerca e di ottimizzazione
I problemi possono essere formulati in tre modi diversi ma equivalenti:
> [!quote] Definizione — Varianti di un problema
> - **Decisionale**: esiste una soluzione con valore $\leq k$ (o $\geq k$)?
> - **Di ricerca**: trova una soluzione con valore $\leq k$.
> - **Di ottimizzazione**: trova la soluzione con valore minimo (o massimo).

> [!quote] Teorema — Equivalenza polinomiale delle varianti
> Le tre varianti di Vertex Cover soddisfano:
> $$\text{VERTEX-COVER (dec)} \equiv_P \text{FIND-VERTEX-COVER (ric)} \equiv_P \text{FIND-MIN-VERTEX-COVER (ott)}$$

**Idea della riduzione (dec → ric):** per trovare un vertex cover di dimensione $\leq k$, procediamo per selezione sequenziale: cerchiamo un vertice $v$ tale che $G - \{v\}$ abbia un vertex cover di dimensione $\leq k-1$ (ogni vertice in un vertex cover ottimo ha questa proprietà). Includiamo $v$ nel cover e ricorsiamo su $G - \{v\}$. Ogni passo usa il problema decisionale; in totale si effettuano $O(n)$ chiamate, ciascuna polinomiale.

**Idea della riduzione (ric → ott):** per trovare il vertex cover di dimensione minima, si effettua una **ricerca binaria** su $k$ (da $0$ a $n$) e si risolve il problema di ricerca per ciascun valore: $O(\log n)$ chiamate, ognuna polinomiale.

> [!example] Domanda tipica d'esame
> D: Perché ci concentriamo su problemi decisionali per definire NP-completezza, invece che di ottimizzazione?
> R: Per semplicità formale: la risposta sì/no è facilmente catturata dal modello teorico (Turing machine non deterministica). Le tre varianti sono comunque polinomialmente equivalenti, quindi la scelta non perde generalità.
## Significato pratico per la progettazione
Quando si dimostra che un problema è NP-completo, le opzioni per la progettazione cambiano radicalmente:
1. **Algoritmi di approssimazione**: rinunciare all'ottimalità garantendo una soluzione entro un fattore $\alpha$ dall'ottimo (sezione successiva).
2. **Algoritmi parametrizzati** (*FPT*): risolvere esattamente ma in tempo $f(k) \cdot n^{O(1)}$, dove $k$ è un parametro "piccolo" (es. dimensione della soluzione).
3. **Casi speciali trattabili**: come in [[04 - Programmazione Dinamica I (Weighted Independent Set)]] (grafi a intervalli) o [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] (Knapsack con $W$ piccolo), trovare restrizioni del problema risolvibili in poly-time.
4. **Euristiche**: sacrificare le garanzie formali per soluzioni buone in pratica.

> [!warning] Attenzione alle ipotesi implicite
> La NP-completezza presuppone istanze **nel caso peggiore**. Un problema NP-completo può avere istanze pratiche risolvibili velocemente (es. SAT su formule reali è spesso facile per i SAT solver moderni). La difficoltà teorica non esclude la trattabilità pratica su distribuzioni di input ristrette.
## Algoritmi di approssimazione (cenni)
Quando un problema di ottimizzazione è NP-hard, gli **algoritmi di approssimazione** offrono un compromesso: tempo polinomiale, ma con garanzia di qualità sulla soluzione.
> [!quote] Definizione — $\alpha$-approssimazione
> Un algoritmo polinomiale $\mathcal{A}$ è una **$\alpha$-approssimazione** per un problema di minimizzazione se per ogni istanza restituisce una soluzione di costo $C$ tale che:
> $$C \leq \alpha \cdot \text{OPT}$$
> dove $\text{OPT}$ è il costo della soluzione ottima. Per i problemi di massimizzazione, $C \geq \alpha \cdot \text{OPT}$ con $\alpha \leq 1$.
### Load Balancing — 2-approssimazione
**Problema:** date $m$ macchine identiche e $n$ job con tempi $t_j$, assegnare ogni job a una macchina minimizzando il **makespan** $L = \max_i L_i$ (massimo carico tra le macchine), dove $L_i = \sum_{j \in S_i} t_j$.

**Limiti inferiori sull'ottimo:**
- $L^* \geq t_k$ per ogni job $k$ (qualche macchina deve eseguire il job più lungo).
- $L^* \geq \frac{1}{m} \sum_k t_k$ (il lavoro totale va distribuito su $m$ macchine).

**`List-Scheduling`** — algoritmo greedy: assegna ogni job, nell'ordine dato, alla macchina con carico minimo corrente.

**`List-Scheduling(macchine M[1..m], job J[1..n])`**
```text
1   for i = 1 to m: L[i] = 0; S[i] = {}
2   for j = 1 to n:
3       i* = argmin_{i} L[i]          // macchina con carico minimo
4       S[i*] = S[i*] ∪ {j}
5       L[i*] = L[i*] + t_j
6   return S
```

> [!quote] Teorema — List-Scheduling è una 2-approssimazione
> L'algoritmo List-Scheduling produce un makespan $L \leq 2 \cdot L^*$.
>
> **Dimostrazione:** sia $i^*$ la macchina con carico massimo e $j$ l'**ultimo** job assegnato a $i^*$. Quando $j$ viene assegnato, $i^*$ aveva il carico minimo: $L_{i^*} - t_j \leq L_i$ per ogni $i$. Sommando su tutte le macchine:
> $$L_{i^*} - t_j \leq \frac{1}{m}\sum_{i} L_i = \frac{1}{m}\sum_k t_k \leq L^*$$
> Quindi $L = L_{i^*} = (L_{i^*} - t_j) + t_j \leq L^* + L^* = 2L^*$. $\square$

**Versione LPT (Longest Processing Time):** ordinare i job in ordine **decrescente** di $t_j$ prima di applicare List-Scheduling migliora il fattore a $\frac{3}{2}$ (la dimostrazione usa il fatto che se ci sono più di $m$ job, allora $L^* \geq 2t_{m+1}$, cioè l'ottimo deve essere almeno il doppio del tempo del $(m+1)$-esimo job più grande).
### Vertex Cover — 2-approssimazione
Un algoritmo greedy elementare fornisce una 2-approssimazione per Vertex Cover (problema di minimizzazione):

**`Approx-Vertex-Cover(G)`**
```text
1   C = {}
2   E' = E                             // copia degli archi
3   while E' ≠ {} do:
4       scegli un arco (u, v) ∈ E'
5       C = C ∪ {u, v}
6       rimuovi da E' tutti gli archi incidenti a u o v
7   return C
```

> [!quote] Teorema — Approx-Vertex-Cover è una 2-approssimazione
> Sia $M$ l'insieme degli archi selezionati al passo 4 (un **matching** massimale). Ogni arco di $M$ richiede almeno un vertice nel vertex cover ottimo, quindi $|M| \leq \text{OPT}$. L'algoritmo aggiunge entrambi gli estremi per ogni arco in $M$: $|C| = 2|M| \leq 2 \cdot \text{OPT}$.

> [!example] Domanda tipica d'esame
> D: Perché Vertex Cover ammette una 2-approssimazione ma è NP-completo?
> R: La NP-completezza riguarda la soluzione **esatta**. Un algoritmo di approssimazione rinuncia all'ottimalità: garantisce una soluzione entro un fattore 2, ma non necessariamente ottima. Le due affermazioni non si contraddicono.
>
> D: Qual è la struttura della catena di riduzioni 3-SAT → Independent Set → Vertex Cover → Set Cover?
> R: La catena usa tre tipi diversi di riduzione: equivalenza semplice (Independent Set ↔ Vertex Cover tramite complemento), caso speciale → generale (Vertex Cover ≤ Set Cover), e codifica con gadget (3-SAT → Independent Set tramite triangoli). La transitività garantisce che tutti i problemi a destra di 3-SAT siano NP-hard.
## Riepilogo
| Problema | Classe | Strategia |
|---|---|---|
| Independent Set (grafi a intervalli) | P | DP ([[04 - Programmazione Dinamica I (Weighted Independent Set)]]) |
| Independent Set (grafi generali) | NP-completo | — |
| Vertex Cover | NP-completo ($\equiv_P$ Indep. Set) | 2-approx greedy |
| Set Cover | NP-completo (da Vertex Cover) | greedy logaritmico |
| 3-SAT | NP-completo (Cook-Levin) | — |
| Knapsack (W intero) | pseudo-polinomiale | DP ([[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]) |
| Load Balancing | NP-hard (ottimizzazione) | 2-approx (List-Scheduling), $\frac{3}{2}$-approx (LPT) |

> [!info] Collegamento con i flussi
> Vertex Cover su grafi **bipartiti** è risolvibile in tempo polinomiale tramite il Teorema di König (equivalente al Max-Flow Min-Cut per reti bipartite, si veda [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] e [[08 - Applicazioni dei Flussi di Rete]]). Questo dimostra che la struttura del grafo può rendere un problema NP-completo trattabile: ciò che è difficile su grafi generali può essere facile su classi ristrette.
