> [!abstract] Introduzione all'Analisi Asintotica
> L'analisi asintotica ci permette di descrivere la complessità computazionale di un algoritmo, descritto da una funzione $T(n)$, in modo qualitativo, ignorando costanti moltiplicative e termini di ordine inferiore.
>
> **Obiettivo:** Valutare come cresce il tempo di esecuzione o lo spazio richiesto al tendere della dimensione dell'input $n$ all'infinito.

### Modelli di Calcolo
> [!info] Macchina di Turing
> Modello teorico storico, composto da un nastro infinito e una testina di lettura/scrittura. Poco pratico per l'analisi di algoritmi reali.

> [!definition] Modello RAM (Random Access Machine)
> Un modello più realistico simile ai moderni computer.
> - **Memoria:** Array di celle accessibili in tempo costante.
> - **Processore:** Esegue istruzioni elementari (aritmetica, logica, controllo, I/O).
> - **Costo:** Ogni istruzione elementare ha un costo unitario (criterio di costo uniforme).

### Analisi dei Casi
> [!warning] Caso Peggiore ($T_{worst}$)
> Il tempo massimo impiegato dall'algoritmo su una qualsiasi istanza di dimensione $n$. Fornisce una **garanzia** assoluta sulle prestazioni.
> $T_{worst}(n) = \max_{|I|=n} \{ \text{tempo}(I) \}$

> [!info] Caso Medio ($T_{avg}$)
> Il valore atteso del tempo di esecuzione, pesato sulla probabilità di occorrenza delle istanze. Spesso difficile da calcolare perché richiede di conoscere la distribuzione degli input.
> $T_{avg}(n) = \sum_{|I|=n} P(I) \cdot \text{tempo}(I)$

### Notazioni Asintotiche
#### O-Grande (O) - Upper Bound
> [!definition] Delimitazione Superiore
> $f(n) = O(g(n))$ se esistono due costanti $c > 0$ e $n_0 \ge 0$ tali che:
> $0 \le f(n) \le c \cdot g(n) \quad \forall n \ge n_0$
> Indica che $f(n)$ cresce **al più** velocemente quanto $g(n)$.

**Esempio:** $2n^2 + 3n = O(n^2)$
#### Omega ($\Omega$) - Lower Bound
> [!definition] Delimitazione Inferiore
> $f(n) = \Omega(g(n))$ se esistono due costanti $c > 0$ e $n_0 \ge 0$ tali che:
> $0 \le c \cdot g(n) \le f(n) \quad \forall n \ge n_0$
> Indica che $f(n)$ cresce **almeno** velocemente quanto $g(n)$.

**Esempio:** $n^2 \log n = \Omega(n^2)$
#### Theta ($\Theta$) - Tight Bound
> [!definition] Delimitazione Stretta
> $f(n) = \Theta(g(n))$ se $f(n) = O(g(n))$ e $f(n) = \Omega(g(n))$.
> Esistono costanti $c_1, c_2 > 0$ e $n_0 \ge 0$ tali che:
> $c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n) \quad \forall n \ge n_0$

**Esempio:** $3n^2 - n = \Theta(n^2)$
#### Notazioni "Piccolo" (o, $\omega$)
> [!info] o-piccolo e omega-piccolo
> - **o-piccolo:** $f(n) = o(g(n))$ se $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$. (Crescita strettamente minore).
> - **omega-piccolo:** $f(n) = \omega(g(n))$ se $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$. (Crescita strettamente maggiore).

### Proprietà delle Notazioni
> [!theorem] Proprietà di Transitività
> - Se $f(n) = \Theta(g(n))$ e $g(n) = \Theta(h(n))$, allora $f(n) = \Theta(h(n))$.
> - Vale anche per $O, \Omega, o, \omega$.

> [!theorem] Proprietà di Simmetria Trasposta
> $f(n) = O(g(n)) \iff g(n) = \Omega(f(n))$

> [!tip] Algebra delle Funzioni
> - **Somma:** $O(f(n) + g(n)) = O(\max(f(n), g(n)))$.
> - **Prodotto:** $O(f(n)) \cdot O(g(n)) = O(f(n) \cdot g(n))$.

### Gerarchia delle Funzioni
> [!tip] Ordini di Infinito
> Per confrontare rapidamente la velocità di crescita di due funzioni senza calcolare il limite, è utile conoscere la seguente gerarchia (dal più lento al più veloce):
> $$1 \prec \log \log n \prec \log n \prec n^\epsilon \prec n \prec n \log n \prec n^c \prec c^n \prec n! \prec n^n$$
> Dove:
> - $a \prec b$ significa $a = o(b)$
> - $0 < \epsilon < 1 < c$
> 
> **Regola pratica:** Un esponenziale ($c^n$) domina sempre un polinomio ($n^c$), che a sua volta domina sempre un polilogaritmo ($\log^k n$).

