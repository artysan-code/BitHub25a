# File: b-Esercizi Moto Bidimensionale
### Esercizio 1 (Serway 1.73)

Un cannoncino a molla si trova sul bordo di un tavolo, a un'altezza di **1,2 m** dal pavimento. Il cannoncino spara orizzontalmente una biglia di acciaio con una velocità vettoriale istantanea di modulo $v_{i}​$ e un alzo di 35°.
**Domande:** 
a) Si trovi, in funzione di vi​, la posizione orizzontale della pallina nell'istante in cui questa colpisce il pavimento. Si chiami $x(v_{i}​)$ questa funzione.
b) Si dia il valore di $x$ per $\displaystyle v_{i}=0,1\frac{m}{s}$
c) si dia il valore di $x$ per $\displaystyle v_{i}=100\frac{m}{s}$​.
d) Si faccia l'ipotesi che vi​ sia molto piccola ma non esattamente zero. Si mostri che in questo caso uno dei termini che appaiono nel risultato *a)* diviene dominante, per cui la forma di $x(v_{i}​)$ si semplifica.
e) Nel caso in cui $v_{i}​$ sia molto grande, qual è la forma approssimata di $x(v_{i})$?
f) Si descriva la forma generale della curva $x(v_{i}​)$
#### Soluzione
##### a)Posizione orizzontale x(vi​)
Dati del problema:
$h=1,2 m\quad\quad\theta_{i}​=35\quad\quad v_{i}​$
Le equazioni del moto per la pallina sono:$$\begin{cases} x(t) = (v_i \cos \theta_i) t \\ y(t) = h + (v_i \sin \theta_i) t - \frac{1}{2}gt^2 \end{cases} $$Ricaviamo il tempo $t$ dalla prima equazione: $$ t = \frac{x(t)}{v_i \cos \theta_i} $$Sostituiamo questa espressione per $t$ nella seconda equazione per ottenere l'equazione della traiettoria: $$ y(x) = h + (v_i \sin \theta_i) \left(\frac{x(t)}{v_i \cos \theta_i}\right) - \frac{1}{2}g \left(\frac{x(t)}{v_i \cos \theta_i}\right)^2 $$$$ y(x) = h + (\tan \theta_i) x(t) - \frac{g}{2 v_\hat{i}2 \cos^2 \theta_i} x(t)^2$$ La pallina colpisce il pavimento quando $y(t) = 0$. Dobbiamo quindi risolvere la seguente equazione di secondo grado in $x(t)$:  $$\frac{g}{2 v_\hat{i}2 \cos^2 \theta_i} x(t)^2 - (\tan \theta_i) x(t) - h = 0$$ Riordinando i termini, si ottiene: $$x(t)^2 - \left(\frac{2 v_\hat{i}2 \sin \theta_i \cos \theta_i}{g}\right) x(t) - \frac{2h v_\hat{i}2 \cos^2 \theta_i}{g} = 0$$ Risolvendo con la formula quadratica e scegliendo la radice positiva (poiché la posizione orizzontale non può essere negativa), si ottiene: $$x(v_i) = \frac{v_\hat{i}2 \sin \theta_i \cos \theta_i}{g} + \sqrt{\left(\frac{v_\hat{i}2 \sin \theta_i \cos \theta_i}{g}\right)^2 + \frac{2h v_\hat{i}2 \cos^2 \theta_i}{g}}$$ Questa espressione può essere riscritta in una forma più compatta: $$x(v_i) = \frac{v_\hat{i}2 \sin \theta_i \cos \theta_i}{g} \left[ 1 + \sqrt{1 + \frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}} \right]$$ 
##### b) Calcolo per $v_i = 0,1 \ m/s$ 
Sostituendo i valori numerici, si ottiene: $$x(0,1 \ m/s) = 0,041 \ m = 4,1 \ cm$$ 
#####  c) Calcolo per $v_i = 100 \ m/s$ 
Sostituendo i valori numerici, si ottiene: $$x(100 \ m/s) = 9960 \ m$$ 
##### d) Comportamento per $v_i$ molto piccola 
Se $v_i$ è molto piccola, il termine $\displaystyle\frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}$ dentro la radice quadrata diventa molto grande. L'espressione si semplifica come segue:  $$\sqrt{1 + \frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}} \approx \sqrt{\frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}} = \frac{\sqrt{2gh}}{v_i \sin \theta_i}$$ Sostituendo questa approssimazione in $x(v_i)$: $$x(v_i) \approx \frac{v_\hat{i}2 \sin \theta_i \cos \theta_i}{g} \left( \frac{\sqrt{2gh}}{v_i \sin \theta_i} \right) = v_i \cos \theta_i \sqrt{\frac{2h}{g}}$$ L'andamento è **lineare** con $v_i$. 
##### e) Comportamento per $v_i$ molto grande 
Se $v_i$ è molto grande, il termine $\displaystyle\frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}$ diventa molto piccolo. L'espressione si semplifica come segue: $$\sqrt{1 + \frac{2gh}{v_\hat{i}2 \sin^2 \theta_i}} + 1 \approx \sqrt{1} + 1 = 2$$ Sostituendo questa approssimazione in $x(v_i)$: $$x(v_i) \approx \frac{v_\hat{i}2 \sin \theta_i \cos \theta_i}{g} (2) = \frac{v_\hat{i}2 \sin(2\theta_i)}{g}$$ L'andamento è **parabolico** (quadratico) con $v_i$. 
##### f) Forma generale della curva $x(v_i)$ 
La funzione $x(v_i)$ ha un andamento che inizia in modo lineare per valori bassi di $v_i$ e diventa progressivamente parabolico per valori alti di $v_i$. 
### Esercizio 2 (Serway, n. 74) 
Un giocatore di baseball lancia la palla al ricevitore. La palla rimbalza una volta prima di raggiungerlo. Si suppone che l'angolo con cui la palla rimbalza sia uguale all'angolo di impatto, ma che il modulo della velocità dopo il rimbalzo si dimezzi. 
**Domande:** 
a) Assumendo che la palla venga sempre lanciata con la stessa velocità iniziale $v_0$, quale angolo $\theta$ di lancio permette di raggiungere, con un solo rimbalzo, la stessa distanza orizzontale $D$ raggiunta senza rimbalzi da una palla lanciata a 45°? 
b) Si determini il rapporto dei tempi di volo tra il percorso con un rimbalzo e quello senza rimbalzi. 
#### **Soluzione** 
##### **a) Angolo di lancio per gittata uguale** 
La gittata $D_1$ di un proiettile lanciato a 45° senza rimbalzi è la gittata massima: $$D_1 = \frac{v_0^2 \sin(2 \cdot 45^\circ)}{g} = \frac{v_0^2}{g}$$ Il percorso con un rimbalzo $D_2$ è la somma di due gittate: la prima con velocità $v_0$ e angolo $\theta$, la seconda con velocità $v_0/2$ e stesso angolo $\theta$: $$D_2 = \frac{v_0^2 \sin(2\theta)}{g} + \frac{(v_0/2)^2 \sin(2\theta)}{g} = \frac{v_0^2 \sin(2\theta)}{g} \left(1 + \frac{1}{4}\right) = \frac{5v_0^2}{4g} \sin(2\theta)$$ Imponendo $D_1 = D_2$: $$\frac{v_0^2}{g} = \frac{5v_0^2}{4g} \sin(2\theta)$$ Da cui si ricava: $$\sin(2\theta) = \frac{4}{5}$$ $$2\theta = \arcsin(0.8) \Rightarrow \theta = 26,6^\circ$$
##### **b) Rapporto dei tempi di volo** 
Il tempo di volo totale per un proiettile su terreno piano è $T = \frac{2v_{0y}}{g} = \frac{2v_0 \sin\theta}{g}$.* **Tempo di volo con un rimbalzo ($T_{tot,a}$):** È la somma dei tempi di volo del primo e del secondo arco. * Tempo primo arco: $T_1 = \frac{2v_0 \sin\theta}{g}$ * Tempo secondo arco (velocità iniziale $v_0/2$): $T_2 = \frac{2(v_0/2) \sin\theta}{g} = \frac{v_0 \sin\theta}{g}$ * Tempo totale: $T_{tot,a} = T_1 + T_2 = \frac{3v_0 \sin\theta}{g}$ * **Tempo di volo senza rimbalzi ($T_{tot,b}$):** Corrisponde al lancio a 45°. $$T_{tot,b} = \frac{2v_0 \sin(45^\circ)}{g}$$ Il rapporto è: $$\frac{T_{tot,a}}{T_{tot,b}} = \frac{3v_0 \sin\theta / g}{2v_0 \sin(45^\circ) / g} = \frac{3 \sin\theta}{2 \sin(45^\circ)}$$ Per calcolarlo, ci serve $\sin\theta$. Sapendo che $\sin(2\theta)=4/5$, usiamo le formule trigonometriche: * $\cos(2\theta) = \sqrt{1 - \sin^2(2\theta)} = \sqrt{1 - (4/5)^2} = 3/5$ * $\sin\theta = \sqrt{\frac{1-\cos(2\theta)}{2}} = \sqrt{\frac{1-3/5}{2}} = \frac{1}{\sqrt{5}}$ * $\sin(45^\circ) = \frac{1}{\sqrt{2}}$ Sostituendo nel rapporto: $$\frac{T_{tot,a}}{T_{tot,b}} = \frac{3}{2} \cdot \frac{1/\sqrt{5}}{1/\sqrt{2}} = \frac{3\sqrt{2}}{2\sqrt{5}} = \frac{3}{\sqrt{10}} \approx 0,95$$ La traiettoria con un rimbalzo è quindi più rapida di quella senza rimbalzi a gittata massima. 
### Esercizio 3 (Serway n. 78) 
Wile E. Coyote indossa pattini a rotelle a propulsione che forniscono un'accelerazione orizzontale costante di $15 \ m/s^2$. 
Il Coyote parte da fermo da un punto posto a 70 m dal ciglio di un burrone, nell'istante in cui Beep Beep gli passa davanti correndo verso il burrone. 
**Domande:**
a) Quale deve essere la velocità costante minima che Beep Beep deve mantenere per arrivare all'orlo del burrone prima del Coyote? 
b) Arrivato al ciglio, il Coyote continua dritto nel vuoto. La sua accelerazione in volo è $\vec{a} = (15\hat{i} - 9,81\hat{j}) \frac{m}{s^2}$. Se il burrone è profondo 100 m, a che distanza dalla parete verticale atterra il Coyote? 
c) Si determinino le componenti della velocità del Coyote nell'istante del suo impatto con il fondo. 
#### **Soluzione**
##### **a) Velocità minima di Beep Beep** 
Calcoliamo il tempo $t_1$ che impiega il Coyote per percorrere $l = 70 \ m$ con accelerazione $a_x = 15 \ m/s^2$ partendo da fermo: $$l = \frac{1}{2} a_x t_1^2 \Rightarrow t_1 = \sqrt{\frac{2l}{a_x}} = \sqrt{\frac{2 \cdot 70}{15}} \approx 3,055 \ s$$ Affinché Beep Beep arrivi prima del Coyote, il suo tempo di percorrenza $t_2$ deve essere minore di $t_1$.  Se la velocità di Beep Beep è $v_{BB}$: $$t_2 = \frac{l}{v_{BB}} < t_1$$ $$v_{BB} > \frac{l}{t_1} = \frac{l}{\sqrt{2l/a_x}} = \sqrt{\frac{l^2 a_x}{2l}} = \sqrt{\frac{la_x}{2}}$$  $$v_{BB} > \sqrt{\frac{70 \cdot 15}{2}} = \sqrt{525} \approx 22,91 \ m/s$$
##### **b) Distanza di atterraggio del Coyote** 
Prima, calcoliamo la velocità orizzontale del Coyote, $v_{x,1}$, quando raggiunge il ciglio del burrone: $$v_{x,1} = a_x t_1 = \sqrt{2la_x} = \sqrt{2 \cdot 70 \cdot 15} = \sqrt{2100} \approx 45,83 \ m/s$$ Ora analizziamo il moto in volo, con $H=100 \ m$. L'equazione per il moto verticale è:$$y(t) = H + \frac{1}{2} a_y t^2$$ Il Coyote atterra quando $y(t_3) = 0$. Il tempo di caduta $t_3$ è: $$0 = H - \frac{1}{2} |a_y| t_3^2 \Rightarrow t_3 = \sqrt{\frac{2H}{|a_y|}} = \sqrt{\frac{2 \cdot 100}{9,81}} \approx 4,51 \ s$$  La distanza orizzontale percorsa in questo tempo è: $$x(t_3) = v_{x,1} t_3 + \frac{1}{2} a_x t_3^2 = \sqrt{2la_x} \sqrt{\frac{2H}{|a_y|}} + \frac{1}{2} a_x \left(\frac{2H}{|a_y|}\right)$$ $$x(t_3) = 2\sqrt{\frac{la_x H}{|a_y|}} + \frac{a_x H}{|a_y|}$$ Sostituendo i valori: $$x(t_3) = 2\sqrt{\frac{70 \cdot 15 \cdot 100}{9,81}} + \frac{15 \cdot 100}{9,81} \approx 207,5 + 152,9 = 359,82 \ m$$
##### **c) Componenti della velocità all'impatto** 
Le componenti della velocità al tempo $t_3$ sono: 
**Componente orizzontale:** $$v_x(t_3) = v_{x,1} + a_x t_3 = \sqrt{2la_x} + a_x \sqrt{\frac{2H}{|a_y|}}$$ $$v_x(t_3) = \sqrt{2100} + 15 \sqrt{\frac{200}{9,81}} \approx 45,83 + 67,7 = 113,53 \ m/s$$  **Componente verticale:** $$v_y(t_3) = a_y t_3 = -|a_y| \sqrt{\frac{2H}{|a_y|}} = -\sqrt{2|a_y|H}$$ $$v_y(t_3) = -\sqrt{2 \cdot 9,81 \cdot 100} = -\sqrt{1962} \approx -44,29 \ m/s$$
# File: c-Esercizi Leggi Del Moto 
### Esercizio 1 (Serway, n. 85) 
Un corpo di massa M è mantenuto in posizione da una forza $\vec{F}$ e da un sistema di pulegge ideali (prive di massa e attrito), come mostrato in figura. 
**Domande:** 
a) Disegnare i diagrammi delle forze agenti su ogni puleggia. 
b) Determinare le tensioni in ciascun tratto di corda (1, 2, 3, 4) e la forza di reazione nel punto di sostegno 5. 
c) Determinare il modulo della forza $\vec{F}$. 
#### **Soluzione** 
##### **a) Diagrammi delle forze**
**Puleggia inferiore:** Su di essa agiscono verso l'alto le tensioni dei due tratti di corda che la sorreggono (che chiameremo $T_{corda}$), e verso il basso la tensione $T_4$ del filo che sostiene la massa M. All'equilibrio: $T_4 = 2 T_{corda}$. 
**Puleggia superiore:** Su di essa agiscono verso il basso le tensioni dei tre tratti di corda ($T_1$, $T_2$, $T_3$) e verso l'alto la reazione del sostegno $R_5$. All'equilibrio: $R_5 = T_1 + T_2 + T_3$.

##### **b) e c) Calcolo delle tensioni e della forza F** 
Dato che la corda è unica e le pulegge sono ideali, la tensione è la stessa in tutti i suoi segmenti. Chiamiamola $T$. $$T = |\vec{F}| = T_1 = T_2 = T_3$$ Analizziamo l'equilibrio della massa M e della puleggia inferiore: 
1. **Corpo M:** La tensione $T_4$ nel filo che lo sostiene deve equilibrare il suo peso. $$T_4 = Mg$$
2. **Puleggia inferiore:** La tensione $T_4$ verso il basso è bilanciata dalle tensioni dei due segmenti di corda (segmenti 2 e 3 del disegno originale) che tirano verso l'alto. $$T_4 = T_2 + T_3$$ Poiché $T_2 = T_3 = T$, abbiamo: $$Mg = 2T \Rightarrow T = \frac{1}{2}Mg$$  Di conseguenza: **Modulo della forza F (domanda c):** $$|\vec{F}| = T = \frac{1}{2}Mg$$
**Tensioni nei fili (domanda b):**
  $T_1 = \frac{1}{2}Mg$   $T_2 = \frac{1}{2}Mg$   $T_3 = \frac{1}{2}Mg$  $T_4 = Mg$ 
**Reazione del sostegno R5 (domanda b):** La forza totale verso il basso sulla puleggia superiore è la somma delle tensioni dei tre segmenti di corda che vi sono collegati (1, 2, 3). $$R_5 = T_1 + T_2 + T_3 = T + T + T = 3T = \frac{3}{2}Mg$$ 
### Esercizio 2 (Serway n. 86) 
Per spostare un'auto impantanata, si lega una fune tra l'auto e un albero. Si esercita una forza $\vec{F}$ al centro della fune, tendendola in modo che ciascuna metà formi un piccolo angolo $\theta$ rispetto alla linea retta tra auto e albero. 
**Domande:** 
a) Ricavare un'espressione della forza che agisce sull'auto. 
b) Calcolare il modulo della tensione della fune se $\theta = 7^\circ$ e $|\vec{F}| = 100 \ N$. 
#### **Soluzione** 
##### **a) Forza sull'auto** 
La forza applicata $\vec{F}$ è bilanciata dalle componenti verticali della tensione $T$ presente in entrambe le metà della fune. Per l'equilibrio nel punto di applicazione della forza: $$|\vec{F}| = T \sin\theta + T \sin\theta = 2T \sin\theta$$ La forza che agisce sull'auto è la tensione $T$ della fune. Possiamo esprimerla in funzione di $F$: $$T = \frac{|\vec{F}|}{2 \sin\theta}$$ Questa è l'espressione della forza che agisce sull'auto (e anche sull'albero). 
##### **b) Calcolo della tensione** 
Con $\theta = 7^\circ$ e $|\vec{F}| = 100 \ N$: $$T = \frac{100 \ N}{2 \sin(7^\circ)} \approx \frac{100 \ N}{2 \cdot 0,1218} \approx 410,3 \ N$$ La macchina "sente" una forza di oltre 400 N, un notevole vantaggio meccanico.
### Esercizio 3 (Serway n. 91) 
Un cuscino di massa $m$ viene lasciato cadere da fermo dalla sommità di un palazzo alto $h$. Un vento costante esercita una forza orizzontale $\vec{F}$ sul cuscino. La resistenza dell'aria verticale è trascurabile. **Domande:** 
a) Mostrare che la traiettoria del cuscino è una linea retta. 
b) Il cuscino cadrà con velocità costante? Spiegare. 
c) Se $m=1,2 \ kg$, $h=8 \ m$ e $F=2,4 \ N$, a che distanza dalla base del palazzo atterrerà il cuscino?  
d) Se il cuscino viene lanciato con una velocità iniziale non nulla, che tipo di traiettoria seguirà? Spiegare. 
#### **Soluzione**
##### **a) Traiettoria del cuscino** 
Le forze agenti sono la gravità ($m\vec{g}$) e il vento ($\vec{F}$). Le equazioni del moto sono: $$\begin{cases} m a_x = F \\ m a_y = -mg \end{cases} \implies \begin{cases} a_x = F/m \\ a_y = -g \end{cases}$$  Integrando due volte rispetto al tempo, partendo da fermo ($v_0=0$) e da una posizione iniziale $(x_0=0, y_0=h)$: $$\begin{cases} x(t) = \frac{1}{2} \frac{F}{m} t^2 \\ y(t) = h - \frac{1}{2}gt^2 \end{cases}$$  Per trovare l'equazione della traiettoria, eliminiamo il tempo $t$. Dalla prima equazione ricaviamo $t^2 = \frac{2m}{F}x(t)$. Sostituendo nella seconda: $$y(x) = h - \frac{1}{2}g \left(\frac{2m}{F}x\right) = h - \frac{mg}{F}x$$  Questa è l'equazione di una **retta**, quindi la traiettoria è rettilinea.  
##### **b) Velocità del cuscino**
Le componenti della velocità sono: $v_x(t) = a_x t = \frac{F}{m}t$ e $v_y(t) = a_y t = -gt$.  Il modulo della velocità (la celerità) è: $$|\vec{v}(t)| = \sqrt{v_x^2 + v_y^2} = \sqrt{\left(\frac{F}{m}t\right)^2 + (-gt)^2} = t \sqrt{\left(\frac{F}{m}\right)^2 + g^2}$$  Poiché il modulo della velocità dipende dal tempo $t$, **non è costante**. 
##### **c) Distanza di atterraggio** 
Il cuscino atterra quando $y(x_1) = 0$. Usando l'equazione della traiettoria: $$0 = h - \frac{mg}{F}x_1 \Rightarrow x_1 = \frac{hF}{mg}$$  Sostituendo i valori: $$x_1 = \frac{8 \ m \cdot 2,4 \ N}{1,2 \ kg \cdot 9,81 \ m/s^2} \approx 1,63 \ m$$ 
##### **d) Traiettoria con velocità iniziale non nulla** 
Se il cuscino ha una velocità iniziale $\vec{v}_0$, il moto è governato da un'accelerazione vettoriale **costante**: $$\vec{a} = \frac{F}{m}\hat{i} - g\hat{j}$$  Un corpo soggetto a un'accelerazione costante (sia in modulo che in direzione) segue una traiettoria **parabolica**, a meno che la velocità iniziale non sia parallela al vettore accelerazione (nel qual caso il moto rimane rettilineo).  L'asse di questa parabola sarà inclinato e parallelo alla direzione del vettore $\vec{a}$. 
### Esercizio 4 (Serway, n. 92) 
Un blocco di massa $m_1$ giace su un piano orizzontale privo di attrito. È collegato tramite un sistema di pulegge e una fune ideale a un blocco di massa $m_2$ che pende verticalmente. 
**Domande:** 
a) Come si confronta l'accelerazione del blocco 1 con l'accelerazione del blocco 2?  
b) Se $m_2 = 1,3 \ kg$, trovare l'accelerazione di $m_2$ in funzione di $m_1$. 
c) Cosa succede se $m_1$ è molto minore di 1,3 kg? 
d) Cosa succede se $m_1$ tende all'infinito?  
e) Quanto vale la tensione della corda nel caso d)?  
f) È possibile rispondere a c), d), e) senza risolvere b)? Spiegare.
#### **Soluzione** 
##### **a) Relazione tra le accelerazioni** 
Questa è una relazione di vincolo cinematico. Se il blocco $m_1$ si sposta orizzontalmente di una distanza $\Delta x_1$, la fune deve scorrere. Questa lunghezza di fune si distribuisce sui due segmenti verticali che sorreggono la puleggia mobile a cui è attaccato $m_2$. Se $m_2$ scende di $\Delta y_2$, ogni segmento verticale si allunga di $\Delta y_2$, richiedendo una lunghezza totale di fune pari a $2\Delta y_2$. Pertanto, il vincolo è: $$\Delta x_1 = 2 \Delta y_2$$ Derivando due volte rispetto al tempo, otteniamo la relazione tra i moduli delle accelerazioni $a_1$ e $a_2$: $$a_1 = 2a_2$$ L'accelerazione del blocco 1 è il doppio di quella del blocco 2. 
##### **b) Accelerazione di $m_2$** 
Scriviamo le equazioni della dinamica per i due blocchi. Sia $T$ la tensione nella fune. 
**Blocco 1:** $T = m_1 a_1$ 
**Blocco 2:** Il blocco è sorretto da una puleggia su cui agiscono due tratti di fune verso l'alto. 
La forza netta verso l'alto è $2T$. $$m_2g - 2T = m_2 a_2$$ Sostituiamo $a_1 = 2a_2$ e $T=m_1 a_1$ nell'equazione per il blocco 2: $$m_2g - 2(m_1 a_1) = m_2 a_2$$ $$m_2g - 2(m_1 (2a_2)) = m_2 a_2$$ $$m_2g - 4m_1 a_2 = m_2 a_2$$ $$m_2g = (4m_1 + m_2) a_2$$ L'accelerazione del blocco 2 è quindi: $$a_2 = \frac{m_2 g}{4m_1 + m_2}$$ 
#####  **c) Limite per $m_1 \ll m_2$**
Se $m_1$ è trascurabile rispetto a $m_2$, il termine $4m_1$ al denominatore è molto piccolo. $$a_2 \approx \frac{m_2 g}{m_2} = g$$  Il blocco 2 cade essenzialmente in caduta libera, poiché il blocco 1 non oppone quasi nessuna inerzia.  
##### **d) Limite per $m_1 \to \infty$**
Se $m_1$ è molto grande, il termine $4m_1$ al denominatore domina.  $$a_2 = \frac{m_2 g}{4m_1 + m_2} \approx \frac{m_2 g}{4m_1} \to 0$$ L'accelerazione del blocco 2 tende a zero. Il sistema rimane fermo, poiché il blocco 1 è troppo "pesante" da muovere.  
##### **e) Tensione per $m_1 \to \infty$** 
Nel caso d), il sistema è in equilibrio statico ($a_2 \approx 0$). Dall'equazione per il blocco 2: $$m_2g - 2T = m_2 a_2 \approx 0 \implies T \approx \frac{m_2 g}{2}$$ La tensione nella corda è la metà del peso del blocco 2.  
##### **f) Risposte qualitative** 
Sì, è possibile rispondere basandosi sull'intuizione fisica: 
**c) $m_1 \ll m_2$:** 
Se la massa $m_1$ è quasi zero, non oppone resistenza. Il blocco $m_2$ è libero di cadere e la sua accelerazione sarà $g$.

**d) e e) $m_1 \to \infty$:** 
Se la massa $m_1$ è infinita, agisce come un'ancora. Il sistema non può muoversi, quindi le accelerazioni sono nulle. La situazione diventa un problema di statica. Per l'equilibrio di $m_2$, le due tensioni $T$ verso l'alto devono bilanciare il peso $m_2 g$, da cui $2T = m_2 g$ e $T = m_2g/2$.


# File d - Esercizi Applicazioni Leggi Del Moto
## Serway, pr. 5.84
Un blocco di alluminio ($m_{1}​=2 kg$) e un blocco di rame ($m_{2}=6 kg$) sono collegati da una corda su una puleggia. Il blocco di rame è su un piano inclinato di $\theta=30°$. 
I blocchi poggiano su una superficie di acciaio. Coefficienti d'attrito: 
Alluminio ($\mu_{s}​=0,61, \mu_{d}=0,47$), 
Rame ($\mu_{s}=0,53, \mu_{d}​=0,36$).
**Domande:** 
a) Se i blocchi vengono lasciati liberi dalla quiete, inizieranno a muoversi? 
b) Se sì, si determinino le loro accelerazioni. 
c) Se sì, si determini il modulo della tensione della corda. 
d) Se no, si determini la somma dei moduli delle forze di attrito agenti sui blocchi.
### Soluzione:
#### a)
Per verificare se il sistema si muove, si confronta la forza motrice ($m_{2}​g\sin\theta$) con le forze di attrito statico massime. La forza motrice è $29,43 N$. La somma delle forze d'attrito statico massime è $38,984 N$. Poiché la forza motrice è minore, il sistema non si muove.
#### d)
In equilibrio statico, la somma delle forze lungo il piano inclinato è zero. $m_{2}​g\sin\theta-F_{s1}​-F_{s2}​=0\implies F_{s1}​+F_{s2}​=m_{2}​g\sin\theta=29,43 N$.
## Serway, pr. 5.89
Una cassa di peso $P=mg$  viene spinta da una forza $F$ inclinata di un angolo $\theta$ rispetto all'orizzontale. Il coefficiente di attrito statico è $\mu_{s}$​.
**Domande:** 
a) Si esprima il minimo valore di $F=|\overset{\rightarrow}{F}|$ necessario per far muovere la cassa. 
b) Si trovi quale condizione deve soddisfare $\theta$ affinché la cassa non si muova per nessun valore di $F$.
### Soluzione:
#### a)
La condizione per il movimento è che la componente orizzontale di $F$ superi la forza d'attrito statico massima. L'equilibrio verticale è $N=P+F\sin\theta$. La condizione è $F\cos\theta=\mu_{s}​N$. $\displaystyle F\cos\theta=\mu s​(P+F\sin\theta)\implies F_{min}​=\frac{\mu_{s}P}{\cos\theta-\mu_{s}\sin\theta}$​.
#### b)
La cassa non si muove se il denominatore della formula precedente è minore o uguale a zero. $\displaystyle\cos\theta-\mu_{s}\sin\theta\leq0\implies \tan\theta\geq \frac{1}{\mu_{s}}\implies\theta\geq \arctan\left(\frac{1}{\mu_{s}}\right)$.
## Serway, pr. 5.95
Un'auto accelera lungo una discesa, partendo da ferma e raggiungendo una velocità di $30 m/s$ in $6 s$. Un giocattolo di massa $m=0,1 kg$ pende dal soffitto con una cordicella che rimane perpendicolare al soffitto dell'auto.
**Domande:** 
a) Si determini l'angolo $\theta$ di inclinazione della discesa. 
b) Si determini il modulo della tensione della cordicella.
### Soluzione:
#### a)
L'accelerazione dell'auto è $\displaystyle a=\frac{\Delta v}{\Delta t}​=\frac{30m/s}{6 s}​=5m/s^{2}$. In un sistema di riferimento non inerziale, la componente del peso lungo la discesa bilancia la forza apparente ($ma$). 
$\displaystyle mg\sin\theta=ma\implies \sin\theta=\frac{a}{g}​=\frac{5}{9,81}​\implies\theta=30,64°$.
#### b)
La tensione della cordicella bilancia la componente del peso perpendicolare al piano inclinato. $T=mg\cos\theta=0,1 kg\cdot9,81 m/s^{2}\cdot\cos(30,64°)=0,844 N$.

## Serway, pr. 6.44
Due corpi di masse $m_{1}=4 kg$ e $m_{2}​=3 kg$ sono collegati da una corda 1 di lunghezza $l=0,5 m$. L'insieme ruota in un piano verticale, sostenuto da una seconda corda (corda 2) di lunghezza $l=0,5 m$. Nel punto più alto, $m_{2}$ ha una velocità di modulo $v_{2}=4 m/s$.
**Domande:** 
a) Si calcoli il modulo della tensione della corda 1 in tale situazione. 
b) Si calcoli il modulo della tensione della corda 2 in tale situazione. 
c) Se aumenta indefinitamente la velocità angolare, quale corda si romperà per prima?
### Soluzione:
#### a)
Poiché i corpi hanno la stessa velocità angolare, $v_{1}​=2v_{2}$​. Sul corpo $m_{1}​$ le forze sono $m_{1}g$ e $T_{1}$​ dirette verso il centro. $$T_{1}+m_{1}​g=m_{1} \frac{v_{1}^{2}}{2l}​​=m_{1}​ \frac{(2v_{2})^{2}}{2l}​\implies T_{1}​=m_{1}​\left( \frac{2v_{2}^{2}}{l}​​-g \right)=216,76 N$$
#### b)
Sul corpo $m_{2}$​ le forze sono $m_{2}g$ e $T_{2}$​ verso il centro, e $T_{1}$​ verso l'esterno. $$T_{2}​+m_{2}​g-T_{1}​=m_{2}​ \frac{v_{2}^{2}}{l}​\implies T_{2}​=m_{2}​(\frac{v_{2}^{2}}{l}​-g)+T_{1}​=283,33 N$$
#### c)
Le tensioni dipendono da $\omega_{2}$. Poiché $T_{2}​=(2m_{1}​+m_{2}​)\omega^{2}l-(m_{1}+m_{2}​)g$ e $T_{1}​=m_{1}​(2\omega^{2}l-g)$, $T_{2}$​ cresce più rapidamente di $T_{1}$, quindi la corda 2 si romperà per prima.
## Serway, pr. 6.47
a) Un nastro bagagli è un cono in rotazione con inclinazione di $20°$. Un bagaglio di massa $30 kg$ compie un giro in $38 s$ a una distanza di $7,46 m$ dall'asse. Si calcoli la forza di attrito statico. 
b) La velocità aumenta e il bagaglio compie un giro in $34 s$ a $7,94 m$. Se si trova al punto di scivolare, si calcoli il coefficiente di attrito statico.
**Domande:** 
a) Si calcoli il modulo della forza di attrito statico esercitato dal nastro sul bagaglio. 
b) Si calcoli il valore del coefficiente di attrito statico tra il nastro e il bagaglio.
### Soluzione:
#### a)
In un sistema di riferimento non inerziale, le forze orizzontali sono bilanciate dalla forza apparente ($F_{a}​$) e le forze verticali dalla forza di attrito ($F_{s}$​) e dalla forza normale ($N$). La forza di attrito bilancia le componenti del peso e della forza apparente. $$F_{s}​=mg\sin\theta+F_{a}\cos\theta=m\left( g\sin\theta+ \frac{4\pi\hat{i}{2}r}{T^{2}}\cos\theta\right)=166,100 N$$
#### b)
Al limite di scivolamento, $F_{s}​=\mu_{s}​N$. Si calcolano $F_{s}​$ e $N$ con i nuovi valori e si trova il coefficiente d'attrito. $F_{s}​=F_{a}\cos\theta-mg\sin\theta=108,301 N$ (dal file) $N=F_{a}\sin\theta+mg\cos\theta=273,769 N$(dal file) $\mu_{s}​=\frac{F_{s_{2}}}{N_{2}}​​=0,396$
## Serway, pr. 6.51
Un camioncino si muove con accelerazione costante a lungo un pendio inclinato di un angolo $\phi$. Una sferetta pende dal soffitto, e il filo forma un angolo costante $\theta$ con la verticale perpendicolare al soffitto.
**Domande:** 
a) Quanto vale l'accelerazione a in funzione di $\theta$ e $\phi$?
### Soluzione:
#### a) Calcolo dell'accelerazione
In un sistema di riferimento non inerziale solidale con il camioncino, le forze sulla sferetta sono in equilibrio. Le forze sono la tensione ($T$), la forza peso ($mg$) e la forza apparente ($ma$). 
Si scompongono le forze lungo gli assi parallelo e perpendicolare al pendio. 
Asse parallelo: $T\sin\theta-mg\sin\phi-ma=0$ 
Asse perpendicolare: $T\cos\theta-mg\cos\phi=0$
Dalla seconda equazione, $T=\cos\theta mg\cos\phi​$. 
Sostituendo nella prima, si ottiene: $a=g(\tan\theta \cos\phi-\sin\phi)=g\cos\theta \sin(\theta-\phi)​$.
## Serway, pr. 6.52
Il pilota di un aereo esegue un giro della morte in un piano verticale. Le velocità sono $300\ mi/h$ in alto e $450\ mi/h$ in basso. Il raggio è $1200\ piedi$. La massa del pilota è $160\ lb$.
**Domande:** 
a) Si calcoli il suo peso apparente nel punto più basso della traiettoria. 
b) Si calcoli il suo peso apparente nel punto più alto della traiettoria. 
c) Si dica in quale modo il peso apparente del pilota potrebbe essere reso nullo cambiando il raggio o il modulo della velocità dell'aereo.
### Soluzione:
#### a)
Le forze nel punto più basso sono la forza normale ($N_{1}​$) verso l'alto e il peso ($mg$) verso il basso. $$N_{1}​-mg=m \frac{v_{basso}^{2}}{R}\implies​N_{1}​=m\left(\frac{v_{basso}^{2}}{R}​​+g \right)=0,378\times10^{4} N$$
#### b)
Nel punto più alto, le forze sono $N_{2}$​ e $mg$ verso il basso. $$N_{2}+mg=m \frac{v_{alto}^{2}}{R}\implies N_{2}​=m\left( \frac{v_{alto}^{2}}{R}-g\right)=2,8553×10^{3} N$$
#### c)
Il peso apparente è nullo nel punto più alto se la forza normale è zero. $$N_{2}=m\left( \frac{v_{alto}^{2}}{R}-g\right)=0\implies \frac{v_{alto}^{2}}{R}​​=g\implies v_{alto}​=\sqrt{gR}​$$
## Serway, pr. 6.54
Un disco di massa $m_{1}$ ruota su un piano orizzontale liscio, collegato a un contrappeso di massa $m_{2}$ attraverso un foro. Il contrappeso è in equilibrio. Il raggio della traiettoria del disco è $R$.
**Domande:** 
a) Si determini il modulo della tensione della corda. 
b) Si determini il modulo della forza radiale agente nel disco. 
c) Si determini il modulo della velocità del disco. 
d) Si descriva qualitativamente il moto del disco se si aggiunge un piccolo carico al contrappeso. 
e) Si descriva qualitativamente il moto del disco se si rimuove una parte del carico del contrappeso.
### Soluzione:
#### a)
Il contrappeso è in equilibrio, quindi la tensione bilancia il suo peso: $T=m_{2}​g$.
#### b)
La forza radiale sul disco è la tensione della corda:$F_{rad}​=T=m_{2}​g$.
#### c)
La forza radiale fornisce l'accelerazione centripeta: $$F_{rad}​=m_{1}​ \frac{v^{2}}{R}​\implies m_{2}​g=m_{1}​ \frac{v^{2}}{R}​\implies v=\sqrt{ \frac{m_{2}gR}{m_{1}}}$$​
#### d)
La tensione aumenta, il raggio diminuisce lentamente e, per la conservazione del momento angolare, la velocità del disco aumenta.
#### e)
La tensione diminuisce, il raggio aumenta lentamente e la velocità del disco diminuisce.
## Serway, pr. 6.59
Un'attrazione di un parco divertimenti è un cilindro verticale rotante di raggio $R$. Il coefficiente di attrito statico tra una persona e la parete è $\mu_{s}​$.
**Domande:** 
a) Si calcoli l'espressione del massimo valore che può avere il periodo di rotazione del cilindro affinché una persona rimanga attaccata alla parete senza cadere. 
b) Se la frequenza di rotazione aumenta, come cambiano le forze e il moto di una persona? 
c) Se la frequenza di rotazione diminuisce, come cambiano le forze e il moto di una persona?
### Soluzione:
#### a)
In un sistema non inerziale, l'equilibrio verticale richiede $F_{s}​=mg$ e l'equilibrio orizzontale $\displaystyle N=F_{a}​=m \frac{4\p\hat{i}{2}R}{T^{2}}$​. La condizione per non cadere è $F_{s}​\leq\mu_{s}​N$. $$mg\leq\mu_{s}​m \frac{4\p\hat{i}{2}R}{T^{2}}\implies T^{2}\leq \frac{4\p\hat{i}{2}\mu_{s}R}{g}\implies T_{max}​=2\pi\sqrt{\frac{\mu_{s}R}{g}}​​$$
#### b)
Con l'aumento della frequenza, la forza normale $N$ aumenta, mentre la forza di attrito statica richiesta $F_{s}​=mg$ rimane costante. La persona resta attaccata alla parete.
#### c)
Con la diminuzione della frequenza, la forza normale $N$ diminuisce. Se la $F_{s}$​ richiesta ($mg$) supera la forza di attrito statico massima ($\mu_{s}​N$), la persona cade.
## Serway, pr. 6.61
Un'auto affronta una curva sopraelevata di raggio $R$ e angolo $\theta$. Il coefficiente di attrito statico è $\mu_{s}$​.
**Domande:** 
a) Si determini l'intervallo di valori che può assumere il modulo della velocità dell'auto senza che scivoli. 
b) Si calcoli il minimo valore di $\mu_{s}$​ per cui tale intervallo di velocità è nullo.
### Soluzione:
#### a)
L'intervallo di velocità è delimitato da due condizioni: il limite di scivolamento verso il basso e verso l'alto.
- Velocità minima (scivolamento in basso, $F_{s}​$ in alto): $\displaystyle v_{min}^{2}​=gR \frac{\sin\theta-\mu_{s}\cos\theta}{\cos\theta+\mu_{s}\sin\theta}$​.
- Velocità massima (scivolamento in alto, $F_{s}​$ in basso):$\displaystyle v_{min}^{2}​=gR \frac{\sin\theta+\mu_{s}\cos\theta}{\cos\theta-\mu_{s}\sin\theta}$. 
  L'intervallo è $[\sqrt{ v_{min}^{2} },\sqrt{ v_{max}^{2} }​​]$.
#### b)
L'intervallo è nullo quando $v_{min}​=v_{max}​=0$. Questo accade quando l'attrito è sufficiente a impedire all'auto di scivolare verso il basso da ferma. La condizione è $mg\sin\theta=\mu_{s}​mg\cos\theta$, da cui $\mu_{s,min}​=\tan\theta$.
## Serway, pr. 6.63
Un modellino di aeroplano di massa $0,75 kg$ vola in una traiettoria circolare orizzontale. Velocità $35 m/s$, lunghezza del filo $60 m$. Le forze sono: tensione ($T$), peso ($mg$) e spinta aerodinamica ($F_{sp}$​) che forma un angolo $\theta=20°$ con la verticale. Il filo forma un angolo costante $\phi=20°$ con l'orizzontale.
**Domande:** 
Si calcolino i moduli della tensione del filo e della spinta aerodinamica.
### Soluzione:
#### Calcolo delle forze
Si impostano le equazioni di equilibrio in un sistema di riferimento non inerziale. 
La forza apparente è $\displaystyle F_{a}=m \frac{v^{2}}{r}=m \frac{v^{2}}{L\cos\phi}​$. 
Equilibrio orizzontale: $T\cos\phi+F_{sp}\sin\theta-F_{a}​=0$
Equilibrio verticale: $F_{sp}​\cos\theta-T\sin\phi-mg=0$ 
Risolvendo il sistema si ottiene: 
$\displaystyle T=m\left( \frac{v^{2}}{L\cos\phi}-g\sin\theta \right)=12,796 N$ 
$\displaystyle F_{sp}​=m\left( g\cos\theta+ \frac{v^{2}}{L\cos\phi}\sin\phi \right)=12,487 N$  
## Serway, pr. 6.64
Uno studente usa un accelerometro (filo a piombo) per misurare la velocità di un'auto in una curva non sopraelevata. La deflessione è di $15°$ quando la velocità è di $23 m/s$.
**Domande:** 
a) Quanto vale l'accelerazione centripeta dell'auto? 
b) Quanto vale il raggio della curva? 
c) Quanto vale la velocità dell'auto se, affrontando la stessa curva, la deflessione è $9°$?
### Soluzione:
#### a)
L'accelerazione centripeta si calcola dall'equilibrio delle forze nel sistema non inerziale: $a_{c}​=g\tan\theta$.
$a_{c}​=9,81 m/s^{2}\ \tan(15°)=2,629 m/s^{2}$
#### b)
Il raggio si ricava da $a_{c}​= \frac{V^{2}}{r}​:$
$\displaystyle r= \frac{a_{c}}{V^{2}}​= \frac{(23 m/s)^{2}}{2,629 m/s^{2}​}=201,249 m$.
#### c)
Per la stessa curva, il raggio è costante. La nuova velocità si ottiene dalla nuova accelerazione centripeta: $\displaystyle V'=\sqrt{ a_{c}'​r​ }=\sqrt{ g\tan\theta'\cdot r​ }=\sqrt{ g\tan(9°)\cdot 201,249 m }​=17,683 m/s$.
# File e - Esercizi Lavoro Ed Energia
## Serway, pr. 7.61
Due forze costanti sono applicate a un corpo avente massa $m=5 kg$, libero di muoversi nel piano $xy$. Le due forze $F_{1}$​ e $F_{2}$​ hanno modulo rispettivamente $25 N$ e $42 N$ e formano un angolo con il semiasse x positivo rispettivamente di $35°$ e $150°$. Nell'istante $t=0$ il corpo si trova nell'origine con velocità $\overset{\rightarrow}{v_{0}}​=(4\hat{i}+2,5\hat{j}) m/s$.
**Domande:** 
a) Si esprimano le due forze in termini dei vettori, e si usi tale notazione anche per le risposte successive. 
b) Si calcoli la forza risultante agente sul corpo. 
c) Si calcoli l'accelerazione del corpo. 
d) Si calcoli la velocità del corpo all'istante $t=3s$. 
e) Si calcoli la sua posizione all'istante $t=3s$. 
f) Si calcoli la sua energia cinetica usando l'espressione $\displaystyle K_{f}​=\frac{1}{2}​m|\overset{\rightarrow}{v_{f}}​|^{2}$. 
g) Si calcoli la sua energia cinetica usando l'espressione $\displaystyle K_{f}​=\frac{1}{2}​m|\overset{\rightarrow}{v_{i}}​|^{2}+\sum_{k}\overset{\rightarrow}{F_{k}}\cdot\Delta\overset{\rightarrow}{r}$. 
h) Quale conclusione si trae dal confronto delle risposte alle domande f) e g)?
### Soluzione:
#### a)
Scomponendo le forze in componenti cartesiane: $$\begin{array}{l}
\overset{\rightarrow}{F_{1}}=(|\overset{\rightarrow}{F_{1}}|\cos\theta_{1}​)\hat{i}+(|\overset{\rightarrow}{F_{1}}|\sin\theta_{1}​)\hat{j}​=(20,4788\hat{i}+14,3394\hat{j}​)N\\
\overset{\rightarrow}{F_{2}}=(|\overset{\rightarrow}{F_{2}}|\cos\theta_{2}​)\hat{i}+(|\overset{\rightarrow}{F_{2}}|\sin\theta_{2}​)\hat{j}​​=(-36,3731\hat{i}+21\hat{j}​)N
\end{array}$$
#### b)
La forza risultante è la somma vettoriale: $F_{ris}​=\overset{\rightarrow}{F_{1}}​+\overset{\rightarrow}{F_{2}}​=(-15,8943\hat{i}+35,3394\hat{j}​) N$  
#### c)
L'accelerazione si calcola con la seconda legge di Newton: $\displaystyle \overset{\rightarrow}{a}= \frac{\overset{\rightarrow}{F_{ris}}}{m}​​=5-15,8943\hat{i}+35,3394\hat{j}​​=(-3,1789\hat{i}+7,0679\hat{j}​) m/s^{2}$  
#### d)
La velocità all'istante $t=3s$ si ottiene da $\overset{\rightarrow}{v}(t)=\overset{\rightarrow}{v_{0}}​+\overset{\rightarrow}{a}t$: $$v(3)=(4\hat{i}+2,5\hat{j}​)+(-3,1789\hat{i}+7,0679\hat{j}​)\cdot3=(-5,5367\hat{i}+23,7037\hat{j}​) m/s$$  
#### e)
La posizione all'istante $t=3s$ si ottiene da $\displaystyle \overset{\rightarrow}{r}(t)=\overset{\rightarrow}{r_{0}}+\overset{\rightarrow}{v_{0}}t+\frac{1}{2}​\overset{\rightarrow}{a}t^{2}$: $$\overset{\rightarrow}{r}(3)=(4\hat{i}+2,5\hat{j}​)\cdot3+\frac{1}{2}​(-3,1789\hat{i}+7,0679\hat{j}​)\cdot3^{2}=(-2,3051\hat{i}+39,3056\hat{j}​) m$$  
#### f)
L'energia cinetica finale è $K_{f}=\frac{1}{2}m|\overset{\rightarrow}{v_{f}}​|^{2}$: $$\begin{array}{}
|\overset{\rightarrow}{v_{f}}​|^{2}=(-5,5367)^{2}+(23,7037)^{2}=592,514 m^{2}/s^{2} \\
K_{f}=\frac{1}{2}​(5 kg)(592,514 m^{2}/s^{2})\approx1,4813 KJ
\end{array} $$  
#### g)
L'energia cinetica finale è $K_{f}=K_{i}​+W_{tot}$​: $$\begin{array}{l}
K_{i}=\frac{1}{2}m|v_{0}|^{2}=\frac{1}{2}​(5 kg)(42+2,52)=55,625 J \\
W_{tot}​=F_{ris}​\cdot\Delta r=(-15,8943)(-2,3051)+(35,3394)(39,3056)\approx1,4257 KJ \\
K_{f}=55,625 J+1,4257 KJ\approx1,4813 KJ
\end{array}$$  
#### h)
I risultati dei punti f) e g) coincidono, confermando il teorema dell'energia cinetica.
## Serway, pr. 7.63
Un piano inclinato di un angolo $\theta=20°$ rispetto al piano orizzontale ha una molla con costante elastica $K=500 N/m$ fissata all'estremità inferiore. Un blocco avente massa $m=2,5 kg$ è posto sul piano inclinato a una distanza $d=0,3 m$ dall'estremità libera della molla. Da questa posizione, il blocco inizia a muoversi verso la molla con velocità iniziale di modulo $V_{0}​=0,75 m/s$.
**Domande:** 
Calcolare la compressione della molla nell'istante in cui il blocco si ferma.
### Soluzione:
#### Calcolo della compressione
Si applica il teorema dell'energia cinetica, $W_{tot}​=\Delta K=K_{f}​-K_{i}$​. I lavori sono dovuti alla forza peso ($W_{g}$​) e alla forza elastica ($W_{el}​$). 
$$\begin{array}{l}
W_{g}​=mg\Delta h=mg(d+D)\sin\theta \\
W_{el}​=-\frac{1}{2}KD^{2} \\
K_{i}=\frac{1}{2}​mv_{0}^{2}​\quad\text{ e }\quad K_{f}​=0 \\
mg(d+D)\sin\theta- \frac{1}{2}​KD^{2}=-\frac{1}{2}​mv_{0}^{2}
\end{array}$$ Riorganizzando si ottiene un'equazione quadratica in $D$, la cui soluzione positiva è: $$D=\frac{mg\sin\theta}{K}+\sqrt{ \left( \frac{mg\sin\theta​}{K} \right)^{2}+\frac{2mgd\sin\theta}{K}​+\frac{mv_{0}^{2}}{K}}=0,1315 m$$  

## Serway, pr. 7.65
a) In un sistema, si espone che l'energia potenziale $U(x)$ vale $5 J$ per $x=0$. La forza agente sul punto materiale è $\overset{\rightarrow}{F}=(8e^{-2x})\hat{i}$. 
b) Si dice se la forza è conservativa o non conservativa e si spieghi come si fa a verificarlo.
**Domande:** 
a) Si calcoli la funzione $U(x)$. 
b) Si dica se la forza è conservativa o meno e si spieghi come verificarlo.
### Soluzione:
#### a)
Si usa la relazione $F_{x}​=-\frac{dU}{dx}$​. $$U(x)=-\int F_{x}​dx=-\int 8e^{-2x}dx=4e^{-2x}+C$$
Usando la condizione $U(x=0)=5 J$, si ha $U(0)=4e0+C=4+C=5 J\implies C=1 J$. 
La funzione di energia potenziale è $U(x)=(4e^{-2x}+1) J$.
#### b)
La forza è conservativa perché il lavoro che compie tra due punti dipende solo dalle posizioni iniziale e finale, non dal percorso seguito.
## Serway, pr. 8.46
Un filo inestensibile collega un blocco di massa $m_{1}​=3,5$ kg su un tavolo privo di attrito con un blocco di massa $m_{2}​=1,9 kg$ sospeso. Il blocco $m_{2}$​ si trova a un'altezza $h=0,9 m$ dal pavimento, mentre $m_{1}​$ è a una distanza $H=1,2 m$ dal bordo del tavolo. I blocchi partono da fermi. Il blocco $m_{2}$​ tocca il pavimento e si ferma prima che $m_{1}$​ raggiunga il bordo.
**Domande:** 
a) Si calcoli la velocità con cui il blocco di massa $m_{1}$​ scivola fuori dal bordo del tavolo. 
b) Si trovi il modulo della velocità d'impatto con il pavimento del blocco di massa $m_{1}$. 
c) Quale lunghezza minima deve avere il filo per non tendersi durante la caduta del blocco $m_{1}​$? 
d) L'energia del sistema nella configurazione iniziale e in quella un attimo prima che il corpo di massa $m_{1}$​ tocchi il pavimento è la stessa? 
e) Motivare la risposta.
### Soluzione:
#### a)
Si usa la conservazione dell'energia meccanica durante la caduta di $m_{2}$​: $$\begin{array}{l}
E_{i}=m_{2}​gh \\
E_{f}​=\frac{1}{2}​(m_{1}​+m_{2})V^{2} \\
V=\sqrt{ \frac{2m_{2}gh}{m_{1}+m_{2}} }​​=2,493 m/s
\end{array}$$  
#### b)
Si usa la conservazione dell'energia per il blocco $m_{1}$​ dopo che $m_{2}$​ ha toccato terra: $$\begin{array}{l}
\displaystyle\frac{1}{2}​m_{1}​V^{2}+m_{1}​gH=\frac{1}{2}​m_{1}​|\overset{\rightarrow}{v_{f}}​|^{2} \\
|\overset{\rightarrow}{v_{f}}​|=\sqrt{ V^{2}+2gH }​=5,455 m/s
\end{array}$$  
#### c)
La lunghezza minima del filo è la distanza massima tra il bordo del tavolo e il blocco $m_{1}$​ durante la caduta, che si verifica all'impatto con il suolo: $$L_{min}​=V\sqrt{ \frac{2H}{g} }​​=1,233 m$$ 
#### d)
No.
#### e)
L'energia non si conserva perché l'urto anelastico di $m_{2}$​ con il pavimento dissipa l'energia cinetica.
## Serway, pr. 8.64
Un blocco di massa $m_{1}​=2,0 kg$ è collegato a un blocco di massa $m_{2}=3,0 kg$ tramite una corda che passa su una puleggia. Il blocco $m_{2}$ è attaccato a una molla con costante elastica $K=250 N/m$. Il piano inclinato è liscio e forma un angolo $\theta=40°$. Inizialmente la molla è a riposo e il blocco $m_{1}$ viene tirato verso il basso di un tratto $d=0,2 m$ e poi rilasciato.
**Domande:** 
Si calcoli il modulo della velocità di ciascun blocco quando la molla torna nella posizione di riposo.
### Soluzione:
#### Modulo della velocità
Si applica la conservazione dell'energia meccanica, $E_{i}​=E_{f}​$. $$\begin{array}{l}
E_{i}​=\frac{1}{2}​Kd^{2}+m_{1}gd\sin\theta-m_{2}gd \\
E_{f}​=\frac{1}{2}(m_{1}+m_{2})V^{2} \\
\displaystyle V^{2}=\frac{Kd^{2}+2gd(m_{1}\sin\theta-m_{2})}{m_{1}+m_{2}}​ \\
\displaystyle V=\sqrt{\frac{2(m_{2}-m_{1}\sin\theta)gd+Kd^{2}}{m_{1}+m_{2}}}=1,2432 m/s
\end{array}$$  
## Serway, pr. 8.66
Una zucca scivola lungo la copertura semisferica di un silo. Parte dal punto più alto e viene smossa. Si osserva che la zucca perde contatto con la superficie sferica quando la semiretta che parte dal centro di curvatura della semisfera e passa per la posizione della zucca forma un certo angolo $\theta$ con la direzione verticale.
**Domande:** Qual è il valore di questo angolo?
### Soluzione:
#### Calcolo dell'angolo di distacco
Si usa la conservazione dell'energia per trovare la velocità $v$ della zucca in funzione dell'angolo $\theta$: $$v^{2}=2gR(1-cos\theta)$$Si applica la seconda legge di Newton in direzione radiale: $$mg\cos\theta-N=m\frac{v^{2}}{R}$$​La zucca perde il contatto quando la reazione vincolare $N=0$. $$\begin{array}{l}
\displaystyle mg\cos\theta=m\frac{2gR(1-\cos\theta)​}{R}\implies \cos\theta=2-2\cos\theta\implies 3\cos\theta=2 \\
\displaystyle \theta=\arccos\left( \frac{2}{3}​ \right)=48,19°
\end{array}$$  


# File f - Quantità di moto e Sistemi
## Esercizio 1
Un proiettile di massa $m=0,008 kg$ viene sparato contro un blocco di massa $M=0,25 kg$ inizialmente a riposo su un tavolo di altezza $h=1m$. Il proiettile si conficca nel blocco, che cade dal tavolo toccando il suolo in un punto a una distanza orizzontale $d=2m$ dal tavolo.
domande:
a) Si calcoli il modulo $v_{0}$​ della velocità iniziale del proiettile.
### Soluzioni:
#### Calcolo della velocità iniziale del proiettile
L'urto tra il proiettile e il blocco è un urto unidimensionale totalmente anelastico, quindi si conserva la quantità di moto totale del sistema. 
*Prima dell'urto*: La quantità di moto del sistema è data solo dal proiettile: $P_{tot,x,i}​=m\cdot v_{0,x}$​. 
*Dopo l'urto*: Il proiettile si conficca nel blocco, formando un unico corpo di massa ($M+m$) che si muove con una velocità $V_{x}$​. La quantità di moto è $P_{tot,x,f}​=(M+m)\cdot V_{x}$​. 
Applicando la conservazione della quantità di moto: $(M+m)Vx​=m\cdot v0,x$​ 
Da cui si ottiene: $\displaystyle V_{x}​=\frac{m\cdot v_{0,x}}{M+m}$​​ 
Successivamente, il sistema blocco+proiettile si stacca dal bordo del tavolo con una velocità orizzontale $V_{x}$​ e compie una traiettoria parabolica. Il tempo di caduta $t_{c}​$ può essere calcolato dalla legge del moto orizzontale ($d=V_{x}\cdot t_{c}$​) e dalla legge del moto verticale ($h=\frac{1}{2}gt_{c}^{2}$​). 
Dal moto orizzontale: $\displaystyle t_{c}​=\frac{d}{V_{x}}​=\frac{(M+m)d}{m\cdot v_{0,x}}​$ 
Sostituendo questa espressione nella legge del moto verticale: $\displaystyle h=\frac{1}{2}​g\cdot t_{c}^{2}=\frac{1}{2}​g \frac{(M+m)^2d^2}{m^2v_{0,x}^2}​$​ 
Risolvendo per $v_{0,x}​$ si ottiene: $\displaystyle v_{0,x}^{2}​=\frac{(M+m)^2gd^2}{2hm^{2}}$​ 
E infine: $\displaystyle |v_{0}|=v_{0}=\frac{(M+m)d​^{2}}{m}\sqrt{ \frac{g}{2h} }​​=\frac{(0,25kg+0,008kg)\cdot (2m)}{0,008kg}​ \sqrt{ \frac{9,81m/s^{2}}{2\cdot (1m)} }​​=142,857 m/s$​  

## Esercizio 2
Una molla di massa trascurabile è compressa di un tratto $d=0,08m$ e costante elastica $K=3,85N/m$ ed è tenuta tra due blocchi aventi masse rispettivamente $m_{1}=0,25 kg$ (a sinistra) e $m_{2}=0,5 kg$ (a destra), entrambi inizialmente in quiete sulla superficie orizzontale. 
Domande: 
1) Si calcoli il modulo della velocità massima raggiunta da ciascun blocco se il coefficiente di attrito dinamico tra ciascun blocco e la superficie è: 
	domande esercizio ad elenco
	a) $\mu_{d}​=0$  
	b) $\mu_{d}​=0,1$  
	c) $\mu_{d}=0,462$  
### Soluzioni:
#### a) Caso $\mu_{d}​=0$  
In assenza di attrito, la risultante delle forze esterne sul sistema è nulla, quindi si conservano la quantità di moto totale e l'energia meccanica.
*Conservazione della quantità di moto*: $$\begin{array}{l}
P_{tot,f}​=P_{tot,i} \\
m_{1}​V_{1,f}​+m_{2}​V_{2,f}​=0
\end{array}$$ 
*Conservazione dell'energia meccanica*: $E_{m,f}​=E_{m,i}$​ 
L'energia potenziale elastica iniziale è convertita in energia cinetica dei due blocchi. $$\frac{1}{2}m_{1}​V_{1,f}^{2}​+\frac{1}{2}​m_{2}​V_{2,f}^{2}​=\frac{1}{2}​Kd^{2}$$ 
Risolvendo il sistema di equazioni, si ottengono le velocità: $$\begin{array}{l}
\displaystyle V_{1,f}​=-d\sqrt{ \frac{m_{2}k}{m_{1}(m_{1}+m_{2})} }​​\approx -0,2563m/s\\
\displaystyle V_{2,f}​=d\sqrt{ \frac{m_{1}k}{m_{2}(m_{1}+m_{2})} }​​\approx 0,1282m/s
\end{array}$$ 
Dunque, i moduli delle velocità massime sono: $$\begin{array}{}
|\overset{\rightarrow}{V_{1}}​|_{max}​=0,2563m/s \\
|\overset{\rightarrow}{V_{2}}​|_{max}​=0,1282m/s
\end{array}$$  
#### b) Caso $\mu_{d}​=0,1$  
In questo caso si muove solo il blocco di massa $m_{1}​$, poiché l'analisi preliminare mostra che la forza di attrito statico sul blocco $m_{2}$​ è maggiore della forza elastica iniziale. 
Applichiamo il teorema dell'energia cinetica per il blocco $m_{1}$. 
L'energia cinetica del blocco $m_{1}$​ in una posizione $x$ è data dal lavoro delle forze agenti: $$\begin{array}{l}
K(x)-Ki_{i}=W_{el}​+W_{d}​ \\
\frac{1}{2}​m_{1}​|\overset{\rightarrow}{V_{1}​}(x)|^{2}=\left( \frac{1}{2}​Kd^{2}-\frac{1}{2}​Kx^{2} \right)-\mu_{d}​m_{1}​g(d-x)
\end{array} $$
La velocità è massima quando la derivata di $|\overset{\rightarrow}{V_{1}}(x)|^{2}$ rispetto a $x$ è zero. 
Questo accade per $x=K\mu_{d}​m_{1}​g$​. 
Sostituendo questo valore di $x$ nell'espressione della velocità, si ottiene: $$|\overset{\rightarrow}{V_{1}​}|_{max}​=\left( d- \frac{\mu_{d}​m_{1}​g}{K}​ \right)\sqrt{ \frac{K}{m_{1}} }=0,0640m/s$$ 
Il blocco $m_{2}$​ rimane fermo, quindi la sua velocità massima è zero.
#### c) Caso $\mu_{d}​=0,462$ 
Dall'analisi preliminare del testo si evince che in questo caso le forze di attrito statico sono sufficientemente grandi da impedire il movimento di entrambi i blocchi. Pertanto, la velocità massima di entrambi i blocchi è zero. 
$|\overset{\rightarrow}{V_{1}​}|_{max}​=0$
$|\overset{\rightarrow}{V_{2}​}|_{max}​=0$  
## Esercizio 3
Una pallottola avente massa $m=0,005 kg$, con velocità iniziale $V_{pi,x}​=400m/s$, attraversa un blocco avente massa $M=1kg$. 
Il blocco, inizialmente in quiete su una piattaforma orizzontale liscia, è connesso a una molla avente costante elastica $k=900N/m$. 
Se, dopo l'impatto, il blocco si muove di un tratto $d=0,05m$ verso destra prima di fermarsi istantaneamente, si trovino: 
domande 
a) il modulo della velocità con la quale il proiettile esce dal blocco;
b) la frazione dell'energia cinetica iniziale del proiettile che è andata dissipata durante l'urto.
### Soluzioni:
#### a) Calcolo della velocità di uscita del proiettile
La soluzione si articola in due fasi:
1. *Fase di compressione della molla*: Dopo che il proiettile ha attraversato il blocco, questo si muove comprimendo la molla. L'energia meccanica del blocco si conserva. L'energia cinetica del blocco dopo l'urto si trasforma completamente in energia potenziale elastica quando la molla raggiunge la sua massima compressione $d$. $$\frac{1}{2}​MV_{b2,x}^{2}​=\frac{1}{2}kd^{2}$$Risolvendo per la velocità del blocco $V_{b2,x}$:$$ V_{b2,x}=d\sqrt{ \frac{k}{M} }​=0,05m\sqrt{ \frac{900N/m​​}{1kg} }=1,5m/s$$  
2. *Fase di urto*: Durante l'urto tra proiettile e blocco, la quantità di moto del sistema si conserva. $$\begin{array}{l}
P_{tot,f}​=P_{tot,i}​ \\
MV_{b2,x}​+mV_{pf,x}​=mV_{pi,x}
\end{array}$$Risolvendo per la velocità finale del proiettile $V_{pf,x}$​: $$V_{pf,x}​=V_{pi,x}-mM​V_{b2,x}​=400m/s- \frac{1kg}{0,005kg​}(1,5m/s)=400m/s-300m/s=100m/s$$  
#### b) Calcolo della frazione di energia cinetica dissipata
La frazione di energia cinetica iniziale del proiettile che è stata dissipata è data da: $$\frac{|\Delta K_{p}|​}{K_{p,i}}​=\frac{K_{p,i}-K_{p,f}​}{K_{p,i}​}=1-\frac{K_{p,f}​​}{K_{p,i}​}=1-\frac{\frac{1}{2}​mV_{pf,x}^{2}​​}{\frac{1}{2}mV_{pi,x}^{2}2}​​=1-\left( \frac{V_{pf,x}}{V_{pi,x}​​​} \right)^{2} $$
Sostituendo i valori: 
$$1−(400m/s100m/s​)2=1−(41​)2=1−161​=1615​=0,9375$$ 
L'energia cinetica iniziale del proiettile è $$Kp,i​=21​mVpi,x2​=21​(0,005kg)(400m/s)2=400J$$L'energia cinetica dissipata è $$|ΔKp​|=0,9375\cdot 400J=375J$$
## Esercizio 4
Un punto materiale avente massa m1​=0,002kg in moto con velocità V1,i​=8m/s urta centralmente in modo elastico un punto materiale avente massa m2​=0,001kg inizialmente in quiete. 
domande
a) si calcoli il modulo della velocità di ciascun punto materiale dopo l'urto.
b) si calcoli il modulo della velocità di ciascun punto materiale dopo l'urto nel caso in cui il secondo punto materiale abbia massa m2​=0,01Kg.
c) si calcoli l'energia cinetica del punto materiale di massa m1​ dopo l'urto nei due casi a) e b); in quale dei due casi il punto materiale perde più energia cinetica?
### Soluzioni:
#### a) Calcolo delle velocità dopo l'urto (caso a)
Trattandosi di un urto elastico unidimensionale, si possono usare le formule specifiche per calcolare le velocità finali dei due corpi, dove V2,i​=0: V1,f​=(m1​+m2​m1​−m2​​)V1,i​+(m1​+m2​2m2​​)V2,i​=(0,002kg+0,001kg0,002kg−0,001kg​)\cdot (8m/s)=31​\cdot 8m/s\approx 2,6667m/s V2,f​=(m1​+m2​2m1​​)V1,i​+(m1​+m2​m2​−m1​​)V2,i​=(0,002kg+0,001kg2\cdot 0,002kg​)\cdot (8m/s)=34​\cdot 8m/s\approx 10,6667m/s  
#### b) Calcolo delle velocità dopo l'urto (caso b)
Utilizzando le stesse formule, ma con la nuova massa m2​=0,01kg: V1,f​=(m1​+m2​m1​−m2​​)V1,i​=(0,002kg+0,01kg0,002kg−0,01kg​)\cdot (8m/s)=(0,012−0,008​)\cdot 8m/s\approx −5,3333m/s V2,f​=(m1​+m2​2m1​​)V1,i​=(0,002kg+0,01kg2\cdot 0,002kg​)\cdot (8m/s)=(0,0120,004​)\cdot 8m/s\approx 2,6667m/s  
#### c) Calcolo e confronto dell'energia cinetica di m1​  
**Caso a):** Energia cinetica finale di m1​: K1,f​=21​m1​V1,f2​=21​(0,002kg)(2,6667m/s)2\approx 0,0071J Energia cinetica iniziale di m1​: K1,i​=21​m1​V1,i2​=21​(0,002kg)(8m/s)2=0,064J Variazione di energia cinetica: |ΔK1​|=K1,i​−K1,f​\approx 0,064J−0,0071J=0,0569J  
**Caso b):** Energia cinetica finale di m1​: K1,f​=21​m1​V1,f2​=21​(0,002kg)(−5,3333m/s)2\approx 0,0284J Variazione di energia cinetica: |ΔK1​|=K1,i​−K1,f​\approx 0,064J−0,0284J=0,0356J Confrontando i valori, il punto materiale di massa m1​ perde più energia cinetica nel caso a), dove la massa m2​ è minore.