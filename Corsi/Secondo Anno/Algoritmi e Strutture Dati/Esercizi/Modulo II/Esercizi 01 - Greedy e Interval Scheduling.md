---
tags:
  - algoritmi
  - greedy
  - esercizi
nota: "[[01 - Greedy e Interval Scheduling]]"
---
# Esercizi — Greedy e Interval Scheduling
Palestra della nota [[01 - Greedy e Interval Scheduling]]. Ogni item è una **domanda d'esame reale**, con la traccia di provenienza, la posizione nell'esercizio e il limite di righe verbatim. La risposta modello è in un callout **richiudibile**: si apre *dopo* aver scritto la propria, a penna, dentro il limite.
Nel campione il Greedy sta **sempre in Esercizio 2** (teoria pura), nella tripla *definizione formale → controesempio → dimostrazione di correttezza*.
## Interval Scheduling
### Definizione formale di IS
> [!question] Domanda d'esame — Definizione formale di IS
> **D:** «A. Si definisca formalmente IS. (Max 5 righe.)» *(traccia 21/01/2025 · Es. 2.1 · «Max 5 righe» · anche 20/07/2026 Es. 2.1, 19/02/2024 Es. 2.1)*

> [!info]- Risposta modello
> **Input.** Un insieme di $n$ intervalli $I_1, \ldots, I_n$, ciascuno con tempo di inizio $s_i$ e tempo di fine $f_i$.
>
> **Soluzione ammissibile.** Un sottoinsieme $S$ di intervalli a due a due compatibili, cioè tali che per ogni coppia $I_i, I_j \in S$ risulti $f_i \leq s_j$ oppure $f_j \leq s_i$ (non si sovrappongono).
>
> **Misura.** La cardinalità $|S|$ da **massimizzare**: il numero di job schedulabili sulla singola risorsa.
>
> ⏱️ **In 5 righe**: le tre componenti in una riga ciascuna, con la formula di compatibilità scritta per esteso — **non va mai omessa**, è l'unico punto realmente verificabile della definizione.
### Il criterio di ordinamento corretto
> [!question] Domanda d'esame — Il criterio di ordinamento corretto
> **D:** «B. Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto, ovvero l'algoritmo greedy che trova sempre una soluzione ottima del problema. (Max 2 righe.)» *(traccia 21/01/2025 · Es. 2.2 · «Max 2 righe» · anche 19/02/2024 Es. 2.3, 22/06/2022 Es. 2.1 «Max una riga»)*

> [!info]- Risposta modello
> **Criterio.** Ordine crescente di tempo di fine $f(j)$ — *earliest finish time*.
>
> **Perché proprio questo.** È l'unico dei quattro schemi candidati (start time, finish time, durata, numero di conflitti) che garantisce l'ottimalità; gli altri tre ammettono controesempi.
>
> ⏱️ **In 2 righe**: il criterio più la selezione greedy compatibile con l'ultimo scelto — **il nome del criterio non va mai omesso**, il confronto con gli altri tre schemi si taglia per primo.
### Schema della dimostrazione di ottimalità
> [!question] Domanda d'esame — Schema della dimostrazione di ottimalità di IS
> **D:** «C. Si dimostri a grandi linee perché l'algoritmo del punto (B) trova sempre una soluzione ottima del problema. (Max 10 righe.)» *(traccia 21/01/2025 · Es. 2.3 · «Max 10 righe» · anche 20/07/2026 Es. 2.3, 19/02/2024 Es. 2.4)*

> [!info]- Risposta modello
> **Impostazione.** Tecnica *greedy stays ahead*: si confrontano i job scelti dal greedy $i_1, \ldots, i_k$ con quelli di una soluzione ottima $j_1, \ldots, j_m$, entrambi ordinati per tempo di fine.
>
> **Lemma (per induzione su $r$).** Per ogni $r$ vale $f(i_r) \leq f(j_r)$. Caso base: il greedy prende subito il job con finish time minimo in assoluto, quindi non può essere battuto da nessun $j_1$. Passo induttivo: la compatibilità di $j_r$ con $j_{r-1}$ dà $s(j_r) \geq f(j_{r-1})$, che con l'ipotesi induttiva $f(i_{r-1}) \leq f(j_{r-1})$ implica $s(j_r) \geq f(i_{r-1})$ — $j_r$ era quindi un candidato disponibile anche per il greedy al passo $r$, che sceglie sempre il candidato con finish time minimo.
>
> **Teorema (per assurdo).** Se fosse $m > k$, il job aggiuntivo $j_{k+1}$ dell'ottimo risulterebbe compatibile con tutta la soluzione greedy $i_1, \ldots, i_k$ (per il lemma con $r = k$), e il greedy lo avrebbe quindi incluso proseguendo la scansione — contraddizione.
>
> **Conclusione.** Perciò $m = k$: il greedy è ottimo.
>
> ⏱️ **In 10 righe**: c'è spazio per il lemma completo con entrambi i passi (4-5 righe) e il teorema per assurdo con la contraddizione esplicita (3-4 righe) — **la disuguaglianza $f(i_r) \leq f(j_r)$ e il passaggio all'assurdo restano gli unici due elementi mai omissibili**.
### Controesempio al criterio «intervallo più corto»
> [!question] Domanda d'esame — Controesempio al criterio dell'intervallo più corto
> **D:** «Si mostri che il criterio greedy secondo cui i migliori job sono quelli che durano di meno (ovvero che minimizzano $f_i - s_i$) in generale non consente di trovare una soluzione ottima. (Max 3 righe.)» *(traccia 22/06/2022 · Es. 2.2 · «Max 3 righe» · anche 19/02/2024 Es. 2.2)*

> [!info]- Risposta modello
> **Istanza.** Tre job: $[0,3]$, $[2,4]$, $[3,6]$.
>
> **Comportamento del greedy.** Il più corto è $[2,4]$ (durata 2): viene preso per primo e si sovrappone sia a $[0,3]$ sia a $[3,6]$, che restano esclusi → **1 job**.
>
> **Ottimo.** $[0,3]$ e $[3,6]$ sono compatibili fra loro ($f = 3 \leq s = 3$) → **2 job**. Il criterio non è ottimo.
>
> ⏱️ **In 3 righe**: i tre intervalli numerici (1 riga), cosa sceglie il greedy e cosa esclude (1 riga), il confronto 1 contro 2 (1 riga) — **il confronto numerico fra i due esiti non va mai omesso**: senza quello non è un controesempio, è un'osservazione.
### La proprietà chiave che dimostra l'ottimalità
> [!question] Domanda d'esame — La proprietà chiave dell'ottimalità di IS
> **D:** «Si enunci in modo formale e preciso la proprietà chiave che permette di dimostrare che A è un algoritmo ottimo per Interval Scheduling. (Max 5 righe.)» *(traccia 22/06/2022 · Es. 2.3 · «Max 5 righe»)*

> [!info]- Risposta modello
> **La proprietà** è il *greedy stays ahead*. Siano $i_1, \ldots, i_k$ i job selezionati dall'algoritmo e $j_1, \ldots, j_m$ quelli di una soluzione ottima qualunque, entrambi ordinati per tempo di fine. Allora
> $$f(i_r) \leq f(j_r) \quad \text{per ogni } r = 1, \ldots, k$$
> cioè l'$r$-esimo job scelto dal greedy finisce **non più tardi** dell'$r$-esimo job dell'ottimo.
>
> **Perché è la proprietà chiave.** Applicata all'ultimo passo, impedisce che l'ottimo abbia un job in più: se fosse $m > k$, il job $j_{k+1}$ inizierebbe dopo $f(j_k) \geq f(i_k)$ e sarebbe compatibile con tutta la soluzione greedy, che quindi lo avrebbe preso.
>
> ⏱️ **In 5 righe**: l'enunciato con la disuguaglianza $f(i_r) \leq f(j_r)$ e la definizione delle due sequenze (2-3 righe), poi in una riga perché chiude la dimostrazione — **la disuguaglianza scritta in formula non va mai omessa**: è quella «la proprietà», il resto è contorno.
### Ordine per tempo di inizio in Interval Scheduling
> [!question] Domanda d'esame — Ordine per tempo di inizio in Interval Scheduling
> **D:** «Si mostri che l'algoritmo greedy che ordina gli intervalli per tempo di inizio non trova sempre la soluzione ottima. (Max 5 righe.)» *(traccia 20/07/2026 · Es. 2.2 · «Max 5 righe»)*

> [!info]- Risposta modello
> **Istanza.** Tre job: $A=[0,10]$, $B=[1,3]$, $C=[4,6]$.
>
> **Cosa fa il greedy per tempo di inizio.** Ordine $A\,(s=0)$, $B\,(s=1)$, $C\,(s=4)$: prende $A$; poi $B$ e $C$ sono entrambi incompatibili con $A$, che occupa la risorsa fino a $10$ → **1 job**.
>
> **Ottimo.** $B$ e $C$ sono compatibili fra loro ($f_B = 3 \leq s_C = 4$) → **2 job**.
>
> **Conclusione.** Il criterio per tempo di inizio restituisce 1 job dove l'ottimo ne prende 2: non è ottimo. La causa strutturale è che un job che inizia prestissimo può durare arbitrariamente a lungo e bloccare la risorsa.
>
> ⏱️ **In 5 righe**: l'istanza numerica (1 riga), cosa prende il greedy e perché esclude gli altri (1-2 righe), cosa prende l'ottimo con il conteggio 1 contro 2 (1-2 righe) — **il confronto numerico fra i due esiti non va mai omesso**: la traccia dice «si mostri», quindi vuole un'istanza esibita, non una spiegazione.
## Interval Partitioning
### Definizione formale di IP
> [!question] Domanda d'esame — Definizione formale di IP
> **D:** «1. Si definisca formalmente il problema di IP. (Max 5 righe.)» *(traccia 18/02/2025 · Es. 2.1 · «Max 5 righe» · anche 28/09/2022 Es. 2.1, 09/09/2025 Es. 2.1, 30/06/2026 Es. 2.1)*

> [!info]- Risposta modello
> **Input.** Un insieme di $n$ intervalli $I_1, \ldots, I_n$, con $I_i = [s_i, f_i)$.
>
> **Soluzione ammissibile.** Una partizione degli intervalli in classi $C_1, \ldots, C_d$ tali che ogni classe contenga solo intervalli a due a due compatibili — equivalentemente, un'assegnazione di etichette in cui due intervalli sovrapposti ricevono etichette **diverse**.
>
> **Misura.** Il numero di classi $d$, da **minimizzare**; nell'interpretazione delle aule universitarie, il numero minimo di aule per ospitare tutte le lezioni senza conflitti.
>
> ⏱️ **In 5 righe**: le tre componenti in una riga ciascuna; se resta spazio aggiungi l'interpretazione delle aule, ma **la condizione «sovrapposti → classi diverse» non va mai omessa**, è l'unico vincolo che rende la definizione verificabile.
### La depth e il suo ruolo
> [!question] Domanda d'esame — La depth e il suo ruolo nell'analisi
> **D:** «2. Si definisca il concetto di depth di un'istanza di IP e si discuta perché è importante per analizzare l'algoritmo greedy che risolve IP. (Max 5 righe.)» *(traccia 18/02/2025 · Es. 2.2 · «Max 5 righe» · anche 28/09/2022 Es. 2.2)*

> [!info]- Risposta modello
> **Definizione.** La depth è il **massimo numero di intervalli che si sovrappongono in uno stesso istante** — un picco di contemporaneità, non un conteggio dei conflitti totali. *(Extra, non da slide: equivale alla dimensione della clique massima nel grafo di intersezione degli intervalli.)*
>
> **Ruolo come lower bound.** È un limite inferiore al numero di risorse per **qualunque** soluzione ammissibile: nell'istante di picco quegli intervalli devono stare in classi distinte, quindi $d \geq \text{depth}$.
>
> **Perché rende l'algoritmo ottimo.** L'algoritmo earliest-start-time-first alloca **esattamente** $\text{depth}$ classi: quando apre la $d$-esima esibisce $d$ intervalli attivi insieme in $s(j)+\epsilon$, quindi $\text{depth} \geq d$. Combinando, $d = \text{depth}$ è il minimo possibile.
>
> ⏱️ **In 5 righe**: definizione, lower bound e chiusura «il greedy usa esattamente depth classi → ottimo», una riga ciascuna — **il collegamento fra lower bound e uguaglianza raggiunta dal greedy non va mai omesso**: è quello che trasforma la depth da definizione in argomento di ottimalità.
### Ordine per finish time in Interval Partitioning
> [!question] Domanda d'esame — Ordine per finish time in Interval Partitioning
> **D:** «2. Si motivi perché un algoritmo greedy che ordina gli intervalli per finish time non trova la soluzione ottima. (Max 5 righe.)» *(traccia 09/09/2025 · Es. 2.2 · «Max 5 righe» · anche 30/06/2026 Es. 2.2)*

> [!info]- Risposta modello
> **Istanza e ottimo.** $A=[0,4]$, $B=[1,2]$, $C=[3,7]$, $D=[5,6]$. La profondità è $2$ (nessun istante ha 3 intervalli sovrapposti), quindi bastano 2 aule.
>
> **Comportamento del greedy per finish time.** Ordine $B(f=2), A(f=4), D(f=6), C(f=7)$: $B$ apre la classe 1; $A$ è incompatibile con la classe 1 ($0<2$) e apre la classe 2; $D$ è compatibile con la classe 1 ($5\geq2$) e vi entra (la classe 1 finisce ora a $6$); $C$ inizia a $3$ ed è incompatibile sia con la classe 1 (finisce a $6$) sia con la classe 2 (finisce a $4$): apre una **terza** classe.
>
> **Causa.** Ordinare per tempo di fine non tiene conto di *quando* un intervallo diventa disponibile (il suo start), solo di quando finisce.
>
> **Conclusione.** 3 classi contro le 2 ottime: il criterio non è corretto per IP.
>
> ⏱️ **In 5 righe**: istanza numerica con la profondità (1 riga), conteggio delle classi aperte senza il dettaglio passo-passo (1-2 righe), causa e conclusione (1 riga) — **l'istanza concreta e il conteggio 3 vs 2 non vanno mai omessi**, il passo-passo si taglia per primo.
### Ordine per tempo di inizio in Interval Partitioning
> [!question] Domanda d'esame — Ordine per tempo di inizio in Interval Partitioning
> **D:** «3. Si argomenti sulla correttezza dell'algoritmo greedy che ordina gli intervalli per tempo di inizio. (Max 10 righe.)» *(traccia 30/06/2026 · Es. 2.3 · «Max 10 righe»)*

> [!info]- Risposta modello
> **Impostazione.** Si mostra che il numero di classi $d$ allocate da earliest-start-time-first coincide con la profondità, tramite due disuguaglianze.
>
> **Caso 1 — $d \geq \text{depth}$.** Ogni soluzione ammissibile richiede almeno $\text{depth}$ classi (intervalli sovrapposti devono stare in classi diverse); la soluzione del greedy è ammissibile, quindi $d \geq \text{depth}$.
>
> **Caso 2 — $\text{depth} \geq d$.** Quando il greedy apre la $d$-esima classe per una lezione $j$, è perché $j$ è incompatibile con l'ultima lezione di ciascuna delle $d-1$ classi già aperte. Processando in ordine di inizio crescente, quelle $d-1$ lezioni hanno inizio $\leq s(j)$ e finiscono dopo $s(j)$: sono tutte ancora in corso in $s(j)+\epsilon$ insieme a $j$, quindi $\text{depth} \geq d$.
>
> **Conclusione.** Le due disuguaglianze danno $d = \text{depth}$, il minimo possibile: l'algoritmo è ottimo.
>
> ⏱️ **In 10 righe**: entrambi i casi con giustificazione completa (3-4 righe ciascuno) più impostazione e conclusione — **le due disuguaglianze non vanno mai omesse**, sono l'intera struttura; il primo dettaglio da tagliare è il perché quelle $d-1$ lezioni sono ancora attive.
### Algoritmo e complessità, senza correttezza
> [!question] Domanda d'esame — Algoritmo e complessità di IP, senza correttezza
> **D:** «3. Si descriva invece l'algoritmo greedy ottimo per il problema discutendone la complessità computazionale (non si discuta la correttezza). (Max 5 righe.)» *(traccia 09/09/2025 · Es. 2.3 · «Max 5 righe»)*

> [!info]- Risposta modello
> **Idea.** Earliest-start-time-first: ordina gli intervalli per tempo di inizio crescente e li scandisce una volta sola.
>
> **Procedura.** Per ciascuna lezione cerca, tramite un **min-heap** di classi con chiave = finish time dell'ultima lezione assegnata, la classe con finish time minimo; se è compatibile ($f_{\min} \leq s(j)$) vi assegna $j$ e aggiorna la chiave (INCREASE-KEY), altrimenti apre una nuova classe (INSERT).
>
> **Perché basta il min-heap.** L'unica classe che può accogliere $j$ è quella che si libera prima: se non basta lei, non ne basta nessuna.
>
> **Complessità.** Ordinamento $O(n \log n)$ più $n$ operazioni sull'heap da $O(\log n)$ ciascuna: **$O(n \log n)$** complessivo.
>
> ⏱️ **In 5 righe**: idea (1 riga), procedura con ordinamento e min-heap (2-3 righe), complessità (1 riga) — **il totale $O(n \log n)$ con la sua giustificazione non va mai omesso**, è quello che la traccia chiede esplicitamente.
## Come usare questa pagina
Gli item qui sopra sono ordinati **per problema** (prima IS, poi IP), mentre l'allenamento va fatto **per formato**: cercali per tipo, non in sequenza. Ordine consigliato, coerente con la tripla in cui il Greedy viene chiesto: prima le due **definizioni formali** (IS e IP) dentro le 5 righe, poi i **controesempi** costruiti da zero, infine le due **dimostrazioni** a penna. Un item è chiuso quando la risposta esce **senza aprire il callout**.
