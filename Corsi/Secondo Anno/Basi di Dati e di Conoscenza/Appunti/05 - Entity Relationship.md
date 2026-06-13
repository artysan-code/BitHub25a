## Progettazione Concettuale
Progettare una base di dati significa definirne **struttura**, **caratteristiche** e **contenuto**. Prevede l'uso di opportune metodologie basate sul grado di astrazione:
1. **Modello concettuale**: rappresenta la realtà dei dati e le relazioni tra essi in modo astratto e indipendente dalle applicazioni.
2. **Modello logico**: descrive come i dati sono organizzati per essere gestiti dal DBMS (es. relazionale, a oggetti, gerarchico).
3. **Modello fisico**: descrive l'implementazione fisica nelle memorie di massa.
Il modello concettuale è una rappresentazione **astratta** della realtà: definire un insieme di dati presenti in natura che rappresentano la natura stessa delle informazioni che si vogliono archiviare. **Non esistono regole prefissate** per l'individuazione dei dati e per la loro selezione.

> [!info] Le 5 domande della progettazione
> 1. Cosa c'è? (Oggetti)
> 2. Come si collegano o si parlano?
> 3. Quanti tra loro?
> 4. Cosa identifica gli "oggetti"?
> 5. Quali informazioni utili non principali?

## Il Modello Entità-Relazione (ER)
Il modello Entità-Relazione (ER = Entity/Relationship) è uno strumento per analizzare le caratteristiche di una realtà in modo indipendente dagli eventi che in essa accadono, cioè per costruire un modello concettuale dei dati indipendente dalle applicazioni.
Sono stati sviluppati modelli più moderni:
- **Modello Entità Relazioni Esteso (EER)**: consente l'utilizzo di costrutti più potenti (es. ereditarietà).
- **UML**: linguaggio unificato per la progettazione dei dati e delle funzioni.
### Costrutti principali
#### Entità

> [!quote] Definizione — Entità
> È un oggetto, concreto o astratto, che ha un significato anche quando viene considerato in modo isolato ed è di interesse per la realtà che si vuole modellare.

- Esempi: `Studente`, `Automobile`, `Persona`. Le singole istanze formano il livello estensionale.
- Le entità possono essere **statiche** (non cambiano nel tempo) o **dinamiche** (cambiano nel tempo).
##### Entità deboli e forti
Entità che non hanno una chiave primaria e devono essere associate ad un'altra entità per essere completamente significative prendono il nome di **entità deboli**. Le entità indipendenti sono **forti**.

> [!example] Entità deboli — Movimento/Conto/Cliente
> `Movimento` ha senso solo in relazione a `Conto` → `Movimento` è un'entità debole. `Cliente` e `Conto` sono entità forti. Per risolvere la debolezza spesso si introduce una *chiave artificiale* (id autoincrementale).

#### Relazione (Associazione)

> [!quote] Definizione — Relazione (Associazione)
> È un legame logico che stabilisce un'interazione tra due o più entità.

- Può avere un *verso* (il nome evocativo, es. "Possedere" o "Essere posseduta") e un *ruolo* (es. genitore-figlio).
- **Relazioni ricorsive**: avvengono tra un'entità e se stessa (es. `Persona` che è "figlio di" un'altra `Persona`, con ruoli **Genitore** e **Figlio**).
- **Relazioni n-arie**: relazioni che coinvolgono tre o più entità (spesso scomposte in associazioni binarie).

> [!example] Relazione ternaria — Chirurgo/Opera/Sala operatoria
> La relazione `Opera` coinvolge tre entità: `Chirurgo`, `Sala operatoria` e `Intervento`. Una relazione ternaria si scompone in diverse relazioni binarie.

#### Attributi e Chiavi
Le proprietà delle entità e delle relazioni sono descritte dagli **attributi**. Alcune caratteristiche che descrivono il **dominio** di un attributo:
- **Formato**: tipo di valore che assume (carattere, numerico, data/ora, …)
- **Dimensione**: quantità max di caratteri o cifre inseribili
- **Opzionalità**: possibilità di non essere sempre valorizzato
Ulteriori proprietà del dominio:
- **Tipo di dato**: intero, decimale, carattere, data, …
- **Lunghezza**: numero di cifre o caratteri per rappresentare il valore dell'attributo
- **Intervallo**: limite superiore e inferiore dei valori
- **Vincoli**: restrizioni sui valori ammessi
- **Supporto del valore NULL**: quando non è assegnato nessun valore
- **Valore di default**

> [!warning] Regole per chiavi primarie e esterne
> **Per le chiavi primarie:**
> - Il valore deve essere unico e i `NULL` non sono ammessi
>
> **Per le chiavi esterne:**
> - Il tipo di dato, la lunghezza e il formato della chiave esterna devono essere uguali a quelli della corrispondente chiave primaria

La **chiave primaria** è un attributo (o insieme di attributi) che identifica univocamente un'istanza dell'entità. La chiave primaria non può essere opzionale (non ammette `NULL`) né ripetuta.
##### Chiave artificiale
Spesso, anche in presenza di chiavi palesi, si utilizza un numero progressivo come chiave primaria ovvero una **chiave artificiale**. Una chiave artificiale è formata da un attributo privo di significato proprio. Di solito consiste in un contatore che si autoincrementa ad ogni istanza che si aggiunge.
##### Attributi delle relazioni
Anche le relazioni possono avere attributi propri.

> [!example] Attributi di una relazione — Acquistare
> La relazione `acquistare` tra `Automobile` e `Persona` può avere attributi propri: `targa`, `prezzo acquisto`, `data acquisto`. Questi attributi non appartengono né all'automobile né alla persona, ma all'atto dell'acquisto.

### Molteplicità (Cardinalità)
La **molteplicità** di una relazione è il numero di possibili istanze di un'entità che sono messe in corrispondenza con un'istanza dell'altra entità.
Definisce il numero minimo e massimo di associazioni a cui un'istanza può (o deve) partecipare: `(min, max)`.
- I valori **min** e **max** assunti dalla molteplicità sono: `(1,1)`, `(1,N)`, `(0,1)`, `(0,N)`.
- `min`: se è **0** la partecipazione è **facoltativa**, se è **1** è **obbligatoria**.
- `max`: definisce la cardinalità dell'associazione, assume i valori **1** e **N**.
Tipi di associazione in base alla cardinalità massima:
- **Uno a uno (1:1)**: ad ogni istanza di E1 corrisponde una sola istanza di E2 e viceversa.
- **Uno a molti (1:N)** o (N:1): ad ogni istanza di E1 corrispondono una o più istanze di E2 e ad ogni istanza di E2 corrisponde una sola istanza di E1.
- **Molti a molti (N:N)**: ad ogni istanza di E1 corrispondono una o più istanze di E2 e viceversa.
## Ereditarietà e Generalizzazione (IS-A)
Può accadere che sussista **l'associazione IS-A** (o associazione di sottoinsieme) tra due entità, e cioè che ogni istanza di una sia anche istanza dell'altra.
La associazione IS-A nel modello ER si può definire tra due entità, che si dicono "entità padre" ed "entità figlia" (o sottoentità, cioè quella che rappresenta un sottoinsieme dell'entità padre).
- **Principio di ereditarietà**: ogni proprietà dell'entità padre è anche una proprietà della sottoentità, e non si riporta esplicitamente nel diagramma. L'entità figlia può avere ulteriori proprietà.
- L'associazione IS-A si eredita, pertanto **IS-A è transitiva** (es. `Fuori corso` IS-A `Studente` IS-A `Persona` → `Fuori corso` IS-A `Persona`).
- Il modello ER classico **non ammette l'ereditarietà multipla** (una entità figlia ha al massimo un padre).
### Tipi di Generalizzazione
L'entità padre può generalizzare diverse sottoentità rispetto ad un unico criterio. In questo caso si parla di **generalizzazione**. Nella generalizzazione, le sottoentità hanno insiemi di istanze disgiunti a coppie (anche se in alcune varianti del modello ER, si può specificare se due sottoentità della stessa entità padre sono disgiunte o no).
- **Disjoint / Overlapping**:
  - *Disjoint* (non sovrapposte): l'intersezione tra le istanze figlie è nulla (es. `Uomo` e `Donna`).
  - *Overlapping* (sovrapposte): una stessa istanza può appartenere a più sottoentità (es. `BarcaAVela` e `BarcaAMotore`).
- **Complete / Incomplete**:
  - *Complete*: l'unione delle istanze delle sottoclassi copre tutte le istanze del padre.
  - *Incomplete*: esistono istanze del padre che non fanno parte di nessuna sottoclasse (es. `Gatto` e `Cane` per `Mammifero`).
Il principio di ereditarietà vale anche per le generalizzazioni.
## Diagrammi delle Classi in UML
UML (Unified Modeling Language) è uno standard per la progettazione orientata agli oggetti e amplia/integra i concetti dell'ER.

> [!quote] Definizione — Diagramma delle classi
> Il *diagramma delle classi* è un grafo che descrive i tipi degli oggetti in un sistema, le relazioni statiche tra essi, gli attributi e le operazioni di una classe, ed i vincoli sulle relazioni. Sono definiti come *Diagrammi a struttura statica*.

Una classe è rappresentata da un rettangolo scomposto in tre parti:
1. **Nome** della classe
2. **Attributi** della classe (con visibilità e tipo, es. `-cognome : String`)
3. **Operazioni/Metodi** della classe (es. `+setViaggio() : void`)
Vengono utilizzati per:
- Documentare le classi che compongono un sistema o un sottosistema.
- Descrivere **associazioni**, **generalizzazioni**, **aggregazioni** fra le varie classi.
- Evidenziare le caratteristiche di una classe — **attributi** e **operazioni**.
### Attributi e Istanze in UML
Un **attributo** modella una proprietà locale della classe ed è caratterizzato da un nome e dal tipo dei valori associati. Ogni attributo stabilisce una proprietà locale valida per **tutte le istanze** della classe.
Tra un oggetto (istanza) e la classe si traccia un arco **Instance-of**. Gli oggetti formano il livello **estensionale**, le classi il livello **intensionale**.
Due oggetti con identificatori distinti sono comunque distinti, anche se hanno i valori di tutti gli attributi uguali.
Ulteriori specifiche degli attributi:
- **Molteplicità**: `[m..n]` dove m è il numero minimo e n il massimo (es. `1..1` troncato a `1`, `0..*` troncato a `*`)
- **Attributi derivati**: calcolati da altri attributi (es. `/età` derivato da `oggi - dataDiNascita`)
- **Valori iniziali**: valori di default (es. `dataRegistrazione : Date = Oggi`)
### Visibilità in UML
- `-` **Private**: disponibile solo all'interno della classe che la definisce.
- `+` **Public**: disponibile per le classi associate alla classe che la definisce.
- `#` **Protected**: disponibile all'interno della classe che la possiede e di ogni sua sottoclasse.
### Associazioni in UML
Una **associazione** (o relazione) tra una classe *C1* ed una classe *C2* modella una relazione matematica tra l'insieme delle istanze di *C1* e l'insieme delle istanze di *C2*. Gli attributi modellano proprietà locali di una classe, le associazioni modellano proprietà che coinvolgono altre classi.
Alcune volte è interessante specificare un **verso** per il nome della associazione. Il verso non è una caratteristica del significato dell'associazione, ma dice semplicemente che il nome scelto evoca un verso.
#### Ruoli
È possibile aggiungere alla associazione una informazione che specifica il **ruolo** che una classe gioca nella associazione. Analogamente al verso, il ruolo è generalmente opzionale. L'unico caso in cui **il ruolo è obbligatorio è quello in cui l'associazione insiste più volte sulla stessa classe**, e rappresenta una relazione non simmetrica (es. `Persona` con ruoli `-Genitore` e `-figlio`).
#### Molteplicità in UML
Per specificare con maggiore precisione il significato delle associazioni binarie si possono definire i vincoli di **molteplicità** delle associazioni. La notazione è `x..y` dove x è il minimo e y il massimo. Ogni istanza di Class1 è legata ad almeno x e al massimo y istanze di Class2.
#### Associazioni N-arie
Una associazione può essere definita su tre o più classi. In tale caso **l'associazione si dice n-aria**, e modella una relazione matematica tra n insiemi.
### Aggregazione e Composizione
In UML le relazioni "tutto-parte" si specificano in due modi:
- **Aggregazione** (rombo vuoto): le parti possono esistere in modo indipendente dal tutto. Si utilizza il termine *tutto-parte*.
- **Composizione** (rombo pieno): le parti **non possono esistere** senza la parte "tutto" (es. se il `documento` viene distrutto, si distruggono anche `frontespizio`, `paragrafo` e `indice`).
