---
tags:
  - algoritmi
  - union-find
  - esercizi
---
# Esercizi d'esame — Union-Find
Tutti gli item su **Union-Find** realmente usciti nei **12 compiti** di Modulo II dal giugno 2024 al giugno 2026, con la risposta modello. **Nessun esercizio è inventato**: ogni testo è verbatim dal compito, con appello, esercizio e punto.
> [!info] Cosa dicono i numeri per questo argomento
> **13 item** su 4 appelli diversi (su 12 analizzati). Slot: Es. 1 ×13.
> Cosa ti chiede di produrre: motiva-vf ×11, costruisci-esempio ×2.
> Richieste esplicite di **dimostrazione**: **0**.
> Come usarlo: copri la riga «**Risposta.**», rispondi ad alta voce, scopri. Sui vero/falso motiva **sempre in una riga** — il «vero/falso» secco non prende punti pieni.
### 1. Kruskal con Quick-Find senza union by size
*(13/06/2024 · Es. 1 · V/F n. 3 · motiva-vf)*
> Se si implementa l'algoritmo di Kruskal con la struttura dati Quick-Find senza euristica di bilanciamento union-by-size, la complessità dell'algoritmo nel caso peggiore è O(n^2).

**Risposta.** Falsa. Senza union by size ogni union costa O(n) nel caso peggiore, quindi le n−1 union costano O(n²); ma Kruskal richiede anche l'ordinamento degli m archi, che costa O(m log n). Poiché m può essere Θ(n²), il termine di ordinamento domina: la complessità complessiva nel caso peggiore è O(m log n), non O(n²).
### 2. QuickFind union by size — altezza albero
*(16/07/2024 · Es. 1 · V/F n. 1 · motiva-vf)*
> Nella QuickFind con euristica union by size ogni insieme è rappresentato con un albero di altezza Θ(log n), dove n è il numero di makeSet, in modo che l'operazione di find richieda tempo logaritmico.

**Risposta.** Falsa. Nella QuickFind ogni elemento punta direttamente al rappresentante del proprio insieme (non c'è struttura ad albero), quindi find è O(1) indipendentemente da n. È la QuickUnion con union by size ad avere alberi di altezza O(log n).
### 3. QuickFind union by size — complessità sequenza operazioni
*(16/07/2024 · Es. 1 · V/F n. 2 · motiva-vf)*
> Usando la struttura dati QuickFind con euristica union by size, ogni sequenza di n makeSet, n − 1 union e m find, richiede nel caso peggiore tempo O(m + n log n).

**Risposta.** Vera. Ogni makeSet e find costano O(1) (totale O(n) + O(m)); union by size relabela sempre l'insieme più piccolo, e ogni elemento può essere relabellato al più O(log n) volte (ogni relabel almeno raddoppia la taglia del suo insieme), quindi il costo totale delle union è O(n log n).
### 4. QuickFind union by size — cambi di padre e dimensione insieme
*(16/07/2024 · Es. 1 · V/F n. 3 · motiva-vf)*
> Usando la struttura dati QuickFind con euristica union by size, se in una sequenza di operazioni un elemento ha cambiato padre k volte allora appartiene ad un insieme che è grande almeno 2^k.

**Risposta.** Vera. Union by size relabela sempre gli elementi dell'insieme di taglia minore o uguale; ogni volta che un elemento cambia rappresentante, la taglia dell'insieme risultante è almeno il doppio di quella precedente. Partendo da taglia 1 = 2^0, dopo k cambi la taglia è ≥ 2^k.
### 5. Lower bound per strutture dati Union-Find
*(16/07/2024 · Es. 1 · V/F n. 4 · motiva-vf)*
> Ogni struttura dati, per eseguire una sequenza di n makeSet, n − 1 union e m find, deve impiegare nel caso peggiore tempo Ω(m + n).

**Risposta.** Vera. È un lower bound banale: qualunque struttura dati deve almeno leggere/produrre l'input e l'output delle n makeSet e delle m find, quindi il tempo è necessariamente Ω(m + n).
### 6. QuickUnion union by size — costruzione albero di altezza Θ(log n)
*(16/07/2024 · Es. 1 · domanda aperta punto 2 · costruisci-esempio)*
> Si consideri la struttura dati QuickUnion con euristica union by size. Si mostri una sequenza di operazioni di n makeSet e n − 1 union in cui l'albero ottenuto abbia altezza Θ(log n).

**Risposta.** Con n = 2^k: eseguire n makeSet (n singoletti, altezza 0). Poi fare n/2 union tra coppie di alberi di taglia 1, ottenendo n/2 alberi di taglia 2 e altezza 1. Ripetere unendo a coppie alberi di taglia uguale (2→4, 4→8, ...) fino a un unico albero di taglia n. Poiché ad ogni round le due taglie sono uguali, union by size fa crescere l'altezza di 1 ad ogni round: dopo k = log n round si ottiene un albero di altezza Θ(log n).
### 7. Altezza albero in QuickUnion con union by size
*(18/02/2025 · Es. 1 · V/F n. 1 · motiva-vf)*
> Nella QuickUnion con euristica union by size ogni insieme è rappresentato con un albero di altezza 1, in modo che sia l'operazione di find che di union richiedano tempo logaritmico.

**Risposta.** Falsa. Con union by size l'altezza dell'albero è al più O(log n), non necessariamente 1 (vedi item 6 per un esempio con altezza Θ(log n)); inoltre se l'altezza fosse davvero 1, find e union costerebbero O(1), non tempo logaritmico: l'affermazione è internamente contraddittoria.
### 8. Costo ammortizzato vs caso peggiore di find in QuickUnion con union by size
*(18/02/2025 · Es. 1 · V/F n. 2 · motiva-vf)*
> Usando la struttura dati QuickUnion con euristica union by size, ogni operazione di find ha costo ammortizzato O(log n), dove n è il numero di makeSet. Eppure una singola operazione di find nel caso peggiore può costare anche Θ(n).

**Risposta.** Falsa. Con union by size l'altezza dell'albero è limitata da O(log n) come invariante di caso peggiore (non solo in ammortizzato), quindi ogni singola find costa O(log n) anche nel caso peggiore: non può mai costare Θ(n).
### 9. Complessità sequenza di operazioni con QuickFind e union by size
*(18/02/2025 · Es. 1 · V/F n. 3 · motiva-vf)*
> Usando la struttura dati QuickFind con euristica union by size, ogni sequenza di n makeSet, n − 1 union e m find, richiede nel caso peggiore tempo O(m + n log n).

**Risposta.** Vedi item 3 — stessa domanda, identica risposta (Vera).
### 10. Lower bound Ω(m+n) per una sequenza di operazioni Union-Find
*(18/02/2025 · Es. 1 · V/F n. 4 · motiva-vf)*
> Ogni struttura dati, per eseguire una sequenza di n makeSet, n − 1 union e m find, deve impiegare nel caso peggiore tempo Ω(m + n).

**Risposta.** Vedi item 5 — stessa domanda, identica risposta (Vera).
### 11. Complessità di Kruskal con QuickFind e union by size, archi già ordinati
*(18/02/2025 · Es. 1 · V/F n. 5 · motiva-vf)*
> Si assuma di implementare l'algoritmo di Kruskal usando una struttura dati QuickFind con euristica union by size. Si assuma inoltre di avere già gli archi del grafo ordinati in ordine non decrescente rispetto al loro peso. Allora l'esecuzione dell'algoritmo di Kruskal ha complessità temporale O(m + n log n).

**Risposta.** Vera. Senza il costo di ordinamento (già dato in input), restano n makeSet e m find a costo O(1) ciascuno (O(n + m) totale) più n−1 union che, con union by size, costano complessivamente O(n log n) (vedi item 3): totale O(m + n log n).
### 12. Sequenza di operazioni che produce albero di altezza Θ(log n) in QuickUnion con union by size
*(18/02/2025 · Es. 1 · punto 2 · costruisci-esempio)*
> Si consideri la struttura dati QuickUnion con euristica union by size. Si mostri una sequenza di operazioni di n makeSet e n − 1 union in cui l'albero ottenuto abbia altezza Θ(log n).

**Risposta.** Vedi item 6 — stessa domanda, identica costruzione.
### 13. Complessità Kruskal con Union-Find QuickFind e union by size
*(09/09/2025 · Es. 1 · V/F n. 5 · motiva-vf)*
> Se G ha Θ(n√n) archi, allora l'algoritmo di Kruskal che implementa la Union-Find con la QuickFind con euristica union by size ha complessità lineare, ovvero Θ(n√n).

**Risposta.** Falsa. Con m = Θ(n√n) = Θ(n^1.5), la parte union-find costa O(m + n log n) = Θ(n^1.5), effettivamente lineare in m; ma Kruskal richiede prima l'ordinamento degli m archi, che costa Θ(m log m) = Θ(n^1.5 log n), termine superlineare che domina. La complessità complessiva è quindi Θ(n^1.5 log n), non lineare.
