## Es. (produttoria)
Trovare una formula chiusa per $$\prod_{i=1}^n\prod_{j=1}^n2^i\cdot3^j$$
Calcoliamo prima il prodotto interno $$\prod_{j=1}^n2^i\cdot3^j=2^i\cdot3^1\cdot2^i\cdot3^2\cdot\ldots\cdot2^i\cdot3^n=(2^i)^n\cdot3^{1+2+\ldots+n}=2^{i\cdot n}\cdot3^{\binom{n+1}{2}}$$
Pertanto $$\begin{array}{l}
\displaystyle{\prod_{i=1}^n\prod_{j=1}^n2^i\cdot3^j=\prod_{i=1}^n2^{i\cdot n}\cdot3^{\binom{n+1}{2}}} \\
=2^n\cdot 3^\binom{n+1}{2}\cdot2^{2n}\cdot3^\binom{n+1}{2}\cdot\ldots\cdot 2^{n\cdot n}\cdot3^\binom{n+1}{2} \\
=3^{\binom{n+1}{2}\cdot n}\cdot2^{n+2n+\ldots+n\cdot n} \\
=3^{n\cdot\binom{n+1}{2}}\cdot 2^{n(1+2+\ldots+n)} \\
=3^{n\binom{n+1}{2}}\cdot2^{n\binom{n+1}{2}} \\
=6^{n\binom{n+1}{2}}
\end{array}$$

