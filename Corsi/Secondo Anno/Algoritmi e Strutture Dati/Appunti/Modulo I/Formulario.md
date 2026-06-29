---
tags:
  - algoritmi
  - ricorrenze
---
# Formulario — Modulo I (Esercizio 1)
**Formulario teorico** del Modulo I (corso del prof. Gualà): tutto ciò che serve "a colpo d'occhio" per l'**Esercizio 1** dello scritto — notazioni asintotiche (1.A), equazioni di ricorrenza (1.B), sommatorie e identità, e la tabella decisionale problema → algoritmo → costo (1.C). Gli **pseudocodici** degli algoritmi e le loro interfacce stanno in [[Pseudocodici e Interfacce]]; per le complessità a confronto vedi il [[#Riepilogo complessità]] in fondo.
## Come è organizzato
1. **Notazioni asintotiche** (Es 1.A) — definizioni, metodo dei limiti, gerarchia di crescita, identità.
2. **Equazioni di ricorrenza** (Es 1.B) — Teorema Master, sottrattive, tipo Fibonacci, cambio di variabile.
3. **Sommatorie e identità utili** — formule di rapida consultazione per l'analisi di complessità.
4. **Esercizio 1.C** — problema → algoritmo → costo (tabelle decisionali; pseudocodici in [[Pseudocodici e Interfacce]]).
5. **Riferimento rapido** — [[#Riepilogo complessità]] e [[#Trappole ricorrenti]].
## Notazioni asintotiche
Cheat-sheet per l'**Esercizio 1.A**: verificare vero/falso di relazioni asintotiche con il **metodo dei limiti**. Per la teoria completa, dimostrazioni ed esempi → [[02 - Notazioni Asintotiche]].
### Definizioni formali
> [!quote] Definizione — $O$ (upper bound)
> $f(n) = O(g(n))$ se $\exists\, c > 0,\, n_0 \ge 0$ tali che
> $$0 \le f(n) \le c \cdot g(n) \qquad \forall n \ge n_0$$

> [!quote] Definizione — $\Omega$ (lower bound)
> $f(n) = \Omega(g(n))$ se $\exists\, c > 0,\, n_0 \ge 0$ tali che
> $$0 \le c \cdot g(n) \le f(n) \qquad \forall n \ge n_0$$

> [!quote] Definizione — $\Theta$ (tight bound)
> $f(n) = \Theta(g(n))$ se $\exists\, c_1, c_2 > 0,\, n_0 \ge 0$ tali che
> $$c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n) \qquad \forall n \ge n_0$$
> Equivalente: $f = \Theta(g) \iff f = O(g)$ **e** $f = \Omega(g)$.

> [!quote] Definizione — $o$ (upper bound stretto)
> $f(n) = o(g(n))$ se per **ogni** $c > 0$ esiste $n_0$ t.c. $0 \le f(n) < c \cdot g(n)$ per ogni $n \ge n_0$.
> $$f = o(g) \iff \lim_{n\to\infty} \frac{f(n)}{g(n)} = 0$$
> Vale $o(g) \subsetneq O(g)$: $o$ è più restrittivo di $O$.

> [!quote] Definizione — $\omega$ (lower bound stretto)
> $f(n) = \omega(g(n))$ se per **ogni** $c > 0$ esiste $n_0$ t.c. $0 \le c \cdot g(n) < f(n)$ per ogni $n \ge n_0$.
> $$f = \omega(g) \iff \lim_{n\to\infty} \frac{f(n)}{g(n)} = \infty$$
> Vale $\omega(g) \subsetneq \Omega(g)$. Simmetria trasposta: $f = o(g) \iff g = \omega(f)$.
### Metodo dei limiti
Dato $L = \lim_{n\to\infty} f(n)/g(n)$ (quando esiste):

| $L$ | Relazione più stretta | Analogia | Implica anche |
|---|---|---|---|
| $L = 0$ | $f = o(g)$ | $f < g$ | $f = O(g)$ |
| $0 < L < \infty$ | $f = \Theta(g)$ | $f = g$ | $f = O(g)$ e $f = \Omega(g)$ |
| $L = \infty$ | $f = \omega(g)$ | $f > g$ | $f = \Omega(g)$ |

> [!warning] Trappola — limite finito non nullo
> Se $L = c$ con $0 < c < \infty$: la relazione è **soltanto** $\Theta$. Scrivere $f = o(g)$ (che richiede $L = 0$) o $f = \omega(g)$ (che richiede $L = \infty$) è sbagliato. Esempio: $2^{n+2}/2^n = 4$ (costante) $\Rightarrow \Theta$, **non** $\omega$.
### Gerarchia di crescita
Dal più lento al più veloce ($a \prec b$ sse $a = o(b)$; $0 < \varepsilon < 1 < c$):
$$1 \;\prec\; \log\log n \;\prec\; \log n \;\prec\; n^\varepsilon \;\prec\; n \;\prec\; n\log n \;\prec\; n^c \;\prec\; n^{\log n} \;\prec\; c^n \;\prec\; (\log n)^n \;\prec\; n! \;\prec\; n^n$$
In particolare: $\sqrt{n} = n^{1/2}$ è un caso di $n^\varepsilon$ ($\varepsilon = \tfrac{1}{2}$); $n^2$ è un caso di $n^c$ ($c = 2$).

> [!info] I due livelli intermedi facili da dimenticare
> - $n^{\log n} = 2^{(\log n)^2}$: **super-polinomiale** (l'esponente $\log n$ supera ogni costante $c$) ma **sub-esponenziale** (più lento di ogni $c^n$).
> - $(\log n)^n = 2^{n\log\log n}$: **sopra ogni esponenziale** $c^n$ (poiché $n\log\log n \gg n\log c$), ma sotto $n!$.
### Identità e regole utili
> [!info] Proprietà dei logaritmi
> - **Cambio di base:** $\log_a n = \frac{\ln n}{\ln a}$ — per $a > 1$ fissa: $\log_a n = \Theta(\log n)$.
> - **Log di potenza:** $\log(n^k) = k\log n$; $\;\log\sqrt{n} = \tfrac{1}{2}\log n$; $\;\log(a^b) = b\log a$.
> - **Log di prodotto:** $\log(ab) = \log a + \log b$.
> - **Base variabile:** $\log_n n = 1$; se $f(n)\to\infty$: $\log_{f(n)} c = \tfrac{\ln c}{\ln f(n)} \to 0$ — **non** è $\Theta(1)$.

> [!info] Identità esponenziale fondamentale
> $$a^{\log_b n} = n^{\log_b a}$$
> Esempi: $2^{\log_2 n} = n$; $\;4^{\log_2 n} = n^{\log_2 4} = n^2$; $\;3^{\log_2 n} = n^{\log_2 3} \approx n^{1.585}$.
> La base del logaritmo **deve coincidere** con la base dell'esponenziale; altrimenti convertire prima con il cambio di base.

> [!info] Esponenziali — costante additiva vs moltiplicativa
> - **Additiva:** $2^{n+c} = 2^c \cdot 2^n = \Theta(2^n)$ — solo un fattore moltiplicativo costante.
> - **Moltiplicativa:** $2^{cn} = (2^c)^n$; se $c \ne 1$ cambia la base: $2^{2n} = 4^n = \omega(2^n)$.
> - **Addendo non costante:** $2^{n+f(n)} = 2^n \cdot 2^{f(n)}$; se $f(n)\to\infty$ il rapporto con $2^n$ diverge. Es.: $2^{n+\log n} = n \cdot 2^n = \omega(2^n)$.
> - **Basi diverse:** per $1 < a < b$: $a^n/b^n = (a/b)^n \to 0$, quindi $a^n = o(b^n)$, mai $\Theta$.

> [!info] Funzioni sub-polinomiali e formula di Stirling
> Per confrontare $2^{f(n)}$ con $n^k$: confronta i **logaritmi** ($f(n)$ vs $k\log n$).
> - $2^{\sqrt{\log n}}$: $\sqrt{\log n} = o(\log n)$, quindi $2^{\sqrt{\log n}} = o(n^\varepsilon)$ per ogni $\varepsilon > 0$.
> - $2^{\log^2 n} = n^{\log n}$: super-polinomiale ($\log^2 n \gg k\log n$), quindi $\omega(n^k)$ per ogni costante $k$.
> **Stirling:** $n! \approx \sqrt{2\pi n}\,(n/e)^n$. Senza memorizzare la costante: $\log(n!) = \Theta(n\log n)$; $\;n! = \omega(a^n)$ per ogni $a > 1$; $\;n! = o(n^n)$.
### Casistiche 1.A — mossa risolutiva
| Casistica | Pr. | Mossa risolutiva |
|---|---|---|
| Polinomi puri $n^a$ vs $n^b$ | 🔴 | Rapporto $n^{a-b}$: $a>b\Rightarrow\omega$; $a<b\Rightarrow o$; $a=b\Rightarrow\Theta$. Radici → esponenti frazionari ($\sqrt{n}=n^{1/2}$). |
| $n^a\log^k n$ vs $n^b$ | 🔴 | $a\ne b$: domina l'esponente di $n$ (log irrilevante). $a=b, k>0$: $\omega$; $k=0$: $\Theta$. |
| $\log^k n$ vs $n^\varepsilon$ ($\varepsilon>0$) | 🔴 | Sempre $o$: ogni potenza di $n$ domina qualsiasi potenza del logaritmo. |
| Proprietà dei logaritmi | 🟡 | Cambio di base $\Rightarrow\Theta$; $\log n^k = k\log n$; base variabile $\log_{f(n)}c\to 0 \not\Leftrightarrow \Theta(1)$. |
| $\log\log n$, $\sqrt{\log n}$, $\log n$ | 🔴 | Sostituzione $t=\log n\to\infty$; poi limiti standard $\log t\,/\,t^\alpha \to 0$. |
| $\log^a n$ vs $\log^b n$ | 🟡 | Sostituzione $u=\log n$; confronta $u^a$ vs $u^b$ come polinomi. |
| Frazioni razionali con radici | 🔴 | Termine dominante num / termine dominante denom $= n^{a-b}$. |
| $a^{\log_b n}$ vs altra funzione | 🟡 | Identità $a^{\log_b n}=n^{\log_b a}$; poi confronto normale. |
| $2^{\sqrt{\log n}}$, $2^{\log^2 n}$ | 🟡 | Confronta i log: $f(n)$ vs $k\log n$. $2^{\log^2 n}=n^{\log n}$: super-polinomiale. |
| $a^n$ vs $b^n$ ($a\ne b>1$) | 🔴 | $(a/b)^n\to 0$ o $\infty$: mai $\Theta$ con basi diverse. |
| $a^n$ vs $n^k$ | 🟡 | $n^k = o(a^n)$ per ogni $k$ fissato e $a>1$; vale anche $2^{n/2}=(\sqrt{2})^n \gg n^k$. |
| $2^{n+c}$ ($c$ costante) | 🔴 | $2^c\cdot 2^n=\Theta(2^n)$: fattore moltiplicativo costante. |
| $2^{cn}$ vs $2^{dn}$ ($c\ne d$) | 🔴 | $2^{(c-d)n}\to 0$ o $\infty$; mai $\Theta$. Nota: $2^{2n}=4^n$. |
| Somma esponenziali $a^n+b^n$ | 🔴 | Domina il termine più grande: $a^n+b^n=\Theta(a^n)$ se $a>b>1$. |
| $2^{n+f(n)}$, $f(n)$ non costante | 🟡 | $=2^n\cdot 2^{f(n)}$; se $f(n)\to\infty$: $\omega(2^n)$. Es.: $f=\log n\Rightarrow n\cdot 2^n$. |
| $o$/$\omega$ vs $\Theta$ | 🔴 | $\lim f/g=c\in(0,\infty)\Rightarrow$ solo $\Theta$; $o$ richiede $L=0$, $\omega$ richiede $L=\infty$. |
| $n!$ vs $a^n$ | ⚪ | Stirling: $n!=\omega(a^n)$ per ogni $a>1$ fissa. |
| $n^n$, $n^{\sqrt{n}}$, super-esp. | ⚪ | Confronta log: $\log(n^{f(n)})=f(n)\log n$; domina chi ha esponente $f(n)$ maggiore. |

> [!warning] Trappola — identità $a^{\log_b n}=n^{\log_b a}$
> La base del logaritmo deve coincidere con quella dell'esponenziale: $4^{\log_2 n}=n^{\log_2 4}=n^2$, **non** $n^4$. Se le basi non coincidono, convertire prima con il cambio di base.
## Equazioni di ricorrenza
Cheat-sheet per l'**Esercizio 1.B**. Dimostrazioni complete e metodi per esteso in [[03 - Equazioni di Ricorrenza]]; esempi da esame in [[1.B — Equazioni di ricorrenza]].
### Teorema Master
> [!quote] Teorema — Master ($T(n) = aT(n/b) + f(n)$)
> Con $a \ge 1$, $b > 1$ costanti e $f(n)$ asintoticamente positiva, lo **spartiacque** è $n^{\log_b a}$ (numero di foglie dell'albero di ricorsione). Si confronta $f(n)$ con $n^{\log_b a}$:
>
> **Caso 1 — foglie dominano:** $f(n) = O(n^{\log_b a - \varepsilon})$ per qualche $\varepsilon > 0$ $\implies T(n) = \Theta(n^{\log_b a})$
>
> **Caso 2 — pareggio:** $f(n) = \Theta(n^{\log_b a})$ $\implies T(n) = \Theta(n^{\log_b a} \log n)$
>
> **Caso 3 — radice domina:** $f(n) = \Omega(n^{\log_b a + \varepsilon})$ per qualche $\varepsilon > 0$ **e** **condizione di regolarità** $a\,f(n/b) \le c\,f(n)$ con $c < 1$ per $n$ grande $\implies T(n) = \Theta(f(n))$

| Caso | Condizione su $f(n)$ vs $n^{\log_b a}$ | Risultato |
|---|---|---|
| 1 — foglie | $f(n) = O(n^{\log_b a - \varepsilon})$, $\varepsilon > 0$ | $\Theta(n^{\log_b a})$ |
| 2 — pareggio | $f(n) = \Theta(n^{\log_b a})$ | $\Theta(n^{\log_b a} \log n)$ |
| 3 — radice | $f(n) = \Omega(n^{\log_b a + \varepsilon})$ + regolarità $a\,f(n/b) \le c\,f(n)$ | $\Theta(f(n))$ |

> [!warning] Il Master NON si applica se
> - **Argomento sottrattivo:** $T(n-k)$ invece di $T(n/b)$ — usare iterazione/srotolamento.
> - **$a$ o $b$ dipendono da $n$:** es. $T(n) = n\,T(n/2) + n$.
> - **Gap tra i casi:** es. $T(n) = 2T(n/2) + n/\log n$ (né Caso 1 né Caso 2) — usare albero di ricorsione.
> - **Caso 2 esteso:** $T(n) = 2T(n/2) + n\log n \implies \Theta(n\log^2 n)$ ma non è coperto dalla forma base del teorema.
### Ricorrenze sottrattive $T(n) = aT(n-c) + f(n)$
> [!info] Regola — $a = 1$, costo polinomiale
> $$T(n) = T(n-c) + \Theta(n^p) \implies T(n) = \Theta(n^{p+1})$$
> Srotolando si accumula $\sum_{j=1}^{n} j^p = \Theta(n^{p+1})$; la costante $c$ non cambia l'ordine asintotico.
> **Es.:** $T(n) = T(n-1) + n^2 \implies \Theta(n^3)$; $T(n) = T(n-4) + n^2 \implies \Theta(n^3)$.

> [!info] Regola — $a \ge 2$, crescita esponenziale
> $$T(n) = a\,T(n-c) + \Theta(n^p),\quad a > 1 \implies T(n) = \Theta(a^{n/c})$$
> Il numero di chiamate si moltiplica a ogni passo; la progressione geometrica $\sum_{i=0}^{n/c} a^i = \Theta(a^{n/c})$ domina qualunque fattore polinomiale in $f(n)$.
> **Es.:** $T(n) = 2T(n-2) + 1 \implies \Theta(2^{n/2}) = \Theta(\sqrt{2}^n)$; $T(n) = 2T(n-1) + n \implies \Theta(2^n)$.

> [!warning] Distinzione critica: $a = 1$ vs $a \ge 2$
> $T(n) = T(n-1) + n \implies \Theta(n^2)$ (polinomiale, $a=1$), ma $T(n) = 2T(n-1) + n \implies \Theta(2^n)$ (esponenziale, $a=2$). La distinzione è il **coefficiente** davanti a $T$: non confonderli.
### Ricorrenza tipo Fibonacci
> [!info] Due rami: $T(n) = T(n-1) + T(n-2) + O(1)$
> $$T(n) = T(n-1) + T(n-2) + O(1) \implies T(n) = \Theta(\phi^n)$$
> dove $\phi = \dfrac{1+\sqrt{5}}{2} \approx 1.618$ è il **rapporto aureo**. L'albero delle chiamate ha $\Theta(\phi^n)$ nodi: $\phi$ è la radice dominante di $x^2 - x - 1 = 0$ (equazione caratteristica); il termine $|\hat{\phi}| < 1$ è trascurabile. → [[01 - Il Problema di Fibonacci]]

> [!warning] Trappola
> Non usare Master Theorem né srotolamento lineare su questa ricorrenza: le due chiamate con argomenti distinti richiedono l'**equazione caratteristica** o il conteggio diretto dei nodi dell'albero di ricorsione.
### Cambio di variabile
> [!info] Schema — argomento $n^{1/k}$ (es. $\sqrt{n}$)
> Per $T(n) = \alpha\,T(n^{1/k}) + f(n)$:
> 1. Poni $n = 2^m$ (cioè $m = \log_2 n$) e $R(m) = T(2^m)$.
> 2. Osserva che $n^{1/k} = 2^{m/k}$: la ricorrenza diventa $R(m) = \alpha\,R(m/k) + f(2^m)$.
> 3. Risolvi $R(m)$ con i metodi standard (spesso Master).
> 4. Ritraduci: $T(n) = R(\log_2 n)$.

**$T(n) = T(\sqrt{n}) + O(1)$** — $R(m) = R(m/2) + O(1)$, Master Caso 2 ($a=1,b=2$, spartiacque $=1$): $R(m) = \Theta(\log m)$ → $T(n) = \Theta(\log \log n)$.

**$T(n) = 2T(\sqrt{n}) + \log n$** — $R(m) = 2R(m/2) + m$, Master Caso 2 ($a=2,b=2$, spartiacque $=m$): $R(m) = \Theta(m \log m)$ → $T(n) = \Theta(\log n \cdot \log \log n)$.

> [!warning] Non dimenticare la ritraduzione
> Risposta con $\Theta(\log m)$ senza sostituire $m = \log_2 n$ è **errata**: $m$ è variabile ausiliaria priva di significato nel problema originale.
### Metodi risolutivi
| Metodo | Quando usarlo | Come |
|---|---|---|
| **Iterazione / srotolamento** | sottrattive; qualsiasi ricorrenza lineare | sostituisci iterativamente fino al caso base; somma la serie risultante |
| **Albero di ricorsione** | $aT(n/b)+f(n)$; alberi non bilanciati | costo totale = costo/livello × numero di livelli; conferma per sostituzione |
| **Sostituzione** | verifica un'ipotesi già indovinata | ipotizza $T(n) \le c\,g(n)$; dimostra per induzione; se il residuo è positivo, aggiungi un termine sottrattivo nell'ipotesi |
| **Teorema Master** | $aT(n/b)+f(n)$ in forma canonica | calcola $n^{\log_b a}$; confronta con $f(n)$; individua il caso |
| **Cambio di variabile** | argomento $n^{1/k}$ o $\sqrt{n}$ | poni $n=2^m$, riduci a forma nota, ritraduci con $m=\log_2 n$ |
### Ricorrenze notevoli
| Ricorrenza | Metodo | Complessità | Algoritmo |
|---|---|---|---|
| $T(n) = T(n/2) + O(1)$ | Master Caso 2 | $\Theta(\log n)$ | Ricerca binaria |
| $T(n) = 2T(n/2) + \Theta(n)$ | Master Caso 2 | $\Theta(n \log n)$ | MergeSort |
| $T(n) = 2T(n/2) + \Theta(1)$ | Master Caso 1 | $\Theta(n)$ | — |
| $T(n) = T(n-1) + \Theta(n)$ | Iterazione ($a=1$, $p=1$) | $\Theta(n^2)$ | SelectionSort, InsertionSort |
| $T(n) = 2T(n-1) + O(1)$ | Iterazione ($a=2$, $c=1$) | $\Theta(2^n)$ | Torre di Hanoi |
| $T(n) = T(n-1)+T(n-2)+O(1)$ | Equazione caratteristica | $\Theta(\phi^n)$ | Fibonacci ricorsivo (fibonacci2) |
| $T(n) = T(\sqrt{n}) + O(1)$ | Cambio di variabile | $\Theta(\log \log n)$ | — |
## Sommatorie e identità utili
Formule matematiche di rapida consultazione per l'analisi di complessità e la risoluzione di [[03 - Equazioni di Ricorrenza|ricorrenze]].
### Sommatorie notevoli
> [!info] Sommatorie notevoli
> | Sommatoria | Forma chiusa | $\Theta$ | Dove serve |
> |---|---|---|---|
> | $\sum_{i=1}^{n} i$ | $\frac{n(n+1)}{2}$ | $\Theta(n^2)$ | $T(n)=T(n-1)+n \Rightarrow \Theta(n^2)$ |
> | $\sum_{i=1}^{n} i^2$ | $\frac{n(n+1)(2n+1)}{6}$ | $\Theta(n^3)$ | $T(n)=T(n-1)+n^2 \Rightarrow \Theta(n^3)$ ([[03 - Equazioni di Ricorrenza#Esercizi svolti dagli esami|Es. 7]]) |
> | $\sum_{i=1}^{n} i^p$ | — | $\Theta(n^{p+1})$ | [[03 - Equazioni di Ricorrenza#1.2 Caso sottrazione — pattern e regole rapide|regola rapida §1.2]] |
> | $H_n = \sum_{i=1}^{n} \frac{1}{i}$ | — | $\Theta(\log n)$ | serie armonica; analisi media QuickSort |
> | $\sum_{i=0}^{n} i\,2^i$ | — | $\Theta(n\,2^n)$ | strutture con peso esponenziale per indice |

> [!info] Serie geometrica finita
> $$\sum_{i=0}^{n} x^i = \frac{x^{n+1}-1}{x-1} \qquad (x \neq 1)$$
> - **$x < 1$**: la serie tende a $\frac{1}{1-x}$ per $n \to \infty$ → $\Theta(1)$.
> - **$x > 1$**: l'ultimo termine $x^n$ domina tutti gli altri → $\Theta(x^n)$.
> - Caso tipico: $\sum_{j=0}^{k-1} 2^j = 2^k - 1$ (Torre di Hanoi, [[03 - Equazioni di Ricorrenza#1.2 Caso sottrazione — pattern e regole rapide|§1.2]]).
### Potenze di 2 e logaritmi
> [!info] Identità su esponenziali e logaritmi
> **Potenze di 2:**
> $$2^{\log_2 n} = n, \qquad \log_2(2^n) = n$$
> **Generalizzazione** ([[02 - Notazioni Asintotiche#Gerarchia degli ordini di infinito|§ gerarchia]]):
> $$a^{\log_b n} = n^{\log_b a}$$
> Es. $4^{\log_2 n} = n^2$; $3^{\log_2 n} = n^{\log_2 3} \approx n^{1{,}585}$; $2^{\log_2 n} = n$.
>
> **Regole dei logaritmi:**
> $$\log_b(xy) = \log_b x + \log_b y, \qquad \log_b(x^k) = k\log_b x, \qquad \log_b\!\tfrac{x}{y} = \log_b x - \log_b y$$
>
> **Cambio di base:**
> $$\log_b n = \frac{\log_a n}{\log_a b}$$
> Conseguenza pratica: $\log_b n = \Theta(\log n)$ per qualsiasi base $b > 1$ fissa — nei $\Theta$ la base è irrilevante. Usato nel [[03 - Equazioni di Ricorrenza#5. Cambiamento di variabile|cambiamento di variabile]] e negli spartiacque del [[03 - Equazioni di Ricorrenza#4. Teorema Master|Teorema Master]].
### Rapporto aureo e formula di Binet
> [!info] Rapporto aureo $\phi$ e numeri di Fibonacci
> Il **rapporto aureo** è $\phi = \frac{1+\sqrt{5}}{2} \approx 1{,}618$, radice positiva di $x^2 = x+1$.
> La **formula di Binet** ([[01 - Il Problema di Fibonacci#Algoritmo 1 — Formula di Binet|fibonacci1]]):
> $$F_n = \frac{1}{\sqrt{5}}\!\left(\phi^n - \hat{\phi}^n\right), \qquad \hat{\phi} = \frac{1-\sqrt{5}}{2} \approx -0{,}618$$
> Poiché $|\hat{\phi}| < 1$, il termine $\hat{\phi}^n \to 0$, quindi $F_n \approx \phi^n/\sqrt{5}$ e $F_n = \Theta(\phi^n)$.
> Il numero di nodi dell'albero di ricorsione di fibonacci2 è $\Theta(\phi^n)$ — cfr. [[03 - Equazioni di Ricorrenza#1.3 Caso con due chiamate ricorsive — $T(n) = T(n-1) + T(n-2) + 1$|§1.3]] e [[01 - Il Problema di Fibonacci#Algoritmo 2 — Ricorsione diretta|fibonacci2]].
## Esercizio 1.C — problema → algoritmo → costo
Tabella decisionale per l'Esercizio 1.C: dato il problema, quale algoritmo/struttura usare e quanto costa. Svolgimenti completi e trappole dettagliate in [[1.C — Algoritmi e complessità]].
### Ordinamento e Ricerca
| Problema | Algoritmo / Struttura | Costo | Note / trappola |
|---|---|---|---|
| Ordina $n$ interi in $[1, n^k]$, $k$ costante | Radix Sort in base $n$, $k$ passate di Integer Sort | $O(n)$ | Integer Sort diretto → $O(n+n^k)$; la base $n$ (non 10, non 2) è cruciale; linearità richiede $k=O(n^c)$ |
| Ordina $n$ interi in $[1, n\log\log n]$ | Radix Sort in base $n$, 2 passate | $O(n)$ | $n\log\log n=O(n^2)$ → 2 cifre in base $n$; Integer Sort diretto costerebbe $O(n\log\log n)$, superlineare |
| Ordina $n$ interi in intervallo di cardinalità costante $C$ (es. $[1,200]$, voti $18$–$30L$, $[n^3,n^3+100]$) | Integer Sort con offset (valore minimo dell'intervallo) | $O(n+C)=O(n)$ | Allocare array di taglia pari al valore massimo (es. $n^3+100$) anziché $C=101$; offset obbligatorio per indici corretti |
| Ordina $n$ bit $V[i]\in\{0,1\}$ | Integer Sort con $C=2$ contatori, offset $0$ | $O(n)$, spazio $O(1)$ | Caso degenere di Integer Sort; due contatori scalari sufficienti |
| Ordina $n$ elementi senza vincoli sul dominio | MergeSort o HeapSort | $\Theta(n\log n)$ | Lower bound $\Omega(n\log n)$; QuickSort deterministico ha worst-case $O(n^2)$ |
| Subroutine: fondi due array ordinati di taglia totale $n$ | Merge | $\Theta(n)$ | Unico scorrimento con array ausiliario; usata in MergeSort |
| Subroutine: partiziona $A[i;f]$ attorno al pivot | Partition | $\Theta(f-i)$ | Colloca il pivot nella posizione finale; usata in QuickSort |
| Cerca elemento in lista concatenata ordinata di $n$ nodi | Scansione sequenziale dalla testa | $O(n)$ | Ricerca binaria inapplicabile: raggiungere il nodo centrale richiede già $O(n)$ passi |
| Cerca elemento in vettore ordinato di $n$ elementi (accesso diretto) | Ricerca Binaria | $O(\log n)$ | Richiede accesso $O(1)$ per indice; su lista concatenata la stessa idea rimane $O(n)$ |
| Trova il secondo massimo (o minimo) in vettore non ordinato | Scansione lineare con $m_1$ e $m_2$ | $\Theta(n)$, spazio $O(1)$ | Ordinare è $O(n\log n)$: sovradimensionato; usare un heap idem |
| Calcola $F(n)$ con spazio minimo | `fibonacci4` — iterativo con due variabili | $O(n)$ tempo, $O(1)$ spazio | Spazio minimo raggiungibile; `fibonacci2` ricorsivo è $\Theta(\phi^n)$ — esponenziale |
| Calcola $F(n)$ con tempo minimo | `fibonacci6` — esponenziazione veloce di $M^{n-1}$ | $O(\log n)$ tempo, $O(\log n)$ spazio | `fibonacci6` **non** ha spazio $O(1)$: stack di `potenzaDiMatrice` pesa $O(\log n)$ |
### Strutture Dati
| Problema | Algoritmo / Struttura | Costo | Note / trappola |
|---|---|---|---|
| Costruisci un heap binario da $n$ chiavi non ordinate | Heapify (`muoviBasso` su tutti i nodi interni dal basso) | $\Theta(n)$ | $n$ inserzioni singole costano $O(n\log n)$; non usare insert ripetuto |
| Inserisci $n$ chiavi in heap binomiale vuoto | $n$ inserzioni singole (analisi ammortizzata) | $O(n)$ totale | Costo ammortizzato $O(1)$ per inserzione (carry propagation); non è Heapify binario |
| Merge di due heap binomiali con $n_1$ e $n_2$ nodi | merge binomiale (somma di due numeri binari) | $O(\log(n_1+n_2))$ | Es. $n_1=n,\,n_2=n^2$: $O(\log n^2)=O(\log n)$; $\log n^2=2\log n\ne\log^2 n$ |
| Merge di due heap binari con $n^2$ e $n$ nodi | Inserisci gli $n$ elem. del piccolo nel grande (ogni insert $O(\log n^2)=O(\log n)$) | $O(n\log n)$ | Heapify sull'unione costerebbe $O(n^2)$; per due heap di taglia $n$ uguali, Heapify $O(n)$ è meglio |
| Inserisci $k$ nuovi elementi in heap binario di $n$ | A) $k$ inserzioni $O(k\log(n+k))$; B) Heapify sull'unione $O(n+k)$ | dipende da $k$ | Per $k=\sqrt{n}$: A è $O(\sqrt{n}\log n)=o(n)$ → meglio di B ($O(n)$). Su heap binomiale: $k=2$ costa $O(\log n)$ pessimo, $O(1)$ ammortizzato per inserzione |
| Trova i $k$ massimi (o minimi) tra $n$ elementi | A) Heapify + $k$ estrazioni; B) min-heap di taglia $k$ in scansione | A) $O(n+k\log n)$; B) $O(n\log k)$ | $k$ costante → entrambe $O(n)$; per i $k$ **massimi** serve un *min*-heap di taglia $k$ |
| Costruisci dizionario per ricerche in $O(\log n)$ da $n$ chiavi | Array ordinato (MergeSort + Ricerca Binaria) **oppure** AVL ($n$ inserzioni) | Costruzione $O(n\log n)$; ricerca $O(\log n)$ | Lista ordinata non funziona (accesso al centro $O(n)$); hash table fuori programma |
| Inserisci $n$ chiavi una alla volta in AVL vuoto | $n$ inserzioni in AVL | $O(n\log n)$ | $\sum_{k=1}^{n}O(\log k)=O(n\log n)$; non esiste analogo lineare di Heapify per AVL |
| Visita BST in ordine crescente | In-order: sx → radice → dx | $\Theta(n)$ | Ogni nodo visitato esattamente una volta |
| Visita BST in ordine decrescente | In-order invertita: dx → radice → sx | $\Theta(n)$ | Non accumulare e rovesciare a posteriori (spazio $O(n)$ extra non necessario) |
| Trova il secondo minimo in AVL | Scendi al minimo ($O(\log n)$), poi risali al successore in-order ($O(\log n)$) | $O(\log n)$ | Visitare tutto l'AVL costerebbe $\Theta(n)$ |
| Trova il massimo $< x$ (floor) in AVL | Discendi come in una ricerca mantenendo il miglior candidato $<x$ incontrato scendendo a destra | $O(\log n)$ | Il candidato si aggiorna ad ogni svolta a destra; sfrutta la proprietà BST |
| Trova il $k$-esimo minimo in lista ordinata | Percorri sequenzialmente per $k$ passi | $O(k)$ | Nessun accesso diretto: impossibile fare $O(\log k)$ |
| Fondi AVL con $n$ nodi e AVL con $\log n$ nodi (tutte le chiavi del piccolo $>$ chiavi del grande) | In-order del piccolo + $\log n$ inserzioni nel grande | $O(\log^2 n)$ | Ricostruire da zero: $O(n\log n)$ — molto peggiore |
### Grafi
| Problema | Algoritmo / Struttura | Costo | Note / trappola |
|---|---|---|---|
| Nodi raggiungibili da $s$ in $G=(V,E)$ non pesato | BFS o DFS da $s$ | $O(n+m)$ liste; $O(n^2)$ matrice | Con matrice di adiacenza ogni riga va percorsa per intero |
| Raggiungibilità da $s$ con filtro sugli archi (es. peso $\le x$, colore) | BFS/DFS sul sottografo filtrato $G'$ | $O(n+m)$ liste; $O(n^2)$ matrice | Sequenze di tipi di archi → grafo a strati (stato = nodo + tipo atteso) con BFS su spazio degli stati |
| Distanze da $k$ sorgenti costanti in $G$ non orientato non pesato | $k$ BFS, una per sorgente | $O(n+m)$ per $k$ costante | Su non orientato $d(s,v)=d(v,s)$: non serve $G^T$ |
| Distanze (o raggiungibilità) *verso* nodo $t$ in $G$ orientato non pesato | BFS o DFS su $G^T$ da $t$ | $O(n+m)$ | BFS su $G$ dà distanze *da* $t$, non *verso* $t$; invertire gli archi è obbligatorio |
| Distanze *verso* $t$ in $G$ orientato pesato (pesi $\ge 0$) | Dijkstra su $G^T$ da $t$ | $O(m\log n)$ | $d_G(v\to t)=d_{G^T}(t\to v)$: basta un'unica esecuzione per ottenere tutte le distanze verso $t$ |
| Cammini minimi da sorgente $s$ (pesi non negativi) | Dijkstra$(G,s)$ | $O(m\log n)$ heap; $O(n^2)$ array su grafo denso | Pesi positivi ma limitati (es. tutti $>100$): red herring, non cambia il costo; pesi negativi → Dijkstra errato |
| Nodo a distanza massima da $s$ (pesi $\ge 0$) | Dijkstra$(G,s)$ + argmax su $d[\cdot]$ | $O(m\log n)$ | L'argmax finale ($O(n)$) è assorbito nella complessità di Dijkstra |
| Cammino minimo $s\to t$ passante per nodo intermedio obbligatorio $u$ | 2 Dijkstra (da $s$ e da $u$); verifica $d(s,u)+d(u,t)=d(s,t)$ | $O(m\log n)$ | Su non orientato $d(u,t)=d(t,u)$; su orientato serve terza Dijkstra da $t$ |
| Cammino minimo evitando nodo/arco proibito $w$ | Dijkstra su $G\setminus\{w\}$ (pesato) oppure BFS (non pesato) | $O(m\log n)$ pesato; $O(n+m)$ non pesato | Rimuovere $w$: togliere **tutti** gli archi incidenti (entranti e uscenti) |
| Cammino minimo con pesi in $\{1,2\}$ | Sostituisci ogni arco di peso $2$ con 2 archi di peso $1$ + BFS sul grafo espanso | $O(n+m)$ | Ogni arco di peso $2$ introduce un nodo intermedio; il grafo espanso ha solo pesi unitari |
| Distanze minime tra tutte le coppie di nodi (pesi $\ge 0$) | $n$ esecuzioni di Dijkstra | $O(nm\log n)$ heap; $O(n^3)$ array su grafo denso | Floyd-Warshall ($O(n^3)$) è fuori programma Modulo I |
| Diametro di $G$ non orientato non pesato | $n$ BFS, una per ogni sorgente $u\in V$; massimo delle distanze | $O(n(n+m))$ | 1 sola BFS dà distanze da un nodo, non il diametro globale; trucco "2 BFS" vale solo per alberi |
| $G$ fortemente connesso? (1 sola CFC) | Componenti Fortemente Connesse (DFS su $G^R$ per `post(v)` + DFS su $G$ in ordine decrescente di `post`) | $\Theta(n+m)$ | 1 visita verifica solo raggiungibilità *da* un nodo; `post(v)` si calcola su $G^R$, seconda DFS su $G$ — invertirli dà risultati errati |
| Esistono nodi non mutuamente raggiungibili? ($\ge 2$ CFC) | Componenti Fortemente Connesse (2 DFS) | $\Theta(n+m)$ | Sì se la DFS-forest di $G$ produce $\ge 2$ alberi |
| Esiste $s\to t$ ma non $t\to s$? (arco nel DAG delle CFC) | Componenti Fortemente Connesse + verifica arco $(u,v)$ con $\text{cfc}(u)\ne\text{cfc}(v)$ nel DAG | $\Theta(n+m)$ | "$\ge 2$ CFC" non basta: se le componenti sono isolate nessun arco le collega |
| Disponi i nodi di $G$ diretto con tutti gli archi orientati nello stesso verso | Ordinamento Topologico (DFS con `post(v)` decrescente, o algoritmo di Kahn) | $\Theta(n+m)$ | Esiste se e solo se $G$ è un DAG; un ciclo rende la disposizione impossibile |
## Riepilogo complessità
Tabellone di riferimento ($n$ = elementi/nodi, $m$ = archi, $k$ = ampiezza del dominio delle chiavi, $h$ = altezza dell'albero).
| Algoritmo | Tempo | Note |
|---|---|---|
| Fibonacci ricorsivo | $O(\phi^n)$ | esponenziale |
| Fibonacci DP / iterativo | $\Theta(n)$ | spazio $\Theta(1)$ nella v. iterativa |
| Fibonacci potenza di matrice | $O(\log n)$ | con esponenziazione veloce |
| RicercaSequenziale | $O(n)$ | vettore non ordinato |
| RicercaBinaria | $O(\log n)$ | vettore ordinato |
| SelectionSort | $\Theta(n^2)$ | in loco, non stabile |
| InsertionSort | $O(n^2)$, $\Omega(n)$ | in loco, stabile, ottimo se quasi ordinato |
| BubbleSort | $O(n^2)$ | in loco, stabile |
| MergeSort | $\Theta(n\log n)$ | stabile, non in loco |
| QuickSort | $\Theta(n\log n)$ medio, $O(n^2)$ peggiore | in loco, non stabile |
| HeapSort | $O(n\log n)$ | in loco, non stabile |
| IntegerSort / Counting | $O(n+k)$ | **non** stabile nella versione base; lineare se $k=O(n)$ |
| RadixSort | $\Theta\!\left((n+b)\frac{\log k}{\log b}\right)$ | stabile; lineare se $k=O(n^c)$ (base $b=\Theta(n)$) |
| BucketSort | $O(n+k)$ | stabile |
| Pila / Coda (push, pop, enqueue, dequeue) | $O(1)$ | array (circolare per la coda) |
| Visite di alberi (DFS, BFS, altezza, foglie, …) | $\Theta(n)$ | |
| Heap: insert, delete, decreaseKey, increaseKey | $O(\log n)$ | |
| Heap: findMin | $O(1)$ | |
| Heap: Heapify (costruzione) | $O(n)$ | non $O(n\log n)$ |
| Heap binomiale: merge / costruzione | $O(\log n)$ / $O(n)$ amm. | unione efficiente; cenni heap di Fibonacci |
| BST: search, insert, delete, min, successore | $O(h)$ | $O(n)$ nel caso peggiore |
| AVL: tutte le operazioni | $O(\log n)$ | altezza garantita $O(\log n)$ |
| BFS / DFS su grafo | $O(n+m)$ | liste di adiacenza |
| Ordinamento topologico | $O(n+m)$ | solo su DAG |
| Componenti fortemente connesse | $O(n+m)$ | due DFS |
| Dijkstra | $O(m\log n)$ | heap binario; pesi non negativi |
| 0-1 BFS | $O(n+m)$ | pesi $\in\{0,1\}$, con deque |
## Trappole ricorrenti
Errori che costano punti all'esame.

> [!warning] Casi peggiori e pre-condizioni
> - **RicercaBinaria**: richiede il vettore **ordinato**; su uno non ordinato non vale $O(\log n)$.
> - **QuickSort**: $O(n^2)$ se il perno è sempre il minimo/massimo (es. array già ordinato con perno $A[i]$).
> - **IntegerSort/Counting/Bucket**: lineari solo se $k = O(n)$; non sono ordinamenti per confronti, quindi aggirano il lower bound $\Omega(n\log n)$.
> - **BST non bilanciato**: le operazioni sono $O(h)$, che degenera a $O(n)$; l'AVL garantisce $h = O(\log n)$.
> - **Dijkstra**: corretto **solo con pesi non negativi**; con pesi negativi serve Bellman-Ford (Modulo II).
> - **Heapify vs $n$ insert**: costruire un heap con Heapify è $O(n)$; $n$ `insert` successive costano $O(n\log n)$.
> - **$G^T$ (grafo trasposto)**: per distanze o raggiungibilità *verso* un nodo $t$ si lavora su $G^T$; una visita su $G$ dà le distanze *da* $t$, non *verso*.
> - **Master Theorem**: non si applica alle ricorrenze **sottrattive** ($T(n-c)$) né quando c'è un *gap* fra $f(n)$ e $n^{\log_b a}$ — usa srotolamento o albero di ricorsione.
> - **$o$ / $\omega$ vs $\Theta$**: se $\lim f/g = c$ finito e non nullo la relazione è **solo** $\Theta$, non $o$ né $\omega$.
> - **Componenti Fortemente Connesse**: i valori `post(v)` si calcolano sul trasposto, la seconda visita su $G$ in ordine decrescente di `post`; invertire i due passi è errato.
