---
tags:
  - algoritmi
  - flussi
  - esercizi
---
# Esercizi d'esame — Flussi di Rete
Tutti gli item su **Flussi di Rete** realmente usciti nei **12 compiti** di Modulo II dal giugno 2024 al giugno 2026, con la risposta modello. **Nessun esercizio è inventato**: ogni testo è verbatim dal compito, con appello, esercizio e punto.
> [!info] Cosa dicono i numeri per questo argomento
> **32 item** su 7 appelli diversi (su 12 analizzati). Slot: Es. 1 ×24, Es. 2 ×8.
> Cosa ti chiede di produrre: motiva-vf ×22, definisci ×4, calcola-complessita ×2, altro ×1, discuti-correttezza ×1, dimostra ×1, costruisci-esempio ×1.
> Richieste esplicite di **dimostrazione**: **1**.
> Come usarlo: copri la riga «**Risposta.**», rispondi ad alta voce, scopri. Sui vero/falso motiva **sempre in una riga** — il «vero/falso» secco non prende punti pieni.
### 1. Definizione formale — massimo flusso
*(13/06/2024 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema. (Max 5 righe.)

**Risposta.** Data una rete di flusso $G=(V,E,s,t,c)$ con $c:E\to\mathbb{R}_{\ge0}$, un **flusso** è una funzione $f:E\to\mathbb{R}_{\ge0}$ tale che: (i) *vincolo di capacità* $0\le f(e)\le c(e)$ per ogni $e\in E$; (ii) *conservazione* $\sum_{e \text{ entrante in } v} f(e) = \sum_{e \text{ uscente da } v} f(e)$ per ogni $v\ne s,t$. Il **valore** del flusso è $v(f)=\sum_{e \text{ uscente da } s} f(e) - \sum_{e \text{ entrante in } s} f(e)$. Il problema chiede il flusso ammissibile di valore massimo.
### 2. Complessità e polinomialità di Ford-Fulkerson
*(13/06/2024 · Es. 2 · punto 2 · calcola-complessità)*
> Si enunci la complessità temporale dell'algoritmo di Ford-Fulkerson, argomentando sulla sua polinomialità o meno. (Max 5 righe.)

**Risposta.** $O(m\cdot val(f^*)) = O(mnC)$, dove $C$ è la capacità intera massima. Non è polinomiale nella dimensione dell'istanza: $val(f^*)$ (e quindi $C$) è un *valore*, rappresentabile con $O(\log C)$ bit, ma compare linearmente nel bound — con capacità esponenziali in $n$ il numero di iterazioni è esponenziale. È quindi **pseudo-polinomiale**.
### 3. Taglio e flusso netto (disuguaglianza invertita)
*(9/06/2024 · Es. 1 · V/F 1 · motiva-vf)*
> Dato un taglio (A, B) e un flusso f, allora il flusso netto che passa per (A, B) è sempre maggiore o uguale alla capacità di (A, B).

**Risposta.** **Falsa.** Vale il contrario: per ogni taglio $(A,B)$ il flusso netto è $\le cap(A,B)$ (weak duality), poiché ogni arco forward contribuisce al più $c(e)$ e ogni arco backward contribuisce $\ge0$ sottraendo.
### 4. Cammini aumentanti con capacità intere
*(9/06/2024 · Es. 1 · V/F 2 · motiva-vf)*
> Se le capacità sono intere, allora ogni cammino aumentante trovato nella rete residua può essere usato per aumentare il flusso corrente di almeno una unità.

**Risposta.** **Vera.** Le capacità residue $c_f(e)=c(e)-f(e)$ o $c_f(e)=f(e)$ sono intere se $c$ ed $f$ lo sono; un arco esiste in $G_f$ solo se $c_f(e)\ge1$, quindi il collo di bottiglia del cammino (minimo dei $c_f(e)$) è un intero $\ge1$.
### 5. Max-flow min-cut (esistenza di gap strettо)
*(9/06/2024 · Es. 1 · V/F 3 · motiva-vf)*
> Ci sono dei grafi per cui la capacità del taglio di capacità minima è strettamente inferiore al massimo flusso.

**Risposta.** **Falsa.** Per il teorema max-flow min-cut $val(f^*) = \min_{(A,B)} cap(A,B)$ sempre; inoltre per weak duality $val(f^*)\le cap(A,B)$ per ogni taglio, quindi il min cut non può mai essere strettamente inferiore al max flow.
### 6. Complessità di Ford-Fulkerson con BFS (Edmonds-Karp)
*(9/06/2024 · Es. 1 · V/F 4 · motiva-vf)*
> L'algoritmo di Ford-Fulkerson, se si usa la visita BFS per trovare i cammini aumentanti, ha una complessità polinomiale nella dimensione dell'istanza.

**Risposta.** **Vera.** Usando BFS (cammino aumentante più corto) si ottiene Edmonds-Karp: ogni arco diventa "critico" (satura il bottleneck) $O(n)$ volte, quindi al più $O(nm)$ iterazioni, ciascuna $O(m)$ per la BFS ⇒ $O(m^2n)$, indipendente dal valore delle capacità.
### 7. Flusso netto attraverso un taglio = v(f)
*(9/06/2024 · Es. 1 · punto 2 · motiva-vf)*
> per ogni taglio (A, B) e per ogni flusso f, il flusso netto che attraversa (A.B) è sempre uguale al valore di f.

**Risposta.** **Vera** — è il *flow-value lemma*: per costruzione, sommando i vincoli di conservazione su tutti i nodi di $A$ si ottiene che il flusso netto uscente da $A$ (cioè attraverso $(A,B)$) è uguale a $v(f)$, qualunque sia il taglio scelto.
### 8. Iterazioni di FF con capacità unitarie
*(9/06/2024 · Es. 1 · punto 2 · motiva-vf)*
> Se le capacità degli archi sono tutte uguali a 1, allora il numero di iterazioni [...] è sempre polinomiale nel numero di nodi del grafo, indipendentemente dalla strategia [...]

**Risposta.** **Vera.** Con capacità unitarie $val(f^*) \le$ capacità del taglio $(\{s\},V\setminus\{s\}) \le \text{outdeg}(s) \le n-1 = O(n)$. Per integralità ogni augmenting step aumenta il flusso di almeno 1 unità, quindi il numero di iterazioni è $\le val(f^*) = O(n)$, qualunque sia la strategia di scelta del cammino.
### 9. v(f) uguale alla capacità di un taglio arbitrario
*(26/06/2025 · Es. 1 · V/F 1 · motiva-vf)*
> dato un flusso f di G e un st-taglio (A, B), il valore del flusso v(f) è sempre uguale alla capacità del taglio cap(A, B)

**Risposta.** **Falsa.** Vale solo $v(f)\le cap(A,B)$ (weak duality) per un taglio arbitrario; l'uguaglianza è garantita solo per il taglio di capacità minima quando $f$ è massimo, non per un taglio qualsiasi.
### 10. Complessità FF con capacità intere (non limitate)
*(26/06/2025 · Es. 1 · V/F 2 · motiva-vf)*
> Ford-Fulkerson [...] complessità in generale esponenziale [...] ma è sempre polinomiale quando le capacità sono valori interi.

**Risposta.** **Falsa.** $O(m\cdot val(f^*))$ è pseudo-polinomiale: se le capacità intere sono arbitrariamente grandi (es. $2^n$), $val(f^*)$ può essere esponenziale nel numero di bit necessari a rappresentarle, quindi il numero di iterazioni resta esponenziale nella dimensione dell'istanza.
### 11. Assenza di cammino in G_f ⇒ f massimo
*(26/06/2025 · Es. 1 · V/F 3 · motiva-vf)*
> Dato un flusso f, se nella rete residua G_f non c'è alcun cammino da s a t, allora f è un flusso massimo per G.

**Risposta.** **Vera.** Ponendo $A=\{v: \exists$ cammino $s\to v$ in $G_f\}$, $B=V\setminus A$, ogni arco forward $A\to B$ è saturo e ogni arco backward $B\to A$ ha $f=0$ (altrimenti esisterebbe arco residuo che estenderebbe la raggiungibilità), quindi $cap(A,B)=v(f)$: per weak duality nessun flusso può superare $cap(A,B)$, dunque $f$ è massimo.
### 12. Aumento lungo un singolo arco del cammino
*(26/06/2025 · Es. 1 · V/F 4 · motiva-vf)*
> Sia f un flusso e sia e un arco di un cammino P [...] è sempre possibile usare P per aumentare f di $c_f(e)$ [...]

**Risposta.** **Falsa.** L'incremento massimo lungo $P$ è il minimo delle capacità residue di **tutti** gli archi di $P$ (il bottleneck), non la capacità residua di un singolo arco $e$; se $e$ non è l'arco di collo di bottiglia, usare $c_f(e)$ violerebbe il vincolo di capacità su un altro arco di $P$.
### 13. Taglio minimo da nodi che raggiungono t
*(26/06/2025 · Es. 1 · V/F 5 · motiva-vf)*
> Sia f un flusso tale che [...] s e t sono separati. Sia B l'insieme dei nodi che possono raggiungere t. Allora $(V\setminus B, B)$ è un taglio minimo.

**Risposta.** **Vera.** Per ogni arco forward $u\to v$ con $u\notin B,v\in B$: se non fosse saturo esisterebbe arco residuo $u\to v$, e poiché $v$ raggiunge $t$ anche $u$ raggiungerebbe $t$, assurdo — quindi è saturo. Per ogni arco backward $v\to u$ con $v\in B,u\notin B$: se $f(v,u)>0$ esisterebbe arco residuo $u\to v$, stesso assurdo — quindi $f=0$. Il flusso netto attraverso il taglio è quindi $cap(V\setminus B,B)=v(f)$, che per max-flow min-cut lo rende minimo.
### 14. Complessità FF con grado entrante ≤3 e capacità ≤n²
*(26/06/2025 · Es. 1 · punto 2 · calcola-complessità)*
> [...] grado entrante al più 3 [...] capacità [...] non più grande di $n^2$. Si derivi una delimitazione superiore [...] e si dica se l'algoritmo è garantito polinomiale.

**Risposta.** Grado entrante $\le3$ per ogni nodo ⇒ $m=\sum_v \text{indeg}(v)\le 3n=O(n)$. $val(f^*)\le$ capacità del taglio attorno a $t$ (in-degree $\le3$, capacità $\le n^2$ ciascuna) $=O(n^2)$. Quindi $O(m\cdot val(f^*)) = O(n\cdot n^2)=O(n^3)$: sì, l'algoritmo è **garantito polinomiale** ($O(n^3)$), perché sia $m$ che la capacità massima raggiungibile sono limitati polinomialmente in $n$.
### 15. Definizione formale — minimum cut problem
*(18/07/2025 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema. (Max 5 righe.)

**Risposta.** Un **s-t taglio** $(A,B)$ è una partizione di $V$ con $s\in A, t\in B$. La sua **capacità** è $cap(A,B)=\sum_{e=(u,v):u\in A,v\in B} c(e)$ (solo archi diretti da $A$ a $B$). Il problema del taglio minimo chiede, tra tutti gli s-t tagli, quello di capacità minima.
### 16. Taglio minimo in tempo lineare da un flusso massimo
*(18/07/2025 · Es. 2 · punto 2 · altro)*
> Si descriva come calcolare in tempo lineare un taglio di capacità minima dato un flusso massimo.

**Risposta.** Dato $f$ massimo, si costruisce la rete residua $G_f$ ($O(m)$) e si esegue una BFS/DFS da $s$ su $G_f$ ($O(n+m)$): sia $A$ l'insieme dei nodi raggiunti, $B=V\setminus A$. $(A,B)$ è un taglio di capacità minima. Tempo totale $O(n+m)$.
### 17. Correttezza dell'algoritmo del punto 16
*(18/07/2025 · Es. 2 · punto 3 · discuti-correttezza)*
> Si discuta la correttezza dell'algoritmo fornito al punto precedente. (Max 5 righe.)

**Risposta.** Ogni arco forward $u\to v$ con $u\in A,v\in B$ deve essere saturo, altrimenti esisterebbe arco residuo $u\to v$ e $v\in A$, assurdo; ogni arco backward $v\to u$ deve avere $f=0$, altrimenti l'arco residuo inverso metterebbe $u$ (o meglio renderebbe $v$) raggiungibile, assurdo. Quindi il flusso netto attraverso $(A,B)$ è $cap(A,B)$, e per il flow-value lemma tale netto è $v(f)=v(f^*)$: per weak duality nessun taglio può avere capacità inferiore, dunque $(A,B)$ è minimo.
### 18. Definizione formale — massimo flusso
*(23/09/2025 · Es. 2 · punto 1 · definisci)*
> Si definisca formalmente il problema. (Max 5 righe.)

**Risposta.** Vedi item 1.
### 19. Definizione formale — rete residua
*(23/09/2025 · Es. 2 · punto 2 · definisci)*
> Si definisca formalmente il concetto di rete residua.

**Risposta.** Data $G=(V,E,s,t,c)$ e un flusso $f$, la rete residua $G_f=(V,E_f,c_f)$ contiene, per ogni $e=(u,v)\in E$: un arco $(u,v)$ con $c_f(u,v)=c(u,v)-f(u,v)$ se $>0$ (capacità residua in avanti), e un arco $(v,u)$ con $c_f(v,u)=f(u,v)$ se $>0$ (arco di ritorno, che permette di "disfare" flusso già instradato).
### 20. Dimostrazione — assenza di cammino aumentante ⇒ f massimo
*(23/09/2025 · Es. 2 · punto 3 · dimostra)*
> Si dimostri che se in $G_f$ non c'è cammino s→t, allora f è massimo. (Max 5 righe.)

**Risposta.** Sia $A=\{v : \exists$ cammino $s\to v$ in $G_f\}$ (per ipotesi $t\notin A$), $B=V\setminus A$. Per ogni arco $(u,v)\in E$ con $u\in A,v\in B$: se $f(u,v)<c(u,v)$ esisterebbe l'arco residuo $u\to v$, rendendo $v$ raggiungibile da $s$, assurdo; quindi $f(u,v)=c(u,v)$. Per ogni arco $(v,u)\in E$ con $v\in B,u\in A$: se $f(v,u)>0$ esisterebbe l'arco residuo inverso $u\to v$ in $G_f$, stesso assurdo; quindi $f(v,u)=0$. Il flusso netto attraverso $(A,B)$ vale dunque $cap(A,B)$, e per il flow-value lemma tale netto è $v(f)$: $v(f)=cap(A,B)$. Per weak duality $v(f')\le cap(A,B)$ per ogni flusso ammissibile $f'$, quindi $f$ è massimo. $\blacksquare$
### 21. Esistenza di un taglio con capacità = v(f)
*(02/02/2026 · Es. 1 · V/F 1 · motiva-vf)*
> Dato un flusso f di G, c'è sempre un s-t-taglio (A, B) la cui capacità è uguale a v(f).

**Risposta.** **Falsa.** Vale solo se $f$ è massimo (max-flow min-cut). Controesempio: rete con un unico arco $s\to t$ di capacità 5, e $f$ con $f(s,t)=1$ (non massimo): l'unico taglio possibile ha capacità $5\ne v(f)=1$.
### 22. Complessità FF con capacità intere ≤ n²
*(02/02/2026 · Es. 1 · V/F 2 · motiva-vf)*
> [...] complessità in generale esponenziale [...] ma sempre polinomiale quando le capacità sono interi non più grandi di $n^2$.

**Risposta.** **Vera.** Con capacità $\le n^2$, $val(f^*)\le m\cdot n^2$ e $m\le n^2$, quindi $val(f^*)=O(n^4)$; complessità $O(m\cdot val(f^*))=O(n^2\cdot n^4)=O(n^6)$, polinomiale in $n$. A differenza del caso generale (item 10), qui il bound numerico è esso stesso polinomiale nella dimensione dell'istanza, quindi la pseudo-polinomialità diventa polinomialità vera.
### 23. Augmenting step e incremento pari a β
*(02/02/2026 · Es. 1 · V/F 3 · motiva-vf)*
> Se per ogni arco e $c(e)\ge\beta$, allora ogni augmenting step aumenta il flusso corrente di almeno β.

**Risposta.** **Falsa.** L'incremento è il minimo delle capacità **residue** $c_f(e)=c(e)-f(e)$ (o $f(e)$ per archi di ritorno) lungo il cammino, che possono essere arbitrariamente piccole (anche $<\beta$) indipendentemente da quanto grandi siano le capacità originali $c(e)$.
### 24. Cammino in G_f ⇒ f non massimo
*(02/02/2026 · Es. 1 · V/F 4 · motiva-vf)*
> Dato un flusso f, se in Gf c'è un cammino da s a t, allora f non è massimo.

**Risposta.** **Vera.** Se esiste un cammino aumentante $P$ in $G_f$, si può incrementare $f$ lungo $P$ di una quantità pari al bottleneck (>0), ottenendo un flusso di valore strettamente maggiore; quindi $f$ non era massimo.
### 25. Complessità FF con m=Θ(n√n) archi e capacità ≤2
*(02/02/2026 · Es. 1 · V/F 5 · motiva-vf)*
> Se G ha $\Theta(n\sqrt n)$ archi e capacità $\le2$, allora FF ha complessità lineare $O(n\sqrt n)$.

**Risposta.** **Falsa.** $val(f^*)=O(n)$ (bound dato dal grado uscente di $s$), ma ogni iterazione costa $O(m)=O(n\sqrt n)$ per trovare il cammino aumentante (BFS/DFS); complessità totale $O(m\cdot val(f^*)) = O(n\sqrt n \cdot n) = O(n^2\sqrt n)$, non lineare in $m$. L'errore è confondere il numero di iterazioni con la complessità totale, trascurando il costo per iterazione.
### 26. Aumento di 1 alla capacità di un arco e algoritmo O(n+m)
*(02/02/2026 · Es. 1 · punto 2 · costruisci-esempio)*
> [...] Mostrate che non è sempre possibile aumentare il valore del flusso massimo [...] fornite un algoritmo O(n+m) [...]

**Risposta.** *Controesempio*: rete con $s\to a\to t$ (capacità 1 su entrambi gli archi) e $s\to t$ diretto (capacità 1); $val(f^*)=2$. Aumentando $c(s,a)$ a 2, il collo di bottiglia resta $a\to t$ (capacità 1): $val(f^*)$ resta 2.
*Algoritmo*: dato $f^*$, costruire $G_{f^*}$ ($O(m)$); BFS da $s$ in $G_{f^*}$ → insieme $A$ (raggiungibili da $s$); BFS da $t$ sul grafo inverso di $G_{f^*}$ → insieme $R$ (che raggiungono $t$); entrambe $O(n+m)$. Aumentare $c(u,v)$ di 1 incrementa $val(f^*)$ **se e solo se** $u\in A$ e $v\in R$ (si crea il cammino aumentante $s\to u\to v\to t$): verifica $O(1)$ per arco.
### 27. f massimo "solo se" assenza di cammino aumentante
*(30/06/2026 · Es. 1 · punto 1, V/F 1 · motiva-vf)*
> f è massimo solo se in $G_f$ non c'è alcun cammino da s a t.

**Risposta.** **Vera** (è la direzione facile del teorema, item 24 in forma contronominale): se esistesse un cammino aumentante in $G_f$, si potrebbe incrementare strettamente $f$ lungo di esso, contraddicendo la massimalità; quindi $f$ massimo implica necessariamente l'assenza di cammini aumentanti.
### 28. Un solo nodo con archi entranti unitari ⇒ FF polinomiale?
*(30/06/2026 · Es. 1 · punto 1, V/F 2 · motiva-vf)*
> Se esiste un nodo v i cui archi entranti hanno tutti capacità 1, FF è garantito polinomiale.

**Risposta.** **Falsa.** Una condizione locale su un solo nodo non limita in alcun modo $val(f^*)$ della rete complessiva: altri archi (non incidenti su $v$) possono avere capacità arbitrariamente grandi, rendendo il numero di iterazioni di FF ancora esponenziale nella dimensione dell'istanza.
### 29. Esistenza di un taglio con capacità = v(f) (duplicato)
*(30/06/2026 · Es. 1 · punto 1, V/F 3 · motiva-vf)*
> Per ogni flusso f, esiste sempre un taglio (A, B) la cui capacità è uguale al valore di f.

**Risposta.** Vedi item 21 (stessa affermazione, stesso controesempio).
### 30. Complessità FF con capacità tutte 1 → O(n³)
*(30/06/2026 · Es. 1 · punto 1, V/F 4 · motiva-vf)*
> Se tutti gli archi hanno capacità 1, FF ha complessità $O(n^3)$.

**Risposta.** **Vera.** Con capacità unitarie $val(f^*)=O(n)$ (item 8) e $m=O(n^2)$ in generale; ogni iterazione costa $O(m)=O(n^2)$ per trovare il cammino, quindi complessità totale $O(n\cdot n^2)=O(n^3)$.
### 31. Esistenza di un taglio con capacità stretta > v(f)
*(30/06/2026 · Es. 1 · punto 1, V/F 5 · motiva-vf)*
> Per ogni f esiste sempre almeno un taglio (A,B) tale che $cap(A,B) > v(f)$ (stretta).

**Risposta.** **Falsa.** Controesempio: rete con un unico arco $s\to t$ di capacità 5 e $f$ il flusso massimo ($v(f)=5$); l'unico taglio possibile è $(\{s\},\{t\})$ con $cap=5=v(f)$, non $>$. Non esiste in questo caso alcun taglio di capacità strettamente maggiore.
### 32. Taglio minimo dopo aumento uniforme delle capacità
*(30/06/2026 · Es. 1 · punto 2 · motiva-vf)*
> $(A,B)$ taglio minimo di G. $G'$ = G con ogni capacità aumentata di 1. $(A,B)$ è ancora minimo per G'?

**Risposta.** **Falsa.** $cap_{G'}(A,B) = cap_G(A,B) + |\{$archi che attraversano $(A,B)\}|$: l'aumento dipende dal **numero di archi** del taglio, non solo dalla sua capacità, quindi un taglio con meno archi crossing può "sorpassare" $(A,B)$ in $G'$. Esempio: $(A,B)$ minimo in $G$ con 3 archi di capacità 1 ($cap=3$); un altro taglio $(A',B')$ con 1 solo arco di capacità 4 ($cap=4>3$, non minimo in $G$). In $G'$: $cap_{G'}(A,B)=3\cdot2=6$, $cap_{G'}(A',B')=1\cdot5=5<6$: $(A,B)$ non è più minimo.
