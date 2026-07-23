## Formulario — Calcolo delle Probabilità e Statistica
Formulario d'esame (Macci), organizzato per slot d'esercizio. Per ogni modello: quando si usa, le formule e una o più tracce d'esame svolte. Teoria in [[Es1 - Probabilità discreta elementare]] e [[Es2 - Probabilità condizionata]].
### Es1 — Probabilità discreta elementare
#### Riconoscimento del modello
| Situazione | Modello |
|---|---|
| Con reinserimento, numero di prove fisso, conto i successi | Binomiale |
| Con reinserimento, conto le prove fino al 1° successo | Geometrica (serie) |
| Con reinserimento, conto le prove fino all'r-esimo successo | Binomiale negativa |
| Senza reinserimento, due tipi di oggetto | Ipergeometrica |
| Senza reinserimento o in blocco, più di due tipi | Multinomiale / combinatorio |
| Sequenza in ordine fissato | Regola del prodotto (condizionate) |
| Nessun modello combacia | Conteggio diretto |

---
#### Binomiale — Bin(n, p)
Quando: numero di prove fisso e indipendenti, si contano i successi. Dadi e monete sono sempre con reinserimento.

Densità, media e varianza:
$$P(X=k)=\binom{n}{k}\,p^{k}(1-p)^{n-k}$$
$$E[X]=np\qquad\qquad \operatorname{Var}[X]=np(1-p)$$

Caso «almeno uno» (conviene sempre il complementare):
$$P(X\ge1)=1-(1-p)^{n}$$

Traccia tipo — appello del 6 Febbraio 2026:
> Si lancia tre volte un dado equo. Calcolare la probabilità che il numero 4 esca almeno due volte.

Il numero di prove è fissato (tre lanci) e i successi sono "esce 4":
$$X\sim\operatorname{Bin}\!\left(3,\tfrac{1}{6}\right)$$
"Almeno due volte" significa due o tre successi, quindi si sommano i casi:
$$P(X\ge2)=\sum_{k=2}^{3}\binom{3}{k}\left(\tfrac{1}{6}\right)^{k}\left(\tfrac{5}{6}\right)^{3-k}
=3\cdot\tfrac{1}{36}\cdot\tfrac{5}{6}+\tfrac{1}{216}
=\frac{15+1}{216}=\frac{2}{27}$$

Tracce simili negli appelli: «almeno uno» al complementare e speranza di una binomiale (9 Febbraio 2021); riconoscimento con/senza reinserimento contro l'ipergeometrica.

---
#### Geometrica traslata — Geo(p)
Quando: si contano le prove necessarie fino al primo successo. Le prove possibili sono infinite, quindi l'evento va scritto come una serie.

Densità, media e varianza:
$$P(X=k)=(1-p)^{k-1}\,p\qquad (k\ge1)$$
$$E[X]=\frac{1}{p}\qquad\qquad \operatorname{Var}[X]=\frac{1-p}{p^{2}}$$

Formula della serie geometrica (l'evento raccoglie infiniti casi disgiunti, quindi le probabilità si sommano):
$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad (|r|<1)$$

Coda già pronta, per «servono almeno j prove»:
$$P(X\ge j)=(1-p)^{\,j-1}$$

Traccia tipo — appello del 20 Febbraio 2026:
> Si lancia ripetutamente una moneta equa. Calcolare la probabilità che esca testa per la prima volta a un lancio pari diverso dal secondo (al quarto, al sesto, all'ottavo, ecc.).

Con moneta equa la densità si semplifica:
$$P(X=k)=\left(\tfrac{1}{2}\right)^{k-1}\tfrac{1}{2}=\left(\tfrac{1}{2}\right)^{k}$$
I lanci ammessi sono 4, 6, 8, … cioè della forma 2k con k a partire da 2 (il secondo lancio, cioè k = 1, è escluso):
$$P\!\left(\bigcup_{k\ge2}\{X=2k\}\right)
=\sum_{k\ge2}\left(\tfrac{1}{2}\right)^{2k}
=\sum_{k\ge2}\left(\tfrac{1}{4}\right)^{k}
=\frac{(1/4)^{2}}{1-1/4}=\frac{1}{12}$$

Tracce simili — stessa tecnica, cambia solo l'insieme degli indici (il denominatore usa la ragione elevata, non la base):
> Prima testa a un lancio dispari — indici 2m − 1:
$$\sum_{m\ge1}\left(\tfrac{1}{2}\right)^{2m-1}=\frac{1/2}{1-1/4}=\frac{2}{3}$$
> Prima testa a un lancio multiplo di 3 — indici 3m:
$$\sum_{m\ge1}\left(\tfrac{1}{2}\right)^{3m}=\frac{1/8}{1-1/8}=\frac{1}{7}$$

---
#### Binomiale negativa traslata — BinNeg(r, p)
Quando: si contano le prove necessarie fino all'r-esimo successo. Con r = 1 si ricade nella geometrica.

Densità, media e varianza:
$$P(X=k)=\binom{k-1}{r-1}\,p^{r}(1-p)^{k-r}\qquad (k\ge r)$$
$$E[X]=\frac{r}{p}\qquad\qquad \operatorname{Var}[X]=\frac{r(1-p)}{p^{2}}$$

La media è r successi moltiplicati per il costo medio di ciascuno, che è 1/p prove (non r · p):
$$E[X]=r\cdot\frac{1}{p}=\frac{r}{p}$$

Traccia tipo — appello del 3 Febbraio 2025:
> Un'urna ha 9 palline bianche e 18 nere. Si estraggono palline una alla volta con reinserimento. Sia X il numero di palline estratte fino a quando esce per la seconda volta una bianca. Calcolare E[X].

Con reinserimento le prove sono indipendenti e la probabilità di bianca è costante:
$$p=\frac{9}{27}=\frac{1}{3}\qquad r=2$$
$$E[X]=\frac{r}{p}=\frac{2}{1/3}=6$$
Controllo a occhio: se serve in media una estrazione ogni tre per una bianca, per averne due ne servono in media sei.

---
#### Ipergeometrica — Iper(N, K, n)
Quando: n oggetti estratti senza reinserimento da N totali, di cui K "buoni". Le prove sono dipendenti (l'urna cambia a ogni estrazione), quindi non è una binomiale.

Densità, media e varianza:
$$P(X=k)=\frac{\dbinom{K}{k}\dbinom{N-K}{n-k}}{\dbinom{N}{n}}$$
$$E[X]=n\frac{K}{N}\qquad\qquad \operatorname{Var}[X]=n\frac{K}{N}\left(1-\frac{K}{N}\right)\frac{N-n}{N-1}$$
Il fattore (N − n)/(N − 1) è la correzione per popolazione finita: vale meno di 1 perché senza reinserimento la variabilità è minore.

Traccia tipo — appello del 19 Luglio 2025:
> Un'urna ha 4 palline bianche e 4 nere. Si estraggono 3 palline senza reinserimento. Sia X il numero di bianche estratte. Calcolare la probabilità che siano tutte dello stesso colore.

Il modello è ipergeometrico con N = 8, K = 4, n = 3. I due casi (tutte bianche, tutte nere) sono disgiunti e si sommano:
$$P(\{X=0\}\cup\{X=3\})=\frac{\dbinom{4}{0}\dbinom{4}{3}+\dbinom{4}{3}\dbinom{4}{0}}{\dbinom{8}{3}}=\frac{4+4}{56}=\frac{1}{7}$$
Le altre due domande dello stesso appello usano le altre formule del modello:
$$\operatorname{Var}[X]=3\cdot\tfrac{1}{2}\cdot\tfrac{1}{2}\cdot\tfrac{5}{7}=\frac{15}{28}$$
$$P(B_1\cap N_2\cap B_3)=\frac{4}{8}\cdot\frac{4}{7}\cdot\frac{3}{6}=\frac{1}{7}\quad(\text{sequenza ordinata, regola del prodotto})$$

---
#### Multinomiale / estrazione in blocco
Quando: più di due tipi di oggetto. Si sceglie quanti prenderne da ciascun tipo.

Densità (con reinserimento a sinistra, senza reinserimento o in blocco a destra):
$$P=\frac{n!}{k_1!\cdots k_m!}\,p_1^{k_1}\cdots p_m^{k_m}
\qquad\qquad
P=\frac{\dbinom{K_1}{k_1}\cdots\dbinom{K_m}{k_m}}{\dbinom{N}{n}}$$

Traccia tipo — appello del 7 Febbraio 2020:
> Un'urna ha 2 palline bianche, 2 gialle e 2 rosse. Si estraggono 3 palline senza reinserimento. Calcolare la probabilità di estrarre le due gialle; e quella di estrarre le due gialle e una rossa.

Tre tipi di oggetto, estrazione in blocco: si conta su tutti i modi di prendere 3 palline su 6.
$$P(\text{2 gialle})=\frac{\dbinom{2}{2}\dbinom{4}{1}}{\dbinom{6}{3}}=\frac{4}{20}=\frac{1}{5}$$
$$P(\text{2 gialle e 1 rossa})=\frac{\dbinom{2}{2}\dbinom{2}{1}\dbinom{2}{0}}{\dbinom{6}{3}}=\frac{2}{20}=\frac{1}{10}$$

---
#### Conteggio diretto
Quando: nessuna distribuzione notevole combacia. Si torna alla definizione di spazio uniforme e si elencano i casi favorevoli.
$$P(A)=\frac{|A|}{|\Omega|}$$

Traccia tipo — appello del 21 Febbraio 2020:
> Si lancia 3 volte un dado equo. Calcolare la probabilità che la somma dei tre numeri sia uguale a 4.

Lo spazio ha 6³ = 216 sequenze equiprobabili. La somma 4 esce solo da tre sequenze:
$$P(\text{somma}=4)=\frac{|\{(2,1,1),(1,2,1),(1,1,2)\}|}{6^{3}}=\frac{3}{216}=\frac{1}{72}$$

---
#### Condizionata dentro Es1
Quando: un evento noto restringe lo spazio campionario. Anche l'Es1 può contenerla.
$$P(E\mid F)=\frac{P(E\cap F)}{P(F)}$$
Se l'evento è contenuto nella condizione, l'intersezione si semplifica:
$$E\subset F\ \Rightarrow\ P(E\mid F)=\frac{P(E)}{P(F)}$$

Traccia tipo — appello del 21 Febbraio 2020, terza domanda:
> Sui 3 lanci di un dado: probabilità che esca la sequenza (2, 2, 2) sapendo di aver ottenuto 3 numeri pari.

La sequenza (2, 2, 2) è contenuta nell'evento "3 numeri pari", quindi l'intersezione è la sequenza stessa:
$$P\big((2,2,2)\mid \text{3 pari}\big)=\frac{(1/6)^{3}}{(1/2)^{3}}=\frac{8}{216}=\frac{1}{27}$$

---
#### Poisson — Pois(λ)
Quando: conteggi di eventi rari. Raro nell'Es1, ma la densità serve a memoria per Es1 ed Es3.
$$P(X=k)=\frac{\lambda^{k}}{k!}\,e^{-\lambda}$$
$$E[X]=\lambda\qquad\qquad \operatorname{Var}[X]=\lambda$$

---
#### Trappole ricorrenti
Reinserimento — decide la distribuzione:
- con reinserimento → binomiale, geometrica, binomiale negativa;
- senza reinserimento → ipergeometrica oppure catena di condizionate;
- in blocco (tutte insieme, senza ordine) → conteggio combinatorio con i coefficienti binomiali.

Traslata oppure no — l'errore che costa più punti:
$$\text{traslata: conta le prove, parte da } k=1,\quad E[X]=\frac{1}{p}$$
$$\text{non traslata: conta gli insuccessi, parte da } 0,\quad E[X]=\frac{1-p}{p}$$

Serie — l'unico vero punto d'errore è l'indice di partenza h; e attenzione che con esponente 2k la ragione della serie diventa r², non r.
### Es2 — Probabilità condizionata
Esperimento a due fasi: la prima fase sceglie lo scenario (urna, moneta, dado), la seconda produce l'evento osservato. Teoria in [[Es2 - Probabilità condizionata]].
#### Riconoscere il verso della domanda
| La traccia chiede… | Verso | Formula |
|---|---|---|
| la probabilità dell'evento (nessun «sapendo») | causa → effetto | Probabilità totali |
| la probabilità di uno scenario, «sapendo» l'evento | effetto → causa | Bayes |

---
#### Probabilità totali
Quando: si conosce cosa succede in ogni scenario e si vuole la probabilità complessiva dell'evento. Gli scenari $H_k$ formano una partizione (disgiunti, coprono tutto).
$$P(E)=\sum_{k=1}^{n}P(E|H_k)\,P(H_k)$$

Traccia tipo — appello del 6 Febbraio 2026:
> Due urne (2 bianche + 2 nere; 3 bianche + 3 nere). Si sceglie un'urna a caso e si estraggono due palline in blocco. Probabilità di due colori diversi.

Scenari $U_1,U_2$ con $P(U_1)=P(U_2)=\tfrac12$; le condizionate sono due conteggi in blocco (mini-Es1):
$$P(E|U_1)=\frac{\dbinom{2}{1}\dbinom{2}{1}}{\dbinom{4}{2}}=\frac{4}{6}\qquad P(E|U_2)=\frac{\dbinom{3}{1}\dbinom{3}{1}}{\dbinom{6}{2}}=\frac{9}{15}$$
$$P(E)=\frac{4}{6}\cdot\tfrac12+\frac{9}{15}\cdot\tfrac12=\frac{1}{3}+\frac{3}{10}=\frac{19}{30}$$

Tracce simili: monete truccate selezionate da un dado (19 Giugno 2026, risultato $\tfrac12$); due fasi con i dadi (20 Febbraio 2025, risultato $\tfrac29$); parametro simbolico «verificare che» (21 Giugno 2025).

---
#### Bayes
Quando: si osserva l'evento e si risale allo scenario (compare «sapendo» o «dato che»). Il denominatore di Bayes È la formula delle probabilità totali.
$$P(H_j|E)=\frac{P(E|H_j)\,P(H_j)}{\sum_{k=1}^{n}P(E|H_k)\,P(H_k)}$$

Traccia tipo — appello del 20 Febbraio 2026:
> Tre urne (4B+2N; 3B+3N; 2B+4N). Si sceglie un'urna a caso e si estrae una pallina. Probabilità di aver scelto la seconda urna sapendo di aver estratto una bianca.

Scenari $U_1,U_2,U_3$ con $P(U_k)=\tfrac13$; condizionate $P(B|U_1)=\tfrac46,\ P(B|U_2)=\tfrac36,\ P(B|U_3)=\tfrac26$:
$$P(U_2|B)=\frac{\tfrac36\cdot\tfrac13}{\tfrac46\cdot\tfrac13+\tfrac36\cdot\tfrac13+\tfrac26\cdot\tfrac13}=\frac{3}{4+3+2}=\frac{1}{3}$$
Il risultato coincide con $P(U_2)=\tfrac13$: l'osservazione non cambia la credenza, quindi $U_2$ e $B$ sono indipendenti. Se Bayes restituisce la probabilità a priori, è indipendenza, non un errore.

Tracce simili: Bayes con evento che cambia forma — «tutte teste» con due o una moneta (3 Febbraio 2025, risultato $\tfrac12$).

---
#### Regola del prodotto (sequenze ordinate)
Quando: una sequenza in ordine fissato, tipicamente senza reinserimento. Si moltiplicano le condizionate passo passo.
$$P(A_1\cap A_2\cap A_3)=P(A_1)\,P(A_2|A_1)\,P(A_3|A_1\cap A_2)$$

Esempio — sequenza $(B,N,B)$ da un'urna con 4 bianche e 4 nere senza reinserimento (a ogni passo il denominatore cala di 1):
$$P(B_1\cap N_2\cap B_3)=\frac{4}{8}\cdot\frac{4}{7}\cdot\frac{3}{6}=\frac{1}{7}$$

---
#### Trappole (Es2)
- Verso: $P(E|H)$ e $P(H|E)$ sono numeri diversi. «sapendo»/«dato che» → ciò che segue sta DOPO la barra.
- Condizionate dentro lo scenario: $P(B|U_2)$ si legge guardando solo la seconda urna, mai mescolando le urne.
- Partizione: gli scenari devono essere disgiunti e coprire tutto; controllo $\sum_k P(H_k)=1$.
- Pesi non uniformi: se il dado seleziona lo scenario, i pesi sono $\tfrac26,\tfrac46$, non $\tfrac12,\tfrac12$.
- Risultati «troppo puliti» ($\tfrac12$, oppure $P(H|E)=P(H)$): di solito corretti, segnalano simmetria o indipendenza.

### Es3 — Densità congiunta discreta
La traccia regala la densità congiunta $p_{X_1,X_2}$ di due variabili discrete e chiede di ricavarne qualcosa. Tutto si riduce a **sommare la densità sulle coppie giuste**. Teoria in [[Es3 - Densità congiunta discreta]].
$p_{X_1,X_2}(x_1,x_2)=P(X_1=x_1\text{ e }X_2=x_2)$ è una **tabella di pesi** (somma 1, vale 0 fuori dal supporto). **Quale richiesta?** barra $\mid$ → condizionata · "densità di $Y$" → trasformazione · "marginale" → sommi via una variabile · $P(\dots)$ senza barra → evento.
#### Principio unico e quattro richieste
Ogni domanda è un caso particolare della somma della densità sulle coppie dell'evento:
$$P\big((X_1,X_2)\in A\big)=\sum_{(x_1,x_2)\in A}p_{X_1,X_2}(x_1,x_2)$$
$$\text{Marginale:}\quad p_{X_1}(x_1)=\sum_{x_2}p_{X_1,X_2}(x_1,x_2)$$
$$\text{Condizionata:}\quad P(A|B)=\frac{P(A\cap B)}{P(B)}$$
$$\text{Densità di }Y=g(X_1,X_2):\quad p_Y(y)=\sum_{(x_1,x_2)\,:\,g(x_1,x_2)=y}p_{X_1,X_2}(x_1,x_2)$$
La densità vale **zero** fuori dal supporto: prima di sommare, individua quali coppie esistono.

---
#### Le due serie (e il cambio di indice)
$$\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda}\qquad\qquad \sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\ \ (|r|<1)$$
Una densità di Poisson o geometrica sommata su tutto il supporto fa **1**. Se la somma non parte da 0, si sostituisce l'indice: $\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}\overset{j=h-1}{=}\sum_{j\ge0}\frac{3^{j}}{j!}=e^{3}$ (non $e^{3}-1$).

---
#### Criteri rapidi
- **Fattorizzazione = indipendenza**: se $p_{X_1,X_2}(x_1,x_2)=f(x_1)\,g(x_2)$ su supporto rettangolare, $X_1$ e $X_2$ sono indipendenti e ogni marginale è il fattore corrispondente.
- **Prodotto nullo = unione**: $\{X_1X_2=0\}=\{X_1=0\}\cup\{X_2=0\}$; se non disgiunti, inclusione-esclusione $P(X_1=0)+P(X_2=0)-P(X_1=0,X_2=0)$.
- **Densità di $Y$**: elenca solo i valori raggiungibili; controllo $\sum_y p_Y(y)=1$.

---
#### Esempio svolto — marginale e coda (19 Giugno 2026)
> Densità $p_{X_1,X_2}(x_1,x_2)=(1-q^2)^{x_1}q^2\dfrac{\lambda^{x_2-x_1}}{(x_2-x_1)!}e^{-\lambda}$ per $x_2\ge x_1\ge0$. Calcolare $P(X_1\ge k)$.

Marginale di $X_1$: il fattore $(1-q^2)^{x_1}q^2$ non dipende da $x_2$ ed esce dalla somma; il resto, con $h=x_2-x_1$, è la serie esponenziale $=e^{\lambda}$:
$$p_{X_1}(x_1)=(1-q^2)^{x_1}q^2\,e^{-\lambda}\sum_{h\ge0}\frac{\lambda^{h}}{h!}=(1-q^2)^{x_1}q^2$$
È una geometrica di parametro $q^2$; la coda si somma con la serie geometrica:
$$P(X_1\ge k)=\sum_{x_1\ge k}(1-q^2)^{x_1}q^2=q^2\cdot\frac{(1-q^2)^{k}}{q^2}=(1-q^2)^{k}$$

---
#### Trappole (Es3)
- Sommare fuori dal supporto: le coppie non elencate valgono 0.
- Pezzi che si intersecano (diagonale + riga): la coppia comune, di solito $(0,0)$, va contata una sola volta.
- Cambio di indice nelle serie: $\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}=e^{3}$, non $e^{3}-1$.
- Valori non raggiungibili nella densità di $Y$: indica solo quelli veri, controlla che la somma faccia 1.

---
### Es4 — Trasformazione di variabile continua
Data la densità $f_X$ di $X$ continua, si chiede la funzione di distribuzione $F_Y$ di $Y=g(X)$ (metodo della funzione di ripartizione). Teoria in [[Es4 - Trasformazione di variabile continua]].
La richiesta **è** $F_Y(y)=P(Y\le y)$ (una funzione di $y$); il ponte per calcolarla è $P(Y\le y)=P(g(X)\le y)$, che riporta tutto a $X$ (di cui hai la densità). Isolare $X$ = trovare gli estremi dell'integrale.
#### Metodo — due mosse
Prima mossa: applica $g$ agli estremi del supporto di $X$ per trovare il supporto $[a,b]$ di $Y$, e scrivi lo scheletro a 3 casi (F_Y è definita su tutto $\mathbb{R}$):
$$F_Y(y)=\begin{cases}0 & y\le a\\ (*) & a<y<b\\ 1 & y\ge b\end{cases}$$
Seconda mossa: calcola $(*)$ solo nell'intervallo intermedio, isolando $X$ nella disuguaglianza e integrando:
$$(*)=P\big(g(X)\le y\big)=\int_{\{x\,:\,g(x)\le y\}}f_X(x)\,dx$$
Densità (se richiesta): $f_Y(y)=F_Y'(y)$ sull'intervallo intermedio, 0 fuori. Mediana: si risolve $F_Y(m)=\tfrac12$.

---
#### Isolare X — la condizione $g(X)\le y$
| $Y=g(X)$ | diventa | nota |
|---|---|---|
| $\sqrt{X}$ | $X\le y^{2}$ | $y>0$ |
| $X^{2}$ | $-\sqrt{y}\le X\le\sqrt{y}$ | non monotona → intervallo simmetrico |
| $\lvert X\rvert$ | $-y\le X\le y$ | non monotona → intervallo simmetrico |
| $e^{\beta X}$ | $X\le\frac{1}{\beta}\log y$ | $\beta>0$ |
| $-\log(X/b)$ | $X\ge be^{-y}$ | decrescente → **il verso si ribalta** |

---
#### Trappole
- **Decrescente**: la disuguaglianza si ribalta ($X\ge\dots$) e l'integrale cambia estremi.
- **Non monotona** ($X^{2}$, $\lvert X\rvert$): condizione simmetrica $-y\le X\le y$; se $f_X$ è a tratti, l'integrale si spezza sui sottointervalli.
- **Estremi dell'integrale**: si parte dall'estremo del supporto dove $f_X\ne0$, non da $-\infty$.
- **Costante di normalizzazione**: se $f_X$ è troncata (es. $\frac{e^{-x}}{1-e^{-b}}$ su $(0,b)$), è la costante che rende $\int f_X=1$; si trascina invariata fino alla fine.
- **Controllo**: $F_Y$ deve valere 1 all'estremo destro del supporto.

---
#### Esempio svolto — non monotona con densità a tratti (6 Febbraio 2026)
> $f_X(x)=\tfrac12$ su $(-1,0)$ e $f_X(x)=x$ su $(0,1)$. Trovare $F_Y$ per $Y=\lvert X\rvert$.

$X$ vive su $(-1,1)$, quindi $Y=\lvert X\rvert$ vive su $[0,1]$. Per $0<y<1$ la condizione $\lvert X\rvert\le y$ è $-y\le X\le y$; poiché $f_X$ è a tratti, l'integrale si spezza in $(-y,0)$ e $(0,y)$:
$$(*)=\int_{-y}^{0}\tfrac12\,dx+\int_{0}^{y}x\,dx=\frac{y}{2}+\frac{y^{2}}{2}=\frac{y+y^{2}}{2}$$
$$F_Y(y)=\begin{cases}0 & y\le0\\ \dfrac{y+y^{2}}{2} & 0<y<1\\ 1 & y\ge1\end{cases}$$
Controllo: $F_Y(1)=\frac{1+1}{2}=1$, coerente col fatto che $F_Y$ raggiunge 1 alla fine del supporto.

---
### Es5 — Speranza di variabile continua
Data una densità continua $f_X$ (spesso la stessa di Es4), si chiede una speranza, tipicamente $E[X^{2}]$ o $E[1/X^{2}]$. Teoria in [[Es5 - Speranza di variabile continua]].
$E[X]$ = media pesata dalla probabilità, un **numero** (non una funzione: la $x$ sparisce nell'integrale). La $g$ non si sceglie, è ciò che sta dentro $E[\cdots]$: $E[X^{2}]\Rightarrow g(x)=x^{2}$, $E[1/X^{2}]\Rightarrow g(x)=1/x^{2}$.
#### L'unica formula
$$E[g(X)]=\int_{-\infty}^{+\infty}g(x)\,f_X(x)\,dx=\int_{a}^{b}g(x)\,f_X(x)\,dx$$
Si integra **solo sul supporto** $(a,b)$: fuori $f_X=0$. Non serve passare per $f_Y$ (come in Es4): si integra direttamente $g\cdot f_X$. Casi frequenti: $g(x)=x,\ x^{2},\ \frac{1}{x^{2}},\ x^{r}e^{x}$.
**Errore concettuale**: $E[g(X)]\ne g(E[X])$ — es. $E[1/X^{2}]\ne 1/E[X]^{2}$; la differenza fra $E[X^{2}]$ e $(E[X])^{2}$ è la varianza.

---
#### Formule di appoggio
$$E[c_1X_1+c_2X_2]=c_1E[X_1]+c_2E[X_2]\qquad \operatorname{Var}[X]=E[X^{2}]-\big(E[X]\big)^{2}$$
$$\text{Uniforme }(a,b):\quad f_X=\tfrac{1}{b-a},\quad E[X]=\tfrac{a+b}{2},\quad \operatorname{Var}[X]=\tfrac{(b-a)^{2}}{12}$$
$$\int x^{n}\,dx=\frac{x^{n+1}}{n+1}\ (n\ne-1)\qquad \int\frac{1}{x^{2}}\,dx=-\frac{1}{x}\qquad \int e^{x}\,dx=e^{x}$$

---
#### Esempi svolti
$E[X^{2}]$ con densità triangolare $f_X=2(1-x)$ su $(0,1)$:
$$E[X^{2}]=\int_{0}^{1}x^{2}\,2(1-x)\,dx=2\left[\frac{x^{3}}{3}-\frac{x^{4}}{4}\right]_{0}^{1}=2\cdot\frac{1}{12}=\frac{1}{6}$$
$E[1/X^{2}]$ con $X\sim U(1,5)$ (densità $\tfrac14$, non 1):
$$E\!\left[\frac{1}{X^{2}}\right]=\frac14\int_{1}^{5}\frac{1}{x^{2}}\,dx=\frac14\left[-\frac{1}{x}\right]_{1}^{5}=\frac14\cdot\frac{4}{5}=\frac{1}{5}$$

---
#### Trappole
- **$E[g(X)]\ne g(E[X])$**: l'errore concettuale più grave (la differenza fra $E[X^{2}]$ e $(E[X])^{2}$ è la varianza).
- **Estremi**: si integra sul supporto $(a,b)$ dell'indicatrice, non su $\pm\infty$.
- **Costante di normalizzazione**: va moltiplicata, e spesso ricompare nel risultato finale.
- **Uniforme**: densità $\frac{1}{b-a}$, non 1.
- **Semplificazione**: se $g(x)f_X(x)$ non diventa un integrale elementare, ricontrolla l'impostazione — le tracce sono costruite perché si semplifichi (es. $e^{x}\cdot e^{-x}=1$).

---
### Es6 — Normale e teorema del limite centrale
Esprimere con $\Phi$ una probabilità sulla Normale o sulla somma standardizzata di v.a. i.i.d. (TLC). $\Phi$ è la funzione di distribuzione della Normale standard; la risposta resta in forma di $\Phi$ (niente tavole). Teoria in [[Es6 - Normale e teorema del limite centrale]].
$\Phi(z)=P(Z\le z)$ (coda sinistra della standard). **Standardizzare** = $Z=\frac{X-\mu}{\sigma}$ (centra e riscala). $\sigma=\sqrt{\text{varianza}}$: la traccia dà la varianza, a te serve $\sigma$.
#### Due situazioni
| Traccia | Metodo | Risultato |
|---|---|---|
| $X$ è già Normale$(\mu,\sigma^{2})$ | standardizzare | uguaglianza **esatta** ($=$) |
| $X_i$ i.i.d., somma di tante ($n$ grande, $\lim$, «i.i.d.») | TLC | **approssimazione** ($\approx$) |
#### Le formule
$$P(X\le a)=\Phi\!\left(\frac{a-\mu}{\sigma}\right)\qquad P(a<X<b)=\Phi\!\left(\frac{b-\mu}{\sigma}\right)-\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$
$$\text{TLC:}\quad P(S_n\le s)\approx\Phi\!\left(\frac{s-n\mu}{\sigma\sqrt{n}}\right)\quad\text{con } S_n=X_1+\cdots+X_n$$
$$\Phi(-x)=1-\Phi(x)\qquad\qquad P(Z>z)=1-\Phi(z)$$
$$aX_1+bX_2\sim N\big(a\mu_1+b\mu_2,\ a^{2}\sigma_1^{2}+b^{2}\sigma_2^{2}\big)\quad(\text{Normali indipendenti})$$
La somma $S_n$ ha media $n\mu$ e deviazione standard $\sigma\sqrt{n}$ (non $\sigma^{2}\sqrt{n}$).

---
#### Momenti in ingresso (se la traccia dà la distribuzione)
- Uniforme $(a,b)$: $\mu=\tfrac{a+b}{2}$, $\sigma^{2}=\tfrac{(b-a)^{2}}{12}$
- Esponenziale $(\lambda)$: $\mu=\tfrac{1}{\lambda}$, $\sigma^{2}=\tfrac{1}{\lambda^{2}}$
- Discrete (Bernoulli, binomiale, Poisson, geometrica): tabella in [[Es1 - Probabilità discreta elementare|Es1]]

---
#### Esempio svolto — intervallo con TLC e argomenti positivi (20 Febbraio 2026)
> $X_1,\dots,X_{900}$ i.i.d. media 1, varianza 100. Calcolare $P(700<S_{900}<800)$ con $\Phi$ ad argomenti positivi.

$\sigma=\sqrt{100}=10$, media $n\mu=900$, deviazione standard $\sigma\sqrt{n}=10\cdot30=300$. Si sottrae 900 e si divide per 300 a **tutti** i membri:
$$P(700<S_{900}<800)\approx P\!\left(-\tfrac{2}{3}<Z<-\tfrac{1}{3}\right)=\Phi\!\left(-\tfrac13\right)-\Phi\!\left(-\tfrac23\right)=\Phi\!\left(\tfrac23\right)-\Phi\!\left(\tfrac13\right)$$
Agli argomenti positivi i due termini si **scambiano**; il risultato resta positivo (è il controllo).

---
#### Trappole
- **$\sigma=\sqrt{\text{varianza}}$**: la traccia dà la varianza, non $\sigma$. «varianza 9» → $\sigma=3$, «varianza 100» → $\sigma=10$.
- **Denominatore TLC** $\sigma\sqrt{n}$, **non** $\sigma^{2}\sqrt{n}$ né $\sigma n$.
- **$=$ contro $\approx$**: Normale esatta → $=$; TLC → $\approx$ (mai $=$, tranne nei $\lim$).
- **Argomenti positivi**: con $\Phi(-x)=1-\Phi(x)$, in un intervallo i due termini si scambiano; a cavallo dello zero la differenza diventa una **somma meno 1**: $\Phi(b)-\Phi(-a)=\Phi(b)+\Phi(a)-1$.
- **$\Phi$ è coda sinistra**: $P(Z>z)=1-\Phi(z)$.
