## Database NoSQL: esigenze e caratteristiche

I database **NoSQL** nascono per rispondere a esigenze diverse da quelle dei DBMS relazionali tradizionali:

- **grandi volumi di dati**, in continua crescita;
- **nessuna struttura dati regolare** da gestire;
- elementi **relativamente omogenei** fra loro, ma **senza relazioni** esplicite fra di essi;
- **tipi di operazione semplici**.

> [!example] Esempio — Twitter
> Un insieme di utenti che pubblicano tweet: poche collezioni di interesse (due entità: utenti e tweet), ma **massive**; poche operazioni (inserimento/aggiornamento utente, inserimento tweet); dati identificati da una chiave, ma solo **parzialmente strutturati**.

Da queste esigenze derivano le caratteristiche dei sistemi **NoSQL** (*Not only SQL*):

- gestire oggetti **non rigidamente strutturati**;
- gestire la **scalabilità** dei dati;
- offrire solo **alcune** delle funzionalità dei sistemi tradizionali (in cambio di prestazioni e scalabilità).

### "One size does not fit all"

Un principio guida: non esiste un'unica soluzione adatta a tutti i casi d'uso. I sistemi NoSQL puntano su:

- **grande scalabilità** (molti processori, partizionamento orizzontale dei dati, architetture distribuite a basso costo);
- **alta disponibilità**, **replicazione** e **consistenza eventuale** (*eventual consistency*);
- **accesso ai dati ad alte prestazioni**.

**Replicazione**:
- *Master-Slave Replication*
- *Master-Master Replication*

**Scalabilità**:
- *Sharding* (partizionamento dei file)
- accesso ai dati ad alte prestazioni

Altre caratteristiche comuni:
- il modello relazionale resta una base concettuale, ma **non è sufficiente**;
- **non richiedono uno schema** fisso;
- **adattabilità** a scenari applicativi diversi;
- linguaggi per dati semi-strutturati: **JSON**, **XML**;
- linguaggi di interrogazione **meno potenti** di SQL, basati su operazioni **CRUD** (Create, Read, Update, Delete) o **SCRUD**.

## Transazionalità? No, grazie

I sistemi NoSQL, in generale, **non offrono le proprietà ACID** (si veda [[18 - Gestione delle Transazioni]] per il confronto), ma seguono il principio **BASE**:

> [!quote] Definizione — BASE
> **B**asically **A**vailable, **S**oft state, **E**ventually consistent: il sistema è fondamentalmente disponibile, il suo stato può essere "morbido" (temporaneamente incoerente), ma diventa consistente col tempo.

> [!quote] Definizione — Teorema CAP
> In un sistema distribuito **non è possibile garantire simultaneamente**: **C**onsistency (consistenza), **A**vailability (disponibilità), **P**artition tolerance (tolleranza al partizionamento della rete).

I sistemi NoSQL, dovendo garantire disponibilità e tolleranza al partizionamento su larga scala, **sacrificano la consistenza forte** (immediata) in favore di una consistenza "eventuale".

## Categorie/famiglie di database NoSQL

Ogni categoria si basa su una specifica organizzazione dei dati:

1. **Key-value system**
2. **Document Store**
3. **Column-based store**
4. **Graph database**
5. Altri (ibridi, basati su XML, ...)

### 1. Key-value

I dati sono coppie chiave-valore definite dal programma (database "senza schema"). La struttura degli oggetti è trasparente al sistema e scelta dall'applicazione che vi accede.

- **Esempi**: Oracle NoSQL, DynamoDB (Amazon), Voldemort.
- Il valore della chiave può essere un record, un oggetto, un documento o una struttura più complessa.

### 2. Document Store

Gli oggetti hanno una struttura complessa (**documenti**), anche se organizzati in collezioni. Formato tipico: **JSON**. Gli indici secondari non sono predefiniti e non hanno un tipo fisso.

- **Esempi**: MongoDB e CouchDB.
- Identificati da: document id — JSON.

### 3. Column-based (o Extensible record store)

Collezioni (tabelle) senza struttura predefinita, eccetto una prima struttura di "famiglie" (**column families**), o gruppi di colonne. Possono essere annidate (*nested*).

- **Esempi**: BigTable (Google), HBase e HyperTable (open source).
- Identificati da: file di column families — partizionamento verticale.

### Column-based e Key-value

Sistemi NoSQL che uniscono concetti sia dei key-value store sia dei column-based store.

- **Esempio**: Apache Cassandra (Facebook).

### 4. Graph Database

Database adatti a tutti i dati che possono essere rappresentati efficientemente come grafi, anche di grandi dimensioni.

- **Esempi**: Neo4J o GraphBase, per topologie di rete e connessioni di traffico.
- Identificati da: grafi — *path expression*.

### Sistemi NoSQL ibridi

Combinano concetti di più categorie fra quelle discusse sopra.

- **Esempio**: OrientDB.

### Altri sistemi NoSQL

Basati sul modello a oggetti o sul modello XML nativo; in genere non offrono le stesse alte prestazioni e replicazione degli altri sistemi.

- **Esempio**: XML.

## MongoDB

### Obiettivi

MongoDB gestisce documenti **JSON** raccolti in **collezioni**, con l'obiettivo di offrire:

- **alte prestazioni**;
- **alta scalabilità**;
- **alta affidabilità**;
- un insieme di funzionalità **semplice ma completo**.

### Modello dei dati

I documenti sono memorizzati in collezioni, in formato **BSON** (*Binary JSON*):

```
dbcreateCollection("project", {capped:true, size:1310720, max:500})
dbcreateCollection("worker",  {capped:true, size:5242880, max:2000})
```

Ogni documento ha un solo campo obbligatorio, l'identificatore **`Object_id`**. Le collezioni **non hanno uno schema** fisso: documenti diversi nella stessa collezione possono avere strutture diverse.

### Strutture dei dati: tre approcci

Dato lo schema logico "Progetto — Lavoratori" (un progetto ha più lavoratori, con relative ore lavorate), MongoDB permette diverse strategie di modellazione, con un compromesso fra ridondanza e numero di accessi (analogo, concettualmente, alle scelte di ridondanza discusse in [[07 - Progettazione Logica]] per lo schema E-R):

**(1) Documento denormalizzato** — i lavoratori sono annidati direttamente dentro il documento del progetto:

```json
{ _id: "P1",
  Pname: "ProductX",
  Plocation: "Bellaire",
  Workers: [
    { Ename: "John Smith", Hours: 32.5 },
    { Ename: "Joice English", Hours: 20.0 }
  ]
};
```

**(2) Array annidato di riferimenti a documenti** — il progetto contiene solo gli id dei lavoratori, memorizzati come documenti separati:

```json
{ _id: "P1", Pname: "ProductX", Plocation: "Bellaire", WorkersId: ["W1","W2"] }
{ _id: "W1", Ename: "John Smith", Hours: 32.5 }
{ _id: "W2", Ename: "Joice English", Hours: 20.0 }
```

**(3) Documenti normalizzati** — analogo a una struttura relazionale, con il lavoratore che referenzia il progetto tramite `projectId` (concettualmente simile a una foreign key):

```json
{ _id: "P1", Pname: "ProductX", Plocation: "Bellaire" }
{ _id: "W1", Ename: "John Smith", projectId: "P1", Hours: 32.5 }
{ _id: "W2", Ename: "Joice English", projectId: "P1", Hours: 20.0 }
```

> [!info] Trade-off fra le tre strutture
> La denormalizzazione (1) riduce il numero di accessi per leggere un progetto completo coi suoi lavoratori, ma introduce ridondanza se un lavoratore compare in più progetti. La normalizzazione (3) evita la ridondanza ma richiede più interrogazioni (o join applicativi, dato che MongoDB non supporta join nativi come SQL). La soluzione (2) è una via di mezzo.

### Operazioni CRUD

**Insert**:

```
db.<Collection_name>.insert(<document(s)>)

Db.project.insert({_id:"P1", Pname:"ProductX", Plocation:"Bellaire"})

Db.worker.insert([
  {_id:"W1", Ename:"John Smith",   ProjectId:"P1", Hours:32.5},
  {_id:"W2", Ename:"Joice English", ProjectId:"P1", Hours:20}
])
```

**Delete e Update**:

```
db.<Collection_name>.remove(<condition>)
db.<Collection_name>.update(<condition>, <setclause>)
```

**Read**:

```
db.<Collection_name>.find(<condition>)

db.Project.find({}, {Ename:1, Hours:1});
```

### Caratteristiche aggiuntive

- **assenza di una definizione di schema**;
- **assenza di tipizzazione** dei dati.

### Confronto SQL vs MongoDB

| SQL | MongoDB |
|---|---|
| `select a,b from Users;` | `db.users.find({}, {a:1,b:1});` |
| `select * from users where age=33;` | `db.users.find({age:33});` |
| `select * from users where age=33 order by name;` | `db.users.find({age:33}).sort({name:1});` |
| `create index myind on users(name);` | `db.users.ensureIndex({name:1});` |

### Caratteristiche del sistema distribuito

- **Two-Phase Commit Protocol** (analogo, per lo scopo, al protocollo di commit a due fasi delle transazioni distribuite — non da confondere con il *Two Phase Locking* del controllo di concorrenza, si veda [[18 - Gestione delle Transazioni]]).
- **Replicazione** tramite *Replica Set*.
- **Sharding** (partizionamento orizzontale) e scalabilità orizzontale (*load balancing*):
  - **Range partitioning**
  - **Hash partitioning**

## BigTable / HBase

### Obiettivi di BigTable

- **Alta scalabilità**, gestendo diversi server e petabyte di dati da memorizzare.
- **Controllo delle prestazioni**.
- **Continuità e tolleranza ai guasti** (*Fault Tolerance*).
- Generazione di **mappe ordinate multidimensionali**.

Sistema di storage distribuito, per dati semi-strutturati, basato sul **Google File System**.

### Formato dei dati: SSTable

- Formato **SSTable**: mappa persistente, ordinata e immutabile di associazioni chiave-valore, viste come stringhe arbitrarie.
- **Chiavi multidimensionali**.
- **Colonna**: combinazione di *column family* e *column qualifier*.

### Modello dei dati BigTable/HBase

I concetti fondamentali del modello sono:

- **Namespace**
- **Table**
- **Column** (`Column family : Column qualifier`)
- **Row**
- **Data cell**

Non è un modello relazionale, ma è basato sulla disposizione di ciascuna proprietà del database: è una **mappa multidimensionale**, ordinata, **sparsa**, distribuita e persistente, indicizzata per **chiave di riga**, **chiave di colonna** e **timestamp**. Le righe sono raggruppate dinamicamente; **non ci sono colonne predefinite**; ogni cella supporta il **multiversioning** dei dati (più valori nel tempo per la stessa cella, distinti per timestamp).

Una **tabella** è associata a **column family**: le column family associate a una tabella **non possono essere modificate** dopo la creazione della tabella.

```
Create 'EMP', 'Name', 'Address', 'Details'
```

Ogni column family può essere associata a molti **column qualifier** non specificati a priori. Una **colonna** è quindi la combinazione `ColumnFamily:ColumnQualifier`.

> [!example] Popolamento di una tabella EMP
> ```
> put 'EMP','row1','Name:Fname','John'
> put 'EMP','row1','Name:Lname','Smith'
> put 'EMP','row1','Name:Nickname','Johnny'
> put 'EMP','row1','Details:Job','Engineer'
> put 'EMP','row1','Details:Review','Good'
> put 'EMP','row2','Name:Fname','Alicia'
> put 'EMP','row2','Name:Lname','Zelaya'
> put 'EMP','row2','Name:Mname','Jennifer'
> put 'EMP','row2','Details:Job','DBA'
> put 'EMP','row2','Details:Supervisor','James Borg'
> put 'EMP','row3','Name:Fname','James'
> put 'EMP','row3','Name:Minit','E'
> put 'EMP','row3','Name:Lname','Borg'
> put 'EMP','row3','Name:Suffix','Jr.'
> put 'EMP','row3','Details:Salary','1,000,000'
> ```
> Si noti come righe diverse (`row1`, `row2`, `row3`) possano avere **qualifier diversi** all'interno della stessa column family (es. `row1` ha `Name:Nickname`, `row3` ha `Name:Minit` e `Name:Suffix`): questa è la natura "sparsa" e senza schema fisso del modello.

### Operazioni CRUD (basso livello)

```
Create <tablename>,<column family>,<column family>,...

Put <tablename>,<rowid>,<column family>:<column qualifier>,<value>

Scan <tablename>

Get <tablename>,<rowid>
```

## Linked Open Data

Il tema del **Linked Open Data** (introdotto a partire dal lavoro di **Tim Berners-Lee**) viene solo accennato nel materiale della lezione, senza contenuti testuali sviluppati oltre il titolo: l'argomento riguarda la pubblicazione e interconnessione di dati aperti sul Web secondo principi standard (identificatori URI, formati come RDF, collegamenti fra dataset), ma non è approfondito nelle slide disponibili.
