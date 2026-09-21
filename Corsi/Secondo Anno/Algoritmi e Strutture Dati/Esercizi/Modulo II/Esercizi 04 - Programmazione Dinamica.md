---
tags:
  - algoritmi
  - dp
  - esercizi
nota: "[[04 - Programmazione Dinamica I (Weighted Independent Set)]]"
---
# Esercizi — Progettazione di algoritmi di programmazione dinamica
Palestra dell'**Esercizio 3**: progettazione di un algoritmo di DP su un problema mai visto, 11 punti. Sono gli Esercizio 3 delle tracce reali, con il testo verbatim.
Il **metodo** — i cinque passi, dove si perdono i punti, come si legge la risposta — sta in [[04 - Programmazione Dinamica I (Weighted Independent Set)#Come si scrive un Esercizio 3]]. Qui si allena, non si spiega.
## Come si usa questa pagina
Ogni item ha la **traccia integrale** e due callout richiudibili:
- **Indizio** — la sola definizione dello stato, da aprire se non parti proprio;
- **Soluzione** — i cinque passi per esteso, più una verifica numerica su un'istanza piccola.
Apri la soluzione **dopo** aver scritto la tua, non prima. Criterio di chiusura: l'item è chiuso quando produci tutti e cinque i passi senza aprire niente.
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
## Nota sul perimetro
I primi sette item coprono gli Esercizio 3 delle tracce più recenti: sono l'allenamento vero. I problemi di DP **studiati** — weighted interval scheduling, knapsack, segmented least squares, sequence alignment, Hirschberg, Bellman-Ford, LIS — nella configurazione attuale non sono mai stati chiesti come teoria allo scritto: servono come **repertorio di telai** da riconoscere sotto il travestimento, ed è all'orale che vengono chiesti per nome.
Le quattro domande concettuali in coda sono costruite, non sono item d'esame: stanno qui come controllo della teoria. Le domande di teoria sulla DP realmente comparse (formato Clementi) sono in [[Esercizi 05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]].
