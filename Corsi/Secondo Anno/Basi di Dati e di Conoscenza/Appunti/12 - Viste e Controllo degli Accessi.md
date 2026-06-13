## Viste

> [!quote] Definizione — Vista
> Una **vista** (o *view*) è una **tabella virtuale** ricavata da informazioni contenute in altre tabelle (o in altre viste). Non contiene dati propri: è definita da una query SQL che viene eseguita ogni volta che la vista viene interrogata.

Nella definizione di una vista possono comparire anche altre viste, a patto che non vi siano **dipendenze ricorsive** (dirette, immediate o transitive): una vista non può dipendere da se stessa.

### Sintassi: CREATE VIEW

```sql
CREATE VIEW NomeVista [(ListaAttributi)] AS SelectSQL
[WITH [LOCAL | CASCADED] CHECK OPTION]
```

Due vincoli strutturali:
- la query `SelectSQL` deve restituire un numero di colonne **pari** a quello dichiarato in `ListaAttributi`;
- l'ordine degli attributi nella target list deve **rispettare** quello dello schema della vista.

> [!example] Vista degli impiegati dell'Amministrazione
> ```sql
> CREATE VIEW ImpiegatiAmmin (Matricola, Nome, Cognome, Stipendio) AS
>     SELECT Matricola, Nome, Cognome, Stipendio
>     FROM Impiegato
>     WHERE Dipart = 'Amministrazione' AND Stipendio > 10;
> ```
> La vista `ImpiegatiAmmin` mostra solo le righe degli impiegati del dipartimento Amministrazione con stipendio superiore a 10, esposta come se fosse una tabella indipendente.

### Vantaggi e svantaggi

**Vantaggi:**
1. **Non occupano memoria**: le viste virtuali non memorizzano dati — il costo di storage è zero.
2. **Sicurezza e riservatezza**: si possono nascondere colonne o righe sensibili, mostrando solo il sottoinsieme di dati autorizzato.
3. **Convenienza**: permettono di semplificare interrogazioni complesse e di creare query altrimenti impossibili da esprimere direttamente, spesso con ottimizzazione dei tempi di risposta.

**Svantaggi:**
1. `UPDATE` e `DELETE` sulle viste diventano azioni potenzialmente pericolose per le tabelle sottostanti.
2. Possibilità di **inconsistenza** tra le tabelle di base e il database.

## Interrogazioni sulle viste

Una vista si interroga esattamente come se fosse una relazione di base: il DBMS riscrive internamente la query espandendo la definizione della vista.

> [!example] Espansione di una query su vista
> Data la vista `ImpiegatiAmmin (Nome, Cognome, Stipendio)`:
> ```sql
> SELECT * FROM ImpiegatiAmmin;
> ```
> viene eseguita internamente come:
> ```sql
> SELECT Nome, Cognome, Stipendio
> FROM Impiegato
> WHERE Dipart = 'Amministrazione' AND Stipendio > 10;
> ```

### Viste per interrogazioni altrimenti impossibili

Le viste permettono di strutturare interrogazioni che SQL non consente di esprimere direttamente in un'unica query (ad esempio, aggregazioni annidate).

> [!example] Dipartimento con la massima somma degli stipendi
> La query `SELECT avg(count(distinct Ufficio)) FROM Impiegato GROUP BY Dipart` non è sintatticamente ammessa in SQL standard. La soluzione è usare una vista intermedia:
>
> ```sql
> -- Passo 1: creare la vista con il totale stipendi per dipartimento
> CREATE VIEW BudgetStipendi (Dip, TotaleStipendi) AS
>     SELECT Dipart, SUM(Stipendio)
>     FROM Impiegato
>     GROUP BY Dipart;
>
> -- Passo 2: interrogare la vista per trovare il massimo
> SELECT Dip
> FROM BudgetStipendi
> WHERE TotaleStipendi = (
>     SELECT MAX(TotaleStipendi)
>     FROM BudgetStipendi
> );
> ```

> [!example] Numero medio di uffici per dipartimento
> La nidificazione di funzioni aggregate nella clausola `HAVING` non è ammessa in tutti i sistemi. Con una vista:
> ```sql
> CREATE VIEW DipartUffici (NomeDip, NroUffici) AS
>     SELECT Dipart, COUNT(DISTINCT Ufficio)
>     FROM Impiegato
>     GROUP BY Dipart;
>
> SELECT AVG(CAST(NroUffici AS DECIMAL(5,2))) AS NumeroMedioUffici
> FROM DipartUffici;
> ```
> Alternativa senza vista (solo dove la nidificazione in `HAVING` è supportata):
> ```sql
> SELECT Dipart
> FROM Impiegato
> GROUP BY Dipart
> HAVING SUM(Stipendio) >= ALL (
>     SELECT SUM(Stipendio)
>     FROM Impiegato
>     GROUP BY Dipart
> );
> ```

## Aggiornabilità delle viste

Su certe viste è possibile eseguire operazioni di modifica (`INSERT`, `UPDATE`, `DELETE`) che si propagano alle tabelle di base sottostanti. Esistono però forti limitazioni.

> [!info] Condizioni per l'aggiornabilità
> SQL permette la modifica di una vista solo se:
> - è definita su **una sola tabella** di base (non su un join);
> - esiste una corrispondenza biunivoca tra le righe della vista e quelle della tabella di base (una sola riga di ciascuna tabella corrisponde a una riga della vista);
> - la vista contiene almeno la **chiave primaria** della tabella di base.
>
> Viste con `GROUP BY`, `DISTINCT`, funzioni aggregate, join o sottoquery nella `SELECT` non sono aggiornabili.

### WITH CHECK OPTION

La clausola `WITH CHECK OPTION` aggiunge un **vincolo di integrità sugli aggiornamenti**: qualsiasi modifica tramite la vista viene accettata solo se la riga modificata (o inserita) continua a soddisfare il predicato `WHERE` che definisce la vista. In altri termini, la riga deve rimanere visibile attraverso la vista dopo la modifica.

> [!example] Vista con CHECK OPTION
> ```sql
> CREATE VIEW ImpiegatiAmminPoveri AS
>     SELECT *
>     FROM ImpiegatiAmmin
>     WHERE Stipendio < 50
>     WITH CHECK OPTION;
> ```
> Con questa vista, l'operazione seguente viene **rifiutata** dal DBMS:
> ```sql
> UPDATE ImpiegatiAmminPoveri
>     SET Stipendio = 60
>     WHERE Nome = 'Paola';
> ```
> portando lo stipendio a 60 la riga non soddisferebbe più `Stipendio < 50`, quindi uscirebbe dalla vista — il DBMS rifiuta la modifica.

La clausola `WITH CHECK OPTION` può essere qualificata:
- `WITH LOCAL CHECK OPTION`: il vincolo si applica solo alla definizione della vista corrente.
- `WITH CASCADED CHECK OPTION` (default): il vincolo si applica a cascata anche alle viste su cui quella corrente è definita.

## Ricorsione nelle viste

> [!warning] Dipendenze ricorsive vietate nelle viste ordinarie
> Le viste create con `CREATE VIEW` **non** possono fare riferimento a se stesse, né direttamente né transitivamente: una vista non può dipendere da se stessa. Le interrogazioni intrinsecamente ricorsive (es. la chiusura transitiva di una relazione padre-figlio) non sono quindi esprimibili con una vista standard.

## Funzioni scalari e condizionali

Le **funzioni scalari** operano a livello di singola ennupla e restituiscono un singolo valore. MySQL ne mette a disposizione diverse categorie:

| Categoria | Esempi |
|---|---|
| Temporali | `CURRENT_DATE`, `EXTRACT(YEAR FROM ...)` |
| Manipolazione stringhe | `CHAR_LENGTH`, `LOWER` |
| Conversione di tipo | `CAST` |
| Condizionali | `NULLIF`, `COALESCE`, `CASE` |

### NULLIF

> [!quote] Definizione — NULLIF
> `NULLIF(expr1, expr2)` confronta le due espressioni: restituisce `NULL` se sono uguali, altrimenti restituisce `expr1`.

```sql
SELECT NULLIF(25, 26);  -- risultato: 25
SELECT NULLIF(25, 25);  -- risultato: NULL
```

### COALESCE

> [!quote] Definizione — COALESCE
> `COALESCE(val1, val2, ..., valN)` restituisce il **primo valore non nullo** nella lista degli argomenti.

```sql
SELECT Nome, Cognome, COALESCE(Dipart, 'Ignoto')
FROM Impiegato;
```
Per ogni impiegato senza dipartimento (`Dipart = NULL`), la funzione restituisce la stringa `'Ignoto'` al posto del valore nullo.

### CASE

> [!quote] Definizione — CASE
> L'espressione `CASE` valuta una sequenza di condizioni in ordine e restituisce il valore della prima condizione verificata (semantica IF-THEN-ELSE). Se nessuna condizione è vera, viene restituito il valore della clausola `ELSE` (o `NULL` se `ELSE` è assente).

```sql
SELECT Targa,
    CASE Tipo
        WHEN 'Auto' THEN 2.58 * KWatt
        WHEN 'Moto' THEN (22.00 + 1.00 * KWatt)
        ELSE NULL
    END AS Tassa
FROM Veicolo
WHERE Anno > 1975;
```
A seconda del tipo di veicolo, la tassa viene calcolata con formule diverse; i veicoli di tipo diverso da `'Auto'` e `'Moto'` ricevono `NULL`.

## Controllo degli Accessi

Il **controllo degli accessi** è il meccanismo con cui un DBMS garantisce che ogni utente possa eseguire solo le operazioni per cui è autorizzato.

> [!quote] Definizione — Privilegio
> Un **privilegio** è il diritto di eseguire una certa azione su una certa risorsa. Ogni privilegio è caratterizzato da:
> - la **risorsa** cui si riferisce (tabella, vista, attributo, dominio);
> - l'**utente che concede** il privilegio (*grantor*);
> - l'**utente che lo riceve** (*grantee*);
> - l'**azione permessa** (tipo di privilegio);
> - la **possibilità di trasmettere** o meno il privilegio ad altri utenti.

SQL prevede la definizione di **utenti e ruoli** cui assegnare diversi privilegi. Gli utenti possono coincidere con gli utenti del sistema operativo su cui è attivo il server SQL, oppure essere indipendenti da esso. Ogni componente del sistema è proteggibile; di solito si proteggono le tabelle.

### Tipi di privilegio

| Privilegio | Applicabile a | Significato |
|---|---|---|
| `SELECT` | tabelle, viste, attributi | permette di leggere la risorsa |
| `INSERT` | tabelle, viste | inserisce un nuovo oggetto nella risorsa |
| `UPDATE` | tabelle, viste, attributi | aggiorna il valore di un oggetto |
| `DELETE` | tabelle, viste | rimuove un oggetto |
| `REFERENCES` | tabelle, attributi | permette di fare riferimento alla risorsa nella definizione di uno schema (chiave esterna) |
| `USAGE` | domini | permette di usare il dominio |
| `DROP`, `ALTER` | tutti gli oggetti | riservati al **creatore** dell'oggetto |

> [!info] Utente di sistema
> Il creatore di una risorsa ha automaticamente **tutti i privilegi** su di essa al momento della creazione. Esiste inoltre un utente speciale `_system` che dispone di tutti i privilegi su tutte le risorse in qualsiasi momento.

## GRANT e REVOKE

### Concessione di privilegi: GRANT

```sql
GRANT tipo_privilegio
ON oggetto(DB, tabella)
TO nome_utente;
```

> [!example] Concessione del privilegio SELECT
> ```sql
> GRANT SELECT ON Dipartimento TO Stefano;
> ```
> Concede all'utente `Stefano` il privilegio di lettura (`SELECT`) sulla tabella `Dipartimento`.

Varianti importanti:
- `WITH GRANT OPTION`: l'utente destinatario può a sua volta **propagare** il privilegio ricevuto ad altri utenti.
- `ALL PRIVILEGES`: concede **tutti i possibili privilegi** sull'oggetto indicato.

```sql
-- Concede tutti i privilegi con possibilità di propagazione
GRANT ALL PRIVILEGES ON Impiegato TO Mario WITH GRANT OPTION;

-- Concede solo la lettura su colonne specifiche
GRANT SELECT (Nome, Cognome, Stipendio) ON Impiegato TO Lucia;
```

### Revoca di privilegi: REVOKE

```sql
REVOKE tipo_privilegio
ON oggetto
FROM nome_utente;
```

> [!example] Revoca del privilegio INSERT
> ```sql
> REVOKE INSERT ON Impiegato FROM Lucia;
> ```
> Rimuove all'utente `Lucia` il privilegio di inserimento sulla tabella `Impiegato`.

> [!warning] Effetti della revoca con GRANT OPTION
> Se un utente aveva ricevuto un privilegio `WITH GRANT OPTION` e lo aveva propagato ad altri, la revoca del privilegio all'utente originale può causare la revoca a cascata anche sui destinatari secondari, a seconda delle opzioni del DBMS (`REVOKE ... CASCADE` vs `REVOKE ... RESTRICT`).

## Ruoli

> [!quote] Definizione — Ruolo
> Un **ruolo** è un insieme denominato di privilegi che può essere assegnato a uno o più utenti (o a interi gruppi). Semplifica la gestione delle autorizzazioni: invece di assegnare singolarmente i privilegi a ciascun utente, si assegnano a un ruolo e il ruolo agli utenti.

```sql
-- Creazione di un ruolo
CREATE ROLE responsabile_hr;

-- Assegnazione di privilegi al ruolo
GRANT SELECT, INSERT, UPDATE ON Impiegato TO responsabile_hr;

-- Assegnazione del ruolo a un utente
GRANT responsabile_hr TO Mario;

-- Eliminazione di un ruolo
DROP ROLE responsabile_hr;
```

Con molti ruoli il responsabile può gestire facilmente i privilegi di accesso: modificare i permessi del ruolo si riflette automaticamente su tutti gli utenti che lo possiedono.

## Viste e Controllo degli Accessi

Le viste sono uno strumento fondamentale per la **sicurezza e la riservatezza** dei dati. Anziché concedere l'accesso diretto alle tabelle di base (con tutti i loro attributi e righe), si può:

1. creare una vista che espone solo le colonne e le righe autorizzate;
2. concedere i privilegi sulla vista invece che sulla tabella.

> [!example] Accesso limitato tramite vista
> ```sql
> -- Vista che mostra solo i dati pubblici degli impiegati
> CREATE VIEW ImpiegatiPubblici (Matricola, Nome, Cognome, Dipart) AS
>     SELECT Matricola, Nome, Cognome, Dipart
>     FROM Impiegato;
>
> -- Si concede SELECT sulla vista, non sulla tabella
> GRANT SELECT ON ImpiegatiPubblici TO Lucia;
> ```
> `Lucia` può leggere nome, cognome e dipartimento, ma non lo stipendio né altri attributi sensibili.

> [!warning] Attenzione ai privilegi a grana fine
> Troppi privilegi, o troppi privilegi definiti a livello di singola colonna, possono creare **problemi di performance**. La soluzione preferibile è costruire viste con le sole colonne accessibili e concedere i privilegi sulla vista, invece di gestire permessi colonna per colonna sulle tabelle di base.

In sintesi, le viste realizzano il livello esterno dell'architettura ANSI/SPARC: ogni utente (o gruppo) vede la base di dati attraverso uno *schema esterno* personalizzato, ottenuto proprio tramite le viste definite per lui. Questo garantisce l'**indipendenza logica dei dati**: le applicazioni sono isolate dalla struttura fisica e logica delle tabelle di base, e un cambiamento allo schema interno può essere mascherato ridefinendo le viste senza modificare le applicazioni.
