---
tags:
  - algoritmi
  - mst
  - esercizi
---
# Teoria — Minimum Spanning Tree
*Esercizio 2 · MST · 4 domande da 2 appelli (26/06/2025, 02/02/2026).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 26/06/2025 e 02/02/2026.*
## Come leggere questo file
Nei due appelli analizzati MST occupa questo slot con lo stesso schema a tre punti: definire il problema, enunciare la cut property, e un terzo punto che alterna fra *usarla* (correttezza di Prim) e *dimostrarla*. I primi due sono usciti **identici parola per parola** — collassano in due voci sole, da imparare a memoria una volta. Il terzo cambia verbo ma non scheletro: ciclo o taglio indotto, lemma di intersezione ciclo-cutset per il secondo arco, confronto dei pesi, chiusura.

Trappole ricorrenti: confondere «esiste un MST» con «ogni MST» (serve il minimo *stretto*); nella dimostrazione, dimenticare il caso banale $e\in T$ o il lemma ciclo-cutset; nella correttezza di Prim, descrivere l'algoritmo invece di enunciarne l'invariante induttivo. Il vincolo delle cinque righe punisce chi non ha questi scheletri già pronti.
## Definizione formale del problema
Punto d'apertura di entrambi gli appelli, testualmente identico.
### Il problema del MST — grafo connesso, spanning tree, costo minimo
*citazione: 26/06/2025 · Es. 2, punto 1 · e 02/02/2026 · Es. 2, punto 1 — testo identico nei due appelli.*

> 1. Si definisca formalmente il problema. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dato un grafo non orientato e **connesso** $G=(V,E)$ con funzione peso $w:E\to\mathbb{R}$ sugli archi (pesi reali, non necessariamente positivi), il problema del **Minimum Spanning Tree** chiede di trovare $T\subseteq E$ tale che $(V,T)$ sia uno **spanning tree** di $G$ — sottografo **aciclico** e **connesso**, con $|T|=n-1$ archi — di costo totale minimo **fra tutti gli spanning tree di $G$**, dove
> $$w(T)=\sum_{e\in T}w(e).$$

> [!info]- Spiegazione
> Le clausole da citare esplicitamente. **«Connesso»** è un'ipotesi di *esistenza*: su un grafo sconnesso non esiste alcuno spanning tree (servirebbe una *minimum spanning forest*).
>
> **«Non orientato»** delimita l'ambito: Kruskal e Prim sono definiti su grafi non orientati; l'analogo diretto è l'*arborescenza di costo minimo*, problema diverso e fuori programma.
>
> La tripla **aciclico + connesso + $n-1$ archi** toglie l'ambiguità di «connette tutti i vertici» presa da sola, che un sottografo con archi ridondanti soddisferebbe pur non essendo un albero — e coi pesi negativi ammessi qui un arco ridondante può persino *abbassare* il costo, quindi l'esclusione deve venire dall'**aciclicità**, non da un argomento di costo.
>
> **«Minimo fra tutti gli spanning tree»**, non genericamente «il sottografo connettente più economico»: un insieme con meno di $n-1$ archi non è ammissibile anche se costa meno, perché non connette tutti i vertici.
>
> I **pesi reali, anche negativi**, restano ammessi: a differenza di Dijkstra, la correttezza di Kruskal e Prim discende dalla cut property, un confronto puramente ordinale fra $w(e)$ e $w(f)$, indifferente al segno (cfr. [[03 - Minimum Spanning Tree#Definizioni]]).
>
> **Dove si perdono punti:** omettere «connesso» fra le ipotesi; scrivere «costo minimo» senza «fra tutti gli spanning tree».
## Enunciato della cut property
Secondo punto, anch'esso identico nei due appelli: solo l'enunciato, senza dimostrazione.
### Taglio, cutset e l'arco di peso minimo
*citazione: 26/06/2025 · Es. 2, punto 2 · e 02/02/2026 · Es. 2, punto 2 — testo identico nei due appelli.*

> 2. Si enunci formalmente la proprietà del taglio (cut property). *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Sia $G=(V,E,w)$ connesso, non orientato, pesato, e sia $(S,V\setminus S)$ un **taglio** con $\emptyset\neq S\subset V$. Sia $D=\{(u,v)\in E: u\in S,\ v\notin S\}$ il **cutset** di $S$ (archi con **esattamente un** estremo in $S$) e sia $e$ l'arco di **peso minimo** in $D$. Allora **esiste** almeno un MST di $G$ che contiene $e$. Se $e$ è l'unico arco di peso minimo in $D$ (minimo **stretto**), allora $e$ appartiene a **ogni** MST di $G$.

> [!info]- Spiegazione
> Due dettagli tecnici da non abbreviare: il taglio va dichiarato **proprio** ($\emptyset\neq S\subset V$, cfr. [[03 - Minimum Spanning Tree#Taglio e cutset|taglio e cutset]]), e il cutset va definito con **«esattamente un estremo in $S$»** — «almeno un estremo» includerebbe anche gli archi interni a $S$, che il taglio non attraversano.
>
> **La distinzione fra «esiste un MST» e «ogni MST» è la clausola che vale i punti.** Con pesi ripetuti nel cutset un MST può prendere un altro arco di pari peso e restare ottimo, quindi «$e$ in ogni MST» senza l'ipotesi di minimo stretto è un enunciato falso — è lo stesso asterisco della batteria V/F del [[Formulario MST]]. La stessa distinzione regge la dimostrazione del punto seguente: la forma debole («esiste un MST») non richiede ipotesi sui pesi, la forte («ogni MST») richiede il minimo stretto → [[#Dimostrazione della cut property]]. Il punto chiede **solo l'enunciato**: infilarci l'argomento di scambio brucia le cinque righe.
>
> **Corollari già usciti come V/F**, tutti derivabili da questo enunciato: [[01 - Vero-Falso MST#1. L'arco più leggero incidente a un nodo|l'arco più leggero incidente a un nodo]], col taglio banale $S=\{v\}$ (18/07/2025, Es. 1, affermazione 2); le due domande di *sensitivity* su [[01 - Vero-Falso MST#1. Abbassare il peso di un arco dentro l'MST|abbassamento]] e [[01 - Vero-Falso MST#2. Alzare il peso di un arco fuori dall'MST|innalzamento]] del peso di un arco (18/07/2025 e 09/09/2025, punto 2 di entrambi); la trappola «$e$ è il minimo di *tutti* i tagli che attraversa» ([[01 - Vero-Falso MST#5. Con pesi distinti, un arco dell'MST è minimo di ogni taglio che attraversa?|13/06/2024, Es. 1, punto 2]]).
>
> **Dove si perdono punti:** scrivere «ogni MST» senza l'ipotesi di minimo stretto.
## Dimostrazione della cut property
L'unico dei due appelli a chiedere non di enunciare ma di *dimostrare* la proprietà — uscito una sola volta finora, ma cardine dello slot: lo stesso scheletro regge, a ruoli scambiati, anche la cycle property.
### L'argomento di scambio: costruire un secondo MST che contiene e
*citazione: 02/02/2026 · Es. 2, punto 3.*

> 3. Si fornisca una dimostrazione della proprietà del taglio. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Sia $(S,V\setminus S)$ un taglio ed $e$ il suo arco di peso minimo. Sia $T$ un MST qualsiasi: se $e\in T$ non c'è nulla da dimostrare, quindi si assuma $e\notin T$. Aggiungendo $e$ a $T$ si forma **esattamente un ciclo** $C$, che attraversa il cutset $D$ di $S$ nell'arco $e$; per la proprietà di intersezione ciclo-cutset $|C\cap D|$ è **pari**, quindi esiste un secondo arco $f\in T$, $f\neq e$, che attraversa lo stesso taglio. Essendo $e$ il minimo di $D$, $w(e)\leq w(f)$. Sia $T'=T-f+e$: rimuovere $f$ spezza l'unico ciclo (aciclico), e i due estremi di $f$ restano connessi passando per il resto di $C$ (connesso, $n-1$ archi, quindi spanning tree), con $w(T')=w(T)-w(f)+w(e)\leq w(T)$. Per minimalità di $T$ vale anche $w(T')\geq w(T)$, dunque $w(T')=w(T)$: $T'$ è un MST e contiene $e$. $\blacksquare$

> [!info]- Spiegazione
> Argomento di **scambio** (*exchange argument*): si parte da un MST $T$ arbitrario — il caso $e\in T$ va escluso esplicitamente, «$T$ MST qualsiasi» da sola non basta — e si costruisce $T'$ che contiene $e$ e non costa più di $T$; essendo $T$ già ottimo, $T'$ costa **uguale**, quindi è anch'esso un MST con $e$.
>
> Il passo delicato è l'**esistenza di $f$**: senza il lemma di [[03 - Minimum Spanning Tree#Intersezione ciclo-cutset|intersezione ciclo-cutset]] non c'è garanzia che $C$ contenga, oltre a $e$, un altro arco che attraversa il taglio. Il lemma dice $|C\cap D|$ pari: essendo $e\in C\cap D$ per costruzione e pari implica almeno 2 quando è almeno 1, $f$ esiste sempre — citarlo per nome, non ridimostrarlo, è la scorciatoia che tiene la dimostrazione in cinque righe. $T'$ resta spanning tree va argomentato su entrambe le proprietà: aciclico perché $f\in C$ e toglierlo spezza l'unico ciclo; connesso perché gli estremi di $f$ restano collegati dal resto di $C$, che include $e$.
>
> La dimostrazione data prova solo la forma **debole**: con pareggi nel cutset $w(e)\leq w(f)$ è non stretta, compatibile con l'uguaglianza, e non basta per «$e$ in ogni MST». Per la forma **forte** (→ [[#Enunciato della cut property]]) serve che $e$ sia l'**unico** minimo di $D$: allora $w(e)<w(f)$ stretta per ogni $f\neq e$, lo stesso argomento dà $w(T')<w(T)$ stretta, assurdo per ogni $T$ che non contiene $e$.
>
> **Variante non ancora uscita in questo slot, ma analoga naturale: la dimostrazione della cycle property** (cfr. [[03 - Minimum Spanning Tree#Cycle property]]). Stesso scheletro coi ruoli scambiati: si parte da un MST $T$ che **contiene** $f$, il massimo di un ciclo $C$ dato; si **rimuove** $f$, inducendo un taglio con $f$ nel cutset; per lo stesso lemma esiste $e\in C\cap D$, $e\neq f$; $T'=T-f+e$ è ancora spanning tree ($e$ ricollega le componenti separate da $f$); infine $w(e)\leq w(f)$ perché $f$ è il **massimo del ciclo**, non il minimo del taglio — cambia solo la provenienza della disuguaglianza, non la direzione.
>
> **Dove si perdono punti:** affermare «esiste $f\neq e$» senza citare il lemma; dichiarare $T'$ spanning tree senza argomentare aciclicità *e* connessione; scrivere $w(T')<w(T)$ dimenticando che $w(e)\leq w(f)$ è non stretta in generale; applicare la forma «ogni MST» senza l'ipotesi di minimo stretto; omettere il caso banale $e\in T$.
## Correttezza di Prim via cut property
L'unico dei due appelli a chiedere di *usare* la cut property invece di dimostrarla — nell'appello successivo questo terzo punto è stato sostituito dalla dimostrazione appena vista.
### L'invariante induttivo sul taglio che cresce
*citazione: 26/06/2025 · Es. 2, punto 3.*

> 3. Si discuta in modo conciso e preciso come è possibile usare la proprietà del taglio per dimostrare la correttezza dell'algoritmo di Prim. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Ad ogni iterazione l'insieme $S$ dei nodi già in $T$ induce il taglio $(S,V\setminus S)$, e l'arco $e$ scelto da Prim è per costruzione il **minimo del cutset** di $S$. Si dimostra per induzione sul numero di archi aggiunti l'invariante **«$T\subseteq M$ per un qualche MST $M$»**. *Base:* $T=\emptyset\subseteq M$, banale. *Passo:* se $T\subseteq M$ ed $e$ è il minimo del cutset, per la cut property esiste un MST $M'\supseteq T\cup\{e\}$ — se $e\notin M$ si applica a $M$ lo scambio della cut property, e l'arco scartato sta nel cutset di $S$, quindi non è mai un arco di $T$, che ha **entrambi** gli estremi in $S$. Dopo $n-1$ passi $T$ è uno spanning tree con $T\subseteq M$ e $|T|=|M|=n-1$, dunque $T=M$: $T$ è un MST. $\blacksquare$

> [!info]- Spiegazione
> **Il taglio va identificato come «nodi già visitati contro non ancora visitati», ed è un unico taglio che cresce** di un nodo per volta. In Kruskal, invece, ogni arco accettato invoca un taglio *diverso* (la componente connessa di un suo estremo) — cfr. [[03 - Minimum Spanning Tree#Idea e correttezza|Kruskal e Prim usano la stessa proprietà su tagli diversi]]. Riciclare l'argomento dell'uno per l'altro è l'errore concettuale più frequente.
>
> **L'invariante è il nucleo tecnico.** Applicare la cut property $n-1$ volte in modo indipendente dice solo che *ciascun* arco, preso da solo, sta in *qualche* MST — non che la loro **unione** sia un MST, perché i testimoni potrebbero essere alberi diversi. È l'induzione a chiudere questo buco, e la chiusura finale $T=M$ segue da $T\subseteq M$, $|T|=|M|=n-1$ per un argomento di **cardinalità**, non per ovvietà: è il passaggio che manca quando si scrive di fretta.
>
> **Due dettagli spesso omessi.** L'arco scelto da Prim è *esattamente* il minimo del cutset, non genericamente «il più economico disponibile» — è questo a rendere applicabile l'ipotesi della cut property. E applicando lo scambio a un $M$ che non contiene $e$, l'arco $f$ scartato non è mai già in $T$: sta nel cutset (un estremo dentro e uno fuori $S$), mentre ogni arco di $T$ ha entrambi gli estremi in $S$. Con pesi ripetuti, l'invariante va letto come «esiste un $M$, che può cambiare passo per passo, con $T\subseteq M$», non come un $M$ fissato una volta per tutte.
>
> **Variante non ancora uscita in questo slot, ma analoga naturale: la correttezza di Kruskal** (→ [[03 - Minimum Spanning Tree#Correttezza]]). Stesso schema, tagli diversi: quando Kruskal **accetta** $(u,v)$, il taglio è la componente connessa corrente di $u$ — uno diverso a ogni arco accettato, non un unico $S$ che cresce — e $(u,v)$ resta il minimo del proprio cutset perché gli archi già scartati avevano entrambi gli estremi già connessi, e quelli non ancora esaminati pesano $\geq w(u,v)$ per l'ordinamento crescente. L'invariante è formalmente lo stesso, $T\subseteq M$, con la stessa chiusura per cardinalità.
>
> Perché il greedy funziona qui e non nel Weighted Independent Set: [[03 - Minimum Spanning Tree#L'idea: perché qui il greedy funziona]] e [[01 - Greedy e Interval Scheduling#Tecniche di dimostrazione dell'ottimalità]].
>
> **Dove si perdono punti:** descrivere Prim invece di dimostrarlo (nessun invariante esplicito); ridimostrare la cut property invece di *usarla*, bruciando le cinque righe.
