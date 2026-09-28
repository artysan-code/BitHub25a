# Contribuire a BitHub25a

Grazie per voler contribuire! Questa repository è una raccolta di appunti universitari — ogni contributo aiuta i futuri studenti. Le regole qui sotto servono a mantenere il materiale coerente, navigabile su Obsidian e leggibile in un (futuro) sito web.

---

## Prima di iniziare

1. Clona la repository e apri la cartella come **vault Obsidian** (File → Open vault → Open folder as vault).
2. Installa i **community plugin** elencati (`obsidian-latex-suite`, `pseudocode-in-obs`) da *Settings → Community plugins → Browse*.
3. La cartella `.obsidian/` **non è versionata** (è nel `.gitignore`): tema, plugin e impostazioni del vault sono personali e non vanno mai committati.

### Plugin opzionali

Per una migliore esperienza durante la stesura delle note, considera:

- **Dataview** — per generare indici e tabelle dinamiche dalle note.
- **Paste image rename** — per assegnare nomi puliti agli screenshot incollati.

Non sono obbligatori e non devono alterare le note esistenti.

---

## Struttura della repository

```
Corsi/<Anno>/<Materia>/
├── README.md             ← OBBLIGATORIO, unica fonte info corso
├── Appunti/              ← opzionale, note .md dello studente
│   └── assets/           ← immagini usate dalle note dello stesso corso
├── Esercizi/             ← opzionale, esercizi svolti / tracce d'esame
└── Materiale Didattico/  ← opzionale, slide PDF / esercitazioni del docente
```

Gli anni sono `Primo Anno/`, `Secondo Anno/`, `Terzo Anno/`.

### Principi

1. **`README.md` è l'unica fonte d'informazione sul corso.** Niente `Informazioni-Corso.md`, `ARGOMENTI.md`, `GUIDA_STUDIO.md` o simili. Tutto quello che va detto sul corso — esame, docenti, libri, argomenti, metodo di studio, note organizzative — sta nel README.
2. **Contenuto libero negli appunti.** Dentro `Appunti/` ed `Esercizi/` ognuno organizza come vuole (per lezione, per argomento, per libro). Non esistono template per materia. `Materiale Didattico/` segue invece i nomi standard descritti sotto.
3. **Rispetta lo stile del corso** su cui lavori: se un corso ha già un pattern, non inventarne uno nuovo.

### Nomi cartelle canonici

| Scopo | Nome canonico | Mai usare |
|---|---|---|
| Note studente | `Appunti/` | `Lezioni`, `Appunti Corso`, `Riassunti` (a sé) |
| Esercizi | `Esercizi/` | — |
| Materiale docente | `Materiale Didattico/` | `Materiale-Didattico`, `Materiali Didattici` |
| Immagini | `assets/` lowercase dentro la cartella che le usa | `Asset`, `Assets`, `img` |
| Info corso | `README.md` alla radice materia | file separati |

Cartelle extra solo se servono (es. `Modulo-I/` e `Modulo-II/` per corsi divisi, `Progetti/` per lavori integrati).

### Dentro `Materiale Didattico/`

Si usano solo le sottocartelle seguenti, create quando arriva il primo file:

| Cartella | Contenuto |
|---|---|
| `Slide/` | slide e dispense delle lezioni |
| `Esercitazioni/` | esercizi ed esercitazioni del docente (eventuale `Problem Set/` dentro) |
| `Esami/` | tracce passate, simulazioni, regole e programma d'esame (eventualmente per anno: `Esami/2024-2025/`) |
| `Libri/` | libri di testo e dispense estese |
| `Esempi/` | codice mostrato dal docente (corsi di programmazione) |
| `Progetto/` | specifiche, linee guida e template del progetto d'esame |
| `Risorse Studenti/` | materiale di altri studenti (appunti scansionati, foto di test) |

- **Niente file sciolti** alla radice di `Materiale Didattico/`: ogni file sta in una delle cartelle sopra.
- **Moduli**: se un corso ha moduli con materiale separato su più tipi, il modulo è un livello sopra (`Modulo I/Slide/`, `Sistemi Operativi/Esempi/`). Se cambia un solo tipo, il modulo è una sottocartella di quel tipo (`Slide/Modulo 12 CFU/`).
- **Niente archivi, binari compilati o dipendenze** (`.zip`, eseguibili, `node_modules/`): si estraggono e si versionano solo i file utili.
- **Niente dati personali di altri** (esiti con matricole, nomi, voti).

---

## Come aggiungere contenuti

### Modificare una nota esistente

- Apri la nota in Obsidian, modifica, salva.
- Rispetta lo stile del file: stessi callout (`> [!quote]`, `> [!example]`, ecc.), stessa profondità di heading, stesso uso di grassetto/corsivo.
- Se correggi un errore tecnico, menzionalo nel commit message.

### Creare una nuova nota

**Naming**: `NN - Titolo.md` con zero-padding a due cifre (`01`, `02`, …, `10`, `11`). Serve perché l'ordinamento alfabetico mette `10` prima di `2` senza padding. Spazi e accenti italiani OK.

Nomi liberi solo quando non c'è una sequenza (formulari, riassunti tematici).

**Frontmatter minimo**:

```yaml
---
tags:
  - <slug-materia>   # es. basi-di-dati, analisi-matematica
  - lezione          # oppure: esercizi, riassunto, formulario, progetto…
slide: "<file.pdf>"  # opzionale, se la nota deriva da una slide specifica
---
```

`tags` e il riferimento slide aiutano la ricerca in Obsidian e l'indicizzazione nel futuro sito.

### Aggiungere un nuovo corso

1. Crea `Corsi/<Anno>/<Nome Materia>/` con almeno il `README.md`.
2. Scheletro minimo del `README.md`:

   ```markdown
   # <Nome Materia>

   **Codice**: XX · **CFU**: N · **Semestre**: 1|2|1-2 · **Anno**: N°
   **SSD**: <settore>
   **Docente/Docenti**: <nomi>
   **Propedeuticità**: <materie> (o "nessuna")

   ## Modalità d'esame
   ...

   ## Materiale di riferimento
   ...
   ```

3. Aggiorna l'indice nel `README.md` della repository alla root.
4. Le cartelle `Appunti/`, `Esercizi/`, `Materiale Didattico/` si creano quando arriva il primo contenuto, non prima.

### Formato Markdown

- **Obsidian Flavored Markdown**: callout (`> [!info]`), wikilink (`[[Nota]]`), embed (`![[assets/foo.png]]`).
- **LaTeX**: inline `$...$`, block `$$...$$`. Serve il plugin Latex Suite.
- **Pseudocodice**: blocchi ` ```pseudo ` (plugin Pseudocode), sintassi LaTeX *algorithmic* (nome nel `\caption`, niente `\Procedure`); vedi gli appunti di Algoritmi e Strutture Dati per il modello.
- Evita HTML grezzo quando esiste l'equivalente Markdown/Obsidian.
- Link interni: preferisci **wikilink** (`[[...]]`) ai link relativi — restano validi anche se si rinomina una cartella.

---

## Git e Pull Request

### Branch

- Branch principale: `release`.
- Per contributi significativi, crea un branch tematico: `appunti/<materia-breve>`, `fix/<note>`, `docs/<scope>`.

### Commit

Commit **atomici** (un cambiamento logico ciascuno), messaggio breve in italiano nel formato `tipo(scope): descrizione`:

```
tipo(scope): descrizione breve

corpo opzionale (il "perché", se non ovvio)
```

**Tipi**: `note` (appunti), `fix` (correzioni di contenuto), `docs` (meta-doc: README, CONTRIBUTING), `chore` (manutenzione/normalizzazioni), `assets` (immagini/PDF), `struct` (riorganizzazioni di cartelle), `ci` (workflow). **Scope** = codice del corso (es. `asd`, `bdc`, `ro`) oppure `repo` / `obsidian` / `hackathon`.

Esempi:

```
note(bdc): aggiunta lezione 6 Algebra Relazionale
fix(fis): correzione formula cinetica in lezione 3
chore(asd): normalizzazione pseudocodici a blocchi pseudo
docs(repo): aggiornamento indice corsi
```

**Non committare mai**: file `.zip` di materiali pesanti, file binari personali, la cartella `.obsidian/` — già gestiti dal `.gitignore`.

### Pull Request

- Apri la PR verso `release`.
- Compila il template: descrivi cosa hai aggiunto/modificato e su quale corso.
- Il workflow `link-check` verifica automaticamente che i link non siano rotti.
- Un maintainer (vedi `CODEOWNERS`) farà review prima del merge.

---

## Segnalare un problema

Usa **Issues** con il template appropriato:

- **Bug / errore** — un'informazione sbagliata, un link rotto, un file mancante.
- **Richiesta materiale** — manca un corso o una lezione.
- **Proposta** — modifiche strutturali, nuovi contenuti trasversali.

---

## Cosa non fare

- Non riorganizzare cartelle o rinominare file esistenti senza discuterne prima — rompe i wikilink e i link esterni.
- Non aggiungere `README.md`, indici o file di metadata a ogni materia se non utili.
- Non modificare le note altrui per ragioni puramente stilistiche (grassetti/corsivi diversi).
- Non committare la cartella `.obsidian/`: è la configurazione personale del tuo vault.

---

## Licenza dei contributi

Contribuendo, accetti che il tuo contributo agli **appunti** sia rilasciato sotto la stessa licenza **[CC BY-NC-SA 4.0](LICENSE)** della repository. Non caricare materiale protetto da copyright altrui (es. slide o testi dei docenti) se non ne hai il diritto.

---

## Dubbi?

Apri una Issue con label `question` o contatta i maintainer:
- [@artysan-code](https://github.com/artysan-code) (Samuel Tagliacozzo)
- [@Cromocon](https://github.com/Cromocon) (Marius Craciun)
