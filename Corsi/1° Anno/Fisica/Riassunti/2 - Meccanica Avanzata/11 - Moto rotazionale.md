[[10 - Quantità di moto e sistemi|Lezione Precedente]]
# Corpo Rigido e Moto Angolare
Un **corpo rigido** è un sistema di punti materiali in cui le distanze relative tra i punti rimangono fisse. 
A differenza di un punto materiale, i diversi punti di un corpo rigido in rotazione hanno velocità vettoriali diverse. 
Per descrivere il moto di un corpo rigido attorno a un asse fisso, si usano grandezze angolari.
- **Posizione Angolare** ($\theta$): L'*angolo* che un punto del corpo forma con una semiretta di riferimento. 
  Si misura in radianti.
- **Velocità Angolare** ($\omega$): La rapidità di *variazione della posizione angolare*. 
  È la derivata prima della posizione angolare rispetto al tempo, $\displaystyle\omega(t)=\frac{d\theta}{dt}​$. 
  Si misura in radianti al secondo ($rad/s$).
- **Accelerazione Angolare** ($\alpha$): La *rapidità di variazione della velocità angolare*. 
  È la derivata seconda della posizione angolare rispetto al tempo, $\displaystyle\alpha(t)=\frac{d\omega}{dt}​=\frac{d^{2}\theta​}{dt^{2}}$. 
  Si misura in radianti al secondo quadrato ($rad/s^{2}$).

Se l'asse di rotazione è fisso, $\omega$ e $\alpha$ sono le stesse per tutti i punti del corpo rigido. 
La direzione dei vettori $\omega$ e $\alpha$ è lungo l'asse di rotazione, e il loro verso si determina con la regola della mano destra.
# Relazioni Cinematiche
Nel caso di un'accelerazione angolare costante, le equazioni che descrivono il moto rotazionale sono analoghe a quelle del moto rettilineo uniformemente accelerato:
- **Velocità angolare in funzione del tempo**:$$\omega(t)=\omega_{0}​+\alpha t$$
- **Posizione angolare in funzione del tempo**:$$\theta(t)=\theta_{0}​+\omega_{0}​t+\frac{1}{2}​\alpha t^{2}$$
- **Velocità angolare in funzione della posizione**:$$\omega(t)^{2}=\omega_{0}^{2}​+2\alpha(\theta(t)−\theta_{0}​)$$
# Momento d'Inerzia ed Energia Cinetica Rotazionale
Il **momento d'inerzia** ($I_{z}$​) è una grandezza scalare che rappresenta la resistenza di un corpo alla variazione del suo stato di moto rotazionale. 
Dipende dalla distribuzione della massa del corpo rispetto all'asse di rotazione. 
Per un sistema di $N$ punti materiali, il momento d'inerzia è:$$I_{z}​=\sum_{i=1}^{N}m_{i}r_{i}^{2}​$$
dove $m_{i}$​ è la massa del punto $i$ e $r_{i}$​ è la sua distanza dall'asse di rotazione. 
Per un corpo continuo, la sommatoria diventa un integrale. 
L'unità di misura è il $kg\cdot m^{2}$.

L'**energia cinetica rotazionale** ($K$) è l'energia che un corpo rigido possiede a causa della sua rotazione. 
È direttamente proporzionale al momento d'inerzia e al quadrato della velocità angolare:$$K=\frac{1}{2}​I_{z}\omega^{2}$$
Il **Teorema di Huygens-Steiner** (o degli assi paralleli) permette di calcolare il momento d'inerzia di un corpo rispetto a un asse qualsiasi, purché si conosca il momento d'inerzia rispetto a un asse parallelo passante per il centro di massa:$$I_{z}=I_{z,CM}​+M_{Tot}​d^{2}$$

dove $I_{z,CM}$​ è il momento d'inerzia rispetto all'asse passante per il centro di massa, $M_{Tot}$​ è la massa totale del corpo e $d$ è la distanza tra i due assi paralleli.

[[12 - Moto rotazionale|Lezione Successiva]]