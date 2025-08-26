[[22 - Corrente e circuiti in corrente continua|Lezione Precedente]]
# Campo Magnetico e Forza di Lorentz
Una carica elettrica in movimento genera un **campo magnetico** ($\vec{B}$). 
Simile al campo elettrico, anche il campo magnetico è un campo vettoriale. 
La direzione e il verso di $\vec{B}$ in un punto sono quelli indicati dal polo nord di una bussola posta in quel punto.

La forza magnetica ($\vec{F}_{B}$​​) che agisce su una particella di carica q in movimento con velocità v in un campo magnetico B è data dalla **forza di Lorentz**:$$\vec{F}_{\vec{B}}​=q(\vec{v}\times\vec{B})$$

Il modulo di questa forza è $F_{B}=|q|vB\sin\theta$, dove $\theta$ è l'angolo tra $v$ e $B$. 
La forza magnetica è sempre perpendicolare sia a $\vec{v}$ che a $\vec{B}$, il che implica che non compie lavoro e non altera l'energia cinetica della particella, ma ne modifica solo la direzione del moto.

Quando una particella carica si muove in un campo magnetico uniforme con velocità perpendicolare al campo, la sua traiettoria è una circonferenza di raggio:$$r=\frac{mv​}{|q|B}$$
Se la velocità ha anche una componente parallela al campo, la traiettoria diventa un'elica.

# Forza Magnetica su un Conduttore
Un filo percorso da corrente, essendo un insieme di cariche in movimento, subisce una forza magnetica se immerso in un campo magnetico esterno. La forza magnetica su un tratto rettilineo di filo di lunghezza $L$ è:$$\vec{F}_{B}=I(\vec{L}\times\vec{B})$$dove $I$ è la corrente e $\vec{L}$ è un vettore con modulo pari alla lunghezza del filo e orientato nel verso della corrente.
# Momento Magnetico e Spire
Una spira percorsa da corrente, immersa in un campo magnetico uniforme, è soggetta a un momento torcente ($\tau$) che tende a farla ruotare. Il momento torcente è dato da:$$\vec{\tau}=I(\vec{A}\times\vec{B})$$dove $\vec{A}$ è il vettore area della spira. 
Il prodotto $I\vec{A}$ è definito come il **momento di dipolo magnetico** ($\vec{\mu}$​), per cui $\vec{\tau}=\vec{\mu}\times\vec{B}$. 
La spira tende ad allinearsi in modo che il suo momento di dipolo sia parallelo al campo magnetico.
# Legge di Biot-Savart e Teorema di Ampère
Le leggi di Biot-Savart e di Ampère permettono di calcolare il campo magnetico generato da una distribuzione di corrente.

La **legge di Biot-Savart** descrive il contributo di un piccolo segmento di filo percorso da corrente ($\Delta\vec{s}$) al campo magnetico in un punto:$$\Delta \vec{B}=\frac{\mu_{0}}{4\pi} \frac{I(\Delta \vec{s}\times \hat{r})}{r^{2}}​$$dove $\mu_{0}$​ è la **permeabilità magnetica del vuoto** $\displaystyle\left( \mu_{0}​=4\pi \times10^{-7}\frac{T\cdot m​}{A} \right)$.

Il **teorema di Ampère** è un'alternativa utile per distribuzioni di corrente altamente simmetriche. 
Afferma che l'integrale di linea del campo magnetico lungo un percorso chiuso è proporzionale alla corrente totale che attraversa la superficie delimitata dal percorso:$$\oint\vec{B}\cdot d\vec{s}=\mu_{0}​I$$

Con questo teorema si può calcolare facilmente il campo magnetico all'interno di un **solenoide** ideale $(B=\mu_{0}​nI$, dove $n$ è il numero di spire per unità di lunghezza) e di un filo lungo e rettilineo ($\displaystyle B=\frac{\mu_{0}I}{2\pi r})$​

[[24 - Legge di Faraday e induttanza|Lezione Successiva]]