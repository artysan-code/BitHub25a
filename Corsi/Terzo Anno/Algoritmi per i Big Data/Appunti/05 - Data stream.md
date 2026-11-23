---
tags:
  - algoritmi-big-data
  - data-stream
  - sketch
  - algoritmi-randomizzati
slide:
  - "ch04-streams1_Andy_14-11-23.pdf"
---
# Data stream
## Il modello stream, pattern matching e campionamento
Lezione 11 (10/11/2026), slide ch04-streams1_Andy_14-11-23 (adattamento di A. Clementi delle slide di Leskovec, Rajaraman e Ullman, mmds.org), pp. 3-20 e 33-34; i numeri di pagina sono quelli del PDF. Riferimento principale: la **sezione 4 delle note di Prezza** (*Algorithms for Massive Data*), che il docente consiglia di riscaricare ogni tanto da arXiv perché vengono aggiornate. Chiuso il problema degli [[03 - Ricerca di oggetti simili|oggetti simili]], comincia un argomento caratterizzato non da un problema specifico ma dal **modello di input**: i dati non sono fermi in memoria, arrivano di continuo. Si vedono il modello stream e le query tipiche, gli **sketch** dei dati, l'algoritmo di **Karp-Rabin** per il pattern matching (prima statico, poi sullo stream) e l'inizio del **reservoir sampling**.
### Il modello stream
Come detto all'inizio del corso ([[01 - Introduzione al corso e al data mining]]), una parte importante del corso è la **modellazione**. In molte applicazioni non è realistico assumere che l'input sia tutto in memoria e resti fermo mentre l'algoritmo lavora (una "foto" al tempo $t$): la borsa e i titoli, le decisioni dentro un dispositivo mobile, un robot o un drone, un server che fa data mining sui pacchetti che arrivano da tutto il mondo. L'input cambia più rapidamente di quanto si possa ricaricarlo e rieseguire l'algoritmo.

Il modello **stream** (*data streaming*) descrive queste situazioni:
- l'input è una sequenza **discreta** di dati $x_1,x_2,\dots$: al tempo $t$ arriva un nuovo dato (un bit, un intero, un simbolo, o un vettore quando il dato è composito);
- lo stream **non** si può memorizzare per intero: si tiene solo uno **sketch** (una firma, come nel [[03 - Ricerca di oggetti simili#Shingling e min-hashing|min-hashing]]), e su quello si risponde alle query dell'utente.

Quando gli elementi sono tuple (un'email, un pacchetto) le query riguardano di solito **una componente** (il mittente, l'indirizzo IP: quanti messaggi ha mandato quell'indirizzo, oppure un forte cambiamento nei pacchetti da un certo server, che può essere un'anomalia), quindi si può assumere che lo stream sia di **scalari**.

La memoria è a due livelli (slide p. 5): una memoria di lavoro **piccola e veloce** (la cache), dove stanno gli sketch, e una memoria d'archivio grande ma ad accesso **lentissimo**, dove si può tenere una parte importante dello stream. Gli accessi all'archivio vanno minimizzati: si lavora sugli sketch e solo ogni tanto si recuperano dati dall'archivio.

> [!example] Query tipiche
> - In uno stream **binario**, contare gli 1 visti finora è banale: un contatore, che cresce al più in modo logaritmico. Più difficile: contare gli 1 nella **finestra** degli ultimi $N$ elementi.
> - Elementi in $\{0,\dots,k\}$, i codici dei prodotti venduti in un supermercato: per **ogni** prodotto, quanti ne sono stati venduti nelle ultime 24 ore (la frequenza), oppure quali sono i 5 prodotti più frequenti.
>
> Tenendo tutto lo stream sono esercizi di programmazione di base; con memoria **sublineare** nella dimensione dello stream il problema cambia completamente.

> [!info] Le query nelle slide (pp. 6-9)
> Nella mappa dei temi del corso (p. 2) si passa dai dati ad alta dimensionalità (LSH) ai dati "**infiniti**", e in particolare alle *queries on streams*. Tipi di query: costruire un **campione casuale** dello stream; query su **finestre scorrevoli** (*sliding windows*), come il **pattern matching** o il numero di elementi di tipo $x$ negli ultimi $k$; **filtrare** lo stream (elementi con una proprietà $x$); contare gli elementi **distinti** negli ultimi $k$; stimare i **momenti** (media e deviazione standard degli ultimi $k$); trovare gli elementi **frequenti**. Applicazioni: le query più frequenti oggi rispetto a ieri (Google), le pagine con un numero insolito di visite nell'ultima ora (Yahoo), i *trending topic* sui social, le reti di sensori, i tabulati telefonici, i pacchetti IP monitorati da uno switch.
### Data sketch
Un **data sketch** generalizza la firma del min-hashing. È una funzione, in generale **randomizzata**,
$$f:\Sigma^*\to\{0,1\}^k$$
che a una stringa qualunque su un alfabeto $\Sigma$ associa una parola di codice, con tre proprietà (slide p. 11):
1. **Dimensione**: $k\ll|x|$, lo sketch deve essere una versione compressa e approssimata del dato (nel min-hashing si passava dalla grande matrice a un indice logaritmico).
2. **Facile da aggiornare e da combinare**: se a $x$ si toglie il dato più vecchio e si aggiunge il più nuovo, ottenendo $x'$, non si deve ricalcolare tutto da zero, ma ottenere $f(x')$ dal solo sketch vecchio e dal nuovo simbolo: $f(xa)=F\big(f(x),f(a)\big)$. Così non si va nella memoria grande a recuperare lo stream: se $x$ è 50 MB e $f(x)$ 6 MB, basta rileggere i 6 MB.
3. **Preservare (con alta probabilità) la proprietà che interessa** di $x$. Quale proprietà dipende dal problema: per il min-hashing era la **similarità** di Jaccard, per il pattern matching è l'**identità**.

> [!warning] Identità, non similarità
> Nel min-hashing due documenti dovevano risultare vicini se erano "dentro una sfera" di raggio dato attorno all'altro. Qui la richiesta è molto più forte: gli sketch devono coincidere se e solo se le due stringhe coincidono. Se $y$ differisce da $x$ in un solo carattere, uno sketch buono deve dire con alta probabilità che sono **diverse**, mentre per la distanza di Hamming sarebbero vicinissime.
### Il pattern matching
Il **pattern matching** su uno stream: data una stringa fissata (una parola chiave, una proteina, un indirizzo IP), contare quante volte compare nello stream, aggiornando il conteggio man mano che arrivano i caratteri. Si parte dalla versione **statica** del problema: date $x,y\in\Sigma^n$ con
$$\Sigma=[s]=\{0,1,\dots,s-1\}$$
(alfabeto finito e fissato), decidere se $x=y$. Le due stringhe sono vettori di $n$ componenti, ciascuna tra $0$ e $s-1$. L'algoritmo banale confronta carattere per carattere: tempo lineare, ma anche **spazio** lineare, perché servono entrambi i vettori. Si vuole invece uno sketch che, una volta costruito (anche in tempo $n$), occupi molto meno di $n$.

> [!warning] L'idea sbagliata (slide p. 12)
> Si potrebbe vedere $x$ come un numero di $n$ cifre (con $s=2$, la sua codifica binaria) e usare una [[04 - Funzioni hash universali#Seconda costruzione: una retta casuale|funzione hash universale]] $f(x)=\big((ax+b)\bmod M\big)\bmod d$. Ma per rilevare l'identità bisogna mandare con alta probabilità numeri distinti in slot distinti, e serve $M>x$ come **valore**, non come lunghezza: l'aritmetica modulare lavora su numeri di $n$ cifre e lo sketch occupa spazio $\Theta(n)$. Non si è compresso nulla.
### L'impronta di Karp-Rabin
L'idea di **Rabin** (con Richard Karp, tra i padri dell'informatica teorica) è usare non le codifiche numeriche ma i **polinomi** su un campo finito.

> [!quote] Definizione (impronta di Rabin, slide p. 13)
> Si fissa un **primo** $q>s$ (più grande dell'**alfabeto**, non della stringa; se $s$ è primo può essere anche $q=s$) e si sceglie $z$ uniformemente a caso in $\mathbb{Z}_q=[q]$. Per $x=\langle x[0],\dots,x[n-1]\rangle\in[s]^n$:
> $$K_{q,z}(x)=\left(\sum_{i=0}^{n-1}x[n-1-i]\,z^i\right)\bmod q=\big(x[0]\,z^{n-1}+x[1]\,z^{n-2}+\dots+x[n-1]\big)\bmod q$$

Le componenti del vettore sono i **coefficienti** di un polinomio di grado al più $n-1$ in $\mathbb{Z}_q$, leggendo da sinistra a destra: $x[0]$ è il coefficiente più significativo, di $z^{n-1}$, e $x[n-1]$ il termine noto. Fissate le coordinate, il polinomio in forma canonica è unico. Con $q$ primo $\mathbb{Z}_q$ è un **campo** ([[04 - Funzioni hash universali#Rappresentare l'universo]]): somme, differenze e prodotti di polinomi sono polinomi, e vale il **teorema fondamentale dell'algebra** nella forma che serve, cioè un polinomio non nullo di grado $d$ ha al più $d$ radici. È lo stesso fatto già usato nel test di [[02 - Algoritmi randomizzati e probabilità#Algoritmi randomizzati|identità tra polinomi]], il primo algoritmo randomizzato del corso.

> [!example] Un esempio (nostro)
> Con $q=3$ e $x=\langle1,0,2,2,1\rangle$ ($n=5$) il polinomio è $z^4+2z^2+2z+1$ in $\mathbb{Z}_3$. Con $z=2$: $16+8+4+1=29\equiv2\pmod3$, e lo sketch è il solo numero $2$. A lezione l'esempio alla lavagna conteneva una cifra 3, non ammessa in $\mathbb{Z}_3$ (le cifre vanno da $0$ a $q-1$), come ha fatto notare uno studente.

Rappresentare il **polinomio** costerebbe ancora $n$ coefficienti. Il punto è che $z$ non è un'indeterminata ma una **variabile aleatoria** uniforme in $\mathbb{Z}_q$: lo sketch è il **valore** del polinomio in un punto casuale, un numero di $\mathbb{Z}_q$.
- **Tempo di costruzione**: $O(n)$ operazioni nel campo (una sommatoria di $n$ termini e le potenze $z^i$), ciascuna $O(1)$.
- **Spazio**: un valore di $\mathbb{Z}_q$, cioè $\log q$ bit. Si passa da $n\log q$ a $\log q$.

Restano da verificare le altre due proprietà: l'aggiornamento facile e la preservazione dell'identità.
#### Aggiornamento e concatenazione
> [!quote] Lemma 3.2 (facile da aggiornare)
> Per ogni carattere $c\in[s]$:
> $$K_{q,z}(x\,c)=\big(K_{q,z}(x)\cdot z+c\big)\bmod q$$

**Dimostrazione.** Il polinomio di $x\,c$ è $x[0]z^n+x[1]z^{n-1}+\dots+x[n-1]z+c$: tutti i coefficienti di $x$ salgono di un grado, cioè il polinomio di $x$ è moltiplicato per $z$, e $c$ diventa il nuovo termine noto. $\blacksquare$

Il docente insiste a leggere gli enunciati "da informatici": cosa serve per calcolare il membro sinistro? Solo lo sketch vecchio (un numero già in memoria), $z$ e il nuovo carattere: un prodotto, una somma e un modulo, tempo e spazio $O(\log q)$, senza tornare al polinomio di $x$ né alla memoria secondaria. Ricalcolando da zero a ogni carattere, costruire lo sketch di una stringa lunga $n$ costerebbe $O(n^2)$; con il lemma si costruisce incrementalmente in $O(n)$:

```pseudo
\begin{algorithm}
\caption{Rabin-Sketch($q, x$)}
\begin{algorithmic}
\State scegli $z$ uniformemente in $\mathbb{Z}_q$ \Comment{l'unica scelta casuale, una volta per tutte}
\State $K \gets 0$ \Comment{sketch della stringa vuota}
\For{$j \gets 1$ \textbf{to} $n$}
	\State $K \gets (K \cdot z + x[j-1]) \bmod q$
\EndFor
\State \Return $K$
\end{algorithmic}
\end{algorithm}
```

Se arriva un nuovo carattere non si rifà il ciclo: si fa un passo in più.

**Concatenazione di due stringhe** (l'esercizio per casa della slide p. 13, risolto a lezione). Noti $K_{q,z}(x)$ e $K_{q,z}(y)$, con lo **stesso** $z$ e $|y|=m$, nel polinomio di $x\,y$ i coefficienti di $x$ diventano i più significativi, spostati di $m$ posizioni, cioè moltiplicati per $z^m$:
$$K_{q,z}(x\,y)=\big(K_{q,z}(x)\cdot z^{|y|}+K_{q,z}(y)\big)\bmod q$$
L'unica quantità che manca è $z^{|y|}$. Calcolarla con $m$ moltiplicazioni costerebbe $O(m)$, cioè quanto ricalcolare lo sketch di $y$. Si usa l'**esponenziazione veloce** (vista ad Algoritmi):
$$z^k=\begin{cases}z^{k/2}\cdot z^{k/2}&k\text{ pari}\\ z\cdot z^{\lfloor k/2\rfloor}\cdot z^{\lfloor k/2\rfloor}&k\text{ dispari}\end{cases}$$
con una sola chiamata ricorsiva per livello (il valore di $z^{k/2}$ si calcola una volta e si usa due volte): $O(\log k)$ chiamate con 2 o 3 operazioni ciascuna, quindi $O(\log|y|)$ operazioni in $\mathbb{Z}_q$. Le slide (p. 14) danno lo spazio $O(\log q)$ per lo sketch e $O(\log q+\log|y|\log q)$ per la concatenazione, e osservano che $z^{|y|}$ si può **precalcolare**.
#### Lo sketch preserva l'identità
> [!quote] Lemma 3.4 (buono sketch per l'identità)
> Per ogni $x\neq y$ in $[s]^n$:
> $$\Pr_z\big[K_{q,z}(x)\equiv K_{q,z}(y)\pmod q\big]\leq\frac nq$$

Se $x=y$ i polinomi coincidono coefficiente per coefficiente, e comunque si scelga $z$ gli sketch sono uguali: probabilità 1. Non ci sono falsi negativi. Se le lunghezze sono diverse ci si accorge subito che le stringhe sono diverse, quindi si assume $|x|=|y|=n$.

**Dimostrazione.** $K_{q,z}(x)\equiv K_{q,z}(y)$ se e solo se $K_{q,z}(x)-K_{q,z}(y)\equiv0$. Raggruppando i termini dello stesso grado,
$$K_{q,z}(x)-K_{q,z}(y)=\big(x[0]-y[0]\big)z^{n-1}+\dots+\big(x[n-1]-y[n-1]\big)\equiv K_{q,z}(x-y)\pmod q$$
dove $x-y$ è la differenza componente per componente in $\mathbb{Z}_q$: fare la differenza dei polinomi o il polinomio della differenza dà lo stesso risultato. Poiché $x\neq y$, almeno una componente di $x-y$ è non nulla, quindi $K_{q,z}(x-y)$ è un polinomio **non nullo** di grado al più $n-1$. L'evento "sketch uguali" accade solo se il punto casuale $z$ è una sua **radice**, e le radici sono al più $n$ (meglio, $n-1$). Con $z$ uniforme sui $q$ valori di $\mathbb{Z}_q$, casi favorevoli su casi possibili: probabilità al più $\frac nq$. $\blacksquare$

> [!info] Come scegliere $q$
> Uno studente obietta: con l'alfabeto di 26 lettere e $q=29$, per una stringa di 500 caratteri il lemma non dice nulla. Giusto: il lemma non dice che la probabilità è bassa, ma che è **parametrizzabile** in $q$. Il primo $q$ deve solo superare l'alfabeto, ma può essere molto più grande: si immerge l'alfabeto in un campo molto più grande, usando solo pochi dei coefficienti possibili, e tutte le proprietà restano valide. La probabilità di errore (falsi positivi) decresce **linearmente** in $q$, mentre spazio e tempo crescono solo come $\log q$. Con $q=\Theta(n^2)$ la probabilità di errore è $O(1/n)$, e i costi restano $O(\log n^2)=O(\log n)$ (logaritmo di $n^2$, non logaritmo al quadrato). Basta che $q$ sia **polinomiale** in $n$.

> [!quote] Corollario 3.4.1 (slide p. 16)
> Se $q$ è un primo con $n^{b+1}\leq q\leq2n^{b+1}$ per una costante $b>0$, allora per ogni $x\neq y$
> $$\Pr\big[K_{q,z}(x)\equiv K_{q,z}(y)\big]\leq\frac1{n^b}$$
> e lo sketch occupa $O(\log n)$ bit: si comprime da $n$ a $\log n$.

Nella slide il secondo estremo è scritto $n^{b+1}$; la forma $2n^{b+1}$ è la nostra lettura (come per gli altri primi del corso, per il postulato di Bertrand ne esiste uno tra $N$ e $2N$). Nella versione statica $n$ è noto, e si sceglie $q$ in funzione di $n$.
### Karp-Rabin sullo stream
Il caso realistico: un **pattern** fissato $y\in[s]^n$ (una proteina, un indirizzo IP, un'immagine), abbastanza piccolo da tenerlo in cache con memoria $O(n)$, e lo **stream** $x=\langle x[1],x[2],\dots,x[m]\rangle$, con $m\gg n$ al tempo $m$. Si vuole contare le occorrenze di $y$ nello stream. (Rispetto alla parte statica, $x$ e $y$ si scambiano i ruoli: ora $y$ è il pattern e $x$ lo stream; slide p. 17.)

- Si calcola una volta $K_{q,z}(y)$.
- Per i primi $n-1$ caratteri dello stream non può esserci un'occorrenza: si costruisce solo lo sketch del prefisso con il lemma di aggiornamento.
- Al carattere $n$ si confrontano i due sketch.
- **Passo induttivo** (slide p. 18): elaborati $x[1],\dots,x[i]$ con $i\geq n$, si conoscono $K_{q,z}(\langle x[i-n+1],\dots,x[i]\rangle)$, lo sketch della finestra degli ultimi $n$ caratteri, e $K_{q,z}(y)$.
	1. Si confrontano; se coincidono si incrementa il contatore delle occorrenze.
	2. Arrivato $x[i+1]$, si fa **scorrere** la finestra: si toglie il carattere più vecchio, che era il coefficiente di grado massimo $z^{n-1}$, e si aggiunge il nuovo come termine noto:
	$$K_{q,z}(\langle x[i-n+2],\dots,x[i+1]\rangle)=\Big(\big(K_{q,z}(\langle x[i-n+1],\dots,x[i]\rangle)-x[i-n+1]\,z^{n-1}\big)\cdot z+x[i+1]\Big)\bmod q$$
	3. Si torna al passo 1.

Se invece si tenesse uno sketch di tutto lo stream senza togliere nulla, il suo valore resterebbe in $\mathbb{Z}_q$, ma non descriverebbe più la finestra da confrontare con il pattern.

> [!quote] Prestazioni (slide p. 19)
> Con stream di lunghezza $m$ e pattern di lunghezza $n$:
> - **spazio** $\Theta(n)$: per il passo 2 serve il carattere $x[i-n+1]$, uscito dalla finestra, e al passo dopo quello successivo, quindi bisogna tenere in memoria gli **ultimi $n$ caratteri** dello stream;
> - **tempo** $O(1)$ per aggiornamento: basta **precalcolare** $z^{n-1}\bmod q$ (e anche ricalcolandolo con l'esponenziazione costerebbe solo $O(\log n)$).

Lo spazio non dipende dalla lunghezza dello stream, ma è lineare nel pattern. Nella maggior parte delle applicazioni il pattern è piccolo e lo stream enorme, quindi è ragionevole.

> [!info] Porat e Porat (slide p. 20)
> Anche $n$ può essere molto grande. Un risultato del 2009 di **Porat e Porat** risolve il pattern matching nel modello stream con spazio $O(\log n)$: anche la finestra degli ultimi $n$ caratteri viene compressa in sketch. Algoritmo e analisi sono molto complicati, da laurea magistrale o dottorato; sono nella sezione 4.1.2 delle note di Prezza. Fuori programma.

> [!question] Domanda tipica d'esame
> Cos'è un data sketch e quali proprietà deve avere? Definisci l'impronta di Karp-Rabin e dimostra che si aggiorna in tempo costante quando si aggiunge un carattere. Come si calcola lo sketch della concatenazione di due stringhe? Dimostra che $\Pr[K_{q,z}(x)=K_{q,z}(y)]\leq n/q$ per $x\neq y$ e spiega come scegliere $q$. Descrivi l'algoritmo di Karp-Rabin su uno stream e analizzane spazio e tempo.
### Campionare uno stream
Il problema centrale del data mining su stream: mantenere un **campione rappresentativo** di tutti i dati visti finora. Se la memoria contiene $s$ elementi (ad esempio 100 numeri), si vuole un campione di dimensione **fissa** $s$ tale che, dopo $n$ elementi, **ogni** elemento visto stia nel campione con la stessa probabilità
$$\Pr[\text{elemento nel campione}]=\frac sn$$
La probabilità cresce con la dimensione del campione e tende a zero al crescere dello stream, ma conta l'**uniformità**: nessun elemento è privilegiato. Quando si passa da $n$ a $n+1$ elementi, la probabilità di ciascuno deve diventare $\frac s{n+1}$. La soluzione banale, tenere tutti gli $n$ elementi e sceglierne $s$ a caso, è impraticabile (slide p. 33).

> [!info] Campione di proporzione fissa (slide pp. 21-32, saltate)
> Le slide trattano prima il campione di una **proporzione** fissa dello stream (ad esempio un elemento su 10, o il 30%), con l'esempio delle query di un motore di ricerca e il campionamento per utente con una funzione hash. Il docente l'ha saltato: al crescere dello stream cresce anche il campione, mentre la memoria disponibile è fissa.
#### Reservoir sampling
> [!quote] Algoritmo Reservoir Sampling $RS(s)$ (slide p. 34)
> - I primi $s$ elementi dello stream si mettono tutti nel campione $S$.
> - Visti $n-1$ elementi, al tempo $n$ arriva l'$n$-esimo:
> 	1. con probabilità $\frac sn$ lo si prende, altrimenti lo si scarta (e il campione resta com'è);
> 	2. se lo si è preso, sostituisce uno degli $s$ elementi del campione scelto uniformemente, cioè con probabilità $\frac1s$.

> [!quote] Teorema
> Per ogni $s\geq1$ e ogni tempo $n\geq s$, il campione $S$ contiene ciascuno degli $n$ elementi visti finora con probabilità esattamente $\frac sn$.

Come sempre l'algoritmo è semplice e l'analisi più impegnativa: la dimostrazione, per **induzione** su $n$, è rimandata alla lezione successiva. Le slide (pp. 35-36) la impostano così: la base è $n=s$ (ogni elemento è nel campione con probabilità $\frac ss=1$); per il passo, l'elemento $n+1$ entra con probabilità $\frac s{n+1}$, e un elemento vecchio già nel campione ci resta se il nuovo viene scartato oppure se viene preso ma sostituisce un altro elemento:
$$\left(1-\frac s{n+1}\right)+\frac s{n+1}\cdot\frac{s-1}s=\frac n{n+1}$$
quindi è nel campione al tempo $n+1$ con probabilità $\frac sn\cdot\frac n{n+1}=\frac s{n+1}$.
### Prossimi passi
Giovedì si fa l'analisi del reservoir sampling. Le slide proseguono (pp. 37-45) con le **finestre scorrevoli**: contare gli 1 negli ultimi $k$ bit di uno stream binario, il limite inferiore di $N$ bit per la risposta esatta e l'algoritmo approssimato **DGIM** con spazio $O(\log^2N)$.
