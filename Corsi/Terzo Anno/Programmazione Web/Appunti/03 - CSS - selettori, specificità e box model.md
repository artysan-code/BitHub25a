---
tags:
  - programmazione-web
  - css
slide:
  - "PW05-CSS-1.pdf"
  - "PW06-CSS-2.pdf"
  - "PW07-CSS-3.pdf"
---
# CSS - selettori, specificità e box model
Il **CSS** (Cascading Style Sheets) è il linguaggio che descrive come una pagina HTML deve essere *presentata*: colori, font, spaziature, bordi, sfondi. Questa nota copre le basi indispensabili prima del layout vero e proprio (Flexbox, Grid, posizionamento, responsive), trattato in [[04 - CSS - layout, Flexbox, Grid e responsive]]: come si scrive una regola CSS, come si scelgono gli elementi da stilizzare con i **selettori**, come il browser risolve i conflitti tra regole (**cascata**, **ereditarietà**, **specificità**) e come è fatto lo spazio occupato da ogni elemento (il **box model**). Sono argomenti molto presenti nel test a risposta multipla dell'esame, spesso con calcoli numerici precisi da saper rifare a mano.
## Cos'è il CSS e perché separare contenuto e stile
Il CSS è uno standard **W3C**, un linguaggio indipendente con una propria sintassi (non è HTML). Esiste per un motivo preciso: **separare il contenuto dalla resa visiva**. L'HTML descrive la struttura e il significato di una pagina (vedi [[02 - HTML semantico e form]]); il CSS descrive come quella struttura viene mostrata. Il browser combina i due documenti — HTML e CSS — per disegnare la pagina finale.

Questa separazione ha due conseguenze pratiche:
- lo **stesso HTML** può avere **presentazioni completamente diverse** cambiando solo il foglio di stile (è l'idea dimostrata dal progetto [CSS Zen Garden](https://csszengarden.com/pages/alldesigns/), dove la stessa pagina appare come decine di siti diversi);
- il CSS **uniforma la visualizzazione tra browser** diversi, che altrimenti avrebbero stili predefiniti (gli *user-agent stylesheet*) leggermente differenti.

> [!quote] Definizione — CSS
> Il **CSS (Cascading Style Sheets)** è il linguaggio che definisce la presentazione di un documento HTML (o XML): font, colori, spaziature, layout. È separato dal contenuto, che resta responsabilità dell'HTML.
## Come si include il CSS: inline, interno, esterno
Esistono tre modi per collegare regole CSS a una pagina HTML.
### External style sheet
Il modo più comune e consigliato: le regole vivono in un **file `.css` separato**, collegato con il tag `<link>` dentro `<head>`.

```html
<head>
  <link rel="stylesheet" type="text/css" href="theme.css">
</head>
```

Vantaggi: un solo file può essere riusato da più pagine, ed è cacheable dal browser separatamente dall'HTML. Lo stesso tag `<link>` si usa anche per collegare altre risorse alla pagina, ad esempio la favicon:

```html
<link rel="icon" href="demo_icon.gif" type="image/gif">
```
### Internal style element
Le regole sono scritte direttamente nell'`<head>` della pagina, dentro un tag `<style>`.

```html
<head>
  <style>
    p { color: darkblue; }
  </style>
</head>
```

Utile per pagine singole o esempi rapidi, ma non riusabile tra pagine diverse.
### Inline
Lo stile è scritto direttamente sull'elemento con l'attributo `style`; si applica **solo a quell'elemento**, e più dichiarazioni si separano con `;`.

```html
<p style="color: red; font-weight: bold;">Testo</p>
```

Si usa in casi molto particolari, tipicamente per fare **override mirati** di regole esterne — proprio perché lo stile inline ha una specificità altissima (vedi [[#Specificità]]).

> [!info] Priorità tra i tre modi
> External e internal non hanno una priorità intrinseca l'uno sull'altro: quando hanno la stessa specificità, vince quello scritto **dopo** nel documento (vedi [[#Cascata]]). Lo stile **inline** invece ha sempre una specificità superiore a qualunque selettore in un file esterno o interno (a parità di `!important`), quindi normalmente vince sempre.
## Sintassi di una regola CSS
Una regola CSS è composta da un **selettore** e un **blocco di dichiarazioni** tra graffe:

```css
selettore {
  proprietà: valore;
}
```

Ogni riga `proprietà: valore;` dentro le graffe è una **dichiarazione**; l'insieme delle dichiarazioni è il **declaration block**. Ad esempio:

```css
h1 {
  color: green;
  font-size: 32px;
}
```

- `h1` → il **selettore**: dice *quali elementi* selezionare.
- `color: green;` e `font-size: 32px;` → le **dichiarazioni**.
- `color` e `font-size` → le **proprietà**.
- `green` e `32px` → i **valori**.

Una regola dice quindi: *quali elementi selezionare* e *quali proprietà applicare*. Il browser cerca nella pagina tutti gli elementi che soddisfano il selettore e applica loro le dichiarazioni; gli altri elementi non vengono toccati.
## Selettori
Il **selettore** decide il "bersaglio" di una regola. La scelta del selettore giusto dipende da quanto è generale o specifico l'elemento (o gli elementi) che si vuole colpire.
### Selettore di tipo (elemento)
Seleziona **tutti gli elementi di un certo tipo** (tag). È il selettore più generico.

```css
p {
  color: darkslategray;
}
```

Questa regola cambia il colore di *tutti* i `<p>` della pagina.
### Selettore di classe
Seleziona tutti gli elementi che hanno una certa **classe**, assegnata in HTML con l'attributo `class`. In CSS si scrive con un punto `.` seguito dal nome della classe.

```html
<h1 class="center">Titolo</h1>
<p class="center">Paragrafo</p>
```

```css
.center {
  text-align: center;
  color: red;
}
```

Elementi HTML diversi possono condividere la stessa classe: `.center` seleziona sia l'`<h1>` sia il `<p>` dell'esempio. Si può anche restringere la classe a un solo tipo di elemento, ad esempio `p.center` seleziona solo i `<p>` con classe `center`, non gli altri elementi con quella classe.
### Selettore id
Seleziona **un solo elemento specifico**, quello con un certo attributo `id`. In CSS si scrive con il simbolo `#`. Un `id` dovrebbe essere **unico** nella pagina (non condiviso tra più elementi).

```html
<p id="intro">Testo introduttivo</p>
```

```css
#intro {
  font-style: italic;
}
```

Esempio dalle slide (PW05 p.13-14): data la struttura seguente, quale selettore si usa per modellare il solo 6° `<p>`? E per il 3° e il 5° insieme? La soluzione è assegnare una **classe** ai due paragrafi da colpire insieme e un **id** al paragrafo singolo.

```html
<article>
  <p>Ciao a tutti</p>
  <p>Abbiamo iniziato il CSS</p>
  <p class="stile-cl">come fai a cambiare lo stile a me?</p>
  <p>e me no?</p>
  <p class="stile-cl">ma me si!!!</p>
  <p id="stile-id">Io voglio uno stile tutto mio</p>
  <section>
    <p>non mi scordate di me dentro la section</p>
  </section>
</article>
```

```css
.stile-cl {
  color: red;     /* 3° e 5° paragrafo */
}

#stile-id {
  color: green;   /* solo il 6° paragrafo */
}
```

> [!info] Elemento, classe, id — quando usarli
> - **Elemento** → colpisce tutti i tag di un certo tipo (più generico).
> - **Classe** → colpisce un gruppo di elementi che condividono un ruolo.
> - **Id** → colpisce un solo elemento specifico e unico nella pagina (più specifico).
>
> La scelta dipende da quanto deve essere ampio o mirato l'effetto della regola.
### Selettore universale
Il selettore `*` seleziona **tutti gli elementi** della pagina, senza eccezioni. Si usa spesso nei reset CSS (vedi [[#Reset CSS]]) per azzerare margini e padding di default; la proprietà `box-sizing` dell'esempio è spiegata in [[#box-sizing: content-box vs border-box]].

```css
* {
  box-sizing: border-box;
}
```
### Selettori composti (basati sull'albero HTML)
Un documento HTML è un **albero di elementi**: ogni tag può avere elementi **discendenti** (contenuti al suo interno, a qualunque livello), **figli** (discendenti diretti), un **genitore** (l'elemento direttamente sopra) e **fratelli** (elementi con lo stesso genitore). Per il CSS non conta solo il tipo di un elemento, ma anche *dove si trova* nell'albero.

| Combinatore | Sintassi | Seleziona |
|---|---|---|
| Discendente (spazio) | `A B` | tutti i discendenti `B` di `A`, a qualunque profondità |
| Figlio diretto | `A > B` | solo i `B` che sono figli diretti di `A` |
| Fratello adiacente | `A + B` | il `B` immediatamente successivo ad `A` (stesso genitore) |
| Fratelli generali | `A ~ B` | tutti i `B` successivi ad `A` (stesso genitore) |

```css
section p    { color: grey; }   /* tutti i <p> dentro <section>, anche annidati */
section > p  { color: blue; }   /* solo i <p> figli diretti di <section> */
h2 + p       { font-weight: bold; } /* solo il <p> subito dopo un <h2> */
```

**Esercizio 1 dalle slide** (PW05 p.20). L'albero è `html > body > header, main, footer`; `header` contiene `h1` e `p > em`, `main` contiene `h2` e `p > em`, `footer` contiene `h2 > em` e `ul` con due `li`. Le slide propongono questi selettori; gli elementi selezionati sono ricavati dall'albero *(extra, non da slide)*:

| Selettore | Elementi selezionati |
|---|---|
| `p em {color: grey;}` | i due `em` figli di un `p` (uno in `header`, uno in `main`) |
| `header p {font-size: 20px;}` | il `p` dentro `header` |
| `main p {font-size: 16px;}` | il `p` dentro `main` |
| `footer h2 {...}` | l'`h2` dentro `footer` |
| `main h2 {...}` | l'`h2` dentro `main` |
| `header em {...}` | l'`em` dentro `header` |
| `main em {...}` | l'`em` dentro `main` |

L'`em` di `footer` non è colpito da `p em`, perché il suo genitore è un `h2` e non un `p`.

**Esercizio 2 dalle slide** (PW05 p.21). Si hanno due blocchi `<div class="ricetta">`, ciascuno con un `<h2>`, un `<p>` e un `<p class="ingredienti">`:

```html
<div class="ricetta">
  <h2>...</h2>
  <p>...</p>
  <p class="ingredienti">...</p>
</div>
```

```css
p.ingredienti {...}                 /* i p con classe ingredienti */
div.ricetta {...}                   /* i div con classe ricetta */
.ricetta p {...}                    /* tutti i p discendenti di un elemento con classe ricetta */
.ricetta h2 {...}                   /* gli h2 discendenti di un elemento con classe ricetta */
.ricetta .ingredienti {...}         /* gli elementi con classe ingredienti dentro .ricetta */
div.ricetta p.ingredienti {...}     /* come sopra, ma solo p dentro div: più specifico */
```

I commenti sono ricavati dai selettori *(extra, non da slide)*.

> [!example] Discendente vs figlio diretto
> ```html
> <section>
>   <p>Primo paragrafo</p>
>   <div>
>     <p>Paragrafo annidato</p>
>   </div>
> </section>
> ```
> `section p` colpisce **entrambi** i paragrafi (anche quello dentro `<div>`), mentre `section > p` colpisce **solo** il primo, perché il secondo `<p>` non è figlio diretto di `<section>` ma di `<div>`.
### Selettore per attributo
Permette di selezionare elementi in base a un attributo HTML che già possiedono, senza dover aggiungere una classe apposita.

```css
[attributo] { }              /* elementi che hanno quell'attributo, qualunque valore */
[attributo=valore] { }       /* elementi con quel valore esatto */
```

```css
img[alt] {
  background-color: grey;    /* evidenzia le immagini che hanno un testo alternativo */
}
a[target="_blank"] {
  color: red;                 /* link che si aprono in una nuova finestra */
}
```

> [!info] Varianti per il confronto del valore
> | Selettore | Esempio | Seleziona |
> |---|---|---|
> | `[attr~=valore]` | `[title~="flower"]` | l'attributo contiene *quella parola* in una lista separata da spazi |
> | `[attr\|=valore]` | `[lang\|="en"]` | l'attributo è *esattamente* `valore` oppure inizia con `valore-` |
> | `[attr^=valore]` | `a[href^="https"]` | l'attributo **inizia** con quel valore |
> | `[attr$=valore]` | `a[href$=".pdf"]` | l'attributo **finisce** con quel valore |
> | `[attr*=valore]` | `a[href*="uniroma2"]` | l'attributo **contiene** quella sottostringa ovunque |
### Pseudo-classi
Una **pseudo-classe** seleziona un elemento in base a uno **stato speciale** in cui si trova, che non è scritto esplicitamente nell'HTML: il mouse è sopra, il link è già stato visitato, l'elemento ha il focus, la sua posizione tra i fratelli. Si scrive con `:` dopo il selettore.

```css
selettore:pseudo-classe {
  proprietà: valore;
}
```

Le pseudo-classi più comuni legate ai link e all'interazione dell'utente. Gli esempi delle slide (PW05 p.22-24) sono `a:visited` con `color: #00FF00`, `a:hover` con `color: #FF00FF` (poi `crimson`) e `input:focus` con `border: 2px solid steelblue`:

```html
<a href="#">Apri dettaglio</a>
<input type="text" placeholder="Scrivi qui">
```

```css
a:visited { color: #00FF00; }            /* link già visitato (cronologia del browser) */
a:hover   { color: crimson; }            /* il mouse è sopra il link */
input:focus { border: 2px solid steelblue; } /* l'elemento è selezionato (es. da tastiera) */
```

Le altre pseudo-classi dei link (`:link`, `:active`; PW07 p.54 le elenca senza codice) con un esempio *(extra, non da slide: i valori dei colori e `outline`)*:

```css
a:link    { color: blue; }    /* link non visitato */
a:visited { color: purple; }  /* link già visitato (cronologia del browser) */
a:focus   { outline: 2px solid orange; } /* elemento selezionato (es. da tastiera) */
a:hover   { color: magenta; } /* il mouse è sopra il link */
a:active  { color: red; }     /* nel momento esatto del click */
```

Altre pseudo-classi utili riguardano la **posizione** dell'elemento tra i fratelli: `:first-child`, `:last-child`, `:only-child`, `:first-of-type`, `:last-of-type`, `:only-of-type`, `:nth-child()`, `:nth-last-child()`, `:nth-of-type()`, `:nth-last-of-type()`, oltre a `:root` (la radice del documento, cioè `<html>`) e `:empty` (elemento senza contenuto). Esempio dalle slide (PW05 p.24):

```html
<ul>
  <li>Primo</li>
  <li>Secondo</li>
  <li>Terzo</li>
</ul>
```

```css
li:first-child  { font-weight: bold; }   /* solo il primo li */
li:nth-child(2) { color: darkgreen; }    /* solo il secondo li */
```

I link ad altre pagine o a punti precisi di una pagina (ancora `#id`, `target`, `mailto:`, `tel:`, PW07 p.47-51) sono trattati in [[02 - HTML semantico e form#Ancore: link a punti specifici di una pagina]] e [[02 - HTML semantico e form#Attributo target e altri tipi di link]].

> [!warning] Ordine delle pseudo-classi sui link
> Secondo le slide (PW07 p.54) `:hover` deve essere dichiarato **dopo** `:link` e `:visited`, e `:active` **dopo** `:hover` (la slide scrive per errore «:over»). *(Extra, non da slide: il mnemonico comune è "LVHA" — Link, Visited, Hover, Active.)* Se l'ordine è sbagliato, a parità di specificità vince la regola scritta dopo nel CSS (vedi [[#Cascata]]) e lo stato hover o active può non funzionare mai perché sovrascritto da `:link`/`:visited`.
### Pseudo-elementi
Un **pseudo-elemento** permette di stilizzare **una parte** di un elemento (ad esempio la prima lettera o la prima riga), oppure di **inserire contenuto** prima o dopo il contenuto reale dell'elemento. Si scrive con `::` (doppio due punti, per distinguerlo dalle pseudo-classi).

```css
selettore::pseudo-elemento {
  proprietà: valore;
}
```

```css
p::first-letter {
  color: #ff0000;
  font-size: xx-large;
}
```

I pseudo-elementi principali sono `::before`, `::after` (inseriscono contenuto generato via `content:` prima/dopo l'elemento), `::first-letter` e `::first-line`.

Altri esempi dalle slide (PW05 p.27): la lettera iniziale decorata e un testo inserito con `::before` e `content`, che non compare nell'HTML ma solo nella pagina visualizzata.

```html
<p>Questo paragrafo inizia con una lettera decorata.</p>
<p class="note">Messaggio importante</p>
```

```css
p::first-letter {
  font-size: 2em;
  color: darkred;
  font-weight: bold;
}

.note::before {
  content: "Attenzione: ";
  color: crimson;
  font-weight: bold;
}
```

Il secondo paragrafo viene mostrato come «Attenzione: Messaggio importante», con il testo generato da `content` in `crimson` e in grassetto.
### Raggruppare selettori
Più selettori possono condividere lo stesso blocco di dichiarazioni, separandoli con una virgola `,`.

```css
h1, h2, h3 {
  font-family: sans-serif;
  margin-bottom: 0.5em;
}
```

Equivale a scrivere tre regole identiche separate, ma evita la duplicazione.
## Cascata
Più regole CSS possono applicarsi allo **stesso elemento** contemporaneamente: questo genera un **conflitto tra dichiarazioni** che il browser deve risolvere.

```html
<p id="intro" class="note">Testo</p>
```
```css
p       { color: green; }
.note   { color: blue; }
#intro  { color: red; }
```

Il **Cascade** ("cascata") è l'algoritmo che decide quale valore vince quando più regole competono sulla stessa proprietà dello stesso elemento. Le fonti degli stili in gioco sono tre:
- gli **user-agent stylesheet**, gli stili predefiniti del browser (ad esempio `h1` è già grande e in grassetto prima di scrivere qualsiasi CSS);
- gli stili **dell'autore**, cioè quelli che scriviamo noi;
- gli stili **dell'utente**, un foglio di stile personalizzato che l'utente del browser può impostare per la propria esperienza di navigazione.

Il browser confronta le dichiarazioni in conflitto seguendo, in ordine, questi criteri:
1. **origine e importanza** (vedi [[#Ordine di precedenza (Cascading Order)]] e [[#!important]]): una dichiarazione `!important` dell'autore batte le dichiarazioni normali, ma non quelle `!important` di utente e user-agent;
2. maggiore **specificità** del selettore (vedi [[#Specificità]]);
3. a parità di specificità, vince la regola scritta **dopo** nel codice (ultimo dichiarato, ultimo applicato).

> [!example] Chi vince? (PW05 p.36)
> ```css
> p { color: blue; margin-left: 30px; }
> p { color: green; }
> ```
> Le due regole hanno **la stessa specificità** (stesso selettore `p`). Vince la seconda per `color`: il testo dei paragrafi sarà **verde**, perché scritta dopo. La dichiarazione `margin-left: 30px` non è in conflitto con nulla, quindi **il margine rimane**: solo la proprietà in conflitto viene sovrascritta, non l'intera regola.

Con le stesse due regole, se un paragrafo ha anche l'attributo `style="color: red;"` (PW05 p.37), **quel paragrafo è rosso**: domina lo stile inline. Gli strumenti per sviluppatori del browser (devtool) mostrano le dichiarazioni sconfitte barrate.

```html
<p>This is a paragraph.</p>                          <!-- verde -->
<p style="color: red;">This is another paragraph.</p> <!-- rosso: domina lo style inline -->
```

### Ordine di precedenza (Cascading Order)
Le slide (PW05 p.48, tabella ripresa da MDN) elencano l'ordine con cui si impongono le dichiarazioni, **dalla più debole alla più forte**:

| Precedenza (dal basso verso l'alto) | Origine | Importanza |
|---|---|---|
| 1 | user-agent (browser) | normal |
| 2 | user | normal |
| 3 | author (sviluppatore) | normal |
| 4 | animazioni CSS `@keyframe` | |
| 5 | author (sviluppatore) | `!important` |
| 6 | user | `!important` |
| 7 | user-agent (browser) | `!important` |
| 8 | transizioni CSS | |

Due conseguenze da ricordare. Tra le dichiarazioni **normali** vincono quelle dell'autore su quelle dell'utente e queste sul browser; tra quelle **`!important`** l'ordine si **inverte** (vince il browser, poi l'utente, poi l'autore). Quindi `!important` scritto dall'autore batte lo stile inline e qualunque selettore più specifico, ma **non** è il livello più forte della tabella: è sconfitto dagli `!important` di utente e user-agent e dalle transizioni.

> [!question] Domanda tipica d'esame
> Un autore scrive `p { color: blue !important; }` e un utente ha un proprio foglio di stile con `p { color: green !important; }`. Di che colore sono i paragrafi? E se l'autore avesse scritto `<p style="color: red;">` senza `!important`, con `p { color: blue !important; }` nel foglio?
> **Risposta**: nel primo caso **verde**: nella tabella `!important` dell'utente (6) è sopra `!important` dell'autore (5). Nel secondo caso **blu**: la dichiarazione `!important` dell'autore (5) batte quella normale (3), anche se questa è inline e quindi ha specificità `1,0,0,0`. L'ordine della tabella viene prima della specificità; la specificità conta solo tra dichiarazioni della stessa origine e importanza.
## Ereditarietà
Alcune proprietà CSS, se applicate a un elemento, si **propagano automaticamente** ai suoi discendenti anche se non hanno una regola propria: è l'**ereditarietà**. Ad esempio, se si imposta `color` su un `<p>`, uno `<span>` contenuto al suo interno erediterà lo stesso colore, a meno di regole più specifiche.

```html
<p style="color: navy;">Testo con <span>una parte</span> in evidenza.</p>
```

Non tutte le proprietà sono ereditate: quelle legate al **testo** lo sono quasi sempre (`color`, `font-family`, `font-size`, `font-weight`, `font-style`, `line-height`, `text-align`, `text-indent`, `text-transform`, `letter-spacing`, `word-spacing`, `visibility`, `list-style`, `cursor`...), mentre quelle legate al **box** dell'elemento (`margin`, `padding`, `border`, `width`, `height`, `background`...) **non** si ereditano: ogni elemento ha il proprio box indipendente (vedi [[#Box model]]).

L'elenco completo delle proprietà ereditate riportato nelle slide (PW05 p.32) è:
- testo e font: `color`, `font-family`, `font-size`, `font-style`, `font-variant`, `font-weight`, `font`, `letter-spacing`, `line-height`, `text-align`, `text-indent`, `text-transform`, `white-space`, `word-spacing`, `direction`, `quotes`, `orphans`, `widows`;
- liste: `list-style-image`, `list-style-position`, `list-style-type`, `list-style`;
- tabelle: `border-collapse`, `border-spacing`, `caption-side`, `empty-cells`;
- interfaccia: `cursor`, `visibility`;
- proprietà per la sintesi vocale: `azimuth`, `elevation`, `pitch`, `pitch-range`, `stress`, `voice-family`.

Il raggruppamento per tema e il riferimento alla sintesi vocale sono un'organizzazione dell'elenco *(extra, non da slide)*.

> [!info] Perché conta
> Sfruttare l'ereditarietà evita di ripetere le stesse dichiarazioni su ogni elemento: basta impostare `font-family` e `color` una volta su `body`, e tutti i discendenti li erediteranno finché una regola più specifica non li sovrascrive.
## Specificità
Quando più regole competono sullo stesso elemento con la stessa proprietà, e nessuna ha `!important`, il browser non guarda solo l'ordine: guarda prima **quanto è specifico** ogni selettore. Un selettore più specifico prevale su uno più generico, indipendentemente dall'ordine in cui sono scritti. In generale: **id > classe > elemento**. Più un selettore individua precisamente l'elemento, più "pesa".

> [!quote] Definizione — Specificità
> La **specificità** è un punteggio, calcolato per ogni selettore, che stabilisce quale regola vince in caso di conflitto tra dichiarazioni con la stessa importanza. Si confronta come una **tupla di quattro valori** `[a, b, c, d]`, letta da sinistra a destra: conta prima il valore più a sinistra, e solo a parità si passa al successivo.
### Come si calcola: la tupla [a, b, c, d]
- **a** → `1` se la dichiarazione è **inline** (attributo `style="..."`), `0` altrimenti.
- **b** → numero di selettori **id** (`#...`).
- **c** → numero di selettori di **classe**, **attributo** o **pseudo-classe** (`.classe`, `[attr]`, `:hover`...).
- **d** → numero di selettori di **elemento** o **pseudo-elemento** (`p`, `h1`, `::before`...).

Il selettore universale `*` non conta in nessuna colonna (vale `0,0,0,0`).

> [!example] Esempi di calcolo (dallo standard CSS, § 6.4.3)
> ```css
> * {}               /* a=0 b=0 c=0 d=0 → specificità 0,0,0,0 */
> li {}              /* a=0 b=0 c=0 d=1 → specificità 0,0,0,1 */
> li::first-line {}  /* a=0 b=0 c=0 d=2 → specificità 0,0,0,2 */
> ul li {}           /* a=0 b=0 c=0 d=2 → specificità 0,0,0,2 */
> ul ol+li {}        /* a=0 b=0 c=0 d=3 → specificità 0,0,0,3 */
> h1 + *[rel=up] {}  /* a=0 b=0 c=1 d=1 → specificità 0,0,1,1 */
> ul ol li.red {}    /* a=0 b=0 c=1 d=3 → specificità 0,0,1,3 */
> li.red.level {}    /* a=0 b=0 c=2 d=1 → specificità 0,0,2,1 */
> #x34y {}           /* a=0 b=1 c=0 d=0 → specificità 0,1,0,0 */
> style="..."        /* a=1 b=0 c=0 d=0 → specificità 1,0,0,0 */
> ```
> Si confronta **da sinistra a destra**: `#x34y` (0,1,0,0) batte `li.red.level` (0,0,2,1) perché `1 > 0` nella seconda colonna, anche se `li.red.level` ha più selettori in totale. Lo stile inline (1,0,0,0) batte qualunque selettore scritto in un file CSS, perché la prima colonna vince sempre a prescindere dal resto.

Altro esempio delle slide (PW05 p.53), tutti i selettori riferiti allo stesso elemento; come dicono le slide, **si confronta da sinistra a destra**:

```html
<p id="intro" class="note important">Benvenuti</p>
```

```css
p               /* 0,0,0,1 */
.note           /* 0,0,1,0 */
p.note          /* 0,0,1,1 */
.note.important /* 0,0,2,0 */
#intro          /* 0,1,0,0 */
style=""        /* 1,0,0,0 */
```

Nella slide p.55 è proposto anche il selettore `html body div#pagewrap ul#summer-drinks li.favorite` come esercizio di calcolo. Il risultato non è scritto sulla slide; applicando la regola si ottiene `0,2,1,5` *(extra, non da slide)*: due id (`#pagewrap`, `#summer-drinks`), una classe (`.favorite`) e cinque elementi (`html`, `body`, `div`, `ul`, `li`).

### Esempi di conflitto tra selettori
Esempi delle slide (PW05 p.39-43): mostrano come i selettori combinati (discendente, più classi) scelgono elementi diversi; nell'Esempio 1 vince la specificità, non l'ordine di scrittura.

**Esempio 1: elemento contro discendente** (p.39). `p span` (`0,0,0,2`) batte `p` (`0,0,0,1`) per il testo dentro lo `<span>`.

```css
p      { color: red; }
p span { color: green; }
```

```html
<p>This is a paragraph.</p>                                   <!-- rosso -->
<p>This is a <span>paragraph with a span</span> inside.</p>   <!-- span verde, resto rosso -->
```

**Esempio 2: classi sulle sezioni** (p.40): `.news p` rende verdi i paragrafi dentro `<section class="news">` e `.blog p` rossi quelli dentro `<section class="blog">`.
**Esempio 3: id sulle sezioni** (p.41): stesso risultato con `#news p` (verde, `0,1,0,1`) e `#blog p` (rosso) per `<section id="news">` e `<section id="blog">`; con le classi del caso precedente `.news p` vale `0,0,1,1`.
**Esempio 4: combinazione di regole** (p.42):

```css
section      { color: grey; }
.news .mark  { font-weight: bold; }
.blog .mark  { color: orange; }
```

```html
<section class="news">
  <p>This is a paragraph in sec news.</p>                          <!-- grigio -->
  <p class="mark">This is a another paragraph in sec news.</p>     <!-- grigio, grassetto -->
</section>
<section class="blog">
  <p class="mark">This is a paragraph in sec blog.</p>             <!-- arancione -->
  <p>This is a another <span class="mark">paragraph</span> in sec blog.</p> <!-- span arancione, resto grigio -->
</section>
```

Il grigio di `section` è **ereditato** dai `<p>`, quindi `.news .mark` cambia solo il peso del carattere e `.blog .mark` cambia il colore solo dove è presente la classe `mark`.

**Esempio 5: classi sullo stesso elemento contro classi su elementi diversi** (p.43), con `<section class="news mark">`:

```css
.news.mark  { font-weight: bold; }
.news .mark { color: orange; font-weight: normal; }
```

```html
<section class="news mark">
  <p>This is a paragraph in sec news.</p>                   <!-- grassetto -->
  <p class="mark">This is a another paragraph in sec news.</p> <!-- arancione, peso normale -->
</section>
```

`.news.mark` (senza spazio) seleziona gli elementi che hanno **entrambe** le classi: qui la `<section>`, il cui grassetto è ereditato dal primo paragrafo. `.news .mark` (con lo spazio) seleziona i **discendenti** con classe `mark` di un elemento con classe `news`: qui il secondo paragrafo, che sovrascrive il grassetto ereditato con `font-weight: normal`.

### Notazione a tre valori usata nel test
Le slide usano la tupla a **quattro** valori `[a, b, c, d]` (PW05 p.52), con la prima colonna per lo stile inline. Il test d'esame usa invece la forma a **tre valori** (ID, classi/attributi/pseudo-classi, elementi), senza la colonna dello stile inline: coincide con gli ultimi tre valori della tupla a quattro, quindi `0,1,1,1` nelle slide diventa `(1,1,1)` nel test. Lo stile inline non compare perché nelle domande si confrontano solo selettori scritti nei fogli di stile. La regola del confronto è la stessa: si legge da sinistra a destra.

| Selettore | Calcolo | Tupla a 4 valori (slide) | Forma a 3 valori (test) |
|---|---|---|---|
| `#menu .voce a` | 1 id, 1 classe, 1 elemento | `0,1,1,1` | `(1,1,1)` |
| `form input[type="email"]` | 0 id, 1 attributo (conta come classe), 2 elementi | `0,0,1,2` | `(0,1,2)` |
| `ul li.attivo > a:hover` | 0 id, 1 classe + 1 pseudo-classe, 3 elementi (`ul`, `li`, `a`) | `0,0,2,3` | `(0,2,3)` |

Il combinatore (spazio, `>`, `+`, `~`) **non** aggiunge nulla al punteggio. I primi due esempi vengono dalle domande del test reale (cartella `Risorse Studenti`) e il terzo è un esercizio costruito in questa nota *(extra, non da slide)*.

### Classi multiple
Un elemento può avere più classi contemporaneamente (separate da spazio nell'attributo `class`); ogni classe nel selettore aumenta il conteggio della colonna `c`. Esempio dalle slide (PW05 p.44): due link con classi comuni `btn` e una classe specifica per colore.

```html
<a class="btn btn-danger" href="">Pericolo</a>
<a class="btn btn-success" href="">Hai vinto</a>
```
```css
.btn {
  font-size: 18px; color: white; margin: 10px;
  padding: 10px; display: block; width: 100px;
}
.btn-danger  { background: red; }    /* primo link: sfondo rosso */
.btn-success { background: green; }  /* secondo link: sfondo verde */
```

Le classi si combinano: entrambi i link ricevono lo stile di `.btn` (stessa forma) e solo il colore dello sfondo cambia secondo la seconda classe. *(Extra, non da slide)* Un selettore con due classi concatenate è più specifico di ciascuna delle due singole:

```css
.btn         { padding: 10px; }         /* specificità 0,0,1,0 */
.btn-danger  { background: red; }       /* specificità 0,0,1,0 */
.btn.btn-danger { font-weight: bold; }  /* specificità 0,0,2,0 — più specifico di entrambe */
```

Riprendiamo l'esempio di [[#Cascata]] (`<p id="intro" class="note">`, con `p`, `.note`, `#intro` che impostano `color` in modo diverso): con la specificità in mano si può ora rispondere senza ambiguità.

> [!question] Domanda tipica d'esame
> Dati `p { color: green }`, `.note { color: blue }`, `#intro { color: red }` applicati allo stesso `<p id="intro" class="note">`, di che colore sarà il testo?
> **Risposta**: rosso. Le specificità sono `p` → `0,0,0,1`, `.note` → `0,0,1,0`, `#intro` → `0,1,0,0`: `#intro` ha un id (`b=1`), che batte sia il selettore di classe (`c=1`) sia quello di elemento (`d=1`), perché si confronta prima la colonna `b`. L'ordine di scrittura nel file conta solo a **parità** di specificità.

> [!question] Domanda tipica d'esame
> Qual è la specificità di `#menu .voce a`, espressa come (ID, classi/attributi/pseudo-classi, elementi)? E quella di `form input[type="email"]`?
> **Risposta**: `#menu .voce a` vale **(1,1,1)**: un id, una classe, un elemento. `form input[type="email"]` vale **(0,1,2)**: nessun id, **un** selettore di attributo (che conta come una classe) e due elementi (`form`, `input`). Una risposta come `(0,0,3)` dimentica che il selettore di attributo conta come una classe.
## !important
La dichiarazione `!important`, scritta dopo il valore, fa sì che una regola **non venga sovrascritta** da un'altra regola dell'autore con specificità maggiore (ma normale) — batte anche lo stile inline. Resta però sotto gli `!important` di utente e user-agent (vedi [[#Ordine di precedenza (Cascading Order)]]).

```css
p {
  color: blue !important;
}
```

> [!warning] Usare !important con parsimonia
> `!important` si usa in **casi molto particolari**: nella pratica è quasi sempre possibile evitarlo scegliendo un selettore con la specificità giusta. Abusarne rende il CSS difficile da mantenere, perché rompe il normale meccanismo della cascata e obbliga a usare altri `!important` per sovrascriverlo a sua volta.
## Unità di misura
Le proprietà che accettano una lunghezza (`font-size`, `width`, `margin`, `padding`...) possono usare diverse unità, che si dividono in **assolute** e **relative**.

| Unità | Tipo | Cos'è relativa a |
|---|---|---|
| `px` | assoluta | pixel dello schermo (non scala) |
| `%` | relativa | il valore ereditato (per `font-size`, quello del genitore) |
| `em` | relativa | il `font-size` **corrente** dell'elemento (*extra, non da slide:* per la proprietà `font-size` stessa, `em` e `%` si riferiscono al `font-size` del genitore; per `width`, `margin`, `padding` a quello dell'elemento) |
| `rem` | relativa | il `font-size` dell'elemento **root** (`<html>`) |
| `vw` | relativa | 1% della **larghezza** della viewport (l'area visibile della finestra del browser, *extra, non da slide*) |
| `vh` | relativa | 1% dell'**altezza** della viewport |
| `vmin` | relativa | il più piccolo tra `vw` e `vh` |
| `vmax` | relativa | il più grande tra `vw` e `vh` |
| `ch` | relativa | larghezza approssimativa del carattere "0" nel font corrente |

> [!example] % ed em in cascata
> ```css
> body { font-size: 100%; }     /* circa 16px, la dimensione di default del browser */
> h1   { font-size: 150%; }     /* 150% di 16px = 24px */
> p    { font-size: 0.875em; }  /* 0.875 × 16px = 14px */
> ul   { font-size: 1.2857em; } /* 1.2857 × 14px (il font-size ereditato da p) ≈ 18px */
> ```
> `em` e `%` si calcolano rispetto al font-size **ereditato dal genitore**, quindi si accumulano annidando elementi: `ul` qui parte dai 14px di `p`, non dai 16px di `body`.

Le unità relative rendono il testo più **scalabile**: se l'utente cambia la dimensione del font di default del browser, tutto ciò che è espresso in `em`/`rem`/`%` si adatta di conseguenza, mentre `px` resta fisso. *(extra, non da slide)* Per questo motivo `rem` è spesso preferito a `em` per il `font-size` nei progetti reali: essendo relativo solo alla radice del documento, non si accumula annidando elementi come invece fa `em`.

> [!question] Domanda tipica d'esame
> **a)** Con `body { font-size: 100%; }` (16px), `p { font-size: 0.875em; }` e `ul { font-size: 1.2857em; }` con l'`ul` dentro il `p`, quanto vale il `font-size` dell'`ul`?
> **b)** Dati `#content p { font-size: 1.5em; }` e `p { font-size: 120%; }`, con un `<div id="content">` che contiene due `<p>` e un terzo `<p>` fuori dal div, che dimensione hanno i tre paragrafi?
> **Risposta a)**: circa **18px**. `em` e `%` si calcolano sul `font-size` del genitore: il `p` vale `0.875 × 16 = 14px`, l'`ul` vale `1.2857 × 14 ≈ 18px` (non `1.2857 × 16`).
> **Risposta b)**: i due `<p>` in `#content` hanno `font-size` pari a **1.5 volte quello del genitore** (il `div`, che eredita dal `body` la dimensione di sistema); il `<p>` fuori resta al **120%**. Le due regole competono sui `<p>` interni e vince `#content p` (`0,1,0,1`) su `p` (`0,0,0,1`) per la specificità, indipendentemente dall'ordine; l'unità (`em` contro `%`) non entra nel confronto, serve solo a calcolare il valore finale.
## Colori
Il colore si specifica più spesso con la proprietà `color` (testo) o `background-color` (sfondo). I formati disponibili sono:

```css
p { color: tomato; }                 /* parola chiave */
p { color: #ff6347; }                /* esadecimale: RR GG BB */
p { color: rgb(255, 99, 71); }       /* rosso, verde, blu: 0-255 ciascuno */
p { color: rgba(255, 99, 71, 0.5); } /* rgb + canale alfa (trasparenza, 0-1) */
```

I tre valori di `rgb()` sono le quantità di rosso, verde e blu, ciascuna un byte (PW06 p.26). Per ogni colore si può indicare la **percentuale** del colore, oppure un valore numerico **decimale da 0 a 255** o **esadecimale da `0x00` a `0xFF`** (in CSS si scrive `#RRGGBB`, vedi sopra). Esempio con le percentuali *(extra, non da slide)*: `rgb(100%, 0%, 0%)` è il rosso puro, uguale a `rgb(255, 0, 0)` e a `#ff0000`. `rgba()` aggiunge un quarto valore, il **canale alfa**, che controlla la trasparenza: `0` è completamente trasparente, `1` completamente opaco. `color` è una proprietà **ereditata** (vedi [[#Ereditarietà]]), quindi va sempre garantito un buon contrasto con lo sfondo.
## Font e testo
### font-family
La proprietà `font-family` specifica il font del testo. Si indica una **lista di font in ordine di preferenza** (un *font stack*): se il primo non è disponibile sul dispositivo dell'utente, il browser prova il successivo, fino all'ultimo, che dovrebbe essere una **famiglia generica** (`serif`, `sans-serif`, `monospace`) sempre disponibile.

Esempio delle slide (PW06 p.4):

```css
body { font-family: Arial; }
code { font-family: Courier, monospace; }
p    { font-family: "Times New Roman", Times, serif; }
```

Il browser prova il primo font; se non è disponibile passa al successivo. Più in generale si indica il font desiderato seguito da alternative simili (*font stack*, PW06 p.10):

```css
body { font-family: Arial, Helvetica, sans-serif; }
code { font-family: "Courier New", Courier, monospace; }
p    { font-family: Georgia, "Times New Roman", Times, serif; }
```

Altri stack proposti nelle slide: `Verdana, Geneva, sans-serif`; `Tahoma, Geneva, sans-serif`; `"Trebuchet MS", Arial, Helvetica, sans-serif`; `"Arial Black", Gadget, sans-serif`. Le slide (PW06 p.9) rimandano a [cssfontstack.com](https://www.cssfontstack.com/) per vedere quali font sono disponibili sui vari sistemi.

Lo stack di font serve perché **i font dipendono dal sistema operativo**: non tutti i font sono installati su tutti i dispositivi, quindi affidarsi a un solo nome rischia di non funzionare per una parte degli utenti. In alternativa ai font di sistema esistono i **web font**: caricati da un file nel progetto con la regola `@font-face`, oppure da un servizio esterno come Google Fonts (di solito collegato con `<link>`, come un normale foglio di stile esterno).

> [!question] Domanda tipica d'esame
> Che cosa fa `p { font-family: "Duru Sans", Verdana, sans-serif; }`?
> **Risposta**: il browser usa il **primo font disponibile nel sistema dell'utente**, scorrendo la lista nell'ordine indicato: `"Duru Sans"` se installato, altrimenti `Verdana`, altrimenti la famiglia generica `sans-serif`, che è sempre disponibile. Non scarica font da internet (per quello servono i web font con `@font-face` o `<link>`) e non dipende dalla versione di CSS: dipende dal fatto che **i font cambiano da un sistema operativo all'altro**.
### Dimensioni e spaziatura del testo
```css
p {
  font-size: 1rem;        /* dimensione del testo */
  font-weight: bold;      /* quanto è marcato: normal | bold | 100-900 */
  font-style: italic;     /* normal | italic */
  line-height: 1.5;       /* altezza della riga, influisce sulla leggibilità */
  letter-spacing: 0.5px;  /* spaziatura tra le lettere */
  word-spacing: 2px;      /* spaziatura tra le parole */
}
```

`font-size` accetta (PW06 p.15) una lunghezza o una percentuale (`length unit | percentage`), le parole chiave assolute `xx-small | x-small | small | medium | large | x-large | xx-large` oppure quelle relative al genitore `smaller | larger`. `letter-spacing` e `word-spacing` accettano una lunghezza o `normal` (PW06 p.33), ad esempio `p { letter-spacing: 8px; }` e `p { word-spacing: 1.5em; }`.

`line-height` accetta un numero puro (moltiplicatore del font-size, es. `2`), una lunghezza (`2em`) o una percentuale (`200%`): valori troppo piccoli o troppo grandi rendono il testo più difficile da leggere.
### Proprietà abbreviata: font
Le proprietà viste finora per il font (`font-style`, `font-weight`, `font-size`, `line-height`, `font-family`, oltre a `font-variant`) si possono impostare tutte insieme con la forma abbreviata `font`.

```css
p {
  font: italic small-caps bold 34px/100px "Times New Roman", Times, serif;
}
```

> [!warning] Ordine obbligatorio della forma abbreviata
> - `font-style`, `font-variant`, `font-weight` sono **opzionali**, ma se presenti devono precedere dimensione e famiglia; se si omettono, quelle proprietà (e `line-height`) non vengono ereditate dal genitore.
> - `font-size` e `font-family` sono **obbligatori**: se manca anche uno solo, l'intera dichiarazione `font` viene ignorata.
> - `line-height`, se presente, va subito dopo `font-size` separata da `/` (senza `line-height` si omette anche lo slash).
> - `font-family` deve sempre essere **l'ultimo** valore.
### Allineamento e decorazione
```css
p {
  text-align: center;        /* left | right | center | justify */
  text-decoration: underline;/* none | underline | overline | line-through | blink */
  text-transform: uppercase; /* none | capitalize | lowercase | uppercase */
  text-indent: 2em;          /* rientro della prima riga */
  text-shadow: 2px 2px 4px gray; /* offset orizzontale, verticale, sfocatura, colore */
}
```

`text-indent` accetta una lunghezza o una percentuale, anche **negativa** (PW06 p.31). Gli esempi delle slide usano `p#1`, `p#2`, `p#3` come selettori (*extra, non da slide*: in CSS un id che inizia con una cifra richiede l'escape, qui servono solo come esempio):

```css
p#1 { text-indent: 2em; }
p#2 { text-indent: 25%; }
p#3 { text-indent: -35px; }
```

> [!warning] `text-decoration: blink`
> Il valore `blink` (testo lampeggiante) esiste nello standard ma *(extra, non da slide)* i browser moderni lo ignorano: non ha più alcun effetto visibile.

La proprietà `vertical-align` allinea un elemento inline (o il contenuto di una cella di tabella) rispetto alla linea di base, con valori come `text-top`, `middle`, `baseline`.
## Box model
Ogni elemento HTML, quando viene disegnato dal browser, occupa un **rettangolo** chiamato **box**. Tutte le proprietà di dimensionamento (`width`, `height`, `padding`, `border`, `margin`) si applicano a questo box, non "al testo" o "all'immagine" in astratto: è per questo che aggiungere un `border: 1px solid black;` a qualunque elemento è un modo rapido per visualizzarne i confini durante il debug.

> [!quote] Definizione — Box model
> Il **box model** descrive come è composto lo spazio occupato da un elemento, a partire dal contenuto verso l'esterno: **content** (il contenuto vero e proprio), **padding** (spazio interno tra contenuto e bordo), **border** (il bordo) e **margin** (spazio esterno, tra il bordo dell'elemento e gli elementi vicini).

```text
┌─────────────────────────────┐
│           margin             │
│  ┌─────────────────────────┐ │
│  │         border          │ │
│  │  ┌─────────────────────┐│ │
│  │  │      padding        ││ │
│  │  │  ┌────────────────┐ ││ │
│  │  │  │    content     │ ││ │
│  │  │  └────────────────┘ ││ │
│  │  └─────────────────────┘│ │
│  └─────────────────────────┘ │
└─────────────────────────────┘
```

- **content**: l'area dove sta il testo o gli altri elementi figli; le sue dimensioni si controllano con `width` e `height`.
- **padding**: spazio **interno**, tra il contenuto e il bordo. Non ha colore proprio: mostra lo sfondo dell'elemento (`background`).
- **border**: il bordo vero e proprio, con `border-style` (`none | solid | dashed | dotted | double | groove | ridge | inset | outset`), `border-width` (`thin | medium | thick` o una lunghezza) e `border-color`. La forma abbreviata `border: 2px solid black;` imposta le tre proprietà insieme; ognuna ha anche una variante per singolo lato (`border-top`, `border-right`, `border-bottom`, `border-left`).
- **margin**: spazio **esterno**, tra il bordo dell'elemento e gli elementi (o il contenitore) vicini. È **trasparente**: non mostra mai lo sfondo dell'elemento.

### Padding e margin: proprietà per lato e forma abbreviata
Le slide (PW07 p.6-7) descrivono `padding-top`, `padding-right`, `padding-bottom`, `padding-left` e `margin-top`, `margin-right`, `margin-bottom`, `margin-left`. I valori ammessi sono una lunghezza, una percentuale, `inherit` (per `margin` anche `auto`). Nessuna delle due proprietà è **ereditata**. Il valore iniziale indicato dalle slide è `0` per il `padding` e `auto` per il `margin` *(extra, non da slide: nello standard CSS il valore iniziale di `margin` è `0`, mentre `auto` serve per centrare un blocco con larghezza definita)*.

```css
blockquote {
  padding-top: 1em;
  padding-right: 3em;
  padding-bottom: 1em;
  padding-left: 3em;
}

blockquote {
  padding: 1em 3em 1em 3em;   /* equivalente: top right bottom left */
}

p {
  margin-top: 2em;
  margin-right: 250px;
  margin-bottom: 1em;
  margin-left: 4em;
}
```

La forma abbreviata a **quattro valori** segue l'ordine **top, right, bottom, left** (senso orario a partire dall'alto). *(Extra, non da slide)* Le forme con meno valori sono: tre valori `top left-right bottom`, due valori `top-bottom left-right` (come `padding: 1em 3em`) e un solo valore per tutti e quattro i lati.

### Border: larghezza, colore, stile a più valori
Dalle slide (PW07 p.9-12): `border-width` accetta una lunghezza oppure `thin`, `medium`, `thick` (valore iniziale `medium`); `border-style` ha come valore iniziale `none`; `border-color` accetta un colore o `transparent` e, se non è indicato, usa il valore della proprietà `color` dell'elemento. Anche per i bordi si possono dare più valori e le proprietà abbreviate:

```css
div#help {
  border-width: thin medium thick 12px;  /* top right bottom left */
  border-style: solid;
  width: 300px;
  height: 100px;
}

div#special {
  border-color: maroon aqua;             /* top/bottom maroon, lati aqua */
  border-style: solid;
  border-width: 6px;
}

h1 { border-left: red .5em solid; }      /* solo il bordo sinistro */
h2 { border-bottom: 1px solid; }         /* solo il bordo inferiore */
p.example { border: 2px dotted #663; }   /* tutti e quattro i lati */
```

Con due valori in `border-color` (e allo stesso modo in `border-width`) il primo vale per top e bottom, il secondo per i lati destro e sinistro *(extra, non da slide: regola generale dei valori a più lati, come per `padding`)*.

### Esempio complessivo
```css
.card {
  padding: 1em 3em;          /* top/bottom 1em, right/left 3em */
  border: 2px solid #355c9a;
  margin: 2em auto;          /* top/bottom 2em, right/left auto (centra orizzontalmente) */
}
```

L'esempio `Materiale Didattico/Esempi/04-1 - box/box-base.html` mostra lo stesso scenario con valori diversi: un `.card` con `width: 360px`, `border: 2px solid #355c9a`, `padding: 1.25rem` e `margin: 2rem auto`; il `body` ha `padding: 2rem`. I confini sono visibili grazie a un bordo di debug (`* { border: 1px solid #000; }`) applicato a tutti gli elementi della pagina. Nel file una regola separata applica `box-sizing: border-box; margin: 0; padding: 0;` a tutti gli elementi: quindi i `360px` del `.card` comprendono già padding e bordo (vedi [[#box-sizing: content-box vs border-box]]), mentre il calcolo della sezione seguente è quello del `content-box` di default.
### Calcolo della larghezza totale (content-box)
Per default (valore iniziale di `box-sizing`, vedi sotto), quando si imposta `width` su un elemento si sta fissando **solo la larghezza del content**. Padding e border si **aggiungono** a quella larghezza, allargando il box visibile sulla pagina.

> [!example] Calcolo passo-passo
> ```css
> .box {
>   width: 500px;
>   padding: 20px;
>   border: 2px solid gray;
>   margin: 20px;
> }
> ```
> Larghezza **visibile** del box (content + padding + border, esclusi i margini che sono spazio esterno):
> `20px (padding sx) + 2px (border sx) + 500px (content) + 2px (border dx) + 20px (padding dx) = 544px`
>
> Se si contano anche i margini (lo spazio totale "occupato" nel flusso della pagina):
> `20px (margin sx) + 2px + 20px + 500px + 20px + 2px + 20px (margin dx) = 584px`

Lo stesso calcolo, posto come domanda d'esame:

> [!question] Domanda tipica d'esame
> Un box ha `width: 200px`, `padding: 20px` (su tutti i lati) e `border: 5px solid black`, con `box-sizing: content-box` (il default). Quanto è larga la sua area visibile (senza contare eventuali margini)?
> **Risposta**: **250px**. Con `content-box`, `width` fissa solo il contenuto: si somma il padding su entrambi i lati (`20 + 20 = 40`) e il border su entrambi i lati (`5 + 5 = 10`). `200 + 40 + 10 = 250px`. È un errore comune rispondere `200px`, dimenticando che padding e border si aggiungono anziché "starci dentro".
## box-sizing: content-box vs border-box
La proprietà `box-sizing` decide **cosa** misura esattamente `width`/`height`.

```css
.box {
  box-sizing: content-box; /* valore di default */
}
```

- **`content-box`** (default): `width` e `height` misurano **solo il content**. Padding e border si aggiungono, allargando il box (vedi il calcolo sopra: `200 + 40 + 10 = 250px`).
- **`border-box`**: `width` e `height` misurano **content + padding + border insieme**. Impostare `width: 200px` con `box-sizing: border-box` e lo stesso padding/border dell'esempio precedente dà un box largo **esattamente 200px** in totale: il browser riduce automaticamente lo spazio disponibile per il content per far posto a padding e border.

```css
.box-content { box-sizing: content-box; width: 200px; padding: 20px; border: 5px solid; }
/* larghezza visibile totale: 250px */

.box-border { box-sizing: border-box; width: 200px; padding: 20px; border: 5px solid; }
/* larghezza visibile totale: 200px (il content si restringe internamente) */
```

> [!warning] Perché quasi tutti i progetti usano border-box
> Con `content-box` (il default), se si imposta `width: 25%` su quattro box affiancati e poi si aggiunge un `border`, la larghezza reale supera il 25% e i quattro box **non stanno più su una riga**. Con `box-sizing: border-box` il `width: 25%` resta sempre il 25% totale, bordo compreso: è per questo che praticamente ogni foglio di reset (vedi [[#Reset CSS]]) imposta `* { box-sizing: border-box; }` all'inizio del progetto.
## Margin collapsing e margini negativi
### Margini sugli elementi inline
Gli elementi **inline** (come `<span>`, `<a>`, `<em>`) **ignorano** il margine `top` e `bottom`: impostarli non ha alcun effetto sulla posizione degli elementi vicini (i margini orizzontali, `margin-left`/`margin-right`, funzionano normalmente). Fanno eccezione gli elementi inline **replaced**, come `<img>`, che rispettano il margine su tutti e quattro i lati. La differenza tra elementi inline e block-level (e come cambiarla con `display`) è trattata in dettaglio in [[04 - CSS - layout, Flexbox, Grid e responsive]].
### Margini che collassano
Quando due elementi **block-level** si susseguono verticalmente, il margine `bottom` del primo e il margine `top` del secondo **non si sommano**: **collassano in un solo margine**, pari al **massimo** dei due.

> [!quote] Definizione — Margin collapsing
> Il **margin collapsing** ("collasso dei margini") è il comportamento per cui due margini verticali **adiacenti** (bottom di un elemento e top del successivo) si fondono in un unico margine, di dimensione pari al più grande dei due, invece di sommarsi.

```css
.primo  { margin-bottom: 2em; }
.secondo { margin-top: 1em; }
```

Lo spazio reale tra `.primo` e `.secondo` non sarà `2em + 1em = 3em`, ma **`2em`** (il massimo tra i due). Il margin collapsing **non avviene** se uno dei due elementi è posizionato con `float` o `position: absolute` (concetti di layout, vedi [[04 - CSS - layout, Flexbox, Grid e responsive]]).

> [!warning] Errore tipico: sommare i margini a mano
> È un errore comune calcolare lo spazio tra due elementi sommando i loro margini verticali. Bisogna invece prendere il **massimo** dei due, non la somma — e solo per i margini **verticali** tra elementi **block-level** nel normale flusso del documento.

Un esercizio tipico sul collasso dei margini:

> [!question] Domanda tipica d'esame
> Due paragrafi block-level consecutivi hanno `margin-bottom: 30px` il primo e `margin-top: 20px` il secondo. Quanto spazio verticale c'è tra i due?
> **Risposta**: **30px**, non 50px. I margini verticali adiacenti tra elementi block-level collassano in uno solo, pari al **massimo** dei due (`max(30, 20) = 30`). Il collasso non avviene se uno dei due elementi è `float` o `absolute`; e gli elementi inline ignorano del tutto `margin-top` e `margin-bottom`, tranne quelli replaced come `<img>`.
### Margini negativi
Il valore di `margin` può essere **negativo**: sposta l'elemento "indietro" rispetto a dove si troverebbe normalmente, sovrapponendolo potenzialmente agli elementi vicini. Esempio dalle slide (PW07 p.25): con `p.top { margin-bottom: 4em; }` l'elemento seguente è **allontanato** di 4em; con `p.top { margin-bottom: -4em; }` l'elemento seguente **torna indietro** di 4em e si sovrappone al primo.

```css
p.top { margin-bottom: 4em; }   /* il paragrafo successivo è spinto via di 4em */
p.top { margin-bottom: -4em; }  /* il paragrafo successivo si sovrappone al primo */
```

Un altro esempio *(extra, non da slide)* con `margin-top` negativo:

```css
.sovrapposto {
  margin-top: -2em; /* l'elemento si sposta di 2em verso l'alto rispetto al flusso normale */
}
```
### Altre proprietà del box: overflow
Quando il contenuto di un elemento è più grande del suo box, la proprietà `overflow` decide cosa succede al contenuto in eccesso:

```css
.box {
  overflow: hidden; /* visible (default) | hidden | scroll | auto */
}
```

- `visible` (default): il contenuto trabocca fuori dal box, senza essere tagliato.
- `hidden`: il contenuto in eccesso viene **tagliato** e nascosto.
- `scroll`: vengono sempre mostrate le barre di scorrimento, anche se il contenuto ci sta.
- `auto`: le barre di scorrimento compaiono **solo se necessarie**.

Le slide (PW07 p.27) indicano che `overflow` si applica agli elementi **block-level** e agli elementi inline **replaced**.
## Background
Lo sfondo di un elemento si controlla con le proprietà `background-*` (o con la forma abbreviata `background`).

```css
.box {
  background-color: white;
  background-image: url("star.gif");
  background-repeat: no-repeat;      /* repeat (default) | repeat-x | repeat-y | no-repeat */
  background-position: right top;    /* left/center/right top/center/bottom, oppure lunghezze/percentuali */
  background-attachment: fixed;      /* scroll (default) | fixed | local */
}

/* equivalente in forma abbreviata */
.box {
  background: white url("star.gif") no-repeat right top fixed;
}
```

- `background-color` accetta anche `transparent` (default) ed è indipendente dal colore del testo; con `opacity` (proprietà separata, applicata all'intero elemento) si può rendere un blocco parzialmente trasparente, ma **attenzione alla leggibilità** del testo sopra uno sfondo poco contrastato.
- `background-image` accetta `url(...)`, `none` (default) o `inherit`; non è ereditata. Esempi delle slide (PW07 p.33): `body { background-image: url(star.gif); }` e `blockquote { background-image: url(dot.gif); padding: 2em; border: 4px dashed; }`.
- `background-repeat` controlla il **tiling**: se l'immagine è più piccola del box, per default si ripete in entrambe le direzioni. I valori sono `repeat` (default), `repeat-x`, `repeat-y`, `no-repeat` (PW07 p.34).
- `background-position` posiziona l'immagine nel box; il valore iniziale è `0% 0%` (come `left top`) e i valori sono lunghezze, percentuali o `left`, `center`, `right`, `top`, `bottom` (PW07 p.35). Esempi delle slide: `background-position: 200px 50px;` e `background-position: 15% 100%;`. `background-attachment: fixed` ancora l'immagine alla **viewport** invece che al contenuto della pagina, producendo il classico effetto "parallasse" quando si scorre *(extra, non da slide: l'effetto «parallasse»; le slide elencano solo `scroll`, `fixed`, `local`)*.
- `opacity` (novità di CSS3, PW07 p.32) accetta un numero da `0` a `1` (default `1`), si applica a tutti gli elementi e **non è ereditata**. Esempi: `h1 { color: green; background: white; opacity: .25; }`, con `.5` e `1`. *(Extra, non da slide)* Agisce sull'**intero elemento**, testo compreso, a differenza di `rgba()` che rende trasparente solo il colore.

> [!example] Esempi del docente
> `Materiale Didattico/Esempi/04-2 - background/ogre-bg.html` usa `background-image`, `background-repeat: no-repeat`, `background-position: center top`, `background-size` e `background-attachment: fixed`. Sul `body` una seconda regola imposta `background-image: none`, mentre i `<p>` hanno un bordo e la stessa immagine con `background-size: 40%` e `background-attachment: fixed`; `p.first` cambia la posizione in `left top`. Il risultato è un'illustrazione ancorata alla viewport mentre il testo scorre. `landing.html` usa `background-image`, `background-position: center center` e `background-size: cover`, con `background-attachment: fixed` in una delle sezioni; le cartelle `es-bg-fisso-1/` e `es-bg-fisso-2/` usano `background-repeat: no-repeat`, `background-size: cover` e `background-position: center center` (con `background-attachment: fixed`) per far riempire lo sfondo al suo contenitore indipendentemente dallo scroll.
## Reset CSS
Ogni browser applica un proprio **user-agent stylesheet** di default: margini su `body`, padding sulle liste, dimensioni diverse per i titoli. Questo rende gli stili leggermente diversi da browser a browser, proprio il problema che il CSS dovrebbe risolvere (vedi [[#Cos'è il CSS e perché separare contenuto e stile]]). Un **reset.css** è un foglio di stile che si collega **per primo**, prima di ogni altra regola, e azzera questi default per partire da una base uniforme.

`Materiale Didattico/Esempi/reset.css` è un reset tipico: usa il selettore universale per azzerare margini e padding e per impostare `box-sizing: border-box` ovunque, poi normalizza testo e titoli, liste, link, media, form, tabelle, citazioni ed elementi semantici HTML5. Il file è riportato per intero:

```css
/* -----------------------
   RESET GENERALE
----------------------- */

*,
*::before,
*::after {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

/* -----------------------
   HTML / BODY
----------------------- */

html {
  font-size: 16px;
}

body {
  line-height: 1;
  font-family: sans-serif;
  -webkit-font-smoothing: antialiased;
}

/* -----------------------
   HEADINGS E TESTO
----------------------- */

h1, h2, h3, h4, h5, h6 {
  font-size: inherit;
  font-weight: normal;
}

p {
  margin: 0;
}

/* -----------------------
   LISTE
----------------------- */

ul, ol {
  list-style: none;
}

/* -----------------------
   LINK
----------------------- */

a {
  text-decoration: none;
  color: inherit;
}

/* -----------------------
   MEDIA
----------------------- */

img,
picture,
video,
canvas,
svg {
  display: block;
  max-width: 100%;
}

/* -----------------------
   FORM
----------------------- */

input,
button,
textarea,
select {
  font: inherit;
  border: none;
  background: none;
}

/* -----------------------
   TABELLE
----------------------- */

table {
  border-collapse: collapse;
  border-spacing: 0;
}

/* -----------------------
   CITAZIONI
----------------------- */

blockquote,
q {
  quotes: none;
}

blockquote::before,
blockquote::after,
q::before,
q::after {
  content: "";
}

/* -----------------------
   ELEMENTI SEMANTICI HTML5
----------------------- */

header,
nav,
main,
section,
article,
aside,
footer,
figure,
figcaption,
details,
summary {
  display: block;
}
```

In sintesi: `html` fissa `font-size: 16px`; `body` imposta `line-height: 1`, `font-family: sans-serif` e `-webkit-font-smoothing: antialiased`; i titoli perdono dimensione e peso propri; le liste perdono i marcatori; i link perdono sottolineatura e colore; immagini e media diventano `display: block` con `max-width: 100%`; i campi dei form ereditano il font e perdono bordo e sfondo; le tabelle usano `border-collapse: collapse`; le citazioni perdono le virgolette; gli elementi semantici HTML5 sono `display: block`.

> [!info] Perché un reset conviene
> Senza reset, uno stesso layout può avere spaziature leggermente diverse tra Chrome, Firefox e Safari, perché ognuno parte da margini/padding di default differenti. Il reset elimina questa variabile: da quel punto in poi, ogni spazio visibile nella pagina è stato dichiarato esplicitamente nel proprio CSS, non ereditato per caso dal browser.
## Riferimenti
- `Materiale Didattico/Slide/PW05-CSS-1.pdf` — cos'è il CSS, i tre modi di inclusione, sintassi della regola, selettori (tipo, classe, id, universale, combinatori, attributo, pseudo-classi, pseudo-elementi, raggruppamento), cascata, ereditarietà, specificità (con gli esempi numerici dello standard CSS § 6.4.3), `!important`.
- `Materiale Didattico/Slide/PW06-CSS-2.pdf` — font (`font-family`, font stack, web font), unità di misura (`px`, `%`, `em`, `rem`, `vw`/`vh`/`vmin`/`vmax`/`ch`), colori (parole chiave, esadecimale, `rgb()`/`rgba()`), proprietà del testo (`text-align`, `text-decoration`, `text-transform`, `text-indent`, `text-shadow`, `letter-spacing`, `word-spacing`).
- `Materiale Didattico/Slide/PW07-CSS-3.pdf`, pagine 1-27 e 29-39 — box model (content, padding, border, margin), `box-sizing` (content-box vs border-box), margin collapsing, margini negativi, `overflow`, background e proprietà `background-*`; pagine 47-51 — ancore, `target`, `mailto:` e `tel:` (trattati in [[02 - HTML semantico e form#Ancore: link a punti specifici di una pagina]]); pagine 53-55 — pseudo-classi dei link e loro ordine. Le pagine su `display` e liste non sono trattate qui: il layout è oggetto di [[04 - CSS - layout, Flexbox, Grid e responsive]].
- `Materiale Didattico/Esempi/04-1 - box/box-base.html` — esempio di box model (width, border, padding, margin) con bordo di debug.
- `Materiale Didattico/Esempi/04-2 - background/ogre-bg.html`, `es-bg-fisso-1/`, `es-bg-fisso-2/` — esempi di background-image, background-attachment: fixed e background-size: cover.
- `Materiale Didattico/Esempi/reset.css` — reset CSS del docente, riportato per intero nella sezione [[#Reset CSS]].
