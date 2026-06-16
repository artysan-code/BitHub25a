> [!info] Da inviare a
> Paola Vocca — `paola.vocca@uniroma2.it`
>
> Documento di assegnazione del progetto. Una volta approvato dalla docente si procede con la Fase 2 (progettazione concettuale).
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