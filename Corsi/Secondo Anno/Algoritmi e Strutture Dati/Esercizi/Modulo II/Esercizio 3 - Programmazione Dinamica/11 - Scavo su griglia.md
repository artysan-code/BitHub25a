---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 11 — Scavo su griglia
*(Esercizio 3 — compito del 02/02/2026 — 11 punti)*
> [!note] Traccia
> **Scavo.** Nella vostra città si scava per realizzare la linea D della metropolitana. A voi hanno affidato un particolare lavoro, quello di scavare in meno tempo possibile un tunnel che vi porti da una parte all'altra di due zone sotterranee che sono separate da una mole di terra che può essere rappresentata da una matrice di con $n$ righe e $m$ colonne.
> **Movimento.** Voi vi trovate nella casella $(1,1)$ e dovete arrivare in una qualsiasi casella della colonna $m$. Se siete in una casella $(i,j)$, la tecnologia del vostro scavatore vi permette di scavare ogni volta di una casella o verso destra (che libererà la casella $(i, j+1)$) o verso il basso (che libererà $(i+1, j)$). Liberare una casella richiede esattamente un'ora.
> **Reperti.** Ora, si sa che il sottosuolo della vostra città è ricco di reperti del passato, che è una cosa bella, in generale. Ma non per voi. Infatti, ogni volta che scavando dissotterrate un reperto, questo va catalogato dagli archeologi e la cosa richiede tempo e voi dovete aspettare prima di riprendere a scavare. I reperti possono essere di 3 tipi: anfora (A), bifora (B), colonna dorica (C).
> **Tempi di catalogazione.** Catalogare un'anfora richiede 3 ore mentre catalogare una bifora ne richiede 10. Se invece vi imbattreste in una colonna dorica... be', peggio per voi: perché in questo caso bisognerebbe interrompere i lavori per il rischio di rovinare una potenziale valle dei templi.
> **Richiesta.** Per fortuna avete a disposizione un macchinario che prima di scavare è stato in grado di capire cosa c'è in ogni casella. Progettate un algoritmo di programmazione dinamica che, presa la matrice, calcoli il tunnel migliore da scavare e il tempo necessario per farlo.
## Pattern
**Cammino minimo su un DAG implicito a griglia** — `OPT(i,j)` indicizzato sulla **posizione** $(i,j)$ raggiunta, l'oggetto che si muove nel tempo, non su una risorsa che si consuma. Parente stretto di [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)|Sequence Alignment]]: stessa coppia di indici che avanza sempre in avanti, ma qui il grafo è una griglia con mosse solo destra/basso invece di una coppia di sequenze.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,j) = \text{tempo minimo (in ore) per raggiungere la casella } (i,j) \text{ da } (1,1) \text{ lungo un cammino monotono}$$
Somma un'ora per ogni casella liberata più il tempo di catalogazione dei reperti incontrati lungo il cammino, oppure $+\infty$ se $(i,j)$ non è raggiungibile da nessun cammino ammissibile perché il cammino dovrebbe attraversare una colonna dorica.
I sottoproblemi sono $n \cdot m$, uno per ogni casella della matrice: $i=1,\ldots,n$ e $j=1,\ldots,m$. La coppia $(i,j)$ individua univocamente lo stato del cammino in quel punto.
### Casi base
$$\text{OPT}(1,1) = 0$$
La casella di partenza non viene scavata: ci si trova già lì, come dice la traccia, quindi non si paga né l'ora di scavo né un'eventuale catalogazione.
$$\text{OPT}(i,j) = +\infty \qquad \text{se tipo}(i,j) = \text{C}$$
Il valore neutro per una minimizzazione bloccata è $+\infty$, non $0$: la casella non è mai una scelta possibile, non semplicemente una scelta costosa.
### Ricorrenza
Per $(i,j) \neq (1,1)$ con tipo$(i,j) \neq \text{C}$, l'ultima mossa che porta a $(i,j)$ è una delle due seguenti.
**Arrivi da sinistra**, muovendoti verso destra dalla casella $(i,j-1)$. Paghi il costo ottimo per raggiungere $(i,j-1)$, un'ora per liberare $(i,j)$, e l'eventuale catalogazione del reperto lì trovato. Definito solo per $j>1$.
**Arrivi dall'alto**, muovendoti verso il basso dalla casella $(i-1,j)$. Paghi il costo ottimo per raggiungere $(i-1,j)$, un'ora per liberare $(i,j)$, e l'eventuale catalogazione. Definito solo per $i>1$.
$$\text{extra}(i,j) = \begin{cases} 0 & \text{casella vuota} \\ 3 & \text{anfora (A)} \\ 10 & \text{bifora (B)} \end{cases}$$
$$\text{OPT}(i,j) = \min\bigl\{\text{OPT}(i,j-1),\; \text{OPT}(i-1,j)\bigr\} + 1 + \text{extra}(i,j)$$
Sui bordi ($i=1$ o $j=1$) uno dei due termini non esiste ed è omesso dal minimo, non sostituito da un valore convenzionale.
### Giustificazione
**Esaustività.** Ogni casella diversa da $(1,1)$ è raggiunta da un'unica ultima mossa: o "destra" o "basso". Non esistono altre mosse ammesse dalla traccia, e le due non possono coincidere nella stessa mossa. Sui bordi resta un solo candidato, preso senza confronto.
**Assenza di un avversario.** L'algoritmo è l'unico decisore: sceglie liberamente fra le mosse disponibili quella di costo minimo. La ricorrenza è un $\min$ puro fra alternative, non un minimax fra due giocatori.
**Sottostruttura ottima.** Se il cammino ottimo fino a $(i,j)$ arriva da $(i,j-1)$, il tratto fino a $(i,j-1)$ deve essere a sua volta ottimo: sostituendolo con un cammino più corto si otterrebbe un cammino complessivo più corto fino a $(i,j)$, contro l'ipotesi di ottimalità. Lo stesso vale per l'arrivo dall'alto.
### Ordine di calcolo
Riga per riga dall'alto verso il basso, e all'interno di ogni riga colonna per colonna da sinistra a destra: $i$ crescente da $1$ a $n$, e per ogni $i$, $j$ crescente da $1$ a $m$.
Quando si calcola $\text{OPT}(i,j)$, la casella $\text{OPT}(i-1,j)$ (riga precedente, già completata) e $\text{OPT}(i,j-1)$ (stessa riga, colonna precedente, già calcolata in questa stessa passata) sono entrambe pronte. È lo stesso principio di ordinamento topologico di [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]] e [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|Knapsack]], applicato su due indici invece di uno.
### Risposta
$$\text{Risposta} = \min_{i=1,\ldots,n} \text{OPT}(i,m)$$
La destinazione è una qualsiasi casella della colonna $m$, quindi la risposta è il minimo su tutta l'ultima colonna, non il valore di una singola cella.
Se questo minimo vale $+\infty$, ogni cammino monotono da $(1,1)$ alla colonna $m$ è bloccato da almeno una colonna dorica: non esiste un tunnel realizzabile, e l'algoritmo deve riportarlo esplicitamente invece di restituire $+\infty$ come se fosse un numero di ore.
### Complessità
$\Theta(n \cdot m)$ celle, ciascuna risolta in $O(1)$ con un confronto fra al più due valori già noti più una somma. Tempo $\Theta(n \cdot m)$, spazio $\Theta(n \cdot m)$, riducibile a $\Theta(m)$ tenendo solo la riga corrente e quella precedente se non serve ricostruire il cammino.
È **polinomiale**, non pseudo-polinomiale: $n$ e $m$ sono le dimensioni dirette della matrice in input, non un valore-parametro come la capacità $W$ del Knapsack. L'istanza stessa occupa $\Theta(n \cdot m)$ celle, quindi $\Theta(n \cdot m)$ è lineare nella dimensione dell'input.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Tunnel-Minimo($n, m, \text{tipo}[1..n][1..m]$)}
\begin{algorithmic}
\State $\text{OPT}(1,1) \gets 0$
\For{$i \gets 1$ \To $n$}
  \For{$j \gets 1$ \To $m$}
    \If{$(i,j) = (1,1)$}
      \State \textbf{continua}
    \EndIf
    \If{$\text{tipo}[i][j] = \text{C}$}
      \State $\text{OPT}(i,j) \gets +\infty$
    \Else
      \State $\text{candidati} \gets \emptyset$
      \If{$j > 1$}
        \State aggiungi $\text{OPT}(i,j-1)$ a $\text{candidati}$
      \EndIf
      \If{$i > 1$}
        \State aggiungi $\text{OPT}(i-1,j)$ a $\text{candidati}$
      \EndIf
      \State $\text{OPT}(i,j) \gets \min(\text{candidati}) + 1 + \text{extra}(\text{tipo}[i][j])$
    \EndIf
  \EndFor
\EndFor
\State \Return $\min_{i=1,\ldots,n} \text{OPT}(i,m)$
\end{algorithmic}
\end{algorithm}
```
La traccia chiede anche il tunnel, non solo la sua durata: la ricorrenza va corredata da un puntatore ai predecessori, popolato ogni volta che si sceglie il minimo. Il cammino si ricostruisce risalendo dalla cella $(i^*,m)$ che realizza il minimo finale fino a $(1,1)$, simmetricamente a WIS e Knapsack.
## Note di studio
### Riconoscere il pattern
Le parole chiave che fanno scattare l'allarme "griglia" sono: **matrice** $n \times m$, mosse solo **destra o basso**, arrivo in **una qualsiasi casella** di un bordo. Non c'è una sequenza di oggetti da includere/escludere (niente WIS, niente Interval Scheduling) e non c'è un budget residuo da tracciare (niente Knapsack): l'oggetto che si muove nel tempo è la **posizione stessa nel piano**, la coppia $(i,j)$.
È il pattern del **cammino di costo minimo in un DAG implicito**: ogni casella è un nodo, ogni mossa destra/basso è un arco pesato (peso = un'ora più l'eventuale catalogazione della casella di arrivo), e il grafo è aciclico perché le mosse avanzano sempre, riga o colonna crescente, mai indietro.
È imparentato con [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)|Sequence Alignment]]: lì lo stato è una coppia di indici su due sequenze e ci si muove avanzando l'uno, l'altro o entrambi; qui lo stato è una coppia di indici sulla griglia e ci si muove avanzando uno solo dei due, mai entrambi insieme, perché lo scavatore libera una casella alla volta.
La casella con la **colonna dorica (C)** introduce un vincolo aggiuntivo: quella casella non può mai comparire in un cammino valido, quindi va trattata come nodo **irraggiungibile** (costo $+\infty$), non come un costo alto.
### Perché servono due indici
La domanda da farsi per prima è se basti un solo indice. **Tentativo ingenuo**: $\text{OPT}(j) = $ tempo minimo per raggiungere una qualche casella della colonna $j$, minimizzando su tutte le righe. Sembra economico, ma si rompe scrivendo la ricorrenza: per decidere il costo di arrivare in colonna $j+1$ serve sapere **da quale riga esatta** si è arrivati in colonna $j$, perché le caselle sottostanti e a destra di righe diverse contengono reperti diversi.
Con un solo indice $j$ quell'informazione è già persa, e non è un dettaglio: è esattamente ciò che serve per continuare. È lo stesso avvertimento del [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|Knapsack]] (l'indice da solo non basta, serve la capacità residua): il primo indice descrive quanto si è processato, non lo stato esatto in cui ci si trova.
Qui lo stato mancante è la **riga**. Servono due indici, $(i,j)$: non per un budget da tracciare come nel Knapsack, ma perché la posizione nel piano ha due gradi di libertà indipendenti.
### Esempio numerico
Griglia $3\times3$ (— = nessun reperto):

| | col 1 | col 2 | col 3 |
|---|---|---|---|
| riga 1 | — | A | — |
| riga 2 | B | — | C |
| riga 3 | — | — | — |

Tabella $\text{OPT}(i,j)$ risultante, in ore:

| | col 1 | col 2 | col 3 |
|---|---|---|---|
| riga 1 | 0 | 4 | 5 |
| riga 2 | 11 | 5 | $+\infty$ |
| riga 3 | 12 | 6 | 7 |

$\text{OPT}(1,2) = \text{OPT}(1,1) + 1 + 3 = 4$: si arriva da sinistra e si paga la catalogazione dell'anfora. $\text{OPT}(2,3) = +\infty$ perché quella casella è una colonna dorica, indipendentemente da come vi si arriverebbe.
La risposta è $\min\{\text{OPT}(1,3),\,\text{OPT}(2,3),\,\text{OPT}(3,3)\} = \min\{5,\,+\infty,\,7\} = 5$, ottenuta scavando $(1,1)\to(1,2)\to(1,3)$: due ore di scavo più tre ore per catalogare l'anfora incontrata in $(1,2)$.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Trattare la colonna dorica come un costo alto invece che come nodo irraggiungibile | la traccia dice esplicitamente di interrompere i lavori: non è un numero grande a piacere, è $+\infty$ |
| Scrivere $0$ come caso base neutro anche per le colonne doriche | in una minimizzazione il valore neutro per un caso non ammissibile è quello che perde ogni confronto, cioè $+\infty$, non $0$ |
| Calcolare $\min\{\text{OPT}(i,j-1),\text{OPT}(i-1,j)\}$ senza controllare i bordi | sulla prima riga non esiste "sopra", sulla prima colonna non esiste "sinistra": si legge fuori tabella se non si trattano come casi base separati |
| Dichiarare la complessità pseudo-polinomiale per analogia col Knapsack | qui $n$ e $m$ sono le dimensioni dirette della matrice in input, non un valore-parametro come $W$: $\Theta(nm)$ è polinomiale nella dimensione dell'input |
