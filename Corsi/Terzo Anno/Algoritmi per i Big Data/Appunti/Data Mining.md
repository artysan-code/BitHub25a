Lo scopo del *Data Mining* è di trovare i migliori **Modelli** e **Algoritmi** per risolvere problemi su grandi e complessi **Input Data Sets** in diverse materie (Scienza, Medicina, E-commerce, ... ).

Possiamo generalizzare l'analisi e la risoluzione di problemi in *step*:
- **1° Step**, analizzare il *Data Set* in input e trasformarlo in un *modello o struttura* formale **Z** così che il problema principale viene ridotto ad una semplice **Task Computazionale T** su Z.
- **2° Step**, trovare il miglior algoritmo per risolvere $T_{p}$ su Z.

Generalmente lo step più complesso è il primo, creata la struttura dati basta cercare un modello / algoritmo standard avanzato.

#### Un problema reale: Email di Phishing 
Proviamo a trovare una soluzione algoritmica generica per il problema del phishing:
- **1° Step**, un utente crea e classifica le email in due sottoinsiemi principali: *Phishing* / *Non-Phishing*.
- **2° Step**, estrai parole, o frasi, utilizzate spesso nelle *email di phishing* (come ad esempi "Principe Nigeriano").
- **3° Step**, assegna valori positivi alle *parole di phishing* e negativi agli altri.
- **4° Step**, per ciascuna email in arrivo eseguiamo una *somma* dei valori; se supera un certo *threshold* che chiamiamo $\gamma$ allora le segnaliamo come *Phishing*, altrimenti le impostiamo *Non-Phishing*.

Il 2° Step corrisponde al definire un **Modello Statistico** *M* adatto (Ad esempio una Distribuzione di Probabilità) sull'insieme grezzo di dati (le email) in modo che le informazioni che vogliamo escano come un evento probabile di *M*.

Il 3° Step invece impone di trovare un *giusto* peso o valore per le parole, proporzionale alla probabilità che si tratti di phishing.

## Data Streams
In questo caso diversi elementi arrivano in input ad una *rapida frequenza*, da una o più porte di input che chiamiamo *Streams*. Ciascun elemento viene generalmente fornito in t-uples.

Il sistema non può però contenere tutto lo *Stream* **S**, ma solo in piccoli batch che possono essere mantenuti e aggiornati. Quindi come si rispondo delle *critical queries* su **S** usando una memoria limitata?

![[md1.png]]

Le tipologie di query che possiamo svolgere su una **Data Stream (DS)** possono essere le seguenti:
- Eseguire un *campionamento dei dati* (Creare un sample)
- *Filtraggio* (Selezionare elementi con proprietà x)
- *Conteggio degli elementi distinti* (numero di elementi distinti negli ultimi k elementi)
- *Stima dei momenti* (stima della media e della deviazione standard degli ultimi k elementi)
- *Individuazione* dei k elementi più frequenti


## Lezione
#### Page ranking
Distribuzione Probabilistica di una *Random Walk* cioè un cammino casuale su un *WEB Graph* che è un grafo diretto. Praticamente più un nodo è collegato più ha possibilità di essere scelto, se è isolato no.

Questo misura l'importanza di una pagina *x* rispetto all'intero WEB.

Se fosse basato così, si potrebbe cercare di aumentare gli archi con gli altri nodi per diventare "visibile", quindi quello che sarebbe un *popularity score* sarebbe erroneo.

#### Data Clustering
Masterizzare in k regioni i dati (riorganizzare i dati diciamo)

## Probabilità
Defininiamo una variabile aleatoria r [1, 600], eseguo H(r) e G(r), se sono uguali è corretto sennò è sbagliato.

L'output di questo algoritmo fissato l'input è una variabile aleatoria che assume solo due valori. DIpende dall'input e da r. Se r è fissato l'output è fissato. L'output è una variabile aleatoria che dipende unicamente da r.

One sider Error, ha un caso che non commette errori. Esempio per $H(r)=G(r)$ la cosa sicura che se il caso è negativo allora siamo certi che lo sia.

Definisco $S=\{1,2,\cdots,m\}$ che dentro un array binario, rappresentato con indice $r\in S$ avrà grandezza $\theta(\log_{2}(n))$. Riempiamo questo array di 0 e 1. Questo crea una distribuzione lineare ottimale ma sposta il problema del "randomico" verso la scelta se mettere 0 o 1. Però noi assumiamo nella nostra macchina che quando ci viene dato un bit ci viene dato perfetto (anche se si approssimerebbe questo problema all'aumentare di m).

Per ottenere un minore errore diciamo, possiamo fare molte più iterazioni e combinarle per avere una maggiore "percentuale di successo".

Se da 10 macchine esce anche solo 1 no allora sono certo che è no.

Facciamo tante volte perché vogliamo diventare sempre più certi che tramite tanti *r* **non ci capiti no**, perché se ci capita è sicuramente no.

Se $H(x) = G(x)\implies P(alg^k=error)=0$
Se $H(x)\not=G(x)\implies P(alg^k=error)=P[\cap^{(i)}_{i=1}\ alg^[(i)]=error]\implies \prod^k_{i=1}Pr[alg^[(i)]=error]\leq\left( \frac{1}{600} \right)^k\leq \epsilon$
$k\log_{2}\left( \frac{1}{600} \right)\leq \log(\epsilon)\implies k\leq \frac{\log\left( \frac{1}{\epsilon} \right)}{\log\left( \frac{1}{600} \right)}$
$\text{Target}\implies Pr[error]\leq \frac{1}{n}$

Lo spazio di probabilità ha tre componenti:
- Lo spazio di esempio (dominio) che corrisponde al numero di valori