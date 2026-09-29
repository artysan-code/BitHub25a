---
tipo: corso
materia: Architettura dei Sistemi di Elaborazione
codice: AE
anno: 1
semestre: "2"
cfu: 6
ssd: INF/01
docenti:
  - Alessandro Simonetta
propedeuticita: []
---
# Architettura dei Sistemi di Elaborazione
Corso del prof. **Alessandro Simonetta** sugli aspetti fondamentali dell'architettura dei sistemi di elaborazione, con riferimento ai principi di funzionamento dei microprocessori moderni e al rapporto tra architettura del calcolatore e software di base; richiede conoscenze sui sistemi di numerazione (binario, ottale, esadecimale).
## Modalità d'esame
Secondo DidatticaWEB (A.A. 2025/2026) la valutazione è scritta e orale.
<!-- Da completare -->
## Programma e Appunti
Riassunti del libro con integrazioni del corso, per comprendere i capitoli in minor tempo. Non sono affidabili a causa delle interpretazioni che ciascuno può avere: da usare per infarinature o per ripasso. Le note seguono la numerazione dei capitoli del libro.
### Architettura dei calcolatori
- `Appunti/Architettura dei Calcolatori/01 - Introduzione.md`: approccio strutturale, linguaggi, livelli e macchine virtuali, generazioni di computer, tipologie di computer (nome condiviso con l'introduzione dei Sistemi Operativi, quindi non linkabile in modo univoco).
- [[02 - Organizzazione dei sistemi di calcolo]]: processori (organizzazione della CPU, RISC e CISC, parallelismo a livello di istruzione e di processore), memoria principale, codici correttori, cache.
- [[03 - Livello logico digitale]]: porte logiche e algebra di Boole, circuiti digitali elementari, reti combinatorie, circuiti per l'aritmetica, clock, latch, flip-flop e registri.
- [[04 - Livello di microarchitettura]]: microarchitettura di esempio (percorso dati, microistruzioni, controllo microprogrammato Mic-1), ISA IJVM, esempi Core i7, OMAP4430, ATmega168.
- [[05 - Livello di architettura dell'insieme d'istruzioni]]: panoramica del livello ISA, modelli di memoria, registri, tipi di dati (Core i7, ARM OMAP4430, AVR ATmega168).
- [[07 - Livello del linguaggio Assemblativo]]: linguaggio assemblativo, pseudoistruzioni, macroistruzioni, assemblatori a due passate.
- [[08 - Architettura per il calcolo parallelo]]: parallelismo nel chip, multithreading, coprocessori, multiprocessori a memoria condivisa (UMA, NUMA, COMA).
### Sistemi operativi
- `Appunti/Sistemi Operativi/01 - Introduzione.md`: il sistema operativo come macchina estesa e gestore di risorse, storia dei sistemi operativi, analisi dell'hardware.
- [[02 - Processi e Thread]]: scheduling dei processi.
- [[03 - Gestione della Memoria]]: astrazione della memoria e spazi degli indirizzi, swapping, memoria virtuale e paginazione, algoritmi di sostituzione delle pagine.
- [[05 - Input & Output]]: principi hardware dell'I/O (controller, DMA, interrupt), principi e livelli del software di I/O.
### Esercizi
Spiegazioni sugli esercizi (la maggior parte) da saper svolgere con il professore; potranno essere aggiunti altri esercizi con collegamenti alla teoria.
- [[Domande ed Esercizi per Orale]]: domande teoriche pubblicate dal professore ed esercizi ARM.
- [[Algebra Booleana]], [[Codice di Hamming]], [[Conversioni]], [[Decodifica degli indirizzi]], [[Mappa di Karnaugh]] (architettura dei calcolatori).
- [[Modello Statistico di Multiprogrammazione]], [[Scheduling]] (sistemi operativi).
## Materiale di riferimento
Si cerca ogni anno di accomunare tutte le risorse fornite dal corso; la maggior parte dei materiali non è condivisibile per problemi di licenza d'uso. La sezione dispense è al momento sospesa perché non c'è materiale didattico ritenuto integrante per l'esame. La cartella `Materiale Didattico/` esiste solo in locale (contiene un archivio zip escluso da git).
## Note
Questa è la zona di repository dell'esame di Architettura dei Sistemi di Elaborazione. Ricordiamo che questi sono appunti presi da studenti e che non valgono come dispense affidabili dell'esame.
