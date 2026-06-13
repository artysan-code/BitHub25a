# Basi di Dati e di Conoscenza

**Codice**: bdc · **CFU**: 9 · **Semestre**: 2 · **Anno**: 2°
**SSD**: ING-INF/05
**Docente**: Paola Vocca — `paola.vocca@uniroma2.it`
**Ricevimento**: lunedì 11:00–12:00 su appuntamento (studio o online); disponibile anche durante e dopo ogni lezione.
**Propedeuticità**: Matematica Discreta, Programmazione dei Calcolatori con Laboratorio (vincolanti solo per il CdL in Informatica).

Corso dedicato alla teoria delle basi di dati e del modello relazionale, alle metodologie di progettazione (concettuale, logica, fisica), ai linguaggi di interrogazione (algebra, calcolo, SQL) e alla programmazione avanzata di basi di dati (viste, trigger, transazioni, normalizzazione).

## Modalità d'esame

L'esame si compone di **tre prove in sequenza**, da superare nell'ordine indicato:

1. **Prova scritta.** Verifica la parte teorica e la capacità di risolvere esercizi (progettazione concettuale e logica, interrogazioni in algebra relazionale e SQL, normalizzazione).
2. **Progetto.** Realizzazione completa di un database tratto da una realtà a piacere.
   - Si svolge in **gruppi da 2 o 3 persone**.
   - Viene assegnato circa **un mese prima della fine del corso**.
   - L'argomento è approvato **su proposta del gruppo**, presentando il **modello concettuale** della realtà scelta.
   - Si accede al progetto **solo dopo aver superato la prova scritta** e seguendo le linee guida fornite dal docente.
3. **Prova orale.** Accessibile **solo se la prova scritta è superata e il progetto è approvato**. Consiste nella discussione del progetto e di domande sulla parte teorica.

> Materiale ufficiale per il progetto in `Materiale Didattico/Materiale Progetto/` (linee guida e template, anno 2025-26).

## Materiale di riferimento

- **Libro di testo** (prima parte del corso): Atzeni, Ceri, Fraternali, Paraboschi, Torlone — *Basi di dati. Modelli e linguaggi di interrogazione*, McGraw-Hill, 6ª edizione.
- **SQL**: manuali in linea indicati dal docente (sintassi MySQL).
- **Slide del corso**: in `Materiale Didattico/Slide Lezione/`.
- **Esercitazioni** (con soluzioni) in `Materiale Didattico/Esercitazioni/`: dipendenze funzionali, forme normali, normalizzazione e progettazione fisica, progettazione concettuale-logica.

## Programma e indice degli appunti

Gli appunti seguono l'ordine logico del corso. Il numero di nota e l'argomento sono mappati alle slide ufficiali del docente.

### Fondamenti e modelli dei dati

- [[01 - Introduzione]] — Dati, informazioni e sistemi informativi; basi di dati e DBMS; archivio di file vs approccio DBMS; condivisione.
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

## Struttura della cartella

```
Basi di Dati e di Conoscenza/
├── README.md                 # questo file
├── Appunti/                  # note .md (01–14) + assets/
└── Materiale Didattico/
    ├── Slide Lezione/        # slide ufficiali del docente
    ├── Esercitazioni/        # tracce ed esercizi svolti con soluzioni
    └── Materiale Progetto/   # linee guida e template del progetto d'esame
```
