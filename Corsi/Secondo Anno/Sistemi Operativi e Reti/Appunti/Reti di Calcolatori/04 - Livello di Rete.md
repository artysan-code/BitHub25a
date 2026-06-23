# Livello di Rete
Il livello di rete è responsabile del trasferimento dei **datagrammi** dall'host mittente all'host destinatario attraverso l'intera rete di router. Questa nota copre il **piano dei dati** — architettura dei router, IP, NAT, IPv6 — e il **piano di controllo** — algoritmi di instradamento, OSPF, BGP, SDN, ICMP e gestione della rete. Per il contesto della pila protocollare vedi [[01 - Introduzione]]; per i protocolli di trasporto che consegnano i segmenti al livello di rete vedi [[03 - Livello di Trasporto]].
## Piano dei dati e piano di controllo
Le due funzioni fondamentali del livello di rete sono:
- **Inoltro (forwarding):** funzione *locale* al singolo router; trasferisce i datagrammi dalla porta di ingresso alla porta di uscita appropriata; opera su scala dei **nanosecondi**, implementata in hardware.
- **Instradamento (routing):** funzione *globale* della rete; determina il percorso end-to-end tramite algoritmi distribuiti o centralizzati; opera su scala dei **millisecondi/secondi**, implementata in software.
### Piano dei dati
Opera sui singoli datagrammi in transito, router per router. La **tabella di inoltro (forwarding table)** è l'elemento chiave: ogni router la consulta per sapere su quale porta di uscita spedire il datagramma in base ai valori estratti dall'intestazione.
### Piano di controllo
Rappresenta la *logica della rete*: determina come i datagrammi sono instradati end-to-end. Due approcci:
1. **Algoritmi di instradamento tradizionali (per router):** ogni router esegue il proprio algoritmo e comunica con gli altri tramite messaggi di protocollo per popolare le tabelle di inoltro.
2. **SDN (Software-Defined Networking):** un **controller remoto** calcola e distribuisce le tabelle di inoltro a tutti i router; il router si limita all'inoltro, il controller centralizza l'instradamento.
## Modelli di servizio del livello di rete
> [!quote] Definizione — Modello di servizio
> Il **modello di servizio** descrive le caratteristiche del canale di trasporto dei datagrammi dal mittente al destinatario: garanzie di consegna, ordine, ritardo, banda minima, sicurezza.

Internet adotta un unico modello: **best effort** (massimo impegno). Non ci sono garanzie sulla consegna, sull'ordine, sul ritardo end-to-end né su una banda minima. La semplicità del modello ha consentito la massima diffusione di Internet; la banda sufficiente, i protocolli adattativi (TCP, [[03 - Livello di Trasporto]]) e i servizi replicati (CDN, datacenter) compensano la mancanza di garanzie.
Altri modelli esistono (ATM con CBR e ABR, Intserv, Diffserv) ma rimangono marginali rispetto al best effort di Internet.
## Architettura di un router
Un router è strutturato in quattro componenti principali.

> [!info] Calcolo di riferimento
> Collegamento a **100 Gbps**, datagramma da **64 byte**: il prossimo datagramma arriva dopo
> $$\frac{64 \times 8 \text{ bit}}{100 \times 10^9 \text{ bit/s}} = 5{,}12 \text{ ns}$$
> Le porte di ingresso e la struttura di commutazione devono completare l'elaborazione entro questo intervallo.
### Porte di ingresso
La **porta di ingresso** svolge una pipeline di tre funzioni:
1. Terminazione di linea (livello fisico).
2. Elaborazione del livello di collegamento (es. de-capsulamento Ethernet).
3. **Ricerca e inoltro:** cerca nella tabella di inoltro locale (in TCAM) la porta di uscita, senza coinvolgere la CPU centrale — questo è detto **commutazione decentralizzata**.
L'obiettivo è elaborare alla **velocità della linea (line-rate)**.
Due modalità di inoltro dalla porta di ingresso:
- *Inoltro basato sulla destinazione:* solo sull'indirizzo IP di destinazione (approccio tradizionale).
- *Inoltro generalizzato:* su più campi di intestazione (OpenFlow/SDN).
### Corrispondenza a prefisso più lungo
Quando più prefissi nella tabella di inoltro corrispondono all'indirizzo di destinazione, si usa il **prefisso più lungo** (più specifico) — regola della **Longest Prefix Match**.

> [!example] Longest Prefix Match
> Indirizzo A: `11001000 00010111 00010110 10100001` → corrisponde al prefisso `11001000 00010111 00010*** ********` (/21) → porta 0.
> Indirizzo B: `11001000 00010111 00011000 10101010` → corrisponde sia al prefisso `/21` (`00011*** ********`) sia al prefisso più lungo `/24` (`00011000 ********`) → prefisso più lungo `/24` → porta 0.

La ricerca è implementata con **TCAM (Ternary Content Addressable Memory)**:
- L'indirizzo IP a 32 bit è passato alla memoria che restituisce la voce corrispondente in **tempo essenzialmente costante** (ricerca parallela su tutte le voci).
- Le celle TCAM usano bit "don't care" per la parte non prefissata.
- I prefissi sono memorizzati dal più lungo al più corto; un **priority encoder** restituisce la prima corrispondenza.
- Cisco Catalyst: circa **1 milione di voci** in TCAM.
### Struttura di commutazione
La **struttura di commutazione (switching fabric)** trasferisce i datagrammi dalla porta di ingresso alla porta di uscita. Il tasso di trasferimento desiderato è $N \times R$ con $N$ porte e $R$ tasso delle linee. Tre tipi:
1. **Commutazione in memoria:** i router di prima generazione usavano la CPU; il pacchetto veniva copiato in memoria di sistema e poi nella porta di uscita (**2 attraversamenti del bus** per datagramma); velocità limitata dalla banda della memoria.
2. **Commutazione tramite bus:** le porte di ingresso trasferiscono il pacchetto direttamente alle porte di uscita su bus condiviso; velocità limitata dalla velocità del bus (**bus contention**); es. Cisco 5600: **32 Gbps**.
3. **Commutazione tramite rete di interconnessione (crossbar/multistage):**
   - Crossbar e reti Clos, derivate dalle architetture multiprocessore.
   - Switch $n \times n$ composti da switch più piccoli (multistage).
   - Sfrutta il **parallelismo:** frammenta datagrammi in celle di lunghezza fissa, le commuta, le riassembla in uscita.
   - Cisco CRS: **8 fabric planes** in parallelo, ogni plane = rete a **3 stadi**; capacità fino a **centinaia di Tbps**.
### Accodamento
Se la struttura di commutazione è più lenta delle porte combinate, si verifica **accodamento in ingresso** con ritardi e perdite per overflow del buffer.

> [!quote] Definizione — HOL blocking
> Il **blocco in testa alla coda (HOL blocking, Head-of-Line blocking)** si verifica quando il datagramma in testa alla coda di ingresso blocca quelli dietro che potrebbero già essere serviti, perché il datagramma in testa è diretto a una porta di uscita già occupata.

**Accodamento in uscita:** si verifica quando i datagrammi arrivano dalla struttura di commutazione più velocemente del tasso di trasmissione del collegamento; lo schedulatore di pacchetti decide l'ordine di trasmissione.
**Dimensionamento del buffer** — RFC 3439 e raccomandazione attuale:
$$\text{buffer} = \text{RTT} \times C \qquad \text{(regola storica, RTT} \approx 250 \text{ ms)}$$
$$\text{buffer} = \frac{\text{RTT} \times C}{\sqrt{N}} \qquad \text{(con } N \text{ flussi TCP)}$$

> [!warning] Bufferbloat
> Buffer troppo grandi aumentano i ritardi di coda (**bufferbloat**): RTT elevato, TCP meno reattivo, latenza percepita peggiore per gioco e videoconferenza.

**Drop policy** quando il buffer è pieno:
- *Tail drop:* scarta il pacchetto in arrivo.
- *Priorità:* scarta/rimuove in base alla classe di priorità.
- *Marcatura:* ECN, RED — segnalazione anticipata di congestione prima del riempimento.
### Schedulazione dei pacchetti
Lo **schedulatore di pacchetti** determina quale pacchetto trasmettere successivamente sulla porta di uscita.
- **FCFS/FIFO:** primo arrivato, primo servito; nessuna distinzione tra classi.
- **Priority queuing:** il traffico è classificato in code; si serve sempre la coda non vuota con priorità più alta (FCFS dentro ogni classe); rischio di **starvation** per le classi a bassa priorità.
- **Round Robin (RR):** scansione ciclica delle classi, un pacchetto per classe per turno; nessuna starvation.
- **Weighted Fair Queuing (WFQ):** generalizzazione di RR; ogni classe $i$ ha peso $w_i$; frazione di servizio per ciclo:
$$\frac{w_i}{\sum_j w_j}$$
WFQ garantisce una **larghezza di banda minima** per ogni classe di traffico.
## IP: il Protocollo Internet
### Formato del datagramma IPv4
> [!quote] Definizione — Datagramma IP
> Il **datagramma IP** è la PDU del livello di rete; ha una dimensione massima di **65535 byte** (campo lunghezza totale a 16 bit) e tipicamente **1500 byte o meno** (vincolo MTU Ethernet). L'overhead normale è **20 byte IP + 20 byte TCP = 40 byte** di intestazioni.

Campi principali dell'intestazione IPv4 (20 byte in assenza di opzioni):
| Campo | Dimensione | Descrizione |
|---|---|---|
| `ver` | 4 bit | Versione del protocollo (4 per IPv4) |
| `lungh. intestazione` | 4 bit | Lunghezza intestazione in multipli di 32 bit |
| `tipo di servizio` | 8 bit | DiffServ (bit 0–5) + ECN (bit 6–7) |
| `lunghezza totale` | 16 bit | Lunghezza totale del datagramma in byte |
| `identificatore` | 16 bit | Identifica il datagramma originale per la frammentazione |
| `flag` | 3 bit | MF (More Fragments), DF (Don't Fragment) |
| `offset frammento` | 13 bit | Posizione del frammento in unità di 8 byte |
| `TTL` | 8 bit | Decrementato a ogni hop; scartato se raggiunge 0 |
| `livello superiore` | 8 bit | Protocollo destinatario: TCP = **6**, UDP = **17** |
| `checksum intestazione` | 16 bit | Verifica errori sui bit dell'intestazione |
| IP sorgente / destinazione | 32 bit ciascuno | Indirizzi mittente e destinatario |
| `opzioni` | variabile | Es. registrazione percorso, timestamp |
### Frammentazione e riassemblaggio
Se un datagramma è più grande della **MTU (Maximum Transmission Unit)** del collegamento in uscita, il router lo frammenta in datagrammi IP più piccoli. Il riassemblaggio avviene **solo all'host di destinazione**, usando i campi identificatore, flag MF e offset.

> [!example] Esempio di frammentazione
> Datagramma originale: **4000 byte**, MTU = **1500 byte**.
> Ogni frammento trasporta **1480 byte** di dati (= 1500 − 20 byte intestazione IP).
>
> | Frammento | `length` | `ID` | `flag MF` | `offset` |
> |---|---|---|---|---|
> | 1 | 1500 | x | 1 | 0 |
> | 2 | 1500 | x | 1 | 185 (= 1480/8) |
> | 3 | 1040 | x | 0 | 370 |
>
> La lunghezza dei dati in ciascun frammento (tranne l'ultimo) deve essere **multiplo di 8** (unità dell'offset).

**Problemi della frammentazione** (per questo deprecata in IPv6):
- Overhead: ogni frammento richiede una propria intestazione IP.
- Perdita di un frammento → perdita dell'intero datagramma originale.
- Costo computazionale del riassemblaggio agli endpoint.
- Sicurezza: **tiny fragment attack** (intasare i buffer di riassemblaggio).
**Path MTU Discovery (PMTUD):** invio con bit DF=1; se un router non può inoltrare, scarta e invia ICMP "Destination Unreachable: Fragmentation Required" con il campo *next-hop MTU*.
### Indirizzamento IPv4 e sottoreti
Un **indirizzo IP** è un identificatore a **32 bit** associato a un'*interfaccia* (non all'host in quanto tale); notazione **decimale puntata**, es. `223.1.1.1`.

> [!quote] Definizione — Sottorete
> Una **sottorete (subnet)** è un insieme di interfacce che possono raggiungersi fisicamente *senza passare per un router intermedio*. Tutti i dispositivi di una sottorete condividono i bit di ordine superiore dell'indirizzo IP, definiti dalla **maschera di sottorete (subnet mask)**, es. `/24` = 24 bit di parte di rete.

Per identificare le sottoreti si "sganciano" le interfacce da host e router: le isole di rete isolate risultanti sono le sottoreti.
### CIDR
**CIDR (Classless InterDomain Routing,** pronunciato *"cider"*)  generalizza l'indirizzamento di sottorete: la parte di rete ha **lunghezza arbitraria**, non vincolata ai classici 8/16/24 bit. Formato: `a.b.c.d/x` dove $x$ = numero di bit della parte di rete.
In un blocco `/x` ci sono $2^{32-x}$ indirizzi totali; vanno sottratti **2** (indirizzo di rete = tutti 0 nella parte host, broadcast diretto = tutti 1). Esiste anche il **broadcast limitato** `255.255.255.255`.
**Aggregazione di route (route aggregation):** un ISP con blocco `/20` può aggregare le route di 8 organizzazioni con blocchi `/23` annunciando un solo prefisso a Internet. Se un'organizzazione cambia ISP, il nuovo ISP annuncia il prefisso più specifico; i router applicano la longest prefix match e dirottano il traffico correttamente.
L'indirizzamento **classful** precedente CIDR assegnava porzioni di rete rigide:

| Classe | Bit iniziali | Parte rete | Host/rete | Problema |
|---|---|---|---|---|
| A | 0 | 8 bit | 16.777.216 ($2^{24}$) | Troppo grande per quasi tutti |
| B | 10 | 16 bit | 65.536 ($2^{16}$) | Spesso sprecata |
| C | 110 | 24 bit | 256 ($2^8$) | Troppo piccola per molte reti |
| D | 1110 | multicast | — | — |

CIDR ha sostituito il classful addressing eliminando gli sprechi tramite allocazione su misura e aggregazione.
### DHCP
**DHCP (Dynamic Host Configuration Protocol)** consente a un host di ottenere dinamicamente l'indirizzo IP dal server all'atto della connessione alla rete ("plug-and-play"). Permette il riutilizzo degli indirizzi tramite **lease** temporanei; supporta utenti mobili.
Il server DHCP risiede tipicamente nel router e serve tutte le sottoreti connesse. Il protocollo si articola in **4 passi**:
1. **DHCP discover** (host → broadcast): `src=0.0.0.0:68`, `dst=255.255.255.255:67` — l'host senza indirizzo annuncia la propria presenza [passo opzionale insieme a DHCP offer].
2. **DHCP offer** (server → broadcast): `src=223.1.2.5:67`, `dst=255.255.255.255:68`, `yiaddr=223.1.2.4`, `lifetime=3600s` — il server propone un indirizzo [passo opzionale insieme a DHCP discover: la coppia discover+offer può essere saltata se il client vuole riutilizzare un indirizzo precedentemente assegnato].
3. **DHCP request** (host → broadcast): il client sceglie una delle offerte e ne conferma la selezione in broadcast (così gli altri server possono annullare la riserva).
4. **DHCP ACK** (server → broadcast): conferma definitiva dell'indirizzo.

> [!info] Informazioni restituite da DHCP
> Oltre all'indirizzo IP, DHCP restituisce: indirizzo del **router first-hop** (gateway predefinito), nome e indirizzo IP del **server DNS**, **maschera di sottorete**.

I blocchi di indirizzi IP sono assegnati dall'ISP; ICANN li distribuisce tramite 5 **registri regionali (RR)**. ICANN ha assegnato l'ultima porzione di indirizzi IPv4 ai RR nel **2011**.
### NAT
**NAT (Network Address Translation)** permette a tutti i dispositivi di una rete locale di condividere un **unico indirizzo IP pubblico** verso Internet, usando indirizzi privati internamente (prefissi **10/8**, **172.16/12**, **192.168/16**).

> [!example] Funzionamento NAT
> 1. Host `10.0.0.1:3345` invia datagramma verso `128.119.40.186:80`.
> 2. Il router NAT sostituisce `(10.0.0.1, 3345)` con `(138.76.29.7, 5001)` e aggiorna la **tabella di traduzione NAT**.
> 3. La risposta arriva a `138.76.29.7:5001`.
> 4. Il router NAT sostituisce `(138.76.29.7, 5001)` con `(10.0.0.1, 3345)` e consegna all'host interno.

Vantaggi: un solo indirizzo IP dal provider per tutta la rete locale; cambio ISP senza modificare indirizzi interni; dispositivi interni non indirizzabili dall'esterno (sicurezza).
Controversie: i router dovrebbero elaborare solo fino al livello 3; il NAT manipola il numero di porta (campo del livello 4), violando il principio **end-to-end**; causa il problema del **NAT traversal** per server dietro NAT. Nonostante ciò, è ampiamente usato in reti domestiche, aziendali e cellulari 4G/5G.
### IPv6
**IPv6** nasce dall'esaurimento dello spazio di indirizzi IPv4 (32 bit); estende gli indirizzi a **128 bit**. Motivazioni aggiuntive: intestazione a **lunghezza fissa di 40 byte** per elaborazione più rapida; gestione dei **flussi** come entità di prima classe.
Campi del datagramma IPv6:
| Campo | Dimensione | Descrizione |
|---|---|---|
| `ver` | 4 bit | Versione (6) |
| `classe di traffico` | 8 bit | DiffServ (bit 0–5) + ECN (bit 6–7) |
| `etichetta di flusso` | 20 bit | Identifica datagrammi dello stesso flusso |
| `lunghezza dati` | 16 bit | Lunghezza del payload |
| `intestazione successiva` | 8 bit | Protocollo destinatario (next header) |
| `limite di hop` | 8 bit | Equivalente del TTL |
| sorgente / destinazione | 128 bit ciascuno | Indirizzi IPv6 |

Cosa manca rispetto a IPv4:
- **No checksum:** velocizza l'elaborazione nei router.
- **No frammentazione/riassemblaggio nei router** (solo nella sorgente); il router invia invece **ICMPv6 Packet Too Big**.
- **No opzioni** nell'intestazione fissa (disponibili come intestazione successiva).
**Notazione indirizzi IPv6** (RFC 4291): gruppi da 4 cifre esadecimali separati da `:`, es. `2001:0db8:0000:0000:0001:0000:0000:0001`. Abbreviazioni: zeri iniziali omissibili per gruppo; una sola sequenza di gruppi a zero contigui → `::` (RFC 5952 preferisce la prima sequenza più lunga).
**Tunneling:** quando due router IPv6 comunicano attraverso una regione IPv4, il datagramma IPv6 viene incapsulato come payload di un datagramma IPv4 ("pacchetto nel pacchetto"). I router dual-stack ai bordi del tunnel incapsulano/de-incapsulano. Adozione IPv6: ~40% dei client Google nel 2023; transizione in corso da oltre 25 anni.
## Inoltro generalizzato e SDN (piano dei dati)
### Astrazione match + action
> [!quote] Definizione — Inoltro generalizzato
> Nell'**inoltro generalizzato** ogni entry della **tabella dei flussi (flow table)** contiene: un **match** (pattern su campi di intestazione di qualsiasi livello), un'**action** (inoltro, scarto, modifica, invio al controller), una **priorità** (disambigua pattern sovrapposti) e **contatori** (byte, pacchetti, timestamp).

Questa astrazione unifica dispositivi eterogenei:

| Dispositivo | Match | Action |
|---|---|---|
| Router | Prefisso IP destinazione (LPM) | Forward su porta |
| Firewall | IP + porta TCP/UDP | Permit / deny |
| Switch | MAC destinazione | Forward / flood |
| NAT | IP + porta | Riscrive IP + porta |
### OpenFlow
**OpenFlow** è il protocollo tra controller SDN e switch; opera su **TCP** (porta 6653, crittografia opzionale). Campi di match: Ingress Port, MAC sorgente/destinazione, Ethernet Type, VLAN ID/priorità, IP sorgente/destinazione, IP Protocol, IP ToS, TCP/UDP porta sorgente/destinazione.
Azioni principali: forward to port; drop; modify header fields (eccetto IP Proto); encapsulate and send to controller.

> [!example] Esempi di regole OpenFlow
> - Inoltro basato su destinazione: `IP Dst=51.6.0.8` → `port6`
> - Firewall: `TCP dst-port=22` → `drop`; `IP Src=128.119.1.1` → `drop`
> - Load balancing: `dst=10.1.*.*` da porta 3 → porta 2; da porta 4 → porta 1 (impossibile con inoltro basato sulla destinazione)
> - Inoltro L2: `MAC dst=22:A7:23:11:E1:02` → `port3`

Evoluzione: **P4** (p4.org) per programmazione ancora più generalizzata del piano dei dati.
### Middlebox
> [!quote] Definizione — Middlebox
> Un **middlebox** (RFC 3234) è qualsiasi dispositivo intermedio che svolge funzioni diverse dalla normale operazione di router IP sul percorso tra host sorgente e destinazione.

Esempi: NAT, Firewall, IDS, Load balancer, Cache. Evoluzione: da hardware proprietario chiuso → hardware "whitebox" con API aperte → **NFV (Network Functions Virtualization)**: funzioni di rete in software su hardware COTS (commodity off-the-shelf), tramite VM o container, eseguibili anche in cloud. Le middlebox violano il **principio end-to-end** (Saltzer, Reed, Clark 1981): le funzioni devono risiedere agli endpoint perché solo lì si ha la conoscenza completa necessaria.
## Piano di controllo
### Algoritmi di instradamento
Il problema dell'instradamento si modella su un grafo $G = (N, E)$ dove $N$ = router, $E$ = collegamenti. Il costo di un collegamento diretto tra $x$ e $y$ è $c_{x,y}$ ($= \infty$ se non adiacenti). L'obiettivo è trovare il **percorso di costo minimo** tra coppie di nodi.
Classificazione:
- **Globali (link-state):** conoscenza completa della topologia; calcolo centralizzato o replicato.
- **Decentralizzati (distance-vector):** conoscenza iniziale solo dei vicini; calcolo iterativo distribuito.
- **Statici / dinamici:** i percorsi cambiano lentamente (intervento umano) o in risposta a variazioni.
- **Sensibili / insensibili al carico:** oggi si preferiscono gli **insensibili** per la difficoltà sperimentata in ARPAnet.
### Instradamento link-state: algoritmo di Dijkstra
Nell'instradamento **link-state** ogni router invia in **flooding** (inondazione) le informazioni sui propri collegamenti a *tutti* gli altri router, così che ciascuno disponga della topologia completa. Su questa base viene eseguito l'**algoritmo di Dijkstra**, che calcola i percorsi a costo minimo dalla sorgente a tutti gli altri nodi in modo **iterativo** (dopo $k$ iterazioni, $k$ percorsi definitivi).
**Notazione:**
- $D(v)$: stima corrente del costo minimo dalla sorgente $u$ al nodo $v$
- $p(v)$: predecessore immediato di $v$ nel percorso ottimo
- $N'$: insieme dei nodi con percorso definitivamente noto
**Pseudocodice:**
```
Inizializzazione:
  N' = {u}
  per ogni nodo v:
    se v adiacente a u: D(v) = c(u,v); p(v) = u
    altrimenti: D(v) = ∞

Ciclo (ripeti finché N' = N):
  scegli w ∉ N' con D(w) minimo
  aggiungi w a N'
  per ogni v adiacente a w con v ∉ N':
    D(v) = min(D(v), D(w) + c(w,v))
    se aggiornato: p(v) = w
```
Formula di aggiornamento:
$$D(v) = \min\bigl(D(v),\; D(w) + c_{w,v}\bigr)$$

> [!example] Esecuzione su grafo (nodi u, v, w, x, y, z)
>
> | Passo | $N'$ | $D(v)$ | $D(w)$ | $D(x)$ | $D(y)$ | $D(z)$ |
> |---|---|---|---|---|---|---|
> | 0 | u | 2,u | 5,u | 1,u | ∞ | ∞ |
> | 1 | ux | 2,u | 4,x | — | 2,x | ∞ |
> | 2 | uxy | 2,u | 3,y | — | — | 4,y |
> | 3 | uxyv | — | 3,y | — | — | 4,y |
> | 4 | uxyvw | — | — | — | — | 4,y |
> | 5 | uxyvwz | — | — | — | — | — |
>
> Tabella di inoltro risultante in $u$: $v \to (u,v)$; $x, y, w, z \to (u,x)$.

**Complessità:** $O(n^2)$ senza ottimizzazioni; $O(n \log n)$ con heap. La complessità di messaggi è $O(n^2)$: ogni router diffonde le proprie informazioni di stato a $O(n)$ nodi tramite flooding, e ciascun messaggio di broadcasting attraversa $O(n)$ collegamenti — complessità complessiva $O(n^2)$.
**Oscillazioni:** quando i costi dipendono dal traffico, i percorsi possono oscillare periodicamente.
### Instradamento distance-vector: Bellman-Ford
Nell'instradamento **distance-vector** ogni nodo conosce inizialmente solo i costi verso i vicini diretti; il calcolo del percorso ottimo è **distribuito, iterativo e asincrono**.
**Equazione di Bellman-Ford (esatta):**
$$d_x(y) = \min_v \bigl\{ c_{x,v} + d_v(y) \bigr\}$$
dove il minimo è su tutti i vicini $v$ di $x$.
**Versione stimata (algoritmo DV):**
$$D_x(y) \leftarrow \min_v \bigl\{ c_{x,v} + D_v(y) \bigr\} \quad \forall y \in N$$

> [!example] Calcolo BF
> Con $D_v(z)=5$, $D_x(z)=3$, $D_w(z)=3$ e costi $c_{u,v}=2$, $c_{u,x}=1$, $c_{u,w}=5$:
> $$D_u(z) = \min\{2+5,\; 1+3,\; 5+3\} = 4$$
> Il next-hop verso $z$ è $x$ (quello che realizza il minimo).

Funzionamento: ogni nodo mantiene il proprio **vettore delle distanze** verso tutti i destinatari. Periodicamente, o quando qualcosa cambia, invia il proprio DV ai vicini. Alla ricezione, ricalcola con B-F; se cambia, notifica i vicini. Al tempo $t$ l'informazione si propaga a distanza $t$ hop → **diametro della rete** iterazioni per la convergenza.
#### Problema: conteggio all'infinito
Le buone notizie (costo che diminuisce) si propagano rapidamente. Le **cattive notizie** (costo che aumenta o collegamento interrotto) viaggiano lentamente, generando **instradamento ciclico**: i costi crescono a ogni iterazione fino a un valore limite prefissato.

> [!example] Conteggio all'infinito
> Se il collegamento $c_{y,x}$ passa da 4 a 60: $y$ crede di raggiungere $x$ via $z$ con costo 6, $z$ aggiorna a 7, $y$ a 8, … — il ciclo procede fino a che il costo supera la soglia di "infinito" del protocollo.

**Soluzione: inversione avvelenata (poisoned reverse).** Se $z$ instrada verso $x$ passando per $y$, allora $z$ comunica a $y$ che $D_z(x) = +\infty$ (mente al vicino per rompere il ciclo). Risolve il conteggio all'infinito **solo per cicli che riguardano nodi adiacenti**; non risolve i cicli tra nodi non direttamente collegati. In pratica, **RIP** (RFC 1058) usa costi unitari e **16 come infinito** (rete impraticabile per diametro > 15).
### Confronto LS vs DV
| | Link State | Distance Vector |
|---|---|---|
| Complessità messaggi | $O(n^2)$ broadcast | Scambio solo tra vicini |
| Velocità convergenza | $O(n^2)$; possibili oscillazioni | Lenta; possibile ciclo e count-to-infinity |
| Robustezza | Router può diffondere costo sbagliato di un collegamento; ogni nodo calcola solo la propria tabella | Errori si propagano: DV errato può infettare tutta la rete (buco nero) |
### Instradamento intra-AS: OSPF
Per ragioni di scalabilità, i router di Internet sono raggruppati in **AS (Autonomous System, Sistema Autonomo)**, identificati da un **ASN** (Autonomous System Number, allocato da IANA tramite 5 Registri Regionali). Un ISP può costituire uno o più AS.
- **Intra-AS (intra-domain):** tutti i router nell'AS eseguono lo stesso algoritmo; la topologia è visibile solo all'interno dell'AS.
- **Inter-AS (inter-domain):** tra AS diversi; i **router gateway** (sul bordo dell'AS) effettuano sia l'instradamento intra-AS sia quello inter-AS.
La **tabella di inoltro** di ogni router è configurata congiuntamente: intra-AS per le destinazioni interne, intra-AS + inter-AS per le destinazioni esterne.
Protocolli intra-AS principali:
- **RIP** (RFC 1723): distance-vector classico; DV scambiati ogni 30 secondi; non più largamente usato.
- **EIGRP:** basato su DV; precedentemente proprietario Cisco (aperto 2013, RFC 7868).
- **OSPF** (Open Shortest Path First, RFC 2328): link-state; IS-IS (ISO) essenzialmente identico.

> [!quote] Definizione — OSPF
> **OSPF (Open Shortest Path First)** è un protocollo link-state intra-AS: ogni router inonda in broadcast le informazioni sui propri collegamenti a **tutti i router** dell'AS (almeno ogni **30 minuti** o a ogni variazione); i messaggi OSPF viaggiano **direttamente in datagrammi IP** (senza TCP/UDP). Ogni router calcola la propria tabella di inoltro con **Dijkstra**.

Caratteristiche avanzate di OSPF:
- **Sicurezza:** tutti i messaggi OSPF sono **autenticati** per prevenire intrusioni.
- **ECMP (Equal-Cost Multi-Path Routing):** più percorsi di uguale costo; load balancing per flusso (hash su IP sorgente + destinazione + porte), per destinazione (hash solo su IP destinazione) o per pacchetto (ogni pacchetto può seguire percorso diverso, ma può causare consegna fuori ordine e variabilità MTU per PMTUD).
**OSPF gerarchico — gerarchia a due livelli:**
- **Area locale:** i router interni (local router) inondano le informazioni di stato solo all'interno della propria area.
- **Dorsale (backbone):** interconnette tutte le aree.
- **ABR (Area Border Router):** riassume le distanze verso le destinazioni della propria area e le annuncia nella dorsale.
- **ASBR (AS Boundary Router):** si connette ad altri AS.
- **Router di dorsale:** esegue OSPF limitatamente alla dorsale.
### Instradamento inter-AS: BGP
> [!quote] Definizione — BGP
> **BGP (Border Gateway Protocol)** è il protocollo de facto per l'instradamento inter-dominio: la "colla che tiene insieme Internet". Permette alle sottoreti di pubblicizzare la loro esistenza e le destinazioni raggiungibili al resto di Internet.

BGP è un protocollo **path vector** (include l'AS-PATH per evitare cicli: un AS non accetta una rotta che lo include già).
- **eBGP (external BGP):** sessione tra router gateway di AS diversi; ottiene informazioni di raggiungibilità dai sistemi confinanti.
- **iBGP (internal BGP):** sessione tra router dello stesso AS; propaga le informazioni di raggiungibilità a tutti i router interni.
Le sessioni BGP si instaurano su connessioni **TCP semi-permanenti**.
**Messaggi BGP** (RFC 4271):

| Messaggio | Funzione |
|---|---|
| OPEN | Apre la connessione TCP e autentica il peer |
| UPDATE | Annuncia un nuovo percorso o ritira il vecchio |
| KEEPALIVE | Mantiene viva la connessione; ACK di OPEN |
| NOTIFICATION | Segnala errori o chiude la connessione |

**Attributi di una rotta BGP:**
- **AS-PATH:** elenco degli AS attraversati dall'annuncio del prefisso.
- **NEXT-HOP:** indirizzo IP dell'interfaccia del router che inizia l'AS-PATH.
**Selezione delle rotte BGP** (in ordine di priorità):
1. Valore dell'attributo di **preferenza locale** (decisione politica).
2. **AS-PATH più breve.**
3. Router **NEXT-HOP più vicino** (instradamento a patata bollente).
4. Identificatori BGP (tie-breaking).

> [!info] Instradamento a patata bollente (hot potato routing)
> Il router sceglie il gateway NEXT-HOP con il **minimo costo intra-AS**, indipendentemente dal costo inter-AS complessivo verso la destinazione: "disfati del pacchetto il prima possibile". È preferito perché riduce il carico trasportato internamente all'AS.

**Politiche attraverso gli annunci:** un ISP non annuncia ai peer le rotte apprese da altri peer (non vuole trasportare traffico di transito non remunerato).
**Perché protocolli intra-AS e inter-AS diversi?**
- *Politiche:* inter-AS richiede controllo esplicito su traffico e transito; intra-AS ha un singolo amministratore.
- *Scalabilità:* il routing gerarchico (AS + aggregazione di prefissi) limita la dimensione delle tabelle.
- *Prestazioni:* intra-AS può ottimizzare le prestazioni; inter-AS è dominato dalle politiche.
## Piano di controllo SDN
### Motivazione e vantaggi
Intorno al 2005 i router erano dispositivi monolitici con hardware di commutazione, OS proprietario e protocolli standard integrati. La gestione era complessa: i pesi OSPF erano le uniche "manopole di controllo" per l'ingegneria del traffico. Il **piano di controllo centralizzato** semplifica la gestione, permette l'inoltro generalizzato tramite tabelle dei flussi e favorisce implementazioni aperte (non proprietarie).
### Architettura a 3 livelli
1. **Switch del piano dei dati:** switch veloci e semplici; implementano l'inoltro generalizzato in hardware; tabella dei flussi calcolata e installata dal controller; comunicano con il controller via OpenFlow.
2. **Controller SDN (network OS):**
   - Mantiene lo stato della rete (link-state, host info, switch info, statistiche, flow tables) in un **database distribuito**.
   - Interagisce con le applicazioni di controllo "in alto" tramite **API northbound**.
   - Interagisce con gli switch "in basso" tramite **API southbound**.
   - Implementato come **sistema distribuito** per prestazioni, scalabilità, tolleranza ai guasti, robustezza e sicurezza.
3. **Applicazioni di controllo di rete:** i "cervelli" del controllo; implementano routing, access control, load balancing; possono provenire da terzi, distinti dal fornitore di routing o del controller SDN.
### Protocollo OpenFlow (controller ↔ switch)
Tre classi di messaggi:
- **Controller-to-switch:** features (interroga caratteristiche), configure (imposta parametri), modify-state (aggiunge/elimina/modifica voci di flusso), packet-out (invia pacchetto da porta specifica).
- **Switch-to-controller (asincroni):** packet-in (trasferisce pacchetto al controller), flow-removed (voce cancellata), port-status (notifica modifica su porta).
- Symmetric (misc.).

> [!example] Esempio: guasto di collegamento in una rete SDN
> 1. S1 rileva la caduta del collegamento con S2 → invia **port-status** OpenFlow al controller.
> 2. Il controller aggiorna le informazioni sullo stato del collegamento.
> 3. L'applicazione di routing Dijkstra (registrata per eventi di cambio stato) viene invocata.
> 4. Dijkstra accede al grafo della rete nel controller e calcola nuovi percorsi.
> 5. L'applicazione interagisce con il componente flow-table-computation del controller.
> 6. Il controller installa le nuove tabelle di flusso negli switch via OpenFlow.

**Intent-based networking (IBN):** l'utente esprime un obiettivo di alto livello in forma **dichiarativa** (il "cosa", es. "latenza < 5 ms tra datacenter A e B"); il sistema determina il "come" e monitora la rete per mantenere l'obiettivo automaticamente. SDN è fondamentale per le reti **cellulari 5G**.
## ICMP
**ICMP (Internet Control Message Protocol)** è usato da host e router per comunicare informazioni a livello di rete (segnalazione errori, diagnostica). Dal punto di vista architetturale si trova **sopra IP**: i messaggi ICMP sono trasportati come payload di datagrammi IP, non è un protocollo di trasporto usato direttamente dalle applicazioni.

> [!quote] Definizione — Messaggio ICMP
> Un **messaggio ICMP** è composto da: `tipo` (8 bit), `codice` (8 bit), `checksum` (16 bit), eventuali dati aggiuntivi dipendenti dal tipo (es. intestazione IP + primi 8 byte del datagramma che ha causato l'errore — utili per la demultiplazione grazie ai numeri di porta).

Tipi e codici principali:

| Tipo | Codice | Descrizione |
|---|---|---|
| 0 | 0 | Echo reply (ping) |
| 3 | 0 | Destination network unreachable |
| 3 | 1 | Destination host unreachable |
| 3 | 2 | Destination protocol unreachable |
| 3 | 3 | Destination port unreachable |
| 3 | 4 | Fragmentation required (PMTUD) |
| 4 | 0 | Source quench (**deprecato**, sostituito da ECN) |
| 8 | 0 | Echo request (ping) |
| 11 | 0 | TTL expired (**traceroute**) |
| 12 | 0 | Bad IP header |

Note sui tipi principali:
- Tipo 3 codice 0/1: inviati dai **router** lungo il percorso. Codice 2/3: inviati dall'**host di destinazione** (protocollo o porta non attivi).
- Tipo 3 codice 4: il campo *next-hop MTU* contiene la MTU del collegamento che ha causato il problema (usato da PMTUD).
- Tipo 4 (source quench): forzava il mittente a ridurre il tasso; oggi **deprecato** perché ECN è più efficiente e preciso.
- Tipo 8/0 e 0/0 (ping): la risposta contiene gli stessi dati della richiesta; può includere un timestamp per calcolare l'RTT in modo **stateless**; il server ping è implementato nel SO (non è un processo applicativo).
- Tipo 11 codice 0 (TTL expired): usato da **traceroute** — la sorgente invia segmenti UDP con TTL crescente (1, 2, 3, …) verso una porta improbabile; ogni router che scarta il pacchetto per TTL=0 invia ICMP tipo 11; l'arrivo a destinazione causa ICMP tipo 3 codice 3 (port unreachable); la sorgente si ferma e ha tracciato il percorso.
**ICMPv6** ridefinisce alcuni messaggi: "destination unreachable – fragmentation required" diventa **"Packet Too Big"**.
## Gestione della rete
### Componenti
> [!quote] Definizione — Gestione della rete
> La **gestione della rete** (Saydam 1996) comprende il funzionamento, l'integrazione e il coordinamento di hardware, software e personale tecnico per monitorare, verificare, configurare, analizzare, valutare e controllare le risorse della rete.

Componenti principali:
- **Server di gestione (management server / controller):** raccoglie, elabora e analizza informazioni; invia comandi ai dispositivi.
- **Dispositivo di rete gestito:** contiene *dati di configurazione* (assegnati dall'amministratore, es. indirizzo IP), *dati operativi* (acquisiti dal dispositivo, es. vicini OSPF) e *statistiche*.
- **Agente di gestione:** risiede nel dispositivo gestito; comunica con il server.
- **Protocollo di gestione:** protocollo a livello applicativo per interrogare lo stato e agire sui dispositivi.
### Tre approcci dell'operatore
1. **CLI (Command Line Interface):** comandi su console o script remoto (SSH/telnet); molti dispositivi offrono anche UI web. Approccio diretto ma non scalabile per reti grandi.
2. **SNMP/MIB:** interroga/imposta i dati negli oggetti MIB (Management Information Base) tramite Simple Network Management Protocol; principalmente per dati operativi e statistici di un singolo dispositivo.
3. **NETCONF/YANG:** più astratto, a livello di rete, olistico; enfasi sulla gestione della configurazione multi-dispositivo con commit atomici.
### SNMP e MIB
**MIB (Management Information Base):** i dati operativi e le statistiche sono modellati come **managed objects**, raccolti in moduli MIB (oltre 400 definiti da RFC + molti specifici del fornitore). Il linguaggio di definizione è **SMI (Structure of Management Information)**. Ogni managed object ha un **OID (Object Identifier)** univoco e gerarchico (percorso separato da punti, es. `1.3.6.1.2.1.7.1`).
Tipi di managed object:
- **Scalari:** singola istanza, identificata come `OID.0`.
- **Tabulari:** valori multipli, identificati con `OID.<indice-riga>` (a partire da 1).

> [!example] Estratto MIB per UDP
> | OID | Nome | Tipo | Descrizione |
> |---|---|---|---|
> | 1.3.6.1.2.1.7.1 | UDPInDatagrams | 32-bit counter | Datagrammi UDP consegnati |
> | 1.3.6.1.2.1.7.2 | UDPNoPorts | 32-bit counter | Nessuna app alla porta destinazione |
> | 1.3.6.1.2.1.7.3 | UDPInErrors | 32-bit counter | Non consegnabili per altra ragione |
> | 1.3.6.1.2.1.7.4 | UDPOutDatagrams | 32-bit counter | Datagrammi UDP inviati |
> | 1.3.6.1.2.1.7.5 | udpTable | SEQUENCE | Una voce per ogni porta UDP in uso |

**Protocollo SNMP** usa in genere **UDP** come trasporto. Due modalità:
- **Richiesta/risposta:** manager interroga l'agente; l'agente risponde.
- **Trap mode:** l'agente informa proattivamente il manager di un evento inatteso.

| Tipo messaggio | Funzione |
|---|---|
| GetRequest | Manager → agente: richiede dati |
| GetNextRequest | Richiede la prossima istanza di oggetto |
| GetBulkRequest | Richiede un blocco di dati |
| SetRequest | Manager → agente: imposta valore istanza/e MIB |
| Response | Agente → manager: risposta a richiesta |
| Trap | Agente → manager: notifica evento inatteso |
### NETCONF e YANG
**NETCONF** gestisce/configura attivamente i dispositivi; paradigma **RPC (Remote Procedure Call)**; messaggi codificati in **XML**; scambiati su protocollo affidabile e sicuro (TLS o SSH).
Operazioni principali: `<get-config>`, `<get>`, `<edit-config>` (con `<ok>` o `<rpc-error>` e rollback), `<lock>` / `<unlock>`, `<create-subscription>` / `<notification>`.
Differenza chiave rispetto a SNMP: NETCONF supporta la **configurazione simultanea di molteplici dispositivi con commit atomico** — impossibile con SNMP.

> [!info] YANG
> **YANG** è il linguaggio di modellazione dei dati per specificare struttura, sintassi e semantica dei dati di gestione NETCONF. Ha tipi di dati incorporati (come SMI) e può esprimere vincoli di correttezza e coerenza tra dati. Da una descrizione YANG si può generare automaticamente il documento XML che descrive il dispositivo.

---

**Prossimo argomento:** [[05 - Livello di Collegamento]] — Ethernet, switch, VLAN, protocolli di accesso multiplo e rilevazione degli errori.
