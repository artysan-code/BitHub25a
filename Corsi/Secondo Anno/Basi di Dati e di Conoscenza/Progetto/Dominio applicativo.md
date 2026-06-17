> [!info] Stato — Fase 1 (assegnazione)
> Alla docente (Paola Vocca — `paola.vocca@uniroma2.it`) viene inviata **via email una versione ridotta** della proposta: solo dominio applicativo e funzionalità principali. Questo documento resta la visione completa del gruppo. Ciò che è stato effettivamente presentato — e che quindi va mantenuto anche se cambiamo idea nelle fasi successive — è fissato in fondo, in [[#Nucleo vincolante e margine di manovra]]. Una volta approvato si procede con la Fase 2 (progettazione concettuale).
## Componenti del gruppo

| Nome e cognome     | Matricola | E-mail                                  |
| ------------------ | --------- | --------------------------------------- |
| Samuel Tagliacozzo | 0349831   | samuel.tagliacozzo@students.uniroma2.eu |
| Marius Craciun     | 0334807   | marius.craciun@students.uniroma2.eu     |
## Idea del progetto
> [!info] Nome di lavoro
> **QuartiereExpress** — piattaforma di consegna a domicilio per i negozi di quartiere (nome provvisorio).
### Dominio applicativo
Il progetto ha per oggetto il sistema informativo di una **piattaforma di consegna a domicilio** che mette in rete i **negozi di quartiere** di una città — alimentari, ortofrutta, gastronomie, farmacie e simili — collegandoli ai clienti finali tramite un servizio di consegna affidato a **corrieri**.

Si tratta di un modello *marketplace*: la piattaforma non possiede la merce, ma fa da intermediario tra esercenti, clienti e corrieri. Ogni esercente gestisce il proprio catalogo, i propri prezzi e le proprie scorte; il cliente compone un ordine — eventualmente con prodotti di più negozi — quindi la piattaforma verifica la disponibilità, scala le scorte, affida la consegna a un corriere disponibile nella zona e segue l'ordine dal momento della conferma fino alla consegna. A consegna avvenuta, il cliente può lasciare una recensione del negozio e del servizio.
### Obiettivi e funzionalità
L'obiettivo è progettare e realizzare **la sola base di dati** a supporto della piattaforma: lo schema dei dati, i vincoli di integrità, le interrogazioni, le viste per i diversi ruoli e le procedure che ne mantengono coerenti le informazioni.
#### Funzionalità principali
- anagrafica di negozi, prodotti e cataloghi, con prezzo e scorta per ciascun negozio;
- composizione e gestione degli ordini dei clienti, anche con prodotti di più negozi;
- gestione delle consegne: assegnazione a un corriere, zona di competenza, stato e tempi;
- coerenza automatica tra scorte, totali degli ordini e stato delle consegne;
- interrogazioni statistiche significative: prodotti più venduti, fatturato per negozio, tempi medi di consegna, scorte sotto soglia, e simili.
#### Funzionalità secondarie
- recensioni dei clienti su negozi e consegne, con voto medio per negozio;
- differenziazione delle informazioni visibili a ciascuna categoria di utente;
- *(estensione facoltativa)* gestione di un deposito della piattaforma e dei rifornimenti ai negozi.
### Classi di utenza (preliminari)
- **Cliente** — consulta i cataloghi, effettua ordini, segue le proprie consegne, lascia recensioni.
- **Esercente** — gestisce il proprio negozio (catalogo, prezzi, scorte) e consulta gli ordini che lo riguardano.
- **Corriere** — visualizza e aggiorna lo stato delle consegne assegnate.
- **Amministratore** — gestisce la piattaforma e accede alle statistiche complessive.
### Perimetro del progetto
In linea con le linee guida, il progetto sviluppa **esclusivamente la parte relativa ai dati**. Restano fuori l'applicazione e l'interfaccia utente, la gestione effettiva dei pagamenti e il calcolo dei percorsi di consegna: di questi aspetti la base di dati rappresenta soltanto le informazioni (ad esempio lo stato di un pagamento o la zona di una consegna), non la logica applicativa.
## Nucleo vincolante e margine di manovra
Sezione di servizio per il gruppo: registra **cosa è stato effettivamente presentato alla docente** nell'email di Fase 1 e, di conseguenza, cosa dobbiamo mantenere nelle fasi successive per non uscire dal progetto approvato.
### Cosa è stato presentato (email Fase 1)
> [!example] Estratto della proposta inviata
> Base di dati di una piattaforma di consegna a domicilio per i negozi di quartiere (alimentari, ortofrutta, ecc.); la piattaforma fa da intermediario tra negozi, clienti e corrieri. Ogni negozio gestisce catalogo e scorte, il cliente fa un ordine e la piattaforma lo affida a un corriere, seguendolo fino alla consegna. Si sviluppa **solo la parte dati**. Il database dovrà gestire:
> - negozi, prodotti e cataloghi (con prezzo e scorta per negozio);
> - gli ordini dei clienti;
> - le consegne affidate ai corrieri;
> - la coerenza tra scorte, ordini e stato delle consegne;
> - qualche interrogazione statistica sul servizio.
>
> Classi di utenza, funzionalità secondarie e requisiti di dettaglio sono stati esplicitamente rimandati alla fase concettuale.
### Da mantenere (nucleo vincolante)
> [!warning] Non modificare senza riproporlo alla docente
> Questi punti definiscono il progetto approvato: vanno tenuti anche se rivediamo tutto il resto.
> 1. **Identità del dominio**: piattaforma *marketplace* di consegna a domicilio per negozi di quartiere, intermediaria tra **negozi, clienti e corrieri** (la piattaforma non possiede la merce).
> 2. **Perimetro**: si progetta **solo la base di dati**.
> 3. **Funzionalità core** (le cinque presentate):
>     - anagrafica di negozi, prodotti e cataloghi, con **prezzo e scorta per negozio**;
>     - **ordini** dei clienti;
>     - **consegne** affidate ai corrieri;
>     - **coerenza** tra scorte, ordini e stato delle consegne;
>     - almeno alcune **interrogazioni statistiche** sul servizio.
### Margine libero (modificabile senza uscire dal progetto)
> [!info] Tenuto in riserva, non presentato
> Possiamo aggiungere, ridurre o cambiare questi aspetti nelle fasi successive senza contraddire la proposta:
> - **ordini con prodotti di più negozi** (tenere o semplificare a un negozio per ordine);
> - **recensioni** di negozi e consegne;
> - **differenziazione di viste/permessi** per ruolo;
> - estensione **deposito della piattaforma e rifornimenti**;
> - numero e profilo dettagliato delle **classi di utenza** (clienti, esercenti, corrieri, amministrazione);
> - dettagli delle consegne (**zona di competenza, tempi, stati**);
> - quali e quante **statistiche** realizzare.