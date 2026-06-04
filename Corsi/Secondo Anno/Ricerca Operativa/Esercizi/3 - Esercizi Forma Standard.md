# Esercizi — Forma Standard

> [!info] Come usare questo file
> Ogni esercizio ha **Traccia** seguita immediatamente da **Svolgimento**. Per esercitarti a libro chiuso, copri lo Svolgimento con la mano mentre leggi la Traccia.

> [!info] Cosa significa "forma standard"
> $\min\ c^T x$ s.t. $Ax = b$, $b \ge 0$, $x \ge 0$. Tutti i vincoli sono uguaglianze, tutti i termini noti non-negativi, tutte le variabili non-negative, F.O. di minimizzazione.

---

# Esercizio 1

## Traccia
Portare in **forma standard** il seguente problema di Programmazione Lineare:

$$\begin{array}{rl}
\max & 5(-3x_1 + 5x_2 - 7x_3) + 34 \\
\text{s.t.} & -2x_1 + 7x_2 + 6x_3 - 2x_1 \leq 5 \\
 & -3x_1 + x_3 + 12 \geq 13 \\
 & x_1 + x_2 \leq -2 \\
 & x_1 \leq 0 \\
 & x_2 \geq 0
\end{array}$$

## Svolgimento

**Sostituzioni di variabile:**
- $x_3$ è libera di segno (non dichiarata) $\implies$ pongo $x_3 = x_3^+ - x_3^-$ con $x_3^+, x_3^- \ge 0$.
- $x_1 \le 0$ ma serve $\ge 0$ $\implies$ pongo $\hat{x}_1 = -x_1$ (cioè $x_1 = -\hat{x}_1$), con $\hat{x}_1 \ge 0$.

**F.O.** — semplifico l'espressione e applico $\max f \to \min -f$:

$$5(-3x_1 + 5x_2 - 7x_3) + 34 = -15x_1 + 25x_2 - 35x_3 + 34$$

Sostituendo le variabili:
$$= 15\hat{x}_1 + 25x_2 - 35x_3^+ + 35x_3^- + 34$$

$$\max f \to \min -f \implies \min\ -15\hat{x}_1 - 25x_2 + 35x_3^+ - 35x_3^- - 34$$

> [!info] La costante additiva
> Il termine $-34$ è una costante: non influisce sulla scelta della soluzione ottima, solo sul valore di $z$.

**1° vincolo** — semplifico ($-2x_1 - 2x_1 = -4x_1$), aggiungo slack:
$$-4x_1 + 7x_2 + 6x_3 \leq 5$$
Sostituendo:
$$4\hat{x}_1 + 7x_2 + 6x_3^+ - 6x_3^- + s_1 = 5,\quad s_1 \geq 0$$

**2° vincolo** — porto $12$ a destra, sottraggo surplus:
$$-3x_1 + x_3 \geq 1 \implies 3\hat{x}_1 + x_3^+ - x_3^- - s_2 = 1,\quad s_2 \geq 0$$

**3° vincolo** — il RHS è $-2 < 0$: moltiplico per $-1$ invertendo il verso, poi sottraggo surplus:
$$x_1 + x_2 \leq -2 \implies -x_1 - x_2 \geq 2 \implies \hat{x}_1 - x_2 - s_3 = 2,\quad s_3 \geq 0$$

**Risultato — forma standard:**

$$\begin{array}{rl}
\min & -15\hat{x}_1 - 25x_2 + 35x_3^+ - 35x_3^- - 34 \\
\text{s.t.} & 4\hat{x}_1 + 7x_2 + 6x_3^+ - 6x_3^- + s_1 = 5 \\
 & 3\hat{x}_1 + x_3^+ - x_3^- - s_2 = 1 \\
 & \hat{x}_1 - x_2 - s_3 = 2 \\
 & \hat{x}_1, x_2, x_3^+, x_3^-, s_1, s_2, s_3 \geq 0
\end{array}$$

> [!warning] Errori frequenti
> - Dimenticare di applicare $\max \to \min$ a **tutti** i termini della F.O. (incluse le costanti additive se le tieni).
> - Aggiungere lo slack al vincolo $\le$ **prima** di aver portato il RHS $\ge 0$: bisogna prima sistemare il segno del termine noto, poi introdurre le variabili ausiliarie.
> - Confondere slack ($\le$, si **aggiunge** $+s$) e surplus ($\ge$, si **sottrae** $-s$).

---

# Esercizio 2

## Traccia
Portare in **forma standard** il seguente problema:

$$\begin{array}{rl}
\min & -13x_1 - 20x_2 + 5x_3 + x_4 \\
\text{s.t.} & -4x_1 + x_2 \geq 1 \\
 & 5x_2 + 3x_3 = 4 \\
 & 3x_1 + 12x_3 - x_4 \geq -2 \\
 & x_2 + x_3 + 50x_4 \leq 3 \\
 & x_1, x_2, x_3 \geq 0
\end{array}$$

## Svolgimento

$x_4$ libera di segno: pongo $x_4 = x_4^+ - x_4^-$ con $x_4^+, x_4^- \ge 0$.

**1° vincolo** ($\ge$, surplus):
$$-4x_1 + x_2 - s_1 = 1$$

**2° vincolo** già uguaglianza con RHS $\ge 0$: nessuna modifica.
$$5x_2 + 3x_3 = 4$$

**3° vincolo** — RHS $= -2 < 0$, moltiplico per $-1$ invertendo il verso, poi slack:
$$3x_1 + 12x_3 - x_4 \geq -2 \implies -3x_1 - 12x_3 + x_4 \leq 2 \implies -3x_1 - 12x_3 + x_4^+ - x_4^- + s_2 = 2$$

**4° vincolo** ($\le$, slack):
$$x_2 + x_3 + 50x_4^+ - 50x_4^- + s_3 = 3$$

**Risultato:**

$$\begin{array}{rl}
\min & -13x_1 - 20x_2 + 5x_3 + x_4^+ - x_4^- \\
\text{s.t.} & -4x_1 + x_2 - s_1 = 1 \\
 & 5x_2 + 3x_3 = 4 \\
 & -3x_1 - 12x_3 + x_4^+ - x_4^- + s_2 = 2 \\
 & x_2 + x_3 + 50x_4^+ - 50x_4^- + s_3 = 3 \\
 & x_1, x_2, x_3, x_4^+, x_4^-, s_1, s_2, s_3 \geq 0
\end{array}$$

---

[[4 - Esercizi Simplesso e Due Fasi|Prossimo Argomento]]
