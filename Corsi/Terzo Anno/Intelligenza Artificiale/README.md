---
tipo: corso
materia: Intelligenza Artificiale
codice: IA
anno: 3
semestre: "1"
cfu: 9
ssd: INF/01
docenti:
  - Roberto Basili
propedeuticita:
  - Programmazione dei Calcolatori con Laboratorio
---
# Intelligenza Artificiale
Corso del terzo anno sui fondamenti dell'IA: agenti razionali, ricerca, conoscenza, ragionamento logico, apprendimento automatico e linguaggio naturale.
## Modalità d'esame
Regole dell'a.a. 2026-27 come le ha spiegate il docente a lezione (05/10/2026). Le slide della Lezione 0 pubblicate finora sono in parte dell'anno precedente e non fanno fede.
- **Esercitazioni (assignment)**: circa un esercizio individuale a settimana, da sviluppare in pochi giorni con il supporto degli esercitatori. Circa ogni venti giorni una lezione è dedicata a discutere insieme le soluzioni. Si consegna sul portale degli esercizi del corso (in preparazione, con login personale):
	- il **prodotto** (ad es. un programma Python funzionante, o un modello logico del problema);
	- un **notebook** (Colab/Jupyter) che documenta lo sviluppo, comprese le interazioni con i modelli di IA usati. Chiedere all'IA la soluzione e consegnarla ("outsourcing") vale poco; progettarla insieme all'IA, documentandolo, conta come lavoro svolto.
	- Ogni esercitazione consegnata può essere oggetto di domanda all'orale.
- **Scritto**: obbligatorio **solo** per chi non ha consegnato l'**80%** degli esercizi assegnati. Due sezioni:
	- **test a risposta multipla** (8 domande in una ventina di minuti, circa 3 minuti a domanda) a rovescio, *stile Jeopardy*: data una risposta, si sceglie l'unica domanda di cui è la risposta;
	- **domanda aperta** (stile orale, circa 90 minuti) a scelta fra 2-3 proposte: domande di progettazione (ad es. di un agente) oppure la discussione di un argomento del programma e dei suoi legami con gli altri.
	- Secondo il docente la percentuale di promossi va dal 25-30% al 60-65%.
- **Orale**: obbligatorio per tutti (novità rispetto all'anno scorso), breve (5-10 minuti, di più nei casi complicati). Parte dagli esercizi consegnati e dall'interazione con l'IA documentata nel notebook. Il riferimento per definizioni e algoritmi è il **libro di testo**, non il modello di IA.
- **Agenda**:
	- esonero *midterm* sulla prima metà del programma, dopo circa un mese e mezzo (novembre);
	- secondo esonero a gennaio (verso il 16-20), lo stesso giorno del primo scritto finale per chi non ha fatto l'esonero.
- **Progetto facoltativo** (da soli o fino a 2-3 persone; in gruppo il docente è più esigente): si raccolgono e integrano i dati, si applicano uno o più approcci e se ne confrontano i risultati. Serve ad alzare il voto e, se ben fatto, può valere anche **3-6 crediti D** (a scelta). Esempi: sentiment analysis su Twitter/X, addestramento di modelli piccoli su task specifici.
- Il voto si decide insieme: il docente fa una proposta, che si può migliorare con il progetto.
## Programma e Appunti
Il programma del corso è nella sezione «Obiettivi del corso» qui sotto. Gli appunti sono organizzati per argomento: ogni nota raccoglie tutte le lezioni su quell'argomento, una sezione per lezione. Le lezioni sono il lunedì e il mercoledì; le esercitazioni del venerdì non sono contate.
1. [[01 - Presentazione del corso]]
	- Lezione 1 (05/10/2026): il paradosso dei problemi senza una sola soluzione (la diagnosi medica), cosa c'è dietro una risposta (le decisioni critiche), le discipline che confluiscono nell'IA e i suoi ingredienti: agenti e ricerca, conoscenza e logica, modellazione dei dati, machine learning e linguaggio.
2. [[02 - Agenti intelligenti]]
	- Lezione 2 (07/10/2026): agente, ambiente e funzione agente, razionalità e misura di prestazione, formulazione PEAS, proprietà degli ambienti, l'ambiente come programma (simulatore), tipi di agente dal reattivo semplice all'agente che apprende, rappresentazioni atomiche, fattorizzate e strutturate (AIMA cap. 2).
3. [[03 - Risoluzione di problemi mediante ricerca]]
	- Lezione 3 (12/10/2026), [[03 - Risoluzione di problemi mediante ricerca#Problemi come ricerca nello spazio degli stati|problemi come ricerca nello spazio degli stati]]: i cinque elementi della formulazione (stato iniziale, azioni, modello di transizione, test obiettivo, costo del cammino), problemi giocattolo (Romania, aspirapolvere, gioco dell'8, otto regine) e dimostrazione di teoremi con il modus ponens, ricerca ad albero, nodi e frontiera (FIFO, LIFO, coda con priorità), ricerca in ampiezza (AIMA cap. 3).
	- Lezione 4 (14/10/2026), [[03 - Risoluzione di problemi mediante ricerca#Ricerca non informata e ricerca euristica|ricerca non informata e ricerca euristica]]: completezza, ottimalità e complessità di una strategia, ricerca in ampiezza, a costo uniforme, in profondità, a profondità limitata e ad approfondimento iterativo, ricerca bidirezionale e tabella di confronto, stati ripetuti, funzioni euristiche, greedy best-first e A\*, euristiche del gioco dell'8 (AIMA cap. 3).
	- Lezione 5 (19/10/2026), [[03 - Risoluzione di problemi mediante ricerca#Algoritmo A* e funzioni euristiche|A\* e funzioni euristiche]]: A\* (esempio della Romania, completezza, euristiche ammissibili e consistenti, ottimalità, contorni, memoria), IDA\*, A\* a memoria limitata e beam search, dominanza e fattore di ramificazione effettivo, euristiche da problemi rilassati, massimo di euristiche, pattern database, apprendimento e combinazioni lineari (AIMA cap. 3).
	- Lezione 6 (21/10/2026), [[03 - Risoluzione di problemi mediante ricerca#Ricerca locale e ambienti non deterministici|ricerca locale e ambienti non deterministici]]: oltre la ricerca classica, completezza prima dell'ottimalità, ricerca locale e paesaggio degli stati, gradiente, hill climbing e otto regine, mosse laterali, varianti stocastiche e riavvio casuale, simulated annealing, beam search locale e riconoscimento del parlato, azioni non deterministiche e piani contingenti (AIMA cap. 4).
	- Lezione 7 (26/10/2026), [[03 - Risoluzione di problemi mediante ricerca#Ricerca AND-OR, stati credenza e ricerca online|ricerca AND-OR, stati credenza e ricerca online]]: piani contingenti e ricerca AND-OR, piani ciclici, ricerca senza osservazioni sugli stati credenza, osservabilità parziale, ricerca online, rapporto competitivo, ambienti esplorabili in sicurezza, agente online in profondità, LRTA\* (AIMA cap. 4).
4. [[04 - Agenti basati sulla conoscenza]]
	- Lezione 5 (19/10/2026), ultima parte, [[04 - Agenti basati sulla conoscenza#Dal linguaggio alla logica|dal linguaggio alla logica]]: traduzione di frasi italiane in formule logiche.
	- Lezione 8 (28/10/2026), [[04 - Agenti basati sulla conoscenza#Rappresentazione della conoscenza e agenti basati sulla conoscenza|rappresentazione della conoscenza]]: perché rappresentare la conoscenza, il mondo del Wumpus (brezza, puzza, celle sicure), logica per descrivere, dedurre, verificare la coerenza e spiegare, logica e machine learning, TELL e ASK e il programma KB-Agent, conseguenza logica, conoscenza dichiarativa, confronto con le basi di dati (chiusura ricorsiva, mondo chiuso), trasparenza epistemologica e atteggiamento intenzionale, interpretazione (AIMA cap. 7).
	- Lezione 9 (02/11/2026), [[04 - Agenti basati sulla conoscenza#Logiche, ontologie e logica proposizionale|logiche, ontologie e logica proposizionale]]: logica proposizionale e del primo ordine, ragionamento incerto, logiche epistemiche, modali, a tre valori, probabilistiche e fuzzy, ragionamento non monotono e default, ontologia, il mondo dei blocchi in Prolog, sintassi e semantica proposizionale, modelli e conseguenza logica nel Wumpus, validità e soddisfacibilità, model checking, deduzione e risoluzione (AIMA cap. 7).
## Materiale di riferimento
- **Slide** in `Materiale Didattico/Slide/`: `000_Intro_2026_27_v1.0.pdf` (Lezione 0, pubblicata il 05/10/2026 ma con contenuti in parte dell'a.a. 2025-26) e `000_From_Intro_AI_Short_For_Lab_25_26_v1.0.pdf` (introduzione all'IA, a.a. 2025-26). Le slide delle lezioni 2-6 del docente (la sua numerazione dei lucidi non coincide con quella delle lezioni negli appunti) sono state pubblicate sul sito. Ogni nota indica nel frontmatter (`slide`) i PDF usati e, nella riga di ogni lezione, l'intervallo di pagine:
	- `000_Intro_2026_27_v1.0.pdf` (Lezione 0): [[01 - Presentazione del corso]];
	- `002_Agents_v26_27_v1.0.pdf` (Lezione 2, *Agenti razionali*): [[02 - Agenti intelligenti]];
	- `0030_Search_26_27_v2.1.pdf` (Lezione 3, *Problem solving come ricerca*), `0031_InformedSearch_aa_26_27_v1.2.1.pdf` (Lezione 4, *Ricerca informata*) e `0032_AdvancedSearch_26_27_v1.5.pdf` (Lezione 5, *Local e on-line search*): lezioni 3-7 degli appunti, [[03 - Risoluzione di problemi mediante ricerca]];
	- `004_Knowldege_and_Logic_2026_27_v1.4.pdf` (Lezione 6, *Agenti logici*): lezioni 8-9 degli appunti, [[04 - Agenti basati sulla conoscenza]]. Sintassi e semantica della logica proposizionale, model checking e risoluzione non sono in questo PDF.
- **Sito del corso**: <http://sag.art.uniroma2.it/didattica/basili/IA_26_27/>, con avvisi, programma, testi e slide delle lezioni.
- **MS Teams**: team `2026_27_BASILI-8067806-INTELLIGENZA_ARTIFICIALE`, il canale per tutte le comunicazioni (link d'esame, esercizi, accettazione del voto). Bisogna anche registrarsi al corso su Delphi e rispondere al questionario iniziale.
- **Ricevimento**: il mercoledì dopo la lezione.
- **Email del docente**: `basili@info.uniroma2.it`. Il docente chiede di non scrivere all'indirizzo che compare su Teams.
- **Libro di testo**: S. Russell, P. Norvig, *Artificial Intelligence: A Modern Approach*, 4ª ed., 2022 ([sito AIMA](https://aima.cs.berkeley.edu/)); traduzione italiana Pearson in due volumi. Il docente consiglia l'edizione inglese. È il riferimento d'esame: il docente indicherà quali sezioni fanno parte del programma.
- **Altri testi**: a lezione il docente ha citato un testo di logica (se ne usano un paio di capitoli) e un testo di Stanford; i riferimenti precisi saranno sul sito.
- **Prerequisiti** (detti a lezione): Analisi, Algebra lineare, probabilità e statistica, Logica; Basi di Dati, soprattutto la modellazione; la programmazione logica (Prolog).
## Approccio del corso
Quanto detto dal docente nella lezione del 05/10/2026.
- **Il docente** viene dal trattamento automatico del linguaggio naturale (dottorato nei primi anni '90: riconoscimento del parlato, motori di ricerca).
- **Obiettivo**: non insegnare a *usare* l'IA (sanno farlo anche il poeta, l'educatore o il medico), ma **aprire i sistemi** e capire il flusso di dati, regole e conoscenze che porta a una risposta: è il quadro complessivo con cui uscire dalla triennale.
- **Percorso**: agenti razionali e ricerca, poi conoscenza e logica (con **Prolog** come strumento pratico; aver fatto bene Basi di Dati aiuta per la modellazione), poi machine learning presto ma in modo introduttivo (lo si approfondisce nei corsi di Machine Learning e Deep Learning) per arrivare ai Transformer, poi linguaggio e prompting. Argomenti avanzati: ricerca locale, ML e NLP, LLM e i loro meccanismi di codifica. L'introduzione "tradizionale" all'IA viene ripresa alla fine.
- **Frequenza**: il docente insiste sul seguire e lavorare durante il corso (lezioni interattive, workshop sugli esercizi circa ogni venti giorni, laboratorio episodico il venerdì pomeriggio); chi studia solo per prendere i crediti rischia di non imparare.
- **L'IA per studiare**: il docente non è contrario, ma studiare non significa farsi fare gli esercizi: significa discutere con il modello i punti difficili e risolverli pezzo per pezzo. Chiedere "scrivimi un programma che fa questo" e consegnare il risultato è **outsourcing**, non progettazione. L'interazione con il modello, documentata nel notebook dell'esercizio, è "il sale del lavoro" e dà una misura dell'impegno. Il riferimento per definizioni e algoritmi resta il **libro di testo**.
## Obiettivi del corso
- Introduzione all'AI
	- Scopi, Fenomeni e Processi Computazionali
	- Paradigmi e Funzionalità
	- Applicazione
- Fondamenti dell'AI
	- **Agenti Razionali**, Informazione e **Ricerca** per il *problem solving*
	- Il ruolo della **Conoscenza**: Modelli di Mondo, Modelli delle Task e Paradigmi
	- **Lingue ed Ia**, dal NLP al prompting
	- Problem Solving e Ragionamento: la **Logica per la Conoscenza** e la **Deduzione**
	- **Conoscenza e Apprendimento**: dall'incertezza al **Machine Learning**.
- Approfondimenti
	- Algoritmi di *Ricerca Online*: local search e random search
	- *Machine Learning*: **Example-driven Learning**, **Reti neurali** ed **LLM**
	- **Encoding** dei dati per l'**IA generativa**
	- **Natural Language Processing**: dati, modelli e task.
- Esercitazioni
	- Completamento e pratica della parte teorica
		- Prompting & Discussione dei progetti
		- Progettazione degli agenti
			- Agenti semplici
			- Algoritmi di ricerca euristica
		- Agenti che integrano Machine Learning e Problem-Solving
			- Apprendimento per la soluzione dei problemi di pianificazione
			- Classificazione dei Testi e Inferenza Testuale
			- On-going challenge: sentiment analysis da Twitter/X
		- Introduzione alle tecnologie più diffuse
			- Agent Design in Python
			- Machine Learning in Python, PyTorch
			- Prompt Engineering
## Corsi correlati
- Machine Learning (Gambosi)
- Deep Learning (RB)
- Information Retrieval (D. Croce)
- Natural Language Processing (F. M. Zanzotto)
- Knowledge Engineering (A. Stellato)
- AI and security (MT, RB)
