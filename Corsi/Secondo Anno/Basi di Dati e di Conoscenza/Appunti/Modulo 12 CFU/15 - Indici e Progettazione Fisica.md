## Progettazione fisica

Progettare una base di dati significa definirne struttura, caratteristiche e contenuto, attraverso opportune metodologie. In base al grado di astrazione, la progettazione prevede tre modelli:

- **Modello concettuale**: rappresenta la realtà dei dati e le relazioni tra essi attraverso uno schema (es. diagramma ER)
- **Modello logico**: descrive il modo attraverso il quale i dati sono organizzati negli archivi del calcolatore (es. schema relazionale)
- **Modello fisico**: descrive come i dati sono registrati nelle memorie di massa

Gli utenti interrogano le basi di dati vedendo solo il **modello logico** (relazionale), ma i dati risiedono fisicamente in **memoria secondaria**. Le strutture logiche non sarebbero efficienti se usate direttamente in memoria secondaria: servono **strutture fisiche opportune**. Inoltre la memoria secondaria è molto più lenta della memoria principale, quindi serve un'interazione tra le due che limiti il più possibile gli accessi alla secondaria (esempio tipico: un'interrogazione con un join).

## Organizzazione fisica dei dati

In un DBMS relazionale, i dati sono rappresentati come collezioni di record memorizzati in uno o più file.

> [!info] Organizzazione fisica ed efficienza
> L'organizzazione fisica dei dati all'interno di un file influenza il tempo di accesso alle informazioni: ogni organizzazione fisica rende alcune operazioni efficienti e altre onerose. **Non esiste un'organizzazione fisica dei dati che sia efficiente per qualunque tipo di lettura e scrittura dei dati.**

### Esempio motivante

Si consideri la relazione:

`Dipendente(id, nome, cognome, datanascita, residenza, salario)`

e l'interrogazione:

```sql
select * from Dipendente where residenza = 'Como';
```

**Caso 1 — file non ordinato.** Le operazioni eseguite sono:

1. lettura sequenziale dell'intero file
2. durante la lettura, selezione dei record dei dipendenti con residenza a Como
3. visualizzazione dei record

Questo comporta la scansione completa del file, anche se solo pochi record soddisfano la condizione.

**Caso 2 — file ordinato per residenza.** Se il file `Dipendente` è fisicamente ordinato sull'attributo `residenza`, le operazioni diventano:

1. lettura sequenziale del file fino al primo record con residenza uguale a Como
2. lettura sequenziale di tutti i record con residenza uguale a Como, fino al primo record con residenza diversa da Como
3. visualizzazione dei record

Questa organizzazione è però progettata specificamente per quell'operazione.

> [!info] Vantaggi e svantaggi dell'ordinamento fisico
> **Vantaggi**: si evita la lettura sequenziale di tutto il file.
>
> **Svantaggi**: bisogna mantenere l'ordinamento (operazione costosa ad ogni inserimento/cancellazione), e l'organizzazione non è efficiente per interrogazioni che non coinvolgono l'attributo `residenza`.

## Indici

> [!quote] Definizione — Indice
> Un **indice** è una struttura ausiliaria per l'accesso (efficiente) ai record di un file sulla base dei valori di un campo (o di una concatenazione di campi) detto **chiave** (o più propriamente **pseudochiave**, perché non è necessariamente identificante).

L'idea fondamentale è la stessa dell'**indice analitico di un libro**: una lista di coppie (termine, pagina), ordinata alfabeticamente sui termini, posta in fondo al libro e separabile da esso. Analogamente, un indice `I` di un file `f` è **un altro file**, con record a due campi — chiave e indirizzo (dei record di `f` o dei relativi blocchi) — ordinato secondo i valori della chiave.

### Struttura fisica accessoria

È possibile definire strutture fisiche accessorie (gli indici) che permettano di facilitare l'accesso ai dati senza dover riordinare fisicamente il file principale.

> [!example] Indice sull'attributo residenza
> Per la relazione `Dipendente`, si può realizzare una struttura fisica accessoria sull'attributo `residenza` (campo chiave dell'indice): per ogni valore di `residenza` viene memorizzata la **locazione fisica** dei record corrispondenti.
>
> - la **struttura fisica accessoria** contiene, per ogni valore della chiave, tutte le locazioni fisiche dei record corrispondenti
> - la **locazione fisica** indica la posizione di un record all'interno di un file e permette di accedere direttamente al record d'interesse (alla pagina fisica che lo contiene)

Con l'indice su `residenza`, l'interrogazione `select * from Dipendente where residenza = 'Como'` viene eseguita così:

1. lettura della struttura fisica accessoria per recuperare le locazioni fisiche dei record corrispondenti a `residenza = 'Como'`
2. accesso diretto solo ai record del file associati a `residenza = 'Como'`
3. visualizzazione dei record

> [!info] Vantaggi e svantaggi degli indici
> **Vantaggi**:
> - si evita la lettura sequenziale di tutto il file
> - accesso diretto solo ai record di interesse
> - il costo di mantenimento della struttura accessoria è meno oneroso rispetto al costo di mantenimento del file con struttura ordinata
>
> **Svantaggi**:
> - è necessario spazio supplementare per memorizzare la struttura fisica accessoria
> - possono essere necessarie più strutture accessorie per più attributi o combinazioni di attributi (un indice è relativo solo a un attributo, o a una concatenazione di attributi specifica)

### Strutture fisiche per la realizzazione degli indici

Gli indici sono le strutture fisiche accessorie offerte dai DBMS per migliorare l'efficienza delle operazioni di accesso ai dati. Possono essere realizzati mediante:

- **Alberi** (es. B-tree, B+-tree)
- **Hash table**

## Definizione degli indici in SQL

La sintassi per la definizione degli indici non è standard, ma è presente in forma simile nei vari DBMS:

```sql
create [unique] index IndexName on TableName(AttributeList)
drop index IndexName
```

L'opzione `unique` impone che i valori della chiave dell'indice siano distinti.

## Esecuzione e ottimizzazione delle interrogazioni

Il **query processor** (o **ottimizzatore**) è il modulo del DBMS responsabile di tradurre un'interrogazione SQL in un piano di esecuzione efficiente. È più importante nei sistemi relazionali attuali che in quelli "vecchi" (gerarchici e reticolari), perché:

- le interrogazioni sono espresse ad alto livello (concetto di **indipendenza dei dati**): insiemi di tuple, con poca proceduralità
- l'**ottimizzatore** sceglie la strategia realizzativa (di solito fra diverse alternative), a partire dall'istruzione SQL

### Il processo di esecuzione delle interrogazioni

Il processo si articola in tre fasi, con il supporto del **catalogo** del DBMS:

1. **Analisi lessicale, sintattica e semantica**: l'istruzione SQL viene analizzata usando le informazioni sullo schema contenute nel catalogo, e tradotta in un'espressione di algebra relazionale
2. **Ottimizzazione algebrica**: l'espressione algebrica viene riscritta in una forma equivalente ma meno costosa
3. **Ottimizzazione basata sui costi**: usando i profili delle relazioni e le informazioni sulle dipendenze presenti nel catalogo, si produce il **piano di accesso** finale

> [!info] Nota
> L'ottimizzazione agisce a tempo di compilazione (non a runtime).

### Profili delle relazioni

Il catalogo mantiene informazioni quantitative sulle relazioni, dette **profili**:

- cardinalità di ciascuna relazione
- dimensioni delle tuple
- dimensioni dei valori
- numero di valori distinti degli attributi
- valore minimo e massimo di ciascun attributo

Queste informazioni sono memorizzate nel catalogo e aggiornate con comandi del tipo `update statistics`. Vengono utilizzate nella fase finale dell'ottimizzazione per stimare le dimensioni dei risultati intermedi.

### Ottimizzazione algebrica

Il termine "ottimizzazione" è improprio (anche se efficace), perché il processo utilizza **euristiche**, non garantisce necessariamente il piano ottimo in senso assoluto.

Si basa sulla nozione di **equivalenza**: due espressioni sono equivalenti se producono lo stesso risultato qualunque sia l'istanza attuale della base di dati. I DBMS cercano di eseguire espressioni equivalenti a quelle date, ma meno "costose".

> [!quote] Euristica fondamentale
> Eseguire selezioni e proiezioni il più presto possibile, per ridurre le dimensioni dei risultati intermedi:
> - **"push selections down"**
> - **"push projections down"**

> [!example] Push selections down
> Assumendo A attributo di $R_2$:
> $$\text{SEL}_{A=10}(R_1 \Join R_2) = R_1 \Join \text{SEL}_{A=10}(R_2)$$
>
> Anticipare la selezione prima del join riduce in modo significativo la dimensione del risultato intermedio (e quindi il costo dell'operazione).

Questa equivalenza può essere rappresentata tramite **alberi di interrogazione**: l'albero con la selezione applicata subito su $R_2$ (prima del join) è preferibile rispetto a quello con la selezione applicata dopo il join su tutto $R_1 \Join R_2$.

### Procedura euristica di ottimizzazione

1. Decomporre le selezioni congiuntive in successive selezioni atomiche
2. Anticipare il più possibile le selezioni
3. In una sequenza di selezioni, anticipare le più selettive
4. Combinare prodotti cartesiani e selezioni per formare join
5. Anticipare il più possibile le proiezioni (anche introducendone di nuove)

> [!example] Applicazione della procedura euristica
> Siano $R_1(ABC)$, $R_2(DEF)$, $R_3(GHI)$ e l'interrogazione:
>
> ```sql
> SELECT   A, E
> FROM     R1, R2, R3
> WHERE    C=D AND B>100 AND F=G AND H=7 AND I>2
> ```
>
> La traduzione diretta in algebra relazionale è:
> $$\text{PROJ}_{AE}\big(\text{SEL}_{C=D \,\wedge\, B>100 \,\wedge\, F=G \,\wedge\, H=7 \,\wedge\, I>2}\big((R_1 \Join R_2) \Join R_3)\big)$$
>
> Applicando le euristiche (decomposizione delle selezioni, anticipazione di selezioni e join per attributi comuni) diventa:
> $$\text{PROJ}_{AE}\Big(\big(\text{SEL}_{B>100}(R_1) \Join_{C=D} R_2\big) \Join_{F=G} \text{SEL}_{I>2}\big(\text{SEL}_{H=7}(R_3)\big)\Big)$$
>
> Anticipando anche le proiezioni si ottiene una forma ancora più ottimizzata:
> $$\text{PROJ}_{AE}\Big(\text{PROJ}_{AEF}\big((\text{PROJ}_{AC}(\text{SEL}_{B>100}(R_1))) \Join_{C=D} R_2\big) \Join_{F=G} \text{PROJ}_G\big(\text{SEL}_{I>2}(\text{SEL}_{H=7}(R_3))\big)\Big)$$

### Join

Il **join** è l'operazione più costosa dell'algebra relazionale. I metodi più noti per calcolarlo sono:

- **nested-loop**
- **merge-scan**
- **hash-based**

### Il processo di ottimizzazione basata sui costi

Nella fase finale, si costruisce un **albero di decisione** con le varie alternative (i **piani di esecuzione**), si valuta il costo di ciascun piano e si sceglie il piano di costo minore.

> [!info] Nota
> L'ottimizzatore trova di solito una "buona" soluzione, non necessariamente l'ottimo in senso assoluto.

## Progettazione fisica

La progettazione fisica è la **fase finale** del processo di progettazione di basi di dati.

- **Input**: lo schema logico e informazioni sul carico applicativo
- **Output**: lo schema fisico, costituito dalla definizione delle relazioni con le relative strutture fisiche (e molti parametri, spesso legati allo specifico DBMS)

### Progettazione fisica nel modello relazionale

La caratteristica comune dei DBMS relazionali è la disponibilità degli indici: la progettazione fisica spesso coincide con la **scelta degli indici** (oltre ai parametri strettamente dipendenti dal DBMS).

- le **chiavi primarie** delle relazioni sono di solito coinvolte in selezioni e join: molti sistemi prevedono (oppure suggeriscono) di definire indici sulle chiavi primarie
- altri indici vengono definiti con riferimento ad altre selezioni o join "importanti"
- se le prestazioni sono insoddisfacenti, si "tara" il sistema aggiungendo o eliminando indici
- è utile verificare se e come gli indici sono utilizzati con il comando SQL `show plan`
