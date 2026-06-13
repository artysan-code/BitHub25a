## SQL — Interrogazioni

Le interrogazioni in SQL sono formulate in modo **dichiarativo**: si specifica *cosa* si vuole ottenere, non *come* ottenerlo. L'interrogazione viene passata all'**ottimizzatore di interrogazioni** (*query optimizer*), componente del DBMS che la analizza e la traduce nel linguaggio di interrogazione interno più efficiente.

### Schema di riferimento usato negli esempi

Tutti gli esempi di questa nota si basano sullo schema seguente, ripreso dalle slide della Prof.ssa Vocca:

**Persone**

| Nome | Età | Reddito |
| ------- | --- | ------- |
| Andrea | 27 | 21 |
| Aldo | 25 | 15 |
| Maria | 55 | 42 |
| Anna | 50 | 35 |
| Filippo | 26 | 30 |
| Luigi | 50 | 40 |
| Franco | 60 | 20 |
| Olga | 30 | 41 |
| Sergio | 85 | 35 |
| Luisa | 75 | 87 |

**Maternità**

| Madre | Figlio |
| ----- | ------- |
| Luisa | Maria |
| Luisa | Luigi |
| Anna | Olga |
| Anna | Filippo |
| Maria | Andrea |
| Maria | Aldo |

**Paternità**

| Padre | Figlio |
| ------ | ------- |
| Sergio | Franco |
| Luigi | Olga |
| Luigi | Filippo |
| Franco | Andrea |
| Franco | Aldo |

Viene usato anche lo schema:

```
IMPIEGATO(Nome, Cognome, Dipart, Ufficio, Stipendio, Città)
DIPARTIMENTO(Nome, Indirizzo, Città)
```

## Struttura base: SELECT-FROM-WHERE

L'istruzione fondamentale per le interrogazioni è `SELECT`:

```sql
SELECT ListaAttributi        -- target list
FROM   ListaTabelle          -- clausola FROM
[WHERE Condizione]           -- clausola WHERE (opzionale)
```

In forma estesa, con alias:

```sql
SELECT AttrEspr [[AS] Alias] {, AttrEspr [[AS] Alias]}
FROM   Tabella [[AS] Alias]  {, Tabella [[AS] Alias]}
[WHERE Condizione]
```

### Semantica operazionale

Una `SELECT` su più tabelle esegue concettualmente tre passi dell'algebra relazionale nell'ordine:

1. **Prodotto cartesiano** ($\times$) di tutte le tabelle elencate nella `FROM`
2. **Selezione** ($\sigma$) delle righe che soddisfano la condizione `WHERE`
3. **Proiezione** ($\Pi$) sugli attributi della target list

Per le relazioni $R_1(A_1,A_2)$ e $R_2(A_3,A_4)$:

```sql
SELECT DISTINCT R1.A1, R2.A4
FROM   R1, R2
WHERE  R1.A2 = R2.A3
```

corrisponde all'espressione algebrica $\Pi_{A_1,A_4}(\sigma_{A_2=A_3}(R_1 \times R_2))$.

> [!info] SQL vs algebra relazionale
> L'algebra relazionale non ammette duplicati; SQL li ammette per default. Una `SELECT` senza `DISTINCT` può restituire righe ripetute.

## Selezione e proiezione

### Solo proiezione (nessun filtro)

*Nome e reddito di tutte le persone* — corrisponde a $\Pi_{\text{Nome,Reddito}}(\text{Persone})$:

```sql
SELECT Nome, Reddito
FROM   Persone;
```

### Solo selezione (tutti gli attributi)

*Tutte le informazioni sulle persone con meno di 30 anni* — corrisponde a $\sigma_{\text{Età}<30}(\text{Persone})$:

```sql
SELECT *
FROM   Persone
WHERE  Eta < 30;
```

`SELECT *` è abbreviazione per "tutti gli attributi della tabella".

### Selezione e proiezione combinate

*Nome e reddito delle persone con meno di 30 anni* — corrisponde a $\Pi_{\text{Nome,Reddito}}(\sigma_{\text{Età}<30}(\text{Persone}))$:

```sql
SELECT Nome, Reddito
FROM   Persone
WHERE  Eta < 30;
```

Risultato:

| Nome | Reddito |
| ------- | ------- |
| Andrea | 21 |
| Aldo | 15 |
| Filippo | 30 |

## DISTINCT

Poiché SQL ammette duplicati, `SELECT Città FROM Persona` può restituire la stessa città più volte. Per eliminare i duplicati si usa `DISTINCT`:

```sql
SELECT DISTINCT Città
FROM   Persona;
```

> [!warning] DISTINCT e proiezioni
> `DISTINCT` elimina i duplicati anche nelle proiezioni, non solo nei risultati di unione. Va usato con consapevolezza: aggiunge un costo computazionale e non è sempre necessario (se la colonna proiettata è già una chiave, i duplicati non esistono).

## Alias di colonna e di tabella

### Alias di colonna

Un alias rinomina una colonna nel risultato. La parola chiave `AS` è opzionale:

```sql
SELECT emp_id codice
FROM   emp;

SELECT Stipendio / 12 AS SalarioMensile
FROM   Impiegato
WHERE  Cognome = 'Rossi';
```

Il risultato ha una sola colonna denominata `SalarioMensile`.

### Alias di tabella

Un alias di tabella (detto anche *variabile di range*) abbrevia il riferimento alla tabella e diventa indispensabile nel self join:

```sql
SELECT p.Nome AS Nome, p.Reddito AS Reddito
FROM   Persone p
WHERE  p.Eta < 30;
```

> [!info] SELECT * e alias
> `SELECT * FROM R` equivale a `SELECT X.A AS A, X.B AS B FROM R X WHERE TRUE`. L'alias di tabella `X` è introdotto implicitamente.

## Espressioni nella target list

La target list può contenere espressioni aritmetiche su attributi e costanti:

```sql
SELECT Reddito / 2 AS RedditoSemestrale
FROM   Persone
WHERE  Nome = 'Luigi';
```

Risultato: una riga con `RedditoSemestrale = 20`.

## Clausola WHERE

La clausola `WHERE` filtra le righe prodotte dal prodotto cartesiano. Accetta i seguenti operatori.

### Operatori di confronto

| Operatore | Significato |
| --------- | ----------- |
| `=` | uguaglianza |
| `<>` o `!=` | diverso |
| `<` | minore |
| `>` | maggiore |
| `<=` | minore o uguale |
| `>=` | maggiore o uguale |

### Connettivi logici

`AND`, `OR`, `NOT` combinano predicati atomici.

### BETWEEN

Verifica l'appartenenza a un intervallo chiuso $[a, b]$:

```sql
SELECT ename, job, sal
FROM   emp
WHERE  sal BETWEEN 1200 AND 5000;
```

Equivale a `sal >= 1200 AND sal <= 5000`.

### IN

Verifica l'appartenenza a un insieme esplicitamente elencato:

```sql
SELECT *
FROM   emp
WHERE  job IN ('CLERK', 'MANAGER', 'ANALYST');
```

### LIKE

Confronto lessicale con pattern su stringhe. I caratteri speciali sono:
- `%` — sequenza arbitraria di caratteri (anche vuota)
- `_` — esattamente un carattere arbitrario

```sql
SELECT *
FROM   Impiegato
WHERE  Cognome LIKE '_o%i';
-- corrisponde a: Rossi, Rosi, Porti, ...
```

```sql
SELECT autore, qualific
FROM   au
WHERE  autore LIKE 'A%';
-- tutti gli autori il cui nome inizia per A
```

### IS NULL / IS NOT NULL

I confronti con `NULL` tramite `=` o `<>` restituiscono sempre `UNKNOWN` (logica a tre valori). L'unico modo corretto per testare la presenza o l'assenza di un valore nullo è:

```sql
SELECT *
FROM   Impiegati
WHERE  Eta IS NULL;

SELECT *
FROM   Impiegati
WHERE  Eta IS NOT NULL;
```

## Logica a tre valori e NULL

SQL adotta una **logica a tre valori**: `TRUE`, `FALSE`, `UNKNOWN`. Ogni confronto che coinvolge `NULL` produce `UNKNOWN`. La clausola `WHERE` seleziona solo le righe per cui la condizione vale `TRUE`.

> [!example] Gestione dei NULL — impiegati con età sconosciuta
> Tabella Impiegati:
>
> | Matricola | Cognome | Filiale | Età |
> | --------- | ------- | ------- | ---- |
> | 5555 | Rossi | Roma | 45 |
> | 6666 | Neri | Roma | NULL |
>
> Per selezionare gli impiegati la cui età *è o potrebbe essere* maggiore di 40 (cioè quelli con età > 40 più quelli con età sconosciuta):
>
> Algebra: $\sigma_{(\text{Età}>40) \lor (\text{Età IS NULL})}(\text{Impiegati})$
>
> ```sql
> SELECT *
> FROM   Impiegati
> WHERE  Eta > 40 OR Eta IS NULL;
> ```
>
> Risultato: entrambe le righe.

> [!warning] Attenzione con NOT e NULL
> `NOT (Eta > 40)` non include le righe con `Eta IS NULL`, perché `NOT UNKNOWN = UNKNOWN`. Se si vogliono includere i NULL occorre scrivere esplicitamente `WHERE Eta <= 40 OR Eta IS NULL`.

## Ordinamento del risultato: ORDER BY

SQL non garantisce alcun ordine sul risultato senza `ORDER BY`. Per ordinare si usa:

```sql
SELECT Nome, Reddito
FROM   Persone
WHERE  Eta < 30
ORDER BY Nome ASC;
```

- `ASC` (default) — ordine crescente
- `DESC` — ordine decrescente

Risultato ordinato:

| Nome | Reddito |
| ------- | ------- |
| Aldo | 15 |
| Andrea | 21 |
| Filippo | 30 |

Si possono indicare più attributi di ordinamento; il secondo criterio viene applicato a parità del primo.

## Join in SQL

### Join tramite prodotto cartesiano e WHERE (stile implicito)

Elencando più tabelle nella `FROM` si forma il prodotto cartesiano; la condizione di join va espressa nel `WHERE`:

```sql
SELECT Impiegato.Nome, Impiegato.Cognome, Dipartimento.Città
FROM   Impiegato, Dipartimento
WHERE  Impiegato.Dipart = Dipartimento.Nome;
```

> [!example] I padri di persone che guadagnano più di 20
> Algebra: $\Pi_{\text{Padre}}(\text{Paternita} \bowtie_{\text{Figlio=Nome}} \sigma_{\text{Reddito}>20}(\text{Persone}))$
>
> ```sql
> SELECT DISTINCT Padre
> FROM   Persone, Paternita
> WHERE  Figlio = Nome AND Reddito > 20;
> ```

### JOIN esplicito: INNER JOIN ... ON

La sintassi esplicita è preferibile per la leggibilità:

```sql
SELECT AttrEspr [[AS] Alias] {, ...}
FROM   Tabella [[AS] Alias]
       [{TipoJoin} JOIN Tabella [[AS] Alias] ON CondizioneJoin]
[WHERE AltraCondizione]
```

`TipoJoin` può essere: `INNER` (default), `LEFT [OUTER]`, `RIGHT [OUTER]`, `FULL [OUTER]`.

> [!example] Padre e madre di ogni persona — join esplicito
> ```sql
> SELECT maternita.figlio, padre, madre
> FROM   maternita JOIN paternita
>        ON paternita.figlio = maternita.figlio;
> ```
>
> Equivale alla forma implicita:
>
> ```sql
> SELECT paternita.figlio, padre, madre
> FROM   maternita, paternita
> WHERE  paternita.figlio = maternita.figlio;
> ```

### Join su più tabelle

Le persone che guadagnano più dei rispettivi padri (con nome, reddito del figlio e reddito del padre):

```sql
SELECT f.Nome, f.Reddito, p.Reddito
FROM   (Persone p JOIN Paternita ON p.Nome = Padre)
       JOIN Persone f ON Figlio = f.Nome
WHERE  f.Reddito > p.Reddito;
```

Forma equivalente con stile implicito:

```sql
SELECT f.Nome, f.Reddito, p.Reddito
FROM   Persone p, Paternita, Persone f
WHERE  p.Nome = Padre
  AND  Figlio = f.Nome
  AND  f.Reddito > p.Reddito;
```

### Self join

Il self join si realizza usando due alias diversi per la stessa tabella:

```sql
SELECT I1.Nome
FROM   Impiegato I1, Impiegato I2
WHERE  I1.Nome = I2.Nome
  AND  I1.Dipart = 'Produzione'
  AND  I2.Dipart <> 'Produzione';
```

Restituisce i dipendenti non del dipartimento Produzione che si chiamano come qualche dipendente della Produzione.

### Join esterno (OUTER JOIN)

Il join interno (`INNER JOIN`) esclude le righe senza corrispondenza. Il join esterno le conserva, riempiendo con `NULL` le colonne mancanti.

> [!quote] Definizione — Join esterno
> Il **join esterno** estende il join interno includendo, nel risultato, anche le ennuple che non trovano corrispondenza nell'altra relazione, con `NULL` al posto dei valori mancanti.

**LEFT OUTER JOIN** — conserva tutte le righe della tabella di sinistra:

```sql
SELECT Paternita.Figlio, Padre, Madre
FROM   Paternita LEFT OUTER JOIN Maternita
       ON Paternita.Figlio = Maternita.Figlio;
```

Risultato: tutti i figli che hanno un padre noto; `Madre = NULL` dove la corrispondenza in Maternita non esiste.

La parola `OUTER` è opzionale: `LEFT JOIN` e `LEFT OUTER JOIN` sono equivalenti.

**FULL OUTER JOIN** — conserva tutte le righe di entrambe le tabelle:

```sql
SELECT Paternita.Figlio, Padre, Madre
FROM   Maternita FULL OUTER JOIN Paternita
       ON Maternita.Figlio = Paternita.Figlio;
```

> [!info] FULL OUTER JOIN in MySQL
> MySQL non supporta `FULL OUTER JOIN` in modo nativo. Si emula con `LEFT JOIN UNION RIGHT JOIN`.

## Operatori insiemistici

### UNION

Restituisce l'unione di due risultati compatibili, eliminando i duplicati per default:

```sql
SELECT *
FROM   A
UNION
SELECT *
FROM   B;
```

Con `UNION ALL` i duplicati vengono conservati. I duplicati vengono eliminati anche rispetto alle proiezioni, non solo tra le due query.

### INTERSECT

Restituisce le righe presenti in entrambi i risultati:

```sql
SELECT Nome
FROM   Impiegato
INTERSECT
SELECT Cognome AS Nome
FROM   Impiegato;
```

Equivale al self join:

```sql
SELECT I.Nome
FROM   Impiegato I, Impiegato J
WHERE  I.Nome = J.Cognome;
```

> [!info] INTERSECT in MySQL
> MySQL non supporta `INTERSECT` nativamente (prima di MySQL 8.0.31). Si emula con `INNER JOIN` o con subquery correlata usando `IN`.

### EXCEPT (differenza)

Restituisce le righe del primo risultato non presenti nel secondo:

```sql
SELECT *
FROM   A
EXCEPT
SELECT *
FROM   B;
```

> [!example] Differenza con EXCEPT
> ```sql
> SELECT Nome
> FROM   Impiegato
> EXCEPT
> SELECT Cognome AS Nome
> FROM   Impiegato;
> ```
> Restituisce i nomi che non compaiono tra i cognomi.

Le due tabelle devono avere gli stessi nomi di attributo e domini compatibili.

La differenza si può esprimere anche con una subquery correlata:

```sql
SELECT *
FROM   A
WHERE  NOT EXISTS (
    SELECT *
    FROM   B
    WHERE  A.column_name = B.column_name  -- column_name è chiave
);
```

> [!info] EXCEPT in MySQL
> MySQL non supporta `EXCEPT` (prima di MySQL 8.0.31). Si emula con `NOT IN` o `NOT EXISTS`.
>
> Alcuni DBMS (Oracle) usano il termine `MINUS` al posto di `EXCEPT`.

## Funzioni di aggregazione

In algebra relazionale ogni espressione è valutata su singole tuple. SQL offre invece **funzioni di aggregazione** che operano su insiemi di tuple:

| Funzione | Significato |
| -------- | ----------- |
| `COUNT(*)` | numero di righe |
| `COUNT([DISTINCT] A)` | numero di valori (distinti) non nulli di $A$ |
| `SUM([DISTINCT] A)` | somma dei valori di $A$ |
| `AVG([DISTINCT] A)` | media dei valori di $A$ |
| `MAX(A)` | valore massimo di $A$ |
| `MIN(A)` | valore minimo di $A$ |

Sintassi:

```sql
COUNT ( * | [DISTINCT | ALL] ListaAttributi )
<SUM | MAX | MIN | AVG> ( [DISTINCT | ALL] AttrEspr )
```

> [!warning] NULL e funzioni di aggregazione
> Tutte le funzioni di aggregazione **ignorano i NULL**, eccetto `COUNT(*)` che conta le righe indipendentemente dal loro contenuto. Questo significa che `AVG(A)` divide per il numero di valori non nulli, non per il numero totale di righe.

> [!example] Esempi di aggregazione
> Numero di impiegati che si chiamano Rossi:
> ```sql
> SELECT COUNT(*)
> FROM   Impiegato
> WHERE  nome = 'Rossi';
> ```
>
> Massimo, minimo e differenza dei salari:
> ```sql
> SELECT MAX(sal), MIN(sal), MAX(sal) - MIN(sal)
> FROM   Impiegato;
> ```

## GROUP BY

Gli operatori di aggregazione vengono applicati a *tutte* le righe del risultato. Quando si vogliono calcolare aggregati per sottoinsiemi di righe, si usa `GROUP BY`.

> [!quote] Definizione — GROUP BY
> `GROUP BY` suddivide le righe della tabella in gruppi secondo i valori degli attributi indicati, e applica le funzioni di aggregazione separatamente a ciascun gruppo.

```sql
SELECT Dipart, MAX(Stipendio)
FROM   Impiegato
GROUP BY Dipart;
```

> [!warning] Regola della target list con GROUP BY
> Nella `SELECT` di una query con `GROUP BY`, possono comparire **solo**:
> - gli attributi elencati nel `GROUP BY`
> - funzioni di aggregazione
>
> Includere un attributo non raggruppato nella target list è un errore logico (MySQL in modalità non-strict lo permette con risultati imprevedibili).

> [!example] Numero di figli per ciascun padre
> ```sql
> SELECT padre, COUNT(*) AS NumFigli
> FROM   paternita
> GROUP BY padre;
> ```
>
> Paternita:
>
> | Padre | Figlio |
> | ------ | ------- |
> | Sergio | Franco |
> | Luigi | Olga |
> | Luigi | Filippo |
> | Franco | Andrea |
> | Franco | Aldo |
>
> Risultato:
>
> | Padre | NumFigli |
> | ------ | -------- |
> | Sergio | 1 |
> | Luigi | 2 |
> | Franco | 2 |

### GROUP BY e NULL

I valori `NULL` formano un gruppo a sé nel `GROUP BY`. La funzione `COUNT(*)` conta anche le righe con `NULL` nell'attributo di raggruppamento; `COUNT(A)` conta solo i valori non nulli di $A$.

> [!example] GROUP BY con NULL
> Relazione R(A, B): righe (1,11), (2,11), (3,NULL), (4,NULL).
>
> ```sql
> SELECT B, COUNT(*)
> FROM   R
> GROUP BY B;
> ```
> Risultato: (11, 2), (NULL, 2) — i NULL formano un gruppo.
>
> ```sql
> SELECT A, COUNT(B)
> FROM   R
> GROUP BY A;
> ```
> Risultato: (1,1), (2,1), (3,0), (4,0) — `COUNT(B)` ignora i NULL.

## HAVING

`HAVING` filtra i gruppi prodotti da `GROUP BY` sulla base di condizioni che coinvolgono funzioni di aggregazione. Non può essere usato senza `GROUP BY` in modo significativo.

> [!quote] Definizione — HAVING
> La clausola `HAVING` specifica una condizione sui *gruppi*; solo i gruppi per cui la condizione è `TRUE` compaiono nel risultato.

```sql
SELECT Dipart, SUM(Stipendio) AS SommaStipendi
FROM   Impiegati
GROUP BY Dipart
HAVING SUM(Stipendio) > 100;
```

### WHERE vs HAVING

| | WHERE | HAVING |
| -- | ----- | ------ |
| Filtra | singole righe | gruppi |
| Momento di applicazione | prima del raggruppamento | dopo il raggruppamento |
| Può usare funzioni aggregate | no | sì |

> [!example] WHERE e HAVING nella stessa query
> I padri i cui figli *sotto i 30 anni* hanno un reddito medio maggiore di 25:
>
> ```sql
> SELECT padre, AVG(f.reddito)
> FROM   persone f JOIN paternita ON figlio = nome
> WHERE  eta < 30
> GROUP BY padre
> HAVING AVG(f.reddito) > 25;
> ```
>
> Il `WHERE` filtra le righe *prima* del raggruppamento (solo persone con meno di 30 anni); `HAVING` filtra i *gruppi* (solo i padri con media > 25).

> [!example] I padri i cui figli hanno reddito medio > 25 (senza vincolo di età)
> ```sql
> SELECT padre, AVG(f.reddito) AS StipendioMedio
> FROM   persone f JOIN paternita ON figlio = f.nome
> GROUP BY padre
> HAVING AVG(f.reddito) > 25;
> ```
>
> Risultato (dai dati di esempio):
>
> | Padre | StipendioMedio |
> | ----- | -------------- |
> | Luigi | 30,5 |
>
> I figli di Luigi sono Olga (41) e Filippo (30): media = 35,5 > 25. I figli di Franco sono Andrea (21) e Aldo (15): media = 18 $\leq$ 25. Sergio ha solo Franco (20): media = 20 $\leq$ 25.

## Forma completa della SELECT

Dopo tutte le estensioni viste, la forma completa di una `SELECT` è:

```sql
SELECT   ListaAttributiOEspressioni
FROM     ListaTabelle
[WHERE   CondizioniSemplici]
[GROUP BY ListaAttributiDiRaggruppamento]
[HAVING  CondizioniAggregate]
[ORDER BY ListaAttributiDiOrdinamento]
```

### Ordine logico di valutazione

1. **FROM** — calcola il prodotto cartesiano delle tabelle (o esegue i join)
2. **WHERE** — filtra le righe
3. **GROUP BY** — raggruppa le righe
4. **HAVING** — filtra i gruppi
5. **SELECT** — calcola le espressioni della target list
6. **ORDER BY** — ordina il risultato

> [!warning] Ordine sintattico vs ordine di valutazione
> L'ordine in cui si *scrivono* le clausole è `SELECT ... FROM ... WHERE ... GROUP BY ... HAVING ... ORDER BY`, ma l'ordine in cui vengono *valutate* logicamente è quello elencato sopra. Questo spiega perché non si può usare un alias definito nella `SELECT` dentro la `WHERE` dello stesso blocco.

## Interrogazioni nidificate (subquery)

Una **subquery** è una `SELECT` interna collocata nella clausola `WHERE` di un'interrogazione esterna. Il risultato della subquery è un attributo o una lista di attributi, e viene confrontato con valori della query esterna.

### Subquery semplice (non correlata)

La subquery viene eseguita *una sola volta*, indipendentemente dall'interrogazione esterna.

> [!example] Nome e reddito del padre di Franco
> Con join:
> ```sql
> SELECT Nome, Reddito
> FROM   Persone, Paternita
> WHERE  Nome = Padre AND Figlio = 'Franco';
> ```
>
> Con subquery:
> ```sql
> SELECT Nome, Reddito
> FROM   Persone
> WHERE  Nome = (SELECT Padre
>                FROM   Paternita
>                WHERE  Figlio = 'Franco');
> ```

> [!example] Persone più anziane di tutte le persone che risiedono a Roma
> ```sql
> SELECT *
> FROM   Persone
> WHERE  Età > (SELECT MAX(Età)
>               FROM   Persone
>               WHERE  Residenza = 'Roma');
> ```

> [!example] Dipendenti nello stesso dipartimento di Allen
> ```sql
> SELECT ename
> FROM   emp
> WHERE  deptno = (SELECT deptno
>                  FROM   emp
>                  WHERE  ename = 'Allen');
> ```
>
> Equivale al self join:
> ```sql
> SELECT x.ename
> FROM   emp x, emp y
> WHERE  x.deptno = y.deptno AND y.ename = 'Allen';
> ```

### Operatore IN / NOT IN

Quando la subquery restituisce più righe si usa `IN`:

```sql
SELECT Nome, Reddito
FROM   Persone
WHERE  Nome IN (SELECT Padre
                FROM   Paternita, Persone
                WHERE  Figlio = Nome AND Reddito > 20);
```

`=ANY` e `IN` sono equivalenti; `<>ALL` e `NOT IN` sono equivalenti:

```sql
SELECT Nome
FROM   Dipartimento
WHERE  Nome NOT IN (SELECT Dipart
                    FROM   Impiegato
                    WHERE  Cognome = 'Rossi');
```

Corrisponde alla differenza insiemistica $\Pi_{\text{Nome}}(\text{Dipartimento}) - \Pi_{\text{Dipart}}(\sigma_{\text{Cognome=Rossi}}(\text{Impiegato}))$.

> [!warning] NOT IN e NULL
> Se il risultato della subquery contiene anche un solo `NULL`, `NOT IN` restituisce sempre `FALSE` (o `UNKNOWN`) per tutte le righe. In presenza di possibili `NULL` nella subquery, preferire `NOT EXISTS`.

### Operatori ANY / SOME e ALL

`ANY` (sinonimo `SOME`): il confronto è vero se è vero per *almeno una* riga del risultato.

`ALL`: il confronto è vero se è vero per *tutte* le righe del risultato.

> [!example] Impiegati in un dipartimento con sede a Firenze
> ```sql
> SELECT *
> FROM   Impiegato
> WHERE  Dipart = ANY (SELECT Nome
>                      FROM   Dipartimento
>                      WHERE  Citta = 'Firenze');
> ```

> [!example] Dipartimento dello stipendio massimo (con ALL)
> ```sql
> SELECT Stipendio
> FROM   Impiegato
> WHERE  Stipendio >= ALL (SELECT Stipendio
>                          FROM   Impiegato);
> ```
>
> Equivale a:
> ```sql
> SELECT Dipart
> FROM   Impiegato
> WHERE  Stipendio = (SELECT MAX(Stipendio)
>                     FROM   Impiegato);
> ```

> [!example] Impiegati non della Produzione con stesso nome di un impiegato della Produzione
> Con self join:
> ```sql
> SELECT I1.Nome
> FROM   Impiegato I1, Impiegato I2
> WHERE  I1.Nome = I2.Nome
>   AND  I2.Dipart = 'Produzione'
>   AND  I1.Dipart <> 'Produzione';
> ```
>
> Con subquery e `ANY`:
> ```sql
> SELECT Nome
> FROM   Impiegato
> WHERE  Dipart <> 'Produzione'
>   AND  Nome = ANY (SELECT Nome
>                    FROM   Impiegato
>                    WHERE  Dipart = 'Produzione');
> ```

### Subquery con più attributi

Quando si vuole confrontare una tupla con una lista di attributi, si racchiude la lista tra parentesi:

```sql
SELECT *
FROM   Persona P
WHERE  (Nome, Cognome) NOT IN (SELECT Nome, Cognome
                                FROM   Persona Q
                                WHERE  P.CodFiscale <> Q.CodFiscale);
```

## Interrogazioni nidificate correlate

Una subquery **correlata** contiene un riferimento (*passaggio di binding*) a una variabile definita nell'interrogazione esterna. Per questo motivo *non* può essere eseguita prima e indipendentemente dalla query esterna: viene rieseguita *una volta per ogni riga* dell'interrogazione esterna.

> [!quote] Definizione — Subquery correlata
> Una **subquery correlata** è un'interrogazione nidificata che fa riferimento tramite un alias a tabelle della query che la contiene. L'interrogazione interna viene eseguita una volta per ciascuna ennupla dell'interrogazione esterna.

### EXISTS / NOT EXISTS

`EXISTS` restituisce `TRUE` se la subquery produce almeno una riga, `FALSE` se non ne produce nessuna. È sempre usato con subquery correlate.

> [!example] Le persone che hanno almeno un figlio
> ```sql
> SELECT *
> FROM   Persone
> WHERE  EXISTS (SELECT Padre
>                FROM   Paternita
>                WHERE  Padre = Nome)
>     OR EXISTS (SELECT Madre
>                FROM   Maternita
>                WHERE  Madre = Nome);
> ```
> `Nome` nella subquery fa riferimento alla colonna `Nome` di `Persone` dell'interrogazione esterna: questo è il passaggio di binding.

> [!example] Le persone che hanno almeno un omonimo (stesso nome e cognome, codice fiscale diverso)
> ```sql
> SELECT *
> FROM   Persona P
> WHERE  EXISTS (SELECT *
>                FROM   Persona P1
>                WHERE  P1.Nome = P.Nome
>                  AND  P1.Cognome = P.Cognome
>                  AND  P1.CodFiscale <> P.CodFiscale);
> ```
> La subquery è indeterminata senza risolvere il riferimento a `P`: va eseguita per ogni riga di `Persona P`.

> [!example] I padri i cui figli guadagnano *tutti* più di 20 (con NOT EXISTS)
> La formula "tutti i figli guadagnano più di 20" equivale a "non esiste un figlio che guadagna $\leq$ 20":
>
> ```sql
> SELECT DISTINCT Padre
> FROM   Paternita Z
> WHERE  NOT EXISTS (SELECT *
>                    FROM   Paternita W, Persone
>                    WHERE  W.Padre = Z.Padre
>                      AND  W.Figlio = Nome
>                      AND  Reddito <= 20);
> ```
>
> La versione seguente è **scorretta** perché `Figlio` nella subquery non è collegato all'alias `Z` della query esterna (viola le regole di visibilità):
>
> ```sql
> -- ERRATA
> SELECT DISTINCT Padre
> FROM   Paternita
> WHERE  NOT EXISTS (SELECT *
>                    FROM   Persone
>                    WHERE  Figlio = Nome
>                      AND  Reddito <= 20);
> ```

### Regole di visibilità nelle subquery

- Un blocco può fare riferimento a variabili definite in blocchi *più esterni* (questo produce correlazione).
- Non è possibile fare riferimento a variabili definite in blocchi più *interni*.
- Se lo stesso nome appare a più livelli, si assume riferimento alla variabile più *vicina* (scope lessicale).
- Le sottointerrogazioni non possono contenere operatori insiemistici (`UNION`, `INTERSECT`, `EXCEPT`): le unioni si fanno solo al livello più esterno.

> [!example] Regola di visibilità violata — query scorretta
> ```sql
> -- SCORRETTA: D1 non è visibile dentro la seconda subquery
> SELECT *
> FROM   Impiegato
> WHERE  Dipart IN (SELECT Nome
>                   FROM   Dipartimento D1
>                   WHERE  Nome = 'Produzione')
>     OR Dipart IN (SELECT Nome
>                   FROM   Dipartimento D2
>                   WHERE  D2.Citta = D1.Citta);  -- D1 non visibile qui
> ```

### Commenti sulla forma nidificata

La prima versione di SQL prevedeva solo la forma nidificata (struttura a blocchi, una sola relazione per clausola `FROM`). Questa forma:
- ha dichiaratività limitata
- non permette di includere nella target list attributi di relazioni nei blocchi interni
- è meno generale della forma piana con join multipli

La forma piana e quella nidificata possono essere combinate. Non tutte le interrogazioni nidificate corrispondono a un join (in particolare quelle con `ALL` o `NOT EXISTS`).
