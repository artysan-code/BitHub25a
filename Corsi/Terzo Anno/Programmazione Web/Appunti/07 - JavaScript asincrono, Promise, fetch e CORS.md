---
tags:
  - programmazione-web
  - javascript
slide:
  - "PW31-JS-Asincrono-Promises.pdf"
  - "PW32-Fetch-Async-CORS.pdf"
  - "javascript_2026.pdf"
---
# JavaScript asincrono, Promise, fetch e CORS
JavaScript è **single-thread**: esiste un solo *thread* di esecuzione, quindi se una riga di codice impiega molto tempo (una richiesta di rete, un timer, una lettura di file) l'intera pagina si blocca finché quella riga non finisce. Questa nota spiega come JavaScript evita il blocco tramite il modello **asincrono** (event loop, callback, Promise, `async`/`await`), come si usa `fetch` per parlare con un backend (GET e POST, gestione degli errori, stati dell'interfaccia) e cos'è il **CORS**, il meccanismo che regola le richieste tra origini diverse — argomenti alla base del frontend del progetto d'esame, che comunica via `fetch` con le API REST viste in [[09 - Express e API REST]].
## Codice sincrono e codice asincrono
Nel **codice sincrono** ogni istruzione è eseguita linea dopo linea, e ogni riga aspetta che finisca la precedente: se un'operazione è lenta, blocca tutto il resto.

> [!example] Codice sincrono bloccante
> ```js
> const modal = document.querySelector('.modal');
> modal.style.backgroundColor = 'red';
> let val = confirm('Show Modal?'); // bloccante: il codice si ferma qui
> if (val) modal.classList.add('show');
> ```
> `confirm()` apre una finestra di dialogo e **blocca** l'esecuzione: nessun'altra riga viene eseguita finché l'utente non risponde.

Nel **codice asincrono** un'operazione lenta viene delegata a un "task in background" (gestito dal browser, non da JavaScript), e il codice sincrono continua subito la sua esecuzione; la funzione di callback passata al task viene eseguita solo quando il task in background è terminato.

> [!example] Codice asincrono con setTimeout
> ```js
> const modal = document.querySelector('.modal');
> setTimeout(function () {
>   modal.classList.add('show'); // eseguita dopo 2000ms, in background
> }, 2000);
> modal.style.backgroundColor = 'red'; // eseguita subito, non aspetta il timer
> ```

I timer sono metodi dell'oggetto `window` (`javascript_2026.pdf`): `setTimeout(funzione, ms)` richiama una funzione **una sola volta** dopo `ms` millisecondi, `setInterval(funzione, ms)` la richiama **ciclicamente** ogni `ms` millisecondi; `clearTimeout`/`clearInterval` li annullano, ricevendo l'identificativo restituito da `setTimeout`/`setInterval`.

Lo stesso vale per eventi come il caricamento di un'immagine: `image.src = 'mountain.jpg'` avvia il caricamento in background e il codice successivo continua subito; solo quando l'immagine è caricata scatta l'evento `load` e viene eseguita la callback registrata con `addEventListener`.

> [!warning] Una callback da sola non rende il codice asincrono
> Passare una funzione come parametro (es. dentro un `forEach`) non basta a renderla asincrona: se l'operazione dentro la callback è sincrona (es. modificare lo stile di alcuni elementi), viene eseguita comunque nell'ordine normale, bloccando come qualsiasi altra riga. È **asincrona solo l'operazione stessa** (timer, rete, caricamento di una risorsa), non il fatto di usare una funzione come argomento.
## Call stack, event loop e code dei task
Il motore JavaScript ha una **call stack** (dove si accumulano le funzioni in esecuzione) e una **memory heap**. Le operazioni asincrone (timer, richieste AJAX, eventi del DOM) non sono gestite dal motore JS ma dalle **Web API** del browser: quando un'operazione asincrona finisce, il browser mette la sua callback in una coda.
- La **Callback Queue** (o coda dei *task*/*macrotask*) riceve le callback di `setTimeout`, eventi DOM (`onClick`, `onLoad`), richieste AJAX completate.
- La **Microtask Queue** riceve le callback di `.then`/`.catch`/`.finally` delle Promise.
- L'**Event Loop** ha un compito semplice: controlla continuamente se la call stack è vuota; solo quando lo è, preleva ed esegue il prossimo elemento in coda.

> [!info] Priorità: microtask prima dei macrotask
> La coda dei **microtask ha sempre priorità** su quella dei task/callback: l'event loop svuota **tutta** la microtask queue (anche se nel frattempo se ne aggiungono altre) prima di prelevare anche un solo elemento dalla callback queue, indipendentemente da quale dei due sia "arrivato prima".

> [!example] Ordine di esecuzione
> ```js
> function main() {
>   console.log('A');
>   setTimeout(function display() {
>     console.log('B');
>   }, 0);
>   console.log('C');
> }
> main();
> // stampa: A, C, B
> ```
> Anche con `0` millisecondi di ritardo, `setTimeout` mette la sua callback nella callback queue: viene eseguita solo dopo che tutto il codice sincrono (`main()`) è terminato e la call stack si è svuotata.

> [!question] Domanda tipica d'esame
> Dato questo codice, qual è l'ordine di stampa in console?
> ```js
> console.log('Start');
> setTimeout(() => console.log('Timer 0'), 0);
> Promise.resolve('resolved Promise 1').then((res) => console.log(res));
> Promise.resolve('resolved Promise 2').then((res) => {
>   for (let index = 0; index < 10000000000; index++) {}
>   console.log(res);
> });
> console.log('Stop');
> ```
> Risposta: `Start`, `Stop`, `resolved Promise 1`, `resolved Promise 2`, `Timer 0`. Il codice sincrono (`Start`, `Stop`) va sempre per primo. Poi l'event loop svuota **tutta** la microtask queue prima di considerare `Timer 0`: anche se il secondo `.then` contiene un ciclo lentissimo che blocca il thread, `Timer 0` deve comunque aspettare che la microtask queue sia completamente vuota.
## Callback e Callback Hell
Una **callback** è una funzione passata come argomento a un'altra funzione, per essere richiamata più avanti (subito, o dopo un evento asincrono).

> [!example] Passare funzioni ad altre funzioni
> ```js
> function ask(question, yes, no) {
>   if (confirm(question)) yes();
>   else no();
> }
> ask(
>   'Do you agree?',
>   function () { alert('You agreed.'); },
>   function () { alert('You canceled the execution.'); }
> );
> ```

Quando più operazioni asincrone dipendono l'una dal risultato dell'altra, annidare le callback porta al cosiddetto **callback hell**: codice a "piramide" difficile da leggere, modificare e in cui gestire gli errori diventa complicato.

> [!example] Callback Hell
> ```js
> setTimeout(() => {
>   console.log('1 second passed');
>   setTimeout(() => {
>     console.log('2 seconds passed');
>     setTimeout(() => {
>       console.log('3 second passed');
>       setTimeout(() => {
>         console.log('4 second passed');
>       }, 1000);
>     }, 1000);
>   }, 1000);
> }, 1000);
> ```
> Le **Promise** risolvono esattamente questo problema: permettono di concatenare operazioni asincrone in sequenza piatta con `.then`, invece di annidarle (vedi [[#Concatenare Promise]]).
## Promise
Una **Promise** è un oggetto placeholder per il risultato futuro di un'operazione asincrona: un "contenitore" per un valore che sarà disponibile più avanti.

> [!quote] Definizione — Promise
> Una Promise è un oggetto che rappresenta l'eventuale completamento (o fallimento) di un'operazione asincrona e il suo valore risultante. Vantaggi: non serve più abbinare un evento a una callback per gestire il risultato asincrono, e le Promise si possono **concatenare**, evitando il callback hell.
### Ciclo di vita
Una Promise nasce nello stato **pending** (in attesa) e passa (una sola volta) a uno stato **settled** (definitivo):
- **fulfilled**: l'operazione è andata a buon fine, chiamando `resolve(value)`.
- **rejected**: l'operazione è fallita, chiamando `reject(error)`.

Si crea con `new Promise(executor)`, dove `executor` è una funzione che riceve `resolve` e `reject` come parametri ed è eseguita **subito, in modo sincrono**, al momento della costruzione.

> [!warning] Una Promise cambia stato una sola volta
> Il primo `resolve` o `reject` chiamato decide lo stato definitivo: tutte le chiamate successive a `resolve`/`reject` sulla stessa Promise vengono **ignorate**, senza errori.

> [!example] Creare una Promise
> ```js
> let promise = new Promise(function (resolve, reject) {
>   // eseguita subito, in modo sincrono
>   setTimeout(() => resolve('done'), 1000); // dopo 1s: fulfilled, result "done"
> });
> let failing = new Promise(function (resolve, reject) {
>   setTimeout(() => reject(new Error('Whoops!')), 1000); // dopo 1s: rejected
> });
> ```
### Consumare una Promise: then, catch, finally
`.then()` accetta fino a due funzioni: una per il caso `resolve`, una per il caso `reject`.

> [!example] then, catch e finally
> ```js
> let promise = new Promise((resolve, reject) => {
>   setTimeout(() => resolve('done!'), 1000);
> });
> promise.then(
>   result => console.log(result), // "done!" dopo 1s (resolve)
>   error => console.error(error)  // non eseguita
> );
> // .catch(f) equivale a .then(null, f)
> promise.catch(error => console.error(error)).finally(() => console.log('Finally!'));
> ```
> `.finally()` viene eseguito comunque, sia in caso di successo sia di errore, e non riceve il valore/errore come parametro: serve per operazioni di pulizia (es. nascondere uno spinner di caricamento). Il valore o l'errore **passano attraverso** il `finally` e arrivano al gestore successivo:
> ```js
> promise
>   .finally(() => alert('Promise ready'))
>   .then(result => alert(result)); // .then riceve comunque il risultato
> ```

> [!question] Domanda tipica d'esame
> ```js
> function buttonExecutor(resolve, reject) {
>   let myBtn = document.querySelector('button');
>   myBtn.addEventListener('click', function () {
>     resolve();
>     console.log('clicked!');
>   });
>   setTimeout(reject, 5000);
> }
> let betterClick = new Promise(buttonExecutor);
> betterClick
>   .then(function () { console.log('Option A'); })
>   .catch(function () { console.log('Option B'); });
> ```
> Cosa succede se il pulsante viene cliccato **dopo** 5 secondi? Allo scadere dei 5 secondi `reject` porta la Promise in *rejected* e viene stampato `Option B`. Il clic successivo stampa `clicked!` (il listener è ancora attivo), ma il suo `resolve()` viene **ignorato**: la Promise è già *settled*, quindi `Option A` non viene mai stampato. Se invece nessuno clicca, si vede solo `Option B`.
### Concatenare Promise
Ogni `.then()` restituisce a sua volta una **nuova Promise**: se la funzione passata a `.then` restituisce un valore, quel valore diventa il risultato della Promise successiva nella catena, permettendo di incatenare più passaggi in sequenza piatta. Se invece restituisce **un'altra Promise**, il `.then` successivo **aspetta** che quella Promise si risolva e riceve il suo valore (non la Promise stessa).

> [!example] Concatenare Promise
> ```js
> new Promise((resolve, reject) => {
>   setTimeout(() => resolve(1), 1000);
> })
>   .then(result => { console.log(result); return result * 2; }) // 1
>   .then(result => { console.log(result); return result * 2; }) // 2
>   .then(result => { console.log(result); return result * 2; }); // 4
> ```

> [!question] Domanda tipica d'esame
> Cosa stampano questi due frammenti?
> ```js
> const executor = (resolve, reject) => resolve(1);
> // (a) funzioni che restituiscono valori
> new Promise(executor)
>   .then(value => value + 5)
>   .then(value => value * 6)
>   .then(console.log);
> // (b) funzione che restituisce una Promise
> new Promise(executor)
>   .then(value => new Promise(resolve => resolve(value + 5)))
>   .then(console.log);
> ```
> (a) stampa `36`: $1 + 5 = 6$, poi $6 \cdot 6 = 36$. (b) stampa `6`: il secondo `.then` aspetta la Promise restituita dal primo e riceve il suo valore, non l'oggetto Promise.

> [!warning] resolve/reject sincroni, ma then/catch sempre asincroni
> Anche se `resolve()` viene chiamato in modo sincrono dentro l'executor (senza `setTimeout`), la callback passata a `.then()` **non** viene mai eseguita immediatamente: è sempre schedulata come microtask, e quindi eseguita solo dopo che il codice sincrono che segue è terminato.

> [!question] Domanda tipica d'esame
> ```js
> function orderExecutor(resolve, reject) {
>   console.log('Pizza ordered...');
>   resolve("Here's your pizza!");
> }
> let orderPizza = new Promise(orderExecutor);
> orderPizza.then(console.log);
> console.log('Waiting for my pizza!');
> ```
> Ordine di stampa: `Pizza ordered...`, `Waiting for my pizza!`, `Here's your pizza!`. L'executor gira subito in modo sincrono (stampa `Pizza ordered...` e chiama `resolve`), ma la callback di `.then` è comunque una microtask e aspetta che il codice sincrono (`console.log('Waiting for my pizza!')`) sia finito.
## async/await
`async` prima di una dichiarazione di funzione fa sì che quella funzione **restituisca sempre una Promise** — anche se al suo interno c'è un semplice `return`.

> [!example] async
> ```js
> async function f() {
>   return 1;
> }
> f().then(alert); // 1 — equivalente a "return Promise.resolve(1)"
> ```

`await` (utilizzabile solo dentro una funzione `async`) sospende l'esecuzione della funzione finché la Promise a cui è applicato non si risolve, e restituisce il suo valore; nel frattempo il resto del programma (fuori da quella funzione) continua a girare normalmente.

> [!example] await
> ```js
> async function f() {
>   let promise = new Promise((resolve, reject) => {
>     setTimeout(() => resolve('done!'), 1000);
>   });
>   let result = await promise; // aspetta che la promise si risolva
>   alert(result); // "done!"
> }
> f();
> ```

Se la Promise viene **rifiutata**, `await` lancia l'errore come se ci fosse un `throw` in quel punto: si gestisce quindi con un normale blocco `try...catch`, invece di `.catch()`.

> [!example] Gestione errori con try/catch
> ```js
> async function f() {
>   try {
>     let response = await fetch('http://no-such-url');
>   } catch (err) {
>     alert(err); // TypeError: failed to fetch
>   }
> }
> f();
> ```
## fetch
`fetch` è l'API moderna, basata su Promise, per fare richieste AJAX (Asynchronous JavaScript And XML — comunicazione col server senza ricaricare la pagina); sostituisce la vecchia `XMLHttpRequest` (vedi [[#XMLHttpRequest — il predecessore di fetch]]) ed è supportata da tutti i browser moderni.
`fetch(url)` restituisce subito una Promise che si risolve con un oggetto `Response` non appena arrivano gli **header** della risposta (non serve aspettare tutto il body). Da lì il corpo va estratto in modo asincrono con `res.json()` o `res.text()` (che restituiscono a loro volta una Promise), seguendo quella che le slide chiamano la **Promise Pipeline**: `fetch` → controllo dello status → estrazione del body → gestione del risultato, con `.catch()` che intercetta l'errore in qualsiasi punto della catena.
### GET
> [!example] Richiesta GET
> ```js
> fetch('https://jsonplaceholder.typicode.com/users')
>   .then(res => res.json())
>   .then(res => res.map(user => user.username))
>   .then(userNames => console.log(userNames));
> ```
### POST con JSON
Per inviare dati si passa un secondo argomento a `fetch` con `method`, `headers` e `body` (il body va serializzato con `JSON.stringify`, perché `fetch` invia stringhe o binari, non oggetti JS).

> [!example] Richiesta POST con body JSON
> ```js
> const myPost = { title: 'A post about true facts', body: '42', userId: 2 };
> const options = {
>   method: 'POST',
>   body: JSON.stringify(myPost),
>   headers: { 'Content-Type': 'application/json' }
> };
> fetch('https://jsonplaceholder.typicode.com/posts', options)
>   .then(res => res.json())
>   .then(res => console.log(res));
> ```
### Gestione dell'errore
`fetch` mette a disposizione `response.ok` (booleano) e `response.status` (il codice numerico, vedi [[01 - Internet, Web e HTTP]]) per controllare l'esito.

> [!example] Controllo dello status
> ```js
> fetch('https://jsonplaceholder.typicode.com/postsZZZ', options)
>   .then(res => {
>     if (res.ok) {
>       return res.json();
>     } else {
>       return Promise.reject({ status: res.status, statusText: res.statusText });
>     }
>   })
>   .then(res => console.log(res))
>   .catch(err => console.log('Error, with message:', err.statusText));
> ```

> [!warning] fetch NON rifiuta la Promise su 404/500
> La Promise restituita da `fetch` va in **rejected** solo per un errore di **rete** (host irraggiungibile, nessuna connessione, CORS bloccante): una risposta con status **404 o 500 è comunque una risposta HTTP valida**, quindi la Promise va in **fulfilled** normalmente. Bisogna controllare esplicitamente `response.ok` (equivalente a `status` tra 200 e 299) o `response.status`: un `.catch()` da solo **non intercetta** un 404/500.
## fetch con async/await
La stessa logica di `fetch` si scrive in modo più lineare con `async`/`await`.

> [!example] GET con async/await
> ```js
> async function fetchUsers(endpoint) {
>   const res = await fetch(endpoint);
>   const data = await res.json();
>   return data;
> }
> fetchUsers('https://jsonplaceholder.typicode.com/users')
>   .then(data => console.log(data.map(user => user.username)));
> ```

> [!example] Gestione errori con status + try/catch
> ```js
> async function fetchUsers(endpoint) {
>   try {
>     const res = await fetch(endpoint);
>     if (!res.ok) {
>       throw new Error(res.status); // 404
>     }
>     const data = await res.json();
>     return data;
>   } catch (error) {
>     console.error('Ooops, error', error.message);
>   }
> }
> ```
> Come nell'esempio con `.then`/`.catch`, il controllo di `res.ok` va fatto a mano: `await fetch(...)` non lancia un errore da solo su un 404, va convertito con un `throw` esplicito perché `try/catch` lo intercetti.

Un esempio realistico, dal materiale del corso (`Materiale Didattico/Esempi/live/js1/index2.html`), che aggiorna il DOM col risultato:
```js
const getData = async function () {
  try {
    const response = await fetch('https://jsonplaceholder.typicode.com/users/2');
    const data = await response.json();
    mydiv.innerHTML = `<p>${data.email}</p>`;
  } catch (error) {
    console.error('Error fetching data:', error);
  }
};
getData();
```
## Gestione degli stati dell'interfaccia
Il progetto d'esame (vedi il README del corso) richiede esplicitamente che il frontend mostri gli **stati** di una richiesta `fetch`: **caricamento**, **errore**, **successo** e **lista vuota** (quando la richiesta riesce ma non ci sono dati da mostrare). Senza questi stati l'utente non capisce se l'app si è bloccata, se c'è stato un errore o se semplicemente non ci sono risultati.

> [!example] Pattern loading/error/success/empty
> ```js
> async function loadItems() {
>   const container = document.querySelector('#list');
>   container.textContent = 'Caricamento...'; // stato: caricamento
>   try {
>     const res = await fetch('/api/items');
>     if (!res.ok) throw new Error(`Errore ${res.status}`);
>     const items = await res.json();
>     if (items.length === 0) {
>       container.textContent = 'Nessun elemento trovato.'; // stato: lista vuota
>       return;
>     }
>     container.innerHTML = items.map(i => `<li>${i.name}</li>`).join(''); // stato: successo
>   } catch (err) {
>     container.textContent = `Si è verificato un errore: ${err.message}`; // stato: errore
>   }
> }
> ```
> *(extra, non da slide: pattern derivato dal requisito di progetto descritto nel README del corso, non da una slide specifica.)*
## XMLHttpRequest — il predecessore di fetch
Prima di `fetch`, le richieste AJAX si facevano con `XMLHttpRequest`. È materiale più datato (da `javascript_2026.pdf`), utile per riconoscere codice legacy: il terzo parametro di `open()` indica se la richiesta è sincrona (`false`, bloccante) o asincrona (`true`, richiede di gestire manualmente il risultato con un listener su `onreadystatechange`).

> [!example] XMLHttpRequest asincrono
> ```js
> var xhr = new XMLHttpRequest();
> xhr.onreadystatechange = function () {
>   if (xhr.readyState == 4 && xhr.status == 200) {
>     console.log(xhr.responseText); // risposta come stringa, non ancora JSON
>   }
> };
> xhr.open('GET', yourUrl, true);
> xhr.send();
> ```
## CORS
Quando il frontend (es. `http://localhost:5500`) e il backend (es. `http://localhost:3000`) girano su **origini diverse**, il browser applica delle regole di sicurezza che vanno capite per far funzionare `fetch` verso l'API del progetto.

> [!quote] Definizione — Origine (origin) e Same-Origin Policy
> L'**origine** di una pagina è la combinazione di **schema** (`http`/`https`), **host** (dominio) e **porta**. La **same-origin policy** del browser permette a uno script di leggere i dati di un'altra risorsa web (pagina, JSON, ecc.) solo se ha la **stessa origine** della pagina che lo esegue. Le richieste same-origin (immagini, CSS, script del proprio dominio) sono sempre permesse; le richieste **cross-origin** sono controllate dal **CORS**.

> [!warning] La same-origin policy blocca lo script, non la richiesta
> Se manca l'autorizzazione CORS, il server riceve comunque la richiesta e può rispondere normalmente: è il **browser** che blocca lo script dal leggere quella risposta, mostrando un errore tipo `No 'Access-Control-Allow-Origin' header is present on the requested resource`. Non è quindi un problema del server che "non risponde", ma del browser che impedisce alla pagina di accedere alla risposta.

**CORS** (Cross-Origin Resource Sharing) è lo standard W3C che permette di autorizzare esplicitamente il resource sharing tra domini diversi, tramite header HTTP scambiati in richiesta/risposta. Prevede due modalità:
### Simple request
Richieste "semplici" (metodi `GET`, `HEAD`, `POST`; header limitati a `Accept`, `Accept-Language`, `Content-Language`, `Content-Type` solo con valore `application/x-www-form-urlencoded`, `multipart/form-data` o `text/plain`) vengono inviate direttamente; il server risponde con l'header `Access-Control-Allow-Origin`, che il browser controlla prima di consegnare la risposta allo script.

```http
GET /doc HTTP/1.1
Origin: foo.example

HTTP/1.1 200 OK
Access-Control-Allow-Origin: *
```
`Access-Control-Allow-Origin: *` significa che la risorsa è accessibile da **qualsiasi** origine.
### Preflight request
Una richiesta con un metodo non "semplice" (`PUT`, `DELETE`, `PATCH`) o con header/valori fuori dall'elenco sopra — incluso il tipico `Content-Type: application/json` usato per inviare JSON a un'API REST — attiva prima una **richiesta preflight**: il browser invia automaticamente una `OPTIONS` per chiedere l'autorizzazione, e solo se la risposta la concede invia la richiesta vera.

```http
OPTIONS /doc HTTP/1.1
Origin: http://foo.example
Access-Control-Request-Method: POST
Access-Control-Request-Headers: X-PINGOTHER, Content-type

HTTP/1.1 204 No Content
Access-Control-Allow-Origin: http://foo.example
Access-Control-Allow-Methods: POST, GET, OPTIONS
Access-Control-Allow-Headers: X-PINGOTHER, Content-Type
Access-Control-Max-Age: 86400
```

> [!warning] Un POST con JSON attiva quasi sempre il preflight
> `Content-Type: application/json` **non** è tra i valori ammessi per una simple request: quindi qualunque `fetch` che invia JSON con `POST` (vedi [[#POST con JSON]] in questa nota) genera prima una richiesta `OPTIONS` di preflight. Se il backend Express non risponde correttamente a `OPTIONS` (tipicamente tramite il middleware `cors`), la richiesta reale non parte mai e il browser mostra un errore CORS.

> [!info] Come si abilita in Express
> Il backend deve rispondere con gli header `Access-Control-Allow-Origin` (ed eventualmente `Access-Control-Allow-Methods`/`Access-Control-Allow-Headers` per le richieste preflight). In pratica si usa il middleware `cors` di Express: i dettagli di configurazione sono in [[09 - Express e API REST]].
## Riferimenti
- `PW31-JS-Asincrono-Promises.pdf`: codice sincrono/asincrono, event loop e call stack, Promise (ciclo di vita, creazione, then/catch/finally, concatenazione), esercizi 1-6 sull'ordine di esecuzione (pp. 35-42), callback hell, microtask queue.
- `PW32-Fetch-Async-CORS.pdf`: fetch API e Promise pipeline, esempi GET/POST, gestione errori, async/await, try/catch, CORS (same-origin policy, simple request, preflight request).
- `javascript_2026.pdf`: timer dell'oggetto `window` (`setTimeout`, `setInterval`), `XMLHttpRequest` sincrona e asincrona (predecessore di `fetch`).
- Esempi del docente: `Materiale Didattico/Esempi/promise1/main.js` (Promise con `setTimeout`, `then`/`catch`/`finally`); `Materiale Didattico/Esempi/live/js1/index.html` (fetch con `.then` e aggiornamento del DOM); `Materiale Didattico/Esempi/live/js1/index2.html` (fetch con `async`/`await` e `try`/`catch`).
