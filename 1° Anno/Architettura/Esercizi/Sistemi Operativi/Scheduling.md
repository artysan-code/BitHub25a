Per un riferimento teorico sugli **algoritmi di scheduling** andare[[2 - Processi e Thread#^311407| a questa pagina]].

## Batch
Generalmente dobbiamo fissare i seguenti concetti, che sono:
- Tempo di Turnaround $T_T$, intervallo del processo dall'ingresso in coda fino al termine dell'esecuzione.
- Tempo di Attesa $T_W$, intervallo di tempo che il processo trascorre in attesa.
- Tempo di Arrivo $T_A$, tempo di arrivo nella coda dei processi.
- Tempo di Esecuzione $T_X$, autoesplicativo.
- Tempo di Inizio esecuzione $T_S$, anche questo autoesplicativo.
- Tempo di fine esecuzione $T_E$, pure questo.

Il calcolo di ogni T è diverso e dipende dal problema, ma i fondamentali sono questi (Ottenuti da First-come First-Served):$$\begin{array}{l}
T_{T} = T_{E}(i) - T_{A}(i)  \\
T_{W} = T_{S}(i) - T_{A}(i) \\
T_{E} = T_{S}(i) + T_{X}(i) \\
T_{S} = T_{E}(i-1)\quad se\quad i>1\quad oppure\quad T_{S} = T_{A}(1) = 0\quad se\quad i=1
\end{array}$$
Generalmente viene richiesto di calcolare la media di $T_{W}$ e di $T_{T}$.

Nei sistemi batch possiamo riordinare (a seconda dell'algoritmo) i processi in arrivo. Nei sistemi interattivi no.

Se non viene specificato in quanto partono i processi, possiamo scegliere noi tramite l'algoritmo quali far partire e in che ordine.

## Sistemi Interattivi
### Sistema Round-Robin
Dato un sistema di n processi, troviamo definito un quantum di esecuzione, un cambio di contesto (entrambi in $u\text{s}$) e in che posizione ci troviamo nel giro. Ci viene chiesto