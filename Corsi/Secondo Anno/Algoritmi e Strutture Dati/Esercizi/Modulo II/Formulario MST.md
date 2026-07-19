---
tags:
  - algoritmi
  - mst
---
# Formulario — Minimum Spanning Tree (Esercizio 1 / 2)
Scheda di consegna per lo slot **MST** dello scritto di Modulo II. Non è materiale di studio: la teoria estesa sta in [[03 - Minimum Spanning Tree]] e [[02 - Union-Find]]. Qui c'è **solo quello che va finire sul foglio**, nella forma in cui va scritto.

> [!info] Come cade all'esame
> MST occupa uno dei due slot Es1/Es2 in **5 compiti su 6** recenti. Il formato è fisso: **4-5 affermazioni vero/falso** (quasi sempre su **complessità con struttura dati specifica**: Kruskal con QuickFind, Prim con heap di Fibonacci) **+ 1-2 domande aperte da ~5 righe** (enuncia una proprietà, applicala a un arco dato, dimostrala). Il punteggio è **granulare**: ogni V/F motivato correttamente porta punti. Non lasciare mai un item in bianco.
## Definizioni — vanno scritte così
Grafo $G=(V,E)$ **connesso, non orientato**, con pesi $w: E \to \mathbb{R}$, $|V|=n$, $|E|=m$.
- **Spanning tree** $T \subseteq E$: sottoinsieme di archi **aciclico** che **connette tutti** i nodi. Ha esattamente $n-1$ archi.
- **MST**: spanning tree di costo $w(T) = \sum_{e \in T} w(e)$ **minimo**.
- **Taglio**: una partizione $(S, V \setminus S)$ dei nodi, con $S \neq \emptyset$ e $S \neq V$.
- **Cutset** $D$ del taglio $S$: l'insieme degli archi con **esattamente un estremo** in $S$ («archi che attraversano il taglio»).
- **Ciclo** $C$: sequenza di archi che parte e torna sullo stesso nodo senza ripetere archi.
### Il lemma che regge tutto
> [!quote] Lemma — intersezione ciclo/cutset
> Un **ciclo** $C$ e un **cutset** $D$ si intersecano in un numero **pari** di archi: $|C \cap D|$ è pari.

**Perché**: un ciclo che esce da $S$ deve **rientrare** in $S$ per chiudersi. Ogni uscita è appaiata a un rientro, quindi gli attraversamenti sono pari.

> [!warning] Non saltarlo
> È il passo 3 di entrambe le dimostrazioni. Chi sbaglia cut/cycle property all'esame è quasi sempre perché dà per scontata l'esistenza del **secondo** arco sul taglio invece di giustificarla con questo lemma. Costa una riga e vale il punto.
## Cut property — la dimostrazione da consegnare
> [!quote] Cut property
> Sia $(S, V\setminus S)$ un taglio qualsiasi e sia $e$ l'arco di **peso minimo** del suo cutset. Allora **esiste un MST che contiene $e$**. Se i pesi sono **tutti distinti**, $e$ appartiene a **ogni** MST.

**Dimostrazione (exchange argument).**
1. Per assurdo, sia $T$ un MST con $e=(u,v) \notin T$.
2. $T$ è connesso, quindi $T \cup \{e\}$ ha $n$ archi su $n$ nodi: contiene **esattamente un ciclo** $C$, e $e \in C$.
3. $C$ attraversa il cutset $D$ in $e$; per il **lemma ciclo/cutset** $|C \cap D|$ è pari, quindi esiste un secondo arco $f \in C \cap D$, con $f \neq e$.
4. $e$ è il minimo del cutset $\Rightarrow w(e) \le w(f)$.
5. Poni $T' = T \cup \{e\} \setminus \{f\}$. Rimuovere $f$ rompe l'unico ciclo, quindi $T'$ è **aciclico**; e resta **connesso**, perché i due lati di $f$ restano collegati passando per il resto di $C$. Dunque $T'$ è spanning tree e $w(T') = w(T) + w(e) - w(f) \le w(T)$.
6. Quindi esiste un MST che contiene $e$. Con pesi **distinti** vale $w(e) < w(f)$, da cui $w(T') < w(T)$: assurdo, $T$ non era minimo. $\blacksquare$

> [!warning] La precisione che Gualà pretende
> Enunciare «$e$ sta in **ogni** MST» **senza** l'ipotesi di pesi distinti è **falso** (con pesi ripetuti esistono MST diversi che scelgono archi diversi di pari peso). Scrivi sempre la versione doppia: *«esiste un MST che lo contiene; se i pesi sono distinti, sta in tutti»*.
## Cycle property — la duale
> [!quote] Cycle property
> Sia $C$ un ciclo qualsiasi e sia $f$ il suo arco di peso **massimo**. Allora **esiste un MST che non contiene $f$**. Se i pesi sono **distinti**, $f$ non appartiene a **nessun** MST.

**Dimostrazione (exchange argument speculare).**
1. Per assurdo, sia $T$ un MST con $f=(u,v) \in T$.
2. Rimuovi $f$: $T \setminus \{f\}$ si spezza in **due componenti**. Sia $S$ l'insieme dei nodi della componente di $u$: questo definisce un taglio, e $f$ sta nel suo cutset $D$.
3. Il ciclo $C$ contiene $f \in D$; per il **lemma ciclo/cutset** esiste un secondo arco $e \in C \cap D$, $e \neq f$.
4. $f$ è il massimo del ciclo $\Rightarrow w(e) \le w(f)$.
5. $T' = T \cup \{e\} \setminus \{f\}$ ricollega le due componenti (perché $e$ attraversa il taglio) ed è aciclico: è spanning tree, con $w(T') \le w(T)$.
6. Quindi esiste un MST senza $f$; con pesi distinti $w(T') < w(T)$: assurdo. $\blacksquare$

> [!info] Le due proprietà, in una riga ciascuna
> **Cut** = quali archi puoi **includere** (il più leggero di un taglio). **Cycle** = quali archi puoi **scartare** (il più pesante di un ciclo). Kruskal e Prim sono corollari della cut property; la cycle property serve soprattutto nelle domande «l'arco $e$ può stare in un MST?».
## Unicità
> [!quote] Criterio
> Se **tutti i pesi sono distinti**, l'MST è **unico**.

**Perché**: con pesi distinti la cut property forza *ogni* arco minimo di *ogni* taglio dentro *ogni* MST, e la cycle property ne esclude ogni arco massimo di ogni ciclo: la scelta è deterministica a ogni passo.

> [!warning] Il V/F trappola sull'unicità
> Pesi distinti $\Rightarrow$ MST unico: **vero**. Il **viceversa è falso**: un MST può essere unico anche con pesi ripetuti (basta che gli archi di pari peso non siano mai in competizione sullo stesso taglio). Quindi «MST unico $\Rightarrow$ pesi distinti» è **falso** — è un item ricorrente.
## Kruskal
**Idea**: scorri gli archi in ordine di peso **crescente**, aggiungi $e$ se **non crea ciclo**.
```
KRUSKAL(G, w):
  ordina gli archi per peso crescente
  T ← ∅
  per ogni v ∈ V: makeSet(v)
  per ogni arco (u,v) in ordine:
      se find(u) ≠ find(v):        // non crea ciclo
          T ← T ∪ {(u,v)}
          union(u, v)
  return T
```
**Correttezza (da cut property).** Quando Kruskal aggiunge $(u,v)$, sia $S$ la componente connessa di $u$ nella foresta corrente. L'arco $(u,v)$ attraversa il taglio $(S, V\setminus S)$, e **tutti** gli archi di quel cutset non ancora esaminati hanno peso $\ge w(u,v)$ (perché li scorriamo in ordine crescente, e quelli già scartati avevano entrambi gli estremi in $S$, quindi non attraversano il taglio). Dunque $(u,v)$ è minimo sul cutset: per la cut property sta in un MST. $\blacksquare$

**Complessità** — dipende dall'implementazione di [[02 - Union-Find]]:

| Voce | Costo |
|---|---|
| Ordinamento degli archi | $O(m \log m) = O(m \log n)$ |
| $n$ `makeSet` | $O(n)$ |
| $2m$ `find` + $n-1$ `union` | dipende dalla struttura |
| Totale con **QuickFind + union by size** | $O(m \log n)$ |
| Totale con **QuickUnion + union by size** | $O(m \log n)$ |
| **Totale** | $\mathbf{O(m \log n)}$ |

> [!warning] Il V/F più frequente su Kruskal
> «Kruskal con QuickFind costa più di Kruskal con QuickUnion»: **falso**. In **entrambi** i casi domina l'**ordinamento**, $O(m\log n)$, quindi il totale è identico. La struttura Union-Find cambia il termine non dominante, non l'asintotico. Se il compito ti dà gli archi **già ordinati** (o pesi interi piccoli ordinabili in $O(m)$), allora la differenza emerge: lì la struttura Union-Find diventa il termine dominante — ed è esattamente il caso su cui il prof costruisce l'item.
## Prim
**Idea**: parti da un nodo $s$, fai crescere **un unico albero** aggiungendo ogni volta l'arco più leggero che esce dall'albero.
```
PRIM(G, w, s):
  per ogni v: d[v] ← +∞ ; π[v] ← nil
  d[s] ← 0
  Q ← coda con priorità su tutti i nodi (chiave d)
  mentre Q ≠ ∅:
      u ← deleteMin(Q)
      per ogni (u,v) ∈ E con v ∈ Q:
          se w(u,v) < d[v]:
              d[v] ← w(u,v) ; π[v] ← u ; decreaseKey(v)
  return { (v, π[v]) : v ≠ s }
```
**Correttezza (da cut property).** A ogni passo sia $S$ l'insieme dei nodi già nell'albero. L'arco estratto è per costruzione quello di peso minimo del cutset di $(S, V\setminus S)$: per la cut property appartiene a un MST. $\blacksquare$

> [!warning] Prim vs Dijkstra — la trappola numero uno
> Stesso scheletro, **chiave diversa**:
> - **Prim**: $d[v] = w(u,v)$ — il **peso dell'arco** che collega $v$ all'albero. Non cumula.
> - **Dijkstra**: $d[v] = d[u] + w(u,v)$ — la **distanza da $s$**. Cumula lungo il cammino.
>
> Da qui segue anche che **Prim non richiede pesi non negativi**, mentre Dijkstra sì.

**Complessità** — dipende dalla coda con priorità:

| Struttura | Insert | DeleteMin | DecreaseKey | Totale Prim |
|---|---|---|---|---|
| Scansione lineare (senza PQ) | — | $O(m)$ per step | — | $O(mn)$ |
| **Array non ordinato** | $O(1)$ | $O(n)$ | $O(1)$ | $\mathbf{O(n^2)}$ |
| **Heap binario** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $\mathbf{O(m \log n)}$ |
| **Heap di Fibonacci** | $O(1)$ | $O(\log n)$ | $O(1)$ ammort. | $\mathbf{O(m + n \log n)}$ |

> [!info] Come si ricostruisce il totale (non impararlo a memoria)
> Prim fa $n$ `deleteMin` e al più $m$ `decreaseKey`. Quindi **totale $= n \cdot C_{\text{deleteMin}} + m \cdot C_{\text{decreaseKey}}$**. Heap binario: $n\log n + m \log n = O(m\log n)$. Fibonacci: $n \log n + m\cdot O(1) = O(m + n\log n)$. Array: $n \cdot n + m \cdot 1 = O(n^2)$. Con questa formula ricavi ogni riga sul momento, e rispondi anche a strutture mai viste.
### Quale algoritmo su quale grafo
- **Grafo sparso** ($m = O(n)$): Kruskal o Prim con heap binario, $O(m\log n)$.
- **Grafo denso** ($m = \Theta(n^2)$): Prim con **array** è $O(n^2)$, **migliore** di $O(m \log n) = O(n^2 \log n)$. Item V/F classico: «l'heap binario è sempre meglio dell'array» → **falso**.
- **Ottimale in generale**: Prim con Fibonacci, $O(m + n\log n)$.
## Esecuzione a mano — la procedura
Nelle aperte capita «esegui l'algoritmo sul grafo in figura». Fallo **nominando la giustificazione**, non solo il risultato: è lì che stanno i punti.

**Kruskal.** Scrivi la lista degli archi ordinata per peso. Scorrila e per ciascuno annota `PRESO` / `SCARTATO (ciclo)`. Fermati a $n-1$ archi. Se ti chiedono la correttezza del singolo passo: *«questo arco è il minimo del cutset della componente di $u$»*.

**Prim.** Tabella con una riga per iterazione e una colonna per nodo, contenente $d[v]$ e $\pi[v]$. A ogni riga: cerchia il minimo fra i nodi ancora in $Q$, estrai, aggiorna i vicini. Errore tipico: aggiornare anche i nodi **già estratti** — non si fa.
## Batteria V/F — le risposte che ricorrono
Rispondi **sempre motivando in una riga**, mai secco: il «vero/falso» nudo non prende punti pieni.

| Affermazione | Risp. | Motivazione in una riga |
|---|---|---|
| L'arco di peso minimo del grafo sta in ogni MST | **V*** | è il minimo di ogni taglio che separa i suoi estremi (con pesi distinti; altrimenti «in qualche MST») |
| L'arco di peso massimo del grafo non sta in nessun MST | **F** | se è un **ponte** deve starci; la cycle property si applica solo se il suo peso è massimo **in un ciclo** |
| Se i pesi sono distinti l'MST è unico | **V** | cut+cycle property rendono deterministica ogni scelta |
| Se l'MST è unico i pesi sono distinti | **F** | archi di pari peso possono non competere mai sullo stesso taglio |
| Kruskal con QuickFind è asintoticamente peggiore che con QuickUnion | **F** | in entrambi domina l'ordinamento $O(m\log n)$ |
| Prim con heap binario batte Prim con array su grafi densi | **F** | $m\log n = n^2\log n > n^2$ |
| Prim funziona con pesi negativi | **V** | la chiave è il peso dell'arco, non un cammino cumulato (a differenza di Dijkstra) |
| Moltiplicare tutti i pesi per $c>0$ cambia l'MST | **F** | l'ordinamento relativo degli archi non cambia |
| Sommare $c$ a tutti i pesi cambia l'MST | **F** | ogni spanning tree ha esattamente $n-1$ archi, quindi tutti i costi traslano di $(n-1)c$ |
| Un MST è anche albero dei cammini minimi da $s$ | **F** | minimizza il **costo totale**, non le distanze da un sorgente |

> [!danger] Le due cose che devono essere automatiche domani
> **(1)** Cut property con il lemma ciclo/cutset citato esplicitamente al passo 3. **(2)** La formula $n \cdot C_{\text{deleteMin}} + m \cdot C_{\text{decreaseKey}}$ per Prim, da cui ricavi ogni riga della tabella complessità senza memorizzarla.
