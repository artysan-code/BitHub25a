---
tags:
  - programmazione-web
  - http
slide:
  - "PW00-Introduzione.pdf"
  - "PW01-Internet e HTML.pdf"
  - "PW04-WebServer-Url.pdf"
  - "PW46-Express-rest-v2.pdf"
  - "PW32-Fetch-Async-CORS.pdf"
  - "PW35-Express.pdf"
---
# Internet, Web e HTTP
Questa nota apre il corso: prima di scrivere una riga di HTML, CSS o JavaScript bisogna capire **come funziona il Web su cui gireranno le applicazioni**. Si parte dall'architettura full stack del corso (Browser ⇔ Server ⇔ Storage), si passa per il modello client-server e l'indirizzamento delle risorse (URI, URL, DNS), e si arriva al protocollo che fa girare tutto: **HTTP**. Questi concetti sono la base teorica su cui si costruiscono sia il progetto (frontend che parla con un backend Express via HTTP) sia buona parte delle domande del test a risposta multipla.
## Applicazioni web e architettura full stack
Una **web application** è un'applicazione accessibile tramite browser: è un'estensione delle pagine web che, sfruttando la rete, offre servizi dinamici senza richiedere l'installazione di programmi aggiuntivi. Esempi tipici sono *Google Workspace* (docs, drive, mail: accesso universale via browser, collaborazione in tempo reale), *Trello* (gestione progetti con bacheche e schede) e *Doctolib* (prenotazioni sanitarie, telemedicina). In tutti questi casi i dati dell'utente non stanno sul suo dispositivo ma **nella rete**.
Rispetto a un'app nativa (installata da uno store, legata a un sistema operativo, aggiornata dall'utente), una web app gira direttamente nel browser, non richiede installazione, è immediatamente fruibile su qualunque dispositivo compatibile e viene aggiornata **una sola volta lato server**, senza coinvolgere l'utente. Questo porta i vantaggi tipici delle web app: **scalabilità** (si adattano a più utenti), **aggiornamenti centralizzati**, **sicurezza dei dati** (restano su server protetti) e **flessibilità** (accesso da PC, tablet, smartphone).
Il corso descrive questa architettura come **full stack**, cioè composta da tre macro-livelli che comunicano tra loro:

> [!info] Full Stack Web Architecture
> - **Browser** (Chrome, Firefox, Safari...): interpreta HTML/CSS/JavaScript e mostra l'interfaccia all'utente.
> - **Server web** (es. Node.js, nginx): riceve le richieste del browser, esegue la logica applicativa e produce le risposte.
> - **Storage** (es. MongoDB, MySQL): conserva i dati in modo persistente.
>
> Il browser parla con il server usando il protocollo **HTTP**; il server parla con lo storage tramite la rete interna (**Network**). Le slide introduttive la esemplificano con lo stack MEVN (MongoDB, Express, Vue, Node), ma il principio — client, server applicativo, base dati — vale per qualunque tecnologia si scelga.

> [!warning] MEVN nelle slide introduttive vs requisiti del progetto d'esame
> Le slide di apertura (`PW00-Introduzione.pdf`) presentano lo stack **MEVN** come esempio concreto dell'architettura full stack. Le regole d'esame A.A. 2025/26 (`Materiale Didattico/Esami/PW-Esame-2026.pdf`) però non richiedono né Vue né MongoDB: il backend obbligatorio è **Node.js + Express**, il frontend richiesto è **JavaScript "vanilla"** (senza framework SPA, con manipolazione diretta del DOM), e i dati possono stare in memoria, in un file JSON o in un database leggero — MongoDB è solo una delle opzioni facoltative per la persistenza. Il principio architetturale (Browser ⇔ Server applicativo ⇔ Storage) resta comunque valido qualunque tecnologia si scelga.

Coerentemente con questa suddivisione, il codice di una web app si divide in due parti:
- **Frontend (lato client)**: eseguito sul dispositivo dell'utente, gestisce interfaccia e interazioni (HTML, CSS, JavaScript, eventualmente framework come React, Angular, Vue).
- **Backend (lato server)**: eseguito sul server remoto, gestisce dati e logica applicativa, tipicamente esponendo un'**API** invece di un'interfaccia utente.
## Il modello client-server
Il **modello client-server** è il modello di progettazione software alla base di (quasi) tutte le applicazioni web: suddivide l'applicazione in due parti, il **client** e il **server**, con una regola semplice — il client fa le richieste, il server risponde.

> [!quote] Definizione — Client-side e Server-side
> **Client (client-side)**: applicazione eseguita sul computer dell'utente finale. Fornisce l'interfaccia utente (UI) e gestisce l'interazione con l'utente; può usare risorse locali del dispositivo (memoria temporanea, archiviazione locale).
> **Server (server-side)**: applicazione che riceve le richieste dai client e contiene la logica per restituire i dati appropriati. Espone di solito un'**interfaccia di programmazione (API)** anziché un'interfaccia utente, e spesso include un database per la persistenza dei dati.

**HTTP** è il protocollo che fa da ponte in questa comunicazione: regola lo scambio di dati fra client e server, e ogni azione dell'utente (una prenotazione, il caricamento di un referto, un click su un link) si traduce in una o più richieste HTTP.

> [!example] Esempio di interazione
> 1. Il paziente accede al portale sanitario.
> 2. Il client (il browser) invia una richiesta al server.
> 3. Il server recupera i dati (tipicamente da un database) e restituisce una risposta.
> 4. Il browser visualizza i risultati.
>
> Questo modello è alla base di quasi tutte le web app: dal fascicolo sanitario elettronico a un e-commerce.

Il server è il **punto centrale** di elaborazione, memorizzazione e logica applicativa: i client possono interagire con esso in modo **sincrono** (in tempo reale) o **asincrono** (in momenti diversi), mantenendo comunque coerenti i dati. I client, dal canto loro, possono essere eterogenei — browser, app mobile, software desktop, dispositivi IoT — e ciascuno può ricevere un'interfaccia adattata alla propria piattaforma, pur parlando con lo stesso server.
## Risorse statiche e dinamiche
I contenuti che vediamo in una pagina web non stanno sul nostro dispositivo: sono ospitati su **server web**, computer dedicati che archiviano e distribuiscono risorse digitali. Queste risorse sono di due tipi:
- **File statici**: contenuti sempre uguali per tutti gli utenti (es. un'immagine, un foglio di stile).
- **Contenuti dinamici**: generati in tempo reale al momento della richiesta, personalizzati in base all'utente, ai dati di un database o all'interazione (es. il risultato di una ricerca, il saldo di un conto).

Le web app moderne combinano sistematicamente risorse statiche (HTML, CSS, immagini, script) e contenuti dinamici (dati recuperati da un'API o da un database).
## URI e URL: anatomia di un indirizzo
Per poter richiedere una risorsa al server, serve un modo univoco di identificarla e localizzarla in rete.

> [!quote] Definizione — URI (Uniform Resource Identifier)
> Identificatore univoco per una risorsa sul Web, come un indirizzo postale: dice **cosa** cercare (e, in alcuni casi, anche dove trovarlo). Non è legato a un solo protocollo.

Alcuni esempi di URI, ciascuno con uno schema diverso:

| URI | Significato |
|---|---|
| `mailto:info@ospedalesanita.it` | Indirizzo email |
| `urn:isbn:978-88-123-4567-0` | Identifica un libro tramite ISBN, senza dire dove trovarlo |
| `ftp://ftp.esempio.it/immagini/banner.png` | Risorsa accessibile via protocollo FTP |
| `http://www.laboratoriomedico.it/referti/12345.pdf` | Può essere sia URI (identifica il referto) sia URL (dice anche dove/come recuperarlo) |

> [!quote] Definizione — URL (Uniform Resource Locator)
> Il tipo più comune di URI: specifica **dove** si trova una risorsa e **come** accedervi. È un identificatore per la posizione di un documento in rete.

Una URL come `https://www.domain-name.com` si scompone in parti ben precise:

> [!info] Anatomia di una URL
> ```text
> https://blog.domain-name.com/articoli/pw?ordine=data#introduzione
> └─┬──┘   └──┬──┘└─────┬─────┘└─────┬───┘└─────┬─────┘└─────┬─────┘
>  schema  sub-domain  domain      path       query      fragment
>                        + TLD
> ```
> - **Schema/protocollo** (`https`): il protocollo da usare per accedere alla risorsa.
> - **Host**: identifica il server, ed è a sua volta composto da **sub-domain** (es. `blog`, spesso `www`), **domain name** (`domain-name`) e **top-level domain/TLD** (`.com`). Sub-domain + domain + TLD insieme formano l'host; domain + TLD è il **root domain**, quello che si registra presso un registrar.
> - **Path** (`/articoli/pw`): la posizione della risorsa all'interno del server, con la stessa convenzione delle cartelle Unix (separatore `/`).
>
> *(extra, non da slide)* Una URL completa può avere anche:
> - **Porta** (es. `:8080`, subito dopo l'host): il "canale" su cui il server ascolta; se omessa, si usa la porta di default del protocollo (80 per HTTP, 443 per HTTPS).
> - **Query string** (`?ordine=data`): coppie chiave-valore introdotte da `?` e separate da `&`, usate per passare parametri al server (es. filtri, ricerche, paginazione).
> - **Fragment** (`#introduzione`): riferimento a una sezione interna della risorsa, gestito lato browser (non viene inviato al server).

> [!question] Domanda tipica d'esame
> Data una URL, saper individuare protocollo, host e path è la base minima richiesta. Occhio a non confondere il **root domain** (`dominio.it`, quello che si registra) con il singolo **sub-domain** (`www.dominio.it` è solo uno dei possibili sotto-domini di `dominio.it`).
## Server web: root, path e tipi di URL
Un **server web** è un computer — più precisamente un programma, il server web vero e proprio — che risponde a richieste di documenti: aspetta una richiesta, cerca il documento richiesto e lo invia al richiedente. Per farlo deve "parlare" HTTP, per questo viene spesso chiamato **server HTTP**. Qualunque computer può diventare un server web installando il software adatto: i più diffusi sono **Apache** e **nginx**.
Ogni server ha una **root**: la cartella principale da cui vengono servite tutte le risorse. Quando si digita una URL senza percorso (es. `www.miosito.it`), il browser richiede al server il **file di default della root**, che per convenzione si chiama `index.html`. Il **path** di una URL indica la posizione di una risorsa relativamente alla root, e ogni livello del path corrisponde a una sottocartella sul server.

> [!example] Avviare un server web locale
> Per esercitarsi senza un server "vero" si può avviare un server statico locale con Node.js (approfondito in [[08 - Node.js e npm]]):
> ```bash
> npx http-server
> ```
> Il comando serve la cartella corrente (la sua root) sulla porta di default (`8080`, a seconda della versione anche `8000`); dal browser si accede con `http://127.0.0.1:8080` oppure `http://localhost:8080`.

Le URL che scriviamo nelle pagine (per esempio nell'attributo `href` di un link o `src` di un'immagine) possono essere di tre tipi:

| Tipo | Esempio | Quando usarla |
|---|---|---|
| **Assoluta** | `http://www.miosito.com/about.html` | La risorsa è su un server **diverso** da quello della pagina corrente (link esterno): serve l'indirizzo completo. |
| **Relativa alla pagina** | `about.html` oppure `privacy/privacy.html` | Risorsa nello stesso server, path calcolato rispetto alla posizione del file attuale. |
| **Relativa alla root** | `/about.html` oppure `/privacy/privacy.html` | Risorsa nello stesso server, path calcolato a partire dalla root (inizia sempre con `/`). |

> [!warning] Stesso dominio non vuol dire stesso server
> `web.uniroma2.it` e `ppl.eln.uniroma2.it` sono **due server diversi**, anche se "sembrano" dello stesso sito: hanno sub-domain differenti. Per collegarsi a una risorsa su un server diverso da quello della pagina corrente servono sempre **URL assolute**; per link interni allo stesso server si può omettere protocollo e host e usare solo il path.
## Il percorso di una richiesta
Digitare un indirizzo nella barra del browser e premere invio sembra un'azione istantanea, ma dietro le quinte succedono diversi passaggi:
1. **Inserimento dell'indirizzo web** da parte dell'utente.
2. **Risoluzione del dominio**: il nome a dominio viene tradotto nell'indirizzo IP del server tramite il DNS (vedi sezione successiva).
3. **Invio della richiesta al server**: il browser apre una connessione con il server e invia una richiesta HTTP; il server la riceve e recupera il file (o i dati) desiderati.
4. **Risposta del server**: il server invia una risposta HTTP con il contenuto richiesto (HTML, immagini, CSS, script, ecc.).
5. **Rendering**: il browser interpreta il codice HTML e "renderizza" la pagina, rendendola navigabile per l'utente.

Un aspetto spesso sottovalutato: le risorse che compongono una pagina sono **fisicamente sparse per il mondo**. Chiedere `google.com` da un browser in Italia può voler dire raggiungere un server dall'altra parte dell'oceano: la latenza di questo percorso fisico è uno dei motivi per cui il DNS e i browser usano intensamente la cache.
Una singola pagina, inoltre, richiede quasi sempre **più risorse separate**, ciascuna con la propria richiesta HTTP: il browser scarica prima il documento HTML, poi — leggendolo — scopre di dover richiedere anche il foglio di stile CSS e le immagini referenziate, e le richiede a loro volta.

> [!example] Scambio file fra Browser e Server
> Per mostrare una pagina come `kitchen.html` (esempio del docente in `Materiale Didattico/Esempi/01 - kitchen/`) il browser fa in sequenza più richieste HTTP distinte:
> 1. `GET kitchen.html` → riceve la struttura della pagina.
> 2. `GET kitchen.css` → riceve lo stile, trovato come riferimento nell'HTML.
> 3. `GET foods.gif`, `GET spoon.gif` → riceve le immagini referenziate dall'HTML.
>
> Ogni file è quindi il risultato di una richiesta HTTP indipendente, anche se all'utente appare come un'unica pagina.
## DNS: Domain Name System
I computer non "capiscono" i nomi di dominio (`www.google.com`): comunicano solo tramite **indirizzi IP** (es. `173.194.34.87`). Il **DNS** (Domain Name System) è il sistema che traduce i nomi di dominio in indirizzi IP, permettendo ai dispositivi di comunicare — esattamente come una rubrica telefonica collega un nome a un numero. Una volta noto l'indirizzo IP, il client può aprire una connessione (un *socket*) verso il server.
### Come funziona la risoluzione
1. L'utente digita un indirizzo nel browser (es. `www.google.com`).
2. Il computer invia la richiesta a un **server DNS**.
3. Il server DNS cerca nel suo database di corrispondenze e restituisce l'indirizzo IP.
4. Il browser usa l'IP per connettersi al server web e caricare il sito.
### La struttura gerarchica del DNS
Il DNS è organizzato come un **albero gerarchico**, con la radice (`.`) al vertice, seguita dai **TLD** (Top-Level Domain, es. `.com`, `.org`, `.it`) e infine dai domini registrati sotto ciascun TLD (con i loro eventuali sottodomini).
I TLD si dividono in tre categorie:
- **Nazionali**: identificano paesi o territori, composti da due lettere secondo i codici ISO 3166 (`.it` Italia, `.fr` Francia, `.jp` Giappone).
- **Generici**: non associati a una nazione, rappresentano categorie o settori (`.com` originariamente commerciale, `.org` no-profit, `.net` infrastrutture di rete).
- **Infrastrutturali**: scopi tecnici legati all'infrastruttura di Internet; l'unico oggi è `.arpa`, usato per la risoluzione inversa degli indirizzi IP.

> [!quote] Definizione — Registry e Registrar
> **Registry**: l'organismo che gestisce un TLD e ne aggiorna i server (es. `registro.it` per `.it`, operato dal CNR).
> **Registrar**: aziende accreditate dal Registry che permettono all'utente finale di registrare un dominio (es. Aruba, Register.it, OVH).

> [!example] Il dominio miosito.it
> 1. **TLD**: `.it` — indica la zona geografica italiana.
> 2. **Registry**: `registro.it`, operato dal CNR (Consiglio Nazionale delle Ricerche) attraverso l'Istituto di Informatica e Telematica di Pisa; tiene traccia di tutti i domini `.it` registrati.
> 3. **Registrar**: aziende come Aruba o OVH, accreditate dal Registro.it, presso cui l'utente registra effettivamente `miosito.it`.
### DNS come sistema distribuito
Il DNS è **distribuito** per scalabilità e resilienza: la risoluzione passa attraverso più livelli di server (**Root Server → TLD Server → server autoritativi**), dove ogni livello conosce solo il successivo. Questo garantisce affidabilità e prestazioni migliori rispetto a un unico database centrale.
La risoluzione completa di `miosito.it` segue questi passaggi:
1. Il browser controlla la **cache**: se ha già l'IP salvato, lo usa subito; altrimenti chiede al **resolver**.
2. Il resolver interroga i **Root Server**: "Chi gestisce `.it`?" → i Root Server rispondono con l'indirizzo dei TLD server di `.it`.
3. Il resolver interroga i **TLD Server** di `.it`: "Chi è il server autoritativo per `miosito.it`?" → risposta con l'indirizzo dei server autoritativi configurati dal registrar (es. `ns1.aruba.it`).
4. Il resolver interroga il **server autoritativo**: "Qual è l'IP di `www.miosito.it`?" → risposta con l'IP (es. `93.184.216.34`).
5. Il resolver restituisce l'IP al browser, che ora sa dove inviare la richiesta HTTP.

Tutti questi passaggi possono essere memorizzati in **cache** per un tempo determinato, il **TTL** (Time To Live), per evitare di ripetere l'intera catena di richieste ogni volta.

> [!info] Comandi utili per esplorare il DNS
> - `nslookup www.google.com` — interroga il DNS e mostra l'IP associato al dominio.
> - `dig www.miosito.it` — analogo più dettagliato di `nslookup`.
> - `dnschecker.org` — verifica la propagazione di un dominio da più località nel mondo.
## Internet e il World Wide Web
**Internet** è un sistema di dispositivi elettronici interconnessi: ogni computer ha un indirizzo **IP** (Internet Protocol, es. `160.80.180.186`) e chi è connesso alla rete può scambiare informazioni con chiunque altro.
Il **World Wide Web (WWW)** è uno dei modi — non l'unico — con cui queste informazioni possono essere condivise: è un insieme di pagine web e documenti collegati tra loro tramite collegamenti ipertestuali (**link**). Il protocollo principale con cui il Web scambia documenti è **HTTP** (HyperText Transfer Protocol).

> [!warning] Internet non è il Web
> **Internet** è l'infrastruttura di rete (dispositivi collegati, indirizzi IP, instradamento dei pacchetti). Il **Web** è un *servizio* che gira sopra Internet, basato su HTTP e ipertesto. Email, streaming video e giochi online usano Internet ma non sono "il Web". È un trabocchetto da test a risposta multipla: i due termini non sono sinonimi.

I software che fanno richieste HTTP ai server si chiamano **client web**: i più comuni sono i browser (Chrome, Firefox, Safari, Edge...). L'utente inserisce un indirizzo, il browser chiede il documento corrispondente al server (per esempio con una richiesta `GET page1.html`), il server lo spedisce e il browser lo mostra, potendo richiedere documenti di qualsiasi tipo (testo, immagini, video, audio, script). Dal lato opposto, come già visto, il **server web** è il programma che riceve queste richieste e le soddisfa: i due server più diffusi al mondo sono storicamente **Apache** e **nginx**.
### Un po' di storia
Il Web nasce nel **1989** al CERN di Ginevra: **Tim Berners-Lee**, insieme a Robert Cailliau, propone un sistema di gestione delle informazioni basato sull'ipertesto per collegare documenti fra loro, e nel **1991** crea il primo sito web. Nel 1992 nasce **NCSA Mosaic**, il primo browser grafico, che rende il Web accessibile "di massa".
Tre enti principali si occupano oggi della governance di Internet e del Web:

> [!info] Chi governa Internet e il Web
> - **IETF** (Internet Engineering Task Force): definisce gli standard dei protocolli Internet.
> - **ICANN** (Internet Corporation for Assigned Names and Numbers): decide l'assegnazione dei nomi a dominio di primo livello.
> - **W3C** (World Wide Web Consortium): definisce gli standard del Web (HTML, CSS...), fondato dallo stesso Tim Berners-Lee.
## Il ciclo richiesta/risposta HTTP
**HTTP** (HyperText Transfer Protocol) è il protocollo su cui si basa la comunicazione fra client e server nel Web: sia le richieste sia le risposte sono gestite tramite HTTP, e sono sempre i client (i browser, ma anche il codice JavaScript che esegue una `fetch`, approfondita in [[07 - JavaScript asincrono, Promise, fetch e CORS]]) a iniziare lo scambio.

> [!quote] Definizione — HTTP
> Protocollo di livello applicativo per lo scambio di documenti sul Web. Funziona a **richiesta/risposta**: il client invia una richiesta HTTP a un server, il server elabora la richiesta e restituisce una risposta HTTP. È **stateless**: ogni richiesta è indipendente dalle precedenti, il server non ricorda automaticamente nulla della richiesta precedente dello stesso client.

*(extra, non da slide)* Le slide del corso introducono HTTP come "il ponte della comunicazione" ma non dettagliano la struttura testuale di una richiesta/risposta: la sezione seguente la ricostruisce per completezza. Metodi, classi di status code, gli header `Accept`/`Content-Type` e il formato JSON sono invece trattati esplicitamente nelle slide sull'architettura REST (`PW46-Express-rest-v2.pdf`, `PW35-Express.pdf`) e vengono ripresi qui in chiave di protocollo generale, prima che [[09 - Express e API REST]] li applichi a un'API concreta.
### Struttura di una richiesta HTTP
Una richiesta HTTP è testo strutturato in tre parti: una **request line**, una serie di **header**, e un **body** opzionale.
```http
GET /referti/12345.pdf HTTP/1.1
Host: www.laboratoriomedico.it
Accept: application/pdf
User-Agent: Mozilla/5.0
```
- **Request line**: `METODO path versione-HTTP` — qui `GET`, il path della risorsa e la versione del protocollo.
- **Header**: coppie `Chiave: valore` con metadati sulla richiesta (chi la fa, cosa accetta come risposta, ecc.).
- **Body**: presente solo per alcuni metodi (tipicamente `POST`/`PUT`/`PATCH`), contiene i dati inviati al server.
### Struttura di una risposta HTTP
```http
HTTP/1.1 200 OK
Content-Type: application/pdf
Content-Length: 48213

<contenuto binario del file>
```
- **Status line**: `versione-HTTP status-code reason-phrase` — qui la versione, il codice `200` e la frase `OK`.
- **Header**: metadati sulla risposta (tipo e dimensione del contenuto, politiche di cache...).
- **Body**: il contenuto vero e proprio della risposta (HTML, JSON, un file, o nulla).

> [!question] Domanda tipica d'esame
> Una richiesta e una risposta HTTP hanno la **stessa struttura a tre parti** (riga iniziale, header, body): cambia solo cosa contiene la prima riga (metodo+path per la richiesta, status code per la risposta).
## Metodi HTTP
Il **metodo** (o verbo) HTTP indica l'azione che il client vuole compiere sulla risorsa indicata dal path.

| Metodo | Uso tipico | Ha un body? | Idempotente? |
|---|---|---|---|
| `GET` | Richiede/legge una risorsa | No | Sì |
| `POST` | Crea una nuova risorsa, o esegue un'azione | Sì | No |
| `PUT` | Sostituisce interamente una risorsa esistente | Sì | Sì |
| `PATCH` | Modifica parzialmente una risorsa | Sì | No (in generale) |
| `DELETE` | Elimina una risorsa | Di solito no | Sì |
| `HEAD` | Come `GET`, ma la risposta ha solo gli header (nessun body) | No | Sì |
| `OPTIONS` | Chiede quali metodi/header sono ammessi su una risorsa (usato anche dal *preflight* CORS, vedi [[#CORS: cenni]]) | No | Sì |

**Idempotente** significa che ripetere la stessa richiesta più volte produce lo stesso effetto di eseguirla una sola volta (es. cancellare due volte la stessa risorsa lascia il sistema nello stesso stato). `GET`, `PUT`, `DELETE` sono idempotenti; `POST` in generale no, perché ogni chiamata può creare una nuova risorsa. Come questi metodi si applicano alle quattro operazioni **CRUD** su una risorsa REST (`POST`→Create, `GET`→Read, `PUT`/`PATCH`→Update, `DELETE`→Delete) è approfondito in [[09 - Express e API REST#Dal CRUD ai metodi HTTP]].

> [!warning] Trabocchetto — GET non deve avere effetti collaterali
> Le slide sono nette su questo punto: **"GET deve solo recuperare dati, non modificarli"** (un `GET /addCustomer?name=Rossi` che crea una risorsa è l'esempio scorretto da evitare). `GET` non dovrebbe mai modificare lo stato del server, ed è per questo **idempotente**. Inoltre una richiesta `GET` normalmente **non ha un body**: eventuali parametri vanno nella query string della URL.
## Status code HTTP
Ogni risposta HTTP porta uno **status code**: un numero a tre cifre che indica l'esito della richiesta. La prima cifra individua la **classe**:

| Classe | Significato | Codici comuni |
|---|---|---|
| **1xx** | Informativo | `100 Continue` |
| **2xx** | Successo | `200 OK`, `201 Created`, `204 No Content` |
| **3xx** | Redirezione | `304 Not Modified` *(301/302: standard HTTP diffusi, non elencati esplicitamente nelle slide)* |
| **4xx** | Errore del client | `400 Bad Request`, `401 Unauthorized`, `403 Forbidden`, `404 Not Found`, `405 Method Not Allowed`, `422 Unprocessable Entity` |
| **5xx** | Errore del server | `500 Internal Server Error` *(502/503: standard HTTP diffusi, non elencati esplicitamente nelle slide)* |

Quali di questi codici usare in una risposta e come strutturarla in un'API REST — inclusi i casi d'uso di 401/403/422 e il formato JSend — è approfondito in [[09 - Express e API REST#Status code e formato delle risposte]].

> [!question] Domanda tipica d'esame
> Saper collocare uno status code nella classe giusta (es. "404 è un errore di quale classe?" → 4xx, errore del client) è un classico del test a risposta multipla; non serve sapere a memoria l'elenco completo, ma riconoscere i più comuni e la loro classe.
## Header HTTP
Gli header sono metadati, coppie `Chiave: valore`, che accompagnano richiesta e risposta. Le slide sull'architettura REST introducono la coppia più importante per negoziare il formato dei dati:

> [!quote] Definizione — Accept e Content-Type
> **`Accept`** (dal client verso il server): i formati di risposta che il client è disposto ad accettare, es. `Accept: application/json`. **`Content-Type`** (da chi invia un body, client o server): il formato del corpo della richiesta o della risposta, es. `Content-Type: application/json`. Formati comuni: `application/json`, `application/xml`, `text/plain`.

*(extra, non da slide)* Altri header ricorrenti, utili per leggere una richiesta/risposta reale nei **DevTools** (pannello Network), uno strumento fondamentale per il debug del progetto d'esame:

| Header | Dove si usa | Significato |
|---|---|---|
| `Host` | Richiesta | Dominio del server a cui ci si rivolge (obbligatorio da HTTP/1.1) |
| `User-Agent` | Richiesta | Identifica il client (browser, versione, sistema operativo) |
| `Authorization` | Richiesta | Credenziali di autenticazione (es. un token) |
| `Cookie` | Richiesta | Cookie inviati dal client, impostati in precedenza dal server |
| `Content-Length` | Risposta | Dimensione in byte del body |
| `Set-Cookie` | Risposta | Chiede al client di memorizzare un cookie |
| `Cache-Control` | Risposta | Direttive sulla cache del contenuto |
| `Location` | Risposta | URL di destinazione in una redirezione (3xx) o della risorsa appena creata (201) |
## JSON come formato di scambio
**JSON** (JavaScript Object Notation) è il formato più usato per scambiare dati strutturati tra client e server nelle applicazioni web moderne, al posto (o accanto) di HTML puro. È testo semplice, leggibile sia da umani sia da programmi, indipendente dal linguaggio di programmazione. Le slide sull'architettura REST ("JSON formatting") lo mostrano con un oggetto di esempio:
```json
{
  "id": 1,
  "name": "cerulean",
  "year": 2000,
  "color": "#98B2D1",
  "pantone_value": "15-4020"
}
```
*(extra, non da slide)* Regole di sintassi non dettagliate a lezione ma indispensabili per scrivere JSON valido: le chiavi sono sempre stringhe fra doppi apici, i valori possono essere stringhe, numeri, booleani, `null`, oggetti (`{}`) o array (`[]`); non sono ammessi commenti né virgole finali. Quando il body di una richiesta o risposta HTTP contiene JSON, l'header `Content-Type` deve valere `application/json` (vedi sopra). Come avvolgere questi dati in una busta coerente per un'intera API (lo standard **JSend**) è mostrato in [[09 - Express e API REST#Status code e formato delle risposte]].
## CORS: cenni
Per motivi di sicurezza il browser applica di default la **same-origin policy**: uno script non può leggere liberamente le risposte di richieste verso un'origine (schema + host + porta) diversa da quella della pagina che lo esegue. **CORS** (Cross-Origin Resource Sharing) è il meccanismo, introdotto nelle slide su fetch/AJAX, con cui un server autorizza esplicitamente, tramite header di risposta, l'accesso da origini esterne. Il meccanismo compare anche fra le funzionalità elencate per un server web locale (`http-server`, vedi [[#Server web: root, path e tipi di URL]]).
La logica completa — *simple request* contro richiesta di *preflight* con `OPTIONS`, header coinvolti, configurazione lato Express — è approfondita in [[07 - JavaScript asincrono, Promise, fetch e CORS#CORS]], dove si studia insieme a `fetch` e alle chiamate asincrone che più spesso incontrano problemi di CORS.
## Riferimenti
- `PW00-Introduzione.pdf` — schema Full Stack Web Architecture (Browser ⇔ Server ⇔ Storage).
- `PW01-Internet e HTML.pdf`, pp. 1-62 — web app, modello client-server, ciclo di comunicazione, percorso di una richiesta, URI/URL, DNS (pp. 25-36), Internet e WWW, client/server HTTP, nascita del Web (pp. 37-62). Le pagine successive (63 in poi) riguardano il markup HTML e sono trattate in [[02 - HTML semantico e form]].
- `PW04-WebServer-Url.pdf`, pp. 1-13 — server web locale (`http-server`), root e file di default, tipi di URL (assolute, relative alla pagina, relative alla root).
- `PW46-Express-rest-v2.pdf`, pp. 4-5, 13-16 — struttura della request (metodo, endpoint, header, body), "GET deve solo recuperare dati, non modificarli", status code HTTP, header Accept/Content-Type, JSON formatting (esempio `cerulean`). Il mapping CRUD/REST e l'uso dei codici in un'API sono approfonditi in [[09 - Express e API REST]].
- `PW32-Fetch-Async-CORS.pdf`, pp. 20-28 — same-origin policy, CORS, metodi ammessi in una simple request (GET/HEAD/POST). Il dettaglio è in [[07 - JavaScript asincrono, Promise, fetch e CORS]].
- `PW35-Express.pdf`, p. 29 — elenco completo dei metodi HTTP supportati da Express (incluse `head` e `options`).
- `Materiale Didattico/Esempi/01 - kitchen/` — esempio pratico di pagina composta da più richieste HTTP separate (HTML, CSS, immagini).
