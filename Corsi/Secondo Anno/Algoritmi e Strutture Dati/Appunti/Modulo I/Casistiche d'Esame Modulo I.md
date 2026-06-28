---
tags:
  - algoritmi
---
# Casistiche d'Esame — Modulo I
Indice delle **tracce possibili** allo scritto del Modulo I (prof. Gualà), estratte dalle prove 2021–2026. Una *casistica* è una **categoria** di quesito, non il singolo esercizio. Tra parentesi quante volte è apparsa. Struttura della prova: **Es 1** (16 pt — A asintotici, B ricorrenze, C algoritmi & complessità), **Es 2** (8 pt, progettazione), **Es 3** (8 pt, modellazione). La checklist «cosa devo saper fare» è in [[Piano Esame ASD - Modulo I]]; gli **svolgimenti** sono nelle cartelle `Esercizio 1`, `Esercizio 2`, `Esercizio 3` (in `Esercizi/Modulo I/`).
## 1.A — Notazione asintotica
Dire quali relazioni asintotiche ($O,\Omega,\Theta,o,\omega$) sono vere o false, col metodo dei limiti. → ripasso [[02 - Notazioni Asintotiche]] · svolti [[1.A — Notazione asintotica]]
- **Confronto tra polinomi puri** — $n^a$ vs $n^b$, anche con radici *(8×)*
- **Polinomiale × log vs polinomiale** — il log conta solo a esponenti pari *(10×)*
- **Polilogaritmico vs polinomiale/radice** — $\log^k n$ vs $n^\varepsilon$ *(8×)*
- **Proprietà dei logaritmi** — cambio di base, $\log n^k$, $\log\sqrt n$ *(5×)*
- **Logaritmi iterati e log-radice** — $\log\log n$, $\sqrt{\log n}$, $\log n$ *(7×)*
- **Potenze del logaritmo** — $\log^a n$ vs $\log^b n$ *(6×)*
- **Frazioni razionali con radici** — tenere solo il termine dominante *(10×)*
- **Identità $a^{\log n}=n^{\log a}$** — riscrivere e poi confrontare *(5×)*
- **Funzioni sub-polinomiali** — $2^{\sqrt{\log n}}$, $2^{\log^2 n}=n^{\log n}$ *(4×)*
- **Esponenziali a basi diverse** — $a^n$ vs $b^n$, domina la base maggiore *(10×)*
- **Esponenziale vs polinomiale** — $a^n$ batte ogni $n^k$ *(6×)*
- **Costante additiva all'esponente** — $2^{n+c}=\Theta(2^n)$ *(10×)*
- **Esponente scalato** — $2^{cn}$ vs $2^{dn}$, mai $\Theta$ se $c\ne d$ *(10×)*
- **Somma di esponenziali** — domina il termine più grande *(8×)*
- **Esponente con addendo non costante** — $2^{n+\log n}=n\cdot 2^n$ *(4×)*
- **$o$/$\omega$ vs $\Theta$** — limite finito non-zero ⟹ $\Theta$ *(8×)*
- **Fattoriale vs esponenziale** — $n!=\omega(a^n)$ (Stirling) *(2×)*
- **Funzioni super-esponenziali** — $n^n$, $n^{\sqrt n}$ via logaritmi *(3×)*
## 1.B — Equazioni di ricorrenza
Dare la soluzione asintotica di una relazione di ricorrenza. → ripasso [[03 - Equazioni di Ricorrenza]] · svolti [[1.B — Equazioni di ricorrenza]]
- **Master Theorem — caso 2** — $f=\Theta(n^{\log_b a})$ → $\Theta(n^{\log_b a}\log n)$ *(8×)*
- **Master Theorem — caso 1** — dominano le foglie → $\Theta(n^{\log_b a})$ *(6×)*
- **Master Theorem — caso 3** — domina $f$ → $\Theta(f(n))$ *(10×)*
- **Sottrattiva con $a\ge 2$** — $aT(n-k)+f$ → $\Theta(a^{n/k})$ *(8×)*
- **Sottrattiva con $a=1$** — $T(n-k)+f$ → $\Theta(n^{p+1})$ *(10×)*
- **Tipo Fibonacci** — $T(n-1)+T(n-2)$ → $\Theta(\varphi^n)$ *(2×)*
- **Cambio di variabile** — $T(\sqrt n)+1$ → $\Theta(\log\log n)$ *(3×)*
## 1.C — Algoritmi e complessità
Per ogni richiesta: «quale algoritmo useresti e quanto costa». → ripasso note [[04 - Algoritmi di Ordinamento|04]]–[[10 - Cammini Minimi e Dijkstra|10]] · svolti [[1.C — Algoritmi e complessità]]
- **Ordinamento lineare, range polinomiale** — interi in $[1,n^k]$ → Radix base $n$ (anche $n\log\log n$) *(8×)*
- **Distanze/raggiungibilità inverse su $G^T$** — distanze di tutti verso $t$ *(9×)*
- **Forte connessione e CFC** — due DFS; 3 varianti: $\ge 2$ CFC / 1 sola CFC / arco nel DAG *(7×)*
- **Cammini minimi con vincoli** — nodo/arco proibito, pesi $\{1,2\}$, $\le k$ archi *(6×)*
- **Dijkstra da sorgente singola** — pesi non negativi, argmax distanze *(6×)*
- **Heapify** — costruire un heap da $n$ chiavi in $O(n)$ *(6×)*
- **Raggiungibilità su grafo** — BFS/DFS, anche con filtri sugli archi *(6×)*
- **Ordinamento lineare, range costante** — Integer Sort con offset (anche bit $\{0,1\}$) *(5×)*
- **Ricerca in lista concatenata ordinata** — sequenziale $O(n)$ *(5×)*
- **Costruzione AVL** — $n$ inserzioni → $O(n\log n)$ *(3×)*
- **Visita BST in-order** — chiavi in ordine crescente/decrescente *(3×)*
- **Selezione dei $k$ massimi/minimi** — heap, $O(n+k\log n)$ *(3×)*
- **$n$-esimo Fibonacci** — `fibonacci4` $O(n)$ o `fibonacci6` $O(\log n)$ *(3×)*
- **Ricerca binaria su vettore ordinato** — $O(\log n)$ *(3×)*
- **Selezione/navigazione in BST/AVL** — 2° minimo, predecessore, floor *(3×)*
- **Ordinamento per confronto generale** — MergeSort/HeapSort, Merge, Partition *(3×)*
- **Costruzione heap binomiale** — analisi ammortizzata $O(n)$ *(2×)*
- **Merge di heap binomiali** — $O(\log N)$ *(2×)*
- **Merge di heap binari** — Heapify sull'unione *(2×)*
- **Diametro grafo non pesato** — $n$ BFS *(2×)*
- **Inserzione batch in heap** — $k$ inserzioni vs rebuild *(2×)*
- **Cammino minimo per nodo intermedio** — $d(s,u)+d(u,t)=d(s,t)$ *(1×)*
- **Ordinamento topologico e DAG** — disporre i nodi su una linea *(1×)*
- **All-pairs shortest paths** — $n$ Dijkstra *(1×)*
- **Merge di AVL asimmetrici** — inserire il piccolo nel grande, $O(\log^2 n)$ *(1×)*
- **Costruzione dizionario per ricerche logaritmiche** — array ordinato/AVL, $O(n\log n)$ *(1×)*
- **Secondo massimo/minimo in vettore non ordinato** — scansione a 2 variabili, $O(n)$ *(1×)*
- **Distanze da più sorgenti, grafo non pesato** — una BFS per sorgente, $O(n+m)$ *(1×)*
## Esercizio 2 — Progettazione (8 punti)
Progettare un algoritmo con pseudocodice rispettando un bound dato. → svolti nella cartella `Esercizio 2/` (un file per esercizio).
- **DFS top-down su albero binario** — contare nodi/foglie con condizione cumulativa sugli antenati *(8×)* · [[01 - DFS top-down su albero binario|svolto]]
- **Precalcolo di array ausiliari** — run left/right, prev/next, first/last per valore *(3×)* · [[02 - Precalcolo di array ausiliari|svolto]]
- **Struttura oracolo** — preprocessing $O(n)$, query $O(1)$ o $O(\log n)$ *(3×)* · [[03 - Struttura oracolo|svolto]]
- **Ordinamento/conteggio come preprocessing** — Integer Sort con outlier, ordina+due puntatori, conteggio+interleaving *(3×)* · [[04 - Ordinamento e conteggio come preprocessing|svolto]]
- **Grafo modificato strutturalmente** — archi extra (inversi o di teletrasporto) + SCC o Dijkstra *(2×)* · [[07 - Grafo modificato strutturalmente|svolto]]
- **Intersezione/appartenenza su insiemi** — hash set o sort+merge, memoria $o(N)$ *(2×)* · [[08 - Intersezione e appartenenza su insiemi|svolto]]
- **Scansione con prefix sum** — primo indice prefisso vs suffisso, $O(1)$ spazio *(1×)* · [[05 - Scansione lineare con prefix sum|svolto]]
- **DFS post-order su albero binario** — aggregare contatori dal basso (discendenti) *(1×)* · [[06 - DFS post-order su albero binario|svolto]]
- **Sliding window con BST** — finestra di $k$, $O(n\log k)$ *(1×)* · [[09 - Sliding window con BST|svolto]]
## Esercizio 3 — Modellazione (8 punti)
Problema "a parole" da modellare e risolvere con un algoritmo efficiente. → svolti nella cartella `Esercizio 3/` (un file per esercizio).
- **Grafo degli stati aumentato** — stato discreto (parità, colore, tempo) + BFS/Dijkstra *(5×)* · [[01 - Grafo degli stati aumentato|svolto]]
- **Multi-run Dijkstra** — tappe obbligatorie, combinazione lineare *(4×)* · [[02 - Multi-run Dijkstra|svolto]]
- **DFS con stato cumulativo top-down** — la proprietà dipende dal cammino dalla radice *(3×)* · [[03 - DFS con stato cumulativo top-down|svolto]]
- **Prefix sums 1D** — preprocessing $O(n)$, query $O(1)$ *(2×)* · [[04 - Prefix sums 1D|svolto]]
- **Ordinamento + binary search/merge** — proprietà su coppie/insiemi *(2×)* · [[05 - Ordinamento con binary search o merge|svolto]]
- **BFS su grafo implicito / 0-1 BFS** — griglia o sequenza, deque *(2×)* · [[06 - BFS su grafo implicito e 0-1 BFS|svolto]]
- **Binary search su prefix sums monotone** — oracolo parametrico *(1×)* · [[07 - Binary search su prefix sums monotone|svolto]]
- **Selezione online dei $k$ migliori** — max-heap di taglia $k$ *(1×)* · [[08 - Selezione online con max-heap|svolto]]
- **Forte connettività con modifica locale** — inversione archi di un nodo *(1×)* · [[09 - Forte connettività con modifica locale|svolto]]
- **Binary search on answer** — parametro ottimale + BFS di verifica *(1×)* · [[10 - Binary search on answer|svolto]]
- **Prefix sums 2D** — range sum query su matrice *(1×)* · [[11 - Prefix sums 2D|svolto]]
- **Scansione $O(1)$ spazio** — prefisso vs suffisso su due sequenze *(1×)* · [[12 - Scansione lineare in spazio costante|svolto]]
