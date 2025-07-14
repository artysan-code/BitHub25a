## Problema
>Un **problema** è la descrizione di un insieme di parametri che chiamiamo **dati**, tra i quali sussiste un certo insieme di relazioni da cui si vogliono derivare un altro insieme di parametri che corrisponderà successivamente alla **soluzione**.

Vi è una precisa differenza tra istanze di problema e il problema stesso, un esempio lo possiamo avere con la *somma*:

**Problema**: Dati due numeri naturali, n e k, calcolare il valore della somma di n con k (ossia, n + k).
**Istanza di un problema**: Calcolare il valore di 2 + 7.

L'*istanza di un problema* è un'insieme di valori associati ai dati parametri del problema. Risolvere un'istanza può essere fatto sfruttando le caratteristiche del problema, ma non sempre è possibile:

Calcolare $2+7$ è semplice, mentre calcolare $\sqrt{ 2 }$ può essere notevolmente difficile, ma esistono anche casi in cui non è possibile calcolare un'istanza (ad esempio $\sqrt{ -4 }$). Queste istanze sono chiamate **istanze negative**, e saranno fondamentali.

> Per **risolvere** un problema corrisponde ad individuare un metodo che mi permette di associare ad ogni istanza una soluzione, ovvero data una qualunque istanza indicare la sequenza di azioni per trovare una soluzione.

Ciò implica ovviamente riconoscere se un'istanza è negativa. Iniziamo quindi a porre le definizioni di questo processo.
## Procedimento
>Un **procedimento** un'insieme di azioni di cui viene specificato l'ordine in cui eseguirle.

Quindi un'**azione** corrisponde ad una *istruzione* semplice da eseguire, ad esempio:

Data una funzione $f: ℝ → ℝ+$ e dati due numeri reali $a$ e $b$, calcolare la misura dell’area della regione di piano compresa fra la funzione, l’asse x e le rette $y=a$ e $y=b$.

PROCEDIMENTO: 
1) Calcola la funzione primitiva $F(x)$ di $f(x)$
2) Calcola $F(b)\ –\ F(a)$

Ma cos'è un'istruzione semplice... un'**istruzione elementare**? Beh dipende da chi deve eseguirle.

>**Istruzione elementare** è descrivibile (secondo Turing) in questa maniera:
> 1) deve essere scelta in un insieme di *"poche" istruzioni possibili*.
> 2) deve scegliere l’azione da eseguire all'interno di un insieme di *"poche" azioni possibili*.
> 3) deve poter essere eseguita ricordando una quantità limitata di dati, ossia, in termini
    più tecnici, utilizzando *"poca" memoria*.

Potremmo pensare che sommare due numeri (Quindi il *problema della somma*) sia semplice, lo sappiamo fare dalle elementari. In realtà no, dovrei memorizzare una tabellina di dimensioni infinite, in quanto i numeri sono infiniti.

Invece di inventarci una enorme tabella, usiamo un *procedimento*.

1) mi posiziono alla coppia di cifre più a destra e definisco $r=0$.
2) fino a quando leggi una coppia di cifre, esegui la somma della coppia di cifre sulle quali sei posizionato, aggiungi $r$ a tale valore e scrivi una cifra del risultato calcolando anche il nuovo valore di $r$, e poi spostati a sinistra – ossia:
	1) se r = 0 e le due cifre sono 0 e 0, allora scrivi 0, poni $r = 0$, e spostati di una posizione a sinistra.
	2) se r = 1 e le due cifre sono 0 e 0 e allora scrivi 1, poni $r = 0$, e spostati di una posizione a sinistra.
	3) ...
	4) se r = 0 e le due cifre sono 9 e 9, allora scrivi 8, poni $r = 1$,e spostati di una posizione a sinistra.
	5) se r = 1 e le due cifre sono 9 e 9, allora scrivi 9, poni $r = 1$, e spostati di una posizione a sinistra.
3) \[ ... continua ... \]

Dunque eseguirò l'unica azione a me possibile fino a quando non arriverò ad un istruzione che mi dice di terminare, quindi saranno una serie di **se** e **allora**. L'istruzione è composta da due parti: condizione e azione:
- "$r=0$ e leggo le due cifre 0 e 0" è una **condizione**.
- "scrivo 0, pongo $r =0$ e mi sposto a sinistra" è una **azione**.

Le condizioni sono alla base delle istruzioni, una istruzione normale ti dice *per ogni condizione possibile esegui...*; anche l'ordine è dato dalle frasi "se allora".

Queste istruzioni possono essere eseguite da chiunque è capace di leggere (e scrivere) anche se non conosce i concetti. Quindi alla fine dell'esecuzione sara completato in modo "automatico" nonostante non si abbia la conoscenza della somma; il risultato verrà da solo.

## Un nuovo Linguaggio
Iniziamo però a scrivere in maniera formale le cose, usando un **linguaggio nuovo**. Ad esempio:

L'istruzione "$\text{se }r=0\text{ e le due cifre sono 4 e 6 allora scrivi 0, poni }r=1\text{ e spostati a sinitra}$" diventa:  $$<q_{0},(4,6),0,q_{1},S>$$

Oppure "$\text{se }r=1\text{ e l’unica cifra è 5, allora scrivi 6, poni }r=0\text{, e spostati di una posizione a sinistra}$" diventa:$$<q_{1},\ (5,\ \Box),\ 6,\ q_{0},\ S >$$
dove il simbolo $\Box$ indica che non viene letto o scritto nulla.

Per riscrivere il nostro programma in maniera più compatta:$$\begin{array}{}
\text{se }r=1\text{ e le cifre di entrambi i numeri sono terminate, allora scrivi 1 e termina} \\
\text{se }r=0\text{ e le cifre di entrambi i numeri sono terminate, allora termina.} \\
 \\
<q_{1},\ (\Box,\ \Box),\ 1, q_{f},\ fermo> \\
<q_{0},\ (\Box,\ \Box),\ \Box, q_{f},\ fermo>
\end{array}$$
dove $q_{f}$ è lo *stato inferiore* o propriamente **stato interno**, e significa che non bisogna tornare indietro, rafforzato poi dal *fermo*. Iniziamo ad immaginare quindi l'esecuzione come una *macchina robotizzata*, che ha delle testine di lettura/scrittura che lavorano su dei *nastri*. Questi ultimi possono avere valori o $\Box$ e a prescindere dall'operazione, quando l'automa ci passa sopra inizia a **computare**, cioè eseguire le quintuple del procedimento.

L'istruzione che ritroviamo qui sopra è una **quintupla**. L'esecuzione di una quintupla su un set di dati è chiamato **computazione**.

La macchina di Turing serve a risolvere automaticamente un problema.

![[l11.png|600]]

L'insieme di queste 250 istruzioni costituisce la **macchina di Turing** (indicata con $\text{T}_{somma\_in\_ colonna}$) ed è un programma scritto in linguaggio macchina.$$\begin{array}{}
<\text{stato iniziale, lettura, scrittura, stato finale, spostamento}>\\
<q_{0},\ (9,\ 5,\ \Box),\ (9,\ 5,\ 4),\ q_{1},\ (s,\ s,\ s)>
\end{array}$$
>**Ricorda**:
	Macchina di Turing  = Linguaggio di programmazione
	macchina di Turing = serie di istruzioni
