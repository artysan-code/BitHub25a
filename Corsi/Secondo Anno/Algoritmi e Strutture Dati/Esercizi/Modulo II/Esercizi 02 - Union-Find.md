---
tags:
  - algoritmi
  - union-find
  - esercizi
nota: "[[02 - Union-Find]]"
---
# Esercizi — Union-Find
Palestra della nota [[02 - Union-Find]]. Ogni item è una **domanda d'esame reale**, con traccia, posizione e limite verbatim; la risposta modello sta in un callout **richiudibile**, da aprire solo dopo aver scritto la propria. Un item è chiuso quando la risposta esce senza aprire il callout.
Nel campione Union-Find allo scritto è **sempre analisi di costi e proprietà**: lo pseudocodice della struttura non è mai stato chiesto. Ricorre invece la richiesta di **costruire a mano** una sequenza che realizzi un caso peggiore.

> [!warning] La trappola ricorrente
> Le domande su Union-Find arrivano spesso **travestite da domande su Kruskal** — sei dei quindici item qui sotto sono di questo tipo. Quando leggi «Kruskal implementato con QuickFind…», la domanda è sui costi della struttura.

> [!warning] Due item vengono da una configurazione d'esame non più osservata
> Gli item **«Tre union ciascuna di costo Θ(n)»** e **«Enunciare le prestazioni della struttura»** vengono dal 18/07/2022, l'unico appello del materiale in cui **Union-Find occupa un intero Esercizio 2** — teoria pura da 11 punti, con due sotto-domande da 5 righe.
>
> Nelle 14 tracce dall'a.a. 2023-24 in poi questo **non accade più**: Union-Find compare **solo in Esercizio 1**, come affermazione vero/falso o come claim da argomentare, spesso travestita da domanda su Kruskal. In Esercizio 2 ruotano MST, Flussi, Greedy, NP e Approssimazione — mai Union-Find.
>
> Cosa farne: il **contenuto** resta pienamente valido, ed è esattamente quello su cui vertono i vero/falso di oggi — la sequenza costosa e i costi ammortizzati sono le due cose che l'esame chiede comunque. Cambia il **formato in cui aspettarselo**: allenali come materiale da Esercizio 1 e da orale, non come un'esercitazione di teoria da 11 punti.
## Lower bound
### Lower bound Ω(m+n) per qualunque struttura dati
> [!question] Domanda d'esame — Lower bound Ω(m+n) per qualunque struttura dati
> **D:** *(Vero o Falso)* «Ogni struttura dati, per eseguire una sequenza di $n$ makeSet, $n-1$ union e $m$ find, deve impiegare nel caso peggiore tempo $\Omega(m+n)$.» *(traccia 16/07/2024 · Es. 1.1 n. 4 · anche 18/02/2025 Es. 1.1 n. 4)*

> [!info]- Risposta modello
> **Vero.**
>
> **Perché.** Le $n$ `makeSet` devono creare $n$ insiemi (tempo $\Omega(n)$ solo per allocarli), e le $m$ `find` devono restituire una risposta ciascuna ($\Omega(1)$ a query, quindi $\Omega(m)$). Nessuna struttura può evitare di toccare ogni elemento creato e ogni interrogazione ricevuta.
>
> **Coerenza.** Tutte le implementazioni viste hanno un termine additivo $n$ o $m$ nella complessità totale; le migliori (rank + path compression) si avvicinano al bound aggiungendo solo $\alpha(m,n)$.
## QuickFind
### Tre union ciascuna di costo Θ(n)
> [!question] Domanda d'esame — Tre union ciascuna di costo Θ(n) in QuickFind
> **D:** «Si fornisca un esempio di una sequenza di 3 operazioni di union in cui ogni singola operazione di union ha costo $\Theta(n)$. (Max 5 righe.)» *(traccia 18/07/2022 · Es. 2.1 · «Max 5 righe» · configurazione non più osservata, vedi l'avviso in testa)*

> [!info]- Risposta modello
> **Idea.** In QuickFind base `union(X,Y)` rietichetta **sempre e solo** le foglie del **secondo** argomento, qualunque sia la sua dimensione: basta passare come secondo argomento un insieme già grande.
>
> **Costruzione.** $n=4k$ elementi ripartiti in quattro insiemi $A,B,C,D$ da $k=n/4$ (le union preliminari non si contano). Poi: `union(A,B)` rietichetta $B$ ($k$ elementi); `union(C,D)` rietichetta $D$ ($k$); `union(A,C)` rietichetta $C$, che ora contiene $C \cup D$, cioè $2k$.
>
> **Verifica.** $k$, $k$ e $2k$ sono tutte $\Theta(n)$: ciascuna delle tre union costa $\Theta(n)$.
>
> ⏱️ **In 5 righe**: i quattro insiemi da $k=n/4$ e le tre chiamate (2 righe), poi perché ognuna costa $\Theta(n)$ (1 riga) — **non va mai omesso** il motivo per cui basta passare l'insieme grande come secondo argomento: è il fatto strutturale su cui si regge il controesempio.
### L'altezza resta 1 anche con union by size
> [!question] Domanda d'esame — QuickFind + union by size: l'altezza resta 1
> **D:** *(Vero o Falso)* «Nella QuickFind con euristica union by size ogni insieme è rappresentato con un albero di altezza $\Theta(\log n)$, dove $n$ è il numero di makeSet, in modo che l'operazione di find richieda tempo logaritmico.» *(traccia 16/07/2024 · Es. 1.1 n. 1)*

> [!info]- Risposta modello
> **Falso.**
>
> **Perché.** La union by size cambia **chi viene attaccato a chi**, non la forma degli alberi: in QuickFind ogni albero resta **sempre di altezza 1** (radice + foglie), con o senza euristica. È questo a garantire alla `find` costo $O(1)$, non logaritmico.
>
> **L'errore che la domanda induce.** Confondere l'euristica che riduce l'altezza (utile solo in QuickUnion) con quella che bilancia le dimensioni (utile qui, ma senza effetto sull'altezza, che è già fissa a 1). In QuickFind la union by size migliora il costo **ammortizzato** della `union`, non la `find`.
### Cambi di padre e raddoppio della size
> [!question] Domanda d'esame — Cambio di etichetta e raddoppio della size
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickFind con euristica union by size, se in una sequenza di operazioni un elemento ha cambiato padre $k$ volte allora appartiene ad un insieme che è grande almeno $2^k$.» *(traccia 16/07/2024 · Es. 1.1 n. 3)*

> [!info]- Risposta modello
> **Vero.**
>
> **Perché.** Per induzione su $k$: alla nascita l'elemento è in un insieme di dimensione $1 = 2^0$; a ogni cambio di padre, per l'euristica finisce in un insieme di cardinalità **almeno doppia** rispetto a quello di provenienza. Dopo $k$ cambi è quindi in un insieme di dimensione $\geq 2^k$.
>
> **A cosa serve.** È l'argomento che limita i cambi di padre: da $2^k \leq n$ segue $k \leq \log_2 n$, ed è da lì che nasce il bound $O(n \log n)$ sul totale delle union.
### Il bound O(m + n log n)
> [!question] Domanda d'esame — QuickFind + union by size: il bound O(m + n log n)
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickFind con euristica union by size, ogni sequenza di $n$ makeSet, $n-1$ union e $m$ find richiede nel caso peggiore tempo $O(m + n\log n)$.» *(traccia 16/07/2024 · Es. 1.1 n. 2 · anche 18/02/2025 Es. 1.1 n. 3)*

> [!info]- Risposta modello
> **Vero.**
>
> **Perché.** $n$ `makeSet` e $m$ `find` costano $O(1)$ ciascuna, quindi $O(m+n)$; per le $n-1$ `union`, l'argomento del raddoppio limita a $O(\log n)$ i cambi di etichetta per elemento, quindi $O(n\log n)$ in totale. Sommando, $O(m + n\log n)$.
>
> **Il punto da non sbagliare.** È un bound sul **caso peggiore dell'intera sequenza**, non della singola operazione: una singola `union` può ancora costare $\Theta(n)$, ma non tutte insieme.
### Enunciare le prestazioni della struttura
> [!question] Domanda d'esame — Enunciato preciso delle prestazioni
> **D:** «Si enunci in modo preciso le prestazioni della struttura dati, in termini di costi delle operazioni della struttura dati. (Max 5 righe.)» *(traccia 18/07/2022 · Es. 2.2 · «Max 5 righe» · configurazione non più osservata, vedi l'avviso in testa)*

> [!info]- Risposta modello
> **Operazione singola.** `makeSet` e `find` costano $O(1)$ ciascuna. Una singola `union` costa $O(\text{dimensione dell'insieme più piccolo})$, quindi $O(n)$ nel caso pessimo.
>
> **Ammortizzato.** Con union by size ogni elemento cambia etichetta al più $O(\log n)$ volte (a ogni cambio la size almeno raddoppia), quindi le $\leq n-1$ union costano complessivamente $O(n\log n)$.
>
> **Sequenza intera.** Con $n$ makeSet, $\leq n-1$ union e $m$ find: $O(m + n\log n)$.
>
> ⏱️ **In 5 righe**: i tre costi singoli (1 riga), il motivo dell'ammortamento (1-2 righe), il bound sulla sequenza (1 riga) — **non va mai omesso** che l'$O(\log n)$ della union è *ammortizzato sulla sequenza*: la singola union resta $O(n)$.
## QuickUnion
### L'altezza NON è 1
> [!question] Domanda d'esame — QuickUnion + union by size: l'altezza non è 1
> **D:** *(Vero o Falso)* «Nella QuickUnion con euristica union by size ogni insieme è rappresentato con un albero di altezza 1, in modo che sia l'operazione di find che di union richiedano tempo logaritmico.» *(traccia 18/02/2025 · Es. 1.1 n. 1)*

> [!info]- Risposta modello
> **Falso, e sbagliata su due fronti.**
>
> **Primo errore.** L'altezza 1 è di **QuickFind**, non di QuickUnion: qui il lemma $s \geq 2^h$ garantisce altezza $O(\log n)$, non costante.
>
> **Secondo errore.** La `union` in QuickUnion resta $O(1)$ (ricollega due radici): è la `find` a costare $O(\log n)$, non entrambe.
### find è O(log n) nel caso peggiore, non solo ammortizzato
> [!question] Domanda d'esame — find O(log n) nel caso peggiore, non ammortizzato
> **D:** *(Vero o Falso)* «Usando la struttura dati QuickUnion con euristica union by size, ogni operazione di find ha costo ammortizzato $O(\log n)$, dove $n$ è il numero di makeSet. Eppure una singola operazione di find nel caso peggiore può costare anche $\Theta(n)$.» *(traccia 18/02/2025 · Es. 1.1 n. 2)*

> [!info]- Risposta modello
> **Falso.**
>
> **Perché.** Con la sola union by size il lemma $s \geq 2^h$ garantisce che **ogni** albero con $n$ nodi ha altezza $O(\log n)$: è un bound **deterministico sul caso peggiore**, non ammortizzato. Quindi anche la **singola** `find` costa $O(\log n)$, e non può mai costare $\Theta(n)$ con l'euristica attiva.
>
> **Da dove nasce la confusione.** Da QuickUnion **senza** euristiche, dove una singola find può davvero costare $\Theta(n)$ su una sequenza degenere che produce una lista.
### Costruire un albero di altezza Θ(log n)
> [!question] Domanda d'esame — Costruire un albero di altezza Θ(log n)
> **D:** «Si consideri la struttura dati QuickUnion con euristica union by size. Si mostri una sequenza di operazioni di $n$ makeSet e $n-1$ union in cui l'albero ottenuto abbia altezza $\Theta(\log n)$. (Max 5 righe.)» *(traccia 16/07/2024 · Es. 1.2 · «Max 5 righe» · anche 18/02/2025 Es. 1.2)*

> [!info]- Risposta modello
> **Idea.** Sfruttare il caso peggiore ammesso dal lemma: l'altezza cresce di 1 **solo** quando si uniscono due alberi di size uguale. Un torneo a eliminazione fra alberi di pari dimensione realizza sistematicamente questo caso.
>
> **Costruzione.** Con $n = 2^k$ elementi: $n$ `makeSet`, poi union a torneo per round. Primo round: $n/2$ union fra singoletti → $n/2$ alberi di altezza 1. Secondo round: union a coppie fra alberi di altezza 1 e size uguale → $n/4$ alberi di altezza 2. E così via.
>
> **Verifica.** Dopo $k = \log_2 n$ round (in totale $n-1$ union) resta un unico albero di altezza esattamente $k = \Theta(\log n)$.
>
> ⏱️ **In 5 righe**: il torneo per round (2 righe), perché ogni round incrementa l'altezza di 1 (1-2 righe), la conclusione dopo $\log_2 n$ round (1 riga) — **non va mai omesso** il perché l'altezza cresce solo con size uguali: è la condizione che rende il caso peggiore.
## Union-Find dentro Kruskal
### Quale struttura, quali operazioni, come si usano
> [!question] Domanda d'esame — Union-Find in Kruskal: struttura, operazioni, uso
> **D:** «B. Si dica quale struttura dati viene utilizzata nell'implementazione efficiente dell'algoritmo di Kruskal, quali operazioni mette a disposizione la struttura dati e come queste vengono usate nell'algoritmo. (Max 10 righe.)» *(traccia 19/02/2024 · Es. 1.2 · «Max 10 righe» · formato ridotto)*

> [!info]- Risposta modello
> **Struttura.** Union-Find (gestione di insiemi disgiunti).
>
> **Operazioni.** `makeSet(x)` crea il singoletto $\{x\}$; `union(A,B)` fonde due insiemi; `find(x)` restituisce il nome dell'insieme che contiene $x$.
>
> **Uso in Kruskal.** Ogni insieme è una componente connessa dell'albero in costruzione: una `makeSet` per ciascuno degli $n$ nodi, poi si scandiscono gli $m$ archi in ordine di peso crescente e per ogni arco $(u,v)$ si confrontano `find(u)` e `find(v)`. Se differiscono l'arco entra nell'MST e si esegue `union`; se coincidono l'arco si scarta, perché chiuderebbe un ciclo.
>
> **Complessità.** Con union by rank + path compression, le $O(m)$ find e le $n-1$ union costano $O(m \cdot \alpha(m,n))$, praticamente lineare.
>
> ⏱️ **In 10 righe**: struttura e tre operazioni (3-4 righe), uso in Kruskal (3-4 righe), complessità (1-2 righe) — **non va mai omesso** il legame fra `find(u) ≠ find(v)` e il test «l'arco chiuderebbe un ciclo?»: è il punto in cui la struttura entra nella logica dell'algoritmo.
### Kruskal con QuickFind senza euristica
> [!question] Domanda d'esame — Kruskal con QuickFind senza euristica non è (solo) O(n²)
> **D:** *(Vero o Falso)* «Se si implementa l'algoritmo di Kruskal con la struttura dati Quick-Find senza euristica di bilanciamento union-by-size, la complessità dell'algoritmo nel caso peggiore è $O(n^2)$.» *(traccia 13/06/2024 · Es. 1.1 n. 3)*

> [!info]- Risposta modello
> **Falso.**
>
> **Costi della struttura.** $n-1$ union a $O(n)$ ciascuna → $O(n^2)$; $O(m)$ find a $O(1)$ → $O(m)$.
>
> **Il costo dimenticato.** Kruskal deve **ordinare gli $m$ archi**: $O(m \log m)$. La complessità corretta è $O(m\log m + n^2)$.
>
> **Perché l'affermazione è falsa.** Su grafo denso con $m = \Theta(n^2)$ il termine $m\log m = \Theta(n^2\log n)$ domina $n^2$: la complessità reale è $\Theta(n^2\log n)$, diversa da $O(n^2)$.
### Kruskal senza union by size con O(n^{3/2}) archi
> [!question] Domanda d'esame — Kruskal senza union by size con |E| = O(n^{3/2})
> **D:** «Qual è la complessità nel caso peggiore dell'algoritmo di Kruskal implementato con la struttura dati Union-Find senza l'uso dell'euristica union by size se il numero di archi $|E| = O(n^{3/2})$? [risposta in 1 riga]» *(traccia 27/09/2023 · Es. 1.2 n. 1 · «risposta in 1 riga» · formato Clementi)*

> [!info]- Risposta modello
> **$O(n^{5/2})$.**
>
> **Giustificazione.** Senza union by size la `find` costa $O(n)$ nel caso peggiore (l'albero degenera in lista), quindi le $O(|E|)$ find costano $O(n^{3/2} \cdot n) = O(n^{5/2})$. Questo termine domina sia l'ordinamento $O(n^{3/2}\log n)$ sia le union ($O(n^2)$ in totale, e $n^2 = o(n^{5/2})$).
>
> ⏱️ **In 1 riga**: scrivi solo $O(n^{5/2})$ — **il valore finale non va mai omesso**, la giustificazione è ciò che si taglia se lo spazio manca.
### Kruskal con QuickFind + union by size, archi già ordinati
> [!question] Domanda d'esame — QuickFind + union by size, archi già ordinati
> **D:** *(Vero o Falso)* «Si assuma di implementare Kruskal usando una struttura dati QuickFind con euristica union by size, e di avere già gli archi ordinati in ordine non decrescente di peso. Allora l'esecuzione ha complessità temporale $O(m + n\log n)$.» *(traccia 18/02/2025 · Es. 1.1 n. 5)*

> [!info]- Risposta modello
> **Vero.**
>
> **Perché.** Con gli archi già ordinati cade il costo $O(m\log m)$. Restano le $O(m)$ find a $O(1)$ ciascuna, quindi $O(m)$, e le $n-1$ union, che con union by size costano complessivamente $O(n\log n)$. Totale $O(m + n\log n)$, cioè esattamente il bound generale della QuickFind con union by size.
### Kruskal con QuickUnion + union by size, archi già ordinati
> [!question] Domanda d'esame — QuickUnion + union by size, archi già ordinati
> **D:** *(Vero o Falso)* «Si assuma di implementare Kruskal usando una struttura dati QuickUnion con euristica union by size, e di avere già gli archi ordinati in ordine non decrescente di peso. Allora l'esecuzione ha comunque complessità temporale $O(m\log n)$.» *(traccia 16/07/2024 · Es. 1.1 n. 5)*

> [!info]- Risposta modello
> **Vero.**
>
> **Perché.** Niente ordinamento; restano $n$ makeSet ($O(n)$), $n-1$ union a $O(1)$ ciascuna ($O(n)$) e $O(m)$ find a $O(\log n)$ ciascuna per il lemma $s \geq 2^h$. Le find dominano: $O(m\log n)$.
>
> **Il passaggio che chiude.** $O(n + m\log n) = O(m\log n)$ perché $m \geq n-1$ (il grafo è connesso, altrimenti non esisterebbe uno spanning tree): è questa disuguaglianza ad assorbire il termine $O(n)$.
### Kruskal con una Union-Find ipotetica
> [!question] Domanda d'esame — Kruskal con find O(log log n)
> **D:** «2. Immaginate di implementare l'algoritmo di Kruskal con un'altra struttura dati Union-Find i cui costi delle operazioni sono: la MakeSet e l'operazione di Union hanno costo costante, mentre la Find costa $O(\log\log n)$. Quale sarebbe la complessità dell'algoritmo di Kruskal? Giustificate la risposta. (Max 5 righe.)» *(traccia 28/09/2022 · Es. 1.2 · «Max 5 righe»)*

> [!info]- Risposta modello
> **$O(m\log m)$**, equivalentemente $O(m\log n)$ dato che $m < n^2$ implica $\log m = O(\log n)$.
>
> **Gestione degli insiemi.** $n$ makeSet e $n-1$ union a costo costante: $O(n)$. $O(m)$ find a $O(\log\log n)$: $O(m\log\log n)$.
>
> **Chi domina.** Kruskal deve comunque ordinare gli $m$ archi, $O(m\log m)$, che domina entrambi perché $\log\log n = o(\log m)$.
>
> **Il punto della domanda.** La gestione degli insiemi diventa **irrilevante**: è l'ordinamento a determinare il costo totale. Rendere la Find più veloce non migliora Kruskal finché gli archi vanno ordinati.
>
> ⏱️ **In 5 righe**: il risultato subito (1 riga), i costi della struttura (1-2 righe), perché domina l'ordinamento (1-2 righe) — **non va mai omesso** che è l'ordinamento a dominare: è il punto concettuale, non il valore in sé.
## Come usare questa pagina
Allo scritto Union-Find non chiede mai lo pseudocodice della struttura: chiede **costi, proprietà e costruzioni di casi peggiori**. Allenati in quest'ordine: prima la tabella dei costi delle quattro implementazioni **a memoria**, poi i due vero/falso che distinguono *caso peggiore* da *ammortizzato* (sono la coppia su cui si scivola), poi le due costruzioni a mano (le tre union da $\Theta(n)$ e il torneo di altezza $\Theta(\log n)$), infine i sei item su Kruskal, che sono domande sulla struttura travestite.
