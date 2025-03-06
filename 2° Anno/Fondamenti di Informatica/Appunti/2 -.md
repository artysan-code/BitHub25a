## Descrizione di un programma
$\Sigma$ e' un insieme finito di caratteri e tipicamente non contiene il simbolo $\Box$ (cella vuota)
Q e' l'insieme degli stati
$q_{0}$ e' lo stato iniziale
$Q_{F}$ l'insieme degli stati finali
P e' l'insieme delle quintuple

$T= <\Sigma,Q,q_{0},Q_{F},P>$
$q_{0}\in Q$
$Q_{F}\subseteq Q$
$P\subseteq (Q\times \Sigma\ \cup \{\Box\}\times\Sigma\ \cup \{\Box\}\times Q\times\{S,F,D\})$
E' la macchina di Turing se $\forall\ q\in Q\in\Sigma\ [\forall\  b,c\in\Sigma\ \forall \ q',q''\in Q:b\not= c \lor q'\not=q'' \lor  m'\not=m''[<q,a,b,q',m'>\not\in P \lor <q,a,c,q'',m''>\not\in P]]$
###### Esempio
$Q=\{q_{0},q_{1},q_{2}\}$
$\Sigma=\{0,1\}$

$<q_{0},0,0,q_{1},D>$
$<q_{0},0,1,q_{1},D>$
---

In ogni quintupla ad ogni condizione c'e' un azione chiamata **funzione di transizione**:
$\delta:Q\times\Sigma\to\Sigma \times Q\times\{S,F,D\}$

...immagine...

cerca una quintupla
$<q_{0},x_{1},a,q_{1},D>$

###### Esempio
data una parola binaria $x$
Vogliamo progettare una macchina di Turing che termina in $q_{P}$ se $x$ contiene un numero pari di 1, termina in $Q_{}d$ se x  contiene un numero dispari di 1

$\Sigma=\{0,1\}$
$Q=\{q_{0},q_{P},q_{D}$
scriviamo le quintuple

Ricordiamo che $\epsilon$ e' il simbolo di cella vuota
$<q_{0},0,0,q_{P},D>$
$<q_{0},1,1,q_{D},D>$
$<q_{0},\epsilon,\epsilon,q_{f},F>$

$<q_{P},0,0,q_{P},D>$
$<q_{P},1,1,q_{D},D>$
$<q_{P},\epsilon,\epsilon,q_{P},F>$

$<q_{D},0,0,q_{D},D>$
$<q_{D},1,1,q_{P},D>$
$<q_{D},\epsilon,\epsilon,q_{D},F>$

Se abbiamo uno stato finale, nessuna quintupla può iniziare con esso quindi aggiungo uno stato
$Q=\{q_{0},q_{P},q_{D},q_{1}\}$

$<q_{0},0,0,q_{0},D>$
$<q_{0},1,1,q_{1},D>$
$<q_{0},\epsilon,\epsilon,q_{P},F>$

$<q_{1},0,q_{1},D>$
$<q_{1},1,1,q_{0},D>$
$<q_{1},\epsilon,\epsilon,q_{D},F>$

$Q$ e $\Sigma$ si possono ricavare una volta che si hanno tutte le quintuple

## Macchine a più nastri
Una quintupla in una macchina a $k$ nastri
$P=Q\times(\Sigma\cup \{\square\})^{k}\times Q\times(S,F,D)^{k}$

macchina che ha 2 nastri
sul primo nastro ci sono addendi con lo stesso numero di cifre
sul secondo nastro la macchina scrive il risultato

...immagine...

|     | 9   | 5   | 4   | +   | 3   | 6   | 8   |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |     |     |     |     |     |     |     |     |     |

$<q_{0},(a,\epsilon),(a,\epsilon),q_{0},0,(D,F)>$ $\forall a\in\{0,9\}$
$<q_{0},(+,\epsilon),(+,\epsilon),q_{1},(S,F)>$
$<q_{1},(a,\epsilon),(+,\epsilon),q_{a}^{0},(D,F)>$ $\forall a\in\{0,9\}$
$<q_{a}^{0},(s,\epsilon),(s,\epsilon),q_{a}^{0},(D,F)>$ $\forall a\in\{0,9,+\}$
$<q_{a}^{0},(\epsilon,\epsilon),(\epsilon,\epsilon),\overline q_{a}^{0},(S,F)>$ $\forall a\in\{0,9\}$
$<\overline q_{a}^{0},(8,\epsilon),(\epsilon,2),q^{1},(S,S)>$
$<q^{1},(a,\epsilon),(a,\epsilon),q^{1},(S,F)>$
$<q^{1},(+,\epsilon),(+,\epsilon),\overline q^{1},(S,F)>$
$<\overline q^{1},(+,\epsilon),(+,\epsilon),\overline q_{1},(S,F)>$
$<\overline q_{1},(a,\epsilon),(+,\epsilon),q_{a}^{1},(D,F)>$
$<\overline q^{1},(\epsilon,\epsilon),(\epsilon,1),q_{F},(F,F)>$
$<\overline q^{0},(\epsilon,\epsilon),(\epsilon,\epsilon),q_{F},(F,F)>$

Vedere il caso di 2 addenti con cifre diverse

---
$\Sigma^*$ sono tutte le parole (combinazioni dei caratteri)

### STATO GLOBALE
informalmente e' una fotografia della macchina ad un certo istante
rappresenta stato interno, posizione testina e contenuto del nastro

... immagine ...

$+\Box+q_{4}^{0}+368$

Uno stato globale e' iniziale quando e' della forma 
$q_{0}abcd$

Uno stato globale e' finale quando lo stato interno e' uno stato finale
### Transizione
Avviene tra due stati globali 
$SG_{1}\to SG_{2}\quad\quad SG_{1}$ non e' SG finale
$aqad$
$q\in Q,a\in\Sigma \land \exists<q,a,b,q',S>\land\ SG_{2}\text{ contiene }q'cbd$


### Computazione
L'esecuzione di una macchina di Turing su un certo input e' una computazione
E' una successione di stati globali collegati da transizioni
$SG_{0}\to SG_{1}\to SG_{2}\to \dots\to SG_{F}$
$SG_{0}\to SG_{1}\to SG_{2}\to \dots\to$             (loop o stato in cui non può eseguire nessuna quintupla)

----

Esistono 2 tipi di Macchine di Turing:
Macchine di Turing di tipo trasduttore:
	hanno un nastro particolare usato solo per l'output
	hanno un solo stato finale chiamato $Q_{F}$
Macchine di Turing di tipo riconoscitore:
	sanno calcolare solo ... di tipo booleane
	il risultato lo esprimono nello stato finale ()
	tipicamente $q_{A},q_{R}$ (quasi sempre queste nel corso)