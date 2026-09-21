---
tags:
  - algoritmi
  - mst
slide: ["03"]
capitolo: "Kleinberg-Tardos cap. 4"
---
# Minimum Spanning Tree
Il **Minimum Spanning Tree** (MST), o **albero ricoprente minimo**, è uno dei problemi fondamentali su grafi pesati: dato un grafo connesso non orientato con pesi reali sugli archi, si cerca l'insieme di archi che connette tutti i nodi con costo totale minimo. Questa nota tratta le definizioni fondamentali, le due proprietà strutturali con le relative dimostrazioni, l'algoritmo di Kruskal (basato su [[02 - Union-Find]]) e l'algoritmo di Prim (basato su [[07 - Code con Priorità e Heap]]). Un'applicazione al clustering gerarchico conclude la nota.

> [!info] Le domande d'esame su MST stanno in palestra
> Questa nota è la **trattazione**; le 44 domande d'esame — 41 reali, con data, esercizio e sotto-punto — stanno in [[Esercizi 03 - Minimum Spanning Tree]], insieme alla legenda di come si leggono le citazioni. Nel corpo della nota trovi un link → **Palestra** alla fine di ogni argomento, che porta all'item corrispondente.
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

Questa è la frase con cui la slide *introduce* il problema (p. 3). La sua **formalizzazione** è invece la terna **input / soluzione ammissibile / misura** di p. 4, ed è il formato da riprodurre quando la traccia chiede «si definisca formalmente il problema». La terna compare in due sole slide del modulo — questa e `01_Interval_scheduling` — cioè proprio i problemi che ruotano nell'Esercizio 2: si impara una volta e si riusa su MST, IS e IP.

> [!quote] Definizione — Il problema MST come problema di ottimizzazione
> - **Input**: un grafo non orientato, connesso e pesato $G = (V, E)$ con pesi reali $c_e$ sugli archi.
> - **Soluzione ammissibile**: uno spanning tree $T$ di $G$, cioè un albero $T = (V, F)$ con $F \subseteq E$ che raggiunge tutti i vertici di $G$.
> - **Misura (da minimizzare)**: il peso (o costo) di $T$, cioè $c(T) = \sum_{e \in F} c_e$.

Le proprietà elencate riguardano **due oggetti distinti**: *non orientato, [[08 - Grafi e Visite#Cammini, cicli e connessione|connesso]], pesato* sono ipotesi su $G$, il grafo di input; *[[08 - Grafi e Visite#Alberi come grafi|albero]], quindi connesso e aciclico* sono requisiti su $T$, la soluzione. La parola «connesso» compare in entrambi con ruoli diversi: su $G$ garantisce che una soluzione **esista** — su un grafo sconnesso nessun insieme di archi raggiunge tutti i vertici, e il problema diventa quello della *spanning forest* — mentre su $T$ è parte della definizione di albero. $T$ non ha orientamento né pesi propri: li eredita da $G$, di cui è un sottografo.

Su $n$ vertici le proprietà *connesso*, *aciclico* e *$n-1$ archi* sono legate — **due qualsiasi implicano la terza** — ed è per questo che $|F| = n-1$ si cita come conseguenza e non come requisito; il [[08 - Grafi e Visite#Alberi come grafi|teorema sugli archi di un albero]] è dimostrato per induzione nel Modulo I. La minimalità, infine, è **relativa agli altri spanning tree** e non a sottografi arbitrari: un insieme di archi più leggero che non raggiunge tutti i vertici non è una soluzione migliore, è una soluzione non ammissibile.

> [!warning] Due dettagli che fanno la differenza nella definizione
> - **I pesi sono reali, quindi anche negativi.** Per l'MST non è un problema, a differenza dei cammini minimi — ed è il motivo per cui l'affermazione «con pesi negativi serve Bellman-Ford per l'MST» è falsa.
> - **Convenzione sul simbolo $T$, valida per tutta la nota.** Nella **definizione del problema** l'albero si scrive $T=(V,F)$ con $F \subseteq E$, e la misura è $c(T)=\sum_{e \in F} c_e$: così «$T$ è un albero» si dice senza giri di parole. Nel **resto della nota** — dimostrazioni comprese — si scrive $e \in T$, $f \notin T$, $T' = T^* \cup \{e\} \setminus \{f\}$, **identificando $T$ con il suo insieme di archi**. Non sono due notazioni in conflitto: è un'identificazione dichiarata qui una volta per tutte, la stessa che usano la slide e Kleinberg-Tardos, e serve perché gli scambi di archi si scrivono in modo leggibile solo così.

Nello scrivere la terna si perdono di solito due cose: **connesso** nell'input, e la **misura**, che è lo slot che salta quando si va di fretta.
### Conseguenze dirette del conteggio degli archi
Dal solo fatto che ogni spanning tree ha $n-1$ archi discendono i **bound sul costo**. Se tutti i pesi stanno in $\{1,2\}$, il costo è una somma di $n-1$ termini ciascuno pari a 1 o 2: al minimo $(n-1)\cdot 1 = n-1$, al massimo $(n-1)\cdot 2 = 2n-2$, e ogni altra combinazione cade in mezzo. È pura combinatoria: non serve che l'albero sia ottimo, e infatti il bound vale per **qualunque** spanning tree.

Diverso è affermare che il costo sia **esattamente** $n-1$: questo richiede che esista uno spanning tree fatto di **soli** archi di peso 1, cioè che il sottografo dei soli archi leggeri sia connesso e ricoprente. È la differenza fra un vincolo di **cardinalità** (quanti archi leggeri ci sono) e uno di **connettività** (dove stanno): gli archi di peso 1 possono essere moltissimi e concentrati in una sola zona, lasciando un nodo raggiungibile solo con archi di peso 2.

Per confutare un'affermazione di questo tipo serve un'istanza che **rispetti l'ipotesi**: se la claim parte da «gli archi di peso 1 sono almeno $2n$», il controesempio deve averne davvero almeno $2n$. Concentrandoli in una clique su $n-1$ nodi se ne ottengono $\binom{n-1}{2} = \frac{(n-1)(n-2)}{2}$ — il conteggio standard degli archi di un grafo completo, un arco per ogni coppia di nodi — e la condizione $\frac{(n-1)(n-2)}{2} \geq 2n$ vale da $n \geq 7$ in poi. È la stessa costruzione del callout [[08 - Grafi e Visite#Alberi come grafi|«$m \geq n-1$ non implica connessione»]] del Modulo I: molti archi, concentrati dove non servono.

> [!quote] Teorema — Numero di spanning tree (Cayley)
> Il grafo completo $K_n$ ha esattamente $n^{n-2}$ spanning tree distinti.

Il Teorema di Cayley mostra che il numero di spanning tree cresce esponenzialmente in $n$: la ricerca per forza bruta è impraticabile anche per grafi piccoli.

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Definizione formale del problema|definizione formale del problema — 26/06/2025, 02/02/2026 +1, Max 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Bound sul costo con pesi in {1, 2}|bound sul costo con pesi in {1, 2} — 23/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Pesi in {1,2}: molti archi di peso 1|pesi in {1,2}: molti archi leggeri non bastano — 08/09/2026, motiva in 5 righe]]
### Unicità dell'MST
L'MST **non è unico** in generale: se esistono archi con lo stesso peso, possono esistere più MST di costo uguale.

> [!quote] Proprietà — Unicità dell'MST
> Se tutti i pesi degli archi di $G$ sono **distinti**, allora l'MST è **unico**.

Sulla slide questa proprietà è lasciata come **«exercise: prove it»**, e in effetti nelle 24 tracce d'esame la sua dimostrazione non è mai stata richiesta: l'unicità compare sempre come **affermazione da giudicare** (per esempio «se tutti gli archi hanno peso intero positivo, l'MST è unico», Es. 1.1 n. 3 — 20/07/2026, falsa). Saperla dimostrare resta però utile all'orale ed è il lemma che giustifica tutte le domande del tipo «Kruskal e Prim calcolano lo stesso albero?». La dimostrazione è un argomento di scambio sulla differenza simmetrica.

La dimostrazione usa la **differenza simmetrica** di due insiemi, $A \triangle B = (A \setminus B) \cup (B \setminus A)$: gli elementi che stanno in uno solo dei due, esclusi quelli comuni. Applicata a due alberi, $T_1 \triangle T_2$ è l'insieme degli archi **su cui i due differiscono**, ed è vuota se e solo se $T_1 = T_2$. Serve per poter parlare del «più leggero fra gli archi in cui i due alberi differiscono», che è il punto di partenza dello scambio.

**Dimostrazione (per assurdo).** Si supponga che esistano due MST distinti $T_1 \neq T_2$.
1. La differenza simmetrica $T_1 \triangle T_2$ è non vuota. Sia $e$ l'arco di peso **minimo** in $T_1 \triangle T_2$: essendo i pesi distinti, $e$ è univocamente determinato. Senza perdita di generalità $e \in T_1 \setminus T_2$.
2. Aggiungendo $e$ a $T_2$ si crea un ciclo $C$. Non tutti gli archi di $C$ diversi da $e$ possono appartenere a $T_1$: altrimenti $C \subseteq T_1$, e $T_1$ conterrebbe un ciclo, contro il fatto che è un albero.
3. Esiste dunque $f \in C$, $f \neq e$, con $f \in T_2 \setminus T_1$, quindi $f \in T_1 \triangle T_2$.
4. Per la minimalità di $e$ nella differenza simmetrica e la distinzione dei pesi, $w(f) > w(e)$.
5. L'albero $T_2 \cup \{e\} \setminus \{f\}$ è ancora uno spanning tree e pesa $w(T_2) + w(e) - w(f) < w(T_2)$: contraddice la minimalità di $T_2$. $\square$

> [!warning] L'ipotesi «pesi distinti» serve nel passo 4, non prima
> Con pesi ripetuti il passo 1 fallisce (il minimo della differenza simmetrica può non essere unico) e soprattutto il passo 4 dà solo $w(f) \geq w(e)$, da cui $w(T_2 \cup \{e\} \setminus \{f\}) \leq w(T_2)$: si ottiene un **altro MST di pari costo**, non una contraddizione. È esattamente il modo in cui nascono gli MST multipli.

Pesi distinti è condizione **sufficiente ma non necessaria**: esistono grafi con pesi ripetuti e MST comunque unico (il caso limite è $G$ già albero). La caratterizzazione esatta si ottiene guardando i **massimi dei cicli**, non i pesi in sé.

> [!quote] Criterio — Caratterizzazione dell'unicità *(extra, non da slide)*
> Sia $T$ un MST di $G$. Allora $T$ è l'**unico** MST di $G$ se e solo se ogni arco $f \notin T$ è l'arco di peso **strettamente** massimo del proprio ciclo fondamentale (il ciclo che $f$ forma con $T$).

**Dimostrazione.** Se qualche $f \notin T$ pareggia con un arco $e$ del suo ciclo fondamentale, lo scambio $T \cup \{f\} \setminus \{e\}$ produce un secondo MST di pari costo, quindi $T$ non è unico. Viceversa, se ogni $f \notin T$ è massimo stretto del proprio ciclo, ogni scambio possibile aumenta strettamente il costo, e per l'argomento sulla differenza simmetrica visto sopra nessun altro MST può esistere. Questo criterio si applica anche quando i pesi si ripetono — è quello che serve, ad esempio, nella domanda sulla **griglia $N \times N$** più avanti, dove gli archi orizzontali sono tutti di peso $1$ eppure l'MST è unico.

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

La formulazione è quella letterale della slide, ed è volutamente informale; la definizione generale di [[08 - Grafi e Visite#Cammini, cicli e connessione|ciclo come cammino chiuso]] sta nel Modulo I. Se la traccia chiede la definizione di ciclo come oggetto formale, va aggiunto ciò che la slide lascia implicito: i nodi $a, b, \ldots, z$ sono **a due a due distinti** (il ciclo si chiude solo sull'ultimo arco $z$-$a$). Senza quel vincolo la scrittura descriverebbe un qualsiasi cammino chiuso, che può ripassare su nodi e archi già visitati — e l'intersezione ciclo-cutset, che si dimostra contando gli attraversamenti del confine, vale comunque, ma la nozione non sarebbe più quella usata nelle due property.

![[mst_ciclo.png]]
Il ciclo $C$ è evidenziato in **rosso**. Nota che il grafo è lo stesso delle due figure che seguono: prima ci si mette sopra un ciclo, poi un taglio, poi si sovrappongono i due per vedere l'intersezione. Tenere lo stesso grafo campione per tutti e tre i passaggi è il motivo per cui questa sequenza di slide funziona — leggile in fila.
### Taglio e cutset
> [!quote] Definizione — Taglio e cutset
> Un **taglio** (*cut*) è un sottoinsieme di nodi $S \subseteq V$; la slide aggiunge tra parentesi la formulazione equivalente «*a volte definito come una partizione di $V$ in $S$ e $V \setminus S$*». Il **cutset** $D$ corrispondente al taglio $S$ è il sottoinsieme degli archi con **esattamente un** estremo in $S$:
> $$D = \{\, e = \{u,v\} \in E \;:\; |e \cap S| = 1 \,\}$$

Due dettagli che la slide lascia impliciti. Il grafo è **non orientato**, quindi l'arco è la coppia *non ordinata* $\{u,v\}$: la condizione va scritta come $|e \cap S| = 1$, mentre la forma $\{(u,v) : u \in S, v \notin S\}$ con la coppia ordinata suggerisce un orientamento che qui non esiste. E il taglio è significativo solo per $\emptyset \neq S \subset V$: con $S = \emptyset$ o $S = V$ il cutset è vuoto e la cut property non ha archi a cui applicarsi.

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

> [!warning] «Pari» non vuol dire «due»
> La figura mostra un'intersezione di 2 archi, ed è facile memorizzare la proprietà come «si intersecano in due archi». È falso: il numero è **pari**, e può essere 0, 2, 4, … Sullo stesso grafo, con lo stesso taglio $S=\{4,5,8\}$, il ciclo $1\text{-}6\text{-}5\text{-}3\text{-}4\text{-}8\text{-}7\text{-}1$ interseca il cutset in **quattro** archi: $6\text{-}5$ (entro in $S$), $5\text{-}3$ (esco), $3\text{-}4$ (entro), $8\text{-}7$ (esco) — due ingressi e due uscite. Un ciclo interamente contenuto in $S$ o interamente fuori, come $6\text{-}7\text{-}1\text{-}6$, dà invece intersezione **0**.
>
> Si noti anche che **il cutset non ha un verso**: un arco vi appartiene se ha esattamente un estremo in $S$, indipendentemente dal fatto che percorrendo il ciclo lo si attraversi entrando o uscendo. Invertendo il senso di percorrenza, ingressi e uscite si scambiano ma $C \cap D$ resta lo stesso insieme; il conteggio degli attraversamenti serve solo a *dimostrare* la parità.

> [!warning] Perché questa proprietà viene prima di tutto il resto
> Sembra un tecnicismo, ma è **il perno delle dimostrazioni di entrambe le proprietà**: è ciò che garantisce l'esistenza del *secondo* arco da usare nello scambio. Senza di essa, aggiungendo $e$ a $T^*$ si otterrebbe un ciclo, ma non si potrebbe affermare che in quel ciclo esiste un altro arco che attraversa lo stesso taglio — e lo scambio non si potrebbe fare. All'esame è quindi il lemma da citare, non da saltare.
## Cut property e Cycle property
Queste due proprietà sono il **cuore della correttezza** degli algoritmi greedy per l'MST.
### Cut property
> [!quote] Proprietà — Cut property (proprietà del taglio)
> Sia $S$ un qualsiasi sottoinsieme di nodi, e sia $e$ **un** arco di **costo minimo** con esattamente un estremo in $S$ (un arco di costo minimo del cutset di $S$). Allora esiste un MST che **contiene** $e$.

L'enunciato della slide dice *«let $e$ be a min cost edge»*, non *«the»*: se più archi del cutset condividono il peso minimo, la proprietà vale per **ciascuno** di essi preso singolarmente — ma su MST possibilmente diversi. Riprodurre l'articolo indeterminato è ciò che rende l'enunciato corretto anche in presenza di pareggi, e vale in entrambi i punti: *un* arco di costo minimo, ed *esiste un* MST. Con l'articolo determinativo l'enunciato diventa falso, ed è la variante gemella che ricorre nelle tracce.

Allo stesso modo va riprodotto **«esattamente un** estremo in $S$»: scrivere «un estremo in $S$» renderebbe l'enunciato vero anche per gli archi interni al taglio, che non appartengono al cutset.

Il caso del **minimo stretto** è un corollario utile ma distinto: se $e$ è l'**unico** arco di peso minimo del taglio, allora appartiene a *ogni* MST di $G$, perché nessun altro arco del cutset potrebbe sostituirlo senza aumentare il costo. Va detto solo se la traccia lo chiede.

**Dimostrazione (argomento di scambio).**
Sia $T^*$ un MST qualsiasi. Se $e \in T^*$ non c'è nulla da dimostrare; supponiamo dunque che $e = (u,v)$, con $u \in S$ e $v \notin S$, **non** appartenga a $T^*$.
1. $T^*$ è uno spanning tree, quindi contiene un cammino da $u$ a $v$: aggiungendo $e$ a $T^*$ si crea un **ciclo** $C$ in $T^* \cup \{e\}$.
2. L'arco $e$ appartiene sia al ciclo $C$ sia al cutset $D$ di $S$ (ha esattamente un estremo in $S$): dunque $C \cap D \neq \emptyset$. Per la proprietà di intersezione ciclo-cutset $|C \cap D|$ è **pari**, quindi $|C \cap D| \geq 2$: **esiste** almeno un altro arco $f \in C \cap D$ con $f \neq e$.
3. Poiché $f \in C$ e $f \neq e$, si ha $f \in T^*$. Si ponga $T' = T^* \cup \{e\} \setminus \{f\}$: rimuovere un arco da un ciclo non disconnette, e il conteggio degli archi resta $n-1$, quindi $T'$ è **ancora uno spanning tree**.
4. $f$ appartiene al cutset $D$ ed $e$ è un arco di costo minimo di $D$: dunque $c_e \leq c_f$, da cui $c(T') = c(T^*) + c_e - c_f \leq c(T^*)$.
5. $T^*$ è un MST, quindi nessuno spanning tree costa meno: vale $c(T') = c(T^*)$. Perciò $T'$ è un MST e contiene $e$. $\square$

La struttura è di **cinque mosse in quest'ordine**: si suppone che $T^*$ non contenga $e$ → si crea il ciclo → si ricava l'esistenza di $f$ dalla parità → si esegue lo scambio → si confrontano i costi. Quando la traccia concede 10 righe le mosse si distendono, quando ne concede 5 si comprimono, ma l'ordine non cambia. I due passaggi che **non possono mancare** sono la **parità dell'intersezione ciclo-cutset**, che è ciò che garantisce l'esistenza dell'arco $f$ da scambiare, e la **chiusura** $c(T')=c(T^*)$: dalla sola disuguaglianza $c(T') \leq c(T^*)$ non segue che $T'$ sia ottimo, serve invocare la minimalità di $T^*$.

> [!warning] Non è una dimostrazione per assurdo
> La slide la etichetta *«Pf. (exchange argument)»*: si **costruisce** esplicitamente un MST che contiene $e$, partendo da uno qualsiasi che non lo contiene. Non si assume una tesi falsa per derivarne una contraddizione. Scriverla come prova per assurdo è un errore di impostazione che il prof segna, perché tradisce il punto: la cut property è un enunciato **esistenziale** ($\exists$ un MST con $e$) e lo scambio è precisamente il testimone che lo realizza.

![[mst_exchange_argument.png]]
Come leggerla: le due macchie grigie sono $S$ e $V\setminus S$; i segmenti pieni sono gli archi di $T^*$, l'MST di partenza. L'arco **tratteggiato $e$** è quello che la cut property vuole dentro, e non c'è. Aggiungendolo si chiude un ciclo, che riattraversa il taglio in **$f$**: lo scambio $T' = T^* \cup \{e\} \setminus \{f\}$ toglie $f$ e mette $e$. Le due macchie restano collegate — è il punto che rende $T'$ ancora uno spanning tree.

> [!warning] La coppia gemella «+1 su ogni arco»: MST vero, min-cut falso
> Il prof ha chiesto la stessa perturbazione in due appelli consecutivi, su oggetti diversi e con **risposte opposte**:
> - su **MST** (20/07/2026): $T$ resta MST — tutti gli spanning tree hanno $n-1$ archi, l'aumento è uniforme;
> - su **min-cut** (30/06/2026, cfr. [[07 - Flussi di Rete (Max-Flow e Min-Cut)]]): il taglio minimo **può cambiare** — i tagli hanno cardinalità diverse, quindi $+1$ per arco penalizza di più i tagli con molti archi, e un taglio prima più costoso può diventare il minimo.
>
> Il discrimine da dire in una riga: **gli spanning tree hanno tutti lo stesso numero di archi, i tagli no.**

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Enunciato della cut property|enunciato della cut property — 26/06/2025, 02/02/2026 +1, Max 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Dimostrazione della cut property|dimostrazione della cut property — 02/02/2026, 08/09/2026, max 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Arco più leggero incidente a un nodo|arco più leggero incidente a un nodo — 18/07/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Arco di peso massimo e appartenenza all'MST|l'arco di peso massimo può essere obbligato — 28/09/2022]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Sensitivity: alzare il peso di un arco fuori dall'MST|sensitivity: alzare il peso di un arco fuori dall'MST — 09/09/2025, motiva in 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Sensitivity: abbassare il peso di un arco dentro l'MST|sensitivity: abbassare il peso di un arco dentro l'MST — 18/07/2025, motiva in 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Perturbazione uniforme: $+1$ su ogni arco|perturbazione uniforme: $+1$ su ogni arco — 20/07/2026, motiva in 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Esiste un duale della cut property per gli archi fuori T?|non esiste un duale della cut property per gli archi fuori T — 23/09/2025]]
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
### Dalla proprietà locale alla correttezza globale *(extra, non da slide)*
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

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Arco più leggero di un ciclo e appartenenza all'MST|arco più leggero di un ciclo non è garantito — 28/09/2022]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Peso di un arco fuori da $T$ rispetto agli archi di $T$|un arco fuori da $T$ non è più pesante di *tutti* gli archi di $T$ — 20/07/2026]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Caratterizzazione degli alberi non ottimi|caratterizzazione degli alberi non ottimi — 13/06/2024]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Massimo di un ciclo vs massimo di tutti i cicli|massimo di un ciclo vs massimo di tutti i cicli — 18/07/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Arco dell'MST e minimo del proprio ciclo|un arco dell'MST non è per forza il minimo di un ciclo — 09/09/2025, 27/09/2023]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Cut property e archi non minimi|cut property e archi non minimi — 13/06/2024, max 5 righe]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Pesi in {1, 2}: peso di un arco fuori da T|pesi in {1, 2}: un arco fuori T non deve avere per forza peso 2 — 09/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Archi del ciclo fondamentale rispetto a w(f)|tutti gli archi del ciclo fondamentale sono ≤ w(f) — 09/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Variante: f e i cicli di G che lo contengono|variante: f non è il più pesante di ogni ciclo che lo contiene — 23/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Unicità e pesi ripetuti|unicità e pesi ripetuti — 18/07/2022, 20/07/2026]]
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

La struttura dati [[02 - Union-Find]] mantiene le **[[08 - Grafi e Visite#Cammini, cicli e connessione|componenti connesse]]** di $T$ durante l'esecuzione:
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

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Numero di componenti dopo k archi accettati|il numero di componenti dopo k archi non è garantito n−k — 19/02/2024]]
### Correttezza
La correttezza di Kruskal segue direttamente dalla **cut property** e dalla **cycle property**; la slide dedica una figura a ciascuno dei due casi.
- Quando l'algoritmo **aggiunge** l'arco $(x, y)$: le componenti di $x$ e $y$ sono distinte. Sia $S$ l'insieme dei vertici appartenenti alla **componente connessa di $y$** nella soluzione corrente. L'arco $(x,y)$ attraversa il taglio $(S, V\setminus S)$; ogni altro arco che lo attraversa non è ancora stato esaminato, e poiché l'algoritmo scandisce gli archi in **ordine crescente di costo**, ha costo $\geq c_{xy}$. Dunque $(x, y)$ è un arco di costo minimo che attraversa quel taglio: per la **cut property** esiste un MST che lo contiene. Si noti che **nessun arco già selezionato attraversa questo taglio** — gli archi di $F$ incidenti a $S$ sono interni alla componente di $y$ — il che è esattamente l'ipotesi che rende applicabile l'[[#Dalla proprietà locale alla correttezza globale *(extra, non da slide)*|invariante di estendibilità]].
- Quando l'algoritmo **rifiuta** l'arco $(x, y)$: $x$ e $y$ sono già connessi nella soluzione corrente, quindi $(x, y)$ chiude un ciclo con il cammino già presente. Tutti gli archi di quel cammino sono stati aggiunti **prima**, dunque hanno costo $\leq c_{xy}$: $(x, y)$ è un arco di costo massimo in quel ciclo, e per la **cycle property** esiste un MST che **non** lo contiene.

> [!warning] «Esiste un MST senza $f$», non «$f$ non sta in nessun MST»
> Entrambe le proprietà sono enunciati **esistenziali**, e vanno riportate così. La cycle property non dice che l'arco massimo di un ciclo è escluso da *ogni* MST: se il massimo non è stretto (pesi ripetuti sul ciclo), quell'arco può benissimo comparire in qualche altro MST di pari costo. La forma «non appartiene ad alcun MST» vale solo aggiungendo l'ipotesi di **massimo stretto**, e simmetricamente per la cut property con il minimo stretto. È una delle imprecisioni più penalizzate all'orale.

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Perché un arco viene scartato|perché un arco viene scartato — 19/02/2024]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Perché un arco viene accettato|perché un arco viene accettato — 20/07/2026]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Kruskal: archi guardati e condizione di arresto|kruskal non finisce dopo $n-1$ archi *guardati* — 20/07/2026]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#MST e arco più pesante di G|l'MST può contenere l'arco più pesante di G — 24/09/2024]]
### Complessità
| Operazione                                | Costo                                      |     |
| ----------------------------------------- | ------------------------------------------ | --- |
| Ordinamento degli archi                   | $O(m \log m) = O(m \log n)$                |     |
| $n$ `makeset`                             | $O(n)$                                     |     |
| $n-1$ `union`                             | dipende da UF                              |     |
| $2m$ `find`                               | dipende da UF                              |     |
| **Totale con QuickFind + union by size**  | $O(m \log n + m + n \log n) = O(m \log n)$ |     |
| **Totale con QuickUnion + union by size** | $O(m \log n + m \log n + n) = O(m \log n)$ |     |
| **Totale complessivo**                    | $\mathbf{O(m \log n)}$                     |     |

Nota: $\log m = O(\log n^2) = O(\log n)$ poiché $m \leq \binom{n}{2}$, quindi $O(m \log m) = O(m \log n)$. Per i dettagli sulle implementazioni di Union-Find e le loro complessità, si veda [[02 - Union-Find]].

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Numero di archi e complessità di Kruskal|il numero di archi non basta per la complessità — 18/07/2022]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Kruskal con Θ(n√n) archi|θ(n√n) archi non rende Kruskal lineare — 09/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Union-by-size su grafi densi|su grafi densi l'euristica union-by-size è ininfluente — 18/07/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#MST di una griglia N×N con pesi orizzontali 1 e verticali i+j|mST di una griglia N×N con pesi orizzontali 1 e verticali i+j — 23/09/2025, motiva in 5 righe]]
## Algoritmo di Prim
L'algoritmo di **Prim** (Jarník 1930, Dijkstra 1957, Prim 1959) costruisce l'MST partendo da un nodo sorgente $s$ e crescendo l'albero un arco alla volta, scegliendo sempre l'arco di costo minimo che ha esattamente un estremo nell'albero corrente.
### Idea e correttezza
Ad ogni passo si ha un insieme $S$ di nodi già esplorati (inizialmente $S = \{s\}$). Si aggiunge il **nodo più economico** raggiungibile da $S$, cioè il nodo $v \notin S$ per cui esiste un arco $(u, v)$ con $u \in S$ e $c_{uv}$ minimo tra tutti gli archi del cutset.

**Correttezza:** la slide liquida il punto con *«immediate consequence of the cut property, used exactly $n-1$ times»*. In forma rigorosa: a ogni passo $S$ è l'insieme dei nodi già raggiunti e nessun arco già selezionato attraversa il taglio $(S, V\setminus S)$ — sono tutti interni a $S$ — quindi si applica l'[[#Dalla proprietà locale alla correttezza globale *(extra, non da slide)*|invariante di estendibilità]]. L'arco scelto è il minimo di quel cutset, l'invariante si conserva, e dopo $n-1$ passi la soluzione parziale è uno spanning tree contenuto in un MST: coincide con esso.

![[mst_prim_taglio_iniziale.png]]
Il primo passo di Prim sul grafo campione: $s = A$ (cerchiato in blu) e la **curva rossa** è il taglio $(\{A\}, V\setminus\{A\})$. Gli archi che lo attraversano sono $A\text{-}B\ (7)$, $A\text{-}C\ (14)$, $A\text{-}D\ (30)$: il minimo è $A\text{-}B$, ed è quello che Prim aggiunge. A ogni iterazione la curva si allarga per inglobare il nodo appena preso — è la lettura visiva del «taglio unico che cresce».

> [!info] Kruskal e Prim usano la stessa proprietà su tagli diversi
> È la distinzione che chiarisce il rapporto fra i due algoritmi, ed è una domanda d'orale ricorrente.
> - In **Prim** il taglio è **uno solo e cresce**: $(S, V\setminus S)$ con $S$ l'insieme dei nodi già raggiunti, che si allarga di un nodo per volta.
> - In **Kruskal** i tagli sono **molti e cambiano**: ogni volta che si accetta un arco $(u,v)$, il taglio implicitamente invocato è quello che separa la componente connessa di $u$ dal resto. Non essendoci un unico $S$ che cresce, Kruskal può far crescere più «pezzi» di albero in parallelo e fonderli alla fine.
>
> In entrambi i casi l'arco scelto è il minimo del proprio cutset, quindi la cut property si applica identica; cambia solo *quale* taglio si sta considerando a ogni passo.

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Cut property e correttezza di Prim|cut property e correttezza di Prim — 26/06/2025, max 5 righe]]
### Implementazione con coda con priorità
L'implementazione naïve (per $n-1$ volte, scansione lineare di tutti gli archi) costa $O(nm)$. L'implementazione efficiente usa una [[07 - Code con Priorità e Heap#ADT CodaPriorità|coda con priorità]] (**min-heap**):

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
> La struttura di Prim è molto simile a quella di [[10 - Cammini Minimi e Dijkstra#Algoritmo di Dijkstra|Dijkstra]]: entrambi usano una coda con priorità e un'operazione `decreaseKey`. La differenza chiave è la **chiave usata**. In Dijkstra la chiave di $v$ è la **distanza totale** da $s$ (costo del cammino da $s$ a $v$); in Prim la chiave di $v$ è il **costo del singolo arco** che collega $v$ all'albero corrente. Prim non cerca il cammino più corto da $s$, ma l'arco di attacco più economico.
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

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Prim su grafo non pesato|prim su grafo non pesato non è BFS — 13/06/2024]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#MST e albero dei cammini minimi|mST e albero dei cammini minimi restano problemi diversi — 24/09/2024]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Pesi tutti uguali: SPT e MST|pesi tutti uguali: ogni SPT è anche un MST — 18/07/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Pesi in {1, 2}: Prim e albero dei cammini minimi|pesi in {1, 2}: Prim non dà per forza un albero dei cammini minimi — 18/07/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Variante: pesi tutti unitari, Prim e SPT|variante: pesi tutti unitari, Prim non dà per forza un SPT — 09/09/2025]]
### Complessità
Le operazioni sulla coda con priorità determinano la complessità totale. Si eseguono $n$ insert, $n$ deleteMin, e al più $m$ decreaseKey:

| Struttura per la coda | Insert | DeleteMin | DecreaseKey | Totale Prim |
|---|---|---|---|---|
| Scansione lineare naïve (senza PQ) | — | $O(m)$ per step | — | $O(mn)$ |
| **Array non ordinato** | $O(1)$ | $O(n)$ | $O(1)$ | $O(n^2)$ |
| **Heap binario** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(m \log n)$ |
| **[[07 - Code con Priorità e Heap#Heap di Fibonacci (cenni)|heap di Fibonacci]]** | $O(1)$ | $O(\log n)$ | $O(1)$ ammort. | $O(m + n \log n)$ |

Il calcolo con heap binario: $n \cdot O(\log n) + n \cdot O(\log n) + m \cdot O(\log n) = O(m \log n)$.
Il calcolo con heap di Fibonacci: $n \cdot O(1) + n \cdot O(\log n) + m \cdot O(1) = O(m + n \log n)$.

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Θ(n√n) archi e heap di Fibonacci|θ(n√n) archi e heap di Fibonacci — 23/09/2025]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Prim con array non ordinato|prim con array non ordinato — 20/07/2026]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Bound in funzione del grado massimo|bound in funzione del grado massimo — 27/09/2023]]
## Riepilogo e confronto degli algoritmi
| Algoritmo | Struttura dati | Complessità | Note |
|---|---|---|---|
| Kruskal | [[02 - Union-Find]] (Union by size) | $O(m \log n)$ | Ottimo su grafi sparsi; ordinamento domina |
| Prim (naïve) | Scansione lineare, senza PQ | $O(mn)$ | Semplice ma inefficiente |
| Prim (array) | Array non ordinato | $O(n^2)$ | Buono su grafi densi ($m=\Theta(n^2)$) |
| Prim (heap binario) | Min-heap binario | $O(m \log n)$ | Bilanciato; buono su grafi sparsi |
| Prim (Fibonacci) | [[07 - Code con Priorità e Heap#Heap di Fibonacci (cenni)|heap di Fibonacci]] | $O(m + n \log n)$ | Bound migliore in assoluto; su grafi densi pareggia l'array ($O(n^2)$) |

> [!info] Confronto Kruskal vs Prim
> Su grafi **sparsi** ($m = O(n)$) sia Kruskal che Prim con heap binario danno $O(n \log n)$; la scelta è indifferente. Su grafi **densi** ($m = \Theta(n^2)$), Kruskal richiede $O(n^2 \log n)$ (dominato dall'ordinamento), mentre Prim con array non ordinato dà $O(n^2)$ e Prim con heap di Fibonacci dà $O(n^2)$: in questo caso Prim è preferibile.
>
> **Dove serve davvero l'heap di Fibonacci.** Non sui grafi densi: lì $O(m + n\log n) = O(n^2)$, esattamente quanto il banale array non ordinato, che è molto più semplice da implementare. Il bound $O(m + n\log n)$ domina (in senso debole) sia l'array — $O(m + n\log n) \leq O(n^2)$, con uguaglianza solo a densità massima — sia l'heap binario — $O(m + n\log n) \leq O(m\log n)$, con uguaglianza solo sui grafi sparsi. Il vantaggio **stretto** su entrambe le alternative si materializza quindi nella **fascia intermedia** di densità, ad esempio $m = \Theta(n\sqrt n)$: lì Fibonacci dà $\Theta(n\sqrt n)$ contro $\Theta(n\sqrt n \log n)$ dell'heap binario e $\Theta(n^2)$ dell'array. È lo scenario della domanda d'esame del 23/09/2025 qui sopra.
> Nota teorica: esistono algoritmi asintoticamente migliori — $O(m \log \log n)$ (Cheriton-Tarjan 1976, Yao 1975), $O(m \cdot \alpha(m,n))$ (Fredman-Tarjan 1987), $O(m)$ randomizzato (Karger-Klein-Tarjan 1995) — ma Kruskal e Prim rimangono gli algoritmi standard per il corso.

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Caso speciale: pesi tutti uguali|caso speciale: pesi tutti uguali — 27/09/2023]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Kruskal: descrizione e correttezza|kruskal: descrizione e correttezza — domanda costruita]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Differenza tra Prim e Dijkstra|differenza tra Prim e Dijkstra — domanda costruita]]

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#Pesi distinti: Kruskal e Prim a confronto|pesi distinti: Kruskal e Prim coincidono sempre — 23/09/2025]]
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

→ **Palestra**: [[Esercizi 03 - Minimum Spanning Tree#MST e clustering di massima spaziatura|mST e clustering di massima spaziatura — domanda costruita]]
## Mappa nota ↔ slide
Riferimenti a `Materiale Didattico/Modulo II/Slide/03_mst_2025.pdf` (58 pagine), per studiare sulla slide tenendo la nota come riscontro.

| Sezione della nota | Slide |
|---|---|
| *(apertura)* | pp. 1-2 (copertina, «4.5 Minimum Spanning Tree») |
| L'idea: perché qui il greedy funziona | p. 7 (i tre algoritmi greedy) — il resto è *extra* |
| Definizioni | p. 3 (frase introduttiva) · **p. 4** (terna input / soluzione ammissibile / misura) |
| — Conseguenze dirette del conteggio degli archi | p. 3 (Teorema di Cayley) — i bound con pesi in $\{1,2\}$ sono *extra* |
| — Unicità dell'MST | **p. 6** (i tre triangoli e «exercise: prove it») |
| — Ciclo | p. 8 (prima metà) |
| — Taglio e cutset | p. 8 (seconda metà) |
| — Intersezione ciclo-cutset | **p. 9** (Claim + «Pf. by picture») |
| Cut property e Cycle property | **p. 10** (entrambi gli enunciati, con le due figure) |
| — Cut property | p. 10 (enunciato) · **p. 11** (Pf. exchange argument) |
| — Cycle property | p. 10 (enunciato) · **p. 12** (Pf. exchange argument) |
| — Dalla proprietà locale alla correttezza globale | *(nessuna slide: è il ponte che il deck salta)* |
| Algoritmo di Kruskal | p. 13 (titolo) · p. 14 (idea + remark sulla Union-Find) |
| — Pseudocodice | **p. 15** |
| — Esempio di esecuzione | **pp. 16-26** (demo passo-passo) |
| — Correttezza | **p. 27** (arco accettato) · **p. 28** (arco scartato) |
| — Complessità | **p. 29** |
| Algoritmo di Prim | p. 30 (titolo) · **p. 33** (algoritmo, Jarník-Dijkstra-Prim) |
| — Idea e correttezza | p. 33 · p. 32 (cut property richiamata) |
| — Implementazione con coda con priorità | p. 43 (seconda metà) |
| — Pseudocodice | **pp. 44-45** |
| — Esempio di esecuzione | **pp. 35-42** (demo con $s=A$) |
| — Complessità | p. 43 (prima metà, «running time») |
| Riepilogo e confronto degli algoritmi | p. 58 (bound teorici) — la tabella per implementazione è *extra* |
| Applicazione: Clustering di massima spaziatura | p. 46-47 · **p. 48** ($k$-clustering e spacing) · **p. 49** (single-linkage) · pp. 50-55 (dendrogramma) · **p. 56** (teorema di ottimalità) |

> [!info] Come si legge — tre cose utili quando ripassi sulla slide
> - **Le pagine 30-45 si autocontengono**: il deck ripete la terna formale di p. 4 a p. 31 e le due property di p. 10 a p. 32. Se vuoi ripassare solo Prim, quel blocco ti ridà definizione, cut property e algoritmo senza tornare indietro.
> - **Su Prim l'ordine diverge**: la nota va idea → implementazione → pseudocodice → esempio → complessità, la slide va idea (33) → esempio (35-42) → complessità *e* implementazione insieme (43) → pseudocodice (44-45). La p. 43 copre due sezioni che la nota tiene distanti.
> - **Quattro pagine non coperte**: p. 5 (applicazioni: network design, approssimazione per TSP e Steiner tree, bottleneck paths, cluster analysis), p. 34 (grafo euclideo completo), p. 57 (divisore «Extra Slides»), p. 59 (vuota). Solo la p. 5 ha contenuto: mai chiesta nelle tracce, ma è il tipo di inquadramento che all'orale apre una domanda.
