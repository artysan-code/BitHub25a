---
tags:
  - ricerca-operativa
  - lezione
  - simplesso
slide: "Teoria_Simplesso.pdf"
---

# 3. Metodo del Simplesso e Due Fasi

> [!info] Cosa impariamo qui
> Sappiamo che l'ottimo di un PL, se esiste, sta in una SBA (vertice algebrico). Il **metodo del Simplesso** è l'algoritmo che esplora le SBA in modo intelligente: parte da una SBA iniziale, e ad ogni iterazione si sposta a una SBA *adiacente* che migliora $z$. Si ferma quando non può più migliorare (ottimalità) o quando rileva direzioni illimitate.

## 3.1 Forma canonica e Costi Ridotti

### 3.1.1 Forma canonica rispetto a una base

Sia $B$ una base ammissibile, $F$ la fuori-base. Si possono ottenere — con operazioni di Gauss-Jordan sul sistema $Ax = b$ — le **espressioni esplicite** di $x_B$ e $z$ in funzione delle sole $x_F$:

$$\begin{cases} z = \bar{z}_B + \sum_{j} \bar{c}_{F_j} x_{F_j} \\ x_{B_i} = \bar{b}_i - \sum_{j} \bar{a}_{i F_j} x_{F_j}, \quad i = 1, \dots, m \end{cases}$$

Questa scrittura si chiama **forma canonica rispetto alla base $B$**. Significato dei simboli:
- $\bar{z}_B$ = valore della F.O. nella SBA corrente;
- $\bar{b}_i$ = valore di $x_{B_i}$ nella SBA corrente;
- $\bar{c}_{F_j}$ = **costo ridotto** della variabile fuori base $x_{F_j}$;
- $\bar{a}_{i F_j}$ = coefficiente "aggiornato" della $j$-esima fuori base nel vincolo $i$.

### 3.1.2 Costo ridotto: intuizione

> [!quote] Definizione — Costo ridotto
> Il costo ridotto $\bar{c}_j$ di una variabile $x_j$ rispetto alla base $B$ è il coefficiente di $x_j$ nella funzione obiettivo *espressa in forma canonica*. In formula matriciale: $\bar{c}_j = c_j - c_B^T B^{-1} A_j$.

**Significato pratico**: $\bar{c}_j$ misura di quanto cambia $z$ se aumentiamo $x_j$ di una unità *partendo dalla soluzione corrente*, mantenendo l'ammissibilità.
- $\bar{c}_j > 0$: aumentare $x_j$ **peggiora** $z$ (in problema $\min$) — non conviene.
- $\bar{c}_j < 0$: aumentare $x_j$ **migliora** $z$ — conviene farla entrare in base.
- $\bar{c}_j = 0$: indifferente — può segnalare soluzioni ottime multiple o degenere.

I costi ridotti delle variabili **in base** sono per definizione $= 0$ (non appaiono nella F.O. in forma canonica).

### 3.1.3 Test di Ottimalità

> [!quote] Teorema 5 — Test di Ottimalità (condizione sufficiente)
> Se in una base $B$ ammissibile tutti i costi ridotti sono $\bar{c}_j \ge 0$, allora la SBA associata è **OTTIMA**.

> [!warning] Non è "se e solo se"
> Il viceversa non vale in generale: posso avere una SBA ottima con qualche $\bar{c}_j < 0$, ma solo nel caso di SBA **degenere**. In assenza di degenerazione, $\bar{c}_j \ge 0$ è anche necessario.

## 3.2 L'Algoritmo del Simplesso (passi)

Sia il PL in forma standard $\min\ c^T x$ s.t. $Ax = b, x \ge 0$, e sia $B$ una **base ammissibile** iniziale (per ora la diamo per fornita; vedere §3.5 per costruirla).

**Passo 1 — Forma canonica.** Riscrivere $z$ e $x_B$ in funzione di $x_F$.

**Passo 2 — Test di ottimalità.** Se $\bar{c}_j \ge 0$ per tutte le $x_j$ fuori base $\implies$ STOP, base corrente OTTIMA.

**Passo 3 — Test di illimitatezza.** Se esiste $x_h$ fuori base con $\bar{c}_h < 0$ e $\bar{a}_{ih} \le 0$ per *ogni* riga $i$ $\implies$ STOP, problema **ILLIMITATO** inferiormente. (Si può aumentare $x_h$ all'infinito senza violare alcun vincolo, facendo divergere $z \to -\infty$.)

**Passo 4 — Variabile entrante.** Scegliere $x_h$ fuori base con $\bar{c}_h < 0$. Se ce ne sono più di una si può scegliere (a) la più negativa (regola di Dantzig) o (b) quella con indice minore (regola di Bland, anti-ciclo).

**Passo 5 — Variabile uscente: test del quoziente minimo.** Si calcola
$$\theta = \min_{i : \bar{a}_{ih} > 0} \left\{ \frac{\bar{b}_i}{\bar{a}_{ih}} \right\}$$
La variabile $x_{B_t}$ corrispondente alla riga $t$ del minimo **esce** dalla base. L'elemento $\bar{a}_{th}$ è il **pivot**.

**Passo 6 — Pivot.** Aggiornare la base sostituendo $x_{B_t}$ con $x_h$. Tornare al Passo 1.

> [!info] Perché il test del quoziente
> Aumentando $x_h$ da $0$ a $\theta$, la variabile $x_{B_i}$ diminuisce di $\bar{a}_{ih} \cdot \theta$ (se $\bar{a}_{ih} > 0$). Affinché $x_{B_i} \ge 0$ continui a valere, $\theta$ è limitato dal *rapporto più stringente* $\bar{b}_i / \bar{a}_{ih}$.

> [!warning] Test del quoziente solo per $\bar{a}_{ih} > 0$
> Se $\bar{a}_{ih} \le 0$ la corrispondente variabile $x_{B_i}$ resta $\ge 0$ comunque, quindi non vincola $\theta$. Considerare anche i denominatori $\le 0$ porta a errori (numeri negativi o $\theta = 0$ artefatti).

## 3.3 Simplesso in forma di Tableau

Per fare i conti a mano serve un'organizzazione tabellare. Il **tableau** del Simplesso (dopo aver scritto $z$ come un vincolo aggiuntivo $z - c^T x = 0$) ha la struttura:

$$\begin{array}{c|c|c|c}
& x_B & x_F & b \\
\hline
-z & 0 & \bar{c}_F & -\bar{z}_B \\
\hline
x_B & I & \bar{F} & \bar{b}
\end{array}$$

Significato:
- **Riga $-z$** (o riga $0$): contiene i costi ridotti delle fuori base nella forma canonica corrente, e $-\bar{z}_B$ a destra.
- **Sottomatrice $I$**: le colonne in base formano l'identità.
- **$\bar{F} = B^{-1} F$**: colonne aggiornate delle fuori base.
- **$\bar{b} = B^{-1} b$**: valori correnti delle $x_B$ a destra.

### Operazione di pivot sul tableau

Una volta scelta colonna entrante $h$ e riga uscente $t$:

1. Dividere riga $t$ per $\bar{a}_{th}$ (pivot a $1$).
2. Sottrarre $\bar{a}_{ih} \cdot R_t$ a ogni altra riga $R_i$ (incluso $R_0$) per azzerare la colonna $h$.

> [!warning] Non toccare la colonna $-z$
> La colonna implicita di $z$ (il $-1$ in riga 0) deve restare invariata. Sono ammesse solo operazioni $R_0 \leftarrow R_0 + \alpha R_i$; **mai** $R_i \leftarrow R_i + \alpha R_0$ (introdurrebbe dipendenza da $z$ nei vincoli).

> [!example] Lettura del tableau finale
> - Se tutti i costi ridotti sulla riga $-z$ sono $\ge 0$: base attuale **ottima**. Il valore di $z^*$ è l'**opposto** del numero a destra di $-z$.
> - Se esiste un costo ridotto negativo $\bar{c}_h < 0$ e tutta la colonna $h$ ha $\bar{a}_{ih} \le 0$: problema **illimitato**.
> - Altrimenti: continuare con un altro pivot.

## 3.4 Casi notevoli durante il Simplesso

### 3.4.1 Soluzioni di base degeneri

Una SBA è **degenere** se qualche $\bar{b}_i = 0$ (almeno una variabile in base vale $0$). Conseguenze:
- $\theta = 0$ è possibile $\implies$ il cambio base non migliora $z$.
- Si rischia di **ciclare** (visitare ripetutamente le stesse basi senza progredire).

### 3.4.2 Regola di Bland (anti-ciclo)

> [!quote] Regola di Bland
> Quando ci sono più candidate per l'ingresso o l'uscita dalla base, scegliere sempre la variabile con **indice minimo**.
> - Entrante: $h = \min\{j : \bar{c}_j < 0\}$
> - Uscente: $t = \min\{B_i : \bar{b}_i / \bar{a}_{ih} = \theta\}$

> [!quote] Teorema 6 — Convergenza con regola di Bland
> Usando la regola di Bland, il Simplesso converge a una soluzione ottima (o riconosce illimitatezza/inammissibilità) in al più $\binom{n}{m}$ iterazioni.

### 3.4.3 Soluzioni ottime multiple

Se all'ottimo c'è una variabile fuori base con $\bar{c}_j = 0$, allora esiste un'altra base ottima ottenuta facendo entrare $x_j$ (e i punti del segmento tra le due basi sono *tutti* ottimi → infinite soluzioni ottime).

### 3.4.4 Illimitatezza

Se $\bar{c}_h < 0$ e tutta la colonna $h$ è $\le 0$, il test del quoziente non ha denominatori positivi $\implies$ $\theta = +\infty$. Aumentando $x_h$ a piacere $z$ scende a $-\infty$.

## 3.5 Metodo delle Due Fasi (M2F)

Il Simplesso parte da una SBA ammissibile, ma cosa fare se non c'è una base identità "naturale"? Esempi:
- Vincoli $\ge$: la variabile di surplus entra con segno $-$, non forma identità.
- Vincoli $=$: nessuno slack disponibile.
- Vincoli $\le$ con RHS negativo già moltiplicato per $-1$ → $\ge$.

In tutti questi casi si usa il **Metodo delle Due Fasi**.

### 3.5.1 Fase I — Problema artificiale

Si introduce una **variabile artificiale** $y_i \ge 0$ in ogni vincolo che non ha già uno slack pulito, e si risolve il **problema artificiale**:

$$w^* = \min\ \mathbf{1}^T y = y_1 + y_2 + \dots + y_m \quad \text{s.t.} \quad Ax + Iy = b,\ x, y \ge 0$$

Le variabili artificiali $y$ partono in base (formano l'identità $I$), così abbiamo una SBA iniziale ovvia: $x = 0, y = b \ge 0$.

> [!info] Preparazione del tableau di Fase I
> Il tableau iniziale ha la riga di $w$ con $0$ sulle $x$ e $1$ sulle $y$. Per passare alla forma canonica rispetto alle $y$ in base, bisogna **sottrarre da $R_w$ tutte le righe dei vincoli** (così i costi ridotti delle $y$ in base si azzerano e quelli delle $x$ diventano $\bar{c}_x$). Senza questo passaggio i costi ridotti delle artificiali in base non sono $0$ — errore comune.

Dopo aver risolto il problema artificiale col Simplesso:

| Esito | Significato |
|---|---|
| $w^* > 0$ | Le artificiali non si annullano $\implies$ vincoli incompatibili $\implies$ **PROBLEMA INAMMISSIBILE**, STOP |
| $w^* = 0$ | Esiste SBA per il problema originale, passo a Fase II |

> [!warning] Artificiale in base alla fine della Fase I
> Se $w^* = 0$ ma qualche $y_i$ è ancora in base (a valore $0$), va estromessa con un pivot "degenere" su un qualsiasi elemento non-nullo nella sua riga. Solo se l'intera riga è di soli $0$ sulle $x$, allora quel vincolo era **ridondante** e si può cancellare.

### 3.5.2 Fase II — Problema originale

Una volta ottenuta una SBA ammissibile fatta di sole variabili $x$:

1. **Eliminare le colonne** delle variabili artificiali $y$.
2. **Reinserire la F.O. originale** $z = c^T x$ al posto della $w$.
3. **Riportare la riga di $z$ in forma canonica** rispetto alla base corrente: sottrarre dalle righe della F.O. le righe dei vincoli, in modo da azzerare i costi ridotti delle variabili attualmente in base.
4. **Applicare il Simplesso standard** fino al test di ottimalità.

> [!example] Esempio sintetico — quando serve Fase I
> $\min\ x_1 + 2x_2$ s.t. $x_1 + x_2 \ge 4$, $x_1 - x_2 \le 2$, $x_{1,2} \ge 0$. Forma standard: $x_1 + x_2 - s_1 = 4$, $x_1 - x_2 + s_2 = 2$. La $s_1$ entra con $-1$, non forma identità $\implies$ aggiungo $y_1$ al primo vincolo, Fase I minimizza $y_1$. (Lo svolgimento completo è in [[4 - Esercizi Simplesso e Due Fasi]] Esempio 2.)

## 3.6 Convergenza e complessità

> [!quote] Teorema — Convergenza
> Senza basi degeneri: il Simplesso visita ogni SBA al più una volta e termina in al più $\binom{n}{m}$ iterazioni. Con basi degeneri: senza accorgimenti può ciclare; con la **regola di Bland** la convergenza è garantita comunque in al più $\binom{n}{m}$ iterazioni.

In pratica, su problemi reali, il Simplesso converge in $O(m)$ o $O(n)$ iterazioni (lontano dal caso peggiore esponenziale).

## 3.7 Schema operativo riepilogativo

```
INPUT: PL in forma standard, m vincoli, n variabili

STEP 0: Identifica base ammissibile iniziale
        - se ci sono slack su TUTTI i vincoli (≤) con RHS ≥ 0 → usa gli slack
        - altrimenti → Metodo Due Fasi (Fase I)

STEP 1: Costruisci tableau in forma canonica rispetto alla base

LOOP:
   STEP 2: TUTTI i costi ridotti ≥ 0 ?
           SÌ → STOP: OTTIMO trovato, z* = -(valore in alto a destra)
           NO → continua

   STEP 3: Esiste x_h con c̄_h < 0 e colonna h tutta ≤ 0 ?
           SÌ → STOP: PROBLEMA ILLIMITATO
           NO → continua

   STEP 4: Variabile entrante x_h:
           - regola di Dantzig: c̄_h più negativo
           - regola di Bland: indice minimo tra c̄_j < 0

   STEP 5: Test del quoziente:
           θ = min { b̄_i / ā_ih : ā_ih > 0 }
           Variabile uscente x_{B_t} dalla riga del minimo

   STEP 6: Pivot su ā_{th}:
           - R_t ← R_t / ā_th  (porta pivot a 1)
           - R_i ← R_i - ā_ih * R_t per ogni altra riga (incluso R_0)

   Torna a STEP 2.
```

> [!info] Riferimenti
> Dispensa `Teoria_Simplesso.pdf`, §6–15 (pp. 20–46). Per esempi numerici svolti vedere `Lez4Simplesso24_marzo_2026.pdf` e [[4 - Esercizi Simplesso e Due Fasi]].
