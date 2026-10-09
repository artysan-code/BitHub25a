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
Il programma del corso è nella sezione «Obiettivi del corso» qui sotto. Le note seguono le lezioni:
- [[01 - Presentazione del corso]]: il paradosso dei problemi senza una sola soluzione (la diagnosi medica), cosa c'è dietro una risposta (le decisioni critiche), le discipline che confluiscono nell'IA e i suoi ingredienti: agenti e ricerca, conoscenza e logica, modellazione dei dati, machine learning e linguaggio.
- [[02 - Agenti intelligenti]]: agente, ambiente e funzione agente, razionalità e misura di prestazione, formulazione PEAS, proprietà degli ambienti, l'ambiente come programma (simulatore), tipi di agente dal reattivo semplice all'agente che apprende, rappresentazioni atomiche, fattorizzate e strutturate (AIMA cap. 2).
## Materiale di riferimento
- **Slide** in `Materiale Didattico/Slide/`, per ora solo come storico: `000_Intro_2026_27_v1.0.pdf` (Lezione 0, pubblicata il 05/10/2026 ma con contenuti in parte dell'a.a. 2025-26) e `000_From_Intro_AI_Short_For_Lab_25_26_v1.0.pdf` (introduzione all'IA, a.a. 2025-26). Le slide aggiornate non sono ancora state condivise.
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
