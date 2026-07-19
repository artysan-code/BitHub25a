---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 01 — Pizza a gusti misti
*(Esercizio 3 — compito del 13/06/2024 — 11 punti)*
> [!note] Traccia
> Alice e Bob ti hanno invitato a cena e avete ordinato una teglia di pizza con gusti misti: $n$ pezzi già tagliati, allineati in una striscia e numerati da sinistra a destra. Se mangi il pezzo $i$-esimo godi $g_i$.
> **Regole.** Puoi prendere solo uno dei due pezzi esterni rimasti. Tu scegli per primo; subito dopo la tua scelta Alice e Bob mangiano i due pezzi più esterni fra quelli rimasti; poi tocca di nuovo a te.
> **Esempi sull'intera teglia.** Se mangi il pezzo $1$, loro mangiano il $2$ e l'$n$. Se mangi il pezzo $n$, loro mangiano l'$1$ e l'$n-1$.
> **Richiesta.** Progetta un algoritmo di programmazione dinamica che calcoli il massimo godimento ottenibile, dove il godimento di un sottoinsieme $S \subseteq \{1,\ldots,n\}$ è $g(S)=\sum_{i\in S} g_i$. Si discuta la complessità temporale.
## Pattern
**DP su intervallo** — `OPT(l,r)` indicizzato sugli **estremi** del segmento residuo. Parente stretto del [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)|Segmented Least Squares]]; **non** è un Knapsack, perché il secondo indice non è una risorsa che si consuma ma la seconda coordinata del sottoproblema.
## Soluzione
### Sottoproblema
$$\text{OPT}(l,r) = \text{massimo godimento ottenibile quando restano i pezzi } g_l,\ldots,g_r \text{ ed è il tuo turno}$$
$l$ ed $r$ sono gli estremi del segmento ancora sul tavolo. I sottoproblemi sono le coppie con $1 \le l \le r \le n$, cioè $\Theta(n^2)$.
### Casi base
$$\text{OPT}(l,r) = 0 \qquad \text{per ogni } l > r$$
Il segmento è vuoto: non resta nulla da mangiare. La condizione è una **disuguaglianza** perché la ricorrenza sposta gli indici di due e tre posizioni per volta, quindi produce anche celle in cui $l$ supera $r$ di due o di tre.
Da questa sentinella la ricorrenza ricava da sola i due casi piccoli: con **un pezzo solo** dà $\text{OPT}(l,l)=g_l$ (lo mangi, non c'è scelta), con **due pezzi** dà $\text{OPT}(l,l+1)=\max(g_l,g_{l+1})$ (prendi il migliore, l'altro non lo mangi più). Sul compito conviene enunciarli comunque: sono due righe e mostrano che i bordi sono stati controllati.
### Ricorrenza
Per $l \le r$ le mosse possibili sono due.
**Mangi il pezzo $l$**, l'estremo sinistro. Guadagni $g_l$; restano i pezzi $[l+1,\,r]$; Alice e Bob mangiano i due più esterni di questo segmento, cioè $l+1$ e $r$; torni a giocare su $[l+2,\,r-1]$.
**Mangi il pezzo $r$**, l'estremo destro. Guadagni $g_r$; restano $[l,\,r-1]$; loro mangiano $l$ e $r-1$; torni a giocare su $[l+1,\,r-2]$.
$$\text{OPT}(l,r) = \max \begin{cases} g_l + \text{OPT}(l+2,r-1) \\[2pt] g_r + \text{OPT}(l+1,r-2) \end{cases}$$
### Giustificazione
**Esaustività.** La regola consente solo i due pezzi esterni: non esiste una terza mossa, e non se ne possono fare due nello stesso turno.
**Assenza di minimo.** Alice e Bob non scelgono, mangiano sempre i due più esterni: lo stato successivo dipende soltanto dalla tua decisione, quindi la ricorrenza non contiene alcun $\min$.
**Sottostruttura ottima.** Dopo un turno completo resta ancora un segmento contiguo con il tuo turno di scegliere, cioè un sottoproblema dello stesso tipo e più corto di tre pezzi. Se nel seguito non giocassi in modo ottimo, sostituendo quella parte con la strategia ottima otterrei un godimento complessivo maggiore, contro l'ottimalità della soluzione di partenza.
### Ordine di calcolo
Per lunghezza crescente del segmento. Posto $d = r-l$, si scorre $d$ da $0$ a $n-1$ e per ogni $d$ si scorre $l$ da $1$ a $n-d$ ponendo $r = l+d$. Le due celle da cui $\text{OPT}(l,r)$ dipende hanno lunghezza $d-3$, quindi sono già state calcolate.
### Risposta
$$\text{OPT}(1,n)$$
All'inizio hai davanti l'intera teglia ed è il tuo turno: è la situazione descritta da quella cella.
### Complessità
$\Theta(n^2)$ sottoproblemi, ciascuno risolto in $O(1)$ con due somme, due letture e un confronto. Tempo $\Theta(n^2)$, spazio $\Theta(n^2)$.
È **polinomiale**, non pseudo-polinomiale: la tabella è indicizzata su $n$ e non sui valori $g_i$, che compaiono solo come termini additivi.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{PizzaGusti($g[1 \ldots n]$)}
\begin{algorithmic}
\Comment{$\text{OPT}(l,r) = 0$ ogni volta che $l > r$}
\For{$d \gets 0$ \To $n-1$}
  \For{$l \gets 1$ \To $n-d$}
    \State $r \gets l + d$
    \State $\text{OPT}(l,r) \gets \max\bigl(g[l] + \text{OPT}(l+2,r-1),\; g[r] + \text{OPT}(l+1,r-2)\bigr)$
  \EndFor
\EndFor
\State \Return $\text{OPT}(1,n)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Due frasi della traccia decidono tutto. «*Solo uno dei due pezzi esterni*» dice che ciò che resta è sempre un segmento contiguo. «*Alice e Bob mangiano i due più esterni*» è la trappola: assomiglia al gioco delle monete in fila, che si risolve col minimax, ma qui loro non scelgono e la funzione obiettivo conta solo i pezzi che mangi tu. La ricorrenza è quindi **max-max**, non max-min.
Tolto il minimax resta un'ottimizzazione a singolo agente su un intervallo che si accorcia: ogni turno consuma tre pezzi, ma restringe il segmento in due modi asimmetrici a seconda dell'estremo scelto.
### Perché servono due indici
Nel [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]] basta un indice perché il residuo è sempre un prefisso: si consuma un solo lato. Qui i pezzi spariscono da entrambi i lati contemporaneamente.
```
prima:   1  2  3  4  ...  n-1  n
tu:      x                          mangi 1
loro:       x              x        mangiano 2 e n
resta:         3  4  ...  n-1
```
Hai toccato solo l'estremo sinistro, eppure il residuo $[3,\,n-1]$ ha perso pezzi da tutt'e due i lati. Per descriverlo servono due informazioni indipendenti: dove il segmento **inizia** e dove **finisce**.
### Esempio numerico
$n=4$, $g=[3,\,9,\,1,\,2]$.

| Strategia | Mosse | Totale |
|---|---|---|
| Greedy — prendi l'estremo maggiore | prendi $1$ ($=3$), loro prendono $2$ e $4$, prendi $3$ ($=1$) | $4$ |
| Ottima | prendi $4$ ($=2$), loro prendono $1$ e $3$, prendi $2$ ($=9$) | $\mathbf{11}$ |

Il greedy lascia che si portino via il pezzo da $9$. Con la ricorrenza: $\max(3+\text{OPT}(3,3),\; 2+\text{OPT}(2,2)) = \max(4,11) = 11$.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Scrivere un $\min$, trattandolo come minimax | $g(S)$ è definita solo sui pezzi che mangi tu |
| Far sparire un pezzo per turno invece di tre | la traccia dice che dopo il pezzo $1$ restano $3,\ldots,n-1$ |
| Scambiare le traslazioni degli indici | a sinistra $l$ avanza di $2$ e $r$ arretra di $1$; a destra il contrario |
| Scrivere il caso base come $\text{OPT}(l,l-1)=0$ | la ricorrenza genera anche $l=r+2$ e $l=r+3$ |
| Dichiarare $O(n)$ per analogia col WIS | il residuo è una finestra, non un prefisso: $\Theta(n^2)$ |
