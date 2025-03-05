Chi deve dare modulo 1 contattare Gambosi
Chi deve dare modulo 2 solo esame

voto esame scritto:
<15 bocciato
15-17 orale
18-24 non obbligatori orale
\>25 orale non necessario ma voto finale =24


## Problemi risolti automaticamente

>Definizione **problema**
>e' la descrizione di un insieme di oggetti tra i quali sussiste una relazione e un altro insieme di oggetti tra i quali sussiste una relazione tra i due

Somma: dati 2 interi $n$ e $k$, trovare un terzo intero $s$ tale che $s=n+k$

trovare la somma di 3+2 e' trovare la soluzione di un istanza di somma
(3,2) = istanza

>**Risolvere** un problema
trovare un metodo che mi permette di associare ad ogni istanza una soluzione

(789437217455, 6789678954321)

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

poche = deve essere indipendente dall'istanza del problema (deve essere costante)
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
