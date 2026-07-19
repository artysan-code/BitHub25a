---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 05 — Raggiungibilità di un Target con Operatori +, × e Skip
*(Esercizio 3 — compito del 21/01/2025 — 11 punti)*
> [!note] Traccia
> Ti è data una sequenza di $n$ interi $s_1, s_2, \ldots, s_n$ e un intero target $N$. Fra ogni coppia di numeri $s_i$ e $s_{i+1}$ devi mettere un operatore preso dall'insieme $\{+, \times, \pm\}$, che sono l'operatore di somma ($+$), moltiplicazione ($\times$), e di skip ($\pm$). L'operatore $\pm$ ha la seguente semantica: $a \pm b = a + b - b = a$. Gli operatori vengono valutati da sinistra a destra e il tuo obiettivo è capire se puoi ottenere il valore $N$.
> **Esempio.** Per la sequenza $s_1 = 1, s_2 = 2, s_3 = 30, s_4 = 8$ è possibile ottenere $N = 10$:
> $$1 \times 2 \pm 30 + 8 = (1 \times 2) \pm 30 + 8 = 2 \pm 30 + 8 = (2 \pm 30) + 8 = 2 + 8 = 10$$
> mentre non è possibile ottenere $N = 15$.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che prende in input la sequenza e l'intero target $N$ e restituisce `true` se è possibile ottenere $N$, `false` altrimenti. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**Knapsack travestito da raggiungibilità booleana** — `OPT(i,v)` indicizzato sul prefisso $i$ e sul valore accumulato $v$, con un $\lor$ al posto del $\max$. Parente stretto del [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]] e del Subset Sum: il secondo indice non è una capacità residua che si consuma, ma il valore che si può ancora produrre. **Non** è un problema di ottimizzazione: non c'è alcun max/min nella ricorrenza, solo un OR fra le scelte d'operatore.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,v) = \texttt{true} \iff \text{esiste una scelta di operatori in } \{+,\times,\pm\} \text{ fra } s_1,\ldots,s_i \text{ che produce esattamente il valore } v$$
$i$ è il prefisso considerato, $v$ è il valore accumulato usando quel prefisso. A differenza del Knapsack, dove il secondo indice è una capacità che si consuma, qui $v$ può salire, scendere o restare invariato a seconda dell'operatore applicato.
Il range di $v$ è $[-M,M]$, con $M$ calcolato per induzione, una volta sola, come pre-processing:
$$B_1 = |s_1|, \qquad B_i = \max\bigl(B_{i-1}+|s_i|,\ B_{i-1}\cdot|s_i|,\ B_{i-1}\bigr) \text{ per } i \ge 2, \qquad M = B_n$$
Il bound è corretto per induzione: se ogni valore raggiungibile al passo $i-1$ sta in $[-B_{i-1},B_{i-1}]$, allora al passo $i$ resta invariato con $\pm$, diventa $u+s_i$ con $|u+s_i|\le B_{i-1}+|s_i|$ con $+$, oppure $u\cdot s_i$ con $|u\cdot s_i|=|u|\cdot|s_i|\le B_{i-1}\cdot|s_i|$ con $\times$; $B_i$ è il massimo dei tre bound.
I sottoproblemi sono $n\cdot(2M+1)$, uno per ogni coppia $(i,v)$ con $i\in\{1,\ldots,n\}$ e $v\in\{-M,\ldots,M\}$.
### Casi base
$$\text{OPT}(1,v) = \texttt{true} \iff v = s_1$$
Con un solo numero disponibile non c'è ancora nessun operatore da applicare, perché il primo operatore compare fra $s_1$ e $s_2$: l'unico valore raggiungibile è $s_1$ stesso. Per ogni $v \neq s_1$, $\text{OPT}(1,v)=\texttt{false}$.
La riga $i=1$ contiene sempre almeno un valore vero, esattamente $v=s_1$. La proprietà si mantiene per induzione a ogni riga successiva e permette di gestire il caso $s_i=0$ nella moltiplicazione senza dover controllare esplicitamente l'esistenza di un valore raggiungibile prima.
### Ricorrenza
Per $i \ge 2$ la ricorrenza distingue i tre operatori possibili fra il valore accumulato al passo $i-1$ e $s_i$.
**Applichi $\pm$**, lo skip. Il valore accumulato non cambia, perché $a\pm s_i=a$: $v$ è raggiungibile al passo $i$ se e solo se lo era già al passo $i-1$.
**Applichi $+$.** Il valore $v$ nasce da un $u=v-s_i$ raggiungibile al passo $i-1$: basta verificare se $v-s_i$ era raggiungibile, e se cade in $[-M,M]$.
**Applichi $\times$.** Se $s_i \neq 0$, $v$ nasce da $u=v/s_i$: serve una divisione esatta ($v \bmod s_i = 0$) e $v/s_i$ raggiungibile prima. Se $s_i=0$, ogni $u$ dà $u\cdot 0=0$: $\text{OPT}(i,0)$ è vero automaticamente, perché la riga precedente ha sempre almeno un valore vero; per $v\neq 0$ la moltiplicazione per $0$ non può mai produrlo.
$$\text{OPT}(i,v) = \text{OPT}(i-1,v) \;\vee\; \text{OPT}(i-1,v-s_i) \;\vee\; \Bigl[s_i \neq 0 \wedge (v \bmod s_i=0) \wedge \text{OPT}(i-1,v/s_i)\Bigr] \;\vee\; \bigl[s_i=0 \wedge v=0\bigr]$$
### Giustificazione
**Esaustività.** Su ogni posizione $i$ esiste un solo operatore da scegliere fra i tre possibili $\{+,\times,\pm\}$: non esiste una quarta opzione, e non se ne può applicare più di uno nella stessa posizione.
**Connettivo OR, non max/min.** Il problema è di raggiungibilità booleana, non di ottimizzazione: non serve dimostrare che un caso è migliore degli altri, basta che i tre casi coprano tutte le scelte possibili dell'operatore. È del tutto normale che lo stesso $v$ risulti raggiungibile da più casi contemporaneamente.
**Sottostruttura.** Ogni valore raggiungibile al passo $i$ deriva da un valore raggiungibile al passo $i-1$ tramite uno dei tre operatori; viceversa ogni valore raggiungibile al passo $i-1$, combinato con uno dei tre operatori, produce un valore raggiungibile al passo $i$. La ricorrenza copre quindi esattamente l'insieme dei valori raggiungibili, senza perderne né aggiungerne.
### Ordine di calcolo
Per $i$ crescente da $2$ a $n$, con la riga $i=1$ già nota dal caso base. Ogni riga $\text{OPT}(i,\cdot)$ dipende soltanto dalla riga $\text{OPT}(i-1,\cdot)$ già completamente calcolata: non c'è alcuna dipendenza all'interno della stessa riga, quindi l'ordine di scorrimento di $v$ da $-M$ a $M$ è irrilevante.
### Risposta
$$\text{OPT}(n,N)$$
`true` se e solo se, usando tutti gli $n$ numeri della sequenza con una qualche scelta di operatori, si ottiene esattamente il target $N$. Se $N \notin [-M,M]$ la risposta è `false` senza nemmeno consultare la tabella.
### Complessità
$\Theta\bigl(n\cdot(2M+1)\bigr) = \Theta(nM)$ celle, ciascuna risolta in $O(1)$ con al più tre letture di tabella e un'operazione aritmetica (sottrazione, divisione, modulo). Tempo $\Theta(nM)$, spazio $O(M)$ tenendo solo la riga corrente e la precedente, perché serve solo `true`/`false` e non la ricostruzione della sequenza di operatori.
È **pseudo-polinomiale**, con un'attenzione in più rispetto al Knapsack: qui $M$ non è un dato d'input come $W$ nel Knapsack, ma un valore derivato per induzione dalla sequenza stessa, potenzialmente esponenziale in $n$. Se $|s_i|\ge 2$ per ogni $i$, $M=\Omega(2^n)$: l'algoritmo resta pseudo-polinomiale per definizione, ma di fatto esponenziale su istanze con molte moltiplicazioni di numeri grandi.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{RaggiungiTarget($s[1 \ldots n],\, N$)}
\begin{algorithmic}
\State $B \gets |s[1]|$
\For{$i \gets 2$ \To $n$}
  \State $B \gets \max(B + |s[i]|,\; B \cdot |s[i]|,\; B)$
\EndFor
\State $M \gets B$
\If{$N < -M$ \textbf{or} $N > M$}
  \State \Return \texttt{false}
\EndIf
\For{$v \gets -M$ \To $M$}
  \State $\text{OPT}(1,v) \gets (v = s[1])$
\EndFor
\For{$i \gets 2$ \To $n$}
  \For{$v \gets -M$ \To $M$}
    \State $\text{skip} \gets \text{OPT}(i-1,v)$
    \State $\text{somma} \gets \bigl(v - s[i] \in [-M,M]\bigr) \wedge \text{OPT}(i-1)[v - s[i]]$
    \If{$s[i] \neq 0$}
      \State $\text{prodotto} \gets \bigl(v \bmod s[i] = 0\bigr) \wedge \bigl(v/s[i] \in [-M,M]\bigr) \wedge \text{OPT}(i-1)[v/s[i]]$
    \Else
      \State $\text{prodotto} \gets (v = 0)$
    \EndIf
    \State $\text{OPT}(i,v) \gets \text{skip} \vee \text{somma} \vee \text{prodotto}$
  \EndFor
\EndFor
\State \Return $\text{OPT}(n,N)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Tre indizi nella traccia guidano il riconoscimento. **"Preso dall'insieme $\{+,\times,\pm\}$"**: a ogni posizione la scelta è fra tre opzioni, non due come nel WIS o nel Knapsack 0/1. **"Restituisce `true` se è possibile ottenere $N$"**: non è un problema di ottimizzazione (max o min di qualcosa), è una **raggiungibilità booleana**, come nel Subset Sum.
Il punto di contatto con il [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Knapsack 0/1|Knapsack 0/1]] è strutturale: lì il secondo indice è la capacità residua, qui è il valore accumulato $v$. Non decresce monotonicamente come la capacità, ma serve allo stesso modo: senza saperlo, non si può decidere l'effetto dell'operatore successivo.
Un $\text{OPT}(i)$ a un solo indice, "posso ottenere $N$ col prefisso $i$?", sembra la traduzione più diretta della domanda ma non ammette ricorrenza. Sapere che il prefisso $1$ non raggiunge $10$ non dice nulla su cosa succede aggiungendo $s_2$: serve **quale** valore intermedio è stato prodotto (nell'esempio, $1$), non solo se coincide col target finale.
### Perché il bound non può essere $[-N,N]$
Limitare il range di $v$ ai valori vicini al target è l'errore più naturale: sembra inutile ricordare un valore lontanissimo da $N$. È falso, perché l'operatore $\pm$ può scartare un valore intermedio arbitrariamente grande, e un $+$ successivo può riportarlo vicino al target.
Nell'esempio $s=(1,2,30,8)$ con $N=10$, la riga $i=3$ contiene $90$, ben oltre $N$, ma resta un candidato legittimo finché non si esclude che serva a costruire la riga $i=4$. Il bound corretto è $M=B_n$, calcolato per induzione su **tutta** la sequenza, non guardando solo il target.
### Esempio numerico
$n=4$, $s=(1,\,2,\,30,\,8)$, target $N=10$.

| $i$ | $s_i$ | Valori raggiungibili |
|---|---|---|
| 1 | 1 | $\{1\}$ |
| 2 | 2 | $\{1,2,3\}$ |
| 3 | 30 | $\{1,2,3,30,31,32,33,60,90\}$ |
| 4 | 8 | $\{1,2,3,8,9,10,11,16,24,30,31,32,33,38,39,40,41,60,68,90,98,240,248,256,264,480,720\}$ |

Il valore $10$ compare in riga $4$ perché $2 \in \text{OPT}(3,\cdot)$ e $2+8=10$: infatti $\text{OPT}(4,10)=\text{OPT}(3,2)=\texttt{true}$, coerente con la traccia. Il valore $15$ non compare in nessuna riga: **false**, di nuovo coerente.
Il bound calcolato per induzione è $B_1=1,\ B_2=3,\ B_3=90,\ B_4=720$, ed è esatto: $720$ è proprio il massimo valore che compare nella riga $i=4$.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Definire $\text{OPT}(i)$ a un solo indice | non si riesce a scrivere la ricorrenza senza reintrodurre il valore accumulato |
| Dimenticare il caso $s_i=0$ nel $\times$ | produce una divisione per zero: la sequenza è di interi generici, $0$ è ammesso |
| Limitare il range a $[-N,N]$ | l'operatore $\pm$ scarta valori intermedi arbitrariamente grandi che un $+$ successivo può riportare vicino al target |
| Confondere pseudo-polinomiale con efficiente | qui $M$ non è un dato d'input come $W$ nel Knapsack: se $|s_i|\ge 2$ per ogni $i$, $M=\Omega(2^n)$ |
