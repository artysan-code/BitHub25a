[[21 - Potenziale elettrico e capacità|Lezione Precedente]]
# Corrente Elettrica
La **corrente elettrica** è la velocità con cui la carica elettrica fluisce attraverso una superficie. 
La sua unità di misura nel Sistema Internazionale è l'**Ampere** ($A$), dove $1A=\frac{1C}{s}$​. 
Il verso convenzionale della corrente è quello in cui si muovono le cariche positive. 
Nel caso dei conduttori metallici, dove la corrente è generata dal movimento degli elettroni (cariche negative), il verso della corrente è opposto a quello del flusso degli elettroni.

La **velocità di deriva** ($v_{d}$​) è la velocità media con cui si muovono i portatori di carica in un conduttore, e si relaziona alla corrente elettrica ($I$) e alla densità di carica ($n$) tramite l'equazione:$$I=nqv_{d}​A$$dove $q$ è la carica di ciascun portatore e $A$ è l'area della sezione trasversale del conduttore. 
Sebbene i portatori di carica si muovano con una velocità di deriva molto bassa (nell'ordine di $10^{−4} m/s$), la variazione del campo elettrico che li guida si propaga quasi alla velocità della luce, permettendo al movimento di iniziare quasi simultaneamente in tutto il conduttore.

La **densità di corrente** (J) è definita come la corrente per unità di superficie:$$J=\frac{I}{A}​=nqvd_{d}$$

che si misura in $A/m^{2}$.
# Resistenza e Legge di Ohm
I portatori di carica, scontrandosi con gli atomi del conduttore, cedono loro energia. 
Questo causa un aumento dell'energia vibrazionale degli atomi e un conseguente aumento della temperatura del conduttore, noto come **effetto Joule**.

La **legge di Ohm** stabilisce che la corrente ($I$) che fluisce in un conduttore è direttamente proporzionale alla differenza di potenziale ($\Delta V$) applicata ai suoi capi:$$\Delta  V=RI$$dove $R$ è la **resistenza** del conduttore. 
L'unità di misura della resistenza è l'**Ohm** ($\Omega$), dove $\displaystyle1\Omega=1\frac{V}{A}$​.

La resistenza di un conduttore dipende dal materiale, dalla sua geometria e dalla temperatura. 
Per un conduttore ohmico con lunghezza l e sezione $A$, la resistenza è data da:$$R=\rho \frac{l}{A}$$dove $\rho$ è la **resistività** del materiale. 
La resistività si misura in $\Omega \cdot m$ e dipende dalla temperatura secondo la relazione $$\rho =\rho_{0}​[1+\alpha(T-T_{0})]$$L'inverso della resistività è la conducibilità ($\sigma$), per cui $\displaystyle R=\frac{l}{\sigma A}$.
# Potenza nei Circuiti
Quando una carica attraversa un resistore, la sua energia potenziale diminuisce e viene convertita in energia interna del resistore. La **potenza** consumata in un resistore è data da:$$P=I\Delta V$$Utilizzando la legge di Ohm, la potenza può essere espressa anche come:$$P=I^{2}R=\frac{(\Delta V)^{2}}{R}$$
# Sorgenti di F.E.M. e Circuiti RC
Una **sorgente di f.e.m.** (*forza elettromotrice*), come una batteria, è un dispositivo che mantiene una differenza di potenziale costante. 
In una batteria reale, la tensione ai terminali è minore della f.e.m. ideale a causa della **resistenza interna** $(r)$. 
La corrente in un circuito semplice con una batteria e una resistenza di carico $(R)$ è:$$I=\frac{\mathcal{E}}{R+r}$$

Un **circuito RC** contiene una resistenza e un condensatore.
- **Carica del condensatore:** Quando un condensatore scarico si connette a una batteria tramite una resistenza, la carica $q(t)$ sul condensatore e la corrente $I(t)$ nel circuito variano nel tempo.$$\begin{array}{l}
\displaystyle q(t)=C\mathcal{E}[1-e^{-(t/\tau )}] \\
\displaystyle I(t)=\frac{\mathcal{E}}{R}e^{-(t/\tau)}
\end{array}$$dove $\tau =RC$ è la **costante di tempo** del circuito.
- **Scarica del condensatore:** Quando un condensatore carico si scarica attraverso una resistenza, la carica e la corrente diminuiscono esponenzialmente:  $$\begin{array}{l}
\displaystyle q(t)=Qe^{-(t/\tau)} \\
\displaystyle I(t)=-\frac{Q}{RC}​e^{-(t/\tau)}
\end{array}$$Il segno negativo indica che la corrente scorre in verso opposto.
# Leggi di Kirchhoff
Per analizzare circuiti più complessi, si usano le due leggi di Kirchhoff:
1. **Regola dei nodi:** La somma algebrica delle correnti che convergono in un nodo è nulla. (*Principio di conservazione della carica*).
2. **Regola delle maglie:** La somma algebrica delle differenze di potenziale in una maglia chiusa è nulla. (*Principio di conservazione dell'energia*).

[[23 - Forze e campi magnetici|Lezione Succesiva]]