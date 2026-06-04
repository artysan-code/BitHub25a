---
tags:
  - basi-di-dati
  - lezione
slide: "03-ModelliDati.pdf"
---
## DBMS vs File system
L'efficienza di un sistema si misura (come in tutti i sistemi informatici) in termini di:
- **tempo** di esecuzione (tempo di risposta) e spazio.
- **memoria** (principale e secondaria).
I DBMS, a causa della varietà di funzioni, non sono necessariamente più efficienti dei file system. L'efficienza è il risultato della qualità del DBMS e delle applicazioni che lo utilizzano.
La gestione di insiemi di dati grandi e persistenti è possibile anche attraverso sistemi più semplici — gli ordinari **file system** dei sistemi operativi. Tuttavia:
- I file system prevedono forme rudimentali di condivisione: "tutto o niente". Nei DBMS, è consentita una **maggiore flessibilità**.
- I DBMS **estendono** le funzionalità dei file system, fornendo più servizi ed in maniera integrata (efficacia).
### Catalogo o dizionario
Nei programmi tradizionali che accedono a file, ogni programma contiene una descrizione della struttura del file stesso, con i conseguenti rischi di incoerenza fra le descrizioni (ripetute in ciascun programma) e i file stessi.
Nei DBMS, esiste una porzione della base di dati chiamata **catalogo** o **dizionario** che contiene una descrizione centralizzata dei dati, che può essere utilizzata dai vari programmi. Questo elimina le inconsistenze e rende la gestione molto più affidabile.
## Modello di rappresentazione dei dati
I DBMS non sono progettati per gestire un unico caso d'uso; al contrario, sono software in grado di gestire **dati eterogenei**. Al fine di creare e gestire la corrispondente base di dati, uno **schema dei dati** deve essere fornito al DBMS.
Lo schema viene costruito secondo un **modello di dati** ben definito: una collezione di costrutti usati per descrivere lo schema dei dati, le loro relazioni e i vincoli di consistenza che devono essere applicati sugli stessi. Tramite questo schema si fornisce al DBMS una rappresentazione dei dati in modo da permettere l'organizzazione della gestione.
Le descrizioni e rappresentazioni dei dati a livelli diversi consentono l'indipendenza dei dati dalla rappresentazione fisica:
- I programmi fanno riferimento alla struttura a livello più alto, e le rappresentazioni sottostanti possono essere modificate senza necessità di intervenire sui programmi.
- Questo fondamentale concetto viene realizzato attraverso il **modello dei dati**.

> [!quote] Definizione — Modello di dati
> Un insieme di concetti utilizzati per organizzare i dati di interesse e descriverne la struttura in modo che essa risulti comprensibile ad un elaboratore (e non solo).

La **Definizione di Ullman** lo descrive come un formalismo matematico composto da:
- Una notazione per descrivere i dati.
- Un insieme di operazioni per manipolare tali dati.
Da queste considerazioni deriva quindi la seguente definizione completa:

> [!quote] Definizione completa — Modello di dati
> Un insieme di costrutti utilizzati per organizzare i dati di interesse e descriverne la **struttura** e la **dinamica**. In particolare è costituito da:
> - **Costrutti sintattici** per definire i dati
> - **Regole semantiche** per interpretarli
> - **Linguaggi** per manipolarli

### Tipologie di modelli nei DBMS
Nei DBMS esistono due principali tipologie di modelli:
- **Modello logico**
- **Modello concettuale**
#### Modello Logico
Esistono diverse tipologie di modelli logici definiti nel tempo. Descrivono l'organizzazione dei dati nei DBMS **visibile all'utente**, sono indipendenti dalle strutture fisiche e comprendono:
- **Modelli gerarchici** e **reticolari**: utilizzano riferimenti espliciti (puntatori) fra record.
- **Modello ad oggetti** (ODBMS, Object Database Management System): l'informazione è rappresentata in forma di oggetti. Utilizzato in un mercato di nicchia rispetto al modello relazionale (applicazioni real time).
- **Modello relazionale** (RDBMS): basato sui valori. Anche i riferimenti fra dati in strutture (relazioni) diverse sono rappresentati per mezzo dei valori stessi.
#### Modello Concettuale
I modelli concettuali hanno l'obiettivo di descrivere i **concetti** del mondo reale e vengono impiegati nelle fasi iniziali della progettazione. I principali sono:
- **Entity-Relationship (ER)**
- **Modello Classi Associazioni** (UML)
### Esempio: organizzazione dei dati in un RDBMS

> [!example] Tabella studenti
> | Nome  | Cognome | Matricola | Voto medio |
> |-------|---------|-----------|------------|
> | Mario | Rossi   | 1         | 24         |
> | Luigi | Bianchi | 2         | 28         |
> | Rosa  | Rossa   | 3         | 26         |

## Schemi ed Istanze
In ogni base di dati esistono due concetti fondamentali:
- Lo **schema**, sostanzialmente invariante nel tempo, che descrive la struttura della base di dati (**aspetto intensionale**). Nell'esempio della tabella, corrisponde alle intestazioni delle colonne (Nome, Cognome, Matricola, Voto medio).
- L'**istanza**, ovvero i valori attuali, che possono cambiare anche molto rapidamente (**aspetto estensionale**). Nell'esempio, corrisponde al "corpo" della tabella, cioè le righe con i dati.
## Architettura di un DBMS
Nel nostro caso studiamo l'architettura **Standard ANSI/SPARC a tre livelli**:
```
utente  utente    utente    utente  utente
  |       |          |        |       |
Schema  Schema    Schema  Schema  Schema
esterno esterno  esterno esterno esterno
  \       |        /
       Schema logico
            |
       Schema interno
            |
           BD
```
I tre schemi fondamentali sono:
- **Schema logico**: descrizione della base di dati nel modello logico del DBMS.
- **Schema fisico** (o interno): rappresentazione dello schema logico per mezzo di strutture di memorizzazione (file).
- **Schema esterno** (o vista): descrizione di parte della base di dati in un modello logico — "viste" parziali, derivate, anche in modelli diversi.
### Esempio: le Viste
> [!example] Viste — CorsiSedi
> Dati due schemi base **Corsi** (Corso, Docente, Aula) e **Aule** (Nome, Edificio, Piano), è possibile definire uno schema esterno **CorsiSedi** (Corso, Aula, Edificio, Piano) che combina le informazioni delle due tabelle, senza modificare lo schema logico sottostante.

### Analogia con la programmazione (matrici)
> [!example] Analogia — Livelli e matrici
> | Livello | Esempio |
> |---|---|
> | **Concettuale/logico** | `int a[n][m];` — dichiarazione della struttura |
> | **Fisico** | `a[i][j]` si trova alla locazione $a_0 + 4(m(i-1)+j-1)$ |
> | **Esterno (vista)** | $f(i) = \sum_{j=1}^{m} a[i][j]$ — somma riga i-esima |

## Indipendenza dei dati
L'indipendenza dei dati è una conseguenza dell'articolazione in livelli. L'accesso avviene solo tramite il livello esterno (che può coincidere con quello logico) e si presenta in due forme:
- **Indipendenza fisica**: si parla di indipendenza fisica quando il livello logico e quello esterno sono indipendenti da quello fisico. Una relazione è utilizzata nello stesso modo qualunque sia la sua realizzazione fisica; la **realizzazione fisica** può cambiare senza che debbano essere modificati i programmi.
- **Indipendenza logica**: si parla di indipendenza logica quando il livello esterno è indipendente da quello logico. Aggiunte o modifiche alle viste non richiedono modifiche al livello logico. Le modifiche allo schema logico che lasciano inalterato lo schema esterno sono **trasparenti**.
## Linguaggi per basi di dati
Esistono due tipologie di linguaggi per le operazioni su una base di dati:
- **DDL: data definition language** — operazioni **sullo schema**:
```SQL
create table orario(
	insegnamento char(20),
	docente      char(20),
	aula         char(4),
	ora          char(5)
)
```
- **DML: data manipulation language** — operazioni **sull'istanza** (i dati):
```SQL
select docente
from orario
where aula = 'N1';
```
I DBMS dispongono di diversi linguaggi e interfacce:
- **Linguaggi testuali interattivi** (SQL): si scrivono ed eseguono query direttamente.
```SQL
SELECT Corso, Aula, Piano
FROM Aule, Corsi
WHERE Aula = 'N3' AND Piano = 'Terra';
```
- **Comandi SQL immersi in un linguaggio ospite** (Java, C, Spark, ecc.): il codice SQL è inserito all'interno di un programma scritto in altro linguaggio (es. `EXEC SQL`).
- **Comandi SQL immersi in un linguaggio ad hoc** (es. Oracle PL/SQL): linguaggi proprietari che estendono SQL con strutture di controllo (if/then, loop, eccezioni, ecc.).
- **Interfacce grafiche amichevoli** (senza linguaggio testuale): come Microsoft Access, che consente di costruire query visivamente.
## Attori del sistema
A livello professionale le figure applicate alle Basi di Dati sono le seguenti:
- **Progettisti e realizzatori di DBMS**.
- **Progettisti della base di dati** e amministratori della base di dati (**DBA**, Database Administrator).
- **Progettisti e programmatori di applicazioni**.
- **Utenti**:
	- **finali** (terminalisti): eseguono applicazioni predefinite (*transazioni*).
	- **casuali**: eseguono operazioni non previste a priori, usando linguaggi interattivi.

> [!quote] Definizione — Transazione
> Attività eseguita periodicamente e di cui vengono calcolate e previste le eccezioni. In senso più specifico, una transazione è una sequenza indivisibile di operazioni: o vengono eseguite tutte o nessuna.

## Pro e contro dei DBMS
- **Pro**
	- dati come risorsa comune, base di dati come modello della realtà
	- gestione centralizzata con possibilità di standardizzazione ed "economia di scala"
	- disponibilità di servizi integrati
	- riduzione di ridondanze e inconsistenze
	- indipendenza dei dati (favorisce lo sviluppo e la manutenzione delle applicazioni)
- **Contro**
	- costo dei prodotti e della transizione verso di essi
	- non scorporabilità delle funzionalità (con riduzione di efficienza nei casi d'uso semplici)
