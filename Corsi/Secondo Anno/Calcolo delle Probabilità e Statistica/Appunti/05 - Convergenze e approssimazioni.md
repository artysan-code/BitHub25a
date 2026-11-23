# Convergenze e approssimazioni
Appunti sul **Capitolo 5** del corso (lezione 22, più gli esercizi sul teorema del limite centrale e sulla correzione di continuità della lezione 24, pp. 21-29 del PDF): il comportamento della somma/media di tante v.a. i.i.d. al crescere di $n$. Sezioni:
1. [[05 - Convergenze e approssimazioni#Legge dei grandi numeri|Legge dei grandi numeri]] — legge debole e forte: la media campionaria $\overline{X}_{n}$ si concentra sulla media $\mu$.
2. [[05 - Convergenze e approssimazioni#Teorema del limite centrale|Teorema del limite centrale]] — la somma standardizzata di v.a. i.i.d. tende a $N(0,1)$ (materia dell'[[06 - Normale e teorema del limite centrale|esercizio 6 dello scritto]]).
3. [[05 - Convergenze e approssimazioni#Approssimazione Normale e correzione di continuità|Approssimazione Normale e correzione di continuità]] — uso pratico del TLC, con la correzione per v.a. a valori interi.
## Nota sulla struttura
Blocco successivo a [[04 - Modelli continui]]. È il **Capitolo 5** del corso. I marcatori `--- Fine lezione NN ---` conservano la corrispondenza con i PDF delle lezioni in `Materiale Didattico/Slide/6 CFU/`.
## Legge dei grandi numeri
Per una successione di v.a. i.i.d., la media aritmetica delle prime $n$ variabili si concentra sulla media comune $\mu$.
### La media campionaria
Sia $\{X_{n}:n\geq 1\}$ una successione di v.a. **i.i.d.** (indipendenti e identicamente distribuite). Si pone $$\overline{X}_{n}=\frac{X_{1}+\dots+X_{n}}{n}$$(la **media aritmetica** delle prime $n$ v.a.; notazione usata anche nel seguito).
### Enunciato

> [!quote] Legge dei grandi numeri (legge debole)
> Sia $\{X_{n}:n\geq 1\}$ i.i.d. con **speranza matematica finita** (media comune $\mu$). Allora $$\begin{bmatrix}\lim_{n\to\infty}P\big(|\overline{X}_{n}-\mu|\geq\varepsilon\big)=0\qquad\forall\varepsilon>0\end{bmatrix}$$

> [!info] Legge forte (stesse ipotesi)
> Vale la versione **forte**: $P\big(\{\omega\in\Omega:\lim_{n\to\infty}\overline{X}_{n}(\omega)=\mu\}\big)=1$ (si dimostra che quel sottoinsieme di $\Omega$ è un evento; va oltre gli scopi del corso).

Anche per $\varepsilon>0$ piccolissimo, la probabilità che $\overline{X}_{n}$ cada **fuori** da $(\mu-\varepsilon,\mu+\varepsilon)$ tende a $0$: all'aumentare di $n$ la media campionaria si concentra attorno a $\mu$.
### Dimostrazione (con varianza finita)
Aggiungiamo l'ipotesi di **varianza finita** $\sigma^{2}$. Allora $$\mathbb{E}[\overline{X}_{n}]=\frac{n\mu}{n}=\mu\qquad \text{Var}[\overline{X}_{n}]=\frac{1}{n^{2}}\,\text{Var}[X_{1}+\dots+X_{n}]\overset{\text{indip.}}{=}\frac{1}{n^{2}}\,n\sigma^{2}=\frac{\sigma^{2}}{n}$$Applicando la [[03 - Speranza matematica e momenti#Disuguaglianza di Chebyshev|disuguaglianza di Chebyshev]] a $\overline{X}_{n}$: $$0\leq P\big(|\overline{X}_{n}-\mu|\geq\varepsilon\big)\leq \frac{\text{Var}[\overline{X}_{n}]}{\varepsilon^{2}}=\frac{\sigma^{2}}{n\varepsilon^{2}}\xrightarrow[n\to\infty]{}0$$e per il teorema del confronto si conclude. $\Box$
### Esercizi tipici

> [!example] Media dei lanci di un dado
> $X_{n}=$ numero uscito all'$n$-simo lancio di un dado equo. Il $\mu$ cercato è la media comune: $\mu=\sum_{k=1}^{6}k\cdot\frac{1}{6}=\frac{21}{6}=\frac{7}{2}$.

> [!example] Processo di Poisson
> Per un [[04 - Modelli continui#Il processo di Poisson|processo di Poisson]] di intensità $\lambda$, con $T_{n}=S_{1}+\dots+S_{n}$ e $\{S_{m}\}$ i.i.d. $\sim Exp(\lambda)$: poiché $\frac{T_{n}}{n}=\overline{S}_{n}$, il $\mu$ è $\mathbb{E}[S_{m}]=\frac{1}{\lambda}$.

> [!question] Domanda tipica d'esame
> Enunciare la legge debole dei grandi numeri e dimostrarla con varianza finita.
> **Risposta.** Per $\{X_{n}\}$ i.i.d. con media $\mu$ finita, $\lim_{n}P(|\overline{X}_{n}-\mu|\geq\varepsilon)=0$ per ogni $\varepsilon>0$. Con varianza $\sigma^{2}$ finita: $\mathbb{E}[\overline{X}_{n}]=\mu$, $\text{Var}[\overline{X}_{n}]=\frac{\sigma^{2}}{n}$, e per Chebyshev $0\leq P(|\overline{X}_{n}-\mu|\geq\varepsilon)\leq\frac{\sigma^{2}}{n\varepsilon^{2}}\to0$.

--- Fine parte sulla legge dei grandi numeri (lezione 22) ---
## Teorema del limite centrale
La somma standardizzata di $n$ v.a. i.i.d. tende alla Normale standard.
### Enunciato

> [!quote] Teorema del limite centrale
> Sia $\{X_{n}:n\geq 1\}$ i.i.d. con media $\mu$ finita e varianza $\sigma^{2}$ **finita e $>0$** (quindi non costanti). Allora $$\begin{bmatrix}\lim_{n\to\infty}P\left( \frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}\leq x \right)=\Phi(x)\qquad\forall x\in \mathbb{R}\end{bmatrix}$$(la disuguaglianza può essere anche stretta).

> [!info] Commenti
> - "**Centrale**" $=$ "importante". Poiché $\mathbb{E}[X_{1}+\dots+X_{n}]=n\mu$ e $\text{Var}[X_{1}+\dots+X_{n}]=n\sigma^{2}$, la quantità $\frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}$ è la **somma standardizzata** (media $0$, varianza $1$).
> - Compare **sempre** la funzione $\Phi$ (vedi [[04 - Modelli continui#Distribuzione normale|Normale]]), qualunque sia la distribuzione comune.
> - Se le $X_{n}$ sono già $N(\mu,\sigma^{2})$, per la [[04 - Modelli continui#Combinazioni lineari di normali indipendenti|combinazione lineare di Normali]] il risultato è **esatto per ogni $n$**.
### Formulazione con le medie
Dividendo numeratore e denominatore per $n$ si ottiene lo stesso evento con la [[05 - Convergenze e approssimazioni#La media campionaria|media campionaria]]: $$\frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}=\frac{\overline{X}_{n}-\mu}{\sigma/\sqrt{n}}\qquad\Longrightarrow\qquad \lim_{n\to\infty}P\left( \frac{\overline{X}_{n}-\mu}{\sigma/\sqrt{n}}\leq x \right)=\Phi(x)$$

> [!info] Altre formulazioni
> $$\lim_{n\to\infty}P\left( \frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}\geq x \right)=1-\Phi(x)$$ $$\lim_{n\to\infty}P\left( a\leq \frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}\leq b \right)=\Phi(b)-\Phi(a)\qquad(a<b)$$ (le disuguaglianze possono essere strette; ognuna ha la versione "con le medie").
### Esercizi (forma limite)

> [!example] $\{X_{n}\}$ i.i.d. $\sim U(0,2a)$: $\lim_{n}P(X_{1}+\dots+X_{n}>na+x\sqrt{n})$
> Per la [[04 - Modelli continui#Distribuzione uniforme continua|uniforme continua]]: $\mu=a$, $\sigma^{2}=\frac{(2a)^{2}}{12}=\frac{a^{2}}{3}$, $\sigma=\frac{a}{\sqrt{3}}$. Standardizzando: $$P(X_{1}+\dots+X_{n}>na+x\sqrt{n})\xrightarrow[n\to\infty]{}1-\Phi\left( \frac{\sqrt{3}\,x}{a} \right)$$Per averlo uguale a $1-\Phi\left( \frac{1}{2} \right)$ si impone $\frac{\sqrt{3}\,x}{a}=\frac{1}{2}$, cioè $\begin{bmatrix}x=\frac{a}{2\sqrt{3}}\end{bmatrix}$.

> [!example] $\{X_{n}\}$ i.i.d. $\sim Exp(\lambda=4)$: valore assoluto e $2\Phi(z)-1$
> Per la [[04 - Modelli continui#Distribuzione esponenziale|esponenziale]] $\mu=\frac{1}{\lambda}=\frac{1}{4}$, $\sigma=\frac{1}{\lambda}=\frac{1}{4}$. Domanda 2 della slide: trovare $z>0$ con $\lim_{n}P\left( \left| \frac{X_{1}+\dots+X_{n}-n/4}{\sqrt{n}} \right|\leq \frac{2}{3} \right)=2\Phi(z)-1$. Standardizzando (dividendo per $\sigma=\frac{1}{4}$) e usando $|u|\leq c\iff -c\leq u\leq c$: il limite è $\Phi\left( \frac{8}{3} \right)-\Phi\left( -\frac{8}{3} \right)=2\Phi\left( \frac{8}{3} \right)-1$. Per iniettività di $\Phi$: $\begin{bmatrix}z=\frac{8}{3}\end{bmatrix}$.

> [!example] $Exp(\lambda=4)$, domanda 1: argomenti positivi di $\Phi$ (lezione 22 p. 12)
> Con $\mu=\sigma=\frac{1}{4}$: $$P\left(-\frac{1}{8}\leq\frac{X_{1}+\dots+X_{n}-\frac{n}{4}}{\sqrt{n}}\leq\frac{1}{16}\right)\xrightarrow[n\to\infty]{}\Phi\left(\frac{1/16}{1/4}\right)-\Phi\left(\frac{-1/8}{1/4}\right)=\Phi\left(\frac{1}{4}\right)-\Phi\left(-\frac{1}{2}\right)=\Phi\left(\frac{1}{4}\right)+\Phi\left(\frac{1}{2}\right)-1$$usando $\Phi(-t)=1-\Phi(t)$ per avere solo argomenti positivi.

> [!example] $\{X_{n}\}$ i.i.d. con media $1$ e varianza $16$ (lezione 22 pp. 9-10)
> Si usa il TLC con $\mu=1$, $\sigma=\sqrt{16}=4$.
> 1. $\lim_{n}P\left(\frac{1}{2}\leq\frac{X_{1}+\dots+X_{n}-n}{\sqrt{n}}\leq 1\right)$: dividendo tutti i membri per $\sigma=4$ si ottiene $P\left(\frac{1}{4\cdot 2}\leq\frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}\leq\frac{1}{4}\right)\to\Phi\left(\frac{1}{4}\right)-\Phi\left(\frac{1}{8}\right)$.
> 2. Trovare $y$ con $\lim_{n}P\left(\frac{X_{1}+\dots+X_{n}-n}{\sqrt{n}}\geq y\right)=\Phi(-2)$. Il limite è $1-\Phi\left(\frac{y}{4}\right)$ e $\Phi(-2)=1-\Phi(2)$, quindi $\Phi\left(\frac{y}{4}\right)=\Phi(2)$; $\Phi$ è strettamente crescente, quindi invertibile: $\frac{y}{4}=2$, $\begin{bmatrix}y=8\end{bmatrix}$.

> [!tip] Metodo per i limiti col TLC *(riepilogo dei passaggi degli esercizi, non da slide)*
> 1. Ricavare $\mu$ e $\sigma=\sqrt{\sigma^{2}}$ dalla distribuzione comune.
> 2. Portare l'evento nella forma $\frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}$ dividendo tutti i membri per $\sigma$ (oppure, con le medie, $\frac{\overline{X}_{n}-\mu}{\sigma/\sqrt{n}}$).
> 3. Scrivere il limite con $\Phi(b)-\Phi(a)$ oppure $1-\Phi(x)$.
> 4. $|u|\leq c\iff -c\leq u\leq c$ per $c>0$; $\Phi(-t)=1-\Phi(t)$ per avere argomenti positivi.
> 5. Per «trovare il parametro» si uguagliano gli argomenti di $\Phi$ (iniettività).

> [!question] Domanda tipica d'esame
> Enunciare il teorema del limite centrale e usarlo per $\{X_{n}\}$ i.i.d. con media $1$ e varianza $16$: $\lim_{n}P\left(\frac{1}{2}\leq\frac{X_{1}+\dots+X_{n}-n}{\sqrt{n}}\leq 1\right)$.
> **Risposta.** Enunciato: $P\left(\frac{X_{1}+\dots+X_{n}-n\mu}{\sigma\sqrt{n}}\leq x\right)\to\Phi(x)$ per ogni $x$, con $\sigma^{2}\in(0,\infty)$. Con $\mu=1$, $\sigma=4$ si divide per $4$ e il limite è $\Phi\left(\frac{1}{4}\right)-\Phi\left(\frac{1}{8}\right)$.

--- Fine parte sul teorema del limite centrale (lezione 22) ---
## Approssimazione Normale e correzione di continuità
Applicazione del TLC per calcolare in modo approssimato probabilità su somme di tante v.a. i.i.d.
### Approssimazione Normale

> [!quote] Approssimazione Normale
> Siano $X_{1},\dots,X_{n}$ i.i.d. con media $\mu$ e varianza $\sigma^{2}$ finite ($\sigma^{2}>0$). Se $n$ è **grande**: $$X_{1}+\dots+X_{n}\ \approx\ N(n\mu,\,n\sigma^{2})\qquad \overline{X}_{n}\ \approx\ N\left( \mu,\frac{\sigma^{2}}{n} \right)$$

Sono **approssimazioni**, esatte solo se le $X_{i}$ sono già Normali. In pratica si standardizza e si usa $\Phi$. I valori numerici di $\Phi$ citati in questa sezione (ad esempio $\Phi(2{,}63)=0{,}99573$) sono **presi dalle tavole della Normale standard**, come fa la slide; per argomenti negativi si usa $\Phi(-t)=1-\Phi(t)$.

> [!example] Somma di Gamma
> $X_{1},\dots,X_{100}$ i.i.d. $\sim Gamma(2,4)$ (vedi [[04 - Modelli continui#Distribuzione Gamma|Gamma]]): $\mu=\frac{\alpha}{\beta}=\frac{1}{2}$, $\sigma^{2}=\frac{\alpha}{\beta^{2}}=\frac{1}{8}$, $\sigma=\frac{1}{2\sqrt{2}}$. Con $n=100$: $$P(X_{1}+\dots+X_{100}>60)\approx 1-\Phi(2\sqrt{2})$$ (analogamente $P(42<\dots<48)\approx\Phi(\tfrac{8}{5}\sqrt{2})-\Phi(\tfrac{2}{5}\sqrt{2})$).

> [!example] Errore di arrotondamento di un calcolatore (lezione 22 pp. 15-16)
> Un calcolatore somma $10^{6}$ numeri e a ogni somma genera un errore aleatorio $U(-0{,}5\cdot 10^{-10},0{,}5\cdot 10^{-10})$, con errori indipendenti. Calcolare la probabilità che l'errore totale sia in valore assoluto minore di $0{,}5\cdot 10^{-7}$, con l'approssimazione Normale ($10^{6}$ è il numero degli addendi, grande).
> $\mu=0$, $\sigma^{2}=\frac{(10^{-10})^{2}}{12}$, $\sigma=\frac{10^{-10}}{2\sqrt{3}}$, $\sigma\sqrt{10^{6}}=\frac{10^{-7}}{2\sqrt{3}}$. Con $S=X_{1}+\dots+X_{10^{6}}$: $$P\left(-0{,}5\cdot10^{-7}<S<0{,}5\cdot10^{-7}\right)\approx\Phi(\sqrt{3})-\Phi(-\sqrt{3})=2\Phi(\sqrt{3})-1=2\cdot0{,}95819-1=0{,}91638$$ ($\Phi(\sqrt{3})=0{,}95819$ è il valore della slide; *(extra, non da slide)* con le tavole $\Phi(1{,}73)=0{,}95818$, mentre $\Phi(\sqrt{3})\approx0{,}95837$, quindi il risultato più preciso è $2\Phi(\sqrt{3})-1\approx0{,}9167$).
### Correzione di continuità
Quando le $X_{i}$ (con $n$ grande) assumono **valori interi**, al valore intero $k$ si associa l'intervallo $(k-0{,}5,\ k+0{,}5)$: $$\{X_{1}+\dots+X_{n}>k\}=\{\dots\geq k+1\}=\{\dots>k+0{,}5\}\qquad \{X_{1}+\dots+X_{n}\geq k\}=\{\dots>k-0{,}5\}$$(analogamente per intervalli limitati: $\{a\leq\dots\leq b\}\to\{a-0{,}5<\dots<b+0{,}5\}$). Le quattro regole, a seconda che gli estremi siano inclusi o esclusi:
$$P(k_{1}\leq S\leq k_{2})=P(k_{1}-0{,}5<S<k_{2}+0{,}5)\qquad P(k_{1}<S\leq k_{2})=P(k_{1}+0{,}5<S<k_{2}+0{,}5)$$ $$P(k_{1}\leq S<k_{2})=P(k_{1}-0{,}5<S<k_{2}-0{,}5)\qquad P(k_{1}<S<k_{2})=P(k_{1}+0{,}5<S<k_{2}-0{,}5)$$con $S=X_{1}+\dots+X_{n}$ e $k_{1},k_{2}$ **interi** (le quattro regole della lavagna aggiuntiva della lezione 22).

> [!example] Approssimare una Binomiale (il nome «De Moivre–Laplace» *(extra, non da slide)*)
> $X\sim Bin(n,p)$ (vedi [[02 - Modelli discreti#Caso 1): distribuzione binomiale|binomiale]]) è somma di $n$ [[02 - Modelli discreti#Distribuzione Bernoulliana|Bernoulli]] i.i.d. ($\mu=p$, $\sigma^{2}=p(1-p)$); per $n$ grande $X\approx N(np,np(1-p))$.
> - **Moneta equa, 400 lanci**, $X\sim Bin(400,\frac{1}{2})\approx N(200,100)$: $$P(195\leq X\leq 210)=P(194{,}5<X<210{,}5)\approx\Phi(1{,}05)-\Phi(-0{,}55)\approx0{,}56198$$($\sigma=\sqrt{100}=10$; valore ottenuto dalle tavole: $\Phi(1{,}05)=0{,}85314$, $\Phi(0{,}55)=0{,}70884$ *(extra, non da slide: la slide lascia il risultato in forma di $\Phi$)*).
> - **Dado equo, 900 lanci**, "almeno 180 volte il 6", $X\sim Bin(900,\frac{1}{6})$: $$P(X\geq 180)=P(X\geq 179{,}5)\approx 1-\Phi(2{,}63)=1-0{,}99573=0{,}00427$$($\frac{179{,}5-150}{\sqrt{5/36}\cdot30}=\frac{29{,}5}{5\sqrt{5}}\approx2{,}63$; $\Phi(2{,}63)$ dalle tavole).
> - **Dado «troncato»** con $p=\frac{2}{9}$ per il 6 (nel testo la slide p. 20 scrive per refuso $\frac{2}{3}$, lo svolgimento usa $\frac{2}{9}$; stessa domanda, $X\sim Bin(900,\frac{2}{9})\approx N(200,\frac{1400}{9})$): $$P(X\geq180)=P(X\geq179{,}5)\approx 1-\Phi\left(\frac{179{,}5-200}{\sqrt{\frac{14}{81}}\cdot 30}\right)\approx1-\Phi(-1{,}64)=\Phi(1{,}64)\approx0{,}9495$$ Probabilità grande (la campana è centrata in $200$), a differenza del caso $p=\frac{1}{6}$ (campana centrata in $150$, coda destra a partire da $179{,}5$: probabilità piccola). In generale la quantità da calcolare è $\frac{179{,}5-900p}{\sqrt{p(1-p)}\cdot30}$.
> - Senza approssimazione Normale: $P(X\geq180)=\sum_{k=180}^{900}\binom{900}{k}p^{k}(1-p)^{900-k}$ (valore esatto, ma non pratico da quantificare).

> [!example] $\{X_{n}\}$ i.i.d. $\sim U(-1,3)$: TLC con le medie (lezione 22 pp. 24-25)
> $\mu=\frac{-1+3}{2}=1$, $\sigma^{2}=\frac{(3-(-1))^{2}}{12}=\frac{4}{3}$, $\sigma=\frac{2}{\sqrt{3}}$.
> 1. $\lim_{n}P\left(1\leq\frac{\overline{X}_{n}-1}{1/\sqrt{n}}<2\right)=\lim_{n}P\left(\frac{1}{\sigma}\leq\frac{\overline{X}_{n}-\mu}{\sigma/\sqrt{n}}<\frac{2}{\sigma}\right)=\Phi(\sqrt{3})-\Phi\left(\frac{\sqrt{3}}{2}\right)$; stesso risultato con le somme (metodo alternativo della slide).
> 2. $P\left(\overline{X}_{900}-1<\frac{1}{15}\right)$ con l'approssimazione Normale: $\sigma/\sqrt{900}=\frac{2}{\sqrt{3}}\cdot\frac{1}{30}$, quindi $\frac{1/15}{\frac{2}{\sqrt{3}}\cdot\frac{1}{30}}=\sqrt{3}$ e $P\approx\Phi(\sqrt{3})$ *(passaggio finale ricavato qui, non scritto per esteso nella slide)*.

> [!question] Domanda tipica d'esame
> Si lanciano $900$ volte un dado equo: probabilità di almeno $180$ volte il 6, con approssimazione Normale e correzione di continuità?
> **Risposta.** $X\sim Bin(900,\frac{1}{6})\approx N(150,125)$; $P(X\geq180)=P(X\geq179{,}5)\approx1-\Phi\left(\frac{29{,}5}{5\sqrt{5}}\right)\approx1-\Phi(2{,}63)\approx0{,}00427$ (da tavole).

--- Fine lezione 22 (TLC, approssimazione Normale, correzione di continuità) ---
### Esercizi della lezione 24 (TLC e correzione di continuità)
Esercizi di ripasso della lezione 24, pp. 21-29 del PDF (le pp. 18-20 trattano la Normale).

> [!example] Binomiale con correzione di continuità: 400 lanci, estremi compresi (pp. 21-22)
> $X\sim Bin(400,p)$; $P(190\leq X\leq205)=P(189{,}5<X<205{,}5)$ (si usa la prima regola della correzione di continuità).
> 1. Moneta equa ($np=200$, $\sigma=\sqrt{400\cdot\frac{1}{2}\cdot\frac{1}{2}}=10$): $\Phi(0{,}55)-\Phi(-1{,}05)=0{,}56198$.
> 2. $p=\frac{190}{400}$ ($np=190$, $\sqrt{p(1-p)}\simeq0{,}499$, quindi $\sigma\simeq10$): $\Phi(1{,}55)-\Phi(-0{,}05)=0{,}45937$ (dalle tavole: $\Phi(1{,}55)=0{,}93943$, $\Phi(-0{,}05)=1-0{,}51994$).
>
> Attenzione: nella slide p. 21 il secondo caso è scritto $\Phi(1{,}55)-\Phi(-0{,}55)$ per refuso: $\frac{189{,}5-190}{10}=-0{,}05$, e il valore $0{,}45937$ corrisponde a $-0{,}05$ (ricontrollato).
> Senza la correzione si avrebbe $\Phi(0{,}5)-\Phi(-1)=0{,}5328$ e $\Phi(1{,}5)-\Phi(0)=0{,}43319$: valori vicini ma un po' più piccoli. Nel caso 1 la probabilità è maggiore perché l'intervallo è più vicino al centro della campana (p. 22).

> [!example] $\{X_{n}\}$ i.i.d. con media $\mu$ e varianza $16$ (pp. 23-24)
> 1. $\lim_{n}P\left(\mu<\frac{X_{1}+\dots+X_{n}}{n}<\mu+\frac{1}{\sqrt{n}}\right)=\lim_{n}P\left(0<\frac{\overline{X}_{n}-\mu}{4/\sqrt{n}}<\frac{1}{4}\right)=\Phi\left(\frac{1}{4}\right)-\Phi(0)=\Phi\left(\frac{1}{4}\right)-0{,}5$ (TLC per le medie; con le somme si arriva allo stesso risultato).
> 2. Trovare $\mu$ con $P(X_{1}+\dots+X_{100}>102\mu)\approx1-\Phi(2)$. Per ogni $\mu$: $P\approx1-\Phi\left(\frac{102\mu-100\mu}{4\cdot10}\right)=1-\Phi\left(\frac{\mu}{20}\right)$. Per invertibilità di $\Phi$: $\frac{\mu}{20}=2$, $\begin{bmatrix}\mu=40\end{bmatrix}$.

> [!example] $\{X_{n}\}$ i.i.d. $\sim Exp(\lambda=2)$, $\mu=\sigma=\frac{1}{2}$ (pp. 25-29)
> 1. $\lim_{n}P\left(0\leq\frac{X_{1}+\dots+X_{n}-\frac{n}{2}}{\sqrt{n}}<\frac{3}{4}\right)=\Phi\left(\frac{3/4}{1/2}\right)-\Phi(0)=\Phi\left(\frac{3}{2}\right)-0{,}5$.
> 2. $\lim_{n}P\left(\left|\overline{X}_{n}-\frac{1}{2}\right|>\frac{2}{5}\frac{x}{\sqrt{n}}\right)=1-\Phi\left(\frac{4}{5}x\right)+\Phi\left(-\frac{4}{5}x\right)=2\left(1-\Phi\left(\frac{4}{5}x\right)\right)$ (somma delle due code, oppure passaggio al complementare $1-P(|\dots|\leq\dots)$). Uguagliando a $2(1-\Phi(1))$: $\frac{4}{5}x=1$, $\begin{bmatrix}x=\frac{5}{4}\end{bmatrix}$.
> 3. $P(X_{1}+\dots+X_{100}\geq57)\approx1-\Phi\left(\frac{57-50}{\frac{1}{2}\cdot10}\right)=1-\Phi\left(\frac{7}{5}\right)$ (qui la slide non applica la correzione di continuità: le $X_{i}$ sono continue).
> 4. $P(180\leq X_{1}+\dots+X_{400}\leq210)\approx\Phi\left(\frac{210-200}{10}\right)-\Phi\left(\frac{180-200}{10}\right)=\Phi(1)-\Phi(-2)=\Phi(1)+\Phi(2)-1$.

> [!question] Domanda tipica d'esame
> $\{X_{n}\}$ i.i.d. $\sim Exp(\lambda=2)$: calcolare con l'approssimazione Normale $P(X_{1}+\dots+X_{100}\geq57)$.
> **Risposta.** $\mu=\sigma=\frac{1}{2}$; somma $\approx N(50,25)$; $P\approx1-\Phi\left(\frac{57-50}{5}\right)=1-\Phi\left(\frac{7}{5}\right)$.

--- Fine esercizi TLC della lezione 24 (pp. 21-29) ---
