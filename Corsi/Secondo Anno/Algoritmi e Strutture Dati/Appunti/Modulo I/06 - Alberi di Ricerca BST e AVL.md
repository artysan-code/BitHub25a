# Alberi di Ricerca BST e AVL
Il problema del [[05 - Strutture Dati Elementari e Dizionari|dizionario]] — implementare efficientemente le operazioni `search`, `insert` e `delete` — si risolve in modo elegante con strutture ad albero. L'idea di fondo è duplice: definire un **albero binario di ricerca (BST)** tale che ogni operazione costi $O(\text{altezza})$, e poi garantire che l'altezza resti sempre $O(\log n)$ tramite il meccanismo di auto-bilanciamento degli **alberi AVL**. Il risultato è un dizionario con tutte le operazioni garantite in $O(\log n)$ nel senso della [[02 - Notazioni Asintotiche|notazione asintotica]].
## Alberi Binari di Ricerca (BST)
> [!quote] Definizione — Albero Binario di Ricerca (BST)
> Un **albero binario di ricerca** è un albero binario in cui ogni nodo $v$ contiene un elemento `elem(v)` con chiave `chiave(v)` presa da un dominio totalmente ordinato, e vale la seguente **proprietà di ricerca**:
> - le chiavi nel **sottoalbero sinistro** di $v$ sono $\le$ `chiave(v)`;
> - le chiavi nel **sottoalbero destro** di $v$ sono $>$ `chiave(v)`.

La convenzione del prof. Gualà pone le chiavi **uguali a sinistra**: un nodo con chiave $k$ ha a sinistra le chiavi $\le k$ e a destra le chiavi $> k$. Questa scelta deve essere rispettata coerentemente in tutte le operazioni.
### Proprietà chiave: visita in ordine simmetrico
La **visita in ordine simmetrico** (sinistra → radice → destra) di un BST restituisce le chiavi in ordine crescente. Si dimostra per induzione sull'altezza $h$:
- **Caso base** $h = 1$: i due figli $u$ e $v$ soddisfano `chiave(u) ≤ chiave(r) < chiave(v)` per la proprietà di ricerca.
- **Passo induttivo**: supposta la correttezza per altezza $< h$, il sottoalbero sinistro (altezza $h - 1$) produce chiavi $\le$ `chiave(r)` in ordine crescente, il sottoalbero destro (altezza $h - 1$) produce chiavi $>$ `chiave(r)` in ordine crescente; concatenando si ottiene la sequenza ordinata.

Esempio di BST con $n = 10$ nodi:

```
           15
          /  \
         6    18
        / \  /  \
       3   8 17  20
      / \   \
     2   4   13
             /
            9
Visita simmetrica: 2 3 4 6 8 9 13 15 17 18 20
```

> [!example] Domanda tipica d'esame
> **D:** Come si usa un BST per ottenere una sequenza ordinata? **R:** Si esegue una **visita in ordine simmetrico** (sinistra → radice → destra): la proprietà di ricerca garantisce che i nodi vengano visitati in ordine crescente di chiave, con costo $\Theta(n)$.
### Operazioni di ricerca
Tutte le operazioni del dizionario su un BST costano $O(h)$ dove $h$ è l'altezza dell'albero.
#### Search
Si traccia un cammino dalla radice verso il basso. Ad ogni nodo $v$ si confronta la chiave cercata $k$ con `chiave(v)`:
- se $k =$ `chiave(v)` si restituisce il nodo corrente (trovato);
- se $k <$ `chiave(v)` si prosegue a sinistra;
- se $k >$ `chiave(v)` si prosegue a destra;
- se il nodo corrente è `null`, la chiave non è presente.

**`search(chiave k)`**
```text
search(BST T, chiave k)
1. curr = T.radice
2. while curr ≠ null and k ≠ chiave(curr) do
3.   if k ≤ chiave(curr) then curr = curr.sx
4.   else curr = curr.dx
5. return curr
```
#### Minimo e Massimo
Grazie alla proprietà di ricerca, il **minimo** si trova seguendo sempre i puntatori sinistri fino al nodo più a sinistra; il **massimo** seguendo i puntatori destri.

**`min(nodo u)`**
```text
min(nodo u)
1. curr = u
2. while curr.sx ≠ null do
3.   curr = curr.sx
4. return curr
```

`max(nodo u)` è simmetrica: si segue il puntatore destro.
#### Successore e Predecessore
Il **successore** di un nodo $u$ è il nodo con la minima chiave strettamente maggiore di `chiave(u)`. Si individuano due casi:
- **Caso 1 — $u$ ha figlio destro:** il successore è `min(u.dx)` (il minimo del sottoalbero destro).
- **Caso 2 — $u$ non ha figlio destro:** si risale verso la radice finché non si incontra il primo antenato $p$ di cui $u$ è nel sottoalbero **sinistro**; $p$ è il successore.

```
           15          ← suc(8): caso 1 → min(sottoalbero destro di 8) = 9
          /  \
         6    18
        / \  /  \
       3   8 17  20
              \
              13
              /
             9
suc(6): caso 1 → min(sottoalbero destro di 6) = 8
suc(13): caso 2 → risale fino a 8, poi a 6, poi a 15 (15 ha 6 come figlio sinistro) → suc = 15
```

**`successore(nodo u)`**
```text
successore(nodo u)
1. if u.dx ≠ null then return min(u.dx)
2. p = u.padre
3. while p ≠ null and u == p.dx do
4.   u = p
5.   p = p.padre
6. return p
```

Il **predecessore** è simmetrico: massimo del sottoalbero sinistro se esiste, altrimenti primo antenato di cui il nodo è figlio destro.
### Operazioni di modifica
#### Insert
Il nuovo elemento viene inserito sempre come **foglia**, simulando una ricerca con la chiave da inserire per individuare la posizione corretta.

1. Creare un nuovo nodo $u$ con `elem = e`, `chiave = k`.
2. Simulare `search(k)` tenendo traccia del padre $v$ dell'ultimo nodo visitato.
3. Appendere $u$ come figlio sinistro di $v$ se $k \le$ `chiave(v)`, altrimenti come figlio destro.

**`insert(elem e, chiave k)`**
```text
insert(BST T, elem e, chiave k)
1. u = nuovo nodo con elem = e, chiave = k
2. padre = null, curr = T.radice
3. while curr ≠ null do
4.   padre = curr
5.   if k ≤ chiave(curr) then curr = curr.sx
6.   else curr = curr.dx
7. u.padre = padre
8. if padre == null then T.radice = u         // albero era vuoto
9. else if k ≤ chiave(padre) then padre.sx = u
10. else padre.dx = u
```

> [!info] Coerenza con la convenzione sx $\le$, dx $>$
> Alle righe 5 e 9 la condizione è $k \le$ `chiave(curr)`: chiavi uguali vanno a **sinistra**. Questo è coerente con la proprietà di ricerca (sottoalbero sinistro $\le$ chiave del nodo).

Correttezza: per costruzione ogni antenato di $u$ lo contiene nel sottoalbero corretto.

Esempio — `insert(e, 8)` nell'albero `[15, 6, 18, 3, 9, 17, 20, 2, 4, 7, 13]`:
```
Prima                     Dopo
     15                       15
    /  \                      /  \
   6    18                   6    18
  / \  /  \                 / \  /  \
 3   9 17  20              3   9 17  20
/ \ /     \               / \ /     \
2  4 7    13              2  4 7    13
                               \
                                8   ← nuovo nodo (8 ≤ 9, va a sx di 9... ma 8 > 7 → dx di 7)
```
#### Delete
La cancellazione distingue tre casi in base al numero di figli del nodo $u$ da rimuovere:

**Caso 1 — $u$ è una foglia:** si rimuove direttamente aggiornando il puntatore del padre a `null`.

**Caso 2 — $u$ ha un solo figlio:** si "scavalca" $u$ collegando il padre direttamente all'unico figlio.

**Caso 3 — $u$ ha due figli:** non si può rimuovere $u$ direttamente. Si individua il **predecessore** (o successore) $v$ di $u$ — che ha al più un figlio — si copia il contenuto di $v$ in $u$, e si rimuove fisicamente $v$ (che ricade nei casi 1 o 2).

```
delete(u) con u avente chiave 4, due figli:

     15
    /  \
   6    18
  / \  /  \
 3   9 17  20
/ \ /
2  4 7            → u = nodo(4), predecessore v = nodo(2) (max del sottoalbero sx di 4)
   /\                  oppure successore v = nodo(7) (min del sottoalbero dx di 4)
  ...
```

**`delete(BST T, nodo u)`**
```text
delete(BST T, nodo u)
1. if u.sx == null or u.dx == null then y = u     // 0 o 1 figlio: rimuovi u
2. else y = successore(u)                          // 2 figli: rimuovi il successore
3. // y è il nodo da rimuovere fisicamente (ha al più 1 figlio)
4. if y.sx ≠ null then x = y.sx else x = y.dx
5. if x ≠ null then x.padre = y.padre
6. if y.padre == null then T.radice = x
7. else if y == y.padre.sx then y.padre.sx = x
8. else y.padre.dx = x
9. if y ≠ u then copia elem e chiave di y in u    // caso 3: copia il contenuto
```
### Analisi del costo
> [!warning] Il problema del bilanciamento
> Tutte le operazioni sul BST costano $O(h)$, dove $h$ è l'altezza dell'albero.
> - **BST bilanciato (completo):** $h = \Theta(\log n) \Rightarrow$ operazioni in $O(\log n)$.
> - **BST degenere (lista):** $h = \Theta(n) \Rightarrow$ operazioni in $O(n)$, pessime quanto una lista.
>
> Il caso degenere si verifica ad esempio inserendo chiavi già in ordine crescente: ogni nodo diventa figlio destro del precedente, producendo un albero "linearizzato". La soluzione è garantire strutturalmente che $h = O(\log n)$ — ed è qui che entrano gli **alberi AVL**.

> [!example] Domanda tipica d'esame
> **D:** Qual è il costo di `search` su un BST? Quando è peggiore? **R:** Il costo è $O(h)$ dove $h$ è l'altezza. Nel **caso peggiore** — albero degenere ottenuto inserendo elementi già ordinati — $h = \Theta(n)$ e la ricerca costa $O(n)$ come in una lista. Nel caso di albero bilanciato $h = \Theta(\log n)$.
## Alberi AVL
Gli **alberi AVL** (Adel'son-Vel'skii e Landis, 1962) sono BST che si auto-bilanciano dopo ogni inserimento o cancellazione, garantendo $h = O(\log n)$ sempre.
> [!quote] Definizione — Fattore di bilanciamento
> Il **fattore di bilanciamento** $\beta(v)$ di un nodo $v$ è:
> $$\beta(v) = h(\text{sottoalbero sinistro di } v) - h(\text{sottoalbero destro di } v)$$
> dove $h(\text{albero vuoto}) = -1$ per convenzione.
>
> Un albero si dice **bilanciato in altezza** se ogni nodo $v$ ha $|\beta(v)| \le 1$.
>
> Un **albero AVL** è un BST bilanciato in altezza.

Il valore $\beta(v)$ è generalmente mantenuto come campo aggiuntivo nel record di ogni nodo (in alternativa si memorizza il campo **altezza** del sottoalbero radicato in $v$, dal quale $\beta$ si calcola in $O(1)$).
### Esempi di alberi AVL
Albero bilanciato con $\beta = 0$ per tutti i nodi:
```
                 15  (β=0)
               /    \
        (β=0) 6      20 (β=0)
             / \    /  \
       (β=0)3   8  17   27 (β=0)
            / \ / \/ \  / \
           2  4 7 13 16 19 22 30
```
Albero AVL con fattori non tutti nulli — è comunque AVL (tutti $|\beta| \le 1$):
```
              15  (β=+1)
            /    \
     (β=-1) 6      18 (β=-1)
           / \       \
     (β=0)3   8(β=-1) 20(β=-1)
         / \   \          \
        2   4   10(β=0)    25(β=0)
               /  \
          (β=0)9  13(β=0)
```
Albero **NON** AVL — presenta fattori $|\beta| = 2$ in più nodi:
```
        30  (β=5 → NON AVL)
       /
      27
     /
    22
   /
  20
 /
19
/
17
```
### Teorema sull'altezza degli AVL
> [!quote] Teorema — Altezza degli alberi AVL
> Un albero AVL con $n$ nodi ha altezza $h = O(\log n)$.

**Idea della dimostrazione.** Si considerano, tra tutti gli AVL di altezza $h$, quelli con il **minimo numero di nodi** $n_h$ — chiamati **alberi di Fibonacci** $T_h$. Se anche questi alberi "massimamente sbilanciati" hanno altezza $O(\log n)$, lo stesso vale per ogni AVL.

Schema ricorsivo degli alberi di Fibonacci:

```
T0       T1         T2              T3
●        ●          ●               ●
         |         / \             / \
         ●        ●   ●           ●   ●
                  |              / \ |
                  ●             ●  ●  ●
                                   |
                                   ●
```

Ogni nodo non foglia ha $|\beta| = 1$; togliendo qualsiasi nodo o l'albero si sbilancia o cambia altezza.
> [!quote] Lemma — Nodi degli alberi di Fibonacci
> Sia $n_h$ il numero di nodi di $T_h$. Allora:
> $$n_h = F_{h+3} - 1$$
> dove $F_k$ è il $k$-esimo numero di Fibonacci.
>
> **Dimostrazione per induzione su $h$:** si usa la relazione $n_h = 1 + n_{h-1} + n_{h-2}$ (radice + due sottoalberi di Fibonacci di altezze $h-1$ e $h-2$); la struttura ricorsiva richiama quella delle [[03 - Equazioni di Ricorrenza|equazioni di ricorrenza]].
> [!quote] Corollario — $h = O(\log n)$
> Poiché $F_k = \Theta(\phi^k)$ con $\phi = 1{,}618\ldots$ (sezione aurea; si veda [[01 - Il Problema di Fibonacci]] per la sequenza di Fibonacci), si ha:
> $$n_h = F_{h+3} - 1 = \Theta(\phi^h)$$
> Quindi $h = \Theta(\log_\phi n_h) = O(\log n)$. Siccome ogni AVL con $n$ nodi ha $n \ge n_h$, vale $h = O(\log n)$.

> [!example] Domanda tipica d'esame
> **D:** Perché un albero AVL ha altezza $O(\log n)$? **R:** Si considera l'albero di Fibonacci $T_h$ — l'AVL di altezza $h$ con il **minimo numero di nodi** $n_h$. Vale $n_h = F_{h+3} - 1 = \Theta(\phi^h)$, quindi $h = O(\log n)$. Ogni AVL con $n \ge n_h$ nodi ha altezza al più $h$, dunque $h = O(\log n)$.
### Implementazione delle operazioni
`search` si esegue identica al BST, con costo $O(\log n)$ garantito dall'altezza.

Inserimenti e cancellazioni possono però alterare i fattori di bilanciamento. Dopo ogni operazione si aggiornano i $\beta$ lungo il cammino radice-nodo modificato (i fattori cambiano di $\pm 1$ solo lungo quel cammino) e si ripristina il bilanciamento con **rotazioni**.

> [!info] Quanto cambiano i fattori di bilanciamento?
> A fronte di un inserimento o cancellazione cambiano solo i fattori di bilanciamento dei nodi lungo il **cammino radice → nodo inserito/cancellato**, e di al più $\pm 1$ per nodo.
### Rotazioni di base
> [!quote] Proprietà — Rotazioni
> Una rotazione semplice (destra o sinistra) su un nodo:
> - mantiene la **proprietà di ricerca** del BST;
> - richiede tempo $O(1)$ (solo aggiornamenti di puntatori locali).

**Rotazione verso destra sul nodo $v$** (il figlio sinistro $u$ sale al posto di $v$):
```
     v                u
    / \              / \
   u   T3    →     T1   v
  / \                  / \
 T1  T2               T2  T3
```

**Rotazione verso sinistra sul nodo $v$** (simmetrica): il figlio destro sale al posto di $v$.
### I 4 casi di ribilanciamento
Sia $v$ il **nodo critico**: il nodo di profondità massima con $|\beta(v)| = 2$. Esistono 4 casi (simmetrici a coppie) in base alla posizione del sottoalbero che ha provocato lo sbilanciamento.

Sia $h$ l'altezza del sottoalbero **destro** di $v$.
#### Caso SS — $\beta(v) = +2$, sbilanciamento a sinistra-sinistra
Il sottoalbero sinistro del figlio sinistro $u$ di $v$ ha altezza $h + 1$.

```
Prima (sbilanciato):           Dopo rotazione destra su v:
        v (β=+2)                       u
       / \                            / \
      u   T3(h)                     T1   v
     / \                                / \
  T1(h+1) T2(h o h+1)               T2   T3
```

Si applica una **rotazione semplice verso destra** su $v$. L'altezza dell'albero:
- **sottocaso (i)** $h(T_2) = h$: l'altezza passa da $h + 3$ a $h + 2$ (diminuisce di 1).
- **sottocaso (ii)** $h(T_2) = h + 1$: l'altezza rimane $h + 3$.

> [!info] Inserimento vs cancellazione nel caso SS
> - **Insert** può provocare solo il sottocaso (i) (l'albero era bilanciato prima dell'inserimento).
> - **Delete** può provocare entrambi i sottocasi.
#### Caso DD — $\beta(v) = -2$, sbilanciamento a destra-destra
Simmetrico al caso SS. Il sottoalbero destro del figlio destro $u$ di $v$ ha altezza $h + 1$.

```
Prima (sbilanciato):           Dopo rotazione sinistra su v:
   v (β=-2)                           u
  / \                                / \
 T3(h) u                            v   T1(h+1)
       / \                         / \
  T2(h o h+1) T1(h+1)            T3  T2
```

Si applica una **rotazione semplice verso sinistra** su $v$.
#### Caso SD — $\beta(v) = +2$, sbilanciamento a sinistra-destra
$\beta(v) = +2$, ma lo sbilanciamento è provocato dal **sottoalbero destro** del figlio sinistro $z$ di $v$ (altezza $T_1 = h$, altezza $T(w) = h + 1$).

```
Prima:                         Dopo rot. sinistra su z:    Dopo rot. destra su v:
     v (β=+2)                        v (β=+2)                     w
    / \                             / \                           / \
   z(β=-1) T4(h)                  w   T4                        z   v
  / \                            / \                           / \ / \
 T1(h) w                        z   T3                       T1 T2 T3 T4
       / \                     / \
      T2  T3                  T1  T2
```

Si applicano **due rotazioni**:
1. Rotazione semplice verso **sinistra** su $z$ (figlio sinistro di $v$).
2. Rotazione semplice verso **destra** su $v$.

L'altezza dell'albero passa da $h + 3$ a $h + 2$. Il caso SD può essere provocato sia da inserimenti (in $T_2$ o $T_3$) sia da cancellazioni.
#### Caso DS — $\beta(v) = -2$, sbilanciamento a destra-sinistra
Simmetrico al caso SD. Si applicano:
1. Rotazione semplice verso **destra** sul figlio destro di $v$.
2. Rotazione semplice verso **sinistra** su $v$.

| Caso | $\beta(v)$ | Causa | Rotazioni |
|:--|:-:|:--|:--|
| **SS** | $+2$ | sottoalbero sinistro del figlio sx | 1 destra su $v$ |
| **DD** | $-2$ | sottoalbero destro del figlio dx | 1 sinistra su $v$ |
| **SD** | $+2$ | sottoalbero destro del figlio sx | 1 sinistra su figlio, 1 destra su $v$ |
| **DS** | $-2$ | sottoalbero sinistro del figlio dx | 1 destra su figlio, 1 sinistra su $v$ |

> [!example] Domanda tipica d'esame
> **D:** Quali sono i 4 casi di rotazione negli AVL e quando si applicano? **R:** I casi dipendono dal segno di $\beta(v)$ (nodo critico) e dalla posizione del sottoalbero che sbilancia. **SS** ($\beta = +2$, sottoalbero sx-sx): rotazione semplice destra. **DD** ($\beta = -2$, sottoalbero dx-dx): rotazione semplice sinistra. **SD** ($\beta = +2$, sottoalbero sx-dx): doppia rotazione (sinistra sul figlio, destra su $v$). **DS** ($\beta = -2$, sottoalbero dx-sx): doppia rotazione (destra sul figlio, sinistra su $v$). I 4 casi sono simmetrici a coppie: SS↔DD, SD↔DS.
### Insert nell'AVL
**`insert(elem e, chiave k)` — AVL**
```text
insert(AVL T, elem e, chiave k)
1. Crea un nuovo nodo u con elem = e, chiave = k
2. Inserisci u come in un BST (righe 1–10 della procedura BST)
3. Ricalcola i fattori di bilanciamento dei nodi nel cammino da u alla radice
4. Sia v il nodo critico più profondo (il primo con |β(v)| = 2)
5. if v esiste then
6.   Determina il caso (SS / DD / SD / DS)
7.   Esegui la rotazione opportuna su v
```

> [!info] Perché basta una sola rotazione per insert
> Dopo la rotazione, l'altezza del sottoalbero ruotato **torna uguale** a quella che aveva prima dell'inserimento (si ricade sempre nel sottocaso (i) del caso SS o DD, o nei casi SD/DS). Pertanto nessun altro nodo verso la radice si sbilancia: **una sola rotazione (semplice o doppia) è sempre sufficiente**.

**Esempio — `insert(e, 10)` nell'AVL:**
```
Prima dell'insert:         Dopo l'insert di 10:      Rotazione SD su nodo 13:
      15 (β=+1)                 15 (β=+2)                  15
     /    \                    /    \                      /    \
    6      18                 6      18                   6      18
   / \    /  \               / \    /  \                 / \    /  \
  3   8  17  20             3   8  17  20               3   8  17  20
 / \ / \                   / \ / \                     / \ / \
2  4 7  13                2  4 7  13(β=+2)            2  4 7  10(β=0)
                                  /                             / \
                                 9(β=0)                        9  13
                                  \
                                  10(β=0)
```
### Delete nell'AVL
**`delete(elem e)` — AVL**
```text
delete(AVL T, elem e)
1. Cancella il nodo contenente e come in un BST (3 casi)
2. curr = padre del nodo eliminato fisicamente
3. while curr ≠ null do
4.   Ricalcola β(curr)
5.   if |β(curr)| == 2 then
6.     Determina il caso e applica la rotazione opportuna su curr
7.     if altezza del sottoalbero di curr uguale a prima della cancellazione then
8.       break   // sbilanciamento non si propaga, termina
9.   curr = curr.padre
```

> [!warning] Delete richiede fino a $O(\log n)$ rotazioni
> Diversamente dall'insert, nella cancellazione la rotazione può **abbassare l'altezza** del sottoalbero ribilanciato di 1 rispetto a prima della cancellazione, propagando lo sbilanciamento verso la radice. Occorre quindi risalire l'intero cammino fino alla radice, applicando una rotazione per ogni livello sbilanciato: nel caso peggiore $O(\log n)$ rotazioni.

**Esempio — `delete(18)` con rotazioni a cascata:**
```
Prima:                   Dopo cancellazione 18        Dopo rot. DD su 20:
    15(β=+1)             (predecessore 17 sale):
   /    \                    15(β=+2)                      15(β=+1)
  6      18(β=-1)           /    \                        /    \
 / \    /    \             6      20(β=-2)               6      17(β=0)
3   8  17    20           / \    /    \                 / \    /    \
                         3   8  17    25               3   8 13     20
                                \                             \      \
                                13                            (...)  25
```
Continuando a risalire, se il padre della radice del sottoalbero appena ribilanciato risulta a sua volta sbilanciato, si applica un'ulteriore rotazione.
### Campo altezza nei nodi
Per garantire $O(1)$ per il calcolo di $\beta(v)$ e $O(\log n)$ per l'aggiornamento dei fattori lungo il cammino, ogni nodo $v$ memorizza il campo **`altezza(v)`** (altezza del sottoalbero radicato in $v$).

```text
aggiornaAltezza(nodo v)
1. h_sx = altezza(v.sx)   // -1 se v.sx == null
2. h_dx = altezza(v.dx)   // -1 se v.dx == null
3. v.altezza = 1 + max(h_sx, h_dx)
4. β(v) = h_sx - h_dx
```

Dopo ogni rotazione si aggiornano i campi altezza dei nodi coinvolti in $O(1)$.

Le tre proprietà richieste per la correttezza dell'implementazione:
1. Dato un nodo $v$, calcolare $\beta(v)$ in $O(1)$ — garantito dal campo `altezza`.
2. Dopo insert/delete, ricalcolare i $\beta$ lungo il cammino radice-nodo in $O(\log n)$ — il cammino ha lunghezza $O(\log n)$ e ogni aggiornamento costa $O(1)$.
3. Durante le rotazioni, aggiornare i $\beta$ dei nodi coinvolti in $O(\log n)$ complessivo — al più $O(\log n)$ rotazioni, ognuna $O(1)$.
### Riepilogo complessità AVL
| Operazione | Complessità | Note |
|:--|:-:|:--|
| `search` | $O(\log n)$ | identica al BST; garantita da $h = O(\log n)$ |
| `insert` | $O(\log n)$ | inserimento BST + al più **1 rotazione** |
| `delete` | $O(\log n)$ | cancellazione BST + fino a $O(\log n)$ rotazioni |
| `min` / `max` | $O(\log n)$ | cammino più a sinistra/destra |
| `successore` / `predecessore` | $O(\log n)$ | cammino di lunghezza $O(h)$ |

> [!example] Domanda tipica d'esame
> **D:** Perché insert in un AVL richiede al più 1 rotazione mentre delete può richiederne $O(\log n)$? **R:** Nell'**insert** la rotazione riporta l'altezza del sottoalbero ruotato uguale a quella precedente l'inserimento, quindi nessun antenato si sbilancia ulteriormente. Nella **delete**, invece, la rotazione può abbassare l'altezza di 1, propagando lo sbilanciamento verso l'alto: nel caso peggiore occorre ribilanciare ad ogni livello fino alla radice, per un totale di $O(\log n)$ rotazioni.

> [!info] Confronto BST vs AVL
> Il BST semplice ha operazioni $O(h)$: ottimo in media (albero casuale ha $h = O(\log n)$) ma degradante in $O(n)$ in caso patologico. L'AVL garantisce $h = O(\log n)$ sempre, a fronte di un overhead di $O(\log n)$ rotazioni per mantenere il bilanciamento. Per l'implementazione di un [[05 - Strutture Dati Elementari e Dizionari|dizionario]] in cui non si ha controllo sull'ordine degli inserimenti, l'AVL è la scelta corretta.
