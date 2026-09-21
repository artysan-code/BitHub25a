---
tags:
  - algoritmi
  - flussi
slide: ["07-I"]
capitolo: "Kleinberg-Tardos cap. 7"
---
# Flussi di Rete (Max-Flow e Min-Cut)
## Rete di flusso
> [!quote] Definizione — Rete di flusso
> Una **rete di flusso** è una tupla $G = (V, E, s, t, c)$ dove:
> - $(V, E)$ è un **grafo orientato** (diretto);
> - $s \in V$ è la **sorgente** (*source*) e $t \in V$ è il **pozzo** (*sink*), con $s \neq t$;
> - $c: E \to \mathbb{R}_{\geq 0}$ è la **funzione di capacità**, con $c(e) \geq 0$ per ogni arco $e \in E$.
>
> Si assume che tutti i nodi siano raggiungibili da $s$.

L'intuizione è quella di una rete di trasporto: il materiale parte da $s$, scorre lungo gli archi nel rispetto delle loro capacità, e arriva a $t$.

![[mf_rete_di_flusso.png]]
La rete di flusso come la definisce la slide: grafo orientato, sorgente $s$, pozzo $t$, una capacità non negativa su ogni arco.
## Flusso e problema del massimo flusso
> [!quote] Definizione — Flusso st
> Un **flusso st** (*st-flow*) è una funzione $f: E \to \mathbb{R}_{\geq 0}$ che soddisfa:
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Definizione formale del problema del massimo flusso|definizione formale di Max-Flow — 13/06/2024, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Definizione formale quando la traccia non nomina il problema|definizione formale quando la traccia non nomina il problema — 23/09/2025]]

![[mf_flusso_e_valore.png]]
Un flusso con i due vincoli in azione: su ogni arco la notazione è **flusso / capacità**, e il valore $\operatorname{val}(f)$ è quanto esce netto da $s$.
## Taglio e problema del minimo taglio
> [!quote] Definizione — Taglio st (st-cut)
> Un **taglio st** è una **partizione** $(A, B)$ dell'insieme dei nodi — cioè $A \cup B = V$ e $A \cap B = \emptyset$ — tale che $s \in A$ e $t \in B$.
>
> La **capacità del taglio** è la somma delle capacità degli archi che vanno **da $A$ a $B$** (non da $B$ ad $A$):
> $$\operatorname{cap}(A, B) = \sum_{\substack{e = (u,v) \\ u \in A,\ v \in B}} c(e)$$

> [!quote] Definizione — Problema del minimo taglio (Min-Cut)
> Dato $G = (V, E, s, t, c)$, trovare un taglio $(A^*, B^*)$ di **capacità minima**.

> [!example] Taglio — esempio
> Consideriamo una rete con $s$ collegato a $t$ tramite tre archi uscenti da $s$ di capacità 10, 5, 15. Se $A = \{s\}$ e $B = V \setminus \{s\}$, la capacità del taglio è $10 + 5 + 15 = 30$. Un altro taglio con capacità inferiore può escludere alcuni archi di capacità elevata includendo nodi intermedi in $A$.

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Definizione formale del problema del minimo taglio|definizione formale di Min-Cut — 18/07/2025, max 5 righe]]

![[mf_taglio_esempio.png]]
Un taglio st concreto e la sua capacità: si sommano **solo** gli archi che escono da $A$ verso $B$ ($20+25=45$); quelli che rientrano non contano.
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

![[mf_greedy_fallisce.png]]
La slide che diagnostica il fallimento del greedy: una volta che il flusso è stato messo su un arco, non viene mai più tolto.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Definizione formale della rete residua|definizione formale della rete residua — 23/09/2025, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Ruolo dell'arco inverso nel grafo residuo|ruolo dell'arco inverso]]

![[mf_rete_residua_definizione.png]]
La costruzione arco per arco: dall'arco originale nascono l'arco **diretto** con la capacità ancora libera e l'arco **inverso** con il flusso già inviato.

![[mf_rete_residua_esempio.png]]
Sopra la rete $G$ con un flusso, sotto la rete residua $G_f$ che ne deriva. È la figura da tenere davanti finché la costruzione non diventa automatica.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Aumento lungo P e capacità residua di un singolo arco|aumento lungo P e capacità residua di un singolo arco — 26/06/2025]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità originali ≥ β e incremento di ogni augmenting step|capacità originali ≥ β e incremento di ogni step — 02/02/2026]]

![[mf_cammino_aumentante.png]]
Il cammino aumentante è un cammino $s \leadsto t$ **nella rete residua**, e il suo bottleneck è il minimo delle capacità residue lungo il cammino.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità intere e incremento minimo di un aumento|capacità intere e incremento minimo — 09/09/2024]]

![[mf_ff_demo_inizio.png]]
La demo della slide, passo iniziale: flusso nullo su ogni arco.

![[mf_ff_demo_arco_inverso.png]]
Un passo intermedio in cui il cammino aumentante usa un **arco inverso**: il flusso già piazzato viene in parte ritirato e dirottato.

![[mf_ff_demo_finale.png]]
Lo stato finale: nessun cammino aumentante, e il taglio evidenziato ha capacità uguale al valore del flusso — **max flow = min cut**.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Terminazione di Ford-Fulkerson al variare delle capacità|terminazione al variare delle capacità]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Complessità di Ford-Fulkerson e sua polinomialità|complessità e polinomialità — 13/06/2024, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità intere limitate da n² e polinomialità|capacità intere ≤ n² e polinomialità — 02/02/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Bound più stretto con grado entrante limitato e capacità ≤ n²|bound più stretto con grado entrante limitato — 26/06/2025, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità unitarie e numero di iterazioni|capacità unitarie e numero di iterazioni — 09/09/2024, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità unitarie e complessità di Ford-Fulkerson|capacità unitarie e complessità O(n³) — 30/06/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità intere e polinomialità in generale|capacità intere e polinomialità in generale — 26/06/2025]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Θ(n√n) archi e capacità al più 2|Θ(n√n) archi e capacità al più 2 — 02/02/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Un solo nodo con archi entranti di capacità 1|un solo nodo con archi entranti di capacità 1 — 30/06/2026]]

![[mf_analisi_capacita_intere.png]]
L'analisi con capacità intere: ogni aumento porta almeno 1 unità, quindi gli aumenti sono al più $\operatorname{val}(f^*) \leq nC$ e il costo totale è $O(mnC)$.

![[mf_esempio_esponenziale.png]]
L'istanza patologica: con l'arco centrale di capacità 1 e scelta sfortunata dei cammini servono $2C$ iterazioni, esponenziali nei bit di $C$.
## Relazione tra flussi e tagli
### Lemma del valore del flusso
> [!quote] Lemma — Valore del flusso su un taglio
> Sia $f$ un flusso qualsiasi e $(A, B)$ un taglio st qualsiasi. Allora:
> $$\operatorname{val}(f) = \sum_{\substack{e \text{ esce da } A}} f(e) \;-\; \sum_{\substack{e \text{ entra in } A}} f(e)$$

**Dimostrazione.** Poiché $\operatorname{val}(f) = \sum_{e \text{ esce da } s} f(e) - \sum_{e \text{ entra in } s} f(e)$, si estende la somma a tutti i nodi di $A$:
$$\operatorname{val}(f) = \sum_{v \in A} \Bigl(\sum_{e \text{ esce da } v} f(e) - \sum_{e \text{ entra in } v} f(e)\Bigr)$$
Per la conservazione del flusso, ogni termine con $v \neq s$ vale 0. Gli archi interni ad $A$ si cancellano. Rimangono solo gli archi tra $A$ e $B$. $\square$

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Capacità di un taglio e flusso netto attraverso un taglio|capacità di un taglio e flusso netto]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Flusso netto attraverso un taglio e valore del flusso|flusso netto attraverso un taglio e val(f) — 09/09/2024]]

![[mf_lemma_del_valore.png]]
Il lemma del valore: **qualunque** taglio si scelga, il flusso netto che lo attraversa è sempre $\operatorname{val}(f)$.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Flusso netto attraverso un taglio e capacità del taglio|flusso netto e capacità del taglio — 09/09/2024]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Valore del flusso e capacità di un taglio qualsiasi|val(f) e capacità di un taglio qualsiasi — 26/06/2025]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Esistenza di un taglio di capacità uguale a val(f)|esistenza di un taglio di capacità uguale a val(f) — 02/02/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Variante: esistenza di un taglio di capacità uguale al valore di f|variante dello stesso item — 30/06/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Esistenza di un taglio di capacità strettamente maggiore di val(f)|taglio di capacità strettamente maggiore — 30/06/2026]]

![[mf_dualita_debole.png]]
La catena di disuguaglianze della dualità debole: si butta via il flusso entrante in $A$, poi si usa il vincolo di capacità arco per arco.

![[mf_certificato_ottimalita.png]]
Il corollario del certificato: se trovi un flusso e un taglio con lo stesso numero, **entrambi** sono ottimi e la ricerca è finita.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Enunciato del teorema Max-Flow Min-Cut e certificato di ottimalità|enunciato e certificato di ottimalità]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Grafi con taglio minimo di capacità inferiore al massimo flusso|taglio minimo inferiore al massimo flusso — 09/09/2024]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Flusso massimo e assenza di cammini nella rete residua|f massimo e assenza di cammini — 30/06/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Assenza di cammino aumentante e massimalità del flusso|assenza di cammino aumentante e massimalità — 26/06/2025]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Presenza di un cammino aumentante e massimalità del flusso|presenza di un cammino aumentante — 02/02/2026]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Dimostrazione: assenza di cammino aumentante e flusso massimo|dimostrazione: nessun cammino aumentante ⇒ flusso massimo — 23/09/2025, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Taglio minimo costruito dai nodi che raggiungono t|taglio minimo dai nodi che raggiungono t — 26/06/2025]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Calcolo di un taglio di capacità minima in tempo lineare|calcolo del taglio minimo in tempo lineare — 18/07/2025, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Correttezza dell'algoritmo di estrazione del taglio minimo|correttezza dell'algoritmo — 18/07/2025, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Aumentare di 1 la capacità di un arco e valore del flusso massimo|aumentare di 1 la capacità di un arco — 02/02/2026, max 5 righe]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Taglio minimo dopo l'aumento di 1 su ogni capacità|taglio minimo dopo +1 su ogni capacità — 30/06/2026, max 5 righe]]

![[mf_teorema_terza_implicazione.png]]
La slide di $[iii \Rightarrow i]$, cioè **la dimostrazione che viene chiesta all'esame**: $A$ sono i nodi raggiungibili da $s$ in $G_f$, gli archi $A \to B$ sono saturi, quelli $B \to A$ hanno flusso nullo.

![[mf_taglio_minimo_da_flusso_massimo.png]]
Il corollario operativo: da un flusso massimo il taglio minimo esce con **una sola visita** della rete residua.
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

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#Scelta dei cammini aumentanti: Ford-Fulkerson e Edmonds-Karp|Ford-Fulkerson e Edmonds-Karp a confronto]]

→ **Palestra**: [[Esercizi 07 - Flussi di Rete (Max-Flow e Min-Cut)#BFS per i cammini aumentanti e polinomialità|BFS e polinomialità — 09/09/2024]]
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

![[mf_tabella_algoritmi.png]]
La tabella della slide sugli algoritmi a cammini aumentanti: cambia la **strategia di scelta del cammino**, e con essa il numero di aumenti.

> [!info] Evoluzione storica degli algoritmi di Max-Flow
> Il problema del massimo flusso ha una storia algoritmicamente ricca. Principali risultati: Karzanov (1974) con blocking flows in $O(n^3)$; Sleator-Tarjan (1983) con dynamic trees in $O(mn \log n)$; Gabow (1985) con improved capacity scaling in $O(mn \log C)$; Goldberg-Tarjan (1988) con push-relabel in $O(mn \log(n^2/m))$; Orlin (2013) in $O(mn)$; Lee-Sidford (2014) in $\tilde{O}(m n^{1/2} \log C)$ con metodi di punto interno; Mądry (2016) con electrical flows in $\tilde{O}(m^{10/7} C^{1/7})$; risultati molto recenti (FOCS 2022) che si avvicinano a $\tilde{O}(m)$.
