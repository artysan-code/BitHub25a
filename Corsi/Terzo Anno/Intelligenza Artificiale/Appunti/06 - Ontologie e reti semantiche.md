---
tags:
  - intelligenza-artificiale
  - rappresentazione-della-conoscenza
  - ontologie
  - reti-semantiche
slide: []
---
# Ontologie e reti semantiche
## Categorie, ontologie e reti semantiche
Lezione 13 (16/11/2026): dopo la [[05 - Logica del primo ordine|logica del primo ordine]], si vede come usarla per **rappresentare la conoscenza** di un dominio, non per dimostrare teoremi ma per descrivere il mondo in cui l'agente lavora. Si introducono categorie e **ontologie** (con l'esempio della *Gene Ontology*), le **reti semantiche** con l'ereditarietà e le eccezioni, la loro semantica in logica del primo ordine e i grafi della conoscenza usati dai motori di ricerca (AIMA cap. 10, *Knowledge Representation*).

> [!warning] Slide da integrare
> Le slide di questa parte (sul sito del corso probabilmente `0044_Logic_and_KR_v1.pdf`, insieme a `0043_Logic_and_Reasoning_v1.3.pdf`) non sono ancora nel repo: la nota è ricavata dalla sola registrazione. Manca anche la lezione 12 (11/11/2026), di cui non c'è registrazione.
### Esercizi sulla logica del primo ordine
All'inizio il docente presenta gli esercizi del capitolo sulla logica del primo ordine (AIMA, 3ª ed., cap. 8; le domande sono personali, ma alcune finiranno sul sito tra quelle da consegnare):
- dire se una formula è **valida**, cioè vera in tutte le interpretazioni, ad esempio una formula su $x$ e $y$ con $x=y$; oppure, date tre o quattro formule, indicare quali sono valide (è una tipica domanda dello scritto, con risposte come "nessuna" o "tutte");
- per frasi sulla geografia (capitali e stati, es. 8.9), dire se una formula FOL proposta è (1) corretta e rappresenta il significato inteso, (2) sintatticamente non valida (ad esempio se si applica un connettivo dentro gli argomenti di un predicato), (3) corretta ma solo un'approssimazione del significato;
- **albero genealogico** (es. 8.14): definire in modo non ridondante, come in una base di dati, predicati come sorella, fratello, moglie, marito, coniuge, figlio, figlia, poi chiedere al sistema i nipoti di Elisabetta o il cognato di Diana, e infine definire il cugino di grado $m$ a distanza di $n$ generazioni (*$m$-th cousin $n$ times removed*);
- rappresentare in Prolog la **mappa** usata per A\*, sfruttando la ricorsione per domande che in SQL richiederebbero un join per ogni livello (ad esempio quali città sono collegate da cammini più lunghi di una certa distanza);
- dal par. 8.3.4: tradurre il **Wumpus** dalla versione proposizionale al primo ordine in Prolog, e pianificare con A\* quando buche e oro sono noti, oppure con una ricerca online che passa solo per celle sicure. Una cella dimostrata sicura si può asserire e riusare (come in [[03 - Risoluzione di problemi mediante ricerca#Ricerca AND-OR, stati credenza e ricerca online|LRTA\*]]).

Mercoledì si fa una **prova generale** in aula: dato un gioco, progettare l'agente fino ad A\* ed eventualmente a una ricerca online, in pseudocodice o Python, partendo dalla propria modellazione. Il docente consiglia di provare su carta, perché all'esame il PC non c'è. Completata a casa e caricata, vale come esercizio consegnato.
### Ingegneria della conoscenza
Quando gli agenti lavorano in mondi complessi la conoscenza cresce di volume e va **organizzata**, come il software a oggetti: molte persone la scrivono a più mani, serve modularità, incapsulamento e il modo di scoprire gli errori di chi la scrive. Serve una metodologia, cioè un'**ingegneria della conoscenza**, e un modello che ha funzionato in un dominio si può portare in altri.

Elementi da rappresentare:
- **categorie** di oggetti: il dominio non è monolitico ma diviso in categorie disgiunte (nel labirinto: celle come posizioni, ostacoli, nemici, agenti). Dire che un oggetto è di una categoria esclude i modelli in cui non lo è: restringe i mondi possibili e le interpretazioni, come in un diagramma ER o con i tipi in un linguaggio a oggetti (meno operazioni possibili su un oggetto, programmazione più semplice e più modulare);
- la distinzione tra oggetti **fisici** (il braccio di una persona, la sua altezza) e **astratti** (il benessere): confonderli complica i vincoli, come un diagramma ER con una sola tabella chiave-valore;
- **azioni** ed **eventi**, perché spesso bisogna ragionare su ciò che accade: in un video di cucina le fasi della ricetta ("tutti i video in cui si usano le cipolle ma non soffritte");
- **atteggiamenti mentali**: ciò che è vero nel mondo, ciò che l'agente **crede** (dalle sue percezioni) e ciò che **preferisce** sono conoscenze diverse, da codificare separatamente;
- la **non monotonia**: esplorando un labirinto si aggiungono fatti, e teoremi che erano veri possono smettere di esserlo; l'insieme dei modelli a volte si restringe e a volte si allarga. La risoluzione lavora su insiemi di modelli monotoni e fatica a catturarlo; per questo si introducono incertezza e probabilità (non nel corso). Vedi anche il [[04 - Agenti basati sulla conoscenza#Ragionamento non monotono|ragionamento non monotono]].
### Ontologie
Un'**ontologia** separa gli oggetti del dominio in **classi** organizzate gerarchicamente. Un esempio di **ontologia superiore** (*upper ontology*, AIMA fig. 10.1): tutto ciò che esiste si divide in categorie **astratte** (insiemi, numeri, oggetti rappresentazionali come frasi e misure, che non hanno un luogo fisico) e **generalizzate** degli eventi (intervalli di tempo, luoghi, processi, oggetti fisici); gli oggetti fisici comprendono le **cose** (animali, agenti, esseri umani) e le **sostanze** (solide, liquide, gassose: "mucchi" di materia senza un'unità).

> [!example] Dove mettere i medicinali
> Un medicinale è un oggetto fisico, aggregato a livello molecolare, quindi starebbe tra le sostanze. Ma un medicinale si vende e ha un prezzo, cioè ha un'**unità**, e allora forse sta tra le cose; però le cose dell'ontologia sono animali e agenti, e mancano gli **artefatti**. L'ontologia va rivista. Fare un *commitment* verso un'ontologia significa negare i mondi in cui un oggetto non trova posto nelle sue categorie. Un concetto può anche appartenere a più categorie (Pinocchio è un essere umano in una storia, ma anche un oggetto astratto inventato da uno scrittore).
#### La Gene Ontology
La **Gene Ontology** (GO) rappresenta gli oggetti di interesse per biologia, medicina e chimica. Al primo livello non distingue astratto e fisico, ma tre tassonomie indipendenti: **processi biologici**, **funzioni molecolari** e **componenti cellulari**. Scendendo:
- un processo di biosintesi può essere figlio di due concetti visti da prospettive diverse, quindi la struttura non è un albero ma un grafo aciclico; i sottoinsiemi al livello superiore devono allora sovrapporsi;
- la terminologia non è casuale: deve valere che un processo è del tipo di tutti i suoi antenati (biosintesi dei carboidrati, quindi processo metabolico, quindi processo cellulare);
- le relazioni principali sono **is-a** (il mitocondrio è un organello) e **part-of**, la composizione (il citoplasma ha tra le sue parti il mitocondrio).

Ogni nodo ha attributi obbligatori: un **identificatore** univoco (`GO:` seguito da un numero), un **nome** (mitocondrio), la **tassonomia** di appartenenza, una **definizione testuale** scritta dai biologi e le **relazioni** con altri nodi, cioè archi con un tipo. È una struttura più ricca dei grafi visti finora, con nodi atomici: ogni nodo ha una struttura interna data dal modello logico del dominio, e un sistema agentico può leggere la definizione invece di fermarsi a un nome o a un numero. Al tempo della slide la GO aveva circa 38 000 termini validi, distribuiti tra le tre tassonomie.

La GO è anche una **norma**: è costruita da tutta la comunità internazionale, e chi vuole cambiare una definizione deve confrontarsi con le annotazioni che rappresentano ciò che si sa. Le ontologie hanno un ruolo socio-tecnico: più sono usate, più diventano la prassi standard. Per costruirle non basta il rigore logico: bisogna acquisire la conoscenza in modo giustificato (intervistando gli esperti del dominio, non imponendo la propria tassonomia da informatici), e conta il modo in cui le **persone** categorizzano, che lascia traccia soprattutto nella lingua.
### Reti semantiche
Le rappresentazioni della conoscenza diventano **grafi** ricchi di relazioni. Le prime forme diagrammatiche vengono da Charles S. **Peirce**, filosofo e semiologo. Oltre alle relazioni rigide servono anche **associazioni**: neve è associata a freddo, ghiaccio, bianco, acqua, che sono dimensioni del significato ma non sono neve, e la forza dell'associazione dipende dal contesto (in Africa la neve è rarissima). Sono le persone a creare queste associazioni, e chi scrive prompt deve usare il vocabolario a cui l'agente è stato esposto: la logica non è morta, perché le risposte seguono il rigore del modello logico dato con il prompt.

> [!example] Gli esperimenti sui tempi di risposta
> (Sono gli esperimenti di Collins e Quillian, 1969: il nome è una nostra aggiunta, a lezione non è stato detto.) Tra fine anni '60 e anni '70 si misuravano i **tempi di risposta** di molte persone a domande come "un canarino è un canarino?", "è un uccello?", "può cantare?", "può volare?", "ha la pelle?". Le risposte più rapide sono quelle quasi sintattiche (un canarino è un canarino); le altre richiedono più tempo quanto più la proprietà è "lontana": "può volare" è più veloce di "ha la pelle". L'ipotesi è che la mente organizzi i concetti in un grafo e che ogni proprietà sia memorizzata al livello **più alto** possibile: "respira" sta con gli animali, "vola" con gli uccelli, "canta" ed "è giallo" con i canarini. Rispondere significa risalire il grafo, e il tempo cresce con il numero di passi.
>
> Le **eccezioni** si memorizzano localmente: "lo struzzo vola?" ha una risposta rapida, perché "non vola" è associato direttamente allo struzzo e **maschera** la proprietà degli uccelli.

È la stessa idea della **programmazione a oggetti**, nata secondo il docente dall'incontro tra IA e ingegneria del software: i metodi si associano alle classi e si **ereditano** risalendo la gerarchia a run time, e una sottoclasse può ridefinirli (*override*), mascherando quelli della superclasse. Le proprietà si scrivono una volta sola, nella classe più generale a cui si applicano, e le istanze le ereditano. Come nella generalizzazione dei diagrammi ER: se $\alpha$ sono gli attributi del padre e $\beta_1,\beta_2$ quelli dei figli, i figli hanno $\alpha\cup\beta_1$ e $\alpha\cup\beta_2$.

In una rete semantica:
- i nodi etichettati sono **categorie** (classi, come le entità dei diagrammi ER) o **individui** (istanze);
- gli archi sono relazioni binarie: **SubsetOf** (o *is-a* tra classi: Canary → Bird), **MemberOf** (tra un'istanza e la sua classe: Mary → FemalePersons) e relazioni tra istanze o con valori ($\mathit{Legs}$, $\mathit{Color}$, $\mathit{CanFly}$);
- l'**ereditarietà** viene dalla **transitività** di *is-a*: un cammino di lunghezza arbitraria porta all'istanza le proprietà di tutte le classi sopra, tranne quelle ridefinite più in basso.

**Reificazione.** Una relazione $n$-aria come "John dà il libro a Mary" si rappresenta con un nodo **evento** $E_1$, istanza della classe degli eventi $\mathit{Dare}$, collegato da relazioni binarie con i **ruoli**: agente (chi dà), oggetto (ciò che cambia proprietario) e destinatario. Si modellano così non solo gli oggetti ma anche gli eventi. Negli assistenti vocali per prenotare voli, ogni operazione è un evento di questo tipo, e la struttura **ispira le domande**: se l'utente dice "vorrei partire da New York domani", l'agente sa che manca la destinazione e la chiede.
### Semantica delle reti semantiche
Una rete semantica, come un diagramma ER o un insieme di classi Java, ha un'interpretazione in **logica del primo ordine**: il docente insiste che il modello nasce prima, e solo dopo si scelgono le librerie conformi al modello.

| Rete semantica | Logica del primo ordine |
| --- | --- |
| $A$ *is-a* $B$ (tra categorie) | $\forall x\ A(x)\Rightarrow B(x)$ |
| $a$ *member-of* $B$ | $B(a)$ |
| $A\xrightarrow{R}b$ (relazione tra istanze di $A$ e un valore) | $\forall x\ A(x)\Rightarrow R(x,b)$ |
| $A\xrightarrow{R}B$ (relazione tra categorie) | $\forall x\ A(x)\Rightarrow\exists y\ B(y)\land R(x,y)$ |

L'implicazione va solo **verso l'alto**: gli uccelli sono animali, ma non vale $\forall x\ \mathit{Animale}(x)\Rightarrow\mathit{Uccello}(x)$. Un'istanza di $B$ ha le proprietà di $B$ unite a quelle di $A$, meno quelle ridefinite in $B$. Esempi: $\forall x\ \mathit{Canary}(x)\Rightarrow\mathit{Color}(x,\mathit{Yellow})$ (tutti i canarini sono gialli); l'ultima forma dice ad esempio che ogni evento di tipo volo ha una persona che è il suo ordinante.

> [!example] L'elefante Clyde
> - $\mathit{Elefante}(\mathit{Clyde})$;
> - $\forall x\ \mathit{Elefante}(x)\Rightarrow\mathit{Colore}(x,\mathit{Grigio})$;
> - $\forall x\ \mathit{Elefante}(x)\Rightarrow\mathit{Mammifero}(x)$;
> - $\forall x\ \mathit{Mammifero}(x)\Rightarrow\mathit{NZampe}(x,4)$;
> - $\forall x\ \mathit{Mammifero}(x)\Rightarrow\mathit{Animale}(x)$.
>
> Con un passo di modus ponens (o di risoluzione) si deduce $\mathit{Mammifero}(\mathit{Clyde})$, poi $\mathit{Animale}(\mathit{Clyde})$, $\mathit{NZampe}(\mathit{Clyde},4)$ e $\mathit{Colore}(\mathit{Clyde},\mathit{Grigio})$, senza scriverli. È il numero **minimo** di assiomi da cui seguono tutte le altre conclusioni. L'eccezione del pipistrello, un mammifero con $\mathit{NZampe}=2$, si scrive sulla sua classe e maschera quella dei mammiferi.

Anche un record (un oggetto Java, un nodo della GO) è una piccola **teoria**: le variabili che formano la sua memoria e i metodi che le leggono e le scrivono. Per la GO la teoria interna di un nodo comprende un testo, la definizione: confrontando nomi e definizioni di due nodi in sotto-gerarchie diverse si ottengono **punteggi** di associazione, combinabili in modo lineare o non lineare. Secondo il docente le reti neurali imparano punteggi di questo tipo, e danno risposte corrette non perché i numeri siano giusti in sé, ma perché la struttura logica da cui sono stati appresi è coerente.
### Grafi della conoscenza
Cercando "Taj Mahal" su Google si trovano ristoranti e musicisti con quel nome, ma nel riquadro a destra (il *knowledge panel*) compaiono la descrizione del monumento, un'immagine, l'altezza, l'anno, la posizione. Per "Marie Curie" compaiono nascita, morte, coniuge, figli, scoperte (radio, polonio) e istruzione. Sono informazioni estratte da un **grafo della conoscenza**, costruito leggendo i testi di Wikipedia ed estraendone le relazioni, organizzato per classi (per ogni persona: nascita e, se c'è, morte; per uno scienziato anche le scoperte) e collegato alla query con un **matching approssimato** (funziona anche con "Mari Curie"). Non è il grafo delle pagine di PageRank, ma un grafo di proprietà formalizzate con un nome e una semantica: permette di capire che chi ha scoperto qualcosa è più simile a chi ha inventato qualcosa che a Francesco Totti.

Il quadro dell'IA di oggi: leggere i testi, costruire strutture, assegnare loro una semantica e sfruttarle algoritmicamente, con le reti neurali o altri algoritmi di apprendimento addestrati su quei dati.
### Prossimi passi
Si vedranno altri esempi e il ponte tra questi grafi discreti e le loro controparti **vettoriali** (gli *embedding*), usate oggi al posto delle basi di dati per il matching approssimato. Mercoledì c'è l'esercitazione in aula (il docente sarà alla Camera per la presentazione di un progetto di ricerca in campo medico e sarà online all'inizio).

> [!question] Domanda tipica d'esame
> Cos'è un'ontologia e a cosa serve un'ontologia superiore? Descrivi una rete semantica: quali sono i nodi, quali le relazioni, come funzionano ereditarietà ed eccezioni? Traduci in logica del primo ordine una rete con relazioni *is-a*, *member-of* e relazioni tra categorie, e mostra quali fatti si deducono (l'esempio di Clyde). Cos'è la reificazione di un evento?
