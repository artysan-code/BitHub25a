# Programmazione Dinamica I — Principi e Weighted Independent Set
La **programmazione dinamica** è una tecnica di progettazione algoritmica che consente di risolvere efficientemente problemi in cui tecniche più semplici — forza bruta, [[01 - Greedy e Interval Scheduling|greedy]], divide et impera — falliscono o esplodono in costo. L'idea centrale è quella di scomporre il problema in un numero *piccolo* di **sottoproblemi sovrapposti**, memorizzarne le soluzioni in una tabella ed evitare così il ricalcolo ripetuto. In questo senso la programmazione dinamica è la generalizzazione matura di ciò che abbiamo visto con fibonacci3 in [[01 - Il Problema di Fibonacci]]: invece di ricalcolare esponenzialmente gli stessi sottoproblemi, li memorizziamo e procediamo bottom-up.
## Il problema: Insieme Indipendente di Peso Massimo su grafo a cammino
> [!quote] Definizione — Insieme Indipendente (II)
> Dato un grafo $G = (V, E)$, un **insieme indipendente** è un sottoinsieme $S \subseteq V$ tale che nessuna coppia di nodi in $S$ è unita da un arco, ovvero:
> $$\forall\, u, v \in S \implies (u, v) \notin E$$

Il problema che analizziamo in questa nota è una variante pesata su **grafi a cammino** (path graph).
> [!quote] Definizione — Weighted Independent Set (WIS) su cammino
> **Input**: un cammino $G$ su $n$ nodi $v_1, v_2, \ldots, v_n$, dove ogni nodo $v_i$ ha peso $w_i \geq 0$.
> **Goal**: trovare un insieme indipendente $S^*$ tale che il peso totale
> $$w(S) = \sum_{v_i \in S} w_i$$
> sia **massimo**.

**Esempio di riferimento** (usato in tutta la nota):

```
 v1   v2   v3   v4   v5   v6
  1 — 4 — 8 — 4 — 3 — 10
```

Alcuni insiemi indipendenti e i loro pesi:

| Insieme $S$ | Peso $w(S)$ | Note |
|---|---|---|
| $\{v_1, v_3, v_5\}$ | $12$ | valido |
| $\{v_2, v_4, v_6\}$ | $18$ | valido, migliore |
| $\{v_1, v_3, v_6\}$ | $19$ | valido, **ottimo** |
## Perché le tecniche classiche non funzionano
### Forza bruta
Enumerare tutti i $2^n$ sottoinsiemi di nodi, filtrare quelli indipendenti e tenere il massimo è **corretto** ma richiede tempo $\Omega(2^n)$: esponenziale, impraticabile già per $n$ modesto.
### Approccio greedy
L'idea greedy è costruire la soluzione in modo incrementale scegliendo ogni volta il nodo non ancora escluso con peso massimo.

Funziona sull'esempio di riferimento, ma consideriamo l'istanza:

```
 v1   v2   v3   v4
  1 — 4 — 5 — 4
```

Il greedy sceglie $v_3$ (peso 5), poi non può scegliere $v_2$ né $v_4$, e sceglie $v_1$: ottiene $\{v_1, v_3\}$, peso $6$. La soluzione ottima è $\{v_2, v_4\}$, peso $8$. Il greedy **fallisce**.
> [!warning] Il greedy non funziona per WIS
> Non esiste alcun criterio di scelta locale che garantisca di trovare l'ottimo globale per il Weighted Independent Set. La scelta di un nodo molto pesante può precludere combinazioni ancora più vantaggiose tra i nodi vicini.
### Divide et impera
L'idea è dividere il cammino a metà, risolvere ricorsivamente il WIS su ciascuna metà e poi ricombinare. Il problema è che la **ricombinazione è difficile**: un nodo selezionato nell'ultima posizione della metà sinistra e uno nella prima posizione della metà destra potrebbero essere adiacenti, generando un conflitto. Risolverlo in modo generico riporta alla complessità esponenziale.
> [!info] Diagnosi comune
> Sia il greedy che il divide et impera falliscono perché non comprendono la **struttura globale del problema**: bisogna ragionare su *come* è fatta la soluzione ottima in termini di soluzioni ottime di sottoproblemi più piccoli.
## Struttura della soluzione ottima
Il passaggio critico della programmazione dinamica è ragionare sulla struttura della soluzione ottima. Questo porta poi a identificare i sottoproblemi giusti.

Sia $S^*$ la soluzione ottima (l'II di peso massimo di $G$). Consideriamo l'**ultimo nodo** $v_n$. Due casi sono esaustivi e mutuamente esclusivi:
**Caso 1** — $v_n \notin S^*$

Consideriamo $G' = G - \{v_n\}$ (il sottocammino sui primi $n-1$ nodi).
Allora $S^*$ è una soluzione ottima anche per $G'$.

*Dimostrazione*: se esistesse un insieme indipendente $S$ di $G'$ con $w(S) > w(S^*)$, allora $S$ sarebbe un II valido anche per $G$ (non contiene $v_n$) con peso maggiore di $S^*$: assurdo, perché $S^*$ è ottima per $G$.

```
 v1 — v2 — ... — v_{n-1}   [vn escluso]
 |_________G'_________|
```

**Caso 2** — $v_n \in S^*$

Poiché $S^*$ è un insieme indipendente, $v_{n-1} \notin S^*$ (i due nodi sono adiacenti).
Consideriamo $G'' = G - \{v_{n-1}, v_n\}$ (il sottocammino sui primi $n-2$ nodi).
Allora $S^* \setminus \{v_n\}$ è una soluzione ottima per $G''$.

*Dimostrazione*: se esistesse un insieme indipendente $S$ di $G''$ con $w(S) > w(S^* \setminus \{v_n\})$, allora $S \cup \{v_n\}$ sarebbe un II valido per $G$ (non contiene $v_{n-1}$) con peso $w(S) + w_n > w(S^*)$: assurdo.

```
 v1 — v2 — ... — v_{n-2}   [v_{n-1}, vn esclusi]
 |_________G''________|
```
> [!quote] Proprietà — Sottostruttura ottima del WIS
> L'insieme indipendente di peso massimo per $G$ è necessariamente uno dei due:
> 1. l'insieme indipendente di peso massimo per $G' = G - \{v_n\}$, oppure
> 2. $\{v_n\}$ unito all'insieme indipendente di peso massimo per $G'' = G - \{v_{n-1}, v_n\}$.
>
> Formalmente: $S^* = \arg\max\bigl(w(\text{OPT}(G')),\; w_n + w(\text{OPT}(G''))\bigr)$.

> [!question] Domanda tipica d'esame — Sottostruttura ottima del WIS
> **D:** Qual è la sottostruttura ottima del problema WIS su cammino, e come si dimostra che l'insieme ottimo $S^*$ deve rispettarla?
> **R:** Considerando l'ultimo nodo $v_n$, ci sono solo due casi possibili per $S^*$: (1) $v_n \notin S^*$, e allora $S^*$ è ottimo anche per $G' = G - \{v_n\}$; (2) $v_n \in S^*$, e allora (per indipendenza $v_{n-1} \notin S^*$) $S^* \setminus \{v_n\}$ è ottimo per $G'' = G - \{v_{n-1}, v_n\}$. La dimostrazione è per assurdo in entrambi i casi: se nel caso 1 esistesse un insieme indipendente $S$ di $G'$ con $w(S) > w(S^*)$, $S$ sarebbe indipendente anche in $G$ (non contiene $v_n$) e con peso maggiore di $S^*$, contraddicendo l'ottimalità di $S^*$ su $G$; analogamente nel caso 2, se esistesse un $S$ di $G''$ con $w(S) > w(S^* \setminus \{v_n\})$, allora $S \cup \{v_n\}$ sarebbe indipendente in $G$ (poiché $v_{n-1} \notin S$) con peso maggiore di $S^*$, di nuovo assurdo. Questa sottostruttura ottima è ciò che genera direttamente l'equazione di Bellman $\text{OPT}[j] = \max\{\text{OPT}[j-1],\, w_j + \text{OPT}[j-2]\}$: senza dimostrarla prima, la ricorrenza non sarebbe giustificata.
## Dall'idea ricorsiva all'algoritmo efficiente
### Prima idea (ingenua): ricorsione diretta
Dalla proprietà di sottostruttura ottima viene naturale un algoritmo ricorsivo che calcola entrambi i casi e restituisce il migliore:

```pseudo
\begin{algorithm}
\caption{WIS-Ricorsivo($G, j$)}
\begin{algorithmic}
\If{$j = 1$}
  \State \Return $w_1$
\EndIf
\If{$j = 2$}
  \State \Return $\max\{w_1, w_2\}$
\EndIf
\State \Return $\max\bigl\{\text{WIS-Ricorsivo}(G, j-1),\; w_j + \text{WIS-Ricorsivo}(G, j-2)\bigr\}$
\end{algorithmic}
\end{algorithm}
```

Il problema è il costo: l'equazione di ricorrenza è

$$T(n) = T(n-1) + T(n-2) + O(1)$$

che è quella di fibonacci2 (vedere [[01 - Il Problema di Fibonacci]] e [[03 - Equazioni di Ricorrenza]]). La soluzione è $T(n) = \Theta(\phi^n)$, **esponenziale**: la stessa di Fibonacci ricorsivo. I sottoproblemi vengono ricalcolati esponenzialmente molte volte.
### Osservazione chiave: quanti sottoproblemi distinti esistono?
> [!info] Numero di sottoproblemi distinti
> L'algoritmo ricorsivo risolve solo sottoproblemi della forma "WIS sul prefisso $G_j$" per $j = 1, \ldots, n$. Esistono quindi **esattamente $n$ sottoproblemi distinti** — uno per ogni prefisso di $G$. Sono $\Theta(n)$: pochi!

Invece di ricalcolare ogni sottoproblema ogni volta che serve, lo risolviamo **una volta sola** e memorizziamo il risultato.
## L'algoritmo di programmazione dinamica (bottom-up)
### Definizione dei sottoproblemi
- $G_j$: sottocammino composto dai **primi $j$ vertici** di $G$ (con $j = 1, \ldots, n$).
- **Sottoproblema $j$**: calcolare il peso dell'insieme indipendente di peso massimo di $G_j$.
- $\text{OPT}[j]$: valore della soluzione ottima del sottoproblema $j$ (peso dell'II di peso massimo di $G_j$).
### Equazione di Bellman (ricorrenza)
$$\text{OPT}[j] = \max\bigl\{\text{OPT}[j-1],\; w_j + \text{OPT}[j-2]\bigr\}$$

**Casi base**:
$$\text{OPT}[1] = w_1 \qquad \text{OPT}[2] = \max\{w_1, w_2\}$$

La ricorrenza cattura esattamente i due casi della struttura ottima: o $v_j$ non è nell'ottimo (e il valore coincide con l'ottimo di $G_{j-1}$), oppure $v_j$ è nell'ottimo (e il valore è $w_j$ più l'ottimo di $G_{j-2}$, poiché $v_{j-1}$ è escluso).
### Calcolo bottom-up con tabella
```pseudo
\begin{algorithm}
\caption{WIS-BottomUp($w[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}[1] \gets w[1]$
\State $\text{OPT}[2] \gets \max\{w[1], w[2]\}$
\For{$j \gets 3$ \To $n$}
  \State $\text{OPT}[j] \gets \max\{\text{OPT}[j-1],\; w[j] + \text{OPT}[j-2]\}$
\EndFor
\State \Return $\text{OPT}[n]$
\end{algorithmic}
\end{algorithm}
```

**Avanzamento sulla tabella** per l'esempio di riferimento (pesi: $1, 4, 8, 4, 3, 10$):

| $j$ | $w_j$ | $\text{OPT}[j-1]$ | $w_j + \text{OPT}[j-2]$ | $\text{OPT}[j]$ |
|---|---|---|---|---|
| 1 | 1 | — | — | **1** |
| 2 | 4 | — | — | **4** |
| 3 | 8 | 4 | $8 + 1 = 9$ | **9** |
| 4 | 4 | 9 | $4 + 4 = 8$ | **9** |
| 5 | 3 | 9 | $3 + 9 = 12$ | **12** |
| 6 | 10 | 12 | $10 + 9 = 19$ | **19** |

```
OPT:  1   4   9   9   12   19
       v1  v2  v3  v4  v5   v6
pesi: 1   4   8   4   3    10
```

Il valore ottimo è $\text{OPT}[6] = 19$, corrispondente all'insieme $\{v_1, v_3, v_6\}$ (lo verificheremo con la ricostruzione).
### Complessità di WIS-BottomUp
| Risorsa | Costo |
|---|---|
| Tempo | $T(n) = \Theta(n)$ — un'operazione per cella della tabella |
| Spazio | $O(n)$ — il vettore $\text{OPT}$ di $n$ elementi |

> [!info] Ottimizzazione spaziale
> Poiché la ricorrenza dipende solo da $\text{OPT}[j-1]$ e $\text{OPT}[j-2]$, è sufficiente mantenere le ultime due celle, riducendo lo spazio a $O(1)$. Tuttavia, per ricostruire la soluzione (non solo il valore) serve l'intero vettore.
## Ricostruzione della soluzione
WIS-BottomUp calcola il **valore** dell'ottimo, ma non l'insieme $S^*$ stesso. Come recuperare i nodi scelti?
> [!quote] Proprietà chiave — Criterio di appartenenza
> Il nodo $v_j$ appartiene all'insieme indipendente di peso massimo di $G_j$ **se e solo se**
> $$w_j + \text{OPT}[j-2] \geq \text{OPT}[j-1]$$
> (il secondo caso della ricorrenza è almeno buono quanto il primo).

Partendo da $j = n$ e percorrendo il vettore $\text{OPT}$ a ritroso:
- se $\text{OPT}[j-1] \geq w_j + \text{OPT}[j-2]$: $v_j \notin S^*$, si retrocede di un passo ($j \leftarrow j-1$);
- altrimenti: $v_j \in S^*$, si aggiunge $v_j$ e si retrocede di due passi ($j \leftarrow j-2$).

```pseudo
\begin{algorithm}
\caption{WIS-Ricostruisci($\text{OPT}[1 \ldots n],\, w[1 \ldots n]$)}
\begin{algorithmic}
\State $S^* \gets \emptyset$
\State $j \gets n$
\While{$j \geq 3$}
  \If{$\text{OPT}[j-1] \geq w[j] + \text{OPT}[j-2]$}
    \State $j \gets j - 1$
  \Else
    \State $S^* \gets S^* \cup \{v_j\}$
    \State $j \gets j - 2$
  \EndIf
\EndWhile
\If{$j = 2 \text{ e } w[2] > w[1]$}
  \State $S^* \gets S^* \cup \{v_2\}$
\Else
  \State $S^* \gets S^* \cup \{v_1\}$
\EndIf
\State \Return $S^*$
\end{algorithmic}
\end{algorithm}
```

**Traccia sull'esempio** ($\text{OPT} = [1, 4, 9, 9, 12, 19]$, pesi $[1, 4, 8, 4, 3, 10]$):

```
j=6: OPT[5]=12, w[6]+OPT[4]=10+9=19 → 19≥12 → aggiungi v6, j←4
j=4: OPT[3]=9,  w[4]+OPT[2]=4+4=8   → 9≥8   → non aggiungere, j←3
j=3: OPT[2]=4,  w[3]+OPT[1]=8+1=9   → 9≥4   → aggiungi v3, j←1
j=1: uscita dal while (j<3)
     j=1 (non j=2): aggiungi v1

S* = {v1, v3, v6}   w(S*) = 1 + 8 + 10 = 19  ✓
```

**Complessità di WIS-Ricostruisci**: $T(n) = \Theta(n)$ — ogni iterazione decrementa $j$ di almeno 1, quindi il ciclo esegue al più $n$ passi.

> [!question] Domanda tipica d'esame — Ricostruzione senza traccia delle scelte
> **D:** Come si ricostruisce la soluzione ottima del WIS senza salvare le scelte durante il calcolo bottom-up?
> **R:** Si sfrutta la proprietà chiave: $v_j \in S^*$ se e solo se $w_j + \text{OPT}[j-2] \geq \text{OPT}[j-1]$. Si scorre il vettore $\text{OPT}$ da $j = n$ verso sinistra: se vale questa disuguaglianza (il secondo caso della ricorrenza è almeno buono quanto il primo), si include $v_j$ e si salta a $j-2$; altrimenti si esclude $v_j$ e si retrocede a $j-1$. Non serve quindi salvare esplicitamente le scelte fatte durante il riempimento della tabella: bastano i valori $\text{OPT}[1..n]$ già calcolati per ricostruire a posteriori quali nodi appartengono a $S^*$. La complessità è $\Theta(n)$ aggiuntivo rispetto al calcolo del valore, dato che ogni iterazione del while decrementa $j$ di almeno 1.
## Principi generali della programmazione dinamica
Il WIS su cammino è il caso di studio introduttivo che illustra i principi generali della tecnica. Ogni algoritmo di programmazione dinamica ben costruito segue questa struttura:
> [!quote] Proprietà — I quattro passi della programmazione dinamica
> 1. **Identificare un numero piccolo di sottoproblemi.**
>    I sottoproblemi devono essere pochi (polinomiali in $n$); risolti tutti, la soluzione al problema originale si calcola rapidamente (spesso è semplicemente quella del sottoproblema più grande).
> 2. **Esprimere la soluzione di ogni sottoproblema in funzione di sottoproblemi più piccoli** (equazione di Bellman).
>    Ci devono esistere casi base e un ordinamento topologico dei sottoproblemi che permette di calcolare ciascuno usando solo soluzioni già note.
> 3. **Memorizzare le soluzioni dei sottoproblemi in una tabella.**
>    Ogni sottoproblema viene risolto esattamente una volta; il risultato è disponibile in $O(1)$ per tutti i sottoproblemi successivi che ne hanno bisogno.
> 4. **Avanzare sulla tabella nell'ordine giusto**, calcolando ogni cella in funzione di celle già riempite.

**Proprietà che i sottoproblemi devono soddisfare**:
- Essere **pochi** (tipicamente $O(n)$, $O(n^2)$, $O(n \cdot W)$, …).
- Avere **casi base** risolvibili direttamente.
- Avere un **ordine di risoluzione**: la dipendenza tra sottoproblemi deve essere aciclica.
- Risolti tutti, permettere di **ricavare rapidamente** la soluzione del problema originale.
> [!warning] La chiave è definire i sottoproblemi giusti
> La parte più difficile della programmazione dinamica non è scrivere il codice, ma **identificare i sottoproblemi corretti**. Essi sono un *punto di arrivo*, non di partenza: si trovano ragionando sulla struttura della soluzione ottima. Solo dopo aver definito i sottoproblemi si può verificare la correttezza dell'algoritmo e scrivere la ricorrenza.
>
> Errore tipico: scrivere una formula del tipo $\text{OPT}[j] = \text{OPT}[j-3] + j^2$ senza specificare cosa rappresenti $\text{OPT}[j]$. La formula senza la definizione del sottoproblema non ha significato.
### Schema della tecnica: top-down con memoization vs bottom-up
> [!info] Top-down (memoization) vs Bottom-up
> **Top-down con memoization**: si usa la ricorsione naturale, ma prima di calcolare $\text{OPT}[j]$ si controlla se è già memorizzato nella tabella. Se sì, si restituisce il valore salvato; altrimenti si calcola ricorsivamente e si salva.
>
> Vantaggio: calcola solo i sottoproblemi effettivamente raggiungibili dalla radice (utile se il grafo dei sottoproblemi è sparso).
> Svantaggio: overhead della ricorsione (stack) e gestione esplicita della tabella.
>
> **Bottom-up**: si riempie la tabella partendo dai casi base verso i sottoproblemi più grandi, nell'ordine topologico delle dipendenze.
>
> Vantaggio: nessun overhead di ricorsione; controllo esplicito sull'ordine di riempimento della tabella.
> Svantaggio: richiede di calcolare tutti i sottoproblemi, anche quelli non necessari.
>
> Per il WIS su cammino entrambi gli approcci hanno complessità $\Theta(n)$. La memoization è descritta per il Weighted Interval Scheduling in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]; il bottom-up è quello presentato sopra.
## Esercizio: WIS su alberi (problema della festa aziendale)
Le slide del corso propongono come estensione il WIS su **alberi** (non solo su cammini). Il problema è noto come *company party problem*:

> **Problema**: si vuole invitare un sottoinsieme di dipendenti a una festa aziendale massimizzando il divertimento totale. Il vincolo è che non si può invitare contemporaneamente un dipendente e il suo superiore diretto.

**Modellazione**: l'organigramma aziendale è un albero radicato; ogni nodo $v$ ha peso $w_v$ (il divertimento). L'obiettivo è trovare un insieme indipendente di peso massimo.

**Esempio delle slide** (pesi sui nodi):

```
              2          ← radice
           /     \
          7       6
        /   \   / | \
       3     1 2  3  3
```

L'ottimo ha peso **OPT = 15**: si selezionano i nodi $\{7, 2, 3, 3\}$ (tutti i nodi di livello 1 e i tre figli di 6), escludendo la radice e i figli di 7.

**Sottoproblemi** (due per ogni nodo $v$, per gestire l'alternativa include/esclude):
- $A[v]$: peso dell'II di peso massimo nel sottoalbero radicato in $v$ (senza vincoli su $v$).
- $B[v]$: peso dell'II di peso massimo nel sottoalbero radicato in $v$, con il vincolo che $v$ **non** venga incluso.

**Casi base** (nodi foglia):
$$A[v] = w_v \qquad B[v] = 0$$

**Ricorrenza** per un nodo interno con figli $u_1, \ldots, u_d$:
$$B[v] = \sum_{i=1}^{d} A[u_i]$$
$$A[v] = \max\!\left\{B[v],\; w_v + \sum_{i=1}^{d} B[u_i]\right\}$$

La logica: se $v$ non è incluso ($B[v]$), per ciascun figlio si prende il meglio senza vincoli ($A[u_i]$); se $v$ è incluso, nessun figlio può esserlo, quindi per ciascun figlio si prende il meglio senza $u_i$ ($B[u_i]$).

**Traccia del calcolo sull'esempio** (bottom-up dalle foglie alla radice):

```
Foglie:  A[3]=3, B[3]=0 | A[1]=1, B[1]=0 | A[2]=2, B[2]=0 | A[3]=3, B[3]=0 | A[3]=3, B[3]=0

Nodo 7 (figli: 3, 1):
  B[7] = A[3]+A[1] = 3+1 = 4
  A[7] = max{4, 7+B[3]+B[1]} = max{4, 7+0+0} = 7

Nodo 6 (figli: 2, 3, 3):
  B[6] = A[2]+A[3]+A[3] = 2+3+3 = 8
  A[6] = max{8, 6+B[2]+B[3]+B[3]} = max{8, 6+0+0+0} = 8

Radice 2 (figli: 7, 6):
  B[2] = A[7]+A[6] = 7+8 = 15
  A[2] = max{15, 2+B[7]+B[6]} = max{15, 2+4+8} = max{15, 14} = 15

OPT = A[radice] = 15  ✓
```

**Ordine di risoluzione**: bottom-up sull'albero (dalle foglie alla radice). La soluzione cercata è $A[r]$ dove $r$ è la radice.

**Complessità**: $\Theta(n)$ tempo (ogni nodo viene visitato una volta), $\Theta(n)$ spazio.

> [!question] Domanda tipica d'esame — Da cammino ad albero: perché due sottoproblemi per nodo
> **D:** Come si estende l'algoritmo di programmazione dinamica per il WIS dai cammini agli alberi, e perché serve una coppia di sottoproblemi per ogni nodo invece di uno solo come nel caso del cammino?
> **R:** Sul cammino basta un solo valore per sottoproblema, $\text{OPT}[j]$, perché la struttura "ultimo nodo incluso o no" si propaga linearmente lungo un solo predecessore. Su un albero questo non basta: quando si combina un nodo $v$ con i suoi figli, per decidere se $v$ può essere incluso bisogna sapere se ciascun figlio è incluso nella soluzione ottima del proprio sottoalbero, altrimenti si rischia di violare il vincolo di indipendenza tra $v$ e i figli. Per questo si definiscono due sottoproblemi per nodo: $A[v]$ (miglior II nel sottoalbero radicato in $v$, senza vincoli su $v$) e $B[v]$ (miglior II nello stesso sottoalbero, ma con $v$ escluso). La ricorrenza $B[v] = \sum_i A[u_i]$ e $A[v] = \max\{B[v],\, w_v + \sum_i B[u_i]\}$ sfrutta esattamente questa distinzione: se $v$ è incluso, tutti i figli devono essere nel loro stato "escluso" ($B[u_i]$); se $v$ non è incluso, ogni figlio può essere preso nel suo stato migliore incondizionato ($A[u_i]$). L'algoritmo resta $\Theta(n)$ tempo e spazio, calcolando ogni coppia $(A[v], B[v])$ una volta sola in ordine bottom-up dalle foglie alla radice.
## Riepilogo complessità
| Fase | Algoritmo | Tempo | Spazio |
|---|---|---|---|
| Valore ottimo | WIS-BottomUp | $\Theta(n)$ | $O(n)$ |
| Ricostruzione soluzione | WIS-Ricostruisci | $\Theta(n)$ | $O(1)$ aggiuntivo |
| Totale (valore + soluzione) | — | $\Theta(n)$ | $O(n)$ |

> [!question] Domanda tipica d'esame — Perché la ricorsione diretta è esponenziale
> **D:** Perché l'approccio ricorsivo diretto per il WIS su cammino ha complessità esponenziale, mentre l'algoritmo bottom-up è lineare?
> **R:** L'approccio ricorsivo diretto ha equazione di ricorrenza $T(n) = T(n-1) + T(n-2) + O(1)$, identica a quella di Fibonacci ricorsivo (vedere [[01 - Il Problema di Fibonacci]]), la cui soluzione è $\Theta(\phi^n)$ con $\phi \approx 1{,}618$. Il motivo è che gli stessi sottoproblemi vengono ricalcolati esponenzialmente molte volte: ad esempio $\text{OPT}[j]$ viene ricalcolato da tutte le chiamate che scendono verso prefissi più piccoli, e il numero di chiamate cresce esattamente come nella ricorsione di Fibonacci. L'algoritmo bottom-up rompe questa esplosione perché calcola ciascuno degli $n$ sottoproblemi esattamente una volta (in ordine crescente di $j$, sfruttando il fatto che i sottoproblemi distinti sono solo $\Theta(n)$), impiegando $O(1)$ per cella: complessità totale $\Theta(n)$.

> [!info] Connessioni ad altri argomenti
> - La memoization applicata a Fibonacci (fibonacci3) è la versione più semplice della programmazione dinamica: [[01 - Il Problema di Fibonacci]].
> - Le equazioni di ricorrenza del tipo $T(n) = T(n-1) + T(n-2) + O(1)$ e le tecniche per risolverle sono in [[03 - Equazioni di Ricorrenza]].
> - Il **Weighted Interval Scheduling** e il problema **Knapsack** — altri classici della programmazione dinamica — sono trattati nella nota successiva: [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]].
> - **Sequence Alignment** (distanza di edit) e **Bellman-Ford** (cammini minimi con archi negativi) come applicazioni avanzate della programmazione dinamica: [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].
> - Per il WIS su grafi generali (non cammini) il problema diventa NP-difficile: [[09 - NP-Completezza e Riduzioni]].
