# Esercizi — Dualità e Scarti Complementari

> [!info] Come usare questo file
> Ogni esercizio ha **Traccia** seguita immediatamente da **Svolgimento**. Per esercitarti a libro chiuso, copri lo Svolgimento con la mano mentre leggi la Traccia.

---

# Richiamo — Tabella di Tucker

Per costruire il duale serve memorizzare la corrispondenza tra **tipo di vincolo** e **segno della variabile associata**. La tabella vale così com'è se il primale è di $\min$; si legge specularmente se è di $\max$.

| Primale $\min$ | Duale $\max$ |
| :--- | :--- |
| vincolo $i$-esimo $\ge$ | $u_i \ge 0$ |
| vincolo $i$-esimo $\le$ | $u_i \le 0$ |
| vincolo $i$-esimo $=$ | $u_i$ libera di segno |
| $x_j \ge 0$ | vincolo duale $j$-esimo $\le$ |
| $x_j \le 0$ | vincolo duale $j$-esimo $\ge$ |
| $x_j$ libera di segno | vincolo duale $j$-esimo $=$ |

> [!warning] Attenzione
> "Libera di segno" **non** significa "uguale a zero". Vuol dire che la variabile può assumere qualunque valore in $\mathbb{R}$; nel duale corrisponde a un vincolo di **uguaglianza**, non a una variabile assente.

---

# Esercizio 1 — Dualizzazione generica (primale $\min$)

## Traccia
Sia il primale:

$$\begin{array}{rl}
\min & c^{T}x - d^{T}y \\
\text{s.t.} & Ax \leq a \\
 & By \leq b \\
 & Cx + Dy = e \\
 & x \geq 0,\ y \text{ libera di segno}
\end{array}$$

Scrivere il problema **duale**.

## Svolgimento
**Passo 1 — assegno una variabile duale a ogni vincolo:**
- $Ax \leq a \implies u_1$ (vincolo $\le$ in problema $\min$ $\implies u_1 \le 0$)
- $By \leq b \implies u_2$ ($u_2 \le 0$)
- $Cx + Dy = e \implies u_3$ (vincolo $=$ $\implies u_3$ libera)

**Passo 2 — F.O. duale:** coefficienti = termini noti del primale.
$$\max\ a^{T}u_1 + b^{T}u_2 + e^{T}u_3$$

**Passo 3 — vincoli duali (uno per variabile primale):**
- $x \ge 0 \implies$ vincolo duale $\le$ del coefficiente di $x$ in F.O. primale: $A^{T}u_1 + C^{T}u_3 \le c$
- $y$ libera $\implies$ vincolo duale $=$: $B^{T}u_2 + D^{T}u_3 = -d$

**Duale risultante:**

$$\begin{array}{rl}
\max & a^{T}u_1 + b^{T}u_2 + e^{T}u_3 \\
\text{s.t.} & A^{T}u_1 + C^{T}u_3 \leq c \\
 & B^{T}u_2 + D^{T}u_3 = -d \\
 & u_1 \leq 0,\ u_2 \leq 0,\ u_3 \text{ libera}
\end{array}$$

> [!info] Regola mnemonica
> Per ogni **variabile** del primale c'è un **vincolo** del duale; per ogni **vincolo** del primale c'è una **variabile** del duale. Il numero di righe della matrice si trasforma nel numero di colonne (e viceversa) — la matrice si traspone.

---

# Esercizio 2 — Dualizzazione generica (primale $\max$)

## Traccia
Stesso problema dell'Esercizio 1 ma in **massimizzazione**:

$$\begin{array}{rl}
\max & c^{T}x - d^{T}y \\
\text{s.t.} & Ax \leq a \\
 & By \leq b \\
 & Cx + Dy = e \\
 & x \geq 0,\ y \text{ libera di segno}
\end{array}$$

Scrivere il problema **duale**.

## Svolgimento
Le regole di Tucker si leggono specularmente.

Corrispondenze (primale $\max$ $\implies$ vincolo $\le$ dà $u \ge 0$):
- $Ax \le a \implies u_1 \ge 0$
- $By \le b \implies u_2 \ge 0$
- $Cx + Dy = e \implies u_3$ libera
- $x \ge 0$ $\implies$ vincolo duale $\ge c$
- $y$ libera $\implies$ vincolo duale $=$

**Duale:**

$$\begin{array}{rl}
\min & a^{T}u_1 + b^{T}u_2 + e^{T}u_3 \\
\text{s.t.} & A^{T}u_1 + C^{T}u_3 \geq c \\
 & B^{T}u_2 + D^{T}u_3 = -d \\
 & u_1 \geq 0,\ u_2 \geq 0,\ u_3 \text{ libera}
\end{array}$$

---

# Esercizio 3 — Dualizzazione numerica

## Traccia
$$\begin{array}{rl}
\max & 4x_1 + 3x_2 + 2x_3 \\
\text{s.t.} & x_1 + 2x_2 + 3x_3 \leq 8 \\
 & 2x_1 \phantom{ + 0x_2} - x_3 \leq 7 \\
 & 3x_1 + 4x_2 - x_3 \leq 5 \\
 & \phantom{0x_1 + }x_2 + x_3 \leq 6 \\
 & x_2 \geq 0,\ x_1\ \text{e}\ x_3\ \text{libere di segno}
\end{array}$$

Scrivere il problema **duale**.

## Svolgimento

> [!warning] Lettura del testo
> Il vincolo di segno è specificato **solo** per $x_2$. Le altre variabili ($x_1, x_3$) si intendono **libere di segno**: possono valere qualunque numero reale.

**Passo 1 — variabili duali (primale $\max$ con vincoli $\le$ $\implies u_i \ge 0$):**

| Vincolo primale | Variabile duale |
|---|---|
| $x_1 + 2x_2 + 3x_3 \le 8$ | $u_1 \ge 0$ |
| $2x_1 - x_3 \le 7$ | $u_2 \ge 0$ |
| $3x_1 + 4x_2 - x_3 \le 5$ | $u_3 \ge 0$ |
| $x_2 + x_3 \le 6$ | $u_4 \ge 0$ |

**Passo 2 — F.O. duale** (coefficienti = termini noti primale):
$$\min\ 8u_1 + 7u_2 + 5u_3 + 6u_4$$

**Passo 3 — vincoli duali (uno per ogni variabile primale):**

- Colonna $x_1$ (libera) → vincolo duale di $=$ con RHS $= c_1 = 4$:
  $$u_1 + 2u_2 + 3u_3 + 0u_4 = 4$$
- Colonna $x_2$ ($\ge 0$) → vincolo duale $\ge c_2 = 3$:
  $$2u_1 + 0u_2 + 4u_3 + u_4 \geq 3$$
- Colonna $x_3$ (libera) → vincolo duale di $=$ con RHS $= c_3 = 2$:
  $$3u_1 - u_2 - u_3 + u_4 = 2$$

**Duale:**

$$\begin{array}{rl}
\min & 8u_1 + 7u_2 + 5u_3 + 6u_4 \\
\text{s.t.} & u_1 + 2u_2 + 3u_3 = 4 \\
 & 2u_1 + 4u_3 + u_4 \geq 3 \\
 & 3u_1 - u_2 - u_3 + u_4 = 2 \\
 & u_1, u_2, u_3, u_4 \geq 0
\end{array}$$

---

# Esercizio 4 — Verifica ottimalità con Scarti Complementari

## Traccia
Verificare se $\bar{x} = (12, 9)$ è ottima per il problema dei profumi (Esercizio 1 di [[4 - Esercizi Simplesso e Due Fasi]]) usando le **Condizioni degli Scarti Complementari** (CSC).

**Primale (MAX):**
$$\begin{array}{rl}
\max & 130x_1 + 100x_2 \\
\text{s.t.} & 1.5x_1 + x_2 \leq 27 \\
 & x_1 + x_2 \leq 21 \\
 & 0.3x_1 + 0.5x_2 \leq 9 \\
 & x_1, x_2 \geq 0
\end{array}$$

## Svolgimento
**Duale associato (MIN)** — vincoli $\leq$ del MAX danno $u_i \geq 0$; $x_j \geq 0$ danno vincoli duali $\geq c_j$:
$$\begin{array}{rl}
\min & 27u_1 + 21u_2 + 9u_3 \\
\text{s.t.} & 1.5u_1 + u_2 + 0.3u_3 \geq 130 \\
 & u_1 + u_2 + 0.5u_3 \geq 100 \\
 & u_1, u_2, u_3 \geq 0
\end{array}$$

**Step 1 — Ammissibilità di $\bar{x}=(12,9)$:**

| Vincolo primale | Valore | Slack |
|---|---|---|
| $1.5(12)+9=27\leq 27$ | ✓ | $s_1=0$ |
| $12+9=21\leq 21$ | ✓ | $s_2=0$ |
| $0.3(12)+0.5(9)=8.1\leq 9$ | ✓ | $s_3=0.9$ |

**Step 2 — CSC sui vincoli primali** (slack $> 0 \implies$ variabile duale $= 0$):
$$s_3 = 0.9 > 0 \implies u_3 = 0$$

**Step 3 — CSC sulle variabili primali** ($x_j > 0 \implies$ vincolo duale $j$ saturo):
$$x_1=12>0 \implies 1.5u_1+u_2+0.3u_3=130 \xrightarrow{u_3=0} 1.5u_1+u_2=130$$
$$x_2=9>0 \implies u_1+u_2+0.5u_3=100 \xrightarrow{u_3=0} u_1+u_2=100$$

**Risolvo il sistema:**
$$1.5u_1+u_2=130 \quad \text{e} \quad u_1+u_2=100 \implies 0.5u_1=30 \implies u_1=60,\quad u_2=40$$

**Step 4 — Ammissibilità duale:** $u_1=60\geq 0$ ✓, $u_2=40\geq 0$ ✓, $u_3=0\geq 0$ ✓.

**Step 5 — Verifica Dualità Forte:**
$$z^* = 130(12)+100(9)=2460 \qquad w^* = 27(60)+21(40)+9(0)=1620+840=2460\ \checkmark$$

Conclusione: $\bar{x}=(12,9)$ è **OTTIMA**.

---

[[6 - Esercizi Branch & Bound|Prossimo Argomento]]
