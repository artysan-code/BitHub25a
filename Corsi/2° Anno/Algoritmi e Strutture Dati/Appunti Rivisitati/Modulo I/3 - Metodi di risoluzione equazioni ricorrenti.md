> [!abstract] Introduzione alle Equazioni di Ricorrenza
> Le equazioni di ricorrenza sono strumenti matematici fondamentali per descrivere la complessità temporale $T(n)$ degli algoritmi ricorsivi.
>
> **Obiettivo:** Trovare una forma chiusa (o asintotica) per $T(n)$, eliminando la dipendenza ricorsiva.

### Esempi Introduttivi

> [!example] Equazioni Tipiche
> - **Fibonacci Ricorsivo:** $T(n) = T(n-1) + T(n-2) + \Theta(1)$
> - **Ricerca Binaria:** $T(n) = T(n/2) + \Theta(1)$
> - **Merge Sort:** $T(n) = 2T(n/2) + \Theta(n)$

### 1. Metodo dell'Iterazione (Srotolamento)

> [!tip] Concetto Chiave
> Sviluppare la ricorrenza sostituendo iterativamente i termini ricorsivi fino a raggiungere il caso base, per poi sommare i costi. È utile per ricorrenze semplici.

#### Esempio: Ricerca Binaria
Consideriamo $T(n) = T(n/2) + c$. Srotoliamo la ricorrenza:
1. $T(n) = T(n/2) + c$
2. $T(n) = (T(n/4) + c) + c = T(n/4) + 2c$
3. $T(n) = (T(n/8) + c) + 2c = T(n/8) + 3c$
...
k. $T(n) = T(n/2^k) + k \cdot c$

Ci fermiamo quando $n/2^k = 1$, ovvero $k = \log_2 n$.
$$T(n) = T(1) + c \log_2 n = \Theta(\log n)$$

### 2. Metodo dell'Albero di Ricorsione

> [!info] Procedura Generale
> Questo metodo permette di visualizzare il costo dell'algoritmo come somma dei costi di ogni nodo nell'albero delle chiamate ricorsive.
>
> **Passi da seguire:**
> 1.  **Disegnare l'albero:** La radice è il costo della chiamata corrente, i figli sono le chiamate ricorsive.
> 2.  **Analizzare i livelli:** Per ogni livello $i$ (da 0 a $h$), calcolare:
>     - Numero di nodi: $N_i$
>     - Costo per singolo nodo: $C_i$
>     - Costo totale del livello: $L_i = N_i \cdot C_i$
> 3.  **Calcolare l'altezza $h$:** Quando la dimensione del problema diventa 1?
> 4.  **Sommare tutto:** $T(n) = \sum_{i=0}^{h} L_i$

#### Esempio Dettagliato: Merge Sort
Equazione: $T(n) = 2T(n/2) + cn$

**Analisi per livelli:**
- **Livello 0 (Radice):** Costo $cn$. Ci sono $1$ nodo.
- **Livello 1:** Abbiamo 2 nodi, ognuno lavora su $n/2$. Costo nodo: $c(n/2)$. Costo livello: $2 \cdot c(n/2) = cn$.
- **Livello 2:** Abbiamo 4 nodi, ognuno lavora su $n/4$. Costo nodo: $c(n/4)$. Costo livello: $4 \cdot c(n/4) = cn$.
...
- **Livello $i$:** Abbiamo $2^i$ nodi. Dimensione input $n/2^i$. Costo livello: $2^i \cdot c(n/2^i) = cn$.

**Altezza dell'albero:**
L'albero termina quando $n/2^i = 1 \implies i = \log_2 n$. Quindi l'altezza è $h = \log_2 n$.

**Totale:**
Sommiamo il costo $cn$ per ogni livello, da $0$ a $\log_2 n$.
$$T(n) = \sum_{i=0}^{\log_2 n} cn = cn \cdot (\log_2 n + 1) = \Theta(n \log n)$$

### 3. Metodo della Sostituzione

> [!warning] Verifica, non scoperta
> Questo metodo non serve per *trovare* la soluzione, ma per **dimostrare** che una soluzione intuita (guess) è corretta.

**Procedura:**
1.  **Indovinare** la forma della soluzione (es. $T(n) = O(n \log n)$).
2.  **Usare l'induzione matematica** per dimostrare che $T(n) \le d \cdot g(n)$ per costanti appropriate.

#### Esempio Pratico
Recurrence: $T(n) = 2T(n/2) + n$.
**Guess:** $T(n) = O(n \log n)$. Vogliamo mostrare $T(n) \le c n \log n$.

**Passo Induttivo:**
Assumiamo che valga per $n/2$, cioè $T(n/2) \le c (n/2) \log(n/2)$.
Sostituiamo nella ricorrenza originale:
$$T(n) \le 2 \left( c \frac{n}{2} \log \frac{n}{2} \right) + n$$
$$T(n) \le cn (\log n - \log 2) + n$$
$$T(n) \le cn \log n - cn + n$$

Affinché la dimostrazione regga, dobbiamo avere $T(n) \le c n \log n$.
Questo è vero se il "resto" $-cn + n \le 0$, ovvero $c \ge 1$.
$\\square$

### 4. Teorema Master

> [!definition] Forma Generale
> Il Teorema Master fornisce una "ricetta" per risolvere ricorrenze della forma:
> $$T(n) = a T(n/b) + f(n)$$
> dove:
> - $a \ge 1$: numero di sottoproblemi ricorsivi.
> - $b > 1$: fattore di riduzione della dimensione dell'input.
> - $f(n)$: costo per dividere il problema e combinare i risultati.

L'idea è confrontare la funzione guida $f(n)$ con la funzione $n^{\log_b a}$ (che rappresenta il numero di foglie dell'albero, o il costo "nudo" della ricorsione).

#### I Tre Casi

| Caso | Condizione su $f(n)$ | Soluzione $T(n)$ | Intuizione |
| :--- | :--- | :--- | :--- |
| **1** | $f(n) = O(n^{\log_b a - \epsilon})$ <br> per $\epsilon > 0$ | **$\Theta(n^{\log_b a})$** | Il costo è dominato dalle foglie (troppe chiamate ricorsive). |
| **2** | $f(n) = \Theta(n^{\log_b a})$ | **$\Theta(n^{\log_b a} \log n)$** | Equilibrio tra costo ricorsivo e costo di combinazione. |
| **3** | $f(n) = \Omega(n^{\log_b a + \epsilon})$ <br> per $\epsilon > 0$ | **$\Theta(f(n))$** | Il costo è dominato dalla radice (costoso combinare/dividere). |
*(Nota per Caso 3: Richiede la condizione di regolarità $a f(n/b) \le c f(n)$ per $c < 1$)*

#### Esempi Applicativi

> [!success] Esempio Caso 1 (Foglie dominanti)
> $T(n) = 9T(n/3) + n$
> - $a=9, b=3 \implies \log_b a = \log_3 9 = 2$.
> - $f(n) = n$. Confrontiamo $n$ con $n^2$.
> - $f(n) = O(n^{2-\epsilon})$ con $\epsilon=1$.
> **Soluzione:** $T(n) = \Theta(n^2)$.

> [!success] Esempio Caso 2 (Equilibrio)
> $T(n) = T(2n/3) + 1$ (Ricerca Binaria su array sbilanciato)
> - $a=1, b=3/2 \implies \log_{3/2} 1 = 0$.
> - $f(n) = 1 = n^0$.
> - Siamo nel caso $f(n) = \Theta(n^{\log_b a})$.
> **Soluzione:** $T(n) = \Theta(\log n)$.

> [!success] Esempio Caso 3 (Radice dominante)
> $T(n) = 3T(n/4) + n \log n$
> - $a=3, b=4 \implies \log_4 3 \approx 0.79$.
> - $f(n) = n \log n$.
> - $f(n) = \Omega(n^{0.79 + \epsilon})$ è vero (es. $\epsilon \approx 0.2$).
> - Regolarità: $3(n/4 \log(n/4)) \le c(n \log n)$ vero per $c=3/4$.
> **Soluzione:** $T(n) = \Theta(n \log n)$.

---