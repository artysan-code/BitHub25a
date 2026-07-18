# Minimum Spanning Tree
Il **Minimum Spanning Tree** (MST), o **albero ricoprente minimo**, è uno dei problemi fondamentali su grafi pesati: dato un grafo connesso non orientato con pesi reali sugli archi, si cerca l'insieme di archi che connette tutti i nodi con costo totale minimo. Il problema è risolvibile in modo efficiente con algoritmi [[01 - Greedy e Interval Scheduling|greedy]], la cui correttezza si basa su due proprietà strutturali — la *cut property* e la *cycle property* — che stabiliscono quali archi possono o non possono appartenere a un MST. Questa nota tratta le definizioni fondamentali, le due proprietà con le relative dimostrazioni, l'algoritmo di Kruskal (basato su [[02 - Union-Find]]) e l'algoritmo di Prim (basato su [[07 - Code con Priorità e Heap]]). Un'applicazione al clustering gerarchico conclude la nota.
## Definizioni
> [!quote] Definizione — Minimum Spanning Tree
> Dato un grafo connesso non orientato $G = (V, E)$ con pesi reali $c_e$ sugli archi, un **albero ricoprente** (*spanning tree*) è un sottoinsieme $T \subseteq E$ tale che $T$ è un albero che connette tutti i vertici di $G$. Un **albero ricoprente minimo** (MST) è uno spanning tree che minimizza il costo totale:
> $$c(T) = \sum_{e \in T} c_e$$

> [!question] Domanda tipica d'esame — Definizione formale del problema
> **D:** «1. Si definisca formalmente il problema.» *(chiesto il 02/02/2026)*
> **R:** Dato un grafo connesso non orientato $G=(V,E)$ con pesi reali $c_e$ sugli archi, il problema del Minimum Spanning Tree consiste nel trovare un sottoinsieme di archi $T \subseteq E$ tale che $T$ sia un albero che connette tutti i vertici di $G$ (uno spanning tree) e tale che il costo totale $c(T) = \sum_{e \in T} c_e$ sia minimo tra tutti gli spanning tree possibili di $G$: è esattamente la definizione data nel box sopra.

> [!quote] Teorema — Numero di spanning tree (Cayley)
> Il grafo completo $K_n$ ha esattamente $n^{n-2}$ spanning tree distinti.

Il Teorema di Cayley mostra che il numero di spanning tree cresce esponenzialmente in $n$: la ricerca per forza bruta è impraticabile anche per grafi piccoli.
### Unicità dell'MST
L'MST **non è unico** in generale: se esistono archi con lo stesso peso, possono esistere più MST di costo uguale.
> [!quote] Proprietà — Unicità dell'MST
> Se tutti i pesi degli archi di $G$ sono **distinti**, allora l'MST è **unico**.

> [!question] Domanda tipica d'esame — Unicità e pesi ripetuti
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G non sono distinti, sicuramente esistono due MST (distinti) di G.» *(chiesto il 18/07/2022)*
> **R:** Falsa: i pesi ripetuti sono condizione necessaria ma non sufficiente per avere più MST distinti. Se $G$ non contiene cicli (è già un albero) esiste un'unica soluzione ricoprente indipendentemente dai pesi, anche se questi si ripetono; il duplicato deve inoltre trovarsi in un ciclo per generare una scelta alternativa che porti a un MST diverso ma di pari costo.

```
Esempio con pesi uguali (tre spanning tree diversi, stesso costo):

    B              B              B
1       1      1       1      1       1
A   1   C    A   1   C    A   1   C
```

> [!info] Tre algoritmi greedy per l'MST
> Il prof. Gualà presenta tre algoritmi:
> - **Kruskal**: parte da $T = \emptyset$, aggiunge archi in ordine crescente di costo se non formano ciclo.
> - **Reverse-Delete**: parte da $T = E$, rimuove archi in ordine decrescente se non disconnettono $T$.
> - **Prim**: parte da un nodo sorgente $s$, espande l'albero aggiungendo ad ogni passo l'arco di costo minimo che ha un solo estremo in $T$.
>
> Tutti e tre producono un MST; questa nota approfondisce Kruskal e Prim.
## Cicli, tagli e intersezione
Prima di dimostrare la correttezza degli algoritmi, introduciamo i concetti fondamentali di ciclo e taglio.
### Ciclo
> [!quote] Definizione — Ciclo
> Un **ciclo** è un insieme di archi della forma $a$-$b$, $b$-$c$, $\ldots$, $y$-$z$, $z$-$a$.

```
Esempio di ciclo C = {1-2, 2-3, 3-4, 4-5, 5-6, 6-1}:

    2 --- 3
   /       \
  1         4
   \       /
    6 --- 5
          |
          7 --- 8
```
### Taglio e cutset
> [!quote] Definizione — Taglio e cutset
> Un **taglio** (*cut*) è un sottoinsieme di nodi $S \subseteq V$ (equivalentemente, una partizione di $V$ in $S$ e $V \setminus S$). Il **cutset** $D$ associato al taglio $S$ è il sottoinsieme di archi con **esattamente un** estremo in $S$:
> $$D = \{(u,v) \in E : u \in S,\ v \notin S\}$$

```
Esempio con S = {4, 5, 8}:

    2 --- 3
   /       \
  1         4*
   \       /|
    6 --- 5*|
          | |
          7 --- 8*

Cutset D = {5-6, 5-7, 3-4, 3-5, 7-8}   (* = nodi in S)
```
### Intersezione ciclo-cutset
> [!quote] Proprietà — Intersezione ciclo-cutset
> Un ciclo $C$ e un cutset $D$ si intersecano in un **numero pari** di archi (eventualmente zero).

**Idea della dimostrazione.** Percorrendo il ciclo, ogni volta che lo attraversiamo da $S$ a $V \setminus S$ dobbiamo necessariamente rientrare in $S$ prima di completare il giro. Ogni "uscita" corrisponde a un arco del cutset, e ogni "entrata" corrisponde a un altro arco del cutset: le uscite e le entrate si bilanciano, producendo sempre un numero pari. In generale l'intersezione ha $2k$ archi per qualche $k \geq 0$.
## Cut property e Cycle property
Queste due proprietà sono il **cuore della correttezza** degli algoritmi greedy per l'MST.
### Cut property
> [!quote] Proprietà — Cut property (proprietà del taglio)
> Sia $S$ un qualsiasi sottoinsieme di nodi, e sia $e$ l'arco di **costo minimo** con esattamente un estremo in $S$ (l'arco di costo minimo che attraversa il taglio). Allora esiste un MST che **contiene** $e$.

> [!question] Domanda tipica d'esame — Enunciato della cut property
> **D:** «2. Si enunci formalmente la proprietà del taglio (cut property).» *(chiesto il 02/02/2026)*
> **R:** Dato un taglio $(S, V\setminus S)$ con $\emptyset \neq S \subset V$ (cfr. box **Definizione — Taglio e cutset**), sia $e$ l'arco di costo minimo tra quelli con esattamente un estremo in $S$ (il minimo del cutset $D$). Nella formulazione usata in questa nota, esiste sempre almeno un MST di $G$ che contiene $e$, anche se il minimo non è stretto (più archi di ugual peso minimo nel cutset). Se invece $e$ è l'unico arco di peso minimo del taglio (minimo stretto), allora $e$ appartiene a *ogni* MST di $G$, non solo ad uno.

**Dimostrazione (scambio di archi).** Sia $T^*$ un MST che non contiene $e = (u, v)$ con $u \in S$, $v \notin S$.
1. Aggiungendo $e$ a $T^*$ si crea un ciclo $C$.
2. Per la proprietà di intersezione ciclo-cutset, $C$ e il cutset $D$ di $S$ si intersecano in un numero pari $\geq 2$ di archi. Uno di questi è $e$; sia $f \neq e$ un altro arco nell'intersezione (anch'esso con un estremo in $S$ e uno in $V \setminus S$).
3. Costruiamo $T' = T^* \cup \{e\} \setminus \{f\}$: sostituiamo $f$ con $e$. $T'$ è ancora uno spanning tree (abbiamo rimosso un arco dal ciclo).
4. Poiché $e$ è l'arco di costo minimo che attraversa il taglio, $c_e \leq c_f$, quindi $c(T') \leq c(T^*)$.
5. Essendo $T^*$ un MST, $c(T') = c(T^*)$: $T'$ è un MST e contiene $e$. $\square$

```
Visuale dello scambio:

    S          V \ S
    .          .
    . u        .
    .   \  e   .
    .    o---->o  v
    .          .
    .    o---->o     <- f (altro arco del cutset nel ciclo C)
    .          .
    T' = T* + {e} - {f}
```

> [!question] Domanda tipica d'esame — Dimostrazione della cut property
> **D:** «3. Si fornisca una dimostrazione della proprietà del taglio.» *(chiesto il 02/02/2026)*
> **R:** Si procede per assurdo con l'argomento di scambio di archi mostrato sopra: sia $T^*$ un MST che non contiene $e=(u,v)$, l'arco di costo minimo del cutset di $S$. Aggiungendo $e$ a $T^*$ si crea un ciclo $C$; per la proprietà di intersezione ciclo-cutset, $C$ interseca il cutset $D$ di $S$ in un numero pari $\geq 2$ di archi, quindi esiste $f \neq e$ anch'esso nel cutset. Costruendo $T' = T^* \cup \{e\} \setminus \{f\}$ si ottiene ancora uno spanning tree, e poiché $e$ è il minimo del cutset, $c_e \leq c_f$, dunque $c(T') \leq c(T^*)$. Essendo $T^*$ un MST, deve valere $c(T')=c(T^*)$: $T'$ è quindi un MST che contiene $e$, il che dimostra la proprietà.

> [!question] Domanda tipica d'esame — Arco più leggero incidente a un nodo
> **D:** *(Vero o Falso)* «Sia v un nodo qualsiasi. L'arco più leggero incidente a v fa parte sempre di un qualche MST di G.» *(chiesto il 18/07/2025)*
> **R:** Vero: è un corollario diretto della cut property applicata al taglio banale $S=\{v\}$. Il cutset di $S$ è esattamente l'insieme degli archi incidenti a $v$, quindi il suo arco di costo minimo (l'arco più leggero incidente a $v$) appartiene ad almeno un MST di $G$.

> [!question] Domanda tipica d'esame — L'arco di peso massimo può essere obbligato
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G sono distinti, l'arco di peso minimo appartiene sempre all'MST T di G mentre l'arco di peso massimo non appartiene mai a T.» *(chiesto il 28/09/2022)*
> **R:** Falsa: la prima parte è corretta (l'arco di peso minimo assoluto è il minimo di ogni taglio che attraversa, quindi appartiene per cut property a ogni MST, essendo i pesi distinti). La seconda parte è sbagliata: l'arco di peso massimo può essere un ponte (l'unico collegamento tra due componenti), nel qual caso è obbligato in ogni spanning tree, MST incluso, indipendentemente dal suo peso.
### Cycle property
> [!quote] Proprietà — Cycle property (proprietà del ciclo)
> Sia $C$ un qualsiasi ciclo in $G$, e sia $f$ l'arco di **costo massimo** in $C$. Allora esiste un MST che **non contiene** $f$.

**Dimostrazione (scambio di archi).** Sia $T^*$ un MST che contiene $f$.
1. Rimuovendo $f$ da $T^*$ si spezza $T^*$ in due componenti, creando un taglio $S$.
2. Per la proprietà di intersezione ciclo-cutset, il ciclo $C$ e il cutset $D$ di $S$ si intersecano in un numero pari $\geq 2$ di archi. Uno di questi è $f$; sia $e \neq f$ un altro arco nell'intersezione.
3. Costruiamo $T' = T^* \cup \{e\} \setminus \{f\}$: sostituiamo $f$ con $e$. $T'$ è ancora uno spanning tree.
4. Poiché $f$ è l'arco di costo massimo in $C$, $c_e \leq c_f$, quindi $c(T') \leq c(T^*)$.
5. Essendo $T^*$ un MST, $c(T') = c(T^*)$: $T'$ è un MST e non contiene $f$. $\square$

> [!question] Domanda tipica d'esame — Arco più leggero di un ciclo non è garantito
> **D:** *(Vero o Falso)* «Sia C un ciclo di G ed e l'arco più leggero di C. Allora esiste sempre un MST di G che contiene e.» *(chiesto il 28/09/2022)*
> **R:** Falsa: a differenza della cut property (che garantisce l'inclusione del minimo di un taglio), non esiste una proprietà simmetrica per il minimo di un ciclo. Un arco leggero interno a un ciclo può comunque essere escluso da ogni MST se esiste, per il taglio che separa i suoi estremi, un percorso alternativo esterno al ciclo di costo complessivo ancora minore: l'esclusione è garantita dalla cut property applicata a quel taglio, non contraddetta dalla cycle property (che riguarda il massimo, non il minimo, del ciclo).

> [!question] Domanda tipica d'esame — Caratterizzazione degli alberi non ottimi
> **D:** *(Vero o Falso)* «Se T non è un MST di G allora esiste un arco e ∈ T e un arco f ∉ T tale che e è l'arco più pesante del ciclo che si forma quando si aggiunge f a T.» *(chiesto il 13/06/2024)*
> **R:** Vera: è la contronominale della cycle property applicata a $T$. Se $T$ non è minimo, esiste un arco $e \in T$ scambiabile con un arco $f \notin T$ per ottenere un albero di costo minore o uguale: aggiungendo $f$ a $T$ si crea un ciclo, e $e$ ne è l'arco di peso massimo (altrimenti lo scambio non ridurrebbe il costo). È l'argomento di scambio alla base della dimostrazione di ottimalità di Kruskal e Prim.

> [!question] Domanda tipica d'esame — Massimo di un ciclo vs massimo di tutti i cicli
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco non di T. Allora f è l'arco di peso massimo in tutti i cicli che lo contengono.» *(chiesto il 18/07/2025)*
> **R:** Falso: la cycle property garantisce che $f$ sia il massimo di *almeno un* ciclo (il ciclo fondamentale che si forma aggiungendo $f$ a $T$), non di *ogni* ciclo di $G$ che contiene $f$. In un grafo con più cicli passanti per $f$, questo può non essere il più pesante in un ciclo diverso da quello fondamentale rispetto a $T$.

> [!question] Domanda tipica d'esame — Un arco dell'MST non è per forza il minimo di un ciclo
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia e un arco di T, allora l'arco e è l'arco più leggero di almeno un ciclo in G.» *(chiesto il 09/09/2025)*
> **R:** Falsa: se $e$ è un ponte (bridge) di $G$, cioè la sua rimozione disconnette il grafo, allora $e$ non appartiene ad alcun ciclo di $G$, quindi non può essere l'arco più leggero di nessun ciclo, pur essendo necessariamente parte di ogni spanning tree (MST incluso).

> [!question] Domanda tipica d'esame — Cut property e archi non minimi
> **D:** Enuncia la cut property e spiega come si usa per mostrare che un albero ricoprente $T$ non è minimo.
> **R:** La cut property afferma che l'arco di costo minimo che attraversa un qualsiasi taglio appartiene ad *almeno* un MST. Per usarla al contrario serve **il taglio giusto**: sia $T$ un albero ricoprente e $f \in T$; rimuovendo $f$ da $T$ l'albero si spezza in due componenti, che definiscono un taglio $(S, V \setminus S)$ di cui $f$ è l'**unico** arco di $T$ che lo attraversa. Se esiste un arco $e \notin T$ che attraversa *quello stesso* taglio con $c_e < c_f$, allora $T$ non è minimo: $T' = T \cup \{e\} \setminus \{f\}$ è ancora un albero ricoprente e costa strettamente meno.
> **Attenzione al verso dell'implicazione**: non vale che «se $f$ non è il minimo di un taglio *qualsiasi*, allora esiste un MST senza $f$». Controesempio: $A-B = 5$ come unico arco incidente ad $A$, più il triangolo $B-C = 1$, $C-D = 1$, $B-D = 1$. Nel taglio $S = \{A, D\}$ il cutset è $\{A\text-B = 5,\ C\text-D = 1,\ B\text-D = 1\}$ e $A\text-B$ non è il minimo, eppure è un **ponte**: sta in ogni albero ricoprente, quindi in ogni MST. Il taglio va scelto come sopra, indotto da $T$, non arbitrariamente.
## Algoritmo di Kruskal
L'algoritmo di **Kruskal** (1956) parte da $T = \emptyset$ e aggiunge gli archi uno alla volta in ordine crescente di costo, saltando quelli che formerebbero un ciclo.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Kruskal($G = (V, E, c)$) — restituisce l'MST $T$}
\begin{algorithmic}
\State $T \gets \emptyset$
\ForAll{vertice $v \in V$}
  \State \Call{UF.makeset}{$v$}
\EndFor
\State ordina gli archi $E$ in ordine crescente di costo
\ForAll{arco $(x, y) \in E$ in ordine crescente di costo}
  \State $T_x \gets$ \Call{UF.find}{$x$}
  \State $T_y \gets$ \Call{UF.find}{$y$}
  \If{$T_x \neq T_y$}
    \State \Call{UF.union}{$T_x, T_y$}
    \State aggiungi $(x, y)$ a $T$
  \EndIf
\EndFor
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

La struttura dati [[02 - Union-Find]] mantiene le **[[08 - Grafi e Visite|componenti connesse]]** di $T$ durante l'esecuzione:
- `makeset(v)`: inizializza la componente $\{v\}$.
- `find(x)`: restituisce il rappresentante della componente di $x$.
- `union(Tx, Ty)`: fonde le due componenti.

Il controllo `Tx ≠ Ty` rileva se $x$ e $y$ sono già nella stessa componente (aggiungere l'arco creerebbe un ciclo).
### Esempio di esecuzione
```
Grafo di esempio:
         B               F
    7        21      6

A       14       C  1              E
                           9
    30       10
         D               G

Archi ordinati per costo: (C,E,1), (E,F,6), (A,B,7), (E,G,9), (C,D,10),
                          (A,C,14), (B,C,21), (A,D,30)

Passo 1: (C,E,1)  → {C}∩{E} = ∅ → aggiungi. T={(C,E)}
Passo 2: (E,F,6)  → {C,E}∩{F} = ∅ → aggiungi. T={(C,E),(E,F)}
Passo 3: (A,B,7)  → {A}∩{B} = ∅ → aggiungi. T+={(A,B)}
Passo 4: (E,G,9)  → {C,E,F}∩{G} = ∅ → aggiungi. T+={(E,G)}
Passo 5: (C,D,10) → {C,E,F,G}∩{D} = ∅ → aggiungi. T+={(C,D)}
Passo 6: (A,C,14) → {A,B}∩{C,D,E,F,G} = ∅ → aggiungi (unisce le due componenti).
Passo 7: (B,C,21) → find(B)=find(C) → CICLO, skip.
Passo 8: (A,D,30) → find(A)=find(D) → CICLO, skip.
MST finale: {(C,E),(E,F),(A,B),(E,G),(C,D),(A,C)}, costo = 1+6+7+9+10+14 = 47
```

> [!question] Domanda tipica d'esame — Il numero di componenti dopo k archi non è garantito n−k
> **D:** *(Vero o Falso)* «Dopo aver processato il terzo arco di peso minimo di G, l'algoritmo ha calcolato una soluzione parziale che è una foresta di esattamente n − 3 componenti connesse;» *(chiesto il 19/02/2024)*
> **R:** Falsa: il numero di componenti diminuisce di uno solo quando l'arco processato viene effettivamente aggiunto a $T$ (cioè collega due componenti distinte). Se il terzo arco in ordine di peso chiude un ciclo (perché i suoi estremi sono già nella stessa componente dopo i primi due), viene scartato e il numero di componenti resta $n-2$, non $n-3$: l'uguaglianza $n-k$ dopo $k$ archi processati vale solo se tutti e $k$ sono stati effettivamente accettati.
### Correttezza
La correttezza di Kruskal segue direttamente dalla **cut property** e dalla **cycle property**:
- Quando l'algoritmo **aggiunge** l'arco $(x, y)$: le componenti di $x$ e $y$ sono distinte; sia $S$ la componente di $x$. Tutti gli archi già esaminati (e saltati) avevano costo $\leq c_{xy}$. Dunque $(x, y)$ è l'arco di costo minimo che attraversa il taglio tra $S$ e $V \setminus S$: per la **cut property** appartiene ad un MST.
- Quando l'algoritmo **rifiuta** l'arco $(x, y)$: $x$ e $y$ sono già connessi in $T$, quindi $(x, y)$ forma un ciclo con il cammino esistente. Poiché gli archi sono esaminati in ordine crescente, $(x, y)$ è l'arco di costo massimo in quel ciclo: per la **cycle property** non appartiene ad alcun MST (se i pesi sono distinti).

> [!question] Domanda tipica d'esame — Perché un arco viene scartato
> **D:** *(Vero o Falso)* «Quando l'algoritmo processa un generico arco e e decide di non aggiungerlo alla soluzione, vuol dire non solo che l'arco e forma un ciclo con gli archi già aggiunti, ma che è anche l'arco più pesante di quel ciclo;» *(chiesto il 19/02/2024)*
> **R:** Vera: è esattamente l'argomento della sezione Correttezza qui sopra. Esaminando gli archi in ordine crescente di peso, quando si scarta $e=(x,y)$ perché $x$ e $y$ sono già connessi in $T$, l'arco chiude un ciclo con il cammino già presente; poiché tutti gli archi già aggiunti (quindi anche quelli del ciclo) hanno peso $\leq c_e$, $e$ è necessariamente l'arco di peso massimo di quel ciclo, e per la cycle property può essere scartato senza compromettere l'ottimalità.

> [!question] Domanda tipica d'esame — L'MST può contenere l'arco più pesante di G
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Kruskal non contiene mai l'arco di peso massimo di G.» *(chiesto il 24/09/2024)*
> **R:** Falsa: controesempio banale, se $G$ è già un albero (connesso con esattamente $n-1$ archi), l'unico spanning tree possibile è $G$ stesso, che è quindi anche l'MST e contiene necessariamente anche l'arco di peso massimo. Più in generale, se l'arco di peso massimo è un ponte, deve comparire in ogni spanning tree.
### Complessità
| Operazione | Costo |
|---|---|
| Ordinamento degli archi | $O(m \log m) = O(m \log n)$ |
| $n$ `makeset` | $O(n)$ |
| $n-1$ `union` | dipende da UF |
| $2m$ `find` | dipende da UF |
| **Totale con QuickFind + union by size** | $O(m \log n + m + n \log n) = O(m \log n)$ |
| **Totale con QuickUnion + union by size** | $O(m \log n + m \log n + n) = O(m \log n)$ |
| **Totale complessivo** | $\mathbf{O(m \log n)}$ |

Nota: $\log m = O(\log n^2) = O(\log n)$ poiché $m \leq \binom{n}{2}$, quindi $O(m \log m) = O(m \log n)$. Per i dettagli sulle implementazioni di Union-Find e le loro complessità, si veda [[02 - Union-Find]].

> [!question] Domanda tipica d'esame — Il numero di archi non basta per la complessità
> **D:** *(Vero o Falso)* «Se il numero di archi in G è Θ(n), allora l'algoritmo di Kruskal ha complessità O(n).» *(chiesto il 18/07/2022)*
> **R:** Falsa: come mostrato nella tabella qui sopra, il costo totale di Kruskal è dominato dall'ordinamento degli archi, $O(m \log m) = O(m \log n)$. Con $m = \Theta(n)$ si ottiene $O(n \log n)$, non $O(n)$: il fattore logaritmico dell'ordinamento non scompare.

> [!question] Domanda tipica d'esame — Θ(n√n) archi non rende Kruskal lineare
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Kruskal che implementa la Union-Find con la QuickFind con euristica union by size ha complessità lineare, ovvero Θ(n√n).» *(chiesto il 09/09/2025)*
> **R:** Falsa: con $m = \Theta(n\sqrt{n})$, la complessità di Kruskal resta $O(m \log n) = \Theta(n \sqrt{n} \log n)$, dominata dall'ordinamento degli archi; il fattore $\log n$ non si elimina, indipendentemente dall'euristica scelta per la Union-Find (che riguarda solo il costo delle operazioni `union`/`find`, non l'ordinamento).

> [!question] Domanda tipica d'esame — Su grafi densi l'euristica union-by-size è ininfluente
> **D:** *(Vero o Falso)* «Se G è completo allora l'algoritmo di Kruskal ha la stessa complessità asintotica sia se usa per la struttura Union-Find la QuickFind con o senza euristica union by size.» *(chiesto il 18/07/2025)*
> **R:** Vero: se $G$ è completo, $m = \Theta(n^2)$, quindi il costo dell'ordinamento $O(m \log n) = O(n^2 \log n)$ domina già asintoticamente il costo delle operazioni di Union-Find, che è al più $O(m) = O(n^2)$ senza euristica e $O(m + n\log n)$ con essa: in entrambi i casi il totale resta $\Theta(n^2 \log n)$, dominato dall'ordinamento.
## Algoritmo di Prim
L'algoritmo di **Prim** (Jarník 1930, Dijkstra 1957, Prim 1959) costruisce l'MST partendo da un nodo sorgente $s$ e crescendo l'albero un arco alla volta, scegliendo sempre l'arco di costo minimo che ha esattamente un estremo nell'albero corrente.
### Idea e correttezza
Ad ogni passo si ha un insieme $S$ di nodi già esplorati (inizialmente $S = \{s\}$). Si aggiunge il **nodo più economico** raggiungibile da $S$, cioè il nodo $v \notin S$ per cui esiste un arco $(u, v)$ con $u \in S$ e $c_{uv}$ minimo tra tutti gli archi del cutset.

**Correttezza:** La cut property applicata all'insieme $S$ garantisce che l'arco scelto a ogni passo appartiene ad almeno un MST. Poiché si usa la cut property esattamente $n-1$ volte (una per ogni arco aggiunto), l'albero finale è un MST.

> [!question] Domanda tipica d'esame — Cut property e correttezza di Prim
> **D:** «3. Si discuta in modo conciso e preciso come è possibile usare la proprietà del taglio per dimostrare la correttezza dell'algoritmo di Prim.» *(chiesto il 26/06/2025)*
> **R:** Ad ogni passo, l'insieme $S$ dei nodi già esplorati definisce un taglio $(S, V\setminus S)$. Prim seleziona sempre l'arco di costo minimo del cutset di $S$ (l'arco che collega $S$ al resto del grafo a minor costo): per la cut property, tale arco appartiene sempre ad almeno un MST di $G$ che estende le scelte già fatte. Poiché questo argomento vale a ogni passo, per ciascuno degli $n-1$ archi aggiunti, l'albero finale, avendo $n-1$ archi tutti giustificati dalla cut property, è esso stesso un MST.
### Implementazione con coda con priorità
L'implementazione naïve (per $n-1$ volte, scansione lineare di tutti gli archi) costa $O(nm)$. L'implementazione efficiente usa una [[07 - Code con Priorità e Heap|coda con priorità]] (**min-heap**):

Per ogni nodo non ancora esplorato $v$, si mantiene la chiave $a[v]$ = costo del **miglior arco** che collega $v$ a un nodo già in $S$ ($+\infty$ se nessun tale arco esiste).
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Prim($G, s$) — restituisce l'MST $T$ radicato in $s$}
\begin{algorithmic}
\ForAll{vertice $v \in V$}
  \State $a[v] \gets +\infty$
\EndFor
\State $a[s] \gets 0$
\State $Q \gets$ nuova coda con priorità (min-heap)
\ForAll{vertice $v \in V$}
  \State \Call{Q.insert}{$v, a[v]$}
\EndFor
\State $S \gets \emptyset$
\State $T \gets$ albero con radice $s$ (senza archi)
\While{$Q$ non è vuota}
  \State $u \gets$ \Call{Q.deleteMin}{}
  \State $S \gets S \cup \{u\}$
  \ForAll{arco $e = (u, v)$ incidente a $u$}
    \If{$v \notin S$ e $c_e < a[v]$}
      \State rendi $u$ genitore di $v$ in $T$
      \State \Call{Q.decreaseKey}{$v, c_e$}
      \State $a[v] \gets c_e$
    \EndIf
  \EndFor
\EndWhile
\State \Return $T$
\end{algorithmic}
\end{algorithm}
```

> [!info] Analogia con Dijkstra
> La struttura di Prim è molto simile a quella di [[10 - Cammini Minimi e Dijkstra]]: entrambi usano una coda con priorità e un'operazione `decreaseKey`. La differenza chiave è la **chiave usata**. In Dijkstra la chiave di $v$ è la **distanza totale** da $s$ (costo del cammino da $s$ a $v$); in Prim la chiave di $v$ è il **costo del singolo arco** che collega $v$ all'albero corrente. Prim non cerca il cammino più corto da $s$, ma l'arco di attacco più economico.
### Esempio di esecuzione
```
Grafo (stesso esempio):
         B               F
    7        21      6

s=A     14       C  1         E
                           9
    30       10
         D               G

Passo 1: S={A}. Archi candidati: (A,B,7),(A,C,14),(A,D,30).
         Minimo: (A,B,7). Aggiungi B. T={(A,B)}.
Passo 2: S={A,B}. Candidati: (A,C,14),(A,D,30),(B,C,21).
         Minimo: (A,C,14). Aggiungi C. T={(A,B),(A,C)}.
Passo 3: S={A,B,C}. Candidati: (A,D,30),(C,D,10),(C,E,1).
         Minimo: (C,E,1). Aggiungi E. T+={(C,E)}.
Passo 4: S={A,B,C,E}. Candidati: (A,D,30),(C,D,10),(E,F,6),(E,G,9).
         Minimo: (E,F,6). Aggiungi F. T+={(E,F)}.
Passo 5: S={A,B,C,E,F}. Candidati: (A,D,30),(C,D,10),(E,G,9).
         Minimo: (E,G,9). Aggiungi G. T+={(E,G)}.
Passo 6: S={A,B,C,E,F,G}. Candidati: (A,D,30),(C,D,10).
         Minimo: (C,D,10). Aggiungi D.
MST = {(A,B,7),(A,C,14),(C,E,1),(E,F,6),(E,G,9),(C,D,10)}, costo=47
```

> [!warning] Chiave vs distanza: non confondere Prim con Dijkstra
> In Prim la chiave $a[v]$ rappresenta il costo del **miglior arco singolo** che connette $v$ all'albero — non il costo cumulativo del cammino da $s$ a $v$. Usare la distanza cumulativa al posto della chiave dell'arco produce Dijkstra (cammini minimi), non Prim (MST).

> [!question] Domanda tipica d'esame — Prim su grafo non pesato non è BFS
> **D:** *(Vero o Falso)* «Quando il grafo è non pesato, l'algoritmo di Prim restituisce un albero dei cammini minimi radicato sul nodo sorgente su cui è chiamato.» *(chiesto il 13/06/2024)*
> **R:** Falsa: come chiarito nel box qui sopra, Prim usa come chiave il costo del singolo arco di attacco, non la distanza cumulativa dalla sorgente. Anche con pesi tutti uguali a 1 ogni spanning tree è un MST (i costi sono tutti uguali), ma le scelte di Prim tra archi di pari peso sono arbitrarie e non seguono necessariamente l'ordine per livelli di una BFS: l'albero prodotto può quindi non coincidere con l'albero dei cammini minimi.

> [!question] Domanda tipica d'esame — MST e albero dei cammini minimi restano problemi diversi
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Prim invocato su una sorgente s è anche un albero dei cammini minimi di G rispetto alla stessa sorgente s.» *(chiesto il 24/09/2024)*
> **R:** Falsa: in generale i due problemi ottimizzano criteri diversi (costo totale dell'albero per Prim, distanza dalla sorgente per l'albero dei cammini minimi) e producono alberi diversi. Un nodo lontano da $s$ ma raggiungibile con un arco di attacco molto economico viene incluso presto da Prim, anche se il suo cammino minimo dalla sorgente è più lungo di quanto l'albero di Prim suggerisca.
### Complessità
Le operazioni sulla coda con priorità determinano la complessità totale. Si eseguono $n$ insert, $n$ deleteMin, e al più $m$ decreaseKey:

| Struttura per la coda | Insert | DeleteMin | DecreaseKey | Totale Prim |
|---|---|---|---|---|
| Scansione lineare naïve (senza PQ) | — | $O(m)$ per step | — | $O(mn)$ |
| **Array non ordinato** | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| **Heap binario** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m \log n)$ |
| **[[07 - Code con Priorità e Heap\|Heap di Fibonacci]]** | $O(1)$ | $O(\log n)$ | $O(1)$ ammort. | $O(m + n \log n)$ |

Il calcolo con heap binario: $n \cdot O(\log n) + n \cdot O(\log n) + m \cdot O(\log n) = O(m \log n)$.
Il calcolo con heap di Fibonacci: $n \cdot O(1) + n \cdot O(\log n) + m \cdot O(1) = O(m + n \log n)$.

> [!question] Domanda tipica d'esame — Θ(n√n) archi e heap di Fibonacci
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Prim che implementa la coda con priorità attraverso un heap di Fibonacci ha complessità lineare, ovvero Θ(n√n).» *(chiesto il 23/09/2025)*
> **R:** Vero: con l'heap di Fibonacci, Prim costa $O(m + n \log n)$. Con $m = \Theta(n\sqrt{n})$ si ha $n \log n = o(n \sqrt n)$ (il fattore $\sqrt n$ domina $\log n$), quindi il totale è $\Theta(n\sqrt n + n\log n) = \Theta(n\sqrt n) = \Theta(m)$: la complessità è effettivamente lineare nel numero di archi — a differenza di Kruskal, dove il fattore $\log n$ dell'ordinamento non si elimina nello stesso scenario (cfr. la domanda analoga nella sezione Kruskal).

> [!question] Domanda tipica d'esame — Bound in funzione del grado massimo
> **D:** *(Vero o Falso)* «Se il grado massimo in G è δ allora l'algoritmo di Prim implementato con heap binario ha complessità O(δ n log(n)) nel caso peggiore» *(chiesto il 27/09/2023)*
> **R:** Vera: con heap binario, Prim costa $O(m \log n)$. Se il grado massimo è $\delta$, allora $m \leq \delta n / 2 = O(\delta n)$ (ogni nodo contribuisce al più $\delta$ archi, ognuno contato due volte), quindi $O(m \log n) = O(\delta n \log n)$: è un bound più fine di $O(m\log n)$ generico, utile su grafi con grado limitato.
## Riepilogo e confronto degli algoritmi
| Algoritmo | Struttura dati | Complessità | Note |
|---|---|---|---|
| Kruskal | [[02 - Union-Find]] (Union by size) | $O(m \log n)$ | Ottimo su grafi sparsi; ordinamento domina |
| Prim (naïve) | Scansione lineare, senza PQ | $O(mn)$ | Semplice ma inefficiente |
| Prim (array) | Array non ordinato | $O(n^2)$ | Buono su grafi densi ($m=\Theta(n^2)$) |
| Prim (heap binario) | Min-heap binario | $O(m \log n)$ | Bilanciato; buono su grafi sparsi |
| Prim (Fibonacci) | [[07 - Code con Priorità e Heap\|Heap di Fibonacci]] | $O(m + n \log n)$ | Ottimale su grafi densi |

> [!info] Confronto Kruskal vs Prim
> Su grafi **sparsi** ($m = O(n)$) sia Kruskal che Prim con heap binario danno $O(n \log n)$; la scelta è indifferente. Su grafi **densi** ($m = \Theta(n^2)$), Kruskal richiede $O(n^2 \log n)$ (dominato dall'ordinamento), mentre Prim con array non ordinato dà $O(n^2)$ e Prim con heap di Fibonacci dà $O(n^2)$: in questo caso Prim è preferibile.
> Nota teorica: esistono algoritmi asintoticamente migliori — $O(m \log \log n)$ (Cheriton-Tarjan 1976, Yao 1975), $O(m \cdot \alpha(m,n))$ (Fredman-Tarjan 1987), $O(m)$ randomizzato (Karger-Klein-Tarjan 1995) — ma Kruskal e Prim rimangono gli algoritmi standard per il corso.

> [!question] Domanda tipica d'esame — Caso speciale: pesi tutti uguali
> **D:** «Quale algoritmo useresti per calcolare un MST di G e qual è la sua complessità asintotica nel caso peggiore se G ha tutti gli archi dello stesso peso? [risposta in 1 riga]» *(chiesto il 27/09/2023)*
> **R:** Basta una BFS o una DFS a partire da un vertice qualsiasi, con complessità $O(n+m)$: se tutti gli archi hanno lo stesso peso, ogni spanning tree ha lo stesso costo totale ($n-1$ volte il peso comune), quindi ogni spanning tree è automaticamente un MST e non serve alcuna logica greedy basata sui pesi — né Kruskal né Prim sono necessari.

> [!question] Domanda tipica d'esame — Kruskal: descrizione e correttezza
> **D:** Descrivi l'algoritmo di Kruskal, spiega perché è corretto e calcolane la complessità.
> **R:** Kruskal ordina gli archi in senso crescente e li aggiunge a $T$ uno a uno, saltando quelli che formano un ciclo (rilevato tramite Union-Find). La correttezza si basa sulla cut property: quando si aggiunge $(x,y)$, la componente di $x$ forma il taglio $S$; poiché gli archi sono esaminati in ordine crescente, $(x,y)$ è il minimo che attraversa quel taglio, quindi appartiene a un MST. Complessità: $O(m \log n)$ — l'ordinamento domina, le operazioni Union-Find con union by size costano $O(m \log n)$ nel totale.

> [!question] Domanda tipica d'esame — Differenza tra Prim e Dijkstra
> **D:** Qual è la differenza tra l'algoritmo di Prim e l'algoritmo di Dijkstra?
> **R:** Entrambi usano una coda con priorità e `decreaseKey`. La differenza è nella **chiave**: Dijkstra usa la distanza cumulativa da $s$ (per trovare i cammini minimi); Prim usa il costo del singolo arco di attacco (per trovare l'MST). Prim non produce un albero dei cammini minimi: un nodo distante da $s$ ma connesso all'albero tramite un arco molto economico viene incluso prima di nodi vicini ma raggiungibili solo con archi costosi.
## Applicazione: Clustering di massima spaziatura
Un'applicazione diretta di Kruskal è il **clustering gerarchico per single-linkage**.
> [!quote] Definizione — k-clustering di massima spaziatura
> Dato un insieme $U$ di $n$ oggetti con una funzione distanza $d$ (non negativa, simmetrica, con $d(p_i, p_j) = 0 \Leftrightarrow p_i = p_j$), un **$k$-clustering** è una partizione di $U$ in $k$ gruppi non vuoti. La **spaziatura** (*spacing*) è la minima distanza tra oggetti in cluster diversi. Il problema è trovare il $k$-clustering di **massima spaziatura**.

**Algoritmo (Single-linkage $k$-clustering):** si esegue Kruskal su un grafo completo con pesi pari alle distanze tra oggetti, fermandosi quando si raggiungono esattamente $k$ componenti connesse. Equivalentemente: si costruisce l'MST completo e si eliminano i $k-1$ archi più costosi.

> [!quote] Teorema — Ottimalità del k-clustering per single-linkage
> Il clustering $\mathcal{C}^*$ ottenuto eliminando i $k-1$ archi più costosi dall'MST è un $k$-clustering di **massima spaziatura**.

**Dimostrazione.** Sia $d^*$ la lunghezza del $(k-1)$-esimo arco più costoso dell'MST (cioè la spaziatura di $\mathcal{C}^*$). Sia $\mathcal{C}$ un qualsiasi altro $k$-clustering. Poiché $\mathcal{C}^* \neq \mathcal{C}$, esistono $p_i, p_j$ nello stesso cluster di $\mathcal{C}^*$ (diciamo $C^*_r$) ma in cluster diversi di $\mathcal{C}$. Il cammino da $p_i$ a $p_j$ in $C^*_r$ (nell'MST) attraversa un arco che separa i due cluster di $\mathcal{C}$; tutti gli archi del cammino hanno lunghezza $\leq d^*$ (Kruskal li ha scelti prima del $(k-1)$-esimo taglio). La spaziatura di $\mathcal{C}$ è quindi $\leq d^*$: $\mathcal{C}^*$ ha spaziatura maggiore o uguale a qualsiasi altro $k$-clustering. $\square$

> [!info] Clustering gerarchico
> Eseguendo Kruskal fino alla fine (senza fermarsi a $k$ componenti) si ottiene implicitamente un **clustering gerarchico**: per ogni $k = n, n-1, \ldots, 1$, i cluster sono le componenti connesse dopo aver eliminato i $k-1$ archi più costosi dall'MST. Questo produce un **dendrogramma** — una struttura ad albero che mostra come i cluster si fondono al crescere di $k$.

> [!question] Domanda tipica d'esame — MST e clustering di massima spaziatura
> **D:** Come si usa l'MST per trovare il clustering di massima spaziatura? Perché funziona?
> **R:** Si calcola l'MST del grafo completo sugli oggetti (con pesi = distanze) e si eliminano i $k-1$ archi più costosi. Le $k$ componenti connesse risultanti sono il clustering ottimale. Funziona perché la spaziatura del clustering è la lunghezza del $(k-1)$-esimo arco più costoso dell'MST; qualsiasi altro clustering deve avere due oggetti in cluster diversi collegati da un percorso nell'MST i cui archi hanno tutti lunghezza $\leq$ quella spaziatura, quindi la spaziatura di qualsiasi altro clustering non può superare quella del clustering MST.
