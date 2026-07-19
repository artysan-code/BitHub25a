---
tags:
  - algoritmi
  - union-find
  - esercizi
---
# Vero/Falso — Union-Find
*Esercizio 1 · Union-Find · 12 domande da 5 appelli (13/06/2024, 16/07/2024, 18/02/2025, 18/07/2025, 09/09/2025).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 13/06/2024, 16/07/2024, 18/02/2025, 18/07/2025, 09/09/2025.*
## Come leggere questo file
Union-Find compare in Es. 1 in **due forme distinte**, e vanno preparate entrambe. Come **esercizio dedicato** — batteria completa di cinque affermazioni V/F più una domanda aperta costruttiva — è uscito il 16/07/2024 e il 18/02/2025. Come **singola affermazione annidata** dentro una batteria altrimenti dedicata a MST è invece uscita il 13/06/2024, il 18/07/2025 e il 09/09/2025: chi si prepara sullo slot MST deve comunque saper rispondere a una domanda di complessità QuickFind/QuickUnion, perché il prof la infila quasi sempre come una delle cinque affermazioni di quella batteria.

I sotto-temi ricorrenti sono cinque: lo **scambio speculare** fra QuickFind e QuickUnion (chi ha altezza $1$, chi ha l'operazione logaritmica — il malinteso più sfruttato, perché i due profili di costo sono letteralmente opposti); l'**argomento del raddoppio della size**, che regge sia il bound aggregato sull'intera sequenza sia l'implicazione sul singolo elemento; la distinzione fra **costo ammortizzato e caso peggiore**, dove il lemma $s\geq 2^h$ di QuickUnion la rende superflua; il **limite inferiore universale** $\Omega(m+n)$; e soprattutto **Kruskal implementato con Union-Find**, dove la domanda di fondo è sempre la stessa — tolto o lasciato il costo di ordinamento degli archi, quale operazione domina la complessità?

Per prendere punti pieni: ogni verdetto "falsa" vuole un **controesempio scritto per esteso**, con una sequenza di operazioni concreta — mai "si può costruire un caso in cui..." senza costruirlo davvero. Nei bound ammortizzati non va mai omesso il contributo $O(m+n)$ di makeSet/find, anche se sembra ovvio ometterlo. Nel limite inferiore $\Omega(m+n)$ l'argomento va dato sul **problema stesso**, non analizzando un'implementazione specifica.
## QuickFind contro QuickUnion: struttura e profilo dei costi
Le due affermazioni che seguono sfruttano lo stesso scambio concettuale in direzioni opposte: attribuire a QuickFind l'altezza logaritmica di QuickUnion, o viceversa regalare a QuickUnion l'altezza fissa a $1$ di QuickFind.
### 1. QuickFind + union by size: altezza Θ(log n) e find logaritmica?
*16/07/2024 · Es. 1, affermazione 1* — cfr. [[02 - Union-Find#QuickFind|QuickFind]] e [[02 - Union-Find#Euristica union by size (QuickFind)|Euristica union by size (QuickFind)]].

> Nella QuickFind con euristica union by size ogni insieme è rappresentato con un albero di altezza $\Theta(\log n)$, dove $n$ è il numero di makeSet, in modo che l'operazione di find richieda tempo logaritmico.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** La union by size cambia solo *chi viene attaccato a chi*, non la forma degli alberi: in QuickFind ogni insieme resta rappresentato da un albero di altezza $1$ (radice + foglie), con o senza euristica, quindi la `find` è $O(1)$, mai logaritmica.
>
> **Controesempio.** $n=4$, elementi $\{1,2,3,4\}$. `makeSet(1)`, `makeSet(2)`, `makeSet(3)`, `makeSet(4)` creano quattro alberi di altezza $1$. `union(1,2)`: size uguali ($1=1$), $1$ assorbe $2$. `union(1,3)`: size$(1)=2\geq 1=$size$(3)$, $1$ assorbe $3$. `union(1,4)`: size$(1)=3\geq 1=$size$(4)$, $1$ assorbe $4$. Dopo le tre union l'insieme $\{1,2,3,4\}$ ha nome $1$ ed è **ancora un unico albero di altezza $1$**: radice $1$, foglie $2,3,4$. `find(4)` segue un solo puntatore e costa $O(1)$, non $\Theta(\log 4)=2$.

> [!info]- Spiegazione
> La parola critica è «in modo che... richieda tempo logaritmico»: lega falsamente altezza e costo della `find` a $\Theta(\log n)$, ma in QuickFind l'altezza è **strutturalmente fissa a $1$**, indipendentemente da quale euristica di union venga applicata. Ogni foglia punta direttamente alla radice per costruzione, non attraverso una catena di padri intermedi come in QuickUnion: la union by size decide solo quale radice sopravvive alla fusione, mai la profondità delle foglie.
>
> **L'errore-tipo è scambiare l'effetto della union by size fra le due strutture.** In QuickFind bilancia le *size*, e quindi il costo *ammortizzato* della `union` (da $O(n)$ a $O(\log n)$ ammortizzato, cfr. [[#3. QuickFind + union by size: bound O(m + n log n) sull'intera sequenza|voce 3]]) — non tocca l'altezza. In QuickUnion, invece, la stessa euristica limita davvero l'altezza a $O(\log n)$ tramite il lemma $s\geq 2^h$ ([[02 - Union-Find#Euristica union by size (QuickUnion)|dimostrazione]]) — cfr. la voce gemella subito sotto, dove l'errore corre in direzione opposta.
>
> **Dove si perdono punti:** rispondere "Vera" pensando al caso più intuitivo (bilanciamento ⇒ comportamento logaritmico) senza costruire il controesempio esplicito con la sequenza di union.
### 2. QuickUnion + union by size: altezza 1 e find/union entrambe logaritmiche?
*18/02/2025 · Es. 1, affermazione 1* — errore speculare della [[#1. QuickFind + union by size: altezza Θ(log n) e find logaritmica?|voce precedente]]: qui è QuickUnion a cui si attribuisce l'altezza $1$ propria di QuickFind.

> Nella QuickUnion con euristica union by size ogni insieme è rappresentato con un albero di altezza $1$, in modo che sia l'operazione di find che di union richiedano tempo logaritmico.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa, su due fronti indipendenti.** (1) L'altezza $1$ è una proprietà di **QuickFind**, non di QuickUnion: con union by size il lemma $s\geq 2^h$ garantisce solo altezza $O(\log n)$, che può essere maggiore di $1$. (2) Anche ammettendo altezza logaritmica, la `union` in QuickUnion resta $O(1)$ — si limita a ricollegare due radici — mentre è la sola `find` a costare $O(\log n)$: l'affermazione le rende entrambe logaritmiche, il che è falso a prescindere dal primo errore.
>
> **Controesempio (altezza).** Con $n=4$: quattro `makeSet` su $\{1,2,3,4\}$, poi `union(1,2)` (size uguali, un albero diventa figlio dell'altro: altezza $1$), poi `union(3,4)` (altezza $1$), poi `union` fra i due alberi risultanti (size entrambe $2$, uguali: per il lemma l'altezza cresce a $2$). L'albero finale ha altezza $2\neq 1$.

> [!info]- Spiegazione
> Il testo somma due errori concettuali distinti, e vanno smontati entrambi esplicitamente — liquidarne uno solo lascia punti sul tavolo.
>
> **Primo errore: l'altezza.** "Altezza 1" è la firma strutturale di [[02 - Union-Find#QuickFind|QuickFind]]: ogni foglia punta direttamente alla radice. QuickUnion, per costruzione, ammette alberi di altezza maggiore di $1$; l'euristica union by size la **limita** a $O(\log n)$ (Lemma $s\geq 2^h$, [[02 - Union-Find#Euristica union by size (QuickUnion)|dimostrazione]]), non la azzera.
>
> **Secondo errore: quale operazione è logaritmica.** In QuickUnion la `union` ricollega due puntatori radice-radice, sempre $O(1)$, indipendentemente da come sono fatti gli alberi. È la `find`, che risale i puntatori padre fino alla radice, a pagare l'altezza dell'albero — quindi $O(\log n)$ con l'euristica attiva.
>
> **Perché l'errore è seducente.** La frase è internamente incoerente già a leggerla con attenzione: un albero di altezza costante rende la `find` $O(1)$, non $O(\log n)$. Chi non nota la contraddizione interna tende a validare l'intera frase sulla fiducia, senza controllare separatamente altezza e operazioni.
>
> **Il paio con la voce precedente.** Le due affermazioni (16/07/2024 e 18/02/2025) sfruttano lo stesso scambio concettuale in direzioni opposte: là si regala a QuickFind l'altezza logaritmica di QuickUnion, qui si regala a QuickUnion l'altezza $1$ di QuickFind. È l'errore più facile da commettere senza un controesempio numerico esplicito davanti.
>
> **Dove si perdono punti:** correggere solo l'altezza ("no, è $O(\log n)$") senza notare che l'affermazione sbaglia *anche* su quale operazione sia logaritmica; oppure limitarsi a "falsa" senza costruire l'esempio con due union fra alberi di size uguale.
## Union by size: l'invariante del raddoppio
Le due voci seguenti sono la stessa proprietà del raddoppio della size letta a due livelli — aggregato sull'intera sequenza e locale sul singolo elemento — ed è la base tecnica su cui si regge il bound $O(m+n\log n)$ di QuickFind.
### 3. QuickFind + union by size: bound O(m + n log n) sull'intera sequenza
*16/07/2024 · Es. 1, affermazione 2 · e 18/02/2025 · Es. 1, affermazione 3* — enunciato identico nei due appelli. Teorema per esteso in [[02 - Union-Find#Euristica union by size (QuickFind)|Euristica union by size (QuickFind)]].

> Usando la struttura dati QuickFind con euristica union by size, ogni sequenza di $n$ makeSet, $n-1$ union e $m$ find, richiede nel caso peggiore tempo $O(m+n\log n)$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Le $n$ `makeSet` e le $m$ `find` costano $O(1)$ ciascuna, quindi $O(m+n)$ in totale. Per le (al più) $n-1$ `union` si analizza il costo per singolo elemento: ogni volta che un elemento cambia radice, per l'euristica finisce in un insieme di cardinalità **almeno doppia** rispetto a quello da cui proveniva; poiché la cardinalità massima è $n$, ogni elemento cambia radice al più $\log_2 n$ volte. Sommando su $n$ elementi, il costo totale delle union è $O(n\log n)$. In totale: $O(m+n+n\log n)=O(m+n\log n)$.

> [!info]- Spiegazione
> È l'enunciato diretto del teorema di analisi ammortizzata per QuickFind + union by size: il bound è sull'**intera sequenza**, non sulla singola operazione — una singola `union` può ancora costare $\Theta(n)$ nel caso peggiore, ma non tutte insieme.
>
> **È la versione aggregata della voce successiva** ([[#4. QuickFind + union by size: k cambi di padre implicano insieme grande almeno 2^k?|voce 4]]): lì si mostra che un singolo elemento cambia padre al più $O(\log n)$ volte perché la size raddoppia a ogni cambio; sommando questo argomento su tutti gli $n$ elementi si ottiene esattamente l'$O(n\log n)$ usato qui. Stesso argomento di raddoppio, letto a granularità diversa.
>
> Il termine $O(m+n)$ per makeSet/find è talmente ovvio da essere spesso omesso per errore: va comunque scritto, perché è quello che rende $m$ un addendo indipendente nel bound finale, non solo $n\log n$.
>
> **Dove si perdono punti:** dimostrare solo il bound sulle union e dimenticare di sommare esplicitamente il contributo $O(m+n)$ di makeSet e find.
### 4. QuickFind + union by size: k cambi di padre implicano insieme grande almeno 2^k?
*16/07/2024 · Es. 1, affermazione 3* — enunciato per esteso in [[02 - Union-Find#Euristica union by size (QuickFind)|Euristica union by size (QuickFind)]].

> Usando la struttura dati QuickFind con euristica union by size, se in una sequenza di operazioni un elemento ha cambiato padre $k$ volte allora appartiene ad un insieme che è grande almeno $2^k$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Per induzione sul numero $k$ di cambi di padre dell'elemento. *Base* ($k=0$): alla creazione con `makeSet` l'elemento è nel singoletto, dimensione $1=2^0$. *Passo*: per l'euristica union by size, ogni volta che l'elemento cambia radice l'insieme in cui finisce ha cardinalità **almeno doppia** di quello da cui proveniva (si attacca sempre il più piccolo — o pari — al più grande); se prima del cambio la dimensione era $\geq 2^{k-1}$, dopo il cambio è $\geq 2\cdot 2^{k-1}=2^k$. Dopo $k$ cambi, dimensione $\geq 2^k$.

> [!info]- Spiegazione
> **È l'implicazione diretta, letta al contrario, della voce precedente.** Da $2^k\leq n$ (la size massima possibile) segue $k\leq\log_2 n$: è esattamente l'argomento che limita a $O(\log n)$ il numero di cambi di padre per elemento, usato per dimostrare il bound $O(m+n\log n)$ sull'intera sequenza in [[#3. QuickFind + union by size: bound O(m + n log n) sull'intera sequenza|voce 3]].
>
> **Attenzione al verso della disuguaglianza:** è «almeno $2^k$», non «esattamente $2^k$». Con union fra insiemi di size molto sbilanciate (es. un insieme piccolo che viene assorbito da uno enorme, con size(enorme) $\gg$ size(piccolo)) la crescita può essere ben più che doppia — la proprietà garantisce solo il minimo.
>
> **Dove si perdono punti:** dimenticare il caso base $k=0$ nell'induzione, oppure scrivere la disuguaglianza come uguaglianza stretta.
## Costo ammortizzato contro caso peggiore
Qui il tranello non è più strutturale ma temporale: distinguere un bound ammortizzato sull'intera sequenza da un bound di caso peggiore sulla singola operazione — quando in QuickUnion con union by size i due, in realtà, coincidono.
### 5. QuickUnion + union by size: find ammortizzata O(log n) ma Θ(n) nel caso peggiore?
*18/02/2025 · Es. 1, affermazione 2* — la più insidiosa delle cinque di quell'appello: incastra una prima metà vera dentro una seconda falsa.

> Usando la struttura dati QuickUnion con euristica union by size, ogni operazione di find ha costo ammortizzato $O(\log n)$, dove $n$ è il numero di makeSet. Eppure una singola operazione di find nel caso peggiore può costare anche $\Theta(n)$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Con la sola union by size (senza compressione dei cammini), il lemma $s\geq 2^h$ garantisce che **ogni** albero costruito da una sequenza di $n$ makeSet e $n-1$ union ha altezza $O(\log n)$ — un bound **deterministico di caso peggiore**, non solo ammortizzato. Di conseguenza anche la **singola** find, nel caso peggiore, costa $O(\log n)$: non può mai costare $\Theta(n)$ con questa euristica attiva. La prima metà dell'affermazione (costo ammortizzato $O(\log n)$) è vera ma debole — il bound vale già per la singola operazione — e la seconda metà (una find può costare $\Theta(n)$) è falsa e la contraddice.

> [!info]- Spiegazione
> **La più sottile delle cinque**, perché la prima metà è un enunciato vero (quindi rassicurante) che maschera la seconda, falsa.
>
> **Perché il bound è di caso peggiore e non solo ammortizzato.** Il Lemma $s\geq 2^h$ ([[02 - Union-Find#Euristica union by size (QuickUnion)|dimostrazione]]) è una proprietà **strutturale** di ogni singolo albero prodotto da union by size, non un argomento di tipo "banking"/potenziale valido solo in media su una sequenza: vale per l'albero ottenuto dopo *qualunque* sequenza di union, quindi vale per *ogni* find eseguita su di esso, isolatamente.
>
> **Da dove nasce la tentazione "ammortizzato ma non caso peggiore".** È lo schema corretto per **altre** operazioni Union-Find — ad esempio il costo delle union in QuickFind con union by size è $O(n)$ nel caso peggiore per la singola operazione ma $O(\log n)$ solo in ammortizzato sull'intera sequenza (cfr. [[#3. QuickFind + union by size: bound O(m + n log n) sull'intera sequenza|voce 3]]). L'affermazione applica per analogia a QuickUnion+find uno schema corretto altrove ma non qui.
>
> **Quando il caso peggiore $\Theta(n)$ per find è reale.** Solo in QuickUnion **senza** alcuna euristica: la sequenza degenere $\text{union}(2,1),\text{union}(3,2),\ldots$ produce una lista di altezza $n-1$, e lì sì una find costa $\Theta(n)$. Con union by size questa degenerazione è strutturalmente impossibile.
>
> **Dove si perdono punti:** fermarsi alla prima metà ("l'ammortizzato è corretto, quindi vero") senza verificare la seconda; oppure confondere il bound di caso peggiore sull'altezza con un bound solo ammortizzato.
## Lower bound Ω(m+n)
Un solo enunciato, riproposto identico in entrambi gli appelli dedicati: il limite inferiore universale che nessuna struttura dati può evitare, dimostrato sul problema stesso e non su un'implementazione specifica.
### 6. Lower bound Ω(m+n) per qualunque struttura dati
*16/07/2024 · Es. 1, affermazione 4 · e 18/02/2025 · Es. 1, affermazione 4* — enunciato identico nei due appelli. Cfr. [[02 - Union-Find#Il problema Union-Find|Il problema Union-Find]].

> Ogni struttura dati, per eseguire una sequenza di $n$ makeSet, $n-1$ union e $m$ find, deve impiegare nel caso peggiore tempo $\Omega(m+n)$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È un limite inferiore banale ma inevitabile, indipendente dall'implementazione. Le $n$ `makeSet` devono creare $n$ nuovi insiemi: tempo $\Omega(n)$ solo per allocarli/inizializzarli. Le $m$ `find` devono restituire una risposta ciascuna: tempo $\Omega(1)$ per query, quindi $\Omega(m)$ in totale. Nessuna struttura dati, per quanto sofisticata, può evitare di "toccare" ogni elemento creato e ogni interrogazione ricevuta: da qui $\Omega(m+n)$.

> [!info]- Spiegazione
> Il bound è **universale**: non richiede di analizzare una struttura dati specifica, va argomentato sul problema stesso (ogni makeSet deve produrre un nuovo insieme accessibile, ogni find deve produrre una risposta). È questo che lo rende $\Omega$ e non solo $O$ per un'implementazione particolare.
>
> **Coerenza con tutte le implementazioni viste**, riassunte nel [[02 - Union-Find#Analisi ottimale: la funzione inversa di Ackermann|riepilogo complessità]]: QuickFind ($O(m+n^2)$ p.p.), QuickFind + union by size ($O(m+n\log n)$), QuickUnion + union by size ($O(n+m\log n)$), fino all'ottimo di Tarjan e van Leeuwen con rank + path compression ($O(n+m\cdot\alpha(m+n,n))$) — tutte presentano un termine additivo $\Omega(m+n)$ che non scompare mai, coerente col limite inferiore qui dimostrato.
>
> Non va confuso con un bound stretto per una struttura specifica: dice solo che *nessuna* struttura può scendere sotto $\Omega(m+n)$, non che tutte lo raggiungano (le migliori vi si avvicinano aggiungendo solo il fattore $\alpha(m,n)$, praticamente costante).
>
> **Dove si perdono punti:** provare a dimostrarlo analizzando una struttura dati concreta (QuickFind, QuickUnion, ...) invece di dare l'argomento universale sul problema stesso.
## Kruskal implementato con Union-Find: chi domina la complessità
Il sotto-tema più ricco della cartella: cinque domande distinte, da cinque appelli diversi, che ripropongono sempre la stessa domanda di fondo — una volta tolto (o lasciato) il costo di ordinamento degli archi, chi determina davvero la complessità di Kruskal? Compare sia come affermazione dell'esercizio dedicato sia annidata in tre batterie di MST: chi punta allo slot MST deve prepararlo comunque.
### 7. Kruskal con QuickFind senza union by size: complessità O(n²)?
*13/06/2024 · Es. 1, affermazione 3* — dal PDF `Materiale Didattico/Modulo II/Esami/2023-2024/ASD_compito2024_06_13_mod2.pdf`, terza di cinque affermazioni del punto 1 (le altre quattro sono di puro MST — cycle/cut property — e vivono in [[01 - Vero-Falso MST]]). Trascritta qui per la prima volta, verificata con `pdftotext` sul PDF originale.

> Se si implementa l'algoritmo di Kruskal con la struttura dati Quick-Find senza euristica di bilanciamento union-by-size, la complessità dell'algoritmo nel caso peggiore è $O(n^2)$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Con QuickFind senza union by size, le $n-1$ `union` costano $O(n)$ nel caso peggiore ciascuna, quindi $O(n^2)$ in totale; le $O(m)$ `find` costano $O(1)$ ciascuna, quindi $O(m)$ in totale. Ma Kruskal deve anche **ordinare gli $m$ archi**, operazione che costa $O(m\log m)$ — un costo che l'affermazione dimentica del tutto. La complessità corretta nel caso peggiore è quindi $O(m\log m + n^2)$, non semplicemente $O(n^2)$.
>
> **Controesempio.** Se il grafo è denso (ad esempio $m=\Theta(n^2)$), il termine $m\log m=\Theta(n^2\log n)$ domina su $n^2$: la complessità reale è $\Theta(n^2\log n)$, diversa da $O(n^2)$, il che rende l'affermazione falsa.

> [!info]- Spiegazione
> Il testo del prof usa la grafia con trattino («Quick-Find», «union-by-size»), diversa da quella delle altre fonti di questo file: riportata verbatim, non è un refuso da correggere, solo un'incoerenza di battitura fra compiti diversi.
>
> **Il tranello è l'ordinamento dimenticato**, lo stesso errore concettuale della voce [[#11. Θ(n√n) archi, Kruskal con QuickFind + union by size: complessità lineare?|11]] più avanti: qualunque sia l'euristica sulla Union-Find, Kruskal parte sempre da un ordinamento $O(m\log m)$ degli archi, che non scompare mai a meno che la traccia non dica esplicitamente "archi già ordinati" (cfr. le voci [[#8. Kruskal con QuickUnion + union by size, archi già ordinati: O(m log n)?|8]] e [[#9. Kruskal con QuickFind + union by size, archi già ordinati: O(m + n log n)?|9]]).
>
> **Dove si perdono punti:** calcolare solo il costo di union e find (arrivando a $O(n^2)$) e dimenticare il termine di ordinamento, che è esattamente il pezzo che rende falsa l'affermazione.
### 8. Kruskal con QuickUnion + union by size, archi già ordinati: O(m log n)?
*16/07/2024 · Es. 1, affermazione 5* — cfr. [[02 - Union-Find#Euristica union by size (QuickUnion)|Euristica union by size (QuickUnion)]] e [[02 - Union-Find#Applicazione: algoritmo di Kruskal|Applicazione: algoritmo di Kruskal]]. Variante gemella con QuickFind, stesso appello → [[#9. Kruskal con QuickFind + union by size, archi già ordinati: O(m + n log n)?|voce 9]].

> Si assuma di implementare l'algoritmo di Kruskal usando una struttura dati QuickUnion con euristica union by size. Si assuma inoltre di avere già gli archi del grafo ordinati in ordine non decrescente rispetto al loro peso. Allora l'esecuzione dell'algoritmo di Kruskal ha comunque complessità temporale $O(m\log n)$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con gli archi già ordinati si evita il costo di ordinamento $O(m\log m)$. Restano: le $n$ `makeSet`, costo $O(n)$; le $n-1$ `union`, costo $O(1)$ ciascuna in QuickUnion (ricollegano due radici), quindi $O(n)$ in totale; le $O(m)$ `find`, ciascuna $O(\log n)$ grazie al lemma $s\geq 2^h$ della union by size. Il costo delle `find` domina: $O(m\log n)$. Complessivamente $O(n+m\log n)=O(m\log n)$, sfruttando $m\geq n-1$ (il grafo deve essere connesso perché esista uno spanning tree).

> [!info]- Spiegazione
> **Il tranello è pensare che "ordinati" elimini l'intera complessità**, non solo il termine di ordinamento: il costo delle `find` resta $\Theta(\log n)$ ciascuna, e con $O(m)$ find questo termine non scompare — anzi diventa quello dominante.
>
> **Contrasto con la voce successiva** ([[#9. Kruskal con QuickFind + union by size, archi già ordinati: O(m + n log n)?|voce 9]], stessa ipotesi ma con QuickFind): lì il bound diventa $O(m+n\log n)$ — le `find` costano $O(1)$ (non $O(\log n)$) perché QuickFind ha sempre alberi di altezza $1$, e il costo logaritmico si sposta invece sulle `union`. Qui in QuickUnion è l'opposto: `union` $O(1)$, `find` $O(\log n)$. È lo stesso scambio di ruoli fra le due strutture discusso in [[#1. QuickFind + union by size: altezza Θ(log n) e find logaritmica?|voce 1]] e [[#2. QuickUnion + union by size: altezza 1 e find/union entrambe logaritmiche?|voce 2]].
>
> Il passaggio $m\geq n-1\Rightarrow O(n+m\log n)=O(m\log n)$ va giustificato esplicitamente: senza la connessione del grafo (necessaria perché esista uno spanning tree) il termine $O(n)$ non sarebbe automaticamente assorbito.
>
> **Dove si perdono punti:** dimenticare il fattore $O(\log n)$ per `find` in QuickUnion e concludere erroneamente $O(m)$; oppure non giustificare l'assorbimento di $O(n)$ dentro $O(m\log n)$.
### 9. Kruskal con QuickFind + union by size, archi già ordinati: O(m + n log n)?
*18/02/2025 · Es. 1, affermazione 5* — variante gemella della [[#8. Kruskal con QuickUnion + union by size, archi già ordinati: O(m log n)?|voce 8]] (16/07/2024), che chiede la stessa cosa con **QuickUnion** al posto di QuickFind e bound $O(m\log n)$ invece di $O(m+n\log n)$: il confronto fra le due è istruttivo.

> Si assuma di implementare l'algoritmo di Kruskal usando una struttura dati QuickFind con euristica union by size. Si assuma inoltre di avere già gli archi del grafo ordinati in ordine non decrescente rispetto al loro peso. Allora l'esecuzione dell'algoritmo di Kruskal ha complessità temporale $O(m+n\log n)$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con gli archi già ordinati, Kruskal non paga il costo di ordinamento $O(m\log m)$: restano le $O(m)$ find (costo $O(1)$ ciascuna in QuickFind, quindi $O(m)$ in totale) e le $n-1$ union, il cui costo complessivo con union by size è $O(n\log n)$ (cfr. [[#3. QuickFind + union by size: bound O(m + n log n) sull'intera sequenza|voce 3]]). Sommando si ottiene $O(m+n\log n)$: il bound generale della QuickFind con union by size, applicato senza il termine di ordinamento perché già assente.

> [!info]- Spiegazione
> **Il confronto con la voce 8 (variante QuickUnion).** Stesso schema di domanda (archi pre-ordinati, quindi si azzera il costo $O(m\log m)$), risposta diversa perché cambia dove si paga il costo residuo: qui con **QuickFind** il costo per elemento (find) è $O(1)$ e il fattore logaritmico sta tutto nelle union, dando $O(m+n\log n)$; con **QuickUnion + union by size** ([[#8. Kruskal con QuickUnion + union by size, archi già ordinati: O(m log n)?|voce 8]]) è l'opposto — la union è $O(1)$, ma ogni find costa $O(\log n)$ per l'altezza dell'albero, dando $O(n+m\log n)=O(m\log n)$. Le due strutture "spostano" il fattore logaritmico su operazioni diverse: cfr. [[02 - Union-Find#Applicazione: algoritmo di Kruskal|entrambi gli enunciati commentati in teoria]].
>
> **Perché non collassa a $O(m)$.** Anche azzerando l'ordinamento, il termine $n\log n$ delle union resta e non è dominato da $m$ in generale: su un grafo sparso con $m=\Theta(n)$, $n\log n$ è comparabile a $m$ ma con un fattore $\log n$ in più — va tenuto esplicito nel bound, non semplificato via.
>
> **Dove si perdono punti:** applicare per riflesso il bound $O(m\log n)$ della voce 8 (QuickUnion) a questa domanda su QuickFind, invece di ricalcolare da capo dove sta il fattore logaritmico.
### 10. Grafo completo: Kruskal con QuickFind, con o senza union by size
*18/07/2025 · Es. 1, affermazione 5* — unica delle cinque affermazioni di quell'appello di interesse Union-Find; le altre quattro (cycle/cut property) vivono in [[01 - Vero-Falso MST]].

> Se $G$ è completo allora l'algoritmo di Kruskal ha la stessa complessità asintotica sia se usa per la struttura Union-Find la QuickFind con o senza euristica union by size.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Su un grafo completo $m=\Theta(n^2)$, quindi l'ordinamento degli archi costa $\Theta(n^2\log n)$ in entrambi i casi. La parte Union-Find costa $O(n^2)$ sia con QuickFind pura (union $O(n)$ nel caso peggiore, $n-1$ union) sia con QuickFind + union by size ($O(n\log n)$ ammortizzato per l'argomento del raddoppio): in entrambi i casi $T(n)=\Theta(n^2\log n)$, perché $O(n^2)=o(n^2\log n)$.
>
> $$T_{\text{senza}}(n) = O(n^2 \log n) + O(n^2) = \Theta(n^2 \log n) \qquad T_{\text{con}}(n) = O(n^2 \log n) + O(n^2) = \Theta(n^2 \log n)$$

> [!info]- Spiegazione
> Attenzione a **quale** struttura: la traccia specifica QuickFind, non QuickUnion — le due hanno profili di costo opposti per `find`/`union` (cfr. [[02 - Union-Find]] e le voci [[#1. QuickFind + union by size: altezza Θ(log n) e find logaritmica?|1]]-[[#2. QuickUnion + union by size: altezza 1 e find/union entrambe logaritmiche?|2]]). Su grafo completo $m=|E|=\binom{n}{2}=\Theta(n^2)$, quindi l'ordinamento costa $O(m\log m)=O(n^2\log n)$ indipendentemente dall'euristica.
>
> **QuickFind senza union by size:** `find` $O(1)$, `union` $O(n)$ caso peggiore; $n-1$ union $\Rightarrow O(n^2)$, più $O(m)=O(n^2)$ di `find`: totale $O(n^2)$.
>
> **QuickFind con union by size:** per il raddoppio della dimensione (cfr. [[#4. QuickFind + union by size: k cambi di padre implicano insieme grande almeno 2^k?|voce 4]]) ogni elemento cambia etichetta $O(\log n)$ volte in tutto, quindi $O(n\log n)$ ammortizzato per le union, più $O(m)$ di `find`: totale $O(m+n\log n)=O(n^2)$.
>
> In entrambi i casi la parte Union-Find, $O(n^2)$, è dominata dall'ordinamento, $\Theta(n^2\log n)$: l'euristica cambia solo il costo della Union-Find (da $\Theta(n^2)$ caso peggiore a $O(n\log n)$ ammortizzato), ma resta $o(n^2\log n)$ e non cambia l'ordine di grandezza totale.
>
> **Dove si perdono punti:** applicare i bound di QuickUnion a una domanda su QuickFind (o viceversa) — struttura sbagliata, anche se la conclusione numerica finale può coincidere per caso.
### 11. Θ(n√n) archi, Kruskal con QuickFind + union by size: complessità lineare?
*09/09/2025 · Es. 1, affermazione 5* — unica delle cinque affermazioni di quell'appello di interesse Union-Find; le altre quattro vivono in [[01 - Vero-Falso MST]]. Variante gemella su **Prim con heap di Fibonacci**, stesso $m=\Theta(n\sqrt n)$, chiesta il 23/09/2025 in [[01 - Vero-Falso MST]] (Es. 1, affermazione 5), verdetto opposto (**Vera**): è la coppia più insidiosa dell'intero programma su MST/Union-Find.

> Se $G$ ha $\Theta(n\sqrt{n})$ archi, allora l'algoritmo di Kruskal che implementa la Union-Find con la QuickFind con euristica union by size ha complessità lineare, ovvero $\Theta(n\sqrt{n})$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Qualunque sia l'implementazione della Union-Find, Kruskal deve prima **ordinare** gli $m$ archi: $\Theta(m\log m)$, indipendente dall'euristica scelta dopo. Con $m=\Theta(n\sqrt n)$ (quindi $\log m=\Theta(\log n)$): l'ordinamento costa $\Theta(n\sqrt n\log n)$, mentre la Union-Find con QuickFind + union by size costa $O(m+n\log n)=O(n\sqrt n)$ (il termine $n\sqrt n$ domina $n\log n$). Il totale è dominato dall'ordinamento:
> $$T(n)=\Theta(n\sqrt n\log n)+O(n\sqrt n)=\Theta(n\sqrt n\log n)\neq\Theta(n\sqrt n)$$

> [!info]- Spiegazione
> È l'affermazione più insidiosa della cartella perché invita a un calcolo sulla Union-Find — dove un margine reale esiste, QuickFind con union by size batte la versione pura — distraendo dal vero collo di bottiglia. I due contributi vanno separati (cfr. [[02 - Union-Find#Applicazione: algoritmo di Kruskal|Applicazione: algoritmo di Kruskal]]): l'**ordinamento**, $\Theta(m\log m)$, è un preprocessing indipendente dalla Union-Find scelta dopo; le operazioni Union-Find ($n$ `makeSet`, $2m$ `find`, $n-1$ `union`) costano con QuickFind $O(1)$ per `find` e $O(n\log n)$ ammortizzato per le `union` (union by size: ogni elemento cambia rappresentante al più $O(\log n)$ volte, cfr. [[#4. QuickFind + union by size: k cambi di padre implicano insieme grande almeno 2^k?|voce 4]]).
>
> **Il contrasto con Prim+Fibonacci.** Stessa densità $m$, risposta opposta: Prim con heap di Fibonacci costa $O(m+n\log n)$, **senza ordinamento** — `decreaseKey` è $O(1)$ ammortizzato, e con $m\gg n\log n$ il totale collassa a $\Theta(m)$, lineare per davvero. Kruskal non ha un analogo: qualunque Union-Find si scelga, resta l'ordinamento a monte, ed è quel passo — non le operazioni Union-Find — a fissare il pavimento $\Omega(m\log m)$.
>
> **Dove si perdono punti:** credere che l'euristica sulla Union-Find elimini il fattore $\log n$ di Kruskal; oppure applicare per analogia il verdetto (Vero) dell'affermazione gemella su Prim+Fibonacci senza ricalcolare da capo.
## Costruzioni: sequenze che forzano altezza Θ(log n)
L'unica domanda aperta della cartella, riproposta identica parola per parola nei due appelli dedicati: costruire concretamente il caso peggiore ammesso dal lemma $s\geq 2^h$.
### 12. Costruzione di un albero QuickUnion di altezza Θ(log n)
*16/07/2024 · Es. 1, punto 2 · e 18/02/2025 · Es. 1, punto 2* — enunciato identico, parola per parola, nei due appelli. Lemma di riferimento in [[02 - Union-Find#Euristica union by size (QuickUnion)|Euristica union by size (QuickUnion)]].

> Si consideri la struttura dati QuickUnion con euristica union by size. Si mostri una sequenza di operazioni di $n$ makeSet e $n-1$ union in cui l'albero ottenuto abbia altezza $\Theta(\log n)$. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Sia $n=2^k$. Si eseguano gli $n$ `makeSet` e poi si uniscano gli alberi **a torneo per round**: al round $i$-esimo si accoppiano a due a due gli $n/2^{i-1}$ alberi rimasti dal round precedente — tutti di size $2^{i-1}$ e altezza $i-1$ — mediante `union`, ottenendo $n/2^i$ alberi di size $2^i$. Per l'euristica, unendo due alberi di **size (e quindi altezza) uguale** l'altezza del risultato cresce sempre di esattamente $1$. Dopo $k=\log_2 n$ round (in totale $n/2+n/4+\dots+1=n-1$ union) resta un unico albero di size $n$ e altezza esattamente $k=\Theta(\log n)$.

> [!info]- Spiegazione
> **L'invariante da rendere esplicito**: «unendo due alberi di size uguale, la size del risultato raddoppia e l'altezza cresce di $1$». È il caso $h_1=h_2$, $s_1=s_2$ della dimostrazione del lemma $s\geq 2^h$: dato $s_1\geq s_2$, è sempre l'albero $2$ (size minore o uguale) ad essere attaccato come figlio della radice dell'albero $1$ — l'attaccamento segue la **size**, non l'altezza. Se $h_2<h_1$ l'altezza complessiva resta $h_1$ e la size aumenta "gratis"; se invece $h_2\geq h_1$ l'altezza è costretta a salire a $h_2+1$. Il torneo per round costruisce sistematicamente il pareggio $h_1=h_2$ a ogni fusione, il caso peggiore ammesso dal lemma.
>
> **Perché serve la size uguale ad ogni round, non una coppia qualunque.** A parità di sole size, due alberi possono avere altezze diverse: un albero "a stella" di size $4$ ottenuto assorbendo tre singoletti in sequenza ha altezza $1$, non $2$. Nella costruzione a torneo, però, l'invariante è più forte — ogni round produce alberi di size *e* altezza uguali fra loro fin dal primo round (tutti singoletti, size $1$ e altezza $0$), quindi la parità di size garantisce davvero anche la parità di altezza e la crescita di $1$ prevista dal lemma; è un invariante che si autosostiene, non serve bilanciare manualmente ad ogni passo.
>
> **Perché è la costruzione estremale.** Il lemma $s\geq 2^h$ garantisce $h\leq\log_2 s\leq\log_2 n$ per *qualunque* sequenza con questa euristica — questa costruzione mostra che il bound è **stretto**, cioè che esiste una sequenza per cui $h=\Theta(\log n)$ è effettivamente raggiunta, non solo un limite superiore mai toccato.
>
> **Verifica del conteggio delle union**: la somma geometrica $n/2+n/4+\dots+2+1=n-1$ deve tornare esatta, altrimenti la sequenza non rispetta il vincolo «$n-1$ union» della traccia — un dettaglio spesso omesso ma verificabile in una riga.
>
> **Dove si perdono punti:** costruire una sequenza che fa crescere la size senza far crescere l'altezza (es. attaccare sempre un singoletto a un albero grande — quello resta di altezza costante); dimenticare di fissare $n=2^k$, che rende $\log_2 n$ un intero esatto; o dimenticare di verificare che il numero totale di union sia esattamente $n-1$.
