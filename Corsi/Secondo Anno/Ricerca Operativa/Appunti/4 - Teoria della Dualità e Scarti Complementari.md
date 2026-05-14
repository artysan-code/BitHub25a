---
tags:
  - ricerca-operativa
  - lezione
  - dualità
slide: "Lezioni_Teoria_Dualita.pdf"
---

# 4. Teoria della Dualità e Scarti Complementari

> [!info] Cosa impariamo qui
> Ad ogni problema di PL ne è associato un altro, detto **duale**. Risolvere uno equivale a risolvere l'altro: gli ottimi sono lo stesso numero. Soprattutto: il duale fornisce uno strumento elegante per **certificare l'ottimalità** di una soluzione senza ri-eseguire il Simplesso, attraverso le **Condizioni di Ortogonalità** (alias Scarti Complementari).

## 4.1 Motivazione: stimare $z^*$ senza risolvere

Sia $(P)$ un PL di minimo in forma standard:
$$\min\ z = c^T x \quad \text{s.t.} \quad Ax = b,\ x \ge 0$$

Vogliamo stimare $z^*$ senza risolverlo davvero.

**Stima per eccesso** (semplice): basta valutare $\bar{z} = c^T \bar{x}$ su una qualsiasi soluzione ammissibile $\bar{x}$: $z^* \le \bar{z}$.

**Stima per difetto** (complicato): occorre dimostrare che *nessuna* soluzione ammissibile ha valore inferiore. Per questo serve il duale.

## 4.2 Costruzione del Duale (caso forma standard)

> [!quote] Teorema 7.1 (Dualità Debole) — forma standard
> Dato $(P) = \min\{c^T x : Ax = b, x \ge 0\}$, **ogni** soluzione ammissibile $\bar{x}$ di $(P)$ soddisfa:
> $$c^T \bar{x} \ge b^T \bar{y}$$
> dove $\bar{y}$ è **qualsiasi** soluzione ammissibile del **problema duale** $(D)$:
> $$\max\ \omega = b^T y \quad \text{s.t.} \quad A^T y \le c$$

**Dimostrazione** (semplice ma utile da memorizzare):
$\bar{y}$ ammissibile per $(D)$ $\implies A^T \bar{y} \le c \iff c^T \ge \bar{y}^T A$.
Per $\bar{x}$ ammissibile per $(P)$: $A \bar{x} = b$, $\bar{x} \ge 0$.
$$c^T \bar{x} \ge (\bar{y}^T A) \bar{x} = \bar{y}^T (A \bar{x}) = \bar{y}^T b = b^T \bar{y}$$

> [!info] Significato pratico
> Una qualsiasi soluzione ammissibile del duale dà una **limitazione inferiore** ($b^T \bar{y}$) per il valore ottimo del primale. Una qualsiasi soluzione ammissibile del primale dà una **limitazione superiore** ($c^T \bar{x}$). Quando coincidono, sono entrambe ottime (vedi §4.4).

## 4.3 Regole di Tucker — Costruire il Duale di un PL qualsiasi

Spesso il primale non è in forma standard. Si applicano le **regole di Tucker** (derivabili passando per la forma standard, ma è più rapido memorizzarle a tabella).

**Caso PRIMALE di MIN:**

| Primale ($\min$) | Duale ($\max$) |
| :--- | :--- |
| $i$-esimo vincolo $\ge$ | $y_i \ge 0$ |
| $i$-esimo vincolo $\le$ | $y_i \le 0$ |
| $i$-esimo vincolo $=$ | $y_i$ libera di segno |
| $x_j \ge 0$ | $j$-esimo vincolo $\le$ |
| $x_j \le 0$ | $j$-esimo vincolo $\ge$ |
| $x_j$ libera di segno | $j$-esimo vincolo $=$ |

**Caso PRIMALE di MAX:** specularmente — invertire ogni "$\ge$" con "$\le$" sulle variabili duali, e ogni "$\le$" con "$\ge$" sui vincoli duali.

> [!info] Regola mnemonica
> - **Variabili** del primale ↔ **vincoli** del duale (e viceversa).
> - **Costi** $c$ del primale → **termini noti** del duale; **termini noti** $b$ del primale → **costi** del duale.
> - La matrice $A$ si **traspone**: una colonna primale diventa una riga duale.

> [!warning] "Libera di segno" ≠ "uguale a zero"
> Una variabile libera ha **valore qualunque** in $\mathbb{R}$, non zero. Il suo vincolo duale corrispondente è un'**uguaglianza** ($=$), non l'assenza del vincolo.

> [!example] Esempio numerico — duale di un MIN forma standard
> $$\begin{array}{rl} \min & 5x_1 + 2x_2 - 3x_3 + 4x_4 \\ \text{s.t.} & x_1 + 2x_2 - 3x_3 - 6x_4 = 16 \\ & x_1 - x_2 + 4x_3 + 12x_4 = 18 \\ & x_{1,2,3,4} \ge 0 \end{array}$$
> Duale (vincoli $=$ → $y_i$ libere; $x_j \ge 0$ → vincoli $\le c_j$):
> $$\begin{array}{rl} \max & 16 y_1 + 18 y_2 \\ \text{s.t.} & y_1 + y_2 \le 5 \\ & 2y_1 - y_2 \le 2 \\ & -3 y_1 + 4 y_2 \le -3 \\ & -6 y_1 + 12 y_2 \le 4 \\ & y_1, y_2 \text{ libere} \end{array}$$

## 4.4 Dualità Forte e i quattro casi

> [!quote] Teorema 7.4 (Dualità Forte)
> $\bar{x}$ ammissibile per $(P)$ è **ottima** se e solo se esiste $\bar{y}$ ammissibile per $(D)$ tale che $c^T \bar{x} = b^T \bar{y}$. In tal caso, $\bar{y}$ è ottima per $(D)$ e $z^* = \omega^*$.

In altre parole: se primale e duale ammettono entrambi ottimo finito, i due valori **coincidono**.

> [!quote] Teorema 7.5 — Quadro completo dei casi possibili
> Per la coppia primale-duale vale **esattamente una** delle seguenti:
> 1. **Entrambi ottimi finiti** con $z^* = \omega^*$;
> 2. **Primale illimitato** inferiormente $\implies$ Duale **inammissibile**;
> 3. **Duale illimitato** superiormente $\implies$ Primale **inammissibile**;
> 4. **Entrambi inammissibili**.

> [!warning] L'inammissibilità di uno NON implica l'illimitatezza dell'altro
> Il caso 4 esiste davvero: si possono costruire coppie primale-duale entrambe inammissibili (basta un sistema $Ax = b$ incompatibile). Quindi *"primale inammissibile ⟹ duale illimitato"* è FALSO in generale.

> [!example] Schema riassuntivo
> ```
>                Duale: ottimo  illimitato  inammissibile
> Primale: ottimo       ✓        ✗          ✗
>          illimitato   ✗        ✗          ✓
>          inammissibile ✗       ✓          ✓
> ```

## 4.5 Condizioni di Ortogonalità (Scarti Complementari)

Il vero strumento operativo nei compiti d'esame.

### 4.5.1 Enunciato (caso forma standard, primale di MIN)

> [!quote] Teorema 7.6 — Condizioni di Ortogonalità
> Sia $\bar{x}$ ammissibile per $(P) = \min\{c^T x : Ax = b, x \ge 0\}$ e $\bar{y}$ ammissibile per $(D) = \max\{b^T y : A^T y \le c\}$.
> $\bar{x}, \bar{y}$ sono **ottime per i rispettivi problemi** se e solo se:
> $$\boxed{\quad (c_j - \bar{y}^T A_j) \cdot \bar{x}_j = 0, \quad \forall j = 1, \dots, n \quad}$$

In altre parole, per ogni variabile $\bar{x}_j$:
- **o** $\bar{x}_j = 0$, **o** il corrispondente $j$-esimo vincolo duale è soddisfatto ad **uguaglianza**.
Almeno una delle due condizioni vale (entrambe ammesse).

### 4.5.2 Forma "simmetrica" (più pratica negli esercizi)

Per un primale di $\min$ con vincoli $\ge$ (forma simmetrica, non standard):
$$\min\ c^T x \quad \text{s.t.} \quad Ax \ge b,\ x \ge 0$$
con duale
$$\max\ b^T y \quad \text{s.t.} \quad A^T y \le c,\ y \ge 0$$

> [!quote] Teorema 7.7 — Ortogonalità (forma simmetrica)
> $\bar{x}, \bar{y}$ ottime se e solo se valgono entrambe:
> 1. $(c_j - \sum_i a_{ij} \bar{y}_i) \cdot \bar{x}_j = 0 \quad \forall j$ — "scarto sul vincolo duale $\times$ variabile primale = 0"
> 2. $\bar{y}_i \cdot (\sum_j a_{ij} \bar{x}_j - b_i) = 0 \quad \forall i$ — "variabile duale $\times$ scarto sul vincolo primale = 0"

### 4.5.3 Lettura operativa delle CSC

| Situazione su $\bar{x}_j$, vincolo duale | Conseguenza |
| :--- | :--- |
| $\bar{x}_j > 0$ | Il $j$-esimo vincolo duale è **saturo** ($=$) |
| Vincolo duale **non saturo** (scarto $>0$) | $\bar{x}_j = 0$ |

| Situazione su vincolo primale, $\bar{y}_i$ | Conseguenza |
| :--- | :--- |
| Vincolo primale **non saturo** (slack $>0$) | $\bar{y}_i = 0$ |
| $\bar{y}_i > 0$ | Il vincolo primale $i$ è **saturo** ($=$) |

> [!info] Intuizione economica
> Pensa al primale come "uso risorse per produrre" e al duale come "prezzo ombra delle risorse". Se al vincolo $i$ avanza risorsa (slack $>0$), il suo prezzo è $0$ ($\bar{y}_i = 0$). Se una variabile primale è in produzione ($\bar{x}_j > 0$), il suo "costo aggregato" pareggia esattamente il margine ($j$-esimo vincolo duale saturo).

## 4.6 Uso pratico nei problemi d'esame

### 4.6.1 Verificare l'ottimalità di una $\bar{x}$ data

**Schema operativo:**
1. **Ammissibilità primale**: sostituisci $\bar{x}$ nei vincoli di $(P)$, controlla che siano rispettati.
2. **Costruisci il duale** $(D)$ con la tabella di Tucker.
3. **Imposta le CSC**:
   - per ogni $\bar{x}_j > 0$, scrivi *come equazione* il corrispondente vincolo duale (= invece di ≤/≥);
   - per ogni vincolo primale **non saturo**, imponi $\bar{y}_i = 0$.
4. **Risolvi il sistema** ottenuto per le $\bar{y}_i$.
5. **Verifica ammissibilità duale**: la $\bar{y}$ trovata deve rispettare *tutti* i vincoli duali residui (compresi i segni).
   - **Sì** → $\bar{x}$ è ottima (e $\bar{y}$ è ottima per il duale).
   - **No** (es. una $\bar{y}_i$ doveva essere $\ge 0$ ma è negativa) → $\bar{x}$ **non** è ottima.

> [!example] Esempio applicativo
> Vedi [[5 - Esercizi Dualità e Scarti Complementari|Esempio 4 degli Esercizi]] dove si verifica $\bar{x} = (12, 9)$ per il problema dei profumi e si ricava $\bar{y} = (60, 40, 0)$ con $z^* = w^* = 2460$.

### 4.6.2 Trovare l'ottimo del duale conoscendo quello del primale (e viceversa)

Se $x^*$ è nota e non degenere, si usa il sistema $A_B^T y = c_B$ (dove $B$ è l'insieme degli indici delle variabili in base all'ottimo): è un sistema $m \times m$ con $A_B$ invertibile, quindi $y^* = (A_B^T)^{-1} c_B$, ovvero $y^{*T} = c_B^T A_B^{-1}$.

**Equivalentemente** con le CSC: imponi all'uguaglianza i vincoli duali corrispondenti alle $x_j^* > 0$ e ricavi le $y_i^*$.

### 4.6.3 Soluzione "complementare" e degenerazione

> [!warning] Soluzione duale unica solo se primale non degenere
> Se la SBA ottima primale è **degenere**, esistono *più* soluzioni duali ammissibili che soddisfano le CSC: il duale ha allora *infinite* soluzioni ottime (e viceversa). Si parametrizza con $y_1 = k$ e si trova l'intervallo di $k$ ammissibile.

## 4.7 Riepilogo strategico

Quando in un esercizio compare la dualità, riconosci il tipo di richiesta:

| Richiesta | Strumento |
| :--- | :--- |
| "Scrivere il duale di…" | Tabella di Tucker (§4.3) |
| "Stimare $z^*$ senza risolvere" | Dualità debole, $b^T \bar{y} \le z^* \le c^T \bar{x}$ |
| "Verificare se $\bar{x}$ è ottima" | Scarti complementari (§4.5–4.6) |
| "Calcolare l'ottimo del duale data $x^*$" | $y^{*T} = c_B^T A_B^{-1}$ o sistema CSC |
| "Se il primale è illimitato, cosa accade al duale?" | Teorema 7.5 (4 casi) |

> [!info] Riferimenti
> Dispensa `Lezioni_Teoria_Dualita.pdf` (87 pp.): §7.1 dualità debole, §7.4 dualità forte, §7.5 casi, §7.6 ortogonalità forma standard, §7.7 ortogonalità forma simmetrica. Per esempi numerici vedere `Esercizio_Algoritmo_Primale_Duale_Svolto_(1).pdf` e `_(2).pdf`.
