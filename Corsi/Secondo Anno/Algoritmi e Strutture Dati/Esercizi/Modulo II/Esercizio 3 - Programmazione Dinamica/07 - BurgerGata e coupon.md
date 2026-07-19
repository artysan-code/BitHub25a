---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 07 — BurgerGata e Coupon
*(Esercizio 3 — compito del 26/06/2025 — 11 punti)*
> [!note] Traccia
> Vicino la vostra università ha aperto un nuovo fast food, il *BurgerGata*. Come lancio pubblicitario, i titolari hanno organizzato un'iniziativa denominata *Menu & Coupon* che sarà attiva per i prossimi $n$ giorni, a pranzo. Potete trovare i dettagli sul sito di BurgerGata. Per ogni giorno $i = 1, \ldots, n$, il locale mette a disposizione un menù fisso al prezzo di $p_i$ euro e un coupon di valore $c_i$, che può essere utilizzato per intero e in un'unica soluzione solo in un giorno successivo. I coupon non sono cumulabili e ogni volta che un coupon è utilizzato viene disattivato. In particolare, se l'ultima volta che avete mangiato al BurgerGata è stato il giorno $i$ e decidete di tornarci il giorno $j > i$, allora lo sconto effettivo che ottenete è di $\min\{p_j, c_i\}$ euro.[^1] In compenso vi mettete in tasca il coupon di valore $c_j$ che potete utilizzare la prossima volta.
>
> **Richiesta.** Il vostro obiettivo è quello di decidere i giorni in cui andare da BurgerGata in modo da massimizzare lo sconto totale effettivo, ovvero la somma degli sconti effettivi ottenuti nei singoli pranzi. Progettate un algoritmo di programmazione dinamica che calcoli il massimo sconto totale effettivo che potete ottenere dall'iniziativa. Si discuta la complessità temporale dell'algoritmo proposto.

[^1]: Il che vuol dire che se per esempio avete un coupon di valore $c_i = 30$ e lo usate un giorno in cui il menù ha costo $p_j = 10$ essenzialmente bruciate 20 euro del valore del coupon.
## Pattern
**DP su sequenza con vincolo «deve terminare qui»** — $\text{OPT}(j)$ indicizzato sull'ultimo giorno visitato, sul modello della [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Longest Increasing Subsequence (LIS)|LIS]], con in più una **scelta multipla** sul predecessore come in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Segmented Least Squares|Segmented Least Squares]]. **Non** è Weighted Interval Scheduling: qui non esiste un predecessore univoco $p(j)$, vanno confrontati tutti gli $i<j$.
## Soluzione
### Sottoproblema
$$\text{OPT}(j) = \text{massimo sconto totale ottenibile da una sequenza di visite tra i giorni } 1,\ldots,j \text{ che termina esattamente al giorno } j$$
La catena può ridursi al solo giorno $j$: in tal caso non c'è sconto quel pranzo, ma si incassa comunque il coupon $c_j$ per il futuro.
I sottoproblemi sono $\Theta(n)$, uno per ciascun possibile ultimo giorno $j=1,\ldots,n$: non serve una seconda dimensione, perché il coupon disponibile dopo la visita in $j$ è univocamente $c_j$.
### Casi base
$$\text{OPT}(1) = 0$$
Per $j=1$ non esiste alcun giorno precedente: l'unica catena che termina in $1$ è il giorno stesso, senza sconto perché non c'è alcun coupon da spendere.
Il valore $0$ non è un artificio tecnico ma un valore realmente raggiungibile: chiunque può andare al BurgerGata una prima volta senza sconto. A differenza di un problema di minimizzazione (dove il neutro sarebbe $+\infty$), qui $0$ funge sia da caso base sia da termine neutro del $\max$ nella ricorrenza.
### Ricorrenza
Per $j>1$ le mosse possibili sono due.
**Riparti da zero al giorno $j$**, senza alcuna visita precedente nella catena: nessun coupon da spendere. Il contributo di sconto è nullo; resta comunque disponibile $c_j$ per il futuro.
**Il giorno $i<j$ è l'ultima visita precedente**: sommi allo sconto ottimo della catena che finisce in $i$ lo sconto effettivo di oggi, $\min\{p_j, c_i\}$. Vanno provati tutti gli $i=1,\ldots,j-1$, perché nessun vincolo di compatibilità li esclude a priori.
$$\text{OPT}(j) = \max\left\{0,\; \max_{i=1}^{j-1}\Bigl(\text{OPT}(i) + \min\{p_j, c_i\}\Bigr)\right\}$$
### Giustificazione
**Esaustività.** Guardando la tappa immediatamente precedente a $j$ nella catena ottima: o non esiste (si riparte da zero) o è un preciso giorno $i<j$. Non c'è una terza possibilità.
**Assenza di sovrapposizioni.** Le $j$ alternative del $\max$ — zero, più un'alternativa per ciascun $i<j$ — sono mutuamente esclusive: una catena ha una e una sola tappa immediatamente precedente a $j$, oppure nessuna.
**Sottostruttura ottima.** Se la tappa precedente è $i$, il resto della catena fino a $i$ deve essere a sua volta ottimo: sostituendovi una catena subottima si otterrebbe un totale ancora maggiore per $\text{OPT}(j)$, contro l'ottimalità di $\text{OPT}(i)$.
### Ordine di calcolo
$j$ crescente da $1$ a $n$. Per calcolare $\text{OPT}(j)$ servono tutti gli $\text{OPT}(i)$ con $i<j$: quando si arriva alla cella $j$, le celle $1,\ldots,j-1$ sono già state riempite. Non serve una seconda dimensione da scandire.
### Risposta
$$\max_{j=1}^{n} \text{OPT}(j)$$
Non $\text{OPT}(n)$: ogni cella copre solo le catene che terminano esattamente in $j$, e la catena ottima globale può fermarsi prima dell'ultimo giorno — esattamente come in LIS, dove la sottosequenza più lunga non deve necessariamente terminare nell'ultimo elemento. Poiché ogni $\text{OPT}(j)\ge 0$, il massimo copre correttamente anche il caso in cui non conviene sfruttare alcun coupon.
### Complessità
$\Theta(n)$ celle. Calcolare $\text{OPT}(j)$ richiede di scandire tutti i predecessori $i=1,\ldots,j-1$, ciascuno in $O(1)$: costo $O(j)$ per cella.
$$\sum_{j=1}^{n} O(j) = O(n^2)$$
Tempo $O(n^2)$, spazio $O(n)$ per il vettore $\text{OPT}(1\ldots n)$.
È **polinomiale in senso proprio**, non pseudo-polinomiale: sottoproblemi e costo per cella dipendono solo dalla lunghezza $n$ dell'istanza, mai dai valori numerici di $p_i$ o $c_i$, che compaiono solo come termini di confronto/somma a costo $O(1)$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{BurgerGata-Sconto($n, p[1 \ldots n], c[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(1) \gets 0$
\For{$j \gets 2$ \To $n$}
  \State $\text{OPT}(j) \gets 0$ \Comment{riparti da zero}
  \For{$i \gets 1$ \To $j-1$}
    \State $\text{OPT}(j) \gets \max\bigl(\text{OPT}(j),\; \text{OPT}(i) + \min\{p[j], c[i]\}\bigr)$
  \EndFor
\EndFor
\State \Return $\max_{j=1}^{n} \text{OPT}(j)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Tre frasi della traccia decidono tutto. **«Solo in un giorno successivo»** dice che si sceglie una sequenza ordinata di giorni $i_1<i_2<\cdots<i_k$, non un sottoinsieme qualunque: è lo schema della [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Longest Increasing Subsequence (LIS)|LIS]], non quello del Knapsack.
**«Se l'ultima volta... è stato il giorno $i$»** dice che per decidere basta un solo dato — quale giorno è stato l'ultimo visitato — la stessa informazione che in LIS è «con quale valore termina la sottosequenza».
**«Vi mettete in tasca il coupon $c_j$»** rende il problema markoviano rispetto all'ultimo giorno: lo stato futuro dipende solo da $j$, non da come ci si è arrivati.
Non è un Weighted Interval Scheduling: lì il predecessore era univoco, $p(j)$; qui qualunque $i<j$ è ammissibile e va confrontato — la stessa scelta multipla di [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Segmented Least Squares|Segmented Least Squares]].
### Il tentativo ingenuo e dove si rompe
**Tentativo naturale.** Si potrebbe definire $\text{OPT}(j)$ come il massimo sconto totale tra i primi $j$ giorni, senza vincolo di terminazione — lo schema di WIS e Weighted Interval Scheduling. Per estendere la ricorrenza al giorno $j+1$ serve però $\min\{p_{j+1}, c_i\}$, dove $i$ è l'ultimo giorno della catena ottima fino a $j$: un $\text{OPT}(j)$ che conserva solo il totale accumulato non dice qual è stato $i$, né quindi $c_i$.
**Dove si rompe.** Tra i primi $j$ giorni possono esistere due catene: una con sconto alto ma coupon finale piccolo, un'altra con sconto più basso ma coupon finale enorme. Se $p_{j+1}$ è molto alto conviene ripartire dalla seconda, pur valendo meno da sola — ma un $\text{OPT}(j)$ che scarta l'identità dell'ultimo giorno non permette questa scelta.
**La correzione.** Non serve un secondo indice indipendente come nel Knapsack, dove la capacità residua è un valore autonomo da tabulare. Qui il coupon in mano è determinato non appena si fissa quale giorno è l'ultimo visitato, perché vale semplicemente $c_j$. Basta ridefinire il sottoproblema imponendo che la catena termini esattamente in $j$ — lo stesso trucco della LIS.
### Esempio numerico
$n=3$, $p=[10,\,5,\,20]$, $c=[3,\,50,\,1]$.

| Strategia | Catena | Sconto totale |
|---|---|---|
| Salta il giorno $2$ | $1\to 3$ | $\min\{20,3\}=3$ |
| Ottima | $1\to 2\to 3$ | $\min\{5,3\}+\min\{20,50\}=3+20=23$ |

Il giorno $2$ sembra costare poco: lo sconto immediato è solo $3$. Ma lascia in tasca il coupon $c_2=50$, ed è quel coupon, speso il giorno $3$, a valere $20$ euro di sconto pieno. Con la ricorrenza: $\text{OPT}(3) = \max\bigl(0,\; 0+\min\{20,3\},\; 3+\min\{20,50\}\bigr) = \max(0,3,23) = \mathbf{23}$.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Definire $\text{OPT}(j)$ senza vincolo di terminazione | non si riesce a scrivere da dove viene $c_i$ nella ricorrenza per $j+1$ |
| Omettere il caso $0$ (nessun predecessore) dal $\max$ | anche $\text{OPT}(1)$ resterebbe senza definizione, dato che per $j=1$ non esiste $i<1$ |
| Restituire $\text{OPT}(n)$ invece di $\max_j \text{OPT}(j)$ | $\text{OPT}(j)$ indica catene che terminano in $j$, non la soluzione globale — stesso errore della LIS |
| Scambiare gli argomenti, scrivere $\min\{p_i, c_j\}$ | la traccia fissa l'ordine: prezzo del giorno di arrivo $j$, coupon lasciato dal giorno di partenza $i$ |
| Dichiarare complessità $O(n)$ per analogia col WIS | la scelta sul predecessore è multipla (ogni $i<j$), non binaria: il ciclo interno costa $O(j)$, non $O(1)$ |
