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
L'esame (regole A.A. 2025/26, in `Materiale Didattico/Esame/PW-Esame-2026.pdf`) ha due parti:
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
Argomenti che il docente verifica all'esame, sia sul codice del progetto sia con le domande. Le slide di `Materiale Didattico/Slide/` sono il riferimento per tutti.
- **Git e GitHub**: repository, commit con messaggi chiari, storia di sviluppo, branch, README come documentazione.
- **Internet, Web e HTTP**: client/server, struttura di una URL, ciclo richiesta/risposta, metodi, status code, header, JSON, CORS.
- **HTML**: struttura semantica, organizzazione dei contenuti, form e input, attributi, accessibilità di base.
- **CSS**: selettori e specificità, box model, Flexbox e Grid, design responsive, organizzazione dei fogli di stile.
- **JavaScript**: DOM, eventi, Promise, `fetch`, `async`/`await`, gestione degli errori e degli stati dell'interfaccia.
- **Node.js**: npm e `package.json`, sistema dei moduli, avvio del server, log dal terminale.
- **Express**: routing, middleware, parametri di rotta e query, parsing del body, file statici.
- **REST**: rotte progettate attorno alle risorse, scelta di metodi e status code, risposte JSON coerenti.
## Materiale di riferimento
- **Slide ufficiali** in `Materiale Didattico/Slide/`: `PW00`–`PW11` (Internet, HTML, Git, web server e URL, CSS), `javascript_2026.pdf`, `PW31`–`PW48` (JS asincrono, Fetch e CORS, Node.js, Express, REST, EJS, form, autenticazione con token).
- **Esempi del docente** in `Materiale Didattico/Esempi/`: pagine HTML/CSS (box model, background, grid, Bootstrap), esercizi sul DOM e sulle Promise, esercizi svolti in aula (`live/`). Il codice mostrato a lezione viene pubblicato dai docenti dopo la lezione.
- **Registrazioni delle lezioni** sul Team del corso, canale «Lezioni» (lezioni in streaming e registrate).
- **Testi di riferimento**: A. Freeman — *The Definitive Guide to HTML5*; D. Flanagan — *JavaScript: The Definitive Guide*.
- **Siti**: [MDN Web Docs](https://developer.mozilla.org/), [W3Schools](https://www.w3schools.com/), [javascript.info](https://javascript.info/).
- **Ambiente di lavoro** consigliato: VS Code, Chrome, Node.js, Git (Git Bash su Windows), GitHub con licenza Education per Copilot.
