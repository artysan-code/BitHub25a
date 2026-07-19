---
tags:
  - algoritmi
  - greedy
slide: "1"
capitolo: "Kleinberg-Tardos cap. 4"
---
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
> **R:**
> **Input.** Un insieme di $n$ intervalli $I_1, \ldots, I_n$, ciascuno con tempo di inizio $s_i$ e tempo di fine $f_i$.
>
> **Soluzione ammissibile.** Un sottoinsieme $S$ di intervalli a due a due compatibili, cioè tali che per ogni coppia $I_i, I_j \in S$ risulti $f_i \leq s_j$ oppure $f_j \leq s_i$ (non si sovrappongono).
>
> **Misura.** La cardinalità $|S|$ da **massimizzare**: il numero di job schedulabili sulla singola risorsa.
>
> ⏱️ **Se la traccia dà 5 righe**: dai le tre componenti (input, ammissibilità, misura) in una riga ciascuna, con la formula di compatibilità scritta per esteso — **non va mai omessa**, è l'unico punto realmente verificabile della definizione.
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
> **R:**
> **Controesempio.** Tre job $[0,3]$, $[3,6]$, $[2,4]$ (è lo stesso controesempio del criterio *shortest interval*).
>
> **Comportamento del greedy.** Ordina per durata crescente e sceglie per primo $[2,4]$ (durata 2), che si sovrappone sia a $[0,3]$ sia a $[3,6]$: la soluzione greedy contiene un **solo** job.
>
> **Ottimo.** Prende $[0,3]$ e $[3,6]$, compatibili tra loro ($f=3 \leq s=3$): **2 job**, strettamente meglio.
>
> **Conclusione.** Il criterio "durata minima" non è ottimo: minimizzare $f_i - s_i$ non tiene conto di quanti altri job un intervallo corto ma mal posizionato può escludere.
>
> ⏱️ **Se la traccia dà 3 righe**: basta il controesempio numerico con l'esito dei due confronti (1-2 righe) e la conclusione in una riga — **il controesempio numerico non va mai omesso**, è l'unica cosa che la traccia sta davvero chiedendo.

> [!question] Domanda tipica d'esame — controesempio all'ordine per lunghezza crescente
> **D:** «B. Si argomenti sul perché l'algoritmo greedy che guarda gli intervalli in ordine crescente di lunghezza non calcola una soluzione ottima. (Max 3 righe.)» *(chiesto il 19/02/2024)*
> **R:**
> **Idea del controesempio.** Basta un intervallo corto **incompatibile** con due o più intervalli più lunghi che sono invece compatibili tra loro: il greedy lo sceglie per primo (è il più corto) ed esclude entrambi gli altri.
>
> **Istanza concreta.** $[0,3]$, $[3,6]$, $[2,4]$: il greedy per lunghezza crescente prende $[2,4]$ e si ferma a 1 job, mentre $[0,3]$ e $[3,6]$ sono compatibili tra loro e danno 2 job.
>
> **Conclusione.** L'ordine per lunghezza crescente non è ottimo, perché ignora quanti job compatibili un intervallo corto può "bloccare" se posizionato al centro.
>
> ⏱️ **Se la traccia dà 3 righe**: descrivi lo schema del controesempio in una riga e chiudi con l'istanza numerica e il confronto 1 vs 2 job — **l'istanza concreta non va mai omessa**, "si può costruire un controesempio" da solo non è una dimostrazione.
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
> **R:**
> **Risposta.** L'algoritmo A considera i job in ordine **non decrescente del tempo di fine** $f_i$ (earliest finish time first).
>
> **Dettaglio.** Li ordina per $f_i$ crescente in un unico passo iniziale e poi li scandisce una sola volta in quell'ordine, senza più riordinarli.
>
> ⏱️ **Se la traccia dà una riga**: scrivi solo "ordine non decrescente di tempo di fine $f_i$" — **il nome del criterio (earliest finish time) non va mai omesso**, è quello che la domanda vuole verificare.

> [!question] Domanda tipica d'esame — V/F sull'ordinamento per finish time
> **D:** *(Vero o Falso)* «Uno step fondamentale dell'algoritmo Greedy ALG-G(I) è quello di ordinare gli intervalli I_j rispetto al finish time.» *(chiesto il 12/09/2023)*
> **R:**
> **Risposta.** Vero.
>
> **Perché.** Il primo passo dell'algoritmo (riga 1 dello pseudocodice) è proprio l'ordinamento di $J$ in ordine crescente di $f(j)$.
>
> **Osservazione.** È il passo che rende poi possibile la scansione lineare $O(n)$ con confronto $O(1)$ ad ogni iterazione, ed è quello che domina asintoticamente il costo totale (l'ordinamento $O(n \log n)$ contro l'$O(n)$ della scansione).

> [!question] Domanda tipica d'esame — il criterio di ordinamento corretto (I)
> **D:** «C. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema.» *(chiesto il 19/02/2024)*
> **R:**
> **Criterio.** Ordine crescente di tempo di fine (finishing time) $f(j)$.
>
> **Procedura.** Si scandiscono gli intervalli in quest'ordine e si seleziona **greedily** ogni intervallo compatibile con l'ultimo intervallo già scelto, senza mai tornare indietro sulle scelte fatte.

> [!question] Domanda tipica d'esame — il criterio di ordinamento corretto (II)
> **D:** «B. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema. (Max 2 righe.)» *(chiesto il 21/01/2025)*
> **R:**
> **Criterio.** Ordine crescente di tempo di fine $f(j)$ — il criterio *earliest finish time* dell'algoritmo A.
>
> **Perché proprio questo.** È l'unico dei quattro schemi candidati (start time, finish time, durata, numero di conflitti) che garantisce l'ottimalità; gli altri tre ammettono controesempi.
>
> ⏱️ **Se la traccia dà 2 righe**: basta il criterio ("ordine crescente di tempo di fine $f(j)$") più la selezione greedy compatibile con l'ultimo scelto — **il nome del criterio non va mai omesso**, il confronto con gli altri tre schemi si taglia per primo.

> [!question] Domanda tipica d'esame — V/F sul divide et impera
> **D:** *(Vero o Falso)* «L'algoritmo ottimale Greedy ALG-G(I) spezza l'istanza iniziale in due sotto-istanze bilanciate in modo tale da applicare la tecnica del Divide et Impera, ottenendo un tempo di completamento O(n log n).» *(chiesto il 12/09/2023)*
> **R:**
> **Risposta.** Falso.
>
> **Perché è falsa.** L'algoritmo non spezza mai l'istanza in sotto-istanze ricorsive: non c'è alcun "divide" né alcuna ricombinazione di sotto-soluzioni.
>
> **Cosa fa realmente.** È un puro schema greedy: un ordinamento iniziale $O(n \log n)$ seguito da un'unica scansione lineare $O(n)$ che aggiunge o scarta ogni job senza mai tornare indietro. Il tempo totale $O(n \log n)$ è dominato dall'ordinamento, non da una ricorrenza di tipo divide-et-impera.
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
> **R:**
> **Enunciato.** Il lemma *greedy stays ahead*: detti $i_1, \ldots, i_k$ i job scelti dal greedy e $j_1, \ldots, j_m$ quelli di una soluzione ottima, entrambi ordinati per tempo di fine, per ogni $r = 1, \ldots, k$ vale $f(i_r) \leq f(j_r)$ — il greedy, passo per passo, non è mai "indietro" rispetto a nessuna soluzione ottima.
>
> **Caso base.** Il greedy sceglie subito il job con finish time minimo in assoluto, quindi $f(i_1) \leq f(j_1)$ per qualunque $j_1$.
>
> **Passo induttivo.** La compatibilità di $j_r$ con $j_{r-1}$ ($s(j_r) \geq f(j_{r-1})$) combinata con l'ipotesi induttiva $f(i_{r-1}) \leq f(j_{r-1})$ mostra che $j_r$ era un candidato disponibile anche per il greedy al passo $r$; il greedy prende sempre il candidato con finish time minimo, quindi $f(i_r) \leq f(j_r)$.
>
> **Conclusione.** Applicando il lemma con $r = k$ e ragionando per assurdo (se l'ottimo avesse $m > k$ job, il job $j_{k+1}$ sarebbe compatibile anche con tutta la soluzione greedy, che quindi l'avrebbe preso) si esclude $m > k$: il greedy è ottimo.
>
> ⏱️ **Se la traccia dà 5 righe**: enuncia il lemma con la disuguaglianza $f(i_r) \leq f(j_r)$ (1-2 righe), riassumi caso base e passo induttivo in una riga ciascuno, chiudi con l'argomento per assurdo in una riga — **la disuguaglianza del lemma e il passaggio all'assurdo non vanno mai omessi**, sono il nucleo dimostrativo.

> [!question] Domanda tipica d'esame — schema della dimostrazione di ottimalità (I)
> **D:** «D. Si dimostri a grandi linee perché l'algoritmo del punto (C) trova sempre una soluzione ottima del problema.» *(chiesto il 19/02/2024)*
> **R:**
> **Impostazione.** La dimostrazione usa *greedy stays ahead* in due passi: un lemma per induzione, poi un teorema per assurdo.
>
> **Lemma (per induzione su $r$).** Il job $i_r$ scelto dal greedy come $r$-esimo finisce non più tardi del $r$-esimo job $j_r$ di una qualunque soluzione ottima, cioè $f(i_r) \leq f(j_r)$: il caso base segue dal fatto che il greedy sceglie subito il job con finish time minimo assoluto, il passo induttivo dalla compatibilità di $j_r$ con $j_{r-1}$ combinata con l'ipotesi induttiva.
>
> **Teorema (per assurdo).** Se l'ottimo avesse $m > k$ job, il job $j_{k+1}$ risulterebbe compatibile con tutti gli $i_1, \ldots, i_k$ già scelti dal greedy (per il lemma applicato a $r = k$), e quindi il greedy stesso lo avrebbe aggiunto a $S$ proseguendo la scansione — contraddizione.
>
> **Conclusione.** Dunque $m = k$ e il greedy è ottimo.

> [!question] Domanda tipica d'esame — schema della dimostrazione di ottimalità (II)
> **D:** «C. Si dimostri a grandi linee perché l'algoritmo del punto (B) trova sempre una soluzione ottima del problema. (Max 10 righe.)» *(chiesto il 21/01/2025)*
> **R:**
> **Impostazione.** Tecnica *greedy stays ahead*: si confrontano i job scelti dal greedy $i_1, \ldots, i_k$ con quelli di una soluzione ottima $j_1, \ldots, j_m$, entrambi ordinati per tempo di fine.
>
> **Lemma (per induzione su $r$).** Per ogni $r$ vale $f(i_r) \leq f(j_r)$. Caso base: il greedy prende subito il job con finish time minimo in assoluto, quindi non può essere battuto da nessun $j_1$. Passo induttivo: la compatibilità di $j_r$ con $j_{r-1}$ dà $s(j_r) \geq f(j_{r-1})$, che con l'ipotesi induttiva $f(i_{r-1}) \leq f(j_{r-1})$ implica $s(j_r) \geq f(i_{r-1})$ — $j_r$ era quindi un candidato disponibile anche per il greedy al passo $r$, che sceglie sempre il candidato con finish time minimo.
>
> **Teorema (per assurdo).** Se fosse $m > k$, il job aggiuntivo $j_{k+1}$ dell'ottimo risulterebbe compatibile con tutta la soluzione greedy $i_1, \ldots, i_k$ (per il lemma con $r = k$), e il greedy lo avrebbe quindi incluso proseguendo la scansione — contraddizione.
>
> **Conclusione.** Perciò $m = k$: il greedy è ottimo.
>
> ⏱️ **Se la traccia dà 10 righe**: c'è spazio per il lemma completo con entrambi i passi (base e induttivo, 4-5 righe) e il teorema per assurdo con la contraddizione esplicita (3-4 righe) — **la disuguaglianza $f(i_r) \leq f(j_r)$ e il passaggio all'assurdo restano gli unici due elementi mai omissibili**; il resto (dettagli della compatibilità) è ciò che riempie lo spazio extra rispetto alla versione da 5 righe.

> [!question] Domanda tipica d'esame — V/F sull'exchange argument
> **D:** *(Vero o Falso)* «La dimostrazione di ottimalità dell'algoritmo Greedy ALG-G(I), basata sull'Exchange Argument, stabilisce che ogni soluzione ammissibile, che non è quella calcolata da ALG-G(I), ha un valore strettamente inferiore a quella ottenuta da ALG-G(I).» *(chiesto il 12/09/2023)*
> **R:**
> **Risposta.** Falso, per due motivi indipendenti.
>
> **Motivo 1 — tecnica sbagliata.** La dimostrazione di ottimalità di IS vista a lezione non usa l'*exchange argument* ma *greedy stays ahead* (il lemma $f(i_r) \leq f(j_r)$ per induzione, seguito da assurdo).
>
> **Motivo 2 — falso anche a tecnica corretta.** Possono esistere più soluzioni ammissibili di cardinalità massima **uguale** a quella del greedy: più insiemi distinti di job compatibili possono raggiungere lo stesso $|S|$ ottimo. Non è quindi vero che ogni altra soluzione abbia valore *strettamente* inferiore.
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Scansione e costruzione di $S$ | $O(n)$ |
| **Totale** | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — perché *earliest finish time* e non *earliest start time*?
> **D:** Perché l'ordine per tempo di inizio non funziona per Interval Scheduling, mentre quello per tempo di fine sì?
> **R:**
> **Comportamento di earliest start time.** Il primo job scelto potrebbe iniziare prestissimo ma durare arbitrariamente a lungo (es. $[0,100]$).
>
> **Causa del fallimento.** Un job così lungo blocca tutti i job successivi, anche se questi sono compatibili tra loro: la risorsa resta occupata inutilmente a lungo.
>
> **Perché earliest finish time invece funziona.** Libera la risorsa il prima possibile, massimizzando le opportunità future; la correttezza si prova con *greedy stays ahead* ($f(i_r) \leq f(j_r)$ per induzione) e chiusura per assurdo.

> [!question] Domanda tipica d'esame — perché il test di compatibilità è $O(1)$?
> **D:** Perché per verificare un nuovo job basta confrontarlo con l'ultimo selezionato $j^*$, e non con tutti quelli già in $S$?
> **R:**
> **Osservazione chiave.** I job sono processati in ordine di finish time crescente, quindi $j^*$ (l'ultimo aggiunto a $S$) ha sempre il **finish time massimo** fra quelli in $S$.
>
> **Perché basta confrontarsi con $j^*$.** Se il nuovo job è compatibile con $j^*$ lo è automaticamente con tutti gli altri elementi di $S$, che finiscono ancora prima: basta un confronto $s(j) \geq f(j^*)$, cioè $O(1)$ per job invece di $O(|S|)$.
>
> **Conseguenza sulla complessità.** Il ciclo costa $O(n)$ complessivo; il totale $O(n \log n)$ dell'algoritmo è quindi dominato dall'ordinamento iniziale, non dalla scansione.
## Interval Partitioning
### Definizione del problema
> [!quote] Definizione — Interval Partitioning
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** una partizione degli intervalli in sottoinsiemi $C_1, \ldots, C_d$ (detti **classi** o **aule**) tali che ogni $C_i$ contiene solo intervalli mutualmente compatibili.
> **Misura (da minimizzare):** il numero di classi $d$.

Il problema modella l'assegnamento di lezioni universitarie alle aule: ogni lezione ha un orario fisso e non può essere spostata, si vuole minimizzare il numero di aule necessarie.

> [!question] Domanda tipica d'esame — definizione formale di IP
> **D:** «1. Si definisca formalmente il problema di IP. (Max 5 righe.)» *(chiesto il 28/09/2022 e il 18/02/2025)*
> **R:**
> **Input.** Un insieme di $n$ intervalli (job) $I_1, \ldots, I_n$, ciascuno con tempo di inizio $s_i$ e tempo di fine $f_i$.
>
> **Soluzione ammissibile.** Un'assegnazione di un'etichetta (risorsa/aula) a ciascun intervallo tale che due intervalli che si sovrappongono ricevano etichette **diverse**.
>
> **Misura.** Il numero totale di etichette (risorse) utilizzate, da **minimizzare**.
>
> ⏱️ **Se la traccia dà 5 righe**: dai le tre componenti in una riga ciascuna, con la condizione "sovrapposti → etichette diverse" scritta esplicitamente — **quella condizione non va mai omessa**, è l'unico vincolo che rende la definizione verificabile.

> [!question] Domanda tipica d'esame — definizione formale del problema (variante I)
> **D:** «1. Si definisca formalmente il problema. (Max 5 righe.)» *(chiesto il 30/06/2026)*
> **R:**
> **Input.** Un insieme di $n$ intervalli $I_1, \ldots, I_n$, con $I_i = [s_i, f_i)$.
>
> **Soluzione ammissibile.** Una partizione degli intervalli in classi $C_1, \ldots, C_d$ tali che ogni classe contenga solo intervalli a due a due compatibili (non sovrapposti).
>
> **Misura.** Il numero di classi $d$ usate, da **minimizzare** — nell'interpretazione delle aule universitarie, il numero minimo di aule necessarie a ospitare tutte le lezioni senza conflitti di orario.
>
> ⏱️ **Se la traccia dà 5 righe**: le tre componenti in una riga ciascuna bastano; se resta spazio aggiungi l'interpretazione delle aule, ma **la condizione di compatibilità a due a due dentro ogni classe non va mai omessa**.

> [!question] Domanda tipica d'esame — definizione formale del problema (variante II)
> **D:** «1. Si definisca formalmente il problema.» *(chiesto il 09/09/2025)*
> **R:**
> **Input.** Un insieme di $n$ intervalli $I_1, \ldots, I_n$, ciascuno con inizio $s_i$ e fine $f_i$.
>
> **Soluzione ammissibile.** Una partizione degli intervalli in sottoinsiemi (classi) $C_1, \ldots, C_d$ tali che ogni classe contenga solo intervalli mutualmente compatibili.
>
> **Misura.** Il numero $d$ di classi, da **minimizzare**.
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
> **R:**
> **Definizione.** La depth di un'istanza è il numero massimo di intervalli che si sovrappongono in uno stesso istante (equivalentemente, la dimensione della clique massima nel grafo di intersezione).
>
> **Ruolo come lower bound.** Costituisce un limite inferiore al numero di risorse necessarie per **qualunque** soluzione ammissibile: nell'istante di picco quegli intervalli devono stare in classi distinte.
>
> **Perché rende l'algoritmo ottimo.** Si dimostra che l'algoritmo greedy earliest-start-time-first utilizza esattamente $\text{depth}$ classi; combinando questo fatto con il lower bound, $d = \text{depth}$ è il minimo possibile, quindi l'algoritmo è ottimo.
>
> ⏱️ **Se la traccia dà 5 righe**: definizione in una riga, lower bound in una riga, e la chiusura "greedy usa esattamente depth classi → ottimo" in una riga — **il collegamento lower bound + uguaglianza raggiunta dal greedy non va mai omesso**, è quello che trasforma la depth in un argomento di ottimalità e non solo una definizione.
### Schemi greedy candidati e ordine corretto
Per Interval Partitioning il template greedy è: *considera le lezioni in un certo ordine; assegnala a una classe compatibile se esiste, altrimenti apri una nuova classe*. L'ordine corretto è **earliest start time** (ordine crescente di $s(j)$); gli altri ordini ammettono controesempi analoghi a quelli visti per Interval Scheduling.

> [!question] Domanda tipica d'esame — perché l'ordine per finish time non funziona per IP (I)
> **D:** «2. Si motivi perché un algoritmo greedy che ordina gli intervalli per finish time non trova la soluzione ottima. (Max 5 righe.)» *(chiesto il 09/09/2025)*
> **R:**
> **Istanza e ottimo.** $A=[0,4]$, $B=[1,2]$, $C=[3,7]$, $D=[5,6]$. La profondità è $2$ (nessun istante ha 3 intervalli sovrapposti), quindi bastano 2 aule.
>
> **Comportamento del greedy per finish time.** Processando nell'ordine $B(f=2), A(f=4), D(f=6), C(f=7)$: $B$ apre la classe 1; $A$ è incompatibile con la classe 1 ($0<2$) e apre la classe 2; $D$ è compatibile con la classe 1 ($5\geq2$) e vi entra (la classe 1 finisce ora a $6$); $C$ inizia a $3$ ed è incompatibile sia con la classe 1 (finisce a $6$) sia con la classe 2 (finisce a $4$), quindi apre una **terza** classe.
>
> **Causa.** Ordinare per tempo di fine non tiene conto di *quando* un intervallo diventa disponibile (il suo start), solo di quando finisce.
>
> **Conclusione.** Il greedy per finish time usa 3 classi contro le 2 ottime: non è corretto per IP.
>
> ⏱️ **Se la traccia dà 5 righe**: l'istanza numerica con la profondità (1 riga), il conteggio delle classi aperte dal greedy per finish time senza il dettaglio passo-passo (1-2 righe), causa e conclusione in una riga — **l'istanza concreta e il conteggio 3 vs 2 non vanno mai omessi**, il dettaglio passo-passo si taglia per primo.

> [!question] Domanda tipica d'esame — perché l'ordine per finish time non funziona per IP (II)
> **D:** «2. Si mostri che l'algoritmo greedy che ordina gli intervalli per tempo di fine non trova sempre la soluzione ottima.» *(chiesto il 30/06/2026)*
> **R:**
> **Controesempio.** $A=[0,4]$, $B=[1,2]$, $C=[3,7]$, $D=[5,6]$ ha profondità $2$, ma ordinando per finish time ($B,A,D,C$) l'algoritmo apre 3 classi: $A$ apre subito una seconda classe perché inizia prima che $B$ liberi la prima, e quando arriva $C$ nessuna delle due classi aperte si è ancora liberata in tempo.
>
> **Causa.** L'ordine per tempo di fine ignora il momento in cui un intervallo *diventa disponibile* (il suo start), che è invece l'informazione decisiva per decidere quando aprire una nuova classe.
>
> **Conclusione.** Per questo l'ordine per finish time non garantisce l'ottimo per Interval Partitioning.
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
> **R:**
> **Definizione.** La profondità è il **massimo numero di intervalli che si sovrappongono in uno stesso istante** $t$ — non un conteggio dei conflitti totali, ma il picco di contemporaneità.
>
> **Lower bound.** Poiché intervalli sovrapposti devono stare in classi distinte, ogni soluzione ammissibile richiede almeno $\text{depth}$ classi: $d \geq \text{depth}$ per qualunque soluzione.
>
> **L'algoritmo raggiunge il bound.** *Earliest-start-time-first* alloca **esattamente** $\text{depth}$ classi: quando apre la $d$-esima classe esibisce $d$ intervalli simultaneamente attivi, quindi $\text{depth} \geq d$.
>
> **Conclusione.** Combinando le due disuguaglianze, $d = \text{depth}$: l'algoritmo usa il numero minimo possibile di classi, quindi è ottimo.

> [!question] Domanda tipica d'esame — correttezza dell'ordine per tempo di inizio
> **D:** «3. Si argomenti sulla correttezza dell'algoritmo greedy che ordina gli intervalli per tempo di inizio. (Max 10 righe.)» *(chiesto il 30/06/2026)*
> **R:**
> **Impostazione.** La correttezza si dimostra mostrando che il numero di classi $d$ allocate dall'algoritmo earliest-start-time-first coincide con la profondità $\text{depth}$, tramite due disuguaglianze.
>
> **Caso 1 — $d \geq \text{depth}$.** Ogni soluzione ammissibile richiede almeno $\text{depth}$ classi (lower bound: intervalli sovrapposti devono stare in classi diverse); la soluzione del greedy è ammissibile, quindi $d \geq \text{depth}$.
>
> **Caso 2 — $\text{depth} \geq d$.** Quando il greedy apre la $d$-esima classe per una lezione $j$, è perché $j$ è incompatibile con l'ultima lezione di ciascuna delle $d-1$ classi già aperte. Processando in ordine di inizio crescente, quelle $d-1$ lezioni hanno inizio $\leq s(j)$ e finiscono dopo $s(j)$ (altrimenti $j$ sarebbe compatibile con almeno una), quindi sono tutte attive nell'istante $s(j)$ insieme a $j$ stesso: $d$ lezioni simultaneamente attive implicano $\text{depth} \geq d$.
>
> **Conclusione.** Le due disuguaglianze danno $d = \text{depth}$, il minimo possibile per il lower bound: l'algoritmo è ottimo.
>
> ⏱️ **Se la traccia dà 10 righe**: c'è spazio per entrambi i casi con la giustificazione completa (3-4 righe ciascuno) più impostazione e conclusione — **le due disuguaglianze $d \geq \text{depth}$ e $\text{depth} \geq d$ non vanno mai omesse**, sono l'intera struttura della dimostrazione; se lo spazio si restringe, il dettaglio da tagliare per primo è la spiegazione di perché quelle $d-1$ lezioni sono attive in $s(j)$.
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per start time | $O(n \log n)$ |
| Ciclo con operazioni sulla coda con priorità | $O(n \log n)$ |
| **Totale** | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — implementazione in $O(n \log n)$ col min-heap
> **D:** Come si implementa Interval Partitioning in $O(n \log n)$ e perché basta un min-heap?
> **R:**
> **Idea.** Mantenere un **min-heap** di classi con chiave = finish time dell'ultima lezione della classe, dopo aver ordinato le lezioni per start time.
>
> **Procedura.** Per ogni lezione $j$, in ordine di $s(j)$ crescente: si guarda il minimo del heap (FIND-MIN); se quella classe è compatibile ($f_{\min} \leq s(j)$) vi si assegna $j$ e si aggiorna la chiave a $f(j)$ (INCREASE-KEY), altrimenti si apre una nuova classe (INSERT).
>
> **Perché basta il min-heap.** L'unica classe che può accogliere $j$ è quella che si libera prima: se non basta lei (la più favorevole), non ne basta nessuna delle altre.
>
> **Complessità.** Ordinamento iniziale $O(n \log n)$, più $n$ operazioni sul heap da $O(\log n)$ ciascuna → $O(n \log n)$ complessivo.

> [!question] Domanda tipica d'esame — algoritmo e complessità (senza correttezza)
> **D:** «3. Si descriva invece l'algoritmo greedy ottimo per il problema discutendone la complessità computazionale (non si discuta la correttezza). (Max 5 righe.)» *(chiesto il 09/09/2025)*
> **R:**
> **Idea.** L'algoritmo earliest-start-time-first ordina gli intervalli per tempo di inizio crescente e li scandisce una volta sola.
>
> **Procedura.** Per ciascuna lezione cerca, tramite un min-heap di classi con chiave = finish time dell'ultima lezione assegnata, la classe con finish time minimo; se è compatibile ($f_{\min} \leq s(j)$) vi assegna $j$ e aggiorna la chiave (INCREASE-KEY), altrimenti apre una nuova classe (INSERT).
>
> **Complessità.** Ordinamento $O(n \log n)$; le $n$ operazioni sul min-heap costano $O(\log n)$ ciascuna, per un totale di $O(n \log n)$ dello stesso ordine — complessità complessiva $O(n \log n)$.
>
> ⏱️ **Se la traccia dà 5 righe**: idea in una riga, procedura in 2-3 righe (ordinamento + min-heap con le due operazioni FIND-MIN/INCREASE-KEY o INSERT), complessità in una riga finale — **il totale $O(n \log n)$ con la sua giustificazione (ordinamento + $n$ operazioni da $O(\log n)$) non va mai omesso**, è quello che la traccia chiede esplicitamente.
## Confronto riassuntivo
| Problema | Obiettivo | Ordine greedy | Struttura ausiliaria | Complessità |
|---|---|---|---|---|
| Interval Scheduling | max job compatibili | Earliest finish time | — (solo variabile $j^*$) | $O(n \log n)$ |
| Interval Partitioning | min classi (aule) | Earliest start time | Min-heap per finish time classi | $O(n \log n)$ |

> [!question] Domanda tipica d'esame — perché ordini diversi nei due problemi?
> **D:** Perché Interval Scheduling ordina per tempo di *fine* e Interval Partitioning per tempo di *inizio*?
> **R:**
> **Causa comune.** Gli obiettivi dei due problemi sono opposti.
>
> **Interval Scheduling.** Una sola risorsa, si vuole massimizzare i job schedulati → conviene liberare la risorsa il prima possibile, quindi si guarda **chi finisce prima** (earliest finish time).
>
> **Interval Partitioning.** Si vogliono servire tutte le lezioni minimizzando le risorse → si processano le lezioni **in ordine di inizio** e si conta quante devono coesistere: il picco di sovrapposizioni (la **profondità**) è il numero minimo di aule, e il greedy lo raggiunge esattamente.
