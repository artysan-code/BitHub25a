# Il Problema di Fibonacci
Il **problema di Fibonacci** è il caso di studio introduttivo del corso: permette di confrontare diverse strategie algoritmiche per uno stesso problema e di ragionare in modo qualitativo sulla **complessità temporale e spaziale** senza ancora le notazioni formali (trattate in [[02 - Notazioni Asintotiche]]). Il punto centrale non è Fibonacci in sé, ma capire che algoritmi diversi e corretti possono avere costi radicalmente differenti.
## L'isola dei conigli
Leonardo da Pisa (Fibonacci, XIII sec.) si chiese: partendo da una coppia di conigli in un'isola deserta, quante coppie esisterebbero nell'anno $n$, date queste regole?
- Una coppia genera ogni anno due coniglietti di sesso diverso (una nuova coppia).
- La gestazione dura un anno.
- I conigli si riproducono solo dal secondo anno di vita.
- I conigli sono immortali.
Nell'anno $n$ sono presenti tutte le coppie dell'anno precedente ($F_{n-1}$) più una nuova coppia per ogni coppia presente due anni prima ($F_{n-2}$), da cui la relazione di ricorrenza.
> [!quote] Definizione — Numeri di Fibonacci
> $$F_n = \begin{cases} F_{n-1} + F_{n-2} & \text{se } n \geq 3 \\ 1 & \text{se } n = 1, 2 \end{cases}$$
> (Per convenzione si fissa $F_0 = 0$, utile nelle dimostrazioni per induzione.)

I primi valori della sequenza sono: $1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, F_{18}=2584, \ldots$

Il problema computazionale è: dato $n$, calcolare $F_n$.
## Strategie risolutive
### Algoritmo 1 — Formula di Binet
**Approccio numerico**: si può dimostrare che esiste una formula chiusa, detta **formula di Binet**:

$$F_n = \frac{1}{\sqrt{5}}\left(\phi^n - \hat{\phi}^n\right) \qquad \phi = \frac{1+\sqrt{5}}{2} \approx 1{,}618, \quad \hat{\phi} = \frac{1-\sqrt{5}}{2} \approx -0{,}618$$

**fibonacci1** implementa direttamente questa formula:

```text
fibonacci1(intero n) → intero
1.  return (1/sqrt(5)) * (phi^n - hat_phi^n)
```

> [!warning] Problema di correttezza
> La formula richiede di calcolare $\phi$ e $\hat{\phi}$ con precisione arbitraria. Con un numero finito di cifre decimali si commettono errori di arrotondamento che si amplificano al crescere di $n$.
> Esempio (3 cifre decimali): per $n=18$ si ottiene $2583{,}1$, arrotondato a $2583$, ma il valore corretto è $F_{18} = 2584$.
> **fibonacci1 non è corretto** per tutti gli $n$: produce risultati errati su istanze anche modeste.
### Algoritmo 2 — Ricorsione diretta
**Approccio**: applicare direttamente la definizione ricorsiva (tecnica del *divide et impera*).

```text
fibonacci2(intero n) → intero
1.  if (n ≤ 2) then return 1
2.  else return fibonacci2(n-1) + fibonacci2(n-2)
```

fibonacci2 è **corretto**. Per analizzarne il costo, modelliamo il tempo $T(n)$ come numero di righe di codice eseguite (ogni riga costa un'unità di tempo).

Ogni chiamata esegue 2 righe proprie, più le chiamate ricorsive:

$$T(n) = 2 + T(n-1) + T(n-2), \qquad T(1) = T(2) = 1$$

Per risolvere questa ricorrenza (trattata sistematicamente in [[03 - Equazioni di Ricorrenza]]) si usa l'**albero della ricorsione**.
#### Albero della ricorsione di fibonacci2
L'albero ha tanti nodi quante sono le chiamate ricorsive. Etichettando ogni nodo con il numero di righe eseguite nella sua chiamata:
- ogni **nodo interno** ha etichetta $2$ (esegue la riga `if` e la riga `return`);
- ogni **foglia** ha etichetta $1$ (esegue solo la riga `if` e ritorna 1).

Il numero totale di righe eseguite è quindi:

$$T(n) = 2 \cdot (\text{nodi interni}) + 1 \cdot (\text{foglie})$$

Servono due lemmi per contare foglie e nodi interni.
> [!quote] Lemma 1 — Foglie dell'albero di ricorsione
> Il numero di foglie dell'albero della ricorsione di fibonacci2(n) è pari a $F_n$.
> **Dimostrazione** (per induzione su $n$):
> - Caso base $n=1,2$: l'albero ha una sola foglia, e $F_1 = F_2 = 1$. ✓
> - Caso induttivo $n > 2$: l'albero di fibonacci2(n) ha radice con due sottoalberi, uno per fibonacci2(n-1) e uno per fibonacci2(n-2). Per ipotesi induttiva i due sottoalberi hanno rispettivamente $F_{n-1}$ e $F_{n-2}$ foglie; in totale $F_{n-1} + F_{n-2} = F_n$. ✓

> [!quote] Lemma 2 — Nodi interni
> In un albero binario in cui ogni nodo interno ha esattamente due figli, il numero di nodi interni è pari al numero di foglie meno 1.
> **Dimostrazione** (per induzione sul numero di nodi dell'albero):
> - Caso base: l'albero ha solo la radice (una foglia), $i=0$ nodi interni, $f=1$ foglia; $i = f - 1 = 0$. ✓
> - Caso induttivo: si prende una coppia di foglie sorelle e si rimuovono entrambe. Il padre diventa una foglia nel nuovo albero $T'$ con $i' = i-1$ nodi interni e $f' = f-1$ foglie. Per ipotesi induttiva $i' = f' - 1$, cioè $i-1 = f-1-1$, quindi $i = f-1$. ✓

Dai due lemmi, il tempo totale di fibonacci2(n) è:

$$T(n) = F_n + 2(F_n - 1) = 3F_n - 2$$

Poiché $F_n \approx \phi^n / \sqrt{5}$, si ha $T(n) = O(\phi^n)$, crescita **esponenziale**.
> [!example] Domanda tipica d'esame
> D: Qual è la complessità temporale di fibonacci2? Perché è così lenta?
> R: $T(n) = 3F_n - 2 = O(\phi^n)$, esponenziale in $n$. La causa è che fibonacci2 **ricalcola ripetutamente gli stessi sottoproblemi**: ad esempio fibonacci2(n-2) viene calcolato sia dalla chiamata fibonacci2(n-1) sia direttamente. Per $n=45$ si eseguono $3 \cdot F_{45} - 2 = 3 \cdot 1\,134\,903\,170 - 2 = 3\,404\,709\,508$ righe di codice; con le tecnologie attuali, calcolare $F_{100}$ richiederebbe circa 8000 anni.

**Spazio** (memoria ausiliaria): le chiamate attive formano un cammino dalla radice al nodo corrente nell'albero della ricorsione; tale cammino ha al più $n$ nodi, ciascuno con memoria costante. Quindi fibonacci2 usa spazio $O(n)$.
### Algoritmo 3 — Programmazione dinamica (array)
**Idea**: memorizzare le soluzioni dei sottoproblemi in un array per evitare ricalcoli (tecnica della **programmazione dinamica**).

```text
fibonacci3(intero n) → intero
1.  sia Fib un array di n interi
2.  Fib[1] ← 1; Fib[2] ← 1
3.  for i = 3 to n do
4.      Fib[i] ← Fib[i-1] + Fib[i-2]
5.  return Fib[n]
```

fibonacci3 è **corretto** (calcola $F_n$ esattamente, senza aritmetica in virgola mobile).

**Analisi del tempo**: le righe 1, 2 e 5 si eseguono una sola volta; le righe 3 e 4 al più $n$ volte ciascuna. In totale:

$$T(n) \leq 2n + 3 = O(n)$$

Per $n=45$: $T(45) \leq 93$ righe — contro le $3{,}4$ miliardi di fibonacci2. Un miglioramento di circa 38 milioni di volte.

**Spazio**: l'array Fib occupa $n$ celle, quindi $O(n)$.
### Algoritmo 4 — Iterativo con spazio costante
**Osservazione**: per calcolare $F_n$ servono solo i due valori precedenti. Non occorre un array di dimensione $n$.

```text
fibonacci4(intero n) → intero
1.  a ← 1; b ← 1; c ← 1
2.  for i = 3 to n do
3.      c ← a + b
4.      a ← b
5.      b ← c
6.  return c
```

**Analisi del tempo**: $T(n) \leq 4n + 2 = O(n)$ (costante per iterazione, $n-2$ iterazioni).

**Spazio**: solo tre variabili scalari, indipendentemente da $n$: $O(1)$.
> [!info] Confronto fibonacci3 vs fibonacci4
> Hanno la stessa complessità temporale $O(n)$, ma fibonacci4 usa spazio $O(1)$ invece di $O(n)$. La memoria può essere la risorsa critica: se un algoritmo richiede più spazio di quello disponibile non termina mai, indipendentemente dall'attesa.
### Algoritmo 5 — Potenza di matrice (iterativa)
**Approccio**: si può dimostrare per induzione la seguente proprietà.
> [!quote] Proprietà — Potenza di matrice
> $$\begin{pmatrix}1 & 1\\1 & 0\end{pmatrix}^n = \begin{pmatrix}F_{n+1} & F_n\\F_n & F_{n-1}\end{pmatrix}$$
> **Dimostrazione** (per induzione su $n$, con $F_0 = 0$):
> - Caso base $n=1$: $\begin{pmatrix}1&1\\1&0\end{pmatrix}^1 = \begin{pmatrix}F_2&F_1\\F_1&F_0\end{pmatrix} = \begin{pmatrix}1&1\\1&0\end{pmatrix}$. ✓
> - Caso induttivo $n>1$: $\begin{pmatrix}1&1\\1&0\end{pmatrix}^n = \begin{pmatrix}1&1\\1&0\end{pmatrix}^{n-1}\begin{pmatrix}1&1\\1&0\end{pmatrix}$. Per ipotesi induttiva il primo fattore vale $\begin{pmatrix}F_n&F_{n-1}\\F_{n-1}&F_{n-2}\end{pmatrix}$. Il prodotto dà $\begin{pmatrix}F_n+F_{n-1}&F_n\\F_{n-1}+F_{n-2}&F_{n-1}\end{pmatrix} = \begin{pmatrix}F_{n+1}&F_n\\F_n&F_{n-1}\end{pmatrix}$. ✓

Sia $M = \begin{pmatrix}1&1\\1&0\end{pmatrix}$ e $I$ la matrice identità $2 \times 2$. Un primo algoritmo calcola $M^{n-1}$ moltiplicando iterativamente:

```text
fibonacci5(intero n) → intero
1.  M ← [[1,1],[1,0]]
2.  R ← [[1,0],[0,1]]       // matrice identità
3.  for i = 1 to n-1 do
4.      R ← R * M
5.  return R[0][0]           // R[0][0] = F_n
```

**Tempo**: $O(n)$ — $n-1$ moltiplicazioni di matrici $2\times 2$, ciascuna a costo costante.
**Spazio**: $O(1)$ — solo le due matrici $R$ e $M$ (dimensione fissa $2\times2$).

Questo non è ancora un miglioramento rispetto a fibonacci4 in termini di ordine di grandezza temporale. Il guadagno arriva con l'elevamento al quadrato veloce.
### Algoritmo 6 — Elevamento al quadrato veloce (potenza logaritmica)
**Idea chiave**: calcolare $A^n$ elevando al quadrato $A^{n/2}$.

$$A^n = \begin{cases}(A^{n/2})^2 & \text{se } n \text{ è pari} \\ A \cdot (A^{(n-1)/2})^2 & \text{se } n \text{ è dispari}\end{cases}$$

Esempio: $3^2=9$, $3^4=(9)^2=81$, $3^8=(81)^2=6561$ — solo 3 moltiplicazioni invece di 7.

```text
fibonacci6(intero n) → intero
1.  M ← [[1,1],[1,0]]
2.  R ← potenzaDiMatrice(M, n-1)
3.  return R[0][0]

potenzaDiMatrice(matrice A, intero k) → matrice
1.  if (k = 0) then return [[1,0],[0,1]]    // identità
2.  P ← potenzaDiMatrice(A, ⌊k/2⌋)
3.  P ← P * P
4.  if (k è dispari) then P ← P * A
5.  return P
```

**Analisi del tempo**: all'interno di `potenzaDiMatrice` si spende tempo costante (due prodotti di matrici $2\times2$, ciascuno $O(1)$) e si effettua una sola chiamata ricorsiva su input $\lfloor k/2 \rfloor$. L'equazione di ricorrenza è:

$$T(n) \leq T(n/2) + c \qquad (c \text{ costante})$$

Soluzione per iterazione (o [[03 - Equazioni di Ricorrenza]]):

$$T(n) \leq c + T(n/2) \leq 2c + T(n/4) \leq \ldots \leq ic + T(n/2^i)$$

Per $i = \lfloor \log_2 n \rfloor$ si ottiene $T(n) \leq c \log_2 n + T(1) = O(\log_2 n)$.

**Spazio**: l'albero delle chiamate ricorsive ha altezza $O(\log n)$; ogni livello usa memoria costante. Totale: $O(\log n)$.
> [!info] Guadagno rispetto a fibonacci3
> fibonacci6 è **esponenzialmente più veloce** di fibonacci3: dove fibonacci3 esegue $O(n)$ operazioni, fibonacci6 ne esegue $O(\log n)$. Per $n = 10^9$, fibonacci3 richiederebbe miliardi di operazioni; fibonacci6 ne basta circa 30.
## Riepilogo complessità
| Algoritmo | Corretto | Tecnica | Tempo | Spazio |
|---|---|---|---|---|
| fibonacci1 | No (per $n$ grandi) | Formula di Binet | $O(1)$* | $O(1)$* |
| fibonacci2 | Sì | Ricorsione (divide et impera) | $O(\phi^n)$ | $O(n)$ |
| fibonacci3 | Sì | Programmazione dinamica (array) | $O(n)$ | $O(n)$ |
| fibonacci4 | Sì | Iterativo (spazio $O(1)$) | $O(n)$ | $O(1)$ |
| fibonacci5 | Sì | Potenza di matrice iterativa | $O(n)$ | $O(1)$ |
| fibonacci6 | Sì | Elevamento al quadrato veloce | $O(\log n)$ | $O(\log n)$ |

*fibonacci1: il costo $O(1)$ è teorico; nella pratica il costo dipende dalla precisione richiesta e l'algoritmo non è corretto per $n$ arbitrariamente grandi.

Nella tabella del prof le righe riportate sono fibonacci2–fibonacci6 (fibonacci1 escluso per scorrettezza):

| Algoritmo | $T(n)$ | Spazio |
|---|---|---|
| fibonacci2 | $O(\phi^n)$ | $O(n)$ |
| fibonacci3 | $O(n)$ | $O(n)$ |
| fibonacci4 | $O(n)$ | $O(1)$ |
| fibonacci5 | $O(n)$ | $O(1)$ |
| fibonacci6 | $O(\log_2 n)$ | $O(\log_2 n)$ |

> [!example] Domanda tipica d'esame
> D: Perché fibonacci6 usa spazio $O(\log n)$ e non $O(1)$?
> R: fibonacci6 è ricorsivo: le chiamate attive simultaneamente formano un cammino radice-foglia nell'albero della ricorsione di `potenzaDiMatrice`, che ha altezza $O(\log n)$. Ogni chiamata occupa memoria costante (la matrice $P$ è $2\times2$), quindi lo spazio totale è $O(\log n)$. Al contrario, fibonacci4 e fibonacci5 sono iterativi e usano $O(1)$ variabili.
> [!info] Collegamento ad altri argomenti
> - La notazione $O(\cdot)$ e le sue varianti ($\Omega$, $\Theta$) sono trattate formalmente in [[02 - Notazioni Asintotiche]].
> - Le tecniche per risolvere equazioni di ricorrenza come $T(n) = T(n/2) + c$ sono in [[03 - Equazioni di Ricorrenza]].
> - La tecnica della programmazione dinamica (fibonacci3) sarà ripresa in contesti più complessi nel Modulo II.
> - Il costo del prodotto di matrici $2\times2$ è considerato $O(1)$ qui perché le dimensioni sono fisse; in generale il prodotto di matrici $k\times k$ ha costo $O(k^3)$.
