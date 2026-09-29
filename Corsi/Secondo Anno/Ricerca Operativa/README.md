---
tipo: corso
materia: Ricerca Operativa
codice: RO
anno: 2
semestre: "2"
cfu: 6
ssd: MAT/09
docenti:
  - Massimiliano Caramia
propedeuticita: []
---
# Ricerca Operativa
Corso del prof. **Caramia** di programmazione lineare (PL) e programmazione lineare intera (PLI): modellazione, geometria del poliedro, metodo del simplesso, dualità e Branch & Bound. Propedeuticità: nessuna.
## Modalità d'esame
Esame scritto con **esonero** sulla prima metà del corso. L'esonero tipicamente copre la **Modellazione**, la **Geometria** e il **Simplesso (con Due Fasi)**; **Dualità** e **Branch & Bound** fanno solitamente parte della seconda metà del corso e dell'esame. Testi d'esame in `Materiale Didattico/Esami/`.
## Programma e Appunti
Sulla base del materiale didattico aggiornato e delle dispense del corso, il programma per l'esonero e l'esame si struttura nei seguenti macro-argomenti. Gli **appunti** (`Appunti/`) sono testi completi in Markdown, riscritti come **spiegazione pedagogica partendo da zero**: ogni file include introduzione motivazionale, definizioni precise, intuizione geometrica/economica, esempi numerici, errori frequenti, callout per i punti chiave e riferimenti puntuali alle dispense. Gli **esercizi** (`Esercizi/`) sono svolgimenti passo-passo: per ogni argomento c'è almeno un esempio completo e gli errori frequenti sono evidenziati con callout `[!warning]`.
### 1. Modellazione Matematica (PL e PLI)
- Introduzione all'ottimizzazione e Programmazione Lineare.
- Linearizzazione di funzioni Min-Max, Max-Min e minimizzazione del valore assoluto.
- Vincoli Logici e Metodo del "Big-M" (attivazione impianti, costi fissi, implicazioni if-then).
- Note: [[01 - Modellazione Matematica]] · esercizi: [[01 - Esercizi Modellazione]]
### 2. Geometria della PL e Basi
- Insiemi poliedrali, vertici, direzioni.
- Basi, Soluzioni di Base (SB), Soluzioni di Base Ammissibili (SBA) e Basi Degeneri.
- Trasformazione del problema in **Forma Standard** (variabili slack/surplus).
- Note: [[02 - Geometria della PL e Forma Standard]] · esercizi: [[02 - Esercizi Vertici e Basi]], [[03 - Esercizi Forma Standard]]
### 3. Algoritmi: Il Metodo del Simplesso
- Algoritmo iterativo su Tableau: calcolo costi ridotti, variabile entrante, test del quoziente (variabile uscente) e operazione di pivot.
- Test di ottimalità e condizioni di illimitatezza.
- Prevenzione dei cicli in caso di degenerezza: **Regola di Bland**.
- **Metodo del Simplesso a due fasi** (per trovare la base identità iniziale quando mancano variabili di slack).
- Attenzione: il "Simplesso Duale" **non** è in programma (usare le Due Fasi negli esercizi d'esame vecchi).
- Note: [[03 - Metodo del Simplesso e Due Fasi]] · esercizi: [[04 - Esercizi Simplesso e Due Fasi]]
### 4. Teoria della Dualità
- Regole per la costruzione del problema Duale.
- Teoremi della Dualità Debole e Forte.
- Condizioni degli **Scarti Complementari (Ortogonalità)** per la verifica dell'ottimalità.
- Note: [[04 - Teoria della Dualità e Scarti Complementari]] · esercizi: [[05 - Esercizi Dualità e Scarti Complementari]]
### 5. Programmazione Lineare Intera (PLI)
- Il Rilassamento Lineare e l'ottenimento di Bound superiori/inferiori.
- Algoritmo enumerativo del **Branch and Bound** (taglio per infattibilità, ottimalità e bound).
- Matrici **Totalmente Unimodulari (TUM)** e loro risoluzione naturale con PL.
- Note: [[05 - Programmazione Lineare Intera e Branch&Bound]] · esercizi: [[06 - Esercizi Branch & Bound]]
### 6. Laboratorio Pratico
- Utilizzo del software **AMPL** per la risoluzione computazionale di modelli (laboratori in `Materiale Didattico/Esercitazioni/AMPL/`).
### Come usare gli appunti
Ogni file di `Appunti/` è autosufficiente: si può leggere da zero, anche senza aver mai visto la materia. La progressione consigliata:
1. [[01 - Modellazione Matematica]] → imparare a tradurre problemi reali in PL/PLI.
2. [[02 - Geometria della PL e Forma Standard]] → capire perché l'ottimo sta sui vertici.
3. [[03 - Metodo del Simplesso e Due Fasi]] → l'algoritmo che salta da vertice a vertice.
4. [[04 - Teoria della Dualità e Scarti Complementari]] → la teoria "specchio" che certifica l'ottimalità.
5. [[05 - Programmazione Lineare Intera e Branch&Bound]] → estensione al caso intero.
## Materiale di riferimento
Cartella `Materiale Didattico/`:
- `Slide/`: slide del docente (Teoria Simplesso, PLI, Dualità, riepilogo) e la dispensa fondamentale sulla Modellazione `m01.modPL.01.modelli.pdf` (De Giovanni-Brentegani — inclusi vincoli logici e Big-M).
- `Esercitazioni/`: esercizi del docente con soluzioni (formulazione, simplesso, primale-duale) e i laboratori `AMPL/`.
- `Esami/`: testi d'esame 2019-2020 ed `Esercizi d'esame/` più recenti, inclusa la nota d'esame.
- `Libri/`: dispensa sulla dualità.
- `Risorse Studenti/`: appunti scansionati su Branch&Bound, PLI, primale-duale e simplesso a due fasi, con esercizi svolti.
