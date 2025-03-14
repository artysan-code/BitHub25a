## DBMS vs Filesystem
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
## Linguaggi per basi di dati
Esistono due tipologie di linguaggi utilizzati nelle basi di dati:
- **DDL: data definition language**.
- **DML: data manipulation language**.