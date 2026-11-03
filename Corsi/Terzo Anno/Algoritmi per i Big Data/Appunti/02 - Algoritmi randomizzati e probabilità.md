---
tags:
  - algoritmi-big-data
  - algoritmi-randomizzati
  - probabilita
  - variabili-aleatorie
  - analisi-del-caso-medio
  - concentrazione
slide:
  - "MITZ_UPFAL_Chapter-1.pdf"
  - "MITZ_UPFAL_Chapter-2.pdf"
  - "MITZ_UPFAL_Chapter-3.pdf"
  - "MITZ_UPFAL_Chapter-4.pdf"
---
# Algoritmi randomizzati e probabilità
## Algoritmi randomizzati
Lezione 2 (08/10/2026), prima lezione sulla parte di probabilità e algoritmi randomizzati annunciata nella [[01 - Introduzione al corso e al data mining]]. Si introducono le due famiglie di algoritmi randomizzati (Monte Carlo e Las Vegas) e si lavora su tre problemi: l'identità tra polinomi, la verifica del prodotto tra matrici e il taglio minimo di un grafo. Su tutti vale lo stesso schema: un algoritmo semplice che può sbagliare, una **probabilità di errore** da maggiorare, e la **ripetizione indipendente** per renderla piccola quanto si vuole. Slide: MITZ_UPFAL_Chapter-1, pp. 9-44 e 57-66 (le pp. 45-56, legge di Bayes, non sono state viste a lezione).
### Monte Carlo e Las Vegas
Si lavora in un modello RAM esteso: memoria, scrittura e lettura costano tempo costante e in più si può **generare un valore casuale in tempo costante**. Generare valori davvero casuali non è banale, ma si assume di poterlo fare.
> [!quote] Algoritmo Monte Carlo
> Algoritmo randomizzato con **tempo di esecuzione deterministico** ma con una certa **probabilità di errore** nella risposta. Per un problema decisionale (risposta vero/falso) può restituire la risposta sbagliata con probabilità limitata.

> [!quote] Algoritmo Las Vegas
> Algoritmo randomizzato che restituisce **sempre la risposta corretta**, ma il cui **tempo di esecuzione è una variabile aleatoria**.

> [!example] Quicksort con pivot casuale
> Il quicksort sceglie un pivot, partiziona l'array in elementi minori e maggiori e ricorre sulle due parti. Nel caso peggiore (pivot sempre minimo o massimo) la ricorsione perde un solo elemento per volta e il costo è $O(n^2)$. Scegliendo il pivot **a caso**, e assumendo che l'avversario non conosca le nostre scelte random, il costo medio è $O(n\log n)$. È quindi un algoritmo Las Vegas: sempre corretto, tempo aleatorio.

Il caso peggiore è spesso troppo pessimistico per gli algoritmi randomizzati, per questo si analizza il caso medio rispetto alle scelte random. Oggi si vedono solo algoritmi Monte Carlo, e il tema ricorrente è **rendere la probabilità di errore piccola a piacere**.
### Identity testing tra polinomi
> [!quote] Problema
> Dati due polinomi $f(x)$ e $g(x)$, stabilire se $f\equiv g$, cioè se $f(r)=g(r)$ per ogni valore $r$.

Esempio visto a lezione: due polinomi scritti in forma diversa (uno con termini $x^6, \dots$) di cui si vuole sapere se coincidono. Nelle slide (p. 9) sono $(x+1)(x-2)(x+3)(x-4)(x+5)(x-6)$ e $x^6-7x^3+25$, quindi $d=6$ e il campione è $\{1,\dots,600\}$. Le slide usano $\equiv$ per l'identità tra polinomi e $=$ per l'uguaglianza numerica.
#### Soluzione deterministica
Si portano entrambi in **forma canonica** $\sum_i c_i x^i$ e si confrontano i coefficienti di ogni potenza. Con $d$ grado massimo il costo è $O(d^2)$ nel caso peggiore.
#### Soluzione randomizzata
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

(Dalle slide, pp. 13-15) Con $r=2$ il primo polinomio dà $3\cdot0\cdot5\cdot(-2)\cdot7\cdot(-4)=0$ e il secondo $64-56+25=33$: sono diversi. Se invece i polinomi sono identici, come $(x+1)(x-1)$ e $x^2-1$, qualunque $r$ dà uguaglianza e l'algoritmo risponde bene. Una scelta sfortunata può ingannare: per $x^2+7x+1$ e $(x+2)^2$ (diversi) $r=2$ dà $19\neq16$, ma $r=1$ dà $9=9$.
#### Probabilità di errore
Se $f\not\equiv g$, il polinomio $h=f-g$ è non nullo di grado al più $d$. Per il teorema fondamentale dell'algebra ha **al più $d$ radici**. L'algoritmo sbaglia solo se $r$ è una radice di $h$, quindi per $r$ uniforme su $S$ con $|S|=100d$:
$$\Pr[\text{errore}]\le \frac{\#\text{casi favorevoli}}{\#\text{casi possibili}}\le\frac{d}{100d}=\frac{1}{100}$$
Le radici di $h$ possono essere negative o non intere: in quel caso cadono fuori da $S$ e l'errore è anche minore, quindi $d/|S|$ resta una maggiorazione valida. Con un approccio deterministico basterebbe invece valutare i polinomi in $d+1$ punti distinti.
#### Ridurre l'errore: ripetizione indipendente
Un errore dell'1% può essere troppo se l'algoritmo viene usato un miliardo di volte. Si **ripete l'algoritmo $k$ volte** con scelte indipendenti $r_1,\dots,r_k$ e si risponde "diversi" se almeno una prova lo dice. L'algoritmo sbaglia solo se sbagliano **tutte** le $k$ prove, cioè se tutti gli eventi di errore accadono insieme (intersezione). Essendo le scelte indipendenti si moltiplicano le probabilità:
$$\Pr[\text{errore su } k \text{ prove}]=\prod_{i=1}^{k}\Pr[\text{errore alla prova } i]\le\left(\frac{1}{100}\right)^{k}$$
Ogni prova in più moltiplica la fiducia nella risposta. Per avere un errore piccolo come $1/n$ basta $k=O(\log n)$ ripetizioni. (Dalle slide, pp. 18, 25-27) Nello spazio delle sequenze $(r_1,\dots,r_k)$ ci sono $(100d)^k$ esiti equiprobabili e quelli "cattivi" (tutte radici) sono al più $d^k$, da cui lo stesso $(1/100)^k$. Con $k=10$ l'errore è minore di $10^{-20}<2^{-64}$.
### Richiami di probabilità
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

> [!quote] Eventi indipendenti
> (Dalle slide, pp. 26 e 34) Due eventi $E$ e $F$ sono **indipendenti** se e solo se $\Pr[E\cap F]=\Pr[E]\Pr[F]$, cioè $\Pr[E\mid F]=\Pr[E]$. Gli eventi $E_1,\dots,E_k$ sono **mutuamente indipendenti** se per ogni sottoinsieme $I\subseteq[1,k]$ vale $\Pr\big[\bigcap_{i\in I}E_i\big]=\prod_{i\in I}\Pr[E_i]$.

Servono anche la **probabilità condizionata** $\Pr[E\mid F]=\Pr[E\cap F]/\Pr[F]$, la **probabilità totale** (si somma sui casi di una partizione dello spazio) e la **regola della catena**
$$\Pr[E_1\cap\dots\cap E_n]=\Pr[E_1]\cdot\Pr[E_2\mid E_1]\cdots\Pr[E_n\mid E_1\cap\dots\cap E_{n-1}]$$
> [!example] Indipendenza e condizionamento (dalle slide, pp. 29-37)
> - Due dadi: $\Pr[\text{somma}=8\mid\text{somma pari}]=\frac{5/36}{1/2}=\frac5{18}$.
> - L'indipendenza è una proprietà matematica, non fisica: nel lancio di un dado "esito pari" ($\frac36$) ed "esito $\le4$" ($\frac46$) sono indipendenti, perché $\Pr[\text{pari e}\le4]=\frac26=\frac36\cdot\frac46$.
> - Due figli: se il primo è femmina, la probabilità che lo sia anche il secondo è $\frac12$; se si sa solo che **almeno uno** è femmina, la probabilità che lo siano entrambi è $\frac{1/4}{3/4}=\frac13$.
#### Probabilità totale e legge di Bayes
(Dalle slide, pp. 44-56; la legge di Bayes non è stata vista a lezione.) Se $E_1,\dots,E_n$ sono eventi disgiunti la cui unione è $\Omega$, la **probabilità totale** è $\Pr[B]=\sum_i\Pr[B\mid E_i]\Pr[E_i]$ e la **legge di Bayes** inverte il condizionamento:
$$\Pr[E_j\mid B]=\frac{\Pr[B\mid E_j]\Pr[E_j]}{\sum_{i=1}^{n}\Pr[B\mid E_i]\Pr[E_i]}$$
> [!example] Fiducia crescente nel test del prodotto tra matrici
> Sia $E$ l'evento "l'identità $AB=C$ è vera" e $B$ "il test dice che è vera". Con a priori $\Pr[E]=\frac12$, $\Pr[B\mid E]=1$ e $\Pr[B\mid\bar E]\le\frac12$ (errore a un lato), dopo un test positivo $\Pr[E\mid B]\ge\frac{1/2}{1/2+1/4}=\frac23$, dopo il secondo $\ge\frac45$ e in generale dopo $i$ test positivi $\ge1-\frac1{2^i+1}$. Dopo 100 test la confidenza è almeno $1-\frac1{2^{100}+1}$.

> [!example] Altri esempi di Bayes
> - Tre monete, due eque e una che dà testa con probabilità $\frac23$: dopo i lanci testa, testa, croce la probabilità che la prima sia quella truccata passa da $\frac13$ a $\frac25$.
> - Un virus colpisce 1 turista su 1000 e il test ha il 5% di falsi positivi e nessun falso negativo: un test positivo porta solo a $\frac{20}{1019}\approx2\%$ di probabilità di avere il virus (su 1000 persone, 1 è malata e circa 50 sono falsi positivi).
### Verifica del prodotto tra matrici (Freivalds)
> [!quote] Problema
> Date tre matrici $A,B,C\in\mathbb{R}^{n\times n}$, stabilire se $A\cdot B=C$.

- Metodo classico: calcolare $A\cdot B$ in $O(n^3)$ e confrontare con $C$ ($O(n^2)$).
- Il miglior algoritmo noto per la moltiplicazione ha costo $O(n^{\omega})$ con $\omega\approx 2.37$ (il miglior esponente noto, che scende ogni tanto con nuove ricerche), ma gli algoritmi sono molto particolari e poco pratici.
- Con la randomizzazione si verifica l'uguaglianza in $O(n^2)$.

> [!warning] Precisazioni rispetto alle slide
> - Negli appunti era scritto $\omega\ge2.37$: $2{,}37$ circa è il **miglior esponente noto** (limite superiore) per la moltiplicazione, non un limite inferiore. Le slide (p. 38) riportano $\Theta(n^3)$ per il metodo classico e $\Theta(n^{2.37})$ per i migliori.
> - Le slide parlano di matrici $n\times n$ "in a Boolean field", gli appunti di matrici reali. L'analisi sotto vale in entrambi i casi: usa solo che $d_{11}\neq0$ e che $r_1$ è un bit uniforme.

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
#### Analisi dell'errore
Sia $D=AB-C\neq 0$. L'algoritmo sbaglia se $Dr=0$ pur essendo $D\neq 0$. Si mostra che
$$\Pr[Dr=0]\le\frac{1}{2}$$
Si usa il **principio delle decisioni differite** (deferred decisions), qui presentato in modo informale: le componenti $r_1,\dots,r_n$ si possono scegliere in qualunque ordine, ad esempio da $r_n$ fino a $r_1$. Si **fissano** per prima cosa $r_2,\dots,r_n$ e si studia l'unica componente ancora casuale, $r_1$.
1. Poiché $D\neq 0$ esiste una entry non nulla; senza perdita di generalità sia $d_{11}\neq 0$.
2. Se $Dr=0$, in particolare è nulla la **prima componente** del vettore $Dr$, cioè $\sum_{j=1}^{n}d_{1j}r_j=0$. L'evento "$Dr=0$" è contenuto in questo evento, quindi la sua probabilità è maggiorata da quella di questo.
3. Isolando il primo termine: $r_1=-\dfrac{1}{d_{11}}\sum_{j=2}^{n}d_{1j}r_j$. Con $r_2,\dots,r_n$ fissati, il membro destro è un **valore determinato** $k$.
4. $r_1$ è un bit uniforme in $\{0,1\}$, quindi $\Pr[r_1=k\mid r_2,\dots,r_n]\le 1/2$ (vale al più $1/2$: è $0$ se $k\notin\{0,1\}$).
5. Per la **probabilità totale**, sommando su tutte le scelte di $r_2,\dots,r_n$, si ottiene $\Pr[Dr=0]\le 1/2$.

In formula (dalle slide, p. 43), sommando su $x=(x_2,\dots,x_n)\in\{0,1\}^{n-1}$: $\Pr[ABr=Cr]\le\sum_x\Pr\big[r_1=-\tfrac{1}{d_{11}}\sum_{j\ge2}d_{1j}x_j\big]\Pr[(r_2,\dots,r_n)=x]\le\frac12\sum_x\Pr[(r_2,\dots,r_n)=x]=\frac12$.

Ripetendo $k$ volte con vettori indipendenti la probabilità di errore scende a $(1/2)^k=2^{-k}$.
### Taglio minimo di un grafo (algoritmo di Karger)
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
#### Perché funziona
- **Ogni taglio del grafo contratto è un taglio del grafo originale**, con la stessa dimensione: la contrazione conserva i tagli (se $S$ non separa gli estremi dell'arco contratto).
- Sia $C^*$ un taglio minimo. Se l'arco contratto **non** appartiene a $C^*$, allora $C^*$ resta un taglio (ancora minimo) del grafo contratto $G'$.
- L'algoritmo restituisce un taglio minimo **se e solo se non contrae mai un arco di $C^*$**: contrarre un arco di $C^*$ lo fa sparire e il taglio finale avrebbe dimensione maggiore.
- La probabilità di pescare un arco del taglio è piccola all'inizio e **cresce** man mano che gli archi diminuiscono.
#### Probabilità di successo
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

> [!warning] Refuso nelle slide
> Le slide (Chapter-1, p. 58) enunciano il teorema con probabilità $\ge\frac1{n(n-1)}$, ma il calcolo (p. 63) e l'amplificazione (p. 65, base $1-\frac2{n(n-1)}$) danno $\frac2{n(n-1)}$. L'enunciato è un refuso (come maggiorazione più debole resta vero): il valore corretto è quello degli appunti.
#### Amplificare la probabilità di successo
La probabilità di successo è piccola (circa $1/n^2$), ma si ripete l'algoritmo $N$ volte in modo indipendente e si tiene **il taglio più piccolo** tra i trovati. L'algoritmo fallisce solo se fallisce ogni volta:
$$\Pr[\text{fallimento}]\le\left(1-\frac{2}{n(n-1)}\right)^{N}\le e^{-2N/(n(n-1))}$$
Con $N=\Theta(n^2\log n)$ ripetizioni la probabilità di fallimento scende a $O(1/n)$ (con $n$ numero di vertici). Le slide (p. 65) usano $N=n(n-1)\ln n$ e ottengono un errore al più $1/n^2$, grazie a $1-x\le e^{-x}$ (sviluppo di Taylor, p. 66): vedi [[#Corretto con alta probabilità]].
## Variabili aleatorie e valore atteso
Lezione 3 (13/10/2026): si riprende il [[02 - Algoritmi randomizzati e probabilità#Taglio minimo di un grafo (algoritmo di Karger)|taglio minimo di Karger]] per chiarire quale spazio di probabilità genera un algoritmo randomizzato e come se ne controlla l'evoluzione con la probabilità condizionata. Poi si introducono gli strumenti del capitolo 2 del Mitzenmacher-Upfal: variabili aleatorie, indipendenza, valore atteso e la sua **linearità**, variabili Bernoulliane e binomiali. Si chiude con l'analisi del **randomized quicksort**, in cui la linearità riduce un'analisi apparentemente esponenziale a pochi passaggi. Slide: MITZ_UPFAL_Chapter-2, pp. 1-21 e MITZ_UPFAL_Chapter-1, pp. 57-63 (Karger); le pp. 12 e 26-36 (guardaroba, valore atteso condizionato) non sono state viste a lezione.
### Perché la randomizzazione conviene
Nella [[02 - Algoritmi randomizzati e probabilità#Verifica del prodotto tra matrici (Freivalds)|verifica del prodotto tra matrici]] il metodo deterministico calcola $AB$ e lo confronta con $C$; anche i metodi più sofisticati per la moltiplicazione restano sopra $n^2$. L'algoritmo randomizzato genera un vettore casuale ($O(n)$) e fa tre prodotti matrice-vettore ($O(n^2)$ ciascuno), quindi costa $O(n^2)$: è un **miglioramento polinomiale**.

Non è gratis: si paga con una **probabilità di errore**, che però è controllabile, perché con ripetizioni indipendenti diventa piccola a piacere.

> [!info] Dimensione dell'input
> Se l'input è una matrice $n \times n$, la sua dimensione è $n^2$, non $n$. In questa prima parte del corso la differenza non è determinante: si può fare l'analisi in funzione di $n$, purché il confronto con il metodo deterministico sia coerente.
### Lo spazio di probabilità di un algoritmo randomizzato
Per verificare di aver capito davvero un algoritmo randomizzato, oltre all'idea, ci si devono porre due tipi di domande, che sono anche quelle tipiche dell'orale:
1. **da probabilista**: qual è lo spazio di probabilità generato dall'algoritmo a ogni passo? Con quale distribuzione? Quanti bit casuali servono?
2. **da informatico**: come si implementa il passo casuale? Quale struttura dati si sceglie, come si modifica, cosa si sceglie esattamente? Il linguaggio è libero (Python, C), ma la descrizione deve essere precisa.

> [!question] Domanda tipica d'esame
> Si porta il min cut di Karger come argomento a piacere. Qual è lo spazio di probabilità generato al primo passo, e come cambia ai passi successivi? Come si implementa la scelta dell'arco da contrarre?
>
> Traccia: al tempo 0 gli esiti possibili sono gli archi $E = \{e_1, \dots, e_m\}$ e la scelta è **uniforme**: $\Pr[E_1 = e_i] = 1/|E|$. Al passo $t$ il grafo $G_t$ ha un vertice in meno e un insieme di archi $E_t \subseteq E$ (spariscono l'arco contratto e i self loop creati), che **non si conosce** finché non si sono eseguiti i primi $t-1$ passi. Lo spazio al passo $t$ è $E_t$ con distribuzione uniforme: in pratica si rinumerano gli archi rimasti e si chiede alla libreria un indice uniforme.
#### Variabili aleatorie e valori deterministici
Si distinguono due tipi di oggetti, anche quando hanno lo stesso simbolo:
- $e_1, \dots, e_m$ sono **elementi di un insieme fissato**: deterministici, non cambiano nel tempo ($e_1$ è sempre l'arco $\{1, 2\}$);
- $E_t$, l'arco scelto al passo $t$, è una **variabile aleatoria**: l'esito (*outcome*) di un esperimento. Finché l'esperimento non è eseguito se ne conoscono solo i **valori possibili** e la **distribuzione**.

Lo spazio di probabilità di un algoritmo randomizzato quindi non è fisso: per ogni passo $t \geq 1$ e ogni $e \in E_t$,

$$\Pr[\,E_t = e\,] = \frac{1}{|E_t|}$$

dove $E_t$ è a sua volta una variabile aleatoria che dipende dalle scelte precedenti.
### Karger rivisto
#### La contrazione non diminuisce il taglio minimo
Il primo ingrediente dell'analisi è di natura **topologica**.

> [!quote] Lemma
> Ogni taglio del grafo ottenuto contraendo un arco è anche un taglio del grafo di partenza, con la stessa dimensione. Quindi la contrazione **non diminuisce** la dimensione del taglio minimo.

> [!example] Due clique unite da un arco
> Si prendono due grafi completi con $n/2$ vertici ciascuno, collegati da un solo arco. Il taglio minimo ha dimensione 1 (quell'arco). Contraendo un arco interno a una clique il taglio minimo resta 1; contraendo l'arco ponte le due clique si fondono e il taglio minimo sale molto.

Un taglio è un insieme di archi la cui rimozione **disconnette** il grafo, e il taglio minimo misura la **resilienza** (*fault tolerance*) della rete: un grafo con taglio minimo $k$ resta connesso finché non si rompono almeno $k$ archi. Contrarre un arco toglie una possibilità di staccare il grafo, quindi non peggiora mai la situazione.

Una conseguenza importante: quando si contrae un arco, gli archi paralleli tra gli stessi due vertici diventano self loop e spariscono. Questi archi o fanno **tutti** parte del taglio $C$ o **nessuno**: togliendone solo alcuni il grafo non si stacca. Se l'arco contratto non è in $C$, nessuno degli archi eliminati con lui è in $C$.
#### Lo schema dell'analisi
L'analisi fissa un taglio minimo $C$ di dimensione $k$ nel grafo iniziale. $C$ **non** è una variabile dell'algoritmo: è l'analista che, con potere di calcolo illimitato, guarda dall'alto e segue cosa succede a quel taglio. A ogni passo ci sono due casi, descritti da una variabile booleana: l'arco scelto è in $C$ oppure no.

> [!info] Un'analisi nel caso peggiore
> I tagli minimi potrebbero essere più di uno: l'algoritmo potrebbe toccare un arco di $C$ e trovare comunque un altro taglio minimo. L'analisi non considera questa possibilità, quindi si mette nell'ipotesi più sfavorevole all'algoritmo.

Siano $E_i$ l'evento "al passo $i$ non si sceglie un arco di $C$" e $F_i = E_1 \cap \dots \cap E_i$ ("fino al passo $i$ è sempre andata bene").
- **Primo passo**. Ogni vertice ha grado almeno $k$, altrimenti staccarlo costerebbe meno di $k$ archi; quindi $|E| \geq nk/2$ e

$$\Pr[E_1] = 1 - \frac{k}{|E|} \geq 1 - \frac{k}{nk/2} = 1 - \frac{2}{n}$$

- **Secondo passo**. Lo spazio di probabilità dipende da cosa è successo prima, quindi si **condiziona**: ci si mette nell'ipotesi $F_1$ (se si è toccato $C$ l'algoritmo è già fallito, e quel caso non interessa). Sotto $F_1$ il numeratore non cambia, perché $C$ è intatto con i suoi $k$ archi; cambia il denominatore, perché la contrazione ha tolto un numero imprecisato di archi. Per il lemma il taglio minimo è ancora almeno $k$, quindi ogni vertice ha ancora grado almeno $k$, e i vertici sono $n-1$:

$$\Pr[E_2 \mid F_1] \geq 1 - \frac{k}{(n-1)k/2} = 1 - \frac{2}{n-1}$$

- **Passo generico**. Con lo stesso ragionamento su $n - i + 1$ vertici, $\Pr[E_i \mid F_{i-1}] \geq 1 - \frac{2}{n-i+1}$.

Senza il lemma topologico non si potrebbe dire nulla sui passi successivi al primo. Per la **regola della catena**, $\Pr[F_{n-2}] = \Pr[E_{n-2} \mid F_{n-3}] \cdot \Pr[F_{n-3}]$, e srotolando fino al primo passo si ottiene il prodotto telescopico già visto nella [[02 - Algoritmi randomizzati e probabilità#Probabilità di successo|probabilità di successo]]:

$$\Pr[F_{n-2}] \geq \frac{2}{n(n-1)}$$
#### Corretto con alta probabilità
La probabilità di successo di una singola esecuzione è dell'ordine di $1/n^2$: tende a zero, ma **in modo polinomiale**. L'algoritmo restituisce sempre un taglio, che non può essere più piccolo di quello minimo; quando fallisce restituisce un taglio più grande, anche di molto. Si esegue quindi $N$ volte in modo indipendente e si tiene il **taglio più piccolo** trovato; si sbaglia solo se tutte le esecuzioni falliscono.

Si usa una disuguaglianza che tornerà spesso, legata all'approssimazione di Taylor:

$$1 - x \leq e^{-x} \qquad\text{quindi}\qquad (1 - x)^N \leq e^{-xN}$$

Con $N = n(n-1) \ln n$ ripetizioni:

$$\Pr[\text{errore}] \leq \left(1 - \frac{2}{n(n-1)}\right)^{n(n-1)\ln n} \leq e^{-2 \ln n} = \frac{1}{n^2}$$

> [!quote] Alta probabilità
> Un algoritmo è **corretto con alta probabilità** (*with high probability*) se la sua probabilità di errore va come l'inverso di un polinomio nella dimensione dell'input, ad esempio $O(1/n)$ o $O(1/n^2)$.
### Variabili aleatorie
> [!quote] Variabile aleatoria
> Una **variabile aleatoria** $X$ su uno spazio di probabilità $(\Omega, \mathcal{F}, \Pr)$ è una funzione $X : \Omega \to \mathbb{R}$ che assegna un valore a ogni evento elementare. È **discreta** se assume un numero finito o numerabile di valori (nel corso, di solito, valori naturali).

Spazio di probabilità e variabile aleatoria vanno tenuti separati: lo spazio descrive gli esiti dell'esperimento, la variabile è una funzione definita sopra di essi. Anche nell'analisi di Karger si è usata una variabile aleatoria: la variabile booleana che vale 1 se l'arco scelto non è nel taglio. Nell'analisi di un algoritmo randomizzato il processo completo è molto complicato, ma interessano poche variabili, soprattutto due:
- la **correttezza**, variabile booleana (l'algoritmo ha risposto bene o no?);
- il **tempo di esecuzione**: eseguendo lo stesso algoritmo cento volte sullo stesso input, una volta fa 10 confronti, un'altra 100, un'altra 50.

> [!warning] Il tempo di un algoritmo randomizzato
> Dire che un ordinamento randomizzato "ci mette tempo $n \log n$" non ha senso: il tempo è una variabile aleatoria. Bisogna dire **con quale probabilità** lo fa, oppure che il **tempo atteso** è $O(n \log n)$. Il valore atteso è un numero deterministico; la variabile no.

> [!example] Due esempi
> - **Un dado**: lo spazio sono le sei facce, la variabile vale il numero letto sulla faccia uscita.
> - **Due monete e un premio**: si lanciano due monete in modo indipendente; se escono due teste si vincono 3 dollari, altrimenti se ne perde 1. Lo spazio ha 4 esiti (TT, TC, CT, CC), la variabile vale $3$ su TT e $-1$ sugli altri tre.

> [!quote] Indipendenza
> Due variabili aleatorie $X$ e $Y$ sono **indipendenti** se per ogni coppia di valori $x, y$
> $$\Pr[(X = x) \cap (Y = y)] = \Pr[X = x] \cdot \Pr[Y = y]$$
> e analogamente per $k$ variabili: la probabilità della congiunzione è il prodotto delle probabilità.

L'indipendenza è una definizione matematica, non un'idea fisica del tipo "uno non dà fastidio all'altro". La notazione $X = x$ ribadisce la distinzione: $x$ è un valore fissato tra quelli possibili, $X$ è l'esito.
### Valore atteso
> [!quote] Valore atteso
> Il **valore atteso** di una variabile aleatoria discreta $X$ è
> $$\mathbb{E}[X] = \sum_{i} i \cdot \Pr[X = i]$$
> dove la somma corre su tutti i valori che $X$ può assumere. Con infiniti valori la somma può anche divergere: va verificato caso per caso.

> [!example] Uno e due dadi
> - Per un dado equo $\mathbb{E}[X] = \sum_{i=1}^{6} i \cdot \frac16 = \frac{21}{6} = 3{,}5$. La variabile assume solo valori naturali, ma il valore atteso è un razionale, e non è un valore che la variabile può assumere.
> - Per la somma di due dadi i valori vanno da 2 a 12, non con distribuzione uniforme: 2 si ottiene solo con $(1,1)$ e 12 solo con $(6,6)$, probabilità $1/36$ ciascuno, mentre 4 si ottiene con $(1,3), (2,2), (3,1)$. Il calcolo diretto dà $\mathbb{E} = 7$.
> - (Dalle slide, p. 5) Se $X$ vale $2^i$ con probabilità $1/2^i$ per $i=1,2,\dots$, allora $\mathbb{E}[X]=\sum_i\frac1{2^i}2^i=\sum_i1=\infty$: il valore atteso è finito solo se $\sum_i|i|\Pr[X=i]$ converge.
> - (Dalle slide, p. 7) Si sceglie un numero in $[1,6]$ e si lanciano 3 dadi: si vince 1 dollaro per ogni dado che coincide, se ne perde 1 se nessuno coincide. $\mathbb{E}=-\left(\frac56\right)^3+3\cdot\frac16\left(\frac56\right)^2+2\cdot3\left(\frac16\right)^2\frac56+3\left(\frac16\right)^3=-\frac{17}{216}$: il gioco è sfavorevole.

La **mediana** è diversa dal valore atteso: è un valore $m$ che la variabile assume davvero e che divide a metà la massa di probabilità, cioè $\Pr[X \leq m] \geq 1/2$ e $\Pr[X \geq m] \geq 1/2$.

> [!warning] Definizione di mediana nelle slide
> Le slide (Chapter-2, p. 6) definiscono la mediana come un valore $m$ con $\Pr[X<m]\le\frac12$ e $\Pr[X>m]<\frac12$. È la stessa idea, con la seconda disuguaglianza stretta. Qui si usa la formulazione standard sopra.
#### Linearità del valore atteso
> [!quote] Teorema (linearità del valore atteso)
> Per qualsiasi variabili aleatorie $X$ e $Y$, **indipendenti o no**, e per ogni costante $c$:
> $$\mathbb{E}[X + Y] = \mathbb{E}[X] + \mathbb{E}[Y] \qquad \mathbb{E}[c\,X] = c\,\mathbb{E}[X]$$

*Dimostrazione.* Per definizione e spezzando $i + j$:

$$\mathbb{E}[X + Y] = \sum_i \sum_j (i + j) \Pr[(X = i) \cap (Y = j)] = \sum_i i \sum_j \Pr[(X = i) \cap (Y = j)] + \sum_j j \sum_i \Pr[(X = i) \cap (Y = j)]$$

Gli eventi $\{Y = j\}$, al variare di $j$, formano una **partizione** dello spazio (disgiunti a due a due, con unione $\Omega$), quindi per la probabilità totale $\sum_j \Pr[(X = i) \cap (Y = j)] = \Pr[X = i]$. Il primo addendo è $\mathbb{E}[X]$, e allo stesso modo il secondo è $\mathbb{E}[Y]$. La seconda proprietà è immediata.

La forza del teorema è che non richiede alcuna ipotesi sulla dipendenza: si calcolano i valori attesi separatamente e si sommano. Non vale per altre grandezze: la **varianza** di una somma, ad esempio, non è la somma delle varianze quando le variabili sono correlate.

> [!example] Somma di due dadi e numero di teste
> - Due dadi: $\mathbb{E}[X_1 + X_2] = 3{,}5 + 3{,}5 = 7$, senza il calcolo sui 36 esiti.
> - $n$ lanci di una moneta equa: il numero atteso di teste è $n \cdot \frac12$, perché ogni lancio contribuisce con $\frac12$.
> - (Dalle slide, p. 11) La linearità vale anche per variabili dipendenti: un dado più il doppio di un secondo dado ha valore atteso $3{,}5+2\cdot3{,}5=10{,}5$. Da qui, confrontando con la somma diretta, segue l'identità $\sum_{i=0}^{N}i\binom Ni2^{-N}=\frac N2$.
> - (Dalle slide, p. 12; non visto a lezione) Guardaroba: $N$ persone lasciano il cappotto e ognuna ne riceve uno a caso. Se $X_i$ è l'indicatrice "la persona $i$ riceve il suo", $\mathbb{E}[X_i]=\frac1N$ e il numero atteso di persone con il proprio cappotto è $\sum_i\mathbb{E}[X_i]=1$, per ogni $N$.
#### Bernoulliana e binomiale
> [!quote] Variabile Bernoulliana
> Una variabile **Bernoulliana** (o **indicatrice**) di parametro $p$ vale 1 con probabilità $p$ e 0 con probabilità $1 - p$. Il suo valore atteso è
> $$\mathbb{E}[X] = 1 \cdot p + 0 \cdot (1 - p) = p = \Pr[X = 1]$$

Per una variabile booleana il valore atteso coincide sempre con la probabilità che valga 1: è il trucco che si usa in quasi tutte le analisi.

> [!quote] Variabile binomiale
> Una variabile **binomiale** $X \sim B(n, p)$ conta i successi in $n$ prove Bernoulliane **indipendenti** di parametro $p$:
> $$\Pr[X = j] = \binom{n}{j} p^j (1 - p)^{n - j} \qquad j = 0, \dots, n$$

Il coefficiente $\binom{n}{j}$ sceglie le posizioni dei $j$ successi; per l'indipendenza, su quelle posizioni si ha $p^j$ e sulle altre $(1-p)^{n-j}$. Ad esempio, la probabilità di esattamente 75 teste su 100 lanci si ottiene sostituendo $n = 100$, $j = 75$, $p = 1/2$. È raro, nell'analisi di algoritmi complessi, conoscere la distribuzione esatta così; di solito ci si concentra sul valore atteso e al più sulla varianza.

Il valore atteso della binomiale si può calcolare dalla definizione, con qualche passaggio sui coefficienti binomiali, oppure in una riga con la linearità: $X = X_1 + \dots + X_n$ con $X_i$ Bernoulliane, quindi

$$\mathbb{E}[X] = \sum_{i=1}^{n} \mathbb{E}[X_i] = n\,p$$
### Randomized quicksort
Il quicksort con pivot casuale (già incontrato come esempio di [[02 - Algoritmi randomizzati e probabilità#Monte Carlo e Las Vegas|algoritmo Las Vegas]]) ordina un insieme $S$ di $n$ elementi distinti. Ha lo stesso numero ottimo di confronti di heapsort e mergesort, ma è molto più semplice.

```pseudo
\begin{algorithm}
\caption{RandQuickSort($S$)}
\begin{algorithmic}
\If{$|S| \leq 1$}
  \State \Return $S$
\EndIf
\State scegli $y \in S$ uniformemente a caso
\State $S_1 \gets \{x \in S : x < y\}$
\State $S_2 \gets \{x \in S : x > y\}$
\State \Return \Call{RandQuickSort}{$S_1$}, $y$, \Call{RandQuickSort}{$S_2$}
\end{algorithmic}
\end{algorithm}
```

Una volta scelto $y$ e partizionato l'insieme, la posizione di $y$ nel vettore ordinato è determinata. A volte $y$ è vicino al centro e le due parti sono bilanciate, a volte è un estremo e una parte è quasi vuota.

Il pivot $y$ è una **variabile aleatoria**, e non ce n'è uno solo: lo spazio di probabilità è quello delle sequenze di pivot $y_1, y_2, \dots, y_t$, ognuno scelto uniformemente nel sottoinsieme corrente. Analizzare il numero di confronti caso per caso ("se $y_1$ è il primo elemento succede questo, poi $y_2$ dipende da $y_1$…") porta a un numero esponenziale di casi: senza un'idea più furba l'analisi è impossibile, e nessuna simulazione la sostituisce.

> [!quote] Teorema
> Per **qualunque** input di $n$ elementi, il numero atteso di confronti di RandQuickSort è $O(n \log n)$.

Non è un'analisi del caso medio sugli input: vale anche per l'istanza peggiore, e il valore atteso è preso sulle scelte casuali dell'algoritmo.
#### Dimostrazione con la linearità
Siano $s_1 < s_2 < \dots < s_n$ gli elementi in ordine crescente. Due elementi qualsiasi vengono confrontati **al più una volta**: si confrontano solo quando uno dei due è il pivot, e dopo quel passo il pivot esce dalle chiamate ricorsive. Si definisce allora, per $i < j$, la variabile indicatrice

$$X_{ij} = \begin{cases} 1 & \text{se } s_i \text{ e } s_j \text{ vengono confrontati durante l'esecuzione} \\ 0 & \text{altrimenti} \end{cases}$$

Non interessa quando né perché: solo se il confronto avviene. Il numero totale di confronti è $X = \sum_{i < j} X_{ij}$ e, per linearità,

$$\mathbb{E}[X] = \sum_{i=1}^{n-1} \sum_{j > i} \mathbb{E}[X_{ij}] = \sum_{i=1}^{n-1} \sum_{j > i} \Pr[X_{ij} = 1]$$

Tutto si riduce a una domanda: con che probabilità due elementi si confrontano? Si guarda l'insieme $\{s_i, s_{i+1}, \dots, s_j\}$, che ha $j - i + 1$ elementi e resta nella stessa chiamata ricorsiva finché non si sceglie come pivot uno di loro.
- Se il pivot è **fuori** dall'intervallo (minore di $s_i$ o maggiore di $s_j$), $s_i$ e $s_j$ finiscono nello stesso sottoinsieme e non si sa ancora nulla.
- Se il pivot è uno dei $j - i - 1$ elementi **strettamente in mezzo**, $s_i$ e $s_j$ finiscono in sottoinsiemi diversi e **non saranno mai confrontati**.
- Se il pivot è **$s_i$ o $s_j$**, i due vengono confrontati.

Il primo pivot scelto nell'intervallo è uniforme sui suoi $j - i + 1$ elementi, quindi

$$\Pr[X_{ij} = 1] = \frac{2}{j - i + 1}$$

Sostituendo, con $k = j - i + 1$:

$$\mathbb{E}[X] = \sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \frac{2}{j - i + 1} \leq \sum_{i=1}^{n} \sum_{k=2}^{n} \frac{2}{k} \leq 2n\,H_n = O(n \log n)$$

dove $H_n = \sum_{k=1}^{n} 1/k \approx \ln n$ è la serie armonica.

> [!warning] Costante nel bound delle slide
> Le slide (Chapter-2, p. 21) scrivono $2nH_n=n\log n+O(n)$, ma $H_n\approx\ln n$ e quindi $2nH_n=2n\ln n+O(n)$ (circa $1{,}39\,n\log_2 n$): il coefficiente non è 1. Per la notazione $O(n\log n)$ non cambia nulla. Inoltre le slide definiscono $S_1=\{x\le y\}$ e $S_2=\{x>y\}$; qui gli elementi sono distinti e si usano $<$ e $>$.

> [!info] La lezione da portare a casa
> Una variabile enorme e intrattabile, il numero totale di confronti, si spezza in una somma di variabili indicatrici semplicissime. La linearità del valore atteso permette di analizzarle una per volta, senza preoccuparsi delle loro dipendenze.

> [!question] Domanda tipica d'esame
> Si porta il randomized quicksort. Qual è lo spazio di probabilità? Quali sono le variabili aleatorie in gioco? Perché $\Pr[X_{ij} = 1] = 2/(j - i + 1)$, e dove si usa che il pivot è scelto in modo uniforme? Perché serve la linearità del valore atteso e non l'indipendenza?
### Valore atteso condizionato
(Dalle slide, Chapter-2 pp. 26-36; non visto a lezione.) Il valore atteso di $Y$ dato $Z=z$ è $\mathbb{E}[Y\mid Z=z]=\sum_y y\Pr[Y=y\mid Z=z]$. L'espressione $\mathbb{E}[Y\mid Z]$ è una variabile aleatoria $f(Z)$ che vale $\mathbb{E}[Y\mid Z=z]$ quando $Z=z$, e vale
$$\mathbb{E}[Y]=\sum_z\Pr[Z=z]\,\mathbb{E}[Y\mid Z=z]=\mathbb{E}\big[\mathbb{E}[Y\mid Z]\big]$$
Con due dadi e $X=X_1+X_2$: $\mathbb{E}[X\mid X_1=2]=\frac{11}2$, $\mathbb{E}[X\mid X_1]=X_1+\frac72$ e $\mathbb{E}\big[\mathbb{E}[X\mid X_1]\big]=\frac72+\frac72=7$.
> [!example] Processo che genera copie di sé stesso
> Un processo $S$ genera ricorsivamente un numero di copie distribuito come $B(n,p)$, indipendente per ogni chiamata. Se $Y_i$ è il numero di processi alla generazione $i$ ($Y_0=1$), condizionando su $Y_{i-1}$ si ha $\mathbb{E}[Y_i\mid Y_{i-1}]=Y_{i-1}\,np$, quindi $\mathbb{E}[Y_i]=(np)^i$ e il numero totale atteso di copie è $\sum_{i\ge0}(np)^i$: illimitato se $np\ge1$, uguale a $\frac1{1-np}$ se $np<1$.
## Analisi del caso medio e disuguaglianze di concentrazione
Lezione 4 (15/10/2026): si distingue l'analisi di un algoritmo randomizzato su un input peggiore dall'**analisi del caso medio** di un algoritmo deterministico su un input casuale, rifacendo il quicksort nei due modi a partire dal [[02 - Algoritmi randomizzati e probabilità#Randomized quicksort|randomized quicksort]] della lezione precedente. Seguono una classificazione degli algoritmi randomizzati per problemi decisionali, la **distribuzione geometrica** con il problema del **coupon collector** e i primi strumenti per misurare quanto una variabile aleatoria si discosta dal suo valore atteso: varianza, **disuguaglianza di Markov** e **disuguaglianza di Chebyshev**. Slide: MITZ_UPFAL_Chapter-2, pp. 22-25 e 37-43 (quicksort deterministico, classificazione, geometrica, coupon collector) e MITZ_UPFAL_Chapter-3, pp. 1-12 (Markov, varianza, Chebyshev); le pp. 30-38 del Chapter-3 non sono state viste a lezione.
### Algoritmi randomizzati e analisi del caso medio
#### Il randomized quicksort, ancora
Nel randomized quicksort il numero di confronti è una variabile aleatoria definita sullo spazio delle scelte dei pivot $y$; anche **quanti** pivot si scelgono è aleatorio (in alcune esecuzioni l'albero delle chiamate è profondo $\log n$, in altre $n$). Il teorema dice che, **per qualunque input fissato**, anche il peggiore, il numero atteso di confronti è $O(n \log n)$: il caso peggiore riguarda l'input, il valore atteso riguarda le scelte dell'algoritmo. L'analisi si basava su [[02 - Algoritmi randomizzati e probabilità#Dimostrazione con la linearità|indicatrici e linearità]]: $s_i$ e $s_j$ si confrontano con probabilità $2/(j - i + 1)$, e la somma dà la serie armonica.

La probabilità entra però nell'algoritmica in due modi diversi.
- **Algoritmi randomizzati**: l'algoritmo, oltre a confronti, cicli e strutture dati, ogni tanto **lancia un bit casuale** e decide in base al risultato. L'input è nel caso peggiore, scelto da un **avversario** che conosce il codice ma **non** le scelte casuali fatte durante l'esecuzione (sa che al passo 33 si sceglierà un pivot a caso, non quale). L'avversario sceglie l'input "a bocce ferme", prima dell'esecuzione. È la stessa ipotesi su cui si regge la crittografia: l'avversario non legge i numeri casuali del sistema.
- **Analisi del caso medio** (*average case analysis*, o analisi probabilistica): l'algoritmo è **deterministico**, e si assume invece un **modello statistico dell'input**, cioè uno spazio di tutti gli input possibili con una distribuzione di probabilità. Le grandezze (tempo, spazio) sono valori attesi rispetto a quella distribuzione.

I due approcci si possono anche combinare.

> [!example] Dijkstra nel caso medio
> Normalmente Dijkstra si analizza sul grafo peggiore. Un'analisi del caso medio fissa $n$ e considera **tutti** i grafi con $n$ nodi: sono un numero esponenziale ma finito, quindi si può mettere su di essi la distribuzione uniforme e calcolare il numero atteso di confronti su un grafo scelto a caso.
#### Quicksort deterministico su input casuale
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
>
> (Dalle slide, Chapter-2 p. 24) Inoltre le esecuzioni ripetute di un algoritmo randomizzato sono indipendenti tra loro, mentre un algoritmo deterministico ripetuto sullo stesso input dà sempre lo stesso risultato.

> [!info] Perché si chiama *quick* sort
> Anche selection sort e insertion sort costano $\Theta(n^2)$ nel caso peggiore, ma per il quicksort le permutazioni "cattive" sono **poche**: l'avversario deve disporre gli elementi in modo molto particolare. Per il selection sort, invece, moltissime configurazioni costano $\Theta(n^2)$. Il modello statistico dell'input fa emergere questa differenza, ed è per questo che la sua costruzione, con le assunzioni dichiarate esplicitamente, è importante quanto l'algoritmo.
#### Tipi di algoritmi randomizzati
Per un **problema decisionale**, in cui ogni istanza ha risposta sì o no (un grafo è connesso? è 3-colorabile?), un algoritmo randomizzato può essere:
- a **errore bilaterale** (*two-sided error*): probabilità di errore maggiore di zero sia sulle istanze sì sia sulle istanze no;
- a **errore unilaterale** (*one-sided error*): sbaglia solo su uno dei due tipi di istanza. Sono di questo tipo l'[[02 - Algoritmi randomizzati e probabilità#Soluzione randomizzata|identity testing tra polinomi]] e la verifica del prodotto tra matrici: se rispondono "diversi" hanno sempre ragione;
- **Las Vegas**: quando risponde, risponde sempre correttamente, ma a volte non risponde. Per la soddisfacibilità di una formula in forma normale congiuntiva, ad esempio, può dire "sì" (ed è certo), "no" (ed è certo) oppure "?". Se la probabilità di "?" è al più $1/3$, ripetendo l'algoritmo cresce la confidenza di ottenere prima o poi la risposta.

I problemi di ottimizzazione si riducono a problemi decisionali con un parametro: invece del numero minimo di colori, ci si chiede se esiste una colorazione con al più $k$ colori.

> [!warning] Definizioni delle slide
> Le slide (Chapter-2, p. 25) chiamano **Monte Carlo** un algoritmo randomizzato che può produrre una soluzione sbagliata (a un lato se per un problema decisionale sbaglia su una sola delle due risposte, a due lati altrimenti) e **Las Vegas** uno che produce **sempre** l'output corretto, e aggiungono che in entrambi i casi il **tempo di esecuzione è una variabile aleatoria**. Due differenze rispetto agli appunti: il tempo deterministico del Monte Carlo (lezione 2) vale per gli algoritmi visti ma non fa parte della definizione generale, e la variante del Las Vegas che può rispondere "?" è quella spiegata a lezione e non compare nelle slide.

> [!info] Domanda a lezione: e il randomized quicksort?
> L'ordinamento non è un problema decisionale: non ci sono istanze sì e istanze no. È un problema di **ricerca**, e si può vedere come problema di **ottimizzazione**: data la permutazione in input, minimizzare il numero di **inversioni** nella permutazione in uscita (il minimo è sempre 0). Il randomized quicksort risponde sempre correttamente; la casualità serve solo a migliorare l'efficienza.
### Distribuzione geometrica
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

(Dalle slide, Chapter-3 p. 27) Dimostrazione alternativa: si condiziona sul primo tentativo. Se $Z$ è il numero di tentativi dopo il primo, $\mathbb{E}[X]=(1-p)\mathbb{E}[Z+1]+p\cdot1$; per l'assenza di memoria $Z$ è geometrica come $X$, quindi $\mathbb{E}[X]=(1-p)\mathbb{E}[X]+1$, cioè $\mathbb{E}[X]=1/p$. Con lo stesso metodo (non visto a lezione) $\mathbb{E}[X^2]=\frac{2-p}{p^2}$ e quindi $\mathrm{Var}[X]=\frac{1-p}{p^2}$.
#### Il coupon collector
> [!example] L'album di figurine
> Ogni pacchetto contiene una figurina scelta uniformemente a caso tra $n$, indipendentemente dalle precedenti. Quanti pacchetti servono in media per completare l'album? Lo stesso processo descrive l'allocazione online di risorse in cui ogni agente deve ricevere una risorsa almeno una volta.

Si divide il processo in **epoche**: l'epoca $i$ va dal momento in cui si ha l'$(i-1)$-esima figurina distinta a quello in cui si ottiene l'$i$-esima. Sia $X_i$ la sua durata.
- La prima figurina è sempre nuova, quindi $X_1 = 1$.
- Già $X_2$ è aleatoria: un collezionista sfortunato può trovare per cento volte la stessa figurina.
- Nell'epoca $i$ ci sono già $i - 1$ figurine, e ogni pacchetto ne porta una nuova con probabilità $p_i = 1 - \frac{i-1}{n} = \frac{n - i + 1}{n}$. Quindi $X_i$ è **geometrica** di parametro $p_i$.
- L'ultima epoca ha $p_n = 1/n$: tutte le figurine sono sempre equiprobabili, ma ne serve solo una. Per questo gli ultimi buchi dell'album sono i più lenti da riempire.

Il numero totale di pacchetti è $X = \sum_{i=1}^{n} X_i$ e, per linearità,

$$\mathbb{E}[X] = \sum_{i=1}^{n} \frac{1}{p_i} = \sum_{i=1}^{n} \frac{n}{n - i + 1} = n \sum_{k=1}^{n} \frac{1}{k} = n\,H_n = n \ln n + \Theta(n)$$

(Dalle slide, Chapter-3 pp. 33-35; non visto a lezione.) Con Markov, $\Pr[X\ge2nH_n]\le\frac12$. Si fa meglio: le $X_i$ sono indipendenti e $\mathrm{Var}[X_i]\le1/p_i^2=\left(\frac n{n-i+1}\right)^2$, quindi $\mathrm{Var}[X]\le n^2\sum_{k=1}^n\frac1{k^2}\le\frac{\pi^2n^2}6$ e per Chebyshev $\Pr[|X-nH_n|\ge nH_n]\le\frac{\pi^2}{6H_n^2}=O\!\left(\frac1{\ln^2n}\right)$. Con un'analisi diretta: un fissato coupon manca dopo $n\ln n+cn$ pacchetti con probabilità $\left(1-\frac1n\right)^{n(\ln n+c)}<\frac1{e^cn}$, e per l'union bound ne manca almeno uno con probabilità minore di $e^{-c}$; dopo $2n\ln n$ pacchetti la probabilità è al più $\frac1n$.


> [!question] Domanda tipica d'esame
> Qual è il numero atteso di estrazioni per vedere tutti gli $n$ coupon almeno una volta? Spiega la divisione in epoche, perché la durata di ogni epoca è geometrica e con quale parametro, e dove si usa la linearità del valore atteso.
### Concentrazione attorno al valore atteso
In data mining non basta dire che un algoritmo ci mette tempo atteso $n \log n$: bisogna sapere **con che probabilità ci si discosta molto** dal valore atteso. Due distribuzioni possono avere lo stesso valore atteso ed essere completamente diverse:
- una **campana stretta** attorno alla media: nelle esecuzioni reali il tempo sarà quasi sempre vicino al valore atteso, ad esempio tra $\frac12 n \log n$ e $2 n \log n$, e il valore atteso è una buona previsione;
- una distribuzione a **due gobbe**, con la massa lontana a sinistra e a destra: il valore atteso non viene quasi mai osservato, e scommettere su di esso è pessimo.

> [!example] Tre giochi con lo stesso valore atteso
> Si vince o si perde 1 euro con probabilità $\frac12$; oppure si vincono o si perdono 100 000 euro con probabilità $\frac12$; oppure un gioco molto sbilanciato con una vincita enorme e rarissima. Il valore atteso è circa lo stesso, ma con un budget di 100 euro nel primo gioco si fanno tranquillamente un centinaio di tentativi, mentre nel secondo si può fallire al primo.

Studiare quanto una variabile si discosta dalla media è l'**analisi del secondo momento** (o della varianza).
#### Disuguaglianza di Markov
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
#### Varianza
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

La prima si dimostra dalla definizione: $\mathbb{E}[XY] = \sum_i \sum_j i\,j \Pr[(X = i) \cap (Y = j)]$, e per l'indipendenza la probabilità si fattorizza in $\Pr[X = i]\Pr[Y = j]$; la somma si separa nel prodotto dei due valori attesi. La seconda segue sviluppando il quadrato (la dimostrazione non è in programma). A differenza della [[02 - Algoritmi randomizzati e probabilità#Linearità del valore atteso|linearità del valore atteso]], queste proprietà **richiedono** l'indipendenza.

Per una binomiale $B(n, \frac12)$, somma di $n$ Bernoulliane indipendenti, si ottiene quindi $\mathrm{Var}[X] = n/4$. In generale (dalle slide, Chapter-3 pp. 11-12) una binomiale $B(n,p)$ ha $\mathrm{Var}[X]=np(1-p)$.
#### Disuguaglianza di Chebyshev
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

> [!info] Verifica con le slide
> La registrazione si interrompe durante il calcolo, ma il risultato $4/n$ è confermato dalle slide (MITZ_UPFAL_Chapter-3, p. 10): $\Pr[X\ge\frac34N]\le\Pr[|X-\mathbb{E}[X]|\ge\frac{\mathbb{E}[X]}2]\le\frac{N/4}{(N^2/4)(1/4)}=\frac4N$, un bound molto migliore di quello di Markov.
#### Media di più campioni e legge dei grandi numeri
(Dalle slide, Chapter-3 pp. 36-38; non visto a lezione.) Per ogni costante $a$, $\mathrm{Var}[aX]=a^2\mathrm{Var}[X]$. Se $X_1,\dots,X_n$ sono indipendenti e identicamente distribuite e $\bar X=\frac1n\sum_iX_i$, allora $\mathrm{Var}[\bar X]=\frac1{n^2}\,n\,\mathrm{Var}[X_i]=\frac1n\mathrm{Var}[X_i]$: la media di più campioni è più concentrata. Con Chebyshev si ottiene la **legge debole dei grandi numeri**, $\Pr[|\bar X_n-\mathbb{E}[X]|>\varepsilon]\le\frac{\mathrm{Var}[X_i]}{n\varepsilon^2}\to0$ per ogni $\varepsilon>0$.

> [!question] Domanda tipica d'esame
> Enuncia e dimostra le disuguaglianze di Markov e di Chebyshev. Applicale alla probabilità di ottenere almeno $\frac34 n$ teste su $n$ lanci indipendenti e spiega perché Chebyshev dà un risultato molto migliore.
## Bound di Chernoff e bilanciamento del carico
Lezione 6 (22/10/2026), prima parte: l'ultima lezione dedicata alla probabilità. Si completano gli strumenti di **concentrazione** con i **bound di Chernoff**, che danno code esponenziali dove [[#Disuguaglianza di Chebyshev|Chebyshev]] dà code polinomiali, e li si applica al **bilanciamento del carico** con assegnazione casuale. La lezione 5 non è presente negli appunti. Nella seconda parte comincia il data mining vero e proprio ([[03 - Ricerca di oggetti simili#Trovare oggetti simili]]); da qui in poi la probabilità resta solo come strumento, da usare quando serve. Slide: MITZ_UPFAL_Chapter-3, pp. 13-24 (mediana randomizzata) e MITZ_UPFAL_Chapter-4, pp. 1-17 (Chernoff e lancio di monete); il bilanciamento del carico non è nelle slide (segue Kleinberg-Tardos) e le pp. 18-49 del Chapter-4 non sono state viste a lezione.
### Ripresa: la mediana con il campionamento
All'inizio si riprende l'algoritmo randomizzato per la **mediana** visto nella lezione precedente, che sceglie un campione $R$ di $n^{3/4}$ elementi dell'insieme $S$ da ordinare. L'idea dell'analisi:
- in $n$ esperimenti indipendenti la **deviazione standard** è dell'ordine di $\sqrt n$: è di quanto ci si può discostare dal valore medio con probabilità significativa;
- il campione ha $n^{3/4}$ elementi, **polinomialmente** più grande di $\sqrt n$ (il rapporto è $n^{1/4}$). Nel gergo del corso, una cosa è "leggermente più grande" se il rapporto è una costante, "abbastanza più grande" se è un logaritmo, "molto più grande" se è un polinomio;
- se il campione fosse distribuito perfettamente, la sua mediana coinciderebbe con quella di $S$. Non lo è, ma può sbagliare di un fattore dell'ordine di $\sqrt n$: prendendo gli estremi $d$ e $u$ a circa metà campione $\pm\sqrt n$, la vera mediana cade tra i due con alta probabilità. Il contrario richiederebbe uno scostamento polinomialmente più grande della deviazione standard, che è altamente improbabile.
#### L'algoritmo e la sua analisi (dalle slide)
(MITZ_UPFAL_Chapter-3, pp. 13-24.) Input: $n=2k+1$ elementi di un universo totalmente ordinato; output: il $(k+1)$-esimo. Ordinare costa $O(n\log n)$ ed esiste un complicato algoritmo deterministico lineare; qui si vuole un algoritmo randomizzato semplice e lineare.
```pseudo
\begin{algorithm}
\caption{MedianaRandomizzata($S$)}
\begin{algorithmic}
\State $R \gets$ campione di $n^{3/4}$ elementi di $S$, scelti indipendentemente e uniformemente con reinserimento
\State ordina $R$
\State $d \gets$ elemento di $R$ in posizione $\frac12 n^{3/4}-\sqrt n$ (dal più piccolo)
\State $u \gets$ elemento di $R$ in posizione $\frac12 n^{3/4}+\sqrt n$ (dal più piccolo)
\State confronta ogni $x \in S$ con $d$ e $u$: $C \gets \{x \in S : d \le x \le u\}$, $\ell_d \gets |\{x \in S : x < d\}|$, $\ell_u \gets |\{x \in S : x > u\}|$
\If{$\ell_d > n/2 \lor \ell_u > n/2$}
  \State \Return FAIL
\EndIf
\If{$|C| > 4n^{3/4}$}
  \State \Return FAIL
\EndIf
\State ordina $C$
\State \Return l'elemento di $C$ in posizione $\lfloor n/2\rfloor-\ell_d+1$
\end{algorithmic}
\end{algorithm}
```

Il campione ordinato ha $n^{3/4}\log n$ di costo, gli insiemi $C$ abbastanza piccoli si ordinano in tempo lineare e i confronti con $d$ e $u$ costano $O(n)$. L'algoritmo sbaglia a calcolare la mediana in tempo lineare solo se accade uno di tre eventi: $E_1$, meno di $\frac12n^{3/4}-\sqrt n$ campioni sono sotto la mediana; $E_2$, lo stesso sopra la mediana; $E_3$, $|C|>4n^{3/4}$. Il numero $Y_1$ di campioni sotto la mediana è somma di $n^{3/4}$ indicatrici indipendenti di media $\frac12$ e varianza $\frac14$, quindi $\mathbb{E}[Y_1]=\frac12n^{3/4}$ e $\mathrm{Var}[Y_1]=\frac14n^{3/4}$. Per Chebyshev
$$\Pr[E_1]\le\Pr\big[|Y_1-\mathbb{E}[Y_1]|>\sqrt n\big]\le\frac{n^{3/4}/4}{n}=\frac14n^{-1/4}$$
e lo stesso per $E_2$. Per $E_3$ si osserva che $|C|>4n^{3/4}$ implica che almeno $2n^{3/4}$ elementi di $C$ siano sopra la mediana o sotto: lo stesso argomento (pp. 21-24) dà $\Pr[E_3]\le\frac12n^{-1/4}$. L'algoritmo ha successo con probabilità almeno $1-n^{-1/4}$.

> [!warning] Precisazioni sulle slide
> - L'evento $E_3$ è scritto come $|C|>n/\log n$ (pp. 16-17 e 21), mentre l'algoritmo e la dimostrazione usano la soglia $4n^{3/4}$: per $n$ abbastanza grande questa è più piccola, quindi basta.
> - Il "$\sqrt n$" della spiegazione a lezione va letto così: la deviazione standard di $Y_1$ è $\sqrt{n^{3/4}/4}=\frac12n^{3/8}$ e la finestra $\pm\sqrt n$ è più larga di un fattore $2n^{1/8}$, da cui l'errore $O(n^{-1/4})$ di Chebyshev.
### I bound di Chernoff
La parte probabilistica di questa lezione segue il libro di Kleinberg e Tardos, *Algorithm Design* (capitolo sugli algoritmi randomizzati). Il docente consiglia di studiare sul libro e non sulle slide, e per le varie forme del bound il capitolo 4 di Mitzenmacher e Upfal.

Finora:
- la **disuguaglianza di Markov** vale per qualunque variabile aleatoria non negativa, ma è molto grossolana;
- la **disuguaglianza di Chebyshev** misura lo scostamento dal valore medio in funzione della **varianza** (analisi del secondo momento). Per $n$ bit casuali indipendenti con $\Pr[1]=\frac12$ e $X$ la loro somma: $\mathbb{E}[X]=\frac n2$, $\mathrm{Var}[X]=\frac n4$, e
$$\Pr\left[X\geq\tfrac34n\right]\leq\frac4n$$
che tende a 0 come l'inverso di un **polinomio** (legge dei grandi numeri).

Le **code** sono le aree sotto la "campana" della distribuzione oltre una certa soglia: più sono piccole, più la variabile è concentrata attorno al valore medio. I bound di Chernoff mostrano che, nelle stesse condizioni (somma di variabili binarie indipendenti), la distribuzione è molto più concentrata di quanto dica Chebyshev: a $\frac34n$ la coda decresce **esponenzialmente** in $n$.

> [!quote] Teorema (bound di Chernoff, coda superiore)
> Siano $X_1,\dots,X_n$ variabili binarie indipendenti, $X=\sum_iX_i$ e $\mu\geq\mathbb{E}[X]$. Allora per ogni $\delta>0$
> $$\Pr[X\geq(1+\delta)\mu]<\left[\frac{e^\delta}{(1+\delta)^{1+\delta}}\right]^\mu$$

Come leggerlo: per $\delta$ costante la base $\frac{e^\delta}{(1+\delta)^{1+\delta}}$ è una **costante minore di 1**, e l'esponente è il valore medio $\mu$. Se $\mu$ cresce linearmente con $n$, la probabilità decresce **esponenzialmente** in $n$. (Dalle slide, Chapter-4 p. 2) Per una binomiale con $\mu=np$ e $q=1-p$ Chebyshev dà $\Pr[|X-\mu|>\delta\mu]\le\frac{npq}{\delta^2n^2p^2}=\frac q{\delta^2\mu}$, mentre Chernoff dà $2e^{-\mu\delta^2/3}$.

> [!example] Troppe teste, con Chernoff
> Con le $n$ monete, $\mu=\frac n2$. Per avere almeno $\frac34n$ teste serve $(1+\delta)\mu=\frac34n$, cioè $\delta=\frac12$ (lo scostamento $\frac n4$ è metà del valore medio):
> $$\Pr\left[X\geq\tfrac34n\right]<\left[\frac{e^{1/2}}{(3/2)^{3/2}}\right]^{n/2}\approx0{,}8975^{\,n/2}$$
> Chebyshev dava $\frac4n$, che va a zero come l'inverso di un polinomio; qui la probabilità va a zero esponenzialmente. Già con $n=100$ Chernoff dà circa $4{,}5\cdot10^{-3}$ contro $0{,}04$, e con $n=1000$ circa $3\cdot10^{-24}$ contro $0{,}004$. Con la forma 2 si ha $e^{-\mu\delta^2/3}=e^{-n/24}$ (le slide, p. 17, scrivono $2e^{-n/24}$ per le due code).

> [!warning] Valore di $\delta$ nell'esempio a lezione
> A lezione l'esempio è stato calcolato con $\delta=\frac14$, ottenendo base $\approx0{,}9715$. Ma $\delta=\frac14$ corrisponde a $(1+\delta)\mu=\frac58n$, non a $\frac34n$: per $\frac34n$ serve $\delta=\frac12$, come nelle slide. Il bound resta esponenziale; cambiano la base e i confronti numerici, con Chernoff migliore di Chebyshev già a $n=100$.

Le dimostrazioni non sono richieste: bisogna conoscere gli **enunciati**, saperli **interpretare** e saperli **applicare**.
#### Le altre forme
Con $X_1,\dots,X_n$ binarie indipendenti con $\Pr[X_i=1]=p_i$, $X=\sum_iX_i$ e $\mu=\mathbb{E}[X]$ (forme di Mitzenmacher e Upfal):
1. per ogni $\delta>0$: $\Pr[X\geq(1+\delta)\mu]\leq\left[\dfrac{e^\delta}{(1+\delta)^{1+\delta}}\right]^\mu$;
2. per $0<\delta<1$: $\Pr[X\geq(1+\delta)\mu]\leq e^{-\mu\delta^2/3}$;
3. per $R\geq6\mu$: $\Pr[X\geq R]\leq2^{-R}$.

La forma 2 vale per scostamenti non più grandi di $\mu$ ($\delta$ come $\frac34$, $\frac18$, $\frac1{\sqrt n}$). La forma 3 serve per scostamenti molto grandi, multipli del valore medio. Con $p=\frac12$ non ha senso (con $n$ lanci non si possono avere $3n$ teste), ma se $p$ è piccolo sì: con $p=\frac1{150}$ il valore atteso è $\frac n{150}$, e chiedersi la probabilità di avere 6 o 7 volte quel numero di uni è sensato. In quel caso vale anche la forma 1, ma la 3 è più forte.

Per la **coda inferiore**, per $0<\delta<1$:
$$\Pr[X\leq(1-\delta)\mu]\leq\left[\frac{e^{-\delta}}{(1-\delta)^{1-\delta}}\right]^\mu\qquad\Pr[X\leq(1-\delta)\mu]\leq e^{-\mu\delta^2/2}$$
Anche qui, per $\delta$ costante, la concentrazione è esponenziale.
#### Idea della dimostrazione (dalle slide, non richiesta)
(MITZ_UPFAL_Chapter-4, pp. 3-15.) Per $t>0$, Markov applicato a $e^{tX}$ dà $\Pr[X\ge a]=\Pr[e^{tX}\ge e^{ta}]\le\mathbb{E}[e^{tX}]/e^{ta}$. La **funzione generatrice dei momenti** $M_X(t)=\mathbb{E}[e^{tX}]$ di una somma di variabili indipendenti è il prodotto delle funzioni generatrici; per una Bernoulliana $M_{X_i}(t)=1+p_i(e^t-1)\le e^{p_i(e^t-1)}$, quindi $M_X(t)\le e^{(e^t-1)\mu}$. Scegliendo $t=\ln(1+\delta)$ si ottiene la forma 1; le forme 2 e 3 ne seguono con maggiorazioni elementari, e per la coda inferiore si usa $t=\ln(1-\delta)<0$.
#### Scostamenti vicini al valore medio
Chernoff permette di analizzare anche scostamenti **non costanti** rispetto al valore medio. Con le $n$ monete la deviazione standard è $\sqrt{n/4}$. Spostandosi di un fattore appena più grande, circa $\sqrt{n\log n}$, applicando la forma 2 con $\mu=\frac n2$ e $\delta=\sqrt{6\ln n/n}$ alle due code:
$$\Pr\left[\left|X-\tfrac n2\right|\geq\tfrac12\sqrt{6\,n\ln n}\right]\leq\frac2n$$
Due cose importanti:
- lo scostamento $\sqrt{n\log n}$ è **sublineare**: il rapporto con il valore medio $\frac n2$ tende a 0, eppure fuori da quella fascia c'è solo una probabilità $O(1/n)$;
- Chebyshev dava lo stesso tipo di bound, $O(1/n)$, ma solo per le code oltre $\frac34n$ e sotto $\frac14n$.

> [!warning] Costante nelle slide
> Le slide (Chapter-4, p. 16) scrivono lo stesso calcolo con $\delta=\sqrt{4\ln n/n}$ (scostamento $\sqrt{n\ln n}$) e concludono $\le2/n$. Ma con la forma 2 si ha $e^{-\mu\delta^2/3}=e^{-\frac13\cdot\frac n2\cdot\frac{4\ln n}n}=n^{-2/3}$, non $n^{-1}$. Per ottenere $2/n$ serve $\delta=\sqrt{6\ln n/n}$, come negli appunti: cambia solo la costante sotto radice.

Il quadro completo: dentro $\frac n2\pm\sqrt{n\log n}$ c'è quasi tutta la probabilità, le code da lì in poi pesano come l'inverso di un polinomio, e le code oltre $\frac34n$ e sotto $\frac n4$ pesano come un esponenziale decrescente.

Per i big data il messaggio è che, sotto condizioni di indipendenza, il **valore medio è molto attendibile**: rappresenta bene la distribuzione.
#### Altre applicazioni nelle slide (non viste a lezione)
Le slide del Mitzenmacher-Upfal (Chapter-4, pp. 18-49) proseguono con la stima di un parametro tramite intervalli di confidenza (pp. 18-22), con il **set balancing** (data $A\in\{0,1\}^{n\times n}$ si cerca $b\in\{-1,1\}^n$ che minimizzi $\|Ab\|_\infty$: con $b$ casuale vale $\|Ab\|_\infty\le\sqrt{4n\ln n}$ con probabilità almeno $1-\frac2n$, grazie a un Chernoff per somme di $\pm1$, $\Pr[X\ge a]\le e^{-a^2/2n}$, pp. 23-33) e con il **packet routing** sull'ipercubo, in cui l'instradamento in due fasi (prima verso una destinazione casuale) porta ogni permutazione a destinazione in $O(\log N)$ passi con alta probabilità (pp. 34-49).
### Bilanciamento del carico
Ci sono $m$ job (ad esempio pacchetti da instradare) e $n$ server in parallelo. Un assegnamento deterministico come il **round robin** richiederebbe di coordinarsi a ogni arrivo, e con input online, traffico e server che cadono spesso non funziona. Si usa allora una tecnica **casuale**: ogni job viene mandato a un server scelto uniformemente, indipendentemente dagli altri. È il modello delle **palline nelle scatole** (*balls into bins*).

Ogni server è una macchina sequenziale: il tempo per smaltire i job è lineare nel numero di job ricevuti. Il caso pessimo è che tutti i job finiscano sullo stesso server (tempo $m$); il caso ideale è una distribuzione uniforme, con carico massimo $\frac mn$ e uno speedup di un fattore $n$.

Sia $Y_{ij}=1$ se il job $j$ va al server $i$ ($j=1,\dots,m$, $i=1,\dots,n$). Le $Y_{ij}$ determinano tutto lo spazio di probabilità, e lanci di job diversi sono indipendenti. Il **carico** del server $i$ è
$$X_i=\sum_{j=1}^mY_{ij}\qquad\mathbb{E}[X_i]=\sum_{j=1}^m\frac1n=\frac mn$$
per la linearità del valore atteso. In media il carico è quello ottimale; ma il valore atteso non basta, serve sapere quanto ci si discosta.
#### $m=n$: il carico massimo è $\Theta(\log n/\log\log n)$
Con $m=n$ il carico medio è $\mu=1$. Per la forma 1, con $c=1+\delta$:
$$\Pr[X_i>c]<\frac{e^{c-1}}{c^c}<\left(\frac ec\right)^c$$
Sia $\gamma(n)$ tale che $\gamma(n)^{\gamma(n)}=n$: si ha $\gamma(n)=\Theta\left(\frac{\log n}{\log\log n}\right)$. Scegliendo $c=e\,\gamma(n)$:
$$\Pr[X_i>e\,\gamma(n)]<\left(\frac1{\gamma(n)}\right)^{e\gamma(n)}<\left(\frac1{\gamma(n)}\right)^{2\gamma(n)}=\frac1{n^2}$$
Con lo **union bound** sugli $n$ server, la probabilità che **qualche** server abbia carico maggiore di $e\,\gamma(n)$ è minore di $\frac1n$.

> [!info] Cosa significa in pratica
> Con $n$ job su $n$ server il carico medio è 1, ma il carico **massimo** è con alta probabilità dell'ordine di $\frac{\log n}{\log\log n}$, che **cresce** con $n$, anche se lentamente (circa 3,6 per $n=10^3$, 6,8 per $n=10^9$). Qualche server sarà sicuramente più carico della media, e nessuno lo sarà oltre quel valore. Per dimensionare memoria e potenza dei server non basta il valore atteso: bisogna tenere conto di questa congestione.
#### $m=\Theta(n\log n)$: il carico si uniforma
Con $m=16\,n\ln n$ job il carico medio è $\mu=16\ln n$, e il valore medio compare all'**esponente** del bound. Con $\delta=1$ (forma 1):
$$\Pr[X_i>2\mu]<\left(\frac e4\right)^{16\ln n}<\frac1{n^2}$$
e con $\delta=\frac12$ (coda inferiore):
$$\Pr\left[X_i<\tfrac12\mu\right]<e^{-\frac12\left(\frac12\right)^2\mu}=e^{-2\ln n}=\frac1{n^2}$$
Con lo union bound, con alta probabilità **tutti** i server hanno carico tra metà e il doppio della media: con molti più job che server, la distribuzione diventa "piatta".

> [!example] L'esempio della lezione
> A lezione il calcolo è stato rifatto con $\mu=\ln n$ e $\delta=\frac12$: la probabilità che un server abbia carico inferiore a $\frac12\ln n$ è al più $e^{-\delta^2\mu/2}=n^{-1/8}$, che tende a zero come l'inverso di un polinomio. Con la costante 16 delle slide si arriva a $\frac1{n^2}$, che permette lo union bound su tutti i server.

> [!question] Domanda tipica d'esame
> Enuncia il bound di Chernoff e confrontalo con la disuguaglianza di Chebyshev sul lancio di $n$ monete. Applicalo al bilanciamento del carico: con $n$ job assegnati a caso a $n$ server, qual è il carico massimo con alta probabilità? E con $\Theta(n\log n)$ job?
