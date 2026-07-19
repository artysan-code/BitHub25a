---
tags:
  - algoritmi
  - mst
slide: "3"
capitolo: "Kleinberg-Tardos cap. 4"
---
# Minimum Spanning Tree
Il **Minimum Spanning Tree** (MST), o **albero ricoprente minimo**, è uno dei problemi fondamentali su grafi pesati: dato un grafo connesso non orientato con pesi reali sugli archi, si cerca l'insieme di archi che connette tutti i nodi con costo totale minimo. Questa nota tratta le definizioni fondamentali, le due proprietà strutturali con le relative dimostrazioni, l'algoritmo di Kruskal (basato su [[02 - Union-Find]]) e l'algoritmo di Prim (basato su [[07 - Code con Priorità e Heap]]). Un'applicazione al clustering gerarchico conclude la nota.
## L'idea: perché qui il greedy funziona
Conviene aprire con la domanda che collega questa nota alle precedenti. Nel [[04 - Programmazione Dinamica I (Weighted Independent Set)#Approccio greedy|Weighted Independent Set]] il greedy **fallisce**, e abbiamo visto che il difetto è strutturale: prendere un nodo pesante ne esclude altri di valore complessivamente maggiore, e nessun criterio locale può accorgersene. Nell'MST, invece, il greedy **funziona** — e non per fortuna: ne esistono addirittura *tre* varianti diverse, tutte corrette.

La differenza sta in una proprietà del problema. Nell'MST vale un **argomento di scambio**: presa una soluzione ottima qualsiasi che *non* contenga l'arco scelto dal greedy, si può sempre modificarla scambiando quell'arco con un altro, **senza peggiorarne il costo**. La scelta greedy non pregiudica dunque nulla — al più si arriva a un ottimo diverso, ma di pari costo. Nel WIS uno scambio del genere non esiste, e infatti lì il greedy perde.

Le due proprietà che formalizzano lo scambio sono il cuore di tutta la nota:
- la **cut property** dice quali archi si possono **includere** con sicurezza (il più leggero che attraversa un taglio);
- la **cycle property** dice quali archi si possono **scartare** con sicurezza (il più pesante di un ciclo).

> [!info] Tre algoritmi, due proprietà
> Kruskal, Prim e Reverse-Delete non sono tre argomenti da imparare separatamente: sono tre modi diversi di applicare le stesse due proprietà.
> - **Kruskal** e **Prim** costruiscono l'albero *aggiungendo* archi, e la loro correttezza è un corollario della **cut property**;
> - **Reverse-Delete** parte dal grafo intero e *rimuove* archi, e la sua correttezza discende dalla **cycle property**;
> - nella dimostrazione di Kruskal servono **entrambe**: la cut property giustifica gli archi accettati, la cycle property quelli scartati.
>
> Se in sede d'esame ricordi le due proprietà e sai dimostrarle, la correttezza dei tre algoritmi si ricostruisce; il viceversa non vale. È il motivo per cui le domande su cut e cycle property sono le più frequenti dell'intero modulo.
## Definizioni
> [!quote] Definizione — Minimum Spanning Tree
> Dato un grafo connesso non orientato $G = (V, E)$ con pesi reali $c_e$ sugli archi, un **albero ricoprente** (*spanning tree*) è un sottoinsieme $T \subseteq E$ tale che $T$ è un albero che connette tutti i vertici di $G$. Essendo un albero su $n$ vertici, ha **esattamente $|T| = n-1$ archi**. Un **albero ricoprente minimo** (MST) è uno spanning tree che minimizza il costo totale:
> $$c(T) = \sum_{e \in T} c_e$$

Il prof formalizza il problema nella terna standard **input / soluzione ammissibile / misura**, la stessa usata per tutti i problemi di ottimizzazione del modulo. È il formato da riprodurre quando la traccia chiede «si definisca formalmente il problema».

> [!quote] Definizione — Il problema MST come problema di ottimizzazione
> - **Input**: un grafo non orientato, connesso e pesato $G = (V, E)$ con pesi reali $c_e$ sugli archi.
> - **Soluzione ammissibile**: uno spanning tree $T$ di $G$, cioè un albero $T = (V, F)$ con $F \subseteq E$ che raggiunge tutti i vertici di $G$.
> - **Misura (da minimizzare)**: il peso (o costo) di $T$, cioè $c(T) = \sum_{e \in T} c_e$.

> [!question] Domanda tipica d'esame — Definizione formale del problema
> **D:** «1. Si definisca formalmente il problema.» *(Es. 2, prima domanda aperta — 26/06/2025; Es. 2, punto 1 — 02/02/2026)*
> **R:**
> **Definizione (formato del prof: input / soluzione ammissibile / misura).**
> - *Input*: un grafo non orientato, connesso e pesato $G = (V,E)$ con pesi reali $c_e$ sugli archi.
> - *Soluzione ammissibile*: uno spanning tree $T = (V,F)$ di $G$, con $F \subseteq E$, che raggiunge tutti i vertici di $G$.
> - *Misura da minimizzare*: $c(T) = \sum_{e \in T} c_e$.
>
> **Elementi della definizione.** Tre condizioni congiunte: (1) $T$ deve essere un albero (connesso, aciclico, esattamente $n-1$ archi); (2) $T$ deve coprire tutti i vertici di $G$ (spanning); (3) tra tutti gli spanning tree di $G$, $T$ minimizza $c(T)$.
>
> **Osservazione.** La minimalità è **relativa**: si confronta $T$ con tutti gli altri spanning tree di $G$, non con sottografi arbitrari — un sottoinsieme con meno archi non è ammissibile se non copre tutti i vertici.

> [!question] Domanda tipica d'esame — Bound sul costo con pesi in {1, 2}
> **D:** *(Vero o Falso)* «Si assuma che per ogni arco e vale w(e) ∈ {1, 2}, e sia T un MST di G. Allora ogni MST di G costa almeno n − 1 e al più 2n − 2.» *(Es. 1, V/F n. 2 — 23/09/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Ogni albero ricoprente di un grafo connesso a $n$ nodi ha esattamente $n-1$ archi — pura combinatoria, non serve ottimalità. Con pesi in $\{1,2\}$, la somma di $n-1$ termini soddisfa $(n-1)\cdot 1 \leq \text{costo} \leq (n-1)\cdot 2 = 2n-2$, bound raggiunti se tutti gli archi pesano rispettivamente 1 o 2.
>
> **Osservazione.** L'ipotesi "$T$ è un MST" è ridondante: il bound vale per qualunque spanning tree.

> [!quote] Teorema — Numero di spanning tree (Cayley)
> Il grafo completo $K_n$ ha esattamente $n^{n-2}$ spanning tree distinti.

Il Teorema di Cayley mostra che il numero di spanning tree cresce esponenzialmente in $n$: la ricerca per forza bruta è impraticabile anche per grafi piccoli.
### Unicità dell'MST
L'MST **non è unico** in generale: se esistono archi con lo stesso peso, possono esistere più MST di costo uguale.

> [!quote] Proprietà — Unicità dell'MST
> Se tutti i pesi degli archi di $G$ sono **distinti**, allora l'MST è **unico**.

Sulla slide questa proprietà è lasciata come **«exercise: prove it»**. La dimostrazione è un argomento di scambio sulla differenza simmetrica, ed è bene saperla produrre: è il lemma che giustifica tutte le domande del tipo «Kruskal e Prim calcolano lo stesso albero?».

**Dimostrazione (per assurdo).** Si supponga che esistano due MST distinti $T_1 \neq T_2$.
1. La differenza simmetrica $T_1 \triangle T_2$ è non vuota. Sia $e$ l'arco di peso **minimo** in $T_1 \triangle T_2$: essendo i pesi distinti, $e$ è univocamente determinato. Senza perdita di generalità $e \in T_1 \setminus T_2$.
2. Aggiungendo $e$ a $T_2$ si crea un ciclo $C$. Non tutti gli archi di $C$ diversi da $e$ possono appartenere a $T_1$: altrimenti $C \subseteq T_1$, e $T_1$ conterrebbe un ciclo, contro il fatto che è un albero.
3. Esiste dunque $f \in C$, $f \neq e$, con $f \in T_2 \setminus T_1$, quindi $f \in T_1 \triangle T_2$.
4. Per la minimalità di $e$ nella differenza simmetrica e la distinzione dei pesi, $w(f) > w(e)$.
5. L'albero $T_2 \cup \{e\} \setminus \{f\}$ è ancora uno spanning tree e pesa $w(T_2) + w(e) - w(f) < w(T_2)$: contraddice la minimalità di $T_2$. $\square$

> [!warning] L'ipotesi «pesi distinti» serve nel passo 4, non prima
> Con pesi ripetuti il passo 1 fallisce (il minimo della differenza simmetrica può non essere unico) e soprattutto il passo 4 dà solo $w(f) \geq w(e)$, da cui $w(T_2 \cup \{e\} \setminus \{f\}) \leq w(T_2)$: si ottiene un **altro MST di pari costo**, non una contraddizione. È esattamente il modo in cui nascono gli MST multipli.

Pesi distinti è condizione **sufficiente ma non necessaria**: esistono grafi con pesi ripetuti e MST comunque unico (il caso limite è $G$ già albero). La caratterizzazione esatta si ottiene guardando i **massimi dei cicli**, non i pesi in sé.

> [!quote] Criterio — Caratterizzazione dell'unicità
> Sia $T$ un MST di $G$. Allora $T$ è l'**unico** MST di $G$ se e solo se ogni arco $f \notin T$ è l'arco di peso **strettamente** massimo del proprio ciclo fondamentale (il ciclo che $f$ forma con $T$).

**Dimostrazione.** Se qualche $f \notin T$ pareggia con un arco $e$ del suo ciclo fondamentale, lo scambio $T \cup \{f\} \setminus \{e\}$ produce un secondo MST di pari costo, quindi $T$ non è unico. Viceversa, se ogni $f \notin T$ è massimo stretto del proprio ciclo, ogni scambio possibile aumenta strettamente il costo, e per l'argomento sulla differenza simmetrica visto sopra nessun altro MST può esistere. Questo criterio si applica anche quando i pesi si ripetono — è quello che serve, ad esempio, nella domanda sulla **griglia $N \times N$** più avanti, dove gli archi orizzontali sono tutti di peso $1$ eppure l'MST è unico.

> [!question] Domanda tipica d'esame — Unicità e pesi ripetuti
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G non sono distinti, sicuramente esistono due MST (distinti) di G.» *(chiesto il 18/07/2022)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Pesi ripetuti sono condizione **necessaria ma non sufficiente** per avere più MST distinti. Per il criterio di unicità (cfr. box **Criterio — Caratterizzazione dell'unicità**), servono due archi di pari peso che si trovino **sullo stesso ciclo** e che siano entrambi massimi di quel ciclo: solo allora lo scambio produce un secondo MST. Due archi di peso uguale in punti scorrelati del grafo non generano alcuna alternativa.
>
> **Controesempio.** Se $G$ non contiene cicli — cioè $G$ è già un albero — esiste un'unica soluzione ricoprente (l'intero $G$), indipendentemente da quanti pesi si ripetono: non ci sono cicli in cui operare uno scambio di archi.
>
> **Osservazione.** Il criterio corretto (cfr. box **Proprietà — Unicità dell'MST**) è: pesi tutti distinti $\Rightarrow$ MST unico. Ma la contronominale «pesi non distinti $\Rightarrow$ MST non unico» è **falsa**, perché l'implicazione originale non è un se-e-solo-se.

![[mst_unicita_tre_alberi.png]]
Il triangolo $A$-$B$-$C$ con tutti gli archi di peso 1 è l'esempio minimo: ognuno dei tre spanning tree possibili (evidenziati in blu) costa 2, quindi sono **tutti e tre MST**. È anche il controesempio da citare quando serve mostrare che l'MST non è unico.

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

![[mst_ciclo.png]]
Il ciclo $C$ è evidenziato in **rosso**. Nota che il grafo è lo stesso delle due figure che seguono: prima ci si mette sopra un ciclo, poi un taglio, poi si sovrappongono i due per vedere l'intersezione. Tenere lo stesso grafo campione per tutti e tre i passaggi è il motivo per cui questa sequenza di slide funziona — leggile in fila.
### Taglio e cutset
> [!quote] Definizione — Taglio e cutset
> Un **taglio** (*cut*) è un sottoinsieme di nodi $S \subseteq V$ (equivalentemente, una partizione di $V$ in $S$ e $V \setminus S$). Il **cutset** $D$ associato al taglio $S$ è il sottoinsieme di archi con **esattamente un** estremo in $S$:
> $$D = \{(u,v) \in E : u \in S,\ v \notin S\}$$

![[mst_taglio_cutset.png]]
Convenzione grafica delle slide, la stessa in tutte le figure di questa sezione: i **nodi neri** sono quelli in $S$ (qui $S=\{4,5,8\}$), i **nodi grigi** stanno in $V\setminus S$, e gli **archi blu** sono il cutset $D=\{5\text{-}6,\ 5\text{-}7,\ 3\text{-}4,\ 3\text{-}5,\ 7\text{-}8\}$. Nota che $S$ **non deve essere connesso**: qui il nodo 8 è staccato da 4 e 5, e il taglio resta perfettamente legittimo — è un punto su cui si sbaglia leggendo la definizione di fretta.
### Intersezione ciclo-cutset
> [!quote] Proprietà — Intersezione ciclo-cutset
> Un ciclo $C$ e un cutset $D$ si intersecano in un **numero pari** di archi (eventualmente zero).

Sulla slide questa proprietà è enunciata come *Claim* e dimostrata **«Pf. (by picture)»**: il prof si limita al disegno del ciclo che entra ed esce dalla macchia $S$. La dimostrazione che segue è la versione rigorosa dello stesso argomento — è quella da scrivere all'esame, perché il disegno da solo non è una prova.

**Dimostrazione.**
1. Si percorra il ciclo $C$ partendo da un suo nodo qualsiasi e tornando allo stesso nodo.
2. Ogni arco di $C$ che appartiene al cutset $D$ è, per definizione, un arco che ha un estremo in $S$ e l'altro fuori: percorrerlo significa **attraversare** il confine del taglio.
3. Gli archi di $C$ che non stanno in $D$ hanno entrambi gli estremi dallo stesso lato: percorrerli non cambia il lato in cui ci si trova.
4. Il percorso è **chiuso**: si termina nello stesso nodo da cui si è partiti, quindi dallo stesso lato del taglio.
5. Per tornare al punto di partenza, il numero di attraversamenti da $S$ verso $V\setminus S$ deve eguagliare quello in senso opposto: ogni "uscita" va compensata da un'"entrata".
6. Gli attraversamenti totali sono dunque $2k$ per qualche $k \geq 0$, ed essi sono esattamente gli archi di $C \cap D$. $\square$

![[mst_intersezione_ciclo_cutset.png]]
Stesso grafo delle due figure precedenti, con **ciclo in rosso** e **cutset in blu** sovrapposti: gli archi che appartengono a entrambi sono $3\text{-}4$ e $5\text{-}6$, cioè **due** — pari, come vuole la proprietà. Tieni a mente questa figura quando applichi le due property: l'arco $f$ da scambiare è sempre «l'altro arco rosso-e-blu».

> [!warning] Perché questa proprietà viene prima di tutto il resto
> Sembra un tecnicismo, ma è **il perno delle dimostrazioni di entrambe le proprietà**: è ciò che garantisce l'esistenza del *secondo* arco da usare nello scambio. Senza di essa, aggiungendo $e$ a $T^*$ si otterrebbe un ciclo, ma non si potrebbe affermare che in quel ciclo esiste un altro arco che attraversa lo stesso taglio — e lo scambio non si potrebbe fare. All'esame è quindi il lemma da citare, non da saltare.
## Cut property e Cycle property
Queste due proprietà sono il **cuore della correttezza** degli algoritmi greedy per l'MST.
### Cut property
> [!quote] Proprietà — Cut property (proprietà del taglio)
> Sia $S$ un qualsiasi sottoinsieme di nodi, e sia $e$ **un** arco di **costo minimo** con esattamente un estremo in $S$ (un arco di costo minimo del cutset di $S$). Allora esiste un MST che **contiene** $e$.

L'enunciato della slide dice *«let $e$ be a min cost edge»*, non *«the»*: se più archi del cutset condividono il peso minimo, la proprietà vale per **ciascuno** di essi preso singolarmente — ma su MST possibilmente diversi. Riprodurre l'articolo indeterminato è ciò che rende l'enunciato corretto anche in presenza di pareggi.

> [!question] Domanda tipica d'esame — Enunciato della cut property
> **D:** «2. Si enunci formalmente la proprietà del taglio (cut property).» *(Es. 2, seconda domanda aperta — 26/06/2025; Es. 2, punto 2 — 02/02/2026)*
> **R:**
> **Enunciato.** Dato un taglio $(S, V\setminus S)$ con $\emptyset \neq S \subset V$ (cfr. box **Definizione — Taglio e cutset**), sia $e$ **un** arco di costo minimo tra quelli con esattamente un estremo in $S$ (un minimo del cutset $D$). Allora esiste sempre almeno un MST di $G$ che contiene $e$.
>
> **Caso del minimo non stretto.** Se più archi del cutset condividono il peso minimo, la proprietà garantisce l'esistenza di *un* MST che contiene $e$, ma non che $e$ sia in *tutti* gli MST.
>
> **Caso del minimo stretto.** Se $e$ è l'**unico** arco di peso minimo del taglio, allora $e$ appartiene a *ogni* MST di $G$: nessun altro arco del cutset può sostituirlo senza aumentare il costo.

**Dimostrazione (argomento di scambio).**
Sia $T^*$ un MST qualsiasi. Se $e \in T^*$ non c'è nulla da dimostrare; supponiamo dunque che $e = (u,v)$, con $u \in S$ e $v \notin S$, **non** appartenga a $T^*$.
1. $T^*$ è uno spanning tree, quindi contiene un cammino da $u$ a $v$: aggiungendo $e$ a $T^*$ si crea un **ciclo** $C$ in $T^* \cup \{e\}$.
2. L'arco $e$ appartiene sia al ciclo $C$ sia al cutset $D$ di $S$ (ha esattamente un estremo in $S$): dunque $C \cap D \neq \emptyset$. Per la proprietà di intersezione ciclo-cutset $|C \cap D|$ è **pari**, quindi $|C \cap D| \geq 2$: **esiste** almeno un altro arco $f \in C \cap D$ con $f \neq e$.
3. Poiché $f \in C$ e $f \neq e$, si ha $f \in T^*$. Si ponga $T' = T^* \cup \{e\} \setminus \{f\}$: rimuovere un arco da un ciclo non disconnette, e il conteggio degli archi resta $n-1$, quindi $T'$ è **ancora uno spanning tree**.
4. $f$ appartiene al cutset $D$ ed $e$ è un arco di costo minimo di $D$: dunque $c_e \leq c_f$, da cui $c(T') = c(T^*) + c_e - c_f \leq c(T^*)$.
5. $T^*$ è un MST, quindi nessuno spanning tree costa meno: vale $c(T') = c(T^*)$. Perciò $T'$ è un MST e contiene $e$. $\square$

> [!warning] Non è una dimostrazione per assurdo
> La slide la etichetta *«Pf. (exchange argument)»*: si **costruisce** esplicitamente un MST che contiene $e$, partendo da uno qualsiasi che non lo contiene. Non si assume una tesi falsa per derivarne una contraddizione. Scriverla come prova per assurdo è un errore di impostazione che il prof segna, perché tradisce il punto: la cut property è un enunciato **esistenziale** ($\exists$ un MST con $e$) e lo scambio è precisamente il testimone che lo realizza.

![[mst_exchange_argument.png]]
Come leggerla: le due macchie grigie sono $S$ e $V\setminus S$; i segmenti pieni sono gli archi di $T^*$, l'MST di partenza. L'arco **tratteggiato $e$** è quello che la cut property vuole dentro, e non c'è. Aggiungendolo si chiude un ciclo, che riattraversa il taglio in **$f$**: lo scambio $T' = T^* \cup \{e\} \setminus \{f\}$ toglie $f$ e mette $e$. Le due macchie restano collegate — è il punto che rende $T'$ ancora uno spanning tree.

> [!question] Domanda tipica d'esame — Dimostrazione della cut property
> **D:** «3. Si fornisca una dimostrazione della proprietà del taglio.» *(Es. 2, punto 3 — 02/02/2026)*
> **R:**
> **Impostazione.** *Argomento di scambio* (non per assurdo — cfr. box **Non è una dimostrazione per assurdo**): sia $T^*$ un MST qualsiasi. Se $e \in T^*$ la tesi è già verificata; si supponga quindi che $T^*$ **non** contenga $e=(u,v)$, arco di costo minimo del cutset $D$ di $S$, con $u \in S$ e $v \notin S$.
>
> **Esistenza dell'arco da scambiare.** $T^*$ contiene un cammino da $u$ a $v$, quindi aggiungendo $e$ si crea un ciclo $C$. L'arco $e$ sta sia in $C$ sia in $D$, dunque $C \cap D \neq \emptyset$; per la proprietà di intersezione ciclo-cutset $|C \cap D|$ è pari, quindi $\geq 2$, e **esiste** $f \in C \cap D$ con $f \neq e$ (e $f \in T^*$).
>
> **Scambio.** Si costruisce $T' = T^* \cup \{e\} \setminus \{f\}$: rimuovere un arco dal ciclo appena creato non disconnette e lascia $n-1$ archi, quindi $T'$ è ancora uno spanning tree.
>
> **Confronto dei costi.** $f$ attraversa il taglio ed $e$ è il minimo del cutset, quindi $c_e \leq c_f$ e $c(T') = c(T^*) + c_e - c_f \leq c(T^*)$.
>
> **Conclusione.** Essendo $T^*$ un MST, non può esistere uno spanning tree di costo strettamente minore: deve valere $c(T') = c(T^*)$. $T'$ è quindi un MST che contiene $e$, il che dimostra la proprietà. $\square$

> [!question] Domanda tipica d'esame — Arco più leggero incidente a un nodo
> **D:** *(Vero o Falso)* «Sia v un nodo qualsiasi. L'arco più leggero incidente a v fa parte sempre di un qualche MST di G.» *(Es. 1, V/F n. 2 — 18/07/2025)*
> **R:**
> **Risposta.** Vero.
>
> **Perché.** È un corollario diretto della cut property applicata al taglio banale $S = \{v\}$: il cutset di $S$ è esattamente l'insieme degli archi incidenti a $v$, quindi il suo arco di costo minimo — l'arco più leggero incidente a $v$ — appartiene ad almeno un MST di $G$.
>
> **Osservazione.** Vale per **ogni** nodo $v$ preso singolarmente: applicando l'argomento a ciascun nodo si ottiene che l'arco più leggero incidente a ogni vertice è "salvabile" in un MST, non necessariamente nello stesso MST per tutti i nodi insieme.

> [!question] Domanda tipica d'esame — L'arco di peso massimo può essere obbligato
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G sono distinti, l'arco di peso minimo appartiene sempre all'MST T di G mentre l'arco di peso massimo non appartiene mai a T.» *(chiesto il 28/09/2022)*
> **R:**
> **Risposta.** Falsa.
>
> **Prima parte (corretta).** L'arco di peso minimo assoluto è il minimo di ogni taglio che attraversa, quindi per cut property appartiene a ogni MST, essendo i pesi distinti (minimo stretto in ogni taglio che lo contiene).
>
> **Controesempio alla seconda parte.** L'arco di peso massimo **può** appartenere all'MST: se è un **ponte** (l'unico collegamento tra due componenti del grafo), è obbligato in ogni spanning tree, MST incluso, indipendentemente dal suo peso.
>
> **Osservazione.** L'affermazione mischia due proprietà diverse: essere il minimo assoluto forza l'appartenenza (cut property), ma essere il massimo assoluto non forza l'**esclusione** — l'unica cosa che la garantirebbe è la cycle property applicata a un ciclo di cui l'arco è il massimo, e un ponte non appartiene a nessun ciclo.

> [!question] Domanda tipica d'esame — Sensitivity: alzare il peso di un arco fuori dall'MST
> **D:** *(Vero o Falso)* «Sia G = (V, E, w) un grafo non orientato e pesato. Sia T un MST di G e sia f un arco non in T. Si consideri il grafo G′ = (V, E, w′) ottenuto da G alzando il peso dell'arco f a un valore w′(f) > w(f). Allora T è un MST anche di G′.» *(Es. 1, punto 2 — 09/09/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** $w'(T)=w(T)$ perché $f\notin T$. Per ogni spanning tree $S$: se $f\notin S$, $w'(S)=w(S)$; se $f\in S$, $w'(S)=w(S)+(w'(f)-w(f))>w(S)$. Quindi $w'(S)\geq w(S)$ sempre. Se $T$ non fosse più MST di $G'$, esisterebbe $S$ con $w'(S)<w'(T)=w(T)$; ma allora $w(S)\leq w'(S)<w(T)$, cioè $S$ batterebbe $T$ già in $G$: assurdo.
>
> **Osservazione.** È il duale della domanda qui sotto, «abbassare il peso di un arco dentro l'MST»: le due si risolvono con lo stesso schema.

> [!question] Domanda tipica d'esame — Sensitivity: abbassare il peso di un arco dentro l'MST
> **D:** «Claim: Sia G = (V, E, w) un grafo non orientato e pesato. Sia T un MST di G e sia e un arco di T. Si consideri il grafo G′ = (V, E, w′) ottenuto da G abbassando il peso dell'arco e a un valore w′(e) < w(e). Allora T è un MST anche di G′.» *(Es. 1, prima domanda aperta — 18/07/2025)*
> **R:**
> $T$ resta un MST di $G'$: abbassare il peso di un arco già scelto non può renderlo svantaggioso.
>
> **Perché.** Sia $\Delta = w(e)-w'(e)>0$. Per assurdo, se $T$ non fosse più MST di $G'$ esisterebbe uno spanning tree $T'$ con $w'(T')<w'(T)$. Se $e\in T'$: entrambi i pesi calano di $\Delta$, quindi $w(T')<w(T)$. Se $e\notin T'$: $w'(T')=w(T')$ e $w'(T)=w(T)-\Delta<w(T)$, quindi ancora $w(T')<w(T)$. In entrambi i casi $T'$ batterebbe $T$ già in $G$: assurdo.
>
> **Osservazione.** Vale per pesi reali qualsiasi. Schema comune alle due domande di sensitivity: si confronta $T$ con un ipotetico $S$ migliore in $G'$, si osserva come cambia il peso di ciascuno passando da $w$ a $w'$, e si riporta la contraddizione **su $G$**, dove $T$ era ottimo per ipotesi.

> [!question] Domanda tipica d'esame — Non esiste un duale della cut property per gli archi fuori T
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora l'arco f è l'arco più pesante di almeno un taglio di G.» *(Es. 1, V/F n. 4 — 23/09/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** La cut property riguarda solo gli archi **dentro** $T$ (ciascuno è il minimo di un taglio indotto dalla propria rimozione). Il vero duale per gli archi **fuori** $T$ è la cycle property, che parla di **cicli**, non di tagli: l'enunciato confonde le due nozioni.
>
> **Controesempio.** $A,B,C,D$ con $AB{=}1,\ BC{=}1,\ AC{=}2,\ AD{=}5,\ DC{=}5$; MST $T=\{AB,BC,AD\}$. Preso $f=AC\ (2)\notin T$: in ogni taglio che $f$ attraversa, l'arco più pesante è sempre $AD$ o $DC$ (peso 5), mai $f$.
### Cycle property
> [!quote] Proprietà — Cycle property (proprietà del ciclo)
> Sia $C$ un qualsiasi ciclo in $G$, e sia $f$ **un** arco di **costo massimo** appartenente a $C$. Allora esiste un MST che **non contiene** $f$.

**Dimostrazione (argomento di scambio).**
Sia $T^*$ un MST qualsiasi. Se $f \notin T^*$ non c'è nulla da dimostrare; supponiamo dunque che $f \in T^*$.
1. Rimuovendo $f$ da $T^*$ l'albero si spezza in **due componenti**: sia $S$ l'insieme dei nodi di una delle due. Ciò definisce un taglio $(S, V\setminus S)$, il cui cutset è $D$.
2. L'arco $f$ appartiene sia al ciclo $C$ sia a $D$ (i suoi estremi stanno nelle due componenti distinte), dunque $C \cap D \neq \emptyset$. Per la proprietà di intersezione ciclo-cutset $|C \cap D|$ è **pari**, quindi $\geq 2$: **esiste** almeno un altro arco $e \in C \cap D$ con $e \neq f$.
3. Si ponga $T' = T^* \cup \{e\} \setminus \{f\}$. L'arco $e$ attraversa il taglio, quindi ricollega le due componenti separate dalla rimozione di $f$: $T'$ è connesso e ha $n-1$ archi, dunque è **ancora uno spanning tree**.
4. $e$ appartiene al ciclo $C$ ed $f$ è un arco di costo massimo di $C$: dunque $c_e \leq c_f$, da cui $c(T') = c(T^*) + c_e - c_f \leq c(T^*)$.
5. $T^*$ è un MST, quindi $c(T') = c(T^*)$. Perciò $T'$ è un MST e non contiene $f$. $\square$

Anche qui la slide riporta *«Pf. (exchange argument)»*: l'unica differenza rispetto alla cut property è **da dove proviene** la disuguaglianza $c_e \leq c_f$ (dalla massimalità di $f$ nel ciclo, anziché dalla minimalità di $e$ nel taglio) e **quale oggetto viene creato per primo** (un taglio anziché un ciclo). Lo scambio $T' = T^* \cup \{e\} \setminus \{f\}$ è letteralmente lo stesso.

![[mst_exchange_argument.png]]
È **la stessa figura della cut property**, letta al contrario: lì si parte da $e$ fuori da $T^*$ e lo si fa entrare, qui si parte da $f$ dentro $T^*$ e lo si fa uscire. Il prof usa deliberatamente lo stesso disegno nelle due slide.

> [!info] Le due dimostrazioni sono la stessa mossa, al contrario
> Conviene impararle in coppia, perché condividono lo scheletro — e infatti il prof riusa la stessa figura per entrambe.
>
> | | Cut property | Cycle property |
> |---|---|---|
> | Si parte da | $T^*$ che **non** contiene $e$ | $T^*$ che **contiene** $f$ |
> | Prima mossa | *aggiungo* $e$ → si crea un **ciclo** | *rimuovo* $f$ → si crea un **taglio** |
> | Si invoca | intersezione ciclo-cutset ⇒ esiste $f \neq e$ in entrambi | intersezione ciclo-cutset ⇒ esiste $e \neq f$ in entrambi |
> | Scambio | $T' = T^* \cup \{e\} \setminus \{f\}$ | $T' = T^* \cup \{e\} \setminus \{f\}$ |
> | Disuguaglianza | $c_e \leq c_f$ perché $e$ è il **minimo del taglio** | $c_e \leq c_f$ perché $f$ è il **massimo del ciclo** |
> | Conclusione | esiste un MST **con** $e$ | esiste un MST **senza** $f$ |
>
> Lo scambio è letteralmente identico: cambia solo **da dove viene la disuguaglianza** $c_e \leq c_f$. In entrambi i casi il passo che fa funzionare tutto è la **proprietà di intersezione ciclo-cutset**, che garantisce l'esistenza del secondo arco da scambiare — ed è per questo che va dimostrata *prima* delle due proprietà.
### Dalla proprietà locale alla correttezza globale
Le due proprietà sono **enunciati esistenziali su un singolo arco**: «esiste *un* MST che contiene $e$». Da sole non bastano a concludere che un algoritmo che le applica ripetutamente produca un MST, perché **ogni applicazione potrebbe testimoniare un MST diverso**. Le slide sorvolano su questo passaggio (per Prim scrivono soltanto *«immediate consequence of the cut property, used exactly $n-1$ times»*), ma il ponte va reso esplicito, ed è un **invariante di ciclo** dimostrato per induzione.

> [!quote] Invariante — Estendibilità della soluzione parziale
> Sia $F$ l'insieme di archi selezionati dall'algoritmo dopo un numero qualsiasi di passi. Vale in ogni momento:
> $$\exists \text{ un MST } T \text{ di } G \text{ tale che } F \subseteq T$$
> Si dice allora che $F$ è **estendibile** a un MST.

**Dimostrazione dell'invariante (per induzione sul numero di archi selezionati).**
- *Base.* $F = \emptyset$ è contenuto in qualunque MST, e un MST esiste perché $G$ è connesso.
- *Passo.* Sia $F \subseteq T$ con $T$ MST, e sia $e$ il prossimo arco selezionato, minimo di un taglio $(S, V\setminus S)$ **che nessun arco di $F$ attraversa** — condizione garantita da come i due algoritmi scelgono il taglio (in Prim $S$ è l'insieme dei nodi già raggiunti, in Kruskal la componente connessa di un estremo). Se $e \in T$ si conclude subito con lo stesso $T$. Altrimenti si applica lo scambio della cut property: aggiungendo $e$ a $T$ si forma un ciclo $C$, ed esiste $f \in C \cap D$, $f \neq e$, con $c_e \leq c_f$. L'albero $T' = T \cup \{e\} \setminus \{f\}$ è un MST che contiene $e$; e poiché $f$ attraversa il taglio mentre **nessun arco di $F$ lo attraversa**, si ha $f \notin F$, dunque $F \cup \{e\} \subseteq T'$. L'invariante si conserva. $\square$

**Conclusione.** Alla terminazione $F$ è uno spanning tree (ha $n-1$ archi ed è aciclico e connesso) ed è contenuto in un MST $T$: due spanning tree con $|F| = |T| = n-1$ e $F \subseteq T$ coincidono, quindi $F = T$ è un MST.

> [!warning] Il dettaglio che rende valida l'induzione
> Il passo cruciale è $f \notin F$: senza di esso lo scambio potrebbe **rimuovere un arco già scelto**, e $F \cup \{e\}$ non sarebbe più contenuto in $T'$. È garantito dal fatto che il taglio usato non è arbitrario — è scelto in modo che nessun arco già selezionato lo attraversi. Chi risponde «basta applicare la cut property $n-1$ volte» sta assumendo implicitamente proprio questo, e all'orale è la domanda di approfondimento naturale.

> [!question] Domanda tipica d'esame — Arco più leggero di un ciclo non è garantito
> **D:** *(Vero o Falso)* «Sia C un ciclo di G ed e l'arco più leggero di C. Allora esiste sempre un MST di G che contiene e.» *(chiesto il 28/09/2022)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** A differenza della cut property (che garantisce l'inclusione del minimo di un taglio), non esiste una proprietà simmetrica per il minimo di un ciclo: la cycle property parla solo del **massimo** del ciclo, non del minimo.
>
> **Come può essere escluso.** Un arco leggero interno a un ciclo può comunque essere escluso da ogni MST se, per il taglio che separa i suoi estremi, esiste un percorso alternativo esterno al ciclo di costo complessivo ancora minore: è la cut property applicata a *quel* taglio a decidere l'esclusione, non la cycle property.
>
> **Osservazione.** Le due proprietà non sono simmetriche: la cut property vincola i minimi dei tagli, la cycle property vincola i massimi dei cicli; non esiste un analogo che vincoli i minimi dei cicli.

> [!question] Domanda tipica d'esame — Caratterizzazione degli alberi non ottimi
> **D:** *(Vero o Falso)* «Se T non è un MST di G allora esiste un arco e ∈ T e un arco f ∉ T tale che e è l'arco più pesante del ciclo che si forma quando si aggiunge f a T.» *(chiesto il 13/06/2024)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È (nella sostanza) la contronominale della cycle property applicata a $T$: se $T$ non è minimo, esiste un arco $e \in T$ scambiabile con un arco $f \notin T$ per ottenere un albero di costo minore o uguale. Aggiungendo $f$ a $T$ si crea un ciclo, e $e$ ne deve essere l'arco di peso **massimo** — altrimenti lo scambio $T \cup \{f\} \setminus \{e\}$ non ridurrebbe (o pareggerebbe) il costo.
>
> **Osservazione.** È lo stesso argomento di scambio alla base della dimostrazione di ottimalità di Kruskal e Prim: ogni volta che un albero non è ottimo, esiste una coppia $(e, f)$ di questo tipo che permette di migliorarlo.

> [!question] Domanda tipica d'esame — Massimo di un ciclo vs massimo di tutti i cicli
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco non di T. Allora f è l'arco di peso massimo in tutti i cicli che lo contengono.» *(Es. 1, V/F n. 1 — 18/07/2025)*
> **R:**
> **Risposta.** Falso.
>
> **Perché.** La cycle property garantisce solo che $f$ sia il massimo di **almeno un** ciclo — il ciclo fondamentale che si forma aggiungendo $f$ a $T$ — non di **ogni** ciclo di $G$ che contiene $f$.
>
> **Osservazione.** In un grafo con più cicli passanti per $f$, l'arco può non essere il più pesante in un ciclo diverso da quello fondamentale rispetto a $T$: la proprietà è legata alla scelta di $T$, non è una caratteristica assoluta di $f$.

> [!question] Domanda tipica d'esame — Un arco dell'MST non è per forza il minimo di un ciclo
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia e un arco di T, allora l'arco e è l'arco più leggero di almeno un ciclo in G.» *(Es. 1, V/F n. 4 — 09/09/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Controesempio.** Se $e$ è un **ponte** (bridge) di $G$ — cioè la sua rimozione disconnette il grafo — allora $e$ non appartiene ad alcun ciclo di $G$, quindi non può essere l'arco più leggero di nessun ciclo, pur essendo necessariamente parte di ogni spanning tree, MST incluso.
>
> **Osservazione.** L'affermazione varrebbe se si aggiungesse l'ipotesi che $e$ appartenga ad almeno un ciclo: in quel caso $e$ è comunque il più leggero solo del ciclo fondamentale indotto da un particolare $T$, non necessariamente di ogni ciclo che lo contiene (cfr. domanda precedente).

> [!question] Domanda tipica d'esame — Cut property e archi non minimi
> **D:** Enuncia la cut property e spiega come si usa per mostrare che un albero ricoprente $T$ non è minimo.
> **R:**
> **Idea.** La cut property afferma che l'arco di costo minimo che attraversa un qualsiasi taglio appartiene ad *almeno* un MST; per usarla "al contrario" e mostrare che $T$ non è minimo serve trovare **il taglio giusto**.
>
> **Procedura.** Sia $T$ un albero ricoprente e $f \in T$. Rimuovendo $f$ da $T$, l'albero si spezza in due componenti, che definiscono un taglio $(S, V\setminus S)$ di cui $f$ è l'**unico** arco di $T$ che lo attraversa. Se esiste un arco $e \notin T$ che attraversa *quello stesso* taglio con $c_e < c_f$, allora $T$ non è minimo: $T' = T \cup \{e\} \setminus \{f\}$ è ancora un albero ricoprente e costa strettamente meno.
>
> **Attenzione al verso dell'implicazione.** Non vale che «se $f$ non è il minimo di un taglio *qualsiasi*, allora esiste un MST senza $f$».
>
> **Controesempio.** $A$-$B = 5$ come unico arco incidente ad $A$, più il triangolo $B$-$C=1$, $C$-$D=1$, $B$-$D=1$. Nel taglio $S=\{A,D\}$ il cutset è $\{A\text-B=5,\ C\text-D=1,\ B\text-D=1\}$ e $A\text-B$ non è il minimo, eppure è un **ponte**: sta in ogni albero ricoprente, quindi in ogni MST. Il taglio va scelto come sopra, **indotto da $T$**, non arbitrariamente.

> [!question] Domanda tipica d'esame — Pesi in {1, 2}: un arco fuori T non deve avere per forza peso 2
> **D:** *(Vero o Falso)* «Si assuma che per ogni arco e vale w(e) ∈ {1, 2}, e sia T un MST di G. Allora ogni arco del grafo che non appartiene a T deve avere peso 2.» *(Es. 1, V/F n. 2 — 09/09/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** La cycle property esclude solo l'arco **strettamente** massimo di un ciclo. Se un ciclo è formato interamente da archi di peso uguale (es. tutti 1), uno qualunque resta escluso da un dato MST per non chiudere il ciclo, pur non essendo affatto il più pesante.
>
> **Controesempio.** Triangolo con i tre archi di peso 1 (rispetta $w(e)\in\{1,2\}$): ogni MST ne sceglie due, il terzo — escluso — pesa comunque 1, non 2.

> [!question] Domanda tipica d'esame — Tutti gli archi del ciclo fondamentale sono ≤ w(f)
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora l'aggiunta di f a T forma un ciclo e tutti gli archi del ciclo hanno un peso che è minore o uguale a quello di f.» *(Es. 1, V/F n. 3 — 09/09/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È la cycle property in forma non stretta. Se esistesse un arco $e$ del ciclo con $w(e)>w(f)$, allora $T'=(T\setminus\{e\})\cup\{f\}$ sarebbe uno spanning tree con $w(T')<w(T)$, contro la minimalità di $T$.
>
> **Osservazione.** La disuguaglianza è $\leq$, non $<$: con pesi ripetuti sul ciclo, $f$ può pareggiare (ma mai superare) il massimo.

> [!question] Domanda tipica d'esame — Variante: f non è il più pesante di ogni ciclo che lo contiene
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora f è l'arco più pesante di ogni ciclo di G che lo contiene.» *(Es. 1, V/F n. 3 — 23/09/2025)*
> **R:**
> **Risposta.** Falsa — stessa argomentazione della domanda «Massimo di un ciclo vs massimo di tutti i cicli» del 18/07/2025 qui sopra: la cycle property garantisce che $f$ sia massimo solo nel ciclo **fondamentale** indotto da $T$, non in ogni ciclo di $G$ che lo contiene.
>
> **Controesempio.** $A,B,C,D$ con $AB{=}1,BC{=}1,AC{=}2,AD{=}5,DC{=}5$: nel ciclo fondamentale $A\text-B\text-C\text-A$, $f=AC$ è il massimo; nel ciclo $A\text-D\text-C\text-A$ (pesi 5,5,2), $f$ è invece il più leggero.
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
![[mst_grafo_esempio.png]]
Il grafo campione: 7 nodi, 9 archi. **Coprine il seguito ed eseguilo a mano** prima di leggere la traccia — è l'esercizio, non il testo.

```
Archi ordinati per costo: (C,E,1), (F,G,4), (E,F,6), (A,B,7), (E,G,9),
                          (C,D,10), (A,C,14), (B,C,21), (A,D,30)

Passo 1: (C,E,1)  → find(C)≠find(E) → aggiungi.  componenti: {C,E}
Passo 2: (F,G,4)  → find(F)≠find(G) → aggiungi.  {C,E} {F,G}
Passo 3: (E,F,6)  → find(E)≠find(F) → aggiungi.  {C,E,F,G}
Passo 4: (A,B,7)  → find(A)≠find(B) → aggiungi.  {A,B} {C,E,F,G}
Passo 5: (E,G,9)  → find(E)=find(G) → CICLO, skip.
Passo 6: (C,D,10) → find(C)≠find(D) → aggiungi.  {A,B} {C,D,E,F,G}
Passo 7: (A,C,14) → find(A)≠find(C) → aggiungi.  {A,...,G}  (fonde le due componenti)
Passo 8: (B,C,21) → find(B)=find(C) → CICLO, skip.
Passo 9: (A,D,30) → find(A)=find(D) → CICLO, skip.
MST finale: {(C,E),(F,G),(E,F),(A,B),(C,D),(A,C)}
            costo = 1+4+6+7+10+14 = 42        (6 archi = n-1 ✓)
```

![[mst_kruskal_risultato.png]]
Il risultato sulle slide: in **blu** i 6 archi accettati, in **rosso** i 3 scartati perché chiudevano un ciclo. Confronto utile: $E\text{-}G\ (9)$ viene rifiutato pur essendo più leggero di $A\text{-}C\ (14)$, che invece è accettato. Non è una contraddizione — Kruskal non sceglie «gli archi più leggeri», sceglie **il più leggero fra quelli che non chiudono un ciclo**, e quando tocca a $E\text{-}G$ i nodi $E$ e $G$ sono già connessi via $E\text{-}F\text{-}G$.

> [!question] Domanda tipica d'esame — Il numero di componenti dopo k archi non è garantito n−k
> **D:** *(Vero o Falso)* «Dopo aver processato il terzo arco di peso minimo di G, l'algoritmo ha calcolato una soluzione parziale che è una foresta di esattamente n − 3 componenti connesse;» *(chiesto il 19/02/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Il numero di componenti diminuisce di uno solo quando l'arco **processato** viene effettivamente **aggiunto** a $T$ (cioè collega due componenti distinte), non a ogni arco processato in assoluto.
>
> **Controesempio.** Se il terzo arco in ordine di peso chiude un ciclo — perché i suoi estremi sono già nella stessa componente dopo i primi due — viene scartato: il numero di componenti resta $n-2$, non $n-3$.
>
> **Osservazione.** L'uguaglianza $n-k$ dopo $k$ archi **processati** vale solo se tutti e $k$ sono stati effettivamente **accettati**; in generale, dopo $k$ archi processati il numero di componenti è $n$ meno il numero di archi effettivamente accettati tra i primi $k$.
### Correttezza
La correttezza di Kruskal segue direttamente dalla **cut property** e dalla **cycle property**; la slide dedica una figura a ciascuno dei due casi.
- Quando l'algoritmo **aggiunge** l'arco $(x, y)$: le componenti di $x$ e $y$ sono distinte. Sia $S$ l'insieme dei vertici appartenenti alla **componente connessa di $y$** nella soluzione corrente. L'arco $(x,y)$ attraversa il taglio $(S, V\setminus S)$; ogni altro arco che lo attraversa non è ancora stato esaminato, e poiché l'algoritmo scandisce gli archi in **ordine crescente di costo**, ha costo $\geq c_{xy}$. Dunque $(x, y)$ è un arco di costo minimo che attraversa quel taglio: per la **cut property** esiste un MST che lo contiene. Si noti che **nessun arco già selezionato attraversa questo taglio** — gli archi di $F$ incidenti a $S$ sono interni alla componente di $y$ — il che è esattamente l'ipotesi che rende applicabile l'[[#Dalla proprietà locale alla correttezza globale|invariante di estendibilità]].
- Quando l'algoritmo **rifiuta** l'arco $(x, y)$: $x$ e $y$ sono già connessi nella soluzione corrente, quindi $(x, y)$ chiude un ciclo con il cammino già presente. Tutti gli archi di quel cammino sono stati aggiunti **prima**, dunque hanno costo $\leq c_{xy}$: $(x, y)$ è un arco di costo massimo in quel ciclo, e per la **cycle property** esiste un MST che **non** lo contiene.

> [!warning] «Esiste un MST senza $f$», non «$f$ non sta in nessun MST»
> Entrambe le proprietà sono enunciati **esistenziali**, e vanno riportate così. La cycle property non dice che l'arco massimo di un ciclo è escluso da *ogni* MST: se il massimo non è stretto (pesi ripetuti sul ciclo), quell'arco può benissimo comparire in qualche altro MST di pari costo. La forma «non appartiene ad alcun MST» vale solo aggiungendo l'ipotesi di **massimo stretto**, e simmetricamente per la cut property con il minimo stretto. È una delle imprecisioni più penalizzate all'orale.

> [!question] Domanda tipica d'esame — Perché un arco viene scartato
> **D:** *(Vero o Falso)* «Quando l'algoritmo processa un generico arco e e decide di non aggiungerlo alla soluzione, vuol dire non solo che l'arco e forma un ciclo con gli archi già aggiunti, ma che è anche l'arco più pesante di quel ciclo;» *(chiesto il 19/02/2024)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** È esattamente l'argomento della sezione Correttezza qui sopra. Esaminando gli archi in ordine crescente di peso, quando si scarta $e=(x,y)$ perché $x$ e $y$ sono già connessi in $T$, l'arco chiude un ciclo con il cammino già presente; poiché tutti gli archi già aggiunti (quindi anche quelli del ciclo) hanno peso $\leq c_e$, $e$ è necessariamente l'arco di peso **massimo** di quel ciclo.
>
> **Osservazione.** Per la cycle property, l'arco di peso massimo di un ciclo può sempre essere escluso da un MST: è questo che garantisce che scartare $e$ non comprometta l'ottimalità.

> [!question] Domanda tipica d'esame — L'MST può contenere l'arco più pesante di G
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Kruskal non contiene mai l'arco di peso massimo di G.» *(chiesto il 24/09/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Controesempio.** Se $G$ è già un albero (connesso con esattamente $n-1$ archi), l'unico spanning tree possibile è $G$ stesso, che è quindi anche l'MST e contiene necessariamente anche l'arco di peso massimo.
>
> **Osservazione.** Più in generale, se l'arco di peso massimo è un **ponte**, deve comparire in ogni spanning tree, MST incluso, indipendentemente da quanto sia costoso: nessuno scambio può eliminarlo perché non esiste un ciclo alternativo che lo contenga.
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
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Come mostrato nella tabella qui sopra, il costo totale di Kruskal è dominato dall'**ordinamento** degli archi, $O(m \log m) = O(m \log n)$.
>
> **Calcolo.** Con $m = \Theta(n)$ si ottiene $O(n \log n)$, non $O(n)$: il fattore logaritmico dell'ordinamento non scompare, indipendentemente da quanto sia piccolo $m$ rispetto a $n^2$.

> [!question] Domanda tipica d'esame — Θ(n√n) archi non rende Kruskal lineare
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Kruskal che implementa la Union-Find con la QuickFind con euristica union by size ha complessità lineare, ovvero Θ(n√n).» *(Es. 1, V/F n. 5 — 09/09/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Calcolo.** Con $m = \Theta(n\sqrt{n})$, la complessità di Kruskal resta $O(m \log n) = \Theta(n \sqrt{n} \log n)$, dominata dall'ordinamento degli archi, non $\Theta(n\sqrt n)$ come richiesto dall'enunciato.
>
> **Osservazione.** Il fattore $\log n$ non si elimina indipendentemente dall'euristica scelta per la Union-Find (QuickFind con o senza union by size), perché quell'euristica riguarda solo il costo delle operazioni `union`/`find`, non quello dell'ordinamento — che resta il termine dominante.

> [!question] Domanda tipica d'esame — Su grafi densi l'euristica union-by-size è ininfluente
> **D:** *(Vero o Falso)* «Se G è completo allora l'algoritmo di Kruskal ha la stessa complessità asintotica sia se usa per la struttura Union-Find la QuickFind con o senza euristica union by size.» *(Es. 1, V/F n. 5 — 18/07/2025)*
> **R:**
> **Risposta.** Vero.
>
> **Perché.** Se $G$ è completo, $m = \Theta(n^2)$, quindi il costo dell'ordinamento $O(m \log n) = O(n^2 \log n)$ domina già asintoticamente il costo delle operazioni di Union-Find.
>
> **Calcolo.** Senza euristica il costo di Union-Find è al più $O(m) = O(n^2)$; con union by size è $O(m + n\log n)$. In entrambi i casi il totale resta $\Theta(n^2 \log n)$, dominato dall'ordinamento: l'euristica non cambia la complessità asintotica complessiva su grafi densi.

> [!question] Domanda tipica d'esame — MST di una griglia N×N con pesi orizzontali 1 e verticali i+j
> **D:** «Sia N > 2 un intero. Si consideri il grafo non orientato di n = N² nodi disposti su un piano a formare una griglia N × N, dove ogni nodo è collegato ai suoi (al più) quattro nodi vicini orizzontalmente e verticalmente. In particolare il nodo in posizione (i, j), con i, j ∈ {1, . . . , N}, ha un arco verso il nodo (i, j − 1) (se esiste) e verso il nodo (i, j + 1) (se esiste) di peso 1, e ha un arco verso il nodo (i − 1, j) (se esiste) di peso i − 1 + j e un arco verso il nodo (i + 1, j) (se esiste) di peso i + j. Si descriva come è fatto un MST del grafo e si derivi una formula chiusa per il suo peso. (Max 5 righe.)» *(Es. 1, punto 2 — 23/09/2025)*
> **R:**
> L'MST è formato da tutti gli archi orizzontali (peso 1) più, per ogni coppia di righe adiacenti, l'unico arco verticale in colonna $j=1$.
>
> **Calcolo.** Gli $N(N-1)$ archi orizzontali (peso 1, minimo assoluto) non creano cicli: ogni riga resta un cammino. Restano $N-1$ archi verticali, uno per coppia di righe adiacenti $(i,i+1)$: tra i candidati di peso $i+j$ ($j=1,\dots,N$), il minimo stretto è in colonna $j=1$ (peso $i+1$) — per la cut property, appartiene a ogni MST. Peso totale: $N(N-1) + \sum_{i=1}^{N-1}(i+1) = \dfrac{(3N+2)(N-1)}{2}$.
>
> **Unicità.** L'MST è unico, ma **non** perché i minimi coinvolti siano stretti: gli archi orizzontali pesano tutti $1$, quindi ci sono pareggi in abbondanza. Il criterio corretto è sui **massimi dei cicli**: ogni arco fuori dall'albero è un verticale in colonna $j \geq 2$, di peso $i+j$, e il suo ciclo fondamentale è formato da orizzontali (peso $1$) più il verticale in colonna $1$ (peso $i+1$). Essendo $j \geq 2$, vale $i+j > i+1$: l'arco escluso è il massimo **stretto** del proprio ciclo fondamentale, quindi nessuno scambio a costo invariato è possibile e l'MST è unico. I pareggi tra orizzontali sono innocui perché quegli archi stanno **tutti** nell'albero.
## Algoritmo di Prim
L'algoritmo di **Prim** (Jarník 1930, Dijkstra 1957, Prim 1959) costruisce l'MST partendo da un nodo sorgente $s$ e crescendo l'albero un arco alla volta, scegliendo sempre l'arco di costo minimo che ha esattamente un estremo nell'albero corrente.
### Idea e correttezza
Ad ogni passo si ha un insieme $S$ di nodi già esplorati (inizialmente $S = \{s\}$). Si aggiunge il **nodo più economico** raggiungibile da $S$, cioè il nodo $v \notin S$ per cui esiste un arco $(u, v)$ con $u \in S$ e $c_{uv}$ minimo tra tutti gli archi del cutset.

**Correttezza:** la slide liquida il punto con *«immediate consequence of the cut property, used exactly $n-1$ times»*. In forma rigorosa: a ogni passo $S$ è l'insieme dei nodi già raggiunti e nessun arco già selezionato attraversa il taglio $(S, V\setminus S)$ — sono tutti interni a $S$ — quindi si applica l'[[#Dalla proprietà locale alla correttezza globale|invariante di estendibilità]]. L'arco scelto è il minimo di quel cutset, l'invariante si conserva, e dopo $n-1$ passi la soluzione parziale è uno spanning tree contenuto in un MST: coincide con esso.

![[mst_prim_taglio_iniziale.png]]
Il primo passo di Prim sul grafo campione: $s = A$ (cerchiato in blu) e la **curva rossa** è il taglio $(\{A\}, V\setminus\{A\})$. Gli archi che lo attraversano sono $A\text{-}B\ (7)$, $A\text{-}C\ (14)$, $A\text{-}D\ (30)$: il minimo è $A\text{-}B$, ed è quello che Prim aggiunge. A ogni iterazione la curva si allarga per inglobare il nodo appena preso — è la lettura visiva del «taglio unico che cresce».

> [!info] Kruskal e Prim usano la stessa proprietà su tagli diversi
> È la distinzione che chiarisce il rapporto fra i due algoritmi, ed è una domanda d'orale ricorrente.
> - In **Prim** il taglio è **uno solo e cresce**: $(S, V\setminus S)$ con $S$ l'insieme dei nodi già raggiunti, che si allarga di un nodo per volta.
> - In **Kruskal** i tagli sono **molti e cambiano**: ogni volta che si accetta un arco $(u,v)$, il taglio implicitamente invocato è quello che separa la componente connessa di $u$ dal resto. Non essendoci un unico $S$ che cresce, Kruskal può far crescere più «pezzi» di albero in parallelo e fonderli alla fine.
>
> In entrambi i casi l'arco scelto è il minimo del proprio cutset, quindi la cut property si applica identica; cambia solo *quale* taglio si sta considerando a ogni passo.

> [!question] Domanda tipica d'esame — Cut property e correttezza di Prim
> **D:** «3. Si discuta in modo conciso e preciso come è possibile usare la proprietà del taglio per dimostrare la correttezza dell'algoritmo di Prim.» *(Es. 2, terza domanda aperta — 26/06/2025)*
> **R:**
> **Idea.** Ad ogni passo, l'insieme $S$ dei nodi già esplorati definisce un taglio $(S, V \setminus S)$; Prim seleziona sempre l'arco di costo minimo del cutset di $S$ (l'arco che collega $S$ al resto del grafo a minor costo).
>
> **Applicazione a ogni passo.** Per la cut property, l'arco scelto appartiene sempre ad almeno un MST di $G$ che estende le scelte già fatte in $T$. L'argomento vale identicamente per ciascuno degli $n-1$ archi aggiunti, perché a ogni passo il taglio $(S, V\setminus S)$ cambia ma la proprietà si applica allo stesso modo.
>
> **Conclusione.** L'albero finale ha $n-1$ archi, ognuno giustificato dalla cut property al momento della sua aggiunta: è quindi esso stesso un MST.
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
Stesso grafo di Kruskal (figura sopra), sorgente $s = A$. A ogni passo i **candidati** sono gli archi del cutset di $S$, cioè quelli con esattamente un estremo in $S$.
```
Passo 1: S={A}.           Candidati: (A,B,7),(A,C,14),(A,D,30).
         Minimo: (A,B,7).   Aggiungi B.
Passo 2: S={A,B}.         Candidati: (A,C,14),(A,D,30),(B,C,21).
         Minimo: (A,C,14).  Aggiungi C.
Passo 3: S={A,B,C}.       Candidati: (A,D,30),(C,D,10),(C,E,1).
         Minimo: (C,E,1).   Aggiungi E.
Passo 4: S={A,B,C,E}.     Candidati: (A,D,30),(C,D,10),(E,F,6),(E,G,9).
         Minimo: (E,F,6).   Aggiungi F.
Passo 5: S={A,B,C,E,F}.   Candidati: (A,D,30),(C,D,10),(E,G,9),(F,G,4).
         Minimo: (F,G,4).   Aggiungi G.   ← entrando F, si apre anche (F,G)
Passo 6: S={A,B,C,E,F,G}. Candidati: (A,D,30),(C,D,10).
         Minimo: (C,D,10).  Aggiungi D.
MST = {(A,B,7),(A,C,14),(C,E,1),(E,F,6),(F,G,4),(C,D,10)}, costo = 42
```
Stesso albero e stesso costo di Kruskal, come dev'essere: i pesi sono tutti distinti, quindi l'MST è **unico** e i due algoritmi non possono che convergere sullo stesso. Se ti viene un costo diverso fra i due, hai sbagliato un passo — è un controllo di correttezza gratuito, usalo anche al compito.

> [!warning] Il passo 5 è la trappola dell'esecuzione a mano
> Entrando $F$ in $S$, il cutset **cambia**: si aprono gli archi incidenti a $F$, fra cui $(F,G,4)$, che diventa il nuovo minimo e scalza $(E,G,9)$. Chi esegue Prim in fretta tende a ricalcolare i candidati solo per il nodo appena aggiunto *senza rileggerne tutti gli archi*, e sceglie $(E,G,9)$ — ottenendo un albero di costo 47, sbagliato. A ogni passo ricontrolla **tutti** gli archi che escono dal nuovo $S$.

> [!warning] Chiave vs distanza: non confondere Prim con Dijkstra
> In Prim la chiave $a[v]$ rappresenta il costo del **miglior arco singolo** che connette $v$ all'albero — non il costo cumulativo del cammino da $s$ a $v$. Usare la distanza cumulativa al posto della chiave dell'arco produce Dijkstra (cammini minimi), non Prim (MST).

> [!question] Domanda tipica d'esame — Prim su grafo non pesato non è BFS
> **D:** *(Vero o Falso)* «Quando il grafo è non pesato, l'algoritmo di Prim restituisce un albero dei cammini minimi radicato sul nodo sorgente su cui è chiamato.» *(chiesto il 13/06/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** Come chiarito nel box qui sopra, Prim usa come chiave il costo del singolo arco di attacco, non la distanza cumulativa dalla sorgente. Con pesi tutti uguali a 1 ogni spanning tree è già un MST (i costi sono tutti uguali), ma le scelte di Prim tra archi di pari peso sono **arbitrarie** e non seguono necessariamente l'ordine per livelli di una BFS.
>
> **Osservazione.** L'albero prodotto può quindi non coincidere con l'albero dei cammini minimi da $s$, anche se entrambi hanno lo stesso costo totale come spanning tree.

> [!question] Domanda tipica d'esame — MST e albero dei cammini minimi restano problemi diversi
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Prim invocato su una sorgente s è anche un albero dei cammini minimi di G rispetto alla stessa sorgente s.» *(chiesto il 24/09/2024)*
> **R:**
> **Risposta.** Falsa.
>
> **Perché.** In generale i due problemi ottimizzano criteri diversi — costo totale dell'albero per Prim, distanza dalla sorgente per l'albero dei cammini minimi — e producono alberi diversi.
>
> **Controesempio (concettuale).** Un nodo lontano da $s$ ma raggiungibile con un arco di attacco molto economico viene incluso presto da Prim, anche se il suo cammino minimo dalla sorgente lungo l'albero di Prim è più lungo del cammino minimo reale: Prim minimizza il costo del singolo arco di attacco, non la distanza cumulativa.

> [!question] Domanda tipica d'esame — Pesi tutti uguali: ogni SPT è anche un MST
> **D:** *(Vero o Falso)* «Se tutti i pesi di G sono uguali, allora ogni albero dei cammini minimi di G rispetto a una qualsiasi sorgente s è anche un MST di G.» *(Es. 1, V/F n. 3 — 18/07/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Se tutti i pesi valgono una costante $c$, ogni spanning tree ha $n-1$ archi e quindi costo $(n-1)c$: sono tutti di pari peso, dunque tutti MST. Un albero dei cammini minimi è per definizione uno spanning tree, quindi rientra in questo insieme indipendentemente dalla sorgente $s$.
>
> **Osservazione.** Argomento diretto per conteggio, non serve cut/cycle property; è il fatto usato più sotto per «con pesi uguali basta BFS/DFS, $O(n+m)$».

> [!question] Domanda tipica d'esame — Pesi in {1, 2}: Prim non dà per forza un albero dei cammini minimi
> **D:** *(Vero o Falso)* «Se per ogni arco e vale w(e) ∈ {1, 2}, allora l'algoritmo di Prim applicato su un nodo iniziale s calcola un MST che è anche un albero dei cammini minimi con sorgente s.» *(Es. 1, V/F n. 4 — 18/07/2025)*
> **R:**
> **Risposta.** Falsa.
>
> **Controesempio.** Ciclo $s\text-a\text-b\text-c\text-d\text-s$ con i quattro archi della catena di peso 1 e l'arco diretto $s\text-d$ di peso 2. Per la cycle property l'unico MST è la catena $s,a,b,c,d$ (esclude l'arco di peso 2, unico massimo del ciclo), e Prim la calcola senza ambiguità di pareggio.
>
> **Perché.** Nell'albero calcolato la distanza $s\to d$ è $4$, ma nel grafo il vero cammino minimo è l'arco diretto, costo $2$: Prim minimizza il costo dell'arco di attacco, non la distanza cumulativa da $s$.

> [!question] Domanda tipica d'esame — Variante: pesi tutti unitari, Prim non dà per forza un SPT
> **D:** *(Vero o Falso)* «Se tutti gli archi hanno peso 1, allora l'algoritmo di Prim applicato su un nodo iniziale s calcola un MST che è necessariamente anche un albero dei cammini minimi con sorgente s.» *(Es. 1, V/F n. 1 — 09/09/2025)*
> **R:**
> **Risposta.** Falsa — stessa argomentazione della domanda «Prim su grafo non pesato non è BFS» del 13/06/2024 qui sopra: con pesi unitari ogni spanning tree è un MST, ma le scelte di Prim tra archi a pari peso sono arbitrarie e non seguono l'ordine per livelli di una BFS.
>
> **Controesempio.** Triangolo $s,a,b$ con i tre archi di peso 1: Prim può scegliere $(s,a)$ poi $(a,b)$, dando $T=\{sa,ab\}$; la distanza $s\to b$ in $T$ è $2$, ma nel grafo è $1$ tramite l'arco diretto $(s,b)$.
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
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Prim che implementa la coda con priorità attraverso un heap di Fibonacci ha complessità lineare, ovvero Θ(n√n).» *(Es. 1, V/F n. 5 — 23/09/2025)*
> **R:**
> **Risposta.** Vero.
>
> **Calcolo.** Con l'heap di Fibonacci, Prim costa $O(m + n\log n)$. Con $m = \Theta(n\sqrt n)$ si ha $n\log n = o(n\sqrt n)$ (il fattore $\sqrt n$ domina $\log n$), quindi il totale è $\Theta(n\sqrt n + n \log n) = \Theta(n\sqrt n) = \Theta(m)$: la complessità è effettivamente lineare nel numero di archi.
>
> **Osservazione.** È l'opposto dello scenario analogo per Kruskal (cfr. la domanda «Θ(n√n) archi non rende Kruskal lineare»): lì il fattore $\log n$ dell'ordinamento non si elimina mai, qui invece l'heap di Fibonacci lo rende asintoticamente irrilevante.

> [!question] Domanda tipica d'esame — Bound in funzione del grado massimo
> **D:** *(Vero o Falso)* «Se il grado massimo in G è δ allora l'algoritmo di Prim implementato con heap binario ha complessità O(δ n log(n)) nel caso peggiore» *(chiesto il 27/09/2023)*
> **R:**
> **Risposta.** Vera.
>
> **Calcolo.** Con heap binario, Prim costa $O(m \log n)$. Se il grado massimo è $\delta$, allora $m \leq \delta n / 2 = O(\delta n)$ — ogni nodo contribuisce al più $\delta$ archi, ognuno contato due volte — quindi $O(m \log n) = O(\delta n \log n)$.
>
> **Osservazione.** È un bound più fine di $O(m \log n)$ generico, utile su grafi con grado massimo limitato: se $\delta = O(1)$ si ottiene $O(n \log n)$ anche senza conoscere $m$ esplicitamente.
## Riepilogo e confronto degli algoritmi
| Algoritmo | Struttura dati | Complessità | Note |
|---|---|---|---|
| Kruskal | [[02 - Union-Find]] (Union by size) | $O(m \log n)$ | Ottimo su grafi sparsi; ordinamento domina |
| Prim (naïve) | Scansione lineare, senza PQ | $O(mn)$ | Semplice ma inefficiente |
| Prim (array) | Array non ordinato | $O(n^2)$ | Buono su grafi densi ($m=\Theta(n^2)$) |
| Prim (heap binario) | Min-heap binario | $O(m \log n)$ | Bilanciato; buono su grafi sparsi |
| Prim (Fibonacci) | [[07 - Code con Priorità e Heap\|Heap di Fibonacci]] | $O(m + n \log n)$ | Bound migliore in assoluto; su grafi densi pareggia l'array ($O(n^2)$) |

> [!info] Confronto Kruskal vs Prim
> Su grafi **sparsi** ($m = O(n)$) sia Kruskal che Prim con heap binario danno $O(n \log n)$; la scelta è indifferente. Su grafi **densi** ($m = \Theta(n^2)$), Kruskal richiede $O(n^2 \log n)$ (dominato dall'ordinamento), mentre Prim con array non ordinato dà $O(n^2)$ e Prim con heap di Fibonacci dà $O(n^2)$: in questo caso Prim è preferibile.
>
> **Dove serve davvero l'heap di Fibonacci.** Non sui grafi densi: lì $O(m + n\log n) = O(n^2)$, esattamente quanto il banale array non ordinato, che è molto più semplice da implementare. Il bound $O(m + n\log n)$ domina (in senso debole) sia l'array — $O(m + n\log n) \leq O(n^2)$, con uguaglianza solo a densità massima — sia l'heap binario — $O(m + n\log n) \leq O(m\log n)$, con uguaglianza solo sui grafi sparsi. Il vantaggio **stretto** su entrambe le alternative si materializza quindi nella **fascia intermedia** di densità, ad esempio $m = \Theta(n\sqrt n)$: lì Fibonacci dà $\Theta(n\sqrt n)$ contro $\Theta(n\sqrt n \log n)$ dell'heap binario e $\Theta(n^2)$ dell'array. È lo scenario della domanda d'esame del 23/09/2025 qui sopra.
> Nota teorica: esistono algoritmi asintoticamente migliori — $O(m \log \log n)$ (Cheriton-Tarjan 1976, Yao 1975), $O(m \cdot \alpha(m,n))$ (Fredman-Tarjan 1987), $O(m)$ randomizzato (Karger-Klein-Tarjan 1995) — ma Kruskal e Prim rimangono gli algoritmi standard per il corso.

> [!question] Domanda tipica d'esame — Caso speciale: pesi tutti uguali
> **D:** «Quale algoritmo useresti per calcolare un MST di G e qual è la sua complessità asintotica nel caso peggiore se G ha tutti gli archi dello stesso peso? [risposta in 1 riga]» *(chiesto il 27/09/2023)*
> **R:**
> **Idea.** Basta una BFS o una DFS a partire da un vertice qualsiasi, con complessità $O(n+m)$: nessun algoritmo greedy basato sui pesi è necessario.
>
> **Perché funziona.** Se tutti gli archi hanno lo stesso peso, ogni spanning tree ha lo stesso costo totale ($n-1$ volte il peso comune): ogni spanning tree è quindi automaticamente un MST, e la scelta greedy di Kruskal o Prim diventa superflua.
>
> ⏱️ **Se la traccia dà 1 riga**: scrivi solo «BFS/DFS, $O(n+m)$: con pesi tutti uguali ogni spanning tree è un MST». Non omettere mai la complessità $O(n+m)$ — è esplicitamente richiesta insieme all'algoritmo.

> [!question] Domanda tipica d'esame — Kruskal: descrizione e correttezza
> **D:** Descrivi l'algoritmo di Kruskal, spiega perché è corretto e calcolane la complessità.
> **R:**
> **Idea.** Kruskal ordina gli archi in senso crescente di costo e li aggiunge a $T$ uno a uno, saltando quelli che formerebbero un ciclo (rilevato tramite Union-Find).
>
> **Correttezza.** Si basa sulla cut property: quando si aggiunge $(x,y)$, la componente di $x$ in $T$ forma il taglio $S$; poiché gli archi sono esaminati in ordine crescente, $(x,y)$ è l'arco di costo minimo che attraversa quel taglio, quindi appartiene a un MST. Quando invece un arco viene scartato, chiude un ciclo di cui è il massimo, ed è escludibile per la cycle property.
>
> **Complessità.** $O(m \log n)$: l'ordinamento degli archi domina ($O(m \log m) = O(m \log n)$), e le operazioni Union-Find con union by size costano complessivamente $O(m \log n)$ nel totale — nessuno dei due termini elimina l'altro.

> [!question] Domanda tipica d'esame — Differenza tra Prim e Dijkstra
> **D:** Qual è la differenza tra l'algoritmo di Prim e l'algoritmo di Dijkstra?
> **R:**
> **Analogia strutturale.** Entrambi usano una coda con priorità e l'operazione `decreaseKey`, con la stessa struttura generale a passi.
>
> **Differenza (la chiave).** Dijkstra usa come chiave la **distanza cumulativa** da $s$ (il costo del cammino da $s$ al nodo), per trovare i cammini minimi. Prim usa come chiave il **costo del singolo arco** di attacco all'albero corrente, per trovare l'MST.
>
> **Conseguenza.** Prim non produce un albero dei cammini minimi: un nodo distante da $s$ ma connesso all'albero tramite un arco di attacco molto economico viene incluso prima di nodi vicini ma raggiungibili solo con archi costosi.

> [!question] Domanda tipica d'esame — Pesi distinti: Kruskal e Prim coincidono sempre
> **D:** *(Vero o Falso)* «Se i pesi sono distinti allora l'algoritmo di Kruskal e quello di Prim calcolano lo stesso identico albero indipendentemente dal nodo s di partenza (sorgente) scelto dall'algoritmo di Prim.» *(Es. 1, V/F n. 1 — 23/09/2025)*
> **R:**
> **Risposta.** Vera.
>
> **Perché.** Con pesi distinti l'MST è **unico**: la dimostrazione completa (argomento di scambio sulla differenza simmetrica $T_1 \triangle T_2$) è nel box [[#Unicità dell'MST]], ed è la parte da esporre per prima se la domanda è aperta.
>
> **Osservazione.** Kruskal e Prim sono **entrambi corretti**, cioè restituiscono un MST. Se l'MST è unico, «un MST» e «l'MST» coincidono: qualunque loro esecuzione dà lo stesso albero, a prescindere dall'ordine di scansione degli archi e dalla sorgente scelta per Prim.
## Applicazione: Clustering di massima spaziatura
Un'applicazione diretta di Kruskal è il **clustering gerarchico per single-linkage**.

> [!quote] Definizione — k-clustering di massima spaziatura
> Dato un insieme $U$ di $n$ oggetti $p_1, \dots, p_n$, un **$k$-clustering** è una suddivisione di $U$ in $k$ gruppi non vuoti. La funzione distanza $d$ soddisfa le tre proprietà naturali:
> - $d(p_i, p_j) = 0 \iff p_i = p_j$ (*identità degli indiscernibili*);
> - $d(p_i, p_j) \geq 0$ (*non negatività*);
> - $d(p_i, p_j) = d(p_j, p_i)$ (*simmetria*).
>
> La **spaziatura** (*spacing*) di un clustering è la **minima distanza tra una qualsiasi coppia di punti che stanno in cluster diversi**. Il problema del **clustering di massima spaziatura** è: dato un intero $k$, trovare il $k$-clustering di spaziatura massima.

**Algoritmo (Single-linkage $k$-clustering).** La slide lo presenta nella forma *agglomerativa*:
1. si costruisce un grafo sull'insieme di vertici $U$, corrispondente a $n$ cluster (uno per oggetto);
2. si trova la coppia di oggetti più vicina tra quelle che stanno in **cluster diversi**, e si aggiunge un arco tra i due (fondendo i cluster corrispondenti);
3. si ripete $n-k$ volte, finché restano esattamente $k$ cluster.

> [!info] Osservazione chiave: è Kruskal
> Questa procedura **è esattamente l'algoritmo di Kruskal**, con l'unica differenza che ci si ferma quando le componenti connesse sono $k$ anziché $1$. Da cui la formulazione equivalente, quella che conviene citare all'esame: si calcola l'MST e si eliminano i $k-1$ archi più costosi.

> [!quote] Teorema — Ottimalità del k-clustering per single-linkage
> Sia $\mathcal{C}^*$ il clustering $C^*_1, \dots, C^*_k$ ottenuto eliminando i $k-1$ archi più costosi di un MST. Allora $\mathcal{C}^*$ è un $k$-clustering di **massima spaziatura**.

**Dimostrazione.** Sia $\mathcal{C}$ un qualsiasi altro $k$-clustering $C_1, \dots, C_k$; si vuole mostrare che la sua spaziatura non supera quella di $\mathcal{C}^*$.
1. La spaziatura di $\mathcal{C}^*$ è la lunghezza $d^*$ del $(k-1)$-esimo arco più costoso dell'MST — cioè il più costoso tra quelli eliminati.
2. Poiché $\mathcal{C}^* \neq \mathcal{C}$ e sono entrambe partizioni di $U$ in $k$ gruppi, esistono due oggetti $p_i, p_j$ che stanno nello **stesso** cluster di $\mathcal{C}^*$, diciamo $C^*_r$, ma in cluster **diversi** di $\mathcal{C}$, diciamo $C_s$ e $C_t$.
3. Il cluster $C^*_r$ è connesso nell'MST, quindi contiene un cammino da $p_i$ a $p_j$. Percorrendolo si parte da un nodo in $C_s$ e si arriva a un nodo in $C_t$: esiste quindi un arco $(p,q)$ del cammino i cui estremi cadono in **due cluster diversi** di $\mathcal{C}$.
4. Tutti gli archi di quel cammino appartengono all'MST e non sono stati eliminati, dunque hanno lunghezza $\leq d^*$ — è Kruskal ad averli scelti prima dei $k-1$ archi rimossi. In particolare $d(p,q) \leq d^*$.
5. La spaziatura di $\mathcal{C}$ è la minima distanza tra punti in cluster diversi di $\mathcal{C}$, quindi è $\leq d(p,q) \leq d^*$.

Perciò nessun $k$-clustering ha spaziatura superiore a $d^*$, che è la spaziatura di $\mathcal{C}^*$. $\square$

> [!info] Clustering gerarchico
> Eseguendo Kruskal fino alla fine (senza fermarsi a $k$ componenti) si ottiene implicitamente un **clustering gerarchico**: per ogni $k = n, n-1, \ldots, 1$, i cluster sono le componenti connesse dopo aver eliminato i $k-1$ archi più costosi dall'MST. Questo produce un **dendrogramma** — una struttura ad albero che mostra come i cluster si fondono al crescere di $k$.

> [!question] Domanda tipica d'esame — MST e clustering di massima spaziatura
> **D:** Come si usa l'MST per trovare il clustering di massima spaziatura? Perché funziona?
> **R:**
> **Procedura.** Si calcola l'MST del grafo completo sugli oggetti (con pesi $=$ distanze) e si eliminano i $k-1$ archi più costosi. Le $k$ componenti connesse risultanti sono il clustering di massima spaziatura.
>
> **Perché funziona.** La spaziatura del clustering ottenuto è la lunghezza del $(k-1)$-esimo arco più costoso dell'MST. Qualsiasi altro $k$-clustering deve avere due oggetti nello stesso cluster dell'MST ma in cluster diversi tra loro; il cammino tra questi due oggetti nell'MST ha tutti gli archi di lunghezza $\leq$ quella spaziatura, quindi la spaziatura di qualsiasi altro clustering non può superare quella del clustering ottenuto dall'MST.
>
> **Complessità.** Dominata dal calcolo dell'MST su un grafo completo: $O(n^2 \log n)$ con Kruskal, oppure $O(n^2)$ con Prim su array non ordinato (adatto perché il grafo è denso); l'eliminazione dei $k-1$ archi più costosi costa poi solo $O(k)$.
