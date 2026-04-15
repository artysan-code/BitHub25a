[[9 - Energia potenziale e forze conservatrici|Lezione Precedente]]
# Quantità di Moto e Conservazione
La **quantità di moto** $\vec{p}$​ di un corpo è una grandezza vettoriale definita come il prodotto della sua massa $m$ e della sua velocità istantanea $\vec{v}$:$$\vec{p}​=m\vec{v}$$
L'unità di misura è $kg\cdot m/s$.
Questa grandezza è fondamentale per descrivere il movimento di un corpo, in quanto tiene conto non solo della sua velocità, ma anche della sua massa, che rappresenta l'inerzia del corpo al movimento. 
In termini concettuali, la quantità di moto è ciò che rende un oggetto in movimento difficile da fermare.
Un camion in movimento a bassa velocità può avere una quantità di moto maggiore di una pallina da tennis lanciata ad alta velocità, semplicemente a causa della sua massa enormemente superiore.

La seconda legge della dinamica può essere espressa in una forma più generale, valida anche per corpi con massa variabile:$$\vec{F}_{ris}​=\frac{d\vec{p}}{dt}$$​​
Questo significa che la forza risultante su un corpo è uguale alla derivata temporale della sua quantità di moto. 
Se la massa di un corpo è costante, questa equazione si riduce alla familiare formula $\vec{F}_{ris}​=m\vec{a}$.
Tuttavia, la formulazione in termini di quantità di moto è più completa e universalmente applicabile.

Un principio fondamentale è la **legge di conservazione della quantità di moto**: 
in un **sistema isolato** (su cui la forza esterna totale è nulla), la quantità di moto totale del sistema si conserva. 
Questo significa che la quantità di moto totale del sistema rimane costante nel tempo, indipendentemente dalle interazioni interne tra i suoi componenti.$$\vec{P}_{tot​}=\sum_{i=1}^{N}​\vec{p}_{i}​=\text{costante}$$
Questo principio è una diretta conseguenza della terza legge di Newton (azione e reazione). 
Le forze che i corpi del sistema si scambiano a vicenda sono forze interne, che, sommate vettorialmente, si annullano a coppie. 
Pertanto, la loro variazione totale di quantità di moto è zero. 
È un concetto potente, che si applica in molti scenari, dagli scontri tra automobili al rinculo di un'arma da fuoco, dove la quantità di moto del proiettile è uguale e opposta a quella dell'arma e della persona che la impugna.
# Impulso e Urti
L'**impulso** I di una forza risultante $F_{ris}$​ su un corpo durante un intervallo di tempo $\Delta t$ è uguale alla variazione della quantità di moto del corpo nello stesso intervallo di tempo:$$\vec{I}=\int_{t_{i}​}^{t_{f}}​​\vec{F}_{ris}​(t)dt=\Delta \vec{p}​$$
L'impulso è una misura dell'effetto cumulativo di una forza nel tempo. 
È particolarmente utile quando si analizzano forze che agiscono per brevi periodi, come negli urti. 
Ad esempio, quando una mazza da baseball colpisce una palla, la forza impulsiva applicata è molto grande per un tempo molto breve, ma la variazione della quantità di moto della palla (e quindi la sua velocità finale) è direttamente proporzionale all'impulso totale ricevuto.

Gli **urti** sono interazioni tra corpi che avvengono in un intervallo di tempo molto breve, durante il quale le forze interne sono molto più grandi delle forze esterne. 
Durante un urto, la quantità di moto totale del sistema si conserva, a meno che non intervengano forze esterne significative. 
In base alla conservazione dell'energia cinetica, gli urti si classificano in:
- **Urto anelastico**: 
  L'energia cinetica totale non si conserva, perché una parte dell'energia viene convertita in altre forme, come calore, suono o deformazione permanente dei corpi. 
  Se i corpi restano uniti dopo l'urto, si parla di **urto totalmente anelastico**. 
  Un esempio comune è un'auto che tampona un'altra e le due vetture si incastrano, muovendosi insieme dopo la collisione. 
  In questo caso, l'energia cinetica finale è minore di quella iniziale.
- **Urto elastico**: 
  Sia la quantità di moto che l'energia cinetica totale si conservano. 
  Questi urti sono idealizzati e si avvicinano a quelli tra particelle subatomiche o tra sfere perfettamente rigide. 
  Un esempio classico è la collisione tra due palle da biliardo, in cui l'energia e la quantità di moto vengono trasferite con perdite minime.
# Centro di Massa
Il **centro di massa** è un punto geometrico che rappresenta la media ponderata delle posizioni di tutti i punti materiali di un sistema, pesata per le loro masse. È il punto in cui, a tutti gli effetti, si può considerare concentrata tutta la massa di un corpo o di un sistema per analizzare la sua traslazione. Per un sistema di N particelle, la posizione del centro di massa è data da:$$\vec{r}_{CM}​=​\frac{\sum_{i=1}^N​m_{i}​\vec{r}_{i}}{\sum_{i=1}^N​m_{i}}$$​​

La velocità e l'accelerazione del centro di massa sono date da:$$\begin{array}{l}
\displaystyle\vec{v}_{CM}=\frac{\vec{P}_{Tot}}{M_{Tot}} \\
\displaystyle\vec{a}_{CM}=\frac{\vec{F}_{e,Tot}}{M_{Tot}}
\end{array}$$
La **prima equazione cardinale della dinamica** afferma che l'accelerazione del centro di massa è determinata unicamente dalla forza esterna totale che agisce sul sistema. 
Questo è un concetto cruciale: il moto del centro di massa di un sistema è indipendente dalle forze interne. 
Ad esempio, se un proiettile esplode a mezz'aria, i suoi frammenti si disperderanno, ma il centro di massa di tutti i frammenti continuerà a seguire la stessa traiettoria parabolica che avrebbe avuto il proiettile intatto.
# Sistemi a Massa Variabile
In un sistema in cui la massa varia nel tempo (come un razzo che espelle propellente), la forza di spinta non è generata da un'interazione con un oggetto esterno, ma dalla conservazione della quantità di moto del sistema stesso (razzo + carburante). 
La forza di spinta è proporzionale alla velocità di espulsione del propellente rispetto al razzo e alla velocità di combustione (cioè, la variazione di massa nel tempo). 
Questo fenomeno è descritto dall'equazione del razzo di Tsiolkovsky, che lega la variazione di velocità del razzo alla massa espulsa. 
La variazione di velocità di un razzo è descritta dalla legge:$$V_{f}-V_{i}​=V_{e}​\ln\left(​\frac{M_{i}}{M_{f}}​​\right)$$dove $V_{e}$​ è la velocità di espulsione del propellente, $M_{i}​$ è la massa iniziale totale del razzo e $M_{f}$​ è la massa finale dopo che una certa quantità di propellente è stata espulsa. 
Questo dimostra come un sistema possa cambiare la propria velocità anche in assenza di forze esterne, semplicemente variando la propria massa.

[[11 - Moto rotazionale|Lezione Successiva]]
[[Eserciziario#^68fa33|Esercizi svolti sul capitolo]]
[[20 - Forza elettrica e campo elettrico|Prossimo Macro Argomento]]