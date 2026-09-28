---
tags:
  - programmazione-web
  - express
slide:
  - "PW35-Express.pdf"
  - "PW45-Express-base.pdf"
  - "PW46-Express-rest-v2.pdf"
  - "PW47-Forms-2.pdf"
---
# Express e API REST
Questa nota copre **Express**, il framework con cui in [[08 - Node.js e npm]] si costruisce il server, e lo stile architetturale **REST** con cui si progettano le sue rotte. È il cuore del backend del progetto d'esame: routing, middleware, parsing del body, file statici, gestione degli errori e le convenzioni per scrivere una API JSON coerente. La parte di rendering lato server con **EJS** e l'**autenticazione** sono trattate in [[10 - Server side rendering con EJS e autenticazione]].
## Cos'è Express e perché usarlo
Con solo il modulo nativo `http` di Node.js (visto in [[08 - Node.js e npm]]) scrivere un server richiede di analizzare manualmente `req.url` e `req.method`, gestire a mano ogni percorso con `if`/`else`, fare il parsing del body a byte e servire i file statici leggendoli da disco. Funziona, ma diventa rapidamente illeggibile appena le rotte crescono.

> [!quote] Definizione — Express
> **Express** è un framework **minimale** per Node.js che semplifica la scrittura di applicazioni web e API. Le slide lo riassumono con quattro funzionalità chiave: **routing** complesso, gestione di richiesta e risposta (`req`/`res`), **middleware** e *server side rendering*. Permette uno sviluppo rapido delle applicazioni, tipicamente organizzato secondo l'architettura **MVC** (Model-View-Controller): le **routes** ricevono la richiesta HTTP e la inoltrano al **controller** giusto, che legge/scrive i dati tramite i **models** e restituisce la risposta, eventualmente passando da una **view** (template) per generare HTML.

Express non sostituisce `http`: lo usa internamente, ma offre un'API dichiarativa sopra di esso.
## Installazione e applicazione minima
Express è un pacchetto **npm** come un altro (vedi [[08 - Node.js e npm]] per `npm install` e `package.json`):
```bash
npm install express
```
Una **app minima** (*basic app* nelle slide) crea l'istanza dell'applicazione, definisce una rotta e mette il server in ascolto su una porta:
```js
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  console.log('Request received');
  res.status(200).send('Hello from the server');
});

const port = 3000;
app.listen(port, () => {
  console.log(`App running on port ${port}`);
});
```
`express()` crea l'oggetto `app`; `app.listen(port, callback)` avvia il server. Da qui in poi tutta la logica dell'applicazione si costruisce aggiungendo **rotte** e **middleware** ad `app`.
## Routing
> [!quote] Definizione — Routing
> Il **routing** è il modo in cui un'applicazione risponde alle richieste HTTP su determinati percorsi (**URL**, detti anche *path*) con **metodi** specifici (GET, POST, ecc.).

Express espone un metodo per ogni verbo HTTP: `app.get(path, callback)`, `app.post(path, callback)`, `app.put(path, callback)`, `app.patch(path, callback)`, `app.delete(path, callback)` (e altri più rari come `head`, `options`, oltre a verbi WebDAV/HTTP estesi come `checkout`, `copy`, `lock`, `merge`, `purge`, `search`). `req` e `res` sono gli oggetti della richiesta e della risposta passati alla callback.
```js
app.get('/about', (req, res) => {
  res.send('Pagina About');
});

app.post('/about', (req, res) => {
  res.status(201).send('Risorsa creata');
});
```
Le stringhe come `'/'` o `'/about'` sono percorsi **statici**. Sulle rotte valgono tre regole importanti:
- sono **case-sensitive**: `/about` ≠ `/About`;
- sono **order-sensitive**: Express le valuta nell'ordine in cui sono scritte nel codice e usa la **prima** che corrisponde;
- un array di funzioni callback (*multiple handlers*) può gestire la stessa rotta: ognuna deve chiamare `next()` tranne l'ultima, che invia la risposta.
```js
const cb0 = (req, res, next) => { console.log('CB0'); next(); };
const cb1 = (req, res, next) => { console.log('CB1'); next(); };
const cb2 = (req, res) => { res.send('Hello from C!'); };
app.get('/example/c', [cb0, cb1, cb2]);
```
È anche possibile concatenare più metodi sullo stesso percorso con `app.route()`, per evitare di ripetere il path:
```js
app.route('/book')
  .get((req, res) => res.send('Get a random book'))
  .post((req, res) => res.send('Add a book'))
  .put((req, res) => res.send('Update the book'));
```
`app.all(path, callback)` risponde invece a **qualsiasi** metodo HTTP su quel percorso, tipicamente per logica trasversale (es. un log o un controllo d'accesso) prima di passare alla rotta specifica con `next()`:
```js
app.all('/secret', (req, res, next) => {
  console.log('Accessing the secret section ...');
  next(); // passa il controllo all'handler successivo
});
```

> [!warning] Ordine delle rotte e percorsi dinamici
> Se una rotta con **parametro** (es. `/:post`) è dichiarata **prima** di una rotta statica con lo stesso prefisso (es. `/page`), la rotta parametrica intercetta anche `/page`, perché `:post` corrisponde a qualsiasi segmento. La regola pratica: le rotte più **specifiche** (statiche) vanno dichiarate **prima** di quelle più generiche (parametriche o wildcard `*`).

> [!question] Domanda tipica d'esame
> Se scrivo `app.get('/:post', ...)` prima di `app.get('/page', ...)`, quale handler risponde a una richiesta su `/page`? Risposta: quello di `/:post`, perché Express valuta le rotte nell'ordine di dichiarazione e il parametro `:post` combacia anche con la stringa `page`.
### Parametri di rotta e query string
> [!quote] Definizione — Route parameters
> I **route parameters** (o **parametri dinamici**) sono segmenti della URL che fungono da **segnaposto** per valori variabili, indicati nel path con `:nome`. Si usano per creare rotte **dinamiche**.

```js
app.get('/users/:userId/books/:bookId', (req, res) => {
  res.send(req.params);
});
```
Una richiesta a `http://localhost:3000/users/34/books/8989` popola `req.params` con:
```json
{ "userId": "34", "bookId": "8989" }
```
Da notare che i valori in `req.params` sono sempre **stringhe**: se servono numeri vanno convertiti esplicitamente (es. `parseInt(req.params.id)`).

La **query string** è invece la parte della URL dopo il `?`, fatta di coppie `chiave=valore` separate da `&` (es. `/search?q=hello&lang=it`, come si vede confrontando GET e POST in [[#Ricevere un form lato server]]).

*(extra, non da slide)* Le slide mostrano solo il formato della query string nell'URL, non il codice Express che la legge: Express la fa il parsing automaticamente e la espone in `req.query`:
```js
// GET /search?q=hello&lang=it
app.get('/search', (req, res) => {
  console.log(req.query); // { q: 'hello', lang: 'it' }
});
```
La differenza pratica con `req.params`: i **parametri di rotta** identificano *quale* risorsa (es. l'id), la **query string** filtra o modifica *come* recuperarla (es. paginazione, ordinamento, ricerca) — utile per un extra come la ricerca lato server nel progetto d'esame.
## L'oggetto res
> [!quote] Definizione — Oggetto res
> `res` (*response*) rappresenta la **risposta HTTP** che l'applicazione invia al client.

| Metodo Express | Tipo di risposta | Descrizione |
|---|---|---|
| `res.send()` | testo / oggetto / buffer | Risposta generica, si adatta al tipo |
| `res.json()` | JSON | Risposta in formato JSON |
| `res.sendFile()` | file | Invia un file al client |
| `res.redirect()` | redirect HTTP | Reindirizza verso un altro URL |
| `res.status()` | imposta codice HTTP | Imposta lo stato della risposta |

```js
res.send('Ciao dal server!');           // testo
res.send('<h1>Homepage</h1>');          // HTML
res.json({ user: 'Mario', id: 42 });    // JSON
res.status(404).send('Pagina non trovata'); // status + testo
```
`res.status()` e `res.send()`/`res.json()` si **concatenano**: `res.status()` restituisce lo stesso oggetto `res`, quindi la seconda chiamata agisce sulla stessa risposta. Se non si chiama `res.status()`, Express usa **200** di default.

Per inviare un file (ad esempio una pagina HTML) si usa `res.sendFile()` con un percorso assoluto, tipicamente costruito con il modulo `path` di Node.js:
```js
const path = require('path');
app.get('/', (req, res) => {
  res.status(200).sendFile(path.join(__dirname, '/index.html'));
});
```
Gli **header HTTP** (visti anche in [[01 - Internet, Web e HTTP#Header HTTP]]) specificano il tipo di contenuto e permettono di inviare informazioni extra (token, CORS, cookie); si impostano con `res.set()`:
```js
res.set('Content-Type', 'text/plain');
res.send('Testo semplice');

res.set({ 'Content-Type': 'application/json', 'X-Powered-By': 'Express' });
res.send({ msg: 'Ok' });
```

> [!warning] Un solo invio per risposta
> Ogni richiesta può ricevere **una sola** risposta: chiamare due volte `res.send()`/`res.json()` sulla stessa `res` genera l'errore `Cannot set headers after they are sent`. È un errore frequente quando si dimentica un `return` dopo un `res.status(400)` dentro un `if` di validazione (vedi [[#Gestione degli errori]]).
## Middleware
> [!quote] Definizione — Middleware
> Un **middleware** è una funzione con accesso agli oggetti richiesta (`req`), risposta (`res`) e alla funzione successiva nella catena (`next`). Ogni richiesta HTTP attraversa uno **stack di middleware** in ordine: ciascuno può leggere o modificare `req`/`res`, terminare la richiesta inviando una risposta, oppure passare il controllo al middleware successivo chiamando `next()`.

Una richiesta tipica attraversa in sequenza logging, autenticazione, parsing del body, file statici e infine il routing dell'app, prima che parta la risposta:
```text
HTTP Request → Logging → User Auth → JSON Parsing → Static Files → App Routing → HTTP Response
```
Un **middleware custom** si registra con `app.use()`:
```js
app.use((req, res, next) => {
  console.log('Hello from the middleware!');
  next(); // senza next() la richiesta resta bloccata qui
});

app.use('/api', (req, res, next) => {
  console.log('This middleware handles the data route');
  next();
});
```
Se `app.use()` ha un primo argomento stringa, il middleware si applica solo alle richieste il cui path inizia con quel prefisso; altrimenti si applica a **tutte** le richieste.

> [!warning] Dimenticare next()
> Se un middleware non chiama `next()` e non invia una risposta, la richiesta resta **appesa** (il client aspetta indefinitamente, senza errori visibili lato server). È l'errore più comune con i middleware custom.

Oltre a quelli scritti a mano, si possono usare **middleware di terze parti**, installati via npm. Un esempio classico è **morgan**, che logga ogni richiesta HTTP in console:
```bash
npm install morgan
```
```js
const morgan = require('morgan');
app.use(morgan('dev'));
```
### express.json() e express.urlencoded()
Per default `req.body` è `undefined`: Express non fa il parsing del corpo della richiesta a meno che non si attivi il middleware adatto al formato dei dati inviati.
- **`express.json()`**: fa il parsing di un body con `Content-Type: application/json` (il caso tipico di una API REST chiamata da `fetch`, vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]]).
- **`express.urlencoded({ extended: true })`**: fa il parsing di un body `application/x-www-form-urlencoded`, cioè quello inviato da un `<form>` HTML classico (vedi [[#Ricevere un form lato server]]).
```js
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
```
Entrambi vanno registrati con `app.use()` **prima** delle rotte che leggono `req.body`, perché i middleware si eseguono in ordine.

> [!warning] req.body vuoto o undefined
> Se `req.body` risulta `undefined` (o le proprietà attese mancano), la causa quasi sempre è: middleware di parsing mancante, oppure registrato **dopo** la rotta invece che prima, oppure `Content-Type` della richiesta che non corrisponde al middleware usato (es. JSON inviato ma solo `express.urlencoded()` attivo).
### express.static e la cartella public
Per gestire i **file statici** — immagini, CSS, JavaScript lato client, pagine HTML — si usa il middleware integrato `express.static`, fornendogli la cartella che li contiene:
```js
app.use(express.static('public'));
app.use(express.static('images'));

// per servirli sotto un prefisso, es. /static/...
app.use('/static', express.static('public'));
```
Con `app.use(express.static('public'))`, un file `public/style.css` diventa raggiungibile all'URL `/style.css` (senza il prefisso `public` nell'URL). È la convenzione da seguire nel progetto d'esame per servire frontend statico (HTML/CSS/JS) dallo stesso server Express che espone anche le rotte `/api/...`.
## express.Router
> [!quote] Definizione — Router
> La classe `express.Router` crea handler di route **modulari** e **montabili**. Un'istanza `Router` è a tutti gli effetti un middleware e un sistema di routing completo; per questo si parla spesso di **"mini-app"**.

Un router si definisce in un file separato e si esporta con `module.exports`:
```js
// userModule.js
const express = require('express');
const userRouter = express.Router();

userRouter.get('/login', (req, res) => res.send('Login page'));
userRouter.get('/register', (req, res) => res.send('Register page'));
userRouter.get('/logout', (req, res) => res.send('Logout page'));

module.exports = userRouter;
```
e si **monta** sull'app principale con un prefisso:
```js
const userRouter = require('./userModule');
app.use('/users', userRouter);
// GET /users/login, GET /users/register, GET /users/logout
```
Il Router supporta anche `router.param(nome, callback)`, che esegue una funzione **prima** di ogni rotta che contiene quel parametro (utile per validare o precaricare una risorsa una sola volta):
```js
router.param('userId', (req, res, next, id) => {
  console.log('Eseguita per prima');
  next();
});
router.get('/user/:userId', (req, res) => {
  console.log('Eseguita dopo');
  res.end();
});
```
Spezzare le rotte in più Router (uno per risorsa: `usersRouter`, `productsRouter`, ecc.) è la struttura consigliata quando l'API del progetto d'esame cresce oltre poche rotte.
## Variabili d'ambiente e configurazione
Le **environment variable** permettono all'applicazione di comportarsi diversamente a seconda dell'ambiente (sviluppo, test, produzione), esternalizzando parametri come la porta HTTP, i percorsi dei file o le credenziali di un database, invece di scriverli fissi nel codice.
```bash
PORT=8626 node server.js
PORT=8626 NODE_ENV=development node server.js
```
```js
const port = process.env.PORT;
app.listen(port, () => console.log(`App running on port ${port}`));
```
Scrivere ogni variabile sulla riga di comando è scomodo: il pacchetto npm **dotenv** (usato negli esempi del docente, vedi `js6`) le legge da un file `.env` nella root del progetto e le carica in `process.env`:
```bash
# .env
PORT=8765
NODE_ENV=development
```
```js
const dotenv = require('dotenv');
dotenv.config();

console.log(process.env.PORT);
```

> [!warning] Il file .env non va committato
> Il file `.env` contiene tipicamente segreti (password, chiavi API) e va escluso da Git (vedi [[05 - Git e GitHub]]); si versiona invece un file di esempio (es. `.env.example`) senza valori reali.
## Gestione degli errori
Un'API deve segnalare in modo esplicito, tramite lo **status code**, se una richiesta ha avuto successo o meno (i codici sono ripresi in dettaglio in [[#Status code e formato delle risposte]]). Tre casi da gestire sempre in un'API REST:
- **404 — rotta o risorsa inesistente**: sia quando nessuna rotta dichiarata corrisponde al path richiesto, sia quando la rotta esiste ma l'id cercato non è presente nei dati (vedi il pattern completo in [[#Dal CRUD ai metodi HTTP]]).
```js
// nessuna rotta precedente ha già risposto: 404 di fallback
app.use((req, res) => {
  res.status(404).json({ status: 'fail', message: 'Risorsa non trovata' });
});
```
- **400 — errore di validazione**: dati mancanti o non validi nel body della richiesta (vedi l'esempio in [[#Ricevere un form lato server]] e nella [[#Esempio completo: mini API REST|mini API]] più sotto).
- **500 — errore interno del server**: un'eccezione imprevista nel codice del server. Va **evitato** quanto possibile e, se capita, loggato lato server senza esporre lo stack trace al client.

*(extra, non da slide)* Un pattern standard di Express per centralizzare la gestione degli errori è il **middleware di errore a 4 argomenti** `(err, req, res, next)`: se una callback di rotta chiama `next(err)` invece di gestire l'errore da sola, Express salta tutti i middleware normali e passa direttamente al primo middleware con questa firma, che va dichiarato **per ultimo**, dopo tutte le rotte:
```js
app.use((err, req, res, next) => {
  console.error(err);
  res.status(500).json({ status: 'error', message: 'Errore interno del server' });
});
```

> [!warning] 404 in fondo, sempre
> Il middleware di fallback per il 404 e quello di gestione errori vanno dichiarati **dopo tutte le altre rotte**: essendo l'ordine di dichiarazione a determinare quale handler risponde, se il 404 fosse dichiarato prima intercetterebbe ogni richiesta.
## Architettura REST
> [!quote] Definizione — REST
> **REST** (*REpresentational State Transfer*) è un insieme di **linee guida** o principi per la realizzazione di un'architettura di sistema — uno **stile architetturale**, non un sistema concreto né uno standard. I suoi principi: identificazione delle **risorse**, utilizzo esplicito dei **metodi HTTP**, risorse **autodescrittive**, collegamenti tra risorse, comunicazione **senza stato** (*stateless*).

Un'**API** è codice che permette a due software di comunicare tra loro; una **REST API** costruisce quella comunicazione usando HTTP come trasporto. È lo standard de facto per la leggerezza, la semplicità e la compatibilità con qualsiasi linguaggio (usata ad esempio da Google Maps, Spotify, Netflix, Amazon, Twitter, Uber).

Una richiesta REST è composta da tre elementi — **client** (chi fa la richiesta), **server** (chi controlla la risorsa), **resource** (il dato: JSON, testo, immagine) — e contiene **metodo HTTP**, **endpoint** (URL), **header** e **body**.
### Dal CRUD ai metodi HTTP
> [!quote] Definizione — CRUD
> **CRUD** è l'acronimo delle quattro operazioni di base su una risorsa: **C**reate, **R**ead (o *retrieve*), **U**pdate, **D**elete.

In un'architettura **non-REST** ("classica") le operazioni finiscono spesso tutte dietro **GET**, con il nome dell'azione nell'URL (`/addNewProduct`, `/getProduct`, `/updateProduct`, `/deleteProduct`). REST le fa corrispondere invece a **metodi HTTP** distinti su un'unica URL che identifica la **risorsa**:

| Metodo HTTP | Operazione CRUD | Descrizione |
|---|---|---|
| POST | Create | Crea una nuova risorsa |
| GET | Read | Ottiene una risorsa esistente |
| PUT | Update | Aggiorna una risorsa **sostituendola** interamente |
| PATCH | Update | Aggiorna **parzialmente** una risorsa |
| DELETE | Delete | Elimina una risorsa |

```text
POST   /products        → crea un nuovo prodotto
GET    /products/3      → legge il prodotto con id 3
PUT    /products/3      → sostituisce il prodotto 3
PATCH  /products/3      → aggiorna parzialmente il prodotto 3
DELETE /products/3      → elimina il prodotto 3

GET    /orders/4/products  → prodotti dell'ordine 4 (risorsa annidata)
GET    /users/9/orders     → ordini dell'utente 9
```

> [!warning] GET deve essere idempotente e senza effetti collaterali
> **GET** serve **solo a leggere**: non deve mai creare, modificare o cancellare dati (l'esempio scorretto `GET /addCustomer?name=Rossi` mescola lettura e scrittura). GET è inoltre **idempotente**: ripetere la stessa GET tante volte produce sempre lo stesso risultato, senza ulteriori effetti sul server. Per creare una risorsa si usa **POST**: `POST /customers` con `{ "name": "Rossi" }` nel body.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra **PUT** e **PATCH**? Risposta: **PUT** sostituisce **l'intera risorsa** con quella inviata nel body (se un campo manca, va perso); **PATCH** applica una modifica **parziale**, aggiornando solo i campi presenti nel body.

Il **CRUD sulla risorsa `products`** in Express, con risposte in formato **JSend** (vedi sotto), riassume tutti i verbi:
```js
// GET /api/v1/products — lista
app.get('/api/v1/products', (req, res) => {
  res.status(200).json({ status: 'success', data: { products } });
});

// GET /api/v1/products/:id — dettaglio
app.get('/api/v1/products/:id', (req, res) => {
  const prod = products.find(el => el.id == req.params.id);
  if (prod == undefined) {
    return res.status(404).json({ status: 'fail', message: 'ID non trovato' });
  }
  res.status(200).json({ status: 'success', data: { product: prod } });
});

// POST /api/v1/products — crea
app.post('/api/v1/products', (req, res) => {
  const newId = products[products.length - 1].id + 1;
  const newProd = Object.assign({ id: newId }, req.body);
  products.push(newProd);
  res.status(201).json({ status: 'success', data: { product: newProd } });
});

// PATCH /api/v1/products/:id — aggiorna
app.patch('/api/v1/products/:id', (req, res) => {
  const prod = products.find(el => el.id == req.params.id);
  if (prod == undefined) {
    return res.status(404).json({ status: 'fail', message: 'ID non trovato' });
  }
  Object.assign(prod, req.body); // update...
  res.status(200).json({ status: 'success', data: { product: prod } });
});

// DELETE /api/v1/products/:id — elimina
app.delete('/api/v1/products/:id', (req, res) => {
  const index = products.findIndex(el => el.id == req.params.id);
  if (index === -1) {
    return res.status(404).json({ status: 'fail', message: 'ID non trovato' });
  }
  products.splice(index, 1);
  res.status(204).json({ status: 'success', data: null });
});
```
### Status code e formato delle risposte
Gli status code più usati in un'API REST (ripresi da [[01 - Internet, Web e HTTP#Status code HTTP]]):

| Codice | Significato |
|---|---|
| 200 | OK — tutto bene |
| 201 | OK — è stata creata una nuova risorsa |
| 204 | OK — la risorsa è stata cancellata con successo |
| 304 | Not Modified — i dati non sono cambiati, il client può usare quelli in cache |
| 400 | Bad Request — richiesta non valida (l'errore esatto va spiegato nel payload, es. "il JSON non è valido") |
| 401 | Unauthorized — la richiesta richiede autenticazione |
| 403 | Forbidden — il server ha capito la richiesta, ma in base ai permessi del richiedente l'accesso non è consentito |
| 404 | Not Found — nessuna risorsa dietro l'URI richiesto |
| 422 | Unprocessable Entity — il server non può elaborare l'entità (es. un'immagine non formattabile o campi obbligatori mancanti nel payload) |
| 500 | Internal Server Error — errore lato server, da evitare; se capita, lo stack trace va loggato e mai esposto al client |

> [!warning] 201 vs 204: quando c'è un body e quando no
> **201 Created** si usa dopo una **POST** riuscita e restituisce nel body la risorsa appena creata. **204 No Content** si usa tipicamente dopo una **DELETE** riuscita e **non ha body**: il client sa che l'operazione è andata a buon fine ma non riceve dati da leggere. Anche se il codice passa un oggetto a `res.status(204).json(...)`, come nell'esempio CRUD sopra, Express non lo invia: con 204 il body viene sempre scartato.

Client e server si accordano sul **formato** dei dati tramite gli header **Accept** (il client indica cosa accetta, es. `Accept: application/json`) e **Content-Type** (chi invia un body, client o server, ne indica il formato, es. `Content-Type: application/json`).

Una risposta JSON "grezza" espone solo i dati:
```json
{ "id": 1, "name": "cerulean", "year": 2000 }
```
mentre uno **standard di formattazione** come **JSend** avvolge sempre i dati in una busta con `status` e `data`, rendendo il formato delle risposte **coerente** in tutta l'API:
```json
{
  "status": "success",
  "data": { "id": 1, "name": "cerulean", "year": 2000 }
}
```
In caso di errore lo stesso formato si adatta con `status: "fail"` (errore del client, es. 400/404) e un campo `message`, come negli esempi di CRUD sopra. Altri formati esistono (JSON:API, OData JSON Protocol) ma sono più complessi; JSend è quello adottato nelle slide del corso per la sua semplicità.
### Naming delle rotte, CORS e stateless
Le API REST espongono tipicamente un unico **entry point** (es. `/api/v1/`), sotto cui si organizzano le **collezioni** (risorse) secondo uno schema gerarchico e prevedibile:

| URL | Descrizione |
|---|---|
| `/api` | punto di ingresso dell'API |
| `/api/:coll` | una collezione di primo livello (es. `/api/products`) |
| `/api/:coll/:id` | una risorsa specifica dentro la collezione |
| `/api/:coll/:id/:subcoll` | una sotto-collezione della risorsa |
| `/api/:coll/:id/:subcoll/:subid` | una risorsa dentro la sotto-collezione |

> [!warning] Evitare URL ambigue o opache
> Nomi come `/getProduct` o `/updateData` sono **ambigui**: ripetono nel path un'informazione che appartiene già al metodo HTTP. Le rotte vanno nominate sui **sostantivi** (le risorse, es. `/products`), lasciando il verbo dell'operazione al metodo HTTP.

Non tutti i metodi HTTP hanno senso a ogni livello di una risorsa: la **collezione** (es. `/books`) supporta `GET` (lista) e `POST` (crea un nuovo elemento), mentre il **singolo elemento** (es. `/books/145`) supporta `GET`, `PUT` e `DELETE` ma non `POST`, perché creare una risorsa già esistente non ha senso:

| Risorsa | GET | POST | PUT | DELETE |
|---|---|---|---|---|
| `/books` | lista di libri | crea un nuovo libro | aggiorna tutti i libri | elimina tutti i libri |
| `/books/145` | un libro specifico | **metodo non consentito (405)** | aggiorna un libro specifico | elimina un libro specifico |

> [!warning] 405 Method Not Allowed
> Chiamare `POST /books/145` deve rispondere **405**, non 404: la rotta e la risorsa esistono, ma quel metodo non è ammesso su una risorsa già identificata da un id.

REST richiede comunicazione **stateless**: il server non deve ricordare richieste precedenti per rispondere a quella corrente. Ogni richiesta deve portare con sé tutta l'informazione necessaria (es. il numero di pagina nella query string `?page=1`, o il token di autenticazione a ogni chiamata, vedi [[10 - Server side rendering con EJS e autenticazione]]) invece di affidarsi a uno stato conservato lato server tra una richiesta e l'altra.

Poiché un'API REST viene tipicamente chiamata via `fetch` da un frontend che gira su un'origine diversa (porta o dominio diverso dal server Express), entra in gioco il **CORS**, spiegato in dettaglio in [[07 - JavaScript asincrono, Promise, fetch e CORS#CORS]]. In Express si abilita con il middleware di terze parti `cors`:
```bash
npm install cors
```
```js
const cors = require('cors');
app.use(cors());
```
## Ricevere un form lato server
Un `<form>` HTML (costruito come visto in [[02 - HTML semantico e form]]) invia i dati con `method="POST"` codificati come `application/x-www-form-urlencoded` (vedi [[#express.json() e express.urlencoded()]] per il middleware che li legge in `req.body`):
```js
app.use(express.urlencoded({ extended: true }));

app.post('/contatto', (req, res) => {
  console.log(req.body); // { nome: '...', email: '...', messaggio: '...' }
  res.send('Messaggio ricevuto!');
});
```
La **validazione HTML5** lato client (attributi come `required`, `type="email"`, `minlength`) migliora l'esperienza utente ma **non sostituisce** la validazione lato server: un client malevolo o senza JavaScript può inviare comunque una richiesta con dati mancanti o non validi, quindi il server deve **ricontrollare** tutto:
```js
app.use(express.urlencoded({ extended: true }));
app.use(express.static('public')); // serve la pagina con il form

app.post('/contatto', (req, res) => {
  const { nome, email, messaggio } = req.body;
  if (!nome || !email || !messaggio) {
    return res.status(400).send('Tutti i campi sono obbligatori');
  }
  // qui: salva nel DB, invia email, ecc.
  console.log({ nome, email, messaggio });
  res.redirect('/grazie');
});
```
`res.redirect(url)` invia una risposta di redirect HTTP che fa navigare il browser verso un'altra pagina — utile dopo un form HTML tradizionale (diversamente da una API JSON, dove di norma si risponde con `res.json()` invece di un redirect).

> [!info] GET vs POST per i form
> **GET**: i dati finiscono nella URL (`/search?q=hello&lang=it`), sono visibili, salvabili nei preferiti e nella cache del browser — adatto a ricerche, filtri, navigazione. **POST**: i dati stanno nel **body** della richiesta, non visibili nella URL — più adatto a dati sensibili o che modificano lo stato del server: login, registrazione, form di contatto, upload.
## Esempio completo: mini API REST
Questo esempio riunisce routing, `express.json()`, parametri di rotta e validazione con 400, riproducendo i **requisiti minimi del progetto d'esame** per una risorsa (qui `corsi`, come nell'esempio del docente in `Materiale Didattico/Esempi/live/js6`): `GET /api/risorsa`, `GET /api/risorsa/:id`, `POST /api/risorsa` con validazione.
```js
const express = require('express');
const app = express();

app.use(express.json());

let corsi = [
  { id: 1, nome: 'Programmazione Web', descrizione: 'Full stack con Node/Express' },
  { id: 2, nome: 'Basi di Dati', descrizione: 'Modello relazionale e SQL' },
];

// GET /api/corsi — lista tutta la risorsa
app.get('/api/corsi', (req, res) => {
  res.status(200).json({ status: 'success', data: { corsi } });
});

// GET /api/corsi/:id — un singolo corso
app.get('/api/corsi/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const corso = corsi.find(c => c.id === id);
  if (!corso) {
    return res.status(404).json({ status: 'fail', message: 'Corso non trovato' });
  }
  res.status(200).json({ status: 'success', data: { corso } });
});

// POST /api/corsi — crea un corso, con validazione
app.post('/api/corsi', (req, res) => {
  const { nome, descrizione } = req.body;
  if (!nome || typeof nome !== 'string' || nome.trim() === '') {
    return res.status(400).json({ status: 'fail', message: 'Il campo "nome" è obbligatorio' });
  }
  const newId = corsi.length > 0 ? corsi[corsi.length - 1].id + 1 : 1;
  const newCorso = { id: newId, nome, descrizione: descrizione || '' };
  corsi.push(newCorso);
  res.status(201).json({ status: 'success', data: { corso: newCorso } });
});

// 404 di fallback per qualunque altra rotta
app.use((req, res) => {
  res.status(404).json({ status: 'fail', message: 'Rotta non trovata' });
});

app.listen(3000, () => console.log('Server avviato su http://localhost:3000'));
```
Da verificare manualmente (con l'estensione *REST Client* di VS Code, come suggerito dalle slide, o con `curl`):
```http
GET http://localhost:3000/api/corsi

###
GET http://localhost:3000/api/corsi/1

###
POST http://localhost:3000/api/corsi
Content-Type: application/json

{ "nome": "Crittografia", "descrizione": "Teoria dei numeri e cifrari" }

###
POST http://localhost:3000/api/corsi
Content-Type: application/json

{ "descrizione": "manca il nome" }
```
L'ultima richiesta deve rispondere **400**, perché `nome` manca: è esattamente il caso di validazione lato server richiesto dal progetto. I `PUT`/`PATCH`/`DELETE` su `/api/corsi/:id` si estendono con lo stesso schema (`find`/`findIndex` + controllo 404) mostrato in [[#Dal CRUD ai metodi HTTP]].
## Riferimenti
- `Materiale Didattico/Slide/PW35-Express.pdf` — panoramica Express, app minima, routing, parametri, static files, JSON/POST, architettura REST, CRUD, JSend, stateless, middleware, router, MVC, variabili d'ambiente.
- `Materiale Didattico/Slide/PW45-Express-base.pdf` — routing con stringhe, route parameters, oggetto `res`, header HTTP, middleware, static files, router, variabili d'ambiente (in gran parte sovrapposto a PW35, unito senza ripetizioni).
- `Materiale Didattico/Slide/PW46-Express-rest-v2.pdf` — architettura REST, elementi della request, status code (incluso 401/403/422), Accept/Content-Type, entry point e struttura delle URL, CRUD in Express.
- `Materiale Didattico/Slide/PW47-Forms-2.pdf`, pagine 8-10 (parte lato server: `express.urlencoded`, `req.body`, validazione e 400); la parte HTML del form è in [[02 - HTML semantico e form]].
- `Materiale Didattico/Esempi/live/js4` — app minima con `app.get`.
- `Materiale Didattico/Esempi/live/js5` — middleware (`cors`, `morgan`, custom), `express.static`, `express.json`, parametri di rotta, `express.Router` (`userModule.js`).
- `Materiale Didattico/Esempi/live/js6` — CRUD completo su una risorsa (`corsi`) con `express.json`, `dotenv`, persistenza su file JSON, status code 200/201/204/404.
