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
# Esercizio 3 — catalogo dei pattern DP
L'Esercizio 3 del Modulo II è **sempre** la progettazione di un algoritmo di programmazione dinamica su un problema inedito. «Inedito» però vale solo per l'ambientazione: sotto il travestimento ci sono **otto famiglie** di sottoproblema, tutte derivate dai problemi delle slide `04`-`06`, e un piccolo repertorio di modifiche che il prof. Gualà applica al problema noto per renderlo nuovo. Questo file mappa le due cose: le famiglie (cos'è la tabella) e i twist (cosa è stato cambiato rispetto al problema di riferimento).
Il *metodo* — i cinque passi, come si legge la risposta, pseudo-polinomialità — sta in [[Formulario Modulo II#04 · Programmazione Dinamica — impianto dell'Esercizio 3]] e non si ripete qui. Qui c'è il **riconoscimento**: data una traccia mai vista, qual è la forma della tabella e perché.
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

| Risposta | Conseguenza |
|---|---|
| nulla: la scelta esclude una finestra di ampiezza **fissa** | **F1** — un indice, ricorrenza a due-tre rami, $\Theta(n)$ |
| **quale** era il predecessore, perché il contributo di $i$ dipende da lui | **F2** — sottoproblema «che termina esattamente in $i$», $\max$ interno su tutti i $j<i$, $O(n^2)$ |
| quale era il predecessore, ma è **univoco** e calcolabile in $O(1)$ | **F3** — $p(j)$ esplicito, si torna a $\Theta(n)$ |
| **quanta** risorsa ho già speso (budget, batteria, contatore, valore accumulato) | **F4** — secondo indice **numerico** |
| **com'è finita** la soluzione parziale (colore, quanti contigui, flag usa-e-getta) | **F5** — secondo indice a **dominio fisso** |

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
