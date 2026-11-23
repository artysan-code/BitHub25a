---
tags:
  - algoritmi
  - np-completezza
slide: "08_Intractability_III_2025.pdf"
---
# Altre Riduzioni (Super Mario, Peg Solitaire, Tetris)
La nota [[09 - NP-Completezza e Riduzioni]] ha fissato la [[09 - NP-Completezza e Riduzioni#Riduzioni polinomiali|riduzione polinomiale]] e la ricetta per dimostrare la [[09 - NP-Completezza e Riduzioni#NP-completo|NP-completezza]]: scelto un problema NP-completo $X$, si mostra $X \leq_P Y$. Le slide di Intractability III applicano la ricetta a tre giochi: **Super Mario**, **Peg Solitaire** e **Tetris**. Il titolo della slide dice che dimostrare la NP-completezza è divertente. In tutti e tre i casi la tecnica è la **codifica con gadget** già vista nella riduzione 3-SAT $\leq_P$ Independent Set: si costruisce, a partire dall'istanza del problema di partenza, una configurazione di gioco fatta di piccoli pezzi locali (i gadget), ciascuno con un comportamento forzato, e si dimostra che la configurazione è risolvibile **se e solo se** l'istanza di partenza è una istanza yes.

Le slide presentano la costruzione quasi solo per figure: qui i gadget sono descritti a parole, seguendo l'ordine delle slide. Dove il passaggio è ricostruito e non scritto sulla slide, è marcato *(extra, non da slide)*.

| Gioco | Problema di partenza | Obiettivo del gioco |
|---|---|---|
| Super Mario | 3-SAT | arrivare alla fine del livello |
| Peg Solitaire | Hamiltonian Cycle su grafi orientati planari di grado 3 | svuotare la scacchiera |
| Tetris | 3-Partition | svuotare la scacchiera con la sequenza di pezzi data |

## Super Mario: riduzione da 3-SAT
### Il problema di partenza
> [!quote] Definizione — 3-SAT (come nella slide)
> **Input:** una formula booleana composta da clausole di 3 letterali su $n$ variabili.
> **Obiettivo:** esiste un assegnamento di verità che soddisfa tutte le clausole (le rende tutte vere)?
>
> Esempio di istanza yes dato dalla slide: $x_1 = \text{true}$, $x_2 = \text{true}$, $x_3 = \text{false}$, $x_4 = \text{false}$.
>
> 3-SAT è NP-completo (vedi [[09 - NP-Completezza e Riduzioni#SAT e 3-SAT]]).

### Il risultato e l'idea
La slide apre con una schermata di Super Mario Bros. (un livello con mattoni, blocchi, un fungo, un goomba e un tubo) e con la copertina dell'articolo **«Classic Nintendo Games are (Computationally) Hard»** di Greg Aloupis, Erik D. Demaine, Alan Guo e Giovanni Viglietta (10 febbraio 2015). L'abstract mostrato nella slide dice che l'articolo dimostra risultati di NP-hardness per cinque grandi franchise di videogiochi Nintendo (Mario, Donkey Kong, Legend of Zelda, Metroid, Pokémon), nelle versioni generalizzate dei giochi.

> [!quote] Idea della riduzione (dalla slide)
> Data un'istanza di 3-SAT, si costruisce un **livello** (istanza) di Super Mario che è **risolvibile se e solo se la formula è soddisfacibile**.

### Struttura generale del livello
La slide mostra lo schema complessivo del livello come un diagramma a blocchi, in due fasi:
- a sinistra in alto c'è **Start**, dove parte Mario (il gadget Start è una piccola stanza: Mario sta sotto un blocco da cui esce un fungo);
- da Start Mario attraversa una fila di gadget **Variable**, uno per variabile (nell'esempio della figura $x$, $y$, $z$); ogni gadget Variable ha due uscite, una per il letterale positivo ($x$) e una per quello negativo ($\neg x$);
- sotto c'è una fila di gadget **Clause**, uno per clausola (nell'esempio, quattro, con i letterali scritti sopra ciascuno); ogni uscita di un gadget Variable è collegata con un cammino ai gadget Clause delle clausole in cui quel letterale compare. Le linee del diagramma si incrociano molte volte, e i **cerchietti** del diagramma sono i punti di crossover;
- dopo aver toccato i Clause in cui compare, il cammino di ciascun letterale risale al gadget Variable successivo;
- dopo l'ultimo Variable, Mario percorre la linea **Clause check** (da «Check in» a «Check out»), che attraversa tutti i gadget Clause in sequenza e arriva a **Finish**, in basso a sinistra: la stanza finale con il castello e la bandiera.

Per realizzare questo schema servono tre tipi di gadget, mostrati uno alla volta dalla slide.

### Variable gadget
Il gadget è una stanza chiusa da mattoni. Mario entra a sinistra, in un corridoio in alto. In basso ci sono **due** varchi: quello a sinistra è etichettato $x_i$, quello a destra $\neg x_i$. *(extra, non da slide)*: scegliere l'uscita equivale a scegliere il valore di verità della variabile $x_i$, perché il percorso preso da Mario rende «vero» il letterale corrispondente.

### Clause gadget
Nella figura il gadget è una stanza con **tre blocchi con il punto interrogativo** in fila, una **stella** sopra di essi, una zona di **barre di fuoco** (fire bars) sulla sinistra e muri di mattoni. *(Extra, non da slide, ricostruito dalla figura)*: i tre blocchi sono i tre letterali della clausola; la stella e le barre di fuoco servono a far attraversare la stanza solo se almeno uno dei tre cammini dei letterali è stato percorso da Mario, cioè se almeno un letterale della clausola è vero.

### Crossover gadget
Nel livello i cammini da variabili a clausole si incrociano, mentre un livello di Super Mario è una struttura piana. Il **crossover gadget** è una stanza (nella figura, un labirinto di mattoni con un goomba a sinistra e, in alto a destra, un blocco con il punto interrogativo da cui esce un fungo) che permette a due cammini di attraversarsi senza interferire, così che il passaggio di Mario su uno dei due non influenzi l'altro. La slide poi ricompone il livello inserendo il gadget Variable, il gadget Clause e il crossover (e infine la stanza del traguardo, con il castello e la bandiera) nei punti corrispondenti del diagramma.

> [!info] Cosa manca nella slide
> La slide **non** scrive l'enunciato del claim né la dimostrazione delle due direzioni per Super Mario: dà l'idea («risolvibile se e solo se soddisfacibile») e le figure dei gadget. Lo schema della prova per analogia con le altre riduzioni è ricostruito qui sotto.

> [!quote] Claim *(extra, non da slide)*
> $\Phi$ è soddisfacibile se e solo se il livello costruito è risolvibile.
>
> **($\Rightarrow$)** Dato un assegnamento soddisfacente, Mario attraversa ogni gadget Variable scegliendo l'uscita coerente con l'assegnamento; percorrendo i cammini dei letterali veri attiva i gadget Clause in cui compaiono. Dopo l'ultimo Variable Mario percorre la Clause check: ogni clausola contiene almeno un letterale vero, quindi è attraversabile, e Mario arriva a Finish. $\square$
>
> **($\Leftarrow$)** Se il livello è risolvibile, le uscite scelte da Mario nei gadget Variable definiscono un assegnamento; poiché Mario ha attraversato ogni gadget Clause, ogni clausola contiene un letterale vero secondo quell'assegnamento, perché un Clause è attraversabile solo se almeno un letterale lo ha attivato. $\square$
>
> Per la direzione ($\Leftarrow$) si assume che nessun gadget permetta di prendere entrambe le uscite e che il crossover non permetta di cambiare cammino: sono requisiti dei gadget che la slide non scrive.

## Peg Solitaire: riduzione da Hamiltonian Cycle
### Il gioco
Il Peg Solitaire si gioca su una scacchiera con dei fori in cui stanno dei pioli (peg). La mossa consiste nel far **saltare** un piolo sopra un piolo adiacente, finendo in un foro vuoto adiacente al piolo scavalcato; il piolo scavalcato viene tolto (come nella dama). La slide mostra come esempio una scacchiera con i pioli disposti a scrivere la parola «FUN».

> [!quote] Definizione — Peg Solitaire (come nella slide)
> **Obiettivo:** trovare una sequenza di mosse che porti da una configurazione iniziale a una configurazione finale (target) data.

La slide riporta un lungo brano di **Gottfried Wilhelm von Leibniz** (1646-1716) che descrive il gioco: una tavola con pietre infilate in buchi, da rimuovere una alla volta saltando una pietra sopra un'altra in un posto vuoto adiacente; vince chi le toglie tutte. Leibniz nota che il gioco si può anche giocare «al contrario», per riempire la tavola o per formare una figura prestabilita, e che dire in anticipo cosa si può ottenere sarebbe «un'arte preziosa».

### Il teorema
> [!quote] Teorema (Uehara e Iwata, 1990)
> È **NP-completo** decidere se la scacchiera può essere svuotata (cleared).

La slide mostra la copertina dell'articolo «Generalized Hi-Q is NP-Complete» di Ryuhei Uehara e Shigeki Iwata (il sommario dell'articolo parla del puzzle «Hi-Q»; *(extra, non da slide)*: Hi-Q è un altro nome del solitario a pioli). Nelle figure compaiono due scacchiere circolari di legno, una con i pioli e una con i fori.

### Il problema di partenza
> [!quote] Definizione — Hamiltonian Cycle su grafi orientati planari di grado 3 (come nella slide)
> Un grafo è **planare** se si può disegnare nel piano senza che gli archi si incrocino.
>
> **Input:** un grafo orientato planare $G$ in cui ogni vertice ha grado esattamente 3.
> **Obiettivo:** $G$ ha un ciclo hamiltoniano orientato (un ciclo orientato che visita ogni vertice)?
>
> Questo problema è NP-completo (affermato dalla slide).

Poiché ogni vertice ha grado 3, nel grafo orientato ci sono solo **due tipi di vertice**:
- vertice **1-in 2-out**: un arco entrante e due uscenti;
- vertice **2-in 1-out**: due archi entranti e uno uscente.

*(extra, non da slide)* Un ciclo hamiltoniano passa per ogni vertice usando esattamente un arco entrante e uno uscente. Quindi in un vertice 1-in 2-out il ciclo usa l'unico arco entrante e **uno** dei due uscenti; in un vertice 2-in 1-out usa **uno** dei due entranti e l'unico uscente. Gli archi non scelti sono quelli che non appartengono al ciclo.

### I gadget
La slide costruisce la configurazione di pioli a partire da tre tipi di gadget, ciascuno disegnato come un piccolo rettangolo della scacchiera con pioli gialli.

- **Gadget del vertice 1-in 2-out.** Ha un ingresso dal basso (arco «from $x$») e due uscite, a sinistra («to $v$») e a destra («to $v'$»). La figura mostra una riga di pioli in alto, da cui partono le due uscite, e una colonna di pioli collegata all'ingresso in basso.
- **Gadget del vertice 2-in 1-out.** Ha due ingressi, a sinistra («from $u$») e a destra («from $u'$»), su una riga in basso, e un'uscita in alto («to $x$»). I pioli sono disposti su una riga in basso (i due ingressi) e in una colonna che sale verso l'uscita.
- **Gadget degli archi (wire/edge).** Sono due: uno **rettilineo**, una riga di pioli equispaziati da sinistra a destra, e uno **con curva**, che porta la riga in diagonale verso l'alto. *(extra, non da slide)*: servono a portare l'arco orientato da un gadget di vertice a quello successivo.

La slide poi mostra **come si collegano** i gadget (Connecting the gadgets): si prende un disegno planare di $G$ e, al posto di ogni vertice e di ogni arco, si mette il gadget corrispondente sulla griglia. Le immagini evidenziano di volta in volta il gadget di un vertice di $G$ (rettangolo azzurro sulla scacchiera) per far vedere dove finisce nella configurazione globale. La figura (p. 44) mostra a sinistra un esempio di $G$ con 4 vertici e a destra la scacchiera ottenuta, con i gadget disposti seguendo il disegno di $G$; compare anche **un piolo aggiuntivo** (additional peg), indicato in figura; la scacchiera ottenuta ha dimensione polinomiale in $|G|$ *(extra, non da slide)*.

### Comportamento voluto dei gadget («deleting this edge»)
Il comportamento che si vuole è dato dalle animazioni, in cui la slide fa vedere come i pioli di un gadget vengono tolti con una sequenza di salti.

- **Gadget 2-in 1-out, comportamento voluto:** l'animazione (pp. 46-54) mostra la «cancellazione» (deleting this edge) di un solo arco entrante, quello «from $u'$»: i pioli di quell'ingresso vengono tolti con una sequenza di salti.
- **Gadget 1-in 2-out, comportamento voluto:** analogamente, l'animazione (fino a p. 60) mostra la cancellazione di un solo arco uscente, quello «to $v$».

*(extra, non da slide)* In altre parole, il gadget «sceglie» quale dei due archi del vertice tenere nel ciclo: la scelta dell'arco da cancellare corrisponde alla scelta dell'arco che non appartiene al ciclo hamiltoniano.

### Il claim e la dimostrazione
> [!quote] Claim
> Si può svuotare la scacchiera **se e solo se** $G$ ha un ciclo hamiltoniano.

> [!quote] Dimostrazione ($\Leftarrow$)
> Se esiste un ciclo hamiltoniano $C$:
> 1. si **cancellano** per primi gli archi che non appartengono a $C$ (tramite il comportamento voluto dei gadget, descritto sopra);
> 2. si **svuotano** i pioli rimanenti percorrendo $C$.

> [!quote] Dimostrazione ($\Rightarrow$)
> La slide la dà solo in modo **intuitivo**: per svuotare la scacchiera bisogna giocare i gadget nel modo voluto (altrimenti si perde, cioè la scacchiera non si può più svuotare). *(extra, non da slide)* Quindi in ogni gadget di vertice si cancella un arco e i restanti archi formano un ciclo che passa per tutti i vertici.

La slide rimanda a un sito dove giocare la riduzione: `https://www.isnphard.com/g/peg-solitaire/`.

## Tetris: riduzione da 3-Partition
### Il gioco e il problema
> [!quote] Definizione — Tetris (come nella slide)
> **Input:** una configurazione iniziale della scacchiera e l'intera sequenza (offline) dei pezzi.
> **Obiettivo:** si può svuotare tutta la scacchiera?

La slide ricorda, per curiosità, che nel 1993 il cosmonauta russo Aleksandr Serebrov fu la prima persona a giocare a un videogioco nello spazio: portò sulla stazione MIR un Game Boy e la sua copia personale di Tetris (Nintendo, 1989).

> [!quote] Definizione — 3-Partition (come nella slide)
> **Input:** una collezione $A$ di $n$ interi positivi $a_1, \dots, a_n$.
> **Domanda:** è possibile partizionare $A$ in $n/3$ collezioni $A_1, \dots, A_{n/3}$ di **somma uguale**, cioè
> $$\sum_{a \in A_1} a = \dots = \sum_{a \in A_{n/3}} a = \frac{\sum_{a \in A} a}{n/3} = t\,?$$
>
> - **Fatto 1.** 3-Partition è NP-completo anche se $t/4 < a_i < t/2$.
> - **Osservazione.** Se vale $t/4 < a_i < t/2$, allora $|A_i| = 3$ per ogni $A_i$ *(extra, non da slide)*: due numeri sommano meno di $t$, quattro più di $t$.
> - **Fatto 2.** 3-Partition è **strongly NP-hard**, cioè è NP-completo anche se ogni $a_i$ è limitato polinomialmente in $n$ (il numero di numeri).

*(extra, non da slide)* Il Fatto 2 serve per la riduzione: la scacchiera che si costruisce ha dimensioni legate ai valori $a_i$ e a $t$, quindi deve essere di dimensione polinomiale in $n$.

### La costruzione
La scacchiera ha questa struttura (dalle figure):
- una serie di $n/3$ **bucket** (pozzi stretti e verticali, con tacche sulla parete destra; uno per ogni gruppo $A_k$ della partizione cercata);
- ogni bucket ha lungo il bordo $t+3$ **notches** (tacche), cioè posti dove la parete laterale è incavata e che i pezzi possono occupare;
- a destra una zona piena di blocchi.

Per ogni numero $a_i$ la sequenza dei pezzi contiene un **gadget** $a_i$ fatto di tre parti, in quest'ordine:
1. un **initiator** (un pezzo di 4 blocchi a forma di L);
2. un **filler**, ripetuto $a_i$ volte: ogni filler è formato da tre pezzi: un quadrato $2\times2$, un pezzo a L e un secondo quadrato;
3. un **terminator**, formato da un quadrato $2\times2$ e una barra verticale di 4 blocchi.

La slide mostra poi l'animazione dei pezzi che cadono in un bucket per il caso $a_i = 3$:
- **initiator:** si posa in fondo al bucket;
- **filler 1, 2, 3:** i filler si impilano sopra l'initiator, uno dopo l'altro (tre volte, perché $a_i = 3$);
- **terminator:** chiude il gadget in cima.

> [!quote] Lemma — tacche usate da un gadget (dalla slide)
> Un gadget $a_i$ usa **esattamente $a_i + 1$ tacche** del bucket in cui viene inserito.

Quindi, poiché ogni $A_k$ ha tre elementi e $\sum_{a \in A_k} a = t$, i tre gadget di un gruppo usano in tutto $t + 3$ tacche, cioè **tutte** le tacche del bucket (dalla slide: «since each $|A_k| = 3$ and $\text{sum}(A_k) = t$ then we need $t+3$ notches»).

La sequenza dei pezzi finisce con dei **final pieces** (pezzi finali, in colore diverso nella figura), uno per bucket, che nella figura (da p. 83) stanno in cima ai bucket pieni.

### Il claim
> [!quote] Claim (dalla slide)
> Una soluzione $A_1, \dots, A_{n/3}$ di 3-Partition esiste **se e solo se** si possono riempire tutti gli $n/3$ bucket in questo modo (ciascun bucket con i gadget di tre numeri la cui somma è $t$).

**Direzione soluzione $\Rightarrow$ scacchiera svuotata.** Se la partizione esiste, si inseriscono nel bucket $k$ i gadget dei tre numeri di $A_k$: usano esattamente le $t+3$ tacche, quindi il bucket si riempie del tutto. Quando tutti i bucket sono pieni cadono i pezzi finali: le **prime due righe scompaiono**, e poi, come mostra l'animazione, si continua così finché l'intera scacchiera è pulita.

**Direzione scacchiera svuotata $\Rightarrow$ soluzione.** La slide la fa vedere con le **mosse forzate** (forced moves): se si prova a posizionare i pezzi in un bucket in un modo diverso da quello previsto, si perde. Le figure, in sequenza, mostrano per ciascun pezzo tutte le posizioni possibili:
- **initiator:** le figure confrontano la posizione voluta con le posizioni alternative;
- **filler** (primo, secondo e terzo pezzo): lo stesso, pezzo per pezzo (nelle figure le posizioni alternative sono accanto a quella voluta, marcate con un asterisco);
- **element gadget:** la slide dice «If you try to break an element gadget» e mostra i pannelli (a)-(k), con i pezzi posati in bucket non preparati (etichetta «unprimed»); i pannelli contrassegnati da un asterisco sono quelli delle posizioni alternative. *(extra, non da slide)*: l'asterisco è interpretato qui come un vicolo cieco, cioè una posizione da cui non si riesce a proseguire.

*(extra, non da slide)* Se un bucket contiene $k$ gadget, le tacche danno $\sum (a_i + 1) = t + 3$, cioè $\sum a_i = t + 3 - k$. Con $t/4 < a_i < t/2$: $k = 2$ darebbe $\sum a_i = t + 1$, impossibile perché due numeri minori di $t/2$ sommano meno di $t$; $k = 4$ darebbe $\sum a_i = t - 1$, impossibile perché quattro numeri maggiori di $t/4$ sommano più di $t$. Quindi $k = 3$ e $\sum a_i = t$: i bucket definiscono una partizione di $A$ in gruppi di tre numeri di somma $t$.

## Per approfondire
La slide chiude con due riferimenti:
- un corso del MIT (video delle lezioni disponibili): `https://courses.csail.mit.edu/6.892/spring19/` (6.892 Algorithmic Lower Bounds: Fun with Hardness Proofs, primavera 2019, Erik Demaine);
- un compendio di risultati di difficoltà per giochi e puzzle: `https://www.isnphard.com/i/`.

## Riepilogo
| Riduzione | Da | A | Gadget | Claim |
|---|---|---|---|---|
| Super Mario | 3-SAT | livello di Super Mario | Variable, Clause, Crossover | livello risolvibile $\Leftrightarrow$ $\Phi$ soddisfacibile |
| Peg Solitaire (Uehara e Iwata, 1990) | Hamiltonian Cycle in grafi orientati planari di grado 3 | scacchiera di Peg Solitaire | vertice 1-in 2-out, vertice 2-in 1-out, arco (wire), più un piolo aggiuntivo | scacchiera svuotabile $\Leftrightarrow$ $G$ ha un ciclo hamiltoniano |
| Tetris | 3-Partition (anche con $t/4 < a_i < t/2$, strongly NP-hard) | scacchiera di Tetris con sequenza offline di pezzi | bucket con $t+3$ tacche; per ogni $a_i$: initiator, $a_i$ filler, terminator | scacchiera svuotabile $\Leftrightarrow$ 3-Partition ha soluzione |

> [!info] Schema di riduzione: codifica con gadget
> Come in [[09 - NP-Completezza e Riduzioni#La riduzione chiave: 3-SAT $\leq_P$ Independent Set|3-SAT $\leq_P$ Independent Set]], ogni riduzione di questa nota costruisce gadget locali che forzano una scelta (l'uscita di una variabile, l'arco da cancellare in un vertice, il bucket in cui inserire un numero) e collega i gadget in modo che l'unico modo di vincere sia rispettare i vincoli del problema di partenza.
