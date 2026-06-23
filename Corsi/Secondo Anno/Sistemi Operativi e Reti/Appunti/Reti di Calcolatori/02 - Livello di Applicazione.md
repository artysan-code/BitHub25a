# Livello di Applicazione
Il livello di applicazione è il livello più alto della [[01 - Introduzione#La pila di protocolli Internet — 5 livelli|pila di protocolli Internet]] ed è quello con cui interagisce direttamente lo sviluppatore. Qui vivono HTTP, DNS, SMTP e i protocolli P2P: il progettista scrive il codice dell'applicazione, sceglie l'architettura e l'eventuale protocollo di trasporto, ma non tocca il software dei router intermedi. Questa nota copre i principi delle applicazioni di rete, il protocollo Web HTTP (versioni 1.1, 2 e 3), la posta elettronica con SMTP, il DNS e infine BitTorrent, DASH e le CDN.
## Principi delle applicazioni di rete
### Architettura delle applicazioni
La struttura dell'applicazione determina come i processi sono organizzati sugli host. Esistono due paradigmi fondamentali.

**Paradigma client-server**
- **Server**: sempre attivo, con indirizzo IP fisso e permanente; spesso replicato in datacenter per la scalabilità; l'onere economico dell'infrastruttura è a carico del fornitore del servizio.
- **Client**: contatta il server quando necessario, può avere IP dinamico, non comunica direttamente con altri client.
- Esempi: Web, posta elettronica, FTP.

**Architettura peer-to-peer (P2P)**
- Nessun server sempre attivo (o infrastruttura server ridotta al minimo); coppie arbitrarie di host — detti **peer** — comunicano direttamente.
- **Scalabilità intrinseca**: ogni nuovo peer aggiunge capacità di servizio al sistema, sebbene generi anche nuovo carico.
- Sfide: gestione complessa (peer non sempre attivi, IP variabili), sicurezza, affidabilità.
- Esempio: BitTorrent.
### Processi e socket
> [\!quote] Definizione — Processo client e processo server
> Un **processo client** è quello che dà inizio alla comunicazione; un **processo server** è quello che attende di essere contattato. In P2P un processo può svolgere entrambi i ruoli nella stessa sessione.

I processi su host differenti comunicano scambiando messaggi attraverso il livello di trasporto. L'interfaccia tra il processo applicativo e la rete è la **socket**: il processo mittente fa uscire il messaggio dalla propria socket, presupponendo l'esistenza di un'infrastruttura di rete che lo consegni alla socket di destinazione.
- Parte controllata dallo sviluppatore: il codice applicativo al di sopra della socket.
- Parte controllata dal sistema operativo: tutto al di sotto della socket (trasporto, rete, collegamento, fisico).

**Indirizzamento**: per ricevere messaggi, un processo necessita di un **identificatore** composto da indirizzo IP (32 bit IPv4 o 128 bit IPv6) e **numero di porta**. Il solo indirizzo IP non basta: sullo stesso host possono girare molti processi. Porte well-known assegnate da IANA:
- HTTP server: **porta 80**
- Mail server SMTP: **porta 25**
- DNS: **porta 53**
### Definizione di un protocollo a livello applicazione
Un protocollo di livello applicazione definisce: i **tipi** di messaggi scambiati (richiesta, risposta), la **sintassi** (campi e descrizione), la **semantica** (significato dei campi) e le **regole** (quando e come inviare/rispondere).

Protocolli di pubblico dominio (RFC — IETF): HTTP, SMTP → interoperabilità garantita. Protocolli proprietari: Skype, Zoom.
### Servizi di trasporto richiesti dalle applicazioni
Le applicazioni richiedono dai protocolli di trasporto quattro dimensioni di servizio.

| Dimensione | Descrizione |
|---|---|
| **Perdita di dati** | Alcune app richiedono trasferimento 100% affidabile (web, file); altre tollerano perdite (audio/video in tempo reale) |
| **Throughput** | App "sensibili alla banda" (multimediali) richiedono un throughput minimo; app "elastiche" usano la banda disponibile |
| **Sensibilità al fattore tempo** | Telefonia IP, giochi interattivi richiedono ritardi bassi (centinaia di ms) |
| **Sicurezza** | Riservatezza, integrità, autenticazione |

Requisiti di trasporto per applicazione tipica:

| Applicazione | Tolleranza perdita | Throughput | Sensib. al tempo |
|---|---|---|---|
| Trasferimento file | No | Variabile | No |
| Posta elettronica | No | Variabile | No |
| Documenti Web | No | Variabile | No |
| Audio in tempo reale | Sì | 5 kbps–1 Mbps | Sì (centinaia di ms) |
| Video in tempo reale | Sì | 10 kbps–5 Mbps | Sì (centinaia di ms) |
| Streaming audio/video memorizzati | Sì | Come sopra | Sì (pochi secondi) |
| Giochi interattivi | Sì | Fino a pochi kbps | Sì (centinaia di ms) |
| Messaggistica istantanea | No | Variabile | Sì e no |

**Servizio TCP** (vedi [[03 - Livello di Trasporto]]):
- Trasporto **affidabile** (senza errori, perdite, nell'ordine corretto).
- **Controllo di flusso**: il mittente non sovraccarica il destinatario.
- **Controllo della congestione**: strozza il mittente se la rete è congestionata.
- **Orientato alla connessione**: richiede setup (handshaking).
- Non offre: temporizzazione, banda minima garantita, sicurezza nativa.

**Servizio UDP**:
- Trasferimento **inaffidabile**, senza connessione.
- Non offre: affidabilità, controllo di flusso, controllo della congestione, temporizzazione, banda minima garantita, sicurezza.
- Vantaggio: maggiore controllo dell'applicazione sull'invio (nessun overhead di controllo).

**Sicurezza su TCP — TLS (Transport Layer Security)**:
- Le socket TCP e UDP non cifrano i dati nativamente: le password transiterebbero in chiaro.
- TLS è implementato a **livello applicazione** tramite librerie.
- Offre: connessioni TCP cifrate, controllo di integrità, autenticazione end-to-end.
- Il testo in chiaro inviato alla socket TLS viene cifrato prima di entrare nella socket TCP sottostante.

Protocolli di trasporto usati dalle principali applicazioni:

| Applicazione | Protocollo applicativo | Trasporto |
|---|---|---|
| Trasferimento file | FTP [RFC 959] | TCP |
| Posta elettronica | SMTP [RFC 5321] | TCP |
| Documenti web | HTTP [RFC 7230, 9110] | TCP |
| Telefonia Internet | SIP [RFC 3261], RTP [RFC 3550] | UDP o TCP |
| Streaming audio/video | HTTP [RFC 7230], DASH | TCP |
| Giochi interattivi | Proprietario | UDP o TCP |
## Web e HTTP
### Terminologia
> [\!quote] Definizione — HTTP
> **HTTP (HyperText Transfer Protocol)** è il protocollo a livello applicazione del Web. Una **pagina web** è un insieme di oggetti (file HTML di base, immagini JPEG, script JS, fogli CSS, file audio), ciascuno identificabile da un **URL** nella forma `schema://nome-host/percorso`.

- HTTP usa **TCP** (fino a HTTP/3 escluso), porta **80**.
- Sequenza: apertura connessione TCP → scambio messaggi HTTP → chiusura connessione TCP.
- **HTTP è stateless**: il server non mantiene informazioni sulle richieste passate del client; i protocolli con stato sono più complessi da gestire (storia da memorizzare, riconciliazione in caso di crash).
### Connessioni non persistenti vs persistenti
**Connessioni non persistenti (HTTP/1.0)**: per ogni oggetto si apre una connessione TCP separata, si invia una coppia richiesta/risposta, poi si chiude la connessione. Scaricare una pagina con più oggetti richiede connessioni multiple.

> [\!quote] Definizione — RTT
> **RTT (Round-Trip Time)**: tempo impiegato da un piccolo pacchetto per andare dal client al server e ritornare. Include ritardi di propagazione, accodamento e elaborazione.

**Tempo di risposta con connessioni non persistenti:**
$$T_{non\text{-}pers} = 2\,\text{RTT} + T_{trasmissione}$$
- 1 RTT per inizializzare la connessione TCP (SYN + SYN-ACK).
- 1 RTT per la richiesta HTTP e i primi byte della risposta.
- $T_{trasmissione}$ = tempo di trasmissione dell'oggetto sul collegamento.

Svantaggi: 2 RTT per oggetto; allocazione di buffer e variabili TCP per ogni connessione; i browser aprono connessioni TCP parallele per compensare, ma il controllo della congestione limita il throughput iniziale di ogni nuova connessione.

**Connessioni persistenti (HTTP/1.1)**: il server lascia la connessione TCP aperta dopo l'invio della risposta. Le richieste successive tra gli stessi client e server transitano sulla stessa connessione. Il client invia le richieste non appena incontra un oggetto referenziato → **un solo RTT per tutti gli oggetti** referenziati (anziché 2 RTT per ciascuno).
### Messaggi di richiesta HTTP
Due tipi di messaggi HTTP: **richiesta** e **risposta**. Il formato è testuale ASCII, leggibile dall'utente; ogni riga termina con CR LF (`\r\n`).

Struttura del messaggio di richiesta: **riga di richiesta** (metodo + URL + versione) → **righe di intestazione** (header lines) → riga vuota (`\r\n`) → **corpo dell'entità** (body, opzionale, lunghezza in `Content-Length`).

```
GET /index.html HTTP/1.1\r\n
Host: www-net.cs.umass.edu\r\n
User-Agent: Mozilla/5.0 ...\r\n
Accept: text/html,...\r\n
Accept-Language: en-us,en;q=0.5\r\n
Accept-Encoding: gzip,deflate\r\n
Connection: keep-alive\r\n
\r\n
```

Campi di intestazione principali nella richiesta:
- `Host`: hostname (e porta) del server — **obbligatorio in HTTP/1.1** (necessario per virtual hosting e web cache; assenza → `400 Bad Request`).
- `User-Agent`: identificazione di applicazione, SO, vendor e versione del browser.
- `Accept`: media type compresi dal client.
- `Accept-Language`: lingue/locale preferiti.
- `Accept-Encoding`: algoritmi di compressione compresi.
- `Connection`: `close` → connessione non persistente; `keep-alive` → persistente (default HTTP/1.1).

**Metodi HTTP:**

| Metodo | Descrizione |
|---|---|
| `GET` | Recupera la risorsa; parametri utente nella query string (`?chiave=valore`) |
| `POST` | Invia dati nel corpo dell'entità; parametri non visibili nell'URL |
| `HEAD` | Come GET ma il server restituisce solo le intestazioni (nessun corpo) |
| `PUT` | Carica/sostituisce completamente un file sul server |

**Idempotenza**: un'operazione è **idempotente** se l'effetto sul server di una singola richiesta è identico a quello di più richieste identiche.
- Idempotenti: `GET`, `PUT`, `HEAD` → il client può ritentare automaticamente in caso di problemi di rete transitori.
- Non idempotente: `POST` in generale (una seconda chiamata crea un secondo elemento).
- Regola pratica per i form: usare `GET` per operazioni idempotenti (es. ricerca), `POST` per le altre (es. aggiunta al carrello).
### Messaggi di risposta HTTP
Struttura: **riga di stato** (versione + codice + espressione) → **righe di intestazione** → **dati** (oggetto o file HTML).

```
HTTP/1.1 200 OK\r\n
Date: Tue, 08 Sep 2020 00:53:20 GMT\r\n
Server: Apache/2.4.6 ...\r\n
Last-Modified: Tue, 01 Mar 2016 18:57:50 GMT\r\n
ETag: "a5b-52d015789ee9e"\r\n
Accept-Ranges: bytes\r\n
Content-Length: 2651\r\n
Content-Type: text/html; charset=UTF-8\r\n
\r\n
data data data...
```

Campi di intestazione principali nella risposta:
- `Date`: data e ora di originazione del messaggio.
- `Server`: software del server (troppi dettagli possono aiutare gli attaccanti).
- `Last-Modified`: data/ora dell'ultima modifica dell'oggetto (usato per il GET condizionale).
- `Accept-Ranges`: supporto ai download parziali.
- `Content-Length`: lunghezza in byte del corpo.
- `Content-Type`: media type del corpo.
### Codici di stato HTTP (RFC 7231)
La prima cifra del codice discrimina la categoria:

| Classe | Significato | Esempi |
|---|---|---|
| `1xx` | Informational — risposta intermedia | — |
| `2xx` | Successful — richiesta accettata | `200 OK` |
| `3xx` | Redirect — il client deve compiere ulteriori azioni | `301 Moved Permanently` |
| `4xx` | Client Error — richiesta scorretta o non soddisfabile | `400 Bad Request`, `404 Not Found`, `406 Not Acceptable` |
| `5xx` | Server Error — il server ha fallito nel soddisfare una richiesta valida | `505 HTTP Version Not Supported` |

Codici citati dal prof:
- `200 OK`: successo, oggetto inviato nella risposta.
- `301 Moved Permanently`: nuova posizione nell'intestazione `Location:`.
- `400 Bad Request`: messaggio non compreso dal server.
- `404 Not Found`: documento non presente sul server.
- `406 Not Acceptable`: l'oggetto non esiste in una forma che soddisfa i campi `Accept-*`.
- `505 HTTP Version Not Supported`.
### Cookie
HTTP è stateless → i **cookie** consentono di mantenere stato tra le transazioni HTTP.

**Quattro componenti del meccanismo cookie:**
1. Riga di intestazione `Set-Cookie:` nel messaggio di **risposta** HTTP (il server assegna l'identificativo).
2. Riga di intestazione `Cookie:` nel messaggio di **richiesta** HTTP (il browser lo riporta).
3. File cookie sul sistema terminale dell'utente, gestito dal browser.
4. Database sul sito, indicizzato dall'identificativo cookie.

> [\!example] Flusso cookie — Amazon
> Prima visita → il server crea identificativo `1678` e voce nel database → risposta con `Set-Cookie: 1678`.
> Richieste successive → il browser include `Cookie: 1678` → il server esegue azioni personalizzate per quell'utente (raccomandazioni, carrello, autorizzazione).

Usi dei cookie: autorizzazione, carrello degli acquisti, raccomandazioni, stato della sessione (es. webmail).

**Cookie di prima parte**: impostati dal sito visitato dall'utente.
**Cookie di terze parti** (tracking cookies): impostati da siti (es. AdX.com) che si caricano come risorse nelle pagine di altri siti → tracciano il comportamento su più siti senza che l'utente abbia scelto di visitarli. Disabilitati di default in Firefox e Safari; Chrome li sta eliminando progressivamente.

> [\!info] GDPR e cookie
> Quando i cookie possono identificare un individuo, sono considerati dati personali soggetti al **GDPR (EU General Data Protection Regulation)**: l'utente deve avere controllo esplicito sull'autorizzazione.
### Web cache (server proxy)
**Obiettivo**: soddisfare le richieste del client senza coinvolgere ogni volta il server d'origine.

**Funzionamento:**
1. Il browser invia tutte le richieste HTTP alla cache.
2. Se l'oggetto è in cache → la cache lo restituisce direttamente (cache hit).
3. Altrimenti → la cache richiede l'oggetto al server d'origine, lo memorizza nella propria memoria su disco, lo restituisce al client (cache miss).

La cache opera sia da **client** (verso il server d'origine) sia da **server** (verso il client).

Vantaggi del web caching:
- Riduce i **tempi di risposta** (la cache è fisicamente più vicina ai client).
- Riduce il **traffico sul collegamento di accesso** a Internet istituzionale.
- Riduce il traffico globale su Internet.

**Campo `Cache-Control`** nelle risposte del server:
- `max-age=3600`: la risposta può essere usata dalla cache per 3600 secondi senza rivalidare.
- `no-cache`: la risposta può essere memorizzata ma non usata senza rivalidazione (non significa "non memorizzare").
- `must-revalidate`: la cache non può restituire una risposta scaduta.

> [\!example] Esempio numerico — confronto con e senza cache
> Scenario: collegamento di accesso 1,54 Mbps, ritardo Internet 2 s, oggetto 100 kbit, frequenza 15 req/s → velocità dati 1,50 Mbps.
>
> Senza cache: utilizzazione $= \frac{1{,}50}{1{,}54} = 0{,}97$ → ritardo di accodamento nell'ordine dei minuti.
>
> Opzione 1 — collegamento 154 Mbps: utilizzazione $= 0{,}0097$, ritardo millisecondico, ma costosa.
>
> Opzione 2 — web cache con hit rate $= 0{,}4$:
> - Tasso sul collegamento d'accesso: $0{,}6 \times 1{,}50 = 0{,}9\ \text{Mbps}$, utilizzazione $\approx 0{,}58$.
> - Ritardo medio end-to-end:
> $$\bar{T} = 0{,}6 \times 2{,}01\ \text{s} + 0{,}4 \times (\sim\text{ms}) \approx 1{,}2\ \text{s}$$
> Risultato: ritardo medio inferiore alla soluzione con collegamento potenziato, a costo nettamente inferiore.
### GET condizionale
**Obiettivo**: non inviare l'oggetto se la cache ha già una copia aggiornata, risparmiando banda e tempo di trasmissione.

**Meccanismo:**
- La cache specifica nella richiesta: `If-Modified-Since: <data>` (data dell'ultima copia memorizzata).
- Se l'oggetto **non è stato modificato**: il server risponde `304 Not Modified` senza corpo → nessun consumo di banda per l'oggetto.
- Se l'oggetto **è stato modificato**: il server risponde `200 OK` con i dati aggiornati.

```
GET /fruit/kiwi.gif HTTP/1.1
Host: www.exotiquecuisine.com
If-Modified-Since: Wed, 9 Sep 2015 09:23:24
```
### HTTP/2
**Problema di HTTP/1.1**: richieste GET multiple in pipeline su singola connessione TCP, ma scheduling FCFS. Il **HOL blocking (head-of-line blocking)** fa attendere oggetti piccoli dietro oggetti grandi; la ritrasmissione di segmenti TCP persi blocca tutti gli oggetti.

**Soluzioni in HTTP/2 [RFC 7540, 2015]:**
- Metodi, codici di stato, header field: invariati rispetto a HTTP/1.1.
- **Codifica binaria** dei messaggi + compressione degli header.
- Ordine di trasmissione basato su **priorità specificata dal client** (non necessariamente FCFS).
- **Server push**: il server invia oggetti aggiuntivi senza che il client li abbia richiesti esplicitamente.
- **Frame e interlacciamento**: ogni oggetto è suddiviso in frame; frame di oggetti diversi sono interlacciati sulla stessa connessione TCP → mitigazione dell'HOL blocking.
- Un'unica connessione TCP → minor overhead sul server, migliore funzionamento del controllo della congestione.

> [\!example] HOL blocking: HTTP/1.1 vs HTTP/2
> Richiesti O1 (grande), O2, O3, O4 (piccoli) sulla stessa connessione.
> - **HTTP/1.1**: O2, O3, O4 aspettano dietro O1 (FCFS).
> - **HTTP/2**: i frame di O2, O3, O4 sono inframezzati con i frame di O1 → O2, O3, O4 consegnati rapidamente; O1 è leggermente ritardato ma il ritardo complessivo percepito è inferiore.
### HTTP/3
**Problema residuo di HTTP/2**: la singola connessione TCP causa comunque blocco in caso di perdita di pacchetti; i browser aprono più connessioni TCP parallele per compensare. Assenza di sicurezza nativa su TCP semplice.

**HTTP/3**: aggiunge sicurezza, controllo di errore per oggetto e controllo della congestione (con più pipelining) su **UDP**. I dettagli del livello di trasporto sono trattati in [[03 - Livello di Trasporto]].
## Posta elettronica (E-mail)
### Tre componenti principali
> [\!quote] Definizione — Componenti del sistema e-mail
> 1. **User agent** (agente utente / "mail reader"): composizione, editing e lettura dei messaggi (es. Outlook, client iPhone); i messaggi in entrata e uscita sono memorizzati sul server.
> 2. **Mail server**: contiene la **mailbox** (messaggi in arrivo per l'utente) e la **coda di messaggi** da trasmettere (con tentativi periodici in caso di fallimento).
> 3. **SMTP (Simple Mail Transfer Protocol)**: protocollo per il trasferimento dei messaggi tra mail server.
### SMTP [RFC 5321]
- Usa **TCP** per il trasferimento affidabile; porta **25**.
- **Trasferimento diretto**: dal mail server del mittente al mail server del destinatario (nessun server intermedio di relay obbligatorio).
- **Tre fasi**: handshaking (saluto) → trasferimento dei messaggi → chiusura.
- Interazione **comando/risposta** (come HTTP): comandi in testo ASCII a 7 bit, risposte con codice di stato + espressione.

**Scenario Alice → Bob (6 passi):**
1. Alice usa lo user agent per comporre il messaggio a `bob@someschool.edu`.
2. Lo user agent invia il messaggio al mail server di Alice (coda).
3. Il lato client SMTP apre una connessione TCP con il mail server di Bob (porta 25).
4. Il client SMTP invia il messaggio sulla connessione TCP.
5. Il mail server di Bob pone il messaggio nella mailbox di Bob.
6. Bob invoca il suo user agent per leggere il messaggio.

> [\!example] Interazione SMTP
> ```
> S: 220 hamburger.edu
> C: HELO crepes.fr
> S: 250 Hello crepes.fr, pleased to meet you
> C: MAIL FROM: <alice@crepes.fr>
> S: 250 alice@crepes.fr... Sender ok
> C: RCPT TO: <bob@hamburger.edu>
> S: 250 bob@hamburger.edu ... Recipient ok
> C: DATA
> S: 354 Enter mail, end with "." on a line by itself
> C: Do you like ketchup?
> C: How about pickles?
> C: .
> S: 250 Message accepted for delivery
> C: QUIT
> S: 221 hamburger.edu closing connection
> ```

**SMTP vs HTTP:**
- HTTP è **client pull** (il client scarica quando vuole); SMTP è **client push** (il mittente invia).
- Entrambi: interazione comando/risposta ASCII, codici di stato, supporto a connessioni persistenti.
- HTTP: ogni oggetto in un proprio messaggio di risposta; SMTP: più oggetti in un unico messaggio.
- SMTP richiede che il messaggio (intestazione + corpo) sia in **ASCII a 7 bit**.
- SMTP usa `CRLF.CRLF` per determinare la fine del messaggio.

**Dot-stuffing**: meccanismo di escaping per righe che contengono solo un punto. Il client invia `..` (due punti) al posto di `.` a inizio riga; il server ripristina `.` in ricezione.
### Formato dei messaggi di posta
- **RFC 5321**: definisce il protocollo SMTP (come RFC 9110 definisce HTTP).
- **RFC 2822**: definisce la sintassi dei messaggi.
  - Righe di intestazione: `To:`, `From:`, `Subject:` — distinte dai comandi SMTP `MAIL FROM:`, `RCPT TO:`.
  - Corpo: solo caratteri ASCII; separato dall'intestazione da una riga vuota.
- **RFC 2045 e 2046 — MIME** (Multipurpose Internet Mail Extensions): estende il formato per includere contenuti non testuali (immagini, audio, video, documenti) e messaggi multipart.
  - Codifica `quoted-printable`: i caratteri non-ASCII e il carattere `=` sono espressi come `=xx` (esadecimale); i caratteri ASCII stampabili restano invariati.
  - Codifica `base64`: conversione di dati binari in caratteri ASCII (overhead circa 40%).
### Protocolli di accesso alla posta
- **SMTP**: consegna e memorizzazione sul server del destinatario (push).
- **IMAP** (Internet Mail Access Protocol, RFC 3501): recupero, cancellazione e archiviazione dei messaggi **sul server** (pull); mantiene lo stato della mailbox lato server.
- **HTTP**: Gmail, Hotmail, Yahoo\!Mail → interfaccia web sopra SMTP (invio) e IMAP (recupero).
## DNS — Domain Name System
### Motivazione
Gli host e i router usano **indirizzi IP** (32 bit per IPv4) per indirizzare i datagrammi; gli esseri umani usano **nomi** (`cs.umass.edu`). Il file `/etc/hosts` (POSIX) fornisce una mappatura locale hostname → IP, ma è locale al nodo e non scalabile. Negli anni '70 esisteva un file `HOSTS.TXT` centralizzato: con la crescita di Internet, divenne impraticabile (file enorme, traffico concentrato sull'host di pubblicazione).

**Perché non centralizzare il DNS?**
- **Single point of failure**: se il server DNS si guasta, ne soffre l'intera Internet.
- **Volume di traffico**: un singolo server non può gestire miliardi di query (Comcast: 600 miliardi/giorno; Akamai: 2,2 trilioni/giorno).
- **Database distante**: non può essere vicino a tutti i client.
- **Manutenzione**: dovrebbe contenere record per tutti gli host di Internet.
### Cos'è DNS
> [\!quote] Definizione — DNS
> Il **DNS (Domain Name System)** è un **database distribuito** implementato in una gerarchia di name server e un **protocollo a livello applicazione** che consente a host e name server di comunicare per risolvere i nomi hostname → indirizzo IP. È un esempio di funzione critica di Internet implementata a livello applicazione — la complessità è nelle parti periferiche della rete.
### Servizi DNS
- **Traduzione hostname → indirizzo IP** (funzione principale).
- **Host aliasing**: un host con nome canonico complesso può avere alias più semplici (es. `www.ibm.com` è alias di `servereast.backup2.ibm.com`).
- **Mail server aliasing**: record MX per indirizzare la posta al mail server corretto.
- **Load distribution**: più indirizzi IP corrispondono allo stesso nome; il DNS ruota l'ordine dei record `A` per bilanciare il carico tra server replicati.
### Struttura gerarchica
Il DNS è organizzato in tre livelli principali:

```
Root DNS Servers
├── TLD .com DNS servers
│   ├── yahoo.com DNS servers
│   └── amazon.com DNS servers
├── TLD .org DNS servers
└── TLD .edu DNS servers
    ├── nyu.edu DNS servers
    └── umass.edu DNS servers
```

**Risoluzione di `www.amazon.com` (prima approssimazione):**
1. Il client interroga il **root server** → ottiene l'indirizzo del TLD server `.com`.
2. Il client interroga il **TLD server `.com`** → ottiene l'indirizzo del server autoritativo `amazon.com`.
3. Il client interroga il **server autoritativo `amazon.com`** → ottiene l'indirizzo IP di `www.amazon.com`.
### Root name server
- Contatto di **ultima istanza** per i name server che non riescono a risolvere il nome.
- Forniscono gli indirizzi IP dei TLD server.
- **13 name server logici** in tutto il mondo, ciascuno replicato più volte.
- Al 20/03/2023: **1813 istanze** gestite da 12 operatori, coordinate dallo **IANA**.
- **ICANN** (Internet Corporation for Assigned Names and Numbers) gestisce il root DNS domain.
- **DNSSEC**: offre autenticazione e integrità dei messaggi DNS (firma crittografica delle risposte).
### TLD e server autoritativi
**TLD (Top-Level Domain) DNS server:**
- Gestiscono domini generici (`.com`, `.org`, `.net`, `.edu`, `.aero`) e nazionali (`.it`, `.cn`, `.uk`, `.fr`, `.jp`).
- Network Solutions: gestisce `.com` e `.net`; Educause: gestisce `.edu`.

**Server DNS autoritativo:**
- DNS proprio di ciascuna organizzazione; fornisce le mappature hostname → IP ufficiali per gli host dell'organizzazione.
- Può essere mantenuto dall'organizzazione stessa o dal service provider.
### DNS server locale (resolver DNS ricorsivo)
Quando un host effettua una richiesta DNS, la query è inviata al proprio **DNS server locale**. Il server locale risponde:
- Dalla **cache locale** (potenzialmente non aggiornata).
- Inoltrandola alla gerarchia DNS.

Ciascun ISP ha un proprio server DNS locale. Non appartiene strettamente alla gerarchia dei server autoritativi; nella pratica gli host usano uno **stub resolver** che si appoggia a questo resolver ricorsivo.
### Risoluzione iterativa vs ricorsiva
**Interrogazione iterativa (tipica):**
- Il server locale contatta il root server → riceve referral al TLD.
- Il server locale contatta il TLD → riceve referral al server autoritativo.
- Il server locale contatta il server autoritativo → riceve la risposta.
- Ogni server contattato risponde: "Non conosco questo nome, ma puoi chiedere a questo server."

**Interrogazione ricorsiva:**
- Il server locale affida l'intero compito al server contattato, che a sua volta contatta il livello successivo della gerarchia e così via.
- Carico pesante ai livelli superiori; nella pratica usata solo dal client verso il server locale.
### Caching e TTL
- Ogni name server che apprende una mappatura la **memorizza in cache**.
- Le voci vanno in **timeout (TTL, Time To Live)**: dopo la scadenza il record deve essere richiesto di nuovo.
- I server TLD sono in genere memorizzati nella cache dei server locali, riducendo la frequenza di interrogazione dei root server.

> [\!warning] Record DNS obsoleti
> Se un host cambia indirizzo IP, la vecchia mappatura può rimanere nelle cache per tutto il tempo del TTL → periodo transitorio in cui il nome risolve all'indirizzo vecchio. La traduzione nome → indirizzo è **best-effort**.
### Record DNS (Resource Record, RR)
> [\!quote] Definizione — Resource Record
> Un **RR (Resource Record)** è la struttura dati fondamentale del DNS. Formato: `(name, value, type, ttl)`.

| Tipo | `name` | `value` |
|---|---|---|
| `A` | hostname | indirizzo IP (IPv4) |
| `NS` | dominio (es. `foo.com`) | hostname del name server autoritativo per quel dominio |
| `CNAME` | nome alias | nome canonico (nome vero) |
| `MX` | nome (dominio) | hostname del mail server associato |

Note importanti:
- Non può esistere un record `CNAME` e nessun altro tipo per lo stesso `name`.
- Possibile avere sia `A` sia `MX` per lo stesso nome (scopi diversi: `A` per il browser, `MX` per SMTP).
- Più record dello stesso tipo per lo stesso nome (tranne `CNAME`): per fault tolerance e load balancing.
- Record `MX`: ha un **preference value** (intero 16 bit senza segno); **più basso = più preferito**; a parità di valore il client SMTP sceglie a caso e sale in caso di problemi.
### Formato messaggi DNS
Query e risposta DNS hanno lo **stesso formato**:

| Campo | Dim. | Descrizione |
|---|---|---|
| Identificazione | 2 byte | Numero a 16 bit; la risposta riporta lo stesso numero della domanda |
| Flag | 2 byte | Domanda/risposta; richiesta di ricorsione; ricorsione disponibile; server autoritativo |
| N. di domande | 2 byte | |
| N. di RR di risposta | 2 byte | |
| N. di RR autoritativi | 2 byte | |
| N. di RR addizionali | 2 byte | |
| Sezione domande | variabile | Nome richiesto e tipo di domanda |
| Sezione risposte | variabile | RR in risposta alla domanda |
| Sezione autoritativa | variabile | Record per server autoritativi (referral) |
| Sezione aggiuntiva | variabile | Informazioni extra (es. record `A` per l'hostname citato in un record `MX`) |
### Inserimento record nel DNS
Esempio: nuova società "Network Utopia":
1. Registrazione di `networkutopia.com` presso un **DNS registrar** accreditato ICANN (es. Network Solutions): si forniscono nome e IP degli authoritative name server primario e secondario. Il registrar inserisce nel TLD server `.com`: `(networkutopia.com, dns1.networkutopia.com, NS)` e `(dns1.networkutopia.com, 212.212.212.1, A)`.
2. Inserimento nell'authoritative server proprio: record `A` per `www.networkutopia.com`, record `MX` per `networkutopia.com`.
### Sicurezza del DNS
> [\!warning] Attacchi al DNS
> - **DDoS sui root server**: finora senza successo grazie al filtraggio del traffico e al caching dei TLD; attacchi ai TLD server sarebbero più pericolosi.
> - **DNS cache poisoning (spoofing)**: l'attaccante intercetta query DNS e restituisce risposte false, reindirizzando il traffico verso host malevoli. **DNSSEC** (RFC 4033) contrasta questo attacco tramite autenticazione e integrità crittografica.
## Distribuzione di file P2P — BitTorrent
### Confronto client-server vs P2P
Dati: file di dimensione $F$, $N$ peer, banda di upload del server $u_s$, banda di upload del peer $i$: $u_i$, banda di download minima: $d_{min}$.

**Tempo di distribuzione client-server:**
$$D_{c\text{-}s} \geq \max\\!\left\{\frac{NF}{u_s},\, \frac{F}{d_{min}}\right\}$$
Il tempo cresce **linearmente** in $N$: il server deve inviare $N$ copie con banda $u_s$ fissa.

**Tempo di distribuzione P2P:**
$$D_{P2P} \geq \max\\!\left\{\frac{F}{u_s},\, \frac{F}{d_{min}},\, \frac{NF}{u_s + \sum_i u_i}\right\}$$
Anche il denominatore $\sum_i u_i$ cresce con $N$ (ogni nuovo peer porta capacità di upload aggiuntiva) → il tempo P2P cresce molto più lentamente rispetto al client-server all'aumentare di $N$.
### BitTorrent
> [\!quote] Definizione — BitTorrent
> **BitTorrent** è il principale protocollo P2P per la distribuzione di file. Il file è suddiviso in **chunk** da 256 kB tipici. L'insieme di tutti i peer che partecipano alla distribuzione di un file è detto **torrent**. Un nodo **tracker** tiene traccia dei peer nel torrent.

**Ingresso di un nuovo peer:**
1. Il peer non ha chunk; si registra presso il tracker.
2. Il tracker restituisce un elenco di circa 50 peer nel torrent.
3. Il peer stabilisce connessioni TCP con un sottoinsieme di peer vicini.
4. Informa periodicamente il tracker di essere ancora attivo.

**Richiesta di chunk — strategia "rarest first" (prima i più rari):**
- Il peer chiede periodicamente ai vicini l'elenco dei chunk in loro possesso.
- Richiede i chunk mancanti con **priorità ai più rari** → uniforma la distribuzione globale, massimizza le possibilità di scambio reciproco.
- Peer appena entrato: può richiedere un chunk casuale per avere subito qualcosa da condividere.
- **End game**: verso la fine del file, richiede lo stesso blocco mancante a più peer simultaneamente; annulla le richieste pendenti non appena lo riceve.

**Invio di chunk — meccanismo tit-for-tat ("pan per focaccia"):**
- Il peer invia chunk ai **4 vicini** che gli inviano chunk alla velocità più alta (peer **unchoked**).
- Tutti gli altri peer sono **choked** (non ricevono chunk da lui).
- Rivalutazione dei 4 ogni **10 secondi**.
- Ogni **30 secondi**: un vicino è selezionato casualmente come **"optimistically unchoked"** → può entrare nella top 4 se offre banda sufficiente.

> [\!info] Perché tit-for-tat funziona
> Il meccanismo crea un incentivo implicito: chi carica velocemente trova partner migliori, chi non carica viene choked. La rete si auto-organizza in modo efficiente senza coordinamento centralizzato.

Un peer che ha completato il file può rimanere come **seeder** (altruisticamente) o uscire dal torrent.
## Streaming video e CDN
### Codifica video
- Un **video** è una sequenza di immagini a frame rate costante (es. 24 immagini/secondo).
- Un'**immagine digitale** è un array di pixel, ciascuno rappresentato da bit.
- **Codifica spaziale**: ridondanza all'interno dello stesso frame (es. N pixel dello stesso colore → valore + contatore).
- **Codifica temporale**: invece di inviare il frame $i+1$ completo, si inviano solo le differenze dal frame $i$.
- **CBR (constant bit rate)**: bit rate costante; **VBR (variable bit rate)**: bit rate variabile con la ridondanza.

Bit rate tipici:
- MPEG-1 (CD-ROM): **1,5 Mbps**
- MPEG-2 (DVD): **3–6 Mbps**
- MPEG-4 (Internet): **64 kbps – 12 Mbps**
### Sfide dello streaming
- La banda da server a client **varia nel tempo** per congestione variabile.
- Perdita di pacchetti e ritardi → qualità ridotta o interruzioni.
- **Vincolo di riproduzione continua**: una volta avviata, la riproduzione deve procedere ai tempi di registrazione originali → necessità di un **buffer lato client** per compensare il jitter (variazione del ritardo di rete).

**Streaming HTTP (base):** il server trasmette alla massima velocità consentita dal controllo di congestione TCP. Se la velocità di ricezione supera il bit rate video, il buffer cresce (**prefetching**) fino al riempimento; il controllo di flusso TCP limita poi la trasmissione al tasso di consumo. L'intestazione HTTP `Range` consente salti a posizioni diverse nel video.
### DASH — Dynamic, Adaptive Streaming over HTTP
> [\!quote] Definizione — DASH
> **DASH (Dynamic, Adaptive Streaming over HTTP)** è un sistema di streaming adattivo in cui il video è codificato in **più versioni a bit rate differenti**, suddivise in **segmenti (blocchi)**. Il client sceglie dinamicamente quale versione richiedere in base alla banda stimata.

**Lato server:**
- Il video è codificato in più versioni a qualità crescente.
- Un **manifest file** (XML) descrive le versioni disponibili, con URL e bit rate di ciascun blocco.

**Lato client:**
- Stima periodicamente la banda disponibile.
- Consulta il manifest e richiede **un blocco alla volta**.
- Sceglie la versione con il **bit rate più alto sostenibile** data la banda corrente.
- Può richiedere blocchi da server diversi (es. il più vicino).

L'"intelligenza" lato client determina: quando richiedere un blocco (evitare starvation o overflow del buffer), che bit rate richiedere, da quale server.

> [\!info] Semplicità lato server
> Il lato server DASH è un semplice web server in grado di servire contenuti statici (manifest + blocchi). Tutta la logica adattiva è lato client.
### CDN — Content Distribution Network
> [\!quote] Definizione — CDN
> Una **CDN (Content Distribution Network)** gestisce server distribuiti geograficamente, memorizza copie dei contenuti e dirige le richieste degli utenti al nodo in grado di offrire il servizio migliore. Può essere **privata** (es. OpenConnect di Netflix) o **di terze parti** (es. Akamai per conto di più fornitori).

**Problema**: un unico datacenter è un single point of failure, punto di congestione e genera percorsi lunghi verso i client lontani.

Due strategie di deployment:
- **Enter deep**: server CDN installati in profondità nelle reti di accesso ISP → vicinanza agli utenti, minori ritardi e maggior throughput, ma maggiore complessità di gestione. Esempio: **Akamai** (240.000 server in più di 120 paesi nel 2015).
- **Bring home**: pochi grandi cluster in **IXP (Internet Exchange Point)** vicino alle reti di accesso → minore complessità. Esempio: **Limelight**.

**Flusso di accesso CDN (esempio KingCDN):**
1. Bob richiede `http://video.netcinema.com/6Y7B23V` dalla pagina web.
2. Il browser risolve `video.netcinema.com` tramite il DNS locale.
3. Il DNS autoritativo di `netcinema.com` restituisce un **CNAME**: `netcinema.KingCDN.com`.
4. Il DNS autoritativo di `KingCDN.com` restituisce l'indirizzo IP del **nodo CDN più vicino** al DNS locale di Bob.
5. Bob richiede il video direttamente al server KingCDN → trasmesso in streaming via HTTP/DASH.

I nodi CDN operano tipicamente come **web cache** (recuperano dall'origin server i dati mancanti) o ricevono contenuti **precaricati**.

> [\!info] OTT (Over The Top)
> Lo streaming video CDN è un esempio di servizio **OTT**: comunicazione tra host come servizio, implementata interamente a livello applicazione sopra l'infrastruttura Internet esistente. Le sfide OTT includono: quale contenuto inserire in quale nodo CDN, da quale nodo recuperare, a quale velocità adattarsi.

---

**Prossimo argomento:** [[03 - Livello di Trasporto]] — TCP, UDP, controllo di flusso e controllo della congestione.
