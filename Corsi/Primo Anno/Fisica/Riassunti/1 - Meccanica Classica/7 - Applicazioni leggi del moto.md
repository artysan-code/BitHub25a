[[6 - Leggi del moto|Lezione Precedente]]
# Forze di Attrito
L'**attrito** è una forza che si oppone al movimento relativo tra due superfici a contatto. Esistono due tipi principali di attrito:
- *Forza di attrito statico* ($F_s$​): 
  Agisce su un corpo fermo, opponendosi a qualsiasi forza applicata che tenti di metterlo in moto. 
  Sperimentalmente, si osserva che il suo modulo aumenta con l'aumentare della forza applicata, fino a raggiungere un valore massimo.$$Fs​\leq \mu_{s}​N$$dove N è la forza normale (perpendicolare alla superficie) e $\mu_s$​ è il **coefficiente di attrito statico**, una costante adimensionale che dipende dai materiali a contatto.
- *Forza di attrito dinamico* ($F_{}d$​): 
  Agisce su un corpo in movimento, opponendosi alla sua direzione di moto. 
  Il suo modulo è generalmente costante e inferiore al valore massimo dell'attrito statico.$$F_d​=\mu_d​N$$dove $\mu_d$​ è il **coefficiente di attrito dinamico**. 
  In generale, $\mu_d​<\mu_s$​.

Un'altra forma di attrito è l'**attrito viscoso**, che si manifesta quando un corpo si muove in un fluido. 
Questo tipo di attrito dipende dalla velocità del corpo, e può essere proporzionale alla velocità stessa o al suo quadrato. 
L'equazione del moto per un corpo in caduta con attrito viscoso è:$$a_x​(t)=g- \frac{D\rho A}{2m}(v_x​(t))^2$$
# Dinamica del Moto Circolare Uniforme
Quando un corpo si muove di moto circolare uniforme, la sua velocità vettoriale cambia continuamente direzione, anche se il suo modulo rimane costante. 
Questo implica un'accelerazione, chiamata **accelerazione centripeta**, diretta verso il centro della traiettoria circolare: $$a_c = \frac{v^2}{r}$$Per la seconda legge della dinamica, un'accelerazione di questo tipo deve essere causata da una forza risultante, detta **forza centripeta**, che agisce anch'essa in direzione radiale verso il centro:$$F_c​=ma_c​=m\frac{v^2}{r}​$$
Questa forza non è un nuovo tipo di forza, ma è il risultato dell'applicazione di altre forze (ad esempio, la tensione di un filo, la forza di attrito o la reazione normale del piano) che costringono il corpo a seguire una traiettoria curva.
## Esempio: Auto in Curva
Quando un'auto percorre una curva su una strada piana, è la forza di attrito statico tra i pneumatici e l'asfalto a fornire la necessaria forza centripeta. La velocità massima che l'auto può raggiungere senza sbandare è limitata da questa forza:$$v_{max}​=\sqrt{\mu_s​gr​}$$Se la curva è sopraelevata (rialzata), la componente orizzontale della forza normale può contribuire alla forza centripeta, permettendo di percorrere la curva a velocità maggiori anche in assenza di attrito.
# Forze Apparenti e Sistemi di Riferimento
Quando si descrive il moto di un corpo da un **sistema di riferimento non inerziale** (cioè, un sistema accelerato), è necessario introdurre delle **forze apparenti** (o fittizie) per applicare le leggi di Newton. 
Queste forze non hanno un'origine fisica reale, ma sono un "artefatto" matematico legato all'accelerazione del sistema di riferimento. 
La relazione tra la forza risultante in un sistema inerziale $(\vec{F}_{ris,o}​)$ e quella in un sistema non inerziale $(\vec{F}_{ris,o′}​)$ è:$$\vec{F}_{ris,o'}​=\vec{F}_{ris,o​}-m\vec{a}_{oo'​}$$dove $a_{oo'}$​ è l'accelerazione del sistema non inerziale rispetto a quello inerziale. 
La forza apparente è quindi $F_a​=-ma_{oo'}​$.

Esempi di forze apparenti includono:
- **Forza centrifuga**:
  Avvertita in un sistema di riferimento rotante, spinge i corpi verso l'esterno della traiettoria circolare.
- **Forza di Coriolis**:
  Agisce su un corpo in movimento all'interno di un sistema di riferimento rotante e ne devia la traiettoria.

[[7A - Equazioni differenziali attrito viscoso|Lezione Successiva]]
[[Eserciziario#^4a3424|Esercizi svolti sul capitolo]]