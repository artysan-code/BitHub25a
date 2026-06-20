# 05 - Scheduling
Quando più processi/thread competono per la CPU, lo **scheduler** decide quale eseguire successivamente seguendo un **algoritmo di scheduling**. Questa nota tratta gli algoritmi per i diversi ambienti (batch, interattivo, real-time) e lo scheduling dei thread. Prerequisito: gli [[03 - Processi e Thread#Stati di un processo|stati di un processo]] e la [[04 - Sincronizzazione|sincronizzazione]].
## Il problema dello scheduling
Storicamente nei sistemi **batch** lo scheduling era **lineare** (il job successivo sul nastro); con la **multiprogrammazione** è diventato complesso per la concorrenza tra utenti. Sui personal computer spesso un solo processo è attivo e la CPU **raramente** è la risorsa scarsa; ma nei **server** e nei dispositivi a **batteria** (IoT, smartphone) lo scheduling torna vitale (anche per ottimizzare i consumi).
### Comportamento dei processi
I processi alternano **fasi di calcolo (CPU burst)** e **attese di I/O**:
- **Compute-bound (CPU-bound)**: burst di CPU lunghi, attese di I/O infrequenti.
- **I/O-bound**: burst di CPU brevi, attese di I/O frequenti (sono tali per la **bassa necessità di calcolo**, non per la durata dell'I/O).

Con CPU sempre più veloci i processi tendono a essere più **I/O-bound**, quindi lo scheduling deve servire rapidamente i processi I/O-bound senza penalizzare troppo quelli CPU-bound.
### Quando interviene lo scheduler
- Alla **creazione** di un nuovo processo (eseguire il padre o il figlio?).
- All'**uscita** di un processo (scegliere il prossimo; se nessuno è pronto, eseguire il processo *idle*).
- al **blocco** di un processo (I/O, semaforo…).
- a un **interrupt di I/O** (un processo potrebbe essere diventato pronto).
### Preemptive vs non-preemptive
- **Non-preemptive (senza prelazione)**: il processo scelto esegue **fino al blocco o al rilascio volontario**; gli interrupt del clock non causano decisioni.
- **Preemptive (con prelazione)**: il processo esegue per un **tempo massimo** definito; se non termina viene **sospeso**. Richiede un **interrupt del clock** ed è fondamentale per evitare che un processo (o una syscall lenta) monopolizzi la CPU.
### Costo del context switch
Il **cambio di contesto** è oneroso: passaggio user→kernel, salvataggio dello stato, esecuzione dell'algoritmo di scheduling, cambio della **mappa di memoria** (vedi [[06 - Gestione della Memoria]]) e potenziale **invalidazione della cache**. Troppe commutazioni sprecano CPU: la prudenza è essenziale.
### Obiettivi degli algoritmi
| Ambiente | Obiettivi specifici |
|---|---|
| **Batch** | throughput, minimo **tempo di turnaround**, alto utilizzo CPU |
| **Interattivo** | **tempo di risposta** rapido, proporzionalità alle aspettative |
| **Real-time** | rispetto delle **scadenze**, prevedibilità |

Per **tutti**: **equità** (CPU equa a tutti), imposizione della **policy**, bilanciamento (tenere attivi tutti i componenti).
## Scheduling nei sistemi batch
### First-Come First-Served (FCFS)
Algoritmo **senza prelazione**: i processi ricevono la CPU **nell'ordine di arrivo**, gestiti con una singola coda (lista). Semplice ed equo per ordine di arrivo, ma con prestazioni **non ottimali** in scenari misti: un processo CPU-bound può far attendere a lungo molti processi I/O-bound.
### Shortest Job First (SJF)
Algoritmo batch **senza prelazione** che esegue per primo il **job più breve**; richiede di **conoscere in anticipo** i tempi di esecuzione.

> [!example] SJF minimizza il turnaround
> Quattro job con tempi 8, 4, 4, 4 minuti. In ordine d'arrivo (8,4,4,4) i turnaround sono 8, 12, 16, 20 → media **14**. Con SJF (4,4,4,8) sono 4, 8, 12, 20 → media **11**.

**Ottimalità**: SJF minimizza il tempo di turnaround medio **solo quando tutti i job sono disponibili contemporaneamente**. Se i job arrivano in momenti diversi, può **non** essere ottimale.
### Shortest Remaining Time Next (SRTN)
Versione **con prelazione** di SJF: sceglie sempre il processo con il **tempo rimanente più breve**. All'arrivo di un nuovo job, se il suo tempo totale è inferiore al tempo rimanente del processo corrente, quest'ultimo viene sospeso. Garantisce servizio rapido ai job brevi (richiede comunque tempi noti in anticipo).
## Scheduling nei sistemi interattivi
Qui il **tempo di risposta** è fondamentale e la prelazione è essenziale.
### Round-Robin
Uno degli algoritmi più vecchi, semplici ed equi. Ogni processo riceve un intervallo di tempo, il **quanto** (quantum); se non termina entro il quanto, la CPU passa (per prelazione) al processo successivo nella lista; se si blocca o termina prima, il passaggio è immediato. Implementazione: una lista dei processi eseguibili, il processo esaurito va in **fondo** alla lista.

> [!warning] La durata del quanto è un compromesso
> Con cambio di contesto di 1 ms e quanto di 4 ms si spreca il **20%** della CPU in overhead. **Quanto troppo breve** → troppi cambi di contesto (inefficiente); **quanto troppo lungo** → tempi di risposta scadenti per le richieste interattive. Compromesso ragionevole: **20-50 ms**.
### Scheduling a priorità
Round-robin tratta tutti i processi come ugualmente importanti, ma spesso serve una **gerarchia**. Nello scheduling a priorità ogni processo ha una **priorità** e si esegue quello pronto con priorità più alta. Per evitare che i processi ad alta priorità monopolizzino la CPU, la priorità del processo in esecuzione può **diminuire nel tempo** o si assegna un quanto massimo.
- **Priorità statica**: es. gerarchie militari, costi nel data center.
- **Priorità dinamica**: es. basata sull'uso della CPU (favorisce i processi I/O-bound).

**Classi di priorità**: i processi si raggruppano in classi; si fa scheduling **a priorità tra le classi** e **round-robin all'interno** di ciascuna classe. Le priorità vanno riviste periodicamente per evitare la **starvation** dei processi a bassa priorità.

> [!info] Collegamento
> Un uso scorretto delle priorità può causare l'[[04 - Sincronizzazione#Inversione delle priorità|inversione delle priorità]].
### Shortest Process Next con aging
Idea: applicare SJF ai sistemi interattivi, stimando quale processo sarà il più breve in base al **comportamento passato** (**aging**). Data una stima $T_0$, dopo una nuova esecuzione misurata $T_1$ la stima si aggiorna come:
$$\text{stima} = a\,T_0 + (1-a)\,T_1$$
Il parametro $a$ pesa le esecuzioni passate. Con $a = 1/2$, dopo 3 esecuzioni il peso di $T_0$ è $1/8$ (le informazioni vecchie "invecchiano" e contano sempre meno), così nessuno rischia la starvation.
### Guaranteed scheduling
Fa **promesse concrete** sulle prestazioni: con $n$ processi/utenti, ciascuno ottiene circa $1/n$ della CPU. Il sistema traccia quanta CPU ha **realmente ricevuto** ogni processo e quanta **avrebbe dovuto** (tempo da creazione $\div n$), calcola il **rapporto** consumato/dovuto ed esegue il processo con il **rapporto più basso** (chi è più indietro rispetto alla sua quota).
### Lottery scheduling
A ogni processo si assegnano **biglietti della lotteria** per le risorse; a ogni decisione si **estrae** un biglietto a caso e vince il processo corrispondente. Un processo con il 20% dei biglietti otterrà a lungo termine il **20%** della CPU. È flessibile (più biglietti = più probabilità) e i processi cooperanti possono **scambiarsi biglietti** (es. un client li dona al server per farsi servire prima). Limite: è **non deterministico**.
### Fair-share scheduling
Gli algoritmi precedenti schedulano i singoli processi; ma se l'utente 1 ha 9 processi e l'utente 2 ne ha 1, con round-robin l'utente 1 otterrebbe il **90%** della CPU. Il **fair-share** considera il **proprietario**: ogni utente riceve una frazione predefinita di CPU, indipendentemente dal numero di processi.

> [!example] Equità per utente
> Due utenti al 50%: l'utente 1 ha i processi A, B, C, D; l'utente 2 ha solo E. La sequenza diventa `A E B E C E D E …` (E ottiene metà CPU pur avendo un solo processo).
### Tabella riassuntiva
| Algoritmo | Idea base | Punti di forza | Limiti |
|---|---|---|---|
| **Round-Robin** | ognuno usa la CPU per un quanto, poi cede il turno | equo, semplice, ottimo per interattivi | quanto mal scelto → lentezza o overhead |
| **Priorità** | esegue chi ha priorità più alta | gestisce urgenze e classi | possibile **starvation** dei deboli |
| **SPN + Aging** | esegue chi sembra più breve (stima aggiornata) | risposte rapide, meno attese | rischio di errori di previsione |
| **Guaranteed** | a ciascuno la sua quota equa ($1/n$) | equità forte e misurabile | serve tracciare le quote |
| **Lottery** | probabilità proporzionale ai biglietti | flessibile, semplice da regolare | non deterministico |
| **Fair-Share** | equità tra **utenti**, non tra processi | impedisce a un utente "ricco di processi" di dominare | più complesso da bilanciare |
## Scheduling nei sistemi real-time
Usato dove il **tempo di risposta** è critico (lettori CD, monitoraggio in terapia intensiva, piloti automatici, controllo robotico): ritardi o scadenze mancate possono avere gravi conseguenze.
- **Categorie**: **hard real-time** (scadenze assolute, inviolabili) vs **soft real-time** (qualche scadenza mancata è tollerabile).
- **Eventi**: **periodici** (a intervalli regolari) o **non periodici** (imprevedibili).

> [!quote] Condizione di schedulabilità
> Con $m$ eventi periodici, se l'evento $i$ ha periodo $P_i$ e richiede $C_i$ secondi di CPU per essere gestito, il carico è gestibile **solo se**:
> $$\sum_{i=1}^{m} \frac{C_i}{P_i} \le 1$$

> [!example] Verifica
> Eventi con periodi 100, 200, 500 ms e tempi richiesti 50, 30, 100 ms: $0{,}5 + 0{,}15 + 0{,}2 = 0{,}85 \le 1$ → **schedulabile**.

Gli algoritmi possono essere **statici** (decisioni prese prima dell'esecuzione, richiedono perfetta conoscenza di esigenze e scadenze) o **dinamici** (decisioni durante l'esecuzione).
## Meccanismo e politica di scheduling
Negli scheduler tradizionali i processi utente non possono influenzare le decisioni, il che porta a scelte **sub-ottimali** (es. un processo padre che conosce l'importanza relativa dei suoi figli). Il principio (**Levin et al., 1975**) è **separare il meccanismo dalla politica**: l'algoritmo (il **meccanismo**) sta nel kernel ed è **parametrizzabile**, ma i parametri (la **policy**) sono forniti dai processi utente. Esempio: il kernel implementa lo scheduling a priorità, ma una system call permette al padre di impostare le priorità dei figli.
## Scheduling dei thread
Lo scheduling differisce a seconda che i [[03 - Processi e Thread#Implementazione dei thread|thread]] siano a livello utente o kernel.
- **Thread a livello utente**: il kernel **ignora** i thread e sceglie un processo per il suo quanto; il *run-time* interno decide quale thread eseguire, **senza interrupt del clock**. Un thread può consumare l'intero quanto del processo. Con quanto di 50 ms e thread da 5 ms, è possibile la sequenza `A1 A2 A3 A1 A2 A3`, **non** `A1 B1 A2 B2` (non si passa a un altro processo a metà quanto).
- **Thread a livello kernel**: il **kernel** sceglie il singolo thread (anche di un altro processo); è possibile `A1 B1 A2 B2`. Il cambio è **più costoso** (context switch completo), ma se un thread fa I/O bloccante si blocca **solo quel thread** (non l'intero processo).

| Aspetto | Thread utente | Thread kernel |
|---|---|---|
| Velocità di switch | veloce | lento |
| Blocco I/O | blocca l'intero processo | blocca solo il thread |
| Chi decide l'ordine | run-time utente | kernel |
| Controllo del sistema | basso | alto |

---
**Argomento precedente:** [[04 - Sincronizzazione]] · **Prossimo:** [[06 - Gestione della Memoria]] — astrazione della memoria, paginazione, memoria virtuale e algoritmi di sostituzione delle pagine.
