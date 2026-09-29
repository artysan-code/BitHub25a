---
tipo: corso
materia: Basi di Dati e di Conoscenza
codice: BDC
anno: 2
semestre: "2"
cfu: 9
ssd: INF/01
docenti:
  - Paola Vocca
propedeuticita:
  - Matematica Discreta
  - Programmazione dei Calcolatori con Laboratorio
---
# Basi di Dati e di Conoscenza
Corso della prof.ssa **Paola Vocca** (`paola.vocca@uniroma2.it`) dedicato alla teoria delle basi di dati e del modello relazionale, alle metodologie di progettazione (concettuale, logica, fisica), ai linguaggi di interrogazione (algebra, calcolo, SQL) e alla programmazione avanzata di basi di dati (viste, trigger, transazioni, normalizzazione). Le propedeuticità (Matematica Discreta, Programmazione dei Calcolatori con Laboratorio) sono vincolanti solo per il CdL in Informatica.
**Ricevimento**: lunedì 11:00–12:00 su appuntamento (studio o online); disponibile anche durante e dopo ogni lezione.
## Modalità d'esame
L'esame si compone di **tre prove in sequenza**, da superare nell'ordine indicato:
1. **Prova scritta.** Verifica la parte teorica e la capacità di risolvere esercizi (progettazione concettuale e logica, interrogazioni in algebra relazionale e SQL, normalizzazione).
2. **Progetto.** Realizzazione completa di un database tratto da una realtà a piacere.
   - Si svolge in **gruppi da 2 o 3 persone**.
   - Viene assegnato circa **un mese prima della fine del corso**.
   - L'argomento è approvato **su proposta del gruppo**, presentando il **modello concettuale** della realtà scelta.
   - Si accede al progetto **solo dopo aver superato la prova scritta** e seguendo le linee guida fornite dal docente.
3. **Prova orale.** Accessibile **solo se la prova scritta è superata e il progetto è approvato**. Consiste nella discussione del progetto e di domande sulla parte teorica.

> Materiale ufficiale per il progetto in `Materiale Didattico/Progetto/` (linee guida e template, anno 2025-26). La proposta del nostro gruppo è in [[Dominio applicativo]].
## Programma e Appunti
Gli appunti seguono l'ordine logico del corso. Il numero di nota e l'argomento sono mappati alle slide ufficiali del docente.
### Fondamenti e modelli dei dati
- [[Basi di Dati e di Conoscenza/Appunti/01 - Introduzione|01 - Introduzione]] — Dati, informazioni e sistemi informativi; basi di dati e DBMS; archivio di file vs approccio DBMS; condivisione.
- [[02 - Modelli di dati]] — Modello logico e concettuale; schema e istanza; architettura ANSI/SPARC a tre livelli; indipendenza fisica e logica dei dati; DDL e DML.
- [[03 - Modello Relazionale]] — Relazione matematica; strutture posizionali e non; modello basato sui valori; schemi e istanze; valore nullo.
- [[04 - Vincoli di integrità]] — Vincoli di dominio, di ennupla e interrelazionali; chiavi e superchiavi; chiave primaria; integrità referenziale e azioni compensative.
- [[05 - Entity Relationship]] — Progettazione concettuale; entità, associazioni, attributi e cardinalità; generalizzazione IS-A; diagrammi delle classi UML.
### Progettazione di basi di dati
- [[06 - Progettazione di Basi di Dati]] — Metodologia di progettazione; ciclo di vita di un sistema informativo; le tre fasi (concettuale, logica, fisica); raccolta dei requisiti; strategie di progettazione concettuale.
- [[07 - Progettazione Logica]] — Analisi delle prestazioni su schemi E-R; ristrutturazione dello schema (ridondanze, eliminazione delle generalizzazioni, partizionamento, scelta degli identificatori); traduzione E-R → modello relazionale.
### Linguaggi di interrogazione formali
- [[08 - Algebra Relazionale]] — Operatori insiemistici; ridenominazione, selezione, proiezione; prodotto cartesiano e join (naturale, theta, esterni); divisione; espressioni e viste.
- [[09 - Calcolo Relazionale]] — Calcolo sui domini e sulle ennuple; quantificatori; espressioni non sicure; equivalenza con l'algebra; cenni a Datalog.
### SQL
- [[10 - SQL DDL e DML]] — Tipi di dato MySQL; `CREATE`/`ALTER`/`DROP`; vincoli e azioni referenziali; `INSERT`, `UPDATE`, `DELETE`.
- [[11 - SQL Interrogazioni]] — `SELECT-FROM-WHERE`; join; funzioni di aggregazione; `GROUP BY` e `HAVING`; interrogazioni nidificate; operatori insiemistici; logica a tre valori.
- [[12 - Viste e Controllo degli Accessi]] — Viste virtuali e materializzate; aggiornabilità e `WITH CHECK OPTION`; funzioni condizionali; `GRANT`/`REVOKE`, privilegi e ruoli.
### Programmazione avanzata e teoria della normalizzazione
- [[13 - Basi di Dati Attive e Transazioni]] — Paradigma ECA; trigger e stored procedure; transazioni e proprietà ACID; cenni a concorrenza e affidabilità.
- [[14 - Normalizzazione]] — Anomalie; dipendenze funzionali e assiomi di Armstrong; chiusure; forme normali (1NF, 2NF, 3NF, BCNF); normalizzazione per decomposizione; 4NF e 5NF.
### Modulo 12 CFU
Note in `Appunti/Modulo 12 CFU/`, relative al modulo da 12 CFU del corso (il piano di studi attuale prevede 9 CFU): approfondimenti su progettazione fisica, transazioni e NoSQL.
- [[15 - Indici e Progettazione Fisica]] — Progettazione fisica; organizzazione fisica dei dati; indici e loro definizione in SQL; esecuzione e ottimizzazione delle interrogazioni.
- [[16 - Organizzazione Fisica dei Dati]] — Architettura del DBMS; memoria principale e secondaria; buffer management; blocchi e record; strutture sequenziali, file hash e indici di file; strutture fisiche nei DBMS relazionali.
- [[17 - Progettazione Logica e SQL (Esercitazione)]] — Esercitazione: da schema relazionale a schema Entità-Relazione; interrogazioni SQL; cardinalità dei risultati di espressioni di join.
- [[18 - Gestione delle Transazioni]] — Transazioni e proprietà ACIDE; gestore dell'affidabilità (log, checkpoint, dump, guasti, restart); controllo di concorrenza e anomalie.
- [[19 - Database NoSQL]] — Esigenze e caratteristiche dei database NoSQL; famiglie di database NoSQL; MongoDB, BigTable/HBase, Linked Open Data.
- [[20 - Database NoSQL e MongoDB (Approfondimento)]] — Big Data storage e limiti degli RDBMS; modelli di dati NoSQL; introduzione, installazione e uso di MongoDB.
## Materiale di riferimento
- **Libro di testo** (prima parte del corso): Atzeni, Ceri, Fraternali, Paraboschi, Torlone — *Basi di dati. Modelli e linguaggi di interrogazione*, McGraw-Hill, 6ª edizione.
- **SQL**: manuali in linea indicati dal docente (sintassi MySQL).
- **Slide del corso**: in `Materiale Didattico/Slide/`.
- **Esercitazioni** (con soluzioni) in `Materiale Didattico/Esercitazioni/`: dipendenze funzionali, forme normali, normalizzazione e progettazione fisica, progettazione concettuale-logica.
- **Progetto**: linee guida e template in `Materiale Didattico/Progetto/` (edizioni 2023-24 e 2025-26).
## Struttura della cartella
```
Basi di Dati e di Conoscenza/
├── README.md                 # questo file
├── Appunti/                  # note .md (01–14) + assets/
│   └── Modulo 12 CFU/        # note .md (15–20)
├── Progetto/                 # proposta e documenti del progetto del gruppo
└── Materiale Didattico/
    ├── Slide/                # slide ufficiali del docente
    ├── Esercitazioni/        # tracce ed esercizi svolti con soluzioni
    └── Progetto/             # linee guida e template del progetto d'esame
```
