---
tags:
  - algoritmi-big-data
  - probabilita
  - analisi-del-caso-medio
  - concentrazione
slide: []
---
# Analisi del caso medio e disuguaglianze di concentrazione
Lezione 4 (15/10/2026): si distingue l'analisi di un algoritmo randomizzato su un input peggiore dall'**analisi del caso medio** di un algoritmo deterministico su un input casuale, rifacendo il quicksort nei due modi a partire dal [[03 - Variabili aleatorie e valore atteso#Randomized quicksort|randomized quicksort]] della lezione precedente. Seguono una classificazione degli algoritmi randomizzati per problemi decisionali, la **distribuzione geometrica** con il problema del **coupon collector** e i primi strumenti per misurare quanto una variabile aleatoria si discosta dal suo valore atteso: varianza, **disuguaglianza di Markov** e **disuguaglianza di Chebyshev**.
## Algoritmi randomizzati e analisi del caso medio
### Il randomized quicksort, ancora
Nel randomized quicksort il numero di confronti è una variabile aleatoria definita sullo spazio delle scelte dei pivot $y$; anche **quanti** pivot si scelgono è aleatorio (in alcune esecuzioni l'albero delle chiamate è profondo $\log n$, in altre $n$). Il teorema dice che, **per qualunque input fissato**, anche il peggiore, il numero atteso di confronti è $O(n \log n)$: il caso peggiore riguarda l'input, il valore atteso riguarda le scelte dell'algoritmo. L'analisi si basava su [[03 - Variabili aleatorie e valore atteso#Dimostrazione con la linearità|indicatrici e linearità]]: $s_i$ e $s_j$ si confrontano con probabilità $2/(j - i + 1)$, e la somma dà la serie armonica.

La probabilità entra però nell'algoritmica in due modi diversi.
- **Algoritmi randomizzati**: l'algoritmo, oltre a confronti, cicli e strutture dati, ogni tanto **lancia un bit casuale** e decide in base al risultato. L'input è nel caso peggiore, scelto da un **avversario** che conosce il codice ma **non** le scelte casuali fatte durante l'esecuzione (sa che al passo 33 si sceglierà un pivot a caso, non quale). L'avversario sceglie l'input "a bocce ferme", prima dell'esecuzione. È la stessa ipotesi su cui si regge la crittografia: l'avversario non legge i numeri casuali del sistema.
- **Analisi del caso medio** (*average case analysis*, o analisi probabilistica): l'algoritmo è **deterministico**, e si assume invece un **modello statistico dell'input**, cioè uno spazio di tutti gli input possibili con una distribuzione di probabilità. Le grandezze (tempo, spazio) sono valori attesi rispetto a quella distribuzione.

I due approcci si possono anche combinare.

> [!example] Dijkstra nel caso medio
> Normalmente Dijkstra si analizza sul grafo peggiore. Un'analisi del caso medio fissa $n$ e considera **tutti** i grafi con $n$ nodi: sono un numero esponenziale ma finito, quindi si può mettere su di essi la distribuzione uniforme e calcolare il numero atteso di confronti su un grafo scelto a caso.
### Quicksort deterministico su input casuale
Per l'ordinamento lo spazio degli input sembra infinito (gli elementi sono reali qualsiasi). Ma a un algoritmo per confronti non interessa se un valore è 56 o 57,1: conta solo l'**ordine relativo** degli elementi. Fissato $n$ e chiamati $s_1 < s_2 < \dots < s_n$ gli elementi ordinati, gli input possibili sono le $n!$ **permutazioni**.

> [!quote] Modello di input uniforme
> L'input è una permutazione di $s_1, \dots, s_n$ scelta uniformemente a caso: ciascuna delle $n!$ permutazioni ha probabilità $1/n!$.

Si analizza la versione **deterministica** del quicksort, in cui il pivot è sempre il **primo** elemento della lista corrente.

```pseudo
\begin{algorithm}
\caption{DetQuickSort($S$)}
\begin{algorithmic}
\If{$|S| \leq 1$}
  \State \Return $S$
\EndIf
\State $y \gets$ primo elemento di $S$
\State $S_1 \gets$ elementi di $S$ minori di $y$, nell'ordine in cui compaiono
\State $S_2 \gets$ elementi di $S$ maggiori di $y$, nell'ordine in cui compaiono
\State \Return \Call{DetQuickSort}{$S_1$}, $y$, \Call{DetQuickSort}{$S_2$}
\end{algorithmic}
\end{algorithm}
```

Nel caso peggiore (ad esempio un vettore già ordinato al contrario) fa $\Theta(n^2)$ confronti.

> [!quote] Teorema
> Se l'input è una permutazione uniforme, il numero atteso di confronti di DetQuickSort è $O(n \log n)$.

La dimostrazione ricalca quella del randomized quicksort, con le stesse indicatrici $X_{ij}$. Cambia solo il **motivo** per cui $\Pr[X_{ij} = 1] = 2/(j - i + 1)$: $s_i$ e $s_j$ restano nella stessa sottolista finché il pivot non è uno degli elementi $s_i, \dots, s_j$, e il pivot è sempre il primo della sottolista nell'ordine dell'input. Quindi si confrontano se e solo se, tra i $j - i + 1$ elementi $s_i, \dots, s_j$, il **primo a comparire nell'input** è $s_i$ o $s_j$. Nella permutazione uniforme ognuno di quei $j - i + 1$ elementi ha la stessa probabilità di essere il primo: casi favorevoli 2 su $j - i + 1$. La somma dà di nuovo la serie armonica.

> [!warning] Due enunciati diversi
> Il risultato è identico nella forma, $O(n \log n)$ atteso, ma ha un significato completamente diverso. Per il randomized quicksort l'input è **fissato e arbitrario** e il valore atteso è sulle **scelte dell'algoritmo**. Per il quicksort deterministico l'algoritmo non genera alcuno spazio di probabilità e il valore atteso è sul **modello dell'input**. Se le permutazioni non sono equiprobabili (ad esempio con elementi in posizioni ricorrenti) l'analisi del caso medio non vale più.

> [!info] Perché si chiama *quick* sort
> Anche selection sort e insertion sort costano $\Theta(n^2)$ nel caso peggiore, ma per il quicksort le permutazioni "cattive" sono **poche**: l'avversario deve disporre gli elementi in modo molto particolare. Per il selection sort, invece, moltissime configurazioni costano $\Theta(n^2)$. Il modello statistico dell'input fa emergere questa differenza, ed è per questo che la sua costruzione, con le assunzioni dichiarate esplicitamente, è importante quanto l'algoritmo.
### Tipi di algoritmi randomizzati
Per un **problema decisionale**, in cui ogni istanza ha risposta sì o no (un grafo è connesso? è 3-colorabile?), un algoritmo randomizzato può essere:
- a **errore bilaterale** (*two-sided error*): probabilità di errore maggiore di zero sia sulle istanze sì sia sulle istanze no;
- a **errore unilaterale** (*one-sided error*): sbaglia solo su uno dei due tipi di istanza. Sono di questo tipo l'[[02 - Algoritmi randomizzati#Soluzione randomizzata|identity testing tra polinomi]] e la verifica del prodotto tra matrici: se rispondono "diversi" hanno sempre ragione;
- **Las Vegas**: quando risponde, risponde sempre correttamente, ma a volte non risponde. Per la soddisfacibilità di una formula in forma normale congiuntiva, ad esempio, può dire "sì" (ed è certo), "no" (ed è certo) oppure "?". Se la probabilità di "?" è al più $1/3$, ripetendo l'algoritmo cresce la confidenza di ottenere prima o poi la risposta.

I problemi di ottimizzazione si riducono a problemi decisionali con un parametro: invece del numero minimo di colori, ci si chiede se esiste una colorazione con al più $k$ colori.

> [!info] Domanda a lezione: e il randomized quicksort?
> L'ordinamento non è un problema decisionale: non ci sono istanze sì e istanze no. È un problema di **ricerca**, e si può vedere come problema di **ottimizzazione**: data la permutazione in input, minimizzare il numero di **inversioni** nella permutazione in uscita (il minimo è sempre 0). Il randomized quicksort risponde sempre correttamente; la casualità serve solo a migliorare l'efficienza.
## Distribuzione geometrica
> [!quote] Variabile geometrica
> Si ripete un esperimento che ha successo con probabilità $p$, in modo indipendente a ogni tentativo. La variabile **geometrica** $X$ di parametro $p$ conta il numero di tentativi fino al primo successo compreso:
> $$\Pr[X = n] = (1 - p)^{n - 1}\,p \qquad n = 1, 2, \dots$$

I primi $n - 1$ tentativi devono fallire, ciascuno con probabilità $1 - p$, e l'$n$-esimo deve riuscire; per l'indipendenza le probabilità si moltiplicano. Ad esempio, $X$ può contare i lanci di moneta fino alla prima testa: anche 100 000 croci di fila sono improbabili ma possibili.

> [!quote] Assenza di memoria
> Per ogni $n \geq 1$ e $k \geq 0$:
> $$\Pr[X = n + k \mid X > k] = \Pr[X = n]$$

Sapere che i primi $k$ tentativi sono falliti non cambia nulla: è come ripartire da zero. Per questo non ha senso puntare su un numero "in ritardo" al lotto. *Dimostrazione*: per definizione di probabilità condizionata il membro sinistro vale $\Pr[X = n + k] / \Pr[X > k]$; il numeratore è $(1 - p)^{n + k - 1} p$ e il denominatore, una serie geometrica, vale $\sum_{i \geq k} (1 - p)^i p = (1 - p)^k$. Il rapporto è $(1 - p)^{n - 1} p$.

Per una variabile a valori naturali vale

$$\mathbb{E}[X] = \sum_{i=1}^{\infty} \Pr[X \geq i]$$

perché, scrivendo $\Pr[X \geq i] = \sum_{j \geq i} \Pr[X = j]$ e scambiando le somme, il termine $\Pr[X = j]$ compare esattamente $j$ volte, una per ogni $i \leq j$. Per la geometrica $\Pr[X \geq i] = (1 - p)^{i - 1}$, quindi

$$\mathbb{E}[X] = \sum_{i=1}^{\infty} (1 - p)^{i - 1} = \frac{1}{p}$$

Con una moneta equa servono in media 2 lanci per la prima testa; con probabilità di successo $1/150$ servono in media 150 tentativi.
### Il coupon collector
> [!example] L'album di figurine
> Ogni pacchetto contiene una figurina scelta uniformemente a caso tra $n$, indipendentemente dalle precedenti. Quanti pacchetti servono in media per completare l'album? Lo stesso processo descrive l'allocazione online di risorse in cui ogni agente deve ricevere una risorsa almeno una volta.

Si divide il processo in **epoche**: l'epoca $i$ va dal momento in cui si ha l'$(i-1)$-esima figurina distinta a quello in cui si ottiene l'$i$-esima. Sia $X_i$ la sua durata.
- La prima figurina è sempre nuova, quindi $X_1 = 1$.
- Già $X_2$ è aleatoria: un collezionista sfortunato può trovare per cento volte la stessa figurina.
- Nell'epoca $i$ ci sono già $i - 1$ figurine, e ogni pacchetto ne porta una nuova con probabilità $p_i = 1 - \frac{i-1}{n} = \frac{n - i + 1}{n}$. Quindi $X_i$ è **geometrica** di parametro $p_i$.
- L'ultima epoca ha $p_n = 1/n$: tutte le figurine sono sempre equiprobabili, ma ne serve solo una. Per questo gli ultimi buchi dell'album sono i più lenti da riempire.

Il numero totale di pacchetti è $X = \sum_{i=1}^{n} X_i$ e, per linearità,

$$\mathbb{E}[X] = \sum_{i=1}^{n} \frac{1}{p_i} = \sum_{i=1}^{n} \frac{n}{n - i + 1} = n \sum_{k=1}^{n} \frac{1}{k} = n\,H_n = n \ln n + \Theta(n)$$

> [!question] Domanda tipica d'esame
> Qual è il numero atteso di estrazioni per vedere tutti gli $n$ coupon almeno una volta? Spiega la divisione in epoche, perché la durata di ogni epoca è geometrica e con quale parametro, e dove si usa la linearità del valore atteso.
## Concentrazione attorno al valore atteso
In data mining non basta dire che un algoritmo ci mette tempo atteso $n \log n$: bisogna sapere **con che probabilità ci si discosta molto** dal valore atteso. Due distribuzioni possono avere lo stesso valore atteso ed essere completamente diverse:
- una **campana stretta** attorno alla media: nelle esecuzioni reali il tempo sarà quasi sempre vicino al valore atteso, ad esempio tra $\frac12 n \log n$ e $2 n \log n$, e il valore atteso è una buona previsione;
- una distribuzione a **due gobbe**, con la massa lontana a sinistra e a destra: il valore atteso non viene quasi mai osservato, e scommettere su di esso è pessimo.

> [!example] Tre giochi con lo stesso valore atteso
> Si vince o si perde 1 euro con probabilità $\frac12$; oppure si vincono o si perdono 100 000 euro con probabilità $\frac12$; oppure un gioco molto sbilanciato con una vincita enorme e rarissima. Il valore atteso è circa lo stesso, ma con un budget di 100 euro nel primo gioco si fanno tranquillamente un centinaio di tentativi, mentre nel secondo si può fallire al primo.

Studiare quanto una variabile si discosta dalla media è l'**analisi del secondo momento** (o della varianza).
### Disuguaglianza di Markov
> [!quote] Disuguaglianza di Markov
> Sia $X$ una variabile aleatoria **non negativa**. Per ogni $a > 0$:
> $$\Pr[X \geq a] \leq \frac{\mathbb{E}[X]}{a}$$

*Dimostrazione.* Dalla definizione di valore atteso, trascurando i termini con $x < a$ (che sono non negativi) e minorando $x$ con $a$ negli altri:

$$\mathbb{E}[X] = \sum_x x \Pr[X = x] \geq \sum_{x \geq a} a \Pr[X = x] = a \Pr[X \geq a]$$

L'unica ipotesi è la non negatività: niente sull'indipendenza. Proprio per questo vale sempre, ma è molto **debole**.

> [!example] Troppe teste
> Lanciando $n$ monete eque, sia $X$ il numero di teste, con $\mathbb{E}[X] = n/2$. La probabilità di avere almeno $\frac34 n$ teste è
> $$\Pr\left[X \geq \tfrac34 n\right] \leq \frac{n/2}{3n/4} = \frac23$$
> Una costante, indipendente da $n$: secondo Markov la probabilità di stare lontano dalla media non diminuirebbe nemmeno con un milione di lanci. La legge dei grandi numeri dice il contrario: Markov non sfrutta l'indipendenza dei lanci.
### Varianza
> [!quote] Varianza e deviazione standard
> La **varianza** di $X$ è il valore atteso del quadrato della distanza dalla media:
> $$\mathrm{Var}[X] = \mathbb{E}\big[(X - \mathbb{E}[X])^2\big] = \mathbb{E}[X^2] - \mathbb{E}[X]^2$$
> La **deviazione standard** è $\sigma[X] = \sqrt{\mathrm{Var}[X]}$.

Se la variabile sta spesso lontano dalla media la varianza è grande (le due gobbe); se è concentrata, come in una binomiale, è piccola. Il termine $\mathbb{E}[X^2]$ è il difficile: il quadrato non è lineare, e nei doppi prodotti entrano le **correlazioni**.

> [!example] Varianza di una Bernoulliana
> Per $X$ Bernoulliana di parametro $\frac12$:
> $$\mathrm{Var}[X] = \tfrac12\left(1 - \tfrac12\right)^2 + \tfrac12\left(0 - \tfrac12\right)^2 = \tfrac14$$
> In generale una Bernoulliana di parametro $p$ ha varianza $p(1 - p)$.

> [!quote] Variabili indipendenti
> Se $X$ e $Y$ sono **indipendenti**:
> $$\mathbb{E}[X\,Y] = \mathbb{E}[X]\,\mathbb{E}[Y] \qquad \mathrm{Var}[X + Y] = \mathrm{Var}[X] + \mathrm{Var}[Y]$$
> e lo stesso vale per somme di più variabili indipendenti a due a due.

La prima si dimostra dalla definizione: $\mathbb{E}[XY] = \sum_i \sum_j i\,j \Pr[(X = i) \cap (Y = j)]$, e per l'indipendenza la probabilità si fattorizza in $\Pr[X = i]\Pr[Y = j]$; la somma si separa nel prodotto dei due valori attesi. La seconda segue sviluppando il quadrato (la dimostrazione non è in programma). A differenza della [[03 - Variabili aleatorie e valore atteso#Linearità del valore atteso|linearità del valore atteso]], queste proprietà **richiedono** l'indipendenza.

Per una binomiale $B(n, \frac12)$, somma di $n$ Bernoulliane indipendenti, si ottiene quindi $\mathrm{Var}[X] = n/4$.
### Disuguaglianza di Chebyshev
> [!quote] Disuguaglianza di Chebyshev
> Per ogni variabile aleatoria $X$ e ogni $a > 0$:
> $$\Pr\big[\,|X - \mathbb{E}[X]| \geq a\,\big] \leq \frac{\mathrm{Var}[X]}{a^2}$$

*Dimostrazione.* L'evento $|X - \mathbb{E}[X]| \geq a$ coincide con $(X - \mathbb{E}[X])^2 \geq a^2$. La variabile $(X - \mathbb{E}[X])^2$ è non negativa, quindi per Markov

$$\Pr\big[(X - \mathbb{E}[X])^2 \geq a^2\big] \leq \frac{\mathbb{E}\big[(X - \mathbb{E}[X])^2\big]}{a^2} = \frac{\mathrm{Var}[X]}{a^2}$$

Due forme equivalenti, molto usate:
- con $a = t\,\sigma[X]$: $\Pr[|X - \mathbb{E}[X]| \geq t\,\sigma[X]] \leq 1/t^2$;
- con un errore **relativo** $a = \varepsilon\,\mathbb{E}[X]$: $\Pr[|X - \mathbb{E}[X]| \geq \varepsilon\,\mathbb{E}[X]] \leq \dfrac{\mathrm{Var}[X]}{\varepsilon^2\,\mathbb{E}[X]^2}$.

> [!example] Troppe teste, con Chebyshev
> Si riprende il lancio di $n$ monete. Avere almeno $\frac34 n$ teste significa discostarsi dalla media $n/2$ di almeno $n/4 = \frac12\,\mathbb{E}[X]$. Con $\varepsilon = \frac12$ e $\mathrm{Var}[X] = n/4$:
> $$\Pr\left[X \geq \tfrac34 n\right] \leq \Pr\left[|X - \tfrac n2| \geq \tfrac n4\right] \leq \frac{n/4}{(n/4)^2} = \frac{4}{n}$$
> La probabilità ora **tende a zero** al crescere di $n$, e la stima copre entrambe le code. La differenza rispetto a Markov viene dall'aver usato l'indipendenza dei lanci, attraverso la varianza.

> [!warning] Da verificare
> La registrazione si interrompe mentre il docente sostituisce i valori nella disuguaglianza di Chebyshev: il risultato $4/n$ è il calcolo standard (Mitzenmacher-Upfal, cap. 3) e va confrontato con le slide della lezione, disponibili su Teams.

> [!question] Domanda tipica d'esame
> Enuncia e dimostra le disuguaglianze di Markov e di Chebyshev. Applicale alla probabilità di ottenere almeno $\frac34 n$ teste su $n$ lanci indipendenti e spiega perché Chebyshev dà un risultato molto migliore.
