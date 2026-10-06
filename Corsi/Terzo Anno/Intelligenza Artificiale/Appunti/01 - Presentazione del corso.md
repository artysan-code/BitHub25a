---
tags:
  - intelligenza-artificiale
  - introduzione
slide: []
---
# Presentazione del corso
Lezione 0 (05/10/2026): che tipo di problemi affronta l'IA e quali sono i suoi ingredienti fondamentali (ricerca, conoscenza, dati, apprendimento, linguaggio).
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
