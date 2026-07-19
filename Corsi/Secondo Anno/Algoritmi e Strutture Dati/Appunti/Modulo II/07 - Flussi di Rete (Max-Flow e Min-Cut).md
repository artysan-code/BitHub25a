---
tags:
  - algoritmi
  - flussi
slide: "7-I"
capitolo: "Kleinberg-Tardos cap. 7"
---
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

> [!question] Domanda tipica d'esame — definizione formale del problema del massimo flusso
> **D:** «Esercizio 2 [11 punti] Si consideri il problema del massimo flusso. 1. Si definisca formalmente il problema. (Max 5 righe.)» *(chiesto il 13/06/2024)*
> **R:**
> **Dati.** Rete $G=(V,E,s,t,c)$, con $c: E \to \mathbb{R}_{\geq 0}$ funzione di capacità, $s$ sorgente, $t$ pozzo.
>
> **Flusso.** Una funzione $f: E \to \mathbb{R}_{\geq 0}$ che rispetta il **vincolo di capacità** $0\leq f(e)\leq c(e)$ per ogni arco $e$, e il **vincolo di conservazione**: per ogni nodo $v$ diverso da $s$ e $t$, il flusso entrante in $v$ è uguale al flusso uscente da $v$.
>
> **Valore e obiettivo.** Il valore $\operatorname{val}(f)$ è il flusso netto uscente da $s$ (equivalentemente, per conservazione, quello entrante in $t$). Il problema del massimo flusso chiede il flusso $f$ che massimizza $\operatorname{val}(f)$.
>
> ⏱️ **Se la traccia dà 5 righe**: cita la tupla $G=(V,E,s,t,c)$, i due vincoli (capacità e conservazione) in una riga ciascuno, e chiudi con l'obiettivo di massimizzare $\operatorname{val}(f)$. **Non omettere mai** il vincolo di conservazione: è quello che distingue un flusso da una funzione arbitraria sugli archi.

> [!question] Domanda tipica d'esame — definizione formale (traccia 23/09/2025)
> **D:** «Si definisca formalmente il problema. (Max 5 righe.)» *(chiesto il 23/09/2025)*
> **R:**
> **Definizione.** Stessa del problema del massimo flusso (vedi domanda precedente): dato $G=(V,E,s,t,c)$ con $c: E \to \mathbb{R}_{\geq 0}$, un flusso $f$ soddisfa il vincolo di capacità $0\leq f(e)\leq c(e)$ e il vincolo di conservazione in ogni nodo diverso da $s,t$; si cerca $f$ di valore $\operatorname{val}(f)$ massimo.
>
> **Perché è questo il problema.** La traccia non nomina esplicitamente "massimo flusso", ma nello stesso compito compaiono una domanda sulla rete residua e una dimostrazione sui cammini aumentanti: entrambe hanno senso solo nel contesto Max-Flow, quindi è quello il problema da definire.
>
> ⏱️ **Se la traccia dà 5 righe**: la definizione stessa (vincoli + obiettivo) basta; la nota sull'identificazione del problema è superflua se il testo del compito lo rende ovvio, **ma se la traccia è ambigua come qui, non va mai omessa** — è la parte che giustifica quale definizione si sta scrivendo.
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

> [!question] Domanda tipica d'esame — definizione formale del problema del minimo taglio
> **D:** «Si consideri il problema del calcolo del taglio di capacità minima - Minimum cut problem. 1. Si definisca formalmente il problema. (Max 5 righe.)» *(chiesto il 18/07/2025)*
> **R:**
> **Dati.** Rete $G=(V,E,s,t,c)$.
>
> **Taglio.** Un taglio st è una partizione $(A,B)$ dei nodi con $s\in A$ e $t\in B$.
>
> **Capacità.** $\operatorname{cap}(A,B)=\sum_{e=(u,v):\,u\in A,\,v\in B} c(e)$, cioè la somma delle capacità dei soli archi diretti **da $A$ verso $B$**: gli archi da $B$ ad $A$ non contribuiscono, per quanto grande sia la loro capacità.
>
> **Obiettivo.** Trovare un taglio $(A^*,B^*)$ che minimizzi $\operatorname{cap}(A,B)$ tra tutte le partizioni st possibili.
>
> ⏱️ **Se la traccia dà 5 righe**: definisci taglio st, la formula della capacità con l'osservazione che conta solo il verso $A\to B$, e l'obiettivo di minimizzazione. **Non omettere mai** la direzionalità della capacità — è l'errore più comune (sommare anche gli archi da $B$ ad $A$).
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

> [!question] Domanda tipica d'esame — definizione formale della rete residua
> **D:** «Si definisca formalmente il concetto di rete residua. (Max 5 righe.)» *(chiesto il 23/09/2025)*
> **R:**
> **Dati.** Rete $G=(V,E,s,t,c)$ e flusso $f$.
>
> **Costruzione.** $G_f=(V,E_f,s,t,c_f)$ ha lo stesso insieme di nodi di $G$. Per ogni arco $e=(u,v)\in E$:
> - se $f(e)<c(e)$, l'arco diretto $(u,v)$ sta in $E_f$ con capacità residua $c_f(e)=c(e)-f(e)$ (quanto si può ancora inviare);
> - se $f(e)>0$, l'arco inverso $(v,u)$ sta in $E_f$ con capacità residua $c_f(e^{\text{rev}})=f(e)$ (quanto si può annullare).
>
> In formule: $E_f=\{e\in E: f(e)<c(e)\}\cup\{e^{\text{rev}}: f(e)>0\}$.
>
> **Proprietà chiave.** Un flusso $f'$ è valido in $G_f$ se e solo se $f+f'$ è valido in $G$: ogni cammino aumentante in $G_f$ corrisponde a un miglioramento del flusso in $G$.
>
> ⏱️ **Se la traccia dà 5 righe**: definisci $G_f$ con i due casi (arco diretto se non saturo, arco inverso se $f(e)>0$) e la formula compatta di $E_f$; la proprietà chiave si può accennare in una riga. **Non omettere mai** la condizione $f(e)>0$ per l'esistenza dell'arco inverso — è il dettaglio che spiega perché il grafo residuo può "annullare" flusso.

> [!question] Domanda tipica d'esame — a cosa serve l'arco inverso
> **D:** A cosa serve l'arco inverso nel grafo residuo?
> **R:**
> **Ruolo.** L'arco inverso $e^{\text{rev}} = (v, u)$, associato all'arco originale $e = (u, v)$ con $f(e) > 0$, permette di **annullare** parte del flusso già inviato su $e$.
>
> **Meccanismo.** Quando un cammino aumentante usa $e^{\text{rev}}$, la procedura AUGMENT riduce $f(e)$ del bottleneck del cammino.
>
> **Perché serve.** È il meccanismo di "undo" delle decisioni sbagliate: senza di esso l'algoritmo greedy puro si blocca su cammini sub-ottimali (vedi il controesempio del greedy), perché una volta saturato un arco non c'è modo di dirottare il flusso altrove.
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

> [!question] Domanda tipica d'esame — il bottleneck non è la capacità residua di un singolo arco
> **D:** *(Vero o Falso)* «Sia f un flusso e sia e un arco di un cammino P da s a t nella rete residua Gf. Allora è sempre possibile usare il cammino aumentante P per aumentare il flusso f di cf(e), dove cf(e) è il peso di e nella rete residua Gf.» *(chiesto il 26/06/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** La quantità di cui si può aumentare il flusso lungo $P$ è il bottleneck del cammino, $\operatorname{bottleneck}(G_f,P)=\min_{e'\in P} c_f(e')$, cioè il minimo tra le capacità residue di **tutti** gli archi di $P$, non la capacità residua $c_f(e)$ di un singolo arco $e\in P$ scelto arbitrariamente.
>
> **Controesempio.** Se un altro arco $e'\in P$ ha $c_f(e')<c_f(e)$, usare $c_f(e)$ come incremento violerebbe il vincolo di capacità su $e'$: la procedura AUGMENT satura sempre l'arco di collo di bottiglia, non l'arco $e$ in questione.

> [!question] Domanda tipica d'esame — capacità minima non garantisce l'incremento del bottleneck
> **D:** *(Vero o Falso)* «Se per ogni arco e c(e) ≥ β, allora ogni augmanting step aumenta il flusso corrente di almeno β.» *(chiesto il 02/02/2026)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Il bottleneck di un cammino aumentante $P$ è il minimo delle **capacità residue** $c_f(e)$ degli archi di $P$ in $G_f$, non delle capacità originali $c(e)$ in $G$. Anche se ogni arco originale ha $c(e)\geq\beta$, un arco può avere capacità residua arbitrariamente piccola (vicina a 0 se quasi saturo) oppure essere un arco inverso con capacità residua pari al flusso $f(e)$ già inviato, che può essere minore di $\beta$.
>
> **Conclusione.** Un augmenting step può quindi aumentare il flusso di una quantità inferiore a $\beta$: l'ipotesi $c(e)\geq\beta$ sugli archi originali non si trasferisce alle capacità residue.
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

> [!question] Domanda tipica d'esame — capacità intere garantiscono incrementi interi ≥1
> **D:** *(Vero o Falso)* «Se le capacità sono intere, allora ogni cammino aumentante trovato nella rete residua può essere usato per aumentare il flusso corrente di almeno una unità.» *(chiesto il 09/09/2024)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Per l'invariante di integralità, se tutte le capacità $c(e)$ sono intere, ogni $f(e)$ e ogni capacità residua $c_f(e)$ restano interi durante l'intera esecuzione (per induzione sul numero di aumenti, dato che AUGMENT somma/sottrae il bottleneck, esso stesso intero).
>
> **Conclusione.** Il bottleneck di un cammino aumentante è quindi un minimo di quantità intere e strettamente positive (un arco esiste in $G_f$ solo se ha capacità residua $>0$), dunque è un intero $\geq 1$.
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

> [!question] Domanda tipica d'esame — terminazione con capacità irrazionali
> **D:** Ford-Fulkerson termina sempre?
> **R:**
> **Risposta.** No, non sempre.
>
> **Caso intere/razionali.** Termina in un numero finito di passi per il teorema di terminazione.
>
> **Caso irrazionali.** Possono esistere sequenze infinite di aumenti che convergono a un valore strettamente inferiore al massimo flusso.
>
> **Soluzione.** In questi casi servono varianti con garanzie di terminazione indipendenti dalle capacità, come Edmonds-Karp (usa solo BFS, termina in $O(m^2n)$).

> [!question] Domanda tipica d'esame — complessità e polinomialità di Ford-Fulkerson
> **D:** «2. Si enunci la complessità temporale dell'algoritmo di Ford-Fulkerson, argomentando sulla sua polinomialità o meno. (Max 5 righe.)» *(chiesto il 13/06/2024)*
> **R:**
> **Complessità.** $O(m\cdot\operatorname{val}(f^*))$, dove $m$ è il numero di archi e $\operatorname{val}(f^*)$ è il valore del flusso massimo.
>
> **Polinomialità.** Non è un algoritmo polinomiale in senso stretto: è **pseudo-polinomiale**. La complessità dipende dal valore numerico delle capacità (tramite $\operatorname{val}(f^*)$), non dalla dimensione dell'input in bit.
>
> **Perché è un problema.** Con capacità intere grandi e scelta sfortunata dei cammini aumentanti, il numero di iterazioni può crescere in modo esponenziale rispetto alla dimensione dell'input (che è logaritmica nel valore delle capacità).
>
> ⏱️ **Se la traccia dà 5 righe**: dai la formula $O(m\cdot\operatorname{val}(f^*))$ e dichiara subito che è pseudo-polinomiale; **non omettere mai** la spiegazione del perché (dipendenza dal valore numerico, non dalla dimensione in bit dell'input) — è quella che distingue pseudo-polinomiale da esponenziale puro.

> [!question] Domanda tipica d'esame — capacità polinomiali in n rendono Ford-Fulkerson polinomiale
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi non più grandi di n².» *(chiesto il 02/02/2026)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Per il teorema di terminazione, con capacità intere comprese tra 1 e $C$ il numero di aumenti è al più $\operatorname{val}(f^*)\leq nC$, e ogni aumento costa $O(m)$: la complessità totale è $O(mnC)$. Se $C\leq n^2$, questa diventa $O(mn\cdot n^2)=O(mn^3)$, polinomiale sia in $n$ che in $m$.
>
> **Osservazione.** Il problema di Ford-Fulkerson nasce quando $C$ cresce esponenzialmente nel numero di bit usati per rappresentarlo (es. $C=2^{30}$); qui invece $C$ è esso stesso polinomiale in $n$, quindi il fattore $C$ non introduce dipendenza esponenziale.

> [!question] Domanda tipica d'esame — bound di complessità con grado entrante limitato e capacità ≤ n²
> **D:** «2. Si consideri una rete di flusso G = (V, E, s, t, c) di n nodi in cui ogni nodo ha grado entrante al più 3 (mentre il grado uscente di un nodo può essere anche Θ(n)) e la capacità di ogni arco e ∈ E è un numero intero non più grande di n². Si derivi una delimitazione superiore (quanto più stretta possibile) alla complessità temporale dell'algoritmo di Ford-Fulkerson sulla rete G. Si può affermare che in questo caso l'algoritmo è garantito avere complessità polinomiale? (Max 5 righe.)» *(chiesto il 26/06/2025)*
> **R:**
> **Bound su $m$.** Ogni nodo ha grado entrante al più 3, quindi sommando i gradi entranti su tutti i nodi si ottiene il numero totale di archi: $m=\sum_v \deg^-(v)\leq 3n=O(n)$ (il grado uscente può essere $\Theta(n)$, ma il conteggio via grado entrante limita comunque $m$).
>
> **Bound su $\operatorname{val}(f^*)$, via il taglio intorno a $t$.** Il bound generico $\operatorname{val}(f^*)\leq nC=n\cdot n^2=n^3$ (dal teorema di terminazione) è valido ma non è il più stretto possibile: ignora la struttura del grafo. Per la dualità debole, $\operatorname{val}(f^*)\leq\operatorname{cap}(A,B)$ per **ogni** taglio $(A,B)$; prendo $(A,B)=(V\setminus\{t\},\{t\})$: $\operatorname{cap}(A,B)=\sum_{e\text{ entra in }t} c(e)\leq \deg^-(t)\cdot n^2\leq 3n^2$ (il vincolo sul grado entrante vale anche per $t$). Dunque $\operatorname{val}(f^*)=O(n^2)$, un fattore $n$ più stretto del bound generico.
>
> **Complessità.** $O(m\cdot \operatorname{val}(f^*))=O(n)\cdot O(n^2)=O(n^3)$.
>
> **Conclusione.** Sì, l'algoritmo è garantito avere complessità polinomiale ($O(n^3)$): sia il numero di archi ($O(n)$, dal vincolo sul grado entrante) sia il valore del flusso massimo ($O(n^2)$, dal taglio intorno a $t$) sono limitati polinomialmente in $n$.
>
> ⏱️ **Se la traccia dà 5 righe**: il bound su $m$ (1 riga), il bound su $\operatorname{val}(f^*)$ via il taglio intorno a $t$ (1-2 righe), la moltiplicazione finale $O(n^3)$ con la risposta sì (1 riga). **Non fermarsi** al bound generico $\operatorname{val}(f^*)\leq nC=n^3$ (che dà solo $O(n^4)$): è polinomiale ma non «quanto più stretto possibile» come richiesto dalla traccia — serve il taglio intorno a $t$, che sfrutta il vincolo di grado entrante anche su $t$ stesso.

> [!question] Domanda tipica d'esame — capacità unitarie e numero di iterazioni polinomiale
> **D:** «Si consideri la seguente affermazione: Se le capacità degli archi sono tutte uguali a 1, allora il numero di iterazioni dell'algoritmo di Ford-Fulkerson, ovvero, il numero di aumenti di flusso tramite cammini aumentanti, è sempre polinomiale nel numero di nodi del grafo, indipendentemente dalla strategia usata per trovare i cammini aumentanti. Dire se l'affermazione è vera o falsa motivando la risposta (Max 5 righe).» *(chiesto il 09/09/2024)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Con capacità unitarie il valore del flusso massimo è limitato dal grado uscente di $s$ (al più $n-1$ archi in un grafo semplice), quindi ogni cammino aumentante satura almeno un arco.
>
> **Conclusione.** Il numero di iterazioni è al più $n-1$, polinomiale (lineare) nel numero di nodi, indipendentemente dall'ordine con cui si scelgono i cammini aumentanti.
>
> ⏱️ **Se la traccia dà 5 righe**: il bound sul grado uscente di $s$ e il fatto che ogni aumento satura almeno un arco bastano; **non omettere mai** la conclusione esplicita sul numero di iterazioni ($\leq n-1$).

> [!question] Domanda tipica d'esame — capacità unitarie e complessità O(n³)
> **D:** *(Vero o Falso)* «Se tutti gli archi hanno capacità pari a 1, allora l'algoritmo di Ford-Fulkerson ha complessità O(n^3).» *(chiesto il 30/06/2026)*
> **R:**
> **Risposta.** Vera.
>
> **N. di aumenti.** Con capacità tutte uguali a 1 ($C=1$), il numero di aumenti è al più $\operatorname{val}(f^*)\leq n-1=O(n)$ (bound sul grado uscente di $s$, coerente con la domanda precedente sulle capacità unitarie).
>
> **Costo per aumento.** $O(m)$ tramite BFS/DFS; in un grafo semplice $m=O(n^2)$.
>
> **Complessità totale.** $O(m\cdot n)=O(n^2\cdot n)=O(n^3)$.

> [!question] Domanda tipica d'esame — capacità intere non bastano per la polinomialità in generale
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi.» *(chiesto il 26/06/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Prima parte (corretta).** Con scelta arbitraria del cammino, il numero di iterazioni può essere esponenziale, come nel caso patologico con $C=2^{30}$.
>
> **Seconda parte (sbagliata).** Capacità **intere** non bastano a garantire la polinomialità: il controesempio patologico ha proprio capacità intere ($C$, $C$, $1$) eppure richiede $2C$ iterazioni, esponenziale nel numero di bit usati per rappresentare $C$.
>
> **Cosa serve davvero.** Un vincolo più forte, come capacità polinomiali in $n$ (es. $C\leq n^2$), oppure una strategia di scelta del cammino con garanzie indipendenti da $C$ (Edmonds-Karp, capacity scaling).

> [!question] Domanda tipica d'esame — Θ(n√n) archi e capacità ≤2 non danno complessità lineare
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, e le capacità degli archi sono tutte al più 2, allora l'algoritmo di Ford-Fulkerson ha complessità lineare, ovvero O(n√n).» *(chiesto il 02/02/2026)*
> **R:**
> **Risposta.** Falsa.
>
> **Bound sul numero di aumenti.** Con $C\leq 2$, il numero di aumenti è al più $\operatorname{val}(f^*)\leq nC=O(n)$.
>
> **Costo per aumento.** $O(m)=O(n\sqrt n)$ per la BFS/DFS che cerca il cammino aumentante.
>
> **Complessità totale.** $O(m\cdot\operatorname{val}(f^*))=O(n\sqrt n\cdot n)=O(n^2\sqrt n)$, non $O(n\sqrt n)$.
>
> **Errore nella traccia.** Il costo di ogni singola iterazione (che dipende da $m$) è già $\Theta(n\sqrt n)$, e va moltiplicato per il numero di iterazioni, non confuso con esso.

> [!question] Domanda tipica d'esame — un solo nodo con archi entranti unitari non basta
> **D:** *(Vero o Falso)* «Se esiste un nodo v nella rete i cui archi entranti hanno tutti capacità 1, allora l'algoritmo di Ford-Fulkerson è garantito avere complessità polinomiale.» *(chiesto il 30/06/2026)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Il bound $O(mnC)$ dipende dalla capacità massima $C$ su **tutti** gli archi della rete, non solo su quelli entranti in un singolo nodo $v$.
>
> **Controesempio.** Anche se gli archi entranti in $v$ hanno capacità 1, altri archi della rete (ad esempio quelli del caso patologico con l'arco centrale di capacità $C=2^{30}$) possono avere capacità arbitrariamente grandi e continuare a causare un numero esponenziale di iterazioni con scelta sfortunata dei cammini aumentanti.
## Relazione tra flussi e tagli
### Lemma del valore del flusso
> [!quote] Lemma — Valore del flusso su un taglio
> Sia $f$ un flusso qualsiasi e $(A, B)$ un taglio st qualsiasi. Allora:
> $$\operatorname{val}(f) = \sum_{\substack{e \text{ esce da } A}} f(e) \;-\; \sum_{\substack{e \text{ entra in } A}} f(e)$$

**Dimostrazione.** Poiché $\operatorname{val}(f) = \sum_{e \text{ esce da } s} f(e) - \sum_{e \text{ entra in } s} f(e)$, si estende la somma a tutti i nodi di $A$:
$$\operatorname{val}(f) = \sum_{v \in A} \Bigl(\sum_{e \text{ esce da } v} f(e) - \sum_{e \text{ entra in } v} f(e)\Bigr)$$
Per la conservazione del flusso, ogni termine con $v \neq s$ vale 0. Gli archi interni ad $A$ si cancellano. Rimangono solo gli archi tra $A$ e $B$. $\square$

> [!question] Domanda tipica d'esame — definizioni fondamentali
> **D:** Qual è la differenza tra la capacità di un taglio e il flusso netto attraverso un taglio?
> **R:**
> **Capacità.** $\operatorname{cap}(A,B) = \sum_{e \text{ da } A \text{ a } B} c(e)$: dipende solo dalla struttura della rete (le capacità), non dal flusso corrente.
>
> **Flusso netto.** $\sum_{e \text{ da } A \text{ a } B} f(e) - \sum_{e \text{ da } B \text{ a } A} f(e)$: dipende dal flusso $f$ scelto.
>
> **Relazione.** Per il lemma del valore del flusso, il flusso netto attraverso qualsiasi taglio è uguale a $\operatorname{val}(f)$, indipendentemente da quale taglio si scelga.

> [!question] Domanda tipica d'esame — il flusso netto attraverso un taglio è sempre val(f)
> **D:** *(Vero o Falso)* «per ogni taglio (A.B) e per ogni flusso f, il flusso netto che attraversa (A.B) è sempre uguale al valore di f.» *(chiesto il 09/09/2024)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È esattamente l'enunciato del Lemma del valore del flusso: per ogni flusso $f$ e ogni taglio st $(A,B)$, $\operatorname{val}(f)=\sum_{e\text{ esce da }A} f(e) - \sum_{e\text{ entra in }A} f(e)$, cioè il flusso netto che attraversa il taglio è sempre uguale al valore del flusso, indipendentemente da quale taglio si scelga.
>
> **Osservazione.** Questo vale per **qualsiasi** flusso valido, non solo per il flusso massimo — a differenza della capacità del taglio, che è un limite superiore (dualità debole) raggiunto con uguaglianza solo per il taglio minimo quando $f$ è massimo.
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

> [!question] Domanda tipica d'esame — il flusso netto non supera mai la capacità del taglio
> **D:** *(Vero o Falso)* «Dato un taglio (A, B) e un flusso f, allora il flusso netto che passa per (A, B) è sempre maggiore o uguale alla capacità di (A, B).» *(chiesto il 09/09/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Per la dualità debole, il flusso netto attraverso un taglio (che, per il lemma del valore, coincide con $\operatorname{val}(f)$) è sempre **minore o uguale** alla capacità del taglio, mai maggiore: $\operatorname{val}(f)\leq\operatorname{cap}(A,B)$.
>
> **Da dove viene.** Il flusso netto uscente da $A$ è al più la somma delle capacità degli archi uscenti da $A$ (per il vincolo di capacità), meno un termine non negativo dato dal flusso entrante in $A$.

> [!question] Domanda tipica d'esame — val(f) non è sempre uguale a cap(A,B)
> **D:** *(Vero o Falso)* «dato un flusso f di G e un st-taglio (A, B), il valore del flusso v(f) è sempre uguale alla capacità del taglio cap(A, B)» *(chiesto il 26/06/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Per la dualità debole vale solo $\operatorname{val}(f)\leq\operatorname{cap}(A,B)$, come disuguaglianza, non come uguaglianza.
>
> **Quando vale l'uguaglianza.** Solo in casi speciali: per il corollario di certificato di ottimalità, quando $\operatorname{val}(f)=\operatorname{cap}(A,B)$ è garanzia che $f$ è massimo e $(A,B)$ è il taglio minimo — non è quindi una proprietà valida per un flusso e un taglio scelti arbitrariamente.

> [!question] Domanda tipica d'esame — non esiste sempre un taglio di capacità uguale a v(f)
> **D:** *(Vero o Falso)* «Dato un flusso f di G, c'è sempre un s-t-taglio (A, B) la cui capacità è uguale a v(f).» *(chiesto il 02/02/2026)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Vale solo il verso debole: per **ogni** taglio $(A,B)$, $\operatorname{cap}(A,B)\geq\operatorname{val}(f)$ (dualità debole), ma non è garantito che esista un taglio con capacità **esattamente** uguale a $\operatorname{val}(f)$.
>
> **Eccezione.** Solo se $f$ è già un flusso massimo: in quel caso il taglio minimo, individuato dai nodi raggiungibili da $s$ in $G_f$, ha proprio capacità $\operatorname{val}(f)$.
>
> **Caso generico.** Per un flusso $f$ non massimo, tutti i tagli possono avere capacità strettamente maggiore di $\operatorname{val}(f)$.

> [!question] Domanda tipica d'esame — esiste sempre un taglio di capacità uguale al valore del flusso? (variante)
> **D:** *(Vero o Falso)* «Per ogni flusso f, esiste sempre un taglio (A, B) la cui capacità è uguale al valore di f.» *(chiesto il 30/06/2026)*
> **R:**
> **Risposta.** Falsa, per lo stesso motivo della domanda precedente.
>
> **Perché.** La dualità debole garantisce solo $\operatorname{cap}(A,B)\geq\operatorname{val}(f)$ per ogni taglio, non l'esistenza di un taglio con uguaglianza esatta.
>
> **Quando esiste garantito.** Solo se $f$ è un flusso massimo (è allora il taglio minimo, per il teorema Max-Flow Min-Cut); per un flusso qualsiasi non c'è alcuna garanzia.

> [!question] Domanda tipica d'esame — non è garantito un taglio di capacità strettamente maggiore
> **D:** *(Vero o Falso)* «Per ogni flusso f esiste sempre almeno un taglio (A, B) tale che la capacità di (A, B) è strettamente più grande del valore di f.» *(chiesto il 30/06/2026)*
> **R:**
> **Risposta.** Falsa.
>
> **Controesempio.** Una rete con un solo arco $s\to t$ di capacità $c(s,t)=k$ e flusso $f(s,t)=k$ (cioè $f$ è già massimo, $\operatorname{val}(f)=k$). L'unico taglio st possibile è $(\{s\},\{t\})$, con $\operatorname{cap}(\{s\},\{t\})=k=\operatorname{val}(f)$: non esiste alcun altro taglio, quindi nessun taglio ha capacità strettamente maggiore di $\operatorname{val}(f)$.
>
> **Osservazione.** In generale, quando $f$ è massimo, il taglio minimo ha capacità esattamente uguale a $\operatorname{val}(f)$, non strettamente maggiore.
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

> [!question] Domanda tipica d'esame — teorema Max-Flow Min-Cut
> **D:** Enuncia il teorema Max-Flow Min-Cut e spiega quando Ford-Fulkerson ci fornisce un certificato di ottimalità.
> **R:**
> **Enunciato.** $\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A,B)$.
>
> **Quando c'è il certificato.** Alla terminazione di Ford-Fulkerson: a quel punto non esistono cammini aumentanti, quindi l'insieme $A$ dei nodi raggiungibili da $s$ in $G_f$ definisce un taglio $(A, B)$ con $\operatorname{cap}(A,B) = \operatorname{val}(f)$, certificando che il flusso è massimo e il taglio è minimo.

> [!question] Domanda tipica d'esame — non esistono grafi con min-cut < max-flow
> **D:** *(Vero o Falso)* «Ci sono dei grafi per cui la capacità del taglio di capacità minima è strettamente inferiore al massimo flusso.» *(chiesto il 09/09/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Per il teorema Max-Flow Min-Cut il valore del massimo flusso è **sempre uguale** alla capacità del taglio di capacità minima ($\max_f\operatorname{val}(f)=\min_{(A,B)}\operatorname{cap}(A,B)$), mai strettamente inferiore.
>
> **Osservazione.** La dualità debole esclude già che il taglio minimo possa avere capacità inferiore al massimo flusso (varrebbe $\operatorname{val}(f^*)\leq\operatorname{cap}(A,B)$ per ogni taglio, incluso quello minimo); il teorema garantisce inoltre che questa disuguaglianza diventa sempre uguaglianza per il taglio ottimo.

> [!question] Domanda tipica d'esame — f massimo solo se non c'è cammino aumentante
> **D:** *(Vero o Falso)* «Dato un flusso f, f è massimo solo se nella rete residua G_f non c'è alcun cammino da s a t.» *(chiesto il 30/06/2026)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È il teorema dei cammini aumentanti: $f$ è massimo se e solo se non esiste un cammino aumentante in $G_f$.
>
> **Direzione richiesta.** La direzione «solo se» ($f$ massimo $\Rightarrow$ nessun cammino aumentante) segue per contronominale: se un cammino aumentante esistesse, AUGMENT produrrebbe un flusso di valore strettamente maggiore, contraddicendo la massimalità di $f$.

> [!question] Domanda tipica d'esame — nessun cammino aumentante implica flusso massimo
> **D:** *(Vero o Falso)* «Dato un flusso f, se nella rete residua Gf non c'è alcun cammino da s a t, allora f è un flusso massimo.» *(chiesto il 26/06/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È la direzione $[3\Rightarrow 2]$ del teorema dei cammini aumentanti: se non ci sono cammini $s\leadsto t$ in $G_f$, si può costruire il taglio $(A,B)$ con $A$ = nodi raggiungibili da $s$ in $G_f$; tutti gli archi da $A$ a $B$ risultano saturi e quelli da $B$ ad $A$ hanno flusso nullo.
>
> **Conclusione.** Quindi $\operatorname{cap}(A,B)=\operatorname{val}(f)$, che per il corollario di certificato di ottimalità implica che $f$ è massimo.

> [!question] Domanda tipica d'esame — un cammino aumentante implica che f non è massimo
> **D:** *(Vero o Falso)* «Dato un flusso f, se nella rete residua Gf c'è un cammino da s a t, allora f non è massimo.» *(chiesto il 02/02/2026)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È la contronominale della direzione $[2\Rightarrow 3]$ del teorema dei cammini aumentanti: se esiste un cammino aumentante $P$ in $G_f$, $\operatorname{AUGMENT}(f,c,P)$ produce un flusso $f'$ con $\operatorname{val}(f')=\operatorname{val}(f)+\operatorname{bottleneck}(G_f,P)>\operatorname{val}(f)$, quindi $f$ non poteva essere massimo.

> [!question] Domanda tipica d'esame — dimostrazione: nessun cammino aumentante implica flusso massimo
> **D:** «Si dimostri che se nella rete residua corrispondente ad un certo flusso f non c'è nessun cammino dalla sorgente al pozzo, allora f è un flusso massimo. (Max 5 righe.)» *(chiesto il 23/09/2025)*
> **R:**
> **Impostazione.** Sia $A$ l'insieme dei nodi raggiungibili da $s$ in $G_f$: per ipotesi $t\notin A$ (altrimenti esisterebbe un cammino aumentante), quindi $(A,B)$ con $B=V\setminus A$ è un taglio st valido.
>
> **Archi da $A$ a $B$ sono saturi.** Per ogni arco $e=(u,v)$ con $u\in A,v\in B$: se fosse $f(e)<c(e)$, allora $e$ apparterrebbe a $G_f$ e $v$ sarebbe raggiungibile da $s$, contraddicendo $v\in B$; dunque $f(e)=c(e)$.
>
> **Archi da $B$ a $A$ hanno flusso nullo.** Per ogni arco $e=(v,u)$ con $v\in B,u\in A$: se fosse $f(e)>0$, l'arco inverso apparterrebbe a $G_f$ rendendo $v$ raggiungibile da $s$, assurdo; dunque $f(e)=0$.
>
> **Conclusione.** Per il lemma del valore del flusso, $\operatorname{val}(f)=\sum_{e\text{ esce da }A} f(e)-\sum_{e\text{ entra in }A} f(e)=\sum_{e\text{ esce da }A} c(e)-0=\operatorname{cap}(A,B)$. Per il corollario di certificato di ottimalità, $\operatorname{val}(f)=\operatorname{cap}(A,B)$ implica che $f$ è un flusso massimo. $\square$
>
> ⏱️ **Se la traccia dà 5 righe**: definisci $A$ e il taglio $(A,B)$ (1 riga), enuncia sinteticamente perché gli archi $A\to B$ sono saturi e quelli $B\to A$ sono nulli (2 righe, l'argomento "altrimenti il nodo sarebbe raggiungibile" in forma compatta), chiudi con l'uguaglianza $\operatorname{val}(f)=\operatorname{cap}(A,B)$ e il richiamo al corollario (1-2 righe). **Non omettere mai** il perché gli archi sono saturi/nulli — è il cuore della dimostrazione, non un dettaglio tecnico.

> [!question] Domanda tipica d'esame — taglio minimo via nodi che raggiungono t
> **D:** *(Vero o Falso)* «Sia f un flusso tale che, nella rete residua Gf, s e t sono separati. Sia B l'insieme di tutti e soli i nodi che possono raggiungere t. Allora (V \ B, B) è un taglio minimo di G.» *(chiesto il 26/06/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Impostazione.** È la costruzione duale di quella standard (che usa $A$ = nodi raggiungibili **da** $s$): qui $B$ = nodi che possono **raggiungere** $t$ in $G_f$. Se $s$ e $t$ sono separati in $G_f$, allora $s\notin B$ (altrimenti esisterebbe un cammino da $s$ a $t$), quindi $(V\setminus B, B)$ è un taglio st valido.
>
> **Argomento di saturazione.** Ogni arco entrante in $B$ dall'esterno deve essere saturo (altrimenti l'origine dell'arco potrebbe raggiungere $t$ e starebbe in $B$); ogni arco uscente da $B$ verso l'esterno ha flusso nullo.
>
> **Conclusione.** Si ottiene $\operatorname{cap}(V\setminus B,B)=\operatorname{val}(f)$, che per il corollario di certificato di ottimalità rende $(V\setminus B,B)$ un taglio minimo.

> [!question] Domanda tipica d'esame — calcolo del taglio minimo in tempo lineare da un flusso massimo
> **D:** «2. Si descriva come è possibile, dato un flusso massimo, calcolare in tempo lineare un taglio di capacità minima. (Max 5 righe.)» *(chiesto il 18/07/2025)*
> **R:** Dato un flusso massimo $f^*$, si costruisce la rete residua $G_{f^*}$ in tempo $O(m)$ e si esegue una BFS o DFS a partire da $s$ (vedi [[08 - Grafi e Visite]]), ottenendo in tempo $O(n+m)$ l'insieme $A$ dei nodi raggiungibili da $s$ in $G_{f^*}$. Si pone $B=V\setminus A$: $(A,B)$ è un taglio st, e $t\notin A$ perché $f^*$ essendo massimo non ammette cammini aumentanti (teorema dei cammini aumentanti), quindi $s$ e $t$ sono separati in $G_{f^*}$. Il tempo totale è $O(n+m)$, lineare nella dimensione della rete.

> [!question] Domanda tipica d'esame — correttezza dell'algoritmo di estrazione del taglio minimo
> **D:** «3. Si discuta in modo conciso e preciso la correttezza dell'algoritmo fornito nel punto precedente. (Max 5 righe.)» *(chiesto il 18/07/2025)*
> **R:** La correttezza segue dalla dimostrazione $[3\Rightarrow 1]$ del teorema dei cammini aumentanti: poiché $f^*$ è massimo, non esistono cammini $s\leadsto t$ in $G_{f^*}$ (per il teorema), quindi ogni arco $e=(u,v)$ con $u\in A,v\in B$ deve essere saturo ($f^*(e)=c(e)$, altrimenti $v$ sarebbe raggiungibile da $s$) e ogni arco $e=(v,u)$ con $v\in B,u\in A$ deve avere flusso nullo ($f^*(e)=0$, altrimenti l'arco inverso renderebbe $v$ raggiungibile). Per il lemma del valore del flusso, $\operatorname{val}(f^*)=\sum_{e\text{ esce da }A} c(e) - 0=\operatorname{cap}(A,B)$: il taglio prodotto ha capacità esattamente uguale al valore del flusso massimo, e per il corollario di certificato di ottimalità questo garantisce che $(A,B)$ è un taglio minimo.

> [!question] Domanda tipica d'esame — aumentare la capacità di un arco di 1 unità aumenta sempre il flusso massimo?
> **D:** «2. Sia G = (V, E, s, t, c) una rete di flusso di n nodi e m archi con capacità intere. Immaginate di aver già calcolato un flusso massimo f per G. Ora vi danno la possibilità di aumentare di una unità la capacità di un arco a vostra scelta. Mostrate che non è sempre possibile aumentare il valore del flusso massimo. E fornite un algoritmo di complessità O(n+m) che decide se è possibile farlo o meno. (Max 5 righe.)» *(chiesto il 02/02/2026)*
> **R:** Non è sempre possibile: aumentare $c(u,v)$ di 1 fa crescere il flusso massimo **se e solo se** quell'unità in più crea un nuovo cammino aumentante, cioè se in $G_f$ esiste un cammino $s \leadsto u$, l'arco $(u,v)$, e un cammino $v \leadsto t$. Algoritmo $O(n+m)$: costruita la rete residua $G_f$, si fanno **due** visite — una BFS/DFS in avanti da $s$, che dà l'insieme $S$ dei nodi raggiungibili da $s$; una BFS/DFS all'indietro da $t$ (percorrendo gli archi residui in senso inverso), che dà l'insieme $T$ dei nodi da cui si raggiunge $t$. L'aumento su $(u,v)$ è utile **se e solo se $u \in S$ e $v \in T$**.
> **Attenzione**: la sola condizione $u \in S$ e $v \notin S$ **non basta**. Controesempio: rete $s\to a$, $s\to b$, $a\to t$, $b\to t$ tutte di capacità 1. Il flusso massimo vale 2, tutti gli archi sono saturi e $S=\{s\}$: l'arco $(s,a)$ soddisfa $u\in S,\ v\notin S$, ma portare $c(s,a)$ a 2 lascia il flusso massimo a 2, perché $a$ non ha comunque modo di raggiungere $t$ ($a\to t$ è saturo). Con il criterio corretto si ha $T=\{t\}$, quindi $a\notin T$ e l'arco viene giustamente scartato.

> [!question] Domanda tipica d'esame — un taglio minimo non resta minimo se si aumentano tutte le capacità
> **D:** *(Vero o Falso)* «2. Si consideri la seguente affermazione e si dica se è vera o falsa, giustificando la risposta. (Max 5 righe.) Claim: Sia (A, B) un s-t-cut di capacità minima per la rete G. Sia G' la rete ottenuta da G aumentando la capacità di ogni arco di esattamente 1. Allora (A, B) è un s-t-cut di capacità minima anche per G'.» *(chiesto il 30/06/2026)*
> **R:** Falsa. Aumentando la capacità di **ogni** arco di 1, la capacità di un taglio $(A,B)$ cresce di una quantità pari al numero di archi che attraversano $(A,B)$ da $A$ a $B$: $\operatorname{cap}_{G'}(A,B)=\operatorname{cap}_G(A,B)+|\{e=(u,v): u\in A, v\in B\}|$. Tagli diversi possono avere un numero diverso di archi uscenti da $A$, quindi l'incremento non è uniforme tra i tagli: un taglio $(A',B')$ che in $G$ aveva capacità leggermente superiore a $\operatorname{cap}_G(A,B)$ ma attraversato da meno archi può ricevere un incremento minore e risultare, in $G'$, di capacità inferiore a quella di $(A,B)$. Quindi il taglio minimo può cambiare quando si aumentano uniformemente tutte le capacità.
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

> [!question] Domanda tipica d'esame — scelta dei cammini aumentanti
> **D:** Perché Ford-Fulkerson generico è pseudo-polinomiale e come Edmonds-Karp risolve il problema?
> **R:** Ford-Fulkerson generico può avere $\Theta(C)$ iterazioni (esempio con arco di capacità $C$ al centro e alternanza di cammini che portano solo 1 unità per volta), quindi la complessità $O(mnC)$ dipende dai valori delle capacità, non solo da $m$ e $n$. Edmonds-Karp usa la BFS per scegliere sempre il cammino con **meno archi**: questo garantisce che le distanze BFS siano monotone non decrescenti, limitando il numero totale di aumenti a $O(mn)$ indipendentemente dai valori di $C$, ottenendo complessità polinomiale $O(m^2 n)$.

> [!question] Domanda tipica d'esame — BFS nei cammini aumentanti garantisce la polinomialità (Edmonds-Karp)
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Fulkerson, se si usa la visita BFS per trovare i cammini aumentanti, ha una complessità polinomiale nella dimensione dell'istanza.» *(chiesto il 09/09/2024)*
> **R:** Vera: usare la BFS per scegliere sempre il cammino aumentante con il minor numero di archi è esattamente l'algoritmo di Edmonds-Karp, la cui complessità è $O(m^2n)$ (al più $O(mn)$ aumenti, ciascuno costa $O(m)$ con la BFS). Questo bound dipende solo da $n$ e $m$, non dal valore delle capacità: a differenza di Ford-Fulkerson generico, è quindi polinomiale nella dimensione dell'istanza indipendentemente da $C$.
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
