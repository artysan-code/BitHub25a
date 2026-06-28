---
tags:
  - algoritmi
---
# Scansione lineare in spazio costante
Casistica "scansione $O(n)$, spazio $O(1)$" tratta in [[Casistiche d'Esame Modulo I]]; per la checklist di preparazione vedi [[Piano Esame ASD - Modulo I]] e il ripasso su [[05 - Strutture Dati Elementari e Dizionari]].
> [!question] Traccia — 30/01/2023
> Dati due array $A[1..n]$ e $B[1..n]$ di interi non negativi, trovare il primo indice $i \in \{1,\ldots,n\}$ tale che $\sum_{k=1}^{i} A[k] > \sum_{k=i}^{n} B[k]$, oppure restituire $-1$ se tale indice non esiste. L'algoritmo deve usare $O(1)$ spazio aggiuntivo (esclusi gli array in input).

**Modellazione.** Calcolare il suffisso $\sum_{k=i}^{n} B[k]$ da zero per ogni $i$ costerebbe $O(n)$ per iterazione, portando a $O(n^2)$ totale. L'idea è scomporre il suffisso usando la somma totale di $B$ precalcolata:

$$\sum_{k=i}^{n} B[k] = \underbrace{\sum_{k=1}^{n} B[k]}_{\text{total\_B}} - \underbrace{\sum_{k=1}^{i-1} B[k]}_{\text{prefB}}$$

Si esegue una prima passata per calcolare $\text{total\_B}$ in $O(n)$ con spazio $O(1)$. Nella seconda passata si mantengono due soli scalari:
- $\text{prefA} = \sum_{k=1}^{i} A[k]$, aggiornato **prima** del confronto aggiungendo $A[i]$;
- $\text{prefB} = \sum_{k=1}^{i-1} B[k]$, aggiornato **dopo** il confronto aggiungendo $B[i]$.

Il test per ogni $i$ diventa $\text{prefA} > \text{total\_B} - \text{prefB}$, eseguito in $O(1)$.

```pseudo
\begin{algorithm}
\caption{PrimoIndice($A$, $B$, $n$) → intero}
\begin{algorithmic}
\State $\text{total\_B} \gets 0$
\For{$j = 1$ \To $n$}
  \State $\text{total\_B} \gets \text{total\_B} + B[j]$
\EndFor
\State $\text{prefA} \gets 0$
\State $\text{prefB} \gets 0$
\For{$i = 1$ \To $n$}
  \State $\text{prefA} \gets \text{prefA} + A[i]$
  \If{$\text{prefA} > \text{total\_B} - \text{prefB}$}
    \State \Return $i$
  \EndIf
  \State $\text{prefB} \gets \text{prefB} + B[i]$
\EndFor
\State \Return $-1$
\end{algorithmic}
\end{algorithm}
```

**Complessità:** $O(n)$ tempo, $O(1)$ spazio aggiuntivo.
**Trappola:** $\sum_{k=i}^{n} B[k]$ include $B[i]$, quindi $\text{prefB}$ deve valere $\sum_{k=1}^{i-1} B[k]$ al momento del confronto — va aggiornato **dopo** il test. Aggiornarlo prima includerebbe $B[i]$ nel prefisso e produrrebbe il confronto sbagliato $\text{prefA} > \sum_{k=i+1}^{n} B[k]$, saltando un elemento.
