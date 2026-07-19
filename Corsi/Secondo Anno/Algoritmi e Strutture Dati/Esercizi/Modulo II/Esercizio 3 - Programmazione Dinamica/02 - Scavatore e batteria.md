---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 02 — Scavatore e batteria
*(Esercizio 3 — compito del 16/07/2024 — 11 punti)*
> [!note] Traccia
> Controlli uno scavatore robotico utilizzato per estrarre oro da una miniera. La miniera è divisa in $n$ tratte disposte linearmente. Conosci la quantità di oro seppellita sotto ogni tratta: se scavi nella tratta $i$ trovi $v_i$ unità di oro. Lo scavatore ha una batteria di $\Delta$ unità ed è inizialmente posizionato sulla tratta $1$ con la batteria completamente carica.
> **Regole.** I controlli permettono due manovre. Muovere lo scavatore in avanti di una o due posizioni — dalla tratta $i$ ci si può spostare nella tratta $i+1$ o $i+2$ — consuma $s$ unità di batteria, indipendentemente dal fatto che ci si sposti di $1$ o di $2$. Scavare nella tratta $i$ estrae le $v_i$ unità di oro sotto di essa e consuma $t$ unità di batteria. Si assume $t > s$.
> **Richiesta.** Progetta un algoritmo di programmazione dinamica che calcoli il massimo numero di unità di oro estraibili dalla miniera. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**Knapsack 0/1 con budget che si consuma** — `OPT(i,b)` indicizzato su tratta e batteria residua, imparentato col [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]]. A differenza del Knapsack puro, qui anche il solo spostarsi costa batteria: il prezzo di scavare la tratta $i$ include tutte le manovre di movimento compiute per raggiungerla, non solo il costo dello scavo.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,b) = \text{massimo oro estraibile proseguendo dalla tratta } i \text{ in poi, con batteria residua } b \text{ e senza aver ancora scavato in } i$$
I sottoproblemi sono $(n+2)\cdot(\Delta+1)$: l'indice $i$ va da $1$ a $n$ per le tratte reali, più due sentinelle $i=n+1$ e $i=n+2$; l'indice $b$ va da $0$ a $\Delta$ ed è la batteria residua in quel momento.
Non serve un terzo indice "ho già scavato qui?": ogni ramo della ricorrenza lascia la tratta $i$ per non tornarci più, e un secondo scavo nella stessa tratta non frutterebbe altro oro.
### Casi base
$$\text{OPT}(n+1,b) = 0 \qquad \text{per ogni } b \in \{0,\ldots,\Delta\}$$
$$\text{OPT}(n+2,b) = 0 \qquad \text{per ogni } b \in \{0,\ldots,\Delta\}$$
Le tratte $n+1$ e $n+2$ non esistono: sono sentinelle per "sono uscito dalla miniera". Servono entrambe perché dalla tratta $i$ la ricorrenza salta a $i+1$ o a $i+2$; da $i=n$ un salto di due punta a $n+2$, da $i=n-1$ un salto di due punta a $n+1$.
Il valore neutro è $0$, non $+\infty$: la tabella accumula un massimo, e "zero oro raccolto da qui in poi" è un valore legittimo, sempre raggiungibile fermandosi subito — non un valore da scartare come in una minimizzazione.
### Ricorrenza
Dalla tratta $i$, con $b$ unità di batteria residue, le manovre disponibili sono quelle della traccia: fermarsi, spostarsi (di $1$ o $2$, costo $s$) o scavare (costo $t$). Combinando "scavo sì/no" con "poi mi fermo / mi sposto di $1$ / mi sposto di $2$" si ottengono sei mosse.
**Non scavo e mi fermo.** Interrompo l'estrazione da $i$ in poi senza consumare altra batteria; sempre disponibile, qualunque sia $b$.
**Non scavo e mi sposto di $1$.** Pago $s$ e proseguo dalla tratta $i+1$, senza aver raccolto nulla da $i$; richiede $b \geq s$.
**Non scavo e mi sposto di $2$.** Identico, ma saltando a $i+2$: il costo resta $s$, non $2s$, perché la traccia fissa un unico costo per la manovra di spostamento, indipendente dalla distanza percorsa. Richiede $b \geq s$.
**Scavo e mi fermo.** Spendo $t$ per estrarre $v_i$ e poi mi fermo, senza pagare lo spostamento; richiede $b \geq t$.
**Scavo e mi sposto di $1$.** Spendo $t$ per estrarre $v_i$, poi $s$ per spostarmi a $i+1$; richiede $b \geq t+s$.
**Scavo e mi sposto di $2$.** Identico, saltando a $i+2$; richiede $b \geq t+s$.
$$\text{OPT}(i,b) = \max \begin{cases} 0 \\[4pt] \text{OPT}(i+1,b-s) & \text{se } b \geq s \\[4pt] \text{OPT}(i+2,b-s) & \text{se } b \geq s \\[4pt] v_i & \text{se } b \geq t \\[4pt] v_i + \text{OPT}(i+1,b-t-s) & \text{se } b \geq t+s \\[4pt] v_i + \text{OPT}(i+2,b-t-s) & \text{se } b \geq t+s \end{cases}$$
### Giustificazione
**Esaustività e mutua esclusione.** Dalla tratta $i$ esistono solo due manovre, muoversi e scavare, e nessuna terza opzione: non si può attendere senza fare nulla, né scavare due volte la stessa tratta. Ogni strategia da $(i,b)$ deve prima o poi fermarsi, oppure eseguire come primo passo una delle altre quattro manovre; le sei alternative coprono per intero il prodotto "scavo/non scavo" $\times$ "fermo/sposto di $1$/sposto di $2$", senza sovrapposizioni.
**Sottostruttura ottima.** Qualunque sia la prima mossa scelta da $(i,b)$, ciò che resta da fare è un'istanza più piccola dello stesso problema, con tratta e batteria residue minori. Se il residuo non fosse risolto in modo ottimo, sostituendolo con la strategia ottima per quel residuo si otterrebbe più oro complessivo, contro l'ipotesi che la strategia di partenza fosse ottima.
### Ordine di calcolo
Ogni cella $\text{OPT}(i,b)$ dipende solo da celle con indice di tratta maggiore, $\text{OPT}(i+1,\cdot)$ e $\text{OPT}(i+2,\cdot)$: si riempie quindi per $i$ decrescente, da $n$ a $1$, con le righe sentinella $n+1$ e $n+2$ inizializzate a $0$ prima di cominciare. Per ogni $i$ l'indice $b$ può essere calcolato in un ordine qualunque da $0$ a $\Delta$, perché nessuna cella dipende da un'altra con lo stesso $i$.
Questa direzione è opposta a quella del Knapsack "da manuale" ([[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|nota 05]]), dove si riempie per $i$ crescente: lì $\text{OPT}(i,w)$ è definito come "usando i primi $i$ oggetti", a prefisso; qui $\text{OPT}(i,b)$ è "proseguendo dalla tratta $i$ in poi", a suffisso, coerente col fatto che lo scavatore si muove solo in avanti.
### Risposta
$$\text{OPT}(1,\Delta)$$
Lo scavatore parte sulla tratta $1$ con la batteria completamente carica, prima di aver scavato lì: è esattamente lo stato descritto dalla definizione del sottoproblema.
### Complessità
La tabella ha $(n+2)(\Delta+1) = \Theta(n\Delta)$ celle, ciascuna calcolata in $O(1)$ con un massimo fra al più sei termini. Tempo $\Theta(n\Delta)$, spazio $\Theta(n\Delta)$ — riducibile a $O(\Delta)$ tenendo in memoria solo le ultime due righe, come nel WIS su cammino.
$\Theta(n\Delta)$ è **pseudo-polinomiale**, non polinomiale: la dimensione dell'istanza è $O(n\log\Delta + n\log v_{\max})$ bit, ma $\Delta$ compare linearmente nel costo come valore, non come numero di bit. Se $\Delta = 2^k$, l'algoritmo esegue $\Theta(n\cdot 2^k)$ operazioni, esponenziale nella dimensione reale (in bit) di $\Delta$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{Scavatore($v[1 \ldots n], s, t, \Delta$)}
\begin{algorithmic}
\For{$b \gets 0$ \To $\Delta$}
  \State $\text{OPT}(n+1,b) \gets 0$
  \State $\text{OPT}(n+2,b) \gets 0$
\EndFor
\For{$i \gets n$ downto $1$}
  \For{$b \gets 0$ \To $\Delta$}
    \State $\text{migliore} \gets 0$ \Comment{non scavo, mi fermo}
    \If{$b \geq s$}
      \State $\text{migliore} \gets \max(\text{migliore},\; \text{OPT}(i+1,b-s))$ \Comment{mi sposto di 1}
      \State $\text{migliore} \gets \max(\text{migliore},\; \text{OPT}(i+2,b-s))$ \Comment{mi sposto di 2}
    \EndIf
    \If{$b \geq t$}
      \State $\text{migliore} \gets \max(\text{migliore},\; v[i])$ \Comment{scavo e mi fermo}
    \EndIf
    \If{$b \geq t+s$}
      \State $\text{migliore} \gets \max(\text{migliore},\; v[i] + \text{OPT}(i+1,b-t-s))$ \Comment{scavo, poi mi sposto di 1}
      \State $\text{migliore} \gets \max(\text{migliore},\; v[i] + \text{OPT}(i+2,b-t-s))$ \Comment{scavo, poi mi sposto di 2}
    \EndIf
    \State $\text{OPT}(i,b) \gets \text{migliore}$
  \EndFor
\EndFor
\State \Return $\text{OPT}(1,\Delta)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Le parole chiave che accendono il pattern sono tre: **batteria** (una quantità limitata posseduta), **consuma** (ogni manovra la intacca), **massimo** (si ottimizza senza sforare il limite). È la firma del [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]]: un budget — qui $\Delta$ — che non si può superare, e ogni decisione lo consuma. Diverso dal segnale del [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS su cammino]], dove il vincolo è strutturale (l'adiacenza), non un contatore.
Il Knapsack puro costa un oggetto solo del suo peso $w_i$. Qui invece anche **raggiungere** una tratta ha un costo: ogni spostamento consuma $s$, quindi il prezzo reale di scavare la tratta $i$ include tutte le manovre fatte per arrivarci, non solo $t$. È un ibrido fra il Knapsack e l'avanzamento a salti del WIS su cammino, con salto di lunghezza variabile ($1$ o $2$) ma costo fisso $s$.
### Perché serve una seconda dimensione
Definire $\text{OPT}(i)$ come massimo oro proseguendo da $i$, ignorando la batteria, sembra bastare: alla tratta $i$ le alternative sono scavare o non scavare. Il tentativo si rompe nel decidere se una mossa è ammissibile: quanta batteria resta all'arrivo su $i$ dipende da **tutte** le manovre già fatte prima, e due strategie possono raggiungere la stessa tratta con residui diversi che $\text{OPT}(i)$ da solo non distingue.
Manca l'informazione «quanta batteria resta ora», il residuo del budget, non deducibile dal solo indice di posizione. Serve una seconda dimensione $b$: con la coppia $(i,b)$ lo stato è completamente determinato. È lo stesso "false start" del Knapsack in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|nota 05]] — un budget che si consuma con le decisioni richiede sempre una seconda variabile.
### Esempio numerico
$n=4$, $v=(3,10,2,8)$, $s=1$, $t=3$, $\Delta=6$.

| $i$ | $\text{OPT}(i,0..2)$ | $\text{OPT}(i,3)$ | $\text{OPT}(i,4)$ | $\text{OPT}(i,5)$ | $\text{OPT}(i,6)$ |
|---|---|---|---|---|---|
| 4 | 0 | 8 | 8 | 8 | 8 |
| 3 | 0 | 2 | 8 | 8 | 8 |
| 2 | 0 | 10 | 10 | 10 | 10 |
| 1 | 0 | 3 | 10 | 10 | **10** |

$\text{OPT}(1,6)=10$ si ottiene fermandosi sulla tratta $2$: uno spostamento (costo $s=1$) più uno scavo (costo $t=3$), totale $4 \leq 6$, guadagno $v_2=10$. Nessuna combinazione ammissibile con $\Delta=6$ fa meglio.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Dimenticare la seconda dimensione, definendo $\text{OPT}(i)$ col solo indice di posizione | senza sapere quanta batteria resta non si può dire se una mossa è ammissibile |
| Scrivere il costo del salto di $2$ come $2s$ | la traccia fissa un unico costo $s$ per la manovra di spostamento, indipendente dalla distanza |
| Dimenticare il caso "scavo e mi fermo" | senza di esso si sottostima l'ottimo quando $b \geq t$ ma $b < t+s$ |
| Dichiarare $\Theta(n\Delta)$ polinomiale | $\Delta$ compare come valore, non come numero di bit dell'input |
| Riempire la tabella per $i$ crescente, per analogia col Knapsack "da manuale" | il sottoproblema è definito a suffisso (da $i$ in poi), non a prefisso: dipende da $i+1,i+2$, quindi si riempie per $i$ decrescente |
