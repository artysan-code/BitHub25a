# Distribuzione binomiale negativa
Generalizzazione della [[Distribuzione geometrica|geometrica]] al "successo $r$-simo": densità discreta, versione traslata e recupero della geometrica per $r=1$.
## Impostazione
Vogliamo considerare una generalizzazione di quel che abbiamo visto per la [[Distribuzione geometrica|geometrica (e la geometrica traslata)]] facendo riferimento al "successo $r$-simo", dove $r\geq 1$ è un intero fissato. Nel caso $r=1$ si dovrà recuperare quel che abbiamo visto, come caso particolare.
Quindi consideriamo ancora una successione di prove indipendenti con probabilità di successo $p\in(0,1]$ e di fallimento $1-p\in[0,1)$. Siamo interessati alle due seguenti v.a.: $$\begin{cases}
X=\#\text{ fallimenti prima di avere il successo }r\text{-simo} & (\text{è a valori in }\{0,1,2,\dots\}) \\
Y=\#\text{ prove per avere il successo }r\text{-simo} & (\text{è a valori in }\{r,r+1,r+2,\dots\})
\end{cases}$$In analogia a quanto visto in passato, si ha $X=Y-r$ e $Y=X+r$.
### Esempio specifico con $r=4$
$$\underset{\substack{\uparrow \\ 1°\text{ succ.}}}{S}\ F\ F\ F\ \underset{\substack{\uparrow \\ 2°\text{ succ.}}}{S}\ \underset{\substack{\uparrow \\ 3°\text{ succ.}}}{S}\ F\ F\ F\ F\ \underset{\substack{\uparrow \\ 4°\text{ succ.}}}{S}$$Abbiamo 7 simboli "$F$" e 11 simboli in totale. Quindi si ha $X=7$ e $Y=11$ (questi valori sono in accordo con $X=Y-r$ e $Y=X+r$, dove $r=4$).
### Terminologia
$$\begin{cases}
X\text{ ha distribuzione \textbf{binomiale negativa} con parametri }r\text{ e }p & (X\sim BIN\text{-}NEG(r,p)) \\
Y\text{ ha distribuzione \textbf{binomiale negativa traslata} con parametri }r\text{ e }p & (Y\sim BIN\text{-}NEG\text{-}traslata(r,p))
\end{cases}$$
> [!warning] Attenzione ai libri
> In altri libri le terminologie potrebbero essere scambiate (stessa avvertenza già vista per la [[Distribuzione geometrica#Terminologia|geometrica]]). Per evitare ambiguità possiamo distinguere i due casi con riferimento al fatto che **$X$ parte da zero** e **$Y$ parte da $r$**.

### Osservazioni sui casi limite
- Il caso $p=0$ si esclude per i motivi visti nel caso della geometrica e della geometrica traslata (in generale si avrà certamente fallimento in ogni prova, e quindi non si arriverà mai al successo $r$-simo).
- Il caso $p=1$ è consentito ma è banale. Infatti si avrà certamente successo in ogni prova, e quindi $P(X=0)=1$ e $P(Y=r)=1$: $$\underset{r\text{ volte}}{\underbrace{S,\dots,S}}\quad\quad\begin{array}{l}
X=0\text{ perché non c'è nessuna }F \\
Y=r\text{ perché la "stringa" ha }r\text{ simboli in totale}
\end{array}$$
## Calcolo delle densità discrete di $X$ e $Y$
Iniziamo da $P_{X}(k)=P(X=k)$ per $k\geq 0$ intero.
Consideriamo la sequenza $(\underset{k\text{ volte}}{\underbrace{F,\dots,F}},\underset{r\text{ volte}}{\underbrace{S,\dots,S}})$; è un caso particolare dell'evento che ci interessa. Per indipendenza delle prove la probabilità di questa sequenza è $p^{r}(1-p)^{k}$.
Ci si convince che ogni altra sequenza con $k$ volte "$F$" e $r$ volte "$S$" ha la stessa probabilità. Quindi $$P_{X}(k)=\underset{b_{r,k}\text{ volte}}{\underbrace{p^{r}(1-p)^{k}+\dots+p^{r}(1-p)^{k}}}=b_{r,k}\,p^{r}(1-p)^{k}\quad\quad(\forall\ k\geq 0\text{ intero})$$dove $b_{r,k}=\#$ sequenze con $k$ volte "$F$" e $r$ volte "$S$", **e che finiscono con "$S$"**.
> [!info] Perché "che finiscono con S"
> L'evento $\{X=k\}$ richiede che il successo $r$-simo cada esattamente all'ultima prova: se la sequenza finisse con $F$, il successo $r$-simo si sarebbe già verificato prima e i fallimenti contati non sarebbero quelli "prima del successo $r$-simo".

### Calcolo di $b_{r,k}$
Consideriamo la seguente corrispondenza biunivoca: $$\left\{ \begin{array}{l}
\text{stringhe con }k\text{ volte "}F\text{" e }r\text{ volte "}S\text{"} \\
\text{che finiscono con "}S\text{"}
\end{array} \right\}\quad\longleftrightarrow\quad\left\{ \begin{array}{l}
\text{i sottoinsiemi di }\{1,\dots,k+r-1\}\text{ con }r-1 \\
\text{elementi, che indicano i posti delle "}S\text{"} \\
(\text{esclusa l'ultima "}S\text{"})
\end{array} \right\}$$Infatti una stringa di questo tipo si scrive come $$(\underbrace{-,-,\ \dots\ ,-}_{k+r-1\text{ simboli, di cui }k\text{ volte "}F\text{" e }r-1\text{ volte "}S\text{"}},S)$$e il secondo insieme ha $\binom{k+r-1}{r-1}$ elementi. Quindi $$b_{r,k}=\binom{k+r-1}{r-1}=\binom{k+r-1}{k}$$dove l'ultima uguaglianza vale per le proprietà dei coefficienti binomiali.
In conclusione $$\begin{bmatrix}
P_{X}(k)=\binom{k+r-1}{r-1}p^{r}(1-p)^{k}=\binom{k+r-1}{k}p^{r}(1-p)^{k}\quad\quad\forall\ k\geq 0\text{ intero}
\end{bmatrix}$$
### Esempio della corrispondenza biunivoca
Prendiamo $r=3$ e $k=2$; allora $k+r-1=2+3-1=4$ e $r-1=2$: $$\begin{array}{lcl}
\text{sequenze con 2 volte "}F\text{" e 3 volte "}S\text{" che finiscono con "}S\text{"} &  & \text{sottoinsiemi} \\
(F,F,S,S,S) & \longleftrightarrow & \{3,4\} \\
(F,S,F,S,S) & \longleftrightarrow & \{2,4\} \\
(F,S,S,F,S) & \longleftrightarrow & \{2,3\} \\
(S,F,F,S,S) & \longleftrightarrow & \{1,4\} \\
(S,F,S,F,S) & \longleftrightarrow & \{1,3\} \\
(S,S,F,F,S) & \longleftrightarrow & \{1,2\}
\end{array}$$e in effetti si hanno 6 elementi, in accordo con $\binom{k+r-1}{r-1}=\binom{4}{2}=6$ e $\binom{k+r-1}{k}=\binom{4}{2}=6$.
### Densità discreta di $Y$
La densità discreta di $Y$ si può ottenere con un ragionamento simile, oppure a partire dalla densità discreta di $X$ (questo è quello che facciamo di seguito). Per ogni $h\geq r$ intero (si osservi che $h-r\geq 0$ è intero) $$\begin{array}{ll}
P_{Y}(h)=P(Y=h)=P(X+r=h)=P(X=h-r)=P_{X}(h-r) & \overset{(*)}{=}\binom{(h-r)+r-1}{r-1}p^{r}(1-p)^{h-r}=\binom{h-1}{r-1}p^{r}(1-p)^{h-r} \\
 & \overset{(*)}{=}\binom{(h-r)+r-1}{h-r}p^{r}(1-p)^{h-r}=\binom{h-1}{h-r}p^{r}(1-p)^{h-r}
\end{array}$$dove in $(*)$ si è usata la formula ottenuta prima con $k=h-r$. Quindi $$\begin{bmatrix}
P_{Y}(h)=\binom{h-1}{r-1}p^{r}(1-p)^{h-r}=\binom{h-1}{h-r}p^{r}(1-p)^{h-r}\quad\quad\forall\ h\geq r\text{ intero}
\end{bmatrix}$$
#### Commento
Si può verificare che $\displaystyle\sum_{k=0}^{\infty}P_{X}(k)=1$ e $\displaystyle\sum_{h=r}^{\infty}P_{Y}(h)=1$. Il prof non dà dettagli su come si verificano.
## Caso $r=1$: recupero della geometrica e della geometrica traslata
$$\begin{array}{l|l}
\text{Per ogni }k\geq 0\text{ intero} & \text{Per }h\geq 1\text{ intero} \\
P_{X}(k)=\binom{k+1-1}{1-1}p^{1}(1-p)^{k}=(1-p)^{k}p & P_{Y}(h)=\binom{h-1}{1-1}p^{1}(1-p)^{h-1}=(1-p)^{h-1}p \\
\text{oppure} & \text{oppure} \\
P_{X}(k)=\binom{k+1-1}{k}p^{1}(1-p)^{k}=(1-p)^{k}p & P_{Y}(h)=\binom{h-1}{h-1}p^{1}(1-p)^{h-1}=(1-p)^{h-1}p
\end{array}$$Si ritrovano esattamente le densità di [[Distribuzione geometrica#Calcolo delle densità discrete di $X$ e $Y$|$Geo(p)$ e $GeoTraslata(p)$]], come ci si aspettava.
> [!info] Esercizi della lezione 09
> Le pp. 9–20 della lezione 09 contengono esercizi sulla binomiale negativa. Sono esercizi puri: la loro sede è la cartella `Esercizi/`.

--- Fine parte sulla binomiale negativa (lezione 09, pp. 1-20) ---
La lezione 09 prosegue a p. 21 con un argomento nuovo: le [[Variabili aleatorie multidimensionali discrete|variabili aleatorie multidimensionali]].
## Un legame tra binomiale negativa (traslata) e geometrica (traslata)
> [!info] Ripreso nella lezione 12 (pp. 9-10)
> Questa sezione arriva più avanti nel corso, dopo aver introdotto le [[Trasformazioni e somme di variabili aleatorie discrete|somme di v.a. indipendenti]]; è raccolta qui perché tematicamente appartiene alla binomiale negativa.

Consideriamo lo schema della binomiale negativa (traslata), con $$\begin{array}{l}
X=\#\text{ fallimenti prima del successo }r\text{-simo} \\
Y=\#\text{ prove per avere il successo }r\text{-simo}
\end{array}$$Possiamo considerare le v.a. "a blocchi": $$\begin{array}{ll}
X_{i}=\#\text{ fallimenti tra il successo }(i-1)°\text{ e il successo }i° & i=1,\dots,r \\
Y_{i}=\#\text{ prove dopo il successo }(i-1)°\text{ per avere il successo }i° & i=1,\dots,r
\end{array}$$Quindi $$\begin{cases}
Y_{1}+\dots+Y_{r}=Y \\
Y_{i}=X_{i}+1\iff X_{i}=Y_{i}-1 \\
X_{1}+\dots+X_{r}=X
\end{cases}$$
### Esempio ($r=4$)
$$F\ S\ F\ F\ F\ S\ S\ F\ F\ S\quad\quad\text{con }X=6\text{ e }Y=10$$Nel caso dell'esempio si ha $$\begin{array}{lll}
X_{1}=1,\ X_{2}=3,\ X_{3}=0,\ X_{4}=2 & \longrightarrow & \text{somma}=6\quad\text{ok} \\
Y_{1}=2,\ Y_{2}=4,\ Y_{3}=1,\ Y_{4}=3 & \longrightarrow & \text{somma}=10\quad\text{ok}
\end{array}$$
### Il risultato
Allora: $$\begin{array}{ll}
Y=Y_{1}+\dots+Y_{r} & \text{e si può dimostrare che }Y_{1},\dots,Y_{r}\text{ sono indipendenti }GeoTraslata(p) \\
X=X_{1}+\dots+X_{r} & \text{e si può dimostrare che }X_{1},\dots,X_{r}\text{ sono indipendenti }Geo(p)
\end{array}$$
> [!quote] In sintesi
> Una binomiale negativa (traslata) di parametri $r$ e $p$ è la **somma di $r$ geometriche (traslate) indipendenti** di parametro $p$. È coerente con la [[Distribuzione geometrica#Proprietà della "mancanza di memoria"|mancanza di memoria]]: dopo ogni successo il conteggio "riparte da zero".

### Rivisitazione di un esercizio fatto in passato
Avevamo dimostrato che $$P(Y_{1}=k|Y_{1}+Y_{2}=n)=\frac{1}{n-1}\quad\quad\text{per }k\in\{1,\dots,n-1\}\text{ con }n\geq 2$$Ora recuperiamo questo risultato tenendo conto di quanto detto qui: essendo $Y_{1},Y_{2}$ indipendenti $GeoTraslata(p)$, la somma $Y_{1}+Y_{2}$ è una $BIN\text{-}NEG\text{-}traslata(r=2,p)$ e quindi $P(Y_{1}+Y_{2}=n)=\binom{n-1}{2-1}p^{2}(1-p)^{n-2}=(n-1)p^{2}(1-p)^{n-2}$. Allora $$\begin{array}{ll}
P(Y_{1}=k|Y_{1}+Y_{2}=n) & =\frac{P(\{Y_{1}=k\}\cap\{Y_{1}+Y_{2}=n\})}{P(Y_{1}+Y_{2}=n)}=\frac{P(\{Y_{1}=k\}\cap\{Y_{2}=n-k\})}{\binom{n-1}{2-1}p^{2}(1-p)^{n-2}}\underset{\text{indip.}}{=}\frac{P(Y_{1}=k)P(Y_{2}=n-k)}{(n-1)p^{2}(1-p)^{n-2}} \\
 & =\frac{(1-p)^{k-1}\cancel{p}(1-p)^{n-k-1}\cancel{p}}{(n-1)\cancel{p^{2}}(1-p)^{n-2}}=\frac{\cancel{(1-p)^{n-2}}}{(n-1)\cancel{(1-p)^{n-2}}}=\frac{1}{n-1}
\end{array}$$in accordo con quanto già dimostrato.

---
Nota precedente: [[Distribuzione geometrica]]. Nota successiva: [[Variabili aleatorie multidimensionali discrete]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
