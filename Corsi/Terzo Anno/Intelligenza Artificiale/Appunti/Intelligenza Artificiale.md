## Introduzione all'IA
L'intelligenza artificiale si occupa della osservazione, comprensione e riproduzione del comportamento *intelligente*. Non corrisponde all'**automazione**.

La definizione di intelligenza è:
- **Apprendere dall'esperienza**
- **Adattarsi alle nuove situazioni**
- Usare la coscienza per **agire sul proprio ambiente**

### IA come scienza
#### Approccio della psicologia cognitiva (IA Forte)
Ha come obiettivo la comprensione dell'intelligenza umana, tramite la costruzione di modelli computazionali *dell'agire intelligente*.

Il criterio di successo la risoluzione di problemi con le stesse metodologie e/o processi usati dall'uomo, ma per fare ciò è richiesta una verifica sperimentale in rapporto all'uomo.

(Riproduzione dell'IA in proporzione all'intelligenza umana)
#### Approccio Ingegneristico (IA Debole)
Ha l'obiettivo di costruire sistemi dotati di razionalità tramite la codifica del pensiero razionale: progettazione di processi simulativi del comportamento razionale.

Avremmo successo in base alla % di successo nelle decisioni che richiedono intelligenza (riproduco la performance dell'uomo, non il processo, principio *statistico*)

(Riproduzione dell'IA con sistemi razionali e statistici)
### Definizioni di IA
Definiamo degli attributi relativi a delle entità di cui abbiamo parlato fino ad ora.
Associamo all'**umano**:
	- *Pensiero*: L'automazione delle attività che associano al pensiero umano, come il processo decisionale, la risoluzione di problem, l'apprendimento, etc. .
	- *Azione*: L'arte di creare macchine che svolgono funzioni che richiedono intelligenza quando svolte da esseri umani. (Come le *reti neurali*)
Mentre associamo alla **razionalità**:
	- *Pensiero*: Lo studio delle facoltà mentali attraverso l'uso di modelli computazionali.
	- *Azione*: Il ramo della scienza dei calcolatori che si occupa dell'automazione del comportamento intelligente. L'impresa di costruire artefatti intelligenti. (Programmi che eseguono)
### Cosa fa un'AI?
Generalizzando le facoltà di una IA, possiamo dire che esegue **Question Answering**, in diverse metodologie:
- Dialoga con noi
- Risponde a delle nostre curiosità
- Risolve problemi di matematica
- Fornisce consigli
- ...

Questo impone però anche un **prompting** accurato, cioè una formulazione precisa della domanda, ed è proprio qui che emerge il concetto di intelligenza. Ad esempio, chiedendo "Chi è il presidente dell'Albania?", l'IA potrebbe rispondere correttamente indicando il _presidente della Repubblica albanese_, utilizzando le fonti trovate online. Tuttavia, se la nostra intenzione era riferirci al "presidente del Consiglio" (premier), la risposta - seppur corretta rispetto al prompt - non è quella che cercavamo.

Migliorando il prompt con "Chi è il presidente del Consiglio in Albania?" otteniamo invece la risposta desiderata.

Da questo esempio emerge un problema fondamentale: **l'interpretazione** che l'IA fa del nostro prompt. Gli addestramenti moderni permettono generalmente di riconoscere quando mancano informazioni specifiche, come mostrato nell'esempio: ![[i1.png]]
Quando però questo non accade, vi è il fenomeno dell'**Ambiguità**.

In generale ciò che manca è _l'intelletto_ necessario per suggerire alternative più pragmatiche. Ad esempio, se chiediamo come costruire una chitarra elettrica Fender, l'IA fornirà istruzioni dettagliate sulla costruzione, ma non avrà l'intuizione di suggerire che potrebbe essere più _intelligente_ acquistarne una già costruita e modificarla secondo le proprie esigenze.

Solo se specifichiamo esplicitamente che vogliamo proprio costruirla da zero, l'IA sa rispondere adeguatamente (Step by Step).

Vi sono diversi esempi e si può anche un po' giocare per capire come deduce il prompt per arrivare alla risposta. L'importante è evidenziare però:
- Da dove vengono le sue conoscenze?
- Quali sono i suoi atteggiamenti intelligenti?
- È naturale il suo modo di proporre soluzioni a problemi un po' diversi dallo standard? Ci soddisfa come risposta?
- Cosa sa dal punto di vista linguistico?

Che capacità ha un'intelligenza artificiale:
• Capacità di simulare il comportamento umano?
• Capacità di ragionamento?
• Intelligenza come competenza “da esperto”?
• Intelligenza come “buon senso” (senso comune)?
• Capacità di interagire con un ambiente?
• Capacità sociali, di comunicazione e coordinamento?
• Capacità di comprendere e provare emozioni?
• Altro?
### Test di Turing
Corrisponde ad un tentativo di definizione operativa di intelligenza.

Supponiamo tu abbia tre partecipanti:
- Un essere umano (giudice)
- Un altro essere umano
- Una macchina/IA

Il giudice chatta con entrambi senza vederli o sentirli, solo tramite testo. Non sa chi è chi. Fa domande, conversa liberamente.

**Obiettivo**: Se il giudice, dopo aver conversato con entrambi, non riesce a distinguere in modo affidabile chi è l'umano e chi è la macchina, allora la macchina "supera" il test.

In pratica è come giocare a indovina chi: la macchina cerca di comportarsi in modo così naturale da sembrare umana, mentre il giudice cerca di smascherarla facendo domande difficili, cercando incongruenze, o testando capacità tipicamente umane come creatività, emozioni, ragionamento complesso.

Se la macchina riesce a "ingannare" il giudice una percentuale significativa delle volte, si considera che abbia dimostrato un comportamento intelligente indistinguibile da quello umano. O è così?
## Problem Solving: Sentimenti Analysis o recognition
Che sentiment esprime un tweet del tipo "Odio il Napoli e amo Roma..."? Che ha assolutamente ragione se non tifasse la Juventus.

Spezzando la frase e le parole definisce ciascuna parola nei i due *domini* richiesti: **positivo** o **negativo**. Immaginiamo che questa distinzione la facciamo tramite una funzione che prende in input una "parola" e genera un risultato per quella:$$f_{sa}:\tau \implies \{pos,neg\}$$
Quindi il tweet ha sentimenti contrastanti ma che sono ben definiti: Odio verso Napoli e positivo per Roma.

Su questa parte vi è proprio un "progetto" o più **sfida** nel corso, si segue ad esercitazione.
## Agenti Intelligenti: la prospettiva di AIMA
Un agente ha dei:
- Sensori per *percepire* i dati e l'ambiente.
- Tools o *effectors* per eseguire azioni sull'ambiente.

Principio di *ciclo*: percepisco-decido-agisco
### Una visione moderna
Gli agenti intelligenti:
- Ricevono percezioni da un ambiente
	- Usate per decidere che azioni svolgere *e quando*.
	- Una parte importante della percezione di informazioni da parte dell'agente è la *memoria persistente* che ha rispetto all'ambiente.
- Agiscono sull'ambiente mediante azioni
	- Anche anticipate da alcuni calcoli.
- Sono capaci di comunicare
- Sono capaci di collaborare
- Sono capaci di difendersi da altri agenti
- Hanno credenze, obiettivi, intenzioni...
- Hanno un corpo e provano *emozioni*
	- Possono avere effettivamente una fisicità nell'ambiente dove percepiscono le informazioni.
	- Dimensione *soggettiva* delle emozioni
### Percezioni e azioni
Chiamiamo *percezione* l'input diciamo dei sensori che possiede l'agente intelligente. Una sequenza percettiva corrisponderà quindi ad una "storia completa delle percezioni"; questa ha 

### Agente razionale
Un agente razionale interagisce con il suo ambiente in maniera *efficacie*:
- Fa la cosa giusta.
- La sequenza di stati ha un qualche aspetto auspicabile
- Mostra una preferenza selettiva verso certi comportamenti

Serve un criterio di valutazione *oggettivo* dell'effetto delle azioni dell'agente (della sequenza di stati dell'ambiente).

La razionalità dell'agente è relativa a:
- La misura delle prestazioni che hanno successo
- La conoscenza pregressa dell'ambiente
- Le percezioni presenti e passate
- Le capacità di un agente

> 
> Per ogni sequenza di percezioni compie l'azione che **massimizza il valore atteso della misura delle prestazioni** considerando *percezioni passate* e la sua *conoscenza pregressa*.
> 

La razionalità **non è onniscenza** e **non è onnipotenza**:
- Non si pretende la perfezione ma basta massimizzare il risultato atteso, si può però richiedere l'acquisizione di nuove informazioni.

Raramente tutta la conoscenza dell'ambiente può essere fornita. L'agente deve essere capace di cambiare il proprio comportamento in base all'esperienza (**Apprendimento**).
### Agente autonomo
Un agente può essere autonomo nella misura in cui il suo comportamento dipende direttamente dalla sua esperienza *dell'ambiente* e delle *operazioni a lui richieste*.

## Ambienti e codifica PEAS (Prestazione, Ambiente, Attuatore, Sensore)
### Proprietà dell'ambiente e del problema
Gli ambienti posseggono caratteristiche comuni lungo alcune dimensioni:
- Completamente o parzialmente *osservabile*
- Agente vs Multi agente
- Deterministico , stocastico o non deterministico
- Episodico o sequenziale
- Statico o dinamico
	- Tempo di reazione dell'agente (lento o istantaneo)
		- Lento, è garantito che durante la decisione l'ambiente non è cambiato (non in maniera precisa ovviamente, ci saranno dei cambiamenti)
- Discreto o continuo
	- Avere un tempo studiato (utilizzo di step)
	- Seguire la linea temporale continua, dover reagire in base al tempo
#### Osservabilità
Un ambiente è **completamente osservabile** se l'apparato percettivo è in grado di dare una conoscenza completa di questo primo o il necessario per eseguire l'azione. Non c'è bisogno di mantenere uno stato.

#### Ambiente Singolo o Multi agente
Il mondo può anche cambiare per eventi, ma non necessariamente per azioni dell'agente.
#### Predicibilità
- Deterministico se lo stato successivo è completamente determinato dallo stato corrente e dall'azione.
- Stocastico, se esistono elementi di incertezza con una probabilità associata.
- Non deterministico, se gli stati possibili non corrispondono ad una specifica distribuzione di probabilità, esempio sono equiprobabili.

Agenti deterministici, i cambiamenti dell'ambiente dipendono solo dallo stato dell'ambiente in un certo istante e dalla azione dell'agente.


