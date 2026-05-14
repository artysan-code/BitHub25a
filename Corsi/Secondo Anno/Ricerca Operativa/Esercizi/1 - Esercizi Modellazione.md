# Esercizio 1 — Linearizzazione Min-Max
Un'azienda vuole minimizzare il massimo tra tre misure di costo, definite come:

$$e_1 = 2x_1 + x_2, \quad e_2 = x_1 + 3x_2, \quad e_3 = x_1 - x_2 + 5$$

con $x_1 + x_2 \leq 10$, $x_1, x_2 \geq 0$.

**Formulazione lineare:**
Introduco la variabile ausiliaria $y$ che rappresenta il massimo dei tre costi:

$$\min \quad y$$

$$\begin{array}{l}
y \geq 2x_1 + x_2 \\
y \geq x_1 + 3x_2 \\
y \geq x_1 - x_2 + 5 \\
x_1 + x_2 \leq 10 \\
x_1, x_2, y \geq 0
\end{array}$$

*Nota:* Si usa la trasformazione $\min\{\max(e_1,e_2,e_3)\} \Leftrightarrow \min y$ con $y \geq e_i\ \forall i$.

---
# Esercizio 2 — Vincoli Logici e Metodo Big-M
Un'azienda valuta se aprire uno o entrambi i magazzini A e B per soddisfare una domanda minima di 90 unità. I dati sono:

| | Impianto A | Impianto B |
|---|---|---|
| Costo fisso di apertura | 200 | 150 |
| Capacità massima | 100 | 80 |
| Costo variabile (€/unità) | 3 | 4 |

**Vincolo logico aggiuntivo:** se si apre B, si deve aprire anche A.

**Variabili:**
- $x_A, x_B \geq 0$: unità prodotte da ciascun impianto
- $y_A, y_B \in \{0,1\}$: 1 se l'impianto è aperto, 0 altrimenti

**Formulazione PLI:**

$$\min \quad 3x_A + 4x_B + 200\,y_A + 150\,y_B$$

$$\begin{array}{ll}
x_A + x_B \geq 90 & \text{(domanda minima)} \\
x_A \leq 100\,y_A & \text{(attivazione A — Big-M con } M = 100\text{)} \\
x_B \leq 80\,y_B & \text{(attivazione B — Big-M con } M = 80\text{)} \\
y_B \leq y_A & \text{(se apre B} \implies \text{apre A)} \\
x_A, x_B \geq 0, \quad y_A, y_B \in \{0,1\}
\end{array}$$

**Analisi delle soluzioni candidate:**

| $y_A$ | $y_B$ | Ammissibile? | Costo minimo |
|---|---|---|---|
| 0 | 0 | No ($x_A=x_B=0$, domanda non soddisfatta) | — |
| 0 | 1 | No (viola $y_B \leq y_A$) | — |
| 1 | 0 | Sì: $x_A = 90$, $z = 3(90) + 200 = 470$ | **470** |
| 1 | 1 | Sì: per minimizzare, $x_A = 10, x_B = 80$, $z = 30 + 320 + 200 + 150 = 700$ | 700 |

**Soluzione ottima:** aprire solo A, produrre 90 unità, $z^* = 470$.

[[2 - Esercizi Vertici e Basi|Prossimo Argomento]]
