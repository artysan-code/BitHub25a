---
tags:
  - algoritmi-big-data
  - introduzione
  - data-mining
slide: []
---
# Introduzione al corso e al data mining
Lezione 1 (06/10/2026): organizzazione del corso, prerequisiti, e una panoramica per esempi (phishing, anomalie, data stream, PageRank) del tipo di problemi che si affrontano. Lo scopo non è capire a fondo ma individuare le situazioni tipiche che si approfondiranno nei prossimi mesi.
## Organizzazione del corso
- **Crediti**: 6 CFU per Informatica; per Data Science il corso vale 9 CFU, con un **progetto** e un'integrazione del programma concordata con gli studenti (gli "extra crediti"), verificata in sede d'esame.
- **Teams** è il canale di riferimento per comunicazioni, materiale e variazioni: comunicazione a senso unico, i docenti non lo leggono ogni giorno. Per parlare col docente o fissare un appuntamento si usa la **mail**.
- Le slide e il materiale sono sul canale; l'aggiornamento è settimanale. I libri di testo sono disponibili online.
- **Esame solo orale**, di circa 35-40 minuti, senza alcun supporto di IA. Si porta un **argomento a piacere**, ma imparare a memoria quello non basta: da lì partono domande di base (cos'è un vettore, una struttura dati, come si inserisce un elemento, in qualunque linguaggio) a cui si risponde **per iscritto sul foglio**, con pezzi di programma e passaggi matematici formalizzati, non a parole.
- Dal giovedì successivo subentra il dott. Luca Pepe (nome come trascritto, da verificare), che apre la parte su **probabilità, algoritmi probabilistici e randomizzati**: circa un mese, partendo dai casi più semplici.
## Prerequisiti e consigli
- **Probabilità e statistica**: primo pilastro. Non si può fare analisi di grandi dati senza nozioni profonde di statistica; le dimostrazioni assumeranno il corso del secondo anno. Da ripassare i modelli di distribuzione: **gaussiana**, **binomiale**, geometrica...
- **Algoritmi e strutture dati**: secondo pilastro. Non verranno rifatti alberi, grafi, visite, vettori, tabelle hash, problema del dizionario, ordinamento, ma vanno saputi **anche a livello implementativo** (ad es. come funziona il selection sort, come si inserisce un elemento in un albero).
- Cambia il tipo di difficoltà. In ASD il problema è ben definito (*dato un vettore, trova il minimo*) e si cerca algoritmo, correttezza, complessità, lower bound. Qui la parte difficile è **modellare il problema**: partire da dati complessi, sporchi e poco chiari, capire cosa si vuole risolvere, formalizzare il modello di dati (nel 90% dei casi un **modello statistico**) e spesso **spezzare** il problema in più sottoproblemi algoritmici da modularizzare, collegare e combinare in un pacchetto software unico.
- Il docente invita a seguire in presenza e a **studiare in piccoli gruppi**: serve a chiarire i dubbi da portare a lezione e come allenamento alla collaborazione per il mondo del lavoro.
## Cos'è il data mining
Area a cavallo tra **computer science** e **statistica**. Obiettivo: scegliere i migliori **modelli di input**, i migliori **algoritmi** e il miglior software per problemi computazionali in cui l'insieme dei dati:
- è **troppo grande** per la memoria centrale, oppure
- **non è disponibile per intero** durante l'esecuzione: l'input è **dinamico**, cambia nel tempo (anche una sequenza potenzialmente infinita, ad es. i dati di un satellite) e l'algoritmo deve aggiornarsi, calcolando indicatori come media, massimo, minimo, numero di elementi con una certa proprietà.
Il data mining completo richiederebbe 3-4 corsi: qui ci si concentra sull'**approccio algoritmico-computazionale**. Si parte sempre da un'applicazione concreta, poi si astrae il problema (modello teorico) e si torna alle applicazioni.
> [!quote] I due step del data mining
> 1. **Modellare l'input**: da un insieme grezzo di dati (una centralina meteo, un satellite, un treno) si estrae un **modello di input**, spesso con una distribuzione di probabilità, e si definisce con precisione il **task computazionale** da risolvere su di esso.
> 2. **Scegliere l'algoritmo** migliore per quel modello e quel task.

La parte difficile è la **prima**, la seconda è quella già sviluppata ad ASD. È anche la figura professionale più richiesta: l'analista che modella bene i dati e propone soluzioni efficienti.
> [!info] Dati e informazione
> Va tenuta distinta la differenza tra **dati grezzi** e **informazione**: il modello serve a estrarre l'informazione.

> [!example] Il modello gaussiano
> I dati grezzi sono numeri reali, in quantità tale da richiedere memoria infinita. Se si assume che seguano una **distribuzione gaussiana**, il modello si riduce a due numeri, **media** e **varianza**, che la caratterizzano in modo univoco e bastano per progettare algoritmi sul modello. Se la distribuzione in ingresso cambia, l'algoritmo se ne deve accorgere e adattarsi. È il tipo di modello su cui poggiano molte applicazioni di machine learning, compresi i large language model (combinazioni di gaussiane).
## Esempio: email di phishing
Non è un problema formulato come *dato un grafo, trova il cammino minimo*: bisogna prima chiedersi **cos'è una mail** per un informatico (una stringa di caratteri, un file) e **cos'è una mail di phishing**.
1. **Caratterizzazione**: nelle mail di phishing ricorrono in modo ossessivo certe parole o frasi (il "principe africano", "dammi la password", "il tuo account è scaduto, clicca qui"). Se ne scelgono circa 500.
2. **Sketch**: ogni mail diventa un **vettore booleano** di 500 (o 100) bit, con 1 se la sequenza compare e 0 altrimenti. Un testo di un mega è ridotto a pochi bit che ne catturano l'essenza *per questo scopo*: si risparmia memoria e si passa da dati grezzi a informazione.
3. **Pesi**: a ogni parola chiave si dà un peso positivo proporzionale a quanto, se presente, aumenta la probabilità di phishing (ad es. 50 per il principe, 500 per la richiesta di password).
4. **Soglia**: si somma il peso delle parole presenti; se la somma supera una soglia $\gamma$ la mail è phishing, altrimenti no.
L'algoritmo è banale (una somma e un confronto); la difficoltà sta in **quali parole**, **quali pesi** e **quale soglia**, scelte che spettano all'analista.
> [!warning] Falsi negativi e falsi positivi
> Alzando la soglia diventa più difficile essere classificati phishing: aumentano i **falsi negativi** (mail di phishing che passano il filtro). Abbassandola aumentano i **falsi positivi** (mail legittime finite in spam e mai lette).

- **Sketch diversi per scopi diversi**: la mail è sempre la stessa, ma lo sketch cambia a seconda di cosa si vuole sapere (phishing, o se è scritta in italiano corretto).
- **Online**: le mail arrivano continuamente, quindi la decisione va presa in modo online e il concetto stesso di phishing, e i pesi, vanno aggiornati nel tempo perché gli attacchi cambiano.
### Apprendimento automatico (cenno)
Gli umani sono lenti nello scegliere parole e pesi. Con il **supervised learning** si parte da un dataset enorme (ad es. di chi gestisce Gmail) già **etichettato** da umani (1 = phishing, 0 = no): il sistema si **addestra** su metà del dataset ed estrae da solo parole e pesi, poi classifica le nuove mail. Non è argomento del corso (lo si vedrà in IA e ML), ma serve a capire il confine:
- il **machine learning** rende meglio quando il task è **vago** (decidere se un film piacerà);
- le tecniche di **data mining** rendono meglio quando il task è **ben definito** (phishing sì/no).
> [!example] Predire il successo di un film
> Per un film non si può rappresentare l'intera sequenza di immagini: si estraggono decine di migliaia di **feature** (giallo, asteroidi, scene violente, adatto ai bambini...) ciascuna con un punteggio, trasformando il film in un vettore con 20.000-30.000 variabili. Il successo si predice dall'esperienza passata di film simili.
### Due scenari di analisi
- **Modello statistico**: si assume una distribuzione dei dati in ingresso.
- **Worst case dinamico**: l'algoritmo deve funzionare anche con la peggiore sequenza possibile. A differenza di ASD, dove tutto l'input è in memoria e non cambia, qui l'input arriva nel tempo e l'**avversario** conosce le mosse già fatte dall'algoritmo e sceglie l'elemento $t+1$ per peggiorarne le prestazioni. Per i problemi su stream si assume spesso questo **scenario avversario**.
## Le anomalie statistiche e il limite dell'analisi
Un'anomalia (ad es. un attacco informatico a un sito istituzionale come INPS o un ministero) si rileva confrontando la distribuzione delle richieste dei server con la **serie storica**. Ma una forte divergenza non basta per concludere che c'è un attacco: può essere una coincidenza (uno sciopero). Un'analisi troppo rigida segnala come strani eventi **del tutto probabili** su sequenze casuali: è il principio, citato nella lezione come *Bonferroni*, per cui su una sequenza molto lunga, osservata abbastanza a lungo, ogni evento raro prima o poi capita.
> [!example] Mille 1 consecutivi
> La probabilità che da un istante $t$ arrivino mille 1 di fila è bassissima su tre giorni, ma cresce osservando la sequenza per vent'anni.
### Esempio: le "gang" in un grafo di incontri
Una regione urbana con $h$ luoghi pubblici (aeroporti, stazioni, hotel, centri commerciali) e $n$ persone (insieme $U$). Per individuare gang criminali si osserva per $T$ giorni (ad es. 1000, più di tre anni) e si costruisce un **grafo** con:
- **vertici**: tutti i cittadini (insieme statico);
- **arco** tra $u$ e $v$ se esiste almeno un giorno in cui sono stati nella **stessa location** (si trascura l'ora).
Di tutto il dataset enorme (nomi di tutti i partecipanti a ogni location, ogni giorno) interessa solo il **grafo**: è il data mining. Ordini di grandezza: $n\approx 10^7$, location da migliaia a decine di migliaia. Cosa segnalerebbe un'analista? Una **clique** (un insieme di cittadini il cui sottografo indotto è completo): potrebbe essere una coalizione.
**Modello random**: ogni giorno ogni agente sceglie una location uniformemente a caso (passeggiata "da ubriaco"), quindi $\Pr[\text{agente in } \ell]\approx 1/h$. Per $T\ll h$ la probabilità che esista l'arco $\{u,v\}$ è circa
$$p\approx \frac{T}{h}$$
Fissato un sottoinsieme $S$ con $|S|=s$, tutte le $\binom{s}{2}$ coppie devono avere l'arco; essendo **eventi indipendenti** (si moltiplicano le probabilità):
$$\Pr[S \text{ clique}]\approx p^{\binom{s}{2}}\approx p^{s^2/2}$$
Ma la domanda dell'analista non riguarda un $S$ fissato: è *quante clique di dimensione $s$ ci sono in tutto il grafo*. Il **numero atteso** è
$$\mathbb{E}[\#\text{clique di dim. } s]=\binom{n}{s}\,p^{\binom{s}{2}}\approx\binom{n}{s}\,p^{s^2/2}$$
dove $\binom{n}{s}$ si approssima con **Stirling**. Se questo numero è circa 0, trovare una clique è significativo; se è grande, è un fenomeno naturale.
- Con $n\approx 10^7$ e $p\approx 1/10$, per $s=10$ il valore atteso è enorme (centinaia di migliaia di clique secondo il docente): **non indica nulla**.
- Per $s=30$ è invece trascurabile: una clique di 30 persone è un'anomalia vera, da indagare.
> [!info] Controllo dei numeri
> Con $n=10^7$ e $p=10^{-1}$: per $s=10$ si ottiene circa $10^{18}$ (quindi in realtà molto più delle centinaia di migliaia dette a lezione), per $s=30$ circa $10^{-257}$. La conclusione qualitativa non cambia.

Morale: **dipende da cosa hai assunto** (parametri e distribuzione). Certe anomalie statistiche sono perfettamente probabili e non vanno lette come significative.
## Data stream
Il processo tipico di un algoritmo di data mining: un **modello di input** (una struttura dati che lo rappresenta) più uno o più algoritmi che fanno due cose:
- **rispondere a query** degli utenti (la struttura è "a sportello");
- **aggiornarsi in modo efficiente** quando l'input cambia (arriva un elemento, ne esce uno vecchio).
> [!quote] Data stream
> Sequenza di elementi, di solito **infinita**, che arriva ad alta frequenza da una o più porte. Ogni elemento è una **tupla** (un vettore con $t$ variabili/campi; il primo è spesso detto **campo chiave**). Il sistema non può tenerla tutta: ha poca memoria e deve rispondere in modo **approssimato** mantenendo solo un piccolo **sketch**.

Esempi: Twitter e social network, dati di server e satelliti, le **transazioni bancarie** (tutti i bancomat passano per i server della banca, come tanti stream in parallelo), il traffico sulla rete pubblica di università e istituti. Su miliardi di dati continui l'unica analisi possibile è statistica: non esiste un algoritmo deterministico che estragga informazione.
> [!example] La media su una finestra
> Lo stream aggiorna ogni ora la temperatura dell'Antartide. Rispondere alla media *fino adesso* è facile; quella degli *ultimi 3 giorni* è più complessa: la finestra scorre, quindi si inserisce il dato nuovo e si **cancella** quello vecchio. Il sistema deve rispondere per **finestre arbitrarie** (3, 6, 12 giorni): mantenere solo la media globale non basta.

**Memoria gerarchica**: una cache piccola ma veloce (circa 1 GB) e un archivio molto più grande ma lento, a cui gli accessi vanno minimizzati. L'output sono le risposte alle query.
> [!quote] Sketch
> Struttura dati molto più piccola del dataset, **tarata sulla query**: deve essere abbastanza piccola e abbastanza efficace per approssimare *quella* grandezza (uno sketch per la media non serve per il numero di elementi distinti), ed **efficientemente aggiornabile** a inserimenti e cancellazioni.
### Query tipiche su stream
- **Campionamento**: mantenere un **campione uniforme** di dimensione $s\ll n$ tra gli elementi della finestra, cioè ogni elemento visto ha probabilità $\approx s/n$ di starci. Problema: all'arrivo di un nuovo elemento si decide se inserirlo e **chi togliere**, e quando un elemento esce dalla finestra va rimosso e sostituito.
- **Filtraggio**: estrarre solo le tuple con un certo campo chiave (si vedranno i **Bloom filter**).
- **Conteggio degli elementi distinti**: ad es. nella sequenza A, B, C, A, E, F, D, A, B, C contare i distinti visti finora. Soluzione banale: un vettore booleano con un bit per ogni valore possibile, ma sprecherebbe troppo spazio; si cercano soluzioni esponenzialmente più economiche.
- **Stima dei momenti**: media e **varianza** (quanto la distribuzione è concentrata sulla media: la stessa media di 60 kg può venire da persone fra 55 e 65 kg o da persone di 20 e 90 kg).
- **Elementi più frequenti**: in e-commerce, i 5 articoli più venduti del giorno su $10^6$-$10^7$ prodotti; non si può tenere la frequenza di ognuno, e la classifica cambia in continuazione.
- **Conteggio degli 1 in una finestra** di $N$ bit: l'esatto richiede spazio $\Omega(N)$ (lower bound che si dimostrerà). Con un'approssimazione si può scendere a un contatore $\log N$, poi $\log\log N$ (miglioramento esponenziale), oppure spazio $O(\sqrt{N})$ per contare gli 1 in qualunque sottofinestra.
## Page ranking
I primi motori di ricerca rappresentavano il web come un **grafo diretto**: ogni pagina è un nodo (di tutto il suo contenuto interessa solo questo) e c'è un arco $x\to y$ se $x$ contiene un link a $y$. Per ordinare le pagine per **autorevolezza** non si può affidarsi a ciò che la pagina dice di sé (*"sono un premio Nobel"*, manipolabile) né ai link **uscenti** (basterebbe linkare le pagine migliori). Conta la struttura del grafo: una pagina è autorevole se è **puntata da molte pagine a loro volta autorevoli** (la NASA o il New York Times, non la pagina del cugino). La definizione è **ricorsiva**, e si calcola dal grafo.
Un grafo con miliardi di nodi e centinaia di miliardi di archi viene così condensato in un solo valore per pagina, il **rank**: è un salto generazionale, che permette di rispondere in un millisecondo. Verrà approfondito più avanti.
