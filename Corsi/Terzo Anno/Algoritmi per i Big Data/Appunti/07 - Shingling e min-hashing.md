---
tags:
  - algoritmi-big-data
  - data-mining
  - similarita
  - min-hashing
slide: []
---
# Shingling e min-hashing
Lezione 7 (27/10/2026): dopo un riepilogo dell'ingresso nel data mining (lezione precedente, non presente negli appunti), si affronta il primo passo concreto per il problema della **similarità tra documenti**: trasformare un testo in un insieme con lo **shingling**, confrontare gli insiemi con la **similarità di Jaccard**, e comprimere la rappresentazione con il **min-hashing**, uno sketch randomizzato che preserva la similarità di Jaccard. Qui comincia a servire tutta la parte di probabilità vista nelle lezioni precedenti ([[04 - Analisi del caso medio e disuguaglianze di concentrazione#Concentrazione attorno al valore atteso]]).
## Dove ci collochiamo nel data mining
Il data mining comprende moltissimi problemi, che si possono organizzare per **tipo di dati** da gestire o per **metodologia** applicata. Il corso si colloca soprattutto su:
- **dati ad alta dimensionalità** (*high dimensional data*): ogni oggetto è un vettore in uno spazio metrico con moltissime dimensioni. In geometria computazionale nel piano la dimensione $d=2$ è una costante e si analizza l'algoritmo solo rispetto al numero di punti $n$ (come per il minimo albero ricoprente su punti del piano). Qui invece anche $d$ è un parametro rilevante: un'immagine, ad esempio, è un vettore con tante componenti quanti sono i pixel di uno schermo 4K, e un film è una sequenza enorme di questi vettori;
- **grafi**, quando bisogna modellare anche le connessioni tra i dati;
- **data stream**, in cui i dati sono potenzialmente infiniti, arrivano come un flusso, non si possono memorizzare tutti e bisogna rispondere alle query man mano ([[01 - Introduzione al corso e al data mining#Data stream]]).

Il **machine learning** (algoritmi che imparano da dati di addestramento per rispondere su input con una distribuzione statistica simile, reti neurali, LLM) non è trattato: è materia di corsi della magistrale. Di ogni argomento il corso fa vedere "l'ABC": le basi e le prime applicazioni.
## Il problema della similarità
Uno strumento centrale è il **locality-sensitive hashing**, che serve a trovare oggetti simili tra loro rispetto a una nozione di similarità ben definita. Due query collegate:
- **nearest neighbor**: dato un oggetto (ad esempio una foto) e un database di milioni di oggetti, trovare il più simile;
- **all candidate pairs** (*all documents*): dato l'intero database e una **soglia** $s$, fissata una metrica, trovare tutte le coppie di oggetti con similarità almeno $s$.

Chi sa risolvere una delle due di solito sa risolvere anche l'altra.
### La barriera quadratica
Con $N$ oggetti e un costo $h$ per confrontare una coppia, il metodo banale (ricerca esaustiva su tutte le coppie, con una matrice di bit $N\times N$ o con un vettore degli oggetti) costa tempo e/o spazio
$$O(N^2\,h)$$
Entrambi i fattori sono inaccettabili:
- con un miliardo di oggetti, $N^2$ è insostenibile;
- $h$ è enorme, perché ogni oggetto è un vettore con moltissime dimensioni (vedremo ordini come $27^{10}$).

L'obiettivo delle prossime lezioni, nel caso della **similarità tra documenti**, è avvicinarsi, con alta probabilità e non nel caso peggiore, a un costo quasi **lineare** in $N$ e a un costo per confronto **logaritmico** in $h$. Ci si arriva con una pipeline di passi: shingling, min-hashing, locality-sensitive hashing. Questa lezione copre i primi due.
## Similarità di Jaccard
Sia $U$ un universo finito, tipicamente molto grande, e siano $C_1,C_2\subseteq U$.

> [!quote] Similarità e distanza di Jaccard
> $$\mathrm{Sim}(C_1,C_2)=\frac{|C_1\cap C_2|}{|C_1\cup C_2|}\qquad d(C_1,C_2)=1-\mathrm{Sim}(C_1,C_2)$$

Con la distribuzione uniforme sui punti di $U$, la similarità di Jaccard è la **probabilità condizionata** di pescare un punto dell'intersezione sapendo di averlo pescato nell'unione:
$$\mathrm{Sim}(C_1,C_2)=\Pr[x\in C_1\cap C_2\mid x\in C_1\cup C_2]$$
(esercizio: basta applicare la definizione di probabilità condizionata). Restringendosi ai casi possibili dentro l'unione, si misura quanta "area" occupa l'intersezione.

Il passaggio fondamentale è da **oggetti concreti** (testi in Word) a **oggetti matematici** (sottoinsiemi di un universo), su cui la distanza è ben definita.
## Shingling
### La prima idea: le parole in comune
A lezione è stato proposto di confrontare due documenti contando le **parole in comune**: un vettore di bit con una componente per ogni parola del vocabolario inglese, a 1 se la parola compare nel documento. Due obiezioni:
- **la frequenza**: un bit 0/1 non distingue una parola che compare 20 volte da una che ne compare 2000, e due testi così non sono simili. Le parole molto comuni ("the") vanno poi pesate meno o tolte, il che richiede già una statistica delle frequenze;
- **l'ordine**: due testi sono tanto più simili quanto più compaiono nello stesso ordine sequenze di parole o di caratteri, e l'insieme delle parole lo perde.
### Documenti come stringhe
Sia $\Sigma$ l'alfabeto dei caratteri (per testi in inglese circa 27 caratteri, spazio compreso). Un documento è un **elemento** di $\Sigma^*$, l'insieme di tutte le stringhe finite su $\Sigma$ (non un sottoinsieme). Da qui in poi "documento" significa questo.

> [!quote] $k$-shingle
> Il **$k$-shingle** di un documento $D\in\Sigma^*$ è l'**insieme** (non ordinato, senza ripetizioni) di tutte le sottostringhe di $D$ di lunghezza esattamente $k$.

> [!example] Esempio
> Con $\Sigma=\{a,b,c\}$ e $D_1=abcab$, scorrendo il testo da sinistra a destra si incontrano $ab$, $bc$, $ca$ e di nuovo $ab$, che è già nell'insieme. Il 2-shingle di $D_1$ è
> $$\{ab,\ bc,\ ca\}$$

Si calcola con una scansione lineare del testo: nessun problema computazionale.
### Varianti
- **Multi-insiemi**: nella pratica conta anche **quante volte** compare uno shingle, e si usa un multi-insieme (nell'esempio $ab$ compare due volte). Tutto quello che si farà nel corso si estende a questo caso, ma per semplicità non lo si fa.
- **Parole come atomi**: invece dei caratteri, gli atomi possono essere le **parole** (sequenze separate da spazi). L'alfabeto diventa il vocabolario (decine di migliaia di parole) e un 3-shingle è l'insieme delle triple di parole consecutive che compaiono nel testo. Cambiano molto i parametri, ma il metodo è identico.
- **Ripulitura**: le sequenze troppo frequenti si pesano meno o si eliminano, e a volte si analizzano "col cacciavite" le frasi strutturali del dominio (testi di medicina, di geografia...). Queste scelte dipendono fortemente dall'applicazione.

> [!info] Quanto deve essere grande $k$
> In teoria $k$ è arbitrario e le soluzioni del corso valgono per ogni $k$, ma la dimensione della rappresentazione cresce **esponenzialmente** in $k$. Un $k$ più grande cattura meglio l'**ordine** in cui compaiono le cose: interi periodi identici come sequenza, non solo come parole presenti. Indicazione empirica, non una legge: $k=5$ per documenti brevi come le email (ordine di 100 KB), $k\geq10$ per documenti lunghi come i libri.

> [!warning] Modellare conta quanto gli algoritmi
> Secondo il docente il vero lavoro del data mining è questo: davanti a una nuova applicazione, trasformare un problema reale in un problema computazionale ben definito, a cui poi applicare gli algoritmi noti. La parte di modellazione è importante quanto l'analisi delle strutture dati, o di più. Il docente consiglia di leggere sul libro il capitolo sulla similarità tra documenti: sulle slide un discorso occupa tre righe, sul libro dieci pagine di esempi ed esercizi.
## La matrice delle caratteristiche
Fissati $\Sigma$ e $k$, gli shingle possibili sono $m=|\Sigma|^k$. Ogni documento $D$ è in corrispondenza biunivoca con un **vettore binario** $C(D)\in\{0,1\}^m$: una componente per ogni possibile $k$-shingle (in ordine lessicografico), a 1 se lo shingle compare in $D$.

> [!example] Esempio
> Con $\Sigma=\{a,b,c\}$ e $k=2$ i possibili shingle sono $3^2=9$: $aa,ab,ac,ba,bb,bc,ca,cb,cc$. Per $D=abcab$:
> $$C(D)=(0,1,0,0,0,1,1,0,0)$$
> Con $|\Sigma|=27$ e $k=10$ il vettore di una sola email ha $27^{10}$ componenti.

Mettendo i vettori dei documenti $1,\dots,N$ come colonne si ottiene la **matrice** (la "matriciona"): $m$ righe, una per ogni shingle possibile, e $N$ colonne, una per ogni documento.
- Il numero di righe **cresce esponenzialmente** con $k$: per questo $k$ va tenuto piccolo.
- La matrice è **estremamente sparsa**: la stragrande maggioranza degli shingle non compare mai nei testi reali ("zvczzy" in inglese non c'è). La sparsità conta molto per la compressione dei dati.
### Jaccard sulle colonne
Per due colonne:
- **denominatore**: il numero di righe in cui **almeno una** delle due ha 1 (OR), cioè la dimensione dell'unione;
- **numeratore**: il numero di righe in cui **entrambe** hanno 1 (AND), cioè la dimensione dell'intersezione.

Nell'esempio alla lavagna due colonne avevano 1 in almeno una delle due in 6 righe e in entrambe in 3 righe, quindi similarità $\frac36=\frac12$: con una soglia $s=0{,}7$ quella coppia non va restituita.

Il calcolo esatto per una coppia costa $O(m)$ (si scorrono tutte le righe), e per tutte le coppie $O(N^2m)$. Con $m=27^{10}$ anche un solo confronto è proibitivo.
## Sketch e firme
Le colonne vanno **compresse**, accettando una certa probabilità di errore: non si ottiene più la similarità di Jaccard esatta, ma una **stima** buona con una certa confidenza, mentre la rappresentazione diventa **esponenzialmente** più piccola e il confronto molto più efficiente.

Due termini da qui in poi centrali:
- **sketch** (*data sketch*): una rappresentazione con molti meno bit che conserva solo i "punti essenziali" dell'oggetto, come lo sketch di una dimostrazione;
- **firma** (*signature*): una stringa che dipende fortemente dall'oggetto; se l'oggetto cambia un po', cambia un po' anche la firma.

> [!info] Lo sketch dipende dalla distanza
> Di uno stesso vettore si possono fare infiniti sketch: la scelta dipende da cosa si vuole preservare. Per la similarità di Jaccard si vuole che, con alta probabilità, colonne con similarità **alta** abbiano sketch **uguali** e colonne con similarità **bassa** sketch **diversi**. Per verificare l'**uguaglianza** esatta servirebbe uno sketch del tutto diverso, e lo stesso cambiando distanza (Hamming, euclidea, Manhattan).

Lo schema: si calcola lo sketch di ogni colonna e si confrontano gli sketch coppia per coppia. Il fattore $N^2$ **resta** (lo si attaccherà con il locality-sensitive hashing), ma ogni confronto diventa molto più economico. Sulle sole coppie che risultano simili si può tornare alle colonne originali e calcolare la similarità esatta: questo elimina i **falsi positivi**, ma non i **falsi negativi**, che richiederebbero di ricontrollare tutte le coppie.

L'idea è una **funzione hash** che mappa ogni colonna possibile in uno tra $B$ bucket, piccola da rappresentare e veloce da calcolare, tale che colonne molto simili finiscano con alta probabilità nello stesso bucket e colonne poco simili in bucket diversi. Le colonne nello stesso bucket sono le coppie **candidate**.
## Min-hashing
L'unica componente casuale è una **permutazione $\pi$ delle righe** della matrice, scelta uniformemente tra le $m!$ permutazioni. Lo spazio di probabilità su cui si analizza tutto è questo.

> [!quote] Min-hash
> Fissata una permutazione $\pi$ delle righe, il **min-hash** di una colonna $C$ è
> $$h_\pi(C)=\text{l'indice, nell'ordine permutato da }\pi\text{, della prima riga in cui }C\text{ ha un }1$$

Una volta fissata $\pi$, $h_\pi$ è deterministica; al variare di $\pi$ casuale, $h_\pi(C)$ è una variabile aleatoria.

> [!question] Domanda tipica d'esame
> Qual è il dominio e il codominio del min-hash $h_\pi$? Traccia: fissata $\pi$, $h_\pi:\{0,1\}^m\to\{1,\dots,m\}$. Il dominio non sono le permutazioni né la matrice: sono **tutti** i possibili vettori binari di $m$ componenti, anche se in un'applicazione le colonne sono poche. Il docente avverte che domande come questa le fa, e che non basta sapere la definizione a memoria.

Rappresentare una colonna richiede $m$ bit, rappresentarne il min-hash solo $\log_2m$ bit: con $m=27^{10}$ si passa da $27^{10}$ bit a circa $10\log_227\approx48$ bit.
### Esempio
L'esempio della lezione (lo stesso delle slide del libro *Mining of Massive Datasets*) ha 4 documenti e 7 shingle:
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
## Il teorema del min-hashing
> [!quote] Teorema
> Per ogni coppia di colonne $C_1,C_2\in\{0,1\}^m$, scegliendo $\pi$ uniformemente tra le permutazioni delle righe,
> $$\Pr_\pi\big[h_\pi(C_1)=h_\pi(C_2)\big]=\mathrm{Sim}(C_1,C_2)$$

Le due colonne sono arbitrarie, anche le peggiori; lo spazio di probabilità è dato solo dalla scelta di $\pi$. L'evento non è che le colonne siano uguali, ma che i loro **min-hash** coincidano, cioè che finiscano nello stesso bucket. La probabilità di collisione cresce **linearmente** con la similarità: proprio quello che si voleva.

> [!info] Idea della dimostrazione (non svolta a lezione)
> Le righe in cui entrambe le colonne hanno 0 non contano. Tra le righe in cui almeno una ha 1 (sono $|C_1\cup C_2|$), si guardi quella che viene prima nell'ordine di $\pi$. Per la simmetria della permutazione uniforme, ognuna di queste righe ha la stessa probabilità di essere la prima. I due min-hash coincidono esattamente quando questa prima riga ha 1 in **entrambe** le colonne, cioè sta nell'intersezione: succede con probabilità $\frac{|C_1\cap C_2|}{|C_1\cup C_2|}$.
### Uno stimatore non distorto
Per una coppia di colonne $i,j$ sia
$$Z_{ij}=\begin{cases}1&\text{se }h_\pi(C_i)=h_\pi(C_j)\\0&\text{altrimenti}\end{cases}$$
È una variabile [[03 - Variabili aleatorie e valore atteso#Bernoulliana e binomiale|bernoulliana]] e per il teorema
$$\mathbb{E}[Z_{ij}]=\Pr[Z_{ij}=1]=\mathrm{Sim}(C_i,C_j)$$
Per questo il min-hashing si chiama uno **stimatore non distorto** (*unbiased*) della similarità di Jaccard.
### Stimare la similarità con più permutazioni
Il teorema non dà da solo un metodo per **stimare** la similarità, ad esempio per decidere se supera $0{,}7$. Con una sola permutazione l'esito è solo "stesso bucket o no": è come una moneta truccata che fa testa con probabilità ignota $0{,}7$, e dopo un solo lancio non si sa nulla di quel valore. Si fanno allora $t$ esperimenti **indipendenti**, con $t$ permutazioni casuali indipendenti, e si stima la similarità con la frazione di permutazioni in cui i min-hash coincidono:
$$\widehat{\mathrm{Sim}}(C_i,C_j)=\frac{\big|\{\ell: h_{\pi_\ell}(C_i)=h_{\pi_\ell}(C_j)\}\big|}{t}$$
Per la legge dei grandi numeri e per le disuguaglianze di concentrazione ([[04 - Analisi del caso medio e disuguaglianze di concentrazione#Disuguaglianza di Chebyshev|Chebyshev]], con la varianza di una somma di variabili binarie indipendenti, e i bound di Chernoff) questa frazione converge al valore atteso, cioè alla similarità vera, e si può quantificare la probabilità di errore in funzione di $t$.

L'algoritmo lavora sulla **matrice delle firme**, non sulla matrice originale: stesse $N$ colonne, ma $t$ righe invece di $27^{10}$. Questo è il punto decisivo: una tecnica di sketching serve solo se le query si possono rispondere **usando soltanto gli sketch**, senza tornare a leggere i dati originali.

> [!example] Stime e valori veri nell'esempio
> Dalla matrice delle firme, la stima per $C_1,C_2$ è $\frac03=0$, come la similarità vera ($C_1$ e $C_2$ non hanno shingle in comune). In generale le stime sbagliano: per $C_1,C_3$ la similarità vera è $\frac34=0{,}75$ e la stima $\frac23\approx0{,}67$; per $C_2,C_4$ la similarità vera è $0{,}75$ e la stima $1$. Aumentando il numero di permutazioni le stime convergono ai valori veri.

> [!question] Domanda tipica d'esame
> Definisci il min-hash di una colonna e dimostra che la probabilità che due colonne abbiano lo stesso min-hash è la loro similarità di Jaccard. Come si usa questo fatto per stimare la similarità, e con quale confidenza? Traccia: matrice shingle × documenti, permutazione casuale delle righe, prima riga con 1; stimatore non distorto; $t$ permutazioni indipendenti, frazione di coincidenze, concentrazione (Chebyshev, Chernoff).
## Prossimi passi
La lezione si interrompe qui: la discussione sulla stima con più permutazioni continua giovedì. Il min-hashing riduce il costo del singolo confronto, ma non il fattore $N^2$ delle coppie: è il compito del locality-sensitive hashing.
