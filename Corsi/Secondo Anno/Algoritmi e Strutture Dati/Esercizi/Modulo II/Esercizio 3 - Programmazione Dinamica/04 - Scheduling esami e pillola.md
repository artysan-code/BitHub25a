---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 04 — Scheduling esami e pillola
*(Esercizio 3 — compito del 24/09/2024 — 11 punti)*
> [!note] Traccia
> **Scenario.** La sessione di esami comincia domani. Ci sono $n$ giorni davanti a te, uno per esame, e non hai ancora cominciato a studiare — ma hai intenzione di rimetterti in riga. Meglio tardi che mai, del resto, no?
> **Regole.** Gli esami non sono tutti uguali. Per ogni $i$, l'esame del giorno $i$ vale $c_i$ crediti e richiede almeno $g_i$ giorni di studio consecutivi per prepararlo. Sai concentrarti su un solo esame alla volta: studi per un esame, lo sostieni, e solo dal giorno dopo cominci a studiare per il prossimo (il giorno dell'esame esci con il tuo miglior amico Walter Bianchi per festeggiare).
> **Richiesta.** Progetta un algoritmo di programmazione dinamica che calcoli il massimo numero di crediti acquisibili in questa sessione.
> **Bonus (per il punteggio pieno).** Da quando hai saputo che il matematico Paul Erdős faceva ampio uso di anfetamine per essere scientificamente più produttivo, ti sei procurato dal tuo amico Walter una pillola che dimezza i giorni di studio necessari per un esame: se la usi sull'esame del giorno $i$, il fabbisogno diventa $\lceil g_i/2 \rceil$ giorni. Hai una sola pillola, utilizzabile una sola volta. Progetta un algoritmo che calcoli il numero massimo di crediti ottenibili anche in questo caso.
## Pattern
**Weighted Interval Scheduling** travestito da calendario: ogni esame $j$ nasconde un intervallo $[j-g_j,\,j]$ di peso $c_j$, vedi [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Weighted Interval Scheduling|WIS]]. Nella parte bonus si aggiunge uno **stato usa-e-getta** (pillola disponibile/consumata) come secondo indice di condizione, pattern già visto in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#House Coloring (esercizio)|House Coloring]].
## Soluzione
### Sottoproblema
**Parte (a).**
$$\text{OPT}(j) = \text{massimo numero di crediti ottenibile considerando solo gli esami dei giorni } 1,\ldots,j$$
$j$ rappresenta fino a che giorno del calendario si guarda, non quanti esami sono stati presi. I sottoproblemi sono $n+1$: $j=0,1,\ldots,n$.
**Parte (b).**
$$\text{OPT}(j,t) = \text{massimo numero di crediti nei giorni } 1,\ldots,j \text{ con stato pillola } t\in\{0,1\}$$
$t=0$: la pillola non è stata usata nel prefisso $1,\ldots,j$; $t=1$: è già stata consumata. I sottoproblemi sono $2(n+1)$, ancora lineari: lo stato ha solo due configurazioni fissate, non una per sottoinsieme.
### Casi base
**Parte (a).**
$$\text{OPT}(0) = 0$$
Zero giorni di calendario disponibili, zero esami prendibili. È il caso base neutro di una massimizzazione (elemento neutro della somma); in una minimizzazione il neutro sarebbe $+\infty$, non $0$.
**Parte (b).**
$$\text{OPT}(0,0) = 0 \qquad \text{OPT}(0,1) = 0$$
Stesso ragionamento, indipendente dallo stato della pillola: con zero giorni non c'è ancora nulla su cui usarla.
### Ricorrenza
**Parte (a).** Per $j \ge 1$ l'esame $j$ è **prendibile** se $g_j \le j-1$, con predecessore $p(j) = j-g_j-1$.
**Non prendi l'esame $j$.** Vale sempre, prendibile o no.
$$\text{OPT}(j-1)$$
**Prendi l'esame $j$**, solo se $g_j \le j-1$. Guadagni $c_j$; il blocco $[j-g_j,\,j]$ è riservato; resta libero $1,\ldots,p(j)$.
$$c_j + \text{OPT}(p(j))$$
$$\text{OPT}(j) = \begin{cases} \text{OPT}(j-1) & \text{se } g_j > j-1 \\ \max\bigl\{\text{OPT}(j-1),\; c_j + \text{OPT}(j-g_j-1)\bigr\} & \text{se } g_j \le j-1 \end{cases}$$
**Parte (b).** Predecessore "con pillola": $g_j' = \lceil g_j/2 \rceil$, $p'(j) = j-g_j'-1$.
**Non prendi l'esame $j$.** Lo stato si propaga identico.
$$\text{OPT}(j-1,t)$$
**Prendi l'esame $j$ senza pillola**, se $g_j \le j-1$. Lo stato con cui si arriva a $j$ resta invariato.
$$c_j + \text{OPT}(p(j),t)$$
**Prendi l'esame $j$ usando la pillola**, solo per lo stato d'arrivo $t=1$ e se $g_j' \le j-1$. È l'unica mossa che cambia lo stato, da $0$ (pillola integra) a $1$ (consumata).
$$c_j + \text{OPT}(p'(j),0)$$
$$\text{OPT}(j,0) = \begin{cases} \text{OPT}(j-1,0) & \text{se } g_j > j-1 \\ \max\bigl\{\text{OPT}(j-1,0),\; c_j + \text{OPT}(j-g_j-1,0)\bigr\} & \text{se } g_j \le j-1 \end{cases}$$
$$\text{OPT}(j,1) = \max \begin{cases} \text{OPT}(j-1,1) \\ c_j + \text{OPT}(j-g_j-1,1) & \text{se } g_j \le j-1 \\ c_j + \text{OPT}(j-g_j'-1,0) & \text{se } g_j' \le j-1 \end{cases}$$
### Giustificazione
**Parte (a) — esaustività.** Per ogni giorno $j$ ci sono solo due possibilità rispetto alla soluzione ottima: l'esame $j$ vi compare oppure no. Non esiste una terza opzione, e le due non sono mai simultanee; se $j$ non è fattibile resta solo il primo caso, ma insieme coprono comunque tutte le possibilità.
**Parte (a) — sottostruttura ottima.** Prendere l'esame $j$ obbliga a riservare l'intero blocco $[j-g_j,\,j]$: ciò che resta disponibile sono i giorni $1,\ldots,p(j)$, su cui si applica ricorsivamente lo stesso problema. Se il residuo non fosse ottimo, sostituendolo con uno migliore si otterrebbero più crediti totali, contro l'ottimalità della soluzione di partenza — stesso argomento di taglia-e-incolla del WIS, vedi [[04 - Programmazione Dinamica I (Weighted Independent Set)#Il cuore dell'argomento: perché il residuo deve essere ottimo|nota 04]].
**Parte (b) — esaustività.** Fissato lo stato d'arrivo $t=1$ al giorno $j$, ci sono esattamente tre modi per arrivarci: non prendere $j$, prenderlo senza toccare la pillola perché già usata prima, oppure prenderlo proprio ora usando la pillola — l'unico caso che genera lo stato $1$ da zero. Per lo stato d'arrivo $t=0$ contano solo i primi due: il terzo è per costruzione incompatibile con $t=0$ come stato di arrivo.
**Parte (b) — sottostruttura ottima.** Stesso argomento della parte (a), esteso allo stato: il residuo ottimo va cercato nello stato corretto (invariato per i primi due casi, $t=0$ per il terzo). Se non fosse ottimo, sostituirlo migliorerebbe il totale, contro l'ipotesi di ottimalità.
### Ordine di calcolo
**Parte (a).** $j$ crescente da $1$ a $n$: poiché $p(j) = j-g_j-1 < j$ sempre, $\text{OPT}(p(j))$ è già stato calcolato quando si arriva a $j$.
**Parte (b).** $j$ crescente da $1$ a $n$; per ogni $j$ prima $\text{OPT}(j,0)$, poi $\text{OPT}(j,1)$. L'ordine fra i due non è in realtà vincolante — nessuno dei due dipende dall'altro alla stessa riga — ma calcolare $t=0$ per primo è la scelta naturale, perché il terzo caso di $\text{OPT}(j,1)$ legge $\text{OPT}(\cdot,0)$ a un giorno precedente.
### Risposta
**Parte (a).**
$$\text{OPT}(n)$$
Il sottoproblema che considera l'intero calendario.
**Parte (b).**
$$\max\bigl\{\text{OPT}(n,0),\; \text{OPT}(n,1)\bigr\}$$
Non si sa a priori se la soluzione ottima usi la pillola: si prende il massimo fra i due stati finali.
### Complessità
**Parte (a).** $\Theta(n)$ celle, $O(1)$ ciascuna: $p(j)$ è un'unica sottrazione, non serve ricerca binaria perché il calendario ordina già i job.
$$T(n) = \Theta(n)$$
Migliore del Weighted Interval Scheduling generico, $O(n \log n)$ per l'ordinamento e la ricerca binaria: qui quel lavoro è gratis, perché la traccia fornisce l'ordinamento.
**Parte (b).** $2(n+1)$ celle, $O(1)$ ciascuna.
$$T(n) = \Theta(n)$$
Il fattore costante dello stato (due configurazioni fisse a priori) non cambia l'ordine di grandezza: resta lineare, non pseudo-polinomiale come nel Knapsack, dove il secondo indice dipende dal *valore* di un dato numerico.
### Pseudocodice
**Parte (a).**
```pseudo
\begin{algorithm}
\caption{CreditiMax($n, c[1 \ldots n], g[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(0) \gets 0$
\For{$j \gets 1$ \To $n$}
  \If{$g[j] \leq j - 1$}
    \State $p \gets j - g[j] - 1$
    \State $\text{OPT}(j) \gets \max(\text{OPT}(j-1),\; c[j] + \text{OPT}(p))$
  \Else
    \State $\text{OPT}(j) \gets \text{OPT}(j-1)$
  \EndIf
\EndFor
\State \Return $\text{OPT}(n)$
\end{algorithmic}
\end{algorithm}
```
**Parte (b).**
```pseudo
\begin{algorithm}
\caption{CreditiMaxConPillola($n, c[1 \ldots n], g[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(0,0) \gets 0$
\State $\text{OPT}(0,1) \gets 0$
\For{$j \gets 1$ \To $n$}
  \State $\text{OPT}(j,0) \gets \text{OPT}(j-1,0)$
  \State $\text{OPT}(j,1) \gets \text{OPT}(j-1,1)$
  \If{$g[j] \leq j - 1$}
    \State $p \gets j - g[j] - 1$
    \State $\text{OPT}(j,0) \gets \max(\text{OPT}(j,0),\; c[j] + \text{OPT}(p,0))$
    \State $\text{OPT}(j,1) \gets \max(\text{OPT}(j,1),\; c[j] + \text{OPT}(p,1))$
  \EndIf
  \State $g' \gets \lceil g[j] / 2 \rceil$
  \If{$g' \leq j - 1$}
    \State $p' \gets j - g' - 1$
    \State $\text{OPT}(j,1) \gets \max(\text{OPT}(j,1),\; c[j] + \text{OPT}(p',0))$
  \EndIf
\EndFor
\State \Return $\max(\text{OPT}(n,0),\, \text{OPT}(n,1))$
\end{algorithmic}
\end{algorithm}
```
## Note di studio
### Riconoscere il pattern
Tre segnali nella traccia bastano: *"giorni davanti a te"* è una sequenza fissata con ordine temporale rigido; *"sai concentrarti su un solo esame alla volta"* è una scelta binaria che, se presa, esclude un blocco di giorni adiacenti; *"massimo numero di crediti"* è una massimizzazione su un peso per elemento. Sequenza + scelta binaria + esclusione di un intorno + peso da massimizzare è la firma del **Weighted Interval Scheduling**.
La traccia non presenta esplicitamente degli intervalli: li nasconde nella durata di studio. Se si sostiene l'esame $i$, il blocco consumato è i $g_i$ giorni di studio più il giorno $i$ stesso, cioè l'intervallo $[i-g_i,\,i]$ di peso $c_i$. Due esami $i<j$ sono compatibili quando i blocchi non si sovrappongono. Fatta questa traduzione, il problema è testualmente un WIS: job = esame, intervallo = blocco studio+esame, peso = crediti.
Per la parte bonus il problema di base resta lo stesso; si aggiunge una risorsa usa-e-getta (la pillola, una sola volta su tutta la sessione), lo stesso pattern di House Coloring, dove lo stato era il colore della casa precedente.
### Perché la pillola richiede un secondo indice
Nel WIS su calendario un solo indice $\text{OPT}(j-1)$ basta perché il salto all'indietro $p(j) = j-g_j-1$ è calcolabile in $O(1)$ dato $j$ — è già ordinato dal calendario, senza bisogno della ricerca binaria della [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Struttura della soluzione ottima|nota 05]].
Con la pillola questo non basta più: decidere sull'esame $j$ richiede sapere se la pillola è ancora disponibile, perché un esame futuro con $g_k$ enorme potrebbe diventare prendibile solo grazie a lei. Tenere due algoritmi separati e scegliere il migliore alla fine non funziona, perché "dove uso la pillola" e "quali esami prendo" sono decisioni intrecciate: usarla su un esame ne cambia la compatibilità con gli altri.
La soluzione è far viaggiare l'informazione **dentro** la tabella: un secondo indice $t \in \{0,1\}$, con solo due configurazioni. Non è un indice "di quantità" come la capacità dello zaino, ma "di condizione" — per questo resta lineare invece di diventare pseudo-polinomiale.
### Esempio numerico
$n=4$, con $c = [5,\,3,\,8,\,10]$ e $g = [0,\,2,\,1,\,3]$.

| $j$ | $g_j$ | fattibile ($g_j \le j-1$) | $p(j)$ | $\text{OPT}(j)$ |
|---|---|---|---|---|
| 1 | 0 | sì | 0 | $\max(0,\,5+0)=5$ |
| 2 | 2 | no | — | $5$ |
| 3 | 1 | sì | 1 | $\max(5,\,8+5)=13$ |
| 4 | 3 | sì | 0 | $\max(13,\,10+0)=13$ |

Senza pillola la risposta è $\text{OPT}(4)=13$ (esami $1$ e $3$). Con la pillola, usarla sull'esame $4$ porta $g_4'=\lceil 3/2 \rceil=2$ e $p'(4)=1$: $\text{OPT}(4,1) = \max\bigl(13,\; 10+\text{OPT}(1,0)\bigr) = \max(13,\,15)=15$, prendendo l'esame $1$ e l'esame $4$ con la pillola. La risposta finale è $\max(13,15)=15$: la pillola conviene.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Confondere l'indice $j$ con il numero di esami presi | $\text{OPT}(j)$ scorre sui giorni di calendario, non sugli esami: se ti ritrovi a "contare quanti esami mancano" hai perso di vista cosa rappresenta l'indice |
| Calcolare $p(j) = j - g_j$ invece di $j - g_j - 1$ | il blocco occupa $j-g_j,\ldots,j-1$ più il giorno $j$; l'ultimo giorno libero è $j-g_j-1$, non il primo giorno del blocco |
| Dimenticare la condizione $g_j \le j-1$ | un esame non fattibile non è mai prendibile: ometterla produce indici negativi in tabella |
| Scrivere il caso "pillola" anche dentro $\text{OPT}(j,0)$ | per definizione $t=0$ significa pillola non ancora usata nel prefisso: usarla su $j$ produce $t=1$, e il risultato va scritto in quella cella, non in questa |
