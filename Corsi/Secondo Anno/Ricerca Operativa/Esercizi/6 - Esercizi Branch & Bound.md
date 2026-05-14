# Esercizio 1 — Branch & Bound (Massimizzazione)
$$\begin{array}{}
\max \quad x_1 + x_2 \\
2x_1 + 5x_2 \leq 16 \\
6x_1 + 5x_2 \leq 30 \\
x_1, x_2 \geq 0,\ \text{interi}
\end{array}$$

---
## Nodo 0 — Rilassamento Lineare (radice)
Si risolve il problema ignorando il vincolo di interezza. L'intersezione dei due vincoli attivi dà:

$$2x_1 + 5x_2 = 16 \quad \text{e} \quad 6x_1 + 5x_2 = 30 \implies 4x_1 = 14 \implies x_1 = 3.5,\ x_2 = 1.8$$

**Ottimo RL:** $x_1 = 3.5,\ x_2 = 1.8,\ z_{RL} = 5.3$ (frazionario).
Inizializzo l'Incumbent (miglior intero trovato): $UB = -\infty$.

---
## Branch su $x_1$ (variabile più frazionaria: $x_1 = 3.5$)
Si creano due sottoproblemi:
- **Nodo 1 (Sinistra):** aggiungo $x_1 \leq 3$
- **Nodo 2 (Destra):** aggiungo $x_1 \geq 4$

---
### Nodo 1 — $x_1 \leq 3$
Con $x_1 \leq 3$, il massimo ammissibile è $x_1 = 3$. Rimpiazzo nel primo vincolo:

$$2(3) + 5x_2 \leq 16 \implies x_2 \leq 2 \quad \text{e} \quad 6(3)+5x_2 \leq 30 \implies x_2 \leq 2.4$$

L'ottimo è $x_1 = 3,\ x_2 = 2$: valore intero! $z = 5$.
**Aggiorno Incumbent:** $UB = 5$. Nodo chiuso per ottimalità locale.

---
### Nodo 2 — $x_1 \geq 4$
Con $x_1 \geq 4$, dal secondo vincolo:

$$6(4) + 5x_2 \leq 30 \implies x_2 \leq 1.2$$

Ottimo del rilassamento: $x_1 = 4,\ x_2 = 1.2,\ z_{RL} = 5.2 > UB = 5$.
Il bound supera l'Incumbent, quindi il nodo va esplorato.
#### Branch su $x_2$ ($x_2 = 1.2$)
- **Nodo 3 (Sinistra):** $x_1 \geq 4,\ x_2 \leq 1$
  $x_1 = 4,\ x_2 = 1$: valore intero, $z = 5$.
  $z = 5 \leq UB = 5$: nessun miglioramento. Nodo chiuso.

- **Nodo 4 (Destra):** $x_1 \geq 4,\ x_2 \geq 2$
  Dal secondo vincolo: $6x_1 + 10 \leq 30 \implies x_1 \leq 3.33$, ma $x_1 \geq 4$: **INAMMISSIBILE**.
  Nodo chiuso per infattibilità.

---
## Albero B&B
```
Nodo 0: z_RL = 5.3 (x1=3.5, x2=1.8)
├── Nodo 1 [x1≤3]: z=5 intero ✓ → UB=5 (chiuso per ottimalità)
└── Nodo 2 [x1≥4]: z_RL=5.2
    ├── Nodo 3 [x2≤1]: z=5 intero, ≤UB (chiuso)
    └── Nodo 4 [x2≥2]: INAMMISSIBILE (chiuso)
```

---
## Soluzione ottima
$$x_1^* = 3,\ x_2^* = 2,\quad z^* = 5$$

*(Anche $(4,1)$ e $(5,0)$ sono ottime con $z=5$; la prima trovata diventa l'incumbent.)*
