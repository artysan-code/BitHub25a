---
tags:
  - algoritmi
  - approssimazione
slide: "09_Apx_Algorithms_II_2025.pdf"
capitolo: "Kleinberg-Tardos cap. 11.2"
---
# Approssimazione II (k-Center)
Seconda parte dell'approssimazione: dopo il [[09 - NP-Completezza e Riduzioni#Load Balancing — 2-approssimazione|Load Balancing]] si studia il problema del **k-center** (*center selection*), di nuovo con un algoritmo greedy e una garanzia di approssimazione. Per la definizione di $\alpha$-approssimazione vedi [[09 - NP-Completezza e Riduzioni#Algoritmi di approssimazione (cenni)]].
## Il problema k-Center
> [!quote] Definizione — k-Center (center selection)
> **Input.** Un insieme di $n$ **siti** $s_1, \dots, s_n$ e un intero $k > 0$.
>
> **Problema.** Scegliere $k$ **centri** $C$ in modo che la **massima distanza** da un sito al centro più vicino sia **minima**.

Nella figura della slide $k = 4$: i siti sono punti, i centri sono scelti tra i punti del piano, e ogni sito è servito dal centro più vicino. Il massimo di queste distanze è il **raggio** $r(C)$, il raggio della «palla» più grande necessaria per coprire tutti i siti. La slide dà due letture applicative: i centri come *ospedali* o *caserme dei vigili del fuoco*, i siti come le zone da servire (si vuole che nessuna zona sia troppo lontana dal centro più vicino).

La slide segnala anche una **variante**: i centri sono obbligati a stare **sulle posizioni dei siti**.

### Notazione
- $\text{dist}(x, y)$ = distanza tra $x$ e $y$.
- $\text{dist}(s_i, C) = \min_{c \in C} \text{dist}(s_i, c)$ = distanza di $s_i$ dal centro più vicino.
- $r(C) = \max_i \text{dist}(s_i, C)$ = **raggio di copertura** più piccolo (il minimo raggio con cui i centri in $C$ coprono tutti i siti).

**Obiettivo.** Trovare l'insieme di centri $C$ che minimizza $r(C)$, con il vincolo $|C| = k$.

> [!quote] Proprietà della funzione distanza
> - $\text{dist}(x, x) = 0$ *(identità)*
> - $\text{dist}(x, y) = \text{dist}(y, x)$ *(simmetria)*
> - $\text{dist}(x, y) \leq \text{dist}(x, z) + \text{dist}(z, y)$ *(disuguaglianza triangolare)*
>
> La disuguaglianza triangolare è quella che serve nella dimostrazione del [[#Analisi dell'algoritmo greedy|teorema]].

### Esempi
**Punti nel piano.** Ogni sito è un punto del piano, un centro può essere **qualsiasi punto del piano**, $\text{dist}(x, y)$ è la distanza euclidea. Nella figura della slide $r(C)$ è il raggio della palla più grande attorno a un centro.

**Grafo pesato.** Ogni sito è un vertice di un grafo non orientato pesato, un centro può essere **qualsiasi vertice**, $\text{dist}(x, y)$ è la distanza pesata in $G$ tra $x$ e $y$ (cioè il costo del cammino minimo). Nella figura della slide gli archi senza etichetta hanno peso 1, ci sono $k = 4$ centri e il grafo è diviso in quattro gruppi di vertici, ciascuno servito dal suo centro. I raggi dei quattro gruppi sono $r = 2$, $r = 1$, $r = 2$, $r = 3$; il raggio della soluzione è il massimo:

$$r(C) = \max\{2, 1, 2, 3\} = 3.$$
## L'algoritmo greedy
Idea della slide: scegliere ripetutamente come nuovo centro il sito **più lontano** da tutti i centri già scelti.

```pseudo
\begin{algorithm}
\caption{Greedy-Center-Selection($k, n, s_1, s_2, \dots, s_n$)}
\begin{algorithmic}
\State $C \gets \emptyset$
\For{$k$ volte}
  \State scegli un sito $s_i$ con $\text{dist}(s_i, C)$ massima \Comment{sito più lontano da ogni centro}
  \State $C \gets C \cup \{s_i\}$
\EndFor
\State \Return $C$
\end{algorithmic}
\end{algorithm}
```

L'algoritmo mette sempre i centri **sui siti**. La slide mostra un'esecuzione con $k = 4$, passo per passo (un centro aggiunto alla volta, figure), e alla fine il raggio $r(C)$ ottenuto.

> [!info] Osservazione
> Al termine dell'algoritmo tutti i centri in $C$ sono a **distanza almeno $r(C)$** a due a due.
>
> **Dimostrazione:** per costruzione dell'algoritmo. $\square$
>
> *(extra, non da slide)* Il passaggio che la slide lascia a «per costruzione»: quando viene scelto un centro $c$, la sua distanza dai centri già presenti è la massima tra tutti i siti; i raggi $\text{dist}(\cdot, C)$ non crescono mai aggiungendo centri, quindi tale distanza è almeno il massimo finale $r(C)$.
## Analisi dell'algoritmo greedy
> [!quote] Teorema
> Sia $C^*$ un insieme ottimo di centri. Allora $r(C) \leq 2\, r(C^*)$.
>
> **Dimostrazione** (per assurdo). Si assume $r(C^*) < \tfrac{1}{2} r(C)$.
>
> 1. Per ogni centro $c_i \in C$ si considera la **palla** di raggio $\tfrac{1}{2} r(C)$ attorno a $c_i$. Le palle sono **disgiunte**, perché tutti i centri di $C$ sono a distanza almeno $r(C)$ a due a due (osservazione).
> 2. **In ogni palla c'è esattamente un centro $c_i^*$ di $C^*$:**
>    - ogni palla di centro $c_i \in C$ deve contenere un centro di $C^*$: altrimenti $\text{dist}(c_i, C^*) \geq \tfrac{1}{2} r(C) > r(C^*)$, assurdo;
>    - le palle sono disgiunte e $|C| = |C^*|$ (= $k$), quindi ne contengono uno ciascuna.
>
>    Si indica con $c_i$ il centro di $C$ abbinato a $c_i^*$.
> 3. Si prende un sito $s$ qualsiasi e il suo centro più vicino $c_i^*$ in $C^*$. Allora
>    $$\text{dist}(s, C) \leq \text{dist}(s, c_i) \leq \text{dist}(s, c_i^*) + \text{dist}(c_i^*, c_i) \leq 2\, r(C^*).$$
>    La seconda disuguaglianza è la disuguaglianza triangolare; per la terza, $\text{dist}(s, c_i^*) \leq r(C^*)$ perché $c_i^*$ è il centro di $C^*$ più vicino a $s$, e $\text{dist}(c_i^*, c_i) \leq r(C^*)$ perché $c_i^*$ è il centro di $C^*$ più vicino al sito $c_i$ *(extra, non da slide: la slide scrive solo «$\leq r(C^*)$ since $c_i^*$ is closest center»; infatti $c_i$ è un sito, quindi $\text{dist}(c_i, C^*) \leq r(C^*) < \tfrac{1}{2} r(C)$, e l'unico centro di $C^*$ a distanza minore di $\tfrac{1}{2} r(C)$ da $c_i$ è $c_i^*$)*.
> 4. Quindi $r(C) \leq 2\, r(C^*)$, in contraddizione con l'ipotesi $r(C^*) < \tfrac{1}{2} r(C)$. $\square$

> [!info] Come leggere la figura della dimostrazione
> Quattro palle di raggio $\tfrac{1}{2} r(C)$, una per ogni centro $c_i$ di $C$ (quadrati), ciascuna con dentro un centro $c_i^*$ di $C^*$ (cerchi). Un sito $s$ fuori dalle palle è collegato al suo $c_i^*$ più vicino e al $c_i$ abbinato: i tre punti $s$, $c_i^*$, $c_i$ formano il triangolo a cui si applica la disuguaglianza triangolare.

> [!quote] Teorema
> L'algoritmo greedy è una **2-approssimazione** per il problema del center selection.

> [!info] Remark
> L'algoritmo greedy mette sempre i centri **sui siti**, ma resta entro un fattore 2 dalla migliore soluzione che può mettere i centri **ovunque** (per esempio, punti del piano).
## Inapprossimabilità
La slide chiede se si possa sperare in un'approssimazione migliore, e risponde che è «molto improbabile»:

> [!quote] Teorema
> A meno che $P = NP$, non esiste nessun algoritmo di $\alpha$-approssimazione per il center selection con $\alpha < 2$.

La slide enuncia il risultato **senza dimostrazione**: il fattore 2 del greedy è dunque il migliore possibile, a meno che $P = NP$.
