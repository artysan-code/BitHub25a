# Workshop Avalanche \# 08.11.2025
## Argomenti
- Blockchain -> Sistema peer to peer a nodi
    - Perché nascono le blockchain -> sfidicia nelle entità che "controllano" e gestiscono tutto.
    - 
## Introduzione
Il sistema bancario trazionale ogni transazione è coperta da diverse entità, dove vi è anche una gestione centralizzata e controllata dalle istituzioni.

(Se deposito denaro dentro una banca il denaro non è più mio, io ho la possibilità di fare credito alla banca)

Il sistema Blockchain è invece sicuro, crittografato e non controllato da nessuna entità se non le due che eseguono la transazione. La validazione della transazione è fatta tramite miliardi di nodi che possono vedere ogni aggiornamento della blockchain.

(Se posseggo 0.0023 bitcoin, nessuno ha controllo su quello, a meno che non mi affido a servizi terzi di banca)
### Perché sono nate?
L'intermediario nelle blockchain non è necessario in quanto si basa tutto sulla **crittografia** e sulle regole condivise nel protocollo.

### Funzioni Hash
Prendono in input una stringa di qualsiasi lunghezza e ritornano in output una stringa di una lunghezza finita completamente casuale.

Un minimo cambiamento nell'input impone un cambiamento anche completo dell'output.

L'hash è usato in quanto:
- Non si può risalire all'input della funzione.
- Se due input x e y sono differenti f(x) e f(y) sono obbligatoriamente differenti. Se accade che sono uguali allora l'algoritmo è stato rotto.

### Cos'è una blockchain
Una catena di blocchi o **nodi** che sono legati tra di loro.

Ciascun blocco ha:
- Un'header dove vi è l'hash del blocco precedente
    - Questo implica che rompere una hash nel tentativo di modificare il programma rompe la catena, tutti se ne accorgono -> immutabilità.

Bitcoin usa SHA-256 per esempio.

### Funzionamento del Bitoin
Principio della chiave privata e chiave pubblica.

La chiave privata è usata per firmare un messaggio.

La chiave pubblica invece può verificare la firma dell'altra entità.

Per trovare la chiave privata non esiste nessun algoritmo efficiente.

L'algoritmo che usa bitcon ECDSA.
#### Mining
I miner raccologono e verificano le transazioni, aggiungono l'has del blocco precedente cercando il nonce che soddisfi la proof of work (cioè che l'hash inzia con un tot di zeri). Il vincitore ottiene la ricompensa in bitcoin e le commissioni delle transazioni incluse.

Il mining mantiene il sistema onesto, l'energia crea denaro (non è prettamente vero, spoiler).

Se vengono trovati troppi blocchi, la difficoltà di mining aumenta (n di zeri richiesti aumenta).

#### Il consenso
Le transazioni vengono trasmette a tutti i nodi, che creano a loro volta un blocco con le nuove transazioni. Cercano di trovare la proof to work e il primo che la trova la manda agli altri e così via.

Una transazione bitcoin è sicura dopo circa 6 blocchi (1 ora), ogni blocco successivo rende difficile modificare le transazioni precedente (sicurezza probabilistica).
### Smart  Contract
Sono programmi compilati che vengono hostati su tutta la blockchain, sono trasparenti, immutabili e pubblici.

Gesticono la logica senza intermediari. Sono la base di tutto il mondo DeFi (Decentralized Finance) e molte blockchain moderne.
### Proof of Stake
Il bitcoin usa la Proof of Work: i nodi competono risolvendo problemi crittografici 

Avalanche usa la Proof of Stake.

I nodi bloccano una quantità di token (maggiori stake = maggiore probabilità di essere scelti per validare). Se si comporano male perdono i rewards, in cambio per rimanere online in maniera pulita ricevi token (ricompensa).

È come un sistema di "cauzione digitale" chi partecipa al consenso deve dimostrare di avere qualcosa da perdere.

IL consenso **Pos** funziona così:
- I validatori mettonoin stake i propri token
- Il protocollo seleziona casualmente chi propone il prossimo blocco
- Altri validatori confermano la validità.

## Avalache
È una blockchain di terza generazione basata su Proof of Stake e usa il nuovo meccanismo **gossip-based**.

Architettura Multi-chain:
- X-Chain, serve per scambiarsi assets
- P-Chain, validatori
- C-Chain, smart contract

Non è una singola blockchain, ma un ecosistema di reti interoperabili.
### Consenso
I nodi non votano tutti, si interrogano casualmente piccoli gruppi (gossip) e se una transazione riceve abbastanza consenso statistico, viene accettata.

Molto veloce, in meno di due secondi. Non bisogna fare mining ma è statisticamente distribuito il reward.


### Creare la tua blockchain
Una tua subnet: un insieme di validatori che raggiungono consenso su una o più blockchain.

Puoi scegliere:
- Proprie regole di consenso
- Proprio token nativo (per gas o governance)
- Parametri di rete dedicati (fee, limiti, privacy, compliance)
- Le subnet sono indipendenti, ma possono interagire con la Primary Network per interoperatibilità e sicurezza.

Una blockchain a Tor Vergata ad esempio può essere usata per prenotazioni ad esami.

Vantaggi:
- Scalabilità orizzontale, più subneto più capacità di rete.
- Personalizzazione Totale, consenso, governance, fee, etc...
- Interoperabile, connessione con la rete principale
- Isolamento

### Perché AValanche
!. Smart Contract sulla C-Chain (EVM Compatible che non so che cazzo vuol dire)
Facilità di sviluppo
- Possiamo usare 
2. Backend che interagisce con X-Chain e P-Chain
    - (X-Chain) Gestione e cambio di asset digitali
    - (P-Chain) gestione di validatori e creazione di subnet
    - Permettere di costruire una infrastruttura applicativa compelta dal layer...

3. Creare la propria blockchain personalizzata

## Solidity
Linguaggio orientato ad oggetti per gli smart contract
- Sintassi simile Javascript e C++ (CHE CAZZO DI LINGUAGGIO È SIMLE A C++ E JAVASCRIPT)
- Compilato in EVM
- Tipizzato e case sensitive

Sulla blockchain il codice è immutabile dopo il deploy, ogni esecuzione ha un costo in gas, i dati sono memorizzati in modo trasparente e persistente.

