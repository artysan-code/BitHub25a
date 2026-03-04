Un problema è una descrizione di un insieme di oggetti, di alcune relazioni di alcuni di questi oggetti e, date queste relazioni, ci si chiede un ulteriore tipo di oggetto che è correlato ai primi.

Vengono generalmente forniti dei **dati esplici** e deve essere prodotto un insieme ulteriore di **dati implici** che forniscono la soluzione.

Risolvere un problema vuol dire trovare un **procedimento** che data una qualsiasi **istanza** del problema, trova la soluzione (e sa anche quando  si trova in una **istanza negativa**). Generalmente però in molti procedimenti ci sono istanze semplici e istanze più complesse, ma anche istanze che risultano impossibili (**istanze negative di un problema**).

Procedimento $\implies$ **sequenza** di **istruzioni** ciascuna delle quali specifica le **azioni** da compiere ad ogni passo.

Es:
Dato un triangolo rettangolo di lati a e b, trovare il perimetro.

Risposta:$a + b +\sqrt{ a^2+b^2 }$

Questo può risultare un procedimento per noi, ma non per **chiunque**, magari non tutti conoscono il principio di somma, radice, elevazione, etc...

Un procedimento per poter risolvere il problema, deve essere composto da **istruzioni elementari**. L'insieme di istruzioni deve risultare "piccolo", come la quantità di azioni disponibili e anche i dati stessi su cui lavoriamo.

Allora dobbiamo arrivare al concetto di **istruzione elementare**.

Proviamo prima a descrivere però la somma diciamo:
```
a,b
risultato: a + b

se r=0, a=0 e b=0 allora scrivo 0 e r=0 e muovi a sinistra
se r=0 e a=1 e b=0 allora....
```

Sembra molto più complesso di una semplice somma.

Il nulla verrà chiamato d'ora in poi **blank**.

Se cerchiamo di contare le azioni di questo problema allora sappiamo che:
- Vedendo la prima riga lavoriamo sui numeri da 0 a 10 + blank, quindi 11 e moltiplichiamo * 2 perché boh.
- Il numero di istruzioni possibili invece dipende da tutte le possibilità di r, a e b, quindi 2 * 11 * 11.

Quindi l'insieme di azioni e l'insieme di istruzioni è sempre **ben definito** e molto piccolo. Inoltre vengono **tenuti in memoria** 3 spazi per r, a e b.

Le istruzioni risultano essere una sequenza di questo tipo:
```
se <condizioni> allora <azioni> 
```

Però questo impone che ogni istruzione deve essere **leggibile** e **non ambigua**, duplicati o errori di battitura possono impedire il raggiungimento della soluzione.

La sequenza di istruzioni deve essere **autoindotta**, cioè deve eseguire ad ogni passo una sola istruzione e deve poterla eseguire, ad ogni passo quindi esegue l'istruzione con la condizione vera.

Traduciamo queste istruzioni in una maniera più compatta (Una **quintupla**).
```
se r=0 e a1=0 e b1=0 allora scrivi 0 e poni r=0 muoviti a sinistra
<r=0,(0,0),0,r=0,S>
<r=1,(3,4),8,r=0,S> // quasi una quintupla

per accorciare ancora
<q^0,(0,0),0,q^0,s>
<q^1,(0,0),0,q^0,s>

Qualche caso particolare
<q^1,(blank, blank),1,q^f,f>
```

**Macchina di Turing** corrisponde al linguaggio di programmazione, mentre **macchina di turing** corrisponde al programma che abbiamo scritto sopra (l'insieme di quintuple).

Possiamo pensare alla macchina di turning come una scatoletta e un'insieme di nastri, il cui numero può dipendere.

Ogni nastro è composto da **infinite** celle, e all'inizio le celle sono di carattere **blank**.

Su ogni nastro vi è una testina di scrittura che si può muovere a destra e a sinistra oppure rimanere fermo.

La scatola di cui parlavamo prima contiene gli **stati** appunto del procedimento.

(creare qui magari un esempio di somma fatta con matrix in latex)


Una quintupla totale sarebbe:$$<q^0,(4,8,\square),(4,8,2),q^1,(s,s,s)$$

$\Sigma$ è in insieme di simboli chiamato **alfabeto**, e viene definito come $\Sigma=\{0,\dots,9\}$ mai il blank però.

Mentre $\displaystyle\Sigma^*$ corrisponde a tutte le combinazioni (insieme di parole), $\Sigma^*=\{0,01,10,121,\dots\}$.

$\varepsilon$