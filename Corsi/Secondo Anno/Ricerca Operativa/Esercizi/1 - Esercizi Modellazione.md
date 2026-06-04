# Esercizi — Modellazione Matematica

> [!info] Come usare questo file
> Ogni esercizio è composto da **Traccia** seguita immediatamente da **Svolgimento**. Per esercitarti a libro chiuso, copri lo Svolgimento con la mano (o un foglio) mentre leggi la Traccia.

> [!info] Provenienza degli esercizi
> Tutti gli esercizi di questo file sono presi **direttamente dai materiali ufficiali del corso**:
> - **De Giovanni-Brentegani** → `Materiale Didattico/m01.modPL.01.modelli.pdf`
> - **Caramia-Stecca** → `Materiale Didattico/Materiale Teams/RO_Lez02_12_marzo_2024_Formulazione_Esercizi.pdf`
>
> La fonte specifica è indicata in calce a ogni traccia.

---

# Esercizio 1 — Gioco di assemblaggio

## Traccia
Per l'assemblaggio di telecomandi, si hanno a disposizione **10 moduli display, 18 moduli di logica di controllo, 12 trasmettitori, 21 tastierini, 9 moduli di navigazione e 10 led**. I telecomandi sono di due tipi:

- **Tipo A**: richiede 1 display, 1 modulo di navigazione, 2 tastierini, 2 moduli di logica, 1 trasmettitore e 1 led.
- **Tipo B**: richiede 2 display, 3 tastierini, 2 moduli di logica e 3 trasmettitori.

Considerando che il tipo A permette un guadagno netto di 3 euro e il tipo B di 8 euro, determinare la produzione che **massimizza il guadagno**.

*Fonte: De Giovanni-Brentegani §3.1.*

## Svolgimento
**Variabili decisionali:**
- $x_A$: quantità di telecomandi di tipo A da produrre;
- $x_B$: quantità di telecomandi di tipo B da produrre.

**Modello PLI:**

$$\begin{array}{rl}
\max & 3 x_A + 8 x_B \quad \text{(guadagno complessivo)} \\
\text{s.t.} & x_A + 2 x_B \le 10 \quad \text{(display)} \\
& x_A \le 9 \quad \text{(navigazione)} \\
& 2 x_A + 3 x_B \le 21 \quad \text{(tastierini)} \\
& 2 x_A + 2 x_B \le 18 \quad \text{(logica)} \\
& x_A + 3 x_B \le 12 \quad \text{(trasmissione)} \\
& x_A \le 10 \quad \text{(led)} \\
& x_A, x_B \in \mathbb{Z}_+ \quad \text{(dominio intero)}
\end{array}$$

> [!info] Schema 1 — Mix produttivo
> *Variabili* = "quanto produrre di ogni prodotto". *Vincoli* = "per ogni risorsa, consumo ≤ disponibilità". *F.O.* = profitto totale.

---

# Esercizio 2 — Dieta economica

## Traccia
Un dietologo deve preparare una dieta che garantisca un apporto giornaliero di proteine, ferro e calcio di almeno **20 mg, 30 mg e 10 mg** rispettivamente.

Il dietologo è orientato su cibi a base di **verdura** (5 mg/kg di proteine, 6 mg/kg di ferro, 5 mg/kg di calcio, al costo di 4 €/kg), **carne** (15 mg/kg di proteine, 10 mg/kg di ferro, 3 mg/kg di calcio, al costo di 10 €/kg) e **frutta** (4 mg/kg di proteine, 5 mg/kg di ferro, 12 mg/kg di calcio, al costo di 7 €/kg).

Determinare la dieta di **costo minimo**.

*Fonte: De Giovanni-Brentegani §3.2.*

## Svolgimento
**Variabili decisionali:**
- $x_1$: kg di cibi a base di verdura nella dieta;
- $x_2$: kg di cibi a base di carne nella dieta;
- $x_3$: kg di cibi a base di frutta nella dieta.

**Modello PL:**

$$\begin{array}{rl}
\min & 4 x_1 + 10 x_2 + 7 x_3 \quad \text{(costo giornaliero)} \\
\text{s.t.} & 5 x_1 + 15 x_2 + 4 x_3 \ge 20 \quad \text{(proteine)} \\
& 6 x_1 + 10 x_2 + 5 x_3 \ge 30 \quad \text{(ferro)} \\
& 5 x_1 + 3 x_2 + 12 x_3 \ge 10 \quad \text{(calcio)} \\
& x_1, x_2, x_3 \in \mathbb{R}_+
\end{array}$$

> [!info] Schema 2 — Copertura
> *Variabili* = "quanto comprare di ogni alimento". *Vincoli* = "per ogni nutriente, valore $\ge$ richiesto". *F.O.* = costo totale.

---

# Esercizio 3 — Indagine di mercato

## Traccia
Un'azienda pubblicitaria deve svolgere un'indagine di mercato per lanciare un nuovo prodotto. Si deve contattare telefonicamente un campione significativo di persone: **almeno 150 donne sposate, 110 donne non sposate, 120 uomini sposati, 100 uomini non sposati**.

Le telefonate possono essere effettuate al mattino (al costo operativo di **1.1 €**) o alla sera (al costo di **1.6 €**). Le percentuali di persone mediamente raggiunte sono:

|  | Mattino | Sera |
|---|---|---|
| Donne sposate | 30% | 30% |
| Donne non sposate | 10% | 20% |
| Uomini sposati | 10% | 30% |
| Uomini non sposati | 10% | 15% |
| Nessuno | 40% | 5% |

Le telefonate serali sono più costose ma più efficaci (solo il 5% va a vuoto). Minimizzare il costo complessivo delle telefonate da effettuare in modo da raggiungere un campione significativo.

*Fonte: De Giovanni-Brentegani §3.3.*

## Svolgimento
**Variabili decisionali:**
- $x_1$: numero di telefonate da fare al mattino;
- $x_2$: numero di telefonate da fare alla sera.

**Modello PLI** (i coefficienti dei vincoli sono le percentuali = probabilità di raggiungere ciascuna categoria):

$$\begin{array}{rl}
\min & 1.1 x_1 + 1.6 x_2 \quad \text{(costo totale)} \\
\text{s.t.} & 0.3 x_1 + 0.3 x_2 \ge 150 \quad \text{(donne sposate)} \\
& 0.1 x_1 + 0.2 x_2 \ge 110 \quad \text{(donne non sposate)} \\
& 0.1 x_1 + 0.3 x_2 \ge 120 \quad \text{(uomini sposati)} \\
& 0.1 x_1 + 0.15 x_2 \ge 100 \quad \text{(uomini non sposati)} \\
& x_1, x_2 \in \mathbb{Z}_+
\end{array}$$

> [!info] Pattern Schema 2 con percentuali
> Quando il "rendimento" della variabile è una percentuale (es. il 30% di chi chiamo è una donna sposata), la percentuale entra come **coefficiente del vincolo**. Il vincolo dice: "il valore atteso di donne sposate raggiunte deve superare la soglia".

---

# Esercizio 4 — Trasporto di frigoriferi

## Traccia
Una ditta di elettrodomestici produce frigoriferi in **tre stabilimenti** ($A, B, C$) e li smista in **quattro magazzini** intermedi di vendita ($1, 2, 3, 4$).

- **Produzione settimanale** negli stabilimenti $A, B, C$: rispettivamente $50, 70, 20$ unità.
- **Quantità richiesta** dai 4 magazzini: rispettivamente $10, 60, 30, 40$ unità.
- **Costi di trasporto** unitari (euro per ogni frigorifero):
  - da $A$: $6, 8, 3, 4$ euro
  - da $B$: $2, 3, 1, 3$ euro
  - da $C$: $2, 4, 6, 5$ euro

Determinare il piano di trasporti di **costo minimo**.

*Fonte: De Giovanni-Brentegani §3.4.*

## Svolgimento
**Insiemi.**
- $I = \{A, B, C\}$: stabilimenti;
- $J = \{1, 2, 3, 4\}$: magazzini.

**Variabili decisionali:**
- $x_{ij}$: numero di frigoriferi prodotti nello stabilimento $i$ e smistati nel magazzino $j$, $\forall i \in I,\ \forall j \in J$.

**Modello PLI:**

$$\begin{array}{rl}
\min & 6 x_{A1} + 8 x_{A2} + 3 x_{A3} + 4 x_{A4} + \\
& 2 x_{B1} + 3 x_{B2} + 1 x_{B3} + 3 x_{B4} + \\
& 2 x_{C1} + 4 x_{C2} + 6 x_{C3} + 5 x_{C4} \\
\text{s.t.} & x_{A1} + x_{A2} + x_{A3} + x_{A4} \le 50 \quad \text{(capacità A)} \\
& x_{B1} + x_{B2} + x_{B3} + x_{B4} \le 70 \quad \text{(capacità B)} \\
& x_{C1} + x_{C2} + x_{C3} + x_{C4} \le 20 \quad \text{(capacità C)} \\
& x_{A1} + x_{B1} + x_{C1} \ge 10 \quad \text{(domanda mag. 1)} \\
& x_{A2} + x_{B2} + x_{C2} \ge 60 \quad \text{(domanda mag. 2)} \\
& x_{A3} + x_{B3} + x_{C3} \ge 30 \quad \text{(domanda mag. 3)} \\
& x_{A4} + x_{B4} + x_{C4} \ge 40 \quad \text{(domanda mag. 4)} \\
& x_{ij} \in \mathbb{Z}_+,\ \forall i \in I,\ \forall j \in J
\end{array}$$

> [!info] Schema 3 — Trasporto
> Variabili a doppio indice $x_{ij}$: una per ogni cella della tabella sorgenti × destinazioni.
> Due famiglie di vincoli: **offerta** (somma per riga $\le$ capacità sorgente) e **domanda** (somma per colonna $\ge$ richiesta destinazione).
> Conta: **variabili** = $|I|\cdot|J|=3\cdot 4=12$. **Vincoli** = $|I|+|J|=3+4=7$.

---

# Esercizio 5 — Turni in ospedale

## Traccia
Si vogliono organizzare i turni degli infermieri in ospedale. Ogni infermiere lavora **5 giorni consecutivi**, indipendentemente da come sono collocati all'interno della settimana, e poi ha diritto a **due giorni consecutivi di riposo**.

Le esigenze di servizio per i vari giorni della settimana richiedono la presenza di:
**17 infermieri il lunedì, 13 il martedì, 15 il mercoledì, 19 il giovedì, 14 il venerdì, 16 il sabato, 11 la domenica.**

Organizzare il servizio in modo da minimizzare il **numero totale di infermieri** da impegnare.

*Fonte: De Giovanni-Brentegani §3.5.*

## Svolgimento
**Variabili decisionali** (una per giorno di inizio turno):
- $lun$: numero di infermieri il cui turno inizia il lunedì;
- $mar$: numero di infermieri il cui turno inizia il martedì;
- $\dots$
- $dom$: numero di infermieri il cui turno inizia la domenica.

> [!info] Logica chiave
> Ogni infermiere lavora **5 giorni consecutivi** dall'inizio del turno. Quindi un infermiere che inizia il lunedì lavora lun-mar-mer-gio-ven (riposa sab-dom). Uno che inizia il martedì lavora mar-mer-gio-ven-sab (riposa dom-lun). E così via.
> Per ogni giorno della settimana, devo contare **chi lavora quel giorno** = chi ha iniziato il turno tra 4 giorni prima e il giorno stesso.

**Modello PLI:**

$$\begin{array}{rl}
\min & lun + mar + mer + gio + ven + sab + dom \\
\text{s.t.} & lun + gio + ven + sab + dom \ge 17 \quad \text{(lun)} \\
& lun + mar + ven + sab + dom \ge 13 \quad \text{(mar)} \\
& lun + mar + mer + sab + dom \ge 15 \quad \text{(mer)} \\
& lun + mar + mer + gio + dom \ge 19 \quad \text{(gio)} \\
& lun + mar + mer + gio + ven \ge 14 \quad \text{(ven)} \\
& mar + mer + gio + ven + sab \ge 16 \quad \text{(sab)} \\
& mer + gio + ven + sab + dom \ge 11 \quad \text{(dom)} \\
& lun, mar, \dots, dom \in \mathbb{Z}_+
\end{array}$$

---

# Esercizio 6 — Pianificazione multiperiodo

## Traccia
Un'azienda deve pianificare la produzione per le prossime **5 settimane** in modo da evadere senza stockout i seguenti quantitativi di domanda:
$$d_t = \{30, 60, 40, 70, 50\}$$

Costi unitari di produzione: $c_t = \{8, 8, 10, 10, 20\}$.
Costi unitari di stoccaggio per unità di tempo: $h_t = \{1, 1, 2, 2, 2\}$.

Le scorte al periodo iniziale sono $0$. La capacità massima del magazzino è **30 unità**.

Formulare il problema di pianificazione multiperiodo che minimizza la somma dei costi totali.

*Fonte: Caramia-Stecca §1.4.*

## Svolgimento
**Variabili decisionali:**
- $x_t \ge 0$: unità prodotte nel periodo $t$;
- $I_t \ge 0$: scorte a fine periodo $t$.

**Funzione obiettivo** (produzione + stoccaggio):
$$\min\; z = \sum_{t=1}^{5} c_t\, x_t + \sum_{t=1}^{5} h_t\, I_t$$

**Vincoli di bilancio inventario** (cuore del modello):
$$I_t = I_{t-1} + x_t - d_t \qquad \forall t = 1,\dots,5$$

con $I_0 = 0$ noto. Esplicitando per ogni $t$:

$$\begin{array}{l}
x_1 - I_1 = 30 \\
I_1 + x_2 - I_2 = 60 \\
I_2 + x_3 - I_3 = 40 \\
I_3 + x_4 - I_4 = 70 \\
I_4 + x_5 - I_5 = 50
\end{array}$$

**Vincoli di capacità magazzino:**
$$I_t \le 30 \quad \forall t = 1,\dots,5$$

**Domini:** $x_t, I_t \ge 0\ \forall t$.

> [!info] Pattern multiperiodo
> Due famiglie di variabili indicizzate sul tempo: una di "azione" ($x_t$) e una di "stato" ($I_t$). L'**equazione di bilancio** $I_t = I_{t-1} + x_t - d_t$ è obbligatoria: lega ogni periodo al successivo.

---

# Esercizio 7 — Schedulazione just-in-time

## Traccia
Un server computazionale deve pianificare l'esecuzione di **5 batch** su una macchina mono-processore. I batch durano rispettivamente $5, 7, 4, 7, 10$ minuti. La sequenza di esecuzione $1{-}2{-}3{-}4{-}5$ è data e non ci può essere sovrapposizione temporale tra i batch.

Le ore di consegna desiderata sono:
- batch 1: ore 10:32
- batch 2: ore 10:38
- batch 3: ore 10:42
- batch 4: ore 10:52
- batch 5: ore 10:57

La consegna dei batch elaborati deve essere il **più puntuale possibile**: si paga una penale di **750 euro** per ogni minuto di anticipo o ritardo nella consegna.

Organizzare i tempi di esecuzione (al minuto) per minimizzare la penale totale.

*Fonte: De Giovanni-Brentegani §5.11.*

## Svolgimento
> [!info] Trasformare il tempo in minuti
> L'ora non è facilmente trattabile con somme e prodotti. Si traduce tutto in **"minuti dopo le 10:00"**: le 10:32 diventano $32$, le 10:38 diventano $38$, e così via.

**Variabili decisionali:**
- $i_j$: minuto dopo le 10:00 nel quale la macchina inizia il batch $j$, $\forall j \in \{1,2,3,4,5\}$;
- $y_j$: minuti di anticipo o ritardo del batch $j$, $\forall j \in \{1,2,3,4,5\}$.

**Idea della linearizzazione.** Se $i_j$ è il minuto di inizio, $p_j$ la durata e $d_j$ il minuto di consegna desiderato, la penale del batch $j$ è $y_j = |i_j + p_j - d_j|$. Per linearizzarla introduco due vincoli per ogni $j$:
$$y_j \ge i_j + p_j - d_j \qquad y_j \ge -(i_j + p_j - d_j) = d_j - p_j - i_j$$

**Modello PLIM** (durate: $p = \{5,7,4,7,10\}$; consegne: $d=\{32,38,42,52,57\}$):

$$\begin{array}{rl}
\min & 750\,(y_1 + y_2 + y_3 + y_4 + y_5) \\
\text{s.t.} & y_1 \ge i_1 + 5 - 32, \quad y_1 \ge 32 - 5 - i_1 \\
& y_2 \ge i_2 + 7 - 38, \quad y_2 \ge 38 - 7 - i_2 \\
& y_3 \ge i_3 + 4 - 42, \quad y_3 \ge 42 - 4 - i_3 \\
& y_4 \ge i_4 + 7 - 52, \quad y_4 \ge 52 - 7 - i_4 \\
& y_5 \ge i_5 + 10 - 57, \quad y_5 \ge 57 - 10 - i_5 \\
& i_2 \ge i_1 + 5 \\
& i_3 \ge i_2 + 7 \\
& i_4 \ge i_3 + 4 \\
& i_5 \ge i_4 + 7 \\
& i_j \in \mathbb{Z}_+,\ y_j \in \mathbb{R},\ \forall j
\end{array}$$

> [!info] Pattern min-abs (DA RICORDARE)
> Ogni termine $|e|$ in F.O. di **minimizzazione** con segno $+$ si sostituisce con una variabile $y \ge 0$ in F.O. e si aggiungono **due vincoli**: $y \ge e$ e $y \ge -e$.

---

# Esercizio 8 — Localizzazione con costi fissi (Big-M)

## Traccia
Una catena della Grande Distribuzione Organizzata (GDO) dispone di un budget $W$ per l'apertura di nuovi ipermercati in Italia. Gli studi preliminari hanno individuato un insieme $I$ di possibili localizzazioni.

Per l'apertura di un ipermercato nella localizzazione $i$ bisogna sostenere:
- un **costo fisso** $F_i$ (acquisto del terreno, oneri amministrativi, etc.)
- un **costo variabile** $C_i$ ogni 100 mq di ipermercato.

Una volta aperto e a regime, l'ipermercato in $i$ produrrà entrate per $R_i$ ogni 100 mq.

Determinare l'insieme di localizzazioni in cui aprire gli ipermercati e dimensionare gli ipermercati stessi in modo da **massimizzare i ricavi complessivi**, rispettando il budget.

*Fonte: De Giovanni-Brentegani §6.12.*

## Svolgimento
**Insiemi.** $I$: possibili localizzazioni.

**Variabili decisionali:**
- $x_i \ge 0$: dimensione in centinaia di mq dell'ipermercato localizzato in $i$;
- $y_i \in \{0,1\}$: variabile logica binaria — vale 1 se viene aperto un ipermercato in $i$, 0 altrimenti.

> [!warning] Formulazione "naturale" che NON funziona
> Verrebbe naturale scrivere $\max \sum_i R_i\, x_i\, y_i$ con vincolo $\sum_i (C_i\, x_i\, y_i + F_i\, y_i) \le W$. Ma il termine $x_i\, y_i$ è un **prodotto di variabili** $\Rightarrow$ **NON lineare**.

**Modello PLIM corretto** (linearizzazione con vincolo Big-M):

$$\begin{array}{rl}
\max & \sum_{i \in I} R_i\, x_i \\
\text{s.t.} & \sum_{i \in I} \left( C_i\, x_i + F_i\, y_i \right) \le W \quad \text{(budget)} \\
& x_i \le M\, y_i \quad \forall i \in I \quad \text{(attivazione binaria)} \\
& x_i \in \mathbb{R}_+,\ y_i \in \{0, 1\} \quad \forall i \in I
\end{array}$$

> [!info] Logica del vincolo di attivazione $x_i \le M\, y_i$
> - Se $y_i = 0$: $x_i \le 0 \Rightarrow x_i = 0$ (la localizzazione $i$ non è aperta).
> - Se $y_i = 1$: $x_i \le M$ — vincolo ridondante (lascia $x_i$ libera fino a $M$, vincolato dal budget).

---

[[2 - Esercizi Vertici e Basi|Prossimo Argomento]]
