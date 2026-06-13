## Progettazione Logica

La **progettazione logica** è la fase che trasforma lo schema concettuale E-R in uno **schema logico** — nel nostro caso, uno schema relazionale — che rappresenta le stesse informazioni in modo corretto ed efficiente e che sia indipendente dal DBMS specifico scelto.

Il processo non è una semplice traduzione meccanica: richiede anche una **ristrutturazione** dello schema E-R, perché alcuni costrutti del modello E-R (in particolare le generalizzazioni) non hanno una traduzione diretta nel modello relazionale, e perché è necessario tenere conto delle prestazioni attese.

### I due passi della progettazione logica

```
Schema E-R  ──┐
              │  + Carico applicativo
              ▼
    [Ristrutturazione dello schema E-R]
              │
              ▼  Schema E-R ristrutturato
              │  + Modello logico scelto
              ▼
    [Traduzione nel modello logico]
              │
              ▼
         Schema logico
```

**Passo 1 — Ristrutturazione dello schema E-R**: il diagramma E-R viene modificato per eliminare i costrutti non traducibili direttamente (generalizzazioni) e per ottimizzarlo rispetto alle operazioni previste. Il risultato è uno schema E-R ristrutturato.

**Passo 2 — Traduzione nel modello relazionale**: lo schema E-R ristrutturato viene tradotto meccanicamente in relazioni, applicando regole precise a seconda del tipo di costrutto.

## Analisi delle prestazioni su schemi E-R

Prima di ristrutturare lo schema è necessario analizzare le prestazioni attese dal sistema. I due principali indici di prestazione in qualsiasi sistema software sono:

- **Costo delle operazioni**: misurato, nel caso delle basi di dati, in funzione del numero di occorrenze delle entità e delle associazioni coinvolte nelle operazioni.
- **Occupazione di memoria**: spazio richiesto per memorizzare i dati.

Per compiere questa analisi è necessario conoscere:
- Il **volume dei dati**: numero di occorrenze di ogni entità e associazione, dimensioni degli attributi.
- Le **caratteristiche delle operazioni**: tipo (lettura o scrittura/interattiva o batch), frequenza, dati coinvolti.

> [!info] Regola dell'80/20
> In genere basta analizzare il costo delle operazioni più frequenti. L'80% del tempo di esecuzione è occupato dal 20% delle operazioni. Conviene concentrare l'ottimizzazione su quel 20%.

### Tavola dei volumi e tavola delle operazioni

Per descrivere il volume dei dati si costruisce la **tavola dei volumi**, in cui ogni concetto dello schema (entità o associazione) viene elencato con il suo volume previsto a regime.

| Concetto | Tipo | Volume |
|---|---|---|
| Sede | E | 10 |
| Dipartimento | E | 80 |
| Impiegato | E | 2000 |
| Progetto | E | 500 |
| Composizione | R | 80 |
| Afferenza | R | 1900 |
| Direzione | R | 80 |
| Partecipazione | R | 6000 |

Per descrivere le operazioni si costruisce la **tavola delle operazioni**, in cui per ogni operazione si indicano il tipo (I = interattiva, B = batch) e la frequenza.

| Operazione | Tipo | Frequenza |
|---|---|---|
| Op. 1 — assegna un impiegato a un progetto | I | 50 al giorno |
| Op. 2 — trova i dati di un impiegato, del suo dipartimento e dei suoi progetti | I | 100 al giorno |
| Op. 3 — trova i dati di tutti gli impiegati di un certo dipartimento | I | 10 al giorno |
| Op. 4 — per ogni sede, trova i dipartimenti con direttore e impiegati | B | 2 a settimana |

Per descrivere nel dettaglio il cammino logico di accesso di un'operazione si usa la **tavola degli accessi**, che riporta i concetti coinvolti, il numero medio di accessi e il tipo (L = lettura, S = scrittura). Gli accessi in scrittura vengono contati doppi rispetto a quelli in lettura per tenere conto del maggiore costo.

## Ristrutturazione dello schema E-R

La ristrutturazione si articola in quattro passi successivi.

### 1. Analisi delle ridondanze

> [!quote] Definizione — Ridondanza
> Una **ridondanza** in uno schema E-R si verifica quando un concetto (attributo o associazione) può essere derivato da altri concetti già presenti nello schema.

Esempi di ridondanze:
- Un attributo derivabile da altri attributi della stessa entità (es. `ImportoLordo` = `ImportoNetto` + `IVA` in FATTURA).
- Un attributo derivabile da attributi di altre entità e relazioni (es. `ImportoTotale` di un ACQUISTO, calcolabile sommando i prezzi dei PRODOTTI nella relazione COMPOSIZIONE).
- Un attributo derivabile contando le occorrenze (es. `NumeroAbitanti` di CITTÀ, contando le PERSONE residenti).
- Un'associazione derivabile da altre associazioni in presenza di cicli (es. DOCENZA tra STUDENTE e PROFESSORE, derivabile da FREQUENZA e INSEGNAMENTO passando per CORSO).

La decisione di mantenere o eliminare una ridondanza dipende da un'analisi costi/benefici:

| | Vantaggio | Svantaggio |
|---|---|---|
| **Con ridondanza** | Interrogazioni semplificate (meno accessi) | Aggiornamenti appesantiti; maggiore occupazione di spazio |
| **Senza ridondanza** | Aggiornamenti più semplici; meno spazio | Interrogazioni più costose (più accessi) |

> [!example] Analisi della ridondanza — NumeroAbitanti in Città
> Schema: PERSONA — (Residenza, 1:N) — CITTÀ con attributo ridondante `NumeroAbitanti` su CITTÀ.
>
> Tavola dei volumi: Città = 200 occorrenze, Persona = 10.000, Residenza = 10.000.
>
> Operazione 1 (500/giorno): memorizza una nuova persona con relativa città.
> Operazione 2 (2/giorno): stampa tutti i dati di una città incluso il numero di abitanti.
>
> **Con ridondanza — costo Op. 1**: per ogni nuova persona si scrive 1 occorrenza Persona (S), 1 occorrenza Residenza (S), si legge 1 occorrenza Città (L) e si aggiorna `NumeroAbitanti` (S).
> Accessi pesati = 500 × (2+2+1+2) = 500 × 7 ≈ 3500 al giorno.
>
> **Con ridondanza — costo Op. 2**: si legge 1 occorrenza Città (L) = trascurabile.
>
> Totale con ridondanza: **3500 accessi/giorno**.
>
> **Senza ridondanza — costo Op. 1**: si scrive 1 Persona (S), 1 Residenza (S) = 500 × 4 = 2000 accessi/giorno.
>
> **Senza ridondanza — costo Op. 2**: si legge 1 Città (L) + si scorrono tutte le 500 Residenze della città (L) = 2 × (1 + 500) ≈ 10.000 accessi/giorno.
>
> Totale senza ridondanza: **12.000 accessi/giorno**.
>
> In questo caso conviene **mantenere la ridondanza**: nonostante costi leggermente di più per Op. 1, il risparmio su Op. 2 (molto costosa senza ridondanza) non compensa perché Op. 2 è rara. Il costo totale con ridondanza (3500) è molto inferiore a quello senza (12000).

### 2. Eliminazione delle generalizzazioni

Il modello relazionale **non può rappresentare direttamente le generalizzazioni**. È dunque necessario eliminarle sostituendole con costrutti traducibili: entità e associazioni. Esistono tre strategie.

> [!info] Schema di riferimento per le tre strategie
> Sia data la generalizzazione: E0 (padre, con attributi A01, A02 e PK) generalizza E1 (figlia, con A11) e E2 (figlia, con A21, partecipa a R2 con E4). E0 partecipa anche a R1 con E3.

#### Strategia 1 — Accorpamento delle figlie nel padre

Si elimina le entità figlie e si porta tutto nell'entità padre, aggiungendo gli attributi specifici delle figlie e un attributo **Tipo** che indica di quale sottoclasse si tratta ogni occorrenza.

- **Quando usarla**: le entità figlie introducono differenziazioni non sostanziali (pochi valori `NULL` rispetto alle occorrenze totali); le operazioni non distinguono tra occorrenze del padre e delle figlie.
- **Pro**: meno accessi (un'unica entità da leggere).
- **Contro**: maggiore occupazione di memoria per i `NULL`; attributi specifici delle figlie valgono `NULL` per le occorrenze che non appartengono a quella sottoclasse.

> [!example] Strategia 1 — Personale ospedaliero
> Schema E-R originale: PERSONALE (CF, Nome, Cognome) generalizza MEDICO (Specializzazione) e VOLONTARIO (Associazione). MEDICO partecipa a "Effettuato da" con ESAME SPECIALISTICO e a "Lavora in" con REPARTO.
>
> Dopo la ristrutturazione, rimane solo PERSONALE con gli attributi di tutti:
> ```
> PERSONALE(CF, Nome, Cognome, Tipo, Specializzazione, Associazione)
> ```
> L'attributo `Tipo` vale es. "Medico" o "Volontario". `Specializzazione` è `NULL` per i volontari; `Associazione` è `NULL` per i medici. L'associazione "Effettuato da" viene ora collegata direttamente a PERSONALE (con partecipazione opzionale dal lato PERSONALE).

#### Strategia 2 — Accorpamento del padre nelle figlie

Si elimina l'entità padre e si riportano i suoi attributi in ciascuna entità figlia. Le associazioni cui partecipava il padre vengono duplicate, una per ciascuna figlia.

- **Possibile solo se la generalizzazione è totale** (ogni occorrenza del padre appartiene ad almeno una figlia).
- **Quando usarla**: le operazioni distinguono nettamente tra occorrenze delle diverse entità figlie.
- **Pro**: meno memoria rispetto alla strategia 1 (nessun `NULL`).
- **Contro**: più accessi rispetto alla strategia 3 perché le associazioni del padre vengono duplicate; impossibile se la generalizzazione è parziale (ci sarebbero occorrenze del padre senza nessuna figlia).

> [!example] Strategia 2 — Personale ospedaliero
> Si eliminano PERSONALE e si ottengono MEDICO (CF, Nome, Cognome, Specializzazione) e VOLONTARIO (CF, Nome, Cognome, Associazione), ciascuno con la propria copia dell'associazione "Lavora in" con REPARTO (ora "Lavora in 1" per MEDICO e "Lavora in 2" per VOLONTARIO).

#### Strategia 3 — Sostituzione con associazioni

La generalizzazione viene trasformata in una serie di **associazioni 1:1** tra il padre e ciascuna figlia. Ogni occorrenza del padre può partecipare ad al più una di tali associazioni (vincolo aggiuntivo da gestire applicativamente).

- **Quando usarla**: la generalizzazione è parziale, oppure le operazioni accedono spesso solo al padre senza scendere nelle figlie.
- **Pro**: meno memoria rispetto alla strategia 1.
- **Contro**: più accessi (bisogna navigare le associazioni per raggiungere gli attributi specifici delle figlie); i vincoli di esclusività e di copertura non sono direttamente esprimibili nel modello relazionale.

> [!example] Strategia 3 — Personale ospedaliero
> PERSONALE rimane entità indipendente. Si aggiungono due associazioni 1:1: "E' un" tra PERSONALE e MEDICO (con cardinalità (1,1) lato MEDICO e (0,1) lato PERSONALE) e "E' un" tra PERSONALE e VOLONTARIO (idem). MEDICO e VOLONTARIO mantengono i propri attributi specifici.

### 3. Partizionamento/accorpamento di entità e associazioni

L'obiettivo è ridurre il numero di accessi separando attributi acceduti da operazioni diverse e raggruppando attributi acceduti sempre insieme.

**Partizionamento verticale di un'entità**: si decompone un'entità in più entità sulla base degli attributi — utile quando operazioni diverse accedono a sottoinsiemi disgiunti di attributi. Ogni sotto-entità conserva la stessa chiave primaria e le due vengono collegate da un'associazione 1:1.

> [!example] Partizionamento verticale — Impiegato
> L'entità IMPIEGATO (Codice, Cognome, Indirizzo, DataNascita, Livello, Stipendio, Ritenute) viene partizionata in:
> - DATI-ANAGRAFICI (Codice, Cognome, Indirizzo, DataNascita)
> - DATI-LAVORATIVI (Codice, Livello, Stipendio, Ritenute)
> collegate da un'associazione R di tipo 1:1 con partecipazione obbligatoria da entrambi i lati.

**Partizionamento orizzontale**: si decompone un'entità sulla base delle sue occorrenze (sottoinsiemi distinti di tuple), equivalente a introdurre una generalizzazione. Obbliga a duplicare tutte le associazioni cui partecipava l'entità originale.

**Accorpamento di entità**: si fondono due entità coinvolte spesso nelle stesse operazioni in una sola entità. Viene eseguito tipicamente su associazioni 1:1. Può introdurre valori `NULL` se la partecipazione non è totale da entrambi i lati.

**Eliminazione degli attributi multivalore**: il modello relazionale non ammette attributi multivalore. Si eliminano sostituendoli con:
- Una nuova **relazione** separata (approccio generale), oppure
- La **decomposizione diretta** in più attributi distinti (se il numero massimo di valori è noto e piccolo, es. `Telefono1`, `Telefono2`).

> [!example] Eliminazione attributo multivalore — Persona con appartamento
> L'entità PERSONA con attributo multivalore `Indirizzo` (una persona può avere più indirizzi) viene ristrutturata: si crea l'entità APPARTAMENTO (Interno, Indirizzo) con un'associazione "Intestazione" 1:1 verso PERSONA (partecipazione opzionale dal lato PERSONA). In alternativa, se si assume che ogni persona abbia al massimo 2 appartamenti, si aggiungono i due attributi opzionali `Interno` e `Indirizzo` direttamente a PERSONA.

**Partizionamento/accorpamento di associazioni**: è possibile anche partizionare un'associazione in più associazioni (es. `Composizione` tra GIOCATORE e SQUADRA, che gestisce sia la composizione attuale che quella passata, viene divisa in `ComposizioneAttuale` e `ComposizionePassata`).

### 4. Scelta degli identificatori primari

La scelta è fondamentale perché le chiavi primarie hanno un ruolo centrale nel modello relazionale (accesso, riferimenti). Criteri da seguire, in ordine di priorità:

1. **Escludere attributi con valori nulli**: la chiave primaria non può ammettere `NULL`.
2. **Preferire identificatori con pochi attributi**: chiavi semplici sono più efficienti.
3. **Preferire identificatori interni** rispetto a identificatori esterni (quelli che richiedono la chiave di un'altra entità).
4. **Preferire identificatori usati da molte operazioni** per accedere alle occorrenze.
5. **Se nessun identificatore soddisfa i criteri**, è consigliabile introdurre un attributo artificiale (codice identificativo, es. un numero progressivo).

## Traduzione nel modello relazionale

Dopo la ristrutturazione, si traduce lo schema E-R nel modello relazionale applicando le seguenti regole sistematicamente. Per schemi complessi conviene procedere per gradi:
1. Traduzione delle entità regolari.
2. Traduzione delle entità con identificazione esterna (entità deboli).
3. Traduzione delle associazioni rimaste (alcune già tradotte al passo 2).

### Entità

> [!quote] Definizione — Regola per le entità
> Ogni **entità** diventa una **relazione** (tabella). Ogni attributo dell'entità diventa una colonna. L'identificatore univoco dell'entità diventa la **chiave primaria** (PK) della relazione.

La notazione degli schemi di relazione usata in queste note è:

```
NomeRelazione(<u>ChiavePrimaria</u>, attributo2, *ForeignKey*)
```

dove la PK è sottolineata e le FK sono in corsivo.

> [!example] Entità — Studenti
> L'entità STUDENTI con attributi Nome, Cognome, Matricola (identificatore), VotoMedio si traduce in:
>
> `Studenti(<u>Matricola</u>, Nome, Cognome, VotoMedio)`

### Associazione N:N

> [!quote] Definizione — Regola per le associazioni N:N
> Un'associazione **molti a molti** diventa una nuova relazione (tabella) composta dagli **identificatori delle due entità** partecipanti (come FK) più gli eventuali **attributi propri** dell'associazione. La **chiave primaria** della nuova relazione è l'insieme degli identificatori delle due entità (più eventuali attributi necessari a garantire l'unicità).

Per ogni FK verso le entità partecipanti si instaura un **vincolo di integrità referenziale**.

> [!example] Associazione N:N — Esame tra Studente e Corso
> Schema E-R: STUDENTE (0,N) — Esame — (0,N) CORSO, con attributo `Voto` sull'associazione.
>
> Traduzione:
> ```
> Studente(<u>Matricola</u>, Nome, Cognome)
> Corso(<u>CodCorso</u>, Nome)
> Esame(<u>Matricola</u>, <u>CodCorso</u>, Voto)
> ```
> Vincoli di integrità referenziale: `Matricola` in Esame → `Matricola` in Studente; `CodCorso` in Esame → `CodCorso` in Corso.
>
> In notazione compatta:
>
> `Esame(<u>*Matricola*</u>, <u>*CodCorso*</u>, Voto)`

> [!example] Associazione N:N — Impiegato e Progetto (dal libro Atzeni)
> Schema E-R: IMPIEGATO (0,N) — Partecipazione — (0,N) PROGETTO, con attributo `DataInizio`.
>
> ```
> Impiegato(<u>Matricola</u>, Cognome, Stipendio)
> Progetto(<u>Codice</u>, Nome, Budget)
> Partecipazione(<u>*Matricola*</u>, <u>*Codice*</u>, DataInizio)
> ```

### Associazione 1:N

> [!quote] Definizione — Regola per le associazioni 1:N
> Un'associazione **uno a molti** viene rappresentata aggiungendo, agli attributi dell'entità che svolge il **ruolo a molti**, l'identificatore dell'entità con ruolo a uno. Questo identificatore prende il nome di **chiave esterna** (foreign key, FK). Gli eventuali attributi dell'associazione vengono inseriti anch'essi nell'entità con ruolo a molti, insieme alla FK.

In questo modo non è necessaria una relazione separata per l'associazione: si usa la relazione dell'entità lato N.

> [!example] Associazione 1:N — Persona risiede in Comune
> Schema E-R: PERSONA (1,1) — Residenza — (1,N) COMUNE, con attributo `DataTrasferimento`.
>
> PERSONA ha il ruolo a molti (ogni comune può avere molte persone residenti). La FK `NomeComune` e l'attributo `DataTrasferimento` vanno in PERSONA:
>
> ```
> Persona(<u>CodiceFiscale</u>, Nome, Cognome, *NomeComune*, DataTrasferimento)
> Comune(<u>NomeComune</u>, Provincia)
> ```

**Caso con partecipazione opzionale lato N**: se la cardinalità minima del lato N è 0 (es. uno studente potrebbe non essersi ancora laureato), allora la FK nella relazione lato N deve ammettere valori `NULL`.

> [!example] Associazione 1:N con partecipazione opzionale — Laurea
> Schema E-R: STUDENTE (0,1) — Laurea — (0,N) FACOLTA, con attributo `DataLaurea`. Entrambi i lati sono opzionali.
>
> Soluzione 1 (relazione separata per l'associazione, elimina i `NULL`):
> ```
> Studente(<u>Matricola</u>, Nome, Cognome)
> Facolta(<u>NomeFacolta</u>, Citta)
> Laurea(<u>*Matricola*</u>, *NomeFacolta*, DataLaurea)
> ```
>
> Soluzione 2 (FK nullable in Studente, più compatta):
> ```
> Studente(<u>Matricola</u>, Nome, Cognome, *NomeFacolta*, DataLaurea)
> Facolta(<u>NomeFacolta</u>, Citta)
> ```
> In questo caso `NomeFacolta` e `DataLaurea` possono essere `NULL` per gli studenti non ancora laureati (indicato con `*` nelle slide).

### Associazione 1:1

Le associazioni uno a uno sono il caso più delicato e il trattamento dipende dalla **partecipazione** (obbligatoria o opzionale) delle entità coinvolte.

#### Caso A — Entrambe le entità con partecipazione obbligatoria (1,1):(1,1)

Si può fondere tutto in **un'unica relazione** oppure scegliere una delle due entità come "lato N fittizio" e inserire la FK nell'altra. Poiché la partecipazione è totale da entrambi i lati, qualunque scelta non introduce `NULL`.

> [!example] Associazione 1:1 obbligatoria — Direttore e Dipartimento
> Schema E-R: DIRETTORE (1,1) — Direzione — (1,1) DIPARTIMENTO, con attributo `DataInizio`.
>
> Soluzione A: FK di Dipartimento in Direttori (attributi della relazione in Direttori):
> ```
> Direttori(<u>Codice</u>, Cognome, Stipendio, *DipartimentoDiretto*, InizioDirezione)
> Dipartimenti(<u>Nome</u>, Telefono, Sede)
> ```
>
> Soluzione B: FK di Direttore in Dipartimenti:
> ```
> Direttori(<u>Codice</u>, Cognome, Stipendio)
> Dipartimenti(<u>Nome</u>, Telefono, Sede, *Direttore*, InizioDirezione)
> ```
>
> Entrambe le soluzioni sono corrette. In pratica si sceglie la soluzione che minimizza gli accessi per le operazioni più frequenti.

#### Caso B — Una sola entità con partecipazione opzionale (0,1):(1,1)

Si tratta come un'associazione **uno a molti**: l'entità con partecipazione opzionale viene considerata come il lato N (può non avere la controparte), e si inserisce la FK nell'entità con partecipazione **obbligatoria**, così da non avere valori `NULL`.

> [!example] Associazione 1:1 con partecipazione opzionale da un lato — Rettore
> Schema E-R: PROFESSORE (0,1) — Rettore — (1,1) UNIVERSITA, con attributo `DataElezione`.
> (Un professore può non essere rettore; ogni università ha esattamente un rettore.)
>
> UNIVERSITA ha partecipazione obbligatoria, quindi la FK va in UNIVERSITA:
> ```
> Professore(<u>Matricola</u>, Nome, Cognome)
> Universita(<u>NomeUniversita</u>, Citta, *Matricola*, DataElezione)
> ```
> Così `Matricola` in Universita non sarà mai `NULL` (ogni università ha sempre il suo rettore).

#### Caso C — Entrambe le entità con partecipazione opzionale (0,1):(0,1)

Si tratta come un'associazione **molti a molti**, creando una **terza relazione** separata per l'associazione. Questo evita i valori `NULL` che si avrebbero se si fondesse tutto in un'unica relazione o si mettesse la FK in una delle due.

> [!example] Associazione 1:1 con partecipazione opzionale da entrambi i lati
> Schema E-R: PROFESSORE (0,1) — Rettore — (0,1) UNIVERSITA, con attributo `DataElezione`.
> (Non tutti i professori sono rettori; non tutte le università hanno un rettore in questo momento.)
>
> ```
> Professore(<u>Matricola</u>, Nome, Cognome)
> Universita(<u>NomeUniversita</u>, Citta)
> Rettore(<u>*Matricola*</u>, *NomeUniversita*, DataElezione)
> ```
> oppure, in alternativa equivalente:
> ```
> Rettore(<u>*NomeUniversita*</u>, *Matricola*, DataElezione)
> ```

### Associazioni ricorsive

Le associazioni che coinvolgono la stessa entità in ruoli diversi seguono le stesse regole delle associazioni binarie, ma è necessario **rinominare gli attributi** per riflettere i diversi ruoli.

**Ricorsiva 1:N**: si può tradurre con una sola relazione che contiene due volte l'identificatore dell'entità — una come PK, una come FK rinominata con il nome del ruolo.

> [!example] Associazione ricorsiva 1:N — Supervisione tra Impiegati
> Ogni impiegato può avere un supervisore (che è a sua volta un impiegato). La relazione 1:N ricorsiva si traduce in:
> ```
> Impiegato(<u>Matricola</u>, Cognome, Stipendio, *Supervisore*)
> ```
> dove `Supervisore` è una FK che punta a `Matricola` nella stessa relazione. Per gli impiegati senza supervisore, `Supervisore` è `NULL`.

**Ricorsiva N:N**: si traduce con due relazioni — una per l'entità, una per l'associazione. La relazione dell'associazione ha due FK verso la stessa entità, rinominate con i nomi dei due ruoli.

> [!example] Associazione ricorsiva N:N — Composizione tra Prodotti
> Un prodotto può essere composto da più prodotti (componenti) e un componente può essere usato in più prodotti composti. L'associazione ricorsiva N:N COMPOSIZIONE ha l'attributo `Quantità`.
>
> ```
> Prodotto(<u>CodP</u>, Nome, Costo)
> Composizione(<u>*CodComposto*</u>, <u>*CodComponente*</u>, Quantità)
> ```
> `CodComposto` e `CodComponente` sono entrambi FK verso `CodP` in Prodotto, con nomi diversi per riflettere il ruolo.

### Associazioni n-arie

Le associazioni che coinvolgono più di due entità (ternarie, quaternarie, ecc.) si traducono sempre con una **nuova relazione** la cui chiave è l'insieme delle chiavi di tutte le entità partecipanti (più eventuali attributi necessari a garantire l'unicità), e i cui attributi FK puntano a ciascuna entità.

> [!example] Associazione ternaria — Fornitura
> Schema E-R: FORNITORE (0,N) — Fornitura — (1,N) PRODOTTO e Fornitura — (1,N) DIPARTIMENTO, con attributo `Quantità`.
>
> ```
> Fornitore(<u>PartitaIVA</u>, Nome)
> Prodotto(<u>Codice</u>, Genere)
> Dipartimento(<u>Nome</u>, Telefono)
> Fornitura(<u>*Fornitore*</u>, <u>*Prodotto*</u>, <u>*Dipartimento*</u>, Quantità)
> ```
> Le tre FK (`Fornitore` → `PartitaIVA`, `Prodotto` → `Codice`, `Dipartimento` → `Nome`) formano insieme la chiave primaria di FORNITURA.

### Entità deboli (identificazione esterna)

Un'entità con **identificazione esterna** (entità debole) si identifica parzialmente tramite un'associazione con un'altra entità (l'entità proprietaria). Poiché partecipa all'associazione identificante con cardinalità (1,1), si ricade nel caso delle associazioni uno a molti.

L'associazione e l'entità debole vengono tradotte **nella stessa relazione**: la PK della relazione risultante è la **combinazione della PK dell'entità proprietaria** (importata come FK) con la **chiave parziale** dell'entità debole.

> [!example] Entità debole — Studente identificato da Università
> Schema E-R: STUDENTE (1,1) — Iscrizione — (1,N) UNIVERSITA. STUDENTE ha come attributi Matricola (chiave parziale, unica solo all'interno della stessa università), Cognome, AnnoIscrizione.
>
> ```
> Universita(<u>Nome</u>, Citta, Indirizzo)
> Studente(<u>Matricola</u>, <u>*NomeUniversita*</u>, Cognome, AnnoIscrizione)
> ```
> La PK di STUDENTE è la coppia (Matricola, NomeUniversita): la stessa matricola può esistere in università diverse.

### Attributi composti e multivalore

**Attributi composti**: nel modello relazionale si "appiattiscono" nelle loro componenti semplici, oppure si mantengono come stringa unica se la struttura interna non è mai interrogata separatamente.

**Attributi multivalore**: non ammessi nel modello relazionale. Si eliminano durante la ristrutturazione (vedi § 3) creando una nuova relazione. La nuova relazione ha come attributi il valore multivalore stesso e la FK verso l'entità di appartenenza; la PK è la coppia (FK, valore).

> [!example] Attributo multivalore — Locations di un Dipartimento
> L'entità DEPARTMENT ha l'attributo multivalore `Locations` (un dipartimento può avere più sedi).
>
> Si crea la relazione:
> ```
> DeptLocations(<u>*DNumber*</u>, <u>DLocation</u>)
> ```
> con FK `DNumber` → PK di DEPARTMENT. La PK di DeptLocations è la coppia (DNumber, DLocation).

## Tabella riepilogativa — Corrispondenza ER → Relazionale

| Costrutto ER | Traduzione nel modello relazionale |
|---|---|
| Entità (tipo regolare) | Relazione con tutti gli attributi semplici |
| Associazione 1:1 o 1:N | FK (o relazione separata per l'associazione) |
| Associazione M:N | Relazione separata con due FK come PK composita |
| Associazione n-aria | Relazione separata con n FK come PK composita |
| Attributo semplice | Attributo (colonna) |
| Attributo composto | Insieme degli attributi semplici componenti |
| Attributo multivalore | Relazione separata + FK |
| Identificatore (key attribute) | Chiave primaria (o secondaria) |
| Entità debole | Relazione con PK = chiave parziale + FK del proprietario |
| Generalizzazione | Eliminazione prima della traduzione (3 strategie) |
