# Convergenze e approssimazioni
Appunti sul **Capitolo 5** del corso (lezione 22): il comportamento della somma/media di tante v.a. i.i.d. al crescere di $n$. Sezioni:
1. [[05 - Convergenze e approssimazioni#Legge dei grandi numeri|Legge dei grandi numeri]] — legge debole e forte: la media campionaria $\overline{X}_{n}$ si concentra sulla media $\mu$.
2. [[05 - Convergenze e approssimazioni#Teorema del limite centrale|Teorema del limite centrale]] — la somma standardizzata di v.a. i.i.d. tende a $N(0,1)$ (materia di **Es6**).
3. [[05 - Convergenze e approssimazioni#Approssimazione Normale e correzione di continuità|Approssimazione Normale e correzione di continuità]] — uso pratico del TLC, con la correzione per v.a. a valori interi.
## Nota sulla struttura
Blocco successivo a [[04 - Modelli continui]]. È il **Capitolo 5** del corso. I marcatori `--- Fine lezione NN ---` conservano la corrispondenza con i PDF delle lezioni in `Materiale Didattico/Lezioni/6 CFU/`.

## Legge dei grandi numeri
Per una successione di v.a. i.i.d., la media aritmetica delle prime $n$ variabili si concentra sulla media comune $\mu$.
### La media campionaria
Sia $\{X_{n}:n\geq 1\}$ una successione di v.a. **i.i.d.** (indipendenti e identicamente distribuite). Si pone $$\overline{X}_{n}=\frac{X_{1}+\dots+X_{n}}{n}$$(la **media aritmetica** delle prime $n$ v.a.; notazione usata anche nel seguito).
### Enunciato
> [!quote] Legge dei grandi numeri (legge debole)
> Sia $\{X_{n}:n\geq 1\}$ i.i.d. con **speranza matematica finita** (media comune $\mu$). Allora $$\begin{bmatrix}\lim_{n\to\infty}P\big(|\overline{X}_{n}-\mu|\geq\varepsilon\big)=0\qquad\forall\varepsilon>0\end{bmatrix}$$

> [!info] Legge forte (stesse ipotesi)
> Vale la versione **forte**: $P\big(\{\omega\in\ohm:\lim_{n\to\infty}\overline{X}_{n}(\omega)=\mu\}\big)=1$ (si dimostra che quel sottoinsieme di $\ohm$ è un evento; va oltre gli scopi del corso).

Anche per $\varepsilon>0$ piccolissimo, la probabilità che $\overline{X}_{n}$ cada **fuori** da $(\mu-\varepsilon,\mu+\varepsilon)$ tende a $0$: all'aumentare di $n$ la media campionaria si concentra attorno a $\mu$.
### Dimostrazione (con varianza finita)
Aggiungiamo l'ipotesi di **varianza finita** $\sigma^{2}$. Allora $$\mathbb{E}[\overline{X}_{n}]=\frac{n\mu}{n}=\mu\qquad \text{Var}[\overline{X}_{n}]=\frac{1}{n^{2}}\,\text{Var}[X_{1}+\dots+X_{n}]\overset{\text{indip.}}{=}\frac{1}{n^{2}}\,n\sigma^{2}=\frac{\sigma^{2}}{n}$$Applicando la [[03 - Speranza matematica e momenti|disuguaglianza di Chebyshev]] a $\overline{X}_{n}$: $$0\leq P\big(|\overline{X}_{n}-\mu|\geq\varepsilon\big)\leq \frac{\text{Var}[\overline{X}_{n}]}{\varepsilon^{2}}=\frac{\sigma^{2}}{n\varepsilon^{2}}\xrightarrow[n\to\infty]{}0$$e per il teorema del confronto si conclude. $\Box$
### Esercizi tipici
> [!example] Media dei lanci di un dado
> $X_{n}=$ numero uscito all'$n$-simo lancio di un dado equo. Il $\mu$ cercato è la media comune: $\mu=\sum_{k=1}^{6}k\cdot\frac{1}{6}=\frac{21}{6}=\frac{7}{2}$.

> [!example] Processo di Poisson
> Per un [[04 - Modelli continui#Il processo di Poisson|processo di Poisson]] di intensità $\lambda$, con $T_{n}=S_{1}+\dots+S_{n}$ e $\{S_{m}\}$ i.i.d. $\sim Exp(\lambda)$: poiché $\frac{T_{n}}{n}=\overline{S}_{n}$, il $\mu$ è $\mathbb{E}[S_{m}]=\frac{1}{\lambda}$.

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
> $\mu=a$, $\sigma^{2}=\frac{(2a)^{2}}{12}=\frac{a^{2}}{3}$, $\sigma=\frac{a}{\sqrt{3}}$. Standardizzando: $$P(X_{1}+\dots+X_{n}>na+x\sqrt{n})\xrightarrow[n\to\infty]{}1-\Phi\left( \frac{\sqrt{3}\,x}{a} \right)$$Per averlo uguale a $1-\Phi\left( \frac{1}{2} \right)$ si impone $\frac{\sqrt{3}\,x}{a}=\frac{1}{2}$, cioè $\begin{bmatrix}x=\frac{a}{2\sqrt{3}}\end{bmatrix}$.

> [!example] $\{X_{n}\}$ i.i.d. $\sim Exp(\lambda=4)$: valore assoluto e $2\Phi(z)-1$
> $\mu=\frac{1}{4}$, $\sigma=\frac{1}{4}$. Trovare $z>0$ con $\lim_{n}P\left( \left| \frac{X_{1}+\dots+X_{n}-n/4}{\sqrt{n}} \right|\leq \frac{2}{3} \right)=2\Phi(z)-1$. Standardizzando (dividendo per $\sigma=\frac{1}{4}$) e usando $|u|\leq c\iff -c\leq u\leq c$: il limite è $\Phi\left( \frac{8}{3} \right)-\Phi\left( -\frac{8}{3} \right)=2\Phi\left( \frac{8}{3} \right)-1$. Per iniettività di $\Phi$: $\begin{bmatrix}z=\frac{8}{3}\end{bmatrix}$.

--- Fine parte sul teorema del limite centrale (lezione 22) ---

## Approssimazione Normale e correzione di continuità
Applicazione del TLC per calcolare in modo approssimato probabilità su somme di tante v.a. i.i.d.
### Approssimazione Normale
> [!quote] Approssimazione Normale
> Siano $X_{1},\dots,X_{n}$ i.i.d. con media $\mu$ e varianza $\sigma^{2}$ finite ($\sigma^{2}>0$). Se $n$ è **grande**: $$X_{1}+\dots+X_{n}\ \approx\ N(n\mu,\,n\sigma^{2})\qquad \overline{X}_{n}\ \approx\ N\left( \mu,\frac{\sigma^{2}}{n} \right)$$

Sono **approssimazioni**, esatte solo se le $X_{i}$ sono già Normali. In pratica si standardizza e si usa $\Phi$.
> [!example] Somma di Gamma
> $X_{1},\dots,X_{100}$ i.i.d. $\sim Gamma(2,4)$: $\mu=\frac{\alpha}{\beta}=\frac{1}{2}$, $\sigma^{2}=\frac{\alpha}{\beta^{2}}=\frac{1}{8}$, $\sigma=\frac{1}{2\sqrt{2}}$. Con $n=100$: $$P(X_{1}+\dots+X_{100}>60)\approx 1-\Phi(2\sqrt{2})$$ (analogamente $P(42<\dots<48)\approx\Phi(\tfrac{8}{5}\sqrt{2})-\Phi(\tfrac{2}{5}\sqrt{2})$).

### Correzione di continuità
Quando le $X_{i}$ (con $n$ grande) assumono **valori interi**, al valore intero $k$ si associa l'intervallo $(k-0{,}5,\ k+0{,}5)$: $$\{X_{1}+\dots+X_{n}>k\}=\{\dots\geq k+1\}=\{\dots>k+0{,}5\}\qquad \{X_{1}+\dots+X_{n}\geq k\}=\{\dots>k-0{,}5\}$$(analogamente per intervalli limitati: $\{a\leq\dots\leq b\}\to\{a-0{,}5<\dots<b+0{,}5\}$).
> [!example] De Moivre–Laplace: approssimare una Binomiale
> $X\sim Bin(n,p)$ è somma di $n$ Bernoulli i.i.d. ($\mu=p$, $\sigma^{2}=p(1-p)$); per $n$ grande $X\approx N(np,np(1-p))$.
> - **Moneta equa, 400 lanci**, $X\sim Bin(400,\frac{1}{2})\approx N(200,100)$: $$P(195\leq X\leq 210)=P(194{,}5<X<210{,}5)\approx\Phi(1{,}05)-\Phi(-0{,}55)$$
> - **Dado equo, 900 lanci**, "almeno 180 volte il 6", $X\sim Bin(900,\frac{1}{6})$: $$P(X\geq 180)=P(X\geq 179{,}5)\approx 1-\Phi(2{,}63)\approx 0{,}00427$$

--- Fine lezione 22 (TLC, approssimazione Normale, correzione di continuità) ---
