---
tags:
  - programmazione-web
  - html
slide:
  - "PW01-Internet e HTML.pdf"
  - "PW03-HTML-2.pdf"
  - "PW07-CSS-3.pdf"
  - "PW11-CSS-HTML-7.pdf"
  - "PW47-Forms-2.pdf"
---
# HTML semantico e form
**HTML** (HyperText Markup Language) è il linguaggio che struttura i contenuti di una pagina web: definisce cosa sono le cose (un titolo, una lista, un'immagine, un form), non come devono apparire — quello è compito del **CSS** (vedi [[03 - CSS - selettori, specificità e box model]]). Questa nota copre la sintassi di base del markup, la struttura di un documento, i tag semantici introdotti con HTML5 e gli elementi per costruire form, cioè il modo standard con cui una pagina raccoglie dati dall'utente e li invia a un server.
## La struttura di un documento HTML
Un documento HTML è un file di testo che il browser interpreta e trasforma (*renderizza*) in una pagina visibile. La sua struttura minima è fissa:
```html
<!DOCTYPE html>
<html lang="it">
<head>
  <title>Titolo della pagina</title>
</head>
<body>
  <h1>Contenuto visibile</h1>
</body>
</html>
```
La dichiarazione **`<!DOCTYPE html>`** dice al browser quale tipo e versione di HTML usare per interpretare il documento; non è case sensitive (`<!doctype html>` è equivalente). Prima di HTML5 le dichiarazioni erano molto più lunghe (es. HTML 4.01, XHTML 1.0, con riferimento a una DTD); HTML5 l'ha ridotta a una sola riga.

> [!info] Evoluzione di HTML e CSS
> HTML: 1991 → HTML+ (1993) → HTML 2.0 (1995) → HTML 3.2 (1997) → HTML 4.01 (1999) → XHTML (2000) → **HTML5** (2012/2014).
> CSS: CSS1 (1996) → CSS2 (2004) → CSS2.1 (2011) → CSS3 (2014).

L'elemento **`<html>`** è la radice dell'albero e contiene tutto il resto; l'attributo `lang` dichiara la lingua del documento. Al suo interno ci sono esattamente due sezioni:
- **`<head>`**: contiene i **metadati** della pagina (titolo, descrizione, charset, autore...). Il suo contenuto non viene mostrato nella pagina. L'unico elemento obbligatorio al suo interno è **`<title>`**: definisce il testo mostrato nella scheda del browser, usato per i preferiti e dai motori di ricerca; senza `<title>` il documento non è HTML valido, e ce ne può essere uno solo.
- **`<body>`**: contiene la parte **visibile** della pagina, normalmente organizzata in sezioni (vedi [[#Tag semantici di HTML5]]).

Un esempio tipico di `<head>` include anche `<meta charset="utf-8">`, che dichiara la codifica dei caratteri del documento. *(extra, non da slide)* Nella pratica moderna si aggiunge quasi sempre anche `<meta name="viewport" content="width=device-width, initial-scale=1">`, che dice al browser mobile di non simulare uno schermo desktop, fondamentale per il responsive design (vedi [[04 - CSS - layout, Flexbox, Grid e responsive]]).

> [!question] Domanda tipica d'esame
> Cosa contiene l'elemento `<head>` di un documento HTML?
> Risposta: metadati sulla pagina (titolo, descrizione, charset...), non contenuto visibile. Il contenuto visibile sta in `<body>`.

> [!info] Validare un documento HTML
> Il servizio [validator.w3.org](https://validator.w3.org) controlla la sintassi di un documento HTML e segnala gli errori rispetto allo standard: il browser, per tolleranza, "maschera" molti errori e mostra comunque la pagina, quindi un documento che sembra funzionare non è detto che sia HTML valido.
## Elementi, tag e attributi
Un documento HTML è pieno di **tag**: testo racchiuso fra parentesi angolari (es. `<body>`, `<p>`). I tag non sono mostrati dal browser: sono istruzioni di struttura, definite dallo standard. La maggior parte dei tag va **a coppie** (tag di apertura e tag di chiusura, es. `<body>...</body>`); l'insieme di tag di apertura, contenuto e tag di chiusura forma un **elemento**.

> [!quote] Definizione — Elemento vuoto
> Alcuni elementi non hanno contenuto né tag di chiusura, e sono quindi definiti con un solo tag (es. `<hr>`, `<br>`, `<img ...>`). Possono comunque avere attributi.

Gli elementi possono essere **annidati** (un elemento dentro un altro), ma l'annidamento deve essere corretto: gli elementi si chiudono nell'ordine inverso rispetto a come sono stati aperti.
```html
<!-- corretto -->
<p>This <em>is <strong>correct</strong>.</em></p>
<!-- scorretto: strong si chiude fuori da em -->
<p>This is <em>very <strong>wrong</em>!</strong></p>
```
### Attributi
Alcuni elementi hanno **attributi**: coppie chiave-valore definite nel tag di apertura, specifiche per ogni tag, che forniscono informazioni aggiuntive sull'elemento. Esempio: `<img src="foods.gif" alt="food illustration">` ha attributo `src` con valore `foods.gif` e attributo `alt` con valore `food illustration`.

> [!info] Regole pratiche sugli attributi
> - Usare **sempre le virgolette** attorno al valore (`href="https://..."`): sono obbligatorie se il valore contiene spazi, ed è buona pratica usarle sempre.
> - Se il valore contiene virgolette doppie, usare quelle singole per l'attributo (`title='John "ShotGun" Nelson'`) e viceversa.
> - Il carattere può essere invertito: `title="John 'ShotGun' Nelson"`.

Un documento HTML, con i suoi elementi annidati, forma un **albero degli elementi** (usato dal browser per costruire il DOM, vedi [[06 - JavaScript e DOM]]):
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Sample page</title>
</head>
<body>
  <h1>Sample page</h1>
  <p>This is a <a href="demo.html">simple</a> sample.</p>
  <!-- this is a comment -->
</body>
</html>
```
Ogni nodo dell'albero è un elemento, un attributo, del testo (`#text`) oppure un commento.

I **commenti** `<!-- ... -->` sono testo non mostrato all'utente e non interpretato dal browser, utile per lasciare note nel codice. Alcuni **caratteri** vanno sostituiti con una sequenza di escape (*entità HTML*) che inizia con `&` e finisce con `;`, perché non ASCII o perché hanno un significato speciale nei tag (`<`, `>`, `&`, `"`):

| Carattere | Sequenza |
|---|---|
| `<` `>` | `&lt;` `&gt;` |
| `&` `"` | `&amp;` `&quot;` |
| é è ñ | `&eacute;` `&egrave;` `&ntilde;` |
| © ™ | `&copy;` `&trade;` |

> [!warning] Spazi e a-capo non contano
> Il browser collassa qualunque sequenza di spazi o a-capo in un unico spazio: non si può controllare la spaziatura aggiungendo spazi o righe vuote nel sorgente HTML. Per un a-capo esplicito si usa `<br>` (non più di due consecutivi); per mantenere spaziatura e a-capo esatti si usa `<pre>` (vedi [[#Titoli, paragrafi e testo]]).
## Elementi block e inline
Ogni elemento HTML appartiene (di default) a una di due categorie che ne determinano il comportamento nel flusso della pagina:

| | Block element | Inline element |
|---|---|---|
| Comportamento | il browser inserisce un a-capo e spazio prima e dopo | rimane nel flusso del paragrafo, senza andare a capo |
| Esempi | `<h1>`...`<h6>`, `<p>`, `<div>`, `<ul>`, `<section>` | `<em>`, `<strong>`, `<a>`, `<span>`, `<img>` |

Questa distinzione è alla base della differenza fra `<div>` (divisione a blocco, senza significato semantico) e `<span>` (divisione inline, senza significato semantico), i due contenitori "generici" usati prima di HTML5 per raggruppare contenuto quando nessun tag semantico è appropriato.
## Titoli, paragrafi e testo
### Heading, h1-h6
HTML definisce sei livelli di intestazione, **`<h1>`** (il più importante) fino a **`<h6>`**. Creano l'indice della pagina (*outline*, come in un documento Word) e sono usati dai motori di ricerca per capire l'importanza dei contenuti. Buona pratica: mantenere un **ordine logico**, senza saltare livelli.

> [!warning] Trabocchetto — h7 non esiste
> HTML definisce **solo sei livelli** di heading: `<h1>` … `<h6>`. `<h7>` **non è un tag valido**. È un errore classico da domanda a risposta multipla: se vedete `<h7>` fra le opzioni, è quella sbagliata.

> [!info] head vs header vs h1...h6 — non confonderli
> - **`<head>`**: sezione di metadati, dentro `<html>`, non mostrata dal browser.
> - **`<header>`**: elemento strutturale (semantico) che identifica un segmento introduttivo di pagina o di sezione, dentro `<body>` (vedi [[#Tag semantici di HTML5]]).
> - **`<h1>`...`<h6>`**: identificano i titoli testuali veri e propri, dentro il contenuto.
### Paragrafi e altri elementi di testo
**`<p>`** identifica un paragrafo; può contenere testo, immagini ed elementi inline. Il tag di chiusura è tecnicamente opzionale (il browser lo chiude da solo), ma in questo corso **non chiuderlo è considerato un errore**: chiudete sempre i paragrafi.

`<pre>` mostra **testo preformattato**: spazi e a-capo del sorgente vengono conservati esattamente, con font monospace — utile per codice o testo con formattazione significativa (l'opposto della regola generale che collassa gli spazi). `<blockquote>` racchiude una **citazione** più lunga, mostrata tipicamente rientrata. `<hr>` rappresenta un'interruzione tematica a livello di paragrafo (non va usato solo per disegnare una riga, ma per il suo significato semantico di separazione fra argomenti).

Fra gli elementi di testo inline più usati:

| Tag | Significato |
|---|---|
| `<em>` | testo enfatizzato, normalmente in *corsivo* |
| `<strong>` | testo fortemente enfatizzato, normalmente in **grassetto** |
| `<code>` | campione di codice, mostrato in monospace (non preformattato) |
| `<q>` | citazione breve inline (alcuni browser aggiungono le virgolette automaticamente) |
| `<abbr>` | abbreviazione |
| `<mark>` | testo evidenziato, contestualmente rilevante |
| `<small>` | testo in corpo minore (es. copyright) |
| `<sub>` / `<sup>` | pedice / apice |

```html
<p>HTML is <em>really</em>, <strong>REALLY</strong> fun!</p>
```
## Liste
HTML definisce tre tipi di lista, tutte mostrate di default come **block element**:
- **Non ordinate** (`<ul>`): l'ordine degli elementi non è rilevante; ogni voce è un `<li>`, con un pallino aggiunto automaticamente (spesso rimosso via CSS per costruire menu, vedi [[04 - CSS - layout, Flexbox, Grid e responsive]]).
- **Ordinate** (`<ol>`): l'ordine è intenzionale; il browser numera automaticamente le voci `<li>`; si può cambiare tipo di numerazione o punto di partenza con `<ol start="50">`.
- **Descrittive** (`<dl>`): coppie termine-descrizione. `<dl>` può contenere solo `<dt>` (termine) e `<dd>` (descrizione); dentro `<dt>` non possono esserci elementi di raggruppamento (`<h1>`, `<p>`...), mentre dentro `<dd>` può esserci qualunque cosa.

```html
<ul>
  <li><a href="#">Home</a></li>
  <li><a href="#">Chi siamo</a></li>
</ul>
<dl>
  <dt>HTML</dt>
  <dd>Linguaggio di markup per la struttura del contenuto.</dd>
</dl>
```
Le liste possono essere **annidate**: all'interno di un `<li>` si può inserire un'altra lista completa. Ad ogni livello di annidamento il browser cambia automaticamente lo stile della lista non ordinata (es. pallino pieno, poi vuoto, poi quadrato).
## Link e percorsi
L'elemento **`<a href="...">...</a>`** (*ancora*) crea un collegamento ipertestuale: il contenuto diventa cliccabile e il browser naviga verso la risorsa indicata dall'attributo **`href`**, che va sempre scritto fra virgolette.
### URL assolute e relative
- **URL assolute**: iniziano con il protocollo (`http://`, `https://`), es. `href="https://www.esempio.it/pagina.html"`. Sono necessarie per **link esterni**, verso un server diverso da quello della pagina corrente (vedi [[01 - Internet, Web e HTTP#URI e URL: anatomia di un indirizzo]] per la struttura di una URL: protocollo, host, path).
- **URL relative**: relative al path del documento corrente, es. `href="recipes/index.html"` o `href="spoon.gif"`. Si usano per **link interni** allo stesso sito/server: si può omettere protocollo e nome del server, indicando solo il path.

> [!warning] "Stesso sito" non basta a evitare l'URL assoluta
> Anche due sottodomini dello stesso ente possono essere server diversi (es. `www.uniroma2.it` e `web.uniroma2.it`): in quel caso serve comunque una URL assoluta, perché la risorsa non è raggiungibile con un path relativo.
### Mapping URL → filesystem
Il server web cerca i file localmente in base al path della URL, a partire dalla **document root** (cartella radice del server, es. `/var/www/html`): la URL `http://esempio.it/img/foto.jpg` corrisponde al file `/var/www/html/img/foto.jpg` sul server. Se la URL non specifica un file ma solo una directory (es. `www.esempio.it/`), il server cerca il **file di default**, tipicamente `index.html` (può variare: `index.htm`, `default.html`...). I percorsi seguono la convenzione Unix, con cartelle separate da `/`; un path relativo alla root del server (quello che comparirebbe nella URL assoluta dopo il nome del server) è detto **path assoluto**, distinto dal path relativo alla pagina corrente.
### Ancore: link a punti specifici di una pagina
Ogni elemento con un attributo **`id`** può fare da **ancora**: un link che punta a `#` seguito dal nome dell'`id` porta direttamente a quel punto della pagina, come nell'indice alfabetico di un glossario.
```html
<h1 id="startH">H</h1>
<!-- altrove nella stessa pagina -->
<p>... F | G | <a href="#startH">H</a> | I | J ...</p>
```
Per puntare a un punto specifico di **un'altra pagina** si aggiunge `#id` in fondo alla URL, relativa o assoluta: `<a href="glossary.html#startH">` oppure `<a href="http://www.example.com/glossary.html#startH">`. Se l'`id` non esiste nella pagina di destinazione, il link funziona comunque come un link normale e apre la pagina dall'inizio.
### Attributo target e altri tipi di link
L'attributo **`target`** specifica in quale finestra aprire il link: `target="_blank"` lo apre in una **nuova finestra** (o scheda).
```html
<a href="http://www.oreilly.com" target="_blank">O'Reilly</a>
```
Si può anche dare un nome a una finestra (`target="display"`) e riusarla per più link, ma spesso l'effetto è sgradevole: sembra che i link non funzionino, perché aprono il contenuto in una finestra già aperta altrove. Per controllare meglio le nuove finestre (es. i pop-up) si usa JavaScript.
Oltre alle pagine web, `href` può indicare altri schemi di URL:
- **`mailto:`** apre il programma di posta con un messaggio già indirizzato (il client di posta deve essere configurato); si possono precompilare altri campi, come oggetto e corpo.
- **`tel:`** avvia una chiamata: su un cellulare parte la telefonata, su desktop si apre un'applicazione di chiamata (es. Skype).
```html
<a href="mailto:nome.cognome@uniroma2.it">Scrivimi</a>
<a href="tel:+390612345678">Chiamami</a>
```
## Immagini e figure
L'elemento **`<img>`** inserisce un'immagine; è un elemento vuoto con due attributi principali:
- **`src`**: la URL dell'immagine (assoluta o relativa).
- **`alt`**: testo alternativo, mostrato se l'immagine non può essere caricata e letto dalle tecnologie assistive — fondamentale per l'accessibilità (vedi [[#Accessibilità di base]]).
```html
<img src="foods.gif" alt="illustrazione di cibo">
```
Ogni immagine è un **file separato**: quando il browser incontra `<img>`, effettua una nuova richiesta HTTP per scaricarla e poi la posiziona nella pagina (lo stesso vale, più o meno, per video e audio). Su connessioni lente si può vedere l'immagine comparire in un secondo momento rispetto al testo.

Quando un'immagine ha bisogno di una didascalia, si usa **`<figure>`** insieme a **`<figcaption>`**:
```html
<figure>
  <img src="trulli.jpg" alt="Trulli, Puglia">
  <figcaption>Fig. 1 - Trulli, Puglia, Italia.</figcaption>
</figure>
```
## Tag semantici di HTML5
> [!quote] Definizione — Markup semantico
> Scegliere l'elemento HTML che fornisce la **miglior descrizione del contenuto**, indipendentemente da come verrà visualizzato di default. Lo scopo dell'HTML5 è aggiungere significato e struttura al contenuto, non istruzioni di presentazione (quello è compito del CSS).

Prima di HTML5 l'unico modo per raggruppare logicamente elementi erano `<div>` (a blocco) e `<span>` (inline), entrambi **privi di significato**. HTML5 introduce un insieme di tag pensati per le parti ricorrenti di una pagina, nati da uno studio di Google sui nomi di classe CSS più usati dagli sviluppatori:

```text
┌──────────────────────────────┐
│           <header>            │
├────────────────────┬─────────┤
│      <main>          │         │
│  ┌─────────────┐   │         │
│  │  <section>  │   │ <aside> │
│  │  <article>  │   │         │
│  │  <article>  │   │         │
│  └─────────────┘   │         │
│  ┌─────────────┐   │         │
│  │  <section>  │   │         │
│  │  <article>  │   │         │
│  └─────────────┘   │         │
├────────────────────┴─────────┤
│           <footer>            │
└──────────────────────────────┘
```
### header, nav e footer
**`<header>`** si usa per materiale introduttivo; ha due usi comuni: header di pagina (logo, titolo, menu) oppure header di una sezione/articolo (dove tipicamente contiene titolo, autore, data). **`<nav>`** identifica una sezione che permette la navigazione nel sito; tipicamente contiene liste di link, ma non tutte le liste di link vanno in un `<nav>` (solo quelle di navigazione principale). **`<footer>`** contiene le informazioni di chiusura di una sezione logica: autore, copyright, documenti correlati, link — sia a fondo pagina che a fine di un `<article>` o `<section>`.
```html
<header>
  <img src="/img/logo.png" alt="Logo del corso">
  <h1>Corso di Programmazione Web</h1>
  <nav>
    <ul>
      <li><a href="#chi-siamo">Chi siamo</a></li>
      <li><a href="#articoli">Articoli</a></li>
      <li><a href="#contatti">Contatti</a></li>
    </ul>
  </nav>
</header>
```
### main, section e article
**`<main>`** specifica il contenuto **principale** del documento, il contenuto che dovrebbe essere unico per quella pagina (esclude header, nav, sidebar, footer ripetuti su tutte le pagine). Ci può essere **un solo `<main>`** per documento, e non deve mai essere discendente di `<article>`, `<aside>`, `<footer>`, `<header>` o `<nav>`.

**`<section>`** raggruppa contenuti **tematicamente correlati**: può contenere un heading e tutti gli elementi che ha senso raggruppare insieme. Si usa sia per dividere le sezioni di una pagina, sia per dividere le sezioni interne di un articolo.

**`<article>`** rappresenta una porzione di pagina **autoconsistente**: contenuto che avrebbe senso anche se estratto e riusato in un altro contesto (es. *syndication*, un post di blog, un articolo di giornale).

> [!warning] Trabocchetto — section vs article vs div
> Sono i tre contenitori più confusi del corso:
> - **`<div>`**: nessun significato semantico. Si usa solo quando serve un contenitore per CSS/JavaScript e nessun tag semantico è appropriato.
> - **`<section>`**: raggruppa contenuto **tematicamente correlato** all'interno di un contesto più ampio (una pagina o un articolo); non ha senso "da solo" fuori da quel contesto.
> - **`<article>`**: contenuto **indipendente e autoconsistente**, comprensibile anche estratto dal resto della pagina (un post, una notizia, un commento).
> Domanda utile per scegliere: "questo blocco avrebbe senso pubblicato da solo altrove?" Se sì → `<article>`. "Questi elementi condividono solo un tema con quello che li circonda?" Se sì → `<section>`. Se non c'è alcun significato da esprimere → `<div>`.

`<section>` e `<article>` si combinano in due modi tipici: **sezioni di un articolo** (un `<article>` diviso internamente in `<section>` tematiche, es. i capitoli di un post lungo) oppure **articolo di sezioni** (una `<section>` che raggruppa più `<article>` indipendenti, es. l'elenco dei post di un blog).
```html
<!-- sezioni di un singolo articolo -->
<article>
  <h1>Guida a Helvetica</h1>
  <section>
    <h2>Storia</h2>
    <p>...</p>
  </section>
  <section>
    <h2>Helvetica oggi</h2>
    <p>...</p>
  </section>
</article>
<!-- sezione che raggruppa più articoli -->
<section id="blog">
  <article>
    <h1>Un nuovo sguardo su Futura</h1>
    <p>...</p>
  </article>
  <article>
    <h1>Conoscere Humanist</h1>
    <p>...</p>
  </article>
</section>
```
### aside
**`<aside>`** contiene contenuto correlato ma **marginale** rispetto al flusso principale: sondaggi, citazioni, informazioni aggiuntive, annunci, link correlati (una vera e propria *sidebar*, anche se le slide notano che non si chiama così perché "side" descriverebbe la presentazione, non il significato). Non ha uno stile di default.

> [!example] Pagina con tag semantici
> Una pagina che usa header/nav/main/section/article/aside/footer per una struttura tipica: intestazione con navigazione (Chi siamo, Articoli, Contatti), un articolo con titolo, data, autore e un `<aside>` di approfondimento collegato ma non centrale nel flusso, e un footer con copyright e contatti. È l'esempio di riferimento di `Materiale Didattico/Esempi/pagina.txt`: la stessa pagina, costruita con `<div>` generici invece che con tag semantici, apparirebbe identica graficamente ma sarebbe **meno chiara per le tecnologie assistive** e per i software che analizzano il documento.
## Accessibilità di base
L'**accessibilità** riguarda il rendere una pagina comprensibile anche a chi la consulta con tecnologie assistive (screen reader) o senza poterla vedere graficamente. Il markup semantico non è solo una questione di stile del codice: è il principale strumento di accessibilità che HTML mette a disposizione senza bisogno di CSS o JavaScript aggiuntivi.
- Usare i **tag semantici** giusti (`<nav>`, `<main>`, `<article>`...) invece di `<div>` generici: uno screen reader può saltare direttamente alla navigazione o al contenuto principale solo se sono marcati come tali.
- **`alt`** su ogni `<img>` che porta informazione (stringa vuota `alt=""` per immagini puramente decorative).
- **Gerarchia di heading** logica e senza salti (non usare `<h3>` solo perché visivamente più piccolo di `<h2>`, se semanticamente è un titolo di secondo livello).
- **`<label for="...">`** associato esplicitamente a ogni campo di form tramite `id` (vedi [[#label]]): senza label, uno screen reader non sa descrivere il campo.
- **`<fieldset>`** e **`<legend>`** per raggruppare campi correlati in un form con una descrizione (vedi [[#fieldset e legend]]).
## Tabelle HTML
Le tabelle rappresentano dati organizzati in righe e colonne. I tag principali:

| Tag | Significato |
|---|---|
| `<table>` | contenitore della tabella |
| `<tr>` | riga (*table row*) |
| `<th>` | cella di intestazione (*table header*) |
| `<td>` | cella di dato (*table data*) |
| `<caption>` | didascalia della tabella |
| `<thead>` / `<tbody>` / `<tfoot>` | raggruppano rispettivamente intestazione, corpo e piè di tabella |
| `<colgroup>` / `<col>` | raggruppano e impostano proprietà su una o più colonne |

```html
<table>
  <caption>Iscritti al corso</caption>
  <thead>
    <tr>
      <th>Nome</th>
      <th>Cognome</th>
      <th>Anno</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Giulia</td>
      <td>Rossi</td>
      <td>3</td>
    </tr>
    <tr>
      <td>Marco</td>
      <td>Bianchi</td>
      <td>2</td>
    </tr>
  </tbody>
</table>
```

> [!warning] Le tabelle sono per i dati, non per il layout
> Le tabelle HTML servono a marcare dati tabellari, non a impaginare una pagina (pratica comune in passato). Per il layout si usano Flexbox e Grid (vedi [[04 - CSS - layout, Flexbox, Grid e responsive]]).
## Form: struttura, invio e attributi
Un **form** è un insieme di elementi con cui l'utente interagisce per inviare informazioni a uno script che le elabora (login, registrazione, ricerca, contatti, ordini: qualunque interazione che richiede input). L'elemento contenitore è **`<form>...</form>`**, che racchiude sia elementi "attivi" (campi, bottoni, menu) sia altri elementi descrittivi.
```html
<form action="/contatto" method="POST">
  <label for="nome">Nome:</label>
  <input type="text" id="nome" name="nome">
  <label for="email">Email:</label>
  <input type="email" id="email" name="email">
  <button type="submit">Invia</button>
</form>
```
### Attributi di form
- **`action`**: la URL dello script che riceverà ed elaborerà i dati. Se assente, i dati vengono inviati alla **pagina corrente**.
- **`method`**: come i dati vengono inviati, `GET` (default) o `POST`.
- **`name`**: identifica il form, utile per accedervi via DOM (`document.forms.nome`, vedi [[06 - JavaScript e DOM]]).
- **`enctype`**: codifica dei dati inviati (default: url-encoded); va impostata a `multipart/form-data` quando il form contiene un `<input type="file">`.
- **`accept-charset`**: charset usato per i dati inviati (default: quello della pagina).
- **`autocomplete`**: se il browser deve suggerire valori già inseriti in precedenza (default: `on`).
- **`novalidate`**: disabilita la validazione nativa del browser (vedi [[#Validazione nativa lato client]]).
- **`target`**: dove aprire la risposta (default `_self`, la finestra corrente).

> [!info] GET vs POST
> | | GET (default) | POST |
> |---|---|---|
> | Dove vanno i dati | concatenati nella URL, dopo un `?`, separati da `&` | nel *body* della richiesta HTTP, non visibili nella URL |
> | Visibilità | visibile, salvabile nei preferiti, cacheable | non visibile, non cacheable |
> | Quando usarlo | ricerche, filtri, navigazione | login, registrazione, form di contatto, upload di file, dati sensibili |
> Esempio GET: `http://esempio.it/mailinglist.php?username=Mario&email=mario%40esempio.it` (i caratteri speciali sono *url-encoded*, es. `@` → `%40`). Il ciclo richiesta/risposta HTTP e i metodi sono trattati in dettaglio in [[01 - Internet, Web e HTTP]].

> [!question] Domanda tipica d'esame
> Se un form non specifica l'attributo `method`, quale metodo HTTP viene usato per inviare i dati?
> Risposta: `GET` (è il valore di default).
### label
L'elemento **`<label>`** definisce un'etichetta testuale per un campo di form: cliccando sulla label si attiva (mette a fuoco) il campo corrispondente. Ci sono due modi per associarli:
- **Associazione implicita**: il `<label>` circonda direttamente il campo.
  ```html
  <label>Nome: <input type="text" name="nome"></label>
  ```
- **Associazione esplicita**: l'attributo **`for`** di `<label>` è uguale all'attributo **`id`** dell'`<input>`. È la forma preferita perché più flessibile (label e input non devono essere adiacenti nel markup) ed è quella richiesta dalle tecnologie assistive.
  ```html
  <label for="fname">Nome:</label>
  <input type="text" id="fname" name="fname">
  ```

> [!warning] name vs id
> Sono due attributi diversi con scopi diversi: **`name`** è la chiave con cui il valore del campo viene inviato al server (`req.body.nome`, vedi [[09 - Express e API REST]]); **`id`** identifica univocamente l'elemento nella pagina ed è quello richiamato da `<label for="...">` e da CSS/JavaScript. Un campo dovrebbe avere entrambi, non uno al posto dell'altro.
## Tipi di input, textarea, select e button
L'elemento **`<input>`** cambia aspetto e comportamento in base all'attributo **`type`**:

| Valore di `type` | Cosa mostra |
|---|---|
| `text` | campo di testo a riga singola |
| `password` | campo di testo con caratteri nascosti |
| `email`, `tel`, `url` | varianti di testo con semantica dedicata (tastiera mobile adatta, validazione base) |
| `number`, `range` | valore numerico / cursore |
| `date`, `month`, `week`, `time`, `datetime-local` | selettori di data e ora |
| `color` | selettore di colore |
| `search` | campo di ricerca |
| `radio` | pulsante di opzione (scelta singola tra un gruppo con lo stesso `name`) |
| `checkbox` | casella di controllo (scelta multipla indipendente) |
| `file` | selezione di un file dal computer locale |
| `hidden` | valore non mostrato né modificabile dall'utente |
| `submit` | pulsante che invia il form |
| `reset` | pulsante che riporta il form ai valori di default |
| `button` | pulsante generico, senza azione predefinita |

> [!warning] `type="datetime"` non esiste più
> Le slide del corso elencano anche `datetime` fra i tipi HTML5 di data/ora, ma questo valore è stato rimosso dallo standard (mai implementato in modo uniforme dai browser): l'equivalente corretto e supportato è `datetime-local`.

Ogni campo definisce una **variabile** che viene inviata al server: l'attributo **`name`** è il nome/chiave della variabile, l'attributo **`value`** (opzionale) ne è il valore di default.

Altri elementi di input:
- **`<textarea>`**: area di testo **multi-riga**; la dimensione si specifica con gli attributi `cols` e `rows` (o via CSS).
  ```html
  <label for="msg">Messaggio:</label>
  <textarea id="msg" name="messaggio" rows="4" cols="40"></textarea>
  ```
- **`<select>`** / **`<option>`**: menu a tendina; `<select>` definisce il menu, ogni `<option>` una voce. Aggiungendo l'attributo `multiple` a `<select>` si ottiene un menu a **scelta multipla**; le opzioni si possono raggruppare con **`<optgroup label="...">`**, che aggiunge un'etichetta di gruppo non selezionabile.
  ```html
  <label for="corso">Corso:</label>
  <select id="corso" name="corso">
    <option value="pw">Programmazione Web</option>
    <option value="bdc">Basi di Dati</option>
  </select>
  ```
- **`<button type="submit">`**: invia il form (equivalente semanticamente a `<input type="submit">`, ma può contenere markup al suo interno, es. un'icona).
- **`<input type="file">`**: per funzionare richiede sul `<form>` `method="post"` **e** `enctype="multipart/form-data"`, altrimenti il file non viene trasmesso correttamente.
- **`<input type="hidden">`**: serve a inviare informazioni che non provengono da un'interazione diretta dell'utente (es. un id di sessione, dati di una query precedente, un token *nonce*).
### fieldset e legend
**`<fieldset>`** raggruppa logicamente più campi correlati di un form, e **`<legend>`** ne fornisce la descrizione (utile anche per l'accessibilità, vedi [[#Accessibilità di base]]).
```html
<fieldset>
  <legend>Dati di contatto</legend>
  <label for="email">Email:</label>
  <input type="email" id="email" name="email">
</fieldset>
```

> [!info] Regole di usabilità di un form
> - Evitare campi opzionali o non necessari.
> - Posizionare le label in modo chiaro, vicino al campo a cui si riferiscono.
> - Scegliere il tipo di `input` più specifico possibile (es. `email` invece di `text` generico).
> - Raggruppare gli input correlati (con `<fieldset>`).
> - Evidenziare visivamente l'azione principale (il bottone di invio).
> - Usare il **CSS** per posizionare e gestire lo stile del form (vedi [[03 - CSS - selettori, specificità e box model]]).
## Validazione nativa lato client
HTML5 offre una **validazione lato client** integrata nel browser, senza bisogno di JavaScript, tramite attributi sull'`<input>`:

| Attributo | Effetto |
|---|---|
| `required` | il campo è obbligatorio, il form non viene inviato se è vuoto |
| `type="email"` / `type="url"` | verifica automaticamente il formato |
| `minlength` / `maxlength` | lunghezza minima/massima del testo |
| `min` / `max` | valori minimo/massimo ammessi (campi numerici, date, range) |
| `step` | intervallo ammesso tra un valore numerico e l'altro |
| `pattern` | espressione regolare personalizzata che il valore deve rispettare |
| `disabled` | il campo non è modificabile e non viene inviato |
| `readonly` | il campo è visibile ma non modificabile (viene comunque inviato) |
| `size` | larghezza del campo in caratteri (aspetto, non validazione) |

```html
<form action="/contatto" method="POST">
  <label for="nome">Nome:</label>
  <input type="text" id="nome" name="nome" required minlength="2">
  <label for="email">Email:</label>
  <input type="email" id="email" name="email" required>
  <label for="msg">Messaggio:</label>
  <textarea id="msg" name="messaggio" required></textarea>
  <button type="submit">Invia messaggio</button>
</form>
```
Se il `<form>` ha l'attributo `novalidate`, il browser **non** esegue questa validazione, ed è cura dello script ricevente controllare i dati.

> [!warning] La validazione lato client non basta
> La validazione HTML5 gira nel browser dell'utente e può essere **aggirata facilmente** (JavaScript disabilitato, richiesta inviata direttamente senza passare dal form, uso di strumenti come `curl`). Serve sempre anche una **validazione lato server**, che è l'unica su cui si può davvero fare affidamento: va eseguita nello script che riceve i dati (`req.body`), restituendo un errore **400** in caso di dati mancanti o non validi. Questa parte — ricevere il form con Express, leggere `req.body`, validare e rispondere — è trattata in [[09 - Express e API REST]].

> [!question] Domanda tipica d'esame
> La validazione lato client (HTML5, attributo `required`) sostituisce la validazione lato server?
> Risposta: no. Impedisce solo invii accidentali da un browser conforme; i dati vanno sempre validati anche sul server, perché il client non è affidabile.
## Riferimenti
- `Materiale Didattico/Slide/PW01-Internet e HTML.pdf` (parte HTML, da p. 63: markup, struttura del documento, elementi, attributi, elementi vuoti, albero degli elementi, dichiarazione DOCTYPE, evoluzione delle versioni, head/title/body).
- `Materiale Didattico/Slide/PW03-HTML-2.pdf` (tag semantici HTML5, heading, liste, elementi di testo, block/inline, commenti, caratteri di escape, immagini, link e URL, mapping URL → filesystem, tabelle base, validatore W3C).
- `Materiale Didattico/Slide/PW07-CSS-3.pdf`, pp. 47-51 (ancore con `id`, link a punti di altre pagine, attributo `target`, link `mailto:` e `tel:`).
- `Materiale Didattico/Slide/PW11-CSS-HTML-7.pdf` (form: elemento form, input, label, action/method, tipi di input, attributi di validazione, textarea/select/optgroup, file/hidden, fieldset/legend, tabelle HTML in dettaglio).
- `Materiale Didattico/Slide/PW47-Forms-2.pdf` (form con label, attributi di validazione HTML5, GET vs POST).
- `Materiale Didattico/Esempi/pagina.txt`: pagina di esempio sui tag semantici (header, nav, main, section, article, aside, footer).
- `Materiale Didattico/Esempi/01 - kitchen/kitchen.html`: esempio storico di pagina HTML minimale (doctype, head/body, img con alt, formattazione con `<strong>`/`<em>`, `<hr>`, `<small>`).
