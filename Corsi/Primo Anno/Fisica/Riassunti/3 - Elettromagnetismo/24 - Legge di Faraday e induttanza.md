[[23 - Forze e campi magnetici|Lezione Precedente]]
# Induzione Elettromagnetica
La **Legge di Faraday-Neumann** è un principio fondamentale che descrive come un campo magnetico variabile nel tempo possa indurre una forza elettromotrice (f.e.m.) e una corrente in un circuito. 
Gli esperimenti di Faraday dimostrarono che una corrente indotta si genera in una spira solo quando c'è un movimento relativo tra la spira e un magnete, o quando il campo magnetico stesso varia nel tempo.

La f.e.m. indotta ($\mathcal{E}$) in una spira è proporzionale al tasso di variazione del **flusso magnetico** ($\Phi_{B}$​) che la attraversa. 
Il flusso magnetico è definito come l'integrale del campo magnetico su una data superficie:$$\Phi_{B}​=\int\vec{B}\cdot d\vec{A}$$

La legge di Faraday-Neumann per una bobina con $N$ spire è data da:$$\mathcal{E}=-N \frac{d\Phi_{B}}{dt}$$​​

Il segno negativo è spiegato dalla **legge di Lenz**, che afferma che la corrente indotta si oppone alla variazione del flusso magnetico che l'ha generata.

# Autoinduzione e Induttanza
L'**autoinduzione** è il fenomeno per cui la variazione di corrente in un circuito induce una f.e.m. nel circuito stesso, che si oppone a tale variazione. Questo effetto è dovuto al fatto che il campo magnetico generato dalla corrente del circuito varia al variare della corrente. La f.e.m. autoindotta ($\mathcal{E}_{L}$​) è direttamente proporzionale alla rapidità con cui varia la corrente:$$\mathcal{E}_{L}​=-L \frac{dI}{dt}​$$
La costante di proporzionalità $L$ è chiamata **induttanza** del circuito, la cui unità di misura è l'**Henry** ($H$). L'induttanza di un solenoide, per esempio, dipende dalla sua geometria e dal numero di spire:$$L=\mu_{0} \frac{N^{2}}{l}​A$$
# Circuiti RL
Un **circuito RL** è un circuito in serie contenente un resistore ($R$) e un induttore ($L$). 
Quando si collega una batteria al circuito, la corrente non raggiunge istantaneamente il suo valore massimo, ma cresce esponenzialmente:$$I(t)=\frac{\mathcal{E}}{R}​(1-e^{-t/\tau})$$
La **costante di tempo** del circuito $RL$ è $\tau=L/R$. 
L'induttore immagazzina energia nel suo campo magnetico. L'energia accumulata è data da:$$U_{L}​=\frac{1}{2}​LI^{2}$$

# Circuiti Oscillanti
In un circuito contenente un induttore ($L$) e un condensatore ($C$), l'energia oscilla tra il campo magnetico dell'induttore e il campo elettrico del condensatore. 
Se non c'è resistenza (circuito $LC$ puro), l'energia totale si conserva e le oscillazioni sono armoniche con una pulsazione $\omega=\frac{1}{\sqrt{ LC }}LC​1$​.

In un circuito **RLC** in *serie*, la presenza di una resistenza causa una perdita di energia per effetto Joule. 
Questo porta a un'oscillazione smorzata della carica e della corrente, la cui pulsazione è data da:$$\omega_{d}=\sqrt{ \frac{1}{LC}-\left(\frac{R}{2L}\right)^{2}}$$