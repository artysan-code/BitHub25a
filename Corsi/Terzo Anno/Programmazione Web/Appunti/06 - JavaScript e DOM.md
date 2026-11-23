---
tags:
  - programmazione-web
  - javascript
slide:
  - "javascript_2026.pdf"
---
# JavaScript e DOM
JavaScript è il linguaggio che rende una pagina web **interattiva**: [[02 - HTML semantico e form|HTML]] struttura i contenuti e [[03 - CSS - selettori, specificità e box model|CSS]] li presenta, ma solo JavaScript permette di reagire alle azioni dell'utente, modificare la pagina dopo che è stata caricata e comunicare con un server senza ricaricarla. Questa nota copre il **linguaggio** (variabili, tipi, funzioni, oggetti, array), il **DOM** (la rappresentazione della pagina che JavaScript può leggere e modificare) e gli **eventi** che collegano l'interazione dell'utente al codice: sono le basi del frontend richieste dal progetto d'esame, dove JavaScript deve stare in un **file separato dall'HTML**. La comunicazione asincrona con un server (timer, Promise, `fetch`, `async`/`await`, CORS) è trattata per esteso in [[07 - JavaScript asincrono, Promise, fetch e CORS]]; l'uso di JavaScript **fuori dal browser** (Node.js) è in [[08 - Node.js e npm]].
## Il linguaggio JavaScript
Prima di arrivare al DOM serve una base solida del linguaggio stesso: cos'è, come si esegue e i suoi costrutti fondamentali.
### Cos'è JavaScript e a cosa serve
JavaScript è un linguaggio di programmazione creato nel **1995** da **Brendan Eich** (Netscape) in soli 10 giorni, per rendere le pagine web "vive"; si chiamava originariamente "LiveScript"/"Mocha". Il nome **"JavaScript" non ha nulla a che fare con Java**: fu scelto solo per motivi di marketing. Nel 1996 è stato standardizzato dalla **ECMA** (European Computer Manufacturer's Association) col nome **ECMAScript**; la versione attuale dello standard è ECMAScript 2025. Le versioni si indicano anche con una sigla: **ES5** e **ES6** (detta anche ES2015) sono quelle che le slide citano più spesso, perché ES6 ha introdotto molte novità (`let` e `const`, arrow function, template literal, `for...of`) *(extra, non da slide: la denominazione ES2015)*.

> [!quote] Definizione — Ruolo di JavaScript
> **Lato client**, JavaScript è praticamente monopolista nei browser: nell'insieme di tre livelli Struttura ([[02 - HTML semantico e form|HTML]]) / Presentazione ([[03 - CSS - selettori, specificità e box model|CSS]]) / **Comportamento (JavaScript)**, è lui a gestire il comportamento della pagina. **Lato server**, dal 2009 esiste **Node.js**: nel 2008 il "Chromium Project" ha creato il motore JavaScript open source **V8**, usato l'anno dopo per costruire un runtime JavaScript lato server (dettagli in [[08 - Node.js e npm]]).

> [!info] Cosa fa (e non fa) JavaScript nel browser
>
> | Cosa fa | Cosa non fa (nel browser) |
> |---|---|
> | Modifica elementi della pagina (DOM) | Accede ai file locali del computer |
> | Interagisce con un server remoto | Interagisce con *qualunque* server remoto (vedi *same-origin policy* in [[07 - JavaScript asincrono, Promise, fetch e CORS#CORS]]) |
> | Reagisce ad azioni dell'utente | — |
> | Imposta cookie e contenuti locali (*file storage*) | — |
> | Disegna sulla pagina | — |

Nella slide la colonna «Cosa non fa» ha l'etichetta **JS VM**: i limiti derivano dal fatto che il codice gira dentro la macchina virtuale del browser (vedi [[#Caratteristiche del linguaggio e garbage collector]]). Le slide (p. 11) riassumono ciò che fa JavaScript in tre punti: **cambiare elementi e stili** della pagina (ad es. aggiungere classi CSS in risposta a eventi dell'utente come click o scroll, cioè *DOM manipulation*, vedi [[#Il DOM (Document Object Model)|il DOM]]); la **comunicazione asincrona**, cioè inviare dati senza ricaricare la pagina e senza interazione dell'utente, paradigma spesso chiamato **AJAX** (*Asynchronous JavaScript and XML*; le slide mostrano come esempi la ricerca istantanea e la chat); altro, come testare le capacità del browser e adattarsi (*polyfill*: libreria che rende il codice compatibile con browser vecchi, definita più sotto) o realizzare app mobile (la slide cita Cordova e PhoneGap con un punto interrogativo). Per studiare le slide consigliano il libro di testo, [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript) e **javascript.info** (segnalato come «Raccomandato!»); la slide «Oggi» cita il sondaggio di Stack Overflow, secondo cui JavaScript è il linguaggio più usato da 8 anni.

### Vanilla JS, framework e transpiler *(cenno)*
Da JavaScript sono nati nel tempo diversi **framework** lato client (ExtJS 2009, Knockout 2012, Backbone 2013, Angular 2014, React 2015, Vue.js 2017), ma questo corso studia **"vanilla JavaScript"**: JavaScript puro, senza framework. *(extra, non da slide)* Capire il linguaggio puro è ciò che poi permette di usare qualunque framework con cognizione di causa.

La scelta di «vanilla JavaScript» è motivata nelle slide con il sito vanilla-js.com; per sapere quali funzionalità sono supportate da quali browser si consulta **caniuse.com** (slide «Compatibilità»).

Un **transpiler** (es. BabelJS) è un *source-to-source translator*: traduce linguaggi differenti (CoffeeScript, TypeScript, Dart, Kotlin, ES6) in una versione specifica di JS (es. ES5). Serve perché permette di scrivere i programmi in modi più comodi per alcuni utenti e per la *backward compatibility* (ad es. ES6 → ES5). Un **polyfill** è invece una libreria JS che adatta del codice (HTML, CSS, JS) per renderlo retrocompatibile con standard vecchi. Esempi dalle slide: *HTML5 polyfill* (rende una pagina HTML5 compatibile con vecchi browser), **Modernizr** (testa la presenza di feature nel browser e carica i polyfill se servono), *Selectivizr* (fa capire a vecchie versioni di Internet Explorer le query CSS3 complesse).
### Caratteristiche del linguaggio e garbage collector
JavaScript è **dynamic**: non viene compilato, gira dentro una macchina virtuale (la *JS VM* del browser o di Node). È **loosely typed** (o *dynamically typed*): non bisogna dichiarare il tipo di una variabile, e una stessa variabile può cambiare tipo nel tempo. È **case-sensitive**: `programmazioneWeb` e `programmazioneweb` sono due variabili diverse.

> [!quote] Definizione — Garbage collector
> Il **garbage collector** è un algoritmo che rimuove automaticamente dalla memoria le variabili/oggetti che non sono più raggiungibili dal codice (nessun riferimento punta più a loro), senza che il programmatore debba liberare memoria a mano. Si può comunque creare un **memory leak** se, per errore, un riferimento a un oggetto ormai inutile resta vivo (esempio in [[#Riferimenti e garbage collector]]).
### Includere ed eseguire JavaScript
Il codice JavaScript si scrive in due modi: **incorporato** (*embedded*) direttamente in un tag `<script>` dentro l'HTML, oppure in un **file esterno** referenziato con l'attributo `src`. Gli script sono di solito inclusi in `<head>` o alla fine del `<body>`.

```html
<script>
  // codice inline (embedded)
</script>
<script src="my_script.js"></script>
```

> [!warning] Perché il progetto d'esame richiede JS separato dall'HTML
> Le specifiche del progetto richiedono **JavaScript separato dall'HTML** (file `.js` esterno), per lo stesso motivo per cui CSS non si scrive inline nei tag: separare struttura, presentazione e comportamento rende il codice più leggibile, riusabile e mantenibile. L'esempio del docente `Materiale Didattico/Esempi/01 - kitchen/kitchen-js.html` mostra lo stile tradizionale opposto: script *embedded* nell'`<head>`, libreria **jQuery** (non vanilla) caricata da una **CDN** (*Content Delivery Network*, rete di server che distribuisce file statici e librerie) *(extra, non da slide: definizione di CDN)*, evento associato con l'attributo HTML `onload` invece che con `addEventListener` (vedi [[#Eventi]]). Il codice della pagina: `startMoving(img)` fa scorrere l'immagine `spoon.gif` (`<img class="mover" onload="startMoving(this)">`) a 100 pixel al secondo (`moveRate = 100`, durata `time = amount * 1000 / moveRate`), con `img$.stop(true).animate({left: "+=" + amount}, time, "linear", callback)`; nella callback richiama `startMoving(this)`, quindi l'animazione riparte da capo a ogni passaggio. `$(window).width()` dà la larghezza della finestra e `parseInt(img$.css("left"), 10) || 0` la posizione attuale (0 se non impostata).

Quando il browser incontra un `<script>`, interrompe la costruzione della pagina, scarica lo script e lo esegue prima di proseguire. Questo crea un compromesso: mettere gli script in cima alla pagina rischia che non vedano ancora gli elementi HTML (il DOM non è pronto) e rallenta il rendering; metterli in fondo funziona, ma su documenti lunghi si rischia di aspettare troppo prima che lo script parta.

> [!info] Gli attributi `defer` e `async`
>
> | Attributo | Comportamento |
> |---|---|
> | *(nessuno)* | Il browser blocca il parsing, scarica ed esegue subito lo script, poi riprende. |
> | `defer` | Lo script si scarica **in background**, senza bloccare il parsing, e viene eseguito solo **dopo** che il DOM è stato costruito (*extra, non da slide:* nell'ordine in cui compare nel documento). |
> | `async` | Come `defer` per il download in background, ma viene eseguito **appena è pronto**, senza aspettare che il DOM sia completo (*extra, non da slide:* senza garanzie sull'ordine rispetto ad altri script `async`). |
>
> *(extra, non da slide)* `defer` è la scelta più sicura per uno script che deve manipolare il DOM: garantisce che gli elementi esistano già quando lo script parte. Gli esempi del docente (`capturediv`, `dynimg`, `dynlist`) usano infatti `<script defer src="...">`.
### Console e strumenti interattivi
Il codice JS si può eseguire in due modi: come **shell interattiva** (lato client, la console del browser; lato server, la console di Node — vedi [[08 - Node.js e npm]]) oppure eseguendo un file `.js` (lato client con il tag `<script>`, lato server lanciandolo con `node`). La **console del browser** si apre dai **DevTools** (gli strumenti per sviluppatori integrati nel browser, vedi [[#Debug e console]]; *extra, non da slide:* tasto F12 o tasto destro → Ispeziona → scheda *Console*) e permette sia di digitare comandi JS direttamente sia di leggere l'output di `console.log(...)`:

```js
console.log("ciao a tutti gli studenti di programmazione web");
// > ciao a tutti gli studenti di programmazione web
```

Per eseguire un file `.js` in Visual Studio Code le slide indicano di scrivere il file e usare *Run and Debug with Node.js*. Il debug più approfondito con breakpoint e call stack è in [[#Debug e console]].
### Variabili: var, let, const e scope
Una variabile si dichiara con `let`, `const` o `var`; il punto e virgola a fine istruzione è tecnicamente opzionale (il motore lo inserisce automaticamente, *Automatic Semicolon Insertion*), e *(extra, non da slide)* è comunque buona pratica scriverlo sempre.

```js
// questo è un commento
let myName = "lorenzo"; // variabile con stringa
let myNumber = 5;       // variabile con intero
let myVar;               // variabile non inizializzata (undefined)
myVar = myNumber;        // assegnazione
console.log(myVar);      // stampa il risultato
```

`let` e `const` sono stati introdotti in **ES6** (la versione dello standard ECMAScript del 2015) e sono da preferire a `var`. La differenza è lo **scope**: la regione di codice in cui il nome della variabile è visibile.

> [!quote] Definizione — Scope di var e let
> Lo scope di **`var`** è il *functional block* più vicino (l'intera funzione che la contiene, o il global scope se dichiarata fuori da funzioni). Lo scope di **`let`** (e `const`) è l'*enclosing block* più vicino: qualsiasi coppia di parentesi graffe `{ }` (un `if`, un `for`, un blocco qualsiasi).

> [!example] var vs let in un ciclo for
> ```js
> for (let i = 0; i < 2; i++) {
>   console.log(i);
> }
> console.log(i); // ReferenceError: i is not defined — i non esiste fuori dal for
> ```
> ```js
> for (var i = 0; i < 2; i++) {
>   console.log(i);
> }
> console.log(i); // 2 — con var, i "fuoriesce" dal blocco del ciclo
> ```

> [!example] Scope globale e locale (slide «scope: esempi»)
> ```js
> let a = 5;                        // global scope
> function x() { return a + 1; }    // vede a
> x();                              // 6
> a;                                // 5
> ```
> ```js
> function x() {                    // local scope
>   let a = 5;
>   return a + 1;
> }
> x();                              // 6
> a;                                // ReferenceError: a is not defined
> ```
> Nella slide (p. 54) l'ultima riga è commentata con `undefined`: è un errore della slide. Una variabile non dichiarata nello scope corrente genera un `ReferenceError`; `undefined` è invece il valore di una variabile dichiarata ma non inizializzata.

Una variabile dichiarata **dentro** una funzione ha *local scope* (visibile solo lì); una dichiarata **fuori** da ogni funzione ha *global scope* ed è visibile da qualunque altro script della pagina — potenzialmente pericoloso: crea interazioni non volute e contamina lo spazio dei nomi globale (*namespace pollution*).

> [!warning] Dimenticare let/var/const: variabile globale su window
> Se in modalità normale si scrive `a = 5;` senza `let`/`var`/`const`, JavaScript non genera errore: crea implicitamente una **proprietà dell'oggetto globale** (`window` nel browser). È uno dei motivi per cui si usa sempre `"use strict"` (sotto) e per cui si evitano le variabili globali.

`const` dichiara una variabile in **sola lettura** (slide: `const prefix = '06'; // read only`): non se ne può cambiare il riferimento dopo l'assegnazione. *(extra, non da slide)* Se il valore è un oggetto o un array, le sue proprietà/elementi restano modificabili: `const` blocca il *binding* (l'associazione tra nome e valore), non il contenuto.

```js
const utente = { nome: "Anna" };
utente.nome = "Luca";        // consentito: l'oggetto non è stato sostituito
const colori = ["rosso", "verde"];
colori.push("blu");          // consentito: l'array è lo stesso, ha un elemento in più
colori = [];                 // TypeError: Assignment to constant variable.
```

> [!question] Domanda tipica d'esame
> `const utente = { nome: "Anna" }; utente.nome = "Luca";` perché è valido? Risposta: `const` impedisce di **riassegnare la variabile** (cambiare quale oggetto o array contiene), ma non di modificare le proprietà dell'oggetto o gli elementi dell'array: l'oggetto non viene sostituito, cambia soltanto una sua proprietà. Lo stesso vale per `colori.push("blu")` su un array `const`.

> [!question] Domanda tipica d'esame
> Lo script non è in modalità strict: `function salvaNome() { nomeUtente = "Anna"; } salvaNome();` perché è pericoloso? Risposta: `nomeUtente` è assegnata senza `let`/`var`/`const`, quindi diventa una **proprietà dell'oggetto globale** (`window` nel browser), visibile ovunque e fuori dalla funzione. Con `"use strict"` si avrebbe invece un `ReferenceError`.
### Strict mode
```js
// senza strict mode questi casi passano in silenzio
a = 5;        // niente let/var: dichiarazione implicita, pericolosa
NaN = true;   // non produce errore, ma non ha alcun senso
```
```js
"use strict"; // prima riga del file: ora entrambi i casi sopra lanciano un errore
```

> [!quote] Definizione — Strict mode
> `"use strict";` è una direttiva (va messa **prima** di tutto il resto del codice, *(extra, non da slide:* all'inizio del file o della funzione*)*) introdotta in **ES5** per garantire un comportamento più sicuro: rende errori casi che altrimenti passerebbero silenziosamente, come gli assegnamenti a proprietà non scrivibili o non esistenti. È buona pratica usarlo sempre — infatti tutti gli esempi del docente (`capturediv/script.js`, `dynlist/main.js`, `dynimg/main.js`, `ecomm/cart.js`) iniziano con `"use strict";`.
### Tipi di dato primitivi
In JavaScript esistono **7 tipi primitivi**: `string`, `number`, `bigint`, `boolean`, `symbol`, `null` e `undefined`. Sono "primitivi" perché contengono un solo valore semplice (a differenza di oggetti e array, i tipi "complessi"). Non serve dichiarare il tipo: lo si scopre con l'operatore `typeof`.

| Dichiarazione | Tipo | Note |
|---|---|---|
| `let test = 5;` | `number` | anche i float (`5.123`); operatori `+ - * / % **` |
| `let test = "ciao";` | `string` | apici singoli o doppi; concatenazione con `+` |
| `let test = true;` | `boolean` | negazione con `!` |
| `let test;` | `undefined` | variabile dichiarata ma non inizializzata |
| `let test = null;` | `null` | valore "vuoto" assegnato esplicitamente; `typeof test` restituisce però `"object"` (vedi l'avviso sotto) |

Anche se sono primitivi, questi tipi hanno **metodi**, grazie a un "object wrapper" creato e distrutto temporaneamente quando si chiama il metodo: `"ciao".toUpperCase()` funziona anche su un letterale, non solo su una variabile. Le operazioni matematiche seguono la precedenza usuale e le parentesi la modificano (slide «Operazioni matematiche di base»):

```js
let i = 0, j = 2;
i = 2 + j * 4;   // 10
i++;             // 11
i = (2 + j) * 4; // 16
```

> [!warning] *(extra, non da slide)* typeof null è "object"
> `typeof null` restituisce `"object"`, non `"null"`: è un'anomalia storica di JavaScript, mai corretta per non rompere la retrocompatibilità. `null` resta comunque uno dei 7 tipi primitivi elencati sopra: `"object"` è solo il risultato (storico) di `typeof`. Per verificare se una variabile è effettivamente `null` si confronta direttamente (`x === null`), non con `typeof`.
### Conversioni e uguaglianza: == vs ===
Due funzioni utili per convertire una stringa in numero: `parseInt(string, radix)` (restituisce un intero, `radix` è la base numerica) e `parseFloat(string)` (restituisce un numero con decimali). In alternativa: `Number("42")` converte in numero, `num.toString()` o `String(num)` convertono in stringa, `(3.141592).toFixed(2)` arrotonda a un numero di decimali (`"3.14"`).

> [!warning] Conversioni automatiche: il trabocchetto di + e -
> ```js
> let answer = "La risposta giusta è ";
> answer += 42;        // "La risposta giusta è 42" — concatenazione
> answer = "45" - 3;    // 42 — "-" forza la conversione a numero
> answer = "45" + 3;    // "453" — "+" con una stringa concatena, non somma!
> ```
> `+` tra stringa e numero **concatena** (converte il numero in stringa); tutti gli altri operatori aritmetici (`-`, `*`, `/`) **convertono la stringa in numero**. È una delle sorgenti di bug più comuni per chi viene da linguaggi fortemente tipizzati.

> [!example] Esercizio 2 (slide p. 42): quale conversione può essere implicita?
> ```js
> "use strict";
>
> let n1, n2, somma;
> n1 = prompt("Inserisci il primo numero");
> n2 = prompt("Inserisci il secondo numero");
>
> somma = Number(n1) + Number(n2);
>
> alert("La somma fa " + String(somma));
> ```
> La slide non riporta la soluzione. *(extra, non da slide)* Nessuna: `Number(...)` e `String(...)` sono conversioni **esplicite**. Una conversione implicita ci sarebbe se si scrivesse `"La somma fa " + somma` (il numero verrebbe convertito in stringa dal `+`) o `n1 + n2` (concatenazione di due stringhe, dato che `prompt` restituisce stringhe). Eseguito in Node con `prompt`/`alert` simulati (3 e 4): `La somma fa 7`.

> [!question] Domanda tipica d'esame
> Con `let valore = "5";` cosa stampano `console.log(valore + 2)` e `console.log(valore - 2)`? Risposta: `"52"` e `3`. Il `+` con una stringa **concatena** (il numero `2` diventa la stringa `"2"`), mentre il `-` converte la stringa in numero e fa la sottrazione. Nella slide la stessa domanda è posta con `"45" + 3`.

> [!quote] Definizione — Uguaglianza debole (==) e stretta (===)
> `==` e `!=` confrontano il valore convertendo i tipi se necessario (*uguaglianza debole*). `===` e `!==` confrontano **valore e tipo**, senza alcuna conversione (*uguaglianza stretta*, "identico"/"non identico").
> ```js
> let a = "5"; // stringa contenente il numero 5
> let b = 5;   // numero 5
> a == b;   // true  — "5" viene convertito a 5
> a === b;  // false — tipi diversi (string vs number)
> ```

> [!warning] Preferire sempre === *(extra, non da slide)*
> Usa (quasi) sempre `===`/`!==`: `==` può dare risultati sorprendenti per le conversioni implicite di tipo. Riservalo solo a casi consapevoli, come `x == null` per controllare insieme `null` e `undefined`.

> [!question] Domanda tipica d'esame
> Cosa stampano `"5" == 5` e `"5" === 5`? Risposta: `true` (uguaglianza debole, converte la stringa a numero) e `false` (uguaglianza stretta, tipi diversi: `string` ≠ `number`).
### Operatori logici, ternario, truthy e falsy
Gli operatori logici sono `&&` (AND), `||` (OR), `!` (NOT); i confronti `> >= < <=` seguono l'ordine naturale. La slide presenta come «nuovo» il **nullish coalescing operator** `??` (*extra, non da slide:* è stato introdotto da ES2020, non da ES6): `a ?? b` ritorna `b` **solo se** `a` è `null` o `undefined`, altrimenti ritorna `a`. *(extra, non da slide)* È diverso da `||`, che scatterebbe anche per `0` o `""`, valori "falsy" ma legittimi. L'operatore **ternario** è una scorciatoia per un `if`/`else` che produce un valore: `let status = (age >= 18) ? "adult" : "minor";` (la slide scrive `var status`).

```js
true && false;       // false
(5 === 5) || false;  // true
```

> [!example] Test delle slide sul `??`
> ```js
> let a = 42, b;
> console.log(b ?? a == 42);       // true
> console.log((b ?? a == 42) + 1); // 2
> console.log(a ?? b ? a : b);     // 42
> ```
> `b` è `undefined`, quindi `b ?? a == 42` vale `a == 42`, cioè `true`; sommando 1 `true` diventa `1` e il risultato è `2`. Nell'ultima riga `a ?? b` vale `42` (truthy), quindi il ternario ritorna `a`.

> [!quote] Definizione — Truthy e falsy
> Ogni valore, usato in un contesto booleano (es. la condizione di un `if`), viene convertito implicitamente a `true` o `false`. Le slide elencano come **falsy** `undefined`, `""` (stringa vuota), `0` e `false`; *(extra, non da slide)* sono falsy anche `null` e `NaN`. **Tutto il resto è truthy**, comprese le stringhe non vuote come `"0"` o `"false"` e gli array o oggetti vuoti (`[]`, `{}`).
> ```js
> let a = "";
> let b = "ciao";
> if (a) { alert("a è falsy"); }   // non eseguito
> if (b) { alert("b è truthy"); }  // eseguito
> ```
### Istruzioni di controllo: if/else, switch, cicli
```js
if (a == 5) {
  alert("a è 5");
} else if (a > 5) {
  alert("a è maggiore di 5");
} else {
  alert("a è minore di 5 (o non è un numero!)");
}
```

Lo `switch` confronta un'espressione con una serie di `case`; senza `break` l'esecuzione "cade" nel `case` successivo (*fall-through*, *extra, non da slide:* il nome):
```js
switch (expression) {
  case label_1:
    // statements_1
    [break;]
  case label_2:
    // statements_2
    [break;]
  default:
    // statements_def
}
```
Il `break` è opzionale (da cui le parentesi quadre nella slide): senza di esso si prosegue nel `case` successivo.

I cicli classici sono `for` e `while`:
```js
for (let i = 0; i <= 10; i++) {
  console.log(i);
}
let i = -20;
while (i > 0) {
  console.log(i);
  i++;
}
```

ES6 (vedi [[#Variabili: var, let, const e scope]]) introduce due modi di iterare: **`for...in`** itera sulle *proprietà* (chiavi) di un oggetto o array, **`for...of`** itera sui *valori* di un iterabile (array, mappa, set).

> [!example] for...in vs for...of
> ```js
> let arr = [3, 5, 7];
> arr.foo = "hello";
> for (let i in arr) {
>   console.log(i); // "0", "1", "2", "foo" — anche la proprietà extra!
> }
> for (let i of arr) {
>   console.log(i); // 3, 5, 7 — solo i valori dell'array
> }
> ```
> La slide (p. 85) riporta come output del `for...in` `"3", "5", "7", "foo"`: è un errore della slide, perché `for...in` itera sulle **chiavi**, quindi stampa gli indici `"0"`, `"1"`, `"2"` e poi `"foo"`, come nel commento sopra.

> [!warning] for...in su un array
> `for...in` è pensato per le proprietà degli **oggetti**: su un array itera anche eventuali proprietà aggiuntive, non solo gli indici. Per iterare i **valori** di un array preferisci `for...of` oppure i metodi visti più avanti (`forEach`, `map`...).
### Funzioni: dichiarazione, parametri e scope
Le funzioni permettono di raggruppare comandi e di richiamare più volte lo stesso codice.

```js
function somma(a, b) {   // dichiarazione, con parametri
  let sum = a + b;
  return sum;             // valore ritornato
}
let s = somma(3, 5); // invocazione; s = 8
```

Esempio delle slide (che risolve anche l'esercizio «creare una calcolatrice per sommare due numeri»): `prompt` ritorna stringhe, quindi vanno convertite con `Number` prima di sommare.
```js
function calcolatrice() {                       // dichiarazione
  let n1, n2;
  n1 = prompt("Primo numero");
  n2 = prompt("Secondo numero");
  alert("La somma è " + (Number(n1) + Number(n2)));
}
calcolatrice();                                  // invocazione
```

I parametri mancanti valgono `undefined`: `somma(3)` calcola `3 + undefined`, cioè `NaN`. Si può impostare un **valore di default**: `function somma(a, b = 1) {...}` *(extra, non da slide:* prima di ES6 si simulava con `b = b || 1`*)*.

Come per le variabili, le funzioni definite **dentro** un'altra funzione (*nested*) vedono lo scope della funzione che le contiene, oltre al proprio e al globale; il contrario non vale — la funzione esterna non vede le variabili locali di quella interna (esempio in [[#Closure e IIFE]]).

> [!info] "One function, one action"
> Una funzione dovrebbe avere un **nome descrittivo** (es. `getName`, `runCalculator`, `checkIsOnline`) e fare **esattamente una cosa**: quella descritta dal suo nome. Se fa più cose, conviene spezzarla in più funzioni.

Le slide mostrano poi un esempio di «cattiva programmazione» da correggere: la funzione usa una **variabile globale come input nascosto** (`data1`), quindi il risultato dipende da dati non visibili dalla firma e il nome `c1` non dice cosa fa. Si sistema con un parametro e un commento **JSDoc** (la slide «Sistemiamo i problemi» ne mostra solo il titolo e un'immagine).
```js
let data1;
function c1() {             // cattiva: legge data1 dal global scope
  let x;
  x = data1 * 1.61803398875;
  return x;
}
data1 = 1000;
let res = c1();             // 1618.03398875

/**
 * Moltiplica un valore per la sezione aurea.
 * @param {number} value
 * @returns {number}
 */
function golden(value) {    // sistemata: dipende solo dal parametro
  return value * 1.61803398875;
}
```
*(extra, non da slide: la versione corretta e il commento JSDoc)*
### Funzioni come valori: espressioni, arrow function e callback
Oltre alla dichiarazione, una funzione si può definire come **espressione**, assegnandola a una variabile:
```js
let somma = function (a, b) {
  return a + b;
};
```

> [!warning] Dichiarazione vs espressione: hoisting
> L'*hoisting* ("sollevamento") è il comportamento per cui il motore conosce le dichiarazioni di funzione prima di eseguire il codice dello scope *(extra, non da slide: il termine)*. Una **dichiarazione di funzione** (`function somma() {...}`) può essere chiamata anche *prima* di essere scritta nel codice. Una **espressione funzionale** (`let somma = function () {...}`) esiste solo a partire dal punto in cui l'esecuzione la raggiunge: chiamarla prima genera un errore.

Le funzioni sono valori come gli altri: si possono passare come argomento ad altre funzioni, dette **callback**:
```js
function ask(question, yes, no) {
  if (confirm(question)) yes();
  else no();
}
ask(
  "Do you agree?",
  function () { alert("You agreed."); },
  function () { alert("You canceled the execution."); }
);
```

Le **arrow function** (ES6) sono una sintassi più sintetica per definire una funzione: `let somma = (a, b) => a + b;`. Esercizio delle slide: riscrivere `ask` con arrow function (soluzione *extra, non da slide*):
```js
function ask(question, yes, no) {
  if (confirm(question)) yes();
  else no();
}
ask(
  "Do you agree?",
  () => alert("You agreed."),
  () => alert("You canceled the execution.")
);
```

Le arrow function funzionano bene come callback brevi (vedi ad esempio `dynimg/main.js` più avanti), ma attenzione al comportamento di `this` al loro interno (vedi [[#Metodi e this]]).
### Closure e IIFE
Una funzione *nested* può accedere alle variabili delle funzioni che la contengono, "annidate" a più livelli:
```js
function moltoFuori() {
  let a = 5;
  function fuori() {
    let b = 6;
    function dentro() {
      let c = 7;
      console.log(a, b, c); // vede a, b e c
    }
    return dentro();
  }
  return fuori();
}
```

Una funzione può anche **ritornare un'altra funzione**, che "si porta dietro" lo scope della funzione che l'ha creata:
```js
function multisum(p1) {
  let x = p1;
  return function sum(a, b) {
    return x * (a + b);
  };
}
multisum(10)(1, 2); // torna 30
```
Nella versione precedente della slide `multisum(p1, a, b)` ritorna invece `sum(a, b)`, cioè **un numero** (il risultato di `sum`): `multisum(10, 1, 2)` torna 30. Con la versione sopra `multisum(10)` torna una **funzione**, che va poi invocata.

> [!quote] Definizione — Closure
> Una **closure** è una funzione che "ricorda" e continua ad avere accesso allo scope della funzione esterna in cui è stata creata, anche dopo che quest'ultima ha terminato l'esecuzione. Non memorizza solo il valore di ritorno, ma l'intero *ambiente* (le variabili) del padre.
> ```js
> function salutatore(name) {
>   let text = "Ciao " + name; // variabile locale
>   return function () { alert(text); };
> }
> let s = salutatore("Lorenzo");
> s(); // alert "Ciao Lorenzo" — "text" è ancora viva grazie alla closure
> ```
> Rispetto alla slide (p. 114) l'esempio è adattato: la slide scrive `'Ciao' + name` (senza spazio, quindi l'alert mostra «CiaoLorenzo») e salva la funzione in `let diCiao = function() {...}; return diCiao;`.

Le closure sono utili per simulare **variabili/metodi privati** (un embrione di object data privacy), separando interfaccia e implementazione:
```js
function counter() {
  let a = 0;
  return {
    inc: function () { ++a; },
    dec: function () { --a; },
    get: function () { return a; },
    reset: function () { a = 0; }
  };
}
let c = counter();
c.inc();
c.get(); // 1 — "a" non è accessibile direttamente dall'esterno (c.a è undefined)
```
La slide (p. 115) dice che `c.a` produce un errore: in realtà non si ha alcun errore, perché `a` non è una proprietà di `c` e l'accesso restituisce `undefined`.

Esercizio delle slide: creare tramite closure un oggetto `Player` con le funzioni di movimento su, giù, destra e sinistra. Soluzione breve *(extra, non da slide)*:
```js
function creaPlayer() {
  let x = 0, y = 0; // posizione privata
  return {
    su: () => { y--; },
    giu: () => { y++; },
    destra: () => { x++; },
    sinistra: () => { x--; },
    posizione: () => [x, y]
  };
}
const p = creaPlayer();
p.su(); p.destra(); p.destra();
p.posizione(); // [2, -1]
```

Un pattern collegato è la **IIFE** (*Immediately Invoked Function Expression*; la slide la chiama «Independently Invoked Functional Expression», ma il nome standard è quello con *Immediately*): una funzione anonima definita e invocata **immediatamente**, usata per non contaminare lo scope globale con le variabili di un intero script — tecnica usata storicamente anche da librerie come jQuery. Il problema da cui nasce, nelle slide: un file `mioprogramma.js` con `let a`, `let b` e `function pippo` scrive questi nomi nel global scope, dove altri script potrebbero usare gli stessi nomi; la soluzione è mettere tutto il codice in una funzione anonima invocata subito all'avvio. La slide la definisce una «tecnica molto usata».
```js
(function () {
  let a = 0;
  function pippo(x, y) { return x * y; }
  // ... tutto il programma qui dentro, invisibile dall'esterno
})();
```

> [!question] Domanda tipica d'esame
> Domanda da un colloquio reale (slide p. 120, «Da intervista vera!»). Cosa stampa questo codice?
> ```js
> (function () {
>   let a = b = 5;
> })();
> console.log(b);
> ```
> Risposta: `5`. `a = b = 5` viene valutato da destra a sinistra: prima si esegue `b = 5`, e poiché `b` non è dichiarato con `let`/`var`/`const`, diventa una **variabile globale implicita** (proprietà di `window`, vedi il warning in [[#Variabili: var, let, const e scope]]); solo dopo si assegna `a = b`. `a`, dichiarata con `let`, resta invece locale alla IIFE. Con `"use strict"` questo codice lancerebbe un errore invece di creare `b` globale.

> [!question] Domanda tipica d'esame
> `function creaContatore() { let valore = 0; return { incrementa() { valore++; }, leggi() { return valore; } }; }`: a cosa serve la closure? Risposta: i metodi `incrementa` e `leggi` **conservano lo stato** `valore` anche dopo che `creaContatore` è terminata, senza esporlo nel global scope né renderlo modificabile dall'esterno (`contatore.valore` è `undefined`). Ogni chiamata a `creaContatore()` crea una closure indipendente, con un proprio `valore`.
### Oggetti
Un **oggetto** raggruppa dati correlati come una lista di coppie proprietà–valore, racchiuse tra `{ }` — proprio da questa struttura nasce il formato **JSON** (*JavaScript Object Notation*, vedi [[#Oggetti built-in e gestione degli errori]]). Le proprietà sono stringhe (o simboli); i valori possono essere un tipo primitivo, un altro oggetto o una funzione. Non esistono valori "privati" per costruzione (per simularli si usano le closure viste sopra).

```js
let studente = {
  name: "Pierpaolo",       // stringa
  age: 80,                 // intero
  scores: [1, 2, 3],       // array
  classes: { pw: 30, fi: 18 } // altro oggetto
};
```
### Creazione, accesso e riferimenti
```js
let studente = {};          // oggetto vuoto (equivalente a new Object())
studente.voto = 30;          // aggiungo una proprietà (dot notation)
console.log(studente["voto"]);   // 30 — accesso equivalente con bracket notation
delete studente.voto;             // rimuovo la proprietà
console.log(studente.voto);      // undefined
```

> [!warning] Copiare un oggetto: è solo un riferimento!
> ```js
> let a = { nome: "pippo" };
> let b = a;        // b non è una copia: punta allo STESSO oggetto di a
> b.nome = "pluto";
> a.nome;           // "pluto" — anche a è cambiato!
> ```
> Per duplicare davvero un oggetto bisogna farlo esplicitamente (copiando ogni proprietà), non con una semplice assegnazione. *(extra, non da slide)* Vale anche per gli array, che sono oggetti.

Per lo stesso motivo il confronto tra oggetti è un confronto tra **riferimenti** (test delle slide, p. 67):
```js
let a1 = { "nome": "pippo" };
let b1 = a1;
a1 == b1;          // true — stesso oggetto
let c1 = {}, d1 = {};
c1 == d1;          // false — due oggetti distinti, anche se entrambi vuoti
```
### Riferimenti e garbage collector
Quando un oggetto non è più raggiungibile da nessuna variabile, il garbage collector ne libera la memoria: se `let b = a;` e poi `a = null; b = null;`, solo dopo l'ultimo azzeramento l'oggetto diventa irraggiungibile e viene rimosso. Un caso più insidioso è quello dei **riferimenti incrociati**: se `a.dog = b` e `b.owner = a`, i due oggetti si referenziano a vicenda; anche azzerando `a` e `b`, la slide presenta questo caso come un possibile **memory leak**, da tenere presente per evitare di mantenere vivi oggetti ormai inutili. *(extra, non da slide)* I motori moderni usano un algoritmo *mark and sweep*, che parte dagli oggetti raggiungibili e rimuove tutto il resto: una coppia che si referenzia soltanto a vicenda ma non è più raggiungibile dal codice viene quindi raccolta. Il leak resta reale quando un riferimento a un oggetto inutile rimane vivo altrove (una variabile globale, una closure, un listener).
### Metodi e this
Un oggetto può avere tra le sue proprietà anche funzioni, chiamate **metodi**:
```js
let a = { name: "pippo" };
a.saluta = function () {
  alert("Ciao sono " + this.name);
};
a.saluta(); // "Ciao sono pippo"
```

> [!quote] Definizione — this
> `this`, usato dentro un metodo, indica l'oggetto su cui il metodo è stato invocato. È valutato **a call-time** (quando la funzione viene chiamata), non nel punto in cui la funzione è definita — quindi la stessa funzione può avere un `this` diverso a seconda di come viene invocata.
> ```js
> let a = { name: "pippo" };
> let b = { name: "pluto" };
> function sayMyName() { alert("Ciao sono " + this.name); }
> a.saluta = sayMyName;
> b.saluta = sayMyName;
> a.saluta();   // "Ciao sono pippo"
> b.saluta();   // "Ciao sono pluto" — stessa funzione, this diverso
> sayMyName();  // this non è più l'oggetto (vedi sotto)
> ```
> Le tre invocazioni chiedono cosa stampano (slide p. 73): `"Ciao sono pippo"`, `"Ciao sono pluto"` e, per la funzione chiamata senza oggetto, `this` vale l'**oggetto globale** in modalità normale (`window` nel browser, dove *(extra, non da slide)* `window.name` è per default una stringa vuota) oppure `undefined` in modalità strict, dove l'accesso a `this.name` genera un `TypeError` *(extra, non da slide: il comportamento in strict mode)*.

> [!example] Esercizio: calcolatrice con oggetti e metodi (slide p. 75)
> Consegna: realizzare una calcolatrice con oggetti e metodi; permettere l'inserimento di due numeri (funzione `inserisci`); implementare i metodi `somma`, `sottrazione`, `moltiplicazione` e `divisione`. La slide non riporta la soluzione: *(extra, non da slide)* una possibile soluzione.
> ```js
> "use strict";
> let calc = {
>   a: 0,
>   b: 0,
>   inserisci(x, y) { this.a = Number(x); this.b = Number(y); },
>   somma() { return this.a + this.b; },
>   sottrazione() { return this.a - this.b; },
>   moltiplicazione() { return this.a * this.b; },
>   divisione() { return this.a / this.b; }
> };
> calc.inserisci("6", "3");
> calc.somma();            // 9
> calc.sottrazione();      // 3
> calc.moltiplicazione();  // 18
> calc.divisione();        // 2
> ```

Il caso della slide «Attenzione al contesto!» (p. 123) mostra il metodo **staccato dal suo oggetto**:
```js
let x = 9;
let module = { x: 81, getX: function () { return this.x; } };
module.getX();        // 81 — this è module
let getX = module.getX;
getX();               // fuori da un oggetto this non è più module
```
Fuori da un oggetto (scope globale) `this === window` nel browser: `getX()` ritorna quindi `window.x`. *(extra, non da slide)* Nel browser `let x = 9` non crea una proprietà di `window` (a differenza di `var`), quindi `getX()` vale `undefined`; in strict mode `this` è `undefined` e la chiamata lancia `TypeError: Cannot read properties of undefined (reading 'x')`.

> [!warning] this nelle arrow function
> Nelle **arrow function** `this` **non** viene rivalutato a call-time: si riferisce sempre al `this` dell'*outer scope*, cioè dell'oggetto/funzione che contiene l'arrow function al momento in cui è stata definita.
> ```js
> let a = { name: "pippo" };
> a.saluta = function () {
>   let x = () => alert("Ciao sono " + this.name); // this = a, ereditato dal metodo esterno
>   x(); // "Ciao sono pippo"
> };
> ```
> *(extra, non da slide)* Per questo motivo è sconsigliato usare un'arrow function come metodo diretto di un oggetto se serve che `this` punti all'oggetto stesso: erediterebbe il `this` dello scope globale, non dell'oggetto.
### Costruttori e prototipi
Per creare più oggetti con la stessa struttura si usa una funzione **costruttore**, invocata con `new`:
```js
function User(name) {
  this.name = name;
  this.isAdmin = false;
  // ritorna implicitamente this
}
let user = new User("Pippo");
```

> [!info] Cosa fa `new` quando chiama un costruttore
> 1. Crea un nuovo oggetto vuoto.
> 2. Lo passa al costruttore (la funzione), in modo che al suo interno ci si possa riferire a esso con `this`, e lo assegna a `this`.
> 3. Esegue il corpo della funzione (che imposta le proprietà su `this`).
> 4. Imposta il prototipo dell'oggetto creato uguale a `NomeCostruttore.prototype`.
> 5. Ritorna implicitamente `this` (l'oggetto appena creato e popolato).
>
> La slide sui costruttori (p. 77) elenca tre passi (oggetto vuoto assegnato a `this`, esecuzione della funzione, ritorno di `this`); quella sui prototipi (p. 129) aggiunge l'impostazione del prototipo.
>
> Se ci si dimentica `new` (esperimento proposto dalle slide), la funzione viene eseguita come una funzione normale: in modalità normale `this` è l'oggetto globale, quindi le proprietà (`this.name = name`) finiscono sull'oggetto globale e la chiamata ritorna `undefined`; in strict mode `this` è `undefined` e si ha un `TypeError` *(extra, non da slide: il dettaglio)* — un errore frequente e difficile da notare a prima vista.

In JavaScript ogni oggetto ha un **prototipo**, un altro oggetto da cui eredita proprietà e metodi (visibile con `oggetto.__proto__`). Quando si accede a una proprietà, JavaScript cerca prima tra le proprietà **proprie** dell'oggetto, poi tra quelle del suo prototipo, poi del prototipo del prototipo, e così via (*prototype chain*).

```js
function Student(name, age) {
  this.name = name;
  this.age = age;
}
Student.prototype.university = "Tor Vergata"; // proprietà condivisa da tutte le istanze
let pippo = new Student("Pippo", 20);
pippo.name;                                   // "Pippo" — proprietà propria
pippo.university;                             // "Tor Vergata" — ereditata dal prototipo
pippo.hasOwnProperty("university");           // false
pippo.__proto__.hasOwnProperty("university"); // true
```

> [!info] `prototype` vs `__proto__`
> `NomeFunzione.prototype` è l'oggetto che diventerà il prototipo di **tutte** le istanze create con quella funzione usata come costruttore: lo si imposta. `nomeIstanza.__proto__` è il prototipo effettivo di una **singola istanza** già creata, e punta allo stesso oggetto di `NomeFunzione.prototype`: lo si legge/verifica. Modificare `Student.prototype.university` dopo la creazione cambia il valore visto da tutte le istanze esistenti, perché condividono lo stesso oggetto prototipo.

Mettere un **metodo** sul prototipo del costruttore (`Student.prototype.saluta = function () {...}`), invece che assegnarlo dentro il costruttore stesso, è più efficiente in memoria: la funzione viene creata **una sola volta** e condivisa da tutte le istanze, invece di essere ricreata a ogni `new`. È la risposta alla domanda delle slide (p. 133) «Cosa scegliereste e perché?», che confronta `this.sayHi = function () {...}` nel costruttore di `Person` con `Person.prototype.sayHi = function () {...}`. Un'istanza può anche **ridefinire** (*override*) una proprietà ereditata assegnandola come propria: la ricerca si ferma alla proprietà propria.

Esercizio delle slide (p. 132): far dire il proprio nome ai tre studenti, implementando `sayName`. Soluzione breve *(extra, non da slide)*:
```js
function Student(name) { this.name = name; }
Student.prototype.sayName = function () { return "Mi chiamo " + this.name; };
new Student("Pippo").sayName(); // "Mi chiamo Pippo"
```

**Modificare o sostituire il prototipo dopo la creazione delle istanze** (slide p. 131). Aggiungere o cambiare una proprietà su `Costruttore.prototype` è visibile anche alle istanze **già create**, perché condividono quell'oggetto; **riassegnare** `Costruttore.prototype = {...}` crea invece un nuovo oggetto: le istanze già create restano legate al vecchio prototipo, solo quelle create dopo usano il nuovo.
```js
function Student(name, age) { this.name = name; this.age = age; }
Student.prototype.university = "TV";
let pippo = new Student("Pippo", 20);
let pluto = new Student("Pluto", 21);
pippo.university;                              // "TV"
pluto.university;                              // "TV"

Student.prototype.university = "La Sapienza";  // modifica lo stesso oggetto prototipo
pippo.university;                              // "La Sapienza"
pluto.university;                              // "La Sapienza"

Student.prototype = { university: "La terza" }; // nuovo oggetto: le istanze esistenti non lo vedono
pippo.university;                              // "La Sapienza"
pluto.university;                              // "La Sapienza"
new Student("Topolino", 22).university;        // "La terza"
```

> [!question] Domanda tipica d'esame
> `function Persona() {} Persona.prototype.citta = "Roma"; let prima = new Persona(); Persona.prototype = { citta: "Milano" }; let seconda = new Persona();` perché `prima.citta` e `seconda.citta` sono diversi (`"Roma"` e `"Milano"`)? Risposta: `prima` è stata creata quando il prototipo era il primo oggetto e resta **legata a quel vecchio oggetto**; la riassegnazione `Persona.prototype = {...}` non modifica le istanze già create, ma solo quelle create dopo, come `seconda`. Se invece, **senza riassegnare** `Persona.prototype`, si aggiungesse una proprietà con `Persona.prototype.nome = "a"` dopo aver creato `prima` e `seconda`, entrambe la vedrebbero (stesso oggetto prototipo): `prima.nome + " " + seconda.nome` darebbe `"a a"`.
### bind, call e apply
`bind`, `call` e `apply` permettono di controllare esplicitamente a cosa punta `this` in una funzione (una funzione, in JS, è essa stessa un oggetto — un *Function object* — e questi sono suoi metodi).

| Metodo | Effetto |
|---|---|
| `f.bind(obj)` | Ritorna una **nuova funzione** con `this` fissato a `obj` (non la esegue subito) |
| `f.call(obj, a, b)` | Esegue **subito** `f` con `this = obj`, passando gli argomenti **elencati** |
| `f.apply(obj, [a, b])` | Come `call`, ma gli argomenti sono passati come **array** |

```js
let a = { id: 10 };
let x = function () { return this.id; };
let w = x.bind(a);
x();  // undefined — this non è a
w();  // 10 — this è ora sempre a
```

Esempi delle slide per `apply` e `call` (il primo argomento è il valore di `this`; con `undefined` la funzione non ha un oggetto di riferimento):
```js
myFunction.apply(myObject, ["Susan", "teacher"]);        // argomenti come array
myFunction.call(undefined, "Claude", "mathematician");   // argomenti elencati
```
`apply` permette anche di usare un costruttore senza `new`: `Car.apply(new_car, ["FIAT", "500", 1936])`, con `let new_car = new Object()`, imposta le proprietà `maker`, `model`, `year` su `new_car` come farebbe `new Car("FIAT", "500", 1936)` (ma senza collegare il prototipo di `Car`).

Un **global object** esiste sempre nel global scope: nel browser è `window`, in Node.js è `global` (vedi [[08 - Node.js e npm]]), nei web worker è `WorkerGlobalScope`. Nel browser, una variabile globale dichiarata con `var` (o creata implicitamente dimenticando `let`/`var`, vedi il warning sopra) diventa una proprietà di `window`; la slide precisa che in Node.js non è così:
```js
var foo = "foobar";
foo === window.foo; // true nel browser (not in NodeJS)
```
Come nota la slide «Copiare un oggetto» (p. 137), duplicare un oggetto è **pericoloso** con la semplice assegnazione e va fatto a mano, proprietà per proprietà; resta aperto anche il problema del prototipo, che una copia manuale non eredita.
### Array e stringhe
Un **array** è un contenitore ordinato di variabili, anche di tipi diversi tra loro; è in realtà un oggetto con proprietà numeriche e metodi dedicati. Ogni elemento ha un **indice** che parte da 0.

```js
let myFirstArray = [5, "ciao", false, undefined];
```

| Operazione | Sintassi |
|---|---|
| Creare | `let arr = [element0, element1, ...];` (preferito a `new Array()`) |
| Modificare un elemento | `arr[0] = "nuovo valore";` |
| Aggiungere in fondo / in testa | `arr.push("ciao")` / `arr.unshift("ciao")` |
| Rimuovere l'ultimo / il primo | `arr.pop()` / `arr.shift()` (li ritornano) |
| Rimuovere senza "spostare" gli indici | `delete arr[10]` (lascia un buco, `length` non cambia) |
| Lunghezza | `arr.length` (assegnare un indice oltre la fine estende l'array e `length`) |
| Svuotare | `arr = []` oppure `arr.length = 0` |

> [!warning] slice vs splice
> `slice(start, end)` **non modifica** l'array: ritorna una nuova porzione. `splice(index, n)` invece **modifica** l'array originale, rimuovendo `n` elementi a partire da `index` e ritornando quelli rimossi.
> ```js
> let a = ["a", "b", "c", "d", "e"];
> a.slice(1, 4);   // ["b", "c", "d"] — a resta invariato
> let b = ["1", "2", "3", "4", "5"];
> b.splice(3, 2);  // ["4", "5"] — b ora è ["1", "2", "3"]
> ```

> [!example] Esercizio sull'array dei giorni (slide p. 83)
> L'array `giorno` contiene `"lunedì"`, ..., `"domenica"` e `giorno[0]` dà `"lunedì"`. In America la settimana parte da domenica: trasformare l'array mettendo `"domenica"` all'inizio. La slide non riporta la soluzione: *(extra, non da slide)* una possibile soluzione.
> ```js
> let giorno = ["lunedì", "martedì", "mercoledì", "giovedì", "venerdì", "sabato", "domenica"];
> giorno.unshift(giorno.pop());   // pop toglie "domenica" in fondo, unshift la mette in testa
> console.log("Il primo giorno della settimana è " + giorno[0]);
> // Il primo giorno della settimana è domenica
> ```

Metodi comuni: `forEach` per iterare, `join(separatore)` per concatenare in una stringa, `indexOf(valore)` per cercare la prima occorrenza:
```js
let colors = ["red", "green", "blue"];
colors.forEach(function (color) { console.log(color); });
colors.join(" - ");     // "red - green - blue"
["a", "b", "a"].indexOf("b"); // 1
```

**`map`** trasforma ogni elemento producendo un **nuovo array** della stessa lunghezza; il callback riceve `(item, index, array)`:
```js
["pippo", "pluto", "paperino"].map((item, index, array) => item.length); // [5, 5, 8]
```

**`reduce`** calcola un **singolo valore** a partire da tutto l'array; il callback riceve `(accumulator, item, index, array)` e un valore iniziale opzionale — `accumulator` è il risultato della chiamata precedente:
```js
[1, 2, 3].reduce((acc, item) => acc + item); // 6
```

> [!example] Esercizio sull'array names (slide p. 94)
> Dato `let names = ['mario', 'giovanna', 'pippo'];` modificare l'array per: 1) convertire i nomi in maiuscolo; 2) aggiungere `"Dr. "` prima del nome; 3) calcolare chi ha il nome più lungo. La slide non riporta la soluzione: *(extra, non da slide)* una possibile soluzione con `map` e `reduce`.
> ```js
> let names = ['mario', 'giovanna', 'pippo'];
> names = names.map(n => "Dr. " + n.toUpperCase());
> // [ 'Dr. MARIO', 'Dr. GIOVANNA', 'Dr. PIPPO' ]
> names.reduce((a, b) => (b.length > a.length ? b : a));
> // 'Dr. GIOVANNA'
> ```

*(extra, non da slide; nell'esempio del docente sotto è usato solo `find`, `filter` è un'aggiunta)* **`filter`** ritorna un nuovo array con solo gli elementi che soddisfano una condizione; **`find`** ritorna il **primo** elemento che soddisfa una condizione (o `undefined` se nessuno la soddisfa):

> [!example] Carrello e-commerce con find e reduce (js-dom/ecomm/cart.js)
> ```js
> "use strict";
> const products = [
>   {'id': 1, 'description': 'pasta', 'price': 1.5, 'availability': 10},
>   {'id': 2, 'description': 'bread', 'price': 1.0, 'availability': 20},
>   {'id': 3, 'description': 'milk', 'price': 0.5, 'availability': 30},
>   {'id': 4, 'description': 'eggs', 'price': 2.0, 'availability': 15},
>   {'id': 5, 'description': 'cheese', 'price': 3.0, 'availability': 5}
> ];
> let cart = {
>   items: [],
>   total_price: 0,
>   addItem(productId, quantity) {
>     const product = products.find(p => p.id === productId); // primo prodotto con quell'id
>     if (product && product.availability >= quantity) {
>       this.items.push({ product, quantity });
>       product.availability -= quantity;
>       this.total_price = this.items.reduce((acc, item) => acc + item.product.price * item.quantity, 0);
>     } else {
>       console.log('Product not available in the requested quantity.');
>     }
>   },
>   clearCart() {                       // rimette in magazzino le quantità e svuota il carrello
>     this.items.forEach(item => { item.product.availability += item.quantity; });
>     this.items = [];
>     this.total_price = 0;
>   }
> };
> cart.addItem(1, 2); cart.addItem(2, 1);
> cart.total_price; // 4 (2 × 1.5 + 1 × 1.0)
> ```
> Notare `this.items` dentro `addItem`: `this` funziona anche nei metodi scritti con la sintassi abbreviata (`addItem(productId, quantity) {...}`) perché, al momento della chiamata `cart.addItem(...)`, `this` è `cart`.

Per le **stringhe**, oltre alla concatenazione con `+`, sono utili: `indexOf`, `slice` (non modifica), `trim` (rimuove spazi a inizio/fine), `charAt(i)`, `toUpperCase`/`toLowerCase`, `replace`:
```js
"ciao ciao".replace("ciao", "bye");     // "bye ciao" — solo la prima occorrenza
"ciao ciao".replace(/ciao/g, "bye");    // "bye bye" — con regex globale, tutte
```

Dalla ES6 esistono i **template literal**, delimitati da backtick, che permettono interpolazione di espressioni con `${...}`:
```js
let lessonNumber = 3;
console.log(`Questa è la lezione numero ${lessonNumber} di javascript`);
```

Come gli array, anche le **stringhe sono oggetti**: `let s = "ciao"` è preferibile a `new String("ciao")`.
### Oggetti built-in e gestione degli errori
JavaScript mette a disposizione diversi oggetti *built-in* con metodi pronti all'uso.

**`Date`** gestisce le date (non esiste un tipo primitivo "data"):
```js
let today = new Date();                           // data di oggi
let xmas = new Date("December 25, 1995 13:30:00"); // da stringa
xmas = new Date(1995, 11, 25);                    // anno, mese (0-based!), giorno
xmas = new Date(1995, 11, 25, 9, 30, 0);          // con ore, minuti, secondi
xmas.getMonth();    // 11
xmas.getFullYear(); // 1995
xmas.getTime();     // millisecondi dal 1/1/1970 (epoch)
```

> [!warning] getMonth() è zero-based
> In `new Date(anno, mese, giorno)` e in `.getMonth()`, i mesi vanno da `0` (gennaio) a `11` (dicembre) — un classico trabocchetto.

**`typeof`** distingue i tipi primitivi (`typeof 62` → `"number"`); **`instanceof`** verifica se un oggetto discende da un certo costruttore (`theDay instanceof Date` → `true`; la slide usa `let theDay = new Date(1995, 12, 17);`, dove il mese `12` va oltre dicembre e produce **gennaio 1996**: `theDay.getFullYear()` ritorna `1996`). `typeof true` → `"boolean"`. **`Math`** offre funzioni matematiche: trigonometriche (`sin`, `cos`, `tan`), esponenziali (`pow`, `exp`, `log10`...), `min`/`max`, `random()` (numero casuale tra 0 e 1), la costante `PI`, arrotondamenti (`round`, `trunc`).

**`JSON`** converte oggetti in stringhe e viceversa — fondamentale per scambiare dati con un server (vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]] e [[09 - Express e API REST]]):
```js
JSON.stringify(object);     // oggetto → stringa
JSON.parse(objectString);   // stringa → oggetto
```

**`window`** rappresenta la finestra del browser ed è il *global object* lato client. I metodi già usati negli esempi precedenti, `alert()`, `confirm()`, `prompt()`, sono in realtà suoi metodi:

> [!info] Metodi principali di `window`
>
> | Metodo | Effetto |
> |---|---|
> | `alert(msg)` | mostra un messaggio in una finestra di dialogo |
> | `confirm(msg)` | chiede conferma (OK/Annulla) e ritorna un booleano |
> | `prompt(msg)` | chiede un testo in una finestra di dialogo e lo ritorna come stringa |
> | `open()` / `close()` | apre/chiude una finestra del browser |
> | `print()` | stampa la pagina |
> | `scrollTo()` | scorre la pagina fino a delle coordinate |
> | `setTimeout(funzione, time)` / `setInterval(funzione, time)`, `clearTimeout`/`clearInterval` | timer: richiamano la funzione dopo `time` millisecondi, una volta o ciclicamente, oppure annullano il timer — vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]] |

Esercizi delle slide (p. 104): stampare «ciao» ogni 5 secondi per un massimo di 4 volte; ricaricare una pagina ogni X secondi (ad es. il sito di un giornale online). Soluzione breve *(extra, non da slide)*:
```js
let volte = 0;
const id = setInterval(function () {
  console.log("ciao");
  if (++volte === 4) clearInterval(id);   // si ferma dopo 4 volte
}, 5000);
// ricaricare la pagina ogni X secondi: setInterval(() => location.reload(), X * 1000);
```

Infine, la gestione degli **errori**. Le eccezioni indicano che qualcosa è andato storto (ad es. `jnkdfsnjkfd();` → `ReferenceError: jnkdfsnjkfd is not defined`). Un'eccezione può essere qualsiasi tipo di dato, viene "lanciata" con `throw` e può essere "gestita" con `try`/`catch`. Quando viene lanciata: 1. interrompe la normale esecuzione; 2. si cerca una routine in grado di risolvere il problema (`catch`); 3. se è gestita, il flusso continua da dopo il blocco `catch`. Il blocco `finally`, se presente, viene eseguito sempre, sia in caso di errore sia no.
```js
function getMonthName(monthId) {
  if (monthId == 1) return "Gennaio";
  else if (monthId == 2) return "Febbraio";
  // ... fino a 12 "Dicembre"
  throw "Il mese non è valido"; // c'è un problema: lancio l'eccezione
}
function f(myMonth) {
  try {
    return getMonthName(myMonth);
  } catch (e) {
    return "unknown"; // gestisco l'eccezione (la slide assegna monthName = "unknown")
  } finally {
    // eseguita in ogni caso (es. chiudere una risorsa)
  }
}
```
L'oggetto **`Error`** è la struttura dati standard per un'eccezione, con due proprietà: `name` (errore sintetico: la slide fa l'esempio `"DOMException"`; con `new Error` il nome è `"Error"`) e `message` (descrizione verbosa dell'errore): `throw new Error("Il messaggio");`. Esistono tipi di errore più specifici (`ReferenceError`, `TypeError`, `URIError`...).
## Il DOM (Document Object Model)
Il linguaggio da solo non basta: serve un modo per collegare JavaScript alla pagina che l'utente vede. Come fa un programma JS ad aggiungere una riga a una tabella HTML già caricata? Non di certo editando il testo HTML sorgente — serve un'interfaccia.
### Cos'è il DOM e l'albero dei nodi
> [!quote] Definizione — DOM
> Il **Document Object Model (DOM)** è un'interfaccia di programmazione per HTML (e XML), standard **W3C**: fornisce una mappa strutturata del documento e i metodi per interfacciarsi con i suoi elementi — senza dover editare il testo HTML a mano.

Ogni elemento della pagina è un **nodo**; l'elemento radice è `document`. I nodi formano un **albero**: `html` è la radice, con `head` (che contiene `title`, `meta`) e `body` (che contiene i vari `div`, `p`, `h2`, `a`...) come suoi rami.
### Selezionare elementi
Esempio delle slide: `let foo = document.getElementById("miodiv").innerHTML;` — `foo` contiene il contenuto HTML del div con id `miodiv`.

| Metodo | Ritorna |
|---|---|
| `document.getElementById("miodiv")` | il nodo con quell'id |
| `document.getElementsByTagName("p")` | una `NodeList` di tutti gli elementi `<p>` |
| `document.getElementsByClassName("myclass")` | una `NodeList` degli elementi con quella classe |
| `document.querySelector("p .warning")` *(extra, non da slide)* | il **primo** elemento che soddisfa il selettore CSS |
| `document.querySelectorAll("p .warning")` | una `NodeList` di tutti gli elementi che soddisfano il selettore CSS |

`querySelector`/`querySelectorAll` accettano qualunque selettore CSS valido (vedi [[03 - CSS - selettori, specificità e box model]]), e sono quindi i più flessibili *(extra, non da slide: le slide trattano solo `querySelectorAll`)*.

> [!warning] NodeList e HTMLCollection
> Le slide dicono che anche `getElementsByTagName` e `getElementsByClassName` ritornano una `NodeList`; *(extra, non da slide)* per la precisione ritornano una **`HTMLCollection`**, che si aggiorna da sola quando il DOM cambia, mentre la `NodeList` di `querySelectorAll` è una fotografia statica. Per l'uso di base (indice `[]` e `.length`) si comportano allo stesso modo.

> [!info] NodeList non è un array
> Una `NodeList` **assomiglia** a un array (è indicizzabile con `[]` e ha `.length`) ma non ne ha tutti i metodi: per usare `map`/`filter`/`reduce` *(extra, non da slide)* serve prima convertirla con `Array.from(paragraphs)`.

> [!question] Domanda tipica d'esame
> *(extra, non da slide: `querySelector` non è nelle slide)* Che differenza c'è tra `getElementById` e `querySelector`? Risposta: `getElementById` accetta solo un id (senza `#`) e ritorna un singolo nodo; `querySelector` accetta un **qualsiasi selettore CSS** (`#id`, `.classe`, `tag`, combinazioni) e ritorna il primo elemento che corrisponde.
### Leggere e modificare un nodo
Gli attributi HTML standard vengono convertiti automaticamente in proprietà dell'oggetto DOM corrispondente (`<body id="test">` → `body.id === "test"`). Per attributi generici si usano `getAttribute`/`setAttribute`:
```js
let oldSrc = myImage.getAttribute("src");   // leggere un attributo
myImage.setAttribute("src", "otherimage.jpg"); // scriverlo
```

`innerHTML` legge/scrive il contenuto **HTML** di un nodo (il browser lo interpreta come markup): `myP.innerHTML = "<p>New text</p>";`

> [!warning] innerHTML e sicurezza (XSS)
> *(extra, non da slide: le slide trattano solo `innerHTML`)* Scrivere in `innerHTML` del testo proveniente dall'utente (non fidato) senza sanificarlo permette di iniettare ed eseguire HTML/script arbitrari nella pagina (**XSS**, *Cross-Site Scripting*), perché il browser interpreta il contenuto come markup. Se serve inserire solo **testo**, `textContent` è la scelta sicura: legge/scrive esclusivamente testo, senza interpretare markup.
> ```js
> elemento.textContent = userInput; // sicuro: userInput non viene mai interpretato come HTML
> elemento.innerHTML = userInput;    // pericoloso se userInput non è fidato
> ```

Anche lo **stile CSS** si legge/modifica via JS con la proprietà `style`; le proprietà CSS composte si scrivono in *camelCase*: `myP.style.backgroundColor = "#fff";` (background-color → backgroundColor).

*(extra, non da slide)* Per gestire le **classi CSS** invece di manipolare `className` come stringa, si usa la proprietà `classList`, più espressiva: `elemento.classList.add("attiva")`, `.remove("attiva")`, `.toggle("attiva")`, `.contains("attiva")`.

> [!example] Esercizio «capture the DIV» (slide p. 150, soluzione `js-dom/capturediv/script.js`)
> Consegna: spostare dinamicamente il div ogni X secondi e, a ogni spostamento, alternare il colore di sfondo del div e della pagina tra bianco e nero. Il div `#clickme` è nero, 80 × 30 px; cliccandolo compare «Hai vinto».
> ```js
> "use strict";
> function haiVinto(e) {
>   alert('Hai vinto');
> }
> const targetDiv = document.getElementById('clickme');
> const body = document.body; // document.getElementsByTagName('body')[0];
>
> // inizializziamo i colori
> targetDiv.style.backgroundColor = 'black';
> body.style.backgroundColor = 'white';
> let divIsBlack = true;
>
> function moveTheDiv() {
>   if (divIsBlack) {
>     targetDiv.style.backgroundColor = 'white';
>     body.style.backgroundColor = 'black';
>   } else {
>     targetDiv.style.backgroundColor = 'black';
>     body.style.backgroundColor = 'white';
>   }
>   divIsBlack = !divIsBlack;
>   targetDiv.style.marginLeft = Math.random() * 500 + 'px';
>   targetDiv.style.marginTop = Math.random() * 500 + 'px';
> }
>
> targetDiv.addEventListener('click', haiVinto);
> const MY_INTERVAL = 500;
> setInterval(moveTheDiv, MY_INTERVAL);   // ogni 500 ms
> ```
### Creare e rimuovere elementi
```js
var newDiv = document.createElement("div");    // crea un nodo (non ancora visibile)
var ourText = document.createTextNode("Ciao!"); // nodo di solo testo
var ourDiv = document.getElementById("mydiv");
newDiv.appendChild(ourText);
ourDiv.appendChild(newDiv);                     // li mettiamo nella pagina
```

Altri metodi per inserire/sostituire/rimuovere nodi, tutti relativi a un nodo genitore:
```js
ourDiv.insertBefore(newHeading, para);  // inserisce newHeading prima di para
ourDiv.replaceChild(newImg, oldImg);    // sostituisce oldImg con newImg
parentDiv.removeChild(removeMe);        // rimuove removeMe da parentDiv
```

*(extra, non da slide)* Il DOM moderno offre alternative più dirette: `elemento.append(...)` (accetta anche più nodi o semplici stringhe di testo, senza dover creare un text node a parte) e `elemento.remove()` (rimuove l'elemento da solo, senza dover risalire al genitore).

> [!example] Aggiungere dinamicamente un elemento a una lista (esercizio delle slide pp. 153-156, soluzione ufficiale `iwant.html` e `iwant.js` + js-dom/dynlist)
> Consegna: aggiungere dinamicamente un elemento a una lista, a ogni click su un pulsante.
> ```html
> <!-- iwant.html (corpo della pagina) -->
> <h1>I want:</h1>
> <ol id="wish-list">
>   <li>Ride a bycicle</li>
>   <li>Break free</li>
> </ol>
> <button id="add-element">Add what do you want</button>
> <script src="iwant.js"></script>
> ```
> ```js
> // iwant.js
> "use strict";
> function addElementToList() {
>   let whatElseIWant = ["it all", "it now"];
>   let whatIWant;
>
>   whatIWant = whatElseIWant[Math.floor(Math.random() * whatElseIWant.length)];
>   let newLi = document.createElement("li");
>   let newText = document.createTextNode(whatIWant);
>   newLi.appendChild(newText);
>   document.getElementById("wish-list").appendChild(newLi);
> }
>
> document
>   .getElementById("add-element")
>   .addEventListener("click", addElementToList);
> ```
> L'esempio del docente `js-dom/dynlist/main.js` applica esattamente lo stesso pattern (con `prompt()` al posto della lista casuale), e mostra in un commento l'alternativa più diretta: `newListItem.textContent = newWish;` al posto di `createTextNode` + `appendChild`. L'esempio `js-dom/dynimg/main.js` applica invece `setAttribute` per cambiare un'immagine al click, con un'arrow function come callback diretta di `addEventListener` (vedi [[#Eventi]]):
> ```js
> "use strict";
> const homerImages = [ /* tre URL di immagini */ ];
> const myImage = document.getElementById("my-image");
> const changeImgBtn = document.getElementById("change-img");
> let imgIdx = 0;
>
> changeImgBtn.addEventListener("click", () => {
>     //myImage.src = homerImages[imgIdx];                // alternativa a setAttribute
>     myImage.setAttribute("src", homerImages[imgIdx]);
>     imgIdx = (imgIdx + 1) % homerImages.length;         // torna a 0 dopo l'ultima
> });
> ```
> `textContent` e `innerHTML` sono usati allo stesso modo con i dati ricevuti da un server in [[07 - JavaScript asincrono, Promise, fetch e CORS]]: `textContent` per testo semplice, `innerHTML` con un template literal per inserire markup (`<p>${data.address.street}</p>`).
## Eventi
Gli eventi collegano le azioni dell'utente (click, digitazione, invio di un form...) al codice JavaScript: senza eventi, uno script potrebbe solo eseguire una volta al caricamento della pagina.
### Associare un evento a un elemento
Esistono tre modi per collegare una funzione a un evento:

1. **Con un attributo HTML**: `<body onclick="myFunction();">` — *(extra, non da slide)* mescola HTML e JS, sconsigliato nel progetto d'esame (vedi [[#Includere ed eseguire JavaScript]]).
2. **Con una proprietà**: `window.onclick = myFunction;` oppure `document.getElementById("miodiv").onclick = ...` — *(extra, non da slide)* assegnare una seconda funzione **sovrascrive** la prima.
3. **Con `addEventListener`**: `window.addEventListener("click", myFunction);` — *(extra, non da slide)* lo standard moderno, permette di registrare **più listener** sullo stesso evento sullo stesso elemento senza che si sovrascrivano.

Esempio delle slide per il primo modo (attributo `onclick`, valore: codice JavaScript): scrivere CIAO dentro un div quando si preme un pulsante.
```html
<div id="prova"></div>
<button onclick="document.getElementById('prova').innerHTML = 'CIAO';">Premi qua</button>
```
Esercizio delle slide (p. 146): associare una funzione JS al click di un div, presentando un `alert` all'utente. Soluzione breve *(extra, non da slide)*:
```js
document.getElementById("miodiv").addEventListener("click", function () {
  alert("Hai cliccato il div");
});
```

> [!warning] "click", non "onclick", con addEventListener
> *(extra, non da slide)* Con `addEventListener` il nome dell'evento **non ha il prefisso `on`**: si scrive `addEventListener("click", fn)`, non `addEventListener("onclick", fn)`. Il prefisso `on` si usa solo per gli attributi HTML (`onclick`) e le proprietà (`.onclick`).

| Evento | Quando scatta |
|---|---|
| `onblur` / `onfocus` | un elemento perde/prende il focus *(la slide p. 144 scrive «prende/perde», che è un errore: `onblur` scatta quando l'elemento perde il focus, `onfocus` quando lo prende)* |
| `onchange` | il contenuto di un form cambia |
| `onclick` | click del mouse |
| `onerror` | errore nel caricamento di immagini o del documento |
| `onload` | la pagina ha finito di caricarsi |
| `onkeydown` / `onkeypress` / `onkeyup` | un tasto viene premuto/tenuto premuto/rilasciato |
| `onmousedown` / `onmouseup` | un bottone del mouse è premuto/rilasciato |
| `onmousemove` / `onmouseout` / `onmouseover` | il mouse si sposta/esce da/entra in un elemento |
| `onsubmit` | è stato premuto il pulsante submit di un form |

*(extra, non da slide, ma essenziale)* Quando un gestore di evento viene eseguito, riceve come parametro un **oggetto evento** con le informazioni su cosa è successo (es. `event.target`, l'elemento che ha effettivamente generato l'evento).
### Click, submit e preventDefault *(extra, non da slide)*
Un caso speciale è l'evento **`submit`** su un `<form>`: per default, quando scatta, il browser invia il form e **ricarica/naviga** verso l'URL indicato in `action` — comportamento che va quasi sempre disattivato quando si vuole gestire l'invio via JavaScript (es. con `fetch`, vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]]).

> [!quote] Definizione — preventDefault
> `event.preventDefault()` annulla il comportamento **predefinito** del browser per quell'evento (l'invio/reload di un form, la navigazione di un link...), ma non ferma la propagazione dell'evento verso gli antenati (vedi il paragrafo su bubbling e delegazione, più avanti). Si chiama dentro il gestore dell'evento.

> [!example] Intercettare il submit di un form *(extra, non da slide, ma richiesto dal progetto d'esame)*
> ```js
> const form = document.querySelector("#contatto");
> form.addEventListener("submit", function (event) {
>   event.preventDefault(); // niente reload della pagina
>   // qui si leggono i valori, si valida, eventualmente si chiama fetch(...)
> });
> ```

*(extra, non da slide)* L'evento **`input`** scatta a ogni modifica del contenuto di un campo (praticamente a ogni carattere digitato), prima di `change` (che scatta solo quando il campo perde il focus con un valore diverso da prima): utile per validazione "live" mentre l'utente scrive.
### Bubbling e delegazione *(extra, non da slide)*
Quando un evento scatta su un elemento, non si ferma lì: **si propaga** (*bubbling*) verso l'alto, attraverso tutti gli antenati dell'elemento fino a `document`. Se anche un antenato ha un listener per lo stesso tipo di evento, viene eseguito anche quello.

Questo rende possibile la **delegazione degli eventi**: invece di registrare un listener su *ogni* elemento figlio (scomodo se i figli vengono creati dinamicamente, come nella lista di `dynlist`), se ne registra **uno solo sul genitore**, e dentro il gestore si controlla `event.target` per sapere quale figlio ha effettivamente generato l'evento.

> [!example] Delegazione su una lista dinamica
> ```js
> document.getElementById("wish-list").addEventListener("click", function (event) {
>   if (event.target.tagName === "LI") {
>     event.target.remove(); // rimuove l'elemento su cui si è cliccato
>   }
> });
> ```
> Con la delegazione, anche i `<li>` aggiunti *dopo* la registrazione del listener rispondono correttamente al click, senza bisogno di registrare un listener apposta per ognuno.
### Validazione di un form lato client con JavaScript *(extra, non da slide)*
[[02 - HTML semantico e form#Validazione nativa lato client|La validazione HTML5 nativa]] (attributi `required`, `pattern`, `minlength`...) copre i casi semplici senza scrivere JavaScript. Quando serve una logica più ricca (confrontare due campi, messaggi personalizzati, validare mentre l'utente digita), si intercetta il `submit`, si blocca l'invio di default e si controllano i valori a mano con `element.value`:

> [!example] Validazione minimale sul submit
> ```js
> form.addEventListener("submit", function (event) {
>   event.preventDefault();
>   const nome = document.querySelector("#nome").value.trim();
>   if (nome === "") {
>     document.querySelector("#errore").textContent = "Il nome è obbligatorio.";
>     return; // non procede
>   }
>   // dati validi: qui si invierebbero al server, vedi nota 07
> });
> ```

> [!warning] La validazione lato client non basta
> Come già visto per la validazione HTML5 in [[02 - HTML semantico e form#Validazione nativa lato client]], anche la validazione scritta a mano in JavaScript gira nel browser dell'utente e può essere **aggirata** (JavaScript disabilitato, richiesta inviata senza passare dal form). Serve sempre anche una validazione **lato server**, trattata in [[09 - Express e API REST]].
## Debug e console
Le slide (p. 56) mostrano il debug con Chrome: impostare un **breakpoint**, ispezionare il **valore delle variabili** e la **pila delle chiamate**. *(extra, non da slide)* Gli strumenti da sviluppatore del browser (**DevTools**, F12 o tasto destro → Ispeziona) sono indispensabili per scrivere e correggere JavaScript.

> [!info] Pannelli DevTools più utili per JavaScript *(extra, non da slide)*
> - **Console**: mostra l'output di `console.log(...)` e permette di eseguire comandi JS direttamente nella pagina.
> - **Sources**: permette di impostare **breakpoint** su una riga di codice; quando l'esecuzione arriva lì si ferma, ed è possibile ispezionare il **valore delle variabili** in quel momento e la **pila delle chiamate di funzioni** (*call stack*, chi ha chiamato chi) per capire come si è arrivati a quel punto.
> - **Elements**: ispeziona e modifica live il DOM della pagina.
> - **Network**: mostra le richieste HTTP fatte dalla pagina (essenziale per `fetch`, vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]]).

*(extra, non da slide)* Lo stesso vale, lato server, per il debug di Node.js con `node --inspect` o gli strumenti dell'editor (vedi [[08 - Node.js e npm]]).
## Verso la comunicazione asincrona
Le slide finali del corso trattano la comunicazione asincrona: i **timer** dell'oggetto `window` (vedi [[#Oggetti built-in e gestione degli errori]]), **`XMLHttpRequest`** (la prima API per fare richieste HTTP da JavaScript), la **same-origin policy** e il meccanismo **CORS**, oltre a `JSON` come formato per scambiare dati strutturati con un server. *(extra, non da slide)* Il codice moderno usa `fetch` con `Promise` e `async`/`await` al posto di `XMLHttpRequest`: tutti questi argomenti sono trattati per esteso — insieme a `XMLHttpRequest` come predecessore storico e al dettaglio delle richieste CORS *simple* e *preflight* — in [[07 - JavaScript asincrono, Promise, fetch e CORS]].
## Riferimenti
- `Materiale Didattico/Slide/javascript_2026.pdf` (170 pagine, contate con `pdfinfo`): pp. 1-22 introduzione, storia, ruolo, Node.js, framework, vanilla JS, compatibilità, transpiler e polyfill, caratteristiche del linguaggio, garbage collector; pp. 23-28 hello world, console e inclusione dello script; pp. 29-42 variabili, tipi, conversioni, strict mode (39), modali (40) ed esercizi; pp. 43-49 operatori, if, ternario, switch, cicli; pp. 50-62 funzioni, scope (53-54), debug (56), callback, arrow function (60), «cattiva programmazione» (61-62); pp. 63-77 oggetti, copia (66), garbage collection (68-70), metodi e `this` (71-74), costruttori (76-77); pp. 78-96 tipi primitivi e metodi, array e stringhe; pp. 97-107 oggetti built-in (Date 98, typeof/instanceof 99, Math 100, JSON 101, window 102-104, eccezioni 105-107); pp. 108-120 funzioni approfondite, `var`/`let` (109), closure (113-116), IIFE (117-119), quiz (120); pp. 121-138 `this` a call-time, prototipi (124-133), bind, apply e call (134-136), copia di oggetti (137), global object (138); pp. 139-156 DOM, eventi (144-146), caricamento degli script (147), nodi (148-153), soluzione della lista (154-156); pp. 157-170 comunicazione asincrona (XMLHttpRequest, JSON, CORS — vedi [[07 - JavaScript asincrono, Promise, fetch e CORS]]).
- `Materiale Didattico/Esempi/01 - kitchen/kitchen-js.html` (script inline con jQuery, uso di `onload`).
- `Materiale Didattico/Esempi/js-dom/capturediv/` (selezione, `style`, `addEventListener`, `setInterval`).
- `Materiale Didattico/Esempi/js-dom/dynimg/` (`setAttribute`, arrow function come callback).
- `Materiale Didattico/Esempi/js-dom/dynlist/` (`createElement`, `createTextNode`, `appendChild`, `prompt`).
- `Materiale Didattico/Esempi/js-dom/ecomm/` (oggetti, metodi, `find`, `reduce`).
