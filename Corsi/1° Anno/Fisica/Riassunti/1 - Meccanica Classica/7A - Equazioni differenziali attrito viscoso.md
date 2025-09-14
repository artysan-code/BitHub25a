[[7 - Applicazioni leggi del moto|Lezione Precedente]]
# Attrito Viscoso e Caduta di un Corpo
In molti problemi di dinamica, specialmente quando un corpo si muove in un fluido come l'aria o l'acqua, oltre alla forza di gravità, è presente una forza di attrito viscoso. 
Questa forza dipende dalla velocità del corpo.

Analizziamo i due casi principali di forza di attrito viscoso e i relativi metodi di risoluzione delle equazioni differenziali del moto:
1. **Forza di attrito proporzionale alla velocità**: 
   La forza di attrito è data da $\vec{F}_a​=-b\vec{v}$, dove $b$ è una costante di attrito.
2. **Forza di attrito proporzionale al quadrato della velocità**: 
   La forza di attrito è data da $\vec{F}_a​=-\frac{1}{2}​D\rho A|\vec{v}|^2\hat{v}$, dove $D$ è il coefficiente di drag, $\rho$ la densità del fluido e $A$ l'area della sezione trasversale del corpo.
## Caso 1: Attrito Proporzionale alla Velocità
L'equazione differenziale del moto per un corpo che cade sotto l'azione della gravità e di una forza di attrito viscoso proporzionale alla velocità è:$$v_x'(t)=g-\frac{b}{m}​v_x​(t)$$

con la condizione iniziale $v_x​(0)=0$.

Questa equazione può essere risolta con il metodo della **separazione delle variabili** o come un'equazione differenziale lineare del primo ordine. La soluzione generale che descrive la velocità del corpo in funzione del tempo è:$$v_x​(t)=\frac{mg​}{b}\left( 1-e^{-\frac{b}{m}t} \right)=V_L​(1-e^{-t/\tau})$$
dove:
- $V_L​= \frac{mg}{b}$​ è la **velocità limite** (o velocità terminale), che il corpo raggiunge asintoticamente quando l'accelerazione diventa nulla.
- $\tau=\frac{m}{b}$ è la **costante di tempo**, che determina la rapidità con cui il corpo si avvicina alla velocità limite.
## Caso 2: Attrito Proporzionale al Quadrato della Velocità
L'equazione differenziale del moto in questo caso è non lineare:$$v_x'(t)=g-\frac{D\rho A​}{2m}(v_x​(t))^2$$
con la condizione iniziale $v_x​(0)=0$.

La risoluzione di questa equazione richiede un approccio più complesso, in particolare l'uso del metodo della separazione delle variabili e la decomposizione in fratti semplici per l'integrazione. 
La soluzione è data da:$$v_x​(t)=\sqrt{\frac{2mg​​}{D\rho A}}\tanh\left( \frac{g​}{V_L​}t \right)=V_L\tanh\left( \frac{g}{V_{L}}​t \right)$$

dove $V_L​=\sqrt{ \frac{2mg}{D\rho A} }$​​ è la velocità limite per questa specifica legge di attrito. 
Anche in questo caso, la velocità del corpo si avvicina asintoticamente alla velocità limite nel tempo.

[[8 - Lavoro ed energia|Lezione Successiva]]
