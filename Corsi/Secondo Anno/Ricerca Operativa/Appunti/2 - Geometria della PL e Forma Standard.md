---
tags:
  - ricerca-operativa
  - lezione
  - geometria
  - forma-standard
slide: "Teoria_Simplesso.pdf"
---

# 2. Geometria della PL e Forma Standard

> [!info] Cosa impariamo qui
> Per risolvere un PL non vogliamo "provare tutti i punti" della regione ammissibile (sono infiniti). Vogliamo individuare i **vertici**: l'ottimo, se esiste, sta sempre su uno di essi. Tradurremo poi i vertici in linguaggio algebrico, le **Soluzioni di Base Ammissibili** (SBA), perché il calcolatore lavora sulle equazioni.
## 2.1 La regione ammissibile: poliedri
Quando si scrive un PL, l'insieme di tutti i punti $x \in \mathbb{R}^n$ che soddisfano i vincoli si chiama **regione ammissibile** $P$.

> [!quote] Definizione — Poliedro
> Un insieme $P \subseteq \mathbb{R}^n$ è un **poliedro** se è ottenuto dall'intersezione di un numero finito di **semispazi chiusi** ($a^T x \le b$) e **iperpiani** ($a^T x = b$).

In $\mathbb{R}^2$ è un poligono; in $\mathbb{R}^3$ è un solido a facce piane; in dimensioni più alte è la generalizzazione naturale.

Un PL si scrive in forma compatta:
$$\min\ c^T x \quad \text{s.t.} \quad x \in P$$
## 2.2 I tre casi possibili per un problema di PL
Ogni problema di PL ricade in **uno e uno solo** dei seguenti tre casi:

| Caso | Significato | Convenzione |
| :--- | :--- | :--- |
| **Ammette ottimo** | Esiste $x^* \in P$ tale che $c^T x^* \le c^T x$ per ogni $x \in P$ | $z^*$ valore finito |
| **Inammissibile** | La regione ammissibile è vuota ($P = \emptyset$) | $z^* = +\infty$ |
| **Illimitato inferiormente** | Per ogni $x \in P$ esiste $\hat{x} \in P$ con $c^T \hat{x} < c^T x$ | $z^* = -\infty$ |

> [!warning] Illimitato $\neq$ poliedro illimitato
> Un poliedro $P$ **illimitato** è condizione *necessaria* ma *non sufficiente* per avere problema illimitato. Esempio: nello stesso poliedro illimitato $\{x_1, x_2 \ge 0\}$, $\min\ x_1 - 2x_2$ è illimitato, ma $\min\ 2x_1 + 3x_2$ ha ottimo finito $z^* = 0$ in $x = (0,0)$. Dipende dalla direzione del gradiente $c$.
## 2.3 Vertici di un poliedro
Intuitivamente: in $\mathbb{R}^2$ un vertice è uno "spigolo" del poligono. Definirlo in modo rigoroso richiede il concetto di **combinazione convessa**.

> [!quote] Definizione — Combinazione convessa
> Dati $x, y \in \mathbb{R}^n$, un punto $z$ è **combinazione convessa** di $x$ e $y$ se $z = \lambda x + (1-\lambda) y$ con $\lambda \in [0, 1]$. È **stretta** se $\lambda \in (0, 1)$ (estremi $x, y$ esclusi).

Geometricamente: le combinazioni convesse di $x$ e $y$ formano il segmento che li unisce.

> [!quote] Definizione — Vertice (estremo) di un poliedro
> Un punto $v \in P$ è **vertice** se **non** può essere espresso come combinazione convessa stretta di due punti distinti di $P$. Cioè: $\not\exists x, y \in P, \lambda \in (0,1) : x \neq y,\ v = \lambda x + (1-\lambda) y$.

In parole: un vertice è un punto del poliedro che non sta "in mezzo" a nessun segmento contenuto in $P$.

> [!example] Esempio in $\mathbb{R}^2$
> Nel triangolo di vertici $A, B, C$: il centro del triangolo *non* è vertice (è combinazione convessa di tutti e tre); il punto medio del lato $AB$ *non* è vertice (combinazione convessa di $A$ e $B$); $A$, $B$, $C$ *sono* vertici (nessun altro segmento li contiene strettamente).

## 2.4 Teoremi fondamentali

> [!quote] Teorema 1 — Rappresentazione (Minkowski-Weyl, caso limitato)
> Sia $P$ un poliedro limitato e $v^1, \dots, v^k$ i suoi vertici. Ogni punto $x \in P$ si può scrivere come combinazione convessa dei vertici:
> $$x = \sum_{i=1}^k \lambda_i v^i, \quad \lambda_i \ge 0, \quad \sum_{i=1}^k \lambda_i = 1$$

> [!quote] Teorema 2 — Esistenza vertice ottimo
> Se $P$ è non vuoto e limitato, il problema $\min\{c^T x : x \in P\}$ ammette soluzione ottima ed esiste **almeno un vertice ottimo**.

**Idea della dimostrazione** (importante!): siano $v^1, \dots, v^k$ i vertici e $v^*$ quello in cui $c^T v$ è minimo. Per il Teorema 1, ogni $x \in P$ è $\sum \lambda_i v^i$, quindi:
$$c^T x = c^T \sum_i \lambda_i v^i = \sum_i \lambda_i \underbrace{c^T v^i}_{\ge\ c^T v^*} \ge c^T v^* \sum_i \lambda_i = c^T v^*$$
Quindi $v^*$ è ottimo.

> [!info] Conseguenza pratica
> Cercare l'ottimo **solo tra i vertici** (sono in numero finito) anziché tra tutti i punti di $P$ (sono infiniti). Il Simplesso fa esattamente questo: salta da un vertice all'adiacente migliorando $z$.

## 2.5 Forma Standard

Per studiare i vertici algebricamente serve uniformare la struttura del problema. La **forma standard** è:

$$\boxed{\quad \min\ c^T x \quad \text{s.t.} \quad Ax = b,\ \ b \ge 0,\ \ x \ge 0 \quad}$$

con $A \in \mathbb{R}^{m \times n}$, $n > m$ e $\rho(A) = m$ (rango massimo).

**Regole di conversione** — un qualsiasi PL si riconduce alla forma standard tramite:
1. **F.O. di massimizzazione** $\to$ minimizzazione: $\max\ c^T x \equiv \min\ -c^T x$. Le costanti additive si trascurano (non cambiano la posizione dell'ottimo); le moltiplicative positive si possono trascurare (scala $z$, ma non $x^*$).
2. **Vincolo $\le$** $\to$ uguaglianza tramite variabile di **slack** (scarto) non negativa:
   $$a^T x \le b \quad \Longleftrightarrow \quad a^T x + s = b,\ s \ge 0$$

3. **Vincolo $\ge$** $\to$ uguaglianza tramite variabile di **surplus** (eccedenza) non negativa:
   $$a^T x \ge b \quad \Longleftrightarrow \quad a^T x - s = b,\ s \ge 0$$

4. **RHS negativo** ($b_i < 0$): moltiplicare l'intero vincolo per $-1$ (cambiando il verso della disuguaglianza, se presente). Esempio:
   $$x_1 + x_2 \le -2 \quad \Longleftrightarrow \quad -x_1 - x_2 \ge 2$$

5. **Variabile libera di segno** ($x \in \mathbb{R}$): sostituirla con due variabili non negative $x = x^+ - x^-$, con $x^+, x^- \ge 0$.

6. **Variabile $x \le 0$**: sostituirla con $\hat{x} = -x$, con $\hat{x} \ge 0$.

> [!warning] Ordine corretto delle conversioni
> 1. Prima sistemo il **segno del RHS** (regola 4): moltiplico per $-1$ se serve, e la disuguaglianza si **gira**.
> 2. Poi aggiungo slack/surplus (regole 2, 3).
> 3. Infine sostituisco le variabili libere o negative (regole 5, 6).
> Saltare l'ordine porta a errori sistematici (es. slack su un vincolo che ha cambiato verso).

> [!example] Esempio di forma standard
> Da $\max\ 13x_1 + 10x_2$ s.t. $3x_1 + 4x_2 \le 24$, $x_1 + 4x_2 \le 20$, $3x_1 + 2x_2 \le 18$, $x_{1,2} \ge 0$, si ottiene:
> $$\min\ -13x_1 - 10x_2 \quad \text{s.t.}\quad \begin{cases} 3x_1 + 4x_2 + s_1 = 24 \\ x_1 + 4x_2 + s_2 = 20 \\ 3x_1 + 2x_2 + s_3 = 18 \\ x_1, x_2, s_1, s_2, s_3 \ge 0 \end{cases}$$

## 2.6 Caratterizzazione algebrica dei vertici: Soluzioni di Base

In forma standard si ha $Ax = b$ con $A \in \mathbb{R}^{m \times n}$, $n > m$, $\rho(A) = m$. Il sistema ha $\infty^{n-m}$ soluzioni (Rouché-Capelli). Tra queste, alcune speciali corrispondono ai vertici.

### Idea: fissiamo $n-m$ variabili a $0$

Se da $n$ variabili ne mettiamo $n - m$ a zero, restano $m$ incognite e $m$ equazioni $\to$ sistema (in generale) determinato. Geometricamente: imporre $x_j = 0$ significa saturare il vincolo "non-negatività" della variabile $j$. Saturare abbastanza vincoli al punto giusto = vertice.

### Definizioni formali

> [!quote] Definizione — Base
> Una **base** di $A$ è una sottomatrice $B \in \mathbb{R}^{m \times m}$ ottenuta scegliendo $m$ colonne **linearmente indipendenti** di $A$. Equivalentemente: $B$ quadrata e invertibile ($\det B \ne 0$).

Le restanti $n - m$ colonne formano la **fuori-base** $F$. Riordinando le variabili:
$$A = [B \mid F], \quad x = \begin{bmatrix} x_B \\ x_F \end{bmatrix}, \quad Ax = b \implies B x_B + F x_F = b$$

> [!quote] Definizione — Soluzione di Base (SB)
> Ponendo $x_F = 0$ e risolvendo $B x_B = b$:
> $$x_B = B^{-1} b,\quad x_F = 0$$
> Il vettore $x$ così ottenuto si dice **Soluzione di Base** associata a $B$.

> [!quote] Definizione — Soluzione di Base Ammissibile (SBA / BFS)
> Una SB è **ammissibile** se $x_B = B^{-1} b \ge 0$ (tutte le variabili di base sono non negative). Notazione comune: **SBA** (italiano) o **BFS** (inglese, Basic Feasible Solution).

> [!quote] Definizione — Soluzione di Base Degenere
> Una SB si dice **degenere** se almeno una variabile *in base* assume il valore $0$ (cioè $x_B$ ha almeno una componente nulla).

### Il teorema chiave: vertice ↔ SBA

> [!quote] Teorema 3 — Corrispondenza vertici / SBA
> Sia $P = \{x \ge 0 : Ax = b\}$ il poliedro associato a un PL in forma standard. Un punto $\bar{x} \in P$ è **vertice** di $P$ se e solo se è **Soluzione di Base Ammissibile** del sistema $Ax = b$.

**Significato pratico**: invece di cercare vertici geometricamente (irrealizzabile in alta dimensione), si cercano SBA del sistema algebrico — il che è un problema *meccanico* di scelta di colonne di $A$.

### Numero di SBA (limite superiore)

Le possibili scelte di $m$ colonne tra $n$ sono al più $\binom{n}{m} = \frac{n!}{m!(n-m)!}$. Quindi:
$$\#\{\text{vertici di } P\} \le \binom{n}{m}$$

> [!info] Perché il Simplesso non è "provarle tutte"
> $\binom{n}{m}$ cresce esponenzialmente: per $n = 50, m = 30$ già si superano $10^{14}$ basi. Il Simplesso evita l'enumerazione esaustiva: parte da una SBA e si sposta solo verso SBA adiacenti che migliorano $z$.

## 2.7 Esempio guida: il problema dei profumi

Forma standard del problema dei profumi (vedi Esercizi/Simplesso):

$$\begin{array}{rl}
\min & -13 x_1 - 10 x_2 \\
\text{s.t.} & 3 x_1 + 4 x_2 + s_1 = 24 \\
& x_1 + 4 x_2 + s_2 = 20 \\
& 3 x_1 + 2 x_2 + s_3 = 18 \\
& x_1, x_2, s_1, s_2, s_3 \ge 0
\end{array}$$

Qui $n = 5$, $m = 3$. La matrice $A$ ha 3 righe e 5 colonne. Una base = scelta di 3 colonne lin. indipendenti.

**Scelta 1**: base $B = $ colonne di $\{x_1, x_2, s_3\}$.
$$B = \begin{bmatrix} 3 & 4 & 0 \\ 1 & 4 & 0 \\ 3 & 2 & 1 \end{bmatrix}, \quad B^{-1} b = \begin{bmatrix} 2 \\ 9/2 \\ 3 \end{bmatrix} \ge 0 \implies \text{SBA}$$
Corrisponde al vertice $B = (2,\ 9/2)$ con $s_1 = s_2 = 0$ (vincoli (e1) ed (e2) saturi) e $s_3 = 3$.

**Scelta 2**: base con colonne di $\{x_1, s_2, s_3\}$.
Risolvendo si ottiene $s_2 < 0$ $\implies$ SB **non ammissibile** (corrisponde geometricamente all'intersezione di rette fuori dalla regione ammissibile).

> [!info] Lettura geometrica
> Mettere $x_F = 0$ significa **saturare** i corrispondenti vincoli (di non-negatività o di uguaglianza dopo slack). Una SBA = saturazione di $n - m$ vincoli che porta a un punto del poliedro = vertice.

## 2.8 Riepilogo concettuale

Lo schema mentale da fissare prima del Simplesso:

```
   Problema PL
      ↓
   Forma standard:  min c^T x  s.t.  Ax = b, x ≥ 0
      ↓
   Vertici di P  ⟺  Soluzioni di Base Ammissibili (SBA)
      ↓
   Ottimo (se esiste) sta su una SBA
      ↓
   Algoritmo: saltare da SBA a SBA adiacente migliorando z
      ↓
   = Metodo del Simplesso (cap. 3)
```

> [!info] Riferimenti
> Dispensa `Teoria_Simplesso.pdf`, §1–3.6 (pp. 4–16). Slide introduttiva `Introduzione_Programmazione_Linear.pdf` per le tre tipologie di soluzione (ottimo, inammissibile, illimitato).
