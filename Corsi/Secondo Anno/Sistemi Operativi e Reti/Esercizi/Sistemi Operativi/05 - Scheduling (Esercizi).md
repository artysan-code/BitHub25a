# Esercizi Svolti — Scheduling
Esercizi di calcolo sullo scheduling della CPU, svolti passo-passo, a supporto della parte teorica dello scritto del **Modulo 1**. Per la teoria vedi [[05 - Scheduling]].

> [!info] Sui numeri di questi esercizi
> Gli esercizi 1, 2, 5 e 6 riprendono gli esempi delle slide del corso; gli esercizi 3 (SRTN) e 4 (Round-Robin) sono costruiti per illustrare il metodo. Tutti i conti sono stati verificati numericamente.
> **Definizioni** (per un job con tempo di arrivo $a$, durata di burst $b$, istante di completamento $c$):
> - **Tempo di turnaround** $T = c - a$ (dall'arrivo alla fine).
> - **Tempo di attesa** $W = T - b$ (tempo passato in coda, non in esecuzione).
> - **Tempo di risposta** = primo istante di esecuzione $-\,a$.
## Es. 1 — FCFS vs SJF (turnaround e attesa medi)
> [!quote] Consegna
> Quattro job $A, B, C, D$ disponibili tutti a $t = 0$ con durate $8, 4, 4, 4$ minuti. Calcolare turnaround medio e attesa media con **FCFS** (ordine di arrivo $A, B, C, D$) e con **SJF**. Commentare.

**FCFS** — esecuzione `A B C D`:
```
A........B....C....D....
0       8   12   16   20
```

| Job | Arrivo | Burst | Completamento | Turnaround $T$ | Attesa $W=T-b$ |
| --- | ------ | ----- | ------------- | -------------- | -------------- |
| A   | 0      | 8     | 8             | 8              | 0              |
| B   | 0      | 4     | 12            | 12             | 8              |
| C   | 0      | 4     | 16            | 16             | 12             |
| D   | 0      | 4     | 20            | 20             | 16             |

Turnaround medio $= \dfrac{8+12+16+20}{4} = \dfrac{56}{4} = \mathbf{14}$ · attesa media $= \dfrac{0+8+12+16}{4} = \dfrac{36}{4} = \mathbf{9}$.
**SJF** — i job più brevi per primi, ordine `B C D A` (4, 4, 4, 8):
```
B....C....D....A........
0    4    8   12       20
```

| Job | Burst | Completamento | Turnaround | Attesa |
| --- | ----- | ------------- | ---------- | ------ |
| B   | 4     | 4             | 4          | 0      |
| C   | 4     | 8             | 8          | 4      |
| D   | 4     | 12            | 12         | 8      |
| A   | 8     | 20            | 20         | 12     |

Turnaround medio $= \dfrac{4+8+12+20}{4} = \dfrac{44}{4} = \mathbf{11}$ · attesa media $= \dfrac{0+4+8+12}{4} = \dfrac{24}{4} = \mathbf{6}$.

> [!check] Conclusione
> Con tutti i job disponibili contemporaneamente, **SJF minimizza il turnaround medio** ($11 < 14$): mandare avanti i job brevi riduce l'attesa accumulata da tutti quelli che seguono.
## Es. 2 — SJF non è ottimale con arrivi sfasati
> [!quote] Consegna
> Cinque job $A$–$E$ con durate $2, 4, 1, 1, 1$ e arrivi a $t = 0, 0, 3, 3, 3$. Mostrare che l'ordine scelto da SJF **non** minimizza il turnaround medio.

A $t = 0$ sono disponibili solo $A$ (2) e $B$ (4); $C, D, E$ arrivano a $t = 3$. SJF (non-preemptive) sceglie il più breve tra i disponibili: prima $A$, poi — a $t = 2$, con solo $B$ disponibile — $B$, e infine $C, D, E$. Ordine `A B C D E`:
```
A..B....C.D.E.
0  2    6 7 8 9
```

| Job | Arrivo | Burst | Compl. | Turnaround |
| --- | ------ | ----- | ------ | ---------- |
| A   | 0      | 2     | 2      | 2          |
| B   | 0      | 4     | 6      | 6          |
| C   | 3      | 1     | 7      | 4          |
| D   | 3      | 1     | 8      | 5          |
| E   | 3      | 1     | 9      | 6          |

Turnaround medio $= \dfrac{2+6+4+5+6}{5} = \dfrac{23}{5} = \mathbf{4{,}6}$.
Ma se, dopo $A$, si eseguono i job da 1 minuto appena arrivano (a $t = 3$) e si rimanda $B$, ordine `A C D E B`:
```
A. C D E B....
0 2(idle)3 4 5 6   10
```

| Job | Arrivo | Burst | Compl. | Turnaround |
| --- | ------ | ----- | ------ | ---------- |
| A   | 0      | 2     | 2      | 2          |
| C   | 3      | 1     | 4      | 1          |
| D   | 3      | 1     | 5      | 2          |
| E   | 3      | 1     | 6      | 3          |
| B   | 0      | 4     | 10     | 10         |

Turnaround medio $= \dfrac{2+1+2+3+10}{5} = \dfrac{18}{5} = \mathbf{3{,}6}$.

> [!check] Conclusione
> $3{,}6 < 4{,}6$: l'ordine scelto da SJF **non** è ottimale. SJF minimizza il turnaround medio **solo se tutti i job sono disponibili allo stesso istante**; con arrivi sfasati conviene a volte ritardare un job lungo già pronto per servire job brevi che arriveranno a breve.
## Es. 3 — SRTN (Shortest Remaining Time Next, con prelazione)
> [!quote] Consegna
> Quattro processi con (arrivo, burst): $P_1(0, 7)$, $P_2(2, 4)$, $P_3(4, 1)$, $P_4(5, 4)$. Applicare **SRTN**: a ogni arrivo si confronta il tempo totale del nuovo processo con il tempo **rimanente** di quello in esecuzione, e si esegue sempre il rimanente più breve. Costruire il diagramma di esecuzione e calcolare i tempi medi.

Ragionamento per istanti notevoli:
- $t=0$: solo $P_1$ (rim. 7) → esegue $P_1$.
- $t=2$: arriva $P_2$ (4). Rimanente di $P_1 = 5 > 4$ → **prelazione**, esegue $P_2$.
- $t=4$: arriva $P_3$ (1). Rimanente di $P_2 = 2 > 1$ → **prelazione**, esegue $P_3$ (finisce a $t=5$).
- $t=5$: arriva $P_4$ (4). Disponibili: $P_2$ (rim. 2), $P_4$ (4), $P_1$ (rim. 5) → esegue $P_2$ (finisce a $t=7$).
- $t=7$: disponibili $P_4$ (4), $P_1$ (5) → esegue $P_4$ (finisce a $t=11$).
- $t=11$: resta $P_1$ (5) → finisce a $t=16$.
```
P1..P2..P3.P2..P4....P1.....
0   2   4  5  7      11      16
```

| Processo | Arrivo | Burst | Compl. | Turnaround | Attesa |
| -------- | ------ | ----- | ------ | ---------- | ------ |
| $P_1$    | 0      | 7     | 16     | 16         | 9      |
| $P_2$    | 2      | 4     | 7      | 5          | 1      |
| $P_3$    | 4      | 1     | 5      | 1          | 0      |
| $P_4$    | 5      | 4     | 11     | 6          | 2      |

Turnaround medio $= \dfrac{16+5+1+6}{4} = \dfrac{28}{4} = \mathbf{7{,}0}$ · attesa media $= \dfrac{9+1+0+2}{4} = \dfrac{12}{4} = \mathbf{3{,}0}$.

> [!note] Osservazione
> SRTN favorisce fortemente i job brevi ($P_3$ ha attesa 0), a costo di penalizzare i lunghi ($P_1$, il più lungo, finisce per ultimo). Richiede di conoscere i tempi in anticipo, come SJF.
## Es. 4 — Round-Robin e calcolo dell'overhead
> [!quote] Consegna
> Tre processi disponibili a $t = 0$: $P_1 = 24$, $P_2 = 3$, $P_3 = 3$ (durate). Quanto $q = 4$. Calcolare turnaround e attesa medi. Poi, con cambio di contesto di $1\,\text{ms}$ e quanto di $4\,\text{ms}$, calcolare la percentuale di CPU sprecata in overhead.

Esecuzione a turni (chi non finisce torna in fondo alla coda):
```
P1..P2.P3.P1..P1..P1..P1..P1..
0   4  7  10 14  18  22  26  30
```

| Processo | Burst | Compl. | Turnaround | Attesa $=T-b$ |
|---|---|---|---|---|
| $P_1$ | 24 | 30 | 30 | 6 |
| $P_2$ | 3 | 7 | 7 | 4 |
| $P_3$ | 3 | 10 | 10 | 7 |

Turnaround medio $= \dfrac{30+7+10}{3} = \dfrac{47}{3} \approx \mathbf{15{,}67}$ · attesa media $= \dfrac{6+4+7}{3} = \dfrac{17}{3} \approx \mathbf{5{,}67}$.
**Overhead del quanto**: ogni quanto "utile" di $4\,\text{ms}$ è preceduto/seguito da un cambio di contesto di $1\,\text{ms}$. La frazione di tempo sprecata è
$$\frac{t_{\text{switch}}}{t_{\text{switch}} + q} = \frac{1}{1 + 4} = \frac{1}{5} = \mathbf{20\%}.$$

> [!warning] Trade-off del quanto
> Quanto **troppo piccolo** → la frazione di overhead cresce (con $q = 1\,\text{ms}$ e switch $1\,\text{ms}$ sarebbe il $50\%$). Quanto **troppo grande** → l'overhead svanisce ma peggiora il tempo di risposta (RR degenera verso FCFS). Compromesso tipico: $q$ tra $20$ e $50\,\text{ms}$.
## Es. 5 — Schedulabilità real-time
> [!quote] Consegna
> Verificare se i seguenti insiemi di eventi periodici sono schedulabili (condizione $\sum_i C_i / P_i \le 1$):
> (a) periodi $100, 200, 500\,\text{ms}$, tempi richiesti $50, 30, 100\,\text{ms}$;
> (b) periodi $100, 200, 500\,\text{ms}$, tempi richiesti $50, 80, 100\,\text{ms}$.

**(a)**
$$\frac{50}{100} + \frac{30}{200} + \frac{100}{500} = 0{,}5 + 0{,}15 + 0{,}2 = 0{,}85 \le 1 \;\Rightarrow\; \textbf{schedulabile}.$$
**(b)**
$$\frac{50}{100} + \frac{80}{200} + \frac{100}{500} = 0{,}5 + 0{,}4 + 0{,}2 = 1{,}1 > 1 \;\Rightarrow\; \textbf{NON schedulabile}.$$

> [!note] Significato
> La condizione confronta la **frazione di CPU** richiesta da ciascun evento (tempo di servizio diviso periodo) con la capacità totale (1). Se la somma supera 1, la CPU non basta a gestire tutti gli eventi entro le loro scadenze, a prescindere dall'algoritmo.
## Es. 6 — Guaranteed scheduling (rapporto consumato/dovuto)
> [!quote] Consegna
> Tre utenti condividono una risorsa per un totale di $100$ minuti. Hanno consumato: Giulia $20$, Matteo $40$, Luca $10$ minuti. Con la regola del **guaranteed scheduling**, chi deve usare la risorsa adesso?

Quota dovuta a ciascuno: $100 / 3 \approx 33{,}3$ minuti. Rapporto $= \dfrac{\text{consumato}}{\text{dovuto}}$:

| Utente | Consumato | Dovuto | Rapporto |
|---|---|---|---|
| Giulia | 20 | 33,3 | $\approx 0{,}6$ |
| Matteo | 40 | 33,3 | $\approx 1{,}2$ |
| Luca | 10 | 33,3 | $\approx 0{,}3$ |

Si esegue il processo con il **rapporto più basso** (chi è più indietro rispetto alla propria quota): ordine **Luca** $(0{,}3)$ → **Giulia** $(0{,}6)$ → **Matteo** $(1{,}2)$.

> [!note] Collegamento
> È l'idea alla base del **CFS** (Completely Fair Scheduler) di Linux: tenere tutti il più vicino possibile alla quota equa $1/n$. Vedi [[05 - Scheduling#Guaranteed scheduling]].
## Es. 7 — Round-Robin: l'effetto del quanto
> [!quote] Consegna
> Quattro processi disponibili a $t = 0$ (ordine di arrivo $A, B, C, D$) con durate $A = 6$, $B = 3$, $C = 1$, $D = 7$. Calcolare turnaround e attesa medi con **quanto $q = 3$** e con **quanto $q = 2$**, e confrontare.

**$q = 3$** — chi non finisce torna in fondo alla coda:
```
A.. B.. C. D.. A.. D.. D.
0   3   6  7   10  13  16 17
```

| Processo | Burst | Compl. | Turnaround | Attesa $=T-b$ |
|---|---|---|---|---|
| A | 6 | 13 | 13 | 7 |
| B | 3 | 6 | 6 | 3 |
| C | 1 | 7 | 7 | 6 |
| D | 7 | 17 | 17 | 10 |

Turnaround medio $= \dfrac{13+6+7+17}{4} = \dfrac{43}{4} = \mathbf{10{,}75}$ · attesa media $= \dfrac{7+3+6+10}{4} = \dfrac{26}{4} = \mathbf{6{,}50}$.
**$q = 2$** — più turni, più cambi di contesto:
```
A. B. C D. A. B D. A. D. D.
0  2  4 5  7  9 10 12 14 16 17
```

| Processo | Burst | Compl. | Turnaround | Attesa |
|---|---|---|---|---|
| A | 6 | 14 | 14 | 8 |
| B | 3 | 10 | 10 | 7 |
| C | 1 | 5 | 5 | 4 |
| D | 7 | 17 | 17 | 10 |

Turnaround medio $= \dfrac{14+10+5+17}{4} = \dfrac{46}{4} = \mathbf{11{,}50}$ · attesa media $= \dfrac{8+7+4+10}{4} = \dfrac{29}{4} = \mathbf{7{,}25}$.

> [!check] Il compromesso del quanto
> Con $q = 2$ i tempi medi **peggiorano** (turnaround $11{,}50 > 10{,}75$): un quanto più piccolo aumenta i cambi di contesto e spezzetta i job lunghi. In compenso **migliora il tempo di risposta** — ogni processo riceve la CPU prima la prima volta — vantaggio prezioso nei sistemi interattivi. È lo stesso trade-off dell'[[#Es. 4 — Round-Robin e calcolo dell'overhead|overhead del quanto (Es. 4)]]: né troppo grande (RR → FCFS), né troppo piccolo (overhead dominante).
## Da svolgere
Esercizi senza soluzione, per esercitarsi. Per la teoria vedi [[05 - Scheduling]].

> [!todo] Da svolgere
> 1. **SRTN.** Processi con (arrivo, burst): $P_1(0,8)$, $P_2(1,4)$, $P_3(2,2)$, $P_4(3,1)$. Costruisci il diagramma [[#Es. 3 — SRTN (Shortest Remaining Time Next, con prelazione)|SRTN]] e calcola turnaround e attesa medi.
> 2. **Priorità con prelazione.** Quattro processi con (arrivo, burst, priorità — 1 = più alta): $A(0,4,3)$, $B(1,2,1)$, $C(2,3,2)$, $D(3,1,1)$. Schedula a [[05 - Scheduling#Scheduling a priorità|priorità con prelazione]] (a parità, FCFS) e calcola i tempi medi. Quale processo rischia la *starvation*?
> 3. **Confronto FCFS/SJF/RR.** Per i processi dell'[[#Es. 1 — FCFS vs SJF (turnaround e attesa medi)|Es. 1]] calcola anche il turnaround medio con **Round-Robin $q = 4$** e confrontalo con FCFS e SJF.
> 4. **Lottery scheduling.** Tre processi hanno rispettivamente 10, 30 e 60 biglietti. Qual è la probabilità che ciascuno venga scelto a una data estrazione? Su 100 estrazioni, quante volte ci si aspetta venga eseguito il terzo? (vedi [[05 - Scheduling#Lottery scheduling|lottery scheduling]]).

---
**Teoria di riferimento:** [[05 - Scheduling]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
