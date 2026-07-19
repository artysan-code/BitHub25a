---
tags:
  - algoritmi
  - flussi
  - esercizi
---
# Teoria — Flussi di Rete e Minimo Taglio
*Esercizio 2 — Teoria · Flussi di Rete e Minimo Taglio · 7 domande da 3 appelli (13/06/2024 · 18/07/2025 · 23/09/2025).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/`, appelli 13/06/2024 · 18/07/2025 · 23/09/2025.*
## Come leggere questo file
Nei tre appelli qui raccolti Flussi occupa sempre l'Esercizio 2, sempre 11 punti, sempre 2-3 domande aperte da **max 5 righe** ciascuna — mai vero/falso in questo slot. Le definizioni formali (massimo flusso, minimo taglio, rete residua) sono il punto d'ingresso quasi obbligato: compaiono in ogni appello e valgono punti quasi gratuiti se la definizione è mandata a memoria nella forma esatta, coi vincoli giusti. Non è un caso che la stessa domanda sulla definizione di massimo flusso sia uscita **identica parola per parola** in due appelli diversi (13/06/2024 e 23/09/2025): è il punto più economico dell'intero slot.

Il resto del punteggio si gioca su due fronti distinti. Il primo è la **complessità di Ford-Fulkerson**: qui il verbo della traccia («argomentando sulla sua polinomialità») pretende la distinzione fra valore delle capacità e dimensione in bit, non solo la formula $O(m\cdot\operatorname{val}(f^*))$. Il secondo è la dimostrazione **"nessun cammino aumentante $\Rightarrow$ flusso massimo"**, che negli appelli compare sotto due travestimenti — come correttezza di un algoritmo di estrazione del min-cut (18/07/2025) e come dimostrazione diretta del teorema (23/09/2025) — ma è **la stessa identica catena di deduzioni**: taglio dei raggiungibili da $s$ in $G_f$, saturazione/flusso-nullo sui due versi, lemma del valore, dualità debole. Impararla una volta la dà quasi gratis nell'altra forma.

L'errore più costoso non è dimenticare un fatto, ma **saltare un passaggio** sotto il vincolo delle 5 righe: fermarsi a "$f^*$ è massimo quindi funziona" senza il ponte saturazione→lemma del valore→corollario di dualità debole, oppure enunciare l'intero teorema Max-Flow Min-Cut a tre vie quando la traccia chiede solo una freccia. La densità simbolica ($c(e)$, $\operatorname{val}(f)$, $G_f$) conta più della prosa attorno, in ognuna di queste risposte.
## Definizione formale del massimo flusso
Domanda ricorrente quasi verbatim: la stessa richiesta, con la stessa risposta attesa, in due appelli a più di un anno di distanza.
### Definizione del problema del massimo flusso
*citazione: 13/06/2024 · Es. 2, punto 1 · e 23/09/2025 · Es. 2, punto 1* — testo della domanda identico in entrambi gli appelli; cambia solo la frase di apertura dell'esercizio («si consideri il problema del massimo flusso» nel 2024, «si consideri il problema del calcolo del massimo flusso (max flow problem)» nel 2025), non la domanda stessa.

> 1. Si definisca formalmente il problema. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Data una rete di flusso $G=(V,E,s,t,c)$ — grafo **orientato** con sorgente $s\in V$, pozzo $t\in V$ e funzione di capacità $c:E\to\mathbb{R}_{\geq 0}$ sugli archi — un **flusso $st$** è una funzione $f:E\to\mathbb{R}_{\geq 0}$ che soddisfa il **vincolo di capacità** $0\leq f(e)\leq c(e)$ per ogni $e\in E$ e il **vincolo di conservazione** $\sum_{e\text{ entra in }v}f(e)=\sum_{e\text{ esce da }v}f(e)$ per ogni $v\in V\setminus\{s,t\}$. Il **valore** del flusso è $\operatorname{val}(f)=\sum_{e\text{ esce da }s}f(e)-\sum_{e\text{ entra in }s}f(e)$, e il problema del **massimo flusso** chiede il flusso $f^*$ che massimizza $\operatorname{val}(f)$ fra tutti i flussi $st$ validi su $G$.

> [!info]- Spiegazione
> Ogni clausola ha un ruolo preciso, e nessuna è ridondante anche sotto il vincolo delle 5 righe.
>
> - **«Orientato»** è essenziale: il verso degli archi conta, un arco $(u,v)$ non implica capacità nel verso $(v,u)$, ed è proprio questa asimmetria a rendere necessario l'arco inverso nel [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Grafo residuo|grafo residuo]].
>
> - **$c(e)\geq 0$, non «$>0$»**: un arco di capacità $0$ è ammesso nel dominio (equivale a non poterlo mai usare); il segno di $c$ non può mai essere negativo, o il vincolo $f(e)\leq c(e)$ non avrebbe senso.
>
> - **Il vincolo di conservazione vale solo per $v\neq s,t$** — la clausola più spesso scritta male, come «per ogni nodo». Su $s$ e $t$ il flusso entrante e uscente può (anzi tipicamente deve) differire: è esattamente quello squilibrio a definire $\operatorname{val}(f)$.
>
> - **$\operatorname{val}(f)$ è un flusso *netto*, sottrazione compresa**: la definizione ammette archi entranti in $s$, e in quel caso vanno sottratti. Omettere il termine sottrattivo è impreciso in generale, anche se passa inosservato negli esercizi dove $s$ non ha archi entranti.
>
> - **L'obiettivo è «massimo fra tutti i flussi $st$ validi»**, non genericamente «il flusso più grande possibile»: senza il vincolo di validità (capacità **e** conservazione insieme) il problema è banale.
>
> **Dove si perdono punti:** omettere il vincolo di conservazione, o scriverlo per «ogni nodo» invece che per $V\setminus\{s,t\}$; dimenticare il termine sottrattivo in $\operatorname{val}(f)$; rispondere solo a parole («il flusso che arriva a $t$») senza la formula sul lato $s$. Sono gli stessi identici errori in entrambi gli appelli — la ripetizione della domanda non abbassa la guardia.
## Definizione formale del minimo taglio
Stessa struttura a tre pezzi (dati, vincoli, obiettivo) della definizione di massimo flusso, applicata al problema duale — ma qui l'insidia non è un vincolo dimenticato, è la direzione della somma nella capacità.
### Definizione del problema del minimo taglio
*citazione: 18/07/2025 · Es. 2, punto 1*

> 1. Si definisca formalmente il problema. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dato $G=(V,E,s,t,c)$ una rete di flusso — grafo **orientato**, sorgente $s$, pozzo $t$, funzione di capacità $c:E\to\mathbb{R}_{\geq 0}$ — un **taglio st** è una partizione $(A,B)$ dei nodi con $s\in A$ e $t\in B$. La sua **capacità** è
> $$\operatorname{cap}(A,B)=\sum_{\substack{e=(u,v)\in E\\u\in A,\ v\in B}} c(e),$$
> la somma delle capacità dei soli archi diretti **da $A$ verso $B$** — gli archi da $B$ ad $A$ non compaiono nella somma, qualunque sia la loro capacità. Il problema del **minimo taglio** chiede di trovare un taglio $(A^*,B^*)$ di capacità **minima fra tutti i tagli st** di $G$.

> [!info]- Spiegazione
> Ogni clausola blocca un errore preciso, e va tenuta anche sotto il vincolo delle 5 righe.
>
> - **La direzionalità della capacità è l'errore più frequente del capitolo.** Sommare anche gli archi da $B$ ad $A$ (o sottrarli) trasforma $\operatorname{cap}(A,B)$ nella definizione, diversa, del **flusso netto** attraverso il taglio — quantità che compare nel [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Lemma del valore del flusso|lemma del valore del flusso]], non nella capacità. Cfr. [[Formulario Flussi#Definizioni — vanno scritte così|l'errore da 1 punto sulla definizione di taglio]].
>
> - **"Fra tutti i tagli st"**, non "il sottoinsieme di archi di capacità minima che separa $s$ da $t$": la minimalità è relativa alla classe delle partizioni $(A,B)$ con $s\in A,\ t\in B$. Un taglio esiste sempre, qualunque sia $G$ — a differenza dell'MST, qui non serve alcuna ipotesi di connessione.
>
> - **$s\in A$ e $t\in B$ sono vincoli fissi**, non un'assegnazione a piacere: scambiare i ruoli darebbe il taglio "ts", con capacità in generale diversa perché la somma non è simmetrica sugli archi orientati.
>
> - **La definizione non presuppone il teorema Max-Flow Min-Cut.** Min-Cut è un problema di ottimizzazione a sé; solo *dopo*, col teorema, si scopre che i due ottimi coincidono. Citare già "il valore del flusso massimo" in questo punto è un salto logico fuori posto.
>
> **Dove si perdono punti:** sommare (o sottrarre) anche gli archi da $B$ ad $A$ nella capacità del taglio; omettere "fra tutti i tagli st".
## Rete residua
La definizione formale della rete residua è chiesta come punto a sé, e premia due dettagli che le slide danno per scontati.
### Definizione formale della rete residua
*citazione: 23/09/2025 · Es. 2, punto 2*

> 2. Si definisca formalmente il concetto di rete residua. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dati $G=(V,E,s,t,c)$ e un flusso $f$, la **rete residua** $G_f=(V,E_f,s,t,c_f)$ ha lo **stesso insieme di nodi** $V$ di $G$. Per ogni arco $e=(u,v)\in E$:
>
> - se $f(e)<c(e)$, l'arco **diretto (forward)** $(u,v)$ sta in $E_f$ con capacità residua $c_f(u,v)=c(e)-f(e)>0$ (quanto si può ancora inviare);
> - se $f(e)>0$, l'arco **inverso (backward)** $(v,u)$ sta in $E_f$ con capacità residua $c_f(v,u)=f(e)>0$ (quanto si può annullare).
>
> In formule: $E_f=\{e\in E: f(e)<c(e)\}\cup\{e^{\text{rev}}: f(e)>0\}$. Ogni arco di $E$ genera al più due archi in $E_f$, quindi $G_f$ ha gli **stessi nodi** di $G$ e $|E_f|\leq 2m$ archi.

> [!info]- Spiegazione
> - **La condizione $f(e)>0$ per l'arco inverso non è opzionale.** Senza flusso già instradato su $e$ non c'è nulla da «annullare»: con $f(e)=0$ l'arco inverso avrebbe capacità residua $0$, cioè non esisterebbe affatto in $G_f$. Trattarlo come sempre presente è l'errore più frequente su questo punto.
>
> - **«Stesso insieme di nodi»** è spesso dato per scontato e quindi taciuto, ma fa parte della definizione formale: $G_f$ non aggiunge né rimuove nodi rispetto a $G$, ridefinisce solo archi e capacità.
>
> - **Il bound $|E_f|\leq 2m$** è il dettaglio che la traccia premia e che quasi nessuno scrive: ogni arco originale contribuisce ad **al più** un forward e **al più** un backward — uno dei due può mancare (se $e$ è saturo manca il forward, se $f(e)=0$ manca il backward). Da qui discende il costo $O(m)$ di ogni singolo aumento di Ford-Fulkerson, non un generico $O(|E_f|)$ non limitato — cfr. [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Terminazione e complessità con capacità intere|07 · Terminazione e complessità]].
>
> - **Un solo conteggio per direzione**, anche con archi antiparalleli già in $G$: la definizione si applica a un singolo $e\in E$ alla volta, e il bound $2m$ resta valido.
>
> **Dove si perdono punti:** dimenticare la condizione $f(e)>0$ per l'esistenza dell'arco inverso; non menzionare che $G_f$ ha lo stesso insieme di nodi di $G$ e/o il bound $|E_f|\leq 2m$.
## Complessità di Ford-Fulkerson e polinomialità
Non basta la formula: il verbo «argomentando» nella traccia pretende la distinzione fra valore delle capacità e dimensione in bit dell'istanza.
### Perché Ford-Fulkerson è pseudo-polinomiale, non polinomiale
*citazione: 13/06/2024 · Es. 2, punto 2*

> 2. Si enunci la complessità temporale dell'algoritmo di Ford-Fulkerson, argomentando sulla sua polinomialità o meno. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Con capacità intere, l'invariante di integralità garantisce che ogni cammino aumentante porti un incremento intero $\geq 1$: quindi al più $\operatorname{val}(f^*)$ aumenti bastano a raggiungere il massimo, e ciascuno costa $O(m)$ per trovare un cammino aumentante con BFS/DFS in $G_f$, dando $T(n,m)=O(m\cdot\operatorname{val}(f^*))$. Questa complessità è **pseudo-polinomiale**, non polinomiale: dipende dal *valore* delle capacità (tramite $\operatorname{val}(f^*)$), non dalla loro dimensione in bit, che per una capacità $C$ è $O(\log C)$. Con scelta sfortunata dei cammini il numero di iterazioni può essere $\Theta(C)$ — rete con arco centrale di capacità $1$ fra due rami di capacità $C$, alternando i due cammini si eseguono $2C$ aumenti da un'unità ciascuno, esponenziale nel numero di bit di $C$. Con capacità irrazionali l'algoritmo può non terminare affatto; scegliendo invece i cammini con BFS (Edmonds-Karp) si ottiene $O(m^2n)$, polinomiale e indipendente dalle capacità.

> [!info]- Spiegazione
> La risposta piena incastra quattro pezzi, e nessuno da solo vale il punteggio pieno.
>
> - **Da dove viene $O(m\cdot\operatorname{val}(f^*))$.** L'invariante di integralità (cfr. [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Algoritmo di Ford-Fulkerson]]) limita il numero di iterazioni a $\operatorname{val}(f^*)$; ciascuna cerca un cammino aumentante in $G_f$ con una visita, costo $O(m)$.
>
> - **Perché è pseudo-, e non semplicemente, polinomiale.** La dimensione di un'istanza si misura in bit: rappresentare $C$ richiede $O(\log C)$ bit, non $C$ unità. $O(m\cdot\operatorname{val}(f^*))$ è polinomiale in $n$, $m$ **e nel valore numerico $C$**, ma $\operatorname{val}(f^*)$ può valere $\Theta(C)$ — esponenziale nel numero di bit necessari a scrivere $C$.
>
> - **Il controesempio classico.** La rete a farfalla con arco centrale di capacità $1$ e due rami esterni di capacità $C$ ammette una scelta dei cammini che alterna l'arco centrale nei due versi, ciascun aumento con bottleneck $1$: servono $2C$ iterazioni per $\operatorname{val}(f^*)=2C$, contro le $2$ che basterebbero coi due cammini disgiunti sui rami esterni. Con $C=2^{30}$ il numero di passi è astronomico pur restando l'istanza minuscola in bit.
>
> - **Capacità irrazionali.** Senza interezza, l'invariante cade del tutto: Ford-Fulkerson può eseguire una sequenza infinita di aumenti che converge a un valore **strettamente inferiore** al massimo flusso.
>
> - **La correzione: Edmonds-Karp.** Scegliendo sempre il cammino con **meno archi** (BFS in $G_f$, cfr. [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Algoritmo di Edmonds-Karp (cammino più corto)]]) si ottengono al più $O(mn)$ aumenti, complessità $O(m^2n)$: polinomiale e **indipendente dai valori delle capacità**. Tabella comparativa completa in [[Formulario Flussi#Complessità — il cuore dei V/F]].
>
> **Dove si perdono punti:** scrivere solo la formula $O(m\cdot\operatorname{val}(f^*))$ senza argomentare la polinomialità; dire genericamente «dipende dalle capacità» senza la distinzione valore-vs-bit; dimenticare il caso delle capacità irrazionali o il rimedio di Edmonds-Karp.
>
> **Corrispettivo in Es. 1:** la stessa distinzione valore-vs-bit, applicata a otto varianti vincolate sulle capacità, è la batteria [[03 - Vero-Falso Flussi di Rete#Complessità di Ford-Fulkerson: polinomiale, pseudo-polinomiale, e sotto quali ipotesi|Vero-Falso Flussi di Rete · Complessità di Ford-Fulkerson]].
## Estrazione del min-cut da un flusso massimo, e sua correttezza
Due domande in scala dello stesso appello, non indipendenti: prima si descrive l'algoritmo che estrae il taglio minimo da un flusso massimo già in mano, poi se ne dimostra la correttezza. Rispondere alla seconda senza aver fissato con precisione la prima lascia la dimostrazione senza un referente su cui appoggiarsi — e la correttezza qui sotto **non** è un argomento nuovo: è la stessa identica dimostrazione richiesta, da un'altra angolazione, in [[#Dimostrazione: assenza di cammino aumentante implica flusso massimo]].
### Estrazione del taglio minimo in tempo lineare da un flusso massimo
*citazione: 18/07/2025 · Es. 2, punto 2*

> 2. Si descriva come è possibile, dato un flusso massimo, calcolare in tempo lineare un taglio di capacità minima. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Dato un flusso massimo $f^*$ di $G$, si costruisce il grafo residuo $G_{f^*}$ in tempo $O(m)$ e si esegue una visita — BFS o DFS, indifferentemente — a partire da $s$, ottenendo l'insieme $A$ dei nodi **raggiungibili da $s$** in $G_{f^*}$. Si pone $B=V\setminus A$: $(A,B)$ è un taglio st, con $t\notin A$ perché $f^*$, essendo massimo, non ammette cammini aumentanti in $G_{f^*}$ (teorema dei cammini aumentanti), quindi $s$ e $t$ risultano separati in $G_{f^*}$. Costruire $G_{f^*}$ e visitarlo costano entrambi $O(n+m)$: tempo totale $O(n+m)$, lineare nella dimensione della rete.

> [!info]- Spiegazione
> - **Perché serve proprio $f^*$ massimo, non un flusso qualsiasi.** Se $f$ non fosse massimo esisterebbe un cammino aumentante $s\leadsto t$ in $G_f$, quindi $t$ sarebbe raggiungibile da $s$ e $t\in A$: la costruzione non produrrebbe nemmeno un taglio st valido. L'ipotesi di massimalità è la condizione che rende $A$ ben definito, non un dettaglio tecnico.
>
> - **Il conto dei tempi va scritto esplicitamente**, non liquidato con "si fa una visita": costruire $G_{f^*}$ è $O(m)$, la BFS/DFS è $O(n+m)$. La somma resta $O(n+m)$ — è proprio la linearità richiesta dal testo a dover comparire, non solo il nome dell'algoritmo.
>
> - **Il punto descrive, non dimostra.** Basta enunciare la procedura e dire *perché $A$ è ben definito* ($t\notin A$ per massimalità di $f^*$); che $(A,B)$ abbia *esattamente* capacità minima è materia della correttezza, qui sotto. Anticiparla brucia le cinque righe di entrambi i punti. Riepilogo compatto in [[Formulario Flussi#Estrazione del min-cut da un flusso massimo|Formulario Flussi]].
>
> **Dove si perdono punti:** omettere l'ipotesi che $f$ debba essere **massimo**; rispondere solo "si fa una BFS da $s$" senza il collegamento esplicito fra assenza di cammini aumentanti e $t\notin A$.
>
> **Corrispettivo in Es. 1:** la costruzione duale — nodi che **raggiungono** $t$ invece di nodi raggiungibili da $s$ — è verificata come V/F in [[03 - Vero-Falso Flussi di Rete#Taglio minimo via nodi che raggiungono t|Vero-Falso Flussi di Rete · Taglio minimo via nodi che raggiungono t]].
### Correttezza dell'algoritmo di estrazione
*citazione: 18/07/2025 · Es. 2, punto 3*

> 3. Si discuta in modo conciso e preciso la correttezza dell'algoritmo fornito nel punto precedente. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> La correttezza segue dalla direzione $[3\Rightarrow 1]$ della dimostrazione del [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Teorema Max-Flow Min-Cut|teorema Max-Flow Min-Cut]], applicata a $f^*$ e ad $A$. Poiché $f^*$ è massimo, non esistono cammini $s\leadsto t$ in $G_{f^*}$: ogni arco $e=(u,v)$ con $u\in A,\ v\in B$ deve essere **saturo** ($f^*(e)=c(e)$, altrimenti $e\in G_{f^*}$ renderebbe $v$ raggiungibile da $s$, contro $v\in B$), e ogni arco $e=(v,u)$ con $v\in B,\ u\in A$ deve avere **flusso nullo** ($f^*(e)=0$, altrimenti il suo arco inverso in $G_{f^*}$ renderebbe $v$ raggiungibile da $s$, stesso assurdo). Per il [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Lemma del valore del flusso|lemma del valore del flusso]], $\operatorname{val}(f^*)=\sum_{e\text{ esce da }A} f^*(e)-\sum_{e\text{ entra in }A} f^*(e)=\sum_{e\text{ esce da }A} c(e)-0=\operatorname{cap}(A,B)$. Per il corollario di [[07 - Flussi di Rete (Max-Flow e Min-Cut)#Dualità debole|dualità debole]] (certificato di ottimalità), $\operatorname{val}(f^*)=\operatorname{cap}(A,B)$ implica che $(A,B)$ è un taglio minimo. $\blacksquare$

> [!info]- Spiegazione
> - **Questa non è una dimostrazione nuova: è un pezzo riciclato del teorema.** La direzione $[3\Rightarrow 1]$ del teorema Max-Flow Min-Cut dimostra esattamente "$f$ senza cammini aumentanti $\Rightarrow$ esiste un taglio $(A,B)$ con $\operatorname{cap}(A,B)=\operatorname{val}(f)$", con $A$ costruito nello stesso modo. Il punto chiede di applicare quell'argomento al caso specifico $f=f^*$: riconoscerlo evita di reinventare la dimostrazione sotto il vincolo di tempo dell'esame.
>
> - **Perché gli archi $A\to B$ sono saturi.** Se $e=(u,v)$ con $u\in A,\ v\in B$ avesse $f^*(e)<c(e)$, per definizione di grafo residuo l'arco diretto $e$ apparterrebbe a $G_{f^*}$, e $v$ sarebbe raggiungibile da $s$, contraddicendo $v\in B$. Argomento per assurdo puntuale, arco per arco.
>
> - **Perché gli archi $B\to A$ hanno flusso nullo.** Simmetricamente: se $e=(v,u)$ con $v\in B,\ u\in A$ avesse $f^*(e)>0$, l'arco inverso apparterrebbe a $G_{f^*}$ con capacità residua $f^*(e)>0$, rendendo di nuovo $v$ raggiungibile da $s$.
>
> - **Le due saturazioni insieme, non separate, danno l'uguaglianza.** Da sole, "gli archi $A\to B$ sono saturi" darebbero solo $\operatorname{val}(f^*)\leq\operatorname{cap}(A,B)$ — vero comunque per dualità debole su *ogni* taglio, quindi non prova nulla di nuovo. Serve anche l'annullamento del termine entrante per chiudere l'uguaglianza.
>
> - **L'ultimo passo non è "ovvio", è il corollario di dualità debole.** Da $\operatorname{val}(f^*)=\operatorname{cap}(A,B)$ si conclude la minimalità del taglio solo invocando il corollario, non per salto automatico.
>
> **Dove si perdono punti:** dimostrare l'intero teorema Max-Flow Min-Cut a tre vie invece della sola direzione $[3\Rightarrow 1]$ richiesta; fermarsi a "$f^*$ è massimo quindi l'algoritmo funziona" senza il passaggio esplicito saturazione/flusso-nullo $\to$ lemma del valore $\to$ corollario di dualità debole.
## Dimostrazione: nessun cammino aumentante implica flusso massimo
Stessa tecnica dimostrativa di [[#Correttezza dell'algoritmo di estrazione]] — lì l'algoritmo restituisce $(A,B)$ e si chiede *perché funziona*, qui si parte dall'ipotesi «nessun cammino aumentante» e si chiede di dimostrare direttamente che $f$ è massimo. Impararne una regala quasi gratis l'altra: cambia solo il punto di partenza della narrazione, non un solo passaggio della catena deduttiva.
### Dimostrazione: assenza di cammino aumentante implica flusso massimo
*citazione: 23/09/2025 · Es. 2, punto 3*

> 3. Si dimostri che se nella rete residua corrispondente ad un certo flusso $f$ non c'è nessun cammino dalla sorgente al pozzo, allora $f$ è un flusso massimo. *(Max 5 righe.)*

> [!quote] Soluzione — da scrivere sul compito
> Sia $A=\{v\in V : \exists\text{ cammino }s\leadsto v\text{ in }G_f\}$ e $B=V\setminus A$. Per ipotesi non esiste cammino $s\leadsto t$ in $G_f$, quindi $t\notin A$: $(A,B)$ è un taglio $st$ valido.
>
> Ogni arco $e=(u,v)\in E$ con $u\in A,\ v\in B$ è **saturo**: se fosse $f(e)<c(e)$, $e$ apparterrebbe a $G_f$ e $v$ sarebbe raggiungibile da $s$, contro $v\in B$. Ogni arco $e=(v,u)\in E$ con $v\in B,\ u\in A$ ha **flusso nullo**: se fosse $f(e)>0$, l'arco inverso $(u,v)$ apparterrebbe a $G_f$, rendendo di nuovo $v$ raggiungibile, assurdo.
>
> Per il lemma del valore del flusso, $\operatorname{val}(f)=\displaystyle\sum_{e\text{ esce da }A} f(e)-\sum_{e\text{ entra in }A} f(e)=\operatorname{cap}(A,B)-0=\operatorname{cap}(A,B)$.
>
> Per **dualità debole**, ogni flusso $g$ soddisfa $\operatorname{val}(g)\leq\operatorname{cap}(A,B)$; in particolare $\operatorname{val}(g)\leq\operatorname{cap}(A,B)=\operatorname{val}(f)$ per **ogni** $g$, dunque $f$ è un flusso massimo. $\blacksquare$

> [!info]- Spiegazione
> - **$A$ è ben definito e $t\notin A$ è esattamente l'ipotesi.** L'insieme dei nodi raggiungibili da $s$ in $G_f$ esiste sempre (contiene almeno $s$); l'ipotesi «nessun cammino $s\leadsto t$» si traduce letteralmente in $t\notin A$, il che rende $(A,B)$ un taglio $st$ legittimo — è il ponte fra l'ipotesi della traccia e l'oggetto che serve alla dimostrazione.
>
> - **L'argomento di saturazione è lo stesso nei due versi, applicato a un arco residuo diverso.** Per gli archi $A\to B$ si usa l'arco forward (esisterebbe se $f(e)<c(e)$); per i $B\to A$ l'arco backward (esisterebbe se $f(e)>0$). Confondere i due casi — per esempio dire che gli archi $A\to B$ sono a flusso nullo — è l'errore più comune, segnalato anche in [[Formulario Flussi#Il teorema — la dimostrazione da consegnare|Formulario Flussi]].
>
> - **Il lemma del valore del flusso**, non il vincolo di capacità sui singoli archi, è il passo che trasforma «$A\to B$ saturi, $B\to A$ nulli» in $\operatorname{val}(f)=\operatorname{cap}(A,B)$: sommando la conservazione su tutti i nodi di $A$, i contributi interni si cancellano e resta il flusso netto attraverso il taglio.
>
> - **Perché la dualità debole è il passo che chiude l'argomento, e non un dettaglio accessorio.** $\operatorname{val}(f)=\operatorname{cap}(A,B)$ dice solo che *questo* taglio ha capacità pari al valore di *questo* flusso — non basta, da solo, a escludere un flusso $g$ migliore. Serve che **ogni** $g$ sia limitato da **ogni** taglio ($\operatorname{val}(g)\leq\operatorname{cap}(A,B)$) per concludere $\operatorname{val}(g)\leq\operatorname{val}(f)$ per ogni $g$, cioè la massimalità.
>
> - **Struttura identica a [[#Correttezza dell'algoritmo di estrazione]]**: stessa catena — taglio dei raggiungibili → saturazione/flusso nullo → lemma del valore → dualità debole — con l'ipotesi e la tesi scambiate di posto rispetto alla domanda del 18/07/2025.
>
> **Dove si perdono punti:** enunciare $\operatorname{val}(f)=\operatorname{cap}(A,B)$ e dichiarare «quindi $f$ è massimo» senza passare esplicitamente dalla dualità debole; invertire quali archi sono saturi e quali a flusso nullo.
>
> **Corrispettivo in Es. 1:** la stessa equivalenza logica, in forma V/F su tre direzioni diverse dei quantificatori, è la tabella in [[03 - Vero-Falso Flussi di Rete#Caratterizzazione del flusso massimo: se, solo se, se e solo se|Vero-Falso Flussi di Rete · Caratterizzazione del flusso massimo]].
