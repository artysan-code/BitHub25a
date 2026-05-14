# Esercizio — Verifica vertice

Dato il poliedro descritto da:

$$\begin{array}{l}
7x_1 - 5x_2 + x_3 \leq 2 \\
-2x_1 + 3x_2 + x_3 \geq 1 \\
x_1, x_2, x_3 \geq 0
\end{array}$$

verificare se $x^{\prime} = [1,\ 1,\ 0]^T$ è un vertice.

---

> [!info] Criterio per vertice (algebrico)
> Un punto $x^{\prime}$ di un poliedro in $\mathbb{R}^n$ è un **vertice** se e solo se i vincoli **attivi** in $x^{\prime}$ contengono $n$ righe linearmente indipendenti. "Attivo" significa che il vincolo vale con il segno di **uguaglianza** in $x^{\prime}$.

---

## Passo 1 — Riscrivo tutti i vincoli in forma $\le$

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

---

## Passo 2 — Identifico i vincoli attivi in $x^{\prime} = [1, 1, 0]^T$

Sostituisco e controllo se vale $a_i^T x^{\prime} = b_i$:

| # | Vincolo | Calcolo | Risultato | Attivo? |
|---|---|---|---|---|
| 1 | $7x_1 - 5x_2 + x_3$ | $7(1) - 5(1) + 0$ | $= 2$ | ✓ |
| 2 | $2x_1 - 3x_2 - x_3$ | $2(1) - 3(1) - 0$ | $= -1$ | ✓ |
| 3 | $-x_1$ | $-1$ | $\neq 0$ | ✗ |
| 4 | $-x_2$ | $-1$ | $\neq 0$ | ✗ |
| 5 | $-x_3$ | $0$ | $= 0$ | ✓ |

Vincoli attivi: $\{1, 2, 5\}$. Sono $3 = n$, il minimo necessario.

---

## Passo 3 — Verifica indipendenza lineare

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

---

> [!example] Conclusione
> $x^{\prime} = [1, 1, 0]^T$ è un **vertice** del poliedro: ha esattamente $3$ vincoli attivi linearmente indipendenti in $\mathbb{R}^3$.

> [!warning] Trappola frequente
> Bisogna **sempre** riscrivere i vincoli $\ge$ come $\le$ (cambiando i segni) e includere anche i vincoli di non-negatività $x_j \ge 0$ riscritti come $-x_j \le 0$. Saltare questo passaggio significa perdere vincoli attivi e non riconoscere vertici "sul bordo dell'ottante positivo".

[[3 - Esercizi Forma Standard|Prossimo Argomento]]
