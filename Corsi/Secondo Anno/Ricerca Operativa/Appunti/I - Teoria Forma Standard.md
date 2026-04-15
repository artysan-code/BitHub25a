Un qualsiasi problema di programmazione lineare può essere portato in forma standard:
$$\begin{array}{}
min\quad c_{1}x_{1}+c_{2}x_{2}+\ldots+c_{n}x_{n} \\
a_{i}x_{1}+a_{i2}x_{2}+\ldots+a_{in}x_{n}=b_{i}
\end{array}$$
dove:
1. la funzione obiettivo è di minimo e senza costanti additive o moltiplicative
	- le funzioni di massimizzazione si moltiplicano per -1
	- si trascurano le costanti additive e moltiplicative
	- le costanti moltiplicative possono essere eliminate cambiando il verso di ottimizzazione
2. tutte le variabili sono positive o nulle
	- effettuiamo sostituzioni di variabili per le variabili libere o negative
3. tutti i vincoli sono delle equazioni
	- aggiungiamo una variabile di slack per i vincoli $\leq$
	- sottraiamo una variabile di surplus per i vincoli $\geq$
4. i termini noti $b_{i}$ sono positivi o nulli
	- si moltiplicano per -1 i vincoli con termine noto negativo

Questi passaggi permettono, senza perdere in generalità, di risolvere qualsiasi problema di PL tramite sistemi di equazioni lineari.

[[I - Esercizi svolti Forma standard|Esercizi esempio]]

[[II - SBA Esempio spiegazione|Prossimo Argomento]]