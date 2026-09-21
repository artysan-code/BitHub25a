---
tags:
  - algoritmi
  - dp
slide: ["04"]
capitolo: "Kleinberg-Tardos cap. 6"
---
# Programmazione Dinamica I — Principi e Weighted Independent Set
La **programmazione dinamica** risolve un problema definendo una famiglia piccola di sottoproblemi, esprimendo la soluzione di ciascuno in funzione di sottoproblemi più piccoli e riempiendo una tabella nell'ordine giusto. Questa nota introduce la tecnica sul caso di studio del **Weighted Independent Set su cammino** e ne ricava i quattro passi generali, che sono il telaio di ogni Esercizio 3. Gli Esercizio 3 di progettazione delle tracce recenti stanno nella palestra [[Palestra - Programmazione Dinamica]]; i problemi di DP successivi sono in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]] e [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].
## L'idea, prima della tecnica
Prima di qualunque definizione, guardiamo **il fenomeno** che la programmazione dinamica sfrutta. Prendiamo un problema qualunque risolto per ricorsione — diciamo il calcolo di $F(6)$, il sesto numero di Fibonacci, con la ricorsione diretta $F(j) = F(j-1) + F(j-2)$. Disegniamo l'albero delle chiamate:
```
                          F(6)
                 ┌──────────┴──────────┐
               F(5)                   F(4)
          ┌─────┴─────┐          ┌─────┴─────┐
        F(4)         F(3)      F(3)         F(2)
     ┌───┴───┐     ┌──┴──┐   ┌──┴──┐
   F(3)     F(2) F(2)  F(1) F(2)  F(1)
  ┌─┴─┐
F(2)  F(1)
```

Contiamo quante volte compare ciascuna chiamata:

| Chiamata | Quante volte viene calcolata |
|---|---|
| $F(5)$ | 1 |
| $F(4)$ | 2 |
| $F(3)$ | 3 |
| $F(2)$ | 5 |
| $F(1)$ | 3 |

In totale **15 chiamate** per calcolare qualcosa che ha soltanto **6 valori distinti**. E il rapporto peggiora in fretta: per $F(30)$ le chiamate diventano $1\,664\,079$, sempre per 30 valori distinti. Stiamo ricalcolando da zero, milioni di volte, risposte che avevamo già trovato.

Questo è il punto — e vale la pena dirlo nel modo più diretto possibile:

> [!quote] L'idea della programmazione dinamica
> Se la ricorsione risolve **un numero piccolo di sottoproblemi distinti**, ma li incontra **un numero enorme di volte**, allora conviene risolverne ciascuno **una volta sola** e conservare il risultato.
> Il costo dell'algoritmo smette di essere «quanti nodi ha l'albero di ricorsione» e diventa «quanti sottoproblemi distinti esistono, per il costo di risolverne uno».

Da questa frase discende tutto il resto. Il lavoro difficile, in ogni problema di DP, non è memorizzare i risultati — quello è banale, è un array. Il lavoro difficile è **capire quali sono i sottoproblemi**, e dimostrare che la soluzione ottima del problema grande si costruisce a partire dalle soluzioni ottime di quelli piccoli.
### Le due condizioni che servono
Perché la strategia funzioni servono **entrambe** queste proprietà. Se ne manca una, la DP non si applica.

| Proprietà | Cosa significa | Cosa succede se manca |
|---|---|---|
| **Sottostruttura ottima** | La soluzione ottima del problema contiene al proprio interno le soluzioni ottime dei sottoproblemi | Non puoi costruire l'ottimo grande da quelli piccoli: la ricorrenza sarebbe sbagliata |
| **Sottoproblemi sovrapposti** | La ricorsione incontra gli stessi sottoproblemi ripetutamente | La memorizzazione non serve a niente: non c'è nulla da riusare |

> [!warning] È qui che si distingue la DP dal divide et impera
> Anche il divide et impera spezza il problema in sottoproblemi. La differenza è la **seconda** condizione: in Merge Sort i due sottoproblemi (metà sinistra e metà destra) sono **disgiunti**, non si sovrappongono mai, e memorizzarli non darebbe alcun vantaggio. Nella DP i sottoproblemi si **accavallano** — ed è esattamente quella ridondanza che la tecnica trasforma in guadagno.
> All'orale è una domanda frequente: la risposta corretta non è «la DP usa una tabella», ma «la DP si applica quando i sottoproblemi si sovrappongono, e la tabella serve a non ricalcolarli».

Con questo in testa, il resto della nota è l'applicazione dell'idea a un problema concreto. La formalizzazione in quattro passi la trovi più avanti, in [[#Principi generali della programmazione dinamica]]: leggila **dopo** aver visto l'esempio, non prima.
## Il problema: Insieme Indipendente di Peso Massimo su grafo a cammino
> [!quote] Definizione — Insieme Indipendente
> Dato un grafo $G = (V, E)$, un **insieme indipendente** è un sottoinsieme $S \subseteq V$ tale che nessuna coppia di nodi in $S$ è unita da un arco, ovvero:
> $$\forall\, u, v \in S \implies (u, v) \notin E$$

Il problema che analizziamo in questa nota è una variante pesata su **grafi a cammino** (path graph).

> [!quote] Definizione — Weighted Independent Set (WIS) su cammino
> **Input**: un cammino $G$ su $n$ nodi $v_1, v_2, \ldots, v_n$, dove ogni nodo $v_i$ ha peso $w_i \geq 0$.
> **Goal**: trovare un insieme indipendente $S^*$ tale che il peso totale
> $$w(S) = \sum_{v_i \in S} w_i$$
> sia **massimo**.

**Esempio di riferimento** (usato in tutta la nota):

![[dp1_insieme_ind_migliore.png]]
Il cammino di riferimento, pesi $1, 4, 8, 4, 3, 10$, con in rosso l'insieme ottimo $\{v_1, v_3, v_6\}$ di peso $19$. Nota che l'ottimo **non** prende semplicemente i nodi in posizione pari o dispari, e nemmeno tutti i più pesanti: salta $v_4$ e $v_5$ per poter tenere insieme $v_3$ e $v_6$. (slide 8)

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
Rendiamo esplicito l'algoritmo, perché è lì che si vede il difetto.
1. **Criterio di ordinamento**: si ordinano i nodi per **peso decrescente**, $w$ dal più grande al più piccolo.
2. **Comparazione e scelta**: si scorre l'elenco in quest'ordine e si prende il nodo corrente **se non è adiacente a nessun nodo già preso**; altrimenti lo si scarta. Una volta preso o scartato, un nodo non si rimette più in discussione.

Sull'esempio di riferimento funziona: l'ordine è $v_6(10), v_3(8), v_2(4), v_4(4), v_5(3), v_1(1)$, si prendono $v_6$, poi $v_3$ (non adiacente a $v_6$), si scartano $v_2, v_4, v_5$ perché adiacenti a qualcosa di già preso, e infine si prende $v_1$: risultato $\{v_1, v_3, v_6\} = 19$, che è proprio l'ottimo.

Ora l'istanza a quattro nodi di pesi $1, 4, 5, 4$. L'ordine diventa $v_3(5), v_2(4), v_4(4), v_1(1)$:
- si prende $v_3$, perché 5 è il peso più alto;
- $v_2$ e $v_4$ vengono **entrambi** scartati, perché adiacenti a $v_3$;
- si prende $v_1$, che è libero.

Risultato $\{v_1, v_3\}$, peso $6$; l'ottimo è $\{v_2, v_4\}$, peso $8$. Il greedy **fallisce**.

![[dp1-controesempio-greedy.png]]
In rosso i nodi scelti. A sinistra la soluzione greedy ($1 + 5 = 6$), a destra l'ottima ($4 + 4 = 8$): prendere il nodo più pesante al centro brucia entrambi i 4 che gli stanno accanto. (slide 15)

**Perché sbaglia.** Il difetto non è il criterio scelto, è la **grandezza che il criterio confronta**. Ordinando per peso, l'algoritmo mette a confronto *un nodo contro un altro nodo*: $5 > 4$, quindi prende il 5. Ma prendere $v_3$ non costa «rinunciare a $v_2$», costa **rinunciare a $v_2$ e a $v_4$ insieme**, perché entrambi gli sono adiacenti. Il confronto che deciderebbe correttamente è quindi
$$w_3 = 5 \quad\text{contro}\quad w_2 + w_4 = 8$$
e nessun ordinamento dei singoli pesi può farlo emergere, perché la quantità $w_2 + w_4$ non compare da nessuna parte nella lista ordinata. Il greedy vede sempre e solo *il prossimo nodo*, mai *ciò che quel nodo esclude*.

> [!warning] Il greedy non funziona per WIS
> Non esiste alcun criterio di scelta locale che garantisca di trovare l'ottimo globale per il Weighted Independent Set — e non serve cercarne uno migliore: il problema è strutturale, sta nel confrontare un nodo con un altro nodo invece che con la somma di ciò che esclude.
> È utile ricordare **il contrasto con l'Interval Scheduling non pesato** ([[01 - Greedy e Interval Scheduling]]): lì il greedy *è* ottimo, perché scegliere il job che finisce prima non pregiudica mai nulla — lascia la massima libertà residua, e questo si dimostra con l'argomento *greedy stays ahead*. Qui invece ogni scelta ne preclude altre di valore arbitrariamente maggiore, e nessun argomento del genere può funzionare. È la domanda d'orale tipica: *perché il greedy va bene lì e non qui?*
### Divide et impera
L'idea è dividere il cammino a metà, risolvere ricorsivamente il WIS su ciascuna metà e poi ricombinare. Il problema è che la **ricombinazione è difficile**: un nodo selezionato nell'ultima posizione della metà sinistra e uno nella prima posizione della metà destra potrebbero essere adiacenti, generando un conflitto. Risolverlo in modo generico riporta alla complessità esponenziale.

> [!info] Diagnosi comune
> Sia il greedy che il divide et impera falliscono perché non comprendono la **struttura globale del problema**: bisogna ragionare su *come* è fatta la soluzione ottima in termini di soluzioni ottime di sottoproblemi più piccoli.
## Struttura della soluzione ottima
Il passaggio critico della programmazione dinamica è ragionare sulla struttura della soluzione ottima. Questo porta poi a identificare i sottoproblemi giusti.
### Il metodo: interrogare la soluzione ottima invece di costruirla
Il cambio di prospettiva è questo: non si tenta di costruire $S^*$ passo dopo passo — è ciò che fa il greedy, e abbiamo visto che fallisce. Si **assume** che una soluzione ottima esista, la si tratta come un oggetto dato di cui non conosciamo il contenuto, e le si pone una **domanda binaria** su un singolo elemento.

La domanda è: *l'ultimo nodo $v_n$ appartiene a $S^*$?* Non ne conosciamo la risposta, ma sappiamo con certezza che le risposte possibili sono **due sole**, e che una delle due è vera. È questo il senso di «casi esaustivi e mutuamente esclusivi»: non è un risultato da dimostrare, è la garanzia che l'analisi per casi non lasci scoperta alcuna possibilità.

Il guadagno è che **in entrambi i casi ciò che resta da determinare è un'istanza dello stesso problema, su un cammino più corto**. Da qui la ricorsione, e con essa i sottoproblemi.
### Perché proprio l'ultimo nodo
La scelta non è arbitraria: interrogare $v_n$ è l'unica mossa che lascia come residuo un **prefisso**, cioè ancora un cammino.

Se si interrogasse un nodo interno $v_i$, il residuo sarebbe costituito da **due** cammini separati, $v_1 \ldots v_{i-1}$ e $v_{i+1} \ldots v_n$. I sottoproblemi da considerare diventerebbero tutti i possibili *segmenti* $v_i \ldots v_j$, che sono $\Theta(n^2)$. Interrogando l'ultimo nodo, invece, i sottoproblemi sono soltanto gli $n$ prefissi $G_1, G_2, \ldots, G_n$: è esattamente da questa scelta che discende il costo lineare dell'algoritmo.
### I due casi
Sia $S^*$ **una** soluzione ottima (un insieme indipendente di peso massimo di $G$) — «una» e non «la», perché l'ottimo **non è unico**: già sul cammino $1 - 1$ sia $\{v_1\}$ sia $\{v_2\}$ hanno peso massimo. Quello che è unico è il **valore** ottimo, ed è infatti il valore che la DP calcola.

Nel seguito si assume $n \geq 2$, in modo che il nodo $v_{n-1}$ esista. Il caso $n = 1$ è banale e non richiede alcuna ricorsione: l'unico insieme indipendente non vuoto è $\{v_1\}$ e il valore ottimo è $w_1$; coerentemente, l'algoritmo lo tratterà come **caso base**.

**Caso 1** — $v_n \notin S^*$

Consideriamo $G' = G - \{v_n\}$ (il sottocammino sui primi $n-1$ nodi).

**Tesi**: $S^*$ è una soluzione ottima anche per $G'$.

**Dimostrazione (per assurdo).**
1. Anzitutto $S^*$ è **ammissibile** per $G'$: per ipotesi di caso $v_n \notin S^*$, quindi $S^* \subseteq \{v_1, \ldots, v_{n-1}\}$, ed è indipendente in $G'$ perché lo è in $G$ e $G'$ ha meno archi.
2. Supponiamo per assurdo che $S^*$ **non** sia ottima per $G'$: esiste allora un insieme indipendente $S$ di $G'$ con $w(S) > w(S^*)$.
3. Tale $S$ è indipendente **anche in $G$**. Infatti gli archi di $G$ che non compaiono in $G'$ sono soltanto quelli incidenti a $v_n$, cioè il solo arco $\{v_{n-1}, v_n\}$; ma $v_n \notin S$, perché $S$ è fatto di nodi di $G'$. Nessun arco di $G$ ha dunque entrambi gli estremi in $S$.
4. Quindi $S$ è un insieme indipendente **di $G$** con $w(S) > w(S^*)$.
5. Questo contraddice l'ottimalità di $S^*$ per $G$.
6. L'assurdo nasce dall'ipotesi al passo 2: dunque $S^*$ è ottima per $G'$. $\square$

![[dp1_caso_1.png]]
Caso 1: il riquadro $G'$ racchiude $v_1, \ldots, v_{n-1}$, mentre $v_n$ resta fuori. Il sottoproblema è tutto ciò che sta dentro il riquadro. (slide 20)

**Caso 2** — $v_n \in S^*$

Poiché $S^*$ è un insieme indipendente e $v_n \in S^*$, il vicino $v_{n-1}$ è **forzatamente escluso**: $v_{n-1} \notin S^*$.
Consideriamo $G'' = G - \{v_{n-1}, v_n\}$ (il sottocammino sui primi $n-2$ nodi).

**Tesi**: $S^* \setminus \{v_n\}$ è una soluzione ottima per $G''$.

**Dimostrazione (per assurdo).**
1. Anzitutto $S^* \setminus \{v_n\}$ è **ammissibile** per $G''$: contiene solo nodi fra $v_1, \ldots, v_{n-2}$ — si è tolto $v_n$, e $v_{n-1}$ non c'era già — ed è indipendente perché sottoinsieme di $S^*$: se nessuna coppia di nodi di $S^*$ è unita da un arco, a maggior ragione ciò vale per una coppia presa in un suo sottoinsieme.
2. Supponiamo per assurdo che non sia ottima per $G''$: esiste allora un insieme indipendente $S$ di $G''$ con $w(S) > w(S^* \setminus \{v_n\})$.
3. Costruiamo il candidato $S \cup \{v_n\}$ e verifichiamo che sia indipendente **in $G$**, distinguendo le due possibili coppie di nodi.
	- *Coppie interne a $S$*: gli archi di $G$ che non compaiono in $G''$ sono soltanto quelli incidenti a $v_{n-1}$ o a $v_n$; poiché $S \subseteq \{v_1, \ldots, v_{n-2}\}$, nessuna coppia di $S$ è toccata da tali archi, e $S$ resta indipendente anche come sottoinsieme di $G$.
	- *Coppie formate da $v_n$ e da un nodo di $S$*: l'unico vicino di $v_n$ in $G$ è $v_{n-1}$ (siamo in $n \geq 2$), che non è un nodo di $G''$ e quindi non appartiene a $S$.
	Nessuna coppia di nodi adiacenti compare dunque in $S \cup \{v_n\}$.
4. Ne calcoliamo il peso, usando il passo 2:
$$w(S \cup \{v_n\}) = w(S) + w_n > w(S^* \setminus \{v_n\}) + w_n = w(S^*)$$
5. Quindi $S \cup \{v_n\}$ è un insieme indipendente di $G$ di peso strettamente maggiore di $w(S^*)$: contraddizione con l'ottimalità di $S^*$.
6. L'assurdo nasce dall'ipotesi al passo 2: dunque $S^* \setminus \{v_n\}$ è ottima per $G''$. $\square$

![[dp1_caso_2.png]]
Caso 2: $v_n$ è in rosso perché è nella soluzione; $v_{n-1}$ è forzatamente escluso (freccia in basso) perché adiacente a $v_n$. Il riquadro $G''$ si ferma a $v_{n-2}$ — il salto di **due** posizioni che diventerà $\text{OPT}[j-2]$ nella ricorrenza. (slide 21)
### Il cuore dell'argomento: perché il residuo deve essere ottimo
Entrambe le dimostrazioni sopra hanno la stessa forma, ed è la forma ricorrente di tutta la programmazione dinamica — è nota come **argomento di taglia-e-incolla** (*cut and paste*). Conviene vederla su numeri concreti prima di fidarsi della versione formale.

Supponiamo che qualcuno proponga come ottima, sull'istanza di riferimento, la soluzione $\{v_6, v_1\}$, di peso $10 + 1 = 11$. Il nodo $v_6$ è incluso, quindi siamo nel Caso 2: il residuo $\{v_1\}$ è un insieme indipendente su $G'' = v_1 \ldots v_4$, e vale $1$. Ma su $v_1 \ldots v_4$ il meglio ottenibile è $\{v_1, v_3\}$, che vale $9$. Poiché né $v_1$ né $v_3$ sono adiacenti a $v_6$, si può **sostituire** il residuo scadente con quello ottimo:
$$\{v_6\} \cup \{v_1, v_3\} = 19 \;>\; 11$$
La soluzione proposta non era dunque ottima. Lo stesso ragionamento si applica a qualunque soluzione il cui residuo non sia ottimo, e questo dimostra la proprietà: **se $S^*$ è ottima, ogni suo residuo è a sua volta ottimo per il proprio sottoproblema**, perché altrimenti lo si potrebbe scambiare con uno migliore ottenendo un peso complessivo maggiore — in contraddizione con l'ottimalità di $S^*$.

> [!warning] Dove lo scambio poteva rompersi
> La sostituzione è lecita **solo perché il residuo non può contenere $v_{n-1}$**: è definito su $G''$, da cui $v_{n-1}$ è già stato rimosso. Se il Caso 2 si fosse ridotto a $G' = G - \{v_n\}$ togliendo un nodo solo, il residuo ottimo di $G'$ potrebbe contenere $v_{n-1}$, e riunirlo a $v_n$ produrrebbe due nodi adiacenti — un insieme **non indipendente**, cioè nemmeno una soluzione ammissibile. È per questo che il Caso 2 rimuove *due* nodi: non è un dettaglio tecnico, è la condizione che rende valido l'argomento di scambio.

> [!quote] Proprietà — Sottostruttura ottima del WIS
> Ogni insieme indipendente di peso massimo per $G$ è di una di queste due forme:
> 1. un insieme indipendente di peso massimo per $G' = G - \{v_n\}$, oppure
> 2. $\{v_n\}$ unito a un insieme indipendente di peso massimo per $G'' = G - \{v_{n-1}, v_n\}$.
>
> Sui **valori** — che sono unici, a differenza degli insiemi che li realizzano — la proprietà si scrive:
> $$w(S^*) = \max\bigl\{\,w(\text{OPT}(G')),\;\; w_n + w(\text{OPT}(G''))\,\bigr\}$$
> e $S^*$ è il candidato che realizza questo massimo (se pareggiano, entrambi vanno bene).

Non sappiamo in quale dei due casi ci si trovi, ma sappiamo calcolarli entrambi: si calcolano e si tiene il maggiore. Sull'istanza di riferimento ($1, 4, 8, 4, 3, 10$):

| Caso | Espressione | Valore | Insieme che lo realizza |
|---|---|---|---|
| 1 — $v_6$ escluso | $w(\text{OPT}(v_1 \ldots v_5))$ | $12$ | $\{v_1, v_3, v_5\}$ |
| 2 — $v_6$ incluso | $w_6 + w(\text{OPT}(v_1 \ldots v_4)) = 10 + 9$ | $\mathbf{19}$ | $\{v_6\} \cup \{v_1, v_3\}$ |

Il massimo è $19$, e la soluzione ottima è $\{v_1, v_3, v_6\}$. Si noti che questa è la ricorrenza $\text{OPT}[j] = \max\{\text{OPT}[j-1],\; w_j + \text{OPT}[j-2]\}$ già in forma definitiva: il termine $\text{OPT}[j-1]$ è il Caso 1, il termine $w_j + \text{OPT}[j-2]$ è il Caso 2, e l'indice $j-2$ è precisamente $v_{j-1}$ che si è stati costretti a escludere.

→ **Palestra**: [[Palestra - Programmazione Dinamica#Sottostruttura ottima del WIS|sottostruttura ottima del WIS — domanda costruita]]
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

che è quella di fibonacci2 (vedere [[01 - Il Problema di Fibonacci]] e [[03 - Equazioni di Ricorrenza]]). La soluzione è $T(n) = \Theta(\phi^n)$, **esponenziale**: la stessa di Fibonacci ricorsivo.

Ma non fermiamoci alla ricorrenza: guardiamo *cosa* sta facendo l'algoritmo. Chiamiamo $\text{OPT}(j)$ la chiamata ricorsiva sul prefisso $G_j$, e sviluppiamo l'albero per il nostro esempio a 6 nodi:
```
                        OPT(6)
                ┌──────────┴──────────┐
             OPT(5)                 OPT(4)  ←── 2ª volta
          ┌─────┴─────┐          ┌─────┴─────┐
       OPT(4)      OPT(3)     OPT(3)      OPT(2)
     ┌───┴───┐    ┌──┴──┐    ┌──┴──┐        ↑
  OPT(3)  OPT(2) OPT(2) OPT(1) OPT(2) OPT(1)  ricalcolo
   ┌─┴─┐     ↑      ↑            ↑
OPT(2) OPT(1)└──────┴────────────┴── stessa identica chiamata, 5 volte
```
Il conteggio è impietoso:

| Sottoproblema | Volte che viene calcolato |
|---|---|
| $\text{OPT}(5)$ | 1 |
| $\text{OPT}(4)$ | 2 |
| $\text{OPT}(3)$ | 3 |
| $\text{OPT}(2)$ | 5 |
| $\text{OPT}(1)$ | 3 |
| **totale chiamate** | **15** |

**15 chiamate per 6 sottoproblemi diversi.**

![[dp1_ricorsione_esponenziale.png]]
La slide che chiude il ragionamento: la proprietà di sottostruttura nei due casi, e sotto il costo dell'«idea forse folle» di calcolarli entrambi ricorsivamente. La ricorrenza è $T(n) = T(n-1) + T(n-2) + O(1)$ — **quella di Fibonacci** — quindi $T(n) = \Theta(\phi^n)$, esponenziale. Il punto da portarsi dietro: la ricorrenza è giusta, è il *modo di calcolarla* a essere sbagliato. E $\text{OPT}(2)$ — che vale sempre e comunque $\max\{1, 4\} = 4$ — viene ricalcolato da capo cinque volte. Con $n = 30$ le chiamate sarebbero $1\,664\,079$; i sottoproblemi distinti, sempre 30.
### Osservazione chiave: quanti sottoproblemi distinti esistono?
> [!info] Numero di sottoproblemi distinti
> L'algoritmo ricorsivo risolve solo sottoproblemi della forma "WIS sul prefisso $G_j$" per $j = 1, \ldots, n$. Esistono quindi **esattamente $n$ sottoproblemi distinti** — uno per ogni prefisso di $G$. Sono $\Theta(n)$: pochi!

Ed ecco le due condizioni della [[#L'idea, prima della tecnica|sezione iniziale]], entrambe soddisfatte: la **sottostruttura ottima** l'abbiamo appena dimostrata nei due casi su $v_n$, e la **sovrapposizione** è quella che si vede nell'albero qui sopra. Quindi la DP si applica: invece di ricalcolare ogni sottoproblema ogni volta che serve, lo risolviamo **una volta sola** e memorizziamo il risultato — e le 15 chiamate (o il milione e mezzo) diventano $n$ celle riempite una per una.
## L'algoritmo di programmazione dinamica (bottom-up)
### Definizione dei sottoproblemi
- $G_j$: sottocammino composto dai **primi $j$ vertici** di $G$ (con $j = 1, \ldots, n$).
- **Sottoproblema $j$**: calcolare il peso dell'insieme indipendente di peso massimo di $G_j$.
- $\text{OPT}[j]$: valore della soluzione ottima del sottoproblema $j$ (peso dell'insieme indipendente di peso massimo di $G_j$).
### Equazione di Bellman (ricorrenza)
$$\text{OPT}[j] = \max\bigl\{\text{OPT}[j-1],\; w_j + \text{OPT}[j-2]\bigr\}$$

**Casi base**:
$$\text{OPT}[1] = w_1 \qquad \text{OPT}[2] = \max\{w_1, w_2\}$$

La ricorrenza cattura esattamente i due casi della struttura ottima: o $v_j$ non è nell'ottimo (e il valore coincide con l'ottimo di $G_{j-1}$), oppure $v_j$ è nell'ottimo (e il valore è $w_j$ più l'ottimo di $G_{j-2}$, poiché $v_{j-1}$ è escluso).

La sottostruttura ottima giustifica la *forma* della ricorrenza; resta da chiudere il cerchio e verificare che l'algoritmo che la itera calcoli davvero il valore cercato. È un'induzione immediata, ma è il passo che trasforma «la formula è plausibile» in «l'algoritmo è corretto».

> [!quote] Proprietà — Correttezza di WIS-BottomUp
> Per ogni $j = 1, \ldots, n$, al termine dell'iterazione $j$ la cella $\text{OPT}[j]$ contiene il peso dell'insieme indipendente di peso massimo di $G_j$.

**Dimostrazione (per induzione su $j$).**
- *Casi base* ($j = 1, 2$). Su $G_1$ l'unico insieme indipendente non vuoto è $\{v_1\}$, di peso $w_1 = \text{OPT}[1]$. Su $G_2$ i due nodi sono adiacenti, quindi un insieme indipendente contiene al più uno fra $v_1, v_2$: il massimo è $\max\{w_1, w_2\} = \text{OPT}[2]$.
- *Passo* ($j \geq 3$). Per ipotesi induttiva $\text{OPT}[j-1]$ e $\text{OPT}[j-2]$ sono i pesi ottimi di $G_{j-1}$ e $G_{j-2}$ — già calcolati, perché l'ordine crescente di $j$ li rende disponibili prima di $\text{OPT}[j]$. Per la sottostruttura ottima ogni insieme indipendente di peso massimo di $G_j$ ha una delle due forme (escludere $v_j$, valore $\text{OPT}[j-1]$; includere $v_j$, valore $w_j + \text{OPT}[j-2]$), e il suo peso è il **maggiore** dei due candidati. L'assegnamento $\text{OPT}[j] \gets \max\{\text{OPT}[j-1],\; w_j + \text{OPT}[j-2]\}$ calcola esattamente questo valore.

In particolare $\text{OPT}[n]$ è il peso ottimo di $G_n = G$, che è quanto l'algoritmo restituisce. $\square$
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

A tabella finita, i valori si leggono meglio incolonnati sopra il grafo:

![[dp1_opt_values.png]]
Ogni $\text{OPT}[j]$ sta sopra il proprio nodo $v_j$. Si legge la ricorrenza a occhio: sotto $v_5$ (peso 3) il valore resta 12 perché $3 + \text{OPT}[3] = 12$ batte di poco $\text{OPT}[4] = 9$; sotto $v_6$ (peso 10) si arriva a $10 + \text{OPT}[4] = 19$. (slide 24)

Il valore ottimo è $\text{OPT}[6] = 19$, corrispondente all'insieme $\{v_1, v_3, v_6\}$ (lo verificheremo con la ricostruzione).
### Complessità di WIS-BottomUp
| Risorsa | Costo |
|---|---|
| Tempo | $T(n) = \Theta(n)$ — un'operazione per cella della tabella |
| Spazio | $O(n)$ — il vettore $\text{OPT}$ di $n$ elementi |

![[dp1_algoritmo_bottomup.png]]
L'algoritmo come sta sulla slide, con il $T(n)=\Theta(n)$ incorniciato: due casi base, un ciclo da $3$ a $n$, una riga di ricorrenza. In fondo l'osservazione che apre la sezione successiva — **calcola il valore dell'ottimo, non l'ottimo**.

> [!info] Ottimizzazione spaziale
> Poiché la ricorrenza dipende solo da $\text{OPT}[j-1]$ e $\text{OPT}[j-2]$, è sufficiente mantenere le ultime due celle, riducendo lo spazio a $O(1)$. Tuttavia, per ricostruire la soluzione (non solo il valore) serve l'intero vettore.
## Ricostruzione della soluzione
WIS-BottomUp calcola il **valore** dell'ottimo, ma non l'insieme $S^*$ stesso. Come recuperare i nodi scelti?

![[dp1_ricostruzione.png]]
La procedura di ricostruzione sulla slide, con sotto il risultato sull'istanza di riferimento: in rosso i nodi che finiscono in $S^*$ — $v_1, v_3, v_6$ — letti a ritroso dal vettore $\text{OPT}$ già calcolato. Si scorre da $j=n$ verso il basso confrontando $\text{OPT}[j-1]$ con $w_j + \text{OPT}[j-2]$: nessuna informazione aggiuntiva va memorizzata durante il riempimento.

> [!quote] Proprietà chiave — Criterio di appartenenza
> Nella ricostruzione qui descritta, il nodo $v_j$ viene **incluso** in $S^*$ **se e solo se**
> $$w_j + \text{OPT}[j-2] > \text{OPT}[j-1]$$
> (il secondo caso della ricorrenza **vince strettamente** sul primo). Sui pareggi il test $\text{OPT}[j-1] \geq w_j + \text{OPT}[j-2]$ dello pseudocodice risulta vero, quindi $v_j$ viene **escluso**.

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

→ **Palestra**: [[Palestra - Programmazione Dinamica#Ricostruzione senza traccia delle scelte|ricostruzione senza traccia delle scelte — domanda costruita]]
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

![[dp1_quattro_passi.png]]
I quattro passi come li enuncia il prof, con accanto a ciascuno l'istanza su WIS. È lo schema da riprodurre su ogni Esercizio 3: **sottoproblemi → ricorrenza → tabella → ordine di riempimento**.

**Proprietà che i sottoproblemi devono soddisfare**:
- Essere **pochi** (tipicamente $O(n)$, $O(n^2)$, $O(n \cdot W)$, …).
- Avere **casi base** risolvibili direttamente.
- Avere un **ordine di risoluzione**: la dipendenza tra sottoproblemi deve essere aciclica.
- Risolti tutti, permettere di **ricavare rapidamente** la soluzione del problema originale.

![[dp1_proprieta_sottoproblemi.png]]
Le quattro proprietà che i sottoproblemi devono avere, dalla slide successiva. La seconda è quella che si dimentica: **risolti tutti i sottoproblemi si deve poter ricavare in fretta la soluzione cercata** — e spesso quella cercata è semplicemente il sottoproblema più grande.

> [!warning] La chiave è definire i sottoproblemi giusti
> La parte più difficile della programmazione dinamica non è scrivere il codice, ma **identificare i sottoproblemi corretti**. Essi sono un *punto di arrivo*, non di partenza: si trovano ragionando sulla struttura della soluzione ottima. Solo dopo aver definito i sottoproblemi si può verificare la correttezza dell'algoritmo e scrivere la ricorrenza.
>
> Errore tipico: scrivere una formula del tipo $\text{OPT}[j] = \text{OPT}[j-3] + j^2$ senza specificare cosa rappresenti $\text{OPT}[j]$. La formula senza la definizione del sottoproblema non ha significato.
### Come si scrive un Esercizio 3
*(extra, non da slide)* I quattro passi qui sopra descrivono la **tecnica**. Quello che segue è come si mette per iscritto sotto esame: la traccia dell'Esercizio 3 dice sempre «*progettate un algoritmo di programmazione dinamica che calcoli …*» — su 24 tracce, 17 hanno un Esercizio 3, tutte e 17 in questa forma, e 9 aggiungono «*si discuta la complessità temporale*».

> [!info] Regola — il protocollo dell'Esercizio 3: cinque passi, sempre gli stessi
> **1. Sottoproblema** — che cosa indicizza la tabella e cosa significa *esattamente* una sua cella, a parole prima che in formula: «$\text{OPT}[i][k]$ = il massimo … considerando i primi $i$ elementi e avendo usato $k$ …». Dichiara anche **quanti** sono.
> **2. Ricorrenza** — la formula che lega una cella a celle più piccole, con i casi che la compongono, e una riga di **giustificazione**: si elencano i casi possibili per l'ultimo elemento, si dice che sono **esaustivi** e che in ciascuno il residuo è a sua volta un sottoproblema ottimo (è il *cut-and-paste*, e in una riga si liquida).
> **3. Caso base** — le celle che si riempiono direttamente.
> **4. Ordine di riempimento e dove si legge la risposta** — in che ordine si scorrono gli indici perché ogni cella trovi pronte quelle da cui dipende, e quale cella (o quale min/max) contiene il risultato. Se la traccia chiede anche la **soluzione** e non solo il suo valore, la ricostruzione sta qui.
> **5. Complessità** — numero di celle $\times$ costo per cella, con la giustificazione, per tempo e spazio.
>
> Il passo difficile è **sempre il primo**, e gli altri quattro seguono quasi da soli. Se sei bloccato, il problema è la definizione dello stato, non la formula.

> [!warning] Dove si perdono davvero i punti
> Non nello pseudocodice: nel **passo 1**. Una definizione di sottoproblema sbagliata o vaga fa crollare tutto ciò che segue, mentre una definizione giusta con pseudocodice assente vale quasi tutto il punteggio. Se il tempo stringe, l'ordine di priorità è **sottoproblemi → ricorrenza → complessità → pseudocodice**.
> **Lo pseudocodice la traccia non lo chiede mai**: la parola non compare in nessuna delle 24 tracce del campione, e il compito non ha un preambolo di istruzioni che lo imponga — la richiesta è sempre e solo «*progettate* un algoritmo di programmazione dinamica che calcoli X». Progettare significa **comunicare** l'algoritmo, e i cinque passi lo comunicano già per intero. Lo pseudocodice è *una* forma possibile per il passo 4, comoda quando l'ordine di riempimento è intricato, inutile quando lo sai dire in una riga di prosa.
> Attenzione infine a **cosa** calcola la tabella: quasi sempre un **valore numerico**, non l'insieme soluzione. Ricostruire la soluzione è un lavoro a parte (dentro il passo 4) e va fatto solo se la traccia lo chiede.

> [!info] La domanda da farsi quando non si trova la ricorrenza
> *«Su quale singola decisione posso spezzare il problema, in modo che ciò che resta sia un'istanza più piccola dello stesso problema?»* Nel Weighted Interval Scheduling la decisione è «prendo il job $j$ oppure no»; nel Knapsack «metto l'oggetto $i$ nello zaino oppure no»; nel WIS su cammino «includo l'ultimo nodo oppure no» (vedi [[04 - Programmazione Dinamica I (Weighted Independent Set)#Il metodo: interrogare la soluzione ottima invece di costruirla|il metodo]]).
> Se la risposta richiede di ricordare **più di una** informazione — come nel Knapsack, dove serve sapere anche quanta capacità resta — allora i sottoproblemi hanno **due indici** invece di uno, e la tabella diventa bidimensionale. È il segnale che distingue $\text{OPT}[j]$ da $\text{OPT}[i][w]$.

> [!warning] Regola — il passo 4 quasi mai è «l'ultima cella», e i motivi sono quattro
> Su questi otto problemi la risposta coincide con l'ultima cella della tabella **una volta sola**. Vale la pena vedere il conto, perché è il punto in cui si buttano via tutti gli altri quattro passi fatti bene.
>
> | problema | dove si legge la risposta |
> |---|---|
> | Comizi con budget | $\text{OPT}[n][B]$ — cella singola (stato «al più $B$») |
> | LIS quasi monocromatica | $\max_i \text{OPT}[i][k]$ — massimo su una riga |
> | Canguro | $\text{OPT}[n][m][k]$ — **cella singola** |
> | Dominating set con sconti | minimo su **quattro dei cinque** stati finali |
> | Metro D | minimo sull'**ultima colonna** |
> | Case con $k$ rosse | minimo sul colore (e su $r$, se lo stato è «esattamente») |
> | Job su due macchine | $\min_h\bigl(\text{OPT}[n][h] + c_h\bigr)$ — con un **termine aggiunto** |
> | Tube Invaders | $\max_i \text{OPT}[i]$, oppure cella singola a seconda dello stato |
>
> I motivi per cui non è l'ultima cella sono **quattro diversi**, e riconoscere quale hai davanti è metà del lavoro:
> 1. lo **stato è vincolato** e l'oggetto ottimo può finire ovunque (LIS, Tube Invaders);
> 2. l'**insieme degli arrivi ammessi** è più grande di un punto (Metro D: tutta la colonna $m$);
> 3. alcuni **stati finali sono inammissibili** e vanno esclusi (Dominating set: un nodo mai dominato);
> 4. alla lettura serve **aritmetica in più**, non solo un min o un max (Job: il costo fisso $c_h$).
>
> **La regola pratica: il punto 4 non si risponde guardando la tabella, si risponde rileggendo il punto 1.** La domanda è «quali celle corrispondono a soluzioni *complete e ammissibili* del problema originale?». Se la definizione del sottoproblema contiene un vincolo — «che termina con $i$», «con esattamente $r$ rosse», «con $v_i$ non ancora dominato» — quel vincolo va **sciolto** alla lettura finale, e scioglierlo significa un min/max su tutte le celle che lo soddisfano *in modo ammissibile*.

> [!info] Regola — quando il caso base esce da solo e quando va scritto a mano
> La diagnostica utile non è «quante posizioni indietro guarda la ricorrenza», ma questa: **il caso base esce dalla ricorrenza solo quando l'insieme vuoto dei predecessori ha un'interpretazione valida.**
> - *Esce da solo*: nella LIS il massimo su un insieme vuoto di predecessori rappresenta legittimamente la sottosequenza di un elemento solo, quindi $\text{OPT}[1][t] = 1 + \max(0,\ldots) = 1$ viene fuori gratis. Nei job su due macchine «zero job costano zero» è il prefisso vuoto in purezza.
> - *Va scritto a mano*: nel Canguro, nella Metro D, nel Dominating set e nella colorazione, «nessun predecessore» **non è una configurazione** — il cammino o la colorazione devono pur venire da qualche parte. Lì la formula darebbe $\pm\infty$, che è sbagliato, e il caso base va dichiarato.
>
> **Controllo che vale sempre**: sostituisci il valore degenere (zero figli, budget zero, prefisso vuoto) nella ricorrenza. Se ottieni i casi base che avevi scritto, la definizione del sottoproblema è solida; se non li ottieni, o hai un caso base da dichiarare, oppure — più spesso — lo stato ha un buco.

> [!info] Regola — un budget limitato da $n$ non ti porta nella pseudo-polinomialità
> Tre di questi problemi hanno un secondo indice che è un budget: $k$ salti, $k$ case rosse, $k$ cambi di colore. In tutti e tre il budget è **limitato da una quantità legata a $n$** — non si fanno più di $n+m$ salti, non si dipingono più di $n$ case, una sottosequenza lunga $L$ ha al più $L-1$ cambi — quindi si può sempre troncare a $k' = \min(k, \cdot)$ e la complessità resta **polinomiale nella dimensione dell'istanza**.
> È il contrasto esatto con il Knapsack, dove $W$ *non* è limitato da $n$ e $\Theta(nW)$ resta pseudo-polinomiale. Dirlo in una riga chiude il punto 5 con un argomento in più invece che con un numero solo.

> [!warning] Il pattern che ricorre nelle tracce recenti
> **Problema noto + un parametro di budget $k$ che diventa una dimensione della tabella.** Le tre tracce più recenti sono tutte così: un dominating set con uno sconto legato alla lunghezza del blocco, un cammino su griglia con $k$ salti a disposizione, una LIS con al più $k$ cambi di colore. La mossa da allenare è **riconoscere il problema noto sotto il travestimento** e chiedersi *quale grandezza va portata nello stato perché la ricorrenza si chiuda*.

→ **Palestra**: gli otto Esercizio 3 reali su cui allenare tutto questo stanno in [[Palestra - Programmazione Dinamica]].
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

![[dp1_wis_alberi_istanza.png]]
L'istanza della festa aziendale. I numeri dentro i cerchi sono i **pesi** dei nodi, non i nomi: la radice pesa 2, i suoi due figli 7 e 6, le foglie 3, 1 sotto il 7 e 2, 3, 3 sotto il 6. I cerchi **rossi** sono la soluzione ottima, $\{7, 2, 3, 3\}$ di peso 15 — puoi usarla per controllare da solo il calcolo bottom-up qui sotto. Nota che l'ottimo **scarta la radice**, che pure è l'unico nodo da cui si vede tutto l'albero: prenderla costerebbe sia il 7 sia il 6. (slide 43)

L'ottimo ha peso **OPT = 15**: si selezionano il nodo $7$ (figlio sinistro della radice) e i tre figli di $6$ (pesi $2, 3, 3$), escludendo la radice, il nodo $6$ e i due figli di $7$. In simboli l'insieme è $\{7, 2, 3, 3\}$, di peso $7 + 2 + 3 + 3 = 15$.

**Sottoproblemi** (due per ogni nodo $v$, per gestire l'alternativa include/esclude):
- $A[v]$: peso dell'insieme indipendente di peso massimo nel sottoalbero radicato in $v$ (senza vincoli su $v$).
- $B[v]$: peso dell'insieme indipendente di peso massimo nel sottoalbero radicato in $v$, con il vincolo che $v$ **non** venga incluso.

**Casi base** (nodi foglia):
$$A[v] = w_v \qquad B[v] = 0$$

**Ricorrenza** per un nodo interno. Prima la notazione, che le slide danno per scontata: si chiamano $u_1, \ldots, u_d$ i **figli** di $v$, e $d$ è **quanti sono** — il grado di $v$ verso il basso. Attenzione che $d$ **non è una costante del problema**: cambia da nodo a nodo. Nell'esempio qui sopra la radice ha $d = 2$ (i nodi 7 e 6), il nodo 6 ha $d = 3$ (le tre foglie 2, 3, 3), ogni foglia ha $d = 0$.
È questa variabilità a imporre la **sommatoria**: sul cammino ogni nodo aveva esattamente un vicino e si poteva scrivere un termine fisso, $\text{OPT}(j-2)$; su un albero il numero di figli non è noto in anticipo, quindi si scrive «sommali tutti» — e per sommarli tutti bisogna poterli nominare uno a uno.
$$B[v] = \sum_{i=1}^{d} A[u_i]$$
$$A[v] = \max\!\left\{B[v],\; w_v + \sum_{i=1}^{d} B[u_i]\right\}$$

> [!info] Regola — i casi base escono gratis dalla formula generale
> Su una foglia $d = 0$, e una sommatoria su **zero** termini vale $0$. Sostituendo: $B[v] = 0$ e $A[v] = \max\{0,\ w_v + 0\} = w_v$ — che sono esattamente i casi base enunciati sopra. Non sono una regola a parte: sono la ricorrenza generale letta con $d = 0$. Le slide li scrivono separati solo per chiarezza.
> Vale la pena controllarlo ogni volta che progetti una ricorrenza con una sommatoria: se i casi base **non** escono da soli sostituendo il valore degenere, di solito è il segnale che la definizione del sottoproblema ha un buco.

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

→ **Palestra**: [[Palestra - Programmazione Dinamica#Da cammino ad albero: perché due sottoproblemi per nodo|da cammino ad albero: perché due sottoproblemi per nodo — domanda costruita]]

![[dp1_wis_alberi.png]]
La soluzione sulle slide, in inglese: per ogni nodo $v$, $A[v]$ è il peso del miglior insieme indipendente di $T_v$ e $B[v]$ quello dei soli insiemi **che non contengono $v$**. Da cui $B[v] = \sum_i A[u_i]$ sui figli, e $A[v] = \max\{B[v],\ w_v + \sum_i B[u_i]\}$. L'ordine di risoluzione è **bottom-up sull'albero**: è il passo 4 dello schema, qui non banale come sul cammino.
## Riepilogo complessità
| Fase | Algoritmo | Tempo | Spazio |
|---|---|---|---|
| Valore ottimo | WIS-BottomUp | $\Theta(n)$ | $O(n)$ |
| Ricostruzione soluzione | WIS-Ricostruisci | $\Theta(n)$ | $O(1)$ aggiuntivo |
| Totale (valore + soluzione) | — | $\Theta(n)$ | $O(n)$ |

→ **Palestra**: [[Palestra - Programmazione Dinamica#Perché la ricorsione diretta è esponenziale|perché la ricorsione diretta è esponenziale — domanda costruita]]

> [!info] Connessioni ad altri argomenti
> - La memoization applicata a Fibonacci (fibonacci3) è la versione più semplice della programmazione dinamica: [[01 - Il Problema di Fibonacci]].
> - Le equazioni di ricorrenza del tipo $T(n) = T(n-1) + T(n-2) + O(1)$ e le tecniche per risolverle sono in [[03 - Equazioni di Ricorrenza]].
> - Il **Weighted Interval Scheduling** e il problema **Knapsack** — altri classici della programmazione dinamica — sono trattati nella nota successiva: [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]].
> - **Sequence Alignment** (distanza di edit) e **Bellman-Ford** (cammini minimi con archi negativi) come applicazioni avanzate della programmazione dinamica: [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].
> - Per il WIS su grafi generali (non cammini) il problema diventa NP-difficile: [[09 - NP-Completezza e Riduzioni]].
## Mappa nota ↔ slide
Riferimenti a `Materiale Didattico/Modulo II/Slide/04_DP_I_2025.pdf` (44 pagine).

| Sezione della nota | Slide |
|---|---|
| L'idea, prima della tecnica | pp. 2-3 (inquadramento e sommario) |
| Il problema: WIS su cammino | **p. 4** (definizione) · **pp. 5-8** (istanza $1,4,8,4,3,10$ e tre insiemi indipendenti, $w=12$, $18$, $19$) |
| Perché le tecniche classiche non funzionano | p. 9 · **p. 10** (forza bruta) · **pp. 11-15** (greedy, demo) · **pp. 16-17** (divide et impera) · **p. 18** (diagnosi) |
| Struttura della soluzione ottima | **p. 19** (il passaggio critico) · **pp. 20-21** (ragionare sulla struttura) · **p. 22** (la proprietà nei due casi e la ricorrenza di Fibonacci) |
| Dall'idea ricorsiva all'algoritmo efficiente | **p. 23** (quanti sottoproblemi distinti) · **p. 24** (i sottoproblemi $G_j$ e il vettore OPT) |
| L'algoritmo bottom-up | **p. 25** (algoritmo e $T(n)=\Theta(n)$) |
| Ricostruzione della soluzione | p. 26 · **p. 27** (l'idea) · **pp. 28-33** (procedura e demo) |
| Principi generali | **p. 34** (i quattro passi) · **p. 35** (proprietà dei sottoproblemi) |
| La chiave è definire i sottoproblemi giusti | pp. 36-41 (i dialoghi con gli avvertimenti) |
| Esercizio: WIS su alberi | **pp. 42-43** (il problema della festa aziendale) · **p. 44** (la soluzione: $A[v]$, $B[v]$) |

> [!info] Come si legge — metà del deck è demo
> Delle 44 pagine, una ventina sono animazioni della stessa istanza (pp. 5-8, 11-15, 28-33): scorrile in fila. Le pagine che contano davvero sono le nove in grassetto, e fra queste **p. 22** (perché la ricorsione diretta è esponenziale) e **p. 34** (i quattro passi) sono quelle da avere in testa martedì.
