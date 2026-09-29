## Esercitazione: dallo schema relazionale a SQL

Questa esercitazione (Università "Tor Vergata") ripercorre in senso inverso e pratico i temi della progettazione: dato uno schema relazionale, risalire allo schema concettuale ([[07 - Progettazione Logica]]); scrivere interrogazioni SQL non banali su uno schema didattico ([[11 - SQL Interrogazioni]]); calcolare la cardinalità di espressioni di join sfruttando vincoli di integrità referenziale e chiavi ([[08 - Algebra Relazionale]], [[04 - Vincoli di integrità]]).

## Quesito 1 — Da schema relazionale a schema Entità-Relazione

> [!example] Schema relazionale dato
> `Dipendente(<u>ID</u>, Cognome, Nome, Dipartimento*)` — FK `Dipartimento` → `Dipartimento`
>
> `Professore(<u>ID</u>, Qualifica, Età)` — FK `ID` → `Dipendente`
>
> `Dipartimento(<u>Codice</u>, Nome, Indirizzo, Direttore)` — FK `Direttore` → `Professore`
>
> `CorsoDiStudio(<u>Codice</u>, Nome, Dipartimento)` — FK `Dipartimento` → `Dipartimento`
>
> `Collaborazione(<u>CorsoDiStudio</u>, <u>Professore</u>, Tipo)` — FK `CorsoDiStudio` → `CorsoDiStudio`, FK `Professore` → `Professore`
>
> `Corso(<u>Codice</u>, Materia, Docente, Semestre)` — FK `Materia` → `Materia`, FK `Docente` → `Professore`
>
> (`*` indica ammissibilità di valori nulli)

### Metodo

Ricostruire lo schema concettuale a partire da quello logico significa applicare **a ritroso** le regole di traduzione viste in [[07 - Progettazione Logica]]:

- una relazione la cui **chiave primaria è anche chiave esterna** verso un'altra relazione rivela una **generalizzazione** (ISA), tradotta con la "strategia 3" (sostituzione con associazione 1:1);
- una FK **non nulla** contenuta in una relazione, non facente parte della chiave, rivela un'associazione **1:N** con partecipazione **obbligatoria** dal lato che contiene la FK;
- una FK **nullable** rivela un'associazione 1:N con partecipazione **opzionale** dal lato che contiene la FK;
- una relazione la cui chiave è **l'unione di due chiavi esterne** (più eventuali attributi propri) rivela un'associazione **N:N**.

### Analisi relazione per relazione

- **`Professore(ID, ...)` con FK `ID → Dipendente`**: la chiave di `Professore` è anche chiave esterna verso `Dipendente`. Questo è il pattern tipico di una **generalizzazione**: ogni professore è anche un dipendente, ma non ogni dipendente è un professore (generalizzazione **parziale**). Si ricostruisce quindi l'ISA `Professore` IS-A `Dipendente`.
- **`Dipendente(Dipartimento*)`**: FK opzionale verso `Dipartimento`, non in chiave → associazione **1:N** *Afferenza* fra `Dipendente` (lato N, partecipazione opzionale `(0,1)` per via del `*`) e `Dipartimento` (lato 1).
- **`Dipartimento(Direttore)`**: FK obbligatoria (non nullable) verso `Professore`, non in chiave, contenuta nella tabella "1" della relazione → associazione **1:1** *Direzione*: `Dipartimento` ha partecipazione obbligatoria `(1,1)` (ogni dipartimento ha esattamente un direttore), `Professore` ha partecipazione opzionale `(0,1)` (non ogni professore dirige un dipartimento). Corrisponde al Caso B delle associazioni 1:1 discusso in [[07 - Progettazione Logica]].
- **`CorsoDiStudio(Dipartimento)`**: FK obbligatoria verso `Dipartimento`, non in chiave → associazione **1:N** *Erogazione*: `CorsoDiStudio` lato N con partecipazione obbligatoria `(1,1)`, `Dipartimento` lato 1.
- **`Collaborazione(CorsoDiStudio, Professore, Tipo)`**: la chiave è l'unione delle chiavi esterne verso `CorsoDiStudio` e `Professore` → associazione **N:N** *Collaborazione* fra `CorsoDiStudio` e `Professore`, con attributo proprio `Tipo`.
- **`Corso(Materia, Docente, Semestre)`**: `Docente` è FK obbligatoria verso `Professore` → associazione **1:N** *Insegnamento*: `Corso` lato N con partecipazione obbligatoria, `Professore` lato 1 (un professore può insegnare più corsi).

> [!warning] Incoerenza nel testo — attributo `Materia`
> Il testo indica un vincolo di integrità referenziale fra l'attributo `Materia` di `Corso` e "la relazione `Materia`", ma nessuna relazione `Materia` compare fra quelle elencate nello schema: si tratta con ogni probabilità di un refuso della traccia originale (l'intento più plausibile è che `Corso` faccia riferimento a `CorsoDiStudio`, cioè che ogni corso appartenga a uno specifico corso di studio). Nella ricostruzione seguente si assume questa lettura, segnalando esplicitamente il punto di incertezza.

Assumendo `Materia → CorsoDiStudio`: **`Corso`** riceve una seconda associazione **1:N** *Composizione* verso `CorsoDiStudio` (un corso di studio è composto da più corsi, un corso appartiene a un solo corso di studio, partecipazione obbligatoria dal lato `Corso`).

### Schema concettuale ricostruito

**Entità**: `Dipendente`, `Professore` (sottoentità di `Dipendente` via ISA parziale), `Dipartimento`, `CorsoDiStudio`, `Corso`.

**Relationship**:

| Relationship | Entità coinvolte | Cardinalità | Attributi propri |
|---|---|---|---|
| *Afferenza* | Dipendente (N) — Dipartimento (1) | `(0,1)` — `(0,N)` | — |
| *Direzione* | Dipartimento (1) — Professore (1) | `(1,1)` — `(0,1)` | — |
| *Erogazione* | CorsoDiStudio (N) — Dipartimento (1) | `(1,1)` — `(0,N)` | — |
| *Collaborazione* | CorsoDiStudio (N) — Professore (N) | `(0,N)` — `(0,N)` | `Tipo` |
| *Insegnamento* | Corso (N) — Professore (1) | `(1,1)` — `(0,N)` | — |
| *Composizione* | Corso (N) — CorsoDiStudio (1) | `(1,1)` — `(0,N)` | — |

> [!info] Osservazione
> Le cardinalità massime dal lato "1" sono lasciate a `(0,N)` per default, in assenza di vincoli espliciti nello schema relazionale che impongano la partecipazione obbligatoria anche da quel lato (ad esempio, nulla impedisce che esista un dipartimento senza dipendenti afferenti). Solo il lato che contiene la chiave esterna non nullable è certamente obbligatorio.

## Quesito 2 — Interrogazioni SQL

> [!example] Schema dato
> `Corsi(<u>CodiceCorso</u>, TitoloCorso, CFU, Docente)`
>
> `Studenti(<u>Matricola</u>, Cognome, Nome)`
>
> `Esami(<u>CodiceCorso</u>, <u>Matricola</u>, Data, Voto)` — FK `CodiceCorso → Corsi`, FK `Matricola → Studenti`

### 1. Per ogni studente, il corso in cui ha preso il voto più alto

Per ogni riga di `Esami`, si confronta il voto con il massimo ottenuto dallo stesso studente (sottointerrogazione **correlata**, come discusso in [[11 - SQL Interrogazioni]]):

```sql
SELECT S.Matricola, S.Cognome, C.TitoloCorso, E.Voto
FROM   Esami E
       JOIN Studenti S ON E.Matricola   = S.Matricola
       JOIN Corsi    C ON E.CodiceCorso = C.CodiceCorso
WHERE  E.Voto = (SELECT MAX(E2.Voto)
                 FROM   Esami E2
                 WHERE  E2.Matricola = E.Matricola);
```

> [!info] Nota su eventuali pari merito
> Se uno studente ha preso lo stesso voto massimo in più corsi, la query restituisce **una riga per ciascuno** di quei corsi: non esiste ambiguità nel risultato, ma lo studente può comparire più volte.

### 2. Per ogni corso, quanti studenti vi hanno preso il proprio voto massimo

Come suggerito dal testo, si definisce una **vista** sulla base della query precedente e la si riusa per il conteggio (tecnica discussa in [[12 - Viste e Controllo degli Accessi]] per semplificare interrogazioni altrimenti più complesse):

```sql
CREATE VIEW MiglioreEsame (Matricola, CodiceCorso, Voto) AS
    SELECT E.Matricola, E.CodiceCorso, E.Voto
    FROM   Esami E
    WHERE  E.Voto = (SELECT MAX(E2.Voto)
                     FROM   Esami E2
                     WHERE  E2.Matricola = E.Matricola);

SELECT C.CodiceCorso, C.TitoloCorso, COUNT(*) AS NumStudenti
FROM   MiglioreEsame M
       JOIN Corsi C ON M.CodiceCorso = C.CodiceCorso
GROUP BY C.CodiceCorso, C.TitoloCorso;
```

Il conteggio è corretto anche in presenza di pari merito: se uno studente ha il proprio massimo in due corsi diversi, contribuisce con un'unità al conteggio di **ciascuno** dei due corsi (il che è coerente con la domanda "quanti studenti hanno preso *in tale corso* il proprio voto più alto").

### 3. Studenti che non hanno superato esami

Si interpreta "non hanno superato esami" come "non compaiono con nessuna riga in `Esami`" (nessun esame verbalizzato), usando `NOT EXISTS` su una sottointerrogazione correlata (evitando `NOT IN`, che darebbe risultati errati in presenza di `NULL`, come discusso in [[11 - SQL Interrogazioni]]):

```sql
SELECT S.Matricola, S.Cognome, S.Nome
FROM   Studenti S
WHERE  NOT EXISTS (SELECT *
                    FROM   Esami E
                    WHERE  E.Matricola = S.Matricola);
```

> [!info] Interpretazione alternativa
> Se invece nello schema fossero registrati anche gli esami **non superati** (es. `Voto < 18`), la query andrebbe riformulata per escludere gli studenti che hanno *almeno un* esame con voto sufficiente:
> ```sql
> SELECT S.Matricola, S.Cognome, S.Nome
> FROM   Studenti S
> WHERE  NOT EXISTS (SELECT *
>                     FROM   Esami E
>                     WHERE  E.Matricola = S.Matricola
>                       AND  E.Voto >= 18);
> ```
> Lo schema dato non specifica se `Esami` contenga anche i tentativi falliti; si è scelta l'interpretazione più diretta (nessuna riga in `Esami`).

## Quesito 3 — Cardinalità dei risultati di espressioni di join

> [!example] Relazioni date (nessun valore nullo)
> $R_1(\underline{A},B,C)$, con FK $(B,C) \to$ chiave $(D,E)$ di $R_2$, cardinalità $M_1 = 2000$
>
> $R_2(\underline{D,E},F)$, con FK $F \to$ chiave di $R_3$, cardinalità $M_2 = 200$
>
> $R_3(\underline{G},H,I)$, cardinalità $M_3 = 500$

### Principio generale

Come discusso in [[08 - Algebra Relazionale]] (proprietà del join naturale), se il predicato di join corrisponde **esattamente** a un vincolo di integrità referenziale verso una **chiave** dell'altra relazione, ogni tupla della relazione che contiene la FK trova **esattamente una** corrispondenza (né zero, per la FK, né più di una, per l'unicità della chiave): il join è quindi **completo e senza duplicazioni**, e la sua cardinalità è **esattamente** pari a quella della relazione che contiene la FK.

Se invece il predicato di join copre solo **parte** della chiave referenziata, la garanzia di unicità si perde: il join resta completo (nessuna tupla dangling dal lato della FK) ma può produrre **più corrispondenze** per ogni tupla, perché più righe dell'altra relazione possono condividere lo stesso valore sull'attributo parziale.

Se il predicato di join coinvolge attributi **non legati da alcun vincolo**, non si può dire nulla a priori: il risultato può variare fra 0 e il prodotto cartesiano completo.

### Espressione 1 — $R_1 \Join_{B=D} R_2$

Il predicato usa solo $B=D$, **non** l'intera FK $(B,C) \to (D,E)$. La FK garantisce comunque che per ogni tupla di $R_1$ esista almeno una tupla di $R_2$ con $D=B$ (quella con anche $E=C$): il join è **completo** dal lato di $R_1$, quindi il minimo si ha quando ogni valore di $B$ compare una sola volta come $D$ in $R_2$ — ogni tupla di $R_1$ produce **esattamente 1** risultato:
$$\text{minimo} = M_1 = 2000$$

Il massimo si ha nel caso limite in cui **tutte** le 200 tuple di $R_2$ condividano lo stesso valore di $D$ (possibile, perché la chiave è la coppia $(D,E)$: valori di $E$ distinti bastano a garantire l'unicità della chiave anche con $D$ costante). In tal caso ciascuna delle 2000 tuple di $R_1$ trova corrispondenza con tutte le 200 tuple di $R_2$:
$$\text{massimo} = M_1 \times M_2 = 2000 \times 200 = 400\,000$$

$$R_1 \Join_{B=D} R_2 \in [\,M_1,\; M_1 \times M_2\,] = [\,2000,\; 400\,000\,]$$

### Espressione 2 — $R_3 \Join_{I=A} R_1$

Non esiste alcun vincolo di integrità referenziale che leghi $I$ (di $R_3$) ad $A$ (di $R_1$): è un theta-join generico su attributi indipendenti. Non essendoci alcuna garanzia di completezza né di unicità, valgono solo i limiti generali del prodotto cartesiano ristretto:
$$R_3 \Join_{I=A} R_1 \in [\,0,\; M_1 \times M_3\,] = [\,0,\; 1\,000\,000\,]$$

- **Minimo 0**: nessun valore di $I$ coincide con nessun valore di $A$ (join vuoto).
- **Massimo $M_1 \times M_3 = 2000 \times 500 = 1\,000\,000$**: ogni tupla di $R_3$ corrisponde a ogni tupla di $R_1$ (ad esempio se $I$ e $A$ assumono ovunque lo stesso valore costante).

### Espressione 3 — $(R_1 \Join_{B=D \,\land\, C=E} R_2) \Join_{F=G} R_3$

**Primo join**: il predicato $B=D \land C=E$ corrisponde esattamente alla FK $(B,C) \to (D,E)$, chiave di $R_2$. Per il principio generale, questo join è completo e senza duplicazioni: ogni tupla di $R_1$ trova **esattamente una** corrispondenza in $R_2$ (quella referenziata dalla FK). Cardinalità **esatta** (non un intervallo):
$$|R_1 \Join_{B=D \,\land\, C=E} R_2| = M_1 = 2000$$

Il risultato intermedio ha quindi 2000 tuple, ciascuna con un valore di $F$ ereditato dalla corrispondente tupla di $R_2$.

**Secondo join**: il predicato $F=G$ corrisponde esattamente alla FK $F \to$ chiave $G$ di $R_3$. Per lo stesso principio, ognuna delle 2000 tuple intermedie trova **esattamente una** corrispondenza in $R_3$:
$$\left|(R_1 \Join_{B=D \,\land\, C=E} R_2) \Join_{F=G} R_3\right| = M_1 = 2000$$

> [!info] Sintesi
> Quando una catena di join ricalca esattamente una catena di vincoli di integrità referenziale verso chiavi (FK → chiave), la cardinalità del risultato finale è **sempre pari** alla cardinalità della relazione di partenza della catena ($M_1$ in questo caso), indipendentemente dalle cardinalità $M_2$, $M_3$ delle relazioni referenziate: ogni tupla di partenza genera esattamente un risultato, senza perdite né duplicazioni.

| Espressione | Intervallo cardinalità |
|---|---|
| $R_1 \Join_{B=D} R_2$ | $[2000,\ 400\,000]$ |
| $R_3 \Join_{I=A} R_1$ | $[0,\ 1\,000\,000]$ |
| $(R_1 \Join_{B=D \land C=E} R_2) \Join_{F=G} R_3$ | esattamente $2000$ |
