---
tags:
  - algoritmi
  - ricorrenze
slide: "4"
capitolo: "Demetrescu cap. 2"
---
# Equazioni di Ricorrenza
La complessità temporale di un algoritmo ricorsivo si esprime in modo naturale come un'**equazione di ricorrenza**: una relazione che definisce $T(n)$ in termini di $T$ su istanze più piccole. L'obiettivo è trovare una forma chiusa o asintotica (nel senso di [[02 - Notazioni Asintotiche]]), eliminando la dipendenza ricorsiva. Questo è il punto di partenza per analizzare tutti gli algoritmi divide-et-impera, tra cui il [[04 - Algoritmi di Ordinamento#Merge Sort|Merge Sort]] e la ricerca binaria, nonché algoritmi più semplici come [[01 - Il Problema di Fibonacci|Fibonacci]] ricorsivo.
## Struttura generale
Ogni equazione di ricorrenza ha due parti obbligatorie: il **caso ricorsivo** (per $n$ grande) e il **caso base** (per $n$ costante). Il caso base è quasi sempre $T(\text{cost}) = \Theta(1)$, spesso scritto $T(1) = 1$ per semplicità.

Esempi tipici che compaiono nel corso:

| Algoritmo | Ricorrenza |
|---|---|
| Fibonacci2 | $T(n) = T(n-1) + T(n-2) + O(1)$ |
| Ricerca binaria | $T(n) = T(n/2) + O(1)$ |
| Algoritmo ottimo di pesatura (Alg4) | $T(n) = T(n/3) + O(1)$ |
| Merge Sort | $T(n) = 2T(n/2) + \Theta(n)$ |

I metodi di risoluzione coperti in questo capitolo sono: **iterazione**, **albero della ricorsione**, **sostituzione**, **Teorema Master** e **cambiamento di variabile**.
## 1. Metodo dell'iterazione (srotolamento)
L'idea è sviluppare la ricorrenza sostituendo iterativamente i termini ricorsivi finché non compare solo il caso base, ottenendo una sommatoria dipendente unicamente da $n$.
### 1.1 Caso divisione — $T(n) = T(n/b) + f(n)$
> [!example] Esempio — $T(n) = T(n/2) + c$
> Ricerca binaria: ogni passo divide a metà l'array e fa $O(1)$ lavoro.
>
> Srotolamento:
> $$T(n) = c + T(n/2) = 2c + T(n/4) = 3c + T(n/8) = \ldots = ic + T(n/2^i)$$
> Per $i = \log_2 n$ si raggiunge il caso base $T(1)$:
> $$T(n) = c\log_2 n + T(1) = \Theta(\log n)$$

> [!example] Esempio — $T(n) = T(n-1) + 1$
> D: Quanto costa un algoritmo che esegue $O(1)$ lavoro e chiama se stesso su $n-1$?
> R: Srotolando $T(n) = T(n-1)+1 = T(n-2)+2 = \ldots = T(n-i)+i$. Per $i = n-1$: $T(n) = T(1) + n-1 = \Theta(n)$.
### 1.2 Caso sottrazione — pattern e regole rapide
Quando la dimensione si riduce sottraendo una costante, i pattern si ripetono e si possono riconoscere rapidamente.

**Pattern A — Costo polinomiale, coefficiente 1:**

Se $T(n) = T(n-k) + n^p$ (con $k$ costante e $p \ge 0$), dopo $n/k$ passi si accumula una somma di potenze $p$-esime. Poiché $\sum_{i=1}^{n} i^p = \Theta(n^{p+1})$, si ottiene:

> [!info] Regola rapida — caso polinomiale
> $$T(n) = T(n-k) + n^p \implies T(n) = \Theta(n^{p+1})$$
> La costante $k$ non cambia l'ordine asintotico.
> Esempi: $T(n)=T(n-1)+n^2 \implies \Theta(n^3)$; $T(n)=T(n-4)+n^2 \implies \Theta(n^3)$.

**Pattern B — Moltiplicazione dei sottoproblemi, coefficiente $a > 1$:**

Se $a > 1$, a ogni passo il numero di chiamate si moltiplica, producendo un albero binario (o $a$-ario) completo.

> [!example] Esempio — $T(n) = 2T(n-1) + 1$ (Torre di Hanoi)
> Srotolamento:
> $$T(n) = 2T(n-1)+1 = 4T(n-2)+2+1 = 8T(n-3)+4+2+1 = \ldots = 2^i T(n-i) + \sum_{j=0}^{i-1}2^j$$
> Per $i = n-1$: $T(n) = 2^{n-1}T(1) + (2^{n-1}-1) = \Theta(2^n)$.

> [!info] Regola rapida — caso esponenziale
> $$T(n) = a \cdot T(n-k) + \Theta(1),\quad a > 1 \implies T(n) = \Theta(a^{n/k})$$
> Esempio: $T(n) = 2T(n-2)+1 \implies \Theta(2^{n/2}) = \Theta(\sqrt{2}^n)$.

**Pattern C — Misto (esponenziale + polinomio):**

> [!info] Regola rapida — caso misto
> $$T(n) = a \cdot T(n-k) + n^p,\quad a > 1 \implies T(n) = \Theta(a^{n/k})$$
> Il termine esponenziale domina sempre il polinomio. Esempio: $T(n) = 2T(n-1)+n \implies \Theta(2^n)$.

> [!warning] Attenzione al coefficiente
> La distinzione critica è se il coefficiente davanti a $T$ è **1** (caso polinomiale) oppure **$a > 1$** (caso esponenziale). Non confonderli: $T(n)=T(n-1)+n \implies \Theta(n^2)$, ma $T(n)=2T(n-1)+n \implies \Theta(2^n)$.
### 1.3 Caso con due chiamate ricorsive — $T(n) = T(n-1) + T(n-2) + 1$
Questa ricorrenza corrisponde esattamente all'algoritmo [[01 - Il Problema di Fibonacci|fibonacci2]] ricorsivo, in cui ogni chiamata di dimensione $n$ genera due chiamate di dimensione $n-1$ e $n-2$.
**Upper bound (maggiorazione):** si maggiora con $R(n) = 2R(n-1)+1$, che dà $R(n) = \Theta(2^n)$, quindi $T(n) = O(2^n)$.
**Lower bound (albero della ricorsione):** l'albero delle chiamate ricorsive è identico all'albero di fibonacci2. Ogni nodo costa $O(1)$, quindi $T(n)$ è proporzionale al numero di nodi. I nodi del livello $k$ sono quanti modi ci sono di decomporre $n$ in somme di 1 e 2, il che cresce come $\Theta(\phi^n)$ dove $\phi = \frac{1+\sqrt{5}}{2} \approx 1.618$ (numero aureo). Poiché $\phi < 2$, si ha $T(n) = o(2^n)$.

> [!example] Fibonacci2: stima del numero di nodi
> L'albero delle chiamate di fibonacci2 ha $\Theta(\phi^n)$ nodi, perché i livelli si espandono esattamente con i numeri di Fibonacci. Il costo per nodo è $O(1)$, quindi:
> $$T(n) = T(n-1)+T(n-2)+1 \implies T(n) = \Theta(\phi^n)$$
> Questo giustifica l'inefficienza dell'implementazione ricorsiva naive di [[01 - Il Problema di Fibonacci|Fibonacci]].
## 2. Metodo dell'albero di ricorsione
Il metodo dell'albero di ricorsione è un modo **grafico** di applicare l'iterazione. Si disegna l'albero delle chiamate ricorsive, si stima il costo per livello, si conta il numero di livelli e si somma tutto.

**Procedura generale:**
1. Disegnare l'albero: la radice ha dimensione $n$, i figli rappresentano i sottoproblemi.
2. Per ogni livello $i$: calcolare numero di nodi $N_i$, costo per nodo $C_i$, costo totale $L_i = N_i \cdot C_i$.
3. Determinare l'altezza $h$ dell'albero (quando la dimensione raggiunge il caso base).
4. Sommare: $T(n) = \sum_{i=0}^{h} L_i$.

> [!info] Due suggerimenti pratici
> - Se il costo per nodo è costante, $T(n)$ è proporzionale al numero di nodi.
> - Se il costo per livello è costante, $T(n)$ è proporzionale al numero di livelli.

> [!example] Esempio dettagliato — Merge Sort: $T(n) = 2T(n/2) + cn$
> **Struttura per livelli:**
>
> | Livello $i$ | Nodi | Dim. sottoproblema | Costo/nodo | Costo livello |
> |---|---|---|---|---|
> | 0 | 1 | $n$ | $cn$ | $cn$ |
> | 1 | 2 | $n/2$ | $c(n/2)$ | $cn$ |
> | 2 | 4 | $n/4$ | $c(n/4)$ | $cn$ |
> | $i$ | $2^i$ | $n/2^i$ | $c(n/2^i)$ | $cn$ |
> | $\log_2 n$ | $n$ | 1 | $O(1)$ | $O(n)$ |
>
> **Altezza:** il caso base si raggiunge quando $n/2^i = 1$, cioè $i = \log_2 n$.
>
> **Somma:** ogni livello costa esattamente $cn$, e i livelli sono $\log_2 n + 1$:
> $$T(n) = cn(\log_2 n + 1) = \Theta(n \log n)$$
> Questo giustifica la complessità del [[04 - Algoritmi di Ordinamento#Merge Sort|Merge Sort]].

> [!example] Esempio — $T(n) = T(n/3) + T(2n/3) + n$
> L'albero non è bilanciato: il ramo sinistro ha altezza $\log_3 n$ (più corto) e il ramo destro $\log_{3/2} n$ (più lungo). Il costo di ogni livello è esattamente $n$ (la somma delle frazioni ricostruisce $n$). Il numero di livelli è $O(\log_{3/2} n) = O(\log n)$.
>
> Quindi: $T(n) = O(n \log n)$. Per il lower bound, i livelli completi (almeno fino a $\log_3 n$) costano già $n \log_3 n = \Omega(n \log n)$.
>
> **Risultato:** $T(n) = \Theta(n \log n)$.

> [!warning] Alberi non bilanciati
> Quando i sottoproblemi hanno dimensioni diverse (es. $n/3$ e $2n/3$), l'altezza si determina sul cammino **più lungo**. In questi casi il Teorema Master non si applica direttamente e il metodo grafico è indispensabile.
## 3. Metodo della sostituzione
Il metodo della sostituzione non serve a trovare la soluzione, ma a **verificare** che una soluzione ipotizzata sia corretta, usando l'induzione matematica.

**Procedura:**
1. **Indovinare** la forma della soluzione (spesso suggerita dall'albero di ricorsione o dall'esperienza).
2. **Dimostrare per induzione** che $T(n) \le c \cdot g(n)$ per qualche costante $c > 0$.
3. **Ricavare la costante** $c$ risolvendo la disequazione che emerge dal passo induttivo.

> [!example] Esempio — $T(n) = n + T(n/2)$, $T(1) = 1$
> **Ipotesi:** $T(n) = O(n)$, cioè vogliamo mostrare $T(n) \le c \cdot n$.
>
> **Caso base:** $T(1) = 1 \le c \cdot 1$ per ogni $c \ge 1$. ✓
>
> **Passo induttivo:** assumiamo $T(k) \le ck$ per ogni $k < n$. Allora:
> $$T(n) = n + T(n/2) \le n + c(n/2) = \left(\frac{c}{2}+1\right)n$$
> Affinché $T(n) \le cn$ basta che $\frac{c}{2}+1 \le c$, cioè $c \ge 2$.
>
> **Conclusione:** $T(n) \le 2n$, quindi $T(n) = O(n)$.

> [!example] Esempio avanzato — $T(n) = 4T(n/2) + n$, $T(1) = 1$
> **Prima ipotesi — $T(n) = O(n^3)$:** proviamo $T(n) \le c n^3$.
>
> $T(n) = 4T(n/2)+n \le 4c(n/2)^3+n = \frac{c}{2}n^3+n = cn^3 - \left(\frac{c}{2}n^3 - n\right)$.
>
> Il residuo $-\!\left(\frac{c}{2}n^3 - n\right) \le 0$ per $n$ sufficientemente grande e $c \ge 1$. Caso base: $T(1)=1 \le c$ per $c \ge 1$. Scegliendo $c=2$: $T(n) \le 2n^3$, quindi $T(n) = O(n^3)$. ✓ (funziona, ma è un bound non stretto)
>
> **Seconda ipotesi — $T(n) = O(n^2)$, tentativo con un parametro:** proviamo $T(n) \le cn^2$.
>
> $T(n) = 4T(n/2)+n \le 4c(n/2)^2+n = cn^2+n$.
>
> Non si riesce a concludere che $cn^2+n \le cn^2$: il residuo $+n > 0$ non può essere assorbito. L'ipotesi $O(n^2)$ è corretta (lo è!), ma questa forma con un solo parametro non funziona.
>
> **Ipotesi raffinata — $T(n) \le c_1 n^2 - c_2 n$ (forma più forte):**
>
> $T(n) \le 4\bigl(c_1(n/2)^2 - c_2(n/2)\bigr)+n = c_1 n^2 - 2c_2 n + n = c_1 n^2 - c_2 n - (c_2 n - n)$.
>
> Il residuo $-(c_2 n - n) \le 0$ se $c_2 \ge 1$. Caso base: $T(1)=1 \le c_1 - c_2$, soddisfatto con $c_1=2, c_2=1$. Quindi $T(n) \le 2n^2 - n$, confermando $T(n) = O(n^2)$. ✓

> [!warning] Sottigliezza del metodo
> L'ipotesi $T(n) \le cn^2$ con un solo parametro può fallire anche quando la risposta è $O(n^2)$: il residuo positivo "rompe" la dimostrazione. In quel caso si introduce un termine di correzione (sottrattivo) nella forma dell'ipotesi, ad es. $c_1n^2 - c_2n$. Il metodo di sostituzione richiede **esperienza**: scegliere un bound sovra-stimato (es. $O(n^3)$) è sempre più semplice, ma per ottenere il bound stretto occorre affinare l'ipotesi iterativamente.
## 4. Teorema Master
Il Teorema Master fornisce una soluzione diretta per le ricorrenze prodotte dalla tecnica **divide et impera**: il problema di dimensione $n$ viene suddiviso in $a$ sottoproblemi di dimensione $n/b$, e la fase di divisione/combinazione costa $f(n)$.

> [!quote] Teorema — Master
> Data la ricorrenza
> $$T(n) = \begin{cases} a\,T(n/b) + f(n) & n > 1 \\ \Theta(1) & n = 1 \end{cases}$$
> con $a \ge 1$, $b > 1$ costanti e $f(n)$ asintoticamente positiva, si pone lo **spartiacque** $n^{\log_b a}$ (numero di foglie dell'albero di ricorsione). Allora:
>
> **Caso 1 — le foglie dominano:**
> se $f(n) = O(n^{\log_b a - \varepsilon})$ per qualche $\varepsilon > 0$, allora $T(n) = \Theta(n^{\log_b a})$.
>
> **Caso 2 — pareggio:**
> se $f(n) = \Theta(n^{\log_b a})$, allora $T(n) = \Theta(n^{\log_b a} \log n)$.
>
> **Caso 3 — la radice domina:**
> se $f(n) = \Omega(n^{\log_b a + \varepsilon})$ per qualche $\varepsilon > 0$ **e** vale la condizione di regolarità $a\,f(n/b) \le c\,f(n)$ per qualche $c < 1$ e $n$ sufficientemente grande, allora $T(n) = \Theta(f(n))$.

La logica intuitiva: si confronta il costo dello strato delle foglie $n^{\log_b a}$ con il costo della radice $f(n)$. Chi è polinomialmente più grande determina il $\Theta$; se sono dello stesso ordine, si moltiplica per $\log n$.

> [!example] Esempi applicativi
> 1. $T(n) = 2T(n/2) + n$: $a=2, b=2$, spartiacque $n^{\log_2 2} = n$. $f(n) = n = \Theta(n)$ → **Caso 2** → $T(n) = \Theta(n \log n)$ (Merge Sort).
> 2. $T(n) = 3T(n/9) + 1$: $a=3, b=9$, spartiacque $n^{\log_9 3} = n^{1/2} = \sqrt{n}$. $f(n)=1 = O(n^{1/2-\varepsilon})$ → **Caso 1** → $T(n) = \Theta(\sqrt{n})$.
> 3. $T(n) = 3T(n/9) + n$: $a=3, b=9$, spartiacque $\sqrt{n}$. $f(n)=n = \Omega(n^{1/2+\varepsilon})$. Regolarità: $3 \cdot (n/9) = n/3 \le cn$ per $c=1/3 < 1$ ✓ → **Caso 3** → $T(n) = \Theta(n)$.
### Condizione di regolarità (Caso 3)
La condizione $a\,f(n/b) \le c\,f(n)$ con $c < 1$ dice che il costo totale dei figli è strettamente minore del costo del padre: il lavoro si concentra alla radice e non cresce verso le foglie. Per le funzioni polinomiali questa condizione è sempre soddisfatta; per funzioni sub-polinomiali o oscillanti può fallire.
### Quando il Teorema Master NON si applica
> [!warning] Limitazioni del Teorema Master
> Il teorema **non si applica** nei seguenti casi:
> 1. **Forma non canonica** (sottrazione invece di divisione): $T(n) = T(n-1) + n$ — usare iterazione.
> 2. **Coefficiente $a$ non costante**: $T(n) = nT(n/2) + n$ — $a$ dipende da $n$.
> 3. **Base $b$ non costante**: $T(n) = 2T(n/\log n) + n$ — $b$ dipende da $n$.
> 4. **Gap tra Caso 1 e Caso 2**: $T(n) = 2T(n/2) + n/\log n$ — $f(n)$ non è né $O(n^{1-\varepsilon})$ né $\Theta(n)$ — usare albero di ricorsione.
> 5. **$f(n)$ non è polinomialmente più grande dello spartiacque**: $T(n) = 2T(n/2) + n\log n$ — $f(n) = \Theta(n \log n)$ non è $\Theta(n^{1+\varepsilon})$, quindi il Caso 3 non scatta (in realtà è un caso 2 esteso: $T(n) = \Theta(n \log^2 n)$, ma il teorema base non lo copre).
## 5. Cambiamento di variabile
Alcune ricorrenze con argomenti non lineari (radici, potenze frazionarie) si risolvono introducendo una sostituzione che riconduce a una forma nota.

> [!example] Esempio — $T(n) = T(\sqrt{n}) + O(1)$, $T(1) = 1$
> Poniamo $n = 2^m$, ovvero $m = \log_2 n$. Osserviamo che $\sqrt{n} = n^{1/2} = 2^{m/2}$.
>
> Definiamo $R(m) = T(2^m)$. La ricorrenza diventa:
> $$R(m) = R(m/2) + O(1)$$
> Questa è esattamente la ricorrenza della ricerca binaria su $m$: $R(m) = \Theta(\log m)$.
>
> Tornando alla variabile originale: $T(n) = R(\log_2 n) = \Theta(\log(\log n))$.

> [!example] Esempio — $T(n) = 2T(\sqrt{n}) + \log n$
> Stessa sostituzione $n = 2^m$, $R(m) = T(2^m)$:
> $$R(m) = 2R(m/2) + m$$
> Applicando il Teorema Master (Caso 2, $a=2, b=2$, spartiacque $m$, $f(m)=m$): $R(m) = \Theta(m \log m)$.
>
> Tornando a $n$: $T(n) = \Theta(\log n \cdot \log(\log n))$.

> [!info] Schema generale del cambiamento di variabile
> Per ricorrenze del tipo $T(n) = \alpha T(n^{1/k}) + f(n)$:
> 1. Poni $n = b^m$ con $b$ opportuno (di solito $b=2$).
> 2. Definisci $R(m) = T(b^m)$.
> 3. Riscrivi la ricorrenza in $R(m)$: l'argomento $n^{1/k} = b^{m/k}$ diventa $R(m/k)$.
> 4. Risolvi la ricorrenza in $m$ con i metodi standard.
> 5. Sostituisci $m = \log_b n$ per tornare a $n$.
## Esercizi svolti dagli esami
### Esercizio 1 — $T(n) = 2T(n/2) + n$ (Compito 02/07/2025, 18/02/2025)
**Metodo:** Teorema Master.
$a=2,\ b=2$, spartiacque $n^{\log_2 2} = n$. $f(n)=n = \Theta(n)$ → Caso 2 (pareggio).
**Soluzione:** $\boxed{\Theta(n \log n)}$ — è la complessità del Merge Sort.
### Esercizio 2 — $T(n) = 2T(n/4) + 1$ (Compito 26/06/2025)
**Metodo:** Teorema Master.
$a=2,\ b=4$, spartiacque $n^{\log_4 2} = n^{1/2} = \sqrt{n}$. $f(n)=1 = O(n^{1/2-\varepsilon})$ → Caso 1 (foglie dominano).
**Soluzione:** $\boxed{\Theta(\sqrt{n})}$.
### Esercizio 3 — $T(n) = 4T(n/4) + n$ (Compito 18/02/2025)
**Metodo:** Teorema Master.
$a=4,\ b=4$, spartiacque $n^{\log_4 4} = n$. $f(n)=n = \Theta(n)$ → Caso 2.
**Soluzione:** $\boxed{\Theta(n \log n)}$.
### Esercizio 4 — $T(n) = T(n/8) + n$ (Compito 09/09/2025)
**Metodo:** Teorema Master.
$a=1,\ b=8$, spartiacque $n^{\log_8 1} = n^0 = 1$. $f(n)=n = \Omega(n^{0+\varepsilon})$ → Caso 3. Regolarità: $1 \cdot f(n/8) = n/8 \le cn$ per $c = 1/8 < 1$ ✓.
**Soluzione:** $\boxed{\Theta(n)}$.
### Esercizio 5 — $T(n) = T(n/8) + \sqrt{n}$ (Compito 23/09/2025)
**Metodo:** Teorema Master.
$a=1,\ b=8$, spartiacque $1$. $f(n)=\sqrt{n} = \Omega(1^{+\varepsilon})$ → Caso 3. Regolarità: $\sqrt{n/8} = \sqrt{n}/\sqrt{8} \le c\sqrt{n}$ per $c = 1/\sqrt{8} < 1$ ✓.
**Soluzione:** $\boxed{\Theta(\sqrt{n})}$.
### Esercizio 6 — $T(n) = 2T(n/8) + 1$ (Compito 02/02/2026)
**Metodo:** Teorema Master.
$a=2,\ b=8$, spartiacque $n^{\log_8 2} = n^{1/3} = \sqrt[3]{n}$. $f(n)=1 = O(n^{1/3-\varepsilon})$ → Caso 1.
**Soluzione:** $\boxed{\Theta(\sqrt[3]{n})}$.
### Esercizio 7 — $T(n) = T(n-1) + n^2$ (Compito 23/09/2025)
**Metodo:** Iterazione (sottrazione, costo polinomiale).
Srotolando: $T(n) = T(1) + \sum_{i=2}^{n} i^2$. Poiché $\sum_{i=1}^{n} i^2 = \frac{n(n+1)(2n+1)}{6} = \Theta(n^3)$:
**Soluzione:** $\boxed{\Theta(n^3)}$ (regola rapida: $p=2 \implies p+1=3$).
### Esercizio 8 — $T(n) = T(n-4) + n^2$ (Compito 18/02/2025)
**Metodo:** Iterazione (sottrazione, costante $k=4$).
Numero di passi: $\Theta(n/4) = \Theta(n)$. La costante $k$ non cambia l'ordine: si somma ancora $\Theta(n^2)$ per $\Theta(n)$ passi (con valori decrescenti), ottenendo $\Theta(n^3)$.
**Soluzione:** $\boxed{\Theta(n^3)}$ (regola rapida indipendente da $k$).
### Esercizio 9 — $T(n) = 2T(n-2) + 1$ (Compito 02/02/2026, 26/06/2025)
**Metodo:** Iterazione (sottrazione, coefficiente $a=2>1$).
Srotolando: dopo $k$ passi $T(n) = 2^k T(n-2k) + \sum_{j=0}^{k-1} 2^j = 2^k T(n-2k) + 2^k - 1$.
Caso base $n-2k = 1 \implies k = (n-1)/2$:
$$T(n) = 2^{(n-1)/2} T(1) + 2^{(n-1)/2} - 1 = \Theta(2^{n/2}) = \Theta(\sqrt{2}^n)$$
**Soluzione:** $\boxed{\Theta(\sqrt{2}^n)}$ (regola rapida: $a=2, k=2 \implies \Theta(2^{n/2})$).
### Esercizio 10 — $T(n) = T(\sqrt{n}) + 1$ (Compito 09/09/2025, 18/07/2025)
**Metodo:** Cambiamento di variabile.
$n = 2^m$, $R(m) = T(2^m)$: $R(m) = R(m/2)+1 \implies R(m) = \Theta(\log m)$.
Tornando: $T(n) = \Theta(\log(\log n))$.
**Soluzione:** $\boxed{\Theta(\log \log n)}$.
## Tabella riassuntiva dei pattern comuni
| Pattern | Metodo | Complessità |
|---|---|---|
| $T(n/b) + \Theta(1)$, foglie $\gg$ radice | Master Caso 1 | $\Theta(n^{\log_b a})$ |
| $aT(n/b) + \Theta(n^{\log_b a})$ | Master Caso 2 | $\Theta(n^{\log_b a} \log n)$ |
| $T(n/b) + f(n)$, radice $\gg$ foglie | Master Caso 3 | $\Theta(f(n))$ |
| $T(n-k) + n^p$ | Iterazione | $\Theta(n^{p+1})$ |
| $aT(n-k) + \Theta(1)$, $a > 1$ | Iterazione | $\Theta(a^{n/k})$ |
| $aT(n-k) + n^p$, $a > 1$ | Iterazione | $\Theta(a^{n/k})$ |
| $T(\sqrt{n}) + \Theta(1)$ | Cambio variabile | $\Theta(\log \log n)$ |
| $2T(\sqrt{n}) + \log n$ | Cambio variabile | $\Theta(\log n \cdot \log \log n)$ |
| $T(n) = T(n-1)+T(n-2)+O(1)$ | Albero / maggiorazione | $\Theta(\phi^n)$ (come [[01 - Il Problema di Fibonacci|Fibonacci]]) |
