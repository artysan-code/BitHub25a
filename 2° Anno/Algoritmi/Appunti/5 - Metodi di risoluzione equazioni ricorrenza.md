Vi sono diverse metodologie per studiare e risolvere le equazioni di ricorrenza, tra questi tratteremo:
- [[4 - Metodo dello Srotolamento e Albero di ricorsione#^40e417|Metodo dell'Iterazione]]
- [[4 - Metodo dello Srotolamento e Albero di ricorsione#^dbadd5|Albero della ricorsione]]
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
T(n)=n+T\left( \frac{n}{2} \right)\leq n+c \cdot \left( \frac{n}{2} \right) \implies T(n)=\left( \frac{c}{2} +1\right)n \\
\end{array}$$
Quindi abbiamo che:$$\left( \frac{c}{2}+1 \right) \leq c \implies c \geq 2 \quad\quad quindi\quad\quad T(n)\leq 2n \implies T(n)=O(n) $$


### Metodo del Teorema Master

^ea5acf
#### Divide et Impera

### Metodo del cambiamento di variabile

^87cfb5
