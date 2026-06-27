# Flussi di Rete (Max-Flow e Min-Cut)
I **flussi di rete** modellano situazioni in cui un materiale — dati, merci, traffico — deve essere trasportato da una sorgente a un pozzo attraverso una rete con capacità limitate. Il problema del **massimo flusso** (Max-Flow) e quello del **minimo taglio** (Min-Cut) sono due facce della stessa medaglia: il celebre teorema Max-Flow Min-Cut garantisce che il valore ottimale coincide. Questa nota studia la struttura del problema, l'algoritmo di Ford-Fulkerson con grafo residuo, la dimostrazione del teorema e due strategie per scegliere cammini aumentanti efficienti (shortest augmenting path / Edmonds-Karp e capacity scaling). Il collegamento con [[08 - Grafi e Visite]] è diretto: la BFS è al cuore dell'algoritmo di Edmonds-Karp; vedi anche [[10 - Cammini Minimi e Dijkstra]] per il contesto sui cammini minimi pesati.
## Rete di flusso
> [!quote] Definizione — Rete di flusso
> Una **rete di flusso** è una tupla $G = (V, E, s, t, c)$ dove:
> - $(V, E)$ è un **grafo orientato** (diretto);
> - $s \in V$ è la **sorgente** (*source*);
> - $t \in V$ è il **pozzo** (*sink*);
> - $c: E \to \mathbb{R}_{\geq 0}$ è la **funzione di capacità**, con $c(e) \geq 0$ per ogni arco $e \in E$.
>
> Si assume che tutti i nodi siano raggiungibili da $s$.

L'intuizione è quella di una rete di trasporto: il materiale parte da $s$, scorre lungo gli archi nel rispetto delle loro capacità, e arriva a $t$.
## Flusso e problema del massimo flusso
> [!quote] Definizione — Flusso st
> Un **flusso st** (*st-flow*) è una funzione $f: E \to \mathbb{R}$ che soddisfa:
> 1. **Vincolo di capacità**: $\forall e \in E,\quad 0 \leq f(e) \leq c(e)$
> 2. **Conservazione del flusso**: $\forall v \in V \setminus \{s, t\},\quad \displaystyle\sum_{e \text{ entra in } v} f(e) = \sum_{e \text{ esce da } v} f(e)$
>
> Il **valore del flusso** è:
> $$\operatorname{val}(f) = \sum_{e \text{ esce da } s} f(e) \;-\; \sum_{e \text{ entra in } s} f(e)$$

Il valore misura la quantità netta di materiale che lascia la sorgente (e arriva al pozzo, per conservazione).
> [!quote] Definizione — Problema del massimo flusso (Max-Flow)
> Dato $G = (V, E, s, t, c)$, trovare un flusso $f^*$ di **valore massimo**.

```
Esempio — rete semplice con flusso f (notazione flusso/capacità)

         3/5          3/4
    s --------> u --------> t
    |                       ^
    | 2/3          2/2      |
    +--------> v -----------+

  Capacità: s->u=5, s->v=3, u->t=4, v->t=2
  Flusso:   f(s,u)=3, f(s,v)=2, f(u,t)=3, f(v,t)=2
  val(f) = f(s,u) + f(s,v) = 3 + 2 = 5
  Conservazione nodo u: entra 3 (da s), esce 3 (verso t) ✓
  Conservazione nodo v: entra 2 (da s), esce 2 (verso t) ✓
```
Nell'esempio, $\operatorname{val}(f) = 5$: dalla sorgente $s$ escono 5 unità che raggiungono il pozzo $t$ attraverso due percorsi distinti, rispettando la conservazione del flusso in ogni nodo intermedio.
## Taglio e problema del minimo taglio
> [!quote] Definizione — Taglio st (st-cut)
> Un **taglio st** è una partizione $(A, B)$ dei nodi tale che $s \in A$ e $t \in B$.
>
> La **capacità del taglio** è la somma delle capacità degli archi che vanno **da $A$ a $B$** (non da $B$ ad $A$):
> $$\operatorname{cap}(A, B) = \sum_{\substack{e = (u,v) \\ u \in A,\ v \in B}} c(e)$$

> [!quote] Definizione — Problema del minimo taglio (Min-Cut)
> Dato $G = (V, E, s, t, c)$, trovare un taglio $(A^*, B^*)$ di **capacità minima**.

> [!example] Taglio — esempio
> Consideriamo una rete con $s$ collegato a $t$ tramite tre archi uscenti da $s$ di capacità 10, 5, 15. Se $A = \{s\}$ e $B = V \setminus \{s\}$, la capacità del taglio è $10 + 5 + 15 = 30$. Un altro taglio con capacità inferiore può escludere alcuni archi di capacità elevata includendo nodi intermedi in $A$.
## Verso l'algoritmo: l'approccio greedy fallisce
Un approccio greedy naturale è: partire da $f(e) = 0$, trovare un cammino $s \leadsto t$ con capacità residua positiva su ogni arco, aumentare il flusso lungo quel cammino, ripetere. Questo approccio **non è corretto**.
> [!warning] Perché il greedy fallisce
> Una volta che il greedy aumenta il flusso su un arco, non lo diminuisce mai. Considerare la rete:
>
> ```
>           2          2
>    s ----------> v -------> t
>    |             |
>    | 2           | 1
>    |             v
>    +-------> w -------> t
>           2       2
> ```
>
> Il **flusso massimo** $f^*$ ha $f^*(v, w) = 0$ e vale 4 (2 unità su $s \to v \to t$ e 2 su $s \to w \to t$). Il **greedy** potrebbe scegliere per primo il cammino $s \to v \to w \to t$ (bottleneck 1), saturando l'arco $(v, w)$ di capacità 1. Dopo questo passo, nessun cammino aumentante porta più di 1 unità sui percorsi rimasti, e il greedy si blocca a un valore sub-ottimale.
>
> **Conclusione**: serve un meccanismo di *undo* per le decisioni sbagliate.
## Grafo residuo
Il **grafo residuo** è la struttura che permette di "annullare" flusso già inviato, fornendo il meccanismo di correzione necessario.
> [!quote] Definizione — Grafo residuo
> Dato $G = (V, E, s, t, c)$ e un flusso $f$, il **grafo residuo** $G_f = (V, E_f, s, t, c_f)$ è definito come segue.
>
> Per ogni arco $e = (u, v) \in E$:
> - Se $f(e) < c(e)$: l'arco **diretto** $e = (u,v)$ esiste in $E_f$ con **capacità residua** $c_f(e) = c(e) - f(e)$ (posso inviare ancora $c(e) - f(e)$ unità).
> - Se $f(e) > 0$: l'arco **inverso** $e^{\text{rev}} = (v, u)$ esiste in $E_f$ con capacità residua $c_f(e^{\text{rev}}) = f(e)$ (posso annullare fino a $f(e)$ unità di flusso).
>
> In formule compatte:
> $$E_f = \{e \in E : f(e) < c(e)\} \;\cup\; \{e^{\text{rev}} : f(e) > 0\}$$

> [!info] Proprietà chiave del grafo residuo
> $f'$ è un flusso valido in $G_f$ se e solo se $f + f'$ è un flusso valido in $G$.
>
> Questo significa che ogni cammino aumentante in $G_f$ corrisponde a un miglioramento di $f$ in $G$.

```
Esempio — arco originale e arco residuo

  Rete G:          u --[6/17]--> v

  Rete residua Gf: u <---6---- v
                   u ---11---> v

  (arco diretto: 17-6=11 di capacità residua; arco inverso: 6 per l'undo)
```
## Cammino aumentante
> [!quote] Definizione — Cammino aumentante
> Un **cammino aumentante** rispetto al flusso $f$ è un cammino semplice $s \leadsto t$ nel grafo residuo $G_f$.
>
> La **capacità di collo di bottiglia** (*bottleneck*) del cammino $P$ è:
> $$\operatorname{bottleneck}(G_f, P) = \min_{e \in P} c_f(e)$$

**Procedura AUGMENT.** Dato un cammino aumentante $P$ con bottleneck $\delta$:

```pseudo
\begin{algorithm}
\caption{Augment($f, c, P$)}
\begin{algorithmic}
\State $\delta \gets \operatorname{bottleneck}(G_f, P)$
\ForAll{arco $e \in P$}
  \If{$e \in E$} \Comment{arco diretto}
    \State $f(e) \gets f(e) + \delta$
  \Else \Comment{arco inverso $e^{\text{rev}}$}
    \State $f(e^{\text{rev}}) \gets f(e^{\text{rev}}) - \delta$
  \EndIf
\EndFor
\State \Return $f$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Proprietà — Aumento del flusso
> Sia $f$ un flusso e $P$ un cammino aumentante in $G_f$. Dopo l'esecuzione di $\operatorname{AUGMENT}(f, c, P)$, il risultante $f'$ è un flusso valido in $G$ e:
> $$\operatorname{val}(f') = \operatorname{val}(f) + \operatorname{bottleneck}(G_f, P)$$
## Algoritmo di Ford-Fulkerson
L'algoritmo di **Ford-Fulkerson** (1955) risolve il problema Max-Flow iterando la ricerca di cammini aumentanti nel grafo residuo.

```pseudo
\begin{algorithm}
\caption{Ford-Fulkerson($G$)}
\begin{algorithmic}
\ForAll{arco $e \in E$}
  \State $f(e) \gets 0$
\EndFor
\State $G_f \gets$ grafo residuo di $G$ rispetto a $f$
\While{esiste un cammino $s \leadsto t$ $P$ in $G_f$}
  \State $f \gets$ \Call{Augment}{$f, c, P$}
  \State aggiorna $G_f$
\EndWhile
\State \Return $f$
\end{algorithmic}
\end{algorithm}
```

> [!info] Invariante di integralità
> Se tutte le capacità $c(e)$ sono **interi**, allora durante tutta l'esecuzione di Ford-Fulkerson ogni flusso $f(e)$ e ogni capacità residua $c_f(e)$ rimangono **interi** (per induzione sul numero di aumenti).

> [!example] Traccia di esecuzione — rete piccola
> Rete con nodi $s, u, v, t$ e archi:
> ```
>       s ---[0/2]---> u ---[0/6]---> t
>       |                              ^
>       +----[0/10]----> v ---[0/9]---+
> ```
> 1. Primo aumento: cammino $s \to v \to t$ con bottleneck 9; flusso diventa 9.
> 2. Secondo aumento: cammino $s \to u \to t$ con bottleneck 2; flusso diventa 11.
> 3. Nessun altro cammino in $G_f$: algoritmo termina con $\operatorname{val}(f) = 11$.
### Terminazione e complessità con capacità intere
> [!quote] Teorema — Terminazione di Ford-Fulkerson (capacità intere)
> Se tutte le capacità sono **interi** compresi tra $1$ e $C$, Ford-Fulkerson termina dopo al più $\operatorname{val}(f^*) \leq nC$ aumenti. Ogni aumento costa $O(m)$ (per trovare un cammino con BFS o DFS in [[08 - Grafi e Visite]]).
>
> **Complessità totale**: $O(m \cdot \operatorname{val}(f^*)) = O(m n C)$
>
> Questa complessità è **pseudo-polinomiale**: dipende dai valori delle capacità (non solo da $m$ e $n$). La BFS o DFS per trovare un cammino in $G_f$ costa $O(m)$; vedi [[08 - Grafi e Visite]] e [[09 - Applicazioni della DFS]].

> [!warning] Caso patologico — esponenziale
> Con scelta arbitraria del cammino, Ford-Fulkerson può richiedere un numero esponenziale di iterazioni. Considera la rete:
> ```
>       s ---[C]---> v
>       |    [1]     |
>       |    v<->w   |
>       +---[C]---> w ---[C]---> t
> ```
> Se l'algoritmo alterna i cammini $s \to v \to w \to t$ e $s \to w \to v \to t$, ogni aumento porta solo $\delta = 1$; ci vogliono $2C$ iterazioni totali. Con $C = 2^{30}$, il numero di passi è astronomico.
>
> **Patologia con capacità irrazionali**: se le capacità sono numeri irrazionali, Ford-Fulkerson potrebbe non terminare mai né convergere al massimo flusso.
## Relazione tra flussi e tagli
### Lemma del valore del flusso
> [!quote] Lemma — Valore del flusso su un taglio
> Sia $f$ un flusso qualsiasi e $(A, B)$ un taglio st qualsiasi. Allora:
> $$\operatorname{val}(f) = \sum_{\substack{e \text{ esce da } A}} f(e) \;-\; \sum_{\substack{e \text{ entra in } A}} f(e)$$

**Dimostrazione.** Poiché $\operatorname{val}(f) = \sum_{e \text{ esce da } s} f(e) - \sum_{e \text{ entra in } s} f(e)$, si estende la somma a tutti i nodi di $A$:
$$\operatorname{val}(f) = \sum_{v \in A} \Bigl(\sum_{e \text{ esce da } v} f(e) - \sum_{e \text{ entra in } v} f(e)\Bigr)$$
Per la conservazione del flusso, ogni termine con $v \neq s$ vale 0. Gli archi interni ad $A$ si cancellano. Rimangono solo gli archi tra $A$ e $B$. $\square$
### Dualità debole
> [!quote] Proprietà — Dualità debole
> Per qualsiasi flusso $f$ e qualsiasi taglio $(A, B)$:
> $$\operatorname{val}(f) \leq \operatorname{cap}(A, B)$$

**Dimostrazione.**
$$\operatorname{val}(f) = \sum_{e \text{ esce da } A} f(e) - \sum_{e \text{ entra in } A} f(e) \leq \sum_{e \text{ esce da } A} f(e) \leq \sum_{e \text{ esce da } A} c(e) = \operatorname{cap}(A, B) \qquad \square$$

La dualità debole dice che il valore di qualsiasi flusso è limitato superiormente dalla capacità di qualsiasi taglio: un taglio costituisce un **certificato di ottimalità superiore** per il flusso.
> [!quote] Lemma — Corollario (certificato di ottimalità)
> Sia $f$ un flusso e $(A, B)$ un taglio. Se $\operatorname{val}(f) = \operatorname{cap}(A, B)$, allora $f$ è un **flusso massimo** e $(A, B)$ è un **taglio minimo**.

**Dimostrazione.** Per la dualità debole:
- Per ogni flusso $f'$: $\operatorname{val}(f') \leq \operatorname{cap}(A, B) = \operatorname{val}(f)$, quindi $f$ è massimo.
- Per ogni taglio $(A', B')$: $\operatorname{cap}(A', B') \geq \operatorname{val}(f) = \operatorname{cap}(A, B)$, quindi $(A, B)$ è minimo. $\square$
## Teorema Max-Flow Min-Cut
> [!quote] Teorema — Max-Flow Min-Cut
> In una rete di flusso, il valore del **massimo flusso** è uguale alla capacità del **minimo taglio**:
> $$\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A, B)$$

> [!quote] Teorema — Cammini aumentanti (Augmenting Path Theorem)
> Un flusso $f$ è un flusso massimo **se e solo se** non esiste alcun cammino aumentante in $G_f$.

**Dimostrazione.** Si dimostra che le seguenti tre condizioni sono equivalenti per qualsiasi flusso $f$:
1. Esiste un taglio $(A, B)$ tale che $\operatorname{cap}(A, B) = \operatorname{val}(f)$.
2. $f$ è un flusso massimo.
3. Non esistono cammini aumentanti rispetto a $f$ in $G_f$.

**$[1 \Rightarrow 2]$** Per il corollario della dualità debole, se $\operatorname{val}(f) = \operatorname{cap}(A,B)$ allora $f$ è massimo.

**$[2 \Rightarrow 3]$** Dimostriamo la contronominale $\neg 3 \Rightarrow \neg 2$. Se esiste un cammino aumentante $P$ in $G_f$, allora $\operatorname{AUGMENT}(f, c, P)$ produce un flusso di valore strettamente maggiore, quindi $f$ non era massimo.

**$[3 \Rightarrow 1]$** Sia $f$ un flusso senza cammini aumentanti. Definiamo $A$ come l'insieme dei nodi raggiungibili da $s$ in $G_f$:
- $s \in A$ per definizione; $t \notin A$ perché non ci sono cammini aumentanti.
- Ogni arco $e = (u, v)$ con $u \in A, v \in B$: se $f(e) < c(e)$, allora $e$ esisterebbe in $G_f$ e $v$ sarebbe raggiungibile da $s$, contraddicendo $v \in B$. Quindi $f(e) = c(e)$ (arco **saturo**).
- Ogni arco $e = (v, u)$ con $v \in B, u \in A$: se $f(e) > 0$, allora l'arco inverso $e^{\text{rev}}$ esisterebbe in $G_f$ e $v$ sarebbe raggiungibile da $s$, contraddicendo $v \in B$. Quindi $f(e) = 0$.

Per il lemma del valore:
$$\operatorname{val}(f) = \sum_{e \text{ esce da } A} f(e) - \sum_{e \text{ entra in } A} f(e) = \sum_{e \text{ esce da } A} c(e) - 0 = \operatorname{cap}(A, B) \qquad \square$$

> [!info] Come calcolare il taglio minimo da un flusso massimo
> Dato un flusso massimo $f^*$, il taglio minimo si ottiene in $O(m)$: basta calcolare tutti i nodi raggiungibili da $s$ in $G_{f^*}$ (con una BFS/DFS come in [[08 - Grafi e Visite]]) — questo insieme forma $A$, e $B = V \setminus A$.

> [!quote] Teorema — Integralità del flusso massimo
> Se tutte le capacità sono **interi**, esiste sempre un flusso massimo **intero** $f^*$, con $f^*(e) \in \mathbb{Z}$ per ogni $e \in E$.
>
> **Dimostrazione**: Ford-Fulkerson termina (per capacità intere), e l'invariante di integralità garantisce che il flusso finale è intero. $\square$
## Scelta dei cammini aumentanti
La scelta del cammino aumentante determina l'efficienza pratica dell'algoritmo.
### Algoritmo di Edmonds-Karp (cammino più corto)
L'algoritmo di **Edmonds-Karp** (1970, indipendentemente da Dinitz) sceglie sempre il cammino aumentante con il **minor numero di archi**, trovato tramite BFS nel grafo residuo (vedi [[08 - Grafi e Visite]]).

```pseudo
\begin{algorithm}
\caption{ShortestAugmentingPath($G$) — Edmonds-Karp}
\begin{algorithmic}
\ForAll{arco $e \in E$}
  \State $f(e) \gets 0$
\EndFor
\State $G_f \gets$ grafo residuo di $G$ rispetto a $f$
\While{esiste un cammino $s \leadsto t$ in $G_f$}
  \State $P \gets$ \Call{BFS}{$G_f, s, t$} \Comment{cammino con meno archi}
  \State $f \gets$ \Call{Augment}{$f, c, P$}
  \State aggiorna $G_f$
\EndWhile
\State \Return $f$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema — Complessità di Edmonds-Karp
> Il numero totale di aumenti è al più $O(mn)$. L'algoritmo esegue in tempo $O(m^2 n)$.
>
> La chiave è che la distanza BFS da $s$ a $t$ in $G_f$ è **monotona non decrescente** nel corso delle iterazioni, il che limita il numero totale di aumenti.

> [!info] Perché la BFS è la scelta giusta
> Scegliere cammini corti riduce la "confusione" nel grafo residuo: gli archi si saturano in ordine di livello BFS e ogni arco può essere critico (bottleneck) al massimo $O(n)$ volte prima che la sua distanza da $s$ aumenti.
### Capacity Scaling (cammino con bottleneck grande)
La strategia **capacity scaling** (Edmonds-Karp, 1972; versione migliorata Gabow, 1985) preferisce cammini con **grande bottleneck**, evitando tanti piccoli aumenti.

L'algoritmo mantiene un parametro di scala $\Delta$ e lavora solo sugli archi con capacità residua $\geq \Delta$, detto **$\Delta$-grafo residuo** $G_f(\Delta)$.

```pseudo
\begin{algorithm}
\caption{CapacityScaling($G$)}
\begin{algorithmic}
\ForAll{arco $e \in E$}
  \State $f(e) \gets 0$
\EndFor
\State $\Delta \gets$ la più grande potenza di $2 \leq C$
\While{$\Delta \geq 1$}
  \State $G_f(\Delta) \gets$ $\Delta$-grafo residuo di $G$ rispetto a $f$
  \While{esiste un cammino $s \leadsto t$ $P$ in $G_f(\Delta)$}
    \State $f \gets$ \Call{Augment}{$f, c, P$}
    \State aggiorna $G_f(\Delta)$
  \EndWhile
  \State $\Delta \gets \Delta / 2$ \Comment{fase di scaling successiva}
\EndWhile
\State \Return $f$
\end{algorithmic}
\end{algorithm}
```

> [!quote] Teorema — Complessità di Capacity Scaling
> Ci sono $1 + \lfloor \log_2 C \rfloor$ fasi di scaling. In ogni fase ci sono al più $2m$ aumenti. Il numero totale di aumenti è $O(m \log C)$.
>
> **Complessità totale**: $O(m^2 \log C)$

**Idea della dimostrazione del bound $2m$ per fase.** Si usa il lemma: all'inizio della fase $\Delta$, il flusso corrente $f$ soddisfa $\operatorname{val}(f^*) - \operatorname{val}(f) \leq m\Delta$. Questo si dimostra osservando che nella fase precedente (con parametro $2\Delta$) non esistono cammini nel $2\Delta$-grafo residuo: ogni taglio st ha capacità $\leq \operatorname{val}(f) + m \cdot 2\Delta$ (ogni arco contribuisce al più $2\Delta$ alla capacità), quindi $\operatorname{val}(f^*) \leq \operatorname{val}(f) + 2m\Delta$. Poiché nella fase $\Delta$ ogni aumento porta almeno $\Delta$ unità, il numero di aumenti per fase è al più $2m\Delta / \Delta = 2m$.
### Tabella riassuntiva degli algoritmi
| Anno | Metodo | N. aumenti | Complessità |
|---|---|---|---|
| 1955 | Ford-Fulkerson (generico) | $\leq nC$ | $O(m \cdot \operatorname{val}(f^*)) = O(mnC)$ |
| 1972 | Capacity Scaling (Edmonds-Karp) | $O(m \log C)$ | $O(m^2 \log C)$ |
| 1970 | Shortest augmenting path (Edmonds-Karp, Dinitz) | $O(mn)$ | $O(m^2 n)$ |
| 1985 | Improved Capacity Scaling (Gabow) | $O(m \log C)$ | $O(mn \log C)$ |

> [!info] Evoluzione storica degli algoritmi di Max-Flow
> Il problema del massimo flusso ha una storia algoritmicamente ricca. Principali risultati: Karzanov (1974) con blocking flows in $O(n^3)$; Sleator-Tarjan (1983) con dynamic trees in $O(mn \log n)$; Gabow (1985) con improved capacity scaling in $O(mn \log C)$; Goldberg-Tarjan (1988) con push-relabel in $O(mn \log(n^2/m))$; Orlin (2013) in $O(mn)$; Lee-Sidford (2014) in $\tilde{O}(m n^{1/2} \log C)$ con metodi di punto interno; Mądry (2016) con electrical flows in $\tilde{O}(m^{10/7} C^{1/7})$; risultati molto recenti (FOCS 2022) che si avvicinano a $\tilde{O}(m)$.
## Domande tipiche d'esame
> [!example] Domanda 1 — definizioni fondamentali
> **D:** Qual è la differenza tra la capacità di un taglio e il flusso netto attraverso un taglio?
>
> **R:** La **capacità** di un taglio $(A,B)$ è $\operatorname{cap}(A,B) = \sum_{e \text{ da } A \text{ a } B} c(e)$ e dipende solo dalla struttura della rete. Il **flusso netto** è $\sum_{e \text{ da } A \text{ a } B} f(e) - \sum_{e \text{ da } B \text{ a } A} f(e)$ e dipende dal flusso corrente. Per il lemma del valore del flusso, il flusso netto attraverso qualsiasi taglio è uguale a $\operatorname{val}(f)$.

> [!example] Domanda 2 — grafo residuo e archi inversi
> **D:** A cosa serve l'arco inverso nel grafo residuo?
>
> **R:** L'arco inverso $e^{\text{rev}} = (v, u)$ associato all'arco originale $e = (u, v)$ con $f(e) > 0$ permette di **annullare** parte del flusso già inviato su $e$. Quando un cammino aumentante usa $e^{\text{rev}}$, la procedura AUGMENT riduce $f(e)$ del bottleneck: questo è il meccanismo di "undo" che rende Ford-Fulkerson corretto dove il greedy puro fallisce.

> [!example] Domanda 3 — teorema Max-Flow Min-Cut
> **D:** Enuncia il teorema Max-Flow Min-Cut e spiega quando Ford-Fulkerson ci fornisce un certificato di ottimalità.
>
> **R:** Il teorema afferma che $\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A,B)$. Ford-Fulkerson fornisce un certificato quando termina: a quel punto non esistono cammini aumentanti, quindi l'insieme $A$ dei nodi raggiungibili da $s$ in $G_f$ definisce un taglio $(A, B)$ con $\operatorname{cap}(A,B) = \operatorname{val}(f)$, certificando che il flusso è massimo e il taglio è minimo.

> [!example] Domanda 4 — scelta dei cammini aumentanti
> **D:** Perché Ford-Fulkerson generico è pseudo-polinomiale e come Edmonds-Karp risolve il problema?
>
> **R:** Ford-Fulkerson generico può avere $\Theta(C)$ iterazioni (esempio con arco di capacità $C$ al centro e alternanza di cammini che portano solo 1 unità per volta), quindi la complessità $O(mnC)$ dipende dai valori delle capacità, non solo da $m$ e $n$. Edmonds-Karp usa la BFS per scegliere sempre il cammino con **meno archi**: questo garantisce che le distanze BFS siano monotone non decrescenti, limitando il numero totale di aumenti a $O(mn)$ indipendentemente dai valori di $C$, ottenendo complessità polinomiale $O(m^2 n)$.

> [!example] Domanda 5 — capacità irrazionali
> **D:** Ford-Fulkerson termina sempre?
>
> **R:** No. Con capacità **intere** (o razionali), termina in un numero finito di passi per il teorema di terminazione. Con capacità **irrazionali**, possono esistere sequenze infinite di aumenti che convergono a un valore strettamente inferiore al massimo flusso. In questi casi è necessario usare varianti con garanzie di terminazione (come Edmonds-Karp, che usa solo BFS e termina in $O(m^2n)$ indipendentemente dalle capacità).
