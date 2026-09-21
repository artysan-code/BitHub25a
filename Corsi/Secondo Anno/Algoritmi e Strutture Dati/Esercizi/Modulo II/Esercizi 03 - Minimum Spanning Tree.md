---
tags:
  - algoritmi
  - mst
  - esercizi
nota: "[[03 - Minimum Spanning Tree]]"
---
# Esercizi — Minimum Spanning Tree
Palestra della nota [[03 - Minimum Spanning Tree]]. Ogni item riporta la **traccia verbatim** con data, posizione nell'esercizio e limite di righe; la risposta modello sta in un callout **richiudibile**, da aprire solo dopo aver scritto la propria. Un item è chiuso quando la risposta esce senza aprire il callout.
MST è **l'argomento più testato dello scritto**: 43 item su 116 nel campione, e ruota sia in Esercizio 1 (vero/falso) sia in Esercizio 2 (teoria). Dei 44 item qui sotto, **41 sono domande d'esame reali**.

> [!info] Come leggere le citazioni delle domande d'esame
> Ogni callout `[!question]` riporta la posizione esatta nella traccia, perché **cambia il tipo di risposta richiesto**:
> - **Es. 1.1 n. K «quale è vera»** — la $K$-esima affermazione del blocco a scelta multipla: cinque affermazioni, **una sola vera**. Va individuata, non argomentata (il perché serve a te per scartare in fretta).
> - **Es. 1.2 «motiva in 5 righe»** — la claim singola che segue il blocco: qui il **perché fa parte della risposta**, e senza motivazione il punto non si prende.
> - **Es. 2.1 / 2.2 / 2.3** — le sotto-domande di teoria: tipicamente definizione formale, enunciato, dimostrazione. Il limite di righe, quando la traccia lo indica, è riportato accanto alla data.
>
> Quando una traccia **non** ha la struttura in uso oggi (3 esercizi da 11 punti: Es. 1 a scelta multipla, Es. 2 teoria, Es. 3 progettazione DP), la citazione lo dichiara: `formato Clementi` (altro docente, struttura diversa) o `formato ridotto` (2 esercizi, nessun punteggio). Senza marcatore la traccia ha esattamente la forma attuale — comprese quelle del 2022, che sono già in formato canonico. Il contenuto resta valido in ogni caso; a cambiare è la forma della risposta.

> [!warning] Le due forme in cui MST viene chiesto
> **Esercizio 1** — affermazioni da giudicare vero/falso, spesso seguite da «motiva in 5 righe». Quasi tutte ruotano attorno a un solo meccanismo: *cosa succede all'MST se perturbo i pesi*. Sono raggruppate qui sotto sotto «Cut property» e «Dalla cut property alla correttezza globale».
> **Esercizio 2** — la tripla **definizione → enunciato → dimostrazione**. La dimostrazione della cut property è stata chiesta per esteso più volte, con limiti diversi (5 righe il 02/02/2026, 10 righe l'08/09/2026): va saputa scrivere in entrambe le lunghezze.

> [!info] Regola — le domande di sensitivity sono tutte lo stesso lemma
> «Alzo il peso di un arco fuori da $T$», «abbasso il peso di un arco dentro $T$», «sommo $+1$ a ogni arco»: sono la stessa domanda travestita. Il criterio unico è
> $$c'(T) - c(T) \;\le\; c'(U) - c(U) \quad \text{per ogni spanning tree } U \;\Longrightarrow\; T \text{ resta un MST.}$$
> In parole: $T$ resta ottimo se la perturbazione **non lo penalizza più di quanto penalizzi qualunque concorrente**. Alzare un arco fuori da $T$ non tocca $c(T)$ e non può che alzare i concorrenti; abbassare un arco dentro $T$ abbassa $c(T)$ almeno quanto chiunque altro; il $+1$ uniforme aggiunge $n-1$ a **tutti** gli spanning tree, quindi non cambia nulla. Riconoscere il lemma fa risparmiare il tempo di ragionare da capo ogni volta.
## Definizioni e conteggio degli archi
### Definizione formale del problema
> [!question] Domanda d'esame — Definizione formale del problema
> **D:** «1. Si definisca formalmente il problema.» *(traccia 26/06/2025 · Es. 2.1 · «Max 5 righe» · anche 02/02/2026, 08/09/2026)*

> [!info]- Risposta modello
> **Input**: un grafo non orientato, connesso e pesato $G = (V,E)$ con pesi reali $c_e$ sugli archi.
> **Soluzione ammissibile**: uno spanning tree $T$ di $G$, cioè un albero $T=(V,F)$ con $F \subseteq E$ che raggiunge tutti i vertici di $G$.
> **Misura (da minimizzare)**: il peso di $T$, cioè $c(T) = \sum_{e \in F} c_e$.
### Bound sul costo con pesi in {1, 2}
> [!question] Domanda d'esame — Bound sul costo con pesi in {1, 2}
> **D:** *(Vero o Falso)* «Si assuma che per ogni arco e vale w(e) ∈ {1, 2}, e sia T un MST di G. Allora ogni MST di G costa almeno n − 1 e al più 2n − 2.» *(traccia 23/09/2025 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Ogni spanning tree di un grafo connesso a $n$ nodi ha esattamente $n-1$ archi. Con pesi in $\{1,2\}$ il costo è dunque una somma di $n-1$ termini in $\{1,2\}$, compresa fra $(n-1)\cdot 1 = n-1$ e $(n-1)\cdot 2 = 2n-2$. L'ipotesi «$T$ è un MST» non serve: il bound vale per ogni spanning tree.
### Pesi in {1,2}: molti archi leggeri non bastano
> [!question] Domanda d'esame — Pesi in {1,2}: molti archi leggeri non bastano
> **D:** «Claim: Sia $G$ un grafo non orientato con $n$ nodi dove il peso di ogni arco può essere 1 o 2. Se il numero di archi di peso 1 è almeno $2n$, allora il costo del MST di $G$ è esattamente $n-1$.» *(traccia 08/09/2026 · Es. 1.2 · «motiva in 5 righe»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Il costo è $n-1$ se e solo se esiste uno spanning tree di soli archi di peso 1, cioè se il sottografo degli archi leggeri è connesso e ricoprente. Il numero di archi di peso 1 non dice nulla su dove si trovano.
>
> **Controesempio.** Si concentrino gli archi di peso 1 in una clique su $n-1$ nodi e si lasci il nodo rimanente $v$ collegato solo da archi di peso 2. Ogni spanning tree deve raggiungere $v$ e usa almeno un arco di peso 2, quindi costa almeno $(n-2)\cdot 1 + 2 = n > n-1$.
## Cut property
### Enunciato della cut property
> [!question] Domanda d'esame — Enunciato della cut property
> **D:** «2. Si enunci formalmente la proprietà del taglio (cut property).» *(traccia 26/06/2025 · Es. 2.2 · «Max 5 righe» · anche 02/02/2026, 08/09/2026)*

> [!info]- Risposta modello
> Sia $S$ un qualsiasi sottoinsieme di nodi, con $\emptyset \neq S \subset V$, e sia $e$ **un** arco di costo minimo fra quelli con **esattamente un** estremo in $S$ (cioè un arco di costo minimo del cutset di $S$). Allora **esiste un** MST di $G$ che contiene $e$.
### Dimostrazione della cut property
> [!question] Domanda d'esame — Dimostrazione della cut property
> **D:** «3. Si fornisca una dimostrazione della proprietà del taglio.» *(traccia 02/02/2026 · Es. 2.3 · «max 5 righe» ; traccia 08/09/2026 · Es. 2.3 · «max 10 righe»)*

> [!info]- Risposta modello
> Sia $T^*$ un MST qualsiasi. Se $e \in T^*$ non c'è nulla da dimostrare; sia dunque $e=(u,v) \notin T^*$, con $u \in S$, $v \notin S$.
> Aggiungendo $e$ a $T^*$ si crea un ciclo $C$. L'arco $e$ sta sia in $C$ sia nel cutset $D$ di $S$; poiché un ciclo e un cutset si intersecano in un numero **pari** di archi, $|C \cap D| \geq 2$: esiste $f \in C \cap D$, $f \neq e$, con $f \in T^*$.
> Sia $T' = T^* \cup \{e\} \setminus \{f\}$: togliere un arco dal ciclo non disconnette e gli archi restano $n-1$, quindi $T'$ è uno spanning tree.
> Poiché $f$ attraversa il taglio ed $e$ è di costo minimo nel cutset, $c_e \leq c_f$, dunque $c(T') = c(T^*) + c_e - c_f \leq c(T^*)$.
> Ma $T^*$ è un MST, quindi $c(T') = c(T^*)$: $T'$ è un MST che contiene $e$. $\square$
### Arco più leggero incidente a un nodo
> [!question] Domanda d'esame — Arco più leggero incidente a un nodo
> **D:** *(Vero o Falso)* «Sia v un nodo qualsiasi. L'arco più leggero incidente a v fa parte sempre di un qualche MST di G.» *(traccia 18/07/2025 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Vero.
>
> **Perché.** È un corollario diretto della cut property applicata al taglio banale $S = \{v\}$: il cutset di $S$ è esattamente l'insieme degli archi incidenti a $v$, quindi il suo arco di costo minimo — l'arco più leggero incidente a $v$ — appartiene ad almeno un MST di $G$.
>
> Vale per **ogni** nodo $v$ preso singolarmente: applicando l'argomento a ciascun nodo si ottiene che l'arco più leggero incidente a ogni vertice è "salvabile" in un MST, non necessariamente nello stesso MST per tutti i nodi insieme.
### L'arco di peso massimo può essere obbligato
> [!question] Domanda d'esame — L'arco di peso massimo può essere obbligato
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G sono distinti, l'arco di peso minimo appartiene sempre all'MST T di G mentre l'arco di peso massimo non appartiene mai a T.» *(traccia 28/09/2022 · Es. 1.1 n. 1)*

> [!info]- Risposta modello
> Falsa.
>
> **Prima parte (corretta).** L'arco di peso minimo assoluto è il minimo di ogni taglio che attraversa, quindi per cut property appartiene a ogni MST, essendo i pesi distinti (minimo stretto in ogni taglio che lo contiene).
>
> **Controesempio alla seconda parte.** L'arco di peso massimo **può** appartenere all'MST: se è un **ponte** (l'unico collegamento tra due componenti del grafo), è obbligato in ogni spanning tree, MST incluso, indipendentemente dal suo peso.
>
> L'affermazione mischia due proprietà diverse: essere il minimo assoluto forza l'appartenenza (cut property), ma essere il massimo assoluto non forza l'**esclusione** — l'unica cosa che la garantirebbe è la cycle property applicata a un ciclo di cui l'arco è il massimo, e un ponte non appartiene a nessun ciclo.
### Sensitivity: alzare il peso di un arco fuori dall'MST
> [!question] Domanda d'esame — Sensitivity: alzare il peso di un arco fuori dall'MST
> **D:** *(Vero o Falso)* «Sia G = (V, E, w) un grafo non orientato e pesato. Sia T un MST di G e sia f un arco non in T. Si consideri il grafo G′ = (V, E, w′) ottenuto da G alzando il peso dell'arco f a un valore w′(f) > w(f). Allora T è un MST anche di G′.» *(traccia 09/09/2025 · Es. 1.2 · «motiva in 5 righe»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** $w'(T)=w(T)$ perché $f\notin T$. Per ogni spanning tree $S$: se $f\notin S$, $w'(S)=w(S)$; se $f\in S$, $w'(S)=w(S)+(w'(f)-w(f))>w(S)$. Quindi $w'(S)\geq w(S)$ sempre. Se $T$ non fosse più MST di $G'$, esisterebbe $S$ con $w'(S)<w'(T)=w(T)$; ma allora $w(S)\leq w'(S)<w(T)$, cioè $S$ batterebbe $T$ già in $G$: assurdo.
>
> È il duale della domanda qui sotto, «abbassare il peso di un arco dentro l'MST»: le due si risolvono con lo stesso schema.
### Sensitivity: abbassare il peso di un arco dentro l'MST
> [!question] Domanda d'esame — Sensitivity: abbassare il peso di un arco dentro l'MST
> **D:** «Claim: Sia G = (V, E, w) un grafo non orientato e pesato. Sia T un MST di G e sia e un arco di T. Si consideri il grafo G′ = (V, E, w′) ottenuto da G abbassando il peso dell'arco e a un valore w′(e) < w(e). Allora T è un MST anche di G′.» *(traccia 18/07/2025 · Es. 1.2 · «motiva in 5 righe»)*

> [!info]- Risposta modello
> $T$ resta un MST di $G'$: abbassare il peso di un arco già scelto non può renderlo svantaggioso.
>
> **Perché.** Sia $\Delta = w(e)-w'(e)>0$. Per assurdo, se $T$ non fosse più MST di $G'$ esisterebbe uno spanning tree $T'$ con $w'(T')<w'(T)$. Se $e\in T'$: entrambi i pesi calano di $\Delta$, quindi $w(T')<w(T)$. Se $e\notin T'$: $w'(T')=w(T')$ e $w'(T)=w(T)-\Delta<w(T)$, quindi ancora $w(T')<w(T)$. In entrambi i casi $T'$ batterebbe $T$ già in $G$: assurdo.
>
> Vale per pesi reali qualsiasi. Schema comune alle due domande di sensitivity: si confronta $T$ con un ipotetico $S$ migliore in $G'$, si osserva come cambia il peso di ciascuno passando da $w$ a $w'$, e si riporta la contraddizione **su $G$**, dove $T$ era ottimo per ipotesi.
### Perturbazione uniforme: $+1$ su ogni arco
> [!question] Domanda d'esame — Perturbazione uniforme: $+1$ su ogni arco
> **D:** «Claim: Sia $T$ un MST di $G$. Sia $G'$ il grafo ottenuto da $G$ aumentando il costo di ogni arco di esattamente 1. Allora $T$ è un MST anche per $G'$.» *(traccia 20/07/2026 · Es. 1.2 · «motiva in 5 righe»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Ogni spanning tree di $G$ ha **esattamente $n-1$ archi**, quindi passando a $G'$ il costo di *ogni* spanning tree aumenta della stessa quantità: $w'(S) = w(S) + (n-1)$ per ogni $S$. Una costante additiva uguale per tutti non altera l'ordinamento: $w'(T) \leq w'(S) \iff w(T) \leq w(S)$. Se $T$ era di costo minimo in $G$, lo resta in $G'$.
>
> La cardinalità costante $n-1$ è l'unico ingrediente: senza di essa l'argomento cade. È per questo che la versione gemella sui **tagli** ha risposta opposta.
### Non esiste un duale della cut property per gli archi fuori T
> [!question] Domanda d'esame — Non esiste un duale della cut property per gli archi fuori T
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora l'arco f è l'arco più pesante di almeno un taglio di G.» *(traccia 23/09/2025 · Es. 1.1 n. 4 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** La cut property riguarda solo gli archi **dentro** $T$ (ciascuno è il minimo di un taglio indotto dalla propria rimozione). Il vero duale per gli archi **fuori** $T$ è la cycle property, che parla di **cicli**, non di tagli: l'enunciato confonde le due nozioni.
>
> **Controesempio.** $A,B,C,D$ con $AB{=}1,\ BC{=}1,\ AC{=}2,\ AD{=}5,\ DC{=}5$; MST $T=\{AB,BC,AD\}$. Preso $f=AC\ (2)\notin T$: in ogni taglio che $f$ attraversa, l'arco più pesante è sempre $AD$ o $DC$ (peso 5), mai $f$.
## Dalla cut property alla correttezza globale
### Arco più leggero di un ciclo non è garantito
> [!question] Domanda d'esame — Arco più leggero di un ciclo non è garantito
> **D:** *(Vero o Falso)* «Sia C un ciclo di G ed e l'arco più leggero di C. Allora esiste sempre un MST di G che contiene e.» *(traccia 28/09/2022 · Es. 1.1 n. 2)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** A differenza della cut property (che garantisce l'inclusione del minimo di un taglio), non esiste una proprietà simmetrica per il minimo di un ciclo: la cycle property parla solo del **massimo** del ciclo, non del minimo.
>
> **Come può essere escluso.** Un arco leggero interno a un ciclo può comunque essere escluso da ogni MST se, per il taglio che separa i suoi estremi, esiste un percorso alternativo esterno al ciclo di costo complessivo ancora minore: è la cut property applicata a *quel* taglio a decidere l'esclusione, non la cycle property.
>
> Le due proprietà non sono simmetriche: la cut property vincola i minimi dei tagli, la cycle property vincola i massimi dei cicli; non esiste un analogo che vincoli i minimi dei cicli.
### Un arco fuori da $T$ non è più pesante di *tutti* gli archi di $T$
> [!question] Domanda d'esame — Un arco fuori da $T$ non è più pesante di *tutti* gli archi di $T$
> **D:** *(Vero o Falso)* «Sia $T$ un MST di $G$ e $f$ un arco non di $T$, allora il peso di $f$ è maggiore o uguale del peso di tutti gli archi di $T$.» *(traccia 20/07/2026 · Es. 1.1 n. 4 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** La cycle property dice che $f$ è il massimo del **proprio ciclo fondamentale** — cioè del ciclo che forma con $T$ — non dell'intero albero. Gli archi di $T$ fuori da quel ciclo non sono confrontati con $f$ da nessun argomento, e possono tranquillamente pesare di più.
>
> **Controesempio.** Triangolo $A,B,C$ con $AB=1$, $AC=2$, $BC=3$, più un nodo $D$ collegato solo ad $A$ con $AD=100$.
> - $AD$ è un **ponte**: sta in ogni spanning tree, MST compreso.
> - Fra i tre archi del triangolo se ne scelgono due, i più leggeri: $T = \{AD, AB, AC\}$, di costo $103$.
> - L'arco fuori dall'albero è $f = BC$, con $w(f) = 3$. Il suo ciclo fondamentale è $B-C$ chiuso dal cammino $B-A-C$ in $T$, di archi $AB=1$ e $AC=2$: $f$ **è** il massimo di quel ciclo, coerentemente con la cycle property.
> - Ma $w(f) = 3 < 100 = w(AD)$ con $AD \in T$: esiste un arco di $T$ più pesante di $f$, quindi l'affermazione è falsa.
>
> È l'errore di quantificatore più frequente su MST: «massimo del suo ciclo» viene letto come «massimo dell'albero». Il confronto è sempre **locale al ciclo fondamentale**.
### Caratterizzazione degli alberi non ottimi
> [!question] Domanda d'esame — Caratterizzazione degli alberi non ottimi
> **D:** *(Vero o Falso)* «Se T non è un MST di G allora esiste un arco e ∈ T e un arco f ∉ T tale che e è l'arco più pesante del ciclo che si forma quando si aggiunge f a T.» *(traccia 13/06/2024 · Es. 1.1 n. 4 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È (nella sostanza) la contronominale della cycle property applicata a $T$: se $T$ non è minimo, esiste un arco $e \in T$ scambiabile con un arco $f \notin T$ per ottenere un albero di costo minore o uguale. Aggiungendo $f$ a $T$ si crea un ciclo, e $e$ ne deve essere l'arco di peso **massimo** — altrimenti lo scambio $T \cup \{f\} \setminus \{e\}$ non ridurrebbe (o pareggerebbe) il costo.
>
> È lo stesso argomento di scambio alla base della dimostrazione di ottimalità di Kruskal e Prim: ogni volta che un albero non è ottimo, esiste una coppia $(e, f)$ di questo tipo che permette di migliorarlo.
### Massimo di un ciclo vs massimo di tutti i cicli
> [!question] Domanda d'esame — Massimo di un ciclo vs massimo di tutti i cicli
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco non di T. Allora f è l'arco di peso massimo in tutti i cicli che lo contengono.» *(traccia 18/07/2025 · Es. 1.1 n. 1 · «quale è vera»)*

> [!info]- Risposta modello
> Falso.
>
> **Perché.** La cycle property garantisce solo che $f$ sia il massimo di **almeno un** ciclo — il ciclo fondamentale che si forma aggiungendo $f$ a $T$ — non di **ogni** ciclo di $G$ che contiene $f$.
>
> In un grafo con più cicli passanti per $f$, l'arco può non essere il più pesante in un ciclo diverso da quello fondamentale rispetto a $T$: la proprietà è legata alla scelta di $T$, non è una caratteristica assoluta di $f$.
### Un arco dell'MST non è per forza il minimo di un ciclo
> [!question] Domanda d'esame — Un arco dell'MST non è per forza il minimo di un ciclo
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia e un arco di T, allora l'arco e è l'arco più leggero di almeno un ciclo in G.» *(traccia 09/09/2025 · Es. 1.1 n. 4 · «quale è vera» · anche 27/09/2023 Es. 1.1 n. 2)*

> [!info]- Risposta modello
> Falsa.
>
> **Controesempio.** Se $e$ è un **ponte** (bridge) di $G$ — cioè la sua rimozione disconnette il grafo — allora $e$ non appartiene ad alcun ciclo di $G$, quindi non può essere l'arco più leggero di nessun ciclo, pur essendo necessariamente parte di ogni spanning tree, MST incluso.
>
> L'affermazione varrebbe se si aggiungesse l'ipotesi che $e$ appartenga ad almeno un ciclo: in quel caso $e$ è comunque il più leggero solo del ciclo fondamentale indotto da un particolare $T$, non necessariamente di ogni ciclo che lo contiene (cfr. domanda precedente).
### Cut property e archi non minimi
> [!question] Domanda d'esame — Cut property e archi non minimi
> **D:** Enuncia la cut property e spiega come si usa per mostrare che un albero ricoprente $T$ non è minimo. *(traccia 13/06/2024 · Es. 1.2 · «max 5 righe»)*

> [!info]- Risposta modello
> **Idea.** La cut property afferma che l'arco di costo minimo che attraversa un qualsiasi taglio appartiene ad *almeno* un MST; per usarla "al contrario" e mostrare che $T$ non è minimo serve trovare **il taglio giusto**.
>
> **Procedura.** Sia $T$ un albero ricoprente e $f \in T$. Rimuovendo $f$ da $T$, l'albero si spezza in due componenti, che definiscono un taglio $(S, V\setminus S)$ di cui $f$ è l'**unico** arco di $T$ che lo attraversa. Se esiste un arco $e \notin T$ che attraversa *quello stesso* taglio con $c_e < c_f$, allora $T$ non è minimo: $T' = T \cup \{e\} \setminus \{f\}$ è ancora un albero ricoprente e costa strettamente meno.
>
> **Controesempio.** $A$-$B = 5$ come unico arco incidente ad $A$, più il triangolo $B$-$C=1$, $C$-$D=1$, $B$-$D=1$. Nel taglio $S=\{A,D\}$ il cutset è $\{A\text-B=5,\ C\text-D=1,\ B\text-D=1\}$ e $A\text-B$ non è il minimo, eppure è un **ponte**: sta in ogni albero ricoprente, quindi in ogni MST. Il taglio va scelto come sopra, **indotto da $T$**, non arbitrariamente.
>
> Non vale che «se $f$ non è il minimo di un taglio *qualsiasi*, allora esiste un MST senza $f$».
### Pesi in {1, 2}: un arco fuori T non deve avere per forza peso 2
> [!question] Domanda d'esame — Pesi in {1, 2}: un arco fuori T non deve avere per forza peso 2
> **D:** *(Vero o Falso)* «Si assuma che per ogni arco e vale w(e) ∈ {1, 2}, e sia T un MST di G. Allora ogni arco del grafo che non appartiene a T deve avere peso 2.» *(traccia 09/09/2025 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** La cycle property esclude solo l'arco **strettamente** massimo di un ciclo. Se un ciclo è formato interamente da archi di peso uguale (es. tutti 1), uno qualunque resta escluso da un dato MST per non chiudere il ciclo, pur non essendo affatto il più pesante.
>
> **Controesempio.** Triangolo con i tre archi di peso 1 (rispetta $w(e)\in\{1,2\}$): ogni MST ne sceglie due, il terzo — escluso — pesa comunque 1, non 2.
### Tutti gli archi del ciclo fondamentale sono ≤ w(f)
> [!question] Domanda d'esame — Tutti gli archi del ciclo fondamentale sono ≤ w(f)
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora l'aggiunta di f a T forma un ciclo e tutti gli archi del ciclo hanno un peso che è minore o uguale a quello di f.» *(traccia 09/09/2025 · Es. 1.1 n. 3 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È la cycle property in forma non stretta. Se esistesse un arco $e$ del ciclo con $w(e)>w(f)$, allora $T'=(T\setminus\{e\})\cup\{f\}$ sarebbe uno spanning tree con $w(T')<w(T)$, contro la minimalità di $T$.
>
> La disuguaglianza è $\leq$, non $<$: con pesi ripetuti sul ciclo, $f$ può pareggiare (ma mai superare) il massimo.
### Variante: f non è il più pesante di ogni ciclo che lo contiene
> [!question] Domanda d'esame — Variante: f non è il più pesante di ogni ciclo che lo contiene
> **D:** *(Vero o Falso)* «Sia T un MST di G e sia f un arco che non appartiene a T, allora f è l'arco più pesante di ogni ciclo di G che lo contiene.» *(traccia 23/09/2025 · Es. 1.1 n. 3 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa — stessa argomentazione della domanda «Massimo di un ciclo vs massimo di tutti i cicli» del 18/07/2025 qui sopra: la cycle property garantisce che $f$ sia massimo solo nel ciclo **fondamentale** indotto da $T$, non in ogni ciclo di $G$ che lo contiene.
>
> **Controesempio.** $A,B,C,D$ con $AB{=}1,BC{=}1,AC{=}2,AD{=}5,DC{=}5$: nel ciclo fondamentale $A\text-B\text-C\text-A$, $f=AC$ è il massimo; nel ciclo $A\text-D\text-C\text-A$ (pesi 5,5,2), $f$ è invece il più leggero.
### Unicità e pesi ripetuti
> [!question] Domanda d'esame — Unicità e pesi ripetuti
> **D:** *(Vero o Falso)* «Se i pesi degli archi di G non sono distinti, sicuramente esistono due MST (distinti) di G.» *(traccia 18/07/2022 · Es. 1.1 n. 1 ; la stessa confusione ritorna come «Se tutti gli archi hanno peso intero positivo, l'MST è unico» — traccia 20/07/2026 · Es. 1.1 n. 3 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Pesi ripetuti sono condizione **necessaria ma non sufficiente** per avere più MST distinti. Per il criterio di unicità (cfr. box **Criterio — Caratterizzazione dell'unicità**), servono due archi di pari peso che si trovino **sullo stesso ciclo** e che siano entrambi massimi di quel ciclo: solo allora lo scambio produce un secondo MST. Due archi di peso uguale in punti scorrelati del grafo non generano alcuna alternativa.
>
> **Controesempio.** Se $G$ non contiene cicli — cioè $G$ è già un albero — esiste un'unica soluzione ricoprente (l'intero $G$), indipendentemente da quanti pesi si ripetono: non ci sono cicli in cui operare uno scambio di archi.
>
> Il criterio corretto (cfr. box **Proprietà — Unicità dell'MST**) è: pesi tutti distinti $\Rightarrow$ MST unico. Ma la contronominale «pesi non distinti $\Rightarrow$ MST non unico» è **falsa**, perché l'implicazione originale non è un se-e-solo-se.
## Kruskal
### Il numero di componenti dopo k archi non è garantito n−k
> [!question] Domanda d'esame — Il numero di componenti dopo k archi non è garantito n−k
> **D:** *(Vero o Falso)* «Dopo aver processato il terzo arco di peso minimo di G, l'algoritmo ha calcolato una soluzione parziale che è una foresta di esattamente n − 3 componenti connesse;» *(traccia 19/02/2024 · Es. 1.1 n. 5 · formato ridotto)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Il numero di componenti diminuisce di uno solo quando l'arco **processato** viene effettivamente **aggiunto** a $T$ (cioè collega due componenti distinte), non a ogni arco processato in assoluto.
>
> **Controesempio.** Se il terzo arco in ordine di peso chiude un ciclo — perché i suoi estremi sono già nella stessa componente dopo i primi due — viene scartato: il numero di componenti resta $n-2$, non $n-3$.
>
> L'uguaglianza $n-k$ dopo $k$ archi **processati** vale solo se tutti e $k$ sono stati effettivamente **accettati**; in generale, dopo $k$ archi processati il numero di componenti è $n$ meno il numero di archi effettivamente accettati tra i primi $k$.
### Perché un arco viene scartato
> [!question] Domanda d'esame — Perché un arco viene scartato
> **D:** *(Vero o Falso)* «Quando l'algoritmo processa un generico arco e e decide di non aggiungerlo alla soluzione, vuol dire non solo che l'arco e forma un ciclo con gli archi già aggiunti, ma che è anche l'arco più pesante di quel ciclo;» *(traccia 19/02/2024 · Es. 1.1 n. 8 · formato ridotto)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È esattamente l'argomento della sezione Correttezza qui sopra. Esaminando gli archi in ordine crescente di peso, quando si scarta $e=(x,y)$ perché $x$ e $y$ sono già connessi in $T$, l'arco chiude un ciclo con il cammino già presente; poiché tutti gli archi già aggiunti (quindi anche quelli del ciclo) hanno peso $\leq c_e$, $e$ è necessariamente l'arco di peso **massimo** di quel ciclo.
>
> Per la cycle property, l'arco di peso massimo di un ciclo può sempre essere escluso da un MST: è questo che garantisce che scartare $e$ non comprometta l'ottimalità.
### Perché un arco viene accettato
> [!question] Domanda d'esame — Perché un arco viene accettato
> **D:** *(Vero o Falso)* «Quando l'algoritmo di Kruskal aggiunge un arco $e$ all'albero che sta costruendo è sempre perché $e$ è l'arco più leggero che attraversa un qualche taglio.» *(traccia 20/07/2026 · Es. 1.1 n. 5 · «quale è vera»)*

> [!info]- Risposta modello
> Vera. È il gemello "in positivo" della domanda precedente: lì si scarta per cycle property, qui si accetta per cut property.
>
> **Perché.** Kruskal aggiunge $e=(u,v)$ solo quando $u$ e $v$ stanno in due componenti diverse della foresta corrente. Si prenda come taglio $S =$ la componente che contiene $u$: ogni arco del cutset di $S$ o non è ancora stato esaminato — e allora ha peso $\geq c_e$, perché gli archi si guardano in ordine non decrescente — oppure era già stato esaminato e scartato, ma in tal caso aveva **entrambi** gli estremi in $S$ e quindi non attraversa il taglio. Dunque $e$ è un arco di costo minimo del cutset di $S$.
>
> Il taglio non è dato dalla traccia: **lo esibisci tu**, ed è quello indotto dalla componente corrente. Rispondere «vero per la cut property» senza costruire $S$ è la risposta a metà.
### Kruskal non finisce dopo $n-1$ archi *guardati*
> [!question] Domanda d'esame — Kruskal non finisce dopo $n-1$ archi *guardati*
> **D:** *(Vero o Falso)* «L'algoritmo di Kruskal guarda gli archi del grafo in ordine crescente di peso. Dopo che ha visto esattamente i primi $n-1$ archi ha calcolato un MST di $G$.» *(traccia 20/07/2026 · Es. 1.1 n. 1 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** L'MST ha $n-1$ archi **accettati**, non $n-1$ archi **esaminati**: i due conteggi coincidono solo se nessun arco viene scartato. Basta un ciclo fra i primi archi leggeri perché l'algoritmo ne butti via qualcuno e debba proseguire oltre il $(n-1)$-esimo.
>
> **Controesempio.** Triangolo $A,B,C$ con pesi $1,1,1$ più un nodo $D$ appeso ad $A$ con peso $10$: $n=4$, quindi $n-1=3$. Nei primi tre archi guardati ci sono i tre lati del triangolo, di cui uno viene scartato perché chiude un ciclo; dopo tre archi esaminati la soluzione ne ha solo due e $D$ è ancora isolato.
>
> L'affermazione sarebbe vera riformulata su «dopo aver **aggiunto** $n-1$ archi»: quello sì è il criterio di arresto dell'algoritmo.
### L'MST può contenere l'arco più pesante di G
> [!question] Domanda d'esame — L'MST può contenere l'arco più pesante di G
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Kruskal non contiene mai l'arco di peso massimo di G.» *(traccia 24/09/2024 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Controesempio.** Se $G$ è già un albero (connesso con esattamente $n-1$ archi), l'unico spanning tree possibile è $G$ stesso, che è quindi anche l'MST e contiene necessariamente anche l'arco di peso massimo.
>
> Più in generale, se l'arco di peso massimo è un **ponte**, deve comparire in ogni spanning tree, MST incluso, indipendentemente da quanto sia costoso: nessuno scambio può eliminarlo perché non esiste un ciclo alternativo che lo contenga.
### Il numero di archi non basta per la complessità
> [!question] Domanda d'esame — Il numero di archi non basta per la complessità
> **D:** *(Vero o Falso)* «Se il numero di archi in G è Θ(n), allora l'algoritmo di Kruskal ha complessità O(n).» *(traccia 18/07/2022 · Es. 1.1 n. 5)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Come mostrato nella tabella qui sopra, il costo totale di Kruskal è dominato dall'**ordinamento** degli archi, $O(m \log m) = O(m \log n)$.
>
> **Calcolo.** Con $m = \Theta(n)$ si ottiene $O(n \log n)$, non $O(n)$: il fattore logaritmico dell'ordinamento non scompare, indipendentemente da quanto sia piccolo $m$ rispetto a $n^2$.
### Θ(n√n) archi non rende Kruskal lineare
> [!question] Domanda d'esame — Θ(n√n) archi non rende Kruskal lineare
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Kruskal che implementa la Union-Find con la QuickFind con euristica union by size ha complessità lineare, ovvero Θ(n√n).» *(traccia 09/09/2025 · Es. 1.1 n. 5 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Calcolo.** Con $m = \Theta(n\sqrt{n})$, la complessità di Kruskal resta $O(m \log n) = \Theta(n \sqrt{n} \log n)$, dominata dall'ordinamento degli archi, non $\Theta(n\sqrt n)$ come richiesto dall'enunciato.
>
> Il fattore $\log n$ non si elimina indipendentemente dall'euristica scelta per la Union-Find (QuickFind con o senza union by size), perché quell'euristica riguarda solo il costo delle operazioni `union`/`find`, non quello dell'ordinamento — che resta il termine dominante.
### Su grafi densi l'euristica union-by-size è ininfluente
> [!question] Domanda d'esame — Su grafi densi l'euristica union-by-size è ininfluente
> **D:** *(Vero o Falso)* «Se G è completo allora l'algoritmo di Kruskal ha la stessa complessità asintotica sia se usa per la struttura Union-Find la QuickFind con o senza euristica union by size.» *(traccia 18/07/2025 · Es. 1.1 n. 5 · «quale è vera»)*

> [!info]- Risposta modello
> Vero.
>
> **Perché.** Se $G$ è completo, $m = \Theta(n^2)$, quindi il costo dell'ordinamento $O(m \log n) = O(n^2 \log n)$ domina già asintoticamente il costo delle operazioni di Union-Find.
>
> **Calcolo.** Senza euristica il costo di Union-Find è al più $O(m) = O(n^2)$; con union by size è $O(m + n\log n)$. In entrambi i casi il totale resta $\Theta(n^2 \log n)$, dominato dall'ordinamento: l'euristica non cambia la complessità asintotica complessiva su grafi densi.
### MST di una griglia N×N con pesi orizzontali 1 e verticali i+j
> [!question] Domanda d'esame — MST di una griglia N×N con pesi orizzontali 1 e verticali i+j
> **D:** «Sia N > 2 un intero. Si consideri il grafo non orientato di n = N² nodi disposti su un piano a formare una griglia N × N, dove ogni nodo è collegato ai suoi (al più) quattro nodi vicini orizzontalmente e verticalmente. In particolare il nodo in posizione (i, j), con i, j ∈ {1, . . . , N}, ha un arco verso il nodo (i, j − 1) (se esiste) e verso il nodo (i, j + 1) (se esiste) di peso 1, e ha un arco verso il nodo (i − 1, j) (se esiste) di peso i − 1 + j e un arco verso il nodo (i + 1, j) (se esiste) di peso i + j. Si descriva come è fatto un MST del grafo e si derivi una formula chiusa per il suo peso. (Max 5 righe.)» *(traccia 23/09/2025 · Es. 1.2 · «motiva in 5 righe»)*

> [!info]- Risposta modello
> L'MST è formato da tutti gli archi orizzontali (peso 1) più, per ogni coppia di righe adiacenti, l'unico arco verticale in colonna $j=1$.
>
> **Calcolo.** Gli $N(N-1)$ archi orizzontali (peso 1, minimo assoluto) non creano cicli: ogni riga resta un cammino. Restano $N-1$ archi verticali, uno per coppia di righe adiacenti $(i,i+1)$: tra i candidati di peso $i+j$ ($j=1,\dots,N$), il minimo stretto è in colonna $j=1$ (peso $i+1$) — per la cut property, appartiene a ogni MST. Peso totale: $N(N-1) + \sum_{i=1}^{N-1}(i+1) = \dfrac{(3N+2)(N-1)}{2}$.
>
> **Unicità.** L'MST è unico, ma **non** perché i minimi coinvolti siano stretti: gli archi orizzontali pesano tutti $1$, quindi ci sono pareggi in abbondanza. Il criterio corretto è sui **massimi dei cicli**: ogni arco fuori dall'albero è un verticale in colonna $j \geq 2$, di peso $i+j$, e il suo ciclo fondamentale è formato da orizzontali (peso $1$) più il verticale in colonna $1$ (peso $i+1$). Essendo $j \geq 2$, vale $i+j > i+1$: l'arco escluso è il massimo **stretto** del proprio ciclo fondamentale, quindi nessuno scambio a costo invariato è possibile e l'MST è unico. I pareggi tra orizzontali sono innocui perché quegli archi stanno **tutti** nell'albero.
## Prim
### Cut property e correttezza di Prim
> [!question] Domanda d'esame — Cut property e correttezza di Prim
> **D:** «3. Si discuta in modo conciso e preciso come è possibile usare la proprietà del taglio per dimostrare la correttezza dell'algoritmo di Prim.» *(traccia 26/06/2025 · Es. 2.3 · «max 5 righe»)*

> [!info]- Risposta modello
> **Idea.** Ad ogni passo, l'insieme $S$ dei nodi già esplorati definisce un taglio $(S, V \setminus S)$; Prim seleziona sempre l'arco di costo minimo del cutset di $S$ (l'arco che collega $S$ al resto del grafo a minor costo).
>
> **Applicazione a ogni passo.** Per la cut property, l'arco scelto appartiene sempre ad almeno un MST di $G$ che estende le scelte già fatte in $T$. L'argomento vale identicamente per ciascuno degli $n-1$ archi aggiunti, perché a ogni passo il taglio $(S, V\setminus S)$ cambia ma la proprietà si applica allo stesso modo.
>
> **Conclusione.** L'albero finale ha $n-1$ archi, ognuno giustificato dalla cut property al momento della sua aggiunta: è quindi esso stesso un MST.
### Prim su grafo non pesato non è BFS
> [!question] Domanda d'esame — Prim su grafo non pesato non è BFS
> **D:** *(Vero o Falso)* «Quando il grafo è non pesato, l'algoritmo di Prim restituisce un albero dei cammini minimi radicato sul nodo sorgente su cui è chiamato.» *(traccia 13/06/2024 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Come chiarito nel box qui sopra, Prim usa come chiave il costo del singolo arco di attacco, non la distanza cumulativa dalla sorgente. Con pesi tutti uguali a 1 ogni spanning tree è già un MST (i costi sono tutti uguali), ma le scelte di Prim tra archi di pari peso sono **arbitrarie** e non seguono necessariamente l'ordine per livelli di una BFS.
>
> L'albero prodotto può quindi non coincidere con l'albero dei cammini minimi da $s$, anche se entrambi hanno lo stesso costo totale come spanning tree.
### MST e albero dei cammini minimi restano problemi diversi
> [!question] Domanda d'esame — MST e albero dei cammini minimi restano problemi diversi
> **D:** *(Vero o Falso)* «L'albero restituito dall'algoritmo di Prim invocato su una sorgente s è anche un albero dei cammini minimi di G rispetto alla stessa sorgente s.» *(traccia 24/09/2024 · Es. 1.1 n. 4 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** In generale i due problemi ottimizzano criteri diversi ([[10 - Cammini Minimi e Dijkstra#Il problema SSSP e l'albero dei cammini minimi|SSSP e albero dei cammini minimi]]) — costo totale dell'albero per Prim, distanza dalla sorgente per l'albero dei cammini minimi — e producono alberi diversi.
>
> **Controesempio (concettuale).** Un nodo lontano da $s$ ma raggiungibile con un arco di attacco molto economico viene incluso presto da Prim, anche se il suo cammino minimo dalla sorgente lungo l'albero di Prim è più lungo del cammino minimo reale: Prim minimizza il costo del singolo arco di attacco, non la distanza cumulativa.
### Pesi tutti uguali: ogni SPT è anche un MST
> [!question] Domanda d'esame — Pesi tutti uguali: ogni SPT è anche un MST
> **D:** *(Vero o Falso)* «Se tutti i pesi di G sono uguali, allora ogni albero dei cammini minimi di G rispetto a una qualsiasi sorgente s è anche un MST di G.» *(traccia 18/07/2025 · Es. 1.1 n. 3 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Se tutti i pesi valgono una costante $c$, ogni spanning tree ha $n-1$ archi e quindi costo $(n-1)c$: sono tutti di pari peso, dunque tutti MST. Un albero dei cammini minimi è per definizione uno spanning tree, quindi rientra in questo insieme indipendentemente dalla sorgente $s$.
>
> Argomento diretto per conteggio, non serve cut/cycle property; è il fatto usato più sotto per «con pesi uguali basta BFS/DFS, $O(n+m)$».
### Pesi in {1, 2}: Prim non dà per forza un albero dei cammini minimi
> [!question] Domanda d'esame — Pesi in {1, 2}: Prim non dà per forza un albero dei cammini minimi
> **D:** *(Vero o Falso)* «Se per ogni arco e vale w(e) ∈ {1, 2}, allora l'algoritmo di Prim applicato su un nodo iniziale s calcola un MST che è anche un albero dei cammini minimi con sorgente s.» *(traccia 18/07/2025 · Es. 1.1 n. 4 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa.
>
> **Controesempio.** Ciclo $s\text-a\text-b\text-c\text-d\text-s$ con i quattro archi della catena di peso 1 e l'arco diretto $s\text-d$ di peso 2. Per la cycle property l'unico MST è la catena $s,a,b,c,d$ (esclude l'arco di peso 2, unico massimo del ciclo), e Prim la calcola senza ambiguità di pareggio.
>
> **Perché.** Nell'albero calcolato la distanza $s\to d$ è $4$, ma nel grafo il vero cammino minimo è l'arco diretto, costo $2$: Prim minimizza il costo dell'arco di attacco, non la distanza cumulativa da $s$.
### Variante: pesi tutti unitari, Prim non dà per forza un SPT
> [!question] Domanda d'esame — Variante: pesi tutti unitari, Prim non dà per forza un SPT
> **D:** *(Vero o Falso)* «Se tutti gli archi hanno peso 1, allora l'algoritmo di Prim applicato su un nodo iniziale s calcola un MST che è necessariamente anche un albero dei cammini minimi con sorgente s.» *(traccia 09/09/2025 · Es. 1.1 n. 1 · «quale è vera»)*

> [!info]- Risposta modello
> Falsa — stessa argomentazione della domanda «Prim su grafo non pesato non è BFS» del 13/06/2024 qui sopra: con pesi unitari ogni spanning tree è un MST, ma le scelte di Prim tra archi a pari peso sono arbitrarie e non seguono l'ordine per livelli di una BFS.
>
> **Controesempio.** Triangolo $s,a,b$ con i tre archi di peso 1: Prim può scegliere $(s,a)$ poi $(a,b)$, dando $T=\{sa,ab\}$; la distanza $s\to b$ in $T$ è $2$, ma nel grafo è $1$ tramite l'arco diretto $(s,b)$.
### Θ(n√n) archi e heap di Fibonacci
> [!question] Domanda d'esame — Θ(n√n) archi e heap di Fibonacci
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, allora l'algoritmo di Prim che implementa la coda con priorità attraverso un heap di Fibonacci ha complessità lineare, ovvero Θ(n√n).» *(traccia 23/09/2025 · Es. 1.1 n. 5 · «quale è vera»)*

> [!info]- Risposta modello
> Vero.
>
> **Calcolo.** Con l'heap di Fibonacci, Prim costa $O(m + n\log n)$. Con $m = \Theta(n\sqrt n)$ si ha $n\log n = o(n\sqrt n)$ (il fattore $\sqrt n$ domina $\log n$), quindi il totale è $\Theta(n\sqrt n + n \log n) = \Theta(n\sqrt n) = \Theta(m)$: la complessità è effettivamente lineare nel numero di archi.
>
> È l'opposto dello scenario analogo per Kruskal (cfr. la domanda «Θ(n√n) archi non rende Kruskal lineare»): lì il fattore $\log n$ dell'ordinamento non si elimina mai, qui invece l'heap di Fibonacci lo rende asintoticamente irrilevante.
### Prim con array non ordinato
> [!question] Domanda d'esame — Prim con array non ordinato
> **D:** *(Vero o Falso)* «La complessità dell'algoritmo di Prim nel caso peggiore è di $\Theta(n^2)$ se la coda con priorità è implementata con un array non ordinato.» *(traccia 20/07/2026 · Es. 1.1 n. 2 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Calcolo.** Con l'[[07 - Code con Priorità e Heap#Array non ordinato|array non ordinato]]: $n$ operazioni di `extractMin`, ciascuna $\Theta(n)$ perché va scandito tutto l'array $\Rightarrow \Theta(n^2)$; le `decreaseKey` costano invece $O(1)$ ciascuna (accesso diretto alla posizione del nodo) e sono al più $m \leq \binom{n}{2}$, quindi $O(n^2)$. Totale $\Theta(n^2)$, e il $\Theta$ regge perché le $n$ estrazioni costano $\Omega(n^2)$ comunque, anche su grafi sparsi.
>
> È il motivo per cui l'array non ordinato **conviene sui grafi densi** ($m = \Theta(n^2)$): lì $\Theta(n^2)$ eguaglia $O(m + n\log n)$ dell'heap di Fibonacci senza il costo costante della struttura. Il confronto fra implementazioni sta nella tabella di riepilogo più avanti.
### Bound in funzione del grado massimo
> [!question] Domanda d'esame — Bound in funzione del grado massimo
> **D:** *(Vero o Falso)* «Se il grado massimo in G è δ allora l'algoritmo di Prim implementato con heap binario ha complessità O(δ n log(n)) nel caso peggiore» *(traccia 27/09/2023 · Es. 1.1 n. 4 · formato Clementi)*

> [!info]- Risposta modello
> Vera.
>
> **Calcolo.** Con heap binario, Prim costa $O(m \log n)$. Se il grado massimo è $\delta$, allora $m \leq \delta n / 2 = O(\delta n)$ — ogni nodo contribuisce al più $\delta$ archi, ognuno contato due volte — quindi $O(m \log n) = O(\delta n \log n)$.
>
> È un bound più fine di $O(m \log n)$ generico, utile su grafi con grado massimo limitato: se $\delta = O(1)$ si ottiene $O(n \log n)$ anche senza conoscere $m$ esplicitamente.
## Confronto fra gli algoritmi
### Caso speciale: pesi tutti uguali
> [!question] Domanda d'esame — Caso speciale: pesi tutti uguali
> **D:** «Quale algoritmo useresti per calcolare un MST di G e qual è la sua complessità asintotica nel caso peggiore se G ha tutti gli archi dello stesso peso? [risposta in 1 riga]» *(traccia 27/09/2023 · Es. 1.2 n. 2 · «risposta in 1 riga» · formato Clementi)*

> [!info]- Risposta modello
> **Idea.** Basta una BFS o una DFS a partire da un vertice qualsiasi, con complessità $O(n+m)$: nessun algoritmo greedy basato sui pesi è necessario.
>
> **Perché funziona.** Se tutti gli archi hanno lo stesso peso, ogni spanning tree ha lo stesso costo totale ($n-1$ volte il peso comune): ogni spanning tree è quindi automaticamente un MST, e la scelta greedy di Kruskal o Prim diventa superflua.
>
> ⏱️ **Se la traccia dà 1 riga**: scrivi solo «BFS/DFS, $O(n+m)$: con pesi tutti uguali ogni spanning tree è un MST». Non omettere mai la complessità $O(n+m)$ — è esplicitamente richiesta insieme all'algoritmo.
### Kruskal: descrizione e correttezza
> [!question] Domanda costruita — Kruskal: descrizione e correttezza
> **D:** Descrivi l'algoritmo di Kruskal, spiega perché è corretto e calcolane la complessità. *(domanda costruita, nessuna traccia reale: serve a coprire un argomento del programma)*

> [!info]- Risposta modello
> **Idea.** Kruskal ordina gli archi in senso crescente di costo e li aggiunge a $T$ uno a uno, saltando quelli che formerebbero un ciclo (rilevato tramite Union-Find).
>
> **Correttezza.** Si basa sulla cut property: quando si aggiunge $(x,y)$, la componente di $x$ in $T$ forma il taglio $S$; poiché gli archi sono esaminati in ordine crescente, $(x,y)$ è l'arco di costo minimo che attraversa quel taglio, quindi appartiene a un MST. Quando invece un arco viene scartato, chiude un ciclo di cui è il massimo, ed è escludibile per la cycle property.
>
> **Complessità.** $O(m \log n)$: l'ordinamento degli archi domina ($O(m \log m) = O(m \log n)$), e le operazioni Union-Find con union by size costano complessivamente $O(m \log n)$ nel totale — nessuno dei due termini elimina l'altro.
### Differenza tra Prim e Dijkstra
> [!question] Domanda costruita — Differenza tra Prim e Dijkstra
> **D:** Qual è la differenza tra l'algoritmo di Prim e l'algoritmo di Dijkstra? *(domanda costruita, nessuna traccia reale: serve a coprire un argomento del programma)*

> [!info]- Risposta modello
>
> **Differenza (la chiave).** Dijkstra usa come chiave la **distanza cumulativa** da $s$ (il costo del cammino da $s$ al nodo), per trovare i cammini minimi. Prim usa come chiave il **costo del singolo arco** di attacco all'albero corrente, per trovare l'MST.
>
> **Conseguenza.** Prim non produce un albero dei cammini minimi: un nodo distante da $s$ ma connesso all'albero tramite un arco di attacco molto economico viene incluso prima di nodi vicini ma raggiungibili solo con archi costosi.
>
> Entrambi usano una coda con priorità e l'operazione `decreaseKey`, con la stessa struttura generale a passi.
### Pesi distinti: Kruskal e Prim coincidono sempre
> [!question] Domanda d'esame — Pesi distinti: Kruskal e Prim coincidono sempre
> **D:** *(Vero o Falso)* «Se i pesi sono distinti allora l'algoritmo di Kruskal e quello di Prim calcolano lo stesso identico albero indipendentemente dal nodo s di partenza (sorgente) scelto dall'algoritmo di Prim.» *(traccia 23/09/2025 · Es. 1.1 n. 1 · «quale è vera»)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Con pesi distinti l'MST è **unico**: la dimostrazione completa (argomento di scambio sulla differenza simmetrica $T_1 \triangle T_2$) è nel box [[#Unicità dell'MST]], ed è la parte da esporre per prima se la domanda è aperta.
>
> Kruskal e Prim sono **entrambi corretti**, cioè restituiscono un MST. Se l'MST è unico, «un MST» e «l'MST» coincidono: qualunque loro esecuzione dà lo stesso albero, a prescindere dall'ordine di scansione degli archi e dalla sorgente scelta per Prim.
## Clustering di massima spaziatura
### MST e clustering di massima spaziatura
> [!question] Domanda costruita — MST e clustering di massima spaziatura
> **D:** Come si usa l'MST per trovare il clustering di massima spaziatura? Perché funziona? *(domanda costruita, nessuna traccia reale: serve a coprire un argomento del programma)*

> [!info]- Risposta modello
> **Procedura.** Si calcola l'MST del grafo completo sugli oggetti (con pesi $=$ distanze) e si eliminano i $k-1$ archi più costosi. Le $k$ componenti connesse risultanti sono il clustering di massima spaziatura.
>
> **Perché funziona.** La spaziatura del clustering ottenuto è la lunghezza del $(k-1)$-esimo arco più costoso dell'MST. Qualsiasi altro $k$-clustering deve avere due oggetti nello stesso cluster dell'MST ma in cluster diversi tra loro; il cammino tra questi due oggetti nell'MST ha tutti gli archi di lunghezza $\leq$ quella spaziatura, quindi la spaziatura di qualsiasi altro clustering non può superare quella del clustering ottenuto dall'MST.
>
> **Complessità.** Dominata dal calcolo dell'MST su un grafo completo: $O(n^2 \log n)$ con Kruskal, oppure $O(n^2)$ con Prim su array non ordinato (adatto perché il grafo è denso); l'eliminazione dei $k-1$ archi più costosi costa poi solo $O(k)$.
