---
tags:
  - algoritmi-big-data
  - hashing
  - algoritmi-randomizzati
slide:
  - "HASH_FUNCTIONS_LUCIO_ANDY_11-25.pdf"
---
# Funzioni hash universali
## Hashing universale
Lezione 9 (03/11/2026), slide *The Dictionary Problem and the Hash Functions* di Luciano Gualà e Andrea Clementi, pagine 1-18 (riferimenti: Kleinberg e Tardos, *Algorithm Design*, par. 13.6, citato a lezione, e la lezione 8 del corso MIT 6.046J; una versione più breve è l'appendice *Hash functions* in testa alle slide del capitolo 3, pagine 1-9): le funzioni hash sono state usate più volte ([[03 - Ricerca di oggetti simili#Il costo delle permutazioni casuali|al posto delle permutazioni]] nel min-hashing, nel [[03 - Ricerca di oggetti simili#Locality-sensitive hashing|locality-sensitive hashing]]) senza dire cosa sia una **buona** funzione hash. Si riprendono il problema del dizionario, le **famiglie universali** di funzioni hash e due costruzioni algebriche, con la gestione di insiemi dinamici. Poi si tornerà alla similarità generalizzando l'LSH.
### Rappresentare l'universo
L'universo $U$ degli elementi possibili (merci, proteine, clienti...) è finito, di cardinalità $N$, e lo si può sempre mettere in corrispondenza biunivoca con vettori su un alfabeto: con l'alfabeto binario servono vettori di $\log_2N$ bit (si lavora in $\mathbb{Z}_2$). Più in generale si usa una base **prima** $m$ (si lavora in $\mathbb{Z}_m$), perché con un modulo primo i numeri formano un **campo**: somma e prodotto hanno tutte le proprietà dell'algebra, in particolare ogni elemento non nullo ha un **unico inverso**.
### Il problema del dizionario
Si vuole mantenere un sottoinsieme $S\subseteq U$, qualunque, con le operazioni di **inserimento**, **cancellazione** e **ricerca** (*lookup*). Un array indicizzato direttamente da $U$ funziona, ma occupa memoria $N$, intrattabile. Si vuole invece:
- spazio quasi **lineare** in $|S|=n$;
- operazioni efficienti: idealmente tempo atteso **costante**.

Le soluzioni deterministiche come gli alberi AVL danno $O(\log n)$ per operazione con spazio lineare. Le **tabelle hash** randomizzate danno spazio lineare e tempo atteso costante, e sono molto più semplici da implementare, soprattutto in contesti dinamici come gli stream di dati, con inserimenti e cancellazioni rapidissimi.

Una **funzione hash** $h:U\to\{0,1,\dots,m-1\}$ manda gli elementi in una tabella di $m$ slot; ogni slot ha una **lista di trabocco** (*separate chaining*) con gli elementi che ci finiscono. Per inserire, cancellare o cercare un elemento si calcola $h$ e si scorre la sua lista. Si ha una **collisione** quando $h(u)=h(v)$ con $u\neq v$; per il paradosso del compleanno, con inserimenti casuali la prima collisione arriva dopo $\Theta(\sqrt m)$ elementi.

Si sceglie $m$ circa uguale a $n$, la dimensione prevista di $S$ (non di $U$). Si vuole che:
- $h$ sia **facile da rappresentare**: se per sapere quale $h$ si sta usando serve una tabella grande come $S$, tanto vale memorizzare $S$;
- $h$ distribuisca bene gli elementi, così che la lunghezza attesa delle liste sia **costante**.
### Una funzione deterministica non basta
Se $N\geq m^2$ (e spesso l'universo è addirittura esponenzialmente più grande di $S$), per **qualunque** funzione deterministica $h:U\to\{0,\dots,m-1\}$ c'è uno slot in cui finiscono almeno $N/m\geq m$ elementi: come mettere $m^2$ palline in $m$ scatole, una scatola ne prende almeno $m$. Un **avversario** che conosce $h$ sceglie $S$ proprio tra quegli elementi, e con $|S|=m$ tutti finiscono nella stessa lista: la ricerca diventa lineare.

> [!info] Hashing deterministico nelle slide
> Le slide (p. 6) ricordano la scelta deterministica classica: si rappresentano gli elementi come interi in $[N]$, si prende un primo $p$ con $m\leq p\leq2m$ e si pone $h(u)=u\bmod p$. Il fatto appena visto vale ancora, ma gli elementi dell'universo risultano ben distribuiti, e per applicazioni **statiche** funziona abbastanza bene.

Si usa allora la **randomizzazione**: $h$ viene scelta a caso in una **famiglia** di funzioni. L'avversario conosce l'algoritmo e la famiglia, ma non la scelta casuale.
### La funzione perfettamente casuale
La funzione casuale "ideale" manda ogni elemento in uno slot scelto uniformemente e indipendentemente dagli altri: è l'esperimento delle [[02 - Algoritmi randomizzati e probabilità#Bilanciamento del carico|palline nelle scatole]], e la lunghezza attesa di una lista è $\frac nm$, costante se $m\approx n$. Il problema è **rappresentarla**: non è comprimibile, e per ogni elemento bisogna memorizzare il suo slot, cioè $|S|\log m$ bit. Per sapere dove va un elemento bisogna rileggere una tabella grande come $S$: non si è risolto niente. Serve una nozione di casualità più **debole**, che però permetta una rappresentazione esponenzialmente più compatta.
### Famiglie universali
> [!quote] Famiglia universale (Carter e Wegman, anni '80)
> Una famiglia $\mathcal H$ di funzioni $h:U\to\{0,1,\dots,m-1\}$ è **universale** se per ogni coppia di elementi $u\neq v$
> $$\Pr_{h\in\mathcal H}\big[h(u)=h(v)\big]\leq\frac1m$$
> dove $h$ è scelta **uniformemente** in $\mathcal H$. Inoltre deve essere possibile scegliere $h$ a caso in modo efficiente e calcolare $h(u)$ in modo efficiente.

Non è più una singola funzione a essere universale, ma una **famiglia**. La probabilità di collisione è la migliore possibile: lo slot di $v$ è equiprobabile tra tutti gli $m$.

> [!example] Universale o no
> Con $U=\{a,b,c,d,e,f\}$ e $m=2$:
> - la famiglia $\{h_1,h_2\}$ con $h_1=(0,1,0,1,0,1)$ e $h_2=(0,0,0,1,1,1)$ (i valori su $a,\dots,f$) **non** è universale: $\Pr[h(a)=h(c)]=1>\frac12$;
> - aggiungendo $h_3=(0,0,1,0,1,1)$ e $h_4=(1,0,0,1,1,0)$ la famiglia $\{h_1,h_2,h_3,h_4\}$ è universale: ogni coppia collide con probabilità al più $\frac12$ (ad esempio $\Pr[h(a)=h(f)]=0$).

> [!quote] Proposizione (liste di trabocco)
> Sia $\mathcal H$ una famiglia universale, $h$ scelta uniformemente in $\mathcal H$, $S\subseteq U$ con $|S|\leq n$ e $u\in U$. Allora il numero atteso di elementi di $S$ che collidono con $u$ è al più $\frac nm$; se $m\geq n$, al più 1.

**Dimostrazione.** Per $s\in S$ sia $X_s=1$ se $h(s)=h(u)$ e 0 altrimenti, e $X=\sum_{s\in S}X_s$ il numero di collisioni con $u$, cioè la lunghezza della sua lista di trabocco. Per la linearità del valore atteso, e poiché ogni $X_s$ è una variabile binaria:
$$\mathbb{E}[X]=\sum_{s\in S}\mathbb{E}[X_s]=\sum_{s\in S}\Pr[X_s=1]\leq\sum_{s\in S}\frac1m=\frac{|S|}m\leq1\qquad\blacksquare$$
Contando anche $u$ stesso, se appartiene a $S$, la lista ha lunghezza attesa al più $1+\frac{|S|}m$. Con $m\approx|S|$ è **costante**: la famiglia universale dà lo stesso carico atteso di una funzione perfettamente casuale.
### Prima costruzione: prodotto scalare modulo $m$
Si sceglie un **primo** $m$ con $n\leq m\leq2n$ (esiste sempre per un risultato di teoria dei numeri, il *postulato di Bertrand*, dimostrato da Chebyshev nel 1850 come citano le slide, e lo si trova facilmente con un algoritmo randomizzato). Ogni $x\in U$ si rappresenta come un vettore di $r$ cifre in base $m$, $x=(x_1,\dots,x_r)$ con $0\leq x_i<m$: elementi distinti hanno codifiche distinte, cioè $U$ corrisponde a $\mathbb{Z}_m^r$. Per ogni vettore $a=(a_1,\dots,a_r)$ con $0\leq a_i<m$ si definisce
$$h_a(x)=\left(\sum_{i=1}^ra_ix_i\right)\bmod m\qquad\mathcal H=\{h_a: a\in\mathbb{Z}_m^r\}$$
Il risultato è tra $0$ e $m-1$, cioè proprio un indice della tabella. Scegliere $h$ a caso significa scegliere $a$ uniformemente, cioè ogni componente $a_i$ uniformemente e indipendentemente.

**Spazio.** Perché $m^r\geq N$ servono $r=\frac{\log N}{\log m}$ cifre, ciascuna di $\log m$ bit: per memorizzare $h_a$ basta memorizzare $a$, cioè
$$r\log m=\log N\ \text{bit}$$
logaritmico nella dimensione dell'universo, invece di $|S|\log m$. La rappresentazione di $h$ deve dipendere dall'universo e non da $S$, che cambia nel tempo. Le funzioni della famiglia sono tante quante gli elementi di $U$ (esponenzialmente molte), ma per sceglierne e memorizzarne una basta un vettore. Il calcolo di $h_a(x)$ richiede $r$ prodotti e somme modulo $m$. Nel modello **word-RAM** delle slide (manipolare un numero costante di parole macchina costa tempo costante e ogni oggetto d'interesse sta in una parola), memorizzare $h_a$ significa memorizzare un solo valore $a$, e calcolare $h_a(x)$ costa $O(1)$. Esempio delle slide: scelto $a$ a caso, per inserire 10 elementi si calcola $h_a$ 10 volte, sempre con lo stesso $a$, e si ottengono i 10 slot.

> [!quote] Teorema
> $\mathcal H=\{h_a:a\in\mathbb{Z}_m^r\}$ è una famiglia universale.

**Dimostrazione.** Siano $x=(x_1,\dots,x_r)\neq y=(y_1,\dots,y_r)$, scelti dall'avversario guardando la famiglia. Bisogna mostrare che $\Pr[h_a(x)=h_a(y)]\leq\frac1m$, dove l'unica variabile aleatoria è $a$.
- Poiché $x\neq y$, esiste un indice $j$ con $x_j\neq y_j$.
- $h_a(x)=h_a(y)$ se e solo se $\sum_ia_ix_i\equiv\sum_ia_iy_i\pmod m$, cioè, portando a sinistra il termine $j$-esimo:
$$a_j\underbrace{(y_j-x_j)}_{z}\equiv\underbrace{\sum_{i\neq j}a_i(x_i-y_i)}_{\alpha}\pmod m\qquad(1)$$
con $z\not\equiv0$.
- **Principio delle decisioni rimandate** (*principle of deferred decisions*): le componenti $a_i$ sono indipendenti, quindi si può immaginare di scegliere prima tutte le $a_i$ con $i\neq j$ e solo alla fine $a_j$. Fissate le altre, $\alpha$ è un numero fissato tra $0$ e $m-1$.
- Poiché $m$ è primo e $z\not\equiv0$, $z$ ha un unico inverso $z^{-1}$, e la (1) equivale a $a_j\equiv\alpha z^{-1}\pmod m$: tra gli $m$ valori possibili di $a_j$ ce n'è **al più uno** cattivo.
- È come lanciare un dado a $m$ facce con una sola faccia cattiva: $\Pr[h_a(x)=h_a(y)]\leq\frac1m$. $\blacksquare$

> [!info] Il fatto di teoria dei numeri
> Se $m$ è primo e $z\not\equiv0\pmod m$, allora $\alpha z\equiv\beta\pmod m$ ha al più una soluzione $0\leq\alpha<m$. Infatti, se $\alpha_1\neq\alpha_2$ fossero due soluzioni, $(\alpha_1-\alpha_2)z\equiv0$, cioè $m$ divide $(\alpha_1-\alpha_2)z$; poiché $m$ è primo e non divide $z$, divide $\alpha_1-\alpha_2$, quindi $\alpha_1=\alpha_2$. Qui si usa che $m$ è primo. In realtà la soluzione è esattamente una (algoritmo di Euclide), e la probabilità è proprio $\frac1m$.

> [!info] Una domanda a lezione
> $a_j$ può valere anche 0: è solo uno dei casi possibili, e non serve escluderlo. La disuguaglianza $\leq\frac1m$ (invece di $=$) riguarda il caso generale; con le $a_i$ uniformi su tutto $\mathbb{Z}_m$ la probabilità di collisione è esattamente $\frac1m$.

Con questa famiglia, usando la proposizione, il carico atteso di ogni slot è $O(n/m)$: spazio $\Theta(m)$ e, con $m\approx n$, tempo atteso $O(1)$ per inserimento, cancellazione e ricerca.

> [!question] Domanda tipica d'esame
> Definisci una famiglia universale di funzioni hash e dimostra che la lunghezza attesa di una lista di trabocco è al più $1+|S|/m$. Costruisci la famiglia $h_a(x)=\sum_ia_ix_i\bmod m$: quanto spazio serve per rappresentare una funzione e quanto per calcolarla? Dimostra che è universale. Il docente chiede di saper costruire e usare la famiglia (inserire, cancellare, cercare un elemento) e di saperne analizzare spazio e tempo.
### Seconda costruzione: una retta casuale
Si sceglie un primo $p\geq N$, così che $U$ si possa mettere in corrispondenza biunivoca con $\mathbb{Z}_p=\{0,1,\dots,p-1\}$, e un primo $m$ con $n\leq m\leq2n$. Per $a\neq0$ e $b$ in $\mathbb{Z}_p$:
$$h_{a,b}(x)=\big((a\cdot x+b)\bmod p\big)\bmod m\qquad\mathcal H=\{h_{a,b}:a\in\mathbb{Z}_p\setminus\{0\},\ b\in\mathbb{Z}_p\}$$
(fare $\bmod\ 7$ di 178 significa dividere per 7 e prendere il resto). Geometricamente si sceglie una **retta casuale** $y=ax+b$ in $\mathbb{Z}_p$: è iniettiva, quindi elementi distinti vanno in punti distinti, e l'avversario che sceglie $S$ non sa quale retta verrà scelta. Il valore $y$ è ancora in $\mathbb{Z}_p$, troppo grande, e lo si riduce $\bmod\ m$ per trovare il bucket. Per calcolarla si memorizzano $a$ e $b$, cioè $O(\log p)=O(\log N)$ bit, e le operazioni su numeri di $\log p$ bit costano tempo costante nel modello RAM.

Questa famiglia è **universale** e anche **a due a due indipendente** (*pairwise independent*): per ogni $x\neq y$ e ogni coppia di slot $i,j$
$$\Pr_h\big[h(x)=i\land h(y)=j\big]\leq\Pr[h(x)=i]\cdot\Pr[h(y)=j]=\frac1{m^2}$$
cioè sapere dove è finito un elemento non dice nulla su dove finisce un altro. È importante quando si analizza la **varianza** delle liste di trabocco, non solo il valore atteso: la probabilità degli eventi congiunti non supera il prodotto.

> [!warning] L'enunciato preciso nelle slide
> La definizione detta a lezione è una semplificazione. Nelle slide (pp. 14-17, con la nota del docente "rivedere e correggere bene!!!") il lemma è dimostrato **prima** della riduzione $\bmod\ m$, per $X=(ax+b)\bmod p$ e $Y=(ay+b)\bmod p$ con $x\neq y$:
> - **Claim 1**: $X$ e $Y$ sono uniformi su $\mathbb{Z}_p$, perché $a,b$ sono uniformi e $x\mapsto ax+b$ è iniettiva per $a\neq0$;
> - **Claim 2**: $X$ e $Y$ sono **quasi** indipendenti a coppie, $\Pr[X=i\land Y=j]=\frac{1}{(p-1)p}$ per $i\neq j$, perché il sistema $ax+b\equiv i$, $ay+b\equiv j$ ha un'unica soluzione $(a,b)$ (le due equazioni sono indipendenti, dato che $x\neq y$); e $X\neq Y$ sempre.
>
> L'universalità segue così: da Claim 2 si ha $\Pr[Y=j\mid X=i]=\frac1{p-1}$; fissato $i$, i valori $j\neq i$ di $\mathbb{Z}_p$ con $j\equiv i\pmod m$ sono al più $\lceil p/m\rceil-1\leq\frac{p-1}{m}$; per la union bound $\Pr[Y\equiv i\ (\mathrm{mod}\ m)\mid X=i]\leq\frac{p-1}m\cdot\frac1{p-1}=\frac1m$, e sommando su $i$ con peso $\Pr[X=i]=\frac1p$ si ottiene $\Pr[h_{a,b}(x)=h_{a,b}(y)]\leq\frac1m$.
>
> Dopo la riduzione $\bmod\ m$ gli slot non sono esattamente uniformi (se $m$ non divide $p$, alcuni resti hanno una controimmagine in più in $\mathbb{Z}_p$), quindi la condizione $\leq\frac1{m^2}$ per $h_{a,b}$ vale solo **approssimativamente**. All'esame bastano gli enunciati, come detto dal docente.

> [!info] Cosa sapere
> Per la prima famiglia: la costruzione, come si usa (arriva un elemento, come lo si inserisce, lo si cancella, lo si cerca), l'analisi di spazio e tempo, la definizione di universalità con il corollario sulle liste di trabocco e la dimostrazione. Per la seconda: la costruzione (la corrispondenza tra $U$ e $\mathbb{Z}_p$, poi il modulo $m$), l'analisi di spazio e tempo e gli enunciati di universalità e indipendenza a coppie, senza dimostrazioni.
### Insiemi dinamici: raddoppio e dimezzamento
L'analisi assume che $|S|$ resti all'incirca $n$, la dimensione con cui si è dimensionata la tabella. In un ambiente dinamico può cambiare molto: partendo con 20 elementi e facendo 2000 inserimenti, le liste non sono più costanti rispetto alla dimensione vera di $S$. Si usa la tecnica del **raddoppio e dimezzamento** (*doubling/halving*):
- un contatore tiene il numero di elementi presenti;
- quando **raddoppia**, si sceglie una nuova funzione hash casuale per una tabella di dimensione doppia (nuovi parametri, $m$ doppio) e si reinseriscono tutti gli elementi, con costo $O(n)$;
- quando si **dimezza**, lo stesso con una tabella più piccola.

Il costo $O(n)$ si paga solo dopo almeno $\frac n2$ operazioni, quindi il costo **ammortizzato** per operazione resta $O(1)$.

Nelle slide (p. 18) la regola è più precisa. I parametri sono $n=|S|$, il numero di elementi presenti, una dimensione "virtuale" $N$ della tabella e la dimensione reale $m$, un primo tra $N$ e $2N$:
- all'inizio $n=N=1$;
- quando $n>N$: $N:=2N$, si sceglie un nuovo $m$ e si rifà l'hashing di tutti gli elementi, in tempo $O(n)$;
- quando $n<\frac N4$: $N:=\frac N2$, nuovo $m$ e nuovo hashing.

Si dimezza quando gli elementi scendono sotto un **quarto**, non sotto la metà: così, dopo un raddoppio, ci vogliono molte cancellazioni prima di dover dimezzare, e una sequenza che oscilla attorno alla soglia non provoca un ricalcolo a ogni operazione (spiegazione nostra; le slide indicano solo il costo ammortizzato $O(1)$ per inserimento e cancellazione).
### Prossimi passi
Le famiglie universali limitano le liste di trabocco solo **in valore atteso**: con sfortuna possono essere molto più lunghe. La prossima volta si vedrà il **doppio hashing randomizzato** (*perfect hashing*): la costruzione diventa lineare solo con alta probabilità, ma una volta costruita la struttura la ricerca costa $O(1)$ nel **caso peggiore**. È la parte *Perfect (Randomized) Hashing* delle stesse slide, pagine 19-26.
