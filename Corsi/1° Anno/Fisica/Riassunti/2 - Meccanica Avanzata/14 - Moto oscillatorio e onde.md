[[13 - Moto rotazionale|Lezione Precedente]]
# Moto Oscillatorio
Il moto oscillatorio è il movimento di un corpo sotto l'azione di una forza elastica. 
Un esempio classico è un punto materiale di massa $m$ collegato a una molla di costante elastica $k$. 
La forza di richiamo della molla, descritta dalla **Legge di Hooke**, è $F_{e}=-kx$. 
Applicando la seconda legge della dinamica ($F=ma$), si ottiene l'equazione del moto:
$$\begin{array}{l}
max​(t)=-kx(t) \\
x^{''}(t)+ \frac{k}{m}​x(t)=0
\end{array}$$


Questa è l'equazione di un **moto armonico semplice**. 
La soluzione di questa equazione è:  
$$x(t)=A\cos(\omega t+\phi_{0}​)$$
dove:
- $\displaystyle\omega=\sqrt{ \frac{k}{m} }​​$ è la **pulsazione angolare** (in $rad/s$), una caratteristica intrinseca del sistema.
- $A$ è l'**ampiezza**, il massimo spostamento dalla posizione di equilibrio.
- $\phi_{0}$​ è la **costante di fase iniziale**.

Il moto è periodico con un **periodo** $T$ e una **frequenza** $f$ dati da:  $$\begin{array}{l}
\displaystyle T=\frac{2\pi}{\omega}​=2\pi \sqrt{ \frac{m}{k} } \\
\displaystyle f = \frac{1}{T} = \frac{\omega}{2\pi} = \frac{1}{2\pi}\sqrt{\frac{k}{m}}
\end{array}​​$$La velocità istantanea e l'accelerazione istantanea si ottengono derivando $x(t)$:$$\begin{array}{l}
v_{x}(t)=-\omega A\sin(\omega t+\phi_{0}​) \\
a_x(t) = -\omega^2 A \cos(\omega t + \phi_0) = -\omega^2 x(t)
\end{array}$$L'**energia meccanica** totale del sistema, che si conserva in assenza di attrito, è:$$E_{m}​=\frac{1}{2}​kA^{2}$$
# Pendolo Semplice
Un pendolo semplice, per piccole oscillazioni $(|\theta|\leq 6°)$, può essere approssimato a un moto armonico semplice. L'equazione del moto è:$$[\theta(t)]^{''}+ \frac{g}{L}\theta(t)=0$$
La pulsazione angolare e il periodo sono:$$\begin{array}{l}
\displaystyle\omega=\sqrt{ \frac{g}{L} } \\
​​\displaystyle T=2\pi \frac{L}{g}
\end{array}​​$$Il periodo dipende solo dalla lunghezza del filo $L$ e dall'accelerazione di gravità $g$, non dalla massa del corpo.
# Onde
Un'**onda** è una perturbazione che si propaga nello spazio, trasferendo energia ma non materia. 
Le **onde meccaniche** richiedono una sorgente, un mezzo e un meccanismo di interazione tra le sue parti.
- **Onde Trasversali:** Le particelle del mezzo si muovono *perpendicolarmente alla direzione* di propagazione dell'onda (es. onde su una corda).
- **Onde Longitudinali:** Le particelle del mezzo si muovono *parallelamente alla direzione* di propagazione dell'onda (es. onde sonore).

La **funzione d'onda** $y(x,t)$ descrive lo spostamento di un punto del mezzo in funzione della posizione x e del tempo $t$. 
Per un'onda che si propaga verso destra, la funzione d'onda è del tipo $y(x,t)=f(x−vt)$.

Per un'**onda sinusoidale**, la funzione d'onda è:$$y(x,t)=A\sin(kx-\omega t)$$
- $A$ è l'ampiezza.
- $\lambda$ è la **lunghezza d'onda**, la distanza tra due creste consecutive. Il **numero d'onda** è $\displaystyle k=\frac{2\pi}{\lambda}​$.
- $T$ è il **periodo**. 
  La **pulsazione** è $\displaystyle\omega=\frac{2\pi}{T}$​.
- La **velocità di propagazione** è data da $v=\frac{\omega}{k}=\lambda f$.

L'**equazione delle onde lineari** descrive la propagazione di un'onda lineare e ha la forma:$$\frac{\partial^{2}y}{\partial x^{2}}=\frac{1}{v^{2}} \frac{\partial^{2}y}{\partial t^{2}}​$$
La velocità di propagazione di un'onda su una corda tesa è $v=\sqrt{ \frac{T}{\mu} }$​​, dove $T$ è la tensione e $\mu$ la densità lineare.
# Riflessione e Trasmissione
Quando un'onda incontra un'interfaccia tra due mezzi, parte dell'energia viene riflessa e parte viene trasmessa.
- **Estremità fissa:** L'onda riflessa è "capovolta" (fase *invertita*).
- **Estremità libera:** L'onda riflessa non è "capovolta".
- **Passaggio da mezzo leggero a pesante** ($\mu_{1}​<\mu_{2}$​): L'onda riflessa è *invertita* e l'ampiezza è *minore*.
- **Passaggio da mezzo pesante a leggero** ($\mu_{1}​>\mu_{2}​$): L'onda riflessa *non* è *invertita* e l'ampiezza è minore.
# Onde Stazionarie
Le **onde stazionarie** si formano dalla sovrapposizione di due onde con la stessa ampiezza, lunghezza d'onda e frequenza che si propagano in direzioni opposte. La funzione d'onda risultante è:$$y(x,t)=2A\sin(kx)\cos(\omega t)$$
I punti con ampiezza massima sono detti **ventri**, mentre quelli con ampiezza nulla sono detti **nodi**. 
Su una corda fissata agli estremi, i nodi sono sempre agli estremi. 
Le lunghezze d'onda possibili sono quantizzate: $$\lambda_n = \frac{2L}{n}$$Le frequenze corrispondenti sono:$$f_{n}=\frac{v}{\lambda_{n}}​=\frac{n}{2L}\sqrt{\frac{T}{\mu}}​​$$

La frequenza $f_{1}$​ è la **frequenza fondamentale**, e le altre frequenze $f_{n}$​ sono le sue armoniche.
# Battimenti
I **battimenti** si verificano quando due onde con frequenze leggermente diverse si sovrappongono. L'ampiezza dell'onda risultante varia nel tempo, con una **frequenza di battimento** $f_{b}​=|f_{1}-f_{2}|$.


[[20 - Forza elettrica e campo elettrico|Lezione Successiva]]