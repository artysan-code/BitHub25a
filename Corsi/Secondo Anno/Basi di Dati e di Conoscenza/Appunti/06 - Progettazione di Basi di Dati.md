## Progettazione di una base di dati
**Progettare una base di dati** significa definirne **struttura**, **caratteristiche** e **contenuto**. L'attività prevede l'uso di opportune metodologie e si articola, in base al grado di astrazione, in tre livelli distinti:

- **Modello concettuale**: rappresenta la realtà dei dati e le relazioni tra essi attraverso uno schema, indipendentemente da qualsiasi sistema informatico.
- **Modello logico**: descrive il modo attraverso il quale i dati sono organizzati negli archivi del calcolatore (es. il modello relazionale).
- **Modello fisico**: descrive come i dati sono registrati nelle memorie di massa; dipende dal DBMS adottato.

## Ciclo di vita di un sistema informativo
La progettazione di una base di dati non è un'attività isolata, ma si inserisce nel **ciclo di vita** di un sistema informativo, composto da sei fasi sequenziali:

1. **Studio di fattibilità**: definisce le varie alternative possibili, i relativi costi e le priorità di realizzazione.
2. **Raccolta e analisi dei requisiti**: individua proprietà e funzionalità del sistema tramite interazione con gli utenti e definizione informale dei dati e delle operazioni.
3. **Progettazione**: divisa in *progettazione dei dati* e *progettazione delle applicazioni*. Individua struttura e organizzazione dei dati e caratteristiche degli applicativi che vi dovranno accedere.
4. **Implementazione**: realizza la base di dati e il codice dei programmi conformemente alle specifiche.
5. **Validazione e collaudo**: verifica il corretto funzionamento del sistema informativo.
6. **Funzionamento**: il sistema informativo diviene operativo.

## Schema del ciclo di progettazione
La progettazione si sviluppa lungo due direttrici parallele che si intersecano: una relativa alle **applicazioni** e una relativa ai **dati**. Lo schema seguente mostra il flusso completo:

```
              Mondo oggetto
                   |
         Raccolta e Analisi dei Requisiti
          /                         \
 Requisiti funzionali        Requisiti della base di dati
          |                               |
  Analisi Funzionale           Progettazione concettuale
          |                               |
  Specifica della transazione       Schema concettuale
          \                               |
           \                    Progettazione Logica
            \                             |
             \               Schema logico (modello DBMS)
              \                           |
       Progettazione programmi   Progettazione Fisica
              \                           |
               \                    Schema fisico
                \                        /
             Implementazione delle transazioni
```

La linea di separazione fondamentale corre fra la **progettazione logica** e la progettazione fisica: tutto ciò che sta sopra è **indipendente dal DBMS** adottato; ciò che sta sotto ne è **dipendente**.

> [!info] Specifiche sui dati vs specifiche sulle operazioni
> Nella progettazione si distinguono sempre due tipi di specifiche:
> - **Specifiche sui dati**: usate direttamente nella progettazione concettuale per costruire lo schema.
> - **Specifiche sulle operazioni**: usate per verificare che lo schema concettuale contenga tutte le informazioni necessarie all'esecuzione delle operazioni, e nella progettazione logica per ottenere uno schema che permetta di eseguirle in modo efficiente.

## Le tre fasi della progettazione

### Progettazione concettuale
Rappresenta le specifiche informali in modo **formale e completo**, ma **indipendente** dalla rappresentazione usata nei DBMS. Produce lo **schema concettuale**, fa riferimento a un **modello concettuale dei dati** (tipicamente il modello Entità-Relazione) e rappresenta il *contenuto informativo*, non la codifica.

Nella progettazione concettuale si usano principalmente le **specifiche sui dati**; le specifiche sulle operazioni servono a verificare che lo schema contenga tutte le informazioni necessarie alla loro esecuzione.

### Progettazione logica
Traduce lo schema concettuale nello **schema logico** basato su un modello logico (es. il modello relazionale), ancora **indipendente dalla realizzazione fisica** della base di dati. Il progettista deve conoscere il modello logico ma non il DBMS specifico adottato.

La fase di progettazione logica si suddivide in due passi:
1. **Ristrutturazione dello schema E-R**: fase indipendente dal modello logico, basata su criteri di ottimizzazione dello schema.
2. **Traduzione verso il modello logico**: fa riferimento a uno specifico modello logico (es. il modello relazionale).

Le specifiche sulle operazioni si usano per ottenere uno schema logico che permetta di eseguirle in modo efficiente.

### Progettazione fisica
Completa lo schema logico con la **specifica dei parametri fisici di memorizzazione** dei dati. Produce lo **schema fisico** e fa riferimento a un modello fisico dei dati, **dipendente dal DBMS** adottato. Si usano lo schema logico e le specifiche sulle operazioni per implementare il sistema in modo efficiente.

> [!info] Riassunto prodotti delle tre fasi
> | Fase | Prodotto | Dipendente dal DBMS? |
> |---|---|---|
> | Progettazione concettuale | Schema concettuale (E-R) | No |
> | Progettazione logica | Schema logico (es. relazionale) | No |
> | Progettazione fisica | Schema fisico | Si |

## Raccolta e analisi dei requisiti
La **progettazione concettuale** si suddivide in due sottofasi: raccolta e analisi dei requisiti, e definizione dello schema E-R.

### Cosa sono i requisiti
I **requisiti** definiscono le caratteristiche dell'applicazione da realizzare: i dati che deve gestire e le operazioni che deve supportare. Vengono spesso espressi con frasi in linguaggio naturale, spesso *ambigue* e *disorganizzate*. Il reperimento dei requisiti è un'attività difficile e non standardizzabile; l'analisi inizia con i primi requisiti raccolti e spesso indirizza verso altre acquisizioni.

### Criteri per una buona descrizione dei requisiti
L'obiettivo è produrre una descrizione del problema in linguaggio naturale che rispetti **completezza** e **non ambiguità**:
- corretto livello di astrazione
- frasi standardizzate
- semplicità delle specifiche (evitare frasi contorte)
- eliminazione di sinonimi o omonimi
- esplicitazione dei riferimenti fra termini
- glossario dei termini

Per i **dati**, specificare il numero delle **occorrenze** previste. Per le **operazioni**, specificare il **numero di volte** che si prevede debbano essere eseguite in un certo arco di tempo.

### Fonti dei requisiti
I requisiti si raccolgono da tre categorie di fonti:
- **Utenti**: tramite interviste e documentazione scritta.
- **Documentazione esistente**: normative, leggi e regolamenti del settore, regolamenti interni, procedure aziendali, moduli.
- **Realizzazioni preesistenti**: applicativi da rimpiazzare, applicazioni che dovranno interagire con il sistema da realizzare.

### Interazione con gli utenti
Utenti diversi forniscono informazioni diverse: gli utenti a livello più alto hanno spesso una visione più ampia ma meno dettagliata. Le interviste portano spesso a un'acquisizione dei requisiti *per raffinamenti successivi*; è necessario:
- effettuare spesso verifiche di comprensione e coerenza
- verificare anche per mezzo di esempi (generali e relativi a casi limite)
- richiedere definizioni e classificazioni
- far evidenziare gli aspetti essenziali rispetto a quelli marginali

> [!example] Esempio 1 — Base di dati bibliografica
> **Requisiti grezzi (versione completa):**
> Si vogliono organizzare i dati di interesse per automatizzare la gestione dei riferimenti bibliografici, con tutte le informazioni da riportarsi in una bibliografia. Le pubblicazioni sono di due tipi:
> - **Monografie**: interessano editore, data e luogo di pubblicazione.
> - **Articoli su rivista**: interessano nome della rivista, volume, numero, pagine e anno di pubblicazione.
>
> Per entrambi i tipi si devono riportare i nomi degli autori. Per ogni pubblicazione deve esistere un **codice identificante** costituito da sette caratteri: le iniziali degli autori, l'anno di pubblicazione e un carattere aggiuntivo per la discriminazione delle collisioni.

> [!example] Esempio 2 — Società di formazione (più articolato)
> **Requisiti organizzati per gruppi omogenei:**
>
> *Frasi di carattere generale:* Si vuole realizzare una base di dati per una società che eroga corsi, di cui vogliamo rappresentare i dati dei partecipanti ai corsi e dei docenti.
>
> *Frasi relative ai partecipanti (circa 5000):* Identificati da un codice, si rappresentano: codice fiscale, cognome, età, sesso, città di nascita, nomi dei datori di lavoro attuali e precedenti (con date di inizio e fine rapporto), edizioni dei corsi frequentati attualmente e nel passato con la relativa votazione finale in decimi.
>
> *Frasi relative a tipi specifici di partecipanti:* Per i **liberi professionisti**: area di interesse e, se posseduto, titolo professionale. Per i **dipendenti**: livello e posizione ricoperta.
>
> *Frasi relative ai datori di lavoro:* Nome, indirizzo e numero di telefono.
>
> *Frasi relative ai corsi (circa 200):* Titolo e codice; varie edizioni con date di inizio e fine; per ogni edizione: numero di partecipanti, giorno della settimana, aule e ore delle lezioni.
>
> *Frasi relative ai docenti (circa 300):* Cognome, età, città di nascita, tutti i numeri di telefono, titolo del corso insegnato, corsi insegnati nel passato e corsi che possono insegnare. I docenti possono essere **dipendenti interni** della società di formazione o **collaboratori esterni**.

> [!example] Glossario dei termini — Società di formazione
> | Termine | Descrizione | Sinonimi | Collegamenti |
> |---|---|---|---|
> | Partecipante | Persona che partecipa ai corsi | Studente | Corso, Società |
> | Docente | Docente dei corsi. Può essere esterno | Insegnante | Corso |
> | Corso | Corso organizzato dalla società. Può avere più edizioni | Seminario | Docente, Partecipante |
> | Società | Ente presso cui i partecipanti lavorano o hanno lavorato | Posto | Partecipante |

## Progettazione concettuale: criteri di rappresentazione
Una volta raccolti e organizzati i requisiti, si procede alla costruzione dello schema E-R. I criteri fondamentali per decidere come rappresentare i concetti sono:
- Rappresentare mediante **entità** le classi di oggetti con **esistenza autonoma** e caratterizzate da proprietà significative.
- Rappresentare mediante **attributi** gli oggetti con struttura semplice e che non presentino proprietà rilevanti.
- Rappresentare mediante **relazioni** i concetti che associano più entità precedentemente identificate.
- Rappresentare mediante **generalizzazioni** i concetti che risultino essere casi particolari di altri.

## Strategie di progettazione concettuale
Nella costruzione dello schema E-R si possono adottare strategie tipiche dello sviluppo di processi di ingegnerizzazione.

### Strategia top-down
A partire da uno schema che descrive le specifiche mediante **pochi concetti molto astratti**, si produce uno schema concettuale mediante **raffinamenti successivi** che aggiungono via via più dettagli. I raffinamenti vengono realizzati mediante trasformazioni elementari dette *primitive di trasformazione top-down*, che trasformano un concetto dello schema in una struttura più complessa.

Le sei primitive top-down sono:

| Primitiva | Concetto iniziale | Quando si applica |
|---|---|---|
| **T1** — da entità a relazione fra entità | Entità | Quando un'entità descrive due concetti distinti legati logicamente |
| **T2** — da entità a generalizzazione | Entità | Quando un'entità è composta da sotto-entità distinte o comprende più concetti |
| **T3** — da relazione a insieme di relazioni | Relazione | Quando una relazione descrive in realtà due o più relazioni fra le stesse entità |
| **T4** — da relazione ad entità con relazioni | Relazione | Quando una relazione descrive un concetto con esistenza autonoma o con più occorrenze |
| **T5** — introduzione di attributi in un'entità | Entità | Per introdurre nuovi attributi che descrivono meglio l'entità |
| **T6** — introduzione di attributi su relazioni | Relazione | Per aggiungere proprietà a relazioni |

> [!info] Visualizzazione del processo top-down
> Il processo top-down può essere immaginato come un imbuto che si allarga verso il basso: dallo schema iniziale (piccolo, astratto) si giunge allo schema finale (ampio, dettagliato) attraverso livelli successivi di schemi intermedi, ciascuno più raffinato del precedente.
> ```
> Specifiche
>     |
> [Schema iniziale]        <- pochi concetti astratti
>     | raffinamenti
> [Schema intermedio]
>     | raffinamenti
> [Schema intermedio]
>     | raffinamenti
> [Schema finale]          <- dettagliato e completo
> ```

### Strategia bottom-up
Le specifiche iniziali sono **suddivise in componenti** via via sempre più piccole, fino a descrivere frammenti elementari della realtà. Le componenti vengono poi **fuse** con trasformazioni successive (*primitive di trasformazione bottom-up*) per giungere allo schema concettuale finale. Ogni trasformazione introduce nuovi concetti non presenti al livello precedente.

Le cinque primitive bottom-up sono:

| Primitiva | Concetto iniziale | Quando si applica |
|---|---|---|
| **T1** — generazione di entità | (assente) | Quando si individua nelle specifiche una classe di oggetti caratterizzata da proprietà comuni |
| **T2** — generazione di relazione | Due o più entità | Quando si individua un legame logico fra entità |
| **T3** — generazione di generalizzazione | Più entità simili | Quando si individua un legame riconducibile a una generalizzazione (le entità sono istanze di una stessa classe) |
| **T4** — aggregazione di attributi su entità | Attributi sparsi | Quando si individua un'entità rappresentabile come aggregazione di attributi presenti nelle specifiche |
| **T5** — aggregazione di attributi su relazione | Attributi sparsi | Analoga a T4, ma relativa a una relazione |

> [!info] Processo bottom-up
> Le specifiche vengono decomposte in componenti (Componente 1, ..., Componente n), ciascuna ulteriormente scomposta in sottocomponenti a cui corrispondono schemi elementari. Questi schemi vengono poi integrati in uno **schema finale** unico tramite un passo di integrazione.

### Strategia inside-out
Può essere vista come un caso particolare della strategia bottom-up. Si individuano **solo alcuni concetti importanti** e si procede poi *a macchia d'olio*: si rappresentano prima i concetti più vicini a quelli di partenza, poi si sviluppano quelli più lontani attraverso una *navigazione* nelle specifiche.

- **Vantaggio**: non richiede passi di integrazione.
- **Svantaggio**: è necessario di volta in volta esaminare tutte le specifiche e descrivere i nuovi concetti nel dettaglio.
- **Limitazione**: non è possibile procedere per livelli di astrazione.

> [!example] Esempio inside-out — Schema aziendale
> Si individua il concetto centrale **Impiegato** con attributi (Codice, Cognome, Stipendio, Età). Si espande verso i concetti vicini:
> - prima cerchio: **Dipartimento** (collegato via relazione *Afferenza* e *Direzione*) con attributi Nome e Telefono
> - secondo cerchio: **Progetto** (collegato via *Partecipazione*) con Budget e Nome
> - terzo cerchio: **Sede** (collegata a Dipartimento via *Composizione*) con attributo composto Indirizzo (Via, CAP, Città)
>
> Lo schema cresce "a macchia d'olio" partendo dall'entità centrale.

### Strategia mista
La strategia mista cerca di **unire i vantaggi** delle strategie top-down e bottom-up. Viene considerata spesso l'**unica strategia realmente utilizzabile** su problemi complessi. Il processo si articola come segue:
- Da un lato si individuano **componenti elementari** (approccio bottom-up).
- Dall'altro si crea uno **schema scheletro** contenente i concetti di base, da espandere poi con raffinamenti successivi in modo top-down.
- Contemporaneamente, dalle specifiche, si creano in modo bottom-up i concetti non presenti nello schema scheletro.
- La strategia inside-out è di fatto **inglobata** nella strategia mista.

> [!quote] Definizione — Schema scheletro
> Lo **schema scheletro** è uno schema concettuale semplice che organizza i concetti più importanti dell'applicazione — quelli più citati nelle specifiche o indicati esplicitamente come cruciali. Costituisce il punto di partenza per la decomposizione e il raffinamento.

## Metodologia della progettazione concettuale
Il processo di progettazione concettuale con strategia mista si articola nei passi seguenti:

**1. Analisi dei requisiti**
- Analizzare i requisiti ed eliminare le ambiguità
- Costruire un glossario dei termini (con sinonimi e collegamenti)
- Raggruppare i requisiti in insiemi omogenei (frasi di carattere generale, frasi relative a ciascuna entità principale, ecc.)

**2. Passo base**
Definire uno **schema scheletro** con i concetti più rilevanti, ricavati dai requisiti (ad esempio le entità più citate o quelle esplicitamente indicate come centrali).

**3. Passo di decomposizione**
Effettuare una decomposizione dei requisiti con riferimento ai concetti presenti nello schema scheletro: ogni gruppo di frasi omogenee viene associato a un concetto dello scheletro.

**4. Passo iterativo** (da ripetere per tutti i sottoschemi finché ogni specifica è stata rappresentata)
- Raffinare i concetti presenti in base alle specifiche
- Aggiungere nuovi concetti non ancora rappresentati

**5. Passo di integrazione**
Integrare i vari sottoschemi utilizzando lo schema scheletro come riferimento comune.

**6. Analisi di qualità**
Verificare le proprietà di qualità dello schema finale (vedi sezione seguente).

## Qualità di uno schema concettuale
Nel definire uno schema concettuale si devono garantire quattro proprietà fondamentali:

> [!quote] Definizione — Correttezza
> Lo schema è **corretto** se utilizza propriamente i costrutti del modello di riferimento (entità, relazioni, attributi, generalizzazioni nel modello E-R). Errori tipici: usare un'entità dove è appropriata una relazione, o viceversa.

> [!quote] Definizione — Completezza
> Lo schema è **completo** se tutti i dati di interesse sono rappresentati e tutte le operazioni sono eseguibili a partire dai concetti descritti nello schema.

> [!quote] Definizione — Leggibilità
> Lo schema è **leggibile** se i requisiti sono rappresentati in modo naturale e comprensibile. La leggibilità riguarda l'estetica dello schema: nomi significativi, struttura chiara, assenza di incroci inutili fra gli archi.

> [!quote] Definizione — Minimalità
> Lo schema è **minimale** se le specifiche sono rappresentate una sola volta, senza ridondanze. Non sempre, tuttavia, eventuali ridondanze sono indesiderate: alcune possono essere introdotte deliberatamente per ragioni di efficienza e devono essere documentate.

> [!warning] Ridondanze volute
> La minimalità non è un requisito assoluto. Quando si introduce una ridondanza voluta nello schema (es. un attributo derivabile da altri dati già presenti), occorre documentarla esplicitamente per evitare che diventi una fonte di inconsistenze non gestite.
