[[11 - Moto rotazionale|Lezione Precedente]]
# Momento di una Forza
Il **momento di una forza** $\vec{\tau}$ (o momento torcente) è una grandezza vettoriale che descrive la capacità di una forza di far ruotare un corpo rigido attorno a un asse. 
È definito come il prodotto vettoriale del vettore posizione $Rvec$ e della forza $\vec{F}$:$$\vec{\tau}=\vec{R}\times\vec{F}$$
Il suo modulo è $|\vec{\tau}|=RF\sin\phi$, dove $\phi$ è l'angolo tra il vettore posizione e la forza. 
Un'altra interpretazione utile del modulo è $|\vec{\tau}|=Fd$, dove $d=R\sin\phi$ è il **braccio della forza**, ovvero la distanza perpendicolare tra l'asse di rotazione e la linea d'azione della forza. 
L'unità di misura del momento è il **Newton-metro** ($N\cdot m$).
# Dinamica di un Corpo Rigido
Per un corpo rigido vincolato a ruotare attorno a un asse fisso, la componente del momento torcente lungo quell'asse è ciò che causa la rotazione. 
In generale, il momento totale delle forze esterne applicate a un corpo rigido è uguale alla somma vettoriale dei momenti delle singole forze esterne. 
La relazione fondamentale che lega il momento totale all'accelerazione angolare $\alpha$ è:$$\tau_{Tot,z}​=I_{z}\alpha $$

dove $I_{z}​$ è il **momento d'inerzia** del corpo rispetto all'asse di rotazione. 
Questa equazione è l'equivalente rotazionale della seconda legge della dinamica ($F=ma$).
# Lavoro ed Energia nel Moto Rotazionale
Il **lavoro** svolto da una forza su un corpo rigido in rotazione è dato da:$$W_{Tot}​=\int_{ti}^{​tf}​​\tau_{Tot,z}​(t)\omega(t)dt$$
Per il teorema dell'energia cinetica, il lavoro totale è uguale alla variazione dell'energia cinetica rotazionale:$$W_{tot}​=K_{f}​-K_{i}=\frac{1}{2}​I_{z}​\omega_f^{2}​- \frac{1}{2}​I_{z}\omega_i^2​$$
La **potenza istantanea** erogata dalle forze sul corpo rigido è:$$P(t)=\tau_{Tot,z}​(t)\omega(t)$$
# Equilibrio di un Corpo Rigido
Un corpo rigido è in equilibrio statico se due condizioni sono soddisfatte simultaneamente:
1. La somma vettoriale di tutte le forze esterne è zero (equilibrio traslazionale):$$\sum \vec{F}_{e}​=0$$
2. La somma vettoriale di tutti i momenti delle forze esterne rispetto a un polo arbitrario è zero (equilibrio rotazionale):$$\sum\vec{\tau}_{e}​=0$$
È importante notare che se la prima condizione è soddisfatta, la seconda condizione è valida per qualsiasi polo scelto.

[[13 - Moto rotazionale|Lezione Successiva]]