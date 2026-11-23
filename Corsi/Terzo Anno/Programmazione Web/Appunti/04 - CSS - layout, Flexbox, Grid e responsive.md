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
> `display` stabilisce il **tipo di box** generato da un elemento e come si comporta rispetto agli elementi vicini. Il default è `inline` e la proprietà si applica a tutti gli elementi (slide PW07 p.40). I valori elencati dalla slide sono `inline`, `block`, `list-item`, `inline-block`, `table`, `inline-table`, `table-row-group`, `table-header-group`, `table-footer-group`, `table-row`, `table-column-group`, `table-column`, `table-cell`, `table-caption` e `none`; CSS3 ne aggiunge altri (`run-in`, `compact`, `ruby`, …). *(extra, non da slide: `run-in` è oggi obsoleto e non supportato dai browser)* I più usati sono `inline`, `block`, `inline-block` e `none`, descritti qui sotto. *(extra, non da slide)* Il foglio di stile predefinito del browser assegna `block` a tag come `<div>`, `<p>`, `<h1>`, mentre `flex` e `grid` non sono nell'elenco della slide e vengono introdotti nelle sezioni dedicate.

- **`block`**: l'elemento occupa **tutta la larghezza disponibile** del contenitore e va sempre a capo prima e dopo (es. `<div>`, `<p>`, `<h1>`). Rispetta `width`, `height`, tutto il `padding`/`margin`/`border` (vedi [[03 - CSS - selettori, specificità e box model#Box model]]).
- **`inline`**: l'elemento occupa **solo lo spazio necessario al suo contenuto** e sta sulla stessa riga degli elementi vicini (es. `<span>`, `<a>`, `<strong>`). *Ignora* `width` e `height`. *(extra, non da slide)* Ignora anche `margin-top`/`margin-bottom` (accetta solo `left`/`right`).
- **`inline-block`**: comportamento ibrido: l'elemento sta in riga come un `inline`, ma accetta `width`, `height` e tutti i margini come un `block`. *(extra, non da slide)* Era molto usato per affiancare più box prima dell'arrivo di Flexbox.
- **`none`**: l'elemento **non viene disegnato e non occupa spazio**: l'elemento resta nel DOM, ma non genera alcun box nella pagina. *(extra, non da slide)* È diverso da `visibility: hidden`, che nasconde l'elemento ma gli lascia lo spazio.

Esempio nostro *(extra, non da slide)*:

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

> [!question] Domanda tipica d'esame
> Uno `<span>` ha `width: 200px; height: 50px;` ma sulla pagina non cambia nulla. Perché, e come si risolve?
> **Risposta**: `<span>` è un elemento `inline` per default, e un elemento `inline` occupa solo lo spazio del proprio contenuto e **ignora `width` e `height`**. Si risolve cambiando il `display`: `inline-block` mantiene l'elemento in riga e fa valere le dimensioni, `block` lo fa andare a capo occupando tutta la larghezza disponibile. `display: none` invece non è una soluzione: l'elemento sparisce e non occupa più spazio.
## Liste: personalizzare i marcatori
Le liste (`<ul>`, `<ol>`, `<li>`, vedi [[02 - HTML semantico e form#Liste]]) hanno di default un `display` di tipo `list-item`, che mostra un marcatore (pallino o numero) davanti a ogni voce. CSS mette a disposizione tre proprietà dedicate per personalizzare questo marcatore.

> [!quote] Definizione — list-style-type
> `list-style-type` sceglie il **simbolo del marcatore** di ogni voce di lista. Si applica a `ul`, `ol`, `li` (o a qualunque elemento con `display: list-item`); il valore di default è `disc` (pallino pieno). La proprietà è ereditata (*Inherits: yes*) e ammette anche il valore `inherit` (slide PW07 p.43).

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
> `list-style-position` vale `outside` (default: il marcatore sta **fuori** dal box del contenuto e le righe del testo restano allineate tra loro, anche quando una voce va a capo) oppure `inside` (il marcatore sta **dentro** il box del contenuto, come fosse la prima parola della voce: se il testo va a capo, la riga successiva riparte sotto il marcatore). Ammette anche `inherit` ed è ereditata (slide PW07 p.44, figura Outside/Inside).

Infine, il marcatore predefinito può essere sostituito da un'immagine con `list-style-image`, che vale `url(...)` oppure `none` (default), ammette `inherit` ed è ereditata (slide PW07 p.45):

```css
ul {
  list-style-image: url(/images/happy.gif);
  list-style-type: circle;    /* fallback se l'immagine non si carica (extra, non da slide) */
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
| `static` | posizione normale, quella del flusso (**default**) | non si applica *(extra, non da slide)*: `top`/`left`/… vengono ignorati |
| `relative` | resta nel flusso, lo spazio originale è comunque riservato | **rispetto al suo posto originale** |
| `absolute` | esce dal flusso, gli altri elementi si comportano come se non ci fosse | rispetto al suo **containing block** (l'elemento contenitore di riferimento, definito subito sotto) |
| `fixed` | esce dal flusso, resta fermo anche durante lo scroll | rispetto al **viewport** (la finestra visibile del browser, vedi [[#Il tag meta viewport]]) |

Il concetto chiave per `absolute` (e per `fixed`) è quello di **containing block**, cioè l'elemento contenitore usato come riferimento per `top`/`right`/`bottom`/`left`.

> [!quote] Definizione — containing block
> Il *containing block* di un elemento con `position: absolute` è il **primo antenato** (risalendo l'albero del DOM) che ha una `position` diversa da `static`; se nessun antenato la ha, il riferimento diventa il `<body>` (così la slide PW08 p.5: «primo antenato con position non static (o il body)»).

*(extra, non da slide)* Lo standard CSS è più preciso della slide: se nessun antenato è posizionato, il riferimento non è propriamente il `<body>` ma l'**initial containing block** (blocco contenitore iniziale), un rettangolo grande quanto il viewport che contiene l'elemento radice `<html>`. È la dizione usata nelle domande a risposta multipla del test d'appello («blocco contenitore iniziale»).

Esempio nostro *(extra, non da slide)*:

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

> [!example] Menu fisso in alto *(extra, non da slide: la slide PW08 p.8 rimanda solo a esempi esterni)*
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
> `z-index` è un numero che stabilisce l'**ordine di sovrapposizione** (stacking order) tra elementi con `position` diversa da `static`: a parità di altre condizioni, l'elemento con `z-index` più alto viene disegnato sopra quello con valore più basso. Valori ammessi: `number | auto | inherit`; default `auto`; si applica agli elementi posizionati; non è ereditata (slide PW08 p.7).

Esempio della slide PW08 p.7 (tre cubi A, B, C; qui con gli id in minuscolo):

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
> **Risposta**: al suo **containing block**: il primo antenato con `position` diversa da `static`, oppure il `<body>` (slide) se nessun antenato è posizionato.

> [!question] Domanda tipica d'esame
> Dati `.card { position: relative; }` e `.badge { position: absolute; top: 8px; right: 8px; }`, con `.badge` figlio diretto di `.card`, rispetto a che cosa è posizionato il badge? E se tutti gli antenati di un elemento `absolute` fossero `static`?
> **Risposta**: rispetto a `.card`, perché è il primo antenato con `position` diversa da `static`. Se tutti gli antenati sono `static`, la slide dice «il body»; *(extra, non da slide)* lo standard e il test d'appello parlano di **blocco contenitore iniziale** (initial containing block), che è la risposta corretta quando compare tra le opzioni.

> [!question] Domanda tipica d'esame
> Che differenza c'è tra `static`, `relative`, `absolute` e `fixed`?
> **Risposta**: `static` è il default, segue il flusso normale e ignora `top`/`left`. `relative` resta nel flusso e si sposta rispetto al proprio posto originale (lo spazio originale resta riservato). `absolute` esce dal flusso e si posiziona rispetto al proprio containing block. `fixed` esce dal flusso e si posiziona rispetto al viewport, restando fermo durante lo scroll. `z-index` ha effetto solo sugli elementi posizionati (cioè non `static`).
## float e clear
Prima che Flexbox e Grid fossero disponibili, `float` era il modo principale per creare layout multi-colonna, ed è ancora usato per far scorrere il testo attorno a un'immagine.

> [!quote] Definizione — float
> `float` **sposta un elemento tutto a sinistra o tutto a destra** del suo contenitore, permettendo agli elementi successivi nel flusso di "circondarlo" (ad esempio un paragrafo di testo che si dispone attorno a un'immagine).

Caratteristiche di un elemento float:
- si **stacca dal flusso normale**, ma continua a influenzare la disposizione del contenuto intorno a sé *(extra, non da slide: a differenza di `absolute`, che viene ignorato dagli altri elementi)*;
- resta comunque **contenuto nell'area di contenuto** dell'elemento che lo contiene;
- i suoi **margini vengono mantenuti**.

Esempio della slide PW08 p.11-12 (`ogre-fl.html`): l'immagine inline resta nel flusso, con `float` si sposta a destra e il testo la circonda.

```css
img { float: right; margin: 10px; }
```

Esempio della slide PW08 p.15: l'immagine va a sinistra e il titolo `h2` successivo riparte sotto di essa grazie a `clear: left`.

```css
img { float: left; margin-right: 10px; }
h2  { clear: left; margin-top: 2em; }
```

Variante nostra *(extra, non da slide)*:

```css
.foto {
  float: left;
  margin-right: 12px;
}
```

Il problema tipico del float è che l'elemento contenitore **non si allunga** per contenere i figli float (sembra "collassare" ad altezza zero). Si risolve in due modi:

> [!info] Contenere i float
> - Aggiungere `clear` a un elemento successivo (es. un `<div>` vuoto o il footer *(extra, non da slide)*) con `clear: both` *(extra, non da slide: la slide p.16 dà solo `overflow: auto/hidden`)*, per forzarlo a comparire sotto tutti i float.
> - Dichiarare `overflow: auto` (o `hidden`) sul contenitore stesso: obbliga il contenitore a calcolare la propria altezza includendo i float. Esempio della slide PW08 p.16 (`float-test.html`): `#container { overflow: auto; width: 100%; padding: 1em; }`.

> [!quote] Definizione — clear
> `clear` impedisce che un elemento si affianchi a elementi float precedenti, forzandolo a comparire **sotto** di essi. I valori sono `left` (libera dai float a sinistra), `right`, `both` (libera da entrambi) e `none` (default); si applica **solo agli elementi di tipo block** e non è ereditata (slide PW08 p.15).

> [!warning] Trabocchetto — margini che non collassano
> Il [[03 - CSS - selettori, specificità e box model#Margini che collassano|collasso dei margini verticali]] tra elementi adiacenti **non avviene** se uno dei due elementi è float oppure `position: absolute`.

> [!question] Domanda tipica d'esame
> Un contenitore ha come figli solo immagini con `float: left` e sembra avere altezza zero. Perché, e come si risolve? A che cosa serve `clear: both`?
> **Risposta**: un elemento float esce dal flusso normale, quindi il contenitore **non si allunga** per contenerlo. Si risolve dichiarando `overflow: auto` (o `hidden`) sul contenitore, oppure aggiungendo dopo i float un elemento con `clear: both`. `clear` impedisce a un elemento (di tipo block) di affiancarsi ai float precedenti e lo forza a comparire sotto di essi: `left` e `right` liberano da un solo lato, `both` da entrambi.
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

La figura «Flex geometry» (slide PW08 p.20) dà un nome a tutti gli elementi di questa geometria: **flex container** e **flex item**; **main axis** e **cross axis**; **main start** e **main end** (inizio e fine dell'asse principale); **cross start** e **cross end** (inizio e fine dell'asse trasversale); **main size** e **cross size** (dimensione del container lungo l'asse principale e lungo quello trasversale).
### Proprietà del container
I default indicati nella tabella (`row`, `nowrap`, `stretch`) non sono scritti nelle slide, ma nella guida CSS-Tricks linkata a p.18 *(extra, non da slide)*.

| Proprietà | A cosa serve | Valori principali |
|---|---|---|
| `flex-direction` | direzione dell'asse principale | `row` \| `row-reverse` \| `column` \| `column-reverse` |
| `flex-wrap` | se gli item possono andare a capo | `nowrap` (default) \| `wrap` \| `wrap-reverse` |
| `justify-content` | allineamento degli item **lungo l'asse principale** | `flex-start` \| `flex-end` \| `center` \| `space-between` \| `space-around` \| `space-evenly` |
| `align-items` | allineamento degli item **lungo l'asse trasversale** | `flex-start` \| `flex-end` \| `center` \| `stretch` (default) \| `baseline` |
| `align-content` | allineamento delle **righe** (con più righe, cioè con `flex-wrap: wrap`) | `flex-start` \| `flex-end` \| `center` \| `space-between` \| `space-around` \| `space-evenly` \| `stretch` *(extra, non da slide: la slide p.24 mostra solo le figure di `align-items`, lasciando vuoto lo spazio di `align-content`)* |
| `gap` | spazio fisso tra gli item, senza margini manuali | es. `gap: 20px` (dall'esempio del docente `es-flex.html`) |

> [!example] Riga di card centrata e con spaziatura (estratto da Esempi/live/es7/es-flex.html)
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
- **`order`** (`order: <integer>`, default `0`; slide PW08 p.25): cambia l'ordine visivo di un item senza toccare l'HTML — utile per spostare, ad esempio, la navigazione sotto il contenuto principale su mobile e sopra su desktop. Gli item si dispongono in ordine crescente di `order`; *(extra, non da slide)* a parità di valore si segue l'ordine nel documento.
- **`align-self`**: sovrascrive `align-items` per un singolo item (`auto` \| `flex-start` \| `flex-end` \| `center` \| `baseline` \| `stretch`).

*(extra, non da slide)* Le slide non trattano esplicitamente `flex-grow`, `flex-shrink` e `flex-basis`, ma sono le proprietà che decidono **come si distribuisce lo spazio in eccesso o in difetto** tra gli item, e sono utili per capire perché un flex item "si allunga" o "si restringe":
```css
.item {
  flex-grow: 1;   /* quanto l'item cresce rispetto agli altri se c'è spazio extra (default 0) */
  flex-shrink: 1; /* quanto si restringe se lo spazio non basta (default 1) */
  flex-basis: 200px; /* dimensione di partenza, prima di applicare grow/shrink (default auto) */
}
```

> [!warning] Trabocchetto — `grid-gap` e `gap`
> Nel codice del docente compare anche `grid-gap` (nome storico della proprietà, usato prima che `gap` fosse standardizzato anche per Flexbox e Grid). *(extra, non da slide)* Oggi si usa `gap` in entrambi i contesti: è preferibile perché, a differenza di margini manuali sugli item, non introduce spazio anche ai bordi esterni del container.

> [!question] Domanda tipica d'esame
> Che differenza c'è tra `justify-content` e `align-items` in un flex container? E se si passa da `flex-direction: row` a `column`?
> **Risposta**: `justify-content` allinea gli item lungo l'**asse principale** (`flex-start`, `flex-end`, `center`, `space-between`, `space-around`, `space-evenly`), `align-items` li allinea lungo l'**asse trasversale** (`flex-start`, `flex-end`, `center`, `stretch`, `baseline`). Con `row` l'asse principale è orizzontale e quello trasversale verticale; con `column` i due assi si scambiano, quindi `justify-content` agisce in verticale e `align-items` in orizzontale.
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

Le grid line sono numerate a partire da **1**: una griglia di 2 colonne e 3 righe ha 3 linee verticali (numerate da 1 a 3) e 4 linee orizzontali (da 1 a 4). La figura della slide (PW10 p.22-23) mostra proprio questa griglia, con righe `150px / auto / 150px` e colonne `25% / 75%`; la trascrizione in codice è nostra *(extra, non da slide)*:

```css
.wrapper {
  display: grid;
  grid-template-rows: 150px auto 150px;
  grid-template-columns: 25% 75%;
}
```
### grid-template-columns/rows e l'unità fr
`grid-template-columns` e `grid-template-rows` definiscono rispettivamente le colonne e le righe della griglia. Oltre a valori assoluti (`px`, `%`) e a `auto`, Grid introduce l'unità **`fr`** (fraction), che rappresenta una "porzione" dello spazio libero disponibile.

Esempi della slide PW10 p.25:

```css
grid-template-rows: 320px auto 320px;
grid-template-rows: 250px 800px 400px;
grid-template-rows: repeat(3, 275px);   /* equivalente a 275px 275px 275px */
grid-template-rows: 1fr 2fr 1fr;        /* 3 righe: la centrale è il doppio delle altre (extra, non da slide: commento) */
grid-template-columns: 25% 75%;
grid-template-columns: 100px 100px 100px 100px;
grid-template-columns: repeat(4, 100px);
grid-template-columns: 200px auto minmax(80px, auto);
```

Variante sulle colonne *(extra, non da slide)*:

```css
grid-template-columns: 1fr 2fr 1fr;     /* 3 colonne: la centrale è il doppio delle laterali */
```

> [!info] repeat() e fr
> - `minmax(min, max)` *(extra, non da slide: la slide lo usa senza spiegarlo)* definisce un intervallo: `minmax(80px, auto)` è una colonna larga almeno 80px e al massimo quanto serve al contenuto (`auto`).
> - `repeat(n, valore)` ripete `n` volte lo stesso valore di colonna/riga, evitando di scriverlo a mano. *(extra, non da slide)*
> - `fr` distribuisce lo spazio **rimasto** dopo aver assegnato le colonne/righe a larghezza fissa *(extra, non da slide)*; `repeat(12, 1fr)` crea 12 colonne di uguale larghezza che occupano tutto lo spazio disponibile (la base della griglia a 12 colonne, vedi [[#Bootstrap: la griglia a 12 colonne|Bootstrap]]).
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

Lo stesso vale per le righe con `grid-row-start` e `grid-row-end`. Esempio della slide PW10 p.29 (griglia 3x3): `.item1` occupa le colonne dalla linea 1 alla 3, `.item3` le righe dalla linea 2 alla 4, `.item4` le colonne dalla linea 2 alla 4.

```css
.item1 { grid-column-start: 1; grid-column-end: 3; }
.item3 { grid-row-start: 2; grid-row-end: 4; }
.item4 { grid-column-start: 2; grid-column-end: 4; }
```

Il valore `-1` indica l'**ultima** linea: `grid-column: 1 / -1` fa occupare tutta la larghezza, qualunque sia il numero di colonne *(extra, non da slide: la slide mostra solo `1 / -1`)*. Page layout della slide PW10 p.30-31 (HTML: `.wrapper` con `<header>`, `<nav>`, `<main>`, `<footer>`):

```css
.wrapper {
  display: grid;
  grid-gap: 3px;
  grid-template-columns: repeat(12, 1fr);
  grid-template-rows: 40px 200px 40px;
}
header { grid-column: 1 / -1; }
nav    { }
main   { grid-column: 2 / -1; }
footer { grid-column: 1 / -1; }
```

Per layout di pagina più leggibili, Grid offre un secondo modo di posizionare gli elementi: **dare un nome** a ciascuna area e disegnare la griglia come una mappa testuale con `grid-template-areas`.

> [!example] Layout di pagina con grid-template-areas (estratto da Esempi/08-1-grid/grid-layout-test-final.html)
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
> Nel file sono presenti, commentate, le alternative con `grid-column` (`1/-1`, `1/4`, `4/-1`): è il passaggio dalla slide precedente a `grid-template-areas`. Ogni lettera ripetuta nella stringa indica quante celle occupa quell'area: `m` (menu) occupa le prime 3 colonne su tutte le righe tranne il footer, `h` (header) le restanti 9 colonne della prima riga, `c` (content) le restanti 9 colonne della seconda riga, `f` (footer) tutte le 12 colonne dell'ultima riga. `grid-gap` è il nome storico di `gap` applicato a Grid.

Versione della slide PW10 p.32 (stesso page layout, `gap` di 3px, righe `40px 200px 40px`, `nav` come area `m`):

```css
.wrapper {
  display: grid;
  grid-gap: 3px;
  grid-template-columns: repeat(12, 1fr);
  grid-template-rows: 40px 200px 40px;
  grid-template-areas:
    "h h h h h h h h h h h h"
    "m c c c c c c c c c c c"
    "f f f f f f f f f f f f";
}
header { grid-area: h; }
nav    { grid-area: m; }
main   { grid-area: c; }
footer { grid-area: f; }
```

> [!warning] Trabocchetto — nomi non coerenti in grid-template-areas
> In `grid-template-areas` ogni riga della stringa deve avere lo **stesso numero di celle**, e la stessa lettera deve formare sempre un **rettangolo** (non è permesso uno schema a "L" o a "T" con lo stesso nome area): un errore qui rompe silenziosamente il layout invece di dare un errore CSS. *(extra, non da slide)*

> [!question] Domanda tipica d'esame
> Che cosa significa `grid-template-columns: repeat(12, 1fr);` e che cosa indica l'unità `fr`?
> **Risposta**: crea 12 colonne di uguale larghezza. `fr` (fraction) è una **porzione dello spazio libero** della griglia, che resta dopo aver assegnato le colonne a larghezza fissa: con `repeat(12, 1fr)` ogni colonna vale 1/12 dello spazio disponibile. `1fr 2fr 1fr` darebbe invece alla colonna centrale il doppio dello spazio delle laterali.

> [!question] Domanda tipica d'esame
> In una griglia, che cosa fa `grid-column: 1 / -1;` e come si dispone un layout con `grid-template-areas`?
> **Risposta**: `1 / -1` fa occupare all'elemento le colonne **dalla linea 1 all'ultima linea** (`-1`), cioè tutta la larghezza. Con `grid-template-areas` si disegna la griglia come mappa testuale (una stringa per riga, una cella per colonna) usando un nome per ogni area, e poi si assegna ogni elemento alla sua area con `grid-area`. Ogni area deve formare un rettangolo *(extra, non da slide)*.
## Flexbox o Grid? Come scegliere
Flexbox e Grid non sono alternative intercambiabili: risolvono problemi diversi. Nel test d'appello compare la domanda «Quando è più adatto usare Flexbox?», con risposta corretta «per organizzare elementi lungo una sola direzione, riga o colonna».

> [!info] Regola pratica
> - **Flexbox → layout monodimensionale**: quando gli elementi vanno disposti lungo **una sola direzione** alla volta (una riga di card, i pulsanti di una toolbar, gli elementi di un menu di navigazione), anche se poi vanno a capo con `flex-wrap`.
> - **Grid → layout bidimensionale**: quando serve controllare **righe e colonne contemporaneamente** (la struttura intera di una pagina con header/nav/main/footer, una galleria a griglia con celle di dimensioni diverse).
> - Nella pratica i due si combinano: Grid per la struttura generale della pagina, Flexbox per allineare il contenuto interno di un singolo blocco (es. i pulsanti dentro una card). *(extra, non da slide: la slide p.21 dice solo «Grid two-dimensional, flexbox one-dimensional»)*

> [!question] Domanda tipica d'esame
> Quando conviene usare Flexbox invece di Grid?
> **Risposta**: quando il layout è **monodimensionale**: gli elementi si dispongono lungo una sola direzione (riga o colonna). Grid si usa invece per layout **bidimensionali**, dove serve controllare righe e colonne insieme.
## Layout fixed e fluido delle pagine
Prima di arrivare al responsive vero e proprio, le slide distinguono due strategie classiche per la larghezza del layout di una pagina.

Definizione (slide PW09 p.2): nel web design il **layout** determina come i contenuti si distribuiscono nella pagina. Un layout **fluid** ha larghezza proporzionale alla larghezza del browser; un layout **fixed** ha larghezza indipendente dalla finestra del browser.

> [!info] Fixed vs fluid
> | Caratteristica | Fixed | Fluid |
> |---|---|---|
> | Larghezza | fissa in pixel, indipendente dalla finestra | proporzionale alla larghezza del browser (es. in %) |
> | Adattabilità | scarsa: schermi piccoli tagliano il contenuto, schermi grandi lasciano spazi vuoti | buona: si adatta, ma righe di testo troppo lunghe su schermi molto grandi |
> | Controllo grafico | alto: il numero di "righe" è prevedibile | basso: la posizione finale degli elementi è meno prevedibile |
> | Usabilità mobile | scarsa | buona |
> | Complessità tecnica | semplice da realizzare | complessa: calcoli un poco più complicati *(extra, non da slide: percentuali, `max-width`)* |
> | Scrollbar orizzontale | rischio se la finestra è più piccola del layout (la parte destra viene coperta) | assente |
>
> Le righe da Adattabilità a Complessità tecnica sono quelle del «Confronto fixed vs fluid» della slide PW09 p.7; Larghezza è la definizione di p.2; Scrollbar riassume le liste di p.4 e p.6.

Vantaggi e svantaggi dalle slide (PW09 p.4 e p.6):
- **Fluid, vantaggi**: sembra più vicino alla natura dei browser; elimina spazi potenzialmente vuoti; l'utente può controllare la pagina; niente scrollbar orizzontali. **Svantaggi**: su un monitor grande le righe sono troppo lunghe (conviene limitare la dimensione); non è facile prevedere la posizione degli elementi e l'effetto grafico finale; problemi nei browser piccoli; i conti sono un poco più complicati.
- **Fixed, vantaggi**: controllo del numero delle righe; è semplice da realizzare; è una visualizzazione comune per i desktop. **Svantaggi**: se la finestra è piccola la parte destra viene coperta; se lo schermo è grande restano spazi a destra e a sinistra da gestire; con caratteri grandi le righe diventano corte; la pagina non è controllabile dall'utente.

Esempio della slide PW09 p.3, layout fluid a due colonne:

```css
.wrapper { display: flex; width: 100%; }
.main    { width: 70%; background-color: yellow; margin-right: 5%; }
.extras  { width: 25%; background-color: orange; }
```

Esempio della slide PW09 p.5, layout fixed a due colonne (con `margin: 0 auto` lo spazio extra si divide tra sinistra e destra, invece di restare tutto a destra con `margin-left: auto`):

```css
.wrapper { width: 750px; display: flex; justify-content: flex-start; margin: 0 auto; }
.extras  { width: 200px; margin-right: 25px; background-color: orange; }
.main    { width: 525px; background-color: yellow; }
```

> [!question] Domanda tipica d'esame
> Qual è la differenza tra layout fixed e fluid, e quali vantaggi ha ciascuno?
> **Risposta**: il layout **fixed** ha larghezza in pixel indipendente dalla finestra: è semplice da realizzare e dà più controllo grafico, ma su schermi piccoli la parte destra viene coperta e su schermi grandi restano spazi vuoti ai lati. Il layout **fluid** ha larghezza proporzionale al browser: si adatta meglio (e funziona meglio su mobile) ed elimina gli spazi vuoti, ma è meno prevedibile, più complesso da calcolare e su schermi grandi produce righe troppo lunghe.

Nessuna delle due strategie da sola risolve il problema di schermi molto diversi tra loro (telefono vs monitor 4K): per questo si passa al **design responsive**.
## Design responsive: viewport e media query
> [!quote] Definizione — Responsive Web Design
> Fornire **layout diversi per schermi diversi**, adattando automaticamente la disposizione in base alla dimensione del dispositivo, mantenendo però **un solo file HTML** e un CSS che cambia grazie alle media query.

Realizzare un sito responsive richiede tre ingredienti: controllare il viewport, gestire il layout con media query, e usare media (immagini, video) "fluidi" che non superino la larghezza del contenitore.
### Il tag meta viewport
> [!quote] Definizione — viewport
> Il *viewport* è la finestra virtuale in cui il browser disegna la pagina. I dispositivi mobili, senza indicazioni, dichiarano una larghezza virtuale di 980px (la slide dice che «barano») e poi la riscalano ai pixel reali dello schermo, rendendo il sito illeggibile (tutto piccolissimo).

Esempio della slide PW09 p.13-14: uno schermo da 320 pixel reali che dichiara 980px viene scalato di un fattore 0.32. Un'immagine di 320x356 px, con «Viewport: Not specified (980)», resta piccola nell'angolo; con «Viewport: 320 Width, scale = 1.0» riempie la schermata.

```html
<meta name="viewport" content="width=device-width, initial-scale=1">
```

- `width=device-width`: il viewport ha la stessa larghezza reale del dispositivo (invece dei 980px finti).
- `initial-scale=1`: livello di zoom iniziale pari a 1 (nessuno zoom).
- altre opzioni (slide PW09 p.15): `width` e `height` (`device-width`/`device-height` oppure un valore in px), `user-scalable` (`yes`/`no`), `minimum-scale` e `maximum-scale` (con valore `1` la pagina non scala).

> [!warning] Trabocchetto — dimenticare il viewport
> Senza il meta tag `viewport` la pagina viene disegnata su 980px virtuali e poi rimpicciolita (slide PW09 p.16: confronto con e senza il tag). *(extra, non da slide)* Di conseguenza **nessuna media query basata sulla larghezza dello schermo funziona come previsto** su mobile: il browser ragiona sulla larghezza virtuale di 980px, non su quella reale del dispositivo.

> [!question] Domanda tipica d'esame
> A che cosa serve `<meta name="viewport" content="width=device-width, initial-scale=1">`?
> **Risposta**: va inserito nell'`<head>` e dice al browser mobile di usare come larghezza del viewport quella reale del dispositivo (`width=device-width`) invece dei 980px dichiarati per default, con zoom iniziale 1 (`initial-scale=1`). Senza di esso il sito viene disegnato su 980px e rimpicciolito, quindi risulta illeggibile.
### Le media query
> [!quote] Definizione — media query
> Una *media query* applica un blocco di regole CSS solo quando certe condizioni sul dispositivo (tipo di media, larghezza, orientamento…) sono verificate.

```css
@media screen and (min-width: 700px) {
  main { width: 70%; }
}
```

- **Media type**: `all`, `screen`, `print`, `speech` — a cosa è destinato l'output.
- **Media feature**: la condizione vera e propria, es. `orientation: landscape`, `max-width: 12450px`, `color` (slide PW09 p.20), oppure `max-width: 600px` (`es-mq.html`) e `min-width: 700px`.
- Si combinano con `and` (tutte le condizioni devono valere) e con la virgola `,` (basta che ne valga una, logica *or*):

```css
@media (min-width: 30em) and (orientation: landscape) { /* ... */ }
@media screen and (min-width: 30em) and (orientation: landscape) { /* ... */ }
@media print and (min-resolution: 300dpi) { /* ... */ }
@media (min-height: 680px), screen and (orientation: portrait) { /* ... */ }
```

> [!info] min-width vs max-width
> - `min-width: Npx` → si applica **a partire da** quella larghezza in su (*applies at or above*).
> - `max-width: Npx` → si applica **fino a** quella larghezza (*applies at or below*).
> - Esempio: `@media (min-width: 900px) { main { max-width: 1200px; } }` applica la regola solo quando il viewport è largo **almeno 900px** (900 compreso). Sotto i 900px la regola non ha effetto; non fissa la larghezza di `main` a 900px, né porta il viewport a 1200px.

> [!question] Domanda tipica d'esame
> Che cosa significa `@media (min-width: 900px) { main { max-width: 1200px; } }`?
> **Risposta**: la regola interna si applica solo quando il viewport è largo **almeno 900px**. In quel caso `main` non può superare i 1200px di larghezza. Sotto i 900px la media query non è soddisfatta e `main` non ha quel limite.
### Breakpoint e strategie: mobile first vs desktop first
> [!quote] Definizione — breakpoint
> Un *breakpoint* è un valore di larghezza del viewport in corrispondenza del quale il layout della pagina cambia; si definisce con una media query. La slide PW09 p.28 (con la figura dei dispositivi di p.27) illustra cinque fasce indicative: **Phone** (0-600px), **Tablet portrait** (600-900px), **Tablet landscape** (900-1200px), **Desktop** (1200-1800px) e **Big desktop** (oltre 1800px), con schermi reali come 360x640, 375x667, 720x1280, 768x1024, 1024x768, 1280x1024, 1366x768, 1440x900.

Ci sono due strategie principali per organizzare più media query nello stesso foglio di stile:

| Strategia | Come funziona |
|---|---|
| **Exclusive** | ogni fascia di larghezza ha regole indipendenti, senza sovrapposizioni da "correggere" |
| **Override** | si parte da uno stile di base e lo si **riscrive/estende** per le altre fasce |

Esempi della slide PW09 p.32 (cambia il colore di sfondo a 400, 600 e 800px). **Override**: ogni regola riscrive la precedente.

```css
@media (min-width: 400px) { html { background: red; } }
@media (min-width: 600px) { html { background: green; } }
@media (min-width: 800px) { html { background: blue; } }
```

**Exclusive**: le fasce non si sovrappongono.

```css
@media (max-width: 400px) { html { background: red; } }
@media (min-width: 401px) and (max-width: 800px) { html { background: green; } }
@media (min-width: 801px) { html { background: blue; } }
```

La strategia "override" si declina in due varianti opposte (slide PW09 p.33):

> [!info] Mobile first vs Desktop first
> - **Mobile first**: si scrivono prima gli stili per i dispositivi piccoli, poi si aggiungono/sovrascrivono proprietà per schermi più larghi con `min-width`. È l'approccio usato dalla maggior parte dei framework (slide PW09 p.30; per Bootstrap vedi PW10 p.34, «Mobile-first approach»).
> - **Desktop first**: si parte dallo stile per schermi grandi e si adatta verso il basso con `max-width`.
>
> Esempi della slide PW09 p.33 (`es-mq.html` è un caso di desktop first con `max-width: 600px`):
>
> ```css
> /* desktop first: max-width */
> html { background: red; }
> @media (max-width: 600px) { html { background: green; } }
>
> /* mobile first: min-width */
> html { background: red; }
> @media (min-width: 600px) { html { background: green; } }
> ```

> [!info] Graceful degradation e progressive enhancement
> La slide PW09 p.31 (solo figura, titolo «Graceful Degradation vs. Progressive Enhancement») contrappone due direzioni di progetto: dal desktop verso tablet e telefono (*graceful degradation*) e dal telefono verso tablet e desktop (*progressive enhancement*). *(extra, non da slide: l'associazione è nostra interpretazione della figura)* La prima direzione corrisponde al desktop first, la seconda al mobile first.

> [!example] Layout mobile first con Flexbox (Esempi/live/es7/es-layout-resp.html)
> ```html
> <div class="container">
>   <header>HEADER</header>
>   <nav>NAV</nav>
>   <main>MAIN</main>
>   <aside>ASIDE</aside>
>   <footer>FOOTER</footer>
> </div>
> ```
> ```css
> * { box-sizing: border-box; margin: 0; padding: 0; }
> .container { display: flex; width: 100%; flex-wrap: wrap; }
> header { background-color: grey; width: 100%; height: 150px; order: 1; }
> nav    { background-color: green; position: absolute; top: 10px; right: 10px; width: 50px; height: 50px; }
> nav:hover { top: 0; right: 0; width: 100%; height: 200px; }
> main   { background-color: indianred; width: 100%; height: 600px; }
> aside  { background-color: lightsteelblue; width: 100%; height: 300px; }
> footer { background-color: black; width: 100%; height: 200px; order: 5; }
>
> @media (min-width: 700px) {
>   main  { width: 70%; }
>   aside { width: 30%; }
> }
>
> @media (min-width: 1000px) {
>   nav, nav:hover { position: static; width: 20%; height: 400px; order: 2; }
>   main  { width: 60%; order: 1; }
>   aside { width: 20%; order: 3; }
> }
> ```
> Di default (mobile) `header`, `main`, `aside` e `footer` occupano il 100% della larghezza e vanno a capo grazie a `flex-wrap: wrap`. Il `nav` invece è fuori dal flusso (`position: absolute`): è un quadrato verde di 50px in alto a destra che, al passaggio del mouse, si espande a tutta la larghezza (altezza 200px). Da 700px in su `main` e `aside` diventano colonne affiancate (70% e 30%). Da 1000px in su il `nav` rientra nel flusso (`position: static`) come colonna del 20% e `order` stabilisce l'ordine visivo: con `order: 1` per `main`, `2` per `nav` e `3` per `aside` le colonne compaiono nell'ordine **main, nav, aside** (non il `nav` a sinistra), tra `header` (`order: 1`, resta in cima perché precede `main` nel documento) e `footer` (`order: 5`).
>
> *(extra, non da slide)* Sotto i 1000px `main` e `aside` hanno `order: 0` (il default), quindi compaiono **prima** dell'`header`, che ha `order: 1`. Per portare il `nav` a sinistra da 1000px in su servirebbe `nav { order: 1 }`, `main { order: 2 }`, `aside { order: 3 }`. La variante `es-layout-resp-fix.html` aggiunge `.container { width: 680px; margin: 0 auto; position: relative; }` (e `width: 960px` da 1000px): così il `.container` è il containing block del `nav` `absolute`, e la pagina resta centrata a larghezza fissa.

> [!question] Domanda tipica d'esame
> Cosa significa "mobile first" nelle media query?
> **Risposta**: si scrivono per prime le regole per schermi piccoli (senza media query, o con `min-width` minimo), e si usano media query con `min-width` crescente per **aggiungere** stile man mano che lo schermo si allarga — al contrario del "desktop first", che parte da `max-width`. Esempio dal test d'appello: con `.card { display: block; }` e `@media (min-width: 768px) { .card { display: flex; } }` la strategia è **mobile first**, perché parte dallo stile per lo schermo piccolo e usa `min-width`; il valore 768px non rende la strategia desktop first.
### Media flessibili e immagini responsive
Oltre a viewport e media query, un sito responsive ha bisogno di **media flessibili**: immagini e video che si adattano alla larghezza del contenitore invece di restare fissi o di "rompere" il layout.

> [!quote] Definizione — media flessibili
> Un media flessibile (immagine, video, `<object>`…) usa `max-width: 100%` invece di una `width` fissa: si restringe se il contenitore è più piccolo di lui, ma non supera mai la sua dimensione originale (slide PW09 p.35: «non posso impostare width ed height»). La stessa tecnica vale per video, `<object>` e altri elementi. Problema: le immagini grandi occupano molta banda e il sito risulta lento.

```css
img {
  max-width: 100%;
}
```

Variante *(extra, non da slide)*: `video` nel selettore e `height: auto` per mantenere le proporzioni.

```css
img, video {
  max-width: 100%;
  height: auto;
}
```

> [!warning] Trabocchetto — max-width, non width: 100%
> `width: 100%` forza il media a riempire **sempre** il contenitore, ingrandendolo oltre le sue dimensioni reali (con perdita di qualità) se il contenitore è più largo dell'originale. `max-width: 100%` invece limita solo il caso in cui il contenitore è più piccolo, senza mai ingrandire il media oltre la sua risoluzione nativa.

Anche uno sfondo (`background-image`) può adattarsi al box che lo contiene con `background-size`:

> [!info] background-size: contain vs cover
> - `contain`: l'immagine si ridimensiona per stare **tutta dentro** il box (può lasciare spazio vuoto). *(extra, non da slide: mantenendo le proporzioni)*
> - `cover`: l'immagine si ridimensiona per **riempire tutto** il box (può tagliarne una parte). *(extra, non da slide: mantenendo le proporzioni)*

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

*(extra, non da slide)* `min-device-width` si riferisce alla larghezza dello **schermo del dispositivo** e non a quella del viewport come `min-width`; è una feature deprecata, e l'esempio della slide la usa come equivalente di «da 400px in su».

Per le immagini `<img>` (non di sfondo), l'elemento `<picture>` con più `<source>` permette di servire un file diverso a seconda della larghezza dello schermo, ciascuno con la propria media query:

```html
<picture>
  <source media="(min-width: 650px)" srcset="img_pink_flowers.jpg">
  <source media="(min-width: 465px)" srcset="img_white_flower.jpg">
  <img src="img_orange_flowers.jpg" alt="Flowers" style="width:auto;">
</picture>
```

*(extra, non da slide)* Il browser usa il primo `<source>` la cui media query è soddisfatta; se nessuna lo è, ricade sull'`<img>` finale, che funge anche da fallback per i browser che non supportano `<picture>`.

> [!question] Domanda tipica d'esame
> Perché per le immagini responsive si usa `max-width: 100%` e non `width: 100%`?
> **Risposta**: `width: 100%` fa espandere l'immagine al 100% del contenitore, anche oltre la sua dimensione reale, degradandone la qualità. `max-width: 100%` invece ferma il ridimensionamento quando il contenitore è più grande dell'immagine, e la restringe solo se il contenitore è più piccolo. Con questa tecnica non si impostano insieme `width` e `height`.
## CSS variables (custom properties)
Ripetere lo stesso valore (un colore, uno spazio) in decine di regole rende il CSS difficile da mantenere: le variabili CSS risolvono il problema. Nella slide PW10 p.2-3 («Old way») il colore `#1e90ff` è scritto a mano in quattro regole; con le variabili si dichiara una volta sola (p.4-6, «Custom Properties»).

> [!quote] Definizione — Custom Property
> Una *custom property* (variabile CSS) è una proprietà il cui nome inizia con `--`, dichiarata dentro un selettore; il suo valore si legge con la funzione `var()`. È **ereditata dai discendenti** del selettore in cui è definita, come le normali proprietà CSS ereditabili.

Esempio della slide PW10 p.4-6:

```css
:root {
  --blue: #1e90ff;
  --white: #ffffff;
}
body { background-color: var(--blue); }
h2 { border-bottom: 2px solid var(--blue); }
.container {
  color: var(--blue);
  background-color: var(--white);
  padding: 15px;
}
button {
  background-color: var(--white);
  color: var(--blue);
  border: 1px solid var(--blue);
  padding: 5px;
}
```

Esempio nostro *(extra, non da slide)*:

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

- **Variabili globali**: definite nell'elemento root, cioè sul selettore `:root` (la radice del documento, l'elemento `<html>`), sono visibili in tutta la pagina (slide PW10 p.9).
- **Variabili locali**: definite su un selettore qualunque, sono visibili solo su quell'elemento e sui suoi discendenti (slide p.10): `.alert { --alert-color: #ff6f69; }` e poi `.alert p { color: var(--alert-color); border: 1px solid var(--alert-color); }`.
- La sintassi è `var( <custom-property-name> , <declaration-value>? )` (slide p.7-8): il secondo argomento è opzionale ed è il valore di fallback, usato se la variabile non è definita. Esempio della slide: `.component .header { color: var(--header-color, blue); }` e `.component .text { color: var(--text-color, black); }`. Nel nostro esempio: `var(--colore-primario, black)`.

> [!example] Ridefinire una variabile in una media query
> Esempio della slide PW10 p.11 («Posso riscrivere il valore di una variabile»):
> ```css
> :root {
>   --main-font-size: 16px;
> }
> @media all and (max-width: 600px) {
>   :root { --main-font-size: 12px; }
> }
> ```
> Esempio nostro *(extra, non da slide)*:
> ```css
> :root {
>   --colonne: 1;
> }
> @media (min-width: 700px) {
>   :root { --colonne: 3; }
> }
> .griglia {
>   display: grid;
>   grid-template-columns: repeat(var(--colonne), 1fr);
> }
> ```
> Cambiando solo il valore della variabile dentro la media query, tutte le regole che la usano si aggiornano automaticamente, senza duplicare l'intera dichiarazione di `.griglia`. Senza `display: grid` la proprietà `grid-template-columns` verrebbe ignorata.

> [!question] Domanda tipica d'esame
> Come si dichiara una variabile CSS globale e come si usa? Che cosa succede se la variabile non è definita?
> **Risposta**: si dichiara una custom property (nome che inizia con `--`) nell'elemento root, `:root { --blue: #1e90ff; }`, e si legge con `var(--blue)`, ad esempio `body { background-color: var(--blue); }`. Se la variabile non è definita si usa il secondo argomento di `var()` come valore di fallback: `var(--blue, black)`. Una variabile dichiarata in un selettore (locale) è visibile solo in quell'elemento e nei suoi discendenti.
## Bootstrap: la griglia a 12 colonne
Bootstrap è un framework CSS che fornisce, tra le altre cose, un sistema di griglia pronto all'uso, esposto tramite **classi HTML** invece che tramite CSS scritto a mano. *(extra, non da slide)* È costruito sugli stessi principi di Grid e Flexbox.

Il concetto di *grid system* (slide PW10 p.13-20) è illustrato con la sovrapposizione di una griglia di colonne a pagine reali (un giornale, un sito aziendale). La figura «Struttura» (p.16) ne dà i termini: le **colonne** (*column*), separate da spazi (**gutter**), formano una **riga** (*row*) dentro un **container**. Il «960 grid system» usa una pagina larga 960px: la slide p.17 la mostra divisa in 16 colonne, quella di p.18 («960 gs») come griglia a 12 colonne con le larghezze possibili di una o più colonne unite (60, 140, 220, …, 940px). Bootstrap e W3.CSS sono i framework responsive con una griglia già pronta (p.19).

> [!info] Perché Bootstrap (dalle slide)
> - **Facile da usare**: bastano conoscenze di base di HTML e CSS.
> - **Responsive**: la griglia si adatta automaticamente a telefoni, tablet e desktop.
> - **Mobile-first**: gli stili di base sono pensati per schermi piccoli e vengono estesi verso l'alto (come nella sezione precedente). La slide PW10 p.34 dice «In Bootstrap 3, mobile-first styles are part of the core framework»; la tabella sotto è di Bootstrap 5.
> - **Compatibilità**: funziona su tutti i browser moderni (Chrome, Firefox, Internet Explorer, Safari, Opera).

> [!quote] Definizione — griglia Bootstrap
> La griglia di Bootstrap si basa su tre livelli annidati: un `.container` (larghezza massima, centrato), che contiene una o più `.row` (righe), che contengono le `.col-*` (colonne). La riga è divisa in **12 colonne** virtuali; ogni `.col-*` dichiara quante di queste 12 colonne occupa.

Per usarlo si collega il suo foglio di stile (nell'esempio del docente, da CDN) e si inserisce il meta viewport già visto:

```html
<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
```

Esempio nostro *(extra, non da slide)*, la struttura minima `container` / `row` / `col-*`:

```html
<div class="container">
  <div class="row">
    <div class="col-md-8">contenuto principale</div>
    <div class="col-md-4">barra laterale</div>
  </div>
</div>
```

Le classi `col-*` includono un **breakpoint** nel nome (`sm`, `md`, `lg`, `xl`, e `xxl` in Bootstrap 5): la colonna occupa la larghezza indicata solo a partire da quel breakpoint, applicando esattamente la logica mobile-first vista sopra (min-width crescenti).

> [!info] Breakpoint della griglia Bootstrap
> | Breakpoint | Prefisso classe | Si applica da | Larghezza massima del `.container` |
> |---|---|---|---|
> | `xs` | `.col-` (senza suffisso) | sempre (< 576px) | nessuna (100%) *(extra, non da slide: la slide dice «None (auto)»)* |
> | `sm` | `.col-sm-` | ≥ 576px | 540px |
> | `md` | `.col-md-` | ≥ 768px | 720px |
> | `lg` | `.col-lg-` | ≥ 992px | 960px |
> | `xl` | `.col-xl-` | ≥ 1200px | 1140px |
> | `xxl` (solo Bootstrap 5; l'esempio del docente usa 4.4.1) | `.col-xxl-` | ≥ 1400px | 1320px |
>
> Un `.container-fluid` invece è sempre largo il 100%, a qualunque breakpoint *(extra, non da slide: le slide ne mostrano solo il markup)*.
>
> La tabella è quella della slide PW10 p.35, che è la tabella di Bootstrap 5 e include `xxl`. L'esempio del docente (`bootstrap-test-final.html`) carica invece **Bootstrap 4.4.1**, che arriva solo fino a `xl` e non ha le classi `.col-xxl-`; gli altri valori coincidono. Altre righe della slide: 12 colonne, gutter di 1.5rem (.75rem a sinistra e a destra), gutter personalizzabili, griglia annidabile (*nestable*) e riordinabile (*column ordering*).

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
> Su schermi medi (`md`, tablet) header, menu e footer occupano tutta la riga (12/12) uno sotto l'altro, mentre main e aside si affiancano (8+4=12). Sotto `md` (`xs`, `sm`) nessuna classe `col-md-*` si applica e tutti gli elementi sono impilati a larghezza piena. Su schermi grandi (`lg`, desktop) menu, main e aside si affiancano tutti e tre (3+6+3=12), mentre header e footer restano a riga intera: lo stesso markup produce layout diversi solo cambiando le classi, senza scrivere media query a mano. Confrontalo con `bootstrap-test-start.html`, che parte dagli stessi tag [[02 - HTML semantico e form|semantici]] senza alcuna classe di griglia.

Esempi della slide PW10 p.36-39. Dentro `.container` (larghezza massima centrata) due colonne `col-sm-6` (6+6=12) affiancate da `sm` in su e impilate sui telefoni; con `.container-fluid` la larghezza è sempre il 100%; con `col-sm-3` e `col-sm-9` le colonne sono 3+9. Più classi di breakpoint nello stesso elemento si combinano: `col-sm-3 col-md-6` e `col-sm-9 col-md-6` danno 3+9 da `sm` e 6+6 da `md`.

```html
<div class="container-fluid">
  <h1>Hello World!</h1>
  <div class="row">
    <div class="col-sm-3 col-md-6" style="background-color:yellow;"><p>Lorem ipsum...</p></div>
    <div class="col-sm-9 col-md-6" style="background-color:pink;"><p>Sed ut perspiciatis...</p></div>
  </div>
</div>
```

> [!question] Domanda tipica d'esame
> In Bootstrap, che cosa produce `<div class="col-sm-3 col-md-6">` dentro una `.row`?
> **Risposta**: sotto il breakpoint `sm` (< 576px) la colonna occupa tutta la riga; da `sm` in su occupa 3 colonne su 12 (25%); da `md` in su (≥ 768px) occupa 6 colonne su 12 (50%). Le colonne di una riga si sommano su una griglia di **12**, e la logica è mobile first (valgono i `min-width` crescenti).

> [!warning] Trabocchetto — colonne senza .row o .container
> Le classi `.col-*` funzionano solo se l'elemento è figlio diretto di una `.row`, a sua volta dentro un `.container` (o `.container-fluid`): usare `.col-md-6` fuori da questa struttura produce un layout rotto, perché Bootstrap calcola larghezze e *(extra, non da slide)* margini negativi assumendo quella gerarchia.
## Riferimenti
- `PW07-CSS-3.pdf`: "Cambiare il display" (p. 40), "LISTE" / list-style (p. 41-45; la slide p. 46 è vuota). Box model, box-sizing, margin collapsing, background (p. 1-27, 29-39) e pseudo-classi dei link (p. 53-55) sono trattati in [[03 - CSS - selettori, specificità e box model]] (che copre anche `reset.css`, corrispondente alla slide di p. 58); le pagine su ancore, `target` e link a mail/telefono (p. 47-51) sono trattate in [[02 - HTML semantico e form#Ancore: link a punti specifici di una pagina]].
- `PW08-CSS-HTML-4.pdf`: "Proprietà position" e "Modalità di posizionamento" (p. 4-6), "Gestire sovrapposizioni" / z-index (p. 7), "float" e "clear dei float" (p. 9-17, con gli esempi `ogre-fl.html` e `float-test.html` e i rimandi a esempi esterni di dropdown, menu fisso e navbar a p. 8 e p. 17), "FLEXBOX DISPLAY" (p. 18-27), "Menu" (p. 28: navigazione verticale o orizzontale con una lista `ul`, esempi `test-menu.html` e `test-menu-sub.html`, non presenti nel repository).
- `PW09-CSS-HTML-5.pdf`: "Layout delle pagine" e confronto fixed vs fluid (p. 1-7), "SITI RESPONSIVE", viewport e meta tag (p. 8-16), "MEDIA query" (p. 17-25), "Breakpoints", "Strategie per le MQ", "Mobile first", "Graceful Degradation vs. Progressive Enhancement" ed esempi (p. 26-33), "Altre tecniche responsive" / media flessibili, `background-size`, `<picture>` (p. 34-38).
- `PW10-CSS-HTML-6.pdf`: "CSS Variables" (p. 1-11), "Grid Layout e Bootstrap" e concetto di grid system (p. 12-20), "CSS grid", grid lines, grid template, posizionamento degli item e page layout (p. 21-32), "GRID FRAMEWORKS" (p. 33), Bootstrap, tabella dei breakpoint ed esempi grid 1-4 (p. 34-40).
- Esempi del docente: `Materiale Didattico/Esempi/08-1-grid/grid-layout-test-start.html` e `-final.html` (grid-template-areas); `Materiale Didattico/Esempi/08-2-bootstrap/bootstrap-test-start.html` e `-final.html` (griglia Bootstrap); `Materiale Didattico/Esempi/live/es7/es-flex.html`, `es-mq.html` (media query desktop first con `max-width`), `es-layout-resp.html` e `es-layout-resp-fix.html` (Flexbox e media query mobile first, con `order`).
