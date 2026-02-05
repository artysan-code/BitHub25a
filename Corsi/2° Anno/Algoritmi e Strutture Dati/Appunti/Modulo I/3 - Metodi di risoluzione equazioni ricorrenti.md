> [!abstract] Introduzione alle Equazioni di Ricorrenza
> 
> Le equazioni di ricorrenza sono strumenti matematici fondamentali per descrivere la complessità temporale $T(n)$ degli algoritmi ricorsivi.
> 
> **Obiettivo:** Trovare una forma chiusa (o asintotica) per $T(n)$, eliminando la dipendenza ricorsiva.

### Esempi Introduttivi
> [!example] Equazioni Tipiche
> 
> - **Fibonacci Ricorsivo:** $T(n) = T(n-1) + T(n-2) + \Theta(1)$  
>     
> - **Ricerca Binaria:** $T(n) = T(n/2) + \Theta(1)$  
>     
> - **Merge Sort:** $T(n) = 2T(n/2) + \Theta(n)$  
>     

### 1. Metodo dell'Iterazione (Srotolamento)
> [!tip] Concetto Chiave
> 
> Sviluppare la ricorrenza sostituendo iterativamente i termini ricorsivi fino a raggiungere il caso base, per poi sommare i costi. È utile per ricorrenze semplici.

#### Caso A: Divisione (Divide et Impera)
**Esempio: Ricerca Binaria**

Consideriamo $T(n) = T(n/2) + c$. Srotoliamo la ricorrenza:

1. $T(n) = T(n/2) + c$  
    
2. $T(n) = (T(n/4) + c) + c = T(n/4) + 2c$  
    
3. $T(n) = (T(n/8) + c) + 2c = T(n/8) + 3c$
    
    ...
    
    k. $T(n) = T(n/2^k) + k \cdot c$  
    

Ci fermiamo quando $n/2^k = 1$, ovvero $k = \log_2 n$.

  

$$T(n) = T(1) + c \log_2 n = \Theta(\log n)$$

#### Caso B: Sottrazione (Decrease and Conquer)
Qui la dimensione cala sottraendo una costante (es. $n-1$, $n-4$).

**Pattern 1: Costo Polinomiale (Caso "Integrale")**

Se $T(n) = T(n - k) + n^p$, il numero di passi è lineare ($n/k$).

Stiamo sommando potenze $p$-esime: $\sum i^p \approx n^{p+1}$.

> [!success] Regola Rapida
> 
> $T(n) = T(n - cost) + n^p \implies \Theta(n^{p+1})$
> 
> _Esempio (Compito 18/02/25):_ $T(n) = T(n-4) + n^2 \implies \Theta(n^3)$  

**Pattern 2: Moltiplicazione dei Sottoproblemi (Caso "Esponenziale")**

Se il coefficiente davanti alla $T$ è maggiore di 1, il numero di nodi esplode.

> [!danger] Regola Rapida (Pericolo!)
> 
> $T(n) = a \cdot T(n - c) + \Theta(1)$ con $a > 1 \implies \Theta(a^{n/c})$
> 
> _Esempio (Compito 26/06/25):_ $T(n) = 2T(n-2) + 1 \implies \Theta(2^{n/2}) = \Theta(\sqrt{2}^n)$  

### 2. Metodo dell'Albero di Ricorsione
> [!info] Procedura Generale
> 
> Questo metodo permette di visualizzare il costo dell'algoritmo come somma dei costi di ogni nodo nell'albero delle chiamate ricorsive.
> 
> **Passi da seguire:**
> 
> 1. **Disegnare l'albero:** La radice è il costo della chiamata corrente, i figli sono le chiamate ricorsive.
>     
> 2. **Analizzare i livelli:** Per ogni livello $i$ (da 0 a $h$), calcolare:
>     
>     - Numero di nodi: $N_i$  
>         
>     - Costo per singolo nodo: $C_i$  
>         
>     - Costo totale del livello: $L_i = N_i \cdot C_i$  
>         
> 3. **Calcolare l'altezza** $h$**:** Quando la dimensione del problema diventa 1?
>     
> 4. **Sommare tutto:** $T(n) = \sum_{i=0}^{h} L_i$  
>     

#### Esempio Dettagliato: Merge Sort
Equazione: $T(n) = 2T(n/2) + cn$  

**Analisi per livelli:**
- **Livello 0 (Radice):** Costo $cn$. Ci sono $1$ nodo.
    
- **Livello 1:** Abbiamo 2 nodi, ognuno lavora su $n/2$. Costo nodo: $c(n/2)$. Costo livello: $2 \cdot c(n/2) = cn$.
    
- **Livello 2:** Abbiamo 4 nodi, ognuno lavora su $n/4$. Costo nodo: $c(n/4)$. Costo livello: $4 \cdot c(n/4) = cn$.
    
    ...
    
- **Livello** $i$**:** Abbiamo $2^i$ nodi. Dimensione input $n/2^i$. Costo livello: $2^i \cdot c(n/2^i) = cn$.
    

**Altezza dell'albero:**

L'albero termina quando $n/2^i = 1 \implies i = \log_2 n$. Quindi l'altezza è $h = \log_2 n$.

**Totale:**

Sommiamo il costo $cn$ per ogni livello, da $0$ a $\log_2 n$.

  

$$T(n) = \sum_{i=0}^{\log_2 n} cn = cn \cdot (\log_2 n + 1) = \Theta(n \log n)$$

### 3. Metodo della Sostituzione

> [!warning] Verifica, non scoperta
> 
> Questo metodo non serve per _trovare_ la soluzione, ma per **dimostrare** che una soluzione intuita (guess) è corretta.

**Procedura:**

1. **Indovinare** la forma della soluzione (es. $T(n) = O(n \log n)$).
    
2. **Usare l'induzione matematica** per dimostrare che $T(n) \le d \cdot g(n)$ per costanti appropriate.
    

#### Esempio Pratico

Recurrence: $T(n) = 2T(n/2) + n$.

**Guess:** $T(n) = O(n \log n)$. Vogliamo mostrare $T(n) \le c n \log n$.

**Passo Induttivo:**

Assumiamo che valga per $n/2$, cioè $T(n/2) \le c (n/2) \log(n/2)$.

Sostituiamo nella ricorrenza originale:

  

$$T(n) \le 2 \left( c \frac{n}{2} \log \frac{n}{2} \right) + n$$$$T(n) \le cn (\log n - \log 2) + n$$$$T(n) \le cn \log n - cn + n$$

Affinché la dimostrazione regga, dobbiamo avere $T(n) \le c n \log n$.

Questo è vero se il "resto" $-cn + n \le 0$, ovvero $c \ge 1$.

$\square$  

### 4. Teorema Master

> [!definition] Forma Generale
> 
> Il Teorema Master fornisce una "ricetta" per risolvere ricorrenze della forma:
> 
>   
> 
> $$T(n) = a T(n/b) + f(n)$$
> 
> dove:
> 
> - $a \ge 1$: numero di sottoproblemi ricorsivi.
>     
> - $b > 1$: fattore di riduzione della dimensione dell'input.
>     
> - $f(n)$: costo per dividere il problema e combinare i risultati.
>     

L'idea è confrontare la funzione guida $f(n)$ con lo **Spartiacque** $n^{\log_b a}$ (che rappresenta il numero di foglie dell'albero).

#### I Tre Casi (Con Esempi d'Esame 2025)

|   |   |   |   |
|---|---|---|---|
|**Caso**|**Condizione (Chi vince?)**|**Soluzione T(n)**|**Esempio Pratico (Esami)**|
|**1**|**Vincono le foglie**<br><br>  <br><br>$n^{\log_b a} > f(n)$|$\Theta(n^{\log_b a})$|$T(n) = 2T(n/4) + 1$  <br><br>  <br><br>Spartiacque: $\sqrt{n}$ vs $1 \to \Theta(\sqrt{n})$|
|**2**|**Pareggio**<br><br>  <br><br>$f(n) = \Theta(n^{\log_b a})$|$\Theta(n^{\log_b a} \log n)$|$T(n) = 4T(n/4) + n$  <br><br>  <br><br>Spartiacque: $n$ vs $n \to \Theta(n \log n)$|
|**3**|**Vince la funzione**<br><br>  <br><br>$f(n) > n^{\log_b a}$|$\Theta(f(n))$|$T(n) = T(n/8) + n$  <br><br>  <br><br>Spartiacque: $1$ vs $n \to \Theta(n)$|

_(Nota per Caso 3: Richiede la condizione di regolarità_ $a f(n/b) \le c f(n)$ _per_ $c < 1$_)_

### 5. Metodo del Cambiamento di Variabile

> [!tip] Tecnica Avanzata
> 
> Utile quando la ricorrenza ha una struttura complessa (es. radici quadrate). L'idea è sostituire $n$ con una funzione $g(m)$ per ricondursi a una forma nota.

#### Caso Standard (Logaritmico)

**Equazione:** $T(n) = T(\sqrt{n}) + 1$ (Compito 18/07/25)

1. Poniamo $n = 2^m \implies m = \log n$.
    
2. Nota che $\sqrt{n} = n^{1/2} = (2^m)^{1/2} = 2^{m/2}$.
    
3. L'equazione diventa: $T(2^m) = T(2^{m/2}) + 1$.
    
4. Rinominiamo $S(m) = T(2^m)$.
    
5. Otteniamo $S(m) = S(m/2) + 1$.
    
6. Questa è la Ricerca Binaria su $m$: $S(m) = \Theta(\log m)$.
    
7. Torniamo a $n$: $T(n) = \Theta(\log (\log n))$.
    

#### Caso con Logaritmo

**Equazione:** $T(n) = 2T(\sqrt{n}) + \log n$  

1. Sostituzione come sopra ($S(m) = 2S(m/2) + m$).
    
2. Master Theorem caso 2 su $m$: $S(m) = \Theta(m \log m)$.
    
3. Torniamo a $n$: $T(n) = \Theta(\log n \log(\log n))$.
    

### Appendice: Cheat Sheet Analisi Asintotica (Esercizio 1A)

Regole rapide per risolvere i confronti "Vero/Falso" sui limiti. $\lim_{n \to \infty} f(n)/g(n)$.

> [!abstract] Trappole Comuni
> 
> 1. **Basi degli Esponenziali:** $2^{2n}$ NON è $\Theta(2^n)$.
>     
>     - $2^{2n} = (2^2)^n = 4^n$. Vince contro $2^n$ ($\omega$).
>         
>     - Invece $2^{n+k} = 2^k \cdot 2^n = \Theta(2^n)$ (costante moltiplicativa).
>         
> 2. **Logaritmi e Radici:**
>     
>     - Qualsiasi $\log^k n$ è $o(n^\epsilon)$ (il log perde sempre contro la radice).
>         
>     - $\log n$ NON è $\Theta(\sqrt{\log n})$. Ponendo $x=\log n$, $x$ batte $\sqrt{x}$.
>         
> 3. **Fattoriali:** $n!$ vince su qualsiasi $k^n$ (esponenziale). $n^n$ vince su $n!$.
>     

### Applicazioni ed Esempi Classici

#### La Torre di Hanoi

> [!example] Problema
> 
> Spostare $n$ dischi da un piolo A a un piolo C usando B come appoggio.
> 
> **Equazione:** $T(n) = 2T(n-1) + 1$
> 
> **Complessità:** $\Theta(2^n)$ (Caso Sottrazione con coefficiente > 1).

#### Il Problema della Celebrità

> [!example] Problema
> 
> Trovare una persona conosciuta da tutti ma che non conosce nessuno con domande "Conosci X?".
> 
> **Equazione:** $T(n) = T(n-1) + 1$
> 
> **Complessità:** $\Theta(n)$ (Caso Sottrazione con coefficiente = 1).