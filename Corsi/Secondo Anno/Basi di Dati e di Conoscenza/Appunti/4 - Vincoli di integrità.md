---
tags:
  - basi-di-dati
  - lezione
slide: "05 -VincoliIntegrita.pdf"
---
## Vincoli di integrità
I vincoli di integrità sono proprietà che devono essere soddisfatte dalle istanze affinché esse rappresentino informazioni corrette per l'applicazione.
Esistono, infatti, istanze di basi di dati che pur essendo sintatticamente corrette, non rappresentano informazioni possibili per il dominio di interesse.
Un vincolo è una funzione booleana (un **predicato** basato sulla logica del primo ordine) che associa ad ogni istanza il valore **vero** o **falso**.
I vincoli d'integrità consentono una descrizione più accurata della realtà e vengono usati dai DBMS nell'esecuzione delle interrogazioni e per prevenire errori.

> [!example] Base di dati "scorretta"
> **Esami**
>
> | Studente | Voto | Lode | Corso |
> |----------|------|------|-------|
> | 276545 | 32 | | 01 |
> | 276545 | 30 | e lode | 02 |
> | 787643 | 27 | e lode | 03 |
> | 739430 | 24 | | 04 |
>
> **Studenti**
>
> | Matricola | Cognome | Nome |
> |-----------|---------|------|
> | 276545 | Rossi | Mario |
> | 787643 | Neri | Piero |
> | 787643 | Bianchi | Luca |
>
> Violazioni presenti:
> - Voto **32** non è un voto valido (vincolo di dominio: `Voto >= 18 AND Voto <= 30`)
> - Lode **"e lode"** con voto **27** (vincolo di ennupla: `Voto = 30 OR NOT Lode = "e lode"`)
> - Matricola **739430** in Esami non esiste in Studenti (vincolo di integrità referenziale)
> - Matricola **787643** duplicata in Studenti con dati diversi (vincolo di chiave)

## Tipi di vincoli
I vincoli possono essere suddivisi in due macro-categorie:
- **Vincoli intrarelazionali**: coinvolgono una sola relazione.
  - **Vincoli su valori (o di dominio)**
  - **Vincoli di ennupla**
- **Vincoli interrelazionali**: coinvolgono più relazioni.
### Vincoli di ennupla
Esprimono condizioni sui valori di ciascuna ennupla, indipendentemente dalle altre ennuple.
Un caso particolare sono i **vincoli di dominio**, che coinvolgono un solo attributo.
Una possibile sintassi è un'espressione booleana di atomi che confrontano valori di attributo o espressioni aritmetiche su di essi.
	Esempi:
- `(Voto >= 18) AND (Voto <= 30)`
- `(Voto = 30) OR NOT (Lode = "e lode")`
- `Lordo = (Ritenute + Netto)`

> [!example] Vincolo di ennupla — Stipendi
> | Impiegato | Lordo | Ritenute | Netto |
> |-----------|-------|----------|-------|
> | Rossi | 55.000,00 € | 12.500,00 € | 42.500,00 € |
> | Neri | 45.000,00 € | 10.000,00 € | 35.000,00 € |
> | Bruni | 47.000,00 € | 11.000,00 € | 36.000,00 € |
>
> Vincolo: `Lordo = (Ritenute + Netto)`

## Chiavi e schemi di relazione
La chiave è un concetto fondamentale nel modello relazionale: garantisce l'**accessibilità** a ciascun dato della base di dati e permette di **correlare** i dati in relazioni diverse (modello basato su valori).
### Identificazione delle ennuple

> [!quote] Definizione — Superchiave
> Un insieme *K* di attributi è **superchiave** per una relazione *r* se *r* non contiene due ennuple distinte $t_1$ e $t_2$ con $t_1[K] = t_2[K]$.

> [!quote] Definizione — Chiave
> *K* è **chiave** per *r* se è una **superchiave minimale** per *r* (ossia, non contiene un'altra superchiave).

> [!info] Esistenza delle chiavi
> Una relazione non può contenere ennuple distinte ma uguali. Ogni relazione ha come superchiave l'insieme di tutti gli attributi su cui è definita, quindi ha (almeno) una chiave.

> [!example] Chiavi nella tabella Studenti
> | Matricola | Cognome | Nome | Corso | Nascita |
> |-----------|---------|------|-------|---------|
> | 27655 | Rossi | Mario | Matem. | 5/12/78 |
> | 78763 | Rossi | Mario | Fisica | 3/11/76 |
> | 65432 | Neri | Piero | Biologia | 10/7/79 |
> | 87654 | Neri | Mario | Fisica | 3/11/76 |
> | 67653 | Rossi | Piero | Biologia | 5/12/78 |
>
> - **Matricola** è una chiave: è superchiave (nessuna coppia uguale) e contiene un solo attributo, quindi è minimale.
> - **{Cognome, Nome, Nascita}** è un'altra chiave: è superchiave e minimale (nessun sottoinsieme proprio è superchiave).
> - **{Cognome, Corso}** non ha ennuple uguali in questa istanza, ma è una chiave solo "per caso" — non è garantito che valga per tutte le istanze possibili.

> [!warning] Vincoli a livello di schema vs istanza
> I vincoli corrispondono a proprietà del mondo reale modellato dalla base di dati. Interessano a **livello di schema** (con riferimento a tutte le istanze possibili). Ad uno schema associamo un insieme di vincoli e consideriamo **corrette** solo le istanze che soddisfano tutti i vincoli. Un'istanza può soddisfare altri vincoli "per caso".

### Chiave primaria
La **chiave primaria** (Primary Key) è una chiave su cui **non sono ammessi valori nulli**. Viene prescelta fra l'insieme di chiavi candidate secondo criteri di efficienza.
- **Notazione**: In uno schema, gli attributi che compongono la chiave primaria sono solitamente _sottolineati_.
## Chiavi e valori nulli
In presenza di valori nulli (`NULL`), i valori della chiave non permettono:
- di identificare le ennuple.
- di realizzare facilmente i riferimenti da altre relazioni.
Di conseguenza, la presenza di valori nulli nelle chiavi deve essere limitata.
## Integrità referenziale
Il **vincolo di integrità referenziale** ("Foreign Key" o Chiave Esterna) correla informazioni in relazioni diverse attraverso valori comuni. In particolare, impone ai valori di un insieme di attributi *X* in una relazione $R_1$ di comparire come valori della chiave primaria di un'altra relazione $R_2$.
Le correlazioni devono essere "coerenti": un record in $R_1$ non può fare riferimento a un record in $R_2$ che non esiste.

> [!example] Integrità referenziale — Infrazioni/Vigili/Auto
> **Infrazioni**
>
> | Codice | Data | Vigile | Prov | Numero |
> |--------|------|--------|------|--------|
> | 34321 | 1/2/95 | 3987 | MI | 39548K |
> | 53524 | 4/3/95 | 3295 | TO | E39548 |
> | 64521 | 5/4/96 | 3295 | PR | 839548 |
> | 73321 | 5/2/98 | 9345 | PR | 839548 |
>
> **Vigili**
>
> | Matricola | Cognome | Nome |
> |-----------|---------|------|
> | 3987 | Rossi | Luca |
> | 3295 | Neri | Piero |
> | 9345 | Neri | Mario |
> | 7543 | Mori | Gino |
>
> **Auto**
>
> | Prov | Numero | Cognome | Nome |
> |------|--------|---------|------|
> | MI | 39548K | Rossi | Mario |
> | TO | E39548 | Rossi | Mario |
> | PR | 839548 | Neri | Luca |
>
> Vincoli di integrità referenziale:
> - L'attributo `Vigile` di **Infrazioni** → chiave primaria `Matricola` di **Vigili**
> - Gli attributi `Prov, Numero` di **Infrazioni** → chiave primaria `Prov, Numero` di **Auto**

### Violazione e Azioni compensative
Cosa succede se un'operazione di aggiornamento (es. eliminazione di un'ennupla in $R_2$) viola l'integrità referenziale?
Sono previste alcune azioni compensative:
- **Rifiuto dell'operazione** (REJECT): annulla l'operazione che causa la violazione.
- **Eliminazione in cascata** (CASCADE): elimina anche le ennuple in $R_1$ che referenziavano il record eliminato.
- **Introduzione di valori nulli** (SET NULL): setta a `NULL` l'attributo in $R_1$ che referenziava il record eliminato.

> [!example] Azioni compensative — Impiegati/Progetti
> **Impiegati**
>
> | Matricola | Cognome | Progetto |
> |-----------|---------|----------|
> | 34321 | Rossi | IDEA |
> | 53524 | Neri | XYZ |
> | 64521 | Verdi | NULL |
> | 73032 | Bianchi | IDEA |
>
> **Progetti**
>
> | Codice | Inizio | Durata | Costo |
> |--------|--------|--------|-------|
> | IDEA | 01/2000 | 36 | 200 |
> | XYZ | 07/2001 | 24 | 120 |
> | BOH | 09/2001 | 24 | 150 |
>
> Se viene eliminato il progetto **XYZ** da Progetti:
> - **CASCADE**: elimina anche la riga di Neri (53524) da Impiegati
> - **SET NULL**: il Progetto di Neri diventa `NULL` → `(53524, Neri, NULL)`

> [!info] Commenti sull'integrità referenziale
> - Giocano un ruolo fondamentale nel concetto di "modello basato su valori".
> - In presenza di valori nulli i vincoli possono essere resi meno restrittivi.
> - Sono possibili meccanismi per il supporto alla loro gestione ("azioni compensative" a seguito di violazioni).

*(Questi meccanismi vengono implementati nei DBMS tramite le operazioni di UPDATE e DELETE sulle Foreign Key).*
## Vincoli di integrità semantica
I **vincoli di integrità semantica** sono basati sulla **semantica dell'applicazione** e **non possono essere espressi direttamente dal modello dei dati** (schema relazionale).

> [!example] Vincolo semantico
> "Il numero massimo di ore lavorate da un dipendente su tutti i progetti è 56 ore a settimana."

Per esprimere questi vincoli può essere necessario usare:
- **Linguaggi di specifica dei vincoli**
- Oppure **logica applicativa**
Nei sistemi SQL moderni tali vincoli possono essere implementati tramite:
- **TRIGGER**
- **CHECK constraints**
- **Stored procedures**
- **Application-level validation**
