## Tecnologia delle basi di dati: perché studiarla

I DBMS offrono i loro servizi in modo "trasparente": finora abbiamo potuto ignorare molti aspetti realizzativi, considerando il DBMS come una "scatola nera". Aprire la scatola nera è utile perché capire come funziona un DBMS può aiutare a un migliore utilizzo, e perché alcuni servizi sono offerti separatamente (es. tuning, gestione degli indici).

### DataBase Management System (DBMS)

> [!quote] Definizione — DBMS
> Un DBMS è un sistema (prodotto software) in grado di gestire collezioni di dati che siano (anche):
> - **grandi** (di dimensioni molto maggiori della memoria centrale dei sistemi di calcolo utilizzati)
> - **persistenti** (con un periodo di vita indipendente dalle singole esecuzioni dei programmi che le utilizzano)
> - **condivise** (utilizzate da applicazioni diverse)
>
> garantendo **affidabilità** (resistenza a malfunzionamenti hardware e software) e **privatezza** (con una disciplina e un controllo degli accessi). Come ogni prodotto informatico, un DBMS deve essere **efficiente** (utilizzando al meglio le risorse di spazio e tempo del sistema) ed **efficace** (rendendo produttive le attività dei suoi utilizzatori).

Da queste caratteristiche derivano le principali sfide tecnologiche di un DBMS:

- **Le basi di dati sono grandi e persistenti**: la persistenza richiede una gestione in memoria secondaria; la grandezza richiede che tale gestione sia sofisticata (non si può caricare tutto in memoria principale e poi riscaricare).
- **Le basi di dati vengono interrogate**: gli utenti vedono il modello logico (relazionale), ma i dati sono in memoria secondaria. Le strutture logiche non sarebbero efficienti se usate direttamente in memoria secondaria: servono strutture fisiche opportune. La memoria secondaria è molto più lenta di quella principale, quindi serve un'interazione fra le due che limiti il più possibile gli accessi alla secondaria (esempio: un'interrogazione con un join).
- **Le basi di dati sono affidabili**: sono una risorsa per chi le possiede e devono essere conservate anche in presenza di malfunzionamenti (es. un trasferimento di fondi fra conti correnti con guasto del sistema a metà). Le transazioni devono essere **atomiche** (o tutto o niente) e **definitive** (dopo la conclusione, non si dimenticano). L'affidabilità è impegnativa per via degli aggiornamenti frequenti e della necessità di gestire il buffer.
- **Le basi di dati sono condivise**: una base di dati è una risorsa integrata e condivisa fra le varie applicazioni. Conseguenze: attività diverse su dati in parte condivisi richiedono meccanismi di **autorizzazione**; attività multi-utente su dati condivisi richiedono il **controllo della concorrenza**. Esempi: due prelevamenti (quasi) contemporanei sullo stesso conto corrente, due prenotazioni (quasi) contemporanee sullo stesso posto. Intuitivamente le transazioni sono corrette se **seriali** (prima una e poi l'altra), ma in molti sistemi reali l'efficienza sarebbe penalizzata troppo se le transazioni fossero seriali: il controllo della concorrenza permette un ragionevole compromesso.

## Architettura del DBMS

Il sistema si articola in due macro-componenti che cooperano attraverso il catalogo (dizionario dei dati):

- **Gestore degli accessi e delle interrogazioni**
- **Gestore delle transazioni**

### Gestore degli accessi e delle interrogazioni

```
SQL
  │
Gestore delle interrogazioni
  │  scansione, accesso diretto, ordinamento
Gestore dei metodi d'accesso
  │  lettura "virtuale"
Gestore del buffer
  │  lettura fisica
Gestore della memoria secondaria
  │
Memoria secondaria
```

### Gestore delle transazioni

Il gestore delle transazioni si appoggia al **gestore della concorrenza** e al **gestore dell'affidabilità**, che a loro volta interagiscono con il gestore dei metodi d'accesso e con il gestore del buffer.

## Memoria principale e secondaria

I programmi possono fare riferimento solo a dati in memoria principale. Le basi di dati devono essere (sostanzialmente) in memoria secondaria per due motivi: **dimensioni** e **persistenza**. I dati in memoria secondaria possono essere utilizzati solo se prima trasferiti in memoria principale (questo spiega i termini "principale" e "secondaria").

I dispositivi di memoria secondaria sono organizzati in **blocchi** di lunghezza (di solito) fissa (ordine di grandezza: alcuni KB). Le uniche operazioni sui dispositivi sono la lettura e la scrittura di una **pagina**, cioè dei dati di un blocco (una stringa di byte); per comodità consideriamo blocco e pagina sinonimi.

L'accesso a memoria secondaria comporta:

- tempo di **posizionamento della testina** (10-50ms)
- tempo di **latenza** (5-10ms)
- tempo di **trasferimento** (1-2ms)

in media non meno di 10ms. Il costo di un accesso a memoria secondaria è quattro o più ordini di grandezza maggiore di quello per operazioni in memoria centrale. Perciò, nelle applicazioni "**I/O bound**" (con molti accessi a memoria secondaria e relativamente poche operazioni) il costo dipende esclusivamente dal numero di accessi a memoria secondaria. Inoltre accessi a blocchi "vicini" costano meno (**contiguità**).

## Buffer management

> [!quote] Definizione — Buffer
> Il **buffer** è un'area di memoria centrale, gestita dal DBMS (preallocata) e condivisa fra le transazioni, organizzata in **pagine** di dimensioni pari o multiple di quelle dei blocchi di memoria secondaria (1KB-100KB). È importantissimo per via della grande differenza di tempo di accesso fra memoria centrale e memoria secondaria.

### Scopo della gestione del buffer

Ridurre il numero di accessi alla memoria secondaria:

- in caso di lettura, se la pagina è già presente nel buffer, non è necessario accedere alla memoria secondaria
- in caso di scrittura, il gestore del buffer può decidere di differire la scrittura fisica (ammesso che ciò sia compatibile con la gestione dell'affidabilità)

> [!example] Merge-sort a più vie
> Un file di 10.000.000 di record da 100 byte ciascuno (1GB), con blocchi da 4KB e un buffer disponibile di soli 20MB, può essere ordinato in memoria secondaria tramite un **merge-sort "a più vie"**: la gestione dei buffer e la differenza di costi fra memoria principale e secondaria possono suggerire algoritmi innovativi rispetto a quelli puramente in-memory.

### Dati gestiti dal buffer manager

Il buffer manager mantiene:

- il **buffer** stesso
- un **direttorio** che per ogni pagina mantiene (ad esempio): il file fisico e il numero del blocco, e due variabili di stato:
  - un **contatore** che indica quanti programmi utilizzano la pagina
  - un **bit** che indica se la pagina è "**sporca**", cioè se è stata modificata

### Interfaccia offerta dal buffer manager

Il buffer manager riceve richieste di lettura e scrittura (di pagine), le esegue accedendo alla memoria secondaria solo quando indispensabile e utilizzando invece il buffer quando possibile, tramite le primitive:

- **fix**: richiesta di una pagina; richiede una lettura solo se la pagina non è nel buffer (incrementa il contatore associato alla pagina)
- **setDirty**: comunica al buffer manager che la pagina è stata modificata
- **unfix**: indica che la transazione ha concluso l'utilizzo della pagina (decrementa il contatore associato alla pagina)
- **force**: trasferisce in modo sincrono una pagina in memoria secondaria (su richiesta del gestore dell'affidabilità, non del gestore degli accessi)

Le politiche sono simili a quelle relative alla gestione della memoria da parte dei sistemi operativi; principi:

- **"località dei dati"**: è alta la probabilità di dover riutilizzare i dati attualmente in uso
- **"legge 80-20"**: l'80% delle operazioni utilizza sempre lo stesso 20% dei dati

### Esecuzione della fix

1. Cerca la pagina nel buffer: se c'è, restituisce l'indirizzo.
2. Altrimenti, cerca una pagina libera nel buffer (contatore a zero): se la trova, restituisce l'indirizzo.
3. Altrimenti, due alternative:
   - **"steal"**: selezione di una "vittima" (pagina occupata del buffer); i dati della vittima sono scritti in memoria secondaria; viene letta la pagina di interesse dalla memoria secondaria e si restituisce l'indirizzo
   - **"no-steal"**: l'operazione viene posta in attesa

> [!info] Scritture sincrone e asincrone
> Il buffer manager richiede scritture in due contesti diversi: in modo **sincrono** quando è richiesto esplicitamente con una `force`; in modo **asincrono** quando lo ritiene opportuno (o necessario), in particolare può decidere di anticipare o posticipare scritture per coordinarle e/o sfruttare la disponibilità dei dispositivi.

## DBMS e file system

Il **file system** è il componente del sistema operativo che gestisce la memoria secondaria. I DBMS ne utilizzano le funzionalità, ma in misura limitata: per creare ed eliminare file e per leggere e scrivere singoli blocchi o sequenze di blocchi contigui. L'organizzazione dei file, sia in termini di distribuzione dei record nei blocchi sia relativamente alla struttura all'interno dei singoli blocchi, è gestita **direttamente dal DBMS**.

Il DBMS gestisce i blocchi dei file allocati come se fossero un unico grande spazio di memoria secondaria e costruisce, in tale spazio, le strutture fisiche con cui implementa le relazioni. Il DBMS crea file di grandi dimensioni che utilizza per memorizzare diverse relazioni (al limite, l'intero database). Talvolta vengono creati file in tempi successivi: è possibile che un file contenga i dati di più relazioni e che le varie tuple di una relazione siano in file diversi. Spesso, ma non sempre, ogni blocco è dedicato a tuple di un'unica relazione.

## Blocchi e record

I blocchi (componenti "fisici" di un file) e i record (componenti "logici") hanno dimensioni in generale diverse: la dimensione del blocco dipende dal file system, mentre la dimensione del record (semplificando un po') dipende dalle esigenze dell'applicazione, e può anche variare nell'ambito di un file.

### Fattore di blocco

Il **fattore di blocco** è il numero di record in un blocco. Detta $L_R$ la dimensione di un record (per semplicità costante nel file: "record a lunghezza fissa") e $L_B$ la dimensione di un blocco, se $L_B > L_R$ possiamo avere più record in un blocco:
$$\left\lfloor \frac{L_B}{L_R} \right\rfloor$$

Lo spazio residuo può essere:

- **utilizzato** (record "spanned" o impaccati)
- **non utilizzato** ("unspanned")

### Organizzazione delle tuple nelle pagine

Ci sono varie alternative, anche legate ai metodi di accesso. Una possibilità tipica prevede, all'interno della pagina:

- un **dizionario di pagina**, con i puntatori alle singole tuple (`*t1`, `*t2`, `*t3`, ...), che cresce come uno stack
- la **parte utile della pagina**, contenente le tuple vere e proprie, che cresce come uno stack in direzione opposta
- un **bit di parità** e informazioni di controllo (relative alla struttura fisica e al file system)

Se la lunghezza delle tuple è fissa, la struttura può essere semplificata; alcuni sistemi possono spezzare le tuple su più pagine (necessario per tuple grandi).

## Strutture sequenziali

Esiste un ordinamento fra le tuple, che può essere rilevante ai fini della gestione:

- **seriale**: ordinamento fisico ma non logico
- **array**: posizioni individuate attraverso indici
- **ordinata**: l'ordinamento delle tuple è coerente con quello di un campo

### Struttura seriale

Chiamata anche "Entry sequenced", **file heap** o **file disordinato**. È molto diffusa nelle basi di dati relazionali, associata a indici secondari. Gli inserimenti vengono effettuati in coda (con riorganizzazioni periodiche) oppure al posto di record cancellati.

### Strutture ordinate

Permettono ricerche binarie, ma solo fino a un certo punto (ad esempio: come troviamo la "metà del file"?). Nelle basi di dati relazionali si utilizzano quasi solo in combinazione con indici (file ISAM o file ordinati con indice primario).

## File hash

Permettono un accesso diretto molto efficiente (da alcuni punti di vista). La tecnica si basa su quella utilizzata per le tavole hash in memoria centrale.

### Tavola hash

Obiettivo: accesso diretto ad un insieme di record sulla base del valore di un campo (detto **chiave**, che per semplicità supponiamo identificante, ma non è necessario).

- se i possibili valori della chiave sono in numero paragonabile al numero di record (e corrispondono a un "tipo indice"), si usa un array (es. università con 1000 studenti e numeri di matricola compresi fra 1 e 1000)
- se i possibili valori della chiave sono molti di più di quelli effettivamente utilizzati, non possiamo usare l'array (spreco): es. 40 studenti e numero di matricola di 6 cifre (un milione di possibili chiavi)

Volendo continuare a usare qualcosa di simile a un array, ma senza sprecare spazio, si trasformano i valori della chiave in possibili indici di un array tramite una **funzione hash**:

- associa a ogni valore della chiave un "indirizzo", in uno spazio di dimensione paragonabile (leggermente superiore) rispetto a quello strettamente necessario
- poiché il numero di possibili chiavi è molto maggiore del numero di possibili indirizzi ("lo spazio delle chiavi è più grande dello spazio degli indirizzi"), la funzione non può essere iniettiva e quindi esiste la possibilità di **collisioni** (chiavi diverse che corrispondono allo stesso indirizzo)
- le buone funzioni hash distribuiscono in modo casuale e uniforme, riducendo la probabilità di collisione (che si riduce aumentando lo spazio ridondante)

> [!example] Un esempio di tavola hash
> 40 record, tavola hash con 50 posizioni (funzione `M mod 50`): si ottengono 1 collisione a 4, 2 collisioni a 3, 5 collisioni a 2 (numero medio di accessi: 1,425).

### Tavola hash: gestione delle collisioni

Varie tecniche:

- posizioni successive disponibili
- tabella di overflow (gestita in forma collegata)
- funzioni hash "alternative"

Nota: le collisioni ci sono (quasi) sempre; le collisioni multiple hanno probabilità che decresce al crescere della molteplicità; la molteplicità media delle collisioni è molto bassa.

### File hash

L'idea è la stessa della tavola hash, ma si basa sull'organizzazione in **blocchi**: in questo modo si "ammortizzano" le probabilità di collisione (ogni indirizzo hash corrisponde a un blocco capace di contenere più record).

> [!example] Confronto tavola hash / file hash
> Stessi 40 record e 50 posizioni: con un file hash a fattore di blocco 10 (5 blocchi con 10 posizioni ciascuno) si hanno solo 2 overflow, con un numero medio di accessi di 1,05 (contro 1,425 della tavola hash "piatta").

### File hash, osservazioni

- È l'organizzazione più efficiente per l'accesso diretto basato su valori della chiave con condizioni di uguaglianza (accesso puntuale): costo medio di poco superiore all'unità (il caso peggiore è molto costoso ma talmente improbabile da poter essere ignorato).
- Le collisioni (overflow) sono di solito gestite con blocchi collegati.
- Non è efficiente per ricerche basate su intervalli (né per ricerche basate su altri attributi).
- I file hash "degenerano" se si riduce lo spazio sovrabbondante: funzionano solo con file la cui dimensione non varia molto nel tempo.

## Indici di file

> [!quote] Definizione — Indice
> Un **indice** è una struttura ausiliaria per l'accesso (efficiente) ai record di un file sulla base dei valori di un campo (o di una concatenazione di campi) detto **chiave** (o, meglio, **pseudochiave**, perché non è necessariamente identificante).

L'idea fondamentale è l'indice analitico di un libro: una lista di coppie (termine, pagina), ordinata alfabeticamente sui termini, posta in fondo al libro e separabile da esso. Un indice `I` di un file `f` è un altro file, con record a due campi — chiave e indirizzo (dei record di `f` o dei relativi blocchi) — ordinato secondo i valori della chiave.

### Tipi di indice

- **indice primario**: su un campo sul cui ordinamento è basata la memorizzazione (detti anche indici di cluster, anche se talvolta si chiamano "primari" quelli su una chiave identificante e "di cluster" quelli su una chiave non identificante)
- **indice secondario**: su un campo con ordinamento diverso da quello di memorizzazione
- **indice denso**: contiene un record per ciascun valore del campo chiave
- **indice sparso**: contiene un numero di record inferiore rispetto al numero di valori diversi del campo chiave (un record per ciascun blocco, tipicamente)

> [!info] Osservazioni sui tipi di indice
> Un indice primario può essere sparso, uno secondario deve essere denso (perché nell'ordinamento fisico i record con la stessa chiave dell'indice secondario non sono contigui). Esempio, sempre rispetto a un libro: indice generale (sparso, tipo primario) e indice analitico (denso, tipo secondario). I benefici legati alla presenza di indici secondari sono molto più sensibili. Ogni file può avere al più un indice primario e un numero qualunque di indici secondari (su campi diversi): ad esempio una guida turistica può avere l'indice dei luoghi e quello degli artisti. Un file hash non può avere un indice primario (non essendo ordinato).

### Dimensioni dell'indice

Notazione: $L$ numero di record nel file, $B$ dimensione dei blocchi, $R$ lunghezza dei record (fissa), $K$ lunghezza del campo chiave, $P$ lunghezza degli indirizzi (ai blocchi).

- numero di blocchi per il file (circa): $N_F = L / (B/R)$
- numero di blocchi per un indice denso: $N_D = L / (B/(K+P))$
- numero di blocchi per un indice sparso: $N_S = N_F / (B/(K+P))$

### Caratteristiche degli indici

- **accesso diretto** (sulla chiave) efficiente, sia puntuale sia per intervalli
- **scansione sequenziale ordinata** efficiente: tutti gli indici (in particolare quelli secondari) forniscono un **ordinamento logico** sui record del file, con numero di accessi pari al numero di record del file (a parte qualche beneficio dovuto alla bufferizzazione)
- **modifiche della chiave, inserimenti, eliminazioni inefficienti** (come nei file ordinati): tecniche per alleviare i problemi: file o blocchi di overflow, marcatura per le eliminazioni, riempimento parziale, blocchi collegati (non contigui), riorganizzazioni periodiche

> [!info] Puntatori ai blocchi vs puntatori ai record
> Un indice secondario può usare puntatori ai blocchi oppure puntatori ai record. I puntatori ai blocchi sono più compatti. I puntatori ai record permettono di semplificare alcune operazioni (effettuate solo sull'indice, senza accedere al file se non quando indispensabile).

### Indici multilivello

Gli indici sono file essi stessi, quindi ha senso costruire indici sugli indici, per evitare di fare ricerche fra blocchi diversi. Possono esistere più livelli fino ad avere il livello più alto con un solo blocco; i livelli sono di solito abbastanza pochi, perché:

- l'indice è ordinato, quindi l'indice sull'indice è sparso
- i record dell'indice sono piccoli

Numero di blocchi al livello $j$ dell'indice (circa): $N_j = N_{j-1} / (B/(K+P))$.

## Indici, problemi

Tutte le strutture di indice viste finora sono basate su strutture ordinate e quindi sono poco flessibili in presenza di elevata dinamicità. Gli indici utilizzati dai DBMS sono più sofisticati: **indici dinamici multilivello**, i **B-tree** (intuitivamente: alberi di ricerca bilanciati).

Si arriva ai B-tree per gradi: alberi binari di ricerca → alberi n-ari di ricerca → alberi n-ari di ricerca bilanciati.

### Albero binario di ricerca

Albero binario etichettato in cui per ogni nodo il sottoalbero sinistro contiene solo etichette minori di quella del nodo e il sottoalbero destro etichette maggiori. Il tempo di ricerca (e inserimento), pari alla profondità, è logaritmico nel caso "medio" (assumendo un ordine di inserimento casuale).

### Albero di ricerca di ordine P

Ogni nodo ha (fino a) $P$ figli e (fino a) $P-1$ etichette, ordinate. Nell'$i$-esimo sottoalbero abbiamo tutte etichette maggiori della $(i-1)$-esima etichetta e minori della $i$-esima. Ogni ricerca o modifica comporta la visita di un cammino radice-foglia. In strutture fisiche, un nodo può corrispondere a un blocco.

Un albero di ricerca di ordine $P$ così definito è ancora (potenzialmente) rigido. Un **B-tree** è un albero di ricerca che viene mantenuto bilanciato, grazie a:

- **riempimento parziale** (mediamente 70%)
- **riorganizzazioni (locali)** in caso di sbilanciamento

### Organizzazione dei nodi del B-tree

Ogni nodo contiene una sequenza alternata di puntatori e chiavi: $P_0, K_1, P_1, \ldots, K_i, P_i, \ldots, K_F, P_F$. Il sottoalbero raggiunto da $P_0$ contiene le chiavi $K < K_1$; il sottoalbero raggiunto da $P_i$ contiene le chiavi $K_i \leq K < K_{i+1}$; il sottoalbero raggiunto da $P_F$ contiene le chiavi $K > K_F$.

### Split e merge

Inserimenti ed eliminazioni sono precedute da una ricerca fino a una foglia:

- **inserimenti**: se c'è posto nella foglia, ok; altrimenti il nodo va suddiviso (**split**), con necessità di un puntatore in più per il nodo genitore; se non c'è posto, si sale ancora, eventualmente fino alla radice. Il riempimento rimane sempre superiore al 50%.
- **eliminazioni**: possono portare a riduzioni (fusioni, **merge**) di nodi.
- **modifiche del campo chiave**: vanno trattate come eliminazioni seguite da inserimenti.

### B-tree e B+-tree

- **B+-tree**: le foglie sono collegate in una lista; ottimo per le ricerche su intervalli; molto usato nei DBMS. I nodi intermedi contengono solo chiavi di separazione, mentre i puntatori ai dati sono tutti nelle foglie (organizzati in modo arbitrario).
- **B-tree**: i nodi intermedi possono avere puntatori direttamente ai dati (non solo le foglie).

## Strutture fisiche nei DBMS relazionali

- **Struttura primaria**:
  - disordinata (heap, "unclustered")
  - ordinata ("clustered"), anche su una pseudochiave
  - hash ("clustered"), anche su una pseudochiave, senza ordinamento
  - clustering di più relazioni
- **Indici** (densi/sparsi, semplici/composti):
  - ISAM (**statico**), di solito su struttura ordinata
  - B-tree (**dinamico**)

### Strutture fisiche in alcuni DBMS

- **Oracle**: struttura primaria come file heap, "hash cluster" (struttura hash), oppure cluster (anche plurirelazionali) anche ordinati (con B-tree denso); indici secondari di vario tipo (B-tree, bit-map, funzioni).
- **DB2**: primaria heap o ordinata con B-tree denso; indice sulla chiave primaria (automaticamente); indici secondari B-tree densi.
- **SQL Server**: primaria heap o ordinata con indice B-tree sparso; indici secondari B-tree densi.
- **Ingres** (anni fa): file heap, hash, ISAM (ciascuno anche compresso); indici secondari.
- **Informix** (per DOS, 1994): file heap; indici secondari (e primari "cluster" ma non mantenuti).

### Definizione degli indici in SQL

Non è standard, ma è presente in forma simile nei vari DBMS:

```sql
create [unique] index IndexName on TableName(AttributeList)
drop index IndexName
```

## Esecuzione e ottimizzazione delle interrogazioni

> Per il dettaglio completo del processo di ottimizzazione (analisi lessicale/sintattica/semantica, ottimizzazione algebrica con "push selections/projections down", procedura euristica, profili delle relazioni e ottimizzazione basata sui costi) si veda [[16 - Indici e Progettazione Fisica]], che tratta lo stesso argomento in dettaglio.

Qui si aggiungono alcuni approfondimenti sull'esecuzione fisica delle operazioni.

### Rappresentazione interna delle interrogazioni

Le interrogazioni sono rappresentate internamente come **alberi**:

- le **foglie** rappresentano i dati (relazioni, file)
- i **nodi intermedi** rappresentano operatori (dapprima operatori algebrici, poi effettivi operatori di accesso)

### Esecuzione delle operazioni

I DBMS implementano gli operatori dell'algebra relazionale (o meglio, loro combinazioni) per mezzo di operazioni di livello abbastanza basso, che però possono implementare vari operatori "in un colpo solo". Operatori fondamentali:

- **scansione**
- **accesso diretto**

A livello più alto: **ordinamento**. Ancora più alto: **join**.

### Accesso diretto

Può essere eseguito solo se le strutture fisiche lo permettono: **indici** o **strutture hash**.

- **Accesso diretto basato su indice**: efficace per interrogazioni sulla chiave dell'indice, "puntuali" ($A_i = v$) o su intervallo ($v_1 \leq A_i \leq v_2$). Per predicati congiuntivi si sceglie il più selettivo per l'accesso diretto e si verifica poi sugli altri dopo la lettura (in memoria centrale). Per predicati disgiuntivi servono indici su tutti gli attributi coinvolti, ma conviene usarli solo se molto selettivi, facendo attenzione ai duplicati.
- **Accesso diretto basato su hash**: efficace per interrogazioni puntuali ($A_i = v$), ma **non** su intervallo. Per predicati congiuntivi e disgiuntivi vale lo stesso discorso fatto per gli indici.

> [!example] Indici e hash su più campi
> Un indice (o una struttura hash) definiti su `(cognome, nome)` funzionano per l'accesso diretto su `cognome` (il campo più significativo), ma **non** per l'accesso diretto sul solo `nome`.

### Join

Il **join** è l'operazione più costosa. I metodi più noti sono:

- **nested-loop**: si scandisce la tabella esterna e, per ogni tupla, si accede alla tabella interna (tramite scansione interna oppure accesso via indice) per cercare le tuple corrispondenti sul valore dell'attributo di join.
- **merge-scan**: se le due tabelle sono ordinate sull'attributo di join, si eseguono due scansioni sincronizzate ("scan sinistro" e "scan destro"), avanzando in parallelo e confrontando i valori correnti.
- **hash-based** (**hash join**): si costruisce una struttura hash sull'attributo di join di una delle due tabelle, e si utilizza per trovare rapidamente le tuple corrispondenti dell'altra tabella.

### Ottimizzazione basata sui costi

Un problema articolato, con scelte relative a:

- operazioni da eseguire (es.: scansione o accesso diretto?)
- ordine delle operazioni (es. join di tre relazioni: in che ordine?)
- i dettagli del metodo (es.: quale metodo di join?)

Le architetture parallele e distribuite aprono ulteriori gradi di libertà.

Il processo di ottimizzazione costruisce un **albero di decisione** con le varie alternative (i **piani di esecuzione**): ad esempio, per un join $R \Join S \Join T$ si valutano i diversi ordini di esecuzione (raggruppamenti $(R \Join S) \Join T$, $(R \Join T) \Join S$, $(S \Join T) \Join R$), e per ciascun join si valutano i diversi metodi (nested-loop con relazione interna o esterna, merge-scan, hash-join con hash su una o sull'altra relazione). Ogni combinazione (foglia dell'albero) rappresenta una **strategia**: si valuta il costo di ciascun piano e si sceglie il piano di costo minore. L'ottimizzatore trova di solito una "buona" soluzione, non necessariamente l'ottimo in senso assoluto.

## Progettazione fisica

La progettazione fisica è la fase finale del processo di progettazione di basi di dati.

- **Input**: lo schema logico e informazioni sul carico applicativo
- **Output**: lo schema fisico, costituito dalla definizione delle relazioni con le relative strutture fisiche (e molti parametri, spesso legati allo specifico DBMS)

### Progettazione fisica nel modello relazionale

La caratteristica comune dei DBMS relazionali è la disponibilità degli indici: la progettazione fisica spesso coincide con la scelta degli indici (oltre ai parametri strettamente dipendenti dal DBMS).

- le chiavi primarie delle relazioni sono di solito coinvolte in selezioni e join: molti sistemi prevedono (oppure suggeriscono) di definire indici sulle chiavi primarie
- altri indici vengono definiti con riferimento ad altre selezioni o join "importanti"
- se le prestazioni sono insoddisfacenti, si "tara" il sistema aggiungendo o eliminando indici
- è utile verificare se e come gli indici sono utilizzati con il comando SQL `show plan`
