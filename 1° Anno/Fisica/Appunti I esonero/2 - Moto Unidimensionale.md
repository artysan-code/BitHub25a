## Moto Unidimensionale
La cinematica studia il moto dei corpi senza considerare le cause del moto stesso.

>Moto: variazione nel tempo della posizione di un corpo rispetto a un osservatore.

In questo approccio trascuriamo la struttura interna dei corpi considerati e considereremo le loro dimensioni trascurabili rispetto all'ambiente in cui si svolge il moto, lavoreremo cioè nell'approssimazione di **Punto materiale**.

Questo è il primo esempio di *modello* di un sistema fisico.

Il **moto unidimensionale**, o **moto rettilineo**, si svolge lungo una direzione fissata. E' quindi possibile associare alla retta lungo la quale si svolge il moto un sistema di *coordinate spaziali* rappresentato da un asse orientato.
![[l21.png]]

Un corpo in moto lungo la retta considerata, a ogni istante si trova in una certa posizione individuata dalle coordinate $x(t)$.

>Consideriamo il moto del corpo tra l'istante $t_{i}$ e l'istante $t_{f}>t_{i}$; indichiamo con $\Delta t$ la quantità $t_{f}-t_{i}$; cioè $\Delta t=t_{f}-t_{i}$.

>Indichiamo poi con $\Delta x$ la variazione della posizione del corpo in questo intervallo di tempo cioè poniamo: $\Delta x=x_{f}-x_{i}$ essendo $x_{i}=x(t_{i})$ e $x_{f}=x(t_{f})$.

>Si definisce **velocità media** del corpo considerato nell'intervallo di tempo $\Delta t$ la quantità $\displaystyle v_{x,med}=\frac{\Delta x}{\Delta t}=\frac{x_{f}-x_{i}}{t_{f}-t_{i}}$ misurato in $\displaystyle\frac{m}{s}$ o $m\cdot s^{-1}$.

La velocità media cosi definita non dipende dal percorso seguito tra gli istanti $t_{i}$ e $t_{f}$.

>Si può definire una **velocità scalare media** dividendo la distanza percorsa per l'intervallo di tempo impiegato a percorrerla e può non coincidere con la velocità media.

Il grafico della posizione $x$ al variare del tempo $t$ si dice **legge oraria** del moto del corpo considerato.
![[1° Anno/Fisica/Appunti I esonero/Assets/l22.png]]

Cosa accade alla velocità media di un corpo quando si prendono intervalli sempre più piccoli?

Supponiamo che la posizione del corpo venga misurata a istanti molto vicini tra loro, in modo che il suo grafico venga rappresentato come un unica funzione continua.

A questo punto manteniamo fisso il punto $(t_{i},x_{i})$ e consideriamo $(t_{f},x_{f})$ in punti sempre più vicini a $(t_{i},x_{i})$.
Più ci avviciniamo più la direzione della retta che congiunge i due punti tende a coincidere con la retta tangente al grafico di $x(t)$ nel punto $(t_{i},x_{i})$.

Al tendere di $(t_{f},x_{f})$ a $(t_{i},x_{i})$ i due intervalli $\Delta t$ e $\Delta x$ diventano sempre più piccoli ma il loro rapporto $\displaystyle\frac{\Delta x}{\Delta t}$ tendere ad assumere un valore ben definito.

>Si definisce la **velocità istantanea** all'istante $t_{i}$: $$\displaystyle v_{x}(t_{i})=\lim_{\Delta t\to 0}\frac{\Delta x}{\Delta t}=x'(t)|_{t=t_{i}}$$
>(derivata prima rispetto al tempo della funzione $x(t)$, calcolata per $t=t_{i}$)

In fisica si usano diverse notazioni per le derivate rispetto al tempo, tutte equivalenti:
$\displaystyle x'(t)\equiv \frac{dx(t)}{dt}\equiv\overset{\bullet}{x}(t)\equiv Dx(t)$

###### Esempio 1
Consideriamo un punto materiale che si muove di moto rettilineo con legge oraria:$$x(t)=3t^{2}\quad(m)$$
Innanzitutto 3, essendo il coefficiente di $t^2$ non può essere adimensionale, infatti esso é una grandezza fisica avente come dimensioni $L^{1}\cdot T^{-2}$, cioè $\displaystyle3\frac{m}{s^{2}}$ 

La velocità istantanea in funzione del tempo sara' quindi 
$\displaystyle v_{x}(t)=x'(t)=3\cdot 2\ t = 6\ t \frac{m}{s}$

###### Esempio 2
$x(t)=-4t+2t^{2}\quad(m)$
1) determinare lo spostamento del corpo tra gli istanti $t_{i}=0$ e $t_{f}=1$ s:
	$\Delta x_{1}=x(t_{f})-x(t_{i})=(-4(1)+2(1^{2}))-(-4(0)+2(0^{2}))m=-2 m$
e tra gli istanti $t_{i}=1\ s$ e $t_{f}=3\ s$:
	$\Delta x_{2}=((-4(3)+2(3^{2}))-(-2))\ m=((6)+2)\ m=8\ m$
2) Calcolare le velocità medie nei due intervalli di tempo considerati sopra:
	$\displaystyle v_{m,1}=\frac{\Delta x_{1}}{\Delta t_{1}}=\frac{-2}{1}=-2\ \frac{m}{s}$
	$\displaystyle v_{m,2}=\frac{\Delta x_{2}}{\Delta t_{2}}=\frac{8}{2}=4\ \frac{m}{s}$
3) Trovare la velocità istantanea del corpo all'istante $t=2,5\ s$:
	$\displaystyle v_{x}(t)=x'(t)=(-4+2\cdot 2\ t)\ \frac{m}{s}= (-4+4)\ \frac{m}{s}$
	dunque:
	$\displaystyle v_{x}(t=2,5)=(-4+2\cdot 2,5)\ \frac{m}{s}=6\ \frac{m}{s}$
Per come è definita, la velocità istantanea di un corpo è nulla negli istanti in cui la funzione $x(t)$ presenta un massimo relativo o un minimo relativo a un flesso orizzontale, cioè negli istanti in cui risulta $x'(t)=0$.

## Moto rettilineo uniforme
>Nel caso in cui un corpo si muove di velocità istantanea costante lungo una linea retta, si parla di **moto rettilineo uniforme**.

*Teorema* : nel moto rettilineo la velocità media su qualunque intervallo di tempo coincide con la velocità istantanea costante $v_{x}$

*Dimostrazione* : suddividiamo l'intervallo di tempo $t_{f}-t_{i}$ in $n$ "intervallini" $\Delta t$ uguali, in modo che risulti
$\displaystyle t_{f}-t_{i}=n\cdot\Delta t$.
Siano $\displaystyle \Delta x_{1},\Delta x_{2},\dots,\Delta x_{n}$ i corrispondenti spostamenti in ciascuno di questi "intervallini"; risulta quindi $\displaystyle t_{f}-t_{i}=\Delta x_{1}+\Delta x_{2}+\dots+\Delta x_{n}$.
Allora otteniamo:
$\displaystyle v_{x,med}=\frac{x_{f}-x_{i}}{t_{f}-t_{i}}=\frac{\Delta x_{1}+\Delta x_{2}+\dots+\Delta x_{n}}{n\Delta t}=\frac{1}{n}\left( \frac{\Delta x_{1}}{\Delta t} + \frac{\Delta x_{2}}{\Delta t} + \dots + \frac{\Delta x_{n}}{\Delta t}\right)$
per $n$ molto grande gli intervallini $\Delta t$ diventano molto piccoli, per cui tutti i rapporti $\displaystyle\frac{\Delta x_{1}}{\Delta t},\frac{\Delta x_{2}}{\Delta t},\dots,\frac{\Delta x_{n}}{\Delta t}$ tendono alla velocità istantanea $v_{x}$ che per ipotesi e' costante.