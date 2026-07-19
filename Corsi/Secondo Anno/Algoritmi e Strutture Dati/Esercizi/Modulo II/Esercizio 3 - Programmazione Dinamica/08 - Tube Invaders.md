---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 08 — Tube Invaders
*(Esercizio 3 — compito del 18/07/2025 — 11 punti)*
> [!note] Traccia
> **Ambientazione.** Dovete progettare un algoritmo per giocare a *Tube Invaders*, un nuovo videogioco messo in commercio proprio il giorno dello scritto di ASD. *Tube Invaders* è un gioco semplice in cui voi controllate un'astronave che avanza dentro un tubo. Il tubo è diviso in $n$ segmenti, corrispondenti alle $n$ battaglie — numerate da $1$ a $n$ — che dovete affrontare. Nella battaglia $i$ troverete una flotta di $a_i$ alieni.
> **Regole.** Per affrontare le battaglie avete a disposizione un'arma. L'arma, quando non la usate, accumula energia: l'energia rappresenta il massimo numero di alieni che potete distruggere quando decidete di usarla in battaglia. Subito dopo aver usato l'arma, l'energia torna a $1$; anche all'inizio, nella prima battaglia, l'energia è $1$. L'energia raddoppia a ogni battaglia in cui non la usate.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che calcoli il massimo numero di alieni che potete distruggere in una generica istanza di *Tube Invaders*. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**DP su prefisso con terminazione forzata** — `OPT(i)` indicizzato sull'ultima battaglia in cui si spara, non su un generico prefisso di lunghezza $i$. Stessa famiglia della [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Longest Increasing Subsequence (LIS)|Longest Increasing Subsequence]], con una scelta **multipla** sul predecessore come in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Segmented Least Squares|Segmented Least Squares]].
## Soluzione
### Sottoproblema
$$\text{OPT}(i) = \text{massimo numero di alieni distrutti nelle battaglie } 1,\ldots,i \text{ supponendo che l'arma venga usata esattamente alla battaglia } i$$
$i$ è l'ultima battaglia, fra le prime $i$, in cui si spara: fissare che lo sparo avvenga esattamente lì determina univocamente l'energia disponibile, in funzione della battaglia precedente $p$ in cui si è sparato l'ultima volta (o della sua assenza).
I sottoproblemi sono $\Theta(n)$, uno per ciascuna battaglia $i=1,\ldots,n$, più l'indice fittizio $\text{OPT}(0)=0$ che rappresenta «nessuna battaglia affrontata, arma mai usata»: il punto di partenza da cui si misura il primo sparo dell'intera partita.
### Casi base
$$\text{OPT}(0) = 0$$
È un sottoproblema virtuale che rappresenta l'istante prima dell'inizio del gioco: zero battaglie affrontate, zero alieni distrutti, arma mai usata. Il valore è lecito perché il problema massimizza quantità $\min\{2^k, a_i\} \geq 0$: $0$ è un risultato realmente raggiungibile, non una sentinella $-\infty$ per stati non ancora ammissibili.
$$\text{OPT}(1) = \min\{1, a_1\}$$
Con una sola battaglia disponibile l'unica strategia che spara esattamente in $1$ usa l'energia iniziale, che vale sempre $1$. Il caso è già catturato dalla ricorrenza generale con $p=0$; si scrive qui solo per completezza dei bordi.
### Ricorrenza
Per $i=1,\ldots,n$ le mosse possibili corrispondono a dove è avvenuto lo sparo precedente.
**Non spara mai prima di $i$**, cioè $i$ è il primo sparo dell'intera partita. L'energia si è raddoppiata ininterrottamente dalla battaglia $1$ (energia $2^0=1$) fino a $i$, raggiungendo $2^{i-1}$.
**L'ultimo sparo prima di $i$ è avvenuto alla battaglia $p$**, per ogni $p=1,\ldots,i-1$. Tra $p$ e $i$ sono trascorse $i-p-1$ battaglie senza sparare (le battaglie $p+1,\ldots,i-1$), quindi l'energia — ripartita da $1$ subito dopo lo sparo in $p$ — si è raddoppiata $i-p-1$ volte.
$$\text{OPT}(i) = \max \begin{cases} \min\{2^{\,i-1},\, a_i\} + \text{OPT}(0) \\[4pt] \displaystyle\max_{1 \,\le\, p \,<\, i} \Bigl(\text{OPT}(p) + \min\{2^{\,i-p-1},\, a_i\}\Bigr) \end{cases}$$
### Giustificazione
**Esaustività.** Fissata una strategia ottima che spara alla battaglia $i$, lo sparo immediatamente precedente nella stessa strategia o non esiste (nessuna battaglia prima ha visto uno sparo) oppure è avvenuto a un preciso $p<i$: non esiste una terza possibilità, e i casi non si sovrappongono mai, perché una strategia ha uno e un solo penultimo sparo (o nessuno).
**Scelta multipla, non binaria.** A differenza del Weighted Interval Scheduling, dove il predecessore $p(j)$ è un valore univoco calcolabile a priori, qui qualunque $p<i$ è ammissibile: ciascuno implica un'energia diversa, perché il raddoppio dipende da *quanto tempo fa* è avvenuto l'ultimo sparo, non da *quale* battaglia in astratto. Vanno quindi confrontate tutte le alternative, non una sola candidata fissa.
**Sottostruttura ottima.** $\text{OPT}(p)$ è già il meglio ottenibile fino a $p$ con l'ultimo sparo esattamente lì: se il prefisso $1,\ldots,p$ non fosse gestito in modo ottimo, sostituirlo con la strategia ottima non peggiorerebbe mai il totale. Comporre $\text{OPT}(p)$ con la scelta di sparare in $i$ resta quindi ottimo per costruzione.
### Ordine di calcolo
Per $i$ crescente da $1$ a $n$. Per calcolare $\text{OPT}(i)$ servono tutti i valori $\text{OPT}(p)$ con $p=0,\ldots,i-1$, già calcolati nei passi precedenti: non serve alcuna seconda dimensione da scandire, perché l'energia $2^{\,i-p-1}$ si ricalcola in $O(1)$ da $i$ e $p$.
### Risposta
$$\max\Bigl\{\, 0,\; \max_{i=1}^{n} \text{OPT}(i) \,\Bigr\}$$
Ogni cella $\text{OPT}(i)$ rappresenta solo le strategie che sparano esattamente l'ultima volta alla battaglia $i$: non è detto che nella strategia globalmente ottima l'ultimo sparo cada proprio in $n$, esattamente come nella LIS la sottosequenza più lunga può terminare in un punto qualunque dell'array. La risposta è il massimo su tutte le celle, incluso il caso limite «non sparo mai» rappresentato dallo $0$ esplicito.
### Complessità
$\Theta(n)$ sottoproblemi, incluso l'indice virtuale $\text{OPT}(0)$. Calcolare $\text{OPT}(i)$ richiede di scandire i predecessori candidati $p=0,\ldots,i-1$, quindi costa $O(i)$; sommando su tutti gli $i$, $\sum_{i=1}^{n} O(i) = O(n^2)$. La scansione finale per il massimo su tutte le celle è $O(n)$, dominata dal riempimento. Tempo $O(n^2)$, spazio $O(n)$ per il vettore $\text{OPT}(0\ldots n)$.
È **polinomiale in senso proprio**, non pseudo-polinomiale: il numero di sottoproblemi e il costo per cella dipendono solo dal numero di battaglie $n$, mai dal valore di $a_i$, che compare solo come termine di confronto/saturazione a costo $O(1)$ — a differenza del Knapsack, dove la capacità $W$ indicizza direttamente la tabella.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{TubeInvaders($n, a[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(0) \gets 0$
\For{$i \gets 1$ \To $n$}
  \State $\text{OPT}(i) \gets 0$
  \State $e \gets 1$ \Comment{$e$ rappresenta $2^{\,i-p-1}$, ricalcolato mentre $p$ decresce}
  \For{$p \gets i-1$ \DownTo $0$}
    \State $\text{OPT}(i) \gets \max\bigl(\text{OPT}(i),\; \text{OPT}(p) + \min(e, a[i])\bigr)$
    \State $e \gets \min(2 \cdot e,\, a[i] + 1)$ \Comment{satura ad $a_i$, non serve mai calcolare oltre}
  \EndFor
\EndFor
\State \Return $\max\bigl(0,\; \max_{i=1,\ldots,n} \text{OPT}(i)\bigr)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Tre elementi della traccia decidono il pattern. «*L'energia raddoppia a ogni battaglia in cui non la usate*» dice che l'energia disponibile non è un dato indipendente ma dipende da **quante battaglie consecutive** sono passate dall'ultimo utilizzo dell'arma — uno stato che si accumula nel tempo. «*Subito dopo aver usato l'arma, l'energia diventa $1$*» dice che ogni sparo **azzera** quello stato: per decidere il futuro basta un solo dato, qual è stata l'ultima battaglia in cui si è sparato, esattamente come in LIS conta solo il valore con cui termina la sottosequenza.
Il terzo elemento è l'assenza di un predecessore obbligato univoco, come il $p(j)$ del Weighted Interval Scheduling: l'ultimo sparo potrebbe essere stato in qualunque battaglia precedente, il che rende la scelta multipla e non binaria. Lo stesso schema, sotto un travestimento diverso, ricorre in [[07 - BurgerGata e coupon]].
### Perché OPT(i) deve terminare esattamente in i
Un tentativo naturale, ricalcato sullo schema del WIS, è definire $\text{OPT}'[i]$ come il massimo numero di alieni distrutti nelle prime $i$ battaglie, senza altri vincoli. Estendendo a $i+1$ sparando, il contributo dipende dall'energia disponibile, che a sua volta dipende da *quante battaglie consecutive* sono passate dall'ultimo sparo — un'informazione che $\text{OPT}'[i]$, essendo un singolo numero, non conserva.
Il controesempio è netto. Con $n=4$ e $a=(3,1,1,50)$, il totale migliore fino alla battaglia $3$ si ottiene sparando a ogni battaglia ($1+1+1=3$), ma questa strategia lascia l'energia a $1$ alla battaglia $4$: estendendola si distruggono solo $\min\{1,50\}=1$ alieni in più, per un totale di $4$.
La strategia globalmente ottima è invece non sparare mai nelle prime tre battaglie, lasciando l'energia raddoppiare fino a $8$: alla battaglia $4$ si distruggono $\min\{8,50\}=8$ alieni, per un totale di $8$ — quasi il doppio.
La strategia migliore per $\text{OPT}'[3]$ (valore $3$) porta a un pessimo risultato finale; quella che vince globalmente parte da un valore isolato di $0$, il peggiore possibile per le prime tre battaglie. Il numero totale accumulato da solo non basta: serve sapere *quando* è avvenuto l'ultimo sparo, non solo *quanto* si è distrutto. Fissare che $\text{OPT}(i)$ termini con uno sparo esattamente in $i$ rende quell'informazione esplicita per costruzione.
### Esempio numerico
$n=4$, $a=(3,\,1,\,1,\,50)$. Tracciamento cella per cella, con $p$ che varia sulle colonne:

| $i$ | $p=0$ | $p=1$ | $p=2$ | $p=3$ | $\text{OPT}(i)$ |
|---|---|---|---|---|---|
| 1 | $2^0{=}1\to\min\{1,3\}{=}1$; $0+1=1$ | — | — | — | **1** |
| 2 | $2^1{=}2\to\min\{2,1\}{=}1$; $0+1=1$ | $2^0{=}1\to\min\{1,1\}{=}1$; $1+1=2$ | — | — | **2** |
| 3 | $2^2{=}4\to\min\{4,1\}{=}1$; $0+1=1$ | $2^1{=}2\to\min\{2,1\}{=}1$; $1+1=2$ | $2^0{=}1\to\min\{1,1\}{=}1$; $2+1=3$ | — | **3** |
| 4 | $2^3{=}8\to\min\{8,50\}{=}8$; $0+8=\mathbf{8}$ | $2^2{=}4\to\min\{4,50\}{=}4$; $1+4=5$ | $2^1{=}2\to\min\{2,50\}{=}2$; $2+2=4$ | $2^0{=}1\to\min\{1,50\}{=}1$; $3+1=4$ | **8** |

A $i=3$ vince $p=2$ (sparare sempre appena possibile, totale $3$), ma a $i=4$ il massimo non estende quella scelta: vince $p=0$ (non aver mai sparato prima, energia accumulata a $8$), con un salto da $3$ a $8$ che nessuna estensione di $\text{OPT}(3)=3$ avrebbe potuto raggiungere. La risposta finale è $\max\{0,1,2,3,8\}=8$, che coincide con $\text{OPT}(4)$ solo per coincidenza di questa istanza.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Definire $\text{OPT}(i)$ come "il meglio nelle prime $i$ battaglie" senza vincolo di terminazione | scrivendo la ricorrenza esplicitamente, non si riesce a dire da dove viene l'esponente nel $\min$ |
| Scrivere l'esponente come $2^{\,i-p}$ invece di $2^{\,i-p-1}$ | con $p=0,\ i=1$ l'energia deve essere $2^0=1$; $2^{i-p}$ darebbe $2^1=2$ |
| Dimenticare il confronto con $0$ nella risposta finale | se nessuna cella conviene, l'unica strategia sensata è «non sparo mai», non rappresentata da alcun $\text{OPT}(i)$ |
| Restituire $\text{OPT}(n)$ come risposta, invece di $\max_i \text{OPT}(i)$ | la definizione dice «termina in $i$», non «è ottima su tutte le $n$ battaglie» |
| Calcolare $2^{\,i-p-1}$ senza saturazione | il divario $i-p-1$ può arrivare a $n-1$: basta confrontare con $a_i$, non conoscere il valore esatto oltre quella soglia |
| Dichiarare la complessità $O(n)$ per analogia col WIS | la scelta è multipla su tutti i $p<i$, non binaria: il ciclo interno costa $O(i)$, non $O(1)$ |
