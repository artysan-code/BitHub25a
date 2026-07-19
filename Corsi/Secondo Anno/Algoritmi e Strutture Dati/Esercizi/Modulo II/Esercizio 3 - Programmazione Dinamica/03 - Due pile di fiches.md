---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 03 — Due pile di fiches
*(Esercizio 3 — compito del 09/06/2024 — 11 punti)*
> [!note] Traccia
> Un casinò di Las Vegas ha ideato il seguente gioco promozionale per attrarre nuovi giocatori. All'ingresso del casinò ci sono due grosse pile di fiches, etichettate $A$ e $B$. La pila $A$ contiene $n$ fiches ed il valore della generica $i$-esima fiche dal fondo di $A$ è $a_i > 0$. La pila $B$ contiene $m$ fiches ed il valore della generica $i$-esima fiche dal fondo di $B$ è $b_i > 0$.
> **Regole.** Il gioco funziona come segue: il giocatore effettua una sequenza di mosse, dove ogni mossa consiste nel selezionare una delle pile tra $A$ e $B$ ed in eseguire **entrambe** le seguenti azioni: rimuovere e tenere per sé la fiche in cima alla pila selezionata, e rimuovere e scartare due fiches dalla cima della pila **non** selezionata. Il gioco continua fino al momento in cui non esistono più mosse ammissibili, cioè fino a quando almeno una delle due pile diventa vuota, o entrambe le pile hanno esattamente una fiche.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che prende in input $m$, $n$, ed i valori di tutte le fiches nelle pile $A$ e $B$ e restituisce il massimo valore complessivo delle fiches che un giocatore riesce a tenere per sé. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**DP su due sequenze accoppiate** — `OPT(i,j)` indicizzato sulle fiches ancora presenti in ciascuna pila. Imparentato con il [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)|Sequence Alignment]]: due sequenze che si consumano entrambe richiedono due indici. La differenza è che qui il consumo è **asimmetrico e accoppiato**, non simmetrico: una mossa toglie $1$ fiche da una pila e $2$ dall'altra, mai la stessa quantità dalle due.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,j) = \text{massimo valore di fiches che il giocatore può ancora tenere, con } i \text{ fiches residue in } A \text{ (cima } a_i\text{) e } j \text{ in } B \text{ (cima } b_j\text{)}$$
$i$ e $j$ sono il numero di fiches ancora presenti in ciascuna pila, contate dal fondo. I sottoproblemi sono le coppie con $i = 0,\ldots,n$ e $j = 0,\ldots,m$, cioè $\Theta(nm)$.
### Casi base
$$\text{OPT}(0,j) = 0 \qquad \text{per ogni } j = 0, \ldots, m$$
$$\text{OPT}(i,0) = 0 \qquad \text{per ogni } i = 0, \ldots, n$$
Se la pila $A$ è vuota ($i=0$) non esiste alcuna mossa ammissibile che selezioni $A$, perché non c'è nulla da prendere in cima, né una mossa che selezioni $B$, perché richiederebbe di scartare due fiches da $A$ che non ci sono. Il gioco è già finito, e da questo punto in poi non si guadagna più nulla: da cui il valore $0$. Simmetricamente per $\text{OPT}(i,0)$ quando è $B$ a essere vuota.
Il caso neutro è $0$ e non $+\infty$ perché la tabella accumula un **massimo**: $0$ fiches raccolte da qui in poi è un valore legittimo e raggiungibile, non un valore impossibile da scartare come accadrebbe in una minimizzazione.
Il caso terminale con **entrambe le pile a una sola fiche**, cioè $\text{OPT}(1,1)$, non è un caso base a parte: emerge dalla ricorrenza generale, perché a $i=1,\,j=1$ nessuna delle due mosse risulta ammissibile.
### Ricorrenza
Per $i,j \ge 0$ le mosse possibili sono due, quando ammissibili.
**Selezioni la pila $A$.** Tieni la fiche in cima ad $A$, di valore $a_i$; $A$ perde quella fiche ($i \to i-1$); $B$, la pila non selezionata, perde le sue due fiches in cima ($j \to j-2$). Ammissibile solo se $i \ge 1$ e $j \ge 2$.
**Selezioni la pila $B$.** Simmetrico: tieni $b_j$; $B$ passa a $j-1$; $A$, la pila non selezionata, passa a $i-2$. Ammissibile se $j \ge 1$ e $i \ge 2$.
**Nessuna mossa è ammissibile.** Il gioco è terminato da questo stato: non c'è altro da raccogliere.
$$\text{OPT}(i,j) = \max \begin{cases} a_i + \text{OPT}(i-1,j-2) & \text{se } i \geq 1,\ j \geq 2 \\ b_j + \text{OPT}(i-2,j-1) & \text{se } j \geq 1,\ i \geq 2 \\ 0 & \text{altrimenti} \end{cases}$$
### Giustificazione
**Esaustività e mutua esclusività.** Ad ogni mossa il giocatore deve scegliere una fra le sole due pile: non esiste una terza opzione, e non si possono selezionare entrambe insieme — la traccia lo dice esplicitamente ("selezionare **una delle** pile"). Se lo stato $(i,j)$ ammette almeno una mossa valida, quella mossa è o la selezione di $A$ o quella di $B$, mai entrambe: sono per costruzione l'una l'opposto dell'altra. Se nessuna delle due è ammissibile, vale il terzo caso.
**Sottostruttura ottima.** Dopo una mossa resta ancora una coppia di pile residue, cioè un sottoproblema dello stesso tipo e più piccolo. Se nel seguito non si giocasse in modo ottimo, sostituendo quella parte con la strategia ottima si otterrebbe un valore complessivo maggiore, contro l'ottimalità della soluzione di partenza.
### Ordine di calcolo
$\text{OPT}(i,j)$ dipende sempre da celle con indice $i$ strettamente più piccolo: $\text{OPT}(i-1,j-2)$ e $\text{OPT}(i-2,j-1)$ appartengono a righe precedenti ($i-1$ e $i-2$), mai alla riga corrente. Basta riempire la tabella per righe crescenti: $i$ da $0$ a $n$, e per ogni $i$ tutte le colonne $j$ da $0$ a $m$ in un ordine qualsiasi, perché nessuna dipendenza resta all'interno della riga.
### Risposta
$$\text{OPT}(n,m)$$
Il gioco inizia con la pila $A$ intera ($n$ fiches) e la pila $B$ intera ($m$ fiches): è la situazione descritta da quella cella.
### Complessità
La tabella ha $(n+1)\times(m+1) = \Theta(nm)$ celle, ciascuna calcolata in $O(1)$ con al più due somme e un massimo fra due o tre valori. Tempo $\Theta(nm)$, spazio $\Theta(nm)$; tenendo in memoria solo le ultime due righe lo spazio scende a $O(m)$.
È **polinomiale**, non pseudo-polinomiale: $n$ e $m$ sono il numero di fiches nelle due pile, cioè la dimensione reale dell'istanza, non valori che possano essere rappresentati in modo esponenzialmente più compatto della loro grandezza.
È diverso dal Knapsack, dove la capacità $W$ compare come *valore* nel costo $\Theta(nW)$ pur occupando solo $O(\log W)$ bit in input: lì il costo è pseudo-polinomiale perché è polinomiale nel valore di $W$ ma non nella sua dimensione in bit. Qui $n$ e $m$ sono già, letteralmente, delle lunghezze.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{PileFiches($n, m, a[1 \ldots n], b[1 \ldots m]$)}
\begin{algorithmic}
\For{$j \gets 0$ \To $m$}
  \State $\text{OPT}(0,j) \gets 0$
\EndFor
\For{$i \gets 1$ \To $n$}
  \State $\text{OPT}(i,0) \gets 0$
  \For{$j \gets 1$ \To $m$}
    \State $\text{migliore} \gets 0$ \Comment{nessuna mossa ammissibile}
    \If{$j \geq 2$}
      \State $\text{migliore} \gets \max(\text{migliore},\; a[i] + \text{OPT}(i-1,j-2))$
    \EndIf
    \If{$i \geq 2$}
      \State $\text{migliore} \gets \max(\text{migliore},\; b[j] + \text{OPT}(i-2,j-1))$
    \EndIf
    \State $\text{OPT}(i,j) \gets \text{migliore}$
  \EndFor
\EndFor
\State \Return $\text{OPT}(n,m)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Le parole chiave sono **due pile** e **in cima**. "In cima" dice che ogni pila si consuma da un'estremità verso l'altra, in ordine — esattamente come i prefissi del [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]]: le fiches non si scelgono a caso dentro la pila, si prendono (o si scartano) sempre nell'ordine imposto dalla pila. Fin qui sembrerebbe un WIS su cammino, con un solo indice.
Il dettaglio che rompe questa illusione è "**rimuovere e scartare due fiches dalla cima della pila non selezionata**": ogni mossa non tocca solo la pila su cui si decide, tocca anche l'altra. Scegliere di giocare $A$ consuma contemporaneamente il fondo residuo di $A$ e la cima di $B$. Le due pile non sono indipendenti: sono accoppiate, e si consumano insieme a ogni mossa.
È il segnale del pattern "due sequenze da confrontare" catalogato anche per [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)|Sequence Alignment]] (vedi il [[Formulario DP]]): quando l'input sono due sequenze che si consumano entrambe, il sottoproblema ha due indici, uno per sequenza. La differenza rispetto a Sequence Alignment è che lì i due indici avanzano quasi sempre in modo simmetrico, mentre qui il consumo è asimmetrico e accoppiato: una mossa toglie $1$ da una pila e $2$ dall'altra, mai la stessa quantità.
In sintesi: un WIS travestito da gioco a due pile, raddoppiato a due indici perché le due pile si consumano insieme e non si può ignorarne una decidendo sull'altra.
### Perché servono due indici
La domanda diagnostica del [[Formulario DP|formulario]] è: per decidere sulla mossa corrente, cosa serve sapere del passato che un solo indice non dice?
Un tentativo con un solo indice definirebbe $\text{OPT}(i)$ come il valore massimo ottenibile considerando solo le prime $i$ fiches di $A$, ignorando $B$. Se alla mossa corrente si gioca $A$, si prende $a_i$ e si passa a $\text{OPT}(i-1)$: fin qui sembra filare. Il problema è $B$: la regola dice che due fiches di $B$ vengono scartate a ogni mossa su $A$. Per sapere se la mossa è ammissibile (servono almeno due fiches in $B$) e da quale stato di $B$ si riparte, serve conoscere quante fiches restano in $B$ in quel momento — un'informazione che $\text{OPT}(i-1)$, definito solo su $A$, non contiene e non può ricostruire: il numero di fiches consumate da $B$ dipende da quante volte, nelle mosse precedenti, si è scelto di giocare $A$ invece di $B$, e questo è precisamente ciò che l'indice singolo $i$ non registra.
Il tentativo si rompe qui: un solo indice non basta, perché lo stato del gioco non è "quante fiches di $A$ restano" ma "quante fiches di $A$ **e** di $B$ restano", due quantità che evolvono insieme senza essere deducibili l'una dall'altra. Serve un secondo indice $j$ = fiches rimaste nella pila $B$. Con la coppia $(i,j)$ lo stato del gioco è completamente determinato: le mosse ammissibili e il loro effetto dipendono solo da $i$ e $j$.
```
A: a1 a2 ... a_i        (cima = a_i)
B: b1 b2 ... b_j        (cima = b_j)

seleziona A → tieni a_i, scarta b_j e b_{j-1}   (i→i-1, j→j-2)
seleziona B → tieni b_j, scarta a_i e a_{i-1}   (j→j-1, i→i-2)
```
### Esempio numerico
$n=3$, $A=(a_1,a_2,a_3)=(1,1,1)$; $m=3$, $B=(b_1,b_2,b_3)=(9,1,1)$.

| Strategia | Mosse | Totale |
|---|---|---|
| Seleziona sempre $B$ per prima | prendi $b_3=1$ (scarta $a_3,a_2$), poi prendi $a_1=1$ (scarta $b_2,b_1$) | $2$ |
| Ottima | prendi $a_3=1$ (scarta $b_3,b_2$), poi prendi $b_1=9$ (scarta $a_2,a_1$) | $\mathbf{10}$ |

Selezionare $B$ per prima scarta $a_3,a_2$ e chiude l'accesso al resto di $A$ dopo un solo turno in più; selezionare $A$ per prima scarta invece le due fiches meno pregiate di $B$ ($b_3,b_2$) e libera $b_1=9$, che diventa la nuova cima di $B$. Con la ricorrenza: $\text{OPT}(3,3) = \max(a_3+\text{OPT}(2,1),\; b_3+\text{OPT}(1,2)) = \max(1+9,\;1+1) = 10$.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Dimenticare il secondo indice, definendo $\text{OPT}(i)$ solo su $A$ | non si riesce a esprimere l'ammissibilità né lo stato residuo di $B$ senza sapere quante fiches vi restano |
| Invertire pila selezionata e pila scartata nella ricorrenza | il pedice del valore raccolto ($a_i$ o $b_j$) deve coincidere con la pila che scende di $1$, non con quella che scende di $2$ |
| Confondere "$i$-esima fiche dal fondo" con "cima della pila" | quando restano $i$ fiches in $A$ la cima è $a_i$, non $a_1$ |
| Trattare $\text{OPT}(1,1)=0$ come caso base a sé | emerge da solo quando nessuna delle due mosse è ammissibile, senza bisogno di gestirlo a parte |
| Dichiarare $\Theta(nm)$ pseudo-polinomiale per analogia col Knapsack | $n$ e $m$ sono conteggi di elementi in input, non valori numerici arbitrari come $W$ |
