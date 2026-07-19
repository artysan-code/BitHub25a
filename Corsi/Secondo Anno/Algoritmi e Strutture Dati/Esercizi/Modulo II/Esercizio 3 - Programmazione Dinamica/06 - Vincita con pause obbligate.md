---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 06 — Vincita con pause obbligate
*(Esercizio 3 — compito del 18/02/2025 — 11 punti)*
> [!note] Traccia
> Siete appena tornati da un viaggio nel tempo e mentre eravate nel futuro avete preso i numeri vincenti della lotteria settimanale. Così ora avete $n$ numeri vincenti, per ognuna delle prossime $n$ settimane. Conoscete anche il valore della vincita $v_i$ per ogni settimana $i$.
> **Vincolo.** Ora, il problema è che la polizia sta cercando i viaggiatori nel tempo, quindi dovete cercare di non destare sospetti. Così decidete di giocare alla lotteria con il seguente vincolo: fra una vincita e l'altra devono esserci *almeno* 3 settimane in cui non vincete.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che calcola il valore massimo che riuscirete a guadagnare nelle prossime $n$ settimane. Si discuta la complessità temporale dell'algoritmo proposto.
## Pattern
**Weighted Independent Set su cammino**, con vincolo di distanza minima generalizzato — `OPT(j)` indicizzato sul prefisso, come nel [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]]. Un solo indice basta ancora, ma il salto della ricorrenza passa da $j-2$ a $j-4$, perché il vincolo impone almeno 3 settimane di pausa (non 1) fra due vincite.
## Soluzione
### Sottoproblema
$$\text{OPT}(j) = \text{massimo guadagno ottenibile considerando soltanto le prime } j \text{ settimane, rispettando il vincolo di almeno 3 settimane di pausa fra due vincite consecutive}$$
$j$ è la lunghezza del prefisso analizzato. I sottoproblemi reali sono $n+1$, uno per ogni $j=0,1,\ldots,n$. Nella ricorrenza compaiono anche indici negativi ($j-1,\ldots,j-4$ per $j$ piccolo): sono coperti dalla convenzione sui casi base, non sono sottoproblemi indipendenti.
### Casi base
$$\text{OPT}(j) = 0 \qquad \text{per ogni } j \le 0$$
Per $j\le 0$ non c'è alcuna settimana disponibile: il guadagno massimo su un insieme vuoto è $0$. Essendo una massimizzazione di quantità sempre $\ge 0$, il valore neutro è $0$ e non $-\infty$: $0$ è già un valore ammissibile (non vincere mai).
Estendere questa convenzione a tutto l'intervallo $j\le 0$ (invece di $j=0$ soltanto, come nel Weighted Interval Scheduling della [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Weighted Interval Scheduling|nota 05]]) evita di dover scrivere a mano quattro casi base espliciti.
La ricorrenza generale, applicata con questa convenzione, riproduce i valori corretti per le prime settimane:
- $\text{OPT}(1) = \max\{\text{OPT}(0),\, v_1 + \text{OPT}(-3)\} = v_1$
- $\text{OPT}(2) = \max\{\text{OPT}(1),\, v_2 + \text{OPT}(-2)\} = \max\{v_1,\, v_2\}$
- $\text{OPT}(3) = \max\{\text{OPT}(2),\, v_3 + \text{OPT}(-1)\} = \max\{\text{OPT}(2),\, v_3\}$
- $\text{OPT}(4) = \max\{\text{OPT}(3),\, v_4 + \text{OPT}(0)\} = \max\{\text{OPT}(3),\, v_4\}$

In nessuno di questi quattro casi $v_1$ può sommarsi a un altro $v_j$: la prima combinazione a lunga distanza ammissibile è $\text{OPT}(5) = \max\{\text{OPT}(4),\, v_5+\text{OPT}(1)\}$, dove $v_1$ e $v_5$ hanno finalmente tre settimane di pausa (2, 3, 4) fra loro.
### Ricorrenza
Per $j \ge 1$ le mosse possibili sono due.
**Non vinco alla settimana $j$.** Il guadagno massimo sulle prime $j$ settimane coincide con quello sulle prime $j-1$: la settimana $j$ non aggiunge nulla e il vincolo di pausa resta intatto.
**Vinco alla settimana $j$.** Incasso $v_j$, ma il vincolo impone che le tre settimane immediatamente precedenti ($j-1,\,j-2,\,j-3$) restino senza vincita; il residuo libero si ferma quindi a $j-4$, e il meglio ottenibile su di esso è $\text{OPT}(j-4)$.
$$\text{OPT}(j) = \max \begin{cases} \text{OPT}(j-1) \\[2pt] v_j + \text{OPT}(j-4) \end{cases}$$
### Giustificazione
**Esaustività.** Sulla settimana $j$ esistono solo due possibilità: vincere o non vincere. Non esiste una terza opzione, e le due non possono verificarsi insieme nello stesso sottoproblema.
**Sottostruttura ottima.** Se vinco in $j$, le tre settimane precedenti sono vincolate a restare senza vincita, quindi il residuo su cui ottimizzare è esattamente il prefisso fino a $j-4$; se non vinco in $j$, il residuo è il prefisso fino a $j-1$. In entrambi i casi il residuo è un sottoproblema dello stesso tipo e più corto. Se la strategia su quel residuo non fosse ottima, sostituirla con quella ottima darebbe un guadagno complessivo maggiore, contro l'ottimalità della soluzione di partenza.
### Ordine di calcolo
Si procede per $j$ crescente, da $1$ a $n$. Il calcolo di $\text{OPT}(j)$ richiede $\text{OPT}(j-1)$ e $\text{OPT}(j-4)$, entrambi di indice strettamente minore (o coperti dalla convenzione $\text{OPT}(k)=0$ per $k\le 0$, disponibile fin dall'inizio). Non c'è dipendenza circolare: l'ordine crescente su un solo indice è l'unico possibile.
### Risposta
$$\text{OPT}(n)$$
È il guadagno massimo considerando tutte le $n$ settimane a disposizione, esattamente ciò che la traccia chiede.
### Complessità
La tabella ha $n+1$ celle; le celle a indice negativo sono costanti a $0$ e non richiedono calcolo. Ogni cella costa $O(1)$: un confronto fra due valori già disponibili, senza ciclo interno (a differenza di Segmented Least Squares o LIS, la scelta qui è binaria).
$$T(n) = (n+1)\cdot O(1) = O(n)$$
Spazio $O(n)$ per la tabella completa; con una finestra scorrevole delle ultime $4$ celle basta $O(1)$, se non serve ricostruire quali settimane sono state scelte.
È **polinomiale**, non pseudo-polinomiale: il costo dipende solo dal numero $n$ di settimane, non dai valori $v_i$ né dalla costante $3$ del vincolo.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{VincitaMax($v[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(j) \gets 0$ \Comment{per ogni $j \leq 0$}
\For{$j \gets 1$ \To $n$}
  \State $\text{OPT}(j) \gets \max\bigl(\text{OPT}(j-1),\; v[j] + \text{OPT}(j-4)\bigr)$
\EndFor
\State \Return $\text{OPT}(n)$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Tre elementi della traccia decidono il pattern. **"Prossime $n$ settimane"** indica una sequenza, non un grafo generico né due sequenze da confrontare. **"Valore massimo"** indica un'ottimizzazione, non un conteggio. **"Fra una vincita e l'altra devono esserci almeno 3 settimane"** è un vincolo di distanza minima fra due elementi scelti.
È un [[04 - Programmazione Dinamica I (Weighted Independent Set)|Weighted Independent Set]] su cammino travestito: ogni settimana $i$ è un nodo di peso $v_i$, e "vincere in settimana $i$" corrisponde a "includere $i$ nell'insieme". Nel WIS classico la distanza minima fra due indici scelti è $1$; qui è $4$, perché servono 3 settimane di silenzio in mezzo.
### Perché il salto è 4 e non 3
Per decidere sulla settimana $j$ serve sapere qualcosa che $\text{OPT}(j-1)$ da solo non dice. Per analogia diretta col WIS della nota 04, dove escludere il vicino significa saltare a $j-2$, si potrebbe scrivere
$$\text{OPT}(j) \overset{?}{=} \max\{\text{OPT}(j-1),\; v_j + \text{OPT}(j-2)\}$$
Un controesempio numerico la smentisce: con $n=3$ e $v_1=10,\,v_2=0,\,v_3=10$ questa formula darebbe $\text{OPT}(3) = \max\{10,\,10+10\} = 20$, permettendo di vincere sia in settimana $1$ sia in settimana $3$. Fra le due c'è però una sola settimana di pausa (la $2$), non tre: la combinazione $\{1,3\}$ non è ammissibile.
Se si vince in settimana $i$ e di nuovo in $i'$, le settimane strettamente fra le due sono $i' - i - 1$. Il vincolo richiede che siano $\ge 3$:
$$i' - i - 1 \ge 3 \quad\Longleftrightarrow\quad i' \ge i+4$$
Il salto corretto nella ricorrenza è quindi $j-4$, non $j-2$ né $j-3$.
### Esempio numerico
$n=6$, $v=[5,\,8,\,1,\,0,\,0,\,6]$.

| $j$ | $v_j$ | $\text{OPT}(j-1)$ | $v_j+\text{OPT}(j-4)$ | $\text{OPT}(j)$ |
|---|---|---|---|---|
| 1 | 5 | 0 | 5 | 5 |
| 2 | 8 | 5 | 8 | 8 |
| 3 | 1 | 8 | 1 | 8 |
| 4 | 0 | 8 | 0 | 8 |
| 5 | 0 | 8 | 5 | 8 |
| 6 | 6 | 8 | 14 | **14** |

La risposta è $\text{OPT}(6)=14$, ottenuta vincendo alle settimane $2$ e $6$ ($8+6$): fra loro cadono le settimane $3,4,5$, cioè tre settimane di pausa, il minimo richiesto.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Copiare il salto $j-2$ del WIS senza rileggere il vincolo | un controesempio piccolo come $v=[10,0,10]$ mostra una combinazione non ammissibile |
| Confondere "3 settimane di pausa" con "salto di 3 posizioni" | contare le settimane strettamente fra $i$ e $i'$: sono $i'-i-1 \ge 3$, quindi $i' \ge i+4$ |
| Scrivere quattro casi base separati invece della convenzione $\text{OPT}(k)=0$ per $k\le 0$ | verificare che la formula generale riproduca $\text{OPT}(1),\ldots,\text{OPT}(4)$ |
| Dichiarare la complessità dipendente dai valori $v_i$ o dalla costante $3$ | ogni cella costa $O(1)$ indipendentemente da $n$, dai $v_i$ e dalla larghezza del vincolo |
