---
tags:
  - programmazione-web
  - git
slide:
  - "PW02-GIT.pdf"
  - "PW04-2-GIT-2.pdf"
---
# Git e GitHub
**Git** è il sistema di controllo di versione usato per tutto il corso: serve per tenere traccia delle modifiche al codice, collaborare senza sovrascrivere il lavoro altrui e consegnare il progetto d'esame su **GitHub Classroom** (lo strumento con cui il docente assegna un repository a ogni studente: vedi [[#Primi passi: setup e GitHub Classroom]]). Questa nota copre i concetti di base (repository, staging area, commit), la sincronizzazione con un repository remoto (push, fetch, pull: vedi [[#Sincronizzare con il remote: push, fetch e pull]]) e i branch (linee di sviluppo indipendenti: vedi [[#I branch: linee di sviluppo indipendenti]]), e chiude con una sezione pratica su come usare Git nel progetto d'esame.
## Perché serve un sistema di controllo di versione
Senza uno strumento dedicato, il modo "naturale" di tenere versioni diverse di un documento è duplicare i file a mano, magari mettendo la data nel nome: `120525_document_updated.txt`, `120605_document_amended.txt`, `120605_document_latest.txt`, `120605_document_latestcopy.txt`... (l'elenco della slide, introdotto dalla didascalia «Se non usate GIT!!!», comprende anche `120604_document.txt`, `120605_document_John.txt`, `120605_document.txt`, `1200602_document.txt` e `document_meeting.txt`). Il risultato è una cartella illeggibile in cui non si capisce più qual è la versione corretta, e il problema peggiora ulteriormente quando più persone lavorano sugli stessi file in una cartella condivisa: due persone modificano lo stesso `index.txt` in parallelo e, quando i file tornano nella cartella condivisa, una delle due versioni sovrascrive l'altra e il lavoro va perso. Questo è il **problema dell'overwriting**.

> [!example] Il problema dell'overwriting (slide «Vi è mai successo?»)
> Due copie di `index.txt` partono dalla stessa versione (righe `AAAA` e `BBBB`) ma una ha come terza riga `XXXX` e l'altra `YYYY`. Quando entrambe vengono caricate nella stessa **Shared Folder**, la seconda sovrascrive la prima: nella cartella resta una sola versione e la modifica dell'altra persona è persa.

> [!quote] Definizione — Sistema di controllo di versione (Version Control System)
> Sistema che **registra e salva le modifiche** ai file mentre li si modifica, e permette di **ripristinare una versione precedente** del proprio lavoro in qualsiasi momento. È la base per gestire il codice in modo ordinato e per farlo collaborando con altre persone senza perdere modifiche.

Quello che si vorrebbe davvero è che ogni modifica venga salvata come una versione a sé, che le versioni di persone diverse possano convivere ed essere confrontate, e che il sistema segnali quando due modifiche sono in conflitto invece di far sparire silenziosamente una delle due. È esattamente questo il ruolo di Git. La slide «Cosa ci piacerebbe?» mostra la stessa situazione con tre versioni di `index.txt` (`ZZZZ`, `XXXX`, ...) che convivono nella cartella condivisa e un segnale di avviso, a indicare che il sistema deve segnalare le modifiche in conflitto invece di perderne una.
## Git: caratteristiche e vantaggi
> [!quote] Definizione — Git
> Sistema di controllo di versione **open source** e **distribuito**, progettato per la velocità e l'efficienza nella gestione del codice.

*(extra, non da slide)* **Distribuito** significa che ogni sviluppatore ha sulla propria macchina una copia completa della cronologia del progetto (il repository locale), non solo l'ultima versione dei file: si può quindi lavorare, fare commit e consultare la cronologia anche senza connessione, e sincronizzarsi con gli altri solo quando serve.
Git aiuta a:
- tenere traccia della **cronologia del codice** (chi ha scritto cosa e quando);
- **collaborare come team** senza sovrascrivere il lavoro altrui;
- **scoprire chi ha apportato quali modifiche**, e perché (tramite i messaggi di commit);
- **distribuire il codice** nella gestione temporanea o nella produzione (formulazione della slide; *(extra, non da slide)* qui «temporanea» indica gli ambienti di prova prima del rilascio, da non confondere con la **staging area** di Git, che è l'area intermedia descritta più avanti).
## Le tre aree di lavoro
Git organizza il lavoro in tre aree distinte, ognuna con un ruolo preciso nel passaggio da "ho modificato un file" a "la modifica è salvata nella cronologia".

> [!quote] Definizione — Repository, Working tree, Staging Area
> - **Repository**: il "contenitore" che tiene traccia delle modifiche, cioè l'intera cronologia dei commit del progetto.
> - **Working tree (o directory)**: è costituito dai file su cui si sta lavorando in questo momento, quelli visibili e modificabili nel filesystem.
> - **Index (o Staging Area)**: è l'area intermedia dove vengono **preparati** i commit, cioè dove si "mettono da parte" le modifiche che si vogliono includere nel prossimo commit.

Il flusso tra le tre aree è sempre lo stesso: i file passano dal **Working tree** all'**Index** con un'operazione di *registrazione* (staging), e dall'**Index** al **Repository** con un'operazione di **commit**. *(extra, non da slide: le slide non contengono un diagramma a frecce tra le tre aree; il flusso va letto così)* Si registra ciò che si vuole salvare, poi si trasforma la registrazione in uno snapshot permanente.

> [!question] Domanda tipica d'esame
> Quali sono le tre aree di lavoro di Git e che ruolo ha ciascuna?
> Il **Repository** è il contenitore che tiene traccia delle modifiche (la cronologia dei commit); il **Working tree** (o directory) è costituito dai file su cui si sta lavorando; l'**Index** (o **Staging Area**) è l'area dove vengono preparati i commit. Le modifiche passano dal Working tree all'Index con lo staging e dall'Index al Repository con il commit.

> [!question] Domanda tipica d'esame
> *(a risposta multipla)* In quale area Git «prepara» le modifiche da includere nel prossimo commit?
> a) Repository; b) Working tree; c) Index (Staging Area); d) Repository remoto.
> Risposta: **c**. Il Repository contiene i commit già creati, il Working tree i file in modifica, il repository remoto è una copia su un altro server.
## Dal working tree al repository: il ciclo add → commit
Il flusso di lavoro base (**Basic Workflow**) con Git è sempre composto da tre passi:
1. **Modificare i file** nel working tree (si scrive codice normalmente, con l'editor).
2. Eseguire lo **staging** delle modifiche che si desidera includere nel commit successivo, cioè spostarle nell'Index.
3. Eseguire il **commit** delle modifiche: il commit prende i file dall'Index e li memorizza come **snapshot** nel repository.

> [!example] Ciclo add → commit *(extra, non da slide: le slide mostrano solo `git commit ...`; `git add` e le opzioni sono provati in un repository di prova)*
> ```bash
> # 1. modifica i file nel working tree (con l'editor)
>
> # 2. staging: sposta le modifiche nell'Index
> git add index.html style.css
>
> # 3. commit: crea uno snapshot permanente nel repository
> git commit -m "aggiunta struttura base della pagina"
> ```
> `git add` accetta anche `git add .` *(extra, non da slide)* per mettere in staging tutte le modifiche della cartella corrente.

> [!warning] Errori frequenti
> - Fare `git commit` senza aver prima fatto `git add`: se un file modificato non è stato messo in staging, quella modifica **non** entra nel commit.
> - Confondere lo staging con il salvataggio del file: `git add` non modifica il file, prepara solo cosa finirà nel prossimo commit.
> - Fare un unico commit enorme a fine progetto invece di tanti commit piccoli e frequenti: rende la cronologia illeggibile (vedi [[#Git e GitHub nel progetto d'esame]]).

> [!question] Domanda tipica d'esame
> Che cosa succede se si modifica un file e si esegue `git commit` senza aver eseguito `git add`?
> Il commit prende i file **dall'Index** (non dal Working tree): se la modifica non è stata messa in staging non entra nel commit e il file resta modificato nel working tree (provato: dopo il commit `git status` lo mostra ancora come modificato). Se invece si fa `git add` e poi si modifica di nuovo il file, nel commit entra solo la versione che era nell'Index.

> [!question] Domanda tipica d'esame
> *(a risposta multipla)* Quale tra queste NON è un passo del Basic Workflow di Git?
> a) modificare i file nel working tree; b) eseguire lo staging delle modifiche; c) eseguire il commit; d) eseguire il push prima di aver modificato i file.
> Risposta: **d**. I tre passi sono modifica, staging e commit; il push riguarda la sincronizzazione con il repository remoto.
## Il commit e i messaggi chiari
Ogni commit è uno **snapshot** dello stato dei file al momento in cui viene creato, con un timestamp e un messaggio associato. I commit successivi si susseguono nel **Local Repository** formando una linea temporale (la slide «Commit» mostra quattro commit lungo un asse del tempo, ciascuno con data e ora, per esempio 08/01/2022 12:06 e 08/04/2022 11:52, associati ai file html, css e js): ogni commit "ricorda" quello precedente, ed è per questo che la cronologia di un progetto Git è ricostruibile commit per commit.
*(extra, non da slide: le slide non spiegano come scrivere un buon messaggio, ma è un requisito valutato esplicitamente nel progetto d'esame — vedi [[#Git e GitHub nel progetto d'esame]].)* Un messaggio di commit chiaro deve spiegare **cosa cambia** e, quando non è ovvio, **perché**. Messaggi generici come `fix`, `update`, `wip` o `cose varie` rendono la cronologia inutile per chi (compreso il docente, o te stesso fra un mese) deve capire come si è evoluto il progetto.

> [!example] Messaggi di commit *(extra, non da slide)*
> ```bash
> # messaggio chiaro: dice cosa è stato fatto
> git commit -m "aggiunta validazione lato client del form di iscrizione"
>
> # messaggio da evitare: non dice nulla di utile
> git commit -m "fix"
> ```
## Storia, stato e differenze: status, log e diff
*(extra, non da slide: le slide non mostrano questi comandi, ma sono lo strumento pratico per verificare lo stato del repository e per mostrare la storia di sviluppo richiesta all'esame.)*
Tre comandi coprono la quasi totalità delle domande "cosa sta succedendo nel mio repository?":
- `git status`: mostra quali file sono modificati, quali sono in staging e quali non sono ancora tracciati da Git.
- `git log`: mostra la cronologia dei commit (autore, data, messaggio); `git log --oneline` la mostra in forma compatta, una riga per commit.
- `git diff`: mostra le differenze riga per riga tra il **working tree e l'Index**, cioè le modifiche non ancora messe in staging (se un file è già in staging, mostra solo ciò che è stato modificato dopo `git add`); `git diff --staged` confronta l'Index con l'ultimo commit; `git diff HEAD` confronta il working tree con l'ultimo commit (provato in un repository di prova); `git diff <commit1> <commit2>` o `git diff main bugfix` confrontano due commit/branch qualsiasi *(extra, non da slide)*.

> [!example] Comandi di ispezione
> ```bash
> git status              # cosa è modificato / in staging / non tracciato
> git log --oneline        # cronologia compatta dei commit
> git diff                 # differenze non ancora messe in staging
> git diff --staged        # differenze già messe in staging, non ancora committate
> git diff HEAD            # working tree contro ultimo commit (staging e non)
> ```
## Repository locale e repository remoto
Finora si è parlato del **repository locale**: quello sulla propria macchina, con la sua cronologia completa di commit. Git è distribuito, quindi lo stesso progetto può esistere in più copie indipendenti — tipicamente una copia locale per ogni sviluppatore, più una copia condivisa che fa da punto di riferimento comune: il **repository remoto**.
Nel corso il repository remoto è ospitato su **GitHub** (la slide «Repository remoti» mostra un unico Remote Repository collegato a due Local Repository, ciascuno con i propri file html e css). *(extra, non da slide: GitHub è una piattaforma che fornisce hosting per repository Git, gestione degli accessi e strumenti collaborativi come issue e pull request.)* GitHub Classroom serve per la consegna dei progetti. Un repository locale può essere collegato a uno o più repository remoti; per convenzione il primo remoto collegato si chiama **`origin`** *(extra: "origin" è solo un nome convenzionale, non una parola riservata di Git — si potrebbe chiamare diversamente, ma quasi tutti gli strumenti lo usano come default)*.

> [!info] Creare un repository locale da zero
> *(extra, non da slide)* Se non si parte da GitHub Classroom, un repository locale nuovo si crea con `git init` nella cartella del progetto. Nel corso, invece, il repository viene creato automaticamente da GitHub Classroom e poi **clonato** in locale (vedi [[#Primi passi: setup e GitHub Classroom]]).
## Sincronizzare con il remote: push, fetch e pull
Una volta che repository locale e remoto sono collegati, bisogna tenerli allineati nelle due direzioni: mandare le proprie modifiche verso il remoto, e ricevere le modifiche altrui dal remoto.
**Push** invia i commit locali al repository remoto: è, di fatto, un **upload** della propria cronologia.

> [!example] Push *(extra, non da slide: le slide indicano solo la funzione di push, non il comando)*
> ```bash
> git push origin main
> ```
> Manda i commit del branch locale `main` (il branch principale, vedi [[#I branch: linee di sviluppo indipendenti]]) al branch `main` del remoto `origin`.

Per la direzione opposta, **Pull** è il processo che integra i cambiamenti del remoto nel locale, e in realtà è composto da due passi distinti:
- **Fetch**: recupera le ultime modifiche dal repository remoto, ma **non** le applica immediatamente alla working directory locale.
- **Merge**: integra le modifiche recuperate nella working directory, combinandole con le modifiche esistenti (vedi [[#Unire i branch: git merge]]).

`git pull` esegue fetch e merge in un solo comando; è, di fatto, un **download** che aggiorna subito i file locali.

> [!example] Fetch e pull *(extra, non da slide: le slide indicano solo i due passi, non i comandi)*
> ```bash
> git fetch origin    # scarica gli aggiornamenti, non li applica
> git merge origin/main  # li integra nel branch corrente
>
> # equivalente in un solo comando:
> git pull origin main
> ```
> *(extra, non da slide, provato con git 2.56.1)* Se `main` locale e `origin/main` sono **divergenti** (ciascuno ha commit che l'altro non ha), `git pull` senza opzioni si interrompe con l'errore `Need to specify how to reconcile divergent branches`: va indicato come procedere, per esempio con `git pull --no-rebase origin main`, che esegue il merge e crea il merge commit (vedi [[#Branch remoti e origin/main]]).

> [!question] Domanda tipica d'esame
> Qual è la differenza tra `git fetch` e `git pull`?
> `git fetch` recupera le ultime modifiche dal repository remoto ma **non le applica** alla working directory locale; `git pull` è il processo che integra i cambiamenti del remote nel local ed è composto da due step: **fetch** e **merge**. Dopo un fetch le modifiche sono visibili in `origin/main` ma il `main` locale non è cambiato; dopo un pull il `main` locale è aggiornato.

> [!question] Domanda tipica d'esame
> *(a risposta multipla)* Quale operazione invia al repository remoto i commit creati in locale?
> a) pull; b) fetch; c) push; d) merge.
> Risposta: **c**. Il push è l'upload dei commit locali; pull e fetch scaricano dal remoto, merge unisce due branch.
## Primi passi: setup e GitHub Classroom
Prima di poter lavorare, servono alcuni step preliminari:
- installare **Git** (solo su Windows, da [gitforwindows.org](https://gitforwindows.org/), come indicato dalla slide; *(extra, non da slide)* su Linux/macOS è spesso già presente o disponibile dal gestore pacchetti);
- installare **VS Code** e, su Windows, configurare un terminale bash al suo interno;
- creare un account su [GitHub](https://github.com/);
- configurare Git in VS Code.

> [!info] Configurazione minima di Git *(extra, non da slide)*
> Ogni commit registra autore e email: prima del primo commit vanno impostati una sola volta a livello globale.
> ```bash
> git config --global user.name "Nome Cognome"
> git config --global user.email "email@esempio.it"
> ```

Il progetto d'esame viene assegnato tramite **GitHub Classroom**: si accetta l'assegnazione (*"Accept this assignment"*) tramite un link fornito dal docente, e GitHub crea automaticamente un repository privato dedicato dentro l'organizzazione del corso (es. `stud-pw-2025`), già inizializzato con un primo commit (`Initial commit`, autore `github-classroom[bot]`) contenente `README.md` e `hello.html`. A quel punto si **clona** il repository sulla propria macchina per iniziare a lavorare in locale.

> [!info] Primo esercizio: «Git 101» (slide PW02, pp. 13-17)
> - Si usa il link dell'esercizio (`classroom.github.com/a/...`) e la pagina `github.com/settings/organizations`, dove va accettato l'invito all'organizzazione del corso.
> - La pagina di GitHub Classroom «Accept the assignment — Git 101» avvisa che, accettando, si ottiene accesso al repository `git-101-<utente>` nell'organizzazione `stud-pw-2025`; si conferma con il pulsante «Accept this assignment».
> - La pagina successiva («You're ready to go!») conferma che il repository è stato creato e indica la **scadenza** dell'assegnazione (nella slide: 15 marzo 2025, 17:00 UTC).
> - Il repository è **privato** e contiene `README.md` (titolo «Progetto PW000») e `hello.html`, con il solo commit `Initial commit`.
> - Il menu «Code» propone tre modi per clonare: **HTTPS**, **SSH** e **GitHub CLI**. Scegliendo SSH senza chiavi pubbliche sul proprio account compare l'avviso «You don't have any public SSH keys in your GitHub account. You can add a new public key, or try cloning this repository via HTTPS» e il suggerimento di usare una chiave SSH protetta da password; l'URL SSH ha la forma `git@github.com:<organizzazione>/git-101-<utente>`.
> - Le pp. 16-17 mostrano l'organizzazione `stud-pw-2024`, mentre le pp. 14-15 mostrano `stud-pw-2025`. *(extra, non da slide: probabilmente le schermate provengono da anni diversi.)*

> [!example] Clonare il repository dell'assegnazione *(extra: il comando esatto non è mostrato nelle slide, solo l'interfaccia grafica di GitHub con le opzioni HTTPS/SSH/GitHub CLI)*
> ```bash
> git clone https://github.com/stud-pw-2025/nome-repository.git
> ```
> Da quel momento il repository locale è collegato al remoto `origin`, e si può lavorare con il normale ciclo add → commit → push.
## Escludere file dal versionamento: .gitignore
*(extra, non da slide)* Non tutti i file di un progetto vanno versionati: dipendenze installate automaticamente (`node_modules/`, vedi [[08 - Node.js e npm]]), file generati, credenziali o configurazioni locali dell'editor non devono finire nel repository, sia perché sono pesanti e ricostruibili sia perché possono contenere informazioni sensibili. Il file **`.gitignore`**, alla radice del repository, elenca i pattern di file e cartelle che Git deve ignorare: non compariranno né in `git status` né potranno essere aggiunti per errore con `git add`.

> [!example] .gitignore per un progetto Node.js/Express
> ```gitignore
> node_modules/
> .env
> *.log
> ```

> [!warning] Trabocchetto
> `.gitignore` impedisce di **aggiungere** file nuovi che rispettano i pattern, ma non rimuove dal repository un file che è già stato committato in precedenza: se un file è finito per errore nel repository prima di essere ignorato, va rimosso esplicitamente dal tracking (es. `git rm --cached <file>`).
## I branch: linee di sviluppo indipendenti
> [!quote] Definizione — Branch
> Linea di sviluppo indipendente all'interno di un repository: ogni branch rappresenta un'istantanea dei file del progetto in un determinato momento, e permette di evolverla separatamente dalle altre linee di sviluppo.

Il branch di partenza, creato automaticamente, si chiama in genere **`main`**: rappresenta il flusso principale di sviluppo del progetto. È pratica comune creare un **nuovo branch per ogni compito** (una funzionalità, una correzione), lavorarci in isolamento e poi riportare il risultato su `main`.
Un nuovo branch si crea con:
```bash
git branch <nome>
```
Questo comando crea il branch ma **non** ci si sposta sopra automaticamente: il branch nuovo punta allo stesso commit da cui è stato creato. Per spostarsi effettivamente su un branch (o su un commit specifico) si usa:
```bash
git checkout <nome/id>
```
`git checkout` imposta la cartella di lavoro sul branch o sul commit indicato. **HEAD** è il puntatore al branch (o al commit) corrente, cioè quello su cui ci si trova in questo momento *(extra, non da slide: è ciò che dice a Git "che cosa sto vedendo adesso nel working tree")*.
Secondo la slide, per cambiare branch le modifiche correnti devono essere state "salvate" in uno dei due modi seguenti:
- con un **commit** vero e proprio (`git commit ...`);
- oppure mettendole da parte temporaneamente con **`git stash`**, che salva lo stato corrente del working tree e riporta i file all'ultimo commit senza crearne uno nuovo; lo stato salvato si recupera poi con `git stash pop`.

> [!warning] Precisazione *(extra, non da slide, provata con git 2.56.1)*
> - La regola della slide è prudente ma non è assoluta: con una modifica non committata a un file, `git checkout <altro-branch>` **riesce** e porta con sé la modifica, a meno che quel file sia diverso anche tra i due branch; in quel caso Git rifiuta il cambio con l'errore `Your local changes to the following files would be overwritten by checkout`. Commit o stash sono quindi il modo sicuro per non perdere né mescolare modifiche.
> - `git stash` salva solo i file **tracciati**: con un file nuovo non tracciato risponde `No local changes to save`. Per includere anche i non tracciati serve `git stash -u`.

> [!warning] Trabocchetto — nome del comando
> Le slide del corso indicano il comando di recupero come "`git pop`", ma il comando corretto di Git è **`git stash pop`** (che ripristina l'ultimo stato salvato con `git stash` e lo rimuove dalla pila degli stash). Attenzione a questa imprecisione se si studia solo dalle slide.

> [!example] Creare e cambiare branch
> ```bash
> git branch nuova-funzionalita   # crea il branch
> git checkout nuova-funzionalita # ci si sposta sopra (HEAD ora punta qui)
>
> # per salvare lo stato corrente senza committare:
> git stash
> git checkout main
> git checkout nuova-funzionalita
> git stash pop                   # recupera le modifiche salvate
> ```

> [!info] Gitflow Workflow
> La slide mostra un diagramma con cinque corsie di branch: `main`, `hotfix`, `release`, `develop` e `feature`; i commit di `main` sono marcati con i tag di versione `version0.1`, `version1.0` e `version1.1`. *(extra, non da slide: in questo schema `main` contiene le versioni rilasciate, `hotfix` le correzioni urgenti, `release` la preparazione di una nuova versione, `develop` è la linea di integrazione e `feature` ospita le singole funzionalità in sviluppo.)* *(extra, non da slide)* Per il progetto d'esame questo schema è più complesso del necessario: basta `main` più un branch per ogni funzionalità (vedi [[#Git e GitHub nel progetto d'esame]]).

> [!question] Domanda tipica d'esame
> A che cosa serve un branch e come si crea e ci si sposta su un nuovo branch?
> Un branch è una linea di sviluppo indipendente all'interno di un repository: ogni branch rappresenta un'istantanea dei file del progetto in un determinato momento. `main` è il flusso principale di sviluppo ed è pratica comune creare un nuovo branch per ogni compito. `git branch <nome>` crea il branch senza spostarsi; `git checkout <nome/id>` imposta la cartella di lavoro su un branch o commit, e **HEAD** punta al branch/commit corrente.

> [!question] Domanda tipica d'esame
> *(a risposta multipla)* Quale comando salva lo stato corrente del working tree e torna al commit precedente senza creare un commit?
> a) `git branch`; b) `git stash`; c) `git merge`; d) `git pop`.
> Risposta: **b**. Lo stato salvato si recupera con `git stash pop` (le slide scrivono «git pop», ma il comando esistente è `git stash pop`).
## Unire i branch: git merge
`git merge` unisce le modifiche di due branch. Il risultato dipende da come si sono evolute le due linee di sviluppo nel frattempo.
Se il branch di destinazione (es. `main`) non ha ricevuto nuovi commit da quando il branch da unire (es. `bugfix`) è stato creato, Git può semplicemente spostare in avanti il puntatore di `main` fino all'ultimo commit di `bugfix`: si chiama **fast forward**, e non crea un commit aggiuntivo perché non c'è nulla da combinare.
Se invece `main` ha ricevuto commit propri nel frattempo, le due storie sono divergenti: Git crea un **merge commit**, un commit speciale con due genitori (l'ultimo commit di ciascun branch) che li ricongiunge in un unico punto della cronologia.

> [!example] Fast forward vs merge commit
> ```bash
> git checkout main
> git merge bugfix
> ```
> - **Fast forward**: `main` era fermo, `bugfix` è andato avanti → `main` viene semplicemente spostato in avanti fino all'ultimo commit di `bugfix`.
> - **Merge commit**: `main` è andato avanti anche lui → Git crea un nuovo commit che unisce le due storie, con due commit genitori.
>
> Nelle slide: nel caso fast forward `main` è fermo su `B` e `bugfix` prosegue con `X` e `Y` (A-B-X-Y); nel caso merge commit `main` prosegue con `C` e `D` mentre `bugfix` ha `X` e `Y`, e il merge crea il commit `E` che ha come genitori `D` e `Y`.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra fast forward e merge commit?
> Nel **fast forward** il branch di destinazione (`main`) non ha ricevuto nuovi commit dopo la creazione del branch da unire: Git sposta in avanti il puntatore di `main` fino all'ultimo commit di `bugfix` e non crea nessun commit. Nel **merge commit** `main` ha commit propri, le storie sono divergenti e Git crea un commit speciale con **due genitori** (provato: `git cat-file -p HEAD` mostra due righe `parent`) che le ricongiunge.

> [!question] Domanda tipica d'esame
> *(a risposta multipla)* `main` ha i commit A-B-C-D e il branch `bugfix`, creato da B, ha i commit X-Y. Dopo `git checkout main` e `git merge bugfix` che cosa si ottiene?
> a) un fast forward con `main` che punta a Y; b) un merge commit E con genitori D e Y; c) un errore, perché i branch sono divergenti; d) la cancellazione del branch `bugfix`.
> Risposta: **b**. Le storie sono divergenti: serve un merge commit; se non ci sono conflitti, l'unione avviene automaticamente. Il fast forward sarebbe possibile solo se `main` fosse fermo a B.
## Conflitti di merge
*(extra, non da slide: le slide mostrano solo il caso senza conflitti — "se non è presente alcun conflitto, il commit verrà unito automaticamente" — senza spiegare cosa succede quando un conflitto c'è.)*
Un **conflitto** si verifica quando due branch modificano **le stesse righe dello stesso file** in modo diverso: Git non può decidere da solo quale versione tenere, quindi interrompe il merge e chiede di risolvere il conflitto a mano. Il file coinvolto viene marcato con dei separatori:
```text
<<<<<<< HEAD
versione presente sul branch corrente
=======
versione presente sul branch che si sta unendo
>>>>>>> nome-branch
```
Per risolvere il conflitto si modifica il file scegliendo (o combinando) il contenuto corretto, si rimuovono i marcatori `<<<<<<<`/`=======`/`>>>>>>>`, e si conclude il merge con un normale `git add` + `git commit`.

> [!warning] Trabocchetto
> Un conflitto **non** è un errore che blocca il progetto: è Git che segnala di non poter decidere da solo. Va risolto a mano, poi si prosegue normalmente con add e commit; finché non si risolve, il merge resta "a metà" e Git lo ricorda nello stato del repository (`git status`).
## Branch remoti e origin/main
Anche i branch hanno una loro versione remota: **`origin/main`** indica lo stato del branch `main` così come risulta sul repository remoto, ed è distinto dal proprio `main` locale, che può essere più avanti, più indietro o allineato.
Con `git pull` (fetch + merge) i commit presenti solo su `origin/main` vengono scaricati e uniti al `main` locale: se non ci sono conflitti, il merge (o il fast forward) avviene automaticamente. Con `git push` avviene il percorso inverso: i commit del `main` locale, assenti su `origin/main`, vengono caricati sul remoto, allineando i due puntatori.
Nelle slide: nel primo caso `origin/main` ha i commit A-B-X-Y e il `main` locale ha solo A-B; dopo il pull (fetch + merge) `main` e `origin/main` puntano entrambi a Y, un fast forward. Nel caso divergente `origin/main` ha A-B-X-Y e il `main` locale A-B-C-D: il merge crea il commit `E` che ha come genitori `Y` e `D`, e la slide riporta «If no conflict is present, commit will be merged automatically!». Dopo il merge il `main` locale (con `E`) è avanti rispetto a `origin/main` e un `git push` lo allinea al remoto *(extra, non da slide: i commit `C`, `D` ed `E` che vengono caricati sono una deduzione)*.

> [!example] Lavorare su un branch di feature e pubblicarlo *(extra, non da slide: `git push origin <branch>` e `git checkout -b` non compaiono nelle slide)*
> ```bash
> git checkout -b nuova-funzionalita   # crea il branch e ci si sposta sopra
> # ... lavoro, git add, git commit ...
> git push origin nuova-funzionalita   # pubblica il branch sul remoto
> ```
> *(extra: `-b` è una scorciatoia di `git checkout` che crea il branch e ci si sposta sopra in un solo comando, non mostrata esplicitamente nelle slide.)*

> [!question] Domanda tipica d'esame
> Che cos'è `origin/main` e in che cosa differisce dal `main` locale?
> `origin/main` indica lo stato del branch `main` sul repository remoto; il `main` locale può essere più avanti, più indietro o allineato. Con `pull` (fetch + merge) i commit presenti solo su `origin/main` vengono integrati nel `main` locale; con `push` i commit locali assenti su `origin/main` vengono caricati sul remoto.
## Git e GitHub nel progetto d'esame
*(extra, non da slide: sezione pratica che applica i concetti precedenti ai requisiti espliciti del progetto d'esame.)*
Il PDF d'esame valuta esplicitamente, sul fronte Git: **uso del repository, commit con messaggi chiari, storia di sviluppo leggibile, branch e gestione delle modifiche, README come documentazione del progetto**. Concretamente, per il progetto full stack consegnato su GitHub Classroom questo significa:
- Lavorare con **commit piccoli e frequenti** che corrispondano a passi di sviluppo reali (es. "creazione struttura HTML pagina catalogo", "aggiunta rotta GET /api/prodotti", "validazione lato server con status 400"), non un unico commit finale con tutto il progetto.
- Il **primo commit di lavoro** (dopo l'`Initial commit` creato da GitHub Classroom) deve essere quello del documento di specifiche, caricato **prima di iniziare a sviluppare**, con il messaggio letterale richiesto dal docente:
  ```bash
  git add specifiche/
  git commit -m "specifiche: primo documento di specifica del progetto"
  ```
- Il **`README.md`** del progetto (diverso dal `README.md` di ogni materia di questo repository di appunti) è la documentazione del progetto stesso: titolo e descrizione, istruzioni di installazione (`npm install`), comando per avviare backend e frontend, elenco delle funzionalità implementate ed extra, e note sull'uso di eventuali strumenti di AI.
- I **branch** possono essere usati per isolare una funzionalità in sviluppo (es. `git checkout -b autenticazione`) e unirla a `main` con `git merge` una volta completata e testata; anche solo lavorare in modo ordinato su `main` con commit atomici soddisfa il requisito, ma i branch aiutano a tenere `main` sempre in uno stato funzionante.

> [!info] Cosa mostrare con git log all'esame
> Il docente chiede esplicitamente di mostrare la **storia Git** su GitHub o con `git log`. Il comando più utile per farlo in modo leggibile è:
> ```bash
> git log --oneline --graph --decorate
> ```
> che mostra una riga per commit, l'eventuale struttura dei branch e dove puntano `HEAD`, `main` e i branch remoti: è la prova visiva che il progetto è stato sviluppato per fasi successive e non scritto tutto insieme all'ultimo momento.

> [!question] Domanda tipica d'esame
> Perché un repository con un solo commit finale, anche se il codice è corretto, viene penalizzato?
> Perché uno dei criteri di valutazione esplicito è la **storia di sviluppo leggibile**: un solo commit non permette di verificare come il progetto è stato costruito, non mostra l'uso reale del controllo di versione e nasconde il processo che il docente vuole invece vedere (specifiche prima dello sviluppo, poi le fasi di implementazione).
## Riferimenti
- `PW02-GIT.pdf` ("GIT 101"): Version Control e problema dell'overwriting (pp. 2-4), Git e concetti di repository/working tree/staging area (pp. 5-6), basic workflow e commit (pp. 7-8), repository remoti, push e pull/fetch/merge (pp. 9-11), step preliminari e GitHub Classroom (pp. 12-17).
- `PW04-2-GIT-2.pdf` ("GIT 102"): branch, main branch e `git branch`/`git checkout` (pp. 2-5), Gitflow Workflow (p. 6), `git merge` fast forward e merge commit (pp. 7-9), branch remoti e `origin/main` (pp. 10-11).
