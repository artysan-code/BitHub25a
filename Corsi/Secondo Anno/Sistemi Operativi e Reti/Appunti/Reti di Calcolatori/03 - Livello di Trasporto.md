# 03 - Livello di Trasporto
Il livello di trasporto fornisce una **comunicazione logica tra processi** di host differenti: dal punto di vista dell'applicazione, tutto avviene come se i due processi fossero direttamente collegati, indipendentemente dalla complessità fisica della rete sottostante. I protocolli di trasporto operano esclusivamente nei **sistemi periferici (end systems)**; i router intermedi vedono solo l'intestazione del datagramma IP e ignorano il segmento incapsulato. Questa nota copre i due protocolli Internet — **TCP** e **UDP** — i principi del trasferimento affidabile, il controllo di flusso, la gestione della connessione, il controllo della congestione e il protocollo QUIC. Per il contesto architetturale si veda [[01 - Introduzione]]; per le applicazioni che usano questi servizi, [[02 - Livello di Applicazione]].
## Servizi del livello di trasporto
Il livello di rete (vedi [[04 - Livello di Rete]]) offre comunicazione logica tra **host**; il livello di trasporto la estende tra **processi**. L'analogia del libro di testo: Ann e Bill smistano lettere tra i loro 12 ragazzi ciascuno — i ragazzi sono i processi, il servizio postale che trasporta le buste tra le case è IP.
I due protocolli Internet di trasporto sono:
- **TCP (Transmission Control Protocol)**: affidabile, orientato alla connessione, con controllo di flusso e della congestione.
- **UDP (User Datagram Protocol)**: non affidabile, senza connessione, minimo overhead.

> [!info] Servizi non disponibili a livello di trasporto
> Per vincolo architetturale di Internet, né TCP né UDP garantiscono ritardi massimi né larghezza di banda minima. Queste garanzie non esistono a livello di rete IP (best effort) e il trasporto non può crearle dal nulla.
## Multiplexing e Demultiplexing
Un processo gestisce i dati attraverso una o più **socket**. Il livello di trasporto non consegna i dati direttamente al processo ma alla socket corretta.
- **Multiplexing** (lato mittente): raccoglie dati da varie socket, aggiunge intestazione, passa i segmenti al livello di rete.
- **Demultiplexing** (lato ricevente): usa le informazioni dell'intestazione per consegnare i dati alla socket appropriata.

Ogni segmento contiene **numero di porta sorgente** e **numero di porta destinazione** (16 bit ciascuno; range 0–65535). I numeri 0–1023 sono **numeri di porta well-known**, assegnati dallo IANA a protocolli specifici (HTTP: 80, DNS: 53, SMTP: 25).
### Demultiplexing senza connessione (UDP)
Una socket UDP è identificata dalla coppia **(indirizzo IP di destinazione, numero di porta di destinazione)**. Due datagrammi UDP con IP/porta sorgente diversi ma stessa destinazione arrivano alla stessa socket. L'indirizzo e la porta sorgente fungono da "indirizzo di ritorno".
### Demultiplexing orientato alla connessione (TCP)
Una socket TCP è identificata da una **quadrupla**: (IP sorgente, porta sorgente, IP destinazione, porta destinazione). Il server mantiene una **socket passiva** (di ascolto) su una porta; per ogni connessione accettata crea una nuova **socket connessa**. Tre segmenti tutti diretti a IP:B porta:80 ma provenienti da client diversi vengono demultiplexati su socket distinte.

> [!info] Multiplexing a tutti i livelli
> Il multiplexing/demultiplexing non è esclusivo del livello di trasporto: avviene a ogni livello della pila protocollare (vedi [[01 - Introduzione]], sezione incapsulamento).
## Trasporto senza connessione: UDP
UDP [RFC 768] è la versione "senza fronzoli" del trasporto: estende IP al minimo indispensabile aggiungendo solo multiplexing/demultiplexing e controllo degli errori.

> [!quote] Definizione — UDP
> **UDP** è un protocollo di trasporto **best effort**: i segmenti possono essere persi, duplicati o consegnati fuori sequenza. Non prevede handshaking; ogni segmento è gestito indipendentemente dagli altri.

**Perché esiste UDP?** Quattro ragioni pratiche:
- Nessun RTT di setup (zero latenza di connessione).
- Nessuno stato di connessione → un server può gestire molti più client contemporaneamente.
- Intestazione corta (8 byte contro i 20 di TCP).
- Controllo preciso di dati e tempistica: utile per applicazioni tolleranti alle perdite ma sensibili ai ritardi (streaming multimediale in tempo reale, DNS, SNMP). **HTTP/3** aggiunge affidabilità e controllo della congestione sopra UDP tramite QUIC.
### Struttura del segmento UDP
Il segmento UDP ha intestazione fissa di 8 byte:

| Campo | Dimensione | Descrizione |
|---|---|---|
| Porta sorgente | 16 bit | Identificatore socket mittente |
| Porta destinazione | 16 bit | Identificatore socket ricevente |
| Lunghezza | 16 bit | Lunghezza totale segmento in byte (intestazione + dati) |
| Checksum | 16 bit | Rilevazione errori |

Il campo **lunghezza** include l'intestazione e impone un limite alla dimensione del segmento e del messaggio.
### Checksum UDP (Internet Checksum)
**Obiettivo**: rilevare errori (bit alterati) nel segmento trasmesso.

*Lato mittente*: tratta il contenuto del segmento (intestazione UDP + indirizzi IP + dati) come sequenza di interi a 16 bit; calcola il **complemento a 1 della somma in complemento a 1** (il campo checksum vale 0 durante il calcolo); inserisce il risultato nel campo checksum.

*Lato ricevente*: ricalcola la checksum nello stesso modo includendo il valore ricevuto; se il risultato è **tutti bit a 1** (che rappresenta −0 in complemento a 1) nessun errore è rilevato, altrimenti c'è un errore.

> [!warning] Protezione debole
> Due errori che si compensano reciprocamente non vengono rilevati dalla checksum UDP. La protezione è necessaria ma non sufficiente.
## Principi del trasferimento dati affidabile (rdt)
Il livello di trasporto deve fornire l'astrazione di un **canale affidabile** pur appoggiarsi a un canale inaffidabile sottostante (IP). Mittente e ricevente non conoscono lo stato dell'altro: occorre un protocollo esplicito. Le interfacce sono: `rdt_send()`, `udt_send()`, `rdt_rcv()`, `deliver_data()`. I protocolli sono descritti tramite **FSM (macchine a stati finiti)** e sviluppati incrementalmente.
### rdt1.0 — canale perfettamente affidabile
Nessun errore sui bit, nessuna perdita. Il mittente crea il pacchetto e lo invia; il ricevente lo estrae e consegna i dati. Non serve alcun meccanismo aggiuntivo. Si assume che il ricevente accetti i dati al ritmo del mittente (nessun controllo di flusso).
### rdt2.0 — canale con errori sui bit
Il canale può invertire bit. Meccanismi aggiunti: **checksum** per rilevare errori, **ACK** (notifica positiva), **NAK** (notifica negativa). In caso di NAK il mittente ritrasmette. Paradigma **stop-and-wait**: il mittente attende la risposta prima di inviare nuovi dati.

> [!warning] Difetto fatale di rdt2.0
> Se ACK o NAK vengono corrotti, il mittente non sa cosa è successo. Ritrasmettere crea possibili duplicati che il ricevente non può distinguere dai pacchetti originali.
### rdt2.1 — gestione di ACK/NAK alterati
Soluzione: aggiungere un **numero di sequenza** al pacchetto. Bastano **0 e 1** perché il paradigma è stop-and-wait: il ricevente controlla il numero di sequenza per distinguere nuovo invio da ritrasmissione. In caso di ACK/NAK corrotto o NAK il mittente ritrasmette. Il ricevente scarta i duplicati ma invia comunque ACK.
### rdt2.2 — protocollo senza NAK
Stessa funzionalità di rdt2.1 usando **solo ACK**. Al posto del NAK, il destinatario invia ACK per l'**ultimo pacchetto ricevuto correttamente** con numero di sequenza esplicito. Un ACK duplicato al mittente produce lo stesso effetto del NAK: ritrasmissione. **TCP usa questo approccio**.
### rdt3.0 — canali con errori e perdite
Il canale può **perdere pacchetti** (dati o ACK). Soluzione: **timer con countdown** nel mittente. Se entro un tempo "ragionevole" non arriva ACK, il pacchetto viene ritrasmesso. Ritrasmissioni duplicate (da timeout prematuro o ACK in ritardo) sono gestite dai numeri di sequenza. Il ricevente è identico a rdt2.1. Per via dell'alternanza 0/1 dei numeri di sequenza, rdt3.0 è detto **protocollo ad alternanza di bit**.
### Prestazioni di rdt3.0 (stop-and-wait)
> [!example] Esempio numerico
> Collegamento da 1 Gbps, RTT = 30 ms, pacchetti da 1000 byte (8000 bit):
> $$D_{trasm} = \frac{L}{R} = \frac{8000}{10^9} = 8 \; \mu s$$
> $$U_{mittente} = \frac{L/R}{RTT + L/R} = \frac{0{,}008}{30{,}008} \approx 0{,}000267$$
> Throughput effettivo: circa **267 kbps** su un collegamento da 1 Gbps. Prestazioni pessime.
## Protocolli con Pipelining
**Pipelining**: il mittente ammette **più pacchetti in transito** non ancora riscontrati. Richiede un range di numeri di sequenza più ampio e buffering al mittente e/o al ricevente. Con una pipeline di 3 pacchetti, l'utilizzo triplica:
$$U_{mittente} = \frac{3L/R}{RTT + L/R} \approx 0{,}00081$$
Due famiglie di soluzioni agli errori con pipeline: **Go-Back-N** e **Ripetizione Selettiva**.
### Go-Back-N (GBN)
Il mittente può avere fino a $N$ pacchetti trasmessi ma non riscontrati nella pipeline (**finestra scorrevole** di ampiezza $N$). I numeri di sequenza sono a $k$ bit.

**Mittente GBN** — tre eventi:
- *Dati dall'applicazione*: invia se `nextseqnum < base + N`; altrimenti rifiuta i dati.
- *ACK ricevuto*: usa **ACK cumulativo** — ACK($n$) riscontra tutti i pacchetti con numero di sequenza $\le n$; avanza la base; riavvia il timer se ci sono pacchetti non riscontrati.
- *Timeout*: ritrasmette il pacchetto più vecchio non riscontrato **e tutti quelli successivi** (go back N); riavvia il timer.

**Ricevente GBN**: invia sempre ACK per il pacchetto in ordine con il più alto numero di sequenza ricevuto correttamente. I pacchetti fuori sequenza sono **scartati** (nessun buffering); re-invia l'ultimo ACK in ordine. Mantiene solo `expectedseqnum`.

> [!example] GBN in azione (N=4)
> pkt2 perso → pkt3, pkt4, pkt5 arrivano ma vengono scartati dal ricevente → timeout su pkt2 → ritrasmissione di pkt2, pkt3, pkt4, pkt5.
### Ripetizione Selettiva (SR)
Il mittente ritrasmette **solo i pacchetti sospettati di errore**, non l'intera finestra. Ha un timer **per ogni pacchetto non riscontrato**.

**Mittente SR**:
- *Timeout(n)*: ritrasmette solo il pacchetto $n$, riavvia il suo timer.
- *ACK(n)* ricevuto: marca individualmente il pacchetto come riscontrato; se $n$ è il numero di sequenza più piccolo non riscontrato, avanza la base della finestra.

**Ricevente SR**: riscontra individualmente ogni pacchetto ricevuto correttamente; i pacchetti fuori sequenza vengono **bufferizzati** (non scartati). Quando arriva il pacchetto atteso, consegna al livello superiore in ordine tutto il blocco contiguo bufferizzato e avanza la finestra. Per i pacchetti già consegnati e richiesti di nuovo (nell'intervallo $[\text{rcvbase}-N, \text{rcvbase}-1]$) invia ACK per far avanzare la finestra del mittente.

> [!example] SR in azione (N=4)
> pkt2 perso → pkt3, pkt4, pkt5 bufferizzati (non scartati) → timeout pkt2 → ritrasmissione solo pkt2 → consegna in ordine pkt2, pkt3, pkt4, pkt5.
### Dilemma SR e dimensione della finestra
Con numeri di sequenza ciclici (aritmetica modulare), se la finestra è troppo grande il ricevente non distingue un nuovo pacchetto da uno ritrasmesso. La relazione necessaria (valida sia per SR sia per GBN), con $w$ dimensione finestra e $m = 2^k$ dimensione dello spazio dei numeri di sequenza:
$$2w \le m \quad \Longleftrightarrow \quad w \le 2^{k-1}$$
## TCP — Trasporto orientato alla connessione
### Panoramica
TCP [RFC 793, 1122, 5681] fornisce:
- **Punto a punto**: singolo mittente, singolo destinatario.
- **Flusso di byte affidabile, in sequenza**: nessun confine ai messaggi.
- **Full duplex**: dati in entrambe le direzioni sulla stessa connessione simultaneamente.
- **ACK cumulativi** e **pipelining** (finestra definita da controllo di flusso e congestione).
- **Orientato alla connessione**: handshaking inizializza lo stato prima dei dati.
- **Controllo di flusso** e **controllo della congestione**.

La connessione TCP è implementata nei sistemi periferici, non nei router.
### MSS e buffer
TCP mantiene un **send buffer** (dati da inviare o in attesa di ACK) e un **receive buffer** (dati ricevuti pronti per l'applicazione).

La **MSS (Maximum Segment Size)** è la quantità massima di dati applicativi nel segmento (esclusa l'intestazione TCP). Si ricava dalla **MTU (Maximum Transmission Unit)** del collegamento:

| Collegamento | MTU | MSS tipica |
|---|---|---|
| Ethernet | 1500 B | 1460 B |
| IPv4 (minima) | 576 B | 536 B |
| IPv6 (minima) | 1280 B | 1220 B |

La MSS è negoziabile durante l'handshake tramite l'opzione MSS. Il **Path MTU Discovery** riduce la MTU se arrivano messaggi ICMP da router che scartano pacchetti troppo grandi; il **MTU Black Hole** si verifica quando tali messaggi ICMP sono bloccati.
### Struttura del segmento TCP
L'intestazione TCP tipica è **20 byte** (senza opzioni), in multipli di 32 bit:

| Campo | Bit | Descrizione |
|---|---|---|
| Porta sorgente / destinazione | 16+16 | Multiplexing/demultiplexing |
| Numero di sequenza | 32 | Numero del **primo byte** del segmento nel flusso |
| Numero di acknowledgement | 32 | Numero di sequenza del **prossimo byte atteso**; ACK cumulativo |
| Lunghezza intestazione | 4 | In multipli di 32 bit |
| Flag (CWR, ECE, URG, ACK, PSH, RST, SYN, FIN) | 8 | Controllo connessione e congestione |
| Finestra di ricezione (rwnd) | 16 | Byte accettabili dal destinatario (controllo di flusso) |
| Checksum | 16 | Rilevazione errori |
| Puntatore dati urgenti | 16 | Usato con flag URG |
| Opzioni | variabile | Es. MSS, window scaling, SACK |

Il **numero di sequenza** conteggia i byte (non i segmenti). Il **numero di acknowledgement** è il numero del prossimo byte atteso: se il ricevente ha ricevuto correttamente i byte 0–535, l'ACK vale 536. L'ACK è spesso **piggybacked** sui segmenti dati nella direzione opposta.
### Stima RTT e timeout
**SampleRTT**: tempo dalla trasmissione del segmento alla ricezione dell'ACK (esclude le ritrasmissioni).

**EstimatedRTT** — media mobile esponenziale pesata (EWMA), con $\alpha = 0{,}125$:
$$\text{EstimatedRTT} = (1-\alpha) \cdot \text{EstimatedRTT} + \alpha \cdot \text{SampleRTT}$$

**DevRTT** — deviazione stimata, con $\beta = 0{,}25$:
$$\text{DevRTT} = (1-\beta) \cdot \text{DevRTT} + \beta \cdot |\text{SampleRTT} - \text{EstimatedRTT}|$$

**Intervallo di timeout**:
$$\text{TimeoutInterval} = \text{EstimatedRTT} + 4 \cdot \text{DevRTT}$$
Dopo ogni timeout la durata viene **raddoppiata** (backoff esponenziale); torna alla formula standard alla ricezione del primo ACK per un nuovo segmento.
### Mittente TCP (semplificato)
Tre eventi guidano il mittente:
- *Dati dall'applicazione*: crea segmento con `NextSeqNum`; avvia il timer se non già attivo.
- *Timeout*: ritrasmette il segmento con il più piccolo numero di sequenza non riscontrato; riavvia il timer.
- *ACK ricevuto ($y > \text{SendBase}$)*: aggiorna `SendBase = y`; avvia il timer se esistono segmenti non riscontrati.
### Ricevente TCP: generazione ACK [RFC 5681]
| Evento | Azione |
|---|---|
| Segmento ordinato, tutto precedente riscontrato | ACK **ritardato** fino a 500 ms; se non arriva il successivo, invia ACK |
| Segmento ordinato, un ACK in attesa | Invia immediatamente **un singolo ACK cumulativo** per entrambi |
| Segmento fuori sequenza (buco rilevato) | Invia immediatamente **ACK duplicato** con il numero di sequenza del prossimo byte atteso |
| Segmento che colma il buco | Invia immediatamente ACK (se inizia all'estremità inferiore del buco) |
### Ritrasmissione rapida
Se il mittente riceve **3 ACK duplicati**: ritrasmette immediatamente il segmento non riscontrato con il numero di sequenza più basso **senza attendere il timeout**. Tre ACK duplicati indicano che almeno tre segmenti successivi sono arrivati correttamente: è probabile che il segmento mancante sia perso, non semplicemente in ritardo.
### Controllo di flusso
Il destinatario comunica lo spazio libero nel proprio buffer tramite il campo **rwnd** nell'intestazione TCP:
$$\text{rwnd} = \text{RcvBuffer} - (\text{LastByteRcvd} - \text{LastByteRead})$$
Il mittente garantisce:
$$\text{LastByteSent} - \text{LastByteAcked} \le \text{rwnd}$$
Se `rwnd = 0` il mittente invia segmenti da **1 byte** per sondare se il buffer si è svuotato. Il valore predefinito di RcvBuffer è tipicamente 4096 byte; molti sistemi operativi lo regolano automaticamente.
### Gestione della connessione — Three-Way Handshake
Un handshake a due vie non basta per via di ritardi variabili, messaggi ritrasmessi e riordino: si andrebbero a creare connessioni mezze aperte o dati duplicati accettati.

**TCP 3-way handshake**:

| Passo | Segmento | Transizione stati |
|---|---|---|
| 1 (Client → Server) | `SYNbit=1, Seq=x` (ISN client casuale) | Client: CLOSED → SYNSENT |
| 2 (Server → Client) | `SYNbit=1, Seq=y, ACKbit=1, ACKnum=x+1` (ISN server casuale) | Server: LISTEN → SYNRCVD |
| 3 (Client → Server) | `ACKbit=1, Seq=x+1, ACKnum=y+1` (può contenere dati) | Entrambi: → ESTABLISHED |

I **numeri di sequenza iniziali (ISN) sono casuali** per evitare interferenze con connessioni precedenti sulla stessa quadrupla. Se un host riceve una richiesta di connessione su una porta senza socket in ascolto risponde con `RST=1`.

> [!warning] Attacco SYN Flood e contromisura SYN cookie
> L'attaccante invia SYN con IP fasullo: il server alloca risorse ma non riceve mai il terzo passo → connessioni mezze aperte per oltre un minuto → DoS.
> Contromisura **SYN cookie**: il server calcola
> $$\text{cookie} = \text{hash}(\text{IP}_{src}, \text{IP}_{dst}, \text{porta}_{src}, \text{porta}_{dst}, \text{chiave segreta})$$
> e lo usa come ISN nel SYNACK senza allocare risorse. Solo all'arrivo di un ACK legittimo (`ACKnum = cookie+1`) la connessione viene ricostruita. Per resistere ai replay è necessario includere una marca temporale o ruotare la chiave segreta periodicamente.
### Chiusura della connessione TCP
Client e server chiudono ciascuno il proprio lato con `FIN=1`; il ricevente risponde con ACK.

| Stato Client | Segmento | Stato Server |
|---|---|---|
| FIN_WAIT_1 | `FINbit=1, seq=x` → | CLOSE_WAIT |
| FIN_WAIT_2 | ← `ACKbit=1, ACKnum=x+1` | (può ancora inviare dati) |
| TIME_WAIT | ← `FINbit=1, seq=y` | LAST_ACK |
| TIME_WAIT | `ACKbit=1, ACKnum=y+1` → | CLOSED |
| CLOSED (dopo 2·MSL) | | |

Lo stato **TIME_WAIT** ha due scopi: (1) ritrasmettere l'ACK finale se arriva un FIN duplicato; (2) attendere la scadenza di eventuali pacchetti ritardati in rete affinché non vengano interpretati come parte di una connessione successiva. In Linux il TIME_WAIT dura **60 secondi** (hard-coded; MSL originale RFC: 120 s).
## Principi del controllo della congestione
**Congestione**: troppe sorgenti inviano troppi dati troppo velocemente per la rete. Sintomi: lunghi ritardi (accodamento), pacchetti persi (overflow buffer dei router). Si distingue dal **controllo di flusso**: la congestione riguarda troppi mittenti nella rete; il controllo di flusso riguarda un mittente troppo veloce rispetto al singolo destinatario.

**Tre scenari di costo della congestione**:
1. *Router con buffer illimitati, 2 flussi, nessuna ritrasmissione*: throughput massimo per connessione = $R/2$; avvicinandosi a $R/2$ il ritardo cresce senza limite.
2. *Buffer finiti, ritrasmissioni*: carico offerto $\lambda'_{in} \ge \lambda_{in}$; la capacità è sprecata per ritrasmissioni necessarie e non necessarie (timeout prematuro → duplicati consegnati).
3. *4 mittenti, percorsi multi-hop*: all'aumentare del carico, il throughput dei flussi in competizione tende a zero; la capacità trasmissiva a monte è sprecata per pacchetti scartati a valle.

**Approcci**:

| Approccio | Descrizione | Esempi |
|---|---|---|
| **End-to-end** | Nessun supporto dalla rete; congestione dedotta da perdite e ritardi | TCP classico |
| **Assistito dalla rete** | Router forniscono feedback tramite chokepacket o bit di marcatura | TCP ECN, ATM ABR |
## Controllo della congestione TCP
### Variabile cwnd
Il mittente limita i dati non riscontrati:
$$\text{LastByteSent} - \text{LastByteAcked} \le \min\{\text{rwnd}, \text{cwnd}\}$$
Il tasso di invio approssimato è:
$$\text{tasso di invio} \approx \frac{\text{cwnd}}{\text{RTT}} \; \text{byte/s}$$
### Le tre fasi — TCP Reno
#### Slow Start (partenza lenta)
All'avvio: `cwnd = 1 MSS`, `ssthresh = 64 KB`. Per ogni ACK ricevuto: `cwnd += 1 MSS` → la finestra **raddoppia ogni RTT** (crescita esponenziale). Continua finché `cwnd < ssthresh` o evento di perdita.
#### Congestion Avoidance
Quando `cwnd >= ssthresh`: incremento **lineare** — per ogni ACK: `cwnd += MSS*(MSS/cwnd)` (in un RTT il totale è +1 MSS). Alla perdita per timeout: `ssthresh = cwnd/2`, `cwnd = 1 MSS`, ritorno a slow start. Alla perdita per 3 ACK duplicati: `ssthresh = cwnd/2`, `cwnd = ssthresh + 3 MSS`, transizione a fast recovery.
#### Fast Recovery
Per ogni ACK duplicato: `cwnd += 1 MSS` (per consentire l'invio di nuovi segmenti durante l'attesa). Alla ricezione di un nuovo ACK (segmento perso riscontrato): `cwnd = ssthresh` → congestion avoidance. In caso di timeout: `ssthresh = cwnd/2`, `cwnd = 1 MSS` → slow start.

**TCP Tahoe** vs **TCP Reno**: Tahoe porta sempre `cwnd = 1 MSS` a qualsiasi evento di perdita (no fast recovery); Reno differenzia tra 3 ACK duplicati (fast recovery) e timeout (slow start).
### FSM del controllo di congestione TCP (estratto)
| Stato | Evento | Azione principale |
|---|---|---|
| Slow Start | Nuovo ACK | `cwnd += MSS`, `dupACKcount=0` |
| Slow Start | `dupACKcount == 3` | `ssthresh=cwnd/2`, `cwnd=ssthresh+3`, → Fast Recovery |
| Slow Start | Timeout | `ssthresh=cwnd/2`, `cwnd=1 MSS` |
| Slow Start | `cwnd > ssthresh` | → Congestion Avoidance |
| Congestion Avoidance | Nuovo ACK | `cwnd += MSS*(MSS/cwnd)`, `dupACKcount=0` |
| Congestion Avoidance | `dupACKcount == 3` | `ssthresh=cwnd/2`, `cwnd=ssthresh+3`, → Fast Recovery |
| Congestion Avoidance | Timeout | `ssthresh=cwnd/2`, `cwnd=1 MSS`, → Slow Start |
| Fast Recovery | Nuovo ACK | `cwnd=ssthresh`, → Congestion Avoidance |
| Fast Recovery | ACK duplicato | `cwnd += MSS` |
| Fast Recovery | Timeout | `ssthresh=cwnd/2`, `cwnd=1 MSS`, → Slow Start |
### AIMD — Additive Increase Multiplicative Decrease
Il comportamento di TCP Reno in congestion avoidance è descritto da **AIMD**: incremento additivo (+1 MSS per RTT), decremento moltiplicativo (÷2 a ogni perdita da 3 ACK duplicati). Il risultato è l'andamento a **dente di sega** della finestra. AIMD è un algoritmo asincrono distribuito con proprietà di stabilità dimostrabili.

**Throughput medio** (TCP Reno, ignorando slow start):
$$\text{throughput TCP medio} = \frac{3}{4} \cdot \frac{W}{\text{RTT}} \; \text{byte/s}$$
In termini di probabilità di perdita $L$ [Mathis 1997]:
$$\text{TCP throughput} = \frac{1{,}22 \cdot \text{MSS}}{\text{RTT} \cdot \sqrt{L}}$$
### TCP CUBIC
Alternativa ad AIMD ottimizzata per sondare la larghezza di banda: dopo un dimezzamento, la finestra sale verso $W_{max}$ (valore al momento della perdita) con una **funzione cubica** della distanza dall'istante $K$ in cui verrà raggiunto $W_{max}$. Gli aumenti sono rapidi quando si è lontani da $K$ e cauti quando ci si avvicina. Modifica solo la fase di congestion avoidance. **TCP CUBIC è il predefinito in Linux** ed è il TCP più diffuso per i server web.
### Controllo della congestione basato sul ritardo (TCP Vegas / BBR)
Obiettivo: "keep the pipe just full, not fuller". Il mittente misura il throughput effettivo e lo confronta con il throughput atteso senza congestione $\text{cwnd}/\text{RTT}_{min}$:
- Throughput misurato ≈ atteso → aumento lineare di `cwnd`.
- Throughput misurato molto inferiore → riduzione lineare di `cwnd`.

Reagisce alla congestione prima che si verifichino perdite. **BBR** (Bottleneck Bandwidth and Round-trip propagation time), variante di questo approccio, è impiegato sulla rete dorsale interna di Google.
### ECN — Explicit Congestion Notification
Controllo della congestione **assistito dalla rete**: due bit ECN nel campo ToS dell'intestazione IP. Un router congestionato marca i pacchetti con `ECN=11`; il destinatario imposta il bit **ECE** nell'ACK; il mittente dimezza `cwnd` e imposta **CWR** nel segmento successivo. ECN viene negoziato durante l'handshake TCP. Come TCP Vegas, permette di reagire alla congestione prima delle perdite.
### TCP Fairness
Con $K$ sessioni TCP su un collegamento collo di bottiglia con banda $R$, l'obiettivo è una velocità media $R/K$ per ciascuna. TCP è fair sotto assunzioni idealizzate (stesso RTT, numero fisso di sessioni in congestion avoidance): AIMD garantisce l'equità perché l'incremento additivo ha pendenza uniforme e il decremento moltiplicativo è proporzionale.

**UDP non è fair**: le applicazioni multimediali inviano a velocità costante senza controllo della congestione, sottraendo banda a TCP. Le **connessioni TCP parallele** (usate dai browser web) minano anch'esse l'equità, ottenendo una quota sproporzionata della banda.
### TCP su "long fat pipes"
Il campo `rwnd` a 16 bit limita la finestra a 65 KiB — insufficiente per link ad alta velocità e alto RTT. Soluzione: **window scaling** (opzione negoziata nel SYN/SYNACK): fattore da 0 a 14, finestra effettiva = `rwnd << scaling_factor`, massimo $2^{30} = 1$ GiB.

> [!example] Esempio long fat pipe
> Throughput desiderato 10 Gbps, RTT = 100 ms → prodotto banda-latenza = $10^{10} \times 0{,}1 = 10^9$ bit = 125 MB in volo. Richiede window scaling e un tasso di perdita $L \approx 2 \times 10^{-10}$ (formula di Mathis), estremamente basso.
## QUIC — Quick UDP Internet Connections
QUIC è un protocollo di **livello applicazione** sopra UDP (non a livello di trasporto), progettato per migliorare le prestazioni di HTTP.

**Stack a confronto**:

| HTTP/2 su TCP | HTTP/3 su QUIC su UDP |
|---|---|
| TCP + TLS (due handshake distinti) | QUIC (affidabilità + sicurezza in 1 RTT) |

TCP+TLS richiede due handshake in successione; QUIC combina setup della connessione, autenticazione e cifratura in **un solo RTT**, eliminando la latenza aggiuntiva.

**Funzionalità principali**:
- Algoritmi di perdita e controllo della congestione analoghi a quelli TCP.
- **Multiplexing di più stream** a livello applicazione su una singola connessione QUIC: ogni stream ha stato di trasferimento dati affidabile e di sicurezza **separato** (eliminazione del **HOL blocking** — Head-of-Line blocking — presente in HTTP/2 su TCP); il controllo della congestione è invece **condiviso** tra stream per evitare acquisizione scorretta di banda.

> [!info] QUIC e HTTP/3
> QUIC è impiegato in molti server e applicazioni Google (Chrome, YouTube mobile). HTTP/3 incorpora nativamente QUIC come layer di trasporto. L'affidabilità aggiuntiva che UDP non offre è costruita interamente dentro QUIC a livello applicativo.

---

**Prossimo argomento:** [[04 - Livello di Rete]] — indirizzamento IP, instradamento, algoritmi di routing e protocolli come OSPF e BGP.
