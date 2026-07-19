---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 09 — Job su due macchine
*(Esercizio 3 — compito del 09/09/2025 — 11 punti)*
> [!note] Traccia
> **Setup.** Devi assegnare $n$ job, numerati da $1$ a $n$, a due macchine con l'obiettivo di minimizzare il costo totale. Ogni job può essere eseguito da entrambe le macchine, ma le politiche di costo delle due macchine sono diverse.
> **Costi.** La macchina $A$ non ha costi fissi e può eseguire il generico job $i$ ad un costo di $a_i$. La macchina $B$ ha dei costi per job più bassi, $b_i \le a_i$, ma ha dei costi fissi che dipendono dal numero totale di job che decidi di assegnare alla macchina: devi pagare un costo pari a $c_k$ se decidi di assegnare $k$ job in totale alla macchina $B$, con $c_1 \le c_2 \le \cdots \le c_n$.
> **Richiesta.** Progetta un algoritmo di programmazione dinamica che calcoli il costo minimo a cui è possibile eseguire tutti i job. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**DP su prefisso con contatore ausiliario** — `OPT(i,k)` indicizzato sul prefisso di job già processati e sul numero di job assegnati alla macchina $B$. Assomiglia in forma al [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|Knapsack 0/1]], ma il secondo indice non è un vincolo di capacità: è un contatore che etichetta lo stato per applicare correttamente il costo fisso $c_k$, che si conosce solo alla fine.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,k) = \text{costo minimo (solo variabile) per assegnare i primi } i \text{ job, con esattamente } k \text{ di essi su } B$$
Il costo fisso $c_k$ **non** è compreso: si paga una volta sola per l'intera assegnazione, non job per job, e va aggiunto solo alla fine. I sottoproblemi sono $\Theta(n^2)$: per ogni $i=0,\ldots,n$ (job considerati) e ogni $k=0,\ldots,i$ (di questi, quanti su $B$; necessariamente $k \le i$).
### Casi base
$$\text{OPT}(0,0) = 0$$
Con zero job processati e zero mandati su $B$ non c'è alcun costo da pagare: è la configurazione vuota, con valore neutro $0$ perché esiste una soluzione ammissibile a costo nullo, non un caso da escludere.
$$\text{OPT}(0,k) = +\infty \quad \text{per ogni } k = 1,\ldots,n$$
Con zero job processati è impossibile che $k>0$ job siano già stati assegnati a $B$: non esistono job da assegnare. Il valore $+\infty$ segnala che la configurazione non è raggiungibile, così un $\min$ non la sceglierà mai per errore. In un problema di massimizzazione il valore neutro per "impossibile" sarebbe $-\infty$: qui si minimizza un costo, quindi vale il segno opposto.
$$\text{OPT}(i,k) = +\infty \quad \text{per ogni } k > i$$
Il caso "impossibile" vale per ogni riga $i$, non solo per $i=0$: non si può mai avere assegnato a $B$ più job di quanti ne siano stati processati. Questo entra in gioco nella colonna $k=i$ di ogni riga: il primo caso della ricorrenza richiederebbe $\text{OPT}(i-1,i)$, che vale $+\infty$ per questa stessa regola, e il $\min$ si riduce al solo secondo caso.
### Ricorrenza
Per $i = 1,\ldots,n$ interroghiamo l'ultimo job processato, $i$: su quale macchina va?
**Il job $i$ va sulla macchina $A$.** Il conteggio dei job su $B$ non cambia: era $k$ fra i primi $i-1$ job, resta $k$ fra i primi $i$. Il costo aggiunto è $a_i$, il costo variabile di $A$ — nessun costo fisso, $A$ non ne ha.
**Il job $i$ va sulla macchina $B$.** Il conteggio sale di uno: per avere $k$ job su $B$ fra i primi $i$, dovevo averne $k-1$ fra i primi $i-1$. Il costo aggiunto è $b_i$, il costo variabile; il costo fisso $c_k$ non entra qui, si paga una volta sola alla fine. Il caso è definito solo per $k \ge 1$.
$$\text{OPT}(i,k) = \begin{cases} \text{OPT}(i-1,k) + a_i & \text{se } k = 0 \\[4pt] \min\bigl\{\text{OPT}(i-1,k) + a_i,\;\; \text{OPT}(i-1,k-1) + b_i\bigr\} & \text{se } 1 \le k \le i \end{cases}$$
Per $k=0$ il secondo termine del $\min$ non esiste ($\text{OPT}(i-1,-1)$ non ha senso): la riga $k=0$ si riempie con il solo primo caso, tutti i primi $i$ job forzati su $A$.
### Giustificazione
**Esaustività.** Il job $i$ deve andare su esattamente una delle due macchine — non è ammesso ometterlo, la traccia richiede che tutti i job vengano eseguiti — e non può andare su entrambe. I due casi coprono quindi tutte e sole le decisioni possibili per l'ultimo job.
**Sottostruttura ottima.** Fissata la decisione sul job $i$, resta da assegnare in modo ottimo il prefisso dei primi $i-1$ job con il conteggio residuo aggiornato: un sottoproblema dello stesso tipo, più corto di uno. Se quella parte non fosse risolta in modo ottimo, sostituendola con la strategia ottima si otterrebbe un costo totale minore, contro l'ottimalità della soluzione di partenza.
**Separazione dei costi.** Il costo fisso $c_k$ dipende solo dal conteggio finale, non dalle decisioni intermedie: tenerlo fuori dalla tabella e applicarlo in un $\min$ separato a $i=n$ non altera l'ottimalità, perché ogni cella $\text{OPT}(i,k)$ rappresenta comunque il costo variabile minimo fra tutte le strategie con quel preciso conteggio.
### Ordine di calcolo
Per $i$ crescente da $1$ a $n$: ogni riga usa solo la riga $i-1$, mai righe successive. Per ogni $i$, per $k$ crescente da $0$ a $i$: ogni cella $\text{OPT}(i,k)$ dipende solo da $\text{OPT}(i-1,k)$ e $\text{OPT}(i-1,k-1)$, entrambe già calcolate nella riga precedente. Non serve alcun ordinamento preliminare dei job: a differenza del Weighted Interval Scheduling qui non c'è compatibilità da verificare, i job si processano nell'ordine dato.
### Risposta
$$\min_{k=0}^{n} \bigl\{\text{OPT}(n,k) + c_k\bigr\}$$
Il costo fisso (con $c_0=0$ per convenzione) si somma solo qui, fuori dalla tabella: per ogni possibile conteggio finale $k$, $\text{OPT}(n,k)$ è il costo variabile ottimo di una strategia che manda esattamente $k$ job su $B$, e la risposta è la migliore fra tutte. A differenza del WIS o del Knapsack, dove la risposta è una singola cella, qui va scandita l'intera ultima riga.
### Complessità
$\Theta(n^2)$ celle: $(n+1)$ righe per $i=0,\ldots,n$ e al più $(n+1)$ colonne per riga ($k=0,\ldots,i\le n$). Ogni cella costa $O(1)$ — un confronto fra due valori già calcolati, o un'unica somma per la riga $k=0$. Il riempimento costa quindi $\Theta(n^2)$; il $\min$ finale sull'ultima riga costa $O(n)$ aggiuntivo, che non cambia l'ordine di grandezza. **Complessità totale: $\Theta(n^2)$ tempo.**
È **polinomiale**, non pseudo-polinomiale: il contatore $k$ varia fra $0$ e $n$, cresce con la lunghezza dell'input (il numero di job), non con il valore dei costi $a_i,b_i,c_k$. È l'opposto del [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Complessità e pseudo-polinomialità|Knapsack]], dove il secondo indice è la capacità $W$ e $\Theta(nW)$ dipende dal valore di $W$.
Sullo spazio: la tabella naïve occupa $\Theta(n^2)$, ma la ricorrenza usa solo la riga $i-1$ per calcolare la riga $i$: con un array a rotazione lo spazio scende a $O(n)$, a patto di non dover ricostruire l'assegnazione ottima (serve l'intera tabella per risalire indietro).
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{CostoMinimoDueMacchine($n$, $a[1..n]$, $b[1..n]$, $c[0..n]$)}
\begin{algorithmic}
\For{$i \gets 0$ \To $n$}
  \For{$k \gets 0$ \To $n$}
    \State $OPT(i,k) \gets +\infty$ \Comment{tabella intera, cos\`i ogni cella fuori range \`e $+\infty$ per default}
  \EndFor
\EndFor
\State $OPT(0,0) \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $OPT(i,0) \gets OPT(i-1,0) + a[i]$
  \For{$k \gets 1$ \To $i$}
    \State $OPT(i,k) \gets \min\bigl(OPT(i-1,k) + a[i],\;\; OPT(i-1,k-1) + b[i]\bigr)$
  \EndFor
\EndFor
\State $\text{migliore} \gets +\infty$
\For{$k \gets 0$ \To $n$}
  \State $\text{migliore} \gets \min\bigl(\text{migliore},\; OPT(n,k) + c[k]\bigr)$
\EndFor
\Return $\text{migliore}$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Ogni job va deciso singolarmente: per ciascun job $i$ la scelta è binaria, su $A$ oppure su $B$. Non ci sono compatibilità fra job come nell'Interval Scheduling, né un ordine temporale da rispettare: il primo istinto è vederlo come una Scelta Binaria su Sequenza, il pattern del [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]].
La frase che rompe l'analogia è "$k$ job **in totale**" nella traccia: il costo fisso $c_k$ non dipende da *quale* job va su $B$ né da *quando* si decide, ma solo dal conteggio finale. Serve quindi un contatore di stato oltre al semplice prefisso processato ([[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Riconoscere il sottoproblema in un problema mai visto|vedi la tabella dei pattern]]).
Il problema assomiglia in forma al Knapsack 0/1 — due indici, scelta binaria, ricorrenza a due termini — ma con una differenza concettuale: nel Knapsack il secondo indice (la capacità residua) è un **vincolo** che filtra le scelte ammissibili. Qui il secondo indice (quanti job sono andati su $B$) **non vincola nulla**: serve solo a sapere, alla fine, quale $c_k$ applicare.
### Perché il costo fisso si applica solo alla fine
Un tentativo naturale è scrivere $\text{OPT}(i) = \min\{\text{OPT}(i-1)+a_i,\, \text{OPT}(i-1)+b_i\}$ come nel WIS, sommando ogni volta il costo scelto. Non funziona: $c_k$ si paga una volta sola per il conteggio finale $k$, non è un costo che si somma job per job durante il riempimento della tabella; e comunque, a metà tabella, il conteggio finale dipende anche dalle decisioni sui job futuri, non ancora prese.
Il rimedio non richiede di conoscere il futuro: basta portare dietro, ad ogni passo, quanti job sono già andati su $B$ fra i primi $i$ processati. Arrivati a $i=n$, il conteggio finale $k$ è noto per ciascuna configurazione tenuta in tabella, e il $c_k$ corretto può essere applicato a ciascuna.
Questo è il motivo per cui $\text{OPT}(i,k)$ non contiene $c_k$: il costo fisso entra solo nel $\min$ finale, fuori dalla tabella. Ed è anche il motivo per cui la risposta non si legge in una singola cella, come in WIS o Knapsack, ma scorrendo l'intera ultima riga — non si sa a priori quale conteggio finale sia il migliore, perché dipende dal confronto fra il risparmio di mandare job su $B$ e il costo fisso crescente $c_k$.
### Esempio numerico
$n=3$.

| $i$ | $a_i$ | $b_i$ |
|---|---|---|
| 1 | 5 | 2 |
| 2 | 4 | 3 |
| 3 | 6 | 5 |

Costi fissi $c_1=1,\ c_2=3,\ c_3=4$ ($c_0=0$ per convenzione); si verifica $b_i \le a_i$ per ogni $i$, come richiesto dalla traccia. Tabella riempita riga per riga:

| | $k=0$ | $k=1$ | $k=2$ | $k=3$ |
|---|---|---|---|---|
| $i=0$ | $0$ | $+\infty$ | $+\infty$ | $+\infty$ |
| $i=1$ | $0+5=5$ | $0+2=2$ | $+\infty$ | $+\infty$ |
| $i=2$ | $5+4=9$ | $\min(2+4,\,5+3)=6$ | $2+3=5$ | $+\infty$ |
| $i=3$ | $9+6=15$ | $\min(6+6,\,9+5)=12$ | $\min(5+6,\,6+5)=11$ | $5+5=10$ |

Applicando il costo fisso alla riga finale $i=3$:

| $k$ | $\text{OPT}(3,k)$ | $c_k$ | Totale |
|---|---|---|---|
| 0 | 15 | 0 | 15 |
| 1 | 12 | 1 | **13** |
| 2 | 11 | 3 | 14 |
| 3 | 10 | 4 | 14 |

Il minimo è $13$, con $k=1$. Ripercorrendo a ritroso: $\text{OPT}(3,1)=12$ viene dal primo caso ($\text{OPT}(2,1)+a_3$), $\text{OPT}(2,1)=6$ viene dal primo caso ($\text{OPT}(1,1)+a_2$), $\text{OPT}(1,1)=2$ viene dal secondo caso ($\text{OPT}(0,0)+b_1$): job $1$ su $B$, job $2$ e $3$ su $A$, costo $b_1+a_2+a_3+c_1 = 2+4+6+1 = 13$. Un controllo per forza bruta sulle $2^3=8$ assegnazioni possibili conferma che $13$ è il minimo globale.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Dimenticare il secondo indice: $\text{OPT}(i)=\min\{\text{OPT}(i-1)+a_i,\,\text{OPT}(i-1)+b_i\}$ | Non permette di sapere quale $c_k$ applicare alla fine: manca il conteggio da tracciare |
| Sommare $c_k$ dentro la ricorrenza invece che una volta sola alla fine | $c_k$ è un costo una tantum sul conteggio finale, non un costo per job: sommarlo nel ciclo lo conta più volte, o nel posto sbagliato |
| Porre $\text{OPT}(0,k)=0$ invece di $+\infty$ per $k>0$ | Con zero job processati non è possibile aver assegnato $k>0$ job a $B$; ricontrollando a mano le prime righe compaiono valori finiti dove $k>i$ |
| Dichiarare la complessità $\Theta(n)$ o $\Theta(n\log n)$ | La tabella ha due indici di taglia $\Theta(n)$: $\Theta(n^2)$ celle, non lineare |
| Inizializzare a $+\infty$ solo la riga $i=0$ | Il caso $k>i$ vale per ogni riga; senza pre-inizializzare l'intera tabella, il primo caso per $k=i$ legge $\text{OPT}(i-1,i)$, una cella mai scritta esplicitamente |
