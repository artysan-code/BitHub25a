[[8 - Lavoro ed energia|Lezione Precedente]]
# Energia Potenziale e Forze Conservative
Una forza è **conservativa** se il lavoro che compie su un corpo che si sposta da un punto A a un punto B è indipendente dal percorso seguito e dipende solo dai punti iniziale e finale. 
Questo ha una conseguenza fondamentale: il lavoro compiuto da una forza conservativa su un qualsiasi percorso chiuso è nullo. 
Un esempio intuitivo di forza conservativa è la **forza peso**. 
Il lavoro compiuto dalla gravità su un oggetto sollevato e poi riportato alla stessa altezza è sempre zero, indipendentemente dal percorso tortuoso che può aver compiuto l'oggetto. 
La **forza elastica** di una molla è un altro esempio, poiché il lavoro necessario per comprimerla e poi riportarla alla sua posizione di riposo si annulla. 
Al contrario, le forze non conservative, come l'attrito o la resistenza dell'aria, compiono un lavoro che dipende fortemente dal percorso. 
Più lungo è il tragitto, maggiore è il lavoro svolto dalla forza d'attrito per dissipare energia.

Per ogni forza conservativa, è possibile definire una funzione scalare chiamata **energia potenziale** ($U$), che dipende solo dalla posizione del corpo. 
La sua importanza risiede nel fatto che il lavoro ($W$) compiuto da una forza conservativa è uguale all'opposto della variazione di energia potenziale del sistema:$$W=U_{i}-U_{f}​=-\Delta U$$

L'unità di misura dell'energia potenziale è il Joule ($J$). 
È importante notare che l'energia potenziale è definita a meno di una costante arbitraria. 
Non è il valore assoluto di $U$ ad avere un significato fisico, ma la sua variazione $\Delta U$, che corrisponde direttamente al lavoro compiuto dalla forza. 
Questa libertà di scelta permette di definire un livello di riferimento convenzionale dove l'energia potenziale è zero, semplificando i calcoli.

L'**energia meccanica totale** ($E_{m}$​) di un sistema è la somma dell'energia cinetica ($K$) e dell'energia potenziale ($U$). 
In un sistema in cui agiscono solo forze conservative, l'energia meccanica si conserva, cioè rimane costante nel tempo. 
Questo principio di conservazione è uno dei più potenti della fisica e permette di risolvere molti problemi di dinamica senza dover ricorrere alle complesse integrazioni della seconda legge di Newton.$$E_{m}​=K+U=\text{costante}$$Quando agiscono anche forze non conservative, come l'attrito, una parte dell'energia meccanica viene dissipata. 
In questo caso, il lavoro totale di queste forze è uguale alla variazione dell'energia meccanica del sistema. 
L'energia totale dell'universo, compresa l'energia termica e altre forme, si conserva comunque.

**Esempi di Energie Potenziali:**
- **Energia potenziale gravitazionale** ($U_{p}$​): Associata alla forza peso. 
  È l'energia immagazzinata da un corpo a causa della sua posizione in un campo gravitazionale. Dipende dall'altezza y del corpo rispetto a un livello di riferimento (spesso il suolo).$$U_{p}​(y)=mgy$$Se un oggetto viene sollevato, il lavoro compiuto contro la gravità viene immagazzinato come energia potenziale. 
  Se l'oggetto viene lasciato cadere, questa energia potenziale si converte in energia cinetica.
- **Energia potenziale elastica** ($U_{el}​$): Associata alla forza elastica di una molla di costante $k$. 
  Rappresenta l'energia immagazzinata in un sistema elastico, come una molla compressa o estesa.
  Dipende dalla deformazione x della molla rispetto alla sua posizione di riposo (dove $x=0$).$$U_{el}​(x)=\frac{1}{2}kx^{2}$$Questo tipo di energia è alla base del funzionamento di molti dispositivi meccanici, come gli orologi a molla e gli ammortizzatori.
# Equilibrio e Punti di Inversione
La relazione tra una forza conservativa e la sua energia potenziale è data dal gradiente negativo della funzione di energia potenziale. Questa relazione è una delle più importanti della dinamica:$$\vec{F}=-\vec{\nabla} U$$Nel caso unidimensionale, dove la forza e lo spostamento avvengono lungo una sola retta, questo si semplifica a:$$\vec{F}_{x}​=-\frac{dU}{dx}​$$
Questa relazione permette di determinare il tipo di equilibrio di un sistema semplicemente analizzando la forma della funzione di energia potenziale, senza dover calcolare esplicitamente le forze in gioco.
- **Equilibrio stabile**: 
  Si verifica in un punto di **minimo relativo** per la funzione di energia potenziale. 
  Se un corpo in questa posizione viene spostato, la forza che agisce su di esso tenderà a riportarlo verso il punto di minimo, come una palla che rotola sul fondo di una conca. 
  *Matematicamente*, in un punto di equilibrio stabile, la derivata prima dell'energia potenziale è zero e la derivata seconda è positiva ($U'(x_{0}​)=0$ e $U''(x_{0}​)>0$).
- **Equilibrio instabile**: 
  Si verifica in un punto di **massimo relativo** per la funzione di energia potenziale. 
  Un corpo in questa posizione è in un equilibrio precario: qualsiasi minima perturbazione lo allontanerà, con la forza che agirà per spingerlo ulteriormente via, come una palla posta sulla cima di una collina. 
  *Matematicamente*, in un punto di equilibrio instabile, la derivata prima dell'energia potenziale è zero e la derivata seconda è negativa ($U'(x_{0}​)=0$ e $U''(x_{0}​)<0$).
- **Equilibrio indifferente**: 
  Si verifica in una regione in cui l'energia potenziale è costante, cioè in una regione di "piattezza". 
  Un corpo in questa regione rimarrà fermo se non viene disturbato, ma non tornerà alla sua posizione originale se spostato. 
  Un esempio è una palla su una superficie orizzontale piana.

I **punti di inversione** del moto sono le posizioni in cui l'energia cinetica di un corpo è nulla, e quindi la sua velocità è zero. 
In questi punti, il corpo si ferma momentaneamente e inverte il suo senso di marcia. 
Tutta l'energia meccanica totale del sistema è stata convertita in energia potenziale. 
Per un sistema in cui l'energia meccanica si conserva, il corpo non può muoversi in regioni dove la sua energia potenziale sarebbe maggiore dell'energia meccanica totale, creando dei "confini" al suo movimento.

[[10 - Quantità di moto e sistemi|Lezione Successiva]]