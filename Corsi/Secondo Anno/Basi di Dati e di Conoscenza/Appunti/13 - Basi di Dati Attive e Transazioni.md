## Basi di Dati Attive e Transazioni

Questa lezione copre due macro-argomenti: le **basi di dati attive** — il paradigma reattivo basato su regole ECA, le stored procedure e i trigger — e le **transazioni**, unità atomiche di lavoro con le loro proprietà ACID.

## Basi di Dati Attive

> [!quote] Definizione — Base di dati attiva
> Una **base di dati attiva** è una base di dati che contiene *regole attive*, chiamate **trigger** o **stored procedure**, che vengono eseguite automaticamente in risposta a eventi che modificano lo stato del database.

Il contrasto con una base di dati *passiva* è netto: in una base di dati passiva il DBMS risponde solo a interrogazioni esplicite; in una base di dati attiva il DBMS reagisce autonomamente agli eventi, eseguendo logica applicativa interna al server.

Il modello di riferimento per le basi di dati attive è il paradigma **Evento-Condizione-Azione** (ECA), formalizzato dallo standard SQL:1999 e implementato (con varianti) da tutti i principali DBMS (MySQL, Oracle, DB2, SQL Server).

## Stored Procedure

> [!quote] Definizione — Stored procedure
> Una **stored procedure** è un insieme di istruzioni SQL precompilate e memorizzate nel database, invocabile per nome per eseguire un'operazione specifica.

### Vantaggi

- **Efficienza**: le istruzioni vengono compilate una volta e risiedono sul server, riducendo il traffico di rete rispetto all'invio ripetuto di query testuali.
- **Sicurezza**: l'accesso diretto alle tabelle può essere limitato; le operazioni consentite sono controllate dall'interfaccia della procedura.
- **Riutilizzabilità**: la procedura può essere richiamata da più punti dell'applicazione senza duplicare il codice SQL.

### Struttura

Una stored procedure è composta da tre parti:

- **Intestazione**: nome della procedura e lista dei parametri con il loro tipo (`IN`, `OUT`, `INOUT`).
- **Corpo**: le istruzioni SQL che realizzano l'operazione desiderata.
- **Ritorno**: eventuali valori di output restituiti tramite parametri `OUT` o come result set.

### Sintassi generale (MySQL)

In MySQL il delimitatore di default `;` è usato anche nelle istruzioni interne, quindi prima di creare una procedura occorre cambiarlo con `DELIMITER`.

```sql
DELIMITER $$

CREATE PROCEDURE nome_procedura (
    parametro1 tipo_dato,
    parametro2 tipo_dato
)
BEGIN
    -- corpo della procedura
    -- istruzioni SQL
END$$

DELIMITER ;
```

> [!info] DELIMITER in MySQL
> Il comando `DELIMITER $$` sostituisce temporaneamente il terminatore di istruzione con `$$`, in modo che il punto e virgola interno al corpo della procedura non venga interpretato come fine del comando `CREATE PROCEDURE`. Al termine si ripristina il delimitatore standard con `DELIMITER ;`.

### Esecuzione

```sql
CALL nome_procedura(valore1, valore2);
```

In SQL Server / T-SQL si usa invece `EXEC nome_procedura @param = valore`.

### Modifica e rimozione

```sql
DROP PROCEDURE nome_procedura;
```

Per modificare una procedura esistente in MySQL si esegue prima `DROP PROCEDURE` e poi si ricrea. In T-SQL esiste `ALTER PROCEDURE`.

> [!example] Stored procedure — calcolo media voti
> Procedura che calcola la media dei voti per un dato corso:
>
> ```sql
> DELIMITER $$
>
> CREATE PROCEDURE CalcolaMediaVoti (
>     corsoId INT
> )
> BEGIN
>     SELECT AVG(Voto) AS MediaVoti
>     FROM Voti
>     WHERE CorsoId = corsoId;
> END$$
>
> DELIMITER ;
>
> -- Chiamata:
> CALL CalcolaMediaVoti(123);
> ```

> [!example] Stored procedure — selezione clienti per città e CAP
> Procedura che restituisce i clienti di una città con un dato codice postale:
>
> ```sql
> DELIMITER $$
>
> CREATE PROCEDURE SelectAllCustomers (
>     City    VARCHAR(30),
>     PostalCode NVARCHAR(10)
> )
> BEGIN
>     SELECT * FROM Customers
>     WHERE  Customers.City       = City
>     AND    Customers.PostalCode = PostalCode;
> END$$
>
> DELIMITER ;
>
> -- Chiamata:
> CALL SelectAllCustomers('London', 'WA1 1DP');
> ```

## Trigger

> [!quote] Definizione — Trigger
> Un **trigger** è una stored procedure speciale, associata a una tabella, che viene eseguita *automaticamente* dal DBMS ogni volta che si verifica un determinato evento di modifica dei dati su quella tabella.

A differenza di una stored procedure ordinaria, un trigger **non può essere invocato manualmente**: si attiva solo in risposta a un evento.

### Il paradigma Evento-Condizione-Azione (ECA)

Il modello ECA è il nucleo concettuale delle basi di dati attive:

- **Evento** (*Event*): una modifica dello stato del database — tipicamente `INSERT`, `UPDATE` o `DELETE` su una tabella. Quando l'evento si verifica, il trigger viene *attivato*.
- **Condizione** (*Condition*): un predicato booleano (clausola `WHEN`) che viene valutato dopo l'evento. Se la condizione è vera, il trigger è *considerato* per l'esecuzione; altrimenti viene ignorato. La condizione è opzionale: se assente, l'azione viene sempre eseguita.
- **Azione** (*Action*): una sequenza di istruzioni SQL (o una chiamata a procedura) che costituisce la risposta del sistema. Quando l'azione viene eseguita, il trigger è *eseguito*.

> [!info] Computazioni reattive
> Il paradigma ECA consente **computazioni reattive**: la logica applicativa è incapsulata nel database e risponde automaticamente agli eventi, senza che l'applicazione client debba gestirla esplicitamente. Questo è il contributo principale delle basi di dati attive.

### Sintassi di CREATE TRIGGER (MySQL / SQL:1999)

```sql
CREATE TRIGGER trigger_name
{BEFORE | AFTER} {INSERT | UPDATE | DELETE}
ON table_name
FOR EACH ROW
BEGIN
    -- istruzioni SQL
END;
```

Parametri principali:

| Clausola | Significato |
|---|---|
| `trigger_name` | Nome univoco del trigger nel database |
| `BEFORE` / `AFTER` | L'azione si esegue *prima* o *dopo* l'evento |
| `INSERT` / `UPDATE` / `DELETE` | Evento che attiva il trigger |
| `ON table_name` | Tabella a cui il trigger è associato |
| `FOR EACH ROW` | Il trigger si esegue una volta per ogni riga coinvolta dall'evento (granularità *row-level*) |
| `BEGIN ... END` | Blocco contenente le istruzioni da eseguire |

### Momento di attivazione: BEFORE vs AFTER

- **BEFORE**: il trigger si esegue *prima* che la modifica venga effettivamente applicata alla tabella. Utile per validare o correggere i valori prima dell'inserimento (es. normalizzare un campo, bloccare valori non ammessi).
- **AFTER**: il trigger si esegue *dopo* che la modifica è stata applicata. Utile per propagare effetti su altre tabelle (log, valori derivati, audit).

### Granularità: FOR EACH ROW vs statement-level

- **FOR EACH ROW** (row-level): il trigger viene eseguito una volta per ciascuna riga modificata dall'istruzione scatenante. MySQL supporta *solo* questa granularità.
- **Statement-level**: il trigger viene eseguito una sola volta per l'intera istruzione, indipendentemente dal numero di righe coinvolte. Supportato da Oracle e DB2, non da MySQL.

### Variabili di transizione: NEW e OLD

All'interno del corpo di un trigger row-level sono disponibili due **pseudorecord** che rappresentano i valori della riga prima e dopo la modifica:

| Pseudorecord | Disponibile per | Contenuto |
|---|---|---|
| `NEW` | `INSERT`, `UPDATE` | Valori della riga *dopo* la modifica |
| `OLD` | `DELETE`, `UPDATE` | Valori della riga *prima* della modifica |

- In un trigger su `INSERT`: solo `NEW` è disponibile (non esiste un "vecchio" valore).
- In un trigger su `DELETE`: solo `OLD` è disponibile.
- In un trigger su `UPDATE`: entrambi sono disponibili.

L'accesso ai singoli attributi avviene con la notazione `NEW.nome_attributo` e `OLD.nome_attributo`.

### Esempi di trigger

> [!example] Trigger — monitoraggio pagamenti su conto (AFTER UPDATE)
> Dopo ogni aggiornamento della tabella `Account`, se il nuovo totale è maggiore del precedente (cioè è stato effettuato un addebito), si inserisce un record nella tabella `Pagamenti`:
>
> ```sql
> CREATE TRIGGER AccountMonitor
> AFTER UPDATE ON Account
> FOR EACH ROW
> BEGIN
>     INSERT INTO Pagamenti VALUES (
>         NEW.NumeroConto,
>         NEW.Totale - OLD.Totale
>     );
> END;
> ```
>
> La clausola `WHERE new.Totale > old.Totale` nella slide originale funge da condizione implicita; in MySQL si può scrivere come `IF NEW.Totale > OLD.Totale THEN ... END IF;` all'interno del blocco `BEGIN ... END`.

> [!example] Trigger — controllo riduzione stipendio (AFTER UPDATE OF)
> Impedisce che lo stipendio di un impiegato venga ridotto di più del 3% rispetto al valore precedente. Se la riduzione è eccessiva, ripristina il valore al 97% dell'originale:
>
> ```sql
> CREATE TRIGGER ControllaStipendi
> AFTER UPDATE ON Impiegato
> FOR EACH ROW
> BEGIN
>     IF NEW.Stipendio < OLD.Stipendio * 0.97 THEN
>         UPDATE Impiegato
>         SET    Stipendio = OLD.Stipendio * 0.97
>         WHERE  Matr = NEW.Matr;
>     END IF;
> END;
> ```
>
> Questo trigger implementa un **vincolo di integrità semantico** che non sarebbe esprimibile con un semplice `CHECK` (perché dipende dal confronto tra il valore precedente e quello nuovo).

### Usi tipici dei trigger

I trigger trovano applicazione in quattro scenari principali:

1. **Vincoli di integrità complessi o semantici**: vincoli che coinvolgono più tabelle o che dipendono dalla storia dei valori (es. uno stipendio non può scendere di più del 3%, un voto non può essere abbassato dopo la verbalizzazione).
2. **Valori derivati**: aggiornamento automatico di attributi calcolati (es. ricalcolo di un totale dopo ogni inserimento di riga di dettaglio).
3. **Audit e log**: registrazione automatica delle modifiche in una tabella di storico, con informazioni su chi ha modificato, quando e quale valore c'era prima.
4. **Azioni compensative**: esecuzione di operazioni di "riparazione" quando si verifica una condizione anomala (es. invio di una notifica, blocco di un'operazione non valida).

### Differenze tra trigger e stored procedure

| Caratteristica | Trigger | Stored procedure |
|---|---|---|
| Attivazione | Automatica, in risposta a un evento | Manuale, tramite `CALL` / `EXEC` |
| Parametri | Non ne riceve | Può ricevere parametri `IN`/`OUT`/`INOUT` |
| `COMMIT` / `ROLLBACK` | Non può eseguirli direttamente | Può gestire le transazioni |
| Invocazione diretta | Non possibile | Possibile |

> [!warning] Cascate di attivazione
> Un trigger può modificare dati che attivano altri trigger, che a loro volta ne attivano altri ancora: si parla di **cascata di attivazione**. Se non progettata con cura, una catena di trigger può generare cicli infiniti o comportamenti difficili da prevedere e debuggare. MySQL limita la ricorsione diretta (un trigger non può attivare se stesso), ma le cascate indirette rimangono un rischio di progetto.

## Transazioni

> [!quote] Definizione — Transazione
> Una **transazione** è un insieme di operazioni sulla base di dati da considerare come un'unità indivisibile ("atomica"), corretta anche in presenza di concorrenza e con effetti definitivi al termine dell'esecuzione con successo.

La transazione è l'unità fondamentale di lavoro nei DBMS. È il meccanismo che garantisce che operazioni logicamente correlate vengano trattate come un blocco unico: o tutte hanno effetto, oppure nessuna.

### Comandi SQL per le transazioni

Una transazione in SQL segue questo schema:

```sql
START TRANSACTION;   -- opzionale in molti DBMS; indica l'inizio esplicito

-- sequenza di istruzioni SQL
UPDATE ...;
INSERT ...;
DELETE ...;

COMMIT WORK;         -- oppure: ROLLBACK WORK;
```

- **`START TRANSACTION`** (o `BEGIN`): avvia esplicitamente una transazione. In molti sistemi la transazione inizia implicitamente al primo comando SQL dopo la connessione o dopo la chiusura della transazione precedente; lo standard SQL indica `START TRANSACTION` come comando esplicito, ma non è obbligatorio.
- **`COMMIT [WORK]`**: chiude la transazione con successo. Tutte le modifiche accumulate vengono rese permanenti nella base di dati.
- **`ROLLBACK [WORK]`**: annulla la transazione. Tutte le modifiche effettuate dall'inizio della transazione vengono disfatte, riportando il database allo stato precedente.

> [!info] Autocommit
> Molti DBMS, incluso MySQL per default, operano in modalità **autocommit**: ogni singola istruzione SQL costituisce automaticamente una transazione a sé. Per disabilitare questa modalità e gestire le transazioni manualmente si usa `SET autocommit = 0;` oppure si apre esplicitamente una transazione con `START TRANSACTION`.

> [!example] Transazione — trasferimento bancario
> Il trasferimento di 10 unità dal conto 12345 al conto 55555 richiede due operazioni che devono essere atomiche:
>
> ```sql
> START TRANSACTION;
>
> UPDATE ContoCorrente
>     SET Saldo = Saldo - 10
>     WHERE NumeroConto = 12345;
>
> UPDATE ContoCorrente
>     SET Saldo = Saldo + 10
>     WHERE NumeroConto = 55555;
>
> COMMIT WORK;
> ```
>
> Se dopo il primo `UPDATE` si verifica un guasto o un errore, il `ROLLBACK` annulla anche il prelievo già eseguito: il sistema ritorna allo stato consistente iniziale. Senza transazione, il conto 12345 risulterebbe già addebitato mentre il conto 55555 non avrebbe ricevuto nulla.

## Proprietà ACID

Le proprietà che una transazione deve garantire sono riassunte nell'acronimo **ACID**:

### Atomicità (Atomicity)

> [!quote] Definizione — Atomicità
> La sequenza di operazioni che compone una transazione viene eseguita **per intero o per niente**: non esistono esecuzioni parziali visibili al di fuori della transazione.

Se una transazione si interrompe a metà (per un guasto hardware, un errore applicativo, o un `ROLLBACK` esplicito), il DBMS disfa tutte le modifiche già apportate, come se la transazione non fosse mai iniziata.

Il caso del trasferimento bancario è l'esempio canonico: o si eseguono sia il prelievo da A che il versamento su B, oppure nessuno dei due.

### Consistenza (Consistency)

> [!quote] Definizione — Consistenza
> Al termine dell'esecuzione di una transazione, **tutti i vincoli di integrità della base di dati devono essere soddisfatti**.

Durante l'esecuzione di una transazione possono verificarsi violazioni temporanee dei vincoli (es. durante un trasferimento bancario, tra il prelievo e il versamento la somma totale dei saldi è momentaneamente alterata). Queste violazioni sono ammesse *internamente* alla transazione, ma se al momento del `COMMIT` persistono, la transazione viene annullata per intero ("abortita").

La responsabilità della consistenza è condivisa: il DBMS controlla i vincoli dichiarativi (chiavi, foreign key, CHECK), mentre l'applicazione deve garantire la correttezza della logica di business.

### Isolamento (Isolation)

> [!quote] Definizione — Isolamento
> L'effetto di transazioni concorrenti deve essere coerente, equivalente a una loro esecuzione seriale (sequenziale).

In un sistema multi-utente, più transazioni vengono eseguite in parallelo. Senza isolamento, un'operazione eseguita da una transazione potrebbe interferire con un'altra. Il DBMS deve garantire che il risultato finale sia equivalente a quello che si otterrebbe eseguendo le transazioni una alla volta.

> [!example] Isolamento — incasso di assegni
> Se due assegni emessi sullo stesso conto corrente vengono presentati all'incasso contemporaneamente, il sistema deve trattarli in modo isolato: ogni transazione deve leggere il saldo aggiornato e non "sovrascrivere" l'effetto dell'altra. Senza isolamento, entrambe potrebbero leggere il saldo originale e aggiornarlo ignorando il prelievo dell'altra, con il risultato che solo uno dei due assegni viene effettivamente scalato.

### Durabilità / Persistenza (Durability)

> [!quote] Definizione — Durabilità
> La conclusione positiva di una transazione (il `COMMIT`) corrisponde a un impegno definitivo: le modifiche vengono mantenute in modo **permanente**, anche in presenza di guasti hardware o di esecuzioni concorrenti successive.

La durabilità è garantita dal meccanismo di **log** (giornale) del DBMS: ogni modifica viene prima registrata su un log persistente, poi applicata ai dati. In caso di guasto, il sistema di recovery rilegge il log e ripristina lo stato corretto (*redo* delle transazioni committed, *undo* di quelle non completate).

### Riepilogo ACID

| Proprietà | Garanzia |
|---|---|
| **Atomicità** | Tutto o niente |
| **Consistenza** | I vincoli sono rispettati a fine transazione |
| **Isolamento** | Le transazioni concorrenti non si interferiscono |
| **Durabilità** | Gli effetti del `COMMIT` sono permanenti |
