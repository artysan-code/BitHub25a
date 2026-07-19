---
tags:
  - algoritmi
  - mst
  - esercizi
---
# Vero/Falso — Minimum Spanning Tree
*Esercizio 1 · Minimum Spanning Tree · 30 domande da 6 appelli (13/06/2024, 24/09/2024, 21/01/2025, 18/07/2025, 09/09/2025, 23/09/2025).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 13/06/2024, 24/09/2024, 21/01/2025, 18/07/2025, 09/09/2025, 23/09/2025.*
## Come leggere questo file
MST occupa l'Esercizio 1 in **tutti e sei** gli appelli qui raccolti, sempre con lo stesso schema da 11 punti: cinque affermazioni vero/falso indipendenti — punteggio granulare, un errore in una non compromette le altre — più una domanda aperta da max 5 righe (il «punto 2»). L'unica eccezione di forma è il 21/01/2025, che pone le sue cinque affermazioni nel linguaggio del confronto fra $S$ (albero dei cammini minimi) e $M$ (MST) invece che su un singolo $T$: stesso schema, notazione diversa, raccolto qui nel sotto-tema dedicato con la notazione chiarita in apertura.

Il tranello più ricorrente è la confusione fra **cut property** (archi dentro $T$, tagli) e **cycle property** (archi fuori $T$, cicli): il prof costruisce sistematicamente affermazioni che applicano la proprietà sbagliata, o la proprietà giusta ma su un dominio troppo ampio — «ogni ciclo» al posto di «il ciclo fondamentale», «ogni taglio» al posto di «un taglio». Il secondo tranello ricorrente è la conflazione fra MST e albero dei cammini minimi (SPT): due ottimizzazioni diverse — costo totale contro distanza dalla sorgente — che coincidono solo in casi speciali (pesi tutti uguali, grafo aciclico); è il sotto-tema più affollato del file.

Delle 36 affermazioni originarie (6 appelli × 6 item ciascuno) tre sono state escluse perché la loro sostanza è di Union-Find, non di MST — la complessità di Kruskal con QuickFind su grafo completo o su $m=\Theta(n\sqrt n)$: vivono in [[02 - Vero-Falso Union-Find]]. Delle 33 rimanenti, tre coppie sono la stessa domanda posta in appelli diversi con formulazione quasi identica, collassate qui in tre voci sole con entrambe le citazioni. Il totale è **30 voci distinte**, all'incirca metà vere e metà false: non fidarsi mai della prima lettura plausibile, ogni item va motivato per conto proprio.
## Cut property e suoi corollari
Le affermazioni di questo gruppo riguardano archi **dentro** $T$: quando sono forzati (bridge), quando sono solo "probabilmente" pesanti, e quanto si estende davvero la garanzia della cut property. Teoria di riferimento: [[03 - Minimum Spanning Tree#Cut property]] e, per l'enunciato formale, [[01 - Teoria MST#Enunciato della cut property]].
### 1. L'arco più leggero incidente a un nodo
*citazione: 18/07/2025 · Es. 1, aff. 2*

> Sia $v$ un nodo qualsiasi. L'arco più leggero incidente a $v$ fa parte sempre di un qualche MST di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È il taglio banale $S=\{v\}$ applicato alla cut property: il cutset di $S=\{v\}$ è esattamente l'insieme degli archi incidenti a $v$, e il suo minimo — l'arco più leggero incidente a $v$ — appartiene quindi a un qualche MST di $G$ (forma debole, nessuna ipotesi di pesi distinti richiesta).

> [!info]- Spiegazione
> La cut property garantisce, per un taglio $(S,V\setminus S)$ qualsiasi, che il minimo del cutset appartenga a **qualche** MST — nella forma non stretta, senza bisogno di pesi distinti. Con $S=\{v\}$, ogni arco con esattamente un estremo in $S$ ha per forza $v$ come estremo: il cutset coincide con gli archi incidenti a $v$.
>
> L'affermazione dice «un qualche MST», cioè la conclusione della forma **debole** (esistenza), non della forma forte (appartenenza a *ogni* MST, che servirebbe minimo stretto). Vale per ogni $v$ preso singolarmente: non garantisce che tutti gli archi più leggeri stiano contemporaneamente nello stesso MST.
>
> **Dove si perdono punti:** aggiungere l'ipotesi non richiesta di pesi distinti, o scrivere «appartiene a ogni MST» invece di «un qualche MST».
>
> **Corollario diretto** dell'enunciato formale della cut property chiesto in Es. 2 → [[01 - Teoria MST#Enunciato della cut property|Teoria MST · Enunciato della cut property]].
### 2. Un arco di T è il più leggero di almeno un ciclo?
*citazione: 09/09/2025 · Es. 1, aff. 4*

> Sia $T$ un MST di $G$ e sia $e$ un arco di $T$, allora l'arco $e$ è l'arco più leggero di almeno un ciclo in $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Se $e$ è un **ponte** (bridge) di $G$, non appartiene ad alcun ciclo: l'insieme dei cicli che lo contengono è vuoto, quindi $e$ non può essere il più leggero di "almeno un ciclo".
>
> **Controesempio.** Due triangoli $A,B,C$ e $D,E,F$ (archi interni tutti di peso $1$) uniti dal solo arco $C\text-D=5$. MST: $T=\{A\text-B,\ B\text-C,\ D\text-E,\ E\text-F,\ C\text-D\}$, costo $9$; $C\text-D$ è obbligato, essendo l'unico collegamento fra le due metà del grafo — rimuoverlo disconnette $G$: è un ponte. Preso $e=C\text-D\in T$: non partecipa a nessun ciclo di $G$, l'affermazione è falsa per vacuità.

> [!info]- Spiegazione
> L'errore è cercare, per simmetria con la cycle property (fuori $T$, cicli), una proprietà analoga per gli archi **dentro** $T$. Ma la duale corretta è la cut property: ogni $e\in T$ è il minimo del **taglio** indotto rimuovendo $e$ da $T$, non genericamente "il più leggero di un ciclo". Senza un percorso alternativo fra i due estremi di $e$, non esiste alcun ciclo che lo contenga.
>
> **Questo stesso grafo** (i due triangoli col ponte $C\text-D=5$) torna utile anche sotto — [[#3. Kruskal esclude sempre l'arco di peso massimo di G?]] usa la stessa costruzione da un'angolazione diversa: lì $C\text-D$ non è solo un ponte, è anche l'arco di peso massimo dell'intero grafo.
>
> **Dove si perdono punti:** applicare meccanicamente la cycle property a un arco dentro $T$ invece della cut property, e non riconoscere il caso-ponte come falsificazione per vacuità.
### 3. Kruskal esclude sempre l'arco di peso massimo di G?
*citazione: 24/09/2024 · Es. 1, aff. 2*

> L'albero restituito dall'algoritmo di Kruskal non contiene mai l'arco di peso massimo di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Se l'arco di peso massimo è un **ponte**, deve comparire in ogni spanning tree — MST incluso — indipendentemente da quanto sia costoso: nessuno scambio può eliminarlo, perché non esiste un ciclo alternativo che lo contenga.
>
> **Controesempio.** Stesso grafo di [[#2. Un arco di T è il più leggero di almeno un ciclo?]]: due triangoli $A,B,C$ e $D,E,F$ (archi interni peso $1$) uniti dal ponte $C\text-D=5$. In questo grafo $5$ è anche il peso **massimo assoluto** — nessun arco pesa di più. Kruskal accetta comunque $C\text-D$: è l'unico modo di connettere le due metà, e il suo MST lo contiene.

> [!info]- Spiegazione
> Caso limite ancora più diretto: se $G$ è già un albero (connesso, $n-1$ archi), l'unico spanning tree possibile è $G$ stesso, quindi anche l'MST — e contiene necessariamente l'arco di peso massimo di $G$, qualunque esso sia.
>
> L'unica proprietà che garantirebbe l'**esclusione** del massimo assoluto è la cycle property applicata a un ciclo di cui quell'arco sia il massimo — e un ponte non appartiene a nessun ciclo, quindi la cycle property non ha nulla su cui applicarsi.
>
> **Dove si perdono punti:** confondere "l'arco più pesante di un ciclo è escludibile" (cycle property, vera) con "l'arco più pesante del grafo è sempre escluso" (falsa in generale): il primo enunciato è locale al ciclo, il secondo è globale e ignora il caso ponte.
### 4. Gli archi esclusi da Kruskal pesano sempre più del minimo assoluto?
*citazione: 24/09/2024 · Es. 1, aff. 3*

> L'albero restituito dall'algoritmo di Kruskal ha la proprietà che tutti gli archi che non fanno parte della soluzione hanno un peso strettamente maggiore dell'arco di peso minimo di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Se il peso minimo di $G$ non è unico, alcuni archi che lo condividono possono comunque essere esclusi (chiudono un ciclo con altri archi già accettati di pari peso), pur pesando esattamente quanto il minimo assoluto — non strettamente di più.
>
> **Controesempio.** Triangolo $A,B,C$ con tutti gli archi di peso $1$ (il minimo assoluto del grafo è $1$, condiviso da tutti e tre). Kruskal ne accetta due, ad esempio $A\text-B$ e $B\text-C$, ed esclude $A\text-C$. L'arco escluso pesa $1$ — uguale al minimo assoluto, non strettamente maggiore.

> [!info]- Spiegazione
> È la stessa insidia del "minimo non stretto" vista più volte in questo file (cfr. [[#3. Cycle property in forma debole: tutti gli archi del ciclo sono ≤ w(f)]]): quando più archi condividono il valore minimo e sono in competizione sullo stesso ciclo, solo alcuni entrano nell'MST, e quelli esclusi non sono affatto "più pesanti" — sono semplicemente ridondanti a parità di peso.
>
> **Dove si perdono punti:** ragionare come se il peso minimo di $G$ fosse sempre unico; con pesi ripetuti l'esclusione di un arco dipende dall'ordine di scansione a parità di peso, non dal suo valore assoluto rispetto al minimo.
### 5. Con pesi distinti, un arco dell'MST è minimo di ogni taglio che attraversa?
*citazione: 13/06/2024 · Es. 1, punto 2*

> Sia $G$ un grafo non orientato e pesato con pesi distinti. Si consideri la seguente affermazione: Se l'arco $e$ appartiene all'unico MST di $G$, allora $e$ è l'arco di peso minimo di tutti i tagli che attraversa. Dire se l'affermazione è vera o falsa argomentando la risposta. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** La cut property garantisce che $e$ sia il minimo di **almeno un** taglio — quello indotto rimuovendo $e$ da $T$ — non di **ogni** taglio che $e$ attraversa: appartenere all'MST non blinda $e$ contro il confronto con qualunque altro arco incidente ai suoi estremi.
>
> **Controesempio.** Nodi $A,B,C,D$, pesi tutti distinti: $A\text-B=1$, $B\text-C=2$, $A\text-C=3$, $C\text-D=4$, $A\text-D=10$. Kruskal: accetta $A\text-B(1)$, poi $B\text-C(2)$, scarta $A\text-C(3)$ (ciclo), accetta $C\text-D(4)$, scarta $A\text-D(10)$ (ciclo). $T=\{A\text-B,\ B\text-C,\ C\text-D\}$, costo $7$, unico essendo i pesi distinti. Preso $e=C\text-D\in T$ e il taglio $S=\{C\}$: il cutset è $\{B\text-C=2,\ A\text-C=3,\ C\text-D=4\}$ ed $e=4$ **non** è il minimo — lo è $B\text-C=2$.

> [!info]- Spiegazione
> L'affermazione confonde la forma **esistenziale** della cut property (vera: $e\in T\Rightarrow$ esiste almeno un taglio di cui $e$ è il minimo — precisamente quello indotto dalla rimozione di $e$ da $T$) con una forma **universale** mai dimostrata (falsa: $e$ minimo di *ogni* taglio che attraversa). Un arco dell'MST può benissimo attraversare tagli "sfortunati" dove esistono alternative più leggere — l'importante è che *quell'arco specifico* le batta solo sul taglio che conta, quello che separa esattamente le due componenti ottenute togliendo $e$ da $T$.
>
> Nel controesempio, $C\text-D=4$ resta comunque giustificato: è il minimo del taglio $S=\{A,B,C\}$ contro $\{D\}$ (cutset $\{A\text-D=10,\ C\text-D=4\}$), che è il taglio indotto dalla sua rimozione da $T$. Sul taglio $S=\{C\}$, invece, $C\text-D$ non è nemmeno l'arco che la cut property userebbe per giustificarlo — è semplicemente uno dei tre archi del cutset, senza alcun ruolo speciale lì.
>
> **Dove si perdono punti:** dimostrare la falsità solo a parole ("non è detto") senza costruire il controesempio con un taglio esplicito dove il confronto fallisce.
>
> **Stesso appello, Es. 2**: la forma corretta della cut property — «esiste almeno un taglio», mai «ogni taglio» — è l'enunciato formale chiesto in [[01 - Teoria MST#Enunciato della cut property|Teoria MST · Enunciato della cut property]].
## Cycle property e la sua portata esatta
Le affermazioni di questo gruppo riguardano archi **fuori** $T$: fin dove arriva la garanzia della cycle property, e dove smette di valere. Teoria di riferimento: [[03 - Minimum Spanning Tree#Cycle property]].
### 1. f è il massimo di ogni ciclo che lo contiene, o solo del fondamentale?
*citazione: 18/07/2025 · Es. 1, aff. 1 · e 23/09/2025 · Es. 1, aff. 3*

Stessa affermazione, parafrasata fra i due appelli — stesso grafo campione usato indipendentemente in entrambe le fonti, segno che è l'esempio "di riferimento" del prof per questa trappola.

> Sia $T$ un MST di $G$ e sia $f$ un arco non di $T$. Allora $f$ è l'arco di peso massimo in tutti i cicli che lo contengono. *(18/07/2025)*

> Sia $T$ un MST di $G$ e sia $f$ un arco che non appartiene a $T$, allora $f$ è l'arco più pesante di ogni ciclo di $G$ che lo contiene. *(23/09/2025)*

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** La cycle property garantisce che $f$ sia massimo solo nel **ciclo fondamentale** indotto da $T\cup\{f\}$ (l'unico ciclo che si forma aggiungendo $f$ a $T$), non in ogni ciclo di $G$ che passa per $f$.
>
> **Controesempio.** Nodi $A,B,C,D$ con archi $A\text-B=1$, $B\text-C=1$, $A\text-C=2$, $A\text-D=5$, $C\text-D=5$ (due triangoli $ABC$ e $ACD$ incollati su $AC$). Kruskal: accetta $A\text-B$, $B\text-C$, scarta $A\text-C$ (ciclo), accetta $A\text-D$, scarta $C\text-D$ (ciclo): $T=\{A\text-B,\ B\text-C,\ A\text-D\}$, costo $7$. Per $f=A\text-C$: nel ciclo fondamentale $A\text-B\text-C\text-A$ (pesi $1,1,2$) $f$ è il massimo, ma nel ciclo $A\text-D\text-C\text-A$ (pesi $5,5,2$) $f$ è il **minimo** — basta questo secondo ciclo a falsificare l'affermazione.

> [!info]- Spiegazione
> La cycle property vale per un ciclo $C$ qualsiasi: il suo massimo può sempre essere escluso da un MST. Applicata a $(T,f)$, il ciclo coinvolto è quello **fondamentale**: $T$ è un albero, quindi $T\cup\{f\}$ contiene esattamente un ciclo, e la correttezza dell'MST forza $f$ a esserne il massimo. Su cicli **diversi** dal fondamentale la proprietà non dice nulla.
>
> Nel controesempio $f=A\text-C$ appartiene a due cicli: quello fondamentale rispetto a $T$ (dove è massimo, coerente con la teoria) e un secondo ciclo esterno, dove è minimo — proprio perché quel secondo ciclo non è il fondamentale, la teoria non lo vincola.
>
> **Dove si perdono punti:** dare per scontato che la cycle property valga su *ogni* ciclo passante per $f$, e costruire un controesempio vago invece di uno con nodi, archi e pesi verificabili a mano.
### 2. f fuori da T è il massimo di almeno un taglio?
*citazione: 23/09/2025 · Es. 1, aff. 4*

> Sia $T$ un MST di $G$ e sia $f$ un arco che non appartiene a $T$, allora l'arco $f$ è l'arco più pesante di almeno un taglio di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Non esiste un "duale" della cut property per gli archi fuori $T$: gli archi **dentro** $T$ sono ciascuno il minimo del taglio indotto dalla propria rimozione (cut property); gli archi **fuori** $T$ sono ciascuno il massimo del ciclo fondamentale che inducono (cycle property) — non il massimo di alcun taglio.
>
> **Controesempio.** Stesso grafo del punto precedente: $T=\{A\text-B,B\text-C,A\text-D\}$, $f=A\text-C=2\notin T$. Nei quattro tagli che separano $A$ da $C$ — $\{A\}$, $\{A,B\}$, $\{A,D\}$, $\{A,B,D\}$ — il massimo del cutset è sempre $A\text-D=5$ o $C\text-D=5$: $f$ non è mai il massimo di nessuno dei tagli che attraversa.

> [!info]- Spiegazione
> La dualità reale del modulo: cut property per gli archi dentro $T$ (tagli), cycle property per gli archi fuori $T$ (cicli). L'affermazione prova a costruire una proprietà ulteriore — "$f$ è il massimo di *qualche* taglio" — che non discende da nessuna delle due ed è in generale falsa.
>
> Verifica riga per riga sui quattro tagli che separano $A$ da $C$:
>
> | Taglio $S$ | Cutset | Arco massimo |
> |---|---|---|
> | $\{A\}$ | $A\text-B(1),\ A\text-C(2),\ A\text-D(5)$ | $A\text-D=5$ |
> | $\{A,B\}$ | $A\text-C(2),\ B\text-C(1),\ A\text-D(5)$ | $A\text-D=5$ |
> | $\{A,D\}$ | $A\text-B(1),\ A\text-C(2),\ D\text-C(5)$ | $D\text-C=5$ |
> | $\{A,B,D\}$ | $A\text-C(2),\ B\text-C(1),\ D\text-C(5)$ | $D\text-C=5$ |
>
> **Dove si perdono punti:** inventare una proprietà "per analogia" (dentro $T$ → tagli, quindi fuori $T$ → tagli?) senza verificarla contro la teoria; la duale vera per gli archi fuori $T$ riguarda i cicli, non i tagli.
### 3. Cycle property in forma debole: tutti gli archi del ciclo sono ≤ w(f)
*citazione: 09/09/2025 · Es. 1, aff. 3*

> Sia $T$ un MST di $G$ e sia $f$ un arco che non appartiene a $T$, allora l'aggiunta di $f$ a $T$ forma un ciclo e tutti gli archi del ciclo hanno un peso che è minore o uguale a quello di $f$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È la cycle property in forma non stretta. $T$ ha $n-1$ archi; aggiungendo $f\notin T$ si ottengono $n$ archi su $n$ nodi, quindi esattamente un ciclo (il ciclo fondamentale indotto da $f$).
>
> Per assurdo, sia $e\in C$ con $w(e)>w(f)$ (necessariamente $e\in T$, dato che $C\setminus\{f\}\subseteq T$). Allora $T'=(T\setminus\{e\})\cup\{f\}$ è ancora uno spanning tree di costo $w(T')=w(T)-w(e)+w(f)<w(T)$: assurdo contro la minimalità di $T$. Dunque ogni arco di $C$ soddisfa $w(\cdot)\leq w(f)$, non $<$: con un pareggio $w(e)=w(f)$ lo scambio darebbe $w(T')=w(T)$, non lo migliorerebbe.

> [!info]- Spiegazione
> **Perché il ciclo è unico:** due cicli distinti condividerebbero archi in modo da eccedere il conteggio $n$ archi su $n$ nodi — contraddizione. **Perché $\leq$ e non $<$:** la dimostrazione usa esplicitamente $w(e)>w(f)$ stretto per ottenere l'assurdo, coerente solo con la conclusione $\leq$ sul verso opposto, mai $<$.
>
> **Dove si perdono punti:** scrivere la forma stretta ($<$) invece di quella debole ($\leq$), oppure non giustificare perché il ciclo indotto da $T\cup\{f\}$ è unico.
## Pesi vincolati in {1, 2}: conteggi e limiti
Due affermazioni che sfruttano solo il conteggio degli archi di uno spanning tree ($n-1$, sempre), senza bisogno di cut o cycle property.
### 1. Il costo dell'MST è compreso tra n−1 e 2n−2
*citazione: 23/09/2025 · Es. 1, aff. 2*

> Si assuma che per ogni arco $e$ vale $w(e) \in \{1, 2\}$, e sia $T$ un MST di $G$. Allora ogni MST di $G$ costa almeno $n - 1$ e al più $2n - 2$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Ogni spanning tree ha esattamente $n-1$ archi. Sommando $n-1$ pesi in $\{1,2\}$:
> $$(n-1)\cdot 1 \le \sum_{e\in T} w(e) \le (n-1)\cdot 2 = 2n-2$$
> Bound raggiungibili: il minimo se tutti gli archi dell'MST pesano $1$, il massimo se pesano tutti $2$.

> [!info]- Spiegazione
> Non serve cut property, cycle property, né alcuna proprietà di ottimalità: il bound discende solo dal conteggio degli archi e dall'intervallo dei pesi ammissibili.
>
> **Dove si perdono punti:** invocare macchinari più pesanti quando basta il conteggio; l'ipotesi "$T$ è un MST" è ridondante — il bound vale per **qualunque** spanning tree, ottimo o no. Confronta col bound *più stretto* di [[#2. Pesi in {1,2} con almeno 3 archi di costo 1: il costo è al più 2n−4?|Costruzioni ed esecuzioni]], che con un'ipotesi aggiuntiva abbassa il tetto da $2n-2$ a $2n-4$.
### 2. Un arco fuori da T deve avere per forza peso 2?
*citazione: 09/09/2025 · Es. 1, aff. 2*

> Si assuma che per ogni arco $e$ vale $w(e) \in \{1, 2\}$, e sia $T$ un MST di $G$. Allora ogni arco del grafo che non appartiene a $T$ deve avere peso $2$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** La cycle property esclude solo l'arco di peso massimo (eventualmente non stretto) del **ciclo fondamentale**: se quel ciclo ha archi tutti di peso $1$, l'arco escluso pesa $1$, non $2$.
>
> **Controesempio.** Triangolo $A,B,C$ con $A\text-B=1$, $B\text-C=1$, $A\text-C=1$ (rispetta $w(e)\in\{1,2\}$, nessun arco usa il valore $2$). $T=\{A\text-B,\ B\text-C\}$ è un MST di costo $2$; l'arco escluso $A\text-C$ pesa $1$, non $2$.

> [!info]- Spiegazione
> Il ragionamento seducente: "un arco fuori $T$ è stato scartato per pesantezza, quindi deve valere il massimo disponibile". Ma la cycle property confronta $f$ solo con gli altri archi del **suo** ciclo fondamentale — confronto *locale*, non globale sull'intero intervallo $\{1,2\}$ dei pesi ammessi.
>
> **Dove si perdono punti:** confondere "massimo del proprio ciclo fondamentale" con "massimo dell'intervallo di pesi ammessi nel problema".
## Unicità dell'MST e confronto Kruskal/Prim
Tre affermazioni che ruotano tutte attorno allo stesso teorema — pesi distinti $\Rightarrow$ MST unico — lette da tre angolazioni diverse: indipendenza dalla sorgente di Prim, contronominale (alberi diversi $\Rightarrow$ pesi ripetuti), e invarianza del *peso* anche quando gli *alberi* differiscono.
### 1. Pesi distinti: Kruskal e Prim calcolano lo stesso albero, per ogni sorgente s
*citazione: 23/09/2025 · Es. 1, aff. 1*

> Se i pesi sono distinti allora l'algoritmo di Kruskal e quello di Prim calcolano lo stesso identico albero indipendentemente dal nodo $s$ di partenza (sorgente) scelto dall'algoritmo di Prim.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Pesi distinti $\Rightarrow$ MST unico (teorema di unicità): se esistessero $T_1\neq T_2$ MST distinti, nella differenza simmetrica $T_1\triangle T_2$ esiste, coi pesi distinti, un unico arco $e$ di peso minimo — sia $e\in T_1\setminus T_2$. Aggiungendo $e$ a $T_2$ si forma un ciclo $C$ con un altro arco $f\in T_2\triangle T_1$; per minimalità di $e$, $w(f)>w(e)$, quindi $T_2\cup\{e\}\setminus\{f\}$ costa meno di $T_2$ — assurdo.
>
> Con un solo MST possibile, ogni esecuzione corretta di Kruskal o Prim — qualunque sorgente $s$, qualunque ordine di scansione — restituisce necessariamente quell'unico albero.

> [!info]- Spiegazione
> La sorgente $s$ è un parametro d'esecuzione di Prim, non un ingrediente della definizione del problema: se l'MST è unico, ogni algoritmo corretto lo trova, indipendentemente da come sceglie fra archi — qui non ce n'è nemmeno bisogno, perché con pesi distinti non ci sono mai pareggi.
>
> **Dove si perdono punti:** asserire l'unicità senza il breve argomento di scambio, o trattare l'indipendenza dalla sorgente come ovvia invece che come conseguenza dell'unicità.
### 2. Alberi diversi da Kruskal e Prim implicano pesi ripetuti
*citazione: 24/09/2024 · Es. 1, aff. 5*

> Gli alberi restituiti dall'algoritmo di Kruskal e dall'algoritmo di Prim potrebbero non essere uguali. Ma in questo caso il grafo contiene più archi dello stesso peso.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È la contronominale esatta del teorema di unicità usato sopra: pesi distinti $\Rightarrow$ MST unico $\Rightarrow$ Kruskal e Prim calcolano lo stesso albero (cfr. voce precedente). Contronominale: se i due alberi differiscono, i pesi **non** possono essere tutti distinti — devono essercene almeno due uguali.

> [!info]- Spiegazione
> Stesso teorema di [[#1. Pesi distinti: Kruskal e Prim calcolano lo stesso albero, per ogni sorgente s]], letto al contrario: lì si parte dall'ipotesi "pesi distinti" e si conclude "stesso albero"; qui si parte dalla negazione della conclusione ("alberi diversi") per dedurre la negazione dell'ipotesi ("pesi ripetuti"). Una contronominale di un'implicazione vera è sempre vera — non serve una dimostrazione nuova, basta riconoscere la struttura logica.
>
> **Attenzione:** non è l'affermazione inversa "pesi ripetuti $\Rightarrow$ alberi diversi", che sarebbe falsa (pesi ripetuti sono compatibili con un MST comunque unico, se i duplicati non competono mai sullo stesso taglio o ciclo — cfr. [[03 - Minimum Spanning Tree#Unicità dell'MST]]).
>
> **Dove si perdono punti:** non riconoscere la contronominale e provare a ricostruire una dimostrazione da zero, rischiando di invertire per errore la direzione dell'implicazione.
### 3. Il peso dell'albero di Kruskal è sempre uguale al peso di quello di Prim
*citazione: 13/06/2024 · Es. 1, aff. 1*

> Il peso dell'albero calcolato con l'algoritmo di Kruskal è sempre uguale al peso di quello calcolato con l'algoritmo di Prim.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Attenzione: qui si chiede l'uguaglianza dei **pesi**, non degli **alberi** (che invece possono differire, cfr. voce precedente). Kruskal e Prim sono entrambi corretti: ciascuno restituisce *un* MST. Il peso di un MST è per definizione il minimo fra tutti gli spanning tree di $G$ — un valore univocamente determinato dal grafo, indipendente da quale specifico albero lo realizzi. Se due spanning tree hanno entrambi peso minimo, quel peso è lo stesso numero per entrambi, anche quando gli insiemi di archi differiscono.

> [!info]- Spiegazione
> Il punto delicato è distinguere due nozioni: "l'MST" come **valore** (il costo minimo, unico per definizione di minimo) e "l'MST" come **oggetto** (l'insieme di archi, che può non essere unico con pesi ripetuti). L'affermazione riguarda solo la prima nozione, ed è sempre vera per costruzione — è quasi tautologica una volta isolata la distinzione, ma va scritta esplicitamente per prendere il punto.
>
> Si confronti con [[#2. Alberi diversi da Kruskal e Prim implicano pesi ripetuti]]: lì gli **alberi** possono differire (se i pesi si ripetono), qui i **pesi totali** non possono mai differire — sono due affermazioni compatibili, non contraddittorie.
>
> **Dove si perdono punti:** rispondere "falsa" pensando (correttamente) che gli alberi possano differire, senza notare che la domanda riguarda il *peso totale*, non l'insieme di archi.
## Caratterizzazione degli alberi non ottimi
Coppia di affermazioni gemelle del 13/06/2024, entrambe sullo stesso schema — "se $T$ non è un MST, esiste uno scambio migliorativo" — ma con un dettaglio invertito che ne rovescia il verdetto: la prima chiede l'arco **più pesante** del ciclo (vera), la seconda l'arco **più leggero** (falsa). Utile leggerle di seguito.
### 1. Se T non è ottimo, esiste un arco di T massimo di un ciclo indotto
*citazione: 13/06/2024 · Es. 1, aff. 4*

> Se $T$ non è un MST di $G$ allora esiste un arco $e \in T$ e un arco $f \notin T$ tale che $e$ è l'arco più pesante del ciclo che si forma quando si aggiunge $f$ a $T$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È (nella sostanza) la contronominale della cycle property applicata a $T$: se $T$ non è minimo, esiste un arco $e \in T$ scambiabile con un arco $f \notin T$ per ottenere un albero di costo minore. Aggiungendo $f$ a $T$ si crea un ciclo, e $e$ ne deve essere l'arco di peso **massimo** — altrimenti lo scambio $T \cup \{f\} \setminus \{e\}$ non ridurrebbe il costo.
>
> **Esempio.** Triangolo $A,B,C$ con $A\text-B=1$, $B\text-C=10$, $A\text-C=5$. $T=\{A\text-B,\ B\text-C\}$ non è MST (l'alternativa $\{A\text-B,\ A\text-C\}$ costa $6<11$). Preso $f=A\text-C=5\notin T$: il ciclo formato è $A\text-B(1),B\text-C(10),A\text-C(5)$, e l'arco di $T$ più pesante del ciclo è $e=B\text-C=10$ — coerente con lo scambio migliorativo $T\setminus\{e\}\cup\{f\}$, di costo $1+5=6<11$.

> [!info]- Spiegazione
> Il criterio è essenzialmente il "test locale" di ottimalità per gli alberi ricoprenti: $T$ è minimo se e solo se **nessuno** scambio a un singolo arco lo migliora. Se $T$ non è minimo, un simile scambio migliorativo esiste per costruzione, e l'arco che *esce* da $T$ deve essere il massimo del ciclo indotto dall'arco che *entra* — altrimenti lo scambio non ridurrebbe il costo.
>
> **Dove si perdono punti:** confondere questo enunciato (vero, "più pesante") con la sua variante scorretta qui sotto ("più leggero") — sono l'una l'immagine speculare (e sbagliata) dell'altra.
### 2. Variante scorretta: l'arco aggiunto è il più leggero del ciclo che forma
*citazione: 13/06/2024 · Es. 1, aff. 5*

> Se $T$ non è un MST di $G$ allora esiste un arco $e$ che non appartiene a $T$ tale che $e$ è l'arco più leggero del ciclo che si forma in $T$ quando si aggiunge $e$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Qui il ruolo di "arco da controllare" è assegnato all'arco **aggiunto** $e\notin T$ (non a quello *tolto*, come nella voce precedente), e gli si chiede di essere il **più leggero** del ciclo — non il più pesante. Non è garantito: nulla impedisce che il ciclo formato contenga un arco di $T$ ancora più leggero di $e$.
>
> **Controesempio.** Stesso triangolo di sopra: $A\text-B=1$, $B\text-C=10$, $A\text-C=5$, $T=\{A\text-B,\ B\text-C\}$ (non MST). L'unico arco fuori $T$ è $e=A\text-C=5$. Il ciclo formato aggiungendolo a $T$ è $A\text-B(1),\ B\text-C(10),\ A\text-C(5)$: il più leggero è $A\text-B=1$, non $e=5$. Nessun arco fuori $T$ soddisfa la proprietà richiesta: l'affermazione è falsa.

> [!info]- Spiegazione
> Confronta con la voce precedente: lì il verdetto era vero perché l'arco corretto da controllare è quello che **esce** da $T$ (deve essere il massimo del ciclo). Qui la traccia chiede invece se l'arco che **entra** sia il minimo — e non c'è alcuna proprietà, cut o cycle, che lo garantisca: la cycle property parla di massimi di cicli, mai di minimi, e la cut property riguarda tagli, non cicli.
>
> Lo stesso identico grafo produce quindi un verdetto opposto a seconda che si chieda dell'arco *tolto* (max, vero) o dell'arco *aggiunto* (min, falso) — è la coppia di domande pensata apposta per punire chi non distingue le due direzioni dello scambio.
>
> **Dove si perdono punti:** scambiare questa variante con quella vera qui sopra; costruire un controesempio "a caso" invece di riusare consapevolmente lo stesso grafo per mostrare il contrasto.
## MST contro albero dei cammini minimi (SPT)
Sotto-tema più affollato del file: dieci voci, sei appelli. Il 21/01/2025 usa una notazione diversa dal resto — $S$ per l'albero dei cammini minimi (*shortest path tree*) con sorgente $r$, $M$ per un MST, entrambi di un grafo connesso a pesi positivi — e la manteniamo qui identica all'originale, invece di tradurla nel $T$ generico usato altrove nel file. Le voci 6-10 sono tutte e sole le cinque affermazioni di quell'appello; le voci 1-5 vengono dagli altri cinque.
### 1. Pesi uguali: ogni SPT è anche un MST
*citazione: 18/07/2025 · Es. 1, aff. 3 · e 21/01/2025 · Es. 1, aff. 2*

Stessa affermazione sostanziale, in due formulazioni: la prima parla di "pesi tutti uguali" a un valore qualsiasi, la seconda del caso particolare "non pesato" (pesi tutti $=1$) — un caso speciale del primo, stesso argomento.

> Se tutti i pesi di $G$ sono uguali, allora ogni albero dei cammini minimi di $G$ rispetto a una qualsiasi sorgente $s$ è anche un MST di $G$. *(18/07/2025)*

> Se $G$ è non pesato, ovvero tutti i pesi di $G$ sono $1$, allora $S$ è anche un minimum spanning tree di $G$. *(21/01/2025, con $S$ = SPT da sorgente $r$)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Ogni spanning tree ha esattamente $n-1$ archi; se tutti i pesi valgono una costante $c$ (qui $c=1$ nella versione 21/01/2025), ogni spanning tree costa $(n-1)c$ — lo stesso valore per tutti, quindi sono tutti MST simultaneamente. Un albero dei cammini minimi (BFS o Dijkstra da una sorgente qualsiasi) è per costruzione uno spanning tree, quindi rientra in questo insieme: è un MST, per ogni sorgente.

> [!info]- Spiegazione
> Argomento di puro conteggio, indipendente da cut/cycle property: con pesi costanti il costo totale non dipende da *quale* spanning tree si scelga, quindi la nozione di "minimo" collassa sull'intero insieme degli spanning tree.
>
> È l'**estremo opposto** dell'unicità dell'MST (pesi tutti distinti ⇒ MST unico, cfr. [[#1. Pesi distinti: Kruskal e Prim calcolano lo stesso albero, per ogni sorgente s|Unicità dell'MST]]): qui pesi tutti uguali fanno coincidere l'MST con **l'intero insieme** degli spanning tree.
>
> **Attenzione alla voce gemella ma falsa:** questa affermazione dice solo che $S$ *è un* MST (claim debole, vero). Non va confusa con "$S$ *è uguale a* un $M$ dato" — claim più forte, falso in generale → [[#6. S ed M possono differire anche a pesi tutti uguali]] qui sotto.
>
> **Dove si perdono punti:** invocare cut o cycle property invece del semplice conteggio; confondere questa forma debole con la forma forte (voce 6).
### 2. Pesi unitari: Prim calcola necessariamente anche uno SPT?
*citazione: 09/09/2025 · Es. 1, aff. 1 · e 13/06/2024 · Es. 1, aff. 2*

Stessa affermazione sostanziale — grafo non pesato equivale a pesi tutti unitari. La versione 2025 rende esplicito il quantificatore "necessariamente" che nella versione 2024 resta implicito nella forma dell'asserzione.

> Se tutti gli archi hanno peso $1$, allora l'algoritmo di Prim applicato su un nodo iniziale $s$ calcola un MST che è necessariamente anche un albero dei cammini minimi con sorgente $s$. *(09/09/2025)*

> Quando il grafo è non pesato, l'algoritmo di Prim restituisce un albero dei cammini minimi radicato sul nodo sorgente su cui è chiamato. *(13/06/2024)*

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Con pesi unitari ogni spanning tree è già un MST (voce precedente), ma le scelte di Prim fra archi a pari peso sono arbitrarie e non seguono l'ordine per livelli di una BFS.
>
> **Controesempio.** Triangolo $\{s,a,b\}$, archi $s\text-a=1$, $a\text-b=1$, $s\text-b=1$. Prim da $s$: al passo 1 il taglio $(\{s\},\{a,b\})$ ha candidati pari $s\text-a$, $s\text-b$; il tie-break sceglie $s\text-a$. Al passo 2 il taglio $(\{s,a\},\{b\})$ ha candidati pari $s\text-b=1$, $a\text-b=1$; sceglie $a\text-b$. Risultato $T=\{s\text-a,\ a\text-b\}$, costo $2$ — MST legittimo. Ma la distanza vera $s\to b$ è $1$ (arco diretto), mentre in $T$ il cammino $s\to a\to b$ vale $2$: $T$ non è un albero dei cammini minimi.

> [!info]- Spiegazione
> La parola critica è **"necessariamente"**: per falsificare un quantificatore universale basta un'esecuzione contro, non serve escluderle tutte. Il motivo strutturale: la chiave di Prim, $a[v]$, è il costo del **singolo arco** che collega $v$ all'albero corrente, non la distanza cumulativa da $s$ — quella è la chiave di Dijkstra.
>
> **Dove si perdono punti:** rispondere "Vera" pensando al caso più intuitivo (pesi uguali ⇒ comportamento BFS-like) senza costruire il controesempio esplicito sul tie-break.
### 3. Pesi in {1, 2}: Prim non è Dijkstra
*citazione: 18/07/2025 · Es. 1, aff. 4*

> Se per ogni arco $e$ vale $w(e) \in \{1, 2\}$, allora l'algoritmo di Prim applicato su un nodo iniziale $s$ calcola un MST che è anche un albero dei cammini minimi con sorgente $s$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Prim minimizza il peso del singolo arco che estende l'albero, non la distanza cumulativa da $s$: con pesi in $\{1,2\}$ questa differenza emerge già su un ciclo minuscolo.
>
> **Controesempio.** Cinque nodi $s,a,b,c,d$: catena $s\text-a=1$, $a\text-b=1$, $b\text-c=1$, $c\text-d=1$, chiusa dalla scorciatoia $d\text-s=2$. Prim da $s$ sceglie sempre l'arco di peso $1$ appena aperto su $d\text-s(2)$: $T=\{s\text-a,a\text-b,b\text-c,c\text-d\}$, costo $4$. In $T$ la distanza fra $s$ e $d$ è $1+1+1+1=4$, ma in $G$ la vera distanza è $2$ (arco diretto $d\text-s$).

> [!info]- Spiegazione
> Stessa trappola della voce precedente, spinta oltre: con pesi *tutti* uguali SPT $=$ MST vale banalmente, ma basta un solo valore diverso — anche solo $1$ contro $2$ — a rompere l'argomento di conteggio. Nel controesempio l'esclusione di $d\text-s=2$ è deterministica (cycle property: è l'unico massimo, stretto, del ciclo), quindi non è un caso limite fragile.
>
> **Dove si perdono punti:** estendere l'argomento di conteggio della voce 1 a pesi "quasi uguali"; costruire il controesempio senza scriverlo per esteso.
### 4. Prim da s è sempre anche uno SPT da s?
*citazione: 24/09/2024 · Es. 1, aff. 4*

> L'albero restituito dall'algoritmo di Prim invocato su una sorgente $s$ è anche un albero dei cammini minimi di $G$ rispetto alla stessa sorgente $s$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Versione generica (nessuna ipotesi sui pesi) delle due voci precedenti: se il claim è falso già coi pesi ristretti a $\{1\}$ o $\{1,2\}$, resta falso senza alcuna restrizione. Riusa uno qualunque dei due controesempi già costruiti.

> [!info]- Spiegazione
> Prim e Dijkstra condividono lo scheletro (coda con priorità, `decreaseKey`), ma la **chiave** è diversa: Prim usa $a[v]=$ peso del singolo arco d'attacco a $v$; Dijkstra usa $d[v]=$ distanza cumulativa da $s$. È questa differenza — non i valori specifici dei pesi — a rendere l'affermazione falsa in generale.
>
> **Dove si perdono punti:** provare a dimostrarla da zero invece di riconoscere che è la generalizzazione (falsa) di un caso già falsificato sopra.
### 5. Pesi negativi: si può usare Bellman-Ford per l'MST?
*citazione: 24/09/2024 · Es. 1, aff. 1*

> Se ci sono archi di peso negativo posso usare l'algoritmo di Bellman-Ford per calcolare un MST di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa, per due motivi indipendenti.** (1) Bellman-Ford calcola cammini minimi da una singola sorgente — un problema diverso dall'MST, non un suo sostituto in presenza di pesi negativi. (2) Anche restando nel problema giusto, i pesi negativi non sono un ostacolo per Kruskal o Prim: le dimostrazioni di cut e cycle property confrontano solo $w(e)$ con $w(f)$ (uno scambio ordinale), senza mai usare la non-negatività.

> [!info]- Spiegazione
> L'associazione mnemonica "pesi negativi → serve Bellman-Ford" è corretta per i cammini minimi (dove Dijkstra richiede pesi non negativi) ma **fuori luogo** per l'MST: Prim non è Dijkstra (cfr. le voci precedenti di questo sotto-tema) e non eredita il suo vincolo sul segno dei pesi. Kruskal, per parte sua, si limita a ordinare gli archi — l'ordinamento funziona identico con numeri negativi.
>
> **Dove si perdono punti:** applicare per riflesso l'associazione "pesi negativi ⇒ Bellman-Ford" senza verificare che qui il problema (MST) non è quello per cui Bellman-Ford è definito (cammini minimi).
### 6. S ed M possono differire anche a pesi tutti uguali
*citazione: 21/01/2025 · Es. 1, aff. 1*

> In generale $S$ ed $M$ possono essere alberi diversi, ma quando tutti i pesi di $G$ hanno valore $1$ allora è sempre vero che $S = M$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Con pesi tutti $1$, ogni spanning tree è un MST (voce 1) — quindi $M$ può essere **uno qualsiasi** di essi, non necessariamente lo stesso albero individuato da Dijkstra/BFS per $S$.
>
> **Controesempio.** Triangolo $r,a,b$, pesi tutti $1$. $S$ (SPT da $r$) $=\{r\text-a,\ r\text-b\}$ (entrambi diretti, distanza $1$). Scegliendo $M=\{r\text-a,\ a\text-b\}$ (anch'esso un MST valido, costo $2$ come ogni spanning tree): $S\neq M$, pur avendo lo stesso costo.

> [!info]- Spiegazione
> Il punto è distinguere questa affermazione (forte: "$S$ coincide con *questo* $M$", falsa) dalla voce 1 (debole: "$S$ *è un* MST", vera): con pesi uguali, ogni spanning tree — $S$ incluso — è un MST valido, ma "essere un MST" non implica "essere *l'unico* MST" né "coincidere con un $M$ scelto arbitrariamente altrove".
>
> **Dove si perdono punti:** confondere questa voce con la voce 1, rispondendo "Vera" perché si è già convinti (correttamente) che $S$ sia un MST — la domanda qui è un'altra: se $S$ coincide col *particolare* $M$ scelto, e non è garantito.
### 7. Ogni cammino in S è al più lungo quanto in M
*citazione: 21/01/2025 · Es. 1, aff. 3*

> Per ogni nodo $v$, il cammino da $r$ a $v$ in $S$ ha lunghezza minore o uguale di quella del cammino da $r$ a $v$ in $M$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** $S$ è per definizione l'albero dei cammini minimi: il cammino da $r$ a $v$ dentro $S$ ha lunghezza esattamente $d_G(r,v)$, la distanza vera nel grafo. Il cammino da $r$ a $v$ dentro $M$ è invece **un** cammino qualsiasi in $G$ (essendo $M\subseteq E$), quindi la sua lunghezza è per forza $\geq d_G(r,v)$ — nessun cammino può essere più corto della distanza minima.

> [!info]- Spiegazione
> L'argomento non richiede nulla sulla struttura specifica di $M$: vale perché **ogni** albero ricoprente induce, fra $r$ e $v$, un cammino che vive dentro $G$, e nessun cammino in $G$ può battere la distanza minima $d_G(r,v)$ per definizione. L'uguaglianza è possibile (se $M$ instrada $v$ esattamente come $S$), la disuguaglianza stretta nella direzione opposta mai.
>
> **Dove si perdono punti:** cercare un controesempio (non esiste); la voce va giustificata come proprietà sempre vera per definizione di distanza minima, non verificata caso per caso.
### 8. Un arco fuori da S è il più pesante del ciclo che forma con S?
*citazione: 21/01/2025 · Es. 1, aff. 4*

> Sia $f$ un arco di $G$ ma non di $S$. Allora $f$ è l'arco più pesante del ciclo che si forma quando si aggiunge $f$ ad $S$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Questa è la cycle property applicata a $S$ — ma $S$ non è un MST in generale, quindi non c'è alcuna garanzia che valga: $S$ ottimizza le distanze cumulative da $r$, non il peso dei singoli archi rispetto ai cicli che inducono.
>
> **Controesempio.** Nodi $r,a,c$: $r\text-a=2$, $r\text-c=3$, $a\text-c=2$. SPT da $r$: $d(a)=2$ (diretto), $d(c)=3$ (diretto, contro $2+2=4$ via $a$): $S=\{r\text-a=2,\ r\text-c=3\}$. Unico arco fuori $S$: $f=a\text-c=2$. Ciclo formato: $r\text-a(2),\ r\text-c(3),\ a\text-c(2)$. Il più pesante è $r\text-c=3$, **non** $f$.

> [!info]- Spiegazione
> La cycle property è un teorema sull'**MST**, dimostrato con un argomento di scambio che confronta i pesi totali di due spanning tree — non si applica a $S$, che è ottimo per un criterio completamente diverso (distanza cumulativa dalla sorgente). Qui $r\text-c=3$ resta nell'albero non perché sia leggero rispetto al ciclo, ma perché la via diretta batte la via indiretta $r\text-a\text-c$ sulla *somma* dei pesi lungo il cammino ($3<2+2=4$): un confronto cumulativo, non un confronto arco-contro-arco come richiede la cycle property.
>
> **Dove si perdono punti:** applicare la cycle property a $S$ per abitudine, senza controllare che l'ipotesi ("$T$ è un MST") non è soddisfatta.
### 9. Grafo aciclico: S coincide con M
*citazione: 21/01/2025 · Es. 1, aff. 5*

> Se $G$ non ha cicli, allora $S = M$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** $G$ è connesso per ipotesi; se non ha cicli è già esso stesso un albero. L'unico spanning tree di un albero è l'albero stesso: nessun arco è ridondante, nessuno può essere rimosso senza disconnettere. Quindi ogni SPT $S$ e ogni MST $M$ — essendo entrambi spanning tree di $G$ — devono coincidere con $G$, e dunque fra loro: $S=G=M$.

> [!info]- Spiegazione
> Caso degenere ma istruttivo: senza cicli non c'è alcuna scelta da fare, né per Dijkstra/BFS né per Kruskal/Prim — l'unico spanning tree disponibile è forzato. La domanda verifica che lo studente non applichi macchinari (cut/cycle property, argomenti di scambio) dove basta l'osservazione "non c'è scelta possibile".
>
> **Dove si perdono punti:** cercare comunque un'argomentazione elaborata invece di riconoscere il caso banale — quando $G$ è un albero, spanning tree, SPT e MST collassano tutti sullo stesso oggetto.
### 10. Il peso di S può superare il doppio del peso di M
*citazione: 21/01/2025 · Es. 1, punto 2*

> Si consideri la seguente affermazione: Esistono grafi $G$ per cui il peso totale di $S$ è maggiore di due volte il peso totale di $M$, dove il peso totale di un albero $T$ è la somma dei pesi degli archi di $T$. Dire se l'affermazione è vera o falsa motivando la risposta. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Nodi $r, v_1, v_2, v_3$. Archi diretti $r\text-v_1=r\text-v_2=r\text-v_3=6$, catena $v_1\text-v_2=1$, $v_2\text-v_3=1$.
>
> **MST.** Kruskal: $v_1\text-v_2(1)$, $v_2\text-v_3(1)$, poi un solo arco diretto per agganciare $r$ (costo $6$, uguale per tutti): $M=\{v_1\text-v_2,\ v_2\text-v_3,\ r\text-v_1\}$, peso $8$.
>
> **SPT da r.** Ogni $v_i$ è raggiunto in $1$ passo diretto (peso $6$); passare per un altro $v_j$ costerebbe $6+1=7>6$: la via diretta vince sempre. $S=\{r\text-v_1,\ r\text-v_2,\ r\text-v_3\}$, peso $18$.
>
> Confronto: $18 > 2\cdot 8 = 16$. L'affermazione è verificata da questo grafo.

> [!info]- Spiegazione
> **Perché la struttura funziona.** $S$ è costretto a pagare il prezzo pieno ($6$) per raggiungere *ciascuna* delle tre foglie separatamente, perché nessuna scorciatoia (peso $1$) batte mai il collegamento diretto sulla distanza cumulativa da $r$. $M$, al contrario, sfrutta le scorciatoie per collegare le foglie *fra loro* a costo quasi nullo, pagando il prezzo pieno una sola volta per agganciare l'intera catena a $r$.
>
> **Generalizzazione.** Con $k$ foglie invece di $3$ (tutte a distanza diretta $W$ da $r$, catena di scorciatoie di peso $\delta$ piccolo fra loro): $M\approx W+(k-1)\delta$, $S=kW$. Il rapporto $S/M\to k$ al crescere di $k$ e al decrescere di $\delta$: non solo si può superare il fattore $2$ richiesto dalla traccia, il divario fra i due pesi totali è **illimitato**.
>
> **Perché serve almeno 3 foglie.** Con solo $2$ foglie il rapporto resta sempre $<2$ (verificabile algebricamente): il fattore $2$ richiesto dalla domanda è la soglia minima che giustifica una costruzione a $3$ o più foglie, non a $2$.
>
> **Dove si perdono punti:** costruire un esempio con margine risicato (rapporto vicino a $2$ ma non sopra) senza verificarlo numericamente; dimenticare di dichiarare esplicitamente peso di $S$ e peso di $M$ prima del confronto finale.
## Complessità di Prim con heap di Fibonacci
Sotto-tema di una sola voce: quanto pesa il fattore logaritmico quando si applica a $n$ (le `deleteMin`) e non a $m$ (gli archi) — verdetto opposto rispetto al caso gemello su Kruskal, richiamato nella citazione sotto.
### 1. Θ(n√n) archi, Prim con heap di Fibonacci: complessità lineare?
*citazione: 23/09/2025 · Es. 1, aff. 5* — la domanda gemella su **Kruskal con QuickFind + union by size**, stesso $m=\Theta(n\sqrt n)$ ma verdetto opposto (**Falsa**), è di sostanza Union-Find e vive in [[02 - Vero-Falso Union-Find]], non qui.

> Se $G$ ha $\Theta(n\sqrt{n})$ archi, allora l'algoritmo di Prim che implementa la coda con priorità attraverso un heap di Fibonacci ha complessità lineare, ovvero $\Theta(n\sqrt{n})$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con heap di Fibonacci Prim costa $T(n,m)=n\cdot O(\log n)+m\cdot O(1)=O(n\log n+m)$. Con $m=\Theta(n\sqrt n)$: ogni potenza positiva di $n$ domina $\log n$, quindi $\sqrt n\gg\log n$ e $n\log n=o(n\sqrt n)$; dunque $T(n,m)=\Theta(n\sqrt n)=\Theta(m)$.
>
> Poiché $m=\Theta(n\sqrt n)\gg n$, la dimensione dell'istanza è $\Theta(n+m)=\Theta(m)$: $\Theta(m)$ è quindi **lineare** nella dimensione dell'input.

> [!info]- Spiegazione
> Formula generale (cfr. [[Formulario MST#Quale algoritmo su quale grafo]]): $\text{totale}=n\cdot C_{\text{deleteMin}}+m\cdot C_{\text{decreaseKey}}$; con l'heap di Fibonacci $C_{\text{deleteMin}}=O(\log n)$, $C_{\text{decreaseKey}}=O(1)$ ammortizzato.
>
> **Perché il caso gemello su Kruskal dà l'opposto** (falso, $\Theta(n\sqrt n\log n)$): Kruskal deve **ordinare** gli $m$ archi, $\Theta(m\log m)$, e con $m=\Theta(n\sqrt n)$ il fattore $\log n$ si applica direttamente a $m$, senza mai sparire — indipendentemente da quale Union-Find si scelga dopo. In Prim+Fibonacci, invece, il fattore logaritmico si applica solo a $n$ (le $n$ `deleteMin`), non a $m$: con $m\gg n\log n$ il totale collassa a $\Theta(m)$, lineare per davvero. Stesso numero di archi, due algoritmi, due verdetti opposti — dettagli del confronto nel file di Union-Find.
>
> **Dove si perdono punti:** applicare per analogia l'esito (falso) della domanda gemella su Kruskal; qui il fattore log si applica a una base diversa ($n$, non $m$) e va ricalcolato da zero.
## Analisi di sensitività: cosa succede se cambio un peso
Coppia di domande aperte, duali fra loro: abbassare un peso già dentro l'albero non può danneggiarlo; alzare un peso già escluso non può migliorarlo. Stesso schema argomentativo — confronto $w \leftrightarrow w'$ fra l'albero di partenza e un ipotetico concorrente migliore — applicato ai due versi opposti.
### 1. Abbassare il peso di un arco dentro l'MST
*citazione: 18/07/2025 · Es. 1, punto 2*

> Claim: Sia $G = (V, E, w)$ un grafo non orientato e pesato. Sia $T$ un MST di $G$ e sia $e$ un arco di $T$. Si consideri il grafo $G' = (V, E, w')$ ottenuto da $G$ abbassando il peso dell'arco $e$ a un valore $w'(e) < w(e)$. Allora $T$ è un MST anche di $G'$. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Sia $\Delta = w(e) - w'(e) > 0$. Per assurdo, se $T$ non fosse MST di $G'$ esisterebbe uno spanning tree $T'$ con $w'(T') < w'(T)$. Se $e \in T'$, entrambi i pesi calano di $\Delta$: $w(T') = w'(T') + \Delta < w'(T) + \Delta = w(T)$. Se $e \notin T'$: $w'(T') = w(T')$ e $w'(T) = w(T) - \Delta$, quindi $w(T') = w'(T') < w'(T) = w(T) - \Delta < w(T)$. In entrambi i casi $w(T') < w(T)$: assurdo, perché $T$ era MST di $G$. $\blacksquare$

> [!info]- Spiegazione
> L'intuizione ("abbassare il peso di un arco già scelto non può svantaggiarlo") è corretta ma non basta: serve escludere formalmente che un *altro* spanning tree scavalchi $T$ in $G'$, confrontando come cambia il peso di **entrambi** i contendenti passando da $w$ a $w'$.
>
> **Lettura alternativa via cut property.** Rimuovendo $e$ da $T$ si ottiene il taglio $(S,V\setminus S)$ di cui $e$ è l'**unico** arco di $T$ che lo attraversa; per la minimalità di $T$ in $G$, $e$ era già il minimo del cutset, e abbassarne il peso rinforza solo questa condizione.
>
> **Confronto con la voce duale** qui sotto ([[#2. Alzare il peso di un arco fuori dall'MST]]): stesso schema per assurdo, verso opposto — lì si indebolisce un arco già escluso, qui si rinforza un arco già incluso.
>
> **Dove si perdono punti:** scrivere solo il verdetto con l'intuizione, senza il confronto esplicito $w\leftrightarrow w'$ fra $T$ e l'ipotetico $T'$ migliore.
### 2. Alzare il peso di un arco fuori dall'MST
*citazione: 09/09/2025 · Es. 1, punto 2*

> Claim: Sia $G = (V, E, w)$ un grafo non orientato e pesato. Sia $T$ un MST di $G$ e sia $f$ un arco non in $T$. Si consideri il grafo $G' = (V, E, w')$ ottenuto da $G$ alzando il peso dell'arco $f$ a un valore $w'(f) > w(f)$. Allora $T$ è un MST anche di $G'$. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** $w'(T) = w(T)$ poiché $f \notin T$. Per ogni spanning tree $S$: se $f \notin S$, $w'(S) = w(S)$; se $f \in S$, $w'(S) = w(S) + (w'(f) - w(f)) > w(S)$. Dunque $w'(S) \geq w(S)$ per ogni spanning tree $S$. Se $T$ non fosse più MST di $G'$, esisterebbe $S$ con $w'(S) < w'(T) = w(T)$; ma allora $w(S) \leq w'(S) < w(T)$, cioè $S$ batterebbe $T$ già in $G$: assurdo.

> [!info]- Spiegazione
> **Seconda lettura, via cycle property.** Conseguenza diretta della forma debole della cycle property (→ [[#3. Cycle property in forma debole: tutti gli archi del ciclo sono ≤ w(f)]]): il ciclo fondamentale $C$ indotto da $f$ ha tutti gli archi $\leq w(f)$ (pesi originali). Alzare $w(f)$ **rafforza** questa disuguaglianza — quindi in $G'$ vale a maggior ragione $w'(e)\leq w(f)<w'(f)$ per ogni $e\in C\setminus\{f\}$: $f$ resta il massimo del proprio ciclo, quindi resta escludibile da $T$.
>
> **Verifica numerica.** Nodi $A,B,C,D$: $A\text-B=1$, $B\text-C=1$, $A\text-C=2$, $A\text-D=5$, $C\text-D=5$. $T=\{A\text-B,\ B\text-C,\ A\text-D\}$, costo $7$. Preso $f=C\text-D=5\notin T$ e alzato a $w'(C\text-D)=100$: $w'(T)=w(T)=7$ (invariato), mentre l'alternativa $T''=\{A\text-B,\ B\text-C,\ C\text-D\}$ passa da costo $7$ a $w'(T'')=1+1+100=102$. $T$ resta MST di $G'$.
>
> **Dove si perdono punti:** dimostrare solo $w'(T)=w(T)$ e fermarsi lì — necessario ma non sufficiente. Manca il confronto $w(S)\leq w'(S)$ per ogni concorrente $S$: senza quella disuguaglianza, "quindi $T$ resta MST" non è giustificato, è solo asserito.
>
> **Coppia citata come corollario** dell'enunciato formale della cut property in Es. 2 → [[01 - Teoria MST#Enunciato della cut property|Teoria MST · Enunciato della cut property]].
## Costruzioni ed esecuzioni
Due domande aperte che chiedono di descrivere un MST su una famiglia di grafi parametrica, non di eseguire Kruskal o Prim a mano: riconoscere **quale taglio** giustifica ogni scelta e tradurla in una formula chiusa.
### 1. MST su una griglia N×N
*citazione: 23/09/2025 · Es. 1, punto 2*

> Sia $N > 2$ un intero. Si consideri il grafo non orientato di $n = N^2$ nodi disposti su un piano a formare una griglia $N \times N$, dove ogni nodo è collegato ai suoi (al più) quattro nodi vicini orizzontalmente e verticalmente. In particolare il nodo in posizione $(i, j)$, con $i, j \in \{1, \ldots, N\}$, ha un arco verso il nodo $(i, j - 1)$ (se esiste) e verso il nodo $(i, j + 1)$ (se esiste) di peso $1$, e ha un arco verso il nodo $(i - 1, j)$ (se esiste) di peso $i - 1 + j$ e un arco verso il nodo $(i + 1, j)$ (se esiste) di peso $i + j$. Si descriva come è fatto un MST del grafo e si derivi una formula chiusa per il suo peso. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> L'MST è formato da tutti gli $N(N-1)$ archi orizzontali (peso $1$, minimo assoluto del grafo, connettono ogni riga in un cammino senza creare cicli), più — per ogni coppia di righe adiacenti $(i,i+1)$, $i=1,\ldots,N-1$ — l'unico arco verticale in colonna $j=1$, di peso $i+1$: è il minimo **stretto** del taglio che separa le prime $i$ righe dalle restanti $N-i$, quindi appartiene a ogni MST per la cut property.
>
> Peso totale:
> $$N(N-1) + \sum_{i=1}^{N-1}(i+1) = N(N-1) + \frac{(N-1)(N+2)}{2} = \frac{(N-1)(3N+2)}{2}$$
>
> **Verifica per $N=3$:** orizzontali $3\cdot 2=6$; verticali (colonna $1$, coppie $(1,2)$ e $(2,3)$) $2+3=5$; totale $11$. Formula: $\dfrac{2\cdot 11}{2}=11$. Coincide.

> [!info]- Spiegazione
> **Passo 1 — entrano tutti gli orizzontali.** Pesano tutti $1$, il minimo assoluto (ogni verticale pesa $i+j\geq 2$). In Kruskal vengono processati per primi; ciascuno collega due nodi della stessa riga senza mai chiudere un ciclo. Entrano tutti gli $N(N-1)$ archi, trasformando le $N$ righe in $N$ componenti connesse distinte.
>
> **Passo 2 — servono esattamente $N-1$ verticali, uno per coppia adiacente.** Un arco verticale esiste solo fra righe adiacenti: il "grafo delle righe" è esso stesso un cammino $1-2-\cdots-N$, nessuna libertà su quali coppie collegare.
>
> **Passo 3 — la colonna giusta è $j=1$, minimo stretto.** Fissata la coppia $(i,i+1)$, il taglio $S=\{\text{righe }1,\ldots,i\}$ ha per cutset esattamente i $N$ archi verticali fra riga $i$ e riga $i+1$, di pesi $i+1,i+2,\ldots,i+N$ (tutti distinti): il minimo è **stretto** a $j=1$, peso $i+1$, quindi per la cut property appartiene a **ogni** MST — l'MST è anche unico.
>
> **Verifica per $N=4$.** Orizzontali $4\cdot 3=12$; verticali (coppie $(1,2),(2,3),(3,4)$) $2+3+4=9$; totale $21$. Formula: $\dfrac{3\cdot 14}{2}=21$. Coincide.
>
> **Dove si perdono punti:** assumere "a occhio" che $j=1$ sia la colonna giusta senza il taglio $S=\{\text{righe }1,\ldots,i\}$ che isola i candidati; dimenticare che le righe non adiacenti non hanno alcun arco diretto, quindi gli $N-1$ verticali sono strutturalmente obbligati a collegare coppie adiacenti.
### 2. Pesi in {1,2} con almeno 3 archi di costo 1: il costo è al più 2n−4?
*citazione: 24/09/2024 · Es. 1, punto 2*

> Si consideri il caso in cui ogni arco $e$ di $G$ ha un costo $c_e \in \{1, 2\}$, e si assuma che ci siano almeno $3$ archi di costo $1$ in $G$. Si consideri la seguente affermazione: Il costo dell'MST di $G$ è al più $2n - 4$. Dire se l'affermazione è vera o falsa motivando la risposta. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Sia $G_1$ il sottografo dei soli archi di peso $1$: Kruskal li processa tutti prima di qualunque arco di peso $2$, quindi il numero di archi di peso $1$ effettivamente accettati nell'MST è pari al **rango** di $G_1$ (nel senso della teoria dei grafi: $n$ meno il numero di componenti connesse indotte da $G_1$ sui nodi coinvolti).
>
> Con **almeno 3** archi di peso $1$, il rango è **almeno 2**: il caso peggiore possibile è che i 3 archi formino esattamente un triangolo (l'unica configurazione di 3 archi con un ciclo), dove solo 2 sono indipendenti; in ogni altra configurazione (percorso, stella, archi disgiunti) il rango è 3, ancora più favorevole.
>
> Quindi l'MST include almeno $2$ archi di peso $1$ e al più $n-3$ archi di peso $2$ per i restanti:
> $$w(\text{MST}) \leq 2\cdot 1 + (n-1-2)\cdot 2 = 2 + 2n-6 = 2n-4$$

> [!info]- Spiegazione
> **Esempio che raggiunge il bound esattamente.** $n=4$: triangolo $A,B,C$ con $A\text-B=A\text-C=B\text-C=1$ (tre archi di costo $1$, il caso peggiore — formano un ciclo), più $A\text-D=2$ per agganciare il quarto nodo. MST: due lati del triangolo (costo $1+1=2$, il rango del triangolo è $2$) più $A\text-D=2$: totale $4$. Bound: $2n-4=2\cdot4-4=4$. Coincide esattamente — il bound è **tight**.
>
> **Perché serve il caso-triangolo per il worst case.** Con 3 archi di peso $1$ che *non* formano un ciclo (percorso o stella), tutti e 3 entrano nell'MST (rango $3$), rendendo il costo ancora più basso di $2n-4$. Il bound $2n-4$ è quindi valido sempre, ma tight solo quando i 3 (o più) archi leggeri si raggruppano nel modo più "sprecato" possibile — un ciclo che ne rende ridondanti tutti tranne 2.
>
> **Confronto col bound generico** (senza l'ipotesi "almeno 3 archi di costo 1"): → [[#1. Il costo dell'MST è compreso tra n−1 e 2n−2]] dà $2n-2$. L'ipotesi aggiuntiva stringe il tetto di esattamente $2$, cioè del costo dei due archi di peso $1$ che l'ipotesi garantisce comunque presenti nell'MST.
>
> **Dove si perdono punti:** dimenticare che "almeno 3 archi di costo 1" non garantisce che siano tutti e 3 nell'MST (potrebbero formare un ciclo) — il punto delicato è mostrare che ne bastano **2 indipendenti**, non che ne bastino 3 pari pari.
