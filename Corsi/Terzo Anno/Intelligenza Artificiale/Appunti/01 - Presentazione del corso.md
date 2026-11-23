---
tags:
  - intelligenza-artificiale
  - introduzione
slide:
  - "000_Intro_2026_27_v1.0.pdf"
  - "000_From_Intro_AI_Short_For_Lab_25_26_v1.0.pdf"
---
# Presentazione del corso
Lezione 1 (05/10/2026; slide 000_Intro, pp. 1-19, in gran parte organizzative: vedi [[#Obiettivi e organizzazione del corso]]): che tipo di problemi affronta l'IA e quali sono i suoi ingredienti fondamentali (ricerca, conoscenza, dati, apprendimento, linguaggio).

> [!info] Fonti di questa nota
> Le sezioni da «Il paradosso dell'intelligenza» a «Le discipline che confluiscono nell'IA» vengono dalla lezione e non si trovano nelle slide. La sezione [[#Dalla slide «From Intro AI Short For Lab»]] viene invece da una slide dell'anno precedente (a.a. 2025/26, 44 pagine), non da una versione di quest'anno.
## Il paradosso dell'intelligenza
Oggi interagire in linguaggio naturale con un sistema sembra banale, ma non lo è: una macchina che capisce da pochi elementi di un problema *cosa deve fare* non è una cascata di `if`, è un sistema che cambia stato, sceglie una strategia, accede ai dati e sintetizza una risposta che dovrebbe essere pertinente e affidabile.

Il punto difficile è che i problemi dell'IA stanno **al confine tra la matematica e la realtà**: spesso non hanno una sola risposta formalmente definita.

> [!example] La diagnosi medica
> Medici diversi, davanti agli stessi sintomi, danno diagnosi vicine ma non identiche, sia sulle cause sia sulle terapie. La relazione *sintomi → diagnosi e terapia* non è quindi una **funzione** in senso matematico: è come se ognuno avesse "la sua matematica". Eppure una terapia **non può essere un'opinione**: il "buon senso" della nonna non è una soluzione.

Da qui il **paradosso dell'intelligenza**: agire su problemi che non hanno un'unica soluzione cercando di sfuggire all'arbitrarietà dell'opinione. L'IA lo affronta con gli **algoritmi**, cioè modelli di calcolo formale, per ottenere decisioni **il più oggettive possibile**: approssimare un ideale che dipende dal **dominio di conoscenza** (un cardiologo e uno pneumologo fanno diagnosi diverse perché si occupano di domini diversi) e dal **contesto** di applicazione. Anche esperti diversi divergono, ma entro i fondamenti oggettivi della loro disciplina.
## Cosa c'è dietro una risposta
Molti prodotti "basati su prompt" che chiamano un LLM deludono gli utenti finali perché chi li costruisce non sa cosa c'è dietro. Nelle decisioni critiche questo non è accettabile.

> [!example] Decisioni critiche: la sicurezza nucleare
> L'agenzia delle Nazioni Unite che monitora gli impianti nucleari (IAEA, ad es. Zaporizhzhia) lavora con un'enorme documentazione tecnica. Firmare un documento che dichiara un impianto **conforme** ai criteri di sicurezza richiede di accedere a tutti i criteri ingegneristici, verificare i dati dell'impianto e poi dire sì o no: se si dice sì quando l'impianto non è conforme, la gente muore. Non è il "compitino" scritto con un chatbot.

Un **uso consapevole** dell'IA si basa sulla conoscenza della catena che porta a una risposta:
- il ruolo dei **dati**;
- il ruolo del **machine learning** e della quantificazione;
- l'**inferenza** e la **decisione finale**;
- il ruolo del **linguaggio**.

Non c'è magia: lavorare con l'IA significa portarla a ragionare, impostare bene i problemi e saper giudicare se le risposte sono accettabili. E questo richiede competenza.
### Le discipline che confluiscono nell'IA
L'IA nasce negli anni '50 e mette insieme:
1. la **matematica**, perché molti modelli sono funzioni quantitative complesse;
2. l'**informatica**, perché i dati e le loro strutture (liste, grafi…) sono materia informatica;
3. l'**intelligenza artificiale** in senso proprio: chi voleva una decisione finale *intelligente* ha individuato modi **deduttivi** (il sillogismo di Aristotele) e modi **induttivi** (l'inferenza statistica), che nella storia della disciplina si sono alternati;
4. la **linguistica**, perché anche i Transformer si ispirano a modelli della lingua.
## Agenti e ricerca
Un **agente razionale**, quando risponde, *sceglie* una risposta; e la risposta spesso non è a un passo di distanza, ma va **costruita con una sequenza di passi**. Quindi **decidere è un problema di ricerca**: agente e ricerca sono intimamente connessi, e gli algoritmi di ricerca già noti (visite di grafi, cammini) vengono riusati ed estesi.
## Conoscenza e logica
Se la scelta avviene con una ricerca in uno **spazio degli stati**, cosa caratterizza lo stato? La **conoscenza**: ogni agente ha una **rappresentazione interna dello stato del mondo** che gli permette di decidere come procedere.
- Nel labirinto vado a destra o a sinistra in base a come immagino il labirinto.
- In una diagnosi scarto delle strade perché so che una rinite indica un raffreddore e non un problema cardiaco.

Cercare con conoscenza serve a fare **pruning**: l'agente si fa spazio nella "giungla delle decisioni" a colpi di mannaia, tiene aperte le strade utili e taglia quelle verso soluzioni impossibili. Ogni visita riduce lo spazio delle alternative.

Per rappresentare il mondo si usano i **linguaggi logici**. Il legame con le basi di dati è diretto: anche lì la realtà si descrive concettualmente con entità e relazioni, e una query SQL (`SELECT … FROM … WHERE`) è una specifica logica di ciò che i dati devono soddisfare per essere una risposta. Nell'IA la logica diventa un meccanismo **proattivo**: esprime anche la **logica delle azioni**, un po' come i vincoli e i **trigger** delle basi di dati che, quando succede qualcosa, eseguono controlli e respingono le transazioni non ammissibili.

La **programmazione logica** (Prolog) rende la logica eseguibile; i risolutori logici sono anche tra i tool usati dagli agenti basati su LLM per fare inferenze automatiche.
## Modellazione dei dati
I dati non arrivano "salvifici": sono **rumorosi**, provengono da sorgenti diverse e vanno **riconciliati**. Una logica che descrive i dati e ne unifica l'interpretazione **precede** il machine learning: reti neurali e metodi statistici non fanno miracoli. Se si scelgono male le variabili da cui dipende una funzione, quella funzione **non potrà mai essere appresa**, indipendentemente dal volume di dati o dalla potenza di calcolo. Il problema è di **modellazione**: dato un problema, quali forme matematicamente rigorose e quali dati servono per rappresentarlo.
## Apprendimento automatico e linguaggio
Il **machine learning** è la base per capire come funzionano i **Transformer** che stanno dietro gli LLM.

Quando si scrive un **prompt** entra in gioco il linguaggio: scrivere un buon prompt significa scrivere bene in italiano, e un prompt sbagliato è un prompt che non ha fatto capire il task.
## Obiettivi e organizzazione del corso
Dalle slide, non visto a lezione (la trascrizione non è disponibile): le slide della Lezione 0 (pp. 2-19) sono in gran parte organizzative; il docente ha detto a lezione che in parte sono dell'anno precedente e non fanno fede (ad es. calendario, orale): il quadro aggiornato è nel [[Intelligenza Artificiale/README#Modalità d'esame]].
### Obiettivi (slide 2-3)
- **Fondamenti**: agenti razionali e algoritmi di ricerca per il problem solving ([[02 - Agenti intelligenti]], [[03 - Risoluzione di problemi mediante ricerca]]); il ruolo della conoscenza, rappresentazione e ragionamento, con la logica per conoscenza e deduzione ([[04 - Agenti basati sulla conoscenza]]); apprendimento automatico, dalle reti neurali multistrato ai Transformer; comunicazione degli agenti, lingue e NLP.
- **Argomenti avanzati**: ricerca on-line (local search e random search), task e modelli di ML per l'NLP, reti neurali e Large Language Models, encoding dei dati per l'IA generativa.
- **Workshop ed esercitazioni**: discussioni su problemi specifici, report dell'interazione didattica con LLM; progettazione di agenti in Python (agenti semplici, ricerca euristica, agenti che integrano ML e problem solving), classificazione dei testi e inferenza testuale, sentiment analysis con encoder pre-addestrati, PyTorch, prompt engineering.
### Prerequisiti e corsi correlati (slide 5)
- Prerequisiti: Analisi, Algebra e Logica, Calcolo delle Probabilità; Python e Prolog; basi di dati (modellazione, progettazione, SQL).
- Correlati della magistrale: Machine Learning (Gambosi), Deep Learning (Basili), Natural Language Processing (Zanzotto), Information Retrieval (Croce), Knowledge Engineering (Stellato), Artificial Intelligence and Security.
### Modalità didattiche (slide 6-10)
- Classe su MS Teams `2026_27_BASILI-8067806-INTELLIGENZA_ARTIFICIALE`; materiali e avvisi anche sul sito `sag.art.uniroma2.it/didattica/basili/IA_26_27/`.
- Lezioni in Aula 5 PP2: lunedì 14-16, mercoledì 14-16, venerdì 11:30-13:30; laboratorio episodico il venerdì 14:30-16:30; ricevimento (da verificare) il mercoledì dopo la lezione e su richiesta.
- Alcuni esercizi di verifica sono da consegnare entro la data d'esame. La frequenza è caldamente consigliata.
- Testi (preliminari): Russell e Norvig, *Artificial Intelligence: a Modern Approach*, 4ª ed. 2022 (online su aima.cs.berkeley.edu); *The Description Logic Handbook* (Baader et al., 2010); Manning, Raghavan, Schütze, *Introduction to Information Retrieval* (2008); articoli e dispense del docente.
### Esami (slide 12-16)
- **Calendario**: esonero di metà/fine novembre; secondo esonero e scritto finale a gennaio; secondo scritto a febbraio. Ogni scritto ha un progetto facoltativo.
- **Esercitazioni**: un tema a settimana, sviluppato dallo studente con il supporto degli esercitatori; si produce un programma funzionante in Python e un notebook che commenta lo sviluppo (anche l'interazione con i modelli di IA usati); consegna sul portale degli esercizi. Ogni esercitazione consegnata può diventare domanda d'esame orale.
- **Scritto**: obbligatorio solo per chi non ha consegnato l'80% degli esercizi. Test a risposta multipla (20-30 minuti, 8-15 domande) e domanda aperta in stile orale (circa 90 minuti): progettazione di un agente per problemi di ricerca, di algoritmi di ML per inferenza complessa (ad es. classificazione di testi), discussione di argomenti del programma.
- **Orale**: obbligatorio per tutti. Discussione di errori dello scritto ed esercizi consegnati (modellazione, formalizzazione matematica, soluzioni algoritmiche, analisi computazionale); può partire dall'interazione con il modello di IA, ma per definizioni, algoritmi e metodi fa fede il **libro di testo**, non il modello.
- **Progetto facoltativo** (max 2-3 persone): assegnato in stile tesi, con ricevimento dedicato, demo (LLM) e breve relazione; si discute progetto e demo. Esempi: sentiment analysis su Twitter, addestramento di LLM per task specifici, image processing con LLM, information extraction medica (genomica, radiomica, DSS). In alternativa un approfondimento bibliografico su un argomento avanzato.
> [!warning] Da verificare
> Le slide indicano "gennaio 2026" e "febbraio 2026" per gli scritti, ma l'anno accademico è 2026-27: è quasi certamente un refuso del docente (gennaio e febbraio 2027). Per ogni differenza (calendario, esonero, orale obbligatorio per tutti) vale quanto detto a lezione, riportato nel [[Intelligenza Artificiale/README#Modalità d'esame]].
### Cosa fare subito (slide 17)
Registrarsi al corso su Delphi, rispondere al questionario preliminare (QR code a slide 18), iscriversi al Team e verificare l'adesione (il docente potrebbe dover accettare la richiesta); verranno pubblicati elenchi degli iscritti, progetti e slide.
## Dalla slide «From Intro AI Short For Lab»
Dalle slide, non visto a lezione: la slide `000_From_Intro_AI_Short_For_Lab` porta la data a.a. 2025-2026 (Roberto Basili, per i corsi di laurea in Informatica e in Ingegneria gestionale, informatica e di internet). Qui si riportano gli argomenti che non compaiono nelle altre parti della nota, con i numeri di pagina della slide. La parte sull'IA generativa, con le conversazioni mostrate con un assistente (pp. 8-19), e quella sul captioning e sulla cronologia (pp. 33-40) non sono riassunte qui.
### Che cos'è l'IA
La slide (p. 3) dice che l'intelligenza artificiale si occupa dell'**osservazione e comprensione** del comportamento intelligente, **per la sua riproduzione**. La definizione di **intelligenza** (p. 4) è quella dell'Enciclopedia britannica:

> [!quote] Intelligenza
> «Qualità mentale che consiste nell'abilità di apprendere dall'esperienza, di adattarsi a nuove situazioni, comprendere e gestire concetti astratti. E utilizzare conoscenza per agire sul proprio ambiente.»
#### IA forte e IA debole
La slide distingue due modi di intendere l'IA (pp. 5-6).

> [!info] L'IA come scienza (IA forte, approccio della psicologia cognitiva)
> - **Obiettivo**: la comprensione dell'intelligenza umana.
> - **Metodo**: costruire modelli computazionali dell'agire intelligente.
> - **Criterio di successo**: risolvere i problemi **con gli stessi processi usati dall'uomo**.
> - **Requisito**: enfasi sulla verifica sperimentale in rapporto all'uomo.

> [!info] L'IA come ingegneria (IA debole, approccio ingegneristico)
> - **Obiettivo**: costruire sistemi dotati di razionalità.
> - **Metodo**: codificare il pensiero razionale; progettare processi che simulano il comportamento razionale.
> - **Criterio di successo**: misure (percentuali) di successo nelle decisioni che richiedono intelligenza.

La differenza sta quindi nel criterio: per l'IA forte conta che il sistema ragioni **come l'uomo**, per quella debole che **decida bene**.
### Definizioni di IA lungo due assi
La slide (p. 7) ordina le definizioni di IA in una tabella con due assi: **pensiero** o **azione** (in riga) e **umanità** o **razionalità** (in colonna).

| | Umanità | Razionalità |
|---|---|---|
| **Pensiero** | «[L'automazione delle] attività che associamo al pensiero umano, come il processo decisionale, la risoluzione di problemi, l'apprendimento…» (Bellman, 1978) | «Lo studio delle facoltà mentali attraverso l'uso di modelli computazionali» (Charniak, McDermott, 1985) |
| **Azione** | «L'arte di creare macchine che svolgono funzioni che richiedono intelligenza quando svolte da esseri umani» (Kurzweil, 1990) | «Il ramo della scienza dei calcolatori che si occupa dell'automazione del comportamento intelligente» (Luger, Stubblefield, 1993); «L'impresa di costruire artifatti intelligenti» (Ginsberg, 1993) |

La slide non collega in modo esplicito questa tabella alla distinzione tra IA forte e IA debole.
### Quali capacità caratterizzano un sistema di IA
La slide (p. 26) lascia la domanda aperta, con un elenco di possibili risposte: capacità di simulare il comportamento umano; di ragionamento; intelligenza come competenza «da esperto»; intelligenza come «buon senso» (senso comune); capacità di interagire con un ambiente; capacità sociali, di comunicazione e coordinamento; capacità di comprendere e provare emozioni; altro. Nella pagina precedente (p. 25) le «conclusioni» sulle prestazioni di un assistente conversazionale riguardano la naturalezza dell'interazione, la comprensione dei problemi, il pragmatismo (capire le intenzioni e porsi obiettivi corretti e realistici), le spiegazioni, la coerenza con il discorso e il ragionamento espresso in forma linguistica.
### Il test di Turing
La slide dedicata a Turing (p. 29, «Capacità di imitazione?») presenta Alan Turing e il suo test. A p. 30 dà la definizione:

> [!quote] Test di Turing
> Il test di Turing (1950) è «un tentativo di definizione **operativa** di intelligenza».

La figura mostra «The Interrogator»: un interrogante, chiuso in una stanza, comunica tramite terminale con due interlocutori, una persona e un calcolatore. La slide non spiega altro del test.
### Ambiguità linguistica
La slide dedica diverse pagine all'**ambiguità**, esempio di quanto sia difficile capire il linguaggio naturale.
- **Il cartello sulla scala mobile** (pp. 31-32). «Dogs must be carried on this escalator» ha, secondo la slide, più interpretazioni: tutti i cani devono avere la possibilità di fare questa meravigliosa corsa sulla scala mobile; questa scala mobile è solo per chi ha un cane in braccio; non si può portare l'animale sulle altre scale mobili; se si viaggia con un animale, bisogna portarlo in braccio.
- **Il riferimento di «questo»** (pp. 20-24). La slide mostra una conversazione con un assistente su frasi come «se sfrego un mattone su un uovo questo si sporca?» e «se tiro il muro sul colle questo si rompe?». La risposta dell'assistente distingue un'interpretazione letterale (il muro si rompe solo se subisce una forza sufficiente) da un gioco di parole o indovinello, e propone di verificare se si tratti di un indovinello. Quando gli si racconta la storiella («C'era un asino ed un muro sul colle. L'asino scese dal colle perché stava stretto insieme al muro. Si domandò: se tiro il muro sul colle questo si rompe, scendendo?») la legge come un piccolo paradosso scherzoso.
- **Analisi dell'interpretazione** (p. 21, «Osservazioni: interpretazione»). La slide annota quattro frasi simili («se tiro un uovo sul muro questo si rompe?», «se sbatto un mattone su un uovo questo si rompe?», «se giro un lago sul van questo si vede?», «se tiro il muro sul colle questo si rompe?»), segnando il verbo, i possibili antecedenti di «questo» (con frecce verso due sintagmi diversi) e il predicato. Nella frase sul lago e sul van i punti interrogativi indicano che l'antecedente non è determinabile con certezza.
### I fondamenti dell'IA
La slide (p. 27) elenca le discipline che stanno alla base dell'IA, con gli ambiti principali:
- **matematica**: logica, algebra, analisi funzionale, probabilità;
- **informatica**: algoritmica, complessità, rappresentazione della conoscenza;
- **linguistica**: linguistica computazionale, semiotica;
- **filosofia**: ontologia, epistemologia, filosofia del linguaggio;
- **psicologia**: percezione e cognizione;
- **economia**: teoria dei giochi;
- **neuroscienze**: brain imaging;
- **teoria del controllo e cibernetica**.

È un elenco più ampio di quello detto a lezione ([[#Le discipline che confluiscono nell'IA]]: matematica, informatica, intelligenza artificiale in senso proprio, linguistica).

A p. 28 la slide propone la figura della «farmacia dell'IA» (*AI pharmacy*): una farmacia i cui scaffali sono intestati ai paradigmi dell'IA, tra cui logica (*logic*), apprendimento (*learning*), reti neurali (*neural nets*), ricerca e risoluzione di problemi (*search/problem solving*), ragionamento con incertezza (*reasoning with uncertainty*) e rimedi applicativi (*application remedies*).
### L'effetto IA
A p. 41 la slide descrive l'IA come un **fenomeno sociale**: lo sviluppo continuo del campo sposta in avanti la frontiera della cosiddetta *machine intelligence*, e questo rafforza il cosiddetto «effetto IA» (*odd paradox*): non appena l'IA porta nuovi risultati nella vita comune, le persone si abituano a quelle tecnologie e smettono di considerarle IA, e lo schema si ripete. L'IA non rilascia prodotti dirompenti dal nulla, ma costruisce in modo incrementale approssimazioni migliori dell'intelligenza; nonostante ciò l'intelligenza umana è la scelta d'elezione per misurare il progresso dell'IA.
