---
tags:
  - intelligenza-artificiale
  - ricerca
  - euristiche
slide: []
---
# Ricerca non informata e ricerca euristica
Lezione 3 (14/10/2026): i criteri con cui si valuta una strategia di ricerca (completezza, ottimalità, complessità in tempo e spazio), le strategie non informate (ampiezza, costo uniforme, profondità, profondità limitata e approfondimento iterativo, ricerca bidirezionale), la gestione degli stati ripetuti e l'introduzione alla ricerca euristica: best-first, greedy best-first, A\* e le euristiche del gioco dell'8. Prosegue la [[03 - Risoluzione di problemi mediante ricerca#Verso la ricerca euristica|lezione precedente]] e corrisponde al resto del capitolo 3 di AIMA.
## Valutare una strategia di ricerca
Una strategia di ricerca è definita dall'ordine in cui si estraggono i nodi dalla [[03 - Risoluzione di problemi mediante ricerca#La frontiera|frontiera]]. Per confrontare strategie diverse si usano quattro criteri.

> [!quote] Criteri di valutazione
> - **Completezza**: se una soluzione esiste, l'algoritmo la trova sempre (disponendo di risorse sufficienti).
> - **Ottimalità**: la prima soluzione trovata è garantita essere di costo minimo.
> - **Complessità in tempo**: quanto tempo serve per trovare la soluzione, misurato come numero di nodi generati.
> - **Complessità in spazio**: quanta memoria serve durante la ricerca, misurata come numero massimo di nodi in memoria.

L'ottimalità riguarda la soluzione che si **eseguirà**; le due complessità riguardano invece la fase **precedente**, quella in cui si cerca. Tempo e spazio sono dimensioni diverse: si può andare più veloci verso la soluzione memorizzando più informazioni, per non ripetere operazioni inutili.

Le complessità si esprimono con tre grandezze:
- $b$, il **fattore di ramificazione**: il numero (medio o massimo) di successori di un nodo;
- $d$, la **profondità** del nodo obiettivo più vicino alla radice;
- $m$, la **lunghezza massima** di un cammino nello spazio degli stati (può essere infinita).

> [!info] Perché in IA l'ottimo è raro
> Nei problemi completamente osservabili e noti, con risorse sufficienti, le garanzie formali sono raggiungibili. In IA succede raramente, per due motivi:
> 1. **non sempre esiste una formulazione matematica dell'ottimo**: per un motore di ricerca, qual è la sequenza ottima di risultati? Ottima per chi, per tutti gli utenti, per chi vive in una certa zona, per chi ha usato certe parole? Spesso non si conosce nemmeno la funzione che descrive il task, e il machine learning serve proprio a costruire funzioni che approssimano quella ottima senza conoscerla;
> 2. **le risorse non bastano**: l'esplosione combinatoria degli stati impedisce di esplorare tutti i casi, quindi si accettano soluzioni **subottime** che siano buone approssimazioni. Anche un decoder che genera una frase stato dopo stato raggiunge una soluzione che può non essere ottima.
>
> Si ragiona quindi su **quanto è buona l'approssimazione** dell'ottimo, più che su come garantirlo.
## Strategie di ricerca non informata
Le strategie **non informate** (o "cieche") usano solo le informazioni della formulazione del problema: sanno generare successori e riconoscere un obiettivo, ma non sanno dire se uno stato non obiettivo è "più promettente" di un altro. Ampiezza e profondità si danno per note dai corsi di algoritmi; qui interessano le loro proprietà come strategie di ricerca.
### Ricerca in ampiezza
La [[03 - Risoluzione di problemi mediante ricerca#Ricerca in ampiezza|ricerca in ampiezza]] usa una frontiera **FIFO**: espande prima la radice, poi tutti i suoi successori, poi i successori di questi, livello per livello.

> [!example] Evoluzione della frontiera
> In un albero binario con radice $A$, figli $B$ e $C$, nipoti $D, E$ (di $B$) e $F, G$ (di $C$): si espande $A$ e la frontiera è $[B, C]$; si estrae $B$ e si accodano $D$ ed $E$ **dopo** $C$, quindi la frontiera è $[C, D, E]$; il nodo estratto dopo è $C$, non $D$.

- **Completa**: sì, se $b$ è finito. Si visitano tutti i nodi di un livello prima di passare al successivo, quindi non si può "saltare" una soluzione a profondità $d$.
- **Ottima**: sì, se tutte le azioni hanno lo stesso costo. Se la soluzione più vicina è a profondità $d$, non ne esistono a profondità minore (altrimenti sarebbero state trovate prima, essendo entrate prima nella coda). Con costi diversi la soluzione meno profonda non è necessariamente la meno costosa.
- **Tempo**: $b + b^2 + \dots + b^d = O(b^d)$ nodi generati (con il test obiettivo fatto alla generazione).
- **Spazio**: $O(b^d)$, perché la frontiera deve contenere un intero livello.

Il vero limite è la **memoria**. Con $b = 10$, un milione di nodi al secondo e un kilobyte per nodo, a profondità 10 servono ore e terabyte di memoria; a profondità 16 servono anni ed exabyte. In giochi come gli scacchi, o nella guida autonoma, il numero di azioni possibili e la profondità delle soluzioni rendono l'ampiezza inutilizzabile anche su architetture moderne.
### Ricerca a costo uniforme
Se gli archi hanno costi diversi, conviene espandere per primo il nodo raggiunto con il cammino **meno costoso** fin lì: da $S$ con successori $A$, $B$, $C$, se l'arco $S \to A$ costa meno degli altri si parte da $A$. La frontiera diventa una **coda con priorità** ordinata per $g(n)$, il costo del cammino dalla radice a $n$: l'inserimento è ordinato, e il `Pop` restituisce il nodo con $g$ minimo.

Due accorgimenti rispetto all'ampiezza:
- il **test obiettivo** si fa quando un nodo viene **estratto** per l'espansione, non quando viene generato: il primo nodo obiettivo generato potrebbe stare su un cammino più costoso di un altro non ancora scoperto;
- se uno stato già in frontiera viene raggiunto con un cammino **più economico**, si sostituisce il nodo in frontiera con quello nuovo. Se uno stato $G$ è raggiungibile sia da $A$ sia da $B$, si tiene il padre che dà il cammino più breve.

```pseudo
\begin{algorithm}
\caption{Uniform-Cost-Search(problem)}
\begin{algorithmic}
\State $node \gets$ un nodo con $\mathit{State} = problem.\mathit{Initial\text{-}State}$, $\mathit{Path\text{-}Cost} = 0$
\State $frontier \gets$ coda con priorità ordinata per $\mathit{Path\text{-}Cost}$, con $node$ come unico elemento
\State $explored \gets \emptyset$
\Loop
  \If{\Call{Empty?}{$frontier$}}
    \State \Return fallimento
  \EndIf
  \State $node \gets$ \Call{Pop}{$frontier$}
  \If{\Call{Goal-Test}{$node.\mathit{State}$}}
    \State \Return \Call{Solution}{$node$}
  \EndIf
  \State aggiungi $node.\mathit{State}$ a $explored$
  \For{$action \in$ \Call{Actions}{$node.\mathit{State}$}}
    \State $child \gets$ \Call{Child-Node}{$problem, node, action$}
    \If{$child.\mathit{State} \notin explored$ e $child.\mathit{State}$ non è in $frontier$}
      \State $frontier \gets$ \Call{Insert}{$child, frontier$}
    \ElsIf{$child.\mathit{State}$ è in $frontier$ con $\mathit{Path\text{-}Cost}$ maggiore}
      \State sostituisci quel nodo di $frontier$ con $child$
    \EndIf
  \EndFor
\EndLoop
\end{algorithmic}
\end{algorithm}
```

L'insieme $explored$ ricorda gli stati già espansi, per evitare cicli. Il costo $g$ è il **passato**: si usa il cammino già fatto per decidere dove cercare nel futuro.
- **Completa**: sì, se ogni passo costa almeno $\varepsilon > 0$ (vedi il [[03 - Risoluzione di problemi mediante ricerca#Il costo del cammino|costo del cammino]]).
- **Ottima**: sì. I nodi vengono espansi in ordine di $g$ crescente, quindi il primo obiettivo estratto è quello di costo minimo.
- **Tempo e spazio**: $O\big(b^{1 + \lfloor C^*/\varepsilon \rfloor}\big)$, dove $C^*$ è il costo della soluzione ottima. Più gli archi costano poco rispetto a $C^*$, più livelli si esplorano. Con costi tutti uguali si riduce a $O(b^{d+1})$.

È una strategia "golosa" e locale: preferisce i cammini localmente più brevi anche quando non vanno nella direzione giusta. Per andare da Roma a Milano non conviene passare per Frascati solo perché è la città più vicina. Fa quindi esplorazioni inutili, ma la soluzione che restituisce è ottima.

> [!info] Le dimostrazioni delle complessità
> Il docente non le dimostra: chiede di ricostruirle sui libri di algoritmica o discutendole con un LLM, e di condividere i prompt migliori.
### Ricerca in profondità
La ricerca in profondità usa una frontiera **LIFO**: espande sempre il nodo più profondo. Dopo aver espanso $B$ in $D$ ed $E$, invece di passare a $C$ approfondisce $D$, e torna indietro solo quando un ramo è esaurito.
- **Completa**: no. Su spazi infiniti, o con cicli se non si controllano gli stati ripetuti, può scendere all'infinito lungo un ramo senza soluzione.
- **Ottima**: no. Restituisce la prima soluzione che incontra scendendo, che può essere più profonda (e costosa) di un'altra in un ramo non ancora esplorato.
- **Tempo**: $O(b^m)$. Dipende dalla profondità massima $m$, non da quella della soluzione: se $m \gg d$ può cercare troppo a lungo.
- **Spazio**: $O(b\,m)$. In memoria ci sono solo il cammino corrente e, per ogni nodo del cammino, i fratelli non ancora espansi: al più $b$ nodi per ciascuno degli $m$ livelli. La memoria **non cresce esponenzialmente**.

È questo il suo vantaggio: a profondità 16, con le stesse ipotesi di prima, la memoria passa dagli exabyte dell'ampiezza a poche centinaia di kilobyte.
### Profondità limitata e approfondimento iterativo
Un compromesso è la ricerca in profondità con un **limite** $\ell$: i nodi a profondità $\ell$ si trattano come se non avessero successori. Se $\ell < d$ la soluzione non si trova; se $\ell$ è molto più grande di $d$ si torna ai difetti della profondità.

La **ricerca ad approfondimento iterativo** (*iterative deepening*) risolve il problema della scelta di $\ell$: esegue la ricerca a profondità limitata con $\ell = 0, 1, 2, \dots$ finché non trova una soluzione.

```pseudo
\begin{algorithm}
\caption{Iterative-Deepening-Search(problem)}
\begin{algorithmic}
\For{$\ell = 0, 1, 2, \dots$}
  \State $result \gets$ \Call{Depth-Limited-Search}{$problem, \ell$}
  \If{$result \neq$ cutoff}
    \State \Return $result$
  \EndIf
\EndFor
\end{algorithmic}
\end{algorithm}
```

> [!example] Le prime iterazioni
> Con $\ell = 0$ si controlla solo $A$. Con $\ell = 1$ si generano $B$ e $C$, ma non si può scendere oltre: è come una visita in ampiezza del primo livello. Con $\ell = 2$ si riparte da $A$ in profondità: $B$ viene espanso in $D$ ed $E$, che si controllano **prima** di $C$, come in profondità; $C$ si espande solo se $D$ ed $E$ non portano alla soluzione.

Combina i vantaggi delle due visite: la frontiera resta piccola come in profondità e cresce solo se la soluzione è lontana, mentre l'esplorazione per livelli la rende completa come l'ampiezza.
- **Completa**: sì, se $b$ è finito: quando $\ell$ raggiunge $d$ la soluzione viene trovata, purché la memoria basti.
- **Ottima**: sì se le azioni hanno tutte lo stesso costo, come l'ampiezza.
- **Spazio**: $O(b\,d)$.
- **Tempo**: $O(b^d)$. I livelli vicini alla radice vengono rigenerati a ogni iterazione, ma il costo resta dominato dall'ultimo livello:

$$N(\text{IDS}) = d\,b + (d-1)\,b^2 + \dots + 1 \cdot b^d = O(b^d)$$

Con $b = 10$ e $d = 5$ si generano $123\,450$ nodi contro i $111\,110$ dell'ampiezza: lo spreco è piccolo, perché la maggior parte dei nodi sta comunque nell'ultimo livello.

> [!warning] Da verificare
> A lezione l'approfondimento iterativo è stato detto "non ottimo". Secondo AIMA è ottimo quando il costo del cammino è una funzione non decrescente della profondità (ad esempio con costi tutti uguali), e non lo è in generale con costi diversi. Qui si riporta la versione del libro.
### Ricerca bidirezionale
Un problema si può risolvere **in avanti**, dallo stato iniziale verso l'obiettivo (ricerca guidata dai dati), oppure **all'indietro**, dall'obiettivo verso lo stato iniziale (ricerca guidata dall'obiettivo): si immaginano gli stati da cui l'obiettivo è raggiungibile, e se si ritrova $s_0$ si è ricostruito il cammino al contrario.

> [!example] Le dimostrazioni per assurdo
> In analisi, per dimostrare l'unicità del limite si suppone che ci siano due limiti $L_1 \neq L_2$ e si arriva a contraddire un'ipotesi: si parte dalla negazione della tesi e si ragiona all'indietro.

Quale direzione conviene dipende dalla **struttura dello spazio di ricerca**: se attorno all'obiettivo ci sono pochi stati e attorno al punto di partenza moltissimi, andare all'indietro è più rapido. Nella dimostrazione automatica di teoremi (pochi dati, molte regole) si procede di solito all'indietro, come fa l'[[03 - Risoluzione di problemi mediante ricerca#Dimostrazione di teoremi|interprete Prolog]]; nella progettazione di un circuito o nella pianificazione di un robot esploratore si procede in avanti.

La **ricerca bidirezionale** esegue le due ricerche insieme, con due frontiere, e si ferma quando le frontiere si **intersecano**: lo stato in comune collega il cammino in avanti da $s_0$ e quello all'indietro dall'obiettivo. Ciascuna ricerca arriva solo a metà profondità, quindi

$$b^{d/2} + b^{d/2} \ll b^d$$

Serve però saper calcolare i **predecessori** di uno stato, e l'obiettivo deve essere esplicito (con un test obiettivo solo funzionale, come lo scacco matto, è difficile partire dal fondo).
### Confronto tra le strategie
| Criterio | Ampiezza | Costo uniforme | Profondità | Profondità limitata | Approfondimento iterativo | Bidirezionale |
|---|---|---|---|---|---|---|
| Completa | sì¹ | sì¹ ² | no | no | sì¹ | sì¹ ⁴ |
| Ottima | sì³ | sì | no | no | sì³ | sì³ ⁴ |
| Tempo | $O(b^d)$ | $O(b^{1+\lfloor C^*/\varepsilon \rfloor})$ | $O(b^m)$ | $O(b^\ell)$ | $O(b^d)$ | $O(b^{d/2})$ |
| Spazio | $O(b^d)$ | $O(b^{1+\lfloor C^*/\varepsilon \rfloor})$ | $O(b\,m)$ | $O(b\,\ell)$ | $O(b\,d)$ | $O(b^{d/2})$ |

¹ se $b$ è finito; ² se ogni passo costa almeno $\varepsilon > 0$; ³ se i passi hanno tutti lo stesso costo; ⁴ se in entrambe le direzioni si usa l'ampiezza.

> [!question] Domanda tipica d'esame
> Il docente ha detto esplicitamente che all'orale chiederà di discutere questa tabella. Per ogni casella si deve saper spiegare il perché: ad esempio, perché la ricerca in profondità non è ottima o non è completa. Per negare una proprietà basta un **controesempio**: un albero in cui la profondità trova prima una soluzione più profonda di un'altra, o un ramo infinito da cui non esce.
## Stati ripetuti
Se lo spazio degli stati non è un albero ma un grafo, la ricerca ad albero può ripetere gli stessi stati: per i cicli (in profondità può non terminare) o semplicemente perché lo stesso stato è raggiungibile con cammini diversi, e l'albero di ricerca si riempie di duplicati. Tre rimedi, dal più economico al più completo:
1. non tornare nello stato da cui si proviene (non generare il padre come successore);
2. non generare successori che siano **antenati** del nodo, cioè controllare il cammino dalla radice (evita i cicli);
3. non generare stati **già visitati**: si ricorda ogni stato espanso in una struttura con accesso rapido, tipicamente una **tabella hash**, e lo si scarta se ricompare. È l'insieme $explored$ della ricerca a costo uniforme.

> [!info] Programma
> Le varianti per i grafi (*graph search*) sono state presentate come facoltative e non fanno parte del programma d'esame.
## Ricerca euristica
Una strategia **informata** usa conoscenza specifica del problema, oltre alla sua definizione, per capire quali successori sono più **promettenti** verso l'obiettivo. Anche un LLM, mentre genera una frase un pezzo alla volta, non procede a caso: sa che la frase finale deve avere certe caratteristiche e orienta la ricerca verso di essa.
### Best-first e funzione di valutazione
Nella ricerca **best-first** si usa lo schema della ricerca a costo uniforme, ma la priorità della frontiera è data da una **funzione di valutazione** $f(n)$, e si espande il nodo con $f$ migliore.
- Se $f$ misura un vantaggio (quanto è buona, utile, elegante la soluzione), va **massimizzata**.
- Se $f$ è un costo, come una distanza dall'obiettivo, va **minimizzata**. È il caso usuale.

La ricerca a costo uniforme è il caso $f(n) = g(n)$.

> [!quote] Funzione euristica
> Una **funzione euristica** $h(n)$ stima il costo del cammino più economico dallo stato del nodo $n$ a uno stato obiettivo. Dipende dal problema, e vale $h(n) = 0$ se $n$ è un nodo obiettivo.

$g(n)$ è **nota**: durante la ricerca si sa esattamente quanto è costato arrivare a $n$. $h(n)$ è un'**ipotesi** sul futuro, una legge inventata per approssimare una verità che non si conosce (se si conoscesse il costo esatto verso l'obiettivo, il problema sarebbe già risolto). Il nome viene dalla stessa idea del machine learning, dove $h$ è l'ipotesi con cui si approssima una funzione sconosciuta a partire dai dati.

> [!example] Euristiche
> - **Navigazione stradale**: la distanza **in linea d'aria** dalla destinazione. Per andare da Roma a Milano, una città a sud come Frascati ha distanza maggiore di una a nord, come Civitavecchia. Non serve conoscere tutta la rete stradale: bastano le coordinate geografiche. È una **sottostima** del costo vero, perché raramente c'è una strada in linea retta.
> - **Gioco dell'8**: il numero di tessere fuori posto.
> - **Scacchi**: il numero di pezzi avversari che si mettono sotto scacco.
>
> Sono imprecise come il passante che, a chi chiede il distributore, risponde "è avanti un paio di chilometri": dice la direzione giusta, ma i chilometri magari sono otto.
### Greedy best-first
La ricerca **greedy best-first** usa $f(n) = h(n)$: dimentica il passato e sceglie il nodo che **sembra** più vicino all'obiettivo.

> [!example] Da Arad a Bucarest
> Con $h$ = distanza in linea d'aria da Bucarest, la greedy best-first va Arad → Sibiu → Fagaras → Bucarest (450 km), mentre il cammino ottimo è Arad → Sibiu → Rimnicu Vilcea → Pitesti → Bucarest (418 km). Fagaras sembra più vicina all'obiettivo, ma la strada da lì costa di più.

Non è quindi ottima (e, senza controllo degli stati ripetuti, nemmeno completa); ma l'idea di guardare **in avanti** è buona e riduce molto l'esplorazione.

> [!info] Terminologia
> A lezione la ricerca a costo uniforme è stata chiamata anche "best-first" e la variante con $h$ "greedy best-first". In AIMA *best-first* è lo schema generale con una qualunque $f$; costo uniforme ($f = g$) e greedy ($f = h$) ne sono casi particolari.
### A\*
L'idea degli algoritmi ottimi è combinare passato e futuro:

$$f(n) = g(n) + h(n)$$

cioè il costo stimato della migliore soluzione che passa per $n$: quanto è costato arrivare fin lì più quanto si spera manchi. L'algoritmo è identico alla ricerca a costo uniforme (coda con priorità, controllo all'inserimento in frontiera, insieme degli stati esplorati); cambia solo $f$. Con una **buona euristica** questo algoritmo, detto **A\***, è **completo e ottimo**: con costi positivi, $f$ cresce lungo i cammini e il primo obiettivo estratto è quello di costo minimo. Le condizioni su $h$ si vedono nella prossima lezione.

> [!example] Labirinto
> In una simulazione su un labirinto di circa $40 \times 40$ celle (fattore di ramificazione 4), A\* visita solo una piccola parte delle celle che esplorerebbe una ricerca cieca. È lo stesso tipo di problema dell'esercitazione: il piano si calcola prima di muovere il robot.

> [!info] Il riconoscimento del parlato come ricerca
> In un dizionario, i successori di un fonema sono migliaia invece di 4, e una frase di poche decine di parole è fatta di molte decine di fonemi, senza silenzi che separano le parole: bisogna anche decidere dove segmentare. Un assistente vocale che non sa in che lingua si parla combina la probabilità della lingua e quella dei fonemi. È una ricerca in cui l'euristica è la **probabilità di una stringa in una lingua**, stimata ad esempio con i bigrammi di fonemi.
### Euristiche per il gioco dell'8
Per il [[03 - Risoluzione di problemi mediante ricerca#Il gioco dell'8|gioco dell'8]] si usano due euristiche classiche:
- $h_1$, il **numero di tessere fuori posto**. Si calcola facilmente, vale 0 solo nella configurazione obiettivo, e dice almeno quante mosse servono: ogni tessera fuori posto va mossa almeno una volta;
- $h_2$, la **distanza di Manhattan**: la somma, su tutte le tessere, del numero di righe e colonne che separano ciascuna dalla sua posizione finale.

> [!example] Lo stato iniziale di AIMA
> Nello stato iniziale dell'esempio del libro nessuna tessera è al suo posto, quindi $h_1 = 8$. Sommando le distanze di Manhattan delle otto tessere (ad esempio 3 mosse per l'1, 1 per il 2) si ottiene $h_2 = 18$.

$h_2$ è sempre maggiore o uguale a $h_1$, quindi stima il costo vero in modo più preciso, distingue meglio tra continuazioni diverse e porta prima alla soluzione ottima.

> [!warning] Da verificare
> A lezione $h_2$ è stata descritta come una "sovrastima" del costo. Entrambe le euristiche sono in realtà **sottostime** del numero reale di mosse: $h_2$ è solo più vicina al valore vero. Se ne riparlerà nella lezione sulle proprietà delle euristiche.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra ricerca a costo uniforme, greedy best-first e A\*? Spiega il ruolo di $g(n)$ e di $h(n)$, mostra con l'esempio della Romania perché la greedy best-first non è ottima, e proponi un'euristica per il gioco dell'8.
