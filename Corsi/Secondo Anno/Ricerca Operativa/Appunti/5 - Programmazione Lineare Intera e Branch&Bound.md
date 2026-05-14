---
tags:
  - ricerca-operativa
  - lezione
  - PLI
  - branch-and-bound
slide: "PLI_Part02.pdf"
---

# 5. Programmazione Lineare Intera e Branch & Bound

> [!info] Cosa impariamo qui
> La PLI aggiunge il vincolo "$x \in \mathbb{Z}$" alla PL. La regione ammissibile non è più un poliedro continuo ma un *reticolo* di punti interi: non si può più applicare direttamente il Simplesso. Vediamo come affrontarla con **rilassamenti** (per stimare l'ottimo) e con il **Branch & Bound** (per trovarlo davvero).

## 5.1 Cos'è la Programmazione Lineare Intera

> [!quote] Definizione — PLI
> Un problema di **Programmazione Lineare Intera** (PLI) è un PL con il vincolo aggiuntivo che alcune (PLI Mista, PLIM) o tutte (PLI pura) le variabili siano intere:
> $$\begin{array}{rl} \min & c^T x \\ \text{s.t.} & A x \le b \\ & x \in \mathbb{Z}^n_+ \quad (\text{oppure } x \in \{0,1\}^n) \end{array}$$

I problemi PLI sono ovunque: localizzazione di impianti (quanti aprire?), turni di personale (quanti operai?), portafoglio di investimenti (quale combinazione di titoli?), pianificazione lotti di produzione, problema dello zaino (knapsack), set covering, ecc.

> [!warning] La PLI non è "PL con arrotondamento"
> Una tentazione naïve è risolvere il PL rilassato e poi arrotondare. **NON funziona** in generale: l'arrotondamento può violare i vincoli o portare lontano dall'ottimo. L'ottimo intero può essere *significativamente diverso* da quello frazionario, e in casi rari l'arrotondamento può portare a soluzioni inammissibili.

## 5.2 Geometria della PLI

Tre regioni ammissibili da distinguere:

1. **Politopo esterno**: regione ammissibile del **rilassamento lineare** (PL ottenuta ignorando $x \in \mathbb{Z}$). È un poliedro continuo.
2. **Punti interi ammissibili**: reticolo (insieme finito o numerabile di punti) interno al politopo esterno.
3. **Guscio convesso** (convex hull) dei punti interi ammissibili: è di nuovo un poliedro, ma più piccolo del politopo esterno.

> [!quote] Proprietà fondamentale
> Se si potesse lavorare direttamente sul **guscio convesso**, basterebbe il Simplesso: i suoi vertici sono interi e l'ottimo PLI si troverebbe in uno di essi. Purtroppo, costruire il guscio convesso è *generalmente più difficile* del problema originale (può richiedere infiniti vincoli).

## 5.3 Rilassamenti e Bound

Per non costruire il guscio convesso, si calcolano **stime** (bound) dell'ottimo $z^*$ usando problemi più facili.

### 5.3.1 Lower Bound (per problema di MIN)

Un **lower bound** $LB \le z^*$ si può ottenere in vari modi:

- **a) Rilassamento Lineare** (il più usato): elimino il vincolo di interezza e risolvo il PL ottenuto col Simplesso. Il valore $z_{RL}$ è un lower bound (perché la regione ammissibile è più grande $\implies$ il minimo può solo scendere).
- **b) Rilassamento per eliminazione**: tolgo dei vincoli "scomodi" (side constraints) e ottengo un PLI più semplice (es. con matrice TUM).
- **c) Rilassamento lagrangiano**: come (b), ma i vincoli rimossi vengono "penalizzati" e portati nella F.O. con dei moltiplicatori.
- **d) Tagli (cutting planes)**: aggiungo vincoli che tagliano via parti del politopo esterno **senza eliminare punti interi ammissibili**. Si ottiene un bound più stretto.
- **e) Rilassamento surrogato**: combino linearmente più vincoli in uno solo (es. trasformando in un problema di Knapsack).

### 5.3.2 Upper Bound (per problema di MIN)

Un **upper bound** $UB \ge z^*$ si ottiene **valutando una qualsiasi soluzione ammissibile intera** (anche euristica). Banalmente: $UB = +\infty$ se non si ha nulla, oppure $UB = c^T \bar{x}$ con $\bar{x}$ ammissibile intera.

> [!info] Logica dei bound in una minimizzazione
> $LB \le z^* \le UB$: l'ottimo "vero" sta in mezzo. Più i bound sono vicini, meglio è. Se mai $LB = UB$, allora il valore stimato è esattamente $z^*$.

> [!warning] In un problema di MAX i ruoli si invertono
> Per la **massimizzazione**: il rilassamento lineare dà un **upper bound** (la regione più grande spinge $z$ in alto); una soluzione intera ammissibile dà un **lower bound** (è almeno raggiungibile).

## 5.4 Matrici Totalmente Unimodulari (TUM)

C'è una classe di PLI per cui il rilassamento lineare dà **direttamente l'ottimo intero**, senza B&B.

> [!quote] Definizione — TUM
> Una matrice $A$ è **Totalmente Unimodulare** se ogni sua sottomatrice quadrata non singolare ha determinante $\pm 1$ (oppure $0$).

> [!quote] Teorema TUM
> Se $A$ è TUM e $b$ è intero, allora **tutti i vertici** del poliedro $\{x : Ax = b, x \ge 0\}$ sono a coordinate intere. Quindi il rilassamento lineare risolto col Simplesso fornisce direttamente l'ottimo PLI.

**Riconoscere matrici TUM** (criterio sufficiente di Hoffman-Kruskal):
- $A$ a coefficienti in $\{0, +1, -1\}$;
- Ogni colonna ha **al massimo 2 elementi non nulli**;
- L'insieme delle righe si può partizionare in $I_1 \cup I_2$ disgiunti tali che:
  - colonne con due elementi dello **stesso segno** $\to$ righe in insiemi **diversi**;
  - colonne con due elementi di **segno opposto** $\to$ righe nello **stesso** insieme.

**Esempi notevoli di problemi con matrice TUM:**
- Problema dei **trasporti**;
- Problema dell'**assegnamento**;
- Problema del **flusso di costo minimo** su rete;
- Problema dello **shortest path** (cammino minimo);
- Problema dello **spanning tree**.

In questi casi: dimentica il B&B, risolvi col Simplesso e basta.

## 5.5 Il Metodo del Branch & Bound

Per la PLI generale, l'algoritmo principe è il **Branch & Bound** (B&B): un'enumerazione *implicita* dei punti interi, che usa i bound per **scartare interi rami** dell'albero senza esplorarli.

### 5.5.1 Idea generale

- **Branch** (Ramificazione): partizionare il problema $P$ in sottoproblemi $P_1, P_2, \dots$ più piccoli.
- **Bound** (Stima): calcolare un lower bound per ciascun sottoproblema.
- **Pruning** (Taglio): se il LB di un sottoproblema è $\ge$ del miglior UB intero trovato finora, allora **nessuna** soluzione intera in quel sottoproblema può essere migliore $\implies$ scarto il ramo.

### 5.5.2 Branch corretto: regole

I sottoproblemi $P_1, \dots, P_q$ generati da $P$ devono soddisfare:
1. **Esaustivi**: $\Omega(P_1) \cup \dots \cup \Omega(P_q) = \Omega(P)$ — non perdere soluzioni.
2. **Disgiunti**: $\Omega(P_i) \cap \Omega(P_j) = \emptyset$ per $i \ne j$ — non duplicare.

**Regola standard** per problemi PL-rilassati che danno valori frazionari: scegliere una variabile $x_h$ con valore $\bar{x}_h$ frazionario all'ottimo del rilassamento (es. $\bar{x}_h = 3.4$) e creare due figli:
- **Figlio sinistro**: aggiungo $x_h \le \lfloor \bar{x}_h \rfloor$ (es. $x_h \le 3$);
- **Figlio destro**: aggiungo $x_h \ge \lceil \bar{x}_h \rceil$ (es. $x_h \ge 4$).

> [!info] Perché questa regola garantisce esaustivi e disgiunti
> Un intero non può valere strettamente $3 < x_h < 4$, quindi i due rami coprono *tutti* gli interi possibili senza sovrapporsi. Il valore $3.4$ è il solo valore frazionario "saltato" — ma non era ammissibile per la PLI comunque.

### 5.5.3 Regole di chiusura (pruning) di un nodo

Un nodo si può **chiudere** (terminare l'esplorazione di quel ramo) per:

| Causa | Condizione | Significato |
| :--- | :--- | :--- |
| **Infattibilità** | Il rilassamento lineare del sottoproblema è infattibile | Il sottoproblema PLI è inammissibile, nessuna soluzione qui |
| **Ottimalità** | L'ottimo del rilassamento è già intero | Candidato ottimo! Confronta col UB globale e aggiorna se migliora |
| **Bound** | $LB_i \ge UB$ globale | Anche se proseguissi, nessuna soluzione intera batterà l'UB attuale |

### 5.5.4 Strategie di esplorazione dell'albero

L'ordine con cui si esplorano i nodi aperti influisce sull'efficienza:

- **Depth-first** (profondità): scegli sempre il figlio appena generato. Vantaggio: trova rapidamente una soluzione intera (utile per avere subito un UB). Implementazione: pila/stack.
- **Breadth-first** (larghezza): esplora tutti i nodi a un livello prima di passare al successivo. Implementazione: coda/queue. Memoria onerosa.
- **Best-bound-first**: scegli il nodo aperto con LB più piccolo (più "promettente"). Garantisce di esplorare meno nodi nel caso peggiore.

### 5.5.5 Algoritmo B&B (versione minimizzazione)

```
INPUT: PLI (P) min{c^T x : Ax ≤ b, x ∈ Z^n_+}

INIZIALIZZAZIONE:
   L ← {P}            (lista nodi aperti)
   UB ← +∞            (incumbent: migliore intero trovato)
   x_best ← undefined

LOOP finché L ≠ ∅:
   1. Estrai un nodo P_i da L (criterio depth/breadth/best-bound)

   2. Risolvi il rilassamento lineare P_i^R → ottimo x_R con valore z_R

   3. PRUNE per infattibilità:
      se P_i^R è infattibile → scarta P_i, vai al passo 1

   4. PRUNE per bound:
      se z_R ≥ UB → scarta P_i, vai al passo 1

   5. PRUNE per ottimalità:
      se x_R è intero:
         se z_R < UB:
            UB ← z_R                   (aggiorna incumbent)
            x_best ← x_R
         scarta P_i, vai al passo 1

   6. BRANCH:
      scegli x_h frazionaria in x_R
      crea P_i,L con vincolo x_h ≤ ⌊x_R_h⌋
      crea P_i,R con vincolo x_h ≥ ⌈x_R_h⌉
      aggiungi P_i,L, P_i,R a L

FINE: x_best è l'ottimo, con valore UB
```

### 5.5.6 Esempio minimale di esecuzione

> [!example] Mini B&B su $\max\ x_1 + x_2$, $2x_1 + 5x_2 \le 16$, $6x_1 + 5x_2 \le 30$, $x \in \mathbb{Z}_+$
> **Nodo 0 (radice)**: ottimo RL $x_1 = 3.5, x_2 = 1.8, z_{RL} = 5.3$. Frazionario, $UB_{glob} = -\infty$.
> **Branch su $x_1$**: figli $x_1 \le 3$ e $x_1 \ge 4$.
> **Nodo 1 ($x_1 \le 3$)**: ottimo RL $x_1 = 3, x_2 = 2, z = 5$. Intero! Aggiorno $UB_{glob} = 5$ (per max, è un "lower bound globale"). Chiudo per ottimalità.
> **Nodo 2 ($x_1 \ge 4$)**: ottimo RL $x_1 = 4, x_2 = 1.2, z_{RL} = 5.2 > 5$. Continua branch.
> **Nodo 2.1 ($x_2 \le 1$)**: $x_1 = 4, x_2 = 1, z = 5$. Intero, ma $\le UB_{glob}$ corrente. Chiudo.
> **Nodo 2.2 ($x_2 \ge 2$)**: dal vincolo $6x_1 + 10 \le 30 \implies x_1 \le 3.33$, ma $x_1 \ge 4$ $\implies$ **infattibile**. Chiudo.
> Albero esaurito $\implies$ ottimo PLI: $x^* = (3, 2), z^* = 5$.

(Svolgimento completo: [[6 - Esercizi Branch & Bound]])

## 5.6 Modelli PLI ricorrenti

Alcuni problemi riconducibili a PLI si incontrano spesso negli esami:

### 5.6.1 Costi di avviamento (setup costs)

Costo di produzione: $0$ se $x_j = 0$, altrimenti $F_j + c_j x_j$. Linearizzazione:
$$\min\ \sum_j c_j x_j + F_j y_j \quad \text{s.t.} \quad x_j \le M y_j,\ x_j \ge 0,\ y_j \in \{0,1\}$$

### 5.6.2 Lotti di produzione minimi

Se si produce, almeno $L_j$ unità: "$x_j = 0$ oppure $x_j \ge L_j$":
$$x_j \le M y_j, \quad x_j \ge L_j y_j, \quad y_j \in \{0,1\}$$

### 5.6.3 Problema dello zaino (Knapsack)

Riempire uno zaino di volume $V$ con oggetti $j = 1, \dots, n$, ciascuno di volume $v_j$ e valore $c_j$, massimizzando il valore:
$$\max\ \sum_j c_j x_j \quad \text{s.t.} \quad \sum_j v_j x_j \le V,\ x_j \in \mathbb{Z}_+ \text{ (o } \{0,1\})$$

### 5.6.4 Set Covering

Coprire ogni elemento $i$ con almeno un sottoinsieme scelto:
$$\min\ \sum_j c_j x_j \quad \text{s.t.} \quad \sum_j a_{ij} x_j \ge 1 \ \forall i,\ x_j \in \{0,1\}$$

### 5.6.5 Set Partitioning

Come Set Covering, ma con uguaglianze: ogni elemento coperto da **esattamente uno**:
$$\min\ \sum_j c_j x_j \quad \text{s.t.} \quad \sum_j a_{ij} x_j = 1 \ \forall i,\ x_j \in \{0,1\}$$

## 5.7 Scelta del Big-M nei modelli PLI

Nei modelli con vincoli del tipo $x_j \le M y_j$:
- $M$ troppo piccolo $\implies$ taglia soluzioni ammissibili (modello errato).
- $M$ troppo grande $\implies$ rilassamento lineare debole $\implies$ B&B lento.
- **Regola pratica**: $M$ = upper bound naturale di $x_j$ (es. capacità massima, disponibilità totale).

## 5.8 Riepilogo strategico

```
DAVANTI A UN PROBLEMA PLI:

1. La matrice A è TUM?
   → SÌ: risolvi col Simplesso, fine.
   → NO: passa al punto 2.

2. Risolvi il Rilassamento Lineare:
   → Ottimo intero per caso?
      → SÌ: è l'ottimo PLI, fine.
      → NO: passa al punto 3.

3. Applica il Branch & Bound:
   - inizializza UB = +∞ (min) o -∞ (max)
   - branch su variabile frazionaria
   - bound con rilassamento lineare di ogni nodo
   - chiudi nodi per infattibilità / ottimalità / bound
   - termina quando la lista L è vuota → x_best è l'ottimo
```

> [!info] Riferimenti
> Dispense del corso: `PLI_Part02.pdf` cap. 13 (modelli PLI, TUM, rilassamenti), `PLI_Part03.pdf` cap. 14 (Branch & Bound, esempio svolto), `PLI_Part04.pdf` (esempi aggiuntivi).
