# 01 - Introduzione
Internet è la rete più grande e complessa mai costruita: miliardi di dispositivi eterogenei — PC, smartphone, sensori IoT, data center — comunicano attraverso una gerarchia di reti fisicamente distinte ma logicamente unite da protocolli condivisi. Questa nota introduce la struttura di Internet, i suoi meccanismi di trasporto dei dati, le metriche di prestazione e il modello a livelli su cui si fonda l'intera disciplina delle reti di calcolatori.
## Cos'è Internet
Internet è descritta su due piani complementari: quello degli *ingranaggi* (cosa la compone fisicamente) e quello dei *servizi* (cosa offre alle applicazioni).
### Gli ingranaggi
I componenti fisici di Internet sono:
- **Host = sistema periferico (end system):** miliardi di dispositivi di calcolo — desktop, server, smartphone, tablet, dispositivi IoT (termostato, pacemaker, frigorifero smart) — che ospitano ed eseguono le applicazioni di rete ai confini di Internet (*edge*). Gli host si dividono in **client** (richiedono servizi) e **server** (erogano servizi, spesso raggruppati in data center).
- **Commutatori di pacchetto (packet switches):** inoltrano i **pacchetti** (frammenti di dati con intestazione); i due tipi principali sono i **router** (livello di rete) e gli **switch** di livello collegamento.
- **Reti di collegamenti (communication link):** i mezzi trasmissivi — fibra ottica, rame, radio, satellite — su cui viaggiano i bit. La velocità di trasmissione si misura in bit per secondo (bps) ed è detta **ampiezza di banda (bandwidth)**.
- **Rete:** collezione di host, commutatori e collegamenti gestita da un'unica organizzazione.

> [!quote] Definizione — Internet
> Internet è una **"rete di reti"**: migliaia di reti autonome interconnesse tramite **ISP (Internet Service Provider)** gerarchicamente organizzati.
### I servizi
Sul piano funzionale, Internet è un'**infrastruttura** che fornisce servizi alle applicazioni distribuite: Web, streaming video e musicale, videoconferenza, email, giochi, e-commerce, social media, IoT. Lo fa esponendo un'**interfaccia di programmazione** — i cosiddetti *hook* — che consentono alle applicazioni mittente e destinataria di connettersi e usare il servizio di trasporto, in modo analogo a come il servizio postale consegna lettere tra indirizzi arbitrari.
### Protocolli e standard
I **protocolli** governano ogni scambio di dati su Internet: HTTP per il Web, SMTP per la posta, TCP e IP per il trasporto e l'instradamento, WiFi e 4G/5G per l'accesso wireless.

> [!quote] Definizione — Protocollo
> Un **protocollo** definisce il **formato** e l'**ordine** dei messaggi scambiati tra due o più entità in comunicazione, così come le **azioni** intraprese in fase di trasmissione e/o di ricezione di un messaggio o di un altro evento.

Gli standard Internet sono pubblicati come **RFC (Request for Comments)** dall'**IETF (Internet Engineering Task Force)**. Per le reti locali cablate e wireless vale invece lo standard **IEEE 802** (comitato LMSC), che comprende Ethernet e WiFi (802.11).
## Ai confini della rete (edge)
La **periferia** di Internet è composta dagli host e dalle *reti di accesso* che li collegano al nucleo. L'**edge router** è il primo router sul percorso da un sistema d'origine verso qualsiasi sistema esterno alla stessa rete di accesso.

Le reti di accesso si caratterizzano per:
- **Velocità (tasso di trasmissione)** in bps.
- **Accesso dedicato vs condiviso** tra gli utenti.
### DSL (Digital Subscriber Line)
La **DSL** sfrutta la linea telefonica in rame esistente (doppino) verso il **DSLAM** nella centrale locale. Usa il **multiplexing a divisione di frequenza (FDM)** per separare voce e dati sullo stesso doppino:
- **0–4 kHz:** telefono (POTS — rete telefonica tradizionale).
- **4–50 kHz:** upstream dati.
- **50 kHz – 1 MHz:** downstream dati.

I dati DSL transitano su Internet; la voce rimane sulla rete telefonica. La DSL è **asimmetrica (ADSL/VDSL)**: 24–52 Mbps in downstream dedicato, 3.5–16 Mbps in upstream dedicato (l'ultimo standard VDSL raggiunge 1 Gbps aggregato). La VDSL è più sensibile alla distanza ed è usata nell'ultimo tratto delle soluzioni *fibra mista rame*.
### FTTx (Fiber To The x)
Le tecnologie FTTx portano la fibra ottica sempre più vicino all'utente finale; più la fibra avanza, maggiore è la velocità nell'ultimo tratto:

| Variante | Significato | Velocità tipica downstream |
|---|---|---|
| **FTTH** | Fiber-to-the-home | 1 Gbps |
| **FTTB** | Fiber-to-the-building/basement | — |
| **FTTC/FTTS** | Fiber-to-the-cabinet/street | 100–200 Mbps |
| **FTTN** | Fiber-to-the-node | — |
| **FTTW/FTTR** | Fiber-to-the-wireless/radio | — |

Per il **FTTH**, esistono due architetture di distribuzione dell'ultimo tratto:
- **AON (Active Optical Network):** Ethernet commutate con commutatori attivi che gestiscono segnali ottici.
- **PON (Passive Optical Network):** splitter ottici non alimentati che trasmettono in broadcast verso tutti gli **ONT** (Optical Network Terminal) degli utenti; standard **GPON** offre 2.5 Gbps downstream e 1.25 Gbps upstream; l'upstream usa **TDMA** per evitare collisioni; il traffico è cifrato perché il segnale OLT arriva a tutti gli ONT.
### FWA (Fixed Wireless Access)
Rete mista fibra+radio che raggiunge i clienti senza posa cavi nell'ultimo tratto:
- Banda larga: fino a 30 Mbps.
- Banda ultralarga: fino a 100 Mbps.

Può impiegare varie tecnologie radio, incluso il 5G.
### Reti domestiche, aziendali e dei data center
Una tipica **rete domestica** combina modem DSL o cavo, router/firewall/NAT e access point WiFi, spesso integrati in un unico apparato; Ethernet cablata raggiunge 1 Gbps, WiFi 802.11 fino a 450 Mbps.

Le **reti aziendali e universitarie** usano un mix di Ethernet cablata (100 Mbps, 1 Gbps, 10 Gbps) e WiFi (11, 54, 450 Mbps), con switch e router per collegare edifici e campus.

Le **reti dei data center** interconnettono centinaia o migliaia di server con larghezze di banda nell'ordine di decine/centinaia di Gbps.
### Wireless
Le reti di accesso wireless collegano i sistemi periferici al router tramite una **base station** (access point):
- **WLAN (Wireless Local Area Network):** tipicamente ~100 m, standard 802.11b/g/n a 11, 54, 450 Mbps.
- **Accesso mobile su scala geografica:** 4G (fino a 300 Mbps con 4G+) e 5G, copertura su decine di km.
### Invio dei pacchetti e mezzi trasmissivi
L'host prende il messaggio dell'applicazione, lo suddivide in **pacchetti** di lunghezza $L$ bit e li trasmette al tasso $R$ bps. Il tempo necessario a immettere tutti i bit sul collegamento è il **ritardo di trasmissione**:

$$d_{trasm} = \frac{L \text{ (bit)}}{R \text{ (bit/s)}}$$

I bit si propagano fisicamente attraverso il **mezzo trasmissivo**. Si distingue tra:
- **Mezzo vincolato (guided media):** segnale confinato in un mezzo solido.
- **Mezzo non vincolato (unguided media):** segnale si propaga liberamente nello spazio (radio).

| Mezzo | Caratteristiche principali |
|---|---|
| **Doppino di rame intrecciato (TP)** | Cat 5: 100 Mbps/1 Gbps; Cat 6: 10 Gbps (<100 m); attorcigliato per ridurre la **diafonia (crosstalk)** |
| **Cavo coassiale** | Due conduttori concentrici; bidirezionale; supporta canali multipli in FDM; centinaia di Mbps per canale |
| **Fibra ottica** | Impulsi di luce = bit; decine/centinaia di Gbps; attenuazione bassissima su 100 km; immune all'interferenza elettromagnetica |
| **Canali radio (wireless)** | Broadcast, half-duplex; soggetti a riflessione, ostruzione, interferenza; WiFi, 4G/5G (decine Mbps a ~10 km), Bluetooth, microonde terrestri (punto-punto, 45 Mbps) |

Per i **satelliti**, due categorie principali:
- **GEO (Geostationary Earth Orbit):** sincronizzato con la rotazione terrestre, orbita equatoriale, ampia copertura (3 satelliti per copertura quasi globale), latenza elevata (~270 ms).
- **LEO (Low Earth Orbit):** non deve seguire l'orbita equatoriale, si sposta velocemente, richiede una costellazione per copertura continua (es. Starlink); latenza bassa (~20 ms), velocità fino a meno di 100 Mbps in downlink.
## Il nucleo della rete (core)
Il **nucleo** di Internet è una **maglia (mesh)** di commutatori di pacchetto e collegamenti che interconnettono i sistemi periferici. Le due funzioni fondamentali nei router sono:
- **Inoltro (forwarding / switching):** azione *locale* — sposta il pacchetto dal collegamento di ingresso al collegamento di uscita appropriato, consultando la **tabella di inoltro locale**.
- **Instradamento (routing):** azione *globale* — determina il percorso end-to-end tramite **algoritmi di instradamento** (vedi [[04 - Livello di Rete]]).
### Commutazione di pacchetto
Nella **commutazione di pacchetto**, i messaggi sono suddivisi in pacchetti inoltrati **indipendentemente** da router a router lungo il percorso, senza prenotazione di risorse.
#### Store-and-forward
Ogni router deve aver ricevuto l'**intero pacchetto** prima di poterlo ritrasmettere sul collegamento in uscita (**store-and-forward**). Su un percorso di $N$ collegamenti di pari velocità $R$:

$$d_{end-to-end} = N \cdot \frac{L}{R} \quad \text{(1 pacchetto)}$$

$$d_{end-to-end} = (N + P - 1) \cdot \frac{L}{R} \quad \text{(P pacchetti)}$$

> [!example] Esempio numerico
> $L = 10$ kbit, $R = 100$ Mbps, percorso one-hop:
> $$d_{trasm} = \frac{10 \times 10^3}{100 \times 10^6} = 0{,}1 \text{ ms}$$
#### Accodamento e perdita
Se il tasso di arrivo supera il tasso di trasmissione sul collegamento in uscita, i pacchetti si **accodano** nel buffer del router (**queuing**). Se il buffer si riempie, i pacchetti in eccesso vengono **scartati (persi)** — il fenomeno è detto perdita di pacchetti.

Il **multiplexing statistico** è il modello di condivisione della capacità: non c'è prenotazione delle risorse, i flussi usano la capacità disponibile su base opportunistica. Rispetto alla commutazione di circuito, la commutazione di pacchetto è inoltre **più semplice**: non richiede l'impostazione della chiamata né di mantenere lo stato dei circuiti su ogni router (**stateless**).
### Commutazione di circuito
Nella **commutazione di circuito**, le risorse (buffer, velocità di trasmissione) lungo l'intero percorso sono **riservate per tutta la durata della sessione**: si stabilisce un **circuito** dedicato punto a punto. Le risorse riservate restano inattive se non utilizzate (*risorse sprecate negli slot inattivi*). È il modello della **rete telefonica tradizionale**.

Due tecniche di multiplexing nel circuito:
- **FDM (Frequency Division Multiplexing):** lo spettro è suddiviso in **bande di frequenza** dedicate a ciascuna connessione; le bande adiacenti sono separate da **guard band**.
- **TDM (Time Division Multiplexing):** il tempo è suddiviso in **frame** di durata fissa; ogni frame è ripartito in slot; ogni circuito riceve slot periodici e trasmette alla velocità massima solo nel proprio slot.

> [!info] Confronto: pacchetto vs circuito
> Collegamento da 1 Gbps; ogni utente: 100 Mbps quando attivo, attivo il 10% del tempo.
> - Commutazione di **circuito**: supporta al massimo **10 utenti** (10 × 100 Mbps = 1 Gbps).
> - Commutazione di **pacchetto** con 35 utenti: la probabilità che più di 10 siano attivi simultaneamente è ≤ 0,0004 (calcolo binomiale). La commutazione di pacchetto è quindi **molto più efficiente** per traffico a raffica (*bursty*), ma non garantisce ritardi costanti — problematico per i servizi in tempo reale (telefonia, videoconferenza).
### Struttura di Internet: "rete di reti"
I sistemi periferici accedono a Internet tramite gli **ISP di accesso**. Collegare ogni ISP direttamente a tutti gli altri non è scalabile: richiederebbe $O(N^2) = \frac{N(N-1)}{2}$ collegamenti. La soluzione è una **gerarchia**:
- **ISP di primo livello (tier-1)** (es. Level 3, Sprint, AT&T, NTT): possiedono reti globali e si connettono tra loro con accordi di **peering settlement-free** (senza scambio di denaro).
- **ISP regionali:** connettono ISP di accesso agli ISP tier-1.
- **ISP di accesso:** connettono gli utenti finali.

Concetti chiave della struttura:
- **Peering link:** collegamento diretto tra ISP di pari livello per scambio di traffico a costo zero.
- **IXP (Internet eXchange Point):** punto d'incontro fisico dove più ISP fanno peering.
- **Multi-homing:** connettersi a due o più ISP fornitori per resilienza e bilanciamento del carico.
- **PoP (Point of Presence):** uno o più router nella rete del fornitore a cui si collegano i clienti.
- **Reti di fornitori di contenuti** (es. Google, Facebook): reti private che connettono data center a Internet, aggirando tier-1 e ISP regionali tramite peering diretto con ISP di accesso.
## Prestazioni: ritardi, perdita, throughput
La qualità della comunicazione in Internet si misura attraverso quattro ritardi di nodo, la perdita di pacchetti e il throughput.
### I quattro ritardi di nodo
Il **ritardo totale di nodo** è la somma di quattro contributi:

$$d_{nodo} = d_{elab} + d_{acc} + d_{trasm} + d_{prop}$$

| Ritardo | Simbolo | Descrizione | Formula / Ordine di grandezza |
|---|---|---|---|
| **Elaborazione nodale** | $d_{elab}$ | Controllo errori sui bit; determinazione del collegamento di uscita | < microsecondi |
| **Accodamento** | $d_{acc}$ | Attesa in coda prima della trasmissione; dipende dalla congestione | variabile |
| **Trasmissione** | $d_{trasm}$ | Tempo per immettere tutti i bit del pacchetto sul collegamento | $d_{trasm} = L/R$ |
| **Propagazione** | $d_{prop}$ | Tempo per propagarsi fisicamente da trasmettitore a ricevitore | $d_{prop} = d/v$ |

Per il ritardo di trasmissione, $L$ è la lunghezza del pacchetto in bit e $R$ è il tasso di trasmissione in bps. Il ritardo di trasmissione **non dipende** dalla lunghezza del collegamento né dalla velocità di propagazione.

Per il ritardo di propagazione, $d$ è la lunghezza del collegamento fisico e $v$ è la velocità di propagazione nel mezzo (~$2 \times 10^8$ m/s in rame/fibra, $3 \times 10^8$ m/s nel vuoto). Il ritardo di propagazione **non dipende** dalla lunghezza del pacchetto né dal tasso di trasmissione.

> [!example] Analogia della carovana
> 10 automobili percorrono 100 km a 100 km/h con un casello che impiega 12 s per auto.
> - Ritardo di **trasmissione** (uscita dal casello): $10 \times 12 = 120$ s.
> - Ritardo di **propagazione** (percorso): $100 \text{ km} / 100 \text{ km/h} = 1$ h.
> - Ritardo totale: 62 minuti.

Il **ritardo end-to-end** si accumula hop per hop lungo il percorso:

$$d_{end-to-end} = \sum_i \left( d_{elab_i} + d_{acc_i} + d_{trasm_i} + d_{prop_i} \right)$$

Lo strumento diagnostico **traceroute** stima il ritardo andata-ritorno verso ogni router $i$ lungo il percorso, inviando tre pacchetti con TTL = $i$ e misurando il tempo di risposta.
### Intensità di traffico e accodamento
Sia $a$ la velocità media di arrivo dei pacchetti (pacchetti/s) e $L$ la lunghezza media. L'**intensità di traffico** è:

$$\frac{L \cdot a}{R}$$

- $La/R \approx 0$: ritardo di accodamento piccolo.
- $La/R \to 1$: ritardo di accodamento crescente, con picchi elevati.
- $La/R > 1$: il carico supera la capacità → il ritardo tende all'**infinito**.
### Perdita di pacchetti
Il buffer del router ha capacità finita. Quando il buffer è pieno, i pacchetti in arrivo sono **scartati (persi)**. Il pacchetto perso può essere ritrasmesso dal nodo precedente, dal sistema terminale, o non ritrasmesso affatto (a seconda del protocollo — vedi [[03 - Livello di Trasporto]]).
### Throughput
Il **throughput** è la frequenza (bit/s) alla quale i bit sono effettivamente trasferiti tra mittente e ricevente:
- **Istantaneo:** misurato in un preciso istante.
- **Medio:** $F/T$ bps per un file di $F$ bit trasferito in $T$ secondi.

Il **collo di bottiglia (bottleneck)** è il collegamento con il tasso minore lungo il percorso, che vincola il throughput end-to-end:

$$throughput \approx \min\{R_i\}$$

dove $R_i$ è il tasso del collegamento $i$-esimo. In un percorso tipico con collegamento di accesso del server $R_s$ e collegamento di accesso del client $R_c$, se 10 connessioni condividono un link di dorsale $R$:

$$throughput_{end-to-end} = \min\!\left(R_c,\, R_s,\, \frac{R}{10}\right)$$

In pratica, $R_c$ o $R_s$ sono quasi sempre il collo di bottiglia.
## Livelli di protocollo e modelli di servizio
### Perché la stratificazione
Una struttura esplicita a **livelli (o strati)** semplifica la progettazione e la manutenzione: ogni livello espone un'interfaccia ben definita al livello superiore e usa i servizi di quello inferiore. Si può modificare l'implementazione di un livello senza toccare gli altri — **modularità**. Potenziali svantaggi: duplicazione di funzionalità tra livelli (es. correzione errori implementata sia a livello trasporto sia a livello collegamento) e necessità di violare la separazione per accedere a informazioni di livelli inferiori.
### La pila di protocolli Internet — 5 livelli
Internet adotta una **pila a cinque livelli (protocol stack)**:

| Livello | Nome | Funzione | Protocolli esempi | PDU |
|---|---|---|---|---|
| 5 | **Applicazione** | Supporto alle applicazioni di rete | HTTP, SMTP, IMAP, DNS | **Messaggio** |
| 4 | **Trasporto** | Trasferimento dati tra processi | TCP, UDP | **Segmento** |
| 3 | **Rete** | Trasferimento datagrammi host-to-host | IP, protocolli di instradamento | **Datagramma** |
| 2 | **Collegamento (link)** | Trasferimento dati tra nodi adiacenti | Ethernet, 802.11 WiFi, PPP | **Frame** |
| 1 | **Fisico** | Bit "sul filo" | — | bit |

Gli host e i router implementano tutti e cinque i livelli; gli **switch** implementano solo i livelli 1 e 2. Per i dettagli di ciascun livello vedi [[02 - Livello di Applicazione]], [[03 - Livello di Trasporto]], [[04 - Livello di Rete]], [[05 - Livello di Collegamento]].
### Incapsulamento
Ogni livello **incapsula** la PDU del livello superiore aggiungendo il proprio **header** ($H$):
- Applicazione genera il **messaggio** $M$.
- Trasporto aggiunge $H_t$ → **segmento** $[H_t \mid M]$.
- Rete aggiunge $H_n$ → **datagramma** $[H_n \mid H_t \mid M]$.
- Collegamento aggiunge $H_l$ → **frame** $[H_l \mid H_n \mid H_t \mid M]$.
- Fisico trasmette i bit del frame sul mezzo.

Ogni pacchetto ha dunque due campi: **header** (informazioni di controllo del livello) e **payload** (dati del livello superiore). Ad ogni hop, l'header di livello 2 è aggiornato con gli indirizzi MAC della coppia sorgente-destinazione immediatamente adiacente; gli header di livello 3 (indirizzi IP) restano invariati lungo il percorso, salvo alcuni campi che cambiano a ogni hop (es. il decremento del **Time To Live**). Gli switch sono **trasparenti** all'instradamento di livello 3: non vengono mai indirizzati esplicitamente.

> [!info] Modello ISO/OSI a 7 strati
> Il modello di riferimento **ISO/OSI** aggiunge due livelli intermedi rispetto alla pila Internet:
> - **Livello 6 — Presentazione:** interpretazione del significato dei dati (crittografia, compressione, convenzioni macchina).
> - **Livello 5 — Sessione:** sincronizzazione, checkpointing e ripristino dello scambio.
> La pila Internet non include questi livelli: se necessari, le funzionalità vanno implementate nell'applicazione stessa.
## Sicurezza di rete
Internet non fu progettata con la sicurezza in mente: la visione originale era quella di un "gruppo di utenti mutuamente fidati collegati a una rete trasparente" [Blumenthal 2001].
### Tipologie di attacco
**Malware:** software malevolo che compromette host. Tipi principali:
- **Virus:** richiedono interazione dell'utente per replicarsi.
- **Worm:** auto-replicanti, si propagano senza interazione.
- **Spyware:** registrano attività e dati dell'utente.
- **Botnet:** reti di host compromessi usati per lanciare attacchi coordinati.

> [!warning] Packet sniffing
> Su media broadcast (Ethernet condivisa, wireless), un'interfaccia di rete in **modalità promiscua** cattura e registra tutti i pacchetti che la attraversano — incluse password in chiaro. I packet sniffer sono **passivi** (non iniettano traffico) e quindi difficili da individuare. Strumento tipico: **Wireshark** (gratuito).

> [!warning] IP spoofing
> Un attaccante può iniettare pacchetti con **indirizzo sorgente falsificato** per: ostacolare l'identificazione e il blocco della sorgente; sfruttare relazioni di fiducia tra host; redirigere risposte verso una vittima (es. **DNS Amplification Attack**: una piccola richiesta DNS genera una risposta molto più grande indirizzata alla vittima).

> [!warning] DoS e DDoS
> Un attacco **DoS (Denial of Service)** mira a rendere un host o un servizio non disponibile agli utenti legittimi. Tre categorie:
> 1. **Attacchi alla vulnerabilità dei sistemi:** pochi pacchetti costruiti ad arte causano blocco o spegnimento del servizio.
> 2. **Bandwidth flooding:** invio massivo di pacchetti verso l'obiettivo a velocità prossima a $R_s$ (velocità di accesso del server), saturando il collegamento. Una singola sorgente ha però tipicamente $R_c \ll R_s$ e sarebbe facile da identificare e bloccare: da qui la necessità del **DDoS** con una botnet.
> 3. **Connection flooding:** apertura di un gran numero di connessioni TCP, impedendo al server di accettare connessioni legittime.
>
> Nel **DDoS (Distributed DoS)** l'attaccante coordina una **botnet**: 1) seleziona l'obiettivo; 2) compromette host attraverso la rete; 3) ordina a tutti gli host compromessi di inviare pacchetti contemporaneamente.
### Linee di difesa
- **Autenticazione:** verificare l'identità del comunicante (le reti cellulari usano la SIM come identità hardware; Internet tradizionale non ha supporto hardware nativo).
- **Riservatezza:** cifratura end-to-end.
- **Integrità:** firme digitali per rilevare e prevenire manomissioni.
- **Restrizioni di accesso:** VPN protette da credenziali.
- **Firewall:** *middlebox* specializzate che filtrano i pacchetti in ingresso per mittente, destinatario e applicazione; proteggono da IP spoofing; rilevano e reagiscono ad attacchi DoS.
## Cenni storici
La storia di Internet ripercorre quasi sessant'anni di innovazione, dall'idea teorica della commutazione di pacchetto alla rete globale odierna.

| Periodo | Fatti chiave |
|---|---|
| **1961–1972** | 1961: Kleinrock dimostra l'efficacia della commutazione di pacchetto (teoria delle code); 1964: Baran (reti militari); 1967: progetto ARPAnet (ARPA); 1969: primo nodo ARPAnet; 1972: dimostrazione pubblica, NCP (primo protocollo host-to-host), prima email, ARPAnet a 15 nodi |
| **1972–1980** | 1970: ALOHAnet (Hawaii) — rete satellitare; 1974: Cerf e Kahn definiscono l'architettura per l'interconnessione di reti (minimalismo, best effort, router stateless, controllo decentralizzato); 1976: Ethernet (Xerox PARC); 1979: ARPAnet a 200 nodi |
| **1980–1990** | 1982: SMTP; 1983: TCP/IP e DNS; 1985: FTP; 1988: controllo della congestione TCP; nuove reti nazionali (CSnet, BITnet, NSFnet, Minitel); 100.000 host connessi |
| **1990–2000s** | Fine anni '80: ARPAnet dismessa; 1991: NSF rimuove restrizioni commerciali NSFnet; HTML/HTTP (Berners-Lee); 1994: Mosaic/Netscape; commercializzazione del Web; messaggistica istantanea, P2P; 50 milioni di host, 100 milioni+ utenti; dorsali a Gbps |
| **2005–presente** | Banda larga domestica (10–100 Mbps); 2008: SDN; WiFi/4G/5G diffusi; Google, Facebook, Microsoft creano reti proprie; cloud computing (AWS, Azure); 2017: più dispositivi mobili che fissi; ~15 miliardi di dispositivi connessi (2023) |

> [!info] Principi fondativi di Cerf e Kahn (1974)
> L'architettura che ha permesso la crescita di Internet si fonda su quattro principi: **minimalismo e autonomia** (ogni rete può collegarsi senza modifiche interne); **modello best effort** (nessuna garanzia di consegna nella rete); **router stateless** (lo stato della connessione è mantenuto agli edge); **controllo decentralizzato** (nessuna autorità centrale).

---

**Prossimo argomento:** [[02 - Livello di Applicazione]] — HTTP, DNS, posta elettronica, architetture P2P e CDN.
