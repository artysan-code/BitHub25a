---
tags:
  - intelligenza-artificiale
  - agenti
slide: []
---
# Agenti intelligenti
Lezione 1 (07/10/2026): cos'è un agente, quando è razionale, come si descrivono problema e ambiente (PEAS), come si simula l'ambiente e quali tipi di agente esistono, dal riflesso semplice all'agente che apprende. Corrisponde al capitolo 2 di AIMA (Russell, Norvig), da rileggere per intero.
## L'IA e gli agenti
L'IA si occupa di **osservare e comprendere** le attività legate al comportamento intelligente e di **riprodurne logiche e funzionalità** in modo accurato. Non è la semplice automazione di un problema complesso: bisogna capire le astrazioni dietro un comportamento intelligente per poterlo trasformare in algoritmo.

Il sistema software che interiorizza un comportamento e agisce non si chiama "un'intelligenza artificiale" ma **agente**.
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
- La **percezione** è il processo con cui l'agente riceve un input dai sensori. Di solito non è isolata: conta la **sequenza di percezioni**, che per esempio dice qualcosa sugli spostamenti di una parte dell'ambiente.
- L'**azione** è in genere **discreta**: si sceglie tra un insieme di azioni possibili, eventualmente parametrizzate.
- La scelta dipende **solo dallo stato interno e dalle percezioni**: l'agente non accede ad altro dell'ambiente. Un LLM che non attiva il recupero di informazioni dal web può non sapere le notizie degli ultimi giorni.

> [!quote] Funzione agente
> La **funzione agente** è la funzione matematica che associa a ogni **sequenza di percezioni** (insieme a ciò che l'agente ha interiorizzato) un'**azione**:
> $$f: \mathcal{P}^* \to \mathcal{A}$$
> Il **programma agente** è la sua implementazione concreta su un'architettura.
## Razionalità
Fare "la cosa giusta" significa che la sequenza di azioni tende a uno **scopo**. Per sapere se lo scopo è raggiunto serve una **misura di prestazione**:
- è **esterna** all'agente e **oggettiva**: se l'agente scegliesse da sé come valutarsi sarebbe sempre bravissimo, come uno studente che si fa l'esame da solo;
- la stabilisce il **progettista**, ed è specifica del task: giocare a scacchi e guidare nel traffico cittadino si misurano in modi diversi.

> [!example] Sentiment analysis
> Un sistema legge i commenti a un post (X, Instagram, TikTok) e li classifica come **positivi**, **negativi** o **neutri**. Per valutarlo si usa un insieme di post annotati a mano da più persone che concordano sull'etichetta:
> - l'**accuracy** è la frazione di casi in cui il giudizio dell'agente coincide con quello umano;
> - l'**error rate** è il complemento, $1 - \text{accuracy}$;
> - esistono anche metriche **per classe** (come la *recall*), che dicono quanto bene il sistema trova i positivi, i negativi e così via. Si vedranno più avanti.

> [!quote] Agente razionale
> Per ogni possibile sequenza di percezioni, un agente razionale sceglie l'azione che **massimizza il valore atteso** della misura di prestazione, date le percezioni ricevute e la conoscenza che possiede.

Essere razionali **non** significa fare sempre bene: si può sbagliare, ma scegliendo comunque l'azione con il miglior valore atteso. Chi gira in auto in una città che non conosce è razionale se, pur senza fare il percorso più breve, non commette errori marcati (andare a nord invece che a sud).
- **Razionalità ≠ omniscienza.** Spesso l'informazione è parziale: il medico non ha tutte le analisi possibili e deve diagnosticare con pochi sintomi e referti. Un agente razionale può anche **raccogliere informazioni** prima di decidere (accendere la luce in una stanza buia) o astenersi dal rispondere.
- **Razionalità ≠ onnipotenza.** Le capacità dell'agente sono limitate: se l'azione ottima è sollevare un peso troppo grande, l'agente razionale **sa fermarsi** prima di danneggiarsi.
- **Apprendimento.** Stando a lungo in un ambiente, l'agente accumula esperienza e modifica le sue azioni: apprendere significa usare bene il passato per migliorare le azioni future (il sistema di sentiment analysis impara quali parole ed espressioni una comunità usa per esprimersi positivamente o negativamente).
- **Autonomia.** Un agente costruito solo con regole `if/then` scritte dal progettista non usa conoscenza propria: è poco flessibile e non si adatta quando l'ambiente cambia. Si vogliono agenti razionali **autonomi**, il cui comportamento dipende dalla loro esperienza.
## Formulazione PEAS
Per descrivere un problema (e quindi l'agente che lo risolve) si usa il template **PEAS**: **P**erformance, **E**nvironment, **A**ctuators, **S**ensors.

> [!quote] Agente come soluzione
> Un agente razionale è una **soluzione** per un problema $P$ se, per diverse **istanze** di $P$, produce una sequenza di azioni che lo risolve. Il taxi automatico risolve il problema "porta il cliente a destinazione" per qualsiasi destinazione: il problema ha sempre la stessa struttura.

| Problema | Performance | Environment | Actuators | Sensors |
|---|---|---|---|---|
| ChatGPT (LLM) | rispondere in modo naturale, efficace, preciso e con tempi "umani" a domande aperte | i testi in ingresso (prompt) e la lingua in cui sono scritti | emissione di parole in sequenza fino alla fine della risposta | lettura del prompt; prima ancora, i testi osservati nel pre-addestramento |
| Taxi automatico | arrivare a destinazione in modo sicuro, veloce, confortevole | strada, altri veicoli, pedoni, cliente | sterzo, acceleratore, freno, sintesi vocale | telecamere, sensori a infrarossi, sonar, tachimetro, accelerometro, tastiera o microfono |
| Diagnosi medica | diagnosi corretta, cura del paziente | pazienti, ospedale | domande, suggerimenti di test, diagnosi | sintomi, test clinici, risposte del paziente |
| Robot "selezionatore" | % di parti classificate correttamente | nastro trasportatore | raccogliere le parti e metterle nei cestini | immagini (pixel di varia intensità) |
| Giocatore di calcio | fare più goal dell'avversario | altri giocatori, campo, porte | calciare il pallone, correre | posizione di pallone, giocatori e porte |
| Information broker (motore di ricerca) | suggerimenti utili e rilevanti, tempo di risposta, completamento dell'interrogazione | il web e i suoi documenti, l'utente | accedere alla rete e ai documenti, comunicare la risposta | "lettura" dei documenti e della query, localizzazione dell'utente |

> [!info] Gli LLM come "pappagalli stocastici"
> L'unica azione di un LLM è **scegliere la parola successiva**, fino al punto finale. Per questo qualcuno li chiama *pappagalli stocastici*; ma se nel parlare dice cose interessanti, una "macchina che parla" diventa molto utile.

La prestazione non è solo **ammissibilità** della soluzione (arrivare a destinazione): conta la sua **qualità**, sia computazionale (memoria, tempo, numero di passi) sia non computazionale (il comfort del passeggero può far preferire una soluzione più lenta).
## Proprietà dell'ambiente
Le caratteristiche dell'ambiente cambiano il problema. Le dimensioni principali:
- **Completamente vs parzialmente osservabile**: in una stanza illuminata vedo tutto; in un appartamento sconosciuto, o in casa mia al buio, vedo solo una parte.
- **Agente singolo vs multi-agente**: alcuni problemi si risolvono con più agenti che lavorano su porzioni diverse dei dati, e le soluzioni parziali si **fondono a posteriori**, come nel *divide et impera* di alcuni algoritmi di ordinamento.
- **Deterministico, stocastico o non deterministico**:
	- **deterministico**: l'evoluzione segue regole fisse, prevedibili dall'agente. Negli scacchi non so quale mossa farà l'avversario, ma so che si muove dentro regole che non cambiano;
	- **stocastico**: l'evoluzione è incerta ma descrivibile con una **distribuzione di probabilità** (le ruote del robot slittano in una certa percentuale di casi; il pallone calciato finisce in una certa zona della porta);
	- **non deterministico**: manca anche il modello probabilistico. Non potendo quantificare i casi, si ragiona sul **caso peggiore** e si minimizza il rischio di sbagliare gravemente.
- **Episodico vs sequenziale**: in un ambiente episodico ogni decisione è indipendente dalle precedenti (valutare una radiografia: la decisione vale per quel referto); in un ambiente sequenziale la decisione $i+1$ dipende dalla $i$-esima (una partita a scacchi si vince con l'intera sequenza di mosse).
- **Statico vs dinamico**: un ambiente statico non cambia mentre l'agente decide (un gioco in cui solo il personaggio si muove); in uno dinamico cambia da solo, come i fantasmi di **Pac-Man**, e l'agente deve ricontrollare se la decisione presa è ancora valida.
- **Discreto vs continuo**: quattro direzioni di movimento sono discrete; problemi che dipendono esplicitamente dal tempo si descrivono con funzioni continue sui reali.
- **Noto vs ignoto**: riguarda la conoscenza dell'agente sulle **regole** dell'ambiente, non l'osservabilità. Posso conoscere la pianta di un appartamento senza sapere se c'è qualcosa per terra (noto ma parzialmente osservabile); in un ambiente ignoto posso solo **esplorare**.

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
## Il programma agente
Lo scheletro di un programma agente riceve una percezione, aggiorna la memoria, sceglie l'azione e si ricorda di averla eseguita:

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
4. aggiornarla e apprendere è complesso.
## Tipi di agente
In ordine di complessità crescente.
### Agente reattivo semplice
Sceglie l'azione in base alla **sola percezione corrente**, con regole **condizione-azione** (`if/then`), persistenti e statiche: interpreta la percezione, aggiorna lo stato, seleziona la regola che corrisponde e restituisce la sua azione.

> [!example] L'aspirapolvere
> Due stanze, $A$ e $B$, che possono essere pulite o sporche. Azioni: `Right`, `Left`, `Suck`. L'ambiente comunica all'agente dove si trova e se la stanza è sporca:
> - se la stanza è sporca → `Suck`;
> - se è pulita ed è in $A$ → `Right`; se è pulita ed è in $B$ → `Left`.
### Agente basato su modello
Mantiene uno **stato interno** che descrive il mondo anche nelle parti che non vede, usando un **modello**: come il mondo evolve indipendentemente dall'agente e quali effetti hanno le sue azioni. Con il modello può **prevedere** lo stato futuro e scegliere l'azione migliore. La conoscenza su come funziona il mondo forma una **base di conoscenza**.

> [!example] Il mondo del Wumpus
> Una griglia $4 \times 4$; il cavaliere parte dalla cella $(1,1)$ e deve trovare l'**oro**. Nelle celle ci sono **buche** (*pit*) e il **Wumpus**, l'antagonista. Le buche emettono una **brezza** (*breeze*) nelle celle adiacenti, il Wumpus un **puzzo** (*stench*). Il cavaliere deve dare un senso alle percezioni e trarne conseguenze: se sente una brezza in una cella, una buca può essere in una delle celle vicine non ancora visitate; se in una cella non c'è puzzo, il Wumpus non può essere in nessuna cella adiacente, quindi ci si può muovere lì in sicurezza. Nel corso il mondo del Wumpus si simula anche in Prolog.

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
Oltre al modello ha un **obiettivo** (*goal*) che guida la scelta: a volte l'azione migliore dipende da cosa si vuole raggiungere (a un incrocio, da che parte girare dipende dalla destinazione). Deve **pianificare** una sequenza di azioni. È meno efficiente di un agente reattivo, ma più flessibile. Gli obiettivi possono riguardare anche *come* si arriva alla soluzione: un taxi che vuole risparmiare benzina non accelera troppo.
### Agente con valutazione di utilità
Quando ci sono **obiettivi alternativi**, o soluzioni più o meno desiderabili, serve una **funzione di utilità** che associa a ogni stato un numero reale ("quanto sarò contento in quello stato"). Si possono generare più soluzioni e scegliere quella che massimizza l'utilità (o minimizza un costo): più strada pagata dal cliente del taxi, meno token consumati in una conversazione con un LLM.
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

> [!question] Domanda tipica d'esame
> Quali tipi di agente conosciamo? Descrivi la struttura di ciascuno, dall'agente reattivo semplice all'agente che apprende, e spiega cosa aggiunge ognuno rispetto al precedente.

> [!question] Domanda tipica d'esame
> Perché la nozione di agente è un buon obiettivo per il concetto generale di IA? Come si modella l'ambiente, e cosa sono stati, conoscenza, sensori, regole e scopi di un agente?
