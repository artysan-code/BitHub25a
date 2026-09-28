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

> [!info] Elemento, classe, id — quando usarli
> - **Elemento** → colpisce tutti i tag di un certo tipo (più generico).
> - **Classe** → colpisce un gruppo di elementi che condividono un ruolo.
> - **Id** → colpisce un solo elemento specifico e unico nella pagina (più specifico).
>
> La scelta dipende da quanto deve essere ampio o mirato l'effetto della regola.
### Selettore universale
Il selettore `*` seleziona **tutti gli elementi** della pagina, senza eccezioni. Si usa spesso nei reset CSS (vedi [[#Reset CSS]]) per azzerare margini e padding di default.

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

Le pseudo-classi più comuni legate ai link e all'interazione dell'utente:

```css
a:link    { color: blue; }    /* link non visitato */
a:visited { color: purple; }  /* link già visitato (cronologia del browser) */
a:focus   { outline: 2px solid orange; } /* elemento selezionato (es. da tastiera) */
a:hover   { color: magenta; } /* il mouse è sopra il link */
a:active  { color: red; }     /* nel momento esatto del click */
```

Altre pseudo-classi utili riguardano la **posizione** dell'elemento tra i fratelli: `:first-child`, `:last-child`, `:only-child`, `:first-of-type`, `:last-of-type`, `:only-of-type`, `:nth-child()`, `:nth-last-child()`, `:nth-of-type()`, `:nth-last-of-type()`, oltre a `:root` (la radice del documento, cioè `<html>`) e `:empty` (elemento senza contenuto).

> [!warning] Ordine delle pseudo-classi sui link
> `:hover` deve essere dichiarato **dopo** `:link` e `:visited`, e `:active` **dopo** `:hover` *(extra, non da slide: il mnemonico comune è "LVHA" — Link, Visited, Hover, Active)*. Se l'ordine è sbagliato, a parità di specificità vince la regola scritta dopo nel CSS (vedi [[#Cascata]]) e lo stato hover o active può non funzionare mai perché sovrascritto da `:link`/`:visited`.
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
1. **`!important`** (vedi [[#!important]]) batte tutto il resto;
2. maggiore **specificità** del selettore (vedi [[#Specificità]]);
3. a parità di specificità, vince la regola scritta **dopo** nel codice (ultimo dichiarato, ultimo applicato).

> [!example] Chi vince?
> ```css
> p { color: green; }
> p { color: blue; }
> ```
> Le due regole hanno **la stessa specificità** (stesso selettore `p`). Vince la seconda: il testo dei paragrafi sarà **blu**, perché scritta dopo.
## Ereditarietà
Alcune proprietà CSS, se applicate a un elemento, si **propagano automaticamente** ai suoi discendenti anche se non hanno una regola propria: è l'**ereditarietà**. Ad esempio, se si imposta `color` su un `<p>`, uno `<span>` contenuto al suo interno erediterà lo stesso colore, a meno di regole più specifiche.

```html
<p style="color: navy;">Testo con <span>una parte</span> in evidenza.</p>
```

Non tutte le proprietà sono ereditate: quelle legate al **testo** lo sono quasi sempre (`color`, `font-family`, `font-size`, `font-weight`, `font-style`, `line-height`, `text-align`, `text-indent`, `text-transform`, `letter-spacing`, `word-spacing`, `visibility`, `list-style`, `cursor`...), mentre quelle legate al **box** dell'elemento (`margin`, `padding`, `border`, `width`, `height`, `background`...) **non** si ereditano: ogni elemento ha il proprio box indipendente (vedi [[#Box model]]).

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

Riprendiamo l'esempio di [[#Cascata]] (`<p id="intro" class="note">`, con `p`, `.note`, `#intro` che impostano `color` in modo diverso): con la specificità in mano si può ora rispondere senza ambiguità.

> [!question] Domanda tipica d'esame
> Dati `p { color: green }`, `.note { color: blue }`, `#intro { color: red }` applicati allo stesso `<p id="intro" class="note">`, di che colore sarà il testo?
> **Risposta**: rosso. Le specificità sono `p` → `0,0,0,1`, `.note` → `0,0,1,0`, `#intro` → `0,1,0,0`: `#intro` ha un id (`b=1`), che batte sia il selettore di classe (`c=1`) sia quello di elemento (`d=1`), perché si confronta prima la colonna `b`. L'ordine di scrittura nel file conta solo a **parità** di specificità.
### Classi multiple
Un elemento può avere più classi contemporaneamente (separate da spazio nell'attributo `class`); ogni classe nel selettore aumenta il conteggio della colonna `c`.

```html
<a class="btn btn-danger" href="#">Pericolo</a>
```
```css
.btn         { padding: 10px; }         /* specificità 0,0,1,0 */
.btn-danger  { background: red; }       /* specificità 0,0,1,0 */
.btn.btn-danger { font-weight: bold; }  /* specificità 0,0,2,0 — più specifico di entrambe */
```
## !important
La dichiarazione `!important`, scritta dopo il valore, fa sì che una regola **non venga mai sovrascritta** da un'altra regola con specificità maggiore (ma normale) — batte anche lo stile inline.

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
| `em` | relativa | il `font-size` **corrente** dell'elemento |
| `rem` | relativa | il `font-size` dell'elemento **root** (`<html>`) |
| `vw` | relativa | 1% della **larghezza** della viewport |
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
## Colori
Il colore si specifica più spesso con la proprietà `color` (testo) o `background-color` (sfondo). I formati disponibili sono:

```css
p { color: tomato; }                 /* parola chiave */
p { color: #ff6347; }                /* esadecimale: RR GG BB */
p { color: rgb(255, 99, 71); }       /* rosso, verde, blu: 0-255 ciascuno */
p { color: rgba(255, 99, 71, 0.5); } /* rgb + canale alfa (trasparenza, 0-1) */
```

I tre valori di `rgb()` sono le quantità di rosso, verde e blu, ciascuna un byte (da `0` a `255` oppure, in alternativa, una percentuale). `rgba()` aggiunge un quarto valore, il **canale alfa**, che controlla la trasparenza: `0` è completamente trasparente, `1` completamente opaco. `color` è una proprietà **ereditata** (vedi [[#Ereditarietà]]), quindi va sempre garantito un buon contrasto con lo sfondo.
## Font e testo
### font-family
La proprietà `font-family` specifica il font del testo. Si indica una **lista di font in ordine di preferenza** (un *font stack*): se il primo non è disponibile sul dispositivo dell'utente, il browser prova il successivo, fino all'ultimo, che dovrebbe essere una **famiglia generica** (`serif`, `sans-serif`, `monospace`) sempre disponibile.

```css
body { font-family: Arial, Helvetica, sans-serif; }
code { font-family: "Courier New", Courier, monospace; }
p    { font-family: Georgia, "Times New Roman", Times, serif; }
```

Questo è necessario perché **i font dipendono dal sistema operativo**: non tutti i font sono installati su tutti i dispositivi, quindi affidarsi a un solo nome rischia di non funzionare per una parte degli utenti. In alternativa ai font di sistema esistono i **web font**: caricati da un file nel progetto con la regola `@font-face`, oppure da un servizio esterno come Google Fonts (di solito collegato con `<link>`, come un normale foglio di stile esterno).
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

```css
.card {
  padding: 1em 3em;          /* top/bottom 1em, right/left 3em */
  border: 2px solid #355c9a;
  margin: 2em auto;          /* top/bottom 2em, right/left auto (centra orizzontalmente) */
}
```

L'esempio `Materiale Didattico/Esempi/04-1 - box/box-base.html` mostra questo esatto scenario: un `.card` con `width`, `border`, `padding` e `margin` visibili grazie a un bordo di debug (`* { border: 1px solid #000; }`) applicato a tutti gli elementi della pagina.
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

> [!warning] Trabocchetto: sommare i margini a mano
> È un errore comune calcolare lo spazio tra due elementi sommando i loro margini verticali. Bisogna invece prendere il **massimo** dei due, non la somma — e solo per i margini **verticali** tra elementi **block-level** nel normale flusso del documento.
### Margini negativi
Il valore di `margin` può essere **negativo**: sposta l'elemento "indietro" rispetto a dove si troverebbe normalmente, sovrapponendolo potenzialmente agli elementi vicini.

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
- `background-repeat` controlla il **tiling**: se l'immagine è più piccola del box, per default si ripete in entrambe le direzioni.
- `background-position` posiziona l'immagine nel box; `background-attachment: fixed` la ancora alla **viewport** invece che al contenuto della pagina, producendo il classico effetto "parallasse" quando si scorre.

> [!example] Esempi del docente
> `Materiale Didattico/Esempi/04-2 - background/ogre-bg.html` usa `background-image`, `background-repeat: no-repeat`, `background-position` e `background-attachment: fixed` insieme per ancorare un'illustrazione di sfondo mentre il testo scorre. Le cartelle `es-bg-fisso-1/` e `es-bg-fisso-2/` applicano la stessa tecnica (`background-attachment: fixed` più `background-size: cover`) a una landing page reale, con lo sfondo che riempie sempre il viewport indipendentemente dallo scroll.
## Reset CSS
Ogni browser applica un proprio **user-agent stylesheet** di default: margini su `body`, padding sulle liste, dimensioni diverse per i titoli. Questo rende gli stili leggermente diversi da browser a browser, proprio il problema che il CSS dovrebbe risolvere (vedi [[#Cos'è il CSS e perché separare contenuto e stile]]). Un **reset.css** è un foglio di stile che si collega **per primo**, prima di ogni altra regola, e azzera questi default per partire da una base uniforme.

`Materiale Didattico/Esempi/reset.css` è un reset tipico: usa il selettore universale per azzerare margini e padding e per impostare `box-sizing: border-box` ovunque, poi normalizza titoli, liste, link e form.

```css
*, *::before, *::after {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

h1, h2, h3, h4, h5, h6 {
  font-size: inherit;
  font-weight: normal;
}

ul, ol {
  list-style: none;
}

a {
  text-decoration: none;
  color: inherit;
}
```

> [!info] Perché un reset conviene
> Senza reset, uno stesso layout può avere spaziature leggermente diverse tra Chrome, Firefox e Safari, perché ognuno parte da margini/padding di default differenti. Il reset elimina questa variabile: da quel punto in poi, ogni spazio visibile nella pagina è stato dichiarato esplicitamente nel proprio CSS, non ereditato per caso dal browser.
## Riferimenti
- `Materiale Didattico/Slide/PW05-CSS-1.pdf` — cos'è il CSS, i tre modi di inclusione, sintassi della regola, selettori (tipo, classe, id, universale, combinatori, attributo, pseudo-classi, pseudo-elementi, raggruppamento), cascata, ereditarietà, specificità (con gli esempi numerici dello standard CSS § 6.4.3), `!important`.
- `Materiale Didattico/Slide/PW06-CSS-2.pdf` — font (`font-family`, font stack, web font), unità di misura (`px`, `%`, `em`, `rem`, `vw`/`vh`/`vmin`/`vmax`/`ch`), colori (parole chiave, esadecimale, `rgb()`/`rgba()`), proprietà del testo (`text-align`, `text-decoration`, `text-transform`, `text-indent`, `text-shadow`, `letter-spacing`, `word-spacing`).
- `Materiale Didattico/Slide/PW07-CSS-3.pdf`, pagine 1-27 e 29-39 — box model (content, padding, border, margin), `box-sizing` (content-box vs border-box), margin collapsing, margini negativi, `overflow`, background e proprietà `background-*`; pagine 53-55 — pseudo-classi dei link e ordine LVHA. Le pagine su `display` e liste non sono trattate qui: il layout è oggetto di [[04 - CSS - layout, Flexbox, Grid e responsive]].
- `Materiale Didattico/Esempi/04-1 - box/box-base.html` — esempio di box model (width, border, padding, margin) con bordo di debug.
- `Materiale Didattico/Esempi/04-2 - background/ogre-bg.html`, `es-bg-fisso-1/`, `es-bg-fisso-2/` — esempi di background-image, background-attachment: fixed e background-size: cover.
- `Materiale Didattico/Esempi/reset.css` — reset CSS completo usato come riferimento nella sezione [[#Reset CSS]].
