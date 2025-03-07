>Un **problema** è la descrizione di un insieme di parametri che chiamiamo **dati**, tra i quali sussiste un certo insieme di relazioni da cui si vogliono derivare un altro insieme di parametri che corrisponderà successivamente alla **soluzione**.

Vi è una precisa differenza tra istanze di problema e il problema stesso, un esempio lo possiamo avere con la *somma*:

**Problema**: Dati due numeri naturali, n e k, calcolare il valore della somma di n con k (ossia, n + k).
**Istanza di un problema**: Calcolare il valore di 2 + 7.

L'*istanza di un problema* è un'insieme di valori associati ai dati parametri del problema. Risolvere un'istanza può essere fatto sfruttando le caratteristiche del problema, ma non sempre è possibile:

Calcolare $2+7$ è semplice, mentre calcolare $\sqrt{ 2 }$ può essere notevolmente difficile, ma esistono anche casi in cui non è possibile calcolare un'istanza (ad esempio $\sqrt{ -4 }$). Queste istanze sono chiamate **istanze negative**, e saranno fondamentali.

> Per **risolvere** un problema corrisponde ad individuare un metodo che mi permette di associare ad ogni istanza una soluzione, ovvero data una qualunque istanza indicare la sequenza di azioni per trovare una soluzione.

Ciò implica ovviamente riconoscere se un'istanza è negativa.


>Definizione **procedimento**
il procedimento specifica le istruzioni da eseguire e l'ordine in cui eseguirle

Radice quadrata: data $x$ trovare $\sqrt{ x }$ 
$\sqrt{ -1 }$

Calcolare l'area della regione piana compresa fra $x=0,\ x=1,\ y=0,\ y=f(x)$:
1) calcolare la primitiva $F$ di $f$
2) $sol=F(1)-F(0)$

>Da cosa dipende elementare:
dipende da chi risolve il problema

>**Istruzione elementare**(secondo Turing):
>1) Un istruzione e' elementare se la scelgo in un insieme di piccole dimensioni(*"poche" istruzioni possibili*)
>2) *"poche" azioni possibili*
>3) Ogni istruzione può essere eseguita ricordando "poche" cose (*"poca" memoria*)

somma di 2 numeri e' semplice? 
No, dovrei memorizzare una tabellina di dimensioni infinite (volendo sommare 2 numeri qualunque)

**poche** = deve essere indipendente dall'istanza del problema (deve essere costante)
$$\begin{array}{r}
7854321\ + \\
663959\ = \\
\hline \\

\end{array}$$

leggo prima cifra della colonna
leggo seconda cifra della colonna
se r=0 e leggo  (0,0) allora scrivo 0, pongo r =0 e mi sposto a sinistra
(tutte le possibili casistiche)
quindi abbiamo $100*2$ istruzioni =200 + le casistiche delle somme di valori ad inesistente ($9*2$=18) e la somma di due valori inesistenti
se r=0 e leggo ($\Box,\Box$) allora scrivo $\Box$ e termino

Dunque eseguirò l'unica azione a me possibile fino a quando non arriverò ad un istruzione che mi dice di terminare, quindi saranno una serie di **se** e **allora**.

(r=0 e leggo  (0,0)) = condizione 
(scrivo 0, pongo r =0 e mi sposto a sinistra) = azione
l'istruzione e' composta da due parti:
condizione e azione

Ad ogni condizione corrisponde un azione

Se vengono soddisfatte due condizioni uguali vengono anche eseguite entrambe le azioni

Queste istruzioni possono essere eseguite da chiunque e' capace di leggere (e scrivere) anche se non conosce i concetti
Quindi alla fine dell'esecuzione sara completato in modo "automatico" nonostante non si abbia la conoscenza della somma; il risultato verrà da solo.

Pero scrivere tutto questo e' stancante quindi definiamo 
$<q_{0},(9,5),4,q_{1},S>$
$q_{1}$


La macchina di Turing serve a risolvere automaticamente un problema

![[l11.png|600]]

l'insieme di queste 250 istruzioni costituisce la **macchina di Turing** (indicata con $\text{T}_{sommaincolonna}$) ed e' un programma scritto in linguaggio macchina
<$q_{0}$,(9,5,$\Box$),(9,5,4),$q_{1}$,(s,s,s,)>
<stato iniziale, lettura, scrittura, stato finale, spostamento>

Macchina di Turing  = Linguaggio di programmazione
macchina di Turing = serie di istruzioni
