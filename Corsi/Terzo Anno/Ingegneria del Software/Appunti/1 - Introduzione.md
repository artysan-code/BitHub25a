# Introduzione all'Ingegneria del Software

L'obiettivo dell'Ingegneria del Software è fornire i metodi e le tecnologie per inquadrare la produzione del software all'interno di una disciplina ingegneristica, presentando il processo software e le più moderne tecniche di produzione. Lo scopo è formare professionisti in grado di gestire la complessità dello sviluppo software moderno, garantendo qualità, rispetto dei tempi e dei budget.

### Software Engineering: Un Matrimonio Incompiuto
L'Ingegneria del Software (Software Engineering) è la disciplina che si occupa della produzione di software secondo i principi sistematici e misurabili dell'ingegneria, come la progettazione e la validazione, rendendolo un vero e proprio prodotto industriale affidabile e mantenibile. L'assenza di un approccio ingegneristico porta a conseguenze negative ben note: scarsa qualità del prodotto, che si manifesta con bug e malfunzionamenti; bassa competitività sul mercato; e il frequente superamento dei costi (cost overrun) e dei tempi di consegna (time overrun), fenomeni che minano la sostenibilità economica dei progetti.

Essendo una disciplina relativamente giovane se paragonata all'ingegneria tradizionale, per anni la produzione di software è stata vista come un'attività quasi artistica, un'arte legata principalmente all'abilità e all'intuizione del singolo programmatore. Si è a lungo creduto che la conoscenza approfondita dei linguaggi di programmazione e delle ultime tecnologie fosse l'unica competenza sufficiente per essere un ingegnere del software, considerandola quasi una branca dell'informatica teorica. Questo ha creato una profonda spaccatura, un "matrimonio non consumato" tra la teoria della programmazione e i principi fondamentali dell'ingegneria (progettazione rigorosa e validazione sistematica), come definito dall'influente informatico D.L. Parnas.

Il termine "Ingegneria del Software" fu coniato nel 1968 durante una storica conferenza della NATO a Garmisch, in Germania, nata per affrontare quella che veniva definita la "crisi del software". I risultati di quella conferenza furono chiari e rivoluzionari per l'epoca:

- La programmazione non è né una scienza pura né una matematica, perché il suo scopo ultimo non è la scoperta di nuova conoscenza, ma la costruzione di un **prodotto** che deve funzionare in modo affidabile per degli utenti.
- Gli ingegneri devono basare i loro principi di progettazione e convalida sulla solida base della teoria della programmazione, usandola come fondamento scientifico per le loro metodologie costruttive.
- I problemi tipici della produzione software (bassa qualità, ritardi cronici, costi imprevisti) sono il risultato di un lavoro svolto da persone non qualificate o, più precisamente, educate per altre professioni, che applicano un approccio improvvisato e non strutturato.

### Aspetti Tipici dell'Ingegneria del Software
Gli aspetti che caratterizzano l'ingegneria del software si dividono in tre categorie principali, che aiutano a comprendere la natura delle sfide da affrontare.

#### 1. Aspetti Accidentali (Superabili con la tecnologia)
Queste sono difficoltà che possono essere mitigate o risolte con il progresso degli strumenti e delle tecnologie.
- **Di attitudine**: legati alle capacità individuali. Strumenti come gli IDE avanzati e i debugger aiutano a ridurre l'impatto degli errori umani.
- **Di manutenzione**: legati alla difficoltà di modifica del software. L'adozione di architetture modulari e linguaggi ad alto livello facilita gli interventi futuri.
- **Di specifica e progetto**: legati alla definizione di cosa e come costruire. Tecniche di modellazione come UML e strumenti CASE (Computer-Aided Software Engineering) supportano queste fasi.
- **Di teaming**: legati al lavoro in gruppo. Sistemi di controllo di versione come Git e piattaforme di collaborazione sono diventati essenziali per coordinare il lavoro di team distribuiti.

#### 2. Aspetti Essenziali (Non superabili con la tecnologia)
Queste sono caratteristiche intrinseche della natura del software, che persisteranno nonostante il progresso tecnologico.
- **Complessità**: Il software è intrinsecamente complesso. A differenza dei sistemi fisici, non è vincolato dalle leggi della fisica e il numero di stati che un programma può assumere cresce in modo esponenziale, rendendone impossibile una comprensione completa.
- **Conformità**: Il software si deve conformare all'ambiente operativo e alle interfacce umane, non il contrario. Deve adattarsi a sistemi preesistenti, ereditandone spesso le limitazioni.
- **Cambiabilità**: È sempre il software che viene modificato per adattarsi a nuove esigenze. Un software di successo è un software che evolve continuamente.
- **Invisibilità**: Il software è invisibile e intangibile. In particolare, il suo comportamento in esecuzione non è direttamente osservabile. Se si verifica un errore, è estremamente complicato risalire alla causa scatenante proprio a causa di questa mancanza di fisicità.

#### 3. Aspetti di Costo
- **Costo vs Dimensione**: Il costo è proporzionale al quadrato della sua dimensione (size), secondo la formula $C = aS^2$. Questo significa che fare due prodotti di dimensione $S/2$ costa significativamente meno che farne uno di dimensione $S$, poiché $(S/2)^2 + (S/2)^2 = S^2/2$, ovvero la metà del costo.
- **Costo vs Repliche**: A differenza di un prodotto fisico, il costo di produzione di una replica digitale è virtualmente nullo.
- **Costo vs Mercato**: Per vendere un prodotto di dimensione doppia, che è costato quattro volte di più, è necessario un prezzo quattro volte superiore a parità di mercato, o un mercato quattro volte più grande a parità di prezzo.

### Il Ciclo di Vita del Software
La produzione del software è un processo esteso nel tempo che si articola in tre stadi principali: sviluppo, manutenzione e dismissione.
1. **Sviluppo (Stadio 1)**: È la fase di creazione del prodotto e si suddivide in 6 sotto-fasi:
    1. Requisiti
    2. Specifiche (o analisi dei requisiti)
    3. Pianificazione
    4. Progetto (preliminare e dettagliato)
    5. Codifica
    6. Integrazione
2. **Manutenzione (Stadio 2)**: È la fase più lunga e costosa, coprendo circa il 60% dei costi totali del ciclo di vita.
3. **Dismissione (Stadio 3)**: La fase finale in cui il software viene ritirato dall'uso.

![[l1 - Costo delle modifiche.png]]

È fondamentale comprendere che l'effetto delle modifiche varia drasticamente a seconda della fase in cui vengono introdotte. Una modifica in una fase avanzata può comportare costi enormemente superiori (da 60 a 100 volte) rispetto a una modifica nella fase di definizione.

### Il Ruolo del Testing
Il testing non è una fase isolata da eseguire solo alla fine, ma un'attività pervasiva e continua. Si articola in due modalità principali:
- **Verifica**: Si esegue alla fine di ogni fase per assicurarsi che sia stata svolta correttamente (_are we building the product right?_).
- **Validazione**: Si esegue alla fine dello sviluppo per controllare che il prodotto finale soddisfi le reali esigenze dell'utente (_are we building the right product?_).

È cruciale capire che **il testing non garantisce che il software sia privo di difetti**, ma serve a ridurre la probabilità che si verifichino malfunzionamenti.

Un'importante metrica associata è la **Defect Removal Efficiency (DRE)**, che indica la percentuale di difetti scoperti dal team prima del rilascio. Se un team trova 900 difetti e gli utenti ne trovano 100 nei primi 90 giorni, il DRE è del 90%. I valori medi si attestano intorno al 92%, ma variano molto in base all'organizzazione e non ci si può mai aspettare un DRE del 100%.

### Definizioni Fondamentali

- **Prodotto Software (Sw)**: L'insieme di Codice + Documentazione.
- **Artefatto**: Un prodotto software intermedio (es. documento dei requisiti). I documenti di specifica e di progetto sono spesso **semi-formali**, ovvero composti da parti testuali e parti in linguaggio tecnico/grafico.
- **Sistema Software**: Un insieme organizzato di prodotti software che lavorano insieme (es. la suite Microsoft Office).
- **Cliente, Sviluppatore, Utente**: Rispettivamente chi ordina, chi produce e chi usa il software.
- **Tipi di Software**: Si distingue tra **Sw interno** (cliente e sviluppatore coincidono) e **Sw a contratto** (soggetti differenti), che è la tipologia più comune.

### Affidabilità, Difetti, Guasti ed Errori
L'**affidabilità** (Software Reliability) è la probabilità che il prodotto funzioni "correttamente" in un determinato intervallo temporale. È legata a tre concetti distinti:
- **Errore**: L'azione umana (per ignoranza, distrazione) che introduce un difetto. 
  Ad esempio, scrivere $a = b * c$ invece di $a = b + c$.
- **Difetto (defect)**: L'anomalia presente nel prodotto a causa dell'errore.
- **Guasto (failure)**: Il comportamento anomalo del software in esecuzione, che si manifesta solo quando un difetto viene attivato. Un errore non implica sempre un guasto.

L'affidabilità non dipende solo dal numero totale di difetti. La **regola 10-90** mostra che il 90% del tempo di esecuzione è speso eseguendo solo il 10% del codice (il "core"). Pertanto, eliminare difetti da parti raramente usate ha un impatto minimo sull'affidabilità percepita, che dipende criticamente dal **profilo operativo** (operational profile) dell'utente.

### Confronto tra Affidabilità Hardware e Software
- **Causa dei guasti**: I guasti hardware sono dovuti a usura fisica. I guasti software sono causati da difetti di progettazione latenti; il software non si consuma.
- **Riparazione**: Nell'hardware, si sostituisce il componente e l'affidabilità torna come prima. Nel software, la "riparazione" (una modifica al codice) può aumentare o diminuire l'affidabilità.
- **Obiettivo**: Per l'hardware è la stabilità (frequenza di guasto costante). Per il software è la crescita di affidabilità (frequenza di guasto decrescente).

### Disponibilità e Sistemi Critici
La **disponibilità** (Availability) è la percentuale di tempo in cui il software è risultato utilizzabile. Dipende sia dall'affidabilità (frequenza dei guasti) sia dalla manutenibilità (tempo per ripararli). Queste metriche sono cruciali per sistemi in cui un guasto può causare enormi perdite economiche e sociali (trasporti, energia, finanza).

Un esempio drammatico è il fallimento del primo lancio del razzo **Ariane 5**, esploso dopo 30 secondi a causa di un guasto software. Il software di Ariane 4 era stato riutilizzato su un hardware diverso, causando un errore catastrofico da centinaia di milioni di euro. Per sistemi così critici, si punta a livelli di affidabilità altissimi ("Nine Nines", 99,9999999%) e si utilizzano tecniche come lo **Statistical Testing**, un processo molto costoso che usa modelli matematici complessi per stimare l'affidabilità del software prima del rilascio.

![[l2 - Affidabilità hardware.png]]

![[l3- Affidabilità software.png]]

### Conclusioni e Miti da Sfatare
La produzione del software è evoluta attraverso tre fasi: una **fase di abilità** (basata sul talento individuale), una **fase artigianale** (piccoli gruppi specializzati) e infine la **fase industriale**, dove lo sviluppo è un processo pianificato, coordinato e misurabile.

Lo standard IEEE definisce l'Ingegneria del Software come "l'applicazione di un approccio sistematico, disciplinato e misurabile allo sviluppo, esercizio e manutenzione del software". Il software stesso è una "configurazione" che include programmi, documenti e dati.

Infine, è importante sfatare alcuni miti persistenti:
- **Falso**: In caso di ritardo, basta aumentare il numero di programmatori.
- **Falso**: Una descrizione generica è sufficiente.
- **Falso**: Una volta consegnato il programma, il lavoro è finito.
- **Falso**: La qualità si può valutare solo alla fine.
- **Falso**: L'ingegneria del software è solo un costo aggiuntivo.

La realtà è che un approccio ingegneristico, sebbene richieda un investimento iniziale, riduce drasticamente i costi totali del ciclo di vita, prevenendo costose rilavorazioni e fallimenti.