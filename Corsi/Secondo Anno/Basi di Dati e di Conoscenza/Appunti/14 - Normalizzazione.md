## Normalizzazione

La **normalizzazione** è una formalizzazione teorica dei problemi che possono emergere durante l'utilizzo, l'interrogazione e la gestione dei dati in un database, e che possono impedire o rendere complicato l'uso delle informazioni. Non sempre è applicabile, ma permette di costruire un DB corretto e ben definito.

In sostanza è un procedimento utile per l'**eliminazione della ridondanza** delle informazioni e per ridurre il rischio di inconsistenza della base di dati. Di fatto riduce la dimensione delle relazioni a partire da relazioni con concetti tra loro indipendenti.

La normalizzazione dei dati può essere considerata come un processo di analisi degli schemi forniti, basato sulle loro dipendenze funzionali e chiavi primarie, per raggiungere le proprietà desiderate di:

1. **Minimizzazione della ridondanza**
2. **Minimizzazione delle anomalie di inserimento, cancellazione, modifica**

## Qualità di uno schema relazionale

### Linee guida

Un buon schema relazionale segue alcune linee guida fondamentali:

- **Linea guida 1**: ogni tupla in una relazione dovrebbe rappresentare un'entità o un'istanza di relazione. Gli attributi di entità diverse (dipendenti, dipartimenti, progetti) **non dovrebbero essere mescolati** nella stessa relazione. Per riferirsi ad altre entità dovrebbero essere usate solo le chiavi esterne. Gli attributi di entità e di relazioni diverse dovrebbero essere tenuti il più possibile separati.
- **Linea guida 2**: progettare uno schema che non risenta delle anomalie di inserimento, cancellazione e aggiornamento.
- **Linea guida 3**: le relazioni dovrebbero essere progettate in modo tale che le loro tuple abbiano il minor numero possibile di valori `NULL`. Gli attributi spesso `NULL` potrebbero essere collocati in relazioni separate (con la chiave primaria).
- **Linea guida 4**: le relazioni dovrebbero essere progettate per soddisfare la condizione di **lossless join** (decomposizione senza perdita). Non si dovrebbero creare tuple spurie facendo un natural join di tutte le relazioni.

## Anomalie di uno schema

Mescolare attributi di più entità nella stessa relazione causa **ridondanza** e tre tipi di **anomalie di aggiornamento**.

> [!example] Schema con anomalie — EMP_PROJ
> Consideriamo la relazione:
>
> `EMP_PROJ(Emp#, Proj#, Ename, Pname, No_hours)`
>
> In questa relazione sono mescolati dati degli impiegati, dei progetti e della partecipazione ai progetti.

> [!quote] Definizione — Anomalia di inserimento
> Impossibilità di inserire un fatto senza che esista un altro fatto correlato. In `EMP_PROJ`: non è possibile inserire un progetto a meno che non abbia un dipendente assegnato, e viceversa non è possibile inserire un dipendente a meno che non sia assegnato a un progetto.

> [!quote] Definizione — Anomalia di cancellazione
> La cancellazione di un fatto provoca la perdita involontaria di un altro fatto correlato. In `EMP_PROJ`: quando un progetto viene eliminato, ciò comporta l'eliminazione di tutti i dipendenti che lavorano su quel progetto; se un dipendente è l'unico su un progetto, la sua eliminazione comporta la scomparsa del progetto.

> [!quote] Definizione — Anomalia di aggiornamento (modifica)
> La modifica di un valore richiede l'aggiornamento di molte righe, con rischio di inconsistenza. In `EMP_PROJ`: la modifica del nome del progetto P1 da "Fatturazione" a "Customer-Accounting" può richiedere l'aggiornamento di tutte le 100 righe dei dipendenti che lavorano al progetto P1.

### Esempio con anomalie (da Atzeni)

Si consideri la relazione (la chiave è composta da {Impiegato, Progetto}):

`Impiegati_Progetti(<u>Impiegato</u>, Stipendio, <u>Progetto</u>, Bilancio, Funzione)`

| **Impiegato** | Stipendio | **Progetto** | Bilancio | Funzione    |
|---------------|-----------|--------------|----------|-------------|
| Rossi         | 20        | Marte        | 2        | tecnico     |
| Verdi         | 35        | Giove        | 15       | progettista |
| Verdi         | 35        | Venere       | 15       | progettista |
| Neri          | 55        | Venere       | 15       | direttore   |
| Neri          | 55        | Giove        | 15       | consulente  |
| Neri          | 55        | Marte        | 2        | consulente  |
| Mori          | 48        | Marte        | 2        | direttore   |
| Mori          | 48        | Venere       | 15       | progettista |
| Bianchi       | 48        | Venere       | 15       | progettista |
| Bianchi       | 48        | Giove        | 15       | direttore   |

Le anomalie sono legate alle dipendenze funzionali $\text{Impiegato} \to \text{Stipendio}$ e $\text{Progetto} \to \text{Bilancio}$, che non corrispondono alla chiave e causano ridondanza. La dipendenza $\text{Impiegato, Progetto} \to \text{Funzione}$ invece corrisponde alla chiave e non causa anomalie.

## Dipendenze Funzionali

### Definizione formale

Le **dipendenze funzionali** (DF, o FD dall'inglese *Functional Dependencies*) sono usate per specificare misure formali della "bontà" dei progetti relazionali. Le FD e le chiavi sono usate per definire le **forme normali**. Le FD sono vincoli che derivano dal significato e dalle interrelazioni degli attributi dei dati.

> [!quote] Definizione — Dipendenza funzionale
> Sia $R(U)$ uno schema di relazione con $U$ insieme di attributi. Una **dipendenza funzionale** $X \to Y$, con $X \subseteq U$ e $Y \subseteq U$, è un vincolo che deve valere su ogni istanza $r$ di $R(U)$: per ogni coppia di tuple $t_1, t_2 \in r$, se $t_1[X] = t_2[X]$ allora $t_1[Y] = t_2[Y]$.
>
> Si dice che $X$ **determina funzionalmente** $Y$, o che $Y$ **dipende funzionalmente** da $X$. $X$ è detto **determinante** per $Y$.

In altre parole: un insieme di attributi $X$ determina funzionalmente un insieme $Y$ se il valore di $X$ determina un valore univoco per $Y$.

> [!info] Chiave e dipendenze funzionali
> Se $K$ è una chiave di $R$, allora $K$ determina funzionalmente tutti gli attributi in $R$ (poiché non abbiamo mai due tuple distinte con $t_1[K] = t_2[K]$). Viceversa, **un attributo che determina tutti gli altri attributi è una chiave candidata**.

Una FD è una **proprietà degli attributi** nello schema $R$: il vincolo deve valere su ogni istanza della relazione $r(R)$, non solo sull'istanza attuale.

> [!example] Dipendenze funzionali — schema Impiegati_Progetti
> Le proprietà del mondo reale modellato:
> - Ogni impiegato ha un solo stipendio (anche se partecipa a più progetti): $\text{Impiegato} \to \text{Stipendio}$
> - Ogni progetto ha un bilancio: $\text{Progetto} \to \text{Bilancio}$
> - Ogni impiegato in ciascun progetto ha una sola funzione (ma può avere funzioni diverse in progetti diversi): $\text{Impiegato, Progetto} \to \text{Funzione}$

### Dipendenze banali e non banali

> [!quote] Definizione — Dipendenza banale
> Una FD $X \to Y$ è **banale** se $Y \subseteq X$ (il secondo membro è sottoinsieme del primo). Ad esempio, $\text{Impiegato, Progetto} \to \text{Progetto}$ è banale: è sempre soddisfatta e non porta informazione.

- $Y \to A$ è **non banale** se $A \notin Y$
- $Y \to Z$ è **non banale** se nessun attributo in $Z$ appartiene a $Y$

### Dipendenze parziali e complete

> [!quote] Definizione — Dipendenza completa
> Una FD $X \to Y$ è **completa** (o dipendenza funzionale completa) se non esiste alcun sottoinsieme proprio $Z \subset X$ tale che $Z \to Y$. In altre parole, $Y$ dipende dall'*intera* chiave $X$, non da una sua parte.

> [!quote] Definizione — Dipendenza parziale
> Una FD $X \to Y$ è **parziale** se esiste un sottoinsieme proprio $Z \subset X$ tale che $Z \to Y$. L'attributo $Y$ dipende solo da *parte* della chiave.

> [!example] Dipendenza parziale in EMP_PROJ
> In `EMP_PROJ(<u>SSN</u>, <u>PNUMBER</u>, HOURS, ENAME, PNAME, PLOCATION)`:
> - $\{\text{SSN}, \text{PNUMBER}\} \to \text{HOURS}$ — dipendenza **completa** (la chiave intera serve)
> - $\text{SSN} \to \text{ENAME}$ — dipendenza **parziale** (dipende solo da parte della chiave)
> - $\text{PNUMBER} \to \{\text{PNAME, PLOCATION}\}$ — dipendenza **parziale**

### Dipendenza transitiva

> [!quote] Definizione — Dipendenza transitiva
> Si ha **dipendenza transitiva** quando $A \to B$ e $B \to C$, con $B$ non chiave. Si dice allora che $C$ dipende transitivamente da $A$ (tramite $B$).

> [!example] Dipendenza transitiva
> In `R(Impiegato, Categoria, Stipendio)`:
> - $\text{Impiegato} \to \text{Categoria}$
> - $\text{Categoria} \to \text{Stipendio}$
>
> Quindi $\text{Stipendio}$ dipende transitivamente da $\text{Impiegato}$ tramite $\text{Categoria}$.

## Assiomi di Armstrong e regole derivate

Per ragionare sulle dipendenze funzionali si usa un sistema di inferenza completo e corretto: gli **assiomi di Armstrong**.

### Assiomi fondamentali

Sia $R(U)$ uno schema e $F$ un insieme di FD su $U$. Per ogni $X, Y, Z, W \subseteq U$:

> [!quote] Definizione — Riflessività (Reflexivity)
> Se $Y \subseteq X$, allora $X \to Y$.
>
> (Ogni insieme di attributi determina i propri sottoinsiemi; genera le dipendenze banali.)

> [!quote] Definizione — Arricchimento / Aumento (Augmentation)
> Se $X \to Y$, allora $XZ \to YZ$ per ogni $Z \subseteq U$.
>
> (Aggiungere gli stessi attributi a entrambi i lati preserva la dipendenza.)

> [!quote] Definizione — Transitività (Transitivity)
> Se $X \to Y$ e $Y \to Z$, allora $X \to Z$.

### Regole derivate

Le seguenti regole si dimostrano a partire dagli assiomi e sono utili nella pratica:

> [!info] Unione (Union)
> Se $X \to Y$ e $X \to Z$, allora $X \to YZ$.

> [!info] Decomposizione (Decomposition)
> Se $X \to YZ$, allora $X \to Y$ e $X \to Z$.

> [!info] Pseudotransitività (Pseudotransitivity)
> Se $X \to Y$ e $YZ \to W$, allora $XZ \to W$.

> [!example] Applicazione degli assiomi
> Sia $F = \{A \to B,\ B \to C\}$.
> - Per transitività: $A \to C$
> - Per unione con $A \to B$ e $A \to C$: $A \to BC$

## Chiusura di un insieme di dipendenze ($F^+$) e di attributi ($X^+$)

### Chiusura di $F$

> [!quote] Definizione — Chiusura di $F$
> Dato un insieme $F$ di dipendenze funzionali, la **chiusura** $F^+$ è l'insieme di tutte le FD che possono essere derivate da $F$ applicando ripetutamente gli assiomi di Armstrong:
> $$F^+ = \{ X \to Y \mid F \text{ implica } X \to Y \}$$

Un insieme $F$ di FD **implica** un'altra FD $f$ se ogni relazione che soddisfa tutte le FD in $F$ soddisfa anche $f$.

### Chiusura di un insieme di attributi ($X^+$)

> [!quote] Definizione — Chiusura di $X$ rispetto a $F$
> Dati uno schema $R(U)$, un insieme $F$ di FD su $U$ e un insieme di attributi $X \subseteq U$, la **chiusura** di $X$ rispetto a $F$, indicata con $X^+_F$ (o semplicemente $X^+$), è l'insieme degli attributi che dipendono funzionalmente da $X$ rispetto a $F$:
> $$X^+_F = \{ A \mid A \in U \text{ e } F \text{ implica } X \to A \}$$
>
> Se $A \in X^+_F$, allora $F$ implica $X \to A$.

### Algoritmo di calcolo di $X^+$

```
Input:  insieme X di attributi, insieme F di dipendenze funzionali
Output: X_P (= X^+_F)

1. Inizializza X_P := X
2. Ripeti:
       Per ogni FD (Y -> A) in F:
           Se Y ⊆ X_P e A ∉ X_P:
               X_P := X_P ∪ {A}
3. Fino a quando X_P non cambia più
4. Restituisci X_P
```

> [!example] Calcolo di $X^+$
> Schema $R(\text{A, B, C, D, E})$ con $F = \{A \to B,\ B \to C,\ C \to D\}$. Calcolare $\{A\}^+$:
> - Inizio: $X_P = \{A\}$
> - $A \to B$: $B \subseteq \{A\}$? No. $A \in X_P$? Sì. Aggiungo $B$: $X_P = \{A, B\}$
> - $B \to C$: $B \in X_P$? Sì. Aggiungo $C$: $X_P = \{A, B, C\}$
> - $C \to D$: $C \in X_P$? Sì. Aggiungo $D$: $X_P = \{A, B, C, D\}$
> - Nessun nuovo attributo aggiungibile.
>
> Risultato: $\{A\}^+ = \{A, B, C, D\}$

### Chiusura e chiavi

Un insieme di attributi $K$ è **superchiave** per $R(U)$ con insieme di FD $F$ se $F$ implica $K \to U$, cioè se $K^+ = U$. È **chiave candidata** se è una superchiave minimale (nessun suo sottoinsieme proprio è superchiave). L'algoritmo di calcolo di $X^+$ può essere usato direttamente per verificare se un insieme di attributi è chiave.

## Copertura e copertura minima (ridotta)

### Copertura

> [!quote] Definizione — Copertura
> Due insiemi di dipendenze funzionali $F_1$ e $F_2$ sono **equivalenti** se $F_1$ implica ogni dipendenza in $F_2$ e viceversa ($F_1^+ = F_2^+$). In tal caso diciamo che ognuno è una **copertura** dell'altro.

Questa proprietà consente di utilizzare, dato un insieme di dipendenze, un altro a esso equivalente ma più semplice.

### Proprietà desiderabili

Un insieme di dipendenze $F$ è:
- **Non ridondante**: non esiste dipendenza $f \in F$ tale che $F - \{f\}$ implica $f$.
- **Ridotto** (o **canonico** o **minimale**): è non ridondante e non esiste un insieme $F'$ equivalente a $F$ ottenuto eliminando attributi dai primi membri di una o più dipendenze.

> [!example] Ridondanza e riduzione
> - $F_1 = \{A \to B;\ AB \to C;\ A \to C\}$ — ridondante (equivalente a $F_2$)
> - $F_2 = \{A \to B;\ AB \to C\}$ — non ridondante ma non ridotto (B nel primo membro è eliminabile)
> - $F_3 = \{A \to B;\ A \to C\}$ — ridotto

### Calcolo della copertura ridotta

```
1. Sostituire l'insieme dato con quello equivalente che ha tutti i secondi
   membri costituiti da singoli attributi (per decomposizione)
2. Eliminare le dipendenze ridondanti
3. Per ogni dipendenza X -> A, verificare se esistono attributi eliminabili
   dal primo membro (cioè se esiste Y ⊂ X tale che F è equivalente
   a F - {X -> A} ∪ {Y -> A})
```

## Attributi primi e non primi

> [!quote] Definizione — Attributo primo
> Sia $R(U)$ una relazione. Un attributo $A \in U$ si dice **attributo primo** se appartiene ad almeno una **chiave candidata** della relazione. Gli attributi che non appartengono ad alcuna chiave candidata sono detti **attributi non primi**.

> [!info] Osservazione
> Se un attributo compare anche in una sola chiave candidata, allora è considerato primo, anche se non appartiene a tutte le chiavi della relazione.

> [!example] Attributi primi e non primi
> Sia $R(\text{Matricola, CodCorso, NomeStudente, NomeCorso, Voto})$ con unica chiave candidata $\{\text{Matricola, CodCorso}\}$.
>
> - **Attributi primi**: Matricola, CodCorso (appartengono alla chiave)
> - **Attributi non primi**: NomeStudente, NomeCorso, Voto

## Forme Normali

Le forme normali sono proprietà degli schemi di relazione che garantiscono l'assenza di certi tipi di anomalie. Ogni forma normale è strettamente più forte della precedente: BCNF implica 3NF, 3NF implica 2NF, 2NF implica 1NF.

### Prima Forma Normale (1NF)

> [!quote] Definizione — Prima Forma Normale (1NF)
> Uno schema di relazione $R(X)$ è in **1NF** se ogni attributo appartenente a $X$ è un **attributo semplice** (atomico): il suo valore è unico e indivisibile in una ennupla. Non sono ammessi attributi multivalore o gruppi ripetuti.

La 1NF è una condizione di base del modello relazionale: tutte le relazioni del modello relazionale sono in 1NF per definizione.

> [!example] Violazione della 1NF — attributo multivalore
> La tabella seguente non è in 1NF perché l'attributo "Figli a carico" contiene più valori:
>
> | **Codice** | Cognome | Nome  | Data Nascita | Figli a carico |
> |------------|---------|-------|--------------|----------------|
> | 001        | Rossi   | Mario | 01/01/1978   | Luca Serena    |
> | 002        | Verdi   | Luca  | 02/04/1959   | Marzia Ilaria  |
>
> **Decomposizione in 1NF** — si separa la tabella in due:
>
> | **Codice** | Cognome | Nome  | Data Nascita |
> |------------|---------|-------|--------------|
> | 001        | Rossi   | Mario | 01/01/1978   |
> | 002        | Verdi   | Luca  | 02/04/1959   |
>
> | **Codice** | **Cod. Figlio** | Nome   |
> |------------|-----------------|--------|
> | 001        | 01              | Luca   |
> | 001        | 02              | Serena |
> | 002        | 01              | Marzia |
> | 002        | 02              | Ilaria |

### Decomposizione rispetto a una FD

Sia $R(U)$ una relazione e $X \to Y$ una dipendenza funzionale, con $X \subseteq U$ e $Y \subseteq U$. La **decomposizione** di $R(U)$ rispetto a $X \to Y$ consiste nella sostituzione di $R(U)$ con due relazioni:

1. $R_1(X \cup Y)$ — contiene gli attributi necessari a rappresentare la FD
2. $R_2(U - (Y - X))$ — contiene gli attributi rimanenti, mantenendo $X$ per garantire il collegamento

### Seconda Forma Normale (2NF)

> [!quote] Definizione — Seconda Forma Normale (2NF)
> Uno schema di relazione $R(X)$ è in **2NF** se è in 1NF e se ogni **attributo non primo** (non facente parte di alcuna chiave) di $R(X)$ dipende funzionalmente e **completamente** da ogni chiave di $R(X)$.
>
> In altre parole: non devono esistere **dipendenze parziali** degli attributi non primi dalla chiave.

> [!example] Violazione della 2NF — schema Inventario
> La relazione:
>
> `Inventario(<u>CodArticolo</u>, <u>CodMagazzino</u>, DescArticoli, Quantità, IndirizzoMagazzino)`
>
> Non è in 2NF perché:
> - $\text{CodArticolo} \to \text{DescArticoli}$ — dipendenza parziale dalla chiave
> - $\text{CodMagazzino} \to \text{IndirizzoMagazzino}$ — dipendenza parziale dalla chiave
> - Solo $\{\text{CodArticolo, CodMagazzino}\} \to \text{Quantità}$ è una dipendenza completa
>
> **Decomposizione in 2NF**:
>
> `Inventario(<u>CodArticolo</u>, <u>CodMagazzino</u>, Quantità)`
>
> `Articoli(<u>CodArticolo</u>, DescArticoli)`
>
> `Magazzino(<u>CodMagazzino</u>, IndirizzoMagazzino)`

### Terza Forma Normale (3NF)

> [!quote] Definizione — Terza Forma Normale (3NF) — versione classica
> Uno schema di relazione $R(X)$ è in **3NF** se è in 1NF e se ogni **attributo non primo** di $R(X)$ è dipendente in modo **non transitivo** da ogni chiave di $R(X)$.
>
> Non devono esistere **dipendenze transitive** tra attributi non chiave.

> [!quote] Definizione — Terza Forma Normale (3NF) — versione alternativa (Atzeni)
> Una relazione $r$ è in **terza forma normale** se, per ogni FD non banale $X \to Y$ definita su $r$, è verificata almeno una delle seguenti condizioni:
> - $X$ contiene una chiave $K$ di $r$ (cioè $X$ è superchiave)
> - ogni attributo in $Y$ è contenuto in almeno una chiave di $r$ (tutti gli attributi in $Y$ sono **primi**)

> [!example] Violazione della 3NF — dipendenza transitiva
> La relazione:
>
> `Impiegati(<u>CodImpiegato</u>, Nome, Reparto, TelefonoReparto)`
>
> ha le dipendenze:
> - $\text{CodImpiegato} \to \text{Reparto}$
> - $\text{Reparto} \to \text{TelefonoReparto}$
>
> Quindi $\text{TelefonoReparto}$ dipende transitivamente da $\text{CodImpiegato}$ tramite $\text{Reparto}$. Questo causa:
> - ridondanza: il telefono del reparto è ripetuto per ogni impiegato di quel reparto
> - anomalia di aggiornamento: se il telefono cambia, occorre modificare molte righe
> - anomalia di inserimento: se un reparto non ha impiegati, non se ne può conoscere il telefono
>
> **Decomposizione in 3NF**:
>
> `Impiegati(<u>CodImpiegato</u>, Nome, Reparto)`
>
> `Reparto(<u>Reparto</u>, TelefonoReparto)`

### Forma Normale di Boyce-Codd (BCNF)

> [!quote] Definizione — BCNF
> Una relazione è in **forma normale di Boyce-Codd (BCNF)** se è in 1NF e se, ogni volta che vale la FD $X \to A$ in $R$ (con $A \notin X$), allora $X$ è una **superchiave** di $R$.
>
> Equivalentemente: ogni determinante (ogni lato sinistro di una FD non banale) deve essere una superchiave.

La BCNF è una forma normale **più forte** della 3NF: ogni relazione in BCNF è anche in 3NF, ma non viceversa. La differenza emerge quando esistono più chiavi candidate che si sovrappongono.

### BCNF vs 3NF

Il vantaggio della 3NF rispetto alla BCNF è che la 3NF è **sempre raggiungibile** senza perdita di informazioni e senza perdita di dipendenze funzionali. Non è così per la BCNF: esistono relazioni che non possono essere normalizzate in BCNF senza perdere qualche dipendenza funzionale.

Regola pratica: **se una relazione ha una sola chiave candidata, allora essa è in BCNF se e solo se è in 3NF**.

> [!example] Relazione in 3NF ma non in BCNF — TEACH
> La relazione:
>
> `TEACH(Student, Course, Instructor)`
>
> con le dipendenze funzionali:
> - $\{\text{Student, Course}\} \to \text{Instructor}$
> - $\{\text{Student, Instructor}\} \to \text{Course}$
> - $\text{Instructor} \to \text{Course}$
>
> Le chiavi candidate sono $\{\text{Student, Course}\}$ e $\{\text{Student, Instructor}\}$. Tutti e tre gli attributi sono **primi**. La terza FD ($\text{Instructor} \to \text{Course}$) non viola la 3NF (perché $\text{Course}$ è primo), ma viola la BCNF (perché $\text{Instructor}$ non è superchiave).

| Student  | Course            | Instructor |
|----------|-------------------|------------|
| Narayan  | Database          | Mark       |
| Smith    | Database          | Navathe    |
| Smith    | Operating Systems | Ammar      |
| Smith    | Theory            | Schulman   |
| Wallace  | Database          | Mark       |
| Wallace  | Operating Systems | Ahamad     |
| Wong     | Database          | Omiecinski |
| Zelaya   | Database          | Navathe    |

## Riepilogo delle forme normali

| Forma Normale | Elimina                      | Requisiti                                              |
|---------------|------------------------------|--------------------------------------------------------|
| **1NF**       | Valori multipli in una cella | Atomicità degli attributi                              |
| **2NF**       | Dipendenze parziali          | 1NF + tutte le DF complete dalla chiave                |
| **3NF**       | Dipendenze transitive        | 2NF + ogni attributo non chiave dipende solo da chiavi |
| **BCNF**      | Violazioni della chiave      | Ogni LHS di una DF è superchiave                       |
| **4NF**       | MVD non banali               | BCNF + nessuna MVD non banale tranne da superchiavi    |
| **5NF**       | Join dependency              | 4NF + ogni JD è implicata da chiavi candidate          |

## Forme normali avanzate: 4NF e 5NF

La quarta e la quinta forma normale risolvono i problemi che si possono creare quando nella relazione sono presenti **attributi multivalore**, cioè attributi che possono assumere più valori in corrispondenza dello stesso valore di un altro attributo.

### Dipendenze multivalore (MVD)

> [!quote] Definizione — Dipendenza multivalore
> Una **dipendenza multivalore** (MVD) $X \twoheadrightarrow Y$ su uno schema $R(U)$ vale su un'istanza $r$ se, per ogni coppia di tuple $t_1, t_2 \in r$ con $t_1[X] = t_2[X]$, esiste una tupla $t_3 \in r$ tale che $t_3[X] = t_1[X]$, $t_3[Y] = t_1[Y]$ e $t_3[U - X - Y] = t_2[U - X - Y]$.
>
> Significa: per ogni valore di $X$, esiste un insieme indipendente di valori di $Y$ (indipendente dagli altri attributi).

> [!example] MVD — R(Student, Course, Hobby)
> Uno studente può seguire più corsi e avere più hobby, e le due cose sono indipendenti tra loro:
>
> | Student | Course | Hobby   |
> |---------|--------|---------|
> | Alice   | Math   | Tennis  |
> | Alice   | CS     | Tennis  |
> | Alice   | Math   | Reading |
> | Alice   | CS     | Reading |
>
> Le MVD sono:
> - $\text{Student} \twoheadrightarrow \text{Course}$
> - $\text{Student} \twoheadrightarrow \text{Hobby}$
>
> Le righe sono il prodotto cartesiano dei due insiemi dipendenti: {Math, CS} e {Tennis, Reading}.

### Quarta Forma Normale (4NF)

> [!quote] Definizione — 4NF
> Uno schema è in **4NF** se:
> - è in BCNF
> - e per ogni MVD non banale $X \twoheadrightarrow Y$, vale che $X$ è una **superchiave**

> [!example] Decomposizione in 4NF
> In $R(\text{Student, Course, Hobby})$ c'è indipendenza tra Course e Hobby, quindi viola la 4NF ($\text{Student}$ non è superchiave). La decomposizione in 4NF è:
>
> `R1(Student, Course)`
>
> `R2(Student, Hobby)`

### Dipendenze di join (JD) e Quinta Forma Normale (5NF)

> [!quote] Definizione — Join Dependency
> Una **dipendenza di join** (JD) $JD(R_1, R_2, \ldots, R_n)$ su uno schema $R$ afferma che $R$ è ricostruibile come join naturale di $R_1, R_2, \ldots, R_n$ senza perdita.

> [!quote] Definizione — 5NF (o PJNF)
> Uno schema è in **5NF** (Project-Join Normal Form) se:
> - è in 4NF
> - e ogni JD è implicata da una delle chiavi candidate

> [!example] Decomposizione in 5NF
> Schema $R(\text{Supplier, Part, Project})$: un fornitore può fornire parti a progetti, ma i dati sono noti solo in combinazioni parziali. Tutte le proiezioni sono corrette ma l'unione può generare tuple spurie. La decomposizione in 5NF è:
>
> `R1(Supplier, Part)` — `R2(Supplier, Project)` — `R3(Part, Project)`

## Normalizzazione per decomposizione

### Proprietà di una buona decomposizione

Una decomposizione dovrebbe sempre soddisfare due proprietà fondamentali:

> [!quote] Definizione — Decomposizione senza perdita (Lossless Join)
> Una relazione $r$ si **decompone senza perdita** su $X_1$ e $X_2$ se il join naturale delle proiezioni di $r$ su $X_1$ e $X_2$ è uguale a $r$ stessa (cioè non contiene tuple spurie):
> $$\pi_{X_1}(r) \bowtie \pi_{X_2}(r) = r$$
>
> La decomposizione senza perdita è garantita se gli attributi comuni $X_1 \cap X_2$ contengono una **chiave** per almeno una delle relazioni decomposte.

> [!quote] Definizione — Conservazione delle dipendenze
> Una decomposizione **conserva le dipendenze** se ciascuna delle dipendenze funzionali dello schema originario coinvolge attributi che compaiono tutti insieme in uno degli schemi decomposti. In caso contrario, si perdono vincoli di integrità che non potranno più essere verificati localmente.

> [!example] Decomposizione con perdita di una FD — schema Impiegato, Progetto, Sede
> Sia la relazione:
>
> `ImpProgSede(Impiegato, Progetto, Sede)`
>
> con le FD:
> - $\text{Impiegato} \to \text{Sede}$
> - $\text{Progetto} \to \text{Sede}$
> - $\text{Progetto, Impiegato} \to \text{Progetto, Impiegato, Sede}$ (chiave)
>
> Decomponiamo su $\text{Impiegato} \to \text{Sede}$ e otteniamo:
>
> | Impiegato | Sede   |      | Impiegato | Progetto |
> |-----------|--------|------|-----------|----------|
> | Rossi     | Roma   |      | Rossi     | Marte    |
> | Verdi     | Milano |      | Verdi     | Giove    |
> | Neri      | Milano |      | Verdi     | Venere   |
> |           |        |      | Neri      | Saturno  |
> |           |        |      | Neri      | Venere   |
>
> Il join naturale produce tuple spurie (es. Verdi-Saturno-Milano, Neri-Giove-Milano) e la FD $\text{Progetto} \to \text{Sede}$ è **perduta**: non è più controllabile localmente. Inserendo Neri-Marte, il sistema non può verificare che Marte sia a Roma (come Rossi) e non a Milano (come Neri), portando a una violazione non rilevabile.

### Quando non è possibile raggiungere la BCNF conservando le dipendenze

> [!warning] BCNF e conservazione delle dipendenze
> In alcuni casi la BCNF non è raggiungibile senza perdere dipendenze funzionali. Quando una FD coinvolge tutti gli attributi dello schema (come $\text{Progetto, Sede} \to \text{Dirigente}$ in uno schema con tutti e tre gli attributi), nessuna decomposizione può preservare tale dipendenza. In questi casi ci si accontenta della 3NF.

## Algoritmo di sintesi in 3NF

Il problema formale è: data una relazione $R(U)$ e un insieme di dipendenze $F$ su $U$, generare una decomposizione di $R$ che:
- sia senza perdita e conservi le dipendenze
- contenga solo relazioni normalizzate (in 3NF)

Si fa riferimento alla 3NF perché, a differenza della BCNF, è **sempre raggiungibile** senza perdita di informazioni e senza perdita di dipendenze.

### Algoritmo (sintesi)

```
Input:  schema R(U), insieme di FD F su U
Output: decomposizione in 3NF, senza perdita, con conservazione delle dipendenze

1. Calcolare una copertura ridotta G di F

2. Partizionare G in sottoinsiemi G_i tali che a ogni insieme
   appartengano dipendenze con primi membri aventi la stessa chiusura
   (cioè raggruppare le FD con lo stesso determinante)

3. Costruire un insieme U di sottoinsiemi U_i ⊂ U, uno per ciascuna
   partizione, con tutti gli attributi coinvolti nella partizione

4. Se un elemento di U è propriamente contenuto in un U_i,
   eliminarlo da U

5. Costruire uno schema R_i(U_i) per ciascun U_i ∈ U con associate
   le dipendenze in G i cui attributi sono tutti contenuti in U_i

6. Se nessuno degli U_i è chiave per R(U), calcolare una chiave K
   di R(U) e aggiungere allo schema generato uno schema di relazione
   sugli attributi K (senza dipendenze, per garantire il lossless join)
```

> [!example] Sintesi in 3NF — schema R(MCGRDSPA)
> Schema: $R(\text{M, C, G, R, D, S, P, A})$ con $F = \{M \to RSDG,\ MS \to CD,\ G \to R,\ D \to S,\ S \to D,\ MPD \to AM\}$.
>
> **Passo 1** — copertura ridotta $G$:
> $\{M \to D,\ M \to G,\ M \to C,\ G \to R,\ D \to S,\ S \to D,\ PD \to A\}$
>
> **Passo 2** — partizioni di $G$ per stesso primo membro:
> - $G_1 = \{M \to D;\ M \to G;\ M \to C\}$
> - $G_2 = \{G \to R\}$
> - $G_3 = \{D \to S;\ S \to D\}$
> - $G_4 = \{PD \to A\}$
>
> **Passi 3-5** — schemi generati (senza eliminazioni):
> - $R_1(\text{M, D, G, C})$ con $\{M \to D;\ M \to G;\ M \to C\}$
> - $R_2(\text{G, R})$ con $\{G \to R\}$
> - $R_3(\text{D, S})$ con $\{D \to S;\ S \to D\}$
> - $R_4(\text{P, D, A})$ con $\{PD \to A\}$
>
> **Passo 6**: MP è chiave per $R$, ed è contenuta in $R_4(\text{P, D, A})$ (contiene P ma non M)... Il sistema verifica; in questo caso MP è chiave e PD è in $R_4$: si aggiunge, se necessario, uno schema con la chiave.

## Normalizzazione nella progettazione concettuale

La teoria della normalizzazione può essere usata anche durante la **progettazione concettuale** per verificare la qualità dello schema ER, identificando dipendenze che segnalano entità mescolate o relazioni mal modellate.

> [!example] Entità con dipendenza transitiva — Prodotto
> L'entità Prodotto con attributi (Codice, NomeProdotto, Prezzo, PartitaIVA, NomeFornitore, Indirizzo) viola la forma normale per la dipendenza:
> $\text{PartitaIVA} \to \text{NomeFornitore, Indirizzo}$
>
> Soluzione: separare l'entità Fornitore (con PartitaIVA come identificatore) e collegare tramite una relationship Fornitura.

> [!example] Relationship con dipendenza transitiva — Tesi
> La relationship Tesi(Studente, Professore, CorsoDiLaurea, Dipartimento) con:
> - $\text{Studente} \to \text{CorsoDiLaurea}$
> - $\text{Studente} \to \text{Professore}$
> - $\text{Professore} \to \text{Dipartimento}$
>
> viola la 3NF per $\text{Professore} \to \text{Dipartimento}$ (Dipartimento non è primo). Soluzione: separare la relationship Afferenza(Professore, Dipartimento) e, notando che Studente determina indipendentemente CorsoDiLaurea e Professore, introdurre anche Iscrizione(Studente, CorsoDiLaurea). Si ottiene così il diagramma corretto con quattro entità (Professore, Studente, Dipartimento, Corso di laurea) e tre relationship (Tesi, Afferenza, Iscrizione).
