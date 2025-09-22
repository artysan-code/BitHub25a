## DBMS vs File system
L'efficienza di un modello si misura come in ogni sistema informatico tramite:
- il **tempo** di esecuzione.
- la **memoria** (principale e secondaria).

Un DBMS a causa delle varie funzioni generalmente non sono più efficienti di un File-system, quindi l'efficienza di questo primo dipende dalla sua implementazione. Generalmente però un **DBMS** aumenta le funzioni di un file-system (che è più rudimentale generalmente).

(Da rivedere questa parte)
## Modello di rappresentazione dei dati
A differenza di quanto si potrebbe pensare, un DBMS è predisposto a contenere e gestire **dati eterogenei**, a cui è associato uno schema costruito sulla base del **modello di dati** (che fornisce schemi, relazioni e vincoli di esistenza e consistenza).

Le descrizioni e rappresentazioni dei dati a livelli diversi consentono l'indipendenza dei dati dalla rappresentazione fisica:
- I programmi fanno riferimento alla struttura a livello più alto, permettendo di modificare le rappresentazioni sottostanti senza necessità di intervenire sui programmi.
- Questo fondamentale concetto viene realizzato attraverso il **modello dei dati**.

> Un **modello di dati** è un insieme di concetti utilizzati per organizzare i dati di interesse e descriverne la struttura in modo che essa risulti comprensibile ad un elaboratore (e non solo).

La **Definizione di Ullman** è formata da:
- Una notazione per scrivere i dati.
- Un insieme di operazioni per manipolare tali dati.

Da queste considerazioni deriva quindi la seguente definizione completa:
> Un **modello di dati** è un insieme di costrutti utilizzati per organizzare i dati di interesse e descriverne la struttura e la dinamica. In particolare è costituito da:
> - **Costrutti sintattici** per definire i dati
> - **Regole semantiche** per interpretarli
> - **Linguaggi** per manipolarli

### Tipologie di modelli
Esistono tre tipologie principali di modelli:
- **Modello concettuale**
- **Modello logico**
- **Modello fisico**

#### Modello Logico
Esistono diverse tipologie di modelli logici definiti nel tempo, che descrivono l'organizzazione dei dati nei DBMS visibile all'utente. Sono indipendenti dalle strutture fisiche e comprendono:

- **Modelli gerarchici** e **reticolari**: utilizzano riferimenti espliciti (puntatori) fra record.
- **Modello ad oggetti** (ODBMS, Object Database Management System): rappresenta l'informazione a livello di oggetto, con utilizzo in ambiti specifici rispetto al mercato generale.
- **Modello relazionale** (RDBMS): basato sui valori, dove anche i riferimenti tra dati in strutture (relazioni) diverse sono rappresentati per mezzo dei valori stessi.

#### Modello Concettuale
I modelli concettuali hanno l'obiettivo di descrivere i concetti del mondo reale e vengono impiegati nelle fasi iniziali della progettazione (Entity-Relationship e Modello Classi Associazioni, UML).![[21.png]]
## Schemi ed Istanze
In ogni base di dati esiste lo **schema**, che è persistente e rappresenta la struttura del dato (come la tabella) e **l'istanza** che è il dato stesso che può variare nel tempo.
## Architettura di un DBMS
Nel nostro caso studiamo l'architettura **Standard ANSI/SPARC a tre livelli**, che rappresentiamo come:![[22.png]]

Qui possiamo quindi dedurre tre tipologie di schemi fondamentali:
- **Schema Esterno o Vista** è una *interfaccia* che permette di "vedere" una parte della base di dati in un modello logico.
- **Schema Logico** che descrive la logica del DBMS.
- **Schema Fisico o Interno** che invece è la sua effettiva rappresentazione per mezzo di strutture di memorizzazione.
## Indipendenza dei dati
L'indipendenza dei dati è una conseguenza dell'articolazione di questi ultimi, l'accesso avviene solo tramite il livello esterno (che spesso coincide con quello logico) e hanno due forme:
- **Indipendenza fisica**, quando il livello logico e fisico sono indipendenti da quello esterno, quindi la realizzazione fisica può cambiare senza cambiare i programmi. Una relazione è utilizzabile nello stesso modo qualunque sia la sua realizzazione fisica.
- **Indipendenza logica**, quando il livello logico è indipendente dal livello fisico quindi aggiunte alle viste non richiedono modifiche a livello logico. Inoltre, le modifiche al livello logico lasciano inalterato lo schema esterno, sono **trasparenti**.


## Linguaggi per basi di dati
Esistono due tipologie di linguaggi utilizzati nelle basi di dati:
- **DDL: data definition language**. Un'operazione DDL si presenta come:
```SQL
create table orario(
	insegnamento char(20) ,
	docente char(20) ,
	aula char(4),
	ora char(5)
)
```
- **DML: data manipulation language**. Un'operazione in DML si presenta come:
```MySQL
select docente
from orario
where aula = 'N1';
```

I DBMS dispongono di diversi linguaggi e interfacce diverse:
- I **linguaggi testuali interattivi** (Esempio *SQL*, quindi esegui *query scritte*).
- Dei **comandi** come nei linguaggi interattivi, immersi in un *linguaggio ospite* o con un *linguaggio ad hoc*.
- Con interfacce grafiche più *amichevoli* (Access di Microsoft).

## Attori del sistema
A livello professionale le figure applicate alle Basi di Dati sono le seguenti:
- **Progettisti di DBMS**.
- **Progettisti di Basi di Dati** (DBA).
- **Progettisti di Applicazioni** (Software Engineers).
- **Utenti**:
		- **finali**, che eseguono delle applicazioni definite (*transazioni*).
		- **casuali**, che eseguono operazioni non previste usando interfacce o linguaggi interattivi.

Le **transazioni** sono attività eseguite periodicamente e di cui vengono calcolate e previste le eccezioni. Inoltre, il termine transazione ha un’altra accezione, più specifica: sequenza indivisibile di operazioni (o vengono eseguite tutte o nessuna). Spesso queste sono eseguite con linguaggi ad hoc o ospiti.

Ecco alcuni pro e contro dell'uso dei DBMS:
- Pro
	- dati come risorsa comune, base di dati come modello della realtà 
	- gestione centralizzata con possibilità di standardizzazione ed “economia di scala” 
	- disponibilità di servizi integrati 
	- riduzione di ridondanze e inconsistenze
	- indipendenza dei dati (favorisce lo sviluppo e la manutenzione delle applicazioni) 
- Contro
	- costo dei prodotti e della transizione verso di essi 
	- non scorporabilità delle funzionalità (con riduzione di efficienza)