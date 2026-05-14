---
tags:
  - ricerca-operativa
  - lezione
  - modellazione
slide: "m01.modPL.01.modelli.pdf"
---
## 1.1 Cos'è la Ricerca Operativa

La **Ricerca Operativa** (RO) è la disciplina che applica metodi matematici alla presa di decisioni *quantitative*: assegnare risorse limitate, organizzare turni, scegliere investimenti, dimensionare impianti, instradare trasporti. Il ponte tra il problema reale (in lingua italiana) e il calcolatore (in linguaggio matematico) si chiama **modello**.

> [!quote] Definizione — Modello di programmazione matematica
> Un modello di programmazione matematica descrive le caratteristiche della soluzione ottima di un problema di ottimizzazione tramite **relazioni matematiche**. Non specifica *come* calcolare la soluzione, ma *che cosa* deve soddisfare.

L'analogia con i linguaggi di programmazione: un modello è *dichiarativo* (come SQL — "cosa voglio"), non *procedurale* (come C — "come lo calcolo"). La parte procedurale (il *come*) è demandata a un **motore di ottimizzazione** generico, come il **Simplesso** o **AMPL**.

## 1.2 Elementi di un modello

Ogni modello matematico è composto da cinque ingredienti:

| Elemento | Significato | Esempio (problema del coltivatore) |
| :--- | :--- | :--- |
| **Insiemi** | Gli aggregati di entità del sistema | $L = \{\text{lattuga}\}$, $P = \{\text{patate}\}$ |
| **Parametri** | Dati noti del problema | resa lattuga $= 3000$ €/ettaro |
| **Variabili decisionali** | Le incognite su cui si agisce | $x_L$ = ettari di lattuga |
| **Vincoli** | Condizioni di ammissibilità | $x_L + x_P \le 12$ ettari |
| **Funzione Obiettivo (F.O.)** | Cosa massimizzare/minimizzare | $\max\ 3000 x_L + 5000 x_P$ |

> [!info] Nota terminologica
> I **parametri** sono *fissati* prima dell'ottimizzazione (input del problema). Le **variabili** sono *libere* e il modello ne sceglie il valore. Confondere le due cose è l'errore numero uno dei principianti.

## 1.3 Forma generale e classi di modelli

La forma generale di un problema di Programmazione Lineare è:

$$\begin{array}{rl}
\min\ (\max) & c_1 x_1 + c_2 x_2 + \dots + c_n x_n \quad (+\text{cost.}) \\
\text{s.t.} & a_{11} x_1 + \dots + a_{1n} x_n \,\{\le, =, \ge\}\, b_1 \\
& \vdots \\
& a_{m1} x_1 + \dots + a_{mn} x_n \,\{\le, =, \ge\}\, b_m \\
& x_j \in \mathbb{R}_+ \ \text{(oppure } \mathbb{Z}_+\text{)} \quad j = 1, \dots, n
\end{array}$$

In notazione compatta: $\min\ c^T x$ s.t. $Ax \,\{\le, =, \ge\}\, b$, $x \ge 0$.

A seconda del dominio delle variabili distinguiamo:

- **PL** (Programmazione Lineare): $x \in \mathbb{R}^n$ (variabili continue).
- **PLI** (PL Intera): $x \in \mathbb{Z}^n$ (tutte intere).
- **PLIM** (PL Intera Mista): alcune variabili reali, altre intere.
- Caso speciale: variabili **binarie** $x \in \{0,1\}$ (PLI 0-1) — modellano decisioni *sì/no*.

> [!warning] Attenzione: un modello PL deve essere LINEARE
> Le variabili possono essere solo **moltiplicate per costanti** e **sommate tra loro**. Sono vietati: prodotti tra variabili ($x_1 \cdot x_2$), divisioni per variabili ($1/x$), potenze ($x^2$), funzioni non lineari ($\sin x, \log x, |x|$ — quest'ultima si può linearizzare, [[1 - Modellazione Matematica#^44d55a|vedi 1.6]]).

## 1.4 Costruzione di un modello — esempio guida

Vediamo un esempio classico, passo dopo passo.

> [!example] Problema del coltivatore
> Un coltivatore ha 12 ettari, 70 kg di semi di lattuga, 18 t di tuberi, 160 m³ di fertilizzante. La resa è 3000 €/ettaro per la lattuga, 5000 €/ettaro per le patate. Consumo per ettaro: lattuga richiede 7 kg semi, 10 m³ fertilizzante; patate richiedono 3 t tuberi, 20 m³ fertilizzante. Quanto seminare di ciascuno per massimizzare il ricavo?

**Passo 1 — Variabili decisionali.** Le decisioni sono "quanti ettari a lattuga / patate":
$$x_L = \text{ettari di lattuga}, \quad x_P = \text{ettari di patate}$$

**Passo 2 — Funzione obiettivo.** Si vuole massimizzare il ricavo:
$$\max\ z = 3000\, x_L + 5000\, x_P$$

**Passo 3 — Vincoli.** Per ciascuna risorsa, "uso $\le$ disponibilità":
$$\begin{array}{ll}
x_L + x_P \le 12 & \text{(ettari di terreno)} \\
7 x_L \le 70 & \text{(semi di lattuga)} \\
3 x_P \le 18 & \text{(tuberi)} \\
10 x_L + 20 x_P \le 160 & \text{(fertilizzante)}
\end{array}$$

**Passo 4 — Dominio.** Non si possono coltivare ettari negativi e non c'è vincolo di interezza ("frazioni di ettaro" sono accettabili):
$$x_L, x_P \ge 0$$

**Modello finale:**

$$\begin{array}{rl}
\max & 3000 x_L + 5000 x_P \\
\text{s.t.} & x_L + x_P \le 12 \\
& 7 x_L \le 70 \\
& 3 x_P \le 18 \\
& 10 x_L + 20 x_P \le 160 \\
& x_L, x_P \ge 0
\end{array}$$

## 1.5 Schemi di modellazione ricorrenti

Molti problemi reali ricadono in **schemi tipici**. Riconoscerli accelera la modellazione.

### Schema 1 — Mix ottimo di produzione (massimizzazione del profitto)
Decidere quanto produrre di ogni bene rispettando le risorse:

$$\begin{array}{rl}
\max & \sum_{i \in I} P_i x_i \\
\text{s.t.} & \sum_{i \in I} A_{ij} x_i \le Q_j \quad \forall j \in J \\
& x_i \ge 0
\end{array}$$

dove $I$ = beni producibili, $J$ = risorse disponibili, $P_i$ = profitto unitario, $Q_j$ = disponibilità della risorsa $j$, $A_{ij}$ = quantità di risorsa $j$ usata per un'unità di bene $i$.

Esempi: problema del coltivatore, assemblaggio di telecomandi.

### Schema 2 — Copertura a costo minimo (minimizzazione del costo)
Decidere quanto acquistare di ogni risorsa per soddisfare le richieste:

$$\begin{array}{rl}
\min & \sum_{i \in I} C_i x_i \\
\text{s.t.} & \sum_{i \in I} A_{ij} x_i \ge D_j \quad \forall j \in J \\
& x_i \ge 0
\end{array}$$

Esempi: dieta economica, turni in ospedale, indagine di mercato, localizzazione di servizi.

### Schema 3 — Trasporto / flusso
Decidere quanto trasportare tra origini $i \in I$ e destinazioni $j \in J$ a costo minimo:

$$\begin{array}{rl}
\min & \sum_{i \in I} \sum_{j \in J} C_{ij} x_{ij} \\
\text{s.t.} & \sum_{j \in J} x_{ij} \le O_i \quad \forall i \in I \quad \text{(offerta)} \\
& \sum_{i \in I} x_{ij} \ge D_j \quad \forall j \in J \quad \text{(domanda)} \\
& x_{ij} \ge 0
\end{array}$$

> [!info] Suggerimento d'esame
> Davanti a un testo nuovo, chiediti: *"sto producendo per max profitto?" → schema 1. "Sto comprando per coprire domanda al min costo?" → schema 2. "Sto spostando cose tra sorgenti e destinazioni?" → schema 3.* Poi aggiungi i vincoli specifici del problema.

## 1.6 F.O. particolari: min-max, max-min, min-abs

^44d55a

Alcune funzioni obiettivo *sembrano* non lineari, ma si possono **linearizzare** introducendo una variabile ausiliaria. Sono casi tipici d'esame.

### Caso A — $\min\, \max\{e_1, e_2, \dots, e_n\}$

Si vuole minimizzare il *peggiore* (massimo) tra più valori. Introducendo $y$ "maggiore o uguale a tutti gli $e_i$" e minimizzando $y$, il minimo possibile di $y$ è proprio il massimo degli $e_i$:

$$\min \max\{e_1, \dots, e_n\} \quad\equiv\quad \begin{array}{rl}\min & y \\ \text{s.t.} & y \ge e_i \quad \forall i = 1, \dots, n \end{array}$$

### Caso B — $\max\, \min\{e_1, e_2, \dots, e_n\}$ (simmetrico)

$$\max \min\{e_1, \dots, e_n\} \quad\equiv\quad \begin{array}{rl}\max & y \\ \text{s.t.} & y \le e_i \quad \forall i \end{array}$$

### Caso C — $\min |e|$ (valore assoluto)

Si osserva che $|e| = \max\{e, -e\}$ — è un sotto-caso del min-max:

$$\min |e| \quad\equiv\quad \begin{array}{rl}\min & y \\ \text{s.t.} & y \ge e \\ & y \ge -e \end{array}$$

> [!example] Mini-esempio — penalità di anticipo/ritardo
> Un batch di lavoro deve essere consegnato al minuto $d$. La penalità è $|i + p - d|$ (anticipo o ritardo). Per linearizzare introduco $y \ge 0$ con $y \ge (i+p-d)$ e $y \ge -(i+p-d)$, poi $\min y$.

## 1.7 Vincoli logici e Big-M

Spesso i problemi PLI contengono **condizioni logiche**: "se attivo l'impianto A, devo coprire un costo fisso"; "i punti vendita di Roma e Milano sono incompatibili"; "almeno uno tra B e C va aperto". Per modellarle si introducono **variabili binarie** $y \in \{0, 1\}$ e si esprime la logica in modo lineare.

### 1.7.1 Costo fisso di attivazione

Un impianto $i$ ha:
- $x_i \ge 0$: quantità prodotta (variabile continua o intera);
- $y_i \in \{0,1\}$: $1$ se l'impianto è attivo, $0$ altrimenti;
- $C_i$: costo variabile per unità prodotta;
- $F_i$: costo fisso di attivazione;
- $U_i$: capacità massima.

**F.O.:** $\quad \min\ C_i x_i + F_i y_i$

**Vincolo di attivazione (Big-M):** $\quad x_i \le M \cdot y_i$, con $M$ "sufficientemente grande" (tipicamente $M = U_i$).

> [!quote] Logica del vincolo Big-M
> - Se $y_i = 0$: $x_i \le 0 \implies x_i = 0$ (non si produce se non si attiva).
> - Se $y_i = 1$: $x_i \le M$ (limite ininfluente, vincolano gli altri vincoli).

### 1.7.2 Tabella delle implicazioni logiche

Sia $y_1, y_2 \in \{0, 1\}$. Le relazioni logiche più comuni si esprimono così:

| Significato logico | Formula lineare |
| :--- | :--- |
| $y_1 = 1 \implies y_2 = 1$ ("se $A$ allora $B$") | $y_1 \le y_2$ |
| $y_1 \text{ e } y_2$ incompatibili (NAND) | $y_1 + y_2 \le 1$ |
| Almeno uno tra $y_1, y_2$ (OR) | $y_1 + y_2 \ge 1$ |
| Esattamente uno tra $y_1, y_2$ (XOR) | $y_1 + y_2 = 1$ |
| Entrambi (AND) | $y_1 + y_2 = 2$ (oppure $y_1 = 1$, $y_2 = 1$) |
| $y_1 = 1$ se e solo se $x_1 > 0$ | $x_1 \le M y_1$ (attivazione standard) |
| $y_1 = 1$ implica $x_1 \ge L$ (soglia minima) | $x_1 \ge L \cdot y_1$ |

### 1.7.3 Errori frequenti con le variabili logiche

> [!warning] Le tre trappole sui vincoli logici
> 1. **Prodotto di variabili.** Scrivere $x_i \cdot y_i$ in F.O. è non lineare. Sostituire $x_i \cdot y_i$ con un **vincolo di attivazione** $x_i \le M y_i$ — così $y_i$ entra solo *moltiplicata per costanti*.
> 2. **"Attivazione" della binaria.** Definire $y_i = 1 \text{ se } x_i > 0$ a parole **non basta**: serve un vincolo lineare ($x_i \le M y_i$) che leghi $x_i$ e $y_i$. Senza vincolo di attivazione, il modello può "barare" mettendo $y_i = 0$ anche con $x_i > 0$.
> 3. **Valori spuri.** Il vincolo $x_i \le M y_i$ non esclude la situazione "$y_i = 1$ con $x_i = 0$": ma essendo una situazione *peggiorativa* (paga il costo fisso $F_i$ senza produrre), il modello la scarterà da solo all'ottimo. Va bene così a meno che il problema richieda *esattamente* qualcosa, nel qual caso serve un vincolo aggiuntivo $x_i \ge 1 \cdot y_i$ (per variabili intere) o equivalente.

### 1.7.4 Scelta di $M$ — non esagerare

$M$ deve essere "sufficientemente grande" per non tagliare soluzioni ammissibili, ma **non troppo grande**: valori enormi rendono il rilassamento lineare debole e rallentano il Branch & Bound.

**Regola pratica:** prendere $M$ = capacità massima conosciuta della variabile (es. $U_i$ se è il tetto produttivo). Se non c'è un tetto naturale, dedurlo dagli altri vincoli (es. dalla disponibilità totale di risorse).

> [!example] Esempio Big-M con vincoli di attivazione/dimensione
> Localizzazione di ipermercati con dimensione massima $U_i$ e minima $L_i$ se aperti:
> $$\begin{array}{ll} x_i \le U_i \cdot y_i & \text{(massimo se aperto, 0 se chiuso)} \\ x_i \ge L_i \cdot y_i & \text{(minimo se aperto, 0 se chiuso)} \end{array}$$
> Se $y_i = 0$: $0 \le x_i \le 0 \implies x_i = 0$. Se $y_i = 1$: $L_i \le x_i \le U_i$.

## 1.8 Checklist per costruire un modello

Quando affronti un esercizio di modellazione, segui sempre questi passi nell'ordine:

1. **Leggi due volte** il testo e sottolinea: cosa si decide, cosa si massimizza/minimizza, quali sono i limiti.
2. **Definisci gli insiemi** (clienti, prodotti, periodi, ecc.) con nomi mnemonici (es. $I, J, T$).
3. **Definisci i parametri** copiandoli dal testo. Distingui chiaramente dati noti da incognite.
4. **Definisci le variabili decisionali**, una alla volta, **scrivendo l'unità di misura** ("$x_i$: kg di farina nella ricetta $i$"). Senza unità di misura saltano fuori errori dimensionali nei vincoli.
5. **Scrivi la F.O.** con un commento del tipo "(ricavo totale)" o "(costo della dieta)".
6. **Per ogni risorsa/condizione**, scrivi un vincolo separato con un commento descrittivo.
7. **Aggiungi i vincoli logici** (se servono variabili binarie, ricordati l'attivazione Big-M).
8. **Specifica il dominio** di ciascuna variabile: $\mathbb{R}_+$, $\mathbb{Z}_+$ o $\{0,1\}$.
9. **Rilettura finale:** ogni unità di misura torna? Ogni variabile binaria ha vincolo di attivazione? Il modello è davvero lineare?

> [!info] Riferimenti
> Dispensa `m01.modPL.01.modelli.pdf`, §1–7 (pp. 3–34). Per altri esempi svolti vedere anche `RO_Lez02_12_marzo_2024_Formulazione_Esercizi.pdf`.
