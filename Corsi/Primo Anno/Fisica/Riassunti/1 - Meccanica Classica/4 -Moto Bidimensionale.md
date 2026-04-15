[[4 -Moto Bidimensionale|Lezione Precedente]]
# Concetti Fondamentali del Moto Bidimensionale
Il moto bidimensionale descrive il movimento di un corpo su un piano. 
Per analizzarlo, si utilizzano le seguenti grandezze vettoriali:
- **Vettore posizione** ( $\vec{r}$ ): 
  Individua la posizione del corpo rispetto all'origine di un sistema di riferimento. $$\vec{r}(t)=x(t)\hat{i}+y(t)\hat{j}​$$
- **Vettore spostamento** ($\Delta r$): 
  Rappresenta la variazione di posizione del corpo in un intervallo di tempo $\Delta t$.$$\Delta r=r_f​-r_i$$​
- **Velocità media** ($\vec{v}_{med}$​): 
  Rapporto tra il vettore spostamento e l'intervallo di tempo.$$\vec{v}_{med}​=\Delta t\Delta r​$$
- **Velocità istantanea** ($v$): 
  Limite della velocità media per un intervallo di tempo che tende a zero.
  È un vettore tangente alla traiettoria del corpo.$$\vec{v}=\lim_{\Delta t \to 0}​\frac{\Delta \vec{r}}{\Delta t}​=\frac{d\vec{r}}{dt}​=v_{x}\hat{i}+v_{y}​\hat{j}$$​
- **Accelerazione istantanea** ($a$): 
  Limite dell'accelerazione media per un intervallo di tempo che tende a zero.
  Rappresenta la rapidità con cui cambia il vettore velocità.$$\vec{a}=\lim_{\Delta t \to 0} \frac{\Delta \vec{v}}{\Delta t}​=\frac{d\vec{v}}{dt}​=a_{x}\hat{i}+a_{y}​\hat{j}​$$
# Moto del Proiettile
Il **moto del proiettile** è un esempio classico di moto bidimensionale con accelerazione costante. 
In assenza di attrito dell'aria, l'unica forza che agisce è la gravità, che produce un'accelerazione costante e verticale ($\vec{a}=-g\hat{j}$​). 
Il moto orizzontale e quello verticale sono indipendenti. 
Le equazioni cinematiche sono:
- **Componenti della velocità**:$$\begin{array}{l}
v_{x}​(t)=v_{0}\cos\theta_{0} \\
​v_{y}​(t)=v_{0}​\sin\theta_{0}​-gt
\end{array}$$
- **Posizione del corpo**:$$\begin{array}{l}
x(t)=(v_{0}​\cos\theta_{0}​)t \\
y(t)=y_{0}+(v_{0}\sin\theta_{0}​)t-\frac{1}{2}​gt^2
\end{array}$$

La traiettoria del proiettile è una **parabola**. 
La **gittata** ($D$), ovvero la distanza orizzontale percorsa, è massima per un angolo di lancio di $45°$.
# Moto Circolare Uniforme
Il **moto circolare uniforme** è un altro caso fondamentale di moto bidimensionale.
La traiettoria è una circonferenza, e il modulo della velocità è costante. 
Anche se il modulo della velocità non cambia, la sua direzione varia continuamente, causando un'accelerazione chiamata **accelerazione centripeta**.
- **Accelerazione centripeta**: 
  È un vettore diretto radialmente verso il centro della circonferenza.$$a_c​=\frac{v^2}{r}$$​
- **Periodo** ($T$): 
  Il tempo necessario per un giro completo.$$T=\frac{2\pi r}{v}$$​
- **Frequenza** ($f$): Il numero di giri al secondo.$$f=\frac{1}{T}$$​
- **Velocità angolare** ($\omega$): 
  Il rapporto tra l'angolo percorso e il tempo.$$\omega=\frac{2\pi}{T}​=2\pi f$$La relazione tra velocità lineare e angolare è $v=\omega r$.
# Accelerazione in un Moto Generico
Nel caso più generale di moto bidimensionale, dove sia il modulo che la direzione della velocità possono cambiare, l'accelerazione può essere scomposta in due componenti:
- **Accelerazione tangenziale** ($\vec{a}_t$​): 
  Tangente alla traiettoria. 
  È legata alla variazione del **modulo** della velocità.$$|\vec{a}_t​|=|\frac{d|\vec{v}|}{dt}​|$$
- **Accelerazione radiale** (o *centripeta*, $\vec{a}_r$​): 
  Perpendicolare alla traiettoria, diretta verso il centro di curvatura istantaneo. 
  È legata alla variazione della **direzione della velocità**.$$|\vec{a}_r​|=\frac{v^2}{r}​$$
    dove $r$ è il raggio di curvatura della traiettoria nel punto considerato. L'accelerazione totale è la somma vettoriale di queste due componenti: $\vec{a}=\vec{a}_t​+\vec{a}_r$​.

[[5 - Moto relativo|Lezione Successiva]]
[[Eserciziario#^b4aa15|Esercizi svolti sul capitolo]]