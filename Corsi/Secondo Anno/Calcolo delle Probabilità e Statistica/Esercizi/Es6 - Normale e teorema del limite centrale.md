## Es6 — Normale e teorema del limite centrale
Ultimo esercizio dello scritto. La traccia apre **sempre** definendo

$$\Phi(y)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{y}e^{-x^{2}/2}dx$$

cioè la funzione di distribuzione della Normale standard, e chiede di esprimere il risultato **con $\Phi$**. Non si calcolano integrali e non servono le tavole: la risposta è una formula in $\Phi$.

Nel formato fino al 2024-25 era l'esercizio 5, con due sotto-domande: una sulla Normale "pura" e una sul TLC.
### Le due situazioni possibili
**1. $X$ è già Normale** — la traccia dice «sia $X$ una variabile aleatoria Normale con media $\mu$ e varianza $\sigma^2$». Si standardizza e basta.

**2. $X_1,X_2,\dots$ sono i.i.d. qualsiasi** — la traccia dà solo media e varianza, oppure una distribuzione non normale, e chiede una probabilità sulla **somma** di tante di esse. Qui interviene il **teorema del limite centrale**: la somma standardizzata è approssimativamente Normale standard.

> [!info] Come riconoscere il caso 2 a colpo d'occhio
> Compaiono $X_1+\cdots+X_n$ con $n$ grande ($100$, $900$, $10^6$), oppure un $\lim_{n\to\infty}$. La parola chiave nella traccia è **«con l'approssimazione Normale»** o **«i.i.d.»**.

### Le formule
**Standardizzazione** — se $X$ ha media $\mu$ e varianza $\sigma^2$:

$$P(X\le a)=P\left(\frac{X-\mu}{\sigma}\le\frac{a-\mu}{\sigma}\right)=\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$

**Teorema del limite centrale** — per $X_i$ i.i.d. con media $\mu$ e varianza $\sigma^2$, la somma $S_n=X_1+\cdots+X_n$ ha media $n\mu$ e deviazione standard $\sigma\sqrt{n}$:

$$P(S_n\le s)\approx\Phi\!\left(\frac{s-n\mu}{\sigma\sqrt{n}}\right)$$

**Simmetria** — indispensabile per ridursi ad argomenti positivi come chiede la traccia:

$$\Phi(-x)=1-\Phi(x)$$

**Intervallo** — sempre come differenza di due valori:

$$P(a<X<b)=\Phi\!\left(\frac{b-\mu}{\sigma}\right)-\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$

**Combinazione lineare di Normali indipendenti** — resta Normale:

$$aX_1+bX_2\sim N\big(a\mu_1+b\mu_2,\ a^2\sigma_1^2+b^2\sigma_2^2\big)$$

> [!warning] $\sigma$ è la radice della varianza
> La traccia dà sempre la **varianza**, mai la deviazione standard: «varianza 9» significa $\sigma=3$, «varianza 100» significa $\sigma=10$. Macci apre le sue soluzioni esattamente così — *«Osservando che $\sigma=\sqrt{100}=10$…»* — perché è lì che si sbaglia.
>
> E al denominatore del TLC va $\sigma\sqrt{n}$, **non** $\sigma^2\sqrt{n}$ né $\sigma n$.

### Il procedimento passo per passo
1. **Identificare $\mu$ e $\sigma$** della singola variabile. Se la traccia dà una distribuzione invece dei momenti (esponenziale, Poisson, Bernoulli), media e varianza vanno ricavate da quella.

2. **Scrivere media e deviazione standard della somma**: $n\mu$ e $\sigma\sqrt{n}$.

3. **Manipolare la disuguaglianza** sottraendo $n\mu$ e dividendo per $\sigma\sqrt{n}$ **a entrambi i membri**, fino a isolare la somma standardizzata.

4. **Sostituire con $\Phi$**, ricordando che $P(Z>z)=1-\Phi(z)$.

5. **Ridurre ad argomenti positivi** con $\Phi(-x)=1-\Phi(x)$, se la traccia lo chiede.

### Esercizi svolti — formato 2025-2026
#### Limite con TLC — appello del 6 Febbraio 2026
Sia $\{X_n\}$ i.i.d. con media 2 e varianza 9. Calcolare

$$\lim_{n\to\infty}P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)$$

esprimendo il risultato con $\Phi$.

**Svolgimento**

Prima cosa: $\sigma=\sqrt{9}=3$, e la somma ha media $n\mu=2n$.

La traccia è costruita apposta perché la standardizzazione venga pulita. Si sottrae $2n$ da entrambi i membri e si divide per $\sigma\sqrt{n}=3\sqrt{n}$:

$$P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)=P\big(X_1+\cdots+X_n-2n>\sqrt{n}\big)=P\left(\frac{X_1+\cdots+X_n-2n}{3\sqrt{n}}>\frac{\sqrt{n}}{3\sqrt{n}}\right)$$

A destra $\frac{\sqrt{n}}{3\sqrt{n}}=\frac{1}{3}$, che **non dipende da $n$**: è il motivo per cui il limite esiste. A sinistra c'è esattamente la somma standardizzata, che per il TLC tende alla Normale standard:

$$\lim_{n\to\infty}P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)=1-\Phi\!\left(\frac{1}{3}\right)$$

Il $\sqrt{n}$ nella traccia non è decorativo: è tarato sulla scala del TLC, dove le fluttuazioni della somma sono dell'ordine di $\sqrt{n}$.
#### Intervallo e riduzione ad argomenti positivi — appello del 20 Febbraio 2026
Siano $X_1,\dots,X_{900}$ i.i.d. con media 1 e varianza 100. Calcolare $P(700<X_1+\cdots+X_{900}<800)$ con l'approssimazione Normale, esprimendo il risultato con $\Phi$ ad argomenti positivi.

**Svolgimento**

$\sigma=\sqrt{100}=10$, media della somma $n\mu=900$, deviazione standard della somma $\sigma\sqrt{n}=10\cdot30=300$.

Si sottrae 900 da tutti e tre i membri e si divide per 300:

$$P(700<S_{900}<800)=P\left(\frac{-200}{300}<\frac{S_{900}-900}{300}<\frac{-100}{300}\right)=P\left(-\frac{2}{3}<Z<-\frac{1}{3}\right)$$

Entrambi gli argomenti sono **negativi**: la somma osservata è sotto la media. Si applica $\Phi(-x)=1-\Phi(x)$:

$$\approx\Phi\!\left(-\frac{1}{3}\right)-\Phi\!\left(-\frac{2}{3}\right)=\left(1-\Phi\!\left(\frac{1}{3}\right)\right)-\left(1-\Phi\!\left(\frac{2}{3}\right)\right)=\Phi\!\left(\frac{2}{3}\right)-\Phi\!\left(\frac{1}{3}\right)$$

> [!question] Attenzione all'ordine dopo il ribaltamento
> Passando agli argomenti positivi i due termini si **scambiano**: si parte da $\Phi(-1/3)-\Phi(-2/3)$ e si arriva a $\Phi(2/3)-\Phi(1/3)$. Il risultato deve restare positivo, essendo una probabilità: è il controllo immediato per sapere se hai sbagliato il verso.

#### Coda destra con media nulla — appello del 19 Giugno 2026
Siano $X_1,\dots,X_{10^6}$ i.i.d. con media 0 e varianza 9. Calcolare $P(X_1+\cdots+X_{10^6}>10^3)$.

**Svolgimento**

$\sigma=3$, media della somma $10^6\cdot0=0$, deviazione standard $3\sqrt{10^6}=3\cdot10^3$.

$$P(S>10^3)=P\left(\frac{S-0}{3\cdot10^{3}}>\frac{10^{3}}{3\cdot10^{3}}\right)=P\left(Z>\frac{1}{3}\right)\approx1-\Phi\!\left(\frac{1}{3}\right)$$

Con media nulla il passaggio è ancora più corto: non c'è niente da sottrarre. Da notare che $\sqrt{10^6}=10^3$ — le tracce scelgono $n$ come quadrato perfetto proprio per questo.
### Esercizi svolti — varianti dagli appelli precedenti
#### Normale "pura", senza TLC — appello del 12 Luglio 2022
Sia $X$ Normale con media 2 e varianza 25. Calcolare $P(3\le X\le4)$ esprimendo il risultato con $\Phi$.

**Svolgimento**

Qui non c'è nessuna somma: $X$ è già Normale, si standardizza direttamente con $\mu=2$ e $\sigma=\sqrt{25}=5$.

$$P(3\le X\le4)=\Phi\!\left(\frac{4-2}{5}\right)-\Phi\!\left(\frac{3-2}{5}\right)=\Phi\!\left(\frac{2}{5}\right)-\Phi\!\left(\frac{1}{5}\right)$$

Entrambi gli argomenti sono già positivi, non serve la simmetria.
#### Normale standard con un estremo negativo — appello del 20 Giugno 2023
Sia $X$ Normale standard. Calcolare $P\!\left(-1\le X\le\frac{3}{2}\right)$ con $\Phi$ ad argomenti positivi.

**Svolgimento**

Normale standard significa $\mu=0$, $\sigma=1$: non c'è niente da standardizzare.

$$P\left(-1\le X\le\frac{3}{2}\right)=\Phi\!\left(\frac{3}{2}\right)-\Phi(-1)=\Phi\!\left(\frac{3}{2}\right)-\big(1-\Phi(1)\big)=\Phi\!\left(\frac{3}{2}\right)+\Phi(1)-1$$

Quando gli estremi stanno **a cavallo dello zero**, la riduzione ad argomenti positivi trasforma la differenza in una **somma meno 1**. È una forma che ricorre spesso.
#### Distribuzione data invece dei momenti — appello del 12 Luglio 2022
Sia $\{X_n\}$ i.i.d. con distribuzione **esponenziale** di parametro $\lambda>0$, cioè $f(x)=\lambda e^{-\lambda x}\mathbb{1}_{(0,\infty)}(x)$. Verificare che per ogni $z\in\mathbb{R}$

$$\lim_{n\to\infty}P\left(\frac{X_1+\cdots+X_n-\frac{n}{\lambda}}{\frac{\sqrt{n}}{\lambda}}\le z\right)=\Phi(z)$$

**Svolgimento**

Qui la traccia non dà media e varianza: vanno ricavate dalla distribuzione. Per l'esponenziale di parametro $\lambda$ si ha

$$\mu=E[X]=\frac{1}{\lambda}\qquad \sigma^{2}=\text{Var}[X]=\frac{1}{\lambda^{2}}\qquad\Rightarrow\qquad\sigma=\frac{1}{\lambda}$$

Sostituendo nella formula del TLC: la somma ha media $n\mu=\frac{n}{\lambda}$ e deviazione standard $\sigma\sqrt{n}=\frac{\sqrt{n}}{\lambda}$ — che sono esattamente i due termini nell'espressione data. Quindi l'espressione **è già** la somma standardizzata, e il TLC dice che il suo limite è $\Phi(z)$.

> [!info] Media e varianza delle continue notevoli
> Servono come input quando la traccia dà la distribuzione invece dei momenti:
> - **Uniforme** su $(a,b)$: $\mu=\frac{a+b}{2}$, $\sigma^2=\frac{(b-a)^2}{12}$
> - **Esponenziale**$(\lambda)$: $\mu=\frac{1}{\lambda}$, $\sigma^2=\frac{1}{\lambda^2}$
> - **Normale**$(\mu,\sigma^2)$: già dati
>
> Per le discrete — Bernoulli, binomiale, Poisson, geometrica — la tabella è in [[Es1 - Probabilità discreta elementare|Es1]].

#### Equazione con condizionata su una Normale — appello del 3 Febbraio 2025
Sia $X$ Normale con media 2 e varianza $\sigma^2$. Trovare, se esiste, $y>2$ tale che $P(X<2\,|\,0<X<y)=\frac{1}{2}$.

**Svolgimento**

Si applica la definizione di condizionata, osservando che $\{X<2\}\cap\{0<X<y\}=\{0<X<2\}$ perché $y>2$. Poi si standardizza numeratore e denominatore con $X^{*}=\frac{X-2}{\sigma}$, ricordando che $\Phi(0)=0{,}5$:

$$\frac{1}{2}=\frac{P(0<X<2)}{P(0<X<y)}=\frac{\Phi(0)-\Phi(-2/\sigma)}{\Phi\!\left(\frac{y-2}{\sigma}\right)-\Phi(-2/\sigma)}=\frac{\Phi(2/\sigma)-0{,}5}{\Phi(2/\sigma)+\Phi\!\left(\frac{y-2}{\sigma}\right)-1}$$

Moltiplicando in croce e semplificando:

$$2\Phi(2/\sigma)-1=\Phi(2/\sigma)+\Phi\!\left(\frac{y-2}{\sigma}\right)-1\ \Rightarrow\ \Phi(2/\sigma)=\Phi\!\left(\frac{y-2}{\sigma}\right)$$

Poiché $\Phi$ è **strettamente crescente**, quindi invertibile, si possono uguagliare gli argomenti:

$$\frac{2}{\sigma}=\frac{y-2}{\sigma}\ \Rightarrow\ y-2=2\ \Rightarrow\ y=4$$

> [!info] La scorciatoia, come controllo
> Il risultato si vede anche senza conti: la Normale è **simmetrica** attorno alla media, che qui è 2, quindi la condizionata vale $\frac{1}{2}$ esattamente quando l'intervallo $(0,y)$ è centrato in 2 — cioè $\frac{0+y}{2}=2$, da cui $y=4$. Coerente col fatto che $\sigma$ sparisce dal risultato.
>
> Sull'elaborato conviene comunque scrivere il passaggio algebrico: l'argomento di simmetria è ottimo per verificare, meno per convincere chi corregge.
### Trappole ricorrenti
- **Varianza scambiata per deviazione standard**: $\sigma=\sqrt{\text{Var}}$. È l'errore numero uno, e il prof lo previene aprendo sempre la soluzione con il calcolo di $\sigma$.

- **Denominatore del TLC**: $\sigma\sqrt{n}$. Non $\sigma^2\sqrt{n}$, non $\sigma n$, non $\sqrt{\sigma n}$.

- **Dividere solo un membro**: la manipolazione va fatta su **tutti** i membri della disuguaglianza, estremi compresi.

- **$P(Z>z)$ dimenticato**: $\Phi$ dà sempre la coda **sinistra**. Per la destra serve $1-\Phi(z)$.

- **Ordine invertito nelle differenze**: dopo aver applicato $\Phi(-x)=1-\Phi(x)$ i due termini si scambiano. Controllo: il risultato deve essere positivo e minore di 1.

- **Media e varianza non date**: se la traccia fornisce una distribuzione, i momenti vanno calcolati prima — è lì che l'esercizio si collega a [[Es5 - Speranza di variabile continua|Es5]].

- **Approssimazione vs uguaglianza**: con il TLC il risultato è un $\approx$, non un $=$. Con una Normale vera è un'uguaglianza esatta.
### Collegamenti
- $\Phi$ è la funzione di distribuzione della Normale standard: stessa nozione di [[Es4 - Trasformazione di variabile continua|Es4]], ma tabulata una volta per tutte.

- Media e varianza in ingresso: [[Es5 - Speranza di variabile continua]] per le continue, [[Es1 - Probabilità discreta elementare]] per le discrete.
