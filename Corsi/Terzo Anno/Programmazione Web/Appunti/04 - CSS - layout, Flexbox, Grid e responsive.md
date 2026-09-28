---
tags:
  - programmazione-web
  - css
slide:
  - "PW07-CSS-3.pdf"
  - "PW08-CSS-HTML-4.pdf"
  - "PW09-CSS-HTML-5.pdf"
  - "PW10-CSS-HTML-6.pdf"
---
# CSS - layout, Flexbox, Grid e responsive
Dopo [[03 - CSS - selettori, specificità e box model]], che spiega come si seleziona un elemento e come si calcola la dimensione del suo box, questa nota affronta il problema successivo: come **disporre i box nella pagina** e come far sì che la pagina funzioni bene su schermi di dimensioni molto diverse (da un telefono a un monitor desktop). Si parte dal comportamento di base di ogni elemento (`display`, incluso lo stile delle liste), si passa a come toglierlo dal flusso normale (`position`, `float`), poi ai due sistemi di layout moderni (**Flexbox** e **Grid**, con il criterio per scegliere tra i due), e infine al design responsive (layout fisso e fluido, viewport, media query, immagini responsive, variabili CSS, Bootstrap).
## Il flusso normale e la proprietà display
Ogni elemento HTML, prima di ricevere qualunque altra regola CSS, viene disposto dal browser secondo il **flusso normale** (normal flow): gli elementi si susseguono nell'ordine del documento, uno dopo l'altro. Il modo in cui un elemento si comporta all'interno di questo flusso è deciso dalla proprietà `display`.

> [!quote] Definizione — display
> `display` stabilisce il **tipo di box** generato da un elemento e come si comporta rispetto agli elementi vicini. I valori principali visti a lezione sono `inline` (il default per molti tag), `block`, `inline-block` e `none`; CSS ne definisce molti altri (`list-item`, `table`, `flex`, `grid`, …) che verranno introdotti quando servono.

- **`block`**: l'elemento occupa **tutta la larghezza disponibile** del contenitore e va sempre a capo prima e dopo (es. `<div>`, `<p>`, `<h1>`). Rispetta `width`, `height`, tutto il `padding`/`margin`/`border` (vedi [[03 - CSS - selettori, specificità e box model#Box model]]).
- **`inline`**: l'elemento occupa **solo lo spazio necessario al suo contenuto** e sta sulla stessa riga degli elementi vicini (es. `<span>`, `<a>`, `<strong>`). *Ignora* `width` e `height`, e ignora anche `margin-top`/`margin-bottom` (li accetta solo `left`/`right`).
- **`inline-block`**: comportamento ibrido, molto usato prima dell'arrivo di Flexbox: l'elemento sta in riga come un `inline`, ma accetta `width`, `height` e tutti i margini come un `block`.
- **`none`**: l'elemento **non viene disegnato e non occupa spazio**, come se non esistesse nel DOM visivo (diverso da `visibility: hidden`, che nasconde l'elemento ma gli lascia lo spazio).

```css
.avviso {
  display: none; /* scompare del tutto, niente spazio residuo */
}
.etichetta {
  display: inline-block; /* in riga, ma con padding e width utilizzabili */
  width: 120px;
  padding: 4px 8px;
}
```

> [!warning] Trabocchetto — inline e dimensioni
> Impostare `width`/`height` su un elemento `inline` (es. uno `<span>`) **non ha alcun effetto**: il browser lo ignora silenziosamente. Se serve dare una dimensione fissa a un elemento in riga, va cambiato il `display` in `inline-block` o `block`.
## Liste: personalizzare i marcatori
Le liste (`<ul>`, `<ol>`, `<li>`, vedi [[02 - HTML semantico e form#Liste]]) hanno di default un `display` di tipo `list-item`, che mostra un marcatore (pallino o numero) davanti a ogni voce. CSS mette a disposizione tre proprietà dedicate per personalizzare questo marcatore.

> [!quote] Definizione — list-style-type
> `list-style-type` sceglie il **simbolo del marcatore** di ogni voce di lista. Si applica a `ul`, `ol`, `li` (o a qualunque elemento con `display: list-item`); il valore di default è `disc` (pallino pieno).

| Valore | Aspetto |
|---|---|
| `disc` (default) | pallino pieno |
| `circle` | pallino vuoto |
| `square` | quadratino pieno |
| `decimal` | 1, 2, 3, 4, 5… |
| `decimal-leading-zero` | 01, 02, 03, 04… |
| `lower-alpha` / `upper-alpha` | a, b, c… / A, B, C… |
| `lower-latin` / `upper-latin` | uguali a lower-alpha / upper-alpha |
| `lower-roman` / `upper-roman` | i, ii, iii… / I, II, III… |
| `lower-greek` | α, β, γ, δ… |
| `none` | nessun marcatore |

```css
ul {
  list-style-type: square;
}
```

> [!info] Togliere i pallini per un menu
> `list-style-type: none;` è la tecnica standard per trasformare un `<ul>` in un menu di navigazione senza pallini, prima di disporne gli `<li>` in riga con Flexbox (vedi [[#Flexbox: layout a una dimensione]]).

La seconda proprietà controlla se il marcatore sta dentro o fuori dal blocco di testo della voce:

> [!quote] Definizione — list-style-position
> `list-style-position` vale `outside` (default: il marcatore sta fuori dall'area di contenuto, che quindi non si allinea con le righe successive se il testo va a capo) oppure `inside` (il marcatore fa parte del blocco di testo, come fosse la prima parola della voce).

Infine, il marcatore predefinito può essere sostituito da un'immagine:

```css
ul {
  list-style-image: url(/images/happy.gif);
  list-style-type: circle;    /* fallback se l'immagine non si carica */
  list-style-position: outside;
}
```

*(extra, non da slide)* Le tre proprietà hanno anche una forma abbreviata, `list-style: <type> <position> <image>;` (es. `list-style: square inside;`), utile per non ripetere tre dichiarazioni separate.
## Uscire dal flusso: la proprietà position
`display` decide come un elemento si comporta *dentro* il flusso normale. `position` invece decide se e come un elemento può essere **spostato rispetto alla sua posizione naturale**, eventualmente uscendo del tutto dal flusso.

> [!quote] Definizione — position
> `position` controlla la modalità di posizionamento di un elemento. Insieme alle proprietà `top`, `right`, `bottom`, `left` (che indicano la distanza dal bordo del riferimento) permette di spostare l'elemento; `z-index` ne controlla la sovrapposizione con altri elementi posizionati.

| Valore | Comportamento | Rispetto a cosa si posiziona |
|---|---|---|
| `static` | posizione normale, quella del flusso (**default**) | non si applica, `top`/`left`/… vengono ignorati |
| `relative` | resta nel flusso, lo spazio originale è comunque riservato | **rispetto al suo posto originale** |
| `absolute` | esce dal flusso, gli altri elementi si comportano come se non ci fosse | rispetto al suo **containing block** |
| `fixed` | esce dal flusso, resta fermo anche durante lo scroll | rispetto al **viewport** |

Il concetto chiave per `absolute` (e per `fixed`) è quello di **containing block**, cioè l'elemento contenitore usato come riferimento per `top`/`right`/`bottom`/`left`.

> [!quote] Definizione — containing block
> Il *containing block* di un elemento con `position: absolute` è il **primo antenato** (risalendo l'albero del DOM) che ha una `position` diversa da `static`; se nessun antenato la ha, il riferimento diventa il `<body>` (quindi l'intera pagina).

```css
.scheda {
  position: relative; /* diventa il containing block dei suoi figli */
}
.badge {
  position: absolute; /* si posiziona rispetto a .scheda, non alla pagina */
  top: 8px;
  right: 8px;
}
```

> [!example] Menu fisso in alto
> ```css
> .navbar {
>   position: fixed;
>   top: 0;
>   left: 0;
>   width: 100%;
> }
> ```
> La barra resta sempre visibile in cima allo schermo, indipendentemente dallo scroll della pagina, perché il riferimento è il viewport e non un antenato nel documento.

*(extra, non da slide)* Le slide del corso elencano solo questi quattro valori, ma CSS ne definisce un quinto molto usato: `position: sticky`, un ibrido tra `relative` e `fixed` — l'elemento scorre come `relative` finché non raggiunge una soglia (es. `top: 0`), poi si blocca come `fixed` finché il suo contenitore è visibile.
### Gestire le sovrapposizioni con z-index
Quando due elementi posizionati si sovrappongono, l'ordine con cui vengono disegnati segue di default l'ordine nel documento (chi viene dopo copre chi viene prima).

> [!quote] Definizione — z-index
> `z-index` è un numero che stabilisce l'**ordine di sovrapposizione** (stacking order) tra elementi con `position` diversa da `static`: a parità di altre condizioni, l'elemento con `z-index` più alto viene disegnato sopra quello con valore più basso.

```css
#a { position: absolute; top: 200px; left: 200px; z-index: 10; }
#b { position: absolute; top: 225px; left: 175px; z-index: 5; }
#c { position: absolute; top: 250px; left: 225px; z-index: 1; }
/* #a è sopra #b, che è sopra #c, anche se nell'HTML compaiono in un altro ordine */
```

> [!warning] Trabocchetto — z-index senza position
> `z-index` **non ha alcun effetto** su un elemento con `position: static` (il default): serve prima impostare `relative`, `absolute`, `fixed` (o `sticky`) perché il browser lo consideri un elemento "posizionato".

> [!question] Domanda tipica d'esame
> Un `<div>` con `position: absolute` a chi fa riferimento per `top` e `left`?
> Al suo **containing block**: il primo antenato con `position` diversa da `static`, oppure il `<body>` se nessun antenato è posizionato.
## float e clear
Prima che Flexbox e Grid fossero disponibili, `float` era il modo principale per creare layout multi-colonna, ed è ancora usato per far scorrere il testo attorno a un'immagine.

> [!quote] Definizione — float
> `float` **sposta un elemento tutto a sinistra o tutto a destra** del suo contenitore, permettendo agli elementi successivi nel flusso di "circondarlo" (ad esempio un paragrafo di testo che si dispone attorno a un'immagine).

Caratteristiche di un elemento float:
- si **stacca dal flusso normale**, ma continua a influenzare la disposizione del contenuto intorno a sé (a differenza di `absolute`, che viene ignorato dagli altri elementi);
- resta comunque **contenuto nell'area di contenuto** dell'elemento che lo contiene;
- i suoi **margini vengono mantenuti**.

```css
.foto {
  float: left;
  margin-right: 12px;
}
```

Il problema tipico del float è che l'elemento contenitore **non si allunga** per contenere i figli float (sembra "collassare" a altezza zero). Si risolve in due modi:

> [!info] Contenere i float
> - Aggiungere `clear` a un elemento successivo (es. un `<div>` vuoto o il footer) con `clear: both`, per forzarlo a comparire sotto tutti i float.
> - Dichiarare `overflow: auto` (o `hidden`) sul contenitore stesso: obbliga il contenitore a calcolare la propria altezza includendo i float.

> [!quote] Definizione — clear
> `clear` impedisce che un elemento si affianchi a elementi float precedenti, forzandolo a comparire **sotto** di essi. I valori sono `left` (libera dai float a sinistra), `right`, `both` (libera da entrambi) e `none` (default).

> [!warning] Trabocchetto — margini che non collassano
> Il [[03 - CSS - selettori, specificità e box model#Margini che collassano|collasso dei margini verticali]] tra elementi adiacenti **non avviene** se uno dei due elementi è float oppure `position: absolute`.
## Flexbox: layout a una dimensione
Flexbox (Flexible Box Layout) è un sistema pensato per disporre elementi **lungo una sola dimensione alla volta** (una riga o una colonna), distribuendo lo spazio disponibile tra loro in modo flessibile.

> [!quote] Definizione — Flexbox
> Flexbox introduce due ruoli: il **flex container**, l'elemento con `display: flex` (o `inline-flex`), e i **flex item**, cioè i suoi figli diretti, che vengono automaticamente disposti lungo un **asse principale** (main axis) e possono essere allineati anche lungo l'**asse trasversale** (cross axis), perpendicolare al primo.

```css
.container {
  display: flex; /* o inline-flex */
}
```

L'asse principale è definito da `flex-direction` (default `row`): se è `row`, l'asse principale è orizzontale e quello trasversale verticale; se è `column`, è il contrario.
### Proprietà del container
| Proprietà | A cosa serve | Valori principali |
|---|---|---|
| `flex-direction` | direzione dell'asse principale | `row` \| `row-reverse` \| `column` \| `column-reverse` |
| `flex-wrap` | se gli item possono andare a capo | `nowrap` (default) \| `wrap` \| `wrap-reverse` |
| `justify-content` | allineamento degli item **lungo l'asse principale** | `flex-start` \| `flex-end` \| `center` \| `space-between` \| `space-around` \| `space-evenly` |
| `align-items` | allineamento degli item **lungo l'asse trasversale** | `flex-start` \| `flex-end` \| `center` \| `stretch` (default) \| `baseline` |
| `align-content` | allineamento delle **righe** (con più righe, cioè con `flex-wrap: wrap`) | stessi valori di `justify-content` |
| `gap` | spazio fisso tra gli item, senza margini manuali | es. `gap: 20px` |

> [!example] Riga di card centrata e con spaziatura (Esempi/live/es7/es-flex.html)
> ```css
> .container {
>   display: flex;
>   justify-content: center;
>   align-items: center;
>   gap: 20px;
>   flex-wrap: wrap;
> }
> .card {
>   width: 300px;
> }
> ```
> Le card si dispongono in riga, centrate, con 20px di spazio tra loro; se lo spazio orizzontale non basta, `flex-wrap: wrap` le manda a capo invece di comprimerle o farle uscire dal contenitore.
### Proprietà degli item
- **`order`** (default `0`): cambia l'ordine visivo di un item senza toccare l'HTML — utile per spostare, ad esempio, la navigazione sotto il contenuto principale su mobile e sopra su desktop.
- **`align-self`**: sovrascrive `align-items` per un singolo item (`auto` \| `flex-start` \| `flex-end` \| `center` \| `baseline` \| `stretch`).

*(extra, non da slide)* Le slide non trattano esplicitamente `flex-grow`, `flex-shrink` e `flex-basis`, ma sono le proprietà che decidono **come si distribuisce lo spazio in eccesso o in difetto** tra gli item, e sono utili per capire perché un flex item "si allunga" o "si restringe":
```css
.item {
  flex-grow: 1;   /* quanto l'item cresce rispetto agli altri se c'è spazio extra (default 0) */
  flex-shrink: 1; /* quanto si restringe se lo spazio non basta (default 1) */
  flex-basis: 200px; /* dimensione di partenza, prima di applicare grow/shrink (default auto) */
}
```

> [!warning] Trabocchetto — gap non è un margine
> Nel codice del docente compare anche `grid-gap` (nome storico della proprietà, usato prima che `gap` fosse standardizzato anche per Flexbox e Grid). Oggi si usa `gap` in entrambi i contesti: è preferibile perché, a differenza di margini manuali sugli item, non introduce spazio anche ai bordi esterni del container.
## Grid: layout a due dimensioni
Mentre Flexbox lavora bene su una dimensione alla volta, CSS Grid è pensato per **righe e colonne insieme**.

> [!quote] Definizione — CSS Grid
> *Grid is a two-dimensional system, handling both columns and rows* (mentre Flexbox è a una dimensione). Si attiva con `display: grid` su un elemento, che diventa una griglia composta da **grid lines** (le linee che delimitano righe e colonne), su cui si posizionano i figli diretti.

```css
.wrapper {
  display: grid;
  grid-template-columns: 200px 50px 100px;
  grid-template-rows: 100px 30px;
}
```
### grid-template-columns/rows e l'unità fr
`grid-template-columns` e `grid-template-rows` definiscono rispettivamente le colonne e le righe della griglia. Oltre a valori assoluti (`px`, `%`) e a `auto`, Grid introduce l'unità **`fr`** (fraction), che rappresenta una "porzione" dello spazio libero disponibile.

```css
grid-template-rows: 320px auto 320px;
grid-template-rows: repeat(3, 275px);   /* equivalente a 275px 275px 275px */
grid-template-columns: 1fr 2fr 1fr;     /* 3 colonne: la centrale è il doppio delle laterali */
grid-template-columns: 200px auto minmax(80px, auto);
```

> [!info] repeat() e fr
> - `repeat(n, valore)` ripete `n` volte lo stesso valore di colonna/riga, evitando di scriverlo a mano.
> - `fr` distribuisce lo spazio **rimasto** dopo aver assegnato le colonne/righe a larghezza fissa; `repeat(12, 1fr)` crea 12 colonne di uguale larghezza che occupano tutto lo spazio disponibile (la base della griglia a 12 colonne, vedi [[#Bootstrap: la griglia a 12 colonne|Bootstrap]]).
### Posizionare gli elementi: grid-column, grid-area e grid-template-areas
Un elemento figlio può occupare più celle indicando su quali *grid line* inizia e finisce:

```css
.item1 {
  grid-column-start: 1;
  grid-column-end: 4;   /* occupa dalla linea 1 alla linea 4: 3 colonne */
}
/* forma abbreviata equivalente */
.item1 {
  grid-column: 1 / 4;
}
```

Per layout di pagina più leggibili, Grid offre un secondo modo di posizionare gli elementi: **dare un nome** a ciascuna area e disegnare la griglia come una mappa testuale con `grid-template-areas`.

> [!example] Layout di pagina con grid-template-areas (Esempi/08-1-grid/grid-layout-test-final.html)
> ```css
> .container {
>   display: grid;
>   grid-template-columns: repeat(12, 1fr);
>   grid-gap: 5px;
>   grid-template-areas:
>     "m m m h h h h h h h h h"
>     "m m m c c c c c c c c c"
>     "f f f f f f f f f f f f";
> }
> .header  { grid-area: h; }
> .menu    { grid-area: m; }
> .content { grid-area: c; }
> .footer  { grid-area: f; }
> ```
> Ogni lettera ripetuta nella stringa indica quante celle occupa quell'area: `m` (menu) occupa le prime 3 colonne su tutte le righe tranne il footer, `h` (header) le restanti 9 colonne della prima riga, `c` (content) le restanti 9 colonne della seconda riga, `f` (footer) tutte le 12 colonne dell'ultima riga. `grid-gap` è il nome storico di `gap` applicato a Grid.

> [!warning] Trabocchetto — nomi non coerenti in grid-template-areas
> In `grid-template-areas` ogni riga della stringa deve avere lo **stesso numero di celle**, e la stessa lettera deve formare sempre un **rettangolo** (non è permesso uno schema a "L" o a "T" con lo stesso nome area): un errore qui rompe silenziosamente il layout invece di dare un errore CSS.
## Flexbox o Grid? Come scegliere
Questa è una delle distinzioni più chieste all'esame, perché Flexbox e Grid non sono alternative intercambiabili: risolvono problemi diversi.

> [!info] Regola pratica
> - **Flexbox → layout monodimensionale**: quando gli elementi vanno disposti lungo **una sola direzione** alla volta (una riga di card, i pulsanti di una toolbar, gli elementi di un menu di navigazione), anche se poi vanno a capo con `flex-wrap`.
> - **Grid → layout bidimensionale**: quando serve controllare **righe e colonne contemporaneamente** (la struttura intera di una pagina con header/nav/main/footer, una galleria a griglia con celle di dimensioni diverse).
> - Nella pratica i due si combinano: Grid per la struttura generale della pagina, Flexbox per allineare il contenuto interno di un singolo blocco (es. i pulsanti dentro una card).

> [!question] Domanda tipica d'esame
> Quando conviene usare Flexbox invece di Grid?
> Quando il layout è **monodimensionale**: gli elementi si dispongono lungo una sola direzione (riga o colonna). Grid si usa invece per layout **bidimensionali**, dove serve controllare righe e colonne insieme.
## Layout fixed e fluido delle pagine
Prima di arrivare al responsive vero e proprio, le slide distinguono due strategie classiche per la larghezza del layout di una pagina.

> [!info] Fixed vs fluid
> | Caratteristica | Fixed | Fluid |
> |---|---|---|
> | Larghezza | fissa in pixel, indipendente dalla finestra | proporzionale alla larghezza del browser (es. in %) |
> | Adattabilità | scarsa: schermi piccoli tagliano il contenuto, schermi grandi lasciano spazi vuoti | si adatta, ma righe di testo troppo lunghe su schermi molto grandi |
> | Controllo grafico | alto: il numero di "righe" è prevedibile | basso: la posizione finale degli elementi è meno prevedibile |
> | Complessità tecnica | semplice da realizzare | calcoli leggermente più complessi (percentuali, `max-width`) |
> | Scrollbar orizzontale | rischio se lo schermo è più piccolo del fisso | assente |

Nessuna delle due strategie da sola risolve il problema di schermi molto diversi tra loro (telefono vs monitor 4K): per questo si passa al **design responsive**.
## Design responsive: viewport e media query
> [!quote] Definizione — Responsive Web Design
> Fornire **layout diversi per schermi diversi**, adattando automaticamente la disposizione in base alla dimensione del dispositivo, mantenendo però **un solo file HTML** e un CSS che cambia grazie alle media query.

Realizzare un sito responsive richiede tre ingredienti: controllare il viewport, gestire il layout con media query, e usare media (immagini, video) "fluidi" che non superino la larghezza del contenitore.
### Il tag meta viewport
> [!quote] Definizione — viewport
> Il *viewport* è la finestra virtuale in cui il browser disegna la pagina. I dispositivi mobili, senza indicazioni, "barano": dichiarano una larghezza virtuale di 980px e poi la riscalano ai pixel reali dello schermo, rendendo il sito illeggibile (tutto piccolissimo).

```html
<meta name="viewport" content="width=device-width, initial-scale=1">
```

- `width=device-width`: il viewport ha la stessa larghezza reale del dispositivo (invece dei 980px finti).
- `initial-scale=1`: livello di zoom iniziale pari a 1 (nessuno zoom).
- altre opzioni: `user-scalable` (`yes`/`no`), `minimum-scale`, `maximum-scale`.

> [!warning] Trabocchetto — dimenticare il viewport
> Senza il meta tag `viewport`, **nessuna media query basata sulla larghezza dello schermo funziona come previsto** su mobile: il browser continua a ragionare sulla larghezza virtuale di 980px, non su quella reale del dispositivo.
### Le media query
> [!quote] Definizione — media query
> Una *media query* applica un blocco di regole CSS solo quando certe condizioni sul dispositivo (tipo di media, larghezza, orientamento…) sono verificate.

```css
@media screen and (min-width: 700px) {
  main { width: 70%; }
}
```

- **Media type**: `all`, `screen`, `print`, `speech` — a cosa è destinato l'output.
- **Media feature**: la condizione vera e propria, es. `orientation: landscape`, `max-width: 600px`, `min-width: 700px`, `color`.
- Si combinano con `and` (tutte le condizioni devono valere) e con la virgola `,` (basta che ne valga una, logica *or*):

```css
@media (min-width: 30em) and (orientation: landscape) { /* ... */ }
@media (min-height: 680px), screen and (orientation: portrait) { /* ... */ }
```

> [!info] min-width vs max-width
> - `min-width: Npx` → si applica **a partire da** quella larghezza in su (*applies at or above*).
> - `max-width: Npx` → si applica **fino a** quella larghezza (*applies at or below*).
### Breakpoint e strategie: mobile first vs desktop first
> [!quote] Definizione — breakpoint
> Un *breakpoint* è un valore di larghezza del viewport in corrispondenza del quale il layout della pagina cambia; si definisce con una media query. Le slide illustrano fasce indicative come phone (fino a ~600px), tablet portrait/landscape (~600-1200px) e desktop (oltre ~1200px), con valori concreti di dispositivi reali intorno a 768px e 1024px.

Ci sono due strategie principali per organizzare più media query nello stesso foglio di stile:

| Strategia | Come funziona |
|---|---|
| **Exclusive** | ogni fascia di larghezza ha regole indipendenti, senza sovrapposizioni da "correggere" |
| **Override** | si parte da uno stile di base e lo si **riscrive/estende** per le altre fasce |

La strategia "override" si declina in due varianti opposte:

> [!info] Mobile first vs Desktop first
> - **Mobile first**: si scrivono prima gli stili per i dispositivi piccoli, poi si aggiungono/sovrascrivono proprietà per schermi più larghi con `min-width`. È l'approccio usato dalla maggior parte dei framework moderni (Bootstrap incluso).
> - **Desktop first**: si parte dallo stile per schermi grandi e si adatta verso il basso con `max-width`.

> [!example] Layout mobile first con Flexbox (Esempi/live/es7/es-layout-resp.html)
> ```css
> .container { display: flex; flex-wrap: wrap; }
> main  { width: 100%; }
> aside { width: 100%; }
>
> @media (min-width: 700px) {
>   main  { width: 70%; }
>   aside { width: 30%; }
> }
>
> @media (min-width: 1000px) {
>   nav   { width: 20%; order: 2; }
>   main  { width: 60%; order: 1; }
>   aside { width: 20%; order: 3; }
> }
> ```
> Di default (mobile) ogni sezione occupa il 100% della larghezza e va a capo grazie a `flex-wrap: wrap`. Da 700px in su, `main` e `aside` diventano colonne affiancate; da 1000px in su anche `nav` diventa una colonna e `order` la riporta a sinistra.

> [!question] Domanda tipica d'esame
> Cosa significa "mobile first" nelle media query?
> Si scrivono per prime le regole per schermi piccoli (senza media query, o con `min-width` minimo), e si usano media query con `min-width` crescente per **aggiungere** stile man mano che lo schermo si allarga — al contrario del "desktop first", che parte da `max-width`.
### Media flessibili e immagini responsive
Oltre a viewport e media query, un sito responsive ha bisogno di **media flessibili**: immagini e video che si adattano alla larghezza del contenitore invece di restare fissi o di "rompere" il layout.

> [!quote] Definizione — media flessibili
> Un media flessibile (immagine, video, `<object>`…) usa `max-width: 100%` e `height: auto` invece di `width`/`height` fissi: si restringe se il contenitore è più piccolo di lui, ma non supera mai la sua dimensione originale.

```css
img, video {
  max-width: 100%;
  height: auto;
}
```

> [!warning] Trabocchetto — max-width, non width: 100%
> `width: 100%` forza il media a riempire **sempre** il contenitore, ingrandendolo (e sgranandolo) oltre le sue dimensioni reali se il contenitore è più largo dell'originale. `max-width: 100%` invece limita solo il caso in cui il contenitore è più piccolo, senza mai ingrandire il media oltre la sua risoluzione nativa.

Anche uno sfondo (`background-image`) può adattarsi al box che lo contiene con `background-size`:

> [!info] background-size: contain vs cover
> - `contain`: l'immagine si ridimensiona per stare **tutta dentro** il box, mantenendo le proporzioni (può lasciare bordi vuoti).
> - `cover`: l'immagine si ridimensiona per **riempire tutto** il box, mantenendo le proporzioni (può tagliarne una parte).

Per non sprecare banda su schermi piccoli, una media query può sostituire un'immagine di sfondo pesante con una più leggera:

```css
/* schermi piccoli: immagine leggera */
body {
  background-image: url('img_smallflower.jpg');
}
/* da 400px in su: immagine più grande */
@media only screen and (min-device-width: 400px) {
  body {
    background-image: url('img_flowers.jpg');
  }
}
```

Per le immagini `<img>` (non di sfondo), l'elemento `<picture>` con più `<source>` permette di servire un file diverso a seconda della larghezza dello schermo, ciascuno con la propria media query:

```html
<picture>
  <source media="(min-width: 650px)" srcset="img_pink_flowers.jpg">
  <source media="(min-width: 465px)" srcset="img_white_flower.jpg">
  <img src="img_orange_flowers.jpg" alt="Flowers" style="width:auto;">
</picture>
```

Il browser usa il primo `<source>` la cui media query è soddisfatta; se nessuna lo è, ricade sull'`<img>` finale, che funge anche da fallback per i browser che non supportano `<picture>`.
## CSS variables (custom properties)
Ripetere lo stesso valore (un colore, uno spazio) in decine di regole rende il CSS difficile da mantenere: le variabili CSS risolvono il problema.

> [!quote] Definizione — Custom Property
> Una *custom property* (variabile CSS) è una proprietà il cui nome inizia con `--`, dichiarata dentro un selettore; il suo valore si legge con la funzione `var()`. È **ereditata dai discendenti** del selettore in cui è definita, come le normali proprietà CSS ereditabili.

```css
:root {
  --colore-primario: #2e7d32; /* variabile globale, visibile ovunque */
  --spazio-base: 8px;
}

.bottone {
  background-color: var(--colore-primario);
  padding: var(--spazio-base);
}
```

- **Variabili globali**: definite sul selettore `:root` (la radice del documento), sono visibili in tutta la pagina.
- **Variabili locali**: definite su un selettore qualunque, sono visibili solo su quell'elemento e sui suoi discendenti.
- `var()` accetta un secondo argomento opzionale come valore di fallback: `var(--colore-primario, black)`.

> [!example] Ridefinire una variabile in una media query
> ```css
> :root {
>   --colonne: 1;
> }
> @media (min-width: 700px) {
>   :root { --colonne: 3; }
> }
> .griglia {
>   grid-template-columns: repeat(var(--colonne), 1fr);
> }
> ```
> Cambiando solo il valore della variabile dentro la media query, tutte le regole che la usano si aggiornano automaticamente, senza duplicare l'intera dichiarazione di `.griglia`.
## Bootstrap: la griglia a 12 colonne
Bootstrap è un framework CSS che fornisce, tra le altre cose, un sistema di griglia pronto all'uso, costruito sugli stessi principi di Grid/Flexbox ma esposto tramite **classi HTML** invece che tramite CSS scritto a mano.

> [!info] Perché Bootstrap (dalle slide)
> - **Facile da usare**: bastano conoscenze di base di HTML e CSS.
> - **Responsive**: la griglia si adatta automaticamente a telefoni, tablet e desktop.
> - **Mobile-first**: gli stili di base sono pensati per schermi piccoli e vengono estesi verso l'alto (come nella sezione precedente).
> - **Compatibilità**: funziona su tutti i browser moderni.

> [!quote] Definizione — griglia Bootstrap
> La griglia di Bootstrap si basa su tre livelli annidati: un `.container` (larghezza massima, centrato), che contiene una o più `.row` (righe), che contengono le `.col-*` (colonne). La riga è divisa in **12 colonne** virtuali; ogni `.col-*` dichiara quante di queste 12 colonne occupa.

```html
<div class="container">
  <div class="row">
    <div class="col-md-8">contenuto principale</div>
    <div class="col-md-4">barra laterale</div>
  </div>
</div>
```

Le classi `col-*` includono un **breakpoint** nel nome (`sm`, `md`, `lg`, `xl`, `xxl`…): la colonna occupa la larghezza indicata solo a partire da quel breakpoint, applicando esattamente la logica mobile-first vista sopra (min-width crescenti).

> [!info] Breakpoint della griglia Bootstrap
> | Breakpoint | Prefisso classe | Si applica da | Larghezza massima del `.container` |
> |---|---|---|---|
> | `xs` | `.col-` (senza suffisso) | sempre (< 576px) | nessuna (100%) |
> | `sm` | `.col-sm-` | ≥ 576px | 540px |
> | `md` | `.col-md-` | ≥ 768px | 720px |
> | `lg` | `.col-lg-` | ≥ 992px | 960px |
> | `xl` | `.col-xl-` | ≥ 1200px | 1140px |
> | `xxl` | `.col-xxl-` | ≥ 1400px | 1320px |
>
> Un `.container-fluid` invece è sempre largo il 100%, a qualunque breakpoint.

> [!example] Layout di pagina con Bootstrap (Esempi/08-2-bootstrap/bootstrap-test-final.html)
> ```html
> <div class="container">
>   <div class="row">
>     <header class="col-md-12">HEADER</header>
>     <nav class="col-md-12 col-lg-3">MENU</nav>
>     <main class="col-md-8 col-lg-6">MAIN</main>
>     <aside class="col-md-4 col-lg-3">ASIDE</aside>
>     <footer class="col-md-12">FOOTER</footer>
>   </div>
> </div>
> ```
> Su schermi medi (`md`, tablet) header, menu, main e footer occupano tutta la riga (12/12) uno sotto l'altro, mentre main e aside si affiancano (8+4=12). Su schermi grandi (`lg`, desktop) menu, main e aside si affiancano tutti e tre (3+6+3=12): lo stesso markup produce due layout diversi solo cambiando le classi, senza scrivere media query a mano. Confrontalo con `bootstrap-test-start.html`, che parte dagli stessi tag [[02 - HTML semantico e form|semantici]] senza alcuna classe di griglia.

> [!warning] Trabocchetto — colonne senza .row o .container
> Le classi `.col-*` funzionano solo se l'elemento è figlio diretto di una `.row`, a sua volta dentro un `.container` (o `.container-fluid`): usare `.col-md-6` fuori da questa struttura produce un layout rotto, perché Bootstrap calcola larghezze e margini negativi assumendo quella gerarchia.
## Riferimenti
- `PW07-CSS-3.pdf`: "Cambiare il display" (p. 40), "LISTE" / list-style (p. 41-45). Box model, box-sizing, margin collapsing, background (p. 1-27, 29-39) e pseudo-classi dei link (p. 53-55) sono trattati in [[03 - CSS - selettori, specificità e box model]] (che copre anche `reset.css`, corrispondente alla slide di p. 58); le pagine su ancore, `target` e link a mail/telefono (p. 47-51) sono trattate in [[02 - HTML semantico e form#Ancore: link a punti specifici di una pagina]].
- `PW08-CSS-HTML-4.pdf`: "Proprietà position" e "Modalità di posizionamento" (p. 4-6), "Gestire sovrapposizioni" / z-index (p. 7), "float" e "clear dei float" (p. 9-17), "FLEXBOX DISPLAY" (p. 18-27).
- `PW09-CSS-HTML-5.pdf`: "Layout delle pagine" e confronto fixed vs fluid (p. 1-7), "SITI RESPONSIVE", viewport e meta tag (p. 8-16), "MEDIA query" (p. 17-25), "Breakpoints" e "Mobile first" (p. 26-32), "Altre tecniche responsive" / media flessibili, `background-size`, `<picture>` (p. 33-38).
- `PW10-CSS-HTML-6.pdf`: "CSS Variables" (p. 1-11), "Grid Layout e Bootstrap" (p. 12-25), "GRID FRAMEWORKS" / Bootstrap e relativi breakpoint (p. 26-40).
- Esempi del docente: `Materiale Didattico/Esempi/08-1-grid/grid-layout-test-start.html` e `-final.html` (grid-template-areas); `Materiale Didattico/Esempi/08-2-bootstrap/bootstrap-test-start.html` e `-final.html` (griglia Bootstrap); `Materiale Didattico/Esempi/live/es7/es-flex.html`, `es-mq.html`, `es-layout-resp.html` (Flexbox e media query mobile first).
