---
tipo: corso
materia: Algoritmi e Strutture Dati
codice: ASD
anno: 2
semestre: "1-2"
cfu: 9
ssd: INF/01
docenti:
  - Luciano Gualà
propedeuticita:
  - Programmazione dei Calcolatori con Laboratorio
---
# Algoritmi e Strutture Dati
Corso annuale del prof. **Luciano Gualà**, in due moduli (A = Modulo I, B = Modulo II): analisi e progettazione di **algoritmi efficienti** — strumenti teorici (notazioni asintotiche, ricorrenze) e tecniche di progettazione (greedy, divide-et-impera, programmazione dinamica). Propedeuticità: Programmazione dei Calcolatori con Laboratorio; consigliata Matematica Discreta.
## Modalità d'esame
**6 appelli** all'anno (2 a giugno-luglio, 2 a settembre, 2 a febbraio). In ogni appello si può sostenere **Modulo 1, Modulo 2 o entrambi**; ogni modulo prevede una **prova scritta e un orale**. I voti parziali sono mantenuti per tutto l'anno accademico (fino a febbraio 2027 incluso). Sono previsti **1-2 Problem Set opzionali** che valgono **fino a 3 punti in più** sul voto del modulo (consegne in LaTeX, in `Materiale Didattico/Slides/Modulo I/Problem Set/`). Tracce d'esame 2021-2026 in `Materiale Didattico/Esami/`. Per le regole aggiornate fa fede **Didattica Web**.
## Programma e Appunti
Le note seguono l'ordine del corso e coprono le slide del prof; lo slide e il capitolo di riferimento di ciascuna stanno nel suo frontmatter.
### Modulo I — `Appunti/Modulo I/`
1. [[01 - Il Problema di Fibonacci]] — analisi di tempo/spazio, dalla ricorsione esponenziale alla potenza di matrici $O(\log n)$.
2. [[02 - Notazioni Asintotiche]] — modello RAM, casi peggiore/medio, $O,\Omega,\Theta,o,\omega$, metodo dei limiti.
3. [[03 - Equazioni di Ricorrenza]] — iterazione, albero di ricorsione, sostituzione, Teorema Master, cambio di variabile.
4. [[04 - Algoritmi di Ordinamento]] — quadratici, divide-et-impera, Heap Sort, lower bound $\Omega(n\log n)$, ordinamenti lineari.
5. [[05 - Strutture Dati Elementari e Dizionari]] — pila, coda, dizionario, rappresentazioni e visite di alberi.
6. [[06 - Alberi di Ricerca BST e AVL]] — BST e bilanciamento AVL con le 4 rotazioni.
7. [[07 - Code con Priorità e Heap]] — heap d-ari, binomiali, cenni Fibonacci.
8. [[08 - Grafi e Visite]] — rappresentazioni, BFS, DFS.
9. [[09 - Applicazioni della DFS]] — tempi pre/post, archi, cicli, ordinamento topologico, SCC.
10. [[10 - Cammini Minimi e Dijkstra]] — SSSP con pesi non negativi.
### Modulo II — `Appunti/Modulo II/`
1. [[01 - Greedy e Interval Scheduling]] — paradigma greedy, interval scheduling e partitioning.
2. [[02 - Union-Find]] — insiemi disgiunti, QuickFind/QuickUnion, union by rank e path compression.
3. [[03 - Minimum Spanning Tree]] — cut/cycle property, algoritmi di Kruskal e Prim.
4. [[04 - Programmazione Dinamica I (Weighted Independent Set)]] — principi della DP, insieme indipendente di peso massimo.
5. [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] — weighted interval scheduling, segmented least squares, knapsack, LIS.
6. [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]] — distanza di edit, Hirschberg, Bellman-Ford.
7. [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] — Ford-Fulkerson, teorema max-flow min-cut.
8. [[08 - Applicazioni dei Flussi di Rete]] — matching bipartito, cammini disgiunti, image segmentation, baseball elimination.
9. [[09 - NP-Completezza e Riduzioni]] — riduzioni polinomiali, SAT, Vertex Cover, cenni di approssimazione.
## Materiale di riferimento
- **Modulo I**: C. Demetrescu, I. Finocchi, G. F. Italiano — *Algoritmi e strutture dati*, McGraw-Hill (le slide ne seguono i capitoli). Integrazione per la DFS avanzata: S. Dasgupta, C. Papadimitriou, U. Vazirani — *Algorithms*, McGraw-Hill, cap. 3.
- **Modulo II**: J. Kleinberg, É. Tardos — *Algorithm Design*, Pearson-Addison Wesley (slide del prof a partire da quelle di **Kevin Wayne**, Princeton); Union-Find anche da Demetrescu-Finocchi-Italiano.
- **Slide ufficiali** del corso (prof. Gualà) in `Materiale Didattico/Slides/`.
## Crediti e fonti integrate
La fonte primaria e autorevole sono le **slide del prof. Gualà**: in caso di conflitto su definizioni, notazioni o complessità prevalgono sempre. Le risorse seguenti sono state usate come traccia di prosa e riscontro, sempre verificate e **rielaborate** (non copiate):
- **Ionut Zbir** ([github.com/IonutZbir/University](https://github.com/IonutZbir/University)): traccia per la prosa di Modulo I e II; soluzioni delle prove d'esame del Modulo I; dispense su Limiti e Ricorrenze; (Modulo II) raccolte di esercizi di DP e una soluzione d'esercitazione discussa dal prof (tutto in `Esercizi/`). Esclusa la nota Hash Table: fuori dal programma del corso.
- **Vittorio Porri** ([github.com/VittorioPorri/universita](https://github.com/VittorioPorri/universita)): codice di ordinamento e strutture dati (Modulo I) e note di teoria su greedy, DP e max-flow (Modulo II), usati come riscontro.
