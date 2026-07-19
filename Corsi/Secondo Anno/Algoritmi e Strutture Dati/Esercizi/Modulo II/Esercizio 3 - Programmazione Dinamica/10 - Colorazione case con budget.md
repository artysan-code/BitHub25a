---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 10 — Colorazione delle case con budget di rosso
*(Esercizio 3 — compito del 23/09/2025 — 11 punti)*
> [!note] Traccia
> In una via ci sono $n$ case, numerate da $1$ a $n$, che devi ridipingere. I colori a disposizione sono tre: rosso, verde e blu. Per ogni casa $i$ e colore $x$ conosci il costo $c(i, x)$ che sosterresti se colorassi la casa di quel colore.
> **Vincoli.** Non puoi colorare case adiacenti con lo stesso colore. Inoltre non hai molta vernice rossa a disposizione: puoi colorare di rosso al più $k$ case.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che calcoli il costo minimo per colorare le case. Si discuta la complessità temporale della soluzione proposta.
## Pattern
**DP multi-dimensionale — House Coloring + Knapsack.** Al colore dell'ultima casa (lo stato locale di [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#House Coloring (esercizio)|House Coloring]]) si affianca un contatore di case rosse usate (una risorsa globale come nel [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]]). Sono due vincoli indipendenti — uno locale, uno globale — e ciascuno richiede la propria dimensione nella tabella $\text{OPT}(i,c,b)$.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,c,b) = \text{costo minimo per colorare le prime } i \text{ case, con la casa } i \text{ colorata esattamente di } c \in \{R,G,B\} \text{ e usando esattamente } b \text{ case rosse fra le prime } i$$
Gli indici sono tre e vale la pena elencarli, perché è la loro combinazione a rendere il sottoproblema ben definito. **$i$**, da $1$ a $n$, è quante case del prefisso sono già state colorate. **$c$** è il colore assegnato all'ultima casa del prefisso, quella in posizione $i$: serve per verificare la compatibilità con la casa $i+1$, esattamente come in House Coloring. **$b$**, da $0$ a $\min(i,k)$, è quante di quelle $i$ case sono state colorate di rosso: serve per verificare, alla fine, che il totale non superi $k$. Il limite $\min(i,k)$ e non semplicemente $k$ è già un'osservazione utile per la complessità: $b$ non ha senso oltre il numero di case già colorate, né oltre il budget stesso.
I sottoproblemi distinti sono $n \cdot 3 \cdot (k+1)$: per ogni casa, tre scelte di colore, e per ognuna un contatore che va da $0$ a $k$.
### Casi base
$$\text{OPT}(1,\text{R},1) = c(1, \text{R}) \qquad \text{OPT}(1,\text{G},0) = c(1, \text{G}) \qquad \text{OPT}(1,\text{B},0) = c(1, \text{B})$$
$$\text{tutte le altre combinazioni } \text{OPT}(1,c,b) = +\infty$$
La prima casa non ha una casa precedente con cui confrontarsi. Colorandola di rosso si usa **esattamente una** casa rossa: l'unica cella sensata per il colore R è quella con $b=1$, non $b=0$. Colorandola di verde o di blu si usano **zero** case rosse: l'unica cella sensata è quella con $b=0$. Ogni altra combinazione — per esempio $\text{OPT}(1,\text{R},0)$, "casa 1 rossa ma zero rosse usate" — descrive una situazione impossibile e va marcata come tale.
La tabella **minimizza** un costo, quindi il valore neutro per "impossibile" è $+\infty$, mai $0$: se fosse $0$ verrebbe scelto in un $\min$ successivo come se fosse più conveniente di qualunque costo reale, corrompendo silenziosamente la tabella a valle con colorazioni che non rispettano i vincoli. È l'opposto di una tabella che massimizza un guadagno, dove il valore neutro per "nessuna scelta disponibile" è $0$.
La convenzione $+\infty$ vale per ogni $i$, non solo per il caso base: in generale $\text{OPT}(i,c,b) = +\infty$ per ogni $b > i$ (non si possono avere più case rosse di quante colorate finora) e per ogni $b<0$. Questo garantisce che la ricorrenza sia ben definita al bordo superiore di $b$: se $i \le k$, il caso "casa $i$ verde" con $b=i$ richiede $\text{OPT}(i-1,\text{R},i)$, cella mai assegnata dal caso generale — per convenzione vale $+\infty$, correttamente, perché con la casa $i$ non rossa non si possono avere $i$ case rosse fra le prime $i$.
### Ricorrenza
Per $i \ge 2$ la casa $i$ ha esattamente uno fra tre colori possibili: è una scelta a tre vie, non binaria come nel Knapsack.
**Colori la casa $i$ di rosso.** La casa $i-1$ non può essere rossa a sua volta (vincolo di adiacenza): deve essere verde o blu, e prendo il migliore fra i due. Colorare la casa $i$ di rosso consuma inoltre una unità di budget: se fra le prime $i$ case ce ne sono $b$ rosse e una di queste è la casa $i$, fra le prime $i-1$ ce n'erano $b-1$ — da qui il salto da $b$ a $b-1$. Se $b=0$ il caso è impossibile: $\text{OPT}(i,\text{R},0) = +\infty$.
**Colori la casa $i$ di verde.** Non consuma budget di rosso: il contatore $b$ resta identico. La casa $i-1$ deve solo essere diversa dal verde: rossa o blu, prendo il migliore.
**Colori la casa $i$ di blu.** Simmetrico al caso precedente: nessun consumo di budget, la casa $i-1$ deve essere rossa o verde.
$$\text{OPT}(i,\text{R},b) = c(i,\text{R}) + \min\{\text{OPT}(i-1,\text{G},b-1),\; \text{OPT}(i-1,\text{B},b-1)\} \quad (b\ge1)$$
$$\text{OPT}(i,\text{G},b) = c(i,\text{G}) + \min\{\text{OPT}(i-1,\text{R},b),\; \text{OPT}(i-1,\text{B},b)\}$$
$$\text{OPT}(i,\text{B},b) = c(i,\text{B}) + \min\{\text{OPT}(i-1,\text{R},b),\; \text{OPT}(i-1,\text{G},b)\}$$
Forma compatta.
$$\text{OPT}(i,c,b) = c(i,c) + \begin{cases} \min\{\text{OPT}(i-1,c',b-1) : c' \neq \text{R}\} & \text{se } c = \text{R} \text{ e } b \ge 1 \\[4pt] \min\{\text{OPT}(i-1,c',b) : c' \neq c\} & \text{se } c \in \{\text{G},\text{B}\} \\[4pt] +\infty & \text{se } c=\text{R} \text{ e } b=0 \end{cases}$$
### Giustificazione
**Esaustività.** La casa $i$ ha, per costruzione del problema, esattamente uno dei tre colori: non può essere contemporaneamente rossa e verde, e non esiste un quarto colore. I tre casi coprono dunque tutte le possibilità e sono mutuamente esclusivi.
**Il $\min$ interno non è una quarta scelta.** All'interno di ciascun caso, il $\min$ fra le due tabelle di colore compatibile per la casa $i-1$ non è un'ulteriore decisione sulla casa corrente: è l'esplorazione di tutte le colorazioni ammissibili della casa precedente, già risolte in modo ottimo dal sottoproblema più piccolo.
**Sottostruttura ottima.** Fissati il colore $c$ della casa $i$ e il numero di rosse $b$ usate fra le prime $i$, il costo delle prime $i-1$ case deve essere minimo fra tutte le colorazioni compatibili con $c$ e con $b$ (o $b-1$) rosse residue: se non lo fosse, sostituendo quel prefisso con la sua colorazione ottima si otterrebbe un costo totale minore, contro l'ottimalità della soluzione di partenza.
### Ordine di calcolo
Si procede per $i$ crescente da $2$ a $n$, dopo aver riempito il caso base $i=1$. Per ogni $i$ si riempiono tutte le celle $\text{OPT}(i,c,b)$ per $c \in \{\text{R},\text{G},\text{B}\}$ e $b = 0,\ldots,\min(i,k)$: l'ordine fra colori e fra valori di $b$ non conta, perché la ricorrenza a livello $i$ dipende solo da celle a livello $i-1$, mai da altre celle allo stesso livello. L'unico vincolo è che $i-1$ sia già completamente calcolato, garantito scandendo $i$ in ordine crescente.
### Risposta
$$\min_{c \in \{\text{R},\text{G},\text{B}\}} \ \min_{0 \le b \le k} \ \text{OPT}(n,c,b)$$
Il minimo va preso su tutte le celle dell'ultima riga, qualunque sia il colore finale e qualunque sia il numero di case rosse effettivamente usate, purché non superi $k$. Il vincolo della traccia è "al più $k$", non "esattamente $k$": una colorazione che usa meno rosso del budget resta ammissibile e può essere quella di costo minimo, come nell'esempio numerico.
### Complessità
La tabella ha $i$ da $1$ a $n$, $c$ su $3$ valori, $b$ da $0$ a $\min(i,k) \le k$: al più $n \cdot 3 \cdot (k+1)$ celle, ciascuna calcolata in $O(1)$. Il costo totale è $\Theta(n \cdot k)$ tempo e altrettanto spazio.
Questo conto è, nella forma, identico a quello del Knapsack ($\Theta(nW)$), e verrebbe naturale concludere per analogia che la complessità sia pseudo-polinomiale in $k$. C'è però una differenza sostanziale: nel Knapsack la capacità $W$ è un dato indipendente da $n$, può crescere arbitrariamente senza legame col numero di oggetti, ed è per questo che $\Theta(nW)$ è davvero pseudo-polinomiale.
Qui invece $b$ conta quante case fra le prime $i$ sono rosse, e non può mai superare $i$, che a sua volta non supera $n$: un valore di $k$ superiore a $n$ non aggiunge alcun vincolo reale, perché non è comunque possibile colorare più di $n$ case di rosso. Si può quindi sempre sostituire $k$ con $\min(k,n)$:
$$\Theta\bigl(n \cdot \min(k,n)\bigr) = O(n^2)$$
Un limite **polinomiale** in $n$, indipendente da quanto grande sia il valore numerico di $k$ nell'istanza: qui il budget è per natura un sottoinsieme delle case stesse, quindi è intrinsecamente limitato da $n$, a differenza della capacità del Knapsack, che è una quantità fisica del problema senza ragione di essere limitata da $n$.
Vale la pena scrivere esplicitamente $\Theta(nk)$ come prima risposta immediata — è ciò che il professore si aspetta di vedere per primo — per poi aggiungere l'osservazione sul limite $\min(k,n)$ come raffinamento: è il tipo di dettaglio che distingue una risposta completa su una sotto-domanda di complessità.
Come nel Knapsack e in House Coloring, ogni riga $i$ dipende solo dalla riga $i-1$: per il solo valore ottimo bastano due piani $3 \times (k+1)$ in memoria, portando lo spazio a $O(k)$; per ricostruire la colorazione serve invece l'intera tabella.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Colora-Case-Budget($n, k, c$)}
\begin{algorithmic}
\State $\text{OPT}(1,\text{R},1) \gets c(1,\text{R})$
\State $\text{OPT}(1,\text{G},0) \gets c(1,\text{G})$
\State $\text{OPT}(1,\text{B},0) \gets c(1,\text{B})$
\State tutte le altre entrate di $\text{OPT}(1,\cdot,\cdot) \gets +\infty$
\For{$i \gets 2$ \To $n$}
  \For{$b \gets 0$ \To $\min(i,k)$}
    \If{$b \geq 1$}
      \State $\text{OPT}(i,\text{R},b) \gets c(i,\text{R}) + \min\{\text{OPT}(i-1,\text{G},b-1),\, \text{OPT}(i-1,\text{B},b-1)\}$
    \Else
      \State $\text{OPT}(i,\text{R},b) \gets +\infty$
    \EndIf
    \State $\text{OPT}(i,\text{G},b) \gets c(i,\text{G}) + \min\{\text{OPT}(i-1,\text{R},b),\, \text{OPT}(i-1,\text{B},b)\}$
    \State $\text{OPT}(i,\text{B},b) \gets c(i,\text{B}) + \min\{\text{OPT}(i-1,\text{R},b),\, \text{OPT}(i-1,\text{G},b)\}$
  \EndFor
\EndFor
\State \Return $\min_{c \in \{\text{R},\text{G},\text{B}\}} \min_{0 \leq b \leq k} \text{OPT}(n,c,b)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Due parole chiave della traccia portano a due pattern diversi, che qui convivono nello stesso esercizio.
**"Case adiacenti"** insieme a **"tre colori"** e **"costo $c(i,x)$"** è, testualmente, il problema [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#House Coloring (esercizio)|House Coloring]]: una casa per volta, tre scelte a ogni casa, vincolo solo con la casa precedente.
**"Non hai molta vernice rossa"** e **"al più $k$ case"** è invece un vincolo di budget globale, la stessa idea che nel [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack]] limita quanta capacità dello zaino si può spendere — qui la "risorsa" è il numero di case rosse contate dall'inizio alla fine, non solo localmente.
Questo esercizio non è un pattern nuovo: è la combinazione di due pattern noti, lo "stato che ci si porta dietro" (il colore della casa precedente) e la "scelta con risorsa globale" (il budget residuo di rosso), che devono convivere nella stessa tabella. Il segnale linguistico che separa i due vincoli è netto: "case adiacenti" è locale (riguarda due case consecutive), "al più $k$ case rosse" è globale (riguarda l'intera via, dalla prima all'ultima casa).
### Perché serve il contatore di rosso
La domanda da farsi è sempre la stessa: per decidere il colore della casa $i$, cosa serve sapere del passato che una tabella a un solo indice non dice?
**Tentativo ingenuo.** Si potrebbe applicare la soluzione di House Coloring così com'è, con tre array $R[i]$, $G[i]$, $B[i]$ (costo minimo per le prime $i$ case con la casa $i$ rispettivamente rossa, verde o blu) e la ricorrenza $R[i] = c(i,\text{rosso}) + \min\{G[i-1], B[i-1]\}$, analoga per $G[i]$ e $B[i]$.
**Perché si rompe.** Con $n=3$ e $k=1$, costi che rendono R, G, R localmente la più economica (per esempio $c(1,\text{R})=1$, $c(2,\text{G})=1$, $c(3,\text{R})=1$, tutti gli altri costi alti): la sequenza rispetta il vincolo di adiacenza ed è quella che $R[i], G[i], B[i]$ troverebbero come migliore, perché quella tabella non sa contare quante volte è stato usato il rosso in tutto il prefisso — sa solo se l'ultima casa è rossa o no. Ma R, G, R usa il rosso due volte, e con $k=1$ è inammissibile: un bug silenzioso, non un errore che si manifesta con un crash.
**Cosa serve davvero.** Oltre al colore dell'ultima casa, quante case sono già state colorate di rosso fra le prime $i$: una terza dimensione, un contatore che accompagna sia $i$ sia il colore, come la capacità residua nel Knapsack. Non basta un solo bit "l'ultima casa era rossa?": quel bit dice qualcosa sul vincolo di adiacenza, già gestito dalle tre tabelle separate, ma nulla sul totale cumulativo di rosso usato dall'inizio. Il vincolo "al più $k$ case rosse" riguarda l'intera sequenza, non la sola casa precedente: per questo serve un contatore, non un bit.
### Esempio numerico
$n=3$, $k=1$. Costi: $c(1,\text{R})=1,\ c(1,\text{G})=5,\ c(1,\text{B})=5$; $c(2,\text{R})=1,\ c(2,\text{G})=1,\ c(2,\text{B})=5$; $c(3,\text{R})=1,\ c(3,\text{G})=1,\ c(3,\text{B})=1$.

| $i$ | $\text{OPT}(i,\text{R},\cdot)$ | $\text{OPT}(i,\text{G},\cdot)$ | $\text{OPT}(i,\text{B},\cdot)$ |
|---|---|---|---|
| $1$ | $b{=}1:\,1$ | $b{=}0:\,5$ | $b{=}0:\,5$ |
| $2$ | $b{=}1:\,6$ | $b{=}0:\,6,\ b{=}1:\,2$ | $b{=}0:\,10,\ b{=}1:\,6$ |
| $3$ | $b{=}1:\,7$ | $b{=}0:\,11,\ b{=}1:\,7$ | $b{=}0:\,7,\ b{=}1:\,3$ |

Il minimo su tutte le celle di $i=3$ è $3$, raggiunto da $\text{OPT}(3,\text{B},1)$: colorazione R, G, B (rosso solo sulla casa $1$, la più economica da colorare di rosso), costo $1+1+1=3$. Nessuna colorazione ammissibile con al più una casa rossa costa meno.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Dimenticare la terza dimensione e riusare House Coloring puro | costruire un controesempio (come in "Perché serve il contatore di rosso") in cui la colorazione localmente più economica usa il rosso più volte di quante il budget lo permetta |
| Inizializzare i casi base impossibili a $0$ invece che a $+\infty$ | chiedersi se la cella rappresenta una situazione che può davvero accadere: se no, il valore neutro per un $\min$ è $+\infty$, mai $0$ |
| Sbagliare lo spostamento dell'indice $b$ quando si colora di rosso (dimenticare il $-1$) | contare a mano, su un esempio con $k$ piccolo, quante case rosse compaiono nella colorazione che la ricorrenza sbagliata produrrebbe |
| Dichiarare la complessità pseudo-polinomiale per analogia col Knapsack | chiedersi se il parametro sospetto ($k$) è per natura limitato da $n$: se sì, sostituirlo con $\min(k,n)$ prima di concludere |
| Leggere la risposta in $\text{OPT}(n,c,k)$ invece che nel minimo su tutti i $b \le k$ | rileggere la traccia — "al più $k$", non "esattamente $k$" — e verificare che l'algoritmo esplori tutti i valori di $b$ da $0$ a $k$ |
