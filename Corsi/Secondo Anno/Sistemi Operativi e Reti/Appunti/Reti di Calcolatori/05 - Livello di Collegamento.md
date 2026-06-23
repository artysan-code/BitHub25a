# Livello di Collegamento
Il livello di collegamento è il quarto livello della pila di protocolli Internet (secondo salendo dal basso) e si occupa del trasferimento dei dati tra nodi **adiacenti** lungo un singolo collegamento fisico. A differenza del livello di rete, che gestisce il percorso end-to-end tra host (vedi [[04 - Livello di Rete]]), il livello di collegamento risolve soltanto il problema locale: "come si muove questo datagramma da questo nodo al nodo successivo sul percorso?". Questa nota copre i meccanismi di rilevazione degli errori, i protocolli di accesso multiplo e le tecnologie LAN (Ethernet, switch, VLAN, ARP).
## Introduzione
### Terminologia di base
Nella terminologia del livello di collegamento, ogni dispositivo connesso a un collegamento prende il nome di **nodo**: host, router e switch sono tutti nodi. Il **collegamento (link)** è il canale di comunicazione che connette nodi adiacenti lungo il percorso — può essere cablato (fibra, doppino, coassiale) o wireless. La PDU del livello di collegamento è il **frame**, che incapsula il datagramma di livello di rete aggiungendo intestazione e trailer.

> [!quote] Definizione — Frame
> Il **frame** è l'unità dati del livello di collegamento. Incapsula un datagramma di livello di rete e aggiunge campi di controllo (intestazione e trailer) necessari al trasferimento affidabile tra nodi adiacenti.

Il livello di rete si serve del livello di collegamento per trasportare datagrammi hop-by-hop lungo il percorso. Gli **switch** operano esclusivamente a livello di collegamento: non sono destinatari finali dei frame ma li inoltrano tra i propri segmenti; dalla prospettiva del livello di rete, uno switch è invisibile (vedi [[01 - Introduzione]], sezione incapsulamento).
### Implementazione: la scheda di rete (NIC)
Il livello di collegamento è implementato principalmente nell'**adattatore di rete (NIC — Network Interface Controller)**, un elemento ibrido di hardware, software e firmware.

- **Lato mittente:** riceve il datagramma dal livello di rete, lo incapsula in un frame, aggiunge i bit di controllo degli errori e implementa il controllo di flusso e di accesso al mezzo.
- **Lato ricevente:** verifica la presenza di errori, gestisce il controllo di flusso, estrae il datagramma dall'intestazione del frame e lo consegna al livello superiore.

L'analogia con i trasporti chiarisce il ruolo del livello: il datagramma è il turista, ogni collegamento è un segmento del viaggio (treno, nave, autobus), il protocollo di collegamento è la modalità di trasporto per quel segmento, l'algoritmo di instradamento del livello di rete è l'agenzia viaggi che ha pianificato l'itinerario completo.
## Servizi del Livello di Collegamento
Il livello di collegamento può offrire i seguenti servizi, non tutti obbligatori per ogni protocollo:

- **Framing:** incapsulamento del datagramma in un frame con intestazione e trailer.
- **Accesso al collegamento (MAC — Medium Access Control):** quando il mezzo è condiviso tra più nodi, il protocollo MAC regolamenta chi può trasmettere e quando; gli indirizzi MAC nell'intestazione identificano mittente e destinatario.
- **Half-duplex / full-duplex:** in **half-duplex** i due estremi del collegamento non trasmettono simultaneamente; in **full-duplex** la trasmissione bidirezionale è concorrente.
- **Consegna affidabile tra nodi adiacenti:** raramente necessaria su canali a basso tasso di errore (fibra); indispensabile su wireless, dove il tasso di errore è elevato — consente di correggere l'errore localmente invece di attendere la ritrasmissione end-to-end da TCP.
- **Controllo di flusso:** regola la velocità tra nodo trasmittente e nodo ricevente adiacenti.
- **Rilevazione degli errori:** il ricevente rileva errori introdotti da attenuazione del segnale e rumore elettromagnetico.
- **Correzione degli errori:** due approcci distinti:
  - **ARQ (Automatic Repeat reQuest):** il ricevente segnala l'errore e il mittente ritrasmette.
  - **FEC (Forward Error Correction):** il ricevente identifica e corregge autonomamente gli errori senza ritrasmissione — utile quando l'RTT è molto elevato o l'applicazione è real-time.
## Rilevazione e Correzione degli Errori
### Schema generale EDC
Lo schema generale di rilevazione-correzione degli errori prevede che il mittente calcoli $r$ bit di controllo $EDC = f(D)$ a partire dai $d$ bit di dati $D$ e li trasmetta insieme. Il ricevente legge $D'$ e $EDC'$ (potenzialmente alterati durante il transito) e verifica se $f(D') = EDC'$: se la condizione non è soddisfatta, l'errore è rilevato.

Nessuno schema rileva il 100% degli errori: ridurre la probabilità di mancata rilevazione richiede più bit EDC (maggiore overhead) e calcoli più complessi.
### Controllo di Parità
**Singolo bit di parità:** il mittente aggiunge un bit tale che il numero totale di bit a 1 nel blocco $d+1$ sia pari (parità pari) o dispari (parità dispari). Il ricevente conta i bit a 1 ricevuti; se la parità non corrisponde, almeno un errore è avvenuto. Il singolo bit di parità rileva qualsiasi numero **dispari** di errori ma non due errori che si annullano.

**Parità bidimensionale:** i $d$ bit dei dati sono disposti in una matrice $i \times j$; si calcola un bit di parità per ciascuna riga e ciascuna colonna. Con questa organizzazione:
- Si **rileva e corregge** qualsiasi errore su un singolo bit (si individua la riga e la colonna in errore).
- Si rilevano tutte le combinazioni di al più 3 errori.
- Si rileva qualsiasi numero dispari di errori.
- Due errori sulla stessa riga vengono rilevati sulle colonne corrispondenti (e viceversa), ma **non sono correggibili**.
- Quattro errori ai vertici di un rettangolo nella matrice **non sono rilevabili**: la parità di ogni riga e colonna risulta inalterata.

> [!info] Limite della parità nella realtà
> La parità è adatta solo quando gli errori sono rari e statisticamente indipendenti. Nella pratica gli errori avvengono in **burst** (raffiche): un burst non rilevato da un singolo bit di parità ha probabilità che può avvicinarsi al 50%.
### Checksum Internet
Il checksum Internet (già introdotto nel contesto di UDP in [[03 - Livello di Trasporto]]) tratta il contenuto del segmento come una sequenza di interi a 16 bit. Il mittente calcola il **complemento a 1 della somma in complemento a 1** di tutta la sequenza. Il ricevente somma il checksum ricevuto agli altri campi: il risultato deve essere tutto 1 (equivalentemente, il complemento a 1 del risultato deve essere tutto 0). Rilevazione debole ma calcolo semplicissimo, adatto per il software; il CRC è invece preferito nell'hardware della NIC.
### CRC (Cyclic Redundancy Check)
Il CRC è la tecnica di rilevazione degli errori più potente ed è ampiamente usato in pratica da **Ethernet** e **802.11 WiFi**.

**Principio:** si usa un polinomio generatore $G$ di $r+1$ bit (il bit più significativo deve essere 1, definito nello standard). Il mittente aggiunge $r$ bit $R$ ai $d$ bit di dati $D$ in modo che la sequenza $\langle D, R \rangle$ sia divisibile per $G$ in aritmetica modulo 2.

$$\langle D, R \rangle = D \cdot 2^r \oplus R$$

$$R = \left( D \cdot 2^r \right) \bmod G$$

Il ricevente divide la sequenza ricevuta $\langle D', R' \rangle$ per $G$: se il resto è diverso da zero, un errore è stato rilevato.

**Aritmetica modulo 2:** addizione e sottrazione coincidono entrambe con lo XOR bit a bit (nessun riporto né prestito). Le sequenze di bit corrispondono ai coefficienti — in modulo 2 — di polinomi, dove il grado del polinomio è uguale al numero di bit meno 1.

> [!example] Calcolo CRC
> $D = 101011$, $G = 1001$ ($r = 3$).
> Si calcola $D \cdot 2^3 = 101011000$.
> Divisione in modulo 2 per $G = 1001$: il resto è $R = 011$.
> La sequenza trasmessa è $\langle D, R \rangle = 101011011$.
> Il ricevente divide $101011011$ per $1001$: resto 0 $\Rightarrow$ nessun errore rilevato.

**Proprietà del generatore $G$:**
- Se $G$ ha un **numero pari di bit a 1**, rileva qualsiasi numero dispari di errori. Dimostrazione: un errore con numero dispari di bit a 1 ha $E(1)=1$; ma se $E(x)=Q(x)\cdot G(x)$ e $G(1)=0$ si ottiene la contraddizione $1=Q(1)\cdot 0$. Caso particolare: $G(x)=x+1$ (in bit "11") è il classico controllo di parità.
- Se $G$ ha **almeno due bit a 1**, rileva qualsiasi errore singolo (un errore singolo è $x^k$, divisibile solo da $x^i$ con $i\leq k$; un $G$ con almeno due bit a 1 non ha questa forma).
- Rileva **tutti i burst di lunghezza $\leq r$ bit**.
- La frazione di burst più lunghi di $r$ bit **rilevati** è circa $1 - 2^{-r}$; equivalentemente, la frazione **non rilevata** è $2^{-r}$.
## Protocolli di Accesso Multiplo
### Tipi di collegamento
Esistono due categorie fondamentali di collegamento:

- **Punto a punto:** un solo trasmittente, un solo ricevente. Esempi: PPP per l'accesso dial-up, collegamento host-switch Ethernet.
- **Broadcast:** canale fisico condiviso tra più nodi; ogni frame trasmesso è ricevuto da tutti. Esempi: Ethernet "vecchia scuola" a cavo condiviso, 802.11 WiFi, 4G/5G, satellite.

Il problema centrale del canale broadcast è la **collisione**: se due o più nodi trasmettono simultaneamente i segnali si sovrappongono e i frame risultano corrotti.

Un **protocollo MAC ideale** per un canale a $R$ bps dovrebbe garantire: (1) un singolo nodo attivo trasmette a $R$ bps; (2) con $M$ nodi attivi ciascuno trasmette a $R/M$ in media; (3) completamente decentralizzato (nessun coordinatore, nessuna sincronizzazione obbligatoria); (4) semplicità implementativa.

I protocolli MAC si suddividono in tre classi: **suddivisione del canale**, **accesso casuale** e **a rotazione**.
### Protocolli a Suddivisione del Canale
#### TDMA (Time Division Multiple Access)
Il canale è diviso in **time frame** ripetuti; ogni time frame è suddiviso in $N$ slot temporali, uno per nodo. La durata di ogni slot corrisponde al tempo di trasmissione di un pacchetto. Gli slot non usati sono **idle**.

Ogni nodo trasmette a $R$ bps ma solo per $1/N$ del tempo, ottenendo una velocità media di $R/N$ indipendentemente dal carico. Un nodo deve attendere il proprio slot anche se è l'unico attivo nella rete.
#### FDMA (Frequency Division Multiple Access)
Lo spettro del canale è diviso in **bande di frequenza**; ciascun nodo ha una banda fissa, le bande non usate sono idle. Un nodo trasmette non appena ha dati (senza attendere turni temporali), ma la velocità è limitata alla propria banda ridotta: anche qui la velocità effettiva è $R/N$ indipendentemente dal carico.
### Protocolli ad Accesso Casuale
Quando un nodo ha dati, trasmette a $R$ bps senza coordinamento a priori. Due o più nodi in trasmissione simultanea generano una collisione. Il protocollo specifica come rilevare e recuperare dalle collisioni.
#### Slotted ALOHA
**Assunzioni:** tutti i frame hanno la stessa dimensione $L$ bit; il tempo è diviso in slot di durata $L/R$; i nodi iniziano le trasmissioni solo all'inizio di uno slot; i nodi sono sincronizzati; se due o più nodi trasmettono nello stesso slot, la collisione è rilevata da tutti prima della fine dello slot.

**Operazioni:** quando un nodo ha un frame, lo trasmette all'inizio dello slot successivo. Se non si verifica collisione, il nodo può prepararsi a inviare il frame successivo. In caso di collisione, il nodo ritrasmette in ogni slot successivo con probabilità $p$ (come lanciare una moneta truccata: testa = ritrasmetti, croce = salta lo slot).

**Efficienza** con $N$ nodi, ciascuno che trasmette con probabilità $p$:

$$\text{efficienza}(p) = N p (1-p)^{N-1}$$

La probabilità ottimale che massimizza l'efficienza è $p^* = 1/N$:

$$\text{efficienza}(p^*) = \left(1 - \frac{1}{N}\right)^{N-1} \xrightarrow{N \to \infty} \frac{1}{e} \approx 37\%$$

Al massimo il 37% degli slot svolge lavoro utile; il 37% è idle; il 26% subisce collisioni. La velocità effettiva massima è $0{,}37 R$ bps.

**Pro:** un singolo nodo attivo usa il canale a $R$ bps; altamente decentralizzato; semplice.
**Contro:** collisioni; slot idle; richiede sincronizzazione degli orologi.
#### ALOHA Puro (Unslotted)
Nessuna sincronizzazione: il nodo trasmette immediatamente quando arriva un frame. In caso di collisione (assenza di ACK), ritrasmette con probabilità $p$, altrimenti attende un tempo pari alla trasmissione di un frame e riprova.

Un frame trasmesso a $t_0$ può collidere con frame inviati nell'intervallo $[t_0 - 1,\, t_0 + 1]$ — una finestra doppia rispetto a Slotted ALOHA:

$$P(\text{successo qualsiasi nodo}) = N \cdot p \cdot (1-p)^{2(N-1)}$$

$$p^* = \frac{1}{2N-1} \xrightarrow{N \to \infty} \text{efficienza massima} = \frac{1}{2e} \approx 18\%$$

Esattamente la metà di Slotted ALOHA, perché la finestra vulnerabile è doppia.
#### CSMA (Carrier Sense Multiple Access)
Regola fondamentale: **"ascolta prima di trasmettere" (carrier sense)**. Se il canale è rilevato idle, il nodo trasmette; se il canale è occupato, il nodo differisce la trasmissione.

Le collisioni possono tuttavia ancora verificarsi a causa del **ritardo di propagazione**: due nodi possono non aver ancora sentito la trasmissione dell'altro già avviata quando iniziano la propria. Una collisione spreca l'intero tempo di trasmissione del pacchetto.

> [!info] CSMA e wireless
> CSMA/CD è usato in Ethernet; CSMA/CA (Collision Avoidance) è usato in 802.11 WiFi (vedi [[06 - Reti Wireless e Mobilita]]). Il rilevamento della collisione sul wireless è non banale perché il segnale trasmesso domina quello ricevuto.
#### CSMA/CD (CSMA with Collision Detection)
CSMA/CD riduce lo spreco interrompendo la trasmissione **non appena la collisione è rilevata** e inviando un segnale di disturbo (**jam**) che garantisce a tutti i nodi di scartare il frame per errore CRC.

**Algoritmo Ethernet CSMA/CD:**
```
1. Ricevuto il datagramma dal livello di rete, crea il frame.
2. Ascolta il canale: se idle trasmetti; se busy aspetta.
3. Trasmesso il frame senza rilevare altri segnali: fine.
4. Rilevata trasmissione concorrente durante l'invio:
   interrompi, invia segnale JAM.
5. Binary exponential backoff: dopo la m-esima collisione,
   scegli K casuale in {0, 1, ..., 2^m - 1};
   attendi K × 512 bit time; torna al passo 2.
   (m limitato a 10)
```

**Vincolo fondamentale dello slot time:** affinché il mittente $A$ rilevi sempre la collisione con $B$, $A$ deve essere ancora in trasmissione quando il segnale di $B$ lo raggiunge. Questo impone:

$$T_\text{trasm} = \frac{L}{R} > 2\tau$$

dove $\tau$ è il ritardo di propagazione massimo in una direzione. Si definisce uno **slot time**:

$$\text{slot time} = 2\tau_\text{max} + \text{durata\_jam\_massima}$$

In Ethernet a 10 e 100 Mbps lo slot time è **512 bit (64 byte)**. In Gigabit Ethernet è 4096 bit (512 byte) per mantenere la stessa distanza massima tra nodi.

**Efficienza CSMA/CD:**

$$\text{efficienza} = \frac{1}{1 + 5 \, d_\text{prop} / d_\text{trasm}}$$

dove $d_\text{prop}$ è il massimo ritardo di propagazione tra due NIC e $d_\text{trasm}$ è il tempo di trasmissione di un frame di dimensione massima. L'efficienza tende a 1 se $d_\text{prop} \to 0$ oppure $d_\text{trasm} \to \infty$.

> [!example] Efficienza CSMA/CD — esempio numerico
> $d_\text{prop} = 256$ bit time; $d_\text{trasm} = 12144$ bit time (frame 1518 B a 100 Mbps).
> $$\text{efficienza} = \frac{1}{1 + 5 \times 256 / 12144} \approx 90\%$$
### Protocolli a Rotazione (Taking Turns)
La suddivisione del canale è inefficiente a basso carico (slot/banda assegnati anche a nodi inattivi); l'accesso casuale genera overhead a carico elevato (collisioni frequenti). I protocolli a rotazione cercano il meglio di entrambi.
#### Polling
Un **nodo controllore** centralizzato invita in round robin ciascun nodo a trasmettere per un numero massimo di frame. Elimina collisioni e slot idle. Svantaggi: **ritardo di polling** (anche un singolo nodo attivo deve aspettare che il controllore lo contatti); **singolo punto di rottura** (se il master cade, l'intera LAN si ferma). Usato in **Bluetooth**.
#### Token Passing
Un frame di controllo detto **token (gettone)** circola sequenzialmente tra i nodi in ordine fissato. Un nodo può trasmettere solo mentre possiede il token (entro un massimo concordato), poi lo passa al successivo. Alta efficienza, completamente decentralizzato. Svantaggi: overhead del token; latenza; **singolo punto di rottura** (perdita del token o rottura di un nodo). Usato in **FDDI** e **Token Ring (IEEE 802.5)**.
### Rete di Accesso via Cavo (DOCSIS)
Il protocollo **DOCSIS (Data Over Cable Service Interface Specification)** usato nelle reti via cavo combina tre tecniche di accesso:

- **FDM:** i canali downstream e upstream operano su frequenze distinte.
- **TDM:** il **CMTS (Cable Modem Termination System)** assegna minislot upstream tramite messaggi MAP in downstream.
- **Accesso casuale con binary backoff:** per i minislot "contesi" (richieste di banda), i modem competono con meccanismo simile al backoff Ethernet.

I canali downstream (da CMTS a modem) arrivano fino a 1,6 Gbps per canale: poiché un solo CMTS trasmette, non c'è problema di accesso multiplo. I canali upstream (da modem a CMTS) arrivano fino a 1 Gbps per canale e richiedono il protocollo di accesso multiplo descritto.
## LAN
### Indirizzi MAC
Ogni interfaccia di rete ha due tipi di indirizzo:

- **Indirizzo IP** (32 bit in IPv4, 128 bit in IPv6): indirizzo gerarchico di livello di rete, usato per l'instradamento end-to-end; dipende dalla sottorete di appartenenza.
- **Indirizzo MAC** (o LAN, fisico, Ethernet): 48 bit; memorizzato nella ROM della NIC; usato localmente per identificare le interfacce fisicamente connesse nella stessa sottorete; notazione esadecimale (es. `1A-2F-BB-76-09-AD`).

> [!quote] Definizione — Indirizzo MAC
> L'**indirizzo MAC** è un identificatore a 48 bit assegnato alla NIC dal produttore, che garantisce l'unicità globale grazie all'allocazione gestita dall'IEEE. È piatto e portabile: un'interfaccia conserva il proprio indirizzo MAC indipendentemente dalla rete a cui è connessa.

**Analogia con il mondo reale:**
- Indirizzo MAC ≈ **codice fiscale** (piatto, non dipende dalla posizione geografica).
- Indirizzo IP ≈ **indirizzo postale** (gerarchico, dipende dalla sottorete).

L'indirizzo di **broadcast MAC** è `FF-FF-FF-FF-FF-FF`: un frame con questo indirizzo di destinazione è ricevuto e processato da tutte le interfacce nella stessa LAN.
### ARP (Address Resolution Protocol)
**Problema:** dato l'indirizzo IP di un'interfaccia nella stessa sottorete, come determinarne l'indirizzo MAC per creare il frame da trasmettere?

Ogni nodo IP mantiene una **tabella ARP** per ciascuna interfaccia, con voci della forma:

$$\langle \text{indirizzo IP};\; \text{indirizzo MAC};\; \text{TTL} \rangle$$

Il TTL tipico è 20 minuti, dopo i quali la voce è rimossa e deve essere riacquisita.

**Protocollo ARP in azione** (A vuole inviare a B nella stessa sottorete, MAC di B non noto):
1. A invia in **broadcast** una richiesta ARP contenente l'IP di B (MAC destinazione = `FF-FF-FF-FF-FF-FF`); tutti i nodi della sottorete ricevono la query.
2. Solo B risponde **in unicast** con una risposta ARP contenente il proprio indirizzo MAC; nella risposta i campi source/target sono invertiti rispetto alla richiesta.
3. A aggiorna la propria tabella ARP con la mappatura IP→MAC di B.

> [!info] ARP e IPv6
> In IPv6 le funzionalità di ARP sono integrate nel **Neighbor Discovery Protocol (NDP)**, basato su messaggi ICMPv6 multicast anziché broadcast.

**Invio a nodo esterno alla sottorete** (A $\to$ B via router R):
1. A crea il datagramma IP con sorgente A e destinazione B.
2. A rileva che B appartiene a una sottorete diversa (confronto del prefisso); il prossimo hop è il router R.
3. A usa ARP per risolvere il MAC dell'interfaccia di R nella propria sottorete; crea un frame con MAC destinazione = MAC di R.
4. R riceve il frame, decapsula il datagramma, determina l'interfaccia di uscita verso la sottorete di B.
5. R usa ARP per risolvere il MAC di B; crea un **nuovo** frame con MAC sorgente = MAC dell'interfaccia R lato B e MAC destinazione = MAC di B.
6. B riceve il frame e consegna il datagramma al livello di rete.

In tutto il percorso gli indirizzi IP sorgente e destinazione nel datagramma rimangono invariati; soltanto gli indirizzi MAC cambiano a ogni hop.

> [!warning] ARP Spoofing / ARP Poisoning
> ARP è **senza stato**: un nodo aggiorna la propria tabella ARP a ogni risposta ricevuta, anche non sollecitata. Un attaccante può sfruttare questa proprietà inviando risposte ARP contraffatte:
> - **DoS (Denial of Service):** più indirizzi IP associati allo stesso MAC, sovraccaricando una singola interfaccia.
> - **MITM (Man-in-the-Middle):** l'attaccante associa il proprio MAC all'IP della vittima, intercettando (e potenzialmente modificando) tutto il traffico diretto a quell'indirizzo prima di re-inoltrarlo.
### Probe ARP e Announcement ARP
**Probe ARP:** prima di usare un indirizzo IP, un host invia una richiesta ARP con `SPA = 0.0.0.0` (nessun indirizzo ancora assegnato). Se nessuno risponde, l'indirizzo è libero. Le coppie (SHA, SPA) e (THA, TPA) non sono mai valide in un probe ARP, impedendo di creare o aggiornare voci ARP altrui per errore.

**Announcement ARP:** un host X che vuole aggiornare le voci nelle tabelle degli altri nodi invia una richiesta ARP in cui `SPA = TPA = indirizzo IP di X` e `SHA = MAC di X`, `THA = 0`. Tutti i nodi che ricevono questo messaggio aggiornano le proprie tabelle ARP.
### Ethernet
Ethernet è la tecnologia dominante per le LAN cablate: prima tecnologia LAN ampiamente diffusa, rimasta rilevante grazie alla semplicità e alla scalabilità in velocità. Inventata da **Bob Metcalfe**, che ha ricevuto il **Premio ACM Turing 2022** per questo contributo. Velocità: da **10 Mbps** fino a **400 Gbps** sullo stesso chip (es. Broadcom BCM5761).
#### Evoluzione topologica
- **Bus** (fino a metà anni '90): tutti i nodi nello stesso cavo coassiale, stesso dominio di collisione; un cavo tagliato fermava l'intera rete.
- **Stella con hub** (fino anni 2000): l'**hub** è un dispositivo a livello fisico che rigenera il segnale in ingresso e lo ritrasmette su **tutte** le porte; tutti i nodi rimangono nello stesso dominio di collisione.
- **Stella con switch** (oggi prevalente): lo switch di livello 2 al centro; ogni segmento è un dominio di collisione separato, eliminando di fatto le collisioni tra host diversi.
#### Struttura del frame Ethernet
```
| Preambolo | Ind. dest. | Ind. src. | Tipo | Payload | CRC |
```

- **Preambolo** (8 byte): 7 byte `10101010` "risvegliano" le NIC e sincronizzano i clock; 1 byte `10101011` segnala l'inizio effettivo del frame con i due 1 consecutivi finali.
- **Indirizzo di destinazione** (6 byte): MAC del destinatario; se non corrisponde all'indirizzo proprio e non è broadcast, il frame è scartato.
- **Indirizzo sorgente** (6 byte): MAC del mittente.
- **Tipo** (2 byte): protocollo di livello superiore (IP, ARP, AppleTalk…); usato per il **demultiplexing** al ricevente.
- **Payload** (46–1500 byte): il datagramma IP. Minimo 46 byte (padding se necessario); massimo **1500 byte** (MTU Ethernet). La fine del frame è determinata a livello fisico dall'assenza di transizioni sul mezzo.
- **CRC** (4 byte): controllo a ridondanza ciclica; un errore rilevato causa lo scarto immediato del frame.

Dimensione totale del frame (escluso preambolo): da 64 byte (512 bit) a 1518 byte. Lo slot time di 512 bit vale per Ethernet a 10 e 100 Mbps.

> [!info] Standard 802.3
> Il formato del frame e il protocollo MAC CSMA/CD sono comuni a tutti gli standard 802.3; ciò che differisce tra le versioni è la velocità (da 2 Mbps a 400 Gbps) e il mezzo fisico (coassiale, doppino Cat. 5/6, fibra ottica). Gigabit Ethernet opera tipicamente in **full-duplex**, quindi CSMA/CD non è necessario.

**Proprietà di Ethernet:**
- **Senza connessione:** nessun handshake tra NIC mittente e ricevente prima dell'invio del frame.
- **Non affidabile:** la NIC ricevente non invia ACK né NAK; i dati persi sono recuperati solo dai livelli superiori (es. TCP, vedi [[03 - Livello di Trasporto]]).
- **Protocollo MAC:** CSMA/CD unslotted con binary exponential backoff.

**Limite fisico:** segmento massimo di 100 m su doppino Cat. 5 per Fast Ethernet (100BASE-TX) e Gigabit Ethernet. Il ritardo di propagazione sul doppino è circa il 60% della velocità della luce:

$$v = \frac{200\text{ m}}{111{,}2 \times 10^{-8}\text{ s}} \approx 1{,}8 \times 10^8\text{ m/s} \approx 0{,}6\,c$$
### Switch a Livello di Collegamento
Lo **switch** è un commutatore di pacchetti a livello di collegamento. Opera in modalità **store-and-forward**: riceve il frame completo, verifica il CRC, poi lo inoltra sull'interfaccia di uscita appropriata.

**Caratteristiche principali:**
- **Trasparente:** gli host non sanno che gli switch esistono. Le interfacce degli switch non hanno indirizzi MAC usati nella commutazione; i MAC dei frame non vengono mai alterati.
- **Plug-and-play, autoapprendimento:** non richiede configurazione manuale.
- **Full-duplex su ogni segmento:** trasmissioni simultanee su segmenti diversi sono possibili senza collisioni; la banda aggregata è maggiore rispetto all'hub.
- **Supporto a collegamenti eterogenei:** velocità e mezzi diversi sulle porte.

**Tabella di commutazione (switch table):** ogni voce è composta da $(\text{indirizzo MAC},\, \text{interfaccia},\, \text{timestamp})$.

**Autoapprendimento:** ogni volta che arriva un frame, lo switch registra il MAC sorgente e l'interfaccia di ingresso nella tabella, aggiornando il timestamp.

**Algoritmo di filtraggio e inoltro:**
```
1. Registra MAC sorgente e interfaccia di ingresso nella tabella.
2. Cerca il MAC di destinazione nella tabella.
3. SE trovato:
     SE la destinazione è sul segmento di arrivo:
       scarta il frame (mittente e destinatario già sullo stesso segmento)
     ALTRIMENTI:
       inoltra il frame sull'interfaccia indicata
4. SE non trovato:
     FLOOD: invia su tutte le interfacce eccetto quella di arrivo
     (il MAC di destinazione nel frame rimane invariato, non diventa broadcast)
```

Il meccanismo di autoapprendimento funziona in modo identico anche con più switch in cascata.

> [!quote] Definizione — Flooding dello switch
> Il **flooding** è l'operazione con cui uno switch, non trovando in tabella il MAC di destinazione, invia il frame su tutte le proprie interfacce eccetto quella di arrivo. L'indirizzo MAC di destinazione nel frame rimane l'indirizzo unicast originale — non viene sostituito con l'indirizzo broadcast.

**Confronto Switch vs. Router:**

| | Switch | Router |
|---|---|---|
| Livello | Collegamento (L2) | Rete (L3) |
| Intestazione esaminata | MAC | IP |
| Tabella | Commutazione (autoapprendimento con flooding) | Inoltro (calcolata con algoritmi di instradamento) |
| Topologia ammessa | Albero (Spanning Tree Protocol — cicli vietati) | Cicli permessi (TTL elimina i loop) |
| Scalabilità | Tabelle ARP grandi; ingente traffico ARP e broadcast | Instradamento gerarchico, aggregazione degli indirizzi |
| Isolamento traffico | Flood dei MAC sconosciuti; broadcast inoltrato a tutti | Percorsi determinati dalla funzione di instradamento |
### VLAN (Virtual LAN)
All'aumentare della LAN, il singolo dominio di broadcast genera problemi di scalabilità, efficienza, sicurezza e gestione:

- Tutto il traffico broadcast L2 (ARP, DHCP, MAC sconosciuto) attraversa l'intera LAN.
- Un utente che si sposta fisicamente vuole rimanere connesso logicamente alla propria VLAN.
- Separare i reparti (es. CS ed EE) richiederebbe switch fisici distinti.

**VLAN basate sulle porte (port-based VLAN):** le porte dello switch sono raggruppate via software; un singolo switch fisico opera come più switch virtuali. Il traffico da/verso le porte di una VLAN raggiunge **solo** le porte di quella stessa VLAN. Le porte possono essere riassegnate dinamicamente senza modifiche hardware. È possibile anche una VLAN basata sugli indirizzi MAC degli endpoint.

**Inoltro inter-VLAN:** avviene tramite routing, esattamente come tra switch fisici separati. In pratica, i produttori combinano switch e router in un unico apparato.

**Porta trunk:** per connettere $N$ VLAN tra due switch fisici, dedicare una porta per VLAN non è scalabile. La soluzione è una **porta trunk** — un singolo collegamento che trasporta frame di tutte le VLAN; i frame devono includere il VLAN ID per distinguere l'appartenenza.

**Formato frame 802.1Q:** aggiunge un **tag di 4 byte** tra il campo degli indirizzi e il campo tipo del frame Ethernet standard:

- **Tag Protocol Identifier** (2 byte, valore fisso `81-00`): occupa la posizione dell'EtherType e distingue il frame tagged da uno untagged.
- **Tag Control Information** (2 byte): 12 bit di **VLAN ID** (fino a 4094 VLAN), 3 bit di **priority** (analogo all'IP TOS), 1 bit di **drop eligible indicator**.
- Il CRC viene ricalcolato dopo l'aggiunta del tag.

> [!info] EVPN / VXLAN
> Per estendere le VLAN Ethernet su scala geografica (tra data center distanti), si usa il tunneling **VXLAN**: i frame Ethernet L2 vengono incapsulati in datagrammi UDP/IP, permettendo di "allungare" una rete Layer 2 su un'infrastruttura Layer 3. È la base delle reti overlay nei data center moderni [RFC 7348].

---

**Prossimo argomento:** [[06 - Reti Wireless e Mobilita]] — IEEE 802.11 WiFi, accesso multiplo CSMA/CA, reti cellulari 4G/5G e gestione della mobilità.
