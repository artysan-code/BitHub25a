---
tags:
  - algoritmi
  - greedy
slide: ["01"]
capitolo: "Kleinberg-Tardos cap. 4"
---
# Greedy e Interval Scheduling
Il paradigma **greedy** (goloso) affronta problemi di ottimizzazione costruendo la soluzione passo dopo passo: ad ogni passo si compie la scelta *localmente* ottima — senza ritornare indietro — sperando (e dimostrando!) che la sequenza di scelte locali produca la soluzione *globalmente* ottima. Non tutti i problemi ammettono algoritmi greedy corretti: la difficoltà sta nel dimostrare l'ottimalità, tipicamente tramite *greedy stays ahead* o un argomento di scambio (*exchange argument*). Questa nota introduce il paradigma e lo applica ai problemi di Interval Scheduling e Interval Partitioning. Per gli algoritmi di ordinamento richiamati nell'analisi della complessità vedere [[04 - Algoritmi di Ordinamento]]; per la struttura dati coda con priorità usata in Interval Partitioning vedere [[07 - Code con Priorità e Heap]]. Gli item d'esame su questi due problemi stanno nella palestra [[Esercizi 01 - Greedy e Interval Scheduling]], richiamata sezione per sezione.
## Il paradigma Greedy
Un algoritmo **greedy** costruisce la soluzione **un pezzo alla volta**: a ogni passo compie la scelta che sembra migliore *in quel momento* — la scelta *localmente* ottima — e **non la rimette mai in discussione**. Non esplora alternative, non torna indietro, non confronta soluzioni complete tra loro. È questo a renderlo **semplice e veloce**: quasi sempre un **ordinamento** seguito da una **scansione lineare**. Il prezzo della rapidità è che le scelte locali **non è detto** convergano all'ottimo globale.

Lo schema di un greedy è quasi sempre lo stesso:
1. si fissa un **criterio d'ordine** con cui esaminare gli elementi;
2. si scorrono gli elementi in quell'ordine e si **aggiunge** alla soluzione quello corrente se è *ammissibile* (compatibile con le scelte già fatte);
3. non si ripensa **mai** a una scelta passata.

> [!warning] Il criterio è tutto — e l'ottimalità va dimostrata
> Il cuore di un algoritmo greedy è **quale** criterio d'ordine si sceglie: lo stesso problema ne ammette molti plausibili e, in generale, **solo alcuni portano all'ottimo**. Per Interval Scheduling vedremo che su 4 criteri ragionevoli **solo uno** (earliest finish time) funziona. Un greedy quindi **non è mai "ovviamente" corretto**: l'ottimalità va *provata*, non data per scontata. E se non riesci a dimostrarla, spesso è il segnale che il problema chiede la [[04 - Programmazione Dinamica I (Weighted Independent Set)|programmazione dinamica]], non un greedy.
### Tecniche di dimostrazione dell'ottimalità *(extra nel nome, non nel contenuto)*
Le due tecniche standard per dimostrare che un algoritmo greedy è ottimo sono le seguenti. I **nomi** non compaiono nelle slide del corso — che presentano la dimostrazione di Interval Scheduling come «Lemma + Teorema per assurdo», senza etichettarla — e vengono da Kleinberg-Tardos §4.1; ricorrono però nelle tracce d'esame (es. la V/F del 12/09/2023 qui sotto, che cita l'*Exchange Argument*), quindi vanno conosciuti per nome. Il *contenuto* invece è materia d'esame piena: la proprietà di *greedy stays ahead* è stata chiesta per esteso il 22/06/2022 (Es. 2.3, «Max 5 righe»).

> [!quote] Proprietà — Greedy stays ahead
> Si dimostra che, ad ogni passo $r$, la soluzione parziale greedy è "almeno buona quanto" qualunque soluzione parziale ottima fino allo stesso passo. Formalmente, si esibisce una misura quantitativa $\phi(r)$ tale che $\phi_{\text{greedy}}(r) \leq \phi_{\text{OPT}}(r)$ (o $\geq$, a seconda della misura), e si procede per induzione su $r$. L'ottimalità globale segue applicando il lemma all'ultimo passo.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#La proprietà chiave che dimostra l'ottimalità|la proprietà chiave — 22/06/2022, max 5 righe]]

> [!quote] Proprietà — Exchange argument (argomento di scambio)
> Si prende una soluzione ottima $\text{OPT}$ qualunque e si mostra che è possibile trasformarla nella soluzione greedy $G$ tramite una sequenza di piccole modifiche (**scambi**), senza peggiorarne il valore. Ogni scambio sostituisce un elemento di $\text{OPT}$ con il corrispondente elemento scelto dal greedy, e si dimostra che il valore non decresce. Al termine si conclude $\text{cost}(G) \geq \text{cost}(\text{OPT})$ e quindi $G$ è ottimo.

> [!info] Come si legge — quale tecnica di dimostrazione usare
> "Greedy stays ahead" è la tecnica naturale quando la soluzione cresce per aggiunta incrementale (come in Interval Scheduling). L'exchange argument è preferibile quando si vuole confrontare direttamente due soluzioni complete, come in problemi di scheduling con penalità (minimize lateness) o nella dimostrazione delle proprietà di taglio per i MST (cfr. [[03 - Minimum Spanning Tree]]).
## Interval Scheduling
### Definizione del problema
> [!quote] Definizione — Interval Scheduling
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** un sottoinsieme $S$ di intervalli mutualmente compatibili, ovvero tale che per ogni $I_i, I_j \in S$ i due intervalli non si sovrappongono ($f_i \leq s_j$ oppure $f_j \leq s_i$).
> **Misura (da massimizzare):** la cardinalità $|S|$, cioè il numero di intervalli schedulati.

Il problema è anche detto **job scheduling su una singola risorsa**: ogni intervallo è un "job" con inizio e fine, la risorsa (macchina, aula, processore) può gestire un solo job alla volta, e si vuole eseguire il massimo numero di job.

**Notazione.** $J$ è l'insieme dei job e $j \in J$ è il singolo job; $s(j)$ e $f(j)$ ne denotano inizio e fine. È la stessa **notazione funzionale** usata nelle dimostrazioni più sotto, e rende leggibile il confronto $f(j^*)$ — a pedici diventerebbe $f_{j^*}$, un pedice dentro un pedice. *(Le slide scrivono equivalentemente $s_j$ e $f_j$.)*

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Definizione formale di IS|definizione formale di IS — 21/01/2025, max 5 righe]]
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
> *Fewest conflicts*: serve una configurazione in cui il job con **meno conflitti** è proprio quello che spezza l'ottimo. Quattro job disgiunti in fila $B_1=[0,2]$, $B_2=[3,5]$, $B_3=[6,8]$, $B_4=[9,11]$; sopra di essi **tre** copie di $[1,4]$ (a cavallo di $B_1$ e $B_2$), **una sola** copia di $[4,7]$ (a cavallo di $B_2$ e $B_3$) e **tre** copie di $[7,10]$ (a cavallo di $B_3$ e $B_4$). Conteggio dei conflitti: $[4,7]$ ne ha **2** (solo $B_2$ e $B_3$), $B_1$ e $B_4$ ne hanno 3, tutti gli altri 4. Il greedy parte quindi da $[4,7]$, che elimina $B_2$ e $B_3$, e chiude con $\{[4,7], B_1, B_4\}$ → **3 job**; l'ottimo prende $B_1, B_2, B_3, B_4$ → **4 job**. *(Istanza numerica che realizza la figura della slide p. 5.)*

![[is_controesempi_ordini.png]]
Le tre configurazioni della slide p. 5, in grigio scuro il job che il criterio sbagliato sceglie per primo. In alto *earliest start time*: il job lungo in basso viene preso per primo e blocca i quattro corti. Al centro *shortest interval*: il job corto centrale è incompatibile con entrambi i lunghi, che fra loro sarebbero compatibili. In basso *fewest conflicts*: il job centrale ha solo 2 conflitti (contro i 3 dei due laterali scuri e i 4 di tutti gli altri), il greedy lo prende per primo e si preclude due dei quattro job della fila superiore.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Controesempio al criterio «intervallo più corto»|controesempio all'intervallo più corto — 22/06/2022, 19/02/2024, max 3 righe]]

> [!info] Regola — Earliest finish time contro earliest start time
> Ordinare per **tempo di inizio** lascia che un job lunghissimo (es. $[0,100]$) occupi la risorsa e blocchi tutti i job successivi, anche quando fra loro sarebbero compatibili. Ordinare per **tempo di fine** libera la risorsa il prima possibile, e massimizza le opportunità che restano: è la ragione strutturale per cui dei quattro criteri candidati funziona solo questo.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Ordine per tempo di inizio in Interval Scheduling|l'ordine per inizio non è ottimo — 20/07/2026, max 5 righe]]
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

> [!info] Implementazione — earliest-finish-time-first in $O(n \log n)$
> - L'ordinamento iniziale per tempo di fine richiede $O(n \log n)$ — cfr. [[04 - Algoritmi di Ordinamento]] (MergeSort o HeapSort).
> - Il ciclo esegue $n$ iterazioni, ognuna in $O(1)$: il controllo di compatibilità si riduce a confrontare $s(j)$ con $f(j^*)$ (il tempo di fine dell'ultimo job inserito), poiché $S$ contiene sempre intervalli compatibili e il nuovo job deve solo non sovrapporsi all'ultimo.
> - Totale: $O(n \log n)$.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Il criterio di ordinamento corretto|il criterio corretto — 21/01/2025, max 2 righe]]
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

![[is_lemma_greedy_stays_ahead.png]]
Lo schema della slide p. 27 per il passo induttivo: al passo $r$ il job $j_r$ dell'ottimo inizia dopo la fine di $j_{r-1}$ e quindi — per ipotesi induttiva — dopo la fine di $i_{r-1}$. È perciò **disponibile** anche al greedy (linea tratteggiata), che però sceglie il candidato con finish time minimo: da qui $f(i_r) \leq f(j_r)$.

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

![[is_teorema_assurdo.png]]
Lo schema della slide p. 28: se l'ottimo avesse $m > k$ job, il job $j_{k+1}$ (in blu) inizierebbe dopo $f(j_k) \geq f(i_k)$ e sarebbe quindi compatibile con **tutta** la soluzione greedy — che allora lo avrebbe selezionato invece di fermarsi a $k$ job. È la contraddizione che chiude la dimostrazione.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Schema della dimostrazione di ottimalità|schema della dimostrazione — 21/01/2025, max 10 righe]]
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Scansione e costruzione di $S$ | $O(n)$ |
| **Totale** | $O(n \log n)$ |

> [!info] Come si legge — Perché il test di compatibilità costa $O(1)$
> I job sono processati in ordine di finish time crescente, quindi $j^*$ (l'ultimo aggiunto a $S$) ha sempre il **finish time massimo** fra quelli in $S$. Se il nuovo job è compatibile con $j^*$ lo è automaticamente con tutti gli altri, che finiscono ancora prima: basta il confronto $s(j) \geq f(j^*)$, cioè $O(1)$ per job invece di $O(|S|)$. Il ciclo costa quindi $O(n)$, e il totale $O(n\log n)$ è dominato dall'ordinamento.
## Interval Partitioning
### Definizione del problema
> [!quote] Definizione — Interval Partitioning
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** una partizione degli intervalli in sottoinsiemi $C_1, \ldots, C_d$ (detti **classi** o **aule**) tali che ogni $C_i$ contiene solo intervalli mutualmente compatibili.
> **Misura (da minimizzare):** il numero di classi $d$.

Il problema modella l'assegnamento di lezioni universitarie alle aule: ogni lezione ha un orario fisso e non può essere spostata, si vuole minimizzare il numero di aule necessarie.

![[ip_istanza_4_aule.png]]
L'istanza di riferimento delle slide (10 lezioni $a$–$j$, dalle 9 alle 16:30) in una schedulazione **ammissibile ma non ottima**, che usa 4 aule: ogni aula contiene solo lezioni a due a due compatibili, quindi la soluzione è valida — semplicemente non è la migliore. Più avanti la stessa istanza viene servita con 3 aule, che è l'ottimo. Il problema non è trovare *una* schedulazione, ma quella con il numero minimo di aule.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Definizione formale di IP|definizione formale di IP — 18/02/2025, 30/06/2026, 09/09/2025]]
### Lower bound: la profondità
Tutto il problema ruota attorno a una domanda: in ogni istante, quante lezioni sono **in corso contemporaneamente**? Il massimo di questo conteggio — il **picco di sovrapposizioni** — è la *profondità*, e si rivelerà essere **esattamente** il numero di aule necessarie.

> [!quote] Definizione — Profondità
> La **profondità** (*depth*) di un insieme di intervalli **aperti** è il massimo numero di intervalli che contengono uno stesso punto dell'asse temporale (slide p. 49):
> $$\text{depth} = \max_{t} \bigl|\{I_i : s_i < t < f_i\}\bigr|$$
> Che gli intervalli si prendano **aperti** non è un dettaglio: è ciò che rende la definizione coerente con la compatibilità, perché due intervalli con $f_i = s_j$ si toccano in un punto ma non si sovrappongono, e in nessun istante contribuiscono entrambi al conteggio. La convenzione semiaperta $[s_i, f_i)$ dà lo stesso valore di depth.

> [!quote] Proprietà — Lower bound sulla profondità
> Qualunque soluzione ammissibile richiede almeno $\text{depth}$ classi: in ogni punto $t$ in cui si sovrappongono $\text{depth}$ intervalli, tali intervalli devono stare in classi distinte.

Questa proprietà fornisce un lower bound immediato e non dipende dall'algoritmo usato: vale per *ogni* soluzione possibile. L'intuizione è diretta: nell'istante di picco quelle $\text{depth}$ lezioni sono **tutte in corso insieme**, e due lezioni simultanee non possono condividere un'aula — quindi servono **almeno** $\text{depth}$ aule, qualunque strategia si adotti.

> [!warning] Profondità ≠ numero di conflitti
> Non confondere la profondità con il *numero di coppie di intervalli che si sovrappongono*: la profondità guarda **un singolo istante** e conta quanti intervalli sono attivi lì dentro — è un **picco di contemporaneità**, non un totale di conflitti. Esempio: i tre intervalli $[1,4]$, $[2,5]$, $[3,6]$ sono in corso **tutti insieme** nell'istante $t = 3.5$ → profondità $= 3$ → servono almeno $3$ aule.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#La depth e il suo ruolo|la depth e il suo ruolo — 18/02/2025, 28/09/2022]]
### Schemi greedy candidati e ordine corretto
Per Interval Partitioning il template greedy è: *considera le lezioni in un certo ordine; assegnala a una classe compatibile se esiste, altrimenti apri una nuova classe*. L'ordine corretto è **earliest start time** (ordine crescente di $s(j)$); gli altri tre ordini ammettono controesempi — la slide p. 34 ne mostra uno per *earliest finish time*, uno per *shortest interval* e uno per *fewest conflicts*, tutti con il greedy che apre 3 aule dove ne bastano 2. Quello per finish time è ricostruito numericamente nelle due domande d'esame qui sotto.

![[ip_controesempi_ordini.png]]
I tre controesempi della slide p. 34: in ciascuno il greedy con l'ordine sbagliato apre **3 aule** (le righe numerate 1, 2, 3) su un'istanza che ne richiede solo 2. In grigio scuro la lezione corta che, processata al momento sbagliato, occupa un'aula già "sprecata" e costringe ad aprirne una terza.

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Ordine per finish time in Interval Partitioning|controesempio all'ordine per finish time — 09/09/2025, 30/06/2026]]
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

> [!info] Implementazione — coda con priorità per le classi, $O(n \log n)$
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

![[ip_depth_3_aule.png]]
La schedulazione prodotta da earliest-start-time-first sulla stessa istanza della figura precedente: aula 1 = $a, e, h$; aula 2 = $b, g, i$; aula 3 = $c, d, f, j$. La banda rossa segna l'istante di picco (le 9:30), dove sono in corso insieme $a$, $b$ e $c$: $\text{depth} = 3$.

L'algoritmo alloca esattamente tante aule quanta è la profondità dell'istanza — qui 3 — ed è proprio l'uguaglianza $d = \text{depth}$ dimostrata più sotto: è questo a renderlo ottimo, non il fatto che su questa istanza sembri funzionare.
### Dimostrazione di ottimalità
> [!quote] Proprietà — Ammissibilità delle assegnazioni
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
5. Da (3) e (4): ognuna di quelle $d-1$ lezioni soddisfa $\text{inizio} \leq s(j) < \text{fine}$, cioè è **ancora in corso subito dopo $s(j)$**.
6. Aggiungendo anche $j$, nell'istante $s(j) + \epsilon$ coesistono **$d$ lezioni simultaneamente attive** (la slide p. 50 scrive esattamente «$d$ lectures overlapping at time $s_j + \epsilon$»: l'$\epsilon$ serve perché gli intervalli si contano aperti).
7. Per definizione di profondità, $\text{depth} \geq d$. $\square$

*Conclusione.* Da A e B segue $d = \text{depth}$: l'algoritmo usa esattamente il numero minimo di classi, quindi è **ottimale**. $\square$

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Ordine per tempo di inizio in Interval Partitioning|correttezza dell'ordine per inizio — 30/06/2026, max 10 righe]]
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per start time | $O(n \log n)$ |
| Ciclo con operazioni sulla coda con priorità | $O(n \log n)$ |
| **Totale** | $O(n \log n)$ |

→ **Palestra**: [[Esercizi 01 - Greedy e Interval Scheduling#Algoritmo e complessità, senza correttezza|algoritmo e complessità — 09/09/2025, max 5 righe]]
## Confronto riassuntivo
| Problema | Obiettivo | Ordine greedy | Struttura ausiliaria | Complessità |
|---|---|---|---|---|
| Interval Scheduling | max job compatibili | Earliest finish time | — (solo variabile $j^*$) | $O(n \log n)$ |
| Interval Partitioning | min classi (aule) | Earliest start time | Min-heap per finish time classi | $O(n \log n)$ |

> [!info] Regola — Perché i due problemi ordinano in modo diverso
> Gli obiettivi sono opposti, e l'ordine segue l'obiettivo. In **Interval Scheduling** la risorsa è una sola e si massimizzano i job accettati: conviene liberarla il prima possibile, quindi si guarda **chi finisce prima**. In **Interval Partitioning** le lezioni si servono tutte e si minimizzano le risorse: si processa **in ordine di inizio** e si conta quante devono coesistere, perché il picco di sovrapposizioni — la profondità — è il numero minimo di aule, e il greedy lo raggiunge esattamente.
## Checklist d'esame
Greedy allo scritto compare **sempre come Esercizio 2** (teoria pura), nella tripla *definizione formale → controesempio → dimostrazione di correttezza*; Interval Scheduling e Interval Partitioning sono i due problemi su cui viene chiesta. Questa sezione elenca ciò che va prodotto **a penna, senza guardare**, entro il limite di righe della traccia.

> [!info] Regola — cosa devi saper produrre a penna
> 1. **Definizioni** (max 5 righe, schema `Input` / `Soluzione ammissibile` / `Misura`): IS e IP, con la condizione di compatibilità scritta per esteso ($f_i \leq s_j$ oppure $f_j \leq s_i$) — è l'unico punto verificabile della definizione.
> 2. **Controesempi costruiti sul momento**: per IS i tre ordini sbagliati (earliest start, shortest interval, fewest conflicts); per IP l'ordine per finish time. Sempre con istanza numerica **e** confronto dei due esiti ("greedy 3 job vs ottimo 4").
> 3. **Dimostrazioni scritte per esteso**: per IS il lemma $f(i_r) \leq f(j_r)$ per induzione più il teorema per assurdo; per IP la doppia disuguaglianza $d \geq \text{depth}$ e $\text{depth} \geq d$.
> 4. **Pseudocodice + complessità**: EFT-first con il test di compatibilità $s(j) \geq f(j^*)$ in $O(1)$; EST-first con il min-heap delle classi (INSERT / FIND-MIN / INCREASE-KEY). Entrambi $O(n \log n)$, dominati dall'ordinamento.
> 5. **Depth**: definizione su intervalli aperti e il suo **doppio ruolo** — lower bound per ogni soluzione ammissibile *e* valore esattamente raggiunto dal greedy. È il collegamento che trasforma una definizione in un argomento di ottimalità, ed è quello che le tracce chiedono.
## Mappa nota ↔ slide
Riferimenti a `Materiale Didattico/Modulo II/Slide/01_Interval_scheduling_2025.pdf` (50 pagine), per studiare la slide tenendo la nota come riscontro.

| Sezione della nota | Slide |
|---|---|
| Il paradigma Greedy | p. 4 (greedy template) |
| Tecniche di dimostrazione dell'ottimalità | — *(extra: Kleinberg-Tardos §4.1)* |
| Interval Scheduling — definizione | pp. 2-3 (p. 3 = definizione formale) |
| Schemi greedy candidati e controesempi | pp. 4-5 |
| Algoritmo earliest-finish-time-first | p. 6; implementazione $O(n \log n)$ p. 26 |
| Esempio di esecuzione | pp. 7-25 (demo passo-passo) |
| Dimostrazione di ottimalità (IS) | p. 27 (lemma), p. 28 (teorema) |
| Interval Partitioning — definizione | pp. 30-32 (p. 32 = definizione formale) |
| Schemi greedy candidati e ordine corretto | pp. 33-34 (controesempi) |
| Algoritmo earliest-start-time-first | p. 35; implementazione $O(n \log n)$ p. 48 |
| Esempio di esecuzione | pp. 36-47, 49 |
| Lower bound: la profondità | p. 49 |
| Dimostrazione di ottimalità (IP) | p. 50 |
