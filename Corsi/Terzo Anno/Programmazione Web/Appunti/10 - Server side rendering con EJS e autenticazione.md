---
tags:
  - programmazione-web
  - express
slide:
  - "PW47-Express-ejs.pdf"
  - "PW48-Auth-login-token.pdf"
---
# Server side rendering con EJS e autenticazione
Questa nota copre due argomenti che nel progetto d'esame sono **extra facoltativi** (non obbligatori per la sufficienza, ma da documentare bene se implementati): il **server side rendering** con il motore di template **EJS**, e l'**autenticazione** (login, sessioni, token e JWT, definiti nelle sezioni dedicate). Il resto del corso — le rotte REST che rispondono in JSON viste in [[09 - Express e API REST]] — resta l'architettura di base richiesta dal progetto; qui si aggiungono due modi per estenderla: generare HTML già pronto lato server invece di JSON, e proteggere alcune rotte dietro un login.
## SSR vs CSR: due modi di generare l'HTML
Finora, nel flusso visto in [[07 - JavaScript asincrono, Promise, fetch e CORS]], il server rispondeva con **JSON** e il browser costruiva l'HTML dinamicamente via `fetch` e manipolazione del DOM: questo si chiama **CSR (Client Side Rendering)**. Esiste un approccio alternativo, il **SSR (Server Side Rendering)**: il server genera l'**HTML completo** e lo invia già pronto al browser.

> [!quote] Definizione — SSR vs CSR
> **CSR**: JavaScript nel browser modifica dinamicamente il DOM a partire da dati (tipicamente JSON) ricevuti dal server. **SSR**: il server produce direttamente il documento HTML finale, prima di inviarlo al client.

> [!info] Confronto SSR vs CSR (fetch + API JSON)
>
> | | CSR (fetch + JSON, nota 07/09) | SSR (EJS) |
> |---|---|---|
> | Chi costruisce l'HTML | il browser, con JavaScript | il server |
> | Interattività | alta, interfacce dinamiche (es. social) | più limitata, ogni cambio richiede una richiesta *(extra, non da slide)* |
> | Prestazioni con molti dati | scarse con grandi volumi di dati | il server fa il lavoro una volta e invia il risultato *(extra, non da slide)* |
> | SEO (*Search Engine Optimization*, ottimizzazione di una pagina perché i motori di ricerca la trovino e la indicizzino bene *(definizione extra, non da slide)*) | più debole, i motori di ricerca devono eseguire JS *(extra, non da slide)* | ottimo (slide), l'HTML è già completo |
> | Casi d'uso tipici | app interattive (es. social); dashboard *(extra, non da slide)* | marketplace (Amazon, eBay…); siti di contenuto *(extra, non da slide)* |

Nessuno dei due approcci è "giusto" in assoluto: dipende da cosa deve fare l'applicazione. Un progetto può anche combinarli, ad esempio usando EJS per le pagine principali e `fetch` per aggiornare solo una parte della pagina senza ricaricarla.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra CSR e SSR? — Nel CSR il browser usa JavaScript per modificare dinamicamente il DOM (interfacce interattive, ma prestazioni scarse con grandi volumi di dati); nel SSR il server genera l'HTML completo prima di inviarlo (più semplice, ottimo per la SEO, usato nei marketplace come Amazon ed eBay).
## Il templating e i motori di template
> [!quote] Definizione — Templating
> Il **templating** è una tecnica che genera pagine web dinamiche combinando **codice HTML** con **codice (in questo caso JavaScript)** eseguito lato server: al posto di scrivere un file `.html` statico per ogni pagina, si scrive un **template** con dei "buchi" che vengono riempiti con dati diversi ad ogni richiesta.

I vantaggi principali del templating sono tre: **riduzione del codice duplicato** (header, footer e menu di navigazione non vanno riscritti in ogni pagina), **facilità di manutenzione** (una modifica a un componente comune si riflette automaticamente su tutte le pagine che lo usano) e **velocità di sviluppo** (ci si concentra sul contenuto specifico di ogni pagina, senza riscrivere il layout generale ogni volta).
**EJS (Embedded JavaScript Templates)** è un motore di template per Node.js che permette di inserire codice JavaScript direttamente dentro l'HTML. I file EJS hanno estensione `.ejs`. I suoi vantaggi, secondo le slide, sono di essere **leggero e veloce da configurare**, **ottimo per SSR semplice e immediato**, di integrarsi facilmente con **Express.js** e di non richiedere una configurazione complessa come i framework frontend (React, Vue).
## Configurazione di EJS in Express
Per usare EJS servono due istruzioni di configurazione su `app`: impostare EJS come **motore di rendering** (view engine) e indicare dove si trovano i file dei template (la cartella `views/`, per convenzione).

> [!example] Configurazione minima
> ```js
> const express = require('express');
> const app = express();
> const port = 3000;
> const path = require('path');
>
> app.set('view engine', 'ejs');
> app.set('views', path.join(__dirname, '/views'));
>
> app.get('/', (req, res) => {
>   res.render('homepage.ejs');
> });
>
> app.listen(port, () => {
>   console.log(`Server in esecuzione sulla porta ${port}`);
> });
> ```

- `app.set('view engine', 'ejs')`: dice a Express che i file `.ejs` vanno usati per generare HTML dinamico.
- `app.set('views', path.join(__dirname, '/views'))`: specifica la cartella `views/` come posizione in cui Express cerca i template.
- `res.render('homepage.ejs')`: quando l'utente visita `/`, il server **renderizza** la view `views/homepage.ejs` e ne invia l'HTML risultante come risposta. La slide PW47-Express-ejs (p. 5) è incoerente: il codice usa `res.render('homepage.ejs')`, ma il commento a lato parla di `index.ejs`; qui si usa `homepage.ejs`, coerente con il codice e con il file mostrato a p. 6.

Un file `.ejs` senza tag speciali è semplicemente HTML: ad esempio `views/homepage.ejs` può contenere una normale pagina `<!DOCTYPE html>...</html>` con dentro `<h1>Benvenuto su EJS in Node JS</h1>`. Diventa un template vero e proprio solo quando si aggiungono i tag EJS per inserire dati dinamici.
Per passare dei **dati** al template si usa il secondo argomento di `res.render`, un oggetto con le variabili da rendere disponibili dentro il file `.ejs`:

> [!example] Passare dati al render
> ```js
> res.render('esempio', {
>   utente: 'Mario',
>   messaggio: '<strong>Benvenuto!</strong>',
>   notifiche: 3
> });
> ```
> Dentro `views/esempio.ejs` le variabili `utente`, `messaggio` e `notifiche` sono usabili direttamente con i tag EJS visti nella prossima sezione.
## I tag di EJS
EJS distingue tra codice che **non produce output** (serve solo per il controllo di flusso) e codice che **produce output** da inserire nell'HTML. La differenza tra i due tag di output è cruciale per la sicurezza.

> [!info] Tabella dei tag EJS
>
> | Tag | Descrizione |
> |---|---|
> | `<% %>` | **Scriptlet**: controllo di flusso (`if`, `for`, `forEach`…), nessun output |
> | `<%- %>` | Output **non** HTML-escaped, per inserire HTML grezzo |
> | `<%= %>` | Output **HTML-escaped**, per sicurezza |
> | `<%# %>` | Commento: non viene eseguito né mostrato |
> | `<%%` | Stampa un simbolo `%` letterale |
> | `<%_ %>` | Slurping iniziale: rimuove tutti gli spazi prima del tag |
> | `<%_` | Trim-mode (newline slurp): rimuove il newline successivo |
> | `_%>` | Slurping finale: rimuove tutti gli spazi dopo il tag |
> | `%>` | Tag di chiusura normale |

> [!warning] Imprecisione della slide sul trim-mode
> La slide attribuisce il *trim-mode* (newline slurp) a `<%_`. *(extra, non da slide)* Nella documentazione di EJS il tag che rimuove il newline successivo è la chiusura **`-%>`**; `<%_` e `_%>` rimuovono gli spazi prima e dopo il tag. I tag di slurping servono solo a pulire l'HTML generato: per l'esame contano soprattutto `<% %>`, `<%= %>`, `<%- %>` e `<%# %>`.

> [!warning] `<%- %>` e rischio XSS
> *(extra, non da slide: le slide dicono solo «non HTML-escaped» e «HTML-escaped, per sicurezza»)* `<%= %>` fa l'**escaping** dei caratteri speciali (`<`, `>`, `&`…), quindi se il dato contiene HTML questo viene mostrato come testo puro, al sicuro. `<%- %>` inserisce invece l'HTML **così com'è**, senza escaping: se quel valore arriva (anche indirettamente) da un utente, un attaccante può iniettare `<script>` o altri tag e ottenere un **XSS (Cross-Site Scripting)**. `<%- %>` va usato solo con contenuto di cui ci si fida davvero (es. HTML generato dal server stesso), mai con input utente non sanificato.

> [!example] Scriptlet e output nello stesso file
> ```html
> <!-- <% %> Scriptlet: struttura di controllo -->
> <% if (notifiche > 0) { %>
>   <p>Hai <%= notifiche %> nuove notifiche.</p>
> <% } else { %>
>   <p>Nessuna nuova notifica.</p>
> <% } %>
>
> <!-- <%= %> Output HTML-escaped -->
> <p>Utente: <%= utente %></p>
>
> <!-- <%- %> Output non HTML-escaped -->
> <p><%- messaggio %></p>
> ```
> Con i dati passati nell'esempio precedente (`messaggio: '<strong>Benvenuto!</strong>'`), `<%= messaggio %>` stamperebbe il testo letterale `<strong>Benvenuto!</strong>`, mentre `<%- messaggio %>` produce un vero tag `<strong>` in grassetto: qui è voluto perché il messaggio non arriva da un utente esterno.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra `<%= %>` e `<%- %>` in EJS? — `<%= %>` stampa il valore facendo escaping dei caratteri HTML (sicuro contro XSS); `<%- %>` lo stampa senza escaping, inserendo HTML grezzo (rischio XSS se il dato non è fidato).
## Cicli e condizioni nei template
Dentro uno scriptlet `<% %>` si può scrivere codice JavaScript qualsiasi, incluso un ciclo su un array: è il modo con cui EJS genera liste di elementi ripetuti a partire da dati dinamici (esattamente come farebbe `.map()` o un ciclo `for` lato client, ma eseguito sul server prima di inviare l'HTML).

> [!example] Ciclo su un array di prodotti
> ```js
> const products = [
>   { name: 'Laptop', price: 75000 },
>   { name: 'Smartphone', price: 40000 },
>   { name: 'Tablet', price: 25000 }
> ];
> ```
> ```html
> <ul>
>   <% products.forEach(product => { %>
>     <li><%= product.name %>: ₹<%= product.price %></li>
>   <% }) %>
> </ul>
> ```
> Per ogni prodotto nell'array, EJS stampa una riga `<li>Laptop: ₹75000</li>`, `<li>Smartphone: ₹40000</li>`, `<li>Tablet: ₹25000</li>`. Da notare: `<% %>` (senza `=`) apre e chiude il `forEach` senza stampare nulla, mentre `<%= %>` dentro il ciclo stampa il valore di ogni proprietà del prodotto.
## Partial: riuso dei blocchi HTML
Per evitare di ripetere header, footer o menu di navigazione identici in più pagine, EJS permette di estrarli in un file separato — un **partial** — e di **includerlo** dentro le altre view. Per convenzione i partial si mettono in una sottocartella dedicata, ad esempio `views/partials/`.

> [!example] Partial di header incluso in due pagine
> Struttura delle view:
> ```text
> views/
> ├── partials/
> │   └── header.ejs
> ├── products.ejs
> └── contact.ejs
> ```
> `views/partials/header.ejs`:
> ```html
> <header>
>   <h1>My Shop</h1>
>   <nav>
>     <a href="/products">Products</a> |
>     <a href="/contact">Contact</a>
>   </nav>
>   <hr>
> </header>
> ```
> `views/products.ejs` (e allo stesso modo `contact.ejs`, che contiene `<title>Contact Us</title>`, `<h2>Contact Us</h2>` e `<p>Email: info@myshop.com</p>`) include il partial invece di riscriverlo:
> ```html
> <body>
>   <% include partials/header %>
>   <h2>Our Products</h2>
>   <ul>
>     <% products.forEach(product => { %>
>       <li><%= product.name %>: ₹<%= product.price %></li>
>     <% }) %>
>   </ul>
> </body>
> ```

> [!warning] `<% include %>` è sintassi obsoleta
> *(extra, non da slide)* L'esempio delle slide usa la sintassi storica `<% include partials/header %>`, ma le versioni recenti del pacchetto npm `ejs` (dalla 3.x) l'hanno rimossa: l'`include` va scritto come funzione, con il nome del partial tra virgolette e parentesi e il tag non-escaped, `<%- include('partials/header') %>` (si usa `<%-` e non `<%=` perché l'HTML del partial va inserito così com'è, non escaped). Copiando l'esempio delle slide così com'è, EJS restituisce un errore di sintassi: questa è la forma da usare per farlo funzionare davvero.

> [!question] Domanda tipica d'esame
> A cosa servono il templating e i partial in EJS? — Il templating combina HTML e codice JavaScript per generare pagine dinamiche; i partial (es. `views/partials/header.ejs`) estraggono le parti comuni (header, footer, menu) in un file incluso nelle altre view, così si riduce il codice duplicato, si facilita la manutenzione (una modifica si riflette su tutte le pagine) e si accelera lo sviluppo.
## Autenticazione vs autorizzazione
Con EJS si possono già costruire pagine dinamiche; per costruire un'area riservata (es. un profilo utente) serve anche sapere **chi** sta facendo la richiesta, ed è qui che entra l'autenticazione.

L'obiettivo della lezione (PW48 p. 1-2) è capire il giro completo **login → token → fetch → middleware**: (1) l'utente invia email e password a Express da un form; (2) `POST /login`: il backend verifica e risponde con `{ token }` se le credenziali sono valide; (3) il client usa `Authorization: Bearer <token>` ([[#Token, API key e Bearer]]), e le route protette controllano il token prima di rispondere ([[#Il middleware che protegge le rotte]]).

> [!quote] Definizione — Autenticazione vs Autorizzazione
> **Autenticazione (Authentication)**: risponde alla domanda *"chi sei?"*. Esempio: email e password dimostrano che sei `mario@example.com`. **Autorizzazione (Authorization)**: risponde alla domanda *"cosa puoi fare?"*. Esempio: puoi leggere `/api/profile`, ma non i dati di altri utenti.

In sintesi: il **login** è autenticazione; l'**accesso** (concesso o negato) a una specifica risorsa dell'API è autorizzazione. Le due cose sono legate ma distinte: si può essere autenticati (login riuscito) e comunque non autorizzati a una particolare azione.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra autenticazione e autorizzazione? — L'autenticazione risponde a «chi sei?» (email e password dimostrano che sei `mario@example.com`; il login è autenticazione); l'autorizzazione risponde a «cosa puoi fare?» (puoi leggere `/api/profile`, ma non i dati di altri utenti; l'accesso alle API è autorizzazione).
## HTTP è stateless: il problema da risolvere
> [!info] HTTP è stateless
> Come già visto in [[01 - Internet, Web e HTTP]], ogni richiesta HTTP è indipendente dalle altre: il server **non ricorda automaticamente** chi ha effettuato il login in una richiesta precedente. Se un client fa `GET /api/profile`, il server (Express) non ha di per sé modo di sapere chi sta chiedendo: ogni richiesta deve portare con sé una **prova** di chi la sta facendo.

Questa prova può essere di due tipi: una **sessione** (identificata da un cookie) oppure un **token**. Le prossime sezioni coprono entrambi.
## Sessioni e cookie
Con l'approccio a **sessione**, il server crea e mantiene uno stato lato server associato a un identificativo che viene dato al browser tramite un **cookie**.

> [!info] Sessione, API key, token: tre meccanismi diversi
>
> | | Sessione + cookie | API key | Bearer token (vedi [[#Token, API key e Bearer]]) |
> |---|---|---|---|
> | Cosa fa | il server crea una sessione, il browser rimanda automaticamente il cookie | identifica un'app o un progetto | il server lo emette dopo il login |
> | Identifica un utente? | sì, tramite la sessione *(extra, non da slide)* | non bene, non identifica un singolo utente | sì *(extra, non da slide)*, viene usato per proteggere le API |

Il flusso di una sessione è: (1) l'utente fa **login**, (2) il server risponde con un header `Set-Cookie`, (3) il browser salva il cookie e lo **rinvia automaticamente** ad ogni richiesta successiva verso lo stesso dominio. Il cookie in sé di norma contiene solo un identificativo (es. `sessionId=abc123`) e **non** i dati dell'utente (la slide dice che «non contiene per forza i dati utente»): è il server (*in memoria* *(extra, non da slide)*, oppure su un **session store**, cioè un archivio delle sessioni, come **Redis** o un database; la slide parla di «mappa salvata sul server o su Redis/DB») a mantenere la mappa `sessionId → utente`. **Redis** *(extra, non da slide)* è un database che tiene i dati in memoria, molto veloce, usato spesso come cache o come session store. Un middleware recupera la sessione dal cookie ricevuto e imposta qualcosa come `req.user`, così le rotte successive sanno chi ha fatto la richiesta.

> [!example] Sessioni in Express
> ```js
> app.use(session({
>   secret: 'una stringa segreta',
>   resave: false,
>   saveUninitialized: false
> }));
>
> app.post('/login', (req, res) => {
>   req.session.userId = user.id;
>   res.redirect('/profile');
> });
> ```
> Il client vede solo il cookie di sessione; è il server a ricordare cosa significa quel cookie (a quale utente corrisponde).

> [!warning] Frammento non eseguibile così com'è
> *(extra, non da slide)* Il blocco riproduce la slide (PW48 p. 8) ma non gira da solo: manca `const session = require('express-session');` (pacchetto da installare con `npm install express-session`), `user` non è definito (andrebbe cercato dopo aver verificato le credenziali) e manca `app.use(express.urlencoded({ extended: true }))` o `express.json()` per leggere il corpo del form in un login reale. Il blocco è stato provato con express-session 1.19.0, una volta definiti `require('express-session')` e `user = { id: 42 }`: `POST /login` risponde `302` con `Location: /profile` e `Set-Cookie: connect.sid=...; HttpOnly`, `GET /profile` con il cookie restituisce `userId` 42 e senza cookie `null`. `express.urlencoded()` o `express.json()` non servono a far girare il frammento, che non legge `req.body`; servono invece in un login reale, per leggere le credenziali inviate dal form.

> [!info] Attributi importanti del cookie
> `Set-Cookie: sid=abc123; HttpOnly; Secure; SameSite=Lax; Path=/`
>
> | Attributo | Effetto |
> |---|---|
> | `HttpOnly` | JavaScript nel browser non può leggere il cookie: protegge da furti via XSS |
> | `Secure` | il cookie viaggia solo su HTTPS |
> | `SameSite` | riduce gli invii cross-site del cookie e aiuta contro CSRF (*Cross-Site Request Forgery*: un sito malevolo induce il browser a inviare a un altro sito, insieme al cookie già salvato, una richiesta non voluta dall'utente *(definizione extra, non da slide)*) |

> [!question] Domanda tipica d'esame
> Cosa contiene il cookie di una sessione e dove sono i dati dell'utente? — Il cookie di norma contiene solo un identificativo (es. `sessionId=abc123`) e non i dati dell'utente; l'associazione sessione-utente (`abc123 → userId 42`) vive lato server, in una mappa salvata sul server o su Redis/DB. Il browser rinvia il cookie automaticamente ad ogni richiesta; con `HttpOnly` JavaScript non può leggerlo e con `Secure` viaggia solo su HTTPS.
## Dove salvare lo stato di login sul client
Se invece di un cookie automatico si usa un **token** (prossima sezione), il client deve decidere dove tenerlo tra una richiesta e l'altra.

> [!info] Cookie vs localStorage vs sessionStorage
>
> | | Cookie | localStorage | sessionStorage |
> |---|---|---|---|
> | Invio al server | automatico (slide: «inviato automaticamente dal browser») | manuale: va letto e messo in un header *(extra, non da slide)* | manuale, come localStorage *(extra, non da slide)* |
> | Leggibile da JavaScript | no se `HttpOnly` | sì | sì |
> | Durata | quella impostata nel cookie *(extra, non da slide)* | persiste finché non viene cancellato *(extra, non da slide)* | solo per la singola scheda/tab (slide: «dura per la singola tab») |
> | Esposizione a XSS | bassa con `HttpOnly` *(extra, non da slide)* | più esposto: comodo per demo, va discusso in produzione | stessa esposizione di localStorage *(extra, non da slide)* |

Per una demo didattica `localStorage` è comodo perché facile da usare con `fetch`; in un'applicazione reale la scelta va discussa insieme a XSS, cookie `HttpOnly` e HTTPS.

> [!question] Domanda tipica d'esame
> Dove si può salvare lo stato di login sul client e con quali differenze? — Nel cookie (inviato automaticamente dal browser, può essere `HttpOnly` e `Secure`, ottimo per le sessioni web), in `localStorage` (facile da usare con `fetch`, leggibile da JavaScript, comodo per una demo ma più esposto a XSS) o in `sessionStorage` (simile a `localStorage`, ma dura per la singola scheda, ed è sempre leggibile da JavaScript).
## Token, API key e Bearer
Il **Bearer token** è il meccanismo standard per proteggere le API: il client fa login una volta, riceve un token, e lo allega ad ogni richiesta successiva nell'header `Authorization`.

> [!example] Ottenere e usare un Bearer token
> ```http
> POST /login
> ```
> risponde con un token; da quel momento ogni richiesta protetta lo include così:
> ```http
> GET /api/me
> Authorization: Bearer eyJhbGciOiJIUzI1NiIs...
> ```

> [!info] Perché "Bearer"
> **Bearer** (letteralmente "chi lo porta") significa che **chiunque presenti** quel token viene accettato dal server, senza altre verifiche: per questo il token va protetto (*(extra, non da slide)* non esposto in URL, log o repository) e deve avere una **scadenza**, così un token rubato smette di funzionare dopo un certo tempo.

Un'**API key** è un meccanismo diverso: identifica un'applicazione o un progetto — può viaggiare nell'header `Authorization: ApiKey 1234567890abcdef` oppure in un header dedicato come `x-api-key: 1234567890abcdef` — non il login di un singolo utente, e non va mai pubblicata nel codice sorgente.
## JWT: struttura di un token
**JWT (JSON Web Token)** è uno dei formati più comuni per un Bearer token.

> [!quote] Definizione — JWT
> Un **JWT** è composto da tre parti separate da un punto: `header.payload.signature`. L'**header** descrive come il token è firmato (es. `{ alg: 'HS256' }`); il **payload** (il contenuto, cioè i dati trasportati dal token) contiene i dati minimi sull'utente (es. `{ sub: 42, exp: ... }`, dove, *(extra, non da slide)* `sub` è l'identificativo dell'utente ed `exp` la scadenza); la **signature** è una firma crittografica calcolata dal server, che permette di rilevare se il token è stato modificato.

> [!warning] JWT è codificato, non cifrato
> Header e payload di un JWT sono solo codificati in **Base64** *(extra, non da slide)* (una codifica reversibile da testo binario a testo, non una cifratura), **non cifrati** (slide: «codificato, non cifrato»): chiunque intercetti il token può leggerne il contenuto (basta decodificarlo, senza bisogno della chiave segreta). *(extra, non da slide)* La firma garantisce solo l'**integrità** (che non sia stato alterato), non la **confidenzialità**. Per questo un JWT non deve mai contenere password o altri dati sensibili nel payload.

> [!warning] Bearer non significa JWT
> **Bearer** è lo *schema di trasporto* del token: dice come viene inviato (`Authorization: Bearer <token>`) e chi porta il token può accedere. **JWT** è un possibile *formato* del token: un JWT contiene header, payload e firma, e il server può verificarlo autonomamente senza dover cercare una sessione salvata da qualche parte. Un Bearer token non deve necessariamente essere un JWT (*(extra, non da slide)* potrebbe essere una stringa opaca associata a un record nel database).

> [!question] Domanda tipica d'esame
> Bearer e JWT sono la stessa cosa? — No: Bearer è lo schema con cui il token viaggia nell'header `Authorization`; JWT è un formato specifico di token, auto-descrittivo e verificabile senza consultare una sessione salvata sul server.
## Il middleware che protegge le rotte
Il login da solo non "apre" tutte le API: ogni rotta protetta deve verificare il token ad ogni richiesta. In Express questo si fa con un **middleware** dedicato (il concetto di middleware è introdotto in [[09 - Express e API REST]]), applicato a tutte le rotte che richiedono autenticazione.

> [!example] Login e middleware `verifyToken`
> ```js
> app.post('/login', async (req, res) => {
>   const { email, password } = req.body;
>   const user = await findUserByEmail(email);
>   if (!user || !checkPassword(password, user))
>     return res.sendStatus(401);
>   const token = createToken({ sub: user.id });
>   res.json({ token });
> });
>
> function verifyToken(req, res, next) {
>   const auth = req.headers.authorization;
>   if (!auth?.startsWith('Bearer '))
>     return res.sendStatus(401);
>   req.user = jwt.verify(auth.slice(7), SECRET);
>   next();
> }
>
> app.get('/api/profile', verifyToken, handler);
> ```
> `verifyToken` legge l'header `Authorization`, controlla che inizi con `Bearer `, verifica il token e — se valido — imposta `req.user` e chiama `next()` per passare alla rotta vera e propria. Passandolo come secondo argomento di `app.get`, Express lo esegue **prima** dell'handler: se `verifyToken` risponde con `sendStatus(401)`, l'handler non viene mai chiamato.

> [!warning] Frammento non eseguibile così com'è
> *(extra, non da slide)* Il blocco riproduce le slide (PW48 p. 17-19) ma usa nomi mai definiti: `findUserByEmail`, `checkPassword`, `createToken`, `jwt` e `SECRET`. Inoltre `jwt.verify` **lancia un'eccezione** se il token è scaduto o alterato: in Express 5 l'errore di un middleware sincrono arriva al gestore di errori predefinito, che risponde `500` e non `401`. Per avere `401` l'eccezione va intercettata con `try/catch`, come nell'esempio seguente.

> [!example] Versione eseguibile con `jsonwebtoken` *(extra, non da slide)*
> Serve `npm install express jsonwebtoken`. L'utente è tenuto in memoria e la password in chiaro solo per brevità (vedi [[#Hashing delle password]]).
> ```js
> const express = require('express');
> const jwt = require('jsonwebtoken');
>
> const SECRET = 'segreto-di-prova';
> const utenti = [{ id: 42, email: 'mario@example.com', password: '1234' }];
>
> const app = express();
> app.use(express.json());
>
> app.post('/login', (req, res) => {
>   const { email, password } = req.body;
>   const user = utenti.find(u => u.email === email);
>   if (!user || user.password !== password) return res.sendStatus(401);
>   const token = jwt.sign({ sub: user.id }, SECRET, { expiresIn: '1h' });
>   res.json({ token });
> });
>
> function verifyToken(req, res, next) {
>   const auth = req.headers.authorization;
>   if (!auth?.startsWith('Bearer ')) return res.sendStatus(401);
>   try {
>     req.user = jwt.verify(auth.slice(7), SECRET);
>   } catch (err) {
>     return res.sendStatus(401);
>   }
>   next();
> }
>
> app.get('/api/profile', verifyToken, (req, res) => {
>   res.json({ id: req.user.sub });
> });
> ```
> Provato con Express 5.3.0 e `jsonwebtoken` 9.0.3: `POST /login` con credenziali corrette risponde `200` con `{ token }` (tre parti separate da punti); con password errata `401`; `GET /api/profile` senza header `401`, con token valido `200` e `{"id":42}`, con token alterato `401` (senza il `try/catch` sarebbe `500`). Il payload del token contiene `sub`, `iat` ed `exp`.

Il client, dal suo lato, chiama l'API protetta allegando il token salvato al login:

> [!example] Chiamare un'API protetta dal client
> ```js
> const token = localStorage.getItem('token');
> const res = await fetch('/api/profile', {
>   headers: { Authorization: `Bearer ${token}` }
> });
> ```

> [!question] Domanda tipica d'esame
> Cosa fa il middleware `verifyToken` e dove si applica? — Legge l'header `Authorization`, controlla che inizi con `Bearer `, verifica il token, imposta `req.user` e chiama `next()`; se il token manca risponde `401`. Si passa come argomento prima dell'handler (`app.get('/api/profile', verifyToken, handler)`) in tutte le rotte protette: il login da solo non apre le API, e le route protette usano tutte lo stesso middleware.
## Hashing delle password
*(extra, non da slide: le slide citano solo "password hash" tra i concetti della mini app finale, senza mostrare codice)* La funzione `checkPassword` dell'esempio precedente non deve confrontare la password in chiaro inviata dall'utente con una password salvata in chiaro nel database: se il database venisse compromesso, tutte le password sarebbero immediatamente leggibili. La pratica standard è **hashare** la password al momento della registrazione con una libreria come `bcrypt`, che applica un algoritmo di hash lento e con un *salt* casuale, e confrontare l'hash salvato con l'hash della password inserita al login (mai le password in chiaro). Anche se non dettagliata nelle slide di questo corso, questa è una nozione che l'esaminatore può chiedere per chi implementa l'autenticazione come extra nel progetto.
## Logout
Tra i concetti della mini app finale, le slide citano anche il **logout**, senza mostrare codice.

*(extra, non da slide)* Il logout funziona in modo diverso a seconda del meccanismo di autenticazione. Con le **sessioni** (vedi [[#Sessioni e cookie]]), il server può davvero "dimenticare" l'utente: la rotta di logout distrugge la sessione lato server (es. `req.session.destroy()`), e il cookie associato smette di corrispondere a qualcosa di valido, quindi le richieste successive non sono più riconosciute. Con un **token** stateless come il JWT, invece, il server non ha uno stato da cancellare: il token resta verificabile e valido fino alla sua scadenza (`exp`), quindi il "logout" lato client si riduce a **rimuovere il token salvato** (es. `localStorage.removeItem('token')`). Un token già copiato da un attaccante prima del logout resterebbe però utilizzabile fino alla scadenza naturale, a meno di implementare una lista di revoca lato server — argomento non trattato nelle slide di questo corso.
## 401 vs 403
Le slide di autenticazione usano solo `res.sendStatus(401)` per credenziali mancanti o non valide; i due codici sono però definiti nelle slide di REST (PW46 p. 13, vedi [[09 - Express e API REST#Status code e formato delle risposte]]) e corrispondono alla distinzione della sezione [[#Autenticazione vs autorizzazione]].

> [!info] 401 Unauthorized vs 403 Forbidden
>
> | Codice | Significato | Corrisponde a |
> |---|---|---|
> | **401 Unauthorized** | slide PW46: «la richiesta richiede una autenticazione dell'utente» (qui: token assente, scaduto o non valido) | fallimento di **autenticazione**: il server non sa chi sei *(associazione extra, non da slide)* |
> | **403 Forbidden** | slide PW46: «il server ha capito la richiesta, ma in base ai diritti del richiedente l'accesso non è consentito» (qui: utente autenticato senza i permessi per quella risorsa) | fallimento di **autorizzazione**: il server sa chi sei, ma non puoi farlo *(associazione extra, non da slide)* |

*(extra, non da slide: le definizioni dei due codici sono nelle slide PW46, l'associazione ad autenticazione e autorizzazione e l'esempio sono una deduzione)* Un errore comune è restituire sempre 401 anche quando l'utente è loggato ma sta provando ad accedere a dati di un altro utente: in quel caso il codice corretto è **403**, non 401.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra 401 e 403? — `401 Unauthorized`: la richiesta richiede un'autenticazione dell'utente (token o credenziali mancanti o non valide); `403 Forbidden`: il server ha capito la richiesta ma, in base ai diritti del richiedente, l'accesso non è consentito (utente autenticato, ma non autorizzato).
## Sessioni vs token: quale scegliere
> [!info] Quando usare sessione, Bearer token o JWT
>
> | | Sessione + cookie | Bearer token | JWT |
> |---|---|---|---|
> | Contesto tipico | app web tradizionale | API chiamate via `fetch` o da app/mobile | quando servono token firmati e autodescrittivi |
> | Chi gestisce l'invio | il browser gestisce i cookie automaticamente | il client decide quando inviare l'header `Authorization` | come il Bearer token |
> | Stato | il server mantiene lo stato (sessione salvata) | dipende dal formato del token *(extra, non da slide)* | il server può verificarlo senza cercare una sessione *(extra, non da slide)*; la slide avverte: attenzione a scadenza e revoca |

Le slide accennano infine a **OAuth** (login tramite Google, GitHub, ecc.) come argomento successivo: a differenza del login "fatto in casa" descritto qui, OAuth delega l'autenticazione a un provider esterno con un flusso più lungo; capire bene il meccanismo di login e token proprio è indicato come passo utile prima di affrontare OAuth.
## Il flusso di login completo (riepilogo)
Mettendo insieme tutti i pezzi, il flusso end-to-end di un login con token è:
1. **Form** di login: una pagina con campi email e password.
2. **`POST /login`**: il backend verifica le credenziali (confrontando l'**hash** della password, vedi [[#Hashing delle password]]) e, se valide, risponde con `{ token }`.
3. **Salvataggio del token** sul client (es. `localStorage` per una demo).
4. **`fetch` verso un'API protetta**, con l'header `Authorization: Bearer <token>`.
5. **Middleware `verifyToken`** sulla rotta protetta: se il token è valido imposta `req.user` e lascia passare la richiesta, altrimenti risponde `401`.

> [!question] Domanda tipica d'esame
> Cosa succede se una richiesta a `/api/profile` non porta l'header `Authorization`? — Il middleware `verifyToken` non trova un token `Bearer`, quindi risponde `401 Unauthorized` senza mai eseguire l'handler della rotta: il client non è nemmeno riconosciuto come autenticato.
## Riferimenti
- `PW47-Express-ejs.pdf`: SSR vs CSR (p. 2), templating ed EJS (p. 3-4), configurazione `app.set('view engine')`/`views` e file `.ejs` (p. 5-6), tag EJS ed esempio scriptlet/output (p. 7-8), loop EJS (p. 9), partial (p. 10).
- `PW48-Auth-login-token.pdf`: autenticazione vs autorizzazione (p. 1-3), HTTP stateless (p. 4), sessione/API key/token, cookie di sessione e dove salvare lo stato di login (p. 5-9), cookie `HttpOnly`/`Secure` e API key (p. 10-11), Bearer token e JWT (p. 12-15), flusso di login, `POST /login`, chiamata client e middleware `verifyToken` (p. 16-19), OAuth e mini app finale (p. 20-21).
- `Materiale Didattico/Esempi/live/js5/userModule.js`: router Express con le rotte `/login`, `/register` e `/logout` (solo segnaposto, senza EJS, hashing, sessioni o token): utile come traccia della struttura di un router di autenticazione.
