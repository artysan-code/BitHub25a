---
tags:
  - algoritmi
  - strutture-dati
  - hash
slide: "10_hash_table_2025.pdf"
capitolo: "Kleinberg-Tardos cap. 13.6"
---
# Tabelle Hash
Le **tabelle hash** sono un'implementazione **randomizzata** del tipo di dato dizionario: spazio proporzionale agli elementi presenti e tempo $O(1)$ **atteso** per operazione (ammortizzato, grazie al ridimensionamento della tabella). Il deck è in inglese e segue la lezione 8 del corso MIT *Design and Analysis of Algorithms* (OpenCourseWare) più il cap. 13.6 del Kleinberg-Tardos: i nomi degli oggetti sulle slide sono quelli usati qui. È la lezione 22 del diario delle lezioni 2025/26 («Tabelle Hash»).
## Il problema del dizionario
Dato un universo $U$ di elementi possibili, si vuole mantenere un sottoinsieme $S \subseteq U$ che cambia nel tempo.

> [!quote] Definizione — Operazioni del dizionario
> - **`make-dictionary()`**: inizializza un dizionario vuoto.
> - **`insert(u)`**: aggiunge l'elemento $u \in U$ a $S$.
> - **`delete(u)`**: toglie $u$ da $S$, se $u$ è presente.
> - **`look-up(u)`**: determina se $u$ appartiene a $S$.

> [!info] Regola — la difficoltà: $U$ è enorme
> L'universo $U$ può essere estremamente grande, quindi definire un array di dimensione $|U|$ (un elemento = una cella) non è praticabile.

**Soluzione già nota**: gli [[06 - Alberi di Ricerca BST e AVL#Alberi AVL|alberi bilanciati]] (ad esempio AVL), che realizzano il [[05 - Strutture Dati Elementari e Dizionari#Il Tipo di Dato Dizionario|dizionario]] con le prestazioni della tabella seguente. La tabella hash migliora il tempo:

| Struttura | Spazio | Tempo per operazione |
|---|---|---|
| Alberi bilanciati (AVL) | $O(\lvert S\rvert)$ | $O(\log \lvert S\rvert)$ |
| Tabella hash | $O(\lvert S\rvert)$ | $O(1)$ atteso, ammortizzato |
## Hashing con chaining
**Idea**: una funzione $h : U \to \{0,1,\ldots,m-1\}$ associa a ogni elemento $u$ la cella $h(u)$ di una tabella $H$ di $m$ celle, quella in cui $u$ viene messo. Si prende $m \approx n := |S|$.

> [!quote] Definizione — Collisione
> Una **collisione** avviene quando $h(u) = h(v)$ con $u \neq v$: due elementi diversi finiscono nella stessa cella.

> [!quote] Definizione — Hashing con chaining
> $H[i]$ è la **lista concatenata** di tutti gli elementi che $h$ manda nella cella $i$.

```pseudo
\begin{algorithm}
\caption{insert / delete / look-up di $u$ (hashing con chaining)}
\begin{algorithmic}
\State calcola $h(u)$
\State inserisci / cancella / cerca $u$ scorrendo la lista $H[h(u)]$
\end{algorithmic}
\end{algorithm}
```

**Obiettivo**: trovare una funzione $h$ che «distribuisca bene» gli elementi, cioè che renda corte le liste. Il costo di un'operazione è la lunghezza della lista che si scorre.
## Scegliere una buona funzione hash
> [!warning] Una funzione deterministica ha sempre un caso pessimo
> Per **qualunque** funzione hash deterministica si può trovare un insieme $S$ in cui tutti gli elementi sono mandati nella stessa cella. Allora la lista è lunga $n$ e ogni operazione costa $\Theta(n)$.

**Idea**: usare la **randomizzazione**, cioè scegliere la funzione a caso, in modo che nessun insieme $S$ fissato in anticipo sia sempre cattivo.

**Approccio ovvio**: per ogni $u$, scegliere $h(u)$ uniformemente a caso. Ma poi una `look-up(u)` deve rispondere a «dove ho messo $u$?»: bisogna tenere in memoria l'insieme di coppie $\{(u, h(u)) : u \in S\}$. **Questo è proprio il problema del dizionario** (la slide scherza: «forse posso usare una tabella hash»): il ragionamento è circolare, quindi la scelta casuale elemento per elemento non è una soluzione.
## Hashing universale
Si sceglie a caso non il valore di ogni $h(u)$, ma l'**intera funzione** $h$ da una famiglia con una buona proprietà.

> [!quote] Definizione — Famiglia universale di funzioni hash
> Una famiglia $\mathcal{H}$ di funzioni hash è **universale** se, per ogni coppia di elementi distinti $u, v \in U$,
> $$\Pr_{h \in \mathcal{H}}\bigl(h(u) = h(v)\bigr) \leq \frac{1}{m}$$

La probabilità è sulla scelta casuale di $h$ in $\mathcal{H}$, non su $u$ e $v$, che restano fissi. Il valore $1/m$ è quello che si avrebbe con una funzione completamente casuale.

> [!quote] Teorema — Lunghezza attesa della lista
> Sia $\mathcal{H}$ una famiglia universale di funzioni hash. Sia $S \subseteq U$ un insieme di $n$ elementi e sia $u \in S$. Si sceglie a caso una funzione $h$ da $\mathcal{H}$ e sia $X$ la variabile casuale che conta gli elementi di $S$ mandati in $h(u)$. Allora
> $$E[X] \leq 1 + \frac{n}{m}$$

**Dimostrazione.**
Per ogni $s \in S$ sia $X_s$ la variabile casuale indicatrice
$$X_s = \begin{cases} 1 & \text{se } h(s) = h(u) \\ 0 & \text{altrimenti} \end{cases} \qquad X = \sum_{s \in S} X_s$$
Per la linearità del valore atteso, e perché il valore atteso di un'indicatrice è la probabilità dell'evento,
$$E[X] = E\Bigl[\sum_{s \in S} X_s\Bigr] = \sum_{s \in S} E[X_s] = \sum_{s \in S} \Pr\bigl(h(s) = h(u)\bigr)$$
Il termine con $s = u$ vale $1$ (si ha sempre $h(u) = h(u)$); per gli altri $n-1$ elementi si usa l'universalità:
$$= 1 + \sum_{s \in S \setminus \{u\}} \Pr\bigl(h(s) = h(u)\bigr) \leq 1 + \frac{n-1}{m} \leq 1 + \frac{n}{m} \qquad \square$$
*(extra, non da slide)* La slide scrive direttamente $\leq 1 + n/m$; il passaggio intermedio $1 + (n-1)/m$ è esplicitato qui.

> [!info] Regola — conseguenza sul tempo
> Con $m = \Theta(n)$ si ha $E[X] \leq 1 + n/m = O(1)$: ogni operazione costa tempo **atteso** $O(1)$.
## Una famiglia universale: $h_a(x) = \sum_i a_i x_i \bmod m$
La famiglia si costruisce a partire da un numero primo $m$ con $n \leq m \leq 2n$: un primo così esiste sempre (Chebyshev, 1850).

> [!quote] Definizione — La famiglia $\mathcal{H} = \{h_a : a \in U\}$
> - **Dimensione della tabella**: $m$ primo con $n \leq m \leq 2n$ (un primo in questo intervallo esiste sempre: Chebyshev, 1850).
> - **Codifica degli interi**: ogni elemento $x \in U$ si identifica con un intero in base $m$ di $r$ cifre, $x = (x_1, x_2, \ldots, x_r)$ con $x_i \in \{0, 1, \ldots, m-1\}$. Ogni cifra occupa circa $\log m$ bit, e $x$ intero circa $\log |U|$ bit.
> - **Funzione hash**: dato $a \in U$, $a = (a_1, a_2, \ldots, a_r)$ (anch'esso scritto in base $m$),
> $$h_a(x) = \Bigl(\sum_{i=1}^{r} a_i x_i\Bigr) \bmod m$$
> - **Famiglia**: $\mathcal{H} = \{h_a : a \in U\}$. Scegliere $h \in \mathcal{H}$ a caso significa scegliere $a$ a caso.

> [!info] Regola — modello word RAM
> Nel modello **word RAM** manipolare $O(1)$ parole di macchina costa $O(1)$ e ogni oggetto di interesse sta in una parola di macchina. Quindi memorizzare $h_a$ richiede di memorizzare il solo valore $a$ (una parola), e calcolare $h_a(x)$ costa $O(1)$.

> [!quote] Teorema — Universalità di $\mathcal{H} = \{h_a\}$
> La famiglia $\mathcal{H} = \{h_a : a \in U\}$ è universale.

**Dimostrazione.**
Siano $x = (x_1, \ldots, x_r)$ e $y = (y_1, \ldots, y_r)$ due elementi distinti di $U$. Bisogna mostrare che $\Pr[h_a(x) = h_a(y)] \leq 1/m$.

Poiché $x \neq y$, esiste un indice $j$ con $x_j \neq y_j$.

Si ha $h_a(x) = h_a(y)$ se e solo se
$$a_j\,(y_j - x_j) = \sum_{i \neq j} a_i (x_i - y_i) \bmod m$$
Si pongono $z = y_j - x_j$ e $\alpha = \sum_{i \neq j} a_i (x_i - y_i)$, la condizione è dunque $a_j z = \alpha \pmod m$.

Si può pensare che $a$ sia scelto a caso in due tempi: prima tutte le coordinate $a_i$ con $i \neq j$, poi $a_j$. Quindi si può assumere che le $a_i$ con $i \neq j$ siano **fissate**, e con esse $\alpha$.

Poiché $m$ è **primo** e $z \neq 0 \pmod m$, $z$ ha un **inverso moltiplicativo** $z^{-1}$, cioè $z \cdot z^{-1} = 1 \pmod m$. Allora la condizione diventa
$$a_j = z^{-1} \alpha \bmod m$$
e dunque
$$\Pr[h_a(x) = h_a(y)] \leq \frac{1}{m} \qquad \square$$

*(extra, non da slide)* L'ultimo passo, che la slide non esplicita: con le altre coordinate fissate, $z^{-1}\alpha \bmod m$ è **un unico valore** in $\{0,\ldots,m-1\}$, e $a_j$ è uniforme su $m$ valori, quindi coincide con quel valore con probabilità $1/m$. Che $z \neq 0 \pmod m$ segue da $x_j \neq y_j$ con entrambe le cifre in $\{0, \ldots, m-1\}$, quindi $0 < |y_j - x_j| < m$. La primalità di $m$ serve proprio per avere l'inverso: con $m$ composto $z$ potrebbe non averlo.
## Un'altra famiglia universale: $h_{a,b}(x) = ((ax+b) \bmod p) \bmod m$
> [!quote] Definizione — La famiglia $\mathcal{H} = \{h_{a,b} : a, b \in U\}$
> Si sceglie **una volta** un numero primo $p \geq |U|$. Dati $a, b \in U$,
> $$h_{a,b}(x) = \bigl[(ax + b) \bmod p\bigr] \bmod m$$
> La famiglia è $\mathcal{H} = \{h_{a,b} : a, b \in U\}$.

La slide presenta questa famiglia come un'altra famiglia universale, senza dimostrarlo. *(extra, non da slide)* Qui una funzione è individuata da **due** valori $a, b$ (contro il vettore $a$ della famiglia precedente) e l'elemento $x$ è trattato come un unico intero, senza la scomposizione in $r$ cifre.
## Scegliere dinamicamente la dimensione della tabella
$S$ cambia nel tempo e si vuole usare spazio $O(|S|)$: la tabella deve crescere e restringersi insieme a $S$.

> [!quote] Definizione — Parametri
> - $n$: numero di elementi attualmente nella tabella, cioè $n = |S|$;
> - $N$: **dimensione virtuale** della tabella;
> - $m$: **dimensione effettiva** della tabella, un numero primo tra $N$ e $2N$.

> [!quote] Definizione — Tecnica del raddoppio e dimezzamento
> Si parte con $n = N = 1$.
> - Quando $n > N$: si pone $N := 2N$, si sceglie un nuovo $m$, si fa il **re-hash** di tutti gli elementi (in tempo $O(n)$).
> - Quando $n < N/4$: si pone $N := N/2$, si sceglie un nuovo $m$, si fa il **re-hash** di tutti gli elementi (in tempo $O(n)$).

> [!quote] Teorema — Costo ammortizzato
> Con la tecnica di raddoppio e dimezzamento, ogni inserimento o cancellazione costa tempo **$O(1)$ ammortizzato**.

La slide enuncia il risultato senza dimostrarlo. La [[02 - Union-Find#Euristica union by size (QuickFind)|analisi ammortizzata]] è lo stesso tipo di ragionamento: un'operazione costosa ogni tanto, pagata da molte operazioni economiche.

> [!info] Idea della dimostrazione *(extra, non da slide)*
> Un re-hash costa $O(n) = O(N)$. Subito dopo un re-hash la dimensione virtuale è $N'$ e il numero di elementi è circa $N'/2$: dopo un raddoppio ($N' = 2N$) si ha $n = N+1 \approx N'/2$, dopo un dimezzamento ($N' = N/2$) si ha $n < N/4 = N'/2$. Per arrivare al re-hash successivo servono quindi $\Omega(N')$ operazioni (inserimenti per superare $N'$, cancellazioni per scendere sotto $N'/4$). Il costo $O(N')$ del re-hash si spalma su $\Omega(N')$ operazioni: $O(1)$ ciascuna.
## Cosa c'è dopo
Le ultime slide presentano la randomizzazione come strumento algoritmico potente (funzioni e tabelle hash, campionamento, sketch) e due problemi risolti con essa: il **conteggio degli elementi distinti in uno stream** (spazio $O(\log d)$ con i contatori probabilistici, contro $O(d)$ o $O(|U|)$) e la **ricerca di elementi simili** con la tecnica LSH (tempo e spazio $O(N \,\mathrm{polylog}\, N)$ invece di $\Theta(N^2)$); per approfondire, il corso *Algorithms for Big Data* (prof. Clementi).
## Mappa nota ↔ slide
Riferimenti a `Materiale Didattico/Modulo II/Slide/10_hash_table_2025.pdf` (14 pagine). Il deck è **in inglese**.

| Sezione della nota | Slide |
|---|---|
| Il problema del dizionario | **p. 2** (operazioni, sfida, alberi bilanciati contro tabelle hash) · p. 1 (titolo e riferimenti) |
| Hashing con chaining | **p. 3** (idea, collisione, chaining, insert/delete/look-up) |
| Scegliere una buona funzione hash | **p. 4** (caso pessimo deterministico, approccio ovvio) |
| Hashing universale | **p. 5** (definizione) · **p. 6** (teorema e dimostrazione) |
| Famiglia $h_a(x) = \sum a_i x_i \bmod m$ | **p. 7** (definizione, word RAM) · **pp. 8-9** (dimostrazione di universalità; p. 9 è p. 8 con il passo finale) |
| Famiglia $h_{a,b}$ | **p. 10** |
| Dimensione dinamica della tabella | **p. 11** (raddoppio e dimezzamento, $O(1)$ ammortizzato) |
| Cosa c'è dopo | pp. 12-14 (p. 14 è p. 13 con il riquadro su *Algorithms for Big Data*) |
