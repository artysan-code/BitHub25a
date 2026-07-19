---
tags:
  - algoritmi
  - flussi
---
# Formulario — Flussi di Rete (Esercizio 1 / 2)
Scheda di consegna per lo slot **Flussi** dello scritto di Modulo II. Teoria estesa in [[07 - Flussi di Rete (Max-Flow e Min-Cut)]] — che contiene già una quarantina di **domande d'esame reali** con risposta: quella nota è il banco di prova, questa è il ripasso. Applicazioni (matching, cammini disgiunti) in [[08 - Applicazioni dei Flussi di Rete]]: **fuori dallo scritto**, 0/6.

> [!info] Come cade all'esame
> Flussi occupa uno dei due slot Es1/Es2 in **5 compiti su 6**. Il format è lo stesso dell'MST: **4-5 V/F motivati + 1-2 aperte**. Ma il baricentro è diverso: qui i V/F vertono in modo schiacciante su **complessità di Ford-Fulkerson su istanze vincolate** («capacità $\le n^2$», «capacità unitarie», «grado entrante limitato»), e le aperte chiedono la **definizione formale** di max-flow/min-cut o la **dimostrazione** di «nessun cammino aumentante $\Rightarrow$ flusso massimo».
## Definizioni — vanno scritte così
**Rete di flusso**: grafo **orientato** $G=(V,E)$ con capacità $c(e) \ge 0$ su ogni arco, una **sorgente** $s$ e un **pozzo** $t$.
> [!quote] Flusso $st$
> Una funzione $f: E \to \mathbb{R}_{\ge 0}$ che rispetta due vincoli:
> - **capacità**: $0 \le f(e) \le c(e)$ per ogni $e \in E$;
> - **conservazione**: per ogni $v \neq s,t$, $\displaystyle\sum_{e \text{ entrante in } v} f(e) = \sum_{e \text{ uscente da } v} f(e)$.
>
> Il **valore** è $\text{val}(f) = \sum_{e \text{ uscente da } s} f(e) - \sum_{e \text{ entrante in } s} f(e)$.

> [!quote] Taglio $st$
> Una partizione $(A,B)$ di $V$ con $s \in A$ e $t \in B$. La sua **capacità** è
> $$\text{cap}(A,B) = \sum_{e \text{ da } A \text{ a } B} c(e)$$

> [!warning] L'errore da 1 punto sulla definizione di taglio
> Nella **capacità** si sommano **solo gli archi che vanno da $A$ a $B$**, e si contano le **capacità** (non i flussi). Gli archi da $B$ ad $A$ **non** si sottraggono e **non** si sommano: sono ignorati. Nel **lemma del valore** invece il flusso netto sottrae gli archi all'indietro. Confondere le due formule è l'errore più comune del capitolo.

**Max-Flow**: trovare $f$ che massimizza $\text{val}(f)$. **Min-Cut**: trovare $(A,B)$ che minimizza $\text{cap}(A,B)$.
## Perché il greedy fallisce (e da lì nasce l'arco inverso)
Il greedy «trova un cammino $s \to t$ con capacità libera, saturalo, ripeti» si blocca su ottimi locali: una volta mandato flusso lungo un cammino, **non può disfare** quella scelta, anche quando è proprio la scelta che impedisce di raggiungere l'ottimo. Serve un meccanismo per **ritirare** flusso già instradato: è esattamente il ruolo dell'**arco inverso** del grafo residuo.

> [!info] Se ti chiedono «a cosa serve l'arco inverso»
> Rispondi: *«a permettere all'algoritmo di annullare, in tutto o in parte, una decisione presa in un'iterazione precedente, reinstradando quel flusso su un percorso migliore. Senza di esso l'algoritmo sarebbe un greedy e si fermerebbe su un ottimo locale.»*
## Grafo residuo — la definizione precisa
> [!quote] Grafo residuo $G_f$
> Stessi nodi di $G$. Per ogni arco $e=(u,v) \in E$:
> - se $f(e) < c(e)$: arco **forward** $(u,v)$ con capacità residua $c(e) - f(e)$ (quanto puoi ancora **spingere**);
> - se $f(e) > 0$: arco **backward** $(v,u)$ con capacità residua $f(e)$ (quanto puoi **ritirare**).

> [!quote] Cammino aumentante
> Un cammino semplice da $s$ a $t$ **nel grafo residuo** $G_f$. Il suo **bottleneck** è la **minima capacità residua** fra i suoi archi.

Aumentare lungo il cammino di $b$ = bottleneck: su ogni arco forward $f(e) \mathrel{+}= b$, su ogni arco backward $f(e) \mathrel{-}= b$. Il risultato è ancora un flusso valido e $\text{val}(f)$ cresce di $b$.

> [!warning] Due trappole sul bottleneck
> **(1)** Il bottleneck **non** è la capacità residua di un singolo arco né la capacità minima del grafo: è il **minimo lungo il cammino scelto**, e dipende dal cammino. **(2)** Aumentare la capacità dell'arco di capacità minima **non** aumenta necessariamente il bottleneck (il collo di bottiglia si sposta su un altro arco) né il max-flow (il min-cut può passare altrove).
## Ford-Fulkerson
```
FORD-FULKERSON(G, s, t, c):
  f(e) ← 0 per ogni e ∈ E
  costruisci G_f
  finché esiste un cammino aumentante P in G_f:
      b ← bottleneck(P)
      aumenta f di b lungo P
      aggiorna G_f
  return f
```
> [!info] Invariante di integralità
> Se **tutte le capacità sono intere**, allora a ogni iterazione il bottleneck è **intero e $\ge 1$**, quindi tutti i flussi restano interi. Corollario (**teorema di integralità**): esiste sempre un flusso massimo a **valori interi**. È il fatto che rende utilizzabili i flussi per matching e problemi combinatori.
### Complessità — il cuore dei V/F
> [!quote] Terminazione con capacità intere
> Sia $C$ la **capacità massima** di un arco. Ogni iterazione aumenta $\text{val}(f)$ di almeno $1$, e $\text{val}(f^*) \le nC$ (il flusso non supera la capacità uscente da $s$). Quindi al più $\text{val}(f^*)$ iterazioni, ciascuna $O(m)$ per trovare il cammino con una visita:
> $$T(n,m) = O(m \cdot \text{val}(f^*)) = O(mnC)$$

> [!danger] La distinzione che vale i punti: pseudo-polinomiale ≠ polinomiale
> $O(mnC)$ dipende dal **valore** delle capacità, non dalla loro **lunghezza in bit**: è **pseudo-polinomiale**. Con capacità scritte in binario, $C$ può essere esponenziale nella dimensione dell'input. Quindi **«capacità intere» NON basta per la polinomialità** — ed esiste un **caso patologico** (arco centrale di capacità $C$ e cammini che portano 1 unità per volta) in cui FF fa $\Theta(C)$ iterazioni.
> Ma se la traccia **limita** le capacità a un polinomiale in $n$ (es. $c(e) \le n^2$, oppure $c(e) \le 2$, oppure unitarie), allora $C$ è polinomiale e **FF diventa polinomiale**. Il prof costruisce l'item esattamente su questa distinzione: leggi sempre **il vincolo sulle capacità** prima di rispondere.

**Come si risponde a un item «capacità $\le k$, grado entrante $\le d$…»**: dal vincolo ricavi un bound su $\text{val}(f^*)$ (= numero massimo di iterazioni), poi moltiplichi per $O(m)$. **Non memorizzare le righe: ricostruiscile.**

| Vincolo nella traccia | Bound su $\text{val}(f^*)$ | Complessità FF |
|---|---|---|
| Capacità intere generiche | $\le nC$ | $O(mnC)$, **pseudo-polinomiale** |
| Capacità unitarie | $\le \deg^+(s) \le n$ | $O(mn)$, polinomiale |
| Capacità $\le n^2$ | $\le n \cdot n^2 = n^3$ | $O(mn^3)$, polinomiale |
| Capacità reali/irrazionali | nessun bound | **può non terminare** |

**Scelta del cammino** — toglie del tutto la dipendenza da $C$:

| Variante | Criterio del cammino | N. aumenti | Complessità |
|---|---|---|---|
| Ford-Fulkerson generico | uno qualsiasi | $\le nC$ | $O(mnC)$ |
| **Edmonds-Karp** | il **più corto** (BFS) | $O(mn)$ | $\mathbf{O(m^2 n)}$, **sempre polinomiale** |
| **Capacity Scaling** | bottleneck **grande** ($\Delta$-grafo residuo) | $O(m\log C)$ | $O(m^2 \log C)$ |

> [!info] Perché Edmonds-Karp funziona (se te lo chiedono)
> La distanza BFS da $s$ a $t$ in $G_f$ è **monotona non decrescente** lungo le iterazioni; ogni arco può essere critico (cioè bottleneck) al più $O(n)$ volte prima che la sua distanza cresca. Da qui il bound $O(mn)$ sugli aumenti, **indipendente da $C$**.
## Il teorema — la dimostrazione da consegnare
> [!quote] Lemma del valore del flusso
> Per **ogni** flusso $f$ e **ogni** taglio $(A,B)$:
> $$\text{val}(f) = \underbrace{\sum_{e \text{ da } A \text{ a } B} f(e)}_{f^{\text{out}}(A)} - \underbrace{\sum_{e \text{ da } B \text{ a } A} f(e)}_{f^{\text{in}}(A)}$$
> *Prova*: sommi la conservazione su tutti i nodi di $A$; i contributi degli archi interni ad $A$ compaiono una volta con $+$ e una con $-$ e si cancellano, resta il flusso netto attraverso il taglio.

> [!quote] Dualità debole
> Per ogni $f$ e ogni $(A,B)$: $\text{val}(f) \le \text{cap}(A,B)$.
> *Prova*: $\text{val}(f) = f^{\text{out}}(A) - f^{\text{in}}(A) \le f^{\text{out}}(A) \le \sum_{e: A\to B} c(e) = \text{cap}(A,B)$, usando $f^{\text{in}}(A) \ge 0$ e $f(e)\le c(e)$.

> [!quote] Corollario — certificato di ottimalità
> Se esistono $f$ e $(A,B)$ con $\text{val}(f) = \text{cap}(A,B)$, allora $f$ è **massimo** e $(A,B)$ è **minimo**.

> [!quote] Teorema Max-Flow Min-Cut (forma a 3 vie)
> Per un flusso $f$ sono **equivalenti**:
> 1. esiste un taglio $(A,B)$ con $\text{cap}(A,B) = \text{val}(f)$;
> 2. $f$ è un flusso **massimo**;
> 3. **non esiste** cammino aumentante in $G_f$.

**$[1 \Rightarrow 2]$** — Immediato dal corollario: la dualità debole dice $\text{val}(f') \le \text{cap}(A,B) = \text{val}(f)$ per ogni flusso $f'$, quindi $f$ è massimo.

**$[2 \Rightarrow 3]$** — Contronominale: se esistesse un cammino aumentante $P$ in $G_f$, aumentando di $b = \text{bottleneck}(P) > 0$ otterrei un flusso di valore $\text{val}(f) + b > \text{val}(f)$, quindi $f$ non era massimo.

**$[3 \Rightarrow 1]$** — È la parte che conta. Sia $A = \{v \in V : v \text{ è raggiungibile da } s \text{ in } G_f\}$ e $B = V \setminus A$.
- $s \in A$ per definizione; $t \in B$ perché per ipotesi non c'è cammino $s \to t$ in $G_f$. Quindi $(A,B)$ è un taglio $st$ legittimo.
- Sia $e=(u,v)$ un arco di $G$ **da $A$ a $B$**. Se fosse $f(e) < c(e)$, in $G_f$ esisterebbe il forward $(u,v)$ e $v$ sarebbe raggiungibile: assurdo. Dunque $f(e) = c(e)$: gli archi $A \to B$ sono **saturi**.
- Sia $e=(u,v)$ un arco di $G$ **da $B$ ad $A$**. Se fosse $f(e) > 0$, in $G_f$ esisterebbe il backward $(v,u)$ con $v \in A$, e $u$ sarebbe raggiungibile: assurdo. Dunque $f(e) = 0$: gli archi $B \to A$ sono a **flusso nullo**.
- Per il lemma del valore: $\text{val}(f) = f^{\text{out}}(A) - f^{\text{in}}(A) = \sum_{A\to B} c(e) - 0 = \text{cap}(A,B)$. $\blacksquare$

> [!danger] LA trappola del corso — non invertirla
> Nel passo $[3\Rightarrow1]$:
> - archi **$A \to B$** $\;\Rightarrow\;$ **saturi**, $f(e) = c(e)$;
> - archi **$B \to A$** $\;\Rightarrow\;$ **flusso nullo**, $f(e) = 0$.
>
> Il modo per non sbagliarla: **entrambi i casi si dimostrano nello stesso modo** — «se non fosse così, l'arco residuo corrispondente esisterebbe e porterebbe un nodo di $B$ dentro l'insieme dei raggiungibili». Ricostruisci l'argomento invece di ricordare la conclusione.
### Estrazione del min-cut da un flusso massimo
> [!quote] Algoritmo — min-cut in tempo lineare
> Dato un flusso massimo $f$: costruisci $G_f$, fai una **BFS/DFS da $s$** in $G_f$, poni $A$ = nodi raggiunti, $B = V\setminus A$. $(A,B)$ è un **taglio minimo**. Costo $O(m)$.

La correttezza è esattamente la dimostrazione di $[3\Rightarrow1]$: quella costruzione produce un taglio la cui capacità eguaglia $\text{val}(f)$, e per il corollario è minimo.

> [!info] Variante «nodi che raggiungono $t$»
> Si può anche porre $B$ = nodi **da cui si raggiunge $t$** in $G_f$ e $A = V\setminus B$: è anch'esso un min-cut, in generale **diverso** dal primo. I min-cut possono essere più d'uno; il max-flow è **unico nel valore** ma non nell'assegnamento $f$.
## Batteria V/F — le risposte che ricorrono
Motiva **sempre** in una riga.

| Affermazione | Risp. | Motivazione in una riga |
|---|---|---|
| Il flusso netto attraverso un taglio è sempre $\text{val}(f)$ | **V** | lemma del valore, vale per ogni $f$ e ogni taglio |
| $\text{val}(f) = \text{cap}(A,B)$ per ogni taglio | **F** | vale $\le$ (dualità debole); l'uguaglianza solo per il **min**-cut e $f$ massimo |
| Esiste sempre un taglio di capacità pari a $\text{val}(f)$ | **F** | solo se $f$ è **massimo**; per $f$ qualsiasi il min-cut è $\ge \text{val}(f)$ |
| Se non c'è cammino aumentante allora $f$ è massimo | **V** | $[3\Rightarrow1\Rightarrow2]$ del teorema |
| Se esiste un cammino aumentante allora $f$ non è massimo | **V** | aumentando si ottiene $\text{val}(f)+b > \text{val}(f)$ |
| Esistono grafi con min-cut $<$ max-flow | **F** | il teorema li rende uguali; e la dualità debole esclude già $<$ |
| Capacità intere $\Rightarrow$ FF polinomiale | **F** | $O(mnC)$ è **pseudo**-polinomiale; $C$ è esponenziale nei bit |
| Capacità $\le n^2 \Rightarrow$ FF polinomiale | **V** | $\text{val}(f^*) = O(n^3)$, quindi $O(mn^3)$ |
| Capacità irrazionali $\Rightarrow$ FF termina | **F** | può non terminare, e convergere a un valore non massimo |
| Usare la BFS per i cammini rende FF polinomiale | **V** | Edmonds-Karp, $O(m^2n)$, indipendente dalle capacità |
| Aumentare di 1 la capacità di un arco aumenta il max-flow | **F** | solo se l'arco è in **ogni** min-cut; altrimenti il min-cut resta invariato |
| Il max-flow è unico | **F*** | unico il **valore**; l'assegnamento $f$ e il min-cut possono non esserlo |
| Con capacità intere esiste un max-flow intero | **V** | teorema di integralità, per invarianza del bottleneck intero |
## Esecuzione a mano — la procedura
1. Parti da $f = 0$ e **disegna $G_f$** (all'inizio coincide con $G$, capacità piene).
2. Scegli un cammino $s\to t$ in $G_f$, **scrivilo**, calcola il **bottleneck** come minimo lungo il cammino.
3. Aggiorna: forward $+b$, backward $-b$. **Ridisegna $G_f$**, ricordando che ogni arco con $f(e)>0$ genera un backward.
4. Ripeti finché $s$ non raggiunge più $t$ in $G_f$.
5. **Estrai il min-cut**: $A$ = raggiungibili da $s$ in $G_f$ finale. Verifica: $\text{cap}(A,B)$ deve essere $= \text{val}(f)$ — è il tuo **controllo di correttezza gratuito**, fallo sempre.

> [!danger] Le tre cose che devono essere automatiche domani
> **(1)** La definizione di grafo residuo con **entrambi** gli archi (forward = quanto spingi ancora, backward = quanto ritiri). **(2)** Il passo $[3\Rightarrow1]$ con $A\to B$ **saturi** e $B\to A$ a **flusso nullo**, ricostruito dall'argomento di raggiungibilità. **(3)** La catena «vincolo sulle capacità $\to$ bound su $C$ $\to$ $O(mC)$» per rispondere a qualunque item di complessità.
