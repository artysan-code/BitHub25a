## Esercizio 1 1/3
Progettare un riconoscitore che prende in input una parola $x$ dall'alfabeto $[a,b]$ termina in $q_{P}$ se e' palindroma e $q_{NP}$ se non e' palindroma 
$x\in \{a,b\}^{*}$
$T_{PPAL}$ che termina in $q_{p}^{p}$ se $x$ e' palindroma e ha lunghezza pari, termina in $q_{NP}^{p}$ altrimenti

Scansione SD (sinistra a destra): 
	*se* leggo $a$ o $b$ *allora* memorizza il carattere, lo cancella e si sposta sul carattere più a destra
	altrimenti termino in $q_{P}^{p}$

Scansione DS (destra a sinistra): 
	*se* il carattere letto e' uguale al carattere memorizzato *allora* lo cancella e si sposta sul primo carattere più a sinistra.
	altrimenti termina in $q_{NP}^{p}$

$<q_{0}^{p},a,\Box,q_{p}^{a},D>$
$<q_{0}^{p},b,\Box,q_{b}^{p},D>$
$<q_{0}^{0},\Box,\Box,q_{PP}^{p},F>$

$<q_{a}^{p},z,z,q_{a}^{p},D>\quad\quad\forall\ z\in\{a,b\}$
$<q_{a}^{p},\Box,\Box,q_{a}^{psin},S>$

$<q_{a}^{psin},a,\Box,q^{psin},S>$
$<q_{a}^{psin},b,b,q_{NPP}^{p},F>$  non palindroma
$<q_{a}^{psin},\Box,\Box,q_{NPP}^{p},F>$   non ha lunghezza pari

## Esercizio 1 2/3
$T_{DPAL}$ che termina in $q_{NP}^{d}$ se $x$ e' palindroma e ha lunghezza dispari, termina in $q_{NDP}^{d}$ altrimenti

$<q_{0}^{p},a,\Box,q_{p}^{a},D>$
$<q_{0}^{p},b,\Box,q_{b}^{p},D>$
$\underline{<q_{0}^{0},\Box,\Box,q_{PP}^{p},F>}$

$<q_{a}^{p},z,z,q_{a}^{p},D>\quad\quad\forall\ z\in\{a,b\}$
$<q_{a}^{p},\Box,\Box,q_{a}^{psin},S>$

$<q_{a}^{psin},a,\Box,q^{psin},S>$
$\underline{<q_{a}^{psin},b,b,q_{NPP}^{p},F>}$  non palindroma
$\underline{<q_{a}^{psin},\Box,\Box,q_{NPP}^{p},F>}$   non ha lunghezza pari

diventa

$<q_{0}^{d},a,\Box,q_{d}^{a},D>$
$<q_{0}^{d},b,\Box,q_{b}^{d},D>$
$<q_{0}^{0},\Box,\Box,q_{NDP}^{d},F>$  palindroma lunghezza pari

$<q_{a}^{d},z,z,q_{a}^{d},D>\quad\quad\forall\ z\in\{a,b\}$
$<q_{a}^{d},\Box,\Box,q_{a}^{dsin},S>$

$<q_{a}^{dsin},a,\Box,q^{dsin},S>$
$<q_{a}^{dsin},b,b,q_{NDP}^{d},F>$  non palindroma
$<q_{a}^{dsin},\Box,\Box,q_{DP}^{d},F>$   ha lunghezza dispari

## Esercizio 1 3/3
$T_{PAL}$ che termina in $q_{p}$ se $x$ e' palindroma, termina in $q_{NP}$ altrimenti

$T_{PAL}$ ha 3 nastri $(N_{1},N_{2},N_{3})$:
	con input su $N_{1}$
	fase 1) 
		copia l'input su $N_{2}$ e $N_{3}$
	fase 2) 
		simula $T_{PPAL}$ su $N_{2}$, *se* $T_{PPAL}$ termina in $q_{PP}^{p}$ *allora* $T_{PAL}$ termina in $q_{P}$, altrimenti fase 3)
	fase 3) 
		simula $T_{DPAL}$ su $N_{3}$, *se*  $T_{DPAL}$ termina in $q_{DP}^{d}$ *allora* $T_{PAL}$ termina in $q_{P}$, altrimenti termina in $q_{NP}$

### Fase 1
$<q_{0},(a,\Box,\Box),(a,a,a),q_{0},(D,D,D)>$
$<q_{0},(b,\Box,\Box),(b,b,b),q_{0},(D,D,D)>$
$<q_{0},(\Box,\Box,\Box),(\Box,\Box,\Box),q_{sin},(S,S,S)>$
$<q_{sin},(\overset{b,b,b}{a,a,a}),//,q_{sin},(S,S,S)>$
$<q_{sin},(\Box,\Box,\Box),(\Box,\Box,\Box),q_{0}^{p},(D,D,D)>$
$<q_{NPP}^{p},(u,j,z),(u,j,z),q_{0}^{d},(F,F,F)>$

### Fase 2

inserire fase 2 normale  e fase 2 da foto
### Fase 3

$<q_{0}^{d},(y,z,a),(y,z,\Box),q_{a}^{d},(F,F,D)>\quad\quad\forall\ y,z\in\{a,b,\Box\}$

## Esercizio 2
progettare una macchina di Turing che somma un numero arbitrario di interi
$785+24+12389+901+1+\dots$

$T_{A+B}$ somma due numeri scritti sul primo nastro separati da "+" scrivendo il risultato sul secondo

$T_{sommatoria}$ input su $N_{1}$ $x_{1}+x_{2}+\dots+x_{n}\quad x_{i}\in\{0,\dots,9\}^{*}$

fase 1)
	scriviamo "0+" su $N_{2}$
fase 2)
	*se* su $N_{1}$ non leggiamo $\Box$ *allora* copiamo a destra del carattere "+" su $N_{2}$ tutti i caratteri di $N_{1}$ a sinistra del "+" o del $\Box$ , cancellandoli e cancellando il "+", altrimenti termina
fase 3) 
	simula $T_{A+B}$ con $N_{2}$ nastro di input e $N_{3}$ di output
	$\to<q_{0}^{a+b},N_{2},N_{3},T_{A+B},(F,F,F)>$
fase 4)
	$N_{2}=\Box,N_{2}=N_{3}"+",N_{3}=\Box$ e torna a fase 2

## Esercizio 3
$T_{2}^{1}$ che con input $x\in\{0,1\}^{*}$ termina in  $q_{A}$ se $x$ contiene un numero pari di 1, terminare in $q_{R}$ altrimenti
$T_{3}^{0}$ che con input $x\in \{0,1\}^{*}$ termina in $q_{A}$ se il numero di 0 in $x$ e' multiplo di 3, terminare in $q_{R}$ altrimenti

Vogliamo progettare $T_{6}^{1}$ ovvero se il numero di 1 e' multiplo di 6 
$T_{6}^{1}$ a 3 nastri con input $x$ su $N_{1}$ 
fase 1)
	copia $x$ su $N_{2}$ e $x^{c}$ (x complemento) su $N_{3}$
fase 2)
	simula $T_{2}^{1}$ su $N_{2}$: *se* termina in $q_{R}$ *allora* $T_{6}^{1}$ termina in $q_{R}$ altrimenti fase 3)
fase 3)
	simula $T_{3}^{0}$ su $N_{3}$: *se* termina in $q_{R}$ *allora* $T_{6}^{1}$ termina in $q_{R}$ altrimenti termina in $q_{a}$