---
tags:
  - algoritmi-big-data
  - probabilita
  - variabili-aleatorie
  - algoritmi-randomizzati
slide: []
---
# Variabili aleatorie e valore atteso
Lezione 3 (13/10/2026): si riprende il [[02 - Algoritmi randomizzati#Taglio minimo di un grafo (algoritmo di Karger)|taglio minimo di Karger]] per chiarire quale spazio di probabilità genera un algoritmo randomizzato e come se ne controlla l'evoluzione con la probabilità condizionata. Poi si introducono gli strumenti del capitolo 2 del Mitzenmacher-Upfal: variabili aleatorie, indipendenza, valore atteso e la sua **linearità**, variabili Bernoulliane e binomiali. Si chiude con l'analisi del **randomized quicksort**, in cui la linearità riduce un'analisi apparentemente esponenziale a pochi passaggi.
## Perché la randomizzazione conviene
Nella [[02 - Algoritmi randomizzati#Verifica del prodotto tra matrici (Freivalds)|verifica del prodotto tra matrici]] il metodo deterministico calcola $AB$ e lo confronta con $C$; anche i metodi più sofisticati per la moltiplicazione restano sopra $n^2$. L'algoritmo randomizzato genera un vettore casuale ($O(n)$) e fa tre prodotti matrice-vettore ($O(n^2)$ ciascuno), quindi costa $O(n^2)$: è un **miglioramento polinomiale**.

Non è gratis: si paga con una **probabilità di errore**, che però è controllabile, perché con ripetizioni indipendenti diventa piccola a piacere.

> [!info] Dimensione dell'input
> Se l'input è una matrice $n \times n$, la sua dimensione è $n^2$, non $n$. In questa prima parte del corso la differenza non è determinante: si può fare l'analisi in funzione di $n$, purché il confronto con il metodo deterministico sia coerente.
## Lo spazio di probabilità di un algoritmo randomizzato
Per verificare di aver capito davvero un algoritmo randomizzato, oltre all'idea, ci si devono porre due tipi di domande, che sono anche quelle tipiche dell'orale:
1. **da probabilista**: qual è lo spazio di probabilità generato dall'algoritmo a ogni passo? Con quale distribuzione? Quanti bit casuali servono?
2. **da informatico**: come si implementa il passo casuale? Quale struttura dati si sceglie, come si modifica, cosa si sceglie esattamente? Il linguaggio è libero (Python, C), ma la descrizione deve essere precisa.

> [!question] Domanda tipica d'esame
> Si porta il min cut di Karger come argomento a piacere. Qual è lo spazio di probabilità generato al primo passo, e come cambia ai passi successivi? Come si implementa la scelta dell'arco da contrarre?
>
> Traccia: al tempo 0 gli esiti possibili sono gli archi $E = \{e_1, \dots, e_m\}$ e la scelta è **uniforme**: $\Pr[E_1 = e_i] = 1/|E|$. Al passo $t$ il grafo $G_t$ ha un vertice in meno e un insieme di archi $E_t \subseteq E$ (spariscono l'arco contratto e i self loop creati), che **non si conosce** finché non si sono eseguiti i primi $t-1$ passi. Lo spazio al passo $t$ è $E_t$ con distribuzione uniforme: in pratica si rinumerano gli archi rimasti e si chiede alla libreria un indice uniforme.
### Variabili aleatorie e valori deterministici
Si distinguono due tipi di oggetti, anche quando hanno lo stesso simbolo:
- $e_1, \dots, e_m$ sono **elementi di un insieme fissato**: deterministici, non cambiano nel tempo ($e_1$ è sempre l'arco $\{1, 2\}$);
- $E_t$, l'arco scelto al passo $t$, è una **variabile aleatoria**: l'esito (*outcome*) di un esperimento. Finché l'esperimento non è eseguito se ne conoscono solo i **valori possibili** e la **distribuzione**.

Lo spazio di probabilità di un algoritmo randomizzato quindi non è fisso: per ogni passo $t \geq 1$ e ogni $e \in E_t$,

$$\Pr[\,E_t = e\,] = \frac{1}{|E_t|}$$

dove $E_t$ è a sua volta una variabile aleatoria che dipende dalle scelte precedenti.
## Karger rivisto
### La contrazione non diminuisce il taglio minimo
Il primo ingrediente dell'analisi è di natura **topologica**.

> [!quote] Lemma
> Ogni taglio del grafo ottenuto contraendo un arco è anche un taglio del grafo di partenza, con la stessa dimensione. Quindi la contrazione **non diminuisce** la dimensione del taglio minimo.

> [!example] Due clique unite da un arco
> Si prendono due grafi completi con $n/2$ vertici ciascuno, collegati da un solo arco. Il taglio minimo ha dimensione 1 (quell'arco). Contraendo un arco interno a una clique il taglio minimo resta 1; contraendo l'arco ponte le due clique si fondono e il taglio minimo sale molto.

Un taglio è un insieme di archi la cui rimozione **disconnette** il grafo, e il taglio minimo misura la **resilienza** (*fault tolerance*) della rete: un grafo con taglio minimo $k$ resta connesso finché non si rompono almeno $k$ archi. Contrarre un arco toglie una possibilità di staccare il grafo, quindi non peggiora mai la situazione.

Una conseguenza importante: quando si contrae un arco, gli archi paralleli tra gli stessi due vertici diventano self loop e spariscono. Questi archi o fanno **tutti** parte del taglio $C$ o **nessuno**: togliendone solo alcuni il grafo non si stacca. Se l'arco contratto non è in $C$, nessuno degli archi eliminati con lui è in $C$.
### Lo schema dell'analisi
L'analisi fissa un taglio minimo $C$ di dimensione $k$ nel grafo iniziale. $C$ **non** è una variabile dell'algoritmo: è l'analista che, con potere di calcolo illimitato, guarda dall'alto e segue cosa succede a quel taglio. A ogni passo ci sono due casi, descritti da una variabile booleana: l'arco scelto è in $C$ oppure no.

> [!info] Un'analisi nel caso peggiore
> I tagli minimi potrebbero essere più di uno: l'algoritmo potrebbe toccare un arco di $C$ e trovare comunque un altro taglio minimo. L'analisi non considera questa possibilità, quindi si mette nell'ipotesi più sfavorevole all'algoritmo.

Siano $E_i$ l'evento "al passo $i$ non si sceglie un arco di $C$" e $F_i = E_1 \cap \dots \cap E_i$ ("fino al passo $i$ è sempre andata bene").
- **Primo passo**. Ogni vertice ha grado almeno $k$, altrimenti staccarlo costerebbe meno di $k$ archi; quindi $|E| \geq nk/2$ e

$$\Pr[E_1] = 1 - \frac{k}{|E|} \geq 1 - \frac{k}{nk/2} = 1 - \frac{2}{n}$$

- **Secondo passo**. Lo spazio di probabilità dipende da cosa è successo prima, quindi si **condiziona**: ci si mette nell'ipotesi $F_1$ (se si è toccato $C$ l'algoritmo è già fallito, e quel caso non interessa). Sotto $F_1$ il numeratore non cambia, perché $C$ è intatto con i suoi $k$ archi; cambia il denominatore, perché la contrazione ha tolto un numero imprecisato di archi. Per il lemma il taglio minimo è ancora almeno $k$, quindi ogni vertice ha ancora grado almeno $k$, e i vertici sono $n-1$:

$$\Pr[E_2 \mid F_1] \geq 1 - \frac{k}{(n-1)k/2} = 1 - \frac{2}{n-1}$$

- **Passo generico**. Con lo stesso ragionamento su $n - i + 1$ vertici, $\Pr[E_i \mid F_{i-1}] \geq 1 - \frac{2}{n-i+1}$.

Senza il lemma topologico non si potrebbe dire nulla sui passi successivi al primo. Per la **regola della catena**, $\Pr[F_{n-2}] = \Pr[E_{n-2} \mid F_{n-3}] \cdot \Pr[F_{n-3}]$, e srotolando fino al primo passo si ottiene il prodotto telescopico già visto nella [[02 - Algoritmi randomizzati#Probabilità di successo|probabilità di successo]]:

$$\Pr[F_{n-2}] \geq \frac{2}{n(n-1)}$$
### Corretto con alta probabilità
La probabilità di successo di una singola esecuzione è dell'ordine di $1/n^2$: tende a zero, ma **in modo polinomiale**. L'algoritmo restituisce sempre un taglio, che non può essere più piccolo di quello minimo; quando fallisce restituisce un taglio più grande, anche di molto. Si esegue quindi $N$ volte in modo indipendente e si tiene il **taglio più piccolo** trovato; si sbaglia solo se tutte le esecuzioni falliscono.

Si usa una disuguaglianza che tornerà spesso, legata all'approssimazione di Taylor:

$$1 - x \leq e^{-x} \qquad\text{quindi}\qquad (1 - x)^N \leq e^{-xN}$$

Con $N = n(n-1) \ln n$ ripetizioni:

$$\Pr[\text{errore}] \leq \left(1 - \frac{2}{n(n-1)}\right)^{n(n-1)\ln n} \leq e^{-2 \ln n} = \frac{1}{n^2}$$

> [!quote] Alta probabilità
> Un algoritmo è **corretto con alta probabilità** (*with high probability*) se la sua probabilità di errore va come l'inverso di un polinomio nella dimensione dell'input, ad esempio $O(1/n)$ o $O(1/n^2)$.
## Variabili aleatorie
> [!quote] Variabile aleatoria
> Una **variabile aleatoria** $X$ su uno spazio di probabilità $(\Omega, \mathcal{F}, \Pr)$ è una funzione $X : \Omega \to \mathbb{R}$ che assegna un valore a ogni evento elementare. È **discreta** se assume un numero finito o numerabile di valori (nel corso, di solito, valori naturali).

Spazio di probabilità e variabile aleatoria vanno tenuti separati: lo spazio descrive gli esiti dell'esperimento, la variabile è una funzione definita sopra di essi. Anche nell'analisi di Karger si è usata una variabile aleatoria: la variabile booleana che vale 1 se l'arco scelto non è nel taglio. Nell'analisi di un algoritmo randomizzato il processo completo è molto complicato, ma interessano poche variabili, soprattutto due:
- la **correttezza**, variabile booleana (l'algoritmo ha risposto bene o no?);
- il **tempo di esecuzione**: eseguendo lo stesso algoritmo cento volte sullo stesso input, una volta fa 10 confronti, un'altra 100, un'altra 50.

> [!warning] Il tempo di un algoritmo randomizzato
> Dire che un ordinamento randomizzato "ci mette tempo $n \log n$" non ha senso: il tempo è una variabile aleatoria. Bisogna dire **con quale probabilità** lo fa, oppure che il **tempo atteso** è $O(n \log n)$. Il valore atteso è un numero deterministico; la variabile no.

> [!example] Due esempi
> - **Un dado**: lo spazio sono le sei facce, la variabile vale il numero letto sulla faccia uscita.
> - **Due monete e un premio**: si lanciano due monete in modo indipendente; se escono due teste si vincono 3 dollari, altrimenti se ne perde 1. Lo spazio ha 4 esiti (TT, TC, CT, CC), la variabile vale $3$ su TT e $-1$ sugli altri tre.

> [!quote] Indipendenza
> Due variabili aleatorie $X$ e $Y$ sono **indipendenti** se per ogni coppia di valori $x, y$
> $$\Pr[(X = x) \cap (Y = y)] = \Pr[X = x] \cdot \Pr[Y = y]$$
> e analogamente per $k$ variabili: la probabilità della congiunzione è il prodotto delle probabilità.

L'indipendenza è una definizione matematica, non un'idea fisica del tipo "uno non dà fastidio all'altro". La notazione $X = x$ ribadisce la distinzione: $x$ è un valore fissato tra quelli possibili, $X$ è l'esito.
## Valore atteso
> [!quote] Valore atteso
> Il **valore atteso** di una variabile aleatoria discreta $X$ è
> $$\mathbb{E}[X] = \sum_{i} i \cdot \Pr[X = i]$$
> dove la somma corre su tutti i valori che $X$ può assumere. Con infiniti valori la somma può anche divergere: va verificato caso per caso.

> [!example] Uno e due dadi
> - Per un dado equo $\mathbb{E}[X] = \sum_{i=1}^{6} i \cdot \frac16 = \frac{21}{6} = 3{,}5$. La variabile assume solo valori naturali, ma il valore atteso è un razionale, e non è un valore che la variabile può assumere.
> - Per la somma di due dadi i valori vanno da 2 a 12, non con distribuzione uniforme: 2 si ottiene solo con $(1,1)$ e 12 solo con $(6,6)$, probabilità $1/36$ ciascuno, mentre 4 si ottiene con $(1,3), (2,2), (3,1)$. Il calcolo diretto dà $\mathbb{E} = 7$.

La **mediana** è diversa dal valore atteso: è un valore $m$ che la variabile assume davvero e che divide a metà la massa di probabilità, cioè $\Pr[X \leq m] \geq 1/2$ e $\Pr[X \geq m] \geq 1/2$.
### Linearità del valore atteso
> [!quote] Teorema (linearità del valore atteso)
> Per qualsiasi variabili aleatorie $X$ e $Y$, **indipendenti o no**, e per ogni costante $c$:
> $$\mathbb{E}[X + Y] = \mathbb{E}[X] + \mathbb{E}[Y] \qquad \mathbb{E}[c\,X] = c\,\mathbb{E}[X]$$

*Dimostrazione.* Per definizione e spezzando $i + j$:

$$\mathbb{E}[X + Y] = \sum_i \sum_j (i + j) \Pr[(X = i) \cap (Y = j)] = \sum_i i \sum_j \Pr[(X = i) \cap (Y = j)] + \sum_j j \sum_i \Pr[(X = i) \cap (Y = j)]$$

Gli eventi $\{Y = j\}$, al variare di $j$, formano una **partizione** dello spazio (disgiunti a due a due, con unione $\Omega$), quindi per la probabilità totale $\sum_j \Pr[(X = i) \cap (Y = j)] = \Pr[X = i]$. Il primo addendo è $\mathbb{E}[X]$, e allo stesso modo il secondo è $\mathbb{E}[Y]$. La seconda proprietà è immediata.

La forza del teorema è che non richiede alcuna ipotesi sulla dipendenza: si calcolano i valori attesi separatamente e si sommano. Non vale per altre grandezze: la **varianza** di una somma, ad esempio, non è la somma delle varianze quando le variabili sono correlate.

> [!example] Somma di due dadi e numero di teste
> - Due dadi: $\mathbb{E}[X_1 + X_2] = 3{,}5 + 3{,}5 = 7$, senza il calcolo sui 36 esiti.
> - $n$ lanci di una moneta equa: il numero atteso di teste è $n \cdot \frac12$, perché ogni lancio contribuisce con $\frac12$.
### Bernoulliana e binomiale
> [!quote] Variabile Bernoulliana
> Una variabile **Bernoulliana** (o **indicatrice**) di parametro $p$ vale 1 con probabilità $p$ e 0 con probabilità $1 - p$. Il suo valore atteso è
> $$\mathbb{E}[X] = 1 \cdot p + 0 \cdot (1 - p) = p = \Pr[X = 1]$$

Per una variabile booleana il valore atteso coincide sempre con la probabilità che valga 1: è il trucco che si usa in quasi tutte le analisi.

> [!quote] Variabile binomiale
> Una variabile **binomiale** $X \sim B(n, p)$ conta i successi in $n$ prove Bernoulliane **indipendenti** di parametro $p$:
> $$\Pr[X = j] = \binom{n}{j} p^j (1 - p)^{n - j} \qquad j = 0, \dots, n$$

Il coefficiente $\binom{n}{j}$ sceglie le posizioni dei $j$ successi; per l'indipendenza, su quelle posizioni si ha $p^j$ e sulle altre $(1-p)^{n-j}$. Ad esempio, la probabilità di esattamente 75 teste su 100 lanci si ottiene sostituendo $n = 100$, $j = 75$, $p = 1/2$. È raro, nell'analisi di algoritmi complessi, conoscere la distribuzione esatta così; di solito ci si concentra sul valore atteso e al più sulla varianza.

Il valore atteso della binomiale si può calcolare dalla definizione, con qualche passaggio sui coefficienti binomiali, oppure in una riga con la linearità: $X = X_1 + \dots + X_n$ con $X_i$ Bernoulliane, quindi

$$\mathbb{E}[X] = \sum_{i=1}^{n} \mathbb{E}[X_i] = n\,p$$
## Randomized quicksort
Il quicksort con pivot casuale (già incontrato come esempio di [[02 - Algoritmi randomizzati#Monte Carlo e Las Vegas|algoritmo Las Vegas]]) ordina un insieme $S$ di $n$ elementi distinti. Ha lo stesso numero ottimo di confronti di heapsort e mergesort, ma è molto più semplice.

```pseudo
\begin{algorithm}
\caption{RandQuickSort($S$)}
\begin{algorithmic}
\If{$|S| \leq 1$}
  \State \Return $S$
\EndIf
\State scegli $y \in S$ uniformemente a caso
\State $S_1 \gets \{x \in S : x < y\}$
\State $S_2 \gets \{x \in S : x > y\}$
\State \Return \Call{RandQuickSort}{$S_1$}, $y$, \Call{RandQuickSort}{$S_2$}
\end{algorithmic}
\end{algorithm}
```

Una volta scelto $y$ e partizionato l'insieme, la posizione di $y$ nel vettore ordinato è determinata. A volte $y$ è vicino al centro e le due parti sono bilanciate, a volte è un estremo e una parte è quasi vuota.

Il pivot $y$ è una **variabile aleatoria**, e non ce n'è uno solo: lo spazio di probabilità è quello delle sequenze di pivot $y_1, y_2, \dots, y_t$, ognuno scelto uniformemente nel sottoinsieme corrente. Analizzare il numero di confronti caso per caso ("se $y_1$ è il primo elemento succede questo, poi $y_2$ dipende da $y_1$…") porta a un numero esponenziale di casi: senza un'idea più furba l'analisi è impossibile, e nessuna simulazione la sostituisce.

> [!quote] Teorema
> Per **qualunque** input di $n$ elementi, il numero atteso di confronti di RandQuickSort è $O(n \log n)$.

Non è un'analisi del caso medio sugli input: vale anche per l'istanza peggiore, e il valore atteso è preso sulle scelte casuali dell'algoritmo.
### Dimostrazione con la linearità
Siano $s_1 < s_2 < \dots < s_n$ gli elementi in ordine crescente. Due elementi qualsiasi vengono confrontati **al più una volta**: si confrontano solo quando uno dei due è il pivot, e dopo quel passo il pivot esce dalle chiamate ricorsive. Si definisce allora, per $i < j$, la variabile indicatrice

$$X_{ij} = \begin{cases} 1 & \text{se } s_i \text{ e } s_j \text{ vengono confrontati durante l'esecuzione} \\ 0 & \text{altrimenti} \end{cases}$$

Non interessa quando né perché: solo se il confronto avviene. Il numero totale di confronti è $X = \sum_{i < j} X_{ij}$ e, per linearità,

$$\mathbb{E}[X] = \sum_{i=1}^{n-1} \sum_{j > i} \mathbb{E}[X_{ij}] = \sum_{i=1}^{n-1} \sum_{j > i} \Pr[X_{ij} = 1]$$

Tutto si riduce a una domanda: con che probabilità due elementi si confrontano? Si guarda l'insieme $\{s_i, s_{i+1}, \dots, s_j\}$, che ha $j - i + 1$ elementi e resta nella stessa chiamata ricorsiva finché non si sceglie come pivot uno di loro.
- Se il pivot è **fuori** dall'intervallo (minore di $s_i$ o maggiore di $s_j$), $s_i$ e $s_j$ finiscono nello stesso sottoinsieme e non si sa ancora nulla.
- Se il pivot è uno dei $j - i - 1$ elementi **strettamente in mezzo**, $s_i$ e $s_j$ finiscono in sottoinsiemi diversi e **non saranno mai confrontati**.
- Se il pivot è **$s_i$ o $s_j$**, i due vengono confrontati.

Il primo pivot scelto nell'intervallo è uniforme sui suoi $j - i + 1$ elementi, quindi

$$\Pr[X_{ij} = 1] = \frac{2}{j - i + 1}$$

Sostituendo, con $k = j - i + 1$:

$$\mathbb{E}[X] = \sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \frac{2}{j - i + 1} \leq \sum_{i=1}^{n} \sum_{k=2}^{n} \frac{2}{k} \leq 2n\,H_n = O(n \log n)$$

dove $H_n = \sum_{k=1}^{n} 1/k \approx \ln n$ è la serie armonica.

> [!info] La lezione da portare a casa
> Una variabile enorme e intrattabile, il numero totale di confronti, si spezza in una somma di variabili indicatrici semplicissime. La linearità del valore atteso permette di analizzarle una per volta, senza preoccuparsi delle loro dipendenze.

> [!question] Domanda tipica d'esame
> Si porta il randomized quicksort. Qual è lo spazio di probabilità? Quali sono le variabili aleatorie in gioco? Perché $\Pr[X_{ij} = 1] = 2/(j - i + 1)$, e dove si usa che il pivot è scelto in modo uniforme? Perché serve la linearità del valore atteso e non l'indipendenza?
