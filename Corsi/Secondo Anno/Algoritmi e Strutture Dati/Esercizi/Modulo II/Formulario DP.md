---
tags:
  - algoritmi
  - dp
---
# Formulario — Programmazione Dinamica (Esercizio 3)
Dispensa compatta per l'**Esercizio 3** dello scritto di Modulo II, quello che comincia con «*Progettate un algoritmo di programmazione dinamica che …*». Contiene definizioni, metodo e catalogo dei pattern. I compiti veri svolti stanno in `DP - Esercizi d'esame/`; la teoria estesa in [[04 - Programmazione Dinamica I (Weighted Independent Set)]] e [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]].
Dal giugno 2024 **tutti** i compiti hanno un Es3 di progettazione DP, e il problema è **sempre nuovo**: una storiella inventata per l'occasione. Non serve ricordare i problemi già usciti — serve riconoscere il **pattern** e produrre la risposta nella forma attesa.
## Definizioni
**Programmazione dinamica.** Tecnica di progettazione che risolve un problema combinandone le soluzioni ottime di **sottoproblemi più piccoli**, ciascuno risolto **una volta sola** e memorizzato in tabella. Si applica quando valgono due condizioni: sottostruttura ottima e sovrapposizione dei sottoproblemi.
**Sottostruttura ottima.** Una soluzione ottima del problema contiene al suo interno soluzioni ottime dei sottoproblemi. Si argomenta con **cut & paste**: se la parte residua non fosse ottima, sostituendola con quella ottima si otterrebbe una soluzione complessiva migliore, contro l'ipotesi di ottimalità.
**Sovrapposizione dei sottoproblemi.** Lo stesso sottoproblema ricorre più volte nell'albero delle chiamate ricorsive. È ciò che distingue la DP dal divide-et-impera, dove i sottoproblemi sono disgiunti: qui memorizzare conviene, lì no.
**Equazione di Bellman.** La ricorrenza che esprime $\text{OPT}$ in funzione di sottoproblemi **strettamente più piccoli**, ottenuta enumerando i casi possibili per l'**ultima decisione**. I casi devono essere **esaustivi** (coprono tutte le mosse ammesse) e **mutuamente esclusivi**.
**Top-down (memoization) vs bottom-up.** Stessa ricorrenza, verso opposto: il top-down è ricorsione con cache e calcola solo i sottoproblemi che servono; il bottom-up riempie la tabella in un ordine che garantisce le dipendenze già pronte. All'esame si scrive il **bottom-up**.
**Pseudo-polinomialità.** Un algoritmo è pseudo-polinomiale se la sua complessità è polinomiale nel **valore** numerico di un input, ma esponenziale nella sua **lunghezza in bit**. Accade quando un indice della tabella è un valore in input (capacità $W$, batteria $\Delta$, budget $k$). Dichiararlo vale punti.
## Il metodo
### I sei punti della risposta
Una risposta completa contiene questi elementi, in quest'ordine. Conviene scriverli come titoletti sul foglio: rendono evidente al correttore che ci sono tutti.
1. **Definizione del sottoproblema** — a parole, senza ambiguità: «$\text{OPT}(\ldots)$ è il valore ottimo del problema ristretto a …». Va detto anche **quanti** sottoproblemi sono.
2. **Equazione di Bellman** — la ricorrenza, con i **casi base** espliciti.
3. **Giustificazione** — si elencano i casi possibili per l'ultima decisione, si osserva che sono esaustivi, e che in ciascuno il residuo è a sua volta un sottoproblema ottimo.
4. **Ordine di calcolo** — in quale ordine si riempie la tabella, perché ogni cella trovi già pronte quelle da cui dipende.
5. **Dove si legge la risposta** — quale cella contiene il risultato.
6. **Complessità** — tempo e spazio, giustificati come «numero di celle $\times$ costo per cella».

Se il tempo stringe l'ordine di scrittura è: **sottoproblemi → ricorrenza → complessità → pseudocodice**. Una definizione di sottoproblema sbagliata fa crollare tutto il resto; una definizione giusta con pseudocodice assente vale quasi tutto il punteggio.
### La domanda che trova il sottoproblema
Quando non si vede la ricorrenza, la domanda da farsi è sempre la stessa:
> **«Per decidere sull'elemento $i$, cosa avrei bisogno di sapere sul passato che $\text{OPT}(i-1)$ non mi dice?»**

La risposta determina **quanti indici** ha la tabella:

| Risposta alla domanda | Conseguenza |
|---|---|
| «niente, mi basta una scelta sì/no» | un indice: $\text{OPT}(i)$ |
| «quanta risorsa mi resta» (budget, batteria, capacità) | due indici: $\text{OPT}(i,b)$ |
| «cosa ho deciso sull'elemento precedente» (colore, energia, quanti consecutivi) | due indici: $\text{OPT}(i,s)$ |
| «a che punto sono nella seconda sequenza» | due indici: $\text{OPT}(i,j)$ |
| «da dove a dove arriva il pezzo ancora aperto» | due indici: $\text{OPT}(l,r)$ |
| «con quale elemento termina la soluzione parziale» | un indice, ma **ridefinito** con un vincolo |

Il numero di sottoproblemi deve restare **polinomiale**. Se il secondo indice fosse «quale sottoinsieme ho già scelto» sarebbe esponenziale: quasi sempre esiste un riassunto compatto — un contatore saturato a una soglia, un colore, una capacità — che basta per decidere. Trovarlo *è* l'esercizio.
## I pattern
| Pattern | Segnale nella traccia | Tabella | Rappresentante |
|---|---|---|---|
| **Scelta binaria su sequenza** | elementi in fila, «prendo o non prendo», prenderne uno esclude i vicini | $\text{OPT}(i)$ | WIS su cammino |
| **Scelta binaria che esclude un blocco** | prendere un elemento esclude un **intervallo** di posizioni, non solo il vicino | $\text{OPT}(i)$ con salto calcolato | Weighted Interval Scheduling |
| **Scelta binaria con risorsa** | c'è un budget, una batteria, una capacità da non superare | $\text{OPT}(i,b)$ | Knapsack 0/1 |
| **Stato aggiuntivo** | una condizione locale con poche configurazioni: colore, energia, contatore di consecutivi | $\text{OPT}(i,s)$ | House Coloring |
| **DP su intervallo** | si consuma **da entrambi gli estremi**; il residuo è una finestra, non un prefisso | $\text{OPT}(l,r)$ | Segmented Least Squares |
| **Due sequenze / griglia** | l'input sono **due** sequenze, oppure una matrice percorsa avanti-e-giù | $\text{OPT}(i,j)$ | Sequence Alignment |
| **Vincolo «termina qui»** | il primo tentativo non chiude: servirebbe sapere con cosa finisce la soluzione parziale | $\text{OPT}(i)$ ridefinito | LIS |

Sui 12 compiti dal giugno 2024 l'input è **quasi sempre una sequenza lineare** — grafo a cammino e griglia inclusi, sono sequenze travestite. Non aspettarsi alberi o grafi generici. Inoltre non è mai capitato che due appelli consecutivi avessero lo stesso pattern.
### Due indici non significano Knapsack
In $\text{OPT}(i,b)$ il secondo indice è una **risorsa che si consuma**: la complessità dipende dal suo valore numerico, quindi è **pseudo-polinomiale**. In $\text{OPT}(l,r)$ i due indici sono gli **estremi di un segmento**: dipendono solo da $n$, e la complessità è $\Theta(n^2)$, **polinomiale piena**. Scambiare le due cose è un errore da punti.
### Il minimax non è un pattern di questo corso
Alcune tracce mettono in scena più persone che prendono a turno da una sequenza, e sembrano il gioco a due giocatori che si risolve con una ricorrenza **max-min**. La verifica è sempre la stessa: **si guarda la funzione obiettivo**. Se conta solo ciò che prende il protagonista, e le mosse degli altri sono una regola fissa e non una scelta, allora non c'è avversario da minimizzare e la ricorrenza è **max-max**. Un $\min$ scritto per sbaglio cambia il risultato e invalida l'esercizio.
## Tecniche ricorrenti
**Contatore saturato.** Quando un bonus dipende da quanti elementi consecutivi si sono presi, il contatore va **saturato** alla soglia utile (es. valori $\{0,1,2,3^+\}$): resta di dimensione costante e non fa crescere lo stato con $n$.
**Sconto retroattivo.** Quando un premio si acquisisce solo al completarsi di una configurazione, si **paga il prezzo pieno** a ogni passo e si **applica il rimborso** nel momento in cui la soglia viene raggiunta. È la mossa che rende locale una condizione apparentemente non locale.
**Accorpare due mosse in una transizione.** Se dopo la propria decisione l'ambiente reagisce in modo deterministico, si accorpano decisione e reazione in un'unica transizione: si evita un indice di stato in più.
**Ricostruzione della soluzione.** La tabella contiene un **numero**. Per ottenere l'insieme ottimo si riparte dalla cella finale e a ogni passo si guarda quale caso della ricorrenza ha realizzato l'ottimo, spostandosi nella cella corrispondente. Costo $O(n)$ aggiuntivo, da fare solo se richiesto.
## Errori tipici
| Errore | Perché costa |
|---|---|
| Definizione vaga: «$\text{OPT}(i)$ = la soluzione ottima fino a $i$» | non dice *quale* problema ristretto né *cosa* rappresenta il valore |
| Casi base dimenticati | sono metà del punto 2; vanno scritti anche quando valgono $0$ |
| Caso base scritto come uguaglianza invece che disuguaglianza | se la ricorrenza salta più di una posizione, restano celle indefinite |
| Indice sbagliato da cui si pesca | nel Knapsack si guarda $w - w_i$, non $w$; nel WIS si salta a $j-2$, non a $j-1$ |
| Casi non esaustivi | una mossa ammessa dalla traccia che nessun caso copre falsa l'ottimo |
| Confondere il valore con la soluzione | la tabella contiene un numero; ricostruire l'insieme è un passo separato |
| Complessità senza giustificazione | va detto «$n^2$ celle, $O(1)$ per cella», non solo $\Theta(n^2)$ |
| Pseudo-polinomiale scambiata per polinomiale | se un indice è un valore numerico in input, dirlo vale punti |
