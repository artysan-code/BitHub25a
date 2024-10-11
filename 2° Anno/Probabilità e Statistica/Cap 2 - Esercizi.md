## Esercizio
Gli elementi prodotti da una fabbrica possono avere due tipi di difetti:
- il difetto 1 con probabilità $\frac{3}{100}$;
- il difetto 2 con probabilità $\frac{7}{100}$

La presenza dei due difetti può essere considerata indipendente l'una dall'altra.
Si sceglie un elemento prodotto a caso.
1) Calcolare la probabilità che siano presenti entrambi i difetti.
2) Calcolare la probabilità che l'elemento sia difettoso (sia presente almeno uno dei due difetti)
3) Calcolare la probabilità che l'elemento abbia il difetto 1 sapendo che è difettoso
4) Calcolare la probabilità che l'elemento abbia un solo difetto sapendo che è difettoso

**Svolgimento**
Introduciamo le seguenti notazioni:$$D_{k}=\{\text{l'elemento ha il difetto }k\}\quad\text{con }k=1,2$$
allora $D_1$ e $D_2$ sono indipendenti; inoltre $P(D_{1})=\frac{3}{100}$ e $P(D_{2})=\frac{7}{100}$

1) $P(D_{1}\cap D_{2})=P(D_{1})P(D_{2})=\frac{3}{100}\cdot \frac{7}{100}=\frac{21}{10000}$
   
2) $P(D_{1}\cup D_{2})=P(D_{1})+P(D_{2})-P(D_{1}\cap D_{2})=\frac{3}{100}+\frac{7}{100}-\frac{21}{10000}=\frac{979}{10000}$
   
   Metodo alternativo
   $P(D_{1}\cup D_{2})=1-P((D_{1}\cup D_{2})^{c})=1-P(D_{1}^{c}\cap D_{2}^{c})=1-P(D_{1}^{c})P(D_{2}^{c})=$
   $=1-\left(1-\frac{3}{100}\right)\left(1-\frac{7}{100}\right)=1-\frac{97\cdot 93}{10000}=\frac{10000-9021}{10000}=\frac{979}{10000}$
   
3) $P(D_{1}|D_{1}\cup D_{2})=\frac{P(D_{1}\cap(D_{1}\cup D_{2}))}{P(D_{1}\cup D_{2})}\overset{D_{1}\subset D_{1}\cup D_{2}}{=}\frac{P(D_{1})}{P(D_{1}\cup D_{2})}=\frac{\frac{3}{100}}{\frac{979}{10000}}=\frac{3}{100}\cdot \frac{10000}{979}=\frac{300}{979}$
   
4) $P(E|D_{1}\cup D_{2})=\frac{P(E\cap(D_{1}\cup D_{2}))}{P(D_{1}\cup D_{2})}\overset{E\subset D_{1}\cup D_{2}}{=}\frac{P(E)}{P(D_{1}\cup D_{2})}\overset{\overset{P(D_{1}\cup D_{2})=P(E)+P(D_{1}\cap D_{2})}{\downarrow}}{=}\frac{P(D_{1}\cup D_{2})-P(D_{1}\cap D_{2})}{P(D_{1}\cup D_{2})}=$
   $=1-\frac{P(D_{1}\cap D_{2})}{P(D_{1}\cup D_{2})}=1-\frac{\frac{21}{10000}}{\frac{979}{10000}}=1-\frac{21}{979}=\frac{979-21}{979}=\frac{958}{979}$

## Esercizio

Un urna ha 3 tipi di monete:
- $n_{1}$ monete con 2 teste
- $n_{2}$ monete con 2 croci
- $n_{3}$ monete con 1 testa e 1 croce

Si sceglie una moneta a caso e si scopre una faccia a caso della moneta ed è testa.
Calcolare la probabilità che l'altra faccia della moneta non scoperta è testa

**Svolgimento**
Introduciamo le seguenti notazioni: $$\begin{array}{l}
T_{1}=\{\text{la faccia scoperta della moneta scelta è testa}\} \\
T_{2}=\{\text{la faccia non scoperta della moneta scelta è testa}\}
\end{array}$$
Viene chiesto di calcolare $P(T_{2}|T_{1})$: Si ha $$P(T_{2}|T_{1})=\frac{P(T_{2}\cap T_{1})}{P(T_{1})}\underset{\downarrow}{=}\frac{P(T_{1}\cap T_{2})}{\sum_{k=1}^{3}P(T_{1}|M_{k})P(M_{k})}=$$
Qui si considera la formula delle probabilità totali a denominatore rispetto alla partizione di eventi $M_{1},M_{2},M_{3}$, dove $M_{i}=\{\text{scelta la moneta di tipo }i\}$

Osservazione
$M_{1}=T_{1}\cap T_{2}$

$$=\frac{\frac{n_{1}}{n_{1}+n_{2}+n_{3}}}{1\cdot\frac{n_{1}}{n_{1}+n_{2}+n_{3}}+0\cdot\frac{n_{2}}{n_{1}+n_{2}+n_{3}}+\frac{1}{2}\cdot \frac{n_{3}}{n_{1}+n_{2}+n_{3}}}=\frac{n_{1}}{n_{1}+0+\frac{n_{3}}{2}}\overset{\times \frac{2}{2}}{=} \frac{2n_{2}}{2n_{1}+n_{3}}$$

Osservazione
Il risultato $P(T_{2}|T_{1})=\frac{2n_{1}}{2n_{1}+n_{3}}$ ha la seguente interpretazione:
è il rapporto tra il "numero di facce testa della moneta del tipo 1" e il "numero di facce testa totali"

## Esercizio (da fare)

--pag 3 pdf lezione 04--

## Esercizio (da fare)

-- pag 4 pdf lezione 04--

## Esercizio (da fare)

-- pag 5 e 6 pdf lezione 04--

## Esercizio (da fare)

-- pag 7 pdf lezione 04--

## Esercizio (da fare)

-- pag 8 pdf lezione 04--