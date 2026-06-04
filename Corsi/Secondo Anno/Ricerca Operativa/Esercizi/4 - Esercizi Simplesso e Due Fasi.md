# Esercizi — Simplesso e Due Fasi

> [!info] Come usare questo file
> Ogni esercizio ha **Traccia** seguita immediatamente da **Svolgimento**. Per esercitarti a libro chiuso, copri lo Svolgimento con la mano mentre leggi la Traccia.

---

# Esercizio 1 — Simplesso primale (problema dei profumi)

## Traccia
Una ditta di profumi realizza due nuove fragranze a partire da 3 essenze: rosa, mughetto e viola.

Per realizzare un decalitro di fragranza 1 sono richiesti 1,5 litri di rosa, 1 litro di mughetto e 0,3 litri di viola.
Per realizzare un decalitro di fragranza 2 sono richiesti 1 litro di rosa, 1 litro di mughetto e 0,5 litri di viola.

La disponibilità in magazzino per le tre essenze è di 27, 21 e 9 litri per rosa, mughetto e viola rispettivamente.
Sapendo che l'azienda realizza un profitto di 130 e 100 euro per ogni decalitro venduto di fragranza 1 e 2 rispettivamente, determinare le quantità ottimali delle due fragranze da produrre.

Risolvere con il **metodo del simplesso** completo (forma standard + tableau + iterazioni fino all'ottimo).

## Svolgimento
Il problema sarà quindi:
$$\begin{array}{}
max & 130x_{1}+100x_{2} \\
 & 1.5x_{1}+x_{2}\leq 27 \\
 & x_{1}+x_{2}\leq 21 \\
 & 0.3x_{1}+0.5x_{2}\leq 9 \\
 & x_{1}\geq 0,x_{2}\geq 0
\end{array}$$
1) porto il problema in forma standard (cambio $\max \to \min$ negando la F.O.): $$\begin{array}{}
min & -130x_{1}-100x_{2} \\
 & 1.5x_{1}+x_{2}\leq 27 \\
 & x_{1}+x_{2}\leq 21 \\
 & 0.3x_{1}+0.5x_{2}\leq 9 \\
 & x_{1}\geq 0,x_{2}\geq 0
\end{array}$$$$\begin{array}{l}
1° vincolo: \\
1.5x_{1}+x_{2}+s_{1}=27 \\ \\
2° vincolo:  \\
x_{1}+x_{2}+s_{2}=21 \\ \\
3° vincolo:  \\
0.3x_{1}+0.5x_{2}+s_{3}=9 \\
\end{array}$$$$\begin{matrix}{} 
min & - & 130x_{1} & - & 100x_{2} \\
 & 1.5x_{1} & + & x_{2} &  + & s_{1}  &  &  &  & & = & 27 \\
 & x_{1} & + & x_{2} &  &  & + & s_{2} & &  &  = & 21 \\
 & 0.3x_{1} & + & 0.5x_{2} &  &  &  &  & +  & s_{3} & = & 9 \\
 & x_{1}, & x_{2}, & s_{1}, & s_{2}, & s_{3} & \geq & 0
\end{matrix}$$
tableau del simplesso:
$$\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 0 & -130 & -100 & 0 & 0 & 0 \\
\hline
s_{1} & 27 & 1.5 & 1 & 1 & 0 & 0\\
\hline
s_{2} & 21 & 1 & 1 & 0 & 1 & 0\\
\hline
s_{3} & 9 & 0.3 & 0.5 & 0 & 0 & 1 \\
\end{array}$$
seleziono il pivot $(*)$ trovando quale è il $min\{\frac{b_{i}}{a_{i}}\}$ e lo porto a 0 effettuando la stessa operazione sulla sua riga
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 0 & -130 & -100 & 0 & 0 & 0 \\
\hline
s_{1} & 27 & (1.5) & 1 & 1 & 0 & 0\\
\hline
s_{2} & 21 & 1 & 1 & 0 & 1 & 0\\
\hline
s_{3} & 9 & 0.3 & 0.5 & 0 & 0 & 1 \\
\end{array}$$
modifico le altre righe in modo che sopra e sotto il pivot ho solamente il valore 0 e successivamente scelgo il prossimo pivot $(*)$
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 2340 & 0 & -\frac{40}{3} & \frac{260}{3} & 0 & 0  & =130*R_{2}+R_{1}\\
\hline
x_{1} & 18 & 1 & \frac{2}{3} & \frac{2}{3} & 0 & 0\\
\hline
s_{2} & 3 & 0 & (\frac{1}{3}) & -\frac{2}{3} & 1 & 0 & =-\frac{2}{3}R_{2}+R_{3}\\
\hline
s_{3} & 3.6 & 0 & 0.3 & 0.2 & 0 & 1 & =-0.3R_{3}+R_{4}
\end{array}$$
porto il nuovo pivot a 1 ed effettuo nuovamente l'azzeramento dei valori sopra e sotto del pivot con operazioni sulle loro righe
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 2460 & 0 & 0 & 60 & 40 & 0  & =\frac{40}{3}R_{3}+R_{1}\\
\hline
x_{1} & 12 & 1 & 0 & 2 & -2 & 0 & =-\frac{2}{3}R_{3}+R_{2}\\
\hline
x_{2} & 9 & 0 & 1 & -2 & 3 & 0 \\
\hline
s_{3} & 0.9 & 0 & 0 & -0.4 & -0.9 & 1 & =-0.3R_{3}+R_{4}
\end{array}$$
la soluzione ottima quindi è:
$$\begin{array}{}
x_{1}=12 \\
x_{2}=9 \\
s_{1},s_{2}=0 \\
s_{3}=0.9 \\
z=2460 (\text{ valore ottimo del problema iniziale})
\end{array}$$

---

# Esercizio 2 — Metodo delle Due Fasi

## Traccia
$$\begin{array}{}
\min \quad x_1 + 2x_2 \\
x_1 + x_2 \geq 4 \\
x_1 - x_2 \leq 2 \\
x_1, x_2 \geq 0
\end{array}$$

Il primo vincolo ($\geq$) non fornisce una variabile slack positiva utilizzabile come base iniziale. Risolvere con il **Metodo delle Due Fasi**.

## Svolgimento
**Forma standard** (surplus $s_1$, slack $s_2$):
$$x_1 + x_2 - s_1 = 4, \quad x_1 - x_2 + s_2 = 2$$

**Fase I — Minimizzare** $w = y_1$ (aggiunta variabile artificiale al 1° vincolo):

Tableau iniziale (riga $w$ aggiornata sottraendo $R_{y_1}$ per azzerare il costo ridotto di $y_1$):
$$\begin{array}{c|c}
 & b & x_1 & x_2 & s_1 & s_2 & y_1 \\
\hline
w & -4 & -1 & -1 & 1 & 0 & 0 \\
\hline
y_1 & 4 & 1 & 1 & -1 & 0 & 1 \\
\hline
s_2 & 2 & 1 & -1 & 0 & 1 & 0
\end{array}$$

Variabile entrante: $x_1$ ($\bar{c}=-1$). Test quoziente: $\min(4/1,\, 2/1)=2$ → esce $s_2$. Pivot su $a_{21}=1$.

$$\Downarrow$$

$$\begin{array}{c|c}
 & b & x_1 & x_2 & s_1 & s_2 & y_1 \\
\hline
w & -2 & 0 & -2 & 1 & 1 & 0 \\
\hline
y_1 & 2 & 0 & 2 & -1 & -1 & 1 \\
\hline
x_1 & 2 & 1 & -1 & 0 & 1 & 0
\end{array}$$

Variabile entrante: $x_2$ ($\bar{c}=-2$). Test quoziente: $2/2=1$ → esce $y_1$. Pivot su $a_{12}=2$.

$$\Downarrow$$

$$\begin{array}{c|c}
 & b & x_1 & x_2 & s_1 & s_2 & y_1 \\
\hline
w & 0 & 0 & 0 & 0 & 0 & 1 \\
\hline
x_2 & 1 & 0 & 1 & -\tfrac{1}{2} & -\tfrac{1}{2} & \tfrac{1}{2} \\
\hline
x_1 & 3 & 1 & 0 & -\tfrac{1}{2} & \tfrac{1}{2} & \tfrac{1}{2}
\end{array}$$

$w^* = 0$ ✓ — base ammissibile trovata: $\{x_2,\, x_1\}$.

**Fase II — Funzione obiettivo originale** $z = x_1 + 2x_2$, colonna $y_1$ eliminata.

Aggiorno riga $z$ azzerando i costi ridotti delle variabili in base ($z - 1{\cdot}R_{x_1} - 2{\cdot}R_{x_2}$):

$$\begin{array}{c|c}
 & b & x_1 & x_2 & s_1 & s_2 \\
\hline
z & -5 & 0 & 0 & \tfrac{3}{2} & \tfrac{1}{2} \\
\hline
x_2 & 1 & 0 & 1 & -\tfrac{1}{2} & -\tfrac{1}{2} \\
\hline
x_1 & 3 & 1 & 0 & -\tfrac{1}{2} & \tfrac{1}{2}
\end{array}$$

Tutti i costi ridotti $\geq 0$: **OTTIMO**.

$$x_1^* = 3,\quad x_2^* = 1,\quad z^* = 5$$

Verifica vincoli: $3+1=4\geq 4$ ✓ (saturo, $s_1=0$), $\;3-1=2\leq 2$ ✓ (saturo, $s_2=0$).

---

# Esercizio 3 — Simplesso "stile 2026" (riga $z$ in alto)

## Traccia
$$\begin{array}{rl}
\min & z = -2x_1 - 3x_2 \\
\text{s.t.} & x_1 + 2x_2 \le 4 \\
& 2x_1 + x_2 \le 5 \\
& x_1, x_2 \ge 0
\end{array}$$

Risolvere col simplesso secondo la convenzione 2026 (riga $z$ in **prima posizione** nel tableau), prestando attenzione alla lettura del valore ottimo (il valore in alto a destra è $-z$, non $z$).

## Svolgimento

> [!info] Convenzione tableau (Caramia 2026)
> - La riga $z$ sta in **prima posizione** (in alto).
> - In quella riga, sotto la colonna $b$, c'è il valore **$-z$** (cioè per leggere il vero $z^*$ alla fine bisogna cambiarlo di segno).
> - Sotto le variabili, in riga $z$, ci sono i **costi ridotti** $\bar c_j$.
> - **Ottimo** quando tutti $\bar c_j \ge 0$ (per problema di min).

**Forma standard** (aggiungo slack $x_3, x_4 \ge 0$):
$$x_1 + 2x_2 + x_3 = 4, \qquad 2x_1 + x_2 + x_4 = 5$$

Base iniziale = $\{x_3, x_4\}$. **Tableau iniziale:**

$$\begin{array}{c|c|cccc}
 & b & x_1 & x_2 & x_3 & x_4 \\
\hline
z & 0 & -2 & -3 & 0 & 0 \\
\hline
x_3 & 4 & 1 & 2 & 1 & 0 \\
x_4 & 5 & 2 & 1 & 0 & 1 \\
\end{array}$$

### Iterazione 1
**Entrante:** $\bar c_2 = -3$ è il più negativo $\implies$ $x_2$ entra.
**Test del minimo rapporto** (solo righe con $\bar a_{i2} > 0$): $\min\{4/2,\, 5/1\} = 2$ sulla riga $x_3$ $\implies$ $x_3$ esce. **Pivot** $a_{12} = 2$.

Divido la riga $x_3$ per $2$; aggiorno le altre per azzerare la colonna $x_2$:
- $R_z \leftarrow R_z + 3\,R_{x_3}^{\text{new}}$
- $R_{x_4} \leftarrow R_{x_4} - 1\,R_{x_3}^{\text{new}}$

$$\Downarrow$$

$$\begin{array}{c|c|cccc}
 & b & x_1 & x_2 & x_3 & x_4 \\
\hline
z & 6 & -\tfrac{1}{2} & 0 & \tfrac{3}{2} & 0 \\
\hline
x_2 & 2 & \tfrac{1}{2} & 1 & \tfrac{1}{2} & 0 \\
x_4 & 3 & \tfrac{3}{2} & 0 & -\tfrac{1}{2} & 1 \\
\end{array}$$

### Iterazione 2
**Entrante:** $\bar c_1 = -\tfrac{1}{2} < 0$ $\implies$ $x_1$ entra.
**Rapporti** (righe con $\bar a_{i1} > 0$): $\min\{2/(1/2),\, 3/(3/2)\} = \min\{4,\,2\} = 2$ sulla riga $x_4$ $\implies$ $x_4$ esce. **Pivot** $a_{21} = \tfrac{3}{2}$.

Divido la riga $x_4$ per $3/2$; aggiorno le altre.

$$\Downarrow$$

$$\begin{array}{c|c|cccc}
 & b & x_1 & x_2 & x_3 & x_4 \\
\hline
z & 7 & 0 & 0 & \tfrac{4}{3} & \tfrac{1}{3} \\
\hline
x_2 & 1 & 0 & 1 & \tfrac{2}{3} & -\tfrac{1}{3} \\
x_1 & 2 & 1 & 0 & -\tfrac{1}{3} & \tfrac{2}{3} \\
\end{array}$$

**Ottimo** (tutti $\bar c_j \ge 0$). Soluzione: $x_1^* = 2,\ x_2^* = 1,\ x_3^* = x_4^* = 0$.

> [!warning] Lettura del valore ottimo (errore classico 2026)
> Nel tableau, in alto a destra leggo $7$. Ma quel valore è **$-z$**, non $z$! Il vero ottimo è
> $$z^* = -7$$
> Verifica diretta: $z^* = -2(2) - 3(1) = -7$ ✓

---

# Esercizio 4 — Caso illimitato

## Traccia
$$\begin{array}{rl}
\min & z = -x_1 - 2x_2 \\
\text{s.t.} & x_1 - x_2 \le 2 \\
& -x_1 + x_2 \le 1 \\
& x_1, x_2 \ge 0
\end{array}$$

Applicare il simplesso e riconoscere il caso speciale di **illimitatezza**.

## Svolgimento
La regione è **illimitata** ($x_1 + x_2$ può crescere indefinitamente lungo la direzione $(1,1)$); vediamo come il simplesso lo rivela.

**Forma standard** (slack $x_3, x_4$): $x_1 - x_2 + x_3 = 2$, $-x_1 + x_2 + x_4 = 1$. Base iniziale $\{x_3, x_4\}$:

$$\begin{array}{c|c|cccc}
 & b & x_1 & x_2 & x_3 & x_4 \\
\hline
z & 0 & -1 & -2 & 0 & 0 \\
\hline
x_3 & 2 & 1 & -1 & 1 & 0 \\
x_4 & 1 & -1 & 1 & 0 & 1 \\
\end{array}$$

### Iterazione 1
**Entrante:** $\bar c_2 = -2$ è il più negativo $\implies$ $x_2$ entra.
**Rapporti** ($\bar a_{i2} > 0$): solo la riga $x_4$ ha $\bar a_{22} = 1 > 0$. $\min\{1/1\} = 1$ $\implies$ $x_4$ esce. **Pivot** $a_{22} = 1$.

$$\Downarrow$$

$$\begin{array}{c|c|cccc}
 & b & x_1 & x_2 & x_3 & x_4 \\
\hline
z & 2 & -3 & 0 & 0 & 2 \\
\hline
x_3 & 3 & 0 & 0 & 1 & 1 \\
x_2 & 1 & -1 & 1 & 0 & 1 \\
\end{array}$$

### Iterazione 2 — STOP per illimitatezza
**Entrante:** $\bar c_1 = -3 < 0$ $\implies$ $x_1$ entrerebbe.
**Esamino la colonna $x_1$:**

| riga | $\bar a_{i1}$ |
|---|---|
| $x_3$ | $0$ |
| $x_2$ | $-1$ |

**Tutti gli $\bar a_{i1} \le 0$** $\implies$ non ho nessuna riga con $\bar a_{i1} > 0$ per il test del minimo rapporto.

> [!example] STOP — Problema ILLIMITATO inferiormente
> Quando la variabile entrante ha colonna intera $\le 0$, posso aumentare $x_1$ a piacere e $z$ decresce:
> $$z = 2 + (-3)\,x_1 \to -\infty \quad \text{per } x_1 \to +\infty$$

> [!warning] Criterio di illimitatezza (DA RICORDARE)
> 1. Esiste $\bar c_h < 0$ (problema migliorabile).
> 2. **Tutti** gli $\bar a_{ih} \le 0$ nella colonna $h$.
> 
> Se entrambe le condizioni valgono in una stessa colonna $\implies$ **problema illimitato**.

---

[[5 - Esercizi Dualità e Scarti Complementari|Prossimo Argomento]]
