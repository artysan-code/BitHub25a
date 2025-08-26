[[7 - Applicazioni leggi del moto|Lezione Precedente]]

Questa appendice illustra i metodi matematici per risolvere le equazioni differenziali che descrivono il moto di un punto materiale sotto l'azione della forza peso e di una forza di attrito viscoso. 
Questo tipo di attrito si verifica quando un corpo si muove in un fluido (es. aria, acqua).

Nel caso di attrito viscoso proporzionale alla velocità $(F_{R}=-bv)$, l'equazione del moto è:$$v_{x}^{'}​(t)=g- \frac{b}{m}​v_{x}​(t)$$La soluzione di questa equazione, con la condizione iniziale di velocità nulla, è:$$v_{x}(t)=\frac{mg}{b}​\left( 1-e^{-\frac{b}{m}​t} \right)$$In questo caso, la velocità del corpo tende asintoticamente a un valore massimo, chiamato **velocità limite** $\left( V_L​=\frac{mg}{b}​ \right)$. 
La costante di tempo $\tau=\frac{m}{b}$​ determina la rapidità con cui la velocità si avvicina a $V_{L}$​. 
Un esempio pratico è la caduta di una goccia di pioggia in atmosfera: inizialmente accelera, ma poi raggiunge una velocità di regime a causa dell'attrito dell'aria.

Nel caso di attrito viscoso proporzionale al quadrato della velocità $\left( F_{R}=-\frac{1}{2}D\rho Av^{2} \right)$, la velocità limite è $\displaystyle V_{L}​=\sqrt{\frac{2mg}{D\rho A}}$​​ e la soluzione dell'equazione differenziale non lineare è data dalla funzione tangente iperbolica:$$v_{x}​(t)=VL_{L}\tanh\left(​\frac{gt​}{V_{L}}\right)$$

[[8 - Lavoro ed energia|Lezione Successiva]]
