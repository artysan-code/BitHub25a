# Algoritmi e Strutture Dati
**Codice**: ASD · **CFU**: 9 *(da confermare su Didattica Web)* · **Semestre**: 1-2 · **Anno**: 2°
**SSD**: INF/01
**Docente**: Luciano Gualà
**Propedeuticità**: Programmazione dei Calcolatori con Laboratorio · (consigliata) Matematica Discreta
Corso diviso in **due moduli** tenuti dallo stesso docente: **Modulo A** (= Modulo I) e **Modulo B** (= Modulo II). Riguarda l'analisi e la progettazione di **algoritmi efficienti**: strumenti teorici per l'analisi e principali tecniche di progettazione (greedy, divide-et-impera, programmazione dinamica).
## Programma
### Modulo A — Modulo I
Notazione asintotica; metodi per stimare la complessità di algoritmi ricorsivi; il problema dell'ordinamento; strutture dati efficienti per implementare **dizionari** e **code con priorità**; algoritmi efficienti per visitare i **grafi**.
### Modulo B — Modulo II
Principali tecniche di progettazione algoritmica (greedy, divide-et-impera, programmazione dinamica): problemi di **scheduling**, **cammini minimi** su grafi pesati, **minimo albero di copertura (MST)**, **distanza di edit** fra parole; **flussi di rete** (max-flow/min-cut) e loro applicazioni; introduzione alla **teoria dell'NP-completezza** dal punto di vista algoritmico.
## Modalità d'esame
**6 appelli** all'anno (2 a giugno-luglio, 2 a settembre, 2 a febbraio). In ogni appello si può sostenere il **Modulo 1, il Modulo 2 o entrambi**; ogni modulo prevede una **prova scritta e un orale**. I voti parziali sono mantenuti per tutto l'anno accademico (fino a febbraio 2027 incluso).
Sono previsti **1-2 Problem Set opzionali** che valgono **fino a 3 punti in più** sul voto del modulo (consegne in LaTeX, vedi `Materiale Didattico/Modulo I/Problem Set/`). Le tracce d'esame 2021-2026 sono in `Materiale Didattico/Esami/`. Per le regole aggiornate fa fede **Didattica Web**.
## Appunti
Gli appunti sono slide-grounded e standardizzati. **Modulo I** in `Appunti/Modulo I/`:
1. [[01 - Il Problema di Fibonacci]] — caso di studio: analisi di tempo/spazio, dalla ricorsione esponenziale alla potenza di matrici $O(\log n)$.
2. [[02 - Notazioni Asintotiche]] — modello RAM, casi peggiore/medio, $O,\Omega,\Theta,o,\omega$, metodo dei limiti.
3. [[03 - Equazioni di Ricorrenza]] — iterazione, albero di ricorsione, sostituzione, Teorema Master, cambio di variabile.
4. [[04 - Algoritmi di Ordinamento]] — quadratici, divide-et-impera, Heap Sort, lower bound $\Omega(n\log n)$, ordinamenti lineari.
5. [[05 - Strutture Dati Elementari e Dizionari]] — pila, coda, dizionario, rappresentazioni e visite di alberi.
6. [[06 - Alberi di Ricerca BST e AVL]] — BST e bilanciamento AVL con le 4 rotazioni.
7. [[07 - Code con Priorità e Heap]] — heap d-ari, binomiali, cenni Fibonacci.
8. [[08 - Grafi e Visite]] — rappresentazioni, BFS, DFS.
9. [[09 - Applicazioni della DFS]] — tempi pre/post, archi, cicli, ordinamento topologico, SCC.
10. [[10 - Cammini Minimi e Dijkstra]] — SSSP con pesi non negativi.
**Modulo II** in `Appunti/Modulo II/`:
1. [[01 - Greedy e Interval Scheduling]] — paradigma greedy, interval scheduling e partitioning.
2. [[02 - Union-Find]] — insiemi disgiunti, QuickFind/QuickUnion, union by rank e path compression.
3. [[03 - Minimum Spanning Tree]] — cut/cycle property, algoritmi di Kruskal e Prim.
4. [[04 - Programmazione Dinamica I (Weighted Independent Set)]] — principi della DP, insieme indipendente di peso massimo.
5. [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] — weighted interval scheduling, segmented least squares, knapsack, LIS.
6. [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]] — distanza di edit, Hirschberg, Bellman-Ford.
7. [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] — Ford-Fulkerson, teorema max-flow min-cut.
8. [[08 - Applicazioni dei Flussi di Rete]] — matching bipartito, cammini disgiunti, image segmentation, baseball elimination.
9. [[09 - NP-Completezza e Riduzioni]] — riduzioni polinomiali, SAT, Vertex Cover, cenni di approssimazione.
## Perimetro del Modulo I (mappa argomento ↔ nota ↔ slide ↔ libro)
| Argomento | Nota | Slide | Capitolo |
|---|---|---|---|
| Fibonacci e analisi di algoritmi | 01 | 1-2 | cap. 1 |
| Notazioni asintotiche | 02 | 1, 3 | cap. 2 |
| Equazioni di ricorrenza | 03 | 4 | cap. 2 |
| Ordinamento (confronti e lineari) | 04 | 5-7 | cap. 4 |
| Strutture elementari e dizionari | 05 | 8 | cap. 3 |
| Alberi di ricerca BST e AVL | 06 | 9 | cap. 6 |
| Code con priorità e heap | 07 | 10 | cap. 8 |
| Grafi e visite (BFS/DFS) | 08 | 11-12 | — |
| Applicazioni della DFS | 09 | 13 | Dasgupta-Papadimitriou-Vazirani, cap. 3 |
| Cammini minimi (Dijkstra) | 10 | 14 | — |
## Perimetro del Modulo II (mappa argomento ↔ nota ↔ slide ↔ libro)
| Argomento | Nota | Slide | Capitolo (KT) |
|---|---|---|---|
| Greedy: interval scheduling e partitioning | 01 | 01 | cap. 4 |
| Union-Find | 02 | 02 | (Demetrescu) |
| Minimum Spanning Tree (Kruskal, Prim) | 03 | 03 | cap. 4 |
| DP: principi, weighted independent set | 04 | DP I | (Demetrescu cap. 16) |
| DP: interval scheduling pesato, knapsack, LIS | 05 | DP II | cap. 6 |
| DP: sequence alignment, Hirschberg, Bellman-Ford | 06 | DP III | cap. 6 |
| Flussi: max-flow, min-cut, Ford-Fulkerson | 07 | Network Flow I | cap. 7 |
| Applicazioni dei flussi di rete | 08 | Network Flow II | cap. 7 |
| NP-completezza e riduzioni | 09 | Intractability | cap. 8 |
## Materiale di riferimento
- **Modulo I — libro principale**: C. Demetrescu, I. Finocchi, G. F. Italiano — *Algoritmi e strutture dati*, McGraw-Hill (i `capN` delle slide ne seguono i capitoli). Integrazione per la lezione "usi della DFS": S. Dasgupta, C. Papadimitriou, U. Vazirani — *Algorithms*, McGraw-Hill, cap. 3.
- **Modulo II — libro principale**: J. Kleinberg, É. Tardos — *Algorithm Design*, Pearson-Addison Wesley (le slide sono preparate dal prof a partire da quelle di **Kevin Wayne**, Princeton); la struttura dati Union-Find segue anche Demetrescu-Finocchi-Italiano.
- **Slide ufficiali** del corso (prof. Gualà) in `Materiale Didattico/`.
## Crediti e fonti integrate
La fonte primaria e autorevole sono le **slide del prof. Gualà**: in caso di conflitto su definizioni, notazioni o complessità prevale sempre la slide. Le seguenti risorse di colleghi sono state usate come traccia di prosa e riscontro, sempre verificate contro le slide e **rielaborate** (non copiate):
- **Ionut Zbir** ([github.com/IonutZbir/University](https://github.com/IonutZbir/University)), stesso corso e docente: traccia per gli appunti del **Modulo I e del Modulo II**. Da questo repository sono inoltre importate — con attribuzione — le **soluzioni delle prove d'esame del Modulo I**, le **dispense svolte su Limiti e Ricorrenze**, e (Modulo II) le **raccolte di esercizi di Programmazione Dinamica** e una **soluzione di esercitazione discussa dal prof.** (tutte in `Esercizi/`).
- **Vittorio Porri** ([github.com/VittorioPorri/universita](https://github.com/VittorioPorri/universita)): codice di riferimento (ordinamento e strutture dati, Modulo I) e note di teoria del Modulo II (greedy, programmazione dinamica, max-flow) usate come riscontro.
- *Nota*: la nota su Hash Table presente nel repository di IZ è stata **esclusa** perché fuori dal programma del corso (nessuna slide dedicata).
