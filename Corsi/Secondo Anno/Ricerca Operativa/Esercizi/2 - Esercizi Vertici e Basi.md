# Esercizi — Vertici e Basi

> [!info] Come usare questo file
> Ogni esercizio ha **Traccia** seguita immediatamente da **Svolgimento**. Per esercitarti a libro chiuso, copri lo Svolgimento con la mano mentre leggi la Traccia.

---

# Esercizio 1 — Verifica vertice

## Traccia
Dato il poliedro descritto da:

$$\begin{array}{l}
7x_1 - 5x_2 + x_3 \leq 2 \\
-2x_1 + 3x_2 + x_3 \geq 1 \\
x_1, x_2, x_3 \geq 0
\end{array}$$

verificare se $x^{\prime} = [1,\ 1,\ 0]^T$ è un **vertice**.

## Svolgimento

> [!info] Criterio per vertice (algebrico)
> Un punto $x^{\prime}$ di un poliedro in $\mathbb{R}^n$ è un **vertice** se e solo se i vincoli **attivi** in $x^{\prime}$ contengono $n$ righe linearmente indipendenti. "Attivo" significa che il vincolo vale con il segno di **uguaglianza** in $x^{\prime}$.

### Passo 1 — Riscrivo tutti i vincoli in forma $\le$

Per uniformare la lettura, riscrivo tutto come $Ax \le b$:

$$\begin{array}{ll}
7x_1 - 5x_2 + x_3 \leq 2 & \text{(già }\le\text{)} \\
2x_1 - 3x_2 - x_3 \leq -1 & \text{(ho moltiplicato il 2° per }-1\text{)} \\
-x_1 \leq 0 & \text{(da }x_1 \ge 0\text{)} \\
-x_2 \leq 0 & \text{(da }x_2 \ge 0\text{)} \\
-x_3 \leq 0 & \text{(da }x_3 \ge 0\text{)}
\end{array}$$

Matrice completa:

$$A = \begin{bmatrix}
7 & -5 & 1 \\
2 & -3 & -1 \\
-1 & 0 & 0 \\
0 & -1 & 0 \\
0 & 0 & -1
\end{bmatrix},\quad
b = \begin{bmatrix}
2 \\ -1 \\ 0 \\ 0 \\ 0
\end{bmatrix}$$

### Passo 2 — Identifico i vincoli attivi in $x^{\prime} = [1, 1, 0]^T$

Sostituisco e controllo se vale $a_i^T x^{\prime} = b_i$:

| # | Vincolo | Calcolo | Risultato | Attivo? |
|---|---|---|---|---|
| 1 | $7x_1 - 5x_2 + x_3$ | $7(1) - 5(1) + 0$ | $= 2$ | ✓ |
| 2 | $2x_1 - 3x_2 - x_3$ | $2(1) - 3(1) - 0$ | $= -1$ | ✓ |
| 3 | $-x_1$ | $-1$ | $\neq 0$ | ✗ |
| 4 | $-x_2$ | $-1$ | $\neq 0$ | ✗ |
| 5 | $-x_3$ | $0$ | $= 0$ | ✓ |

Vincoli attivi: $\{1, 2, 5\}$. Sono $3 = n$, il minimo necessario.

### Passo 3 — Verifica indipendenza lineare

Estraggo dalla matrice $A$ le righe $1, 2, 5$:

$$A_{\text{att}} = \begin{bmatrix}
7 & -5 & 1 \\
2 & -3 & -1 \\
0 & 0 & -1
\end{bmatrix}$$

Le righe sono linearmente indipendenti $\iff \det(A_{\text{att}}) \neq 0$.

**Sviluppo di Laplace lungo la 3ª riga** (ha due zeri):

$$\det(A_{\text{att}}) = (-1) \cdot \det\begin{bmatrix} 7 & -5 \\ 2 & -3 \end{bmatrix} = (-1) \cdot (7 \cdot (-3) - (-5) \cdot 2) = (-1) \cdot (-21 + 10) = 11$$

$\det(A_{\text{att}}) = 11 \neq 0$ $\implies$ righe indipendenti.

> [!example] Conclusione
> $x^{\prime} = [1, 1, 0]^T$ è un **vertice** del poliedro.

> [!warning] Trappola frequente
> Bisogna **sempre** riscrivere i vincoli $\ge$ come $\le$ e includere anche i vincoli di non-negatività $x_j \ge 0$ riscritti come $-x_j \le 0$.

---

# Esercizio 2 — Verifica SBA in forma standard

## Traccia
Dato il problema in **forma standard**

$$\begin{array}{rl}
\min & x_1 + x_2 \\
\text{s.t.} & x_1 + 2x_2 + x_3 = 4 \\
& 2x_1 + x_2 + x_4 = 5 \\
& x_1, x_2, x_3, x_4 \ge 0
\end{array}$$

verificare se $\bar x = (2,\,1,\,0,\,0)$ è una **Soluzione di Base Ammissibile**, e in tal caso dire se è degenere.

## Svolgimento

> [!info] Criterio SBA (forma standard $Ax=b$, $x\ge 0$, $n$ var, $m$ vincoli)
> 1. **Ammissibile**: $A\bar x = b$ e $\bar x \ge 0$.
> 2. Ha (almeno) $n - m$ componenti **nulle**.
> 3. Le colonne di $A$ corrispondenti alle componenti non nulle (al più $m$) sono **linearmente indipendenti**.
>
> Se in base c'è almeno una variabile pari a $0$ $\implies$ SBA **degenere**.

Qui $n=4$, $m=2$, quindi servono $n-m=2$ componenti nulle.

### Passo 1 — Ammissibilità
Sostituisco $\bar x$ nei vincoli:

$$2 + 2(1) + 0 = 4 \;\checkmark \qquad 2(2) + 1 + 0 = 5 \;\checkmark$$

Tutte le componenti $\ge 0$. **Ammissibile.**

### Passo 2 — Conteggio componenti nulle
$\bar x_3 = \bar x_4 = 0$. Sono esattamente $n-m = 2$ componenti nulle. ✓

### Passo 3 — Base e indipendenza lineare
Le componenti in base sono $\{x_1, x_2\}$. Estraggo le colonne $A_1, A_2$ di
$A = \begin{pmatrix} 1 & 2 & 1 & 0 \\ 2 & 1 & 0 & 1 \end{pmatrix}$:

$$B = (A_1\ \, A_2) = \begin{pmatrix} 1 & 2 \\ 2 & 1 \end{pmatrix}, \qquad \det(B) = 1\cdot 1 - 2\cdot 2 = -3 \ne 0$$

Colonne **linearmente indipendenti**. ✓

### Passo 4 — Degenerazione?
$\bar x_1 = 2 > 0$, $\bar x_2 = 1 > 0$: **nessuna** variabile in base è nulla.

> [!example] Conclusione
> $\bar x = (2,1,0,0)$ è **SBA non degenere** del problema dato.

---

# Esercizio 3 — Esistenza vertice con condizioni sulle componenti

## Traccia
Considerando lo **stesso problema** dell'Esercizio 2:

(a) Esiste un vertice con $x_1 > 0$ e $x_2 > 0$?
(b) Esiste un vertice con $x_2 > 0$ e $x_3 > 0$?

## Svolgimento

> [!info] Tecnica generale
> Chiedere "esiste vertice con $x_i, x_j > 0$?" significa **forzare $x_i$ e $x_j$ in base** e controllare se il sistema risultante ha soluzione ammissibile (segno $\ge 0$ su tutte le componenti).

### Domanda (a): $x_1 > 0, x_2 > 0$
Metto $x_1, x_2$ in base $\implies x_3 = x_4 = 0$. Sistema $Ax = b$:

$$\begin{cases} x_1 + 2x_2 = 4 \\ 2x_1 + x_2 = 5 \end{cases}$$

Dalla 1ª: $x_1 = 4 - 2x_2$. Sostituisco nella 2ª: $2(4-2x_2) + x_2 = 5 \implies 8 - 3x_2 = 5 \implies x_2 = 1$, $x_1 = 2$.

Soluzione: $\bar x = (2,1,0,0)$. Tutte componenti $\ge 0$ → **SÌ**, è un vertice.

### Domanda (b): $x_2 > 0, x_3 > 0$
Metto $x_2, x_3$ in base $\implies x_1 = x_4 = 0$. Sistema:

$$\begin{cases} 2x_2 + x_3 = 4 \\ x_2 = 5 \end{cases}$$

Quindi $x_2 = 5$ e $x_3 = 4 - 2(5) = -6 < 0$.

La soluzione $\bar x = (0,5,-6,0)$ **non è ammissibile** (componente negativa) → **NO**, non esiste vertice con $x_2$ e $x_3$ entrambe in base e positive.

> [!info] Schema operativo per "esiste vertice con $x_h>0$?"
> 1. Metti $x_h$ in base (insieme ad altre $m-1$ var da scegliere, o tutte già fissate dal testo).
> 2. Azzera le $n-m$ variabili non in base.
> 3. Risolvi il sistema $m\times m$.
> 4. Verifica segno: tutte $\ge 0$ → SÌ. Almeno una $< 0$ → NO.

---

[[3 - Esercizi Forma Standard|Prossimo Argomento]]
