Oltre a fornire astrazioni come processi e thread, spazi degli indirizzi e file, un sistema operativo controlla anche tutti i dispositivi di I/O del computer, inviando comandi ai dispositivi, intercettando gli interrupt e gestendo gli errori. 

Per prima cosa vedremo alcuni dei principi dell’hardware per l’I/O, poi analizzeremo il software per l’I/O in generale. Il software per l’I/O può essere strutturato in livelli (layer), dove ciascuno svolge un’attività ben precisa.
## 5.1 - Principi hardware dell'I/O
L’hardware per l’I/O viene considerato da punti di vista diversi: gli ingegneri elettronici lo giudicano in termini di chip, cavi, alimentatori, motori e di qualsiasi altro componente fisico. I programmatori sono interessati all’interfaccia disponibile al software: comandi accettati dall’hardware, funzioni eseguibili e possibili errori. Il nostro interesse è focalizzato sulla programmazione dell’hardware e non sul suo funzionamento interno.

(pagine riassunte: 0.75)
### 5.1.1 - Dispositivi di I/O
I dispositivi di I/O si dividono principalmente in due categorie: **dispositivi a blocchi** e **dispositivi a caratteri**.
1. **Dispositivi a blocchi**: Archiviazione di informazioni in blocchi di dimensioni fisse, ciascuno con il proprio indirizzo. I trasferimenti avvengono in unità di uno o più blocchi consecutivi. Ogni blocco può essere letto o scritto indipendentemente dagli altri. Esempi: dischi rigidi magnetici e unità SSD.
2. **Dispositivi a caratteri**: Gestione di un flusso di caratteri senza struttura a blocchi, non indirizzabili e senza operazioni di ricerca. Esempi: tastiere e stampanti.
Questa classificazione non è perfetta, poiché alcuni dispositivi non rientrano in queste categorie, come i clock, che non sono indirizzabili a blocchi e non gestiscono flussi di caratteri, ma generano solo interrupt a intervalli definiti.

Nonostante le limitazioni, la suddivisione in dispositivi a blocchi e a caratteri è utile per rendere il software del sistema operativo indipendente dal tipo di dispositivo, come nel caso del file system, che si occupa solo di dispositivi a blocchi astratti.

Le diverse velocità dei dispositivi di I/O rappresentano una sfida per il software, che deve garantire buone prestazioni nel trasferimento dei dati.

(pagine riassunte: 0.75)
### 5.1.2 - Controller dei dispositivi
I dispositivi di I/O sono composti da una componente meccanica e una elettronica. La parte elettronica è chiamata **controller del dispositivo** o **adattatore**, mentre la parte meccanica è il dispositivo stesso. Questa separazione consente una progettazione modulare e standardizzata.

Se l'interfaccia tra controller e dispositivo segue standard ufficiali (ANSI, IEEE, ISO) o _de facto_, i produttori possono creare controller o dispositivi compatibili.

Il flusso seriale di bit che esce dal dispositivo inizia con un **preambolo** (contenente informazioni come il numero dei cilindri e dei settori), seguito dai 4096 bit del settore e da una **checksum** o **codice di correzione degli errori** (**ECC**). Il controller converte questo flusso in un blocco di byte, esegue le correzioni degli errori e, dopo aver verificato l'integrità dei dati, copia il blocco nella memoria principale.

I monitor LCD hanno rapidamente sostituito i vecchi monitor a **tubo catodico** (**CRT**). I CRT utilizzano un raggio di elettroni per disegnare i pixel su uno schermo fluorescente. Gli LCD, rispetto ai CRT, sono più leggeri, consumano meno energia e sono più resistenti. Inoltre, gli schermi LCD moderni hanno una risoluzione così alta che l'occhio umano non può distinguere i singoli pixel.

(pagine riassunte: 1)
### 5.1.3 - Input/Output mappato in memoria
I dispositivi di I/O comunicano con la CPU tramite registri di controllo e buffer di dati. Il sistema operativo scrive nei registri per dare comandi al dispositivo e legge da essi per conoscere lo stato del dispositivo.

Due approcci per la comunicazione CPU-dispositivo sono: l'uso di **porte di I/O** e l'**I/O mappato in memoria**. Nel primo metodo, i registri di controllo hanno un numero di porta di I/O associato e sono accessibili tramite istruzioni speciali IN e OUT. Nel secondo metodo, i registri di controllo sono mappati nello spazio della memoria.

L'I/O mappato in memoria ha vantaggi come l'accessibilità dai linguaggi ad alto livello, la facilità di protezione dai processi utente e la possibilità di riferimento tramite istruzioni di memoria. Tuttavia, richiede complessità aggiuntiva per gestire la cache e potrebbe causare conflitti in sistemi con più bus.

L'utilizzo di porte di I/O è più semplice in termini di gestione della cache ma potrebbe causare ritardi nel bus della memoria dedicato. Soluzioni alternative includono l'uso di un dispositivo "spia" sul bus della memoria o il filtraggio degli indirizzi sul bridge PCI.

Entrambi gli approcci presentano compromessi e richiedono decisioni di progettazione ponderate, specialmente per garantire la compatibilità con sistemi legacy.

(pagine riassunte: 3.25)
### 5.1.4 - Direct memory access (DMA)
La CPU può comunicare con i controller dei dispositivi tramite l'accesso diretto alla memoria (DMA). Il DMA consente il trasferimento di dati tra memoria e dispositivi senza coinvolgere continuamente la CPU, migliorando l'efficienza.
#### Processo di DMA:
1. **Programmazione del Controller DMA**: La CPU configura il controller DMA impostando i registri per specificare il trasferimento dei dati.
2. **Richiesta di Lettura**: Il controller DMA invia una richiesta di lettura al controller del disco.
3. **Scrittura in Memoria**: Il controller DMA esegue l'operazione di scrittura in memoria.
4. **Conferma**: Il controller del disco invia un segnale di conferma al controller DMA.
5. **Aggiornamento degli Indirizzi**: Il controller DMA incrementa l'indirizzo di memoria e decrementa il conteggio dei byte.
#### Modalità di Operazione del DMA:
- **Cycle Stealing**: Il controller DMA ruba cicli di bus dalla CPU per trasferire i dati, rallentando leggermente la CPU.
- **Modalità Burst**: Il controller DMA acquisisce il bus per una serie di trasferimenti consecutivi, rilasciandolo poi. Questa modalità è più efficiente.
#### Fly-by Mode:
In questa modalità, il controller DMA dirige il trasferimento dei dati direttamente dalla periferica alla memoria principale senza intermediari, sebbene alcuni controller DMA utilizzino un ciclo extra per trasferire dati da dispositivo a dispositivo o da memoria a memoria.
#### Utilizzo di Buffer Interni:
I controller del disco utilizzano buffer interni per:
- Verificare la checksum prima del trasferimento per assicurarsi che i dati non siano corrotti.
- Gestire la velocità costante dei bit in arrivo dal disco, evitando perdite di dati.
#### Vantaggi e Svantaggi del DMA:
- **Vantaggi**: Efficienza nel trasferimento dei dati e riduzione del carico sulla CPU.
- **Svantaggi**: La CPU potrebbe essere più veloce del controller DMA in alcuni sistemi, rendendo il DMA superfluo e aumentando i costi di implementazione.
#### Applicazione nei Sistemi:
Il DMA è comune nei sistemi con controller dedicati e complessi, mentre nei sistemi a basso costo (come quelli embedded), la CPU potrebbe gestire direttamente i trasferimenti per risparmiare sui costi hardware.

(pagine riassunte: 3)
### 5.1.5 - Ancora sugli interrupt
Gli interrupt hardware funzionano come segue: quando un dispositivo di I/O completa un'operazione, invia un segnale di interrupt tramite una linea del bus al controller degli interrupt della scheda madre. Il controller decide come gestire l'interrupt in base alla priorità e, se necessario, lo invia alla CPU interrompendo l'attuale esecuzione. La CPU utilizza il numero dell'interrupt per accedere a una tabella, chiamata vettore degli interrupt, che contiene gli indirizzi delle procedure di servizio degli interrupt.

Durante un interrupt, la CPU salva le informazioni essenziali, come il contatore di programma, per poter riprendere l'esecuzione interrotta. Queste informazioni sono generalmente salvate nello stack, che può essere problematico se si tratta dello stack utente, portando a errori gravi. Usare lo stack del kernel è più sicuro, ma può comportare la necessità di cambiare il contesto della MMU e invalidare la cache, aumentando il tempo di gestione dell'interrupt.

Il software gioca un ruolo importante nella gestione degli interrupt, coordinando con l'hardware per garantire che le operazioni di I/O siano eseguite correttamente e efficientemente.
#### 5.1.5.1 - Interrupt precisi e imprecisi
In sistemi informatici moderni, soprattutto quelli che utilizzano pipeline e architetture superscalari, la gestione degli interrupt presenta sfide particolari. Nei vecchi sistemi, quando si verificava un interrupt, tutte le istruzioni fino a quel momento erano già state eseguite completamente. Tuttavia, con l'introduzione della pipeline e delle architetture superscalari, questo non è sempre vero.

Nei moderni processori, se si verifica un interrupt mentre la pipeline è piena, molte istruzioni potrebbero essere in vari stati di esecuzione. Anche in architetture superscalari, le istruzioni possono essere divise in micro-operazioni e eseguite in ordine sparso. Questo può portare a una situazione in cui, al momento dell'interrupt, molte istruzioni sono in vari stati di avanzamento, complicando la gestione dell'interrupt.

Un interrupt che lascia la macchina in uno stato ben definito è detto **interrupt preciso** e presenta quattro proprietà chiave. In primo luogo, il valore del program counter (PC) è salvato in un luogo noto. In secondo luogo, tutte le istruzioni eseguite prima del PC sono state completate, mentre nessuna istruzione successiva è stata eseguita. In terzo luogo, lo stato di esecuzione dell'istruzione puntata dal PC è noto. Infine, non vi è alcuna restrizione sull'avvio di istruzioni oltre a quella puntata dal PC, ma qualsiasi modifica apportata ai registri o alla memoria deve essere completamente annullata quando si verifica l'interrupt.

Al contrario, un interrupt che non soddisfa questi requisiti è detto **interrupt impreciso**, il che rende la gestione dell'interrupt più complessa. In particolare, le macchine con interrupt imprecisi tendono a salvare molte informazioni sullo stack per consentire al sistema operativo di capire lo stato della macchina al momento dell'interrupt.

Alcune macchine, come la famiglia x86, supportano interrupt precisi per garantire la compatibilità con il software esistente. Tuttavia, questo comporta una maggiore complessità nella logica dell'interrupt all'interno della CPU.

Infine, è importante notare che anche le istruzioni transitorie, annullate a seguito di un'interrupt, possono rappresentare un rischio per la sicurezza, poiché lasciano tracce nella microarchitettura della CPU che potrebbero essere sfruttate da potenziali attaccanti.

(pagine riassunte: 3.5)
## 5.2 - Principi del software di I/O
Per prima cosa analizzeremo gli obiettivi del software di I/O e successivamente i diversi modi in cui può essere gestito l’I/O dal punto di vista del sistema operativo.
### 5.2.1 - Obbiettivi del software di I/O
Nella progettazione del software di I/O, uno dei concetti fondamentali è l'**indipendenza dal dispositivo**, che permette di scrivere programmi che accedono a qualsiasi dispositivo di I/O senza dover specificare quale dispositivo utilizzare. Il sistema operativo si occupa delle differenze tra i dispositivi e delle sequenze di comandi necessarie per leggere o scrivere.

L'indipendenza dal dispositivo è collegata alla denominazione uniforme (**uniform naming**), che consente di utilizzare nomi di file o dispositivi come semplici stringhe o numeri, indipendentemente dal dispositivo stesso. Ad esempio, una penna USB può essere **montata** in una directory specifica, e copiare un file in quella directory significa copiarlo nella penna USB.

La **gestione degli errori** è un'altra questione importante: gli errori dovrebbero essere gestiti il più vicino possibile all'hardware. Se un controller rileva un errore di lettura, dovrebbe cercare di correggerlo autonomamente; altrimenti, il driver del dispositivo dovrebbe intervenire, magari tentando una rilettura del blocco.

I trasferimenti di I/O possono essere **sincroni** (bloccanti) o **asincroni** (gestiti tramite interrupt). L'I/O fisico è principalmente asincrono, ma i programmi utente sono più facili da scrivere se le operazioni di I/O sono bloccanti. Il sistema operativo deve quindi far sembrare le operazioni asincrone come se fossero bloccanti per i programmi utente. Tuttavia, alcune applicazioni ad alte prestazioni necessitano di controllare i dettagli dell'I/O, per cui l'I/O asincrono è reso disponibile.

La **bufferizzazione** è un'altra sfida: spesso i dati in uscita da un dispositivo non possono essere memorizzati direttamente nella destinazione finale. Alcuni dispositivi, come quelli audio digitali, richiedono la bufferizzazione per sincronizzare la velocità di riempimento e svuotamento del buffer ed evitare il buffer underrun.

Infine, i dispositivi possono essere condivisibili o dedicati. Dischi e SSD possono essere usati contemporaneamente da più utenti, mentre i dispositivi dedicati, come alcune stampanti o unità nastro, richiedono una gestione specifica per evitare problemi come i deadlock. Il sistema operativo deve gestire entrambi i tipi di dispositivi per garantire un funzionamento efficiente e privo di errori.

(pagine riassunte: 1.25)
### 5.2.2 - I/O programmato
L'I/O programmato è un metodo di esecuzione dell'I/O in cui la CPU si occupa interamente del processo. Un esempio per illustrare questo metodo può essere il caso di un processo utente che voglia scrivere una stringa di otto caratteri ("ABCDEFGH") su una stampante tramite un'interfaccia seriale. 
1. **Preparazione e Richiesta della Risorsa:**
   - Il processo utente crea un buffer con la stringa e fa una chiamata di sistema per aprire la stampante.
   - Se la stampante è già in uso, la chiamata può fallire o il processo può restare bloccato fino a quando la stampante diventa disponibile.
2. **Scrittura dei Dati:**
   - Una volta ottenuta la stampante, il sistema operativo copia il buffer dalla memoria utente allo spazio del kernel.
   - Poi, controlla se la stampante è pronta. Se non lo è, attende.
   - Quando la stampante è pronta, il sistema operativo copia il primo carattere nel registro dei dati della stampante, attivandola.
3. **Controllo e Polling:**
   - Dopo aver copiato il primo carattere, il sistema operativo verifica se la stampante è pronta per ricevere il prossimo carattere.
   - Questo viene fatto leggendo un secondo registro che indica lo stato della stampante.
   - Il ciclo continua con la CPU che controlla continuamente lo stato della stampante e copia i caratteri successivi fino a completare la stampa della stringa.

L'aspetto chiave dell'I/O programmato è che la CPU, dopo aver inviato un carattere, interroga costantemente il dispositivo per verificare se è pronta a ricevere il prossimo carattere, un processo noto come **polling** o **busy waiting**. Questo metodo è semplice ma inefficiente, poiché la CPU rimane occupata fino al completamento dell'I/O.

(pagine riassunte: 1.5)
### 5.2.3 - I/O guidato dagli interrupt
Consideriamo una stampante che stampa un carattere alla volta senza buffer, con una velocità di 100 caratteri al secondo, ovvero 10 ms per carattere. In questo scenario, dopo aver scritto un carattere nel registro dei dati della stampante, la CPU rimane inattiva per 10 ms in attesa che la stampante sia pronta per il carattere successivo. Questo tempo di inattività è sufficiente per eseguire un cambio di contesto e far eseguire altri processi per quasi tutto il periodo di attesa, evitando sprechi.

Per sfruttare questo tempo, si possono utilizzare gli **interrupt**. Dopo che il processo utente richiede la stampa di una stringa tramite una chiamata di sistema, il buffer della stringa viene copiato nello spazio del kernel. La CPU copia il primo carattere nella stampante non appena questa è pronta. Successivamente, la CPU può eseguire altri processi tramite lo scheduler mentre il processo di stampa rimane bloccato fino al completamento della stampa.

Quando la stampante ha finito di stampare un carattere ed è pronta per il successivo, genera un interrupt. Questo interrompe il processo attuale, salvando il suo stato. La procedura di servizio di interrupt della stampante viene eseguita: se ci sono ancora caratteri da stampare, il successivo viene inviato alla stampante, l’interrupt viene riconosciuto e il processo interrotto riprende da dove era stato lasciato. Se invece non ci sono più caratteri, il gestore dell’interrupt sblocca il processo utente che aveva richiesto la stampa.

(pagine riassunte: 1)
### 5.2.4 - I/O con DMA
Uno svantaggio dell'I/O guidato dagli interrupt è che avviene un interrupt per ogni carattere, causando un notevole spreco di tempo della CPU. Una soluzione a questo problema è l'uso del **DMA**. In questo schema, il controller DMA gestisce l'invio dei caratteri alla stampante uno alla volta, senza coinvolgere la CPU principale. Questa tecnica richiede un controller DMA speciale, ma permette alla CPU di eseguire altre operazioni durante l'I/O.

Il principale vantaggio del DMA è la riduzione del numero di interrupt da uno per carattere a uno per buffer, migliorando notevolmente l'efficienza quando si trattano molti caratteri e gli interrupt sono lenti. Tuttavia, il controller DMA è generalmente più lento della CPU principale, quindi se non è in grado di operare alla velocità massima del dispositivo, o se la CPU non ha altre operazioni da eseguire durante l'attesa dell'interrupt del DMA, potrebbe essere preferibile utilizzare l'I/O gestito dagli interrupt o l'I/O programmato. Nonostante ciò, nella maggior parte dei casi, l'uso del DMA risulta vantaggioso.

(pagine riassunte: 0.25)
## 5.3 - Livelli del software di I/O
Il software di I/O è generalmente organizzato in quattro livelli ciascuno dei quali ha una funzione ben definita da eseguire e un’interfaccia ben definita verso i livelli adiacenti. La funzionalità e le interfacce sono diverse a seconda del sistema, così l’analisi seguente, che esamina tutti i livelli partendo dal basso, non è specifica di una macchina.
### 5.3.1 - Gestori  degli interrupt
L'I/O programmato è utile in alcuni casi, ma per la maggior parte delle operazioni di I/O, l'uso degli interrupt è inevitabile. Il metodo migliore per gestirli è far sì che il driver che ha iniziato un'operazione di I/O si blocchi fino al completamento dell'operazione e al verificarsi dell'interrupt. Quando avviene l'interrupt, la procedura di gestione deve completare le sue operazioni e sbloccare il driver in attesa. Questo metodo funziona meglio se i driver sono strutturati come processi con i loro stati, stack e contatori di programma.

L'elaborazione di un interrupt va oltre la semplice gestione dell'interrupt e il ritorno al processo precedente. Il sistema operativo deve eseguire una serie di passaggi, che includono:

1. Salvataggio di tutti i registri non ancora salvati dall'interrupt hardware.
2. Impostazione di un contesto per la procedura di servizio dell'interrupt, che potrebbe coinvolgere TLB, MMU e tabelle delle pagine.
3. Impostazione di uno stack per la procedura di servizio dell'interrupt.
4. Conferma al controller degli interrupt o riabilitazione degli interrupt se manca un controller centralizzato.
5. Copia dei registri salvati nella tabella dei processi.
6. Esecuzione della procedura di servizio dell'interrupt, estraendo informazioni dai registri del controller del dispositivo.
7. Scelta del prossimo processo da eseguire, privilegiando quelli a priorità alta sbloccati dall'interrupt.
8. Impostazione del contesto della MMU per il nuovo processo da eseguire.
9. Caricamento dei nuovi registri del processo, incluso il PSW.
10. Avvio dell'esecuzione del nuovo processo.

Questa elaborazione è complessa e richiede molte istruzioni della CPU, soprattutto su macchine con memoria virtuale, dove è necessario gestire le tabelle delle pagine, il TLB e la cache della CPU.

(pagine riassunte: 1.5)
### 5.3.2 - Driver di dispositivo
Il controllo dei dispositivi di I/O richiede specifici codici chiamati **driver di dispositivo**. Questi driver, solitamente forniti dal produttore, sono necessari per ogni sistema operativo. Un driver di dispositivo gestisce generalmente un tipo o una classe di dispositivi, anche se possono esistere eccezioni. Ad esempio, i driver USB sono strutturati su uno stack, con vari livelli che gestiscono diverse funzioni, dal livello hardware fino alle API di alto livello.

Per accedere all'hardware del dispositivo, i driver devono solitamente essere parte del kernel del sistema operativo, isolando così il kernel dai driver stessi per migliorare l'affidabilità del sistema. I progettisti di sistemi operativi devono garantire un modello ben definito per l'interazione dei driver con il sistema. I driver sono classificati principalmente in due categorie: **dispositivi a blocchi** (es. dischi) e **dispositivi a caratteri** (es. stampanti).

Storicamente, i sistemi operativi includevano tutti i driver necessari in un unico binario. Tuttavia, con l'aumento della varietà di dispositivi I/O nei personal computer, questo modello è diventato inefficace. Ora, i driver vengono caricati dinamicamente durante l'esecuzione del sistema operativo.

Le principali funzioni di un driver di dispositivo includono l'accettazione di richieste di lettura e scrittura e la loro esecuzione concreta. I driver devono inoltre gestire vari aspetti come la validazione dei parametri di input, il controllo dello stato del dispositivo, l'invio di comandi al controller del dispositivo e la gestione degli interrupt.

Quando un dispositivo è occupato, le richieste vengono messe in coda. Se un dispositivo è inattivo, il driver verifica lo stato dell'hardware per vedere se può gestire immediatamente la richiesta. I driver devono gestire anche situazioni in cui un dispositivo viene rimosso o aggiunto "a caldo".

I driver non possono fare chiamate di sistema dirette, ma possono interagire con il kernel tramite chiamate a specifiche procedure del kernel per gestire vari aspetti come l'MMU, i timer, il controller DMA e il controller degli interrupt.

(pagine riassunte: 3.5)
### 5.3.3 - Software per l'I/O indipendente dal dispositivo
Sebbene parte del software per l’I/O sia specifico di un determinato dispositivo, altre parti sono indipendenti dal dispositivo stesso (device independent). Il limite esatto fra i driver e il software indipendente dal dispositivo dipende dal sistema e dal dispositivo, poiché alcune funzioni che potrebbero essere svolte in modalità indipendente dal dispositivo sono effettivamente svolte dai driver, sia per efficienza sia per altre ragioni.

La funzione base del software indipendente dal dispositivo è quella di eseguire tutte quelle funzioni di I/O trasversali a tutti i dispositivi e di fornire un’interfaccia uniforme al software a livello utente.
#### 5.3.3.1 - Interfacciamento uniforme dei driver dei dispositivi
Un problema centrale nei sistemi operativi è uniformare i dispositivi e i driver, evitando modifiche al sistema operativo per ogni nuovo dispositivo. L'interfaccia tra i driver e il sistema operativo deve essere standardizzata per facilitare l'integrazione di nuovi driver.

Un'interfaccia diversa per ogni driver richiederebbe notevoli sforzi di programmazione per l'integrazione. Invece, un'interfaccia comune per tutti i driver semplifica l'inserimento di nuovi driver, che devono solo conformarsi a questa interfaccia standard. Anche se i dispositivi non sono identici, i tipi di dispositivi sono pochi e le loro differenze sono gestibili.

Il sistema operativo definisce per ogni classe di dispositivi un insieme di funzioni che i driver devono supportare. Ad esempio, per i dischi, queste funzioni includono lettura, scrittura, accensione, spegnimento e formattazione. Il sistema operativo registra la tabella di puntatori a funzioni del driver, permettendo chiamate indirette alle funzioni necessarie. Questa tabella definisce l'interfaccia tra il driver e il sistema operativo, e tutti i dispositivi di una classe devono rispettarla.

Anche la denominazione dei dispositivi di I/O contribuisce all'uniformità dell'interfaccia. In UNIX, ad esempio, un nome come _/dev/disk0_ identifica univocamente il dispositivo tramite il **major device number** e il **minor device number**. Il numero di dispositivo primario localizza il driver appropriato, mentre il numero secondario specifica l'unità da leggere o scrivere.

Infine, la protezione dell'accesso ai dispositivi è gestita come per i file. Sia in UNIX sia in Windows, i dispositivi appaiono nel file system come oggetti denominati, e le regole di protezione dei file si applicano anche ai dispositivi di I/O. L'amministratore di sistema può quindi impostare i permessi adeguati per ciascun dispositivo.
#### 5.3.3.2 - Buffering
Il buffering è una tecnica cruciale per gestire l'I/O sia per i dispositivi a blocchi sia per quelli a caratteri, ma presenta sfide significative. Ecco le strategie di buffering:
1. **Buffering con processo utente bloccato**: Un processo utente può eseguire una chiamata di sistema read per attendere un carattere in ingresso, ma riavviare il processo per ogni carattere è inefficiente. Migliorare questa tecnica prevedendo un buffer di _n_ caratteri nello spazio utente può aumentare l'efficienza, ma introduce problemi se il buffer viene paginato fuori.
2. **Buffering nel kernel**: Creare un buffer nel kernel permette di accumulare i caratteri prima di copiarli in blocco nel buffer dell'utente. Questo metodo è più efficiente, ma deve gestire i caratteri che arrivano mentre il buffer dell'utente viene paginato.
3. **Buffering doppio**: Utilizzando due buffer nel kernel, uno per raccogliere nuovi caratteri mentre l'altro viene copiato nello spazio utente, si può mantenere l'efficienza e gestire i caratteri in arrivo senza perdita.
4. **Buffer circolare**: Un buffer circolare usa due puntatori per gestire la scrittura e la lettura dei dati in un'area di memoria continua, migliorando la gestione dell'I/O in tempo reale.
5. **Buffering nell'output**: Per l'output, come l'invio di dati tramite un modem, il buffering nel kernel permette di sbloccare immediatamente il processo utente. Il kernel gestisce poi l'I/O effettivo, evitando problemi di sincronizzazione.
6. **Effetti negativi del buffering e copia dei dati**: Ogni operazione di buffering e copia dei dati introduce un overhead. Ad esempio, nella trasmissione su rete, il pacchetto viene copiato dal buffer dell'utente al buffer del kernel, poi al buffer del controller, e infine inviato. Questo processo rallenta la velocità di trasmissione a causa delle multiple copie necessarie.

In sintesi, il buffering è essenziale per un I/O efficiente, ma deve essere gestito con attenzione per evitare problemi di prestazioni dovuti a paginazione, sincronizzazione e overhead di copia dei dati.
#### 5.3.3.3 - Segnalazione degli errori
Gli errori di I/O sono comuni e devono essere gestiti dal sistema operativo in modo efficiente. Ci sono diverse classi di errori, ognuna con una gestione specifica:
1. **Errori di programmazione**: Si verificano quando un processo richiede operazioni impossibili, come scrivere su un dispositivo di input o leggere da un dispositivo di output, fornire indirizzi di buffer non validi, o specificare dispositivi inesistenti. In questi casi, il sistema operativo invia un codice d'errore al chiamante.
2. **Errori di I/O propriamente detti**: Questi includono tentativi di scrivere su blocchi danneggiati o leggere da dispositivi spenti. Il driver del dispositivo tenta di gestirli; se non riesce, il problema passa al software indipendente dal dispositivo.
	   - **Gestione interattiva**: Se c'è un utente interattivo, il sistema può chiedere all'utente come procedere (riprovare, ignorare, terminare il processo).
	   - **Gestione automatica**: Senza un utente disponibile, il sistema probabilmente riporta un codice d'errore e fallisce la chiamata di sistema.
1. **Errori critici**: Alcuni errori, come la distruzione di strutture dati critiche (es. directory radice o lista dei blocchi liberi), non possono essere risolti semplicemente. In questi casi, il sistema potrebbe dover visualizzare un messaggio d'errore e terminare.

Queste strategie assicurano che il sistema operativo possa gestire gli errori di I/O in modo robusto e appropriato, minimizzando l'impatto sull'utente e sul sistema.
#### 5.3.3.4 - Allocazione e rilascio dei dispositivi dedicati
Alcuni dispositivi, come le stampanti, possono essere utilizzati da un solo processo alla volta. Il sistema operativo gestisce le richieste di accesso a questi dispositivi, accettandole o rifiutandole in base alla disponibilità. 
**Metodi di gestione delle richieste:**
1. **Accesso tramite file speciali**: I processi fanno una `open` su file speciali che rappresentano i dispositivi. La `close` di questi file rilascia il dispositivo.
2. **Meccanismi speciali di richiesta e rilascio**: Se un dispositivo non è disponibile, il tentativo di acquisirlo blocca il processo chiamante, mettendolo in una coda. Quando il dispositivo diventa disponibile, il primo processo in coda lo acquisisce e continua l'esecuzione.

Questi metodi garantiscono che i dispositivi dedicati siano utilizzati in modo ordinato e senza conflitti tra i processi.
#### 5.3.3.5 - Dimensione dei blocchi indipendente dal dispositivo
Gli SSD e i dischi possono avere pagine flash e settori di diverse dimensioni. Il software indipendente dal dispositivo ha il compito di uniformare queste differenze, fornendo una dimensione di blocco uniforme ai livelli superiori del sistema operativo. Questo consente ai livelli superiori di interagire con dispositivi astratti usando la stessa dimensione di blocco logico, indipendentemente dalle dimensioni fisiche dei settori. Allo stesso modo, i dispositivi a caratteri che forniscono dati in unità diverse possono essere gestiti in modo da occultare queste differenze, rendendo l'interazione più coerente.

(pagine riassunte: 5.25)
### 5.3.4 - Software di I/O nello spazio utente


(pagine riassunte: 1.5)
## 5.4 - Dischi

### 5.4.1 - Hardware dei dischi


(pagine riassunte: 6.25)
### 5.4.2 - Formattazione dei dischi


(pagine riassunte: 3.5)
### 5.4.3 - Algoritmi di scheduling del braccio del disco


(pagine riassunte: 3.25)
### 5.4.4 - Gestione degli errori


(pagine riassunte: 2.5)
### 5.4.5 - Memoria stabile


(pagine riassunte: 3)
## 5.5 - Clock

### 5.5.1 - Hardware del clock


(pagine riassunte: 1.25)
### 5.5.2 - Software del clock


(pagine riassunte: 2.75)
### 5.5.3 - Soft timer


(pagine riassunte: 1.5)
## 5.6 - Interfacce utente: tastiera, mouse e monitor

### 5.6.1 - Software di input


(pagine riassunte: 5)
### 5.6.2 - Software di output


(pagine riassunte: 15.75)
## 5.7 - Thin client


(pagine riassunte: 1.25)
## 5.8 - Gestione del risparmio energetico


(pagine riassunte: 1)
### 5.8.1 - Problemi relativi all'hardware


(pagine riassunte: 1.5)
### 5.8.2 - Problemi relativi al sistema operativo


(pagine riassunte: 5.25)
### 5.8.3 - Questioni relative ai programmi applicativi


(pagine riassunte: 1)
## 5.9 - Stato della ricerca sull'input/output


(pagine riassunte: 1.5)

[[|Prossimo Capitolo]]