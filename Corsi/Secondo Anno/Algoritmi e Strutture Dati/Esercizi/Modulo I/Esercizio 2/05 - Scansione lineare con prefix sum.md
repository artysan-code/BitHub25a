---
tags:
  - algoritmi
---
# Scansione lineare con prefix sum
Casistica di [[Casistiche d'Esame Modulo I|progettazione]] su array: tecnica del prefisso cumulato, $O(n)$ tempo e $O(1)$ spazio. Per la checklist d'esame: [[Piano Esame ASD - Modulo I]]. Ripasso: [[04 - Algoritmi di Ordinamento]], [[05 - Strutture Dati Elementari e Dizionari]].

> [!question] Traccia — 19/02/2024
> Dato un array $A[1..n]$ di interi, trovare il minimo indice $i \in [1, n]$ tale che
> $$\sum_{j=1}^{i} A[j] > \sum_{j=i+1}^{n} A[j].$$
> Se nessun tale indice esiste, restituire $-1$.

**Idea.** Si calcola prima la somma totale $S = \sum_{j=1}^{n} A[j]$ con una scansione sinistra–destra. Si percorre poi $A$ una seconda volta tenendo un solo accumulatore $\text{prefix}$: al termine del passo $i$ vale $\text{prefix} = \sum_{j=1}^{i} A[j]$, e il suffisso corrisponde a $S - \text{prefix}$ senza ricalcolo. La condizione $\text{prefix} > S - \text{prefix}$ si riscrive come $2\cdot\text{prefix} > S$, eliminando la sottrazione esplicita. Al primo $i$ che soddisfa la condizione si restituisce $i$; se il ciclo termina senza trovarne alcuno, si restituisce $-1$.

> [!info] Le due variabili e il trucco del suffisso
> - $S$ = somma totale dell'array, calcolata una volta sola.
> - $\text{prefix}$ = somma corrente $A[1..i]$, aggiornata $+A[i]$ a ogni passo: è l'unico stato che si trascina ($O(1)$ spazio, nessun array ausiliario).
> - **Identità chiave**: il suffisso $A[i+1..n]$ non si ricalcola, è $S - \text{prefix}$. Quindi $\text{prefix} > \text{suffisso} \iff \text{prefix} > S - \text{prefix} \iff 2\cdot\text{prefix} > S$. Confrontare con $S$ evita perfino la sottrazione.

```pseudo
\begin{algorithm}
\caption{prefissoMaggiore($A$, $n$) → intero}
\begin{algorithmic}
\State $S \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $S \gets S + A[j]$
\EndFor
\State $\text{prefix} \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $\text{prefix} \gets \text{prefix} + A[i]$
  \If{$2 \cdot \text{prefix} > S$}
    \State \Return $i$
  \EndIf
\EndFor
\State \Return $-1$ \Comment{nessun indice soddisfa la condizione}
\end{algorithmic}
\end{algorithm}
```

> [!example] Esempio — $A = [1, 3, 1]$
> Somma totale $S = 5$.
> - $i=1$: $\text{prefix}=1$ → $2\cdot 1 = 2 > 5$? no.
> - $i=2$: $\text{prefix}=4$ → $2\cdot 4 = 8 > 5$? sì → si restituisce $2$.
>
> Verifica: a $i=2$ il prefisso $A[1..2]=4$ supera il suffisso $A[3]=1$; a $i=1$ il prefisso $1$ non superava il suffisso $3+1=4$. Risposta = **2**.

**Complessità:** $O(n)$ tempo, $O(1)$ spazio ausiliario (nessun array aggiuntivo: due sole variabili scalari $S$ e $\text{prefix}$).
**Trappola:** ricalcolare $\sum A[i+1..n]$ con un ciclo interno ad ogni passo porterebbe a $O(n^2)$; la chiave è sfruttare $S - \text{prefix}$ ricavato in $O(1)$ dopo aver calcolato $S$ una volta sola. Occorre inoltre gestire il caso in cui nessun indice soddisfa la condizione restituendo esplicitamente $-1$, non un valore indefinito.
