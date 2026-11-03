---
tags:
  - intelligenza-artificiale
  - agenti
slide:
  - "002_Agents_v26_27_v1.0.pdf"
---
# Agenti intelligenti
Lezione 2 (07/10/2026): cos'è un agente, quando è razionale, come si descrivono problema e ambiente (PEAS), come si simula l'ambiente e quali tipi di agente esistono, dal riflesso semplice all'agente che apprende. Corrisponde al capitolo 2 di AIMA (Russell, Norvig), da rileggere per intero. Slide 002_Agents, pp. 1-63: pp. 2-13 agenti e razionalità, pp. 14-19 PEAS, pp. 20-31 ambienti, pp. 32-35 simulatore, pp. 36-52 programma e tipi di agente, pp. 53-59 rappresentazioni, pp. 60-63 desiderata ed esercizi (questi ultimi dalle slide, non visti a lezione).
## L'IA e gli agenti
L'IA si occupa di **osservare e comprendere** le attività legate al comportamento intelligente e di **riprodurne logiche e funzionalità** in modo accurato. Non è la semplice automazione di un problema complesso: bisogna capire le astrazioni dietro un comportamento intelligente per poterlo trasformare in algoritmo.

Il sistema software che interiorizza un comportamento e agisce non si chiama "un'intelligenza artificiale" ma **agente**.

> [!info] Differenza con l'automazione (dalle slide)
> Le slide (p. 2) insistono sull'osservazione che la differenza sta proprio nel confronto con l'**automazione** usata per risolvere problemi complessi: non basta automatizzare, occorre catturare le logiche del comportamento intelligente.
## Agente e ambiente
> [!quote] Agente
> Un **agente** è un sistema che **percepisce** l'ambiente attraverso i **sensori** e **agisce** su di esso attraverso gli **attuatori** (o effettori).

A differenza di un sistema operativo, di un DBMS o di una visita di un grafo, che vivono dentro il mondo del calcolatore, un agente non può pensare le sue azioni come indipendenti dall'esterno: è immerso in un **ambiente che cambia continuamente**, e non si può progettarlo senza capire l'ambiente.

> [!example] Google come agente
> L'ambiente di un motore di ricerca è il **web**, cioè il sistema distribuito di risorse e soprattutto di dati. Le sue azioni (leggere i documenti, indicizzarli, restituirli all'utente) agiscono su quell'ambiente: è un **agente situato**.

La visione "moderna" degli agenti (Russell e Norvig, dal 1995):
- sono **situati**: ricevono percezioni da un ambiente e agiscono su di esso;
- hanno **capacità di interazione sociale**: comunicano, collaborano, si difendono da altri agenti (una collaborazione può degenerare in uno schema **avversario**);
- hanno **credenze, obiettivi, intenzioni**: oltre agli scopi, formulano ipotesi su cosa è meglio fare e su come evolverà il mondo;
- hanno un **corpo** (risorse e vincoli fisici) e **provano emozioni**.

> [!info] Credenze e conoscenze
> Una **credenza** è un'aspettativa su come il mondo sarà tra poco, non una conoscenza certa. Un'auto a guida autonoma che vede un'auto parcheggiata *crede* che non uscirà dal parcheggio senza mettere la freccia.

> [!info] Le emozioni (domanda a lezione)
> Le emozioni sono **stati interni** che si possono esibire o nascondere e che predispongono positivamente o negativamente verso qualcosa, indipendentemente da ciò di cui si parla (la paura dei serpenti nata da un trauma). Nascono dall'interazione tra percezioni, memoria e stato interno, e influenzano le decisioni: chi è in preda alla paura è meno razionale. Gli LLM riconoscono le emozioni e sanno comportarsi come se le provassero: non è solo un modello per *descriverle*, ma una **funzione di reazione** che decide in modo emotivamente sensibile, per rendere naturale l'interazione con le persone.
### Percezioni e azioni
- La **percezione** è il processo con cui l'agente riceve un input dai sensori. Di solito non è isolata: conta la **sequenza di percezioni** (*sequenza percettiva*), che per le slide (p. 6) è la **storia completa** delle percezioni ricevute fino a quel momento e dice per esempio qualcosa sugli spostamenti di una parte dell'ambiente.
- L'**azione** è in genere **discreta**: si sceglie tra un insieme di azioni possibili, eventualmente parametrizzate.
- La scelta dipende **solo dallo stato interno e dalle percezioni**: l'agente non accede ad altro dell'ambiente. Un LLM che non attiva il recupero di informazioni dal web può non sapere le notizie degli ultimi giorni.

> [!quote] Funzione agente
> La **funzione agente** è la funzione matematica che associa a ogni **sequenza di percezioni** (insieme a ciò che l'agente ha interiorizzato) un'**azione**:
> $$f: \mathcal{P}^* \to \mathcal{A}$$
> Il **programma agente** (o *agente software*) è la sua implementazione concreta su un'architettura.

> [!warning] Differenza con le slide
> Le slide (p. 6) dicono che l'azione dipende **esclusivamente** dalla sequenza delle percezioni ricevute; a lezione si è precisato che conta anche ciò che l'agente ha interiorizzato (stato interno, memoria). Le due formulazioni sono compatibili, perché lo stato interno è funzione della sequenza percettiva passata.
## Razionalità
Fare "la cosa giusta" significa che la sequenza di azioni tende a uno **scopo**. Per sapere se lo scopo è raggiunto serve una **misura di prestazione**:
- è **esterna** all'agente e **oggettiva**: se l'agente scegliesse da sé come valutarsi sarebbe sempre bravissimo, come uno studente che si fa l'esame da solo;
- la stabilisce il **progettista**, ed è specifica del task: giocare a scacchi e guidare nel traffico cittadino si misurano in modi diversi.

> [!example] Sentiment analysis
> Un sistema legge i commenti a un post (X, Instagram, TikTok) e li classifica come **positivi**, **negativi** o **neutri**. Per valutarlo si usa un insieme di post annotati a mano da più persone che concordano sull'etichetta:
> - l'**accuracy** è la frazione di casi in cui il giudizio dell'agente coincide con quello umano;
> - l'**error rate** è il complemento, $1 - \text{accuracy}$;
> - esistono anche metriche **per classe** (positivo, negativo, neutro): *recall*, *precision* e *F-measure* (dalle slide, p. 9), che dicono quanto bene il sistema tratta ciascuna classe. Si vedranno più avanti.

> [!quote] Agente razionale
> Per ogni possibile sequenza di percezioni, un agente razionale sceglie l'azione che **massimizza il valore atteso** della misura di prestazione, date le percezioni ricevute e la conoscenza che possiede.
>
> La razionalità è relativa a quattro elementi (dalle slide, p. 10): la **misura di prestazione**, la **conoscenza pregressa** dell'ambiente, le **percezioni** presenti e passate, le **capacità** dell'agente.

Essere razionali **non** significa fare sempre bene: si può sbagliare, ma scegliendo comunque l'azione con il miglior valore atteso. Chi gira in auto in una città che non conosce è razionale se, pur senza fare il percorso più breve, non commette errori marcati (andare a nord invece che a sud).
- **Razionalità ≠ omniscienza.** Spesso l'informazione è parziale: il medico non ha tutte le analisi possibili e deve diagnosticare con pochi sintomi e referti. Un agente razionale può anche **raccogliere informazioni** prima di decidere (accendere la luce in una stanza buia) o astenersi dal rispondere.
- **Razionalità ≠ onnipotenza.** Le capacità dell'agente sono limitate: se l'azione ottima è sollevare un peso troppo grande, l'agente razionale **sa fermarsi** prima di danneggiarsi.
- **Apprendimento.** Stando a lungo in un ambiente, l'agente accumula esperienza e modifica le sue azioni: apprendere significa usare bene il passato per migliorare le azioni future (il sistema di sentiment analysis impara quali parole ed espressioni una comunità usa per esprimersi positivamente o negativamente).
- **Autonomia** (dalle slide, p. 13: un agente è autonomo nella misura in cui il suo comportamento dipende dalla sua esperienza del mondo e delle operazioni richieste). Un agente costruito solo con regole `if/then` scritte dal progettista non usa conoscenza propria: è poco flessibile e non si adatta quando l'ambiente cambia. Si vogliono agenti razionali **autonomi**, il cui comportamento dipende dalla loro esperienza.
## Formulazione PEAS
Per descrivere un problema (e quindi l'agente che lo risolve) si usa il template **PEAS**: **P**erformance, **E**nvironment, **A**ctuators, **S**ensors.

> [!quote] Agente come soluzione (dalle slide, p. 15)
> Definire un problema $P$ per un agente significa caratterizzare l'**ambiente operativo** in cui opera; progettare l'agente è trovare una soluzione per $P$: agente razionale = soluzione.

> [!quote] Agente come soluzione
> Un agente razionale è una **soluzione** per un problema $P$ se, per diverse **istanze** di $P$, produce una sequenza di azioni che lo risolve. Il taxi automatico risolve il problema "porta il cliente a destinazione" per qualsiasi destinazione: il problema ha sempre la stessa struttura.

| Problema | Performance | Environment | Actuators | Sensors |
|---|---|---|---|---|
| ChatGPT (LLM) | rispondere in modo naturale, efficace, preciso e con tempi "umani" a domande aperte | i testi in ingresso (prompt) e la lingua in cui sono scritti | emissione di parole in sequenza fino alla fine della risposta | lettura del prompt; prima ancora, i testi osservati nel pre-addestramento |
| Taxi automatico | arrivare a destinazione in modo sicuro, veloce, ligio alla legge, confortevole, con minimo consumo di benzina e profitti massimi | strada, altri veicoli, pedoni, clienti | sterzo, acceleratore, freno, frecce, clacson, schermo di interfaccia o sintesi vocale | telecamere, sensori a infrarossi e sonar, tachimetro, GPS, contachilometri, accelerometro, sensori sullo stato del motore, tastiera o microfono |
| Diagnosi medica | diagnosi corretta, cura del paziente | pazienti, ospedale | domande, suggerimenti di test, diagnosi | sintomi, test clinici, risposte del paziente |
| Robot "selezionatore" | % di parti classificate correttamente | nastro trasportatore | raccogliere le parti e metterle nei cestini | immagini (pixel di varia intensità) |
| Giocatore di calcio | fare più goal dell'avversario | altri giocatori, campo di calcio, porte | dare calci al pallone, correre | posizione di pallone, altri giocatori e porte |
| Bibliotecario | da completare (esercizio) | da completare | da completare | da completare |
| Google Assistant / Alexa | da completare (esercizio) | da completare | da completare | da completare |
| Information broker (motore di ricerca) | suggerimenti utili e rilevanti, tempo di risposta, completamento dell'interrogazione | il web e i suoi documenti, l'utente | accedere alla rete e ai documenti, comunicare la risposta | "lettura" dei documenti e della query, localizzazione dell'utente |

> [!info] Gli LLM come "pappagalli stocastici"
> L'unica azione di un LLM è **scegliere la parola successiva**, fino al punto finale. Per questo qualcuno li chiama *pappagalli stocastici*; ma se nel parlare dice cose interessanti, una "macchina che parla" diventa molto utile.

La prestazione non è solo **ammissibilità** della soluzione (arrivare a destinazione): conta la sua **qualità**, sia computazionale (memoria, tempo, numero di passi) sia non computazionale (il comfort del passeggero può far preferire una soluzione più lenta).
## Proprietà dell'ambiente
Le caratteristiche dell'ambiente cambiano il problema. Le dimensioni principali:
- **Completamente vs parzialmente osservabile**: in una stanza illuminata vedo tutto; in un appartamento sconosciuto, o in casa mia al buio, vedo solo una parte. Per le slide (pp. 21-22) in un ambiente **completamente osservabile** l'apparato percettivo dà una conoscenza completa dell'ambiente (o almeno di tutto ciò che serve a decidere), quindi **non serve mantenere uno stato del mondo**; in uno **parzialmente osservabile** i sensori hanno limiti o inaccuratezze. Esempi delle slide: completamente osservabili scacchi, Go, parole crociate (con punto interrogativo); parzialmente osservabili labirinto, interpretazione linguistica, guida autonoma, web search, dialogo con una IA generativa (ChatGPT).
- **Agente singolo vs multi-agente**: alcuni problemi si risolvono con più agenti che lavorano su porzioni diverse dei dati, e le soluzioni parziali si **fondono a posteriori**, come nel *divide et impera* di alcuni algoritmi di ordinamento. Dalle slide (p. 23): bisogna distinguere agente e non agente, perché il mondo può cambiare anche per eventi e non solo per azioni di agenti; un ambiente multi-agente può essere **competitivo** (con comportamento randomizzato) o **cooperativo** (con comunicazione).
- **Deterministico, stocastico o non deterministico**:
	- **deterministico**: l'evoluzione segue regole fisse, prevedibili dall'agente. Negli scacchi non so quale mossa farà l'avversario, ma so che si muove dentro regole che non cambiano;
	- **stocastico**: l'evoluzione è incerta ma descrivibile con una **distribuzione di probabilità** (le ruote del robot slittano in una certa percentuale di casi; il pallone calciato finisce in una certa zona della porta);
	- **non deterministico**: manca anche il modello probabilistico. Non potendo quantificare i casi, si ragiona sul **caso peggiore** e si minimizza il rischio di sbagliare gravemente. Le slide (p. 24) lo definiscono come il caso in cui gli stati possibili non corrispondono a una specifica distribuzione di probabilità (per esempio sono equiprobabili) e fanno l'esempio della **traduzione automatica**; esempi di ambienti stocastici sono la guida e il tiro in porta.
- **Episodico vs sequenziale**: in un ambiente episodico ogni decisione è indipendente dalle precedenti (valutare una radiografia: la decisione vale per quel referto); in un ambiente sequenziale la decisione $i+1$ dipende dalla $i$-esima (una partita a scacchi si vince con l'intera sequenza di mosse). Dalle slide (p. 26): in un ambiente episodico l'esperienza è divisa in episodi atomici indipendenti e **non c'è bisogno di pianificare**; in uno sequenziale ogni decisione influenza le successive.
- **Statico vs dinamico**: un ambiente statico non cambia mentre l'agente decide (un gioco in cui solo il personaggio si muove); in uno dinamico cambia da solo, come i fantasmi di **Pac-Man**, e l'agente deve ricontrollare se la decisione presa è ancora valida (dalle slide, p. 27: ritardare una decisione equivale a non agire). Le slide aggiungono la categoria **semi-dinamico**: l'ambiente non cambia ma la valutazione dell'agente sì, come negli scacchi con timer.
- **Discreto vs continuo**: quattro direzioni di movimento sono discrete; problemi che dipendono esplicitamente dal tempo si descrivono con funzioni continue sui reali. Dalle slide (p. 28) la distinzione vale per lo stato (numero finito di stati o no), per il tempo, per le percezioni (per esempio i gradi di illuminazione) e per le azioni (con parametri); la guida del taxi ha stati e tempi continui.
- **Noto vs ignoto**: riguarda la conoscenza dell'agente sulle **regole** dell'ambiente, non l'osservabilità. Posso conoscere la pianta di un appartamento senza sapere se c'è qualcosa per terra (noto ma parzialmente osservabile); in un ambiente ignoto posso solo **esplorare**. Gli ambienti reali sono in genere (dalle slide, p. 29) parzialmente osservabili, stocastici, sequenziali, dinamici, continui, multi-agente e ignoti.

| Task | Osservabile | Agenti | Deterministico | Episodico | Statico | Discreto |
|---|---|---|---|---|---|---|
| Cruciverba | completo | singolo | deterministico | sequenziale | statico | discreto |
| Scacchi con orologio | completo | multi | deterministico | sequenziale | semi | discreto |
| Poker | parziale | multi | stocastico | sequenziale | statico | discreto |
| Backgammon | completo | multi | stocastico | sequenziale | statico | discreto |
| Guida di un taxi | parziale | multi | stocastico | sequenziale | dinamico | continuo |
| Diagnosi medica | parziale | singolo | stocastico | sequenziale | dinamico | continuo |
| Analisi di immagini | completo | singolo | deterministico | episodico | semi | continuo |
| Robot che raccoglie parti | parziale | singolo | stocastico | episodico | dinamico | continuo |
| Controllo di una raffineria | parziale | singolo | stocastico | sequenziale | dinamico | continuo |
| Tutor interattivo di inglese | parziale | multi | stocastico | sequenziale | dinamico | discreto |

> [!info] Tabella delle slide
> Nelle slide (p. 31) la tabella delle tipologie di ambiente è **vuota** tranne la riga del gioco del 15; la tabella qui sopra è quella ricostruita a lezione e dagli appunti, non copiata dalle slide.

> [!example] Esercizio proposto a lezione
> Completare la formulazione PEAS per il **bibliotecario** e per **Google Assistant / Alexa**, e classificare questi ambienti lungo le sei dimensioni (osservabile, deterministico/stocastico, episodico/sequenziale, statico/dinamico, discreto/continuo, mono/multi-agente): gioco del 15 (risolto a lezione: osservabile, deterministico, sequenziale, statico, discreto, mono-agente), briscola, scacchi, scacchi con timer, sudoku, guida autonoma, information broker, diagnostica per immagini, Alexa. Eventuali dubbi si discutono nella lezione successiva.
## L'ambiente come programma
Il corso non è teoria filosofica: si costruiscono **due programmi**, l'ambiente e l'agente. Il programma ambiente deve:
1. **generare gli stimoli** per gli agenti, cioè estrarre dallo stato del mondo ciò che ciascuno può percepire;
2. **raccogliere le azioni** decise dagli agenti (che sono autonomi);
3. **aggiornare il proprio stato** in conseguenza delle azioni (ed eventualmente attivare altri processi coinvolti nel cambiamento);
4. **valutare le prestazioni** degli agenti.

Ambiente e agenti sono **indipendenti**, come i **processi** di un sistema operativo: ognuno ha il proprio spazio di memoria e non vede quello degli altri. L'unico scambio sono i **messaggi**: l'ambiente manda la percezione, l'agente risponde con l'azione scelta. Va tenuto a mente anche quando si progettano le soluzioni.

```pseudo
\begin{algorithm}
\caption{Run-Eval-Environment(state, Update-Fn, agents, Performance-Fn)}
\begin{algorithmic}
\State $scores \gets$ vettore di dimensione $|agents|$, tutto a 0
\Repeat
	\For{$agent \in agents$}
		\State $Percept[agent] \gets$ \Call{Get-Percept}{$agent, state$}
	\EndFor
	\For{$agent \in agents$}
		\State $Action[agent] \gets$ \Call{Program[agent]}{$Percept[agent]$}
	\EndFor
	\State $state \gets$ \Call{Update-Fn}{$actions, agents, state$}
	\State $scores \gets$ \Call{Performance-Fn}{$scores, agents, state$}
\Until{\Call{Termination}{$state$}}
\Return $scores$
\end{algorithmic}
\end{algorithm}
```

Il simulatore restituisce un vettore di punteggi, uno per agente. A ogni ciclo calcola le percezioni di tutti gli agenti, invoca il programma di ciascuno con la sua percezione, raccoglie le azioni, aggiorna lo stato e i punteggi, e ricomincia. L'ambiente si può scrivere in qualsiasi linguaggio; all'esercitazione si vedono simulatori in Python.

> [!info] Simulatore in Prolog (dalle slide, p. 35, non visto a lezione)
> Le slide mostrano lo stesso ciclo per un **agente singolo in Prolog**: `start` inizializza agente e ambiente e chiama `run_env`, che a ogni passo acquisisce la percezione (`get_percept`), seleziona l'azione (`selectAct`), la attua (`update_env`), valuta la prestazione (`evaluatePerf`) e controlla la terminazione (`check_term`: obiettivo raggiunto, oppure stato non sicuro e partita persa, altrimenti passo successivo).
## Il programma agente
Per le slide (p. 37) **agente = architettura + programma**: il programma implementa la funzione agente $\mathcal{P}^* \to \mathcal{A}$. Lo scheletro di un programma agente riceve una percezione, aggiorna la memoria, sceglie l'azione e si ricorda di averla eseguita:

```pseudo
\begin{algorithm}
\caption{Skeleton-Agent(percept)}
\begin{algorithmic}
\State $memory \gets$ \Call{Update-Memory}{$memory, percept$}
\State $action \gets$ \Call{Choose-Best-Action}{$memory$}
\State $memory \gets$ \Call{Update-Memory}{$memory, action$}
\Return $action$
\end{algorithmic}
\end{algorithm}
```

La realizzazione più ingenua è l'**agente basato su tabella**: una tabella associa un'azione a ogni possibile sequenza di percezioni. Problemi:
1. negli scacchi servirebbe una riga per ogni configurazione e ogni sequenza: dimensioni ingestibili;
2. è difficile da costruire;
3. non c'è autonomia;
4. aggiornarla e apprendere è complesso (dalle slide, p. 40: la tabella associa un'azione a ogni possibile sequenza di percezioni).

> [!example] Tabella dell'aspirapolvere (dalle slide, p. 39)
> Nel mondo dell'aspirapolvere a due stanze la funzione agente si può tabulare (parzialmente) per sequenze di percezioni: $[A,\text{Clean}] \to \text{Right}$, $[A,\text{Dirty}] \to \text{Suck}$, $[B,\text{Clean}] \to \text{Left}$, $[B,\text{Dirty}] \to \text{Suck}$; per sequenze più lunghe, come $[A,\text{Clean}],[A,\text{Clean}] \to \text{Right}$, la tabella cresce senza limite. Lo stesso ambiente è formulato come problema di ricerca in [[03 - Risoluzione di problemi mediante ricerca#Problemi giocattolo#Il mondo dell'aspirapolvere]].
## Tipi di agente
In ordine di complessità crescente.
### Agente reattivo semplice
Sceglie l'azione in base alla **sola percezione corrente**, con regole **condizione-azione** (`if/then`), persistenti e statiche: interpreta la percezione, aggiorna lo stato, seleziona la regola che corrisponde e restituisce la sua azione.

> [!example] L'aspirapolvere
> Due stanze, $A$ e $B$, che possono essere pulite o sporche. Azioni: `Right`, `Left`, `Suck`. L'ambiente comunica all'agente dove si trova e se la stanza è sporca:
> - se la stanza è sporca → `Suck`;
> - se è pulita ed è in $A$ → `Right`; se è pulita ed è in $B$ → `Left`.

Il programma delle slide (p. 42) è: `stato ← Interpreta-Input(percezione)`, `regola ← Regola-Corrispondente(stato, regole)`, `azione ← regola.Azione()`, con `regole` persistente.
### Agente basato su modello
Mantiene uno **stato interno** che descrive il mondo anche nelle parti che non vede, usando un **modello**: come il mondo evolve indipendentemente dall'agente e quali effetti hanno le sue azioni. Con il modello può **prevedere** lo stato futuro e scegliere l'azione migliore. La conoscenza su come funziona il mondo forma una **base di conoscenza**.

> [!example] Il mondo del Wumpus
> Una griglia $4 \times 4$; il cavaliere parte dalla cella $(1,1)$ e deve trovare l'**oro**. Nelle celle ci sono **buche** (*pit*) e il **Wumpus**, l'antagonista. Le buche emettono una **brezza** (*breeze*) nelle celle adiacenti, il Wumpus un **puzzo** (*stench*). Il cavaliere deve dare un senso alle percezioni e trarne conseguenze: se sente una brezza in una cella, una buca può essere in una delle celle vicine non ancora visitate; se in una cella non c'è puzzo, il Wumpus non può essere in nessuna cella adiacente, quindi ci si può muovere lì in sicurezza. Nel corso il mondo del Wumpus si simula anche in Prolog.

> [!example] La mappa delle slide (p. 43)
> Nella figura delle slide, con coordinate (colonna, riga) e partenza in $(1,1)$: il Wumpus è in $(1,3)$, l'oro in $(2,3)$, le buche in $(3,1)$, $(3,3)$ e $(4,4)$. Puzzo nelle celle adiacenti al Wumpus (e nella cella dell'oro, che confina con esso), brezza nelle celle adiacenti alle buche. Il simulatore Prolog (p. 44, dalle slide, non visto a lezione) ha lo stesso ciclo del simulatore generale: acquisire la percezione, `update_KB` per aggiornare le credenze, `ask_KB` per scegliere l'azione, aggiornare l'ambiente, controllare la terminazione (vittoria se l'agente è sull'oro, sconfitta se è sulla cella del Wumpus). Vedi [[04 - Agenti basati sulla conoscenza]].

```pseudo
\begin{algorithm}
\caption{Agente-basato-su-modello(percezione)}
\begin{algorithmic}
\State \textbf{persistent:} $stato$ (descrizione dello stato corrente), $modello$ (conoscenza del mondo), $regole$ (regole condizione-azione), $azione$ (l'azione più recente)
\State $stato \gets$ \Call{Aggiorna-Stato}{$stato, azione, percezione, modello$}
\State $regola \gets$ \Call{Regola-Corrispondente}{$stato, regole$}
\State $azione \gets regola.\text{Azione}$
\Return $azione$
\end{algorithmic}
\end{algorithm}
```
### Agente con obiettivo
Oltre al modello ha un **obiettivo** (*goal*) che guida la scelta: a volte l'azione migliore dipende da cosa si vuole raggiungere (a un incrocio, da che parte girare dipende dalla destinazione). Deve **pianificare** una sequenza di azioni. È meno efficiente di un agente reattivo, ma più flessibile. Le slide (p. 3 e p. 61) chiamano questi agenti anche "basati su un modello del task". Gli obiettivi possono riguardare anche *come* si arriva alla soluzione: un taxi che vuole risparmiare benzina non accelera troppo.
### Agente con valutazione di utilità
Le slide (p. 3) li chiamano anche agenti **opportunistici**. Quando ci sono **obiettivi alternativi**, o soluzioni più o meno desiderabili, serve una **funzione di utilità** che associa a ogni stato un numero reale ("quanto sarò contento in quello stato"). Si possono generare più soluzioni e scegliere quella che massimizza l'utilità (o minimizza un costo): più strada pagata dal cliente del taxi, meno token consumati in una conversazione con un LLM.
- L'utilità è spesso la **combinazione di più criteri** semplici.
- Quando alcuni obiettivi sono più facili da raggiungere di altri, conta anche la **probabilità di successo**: si massimizza l'**utilità attesa**. Nella ricerca di soluzioni, l'utilità serve a preferire certe strade ad altre.
### Agente che apprende
Osserva le proprie prestazioni e modifica la propria conoscenza. Ha quattro componenti:
- l'**elemento esecutivo** (*performance element*): il programma agente visto finora, che percepisce e decide;
- l'**elemento critico** (*critic*): osserva il comportamento rispetto a uno standard di prestazione e dà un **feedback** (di rinforzo, o esempi di successo);
- la **componente di apprendimento** (*learning element*): in base al feedback propone **cambiamenti** all'elemento esecutivo, cioè modifica le regole e quindi il modello decisionale (può essere, ad esempio, una rete neurale);
- il **generatore di problemi**: suggerisce situazioni nuove da esplorare, cioè nuovi dati per l'apprendimento.

Se il feedback è negativo servono cambiamenti, se è positivo no. Più tentativi con buon feedback danno più fiducia nelle regole; il ciclo si ferma quando non servono più cambiamenti.
## Rappresentazioni dello stato
Ambienti e agenti si implementano con rappresentazioni di espressività crescente:
1. **atomiche**: stati senza struttura interna; bastano automi a stati finiti con transizioni semplici, eventualmente estesi con probabilità;
2. **fattorizzate**: lo stato è un insieme di variabili, cioè di dimensioni in uno **spazio vettoriale**;
3. **strutturate**: oggetti e relazioni, come nel modello relazionale o nelle espressioni ricorsive della logica, che formano grafi.

Le rappresentazioni vettoriali sono esse stesse oggetto di apprendimento delle reti neurali: nello spazio dei vettori parole simili hanno vettori vicini (*mela*, *arancia*, *banana* in un cluster, *Roma* e *Parigi* in un altro), e la loro similarità si misura con la **similarità del coseno**:
$$\text{sim}(A, B) = \cos\theta = \frac{A \cdot B}{\|A\|\,\|B\|}$$
### Desiderata ed esercizi (dalle slide, non visto a lezione)
- Slide 56-59: rappresentazione di pattern linguistici con il machine learning (*encoder-decoder* per il linguaggio naturale), semantica lessicale nello spazio dei vettori e **WordSpace**, cioè *embedding* semantici costruiti da corpora di dominio (esempio: i termini bancari vicini a "libro al portatore").
- Slide 60: i sistemi di IA sono complessi e il loro rilascio è costoso e ad alto impatto sui processi delle organizzazioni; le sfide principali sono **accuratezza** (prestazioni vicine a quelle degli esperti), **generalità** (portabilità a domini e task diversi), **sostenibilità** nel tempo (bassi costi di manutenzione ed evoluzione), **modularità** (componenti riusabili), **trasparenza** (perché il sistema decide in un certo modo), **scalabilità** (rispetto a dati e numero di utenti).
- Slide 62-63 ("AI making"): esercizi di formulazione di problemi (perché la formulazione del problema segue quella dell'obiettivo; stato iniziale, test obiettivo, operatori e costo del cammino per la colorazione di una mappa con quattro colori, per il ritorno al mare dalla giungla, per un problema di Analisi; il robot nel labirinto con diverse astrazioni: movimenti elementari, decisioni solo alle intersezioni, movimento fino al punto di svolta, e se serve tenere traccia dell'orientazione). Si ricollegano a [[03 - Risoluzione di problemi mediante ricerca#Problemi come ricerca nello spazio degli stati#Formulazione di un problema]].

> [!question] Domanda tipica d'esame
> Quali tipi di agente conosciamo (slide 61: riflessi semplici, regole statiche, modello del mondo, modello del task, utilità, che apprendono)? Descrivi la struttura di ciascuno, dall'agente reattivo semplice all'agente che apprende, e spiega cosa aggiunge ognuno rispetto al precedente.

> [!question] Domanda tipica d'esame
> Perché la nozione di agente è un buon obiettivo per il concetto generale di IA? Come si modella l'ambiente, e cosa sono stati, conoscenza, sensori, regole e scopi di un agente?
