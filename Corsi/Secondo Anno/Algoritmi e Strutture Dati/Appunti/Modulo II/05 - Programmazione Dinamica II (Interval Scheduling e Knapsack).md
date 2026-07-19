---
tags:
  - algoritmi
  - dp
slide: "5"
capitolo: "Kleinberg-Tardos cap. 6"
---
# Programmazione Dinamica II: Weighted Interval Scheduling, Segmented Least Squares, Knapsack e LIS
La programmazione dinamica consiste nello spezzare un problema in una serie di **sottoproblemi sovrapposti**, risolverli una volta sola e memorizzarne i risultati in una tabella per evitare il ricalcolo. Rispetto al greedy (confronto in [[01 - Greedy e Interval Scheduling]]) non impone scelte irrevocabili: esplora tutte le alternative possibili con costo polinomiale sfruttando la **sottostruttura ottima**. Questa nota copre quattro problemi classici — Weighted Interval Scheduling, Segmented Least Squares, Knapsack 0/1 e Longest Increasing Subsequence — più l'esercizio House Coloring. Per i fondamenti della tecnica si rimanda a [[04 - Programmazione Dinamica I (Weighted Independent Set)]].
## Schema generale della programmazione dinamica
Tutti i problemi di questa nota seguono lo stesso schema. Vale la pena impararlo come **procedura**, perché è esattamente ciò che l'Esercizio 3 dello scritto chiede di produrre: la traccia dice sempre «*progettate un algoritmo di programmazione dinamica che calcoli …*», e talvolta aggiunge «*si discuta la complessità temporale*».

> [!info] I sei punti di una risposta completa all'Es3
> 1. **Definizione dei sottoproblemi** — a parole e senza ambiguità: *«$\text{OPT}[\ldots]$ è il valore ottimo del problema ristretto a …»*. Vanno dichiarati anche **quanti** sono.
> 2. **Equazione di Bellman** — la ricorrenza, con i **casi base** espliciti.
> 3. **Giustificazione della ricorrenza** — si elencano i casi possibili per l'ultimo elemento, si mostra che sono **esaustivi**, e che in ciascuno il residuo è a sua volta un sottoproblema ottimo.
> 4. **Ordine di calcolo** — in che ordine si riempie la tabella, così che ogni cella trovi già pronte quelle da cui dipende.
> 5. **Dove si legge la risposta** — quale cella contiene il risultato (e, se richiesta, come si ricostruisce la soluzione e non solo il suo valore).
> 6. **Complessità** — tempo e spazio, giustificati come «numero di celle $\times$ costo per cella».

> [!warning] Dove si perdono davvero i punti
> Non nello pseudocodice: nel **punto 1**. Una definizione di sottoproblema sbagliata o vaga fa crollare tutto ciò che segue, mentre una definizione giusta con pseudocodice assente vale quasi tutto il punteggio. Se il tempo stringe, l'ordine di priorità è **sottoproblemi → ricorrenza → complessità → pseudocodice**.
> Lo pseudocodice conviene comunque scriverlo — una volta fissati i punti 1 e 2 è meccanico (due cicli annidati e la riga della ricorrenza), costa poco e toglie ogni ambiguità su *quale* algoritmo hai progettato.
> Attenzione infine a **cosa** calcola la tabella: quasi sempre un **valore numerico**, non l'insieme soluzione. Ricostruire la soluzione è un passo separato (punto 5) e va fatto solo se la traccia lo chiede.

> [!info] La domanda da farsi quando non si trova la ricorrenza
> *«Su quale singola decisione posso spezzare il problema, in modo che ciò che resta sia un'istanza più piccola dello stesso problema?»* Nel Weighted Interval Scheduling la decisione è «prendo il job $j$ oppure no»; nel Knapsack «metto l'oggetto $i$ nello zaino oppure no»; nel WIS su cammino «includo l'ultimo nodo oppure no» (vedi [[04 - Programmazione Dinamica I (Weighted Independent Set)#Il metodo: interrogare la soluzione ottima invece di costruirla|il metodo]]).
> Se la risposta richiede di ricordare **più di una** informazione — come nel Knapsack, dove serve sapere anche quanta capacità resta — allora i sottoproblemi hanno **due indici** invece di uno, e la tabella diventa bidimensionale. È il segnale che distingue $\text{OPT}[j]$ da $\text{OPT}[i][w]$.
## Weighted Interval Scheduling
### Il problema
**Input**: $n$ job; il job $j$ inizia in $s_j$, termina in $f_j$ e ha **peso** $w_j > 0$.
Due job sono **compatibili** se non si sovrappongono. L'obiettivo è trovare il sottoinsieme di peso totale massimo di job mutualmente compatibili.

> [!info] Confronto con la versione unweighted
> La versione con pesi unitari ($w_j = 1$ per ogni $j$) si risolve in modo ottimo con l'algoritmo greedy *earliest-finish-time first* (vedi [[01 - Greedy e Interval Scheduling]]). Con pesi arbitrari il greedy può fallire drasticamente: un singolo job di peso $999$ viene ignorato a favore di due job di peso $1$ ciascuno.

![[dp2_greedy_pesato_che_fallisce.png]]
*Il caso estremo: earliest-finish-time-first prende $a$ e $h$ perché finiscono presto, e totalizza $1 + 1 = 2$; il job $b$, che da solo vale **999**, viene scartato perché finisce tardi. Il criterio greedy guarda i tempi e ignora i pesi — ed è la ragione per cui qui serve la DP. (slide 8)*
### Struttura della soluzione ottima
**Convenzione**: i job sono ordinati in ordine crescente di finish time, $f_1 \le f_2 \le \cdots \le f_n$.

> [!quote] Definizione — Predecessore $p(j)$
> $p(j)$ è il più grande indice $i < j$ tale che il job $i$ è **compatibile** con il job $j$ (cioè $f_i \le s_j$). Se nessun job è compatibile con $j$, allora $p(j) = 0$.

**Istanza di riferimento** (usata in tutta la sezione). Sei job, già ordinati per tempo di fine:

| $j$ | $s_j$ | $f_j$ | $w_j$ | $p(j)$ |
|---|---|---|---|---|
| 1 | 0 | 3 | 2 | 0 |
| 2 | 1 | 4 | 4 | 0 |
| 3 | 0 | 5 | 4 | 0 |
| 4 | 3 | 6 | **7** | 1 |
| 5 | 4 | 7 | 2 | 2 |
| 6 | 3 | 9 | 1 | 1 |

Sull'asse dei tempi (il peso è tra parentesi):
```
    0   1   2   3   4   5   6   7   8   9   <- tempo
1   |===========|                               (2)
2       |===========|                           (4)
3   |===============|                           (4)
4               |===========|                   (7)
5                   |===========|               (2)
6               |===========================|   (1)
```
**Come si legge $p(j)$**: $p(4) = 1$ perché il job 4 inizia in $s_4 = 3$, e il job compatibile con indice più alto è il job 1 (finisce esattamente in $f_1 = 3 \le 3$); i job 2 e 3 finiscono dopo e si sovrappongono. $p(5) = 2$ perché $s_5 = 4$ e il job 2 finisce in $f_2 = 4$. $p(2) = 0$ perché nulla finisce entro $s_2 = 1$: nessun job è compatibile, e la ricorsione riparte da zero.

> [!warning] $p(j)$ non è $j-1$
> È l'errore più comune. $p(j)$ **non** è «il job precedente», è **l'ultimo job compatibile**: saltare da $j$ a $p(j)$ scarta in un colpo solo *tutti* i job incompatibili con $j$. Nel WIS su cammino il salto era sempre di due posizioni ($j \to j-2$) perché ogni nodo confligge solo col vicino; qui la lunghezza del salto dipende dall'istanza. È esattamente la stessa idea, generalizzata.

![[dp2_istanza_8jobs.png]]
*L'istanza a 8 job usata dal prof a lezione (la stessa che ricorre nei compiti d'esame). Verifica i tre valori sulla figura: $p(8) = 1$ perché il job 8 parte in 4 e solo il job 1 finisce entro quel punto; $p(7) = 3$ perché il job 7 parte in 6 e il job 3 finisce in 6; $p(2) = 0$ perché prima del job 2 non finisce nulla. (slide 9)*

> [!quote] Definizione — $\text{OPT}(j)$
> $\text{OPT}(j)$ è il peso massimo di qualunque sottoinsieme di job mutualmente compatibili scelto tra i job $1, 2, \ldots, j$.

**Caso 1 — job $j$ non selezionato**: la soluzione coincide con $\text{OPT}(j-1)$.

**Caso 2 — job $j$ selezionato**: si raccoglie $w_j$, si escludono i job incompatibili $\{p(j)+1, \ldots, j-1\}$, e si considera la soluzione ottima sui job compatibili rimasti $1, \ldots, p(j)$.

> [!quote] Equazione di Bellman — Weighted Interval Scheduling
> $$\text{OPT}(j) = \begin{cases} 0 & j = 0 \\ \max\bigl\{\text{OPT}(j-1),\; w_j + \text{OPT}(p(j))\bigr\} & j \ge 1 \end{cases}$$

La slide etichetta i due casi come *optimal substructure property (proof via exchange argument)* senza svolgere la dimostrazione: la si rende qui esplicita, perché è esattamente il «ponte» che l'Es3 richiede fra la struttura della soluzione e la ricorrenza.

> [!quote] Proprietà — Sottostruttura ottima del WIS
> Sia $O_j$ **una** soluzione ottima sul sottoproblema $\{1, \ldots, j\}$ (di peso $\text{OPT}(j)$). Allora:
> - se $j \notin O_j$, l'insieme $O_j$ è ottimo anche per $\{1, \ldots, j-1\}$;
> - se $j \in O_j$, l'insieme $O_j \setminus \{j\}$ è ottimo per $\{1, \ldots, p(j)\}$.

**Dimostrazione (argomento di scambio).** I due casi «$j \notin O_j$» e «$j \in O_j$» sono esaustivi e mutuamente esclusivi, quindi ogni soluzione ottima ricade in esattamente uno di essi.
- **Caso $j \notin O_j$.** Allora $O_j \subseteq \{1, \ldots, j-1\}$, ed è un insieme di job a due a due compatibili, dunque ammissibile per il sottoproblema $\{1, \ldots, j-1\}$. Se esistesse una soluzione ammissibile $S$ per $\{1, \ldots, j-1\}$ con $w(S) > w(O_j)$, allora $S$ sarebbe ammissibile anche per $\{1, \ldots, j\}$ (non contiene $j$) e batterebbe $O_j$: assurdo, perché $O_j$ è ottima su $\{1, \ldots, j\}$. Quindi $w(O_j) = \text{OPT}(j-1)$.
- **Caso $j \in O_j$.** Poiché i job di $O_j$ sono a due a due compatibili, nessuno degli indici $\{p(j)+1, \ldots, j-1\}$ può stare in $O_j$: per definizione di $p(j)$ ciascuno di essi si sovrappone a $j$. Dunque $O_j \setminus \{j\} \subseteq \{1, \ldots, p(j)\}$ ed è ammissibile per quel sottoproblema. Se esistesse $S \subseteq \{1, \ldots, p(j)\}$ compatibile con $w(S) > w(O_j \setminus \{j\})$, allora $S \cup \{j\}$ sarebbe ammissibile per $\{1, \ldots, j\}$ — ogni job di $S$ ha indice $\le p(j)$, quindi è compatibile con $j$ — e avrebbe peso $w(S) + w_j > w(O_j)$: assurdo. Quindi $w(O_j \setminus \{j\}) = \text{OPT}(p(j))$. $\square$

Dalla sottostruttura ottima discende la **correttezza della ricorrenza** per induzione.

**Dimostrazione (per induzione su $j$).** Sia $M[j]$ il valore prodotto dalla ricorrenza; si prova $M[j] = \text{OPT}(j)$.
- **Base** ($j = 0$): non c'è alcun job, l'unica soluzione ammissibile è $\emptyset$, quindi $\text{OPT}(0) = 0 = M[0]$.
- **Passo** ($j \ge 1$): per ipotesi induttiva $M[j-1] = \text{OPT}(j-1)$ e $M[p(j)] = \text{OPT}(p(j))$, poiché entrambi gli indici sono $< j$. Per la proprietà appena dimostrata ogni soluzione ottima vale $\text{OPT}(j-1)$ (Caso 1) oppure $w_j + \text{OPT}(p(j))$ (Caso 2); inoltre entrambe le quantità sono raggiungibili da una soluzione ammissibile, quindi il valore ottimo è il **massimo** dei due — esattamente ciò che calcola $M[j]$. $\square$

L'**ordine di riempimento** discende dalla ricorrenza: $M[j]$ dipende solo da celle di indice $< j$ (cioè $M[j-1]$ e $M[p(j)]$, con $p(j) < j$), quindi calcolando $M[0], M[1], \ldots, M[n]$ per $j$ **crescente** ogni cella trova già pronte quelle da cui dipende.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Bottom-Up($n, s, f, w$)}
\begin{algorithmic}
\State ordina i job per finish time: $f[1] \leq f[2] \leq \cdots \leq f[n]$
\State calcola $p[j]$ per ogni $j$ (ricerca binaria su $f[1..j-1]$)
\State $M[0] \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $M[j] \gets \max(M[j-1],\; w[j] + M[p[j]])$
\EndFor
\State \Return $M[n]$
\end{algorithmic}
\end{algorithm}
```

**Esecuzione passo-passo** sull'istanza di riferimento. Ad ogni riga si confronta «scarto il job $j$» con «prendo il job $j$ e salto a $p(j)$», e si tiene il massimo:

| $j$ | $w_j$ | $p(j)$ | scarto: $M[j-1]$ | prendo: $w_j + M[p(j)]$ | $M[j]$ |
|---|---|---|---|---|---|
| 1 | 2 | 0 | $0$ | $2 + M[0] = 2$ | **2** |
| 2 | 4 | 0 | $2$ | $4 + M[0] = 4$ | **4** |
| 3 | 4 | 0 | $4$ | $4 + M[0] = 4$ | **4** |
| 4 | 7 | 1 | $4$ | $7 + M[1] = 9$ | **9** |
| 5 | 2 | 2 | $9$ | $2 + M[2] = 6$ | **9** |
| 6 | 1 | 1 | $9$ | $1 + M[1] = 3$ | **9** |

Il valore ottimo è $M[6] = 9$, realizzato da $\{1, 4\}$: il job 1 $[0,3]$ e il job 4 $[3,6]$, di peso $2 + 7 = 9$.

Vale la pena leggere due righe di questa tabella per capire il meccanismo:
- alla riga $j = 4$ la scelta «prendo» vince ($9 > 4$): il job 4 pesa 7, e saltando a $p(4) = 1$ recupera anche il job 1. È qui che si costruisce l'ottimo;
- alla riga $j = 6$ la scelta «prendo» perde nettamente ($3 < 9$): il job 6 occupa da 3 a 9 e pesa solo 1, quindi prenderlo costringerebbe a buttare via il job 4. La colonna $M[j]$ resta a 9 e l'ottimo non cambia.

> [!info] Perché il greedy sui pesi fallisce qui
> Un greedy che prende sempre il job più pesante disponibile sceglierebbe il job 4 (peso 7) — e in questo caso ci azzecca. Ma basta alzare a 5 il peso dei job 2 e 5, che sono fra loro compatibili: il greedy prenderebbe ancora il job 4 fermandosi a 9, mentre $\{2, 5\}$ vale $10$. Nessun criterio locale sa quando conviene rinunciare a un job pesante per due leggeri che stanno insieme: serve confrontare *tutte* le alternative, ed è ciò che fa la riga $\max$ della ricorrenza.
### Algoritmo con memoization (top-down)
Il calcolo ricorsivo senza memoization ha $T(n) = T(n-1) + T(n-2) + O(1)$, che cresce come la sequenza di Fibonacci: **esponenziale**. La memoization elimina i ricalcoli.

```pseudo
\begin{algorithm}
\caption{Top-Down($n, s, f, w$)}
\begin{algorithmic}
\State ordina i job per finish time
\State calcola $p[j]$ per ogni $j$
\State $M[0] \gets 0$
\State \Return \Call{M-Compute-Opt}{$n$}
\end{algorithmic}
\end{algorithm}
```

```pseudo
\begin{algorithm}
\caption{M-Compute-Opt($j$)}
\begin{algorithmic}
\If{$M[j]$ è non inizializzato}
  \State $M[j] \gets \max\bigl(\text{M-Compute-Opt}(j-1),\; w[j] + \text{M-Compute-Opt}(p[j])\bigr)$
\EndIf
\State \Return $M[j]$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Lemma — Complessità della memoization
> L'algoritmo con memoization esegue **al più $2n$ chiamate ricorsive** e ha complessità $O(n \log n)$.

**Dimostrazione (argomento di potenziale).**
1. Si definisca $\Phi$ = numero di celle di $M[1..n]$ già inizializzate. All'inizio $\Phi = 0$, e in ogni momento $\Phi \leq n$ perché le celle sono $n$.
2. Le chiamate a `M-Compute-Opt` si dividono in due tipi:
	- *chiamata che trova la cella già inizializzata*: costa $O(1)$ e **non** genera chiamate figlie;
	- *chiamata che inizializza una nuova cella*: costa $O(1)$ di lavoro proprio, incrementa $\Phi$ di 1 e genera esattamente **2** chiamate figlie.
3. Le chiamate del secondo tipo sono al più $n$: ognuna incrementa $\Phi$ di 1, e $\Phi$ non può superare $n$. È qui che la memoization spezza la ricorsione esponenziale — senza tabella, nulla impedirebbe di reinizializzare la stessa cella.
4. Solo le chiamate del secondo tipo generano chiamate figlie (2 ciascuna); quelle del primo tipo non ne generano. Ogni chiamata, tranne quella iniziale $\texttt{M-Compute-Opt}(n)$, è figlia di una chiamata del secondo tipo, quindi il numero totale di chiamate generate è $\leq 2 \cdot (\text{chiamate del secondo tipo}) \leq 2n$.
5. In totale le chiamate a `M-Compute-Opt` sono $\leq 2n + 1 = O(n)$, ciascuna di costo proprio $O(1)$: il calcolo ricorsivo costa dunque $O(n)$.
6. Il costo dominante è quindi il **pre-processing**, non la ricorsione: ordinare i job per tempo di fine costa $O(n \log n)$, e calcolare i $p[j]$ per ricerca binaria costa $O(n \log n)$. Totale $O(n \log n)$. $\square$

> [!info] Il bottleneck è l'ordinamento, non la DP
> È un punto che vale la pena saper dire: la parte di programmazione dinamica è **lineare**, e i $O(n\log n)$ complessivi vengono interamente dal pre-processing. Se i job arrivassero già ordinati per tempo di fine e con i $p[j]$ noti, l'algoritmo sarebbe $\Theta(n)$ — esattamente come il WIS su cammino. La stessa osservazione ritorna nelle domande d'esame su Kruskal, dove il costo è dominato dall'ordinamento degli archi e non dalle operazioni Union-Find.
### Ricostruzione della soluzione
```pseudo
\begin{algorithm}
\caption{Find-Solution($j$)}
\begin{algorithmic}
\If{$j = 0$}
  \State \Return $\emptyset$
\ElsIf{$w[j] + M[p[j]] > M[j-1]$}
  \State \Return $\{j\} \cup \text{Find-Solution}(p[j])$
\Else
  \State \Return \Call{Find-Solution}{$j-1$}
\EndIf
\end{algorithmic}
\end{algorithm}
```

Complessità: $O(n)$ — al più $n$ chiamate ricorsive.
### Complessità
| Fase | Complessità |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Calcolo $p[j]$ per ogni $j$ (ricerca binaria) | $O(n \log n)$ |
| Riempimento tabella (bottom-up) | $O(n)$ |
| Ricostruzione | $O(n)$ |
| **Totale** | $O(n \log n)$ |

> [!info] Bottom-up vs memoization
> | Aspetto | Top-down (memoization) | Bottom-up (tabulazione) |
> |---|---|---|
> | Calcola solo i sottoproblemi necessari | Sì | No (tutti) |
> | Overhead chiamate ricorsive | Sì | No |
> | Indicizzazione dei sottoproblemi | Comoda anche con oggetti generici (es. insiemi) | Solo con interi |
> | Analisi complessità | Più delicata | Immediata |
> | Codice | Più intuitivo | Più compatto e cache-efficiente |

> [!question] Domanda tipica d'esame — Perché il greedy fallisce
> **D:** Perché l'algoritmo greedy *earliest-finish-time first* non funziona per il Weighted Interval Scheduling? Come si risolve correttamente?
> **R:**
> **Comportamento del greedy.** *Earliest-finish-time first* seleziona sempre il job che termina prima, **senza guardare il peso**: è lo stesso criterio ottimo per il problema non pesato (vedi [[01 - Greedy e Interval Scheduling]]), ma qui ignora l'informazione che conta di più.
>
> **Controesempio.** È l'istanza della slide 8 (gli stessi job $a$, $h$, $b$ della figura sopra): il job pesante $b = [0, 10]$ ha peso $999$; due job di peso $1$ coprono $a = [0, 3]$ e $h = [8, 11]$ e sono fra loro compatibili. Il greedy prende $a$ e $h$, perché finiscono prima, e totalizza $2$, scartando il job da $999$.
>
> **Causa.** Il criterio è **locale**: guarda solo i tempi di fine, mai il peso, quindi non può accorgersi che rinunciare a due job leggeri per uno pesante conviene. Nessuna regola greedy basata su un solo parametro (tempo, peso, densità) è ottima in generale per il WIS.
>
> **Soluzione corretta.** Si usa la programmazione dinamica, con equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ e caso base $\text{OPT}(0) = 0$: confrontando *entrambe* le alternative a ogni job si garantisce l'ottimo, in $O(n \log n)$ (dominato dall'ordinamento e dal calcolo di $p(j)$ con ricerca binaria).

> [!question] Domanda tipica d'esame — Riduzione a WIS
> **D:** *(Vero o Falso)* «Trasformando opportunamente l'istanza I, è possibile darla in input all'algoritmo di Programmazione Dinamica per il Weighted Interval Scheduling ed ottenere la soluzione ottima per I.» *(chiesto il 12/09/2023)*
> **R:**
> **Risposta.** Vero.
>
> **Perché.** La tecnica è la **riduzione**: si trasforma l'istanza $I$ in un'istanza equivalente di WIS (job con intervalli $[s_j, f_j]$ e pesi $w_j$) tale che la soluzione ottima calcolata dall'algoritmo PD di WIS sull'istanza trasformata corrisponda esattamente alla soluzione ottima di $I$.
>
> **Esempio.** L'Interval Scheduling **non pesato** (vedi il confronto a inizio sezione): ponendo $w_j = 1$ per ogni job, l'equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ diventa $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, 1 + \text{OPT}(p(j))\}$, che calcola la cardinalità massima di un sottoinsieme di job compatibili — esattamente l'ottimo del problema non pesato.
>
> **Osservazione.** In generale, per mostrare che un problema $P$ si risolve con l'algoritmo PD di WIS basta esibire una **trasformazione polinomiale** dell'istanza di $P$ in un'istanza di intervalli pesati che preservi il valore ottimo: è lo schema di riduzione che estende un algoritmo esistente a problemi apparentemente diversi.
## Segmented Least Squares
### Il problema
**Least Squares**: dati $n$ punti $(x_1, y_1), \ldots, (x_n, y_n)$ nel piano, trovare la retta $y = ax + b$ che minimizza la **somma degli scarti quadratici** (SSE):
$$\text{SSE} = \sum_{i=1}^{n} (y_i - ax_i - b)^2$$
La soluzione in forma chiusa si ricava dal calcolo, con complessità $O(n)$ per fissato insieme di punti.
**Segmented Least Squares**: i punti **non** sono approssimabili bene da un'unica retta, ma da una **sequenza di segmenti lineari**. Si vuole minimizzare:
$$f = E + c \cdot L$$
dove $E$ è la somma degli SSE di ciascun segmento, $L$ è il numero di rette usate, e $c > 0$ è una costante di penalità per la parsimonia.

> [!info] Bilanciamento accuratezza/parsimonia
> Il termine $c \cdot L$ penalizza le soluzioni con troppi segmenti. Con $c \to 0$ si usano $n$ segmenti con SSE $= 0$; con $c \to \infty$ si usa un unico segmento. Il valore di $c$ è scelto dall'utente in base al contesto.
### Struttura della soluzione ottima
**Notazione**: i punti sono ordinati per $x$, con $x_1 < x_2 < \cdots < x_n$. Indichiamo con $e_{ij}$ il SSE del migliore segmento che approssima i punti $p_i, p_{i+1}, \ldots, p_j$.

> [!quote] Definizione — $\text{OPT}(j)$
> $\text{OPT}(j)$ è il costo minimo per approssimare i punti $p_1, p_2, \ldots, p_j$ con una sequenza ottima di segmenti.

**Osservazione chiave**: l'**ultimo segmento** della soluzione ottima per i punti $1, \ldots, j$ copre necessariamente i punti $p_i, \ldots, p_j$ per qualche $1 \le i \le j$. Il suo costo è $e_{ij} + c$ (SSE più penalità per la retta). I punti $p_1, \ldots, p_{i-1}$ devono essere approssimati in modo ottimo con $\text{OPT}(i-1)$: se così non fosse, una segmentazione migliore di $p_1, \ldots, p_{i-1}$ — combinata con lo stesso ultimo segmento — darebbe una soluzione complessiva di costo minore, contraddicendo l'ottimalità di quella di partenza (argomento di scambio). Poiché l'inizio $i$ dell'ultimo segmento non è noto a priori, la ricorrenza prova **tutti** i possibili $i$ e ne tiene il minimo; il caso base è $\text{OPT}(0) = 0$ (nessun punto, costo nullo).

> [!quote] Equazione di Bellman — Segmented Least Squares
> $$\text{OPT}(j) = \begin{cases} 0 & j = 0 \\ \displaystyle\min_{1 \le i \le j}\bigl\{e_{ij} + c + \text{OPT}(i-1)\bigr\} & j \ge 1 \end{cases}$$

La **scelta multipla** (multiway choice) distingue questo problema da Weighted Interval Scheduling, dove la scelta era binaria.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Segmented-Least-Squares($n, p_1, \ldots, p_n, c$)}
\begin{algorithmic}
\For{$j \gets 1$ \To $n$}
  \For{$i \gets 1$ \To $j$}
    \State calcola $e[i][j]$ = SSE per i punti $p_i, \ldots, p_j$
  \EndFor
\EndFor
\State $M[0] \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $M[j] \gets \min_{1 \leq i \leq j} \{ e[i][j] + c + M[i-1] \}$
\EndFor
\State \Return $M[n]$
\end{algorithmic}
\end{algorithm}
```

> [!warning] Pre-calcolo degli SSE con somme cumulative
> Il calcolo naïf di tutti gli $e_{ij}$ richiede $O(n)$ per coppia $\Rightarrow O(n^3)$ in totale. Si può pre-calcolare le **somme cumulative** $\Sigma x$, $\Sigma y$, $\Sigma x^2$, $\Sigma xy$ in $O(n)$, e poi ogni $e_{ij}$ si ottiene in $O(1)$, riducendo il totale a $O(n^2)$.
### Ricostruzione della soluzione
La ricostruzione risale la tabella $M$: partendo da $j = n$, si trova l'indice $i^*$ che minimizza $\{e_{ij} + c + M[i-1]\}$, si emette il segmento $[i^*, j]$, e si ricorre su $j \leftarrow i^* - 1$ fino a $j = 0$.
### Complessità
| Fase | Complessità |
|---|---|
| Pre-calcolo $e_{ij}$ (naïf) | $O(n^3)$ |
| Pre-calcolo $e_{ij}$ (somme cumulative) | $O(n^2)$ |
| Riempimento tabella $M$ | $O(n^2)$ |
| Spazio (tabella $e_{ij}$) | $O(n^2)$ |
| **Totale (versione ottimizzata)** | $O(n^2)$ tempo, $O(n^2)$ spazio |

> [!quote] Teorema — Complessità Segmented Least Squares (Bellman 1961)
> L'algoritmo DP risolve il problema Segmented Least Squares in $O(n^3)$ tempo e $O(n^2)$ spazio (versione base), o in $O(n^2)$ tempo con pre-calcolo delle somme cumulative.

> [!question] Domanda tipica d'esame — Scelta binaria vs multipla
> **D:** Qual è la differenza strutturale tra l'equazione di Bellman per il Weighted Interval Scheduling e quella per il Segmented Least Squares?
> **R:**
> **WIS — scelta binaria.** Si include o si esclude il job $j$: un'unica alternativa per ciascuno dei due casi, quindi il $\max$ della ricorrenza confronta solo **due** valori, $\text{OPT}(j-1)$ e $w_j + \text{OPT}(p(j))$.
>
> **SLS — scelta multipla.** L'ultimo segmento può coprire qualunque prefisso finale $[i, j]$ con $1 \le i \le j$: il $\min$ della ricorrenza confronta fino a $j$ alternative, una per ogni possibile inizio $i$ dell'ultimo segmento.
>
> **Conseguenza sulla complessità.** Entrambe sfruttano la sottostruttura ottima (il sottoproblema residuo è a sua volta ottimo), ma il ciclo interno necessario per esaminare le $j$ alternative di SLS porta il riempimento della tabella a $O(n^2)$ invece del $O(n)$ di WIS, dove ogni cella si calcola in $O(1)$ noto $p(j)$.
## Knapsack 0/1
### Il problema
**Input**: $n$ oggetti; l'oggetto $i$ ha **valore** $v_i > 0$ e **peso** $w_i > 0$ (interi). Uno zaino ha capacità $W$ (intero). **Obiettivo**: selezionare un sottoinsieme di oggetti di valore totale massimo senza superare il peso $W$.
**Assunzione**: i **pesi** $w_i$ e la capacità $W$ sono **interi positivi** — vincolo necessario per indicizzare la tabella DP. I valori $v_i$ sono anch'essi interi nell'istanza standard, ma come chiarito nella sezione sulla complessità, l'algoritmo rimane corretto anche con valori reali.

> [!warning] False start: un'unica variabile non basta
> La definizione $\text{OPT}(i)$ = valore ottimo usando i primi $i$ oggetti non è sufficiente. Quando si decide se includere l'oggetto $i$, non si sa la capacità residua disponibile: senza questa informazione non si può costruire la ricorrenza. **Serve una seconda variabile**.
### Struttura della soluzione ottima
> [!quote] Definizione — $\text{OPT}(i, w)$
> $\text{OPT}(i, w)$ è il valore massimo selezionabile dai primi $i$ oggetti con capacità residua $w$.

**Caso 1 — oggetto $i$ non selezionato** (o $w_i > w$): $\text{OPT}(i, w) = \text{OPT}(i-1, w)$.

**Caso 2 — oggetto $i$ selezionato**: si raccoglie $v_i$, la capacità scende a $w - w_i$, e si risolve ottimamente il sottoproblema sui primi $i-1$ oggetti con capacità $w - w_i$.

> [!quote] Equazione di Bellman — Knapsack 0/1
> $$\text{OPT}(i, w) = \begin{cases} 0 & i = 0 \\ \text{OPT}(i-1, w) & w_i > w \\ \max\bigl\{\text{OPT}(i-1, w),\; v_i + \text{OPT}(i-1, w - w_i)\bigr\} & w_i \le w \end{cases}$$

Anche qui la slide indica *optimal substructure property (proof via exchange argument)* senza svolgerlo. La sottostruttura si prova con lo stesso schema del WIS.

**Dimostrazione (argomento di scambio).** Sia $O$ una soluzione ottima per $(i, w)$ — un sottoinsieme di $\{1, \ldots, i\}$ di peso $\le w$ e valore massimo. Se $i \notin O$, allora $O \subseteq \{1, \ldots, i-1\}$ è ammissibile per $(i-1, w)$ ed è ottima lì: una soluzione migliore per $(i-1, w)$ lo sarebbe anche per $(i, w)$, assurdo. Se $i \in O$ (che richiede $w_i \le w$), allora $O \setminus \{i\} \subseteq \{1, \ldots, i-1\}$ ha peso $\le w - w_i$ ed è ottima per $(i-1, w - w_i)$: se esistesse $S$ migliore per $(i-1, w-w_i)$, l'insieme $S \cup \{i\}$ avrebbe peso $\le w$ e valore $> $ quello di $O$, assurdo. I due casi sono esaustivi, quindi $\text{OPT}(i,w)$ è il massimo dei due valori (e coincide col solo Caso 1 quando $w_i > w$, perché allora $i$ non può entrare). $\square$

Il **caso base** è $\text{OPT}(0, w) = 0$ per ogni $w$ (nessun oggetto ⇒ valore nullo, qualunque sia la capacità). L'**ordine di riempimento** segue la ricorrenza: ogni cella $(i, w)$ dipende solo dalla **riga precedente** $i-1$ (nelle colonne $w$ e $w - w_i \le w$), quindi si riempie la tabella per $i$ crescente da $0$ a $n$, e per ciascuna riga si scorre $w$ da $0$ a $W$.

> [!question] Domanda tipica d'esame — Significato di OPT(j-1, w-wj)
> **D:** «B) Prefissato un qualsiasi ordinamento degli items {Ij : j= 1,...,n}, la funzione OPT(j-1,w-wj) calcolata da PD è uguale al valore ottimo relativo alla sottoistanza \<I1,...,Ij-1; w- wj \> ? Se SI, in che modo viene utilizzato questo valore nell'algoritmo PD? Se NO, quale/i valore/i della funzione OPT(j,w) vengono utilizzati da PD al generico passo ricorsivo?» *(chiesto il 14/09/2022)*
> **R:**
> **Risposta.** Sì.
>
> **Perché.** Per definizione $\text{OPT}(j,w)$ è il valore ottimo della sottoistanza formata dai primi $j$ item con capacità $w$ (vedi la definizione data in questa sezione); sostituendo $j \to j-1$ e $w \to w-w_j$, $\text{OPT}(j-1, w-w_j)$ è — sempre per definizione — il valore ottimo della sottoistanza $\langle I_1,\ldots,I_{j-1}; w-w_j \rangle$.
>
> **Uso nell'algoritmo.** Questo valore compare nel passo ricorsivo dell'equazione di Bellman $\text{OPT}(j,w) = \max\{\text{OPT}(j-1,w),\, v_j + \text{OPT}(j-1, w-w_j)\}$, e corrisponde al **Caso 2**: il ramo in cui l'item $I_j$ **viene incluso** nella soluzione ottima, per cui si somma $v_j$ al valore ottimo ottenibile dai primi $j-1$ item con la capacità residua $w-w_j$ rimasta dopo aver "pagato" il peso $w_j$.
>
> **Condizione.** Il termine è valido solo se $w_j \le w$; altrimenti l'item non entra e $\text{OPT}(j,w) = \text{OPT}(j-1,w)$.

> [!question] Domanda tipica d'esame — Cosa rappresenta M(j,w)
> **D:** «C) Nella versione iterativa dell'algoritmo PD, l'entrata della matrice M(j,w) contiene la soluzione ottima formata da un qualsiasi sottoinsieme S di {I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) } tale che: |S| <= j e Σ_(k∉S) vk = w ?» *(chiesto il 14/09/2022)*
> **R:**
> **Risposta.** No.
>
> **Errore 1 — l'insieme di partenza.** $M(j,w)$ è definita sui **primi $j$ item** $\{I_1,\ldots,I_j\}$, non su un sottoinsieme $S$ qualunque estratto da **tutta** la lista $\{I_1,\ldots,I_n\}$ con $|S|\le j$: un sottoinsieme di $j$ item presi da posizioni arbitrarie (es. $\{I_2, I_7\}$ con $j=5$) non è ammissibile per $M(j,w)$, che considera solo $S \subseteq \{I_1,\ldots,I_j\}$.
>
> **Errore 2 — il vincolo di capacità.** La formulazione è sbagliata: deve valere $\sum_{k \in S} w_k \le w$ (il **peso totale degli item selezionati** non supera la capacità residua $w$), non $\sum_{k \notin S} v_k = w$ (somma dei *valori* degli item *esclusi*, priva di significato per il problema).
>
> **Definizione corretta.** Coerente con quella data in questa nota:
> $$M(j,w) = \max\Bigl\{\sum_{k\in S} v_k \;:\; S \subseteq \{I_1,\ldots,I_j\},\; \sum_{k \in S} w_k \le w\Bigr\}$$
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{Knapsack($n, W, w_1, \ldots, w_n, v_1, \ldots, v_n$)}
\begin{algorithmic}
\For{$w \gets 0$ \To $W$}
  \State $M[0][w] \gets 0$
\EndFor
\For{$i \gets 1$ \To $n$}
  \For{$w \gets 0$ \To $W$}
    \If{$w_i > w$}
      \State $M[i][w] \gets M[i-1][w]$
    \Else
      \State $M[i][w] \gets \max(M[i-1][w],\; v_i + M[i-1][w - w_i])$
    \EndIf
  \EndFor
\EndFor
\State \Return $M[n][W]$
\end{algorithmic}
\end{algorithm}
```
### Tabella di esempio
Con gli oggetti $\{(v_1=1,w_1=1),\,(v_2=6,w_2=2),\,(v_3=18,w_3=5),\,(v_4=22,w_4=6),\,(v_5=28,w_5=7)\}$ e $W = 11$. Due sottoinsiemi illustrativi (slide 43): $\{1, 2, 5\}$ ha valore $35$ e peso $10$; $\{3, 4\}$ ha valore $40$ e peso $11$ — quest'ultimo, come mostra la tabella, è l'ottimo.

```
        w:   0   1   2   3   4   5   6   7   8   9  10  11
  {}         0   0   0   0   0   0   0   0   0   0   0   0
  {1}        0   1   1   1   1   1   1   1   1   1   1   1
  {1,2}      0   1   6   7   7   7   7   7   7   7   7   7
  {1,2,3}    0   1   6   7   7  18  19  24  25  25  25  25
  {1,2,3,4}  0   1   6   7   7  18  22  24  28  29  29  40
  {1,..5}    0   1   6   7   7  18  22  28  29  34  35  40
```

La soluzione ottima è $\text{OPT}(5, 11) = 40$ (sottoinsieme $\{3, 4\}$, peso $5+6=11$, valore $18+22=40$).

![[dp2_knapsack_problem.png]]
*La stessa tabella dalle slide. Tienila accanto quando ti alleni a riempirla a mano: l'errore tipico non è la formula ma la **colonna** da cui si pesca, cioè $w - w_i$ invece di $w$. Esempio da verificare sulla figura: la cella $(\{1,2,3,4\},\ 11) = 40$ nasce da $v_4 + \text{OPT}(3,\ 11-6) = 22 + \text{OPT}(3,5) = 22 + 18$, non da $\text{OPT}(3,11) = 25$. (slide 47)*
### Ricostruzione della soluzione
Si risale la tabella dall'angolo in basso a destra: l'oggetto $i$ **è incluso** nella soluzione ottima per $(i, w)$ se e solo se $M[i][w] > M[i-1][w]$ (cioè la selezione ha effettivamente aumentato il valore). In caso affermativo si ricorre su $(i-1, w - w_i)$, altrimenti su $(i-1, w)$.
### Complessità e pseudo-polinomialità
> [!quote] Teorema — Complessità Knapsack
> L'algoritmo DP risolve Knapsack 0/1 in $\Theta(nW)$ tempo e $\Theta(nW)$ spazio.

**Perché la complessità è pseudo-polinomiale?**

> [!warning] Knapsack è pseudo-polinomiale, non polinomiale
> $\Theta(nW)$ **non è** polinomiale nella **dimensione dell'input**. La dimensione dell'input è $O(n \log W + n \log v_{\max})$ bit (si codificano i numeri in binario). Il valore $W$ può essere esponenziale nel numero di bit che lo rappresentano: se $W = 2^k$, allora $k = \log_2 W$ bit bastano per rappresentarlo, ma l'algoritmo esegue $\Theta(n \cdot 2^k)$ operazioni — esponenziale in $k$.
>
> Un **algoritmo pseudo-polinomiale** ha complessità polinomiale nei *valori* (non nella *dimensione in bit*) dell'input. È efficiente quando $W$ è ragionevolmente piccolo, ma non garantisce costi polinomiali in generale.
>
> **Nota**: l'integrità dei pesi è essenziale. Con pesi reali arbitrari la tabella non è indicizzabile e l'approccio DP non funziona direttamente. L'integrità dei valori invece **non** è necessaria per la correttezza.

> [!question] Domanda tipica d'esame — Perché due variabili
> **D:** Perché per il Knapsack 0/1 è necessario definire il sottoproblema con due variabili $\text{OPT}(i, w)$ invece di una sola $\text{OPT}(i)$?
> **R:**
> **Il problema con una sola variabile.** Con $\text{OPT}(i)$ = valore ottimo usando i primi $i$ oggetti, si fissa il prefisso ma non la **capacità residua**: quando si decide se aggiungere l'oggetto $i$, non si sa quanto spazio è ancora disponibile nello zaino, e senza questa informazione non si può scrivere una ricorrenza corretta.
>
> **La seconda variabile.** $w$ rappresenta esattamente la **capacità residua**: fissando sia il prefisso $i$ sia la capacità $w$ disponibile, il sottoproblema $\text{OPT}(i,w)$ è ben definito e ammette una ricorrenza.
>
> **Ricorrenza.** Se $w_i > w$ l'oggetto non entra e $\text{OPT}(i,w) = \text{OPT}(i-1,w)$; altrimenti si massimizza tra escluderlo (costo $\text{OPT}(i-1,w)$) e includerlo (costo $v_i + \text{OPT}(i-1, w-w_i)$).
>
> **Caso base.** $\text{OPT}(0,w) = 0$ per ogni $w$: senza oggetti disponibili il valore selezionabile è nullo, qualunque sia la capacità.

> [!question] Domanda tipica d'esame — Pseudo-polinomialità
> **D:** L'algoritmo DP per il Knapsack è polinomiale?
> **R:**
> **Risposta.** No.
>
> **Perché.** La complessità $\Theta(nW)$ è **pseudo-polinomiale**: è polinomiale nei *valori* dell'input, non nella sua *dimensione in bit*. Se $W$ è rappresentato con $k$ bit allora $W = O(2^k)$, e l'algoritmo esegue $\Theta(n \cdot 2^k)$ operazioni — esponenziale in $k$, cioè nella dimensione reale dell'input.
>
> **Osservazione.** Knapsack è un problema **NP-hard** (vedi [[09 - NP-Completezza e Riduzioni]]) e non si conosce alcun algoritmo polinomiale nella dimensione dell'input: l'esistenza della DP pseudo-polinomiale non contraddice questo fatto, perché "pseudo-polinomiale" e "polinomiale" sono nozioni diverse (vedi la domanda successiva).

> [!question] Domanda tipica d'esame — K è in P?
> **D:** «ESERCIZIO 1. Si consideri il problema Knapsack (K) e si consideri l'algoritmo ottimale PD per K basato sulla Programmazione Dinamica. Si consideri una generica istanza X = \<I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) ; W\> di K, dove M = max{wj, vj, W : j=1,...,n}. Si risponda alle seguenti domande con al massimo quattro righe negli spazi appropriati, dando delle brevi spiegazioni. A) L'esistenza di un qualsiasi algoritmo che impiega tempo Θ(n^2 log^24(M)) mostrerebbe che il problema K è nella classe P?» *(chiesto il 14/09/2022)*
> **R:**
> **Risposta.** Sì.
>
> **Perché.** $\Theta(n^2 \log^{24} M)$ è polinomiale nella **dimensione dell'input**, che è $O(n \log M)$ bit (peso, valore e capacità sono codificati in binario, quindi ciascuno occupa $O(\log M)$ bit). Un tempo $\Theta(n^2 \log^{24} M)$ è polinomiale sia in $n$ sia in $\log M$, cioè nella lunghezza della codifica dell'istanza: un tale algoritmo classificherebbe $K$ in P.
>
> **Confronto con la DP standard.** L'algoritmo PD di questa nota ha complessità $\Theta(nW)$: è polinomiale nel *valore* $W$ (quindi in $M$), non nella sua *dimensione in bit* $\log W$ — è **pseudo-polinomiale**, non polinomiale (vedi il riquadro sulla pseudo-polinomialità qui sopra).
>
> **Distinzione.** È esattamente quella tra $\text{poly}(M)$ (pseudo-polinomiale, come $\Theta(nW)$) e $\text{poly}(\log M)$ (polinomiale in senso proprio, come l'ipotetico $\Theta(n^2 \log^{24} M)$).
>
> ⏱️ **Se la traccia dà 4 righe**: rispondi Sì e giustifica in una riga che $\Theta(n^2\log^{24}M)$ è polinomiale in $n$ e $\log M$ — cioè nella dimensione in bit dell'istanza, $O(n\log M)$ — quindi metterebbe $K$ in P (1-2 righe); chiudi con il confronto secco «a differenza della PD standard, che è $\Theta(nW)$ e quindi solo pseudo-polinomiale» (1-2 righe). **Non va mai omessa** la distinzione fra dimensione in bit dell'istanza e valore numerico dei dati: è il concetto su cui verte l'intera domanda.
## Longest Increasing Subsequence (LIS)
### Il problema
**Input**: una sequenza $S[1], S[2], \ldots, S[n]$ di $n$ numeri reali. **Obiettivo**: trovare la **sottosequenza crescente più lunga** (LIS), cioè una sequenza di indici $i_1 < i_2 < \cdots < i_k$ tale che $S[i_1] < S[i_2] < \cdots < S[i_k]$, con $k$ massimo.

> [!example] Esempio motivante (dalle slide)
> Sequenza: $S = [4, 1, 8, 3, 4, 8, 2, 7, 5, 6, 9, 8]$
>
> La lunghezza della LIS ottima è $6$. Un esempio di LIS di lunghezza 6: $1, 3, 4, 5, 6, 9$ (indici $2, 4, 5, 9, 10, 11$).
### Primo tentativo fallito
Se si definisce $\text{OPT}[i]$ = lunghezza della LIS di $S[1], \ldots, S[i]$, non si riesce a scrivere una ricorrenza semplice: non si sa con quale valore termina la LIS di $S[1..i]$, e quindi non si può decidere se $S[i+1]$ può essere aggiunto.

> [!info] Tecnica: aggiungere un vincolo al sottoproblema
> Una soluzione classica consiste nel **restringere** la definizione del sottoproblema, aggiungendo il vincolo che la sottosequenza **termini obbligatoriamente con $S[i]$**. Questo abilita la ricorrenza.
### Struttura della soluzione ottima
> [!quote] Definizione — $\text{OPT}[i]$
> $\text{OPT}[i]$ è la lunghezza della sottosequenza crescente più lunga di $S[1], \ldots, S[i]$ **che termina con $S[i]$**.

**Soluzione**: $\max_{i = 1, \ldots, n} \text{OPT}[i]$ (il massimo su tutti i possibili ultimi elementi).

> [!quote] Equazione di Bellman — LIS
> $$\text{OPT}[i] = 1 + \max\Bigl(0,\; \max_{\substack{j = 1, \ldots, i-1 \\ S[j] < S[i]}} \text{OPT}[j]\Bigr)$$

**Lettura**: la LIS che termina in $S[i]$ è l'estensione della migliore LIS che termina in qualche $S[j] < S[i]$ con $j < i$. Se non esiste tale $j$, la LIS è di lunghezza $1$ (solo $S[i]$).
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{LIS($S[1..n]$)}
\begin{algorithmic}
\State $\text{OPT}[1] \gets 1$
\For{$i \gets 2$ \To $n$}
  \State $\text{OPT}[i] \gets 1 + \max\!\Bigl(0,\; \max_{\substack{j=1,\ldots,i-1 \\ S[j] < S[i]}} \text{OPT}[j]\Bigr)$
\EndFor
\State \Return $\max_{i=1,\ldots,n} \text{OPT}[i]$
\end{algorithmic}
\end{algorithm}
```
### Esempio di calcolo
Sequenza: $S = [4, 1, 8, 3, 4, 8, 2, 7, 5, 6, 9, 8]$, indici da $1$ a $12$.

```
i    :  1   2   3   4   5   6   7   8   9  10  11  12
S[i] :  4   1   8   3   4   8   2   7   5   6   9   8
OPT  :  1   1   2   2   3   4   2   4   4   5   6   6
```

La LIS ha lunghezza $\max = 6$, raggiunta sia in $i = 11$ (elemento $9$) sia in $i = 12$ (elemento $8$). Una LIS ottima è $1, 3, 4, 5, 6, 9$ (indici $2, 4, 5, 9, 10, 11$).
### Ricostruzione della soluzione
Per ricostruire la LIS, si mantiene un array `prev[i]` che memorizza l'indice $j$ usato nella ricorrenza per $\text{OPT}[i]$ (il predecessore nella LIS che finisce in $i$). A partire dall'indice $i^*$ con $\text{OPT}[i^*]$ massimo, si risale la catena dei predecessori.
### Complessità
| Fase | Complessità |
|---|---|
| Calcolo $\text{OPT}[i]$ per ogni $i$ (ciclo interno $O(i)$) | $O(n^2)$ |
| Ricerca del massimo | $O(n)$ |
| **Totale** | $O(n^2)$ |

**Spazio**: $O(n)$ per l'array $\text{OPT}$ (e $O(n)$ per `prev` in caso di ricostruzione).

> [!info] Esiste un algoritmo $O(n \log n)$ per LIS
> Con una struttura dati ausiliaria (patience sorting o albero di ricerca) è possibile risolvere LIS in $O(n \log n)$, ma l'approccio DP $O(n^2)$ è quello trattato in questo corso.

> [!question] Domanda tipica d'esame — Vincolo sull'ultimo elemento
> **D:** Perché per LIS è necessario aggiungere il vincolo che la sottosequenza termini con $S[i]$? Come cambia la ricorrenza?
> **R:**
> **Il problema senza vincolo.** Definendo $\text{OPT}[i]$ = lunghezza della LIS di $S[1..i]$ senza altri vincoli, non si sa con quale valore termina la LIS ottima di $S[1..i]$: non è quindi possibile decidere se $S[i+1]$ può prolungarla, e la ricorrenza non si scrive (è il tentativo fallito discusso in questa sezione).
>
> **Il vincolo che sblocca la ricorrenza.** Restringendo la definizione a «la LIS di $S[1..i]$ che **termina obbligatoriamente con $S[i]$**», il valore finale della sottosequenza è fissato per costruzione, e diventa possibile confrontarlo con $S[i]$ per ogni $i$ successivo.
>
> **Ricorrenza.**
> $$\text{OPT}[i] = 1 + \max\Bigl(0,\; \max_{\substack{j<i \\ S[j]<S[i]}} \text{OPT}[j]\Bigr)$$
> con caso base $\text{OPT}[1] = 1$ (una sequenza di un solo elemento è sempre crescente).
>
> **Soluzione globale.** Il vincolo fissa dove finisce *una* sottosequenza, non dove finisce l'intera LIS: bisogna quindi prendere il massimo su tutti i possibili ultimi elementi, $\max_{i=1,\ldots,n} \text{OPT}[i]$.
## House Coloring (esercizio)
### Il problema
**Input**: $n$ case in fila, ognuna va dipinta di rosso (R), verde (G) o blu (B). Il costo di dipingere la casa $i$ del colore $c$ è $\text{cost}(i, c)$. **Vincolo**: nessuna casa adiacente ha lo stesso colore. **Obiettivo**: minimizzare il costo totale.
### Struttura della soluzione ottima
> [!quote] Definizione — $R[i]$, $G[i]$, $B[i]$
> - $R[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **rossa**.
> - $G[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **verde**.
> - $B[i]$ = costo minimo per dipingere le case $1, \ldots, i$ con la casa $i$ **blu**.

La soluzione ottima è $\min\{R[n], G[n], B[n]\}$.

> [!quote] Equazione di Bellman — House Coloring
> $$R[i] = \text{cost}(i, \text{rosso}) + \min\{G[i-1],\, B[i-1]\}$$
> $$G[i] = \text{cost}(i, \text{verde}) + \min\{R[i-1],\, B[i-1]\}$$
> $$B[i] = \text{cost}(i, \text{blu}) + \min\{R[i-1],\, G[i-1]\}$$
> Casi base: $R[1] = \text{cost}(1, R)$, $G[1] = \text{cost}(1, G)$, $B[1] = \text{cost}(1, B)$.
### Algoritmo bottom-up
```pseudo
\begin{algorithm}
\caption{House-Coloring($n, \text{cost}$)}
\begin{algorithmic}
\State $R[1] \gets \text{cost}(1, R)$
\State $G[1] \gets \text{cost}(1, G)$
\State $B[1] \gets \text{cost}(1, B)$
\For{$i \gets 2$ \To $n$}
  \State $R[i] \gets \text{cost}(i, R) + \min(G[i-1],\; B[i-1])$
  \State $G[i] \gets \text{cost}(i, G) + \min(R[i-1],\; B[i-1])$
  \State $B[i] \gets \text{cost}(i, B) + \min(R[i-1],\; G[i-1])$
\EndFor
\State \Return $\min(R[n],\; G[n],\; B[n])$
\end{algorithmic}
\end{algorithm}
```

**Complessità**: $O(n)$ — un'unica passata con $O(1)$ lavoro per ogni casa.
### Esempio di calcolo
Sull'istanza della slide 33 — sei case $A, \ldots, F$, con la matrice dei costi $\text{cost}(i, c)$:
```
         A    B    C    D    E    F
 rosso   7    6    7    8    9   20
 verde   3    8    9   22   12    8
 blu    16   10    4    2    5    7
```
Riempiendo le tre righe da sinistra a destra con la ricorrenza (caso base = costi della casa $A$):
```
 i       A    B    C    D    E    F
 R[i]    7    9   20   21   29   46
 G[i]    3   15   18   35   32   34
 B[i]   16   13   13   20   26   36
```
Il costo minimo è $\min\{R[6], G[6], B[6]\} = \min\{46, 34, 36\} = 34$, realizzato risalendo le scelte a ritroso dalla cella $G[6]$: la colorazione $A$ verde, $B$ rosso, $C$ blu, $D$ rosso, $E$ blu, $F$ verde, di costo $3+6+4+8+5+8 = 34$ (e senza due case adiacenti dello stesso colore).

> [!info] Generalizzazione a $k$ colori
> Con $k$ colori la stessa struttura si generalizza a $k$ array, con equazione $C_i[c] = \text{cost}(i, c) + \min_{c' \ne c} C_{i-1}[c']$. Pre-calcolando i due minimi globali della riga precedente in $O(k)$, ogni cella costa $O(1)$ e la complessità è $\Theta(nk)$ — che è già ottima, perché i costi in input sono $nk$ e vanno comunque letti tutti.

> [!question] Domanda tipica d'esame — Generalizzazione a k colori
> **D:** Qual è la complessità dell'algoritmo DP per House Coloring con 3 colori? Come si generalizza a $k$ colori?
> **R:**
> **Caso a 3 colori.** Complessità $O(n)$: si scorrono le $n$ case, e per ogni casa si calcolano i 3 valori $R[i], G[i], B[i]$, ciascuno in tempo $O(1)$ (il minimo fra due valori già calcolati).
>
> **Generalizzazione naïve a $k$ colori.** Si mantengono $k$ array; per ogni casa serve il minimo tra i $k-1$ colori alternativi al colore corrente. Calcolarlo da zero per ogni cella costa $O(k)$, per un totale di $O(nk^2)$.
>
> **Ottimizzazione.** Si pre-calcolano i **due** valori minimi della riga precedente in $O(k)$ per riga (il secondo minimo serve per il caso in cui il minimo assoluto cada proprio sul colore $c$ escluso). Con questi due valori ogni cella si calcola in $O(1)$, quindi $O(k)$ per riga e $\Theta(nk)$ in totale su $n$ righe.
>
> **Complessità e lower bound.** $\Theta(nk)$ **non è migliorabile**: l'input contiene $nk$ costi $\text{cost}(i,c)$ e un algoritmo corretto deve leggerli tutti, perché cambiare anche un solo costo può cambiare l'ottimo. Quindi $\Omega(nk)$ è un lower bound, e la DP ottimizzata è **asintoticamente ottima**.
## Riepilogo dei problemi trattati
| Problema | Sottoproblemi | Scelta | Equazione di Bellman | Complessità |
|---|---|---|---|---|
| Weighted Interval Scheduling | $O(n)$ | Binaria (includo/escludo job $j$) | $\max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ | $O(n \log n)$ |
| Segmented Least Squares | $O(n)$ | Multipla (quale ultimo segmento) | $\min_{i \le j}\{e_{ij} + c + \text{OPT}(i-1)\}$ | $O(n^2)$ |
| Knapsack 0/1 | $O(nW)$ | Binaria (includo/escludo oggetto $i$) | $\max\{\text{OPT}(i-1,w),\, v_i + \text{OPT}(i-1,w-w_i)\}$ | $\Theta(nW)$ pseudo-pol. |
| LIS | $O(n)$ | Multipla (quale predecessore $j$) | $1 + \max_{j<i,\,S[j]<S[i]} \text{OPT}[j]$ | $O(n^2)$ |
| House Coloring | $O(n)$ | Multipla (3 colori) | $\text{cost}(i,c) + \min_{c' \ne c} C[i-1][c']$ | $O(n)$ |

Per i problemi di sequenza alignment e Bellman-Ford, che usano la stessa tecnica DP con una seconda variabile, si veda [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].
## Riconoscere il sottoproblema in un problema mai visto
All'Esercizio 3 il problema è **sempre nuovo** — una «storiella» inventata per l'occasione. Non si può averlo già studiato: si può però riconoscere a quale **pattern** appartiene. I problemi di questa nota e della successiva coprono cinque schemi, e quasi ogni traccia ricade in uno di essi.

| Pattern | Segnale nella traccia | Forma della tabella | Esempio visto |
|---|---|---|---|
| **Scelta binaria su sequenza** | oggetti in fila, ognuno «si prende o no», e prenderne uno esclude i vicini | $\text{OPT}[j]$, un indice | WIS, Weighted Interval Scheduling |
| **Scelta binaria con risorsa** | c'è un **budget**, una capacità, un tempo totale da non superare | $\text{OPT}[i][w]$, il 2° indice è la risorsa residua | Knapsack 0/1 |
| **Due sequenze da confrontare** | l'input sono **due** stringhe/sequenze da allineare o far corrispondere | $\text{OPT}[i][j]$, un indice per sequenza | Sequence Alignment |
| **Vincolo «deve terminare qui»** | il primo tentativo non chiude perché servirebbe sapere *con che cosa finisce* la soluzione parziale | $\text{OPT}[i]$ ridefinito con vincolo | LIS |
| **Stato che ci si porta dietro** | una condizione locale con **poche configurazioni**: un colore, un'energia, quanti consecutivi ho preso | $\text{OPT}[i][\text{stato}]$ | House Coloring |

> [!warning] Il segnale più importante: quando un indice non basta
> Se scrivendo la ricorrenza ti accorgi che **non sai rispondere** con la sola informazione «ho considerato i primi $i$ elementi», allora manca un indice. La domanda diagnostica è: *«per decidere sull'elemento $i$, cosa avrei bisogno di sapere sul passato che $\text{OPT}[i-1]$ non mi dice?»*
> - «quanta capacità mi resta» $\Rightarrow$ secondo indice = capacità residua (Knapsack);
> - «di che colore ho dipinto la casa precedente» $\Rightarrow$ secondo indice = colore (House Coloring);
> - «quanti nodi contigui ho già preso» $\Rightarrow$ secondo indice = lunghezza del blocco corrente.
>
> Quest'ultimo caso è precisamente l'Es3 del **30/06/2026** (*minimum dominating set with discounts*), dove lo sconto del 10% si applica ai nodi che stanno in un blocco contiguo lungo almeno 3: per saperlo bisogna ricordare **quanti consecutivi** si sono presi finora, e questo diventa il secondo indice della tabella.

> [!info] Se la tabella cresce troppo
> Il numero di sottoproblemi deve restare **polinomiale**. Se il secondo indice può assumere un numero esponenziale di valori — per esempio «quale sottoinsieme ho già scelto» — la definizione è sbagliata e va ripensata: quasi sempre esiste un riassunto più compatto dello stato (un contatore, un colore, una capacità) che basta per decidere. Il Knapsack è al limite: $\Theta(nW)$ è polinomiale nel *valore* $W$ ma **non** nella sua dimensione in bit, ed è per questo che si dice pseudo-polinomiale.
