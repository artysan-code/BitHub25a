---
tags:
  - algoritmi
  - dp
slide: ["06"]
capitolo: "Kleinberg-Tardos cap. 6"
---
# Programmazione Dinamica III: Sequence Alignment e Bellman-Ford
Questa nota estende la [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|programmazione dinamica]] a due problemi classici di natura molto diversa: il **Sequence Alignment** (allineamento di sequenze), che misura quanto sono simili due stringhe tramite la *distanza di edit*, e il **Bellman-Ford-Moore**, che risolve il problema dei cammini minimi su grafi con pesi arbitrari — anche negativi — dove l'algoritmo di [[10 - Cammini Minimi e Dijkstra|Dijkstra]] non è applicabile. Per entrambi si deriverà una ricorrenza DP, un algoritmo bottom-up e si analizzeranno tempo e spazio.
## Sequence Alignment
### Motivazione e modello dei costi
Dati due testi — ad esempio le parole `ocurrance` e `occurrence`, oppure due sequenze di DNA — si vuole quantificare quanto è costoso trasformare l'una nell'altra tramite inserzioni, cancellazioni e sostituzioni di caratteri. L'approccio formale consiste nell'allineare le due stringhe, eventualmente inserendo dei **gap** (carattere vuoto `–`), e sommare i costi delle differenze. La distanza di edit ha applicazioni in bioinformatica, correzione ortografica, traduzione automatica, riconoscimento vocale ed estrazione di informazioni.

> [!quote] Definizione — Edit distance (Levenshtein 1966, Needleman–Wunsch 1970)
> Siano $X = x_1 x_2 \ldots x_m$ e $Y = y_1 y_2 \ldots y_n$ due stringhe. Il modello dei costi è:
> - **Gap penalty** $\delta \geq 0$: costo per lasciare un carattere senza corrispondenza (gap).
> - **Mismatch penalty** $\alpha_{pq} \geq 0$: costo per accoppiare il carattere $p$ con il carattere $q$; convenzionalmente $\alpha_{pp} = 0$.
>
> **Perché una matrice e non un numero solo.** Negli esempi si usa un unico $\alpha_{\text{mismatch}}$ per semplicità, ma la definizione è volutamente a **coppie**: il costo di scambiare due caratteri dipende da *quali* caratteri sono. Le slide 5–6 mostrano i due casi reali — la *confusion matrix* dell'inglese, dove confondere `e` con `a` è molto più frequente che confonderla con `q`, e la matrice **BLOSUM** per le proteine, dove i costi sono un dato biologico sulla sostituibilità degli amminoacidi. La ricorrenza non cambia di una virgola: cambia solo da dove si legge $\alpha_{x_i y_j}$.
> La **distanza di edit** tra $X$ e $Y$ è il costo minimo di un allineamento tra le due stringhe.

![[dp3_edit_distance.png]]
Come si legge un allineamento: le due stringhe sono incolonnate carattere per carattere, le celle scure segnano dove si paga. La terza colonna è un **gap** (`–` sopra, `G` sotto: costo $\delta$), la settima e l'ottava sono **mismatch** (`CT` contro `GA`: costo $\alpha_{CG} + \alpha_{TA}$). Tutto il resto è match e non costa nulla, per la convenzione $\alpha_{pp} = 0$ che la slide dichiara a lato. (slide 4, che nel deck 06 coincide con la pagina 4 del PDF: lo sfasamento comincia da pagina 9)

> [!quote] Definizione — Allineamento
> Un **allineamento** $M$ è un insieme di coppie ordinate $(x_i, y_j)$ tale che:
> 1. ogni carattere appare in **al più una** coppia;
> 2. non ci sono **incroci**: se $(x_i, y_j) \in M$ e $(x_{i'}, y_{j'}) \in M$ con $i < i'$, allora $j < j'$.
> Il **costo** dell'allineamento è:
> $$\text{cost}(M) = \sum_{(x_i,\, y_j)\in M} \alpha_{x_i y_j} \;+\; \delta \cdot |\{i : x_i \text{ non in }M\}| \;+\; \delta \cdot |\{j : y_j \text{ non in }M\}|$$

> [!example] Esempio — PALETTE vs PALATE ($\delta = 2$, $\alpha_{\text{mismatch}} = 1$)
> ```
>   P   A   L   E   T   T   E
>   P   A   L   –   A   T   E
> ```
> Costo = $\delta + \alpha_{EA}$ = $2 + 1 = 3$ (1 gap, 1 mismatch).
> Questo è l'allineamento ottimo per questi parametri.
### Struttura della sotto-soluzione ottima
**Definizione del sotto-problema.** Sia $\text{OPT}(i, j)$ il costo minimo dell'allineamento dei prefissi $x_1 \ldots x_i$ e $y_1 \ldots y_j$.

**Obiettivo.** Calcolare $\text{OPT}(m, n)$.

Fissato un allineamento ottimo di $x_1 \ldots x_i$ con $y_1 \ldots y_j$, l'ultimo carattere di ciascun prefisso deve cadere in uno dei tre casi:
- **Caso 1 — match/mismatch:** $x_i$ è accoppiato con $y_j$; si paga $\alpha_{x_i y_j}$ più il costo ottimo dell'allineamento dei prefissi rimanenti $x_1 \ldots x_{i-1}$ e $y_1 \ldots y_{j-1}$.
- **Caso 2a — gap su $X$:** $x_i$ è lasciato senza corrispondenza; si paga $\delta$ più il costo ottimo di $x_1 \ldots x_{i-1}$ con $y_1 \ldots y_j$.
- **Caso 2b — gap su $Y$:** $y_j$ è lasciato senza corrispondenza; si paga $\delta$ più il costo ottimo di $x_1 \ldots x_i$ con $y_1 \ldots y_{j-1}$.
Restano da giustificare due cose: che i tre casi siano **esaustivi**, e che in ciascuno il residuo sia **ottimo**.

**Perché i tre casi sono esaustivi.** Non è ovvio come nel WIS, e dipende dalla condizione di **non incrocio** nella definizione di allineamento. Consideriamo gli ultimi due caratteri $x_i$ e $y_j$: se non sono accoppiati **fra loro**, allora almeno uno dei due non è accoppiato affatto.
1. Per assurdo, siano entrambi accoppiati ma non fra loro: $(x_i, y_k)$ con $k < j$, e $(x_h, y_j)$ con $h < i$.
2. Si hanno allora due coppie $(x_h, y_j)$ e $(x_i, y_k)$ con $h < i$ ma $j > k$.
3. Questo è esattamente un **incrocio**, vietato dalla condizione 2 della definizione di allineamento.
4. Dunque almeno uno fra $x_i$ e $y_j$ è privo di corrispondenza, e si ricade nel Caso 2a o 2b; se invece sono accoppiati fra loro si è nel Caso 1. I tre casi coprono quindi tutte le possibilità. $\square$

**Perché il residuo è ottimo** (argomento di taglia-e-incolla, lo stesso visto in [[04 - Programmazione Dinamica I (Weighted Independent Set)#Il cuore dell'argomento: perché il residuo deve essere ottimo|DP I]]). Nel Caso 1, l'allineamento ottimo di $x_1 \ldots x_i$ con $y_1 \ldots y_j$ è formato dalla coppia $(x_i, y_j)$ più un allineamento dei prefissi $x_1 \ldots x_{i-1}$ e $y_1 \ldots y_{j-1}$. Se quest'ultimo non fosse di costo minimo, lo si potrebbe **sostituire** con uno migliore — la sostituzione è lecita perché non tocca la coppia $(x_i, y_j)$ né introduce incroci con essa, dato che tutti i suoi indici sono minori di $i$ e di $j$ — ottenendo un allineamento complessivo di costo inferiore, contro l'ipotesi di ottimalità. Identico ragionamento nei casi 2a e 2b.

> [!quote] Proprietà — Equazione di Bellman (Sequence Alignment)
> $$\text{OPT}(i,\,j) = \begin{cases} j\,\delta & \text{se } i = 0 \\ i\,\delta & \text{se } j = 0 \\ \min\!\bigl\{\,\alpha_{x_i y_j} + \text{OPT}(i-1,\,j-1),\;\; \delta + \text{OPT}(i-1,\,j),\;\; \delta + \text{OPT}(i,\,j-1)\,\bigr\} & \text{altrimenti} \end{cases}$$
### Algoritmo bottom-up
La ricorrenza ha la proprietà che $\text{OPT}(i, j)$ dipende solo da celle con indici strettamente minori: la matrice si riempie per righe (o per colonne) in modo che ogni cella sia già disponibile quando serve.
```pseudo
\begin{algorithm}
\caption{Sequence-Alignment($m, n, x_1, \ldots, x_m, y_1, \ldots, y_n, \delta, \alpha$)}
\begin{algorithmic}
\For{$i \gets 0$ \To $m$}
  \State $M[i, 0] \gets i \cdot \delta$
\EndFor
\For{$j \gets 0$ \To $n$}
  \State $M[0, j] \gets j \cdot \delta$
\EndFor
\For{$i \gets 1$ \To $m$}
  \For{$j \gets 1$ \To $n$}
    \State $M[i, j] \gets \min\{\, \alpha_{x_i y_j} + M[i-1, j-1],\;\; \delta + M[i-1, j],\;\; \delta + M[i, j-1] \,\}$
  \EndFor
\EndFor
\State \Return $M[m, n]$
\end{algorithmic}
\end{algorithm}
```

**Matrice riempita per intero** su un'istanza minima: $X = \texttt{AGT}$ ($m=3$), $Y = \texttt{AT}$ ($n=2$), con $\delta = 2$ e $\alpha_{\text{mismatch}} = 1$.

Prima si riempiono i bordi: la riga $i=0$ e la colonna $j=0$ sono i casi base $j\delta$ e $i\delta$ — allineare un prefisso contro la stringa vuota costa un gap per ogni carattere. Poi ogni cella interna è il minimo fra tre celle già calcolate: la diagonale (match/mismatch), quella sopra (gap su $X$), quella a sinistra (gap su $Y$).

|  | $\varepsilon$ | **A** | **T** |
|---|---|---|---|
| $\varepsilon$ | 0 | 2 | 4 |
| **A** | 2 | **0** | 2 |
| **G** | 4 | 2 | **1** |
| **T** | 6 | 4 | **2** |

Due celle lette per esteso, perché è lì che si capisce il meccanismo:
- **cella (A, A)** $= 0$. I tre candidati sono: diagonale $\alpha_{AA} + M[0,0] = 0 + 0 = 0$ (i caratteri coincidono, il match è gratis); sopra $\delta + M[0,1] = 2 + 2 = 4$; sinistra $\delta + M[1,0] = 2 + 2 = 4$. Vince la diagonale.
- **cella (T, T)** $= 2$, l'angolo in basso a destra, cioè la risposta. Candidati: diagonale $\alpha_{TT} + M[2,1] = 0 + 2 = 2$; sopra $\delta + M[2,2] = 2 + 1 = 3$; sinistra $\delta + M[3,1] = 2 + 4 = 6$. Vince la diagonale: 2.

La distanza di edit è **2**, e corrisponde all'allineamento
```
  A   G   T
  A   –   T
```
un solo gap, sulla `G` che $Y$ non ha: costo $\delta = 2$. Il **traceback** è proprio il cammino che ripercorre a ritroso le scelte vincenti — diagonale, sopra, diagonale — dall'angolo in basso a destra fino a $(0,0)$.

> [!info] Come orientarsi nella matrice
> **Diagonale = consumo un carattere da entrambe le stringhe** (li accoppio). **Sopra = consumo solo da $X$** (gap su $Y$). **Sinistra = consumo solo da $Y$** (gap su $X$). Ogni mossa avanza di un carattere in almeno una delle due stringhe: per questo il cammino ha lunghezza al più $m + n$ e l'algoritmo termina.

> [!quote] Teorema — Complessità Sequence Alignment
> L'algoritmo DP calcola la distanza di edit (e un allineamento ottimo tramite traceback) di due stringhe di lunghezze $m$ e $n$ in tempo $\Theta(mn)$ e spazio $\Theta(mn)$.

| Risorsa | Costo |
|---|---|
| Tempo | $\Theta(mn)$ — $mn$ celle, ciascuna in $O(1)$ perché dipende da al più tre celle già calcolate |
| Spazio | $\Theta(mn)$ — intera matrice $M$ |

> [!info] Regola — lo spazio quadratico lo chiede il traceback, non il valore
> Se serve **solo la distanza di edit**, bastano due colonne adiacenti alla volta: ogni cella dipende dalla colonna corrente e dalla precedente, quindi $O(m+n)$ di spazio è sufficiente.
> È il **traceback** a costare: ripercorrere le scelte vincenti da $(m,n)$ fino a $(0,0)$ richiede di aver conservato tutte le celle, da cui $\Theta(mn)$.
> Questa è esattamente la tensione da cui nasce l'algoritmo di Hirschberg: tenere lo spazio lineare **e** recuperare comunque l'allineamento. Vale la pena saperla enunciare in una riga, perché è il ponte fra le due metà di questa sezione.
### Traceback per ricostruire l'allineamento
Dopo aver riempito la matrice, si ripercorre a ritroso da $M[m, n]$ a $M[0, 0]$: in ogni cella $(i, j)$ si identifica quale dei tre casi ha determinato il minimo e si segue la freccia corrispondente (diagonale, su, sinistra). I caratteri accoppiati generano match/mismatch; i movimenti orizzontali o verticali generano gap.

> [!example] Traceback — PALETTE ($m=7$) vs PALATE ($n=6$), $\delta=2$, $\alpha_{\text{mis}}=1$
> La matrice $M$ riempita per righe:
> ```
>        ε    P    A    L    A    T    E
>   ε    0    2    4    6    8   10   12
>   P    2    0    2    4    6    8   10
>   A    4    2    0    2    4    6    8
>   L    6    4    2    0    2    4    6
>   E    8    6    4    2    1    3    4
>   T   10    8    6    4    3    1    3
>   T   12   10    8    6    5    3    2
>   E   14   12   10    8    7    5    3
> ```
> Il traceback da $M[7,6]=3$ dà l'allineamento `PALETTE` / `PAL–ATE`: 1 gap + 1 mismatch, costo $2+1=3$.

![[dp3_palette_palate.png]]
Le frecce sono il traceback sulla stessa matrice: si parte dal 3 cerchiato in basso a destra e si risale fino a $(0,0)$. Ogni **diagonale** accoppia due caratteri (`P`-`P`, `A`-`A`, `L`-`L`, `T`-`T`, `E`-`E`), ogni freccia **verticale** è un gap. Il cammino tocca una verticale sola — la `E` di `PALETTE` senza corrispondenza — più il mismatch `T`/`A`: costo $2 + 1 = 3$. (slide numerata «12», pagina 11 del PDF)
## Algoritmo di Hirschberg (spazio lineare)
La matrice $\Theta(mn)$ può essere proibitiva per stringhe lunghe. Hirschberg (1975) ha dimostrato che si può ottenere sia l'allineamento che il valore ottimo in spazio $O(m + n)$, mantenendo il tempo $O(mn)$, combinando divide-et-impera con la DP.

> [!quote] Teorema — Hirschberg
> Esiste un algoritmo per trovare un allineamento ottimo in tempo $O(mn)$ e spazio $O(m + n)$.

**Prima osservazione — spazio $O(m+n)$ per il valore.**
Per calcolare la colonna $j$ della matrice basta la colonna $j-1$: si mantengono quindi solo due vettori di lunghezza $m+1$ (la colonna corrente e quella precedente), riducendo lo spazio a $O(m+n)$. Il problema è che questo non permette il traceback: si perde la struttura dell'allineamento.

**Grafo di edit.** Si interpreta la matrice DP come un grafo orientato in cui ogni nodo $(i,j)$ ha:
- un arco diagonale verso $(i-1, j-1)$ di peso $\alpha_{x_i y_j}$,
- un arco verticale verso $(i-1, j)$ di peso $\delta$,
- un arco orizzontale verso $(i, j-1)$ di peso $\delta$.

![[dp3_grafo_edit_distance.png]]
Il cambio di punto di vista che rende possibile Hirschberg: la matrice DP diventa un **grafo**, e allineare due stringhe diventa cercare un cammino minimo da $(0,0)$ a $(m,n)$. Sulla figura si vedono i tre archi uscenti da un nodo con i rispettivi pesi — diagonale $\alpha_{x_i y_j}$, verticale e orizzontale $\delta$ — e un cammino evidenziato in blu. Il lemma scritto in alto, $f(i,j) = \text{OPT}(i,j)$, è ciò che autorizza a leggere la tabella come distanze. (slide numerata «17», pagina 16 del PDF)

Sia $f(i,j)$ la lunghezza del cammino minimo da $(0,0)$ a $(i,j)$ e $g(i,j)$ quella da $(i,j)$ a $(m,n)$ (calcolata invertendo gli archi e i ruoli dei due estremi). Si ha:
- $f(i,j) = \text{OPT}(i,j)$ per tutti $i,j$ (dim. per induzione forte su $i+j$);
- **(Osservazione 1)** la lunghezza del cammino minimo che passa per $(i,j)$ è $f(i,j) + g(i,j)$;
- $f(\cdot, j)$ e $g(\cdot, j)$ si calcolano ognuna in tempo $O(mn)$ e spazio $O(m+n)$.

> [!quote] Proprietà — Osservazione 2 (Hirschberg)
> Sia $q^*$ l'indice che minimizza $f(q,\, n/2) + g(q,\, n/2)$ su tutti $q \in \{0,\ldots,m\}$. Allora esiste un cammino minimo da $(0,0)$ a $(m,n)$ che passa per $(q^*, n/2)$: questo nodo appartiene all'allineamento ottimo.

**Divide.** Si fissa la colonna centrale $n/2$. Si calcolano $f(q,\, n/2)$ e $g(q,\, n/2)$ per tutti $q$; si trova $q^*$ che minimizza la somma. Il nodo $(q^*, n/2)$ fa parte della soluzione.

**Conquer.** Si richiama ricorsivamente l'algoritmo su $(x_1\ldots x_{q^*},\; y_1\ldots y_{n/2})$ e su $(x_{q^*+1}\ldots x_m,\; y_{n/2+1}\ldots y_n)$.

![[dp3_hirschberg_divide.png]]
Il passo **divide**. La banda rossa verticale è la colonna $n/2$, fissata una volta per tutte; il nodo scuro su quella banda è $q^*$, l'indice che minimizza $f(q, n/2) + g(q, n/2)$. L'Osservazione 2 garantisce che **esiste** un cammino minimo che lo attraversa — quindi il problema si spezza in due metà indipendenti, in alto a sinistra e in basso a destra, su cui si ricorre. Nota che non serve conoscere tutto il cammino: basta un suo punto, e il resto lo trova la ricorsione. (slide numerata «24», pagina 23 del PDF)

> [!quote] Teorema — Analisi di Hirschberg (tempo)
> Sia $T(m, n)$ il tempo di esecuzione massimo dell'algoritmo di Hirschberg su stringhe di lunghezze al più $m$ e $n$. Allora $T(m, n) = O(mn)$.

**Dimostrazione (per induzione forte su $m+n$).** La ricorrenza è
$$T(m, n) \leq T(q^*, n/2) + T(m - q^*, n/2) + O(mn)$$
dove il termine $O(mn)$ conta il calcolo di $f(\cdot, n/2)$, di $g(\cdot, n/2)$ e la ricerca dell'indice $q^*$. Si prova il **claim** $T(m,n) \leq 2cmn$ per una costante $c$ opportuna. Casi base: $T(m,2) \leq cm$ e $T(2,n) \leq cn$. Passo induttivo, applicando l'ipotesi induttiva alle due chiamate ricorsive:
$$T(m,n) \;\leq\; 2c q^* \frac{n}{2} + 2c(m-q^*)\frac{n}{2} + cmn = cq^*n + cmn - cq^*n + cmn = 2cmn \qquad\square$$

> [!quote] Teorema — Analisi di Hirschberg (spazio)
> L'algoritmo usa spazio $\Theta(m+n)$.

**Dimostrazione.** Ogni chiamata ricorsiva usa $\Theta(m)$ spazio per calcolare $f(\cdot, n/2)$ e $g(\cdot, n/2)$; si mantiene solo $\Theta(1)$ spazio per chiamata attiva; il numero di chiamate ricorsive è $\leq n$. $\square$

| Algoritmo | Tempo | Spazio |
|---|---|---|
| DP standard | $\Theta(mn)$ | $\Theta(mn)$ |
| Hirschberg | $O(mn)$ | $\Theta(m+n)$ |

→ **Palestra**: [[Palestra - Programmazione Dinamica#Idea e complessità di Hirschberg|idea e complessità di Hirschberg — domanda costruita]]
## Cammini minimi con pesi negativi: Bellman-Ford-Moore
### Perché Dijkstra non basta
L'algoritmo di [[10 - Cammini Minimi e Dijkstra|Dijkstra]] risolve il problema SSSP in tempo $O(m + n \log n)$ con pesi **non negativi**. In presenza di pesi negativi, la strategia greedy di Dijkstra — estrarre il nodo con distanza minima e fissarla definitivamente — non è più valida: un arco negativo potrebbe abbreviare un cammino già "chiuso".

> [!warning] Dijkstra fallisce con pesi negativi
> Consideriamo il grafo con nodi $s, t, v, w$ e archi:
> ```
>     s ──2──> t
>     s ──6──> v
>     s ──4──> w
>     v ──(−8)──> w
>     w ──3──> t
> ```
> Dijkstra estrae $s$, poi **subito $t$** (stima 2, la minima in coda) e la **fissa definitivamente**. Poi estrae $w$ (stima 4, dall'arco diretto) e infine $v$ (6) — l'ordine è $s, t, w, v$. Solo a quel punto, da $v$, si scoprirebbe $w$ a distanza $6 - 8 = -2$: ma $w$ è già chiuso, e con esso $t$.
> Il vero cammino minimo è $s \to v \to w \to t$, di lunghezza $6 + (-8) + 3 = 1$, mentre Dijkstra restituisce $2$.
> **Reweighting**: sommando $8$ a ogni peso i valori diventano $s\to t = 10$, $s \to v = 14$, $s \to w = 12$, $v \to w = 0$, $w \to t = 11$. Ora $s \to v \to w \to t$ costa $14 + 0 + 11 = 25$, mentre $s \to t$ ne costa $10$: il cammino minimo è **cambiato**. Il motivo è che un cammino di $k$ archi viene penalizzato di $8k$, quindi i cammini lunghi — proprio quelli che gli archi negativi rendevano convenienti — sono i più danneggiati.

![[dp3_dijkstra_reweight.png]]
I due tentativi falliti, come li presenta il prof. **In alto** il grafo originale: la nota a lato («Dijkstra selects the vertices in the order $s, t, w, v$») è la chiave di lettura — $t$ viene chiuso per primo, a 2, e non verrà più aggiornato. **In basso** lo stesso grafo con $+8$ su ogni arco: il cammino minimo passa da $s\to v\to w\to t$ a $s \to t$, cioè il reweighting ha cambiato la risposta. Attenzione a copiare i pesi esattamente da qui: invertire $s\to t$ e $s\to v$ distrugge il controesempio, perché Dijkstra tornerebbe a dare il risultato corretto. (slide numerata «30», pagina 29 del PDF)
### Cicli negativi
> [!quote] Definizione — Ciclo negativo
> Un **ciclo negativo** è un ciclo diretto $W = v_1 \to v_2 \to \ldots \to v_k \to v_1$ per cui
> $$\ell(W) = \sum_{e \in W} \ell_e < 0$$

![[dp3_ciclo_negativo.png]]
Il ciclo in nero ha pesi $5,\; -3,\; 4,\; -4,\; -3$: la somma è $-1 < 0$, quindi è un ciclo negativo. Gli archi grigi appartengono al grafo ma non al ciclo. Serve avere in mente questa figura quando si legge il Lemma 1: girare su quel ciclo abbassa il costo di 1 ad ogni giro, e nulla impedisce di girare all'infinito. (slide numerata «31», pagina 30 del PDF)

> [!quote] Lemma 1 — Ciclo negativo e inesistenza del minimo
> Se un qualsiasi cammino da $v$ a $t$ contiene un ciclo negativo, allora **non esiste** un cammino minimo da $v$ a $t$.

**Dimostrazione.** Percorrendo il ciclo negativo un numero arbitrario di volte si ottiene un cammino da $v$ a $t$ di lunghezza $\to -\infty$: nessun valore è minimo, perché ogni giro aggiuntivo lo abbassa ancora. $\square$

> [!quote] Lemma 2 — Assenza di cicli negativi e semplicità
> Se $G$ non ha cicli negativi, esiste un cammino minimo da $v$ a $t$ che è **semplice** (senza ripetizioni di nodi) e ha al più $n - 1$ archi.

**Dimostrazione.** Tra tutti i cammini minimi da $v$ a $t$ si prenda quello con il minor numero di archi. Se contenesse un ciclo diretto $W$, quest'ultimo avrebbe peso $\ell(W) \geq 0$ (per assenza di cicli negativi), e lo si potrebbe rimuovere senza aumentare il costo totale — ottenendo un cammino minimo con meno archi, contro la scelta. Dunque il cammino è semplice, e un cammino semplice su $n$ nodi ha al più $n-1$ archi. $\square$
### Formulazione DP
**Definizione del sotto-problema.** Sia $\text{OPT}(i, v)$ la lunghezza del cammino minimo da $v$ a $t$ che usa **al più $i$ archi**.

**Obiettivo.** Calcolare $\text{OPT}(n-1, v)$ per ogni $v$ (per il Lemma 2, bastano $n-1$ archi se non ci sono cicli negativi).

Due casi per il cammino ottimo da $v$ a $t$ con $\leq i$ archi:
- **Caso 1:** il cammino usa $\leq i-1$ archi $\Rightarrow \text{OPT}(i,v) = \text{OPT}(i-1,v)$.
- **Caso 2:** il cammino usa esattamente $i$ archi; sia $(v,w)$ il primo arco $\Rightarrow \text{OPT}(i,v) = \ell_{vw} + \text{OPT}(i-1,w)$, scegliendo $w$ ottimale.

> [!quote] Proprietà — Equazione di Bellman (cammini minimi)
> $$\text{OPT}(i,\,v) = \begin{cases} 0 & \text{se } i = 0 \text{ e } v = t \\ +\infty & \text{se } i = 0 \text{ e } v \neq t \\ \min\!\Bigl(\text{OPT}(i-1,\,v),\;\; \min_{(v,w)\in E}\bigl\{\ell_{vw} + \text{OPT}(i-1,\,w)\bigr\}\Bigr) & \text{se } i > 0 \end{cases}$$

```pseudo
\begin{algorithm}
\caption{Shortest-Paths($V, E, \ell, t$) — algoritmo DP naïve}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State $M[0, v] \gets +\infty$
\EndFor
\State $M[0, t] \gets 0$
\For{$i \gets 1$ \To $n-1$}
  \ForAll{nodo $v \in V$}
    \State $M[i, v] \gets M[i-1, v]$
    \ForAll{arco $(v, w) \in E$}
      \State $M[i, v] \gets \min\{\, M[i, v],\;\; M[i-1, w] + \ell(v,w) \,\}$
    \EndFor
  \EndFor
\EndFor
\State \Return $M[n-1, \cdot]$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema 1 — Complessità dell'algoritmo DP
> Su un grafo $G = (V, E)$ senza cicli negativi, l'algoritmo calcola la lunghezza del cammino minimo da ogni $v$ a $t$ in tempo $\Theta(mn)$ e spazio $\Theta(n^2)$.

**Dimostrazione.** La tabella $M$ ha $n$ righe (indice $i = 0, \ldots, n-1$) e $n$ colonne (un nodo per colonna): spazio $\Theta(n^2)$. Ogni iterazione $i$ esamina ogni arco una volta: costo $\Theta(m)$ per iterazione, $n-1$ iterazioni, totale $\Theta(mn)$. $\square$

**Ricostruzione del cammino.** Due approcci:
1. Mantenere `successor[i, v]` puntando al nodo successivo nel cammino minimo con $\leq i$ archi.
2. Dopo aver calcolato $M$, costruire il sotto-grafo degli archi "attivi" $\{(v,w) : M[i,v] = M[i-1,w] + \ell_{vw}\}$: ogni cammino diretto in tale sotto-grafo è un cammino minimo.
### Bellman-Ford-Moore: implementazione efficiente
Lo spazio $\Theta(n^2)$ è spesso inaccettabile. L'ottimizzazione chiave usa:
- Un vettore **$d[v]$** che mantiene la migliore stima corrente della distanza $v \leadsto t$.
- Un vettore **$\text{successor}[v]$** che punta al nodo successivo sul cammino corrente.
- **Ottimizzazione di prestazione:** alla passata $i$, l'arco $(v,w)$ viene considerato solo se $d[w]$ è stato aggiornato alla passata $i-1$ (non ha senso riesaminare nodi la cui distanza non è cambiata).

```pseudo
\begin{algorithm}
\caption{Bellman-Ford-Moore($V, E, \ell, t$)}
\begin{algorithmic}
\ForAll{nodo $v \in V$}
  \State $d[v] \gets +\infty$
  \State $\text{successor}[v] \gets \text{null}$
\EndFor
\State $d[t] \gets 0$
\For{$i \gets 1$ \To $n-1$}
  \ForAll{nodo $w \in V$}
    \If{$d[w]$ è stato aggiornato alla passata $i-1$}
      \ForAll{arco $(v, w) \in E$}
        \If{$d[v] > d[w] + \ell(v,w)$}
          \State $d[v] \gets d[w] + \ell(v,w)$
          \State $\text{successor}[v] \gets w$
        \EndIf
      \EndFor
    \EndIf
  \EndFor
  \If{nessun $d[\cdot]$ è cambiato in questa passata}
    \State \textbf{break}
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!info] Variante single-source
> Le slide impostano il problema come *single-destination* (trovare i cammini minimi da ogni $v$ verso $t$). La variante *single-source* (da $s$ verso ogni $v$) è del tutto equivalente: basta invertire gli archi e scambiare $s$ con $t$.
### Correttezza e analisi
> [!quote] Lemma 3
> Per ogni nodo $v$: $d[v]$ è la lunghezza di **qualche** cammino $v \leadsto t$ (non per forza minimo durante l'esecuzione).

> [!quote] Lemma 4
> Per ogni nodo $v$: $d[v]$ è **monotona non crescente** nel corso dell'algoritmo.

> [!quote] Lemma 5 — Invariante di passata
> Dopo la passata $i$, per ogni nodo $v$:
> $$d[v] \;\leq\; \text{lunghezza del cammino minimo da } v \text{ a } t \text{ che usa} \leq i \text{ archi}$$

**Dimostrazione (per induzione su $i$).** Caso base $i=0$: $d[t]=0$ (unico cammino con $0$ archi, quello da $t$ a sé stesso) e tutti gli altri $d[v] = +\infty$ (nessun cammino con $0$ archi da $v \neq t$ a $t$). Passo induttivo: sia $P = v \to w \to \ldots \to t$ un cammino con $\leq i+1$ archi, $(v,w)$ il primo arco e $P'$ il sotto-cammino $w \leadsto t$, che ha $\leq i$ archi. Per ipotesi induttiva, dopo la passata $i$, $d[w] \leq \ell(P')$. All'esame dell'arco $(v,w)$ nella passata $i+1$ si ottiene $d[v] \leq \ell_{vw} + d[w] \leq \ell_{vw} + \ell(P') = \ell(P)$; e per il Lemma 4, $d[v]$ non aumenta più. Poiché $P$ era un qualsiasi cammino con $\leq i+1$ archi, $d[v]$ non supera il minimo fra tutti. $\square$

> [!quote] Teorema 2 — Correttezza e complessità di Bellman-Ford-Moore
> Assumendo assenza di cicli negativi, l'algoritmo calcola la lunghezza del cammino minimo da ogni $v$ a $t$ in tempo $O(mn)$ e spazio $\Theta(n)$.

**Dimostrazione.** Per il Lemma 2 esiste un cammino minimo semplice con $\leq n-1$ archi; per il Lemma 5, dopo $n-1$ passate $d[v]$ non supera la lunghezza del cammino minimo con $\leq n-1$ archi, cioè la lunghezza del cammino minimo; per il Lemma 3 $d[v]$ è sempre la lunghezza di *qualche* cammino $v \leadsto t$, quindi non è mai inferiore al minimo. Le due disuguaglianze danno l'uguaglianza. Il tempo è $O(mn)$ ($n-1$ passate da $O(m)$ ciascuna) e lo spazio $\Theta(n)$ (due vettori di dimensione $n$). $\square$

> [!info] Velocità pratica
> Bellman-Ford-Moore è tipicamente molto più veloce di $O(mn)$: l'arco $(v,w)$ viene considerato alla passata $i+1$ solo se $d[w]$ è stato aggiornato alla passata $i$. Se il cammino minimo ha $k$ archi, l'algoritmo termina dopo $\leq k$ passate.
### Ricostruzione e grafo dei successori
> [!warning] I puntatori successor non sono affidabili durante l'esecuzione
> **Durante** l'esecuzione, la catena `successor` può essere inconsistente. Esempio dalle slide (nodi in ordine $t, 1, 2, 3$):
> ```
>   Dopo passata 1:
>   successor[2] = 1,  d[2] = 20
>   successor[1] = 3,  d[1] = 2
>   successor[3] = t,  d[3] = 1
>   d[t] = 0
> ```
> Seguendo la catena da 2: $2 \to 1 \to 3 \to t$; il valore memorizzato è $d[2]=20$, ma la lunghezza reale di quel cammino è **strettamente inferiore** a $20$ (perché $d[2]$ fu fissato quando $d[1]$ valeva ancora $10$, prima che scendesse a $2$). Pertanto la "claim" che seguire i successori restituisca un cammino di lunghezza $d[v]$ è **falsa** durante l'esecuzione.
> C'è di più: se il grafo contiene un **ciclo negativo**, il grafo dei successori può addirittura presentare cicli diretti durante l'esecuzione (le slide lo mostrano con un secondo esempio a 4 nodi). È il rovescio del Lemma 6 più sotto — che in assenza di cicli negativi garantisce invece che il grafo dei successori è aciclico.
> Solo **al termine** dell'algoritmo (quando nessun $d[\cdot]$ cambia più) la catena dei successori forma un cammino minimo.

> [!quote] Lemma 6 — Cicli nel grafo dei successori
> Qualsiasi ciclo diretto nel **grafo dei successori** è un ciclo negativo.

**Dimostrazione.** Se `successor[v] = w`, allora $d[v] \geq d[w] + \ell_{vw}$ (con uguaglianza nell'istante in cui il successore viene impostato; poi $d[w]$ può solo decrescere, mentre $d[v]$ decresce solo se il successore di $v$ viene reimpostato). Sia $v_1 \to v_2 \to \ldots \to v_k \to v_1$ un ciclo nel grafo dei successori, e sia $(v_k, v_1)$ l'ultimo arco aggiunto. Subito prima di tale aggiornamento valgono
$$d[v_1] \geq d[v_2] + \ell(v_1,v_2), \quad d[v_2] \geq d[v_3] + \ell(v_2,v_3), \quad \ldots, \quad d[v_k] > d[v_1] + \ell(v_k,v_1)$$
dove l'ultima disuguaglianza è **stretta** perché in quell'istante si sta abbassando $d[v_k]$ (la condizione di aggiornamento $d[v_k] > d[v_1] + \ell_{v_k v_1}$ è vera). Sommando membro a membro e semplificando i $d[\cdot]$:
$$0 > \ell(v_1,v_2) + \ell(v_2,v_3) + \ldots + \ell(v_{k-1},v_k) + \ell(v_k,v_1) = \ell(W)$$
Dunque $W$ è un ciclo negativo. $\square$

> [!quote] Teorema 3 — Correttezza dei successori a terminazione
> Assumendo assenza di cicli negativi, al termine di Bellman-Ford-Moore, seguendo i puntatori `successor` da ogni $v$ si ottiene un cammino minimo $v \leadsto t$ di lunghezza $d[v]$.

**Dimostrazione.** Per il Lemma 6, il grafo dei successori non ha cicli diretti (altrimenti esisterebbe un ciclo negativo, contro l'ipotesi). Quindi seguire i successori da $v$ porta a $t$ senza ripetere nodi. Sia $v = v_1 \to v_2 \to \ldots \to v_k = t$ tale cammino $P$. A terminazione, per ogni arco $(v_i, v_{i+1})$ con `successor[v_i] = v_{i+1}` vale $d[v_i] = d[v_{i+1}] + \ell(v_i, v_{i+1})$ (i valori non cambiano più, quindi l'uguaglianza dell'istante di impostazione persiste). Sommando lungo $P$:
$$d[v] = d[t] + \ell(v_1,v_2) + \ldots + \ell(v_{k-1},v_k) = 0 + \ell(P)$$
Per il Teorema 2, $d[v]$ è la lunghezza minima di qualsiasi cammino $v \leadsto t$; dunque $P$, che ha proprio lunghezza $d[v]$, è un cammino minimo. $\square$
### Rilevamento di cicli negativi
Per rilevare cicli negativi raggiungibili da $t$, si esegue una **passata aggiuntiva** ($i = n$) dopo le $n-1$ normali:

```pseudo
\begin{algorithm}
\caption{Bellman-Ford-Moore($V, E, \ell, t$) — con rilevamento dei cicli negativi}
\begin{algorithmic}
\State $\ldots$ \Comment{righe 1–12 di Bellman-Ford-Moore: inizializzazione e ciclo principale}
\ForAll{arco $(v, w) \in E$}
  \If{$d[v] > d[w] + \ell(v,w)$}
    \State \Return "esiste un ciclo negativo"
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!quote] Lemma — Correttezza del rilevamento
> Se esiste un ciclo negativo raggiungibile da $t$, la passata $n$ lo rileva.

> [!warning] Le slide chiamano «Lemma 6» due enunciati diversi
> Sulla pagina 46 del PDF il Lemma 6 dice che *ogni ciclo diretto nel grafo dei successori è negativo*; sulla pagina 50 lo stesso numero è riusato per *la passata $n$ rileva il ciclo negativo*. Sono risultati distinti. Questa nota numera il primo e lascia il secondo senza numero, chiamandolo per esteso: se incroci nota e slide, non cercare una corrispondenza fra i numeri.

**Dimostrazione (per assurdo).** Se non ci fosse nessun ciclo negativo, la passata $n$ non cambierebbe nulla (le distanze sono già ottime dopo $n-1$ passate, per il Teorema 2). Se invece esiste un ciclo negativo $W = v_1 \to \ldots \to v_k \to v_1$, si assuma per assurdo che il test $d[v] > d[w] + \ell_{vw}$ della passata aggiuntiva sia sempre falso. Allora $d[v_i] \leq d[v_{i+1}] + \ell(v_i, v_{i+1})$ per ogni $i$ (indici ciclici, $v_{k+1} = v_1$). Sommando lungo $W$ e semplificando i $d[\cdot]$ si ottiene $\ell(W) \geq 0$, che contraddice $\ell(W) < 0$. $\square$

La passata aggiuntiva esamina ogni arco una volta sola, quindi costa $O(m)$ — lo stesso di una passata normale — e **non cambia** la complessità asintotica $O(mn)$ dell'algoritmo.
### Esempio di esecuzione
Le slide propongono un grafo su cui provare l'algoritmo. I nodi sono $t, B, C, D, E$ (sulla slide il pozzo $t$ è disegnato come nodo $A$); l'ordine con cui vengono processati è $t, D, C, B, E$. Gli archi, orientati come li usa l'algoritmo *single-destination* (verso $t$), con i relativi pesi:
```
B ──(−1)──> t
C ───4───> t
C ───3───> B
C ───5───> D
B ───1───> D
D ───2───> B
D ──(−3)──> E
E ───2───> B
```

![[dp3_bfm_esempio_grafo.png]]
Il grafo come lo disegna la slide. Il pozzo è il nodo etichettato **A**, ma nell'ordine di visita è chiamato $t$: sono lo stesso nodo. I due archi curvi fra $B$ e $D$ vanno letti con attenzione — sono **due archi distinti in versi opposti**, $B \to D$ di peso 1 e $D \to B$ di peso 2 — ed è lì che si sbaglia a copiare. (slide numerata «40», pagina 39 del PDF)

**Esecuzione.** L'algoritmo è *single-destination*: $d[v]$ è la stima corrente della distanza da $v$ **verso** $t$, e processare il nodo $v$ significa rilassare i suoi archi **uscenti**, cioè $d[v] \gets \min_{(v,w) \in E}\{\ell_{vw} + d[w]\}$. Gli aggiornamenti sono in-place: un nodo processato più tardi nella stessa passata vede già i valori freschi di quelli processati prima.

| passata | $d[t]$ | $d[D]$ | $d[C]$ | $d[B]$ | $d[E]$ |
|---|---|---|---|---|---|
| init | $0$ | $+\infty$ | $+\infty$ | $+\infty$ | $+\infty$ |
| 1 | $0$ | $+\infty$ | $4$ | $-1$ | $1$ |
| 2 | $0$ | $\mathbf{-2}$ | $\mathbf{2}$ | $-1$ | $1$ |
| 3 | $0$ | $-2$ | $2$ | $-1$ | $1$ |

**Passata 1**, nell'ordine $t, D, C, B, E$:
- $t$ è il pozzo, $d[t] = 0$ e non ha archi uscenti;
- $D$: i suoi archi portano a $E$ e $B$, entrambi ancora a $+\infty$, quindi $d[D]$ non cambia — **è la conseguenza dell'ordine di visita**, $D$ viene processato prima di chi gli sta a valle;
- $C$: $\min\{4 + d[t],\, 3 + d[B],\, 5 + d[D]\} = \min\{4, +\infty, +\infty\} = 4$;
- $B$: $\min\{-1 + d[t],\, 1 + d[D]\} = -1$;
- $E$: $2 + d[B] = 2 - 1 = 1$, e qui si vede l'aggiornamento in-place — $E$ usa il valore di $B$ appena calcolato, nella stessa passata.

**Passata 2**: ora $D$ trova $E$ a 1 e chiude a $d[D] = -3 + 1 = -2$; di conseguenza $C$ scende da 4 a $\min\{4,\, 3 - 1,\, 5 - 2\} = 2$, passando per $B$ invece che per l'arco diretto. $B$ ed $E$ restano invariati.

**Passata 3**: nessun valore cambia, l'algoritmo si ferma. Il bound del Lemma 2 concederebbe $n - 1 = 4$ passate: ne sono bastate **due** produttive più una di conferma.

I cammini minimi corrispondenti, leggibili dai puntatori `successor`, sono $B \to t$ ($-1$), $E \to B \to t$ ($1$), $D \to E \to B \to t$ ($-2$) e $C \to B \to t$ ($2$): per $C$ l'arco diretto $C \to t$ di peso 4 **non** è la scelta ottima, nonostante sia l'unico disponibile alla prima passata.

> [!info] Nota sull'esempio
> Il grafo non ha cicli negativi: gli unici cicli diretti sono $B \to D \to B$ (peso $1 + 2 = 3$) e $D \to E \to B \to D$ (peso $-3 + 2 + 1 = 0$), entrambi $\geq 0$; il problema è quindi ben posto. Eseguendo Bellman-Ford-Moore con l'ordine di visita $t, D, C, B, E$, come mostra la tabella qui sopra nessun $d[\cdot]$ cambia più già alla terza passata, e l'algoritmo termina **prima** delle $n-1$ iterazioni (terminazione anticipata): è la conferma pratica che Bellman-Ford-Moore è spesso molto più veloce del worst-case $O(mn)$.
## Confronto Dijkstra vs Bellman-Ford-Moore
| Proprietà | [[10 - Cammini Minimi e Dijkstra\|Dijkstra]] | Bellman-Ford-Moore |
|---|---|---|
| Pesi negativi | No (fallisce) | Sì |
| Cicli negativi | — | Rilevati con passata $n$ |
| Tempo (con heap Fibonacci) | $O(m + n \log n)$ | $O(mn)$ |
| Spazio | $O(n)$ | $\Theta(n)$ |
| Tecnica | Greedy | Programmazione dinamica |
| Applicabilità | Pesi $\geq 0$ | Pesi arbitrari, no cicli neg. |

> [!info] Collegamento con le note precedenti
> - La tecnica DP di questa nota si innesta direttamente su [[04 - Programmazione Dinamica I (Weighted Independent Set)]] e [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]: stessa metodologia (sotto-struttura ottima, ricorrenza, bottom-up).
> - La visita del grafo e la nozione di cammino minimo rimandano a [[08 - Grafi e Visite]] e [[10 - Cammini Minimi e Dijkstra]].
> - Bellman-Ford-Moore è il fondamento teorico del protocollo di routing **RIP** (Routing Information Protocol) nelle reti di calcolatori. *(extra, non da slide)*
## Mappa nota ↔ slide
Il deck `06_DP_III_2025.pdf` ha 50 pagine. **Attenzione alla numerazione**: fino a pagina 8 il numero stampato coincide con la pagina del PDF, da pagina 9 in poi il numero stampato è **pagina + 1** (manca la slide 9). La tabella riporta entrambi.

| Sezione della nota | Pagine PDF | Slide numerate |
|---|---|---|
| Sequence Alignment — motivazione, edit distance, modello dei costi | 3–8 | 3–8 |
| Struttura della sotto-soluzione ottima | 9 | 10 |
| Algoritmo bottom-up | 10 | 11 |
| Traceback per ricostruire l'allineamento | 11 | 12 |
| Complessità del Sequence Alignment | 12 | 13 |
| Algoritmo di Hirschberg (spazio lineare) | 14–26 | 15–27 |
| Perché Dijkstra non basta | 28–29 | 29–30 |
| Cicli negativi, Lemma 1 e Lemma 2 | 30–33 | 31–34 |
| Formulazione DP dei cammini minimi | 34–36 | 35–37 |
| Bellman-Ford-Moore: implementazione efficiente | 37–38 | 38–39 |
| Esempio di esecuzione | 39 | 40 |
| Correttezza, analisi, grafo dei successori | 40–47 | 41–48 |
| Rilevamento di cicli negativi | 48–50 | 49–51 |
| Confronto Dijkstra vs Bellman-Ford-Moore | — | *(extra, non da slide)* |

Le pagine 5–6 (confusion matrix per l'inglese, matrice BLOSUM per le proteine) sono materiale di contesto sulle applicazioni: la nota le usa dentro «Motivazione e modello dei costi» per spiegare perché $\alpha_{pq}$ è una matrice e non un numero. Le pagine 1, 2, 13 e 27 sono divisori di sezione senza contenuto.
