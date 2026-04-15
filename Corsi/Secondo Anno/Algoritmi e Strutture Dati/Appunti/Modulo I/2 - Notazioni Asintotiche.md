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
> Indica che $f(n)$ cresce **al più** velocemente quanto $g(n)$ (attenzione, al più si intende asintoticamente equivalente e sotto $g(n)$).

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

### Come Lavorare con le Notazioni Asintotiche
#### Intuizione Visiva
Ponendo $f(n) = X(g(n))$ dove $X$ è una notazione asintotica, visualizziamo il comportamento di $f(n)$ rispetto a una funzione di riferimento $g(n)$:

![[notazioni.png]]

**Interpretazione delle notazioni:**
- **$O(g(n))$** → $f$ è delimitata superiormente da $g$ (upper bound)
- **$o(g(n))$** → $f$ cresce strettamente meno di $g$
- **$\Omega(g(n))$** → $f$ è delimitata inferiormente da $g$ (lower bound)
- **$\omega(g(n))$** → $f$ cresce strettamente più di $g$
- **$\Theta(g(n))$** → $f$ e $g$ sono asintoticamente equivalenti (tight bound)

> [!tip] Analogia con Disuguaglianze
> $$O\ \sim\ f(n)\leq g(n) \quad|\quad o \sim f(n) < g(n) \quad|\quad \Omega \sim f(n)\geq g(n) \quad|\quad \omega \sim f(n) > g(n) \quad|\quad \Theta \sim f(n)=g(n)$$

#### Metodi Risolutivi
##### Metodo 1: Limiti (APPROCCIO PRINCIPALE)
> [!success] Tecnica dei Limiti - Il Metodo Più Efficiente
> Per confrontare due funzioni $f(n)$ e $g(n)$, calcoliamo:
> $$L = \lim_{n \to \infty} \frac{f(n)}{g(n)}$$
>
> **Interpretazione:**
> - Se $L = 0$ → $f(n) = o(g(n))$ (f cresce **strettamente meno** di g)
> - Se $0 < L < \infty$ → $f(n) = \Theta(g(n))$ (f e g crescono **allo stesso modo**)
> - Se $L = \infty$ → $f(n) = \omega(g(n))$ (f cresce **strettamente più** di g)
>
> **Conseguenze:**
> - $f(n) = o(g(n)) \Rightarrow f(n) = O(g(n))$ ma $f(n) \neq \Theta(g(n))$
> - $f(n) = \Theta(g(n)) \Rightarrow f(n) = O(g(n))$ e $f(n) = \Omega(g(n))$
> - $f(n) = \omega(g(n)) \Rightarrow f(n) = \Omega(g(n))$ ma $f(n) \neq \Theta(g(n))$

##### Esempio 1: Dimostrare che $3n^2 + 5n = \Theta(n^2)$
**Soluzione con limiti:**
$$L = \lim_{n \to \infty} \frac{3n^2 + 5n}{n^2} = \lim_{n \to \infty} \left(3 + \frac{5}{n}\right) = 3$$

Poiché $L = 3 \in (0, \infty)$, allora $3n^2 + 5n = \Theta(n^2)$. ✓

##### Esempio 2: Dimostrare che $n \log n = o(n^2)$
**Soluzione con limiti:**
$$L = \lim_{n \to \infty} \frac{n \log n}{n^2} = \lim_{n \to \infty} \frac{\log n}{n} = 0$$

Poiché $L = 0$, allora $n \log n = o(n^2)$ e quindi anche $n \log n = O(n^2)$. ✓

##### Esempio 3: Confrontare $2^n$ e $n^{100}$
**Soluzione con limiti:**
$$L = \lim_{n \to \infty} \frac{n^{100}}{2^n} = 0$$

Quindi $n^{100} = o(2^n)$. Gli **esponenziali dominano sempre i polinomi**. ✓

##### Metodo 2: Definizione Diretta (APPROCCIO ALTERNATIVO)
> [!info] Metodo Diretto - Trovare c e n₀
> Per dimostrare $f(n) = O(g(n))$ dobbiamo **trovare esplicitamente** due costanti $c > 0$ e $n_0 \ge 0$ tali che:
> $$f(n) \le c \cdot g(n) \quad \forall n \ge n_0$$
>
> **Strategia:**
> 1. Maggiorare ogni termine di $f(n)$ con un multiplo di $g(n)$
> 2. Sommare i contributi per trovare $c$
> 3. Verificare per quali valori di $n$ la disuguaglianza è valida

##### Esempio 4: Dimostrare che $2n^2 + 3n + 1 = O(n^2)$
**Soluzione con definizione:**

Per $n \ge 1$, possiamo maggiorare:
- $3n \le 3n^2$ (poiché $n \le n^2$ per $n \ge 1$)
- $1 \le n^2$ (poiché $1 \le n^2$ per $n \ge 1$)

Quindi:
$$2n^2 + 3n + 1 \le 2n^2 + 3n^2 + n^2 = 6n^2$$

Abbiamo trovato $c = 6$ e $n_0 = 1$ tali che $f(n) \le 6 \cdot n^2$ per ogni $n \ge 1$. ✓

##### Esempio 5: Dimostrare che $5n^3 = \Omega(n^3)$
**Soluzione con definizione:**

Dobbiamo trovare $c > 0$ e $n_0$ tali che:
$$5n^3 \ge c \cdot n^3 \quad \forall n \ge n_0$$

Dividendo per $n^3$: $5 \ge c$

Possiamo scegliere $c = 5$ (o qualunque $c \le 5$) e $n_0 = 1$. ✓

Per dimostrare $\Theta$, dobbiamo mostrare sia $O$ che $\Omega$:
- $5n^3 = O(n^3)$ con $c = 5, n_0 = 1$
- $5n^3 = \Omega(n^3)$ con $c = 5, n_0 = 1$

Quindi $5n^3 = \Theta(n^3)$. ✓

### Tecniche di Confutazione
#### Come CONFUTARE una relazione asintotica
> [!warning] Per confutare $f(n) = O(g(n))$
> Dobbiamo dimostrare che **per ogni** $c > 0$ esiste un $n$ sufficientemente grande tale che:
> $$f(n) > c \cdot g(n)$$
>
> **Metodi:**
> 1. **Limiti:** Se $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$, allora $f(n) \neq O(g(n))$
> 2. **Per assurdo:** Assumere $f(n) = O(g(n))$ e derivare una contraddizione
> 3. **Controesempio:** Mostrare una sequenza di $n$ per cui la disuguaglianza fallisce per ogni $c$

##### Esempio 6: Confutare che $n^2 = O(n)$
**Metodo 1 - Limiti:**
$$L = \lim_{n \to \infty} \frac{n^2}{n} = \lim_{n \to \infty} n = \infty$$

Poiché $L = \infty$, allora $n^2 \neq O(n)$. ✓

**Metodo 2 - Per assurdo:**
Supponiamo per assurdo che $n^2 = O(n)$. Allora esistono $c > 0$ e $n_0$ tali che:
$$n^2 \le c \cdot n \quad \forall n \ge n_0$$

Dividendo per $n > 0$: $n \le c$ per ogni $n \ge n_0$.

Ma questo è **assurdo** perché $n$ può crescere arbitrariamente. ✗

Quindi $n^2 \neq O(n)$. ✓

##### Esempio 7: Confutare che $2^n = O(n^k)$ per ogni $k$ costante
**Soluzione con limiti:**
$$L = \lim_{n \to \infty} \frac{2^n}{n^k} \stackrel{H^k}{=} \lim_{n \to \infty} \frac{2^n \ln^k 2}{k!} = \infty$$

Gli esponenziali crescono più velocemente di **qualunque** polinomio. ✓

### Tabella di Confronto Rapido
| $f(n)$ vs $g(n)$         | Relazione                     | Giustificazione                                         |
| ------------------------ | ----------------------------- | ------------------------------------------------------- |
| $\log n$ vs $\sqrt{n}$   | $\log n = o(\sqrt{n})$        | Logaritmo cresce più lento di ogni potenza              |
| $n$ vs $n \log n$        | $n = o(n \log n)$             | $\lim \frac{n}{n \log n} = \lim \frac{1}{\log n} = 0$   |
| $n \log n$ vs $n^2$      | $n \log n = o(n^2)$           | $\lim \frac{n \log n}{n^2} = \lim \frac{\log n}{n} = 0$ |
| $n^k$ vs $c^n$           | $n^k = o(c^n)$ per $c > 1$    | Esponenziali dominano polinomi                          |
| $c^n$ vs $n!$            | $c^n = o(n!)$                 | Fattoriale cresce più velocemente                       |
| $2^n$ vs $2^{2n}$        | $2^n = o(2^{2n})$             | $2^{2n} = (2^n)^2$, quadratico in $2^n$                 |
| $\log(n!)$ vs $n \log n$ | $\log(n!) = \Theta(n \log n)$ | Formula di Stirling                                     |

> [!tip] Trucco per Esami Rapidi
> Quando vedi una somma di termini, il termine **dominante** determina la classe:
> $$5n^3 + 2n^2 \log n + 100n = \Theta(n^3)$$
> Ignora tutto tranne il termine che cresce più velocemente!
