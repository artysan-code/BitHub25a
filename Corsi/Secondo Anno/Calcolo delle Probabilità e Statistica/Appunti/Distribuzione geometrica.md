# Distribuzione geometrica
Distribuzione geometrica e geometrica traslata: densità, formula per la coda, mancanza di memoria.
### Distribuzione geometrica (e distribuzione geometrica traslata)
Supponiamo di avere una **successione** di prove indipendenti, tutte con probabilità di successo $p\in(0,1]$. Siamo interessati all'istante del "1° successo" e, per questo motivo, escludiamo il caso $p=0$.
Consideriamo le seguenti v.a.: $$\begin{array}{ll}
X=\#\text{ fallimenti prima del "1° successo"} & (\text{assume valori in }\{0,1,2,\dots\}) \\
Y=\#\text{ prove per avere il "1° successo"} & (\text{assume valori in }\{1,2,3,\dots\})
\end{array}$$Queste v.a. sono legate tra loro perché $Y=X+1$ e $X=Y-1$.
#### Esempio
Se si ha la sequenza di risultati $F,F,S,\dots$ si verificano gli eventi $\{X=2\}$ e $\{Y=3\}$.
#### Terminologia
Si considera la seguente terminologia: $$\begin{array}{l}
X\text{ ha distribuzione \textbf{geometrica} di parametro }p \\
Y\text{ ha distribuzione \textbf{geometrica traslata} di parametro }p
\end{array}$$(in simboli scriveremo $X\sim Geo(p)$ e $Y\sim GeoTraslata(p)$).
> [!warning] Attenzione ai libri
> In alcuni libri la terminologia delle due distribuzioni è **scambiata**, e quella usata in questo corso è in minoranza. Comunque, per non confonderci, si potrebbe dire che:
> - $X$ ha distribuzione geometrica "che parte da zero" (di parametro $p$);
> - $Y$ ha distribuzione geometrica "che parte da uno" (di parametro $p$).
#### Osservazioni sui casi limite
- Abbiamo detto che si esclude il caso $p=0$: infatti non si avrebbe mai il "1° successo" perché si avrebbe **sempre fallimento**. Per aggirare il problema si potrebbe considerare questa situazione: $$\begin{array}{ll}
X:\ohm\to \mathbb{R}\cup\{\infty\}\ (\text{anziché }X:\ohm\to \mathbb{R}) & \text{e}\quad P(X=\infty)=1 \\
Y:\ohm\to \mathbb{R}\cup\{\infty\}\ (\text{anziché }Y:\ohm\to \mathbb{R}) & \text{e}\quad P(Y=\infty)=1
\end{array}$$
- Nel caso $p=1$ non ci sono problemi; però possiamo dire che abbiamo **sempre successo** e quindi $P(X=0)=1$ e $P(Y=1)=1$.
#### Calcolo delle densità discrete di $X$ e $Y$
- Per $k\geq 0$ intero si ha $$P_{X}(k)=P(\underset{k\text{ volte}}{\underbrace{F\dots F}}S)=\underset{k\text{ volte}}{\underbrace{(1-p)\cdot\dots\cdot(1-p)}}\cdot p=\begin{bmatrix}
(1-p)^{k}p
\end{bmatrix}$$(per indipendenza delle prove; vale banalmente anche per $k=0$).
- Per $h\geq 1$ intero si ha $$P_{Y}(h)=P(\underset{h-1\text{ volte}}{\underbrace{F\dots F}}S)=\underset{h-1\text{ volte}}{\underbrace{(1-p)\cdot\dots\cdot(1-p)}}\cdot p=\begin{bmatrix}
(1-p)^{h-1}p
\end{bmatrix}$$(vale banalmente anche per $h=1$), oppure, a partire da $P_{X}$, $$P_{Y}(h)=P(Y=h)=P(Y-1=h-1)=P(X=h-1)=P_{X}(h-1)=(1-p)^{h-1}p$$(essendo $h\geq 1$, si ha $h-1\geq 0$).
#### Osservazione (spiegazione del termine "geometrica")
Il rapporto tra due valori consecutivi della densità è costante, come nelle progressioni geometriche: $$\begin{array}{ll}
\text{per }k\geq 0\text{ intero} & \frac{P_{X}(k+1)}{P_{X}(k)}=\frac{(1-p)^{k+1}p}{(1-p)^{k}p}=1-p\quad\text{costante rispetto a }k \\
\text{per }h\geq 1\text{ intero} & \frac{P_{Y}(h+1)}{P_{Y}(h)}=\frac{(1-p)^{h+1-1}p}{(1-p)^{h-1}p}=1-p\quad\text{costante rispetto ad }h
\end{array}$$
### Formula della serie geometrica
Per ogni $h\geq 0$ intero e per ogni $r$ tale che $|r|<1$ (cioè $-1<r<1$) si ha $$\begin{bmatrix}
\displaystyle\sum_{k=h}^{\infty}r^{k}=\frac{r^{h}}{1-r}
\end{bmatrix}$$(spesso la useremo per $0\leq r<1$).
#### Dimostrazione
Si ha $$\sum_{k=h}^{\infty}r^{k}=r^{h}+r^{h+1}+r^{h+2}+\dots\overset{(*)}{=}r^{h}(1+r+r^{2}+\dots)=?$$Inoltre si ha $1-r^{k}=(1-r)(1+r+r^{2}+\dots+r^{k-1})$ (basta fare i prodotti a secondo membro), da cui segue $$1+r+r^{2}+\dots+r^{k-1}=\frac{1-r^{k}}{1-r}\quad\underset{k\to\infty}{\longrightarrow}\quad \frac{1}{1-r}\quad\text{perché }|r|<1$$Allora, poiché la serie è il limite delle somme parziali, si ha $$\sum_{k=h}^{\infty}r^{k}\overset{(*)}{=}r^{h}\lim_{k\to\infty}(1+\dots+r^{k-1})=r^{h}\cdot \frac{1}{1-r}=\frac{r^{h}}{1-r}\qquad\Box$$
### Formula per la "coda" di una v.a. geometrica (e per la traslata)
- Sia $X\sim Geo(p)$. Allora, per $j\geq 0$, si ha (formula della serie geometrica con $r=1-p$) $$P(X\geq j)=\sum_{k=j}^{\infty}P_{X}(k)=\sum_{k=j}^{\infty}(1-p)^{k}p=p\sum_{k=j}^{\infty}(1-p)^{k}=\cancel{p}\ \frac{(1-p)^{j}}{1-(1-p)}=\cancel{p}\ \frac{(1-p)^{j}}{\cancel{p}}=\begin{bmatrix}
(1-p)^{j}
\end{bmatrix}$$   **Osservazione.** In particolare (per $j=0$) $P(X\geq 0)=(1-p)^{0}=1$, in accordo con quanto ci si aspetta dalla teoria.
- Sia $Y\sim GeoTraslata(p)$. Allora, per $j\geq 1$, si ha $$P(Y\geq j)=\sum_{h=j}^{\infty}P_{Y}(h)=\sum_{h=j}^{\infty}(1-p)^{h-1}p=\frac{p}{1-p}\sum_{h=j}^{\infty}(1-p)^{h}=\frac{\cancel{p}}{1-p}\cdot \frac{(1-p)^{j}}{\cancel{p}}=\begin{bmatrix}
(1-p)^{j-1}
\end{bmatrix}$$   **Osservazione.** In particolare (per $j=1$) $P(Y\geq 1)=(1-p)^{1-1}=(1-p)^{0}=1$, in accordo con quanto ci si aspetta e con la teoria.
### Proprietà della "mancanza di memoria"
Per ogni $k,h\geq 0$ interi si ha $$\begin{bmatrix}
P(X=k+h|X\geq h)=P(X=k)
\end{bmatrix}$$
> [!info] Commento
> Sapendo di aver avuto $h$ fallimenti, la probabilità di avere altri $k$ fallimenti prima del 1° successo è la stessa di avere $k$ fallimenti prima del 1° successo partendo dall'inizio (cioè **senza condizionare**).
#### Dimostrazione
$$P(X=k+h|X\geq h)=\frac{P(\{X=k+h\}\cap\{X\geq h\})}{P(X\geq h)}\underset{\{X=k+h\}\subset\{X\geq h\}}{=}\frac{P(X=k+h)}{P(X\geq h)}\overset{(\star)}{=}\frac{(1-p)^{k+h}p}{(1-p)^{h}}=(1-p)^{k}p=P(X=k)\qquad\Box$$dove in $(\star)$ si è usata al denominatore la formula per la coda vista prima.
#### Commenti
- La proprietà di mancanza di memoria mette in guardia dalle teorie sui **numeri ritardatari** per le estrazioni dei numeri al lotto.
- Si può dimostrare che, se $X$ è una v.a. a valori in $\{0,1,2,3,\dots\}$ e soddisfa la proprietà di mancanza di memoria, allora $X$ ha distribuzione geometrica (è quindi una **caratterizzazione**).
- Si può dare un enunciato analogo per la v.a. $Y$. Infatti, per $k,h\geq 1$ interi, si ha $$P(Y=k+h|Y>h)=\frac{P(\{Y=k+h\}\cap\{Y>h\})}{P(Y>h)}\underset{\{Y=k+h\}\subset\{Y>h\}}{=}\frac{P(Y=k+h)}{P(Y\geq h+1)}=\frac{(1-p)^{k+h-1}p}{(1-p)^{h+1-1}}=(1-p)^{k-1}p=P(Y=k)$$
> [!info] Esercizi conclusivi della lezione 08
> Le pp. 13–21 della lezione 08 contengono tre esercizi sulla geometrica traslata (lanci ripetuti di un dado equo; urna con 5 palline numerate; lanci ripetuti di due dadi equi), risolti con la formula per la coda e con la somma di serie geometriche su sottoinsiemi di indici (numeri pari, dispari, multipli di 3). Sono esercizi puri: la loro sede è la cartella `Esercizi/`.

--- Fine lezione 08 ---

---
Nota precedente: [[Distribuzioni uniforme discreta e di Poisson]]. Nota successiva: [[Distribuzione binomiale negativa]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
