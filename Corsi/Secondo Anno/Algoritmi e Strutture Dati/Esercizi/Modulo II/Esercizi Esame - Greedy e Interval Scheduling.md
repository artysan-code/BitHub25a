---
tags:
  - algoritmi
  - greedy
  - esercizi
---
# Esercizi d'esame — Greedy e Interval Scheduling
Tutti gli item su **Greedy e Interval Scheduling** realmente usciti nei **12 compiti** di Modulo II dal giugno 2024 al giugno 2026, con la risposta modello. **Nessun esercizio è inventato**: ogni testo è verbatim dal compito, con appello, esercizio e punto.
> [!info] Cosa dicono i numeri per questo argomento
> **11 item** su 4 appelli diversi (su 12 analizzati). Slot: Es. 2 ×11.
> Cosa ti chiede di produrre: definisci ×5, discuti-correttezza ×3, altro ×1, calcola-complessita ×1, costruisci-esempio ×1.
> Richieste esplicite di **dimostrazione**: **0**.
> Come usarlo: copri la riga «**Risposta.**», rispondi ad alta voce, scopri. Sui vero/falso motiva **sempre in una riga** — il «vero/falso» secco non prende punti pieni.
### 1. Definizione formale di Interval Scheduling
*(21/01/2025 · Es. 2 · punto A · definisci)*
> Si definisca formalmente IS. (Max 5 righe.)

**Risposta.** Input: un insieme di $n$ richieste $\{1,\dots,n\}$, ciascuna con tempo di inizio $s_i$ e tempo di fine $f_i$ ($s_i<f_i$). Due richieste $i,j$ sono **compatibili** se i loro intervalli $[s_i,f_i)$ e $[s_j,f_j)$ non si sovrappongono, cioè $f_i\le s_j$ oppure $f_j\le s_i$. Obiettivo: trovare il sottoinsieme di richieste a due a due compatibili di **cardinalità massima**.
### 2. Criterio di ordinamento del greedy corretto per IS
*(21/01/2025 · Es. 2 · punto B · definisci)*
> Si definisca il criterio di ordinamento degli intervalli che porta all'algoritmo greedy corretto. (Max 2 righe.)

**Risposta.** Si ordinano gli intervalli per **tempo di fine $f_i$ crescente** (earliest finish time first) e si seleziona greedily ogni intervallo compatibile con quelli già scelti.
### 3. Correttezza del greedy earliest-finish-time per IS
*(21/01/2025 · Es. 2 · punto C · discuti-correttezza)*
> Si dimostri a grandi linee perché l'algoritmo del punto (B) trova sempre una soluzione ottima. (Max 10 righe.)

**Risposta.** Argomento "greedy stays ahead": sia $g_1,\dots,g_k$ la soluzione greedy (in ordine di scelta) e $o_1,\dots,o_m$ una soluzione ottima, entrambe ordinate per tempo di fine. Si dimostra per induzione che $f(g_i)\le f(o_i)$ per ogni $i\le k$: base vera perché greedy sceglie il finish time minimo assoluto; passo induttivo, se $f(g_{i-1})\le f(o_{i-1})$ allora $o_i$ è compatibile con $g_{i-1}$ (perché lo è con $o_{i-1}$ che finisce dopo o insieme a $g_{i-1}$), quindi $o_i$ era un candidato disponibile per greedy al passo $i$, e greedy sceglie quello con finish time minimo, dunque $f(g_i)\le f(o_i)$. Se per assurdo $m>k$: poiché $f(g_k)\le f(o_k)\le s(o_{k+1})$, l'intervallo $o_{k+1}$ sarebbe compatibile con $g_1,\dots,g_k$ e greedy non si sarebbe fermato dopo $k$ scelte — contraddizione. Quindi $k=m$ e la soluzione greedy è ottima.
### 4. Definizione formale di Interval Partitioning
*(18/02/2025 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema di IP. (Max 5 righe.)

**Risposta.** Input: un insieme di $n$ richieste $\{1,\dots,n\}$, ciascuna con tempo di inizio $s_i$ e tempo di fine $f_i$. Obiettivo: partizionare le richieste nel **minor numero possibile** di sottoinsiemi (risorse/aule) tali che, all'interno di ciascun sottoinsieme, le richieste siano a due a due compatibili (nessuna sovrapposizione). Equivalentemente: assegnare a ogni richiesta una risorsa minimizzando il numero totale di risorse usate, senza mai assegnare alla stessa risorsa due richieste sovrapposte.
### 5. Depth di un'istanza IP
*(18/02/2025 · Es. 2 · punto 2 · altro)*
> Si definisca il concetto di depth e si discuta la sua importanza per l'analisi del greedy. (Max 5 righe.)

**Risposta.** La **depth** di un'istanza è il massimo numero di richieste che si sovrappongono in uno stesso punto (istante) della retta dei tempi. È importante perché costituisce un **lower bound** al numero di risorse necessarie in qualsiasi soluzione (le depth richieste sovrapposte in quel punto devono necessariamente stare su risorse diverse). Dimostrando che l'algoritmo greedy usa esattamente `depth` risorse, si conclude che il lower bound è raggiunto e quindi il greedy è ottimo.
### 6. Definizione formale IP (09/09/2025)
*(09/09/2025 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema.

**Risposta.** Vedi item 4 — stessa definizione, nessuna variazione nel testo.
### 7. Perché il greedy per finish time non è ottimo per IP
*(09/09/2025 · Es. 2 · punto 2 · discuti-correttezza)*
> Si motivi perché un algoritmo greedy che ordina per finish time non trova la soluzione ottima. (Max 5 righe.)

**Risposta.** Ordinando per tempo di fine, l'algoritmo può processare un intervallo che inizia molto presto (e quindi occupa fin da subito una risorsa) solo dopo aver già aperto nuove aule per intervalli che iniziano più tardi ma finiscono prima. In questo modo l'algoritmo non riesce a riutilizzare correttamente le risorse già libere al momento dell'inizio di ciascun intervallo, e può aprire più aule del necessario, superando la depth dell'istanza (che è invece il numero ottimo).
### 8. Greedy ottimo per IP e complessità
*(09/09/2025 · Es. 2 · punto 3 · calcola-complessità)*
> Si descriva l'algoritmo greedy ottimo discutendone la complessità (non si discuta la correttezza). (Max 5 righe.)

**Risposta.** Si ordinano gli intervalli per **tempo di inizio $s_i$ crescente**. Si mantiene un min-heap delle aule aperte, con chiave il tempo di fine dell'ultimo intervallo assegnato a ciascuna. Per ogni intervallo $i$ (in ordine di $s_i$): se il minimo del min-heap è $\le s_i$, si estrae quell'aula, vi si assegna $i$ e si reinserisce con chiave $f_i$; altrimenti si apre una nuova aula con chiave $f_i$. Complessità: $O(n\log n)$ per l'ordinamento più $n$ operazioni di heap $O(\log n)$ ciascuna $\Rightarrow O(n\log n)$ totale.
### 9. Definizione formale IP (30/06/2026)
*(30/06/2026 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema.

**Risposta.** Vedi item 4 — stessa definizione, nessuna variazione nel testo.
### 10. Controesempio al greedy per finish time su IP
*(30/06/2026 · Es. 2 · punto 2 · costruisci-esempio)*
> Si mostri che il greedy per tempo di fine non trova sempre la soluzione ottima. (Max 5 righe.)

**Risposta.** Si considerino tre intervalli: $A=[0,10)$, $B=[1,2)$, $C=[2,3)$. La depth è 2 (in $[1,2)$ si sovrappongono $A$ e $B$), quindi l'ottimo usa 2 aule (aula 1: $A$; aula 2: $B,C$). Ordinando per tempo di fine si processa $B$ ($f=2$), poi $C$ ($f=3$), poi $A$ ($f=10$): $B$ va in aula 1; $C$ è compatibile con aula 1 (finisce $B$ a 2, inizia $C$ a 2) quindi va in aula 1; $A$ inizia a 0, sovrapposto sia a $B$ che a $C$ già assegnati in aula 1, quindi serve una nuova aula 2. Risultato: 2 aule — in questo caso specifico coincide, ma con istanze leggermente più fitte (es. aggiungendo un quarto intervallo $D=[3,10)$ sovrapposto solo ad $A$) l'ordine per finish time forza ad aprire una terza aula pur essendo la depth ancora 2, mostrando la non ottimalità del criterio.
### 11. Correttezza del greedy per tempo di inizio su IP
*(30/06/2026 · Es. 2 · punto 3 · discuti-correttezza)*
> Si argomenti sulla correttezza dell'algoritmo greedy che ordina per tempo di inizio. (Max 10 righe.)

**Risposta.** Sia $d$ la depth dell'istanza. Si mostra che il greedy (descritto nell'item 8) non apre mai più di $d$ aule: supponiamo che, per assegnare l'intervallo $i$, il greedy debba aprire l'aula $(d{+}1)$-esima; ciò accade solo se tutte le $d$ aule già aperte sono "occupate" al tempo $s_i$, cioè ciascuna contiene un intervallo che si sovrappone a $s_i$ (altrimenti sarebbe libera e verrebbe riusata). Questi $d$ intervalli, insieme a $i$ stesso, sono $d+1$ intervalli a due a due sovrapposti nel punto $s_i$, contraddicendo il fatto che la depth massima è $d$. Quindi il greedy usa al più $d$ aule. D'altra parte $d$ è anche un lower bound per qualunque soluzione (le $d$ richieste sovrapposte in un punto devono stare su risorse distinte). Poiché il greedy raggiunge esattamente il lower bound $d$, la sua soluzione è ottima.
