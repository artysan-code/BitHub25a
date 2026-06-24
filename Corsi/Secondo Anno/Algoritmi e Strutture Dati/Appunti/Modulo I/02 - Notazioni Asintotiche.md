# Notazioni Asintotiche
La complessità computazionale di un algoritmo è espressa da una funzione $T(n)$, dove $n$ è la dimensione dell'istanza e $T(n)$ rappresenta il numero di passi elementari eseguiti su una RAM nel caso peggiore. L'**analisi asintotica** descrive $T(n)$ in modo qualitativo: si perde un po' di precisione — ignorando costanti moltiplicative e termini di ordine inferiore — ma si guadagna in semplicità e generalità. Questa è una grande idea perché fornisce una misura indipendente dall'implementazione e dalla macchina reale su cui l'algoritmo viene eseguito.
## Modelli di calcolo
### La macchina di Turing
Il modello storico è la **macchina di Turing**: un nastro infinito e una testina di lettura/scrittura guidata da un insieme finito di stati. È troppo di basso livello — somiglia troppo poco ai calcolatori reali — e risulta utile per parlare di *calcolabilità* ma meno per parlare di *efficienza*.
### La RAM (Random Access Machine)
Il modello che usiamo è la **macchina a registri** (RAM, *random access machine*):
- un **programma finito** (non memorizzato nel nastro);
- un **nastro di ingresso** e uno **di uscita**;
- una **memoria** strutturata come un array, dove ogni cella può contenere un qualunque valore intero o reale;
- una **CPU** che esegue istruzioni elementari.

La RAM è un'astrazione dell'architettura di von Neumann ed è il modello di riferimento per tutto il corso.
### Passi elementari e criteri di costo
L'analisi della complessità si basa sul concetto di **passo elementare**. Sulla RAM i passi elementari sono:
- istruzione di ingresso/uscita (accesso ai nastri I/O);
- operazione aritmetico/logica;
- accesso o modifica del contenuto della memoria.

Esistono due criteri di costo:

| Criterio | Descrizione |
|---|---|
| **Uniforme** | Tutte le operazioni hanno costo 1; la complessità è il numero totale di passi elementari eseguiti. |
| **Logaritmico** | Il costo di un'operazione dipende dalla dimensione degli operandi: un'operazione su un operando di valore $x$ ha costo $\log x$. Modella meglio algoritmi "numerici". |

Il **criterio di costo generalmente usato è quello uniforme**.
## Analisi dei casi
Dato un algoritmo, istanze di eguale dimensione $n$ possono richiedere tempi diversi. Si distinguono tre analisi.
### Caso peggiore
> [!quote] Definizione — Caso peggiore
> Sia $\text{tempo}(I)$ il numero di passi elementari su una RAM sull'istanza $I$.
> $$T_{worst}(n) = \max_{\text{istanze } I \text{ di dimensione } n} \{ \text{tempo}(I) \}$$
> Rappresenta una **garanzia assoluta** sul tempo di esecuzione per ogni istanza di dimensione $n$.

È l'analisi più usata nel corso: fornisce una delimitazione superiore valida per qualunque input.
### Caso medio
> [!quote] Definizione — Caso medio
> Sia $P(I)$ la probabilità di occorrenza dell'istanza $I$.
> $$T_{avg}(n) = \sum_{\text{istanze } I \text{ di dimensione } n} P(I) \cdot \text{tempo}(I)$$

Il caso medio corrisponde al tempo su istanze "tipiche". Il problema pratico è che la distribuzione di probabilità sulle istanze è spesso ignota: occorre fare un'assunzione, che difficilmente è sempre realistica.
### Caso migliore
Il caso migliore è il minimo su tutte le istanze di dimensione $n$. Raramente è utile come garanzia, ma può comparire nelle analisi e negli esercizi.
## Notazione asintotica: intuizione
Consideriamo un caso reale: l'algoritmo `fibonacci3` (vedi [[01 - Il Problema di Fibonacci]]) ha complessità

$$T(n) = \begin{cases} 71n^2 + 100\lfloor n/4 \rfloor + 7 & \text{se } n \text{ è pari} \\ 70n^2 + 150\lfloor(n+1)/4\rfloor + 5 & \text{se } n \text{ è dispari} \end{cases}$$

Scriviamo semplicemente $T(n) = \Theta(n^2)$, che vuol dire: $T(n)$ è proporzionale a $n^2$. Ignoriamo le costanti moltiplicative e i termini di ordine inferiore perché, per istanze grandi, ciò che conta è come cresce il termine dominante.
## Le cinque notazioni asintotiche
### O-grande — delimitazione superiore (upper bound)
> [!quote] Definizione — O-grande
> $f(n) = O(g(n))$ se esistono due costanti $c > 0$ e $n_0 \ge 0$ tali che
> $$0 \le f(n) \le c \cdot g(n) \qquad \forall n \ge n_0$$
> In forma insiemistica: $O(g(n)) = \{ f(n) \mid \exists\, c > 0,\, n_0 \ge 0 : 0 \le f(n) \le c \cdot g(n),\, \forall n \ge n_0 \}$

![[notazioni.png]]

La scrittura $2n^2 + 4 = O(n^3)$ è un abuso di notazione per $2n^2 + 4 \in O(n^3)$.
> [!example] Esempi O-grande
> Sia $f(n) = 2n^2 + 3n$.
> - $f(n) = O(n^3)$ — con $c = 1$, $n_0 = 3$
> - $f(n) = O(n^2)$ — con $c = 3$, $n_0 = 3$
> - $f(n) \notin O(n)$ — nessuna coppia $(c, n_0)$ soddisfa la definizione

**Proprietà chiave tramite limiti:**
$$\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0 \implies f(n) = O(g(n))$$
$$f(n) = O(g(n)) \not\!\!\implies \lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$$
$$f(n) = O(g(n)) \iff \limsup_{n \to \infty} \frac{f(n)}{g(n)} < \infty$$
### Omega — delimitazione inferiore (lower bound)
> [!quote] Definizione — Omega
> $f(n) = \Omega(g(n))$ se esistono due costanti $c > 0$ e $n_0 \ge 0$ tali che
> $$f(n) \ge c \cdot g(n) \ge 0 \qquad \forall n \ge n_0$$
> In forma insiemistica: $\Omega(g(n)) = \{ f(n) \mid \exists\, c > 0,\, n_0 \ge 0 : 0 \le c \cdot g(n) \le f(n),\, \forall n \ge n_0 \}$

> [!example] Esempi Omega
> Sia $f(n) = 2n^2 - 3n$.
> - $f(n) = \Omega(n)$ — con $c = 1$, $n_0 = 2$
> - $f(n) = \Omega(n^2)$ — con $c = 1$, $n_0 = 3$
> - $f(n) \notin \Omega(n^3)$
### Theta — delimitazione stretta (tight bound)
> [!quote] Definizione — Theta
> $f(n) = \Theta(g(n))$ se esistono tre costanti $c_1, c_2 > 0$ e $n_0 \ge 0$ tali che
> $$c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n) \qquad \forall n \ge n_0$$
> In forma insiemistica: $\Theta(g(n)) = \{ f(n) \mid \exists\, c_1, c_2 > 0,\, n_0 \ge 0 : c_1 g(n) \le f(n) \le c_2 g(n),\, \forall n \ge n_0 \}$

> [!example] Esempi Theta
> Sia $f(n) = 2n^2 - 3n$.
> - $f(n) = \Theta(n^2)$ — con $c_1 = 1$, $c_2 = 2$, $n_0 = 3$
> - $f(n) \notin \Theta(n)$
> - $f(n) \notin \Theta(n^3)$

> [!quote] Proprietà — Equivalenza Theta–O–Omega
> $$f(n) = \Theta(g(n)) \iff f(n) = O(g(n)) \text{ e } f(n) = \Omega(g(n))$$
### o-piccolo — upper bound stretto
> [!quote] Definizione — o-piccolo
> $f(n) = o(g(n))$ se per **ogni** costante $c > 0$ esiste $n_0$ tale che
> $$0 \le f(n) < c \cdot g(n) \qquad \forall n \ge n_0$$
> Definizione alternativa equivalente:
> $$f(n) = o(g(n)) \iff \lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$$

Vale $o(g(n)) \subsetneq O(g(n))$: o-piccolo è più restrittivo di O-grande.
### omega-piccolo — lower bound stretto
> [!quote] Definizione — omega-piccolo
> $f(n) = \omega(g(n))$ se per **ogni** costante $c > 0$ esiste $n_0$ tale che
> $$0 \le c \cdot g(n) < f(n) \qquad \forall n \ge n_0$$
> Definizione alternativa equivalente:
> $$f(n) = \omega(g(n)) \iff \lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$$

Vale $\omega(g(n)) \subsetneq \Omega(g(n))$.
## Metodo operativo: i limiti
Il metodo principale per stabilire la relazione asintotica tra due funzioni è calcolare il **limite del rapporto**.

> [!quote] Proprietà — Metodo dei limiti
> Siano $f(n)$ e $g(n)$ funzioni positive. Se esiste $L = \lim_{n \to \infty} \dfrac{f(n)}{g(n)}$, allora:
> - $L = 0 \implies f(n) = o(g(n))$ (e quindi $f(n) = O(g(n))$)
> - $0 < L < \infty \implies f(n) = \Theta(g(n))$ (e quindi anche $O$ e $\Omega$)
> - $L = \infty \implies f(n) = \omega(g(n))$ (e quindi $f(n) = \Omega(g(n))$)

In particolare, il caso $L = c > 0$ finito segue dalla disuguaglianza $c/2 < f(n)/g(n) < 2c$ per $n$ sufficientemente grande, che fornisce direttamente le costanti per la definizione di $\Theta$.

> [!quote] Proprietà — Polinomi
> Se $P(n) = a_d n^d + a_{d-1} n^{d-1} + \cdots + a_0$ è un polinomio di grado $d$ con $a_d > 0$, allora $P(n) = \Theta(n^d)$.
>
> *Dimostrazione:* $P(n)/n^d = a_d + a_{d-1}n^{-1} + \cdots + a_0 n^{-d} \to a_d > 0$.
## Metodo alternativo: definizione diretta con $c$ e $n_0$
Quando il limite non è agevole da calcolare, si può lavorare direttamente con la definizione, trovando esplicitamente le costanti.

> [!example] Dimostrazione diretta — $2n^2 + 3n + 1 = O(n^2)$
> Per $n \ge 1$ si ha $3n \le 3n^2$ e $1 \le n^2$, quindi:
> $$2n^2 + 3n + 1 \le 2n^2 + 3n^2 + n^2 = 6n^2$$
> Abbiamo trovato $c = 6$ e $n_0 = 1$. Dunque $f(n) = O(n^2)$.

> [!example] Dimostrazione diretta — $5n^3 = \Theta(n^3)$
> **Upper bound:** $5n^3 \le 5 \cdot n^3$ con $c = 5$, $n_0 = 1$.
> **Lower bound:** $5n^3 \ge 5 \cdot n^3$ con $c = 5$, $n_0 = 1$.
> Quindi $5n^3 = \Theta(n^3)$.
## Tecniche di confutazione
Per confutare $f(n) = O(g(n))$ occorre mostrare che **per ogni** $c > 0$ esiste $n$ abbastanza grande tale che $f(n) > c \cdot g(n)$.

I tre metodi principali sono:
1. **Limiti:** se $\lim_{n\to\infty} f(n)/g(n) = \infty$ allora $f(n) \notin O(g(n))$.
2. **Per assurdo:** assumere la relazione vera e derivare una contraddizione.
3. **Sequenza esplicita:** esibire una successione di $n$ per cui la disuguaglianza fallisce per ogni $c$.

> [!example] Confutazione — $n^2 \ne O(n)$
> **Metodo 1 (limiti):** $\lim_{n\to\infty} n^2/n = \lim_{n\to\infty} n = \infty$, quindi $n^2 \notin O(n)$.
>
> **Metodo 2 (assurdo):** Supponiamo $n^2 = O(n)$: esistono $c > 0$ e $n_0$ tali che $n^2 \le cn$ per ogni $n \ge n_0$. Dividendo per $n > 0$ si ottiene $n \le c$ per ogni $n \ge n_0$, il che è assurdo poiché $n$ cresce senza limite.

> [!example] Confutazione — $2^n \ne O(n^k)$ per ogni $k$ costante
> $\lim_{n\to\infty} 2^n / n^k = \infty$ per qualunque $k$ fissato (applicando $k$ volte L'Hôpital). Quindi gli esponenziali non sono limitati superiormente da nessun polinomio.
## Riassunto e analogie
Le cinque notazioni si distinguono per il comportamento del rapporto $f(n)/g(n)$:

| Notazione | Condizione sul limite | Intuizione |
|---|---|---|
| $f(n) = \Theta(g(n))$ | $0 < L < \infty$ | $f$ e $g$ crescono allo stesso ritmo |
| $f(n) = O(g(n))$ | $L \le c_2 < \infty$ | $f$ cresce al più quanto $g$ |
| $f(n) = \Omega(g(n))$ | $L \ge c_1 > 0$ | $f$ cresce almeno quanto $g$ |
| $f(n) = o(g(n))$ | $L = 0$ | $f$ cresce strettamente meno di $g$ |
| $f(n) = \omega(g(n))$ | $L = \infty$ | $f$ cresce strettamente più di $g$ |

**Analogia con le disuguaglianze tra numeri reali:**

| Notazione | Analoga a |
|---|---|
| $\Theta$ | $=$ |
| $O$ | $\le$ |
| $\Omega$ | $\ge$ |
| $o$ | $<$ |
| $\omega$ | $>$ |
## Proprietà della notazione asintotica
> [!quote] Proprietà — Transitività
> Per ciascuna delle notazioni $\Theta, O, \Omega, o, \omega$:
> $$f(n) = X(g(n)) \text{ e } g(n) = X(h(n)) \implies f(n) = X(h(n))$$

> [!quote] Proprietà — Riflessività
> $$f(n) = \Theta(f(n)), \quad f(n) = O(f(n)), \quad f(n) = \Omega(f(n))$$

> [!quote] Proprietà — Simmetria
> $$f(n) = \Theta(g(n)) \iff g(n) = \Theta(f(n))$$

> [!quote] Proprietà — Simmetria trasposta
> $$f(n) = O(g(n)) \iff g(n) = \Omega(f(n))$$
> $$f(n) = o(g(n)) \iff g(n) = \omega(f(n))$$

> [!info] Convenzione sugli insiemi nelle formule
> Un insieme in una formula rappresenta un'anonima funzione dell'insieme.
> - $f(n) = n^3 + O(n^2)$ significa: esiste $h(n) \in O(n^2)$ tale che $f(n) = n^3 + h(n)$.
> - $n^2 + O(n) = O(n^2)$ significa: per ogni $f(n) \in O(n)$ esiste $h(n) \in O(n^2)$ tale che $n^2 + f(n) = h(n)$.
## Gerarchia degli ordini di infinito
Le principali famiglie di funzioni si ordinano per velocità di crescita (dal più lento al più veloce):
$$1 \prec \log \log n \prec \log n \prec n^\varepsilon \prec n \prec n \log n \prec n^c \prec c^n \prec n! \prec n^n$$
dove $0 < \varepsilon < 1 < c$ e $a \prec b$ significa $a = o(b)$.

I risultati dimostrabili tramite limite sulle singole famiglie sono:

**Polinomi:** $P(n) = a_d n^d + \cdots + a_0 \implies P(n) = \Theta(n^d)$ con $a_d > 0$.

**Esponenziali vs polinomi:** Per $a > 1$ e qualunque $d > 0$:
$$\lim_{n \to \infty} \frac{n^d}{a^n} = 0 \implies n^d = o(a^n)$$

**Logaritmi vs potenze:** Per $b > 1$ e qualunque $c, d > 0$:
$$\lim_{n \to \infty} \frac{(\log_b n)^c}{n^d} = 0 \implies (\log_b n)^c = o(n^d)$$

**Fattoriali:** $n! = \omega(a^n)$ per qualunque $a > 1$ (il fattoriale cresce più di ogni esponenziale), e $n! = o(n^n)$.
> [!warning] Errore comune: confondere $O$ con $\Theta$
> Scrivere $T(n) = O(n^2)$ per un algoritmo quadratico è corretto ma non è il bound più stretto. Quando si può provare la delimitazione inferiore, si preferisce sempre $T(n) = \Theta(n^2)$, che è più informativo. Dire solo $O$ non esclude che l'algoritmo sia in realtà lineare o logaritmico.
## Velocità delle funzioni composte: il termine dominante
### Somme
La velocità asintotica di $f(n) + g(n)$ è quella della **più veloce** tra $f$ e $g$:
$$f(n) + g(n) = \Theta(\max(f(n), g(n)))$$

Esempi: $n^3 + n = \Theta(n^3)$; $n + \log_{10} n = \Theta(n)$.
### Prodotti e quozienti
La velocità di $f(n) \cdot g(n)$ è la "somma" delle velocità di $f$ e $g$; quella di $f(n)/g(n)$ è la "differenza". Formalmente:
$$O(f) \cdot O(g) = O(f \cdot g)$$

> [!example] Termine dominante in espressioni composte
> $$\frac{n^3 \log n + n \log^3 n}{n^2 + 1} = \Theta\!\left(\frac{n^3 \log n}{n^2}\right) = \Theta(n \log n)$$
> Il numeratore è dominato da $n^3 \log n$; il denominatore da $n^2$.

> [!example] Domanda tipica d'esame
> **D:** Qual è la classe asintotica di $5n^3 + 2n^2 \log n + 100n$?
>
> **R:** Il termine dominante è $5n^3$ (polinomio di grado 3). Tutti gli altri termini crescono più lentamente ($n^2 \log n = o(n^3)$ e $n = o(n^3)$), quindi:
> $$5n^3 + 2n^2 \log n + 100n = \Theta(n^3)$$
> Regola pratica: in una somma di termini, ignora tutto tranne il termine che cresce più velocemente.
## Tabella di confronto rapido
| $f(n)$ vs $g(n)$ | Relazione | Giustificazione |
|---|---|---|
| $\log n$ vs $\sqrt{n}$ | $\log n = o(\sqrt{n})$ | Logaritmo cresce più lento di ogni potenza |
| $n$ vs $n \log n$ | $n = o(n \log n)$ | $\lim \frac{1}{\log n} = 0$ |
| $n \log n$ vs $n^2$ | $n \log n = o(n^2)$ | $\lim \frac{\log n}{n} = 0$ |
| $n^k$ vs $c^n$ ($c > 1$) | $n^k = o(c^n)$ | Esponenziali dominano i polinomi |
| $c^n$ vs $n!$ | $c^n = o(n!)$ | Il fattoriale cresce più velocemente |
| $\log(n!)$ vs $n \log n$ | $\log(n!) = \Theta(n \log n)$ | Formula di Stirling: $n! \approx (n/e)^n \sqrt{2\pi n}$ |
## Uso pratico nell'analisi di `fibonacci3`
L'algoritmo `fibonacci3` (definito in [[01 - Il Problema di Fibonacci]]) calcola $F_n$ con un ciclo da $3$ a $n$. Denotando con $c_j$ il costo (numero di passi elementari) della linea $j$:

**Upper bound:** le linee 1, 2, 5 sono eseguite una sola volta; le linee 3 e 4 al più $n$ volte:
$$T(n) \le c_1 + c_2 + c_5 + (c_3 + c_4) n = O(n)$$

**Lower bound:** la linea 4 è eseguita almeno $n - 3$ volte:
$$T(n) \ge c_4(n - 3) = \Omega(n)$$

Quindi $T(n) = \Theta(n)$.
> [!info] Perché è una grande idea
> La notazione asintotica è utile perché:
> - è **indipendente dall'implementazione** e dalla macchina reale;
> - i "dettagli" nascosti (costanti, termini di ordine inferiore) sono poco rilevanti quando $n$ è grande per funzioni asintoticamente diverse;
> - un'analisi dettagliata del numero esatto di passi sarebbe difficile, noiosa e non direbbe molto di più;
> - descrive bene in pratica la velocità degli algoritmi, come confermato dalle tabelle di pesate della prima lezione (Alg3 con $\Theta(\log n)$ pesate è incomparabilmente più veloce di Alg1 con $\Theta(n)$ per $n$ grande).
>
> Per le equazioni di ricorrenza che descrivono la complessità degli algoritmi divide-et-impera, vedi [[03 - Equazioni di Ricorrenza]].
