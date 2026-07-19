---
tags:
  - algoritmi
  - dp
slide: "6"
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
> La **distanza di edit** tra $X$ e $Y$ è il costo minimo di un allineamento tra le due stringhe.

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
| Tempo | $\Theta(mn)$ — $mn$ celle, ciascuna in $O(1)$ |
| Spazio | $\Theta(mn)$ — intera matrice $M$ |
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
*Le frecce sono il traceback sulla stessa matrice: si parte dal 3 cerchiato in basso a destra e si risale fino a $(0,0)$. Ogni **diagonale** accoppia due caratteri (`P`-`P`, `A`-`A`, `L`-`L`, `T`-`T`, `E`-`E`), ogni freccia **verticale** è un gap. Il cammino tocca una verticale sola — la `E` di `PALETTE` senza corrispondenza — più il mismatch `T`/`A`: costo $2 + 1 = 3$. (slide numerata «12», pagina 11 del PDF)*

> [!question] Domanda tipica d'esame — Complessità Sequence Alignment
> **D:** Qual è la complessità del Sequence Alignment e da dove deriva il vincolo sullo spazio?
> **R:**
> **Tempo.** $\Theta(mn)$: si calcolano $mn$ sotto-problemi (le celle di $\text{OPT}(i,j)$), ciascuno in $O(1)$ perché dipende da al più tre celle già calcolate.
>
> **Spazio.** $\Theta(mn)$: si mantiene l'intera matrice $M$, non solo l'ultima riga o colonna.
>
> **Perché il vincolo.** Il traceback deve ripercorrere le scelte vincenti dall'angolo $(m,n)$ fino a $(0,0)$, quindi servono tutte le celle già calcolate — non basta l'ultima riga/colonna.
>
> **Alternativa.** Se serve solo il valore della distanza, senza l'allineamento esplicito, bastano due colonne (o righe) adiacenti alla volta, riducendo lo spazio a $O(m+n)$: è esattamente l'osservazione da cui parte poi l'algoritmo di Hirschberg per recuperare anche il traceback in spazio lineare.
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

Sia $f(i,j)$ la lunghezza del cammino minimo da $(0,0)$ a $(i,j)$ e $g(i,j)$ quella da $(i,j)$ a $(m,n)$ (calcolata invertendo gli archi e i ruoli dei due estremi). Si ha:
- $f(i,j) = \text{OPT}(i,j)$ per tutti $i,j$ (dim. per induzione forte su $i+j$);
- **(Osservazione 1)** la lunghezza del cammino minimo che passa per $(i,j)$ è $f(i,j) + g(i,j)$;
- $f(\cdot, j)$ e $g(\cdot, j)$ si calcolano ognuna in tempo $O(mn)$ e spazio $O(m+n)$.

> [!quote] Proprietà — Osservazione 2 (Hirschberg)
> Sia $q^*$ l'indice che minimizza $f(q,\, n/2) + g(q,\, n/2)$ su tutti $q \in \{0,\ldots,m\}$. Allora esiste un cammino minimo da $(0,0)$ a $(m,n)$ che passa per $(q^*, n/2)$: questo nodo appartiene all'allineamento ottimo.

**Divide.** Si fissa la colonna centrale $n/2$. Si calcolano $f(q,\, n/2)$ e $g(q,\, n/2)$ per tutti $q$; si trova $q^*$ che minimizza la somma. Il nodo $(q^*, n/2)$ fa parte della soluzione.

**Conquer.** Si richiama ricorsivamente l'algoritmo su $(x_1\ldots x_{q^*},\; y_1\ldots y_{n/2})$ e su $(x_{q^*+1}\ldots x_m,\; y_{n/2+1}\ldots y_n)$.

```text
       (0,0) ─────── colonna n/2 ──────── (m,n)
                          │
                     (q*,n/2)  ← nodo dell'allineamento ottimo
                        /    \
            ricorsione sx    ricorsione dx
```

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

> [!question] Domanda tipica d'esame — Idea e complessità di Hirschberg
> **D:** Qual è l'idea alla base dell'algoritmo di Hirschberg per il sequence alignment, e quali sono tempo e spazio risultanti rispetto alla DP standard?
> **R:**
> **Idea.** Il valore $\text{OPT}(i,j)$ si può calcolare mantenendo solo due colonne della matrice (quella corrente e la precedente), in spazio $O(m+n)$ — ma così si perde la possibilità di fare il traceback. Hirschberg recupera l'allineamento sfruttando il grafo di edit: si calcola $f(i,j)$ (cammino minimo da $(0,0)$ a $(i,j)$, che coincide con $\text{OPT}(i,j)$) e $g(i,j)$ (cammino minimo da $(i,j)$ a $(m,n)$), ciascuno in tempo $O(mn)$ e spazio $O(m+n)$.
>
> **Divide.** Sulla colonna centrale $n/2$ si trova l'indice $q^*$ che minimizza $f(q,n/2)+g(q,n/2)$: per l'Osservazione 2, il nodo $(q^*,n/2)$ appartiene a un cammino minimo, quindi fa parte di un allineamento ottimo.
>
> **Conquer.** Si applica ricorsivamente lo stesso procedimento ai due sotto-problemi $(x_1\ldots x_{q^*}, y_1\ldots y_{n/2})$ e $(x_{q^*+1}\ldots x_m, y_{n/2+1}\ldots y_n)$, dimezzando ogni volta l'intervallo di colonne.
>
> **Complessità.** Tempo: $T(m,n) \leq T(q^*,n/2)+T(m-q^*,n/2)+O(mn)$, che per induzione forte su $m+n$ dà $T(m,n) \leq 2cmn = O(mn)$ — stesso ordine della DP standard. Spazio: $\Theta(m+n)$, perché ogni chiamata ricorsiva usa $\Theta(m)$ spazio per calcolare $f(\cdot,n/2)$ e $g(\cdot,n/2)$, e il numero di chiamate ricorsive attive è limitato.
>
> **Confronto.** Rispetto alla DP standard ($\Theta(mn)$ tempo e spazio), Hirschberg mantiene lo stesso ordine di tempo ma riduce lo spazio da quadratico a lineare — il vantaggio è puramente sullo spazio.
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
*I due tentativi falliti, come li presenta il prof. **In alto** il grafo originale: la nota a lato («Dijkstra selects the vertices in the order $s, t, w, v$») è la chiave di lettura — $t$ viene chiuso per primo, a 2, e non verrà più aggiornato. **In basso** lo stesso grafo con $+8$ su ogni arco: il cammino minimo passa da $s\to v\to w\to t$ a $s \to t$, cioè il reweighting ha cambiato la risposta. Attenzione a copiare i pesi esattamente da qui: invertire $s\to t$ e $s\to v$ distrugge il controesempio, perché Dijkstra tornerebbe a dare il risultato corretto. (slide numerata «30», pagina 29 del PDF)*

> [!question] Domanda tipica d'esame — Perché Dijkstra fallisce con pesi negativi
> **D:** Perché l'algoritmo di Dijkstra non funziona in presenza di archi con peso negativo, e perché non basta sommare una costante positiva a tutti i pesi per aggirare il problema?
> **R:**
> **Causa del fallimento.** Dijkstra è greedy: ad ogni passo estrae il nodo con distanza stimata minima e la fissa come definitiva, assumendo implicitamente che nessun cammino scoperto in seguito possa essere più corto. Questa assunzione vale solo se tutti i pesi sono non negativi, perché solo allora estendere un cammino con un arco in più non può mai diminuirne la lunghezza.
>
> **Controesempio.** Con pesi negativi l'assunzione cade: un arco negativo scoperto più tardi può abbreviare un cammino che termina in un nodo già "chiuso". Nell'esempio sopra Dijkstra fissa subito $t$ a 2 tramite l'arco diretto $s \to t$, e solo dopo scopre $s \to v \to w \to t$ di lunghezza $6 + (-8) + 3 = 1$: la risposta corretta è 1, ma $t$ è ormai chiuso e l'algoritmo restituisce 2.
>
> **Perché il reweighting ingenuo non basta.** Sommare una costante $c>0$ a ogni peso non preserva l'ordine dei cammini per lunghezza, perché la penalità totale su un cammino è proporzionale al numero di archi che contiene: un cammino con $k$ archi vede il proprio costo aumentare di $kc$. Un cammino con più archi — magari proprio quello reso minimo dai pesi negativi — viene quindi penalizzato più di un cammino con meno archi ma costo originario maggiore, alterando quale cammino risulta minimo.
### Cicli negativi
> [!quote] Definizione — Ciclo negativo
> Un **ciclo negativo** è un ciclo diretto $W = v_1 \to v_2 \to \ldots \to v_k \to v_1$ per cui
> $$\ell(W) = \sum_{e \in W} \ell_e < 0$$

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

**Dimostrazione (per assurdo).** Se non ci fosse nessun ciclo negativo, la passata $n$ non cambierebbe nulla (le distanze sono già ottime dopo $n-1$ passate, per il Teorema 2). Se invece esiste un ciclo negativo $W = v_1 \to \ldots \to v_k \to v_1$, si assuma per assurdo che il test $d[v] > d[w] + \ell_{vw}$ della passata aggiuntiva sia sempre falso. Allora $d[v_i] \leq d[v_{i+1}] + \ell(v_i, v_{i+1})$ per ogni $i$ (indici ciclici, $v_{k+1} = v_1$). Sommando lungo $W$ e semplificando i $d[\cdot]$ si ottiene $\ell(W) \geq 0$, che contraddice $\ell(W) < 0$. $\square$

> [!question] Domanda tipica d'esame — Rilevamento cicli negativi
> **D:** Come rileva Bellman-Ford-Moore un ciclo negativo?
> **R:**
> **Idea.** Dopo le $n-1$ passate normali — sufficienti a calcolare le distanze ottime in assenza di cicli negativi, perché per il Lemma 2 esiste sempre un cammino minimo semplice con al più $n-1$ archi — si esegue una passata aggiuntiva $n$-esima.
>
> **Criterio.** Se in questa passata esiste ancora un arco $(v,w)$ con $d[v] > d[w] + \ell_{vw}$, significa che $d[v]$ potrebbe ancora diminuire, cioè esiste un cammino che beneficia di più di $n-1$ archi — possibile solo in presenza di un ciclo negativo raggiungibile da $t$.
>
> **Perché funziona.** Se non ci fossero cicli negativi, la passata $n$ non cambierebbe nulla, perché le distanze sono già ottime dopo $n-1$ passate. Se invece esiste un ciclo negativo $W = v_1 \to \ldots \to v_k \to v_1$ e, per assurdo, nessun arco soddisfacesse la condizione, varrebbe $d[v_i] \leq d[v_{i+1}] + \ell(v_i,v_{i+1})$ per ogni $i$ (indici ciclici); sommando lungo $W$ si otterrebbe $\ell(W) \geq 0$, contraddizione.
>
> **Complessità.** La passata aggiuntiva esamina ogni arco una volta, quindi costa $O(m)$ — lo stesso ordine di una singola passata normale — e non cambia la complessità asintotica $O(mn)$ dell'algoritmo.
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

> [!info] Nota sull'esempio
> Il grafo non ha cicli negativi: gli unici cicli diretti sono $B \to D \to B$ (peso $1 + 2 = 3$) e $D \to E \to B \to D$ (peso $-3 + 2 + 1 = 0$), entrambi $\geq 0$; il problema è quindi ben posto. Eseguendo Bellman-Ford-Moore con l'ordine di visita $t, D, C, B, E$, dopo poche passate nessun $d[\cdot]$ cambia più e l'algoritmo termina **prima** delle $n-1$ iterazioni (terminazione anticipata): è la conferma pratica che Bellman-Ford-Moore è spesso molto più veloce del worst-case $O(mn)$.
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
