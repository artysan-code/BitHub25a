# Reti Wireless e Mobilita
Le reti wireless e la gestione della mobilità costituiscono il capitolo conclusivo del modello a strati analizzato in questo modulo. Dopo aver studiato i protocolli dal livello di applicazione ([[02 - Livello di Applicazione]]) fino al livello di collegamento ([[05 - Livello di Collegamento]]), questa nota affronta le peculiarità dei canali radio e la sfida di mantenere la connettività quando un host si sposta tra punti di aggancio diversi — problema che le reti cablate non devono affrontare.
## Contesto e componenti di una rete wireless
Nel 2019 si contavano già 10 abbonati wireless ogni abbonato fisso, e 5 dispositivi a banda larga mobile ogni dispositivo fisso. Le reti 4G/5G abbracciano oggi lo stack Internet completo, compreso l'uso di [[04 - Livello di Rete#SDN|SDN]].

> [!quote] Definizione — Wireless e Mobilità
> **Wireless** indica la comunicazione tramite collegamento radio; **mobilità** indica la gestione dell'utente che cambia punto di aggancio alla rete spostandosi. I due problemi sono distinti: un host può essere wireless senza essere mobile, e un host mobile può temporaneamente non usare un collegamento wireless.

I **componenti fondamentali** di una rete wireless sono:
- **Host wireless**: laptop, smartphone, dispositivi IoT; possono essere fissi o mobili. *Wireless non implica necessariamente mobilità.*
- **Collegamento wireless**: connette gli host alla stazione base o ad altri host; regolato da un protocollo di accesso multiplo (vedi [[05 - Livello di Collegamento]]); varia per tasso trasmissivo, distanza e banda di frequenza.
- **Stazione base**: elemento chiave dell'infrastruttura, connessa alla rete cablata, fa da relay a livello di collegamento tra rete cablata e host nella propria area (es. torre cellulare, access point).

Le reti wireless si organizzano in due modalità:
- **Modalità infrastruttura**: i servizi (indirizzamento, routing) sono forniti dalla rete; prevede **handoff** — il passaggio di un host dal raggio di una stazione base a quello di un'altra.
- **Rete ad hoc**: nessuna stazione base; gli host si autogestiscono per routing, indirizzamento e altri servizi.

**Tassonomia** per numero di hop e presenza di infrastruttura:

| | Hop singolo | Hop multipli |
|---|---|---|
| Con infrastruttura | WiFi, rete cellulare | Wi-Fi mesh, reti di sensori |
| Senza infrastruttura | Bluetooth | MANETs, VANETs |
## Caratteristiche dei collegamenti wireless
I canali radio presentano criticità assenti nei collegamenti cablati, che influenzano profondamente la progettazione dei protocolli MAC e fisico.
### Attenuazione
Le radiazioni elettromagnetiche si attenuano attraversando ostacoli (assorbimento, diffusione). Anche in spazio libero l'intensità cala con la distanza; l'**attenuazione di spazio libero (free space path loss)** segue la relazione:

$$\text{attenuazione di spazio libero} \sim (f \cdot d)^2$$

dove $f$ è la frequenza e $d$ la distanza. Frequenza più alta o distanza maggiore producono maggiore attenuazione.
### Propagazione su più cammini
Parte del segnale si riflette su oggetti e terreno, percorrendo tratti di lunghezza diversa e arrivando al ricevitore in istanti diversi (**multipath propagation**). Il **tempo di coerenza $T_c$** è il tempo in cui il bit è presente nel canale e influenza la massima velocità di trasmissione: i tempi di coerenza non devono sovrapporsi.
### Interferenze da altre sorgenti
Le frequenze standard sono condivise. Nella banda 2,4 GHz operano contemporaneamente WiFi, Bluetooth e telefoni cordless, che competono per lo stesso canale radio. A questo si aggiunge il **rumore elettromagnetico** ambientale prodotto da apparecchi come i forni a microonde, che non trasmettono segnali di rete ma degradano il canale. Gli standard 802.11 più recenti impiegano la banda **5 GHz** per ridurre le interferenze.
### SNR e BER
> [!quote] Definizione — SNR e BER
> **SNR (Signal-to-Noise Ratio)**: rapporto tra potenza del segnale utile e rumore di fondo; SNR più alto rende più facile estrarre il segnale.
> **BER (Bit Error Rate)**: probabilità che un singolo bit sia ricevuto in errore.

Tra SNR e BER esiste un bilanciamento:
- Aumentare la potenza trasmissiva → aumenta l'SNR → diminuisce il BER; ma aumenta il consumo energetico e le interferenze verso gli altri.
- Per un dato SNR, una tecnica di modulazione con tasso di bit più alto produce un BER più alto.

Il livello fisico si adatta **dinamicamente** (cambio di tecnica di modulazione) al variare dell'SNR. Esempi di tecniche di modulazione:

| Tecnica | Tasso bit |
|---|---|
| BPSK | 1 Mbps |
| QAM16 | 4 Mbps |
| QAM256 | 8 Mbps |
### Problema del terminale nascosto
Due nodi A e C non si "vedono" tra loro ma trasmettono entrambi verso B: l'interferenza avviene presso B senza che A e C lo sappiano. Anche l'attenuazione può causare terminali nascosti: A e C sono fuori raggio l'uno dell'altro ma entrambi nel raggio di B. Questo problema rende impossibile il rilevamento delle collisioni tipico di CSMA/CD (vedi [[05 - Livello di Collegamento#CSMA/CD|CSMA/CD in Ethernet]]) e motiva l'uso di CSMA/CA nel WiFi.
## WiFi: 802.11 Wireless LAN
### Standard 802.11
Lo standard IEEE 802.11 definisce una famiglia di specifiche per le reti locali wireless. Tutti gli standard usano **CSMA/CA** per l'accesso multiplo e supportano sia la modalità infrastruttura sia quella ad hoc.

| Standard | Anno | Max data rate | Raggio | Frequenza |
|---|---|---|---|---|
| 802.11b | 1999 | 11 Mbps | 30 m | 2,4 GHz |
| 802.11g | 2003 | 54 Mbps | 30 m | 2,4 GHz |
| 802.11n (WiFi 4) | 2009 | 600 Mbps | 70 m | 2,4 / 5 GHz |
| 802.11ac (WiFi 5) | 2013 | 3,47 Gbps | 70 m | 5 GHz |
| 802.11ax (WiFi 6) | 2020 | 14 Gbps | 70 m | 2,4 / 5 GHz |
| 802.11af | 2014 | 35–560 Mbps | 1 Km | Bande TV inutilizzate (54–790 MHz) |
| 802.11ah | 2017 | 347 Mbps | 1 Km | 900 MHz |
### Architettura BSS
La **BSS (Basic Service Set)** è la "cella" della modalità infrastruttura: comprende uno o più host wireless e un **AP (Access Point)**, connesso a switch/router verso Internet. In modalità ad hoc la BSS contiene solo host, senza AP.
### Canali e associazione
**Canali**: lo spettro è diviso in canali a frequenze diverse; l'amministratore dell'AP sceglie la frequenza. Nella banda 2,4 GHz esistono **3 canali non sovrapposti** (separati da almeno 4 canali): è possibile installare 3 AP nello stesso posto su canali 1, 6 e 11, triplicando il throughput aggregato.

**Associazione**: all'arrivo in una nuova area, un host scansiona i canali in ascolto per **frame beacon** — inviati periodicamente dall'AP, contengono SSID e indirizzo MAC. L'host sceglie l'AP, si autentica e invia una richiesta DHCP per ottenere un indirizzo IP nella sottorete.

Due modalità di scansione:
- **Passiva**: (1) beacon dagli AP → (2) richiesta di associazione da H1 all'AP → (3) risposta di associazione dall'AP.
- **Attiva**: (1) frame sonda in broadcast da H1 → (2) risposte degli AP → (3) richiesta di associazione → (4) risposta di associazione.
### Protocollo MAC: CSMA/CA
**Perché non CSMA/CD**: il segnale trasmesso è molto più forte del segnale ricevuto (attenuazione), rendendo difficile rilevare le collisioni; il problema del terminale nascosto le rende non rilevabili in ogni caso. L'obiettivo è quindi **evitare** le collisioni (Collision Avoidance), non rilevarle.

**Algoritmo mittente**:
1. Se il canale è **idle per DIFS** → trasmette il frame per intero (no Collision Detection).
2. Altrimenti:
   - Sceglie un valore di ritardo casuale (**binary exponential backoff**).
   - Decrementa il timer solo mentre il canale è idle.
   - Quando il timer raggiunge zero → trasmette il frame per intero.
   - Se non riceve ACK → incrementa l'intervallo di backoff e riprova.
   - Se riceve ACK e ha altri dati → resetta il backoff e ripete.

**Algoritmo destinatario**: se il frame è corretto → invia **ACK dopo SIFS**.

> [!info] DIFS vs. SIFS
> **DIFS (Distributed Inter-Frame Spacing)**: attesa minima in cui il canale deve essere idle prima di *iniziare una nuova competizione* (nuovo frame).
> **SIFS (Short Inter-Frame Spacing)**: attesa minima prima di inviare un frame *parte di una comunicazione in corso* (es. ACK), senza competizione.
> Vale sempre $\text{SIFS} < \text{DIFS}$: chi aspetta SIFS ha priorità sull'inizio di un nuovo frame, così l'ACK ha la precedenza su qualsiasi nuovo mittente.

Collisioni residue sono ancora possibili: terminale nascosto, oppure i timer di backoff di due nodi scadono quasi simultaneamente prima che il segnale dell'uno raggiunga l'altro.
### Prenotazione del canale: RTS/CTS (opzionale)
Meccanismo per limitare le collisioni su frame di dati lunghi:
1. Il mittente invia un piccolo **RTS (Request-to-Send)** all'AP via CSMA (possibili collisioni, ma frame piccoli).
2. L'AP risponde in broadcast con **CTS (Clear-to-Send)** dopo SIFS.
3. Tutti i nodi ricevono il CTS: il mittente trasmette, gli altri differiscono la propria trasmissione.
### Frame 802.11: struttura e indirizzamento
**Formato del frame** (dimensioni principali):

| Campo | Dimensione |
|---|---|
| Frame control | 2 B |
| Duration | 2 B |
| Addr 1 | 6 B |
| Addr 2 | 6 B |
| Addr 3 | 6 B |
| Seq control | 2 B |
| Addr 4 | 6 B |
| Payload | 0–2312 B |
| CRC | 4 B |

802.11 usa **quattro indirizzi** perché distingue chi trasmette fisicamente il frame dal mittente originale, e chi lo riceve fisicamente dal destinatario finale:
- **Addr 1**: MAC dell'host wireless o AP che *deve ricevere* il frame (non necessariamente il destinatario finale).
- **Addr 2**: MAC dell'host wireless o AP che *trasmette* il frame (non necessariamente il mittente iniziale).
- **Addr 3**: MAC dell'interfaccia router a cui l'AP è connesso — ruolo cruciale nell'internetworking tra BSS e LAN cablata.
- **Addr 4**: usato solo in modalità ad hoc.

Il **campo duration** riserva il tempo di trasmissione (usato con RTS/CTS); il **numero di sequenza** supporta il trasferimento affidabile.

> [!example] Indirizzamento H1 → Internet tramite AP → R1
> Frame 802.11 sul canale wireless (H1 → AP): Addr1 = MAC AP, Addr2 = MAC H1, Addr3 = MAC R1.
> Frame 802.3 Ethernet (AP → R1): src = MAC H1, dst = MAC R1.
> Grazie ad Addr3, l'AP sa a quale interfaccia router consegnare il frame convertito in Ethernet.
### Mobilità all'interno della stessa sottorete
Se due AP sono connessi da uno **switch** (non da un router), H1 rimane nella stessa sottorete: l'indirizzo IP *può rimanere lo stesso*. Lo switch aggiorna la propria tabella di inoltro per auto-apprendimento; il nuovo AP può inviare un frame Ethernet broadcast con mittente H1 per forzare l'aggiornamento immediato. Il protocollo **802.11f** (inter-AP) gestisce il coordinamento tra AP.

Se due AP sono connessi da un **router**, H1 cambia sottorete e deve ottenere un nuovo IP (tipicamente via DHCP): le connessioni TCP attive non possono essere mantenute.
### Funzionalità avanzate
**Adattamento del tasso trasmissivo**: stazione base e host mobile cambiano dinamicamente la tecnica di modulazione al variare dell'SNR. Se l'host si allontana e l'SNR cala, il BER aumenta: si scende a un tasso inferiore con BER accettabile.

**Gestione dell'energia**: il nodo comunica all'AP che sta per diventare inattivo fino al prossimo beacon. L'AP bufferizza i frame per il nodo inattivo; il frame beacon contiene la lista dei nodi con frame in attesa. Il nodo si riattiva prima del beacon e controlla se ci sono frame per lui, evitando di tenere la radio accesa inutilmente.
## Reti cellulari: 4G/5G
### Contesto 4G
Lo standard tecnico di riferimento è **3GPP (3rd Generation Partnership Project)**, con lo standard **LTE (Long-Term Evolution)**. La disponibilità 4G raggiunge il 97% del tempo in Corea e il 90% negli USA; i tassi di trasmissione arrivano a centinaia di Mbps.

Le reti 4G condividono con Internet cablato la distinzione periferia/nucleo e l'uso di HTTP, DNS, TCP, UDP, IP, NAT, SDN, Ethernet, tunneling e la separazione tra piano di controllo e piano dati. Le differenze principali sono: protocolli di collegamento wireless diversi, **mobilità come servizio di primo livello**, identità utente via SIM card e modello di business ad abbonamento (home network vs. roaming in visited network).
### Elementi dell'architettura 4G
**Mobile device (UE — User Equipment)**: smartphone, tablet, laptop, dispositivi IoT con radio 4G LTE. Porta un **IMSI (International Mobile Subscriber Identity)** a 64 bit memorizzato sulla **SIM card**.

**Base station (eNode-B)**: alla periferia della rete dell'operatore; gestisce le risorse radio per i device nella propria cella; coordina l'autenticazione con altri elementi. A differenza dell'AP WiFi, ha un ruolo attivo nella mobilità e si coordina con le altre BS per ottimizzare l'uso della banda radio.

**Home Subscriber Service (HSS)**: database che memorizza le informazioni sui dispositivi mobili abbonati alla home network; collabora con l'MME per l'autenticazione.

**Serving Gateway (S-GW) e PDN Gateway (P-GW)**: sul percorso dati tra Internet e il mobile device. Il **P-GW** è il gateway per la rete mobile cellulare, appare come un qualunque router Internet e fornisce servizi NAT. Entrambi fanno uso estensivo di **tunneling**.

**Mobility Management Entity (MME)**: gestisce l'autenticazione dei device (device↔network, network↔device) coordinandosi con l'HSS della home network; traccia la posizione dei device con processo di **paging**; imposta il percorso (tunnel) dal mobile device al P-GW.
### Separazione piano di controllo e piano dati LTE
**Piano di controllo**: nuovi protocolli per mobilità, sicurezza e autenticazione; elementi coinvolti: HSS, MME, BS.

**Piano dei dati**: nuovi protocolli a livello fisico e di collegamento; uso estensivo di tunnel per gestire la mobilità. Percorso dati: BS → S-GW → P-GW → Internet.
### Tunneling GTP nel piano dati
I datagrammi del mobile device sono incapsulati con **GTP-U (GPRS Tunneling Protocol)**, inseriti dentro datagrammi UDP, dentro datagrammi IP:

```
[IP datagramma UE]
  → incapsulato in GTP-U (con TEID)
    → incapsulato in UDP
      → incapsulato in IP (sorgente/dest = estremi del tunnel, non UE/server)
```

Il **TEID (Tunnel Endpoint Identifier)** nell'intestazione GTP-U consente più tunnel tra le stesse estremità (uno per UE); i TEID nelle direzioni downstream e upstream sono diversi. Quando il device cambia BS, cambia solo l'endpoint del tunnel BS → S-GW; il tunnel S-GW → P-GW implementa l'instradamento indiretto e rimane stabile.
### Associazione del mobile device a una BS
1. La BS invia in broadcast un **segnale di sincronizzazione primario ogni 5 ms**.
2. Il mobile node scansiona tutte le bande cercando il segnale primario, poi trova il segnale secondario; ricava larghezza di banda, configurazioni e informazioni sull'operatore (può riceverne da più BS/reti).
3. Il mobile node sceglie con quale BS associarsi (preferendo tipicamente la rete dell'operatore d'origine).
4. Seguono ulteriori passaggi per autenticazione, creazione dello stato e configurazione del piano dati.
### Sleep modes LTE
- **Light sleep**: dopo centinaia di ms di inattività → il device si risveglia periodicamente (centinaia di ms) per controllare trasmissioni downstream.
- **Deep sleep**: dopo 5–10 secondi di inattività → la mobilità può cambiare cella durante il sonno profondo → è necessario ristabilire l'associazione al risveglio.
### Rete cellulare globale: una rete di reti IP
Gli operatori si interconnettono tra loro e con Internet pubblico nei punti di scambio tramite **inter-carrier IPX**. L'HSS della home network memorizza informazioni su identità e servizi sia in home network sia in roaming. Le reti 2G/3G legacy non sono interamente basate su IP e sono gestite in modo diverso.
### Passaggio al 5G
Il **5G** si pone tre obiettivi rispetto al 4G: incremento di **10x** del bitrate di picco, riduzione di **10x** della latenza, aumento di **100x** della capacità di traffico.

**5G NR (New Radio)** opera in due bande: **FR1** (450 MHz – 6 GHz) e **FR2** (24 – 52 GHz, *onde millimetriche*). Non è retrocompatibile con il 4G; introduce **MIMO** con antenne multiple direzionali. Le onde millimetriche consentono velocità molto elevate ma su distanze brevi: le **pico-cell** hanno diametro di 10–100 m e richiedono una distribuzione densa di stazioni base.

Tre casi d'uso attesi (Raccomandazione ITU-R M.2083-0, 2015):
- **eMBB** (enhanced Mobile Broadband)
- **mMTC** (massive Machine Type Communications)
- **URLLC** (Ultra-reliable and Low Latency Communications)
## Gestione della mobilità: principi
### Spettro della mobilità
Da nessuna mobilità ad alta mobilità (punto di vista livello di rete):
1. Il device si sposta tra reti di accesso ma è **spento** durante lo spostamento.
2. Si sposta entro la **stessa rete di accesso wireless** (stessa BS → nessuna mobilità a livello di rete).
3. Si sposta tra reti di accesso nella rete di **un singolo fornitore**, mantenendo connessioni in corso. *(caso di interesse principale)*
4. Si sposta tra reti di **fornitori differenti**, mantenendo connessioni in corso. *(caso di interesse principale)*
### Approcci alla mobilità
**Approccio 1 — lasciare che siano i router a gestirla (via BGP)**: i router annunciano l'indirizzo IP permanente del nodo mobile tramite BGP; la rete visitata ritira la rotta all'uscita del device. È già supportato da Internet senza modifiche (prefisso più lungo). **Problema**: non scalabile per miliardi di dispositivi.

**Approccio 2 — gestione alla periferia della rete**:
- **Instradamento indiretto (indirect routing)**: i pacchetti dal corrispondente arrivano alla home network, che li inoltra tramite tunnel al device nella rete visitata.
- **Instradamento diretto (direct routing)**: il corrispondente ottiene il **care-of address** (indirizzo nella rete visitata) e invia il datagramma direttamente al device, senza passare dalla home network.
### Home network e visited network
> [!quote] Definizione — Home e Visited Network
> **Home network**: la rete del carrier a cui il device è abbonato; l'HSS della rete domestica memorizza identità e servizi del device sia in home sia in roaming.
> **Visited network**: qualsiasi rete diversa dalla home network; fornisce l'accesso tramite accordo di roaming.
### Registrazione
Procedura di registrazione quando il device entra in una visited network:
1. Il device si associa al **mobility manager della rete visitata**.
2. Il mobility manager della rete visitata registra la posizione del device nell'**HSS della rete domestica**.

Risultato: il mobility manager della rete visitata conosce il device; l'HSS domestico sa dove si trova il device.
### Mobilità con instradamento indiretto
Flusso dal corrispondente al device:
1. Il corrispondente invia il datagramma all'**indirizzo domestico** (permanente) del device.
2. Il gateway della home network riceve il datagramma e lo **inoltra tramite tunnel** al gateway della rete visitata.
3. Il gateway della rete visitata consegna il datagramma al device mobile.
4. La risposta del device al corrispondente può passare per la home network (**4a**) oppure andare **direttamente** al corrispondente (**4b** — detto *local breakout* nel 4G LTE).

> [!warning] Instradamento triangolare
> Se corrispondente e device si trovano nella stessa rete (o in reti geograficamente vicine), i pacchetti percorrono un tragitto allungato e inefficiente passando per la home network: è il problema dell'**instradamento triangolare (triangular routing)**.

**Vantaggio**: se il device si sposta in una nuova visited network, il corrispondente non lo sa e le connessioni TCP in corso possono essere mantenute (trasparente al corrispondente).
### Mobilità con instradamento diretto
Flusso:
1. Il corrispondente contatta l'**HSS domestico** e ottiene la rete visitata corrente del device.
2. Il gateway della rete visitata fornisce il **care-of address** (indirizzo nella rete visitata).
3. Il corrispondente invia il datagramma direttamente all'indirizzo della rete visitata.

**Vantaggio**: supera le inefficienze dell'instradamento triangolare.
**Svantaggi**: non trasparente al corrispondente; se il device si sposta di nuovo, la gestione si complica (il corrispondente deve aggiornare il care-of address).
## Gestione della mobilità: pratica 4G
### Compiti di mobilità principali
1. **Associazione alla BS**: il device fornisce l'IMSI, identificando se stesso e la home network.
2. **Configurazione del piano di controllo**: MME e HSS della home network stabiliscono lo stato (il device è nella visited network).
3. **Configurazione del piano dati**: l'MME configura i tunnel di inoltro; visited e home network stabiliscono il tunnel dal home P-GW al device.
4. **Mobile handover**: il device cambia punto di aggancio nella rete visitata.
### Handover tra BS nella stessa rete cellulare
Sequenza in sette passi:
1. La **source BS** seleziona la BS target e invia una *Richiesta di Handover* alla BS target.
2. La **target BS** pre-alloca slot temporali nel canale radio e risponde con ACK contenente le informazioni necessarie al device per associarsi.
3. La **source BS** comunica al device mobile la nuova BS → il device può ora trasmettere attraverso la nuova BS (*l'handover appare completo al device*).
4. La source BS smette di inviare datagrammi al device e li **inoltra alla target BS**, che li consegna al device via radio.
5. La **target BS** informa l'MME di essere la nuova BS per quel device; l'MME istruisce l'S-GW a cambiare l'**endpoint del tunnel** alla target BS.
6. La target BS manda ACK alla source BS: handover completato, la source BS **rilascia le risorse**.
7. I datagrammi fluiscono ora attraverso il nuovo tunnel: target BS → S-GW.
## Mobile IP
Mobile IP è citato nelle slide come architettura alternativa per la mobilità nelle reti ISP/WiFi; le reti 4G/5G non lo adottano in pratica. Nelle reti WiFi non esiste una nozione nativa di "home network": le credenziali sono memorizzate sul device o presso l'utente. Eccezione notevole: **eduroam**, la federazione di reti universitarie con credenziali condivise tra atenei.
## Bluetooth
**Bluetooth** cade nella categoria *hop singolo, senza infrastruttura* della tassonomia iniziale. Caratteristiche tecniche:
- Tasso trasmissivo: **2 Mbps**
- Distanza: interni, **10–30 m**
- Frequenza: **2,4 GHz** (condivisa con WiFi → possibili interferenze; gestite tramite *frequency-hopping spread spectrum*)

La rete Bluetooth è detta **piconet**: al massimo 8 dispositivi *attivi*, di cui uno è il **Master** (gestisce clock, tasso trasmissivo e polling dei client) e i restanti sono **client**. Possono coesistere fino a 255 dispositivi *parked* (addormentati), riattivabili dal Master. Il protocollo combina TDM, FDM e polling a rotazione.

Come WiFi e LTE, i device Bluetooth possono mettere la radio in **sleep mode** per preservare la batteria.
## Impatto della mobilità sui protocolli di livello superiore
Il modello best effort di Internet rimane inalterato: TCP e UDP funzionano su reti wireless e mobili. L'impatto si avverte sulle prestazioni:
- Perdita di pacchetti per handover e per BER elevato → ritrasmissioni.
- **TCP interpreta la perdita wireless come congestione** e riduce inutilmente la finestra di congestione (vedi [[03 - Livello di Trasporto#Controllo della congestione|controllo della congestione TCP]]).
- Il traffico in tempo reale è danneggiato dai ritardi da handover.
- La larghezza di banda wireless è una **risorsa scarsa** (canale condiviso): le applicazioni devono tenerne conto.

Tre approcci per mitigare il problema TCP/wireless:
- **Recupero locale**: WiFi implementa il trasferimento affidabile a livello di singolo collegamento, nascondendo le perdite radio al TCP.
- **Consapevolezza del mittente**: distinguere perdite wireless (BER) da perdite per congestione di rete.
- **Split connection**: la connessione end-to-end è divisa in connessione host–AP wireless e connessione AP–destinatario finale; solo il tratto wireless usa un protocollo ottimizzato per il canale radio.

---

Questa nota conclude il modulo sulle reti di calcolatori. Per una visione d'insieme della pila di protocolli e delle strutture di Internet, si rimanda a [[01 - Introduzione]].
