# Greedy e Interval Scheduling
Il paradigma **greedy** (goloso) affronta problemi di ottimizzazione costruendo la soluzione passo dopo passo: ad ogni passo si compie la scelta *localmente* ottima — senza ritornare indietro — sperando (e dimostrando!) che la sequenza di scelte locali produca la soluzione *globalmente* ottima. Non tutti i problemi ammettono algoritmi greedy corretti: la difficoltà sta nel dimostrare l'ottimalità, tipicamente tramite *greedy stays ahead* o un argomento di scambio (*exchange argument*). Questa nota introduce il paradigma e lo applica ai problemi di Interval Scheduling e Interval Partitioning. Per gli algoritmi di ordinamento richiamati nell'analisi della complessità vedere [[04 - Algoritmi di Ordinamento]]; per la struttura dati coda con priorità usata in Interval Partitioning vedere [[07 - Code con Priorità e Heap]].
## Il paradigma Greedy
Un algoritmo **greedy** costruisce la soluzione **un pezzo alla volta**: a ogni passo compie la scelta che sembra migliore *in quel momento* — la scelta *localmente* ottima — e **non la rimette mai in discussione**. Non esplora alternative, non torna indietro, non confronta soluzioni complete tra loro. È questo a renderlo **semplice e veloce**: quasi sempre un **ordinamento** seguito da una **scansione lineare**. Il prezzo della rapidità è che le scelte locali **non è detto** convergano all'ottimo globale.

Lo schema di un greedy è quasi sempre lo stesso:
1. si fissa un **criterio d'ordine** con cui esaminare gli elementi;
2. si scorrono gli elementi in quell'ordine e si **aggiunge** alla soluzione quello corrente se è *ammissibile* (compatibile con le scelte già fatte);
3. non si ripensa **mai** a una scelta passata.

> [!warning] Il criterio è tutto — e l'ottimalità va dimostrata
> Il cuore di un algoritmo greedy è **quale** criterio d'ordine si sceglie: lo stesso problema ne ammette molti plausibili e, in generale, **solo alcuni portano all'ottimo**. Per Interval Scheduling vedremo che su 4 criteri ragionevoli **solo uno** (earliest finish time) funziona. Un greedy quindi **non è mai "ovviamente" corretto**: l'ottimalità va *provata*, non data per scontata. E se non riesci a dimostrarla, spesso è il segnale che il problema chiede la [[04 - Programmazione Dinamica I (Weighted Independent Set)|programmazione dinamica]], non un greedy.
### Tecniche di dimostrazione dell'ottimalità
Le due tecniche standard per dimostrare che un algoritmo greedy è ottimo sono:

> [!quote] Proprietà — Greedy stays ahead
> Si dimostra che, ad ogni passo $r$, la soluzione parziale greedy è "almeno buona quanto" qualunque soluzione parziale ottima fino allo stesso passo. Formalmente, si esibisce una misura quantitativa $\phi(r)$ tale che $\phi_{\text{greedy}}(r) \leq \phi_{\text{OPT}}(r)$ (o $\geq$, a seconda della misura), e si procede per induzione su $r$. L'ottimalità globale segue applicando il lemma all'ultimo passo.

> [!quote] Proprietà — Exchange argument (argomento di scambio)
> Si prende una soluzione ottima $\text{OPT}$ qualunque e si mostra che è possibile trasformarla nella soluzione greedy $G$ tramite una sequenza di piccole modifiche (**scambi**), senza peggiorarne il valore. Ogni scambio sostituisce un elemento di $\text{OPT}$ con il corrispondente elemento scelto dal greedy, e si dimostra che il valore non decresce. Al termine si conclude $\text{cost}(G) \geq \text{cost}(\text{OPT})$ e quindi $G$ è ottimo.

> [!info] Quale tecnica usare?
> "Greedy stays ahead" è la tecnica naturale quando la soluzione cresce per aggiunta incrementale (come in Interval Scheduling). L'exchange argument è preferibile quando si vuole confrontare direttamente due soluzioni complete, come in problemi di scheduling con penalità (minimize lateness) o nella dimostrazione delle proprietà di taglio per i MST (cfr. [[03 - Minimum Spanning Tree]]).
## Interval Scheduling
### Definizione del problema
> [!quote] Definizione — Interval Scheduling
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** un sottoinsieme $S$ di intervalli mutualmente compatibili, ovvero tale che per ogni $I_i, I_j \in S$ i due intervalli non si sovrappongono ($f_i \leq s_j$ oppure $f_j \leq s_i$).
> **Misura (da massimizzare):** la cardinalità $|S|$, cioè il numero di intervalli schedulati.

Il problema è anche detto **job scheduling su una singola risorsa**: ogni intervallo è un "job" con inizio e fine, la risorsa (macchina, aula, processore) può gestire un solo job alla volta, e si vuole eseguire il massimo numero di job.

**Notazione.** $J$ è l'insieme dei job e $j \in J$ è il singolo job; $s(j)$ e $f(j)$ ne denotano inizio e fine. È la stessa **notazione funzionale** usata nelle dimostrazioni più sotto, e rende leggibile il confronto $f(j^*)$ — a pedici diventerebbe $f_{j^*}$, un pedice dentro un pedice. *(Le slide scrivono equivalentemente $s_j$ e $f_j$.)*

> [!question] Domanda tipica d'esame — definizione formale di IS
> **D:** «A. Si definisca formalmente IS. (Max 5 righe.)» *(chiesto il 19/02/2024 e il 21/01/2025)*
> **R:** Un'istanza di IS è definita da un insieme di $n$ intervalli $I_1, \ldots, I_n$, ciascuno con tempo di inizio $s_i$ e tempo di fine $f_i$. Una soluzione ammissibile è un sottoinsieme $S$ di intervalli a due a due compatibili, cioè tali che per ogni coppia $I_i, I_j \in S$ risulti $f_i \leq s_j$ oppure $f_j \leq s_i$ (non si sovrappongono). La misura da massimizzare è la cardinalità $|S|$, il numero di job schedulabili sulla singola risorsa.
### Schemi greedy candidati e controesempi
Uno schema naturale è: *considera i job in un certo ordine, aggiungili a $S$ se compatibili con quelli già scelti*. Quali ordini funzionano?

| Ordine               | Idea                                           | Ottimo?                                                                         |
| -------------------- | ---------------------------------------------- | ------------------------------------------------------------------------------- |
| Earliest start time  | ordine crescente di $s(j)$                     | No — un job lunghissimo blocca tutto                                            |
| Earliest finish time | ordine crescente di $f(j)$                     | **Sì** (dimostrato sotto)                                                       |
| Shortest interval    | ordine crescente di $f(j) - s(j)$              | No — un intervallo corto al centro può escludere due più lunghi non sovrapposti |
| Fewest conflicts     | ordine crescente del numero di conflitti $c_j$ | No — controesempio costruibile facilmente                                       |

> [!warning] Controesempi per gli ordini errati
> *Earliest start time*: un unico job $[0, 100]$ blocca tutti i job $[1,2], [3,4], \ldots$ che partono dopo ma sono compatibili tra loro.
> *Shortest interval*: il job corto $[2, 4]$ si sovrappone sia a $[0, 3]$ sia a $[3, 6]$, quindi il greedy sceglie $[2, 4]$ ed esclude entrambi (1 job soltanto); l'ottimo prende invece $[0, 3]$ e $[3, 6]$, tra loro compatibili ($f = 3 \leq s = 3$) → 2 job.
> *Fewest conflicts*: con la configurazione giusta un job con pochi conflitti "buca" il centro impedendo due job laterali compatibili, ciascuno con un conflitto in più.

> [!question] Domanda tipica d'esame — controesempio al criterio "job più corti"
> **D:** «2. Si mostri che il criterio greedy secondo cui i migliori job sono quelli che durano di meno (ovvero che minimizzano fi − si) in generale non consente di trovare una soluzione ottima del problema. (Max 3 righe.)» *(chiesto il 22/06/2022)*
> **R:** È lo stesso controesempio del criterio *shortest interval*: bastano tre job $[0,3]$, $[3,6]$ e $[2,4]$. Il criterio ordina per durata crescente e sceglie per primo $[2,4]$ (durata 2), che si sovrappone sia a $[0,3]$ sia a $[3,6]$: la soluzione greedy contiene un solo job. L'ottimo prende invece $[0,3]$ e $[3,6]$, compatibili tra loro ($f=3 \leq s=3$), ottenendo 2 job — strettamente meglio. Il criterio "durata minima" non è quindi ottimo.

> [!question] Domanda tipica d'esame — controesempio all'ordine per lunghezza crescente
> **D:** «B. Si argomenti sul perché l'algoritmo greedy che guarda gli intervalli in ordine crescente di lunghezza non calcola una soluzione ottima. (Max 3 righe.)» *(chiesto il 19/02/2024)*
> **R:** Si può costruire un controesempio in cui l'intervallo più corto è incompatibile con due o più intervalli più lunghi che invece sono compatibili tra loro: scegliendo l'intervallo corto per primo si esclude la possibilità di prendere gli altri, ottenendo una soluzione non ottima.
### Algoritmo earliest-finish-time-first
L'unico ordine che garantisce l'ottimalità è **earliest finish time**: si processa ogni job in ordine crescente di tempo di fine e lo si aggiunge alla soluzione se compatibile con l'ultimo job selezionato.

```pseudo
\begin{algorithm}
\caption{Earliest-Finish-Time-First($J$) — insieme massimo di job compatibili}
\begin{algorithmic}
\State Ordina $J$ in ordine crescente di $f(j)$
\State $S \gets \emptyset$
\State $j^* \gets \text{nessuno}$ \Comment{ultimo job inserito in $S$}
\ForAll{$j \in J$ nell'ordine}
  \If{$j^* = \text{nessuno}$ o $s(j) \geq f(j^*)$}
    \State $S \gets S \cup \{j\}$
    \State $j^* \gets j$
  \EndIf
\EndFor
\State \Return $S$
\end{algorithmic}
\end{algorithm}
```

> [!info] Implementazione in $O(n \log n)$
> - L'ordinamento per tempo di fine (riga 1) richiede $O(n \log n)$ — cfr. [[04 - Algoritmi di Ordinamento]] (MergeSort o HeapSort).
> - Il ciclo (righe 4–7) esegue $n$ iterazioni, ognuna in $O(1)$: il controllo di compatibilità si riduce a confrontare $s(j)$ con $f(j^*)$ (il tempo di fine dell'ultimo job inserito), poiché $S$ contiene sempre intervalli compatibili e il nuovo job deve solo non sovrapporsi all'ultimo.
> - Totale: $O(n \log n)$.

> [!question] Domanda tipica d'esame — l'ordine considerato dall'algoritmo
> **D:** «1. Si dica quale è l'ordine con cui A considera i job. (Max una riga.)» *(chiesto il 22/06/2022)*
> **R:** L'algoritmo A considera i job in ordine non decrescente del tempo di fine $f_i$ (earliest finish time first): li ordina per $f_i$ crescente e li scandisce poi una sola volta in quell'ordine.

> [!question] Domanda tipica d'esame — V/F sull'ordinamento per finish time
> **D:** *(Vero o Falso)* «Uno step fondamentale dell'algoritmo Greedy ALG-G(I) è quello di ordinare gli intervalli I_j rispetto al finish time.» *(chiesto il 12/09/2023)*
> **R:** **Vero.** Il primo passo dell'algoritmo (riga 1 dello pseudocodice) è proprio l'ordinamento di $J$ in ordine crescente di $f(j)$: è il passo che rende poi possibile la scansione lineare $O(n)$ con confronto $O(1)$ ad ogni iterazione, ed è quello che domina asintoticamente il costo totale.

> [!question] Domanda tipica d'esame — il criterio di ordinamento corretto (I)
> **D:** «C. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema.» *(chiesto il 19/02/2024)*
> **R:** Si ordinano gli intervalli in ordine crescente di tempo di fine (finishing time) e si seleziona greedily, in quest'ordine, ogni intervallo compatibile con l'ultimo intervallo già scelto.

> [!question] Domanda tipica d'esame — il criterio di ordinamento corretto (II)
> **D:** «B. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema. (Max 2 righe.)» *(chiesto il 21/01/2025)*
> **R:** Si ordinano gli intervalli in ordine crescente di tempo di fine $f(j)$: è lo stesso criterio *earliest finish time* dell'algoritmo A, l'unico dei quattro schemi candidati (start time, finish time, durata, numero di conflitti) che garantisce l'ottimalità.

> [!question] Domanda tipica d'esame — V/F sul divide et impera
> **D:** *(Vero o Falso)* «L'algoritmo ottimale Greedy ALG-G(I) spezza l'istanza iniziale in due sotto-istanze bilanciate in modo tale da applicare la tecnica del Divide et Impera, ottenendo un tempo di completamento O(n log n).» *(chiesto il 12/09/2023)*
> **R:** **Falso.** L'algoritmo non è un divide-et-impera: non spezza mai l'istanza in sotto-istanze ricorsive. È un puro schema greedy — un ordinamento iniziale $O(n \log n)$ seguito da un'unica scansione lineare $O(n)$ che aggiunge o scarta ogni job senza mai tornare indietro. Il tempo totale $O(n \log n)$ è dominato dall'ordinamento, non da una ricorrenza di tipo divide-et-impera.
### Esempio di esecuzione
Otto job (A–H). Prima si **ordina per tempo di fine** (l'ordine di lettura diventa B, C, A, E, D, F, G, H), poi si scorre la lista **una volta sola**.

| Job (per fine) | $s_i$ | $f_i$ |
|---|---|---|
| B | 1 | 3 |
| C | 2 | 4 |
| A | 0 | 5 |
| E | 3 | 6 |
| D | 4 | 8 |
| F | 5 | 9 |
| G | 5 | 10 |
| H | 7 | 11 |

Sull'asse dei tempi (`|===|` job scelto dal greedy, `|---|` scartato; due job si *toccano* quando $f_i = s_j$, e sono compatibili):

```
    0  1  2  3  4  5  6  7  8  9  10 11   <- tempo
B*     |=====|
C         |-----|
A   |--------------|
E*           |========|
D               |-----------|
F                  |-----------|
G                  |--------------|
H*                       |===========|
```

Si scorre la lista tenendo $j^*$ = **ultimo job selezionato**, e si prende il job corrente solo se $s(j) \geq f(j^*)$:

| # | Job | Confronto $s(j) \geq f(j^*)$ | Esito | Nuovo $j^*$ |
|---|---|---|---|---|
| 1 | B | — (è il primo) | **preso** | B ($f=3$) |
| 2 | C | $2 \geq 3$? no | scartato | B |
| 3 | A | $0 \geq 3$? no | scartato | B |
| 4 | E | $3 \geq 3$? **sì** | **preso** | E ($f=6$) |
| 5 | D | $4 \geq 6$? no | scartato | E |
| 6 | F | $5 \geq 6$? no | scartato | E |
| 7 | G | $5 \geq 6$? no | scartato | E |
| 8 | H | $7 \geq 6$? **sì** | **preso** | H ($f=11$) |

Soluzione: $S = \{B, E, H\}$, $|S| = 3$ — ottima (in questa istanza non esistono 4 job a due a due compatibili).
### Dimostrazione di ottimalità
La dimostrazione usa la tecnica *greedy stays ahead* e procede in due passi: un lemma per induzione, poi il teorema per assurdo.

Siano $i_1, i_2, \ldots, i_k$ i job selezionati dall'algoritmo greedy (ordinati per finish time), e siano $j_1, j_2, \ldots, j_m$ i job di una soluzione ottima (ordinati per finish time). Denotiamo con $f(i_r)$ il tempo di fine del job $i_r$.

> [!quote] Lemma — Greedy stays ahead per Interval Scheduling
> Per ogni $r = 1, 2, \ldots, k$ vale:
> $$f(i_r) \leq f(j_r)$$
> Ovvero: il $r$-esimo job scelto dal greedy finisce *non più tardi* del $r$-esimo job scelto dall'ottimo.

**Dimostrazione (per induzione su $r$).**

*Caso base ($r = 1$).*
1. Il greedy sceglie come primo job quello con il **minimo tempo di fine in assoluto**.
2. $j_1$ è un job qualunque, quindi il suo tempo di fine non può essere più piccolo.
3. Perciò $f(i_1) \leq f(j_1)$. $\square$

*Passo induttivo ($r > 1$).* **Ipotesi induttiva:** $f(i_{r-1}) \leq f(j_{r-1})$.
1. Nell'ottimo $j_r$ è compatibile con $j_{r-1}$, quindi $s(j_r) \geq f(j_{r-1})$.
2. Per ipotesi induttiva $f(j_{r-1}) \geq f(i_{r-1})$.
3. Concatenando (1) e (2): $s(j_r) \geq f(i_{r-1})$.
4. Quindi $j_r$ è compatibile anche con i job $i_1, \ldots, i_{r-1}$ già scelti dal greedy: inizia dopo la fine di $i_{r-1}$, che fra quelli ha il tempo di fine **massimo**.
5. Allora, nel momento in cui il greedy sceglieva il suo $r$-esimo job, $j_r$ era **fra i candidati disponibili**.
6. Il greedy prende sempre il candidato con **tempo di fine minimo**, perciò $f(i_r) \leq f(j_r)$. $\square$

```
Greedy:  i1        i2        i(r-1)     ir
         |--|      |---|     |-----|    |---|

Ottimo:   j1         j2         j(r-1)       jr
          |---|      |----|      |------|     |-----|
          ^-- f(ir) <= f(jr) per induzione --^
```

> [!quote] Teorema — Ottimalità di earliest-finish-time-first
> L'algoritmo earliest-finish-time-first è ottimale: produce un insieme di job compatibili di cardinalità massima.

**Dimostrazione (per assurdo).**
1. Supponiamo che il greedy **non** sia ottimo, cioè $m > k$: l'ottimo seleziona più job.
2. Applichiamo il lemma con $r = k$ e otteniamo $f(i_k) \leq f(j_k)$.
3. Poiché $m > k$, l'ottimo contiene un job in più, $j_{k+1}$.
4. Nell'ottimo $j_{k+1}$ è compatibile con $j_k$, quindi $s(j_{k+1}) \geq f(j_k)$; unendo al passo 2, $s(j_{k+1}) \geq f(i_k)$.
5. Dunque $j_{k+1}$ è compatibile con **tutti** i job $i_1, \ldots, i_k$ scelti dal greedy.
6. Ma allora il greedy, proseguendo la scansione, l'avrebbe trovato compatibile e **aggiunto** a $S$: la sua soluzione non si sarebbe fermata a $k$ job.
7. **Contraddizione** — non può essere $m > k$. Quindi $m = k$ e il greedy è ottimo. $\square$

```
Greedy:  i1   i2   i3   ...    ik
         |--|  |--| |--|        |---|

Ottimo:  j1   j2   j3   ...    jk        jk+1
         |--|  |--| |--|        |---|     |---|
                                           ^-- compatibile con ik => greedy lo avrebbe preso! Contraddizione
```

> [!question] Domanda tipica d'esame — la proprietà chiave dell'ottimalità
> **D:** «3. Si enunci in modo formale e preciso la proprietà chiave che permette di dimostrare che A è un algoritmo ottimo per Interval Scheduling. (Max 5 righe.)» *(chiesto il 22/06/2022)*
> **R:** La proprietà chiave è il lemma *greedy stays ahead*: detti $i_1, \ldots, i_k$ i job scelti dal greedy e $j_1, \ldots, j_m$ quelli di una soluzione ottima, entrambi ordinati per tempo di fine, per ogni $r = 1, \ldots, k$ vale $f(i_r) \leq f(j_r)$ — il greedy, passo per passo, non è mai "indietro" rispetto a nessuna soluzione ottima. Si dimostra per induzione su $r$: il caso base segue dal fatto che il greedy sceglie subito il job con finish time minimo in assoluto; il passo induttivo usa la compatibilità di $j_r$ con $j_{r-1}$ combinata con l'ipotesi induttiva per mostrare che $j_r$ era candidato anche per il greedy al passo $r$. Applicando il lemma con $r = k$ e ragionando per assurdo si esclude che l'ottimo possa avere $m > k$ job.

> [!question] Domanda tipica d'esame — schema della dimostrazione di ottimalità (I)
> **D:** «D. Si dimostri a grandi linee perché l'algoritmo del punto (C) trova sempre una soluzione ottima del problema.» *(chiesto il 19/02/2024)*
> **R:** La dimostrazione usa *greedy stays ahead* in due passi. Lemma (per induzione su $r$): il job $i_r$ scelto dal greedy come $r$-esimo finisce non più tardi del $r$-esimo job $j_r$ di una qualunque soluzione ottima, cioè $f(i_r) \leq f(j_r)$ — il caso base segue dal fatto che il greedy sceglie subito il job con finish time minimo assoluto, il passo induttivo dalla compatibilità di $j_r$ con $j_{r-1}$ combinata con l'ipotesi induttiva. Teorema (per assurdo): se l'ottimo avesse $m > k$ job, il job $j_{k+1}$ risulterebbe compatibile con tutti gli $i_1, \ldots, i_k$ già scelti dal greedy (per il lemma applicato a $r = k$), e quindi il greedy stesso lo avrebbe aggiunto a $S$ proseguendo la scansione — contraddizione. Dunque $m = k$ e il greedy è ottimo.

> [!question] Domanda tipica d'esame — schema della dimostrazione di ottimalità (II)
> **D:** «C. Si dimostri a grandi linee perché l'algoritmo del punto (B) trova sempre una soluzione ottima del problema. (Max 10 righe.)» *(chiesto il 21/01/2025)*
> **R:** Si procede con la tecnica *greedy stays ahead*. Si dimostra prima un lemma per induzione: confrontando i job scelti dal greedy $i_1, \ldots, i_k$ e quelli di una soluzione ottima $j_1, \ldots, j_m$ (entrambi ordinati per finish time), vale $f(i_r) \leq f(j_r)$ per ogni $r$ — al passo base il greedy prende il job con finish time minimo in assoluto, al passo induttivo la compatibilità di $j_r$ con $j_{r-1}$ più l'ipotesi induttiva mostrano che $j_r$ era disponibile anche per il greedy, che quindi sceglie un job con finish time non peggiore. Si conclude poi per assurdo: se fosse $m > k$, il job aggiuntivo $j_{k+1}$ dell'ottimo risulterebbe compatibile con tutta la soluzione greedy (per il lemma con $r = k$), e il greedy lo avrebbe quindi incluso — contraddizione. Perciò $m = k$: il greedy è ottimo.

> [!question] Domanda tipica d'esame — V/F sull'exchange argument
> **D:** *(Vero o Falso)* «La dimostrazione di ottimalità dell'algoritmo Greedy ALG-G(I), basata sull'Exchange Argument, stabilisce che ogni soluzione ammissibile, che non è quella calcolata da ALG-G(I), ha un valore strettamente inferiore a quella ottenuta da ALG-G(I).» *(chiesto il 12/09/2023)*
> **R:** **Falso**, per due motivi. Primo: la dimostrazione di ottimalità di IS vista a lezione non usa l'*exchange argument* ma *greedy stays ahead* (il lemma $f(i_r) \leq f(j_r)$ per induzione, seguito da assurdo). Secondo: anche a tecnica corretta l'affermazione resterebbe falsa nella sostanza — possono esistere più soluzioni ammissibili di cardinalità massima **uguale** a quella del greedy (più insiemi distinti di job compatibili possono raggiungere lo stesso $|S|$ ottimo), quindi non è vero che ogni altra soluzione abbia valore *strettamente* inferiore.
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Scansione e costruzione di $S$ | $O(n)$ |
| **Totale** | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — perché *earliest finish time* e non *earliest start time*?
> **D:** Perché l'ordine per tempo di inizio non funziona per Interval Scheduling, mentre quello per tempo di fine sì?
> **R:** Con *earliest start time* il primo job scelto potrebbe iniziare prestissimo ma durare arbitrariamente a lungo (es. $[0,100]$), bloccando tutti i job successivi anche se compatibili tra loro. L'ordine per *earliest finish time* è corretto perché **libera la risorsa il prima possibile**, massimizzando le opportunità future; la correttezza si prova con *greedy stays ahead* ($f(i_r) \leq f(j_r)$ per induzione) e chiusura per assurdo.

> [!question] Domanda tipica d'esame — perché il test di compatibilità è $O(1)$?
> **D:** Perché per verificare un nuovo job basta confrontarlo con l'ultimo selezionato $j^*$, e non con tutti quelli già in $S$?
> **R:** Perché i job sono processati in ordine di finish time crescente, quindi $j^*$ (l'ultimo aggiunto) ha il **finish time massimo** in $S$. Se il nuovo job è compatibile con $j^*$ lo è automaticamente con tutti gli altri, che finiscono ancora prima: basta un confronto $s(j) \geq f(j^*)$ ($O(1)$). Per questo il totale $O(n \log n)$ è dominato dall'ordinamento.
## Interval Partitioning
### Definizione del problema
> [!quote] Definizione — Interval Partitioning
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** una partizione degli intervalli in sottoinsiemi $C_1, \ldots, C_d$ (detti **classi** o **aule**) tali che ogni $C_i$ contiene solo intervalli mutualmente compatibili.
> **Misura (da minimizzare):** il numero di classi $d$.

Il problema modella l'assegnamento di lezioni universitarie alle aule: ogni lezione ha un orario fisso e non può essere spostata, si vuole minimizzare il numero di aule necessarie.

> [!question] Domanda tipica d'esame — definizione formale di IP
> **D:** «1. Si definisca formalmente il problema di IP. (Max 5 righe.)» *(chiesto il 28/09/2022 e il 18/02/2025)*
> **R:** Dato un insieme di $n$ intervalli (job), ciascuno con un tempo di inizio e un tempo di fine, il problema dell'Interval Partitioning chiede di assegnare a ciascun intervallo un'etichetta (risorsa/aula) in modo che due intervalli che si sovrappongono ricevano etichette diverse, minimizzando il numero totale di etichette (risorse) utilizzate.

> [!question] Domanda tipica d'esame — definizione formale del problema (variante I)
> **D:** «1. Si definisca formalmente il problema. (Max 5 righe.)» *(chiesto il 30/06/2026)*
> **R:** Un'istanza di Interval Partitioning è un insieme di $n$ intervalli $I_1, \ldots, I_n$, con $I_i = [s_i, f_i)$. Una soluzione ammissibile è una partizione degli intervalli in classi $C_1, \ldots, C_d$ tali che ogni classe contenga solo intervalli a due a due compatibili (non sovrapposti). La misura da minimizzare è il numero di classi $d$ usate — nell'interpretazione delle aule universitarie, il numero minimo di aule necessarie a ospitare tutte le lezioni senza conflitti di orario.

> [!question] Domanda tipica d'esame — definizione formale del problema (variante II)
> **D:** «1. Si definisca formalmente il problema.» *(chiesto il 09/09/2025)*
> **R:** Dato un insieme di $n$ intervalli $I_1, \ldots, I_n$ (ciascuno con inizio $s_i$ e fine $f_i$), una soluzione ammissibile è una partizione degli intervalli in sottoinsiemi (classi) $C_1, \ldots, C_d$ tali che ogni classe contenga solo intervalli mutualmente compatibili; l'obiettivo è minimizzare il numero $d$ di classi.
### Lower bound: la profondità
Tutto il problema ruota attorno a una domanda: in ogni istante, quante lezioni sono **in corso contemporaneamente**? Il massimo di questo conteggio — il **picco di sovrapposizioni** — è la *profondità*, e si rivelerà essere **esattamente** il numero di aule necessarie.

> [!quote] Definizione — Profondità
> La **profondità** di un insieme di intervalli (considerati come intervalli **aperti**) è il massimo numero di intervalli che contengono contemporaneamente un dato punto dell'asse temporale:
> $$\text{depth} = \max_{t} \bigl|\{I_i : s_i \leq t < f_i\}\bigr|$$
> La convenzione di intervallo aperto a destra è coerente con la definizione di compatibilità: due intervalli con $f_i = s_j$ sono compatibili (non si sovrappongono).

> [!quote] Proprietà — Lower bound sulla profondità
> Qualunque soluzione ammissibile richiede almeno $\text{depth}$ classi: in ogni punto $t$ in cui si sovrappongono $\text{depth}$ intervalli, tali intervalli devono stare in classi distinte.

Questa proprietà fornisce un lower bound immediato e non dipende dall'algoritmo usato: vale per *ogni* soluzione possibile. L'intuizione è diretta: nell'istante di picco quelle $\text{depth}$ lezioni sono **tutte in corso insieme**, e due lezioni simultanee non possono condividere un'aula — quindi servono **almeno** $\text{depth}$ aule, qualunque strategia si adotti.

> [!warning] Profondità ≠ numero di conflitti
> Non confondere la profondità con il *numero di coppie di intervalli che si sovrappongono*: la profondità guarda **un singolo istante** e conta quanti intervalli sono attivi lì dentro — è un **picco di contemporaneità**, non un totale di conflitti. Esempio: i tre intervalli $[1,4]$, $[2,5]$, $[3,6]$ sono in corso **tutti insieme** nell'istante $t = 3.5$ → profondità $= 3$ → servono almeno $3$ aule.

> [!question] Domanda tipica d'esame — la depth e il suo ruolo nell'analisi
> **D:** «2. Si definisca il concetto di depth di un'istanza di IP e si discuta perché è importante per analizzare l'algoritmo greedy che risolve IP. (Max 5 righe.)» *(chiesto il 28/09/2022 e il 18/02/2025)*
> **R:** La depth di un'istanza è il numero massimo di intervalli che si sovrappongono in uno stesso istante (dimensione della clique massima nel grafo di intersezione). È importante perché costituisce un lower bound al numero di risorse necessarie per qualunque soluzione, e si dimostra che l'algoritmo greedy utilizza esattamente "depth" risorse, risultando quindi ottimo.
### Schemi greedy candidati e ordine corretto
Per Interval Partitioning il template greedy è: *considera le lezioni in un certo ordine; assegnala a una classe compatibile se esiste, altrimenti apri una nuova classe*. L'ordine corretto è **earliest start time** (ordine crescente di $s(j)$); gli altri ordini ammettono controesempi analoghi a quelli visti per Interval Scheduling.

> [!question] Domanda tipica d'esame — perché l'ordine per finish time non funziona per IP (I)
> **D:** «2. Si motivi perché un algoritmo greedy che ordina gli intervalli per finish time non trova la soluzione ottima. (Max 5 righe.)» *(chiesto il 09/09/2025)*
> **R:** Controesempio: $A=[0,4]$, $B=[1,2]$, $C=[3,7]$, $D=[5,6]$. La profondità è $2$ (nessun istante ha 3 intervalli sovrapposti: $A$ si sovrappone a $B$ e a $C$, $C$ si sovrappone a $D$, ma non esiste un istante con tre di essi insieme), quindi bastano 2 aule. Ordinando per finish time si processano nell'ordine $B(f=2), A(f=4), D(f=6), C(f=7)$: $B$ apre la classe 1; $A$ è incompatibile con la classe 1 ($0<2$) e apre la classe 2; $D$ è compatibile con la classe 1 ($5\geq2$) e vi entra (la classe 1 finisce ora a $6$); $C$ inizia a $3$ ed è incompatibile sia con la classe 1 (finisce a $6$) sia con la classe 2 (finisce a $4$), quindi apre una terza classe. Il greedy per finish time usa così 3 classi contro le 2 ottime: ordinare per tempo di fine non tiene conto di *quando* un intervallo diventa disponibile, solo di quando finisce, e quindi non è corretto per IP.

> [!question] Domanda tipica d'esame — perché l'ordine per finish time non funziona per IP (II)
> **D:** «2. Si mostri che l'algoritmo greedy che ordina gli intervalli per tempo di fine non trova sempre la soluzione ottima.» *(chiesto il 30/06/2026)*
> **R:** Basta lo stesso tipo di controesempio: $A=[0,4]$, $B=[1,2]$, $C=[3,7]$, $D=[5,6]$ ha profondità $2$, ma ordinando per finish time ($B,A,D,C$) l'algoritmo apre 3 classi — $A$ apre subito una seconda classe perché inizia prima che $B$ liberi la prima, e quando arriva $C$ nessuna delle due classi aperte si è ancora liberata in tempo. L'ordine per tempo di fine ignora il momento in cui un intervallo *diventa disponibile* (il suo start), che è invece l'informazione decisiva per decidere quando aprire una nuova classe: per questo non garantisce l'ottimo per Interval Partitioning.
### Algoritmo earliest-start-time-first
```pseudo
\begin{algorithm}
\caption{Earliest-Start-Time-First($J$) — partiziona $J$ nel minimo numero di classi}
\begin{algorithmic}
\State Ordina $J$ in ordine crescente di $s(j)$
\State $d \gets 0$ \Comment{numero di classi allocate}
\ForAll{$j \in J$ nell'ordine}
  \If{esiste una classe $k$ compatibile con la lezione $j$}
    \State Schedula la lezione $j$ nella classe $k$
  \Else
    \State $d \gets d + 1$
    \State Schedula la lezione $j$ nella nuova classe $d$
  \EndIf
\EndFor
\State \Return $\text{schedule}$
\end{algorithmic}
\end{algorithm}
```

> [!info] Implementazione efficiente con coda con priorità — $O(n \log n)$
> La chiave per l'efficienza è scegliere opportunamente "quale" classe compatibile usare quando ce ne sono più di una. Si usa una **[[07 - Code con Priorità e Heap|coda con priorità (min-heap)]]** con chiave = tempo di fine dell'ultima lezione nella classe:
> - **INSERT** per aprire una nuova classe.
> - **FIND-MIN** per trovare la classe con il tempo di fine più precoce: se $f_{\min} \leq s(j)$ la lezione $j$ è compatibile e viene assegnata a quella classe.
> - **INCREASE-KEY** (o equivalente) per aggiornare il tempo di fine della classe appena usata a $f(j)$.
>
> Totale: $O(n)$ operazioni sulla coda, ciascuna $O(\log n)$ → $O(n \log n)$ complessivo (più $O(n \log n)$ per l'ordinamento).
>
> **Osservazione:** questa implementazione sceglie sempre la classe con il finish time più precoce compatibile con $j$ — una scelta localmente ottima che non influisce sulla correttezza ma è naturale con un min-heap.
### Esempio di esecuzione
10 lezioni (a–j) distribuite in una giornata; l'algoritmo le processa per ora di inizio e le assegna a 3 aule:

```
Aula 3:  c[9-10]       d[11-12]        f[13-14]          j[14:30-15:30]
Aula 2:     b[9:30-10:30]           g[13-14]          i[14:30-15:30]
Aula 1:  a[9-10]          e[11:30-12:30]          h[14-15]
         9   10  10:30 11  12  13  13:30 14  14:30 15
```

La profondità massima è 3 (alle ore 9:30–10 si sovrappongono $a$, $b$, $c$), e l'algoritmo alloca esattamente 3 aule: ottimo.
### Dimostrazione di ottimalità
> [!info] Osservazione — Correttezza delle assegnazioni
> L'algoritmo earliest-start-time-first non schedula mai due lezioni incompatibili nella stessa classe: una nuova lezione viene assegnata a una classe solo se il suo start time è $\geq$ del finish time dell'ultima lezione già assegnata a quella classe.

> [!quote] Teorema — Ottimalità di earliest-start-time-first
> L'algoritmo earliest-start-time-first alloca esattamente $\text{depth}$ classi, ed è quindi ottimale.

**Dimostrazione.** Sia $d$ il numero di classi allocate dall'algoritmo; si vuole mostrare che $d = \text{depth}$.

*Passo 0 — la soluzione è ammissibile.* Per l'Osservazione qui sopra, l'algoritmo non assegna mai due lezioni incompatibili alla stessa classe: quella prodotta è dunque una soluzione valida.

*Parte A — $d \geq \text{depth}$.*
1. Per la proprietà di lower bound, **ogni** soluzione ammissibile richiede almeno $\text{depth}$ classi.
2. La soluzione dell'algoritmo è ammissibile (Passo 0).
3. Perciò $d \geq \text{depth}$. $\square$

*Parte B — $\text{depth} \geq d$.*
1. Consideriamo il momento in cui l'algoritmo apre la classe numero $d$ (l'ultima), e sia $j$ la lezione che ne ha forzato l'apertura.
2. L'algoritmo apre una classe nuova solo se $j$ è **incompatibile** con l'ultima lezione di **ognuna** delle $d-1$ classi già aperte.
3. "Incompatibile" significa che quella lezione **finisce dopo $s(j)$**, cioè è ancora in corso quando $j$ inizia.
4. Le lezioni sono processate in **ordine di inizio crescente**, quindi ognuna di quelle $d-1$ lezioni ha inizio $\leq s(j)$.
5. Da (3) e (4): ognuna di quelle $d-1$ lezioni soddisfa $\text{inizio} \leq s(j) < \text{fine}$, cioè è **attiva nell'istante $s(j)$**.
6. Aggiungendo anche $j$, nell'istante $s(j)$ coesistono **$d$ lezioni simultaneamente attive**.
7. Per definizione di profondità, $\text{depth} \geq d$. $\square$

*Conclusione.* Da A e B segue $d = \text{depth}$: l'algoritmo usa esattamente il numero minimo di classi, quindi è **ottimale**. $\square$

> [!question] Domanda tipica d'esame — cos'è la profondità e che ruolo ha nell'ottimalità?
> **D:** Cos'è la profondità di un insieme di intervalli e che ruolo ha nella dimostrazione di ottimalità di Interval Partitioning?
> **R:** La profondità è il **massimo numero di intervalli che si sovrappongono in uno stesso istante** $t$ (non un conteggio dei conflitti totali, ma il picco di contemporaneità). Poiché intervalli sovrapposti devono stare in classi distinte, ogni soluzione richiede almeno $\text{depth}$ classi: è un **lower bound**. L'algoritmo *earliest-start-time-first* alloca **esattamente** $\text{depth}$ classi — quando apre la $d$-esima esibisce $d$ intervalli sovrapposti in un punto, quindi $\text{depth} \geq d$ — e combinando col lower bound $d = \text{depth}$ → ottimo.

> [!question] Domanda tipica d'esame — correttezza dell'ordine per tempo di inizio
> **D:** «3. Si argomenti sulla correttezza dell'algoritmo greedy che ordina gli intervalli per tempo di inizio. (Max 10 righe.)» *(chiesto il 30/06/2026)*
> **R:** La correttezza si dimostra mostrando che il numero di classi $d$ allocate dall'algoritmo earliest-start-time-first coincide con la profondità $\text{depth}$. Da un lato, poiché ogni soluzione ammissibile richiede almeno $\text{depth}$ classi (lower bound: intervalli sovrapposti devono stare in classi diverse) e la soluzione del greedy è ammissibile, si ha $d \geq \text{depth}$. Dall'altro, quando il greedy apre la $d$-esima classe per una lezione $j$, è perché $j$ è incompatibile con l'ultima lezione di ciascuna delle $d-1$ classi già aperte; processando in ordine di inizio crescente, quelle $d-1$ lezioni hanno inizio $\leq s(j)$ e finiscono dopo $s(j)$ (altrimenti $j$ sarebbe compatibile), quindi sono tutte attive nell'istante $s(j)$ insieme a $j$ stesso: $d$ lezioni simultaneamente attive implicano $\text{depth} \geq d$. Le due disuguaglianze danno $d = \text{depth}$, il minimo possibile: l'algoritmo è ottimo.
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per start time | $O(n \log n)$ |
| Ciclo con operazioni sulla coda con priorità | $O(n \log n)$ |
| **Totale** | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — implementazione in $O(n \log n)$ col min-heap
> **D:** Come si implementa Interval Partitioning in $O(n \log n)$ e perché basta un min-heap?
> **R:** Dopo l'ordinamento per start time ($O(n \log n)$) si tiene un **min-heap** di classi con chiave = finish time dell'ultima lezione della classe. Per ogni lezione $j$ si guarda il minimo (FIND-MIN): se quella classe è compatibile ($f_{\min} \leq s(j)$) vi si assegna $j$ e si aggiorna la chiave a $f(j)$ (INCREASE-KEY), altrimenti si apre una nuova classe (INSERT). Sono $O(n)$ operazioni da $O(\log n)$ → $O(n \log n)$. Basta il min-heap perché l'unica classe che può accogliere $j$ è quella che si libera prima: se non basta lei, non ne basta nessuna.

> [!question] Domanda tipica d'esame — algoritmo e complessità (senza correttezza)
> **D:** «3. Si descriva invece l'algoritmo greedy ottimo per il problema discutendone la complessità computazionale (non si discuta la correttezza). (Max 5 righe.)» *(chiesto il 09/09/2025)*
> **R:** L'algoritmo earliest-start-time-first ordina gli intervalli per tempo di inizio crescente ($O(n \log n)$) e li scandisce una volta: per ciascuno cerca, tramite un min-heap di classi con chiave = finish time dell'ultima lezione assegnata, la classe con finish time minimo; se è compatibile ($f_{\min} \leq s(j)$) vi assegna $j$ e aggiorna la chiave (INCREASE-KEY), altrimenti apre una nuova classe (INSERT). Le $n$ operazioni sul min-heap costano $O(\log n)$ ciascuna, per un totale di $O(n \log n)$, dello stesso ordine dell'ordinamento iniziale: complessità complessiva $O(n \log n)$.
## Confronto riassuntivo
| Problema | Obiettivo | Ordine greedy | Struttura ausiliaria | Complessità |
|---|---|---|---|---|
| Interval Scheduling | max job compatibili | Earliest finish time | — (solo variabile $j^*$) | $O(n \log n)$ |
| Interval Partitioning | min classi (aule) | Earliest start time | Min-heap per finish time classi | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — perché ordini diversi nei due problemi?
> **D:** Perché Interval Scheduling ordina per tempo di *fine* e Interval Partitioning per tempo di *inizio*?
> **R:** Perché gli obiettivi sono opposti. In *Scheduling* (una sola risorsa, massimizzare i job) conviene liberare la risorsa il prima possibile → si guarda **chi finisce prima**. In *Partitioning* (servirli tutti, minimizzare le risorse) si processano le lezioni **in ordine di inizio** e si conta quante devono coesistere: il picco di sovrapposizioni (la **profondità**) è il numero minimo di aule, e il greedy lo raggiunge esattamente.
