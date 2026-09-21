---
tags:
  - algoritmi
  - flussi
  - esercizi
nota: "[[07 - Flussi di Rete (Max-Flow e Min-Cut)]]"
---
# Esercizi — Flussi di Rete (Max-Flow e Min-Cut)
Palestra della nota [[07 - Flussi di Rete (Max-Flow e Min-Cut)]]: le domande d'esame stanno qui, la trattazione sta lì. Le risposte sono in callout **collassato** — leggi la domanda, rispondi a penna, poi apri.
> [!info] Come leggere le citazioni delle domande d'esame
> Ogni callout riporta la **data della traccia** da cui l'item proviene. A differenza della palestra di MST, qui la **posizione esatta** nella traccia (Es. 1.1 n. K, Es. 1.2, Es. 2.x) è riportata solo quando il testo citato la contiene: dove manca, la data resta l'unica provenienza certa e non va integrata a memoria.
> Gli item marcati **`Domanda costruita`** non vengono da una traccia: sono formulati sulla forma che l'esame usa per quell'argomento, e servono a coprire un pezzo di programma che nelle tracce raccolte non compare.

> [!warning] Le due forme in cui i Flussi vengono chiesti
> **Esercizio 1** — affermazioni vero/falso, spesso seguite da «motiva in 5 righe». Ruotano quasi tutte attorno a tre nuclei: la **complessità di Ford-Fulkerson** al variare delle capacità, la relazione **val(f) contro cap(A,B)** (dualità debole), e il **teorema dei cammini aumentanti** nelle sue due direzioni.
> **Esercizio 2** — la tripla **definizione → costruzione → dimostrazione**: definizione formale di Max-Flow o Min-Cut, definizione della rete residua, e la dimostrazione «**assenza di cammino aumentante $\Rightarrow$ flusso massimo**», che è l'unica dimostrazione sui flussi chiesta per esteso.

> [!info] Regola — le domande di complessità di Ford-Fulkerson sono tutte lo stesso conto
> «Capacità unitarie», «capacità $\leq n^2$», «$\Theta(n\sqrt n)$ archi e capacità $\leq 2$», «grado entrante limitato»: sono la stessa domanda travestita. Il conto è sempre
> $$\text{costo totale} \;=\; \underbrace{(\text{numero di aumenti})}_{\leq\ \operatorname{val}(f^*)} \;\times\; \underbrace{O(m)}_{\text{una BFS/DFS per aumento}}$$
> con $\operatorname{val}(f^*) \leq nC$ dal teorema di terminazione. Le tracce variano **una** delle due voci e chiedono il totale. Due avvertenze che ricorrono:
> - il bound $\operatorname{val}(f^*)\leq nC$ è spesso **più largo del necessario**: quando la traccia chiede «quanto più stretta possibile», il bound giusto si ottiene dalla **dualità debole su un taglio comodo** (tipicamente quello intorno a $t$);
> - il costo per iterazione dipende da $m$ e **non va confuso** con il numero di iterazioni: l'errore tipico è moltiplicare quando si doveva sommare, o fermarsi al costo di un singolo aumento.
## Definizioni
### Definizione formale del problema del massimo flusso
> [!question] Domanda d'esame — Definizione formale del problema del massimo flusso
> **D:** «Esercizio 2 [11 punti] Si consideri il problema del massimo flusso. 1. Si definisca formalmente il problema. (Max 5 righe.)» *(traccia 13/06/2024 · Es. 2.1)*

> [!info]- Risposta modello
> **Dati.** Rete $G=(V,E,s,t,c)$, con $c: E \to \mathbb{R}_{\geq 0}$ funzione di capacità, $s$ sorgente, $t$ pozzo.
>
> **Flusso.** Una funzione $f: E \to \mathbb{R}_{\geq 0}$ che rispetta il **vincolo di capacità** $0\leq f(e)\leq c(e)$ per ogni arco $e$, e il **vincolo di conservazione**: per ogni nodo $v$ diverso da $s$ e $t$, il flusso entrante in $v$ è uguale al flusso uscente da $v$.
>
> **Valore e obiettivo.** Il valore $\operatorname{val}(f)$ è il flusso netto uscente da $s$ (equivalentemente, per conservazione, quello entrante in $t$). Il problema del massimo flusso chiede il flusso $f$ che massimizza $\operatorname{val}(f)$.
>
> ⏱️ **In 5 righe**: la tupla $G=(V,E,s,t,c)$, i due vincoli (capacità e conservazione) in una riga ciascuno, e l'obiettivo di massimizzare $\operatorname{val}(f)$. **Non omettere mai** il vincolo di conservazione: è quello che distingue un flusso da una funzione arbitraria sugli archi.
### Definizione formale quando la traccia non nomina il problema
> [!question] Domanda d'esame — Definizione formale quando la traccia non nomina il problema
> **D:** «Si definisca formalmente il problema. (Max 5 righe.)» *(traccia 23/09/2025)*

> [!info]- Risposta modello
> **Definizione.** Stessa del problema del massimo flusso: dato $G=(V,E,s,t,c)$ con $c: E \to \mathbb{R}_{\geq 0}$, un flusso $f$ soddisfa il vincolo di capacità $0\leq f(e)\leq c(e)$ e il vincolo di conservazione in ogni nodo diverso da $s,t$; si cerca $f$ di valore $\operatorname{val}(f)$ massimo.
>
> **Perché è questo il problema.** La traccia non nomina esplicitamente «massimo flusso», ma nello stesso compito compaiono una domanda sulla rete residua e una dimostrazione sui cammini aumentanti: entrambe hanno senso solo nel contesto Max-Flow, quindi è quello il problema da definire.
>
> ⏱️ **In 5 righe**: la definizione stessa (vincoli + obiettivo) basta; la nota sull'identificazione del problema è superflua se il testo del compito lo rende ovvio, **ma se la traccia è ambigua come qui, non va mai omessa** — è la parte che giustifica quale definizione si sta scrivendo.
### Definizione formale del problema del minimo taglio
> [!question] Domanda d'esame — Definizione formale del problema del minimo taglio
> **D:** «Si consideri il problema del calcolo del taglio di capacità minima - Minimum cut problem. 1. Si definisca formalmente il problema. (Max 5 righe.)» *(traccia 18/07/2025 · Es. 2.1)*

> [!info]- Risposta modello
> **Dati.** Rete $G=(V,E,s,t,c)$.
>
> **Taglio.** Un taglio st è una partizione $(A,B)$ dei nodi con $s\in A$ e $t\in B$.
>
> **Capacità.** $\operatorname{cap}(A,B)=\sum_{e=(u,v):\,u\in A,\,v\in B} c(e)$, cioè la somma delle capacità dei soli archi diretti **da $A$ verso $B$**: gli archi da $B$ ad $A$ non contribuiscono, per quanto grande sia la loro capacità.
>
> **Obiettivo.** Trovare un taglio $(A^*,B^*)$ che minimizzi $\operatorname{cap}(A,B)$ tra tutte le partizioni st possibili.
>
> ⏱️ **In 5 righe**: taglio st, la formula della capacità con l'osservazione che conta solo il verso $A\to B$, e l'obiettivo di minimizzazione. **Non omettere mai** la direzionalità della capacità — è l'errore più comune (sommare anche gli archi da $B$ ad $A$).
### Definizione formale della rete residua
> [!question] Domanda d'esame — Definizione formale della rete residua
> **D:** «Si definisca formalmente il concetto di rete residua. (Max 5 righe.)» *(traccia 23/09/2025)*

> [!info]- Risposta modello
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
> ⏱️ **In 5 righe**: i due casi (arco diretto se non saturo, arco inverso se $f(e)>0$) e la formula compatta di $E_f$; la proprietà chiave si accenna in una riga. **Non omettere mai** la condizione $f(e)>0$ per l'esistenza dell'arco inverso — è il dettaglio che spiega perché il grafo residuo può «annullare» flusso.
### Ruolo dell'arco inverso nel grafo residuo
> [!question] Domanda costruita — Ruolo dell'arco inverso nel grafo residuo
> **D:** A cosa serve l'arco inverso nel grafo residuo?

> [!info]- Risposta modello
> **Ruolo.** L'arco inverso $e^{\text{rev}} = (v, u)$, associato all'arco originale $e = (u, v)$ con $f(e) > 0$, permette di **annullare** parte del flusso già inviato su $e$.
>
> **Meccanismo.** Quando un cammino aumentante usa $e^{\text{rev}}$, la procedura AUGMENT riduce $f(e)$ del bottleneck del cammino.
>
> **Perché serve.** È il meccanismo di *undo* delle decisioni sbagliate: senza di esso l'algoritmo greedy puro si blocca su cammini sub-ottimali, perché una volta saturato un arco non c'è modo di dirottare il flusso altrove.
## Cammino aumentante e bottleneck
### Aumento lungo P e capacità residua di un singolo arco
> [!question] Domanda d'esame — Aumento lungo P e capacità residua di un singolo arco
> **D:** *(Vero o Falso)* «Sia f un flusso e sia e un arco di un cammino P da s a t nella rete residua Gf. Allora è sempre possibile usare il cammino aumentante P per aumentare il flusso f di cf(e), dove cf(e) è il peso di e nella rete residua Gf.» *(traccia 26/06/2025)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** La quantità di cui si può aumentare il flusso lungo $P$ è il bottleneck del cammino, $\operatorname{bottleneck}(G_f,P)=\min_{e'\in P} c_f(e')$, cioè il minimo tra le capacità residue di **tutti** gli archi di $P$, non la capacità residua $c_f(e)$ di un singolo arco $e\in P$ scelto arbitrariamente.
>
> **Controesempio.** Se un altro arco $e'\in P$ ha $c_f(e')<c_f(e)$, usare $c_f(e)$ come incremento violerebbe il vincolo di capacità su $e'$: la procedura AUGMENT satura sempre l'arco di collo di bottiglia, non l'arco $e$ in questione.
### Capacità originali ≥ β e incremento di ogni augmenting step
> [!question] Domanda d'esame — Capacità originali ≥ β e incremento di ogni augmenting step
> **D:** *(Vero o Falso)* «Se per ogni arco e c(e) ≥ β, allora ogni augmanting step aumenta il flusso corrente di almeno β.» *(traccia 02/02/2026)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Il bottleneck di un cammino aumentante $P$ è il minimo delle **capacità residue** $c_f(e)$ degli archi di $P$ in $G_f$, non delle capacità originali $c(e)$ in $G$. Anche se ogni arco originale ha $c(e)\geq\beta$, un arco può avere capacità residua arbitrariamente piccola (vicina a 0 se quasi saturo) oppure essere un arco inverso con capacità residua pari al flusso $f(e)$ già inviato, che può essere minore di $\beta$.
>
> **Conclusione.** Un augmenting step può quindi aumentare il flusso di una quantità inferiore a $\beta$: l'ipotesi $c(e)\geq\beta$ sugli archi originali non si trasferisce alle capacità residue.
## Ford-Fulkerson — terminazione e complessità
### Capacità intere e incremento minimo di un aumento
> [!question] Domanda d'esame — Capacità intere e incremento minimo di un aumento
> **D:** *(Vero o Falso)* «Se le capacità sono intere, allora ogni cammino aumentante trovato nella rete residua può essere usato per aumentare il flusso corrente di almeno una unità.» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Per l'invariante di integralità, se tutte le capacità $c(e)$ sono intere, ogni $f(e)$ e ogni capacità residua $c_f(e)$ restano interi durante l'intera esecuzione (per induzione sul numero di aumenti, dato che AUGMENT somma/sottrae il bottleneck, esso stesso intero).
>
> **Conclusione.** Il bottleneck di un cammino aumentante è quindi un minimo di quantità intere e strettamente positive (un arco esiste in $G_f$ solo se ha capacità residua $>0$), dunque è un intero $\geq 1$.
### Terminazione di Ford-Fulkerson al variare delle capacità
> [!question] Domanda costruita — Terminazione di Ford-Fulkerson al variare delle capacità
> **D:** Ford-Fulkerson termina sempre?

> [!info]- Risposta modello
> No, non sempre.
>
> **Caso intere/razionali.** Termina in un numero finito di passi per il teorema di terminazione.
>
> **Caso irrazionali.** Possono esistere sequenze infinite di aumenti che convergono a un valore strettamente inferiore al massimo flusso.
>
> **Soluzione.** In questi casi servono varianti con garanzie di terminazione indipendenti dalle capacità, come Edmonds-Karp (usa solo BFS, termina in $O(m^2n)$).
### Complessità di Ford-Fulkerson e sua polinomialità
> [!question] Domanda d'esame — Complessità di Ford-Fulkerson e sua polinomialità
> **D:** «2. Si enunci la complessità temporale dell'algoritmo di Ford-Fulkerson, argomentando sulla sua polinomialità o meno. (Max 5 righe.)» *(traccia 13/06/2024 · Es. 2.2)*

> [!info]- Risposta modello
> **Complessità.** $O(m\cdot\operatorname{val}(f^*))$, dove $m$ è il numero di archi e $\operatorname{val}(f^*)$ è il valore del flusso massimo.
>
> **Polinomialità.** Non è un algoritmo polinomiale in senso stretto: è **pseudo-polinomiale**. La complessità dipende dal valore numerico delle capacità (tramite $\operatorname{val}(f^*)$), non dalla dimensione dell'input in bit.
>
> **Perché è un problema.** Con capacità intere grandi e scelta sfortunata dei cammini aumentanti, il numero di iterazioni può crescere in modo esponenziale rispetto alla dimensione dell'input (che è logaritmica nel valore delle capacità).
>
> ⏱️ **In 5 righe**: la formula $O(m\cdot\operatorname{val}(f^*))$ e la dichiarazione immediata che è pseudo-polinomiale; **non omettere mai** il perché (dipendenza dal valore numerico, non dalla dimensione in bit dell'input) — è quello che distingue pseudo-polinomiale da esponenziale puro.
### Capacità intere limitate da n² e polinomialità
> [!question] Domanda d'esame — Capacità intere limitate da n² e polinomialità
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi non più grandi di n².» *(traccia 02/02/2026)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Per il teorema di terminazione, con capacità intere comprese tra 1 e $C$ il numero di aumenti è al più $\operatorname{val}(f^*)\leq nC$, e ogni aumento costa $O(m)$: la complessità totale è $O(mnC)$. Se $C\leq n^2$, questa diventa $O(mn\cdot n^2)=O(mn^3)$, polinomiale sia in $n$ che in $m$.
>
> **Osservazione.** Il problema di Ford-Fulkerson nasce quando $C$ cresce esponenzialmente nel numero di bit usati per rappresentarlo (es. $C=2^{30}$); qui invece $C$ è esso stesso polinomiale in $n$, quindi il fattore $C$ non introduce dipendenza esponenziale.
### Bound più stretto con grado entrante limitato e capacità ≤ n²
> [!question] Domanda d'esame — Bound più stretto con grado entrante limitato e capacità ≤ n²
> **D:** «2. Si consideri una rete di flusso G = (V, E, s, t, c) di n nodi in cui ogni nodo ha grado entrante al più 3 (mentre il grado uscente di un nodo può essere anche Θ(n)) e la capacità di ogni arco e ∈ E è un numero intero non più grande di n². Si derivi una delimitazione superiore (quanto più stretta possibile) alla complessità temporale dell'algoritmo di Ford-Fulkerson sulla rete G. Si può affermare che in questo caso l'algoritmo è garantito avere complessità polinomiale? (Max 5 righe.)» *(traccia 26/06/2025 · Es. 2.2)*

> [!info]- Risposta modello
> **Bound su $m$.** Ogni nodo ha grado entrante al più 3, quindi sommando i gradi entranti su tutti i nodi si ottiene il numero totale di archi: $m=\sum_v \deg^-(v)\leq 3n=O(n)$ (il grado uscente può essere $\Theta(n)$, ma il conteggio via grado entrante limita comunque $m$).
>
> **Bound su $\operatorname{val}(f^*)$, via il taglio intorno a $t$.** Il bound generico $\operatorname{val}(f^*)\leq nC=n\cdot n^2=n^3$ è valido ma non è il più stretto possibile: ignora la struttura del grafo. Per la dualità debole, $\operatorname{val}(f^*)\leq\operatorname{cap}(A,B)$ per **ogni** taglio $(A,B)$; prendo $(A,B)=(V\setminus\{t\},\{t\})$: $\operatorname{cap}(A,B)=\sum_{e\text{ entra in }t} c(e)\leq \deg^-(t)\cdot n^2\leq 3n^2$ (il vincolo sul grado entrante vale anche per $t$). Dunque $\operatorname{val}(f^*)=O(n^2)$, un fattore $n$ più stretto del bound generico.
>
> **Complessità.** $O(m\cdot \operatorname{val}(f^*))=O(n)\cdot O(n^2)=O(n^3)$.
>
> **Conclusione.** Sì, l'algoritmo è garantito avere complessità polinomiale ($O(n^3)$): sia il numero di archi ($O(n)$, dal vincolo sul grado entrante) sia il valore del flusso massimo ($O(n^2)$, dal taglio intorno a $t$) sono limitati polinomialmente in $n$.
>
> ⏱️ **In 5 righe**: il bound su $m$ (1 riga), il bound su $\operatorname{val}(f^*)$ via il taglio intorno a $t$ (1-2 righe), la moltiplicazione finale $O(n^3)$ con la risposta sì (1 riga). **Non fermarsi** al bound generico $\operatorname{val}(f^*)\leq nC=n^3$ (che dà solo $O(n^4)$): è polinomiale ma non «quanto più stretto possibile» come chiede la traccia — serve il taglio intorno a $t$, che sfrutta il vincolo di grado entrante anche su $t$ stesso.
### Capacità unitarie e numero di iterazioni
> [!question] Domanda d'esame — Capacità unitarie e numero di iterazioni
> **D:** «Si consideri la seguente affermazione: Se le capacità degli archi sono tutte uguali a 1, allora il numero di iterazioni dell'algoritmo di Ford-Fulkerson, ovvero, il numero di aumenti di flusso tramite cammini aumentanti, è sempre polinomiale nel numero di nodi del grafo, indipendentemente dalla strategia usata per trovare i cammini aumentanti. Dire se l'affermazione è vera o falsa motivando la risposta (Max 5 righe).» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Con capacità unitarie il valore del flusso massimo è limitato dal grado uscente di $s$ (al più $n-1$ archi in un grafo semplice), quindi ogni cammino aumentante satura almeno un arco.
>
> **Conclusione.** Il numero di iterazioni è al più $n-1$, polinomiale (lineare) nel numero di nodi, indipendentemente dall'ordine con cui si scelgono i cammini aumentanti.
>
> ⏱️ **In 5 righe**: il bound sul grado uscente di $s$ e il fatto che ogni aumento satura almeno un arco bastano; **non omettere mai** la conclusione esplicita sul numero di iterazioni ($\leq n-1$).
### Capacità unitarie e complessità di Ford-Fulkerson
> [!question] Domanda d'esame — Capacità unitarie e complessità di Ford-Fulkerson
> **D:** *(Vero o Falso)* «Se tutti gli archi hanno capacità pari a 1, allora l'algoritmo di Ford-Fulkerson ha complessità O(n^3).» *(traccia 30/06/2026)*

> [!info]- Risposta modello
> Vera.
>
> **N. di aumenti.** Con capacità tutte uguali a 1 ($C=1$), il numero di aumenti è al più $\operatorname{val}(f^*)\leq n-1=O(n)$ (bound sul grado uscente di $s$).
>
> **Costo per aumento.** $O(m)$ tramite BFS/DFS; in un grafo semplice $m=O(n^2)$.
>
> **Complessità totale.** $O(m\cdot n)=O(n^2\cdot n)=O(n^3)$.
### Capacità intere e polinomialità in generale
> [!question] Domanda d'esame — Capacità intere e polinomialità in generale
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi.» *(traccia 26/06/2025)*

> [!info]- Risposta modello
> Falsa.
>
> **Prima parte (corretta).** Con scelta arbitraria del cammino, il numero di iterazioni può essere esponenziale, come nel caso patologico con $C=2^{30}$.
>
> **Seconda parte (sbagliata).** Capacità **intere** non bastano a garantire la polinomialità: il controesempio patologico ha proprio capacità intere ($C$, $C$, $1$) eppure richiede $2C$ iterazioni, esponenziale nel numero di bit usati per rappresentare $C$.
>
> **Cosa serve davvero.** Un vincolo più forte, come capacità polinomiali in $n$ (es. $C\leq n^2$), oppure una strategia di scelta del cammino con garanzie indipendenti da $C$ (Edmonds-Karp, capacity scaling).
>
> **Confronto utile.** Questa è la **gemella a ipotesi indebolita** dell'item «capacità intere non più grandi di $n^2$», che invece è vero: cambia solo il vincolo su $C$, e la risposta si ribalta.
### Θ(n√n) archi e capacità al più 2
> [!question] Domanda d'esame — Θ(n√n) archi e capacità al più 2
> **D:** *(Vero o Falso)* «Se G ha Θ(n√n) archi, e le capacità degli archi sono tutte al più 2, allora l'algoritmo di Ford-Fulkerson ha complessità lineare, ovvero O(n√n).» *(traccia 02/02/2026)*

> [!info]- Risposta modello
> Falsa.
>
> **Bound sul numero di aumenti.** Con $C\leq 2$, il numero di aumenti è al più $\operatorname{val}(f^*)\leq nC=O(n)$.
>
> **Costo per aumento.** $O(m)=O(n\sqrt n)$ per la BFS/DFS che cerca il cammino aumentante.
>
> **Complessità totale.** $O(m\cdot\operatorname{val}(f^*))=O(n\sqrt n\cdot n)=O(n^2\sqrt n)$, non $O(n\sqrt n)$.
>
> **Errore nella traccia.** Il costo di ogni singola iterazione (che dipende da $m$) è già $\Theta(n\sqrt n)$, e va **moltiplicato** per il numero di iterazioni, non confuso con esso.
### Un solo nodo con archi entranti di capacità 1
> [!question] Domanda d'esame — Un solo nodo con archi entranti di capacità 1
> **D:** *(Vero o Falso)* «Se esiste un nodo v nella rete i cui archi entranti hanno tutti capacità 1, allora l'algoritmo di Ford-Fulkerson è garantito avere complessità polinomiale.» *(traccia 30/06/2026)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Il bound $O(mnC)$ dipende dalla capacità massima $C$ su **tutti** gli archi della rete, non solo su quelli entranti in un singolo nodo $v$.
>
> **Controesempio.** Anche se gli archi entranti in $v$ hanno capacità 1, altri archi della rete (ad esempio quelli del caso patologico con l'arco centrale di capacità $C=2^{30}$) possono avere capacità arbitrariamente grandi e continuare a causare un numero esponenziale di iterazioni con scelta sfortunata dei cammini aumentanti.
>
> **Confronto utile.** Il vincolo *locale* su un nodo non basta; il vincolo su $\deg^-$ di **ogni** nodo, invece, sì — è l'item «grado entrante limitato e capacità $\leq n^2$».
## Flussi e tagli — lemma del valore e dualità debole
### Capacità di un taglio e flusso netto attraverso un taglio
> [!question] Domanda costruita — Capacità di un taglio e flusso netto attraverso un taglio
> **D:** Qual è la differenza tra la capacità di un taglio e il flusso netto attraverso un taglio?

> [!info]- Risposta modello
> **Capacità.** $\operatorname{cap}(A,B) = \sum_{e \text{ da } A \text{ a } B} c(e)$: dipende solo dalla struttura della rete (le capacità), non dal flusso corrente.
>
> **Flusso netto.** $\sum_{e \text{ da } A \text{ a } B} f(e) - \sum_{e \text{ da } B \text{ a } A} f(e)$: dipende dal flusso $f$ scelto.
>
> **Relazione.** Per il lemma del valore del flusso, il flusso netto attraverso qualsiasi taglio è uguale a $\operatorname{val}(f)$, indipendentemente da quale taglio si scelga.
### Flusso netto attraverso un taglio e valore del flusso
> [!question] Domanda d'esame — Flusso netto attraverso un taglio e valore del flusso
> **D:** *(Vero o Falso)* «per ogni taglio (A.B) e per ogni flusso f, il flusso netto che attraversa (A.B) è sempre uguale al valore di f.» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È esattamente l'enunciato del Lemma del valore del flusso: per ogni flusso $f$ e ogni taglio st $(A,B)$, $\operatorname{val}(f)=\sum_{e\text{ esce da }A} f(e) - \sum_{e\text{ entra in }A} f(e)$, cioè il flusso netto che attraversa il taglio è sempre uguale al valore del flusso, indipendentemente da quale taglio si scelga.
>
> **Osservazione.** Questo vale per **qualsiasi** flusso valido, non solo per il flusso massimo — a differenza della capacità del taglio, che è un limite superiore (dualità debole) raggiunto con uguaglianza solo per il taglio minimo quando $f$ è massimo.
### Flusso netto attraverso un taglio e capacità del taglio
> [!question] Domanda d'esame — Flusso netto attraverso un taglio e capacità del taglio
> **D:** *(Vero o Falso)* «Dato un taglio (A, B) e un flusso f, allora il flusso netto che passa per (A, B) è sempre maggiore o uguale alla capacità di (A, B).» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Per la dualità debole, il flusso netto attraverso un taglio (che, per il lemma del valore, coincide con $\operatorname{val}(f)$) è sempre **minore o uguale** alla capacità del taglio, mai maggiore: $\operatorname{val}(f)\leq\operatorname{cap}(A,B)$.
>
> **Da dove viene.** Il flusso netto uscente da $A$ è al più la somma delle capacità degli archi uscenti da $A$ (per il vincolo di capacità), meno un termine non negativo dato dal flusso entrante in $A$.
>
> **Attenzione al verso.** È la variante gemella **a disuguaglianza invertita**: l'affermazione vera ha $\leq$, questa ha $\geq$.
### Valore del flusso e capacità di un taglio qualsiasi
> [!question] Domanda d'esame — Valore del flusso e capacità di un taglio qualsiasi
> **D:** *(Vero o Falso)* «dato un flusso f di G e un st-taglio (A, B), il valore del flusso v(f) è sempre uguale alla capacità del taglio cap(A, B)» *(traccia 26/06/2025)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Per la dualità debole vale solo $\operatorname{val}(f)\leq\operatorname{cap}(A,B)$, come disuguaglianza, non come uguaglianza.
>
> **Quando vale l'uguaglianza.** Solo in casi speciali: per il corollario di certificato di ottimalità, $\operatorname{val}(f)=\operatorname{cap}(A,B)$ è garanzia che $f$ è massimo e $(A,B)$ è il taglio minimo — non è quindi una proprietà valida per un flusso e un taglio scelti arbitrariamente.
### Esistenza di un taglio di capacità uguale a val(f)
> [!question] Domanda d'esame — Esistenza di un taglio di capacità uguale a val(f)
> **D:** *(Vero o Falso)* «Dato un flusso f di G, c'è sempre un s-t-taglio (A, B) la cui capacità è uguale a v(f).» *(traccia 02/02/2026)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Vale solo il verso debole: per **ogni** taglio $(A,B)$, $\operatorname{cap}(A,B)\geq\operatorname{val}(f)$ (dualità debole), ma non è garantito che esista un taglio con capacità **esattamente** uguale a $\operatorname{val}(f)$.
>
> **Eccezione.** Solo se $f$ è già un flusso massimo: in quel caso il taglio minimo, individuato dai nodi raggiungibili da $s$ in $G_f$, ha proprio capacità $\operatorname{val}(f)$.
>
> **Caso generico.** Per un flusso $f$ non massimo, tutti i tagli possono avere capacità strettamente maggiore di $\operatorname{val}(f)$.
### Variante: esistenza di un taglio di capacità uguale al valore di f
> [!question] Domanda d'esame — Variante: esistenza di un taglio di capacità uguale al valore di f
> **D:** *(Vero o Falso)* «Per ogni flusso f, esiste sempre un taglio (A, B) la cui capacità è uguale al valore di f.» *(traccia 30/06/2026)*

> [!info]- Risposta modello
> Falsa, per lo stesso motivo dell'item precedente.
>
> **Perché.** La dualità debole garantisce solo $\operatorname{cap}(A,B)\geq\operatorname{val}(f)$ per ogni taglio, non l'esistenza di un taglio con uguaglianza esatta.
>
> **Quando esiste garantito.** Solo se $f$ è un flusso massimo (è allora il taglio minimo, per il teorema Max-Flow Min-Cut); per un flusso qualsiasi non c'è alcuna garanzia.
### Esistenza di un taglio di capacità strettamente maggiore di val(f)
> [!question] Domanda d'esame — Esistenza di un taglio di capacità strettamente maggiore di val(f)
> **D:** *(Vero o Falso)* «Per ogni flusso f esiste sempre almeno un taglio (A, B) tale che la capacità di (A, B) è strettamente più grande del valore di f.» *(traccia 30/06/2026)*

> [!info]- Risposta modello
> Falsa.
>
> **Controesempio.** Una rete con un solo arco $s\to t$ di capacità $c(s,t)=k$ e flusso $f(s,t)=k$ (cioè $f$ è già massimo, $\operatorname{val}(f)=k$). L'unico taglio st possibile è $(\{s\},\{t\})$, con $\operatorname{cap}(\{s\},\{t\})=k=\operatorname{val}(f)$: non esiste alcun altro taglio, quindi nessun taglio ha capacità strettamente maggiore di $\operatorname{val}(f)$.
>
> **Osservazione.** In generale, quando $f$ è massimo, il taglio minimo ha capacità esattamente uguale a $\operatorname{val}(f)$, non strettamente maggiore.
## Max-Flow Min-Cut e cammini aumentanti
### Enunciato del teorema Max-Flow Min-Cut e certificato di ottimalità
> [!question] Domanda costruita — Enunciato del teorema Max-Flow Min-Cut e certificato di ottimalità
> **D:** Enuncia il teorema Max-Flow Min-Cut e spiega quando Ford-Fulkerson fornisce un certificato di ottimalità.

> [!info]- Risposta modello
> **Enunciato.** $\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A,B)$.
>
> **Quando c'è il certificato.** Alla terminazione di Ford-Fulkerson: a quel punto non esistono cammini aumentanti, quindi l'insieme $A$ dei nodi raggiungibili da $s$ in $G_f$ definisce un taglio $(A, B)$ con $\operatorname{cap}(A,B) = \operatorname{val}(f)$, certificando che il flusso è massimo e il taglio è minimo.
### Grafi con taglio minimo di capacità inferiore al massimo flusso
> [!question] Domanda d'esame — Grafi con taglio minimo di capacità inferiore al massimo flusso
> **D:** *(Vero o Falso)* «Ci sono dei grafi per cui la capacità del taglio di capacità minima è strettamente inferiore al massimo flusso.» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Per il teorema Max-Flow Min-Cut il valore del massimo flusso è **sempre uguale** alla capacità del taglio di capacità minima ($\max_f\operatorname{val}(f)=\min_{(A,B)}\operatorname{cap}(A,B)$), mai strettamente inferiore.
>
> **Osservazione.** La dualità debole esclude già che il taglio minimo possa avere capacità inferiore al massimo flusso; il teorema garantisce inoltre che la disuguaglianza diventa sempre uguaglianza per il taglio ottimo.
### Flusso massimo e assenza di cammini nella rete residua
> [!question] Domanda d'esame — Flusso massimo e assenza di cammini nella rete residua
> **D:** *(Vero o Falso)* «Dato un flusso f, f è massimo solo se nella rete residua G_f non c'è alcun cammino da s a t.» *(traccia 30/06/2026)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È il teorema dei cammini aumentanti: $f$ è massimo se e solo se non esiste un cammino aumentante in $G_f$.
>
> **Direzione richiesta.** La direzione «solo se» ($f$ massimo $\Rightarrow$ nessun cammino aumentante) segue per contronominale: se un cammino aumentante esistesse, AUGMENT produrrebbe un flusso di valore strettamente maggiore, contraddicendo la massimalità di $f$.
### Assenza di cammino aumentante e massimalità del flusso
> [!question] Domanda d'esame — Assenza di cammino aumentante e massimalità del flusso
> **D:** *(Vero o Falso)* «Dato un flusso f, se nella rete residua Gf non c'è alcun cammino da s a t, allora f è un flusso massimo.» *(traccia 26/06/2025)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È la direzione $[3\Rightarrow 2]$ del teorema dei cammini aumentanti: se non ci sono cammini $s\leadsto t$ in $G_f$, si può costruire il taglio $(A,B)$ con $A$ = nodi raggiungibili da $s$ in $G_f$; tutti gli archi da $A$ a $B$ risultano saturi e quelli da $B$ ad $A$ hanno flusso nullo.
>
> **Conclusione.** Quindi $\operatorname{cap}(A,B)=\operatorname{val}(f)$, che per il corollario di certificato di ottimalità implica che $f$ è massimo.
### Presenza di un cammino aumentante e massimalità del flusso
> [!question] Domanda d'esame — Presenza di un cammino aumentante e massimalità del flusso
> **D:** *(Vero o Falso)* «Dato un flusso f, se nella rete residua Gf c'è un cammino da s a t, allora f non è massimo.» *(traccia 02/02/2026)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** È la contronominale della direzione $[2\Rightarrow 3]$ del teorema dei cammini aumentanti: se esiste un cammino aumentante $P$ in $G_f$, $\operatorname{AUGMENT}(f,c,P)$ produce un flusso $f'$ con $\operatorname{val}(f')=\operatorname{val}(f)+\operatorname{bottleneck}(G_f,P)>\operatorname{val}(f)$, quindi $f$ non poteva essere massimo.
>
> **Nota sul gruppo.** Questi tre item sono lo **stesso teorema** letto nelle due direzioni e nella contronominale: se sai enunciarlo come *se e solo se*, li chiudi tutti e tre senza ragionare da capo.
### Dimostrazione: assenza di cammino aumentante e flusso massimo
> [!question] Domanda d'esame — Dimostrazione: assenza di cammino aumentante e flusso massimo
> **D:** «Si dimostri che se nella rete residua corrispondente ad un certo flusso f non c'è nessun cammino dalla sorgente al pozzo, allora f è un flusso massimo. (Max 5 righe.)» *(traccia 23/09/2025)*

> [!info]- Risposta modello
> **Impostazione.** Sia $A$ l'insieme dei nodi raggiungibili da $s$ in $G_f$: per ipotesi $t\notin A$ (altrimenti esisterebbe un cammino aumentante), quindi $(A,B)$ con $B=V\setminus A$ è un taglio st valido.
>
> **Archi da $A$ a $B$ sono saturi.** Per ogni arco $e=(u,v)$ con $u\in A,v\in B$: se fosse $f(e)<c(e)$, allora $e$ apparterrebbe a $G_f$ e $v$ sarebbe raggiungibile da $s$, contraddicendo $v\in B$; dunque $f(e)=c(e)$.
>
> **Archi da $B$ a $A$ hanno flusso nullo.** Per ogni arco $e=(v,u)$ con $v\in B,u\in A$: se fosse $f(e)>0$, l'arco inverso apparterrebbe a $G_f$ rendendo $v$ raggiungibile da $s$, assurdo; dunque $f(e)=0$.
>
> **Conclusione.** Per il lemma del valore del flusso, $\operatorname{val}(f)=\sum_{e\text{ esce da }A} f(e)-\sum_{e\text{ entra in }A} f(e)=\sum_{e\text{ esce da }A} c(e)-0=\operatorname{cap}(A,B)$. Per il corollario di certificato di ottimalità, $\operatorname{val}(f)=\operatorname{cap}(A,B)$ implica che $f$ è un flusso massimo. $\square$
>
> ⏱️ **In 5 righe**: definisci $A$ e il taglio $(A,B)$ (1 riga), enuncia perché gli archi $A\to B$ sono saturi e quelli $B\to A$ nulli (2 righe, l'argomento «altrimenti il nodo sarebbe raggiungibile» in forma compatta), chiudi con $\operatorname{val}(f)=\operatorname{cap}(A,B)$ e il richiamo al corollario (1-2 righe). **Non omettere mai** il perché gli archi sono saturi/nulli — è il cuore della dimostrazione, non un dettaglio tecnico.
## Taglio minimo: estrazione e perturbazioni
### Taglio minimo costruito dai nodi che raggiungono t
> [!question] Domanda d'esame — Taglio minimo costruito dai nodi che raggiungono t
> **D:** *(Vero o Falso)* «Sia f un flusso tale che, nella rete residua Gf, s e t sono separati. Sia B l'insieme di tutti e soli i nodi che possono raggiungere t. Allora (V \ B, B) è un taglio minimo di G.» *(traccia 26/06/2025)*

> [!info]- Risposta modello
> Vera.
>
> **Impostazione.** È la costruzione duale di quella standard (che usa $A$ = nodi raggiungibili **da** $s$): qui $B$ = nodi che possono **raggiungere** $t$ in $G_f$. Se $s$ e $t$ sono separati in $G_f$, allora $s\notin B$ (altrimenti esisterebbe un cammino da $s$ a $t$), quindi $(V\setminus B, B)$ è un taglio st valido.
>
> **Argomento di saturazione.** Ogni arco entrante in $B$ dall'esterno deve essere saturo (altrimenti l'origine dell'arco potrebbe raggiungere $t$ e starebbe in $B$); ogni arco uscente da $B$ verso l'esterno ha flusso nullo.
>
> **Conclusione.** Si ottiene $\operatorname{cap}(V\setminus B,B)=\operatorname{val}(f)$, che per il corollario di certificato di ottimalità rende $(V\setminus B,B)$ un taglio minimo.
### Calcolo di un taglio di capacità minima in tempo lineare
> [!question] Domanda d'esame — Calcolo di un taglio di capacità minima in tempo lineare
> **D:** «2. Si descriva come è possibile, dato un flusso massimo, calcolare in tempo lineare un taglio di capacità minima. (Max 5 righe.)» *(traccia 18/07/2025 · Es. 2.2)*

> [!info]- Risposta modello
> Dato un flusso massimo $f^*$, si costruisce la rete residua $G_{f^*}$ in tempo $O(m)$ e si esegue una BFS o DFS a partire da $s$, ottenendo in tempo $O(n+m)$ l'insieme $A$ dei nodi raggiungibili da $s$ in $G_{f^*}$. Si pone $B=V\setminus A$: $(A,B)$ è un taglio st, e $t\notin A$ perché $f^*$ essendo massimo non ammette cammini aumentanti (teorema dei cammini aumentanti), quindi $s$ e $t$ sono separati in $G_{f^*}$. Il tempo totale è $O(n+m)$, lineare nella dimensione della rete.
>
> ⏱️ **In 5 righe**: costruzione di $G_{f^*}$, una sola visita da $s$, definizione di $A$ e $B$, giustificazione di $t\notin A$, totale $O(n+m)$. La visita si **invoca**, non si riscrive.
### Correttezza dell'algoritmo di estrazione del taglio minimo
> [!question] Domanda d'esame — Correttezza dell'algoritmo di estrazione del taglio minimo
> **D:** «3. Si discuta in modo conciso e preciso la correttezza dell'algoritmo fornito nel punto precedente. (Max 5 righe.)» *(traccia 18/07/2025 · Es. 2.3)*

> [!info]- Risposta modello
> La correttezza segue dalla dimostrazione $[3\Rightarrow 1]$ del teorema dei cammini aumentanti: poiché $f^*$ è massimo, non esistono cammini $s\leadsto t$ in $G_{f^*}$, quindi ogni arco $e=(u,v)$ con $u\in A,v\in B$ deve essere saturo ($f^*(e)=c(e)$, altrimenti $v$ sarebbe raggiungibile da $s$) e ogni arco $e=(v,u)$ con $v\in B,u\in A$ deve avere flusso nullo ($f^*(e)=0$, altrimenti l'arco inverso renderebbe $v$ raggiungibile). Per il lemma del valore del flusso, $\operatorname{val}(f^*)=\sum_{e\text{ esce da }A} c(e) - 0=\operatorname{cap}(A,B)$: il taglio prodotto ha capacità esattamente uguale al valore del flusso massimo, e per il corollario di certificato di ottimalità questo garantisce che $(A,B)$ è un taglio minimo.
>
> **Coppia da riconoscere.** Questo item e il precedente vengono dalla **stessa traccia**, come punti 2 e 3 dello stesso Esercizio 2: l'algoritmo prima, la sua correttezza subito dopo. È la forma tipica con cui l'Esercizio 2 chiede un algoritmo.
### Aumentare di 1 la capacità di un arco e valore del flusso massimo
> [!question] Domanda d'esame — Aumentare di 1 la capacità di un arco e valore del flusso massimo
> **D:** «2. Sia G = (V, E, s, t, c) una rete di flusso di n nodi e m archi con capacità intere. Immaginate di aver già calcolato un flusso massimo f per G. Ora vi danno la possibilità di aumentare di una unità la capacità di un arco a vostra scelta. Mostrate che non è sempre possibile aumentare il valore del flusso massimo. E fornite un algoritmo di complessità O(n+m) che decide se è possibile farlo o meno. (Max 5 righe.)» *(traccia 02/02/2026 · Es. 2.2)*

> [!info]- Risposta modello
> Non è sempre possibile: aumentare $c(u,v)$ di 1 fa crescere il flusso massimo **se e solo se** quell'unità in più crea un nuovo cammino aumentante, cioè se in $G_f$ esiste un cammino $s \leadsto u$, l'arco $(u,v)$, e un cammino $v \leadsto t$.
>
> **Algoritmo $O(n+m)$.** Costruita la rete residua $G_f$, si fanno **due** visite — una BFS/DFS in avanti da $s$, che dà l'insieme $S$ dei nodi raggiungibili da $s$; una BFS/DFS all'indietro da $t$ (percorrendo gli archi residui in senso inverso), che dà l'insieme $T$ dei nodi da cui si raggiunge $t$. L'aumento su $(u,v)$ è utile **se e solo se $u \in S$ e $v \in T$**.
>
> **Attenzione.** La sola condizione $u \in S$ e $v \notin S$ **non basta**. Controesempio: rete $s\to a$, $s\to b$, $a\to t$, $b\to t$ tutte di capacità 1. Il flusso massimo vale 2, tutti gli archi sono saturi e $S=\{s\}$: l'arco $(s,a)$ soddisfa $u\in S,\ v\notin S$, ma portare $c(s,a)$ a 2 lascia il flusso massimo a 2, perché $a$ non ha comunque modo di raggiungere $t$ ($a\to t$ è saturo). Con il criterio corretto si ha $T=\{t\}$, quindi $a\notin T$ e l'arco viene giustamente scartato.
### Taglio minimo dopo l'aumento di 1 su ogni capacità
> [!question] Domanda d'esame — Taglio minimo dopo l'aumento di 1 su ogni capacità
> **D:** «2. Si consideri la seguente affermazione e si dica se è vera o falsa, giustificando la risposta. (Max 5 righe.) Claim: Sia (A, B) un s-t-cut di capacità minima per la rete G. Sia G' la rete ottenuta da G aumentando la capacità di ogni arco di esattamente 1. Allora (A, B) è un s-t-cut di capacità minima anche per G'.» *(traccia 30/06/2026 · Es. 2.2)*

> [!info]- Risposta modello
> Falsa.
>
> **Perché.** Aumentando la capacità di **ogni** arco di 1, la capacità di un taglio $(A,B)$ cresce di una quantità pari al numero di archi che lo attraversano da $A$ a $B$: $\operatorname{cap}_{G'}(A,B)=\operatorname{cap}_G(A,B)+|\{e=(u,v): u\in A, v\in B\}|$. Tagli diversi possono avere un numero diverso di archi uscenti da $A$, quindi l'incremento **non è uniforme** tra i tagli: un taglio $(A',B')$ che in $G$ aveva capacità leggermente superiore a $\operatorname{cap}_G(A,B)$ ma è attraversato da meno archi può ricevere un incremento minore e risultare, in $G'$, di capacità inferiore a quella di $(A,B)$. Quindi il taglio minimo può cambiare.
>
> **Confronto con MST.** È la gemella della domanda «$+1$ su ogni arco» per l'MST, dove però la risposta è **opposta**: lì tutti gli spanning tree hanno lo stesso numero di archi ($n-1$), quindi l'incremento è uniforme e l'MST non cambia. Qui i tagli hanno cardinalità diversa, e l'uniformità salta. È esattamente il **numero di archi attraversati** a fare la differenza.
## Scelta dei cammini aumentanti
### Scelta dei cammini aumentanti: Ford-Fulkerson e Edmonds-Karp
> [!question] Domanda costruita — Scelta dei cammini aumentanti: Ford-Fulkerson e Edmonds-Karp
> **D:** Perché Ford-Fulkerson generico è pseudo-polinomiale e come Edmonds-Karp risolve il problema?

> [!info]- Risposta modello
> Ford-Fulkerson generico può avere $\Theta(C)$ iterazioni (esempio con arco di capacità $C$ al centro e alternanza di cammini che portano solo 1 unità per volta), quindi la complessità $O(mnC)$ dipende dai valori delle capacità, non solo da $m$ e $n$. Edmonds-Karp usa la BFS per scegliere sempre il cammino con **meno archi**: questo garantisce che le distanze BFS siano monotone non decrescenti, limitando il numero totale di aumenti a $O(mn)$ indipendentemente dai valori di $C$, ottenendo complessità polinomiale $O(m^2 n)$.
### BFS per i cammini aumentanti e polinomialità
> [!question] Domanda d'esame — BFS per i cammini aumentanti e polinomialità
> **D:** *(Vero o Falso)* «L'algoritmo di Ford-Fulkerson, se si usa la visita BFS per trovare i cammini aumentanti, ha una complessità polinomiale nella dimensione dell'istanza.» *(traccia 09/09/2024)*

> [!info]- Risposta modello
> Vera.
>
> **Perché.** Usare la BFS per scegliere sempre il cammino aumentante con il minor numero di archi è esattamente l'algoritmo di Edmonds-Karp, la cui complessità è $O(m^2n)$ (al più $O(mn)$ aumenti, ciascuno $O(m)$ con la BFS).
>
> **Conclusione.** Questo bound dipende solo da $n$ e $m$, non dal valore delle capacità: a differenza di Ford-Fulkerson generico, è quindi polinomiale nella dimensione dell'istanza indipendentemente da $C$.
