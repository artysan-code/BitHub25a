# Scheduling
Quando più processi/thread competono per la CPU, lo **scheduler** decide quale eseguire successivamente seguendo un **algoritmo di scheduling**. Molti problemi valgono sia per processi sia per thread; lo scheduling a livello kernel avviene **per thread**, indipendentemente dal processo di appartenenza, e lo scheduling dei thread pone sfide specifiche (vedi [[#Scheduling dei thread]]). Questa nota tratta gli algoritmi per i diversi ambienti (batch, interattivo, real-time) e lo scheduling dei thread. Prerequisito: gli [[03 - Processi e Thread#Stati di un processo|stati di un processo]] e la [[04 - Sincronizzazione|sincronizzazione]].
## Il problema dello scheduling
Storicamente nei sistemi **batch** lo scheduling era **lineare** (il job successivo sul nastro); con la **multiprogrammazione** è diventato complesso per la concorrenza tra utenti. Sui personal computer tradizionalmente l'attenzione era rivolta alla **reattività** dell'applicazione con cui l'utente interagiva; nei sistemi moderni, però, molte applicazioni e servizi in background competono comunque per la CPU, e lo scheduling deve **bilanciare reattività, prestazioni ed efficienza energetica** *(slide 2026-2027; slide 2025-2026: spesso un solo processo è attivo e la CPU **raramente** è la risorsa scarsa)*. Nei **server** e nei dispositivi a **batteria** (IoT, smartphone, nodi di sensori) lo scheduling torna vitale (anche per ottimizzare i consumi).
### Comportamento dei processi
I processi alternano **fasi di calcolo (CPU burst)** e **attese di I/O**:
- **Compute-bound (CPU-bound)**: burst di CPU lunghi, attese di I/O infrequenti.
- **I/O-bound**: burst di CPU brevi, attese di I/O frequenti (sono tali per la **bassa necessità di calcolo**, non per la durata dell'I/O).

Con CPU sempre più veloci i processi tendono a essere più **I/O-bound**, quindi lo scheduling deve servire rapidamente i processi I/O-bound senza penalizzare troppo quelli CPU-bound. Storicamente le prestazioni delle CPU sono cresciute più rapidamente di quelle dei dischi magnetici, rendendo spesso l'I/O un collo di bottiglia; gli SSD sostituiscono i dischi nei PC, ma i data center usano ancora HDD per il costo per bit. Lo scheduling dipende dal contesto: ciò che funziona per un dispositivo può non funzionare per un altro, e il panorama tecnologico è in continua evoluzione *(slide 2026-2027; slide 2025-2026: CPU e dischi magnetici non stanno avanzando rapidamente in velocità)*.
### Quando interviene lo scheduler
- Alla **creazione** di un nuovo processo (eseguire il padre o il figlio? Se entrambi sono pronti, può essere scelto chiunque).
- All'**uscita** di un processo (scegliere il prossimo; se nessuno è pronto, eseguire il processo *idle*).
- Al **blocco** di un processo (I/O, semaforo…); a volte la causa del blocco può influire sulla scelta.
- A un **interrupt di I/O** (un processo potrebbe essere diventato pronto: si decide se eseguire il processo appena pronto, il precedente o un altro).
### Preemptive vs non-preemptive
- **Non-preemptive (senza prelazione)**: il processo mantiene la CPU **finché termina, si blocca o la rilascia volontariamente**; un interrupt non comporta, di per sé, la sostituzione forzata del processo in esecuzione *(slide 2025-2026: gli interrupt del clock non causano decisioni)*.
- **Preemptive (con prelazione)**: il processo esegue per un **tempo massimo** definito; se non termina viene **sospeso**. Richiede un **interrupt del clock** ed è fondamentale per evitare che un processo (o una syscall lenta) monopolizzi la CPU. Il sistema operativo può interrompere un processo anche se non ha terminato né si è bloccato: la prelazione può avvenire, ad esempio, alla scadenza del quanto o quando diventa pronto un processo a **priorità superiore**, e gli interrupt del timer permettono di riprendere periodicamente il controllo della CPU *(slide 2026-2027)*.

**Importanza della prelazione**: migliora la reattività dei sistemi interattivi e impedisce a un processo di monopolizzare la CPU; la **prelazione del kernel** permette, quando le condizioni lo consentono, di interrompere anche l'esecuzione di codice del kernel *(slide 2026-2027; slide 2025-2026: rilevante per le applicazioni e per i kernel; in un kernel con prelazione lo scheduler può forzare un cambio di contesto)*. Serve in modo diverso nei tre ambienti: nei sistemi **batch** (ideali per attività aziendali periodiche) sono accettabili algoritmi senza prelazione, con priorità a prestazioni efficienti; nei sistemi **interattivi** la prelazione è fondamentale per prevenire la monopolizzazione della CPU (server e utenti multipli); nei sistemi **real-time** si può usare scheduling con o senza prelazione, a seconda dell'algoritmo e dei requisiti (vedi [[#Scheduling nei sistemi real-time]]; slide 2025-2026: prelazione non sempre necessaria). *(Slide 2025-2026: nel caso senza prelazione, dopo un interrupt si ripristina il processo precedente, a meno che non ci sia una priorità superiore.)*

> [!question] Domanda tipica d'esame
> - **D:** Differenza tra scheduling con e senza prelazione; quando è accettabile rinunciare alla prelazione? **R:** **Senza prelazione** il processo scelto esegue fino al blocco o al rilascio volontario; **con prelazione** esegue per un tempo massimo (quanto) e poi viene sospeso (serve un interrupt del clock). Si può rinunciare alla prelazione nei sistemi **batch** (job non interattivi) e in molti sistemi **real-time**, dove i processi sanno di non poter girare a lungo e si bloccano rapidamente *(slide 2025-2026; slide 2026-2027: nei sistemi real-time si può usare scheduling con o senza prelazione, secondo algoritmo e requisiti)*.
### Costo del context switch
Il **cambio di contesto** comporta alcuni costi: nei cambi gestiti dal kernel, l'intervento dello scheduler per selezionare il prossimo thread; il salvataggio dello stato del thread uscente e il ripristino di quello entrante; il possibile cambio dello **spazio di indirizzamento** quando si passa tra processi distinti; possibili effetti sulle **cache** e sul **TLB** (vedi [[06 - Gestione della Memoria]]). Il cambio tra thread dello stesso processo non richiede normalmente un cambio dello spazio di indirizzamento *(slide 2026-2027; slide 2025-2026: passaggio user→kernel, salvataggio dello stato, esecuzione dell'algoritmo di scheduling, cambio della mappa di memoria, potenziale invalidazione della cache)*. Troppe commutazioni sprecano CPU: minimizzarne il numero è essenziale per l'efficienza del sistema.
### Obiettivi degli algoritmi
| Ambiente        | Obiettivi specifici                                            |
| --------------- | -------------------------------------------------------------- |
| **Batch**       | massimo **throughput**, minimo **tempo di turnaround** (dall'arrivo del job al completamento), alto utilizzo CPU |
| **Interattivo** | **tempo di risposta** rapido, proporzionalità alle aspettative |
| **Real-time**   | rispetto delle **scadenze**, prevedibilità                     |

Per **tutti**: **equità** (CPU equa a tutti), imposizione della **policy**, bilanciamento (tenere attivi tutti i componenti). L'equità è fondamentale in ogni scenario; in un sistema batch è ideale **combinare** processi CPU-bound e I/O-bound.
## Scheduling nei sistemi batch
### First-Come First-Served (FCFS)
Algoritmo **senza prelazione**: i processi ricevono la CPU **nell'ordine di arrivo**, gestiti con una singola coda (lista). Un processo bloccato, quando torna pronto, viene rimesso **in fondo** alla coda. Semplice ed equo per ordine di arrivo, ma con prestazioni **non ottimali** in scenari misti: un processo CPU-bound può far attendere a lungo molti processi I/O-bound.

> [!example] FCFS e processi I/O-bound *(extra, non da slide)*
> Un processo CPU-bound che gira per 1 s può far sì che molti processi I/O-bound impieghino circa 1000 s per terminare, invece dei circa 10 s che richiederebbero con un algoritmo di scheduling **con prelazione** che interrompa il processo CPU-bound dopo il suo quanto.
### Shortest Job First (SJF)
Algoritmo batch **senza prelazione** che esegue per primo il **job più breve**; richiede di **conoscere in anticipo** i tempi di esecuzione.

> [!example] SJF minimizza il turnaround
> Quattro job con tempi 8, 4, 4, 4 minuti. In ordine d'arrivo (8,4,4,4) i turnaround sono 8, 12, 16, 20 → media **14**. Con SJF (4,4,4,8) sono 4, 8, 12, 20 → media **11**.

**Ottimalità**: SJF minimizza il tempo di turnaround medio **solo quando tutti i job sono disponibili contemporaneamente** e i tempi di esecuzione sono noti; il turnaround è il tempo trascorso dall'arrivo del job al suo completamento. Se i job arrivano in momenti diversi, **non** è necessariamente ottimale.

> [!example] SJF non ottimale con arrivi sfasati
> Cinque job A–E con tempi di esecuzione 2, 4, 1, 1, 1 minuti e arrivi a $t = 0, 0, 3, 3, 3$. Due sequenze di esecuzione producono medie diverse: una sequenza dà media $4{,}6$, un'altra dà media $4{,}4$. Verifica: `A,B,C,D,E` dà turnaround 2, 6, 4, 5, 6 (media 4,6); `B,C,D,E,A` dà 4, 2, 3, 4, 9 (media 4,4). Se la CPU potesse restare ferma fino a $t=3$, `A,C,D,E,B` darebbe 3,6 *(extra, non da slide)*. Il fatto che esistano due ordini con medie diverse dimostra che SJF **non è ottimale** quando i job non arrivano tutti allo stesso istante. *(I valori 4,6 e 4,4 sono quelli delle slide e sono entrambi ricostruiti qui sopra: gli ordini sono una ricostruzione compatibile con le medie, la slide non li riporta; l'[[05 - Scheduling (Esercizi)#Es. 2 — SJF non è ottimale con arrivi sfasati|esercizio svolto]] li verifica passo-passo.)*
### Shortest Remaining Time Next (SRTN)
Versione **con prelazione** di SJF: sceglie sempre il processo con il **tempo rimanente più breve**. All'arrivo di un nuovo job, se il suo tempo totale è inferiore al tempo rimanente del processo corrente, quest'ultimo viene sospeso. Garantisce servizio rapido ai job brevi (richiede comunque tempi noti in anticipo).

> [!question] Domanda tipica d'esame
> - **D:** Quali parametri si ottimizzano nello scheduling per sistemi batch? Descrivere FCFS, SJF e SRTN con pregi e limiti. **R:** Obiettivi batch: **throughput**, minimo **tempo di turnaround**, alto **utilizzo della CPU**. **FCFS** (senza prelazione, ordine d'arrivo): semplice ed equo, ma un processo CPU-bound fa attendere a lungo gli I/O-bound. **SJF** (senza prelazione, job più breve per primo): minimizza il turnaround medio *se tutti i job sono disponibili insieme*, ma richiede di conoscere i tempi in anticipo. **SRTN** (versione con prelazione di SJF, tempo rimanente più breve): serve rapidamente i job brevi, ma può causare starvation dei lunghi *(extra, non da slide: la slide 2025-2026 cita la starvation dei processi lunghi per SJF nei sistemi interattivi, non per SRTN; la slide 2026-2027 non la cita)*.

> [!info] Mettiti alla prova
> Esercizi di calcolo svolti passo-passo in [[05 - Scheduling (Esercizi)]]:
> - **FCFS vs SJF** (turnaround e attesa medi) → [[05 - Scheduling (Esercizi)#Es. 1 — FCFS vs SJF (turnaround e attesa medi)|Es. 1]];
> - **SJF non ottimale** con arrivi sfasati → [[05 - Scheduling (Esercizi)#Es. 2 — SJF non è ottimale con arrivi sfasati|Es. 2]];
> - **SRTN** con prelazione → [[05 - Scheduling (Esercizi)#Es. 3 — SRTN (Shortest Remaining Time Next, con prelazione)|Es. 3]].
## Scheduling nei sistemi interattivi
Nei sistemi interattivi, a differenza dei batch, conta soprattutto il **tempo di risposta** percepito dall'utente: la **prelazione** diventa essenziale per evitare che un singolo processo monopolizzi la CPU.
### Round-Robin
Uno degli algoritmi più vecchi, semplici ed equi. Ogni processo riceve un intervallo di tempo, il **quanto** (quantum); se non termina entro il quanto, la CPU passa (per prelazione) al processo successivo nella lista; se si blocca o termina prima, il passaggio è immediato. Implementazione: una lista dei processi eseguibili, il processo esaurito va in **fondo** alla lista.

> [!warning] La durata del quanto è un compromesso
> Con cambio di contesto di 1 ms e quanto di 4 ms si spreca il **20%** della CPU in overhead. **Quanto troppo breve** → troppi cambi di contesto (inefficiente); **quanto troppo lungo** → riduce l'overhead ma peggiora la reattività (la slide cita 5 secondi di attesa per un breve comando in un server affollato). Esempio *(extra, non da slide: i valori 100 ms e 50 richieste)*: con un quanto da $100\,\text{ms}$ e 50 richieste a un server, l'ultimo utente può attendere fino a $50 \times 100\,\text{ms} = 5\,\text{s}$ se tutti gli altri usano interamente il loro quanto. Se il quanto è maggiore del tempo medio di burst di CPU, la prelazione avviene di rado, perché molti processi si bloccano prima. Compromesso ragionevole: **20-50 ms**.

> [!question] Domanda tipica d'esame
> - **D:** Come funziona il Round-Robin e qual è il compromesso nella scelta del quanto? **R:** Ogni processo riceve un **quanto**; se non termina entro il quanto, la CPU passa per prelazione al successivo e il processo torna in **fondo** alla coda. Compromesso: quanto troppo **breve** → troppi context switch (overhead, es. 20% con switch 1 ms e quanto 4 ms); quanto troppo **lungo** → tempi di risposta scadenti (degenera verso FCFS) *(extra, non da slide)*. Valore tipico **20–50 ms**.
### Scheduling a priorità
Round-robin tratta tutti i processi come ugualmente importanti, ma spesso serve una **gerarchia**. Vale anche su un singolo PC: un daemon di posta elettronica avrebbe meno priorità di un video in tempo reale. Nello scheduling a priorità ogni processo ha una **priorità** e si esegue quello pronto con priorità più alta. Per evitare che i processi ad alta priorità monopolizzino la CPU, la priorità del processo in esecuzione può **diminuire nel tempo**: se scende sotto quella del processo successivo, avviene un cambio di processo. In alternativa si assegna un quanto massimo: al suo esaurirsi si passa al processo con priorità appena inferiore.
- **Priorità statica**: es. gerarchie militari, costi nel data center.
- **Priorità dinamica**: es. basata sull'uso della CPU (favorisce i processi I/O-bound).

**Classi di priorità**: i processi si raggruppano in classi; si fa scheduling **a priorità tra le classi** e **round-robin all'interno** di ciascuna classe. Le priorità vanno riviste periodicamente per evitare la **starvation** dei processi a bassa priorità.

> [!example] Esempio a 4 classi di priorità
> Con 4 classi di priorità, finché ci sono processi nella classe 4 si usano in round-robin; se la classe 4 è vuota si passa alla 3, poi alla 2, e così via. Senza revisione periodica i processi a bassa priorità non vengono mai eseguiti (starvation).

**Quanto per classe**: a ogni classe è assegnato un quanto *(extra, non da slide: il quanto distinto per ogni classe)*; quando un processo lo esaurisce passa alla priorità appena inferiore. Senza revisione periodica un processo può degradare fino alla priorità 0, dove rimane inibito indefinitamente (**starvation verso il basso** *(extra, non da slide: il termine)*).

> [!info] Collegamento
> Un uso scorretto delle priorità può causare l'[[04 - Sincronizzazione#Inversione delle priorità|inversione delle priorità]].

> [!question] Domanda tipica d'esame
> - **D:** Come funziona lo scheduling a priorità e come si evita la starvation dei processi a bassa priorità? **R:** Ogni processo ha una **priorità** e si esegue il pronto con priorità più alta. Per evitare la **starvation** si fa **diminuire nel tempo** la priorità del processo in esecuzione (o si assegna un quanto, scalandolo poi nella classe inferiore) e si **rivedono periodicamente** le priorità. *(Nell'edizione 2026-2027 il termine «aging» ha due usi: la tecnica di stima di [[#Shortest Process Next con aging]] e l'**aging delle priorità**, che aumenta progressivamente la priorità dei processi che aspettano troppo a lungo; la slide 2025-2026 lo usa solo per la stima.)*
### Shortest Process Next con aging
Idea: SJF riduce il turnaround medio nei sistemi batch; nei sistemi interattivi si può adottare un'idea simile, scegliendo il processo con il **prossimo CPU burst stimato più breve**. Il problema è che la durata del prossimo burst non è nota in anticipo: la si stima dalle durate osservate in passato (**aging**, termine della slide 2025-2026 e della tabella riassuntiva). Con la **stima esponenziale** $T(n+1) = \alpha\,T(n) + (1-\alpha)\,t(n)$, dove $T(n)$ è la stima precedente, $t(n)$ la durata effettiva dell'ultimo CPU burst e $\alpha$ un parametro tra 0 e 1 che pesa la stima precedente; con $\alpha = 0{,}5$ l'ultima osservazione pesa il 50%, quella precedente il 25%, e così via *(slide 2026-2027)*. Nella notazione della slide 2025-2026: data una stima $T_0$, dopo una nuova esecuzione misurata $T_1$ la stima si aggiorna come:
$$\text{stima} = a\,T_0 + (1-a)\,T_1$$
Il parametro $a$ pesa le esecuzioni passate. Espandendo con $a = 1/2$: $\text{stima}_1 = \tfrac{T_0}{2} + \tfrac{T_1}{2}$, $\text{stima}_2 = \tfrac{T_0}{4} + \tfrac{T_1}{4} + \tfrac{T_2}{2}$, e così via — dopo 3 esecuzioni il peso di $T_0$ è già $1/8$ *(slide 2025-2026)*: le informazioni vecchie "invecchiano" e contano sempre meno. Nell'esempio della slide, il professore stima Giulia 4 minuti, Luca 6, Matteo 10 e li serve nell'ordine Giulia → Luca → Matteo; se Matteo diventa più veloce, le sue stime si aggiornano e può essere scelto prima. **Attenzione**: questo meccanismo migliora le stime ma **non garantisce l'assenza di starvation** *(slide 2026-2027; slide 2025-2026: «nessuno rischia la starvation»)*.
### Guaranteed scheduling
Fa **promesse concrete** sulle prestazioni: con $n$ processi/utenti, ciascuno ottiene circa $1/n$ della CPU. Il sistema traccia quanta CPU ha **realmente ricevuto** ogni processo e quanta **avrebbe dovuto** (tempo da creazione $\div n$; es. 100 s dalla creazione e 10 processi: ognuno dovrebbe averne 10 s), calcola il **rapporto** consumato/dovuto ed esegue il processo con il **rapporto più basso** (chi è più indietro rispetto alla sua quota). Si esegue il processo con il rapporto più basso finché non supera il suo concorrente più vicino. *(Extra, non da slide: una variante di questo approccio è adottata da Linux come **CFS**, **Completely Fair Scheduler**.)*

> [!example] Esempio della slide
> Con 100 minuti totali e 3 studenti (Giulia, Matteo, Luca) la quota è circa 33 minuti ciascuno. Giulia ha usato 20 minuti → rapporto $0{,}6$; Matteo 70 minuti → $2{,}1$; Luca 10 minuti → $0{,}3$ *(slide 2025-2026: Matteo 40 minuti → $1{,}2$)*. Usa il computer chi è più indietro: Luca (rapporto più basso), poi Giulia, poi Matteo. In generale, un rapporto di $0{,}5$ significa metà del tempo dovuto, uno di $2{,}0$ il doppio.
### Lottery scheduling
A ogni processo si assegnano **biglietti della lotteria** per le risorse; a ogni decisione si **estrae** un biglietto a caso e vince il processo corrispondente. Un processo con il 20% dei biglietti otterrà a lungo termine il **20%** della CPU. È flessibile (più biglietti = più probabilità) e i processi cooperanti possono **scambiarsi biglietti** (es. un client li dona al server per farsi servire prima). Risponde inoltre rapidamente ai nuovi processi (basta distribuire loro dei biglietti). Limite: è **non deterministico**.

> [!example] Lottery scheduling — parametri quantitativi
> L'estrazione avviene $\approx 50$ volte al secondo; ogni vincita assegna $20\,\text{ms}$ di CPU. Caso d'uso tipico: un **server video** con flussi a frequenze di fotogrammi diverse (es. 25 fps e 10 fps *(valori extra, non da slide)*). Assegnando biglietti proporzionali alla frequenza richiesta, la CPU viene ripartita automaticamente nelle proporzioni corrette — più biglietti = più frame/s.

> [!question] Domanda tipica d'esame
> - **D:** Come funziona il Lottery scheduling e in quale scenario è particolarmente adatto? **R:** A ogni processo si assegnano **biglietti**; a ogni decisione si **estrae** un biglietto a caso e vince il processo corrispondente, così la quota di CPU è **proporzionale** ai biglietti posseduti. È adatto quando servono proporzioni flessibili (assenza di starvation: *extra, non da slide*), es. un **server video** con flussi a frame rate diversi (biglietti proporzionali al frame rate). Limite: è **non deterministico**.
### Fair-share scheduling
Gli algoritmi precedenti schedulano i singoli processi; ma se l'utente 1 ha 9 processi e l'utente 2 ne ha 1, con round-robin l'utente 1 otterrebbe il **90%** della CPU. Il **fair-share** considera il **proprietario**: ogni utente riceve una frazione predefinita di CPU, indipendentemente dal numero di processi.

> [!example] Equità per utente
> Due utenti al 50%: l'utente 1 ha i processi A, B, C, D; l'utente 2 ha solo E. Con quote uguali tra utenti la sequenza diventa `A E B E C E D E …` (E ottiene metà CPU pur avendo un solo processo). Se invece l'utente 1 riceve una quota di CPU **doppia** rispetto all'utente 2 (rapporto 2:1), la sequenza diventa del tipo `A B E C D E A B E …` (l'utente 1 ottiene due slot ogni tre).

> [!question] Domanda tipica d'esame
> - **D:** Spiegare il Fair-Share scheduling: perché è necessario rispetto al Round-Robin classico? **R:** Il Round-Robin schedula i singoli **processi**: un utente con molti processi ottiene una quota di CPU maggiore (9 processi su 10 → 90% della CPU). Il **fair-share** considera il **proprietario**: assegna a ogni utente una frazione predefinita di CPU **indipendentemente** dal numero dei suoi processi, garantendo equità *tra utenti* e impedendo a un utente "ricco di processi" di dominare.
### Tabella riassuntiva
| Algoritmo | Idea base | Metafora (slide) | Punti di forza | Limiti |
|---|---|---|---|---|
| **Round-Robin** | ognuno usa la CPU per un quanto, poi cede il turno | Giulia, Matteo e Luca si alternano con un timer che suona | equo, semplice, ottimo per interattivi | quanto mal scelto → lentezza o overhead |
| **Priorità** | esegue chi ha priorità più alta | il prof dà la precedenza a chi ha un ruolo più importante | gestisce urgenze e classi | possibile **starvation** dei deboli |
| **SPN + Aging** | esegue chi sembra più breve (stima aggiornata) | il prof stima chi finirà più veloce basandosi sulle volte precedenti | risposte rapide, meno attese | rischio di errori di previsione |
| **Guaranteed** | a ciascuno la sua quota equa ($1/n$) | la scuola controlla chi ha già usato troppo o troppo poco tempo | equità forte e misurabile | serve tracciare le quote |
| **Lottery** | probabilità proporzionale ai biglietti | la scuola sorteggia chi usa il PC, ma chi ha più biglietti vince più spesso | flessibile, semplice da regolare | non deterministico |
| **Fair-Share** | equità tra **utenti**, non tra processi | ogni studente ha una quota, indipendentemente dal numero di processi | impedisce a un utente "ricco di processi" di dominare | più complesso da bilanciare |

**Dalla teoria alla pratica: lo scheduling ordinario in Linux** *(slide 2026-2027)*. I sistemi operativi reali combinano più criteri (priorità, equità, reattività, vincoli temporali) e Linux usa diverse politiche di scheduling: non applica semplicemente uno degli algoritmi studiati. Lo scheduling ordinario cerca di distribuire equamente la CPU tra i thread pronti. Il valore **NI (nice)** influenza il peso assegnato a ciascun thread: va da $-20$ a $+19$, normalmente parte da $0$; NI più basso → maggiore favore nello scheduling, NI più alto → minore favore. Nel comando `top` la colonna **PR** mostra una rappresentazione della priorità; per i normali processi `SCHED_OTHER` vale tipicamente $PR = 20 + NI$. Un processo con priorità maggiore non viene necessariamente eseguito sempre per primo: Nice influenza soprattutto la ripartizione della CPU quando c'è contesa, ma non determina da sola quanto tempo di CPU un processo riceverà. La colonna `%CPU` misura l'utilizzo effettivo, **non** la priorità: un processo può usare molta CPU semplicemente perché esegue molti calcoli. Si osserva con `top` e `ps -eo pid,comm,ni,%cpu --sort=-%cpu | head`; si modifica con `nice -n 5 comando` (avvia un programma con Nice incrementato di 5) e `renice -n 10 -p PID` (imposta Nice a 10 per un processo esistente); per diminuire Nice servono normalmente privilegi adeguati.

> [!info] Mettiti alla prova
> - **Round-Robin** e calcolo dell'overhead del quanto → [[05 - Scheduling (Esercizi)#Es. 4 — Round-Robin e calcolo dell'overhead|Es. 4]];
> - **Guaranteed scheduling** (rapporto consumato/dovuto) → [[05 - Scheduling (Esercizi)#Es. 6 — Guaranteed scheduling (rapporto consumato/dovuto)|Es. 6]].
## Scheduling nei sistemi real-time
Usato dove il **tempo di risposta** è critico (slide 2026-2027: monitoraggio dei pazienti in terapia intensiva, sistemi di controllo del volo, robotica e controllo industriale; slide 2025-2026: lettori di compact disc, piloti automatici): ritardi o scadenze mancate possono avere gravi conseguenze. Non basta ottenere risultati corretti: occorre ottenerli entro le scadenze (**deadline**), e un ritardo può avere conseguenze più o meno gravi a seconda dell'applicazione. L'obiettivo principale è rispettare i vincoli temporali; i task hanno spesso caratteristiche temporali note o prevedibili, e la **prevedibilità** dei tempi conta più della sola velocità media. Si può usare scheduling con o senza prelazione, a seconda dell'algoritmo e dei requisiti *(slide 2026-2027; slide 2025-2026: la prelazione non è sempre necessaria, perché i processi sanno di non poter essere eseguiti a lungo e in genere svolgono il proprio lavoro e si bloccano rapidamente)*.
- **Categorie**: **hard real-time** (scadenze assolute, inviolabili) vs **soft real-time** (qualche scadenza mancata è tollerabile).
- **Comportamento**: processi prevedibili, brevi e noti in anticipo.
- **Eventi**: **periodici** (a intervalli regolari) o **non periodici** (imprevedibili).

> [!quote] Condizione necessaria di schedulabilità
> Con $m$ task periodici su una singola CPU, se il task $i$ ha periodo $P_i$ e tempo massimo di esecuzione di ogni istanza $C_i$ (**WCET**, *Worst-Case Execution Time*), il carico totale della CPU è $U = \sum_{i=1}^{m} \frac{C_i}{P_i}$. Se $U > 1$ il carico supera la capacità della CPU; se $U \le 1$ il carico è potenzialmente sostenibile, ma la schedulabilità **non è automaticamente garantita**: dipende anche dall'algoritmo adottato, dalle deadline e dalle ipotesi sui task. *(Slide 2025-2026: il carico è gestibile **solo se** $\sum_{i=1}^{m} C_i/P_i \le 1$.)*

> [!example] Verifica
> Eventi con periodi 100, 200, 500 ms e tempi richiesti 50, 30, 100 ms: $0{,}5 + 0{,}15 + 0{,}2 = 0{,}85 < 1$: il carico complessivo è dell'85%, la condizione necessaria è rispettata, ma occorre ancora verificare la schedulabilità rispetto all'algoritmo scelto *(slide 2025-2026: «schedulabile»)*.

Gli algoritmi possono essere **statici** (decisioni prese prima dell'esecuzione, richiedono perfetta conoscenza di esigenze e scadenze) o **dinamici** (decisioni durante l'esecuzione).

> [!info] Mettiti alla prova
> - **Schedulabilità real-time** (verifica di $\sum_i C_i / P_i \le 1$) → [[05 - Scheduling (Esercizi)#Es. 5 — Schedulabilità real-time|Es. 5]].
## Meccanismo e politica di scheduling
Negli scheduler tradizionali i processi utente non possono influenzare le decisioni, il che porta a scelte **sub-ottimali** (es. un processo padre che conosce l'importanza relativa dei suoi figli). Il principio (**Levin et al., 1975**) è **separare il meccanismo dalla politica**: l'algoritmo (il **meccanismo**) sta nel kernel ed è **parametrizzabile**, ma i parametri (la **policy**) sono forniti dai processi utente. Esempio: il kernel implementa lo scheduling a priorità, ma una system call permette al padre di impostare le priorità dei figli.
## Scheduling dei thread
Lo scheduling differisce a seconda che i [[03 - Processi e Thread#Implementazione dei thread|thread]] siano a livello utente o kernel.
- **Thread a livello utente**: il kernel **ignora** i thread e sceglie un processo per il suo quanto; il *run-time* interno decide quale thread eseguire, **senza interrupt del clock** (spesso con round-robin o a priorità, con cooperazione tra thread e nessuna interruzione forzata). Un thread può consumare l'intero quanto del processo. Con quanto di 50 ms e thread da 5 ms, è possibile la sequenza `A1 A2 A3 A1 A2 A3`, **non** `A1 B1 A2 B2` (non si passa a un altro processo a metà quanto).
- **Thread a livello kernel**: il **kernel** sceglie il singolo thread (anche di un altro processo); è possibile `A1 B1 A2 B2`. Il cambio è **più costoso** (context switch completo), ma se un thread fa I/O bloccante si blocca **solo quel thread** (non l'intero processo). Se un thread eccede il quanto, viene sospeso. Nelle sue decisioni il kernel considera il costo del passaggio tra thread diversi e **può preferire thread dello stesso processo** per ridurre l'overhead; lo scheduler dell'applicazione, a sua volta, può scegliere internamente quale thread eseguire, con ottimizzazioni specifiche non possibili nel kernel.

| Aspetto | Thread utente | Thread kernel |
|---|---|---|
| Velocità di switch | veloce | lento |
| Blocco I/O | blocca l'intero processo | blocca solo il thread |
| Chi decide l'ordine | run-time utente | kernel |
| Flessibilità | alta | media |
| Controllo del sistema | basso | alto |

---
**Argomento precedente:** [[04 - Sincronizzazione]] · **Prossimo:** [[06 - Gestione della Memoria]] — astrazione della memoria, paginazione, memoria virtuale e algoritmi di sostituzione delle pagine.
