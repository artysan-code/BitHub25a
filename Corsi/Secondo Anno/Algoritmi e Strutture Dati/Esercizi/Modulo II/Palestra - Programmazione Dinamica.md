---
tags:
  - algoritmi
  - dp
  - esercizi
nota:
  - "[[04 - Programmazione Dinamica I (Weighted Independent Set)]]"
  - "[[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]"
  - "[[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]]"
  - "[[Formulario Modulo II]]"
---
# Palestra — Programmazione Dinamica
Tutto l'allenamento della DP in un posto solo: **su cosa esercitarsi**. La teoria e la procedura — i cinque passi, come si scrive ciascuna forma, il repertorio dei problemi noti — stanno in [[Formulario Modulo II#Programmazione Dinamica]] e qui non si ripetono.
Dentro ci sono quattro cose: il **riconoscimento** (da una traccia mai vista alla forma della tabella, ricavato dall'audit delle 24 tracce), le **otto tracce d'esame** su cui allenarsi con indizio e soluzione richiudibili, le **cinque tracce risolte** per intero, e le **domande di teoria** realmente uscite ai compiti.

> [!info] Otto famiglie qui, sei forme nel Formulario — è la stessa cosa
> Questo file classifica le tracce in **otto famiglie** `F1`-`F8`, perché serve a dire *quale traccia somiglia a quale*. Il Formulario le raggruppa in **sei forme**, perché lì serve a dire *come si scrive la pagina*. La corrispondenza è questa, e non c'è nessun contenuto in più o in meno da una parte o dall'altra:
>
> | Formulario | Qui |
> |---|---|
> | Forma 1 · catena lineare a salto fisso | `F1` |
> | Forma 2 · predecessore univoco $p(j)$ | `F3` |
> | Forma 3 · prefisso più risorsa numerica | `F4` |
> | Forma 4 · cella vincolata, predecessore libero | `F2` |
> | Forma 5 · griglia o due collezioni | `F6` `F7` `F8` |
> | Forma 6 · stato a dominio fisso | `F5` |
## Come si usa questa pagina
Ogni item ha la **traccia integrale** e due callout richiudibili:
- **Indizio** — la sola definizione dello stato, da aprire se non parti proprio;
- **Soluzione** — i cinque passi per esteso, più una verifica numerica su un'istanza piccola.
Apri la soluzione **dopo** aver scritto la tua, non prima. Criterio di chiusura: l'item è chiuso quando produci tutti e cinque i passi senza aprire niente.
## Da dove viene questo catalogo
Sono state lette integralmente le **24 tracce** del Modulo II presenti in `Materiale Didattico/Modulo II/Esami/` (a.a. 2021-22 → 2025-26, ultima traccia 08/09/2026), più le 3 esercitazioni ufficiali del 2026. Delle 24:
- **6** sono in un formato diverso (`ESERCIZIO A/B`, co-docenza Clementi): 14/09/2022, 30/01/2023, 04/07/2023, 25/07/2023, 12/09/2023, 27/09/2023. Contengono DP solo come *teoria* (ricorrenza di Sequence Alignment, tabella del Knapsack da interpretare), mai come progettazione.
- **1** è in formato Gualà ma a **due soli esercizi**, senza Es. 3: 19/02/2024 (Gualà & Clementi).
- **17** hanno l'Esercizio 3 nella forma canonica «progettate un algoritmo di programmazione dinamica che…». Sono il corpus di questo catalogo.

Di queste 17, **12 hanno già uno svolgimento completo** scritto nella cartella `Esercizio 3 - Programmazione Dinamica/` (attualmente non nel working tree: sta nel commit `181c327`, recuperabile con `git show`). Le **5 restanti** — 22/06/2022, 18/07/2022, 28/09/2022, 20/07/2026, 08/09/2026 — sono risolte in fondo a questo file.
## La consegna — cosa è invariante e cosa no
Su 17 tracce con Es. 3:

| Elemento della consegna | Frequenza | Nota |
|---|---|---|
| Posizione: sempre terzo esercizio, 11 punti | 17/17 | mai spostato, mai pesato diversamente |
| Formula «Progettate un algoritmo di programmazione dinamica che…» | 17/17 | la tecnica è **dichiarata**: non si deve scegliere il paradigma |
| Si chiede il **valore** ottimo, non la soluzione | 17/17 | «calcoli il massimo…», mai «restituisca l'insieme» |
| «Si discuta la complessità temporale» esplicito | 10/17 | concentrato fra 13/06/2024 e 23/09/2025 |
| Titolo accademico fra parentesi in testa | 4/17 | solo dalle ultime quattro tracce (02/02/2026 →) |
| Esempio numerico o figura nel testo | 4/17 | quando la regola del gioco è ambigua a parole |
| Bonus / sottocaso semplificato dichiarato | 2/17 | 28/09/2022, 24/09/2024 |

Funzione obiettivo: **massimo in 12 casi**, **minimo in 4** (18/07/2022 costo noleggio, 09/09/2025 costo job, 02/02/2026 tempo di scavo, 30/06/2026 costo dominating set), **booleana in 1** (21/01/2025, raggiungibilità di un target).

> [!warning] La parola «pseudocodice» non compare mai
> In **0 tracce su 24** la consegna dell'Esercizio 3 chiede esplicitamente lo pseudocodice. È una convenzione del corso, non una richiesta scritta: si scrive perché completa la risposta, ma se il tempo stringe la priorità è sottoproblema → ricorrenza → complessità. La stessa verifica smentisce la stima «pseudocodice richiesto in 13/14» che circola nella meta-conoscenza d'esame.

> [!info] Il trend delle ultime quattro tracce
> Da febbraio 2026 la consegna **dà il nome accademico del problema fra parentesi**: *(La linea della metro D)*, *(minimum dominating set with discounts)*, *(Canguro)*, *(almost monochromatic longest increasing subsequence)*. Negli ultimi tre casi il titolo **è il suggerimento**: dice quale problema noto stai guardando e quale parametro è stato aggiunto. Prima cosa da fare all'esame: leggere il titolo e tradurlo in famiglia.
## Le otto famiglie — mappa
Ogni riga è una forma di tabella. La colonna «riferimento slide» è il problema del corso da cui la famiglia deriva; la colonna «tracce» conta le 17 assegnando a ciascuna la sua famiglia **principale** — le dimensioni innestate sopra sono nella colonna «innesto» dell'[[#Indice completo — traccia per traccia|indice completo]].

| # | Famiglia | Tabella | Costo tipico | Riferimento slide | Tracce |
|---|---|---|---|---|---|
| **F1** | Catena lineare a **salto fisso** | $\text{OPT}(i)$ | $\Theta(n)$ | WIS su cammino | 3 |
| **F2** | Catena lineare a **predecessore libero** | $\text{OPT}(i)$ vincolato | $O(n^2)$ | LIS, Segmented Least Squares | 3 |
| **F3** | **Weighted Interval Scheduling** travestito | $\text{OPT}(j)$ con $p(j)$ | $\Theta(n)$ | WIS pesato | 1 |
| **F4** | Prefisso $+$ **risorsa numerica** | $\text{OPT}(i,b)$ | $\Theta(nb)$ | Knapsack 0/1 | 4 |
| **F5** | Prefisso $+$ **stato a dominio fisso** | $\text{OPT}(i,s)$ | $\Theta(n\lvert S\rvert)$ | House Coloring | 2 |
| **F6** | **Intervallo** che si accorcia da due lati | $\text{OPT}(l,r)$ | $\Theta(n^2)$ | Segmented LS (2 indici) | 1 |
| **F7** | **Due sequenze** accoppiate | $\text{OPT}(i,j)$ | $\Theta(nm)$ | Sequence Alignment | 1 |
| **F8** | **Griglia** / DAG implicito | $\text{OPT}(i,j)$ | $\Theta(nm)$ | Sequence Alignment, Bellman-Ford | 2 |

Le famiglie non sono esclusive: in **6 tracce su 17** la tabella ha **una dimensione in più** rispetto alla famiglia base — 28/09/2022, 16/07/2024, 24/09/2024 (solo nella parte bonus), 23/09/2025, 20/07/2026, 08/09/2026. L'innesto è quasi sempre F4 (risorsa numerica) o F5 (stato a dominio fisso) su un'altra famiglia, ed è il pattern dominante delle tracce recenti.
## Albero decisionale — riconoscere la famiglia in un minuto
Quattro domande, in quest'ordine. La prima fissa il **numero di indici geometrici**, la seconda il **numero di indici di stato**, la terza il verso, la quarta dove si legge la risposta.
**1. Su cosa scorre il problema?**

| Nella traccia c'è… | Indici geometrici |
|---|---|
| una fila di oggetti / giorni / nodi di un cammino | uno: $i$ → F1, F2, F3 |
| **due** collezioni che si consumano entrambe | due: $(i,j)$ → F7 |
| una **matrice** e un oggetto che ci si muove dentro | due: $(i,j)$ = posizione → F8 |
| **un** segmento che si accorcia **da entrambi i lati** | due: $(l,r)$ = estremi → F6 |

**2. Per decidere sull'elemento $i$, cosa devo sapere del passato che $\text{OPT}(i-1)$ non mi dice?**

| Risposta                                                                           | Conseguenza                                                                                        |
| ---------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| nulla: la scelta esclude una finestra di ampiezza **fissa**                        | **F1** — un indice, ricorrenza a due-tre rami, $\Theta(n)$                                         |
| **quale** era il predecessore, perché il contributo di $i$ dipende da lui          | **F2** — sottoproblema «che termina esattamente in $i$», $\max$ interno su tutti i $j<i$, $O(n^2)$ |
| quale era il predecessore, ma è **univoco** e calcolabile in $O(1)$                | **F3** — $p(j)$ esplicito, si torna a $\Theta(n)$                                                  |
| **quanta** risorsa ho già speso (budget, batteria, contatore, valore accumulato)   | **F4** — secondo indice **numerico**                                                               |
| **com'è finita** la soluzione parziale (colore, quanti contigui, flag usa-e-getta) | **F5** — secondo indice a **dominio fisso**                                                        |
|                                                                                    |                                                                                                    |

**3. Il verso.** Massimo, minimo o booleano? Con il minimo il neutro dei casi base è $0$ per «niente da fare» e $+\infty$ per «configurazione inammissibile» — non si mescolano. Con il booleano non c'è né $\max$ né $\min$: c'è un $\lor$.
**4. Dove si legge la risposta.** Rileggi la definizione del sottoproblema: se contiene un vincolo («che termina in $i$», «con esattamente $b$ usati», «con $v_i$ non ancora dominato»), la risposta **non** è l'ultima cella ma un $\max$/$\min$ finale che scioglie il vincolo.

> [!warning] La domanda 2 è l'unica che conta davvero
> Le famiglie F4 e F5 nascono entrambe da un «non mi basta $\text{OPT}(i-1)$», e la differenza fra le due decide la complessità: dominio del secondo indice **numerico** (limitato da un valore dell'input) contro **fisso** (limitato da una costante o da $n$). Sbagliare qui non produce un algoritmo sbagliato, produce una complessità sbagliata — e la complessità è metà del punteggio dell'esercizio.
## F1 · Catena lineare a salto fisso
La famiglia di [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS su cammino]]: oggetti in fila, si decide su ciascuno, e la decisione «prendo $i$» esclude una **finestra di ampiezza fissa**, nota a priori dal testo. Un solo indice, un numero costante di rami, cella $O(1)$.
**Segnale nella traccia** — «non puoi farlo per due giorni consecutivi», «fra una vincita e l'altra almeno 3 settimane», «questa mossa consuma le due monete successive», «il furgone rosso copre tre giorni». La parola chiave è un **numero costante** che dice quante posizioni si bruciano.
**Sottoproblema** — $\text{OPT}(i)$: ottimo sul prefisso $1..i$ (se il vincolo guarda indietro) oppure sul suffisso $i..n$ (se ogni mossa proietta in avanti, come nei giochi a pila e nei problemi di copertura).
**Ricorrenza tipo** — un ramo «salto $i$», uno o più rami «uso $i$ e atterro $d$ posizioni più in là»:
$$\text{OPT}(i) = \max\bigl\{\text{OPT}(i-1),\ v_i + \text{OPT}(i-d-1)\bigr\} \qquad\text{(prefisso)}$$
$$\text{OPT}(i) = \min\bigl\{c_i^{(1)} + \text{OPT}(i+d_1),\ c_i^{(2)} + \text{OPT}(i+d_2)\bigr\} \qquad\text{(suffisso, copertura)}$$
**Caso base** — $\text{OPT}(i)=0$ per ogni $i \le 0$ (prefisso) o $i>n$ (suffisso). Va scritto come **disuguaglianza**, non come singolo valore: se la ricorrenza salta di $3$ o $4$, genera più indici fuori range contemporaneamente.
**Costo** — $\Theta(n)$ celle $\times$ $O(1)$ $=\Theta(n)$. Spazio $O(1)$ con finestra scorrevole, se non serve ricostruire.
**Tracce** — 22/06/2022 (pila di monete, mosse che consumano 2 o 3), 18/07/2022 (noleggio furgoni, copertura a span 2 e 3), 18/02/2025 (vincita con pause obbligate, salto a $j-4$). Palestra ufficiale: **esercitazione 2** (ripetitori wifi H/L), dove il prof scrive lui la ricorrenza.

> [!warning] Il salto non è mai $j-2$ per default
> In WIS il salto è $j-2$ perché il vincolo è l'adiacenza. Se il testo dice «almeno $k$ posizioni di pausa», il salto diventa $j-k-1$; se dice «l'oggetto occupa $k$ posizioni», diventa $i+k$. Riderivarlo sull'istanza minima (tre elementi) prima di scriverlo costa dieci secondi e salva l'esercizio.

> [!warning] Copertura ≠ selezione — e lo stato non è «il primo punto scoperto»
> Nei problemi di copertura (furgoni, ripetitori) il vincolo non è «non sovrapporre» ma «non lasciare buchi», e **la sovrapposizione è ammessa**: il testo dice «almeno un furgone», non «esattamente uno». Questo rompe l'indicizzazione istintiva sul primo punto scoperto. L'oggetto che copre il primo giorno scoperto $j$ può partire da $j$, ma anche da $j-1$ o $j-2$ — cioè **dentro la zona già coperta** — se da lì costa meno. Lo stato corretto è «dove installo il **prossimo** oggetto», e i rami enumerano dove va quello dopo. Dettaglio e controesempio in [[#18/07/2022 · Noleggio furgoni — F1 (copertura)]].
## F2 · Catena lineare a predecessore libero
La famiglia di [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Longest Increasing Subsequence (LIS)|LIS]] e del Segmented Least Squares. Un solo indice come in F1, ma il sottoproblema è **vincolato** — «la soluzione che termina esattamente in $i$» — perché il contributo dell'elemento $i$ dipende da *quale* elemento lo precede, non da una distanza fissa.
**Segnale nella traccia** — il guadagno di una mossa è funzione della **distanza** o dell'**identità** del predecessore: «l'energia raddoppia ad ogni battaglia in cui non usi l'arma», «lo sconto è $\min\{p_j, c_i\}$ dove $i$ è l'ultima volta che ci sei stato», «i valori devono formare una sequenza crescente». Se ti accorgi che per valutare $i$ devi conoscere $i$ *e* il suo predecessore, sei qui.
**Sottoproblema** — $\text{OPT}(i)$: ottimo fra gli elementi $1..i$ **a condizione che $i$ sia l'ultimo selezionato**. Questa clausola è il cuore della famiglia: senza, la ricorrenza non si scrive.
**Ricorrenza tipo** — un massimo su tutti i predecessori ammissibili, più il caso «$i$ è il primo»:
$$\text{OPT}(i) = \max\Bigl\{\,\text{base}(i),\ \max_{j<i,\ j\text{ compatibile con }i}\bigl(\text{OPT}(j) + g(j,i)\bigr)\Bigr\}$$
**Caso base** — spesso gratis: $\text{OPT}(i) = \text{base}(i)$ quando l'insieme dei predecessori è vuoto (in LIS, $1 + \max(0,\ldots) = 1$). Talvolta si introduce un indice fittizio $\text{OPT}(0)=0$ che rappresenta «nessun predecessore».
**Risposta** — $\max_{1\le i\le n} \text{OPT}(i)$, **mai** $\text{OPT}(n)$: la soluzione ottima non è obbligata a terminare sull'ultimo elemento.
**Costo** — $\Theta(n)$ celle $\times$ $O(n)$ per cella $= O(n^2)$.
**Tracce** — 26/06/2025 (BurgerGata, sconto $\min\{p_j,c_i\}$), 18/07/2025 (Tube Invaders, energia $\min\{2^{\,i-p-1}, a_i\}$), 08/09/2026 (LIS quasi monocromatica, F2 $+$ contatore di cambi).

> [!warning] Non è Weighted Interval Scheduling
> In WIS il predecessore è **univoco**: $p(j)$, il più grande $i$ compatibile, e il salto a $p(j)$ scarta in un colpo tutti gli incompatibili. Qui non esiste un $p(j)$ da calcolare, perché **ogni** $j<i$ può essere il predecessore con un contributo diverso: vanno confrontati tutti. È la differenza fra $\Theta(n)$ e $O(n^2)$, e fra una risposta giusta e una che sottostima l'ottimo.
## F3 · Weighted Interval Scheduling travestito
Stessa forma di F2, ma il predecessore è univoco e si calcola in $O(1)$ direttamente dai dati: si torna a una decisione **binaria** e a costo lineare.
**Segnale nella traccia** — ogni elemento **occupa** un intervallo di tempo o di spazio, dichiarato o deducibile: «per preparare l'esame del giorno $j$ ti occorrono $g_j$ giorni di studio consecutivi» nasconde l'intervallo $[\,j-g_j,\ j\,]$ di peso $c_j$.
**Sottoproblema** — $\text{OPT}(j)$: ottimo considerando solo i primi $j$ elementi, **senza** vincolo su cosa è stato preso (a differenza di F2). Attenzione al significato di $j$: è «fino a che punto del calendario guardo», non «quanti elementi ho preso».
**Ricorrenza tipo**
$$\text{OPT}(j) = \max\bigl\{\text{OPT}(j-1),\ w_j + \text{OPT}(p(j))\bigr\}, \qquad p(j) = j - g_j - 1$$
con il primo ramo da solo quando l'intervallo di $j$ non ci sta ($g_j > j-1$).
**Costo** — $\Theta(n)$: il calcolo di $p(j)$ è una sottrazione, non serve ricerca binaria perché il calendario fornisce già l'ordinamento per tempo di fine. È **meglio** del WIS pesato generico ($O(n\log n)$), e vale la pena dirlo esplicitamente nella risposta.
**Tracce** — 24/09/2024 (sessione d'esami; la parte bonus aggiunge la pillola come stato F5 usa-e-getta, restando $\Theta(n)$).

> [!info] Come riconoscere l'intervallo nascosto
> Cerca la frase che lega un elemento a una **durata**: «$g_j$ giorni consecutivi», «il furgone è a disposizione per tre giorni», «il ripetitore copre le tratte $i$ e $i+1$». Se la durata è **costante** sei in F1; se dipende da $j$ e produce un predecessore univoco sei in F3; se il contributo dipende dal predecessore scelto sei in F2.
## F4 · Prefisso più risorsa numerica
La famiglia di [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]]: al primo indice se ne affianca un secondo che misura **quanta risorsa è stata consumata** (o quanto ne resta). È la famiglia più frequente nel campione e il twist più usato dal prof.
**Segnale nella traccia** — «al più $k$», «un budget $B$», «una batteria di $\Delta$ unità», «hai una sola pillola», «restituisce true se è possibile ottenere $N$», «devi pagare $c_k$ se assegni $k$ job». La prova del nove: *due strategie possono arrivare allo stesso elemento $i$ avendo speso quantità diverse, e la differenza cambia cosa posso fare dopo.*
**Sottoproblema** — $\text{OPT}(i,b)$: ottimo sul prefisso $1..i$ (o sul suffisso $i..n$) con $b$ unità di risorsa consumate, oppure residue. Le due convenzioni sono equivalenti; sceglierne una e **dichiararla**, perché decide il verso del riempimento.
**Ricorrenza tipo**
$$\text{OPT}(i,b) = \max\bigl\{\text{OPT}(i-1,b),\ v_i + \text{OPT}(i-1,\,b-\delta_i)\bigr\}$$
con il secondo ramo attivo solo se $b \ge \delta_i$. Nelle varianti booleane il $\max$ diventa $\lor$; nelle varianti a costo fisso pagato alla fine il termine costante si aggiunge **fuori** dalla tabella, in un $\min$ finale su $b$.
**Costo** — $\Theta(n \cdot B)$ dove $B$ è l'estensione del secondo indice, cella $O(1)$.
**Tracce** — 28/09/2022 (comizi, budget $B$), 16/07/2024 (scavatore, batteria $\Delta$), 21/01/2025 (operatori $+,\times,\pm$, valore accumulato $v$, ricorrenza booleana), 09/09/2025 (job su due macchine, contatore $k$ per il costo fisso). Composte: 23/09/2025 (F5 $+$ budget di rosso), 20/07/2026 (F8 $+$ $k$ salti), 08/09/2026 (F2 $+$ $k$ cambi di colore).

> [!warning] Polinomiale o pseudo-polinomiale — la domanda che separa la risposta completa
> $\Theta(nB)$ **non** è automaticamente pseudo-polinomiale. Decide da cosa è limitato $B$:
> - $B$ è un **valore numerico dell'input**, libero di crescere indipendentemente da $n$ (capacità $W$, batteria $\Delta$, target $N$) → **pseudo-polinomiale**: $\Delta$ occupa $O(\log \Delta)$ bit ma compare linearmente nel costo.
> - $B$ conta **elementi** e non può superarne il numero (quante case rosse, quanti comizi, quanti job su $B$, quanti cambi di colore, quanti salti) → si tronca a $\min(B,n)$ e resta **polinomiale**, $O(n^2)$.
>
> Nel campione: pseudo-polinomiali 16/07/2024 e 21/01/2025; polinomiali tutte le altre. Scrivere prima $\Theta(nB)$ e poi aggiungere l'osservazione sul troncamento è la forma di risposta che vale il punteggio pieno.
## F5 · Prefisso più stato a dominio fisso
La famiglia di House Coloring: il secondo indice non misura una quantità, **etichetta la configurazione del bordo destro** della soluzione parziale. Il suo dominio è una costante (o comunque indipendente dai valori numerici dell'input), quindi la DP resta lineare.
**Segnale nella traccia** — un vincolo **locale** fra elementi vicini che non si riduce a una distanza: «non puoi colorare case adiacenti dello stesso colore», «ricevi lo sconto se fai parte di un blocco contiguo lungo almeno 3», «ogni nodo fuori da $S$ deve essere adiacente a un nodo di $S$», «hai una sola pillola». Domanda diagnostica: *quante configurazioni diverse del bordo destro devo distinguere per poter decidere sull'elemento successivo?* Se la risposta è un numero piccolo e fisso, sei qui.
**Sottoproblema** — $\text{OPT}(i,s)$: ottimo sul prefisso $1..i$ con l'elemento $i$ nello stato $s \in S$, dove $S$ è l'insieme delle configurazioni del bordo. Definire $S$ per **estensione**, con una tabella stato→significato, è metà dell'esercizio: se gli stati sono ben scelti la ricorrenza si scrive da sola.
**Ricorrenza tipo**
$$\text{OPT}(i,s) = \text{costo}(i,s) + \min_{s' \to s \text{ ammissibile}} \text{OPT}(i-1,s')$$
Le transizioni inammissibili si scrivono $+\infty$ (per un minimo) o $-\infty$ (per un massimo), non si omettono: una cella mancante nella tabella è un buco nella dimostrazione.
**Risposta** — $\min_{s \text{ finale ammissibile}} \text{OPT}(n,s)$: se qualche stato lascia qualcosa «in sospeso» (un nodo non ancora dominato, un blocco non ancora valido) va **escluso** dal minimo finale.
**Costo** — $\Theta(n \cdot \lvert S\rvert)$, cioè $\Theta(n)$ perché $\lvert S\rvert$ è costante. Vale la pena scriverlo esplicitamente: è il punto in cui si dimostra di aver capito la differenza con F4.
**Tracce** — 30/06/2026 (dominating set con sconti: cinque stati $\text{IN}_1, \text{IN}_2, \text{IN}_{\ge3}, \text{OUT}_D, \text{OUT}_U$), 23/09/2025 (colorazione case: tre colori, composta con F4 per il budget di rosso). Composta minore: 24/09/2024 bonus (pillola disponibile/consumata, $\lvert S\rvert = 2$).

> [!info] Stato composito — la regola di costruzione
> Quando il vincolo riguarda **più cose insieme** (sono dentro o fuori? quanto è lungo il blocco? il vicino è già dominato?), lo stato è il **prodotto** delle risposte necessarie, potato delle combinazioni impossibili. Nel dominating set con sconti servono cinque stati e non quattro perché «fuori da $S$» va spaccato in *già dominato* e *ancora in sospeso*, e «dentro $S$» in blocco di lunghezza $1$, $2$, $\ge 3$ — il $3$ viene dalla soglia dello sconto. Il numero di stati esce dalla soglia che il testo dichiara.
## F6 · Intervallo che si accorcia da due lati
Due indici, ma **non** due sequenze: sono gli **estremi** di un unico segmento residuo. Nasce quando gli elementi spariscono da entrambi i lati e il residuo non è più un prefisso.
**Segnale nella traccia** — «puoi prendere solo uno dei due pezzi esterni», «rimuovi dalla cima», e in generale ogni regola che dopo una mossa lascia ancora un **segmento contiguo**, ma accorciato in modo asimmetrico.
**Sottoproblema** — $\text{OPT}(l,r)$: ottimo quando il segmento residuo è $[l,r]$ (e, se il problema ha turni, quando tocca a te).
**Ricorrenza tipo**
$$\text{OPT}(l,r) = \max\bigl\{\,g_l + \text{OPT}(l+a,\,r-b),\ \ g_r + \text{OPT}(l+b,\,r-a)\,\bigr\}$$
dove $a,b$ vengono dalla regola del gioco e sono in generale **diversi** fra i due rami.
**Caso base** — $\text{OPT}(l,r)=0$ per ogni $l>r$, come disuguaglianza: la ricorrenza produce celle in cui $l$ supera $r$ di due o tre.
**Ordine di riempimento** — per **lunghezza crescente** del segmento: $d = r-l$ da $0$ a $n-1$, e per ogni $d$ tutti gli $l$. Non per righe: le dipendenze vanno dalle finestre corte a quelle lunghe.
**Costo** — $\Theta(n^2)$ celle $\times$ $O(1)$.
**Tracce** — 13/06/2024 (pizza a gusti misti). Palestra ufficiale: **esercitazione 3**, massima sottostringa palindroma, che ha esattamente questa forma e lo stesso ordine di riempimento «in diagonale».

> [!warning] Sembra minimax e non lo è
> Nella pizza, Alice e Bob mangiano **sempre** i due pezzi più esterni: non scelgono. La funzione obiettivo conta solo i pezzi che mangi tu, quindi la ricorrenza è $\max$-$\max$, non $\max$-$\min$. Lo stesso vale per le due pile di fiches. Il segnale che distingue un vero minimax è che **l'avversario ottimizza**; se il testo descrive la sua mossa come deterministica, è solo una regola di transizione.
## F7 · Due sequenze accoppiate
Due indici, uno per collezione, come in [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)|Sequence Alignment]]: entrambe si consumano e lo stato è quanto resta di ciascuna.
**Segnale nella traccia** — due liste, due pile, due macchine, due stringhe, e una mossa che tocca **entrambe**.
**Sottoproblema** — $\text{OPT}(i,j)$: ottimo con $i$ elementi residui nella prima collezione e $j$ nella seconda.
**Ricorrenza tipo**
$$\text{OPT}(i,j) = \max\bigl\{\,a_i + \text{OPT}(i-1,\,j-2),\ \ b_j + \text{OPT}(i-2,\,j-1),\ \ 0\,\bigr\}$$
**Costo** — $\Theta(nm)$, **polinomiale** senza discussione: $n$ e $m$ sono lunghezze, non valori. Spazio riducibile a $O(m)$ con le ultime righe.
**Tracce** — 09/09/2024 (due pile di fiches).

> [!warning] Il consumo è accoppiato e asimmetrico
> In Sequence Alignment le due sequenze si consumano in modo simmetrico (un carattere per volta, da una o da entrambe). Nelle fiches una mossa **sola** toglie $1$ da una pila e $2$ dall'altra: il salto nella tabella è diagonale e sbilanciato. Copiare la ricorrenza del Sequence Alignment senza rileggere la regola del gioco è l'errore tipico.
## F8 · Griglia o DAG implicito
Due indici che sono una **posizione**, non una risorsa. Il problema è un cammino ottimo su un grafo aciclico che la traccia non disegna: le mosse consentite sono gli archi.
**Segnale nella traccia** — «una matrice di $n$ righe e $m$ colonne», «potete muovervi solo verso destra o verso il basso», «dovete arrivare da $(1,1)$ a…». Le mosse monotone garantiscono l'aciclicità, che è ciò che rende lecita la DP.
**Sottoproblema** — $\text{OPT}(i,j)$: ottimo di un cammino ammissibile da $(1,1)$ a $(i,j)$. Con caselle proibite si aggiunge la convenzione $\pm\infty$ per «non raggiungibile».
**Ricorrenza tipo**
$$\text{OPT}(i,j) = \text{val}(i,j) + \min\bigl\{\text{OPT}(i-1,j),\ \text{OPT}(i,j-1)\bigr\}$$
Sui bordi il termine inesistente si **omette** dal minimo, non si sostituisce con uno zero.
**Costo** — $\Theta(nm)$ con mosse a passo unitario. Con mosse di lunghezza arbitraria la cella costa $O(n+m)$ e si torna a $O(1)$ precalcolando i massimi di prefisso per riga e per colonna.
**Tracce** — 02/02/2026 (linea della metro D: tempo minimo, reperti che allungano, colonne doriche impraticabili), 20/07/2026 (Canguro: F8 $+$ $k$ salti, quindi tabella a tre indici).

> [!info] Quando la griglia diventa a tre indici
> Se oltre alla posizione c'è una risorsa globale (salti disponibili, carburante, pedaggi), si innesta F4: $\text{OPT}(i,j,s)$. Il costo passa a $\Theta(nmk)$, e resta polinomiale finché $k$ è limitato da una quantità legata a $n+m$ — nel Canguro, più di $n+m-2$ salti non servono a nulla.
## I sette twist — come la traccia viene costruita
Le famiglie dicono *che forma ha la tabella*. I twist dicono *cosa è stato cambiato* rispetto al problema delle slide: sono il modo in cui un problema noto diventa una traccia inedita. In **14 tracce su 17** la famiglia coincide con quella di un problema delle slide `04`-`06`, e l'esercizio è «problema del corso $+$ un twist». Le **3** restanti — pizza (13/06/2024), metro D (02/02/2026), Canguro (20/07/2026) — usano una forma di tabella che nelle slide non compare come problema a sé, ma che è nelle **esercitazioni ufficiali**: massima sottostringa palindroma per l'intervallo $(l,r)$, cammino su griglia per la matrice.

| Twist | Cosa cambia | Effetto sulla tabella | Tracce |
|---|---|---|---|
| **T1 · Budget** | si aggiunge «al più $k$ / capacità $\Delta$ / target $N$» | $+1$ dimensione (F4) | 6 |
| **T2 · Distanza generalizzata** | l'adiacenza diventa distanza $d$, o l'oggetto occupa $d$ posizioni | stesso indice, salto diverso | 3 |
| **T3 · Contributo dal predecessore** | il guadagno di $i$ dipende da chi lo precede | F1 $\to$ F2: sottoproblema vincolato, cella $O(n)$ | 2 |
| **T4 · Stato locale / soglia** | vincolo fra vicini, o risorsa usa-e-getta | $+1$ dimensione a dominio fisso (F5) | 3 |
| **T5 · Costo noto solo alla fine** | un termine che dipende dal totale, non dai singoli | contatore in tabella, termine aggiunto nel $\min$ finale | 1 |
| **T6 · Obiettivo non numerico** | «restituisce true se…» | $\max \to \lor$, nessuna ottimizzazione | 1 |
| **T7 · Avversario deterministico** | qualcuno agisce fra due tue mosse, ma non sceglie | nessuno: resta $\max$-$\max$, **non** minimax | 2 |

> [!info] Il twist dominante è T1, e sta crescendo
> Nelle ultime **6 tracce** (09/09/2025 → 08/09/2026), **4** contengono un parametro esplicito da trasformare in dimensione della tabella: il contatore $k$ dei job su $B$, il budget di case rosse, i $k$ salti del Canguro, i $k$ cambi di colore della LIS. Il riflesso da allenare: leggere la traccia cercando **il numero che limita qualcosa**, e chiedersi subito se è limitato da $n$ (polinomiale) o da un valore dell'input (pseudo-polinomiale).

> [!warning] Il twist non cambia solo la ricorrenza, cambia dove si legge la risposta
> Aggiungere una dimensione sposta quasi sempre la risposta da «l'ultima cella» a un $\min$/$\max$ finale: su $b$ se il budget è «esattamente», su $s$ se lo stato finale può essere inammissibile, su $i$ se il sottoproblema è vincolato a terminare in $i$. Rileggere il passo 1 prima di scrivere la risposta è l'ultimo controllo che conviene fare sempre.
## Indice completo — traccia per traccia
Le 17 tracce in ordine cronologico. La colonna «svolto» rimanda al file in `Esercizio 3 - Programmazione Dinamica/` (commit `181c327`); «§» rimanda alla sezione finale di questo file.

| Data | Problema | Famiglia | Innesto | Tabella | Costo | Ob. | Svolto |
|---|---|---|---|---|---|---|---|
| 22/06/2022 | Pila di monete (PrimaDiTre / SecondaDiDue) | F1 | T2 | $\text{OPT}(i)$ suffisso | $\Theta(n)$ | max | § |
| 18/07/2022 | Noleggio furgoni rosso e giallo | F1 copertura | T2 | $\text{OPT}(i)$ suffisso | $\Theta(n)$ | min | § |
| 28/09/2022 | Comizi elettorali con budget $B$ | F4 su base F1 | T1 | $\text{OPT}(j,b)$ | $O(n\min(B,n))$ | max | § |
| 13/06/2024 | Pizza a gusti misti | F6 | T7 | $\text{OPT}(l,r)$ | $\Theta(n^2)$ | max | `01` |
| 16/07/2024 | Scavatore e batteria | F4 su base F1 | T1 | $\text{OPT}(i,b)$ suffisso | $\Theta(n\Delta)$ *pseudo-pol.* | max | `02` |
| 09/09/2024 | Due pile di fiches | F7 | T7 | $\text{OPT}(i,j)$ | $\Theta(nm)$ | max | `03` |
| 24/09/2024 | Sessione d'esami (bonus: pillola) | F3 | T4 | $\text{OPT}(j)$ / $\text{OPT}(j,t)$ | $\Theta(n)$ | max | `04` |
| 21/01/2025 | Operatori $+,\times,\pm$ e target $N$ | F4 booleano | T1 T6 | $\text{OPT}(i,v)$ | $\Theta(nM)$ *pseudo-pol.* | bool | `05` |
| 18/02/2025 | Vincita con pause obbligate | F1 | T2 | $\text{OPT}(j)$ | $\Theta(n)$ | max | `06` |
| 26/06/2025 | BurgerGata e coupon | F2 | T3 | $\text{OPT}(j)$ vincolato | $O(n^2)$ | max | `07` |
| 18/07/2025 | Tube Invaders | F2 | T3 | $\text{OPT}(i)$ vincolato | $O(n^2)$ | max | `08` |
| 09/09/2025 | Job su due macchine | F4 contatore | T5 | $\text{OPT}(i,k)$ | $\Theta(n^2)$ | min | `09` |
| 23/09/2025 | Colorazione case con budget di rosso | F5 | T1 T4 | $\text{OPT}(i,c,b)$ | $\Theta(n\min(k,n))$ | min | `10` |
| 02/02/2026 | La linea della metro D | F8 | — | $\text{OPT}(i,j)$ | $\Theta(nm)$ | min | `11` |
| 30/06/2026 | Minimum dominating set with discounts | F5 | T4 | $\text{OPT}(i,s)$, $\lvert S\rvert=5$ | $\Theta(n)$ | min | `12` |
| 20/07/2026 | Canguro | F8 | T1 | $\text{OPT}(i,j,s)$ | $\Theta(nmk)$ | max | § |
| 08/09/2026 | Almost monochromatic LIS | F2 | T1 | $\text{OPT}(i,t)$ | $O(n^2k)$ | max | § |
## Progettazione — Esercizio 3
Otto item, tutti **Esercizio 3** di tracce reali. Il primo — i comizi del 28/09/2022 — non è in ordine di data: sta in testa perché è il più semplice e la traccia stessa offre un sottocaso con punteggio parziale. Gli altri sette seguono in ordine di data decrescente.
### Comizi elettorali con budget
> [!question] Domanda d'esame — Comizi elettorali
> **D:** «State preparando la campagna elettorale in vista delle elezioni e volete pianificare dei comizi per aumentare la vostra chance di vincere. Davanti a voi avete $n$ giorni ma gli esperti dicono che non tutti i giorni garantiscono la stessa visibilità. In particolare, sapete che fare un comizio il giorno $i$ vi farà guadagnare $v_i$ voti. Regole di fairness impongono che **non potete fare comizi per due giorni consecutivi**. Inoltre, i soldi a vostra disposizione per organizzare gli eventi sono limitati e **il numero di comizi deve essere al più $B$**. Progettate un algoritmo di programmazione dinamica che calcoli il numero massimo di voti che potete guadagnare.
> *Una semplificazione*: un sottocaso più semplice è lo scenario in cui siete schifosamente ricchi e quindi non avete vincoli sul numero di comizi (ma il vincolo di fairness resta). Se non riuscite a progettare un algoritmo per il caso generale potete risolvere questo sottocaso (che però non dà diritto al punteggio pieno).» *(traccia 28/09/2022 · Es. 3 · docenti Gualà & Clementi, struttura canonica)*

> [!info] Comincia da qui
> È l'item con cui aprire la palestra, e la ragione sta nella «semplificazione» che la traccia stessa offre: **il sottocaso è esattamente il Weighted Independent Set su cammino**, quello della nota [[04 - Programmazione Dinamica I (Weighted Independent Set)]]. «Non due giorni consecutivi» è «non due nodi adiacenti», i voti sono i pesi.
> Quindi qui vedi il meccanismo in purezza: **problema già noto + un budget $B$ che diventa una dimensione della tabella**. È il pattern che ricorre nelle tracce recenti, e questa è la sua forma più nuda.
> Fai prima il sottocaso senza budget, a mente (dovresti impiegarci un minuto). Poi aggiungi $B$ e guarda che cosa cambia nei cinque passi — cambia meno di quanto sembri.

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Problema noto: **WIS su cammino**. Il budget aggiunge un secondo indice.
> $\text{OPT}[i][b]$ = massimo numero di voti considerando i **primi $i$ giorni**, avendo fatto **al più $b$** comizi.
> Il resto prova a tirarlo fuori da solo prima di aprire le soluzioni qui sotto.

> [!info]- Soluzione — parte 1: il sottocaso senza budget
> **1 · Sottoproblema.** $\text{OPT}[i]$ = il massimo numero di voti ottenibile considerando solo i **primi $i$ giorni**. Sono $n+1$ sottoproblemi, $i = 0, \ldots, n$.
>
> **2 · Ricorrenza.** Interrogo la soluzione ottima sul giorno $i$: ci faccio comizio o no? I due casi sono esaustivi.
> - *non lo faccio* → tutto viene dai primi $i-1$ giorni: $\text{OPT}[i-1]$;
> - *lo faccio* → incasso $v_i$, e il giorno $i-1$ mi è vietato: $v_i + \text{OPT}[i-2]$.
> $$\text{OPT}[i] = \max\{\text{OPT}[i-1],\ \ v_i + \text{OPT}[i-2]\}$$
>
> **3 · Casi base.** $\text{OPT}[0] = 0$ (nessun giorno). $\text{OPT}[1] = v_1$ (un giorno solo: il comizio non ha vincoli da rispettare, quindi conviene sempre). Ne servono **due** perché la ricorrenza guarda indietro di due posizioni.
>
> **4 · Ordine di riempimento e dove si legge la risposta.** Per $i$ **crescente** da 2 a $n$: ogni cella dipende da $i-1$ e $i-2$, già pronte. La risposta è $\text{OPT}[n]$.
>
> **5 · Complessità.** $n+1$ celle, $O(1)$ ciascuna (un confronto fra due valori noti): **$\Theta(n)$ tempo**, $\Theta(n)$ spazio — riducibile a $O(1)$ tenendo solo le ultime due celle, se non serve ricostruire quali giorni scegliere.

> [!info]- Soluzione — parte 2: il caso generale con budget $B$
> **1 · Sottoproblema.** $\text{OPT}[i][b]$ = il massimo numero di voti considerando i **primi $i$ giorni**, avendo fatto **al più $b$** comizi. Sono $(n+1)(B+1)$ sottoproblemi.
> Il secondo indice serve perché «ho guardato i primi $i$ giorni» non dice **quanti comizi ho già speso**, e senza quel dato non si può decidere se è ancora lecito farne uno.
>
> **2 · Ricorrenza.** Stessa domanda di prima sul giorno $i$, ma ora fare il comizio **costa** una unità di budget:
> - *non lo faccio* → il budget non si consuma: $\text{OPT}[i-1][b]$;
> - *lo faccio* (possibile solo se $b \ge 1$) → incasso $v_i$, salto il giorno $i-1$ **e** spendo un comizio: $v_i + \text{OPT}[i-2][b-1]$.
> $$\text{OPT}[i][b] = \max\{\text{OPT}[i-1][b],\ \ v_i + \text{OPT}[i-2][b-1]\} \qquad (b \ge 1)$$
>
> **3 · Casi base.** $\text{OPT}[0][b] = 0$ e $\text{OPT}[1][b] = v_1$ per ogni $b \ge 1$; $\text{OPT}[i][0] = 0$ per ogni $i$ (senza comizi disponibili non si guadagna nulla). Servono sia le due righe iniziali (la ricorrenza guarda $i-2$) sia la colonna $b=0$ (guarda $b-1$).
>
> **4 · Ordine di riempimento e dove si legge la risposta.** Ciclo esterno su $i$ crescente da 2 a $n$, interno su $b$ da 0 a $B$: entrambe le righe $i-1$ e $i-2$ devono essere complete prima di iniziare la riga $i$. La risposta è $\text{OPT}[n][B]$, **senza** massimo su $b$: lo stato dice «al più $b$», quindi $\text{OPT}[n][B]$ include già le soluzioni che usano meno comizi. (Se avessi definito lo stato con «esattamente $b$», allora sì, servirebbe $\max_{b \le B}$.)
>
> **5 · Complessità.** $(n+1)(B+1)$ celle, $O(1)$ ciascuna: **$\Theta(nB)$ tempo** e $\Theta(nB)$ spazio, riducibile a $\Theta(B)$ tenendo due righe.
>
> **I due errori che costano il punto**, entrambi nel ramo «lo faccio»:
> - scrivere $v_i + \text{OPT}[i-2][b]$ — hai fatto un comizio e non l'hai pagato;
> - scrivere $v_i + \text{OPT}[i-1][b-1]$ — hai pagato il comizio ma hai dimenticato che il giorno prima è vietato.
> Nel ramo giusto **i due indici si muovono insieme**: $i-2$ per il vincolo di adiacenza, $b-1$ per il budget.
>
> **Verifica su un'istanza minuscola.** $n=3$, $v = [5, 10, 5]$, $B=1$. Senza budget l'ottimo è 10 (o il solo giorno 2, o i giorni 1 e 3). Con $B=1$ resta 10, ma solo via il giorno 2. La tabella dà $\text{OPT}[2][1] = \max\{5,\ 10+0\} = 10$ e $\text{OPT}[3][1] = \max\{10,\ 5 + \text{OPT}[1][0]\} = \max\{10, 5\} = 10$. Con $B=2$: $\text{OPT}[3][2] = \max\{10,\ 5 + \text{OPT}[1][1]\} = \max\{10, 10\} = 10$ — ora anche $\{1,3\}$ è ammissibile e pareggia.
### LIS quasi monocromatica
> [!question] Domanda d'esame — Almost monochromatic longest increasing subsequence
> **D:** «Sia data una sequenza di $n$ elementi dove l'elemento $i$-esimo ha un valore $v_i$ e un colore $c_i \in \{B, N\}$. Dato un parametro intero $k$, un sottoinsieme $S$ di elementi si dice una **sottosequenza crescente quasi monocromatica** se: (i) i valori degli elementi di $S$ guardati da sinistra a destra formano una sequenza strettamente crescente; (ii) guardando gli elementi di $S$ da sinistra a destra il numero di cambi di colore è al più $k$. Progettate un algoritmo di programmazione dinamica che calcoli la lunghezza della più lunga sottosequenza crescente quasi monocromatica.» *(traccia 08/09/2026 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Problema noto sotto il travestimento: la **LIS**. Il budget $k$ diventa una dimensione.
> Stato: **indice dell'ultimo elemento scelto** × **numero di cambi di colore già usati**. Il colore non serve come terza dimensione, perché è determinato dall'indice.
> Dimensione della tabella $\Theta(nk)$; il costo per cella dipende da come cerchi il predecessore.

> [!info]- Soluzione completa
> **Problema noto sotto il travestimento**: la **LIS** (nota [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]), più un budget di $k$ cambi di colore.
>
> **1 · Sottoproblema.** $\text{OPT}[i][t]$ = lunghezza della più lunga sottosequenza crescente **che termina con l'elemento $i$** e usa **al più $t$** cambi di colore. Sono $n(k+1)$ sottoproblemi.
> Il vincolo «termina con $i$» serve per la stessa ragione della LIS classica: senza, non sapresti con quale valore finisce la sottosequenza e non potresti decidere se $i+1$ la prolunga. Qui serve anche per un secondo motivo — devi conoscere il **colore** dell'ultimo elemento per sapere se il prossimo costa un cambio.
>
> **2 · Ricorrenza.** L'elemento $i$ è l'ultimo; il suo predecessore in $S$ è un $j < i$ con $v_j < v_i$, oppure non esiste (e allora $S = \{i\}$). Il cambio di colore si paga **in $i$** se $c_j \ne c_i$:
> $$\text{OPT}[i][t] = 1 + \max\Bigl(0,\ \max_{\substack{j<i,\ v_j<v_i\\ c_j = c_i}}\text{OPT}[j][t],\ \ \max_{\substack{j<i,\ v_j<v_i\\ c_j \ne c_i}}\text{OPT}[j][t-1]\Bigr)$$
> Il terzo termine esiste solo se $t \ge 1$. Lo $0$ dentro il $\max$ copre il caso «nessun predecessore valido».
>
> **3 · Casi base.** Non ne serve **nessuno di esplicito**, ed è una cosa che vale la pena saper dire: sostituendo $i=1$, entrambi i massimi interni sono su insiemi vuoti, quindi $\text{OPT}[1][t] = 1 + \max(0, -\infty, -\infty) = 1$, che è il valore giusto. L'unica convenzione da dichiarare è $\max\emptyset = -\infty$, più l'assenza del terzo termine quando $t=0$.
> Qui la regola «quante posizioni indietro guarda la ricorrenza, tanti casi base» non si applica alla lettera, perché la ricorrenza non guarda una posizione fissa ma un **insieme** di predecessori — e l'insieme vuoto è già, di per sé, il caso base.
>
> **4 · Ordine e dove si legge la risposta.** $i$ crescente, e per ogni $i$ tutti i $t$ da 0 a $k$: la cella $[i][t]$ guarda solo righe $j<i$. **La risposta è $\max_{i=1..n}\text{OPT}[i][k]$, non $\text{OPT}[n][k]$** — il vincolo «termina con $i$» fissa dove finisce *una* sottosequenza, non la migliore. È l'errore più probabile di tutto l'esercizio.
>
> **5 · Complessità.** $n(k+1)$ celle, ciascuna $O(n)$ perché scorre tutti i $j<i$: **$O(n^2 k)$** tempo, $O(nk)$ spazio. Il costo per cella **non** è $O(1)$, e va detto.
> Osservazione che vale un punto: $k$ si può troncare a $\min(k, n-1)$, perché una sottosequenza lunga $L$ ha al più $L-1$ cambi di colore. Quindi il caso peggiore è $O(n^3)$ — **polinomiale** nella dimensione dell'istanza, non pseudo-polinomiale come il Knapsack.
>
> **Verifica a mano.** $n=3$, $v=[1,2,3]$, $c=[B,N,B]$, $k=1$. Le crescenti sono $\{1,2\}$ (1 cambio), $\{1,3\}$ (0 cambi), $\{2,3\}$ (1), $\{1,2,3\}$ (2 cambi, esclusa da $k=1$): l'ottimo è **2**.
> Tabella: $\text{OPT}[1][\cdot]=1$; $\text{OPT}[2][0]=1$ (il solo predecessore ha colore diverso e il budget è 0), $\text{OPT}[2][1]=\text{OPT}[1][0]+1=2$; $\text{OPT}[3][0]=\text{OPT}[1][0]+1=2$ (via $j=1$, stesso colore), $\text{OPT}[3][1]=\max\{\text{OPT}[1][1]+1,\ \text{OPT}[2][0]+1\}=2$. Massimo $=2$ ✓. Con $k=2$ verrebbe $\text{OPT}[3][2]=\text{OPT}[2][1]+1=3$ ✓.
### Canguro su scacchiera
> [!question] Domanda d'esame — Canguro
> **D:** «Canguro si gioca su una scacchiera di $n$ righe ed $m$ colonne. Controllate un canguro inizialmente in $(1,1)$; l'uscita è in $(n,m)$. Ogni casella $(i,j)$ ospita $f_{i,j}$ fiori. Obiettivo: arrivare alla fine mangiandone il più possibile. Potete muovervi solo verso destra o verso il basso. Su alcune caselle sono appostati dei cacciatori (in tal caso $f_{i,j} = -1$) e finirci significa perdere. Sapete però saltare, sempre verso destra o verso il basso: un salto può essere arbitrariamente lungo, ma nell'intero livello ne avete a disposizione solo $k$ (dovete restare dentro la scacchiera). Progettate un algoritmo di programmazione dinamica che calcoli il massimo numero di fiori che potete mangiare, o dica correttamente che il livello non è risolvibile.» *(traccia 20/07/2026 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Problema noto: il **cammino di peso massimo su griglia** con mosse destra/basso. Il budget $k$ diventa la terza dimensione.
> Stato: **cella $(i,j)$** × **numero di salti già usati**.
> Attenzione a due cose che la traccia mette apposta: le caselle con cacciatore vanno rese **irraggiungibili**, non solo costose; e «arbitrariamente lungo» significa che dalla stessa cella si arriva da un numero non costante di predecessori — il che si riflette sul costo per cella, non sul numero di celle.

> [!info]- Soluzione completa
> **Problema noto**: cammino di valore massimo su griglia con mosse destra/basso, più un budget di $k$ salti.
>
> **Prima di tutto, un'assunzione che la traccia non scrive** e che conviene dichiarare in una riga nel compito. Il testo dice che si perde se «finite in una casella» con un cacciatore, ma **non dice cosa succede alle caselle sorvolate**. L'unica lettura che rende il problema sensato è: sorvolare è innocuo, si muore solo **atterrando**, e i fiori delle caselle sorvolate non si mangiano. Se sorvolare uccidesse, un salto equivarrebbe a una sequenza di mosse normali sulle stesse caselle e il parametro $k$ non servirebbe a nulla. Scrivilo: «assumo che il salto scavalchi le caselle intermedie senza subirne gli effetti, altrimenti i salti sarebbero inutili».
>
> **1 · Sottoproblema.** $\text{OPT}[i][j][s]$ = massimo numero di fiori raccolti su un cammino da $(1,1)$ a $(i,j)$ usando **al più $s$** salti; vale $-\infty$ se $(i,j)$ non è raggiungibile così. Sono $nm(k+1)$ sottoproblemi.
>
> **2 · Ricorrenza.** Se $f_{i,j} = -1$ c'è un cacciatore e la cella è proibita: $\text{OPT}[i][j][s] = -\infty$ per ogni $s$. Altrimenti si guarda **l'ultima mossa** che porta in $(i,j)$, e i casi sono esaustivi perché si arriva solo da sopra o da sinistra, con un passo o con un salto:
> $$\text{OPT}[i][j][s] = f_{i,j} + \max\Bigl(\text{OPT}[i-1][j][s],\ \text{OPT}[i][j-1][s],\ \max_{i'<i-1}\text{OPT}[i'][j][s-1],\ \max_{j'<j-1}\text{OPT}[i][j'][s-1]\Bigr)$$
> I primi due termini sono i passi normali, che non consumano budget; gli altri due sono i salti, che ne consumano uno. Un salto di lunghezza 1 coinciderebbe con un passo normale sprecando budget, quindi non serve considerarlo.
> **Saltare sopra un cacciatore è lecito**: perdi solo se *atterri* su di lui, e la condizione $f_{i,j}=-1$ blocca esattamente l'atterraggio.
>
> **3 · Casi base.** Ne serve **esattamente uno**: $\text{OPT}[1][1][s] = f_{1,1}$ per ogni $s$ (se $f_{1,1}=-1$ il livello è irrisolvibile in partenza). Tutto ciò che esce dalla scacchiera vale $-\infty$, e questo copre da solo prima riga e prima colonna.
> **Qui il caso base non esce dalla ricorrenza**, a differenza della LIS: sostituendo $(1,1)$ tutti e quattro i rami sono fuori scacchiera e la formula darebbe $-\infty$, che è sbagliato. Il motivo è istruttivo — qui il massimo è su predecessori *obbligatori* (il cammino deve pur venire da qualche parte), mentre nella LIS il massimo vuoto rappresentava legittimamente la sottosequenza di un elemento solo. **Il caso base va scritto esplicitamente quando l'insieme vuoto dei predecessori non ha un'interpretazione valida.**
>
> **4 · Ordine e dove si legge la risposta.** $s$ crescente da 0 a $k$ (i salti pescano dal livello $s-1$); dentro ogni livello, $i$ e $j$ crescenti. La risposta è $\text{OPT}[n][m][k]$; **se vale $-\infty$, il livello non è risolvibile** — è la seconda cosa che la traccia chiede e va detta esplicitamente.
>
> **5 · Complessità.** $nm(k+1)$ celle. Il costo per cella **non è $O(1)$**: i due massimi sui salti scorrono fino a $O(n)$ e $O(m)$ predecessori, quindi $O(n+m)$ a cella, per un totale di $O(nmk(n+m))$.
> **Ottimizzazione a $\Theta(nmk)$**: per ogni livello $s-1$ si precalcolano i massimi di prefisso lungo ogni colonna e ogni riga; allora $\max_{i'<i-1}\text{OPT}[i'][j][s-1]$ è una singola lettura, e ogni cella torna $O(1)$.
>
> **Verifica a mano**, su un'istanza che mette alla prova proprio il salto. Scacchiera $2\times3$, $k=1$, con un cacciatore in $(1,2)$:
> $$f = \begin{pmatrix} 0 & -1 & 5\\ 2 & 0 & 1\end{pmatrix}$$
> *Livello $q=0$*: $\text{OPT}[1][1]=0$; $\text{OPT}[1][2]=-\infty$ (cacciatore); $\text{OPT}[1][3]=-\infty$ (ci si arriverebbe solo passando dal cacciatore); $\text{OPT}[2][1]=2$; $\text{OPT}[2][2]=2$; $\text{OPT}[2][3]=3$.
> *Livello $q=1$*: $\text{OPT}[1][3][1] = 5 + \text{OPT}[1][1][0] = 5$ — è il salto che **scavalca il cacciatore**; poi $\text{OPT}[2][3][1] = 1 + \max\{\text{OPT}[1][3][1]{=}5,\ \text{OPT}[2][2][1]{=}2,\ \ldots\} = \mathbf{6}$.
> A mano: senza salti l'unico cammino vivo è $0+2+0+1=3$; con un salto si fa $(1,1)\to(1,3)\to(2,3)$, cioè $0+5+1=6$ ✓.
### Dominating set con sconti
> [!question] Domanda d'esame — Minimum dominating set with discounts
> **D:** «Sia $G$ un grafo a cammino di $n$ nodi dove a ogni nodo $v_i$ è associato un costo non negativo $c_i$. Un **dominating set** è un sottoinsieme di nodi $S$ tale che ogni nodo che non appartiene a $S$ è dominato, ovvero adiacente ad almeno un nodo di $S$. Il costo di $S$ è $\sum_{v_i \in S} c_i$. Si consideri la variante in cui per alcuni nodi di $S$ si riceve uno sconto del 10%: se un nodo $v_i \in S$ fa parte in $S$ di almeno un blocco contiguo di nodi lungo almeno 3, il costo di $v_i$ è $0{,}9\,c_i$. Progettate un algoritmo di programmazione dinamica che calcoli il dominating set il cui costo scontato è minimo.» *(traccia 30/06/2026 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Problema noto: il **dominating set su cammino**, che è il duale del WIS che hai studiato.
> Lo sconto dipende dalla **lunghezza del blocco contiguo corrente** di nodi presi: quella lunghezza va nello stato, ma **satura a 3** — oltre non serve distinguere.
> Stato: **posizione** × **lunghezza del blocco contiguo corrente (0, 1, 2, ≥3)** × quello che serve a garantire la dominanza del nodo precedente.

> [!info]- Soluzione completa
> È il più difficile dei sette. Il punto che lo rende tale è che **lo sconto è retroattivo**: quando un blocco raggiunge lunghezza 3, anche i due nodi già pagati a prezzo pieno diventano scontati.
>
> **1 · Sottoproblema.** Si scorre il cammino da sinistra a destra. $\text{OPT}[i][s]$ = costo scontato minimo di una scelta su $\{v_1,\ldots,v_i\}$ tale che **tutti i nodi $v_1,\ldots,v_{i-1}$ sono dominati** e lo stato di $v_i$ è $s$, con $s$ fra **cinque** valori:
> - $\texttt{IN1}$, $\texttt{IN2}$, $\texttt{IN3+}$ — $v_i \in S$, e il blocco contiguo di $S$ che termina in $i$ è lungo rispettivamente 1, 2, oppure $\ge 3$;
> - $\texttt{OD}$ — $v_i \notin S$ ed è **già dominato** (per forza da $v_{i-1} \in S$: $v_{i+1}$ non è ancora deciso);
> - $\texttt{OU}$ — $v_i \notin S$ e **non ancora dominato**: dovrà pensarci $v_{i+1}$.
>
> Sono $5n$ sottoproblemi. Due osservazioni che valgono punti: i nodi **in $S$ non hanno bisogno di essere dominati** (la traccia dice «ogni nodo che *non* appartiene ad $S$ è dominato»), il che dimezza i casi; e servono **tre** stati IN, non due, perché solo da $\texttt{IN2}$ può scattare lo sconto al passo successivo — da 3 in poi non c'è altra retroattività, quindi lo stato ricorda $\min(\text{lunghezza},\,3)$.
>
> **2 · Ricorrenza.** Transizioni da $i$ a $i+1$, con $\gamma = c_{i+1}$.
> *Da $\texttt{IN1}/\texttt{IN2}/\texttt{IN3+}$* (cioè $v_i \in S$):
> - $v_{i+1} \in S$: $\texttt{IN1}\to\texttt{IN2}$ costa $+\gamma$; $\texttt{IN2}\to\texttt{IN3+}$ costa $+\,0{,}9\gamma - 0{,}1(c_i + c_{i-1})$ — **è qui che scatta il rimborso** sui due nodi già pagati pieni; $\texttt{IN3+}\to\texttt{IN3+}$ costa $+\,0{,}9\gamma$;
> - $v_{i+1} \notin S$: va in $\texttt{OD}$ a costo $0$, perché $v_i \in S$ lo domina.
>
> *Da $\texttt{OD}$*: $v_{i+1}\in S \to \texttt{IN1}$, costo $+\gamma$; $v_{i+1}\notin S \to \texttt{OU}$, costo $0$.
> *Da $\texttt{OU}$*: $v_{i+1}\in S \to \texttt{IN1}$, costo $+\gamma$, ed è **obbligatorio**; $v_{i+1}\notin S$ è **vietato**, perché $v_i$ non verrebbe mai dominato.
>
> I casi sono esaustivi: per ogni stato di $v_i$ le decisioni su $v_{i+1}$ sono solo «dentro» o «fuori», ed entrambe sono coperte (con «fuori» proibito da $\texttt{OU}$).
>
> **3 · Casi base.** Una sola colonna, $i=1$: $\texttt{IN1} = c_1$, $\texttt{OU} = 0$, e $\texttt{IN2} = \texttt{IN3+} = \texttt{OD} = +\infty$ (configurazioni impossibili al primo nodo: $v_1$ non può stare in un blocco lungo 2, né essere già dominato da un $v_0$ che non esiste).
> **Attenzione a una trappola**: la transizione $\texttt{IN2}\to\texttt{IN3+}$ legge $c_{i-1}$ e $c_i$, cioè guarda indietro di due — ma quelli sono **dati di input**, non celle della tabella. La dipendenza *fra celle* resta di un passo solo, quindi **basta una colonna di base**, non due. Scrivere «servono due colonne» è l'errore facile.
>
> **4 · Ordine e dove si legge la risposta.** $i$ crescente da 1 a $n$, i cinque stati in qualunque ordine.
> $$\text{risposta} = \min\bigl(\text{OPT}[n][\texttt{IN1}],\ \text{OPT}[n][\texttt{IN2}],\ \text{OPT}[n][\texttt{IN3+}],\ \text{OPT}[n][\texttt{OD}]\bigr)$$
> **$\texttt{OU}$ va escluso dal minimo finale**: se $v_n \notin S$ e non è dominato, non c'è nessun $v_{n+1}$ che possa salvarlo. È la variante di fine tabella della trappola solita — non «massimo su una riga» ma «solo un sottoinsieme degli stati finali è ammissibile».
>
> **5 · Complessità.** $5n$ celle, ciascuna $O(1)$ (ogni stato ha al più tre candidati entranti): **$\Theta(n)$** tempo e spazio, riducibile a $\Theta(1)$ spazio se serve solo il valore.
>
> **Verifica a mano.** $n=4$, $c=[1,2,3,4]$.
>
> | $i$ | IN1 | IN2 | IN3+ | OD | OU |
> |---|---|---|---|---|---|
> | 1 | 1 | ∞ | ∞ | ∞ | 0 |
> | 2 | 2 | 3 | ∞ | 1 | ∞ |
> | 3 | 4 | 5 | 5,4 | 2 | 1 |
> | 4 | 5 | 8 | 8,1 | **4** | 2 |
>
> Risposta $=\min(5,\ 8,\ 8{,}1,\ 4) = \mathbf{4}$, realizzata da $S=\{v_1,v_3\}$. Enumerando tutti e 16 i sottoinsiemi si trova lo stesso minimo ✓, e lo sconto torna: $\texttt{IN3+}[3] = 5{,}4 = 0{,}9\cdot(1+2+3)$ ✓.
> **Il controllo che conta**: $\texttt{OU}[4] = 2$ corrisponde a $S=\{v_1\}$, che **non domina $v_4$**. Se lo includessi nel minimo finale risponderesti 2 invece di 4 — più del doppio di errore.
>
> **Nota pratica.** Lo sconto rende i costi non interi. Se dà fastidio, si moltiplica tutto per 10 e si lavora con $9c_i$ e $10c_i$: la soluzione ottima non cambia.
### Colorazione di case con budget
> [!question] Domanda d'esame — Colorazione di case con vernice rossa limitata
> **D:** «In una via ci sono $n$ case, numerate da 1 a $n$, che devi ridipingere. I colori a disposizione sono tre: rosso, verde e blu. Per ogni casa $i$ e colore $x$ conosci il costo $c(i,x)$ che sosterresti se colorassi la casa di quel colore. Hai però dei vincoli: non puoi colorare case adiacenti con lo stesso colore, e non hai molta vernice rossa — puoi colorare di rosso al più $k$ case. Progettate un algoritmo di programmazione dinamica che calcoli il costo minimo per colorare le case. Si discuta la complessità temporale della soluzione proposta.» *(traccia 23/09/2025 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Stato: **indice della casa** × **colore assegnato a quella casa** × **numero di case rosse già usate**.
> Il colore serve nello stato perché il vincolo è **locale fra adiacenti**: senza di esso la ricorrenza non si chiude. I colori sono 3, quindi quella dimensione è una costante.

> [!info]- Soluzione completa
> **Problema noto**: House Coloring, che sta sulle slide 33-34 e nella nota [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]. Qui si aggiunge il budget sul rosso. È la prova concreta che il pattern «problema già visto a lezione + un budget» esce davvero allo scritto.
>
> **1 · Sottoproblema.** $\text{OPT}[i][x][r]$ = costo minimo per colorare le case $1..i$, con la casa $i$ del colore $x \in \{R,G,B\}$ e **al più $r$** case rosse fra le prime $i$. Sono $3n(k+1)$ sottoproblemi.
> Il colore della casa $i$ deve stare nello stato perché il vincolo è **locale fra adiacenti**: senza, non potresti vietare alla casa $i+1$ di ripetere il colore. Il budget $r$ è la seconda dimensione.
>
> **2 · Ricorrenza.** La casa $i$ ha colore $x$; la casa $i-1$ può avere qualunque colore $y \ne x$, e questi casi sono esaustivi:
> $$\text{OPT}[i][x][r] = c(i,x) + \min_{y \ne x}\ \text{OPT}[i-1][y]\bigl[r - [\,x = R\,]\bigr]$$
> dove $[\,x=R\,]$ vale 1 se $x$ è il rosso e 0 altrimenti: **dipingere di rosso consuma una unità di budget, gli altri due colori no**.
>
> **3 · Casi base.** $\text{OPT}[1][R][r] = c(1,R)$ per $r \ge 1$ e $+\infty$ per $r=0$ (senza budget non puoi usare il rosso); $\text{OPT}[1][G][r] = c(1,G)$ e $\text{OPT}[1][B][r] = c(1,B)$ per ogni $r \ge 0$.
>
> **4 · Ordine e dove si legge la risposta.** $i$ crescente, e per ogni $i$ tutte le coppie $(x,r)$. La risposta è $\min_{x}\text{OPT}[n][x][k]$: serve il minimo **sui colori** perché lo stato fissa il colore dell'ultima casa, ma **non** serve un minimo su $r$, perché lo stato dice «al più $r$» e quindi $\text{OPT}[n][x][k]$ contiene già le soluzioni che usano meno rossi.
> Se avessi definito lo stato con «**esattamente** $r$ rosse», la ricorrenza sarebbe identica ma la risposta diventerebbe $\min_x \min_{r \le k}\text{OPT}[n][x][r]$. Le due versioni sono entrambe corrette: quello che non si può fare è **mescolarle**, ed è lì che si sbaglia.
> Il caso che smaschera la confusione è $k > n$. Con «esattamente», se $n=2$ e $k=5$ la fetta $r=5$ è tutta $+\infty$, e chi legge solo quella risponde «impossibile» a un'istanza perfettamente risolvibile. Con «al più» il problema non si pone. Se hai dubbi sotto esame, **usa «al più»**: è la formulazione che perdona.
>
> **5 · Complessità.** $3n(k+1)$ celle, ciascuna $O(1)$ (un minimo fra due alternative, perché i colori diversi da $x$ sono due): **$\Theta(nk)$** tempo, $\Theta(nk)$ spazio — riducibile a $\Theta(k)$ tenendo due righe.
> **Osservazione che chiude il punto 5 in una riga**: si può sempre troncare a $k' = \min(k, n)$, perché più di $n$ case rosse non si dipingono. Quindi il caso peggiore è $\Theta(n^2)$, **polinomiale nella dimensione dell'istanza**. È il contrasto esatto con il Knapsack, dove $W$ *non* è limitato da $n$ e la complessità resta pseudo-polinomiale: qui il secondo indice è limitato dal numero di oggetti, lì no.
> Generalizzando a $q$ colori si avrebbe $\Theta(nkq)$ con il trucco dei due minimi (vedi la Regola sui $k$ stati nella nota 05).
>
> **Verifica a mano.** $n=3$ case, costo del rosso $=1$ ovunque, costo di verde e blu $=10$ ovunque. Il rosso conviene sempre, quindi il budget morde.
> Con $k=2$: la colorazione $R,G,R$ costa $1+10+1 = \mathbf{12}$ ed è l'ottimo (due rossi non adiacenti sono il massimo possibile su tre case).
> Con $k=1$: un solo rosso, quindi le altre due case costano 10 ciascuna — **21**, dovunque si metta il rosso. La tabella lo conferma: $\text{OPT}[3][R][1] = 1 + \min\{\text{OPT}[2][G][0],\ \text{OPT}[2][B][0]\} = 1 + 20 = 21$, e analogamente per gli altri due colori.
> Se la tua tabella dà 12 anche con $k=1$, hai dimenticato di decrementare il budget nel ramo del rosso.
### Job su due macchine
> [!question] Domanda d'esame — Job su due macchine con costi fissi
> **D:** «Devi assegnare $n$ job, numerati da 1 a $n$, a due macchine minimizzando il costo totale. Ogni job può essere eseguito da entrambe, ma le politiche di costo sono diverse. La macchina $A$ non ha costi fissi ed esegue il job $i$ a costo $a_i$. La macchina $B$ ha costi per job più bassi ($b_i \leq a_i$ sempre) ma ha costi fissi che dipendono dal **numero totale** di job assegnati: se ne assegni $k$ in totale a $B$, paghi in più un costo $c_k$, con $c_1 \leq c_2 \leq \cdots \leq c_n$. Progettate un algoritmo di programmazione dinamica che calcoli il costo minimo a cui è possibile eseguire tutti i job. Si discuta la complessità temporale.» *(traccia 09/09/2025 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> La difficoltà è che $c_k$ dipende dal **totale** di job su $B$, che non si conosce finché non hai finito: è un costo **globale**, non locale, quindi non si può sommare strada facendo.
> Stato: **indice del job** × **quanti job hai già assegnato a $B$**. Il termine $c_k$ si aggiunge **una volta sola, alla fine**, quando $k$ è noto.

> [!info]- Soluzione completa
> **La difficoltà è dove mettere il costo fisso.** Il costo $c_k$ dipende dal numero **totale** di job assegnati a $B$, che si conosce solo alla fine: non si può sommare dentro la ricorrenza, altrimenti lo pagheresti più volte o a un valore sbagliato.
>
> **1 · Sottoproblema.** $\text{OPT}[i][h]$ = costo minimo **dei soli costi per job** (senza il costo fisso) per assegnare i primi $i$ job, avendone messi **esattamente $h$** sulla macchina $B$. Sono $(n+1)^2$ sottoproblemi.
>
> **2 · Ricorrenza.** Il job $i$ va su $A$ oppure su $B$, e i due casi sono esaustivi:
> $$\text{OPT}[i][h] = \min\{\underbrace{\text{OPT}[i-1][h] + a_i}_{\text{job } i \text{ su } A},\ \ \underbrace{\text{OPT}[i-1][h-1] + b_i}_{\text{job } i \text{ su } B}\}$$
> Il secondo ramo esiste solo se $h \ge 1$.
>
> **3 · Casi base.** $\text{OPT}[0][0] = 0$ (nessun job, nessun costo) e $\text{OPT}[0][h] = +\infty$ per $h \ge 1$ (non puoi aver messo job su $B$ senza avere job).
>
> **4 · Ordine e dove si legge la risposta.** $i$ crescente da 1 a $n$, e per ogni $i$ tutti gli $h$ da 0 a $i$. **Il costo fisso si aggiunge solo alla fine**, ed è qui che si prende o si perde il punto:
> $$\text{risposta} = \min_{h = 0, \ldots, n}\ \bigl(\text{OPT}[n][h] + c_h\bigr), \qquad c_0 = 0$$
> Non è una singola cella: è un minimo su tutta l'ultima riga, perché non sai in anticipo quanti job converrà mettere su $B$ — più ne metti, più risparmi sui costi per job ma più paghi di fisso.
>
> **5 · Complessità.** $(n+1)^2$ celle, $O(1)$ ciascuna, più $O(n)$ per il minimo finale: **$\Theta(n^2)$** tempo e spazio (riducibile a $\Theta(n)$ spazio tenendo due righe).
>
> **Verifica a mano, con la trappola esibita.** $n=3$, $a=[10,10,10]$, $b=[1,5,9]$, $c=[2,3,20]$ e $c_0 = 0$.
>
> | $i$ | $h=0$ | $h=1$ | $h=2$ | $h=3$ |
> |---|---|---|---|---|
> | 0 | 0 | ∞ | ∞ | ∞ |
> | 1 | 10 | 1 | ∞ | ∞ |
> | 2 | 20 | 11 | 6 | ∞ |
> | 3 | 30 | 21 | 16 | **15** |
>
> Lettura finale: $30+0=30$, $21+2=23$, $16+3=\mathbf{19}$, $15+20=35$. Risposta **19**, con i job 1 e 2 sulla macchina $B$.
> **Qui si vede perché la trappola è cattiva**: $\text{OPT}[3][3] = 15$ è la cella **più piccola** dell'ultima riga, ma una volta aggiunto $c_3 = 20$ diventa l'assegnazione **peggiore di tutte**. Chi legge $\text{OPT}[n][n]$, o il minimo nudo della riga senza sommare $c_h$, sbaglia di 16 su 19.
> E non si può scandire $h$ fermandosi al primo peggioramento: la parte variabile è non crescente in $h$, il costo fisso è non decrescente, ma **nessuna delle due è convessa**, quindi il totale non è monotono né unimodale. Vanno provati tutti gli $n+1$ valori.
>
> **Controllo indipendente.** Siccome $b_i \le a_i$ sempre, per un $h$ fissato conviene mettere su $B$ gli $h$ job con **risparmio $a_i - b_i$ più grande**: quindi $\text{OPT}[n][h] = \sum_i a_i - (\text{somma degli } h \text{ risparmi maggiori})$. Sull'istanza sopra: $\sum a = 30$ e gli scarti sono $[9,5,1]$, da cui $30 - \{0, 9, 14, 15\} = \{30, 21, 16, 15\}$, che è esattamente l'ultima riga ✓.
> Attenzione però: questa scorciatoia risolve il problema in $O(n\log n)$, ma è un **greedy**, e la traccia chiede programmazione dinamica. Usala per verificarti, e semmai citala in due righe alla fine — non al posto della DP.
>
> **Ambiguità da dichiarare.** La traccia definisce $c_1,\ldots,c_n$ ma non $c_0$: non dice cosa si paga se la macchina $B$ non viene usata affatto. Assumo $c_0 = 0$, che è l'unica lettura sensata. Se invece $B$ dovesse essere usata per forza, basta far partire il minimo finale da $h=1$.
>
> **Due ipotesi della traccia che la ricorrenza non usa**: $b_i \le a_i$ e $c_1 \le c_2 \le \cdots \le c_n$. Non sono il sintomo di uno stato mal definito — la DP è corretta anche senza — ma sono ciò che rende il problema economicamente sensato e ciò che abilita il controllo greedy qui sopra. Saperlo dire è un punto in più, non in meno.
### Tube Invaders
> [!question] Domanda d'esame — Tube Invaders
> **D:** «Controllate un'astronave che avanza dentro un tubo diviso in $n$ segmenti, corrispondenti alle $n$ battaglie numerate da 1 a $n$. Nella battaglia $i$ troverete una flotta di $a_i$ alieni. Avete a disposizione un'arma che, quando non la usate, accumula energia. L'energia rappresenta il massimo numero di alieni che potete distruggere quando decidete di usarla in battaglia. Subito dopo averla usata, l'energia torna a 1. Anche all'inizio, nella prima battaglia, l'energia è 1; l'energia **raddoppia** a ogni battaglia in cui non la usate. Progettate un algoritmo di programmazione dinamica che calcoli il massimo numero di alieni che potete distruggere. Si discuta la complessità temporale.» *(traccia 18/07/2025 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> L'energia non è una variabile libera: vale $2^t$ dove $t$ è il numero di battaglie consecutive in cui **non** hai sparato. Quindi nello stato non va l'energia, va $t$ — ed è limitato, perché oltre un certo punto l'energia supera qualunque $a_i$.
> Stato: **indice della battaglia** × **numero di battaglie consecutive saltate**.
> In battaglia $i$ distruggi $\min\{a_i,\ 2^t\}$ alieni se spari, $0$ se passi.

> [!info]- Soluzione completa
> **La trappola è lo stato.** L'istinto dice «metto l'energia nello stato», ma l'energia raddoppia e arriva a $2^{n-1}$: la tabella diventerebbe **esponenziale**. L'energia però è sempre una potenza di 2, e l'esponente è il numero di battaglie consecutive saltate — un numero fra 0 e $n$. **Si indicizza sull'esponente, non sull'energia.**
>
> **1 · Sottoproblema.** $\text{OPT}[i][t]$ = massimo numero di alieni distruggibili nelle battaglie $i, i+1, \ldots, n$, sapendo che all'inizio della battaglia $i$ l'arma ha energia $2^t$ (cioè sono state saltate $t$ battaglie consecutive prima di $i$). Sono $n(n+1)$ sottoproblemi.
>
> **2 · Ricorrenza.** Nella battaglia $i$ si usa l'arma oppure no, e i casi sono esaustivi:
> $$\text{OPT}[i][t] = \max\{\underbrace{\min(a_i,\ 2^t) + \text{OPT}[i+1][0]}_{\text{uso l'arma}},\ \ \underbrace{\text{OPT}[i+1][t+1]}_{\text{non la uso}}\}$$
> Se uso l'arma distruggo $\min(a_i, 2^t)$ alieni — non più di quanti ce ne siano, non più di quanta energia ho — e subito dopo l'energia torna a 1, cioè l'esponente si azzera. Se non la uso non distruggo nulla ma l'esponente cresce di 1.
>
> **3 · Casi base.** $\text{OPT}[n+1][t] = 0$ **per ogni $t$**: finite le battaglie non si distrugge più niente. Il «per ogni $t$» non è pignoleria — il ramo «non uso l'arma» indicizza $t+1$, quindi alla battaglia $n$ con l'esponente massimo la formula chiede una cella della riga base con $t$ appena fuori dal campo dichiarato. O si dichiara la riga base per tutti i $t$, o si tronca l'esponente come nel raffinamento qui sotto: entrambe vanno bene, dimenticarsene no.
>
> **4 · Ordine e dove si legge la risposta.** $i$ **decrescente** da $n$ a 1 — la ricorrenza guarda avanti, a $i+1$, quindi la tabella si riempie dal fondo. La risposta è $\text{OPT}[1][0]$: alla prima battaglia l'energia è $1 = 2^0$, come dice la traccia.
>
> **5 · Complessità.** $n(n+1)$ celle, $O(1)$ ciascuna: **$\Theta(n^2)$** tempo e spazio.
> **Raffinamento.** Una volta che $2^t \ge \max_i a_i$, raddoppiare ancora non serve a niente perché il $\min$ è già saturo: si può troncare $t$ a $\lceil\log_2(\max_i a_i)\rceil$, ottenendo $\Theta(n\log A)$ con $A = \max_i a_i$. Vale la pena dirlo, ma il $\Theta(n^2)$ è già una risposta piena.
>
> **Formulazione alternativa, altrettanto corretta** — e il confronto fra le due è la parte più istruttiva dell'esercizio.
> $\text{ALT}[i]$ = massimo numero di alieni distruggibili nelle battaglie $1..i$ **sapendo che l'arma viene usata nella battaglia $i$**, con $\text{ALT}[0] = 0$ che rappresenta una battaglia fittizia in cui l'arma è stata usata (è così che si codifica «all'inizio l'energia è 1»). L'unica cosa da decidere è **quando è stato l'uso precedente**:
> $$\text{ALT}[i] = \max_{0 \le j \le i-1}\Bigl(\text{ALT}[j] + \min\bigl(a_i,\ 2^{\,i-j-1}\bigr)\Bigr)$$
> perché se l'ultimo uso prima di $i$ è stato in $j$, l'energia si è raddoppiata $i-j-1$ volte. La risposta è $\max_i \text{ALT}[i]$. Complessità: $n+1$ celle da $O(n)$ ciascuna, di nuovo $\Theta(n^2)$.
>
> **Il contrasto da portarsi a casa.** Le due formulazioni danno lo stesso risultato, ma il **punto 4 cambia**:
> - stato **completo** («energia $2^t$ all'inizio di $i$») $\Rightarrow$ la risposta è **una cella sola**, $\text{OPT}[1][0]$;
> - stato **vincolato** («l'ultimo uso è in $i$») $\Rightarrow$ la risposta è un **massimo sulla riga**.
>
> Non è che una sia giusta e l'altra sbagliata: è che **dove si legge la risposta dipende da come hai definito il sottoproblema**. Questo è il posto migliore di tutta la palestra per vederlo.
>
> **E c'è una seconda lezione, più sottile.** La traccia impone due condizioni al contorno: «alla prima battaglia l'energia è 1» e «dopo la battaglia $n$ non c'è più niente». Guarda dove finiscono:
> - nella versione con l'energia nello stato, il caso base $\text{OPT}[n+1][t]=0$ codifica la **seconda**, e la prima sta nella **lettura finale** — è lo $0$ di $\text{OPT}[1][0]$ a dire «energia $2^0$»;
> - nella versione $\text{ALT}$ è l'opposto: il caso base $\text{ALT}[0]=0$ con la convenzione $j=0$ codifica la **prima**, e la lettura è un massimo.
>
> **La condizione iniziale deve stare da qualche parte**, e a seconda di come definisci lo stato cade nel caso base oppure nella lettura finale. Se in un compito non riesci a collocarla né nell'uno né nell'altra, non è che l'hai dimenticata: è lo stato a essere definito male.
> *(Curiosità: nella versione $\text{ALT}$ si può dimostrare che $\text{ALT}[n]$ coincide già col massimo, perché sparare nell'ultima battaglia non ha costo opportunità. Ma scrivi comunque il massimo sulla riga: costa $O(n)$, è corretto senza dimostrare nulla, e chi scrive $\text{ALT}[n]$ senza giustificarlo ha scritto la cosa giusta per il motivo sbagliato.)*
>
> **Verifica a mano.** $n=3$, $a=[1,1,8]$. Saltando le prime due battaglie si arriva alla terza con energia $4$ e si distruggono $\min(8,4)=4$ alieni; nessuna altra strategia fa meglio (usarle tutte dà $1+1+1=3$).
> Tabella: $\text{OPT}[4][\cdot]=0$; $\text{OPT}[3][0]=1$, $\text{OPT}[3][1]=2$, $\text{OPT}[3][2]=4$; $\text{OPT}[2][0]=\max\{1+1,\ 2\}=2$, $\text{OPT}[2][1]=\max\{1+1,\ 4\}=4$; $\text{OPT}[1][0]=\max\{1+2,\ 4\}=\mathbf{4}$ ✓.
### Linea della metro D
> [!question] Domanda d'esame — La linea della metro D
> **D:** «Dovete scavare nel minor tempo possibile un tunnel che attraversi una mole di terra rappresentata da una matrice di $n$ righe e $m$ colonne. Partite dalla casella $(1,1)$ e dovete arrivare in una **qualsiasi** casella della colonna $m$. Da $(i,j)$ lo scavatore può liberare la casella $(i, j+1)$ oppure $(i+1, j)$; liberare una casella richiede esattamente un'ora. Ogni volta che dissotterrate un reperto dovete però aspettare la catalogazione: un'**anfora** (A) richiede 3 ore, una **bifora** (B) ne richiede 10, e in una casella con **colonna dorica** (C) i lavori vanno interrotti. Un macchinario vi ha detto in anticipo cosa c'è in ogni casella. Progettate un algoritmo di programmazione dinamica che calcoli il tunnel migliore da scavare e il tempo necessario.» *(traccia 02/02/2026 · Es. 3)*

> [!info]- Indizio — solo il passo 1, se sei bloccato in partenza
> Problema noto: **cammino di costo minimo su griglia** con mosse destra/basso — lo stesso telaio del Canguro, ma **senza** dimensione di budget: qui non c'è nessun $k$.
> Stato: la sola **cella $(i,j)$**, con valore = tempo minimo per arrivarci.
> Le due cose che la traccia mette alla prova: le caselle con colonna dorica sono **proibite** (come i cacciatori del Canguro), e la destinazione non è una cella sola ma **un'intera colonna**, quindi la risposta è un minimo su $m$-esima colonna e non una singola cella.

> [!info]- Soluzione completa
> **Problema noto**: cammino di costo minimo su griglia con mosse destra/basso. Qui **non c'è nessun budget**: la tabella ha due soli indici. È il più semplice dei sette, buono come riscaldamento.
>
> **1 · Sottoproblema.** $\text{OPT}[i][j]$ = tempo minimo per scavare un tunnel da $(1,1)$ fino alla casella $(i,j)$, oppure $+\infty$ se $(i,j)$ non è raggiungibile. Sono $nm$ sottoproblemi.
>
> **2 · Ricorrenza.** Definiamo il costo di liberare una casella:
> $$\text{cost}(i,j) = \begin{cases} 1 & \text{casella vuota}\\ 1+3 = 4 & \text{anfora}\\ 1+10 = 11 & \text{bifora}\\ +\infty & \text{colonna dorica}\end{cases}$$
> In $(i,j)$ ci si arriva solo da sopra o da sinistra, e i due casi sono esaustivi:
> $$\text{OPT}[i][j] = \text{cost}(i,j) + \min\{\text{OPT}[i-1][j],\ \text{OPT}[i][j-1]\}$$
> La colonna dorica non va gestita a parte: il $+\infty$ la rende automaticamente non attraversabile.
>
> **3 · Casi base.** $\text{OPT}[1][1] = 0$: in $(1,1)$ ci sei già, non devi liberarla. Tutto ciò che sta fuori dalla griglia vale $+\infty$, così la prima riga e la prima colonna si riempiono da sole senza casi speciali.
>
> **4 · Ordine e dove si legge la risposta.** $i$ e $j$ crescenti. **La risposta è $\min_{i=1..n}\text{OPT}[i][m]$, non $\text{OPT}[n][m]$**: la traccia dice «arrivare in una **qualsiasi** casella della colonna $m$». È la trappola dell'esercizio.
> La traccia chiede anche **quale** tunnel, non solo il tempo: si tiene un puntatore $\text{prev}[i][j]$ al predecessore che ha realizzato il minimo e si risale dalla cella vincente fino a $(1,1)$.
>
> **5 · Complessità.** $nm$ celle, $O(1)$ ciascuna: **$\Theta(nm)$** tempo e spazio, più $O(n+m)$ per la ricostruzione.
>
> **Verifica a mano.** Griglia $2\times3$, con una bifora in $(1,2)$ e un'anfora in $(2,1)$, il resto vuoto:
> $$\begin{pmatrix} \cdot & B & \cdot \\ A & \cdot & \cdot \end{pmatrix} \qquad \text{cost} = \begin{pmatrix} 0 & 11 & 1 \\ 4 & 1 & 1 \end{pmatrix}$$
> Tabella: $\text{OPT}[1][1]=0$; $\text{OPT}[1][2]=11$; $\text{OPT}[1][3]=1+11=12$; $\text{OPT}[2][1]=4+0=4$; $\text{OPT}[2][2]=1+\min\{11,4\}=5$; $\text{OPT}[2][3]=1+\min\{12,5\}=6$.
> Risposta $=\min\{\text{OPT}[1][3],\ \text{OPT}[2][3]\} = \min\{12, 6\} = \mathbf{6}$, con il tunnel $(1,1)\to(2,1)\to(2,2)\to(2,3)$: conviene scendere subito e pagare l'anfora (3 ore) piuttosto che attraversare la bifora (10 ore).
> **Perturbazione che esibisce la trappola.** Metti una bifora anche in $(2,3)$: allora $\text{OPT}[2][3] = 11 + \min\{12,\,5\} = 16$, mentre $\text{OPT}[1][3]$ resta 12. La risposta diventa **12, in riga 1**, e chi avesse letto $\text{OPT}[n][m]$ risponderebbe 16. Tienitelo in tasca: è la stessa trappola della LIS in un'altra veste.
>
> **Nota sulla lettura della traccia.** Ho assunto che $(1,1)$ sia la posizione di partenza e quindi non vada liberata. Se invece la si considerasse da scavare, basta porre $\text{OPT}[1][1] = \text{cost}(1,1)$: cambia solo il caso base, non il resto.
## Le cinque tracce senza svolgimento
Le altre dodici hanno già uno svolgimento esteso nella cartella `Esercizio 3 - Programmazione Dinamica/`. Qui ci sono le cinque che mancavano, in forma compatta: sottoproblema, casi base, ricorrenza, risposta, costo e la trappola specifica.
### 22/06/2022 · Pila di monete — F1
Pila di $n$ monete, la $i$-esima dall'alto vale $v_i$. **PrimaDiTre** (serve pila $\ge 3$): intaschi la moneta in cima e butti le due successive. **SecondaDiDue** (serve pila $\ge 2$): butti la prima e intaschi la successiva. Massimizzare il guadagno.
**Sottoproblema.** $\text{OPT}(i)$ $=$ massimo guadagno ottenibile quando la pila residua è $v_i, v_{i+1}, \ldots, v_n$, con $v_i$ in cima. Sono $n$ sottoproblemi più tre sentinelle.
**Casi base.** $\text{OPT}(i)=0$ per ogni $i>n$. Il caso «una sola moneta» ($i=n$) esce da solo: nessuna delle due guardie è soddisfatta, quindi resta il ramo «mi fermo».
**Ricorrenza.** Dalla cima $i$ ci sono tre alternative, esaustive e mutuamente esclusive:
$$\text{OPT}(i) = \max \begin{cases} 0 & \text{mi fermo} \\[2pt] v_i + \text{OPT}(i+3) & \text{PrimaDiTre, se } i \le n-2 \\[2pt] v_{i+1} + \text{OPT}(i+2) & \text{SecondaDiDue, se } i \le n-1 \end{cases}$$
**Risposta.** $\text{OPT}(1)$. **Ordine.** $i$ decrescente da $n$ a $1$. **Costo.** $\Theta(n)$ celle $\times$ $O(1)$ $=\Theta(n)$ tempo, $O(1)$ spazio con una finestra di quattro celle.

```pseudo
\begin{algorithm}
\caption{PilaMonete($v[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(n+1) \gets 0$; $\text{OPT}(n+2) \gets 0$; $\text{OPT}(n+3) \gets 0$
\For{$i \gets n$ downto $1$}
  \State $m \gets 0$ \Comment{mi fermo}
  \If{$i \leq n-2$}
    \State $m \gets \max(m,\; v[i] + \text{OPT}(i+3))$ \Comment{PrimaDiTre}
  \EndIf
  \If{$i \leq n-1$}
    \State $m \gets \max(m,\; v[i+1] + \text{OPT}(i+2))$ \Comment{SecondaDiDue}
  \EndIf
  \State $\text{OPT}(i) \gets m$
\EndFor
\State \Return $\text{OPT}(1)$
\end{algorithmic}
\end{algorithm}
```

> [!warning] SecondaDiDue intasca $v_{i+1}$, non $v_i$
> L'indice della mossa e l'indice del valore incassato non coincidono. È l'unico punto in cui questo esercizio è più difficile del WIS: il ramo «prendo» del WIS incassa sempre $w_j$, qui uno dei due rami incassa il valore del **successivo**. Verificarlo su $n=2$: l'unica mossa possibile è SecondaDiDue e frutta $v_2$, non $v_1$.
### 18/07/2022 · Noleggio furgoni — F1 (copertura)
$n$ giorni da coprire. Furgone **giallo** noleggiato il giorno $i$: costo $g_i$, copre $i$ e $i+1$. Furgone **rosso**: costo $r_i$, copre $i$, $i+1$, $i+2$. Minimizzare la spesa garantendo che in ogni giorno ci sia **almeno un** furgone. Nessuna ipotesi lega $r_i$ a $g_i$.
**Osservazione che sblocca l'esercizio.** Il giorno $1$ può essere coperto solo da un furgone noleggiato il giorno $1$, perché i furgoni coprono solo in avanti. Ma questo vale **solo per il primo giorno**: per un giorno scoperto $j>1$ il furgone che lo copre può partire da $j$, da $j-1$ o da $j-2$, e partire da un giorno già coperto è lecito, perché la sovrapposizione è ammessa. Lo stato giusto è quindi **dove si noleggia il prossimo furgone**, non quale sia il primo giorno scoperto.
**Sottoproblema.** $\text{OPT}(i)$ $=$ costo minimo per coprire i giorni $i, i+1, \ldots, n$ **quando il prossimo furgone viene noleggiato esattamente il giorno $i$**.
**Casi base.** $\text{OPT}(i)=0$ per ogni $i>n$: oltre il giorno $n$ non c'è nulla da coprire, e la coda di un rosso noleggiato in $n$ o $n-1$ è innocua.
**Ricorrenza.** Si sceglie il tipo del furgone noleggiato in $i$, e poi **dove sta il prossimo**. Un giallo copre $i,i+1$, quindi il prossimo furgone deve arrivare entro $i+2$; un rosso copre $i,i+1,i+2$, quindi il prossimo deve arrivare entro $i+3$:
$$\text{OPT}(i) = \min \begin{cases} g_i + \text{OPT}(i+1) \\[2pt] g_i + \text{OPT}(i+2) \\[2pt] r_i + \text{OPT}(i+1) \\[2pt] r_i + \text{OPT}(i+2) \\[2pt] r_i + \text{OPT}(i+3) \end{cases}$$
**Risposta.** $\text{OPT}(1)$ — lecito perché in $1$ un furgone ci deve essere per forza. **Ordine.** $i$ decrescente. **Costo.** $\Theta(n)$ celle $\times$ $O(1)$: $\Theta(n)$ tempo e spazio.

> [!warning] Errata corrige — la ricorrenza a due termini è SBAGLIATA
> La versione compatta $\text{OPT}(i) = \min\{g_i + \text{OPT}(i+2),\ r_i + \text{OPT}(i+3)\}$, che segue dall'indicizzare sul «primo giorno scoperto», **non calcola l'ottimo**. Controesempio: l'istanza della **figura del compito stesso**, $n=7$, $r=(10,11,11,11,7,9,6)$, $g=(9,10,12,9,7,8,10)$. Il testo dichiara $\text{Opt}=10+9+7=26$: rosso in $1$ (copre $1$-$3$), giallo in $4$ (copre $4$-$5$), rosso in $5$ (copre $5$-$7$) — e il giorno $5$ è coperto **due volte**. La versione compatta restituisce $27$, perché per coprire $\{6,7\}$ è costretta a noleggiare in $6$ (costo $8$) e non vede il rosso in $5$ a costo $7$. Verificato per enumerazione esaustiva: su $3000$ istanze casuali con $n \le 9$ la versione compatta sbaglia nel **34%** dei casi, la versione a cinque rami in nessuno.

> [!info] Perché il prof, sul wifi, ne scrive solo tre
> L'**esercitazione 2** (ripetitori $L$ e $H$) è lo stesso problema, e Gualà scrive $\text{Opt}[i]=\min\{L_i+\text{Opt}[i+1],\ L_i+\text{Opt}[i+2],\ H_i+\text{Opt}[i+3]\}$ — tre termini invece di cinque. Non è una semplificazione gratuita: la traccia del wifi dichiara $H_i \ge L_i$, e sotto quell'ipotesi i due rami mancanti, $H_i+\text{Opt}[i+1]$ e $H_i+\text{Opt}[i+2]$, sono **dominati** dai corrispondenti con $L_i$. Verificato: con $H_i \ge L_i$ la forma a tre termini è corretta su $3000$ istanze su $3000$; togliendo quell'ipotesi sbaglia nel $22\%$ dei casi. Nei furgoni $r_i$ e $g_i$ non sono ordinati, quindi **servono tutti e cinque i rami**. Morale: un'ipotesi sui costi enunciata nel testo non è decorazione, è ciò che autorizza a potare la ricorrenza.

> [!info] La formulazione a prefisso, equivalente
> Lo stesso problema si indicizza anche in avanti: $\text{OPT}(j)$ $=$ costo minimo per coprire i giorni $1,\ldots,j$, e il giorno $j$ è coperto da un furgone che parte in $s$ con $s \le j \le s + \text{span} - 1$, quindi $$\text{OPT}(j) = \min\Bigl\{\ \min_{s\,\in\,\{j-1,\,j\}} \bigl(g_s + \text{OPT}(s-1)\bigr),\ \ \min_{s\,\in\,\{j-2,\,j-1,\,j\}} \bigl(r_s + \text{OPT}(s-1)\bigr)\ \Bigr\}$$ con $\text{OPT}(j)=0$ per $j\le 0$ e i soli $s \ge 1$. È la forma standard della **copertura di una linea con intervalli pesati** e dà anch'essa $26$ sull'istanza del prof. Le due sono equivalenti: usa quella che ti viene, ma dichiara lo stato con precisione.
### 28/09/2022 · Comizi elettorali — F4 su base F1
$n$ giorni, il comizio del giorno $i$ vale $v_i$ voti. Vincoli: niente comizi in due giorni **consecutivi**, e al più $B$ comizi in tutto. Massimizzare i voti. Il sottocaso dichiarato nella traccia (senza il vincolo $B$) è WIS su cammino puro.
**Sottoproblema.** $\text{OPT}(j,b)$ $=$ massimo numero di voti considerando solo i primi $j$ giorni e usando **al più** $b$ comizi.
**Casi base.** $\text{OPT}(j,b)=0$ per ogni $j\le 0$ e per ogni $b$; $\text{OPT}(j,0)=0$ per ogni $j$.
**Ricorrenza.**
$$\text{OPT}(j,b) = \max \begin{cases} \text{OPT}(j-1,\,b) & \text{non faccio comizio il giorno } j \\[2pt] v_j + \text{OPT}(j-2,\,b-1) & \text{lo faccio, se } b \ge 1 \end{cases}$$
**Risposta.** $\text{OPT}(n,B)$ — grazie alla formulazione «al più $b$» non serve alcun massimo finale. **Ordine.** $j$ crescente, $b$ in ordine qualunque.
**Costo.** $\Theta(n \cdot B)$ celle $\times$ $O(1)$. Poiché non si possono fare più di $\lceil n/2 \rceil$ comizi rispettando il vincolo di non adiacenza, si sostituisce $B$ con $B' = \min(B, \lceil n/2\rceil)$: il costo è $O(n^2)$ e l'algoritmo è **polinomiale**, non pseudo-polinomiale. Sottocaso senza budget: $\Theta(n)$.

> [!warning] «Al più $b$» contro «esattamente $b$»
> Con «esattamente» la ricorrenza è la stessa, ma la risposta diventa $\max_{0\le b\le B} \text{OPT}(n,b)$ e i casi base vanno rivisti ($\text{OPT}(j,b) = -\infty$ quando $b$ è irraggiungibile). Entrambe sono corrette; «al più» costa una riga in meno ed è la scelta da fare sotto esame, ma va **dichiarata** nel passo 1, altrimenti la risposta finale non si giustifica.
### 20/07/2026 · Canguro — F8 con budget di salti
Scacchiera $n \times m$, si parte da $(1,1)$ e si arriva a $(n,m)$ muovendosi solo verso destra o verso il basso. La casella $(i,j)$ ospita $f_{i,j}$ fiori; se $f_{i,j}=-1$ c'è un cacciatore e finirci significa perdere. Oltre al passo di una casella si può **saltare** (sempre a destra o in basso) di lunghezza arbitraria, ma i salti disponibili nell'intero livello sono $k$. Massimizzare i fiori mangiati, o dichiarare il livello irrisolvibile.
**Sottoproblema.** $\text{OPT}(i,j,s)$ $=$ massimo numero di fiori raccolti lungo un cammino ammissibile da $(1,1)$ a $(i,j)$ che usa **al più** $s$ salti; vale $-\infty$ se nessun cammino ammissibile raggiunge $(i,j)$ con quel budget. Sono $n \cdot m \cdot (k+1)$ celle.
**Casi base.** $\text{OPT}(i,j,s) = -\infty$ se $f_{i,j}=-1$, per ogni $s$ (la casella non è calpestabile). $\text{OPT}(1,1,s) = f_{1,1}$ per ogni $s$, se $f_{1,1}\ne-1$. $\text{OPT}(i,j,s)=-\infty$ per $i<1$ o $j<1$.
**Ricorrenza.** Per $f_{i,j}\ne-1$ e $(i,j)\ne(1,1)$:
$$\text{OPT}(i,j,s) = f_{i,j} + \max \begin{cases} \text{OPT}(i-1,\,j,\,s) \\[2pt] \text{OPT}(i,\,j-1,\,s) \\[2pt] \displaystyle\max_{2 \le d \le i-1} \text{OPT}(i-d,\,j,\,s-1) & \text{se } s \ge 1 \\[4pt] \displaystyle\max_{2 \le d \le j-1} \text{OPT}(i,\,j-d,\,s-1) & \text{se } s \ge 1 \end{cases}$$
I primi due rami sono i passi normali, gli altri due i salti: il salto **scavalca** le caselle intermedie, che quindi non vanno né sommate né controllate — è tutto il senso dei salti, aggirare i cacciatori. Un salto di lunghezza $1$ coinciderebbe con un passo consumando un salto, quindi è dominato e si può escludere ($d \ge 2$).
**Risposta.** $\text{OPT}(n,m,k)$; se vale $-\infty$, il livello non è risolvibile.
**Ordine.** Per $s$ crescente da $0$ a $k$; dentro ogni piano, per $i$ e $j$ crescenti.
**Costo.** $\Theta(nmk)$ celle. Scritta così, ogni cella costa $O(n+m)$ per le due scansioni di salto, quindi $O\bigl(nmk(n+m)\bigr)$. Mantenendo per ogni piano $s-1$ i **massimi di prefisso** lungo ciascuna colonna e ciascuna riga (precalcolabili in $\Theta(nm)$ per piano) ogni cella torna $O(1)$ e il totale scende a $\Theta(nmk)$. È **polinomiale**: più di $n+m-2$ salti non servono, quindi si tronca a $k'=\min(k,\,n+m-2)$ e il costo è $O\bigl(nm(n+m)\bigr)$.

> [!warning] $-1$ è un divieto, non un valore
> Sommare $-1$ ai fiori come se fosse un guadagno negativo produce un algoritmo che *attraversa* i cacciatori pagando un pedaggio: è un problema diverso. La casella va esclusa con $-\infty$, e il livello irrisolvibile va riconosciuto dal valore finale, non da un fallimento.

> [!warning] Si contano i salti, non la loro lunghezza
> Il budget $k$ limita **quante volte** si salta, non di quanto. Un'unica dimensione $s$ con dominio $0..k$ basta: la lunghezza del salto è già catturata dall'indice di destinazione.
### 08/09/2026 · Almost monochromatic LIS — F2 con budget di cambi
Sequenza di $n$ elementi, l'$i$-esimo con valore $v_i$ e colore $c_i \in \{B,N\}$. Un sottoinsieme $S$ è una **sottosequenza crescente quasi monocromatica** se i valori di $S$, letti da sinistra a destra, sono strettamente crescenti e i **cambi di colore** lungo $S$ sono al più $k$. Calcolare la lunghezza massima di una tale sottosequenza.
**Sottoproblema.** $\text{OPT}(i,t)$ $=$ lunghezza massima di una sottosequenza crescente quasi monocromatica che **termina esattamente nell'elemento $i$** e ha **esattamente** $t$ cambi di colore; $-\infty$ se una tale sottosequenza non esiste. Sono $n(k+1)$ celle.
**Casi base.** $\text{OPT}(i,0) \ge 1$ per ogni $i$: il singolo elemento $i$ è una sottosequenza valida con zero cambi. $\text{OPT}(i,t) = -\infty$ per $t<0$.
**Ricorrenza.** Il predecessore $j<i$ deve avere $v_j < v_i$ (crescenza); se ha lo **stesso** colore non consuma un cambio, se ha colore **diverso** ne consuma uno:
$$\text{OPT}(i,t) = 1 + \max \begin{cases} 0 & \text{se } t=0 \text{ (nessun predecessore)} \\[2pt] \displaystyle\max_{\substack{j<i,\ v_j<v_i \\ c_j=c_i}} \text{OPT}(j,\,t) \\[6pt] \displaystyle\max_{\substack{j<i,\ v_j<v_i \\ c_j\ne c_i}} \text{OPT}(j,\,t-1) & \text{se } t \ge 1 \end{cases}$$
con la convenzione $\max\emptyset = -\infty$.
**Risposta.** $\displaystyle\max_{1\le i\le n}\ \max_{0\le t\le k} \text{OPT}(i,t)$. Il doppio massimo scioglie **entrambi** i vincoli della definizione: «termina in $i$» e «esattamente $t$ cambi».
**Ordine.** $i$ crescente; dentro ogni $i$, $t$ crescente da $0$ a $k$.
**Costo.** $n(k+1)$ celle $\times$ $O(n)$ per cella (scansione dei predecessori) $= O(n^2 k)$. Poiché una sottosequenza di $n$ elementi ha al più $n-1$ cambi, si tronca a $k'=\min(k,n-1)$: costo $O(n^3)$ nel caso peggiore, **polinomiale** — $k$ conta elementi, non è un valore numerico dell'input.

> [!warning] Il budget deve entrare nella tabella, non filtrare a valle
> Calcolare la LIS normale e poi scartare le soluzioni con più di $k$ cambi non funziona: la LIS più lunga può avere troppi cambi mentre esiste una LIS un po' più corta che rispetta il vincolo, e nessuna delle due si ricava dall'altra. Il contatore $t$ deve essere un **indice**, esattamente come la capacità nel Knapsack.

> [!info] Il titolo era il suggerimento
> La traccia si intitola *(almost monochromatic longest increasing subsequence)*. «Longest increasing subsequence» dà la famiglia (F2, sottoproblema vincolato a terminare in $i$, $\max$ finale su tutte le celle); «almost monochromatic» dà il twist (T1, un contatore che diventa la seconda dimensione). Due parole del titolo e la forma della tabella è già decisa.
## Domande concettuali sulla nota 04
> [!info] A cosa servono
> Non sono item d'esame: sono **domande costruite** sui punti della nota 04 dove il ragionamento è facile da dare per scontato. Servono come controllo prima di attaccare le progettazioni qui sopra — se una di queste non esce, il buco è nella teoria, non nell'allenamento.
### Sottostruttura ottima del WIS
> [!question] Domanda costruita — Sottostruttura ottima del WIS
> **D:** Qual è la sottostruttura ottima del problema WIS su cammino, e come si dimostra che l'insieme ottimo $S^*$ deve rispettarla?

> [!info]- Risposta modello
> **Impostazione.** Sia $S^*$ una soluzione ottima e sia $n \geq 2$. Si interroga l'**ultimo nodo**: i casi $v_n \notin S^*$ e $v_n \in S^*$ sono esaustivi e mutuamente esclusivi.
>
> **Caso 1 — $v_n \notin S^*$.** Tesi: $S^*$ è ottima anche per $G' = G - \{v_n\}$.
> *Per assurdo*: sia $S$ indipendente in $G'$ con $w(S) > w(S^*)$. Poiché $v_n \notin S$, $S$ è indipendente anche in $G$ (i soli archi in più di $G$ sono quelli incidenti a $v_n$). Allora $S$ è indipendente in $G$ e pesa più di $S^*$ — contro l'ottimalità di $S^*$.
>
> **Caso 2 — $v_n \in S^*$.** Per indipendenza $v_{n-1} \notin S^*$. Tesi: $S^* \setminus \{v_n\}$ è ottima per $G'' = G - \{v_{n-1}, v_n\}$.
> *Per assurdo*: sia $S$ indipendente in $G''$ con $w(S) > w(S^* \setminus \{v_n\})$. Allora $S \cup \{v_n\}$ è indipendente in $G$: le coppie interne a $S$ lo sono perché $S \subseteq \{v_1, \ldots, v_{n-2}\}$, e $v_n$ non confligge con nessuno perché il suo unico vicino $v_{n-1}$ non sta in $G''$. Il peso è $w(S) + w_n > w(S^* \setminus \{v_n\}) + w_n = w(S^*)$ — contro l'ottimalità di $S^*$.
>
> **Conclusione.** Ogni soluzione ottima ha una delle due forme, quindi il valore ottimo è il massimo fra i due candidati, da cui l'equazione di Bellman
> $$\text{OPT}[j] = \max\{\text{OPT}[j-1],\; w_j + \text{OPT}[j-2]\}$$
> con casi base $\text{OPT}[1] = w_1$ e $\text{OPT}[2] = \max\{w_1, w_2\}$. Senza questa dimostrazione la ricorrenza sarebbe solo plausibile, non giustificata.
>
> ⏱️ **Se la traccia dà 5 righe**: enuncia i due casi con i rispettivi sottografi $G'$ e $G''$ (2 righe), dai i due argomenti per assurdo in forma sintetica «$S$ resterebbe indipendente in $G$ e peserebbe di più» (2 righe), chiudi con la ricorrenza (1 riga). Le verifiche di indipendenza dettagliate si omettono, ma **i due casi e il fatto che siano esaustivi non si omettono mai**: è quello il cuore della risposta.
### Ricostruzione senza traccia delle scelte
> [!question] Domanda costruita — Ricostruzione senza traccia delle scelte
> **D:** Come si ricostruisce la soluzione ottima del WIS senza salvare le scelte durante il calcolo bottom-up?

> [!info]- Risposta modello
> **Idea.** Le scelte non vanno memorizzate perché sono **ricalcolabili** dai soli valori $\text{OPT}[1..n]$: confrontando i due termini della ricorrenza in posizione $j$ si capisce quale dei due l'ha vinta.
>
> **Criterio.** $v_j$ appartiene alla soluzione ottima ricostruita se e solo se
> $$w_j + \text{OPT}[j-2] \;>\; \text{OPT}[j-1]$$
>
> **Procedura.** Si parte da $j = n$ e si scorre verso sinistra:
> - se la disuguaglianza **stretta** vale, si **include** $v_j$ e si salta a $j - 2$ (il vicino $v_{j-1}$ è escluso per forza);
> - altrimenti (compreso il pareggio) si **esclude** $v_j$ e si passa a $j - 1$.
>
> Si termina quando $j \leq 0$.
>
> **Complessità.** $\Theta(n)$ aggiuntivo, con $O(1)$ spazio in più: ogni iterazione decrementa $j$ di almeno 1, quindi le iterazioni sono al più $n$.
>
> **Osservazione da aggiungere se c'è spazio.** Sui pareggi ($w_j + \text{OPT}[j-2] = \text{OPT}[j-1]$) lo pseudocodice qui presentato **esclude** $v_j$: il test `OPT[j-1] ≥ w_j+OPT[j-2]` cattura anche l'uguaglianza e manda a $j-1$. È una scelta arbitraria ma legittima — a parità di somma entrambe le ricostruzioni (includere o escludere $v_j$) danno insiemi ottimi, coerente col fatto che la soluzione ottima non è unica mentre il valore lo è.
### Da cammino ad albero: perché due sottoproblemi per nodo
> [!question] Domanda costruita — Da cammino ad albero: perché due sottoproblemi per nodo
> **D:** Come si estende l'algoritmo di programmazione dinamica per il WIS dai cammini agli alberi, e perché serve una coppia di sottoproblemi per ogni nodo invece di uno solo come nel caso del cammino?

> [!info]- Risposta modello
> **Il problema del passaggio.** Sul cammino un solo valore per nodo basta, perché ogni nodo ha **un solo predecessore** e la condizione «$v_{j-1}$ escluso» si esprime saltando a $j-2$. Su un albero un nodo $v$ ha **più figli**, e per sapere se $v$ è includibile serve sapere se ciascun figlio è incluso nella *propria* soluzione ottima: un unico valore per sottoalbero non porta con sé questa informazione.
>
> **Definizione dei due sottoproblemi.** Per ogni nodo $v$:
> - $A[v]$ = peso massimo nel sottoalbero radicato in $v$, **senza vincoli** su $v$;
> - $B[v]$ = peso massimo nello stesso sottoalbero, **con $v$ escluso**.
>
> **Ricorrenza.** Detti $u_1, \ldots, u_k$ i figli di $v$:
> $$B[v] = \sum_i A[u_i] \qquad\qquad A[v] = \max\Bigl\{\,B[v],\;\; w_v + \sum_i B[u_i]\,\Bigr\}$$
>
> **Lettura della ricorrenza** — è qui che si vede perché servono due valori:
> - se $v$ **è preso**, tutti i figli devono essere esclusi, quindi si sommano i $B[u_i]$;
> - se $v$ **non è preso**, ogni figlio è libero di fare il meglio, quindi si sommano gli $A[u_i]$.
>
> **Casi base e ordine di calcolo.** Per una foglia $v$: $B[v] = 0$ e $A[v] = w_v$. Si procede **bottom-up dalle foglie alla radice** (equivalentemente, con una visita post-order), così che i valori dei figli siano pronti quando serve il padre.
>
> **Risultato e complessità.** La risposta è $A[r]$ con $r$ radice. Il costo è $\Theta(n)$ in tempo e spazio: ogni coppia $(A[v], B[v])$ si calcola una sola volta, e la somma dei gradi su tutti i nodi è $\Theta(n)$ perché un albero ha $n-1$ archi.
### Perché la ricorsione diretta è esponenziale
> [!question] Domanda costruita — Perché la ricorsione diretta è esponenziale
> **D:** Perché l'approccio ricorsivo diretto per il WIS su cammino ha complessità esponenziale, mentre l'algoritmo bottom-up è lineare?

> [!info]- Risposta modello
> **Costo della ricorsione diretta.** Ogni chiamata su $j$ ne genera due, su $j-1$ e $j-2$, con $O(1)$ di lavoro proprio:
> $$T(n) = T(n-1) + T(n-2) + O(1)$$
> È la ricorrenza di Fibonacci (vedi [[01 - Il Problema di Fibonacci]]), la cui soluzione è $T(n) = \Theta(\phi^n)$ con $\phi = \frac{1+\sqrt 5}{2} \approx 1{,}618$: **esponenziale**.
>
> **Causa del costo.** Non è che i sottoproblemi siano tanti — è che vengono **ricalcolati**. I sottoproblemi *distinti* sono solo i prefissi $G_1, \ldots, G_n$, cioè $n$; l'albero di ricorsione però ne visita un numero esponenziale, perché lo stesso $\text{OPT}(j)$ viene raggiunto da molti rami diversi e ogni volta ricalcolato da zero. Su $n = 6$ le chiamate sono 15 per 6 sottoproblemi; su $n = 30$ sono $1\,664\,079$ per 30 sottoproblemi.
>
> **Perché il bottom-up è lineare.** Risolve ciascuno degli $n$ sottoproblemi **una volta sola**, in ordine crescente di $j$, così che $\text{OPT}[j-1]$ e $\text{OPT}[j-2]$ siano già disponibili quando servono. Ogni cella costa $O(1)$, quindi il totale è $\Theta(n)$.
>
> **La frase che chiude la risposta.** Il costo passa da «numero di nodi dell'albero di ricorsione» a «numero di sottoproblemi distinti $\times$ costo di uno» — ed è esattamente ciò che fa la programmazione dinamica. La memoization top-down ottiene lo stesso $\Theta(n)$ per la stessa ragione, tenendo l'albero di ricorsione ma visitandolo una volta sola per sottoproblema.
## Teoria della DP uscita ai compiti
Item **realmente comparsi** ai compiti, più uno costruito su Hirschberg. Non sono simulazione dello scritto attuale — sono un **controllo di precisione sulle definizioni**, ed è esattamente ciò che serve al passo 1 dell'Esercizio 3. Pienamente esigibili all'orale.

> [!warning] Tutti e quattro gli item sono in formato Clementi
> Vengono da appelli **2022–2023**, quando il Modulo II era tenuto dal prof. Clementi e l'Esercizio 1 poteva chiedere *teoria* sulla programmazione dinamica. Nella configurazione attuale la DP compare **solo** in Esercizio 3, e sempre come progettazione su un problema inedito — per quella si va in [[#Progettazione — Esercizio 3|la sezione di progettazione]].
> Non sono quindi simulazione dello scritto. Sono però un **controllo di precisione** sulle definizioni: se sai rispondere, la tua definizione di sottoproblema regge, ed è esattamente ciò che serve al passo 1 dell'Esercizio 3. E sono pienamente esigibili **all'orale**.
### Weighted Interval Scheduling
#### Riduzione a WIS
> [!question] Domanda d'esame — Riduzione a WIS
> **D:** *(Vero o Falso)* «Trasformando opportunamente l'istanza I, è possibile darla in input all'algoritmo di Programmazione Dinamica per il Weighted Interval Scheduling ed ottenere la soluzione ottima per I.» *(traccia 12/09/2023 · Es. 1 n. 2 · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Vero.
>
> **Perché.** La tecnica è la **riduzione**: si trasforma l'istanza $I$ in un'istanza equivalente di WIS (job con intervalli $[s_j, f_j]$ e pesi $w_j$) tale che la soluzione ottima calcolata dall'algoritmo PD di WIS sull'istanza trasformata corrisponda esattamente alla soluzione ottima di $I$.
>
> **Esempio.** L'Interval Scheduling **non pesato** (vedi il confronto a inizio sezione): ponendo $w_j = 1$ per ogni job, l'equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ diventa $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, 1 + \text{OPT}(p(j))\}$, che calcola la cardinalità massima di un sottoinsieme di job compatibili — esattamente l'ottimo del problema non pesato.
>
> **Osservazione.** In generale, per mostrare che un problema $P$ si risolve con l'algoritmo PD di WIS basta esibire una **trasformazione polinomiale** dell'istanza di $P$ in un'istanza di intervalli pesati che preservi il valore ottimo: è lo schema di riduzione che estende un algoritmo esistente a problemi apparentemente diversi.
### Knapsack 0/1
#### Significato di OPT(j-1, w-wj)
> [!question] Domanda d'esame — Significato di OPT(j-1, w-wj)
> **D:** «B) Prefissato un qualsiasi ordinamento degli items {Ij : j= 1,...,n}, la funzione OPT(j-1,w-wj) calcolata da PD è uguale al valore ottimo relativo alla sottoistanza \<I1,...,Ij-1; w- wj \> ? Se SI, in che modo viene utilizzato questo valore nell'algoritmo PD? Se NO, quale/i valore/i della funzione OPT(j,w) vengono utilizzati da PD al generico passo ricorsivo?» *(traccia 14/09/2022 · Es. 1.2 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Sì.
>
> **Perché.** Per definizione $\text{OPT}(j,w)$ è il valore ottimo della sottoistanza formata dai primi $j$ item con capacità $w$ (vedi la definizione data in questa sezione); sostituendo $j \to j-1$ e $w \to w-w_j$, $\text{OPT}(j-1, w-w_j)$ è — sempre per definizione — il valore ottimo della sottoistanza $\langle I_1,\ldots,I_{j-1}; w-w_j \rangle$.
>
> **Uso nell'algoritmo.** Questo valore compare nel passo ricorsivo dell'equazione di Bellman $\text{OPT}(j,w) = \max\{\text{OPT}(j-1,w),\, v_j + \text{OPT}(j-1, w-w_j)\}$, e corrisponde al **Caso 2**: il ramo in cui l'item $I_j$ **viene incluso** nella soluzione ottima, per cui si somma $v_j$ al valore ottimo ottenibile dai primi $j-1$ item con la capacità residua $w-w_j$ rimasta dopo aver "pagato" il peso $w_j$.
>
> **Condizione.** Il termine è valido solo se $w_j \le w$; altrimenti l'item non entra e $\text{OPT}(j,w) = \text{OPT}(j-1,w)$.
#### Cosa rappresenta M(j,w)
> [!question] Domanda d'esame — Cosa rappresenta M(j,w)
> **D:** «C) Nella versione iterativa dell'algoritmo PD, l'entrata della matrice M(j,w) contiene la soluzione ottima formata da un qualsiasi sottoinsieme S di {I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) } tale che: |S| <= j e Σ_(k∈S) vk = w ?» *(traccia 14/09/2022 · Es. 1.3 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** No.
>
> **Errore 1 — l'insieme di partenza.** $M(j,w)$ è definita sui **primi $j$ item** $\{I_1,\ldots,I_j\}$, non su un sottoinsieme $S$ qualunque estratto da **tutta** la lista $\{I_1,\ldots,I_n\}$ con $|S|\le j$: un sottoinsieme di $j$ item presi da posizioni arbitrarie (es. $\{I_2, I_7\}$ con $j=5$) non è ammissibile per $M(j,w)$, che considera solo $S \subseteq \{I_1,\ldots,I_j\}$.
>
> **Errore 2 — si sommano i valori invece dei pesi.** Il vincolo che definisce l'ammissibilità riguarda i **pesi**, $\sum_{k \in S} w_k$, non i valori $\sum_{k \in S} v_k$. I valori si sommano nella *funzione obiettivo*, quella che si massimizza; i pesi nel *vincolo*, quello che si rispetta. Scambiarli significa scambiare ciò che si ottimizza con ciò che ci si può permettere.
>
> **Errore 3 — l'uguaglianza al posto della disuguaglianza.** Deve valere $\le w$, non $= w$: la soluzione ottima **non satura** necessariamente lo zaino. Sull'istanza della demo (slide 47) si ha $\text{OPT}(5,4) = 7$, realizzato da $\{1,2\}$ che pesa $1+2 = 3 < 4$; anzi, in quell'istanza *nessun* sottoinsieme pesa esattamente 4, quindi con l'uguaglianza la cella non sarebbe nemmeno definita.
>
> **Definizione corretta.** Coerente con quella data in questa nota:
> $$M(j,w) = \max\Bigl\{\sum_{k\in S} v_k \;:\; S \subseteq \{I_1,\ldots,I_j\},\; \sum_{k \in S} w_k \le w\Bigr\}$$
#### K è in P?
> [!question] Domanda d'esame — K è in P?
> **D:** «ESERCIZIO 1. Si consideri il problema Knapsack (K) e si consideri l'algoritmo ottimale PD per K basato sulla Programmazione Dinamica. Si consideri una generica istanza X = \<I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) ; W\> di K, dove M = max{wj, vj, W : j=1,...,n}. Si risponda alle seguenti domande con al massimo quattro righe negli spazi appropriati, dando delle brevi spiegazioni. A) L'esistenza di un qualsiasi algoritmo che impiega tempo Θ(n^2 log^24(M)) mostrerebbe che il problema K è nella classe P?» *(traccia 14/09/2022 · Es. 1.1 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Sì.
>
> **Perché.** $\Theta(n^2 \log^{24} M)$ è polinomiale nella **dimensione dell'input**, che è $O(n \log M)$ bit (peso, valore e capacità sono codificati in binario, quindi ciascuno occupa $O(\log M)$ bit). Un tempo $\Theta(n^2 \log^{24} M)$ è polinomiale sia in $n$ sia in $\log M$, cioè nella lunghezza della codifica dell'istanza: un tale algoritmo classificherebbe $K$ in P.
>
> **Confronto con la DP standard.** L'algoritmo PD di questa nota ha complessità $\Theta(nW)$: è polinomiale nel *valore* $W$ (quindi in $M$), non nella sua *dimensione in bit* $\log W$ — è **pseudo-polinomiale**, non polinomiale (vedi il riquadro sulla pseudo-polinomialità qui sopra).
>
> **Distinzione.** È esattamente quella tra $\text{poly}(M)$ (pseudo-polinomiale, come $\Theta(nW)$) e $\text{poly}(\log M)$ (polinomiale in senso proprio, come l'ipotetico $\Theta(n^2 \log^{24} M)$).
>
> ⏱️ **Se la traccia dà 4 righe**: rispondi Sì e giustifica in una riga che $\Theta(n^2\log^{24}M)$ è polinomiale in $n$ e $\log M$ — cioè nella dimensione in bit dell'istanza, $O(n\log M)$ — quindi metterebbe $K$ in P (1-2 righe); chiudi con il confronto secco «a differenza della PD standard, che è $\Theta(nW)$ e quindi solo pseudo-polinomiale» (1-2 righe). **Non va mai omessa** la distinzione fra dimensione in bit dell'istanza e valore numerico dei dati: è il concetto su cui verte l'intera domanda.

> [!warning] Nel campione questa nota non ha ancora prodotto item d'esame
> Sequence Alignment, Hirschberg e Bellman-Ford **non compaiono** nelle 24 tracce esaminate, in nessuna posizione. Sono però programma pieno e materia d'orale, e Bellman-Ford è un algoritmo con nome proprio: l'unico item qui sotto è **costruito** sulla forma che l'Esercizio 2 usa per gli algoritmi con nome proprio, cioè «enuncia idea e complessità di X».
> Quando arriveranno item reali su questi argomenti, questo file è il posto dove metterli.
### Hirschberg
#### Idea e complessità di Hirschberg
> [!question] Domanda costruita — Idea e complessità di Hirschberg
> **D:** Qual è l'idea alla base dell'algoritmo di Hirschberg per il sequence alignment, e quali sono tempo e spazio risultanti rispetto alla DP standard?

> [!info]- Risposta modello
> **Idea.** Il valore $\text{OPT}(i,j)$ si può calcolare mantenendo solo due colonne della matrice (quella corrente e la precedente), in spazio $O(m+n)$ — ma così si perde la possibilità di fare il traceback. Hirschberg recupera l'allineamento sfruttando il grafo di edit: si calcola $f(i,j)$ (cammino minimo da $(0,0)$ a $(i,j)$, che coincide con $\text{OPT}(i,j)$) e $g(i,j)$ (cammino minimo da $(i,j)$ a $(m,n)$), ciascuno in tempo $O(mn)$ e spazio $O(m+n)$.
>
> **Divide.** Sulla colonna centrale $n/2$ si trova l'indice $q^*$ che minimizza $f(q,n/2)+g(q,n/2)$: per l'Osservazione 2, il nodo $(q^*,n/2)$ appartiene a un cammino minimo, quindi fa parte di un allineamento ottimo.
>
> **Conquer.** Si applica ricorsivamente lo stesso procedimento ai due sotto-problemi $(x_1\ldots x_{q^*}, y_1\ldots y_{n/2})$ e $(x_{q^*+1}\ldots x_m, y_{n/2+1}\ldots y_n)$, dimezzando ogni volta l'intervallo di colonne.
>
> **Complessità.** Tempo: $T(m,n) \leq T(q^*,n/2)+T(m-q^*,n/2)+O(mn)$, che per induzione forte su $m+n$ dà $T(m,n) \leq 2cmn = O(mn)$ — stesso ordine della DP standard. Spazio: $\Theta(m+n)$, perché ogni chiamata ricorsiva usa $\Theta(m)$ spazio per calcolare $f(\cdot,n/2)$ e $g(\cdot,n/2)$, e il numero di chiamate ricorsive attive è limitato.
>
> **Confronto.** Rispetto alla DP standard ($\Theta(mn)$ tempo e spazio), Hirschberg mantiene lo stesso ordine di tempo ma riduce lo spazio da quadratico a lineare — il vantaggio è puramente sullo spazio.
## Trappole ricorrenti
Le stesse otto ricorrono nei dodici svolgimenti. Sono raggruppate per il passo in cui scattano.

| Passo | Trappola | Come si smaschera |
|---|---|---|
| Sottoproblema | Fermarsi a un indice quando ne servono due | «per decidere su $i$ mi basta $\text{OPT}(i-1)$?» — se la risposta cita il budget speso o com'è finita la soluzione, no |
| Sottoproblema | Dimenticare la clausola «che termina esattamente in $i$» | se il contributo di $i$ dipende dal predecessore, senza la clausola la ricorrenza non si scrive |
| Sottoproblema | Stato con un numero **esponenziale** di valori (un sottoinsieme, una permutazione) | la definizione è sbagliata: va trovata la quantità aggregata che riassume il passato |
| Ricorrenza | Copiare il salto $j-2$ del WIS senza rileggere il vincolo | riderivarlo sull'istanza minima: pausa di $3$ settimane $\Rightarrow$ salto a $j-4$ |
| Ricorrenza | Scrivere un $\min$ perché «c'è un avversario» | se l'avversario non **sceglie**, non è minimax: resta $\max$-$\max$ |
| Ricorrenza | Dimenticare un ramo (il «mi fermo», il «non lo prendo») | enumerare il prodotto delle decisioni indipendenti e contare i rami |
| Caso base | Scriverlo come uguaglianza ($\text{OPT}(0)=0$) quando la ricorrenza salta di più | se il salto è di $3$, servono più celle fuori range: usare una **disuguaglianza** |
| Caso base | Mescolare $0$ e $+\infty$ in una minimizzazione | $0$ = «niente da fare, legittimo»; $+\infty$ = «configurazione inammissibile». Non sono intercambiabili |
| Risposta | Leggere l'ultima cella quando il sottoproblema è vincolato | rileggere il passo 1: ogni vincolo nella definizione va sciolto con un $\min$/$\max$ finale |
| Complessità | Dichiarare $\Theta(nB)$ pseudo-polinomiale per analogia col Knapsack | chiedersi da cosa è limitato $B$: se conta elementi, si tronca a $\min(B,n)$ ed è polinomiale |
| Complessità | Dichiarare $\Theta(n)$ per analogia con il WIS quando la cella costa $O(n)$ | decisione **binaria** $\to$ cella $O(1)$; scelta **multipla** sul predecessore $\to$ cella $O(j)$ |
| Ordine | Riempire per $i$ crescente un sottoproblema definito a **suffisso** | guardare da quali celle dipende la ricorrenza: se da $i+1, i+2$, si riempie all'indietro |

> [!question] Il controllo dei cinque minuti, prima di consegnare
> 1. La definizione del sottoproblema è una **frase completa** che dice cosa contiene una cella, e dichiara **quanti** sono i sottoproblemi?
> 2. I rami della ricorrenza sono **esaustivi** rispetto alla prima (o ultima) decisione, ed è scritta una riga di *cut-and-paste* sul residuo?
> 3. I casi base coprono **tutti** gli indici fuori range che la ricorrenza genera, non solo il primo?
> 4. La risposta scioglie **ogni** vincolo presente nella definizione del sottoproblema?
> 5. La complessità è scritta come *celle $\times$ costo per cella*, con una frase esplicita su polinomiale o pseudo-polinomiale?
## Nota sul perimetro
I primi sette item coprono gli Esercizio 3 delle tracce più recenti: sono l'allenamento vero. I problemi di DP **studiati** — weighted interval scheduling, knapsack, segmented least squares, sequence alignment, Hirschberg, Bellman-Ford, LIS — nella configurazione attuale non sono mai stati chiesti come teoria allo scritto: servono come **repertorio di telai** da riconoscere sotto il travestimento, ed è all'orale che vengono chiesti per nome.
Le quattro domande concettuali in coda sono costruite, non sono item d'esame: stanno qui come controllo della teoria. Le domande di teoria sulla DP realmente comparse (formato Clementi) sono in [[#Teoria della DP uscita ai compiti|Teoria della DP uscita ai compiti]].
