---
tipo: corso
materia: Algoritmi per i Big Data
codice: ABD
anno: 3
semestre: "1"
cfu: 6
ssd: INF/01
docenti:
  - Andrea Clementi
propedeuticita:
  - Algoritmi e Strutture Dati
  - Matematica Discreta
  - Calcolo delle Probabilità e Statistica
---
# Algoritmi per i Big Data
Corso del terzo anno che estende Algoritmi e Strutture Dati ai grandi insiemi di dati: modelli e algoritmi per risolvere problemi su input massivi e complessi.
## Modalità d'esame
Regole dell'a.a. 2026-27 come le ha spiegate il docente a lezione (06/10/2026).
- **Solo orale**, di circa 35-40 minuti, senza supporto di IA. Si porta un **argomento a piacere**, ma non basta saperlo a memoria: partono domande di base (vettori, strutture dati, inserimento di un elemento in una struttura, in qualunque linguaggio) a cui si risponde **per iscritto sul foglio**, con codice e passaggi matematici formalizzati.
- **Data Science**: il corso vale 9 CFU, con un progetto e un'integrazione del programma concordata con il docente, verificata in sede d'esame. Per Informatica restano 6 CFU.
- Secondo DidatticaWEB (A.A. 2025/2026) la valutazione è scritta e orale, senza obbligo di frequenza; ricevimento per appuntamento via email.
## Programma e Appunti
Programma del corso ancora da completare. Gli appunti sono organizzati per argomento: ogni nota raccoglie tutte le lezioni su quell'argomento, una sezione per lezione. Manca la lezione 5 (20/10/2026), di cui non c'è registrazione.
1. [[01 - Introduzione al corso e al data mining]]
	- Lezione 1 (06/10/2026): organizzazione e prerequisiti, i due step del data mining, esempio del phishing (sketch, pesi, soglia, falsi positivi e negativi), anomalie statistiche e grafo delle "gang" (clique attese), data stream e query tipiche, page ranking.
2. [[02 - Algoritmi randomizzati e probabilità]]
	- Lezione 2 (08/10/2026), [[02 - Algoritmi randomizzati e probabilità#Algoritmi randomizzati|algoritmi randomizzati]]: Monte Carlo e Las Vegas, identità tra polinomi, richiami di probabilità (union bound, probabilità condizionata e totale), verifica del prodotto tra matrici (Freivalds), taglio minimo (Karger) e amplificazione per ripetizione.
	- Lezione 3 (13/10/2026), [[02 - Algoritmi randomizzati e probabilità#Variabili aleatorie e valore atteso|variabili aleatorie e valore atteso]]: spazio di probabilità generato da un algoritmo randomizzato (Karger rivisto, lemma sulla contrazione, alta probabilità), variabili aleatorie e indipendenza, valore atteso e mediana, linearità del valore atteso, Bernoulliana e binomiale, analisi del randomized quicksort.
	- Lezione 4 (15/10/2026), [[02 - Algoritmi randomizzati e probabilità#Analisi del caso medio e disuguaglianze di concentrazione|analisi del caso medio e concentrazione]]: algoritmi randomizzati e analisi del caso medio (quicksort deterministico su permutazioni uniformi), errore bilaterale, unilaterale e Las Vegas, distribuzione geometrica e assenza di memoria, coupon collector, varianza, disuguaglianze di Markov e di Chebyshev.
	- Lezione 6 (22/10/2026), prima parte, [[02 - Algoritmi randomizzati e probabilità#Bound di Chernoff e bilanciamento del carico|bound di Chernoff e bilanciamento del carico]]: ripresa della mediana con il campionamento, bound di Chernoff (forme superiori e inferiori, confronto con Chebyshev, scostamenti $\sqrt{n\log n}$), bilanciamento del carico con assegnazione casuale: carico massimo $\Theta(\log n/\log\log n)$ con $n$ job, carico uniforme con $\Theta(n\log n)$ job.
3. [[03 - Ricerca di oggetti simili]]
	- Lezione 6 (22/10/2026), seconda parte, [[03 - Ricerca di oggetti simili#Trovare oggetti simili|trovare oggetti simili]]: rappresentazione e similarità, nearest neighbor e all similar pairs, barriera quadratica, distanza di Jaccard, la pipeline shingling, min-hashing e locality-sensitive hashing.
	- Lezione 7 (27/10/2026), [[03 - Ricerca di oggetti simili#Shingling e min-hashing|shingling e min-hashing]]: il problema della similarità tra documenti, similarità di Jaccard, $k$-shingle di un documento e matrice shingle × documenti, sketch e firme, min-hashing e matrice delle firme, teorema $\Pr[h_\pi(C_1)=h_\pi(C_2)]=\mathrm{Sim}(C_1,C_2)$, stima della similarità con più permutazioni indipendenti.
	- Lezione 8 (29/10/2026), [[03 - Ricerca di oggetti simili#Locality-sensitive hashing|locality-sensitive hashing]]: dimostrazione del teorema del min-hashing, stima con $t$ permutazioni e spazio della firma, costo delle permutazioni casuali e funzioni hash al loro posto, algoritmo per la matrice delle firme, perché serve l'LSH, tecnica delle bande, esempio con $b=20$ e $r=5$, curva a S e scelta di $b$ e $r$.
4. [[04 - Funzioni hash universali]]
	- Lezione 9 (03/11/2026), [[04 - Funzioni hash universali#Hashing universale|hashing universale]]: problema del dizionario, perché una funzione deterministica non basta, la funzione perfettamente casuale e il suo costo, famiglie universali e lunghezza attesa delle liste di trabocco, costruzione $h_a(x)=\sum_ia_ix_i\bmod m$ e dimostrazione dell'universalità, retta casuale $((ax+b)\bmod p)\bmod m$ e indipendenza a coppie, raddoppio e dimezzamento.
## Materiale di riferimento
- **Slide** in `Materiale Didattico/Slide/`: quelle effettivamente usate a lezione, scaricate dal canale Teams (aggiornato settimanalmente; alcune sono versioni dell'a.a. 2025-26). Che le slide del Mitzenmacher-Upfal siano state proiettate risulta dalle registrazioni delle lezioni 2, 4 e 6; il docente consiglia comunque di studiare sul libro. Ogni nota indica nel frontmatter (`slide`) i PDF usati e, nella riga di ogni lezione, l'intervallo di pagine:
	- `Ch01_Algo4BigData_Andy_10_2025.pdf`: lezione 1 ([[01 - Introduzione al corso e al data mining]]);
	- `MITZ_UPFAL_Chapter-1.pdf` … `Chapter-4.pdf` (slide di E. Upfal sul libro di Mitzenmacher e Upfal, *Probability and Computing*): lezioni 2-6 ([[02 - Algoritmi randomizzati e probabilità]]);
	- `Ch03-ABD-Andy_SLIDES 3.pdf` (capitolo 3, *Finding Similar Items*, pp. 10-69): lezioni 6-8 ([[03 - Ricerca di oggetti simili]]);
	- `HASH_FUNCTIONS_LUCIO_ANDY_11-25.pdf` (L. Gualà e A. Clementi, pp. 1-18; le pp. 19-26 sul *perfect hashing* sono per la lezione successiva): lezione 9 ([[04 - Funzioni hash universali]]);
	- non ancora usati, e quindi non nel repo: `SLIDES_LSH_PREZZA_11_2026.pdf` (MinHash e LSH), `ch04_2_ABD_Andy_SLIDES.pdf` (stream: filtri di Bloom, Flajolet-Martin, AMS) e, come dispense di riferimento, le note di N. Prezza (*Algorithms for Massive Data*), di J. Nelson (*Sketching Algorithms*) e di C. Seshadhri su Flajolet-Martin.
- **Teams**: canale «Algoritmi per i Big Data», riferimento per tutte le comunicazioni e il materiale (a senso unico: i docenti non lo leggono ogni giorno). Per appuntamenti e chiarimenti si scrive al docente via **mail** (clementi@mat.uniroma2.it).
- **Docenti**: Andrea Clementi; dalla seconda settimana interviene anche Luca Pepe (nome come trascritto, da verificare) per la parte su probabilità e algoritmi randomizzati.
- I libri di testo sono disponibili online (indicazioni precise ancora da raccogliere).
## Propedeuticità
Per affrontare il corso sono considerate necessarie le seguenti *propedeuticità*:
- Algoritmi e Strutture di Dati (Il corso dopotutto è un estensione di questo)
- Matematica Discreta (Base anche per Algoritmi)
- Calcolo delle Probabilità e Statistica (Necessario per comprendere molti algoritmi statistici)
