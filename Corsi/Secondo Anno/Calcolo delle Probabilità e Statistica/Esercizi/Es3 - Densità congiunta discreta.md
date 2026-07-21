## Es3 — Densità congiunta discreta
Terzo esercizio dello scritto. La traccia **regala** la densità congiunta $p_{X_1,X_2}(x_1,x_2)$ di due variabili aleatorie discrete e chiede di ricavarne qualcosa: una probabilità su un evento che coinvolge entrambe, una marginale, una condizionata, o la densità di una trasformazione $Y=g(X_1,X_2)$.

Non c'è niente da modellizzare — la parte difficile di [[Es1 - Probabilità discreta elementare|Es1]] qui è già fatta. Tutto l'esercizio è **sommare la densità sulle coppie giuste**, e riconoscere le serie che ne escono.
### L'unico principio che serve
$$P\big((X_1,X_2)\in A\big)=\sum_{(x_1,x_2)\in A}p_{X_1,X_2}(x_1,x_2)$$

Cioè: qualunque cosa venga chiesta, si tratta di **capire quali coppie $(x_1,x_2)$ soddisfano la condizione** e sommare la densità su quelle. Tutte le formule qui sotto sono casi particolari di questo.

> [!warning] Il supporto è metà dell'esercizio
> La densità è definita solo su certe coppie e vale **zero su tutte le altre**. Se la traccia dice
> $$p_{X_1,X_2}(k,k)=q\frac{2^k}{k!}e^{-2}\ (k\ge0)\qquad p_{X_1,X_2}(h,0)=(1-q)\frac{3^{h-1}}{(h-1)!}e^{-3}\ (h\ge1)$$
> allora la densità vive **solo** sulla diagonale $x_1=x_2$ e sulla riga $x_2=0$: la coppia $(2,5)$ ha probabilità zero.
>
> Prima di sommare qualsiasi cosa, disegnare o immaginare dove sta il supporto. Quasi tutti gli errori di questo esercizio nascono dal sommare su coppie che non esistono, o dal dimenticarne di valide.

### Le quattro richieste possibili
**Marginale** — si somma sull'altra variabile, facendola sparire:

$$p_{X_1}(x_1)=\sum_{x_2}p_{X_1,X_2}(x_1,x_2)$$

**Probabilità di un evento congiunto** — $P(X_1>X_2)$, $P(X_1X_2=0)$, $P(X_1+X_2\le1)$: si elencano le coppie compatibili e si somma.

**Condizionata** — è la definizione di sempre, dove numeratore e denominatore sono due somme:

$$P(A|B)=\frac{P(A\cap B)}{P(B)}$$

**Densità di una trasformazione** $Y=g(X_1,X_2)$ — per ogni valore $y$ raggiungibile:

$$p_Y(y)=\sum_{(x_1,x_2)\,:\,g(x_1,x_2)=y}p_{X_1,X_2}(x_1,x_2)$$

Cioè si raggruppano le coppie che danno lo stesso valore di $Y$.
### Le serie che devi riconoscere a vista
Quando il supporto è infinito, la somma diventa una serie, e Macci ne usa sempre le stesse due:

**Serie esponenziale** — è quella della [[02 - Modelli discreti#Distribuzione di Poisson|Poisson]]:

$$\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda}$$

**Serie geometrica** — dimostrata in [[02 - Modelli discreti#Formula della serie geometrica|serie geometrica]]:

$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad(|r|<1)$$

> [!info] Il trucco del cambio di indice
> Le densità sono scritte apposta perché la serie **non parta da zero**: compaiono $\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}$ o $\frac{3^{h-1}}{(h-1)!}$. Si pone $h=x_2-x_1$ (oppure $h=h-1$) e la somma torna nella forma standard, con risultato $e^{\lambda}$.
>
> Riconoscere che una somma vale **esattamente 1** perché è una densità di Poisson o geometrica su tutto il suo supporto è la mossa che chiude metà degli Es3.

### Esercizi svolti — formato 2025-2026
#### Condizionata su un supporto sparso — appello del 6 Febbraio 2026
Sia $q\in(0,1)$. Densità congiunta:

$$p_{X_1,X_2}(k,k)=q\frac{2^{k}}{k!}e^{-2}\ (k\ge0)\qquad p_{X_1,X_2}(h,0)=(1-q)\frac{3^{h-1}}{(h-1)!}e^{-3}\ (h\ge1)$$

Calcolare $P(X_1=X_2|X_2=0)$.

**Svolgimento**

Il supporto è l'unione della diagonale e della riga $x_2=0$. Le due parti si **intersecano** nella sola coppia $(0,0)$.

Numeratore: $\{X_1=X_2\}\cap\{X_2=0\}$ significa $x_1=x_2=0$, cioè la sola coppia $(0,0)$:

$$P(\{X_1=X_2\}\cap\{X_2=0\})=p_{X_1,X_2}(0,0)=q\frac{2^0}{0!}e^{-2}=qe^{-2}$$

Denominatore: $\{X_2=0\}$ raccoglie $(0,0)$ e tutte le $(h,0)$ con $h\ge1$. La serie che ne esce è una densità di Poisson completa, quindi vale 1:

$$P(X_2=0)=qe^{-2}+(1-q)\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}e^{-3}=qe^{-2}+(1-q)\underbrace{e^{-3}e^{3}}_{=1}=qe^{-2}+1-q$$

$$P(X_1=X_2|X_2=0)=\frac{qe^{-2}}{qe^{-2}+1-q}$$

Il risultato resta in forma letterale: è normale, la traccia non dà valori numerici per $q$.
#### Densità di $Y=X_1X_2$ su supporto finito — appello del 20 Febbraio 2026
Densità congiunta: $p_{X_1,X_2}(x_1,x_2)=\frac{1}{10}$ per $(x_1,x_2)\in\{(0,0),(0,1),(0,2),(1,0),(2,0)\}$, e $p_{X_1,X_2}(1,1)=p_{X_1,X_2}(2,2)=\frac{1}{4}$.

Trovare la densità discreta di $Y=X_1X_2$.

**Svolgimento**

Supporto finito, sette coppie in tutto: si calcola $x_1x_2$ per ciascuna e si raggruppa.

Le prime cinque coppie hanno tutte almeno uno zero, quindi danno $Y=0$; la coppia $(1,1)$ dà $Y=1$; la coppia $(2,2)$ dà $Y=4$.

$$p_Y(0)=5\cdot\frac{1}{10}=\frac{1}{2}\qquad p_Y(1)=\frac{1}{4}\qquad p_Y(4)=\frac{1}{4}$$

> [!info] Il controllo che costa dieci secondi
> $\frac{1}{2}+\frac{1}{4}+\frac{1}{4}=1$. Quando la richiesta è **la densità di $Y$**, la somma dei valori trovati deve fare 1 — se non torna, hai perso una coppia o ne hai contata una due volte.

#### Marginale e coda — appello del 19 Giugno 2026
Siano $q\in(0,1)$ e $\lambda>0$. Densità congiunta:

$$p_{X_1,X_2}(x_1,x_2)=(1-q^2)^{x_1}q^2\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}e^{-\lambda}\qquad\text{per }x_2\ge x_1\ge0$$

Calcolare $P(X_1\ge k)$ per $k\ge0$ intero.

**Svolgimento**

Non si può sommare direttamente su $\{X_1\ge k\}$ senza prima liberarsi di $x_2$: si calcola la **marginale** di $X_1$, sommando su tutti gli $x_2\ge x_1$ ammessi.

Il fattore $(1-q^2)^{x_1}q^2$ non dipende da $x_2$ e esce dalla somma; il resto, con la sostituzione $h=x_2-x_1$, è la serie esponenziale:

$$p_{X_1}(x_1)=(1-q^2)^{x_1}q^2e^{-\lambda}\sum_{h\ge0}\frac{\lambda^{h}}{h!}=(1-q^2)^{x_1}q^2e^{-\lambda}e^{\lambda}=(1-q^2)^{x_1}q^2$$

Riconosciamo una **geometrica** di parametro $q^2$. La coda si somma con la serie geometrica:

$$P(X_1\ge k)=\sum_{x_1\ge k}(1-q^2)^{x_1}q^2=q^2\cdot\frac{(1-q^2)^{k}}{1-(1-q^2)}=q^2\cdot\frac{(1-q^2)^{k}}{q^2}=(1-q^2)^{k}$$

Stesso risultato che si otterrebbe dalla [[02 - Modelli discreti#Formula per la "coda" di una v.a. geometrica (e per la traslata)|formula della coda]] con $p=q^2$: una volta riconosciuta la marginale, la formula è già pronta.
### Esercizi svolti — varianti dagli appelli precedenti
#### Densità che si fattorizza: variabili indipendenti — appello del 20 Febbraio 2025
Densità congiunta:

$$p_{X_1,X_2}(x_1,x_2)=\frac{2^{x_1}}{x_1!}e^{-2}\cdot\frac{\binom{3}{x_2}\binom{3}{2-x_2}}{\binom{6}{2}}\qquad x_1\ge0,\ x_2\in\{0,1,2\}$$

**D5)** Calcolare $P(X_1X_2=0)$. **D6)** Verificare che $P(X_1+X_2\le1)=\frac{6}{5}e^{-2}$.

**Svolgimento**

La densità è un **prodotto** di due fattori, uno che dipende solo da $x_1$ e uno solo da $x_2$: le due variabili sono **indipendenti**, con $X_1\sim\text{Poisson}(2)$ e $X_2$ ipergeometrica. Riconoscerlo semplifica ogni conto.

**D5)** $X_1X_2=0$ quando almeno una delle due è zero. Le coppie sono: tutte le $(k,0)$ con $k\ge0$, più $(0,1)$ e $(0,2)$. Nella prima famiglia la somma su $k$ della densità di Poisson vale 1:

$$P(X_1X_2=0)=\underbrace{\sum_{k\ge0}\frac{2^k}{k!}e^{-2}}_{=1}\cdot\frac{3}{15}+e^{-2}\left(\frac{9}{15}+\frac{3}{15}\right)=\frac{1}{5}+\frac{4}{5}e^{-2}$$

**D6)** $X_1+X_2\le1$ ammette solo tre coppie: $(0,0)$, $(0,1)$, $(1,0)$.

$$P(X_1+X_2\le1)=e^{-2}\frac{3}{15}+e^{-2}\frac{9}{15}+2e^{-2}\frac{3}{15}=\frac{3+9+6}{15}e^{-2}=\frac{18}{15}e^{-2}=\frac{6}{5}e^{-2}$$

#### Inclusione-esclusione su $\{X_1X_2=0\}$ — appello del 20 Giugno 2024
Sia $q\in(0,1)$ e $p_{X_1,X_2}(x_1,x_2)=(1-q)^{x_1}(1-q^2)^{x_2}q^3$ per $x_1,x_2\ge0$ interi.

Verificare che $P(X_1X_2=0)=q+q^2-q^3$.

**Svolgimento**

Anche qui la densità si fattorizza, quindi $X_1$ e $X_2$ sono indipendenti. L'evento $\{X_1X_2=0\}$ è l'**unione** $\{X_1=0\}\cup\{X_2=0\}$, e le due non sono disgiunte: si usa l'inclusione-esclusione.

$$P(X_1X_2=0)=P(X_1=0)+P(X_2=0)-P(X_1=0,X_2=0)$$

Ogni pezzo è una serie geometrica:

$$P(X_1=0)=\sum_{k\ge0}q^3(1-q^2)^{k}=\frac{q^3}{1-(1-q^2)}=\frac{q^3}{q^2}=q$$

$$P(X_2=0)=\sum_{k\ge0}q^3(1-q)^{k}=\frac{q^3}{q}=q^2\qquad P(X_1=0,X_2=0)=q^3$$

$$P(X_1X_2=0)=q+q^2-q^3$$

> [!warning] Prodotto uguale a zero significa unione, non intersezione
> $X_1X_2=0$ vale quando **almeno una** delle due è nulla. Sommare $P(X_1=0)+P(X_2=0)$ senza sottrarre l'intersezione conta due volte la coppia $(0,0)$.

#### Densità simbolica a tabella — appello del 23 Febbraio 2021
La densità è data per valori simbolici: $p_{X_1,X_2}(0,0)=q_{00}$, $p_{X_1,X_2}(0,1)=q_{01}$, $p_{X_1,X_2}(1,0)=q_{10}$, $p_{X_1,X_2}(1,2)=q_{12}$, $p_{X_1,X_2}(2,1)=q_{21}$, tutti positivi e con somma 1.

**D5)** Trovare la densità di $Y=X_1+X_2$. **D6)** Calcolare $P(X_1>X_2|X_1+X_2>1)$.

**Svolgimento**

**D5)** Si calcola $x_1+x_2$ per le cinque coppie e si raggruppa: $(0,0)\to0$; $(0,1)$ e $(1,0)\to1$; $(1,2)$ e $(2,1)\to3$.

$$p_Y(0)=q_{00}\qquad p_Y(1)=q_{01}+q_{10}\qquad p_Y(3)=q_{12}+q_{21}$$

Il valore $Y=2$ **non è raggiungibile**: nessuna coppia del supporto somma a 2. Va detto, non omesso.

**D6)** L'evento $\{X_1+X_2>1\}$ coincide con $\{Y=3\}$, cioè le coppie $(1,2)$ e $(2,1)$. Fra queste, $X_1>X_2$ solo per $(2,1)$:

$$P(X_1>X_2|X_1+X_2>1)=\frac{p_{X_1,X_2}(2,1)}{p_Y(3)}=\frac{q_{21}}{q_{12}+q_{21}}$$

Con la densità simbolica non c'è nessun conto da fare: tutto l'esercizio è **elencare correttamente le coppie**. È la versione più pura di Es3.
### Trappole ricorrenti
- **Sommare fuori dal supporto**: la densità vale zero sulle coppie non elencate. Se il supporto è $x_2\ge x_1$, la coppia $(3,1)$ non contribuisce.

- **Dimenticare l'intersezione dei pezzi**: quando la densità è definita a pezzi (diagonale + riga), la coppia comune — tipicamente $(0,0)$ — appartiene a entrambi. Va contata una volta sola, e con la formula giusta.

- **Prodotto nullo = unione**: $\{X_1X_2=0\}=\{X_1=0\}\cup\{X_2=0\}$, quindi inclusione-esclusione.

- **Valori non raggiungibili**: nella densità di $Y$ vanno indicati **solo** i valori che $Y$ assume davvero. Scrivere $p_Y(2)=0$ non è sbagliato, ma dimenticare che $p_Y(3)$ esiste sì.

- **Cambio di indice nelle serie**: $\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}$ non è $e^3-1$, è $e^3$ — perché sostituendo $j=h-1$ la somma riparte da $j=0$. Sbagliare qui manda a monte tutto il denominatore.

- **Fattorizzazione = indipendenza**: se la densità si scrive come prodotto di una funzione di $x_1$ per una di $x_2$ (supporto rettangolare compreso), le variabili sono indipendenti e ogni marginale si legge direttamente.
### Collegamenti
- Serie e distribuzioni: [[02 - Modelli discreti#Formula della serie geometrica|serie geometrica]], [[02 - Modelli discreti#Distribuzione di Poisson|Poisson]], [[02 - Modelli discreti#Variabili aleatorie discrete|Variabili aleatorie discrete]].

- Teoria delle condizionate: [[01 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|Cap 2]], e [[01 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenza]] per il criterio di fattorizzazione.

- Slot vicini: [[Es2 - Probabilità condizionata]] usa le stesse condizionate su eventi anziché su variabili; [[Es4 - Trasformazione di variabile continua]] fa la stessa operazione di trasformazione, ma nel continuo.
