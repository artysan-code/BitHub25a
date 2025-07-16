	[[4 - Metodo dell'iterazione e Albero di ricorsione|Torna alla lezione precedente]]
[[6 - Algoritmi di Ordinamento|Continua alla lezione successiva]]
Vi sono diverse metodologie per studiare e risolvere le equazioni di ricorrenza, tra questi tratteremo:
- [[4 - Metodo dell'iterazione e Albero di ricorsione#^40e417|Metodo dell'Iterazione]]
- [[4 - Metodo dell'iterazione e Albero di ricorsione#^dbadd5|Albero della ricorsione]]
- [[5 - Metodi di risoluzione equazioni ricorrenza#^5d7100|Metodo della sostituzione]]
- [[5 - Metodi di risoluzione equazioni ricorrenza#^ea5acf|Teorema Master]]
- [[5 - Metodi di risoluzione equazioni ricorrenza#^87cfb5|Cambiamento di Variabile]]
### Metodo della sostituzione

^5d7100

Il metodo è basato su due passi fondamentali:
- "Indovinare" la forma della soluzione.
- Usare l'induzione matematica per provare che la soluzione è quella intuita.

Esempio:$$T(n)=n+T\left( \frac{n}{2} \right),\quad T(1)=1$$
Possiamo pensare che tenda a $T(n)=n\log_{2}(n)$ oppure $T(n)=n$ ma supponiamo di scegliere il secondo. Ora proviamo a dimostrare che $T(n)\leq c\cdot n$:$$\begin{array}{l}
\text{Passo base: } & T(1)=1 \leq c \cdot 1 \quad \forall\ c \geq 1 \\
\text{Passo induttivo: } \\
\text{Assumo che } T(k) \leq c \cdot k\quad \forall\ k<n \\
\displaystyle T(n)=n+T\left( \frac{n}{2} \right)\leq n+c \cdot \left( \frac{n}{2} \right) \implies T(n)=\left( \frac{c}{2} +1\right)n \\
\end{array}$$
Quindi abbiamo che:$$\left( \frac{c}{2}+1 \right) \leq c \implies c \geq 2 \quad\quad quindi\quad\quad T(n)\leq 2n \implies T(n)=O(n) $$


### Divide et Impera
Gli algoritmi basati sul **divide et impera** sono descrivibili in semplici step:
- Dividi il problema (di dimensione *n*) in *a* sotto-problemi di dimensione $\displaystyle\frac{n}{b}$.
- Risolvi i sotto-problemi ricorsivamente.
- Riunisci le soluzioni.

Dato $f(n)$, cioè il tempo per dividere e ricombinare istanze di dimensione n, allora la **relazione di ricorrenza** è la seguente:$$T(n)=\begin{cases}
a\cdot T\left( \frac{n}{b} \right)+ f(n) & \text{se}\ \ n>1 \\
\Theta(1) & \text{se}\ \ n=1
\end{cases}$$
### Metodo del Teorema Master
^ea5acf
Da ciò imparato precedentemente:
$$T(n)=\begin{cases}
a\cdot T\left( \frac{n}{b} \right)+ f(n) & \text{se}\ \ n>1 \\
\Theta(1) & \text{se}\ \ n=1
\end{cases}$$
Analizzando quindi relazione di ricorrenza, possiamo imporre una "lotta" tra $\displaystyle n^{\log_{b}(a)}$ e $f(n)$. Quindi:
- Se sono dello stesso ordine asintotico allora $T(n)=\Theta(f(n)\log (n))$
- Se una delle due è più veloce, allora $T(n)$ tende ad essa.

Analizzando più affondo possiamo dire che possono esserci quindi **tre soluzioni**:
- $\displaystyle  T(n)=\Theta (n^{\log_{b}(a)})$  se  $\displaystyle f(n)=O(n^{\log_{b}(a-\epsilon)})$ per $\displaystyle \epsilon>0$
- $\displaystyle T(n)=\Theta(n^{\log_{b}(a)\cdot \log(n)})$  se  $\displaystyle f(n)=\Theta(n^{\log_{b}(a)})$
- $\displaystyle T(n)=\Theta(f(n))$  se  $\displaystyle f(n)=\Omega(n^{\log_{b}(a+\epsilon)})$ per $\displaystyle \epsilon>0$ e $\displaystyle \forall\ f\left( \frac{n}{b} \right) \leq c \cdot f(n)$ per $c<1$ e $n$ sufficientemente grande

### Metodo del cambiamento di variabile
^87cfb5
![[l51.png]]