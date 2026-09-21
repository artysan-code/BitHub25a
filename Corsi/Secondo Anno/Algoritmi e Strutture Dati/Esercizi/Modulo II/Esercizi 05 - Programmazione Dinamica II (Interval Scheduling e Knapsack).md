---
tags:
  - algoritmi
  - dp
  - esercizi
nota: "[[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]"
---
# Esercizi — Programmazione Dinamica II
Palestra della nota [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]]. Ogni item riporta la traccia verbatim con data, esercizio e sotto-punto; la risposta modello sta in un callout richiudibile.

> [!warning] Tutti e quattro gli item sono in formato Clementi
> Vengono da appelli **2022–2023**, quando il Modulo II era tenuto dal prof. Clementi e l'Esercizio 1 poteva chiedere *teoria* sulla programmazione dinamica. Nella configurazione attuale la DP compare **solo** in Esercizio 3, e sempre come progettazione su un problema inedito — per quella si va in [[Esercizi 04 - Programmazione Dinamica]].
> Non sono quindi simulazione dello scritto. Sono però un **controllo di precisione** sulle definizioni: se sai rispondere, la tua definizione di sottoproblema regge, ed è esattamente ciò che serve al passo 1 dell'Esercizio 3. E sono pienamente esigibili **all'orale**.
## Weighted Interval Scheduling
### Riduzione a WIS
> [!question] Domanda d'esame — Riduzione a WIS
> **D:** *(Vero o Falso)* «Trasformando opportunamente l'istanza I, è possibile darla in input all'algoritmo di Programmazione Dinamica per il Weighted Interval Scheduling ed ottenere la soluzione ottima per I.» *(traccia 12/09/2023 · Es. 1 n. 2 · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Vero.
>
> **Perché.** La tecnica è la **riduzione**: si trasforma l'istanza $I$ in un'istanza equivalente di WIS (job con intervalli $[s_j, f_j]$ e pesi $w_j$) tale che la soluzione ottima calcolata dall'algoritmo PD di WIS sull'istanza trasformata corrisponda esattamente alla soluzione ottima di $I$.
>
> **Esempio.** L'Interval Scheduling **non pesato** (vedi il confronto a inizio sezione): ponendo $w_j = 1$ per ogni job, l'equazione di Bellman $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, w_j + \text{OPT}(p(j))\}$ diventa $\text{OPT}(j) = \max\{\text{OPT}(j-1),\, 1 + \text{OPT}(p(j))\}$, che calcola la cardinalità massima di un sottoinsieme di job compatibili — esattamente l'ottimo del problema non pesato.
>
> **Osservazione.** In generale, per mostrare che un problema $P$ si risolve con l'algoritmo PD di WIS basta esibire una **trasformazione polinomiale** dell'istanza di $P$ in un'istanza di intervalli pesati che preservi il valore ottimo: è lo schema di riduzione che estende un algoritmo esistente a problemi apparentemente diversi.
## Knapsack 0/1
### Significato di OPT(j-1, w-wj)
> [!question] Domanda d'esame — Significato di OPT(j-1, w-wj)
> **D:** «B) Prefissato un qualsiasi ordinamento degli items {Ij : j= 1,...,n}, la funzione OPT(j-1,w-wj) calcolata da PD è uguale al valore ottimo relativo alla sottoistanza \<I1,...,Ij-1; w- wj \> ? Se SI, in che modo viene utilizzato questo valore nell'algoritmo PD? Se NO, quale/i valore/i della funzione OPT(j,w) vengono utilizzati da PD al generico passo ricorsivo?» *(traccia 14/09/2022 · Es. 1.2 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Sì.
>
> **Perché.** Per definizione $\text{OPT}(j,w)$ è il valore ottimo della sottoistanza formata dai primi $j$ item con capacità $w$ (vedi la definizione data in questa sezione); sostituendo $j \to j-1$ e $w \to w-w_j$, $\text{OPT}(j-1, w-w_j)$ è — sempre per definizione — il valore ottimo della sottoistanza $\langle I_1,\ldots,I_{j-1}; w-w_j \rangle$.
>
> **Uso nell'algoritmo.** Questo valore compare nel passo ricorsivo dell'equazione di Bellman $\text{OPT}(j,w) = \max\{\text{OPT}(j-1,w),\, v_j + \text{OPT}(j-1, w-w_j)\}$, e corrisponde al **Caso 2**: il ramo in cui l'item $I_j$ **viene incluso** nella soluzione ottima, per cui si somma $v_j$ al valore ottimo ottenibile dai primi $j-1$ item con la capacità residua $w-w_j$ rimasta dopo aver "pagato" il peso $w_j$.
>
> **Condizione.** Il termine è valido solo se $w_j \le w$; altrimenti l'item non entra e $\text{OPT}(j,w) = \text{OPT}(j-1,w)$.
### Cosa rappresenta M(j,w)
> [!question] Domanda d'esame — Cosa rappresenta M(j,w)
> **D:** «C) Nella versione iterativa dell'algoritmo PD, l'entrata della matrice M(j,w) contiene la soluzione ottima formata da un qualsiasi sottoinsieme S di {I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) } tale che: |S| <= j e Σ_(k∈S) vk = w ?» *(traccia 14/09/2022 · Es. 1.3 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** No.
>
> **Errore 1 — l'insieme di partenza.** $M(j,w)$ è definita sui **primi $j$ item** $\{I_1,\ldots,I_j\}$, non su un sottoinsieme $S$ qualunque estratto da **tutta** la lista $\{I_1,\ldots,I_n\}$ con $|S|\le j$: un sottoinsieme di $j$ item presi da posizioni arbitrarie (es. $\{I_2, I_7\}$ con $j=5$) non è ammissibile per $M(j,w)$, che considera solo $S \subseteq \{I_1,\ldots,I_j\}$.
>
> **Errore 2 — si sommano i valori invece dei pesi.** Il vincolo che definisce l'ammissibilità riguarda i **pesi**, $\sum_{k \in S} w_k$, non i valori $\sum_{k \in S} v_k$. I valori si sommano nella *funzione obiettivo*, quella che si massimizza; i pesi nel *vincolo*, quello che si rispetta. Scambiarli significa scambiare ciò che si ottimizza con ciò che ci si può permettere.
>
> **Errore 3 — l'uguaglianza al posto della disuguaglianza.** Deve valere $\le w$, non $= w$: la soluzione ottima **non satura** necessariamente lo zaino. Sull'istanza della demo (slide 47) si ha $\text{OPT}(5,4) = 7$, realizzato da $\{1,2\}$ che pesa $1+2 = 3 < 4$; anzi, in quell'istanza *nessun* sottoinsieme pesa esattamente 4, quindi con l'uguaglianza la cella non sarebbe nemmeno definita.
>
> **Definizione corretta.** Coerente con quella data in questa nota:
> $$M(j,w) = \max\Bigl\{\sum_{k\in S} v_k \;:\; S \subseteq \{I_1,\ldots,I_j\},\; \sum_{k \in S} w_k \le w\Bigr\}$$
### K è in P?
> [!question] Domanda d'esame — K è in P?
> **D:** «ESERCIZIO 1. Si consideri il problema Knapsack (K) e si consideri l'algoritmo ottimale PD per K basato sulla Programmazione Dinamica. Si consideri una generica istanza X = \<I1=(w1,v1), ..., Ij=(wj,vj) , ..., In=(wn,vn) ; W\> di K, dove M = max{wj, vj, W : j=1,...,n}. Si risponda alle seguenti domande con al massimo quattro righe negli spazi appropriati, dando delle brevi spiegazioni. A) L'esistenza di un qualsiasi algoritmo che impiega tempo Θ(n^2 log^24(M)) mostrerebbe che il problema K è nella classe P?» *(traccia 14/09/2022 · Es. 1.1 · «al massimo quattro righe» · formato Clementi)*

> [!info]- Risposta modello
> **Risposta.** Sì.
>
> **Perché.** $\Theta(n^2 \log^{24} M)$ è polinomiale nella **dimensione dell'input**, che è $O(n \log M)$ bit (peso, valore e capacità sono codificati in binario, quindi ciascuno occupa $O(\log M)$ bit). Un tempo $\Theta(n^2 \log^{24} M)$ è polinomiale sia in $n$ sia in $\log M$, cioè nella lunghezza della codifica dell'istanza: un tale algoritmo classificherebbe $K$ in P.
>
> **Confronto con la DP standard.** L'algoritmo PD di questa nota ha complessità $\Theta(nW)$: è polinomiale nel *valore* $W$ (quindi in $M$), non nella sua *dimensione in bit* $\log W$ — è **pseudo-polinomiale**, non polinomiale (vedi il riquadro sulla pseudo-polinomialità qui sopra).
>
> **Distinzione.** È esattamente quella tra $\text{poly}(M)$ (pseudo-polinomiale, come $\Theta(nW)$) e $\text{poly}(\log M)$ (polinomiale in senso proprio, come l'ipotetico $\Theta(n^2 \log^{24} M)$).
>
> ⏱️ **Se la traccia dà 4 righe**: rispondi Sì e giustifica in una riga che $\Theta(n^2\log^{24}M)$ è polinomiale in $n$ e $\log M$ — cioè nella dimensione in bit dell'istanza, $O(n\log M)$ — quindi metterebbe $K$ in P (1-2 righe); chiudi con il confronto secco «a differenza della PD standard, che è $\Theta(nW)$ e quindi solo pseudo-polinomiale» (1-2 righe). **Non va mai omessa** la distinzione fra dimensione in bit dell'istanza e valore numerico dei dati: è il concetto su cui verte l'intera domanda.
