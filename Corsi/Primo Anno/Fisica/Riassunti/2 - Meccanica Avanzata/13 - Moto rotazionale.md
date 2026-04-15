[[12 - Moto rotazionale|Lezione Precedente]]
# Momento Angolare
Il **momento angolare** $\vec{L}(t)$ di un punto materiale è una grandezza vettoriale definita come il prodotto vettoriale del vettore posizione $\vec{R}(t)$ e della quantità di moto $\vec{p}​(t)$:  $$\vec{L}(t)=\vec{R}(t)\times\vec{p}(t)$$
È misurato in $kg\cdot m^{2}/s$ nel S.I. e, per costruzione, è un vettore perpendicolare al piano definito da $\vec{R}(t)$ e $\vec{p}(t)$.

La sua derivata rispetto al tempo è uguale al momento risultante $\vec{\tau}_{r}(t)$ delle forze agenti sul punto materiale, calcolato rispetto allo stesso polo: $$\frac{d\vec{L}(t)}{dt} = \vec{\tau}_r(t)$$Per un sistema di $N$ punti materiali, la variazione del momento angolare totale $\vec{L}_{Tot}(t)$ è data dal momento risultante delle sole forze esterne:$$\frac{d\vec{L}_{Tot}(t)}{dt} = \vec{\tau}_{e,Tot}(t)$$
# Teoremi di König
I teoremi di König forniscono un modo per scomporre il moto di un sistema di punti materiali.
- **Primo Teorema di König:** Il momento angolare totale di un sistema è la somma del momento angolare del centro di massa (come se tutta la massa fosse concentrata lì) e del momento angolare del moto dei singoli corpi rispetto al centro di massa:$$\vec{L}_{\text{Tot}}(t)=\vec{R}_{CM}​(t)\times\vec{P}_{\text{Tot}}​(t)+\vec{L^{'}}(t)$$
- **Secondo Teorema di König:** L'energia cinetica totale di un sistema di corpi è la somma dell'energia cinetica di traslazione del centro di massa e dell'energia cinetica del moto relativo dei corpi rispetto al centro di massa:$$K_{\text{Tot}}​=\frac{1}{2}​M_{\text{Tot}}|\vec{V}_{CM}|^{2}+K^{'}_{\text{Tot}}​$$Per un corpo rigido, l'energia cinetica è $$K_{\text{Tot}}​=\frac{1}{2}M_{\text{Tot}}​|\vec{V}_{CM}​|^{2}+\frac{1}{2}​I_{CM,z^{'}}\ ​\omega^{'2}$$
# Conservazione del Momento Angolare
Dalla seconda equazione cardinale, se il momento risultante delle forze esterne è nullo ($\tau_{e,Tot}​(t)=0$), il momento angolare totale del sistema si conserva. 
Per un corpo rigido in rotazione attorno a un asse z con momento d'inerzia $I_{z}$​, la relazione è:$$I_{z}​\omega =costante$$

Ciò significa che se il momento d'inerzia diminuisce, la velocità angolare aumenta (e viceversa), come nell'esempio di un pattinatore sul ghiaccio che stringe le braccia.
# Moto di una Trottola
Il moto di una trottola è un esempio di **precessione**, dove l'asse di rotazione della trottola ruota a sua volta attorno a un asse verticale. 
Questo fenomeno è causato dal momento della forza peso rispetto al punto d'appoggio. 
La velocità angolare di precessione $\omega_{p}$​ è data approssimativamente da:$$\omega_{p}\simeq \frac{Mg|RCM​|}{I_{z^{'}}​\omega^{'}}​$$

dove $I_{z^{'}}​$ è il momento d'inerzia della trottola rispetto al proprio asse di rotazione e $\omega^{'}$ è la sua velocità angolare di rotazione.
# Moto di Puro Rotolamento
Il puro rotolamento di un corpo rigido (come una sfera o un disco) su una superficie piana avviene senza strisciamento. 
La condizione per questo moto è che la velocità del punto di contatto sia nulla. 
Questo si traduce nella relazione tra la velocità del centro di massa $V_{CM}$​ e la velocità angolare $\omega$: $$V_{CM}​=\omega R$$

dove $R$ è il raggio del corpo. 
Poiché l'attrito che agisce è statico, non viene compiuto lavoro e l'energia meccanica si conserva. L'energia cinetica totale in questo tipo di moto è:$$K(t)=\frac{1}{2}​\left( M+\frac{I_{z^{'}}}{R^{2}}​​ \right)|\vec{V}_{CM​}|^{2}$$

[[14 - Moto oscillatorio e onde|Lezione Successiva]]