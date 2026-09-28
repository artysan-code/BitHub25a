---
tipo: corso
materia: Programmazione Web
codice: PW
anno: 3
semestre: "2"
cfu: 6
ssd: ING-INF/05
docenti:
  - Pierpaolo Loreti
  - Lorenzo Bracciale
propedeuticita: []
---
# Programmazione Web
Corso dei proff. **Pierpaolo Loreti** e **Lorenzo Bracciale** sulle **applicazioni web full stack** (Browser ⇔ Server web ⇔ Storage): come un'applicazione web viene costruita e come funziona, imparando facendo. Le lezioni puntano più sui principi che sulle istruzioni per scrivere codice, e l'esame premia soprattutto la **comprensione teorica**.
## Modalità d'esame
L'esame (regole A.A. 2025/26, in `Materiale Didattico/Esami/PW-Esame-2026.pdf`) ha due parti:
1. **Test a risposta multipla** sugli argomenti del corso. Foto di un test reale in `Materiale Didattico/Risorse Studenti/`.
2. **Presentazione del progetto e discussione orale.**

Il voto tiene conto di **qualità tecnica del progetto**, **capacità di spiegare e discutere le scelte** e **comprensione degli argomenti del corso**.
### Il progetto
Applicazione web completa **a tema libero** (catalogo, lista attività, prenotazioni, recensioni, dashboard, quiz…) con frontend e backend, sviluppata in un repository **GitHub Classroom**.
- **Frontend**: HTML semantico; CSS leggibile e responsive (Flexbox e/o Grid); JavaScript separato dall'HTML; manipolazione del DOM ed eventi utente (click, submit, input); chiamate `fetch` con `async`/`await`; stati visibili (caricamento, errore, successo, lista vuota); validazione lato client.
- **Backend (Node.js + Express)**: progetto con `package.json`; almeno le rotte REST `GET /api/risorsa`, `GET /api/risorsa/:id`, `POST /api/risorsa`; risposte JSON con status code appropriati; validazione lato server con **400** su dati mancanti o non validi; gestione minima degli errori (404, 400, 500); middleware per il parsing del body JSON e per i file statici.
- **Dati**: in memoria, file JSON o database leggero.
- **Git**: commit significativi con messaggi chiari; la storia deve mostrare le fasi di sviluppo, non un unico commit finale.
- **Documento di specifiche**, da consegnare **prima dello sviluppo** in `specifiche/*.md` con il commit `specifiche: primo documento di specifica del progetto`: obiettivo dell'app, cosa può fare l'utente, struttura del frontend, mockup minimale (anche a mano), scenari di test.
- **`README.md` del progetto**: titolo e descrizione, installazione (`npm install`), avvio di backend e frontend, funzionalità implementate ed extra, note sull'uso dell'AI.

**Extra facoltativi** (devono funzionare ed essere documentati): PUT/DELETE, ricerca o filtro lato server, persistenza su file JSON o database (SQLite, MongoDB), autenticazione (sessioni o token), test con jest e supertest, deploy online, EJS o altro template engine.
### Cosa mostrare all'esame
1. **Funzionamento** dell'applicazione nel browser.
2. **Codice**: spiegare le scelte architetturali; il docente può chiedere di modificare o estendere una parte al momento.
3. **Analisi e debug**: DevTools (Elements, Console, Network, Sources), ispezione delle richieste HTTP (headers, payload, response, status code), log lato server, breakpoint nel browser o con `node --inspect`.
4. **Test funzionali** manuali: input valido, input non valido, lista vuota, errore di rete simulato — cosa ci si aspettava e cosa si è verificato.
5. **Storia Git** su GitHub o con `git log`.
6. **Specifiche per l'AI**: prompt usati, modifiche al codice generato, parti scritte autonomamente.

> [!warning] Uso dell'AI
> Strumenti come ChatGPT, Claude e Copilot sono **consentiti e incoraggiati**, ma bisogna saper capire, spiegare e modificare ogni parte del codice. Presentare codice che non si sa spiegare equivale a copiare.
## Programma e Appunti
Le note seguono l'ordine del corso; le slide da cui deriva ciascuna stanno nel suo frontmatter. Coprono tutti gli argomenti che il docente verifica all'esame, sia sul codice del progetto sia con le domande.
1. [[01 - Internet, Web e HTTP]]: web app e architettura full stack, client-server, URI e URL, DNS, ciclo richiesta/risposta HTTP, metodi, status code, header, JSON.
2. [[02 - HTML semantico e form]]: struttura del documento, tag semantici, link e percorsi, tabelle, form, tipi di input, validazione nativa.
3. [[03 - CSS - selettori, specificità e box model]]: inclusione, selettori, cascata, ereditarietà, specificità, unità, font e testo, box model, background, reset.
4. [[04 - CSS - layout, Flexbox, Grid e responsive]]: display, liste, position, float, Flexbox, Grid, layout responsive, variabili CSS, Bootstrap.
5. [[05 - Git e GitHub]]: le tre aree, commit, remote, push/fetch/pull, branch e merge, GitHub Classroom e Git nel progetto d'esame.
6. [[06 - JavaScript e DOM]]: il linguaggio (tipi, funzioni, closure, oggetti, prototipi, array), il DOM e gli eventi.
7. [[07 - JavaScript asincrono, Promise, fetch e CORS]]: event loop, callback, Promise, async/await, fetch, stati dell'interfaccia, CORS.
8. [[08 - Node.js e npm]]: siti statici, dinamici e API based, runtime Node, moduli, server HTTP nativo, npm e `package.json`.
9. [[09 - Express e API REST]]: routing, middleware, file statici, gestione degli errori, REST, status code, JSend, form lato server, mini API d'esempio.
10. [[10 - Server side rendering con EJS e autenticazione]]: SSR vs CSR, EJS, sessioni e cookie, token e JWT, middleware di protezione (extra facoltativi del progetto).
## Materiale di riferimento
- **Slide ufficiali** in `Materiale Didattico/Slide/`: `PW00`–`PW11` (Internet, HTML, Git, web server e URL, CSS), `javascript_2026.pdf`, `PW31`–`PW48` (JS asincrono, Fetch e CORS, Node.js, Express, REST, EJS, form, autenticazione con token).
- **Esempi del docente** in `Materiale Didattico/Esempi/`: pagine HTML/CSS (box model, background, grid, Bootstrap), esercizi sul DOM e sulle Promise, esercizi svolti in aula (`live/`). Il codice mostrato a lezione viene pubblicato dai docenti dopo la lezione.
- **Registrazioni delle lezioni** sul Team del corso, canale «Lezioni» (lezioni in streaming e registrate).
- **Testi di riferimento**: A. Freeman — *The Definitive Guide to HTML5*; D. Flanagan — *JavaScript: The Definitive Guide*.
- **Siti**: [MDN Web Docs](https://developer.mozilla.org/), [W3Schools](https://www.w3schools.com/), [javascript.info](https://javascript.info/).
- **Ambiente di lavoro** consigliato: VS Code, Chrome, Node.js, Git (Git Bash su Windows), GitHub con licenza Education per Copilot.
