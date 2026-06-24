# Greedy e Interval Scheduling
Il paradigma **greedy** (goloso) affronta problemi di ottimizzazione costruendo la soluzione passo dopo passo: ad ogni passo si compie la scelta *localmente* ottima — senza ritornare indietro — sperando (e dimostrando!) che la sequenza di scelte locali produca la soluzione *globalmente* ottima. Non tutti i problemi ammettono algoritmi greedy corretti: la difficoltà sta nel dimostrare l'ottimalità, tipicamente tramite *greedy stays ahead* o un argomento di scambio (*exchange argument*). Questa nota introduce il paradigma e lo applica ai problemi di Interval Scheduling e Interval Partitioning. Per gli algoritmi di ordinamento richiamati nell'analisi della complessità vedere [[04 - Algoritmi di Ordinamento]]; per la struttura dati coda con priorità usata in Interval Partitioning vedere [[07 - Code con Priorità e Heap]].
## Il paradigma Greedy
Un algoritmo greedy costruisce incrementalmente una soluzione: a ogni passo estende la soluzione parziale corrente con l'elemento che sembra migliore *al momento*, senza mai riesaminare le scelte precedenti. Il pregio è la semplicità e l'efficienza; il rischio è che le scelte locali non portino all'ottimo globale.
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
### Schemi greedy candidati e controesempi
Uno schema naturale è: *considera i job in un certo ordine, aggiungili a $S$ se compatibili con quelli già scelti*. Quali ordini funzionano?

| Ordine | Idea | Ottimo? |
|---|---|---|
| Earliest start time | ordine crescente di $s_j$ | No — un job lunghissimo blocca tutto |
| Earliest finish time | ordine crescente di $f_j$ | **Sì** (dimostrato sotto) |
| Shortest interval | ordine crescente di $f_j - s_j$ | No — un intervallo corto al centro può escludere due più lunghi non sovrapposti |
| Fewest conflicts | ordine crescente del numero di conflitti $c_j$ | No — controesempio costruibile facilmente |

> [!warning] Controesempi per gli ordini errati
> *Earliest start time*: un unico job $[0, 100]$ blocca tutti i job $[1,2], [3,4], \ldots$ che partono dopo ma sono compatibili tra loro.
> *Shortest interval*: un job corto $[2, 4]$ al centro esclude $[0, 3]$ e $[4, 7]$; la soluzione ottima sceglie questi ultimi due.
> *Fewest conflicts*: con la configurazione giusta un job con pochi conflitti "buca" il centro impedendo due job laterali compatibili, ciascuno con un conflitto in più.
### Algoritmo earliest-finish-time-first
L'unico ordine che garantisce l'ottimalità è **earliest finish time**: si processa ogni job in ordine crescente di tempo di fine e lo si aggiunge alla soluzione se compatibile con l'ultimo job selezionato.

**Earliest-Finish-Time-First($n$, $s_1, \ldots, s_n$, $f_1, \ldots, f_n$)**

```text
1. ORDINA i job per tempo di fine: f[1] <= f[2] <= ... <= f[n]
2. S <- insieme vuoto
3. j* <- nessuno          // ultimo job aggiunto a S
4. FOR j = 1 TO n DO
5.     IF (j* = nessuno) OR (s[j] >= f[j*]) THEN
6.         S <- S ∪ {j}
7.         j* <- j
8. RETURN S
```

> [!info] Implementazione in $O(n \log n)$
> - L'ordinamento per tempo di fine (riga 1) richiede $O(n \log n)$ — cfr. [[04 - Algoritmi di Ordinamento]] (MergeSort o HeapSort).
> - Il ciclo (righe 4–7) esegue $n$ iterazioni, ognuna in $O(1)$: il controllo di compatibilità si riduce a confrontare $s_j$ con $f_{j^*}$ (il tempo di fine dell'ultimo job inserito), poiché $S$ contiene sempre intervalli compatibili e il nuovo job deve solo non sovrapporsi all'ultimo.
> - Totale: $O(n \log n)$.
### Esempio di esecuzione
Si considerino 8 job (A–H) con i seguenti intervalli (tempo ordinato per finish time: B, C, A, E, D, F, G, H):

```
  B |-----|          (finisce prima)
  C    |-------|
  A   |------|
  E          |------|
  D          |---------|
  F               |---------|
  G                   |---------|
  H                       |------|
  0   1   2   3   4   5   6   7   8   9   10  11
```

Esecuzione dell'algoritmo:
1. Job B: $S = \emptyset$ → compatibile → $S = \{B\}$, $j^* = B$
2. Job C: $s_C < f_B$ → incompatibile → scarta
3. Job A: $s_A < f_B$ → incompatibile → scarta
4. Job E: $s_E \geq f_B$ → compatibile → $S = \{B, E\}$, $j^* = E$
5. Job D: $s_D < f_E$ → incompatibile → scarta
6. Job F: $s_F < f_E$ → incompatibile → scarta
7. Job G: $s_G < f_E$ → incompatibile → scarta
8. Job H: $s_H \geq f_E$ → compatibile → $S = \{B, E, H\}$, $j^* = H$

Soluzione: $\{B, E, H\}$ con $|S| = 3$ — ottima.
### Dimostrazione di ottimalità
La dimostrazione usa la tecnica *greedy stays ahead* e procede in due passi: un lemma per induzione, poi il teorema per assurdo.

Siano $i_1, i_2, \ldots, i_k$ i job selezionati dall'algoritmo greedy (ordinati per finish time), e siano $j_1, j_2, \ldots, j_m$ i job di una soluzione ottima (ordinati per finish time). Denotiamo con $f(i_r)$ il tempo di fine del job $i_r$.
> [!quote] Lemma — Greedy stays ahead per Interval Scheduling
> Per ogni $r = 1, 2, \ldots, k$ vale:
> $$f(i_r) \leq f(j_r)$$
> Ovvero: il $r$-esimo job scelto dal greedy finisce *non più tardi* del $r$-esimo job scelto dall'ottimo.

**Dimostrazione (per induzione su $r$).**
- *Caso base $r = 1$:* il greedy sceglie il job con il minimo tempo di fine tra tutti; $j_1$ è uno qualsiasi, quindi $f(i_1) \leq f(j_1)$. $\square$
- *Passo induttivo $r > 1$:* per ipotesi $f(i_{r-1}) \leq f(j_{r-1})$. Il job $j_r$ è compatibile con $j_1, \ldots, j_{r-1}$ nell'ottimo, quindi $s(j_r) \geq f(j_{r-1})$. Per l'ipotesi induttiva $f(j_{r-1}) \geq f(i_{r-1})$, dunque $s(j_r) \geq f(i_{r-1})$: il job $j_r$ è compatibile anche con i job $i_1, \ldots, i_{r-1}$ scelti dal greedy. Quando il greedy sceglie il suo $r$-esimo job tra tutti i candidati compatibili (il job con finish time minimo), $j_r$ è nella rosa dei candidati; perciò $f(i_r) \leq f(j_r)$. $\square$

```
Greedy:  i1        i2        i(r-1)     ir
         |--|      |---|     |-----|    |---|

Ottimo:   j1         j2         j(r-1)       jr
          |---|      |----|      |------|     |-----|
          ^-- f(ir) <= f(jr) per induzione --^
```
> [!quote] Teorema — Ottimalità di earliest-finish-time-first
> L'algoritmo earliest-finish-time-first è ottimale: produce un insieme di job compatibili di cardinalità massima.

**Dimostrazione (per assurdo).** Supponiamo che il greedy non sia ottimo, ovvero $m > k$ (l'ottimo seleziona più job del greedy). Applicando il lemma con $r = k$: $f(i_k) \leq f(j_k)$. Poiché $m > k$, l'ottimo include un job $j_{k+1}$ che inizia dopo $f(j_k) \geq f(i_k)$. Quindi $j_{k+1}$ è compatibile con tutti i job $i_1, \ldots, i_k$ del greedy. Ma allora, quando il greedy ha selezionato $i_k$, avrebbe dovuto continuare a processare job — in particolare avrebbe trovato $j_{k+1}$ (o un job con finish time ancora prima) e lo avrebbe aggiunto a $S$: contraddizione con il fatto che $k$ è la dimensione finale della soluzione greedy. $\square$

```
Greedy:  i1   i2   i3   ...    ik
         |--|  |--| |--|        |---|

Ottimo:  j1   j2   j3   ...    jk        jk+1
         |--|  |--| |--|        |---|     |---|
                                           ^-- compatibile con ik => greedy lo avrebbe preso! Contraddizione
```
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per finish time | $O(n \log n)$ |
| Scansione e costruzione di $S$ | $O(n)$ |
| **Totale** | $O(n \log n)$ |
## Interval Partitioning
### Definizione del problema
> [!quote] Definizione — Interval Partitioning
> **Input:** un insieme di $n$ intervalli $I_1, \ldots, I_n$; l'intervallo $I_i$ ha tempo di inizio $s_i$ e tempo di fine $f_i$.
> **Soluzione ammissibile:** una partizione degli intervalli in sottoinsiemi $C_1, \ldots, C_d$ (detti **classi** o **aule**) tali che ogni $C_i$ contiene solo intervalli mutualmente compatibili.
> **Misura (da minimizzare):** il numero di classi $d$.

Il problema modella l'assegnamento di lezioni universitarie alle aule: ogni lezione ha un orario fisso e non può essere spostata, si vuole minimizzare il numero di aule necessarie.
### Lower bound: la profondità
> [!quote] Definizione — Profondità
> La **profondità** di un insieme di intervalli (considerati come intervalli **aperti**) è il massimo numero di intervalli che contengono contemporaneamente un dato punto dell'asse temporale:
> $$\text{depth} = \max_{t} \bigl|\{I_i : s_i \leq t < f_i\}\bigr|$$
> La convenzione di intervallo aperto a destra è coerente con la definizione di compatibilità: due intervalli con $f_i = s_j$ sono compatibili (non si sovrappongono).

> [!quote] Proprietà — Lower bound sulla profondità
> Qualunque soluzione ammissibile richiede almeno $\text{depth}$ classi: in ogni punto $t$ in cui si sovrappongono $\text{depth}$ intervalli, tali intervalli devono stare in classi distinte.

Questa proprietà fornisce un lower bound immediato e non dipende dall'algoritmo usato: vale per *ogni* soluzione possibile.
### Schemi greedy candidati e ordine corretto
Per Interval Partitioning il template greedy è: *considera le lezioni in un certo ordine; assegnala a una classe compatibile se esiste, altrimenti apri una nuova classe*. L'ordine corretto è **earliest start time** (ordine crescente di $s_j$); gli altri ordini ammettono controesempi analoghi a quelli visti per Interval Scheduling.
### Algoritmo earliest-start-time-first
**Earliest-Start-Time-First($n$, $s_1, \ldots, s_n$, $f_1, \ldots, f_n$)**

```text
1. ORDINA le lezioni per tempo di inizio: s[1] <= s[2] <= ... <= s[n]
2. d <- 0                  // numero di classi allocate
3. FOR j = 1 TO n DO
4.     IF (esiste una classe k compatibile con la lezione j) THEN
5.         Schedula la lezione j nella classe k
6.     ELSE
7.         d <- d + 1
8.         Schedula la lezione j nella nuova classe d
9. RETURN schedule
```

> [!info] Implementazione efficiente con coda con priorità — $O(n \log n)$
> La chiave per l'efficienza è scegliere opportunamente "quale" classe compatibile usare quando ce ne sono più di una. Si usa una **[[07 - Code con Priorità e Heap|coda con priorità (min-heap)]]** con chiave = tempo di fine dell'ultima lezione nella classe:
> - **INSERT** per aprire una nuova classe.
> - **FIND-MIN** per trovare la classe con il tempo di fine più precoce: se $f_{\min} \leq s_j$ la lezione $j$ è compatibile e viene assegnata a quella classe.
> - **INCREASE-KEY** (o equivalente) per aggiornare il tempo di fine della classe appena usata a $f_j$.
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

**Dimostrazione.** Sia $d$ il numero di classi allocate dall'algoritmo. Poiché l'algoritmo non assegna mai due lezioni incompatibili alla stessa classe (Osservazione), $d$ è una soluzione ammissibile. Dobbiamo mostrare che $d = \text{depth}$.
- ($d \geq \text{depth}$) Dalla proprietà di lower bound, qualunque soluzione ammissibile — inclusa quella dell'algoritmo — richiede almeno $\text{depth}$ classi.
- ($d \leq \text{depth}$, ovvero $\text{depth} \geq d$) La classe $d$ è stata aperta perché la lezione $j$ (quella che ha forzato l'apertura) era incompatibile con la lezione finale di ognuna delle $d-1$ classi già aperte. "Incompatibile" significa che la fine di quella lezione è $> s_j$ (la lezione è ancora in corso quando $j$ inizia). Poiché le lezioni sono state processate in ordine di start time, ogni lezione nelle $d-1$ classi ha $s \leq s_j$. Dunque le $d-1$ lezioni finali (una per classe) più la lezione $j$ si sovrappongono tutte al tempo $s_j$: in quel punto coesistono $d$ lezioni, quindi $\text{depth} \geq d$.

Combinando i due versi: $d = \text{depth}$, e l'algoritmo è ottimale. $\square$
### Complessità
| Fase | Costo |
|---|---|
| Ordinamento per start time | $O(n \log n)$ |
| Ciclo con operazioni sulla coda con priorità | $O(n \log n)$ |
| **Totale** | $O(n \log n)$ |
## Confronto riassuntivo
| Problema | Obiettivo | Ordine greedy | Struttura ausiliaria | Complessità |
|---|---|---|---|---|
| Interval Scheduling | max job compatibili | Earliest finish time | — (solo variabile $j^*$) | $O(n \log n)$ |
| Interval Partitioning | min classi (aule) | Earliest start time | Min-heap per finish time classi | $O(n \log n)$ |
## Domande tipiche d'esame
> [!example] Domanda tipica d'esame — Interval Scheduling
> **D:** Perché l'ordine "earliest start time" non funziona per Interval Scheduling, mentre "earliest finish time" sì?
> **R:** Con earliest start time si potrebbe scegliere come primo un job con inizio precocissimo ma durata arbitrariamente lunga, bloccando tutti i job successivi anche se fossero mutualmente compatibili tra loro. L'ordine per finish time è corretto perché minimizza il "danno" lasciato da ogni job scelto: scegliere il job che finisce prima libera la risorsa il prima possibile, massimizzando le opportunità per i job futuri. La correttezza si dimostra formalmente con il lemma *greedy stays ahead*: il $r$-esimo job del greedy finisce sempre prima o al pari del $r$-esimo job di qualsiasi soluzione ottima, e per assurdo si conclude che il greedy non può selezionare meno job dell'ottimo.

> [!example] Domanda tipica d'esame — Lower bound e ottimalità in Interval Partitioning
> **D:** Cos'è la profondità di un insieme di intervalli e che ruolo ha nella dimostrazione di ottimalità dell'algoritmo di Interval Partitioning?
> **R:** La profondità è il massimo numero di intervalli che contengono contemporaneamente uno stesso punto. Poiché tutti gli intervalli che si sovrappongono in un punto devono stare in classi distinte, ogni soluzione ammissibile richiede almeno $\text{depth}$ classi: la profondità è un **lower bound** sull'ottimo. L'algoritmo earliest-start-time-first alloca esattamente $\text{depth}$ classi: quando apre la $d$-esima classe, si dimostra che esistono $d$ intervalli sovrapposti nello stesso istante, quindi $d \leq \text{depth}$. Combinando i due verso si conclude $d = \text{depth}$, ovvero l'algoritmo è ottimo.

> [!example] Domanda tipica d'esame — Complessità e implementazione
> **D:** Come si implementa l'algoritmo di Interval Partitioning in $O(n \log n)$ e perché basta un min-heap?
> **R:** Dopo aver ordinato le lezioni per start time in $O(n \log n)$, si mantiene un min-heap in cui ogni elemento è una classe con chiave = tempo di fine della sua ultima lezione. Per ogni lezione $j$: si confronta $s_j$ con il minimo del heap (FIND-MIN in $O(1)$ o $O(\log n)$ a seconda dell'heap). Se la classe con finish time minimo è compatibile ($f_{\min} \leq s_j$), si assegna $j$ a quella classe e si aggiorna la chiave (INCREASE-KEY / DELETE+INSERT in $O(\log n)$); altrimenti si apre una nuova classe (INSERT in $O(\log n)$). In totale $O(n)$ operazioni da $O(\log n)$ ciascuna: $O(n \log n)$.
