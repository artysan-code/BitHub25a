# Ricerca Operativa
**Codice**: RO · **CFU**: 6 · **Semestre**: 2 · **Anno**: 2°
**SSD**: MAT/09
**Docente**: Caramia
**Propedeuticità**: nessuna

---
## 📚 Argomenti del Corso (Syllabus per l'Esonero e l'Esame)
Sulla base del materiale didattico aggiornato e delle dispense del corso, il programma completo si struttura nei seguenti macro-argomenti:
### 1. Modellazione Matematica (PL e PLI)
* Introduzione all'ottimizzazione e Programmazione Lineare.
* Linearizzazione di funzioni Min-Max, Max-Min e minimizzazione del valore assoluto.
* Vincoli Logici e Metodo del "Big-M" (attivazione impianti, costi fissi, implicazioni if-then).
* *Riferimento negli appunti:* `1 - Modellazione Matematica.md`
### 2. Geometria della PL e Basi
* Insiemi poliedrali, vertici, direzioni.
* Basi, Soluzioni di Base (SB), Soluzioni di Base Ammissibili (SBA) e Basi Degeneri.
* Trasformazione del problema in **Forma Standard** (variabili slack/surplus).
* *Riferimento negli appunti:* `2 - Geometria della PL e Forma Standard.md`
### 3. Algoritmi: Il Metodo del Simplesso
* Algoritmo iterativo su Tableau: calcolo costi ridotti, variabile entrante, test del quoziente (variabile uscente) e operazione di pivot.
* Test di ottimalità e condizioni di illimitatezza.
* Prevenzione dei cicli in caso di degenerezza: **Regola di Bland**.
* **Metodo del Simplesso a due fasi** (per trovare la base identità iniziale quando mancano variabili di slack).
* *Attenzione:* Il "Simplesso Duale" **non** è in programma (usare le Due Fasi negli esercizi d'esame vecchi).
* *Riferimento negli appunti:* `3 - Metodo del Simplesso e Due Fasi.md`
### 4. Teoria della Dualità
* Regole per la costruzione del problema Duale.
* Teoremi della Dualità Debole e Forte.
* Condizioni degli **Scarti Complementari (Ortogonalità)** per la verifica dell'ottimalità.
* *Riferimento negli appunti:* `4 - Teoria della Dualità e Scarti Complementari.md`
### 5. Programmazione Lineare Intera (PLI)
* Il Rilassamento Lineare e l'ottenimento di Bound superiori/inferiori.
* Algoritmo enumerativo del **Branch and Bound** (Taglio per infattibilità, ottimalità e bound).
* Matrici **Totalmente Unimodulari (TUM)** e loro risoluzione naturale con PL.
* *Riferimento negli appunti:* `5 - Programmazione Lineare Intera e Branch&Bound.md`
### 6. Laboratorio Pratico
* Utilizzo del software **AMPL** per la risoluzione computazionale di modelli.

---
## 🗂️ Struttura della Repository
* **`/Appunti/`**: Appunti testuali completi in Markdown, riscritti come **spiegazione pedagogica partendo da zero**. Ogni file include: introduzione motivazionale, definizioni precise, intuizione geometrica/economica, esempi numerici, errori frequenti, callout per i punti chiave, riferimenti puntuali alle dispense.
* **`/Esercizi/`**: Svolgimenti passo-passo. Per ogni argomento c'è almeno un esempio completo; gli errori frequenti sono evidenziati con callout `[!warning]`.
* **`/Materiale Didattico/`**: 
  * `m01.modPL.01.modelli.pdf`: Dispensa fondamentale sulla Modellazione (De Giovanni-Brentegani — inclusi vincoli logici e Big-M).
  * `Appunti Aggiuntivi/`: Slide su Branch&Bound, PLI e appunti su Dualità / Basi.
  * `Esami/`: Raccolta di testi d'esame (2019-2020).
  * `Materiale Teams/`: Ultime slide (Teoria Simplesso, Esercizi, AMPL) e testi d'esame più recenti, inclusa la nota d'esame.

## 📖 Come usare questi Appunti
Ogni file `Appunti/` è autosufficiente: si può leggere da zero, anche senza aver mai visto la materia. La progressione consigliata:
1. `1 - Modellazione` → imparare a tradurre problemi reali in PL/PLI.
2. `2 - Geometria della PL` → capire perché l'ottimo sta sui vertici.
3. `3 - Simplesso` → l'algoritmo che salta da vertice a vertice.
4. `4 - Dualità` → la teoria "specchio" che certifica l'ottimalità.
5. `5 - PLI e B&B` → estensione al caso intero.

## ⚠️ Note per lo Studio
* L'Esonero tipicamente copre la parte di **Modellazione**, la **Geometria** e il **Simplesso (con Due Fasi)**. 
* *Dualità* e *Branch & Bound* solitamente fanno parte della seconda metà del corso/esame.
* Il "Simplesso Duale" **non** è in programma (usare le Due Fasi negli esercizi d'esame vecchi).
