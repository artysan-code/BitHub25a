---
tags:
  - programmazione-web
  - node
slide:
  - "PW34-NodeJS.pdf"
---
# Node.js e npm
Fino a questo punto JavaScript viveva solo nel [[06 - JavaScript e DOM|browser]]: uno script poteva manipolare il DOM o fare `fetch` (vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]]), ma non poteva leggere un file dal disco o rispondere a una richiesta HTTP come [[01 - Internet, Web e HTTP|Web Server]]. **Node.js** rompe questo limite: porta JavaScript fuori dal browser, sul server. Questa nota copre il runtime, il sistema dei moduli e npm; il framework **Express**, costruito sopra al server HTTP nativo qui descritto, è nella nota successiva ([[09 - Express e API REST]]).
## Programmare il server: frontend, backend e tipi di sito
Prima di arrivare a Node, le slide ricostruiscono dove si colloca il codice lato server in un'applicazione web.
- Il **frontend** è ciò che gira nel **browser**: HTML, CSS e JavaScript, eventualmente con librerie e framework come Bootstrap, jQuery, Angular o React.
- Il **backend** è ciò che gira nel **Web Server**: un **HTTP Server** che risponde alle richieste, i **file** da servire, le **applicazioni** (*Apps*) che generano contenuti e il **database** (*DB*) da cui leggono i dati. Qui si usano tecnologie come PHP (con framework come CodeIgniter e Symfony), .NET, **Node.js**, database come MySQL, MariaDB e SQL Server, cache come Redis e Memcached, container come Docker.

Il modo in cui backend e frontend si dividono il lavoro è cambiato nel tempo, e le slide distinguono tre modelli.

> [!info] Siti statici, dinamici e API based
> | Modello | Cosa fa il Web Server | Chi costruisce la pagina |
> |---|---|---|
> | **Sito statico** | restituisce file HTML, CSS e JS già pronti, sempre uguali | nessuno: i file sono scritti a mano |
> | **Sito dinamico** | un **Site Builder** legge i dati dal **DB** e genera l'HTML a ogni richiesta | il **server** |
> | **API based** | espone una **JSON API**: legge il DB e restituisce solo **dati** in JSON | il **browser**, con JavaScript che riceve i dati e costruisce la pagina |

Il modello **API based** è quello del progetto d'esame: il backend Node/Express espone rotte che rispondono in JSON ([[09 - Express e API REST]]) e il frontend le chiama con `fetch` e aggiorna il DOM ([[07 - JavaScript asincrono, Promise, fetch e CORS]]). Il sito dinamico corrisponde invece al *server side rendering* della nota [[10 - Server side rendering con EJS e autenticazione]]. Nell'ultimo diagramma delle slide il **Site Builder** compare infatti accanto al **BROWSER** (non più nel Web Server), mentre nel Web Server resta la sola **JSON API** collegata al DB.

Le slide chiudono la parte introduttiva con le statistiche di W3Techs sui linguaggi di programmazione lato server (percentuale di siti che usano ciascun linguaggio; un sito può usare più di un linguaggio lato server).

> [!info] Tecnologie per backend: 2021 e 2026
> | Linguaggio | 23 maggio 2021 | 25 maggio 2026 |
> |---|---|---|
> | PHP | 79,2% | 71,2% |
> | ASP.NET | 8,6% | 4,3% |
> | Ruby | 4,7% | 6,8% |
> | Java | 3,5% | 5,4% |
> | Scala | 1,9% | 5,0% |
> | *static files* | 1,5% | 2,1% |
> | Python | 1,4% | 1,2% |
> | **JavaScript** | 1,3% | 6,4% |
> | ColdFusion | 0,3% | 0,2% |
> | Perl | 0,1% | 0,1% |
> | Erlang | 0,1% | — |
>
> PHP resta il linguaggio dominante, ma JavaScript (cioè Node.js) passa dall'1,3% al 6,4% dei siti. L'ultima slide di questa parte è un grafico delle *market positions* 2026 (siti ad alto o basso traffico contro siti che usano il linguaggio) con JavaScript, Java, Ruby, PHP e Scala.

> [!question] Domanda tipica d'esame
> In un'architettura **API based**, dove viene costruito l'HTML della pagina?
> Nel **browser**: il server restituisce solo dati in JSON, e il JavaScript del frontend li usa per costruire o aggiornare la pagina. In un sito dinamico classico, invece, l'HTML è generato dal server.
## Cos'è Node.js
Partiamo dalla definizione delle slide.

> [!quote] Definizione — Node.js
> **Node.js** è un **ambiente di runtime** per JavaScript costruito sopra il motore **V8** di Google Chrome. Fornisce un contesto in cui eseguire codice JavaScript su qualsiasi piattaforma dove Node è installato, tipicamente il **server**.

Prima di Node, V8 sapeva solo eseguire JavaScript dentro Chrome, con accesso al DOM e alle API del browser. Node prende lo stesso motore V8 e lo affianca a **libuv**, una libreria C che fornisce l'**event loop** e l'accesso **asincrono** a filesystem, rete e altre operazioni di I/O; ad altre librerie di sistema come `http-parser`, `zlib`, `OpenSSL` e `c-ares`. Il risultato è un ambiente dove si scrive JavaScript ma si può leggere un file, aprire una connessione di rete o creare un server HTTP.
La caratteristica chiave dell'architettura di Node è il modello **event-driven** e **non bloccante**: un server tradizionale multi-thread assegna un **thread** a ogni richiesta e, se il thread fa un'operazione di I/O bloccante (es. lettura da disco o da database), quel thread resta fermo ad aspettare — con un numero finito di thread, oltre una certa soglia le richieste in eccesso vengono rifiutate. Node.js invece ha un **event loop single-threaded**: le richieste entrano in una coda, il loop le processa una alla volta senza bloccarsi sulle operazioni di I/O (che vengono delegate a `libuv` e al suo pool di thread di sistema), e quando l'operazione è completata viene eseguita la relativa **callback**. Questo permette di gestire molte connessioni concorrenti con poche risorse, a patto di non eseguire codice JavaScript pesante in modo sincrono nell'event loop (bloccherebbe tutte le altre richieste).

> [!warning] Trabocchetto — Node non è "senza thread"
> Node.js esegue il *codice JavaScript* su un **singolo thread** (l'event loop), ma non è vero che tutto Node sia mono-thread: le operazioni di I/O bloccanti a basso livello vengono eseguite da `libuv` su un **pool di thread separato** (kernel threads), e i risultati tornano all'event loop come callback. Confondere "event loop single-threaded" con "Node è single-process senza altri thread" è un errore comune. *(L'ultima affermazione, a differenza del diagramma con i kernel threads, non è nelle slide: extra, non da slide.)*

> [!question] Domanda tipica d'esame
> **D:** Che cos'è Node.js?
> **R:** Un **ambiente di esecuzione** (runtime) per JavaScript, costruito sul motore V8 di Chrome, che permette di eseguire JavaScript anche **lato server** (e su qualsiasi piattaforma dove Node è installato). Non è un framework per pagine HTML, non sostituisce il linguaggio JavaScript e non è un database.
## JavaScript nel browser vs in Node.js
Le differenze principali fra i due ambienti sono riassunte qui. *(Extra, non da slide: la tabella è una sintesi; dalle slide derivano solo le variabili del modulo `require`, `module`, `exports`, `__filename`, `__dirname`, descritte nel paragrafo sul wrapping.)*

> [!info] Differenze principali
> | Browser | Node.js |
> |---|---|
> | Accesso al **DOM**, `window`, `document` | Nessun DOM: niente `window`/`document` |
> | Oggetto globale `window` | Oggetto globale `global` |
> | API browser (`fetch`, `localStorage`, eventi UI) | Moduli **core** (`fs`, `http`, `path`, …) |
> | Un solo script per pagina, caricato con `<script>` | Programma composto da più **moduli** (`require`/`import`) |
> | — | Variabili speciali del modulo: `__filename`, `__dirname`, `module`, `exports`, `require` |
> | — | Oggetto `process` (argomenti, variabili d'ambiente, uscita dal programma) |

Lo stesso linguaggio, JavaScript, gira quindi in due ambienti molto diversi: nel browser lo scopo tipico è manipolare l'interfaccia utente, in Node lo scopo tipico è gestire file, rete e logica di server. Il codice che usa `document.querySelector` non funziona in Node (non esiste il DOM), e viceversa `require('fs')` non esiste nel browser per motivi di sicurezza (una pagina web non deve poter leggere il filesystem del visitatore) *(extra, non da slide)*.
## REPL ed esecuzione di uno script
Una volta installato Node (da [nodejs.org](https://nodejs.org/), scegliendo la versione **LTS**, *Long Term Support*, cioè a supporto prolungato: è il pulsante "Download Node (LTS)" mostrato dalla slide *Installazione*), ci sono due modi per eseguire JavaScript da terminale: la **REPL** (*Read-Eval-Print Loop*), lanciata digitando `node` senza argomenti, che legge un'espressione alla volta, la esegue e ne stampa il risultato — utile per provare rapidamente una riga di codice *(la REPL non è nelle slide: extra, non da slide)*; oppure l'esecuzione di un file con `node nomefile.js`, il modo normale per lanciare un programma Node.

> [!example] Hello World in Node
> ```js
> // es1.js
> console.log('Hello World!!');
> ```
> ```bash
> node es1.js
> # Hello World!!
> ```
## Il sistema dei moduli
Un programma Node reale è diviso in più file: ogni file è un **modulo**, con il proprio spazio di nomi isolato (le variabili di un modulo non sono visibili automaticamente in un altro). Node distingue tre tipi di modulo secondo le slide: **Core Modules** (di sistema, installati insieme a Node), **Local Modules** (i file che scriviamo noi) e **Third Party Modules** (pacchetti esterni, da installare con npm: nell'esempio `js3` del docente sono `moment`, per formattare le date, e `dotenv`).

> [!quote] Definizione — CommonJS
> **CommonJS** è il sistema di moduli nativo e storico di Node.js: si importa con la funzione `require()` e si esporta assegnando a `module.exports` (o alle proprietà di `exports`).
> ```js
> // betterLog.js — modulo locale
> const debug = function (txt) {
>   console.log('DEBUG - ' + txt);
> };
> const error = function (txt) {
>   console.error('ERROR - ' + txt);
> };
> exports.debug = debug;
> exports.error = error;
> ```
> ```js
> // uso in un altro file
> const betterLog = require('./betterLog');
> betterLog.debug('avviato'); // DEBUG - avviato
> betterLog.error('file mancante'); // ERROR - file mancante
> ```

Un modulo può anche caricare dati e restituire funzioni che li usano, come nell'esempio delle slide che legge un file JSON e ne espone l'accesso:

```js
// lista.js
const fs = require('fs');
const data = JSON.parse(
  fs.readFileSync(`${__dirname}/data/data.json`, 'utf-8')
);
exports.getAll = function () {
  return JSON.stringify(data);
};
exports.getItem = function (index) {
  return JSON.stringify(data.find((el) => el.id == index));
};
```
```js
const { getAll, getItem } = require('./lista');
```

Quando si scrive `require('qualcosa')`, Node deve decidere *cosa* caricare: secondo le slide (**resolving and loading**) l'ordine è (1) se è un **Core Module** lo carica direttamente; (2) se il percorso inizia con `./` o `../` è un **Developer Module**: prima cerca lo script con quel nome esatto, poi — se è una cartella — il file `index.js` al suo interno; (3) altrimenti entra nella cartella `node_modules` e cerca gli **Installed Module**.

> [!warning] Trabocchetto — refuso delle slide su "modules_core"
> La slide "Resolving and loading" scrive che il terzo passo è "entra in **modules_core**" per cercare gli Installed Module: è un refuso del docente. La cartella dove npm installa davvero i pacchetti di terze parti è **`node_modules`** (lo stesso nome usato nella sezione su [[#npm: inizializzare un progetto e package.json|npm]]) — è questo il nome corretto da ricordare per l'esame, non "modules_core".

Tecnicamente, prima di essere eseguito ogni modulo viene "**wrappato**" in una funzione (una IIFE, *Immediately Invoked Function Expression*) che riceve automaticamente cinque parametri: `exports` (riferimento a `module.exports`; la slide *Wrapping* scrive `module.export` al singolare, un refuso), `require` (la funzione per importare altri moduli), `module` (riferimento all'oggetto del modulo corrente), `__filename` (percorso assoluto del file) e `__dirname` (percorso assoluto della cartella che lo contiene). Il codice del modulo viene eseguito una sola volta: `require` restituisce gli `exports`, e il risultato dell'esecuzione viene **messo in cache** — richieste successive dello stesso modulo restituiscono l'oggetto già calcolato, senza rieseguire il file (slide *Esecuzione, exports e caching*: "il risultato dell'esecuzione è cachato e ritornato alle esecuzioni successive del modulo").

Conseguenze della **module cache** *(extra, non da slide: la slide dice solo che il risultato dell'esecuzione è cachato)*: (1) il codice a livello top-level del modulo (per esempio un `console.log`) gira **una sola volta**, alla prima `require`; (2) tutte le `require` successive, anche da file diversi, restituiscono lo **stesso oggetto** (non una copia), quindi una modifica fatta tramite un riferimento si vede da tutti gli altri.

> [!example] Module cache: due `require` dello stesso modulo *(extra, non da slide: esempio costruito per questa nota)*
> ```js
> // stato.js
> console.log('stato.js eseguito');
> module.exports = { valore: 0 };
> ```
> ```js
> // main.js
> const primo = require('./stato');
> const secondo = require('./stato');
> primo.valore = 5;
> console.log(secondo.valore); // 5
> console.log(primo === secondo); // true
> ```
> L'output completo è `stato.js eseguito`, `5`, `true`: la prima riga compare **una volta sola**, anche se `require('./stato')` è chiamata due volte, e `secondo` è lo stesso oggetto di `primo`.

L'esempio del docente `Esempi/live/js3` mostra la stessa cosa: `oraVecchia.js` calcola l'ora (`const now = moment().format(...)`) e la stampa con `console.log('Ora vecchia: ...')` a livello top-level, poi esporta una funzione che restituisce `now`. Il modulo è richiesto più volte (da `index.js` e da `betterLog.js`, che contiene solo `require('./oraVecchia')`): la riga "Ora vecchia" compare **una sola volta**, e anche dopo `setTimeout(..., 10000)` la funzione restituisce ancora l'ora calcolata alla prima esecuzione, perché il modulo non viene rieseguito.

> [!info] ES Modules *(extra, non da slide)*
> Oltre a CommonJS, Node supporta anche gli **ES Modules** (`import`/`export`), lo stesso standard usato nel browser. Per attivarli in un progetto Node serve dichiarare `"type": "module"` nel `package.json`, oppure usare l'estensione `.mjs`. Le due sintassi non si mescolano liberamente nello stesso file: `require` non è disponibile nei moduli ES (esiste solo `import`), e `module.exports` non esiste (si usa `export`/`export default`). Gli esempi di questo corso (vedi `Esempi/live/js2`, `js3`) usano CommonJS, lo stile predefinito di Node e ancora il più diffuso nei progetti Express.

Per riconoscere a quale dei tre tipi appartiene un modulo basta guardare come viene richiesto e da dove proviene.

> [!question] Domanda tipica d'esame
> **D:** `stato.js` contiene `module.exports = { valore: 0 };`. Un file esegue `const primo = require("./stato"); const secondo = require("./stato"); primo.valore = 5; console.log(secondo.valore);`. Che cosa stampa?
> **R:** `5`. Node mette in **cache** il modulo alla prima `require`: `primo` e `secondo` sono lo **stesso oggetto**, quindi la modifica fatta con `primo` si vede anche con `secondo` (non `0`, non `undefined`, non un errore). *(extra, non da slide: domanda costruita per questa nota.)*

> [!question] Domanda tipica d'esame
> **D:** `config.js` contiene `console.log("config caricato"); module.exports = {};` e il file principale fa `require("./config")` due volte. Quante volte viene stampato "config caricato"?
> **R:** **Una sola volta**: il codice del modulo viene eseguito alla prima `require`; la seconda restituisce l'oggetto in cache. *(extra, non da slide: domanda costruita per questa nota.)*

> [!question] Domanda tipica d'esame
> **D:** In un modulo CommonJS, come si espone una funzione ad altri file?
> **R:** Assegnandola a `module.exports` (o a una proprietà di `exports`, es. `exports.nomeFunzione = ...`); il file che la importa la ottiene con `const x = require('./modulo')`.

> [!question] Domanda tipica d'esame
> **D:** Nel codice compaiono `require("fs")`, `require("./calcoli")` e `require("express")`. Di che tipo è ciascun modulo? Quale va installato con npm?
> **R:** `fs` è un **Core Module** (installato con Node); `./calcoli` è un **Local Module** (un file scritto da noi, riconoscibile dal percorso che inizia con `./`); `express` è un **Third Party Module** e va installato con npm (`npm i express`). I moduli core e quelli locali non si installano.
## Moduli core: fs, path, http
Le slide elencano i **Core Module** più usati: `http` (creare un server HTTP), `url` (parsing delle URL), `querystring` (parsing della query string), `path` (gestione dei percorsi di file in modo indipendente dal sistema operativo), `fs` (*file system*, I/O su file) e `util` (funzioni di utilità). Qui interessano in particolare `fs` e `http`; `path` viene usato tipicamente insieme a `fs` per costruire percorsi corretti (es. `path.join(__dirname, 'data')`) senza concatenare stringhe a mano *(l'esempio con `path.join` è extra, non da slide)*.
Nelle slide l'esempio *Esempio fs* (`es2.js`) mostra proprio le due versioni a confronto. Il modulo `fs` offre le stesse operazioni in due versioni: **sincrona** (il nome finisce in `Sync`, es. `readFileSync`) che blocca l'esecuzione finché l'operazione non è completata e restituisce il risultato direttamente; e **asincrona** (es. `readFile`) che non blocca, avvia l'operazione e la termina più avanti richiamando una **callback** `(err, data) => {...}`.

> [!example] Lettura di un file, sincrona e asincrona
> ```js
> // es2.js
> const fs = require('fs');
> // asincrona: non blocca, il risultato arriva nella callback
> fs.readFile('./data/input.txt', 'utf-8', (err, data) => {
>   console.log('Async');
>   console.log(data);
> });
> // sincrona: blocca finché il file non è letto
> const data = fs.readFileSync('./data/input.txt', 'utf-8');
> console.log(data);
> console.log('----\n');
> ```
> Con `data/input.txt` che contiene `contenuto del file`, l'output è: prima il contenuto letto in modo **sincrono** e la riga `----`; solo dopo, quando il file asincrono è stato letto e la callback viene eseguita, `Async` e di nuovo il contenuto.
> ```
> contenuto del file
> ----
>
> Async
> contenuto del file
> ```
> (Il file è supposto senza newline finale; la riga vuota dopo `----` viene da `\n` in `'----\n'`. Se il file termina con newline, compaiono una riga vuota in più prima di `----` e una in coda al contenuto.)
> Il punto dell'esempio è proprio l'ordine: la `readFile` asincrona è la prima istruzione, ma la sua callback arriva per ultima. Nell'esempio del docente (`Esempi/live/js2/es2.js`) la lettura asincrona gestisce anche l'errore (`if (err) { console.error(err); return; }`) e l'ultima riga è `console.log("Fine Script ES2!")`, che viene stampata **prima** del contenuto del file.

> [!warning] Trabocchetto — sync vs async in un server
> Usare le versioni `Sync` di `fs` dentro il codice che gestisce le richieste di un server è un errore frequente: bloccando l'event loop, **tutte** le altre richieste in arrivo restano in attesa finché la lettura sincrona non finisce. Le versioni sincrone vanno bene per script una tantum o per la fase di avvio del programma, non per il codice eseguito ad ogni richiesta.
## Server HTTP nativo con http.createServer
Il modulo `http` permette di creare un server web senza framework: `http.createServer` prende una funzione **handler**, chiamata una volta per ogni richiesta in arrivo, con due argomenti — `req` (la richiesta, con `req.url` e `req.method`) e `res` (la risposta, da costruire e chiudere con `res.end()`).

> [!example] Server HTTP minimo con routing manuale
> ```js
> const http = require('http');
> const server = http.createServer((req, res) => {
>   const pathName = req.url;
>   if (pathName === '/' || pathName === '/home') {
>     res.end('Home page');
>   } else if (pathName === '/contatti') {
>     res.end('Contatti');
>   } else {
>     res.writeHead(404, { 'Content-type': 'text/html' });
>     res.end('<h1>404 - Page Not found</h1>');
>   }
> });
> const port = 8000;
> server.listen(port, '127.0.0.1', () => {
>   console.log(`Server listening on port ${port}`);
> });
> ```

Nella slide originale il messaggio d'errore contiene un refuso del docente (`'<h1>404 - Page Not foud</h1>'`, senza la "n" di "found"): qui sopra è riportato corretto.
Questo `if`/`else if` su `req.url` è, secondo le slide, il **Routing**: *"determinare come un'applicazione risponde a una richiesta client a un endpoint particolare, il quale è un URI (o percorso) e un metodo di richiesta HTTP specifico (GET, POST e così via)"*. Con il modulo `http` nativo il routing va scritto a mano confrontando `req.url` (ed eventualmente `req.method`); `res.writeHead(status, headers)` imposta lo **status code** e gli header prima di chiudere la risposta con `res.end(body)` — se non si chiama `writeHead`, lo status di default è 200. La slide *Routing* mostra lo stesso handler con due rami in più, prima del 404 finale (il refuso `appilication/json` è nella slide):

```js
const pathName = req.url;
if (pathName === '/' || pathName === '/home') {
  res.end('Home page');
} else if (pathName === '/contatti') {
  res.end('Contatti');
} else if (pathName === '/info') {
  res.end('Info Page');
} else if (pathName === '/api') {
  res.writeHead(404, { 'Content-type': 'appilication/json' });
  res.end('Info Page');
} else {
  res.writeHead(404, { 'Content-type': 'text/html' });
  res.end('<h1>404 - Page Not found</h1>');
}
```

Provato con `curl`: `/info` risponde 200 `Info Page`; `/api` risponde **404** con `Content-type: appilication/json` e corpo `Info Page` (lo status 404 è quello impostato dal `writeHead`, probabilmente un'incompletezza dell'esempio); qualsiasi altro percorso risponde 404 con l'HTML `<h1>404 - Page Not found</h1>`. `http` si può anche usare per servire file dal disco combinandolo con `fs`, come nell'esempio del docente che legge il file richiesto e risponde 404 se non esiste (`Esempi/live/js2/es3.js`).
Scrivere manualmente ogni `if`/`else` sul path, gestire i metodi HTTP, il parsing del body JSON e i file statici diventa rapidamente scomodo: è esattamente il problema che risolve **Express**, il framework trattato in [[09 - Express e API REST]].
## npm: inizializzare un progetto e package.json
**npm** (*Node Package Manager*) è lo strumento a riga di comando per gestire i **Third Party Modules**: cercarli sul registro pubblico [npmjs.com](https://www.npmjs.com/), installarli, aggiornarli e definire gli script di avvio di un progetto. Un progetto Node comincia quasi sempre con `npm init` (o `npm init -y` per accettare tutti i valori di default *(extra, non da slide)*), che crea il file **`package.json`**.

> [!quote] Definizione — package.json
> Il **`package.json`** è il manifesto del progetto Node: descrive il pacchetto e le sue dipendenze. I campi principali sono:
> - `name`, `version`: nome e versione del pacchetto.
> - `main`: il file di entrata del modulo (es. `index.js`).
> - `scripts`: comandi eseguibili con `npm run <nome>` (vedi sezione successiva).
> - `dependencies`: pacchetti necessari **a runtime** (es. `express`).
> - `devDependencies`: pacchetti necessari solo **in sviluppo** (es. `nodemon`, descritto più avanti nella sezione dedicata), non richiesti quando l'app gira in produzione.

```json
{
  "name": "js4",
  "version": "1.0.0",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "dev": "nodemon index.js"
  },
  "dependencies": {
    "express": "^5.2.1"
  },
  "devDependencies": {
    "nodemon": "^3.1.14"
  }
}
```

Con `npm i <package>` (alias di `npm install`) un pacchetto viene scaricato e salvato dentro la cartella **`node_modules`**, aggiunto automaticamente a `dependencies` in `package.json`, e viene generato o aggiornato *(da qui in poi, fino alla fine del paragrafo, è extra, non da slide)* **`package-lock.json`**, che registra le versioni **esatte** installate (comprese quelle delle dipendenze delle dipendenze) per garantire che chiunque clona il progetto e lancia `npm install` ottenga esattamente le stesse versioni. `node_modules` va escluso da Git tramite `.gitignore` (vedi [[05 - Git e GitHub]]), perché si rigenera da `package.json` con `npm install`; `package-lock.json` invece **va committato**, proprio perché serve a riprodurre le stesse versioni su ogni macchina.

> [!info] Comandi npm e versioning (semver)
> | Comando | Effetto |
> |---|---|
> | `npm init` | crea `package.json` (con `-y` accetta i valori di default: extra, non da slide) |
> | `npm i <package>` / `npm install <package>` | installa un pacchetto (aggiunto a `dependencies`) |
> | `npm i -D <package>` | installa come `devDependencies` *(extra, non da slide)* |
> | `npm un <package>` | disinstalla un pacchetto |
> | `npm up <package>` | aggiorna un pacchetto |
> | `npm run <script>` | esegue uno script definito in `package.json` |
>
> Le versioni seguono il **semantic versioning** `MAJOR.MINOR.PATCH` (es. `1.0.0`): un **patch** release (bug fix retrocompatibili) incrementa l'ultima cifra (es. `1.0.0` → `1.0.1`), un **minor** (nuove funzionalità retrocompatibili) incrementa la cifra centrale azzerando l'ultima (es. `1.0.1` → `1.1.0`), un **major** (cambi che rompono la compatibilità) incrementa la prima azzerando le altre due (es. `1.1.0` → `2.0.0`). Nel `package.json` l'intervallo di versioni accettate in fase di aggiornamento si indica, secondo la slide *update*, così: **patch releases** `1.0` o `1.0.x` o `~1.0.4` (accetta solo aggiornamenti di patch); **minor releases** `1` o `1.x` o `^1.0.4` (accetta anche aggiornamenti minori); **major releases** `*` o `x` (accetta qualsiasi versione). La slide mostra anche un esempio di `dependencies`: `"my_dep": "^1.0.0"` e `"another_dep": "~2.2.0"`.
## Script npm: npm start vs npm run <nome> *(extra, non da slide)*
La sezione `scripts` di `package.json` definisce comandi con un nome breve al posto di digitare comandi lunghi a mano. Per lanciarli si usa `npm run <nome-script>` — **tranne** per lo script chiamato `start`, che ha un trattamento speciale: npm lo esegue con il solo comando **`npm start`**, senza bisogno di scrivere `run`. Ogni altro nome di script richiede invece `npm run <nome>`.

> [!warning] Trabocchetto — npm start non è un caso di npm run
> `npm start` funziona *solo* perché lo script si chiama esattamente `start` (è uno dei pochi alias speciali di npm, insieme a `test`, `stop`, `restart`). Per qualsiasi altro nome — `dev`, `build`, `api`, ecc. — `npm nome` da solo **non funziona**: va scritto `npm run nome`. Se poi `scripts` non contiene affatto la chiave `start`, `npm start` non dà errore: lancia comunque il default `node server.js` (fallendo solo se neanche quel file esiste). Per questo conviene definire sempre esplicitamente `"start": "node index.js"`, per non dipendere da questo comportamento implicito.

> [!question] Domanda tipica d'esame
> **D:** Il `package.json` di un progetto contiene questo script:
> ```json
> "scripts": {
>   "api": "node server.js"
> }
> ```
> Quale comando lo avvia?
> **R:** `npm run api`. Non basta `npm api`, e `npm start` non c'entra perché lo script non si chiama `start`.
>
> **D:** Con `"scripts": { "start": "node server.js" }` quale comando avvia l'applicazione? E con `"scripts": { "build": "..." }` quale comando esegue lo script `build`?
> **R:** `npm start` per lo script `start` (nome speciale, senza `run`); `npm run build` per lo script `build`, come per ogni altro nome diverso da quelli speciali.
## nodemon *(extra, non da slide)*
Durante lo sviluppo, riavviare a mano `node index.js` dopo ogni modifica al codice è scomodo. **nodemon** è un pacchetto (tipicamente installato come `devDependency`, cioè con `npm i -D nodemon`) che tiene sotto controllo i file del progetto e **riavvia automaticamente** il processo Node ad ogni salvataggio. Si usa quasi sempre tramite uno script `dev` dedicato, così da non doverlo digitare per esteso ogni volta:

```json
"scripts": {
  "dev": "nodemon index.js",
  "start": "node index.js"
}
```

Con questa configurazione, `npm run dev` avvia il server con nodemon (riavvio automatico) per lo sviluppo, mentre `npm start` avvia il server con il semplice `node`, adatto a un ambiente di produzione dove i file non cambiano.

Gli esempi del docente usano nodemon in due modi diversi. In `Esempi/live/js3/package.json` gli script `dev` (`nodemon index.js`) e `start` (`node index.js`) sono definiti, ma nodemon **non** è tra le dipendenze (ci sono solo `dotenv` e `moment`): per far funzionare `npm run dev` andrebbe installato. In `Esempi/live/js4/package.json` nodemon è invece in `devDependencies` (insieme a `express` in `dependencies`), ma esiste solo lo script `dev`, senza `start`.
## Variabili d'ambiente e .env
*(Questo esempio è nel materiale del docente, `Esempi/live/js3` con `index.js` e `.env`; le indicazioni su `.gitignore` e `.env.example` sono extra, non da slide.)*
Un'applicazione ha spesso bisogno di valori di configurazione che **non vanno scritti nel codice** né mandati su Git: la porta del server, chiavi di API, credenziali di un database. Node espone queste informazioni come **variabili d'ambiente** tramite l'oggetto globale `process.env`. Per non doverle impostare a mano nel terminale ad ogni avvio, si usa il pacchetto **dotenv**: legge un file `.env` nella radice del progetto e ne carica il contenuto in `process.env`.

> [!example] .env e dotenv
> ```bash
> # .env
> HELLO="Dotenv"
> ```
> ```js
> // index.js
> const dotenv = require('dotenv');
> dotenv.config();
> console.log(`Hello ${process.env.HELLO}`);
> // Hello Dotenv
> ```
> Nell'esempio `js3` il file `.env` contiene anche `OPENAI_API_KEY="your-api-key-goes-here"`, un segnaposto per una chiave di API: è proprio il tipo di valore che non va scritto nel codice. Lo stesso `index.js` usa il pacchetto di terze parti `moment` (`moment().format("HH:mm")` stampa l'ora corrente).

> [!warning] Trabocchetto — il file .env non si committa
> Il file `.env` contiene valori sensibili (chiavi, password) e **non va incluso nel repository Git**: va aggiunto al `.gitignore`. Chi clona il progetto crea il proprio `.env` locale, spesso partendo da un file di esempio `.env.example` senza valori reali.
## Lettura dei log e debug
*(extra, non da slide, ma richiesto esplicitamente all'esame/progetto)*
Il modo più immediato per capire cosa fa un programma Node è leggere l'output di `console.log` (e `console.error` per gli errori) nel terminale dove il server è in esecuzione — per questo gli esempi del corso usano spesso un piccolo modulo di log personalizzato (`betterLog.js` di `js2`, con le funzioni `debug` ed `error`) che prefissa i messaggi con `DEBUG -` o `ERROR -`, per distinguerli rapidamente nell'output del terminale.
Per un'analisi più approfondita, Node integra un **debugger**: avviando il programma con `node --inspect index.js` (invece di `node index.js`), Node apre una porta di debug a cui ci si può collegare da Chrome DevTools (digitando `chrome://inspect` nel browser) o dall'editor, per impostare **breakpoint**, ispezionare variabili ed eseguire il codice passo passo, esattamente come si farebbe con JavaScript lato client.
## Riferimenti
- `Materiale Didattico/Slide/PW34-NodeJS.pdf`: pp. 1-32 (frontend e backend, siti statici, dinamici e API based, tecnologie per backend 2021 e 2026), pp. 33-58 (Node.js, architettura V8/libuv, moduli, core module, esempio fs, esempio web server, routing, creare moduli, npm, versioning, resolving e wrapping dei moduli).
- `Materiale Didattico/Esempi/live/js2/` (`es1.js`, `es2.js`, `es3.js`, `betterLog.js`): hello world, lettura file sync/async, server HTTP nativo con modulo locale.
- `Materiale Didattico/Esempi/live/js3/` (`package.json`, `index.js`, `.env`, `oraVecchia.js`, `betterLog.js`): script `start` e `dev` (che usa nodemon, non presente tra le dipendenze del `package.json`), `dotenv`, `moment`, cache dei moduli con `oraVecchia.js`.
- `Materiale Didattico/Esempi/live/js4/package.json`: `dependencies` vs `devDependencies` (Express e nodemon), solo script `dev`.
