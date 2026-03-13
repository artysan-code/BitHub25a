$L_{2}^1=\{x\in\{0,1\}^*:\text{x contiene un numero pari di 1}\}\implies T_{2}^1$
$L_{3}^0=\{x\in\{0,1\}^*:\text{x contiene un multiplo di 3 di 0}\}\implies T_{3}^0$

$L_{6}^1=\{x\in{0,1}^*:\text{x contiene un multiplo di 6 di 1}\}\implies T_{6}^1$

Osserviamo che il numero di 1 è multiplo di 6 se:
- È multiplo di 2 (è pari)
- È multiplo di 3

$T_{6}^1:\text{input}x\in \{0,1\}^*\text{ su }n_{1}$:
1) Copia x su $n_{2}$
2) Copia $x^c$ su $n_{3}$
3) $q=T_{2}^1(n_{2})$, se $q=q_{a}$ allora fase 4), se $q=q_{r}$ allora termina in $q_{r}$
4) $q=T_{3}^0(n_{3})$, se $q=q_{a}$ allora termina in $q_{a}$ altrimenti termina in $q_{r}$
