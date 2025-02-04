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
per $n$ molto grande gli intervallini $\Delta t$ diventano molto piccoli, per cui tutti i rapporti $\displaystyle\frac{\Delta x_{1}}{\Delta t},\frac{\Delta x_{2}}{\Delta t},\dots,\frac{\Delta x_{n}}{\Delta t}$ tendono alla velocità istantanea $v_{x}$ che per ipotesi e' costante. Allora otteniamo infine: $$\displaystyle v_{x,med}=\frac{1}{N}\cdot nv_{x}=v_{x}$$e questo dimostra il teorema. $\Box$

Visto che $v_{x,med}=v_{x}$ possiamo scrivere $$\displaystyle\frac{x_{f}-x_{i}}{t_{f}-t_{i}}=v_{x}\implies x_{f}-x_{i}=v_{x}(t_{f}-t_{i})\implies x_{f}=x_{i}+v_{x}(t_{f}-t_{i})$$preso  $t_{i}=0$ e $t_{f}=t$, possiamo scrivere 
>Legge oraria del moto rettilineo uniforme
>$$x_{f}(t)=x_{i}+v_{x}t$$

In definitiva il moto rettilineo uniforme e' descritto dalle seguenti leggi: $$\begin{cases}
v_{x}(t)=v_{x} &  & \text{costante} \\
x(t)=x_{0}+v_{x}t &  & x_{i}=x(t=0)=x_{0}
\end{cases}$$

E' essenziale considerare l'"interpretazione geometrica" del moto rettilineo uniforme. Consideriamo il grafico della funzione $v_{x}(t)=v_{x}$ costante nel piano cartesiano $(t,v_{x})$:
![[1° Anno/Fisica/Appunti I esonero/Assets/l23.png]]
L'area del rettangolo avente per lati i due intervalli $[0,t]$ e $[0,v_{x}]$ e' chiaramente uguale a $v_{x}\cdot t$.
Ma abbiamo visto che risulta $v_{x}t=x(t)-x_{0}$ ; dunque nel piano cartesiano $(t,v_x)$ l'area delimitata tra l'asse dei tempi e il grafico di $v_{x}(t)$ tra gli istanti $0$ e $t$ e' uguale allo spostamento $x(t)-x_{0}$ del corpo tra questi due istanti. Questo e' ovviamente vero anche se $v_{x}<0$

###### Esempio
Corpo che si muove di moto rettilineo uniforme $$x_{i}=0\quad\quad x_{f}=20\ m\quad\quad \Delta t=t_{f}-t_{i}=4,4\ s$$
Poiché $t_{i}=0$ e $x_{i}=0$, quale la posizione del corpo all'istante $t= 10\ s$?$$x(t=10)=x_{i}+v_{x}\cdot(10\ s)=(4,5\cdot 10)\ m= 45\ m$$
##### Osservazione
Le leggi del moto rettilineo uniforme si possono applicare, con le dovute attenzioni, anche al moto non rettilineo purché con velocità scalare costante;
in tal caso occorre immaginare di "rettificare" la traiettoria, e considerare $\Delta x$ la distanza percorsa lungo la traiettoria.

###### Esempio
Traiettoria circolare con raggio $r=10\ m$, percorre con velocità scalare costante $v=5\ m/s$.
Quanto tempo e' necessario per percorrere un giro completo?
Dalla legge $\Delta x=v\Delta t$ otteniamo $$\Delta t=\frac{\Delta x}{v}=\frac{2\pi r}{v}=\frac{2\pi \cdot 10\ m}{5\ m/s}=12,57\ s$$
## Moto accelerato
>Si parla di "moto accelerato" quando la velocità istantanea di un corpo varia nel tempo. 

Sia $V_{x,i}$ la velocità istantanea di un corpo all'istante $t_{i}$, cioè poniamo $V_{x}(t_{i})=V_{x,i}$
Analogamente poniamo $V_{x}(t_{f})=V_{x,f}$

>Definiamo l'**accelerazione media** del corpo tra gli istanti $t_{i}$ e $t_{f}$ la quantità seguente $$a_{x,med}=\frac{v_{x,f}-v_{x,i}}{t_{f}-t_{i}}=\frac{\Delta v_{x}}{\Delta t}$$
che evidentemente si misura con $\displaystyle\frac{m}{s^{2}}$ oppure $m\cdot s^{-2}$ 

Per come e' definita l'accelerazione media di un corpo nell'intervallo $[t_{i},t_{f}]$ e' uguale al coefficiente angolare della retta che passa per i punti $(t_{i},v_{x,i})$ e $(t_{f},v_{x,f})$ nel piano cartesiano $(t,v)_{x}$:
![[1° Anno/Fisica/Appunti I esonero/Assets/l24.png|600]]

Cosa accade all'accelerazione media quando si considerano intervalli di tempo sempre più piccoli?
Supponiamo che la velocità istantanea del corpo venga misurata a istanti molto vicini tra loro, in modo che il grafico sia rappresentato di fatto da una funzione continua.

A questo punto manteniamo fisso il punto $(t_{i},v_{x,i})$ e consideriamo $(t_{f},v_{x,f})$ in punti sempre più vicini a $(t_{i},v_{x,i})$
![[1° Anno/Fisica/Appunti I esonero/Assets/l25.png|500]]
Man mano che $(t_{f},v_{x,f})$ si avvicina a $(t_{i},v_{x,i})$, la direzione della retta che congiunge i due punti tende a coincidere con la direzione della retta tangente al grafico di $v_{x}(t)$ nel punto $(t_{i},v_{x,i})$.
Come già visto nel caso di $\displaystyle\frac{\Delta x}{\Delta t}$, anche nel caso del rapporto $\displaystyle\frac{\Delta v_{x}}{\Delta t}$ i due intervalli di $\Delta v_{x}$ e $\Delta t$ diventano sempre più piccoli al tendere di $(t_{f},v_{x,f})$ a $(t_{i},v_{x,i})$, ma il rapporto $\displaystyle\frac{\Delta v_{x}}{\Delta t}$ tende ad assumere un valore ben definito.

>Si definisce quindi l'**Accelerazione istantanea** all'istante $t_{i}$: $$\displaystyle a_{x}(t_{i})=\lim_{\Delta t\to 0}\frac{\Delta v_{x}}{\Delta t}= v_{x}^{'}(t)$$

Quando si usa il solo termine "accelerazione" in genere si intende accelerazione istantanea.
Per come e' definita, l'accelerazione istantanea di un corpo e' nulla negli istanti in cui la funzione $v_{x}(t)$ presenta un minimo/massimo relativo o un flesso orizzontale, cioè negli istanti in cui risulta $v^{'}_{x}(t)=0$.
Risulta anche, come conseguenza delle leggi determinate sinora: $$a_{x}(t)=x^{''}(t)\quad(\text{essendo }v_{x}(t)=x^{'}(t))$$Quando $v_{x}(t)$ e $a_{x}(t)$ hanno lo stesso segno, $|v_{x}(t)|$ aumenta nel tempo. 
Quando $v_{x}(t)$ e $a_{x}(t)$ hanno segni opposti, $|v_{x}(t)|$ decresce nel tempo. 

*Attenzione:* 
un corpo che si muove di moto rettilineo uniforme ha accelerazione nulla. Infatti risulta $$a_{x}(t)=v^{'}_{x}(t)=0\quad\text{ se }\quad v_{x}(t)=v_{x}\text{ costante}$$
###### Esempio
Un corpo si muove di moto rettilineo con legge oraria $$x(t)=2+3t-t^{2}\quad (m)$$Risulta pertanto $$\begin{array}{l}
v_{x}(t)=x^{'}(t)=3-2t & (m/s) \\
a_{x}(t)=-2\ m/s^{2} & (=v_{x}^{'}(t))
\end{array}$$All'istante $t=3\ s$ risulta: $$\begin{array}{r l l}
x(t=3\ s)= & (2+3\cdot 3-3^{2})\ m & =2\ m \\
v_{x}(t=3\ s)= & (3-2\cdot 3)\ m/s & =-3\ m/s \\
a_{x}(t=3\ s)= & -2\ m/s^{2} & (a_{x}\text{ e' costante in questo caso, non dipende dal tempo})
\end{array}$$
Il grafico di $x(t)$ e' rappresentato da una parabola con asse parallelo all'asse delle ordinate, concavità risolta verso il basso, e vertice nel punto di ascisse$$t_{v}=\frac{-3}{-2}\ s=1,5\ s$$Ordinata del vertice della parabola $$x_{v}=x\left( t=\frac{3}{2}\ s \right)=\left( 2+3\cdot \frac{3}{2}-\left( \frac{3}{2} \right)^{2} \right)\ m=\left( 2+\frac{9}{2}-\frac{9}{4} \right)=\frac{17}{4}\ m=4,25\ m$$
A quale istante risulta $x=0$? considerare solo valori $t>0$
Occorre risolvere l'equazione nell'incognita $t$: $$\begin{array}{}
2+3t-t^{2}=0 \implies t^{2}-3t-2=0 \\
\displaystyle t_{1,2}=\frac{3\pm \sqrt{9+8}}{2}=\frac{3\pm \sqrt{17}}{2}
\end{array}$$
La soluzione accettabile e' $\displaystyle t_{2}=\frac{3\pm \sqrt{ 17 }}{2}\ s\simeq 3,56\ s$ 
![[1° Anno/Fisica/Appunti I esonero/Assets/l26.png|500]]

## Moto Rettilineo Uniformemente Accelerato
>Nel caso particolare in cui un corpo si muove con accelerazione istantanea costante, lungo una linea retta, si parla di **moto rettilineo uniformemente accelerato**.

*Teorema*: 
Nel moto rettilineo uniformemente accelerato l'accelerazione media su un qualunque intervallo di tempo coincide con l'accelerazione istantanea costante $a_{x}$.

*Dimostrazione*: 
Suddividiamo l'intervallo di tempo $t_{f}-t_{i}$ in $n$ "intervallini" $\Delta t$ uguali, in modo che risulti $t_{f}-t_{i}=n\Delta t$. 
Siano $\Delta v_{x,1},\Delta v_{x,2},\dots,\Delta v_{x,n}$ le corrispondenti variazioni delle velocità istantanee in ciascuno di questi "intervallini", risulta pertanto: $$\displaystyle v_{x,f}-v_{x,i}=\Delta v_{x,1}+\Delta v_{x,2}+\dots+\Delta v_{x,n}$$Allora otteniamo $$\displaystyle a_{x,med}=\frac{v_{x,f}-v_{x,i}}{t_{f}-t_{i}}=\frac{\Delta v_{x,1}+\Delta v_{x,2}+\dots+\Delta v_{x,n}}{x\Delta t}=\frac{1}{n}\left( \frac{\Delta v_{x,1}}{\Delta t}+\frac{\Delta v_{x,2}}{\Delta t}+\dots+\frac{\Delta v_{x,n}}{\Delta t} \right)$$Per $n$ molto grande gli "intervallini" $\Delta t$ diventano molto piccoli, per cui tutti i rapporti $\displaystyle\frac{\Delta v_{x,1}}{\Delta t},\frac{\Delta v_{x,2}}{\Delta t},\dots,\frac{\Delta v_{x,n}}{\Delta t}$ tendono all'accelerazione istantanea $a_{x}$, che per ipotesi e' costante.
Allora otteniamo infine: $$a_{x,med}=\frac{1}{n}\cdot n\ a_{x}=a_{x}\ (n\text{ grande})$$e questo dimostra il teorema.$\Box$

Dunque, poiché $a_{x,med}=a_{x}$ costante, possiamo scrivere: $$\displaystyle\frac{v_{x,f}-v_{x,i}}{t_{f}-t_{i}}=a_{x}\implies v_{x,f}-v_{x,i}=a_{x}(t_{f}-t_{i})\implies v_{x,f}=v_{x,i}+a_{x}(t_{f}-t_{i})$$preso $t_{i}=0$ e $t_{f}=t$ (istante generico), possiamo quindi scrivere: $$\begin{bmatrix} \\
 & v_{x,f}(t)=v_{x,i}+a_{x}t & \\ \
\end{bmatrix}\quad (a_{x}\text{ costante})$$
Poiché $t_{i}=0$, eliminando l'indice $f$ possiamo scrivere, in generale, per il moto rettilineo uniformemente accelerato: $$v_{x}(t)=v_{x,0}+a_{x}t$$Anche in questo caso e' possibile dare un interpretazione geometrica. Consideriamo il grafico della funzione $a_{x}(t)=a_{x}$ costante nel piano cartesiano $(t,a_{x})$:
![[1° Anno/Fisica/Appunti I esonero/Assets/l27.png| 400]]
L'area del rettangolo avente per lati i due intervalli $[0,t]$ e $[0,a_{x}]$ e' chiaramente uguale a $a_{x}\cdot t$.
Ma abbiamo visto che risulta $a_{x}t=v_{x}(t)-v_{x,0}$; 
dunque, nel piano cartesiano $(t,a_{x})$, l'area delimitata tra l'asse dei tempi e il grafico di $a_{x}(t)$ tra gli istanti $0$ e $t$ e' uguale alla variazione $v_{x}(t)-v_{x,0}$ della velocità istantanea del corpo tra questi due istanti. Questo e' ovviamente vero anche se $a_{x}<0$

Ma quale e' la legge oraria del moto uniformemente accelerato?
Consideriamo il grafico della funzione $v_{x}(t)$. Risulta $$v_{x}(t)=v_{x,0}+a_{x}t$$Ad esempio, nel caso $a_{x}>0$, l'andamento del grafico di $v_{x}(t)$ può essere di questo tipo:
![[1° Anno/Fisica/Appunti I esonero/Assets/l28.png|400]]
E' necessario procedere in questo modo: suddividiamo l'intervallo $[0,t]$ in $n$ rettangolini aventi tutti base $\Delta t$ sull'asse dei tempi, e ciascuno altezza pari al valore di $v_{x}(t)$ nell'estremo inferiore del corrispondente "intervallino" $\Delta t$: 
![[1° Anno/Fisica/Appunti I esonero/Assets/l29.png|400]]
Poniamo $t_{0}=0$, risulterà $t_{n-1}=t-\Delta t$ e $t_{n}=t$
Per $\Delta t\to 0$, la somma delle aree dei rettangolini tende all'area della regione compresa (nel piano cartesiano ($t,v_{x}$)) tra l'asse dei tempi e il grafico di $v_{x}(t)$ nell'intervallo $[0,t]$.
Questa regione piana e' chiaramente un trapezio rettangolo, e la sua area (che coincide con lo spostamento del corpo lungo l'asse $x$ tra gli istanti $0$ e $t$ dato che questo e' vero per ogni intervallino $\Delta t$) e' facilmente calcolabile: $$x(t)-x_{0}=\frac{[v_{x}(t)+v_{x,0}]\cdot t}{2}=\frac{[(v_{x,0}+a_{x}t)+v_{x,0}]\cdot t}{2}=\frac{(2v_{x,0}+a_{x}t)\cdot t}{2}=v_{x,0}t+\frac{1}{2}a_{x}t^{2}$$Riordiniamo i termini, otteniamo infine:
>**Legge oraria del moto rettilineo uniformemente accelerato**$$\begin{bmatrix} \\
\displaystyle x(t)=x_{0}+v_{x,0}t+\frac{1}{2}a_{x}t^{2} \\ \
\end{bmatrix}$$

>In definitiva il moto rettilineo uniformemente accelerato e' descritto dalle seguenti leggi: $$\begin{cases}
a_{x}(t)=a_{x}\text{ costante} \\
v_{x}(t)=v_{x,0}+a_{x}t \\
\displaystyle x(t)=x_{0}+v_{x,0}t+\frac{1}{2}a_{x}t^{2}
\end{cases}$$

Ad esempio per $a_{x}>0$:
![[l210.png|400]]

Dalle equazioni $v_{x}(t)$ e $x(t)$ e' possibile ricavare un equazione che lega $v_{x}$ direttamente a $x$ nel moto rettilineo uniformemente accelerato.
Da $v_{x}(t)=v_{x,0}+a_{x}(t)$ possiamo ricavare: $$t=\frac{v_{x}(t)-v_{x,0}}{a_{x}}\quad\quad(\text{se }a_{x}=0\text{, ovviamente})$$Sostituiamo questa espressione al posto di $t$ nell'espressione della legge oraria: $$\begin{array}{l}
\displaystyle x(t)=x_{0}+\frac{v_{x,0}[v_{x}(t)+v_{x,0}]}{a_{x}}+\frac{1}{2}\centernot{a_{x}}\frac{[v_{x}(t)+v_{x,0}]^{2}}{a_{x}^{\centernot2}}= \\
\displaystyle=x_{0}+ \frac{1}{2a_{x}} [2v_{x,0}v_{x}(t)-2v_{x,0}^{2}+(v_{x}(t)^{2})-2v_{x,0}v_{x}(t)+v_{x,0}^{2}]= \\
\displaystyle = x_{0}+\frac{1}{2a_{x}}[(v_{x}(t))^{2}-v_{x,0}^{2}] \\
\end{array}$$Questa relazione può anche essere scritta nella forma: $$\displaystyle(v_{x}(t))^{2}=v_{x,0}^{2}+2a_{x}[x(t)-x_{0}]$$

###### Esempio
Un corpo ha inizialmente velocità istantanea $V_{x,0}=632\text{ miglia/h}\quad\quad(1\text{ miglio}=1609,35\ m)$, e viene portato a riposo (cioè fermato) in un intervallo di tempo $T=1,4\ s$ con accelerazione costante.
a) Si calcoli l'accelerazione del corpo
	dalla legge $V_{x}(t)=V_{x,0}+a_{x}t$, sappiamo che risulta $V_{x}(t=T)=0$, per cui possiamo scrivere $$\displaystyle V_{x,0}+a_{x}T\implies a_{x}=-\frac{V_{x,0}}{T}=-\frac{632\cdot 1609,35}{1,4\cdot 3600}\ \frac{m}{s^{2}}$$Abbiamo usato l'identità $\displaystyle1\frac{\text{miglio}}{h}=\frac{1\cdot 1609,35\ m}{3600\ s}$, essendo $1\ h=3600\ s$. Allora: $$a_{x}=-\frac{V_{x,0}}{T}\simeq-201,81\ m/s^{2}$$
b) Si calcoli la distanza percorsa dal corpo tra l'istante $t=0$ e l'istante $T$:
	Usiamo la legge oraria del moto rettilineo uniformemente accelerato: $$\displaystyle x(t)=x_{0}+V_{x,0}t+\frac{1}{2}a_{x}t^{2}\quad,$$
	ponendo $t=T$ e $\displaystyle a_{x}=-\frac{V_{x,0}}{T}$,essendo $x_{0}=0$: $$\displaystyle x(T)=V_{x,0}T-\frac{1}{2}\frac{V_{x,0}}{\centernot T}T^{\centernot 2}=\frac{1}{2}V_{x,0}T=\frac{1}{2}\cdot 632\cdot \frac{1609,35}{3600}\cdot 1,4\ m=197,77\ m$$

###### Esempio
Un corpo si muove di moto rettilineo uniformemente accelerato partendo da fermo all'istante $t=0$, e raggiungendo una velocità istantanea pari a $v_{f}=10,97\ km/s$ dopo aver percorso un tratto lungo $220\ m$.
Quanto vale l'accelerazione?
	Possiamo utilizzare le leggi del moto rettilineo uniformemente accelerato, poniamo $d=220\ m$
	Poiché $x_{0}=0$ e $v_{x,0}=0$ possiamo scrivere: $$\displaystyle\begin{cases}
\displaystyle d=\frac{1}{2}a_{x}t^{2} \\
\displaystyle v_{f}=a_{x}t
\end{cases}\implies \text{Ricaviamo }t\text{ dalla seconda equazione:}$$$\displaystyle t=\frac{v_{f}}{a_{x}}$ e sostituendo questa espressione alla variabile $t$ nella prima equazione: $$\displaystyle d=\frac{1}{2}\centernot{a_{x}}\frac{v_{f}^{2}}{a_{x}^{\not2}}\implies a_{x}=\frac{v_{f}^{2}}{2d}=\frac{(10,97\cdot 10^{3})^{2}}{2\cdot 220}\quad\frac{m}{s^{2}}=2,735\cdot 10^{5}\ m/s^{2}$$Possiamo anche usare la legge che collega direttamente $x$ e $v_{x}$: $$\displaystyle a_{x}=\frac{v_{f^{2}}-v_{x,0}^{2}}{2(d-x_{0})}=\frac{v_{f}^{2}}{2d}$$che e' identica a quella trovata in precedenza.

## Accelerazione di gravita vicino alla superficie terrestre

Un corpo in caduta libera in prossimità della superficie terrestre si muove di moto uniformemente accelerato lungo tratti di cadute brevi.
Se vengono eliminati tutti gli attriti, si osserva che tutti i corpi, cadono con la stessa accelerazione.
Al livello del mare questa accelerazione vale $9,81\ m/s^{2}$ e si indica con la lettera $g$.

###### Esempio
Un corpo viene lanciato verso l'alto con velocità iniziale $v_{x,0}=6\ m/s$.
a) quale e' la massima altezza raggiunta dal corpo?
	Consideriamo un asse $x$ verticale ,orientato positivamente verso l'alto. 
	Con questa scelta risulta $v_{x,0}=6\ m/s,\ a_{x}=-g=-9,81\ m/s^{2}$, in quanto l'accelerazione in quanto l'accelerazione di gravita tende a rallentare i corpi che si muovono verso l'alto.
	Dalla legge $v_{x}(t)=v_{x,0}+a_{x}t=v_{x,0}-gt$ otteniamo l'istante $t_{1}$ in cui risulta $v_{x}(t_{1})=0$, cioè l'istante in cui il corpo raggiunge la massima altezza lungo la sua traiettoria: $$\displaystyle t_{1}=\frac{v_{x,0}}{g}$$	Sostituendo questa espressione alla legge oraria del moto rettilineo uniformemente accelerato otteniamo la quota raggiunta dal corpo all'istante $t=t_{1}$:$$\begin{array}{r}
\displaystyle x(t_{1})=v_{x,0}t_{1}-\frac{1}{2}gt_{1}^{2}=v_{x,0}\left( \frac{v_{x,0}}{g} \right)-\frac{1}{2}g\left( \frac{v_{x,0}}{g} \right)^{2}= \\
\displaystyle =\frac{v_{x,0}^{2}}{g}-\frac{1}{2}\centernot{g}\frac{v_{x,0}^{2}}{g^{\not 2}}=\frac{v_{x,0}^{2}}{2g}=\frac{6^{2}}{2\cdot 9,81}\ m=1,83\ m
\end{array}$$Si poteva ottenere lo stesso risultato utilizzando la legge che lega $v_{x}$ e $x$ direttamente: $$x(t_{1})-x_{0}=\frac{(v_{x}(t_{1}))^{2}-v_{x,0}^{2}}{2a_{x}}$$con $x=0$ e $v_{x}(t_{1})=0$ e $a_x=-g$ otteniamo: $$x(t_{1})=\frac{-v_{x,0}^{2}}{-2g}=\frac{v_{x,0}^{2}}{2g}$$che coincide con il risultato ottenuto precedentemente.

b) a partire dall'istante $t=0$ dopo quanto tempo il corpo torna alla quota $x=0$?
	Dalla legge oraria $\displaystyle x(t)=v_{x,0}t-\frac{1}{2}gt^{2}$, la condizione $x(t)=0$ parte all'equazione $v_{x,0}t-\frac{1}{2}gt^{2}=0$; mettiamo $t$ in evidenza: $$t\left( v_{x,0}-\frac{1}{2}gt \right)=0$$	Si ottengono quindi 2 soluzioni: $$t_{1}=0\quad(\text{ovvia})\quad\quad t_{2}=\frac{2v_{x,0}}{g}=\frac{2\cdot 6}{9,81}\ s=1,22\ s$$	che e' la soluzione cercata.

###### Problema (da fare)

## Moto rettilineo vario

Nel caso più generale, la funzione $v_{x}(t)$ nel moto rettilineo potrebbe non essere costante ne avere un andamento lineare al variare del tempo. Ad esempio:
![[l211.png|400]]
Tuttavia, e' possibile ripetere lo stesso ragionamento fatto nel moto rettilineo uniformemente accelerato. La conclusione e' la stessa: lo spostamento del corpo tra l'istante $t_i$ e l'istante $t_{f}$ e' dato dall'area della regione compresa (nel piano cartesiano $(t,v_{x})$) tra l'asse dei tempi e il grafico di $v_{x}(t)$ matematicamente possiamo quindi scrivere $$\displaystyle x_{f}-x_{i}=\int_{t_{i}}^{t_{f}}v_{x}(t)dt$$nei casi $v_{x}(t)=v_{x} \text{ costante}$ e $v_{x}(t)=v_{x,0}+a_{x}t$, con $a_{x}\text{ costante}$, questa formula fornisce i risultati già ottenuti in precedenza per altre vie. 
Sempre nel caso più generale, la funzione $a_{x}(t)$ nel moto rettilineo potrebbe non essere costante. Ad esempio: 
![[l212.png|400]]
Tuttavia, e' possibile ripetere lo stesso ragionamento fatto nel moto rettilineo uniformemente accelerato.
La conclusione e' la stessa: la variazione della velocità istantanea del corpo tra l'istante $t_i$ e l'istante $t_{f}$ e' data dall'area della regione compresa (nel piano cartesiano $(t,a_{x})$) tra l'asse dei tempi e il grafico di $a_{x}(t)$. Quindi vale la legge: $$\displaystyle v_{x,f}-v_{x,i}=\int_{t_{i}}^{t_{f}}a_{x}(t)dt$$
Il caso $a_{x}(t)=a_{x}=\text{costanti}$ cioè il caso del moto rettilineo uniformemente accelerato e il caso $a_{x}(t)=0$, cioè il caso del moto rettilineo uniforme si ritrovano subito come casi particolari di questa legge.
Posto $t_{i}=0$ e $t_{f}=t$ (istante generico, la legge oraria e la velocità istantanea in funzione del tempo nel moto rettilineo vario si possono esprimere nel modo seguente, quindi: $$\displaystyle x(t)=x_{0}+\int_{0}^{t}v_{x}(\tau)d\tau;\quad v_{x}(t)=v_{x,0}+\int_{0}^{t}a_{x}(\tau)d\tau$$