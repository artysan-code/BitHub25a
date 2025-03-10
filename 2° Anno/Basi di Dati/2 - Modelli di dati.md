L'efficienza di un modello si misura come in ogni sistema informatico tramite:
- il **tempo** di esecuzione.
- la **memoria** (principale e secondaria).

Un DBMS a causa delle varie funzioni generalmente non sono più efficienti di un File-system, quindi l'efficienza di questo primo dipende dalla sua implementazione. Generalmente però un **DBMS** aumenta le funzioni di un file-system (che è più rudimentale generalmente).

(Da rivedere questa parte)
## Modello di rappresentazione dei dati
A differenza di quello che si può pensare un DBMS è predisposto a contenere e gestire **dati eterogenei**, a cui è associato uno schema, che viene costruito sulla base del **modello di dati** (che fornisce schemi, relazioni e vincoli di esistenza e consistenza).

Le descrizioni e rappresentazioni dei dati a livelli diversi permettono l’indipendenza dei dati dalla rappresentazione fisica:
- I programmi fanno riferimento alla struttura a livello più alto, e le rappresentazioni sottostanti possono essere modificate senza necessità di modifica dei programmi.
- Questo concetto viene realizzato tramite il **modello dei dati**.

> Un **modello di dati** è un insieme di concetti utilizzati per organizzare i dati di interesse e descriverne la struttura in modo che essa risulti comprensibile ad un elaboratore (e non solo).

Oppure la **Definizione di Ullman** che è formata da:
- Una notazione per scrivere i dati.
- Un'insieme di operazioni per manipolare tali dati.

Da cui deriviamo quindi la seguente definizione:
> Un **modello di dati** è un insieme di costrutti utilizzati per organizzare i dati di interesse e descriverne la struttura e la dinamica. In particolar modo è costituito da:
> - **Costrutti sintattici** per definire i dati
> - **Regole semantiche** per interpretarli
> - **Linguaggi** per manipolarli

Abbiamo tre tipologie di modelli:
- **Modello concettuale**
- **Modello logico**
- **Modello fisico**
### Modello Logico
Esistono diverse tipologie di modelli logici definiti nel tempo, descrivono l'organizzazione dei nei DBMS che l'utente può vedere. Sono indipendenti dalle strutture fisiche e ve ne sono diversi:
- **Modelli gerarchici** e **reticolari**: che utilizzano riferimenti espliciti (puntatori) fra record.
- **Modello ad oggetti** (ODBMS, Object Database Management System): rappresenta l'informazione a livello di oggetto, sono utilizzati in maniera più specifica rispetto al mercato.
- **Modello relazionale** che è basato su valori (RDBMS): anche i riferimenti tra dati in strutture (relazioni) diverse sono rappresentanti per mezzo dei valori stessi.
### Modello Concettuale
Hanno l'obiettivo di descrivere dei concetti del mondo reale e vengono usati nelle fasi iniziali della progettazione (Entity-Relationship e Modello Classi Associazioni, UML).![[21.png]]
## Schemi ed Istanze
In ogni base di dati esiste lo **schema**, che è persistente e rappresenta la struttura del dato (come la tabella) e **l'istanza** che è il dato stesso che può variare nel tempo.