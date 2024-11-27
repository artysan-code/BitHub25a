[[2 - Introduzione informale agli algoritmi|Torna alla lezione precedente]]
[[4 - Metodo dello Srotolamento e Albero di ricorsione|Continua alla lezione successiva.]]
## Modelli di calcolo
Un modello utilizzato ampiamente nel passato era quello della **macchina di Turing**, che era composto di un meccanismo di controllo, un nastro di memorizzazione e una testina di lettura e scrittura. Questo modello però è poco vicino alla macchina che noi studiamo.

Un modello più realistico di calcolo è quello della **RAM**, cioè della macchina a registri. Possiede: un programma finito, un nastro di input/output, una memoria strutturata come array e una CPU esegue istruzioni.

Tramite questo modello analizziamo il programma basandoci sul concetto di **passo elementare**. I passi elementari su una **RAM** sono:
- Istruzione di ingresso/uscita (I/O).
- Operazione aritmetico/logica.
- Accesso/modifica contenuto in memoria.

Ma quanto costano queste operazioni? (Il metodo per calcolarlo nel generico è quello del **costo uniforme**)
### Criterio di costo uniforme
Tutte le operazioni hanno lo stesso costo e la complessità temporale è misurata come **numero di passi elementari eseguiti**.
### Criterio di costo logaritmico
Il costo dell'operazione singola dipende dalla dimensione degli operandi dell'istruzione. Quindi un'operazione con un operando di valore $x$ costerà $\log(x)$. Modella meglio la complessità di **algoritmi "numerici"**.
## Caso peggiore e caso medio
Misurando il tempo di esecuzione di un algoritmo in funzione della dimensione n delle istanze, noteremo che **istanze diverse**, a parità di dimensione, potrebbero richiedere tempo diverso.

Ma cosa vuol dire caso medio e caso peggiore?

Sia **tempo(I)** il tempo di esecuzione di un algoritmo di sull'istanza **I**, il **caso peggiore**:$$T_{worst}(n)=max_{\text{ istanze I di dimensione n }}\{tempo(I)\}$$
Rappresenta quindi il tempo che viene impiegato quando le istanze di input comportano più lavoro all'algoritmo. Rappresenta una **garanzia** sul tempo di esecuzione.


Sia **P(I)** la probabilità di occorrenza dell'istanza **I**:$$\begin{array}{}
T_{avg}(n)=\displaystyle\sum_{I}^n\{P(I) tempo(I)\} & \text{dove I sono le istanze e n il numero di esse}
\end{array}$$
Quindi $T_{avg}(n)$ è intuitivamente il tempo di esecuzione nel **caso medio**, ovvero sulle istanze di input tipiche del problema. Ma come conosco la **distribuzione di probabilità sulle istanze?**
Semplice! (di solito) Non puoi!

Bisogna fare una assunzione (spesso non realistica).
## Notazioni Asintotiche
Esprimiamo la complessità computazionale di un algoritmo espressa con una funzione $T(n)$.$$T(n): \#\text{passi elementari eseguiti su RAM nel caso peggiore su un'istanza di dimensione n}$$
L'idea è descrivere T(n) in modo qualitativo. Perdiamo un po’ in precisione (senza perdere l’essenziale) e guadagniamo semplicità.

Si ignorano:
- Costanti moltiplicative
- Termini di ordine inferiore

Tempi di esecuzione di differenti algoritmi per istanze di dimensioni crescenti su un processore che sa eseguire milioni di istruzioni di alto livello al secondo. L'indicazione **very long** indica che il tempo di calcolo supera $10^{25}$ anni.

|               |  $n$   | $n \log_n n$ |  $n^2$  |    $n^3$     |   $1,5^n$    |      $2^n$      |      $n!$       |
| :-----------: | :----: | :----------: | :-----: | :----------: | :----------: | :-------------: | :-------------: |
|    $n=10$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    <1 sec    |     <1 sec      |      4 sec      |
|    $n=30$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    <1 sec    |     18 min      | $10^{25}$ years |
|    $n=50$     | <1 sec |    <1 sec    | <1 sec  |    <1 sec    |    11 min    |    36 years     |    very long    |
|    $n=100$    | <1 sec |    <1 sec    | <1 sec  |    1 sec     | 12.892 years | $10^{17}$ years |    very long    |
|   $n=1.000$   | <1 sec |    <1 sec    |  1 sec  |    18 min    |  very long   |    very long    |    very long    |
|  $n=10.000$   | <1 sec |    <1 sec    |  2 min  |   12 days    |  very long   |    very long    |    very long    |
|  $n=100.000$  | <1 sec |    2 sec     | 3 hours |   32 years   |  very long   |    very long    |    very long    |
| $n=1.000.000$ | 1 sec  |    20 sec    | 12 days | 31.710 years |  very long   |    very long    |    very long    |
### Notazione asintotica O 
>$f(n)=O(g(n))$ se $\exists$ due costanti $c>0\ e\ n_{0}\geq 0$ tali che $0\leq f(n) \leq g(n)\quad \forall n \geq n_{0}$.

Quindi:

Sia $f(n)=2n^2+3n$ allora:
- $f(n)=O(n^3)\quad\quad\quad(c=1,n_{0}=3)$
- $f(n)=O(n^2)\quad\quad\quad (c=3,n_{0}=3)$
- $f(n)\not=O(n)$

Dire che $O(n^2)=4n^2+3n$ è un'abuso di notazione, si dovrebbe scrivere $4n^2+3n \in O(n^2)$.
Inoltre, se:$$\lim_{ n \to \infty  }\frac{f(n)}{g(n)}=0 \implies f(n)=O(g(n)) $$
Ma:$$\begin{array}{}
\displaystyle f(n)=O(g(n)) \centernot\implies\lim_{ n \to \infty } \frac{f(n)}{g(n)}=0 \\
\displaystyle f(n)=O(g(n)) \to \lim_{ n \to \infty } \frac{f(n)}{g(n)} < \infty \text{ (se esiste) }
\end{array}$$
### Notazione asintotica $\Omega$
>Sia $f(n)=\Omega(g(n))\text{ se } \exists\ c>0\ \ e\ \ n_{0}\geq 0\ |\ f(n) \geq c\cdot g(n) \geq 0\text{ per ogni }n\geq n_{0}$.

Sia $f(n)=2n^2-3n$, allora 
- $f(n)=\Omega(n)\quad\quad\quad(c=1,n_{0}=2)$
- $f(n)=\Omega(n^2)\quad\quad\quad(c=1,n_{0}=3)$
- $f(n)\neq\Omega(n^3)$

Inoltre:$$\begin{array}{}
\displaystyle \lim_{ n \to \infty  }\frac{f(n)}{g(n)}=\infty \implies f(n)=\Omega (g(n)) \\
\displaystyle f(n)=\Omega(g(n)) \centernot\implies \lim_{ n \to \infty  }\frac{f(n)}{g(n)}= \infty \\
\displaystyle f(n)=\Omega(g(n)) \implies \lim_{ n \to \infty  }\frac{f(n)}{g(n)} > 0 \text{ (se esiste) }
\end{array}$$
### Notazione asintotica $\Theta$
>$f(n)=\Theta (g(n))$ se $\exists$ tre costanti $c_{1}, c_{2} > 0$ e $n_{0}\geq 0$ tali che $c_{1}\cdot g(n) \leq f(n) \leq c_{2}\cdot g(n)$ per ogni $n\geq n_{0}$.

Ad esempio data $f(n)=2n^2-3n$ allora:
- $f(n)=\Theta(n^2)\quad\quad\quad (c_{1}=1,c_{2}=2,n_{0}=3)$
- $f(n)\not=\Theta(n)$
- $f(n)\not=\Theta(n^3)$

Inoltre:$$\begin{array}{}
f(n)=\Theta(g(n)) &  \overset{\text{non il contrario} }{\implies} & f(n)=O(g(n)) \\
f(n)=\Theta(g(n)) &  \overset{\text{non il contrario} }{\implies} & f(n)=\Omega(g(n)) \\
 & \text{ma} \\
f(n)=\Theta(g(n))  & \iff & f(n)=O(g(n))\ \ e\ \ f(n)=\Omega(g(n))
\end{array}$$
Infine, per studiare matematicamente meglio le funzioni, abbiamo anche che:$$\begin{array}{}
\displaystyle \text{Se } \lim_{ n \to \infty } \frac{f(n)}{g(n)}=c>0 \text{ allora } f(n)=\Theta(g(n))
\end{array}$$

### Notazione asintotica o
>Data la funzione $g(n: N\to R)$, si denota con $o(g(n))$ l'insieme di funzioni $f(n): N \to R$:$$o(g(n))=\{f(n): \forall\ c > 0,\ \exists\ n_{0}\ \ tale\ che\ \ \forall\ n \geq n_{0}\ \ e\ \ 0 \leq f(n) < c \cdot g(n)\}$$
Definizione alternativa:$$f(n)=\omega(g(n)) \iff \lim_{ n \to \infty } \frac{f(n)}{g(n)}= \infty $$
### Notazione asintotica $\omega$
>Data una funzione $g(n): N \to R$ si denota con $\omega (g(n))$ l'insieme delle funzioni f(n):$$\begin{array}{}
\omega(g(n))= \{f(n): \forall\ c > 0\ \exists\ n_{0}\ tale\ che\ \forall\ n \geq n_{0}\quad 0 \leq c \cdot g(n)< f(n) \} \\
 \\
\omega(g(n)) \subset \Omega (g(n))
\end{array}$$
Definizione alternativa:$$f(n)=\omega(g(n)) \iff \lim_{ n \to \infty } \frac{f(n)}{g(n)}= \infty $$
### Proprietà della notazione asintotica
Proprietà transitive:
$$\begin{matrix}
f(n)=\Theta(g(n)) & e & g(n)=\Theta(h(n)) & \implies & f(n)=\Theta(h(n)) \\
f(n)=O(g(n)) & e & g(n)=O(h(n)) & \implies & f(n)=O(h(n)) \\
f(n)=\Omega(g(n)) & e & g(n)=\Omega(h(n)) & \implies & f(n)=\Omega(h(n)) \\
f(n)=o(g(n)) & e & g(n)=o(h(n)) & \implies & f(n)=o(h(n)) \\
f(n)=\omega(g(n)) & e & g(n)=\omega(h(n)) & \implies & f(n)=\omega(h(n))
\end{matrix}$$
Proprietà riflessive:
$$\begin{array}{}
f(n)=\Theta(f(n)) \\
f(n)=O(f(n)) \\
f(n)=\Omega(f(n))
\end{array}$$
Proprietà simmetriche:
$$\begin{array}{}
f(n)=\Theta(g(n)) & \iff & g(n)=\Theta(f(n))
\end{array}$$
Proprietà di simmetria trasposta:
$$\begin{array}{}
f(n)=O(g(n)) & \iff & g(n)=\Omega(f(n)) \\
f(n)=o(g(n)) & \iff & g(n)=\omega(f(n))
\end{array}$$
### Velocità delle funzioni composte
Per una funzione composta lineare (cioè $f(n) + g(n)$), l'intera funzione è veloce quanto la più veloce tra le sotto-funzioni.

La velocità ad andare a infinito della funzione $f(n)\cdot g(n)$ e la velocità di f(n) “più” la velocità di g(n). La velocità ad andare a infinito della funzione $\frac{f(n)}{g(n)}$ e la velocità di f(n) “meno” la velocità di g(n).