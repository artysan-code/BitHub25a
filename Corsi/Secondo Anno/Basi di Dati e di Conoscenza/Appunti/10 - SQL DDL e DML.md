## SQL: il linguaggio standard

**SQL** (originariamente *Structured Query Language*, oggi considerato un nome proprio) è il linguaggio standard per la definizione e la manipolazione delle basi di dati relazionali. Incorpora sia le funzionalità di **DDL** (*Data Definition Language*) sia quelle di **DML** (*Data Manipulation Language*), ed esiste in molte versioni dialettali legate ai singoli DBMS.

### Cenni storici

La prima proposta risale al **1974** con il linguaggio SEQUEL (IBM). Le prime implementazioni commerciali arrivarono nel **1981** con SQL/DS e Oracle. Dal **1983** circa SQL divenne lo "standard di fatto". Seguirono numerosi standard ISO ufficiali: 1986, 1989, 1992 (**SQL-92**), 1999 (**SQL:1999**), 2003, 2006, 2008, 2011, 2016 e oltre. Ogni standard è recepito solo *in parte* dai DBMS: le implementazioni reali (MySQL, PostgreSQL, Oracle, SQL Server) presentano estensioni e omissioni rispetto allo standard.

> [!info] Standard e dialetti
> SQL:1999 ha introdotto tipi booleani, BLOB/CLOB e caratteristiche orientate agli oggetti. MySQL implementa un sottoinsieme dello standard con estensioni proprietarie (es. `AUTO_INCREMENT`, `ENGINE`).

### Suddivisione funzionale

SQL comprende tre sotto-linguaggi principali:

- **DDL** (*Data Definition Language*): definizione e modifica della struttura della base di dati (schemi, tabelle, vincoli, indici).
- **DML** (*Data Manipulation Language*): manipolazione dei dati (inserimento, aggiornamento, cancellazione).
- **QL** (*Query Language*, spesso incluso nel DML): interrogazione dei dati tramite `SELECT`.

A questi si aggiunge il **DCL** (*Data Control Language*) per la gestione dei permessi (`GRANT`, `REVOKE`), non trattato in questa lezione.

## MySQL

> [!quote] Definizione — DBMS
> Un **DataBase Management System** (DBMS) è un sistema di gestione il cui obiettivo generale è mantenere le informazioni e renderle disponibili su richiesta. (J. Date)

Un DBMS deve garantire: condivisione dei dati, persistenza, affidabilità, privatezza, efficienza ed efficacia.

**MySQL** è un **RDBMS** (*Relational Database Management System*) open source, sviluppato e mantenuto da Oracle. È tra i più diffusi al mondo e incorpora funzionalità non open source nelle versioni enterprise a pagamento. Esiste un fork open-source attivo: **MariaDB**.

### Caratteristiche principali

- Basato su routine ISAM, scritto in C e C++.
- Storage engine preferibile: **InnoDB** (supporta transazioni, chiavi esterne, lock a livello di record, maggiore robustezza ai guasti). Alternativa: **MyISAM** (più efficiente, meno spazio, ma senza transazioni né foreign key).
- Interfacciabile da C, Java, Python e molti altri linguaggi.
- Nessun limite esplicito sulla dimensione del database o sul numero di tabelle (il limite massimo di righe dipende dai vincoli del sistema operativo).

### Connessione da terminale

L'interfaccia principale è una shell SQL a riga di comando. Per connettersi:

```sql
mysql -u utente -p password [-P porta -h host]
```

### Istruzioni di base

```sql
SHOW DATABASES;          -- visualizza tutti i database
USE nome_db;             -- seleziona il database da usare
CREATE DATABASE nome_db; -- crea un nuovo database
DROP DATABASE nome_db;   -- elimina il database (irreversibile)
EXIT;                    -- esci dalla shell
```

> [!warning] Il punto e virgola
> Ogni istruzione SQL deve terminare con `;`. In MySQL il punto e virgola chiude l'istruzione ed è obbligatorio nella shell interattiva.

## DDL — Data Definition Language

Il DDL serve a definire e modificare la **struttura** della base di dati: database, tabelle, vincoli, indici.

### Domini

SQL distingue due categorie di domini:

- **Domini elementari (predefiniti)**: tipi di dato built-in del DBMS.
- **Domini definiti dall'utente**: tipi semplici ma riutilizzabili, definiti tramite `CREATE DOMAIN` (standard SQL, supporto parziale in MySQL).

#### Tipi numerici

| Tipo | Intervallo (signed) | Note |
|---|---|---|
| `TINYINT` | $-128$ a $127$ (unsigned $0$–$255$) | intero su 1 byte |
| `SMALLINT` | $-32768$ a $32767$ (unsigned $0$–$65535$) | intero su 2 byte |
| `INT` / `INTEGER` | $-2.147.483.648$ a $2.147.483.647$ | intero su 4 byte |
| `FLOAT(M,D)` | — | $M$ cifre totali, $D$ decimali; singola precisione |
| `DOUBLE(M,D)` | — | come `FLOAT` ma a doppia precisione |
| `DECIMAL(M,D)` / `NUMERIC(M,D)` | — | numerico esatto; preferito per valori monetari |

#### Tipi alfanumerici

| Tipo | Descrizione |
|---|---|
| `CHAR(x)` | Stringa a lunghezza **fissa** di max 255 caratteri |
| `VARCHAR(x)` | Stringa a lunghezza **variabile** di max 255 caratteri |
| `TEXT` | Testo lungo fino a 65 535 byte |
| `BLOB` | Dato binario (*Binary Large Object*): file, immagini |

> [!warning] Indici su TEXT e BLOB
> Non creare indici su colonne di tipo `TEXT` o `BLOB`: MySQL non lo supporta in modo diretto e degraderebbe le prestazioni.

#### Tipi temporali

| Tipo | Formato | Note |
|---|---|---|
| `DATE` | `aaaa-mm-gg` | solo data |
| `TIME` | `hh:mm:ss` | solo ora |
| `DATETIME` | `aaaa-mm-gg hh:mm:ss` | data e ora |
| `YEAR` | `aaaa` | solo anno |
| `TIMESTAMP(x)` | variabile | $x$ da 2 a 14; aggiornato automaticamente |

#### Tipo booleano ed ENUM

`BOOLEAN` (introdotto in SQL:1999) memorizza `TRUE` o `FALSE`; in MySQL è implementato come `TINYINT(1)`.

`ENUM('val1', 'val2', ...)` consente di vincolare una colonna a un insieme finito di valori stringa. È utile per campi con dominio piccolo e fisso.

```sql
-- Esempio: colonna che ammette solo 'M' o 'F'
Sesso ENUM('M', 'F') NOT NULL
```

#### Domini definiti dall'utente (CREATE DOMAIN)

`CREATE DOMAIN` definisce un tipo riutilizzabile, eventualmente con vincoli e valore di default:

```sql
CREATE DOMAIN Voto
    AS SMALLINT DEFAULT NULL
    CHECK (value >= 18 AND value <= 30);
```

In MySQL il supporto a `CREATE DOMAIN` è limitato; in pratica si usa direttamente il tipo built-in con i vincoli inline sulla colonna.

### CREATE DATABASE / USE

```sql
CREATE DATABASE universita;
USE universita;
```

Il comando `CREATE DATABASE` e il sinonimo `CREATE SCHEMA` sono equivalenti in MySQL. `USE` seleziona il database corrente per le istruzioni successive.

### CREATE TABLE

La sintassi generale per creare una tabella è:

```sql
CREATE TABLE nome_tabella (
    nome_colonna tipo [opzioni_colonna],
    nome_colonna tipo [opzioni_colonna],
    ...
    [vincoli_di_tabella]
) [ENGINE=innodb];
```

Una tabella appena creata è **vuota**. Chi la crea possiede tutti i diritti su di essa.

Per le tabelle che devono supportare **chiavi esterne** e **transazioni** è obbligatorio usare `ENGINE=InnoDB`.

#### Opzione IF NOT EXISTS

```sql
CREATE TABLE IF NOT EXISTS nome_tabella (...);
```

Crea la tabella solo se non esiste già, evitando un errore.

> [!example] Schema di esempio — Dipartimento e Impiegato
> Useremo questo schema come filo conduttore per tutti gli esempi della lezione:
>
> `dept`(<u>dptno</u>, dname, loc)
> `emp`(<u>emp_id</u>, emp_name, sal, deptno FK→dept)

```sql
-- Creazione del database e selezione
CREATE DATABASE azienda;
USE azienda;

-- Tabella padre: dept
CREATE TABLE dept (
    dptno  INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
    dname  VARCHAR(30)  NOT NULL,
    loc    VARCHAR(50)
) ENGINE=InnoDB;

-- Tabella figlia: emp
CREATE TABLE emp (
    emp_id   INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
    emp_name VARCHAR(30)  NOT NULL,
    sal      FLOAT(4,2)   NOT NULL,
    deptno   INT          NOT NULL,
    FOREIGN KEY (deptno) REFERENCES dept(dptno)
        ON UPDATE CASCADE
        ON DELETE NO ACTION
) ENGINE=InnoDB;
```

### Vincoli di colonna e di tabella

I vincoli possono essere dichiarati **inline** (livello di colonna) oppure come clausola separata in coda alla lista delle colonne (livello di tabella).

#### NOT NULL

Impedisce che la colonna contenga `NULL`. Il DBMS rifiuta qualsiasi inserimento o aggiornamento che lascerebbe il campo senza valore (salvo che non esista un `DEFAULT`).

```sql
emp_name VARCHAR(30) NOT NULL
```

#### DEFAULT

Specifica il valore assunto da una colonna quando al momento dell'inserimento non viene fornito alcun valore. Il nuovo default sostituisce quello precedente.

```sql
numero_figli SMALLINT DEFAULT 0,
stipendio    INT      DEFAULT NULL
```

#### PRIMARY KEY

Definisce la **chiave primaria** della tabella. Implica automaticamente `NOT NULL` su tutte le colonne coinvolte. Può essere dichiarata a livello di colonna (chiave semplice) o di tabella (chiave composta):

```sql
-- Chiave semplice (livello colonna)
emp_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT

-- Chiave composta (livello tabella)
PRIMARY KEY (anno, numero)
```

`AUTO_INCREMENT` è un'estensione MySQL che incrementa automaticamente il valore intero a ogni inserimento; usato tipicamente per le chiavi surrogate.

#### UNIQUE

Impone che i valori nella colonna (o nella combinazione di colonne) siano tutti distinti. A differenza di `PRIMARY KEY`, ammette `NULL` (più righe possono avere `NULL`).

```sql
-- Livello colonna: ogni nome deve essere unico
Nome CHAR(20) NOT NULL UNIQUE

-- Livello tabella: la coppia (Nome, Cognome) deve essere unica
Nome    CHAR(20) NOT NULL,
Cognome CHAR(20) NOT NULL,
UNIQUE (Nome, Cognome)
```

> [!info] UNIQUE vs PRIMARY KEY
> `UNIQUE` definisce una **superchiave**; impone che non esistano due righe con la stessa combinazione di valori, ma non è la chiave primaria. `PRIMARY KEY` è una sola per tabella e comporta implicitamente `NOT NULL`.

#### CHECK

Permette di esprimere vincoli arbitrari su valori di colonna o di ennupla. La condizione deve essere soddisfatta da tutte le tuple in ogni momento.

```sql
-- Vincolo di colonna: sesso ammette solo 'M' o 'F'
Sesso CHAR(1) NOT NULL CHECK (Sesso IN ('M', 'F'))

-- Vincolo di tabella: lo stipendio non può superare quello del superiore
CHECK (Stipendio <= (SELECT Stipendio FROM Impiegato J
                    WHERE Superiore = J.Matricola))
```

> [!warning] CHECK in MySQL
> MySQL verifica la sintassi del `CHECK` ma nelle versioni precedenti alla 8.0.16 **non lo applica** a runtime. Per vincoli complessi è necessario usare trigger o logica applicativa.

#### FOREIGN KEY ... REFERENCES

Definisce un **vincolo di integrità referenziale**: impone che il valore dell'attributo referente sia presente come valore dell'attributo (unico o chiave primaria) della tabella referenziata.

```sql
FOREIGN KEY (deptno) REFERENCES dept(dptno)
    ON UPDATE CASCADE
    ON DELETE NO ACTION
```

La sintassi completa è:

```sql
FOREIGN KEY (col1, col2, ...) REFERENCES tabella_esterna(col1, col2, ...)
    [ON DELETE { CASCADE | SET NULL | SET DEFAULT | NO ACTION | RESTRICT }]
    [ON UPDATE { CASCADE | SET NULL | SET DEFAULT | NO ACTION | RESTRICT }]
```

> [!info] Posizione delle azioni referenziali
> Le clausole `ON DELETE` e `ON UPDATE` si specificano subito dopo `REFERENCES`, all'interno della definizione della foreign key.

### Azioni referenziali (ON DELETE / ON UPDATE)

Quando un'operazione sulla tabella **esterna** (referenziata) potrebbe violare l'integrità referenziale, il DBMS reagisce secondo la politica specificata:

| Politica | ON UPDATE | ON DELETE |
|---|---|---|
| `CASCADE` | Il nuovo valore dell'attributo esterno viene propagato a tutte le righe della tabella interna che vi fanno riferimento. | Tutte le righe corrispondenti della tabella interna vengono cancellate. |
| `SET NULL` | All'attributo referente viene assegnato `NULL`. | All'attributo referente viene assegnato `NULL`. |
| `SET DEFAULT` | All'attributo referente viene assegnato il valore di default. | All'attributo referente viene assegnato il valore di default. |
| `NO ACTION` | La modifica non viene consentita (errore). | La cancellazione non viene consentita (errore). |
| `RESTRICT` | Come `NO ACTION`; il controllo è immediato. | Come `NO ACTION`; il controllo è immediato. |

> [!example] Azioni referenziali — dept/emp
> Supponiamo che il dipartimento con `dptno = 10` venga rinominato (UPDATE) o eliminato (DELETE):
> - `ON UPDATE CASCADE`: tutte le righe di `emp` con `deptno = 10` aggiornano il valore al nuovo `dptno`.
> - `ON DELETE NO ACTION`: il DELETE del dipartimento viene rifiutato finché esistono impiegati che vi appartengono.
> - `ON DELETE SET NULL`: il campo `deptno` degli impiegati di quel dipartimento diventa `NULL` (richiede che la colonna ammetta `NULL`).

### Esempio completo: tabella Impiegato con vincoli

```sql
CREATE TABLE Impiegato (
    Matricola  CHAR(6)     PRIMARY KEY,
    Nome       CHAR(20)    NOT NULL,
    Cognome    CHAR(20)    NOT NULL,
    Sesso      CHAR(1)     NOT NULL CHECK (Sesso IN ('M', 'F')),
    Stipendio  INTEGER     DEFAULT 0,
    Superiore  CHAR(6),
    UNIQUE (Cognome, Nome),
    FOREIGN KEY (Nome, Cognome)
        REFERENCES Anagrafica(Nome, Cognome),
    FOREIGN KEY (Superiore)
        REFERENCES Impiegato(Matricola)
) ENGINE=InnoDB;
```

### DROP TABLE e DROP DATABASE

```sql
DROP TABLE emp;        -- elimina la tabella e tutti i suoi dati
DROP DATABASE azienda; -- elimina l'intero database
```

`DROP TABLE` elimina sia la struttura sia i dati in modo **irreversibile**. La variante con opzione (standard SQL):

```sql
DROP TABLE nome [ RESTRICT | CASCADE ]
```

- `RESTRICT`: non esegue il comando se esistono oggetti dipendenti (es. view, foreign key).
- `CASCADE`: rimuove anche tutti gli oggetti dipendenti. **Usare con estrema cautela.**

### ALTER TABLE — modifica dello schema

`ALTER TABLE` permette di modificare la struttura di una tabella esistente senza ricrearla.

```sql
-- Aggiunta di una colonna
ALTER TABLE emp ADD COLUMN email VARCHAR(100);

-- Eliminazione di una colonna
ALTER TABLE emp DROP COLUMN email;

-- Modifica del tipo o delle opzioni di una colonna
ALTER TABLE emp MODIFY COLUMN sal DOUBLE(6,2) NOT NULL;

-- Modifica del default di una colonna (sintassi standard)
ALTER TABLE emp ALTER COLUMN sal SET DEFAULT 0;
ALTER TABLE emp ALTER COLUMN sal DROP DEFAULT;

-- Aggiunta di un vincolo (il vincolo deve essere soddisfatto dai dati già presenti)
ALTER TABLE emp ADD CONSTRAINT fk_dept
    FOREIGN KEY (deptno) REFERENCES dept(dptno);

-- Rimozione di un vincolo
ALTER TABLE emp DROP CONSTRAINT fk_dept;

-- Rinomina della tabella
ALTER TABLE emp RENAME TO employee;

-- Rinomina (sintassi alternativa MySQL)
RENAME TABLE employee TO emp;
```

> [!warning] Vincoli aggiunti a posteriori
> Quando si aggiunge un nuovo vincolo con `ALTER TABLE ADD CONSTRAINT`, esso deve essere **soddisfatto dai dati già presenti** nella tabella. In caso contrario il comando fallisce.

### Indici (cenni)

Gli indici operano a livello **fisico** (non logico) e non cambiano la semantica della base di dati, ma migliorano le prestazioni delle interrogazioni. In passato erano l'unico mezzo per definire chiavi in certi sistemi; oggi questa funzione è svolta dai vincoli `PRIMARY KEY` e `UNIQUE`.

```sql
-- Creazione di un indice sulla colonna emp_name di emp
CREATE INDEX idx_nome ON emp(emp_name);

-- Eliminazione dell'indice
DROP INDEX idx_nome ON emp;
```

## DML — Data Manipulation Language

Il DML gestisce il **contenuto** delle tabelle tramite tre istruzioni: `INSERT`, `UPDATE`, `DELETE`.

### INSERT INTO

`INSERT` aggiunge una o più righe a una tabella.

**Sintassi con VALUES (inserimento singolo):**

```sql
INSERT INTO nome_tabella [(col1, col2, ...)]
VALUES (val1, val2, ...);
```

Se la lista di colonne è omessa, i valori devono corrispondere in numero e ordine a tutte le colonne della tabella. Se una colonna viene omessa dalla lista, assume il valore di `DEFAULT` (o `NULL` se non è definito un default).

**Inserimento multiplo:**

MySQL supporta l'inserimento di più righe in una sola istruzione:

```sql
INSERT INTO dept (dname, loc)
VALUES ('Informatica', 'Roma'),
       ('Contabilita', 'Milano'),
       ('Risorse Umane', 'Torino');
```

**Inserimento da interrogazione:**

```sql
INSERT INTO nome_tabella [(col1, col2, ...)]
SELECT ...;
```

> [!example] INSERT — esempi dalle slide
> ```sql
> -- Inserimento con lista completa (per posizione)
> INSERT INTO persone VALUES ('mario', 25, 52);
>
> -- Inserimento con lista esplicita di colonne
> INSERT INTO persone (nome, eta, reddito)
> VALUES ('pino', 25, 52);
>
> -- Inserimento omettendo una colonna (eta assumerà default o NULL)
> INSERT INTO persone (nome, reddito)
> VALUES ('lino', 55);
>
> -- Inserimento da interrogazione: aggiunge in persone i padri
> -- che non figurano già come persona
> INSERT INTO persone (nome)
> SELECT padre FROM paternita
> WHERE padre NOT IN (SELECT nome FROM persone);
> ```

> [!example] INSERT — schema aziendale
> ```sql
> -- Inserimento di un dipartimento
> INSERT INTO dept (dname, loc)
> VALUES ('Produzione', 'Torino');
>
> -- Inserimento di un impiegato (deptno deve esistere in dept)
> INSERT INTO emp (emp_name, sal, deptno)
> VALUES ('Wilson', 2500.00, 1);
> ```

### UPDATE

`UPDATE` modifica i valori di uno o più attributi nelle righe che soddisfano la condizione `WHERE`. Se `WHERE` è assente, la modifica viene applicata a **tutte** le righe della tabella.

**Sintassi:**

```sql
UPDATE nome_tabella
SET col1 = valore1,
    col2 = valore2, ...
WHERE condizione;
```

Il nuovo valore può essere: un'espressione calcolata sugli attributi della riga corrente, il risultato di una sottointerrogazione, `NULL`, oppure il valore di `DEFAULT`.

> [!example] UPDATE — esempi dalle slide
> ```sql
> -- Aggiornamento di una sola riga: Wilson diventa salesman con aumento del 10%
> UPDATE emp
>     SET job = 'salesman',
>         sal = 1.1 * sal
>     WHERE emp_name = 'Wilson';
>
> -- Aggiornamento di un insieme di righe:
> -- lo stipendio di tutti i salesman diventa il doppio della media
> UPDATE emp
>     SET sal = (SELECT 2 * AVG(sal) FROM emp WHERE job = 'salesman')
>     WHERE job = 'salesman';
> ```

> [!warning] Natura insiemistica di UPDATE
> SQL ha natura orientata agli **insiemi**, non alle tuple. Un `UPDATE` non si esegue riga per riga in sequenza, ma concettualmente sull'intero insieme delle righe selezionate. Questo ha conseguenze importanti quando la condizione e il valore modificato si riferiscono allo stesso attributo.
>
> **Esempio:** per aumentare del 10% gli stipendi $\leq 30$ e del 15% quelli $> 30$, eseguire i due `UPDATE` in ordine sbagliato può far rientrare alcune righe in entrambe le categorie e applicare due aumenti. La soluzione corretta è eseguire prima l'aumento maggiore:
> ```sql
> UPDATE Impiegato SET Stipendio = Stipendio * 1.15 WHERE Stipendio > 30;
> UPDATE Impiegato SET Stipendio = Stipendio * 1.10 WHERE Stipendio <= 30;
> ```

### DELETE

`DELETE` elimina le righe che soddisfano la condizione `WHERE`. Se `WHERE` è assente, **tutte** le righe vengono eliminate (la struttura della tabella rimane).

**Sintassi:**

```sql
DELETE FROM nome_tabella
WHERE condizione;
```

> [!example] DELETE — esempi dalle slide
> ```sql
> -- Elimina la riga dell'impiegato Wilson
> DELETE FROM emp
> WHERE emp_name = 'Wilson';
>
> -- Elimina le righe degli impiegati il cui job è in un insieme
> -- ricavato da una sottointerrogazione
> DELETE FROM emp
> WHERE job IN (SELECT job FROM job_da_eliminare);
>
> -- Elimina TUTTE le righe della tabella dept (la struttura rimane)
> DELETE FROM dept;
> ```

> [!warning] DELETE senza WHERE e CASCADE
> `DELETE FROM tabella;` svuota l'intera tabella. Se esistono **foreign key con politica CASCADE** verso questa tabella, le righe delle tabelle figlie vengono eliminate a catena. Prestare sempre attenzione all'impatto sulle tabelle dipendenti.

#### DELETE vs TRUNCATE

`TRUNCATE TABLE nome_tabella;` svuota la tabella in modo più rapido di `DELETE FROM nome_tabella;`, ma **non attiva i trigger** e non può essere usato quando ci sono foreign key attive che referenziano la tabella. In MySQL `TRUNCATE` non è reversibile con `ROLLBACK`.

## DDL — Vincoli di integrità

I vincoli visti nelle sezioni CREATE TABLE meritano un riepilogo sistematico.

### Vincoli intrarelazionali (su una sola tabella)

I vincoli intrarelazionali sono verificati dal DBMS ad ogni operazione di modifica. La violazione viene semplicemente **impedita** (l'operazione fallisce con errore).

| Vincolo | Sintassi di colonna | Sintassi di tabella |
|---|---|---|
| Valore non nullo | `NOT NULL` | — |
| Valore di default | `DEFAULT val` | — |
| Chiave primaria | `PRIMARY KEY` | `PRIMARY KEY (col1, col2)` |
| Unicità | `UNIQUE` | `UNIQUE (col1, col2)` |
| Verifica generica | `CHECK (condizione)` | `CHECK (condizione)` |

### Vincoli interrelazionali (FOREIGN KEY)

Per i vincoli referenziali, quando la violazione deriva da un cambiamento alla tabella **esterna**, si applicano le politiche `CASCADE`, `SET NULL`, `SET DEFAULT`, `NO ACTION`/`RESTRICT` come descritto in precedenza.

### Vincoli generici — CHECK

`CHECK` è il meccanismo più potente per esprimere vincoli arbitrari. Tuttavia:
- È meno leggibile di `NOT NULL` / `UNIQUE` / `FOREIGN KEY` per i casi semplici.
- Non supporta politiche di reazione alle violazioni (solo rifiuto dell'operazione).
- In MySQL < 8.0.16 è analizzato ma non applicato a runtime.

```sql
-- Vincolo che il dipartimento del superiore coincida con quello dell'impiegato,
-- oppure che la matricola inizi con '1'
Superiore CHAR(6),
CHECK (Matricola LIKE '1%' OR
       Dipart = (SELECT Dipart FROM Impiegato I
                 WHERE I.Matricola = Superiore))
```

### Asserzioni

Le **asserzioni** sono vincoli che fanno parte dello schema ma non sono associati a un singolo attributo o tabella. Permettono di esprimere vincoli su più tabelle o vincoli di cardinalità:

```sql
CREATE ASSERTION AlmenoUnImpiegato
    CHECK (1 <= (SELECT COUNT(*) FROM Impiegato));
```

Ogni vincolo è associato a una politica di controllo:
- **Immediato**: verificato dopo ogni singola modifica; in caso di violazione l'operazione viene annullata (*rollback parziale*). Tutti i vincoli predefiniti (`NOT NULL`, `PRIMARY KEY`, `FOREIGN KEY`, `UNIQUE`) sono immediati.
- **Differito**: verificato al termine della transazione. Se violato, viene annullata l'intera transazione (*rollback*).

Per cambiare la modalità di controllo di un vincolo nominato:

```sql
SET CONSTRAINTS NomeVincolo IMMEDIATE;
SET CONSTRAINTS NomeVincolo DEFERRED;
```
