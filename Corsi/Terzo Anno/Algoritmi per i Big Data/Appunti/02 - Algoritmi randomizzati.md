---
tags:
  - algoritmi-big-data
  - algoritmi-randomizzati
  - probabilita
slide: []
---
# Algoritmi randomizzati
Lezione 2 (08/10/2026), prima lezione sulla parte di probabilità e algoritmi randomizzati annunciata nella [[01 - Introduzione al corso e al data mining]]. Si introducono le due famiglie di algoritmi randomizzati (Monte Carlo e Las Vegas) e si lavora su tre problemi: l'identità tra polinomi, la verifica del prodotto tra matrici e il taglio minimo di un grafo. Su tutti vale lo stesso schema: un algoritmo semplice che può sbagliare, una **probabilità di errore** da maggiorare, e la **ripetizione indipendente** per renderla piccola quanto si vuole.
## Monte Carlo e Las Vegas
Si lavora in un modello RAM esteso: memoria, scrittura e lettura costano tempo costante e in più si può **generare un valore casuale in tempo costante**. Generare valori davvero casuali non è banale, ma si assume di poterlo fare.
> [!quote] Algoritmo Monte Carlo
> Algoritmo randomizzato con **tempo di esecuzione deterministico** ma con una certa **probabilità di errore** nella risposta. Per un problema decisionale (risposta vero/falso) può restituire la risposta sbagliata con probabilità limitata.

> [!quote] Algoritmo Las Vegas
> Algoritmo randomizzato che restituisce **sempre la risposta corretta**, ma il cui **tempo di esecuzione è una variabile aleatoria**.

> [!example] Quicksort con pivot casuale
> Il quicksort sceglie un pivot, partiziona l'array in elementi minori e maggiori e ricorre sulle due parti. Nel caso peggiore (pivot sempre minimo o massimo) la ricorsione perde un solo elemento per volta e il costo è $O(n^2)$. Scegliendo il pivot **a caso**, e assumendo che l'avversario non conosca le nostre scelte random, il costo medio è $O(n\log n)$. È quindi un algoritmo Las Vegas: sempre corretto, tempo aleatorio.

Il caso peggiore è spesso troppo pessimistico per gli algoritmi randomizzati, per questo si analizza il caso medio rispetto alle scelte random. Oggi si vedono solo algoritmi Monte Carlo, e il tema ricorrente è **rendere la probabilità di errore piccola a piacere**.
## Identity testing tra polinomi
> [!quote] Problema
> Dati due polinomi $f(x)$ e $g(x)$, stabilire se $f\equiv g$, cioè se $f(r)=g(r)$ per ogni valore $r$.

Esempio visto a lezione: due polinomi scritti in forma diversa (uno con termini $x^6, \dots$) di cui si vuole sapere se coincidono.
### Soluzione deterministica
Si portano entrambi in **forma canonica** $\sum_i c_i x^i$ e si confrontano i coefficienti di ogni potenza. Con $d$ grado massimo il costo è $O(d^2)$ nel caso peggiore.
### Soluzione randomizzata
Due polinomi sono diversi se **esiste** un valore $r$ in cui $f(r)\neq g(r)$. Valutare un polinomio di grado $d$ in un punto costa $O(d)$ operazioni (somme e prodotti a costo costante). L'idea è quindi confrontare i polinomi in un punto scelto a caso.
```pseudo
\begin{algorithm}
\caption{IdentityTestingPolinomi($f$, $g$)}
\begin{algorithmic}
\State $d \gets$ grado massimo tra $f$ e $g$
\State $S \gets \{1, 2, \dots, 100d\}$
\State scegli $r \in S$ uniformemente a caso
\If{$f(r) = g(r)$}
  \State \Return "uguali"
\Else
  \State \Return "diversi"
\EndIf
\end{algorithmic}
\end{algorithm}
```

Si sceglie un insieme finito di interi, e non tutto $\mathbb{R}$, perché un calcolatore non può rappresentare tutti i reali. Il tempo è $O(d)$, contro $O(d^2)$ del metodo deterministico.
> [!info] Errore a un lato (one-sided error)
> Se l'algoritmo risponde "diversi" è **certo** che i polinomi sono diversi (si è trovato un $r$ che li distingue). Può sbagliare solo rispondendo "uguali" quando in realtà sono diversi: un solo valore può essere una **coincidenza**.
### Probabilità di errore
Se $f\not\equiv g$, il polinomio $h=f-g$ è non nullo di grado al più $d$. Per il teorema fondamentale dell'algebra ha **al più $d$ radici**. L'algoritmo sbaglia solo se $r$ è una radice di $h$, quindi per $r$ uniforme su $S$ con $|S|=100d$:
$$\Pr[\text{errore}]\le \frac{\#\text{casi favorevoli}}{\#\text{casi possibili}}\le\frac{d}{100d}=\frac{1}{100}$$
Le radici di $h$ possono essere negative o non intere: in quel caso cadono fuori da $S$ e l'errore è anche minore, quindi $d/|S|$ resta una maggiorazione valida. Con un approccio deterministico basterebbe invece valutare i polinomi in $d+1$ punti distinti.
### Ridurre l'errore: ripetizione indipendente
Un errore dell'1% può essere troppo se l'algoritmo viene usato un miliardo di volte. Si **ripete l'algoritmo $k$ volte** con scelte indipendenti $r_1,\dots,r_k$ e si risponde "diversi" se almeno una prova lo dice. L'algoritmo sbaglia solo se sbagliano **tutte** le $k$ prove, cioè se tutti gli eventi di errore accadono insieme (intersezione). Essendo le scelte indipendenti si moltiplicano le probabilità:
$$\Pr[\text{errore su } k \text{ prove}]=\prod_{i=1}^{k}\Pr[\text{errore alla prova } i]\le\left(\frac{1}{100}\right)^{k}$$
Ogni prova in più moltiplica la fiducia nella risposta. Per avere un errore piccolo come $1/n$ basta $k=O(\log n)$ ripetizioni.
## Richiami di probabilità
> [!quote] Spazio di probabilità
> Terna $(\Omega,\mathcal{F},\Pr)$, dove $\Omega$ è lo **spazio campionario** (l'insieme di tutti i possibili esiti dell'esperimento), $\mathcal{F}$ è l'insieme degli **eventi** (nel caso discreto, tutti i sottoinsiemi di $\Omega$, cioè $\mathcal{F}=2^\Omega$) e $\Pr$ è una **funzione di probabilità** che soddisfa:
> 1. $0\le\Pr[E]\le 1$ per ogni evento $E$;
> 2. $\Pr[\Omega]=1$;
> 3. per eventi $E_1,E_2$ **disgiunti** ($E_1\cap E_2=\emptyset$): $\Pr[E_1\cup E_2]=\Pr[E_1]+\Pr[E_2]$ (additività, estesa a successioni di eventi disgiunti).

> [!quote] Union bound
> Per **qualsiasi** famiglia di eventi $E_1,\dots,E_n$, senza ipotesi sulle relazioni tra di loro:
> $$\Pr\left[\bigcup_{i=1}^{n}E_i\right]\le\sum_{i=1}^{n}\Pr[E_i]$$
> Con eventi disgiunti vale l'uguaglianza; in generale è una **maggiorazione**.

Spesso è una maggiorazione grossolana (anche inutile, se la somma supera 1), ma permette di trattare i singoli eventi **senza studiare le loro dipendenze**.

Servono anche la **probabilità condizionata** $\Pr[E\mid F]=\Pr[E\cap F]/\Pr[F]$, la **probabilità totale** (si somma sui casi di una partizione dello spazio) e la **regola della catena**
$$\Pr[E_1\cap\dots\cap E_n]=\Pr[E_1]\cdot\Pr[E_2\mid E_1]\cdots\Pr[E_n\mid E_1\cap\dots\cap E_{n-1}]$$
## Verifica del prodotto tra matrici (Freivalds)
> [!quote] Problema
> Date tre matrici $A,B,C\in\mathbb{R}^{n\times n}$, stabilire se $A\cdot B=C$.

- Metodo classico: calcolare $A\cdot B$ in $O(n^3)$ e confrontare con $C$ ($O(n^2)$).
- Il miglior algoritmo noto per la moltiplicazione ha costo $O(n^{\omega})$ con $\omega\ge 2.37$ circa (la costante scende ogni tanto con nuove ricerche), ma gli algoritmi sono molto particolari e poco pratici.
- Con la randomizzazione si verifica l'uguaglianza in $O(n^2)$.

L'idea generalizza il caso dei polinomi: invece di sostituire un numero a caso si sostituisce un **vettore a caso**. Se $AB=C$ allora $ABr=Cr$ per ogni vettore $r$; si sceglie un $r\in\{0,1\}^n$ e si controlla l'uguaglianza solo per quello.
```pseudo
\begin{algorithm}
\caption{VerificaProdotto($A$, $B$, $C$)}
\begin{algorithmic}
\State scegli $r \in \{0,1\}^n$ a caso (ogni componente uniforme e indipendente)
\State $x \gets B\,r$
\State $y \gets A\,x$
\State $z \gets C\,r$
\If{$y = z$}
  \State \Return "$AB = C$"
\Else
  \State \Return "$AB \neq C$"
\EndIf
\end{algorithmic}
\end{algorithm}
```

**Costo**: tre prodotti matrice-vettore da $O(n^2)$ ciascuno. Il prodotto $A(Br)$ va calcolato **da destra** (prima $Br$, poi $A$ per il risultato) per non calcolare mai $AB$.
> [!info] Scegliere $n$ bit a caso = scegliere un vettore uniforme di $\{0,1\}^n$
> Scegliere ogni componente come un lancio di moneta indipendente equivale a scegliere un vettore uniformemente tra tutti i $2^n$ vettori: ogni vettore specifico (ad es. quello tutto 0) esce con probabilità $1/2^n$ in entrambi i modi.

L'errore è ancora a un lato: se $AB=C$ risponde sempre correttamente; se $AB\neq C$ può sbagliare.
### Analisi dell'errore
Sia $D=AB-C\neq 0$. L'algoritmo sbaglia se $Dr=0$ pur essendo $D\neq 0$. Si mostra che
$$\Pr[Dr=0]\le\frac{1}{2}$$
Si usa il **principio delle decisioni differite** (deferred decisions), qui presentato in modo informale: le componenti $r_1,\dots,r_n$ si possono scegliere in qualunque ordine, ad esempio da $r_n$ fino a $r_1$. Si **fissano** per prima cosa $r_2,\dots,r_n$ e si studia l'unica componente ancora casuale, $r_1$.
1. Poiché $D\neq 0$ esiste una entry non nulla; senza perdita di generalità sia $d_{11}\neq 0$.
2. Se $Dr=0$, in particolare è nulla la **prima componente** del vettore $Dr$, cioè $\sum_{j=1}^{n}d_{1j}r_j=0$. L'evento "$Dr=0$" è contenuto in questo evento, quindi la sua probabilità è maggiorata da quella di questo.
3. Isolando il primo termine: $r_1=-\dfrac{1}{d_{11}}\sum_{j=2}^{n}d_{1j}r_j$. Con $r_2,\dots,r_n$ fissati, il membro destro è un **valore determinato** $k$.
4. $r_1$ è un bit uniforme in $\{0,1\}$, quindi $\Pr[r_1=k\mid r_2,\dots,r_n]\le 1/2$ (vale al più $1/2$: è $0$ se $k\notin\{0,1\}$).
5. Per la **probabilità totale**, sommando su tutte le scelte di $r_2,\dots,r_n$, si ottiene $\Pr[Dr=0]\le 1/2$.

Ripetendo $k$ volte con vettori indipendenti la probabilità di errore scende a $(1/2)^k=2^{-k}$.
## Taglio minimo di un grafo (algoritmo di Karger)
> [!quote] Multigrafo, taglio, taglio minimo
> Un **multigrafo** non diretto $G=(V,E)$ ammette **archi paralleli** (più archi tra la stessa coppia di vertici, distinti tra loro) e **self loop** (archi da un vertice a sé stesso); gli archi non hanno direzione. Un **taglio** è una partizione di $V$ in due insiemi non vuoti $S$ e $V\setminus S$; la sua **dimensione** è il numero di archi con un estremo per parte (la cardinalità dell'insieme di archi che attraversano il taglio). Il **taglio minimo** è quello di dimensione minima.

> [!quote] Contrazione di un arco
> Contrarre $e=\{u,v\}$ significa creare un nuovo **super nodo** $w$ al posto di $u$ e $v$, che eredita tutti gli archi incidenti a $u$ e a $v$. Gli archi paralleli si mantengono (il multigrafo li ammette), mentre i **self loop** (archi che collegano il nuovo vertice a sé stesso) si eliminano: eliminarli non cambia nessun taglio, perché un self loop non attraversa mai un taglio. Il numero di vertici scende di uno e il numero di archi scende di almeno uno.

L'algoritmo è dovuto a Karger (ricercatore del MIT, specializzato in algoritmi randomizzati). Il problema potrebbe anche essere risolto con tecniche di flusso massimo fissando una sorgente e una destinazione, ma qui si vede un approccio randomizzato molto più semplice.

Contrazioni ripetute riducono il grafo a **due soli vertici**, e gli archi rimasti tra i due sono un taglio.
```pseudo
\begin{algorithm}
\caption{TaglioMinimoRandomizzato($G$)}
\begin{algorithmic}
\While{$G$ ha più di 2 vertici}
  \State scegli un arco $e \in E$ uniformemente a caso
  \State contrai $e$ in $G$ ed elimina i self loop
\EndWhile
\State \Return gli archi tra i due vertici rimasti
\end{algorithmic}
\end{algorithm}
```

L'algoritmo è un Monte Carlo (esegue sempre $n-2$ contrazioni) e può restituire un taglio non minimo.
### Perché funziona
- **Ogni taglio del grafo contratto è un taglio del grafo originale**, con la stessa dimensione: la contrazione conserva i tagli (se $S$ non separa gli estremi dell'arco contratto).
- Sia $C^*$ un taglio minimo. Se l'arco contratto **non** appartiene a $C^*$, allora $C^*$ resta un taglio (ancora minimo) del grafo contratto $G'$.
- L'algoritmo restituisce un taglio minimo **se e solo se non contrae mai un arco di $C^*$**: contrarre un arco di $C^*$ lo fa sparire e il taglio finale avrebbe dimensione maggiore.
- La probabilità di pescare un arco del taglio è piccola all'inizio e **cresce** man mano che gli archi diminuiscono.
### Probabilità di successo
> [!quote] Teorema
> L'algoritmo restituisce un taglio minimo con probabilità almeno
> $$\frac{2}{n(n-1)}=\Omega\!\left(\frac{1}{n^2}\right)$$
> dove $n=|V|$.

*Dimostrazione.* Sia $k$ la dimensione del taglio minimo.
1. Ogni vertice ha grado almeno $k$: se un vertice avesse grado minore, i suoi archi formerebbero un taglio (vertice contro resto) più piccolo di $k$. Questo vale anche dopo ogni contrazione, perché i tagli del grafo contratto sono tagli del grafo originale.
2. Dunque il numero di archi è $m=\tfrac12\sum_v\deg(v)\ge \dfrac{nk}{2}$.
3. Sia $E_i$ l'evento "all'iterazione $i$ l'arco scelto non è nel taglio $C^*$" ed $F_{i}=E_1\cap\dots\cap E_i$. Alla fine dell'iterazione $i-1$ ci sono $n-i+1$ vertici, e se non si è mai pescato un arco di $C^*$ questo ha ancora $k$ archi, su almeno $(n-i+1)k/2$ totali:
$$\Pr[E_i\mid F_{i-1}]=1-\frac{k}{m_i}\ge 1-\frac{2}{n-i+1}=\frac{n-i-1}{n-i+1}$$
4. Si vuole la probabilità di non pescare mai un arco di $C^*$ nelle $n-2$ iterazioni. Per la **regola della catena**:
$$\Pr[F_{n-2}]=\prod_{i=1}^{n-2}\Pr[E_i\mid F_{i-1}]\ge\prod_{i=1}^{n-2}\frac{n-i-1}{n-i+1}=\frac{n-2}{n}\cdot\frac{n-3}{n-1}\cdot\frac{n-4}{n-2}\cdots\frac{2}{4}\cdot\frac{1}{3}$$
È un **prodotto telescopico**: ogni numeratore si cancella con il denominatore due fattori dopo, e restano solo i due ultimi numeratori (2 e 1) e i due primi denominatori ($n$ e $n-1$):
$$\Pr[F_{n-2}]\ge\frac{2\cdot 1}{n(n-1)}=\frac{2}{n(n-1)}$$
### Amplificare la probabilità di successo
La probabilità di successo è piccola (circa $1/n^2$), ma si ripete l'algoritmo $N$ volte in modo indipendente e si tiene **il taglio più piccolo** tra i trovati. L'algoritmo fallisce solo se fallisce ogni volta:
$$\Pr[\text{fallimento}]\le\left(1-\frac{2}{n(n-1)}\right)^{N}\le e^{-2N/(n(n-1))}$$
Con $N=\Theta(n^2\log n)$ ripetizioni la probabilità di fallimento scende a $O(1/n)$ (con $n$ numero di vertici).
