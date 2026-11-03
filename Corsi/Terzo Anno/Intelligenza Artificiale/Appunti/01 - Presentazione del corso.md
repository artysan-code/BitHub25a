---
tags:
  - intelligenza-artificiale
  - introduzione
slide:
  - "000_Intro_2026_27_v1.0.pdf"
---
# Presentazione del corso
Lezione 1 (05/10/2026; slide 000_Intro, pp. 1-19, in gran parte organizzative: vedi [[#Obiettivi e organizzazione del corso]]): che tipo di problemi affronta l'IA e quali sono i suoi ingredienti fondamentali (ricerca, conoscenza, dati, apprendimento, linguaggio).
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
