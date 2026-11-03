---
tags:
  - algoritmi-big-data
  - similarita
  - data-mining
  - min-hashing
slide:
  - "Ch03-ABD-Andy_SLIDES 3.pdf"
---
# Ricerca di oggetti simili
## Trovare oggetti simili
Lezione 6 (22/10/2026), seconda parte: comincia il data mining con il problema di **trovare oggetti simili** in grandi dataset (slide Ch03-ABD-Andy_SLIDES 3, pp. 10-20: pp. 10-17 per il problema e la distanza di Jaccard, pp. 18-20 per la pipeline; i numeri di pagina sono quelli del PDF).
Il primo argomento di data mining del corso è trovare **oggetti simili** in un dataset molto grande. Le slide e gli aggiornamenti sono sul sito del libro, mmds.org, utile anche per fare esperimenti. Gli oggetti possono essere foto, documenti di testo, sequenze di DNA, proteine; in ogni caso ci sono due passi fondamentali:
1. **rappresentare** gli oggetti in memoria, in strutture dati;
2. definire cosa significa **simile**, cioè scegliere una **distanza** (una misura della similarità) efficace per l'esigenza dell'utente. Cosa vuol dire che due proteine, due immagini o due documenti sono simili dipende dall'applicazione.

Esempi:
- **nearest neighbor**: data un'immagine target e una collezione di un terabyte di immagini, trovare la più simile. Il processo può selezionarne una quarantina di potenzialmente simili e poi scegliere la migliore (lo *scene completion problem* delle slide);
- **pagine web**: un operatore che raccoglie pagine sul meteo non vuole 200 link a pagine sostanzialmente identiche, e deve farlo su miliardi di pagine che cambiano di continuo;
- **e-commerce**: trovare utenti con acquisti simili, per proporre a un utente quello che hanno comprato gli utenti simili a lui.

Un'immagine si rappresenta come una matrice di valori numerici (il colore di ogni pixel). Oltre al nearest neighbor, un'altra query importante è **all similar pairs**: data una distanza $d$ e una soglia $s$, trovare tutte le coppie di oggetti a distanza al più $s$. Di solito la distanza è tra 0 e 1 e la similarità è il suo complemento, $1-d$.

Il corso si concentra sui **documenti** di testo.

> [!info] Il problema nelle slide (dalle slide)
> Le slide (p. 14-15) formulano il problema così: dati i punti $x_1,\dots,x_N$ ad alta dimensionalità e una funzione distanza $d(x_i,x_j)$, trovare tutte le coppie con $d(x_i,x_j)\leq s$. La soluzione ingenua costa $O(N^2\cdot h)$, con $h$ la dimensione dei dati; la "magia" è farlo in $O(N\cdot h')$ con $h'\ll h$ e con alta confidenza. Nella mappa dei temi di p. 11 questo filone (*high dim. data*) comprende locality-sensitive hashing, clustering, riduzione della dimensionalità, rilevamento di documenti duplicati.
### La barriera quadratica
Se confrontare due oggetti costa $h$, il metodo banale confronta tutte le coppie e costa $O(N^2h)$. Nel mondo dei big data la barriera quadratica è come la differenza tra polinomiale ed esponenziale in teoria della complessità: con $N=10^9$ un algoritmo lineare va bene, uno quadratico ($10^{18}$) è impensabile. L'obiettivo, che richiederà circa un mese, è arrivare a $O(N\,h')$ con $h'$ molto più piccolo di $h$, con metodi randomizzati.

Le difficoltà per i documenti: come capire se due documenti sono simili, come rappresentarli in memoria, e il fatto che spesso sono troppo grandi per stare interamente in memoria.
### Distanza di Jaccard
La **distanza di Jaccard** è una metrica a tutti gli effetti, ma definita sui **sottoinsiemi** di un universo invece che su uno spazio vettoriale:
$$\mathrm{Sim}(C_1,C_2)=\frac{|C_1\cap C_2|}{|C_1\cup C_2|}\qquad d(C_1,C_2)=1-\mathrm{Sim}(C_1,C_2)$$
La similarità è sempre tra 0 (intersezione vuota) e 1 (insiemi coincidenti, unione uguale all'intersezione). Nell'esempio delle slide l'intersezione ha 3 elementi e l'unione 8: similarità $\frac38$, distanza $\frac58$.
### La pipeline
Resta da capire che relazione c'è tra documenti e sottoinsiemi. La soluzione, sviluppata nel mese successivo, ha più passi:
1. **shingling**: ogni documento viene spezzettato in "mattoncini" (*shingle*), che diventano gli elementi di un sottoinsieme;
2. **min-hashing**: gli insiemi così ottenuti sono enormi, e vengono **compressi** in oggetti esponenzialmente più piccoli che **preservano** la similarità di Jaccard: se i documenti erano simili, con alta probabilità lo sono anche le loro versioni compresse, e viceversa. Così si passa da $h$ a $h'$, ma restano $N^2$ confronti;
3. **locality-sensitive hashing**: si mappano i documenti compressi in una **tabella hash** con funzioni hash particolari, tali che nelle **liste di trabocco** finiscano tutti e soli gli elementi simili tra loro. Ogni documento si inserisce una volta sola, con costo lineare, e le liste di trabocco danno direttamente le coppie candidate.

La figura di p. 20 (dalle slide) riassume i passi e che cosa esce da ciascuno: lo shingling produce l'**insieme di stringhe di lunghezza $k$** che compaiono nel documento; il min-hashing produce le **firme**, vettori brevi di interi che rappresentano gli insiemi e ne riflettono la similarità di Jaccard; il locality-sensitive hashing produce le **coppie candidate**, cioè le coppie di firme da sottoporre a un test di similarità.

Il dettaglio di shingling e min-hashing è nella [[03 - Ricerca di oggetti simili#Shingling e min-hashing|lezione successiva]].

> [!info] Output sensitive
> Rispondendo a una domanda a fine lezione: per essere confidenti si usano molte funzioni hash (ad esempio 100), quindi un documento compare in più bucket. Il costo è comunque sotto $N^2$, ma l'algoritmo è **output sensitive**: se le coppie simili fossero dell'ordine di $N^2$, bisognerebbe comunque restituirle tutte. Nelle applicazioni pratiche le coppie simili sono molte meno di tutte le coppie. Per trovare gli oggetti simili a un dato oggetto basta calcolarne l'hash e leggere la lista di trabocco corrispondente.
### Note organizzative
La lezione del martedì finisce di solito un po' prima perché alle 11 il docente ha un altro impegno istituzionale a cui deve essere presente; come compromesso si può iniziare alle 9:05, non prima.
## Shingling e min-hashing
Lezione 7 (27/10/2026), slide Ch03-ABD-Andy_SLIDES 3 (capitolo 3 *Finding Similar Items in Large Data Sets*), pp. 11-41 del PDF (le pp. 11-20 riprendono e ripetono quanto visto alla fine della lezione 6; il materiale nuovo va da p. 21, shingling, a p. 41; adattamento del docente delle slide di Leskovec, Rajaraman e Ullman, *Mining of Massive Datasets*, mmds.org): dopo un riepilogo dell'ingresso nel data mining ([[#Trovare oggetti simili]]), si affronta il primo passo concreto per il problema della **similarità tra documenti**: trasformare un testo in un insieme con lo **shingling**, confrontare gli insiemi con la **similarità di Jaccard**, e comprimere la rappresentazione con il **min-hashing**, uno sketch randomizzato che preserva la similarità di Jaccard. Qui comincia a servire tutta la parte di probabilità vista nelle lezioni precedenti ([[02 - Algoritmi randomizzati e probabilità#Concentrazione attorno al valore atteso]]).
### Dove ci collochiamo nel data mining
Il data mining comprende moltissimi problemi, che si possono organizzare per **tipo di dati** da gestire o per **metodologia** applicata. Il corso si colloca soprattutto su:
- **dati ad alta dimensionalità** (*high dimensional data*): ogni oggetto è un vettore in uno spazio metrico con moltissime dimensioni. In geometria computazionale nel piano la dimensione $d=2$ è una costante e si analizza l'algoritmo solo rispetto al numero di punti $n$ (come per il minimo albero ricoprente su punti del piano). Qui invece anche $d$ è un parametro rilevante: un'immagine, ad esempio, è un vettore con tante componenti quanti sono i pixel di uno schermo 4K, e un film è una sequenza enorme di questi vettori;
- **grafi**, quando bisogna modellare anche le connessioni tra i dati;
- **data stream**, in cui i dati sono potenzialmente infiniti, arrivano come un flusso, non si possono memorizzare tutti e bisogna rispondere alle query man mano ([[01 - Introduzione al corso e al data mining#Data stream]]).

Il **machine learning** (algoritmi che imparano da dati di addestramento per rispondere su input con una distribuzione statistica simile, reti neurali, LLM) non è trattato: è materia di corsi della magistrale. Di ogni argomento il corso fa vedere "l'ABC": le basi e le prime applicazioni.
### Il problema della similarità
Uno strumento centrale è il **locality-sensitive hashing**, che serve a trovare oggetti simili tra loro rispetto a una nozione di similarità ben definita. Molti problemi si riducono a **trovare insiemi simili**:
- pagine con una grande frazione di parole in comune (rilevamento dei duplicati, classificazione per argomento);
- clienti che hanno comprato una grande frazione degli stessi prodotti, o prodotti con insiemi di clienti simili;
- immagini con caratteristiche simili, utenti che hanno visitato siti simili.

In generale l'input sono punti $x_1,\dots,x_N$ ad alta dimensionalità (un'immagine è un lungo vettore di colori dei pixel, $x\in\{0,1,\dots,c\}^h$ con $h$ la dimensione del dato) con una funzione distanza $d(x_i,x_j)$. Due query collegate:
- **nearest neighbor**: dato un oggetto (ad esempio una foto) e un database di milioni di oggetti, trovare il più simile. Esempio delle slide: lo *scene completion problem* (Hays e Efros, SIGGRAPH 2007), che completa una parte mancante di una foto cercando le immagini più simili in un'enorme collezione;
- **all candidate pairs** (*all documents*): dato l'intero database e una **soglia** $s$, fissata una metrica, trovare tutte le coppie di oggetti con similarità almeno $s$ (equivalentemente, con distanza $d(x_i,x_j)\leq s$ per una soglia sulla distanza).

Chi sa risolvere una delle due di solito sa risolvere anche l'altra.
#### La barriera quadratica
Con $N$ oggetti e un costo $h$ per confrontare una coppia, il metodo banale (ricerca esaustiva su tutte le coppie, con una matrice di bit $N\times N$ o con un vettore degli oggetti) costa tempo e/o spazio
$$O(N^2\,h)$$
Entrambi i fattori sono inaccettabili:
- con un miliardo di oggetti, $N^2$ è insostenibile;
- $h$ è enorme, perché ogni oggetto è un vettore con moltissime dimensioni (vedremo ordini come $27^{10}$).

L'obiettivo delle prossime lezioni (la "magia" delle slide) è un costo $O(N\,h')$ con $h'\ll h$, con alta confidenza e non nel caso peggiore: quasi **lineare** in $N$ e con un costo per confronto **logaritmico** in $h$.
#### Similarità tra documenti
L'applicazione studiata è questa: dato un numero enorme $N$ di documenti (milioni o miliardi), trovare le coppie **quasi duplicate**:
- siti mirror, esatti o approssimati, da non mostrare entrambi nei risultati di una ricerca;
- articoli simili su molti siti di notizie, da raggruppare per "stessa notizia";
- molti piccoli pezzi di un documento che compaiono, in ordine diverso, in un altro.

Le difficoltà: troppi documenti per confrontare tutte le coppie, e documenti così grandi o così tanti da non stare in memoria principale.

La soluzione è una pipeline:
1. **input**: un universo enorme di documenti;
2. **shingling**: trasforma i documenti in insiemi (grandi);
3. **min-hashing**: trasforma gli insiemi grandi in **firme** corte, vettori di interi, preservando la similarità di Jaccard;
4. **locality-sensitive hashing**: si concentra sulle coppie di firme che probabilmente vengono da documenti simili, superando la barriera $\Theta(N^2)$;
5. **output**: le coppie candidate, da verificare.

Questa lezione copre i passi 2 e 3.
### Similarità di Jaccard
Sia $U$ un universo finito, tipicamente molto grande, e siano $C_1,C_2\subseteq U$.

> [!quote] Similarità e distanza di Jaccard
> $$\mathrm{Sim}(C_1,C_2)=\frac{|C_1\cap C_2|}{|C_1\cup C_2|}\qquad d(C_1,C_2)=1-\mathrm{Sim}(C_1,C_2)$$

Per ogni applicazione bisogna prima decidere cosa significa "distanza": la scelta del corso è la distanza di Jaccard su una famiglia di sottoinsiemi. Esempio delle slide: due insiemi con 3 elementi nell'intersezione e 8 nell'unione hanno similarità $\frac38$ e distanza $\frac58$.

Con la distribuzione uniforme sui punti di $U$, la similarità di Jaccard è la **probabilità condizionata** di pescare un punto dell'intersezione sapendo di averlo pescato nell'unione:
$$\mathrm{Sim}(C_1,C_2)=\Pr[x\in C_1\cap C_2\mid x\in C_1\cup C_2]$$
(esercizio: basta applicare la definizione di probabilità condizionata). Restringendosi ai casi possibili dentro l'unione, si misura quanta "area" occupa l'intersezione.

Il passaggio fondamentale è da **oggetti concreti** (testi in Word) a **oggetti matematici** (sottoinsiemi di un universo), su cui la distanza è ben definita.
### Shingling
#### La prima idea: le parole in comune
A lezione è stato proposto di confrontare due documenti contando le **parole in comune**: un vettore di bit con una componente per ogni parola del vocabolario inglese, a 1 se la parola compare nel documento. Due obiezioni:
- **la frequenza**: un bit 0/1 non distingue una parola che compare 20 volte da una che ne compare 2000, e due testi così non sono simili. Le parole molto comuni ("the") vanno poi pesate meno o tolte, il che richiede già una statistica delle frequenze;
- **l'ordine**: due testi sono tanto più simili quanto più compaiono nello stesso ordine sequenze di parole o di caratteri, e l'insieme delle parole lo perde.
#### Documenti come stringhe
Sia $\Sigma$ l'alfabeto dei caratteri (per testi in inglese circa 27 caratteri, spazio compreso). Un documento è un **elemento** di $\Sigma^*$, l'insieme di tutte le stringhe finite su $\Sigma$ (non un sottoinsieme). Da qui in poi "documento" significa questo.

> [!quote] $k$-shingle
> Un **$k$-shingle** (o $k$-gramma) di un documento è una sequenza di $k$ **token** consecutivi che compare nel documento; i token possono essere caratteri, parole o altro. L'insieme dei $k$-shingle di $D\in\Sigma^*$, indicato con $S(D)$, è l'**insieme** (non ordinato, senza ripetizioni) di tutti i suoi $k$-shingle.

Rappresentare un documento come l'insieme delle sue parole, o delle sue parole "importanti", non funziona bene per questa applicazione: bisogna tenere conto dell'**ordine** delle parole, ed è quello che fanno gli shingle.

> [!example] Esempio
> Con $\Sigma=\{a,b,c\}$ e $D_1=abcab$, scorrendo il testo da sinistra a destra si incontrano $ab$, $bc$, $ca$ e di nuovo $ab$, che è già nell'insieme. Il 2-shingle di $D_1$ è
> $$\{ab,\ bc,\ ca\}$$

Si calcola con una scansione lineare del testo: nessun problema computazionale.
#### Varianti
- **Multi-insiemi**: nella pratica conta anche **quante volte** compare uno shingle, e si usa un multi-insieme: nell'esempio $S'(D_1)=\{ab,bc,ca,ab\}$, con $ab$ due volte. Tutto quello che si farà nel corso si estende a questo caso, ma per semplicità non lo si fa.
- **Parole come atomi**: invece dei caratteri, gli atomi possono essere le **parole** (sequenze separate da spazi). L'alfabeto diventa il vocabolario (decine di migliaia di parole) e un 3-shingle è l'insieme delle triple di parole consecutive che compaiono nel testo. Cambiano molto i parametri, ma il metodo è identico.
- **Ripulitura**: le sequenze troppo frequenti si pesano meno o si eliminano, e a volte si analizzano "col cacciavite" le frasi strutturali del dominio (testi di medicina, di geografia...). Queste scelte dipendono fortemente dall'applicazione.

> [!info] Quanto deve essere grande $k$
> L'ipotesi di lavoro è che documenti con molti $k$-shingle in comune abbiano testo simile, anche se il testo compare in ordine diverso. In teoria $k$ è arbitrario e le soluzioni del corso valgono per ogni $k$, ma la dimensione della rappresentazione cresce **esponenzialmente** in $k$. D'altra parte $k$ va scelto **abbastanza grande**: con $k$ piccolo quasi tutti i documenti contengono quasi tutti gli shingle, l'intersezione è grande e la similarità di Jaccard risulta alta senza significare nulla. Un $k$ più grande cattura meglio l'**ordine** in cui compaiono le cose: interi periodi identici come sequenza, non solo come parole presenti. Indicazione empirica, non una legge: $k=5$ va bene per documenti brevi come le email (ordine di 100 KB), $k=10$ è meglio per documenti lunghi come i libri.

> [!warning] Modellare conta quanto gli algoritmi
> Secondo il docente il vero lavoro del data mining è questo: davanti a una nuova applicazione, trasformare un problema reale in un problema computazionale ben definito, a cui poi applicare gli algoritmi noti. La parte di modellazione è importante quanto l'analisi delle strutture dati, o di più. Il docente consiglia di leggere sul libro il capitolo sulla similarità tra documenti: sulle slide un discorso occupa tre righe, sul libro dieci pagine di esempi ed esercizi.
### La matrice delle caratteristiche
Fissati $\Sigma$ e $k$, gli shingle possibili sono $m=|\Sigma|^k$. Ogni documento $D$ è in corrispondenza biunivoca con un **vettore binario** $C(D)\in\{0,1\}^m$: una componente per ogni possibile $k$-shingle (in ordine lessicografico), a 1 se lo shingle compare in $D$.

> [!example] Esempio
> Con $\Sigma=\{a,b,c\}$ e $k=2$ i possibili shingle sono $3^2=9$: $aa,ab,ac,ba,bb,bc,ca,cb,cc$. Per $D=abcab$:
> $$C(D)=(0,1,0,0,0,1,1,0,0)$$
> Con $|\Sigma|=27$ e $k=10$ il vettore di una sola email ha $27^{10}$ componenti.

Mettendo i vettori dei documenti $1,\dots,N$ come colonne si ottiene la **matrice** (la "matriciona"): $m$ righe, una per ogni shingle possibile, e $N$ colonne, una per ogni documento.
- Il numero di righe **cresce esponenzialmente** con $k$: per questo $k$ va tenuto piccolo.
- La matrice è **estremamente sparsa**: la stragrande maggioranza degli shingle non compare mai nei testi reali ("zvczzy" in inglese non c'è). La sparsità conta molto per la compressione dei dati.
#### Jaccard sulle colonne
Codificando gli insiemi come vettori binari, l'intersezione diventa l'**AND** bit a bit e l'unione l'**OR**. Per due colonne:
- **denominatore**: il numero di righe in cui **almeno una** delle due ha 1 (OR), cioè la dimensione dell'unione;
- **numeratore**: il numero di righe in cui **entrambe** hanno 1 (AND), cioè la dimensione dell'intersezione.

> [!example] Esempi
> Con $C_1=10111$ e $C_2=10011$: intersezione 3, unione 4, similarità $\frac34$, distanza $\frac14$.
>
> Nell'esempio della lezione, con 7 shingle e 4 documenti:
> $$\begin{array}{cccc}
> 1&1&1&0\\
> 1&1&0&1\\
> 0&1&0&1\\
> 0&0&0&1\\
> 1&0&0&1\\
> 1&1&1&0\\
> 1&0&1&0
> \end{array}$$
> (matrice di p. 30 delle slide) le prime due colonne hanno 1 in entrambe in 3 righe (la 1, la 2 e la 6) e in almeno una in 6 righe, quindi $\mathrm{Sim}(C_1,C_2)=\frac36=\frac12$ e $d(C_1,C_2)=\frac12$: con una soglia $s=0{,}7$ quella coppia non va restituita.

Il calcolo esatto per una coppia costa $O(m)$ (si scorrono tutte le righe), e per tutte le coppie $O(N^2m)$. Con $m=27^{10}$ anche un solo confronto è proibitivo.

> [!info] Gli ordini di grandezza
> Con $N=10^6$ documenti le coppie sono circa $\frac{N^2}{2}\approx5\cdot10^{11}$. Il min-hashing **non** evita questi $\Theta(N^2)$ confronti, ma rende ogni confronto molto più efficiente: il confronto ingenuo di due colonne in $\{0,1\}^{|U|^k}$ costa $\Theta(|U|^k)$, e con $|U|=27$ e $k=10$ è fuori portata.
### Sketch e firme
Le colonne vanno **compresse**, accettando una certa probabilità di errore: non si ottiene più la similarità di Jaccard esatta, ma una **stima** buona con una certa confidenza, mentre la rappresentazione diventa **esponenzialmente** più piccola e il confronto molto più efficiente.

Due termini da qui in poi centrali:
- **sketch** (*data sketch*): una rappresentazione con molti meno bit che conserva solo i "punti essenziali" dell'oggetto, come lo sketch di una dimostrazione;
- **firma** (*signature*): una stringa che dipende fortemente dall'oggetto; se l'oggetto cambia un po', cambia un po' anche la firma.

> [!info] Lo sketch dipende dalla distanza
> Di uno stesso vettore si possono fare infiniti sketch: la scelta dipende da cosa si vuole preservare. Per la similarità di Jaccard si vuole che, con alta probabilità, colonne con similarità **alta** abbiano sketch **uguali** e colonne con similarità **bassa** sketch **diversi**. Per verificare l'**uguaglianza** esatta servirebbe uno sketch del tutto diverso, e lo stesso cambiando distanza (Hamming, euclidea, Manhattan).

Lo schema, in tre passi:
1. si calcolano le **firme** delle colonne, piccoli riassunti delle colonne;
2. si esaminano le coppie di firme per trovare le colonne simili. È essenziale che la similarità delle firme sia legata a quella delle colonne;
3. facoltativo: si verifica che le colonne con firme simili siano davvero simili, tornando alle colonne originali e calcolando la similarità esatta.

Il fattore $N^2$ **resta** (confrontare tutte le coppie può richiedere troppo tempo: è il compito del locality-sensitive hashing), ma ogni confronto diventa molto più economico. Questi metodi possono produrre **falsi negativi**, e anche **falsi positivi** se si salta la verifica del passo 3. La verifica elimina i falsi positivi ma non i falsi negativi, che richiederebbero di ricontrollare tutte le coppie.

L'idea è una **funzione hash** $h$ che mappa ogni colonna $C$ di $m$ bit in una firma $h(C)$ con $|h(C)|\ll|C|=m$, tale che:
1. $h(C)$ sia abbastanza piccola da far stare le firme in RAM (memoria veloce);
2. se $\mathrm{Sim}(C_1,C_2)$ è alta, con alta probabilità $h(C_1)=h(C_2)$; se è bassa, con alta probabilità $h(C_1)\neq h(C_2)$.

Intuitivamente si mettono i documenti in **bucket**, aspettandosi che la maggior parte delle coppie di quasi duplicati finisca nello stesso bucket: le colonne nello stesso bucket sono le coppie **candidate**. La funzione hash dipende dalla metrica, e non tutte le metriche hanno una funzione hash adatta. Per la similarità di Jaccard c'è, ed è il min-hashing.
### Min-hashing
L'unica componente casuale è una **permutazione $\pi$ delle righe** della matrice, scelta uniformemente tra le $m!$ permutazioni. Lo spazio di probabilità su cui si analizza tutto è questo.

> [!quote] Min-hash
> Fissata una permutazione $\pi$ delle righe, il **min-hash** di una colonna $C$ è
> $$h_\pi(C)=\text{l'indice, nell'ordine permutato da }\pi\text{, della prima riga in cui }C\text{ ha un }1$$

Una volta fissata $\pi$, $h_\pi$ è deterministica; al variare di $\pi$ casuale, $h_\pi(C)$ è una variabile aleatoria. Nelle slide si scrive anche $h_\pi(C)=\min(\pi(C))$. La strategia pratica è usare **più** permutazioni casuali indipendenti (ad esempio 100) per costruire la firma di $C$.

> [!question] Domanda tipica d'esame
> Qual è il dominio e il codominio del min-hash $h_\pi$? Traccia: fissata $\pi$, $h_\pi:\{0,1\}^m\to\{1,\dots,m\}$. Il dominio non sono le permutazioni né la matrice: sono **tutti** i possibili vettori binari di $m$ componenti, anche se in un'applicazione le colonne sono poche. Il docente avverte che domande come questa le fa, e che non basta sapere la definizione a memoria.

Rappresentare una colonna richiede $m$ bit, rappresentarne il min-hash solo $O(\log m)$ bit, perché è soltanto un indice di riga della matrice: con $m=27^{10}$ si passa da $27^{10}$ bit a circa $10\log_227\approx48$ bit.
#### Esempio
L'esempio della lezione (slide 37 e 41) ha 4 documenti e 7 shingle:
$$\begin{array}{c|cccc}
 & C_1 & C_2 & C_3 & C_4\\\hline
1 & 1 & 0 & 1 & 0\\
2 & 1 & 0 & 0 & 1\\
3 & 0 & 1 & 0 & 1\\
4 & 0 & 1 & 0 & 1\\
5 & 0 & 1 & 0 & 1\\
6 & 1 & 0 & 1 & 0\\
7 & 1 & 0 & 1 & 0
\end{array}$$
Le permutazioni si scrivono indicando per ogni riga la posizione in cui finisce. Ad esempio la prima (marrone alla lavagna), $\pi_1=(2,3,7,6,1,5,4)$, manda la riga 1 in posizione 2, la riga 2 in posizione 3, la riga 3 in posizione 7, e così via. Il min-hash di una colonna è allora la **più piccola posizione** tra le righe in cui la colonna ha 1.
- $C_1$ ha 1 nelle righe 1, 2, 6, 7, che finiscono nelle posizioni 2, 3, 5, 4: $h_{\pi_1}(C_1)=2$.
- $C_2$ ha 1 nelle righe 3, 4, 5, che finiscono nelle posizioni 7, 6, 1: $h_{\pi_1}(C_2)=1$.

Con le altre due permutazioni $\pi_2=(4,2,1,3,6,7,5)$ e $\pi_3=(3,4,7,2,6,1,5)$ si ottiene la **matrice delle firme** (una riga per permutazione, una colonna per documento):
$$\begin{array}{c|cccc}
 & C_1 & C_2 & C_3 & C_4\\\hline
\pi_1 & 2 & 1 & 2 & 1\\
\pi_2 & 2 & 1 & 4 & 1\\
\pi_3 & 1 & 2 & 1 & 2
\end{array}$$
Ad esempio $h_{\pi_2}(C_3)=4$ e $h_{\pi_3}(C_4)=2$, come verificato a lezione.

> [!warning] Refusi nelle slide dell'esempio
> Nella slide 37 l'intestazione della matrice delle firme riporta $\langle\pi_1,\pi_2,\pi_2\rangle$: è un refuso per $\langle\pi_1,\pi_2,\pi_3\rangle$. Nella tabella finale (slide 41) la similarità vera della coppia $C_1$-$C_3$ è scritta $6/7$, ma dalla matrice risulta $\frac34$ ($C_1$ ha 1 nelle righe 1, 2, 6, 7, $C_3$ nelle righe 1, 6, 7: intersezione 3, unione 4); il valore $0{,}75$ degli appunti è quello giusto, ricalcolato con Python insieme alle firme.
### Il teorema del min-hashing
> [!quote] Teorema
> Per ogni coppia di colonne $C_1,C_2\in\{0,1\}^m$, scegliendo $\pi$ uniformemente tra le permutazioni delle righe,
> $$\Pr_\pi\big[h_\pi(C_1)=h_\pi(C_2)\big]=\mathrm{Sim}(C_1,C_2)$$

Le due colonne sono arbitrarie, anche le peggiori; lo spazio di probabilità è dato solo dalla scelta di $\pi$. L'evento non è che le colonne siano uguali, ma che i loro **min-hash** coincidano, cioè che finiscano nello stesso bucket. La probabilità di collisione cresce **linearmente** con la similarità: proprio quello che si voleva.
#### Dimostrazione
A lezione il docente ha detto di "lasciar perdere la dimostrazione" per concentrarsi sull'uso del teorema; la dimostrazione è nelle slide (pagina 39).
- Sia $X$ una colonna (l'insieme dei suoi shingle) e $y\in X$. Allora $\Pr[\pi(y)=\min(\pi(X))]=\frac1{|X|}$: con una permutazione uniforme ogni riga di $X$ ha la stessa probabilità di finire nella posizione più piccola.
- Sia $y$ la riga tale che $\pi(y)=\min(\pi(C_1\cup C_2))$; per il punto precedente è uniforme su $C_1\cup C_2$. Le righe con 0 in entrambe le colonne non contano.
- Allora $\pi(y)=\min(\pi(C_1))$ se $y\in C_1$, oppure $\pi(y)=\min(\pi(C_2))$ se $y\in C_2$: una delle due colonne deve avere 1 nella riga $y$.
- I due min-hash coincidono esattamente quando valgono entrambe, cioè quando $y\in C_1\cap C_2$. Quindi
$$\Pr[\min(\pi(C_1))=\min(\pi(C_2))]=\frac{|C_1\cap C_2|}{|C_1\cup C_2|}=\mathrm{Sim}(C_1,C_2)\qquad\blacksquare$$
#### Uno stimatore non distorto
Per una coppia di colonne $i,j$ sia
$$Z_{ij}=\begin{cases}1&\text{se }h_\pi(C_i)=h_\pi(C_j)\\0&\text{altrimenti}\end{cases}$$
È una variabile [[02 - Algoritmi randomizzati e probabilità#Bernoulliana e binomiale|bernoulliana]] e per il teorema
$$\mathbb{E}[Z_{ij}]=\Pr[Z_{ij}=1]=\mathrm{Sim}(C_i,C_j)$$
Per questo il min-hashing si chiama uno **stimatore non distorto** (*unbiased*) della similarità di Jaccard.
#### Stimare la similarità con più permutazioni
Il teorema non dà da solo un metodo per **stimare** la similarità, ad esempio per decidere se supera $0{,}7$. Con una sola permutazione l'esito è solo "stesso bucket o no": è come una moneta truccata che fa testa con probabilità ignota $0{,}7$, e dopo un solo lancio non si sa nulla di quel valore. Per aumentare la **confidenza** si usano più firme min-hash, mutuamente indipendenti: la firma di $C$ diventa il vettore $\mathrm{SIG}(C)=\langle h_{\pi_1}(C),\dots,h_{\pi_t}(C)\rangle$.

> [!quote] Similarità tra firme
> La similarità $\text{Sign-Sim}(C_1,C_2)$ di due firme $\mathrm{SIG}(C_1)$ e $\mathrm{SIG}(C_2)$ è la frazione delle funzioni min-hash scelte su cui le due firme coincidono:
> $$\text{Sign-Sim}(C_1,C_2)=\frac{\big|\{\ell: h_{\pi_\ell}(C_1)=h_{\pi_\ell}(C_2)\}\big|}{t}$$

È una media delle $t$ variabili $Z$, il cui valore atteso è la similarità di Jaccard: l'obiettivo è stimare $\Pr[Z=1]$.
Per la legge dei grandi numeri e per le disuguaglianze di concentrazione ([[02 - Algoritmi randomizzati e probabilità#Disuguaglianza di Chebyshev|Chebyshev]], con la varianza di una somma di variabili binarie indipendenti, e i bound di Chernoff) questa frazione converge al valore atteso, cioè alla similarità vera, e si può quantificare la probabilità di errore in funzione di $t$.

L'algoritmo lavora sulla **matrice delle firme**, non sulla matrice originale: stesse $N$ colonne, ma $t$ righe invece di $27^{10}$. Questo è il punto decisivo: una tecnica di sketching serve solo se le query si possono rispondere **usando soltanto gli sketch**, senza tornare a leggere i dati originali.

> [!example] Stime e valori veri nell'esempio
> Dalla matrice delle firme, la stima per $C_1,C_2$ è $\frac03=0$, come la similarità vera ($C_1$ e $C_2$ non hanno shingle in comune). In generale le stime sbagliano: per $C_1,C_3$ la similarità vera è $\frac34=0{,}75$ e la stima $\frac23\approx0{,}67$; per $C_2,C_4$ la similarità vera è $0{,}75$ e la stima $1$; per $C_3,C_4$ entrambe valgono 0 (la tabella di slide 41 riassume tutto: coppie 1-3, 2-4, 1-2, 3-4, similarità vera $\frac34$, $0{,}75$, 0, 0, stima dalle firme $\frac23$, $1$, 0, 0). Aumentando il numero di permutazioni le stime convergono ai valori veri.

> [!question] Domanda tipica d'esame
> Definisci il min-hash di una colonna e dimostra che la probabilità che due colonne abbiano lo stesso min-hash è la loro similarità di Jaccard. Come si usa questo fatto per stimare la similarità, e con quale confidenza? Traccia: matrice shingle × documenti, permutazione casuale delle righe, prima riga con 1; stimatore non distorto; $t$ permutazioni indipendenti, frazione di coincidenze, concentrazione (Chebyshev, Chernoff).
### Prossimi passi
La lezione si interrompe qui, a pagina 41 delle slide: la discussione sulla stima con più permutazioni continua giovedì (dalla pagina 42: l'algoritmo randomizzato che restituisce $\text{Sign-Sim}$ con $t$ permutazioni, la concentrazione, lo spazio $\Theta(t\log m)$ della firma e il trucco di sostituire le permutazioni con funzioni hash sulle righe). Il min-hashing riduce il costo del singolo confronto, ma non il fattore $N^2$ delle coppie: è il compito del locality-sensitive hashing.
## Locality-sensitive hashing
Lezione 8 (29/10/2026), slide Ch03-ABD-Andy_SLIDES 3, pp. 42-63 del PDF (più la dimostrazione di p. 39; le pp. 64-69, algoritmo, tabella, S-curve e riepilogo, sono riassunte in fondo come "dalle slide"): si dimostra il [[03 - Ricerca di oggetti simili#Il teorema del min-hashing|teorema del min-hashing]], si discute il costo di generare permutazioni casuali e come le si sostituisce in pratica con funzioni hash, e si affronta l'ultimo passo della pipeline: il **locality-sensitive hashing** (LSH) con la tecnica delle **bande**, che supera la barriera quadratica.
### Ripresa: una funzione hash con località
Si riparte dalla matrice shingle × documenti: $m=|U|^k$ righe, una per ogni $k$-shingle possibile, e $N$ colonne, una per documento, con 1 nella riga $i$ e colonna $j$ se l'$i$-esimo shingle compare nel $j$-esimo documento. La matrice è sparsa, e calcolare la similarità di Jaccard di due colonne è banale (righe con 1 in entrambe diviso righe con 1 in almeno una), ma la matrice è enorme: già con $k$ tra 5 e 10 il numero di righe è impresentabile.

> [!info] Due idee di hashing opposte
> Nelle funzioni hash dei **dizionari** si vuole che, **qualunque** sia la coppia di chiavi, la probabilità che finiscano nello stesso slot sia bassa: la collisione non deve dipendere da come si chiamano le chiavi. Qui serve una proprietà di **località**: se due colonne si assomigliano (hanno molti 1 in comune) la probabilità di collisione deve **aumentare**, se sono distanti deve diminuire. Le funzioni hash dei dizionari serviranno comunque, più avanti.
### Dimostrazione del teorema del min-hashing
La dimostrazione, saltata nella lezione precedente, è quella delle slide (pagina 39).
- Sia $X$ una colonna e $y$ una riga in cui $X$ ha 1. Con una permutazione uniforme, $y$ è la prima riga con 1 nell'ordine permutato con probabilità $\frac1{|X|}$, dove $|X|$ è il **numero di 1** della colonna: tra tutti gli 1 di $X$ c'è un solo caso favorevole, che $y$ venga prima di tutti gli altri, e la permutazione non favorisce nessuno. Gli 0 non contano, possono finire dove vogliono.
- Per due colonne $C_1,C_2$, i casi possibili per la posizione del primo 1 dell'**unione** sono le righe con 1 in almeno una delle due colonne, tutti equiprobabili.
- I due min-hash coincidono esattamente quando quella riga ha 1 in **entrambe** le colonne: i casi favorevoli sono le righe di $C_1\cap C_2$. Quindi la probabilità è $\frac{|C_1\cap C_2|}{|C_1\cup C_2|}$.

Tutto si basa sul fatto che la permutazione sia scelta **uniformemente**: se alcuni indici fossero privilegiati, ogni posizione avrebbe una probabilità diversa e non basterebbe contare casi favorevoli su casi possibili.
### Stima con $t$ permutazioni
Con una sola permutazione la stima è 1 o 0: se la similarità vera è $0{,}7$ si direbbe 1 oppure 0, con una varianza enorme. Si usano allora $t$ permutazioni indipendenti e si fa la media:

```pseudo
\begin{algorithm}
\caption{Doc-Pair-Check($C_1$, $C_2$, $t$)}
\begin{algorithmic}
\For{$j = 1$ \textbf{to} $t$}
	\State scegli uniformemente a caso una permutazione $\pi_j$ delle $m$ righe
	\State calcola $h_{\pi_j}(C_1)$ e $h_{\pi_j}(C_2)$
\EndFor
\State \Return $\text{Sign-Sim}(C_1, C_2) = |\{j : h_{\pi_j}(C_1) = h_{\pi_j}(C_2)\}| / t$
\end{algorithmic}
\end{algorithm}
```

$\text{Sign-Sim}(C_1,C_2)$ non è uguale a $\mathrm{Sim}(C_1,C_2)$, ma per il teorema ne è il valore atteso, quindi converge a $\mathrm{Sim}(C_1,C_2)$ per $t\to\infty$ (corollario del teorema). Le $t$ variabili binarie "le due colonne collidono con la permutazione $j$" sono indipendenti, quindi valgono i risultati di concentrazione (Chebyshev, [[02 - Algoritmi randomizzati e probabilità#I bound di Chernoff|Chernoff]]) e la convergenza è esponenziale.

Nella pratica bastano circa **100** permutazioni. Ogni elemento della firma è un indice di riga, quindi occupa $\Theta(\log m)$ bit, e la firma di una colonna $\Theta(t\log m)$ bit: con $t=100$, circa 400 byte. Il passaggio da $m$ a $\log m$ ha quindi una costante davanti, $t\approx100$, del tutto accettabile visto che $m$ è dell'ordine dei miliardi. La matrice originale $M$ con $m$ righe diventa la **matrice delle firme** $\mathrm{SIG}$ con $t$ righe da $\log m$ bit.
### Il costo delle permutazioni casuali
Per calcolare i min-hash bisogna generare e tenere in memoria le permutazioni. Le permutazioni di $m$ elementi sono $m!$; numerandole (ad esempio per numero di inversioni) e mettendole in corrispondenza biunivoca con stringhe binarie, il modo migliore per sceglierne una uniformemente è generare a caso, bit per bit, una stringa di
$$\log_2(m!)\approx m\log m\ \text{bit}$$
(con l'approssimazione di Stirling), cioè un costo **superlineare** in $m$. Con $m=27^{10}$ anche generare e memorizzare una sola permutazione è un problema, e ne servono $t$ indipendenti.

In pratica si sostituiscono le $t$ permutazioni delle righe con $t$ **funzioni hash** sulle righe: ordinare le righe secondo $f_i(j)$ dà una permutazione "quasi" casuale. Una funzione hash casuale classica è
$$h_{a,b}(x)=\big((a\cdot x+b)\bmod p\big)\bmod m$$
con $a,b$ interi casuali e $p$ un numero primo maggiore di $m$: per rappresentarla bastano $O(\log m)$ bit invece di $m\log m$.

```pseudo
\begin{algorithm}
\caption{Signature-Matrix($M$, $f_1, \dots, f_t$)}
\begin{algorithmic}
\For{ogni colonna $C = 1, \dots, N$ e ogni $i = 1, \dots, t$}
	\State $\mathrm{SIG}(i, C) \gets \infty$
\EndFor
\For{ogni riga $j = 1, \dots, m$ di $M$}
	\For{ogni colonna $C = 1, \dots, N$}
		\If{$M(j, C) = 1$}
			\For{$i = 1$ \textbf{to} $t$}
				\If{$f_i(j) < \mathrm{SIG}(i, C)$}
					\State $\mathrm{SIG}(i, C) \gets f_i(j)$
				\EndIf
			\EndFor
		\EndIf
	\EndFor
\EndFor
\end{algorithmic}
\end{algorithm}
```

Le iterazioni sono $\Theta(mN)$, ma i $t$ hash si calcolano solo dove $M(j,C)=1$, che in una matrice sparsa capita raramente.

> [!warning] Teoria e pratica
> Una permutazione non crea **collisioni**: indici diversi finiscono sempre in posizioni diverse. Una funzione hash che manda $m$ indici in circa $m$ bucket con probabilità uniforme (lo stesso esperimento delle [[02 - Algoritmi randomizzati e probabilità#Bilanciamento del carico|palline nelle scatole]]) invece ne crea qualcuna: due righe possono avere lo stesso valore, e due colonne possono risultare con lo stesso min-hash non perché sono simili ma per una collisione. In pratica questi errori si trascurano: con un centinaio di funzioni hash sono rari e la media funziona bene. Il min-hashing è progettato e analizzato con le permutazioni, ed è usato con funzioni hash che minimizzano le collisioni, molto più efficienti; empiricamente funziona bene.
### Perché serve il locality-sensitive hashing
Il quadro: documenti → $k$-shingle → matrice di $m$ righe → matrice delle firme di $t\log m$ righe. Il min-hashing ha reso efficiente il confronto di **una** coppia fissata, ma per rispondere alla domanda originale, tutte le coppie candidate con similarità almeno $s$, bisogna ancora confrontare tutte le coppie: il fattore $N^2$ resta.

> [!example] Gli ordini di grandezza
> Con $N=10^6$ documenti le coppie sono $\binom N2\approx5\cdot10^{11}$. Con $10^6$ confronti al secondo e circa $10^5$ secondi in un giorno servono circa 5 giorni; con $N=10^7$ più di un anno.

L'obiettivo dell'LSH: data una soglia $s$ (ad esempio $0{,}8$, un parametro di input), una funzione che dice se due documenti sono una **coppia candidata**, da verificare poi in modo più accurato. Da qui in poi si lavora solo sulla matrice delle firme $\mathrm{SIG}(i,C)$, dimenticando la matrice $M$.

> [!quote] Coppia candidata
> Fissata una soglia $0<s<1$, le colonne $x$ e $y$ di $\mathrm{SIG}$ sono una coppia candidata se
> $$\frac{|\{i\in[t]:\mathrm{SIG}(i,x)=\mathrm{SIG}(i,y)\}|}{t}\geq s$$

L'ipotesi di lavoro è che due documenti abbiano la stessa similarità delle loro firme (grazie al corollario del teorema). La similarità di due firme non viene da piccole differenze nei valori: la distanza tra due indici non ha alcun significato. Contano solo i valori **identici**.
### Hashing delle firme intere
L'idea più semplice: si considera la firma di un documento (ad esempio $(2,1,2)$) come la sua **chiave** e la si manda, con una normale funzione hash dei dizionari, in una tabella con abbastanza bucket da rendere improbabili le collisioni tra chiavi diverse. Firme identiche finiscono sicuramente nello stesso bucket, firme diverse con alta probabilità in bucket diversi. Le coppie candidate si leggono dalle **liste di trabocco**: il costo è lineare per inserire i documenti, e poi **proporzionale all'output**, cioè al numero di coppie simili, che in un dataset grande sono molte meno di $N^2$.

Il problema è che il criterio è troppo forte: due firme sono considerate uguali solo se coincidono in **tutte** le $t$ componenti (un AND). Due colonne con similarità $0{,}75$ superano il test con probabilità $0{,}75^{100}\approx3\cdot10^{-13}$, e anche due firme uguali in 99 componenti su 100 finiscono quasi certamente in bucket diversi.

Il problema "tutte le coppie con similarità almeno $s$" ha una risposta **a gradino**: la funzione ideale vale 0 sotto la soglia e 1 sopra. Il min-hashing da solo dà una retta (la probabilità di collisione è la similarità); l'AND su $t$ componenti dà una curva che crolla verso zero al crescere di $t$. Serve una combinazione di AND e OR.
### La tecnica delle bande
Si divide la matrice delle firme in $b$ **bande** di $r$ righe ciascuna, con $b\cdot r=t$ (ad esempio 20 bande da 5 righe). La numerazione delle righe è fissata una volta per tutte e le bande non si sovrappongono.
- Per **ogni banda**, la porzione di ogni colonna in quella banda si manda con una funzione hash in una tabella con $c$ bucket, con $c$ abbastanza grande rispetto a $r$ da evitare con alta probabilità le collisioni tra porzioni diverse.
- Due colonne sono **candidate** se finiscono nello stesso bucket in **almeno una** banda.

Dentro una banda si fa l'AND sulle righe, tra le bande l'OR. Per l'analisi si assume che "stesso bucket" significhi "identiche in quella banda" (*perfect hashing*): l'ipotesi serve solo a semplificare l'analisi, non alla correttezza dell'algoritmo; nelle applicazioni reali si usa l'hashing universale.

> [!example] Esempio: $N=10^5$, $t=100$, $b=20$, $r=5$, $s=0{,}8$
> Con 100.000 documenti e firme di 100 interi, le firme occupano 40 MB. Si vogliono le coppie con similarità almeno $0{,}8$.
> - **Coppia simile**, $\mathrm{Sim}(C_1,C_2)=0{,}8$: si vuole che sia candidata. La probabilità che sia identica in una banda è $0{,}8^5\approx0{,}328$; che non sia identica in nessuna delle 20 bande è $(1-0{,}328)^{20}\approx0{,}00035$. Solo circa una coppia su 3000 è un **falso negativo**: si trova il 99,965% delle coppie simili.
> - **Coppia dissimile**, $\mathrm{Sim}(C_1,C_2)=0{,}3$: si vuole che non sia candidata. La probabilità che sia identica in una banda è $0{,}3^5=0{,}00243$; che lo sia in almeno una banda è $1-(1-0{,}00243)^{20}\approx0{,}0474$. Circa il 4,75% di queste coppie diventa candidato (le slide scrivono 0,0474, troncando $0{,}04749$): sono **falsi positivi**, da esaminare per scoprire che sono sotto la soglia.
### La curva a S
In generale, se due documenti hanno similarità $x$:
$$\Pr[\text{tutte le righe di una banda uguali}]=x^r\qquad\Pr[\text{nessuna banda identica}]=(1-x^r)^b$$
$$\Pr[\text{coppia candidata}]=1-(1-x^r)^b$$
Questa funzione di $x$ non è un gradino, ma ha una forma a **S** con un flesso vicino alla soglia
$$s\approx\left(\frac1b\right)^{1/r}$$
Con $b=20$ e $r=5$ la soglia è circa $0{,}55$, e il salto è netto: la probabilità di essere candidata passa da circa $0{,}19$ con similarità $0{,}4$ a circa $0{,}80$ con similarità $0{,}6$. Con una sola banda di una sola riga ($r=1$) si torna alla retta del min-hashing, un pessimo comportamento a soglia.

> [!example] Tabella per $b=20$, $r=5$ (dalle slide, p. 65)
> Probabilità che almeno una banda sia identica, $1-(1-x^5)^{20}$, in funzione della similarità $x$ (valori ricalcolati con Python, coincidono con le slide):
>
> | $x$ | 0,2 | 0,3 | 0,4 | 0,5 | 0,6 | 0,7 | 0,8 |
> |---|---|---|---|---|---|---|---|
> | probabilità | 0,006 | 0,047 | 0,186 | 0,470 | 0,802 | 0,975 | 0,9996 |
>
> La soglia teorica $(1/20)^{1/5}\approx0{,}549$ è la zona in cui la curva sale più rapidamente.

> [!warning] Soglia e valori citati a lezione
> A lezione il flesso per $b=20$, $r=5$ è stato indicato a $0{,}5$, e la probabilità a $0{,}4$ a $0{,}1$ (e "da $0{,}2$ a $0{,}8$" tra $0{,}4$ e $0{,}6$). Con le formule il flesso è circa $0{,}55$ e la probabilità vale $0{,}186$ a $0{,}4$ e $0{,}802$ a $0{,}6$, come nella tabella delle slide: i valori a voce sono approssimazioni del docente, quelli degli appunti sono corretti.

> [!info] Come si scelgono $b$ e $r$
> Si fa "reverse engineering": data la soglia $s$ desiderata, si scelgono $b$ e $r$ tali che $(1/b)^{1/r}\approx s$; le coppie possibili sono infinite. Poi:
> - aumentare $t=b\cdot r$ rende la curva più ripida, sempre più simile a un gradino (non lo diventa mai, è continua), ma la firma diventa più grande;
> - a $t$ fissato (ad esempio una memoria che regge 100 hash), aumentare $b$ (e diminuire $r$) riduce i **falsi negativi** e aumenta i **falsi positivi**, perché si fa l'OR su più bande; aumentare $r$ fa il contrario, perché l'AND dentro ogni banda è più severo (dalle slide, p. 61: $\Pr[\exists\text{ banda identica}]=1-(1-x^r)^b$ **cresce con $b$** e **decresce con $r$**). Ad esempio con 15 bande da 5 righe invece di 20 i falsi positivi diminuiscono e i falsi negativi aumentano.
>
> I falsi positivi si possono eliminare verificando le coppie candidate sulle colonne vere; i falsi negativi no, se non tornando al metodo esaustivo. Per ridurli al massimo si aumenta $b$ e si diminuisce $r$.

> [!info] Esercizio delle slide: perché l'LSH supera la barriera $\Theta(N^2)$ (p. 51, risposta ricavata dagli appunti)
> Ogni documento viene inserito una volta per banda ($b$ inserimenti per documento, lineari in $N$) e le coppie candidate si leggono dalle liste di trabocco: il costo è lineare in $N$ più il numero di candidate, cioè **output sensitive**. Funziona quando le coppie davvero simili sono molte meno di $N^2$, come nelle applicazioni pratiche.

> [!info] Similarità e transitività
> Rispondendo a una domanda: se $A$ è simile all'80% a $B$ e a $C$, non segue che $B$ e $C$ siano simili all'80%. Per questo il criterio è sulle **coppie**: due colonne sono candidate se almeno una delle loro $b$ sottofirme finisce nello stesso bucket. Per ogni documento si guardano dove finiscono tutte le sue $b$ sottofirme, non una sola firma.
### Dalle slide, non visto a lezione
Pagine 64-69 delle slide, riassunte in modo sintetico (la tecnica è quella di [[#La tecnica delle bande]]).
- **Obiettivo algoritmico** (p. 64). Dati le colonne della matrice delle firme $\mathrm{SIG}$ e la soglia $s$ ($0<s\leq1$), trovare le coppie con similarità delle firme almeno $s$: si applica la tecnica delle bande scegliendo $b$ e $r$ con $b\cdot r\leq t$ (le slide scrivono $\leq$, mentre sopra si è usato $b\cdot r=t$, il caso in cui si usano tutte le righe) e $(1/b)^{1/r}\approx s$. L'output sono le coppie con le $r$ righe identiche in **almeno una** banda. Taratura: aumentare $b$ diminuisce i falsi negativi, aumentare $r$ diminuisce i falsi positivi.
- **Scelta di $r$ e $b$: la S-curve** (p. 66). Con $t=50$ ($r=5$, $b=10$) la curva è quella a S, con soglia vicina a $0{,}6$; l'**area blu** (sopra la curva ideale a gradino, a destra della soglia) è il tasso di falsi negativi, l'**area verde** (sotto, a sinistra della soglia) è il tasso di falsi positivi.
- **Riepilogo LSH** (p. 67). Si tarano $b$ e $r$ per prendere quasi tutte le coppie con firme simili ed eliminare la maggior parte delle altre, scelta più bilanciata $s\approx(1/b)^{1/r}$. Poi si controlla in memoria centrale che le coppie candidate abbiano davvero firme simili (stessi valori in molte righe) e, facoltativamente, con un ulteriore passaggio sui dati, che i documenti siano davvero simili, per evitare i falsi positivi.
- **Riepilogo dei tre passi** (pp. 68-69). Shingling: ogni $k$-shingle riceve un identificativo tramite hashing (una riga della matrice grande $M$); la similarità di Jaccard è definita su sottoinsiemi. Min-hashing: hashing che preserva la similarità, con $\Pr[h_\pi(C_1)=h_\pi(C_2)]=\mathrm{sim}(C_1,C_2)$, e funzioni hash al posto delle permutazioni. LSH: hashing per trovare le coppie candidate con similarità $\geq s$ (tecnica delle bande).

> [!question] Domanda tipica d'esame
> Perché il min-hashing da solo non basta a trovare tutte le coppie simili? Descrivi la tecnica delle bande e calcola la probabilità che due documenti con similarità $x$ diventino una coppia candidata. Come scegli $b$ e $r$ per una soglia $s$, e come influiscono su falsi positivi e falsi negativi?
