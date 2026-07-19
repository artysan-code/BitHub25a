---
tags:
  - algoritmi
  - flussi
  - esercizi
---
# Vero/Falso — Flussi di Rete
*Esercizio 1 · Flussi di Rete · 23 domande da 4 appelli (09/09/2024, 26/06/2025, 02/02/2026, 30/06/2026).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 09/09/2024, 26/06/2025, 02/02/2026, 30/06/2026.*
## Come leggere questo file
Flussi occupa uno dei due slot Es. 1/Es. 2 in 5 compiti su 6 (cfr. [[Formulario Flussi]]), e quando cade in Es. 1 il format è sempre lo stesso: cinque affermazioni vero/falso indipendenti da 11 punti totali più un punto 2 aperto (max 5 righe). A differenza di MST, dove tipicamente è vera una sola delle cinque, qui il numero di affermazioni vere varia appello per appello (tre il 09/09/2024, due negli altri tre) — non c'è scorciatoia per eliminazione, vanno motivate tutte e cinque indipendentemente.

Sette affermazioni su ventiquattro — quasi un terzo del corpus — vertono sulla stessa area concettuale: il rapporto fra flusso netto attraverso un taglio, capacità del taglio e valore del flusso. È la trappola preferita del prof, perché confonde due proprietà quasi omonime: il lemma del valore (uguaglianza col flusso netto, sempre) e la dualità debole (disuguaglianza con la capacità, stretta salvo il caso ottimo). Il secondo asse più battuto è la complessità di Ford-Fulkerson su istanze vincolate, con lo schema fisso «vincolo sulle capacità → bound su $\operatorname{val}(f^*)$ → moltiplica per $O(m)$» — e con la coppia di affermazioni più insidiosa del corpus: stesso testo, una clausola in più («non più grandi di $n^2$»), verdetto che si ribalta da Falso a Vero.

Per prendere punti pieni in questo slot: ogni affermazione richiede verdetto + motivazione in una riga + controesempio esplicito con numeri veri (mai un controesempio "in astratto"), oppure la citazione diretta del teorema quando l'affermazione nega un'uguaglianza dimostrata (nessun controesempio è costruibile contro un teorema vero). Per il punto 2 di complessità, la traccia chiede spesso il bound «quanto più stretto possibile»: fermarsi al bound generico $\operatorname{val}(f^*)\leq nC$ è corretto ma non basta se esiste un taglio più stretto da sfruttare.
## Flusso netto attraverso un taglio: lemma del valore contro dualità debole
Le sei voci di questo gruppo (sette affermazioni originali, una coppia fusa) testano ogni possibile modo di scambiare l'uguaglianza *sempre vera* del lemma del valore con la disuguaglianza *solo all'ottimo* della dualità debole — in entrambe le direzioni e con quantificatori diversi.
### Il flusso netto attraverso un taglio è sempre ≥ della sua capacità?
*citazione: 09/09/2024 · Es. 1, aff. 1*

> Dato un taglio $(A, B)$ e un flusso $f$, allora il flusso netto che passa per $(A, B)$ è sempre maggiore o uguale alla capacità di $(A, B)$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Per la dualità debole, il flusso netto che attraversa un taglio (che per il lemma del valore coincide sempre con $\operatorname{val}(f)$) è sempre **minore o uguale** alla capacità, mai maggiore: $\operatorname{val}(f)\leq\operatorname{cap}(A,B)$. L'affermazione inverte il verso.
>
> **Controesempio.** Rete a due nodi $s,t$ con un solo arco $c(s,t)=5$. Flusso $f(s,t)=2$ (valido), $\operatorname{val}(f)=2$. Unico taglio $(\{s\},\{t\})$, $\operatorname{cap}=5$. Il flusso netto è $2$, e $2\geq 5$ è falso.

> [!info]- Spiegazione
> La formulazione fonde due proprietà quasi omonime — il lemma del valore (uguaglianza col flusso, sempre vera, sotto) e la dualità debole (disuguaglianza con la capacità) — e ne inverte il verso: scrive $\geq$ dove la teoria dà $\leq$. L'unico caso in cui $\operatorname{val}(f)=\operatorname{cap}(A,B)$ si raggiunge è quando $f$ è massimo e $(A,B)$ è il taglio minimo: anche lì è un'**uguaglianza**, mai una disuguaglianza a favore del flusso.
>
> **Dove si perdono punti:** rispondere "Vera" confondendo questa affermazione con quella immediatamente sotto (che *è* vera) perché entrambe parlano di "flusso netto attraverso un taglio", senza controllare il verso della disuguaglianza.
### Il flusso netto attraverso un taglio è sempre uguale a val(f)?
*citazione: 09/09/2024 · Es. 1, aff. 5* — cfr. l'affermazione precedente, stessa area concettuale, verdetto opposto.

> per ogni taglio $(A, B)$ e per ogni flusso $f$, il flusso netto che attraversa $(A,B)$ è sempre uguale al valore di $f$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È esattamente l'enunciato del [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Lemma del valore del flusso|lemma del valore del flusso]]: per ogni flusso $f$ e ogni taglio st $(A,B)$,
> $$\operatorname{val}(f) = \sum_{e \text{ esce da } A} f(e) - \sum_{e \text{ entra in } A} f(e)$$
> L'uguaglianza vale per **qualsiasi** taglio e **qualsiasi** flusso, indipendentemente dal fatto che $f$ sia massimo o $(A,B)$ minimo.

> [!info]- Spiegazione
> **Perché vale sempre.** Si estende la somma che definisce $\operatorname{val}(f)$ a tutti i nodi di $A$: per conservazione ogni nodo $v\neq s$ contribuisce $0$, gli archi interni ad $A$ si cancellano, restano solo gli archi che attraversano il taglio. Non serve alcuna ipotesi di ottimalità.
>
> **Il contrasto con l'affermazione precedente** è il punto su cui si gioca l'intero blocco: qui si parla di **uguaglianza col valore del flusso** (lemma, sempre vero), là di **disuguaglianza con la capacità** (dualità debole, $\leq$ non $\geq$). Due proprietà diverse che condividono le stesse parole "flusso netto attraverso un taglio".
>
> **Dove si perdono punti:** confondere questo enunciato (lemma, uguaglianza sempre vera) con la dualità debole o col teorema Max-Flow Min-Cut, che riguardano $\operatorname{cap}(A,B)$, non $\operatorname{val}(f)$ da sola.
### v(f) è sempre uguale alla capacità di un taglio dato?
*citazione: 26/06/2025 · Es. 1, aff. 1*

> dato un flusso $f$ di $G$ e un st-taglio $(A, B)$, il valore del flusso $v(f)$ è sempre uguale alla capacità del taglio $\operatorname{cap}(A, B)$

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Vale solo la [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Dualità debole|dualità debole]], $v(f)\leq\operatorname{cap}(A,B)$: l'uguaglianza è garantita esclusivamente quando $f$ è massimo e $(A,B)$ è il taglio minimo, non per un flusso e un taglio scelti a caso.
>
> **Controesempio.** Rete $s,a,t$ con archi $(s,a)$ e $(a,t)$, entrambi $c=10$. Flusso $f(s,a)=f(a,t)=3$, $v(f)=3$. Taglio $(\{s\},\{a,t\})$: $\operatorname{cap}=c(s,a)=10\neq 3$.

> [!info]- Spiegazione
> Confonde il lemma del valore (flusso netto sempre $=v(f)$, per **ogni** taglio) con la dualità debole (la **capacità** è solo un limite superiore, uguale a $v(f)$ solo al taglio minimo con $f$ massimo). Nel controesempio, il taglio scelto non è nemmeno quello minimo, ma con $f$ non massimo nessun taglio arbitrario è tenuto a eguagliare $v(f)$ — nemmeno quello che a flusso ottimo diventerà il minimo.
>
> **Dove si perdono punti:** confondere «flusso netto attraverso il taglio» (sempre $=v(f)$) con «capacità del taglio» (solo $\geq v(f)$, uguale solo all'ottimo).
### Esiste sempre un taglio di capacità uguale a v(f)?
*citazione: 02/02/2026 · Es. 1, aff. 1 · e 30/06/2026 · Es. 1, aff. 3* — stesso claim, testo leggermente diverso fra i due appelli, controesempi diversi (rete a due archi contro rete a un solo arco).

> **02/02/2026:** Dato un flusso $f$ di $G$, c'è sempre un $s$-$t$-taglio $(A, B)$ la cui capacità è uguale a $v(f)$.

> **30/06/2026:** Per ogni flusso $f$, esiste sempre un taglio $(A, B)$ la cui capacità è uguale al valore di $f$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa** (in entrambe le formulazioni). Vale solo il verso debole, $\operatorname{cap}(A,B)\geq v(f)$ per ogni taglio; non è garantita l'esistenza di un taglio con uguaglianza esatta, a meno che $f$ non sia già massimo — nel qual caso il taglio minimo, dai nodi raggiungibili da $s$ in $G_f$, ha capacità esattamente $v(f)$.
>
> **Controesempio 02/02/2026.** Rete $s\to v\to t$, $c(s,v)=2$, $c(v,t)=5$ (max-flow$=2$). Sia $f$ non massimo, $f(s,v)=f(v,t)=1$, $v(f)=1$. I soli due tagli hanno capacità $2$ e $5$: nessuno vale $1$.
>
> **Controesempio 30/06/2026.** Rete a un solo arco $s\to t$, $c(s,t)=5$, $f(s,t)=2$ non massimo, $v(f)=2$. Unico taglio $(\{s\},\{t\})$, $\operatorname{cap}=5\neq 2$: più economico del precedente, elimina a monte la scelta del taglio.

> [!info]- Spiegazione
> Il ragionamento seducente è pensare che ogni flusso "viva dentro" un taglio la cui capacità ne certifichi il valore — ma è un evento speciale (flusso ottimo), non la regola. Se in uno dei due controesempi $f$ fosse il flusso **massimo**, il primo taglio avrebbe capacità esattamente $v(f)$: è l'eccezione prevista dal teorema Max-Flow Min-Cut, non la norma.
>
> **Dove si perdono punti:** dimenticare la clausola «solo se $f$ è massimo» e rispondere Vera pensando al caso limite in cui la si applica correttamente; oppure pensare alla dualità debole come se fosse un'uguaglianza universale, o costruire un controesempio con una rete inutilmente complessa quando quella a un solo arco (30/06/2026) basta ed è immediatamente verificabile.
### Esiste sempre un taglio di capacità strettamente maggiore di v(f)?
*citazione: 30/06/2026 · Es. 1, aff. 5* — variante "in negativo" della voce precedente: là si falsificava l'uguaglianza esatta con $f$ non massimo, qui la disuguaglianza stretta con $f$ massimo.

> Per ogni flusso $f$ esiste sempre almeno un taglio $(A, B)$ tale che la capacità di $(A, B)$ è strettamente più grande del valore di $f$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Controesempio: rete a un solo arco $s\to t$, $c(s,t)=7$, con $f$ **già massimo**: $f(s,t)=7$, $v(f)=7$. L'unico taglio $(\{s\},\{t\})$ ha $\operatorname{cap}=7=v(f)$: non esiste alcun altro taglio, quindi nessuno ha capacità strettamente maggiore.

> [!info]- Spiegazione
> Il caso degenere che falsifica l'affermazione è quello in cui *tutti* i tagli st della rete hanno la stessa capacità — qui ce n'è uno solo. Quando $f$ è massimo, il taglio minimo realizza l'uguaglianza esatta con $v(f)$: non può quindi esisterne uno "maggiore".
>
> **Dove si perdono punti:** costruire un controesempio con una rete che ha più tagli disponibili senza verificare che *tutti* abbiano capacità $\leq v(f)$ — la rete a un solo arco è la scelta più sicura perché elimina a monte la scelta del taglio.
### Esistono grafi con min-cut strettamente inferiore al max-flow?
*citazione: 09/09/2024 · Es. 1, aff. 3*

> Ci sono dei grafi per cui la capacità del taglio di capacità minima è strettamente inferiore al massimo flusso.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Per il [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Teorema Max-Flow Min-Cut|teorema Max-Flow Min-Cut]], $\max_f \operatorname{val}(f) = \min_{(A,B)} \operatorname{cap}(A,B)$ **sempre**: è un'uguaglianza, non una disuguaglianza. Non esiste alcun grafo in cui il taglio minimo abbia capacità strettamente inferiore al massimo flusso.

> [!info]- Spiegazione
> Rispetto alle voci precedenti (che confondono uguaglianza e disuguaglianza per un taglio *arbitrario*), qui l'errore è opposto: si nega l'uguaglianza del teorema *globale* (max sul flusso, min sul taglio) sperando in una disuguaglianza stretta che non esiste mai. La dualità debole esclude già il verso $>$; il teorema chiude l'altro verso costruendo esplicitamente un taglio di capacità $=\operatorname{val}(f^*)$. Nessun controesempio è possibile per costruzione: è materiale da citazione del teorema, non da ricerca di un caso patologico.
>
> **Dove si perdono punti:** rispondere "Vera" pensando a un flusso $f$ **non ottimo**, per cui $\operatorname{val}(f)<\operatorname{cap}(A,B)$ vale per un taglio qualunque — la domanda specifica "il massimo flusso" contro "il taglio di capacità minima", non un flusso e un taglio arbitrari.
## Caratterizzazione del flusso massimo: se, solo se, se e solo se
Il [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Teorema Max-Flow Min-Cut|teorema dei cammini aumentanti]] è un «se e solo se»: $f$ massimo $\iff$ nessun cammino aumentante in $G_f$. Tre appelli chiedono direzioni diverse di questa equivalenza, con quantificatori diversi — la differenza logica, non il calcolo, è il punto.

| Appello | Formulazione | Direzione logica | Dimostrazione | Verdetto |
|---|---|---|---|---|
| 26/06/2025, aff. 3 | «se non c'è cammino aumentante allora $f$ è massimo» | $[\neg\text{cammino}\Rightarrow\text{max}]$, la direzione **profonda** | costruzione esplicita del taglio $(A,B)$ | Vera |
| 02/02/2026, aff. 4 | «se c'è un cammino allora $f$ non è massimo» | contronominale di $[\text{max}\Rightarrow\neg\text{cammino}]$ | AUGMENT, nessun taglio | Vera |
| 30/06/2026, aff. 1 | «$f$ massimo **solo se** non c'è cammino» | $[\text{max}\Rightarrow\neg\text{cammino}]$ diretta | AUGMENT, nessun taglio | Vera |

Le ultime due righe sono **la stessa implicazione logica** ($f$ massimo $\Rightarrow$ nessun cammino aumentante), espressa in due forme equivalenti — contronominale e "solo se" diretto — con la stessa dimostrazione. La prima riga è invece l'implicazione opposta, quella che richiede la costruzione del taglio: non basta ricordare "vero" e riciclare la dimostrazione sbagliata se la formulazione cambia appello.

**Corrispettivo in Es. 2:** la direzione profonda («nessun cammino $\Rightarrow$ massimo») è chiesta per esteso, come dimostrazione da 5 righe anziché come V/F, in [[02 - Teoria Flussi e Min-Cut#Dimostrazione: assenza di cammino aumentante implica flusso massimo|Teoria Flussi · Dimostrazione: assenza di cammino aumentante implica flusso massimo]] — stessa catena deduttiva (taglio dei raggiungibili da $s$, saturazione, lemma del valore, dualità debole).
### Nessun cammino aumentante implica flusso massimo
*citazione: 26/06/2025 · Es. 1, aff. 3*

> Dato un flusso $f$, se nella rete residua $G_f$ non c'è alcun cammino da $s$ a $t$, allora $f$ è un flusso massimo per $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È la direzione «profonda» del teorema. Sia $A$ l'insieme dei nodi raggiungibili da $s$ in $G_f$: per ipotesi $t\notin A$, quindi $(A,B)$ con $B=V\setminus A$ è un taglio st valido. Ogni arco $A\to B$ è saturo — altrimenti l'estremo in $B$ sarebbe raggiungibile da $s$, assurdo — e ogni arco $B\to A$ ha flusso nullo — altrimenti l'arco inverso residuo lo renderebbe raggiungibile, assurdo. Per il lemma del valore, $v(f)=\operatorname{cap}(A,B)$, e per il corollario del certificato di ottimalità $f$ è massimo.

> [!info]- Spiegazione
> A differenza della coppia sotto, questa direzione richiede una costruzione esplicita (il taglio dai nodi raggiungibili), non solo la contronominale immediata. Dimostrazione completa in [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Teorema Max-Flow Min-Cut|teoria · Teorema Max-Flow Min-Cut]].
>
> **Dove si perdono punti:** rispondere solo «vera, per il teorema» senza scrivere la costruzione del taglio — è la costruzione, non l'enunciato, a valere i punti su una domanda che chiede la giustificazione.
### Un cammino aumentante in Gf implica che f non è massimo
*citazione: 02/02/2026 · Es. 1, aff. 4*

> Dato un flusso $f$, se nella rete residua $G_f$ c'è un cammino da $s$ a $t$, allora $f$ non è massimo.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Se esistesse un cammino aumentante $P$ in $G_f$, $\operatorname{AUGMENT}(f,c,P)$ produrrebbe $f'$ con $\operatorname{val}(f')=\operatorname{val}(f)+\operatorname{bottleneck}(G_f,P)$. Il bottleneck è sempre $>0$ (un arco esiste in $G_f$ solo con capacità residua positiva), quindi $\operatorname{val}(f')>\operatorname{val}(f)$: $f$ ammetterebbe un miglioramento, dunque non è massimo.

> [!info]- Spiegazione
> È la direzione "facile" del teorema — non serve un controesempio perché l'affermazione è vera; il "lavoro" è nella direzione logica (contronominale di "$f$ massimo $\Rightarrow$ nessun cammino"), non in una costruzione ad hoc. È la stessa implicazione, con parole diverse, dell'affermazione «solo se» chiesta il 30/06/2026, appena sotto: riconoscerle come la stessa proprietà evita di dover ridimostrare tutto da capo.
>
> **Dove si perdono punti:** nessun errore strutturale ricorrente su questa direzione (la più intuitiva); il rischio compare quando la stessa equivalenza è chiesta nella forma «solo se» e si applica per riflesso la costruzione del taglio, che qui non serve.
### "f massimo solo se non c'è cammino aumentante": la forma con quantificatore esplicito
*citazione: 30/06/2026 · Es. 1, aff. 1*

> Dato un flusso $f$, $f$ è massimo solo se nella rete residua $G_f$ non c'è alcuno cammino da $s$ a $t$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** «Solo se» significa che la proposizione dopo di esso è condizione **necessaria**: l'affermazione da verificare è $f\text{ massimo}\Rightarrow\text{nessun cammino in }G_f$, la stessa direzione dell'affermazione precedente. Si dimostra per contronominale: se in $G_f$ esistesse un cammino aumentante $P$ con $\delta=\operatorname{bottleneck}(G_f,P)>0$, $\operatorname{AUGMENT}(f,c,P)$ produrrebbe $f'$ con $\operatorname{val}(f')=\operatorname{val}(f)+\delta>\operatorname{val}(f)$, contraddicendo la massimalità di $f$.

> [!info]- Spiegazione
> Confondere «solo se» con «se» porterebbe a cercare la dimostrazione sbagliata (quella con la costruzione del taglio, riservata alla direzione opposta). Poiché il teorema è un «se e solo se», anche la direzione inversa è vera, ma non è quella isolata da questa traccia: il punto della domanda è verificare che si sappia *quale* metà della biimplicazione si sta usando.
>
> **Dove si perdono punti:** rispondere "Vera" richiamando genericamente "il teorema Max-Flow Min-Cut" senza indicare quale delle due implicazioni si sta usando, oppure tirare in ballo la costruzione del taglio, che qui non serve e non è quanto chiesto.
## Cammini aumentanti e bottleneck
Tre affermazioni, tre sfaccettature distinte del concetto di [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Cammino aumentante|bottleneck]] — spesso confuse fra loro, ma logicamente indipendenti.
### Capacità intere: ogni cammino aumentante alza il flusso di almeno un'unità
*citazione: 09/09/2024 · Es. 1, aff. 2*

> Se le capacità sono intere, allora ogni cammino aumentante trovato nella rete residua può essere usato per aumentare il flusso corrente di almeno una unità.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Per l'invariante di integralità, se tutte le $c(e)$ sono intere allora ogni $f(e)$ e ogni $c_f(e)$ restano interi per tutta l'esecuzione (induzione sul numero di aumenti). Un arco esiste in $G_f$ solo se $c_f(e)>0$, quindi ogni capacità residua sul cammino è un intero **strettamente positivo**, $\geq 1$. Il bottleneck, minimo di quantità intere $\geq 1$, è quindi anch'esso un intero $\geq 1$.

> [!info]- Spiegazione
> È questo invariante a rendere finito il numero di iterazioni di Ford-Fulkerson con capacità intere: ogni aumento cresce $\operatorname{val}(f)$ di un intero $\geq 1$, e $\operatorname{val}(f)$ è limitato da $nC$, quindi il processo termina.
>
> **Attenzione a non confondere** questa proprietà (vera) con la sua variante indebolita, chiesta il 02/02/2026: se si sostituisce «capacità intere» con «$c(e)\geq\beta$ per ogni arco **originale**», la conclusione «ogni aumento è $\geq\beta$» diventa falsa — le capacità **residue** possono scendere sotto $\beta$, cfr. la voce sotto.
>
> **Dove si perdono punti:** rispondere correttamente "Vera" ma limitandosi a un generico "capacità intere ⇒ flusso intero" senza citare l'invariante di integralità e il passaggio per induzione.
### Il bottleneck non è la capacità residua di un arco a scelta
*citazione: 26/06/2025 · Es. 1, aff. 4*

> Sia $f$ un flusso e sia $e$ un arco di un cammino $P$ da $s$ a $t$ nella rete residua $G_f$. Allora è sempre possibile usare il cammino aumentante $P$ per aumentare il flusso $f$ di $c_f(e)$, dove $c_f(e)$ è il peso di $e$ nella rete residua $G_f$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** L'incremento ammissibile è il **bottleneck**, $\operatorname{bottleneck}(G_f,P)=\min_{e'\in P} c_f(e')$: il minimo tra le capacità residue di **tutti** gli archi di $P$, non $c_f(e)$ di un singolo arco scelto arbitrariamente.
>
> **Controesempio.** Cammino $P: s\to u\to t$ con $c_f(s,u)=10$, $c_f(u,t)=2$. Preso $e=(s,u)$, $c_f(e)=10$: aumentare $f$ di $10$ lungo $P$ violerebbe la capacità residua di $(u,t)$. L'unico incremento ammissibile è $\min(10,2)=2$.

> [!info]- Spiegazione
> La procedura AUGMENT satura sempre l'arco di collo di bottiglia del cammino, un vincolo **globale** su $P$, non locale su un singolo arco. Se $e$ non è il minimo, usare $c_f(e)$ come incremento eccede la capacità residua di qualche altro $e'\in P$ con $c_f(e')<c_f(e)$.
>
> **Dove si perdono punti:** dimenticare che il bottleneck dipende dall'**intero** cammino, non dall'arco menzionato nella traccia — l'affermazione è costruita apposta per suggerire che «un arco qualsiasi di $P$» basti a definire l'incremento.
### c(e) ≥ β per ogni arco garantisce un incremento di almeno β?
*citazione: 02/02/2026 · Es. 1, aff. 3* — refuso «augmanting» (per *augmenting*) riportato verbatim dal testo del compito.

> Se per ogni arco $e$ $c(e) \geq \beta$, allora ogni augmanting step aumenta il flusso corrente di almeno $\beta$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Il bottleneck è il minimo delle **capacità residue** in $G_f$, non delle capacità originali $c(e)$ in $G$: un passo precedente può lasciare un arco con capacità residua arbitrariamente piccola pur avendo $c(e)\geq\beta$.
>
> **Controesempio.** $\beta=2$. Rete $s,v,w,t$ con $c(s,v)=3$, $c(v,w)=2$, $c(w,t)=3$, $c(v,t)=3$ (tutti $\geq\beta$). Primo step: $s\to v\to w\to t$, bottleneck $=\min(3,2,3)=2=\beta$; $c_f(s,v)$ scende a $1$. Secondo step: $s\to v\to t$ (arco diretto $v\to t$ ancora inutilizzato), bottleneck $=\min(1,3)=1<\beta$.

> [!info]- Spiegazione
> La trappola è seducente perché il **primo** passo rispetta davvero l'ipotesi: al primo step $G_f=G$, quindi il bottleneck è un minimo di capacità **originali**, tutte $\geq\beta$. È dal secondo passo che il ragionamento smette di valere: da lì si lavora su $G_f$, dove le capacità residue riflettono quanto già instradato, non più $c(e)$.
>
> **Dove si perdono punti:** verificare l'ipotesi solo sul primo augmenting step e generalizzare a tutta l'esecuzione; oppure confondere il bottleneck (minimo lungo l'intero cammino, in $G_f$) con la capacità originale di un singolo arco.
## Complessità di Ford-Fulkerson: polinomiale, pseudo-polinomiale, e sotto quali ipotesi
Otto voci, lo schema fisso del [[Formulario Flussi#Complessità — il cuore dei V/F|Formulario]]: dal vincolo sulle capacità si ricava un bound su $\operatorname{val}(f^*)$ (= numero massimo di iterazioni), si moltiplica per $O(m)$ (costo di una BFS/DFS per iterazione). Le prime due voci sono la coppia più insidiosa del corpus.

**Corrispettivo in Es. 2:** l'argomentazione discorsiva sulla stessa distinzione pseudo-polinomiale/polinomiale — 5 righe invece di V/F — è chiesta in [[02 - Teoria Flussi e Min-Cut#Perché Ford-Fulkerson è pseudo-polinomiale, non polinomiale|Teoria Flussi e Min-Cut · Perché Ford-Fulkerson è pseudo-polinomiale]].
### «Capacità intere» bastano per la polinomialità di Ford-Fulkerson?
*citazione: 26/06/2025 · Es. 1, aff. 2* — refuso «Ford-Furkerson» del prof, riportato verbatim. Cfr. la voce seguente: stesso testo, una clausola in più, verdetto opposto.

> L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** La prima metà è corretta: con scelta arbitraria del cammino, Ford-Fulkerson può richiedere un numero esponenziale di iterazioni. Ma «capacità intere» da sole **non bastano** per la seconda metà: serve che siano polinomiali in $n$, non semplicemente intere — un intero può essere esponenziale nel numero di bit che lo rappresentano.
>
> **Controesempio.** Rete patologica standard $s,v,w,t$ con $c(s,v)=c(s,w)=c(v,t)=c(w,t)=C$, $c(v,w)=c(w,v)=1$ (tutte intere). Alternando i cammini $s\to v\to w\to t$ e $s\to w\to v\to t$, ogni aumento ha bottleneck $1$: servono $2C$ iterazioni. Con $C=2^{30}$ — intero, ma non polinomiale in $n$ — il numero di passi è astronomico.

> [!info]- Spiegazione
> $O(mnC)$ dipende dal **valore numerico** di $C$, non dalla sua lunghezza in bit ($O(\log C)$). «Intero» non pone alcun limite su quanto grande $C$ possa essere rispetto a $n$; «polinomiale in $n$» sì — è la distinzione della voce seguente.
>
> **Dove si perdono punti:** leggere «capacità intere» e concludere «quindi polinomiale» senza controllare se il vincolo limita $C$ a un valore polinomiale in $n$; oppure "correggere" silenziosamente il refuso «Ford-Furkerson» senza segnalarlo nella trascrizione.
### ...con capacità intere ≤ n²: il verdetto si ribalta
*citazione: 02/02/2026 · Es. 1, aff. 2* — stesso testo della voce precedente con la sola clausola aggiuntiva «non più grandi di $n^2$»: un dettaglio che ribalta il verdetto da Falso a Vero. Refuso «Ford-Furkerson» ripetuto identico.

> L'algoritmo di Ford-Furkerson ha una complessità che in generale può essere esponenziale nella dimensione dell'istanza, ma è sempre polinomiale quando le capacità degli archi sono valori interi non più grandi di $n^2$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con scelta arbitraria del cammino il numero di iterazioni può ancora essere $\Theta(C)$ nel caso patologico — la prima parte resta corretta in generale. Ma se $c(e)\leq n^2$ per ogni arco, per il teorema di terminazione $\operatorname{val}(f^*)\leq nC\leq n\cdot n^2=n^3$; ogni aumento costa $O(m)$, quindi la complessità totale è $O(m\cdot n^3)=O(mn^3)$, polinomiale sia in $n$ sia in $m$.

> [!info]- Spiegazione
> La differenza con la voce precedente sta tutta nel far diventare $C$ **polinomiale in $n$** invece che potenzialmente esponenziale nel numero di bit — cfr. [[Formulario Flussi#Complessità — il cuore dei V/F|Formulario · tabella dei vincoli]]. Un solo dettaglio della clausola ribalta il verdetto: leggere con attenzione il vincolo esatto sulle capacità è l'unica difesa.
>
> **Dove si perdono punti:** rispondere "Falsa" per riflesso ricordando che "Ford-Fulkerson in generale non è polinomiale", senza notare che la traccia introduce il vincolo aggiuntivo $c(e)\leq n^2$, che è proprio ciò che ribalta il verdetto.
### Ford-Fulkerson con BFS (Edmonds-Karp): polinomiale nella dimensione dell'istanza?
*citazione: 09/09/2024 · Es. 1, aff. 4*

> L'algoritmo di Ford-Fulkerson, se si usa la visita BFS per trovare i cammini aumentanti, ha una complessità polinomiale nella dimensione dell'istanza.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Scegliere sempre il cammino con **meno archi** tramite BFS è esattamente [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Algoritmo di Edmonds-Karp (cammino più corto)|Edmonds-Karp]]. La distanza BFS da $s$ a $t$ in $G_f$ è monotona non decrescente lungo le iterazioni, il che limita il numero totale di aumenti a $O(mn)$; ogni aumento costa $O(m)$, quindi la complessità totale è $O(m^2n)$ — polinomiale in $n$ e $m$, **indipendente dal valore delle capacità** $C$.

> [!info]- Spiegazione
> A differenza delle due voci precedenti, qui la polinomialità non nasce da un vincolo sulle capacità ma dalla **struttura della strategia di ricerca del cammino**: la dimensione dell'istanza si misura in $n$, $m$ e nel numero di bit per le capacità, non nel valore numerico di $C$. Il caso patologico dell'arco centrale di capacità $C=2^{30}$ resta valido contro Ford-Fulkerson generico, ma qui la BFS lo elimina.
>
> **Dove si perdono punti:** rispondere "Falsa" ricordando che Ford-Fulkerson **in generale** è pseudo-polinomiale, senza notare che la domanda specifica la strategia BFS — che è appunto la condizione che lo rende polinomiale.
### Un nodo con archi entranti unitari basta per garantire la polinomialità?
*citazione: 30/06/2026 · Es. 1, aff. 2*

> Se esiste un nodo $v$ nella rete i cui archi entranti hanno tutti capacità $1$, allora l'algoritmo di Ford-Fulkerson è garantito avere complessità polinomiale.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Il bound $O(mnC)$ dipende dalla capacità massima $C$ su **tutti** gli archi della rete, non da una condizione locale su un singolo nodo.
>
> **Controesempio.** Nodi $s,a,b,v,t$. Archi $s\to a=C$, $s\to b=C$, $a\to b=1$, $b\to a=1$, $a\to t=C$, $b\to t=C$ (caso patologico esponenziale), più $s\to v=1$, $v\to t=1$. L'unico arco entrante in $v$ è $s\to v=1$: $v$ soddisfa l'ipotesi. Il flusso massimo vale $2C+1$; alternando i cammini su $\{a,b\}$ (bottleneck $1$ ad ogni passo) servono comunque $2C$ iterazioni, indipendentemente da $v$.

> [!info]- Spiegazione
> Il ragionamento seducente: "un nodo con archi entranti piccoli limita il flusso che lo attraversa, quindi limita l'intero algoritmo". Ma limita solo il flusso **locale** su quel nodo, non $\operatorname{val}(f^*)$ della rete né le capacità residue nel resto del grafo. Il bound polinomiale richiede un vincolo **globale** su tutte le capacità, mai una condizione locale su un singolo nodo.
>
> **Dove si perdono punti:** confondere una condizione locale (un nodo) con una condizione globale (tutti gli archi); oppure limitarsi a scrivere "non è garantito" senza costruire un controesempio esplicito che includa sia il nodo sia la parte patologica.
### Θ(n√n) archi, capacità al più 2: la complessità diventa lineare?
*citazione: 02/02/2026 · Es. 1, aff. 5*

> Se $G$ ha $\Theta(n\sqrt{n})$ archi, e le capacità degli archi sono tutte al più $2$, allora l'algoritmo di Ford-Fulkerson ha complessità lineare, ovvero $O(n\sqrt{n})$.

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Bound sul numero di aumenti: con $C\leq 2$, $\operatorname{val}(f^*)\leq nC=O(n)$. Costo per aumento: $O(m)=O(n\sqrt n)$ tramite BFS/DFS. Complessità totale:
> $$O(m\cdot \operatorname{val}(f^*))=O(n\sqrt n\cdot n)=O(n^2\sqrt n)\neq O(n\sqrt n)$$

> [!info]- Spiegazione
> L'errore è leggere «$\Theta(n\sqrt n)$ archi» e concludere direttamente «quindi la complessità è $\Theta(n\sqrt n)$», confondendo il costo di **una singola** BFS/DFS (che è sì $\Theta(n\sqrt n)$) con il costo **totale**, da moltiplicare per il numero di iterazioni. Il vincolo $c(e)\leq 2$ limita solo $\operatorname{val}(f^*)$ a $O(n)$ iterazioni, non a $O(1)$: lo stesso identico errore di composizione ricorre nella batteria V/F su MST, con Kruskal e QuickFind al posto di Ford-Fulkerson — meccanismo diverso, stessa confusione fra costo di un passo e costo totale.
>
> **Dove si perdono punti:** non moltiplicare il costo per iterazione per il numero di iterazioni; scambiare $\Theta(m)$ (il costo di una singola visita) per la complessità asintotica dell'intero algoritmo.
### Capacità unitarie: il numero di iterazioni è sempre polinomiale nel numero di nodi, indipendentemente dalla strategia?
*citazione: 09/09/2024 · Es. 1, punto 2* — cfr. la voce seguente, stessa premessa (capacità unitarie) ma domanda diversa: qui il numero di **iterazioni**, là la complessità **totale**.

> Si consideri la seguente affermazione: Se le capacità degli archi sono tutte uguali a 1, allora il numero di iterazioni dell'algoritmo di Ford-Fulkerson, ovvero, il numero di aumenti di flusso tramite cammini aumentanti, è sempre polinomiale nel numero di nodi del grafo, indipendentemente dalla strategia usata per trovare i cammini aumentanti. Dire se l'affermazione è vera o falsa motivando la risposta. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con capacità tutte unitarie ogni capacità residua vale $0$ o $1$, quindi il bottleneck di **qualsiasi** cammino aumentante è esattamente $1$: ogni iterazione aumenta $\operatorname{val}(f)$ di esattamente $1$. Il numero di iterazioni è quindi esattamente $\operatorname{val}(f^*)$, limitato dal grado uscente di $s$: $\operatorname{val}(f^*)\leq\deg^+(s)\leq n-1$ (grafo semplice). Il numero di iterazioni è dunque $O(n)$, polinomiale nel numero di nodi, per qualunque strategia di scelta del cammino.

> [!info]- Spiegazione
> Il bound corretto è sul grado **uscente di $s$**, non sul numero di archi $m$: su un grafo denso $m$ può essere $\Theta(n^2)$, ma questo non influenza $\operatorname{val}(f^*)$, limitato solo dalla capacità uscente da $s$. «Indipendentemente dalla strategia» è la clausola che rende l'affermazione forte ma comunque corretta: qualunque cammino aumentante, in qualunque ordine, satura sempre almeno un'unità.
>
> **Costo totale (extra).** $O(n)$ iterazioni $\times$ $O(m)$ per BFS/DFS dà $O(mn)$; in un grafo semplice $m=O(n^2)$, quindi $O(n^3)$ nel caso peggiore — coerente con la voce seguente, che chiede esplicitamente questo bound $O(n^3)$.
>
> **Dove si perdono punti:** limitare il bound sulle iterazioni al numero di archi $m$ invece che al grado uscente di $s$ — un'analisi che sembra più "generale" ma dà un bound più debole, e non risponde alla domanda (che chiede polinomialità nel numero di **nodi**, non di archi).
### Capacità tutte unitarie: Ford-Fulkerson ha complessità O(n³)?
*citazione: 30/06/2026 · Es. 1, aff. 4*

> Se tutti gli archi hanno capacità pari a $1$, allora l'algoritmo di Ford-Fulkerson ha complessità $O(n^3)$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** Con capacità unitarie ($C=1$), il numero di aumenti è al più $\operatorname{val}(f^*)\leq n-1=O(n)$ (bound sul grado uscente di $s$, coerente con la voce precedente). Ogni aumento costa $O(m)$ tramite BFS/DFS; in un grafo diretto semplice $m=O(n^2)$. Complessità totale:
> $$T(n)=O(m\cdot\operatorname{val}(f^*))=O(n^2\cdot n)=O(n^3)$$

> [!info]- Spiegazione
> $O(n^3)$ è il prodotto di **due** bound indipendenti: $O(n)$ iterazioni (dalle capacità) e $O(n^2)$ costo per iterazione (dalla dimensione del grafo, in un grafo semplice $m\leq n(n-1)$). Nessuno dei due bound da solo dà $n^3$: va dichiarata esplicitamente la sostituzione $m=O(n^2)$.
>
> **Dove si perdono punti:** fermarsi a $O(mn)$ senza sostituire esplicitamente $m=O(n^2)$, consegnando un risultato in una forma diversa da quella richiesta; dimenticare che il bound sul grado uscente di $s$ presuppone un grafo semplice (senza archi paralleli).
### Grado entrante limitato a 3 e capacità ≤ n²: quanto è stretto il bound, ed è garantito polinomiale?
*citazione: 26/06/2025 · Es. 1, punto 2*

> Si consideri una rete di flusso $G = (V, E, s, t, c)$ di $n$ nodi in cui ogni nodo ha grado entrante al più $3$ (mentre il grado uscente di un nodo può essere anche $\Theta(n)$) e la capacità di ogni arco $e \in E$ è un numero intero non più grande di $n^2$. Si derivi una delimitazione superiore (quanto più stretta possibile) alla complessità temporale dell'algoritmo di Ford-Fulkerson sulla rete $G$. Si può affermare che in questo caso l'algoritmo è garantito avere complessità polinomiale? *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Bound su $m$.** Sommando i gradi entranti su tutti i nodi si ottiene $m$: $m=\sum_v \deg^-(v)\leq 3n=O(n)$ (il grado uscente $\Theta(n)$ non impedisce il conteggio, ogni arco è contato una sola volta come entrante).
>
> **Bound su $\operatorname{val}(f^*)$, via il taglio intorno a $t$.** Per la dualità debole, $\operatorname{val}(f^*)\leq\operatorname{cap}(A,B)$ per **ogni** taglio; prendo $(A,B)=(V\setminus\{t\},\{t\})$: $\operatorname{cap}(A,B)=\sum_{e\text{ entra in }t} c(e)\leq \deg^-(t)\cdot n^2\leq 3n^2$. Dunque $\operatorname{val}(f^*)=O(n^2)$.
>
> **Complessità e conclusione.** $O(m\cdot \operatorname{val}(f^*))=O(n\cdot n^2)=O(n^3)$: **sì**, l'algoritmo è garantito polinomiale.

> [!info]- Spiegazione
> **Perché il taglio $(\{s\},V\setminus\{s\})$ non basta.** È la scelta istintiva, ma il grado **uscente** di $s$ è $\Theta(n)$: quel taglio darebbe solo $\operatorname{val}(f^*)\leq n\cdot n^2=n^3$, un fattore $n$ più debole, portando a $O(n^4)$ invece di $O(n^3)$. Il vincolo che stringe davvero è quello sul grado **entrante**, applicato al taglio intorno a $t$ — il vincolo «grado entrante $\leq 3$» vale per **ogni** nodo, $t$ incluso.
>
> **Perché è comunque un bound legittimo.** La dualità debole vale per ogni flusso e ogni taglio, quindi in particolare per $f^*$ e per $(V\setminus\{t\},\{t\})$: non serve conoscere $f^*$ in anticipo per applicare l'argomento.
>
> **Dove si perdono punti:** applicare solo il bound generico $\operatorname{val}(f^*)\leq nC$ e fermarsi a $O(n^4)$ — corretto ma non ottimale, dato che la traccia chiede esplicitamente il bound «quanto più stretto possibile»; oppure dimenticare che il vincolo sul grado entrante si applica anche a $t$, non solo ai nodi intermedi.
## Min-cut: estrazione e proprietà
Una sola voce, ma è la costruzione duale a quella standard di estrazione del min-cut da un flusso massimo: non i nodi raggiungibili **da** $s$, ma quelli che **raggiungono** $t$ in $G_f$. La costruzione standard (nodi raggiungibili da $s$) e la sua correttezza sono chieste per esteso in Es. 2 → [[02 - Teoria Flussi e Min-Cut#Estrazione del taglio minimo in tempo lineare da un flusso massimo|Teoria Flussi e Min-Cut · Estrazione del taglio minimo]] e [[02 - Teoria Flussi e Min-Cut#Correttezza dell'algoritmo di estrazione|Correttezza dell'algoritmo di estrazione]].
### Taglio minimo via nodi che raggiungono t
*citazione: 26/06/2025 · Es. 1, aff. 5*

> Sia $f$ un flusso tale che, nella rete residua $G_f$, $s$ e $t$ sono separati. Sia $B$ l'insieme di tutti e soli i nodi che possono raggiungere $t$. Allora $(V \setminus B, B)$ è un taglio minimo di $G$.

> [!quote] Soluzione — da scrivere sul compito
> **Vera.** È la costruzione duale di quella standard: invece di $A=$ nodi raggiungibili **da** $s$, si usa $B=$ nodi che **raggiungono** $t$ in $G_f$. Da $s,t$ separati segue $s\notin B$ e $t\in B$: $(V\setminus B,B)$ è un taglio st valido. Ogni arco entrante in $B$ dall'esterno è saturo — altrimenti la sua origine raggiungerebbe $t$ passando per quell'arco residuo, e starebbe già in $B$, assurdo — e ogni arco uscente da $B$ ha flusso nullo, per l'argomento simmetrico. Per il lemma del valore, $\operatorname{cap}(V\setminus B,B)=v(f)$, e per il corollario del certificato di ottimalità $(V\setminus B,B)$ è minimo.
>
> **Verifica numerica.** Nodi $s,a,b,t$; archi $(s,a),(a,t),(s,b),(b,t)$ con $c(s,a)=3$, $c(a,t)=1$, $c(s,b)=1$, $c(b,t)=5$. Flusso $f(s,a)=f(a,t)=1$, $f(s,b)=f(b,t)=1$ ($v(f)=2$): $(a,t)$ e $(s,b)$ saturi. Da $s$ si raggiunge solo $\{s,a\}$ in $G_f$: separati. I nodi che raggiungono $t$: $\{b,t\}$ (non $a$, non $s$). $B=\{b,t\}$, $V\setminus B=\{s,a\}$: $\operatorname{cap}(\{s,a\},\{b,t\})=c(s,b)+c(a,t)=1+1=2=v(f)$ — qui coincide con il taglio standard.

> [!info]- Spiegazione
> È la voce più insidiosa del gruppo perché non è falsa per costruzione poco familiare: il repertorio standard usa i nodi raggiungibili **da** $s$, e la tentazione è bollare come falsa qualunque costruzione diversa. Ma l'argomento di saturazione si ricostruisce **simmetricamente**, con la direzione di percorrenza invertita — cfr. la [[Formulario Flussi#Estrazione del min-cut da un flusso massimo|variante «nodi che raggiungono t»]] già annotata nel formulario. In generale le due costruzioni possono restituire tagli minimi diversi (il max-flow è unico nel valore, non necessariamente il min-cut).
>
> **Dove si perdono punti:** giudicare falsa l'affermazione solo perché non è la costruzione «da manuale» (raggiungibili da $s$), senza verificare che l'argomento di saturazione regge identico con i ruoli scambiati.
## Analisi di sensitività
Due punti aperti, entrambi su come una perturbazione delle capacità (un arco solo, o tutti uniformemente) si ripercuote su flusso massimo e taglio minimo già calcolati — imparentate ma logicamente distinte, da non confondere.
### Aumentare di 1 la capacità di un arco a scelta: fa sempre crescere il flusso massimo?
*citazione: 02/02/2026 · Es. 1, punto 2*

> Sia $G = (V, E, s, t, c)$ una rete di flusso di $n$ nodi e $m$ archi con capacità intere. Immaginate di aver già calcolato un flusso massimo $f$ per $G$. Ora vi danno la possibilità di aumentare di una unità la capacità di un arco a vostra scelta. Mostrate che non è sempre possibile aumentare il valore del flusso massimo. E fornite un algoritmo di complessità $O(n + m)$ che decide se è possibile farlo o meno. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Non sempre è possibile.** Aumentare $c(u,v)$ di $1$ fa crescere $\operatorname{val}(f^*)$ **se e solo se** quell'unità crea un nuovo cammino aumentante in $G_f$, cioè se esistono un cammino $s\leadsto u$, l'arco $(u,v)$, e un cammino $v\leadsto t$, tutti in $G_f$.
>
> **Algoritmo $O(n+m)$.** Costruita $G_f$ in $O(m)$: (1) BFS/DFS da $s$ in avanti su $G_f$, ottenendo $S=$ nodi raggiungibili da $s$; (2) BFS/DFS da $t$ percorrendo gli archi di $G_f$ **all'indietro**, ottenendo $T=$ nodi da cui si raggiunge $t$. L'aumento è utile $\iff$ esiste $(u,v)\in E$ con $u\in S$ e $v\in T$. Costo totale $O(n+m)$.

> [!info]- Spiegazione
> **Perché non sempre aiuta: due min-cut disgiunti in serie.** Rete $s\to v\to w\to t$ con $c(s,v)=2$, $c(v,w)=5$, $c(w,t)=2$. Il flusso massimo vale $2$, con $f^*(s,v)=f^*(w,t)=2$ saturi e $f^*(v,w)=2$ non saturo (residuo $3$). Due tagli minimi disgiunti: $(\{s\},\{v,w,t\})$ cap $2$, e $(\{s,v,w\},\{t\})$ cap $2$. Aumentare $c(s,v)$ lascia $c(w,t)=2$ come collo di bottiglia residuo, e viceversa; aumentare $c(v,w)$ (su nessun min-cut) non serve. **Nessun singolo arco** attraversa entrambi i tagli minimi.
>
> **Perché serve $v\in T$, non solo $v\notin S$.** La condizione più debole non basta: controesempio $s\to a$, $s\to b$, $a\to t$, $b\to t$ tutte cap $1$. $f^*$ satura tutto, $v(f^*)=2$, $S=\{s\}$. L'arco $(s,a)$ ha $u=s\in S$, $v=a\notin S$, ma $a$ non raggiunge $t$ in $G_f$ ($a\to t$ saturo): portare $c(s,a)$ a $2$ non cambia $v(f^*)$. Con $T=\{t\}$ e $a\notin T$, il criterio corretto scarta l'arco.
>
> **Complessità.** Costruire $G_f$ costa $O(m)$; ciascuna delle due visite (in avanti da $s$, all'indietro da $t$) costa $O(n+m)$; il confronto finale scorre gli $m$ archi una volta. Totale $O(n+m)$.
>
> **Dove si perdono punti:** dimostrare "non sempre possibile" con un esempio isolato senza collegarlo ai **due min-cut disgiunti** — è quel dettaglio strutturale a spiegare perché l'aumento è inutile su *qualunque* arco; oppure usare la condizione più debole $u\in S,\ v\notin S$ al posto di $u\in S,\ v\in T$.
### Innalzare uniformemente di 1 la capacità di ogni arco: il taglio minimo resta minimo?
*citazione: 30/06/2026 · Es. 1, punto 2* — contrappunto della voce precedente: qui l'aumento è uniforme su tutti gli archi e la domanda riguarda la stabilità del **taglio minimo**, non del flusso massimo.

> Claim: Sia $(A, B)$ un s-t-cut di capacità minima per la rete $G$. Sia $G'$ la rete ottenuta da $G$ aumentando la capacità di ogni arco di esattamente $1$. Allora $(A, B)$ è un s-t-cut di capacità minima anche per $G'$. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> **Falsa.** Aumentando la capacità di **ogni** arco di $1$, la capacità di un taglio $(A,B)$ cresce esattamente del numero di archi che lo attraversano da $A$ a $B$:
> $$\operatorname{cap}_{G'}(A,B)=\operatorname{cap}_G(A,B)+\bigl|\{e=(u,v)\in E: u\in A,\,v\in B\}\bigr|$$
> Tagli diversi possono avere un numero diverso di archi attraversanti: un taglio con **pochi** archi ma capacità iniziale solo leggermente maggiore riceve un incremento minore, e può superarlo in $G'$.

> [!info]- Spiegazione
> **Verifica numerica.** Nodi $s,p_1,p_2,p_3,m,t$. Archi: $s\to p_1=1$, $s\to p_2=1$, $s\to p_3=1$ (layer 1, 3 archi), $p_1\to m=10$, $p_2\to m=10$, $p_3\to m=10$ (non bottleneck), $m\to t=4$ (layer 2, 1 arco). Il taglio $(A,B)=(\{s\},\text{resto})$ è il minimo di $G$: $\operatorname{cap}_G(A,B)=3<4=\operatorname{cap}_G(A',B')$, dove $(A',B')$ è il taglio di layer 2 (attraversato dal solo $m\to t$).
>
> In $G'$ (ogni capacità $+1$): $\operatorname{cap}_{G'}(A,B)=3+3\cdot1=6$ (3 archi attraversanti), mentre $\operatorname{cap}_{G'}(A',B')=4+1\cdot1=5$ (1 arco attraversante). Ora $5<6$: $(A,B)$ **non è più** il taglio minimo, $(A',B')$ lo ha superato.
>
> **Il meccanismo generale.** Il vantaggio di $(A,B)$ era di sole $4-3=1$ unità in $G$, ma $(A,B)$ ha $2$ archi in più ad attraversarlo ($3$ contro $1$): l'incremento uniforme paga ogni arco attraversante allo stesso modo, quindi un taglio con più archi accumula più incremento assoluto anche se partiva più economico.
>
> **Dove si perdono punti:** dimostrare solo la formula generale ($\operatorname{cap}_{G'}=\operatorname{cap}_G+|\text{archi attraversanti}|$) senza costruire il controesempio numerico esplicito — un'affermazione universale falsa si giustifica con un controesempio verificabile, non solo con l'osservazione strutturale.
