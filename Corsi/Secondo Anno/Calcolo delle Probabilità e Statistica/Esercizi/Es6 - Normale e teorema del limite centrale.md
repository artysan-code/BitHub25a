## Es6 — Normale e teorema del limite centrale
Ultimo esercizio dello scritto: esprimere con $\Phi$ una probabilità sulla Normale o sulla somma standardizzata di variabili i.i.d. (teorema del limite centrale). Non si calcolano integrali e non servono le tavole: la risposta resta in forma di $\Phi$.
### Prima di tutto: Φ, standardizzare, varianza
Tre oggetti da avere chiari prima di partire:
- **$\Phi$ è la funzione di distribuzione della Normale standard** $N(0,1)$: $\Phi(z)=P(Z\le z)$, la probabilità che una Normale standard esca $\le z$. Non ha primitiva elementare — **non si calcola a mano** — quindi la risposta **resta in forma di $\Phi$** (niente tavole all'esame).
- **La varianza $\sigma^2$ misura quanto $X$ si sparpaglia attorno alla media** $\mu=E[X]$; la sua radice $\sigma=\sqrt{\sigma^2}$ è la **deviazione standard**, nelle stesse unità di $X$. ⚠️ La traccia dà **sempre la varianza**, e a te serve $\sigma$: "varianza 100" $\Rightarrow\sigma=10$, non 100.
- **Standardizzare** significa trasformare una Normale qualunque nella standard con $Z=\dfrac{X-\mu}{\sigma}$: si **centra** (sottrai la media, così lo zero cade sul centro) e si **riscala** (dividi per $\sigma$, così l'unità di misura diventa "una deviazione standard"). Fatto questo, ogni probabilità su $X$ si legge come una $\Phi$.
E il **TLC** (caso 2 qui sotto): la somma di **tante** variabili i.i.d. — qualunque sia la loro distribuzione di partenza — è **approssimativamente Normale**, quindi si standardizza la somma e si usa $\Phi$ lo stesso.
### Le due situazioni possibili
**1. $X$ è già Normale** — la traccia dice «sia $X$ una variabile aleatoria Normale con media $\mu$ e varianza $\sigma^2$». Si standardizza e basta: il risultato è un'**uguaglianza esatta**.
**2. $X_1,X_2,\dots$ sono i.i.d. qualsiasi** — la traccia dà solo media e varianza, oppure una distribuzione non normale, e chiede una probabilità sulla **somma** di tante di esse. Qui interviene il **teorema del limite centrale**: la somma standardizzata è approssimativamente Normale standard, e il risultato resta un'**approssimazione** ($\approx$), mai un'uguaglianza esatta.

> [!info] Come riconoscere il caso 2 a colpo d'occhio
> Compaiono $X_1+\cdots+X_n$ con $n$ grande ($100$, $900$, $10^6$), oppure un $\lim_{n\to\infty}$. La parola chiave nella traccia è **«con l'approssimazione Normale»** o **«i.i.d.»**.

### Le formule
La traccia apre **sempre** definendo $\Phi(y)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{y}e^{-x^{2}/2}dx$, la funzione di distribuzione della Normale standard.
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
3. **Manipolare la disuguaglianza** sottraendo $n\mu$ e dividendo per $\sigma\sqrt{n}$ **a tutti i membri**, estremi compresi, fino a isolare la somma standardizzata.
4. **Sostituire con $\Phi$**, ricordando che $P(Z>z)=1-\Phi(z)$: $\Phi$ dà sempre la coda sinistra.
5. **Ridurre ad argomenti positivi** con $\Phi(-x)=1-\Phi(x)$, se la traccia lo chiede.
### Esercizi svolti — formato 2025-2026
#### Limite con TLC — appello del 6 Febbraio 2026
Sia $\{X_n\}$ i.i.d. con media 2 e varianza 9. Calcolare
$$\lim_{n\to\infty}P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)$$
esprimendo il risultato con $\Phi$.
**Svolgimento**
**Passo 1 — riconoscere il caso.** La traccia dà $X_1,X_2,\dots$ i.i.d. (non una singola $X$ già Normale) e chiede una probabilità sulla **somma** $X_1+\cdots+X_n$ con $n\to\infty$: sono esattamente i due segnali del caso 2 — somma di tante variabili i.i.d. **e** un $\lim_{n\to\infty}$. Serve quindi il **teorema del limite centrale**, non la standardizzazione diretta di una Normale. Di regola il TLC dà solo un'**approssimazione** ($\approx$) a $n$ fissato; ma qui non ci si ferma a $n$ fissato, si prende il limite per $n\to\infty$, e in quel limite l'errore di approssimazione del TLC tende a zero: il risultato finale sarà quindi un'**uguaglianza esatta** ($=$), non un'approssimazione.

**Passo 2 — trovare $\sigma$ dalla varianza.** La traccia dà sempre la **varianza**, mai la deviazione standard:
$$\sigma=\sqrt{\operatorname{Var}(X)}.$$
Qui la varianza della singola $X_i$ è 9, quindi $\sigma=\sqrt9=3$; la media è già quella della singola variabile, $\mu=2$.

**Passo 3 — media e deviazione standard della somma.** Per il TLC, se $X_i$ sono i.i.d. con media $\mu$ e varianza $\sigma^2$, la somma $S_n=X_1+\cdots+X_n$ ha
$$E[S_n]=n\mu,\qquad \operatorname{d.s.}(S_n)=\sigma\sqrt n$$
— **mai** $\sigma^2\sqrt n$ né $\sigma n$: al denominatore va sempre $\sigma\sqrt n$. Con $\mu=2$ e $\sigma=3$:
$$n\mu=2n,\qquad \sigma\sqrt n=3\sqrt n.$$

**Passo 4 — standardizzare la disuguaglianza.** Il TLC in formula generale dice
$$P(S_n\le s)\approx\Phi\!\left(\frac{s-n\mu}{\sigma\sqrt n}\right),$$
cioè: si sottrae la media della somma e si divide per la sua deviazione standard, **a tutti i membri della disuguaglianza**, per isolare la somma standardizzata. Qui l'evento è una coda destra, $S_n>2n+\sqrt{n}$: si sottrae $2n$ e si divide per $3\sqrt n$ a entrambi i membri:
$$P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)=P\big(X_1+\cdots+X_n-2n>\sqrt{n}\big)=P\left(\frac{X_1+\cdots+X_n-2n}{3\sqrt{n}}>\frac{\sqrt{n}}{3\sqrt{n}}\right).$$

**Passo 5 — il rapporto non dipende da $n$.** A destra della disuguaglianza,
$$\frac{\sqrt n}{3\sqrt n}=\frac13\qquad\text{per ogni }n,$$
la $\sqrt n$ si semplifica e resta una costante che **non dipende da $n$**. È per questo che il limite esiste finito: se l'argomento di $\Phi$ dipendesse ancora da $n$, bisognerebbe studiarne il limite separatamente; qui è già un numero fisso, $\frac13$, per ogni $n$.

**Passo 6 — applicare il TLC e passare al limite.** A sinistra della disuguaglianza c'è esattamente la somma standardizzata, che per il TLC converge alla Normale standard $Z$ quando $n\to\infty$. Ricordando che $\Phi$ dà sempre la coda sinistra, quindi
$$P(Z>z)=1-\Phi(z),$$
e usando che l'argomento resta $\frac13$ per ogni $n$ (Passo 5):
$$\lim_{n\to\infty}P\big(X_1+\cdots+X_n>2n+\sqrt{n}\big)=P\left(Z>\frac13\right)=1-\Phi\!\left(\frac13\right).$$
Essendo un limite — e non un'approssimazione a $n$ fissato — l'uguaglianza è esatta, coerentemente con quanto notato nel Passo 1.

Il $\sqrt n$ nella traccia non è decorativo: è tarato sulla scala del TLC, dove le fluttuazioni della somma attorno alla media sono dell'ordine di $\sigma\sqrt n$. Se al posto di $\sqrt n$ ci fosse, ad esempio, $n$ — soglia $2n+n=3n$ — l'argomento diventerebbe
$$\frac{n}{3\sqrt n}=\frac{\sqrt n}{3}\;\longrightarrow\;\infty,$$
e il limite degenererebbe a $0$. Se invece ci fosse una **costante fissa** $c$ — soglia $2n+c$ — l'argomento diventerebbe
$$\frac{c}{3\sqrt n}\;\longrightarrow\;0,$$
e il limite diventerebbe $P(Z>0)=1-\Phi(0)=\frac12$: un valore fisso che non dipende più dalla soglia scelta, quindi altrettanto poco informativo. Solo la scala $\sigma\sqrt n$ restituisce, nel limite, il valore intermedio non banale $\frac13$ che compare nel risultato.
#### Intervallo e riduzione ad argomenti positivi — appello del 20 Febbraio 2026
Siano $X_1,\dots,X_{900}$ i.i.d. con media 1 e varianza 100. Calcolare $P(700<X_1+\cdots+X_{900}<800)$ con l'approssimazione Normale, esprimendo il risultato con $\Phi$ ad argomenti positivi.
**Svolgimento**
**Passo 1 — riconoscere il caso.** La traccia parla di $X_1,\dots,X_{900}$ **i.i.d.** — tante variabili indipendenti e identicamente distribuite — e chiede una probabilità sulla loro **somma** di $n=900$ termini, esplicitando «con l'approssimazione Normale»: sono esattamente i segnali del secondo caso richiamati in [[#Le due situazioni possibili|questa nota]]. Non c'è nessuna singola variabile già Normale da standardizzare: il risultato dovrà quindi restare un'**approssimazione** ($\approx$) fornita dal teorema del limite centrale, mai un'uguaglianza esatta.

**Passo 2 — momenti della singola variabile.** La traccia dà, per ciascuna $X_i$, media $\mu=1$ e **varianza** $\sigma^2=100$. La varianza non è la deviazione standard: va estratta la radice, come richiamato nel promemoria di questa nota,
$$\sigma=\sqrt{\sigma^2}=\sqrt{100}=10$$
Confondere $\sigma^2$ con $\sigma$ a questo punto propagherebbe l'errore a tutti i passi successivi.

**Passo 3 — media e deviazione standard della somma.** Per il [[#Le formule|teorema del limite centrale]], la somma $S_n=X_1+\cdots+X_n$ di $n$ variabili i.i.d. con media $\mu$ e varianza $\sigma^2$ ha media $n\mu$ e deviazione standard $\sigma\sqrt n$ — **non** $\sigma^2\sqrt n$ né $\sigma n$:
$$E[S_n]=n\mu\qquad \text{DevStd}(S_n)=\sigma\sqrt n$$
Qui $n=900$, quindi
$$n\mu=900\cdot1=900\qquad \sigma\sqrt n=10\cdot\sqrt{900}=10\cdot30=300$$

**Passo 4 — standardizzare la disuguaglianza.** Per ricondursi alla somma standardizzata si sottrae $n\mu$ e si divide per $\sigma\sqrt n$ a **tutti i membri** della disuguaglianza, estremi compresi:
$$P(a<S_n<b)\approx P\left(\frac{a-n\mu}{\sigma\sqrt n}<Z<\frac{b-n\mu}{\sigma\sqrt n}\right)$$
con $Z$ Normale standard. Qui $a=700$, $b=800$, $n\mu=900$, $\sigma\sqrt n=300$:
$$P(700<S_{900}<800)=P\left(\frac{700-900}{300}<\frac{S_{900}-900}{300}<\frac{800-900}{300}\right)=P\left(-\frac{2}{3}<Z<-\frac{1}{3}\right)$$
Sostituendo con $\Phi$ — che è sempre la coda sinistra, $P(Z\le z)=\Phi(z)$ — e ricordando che il TLC dà solo un'approssimazione:
$$\approx\Phi\!\left(-\frac{1}{3}\right)-\Phi\!\left(-\frac{2}{3}\right)$$

**Passo 5 — ridurre ad argomenti positivi.** Entrambi gli argomenti, $-\frac13$ e $-\frac23$, sono **negativi**: la somma osservata (fra 700 e 800) è sotto la media 900. Si applica a ciascuno la simmetria della Normale standard richiamata fra le [[#Le formule|formule]] di questa nota,
$$\Phi(-x)=1-\Phi(x)$$
che legge la coda sinistra fino a $-x$ come uno meno la coda sinistra fino a $x$. Sostituendo:
$$\Phi\!\left(-\frac{1}{3}\right)-\Phi\!\left(-\frac{2}{3}\right)=\left(1-\Phi\!\left(\frac{1}{3}\right)\right)-\left(1-\Phi\!\left(\frac{2}{3}\right)\right)=\Phi\!\left(\frac{2}{3}\right)-\Phi\!\left(\frac{1}{3}\right)$$
I due $1$ si cancellano e i due termini si **scambiano di posto**: chi era sottratto, $\frac23$, passa davanti, e chi era davanti, $\frac13$, passa dietro. Il risultato resta un'approssimazione del teorema del limite centrale, non un'uguaglianza esatta:
$$P(700<X_1+\cdots+X_{900}<800)\approx\Phi\!\left(\frac{2}{3}\right)-\Phi\!\left(\frac{1}{3}\right)$$

> [!question] Attenzione all'ordine dopo il ribaltamento
> Passando agli argomenti positivi i due termini si **scambiano**: si parte da $\Phi(-1/3)-\Phi(-2/3)$ e si arriva a $\Phi(2/3)-\Phi(1/3)$. Il risultato deve restare positivo, essendo una probabilità: è il controllo immediato per sapere se hai sbagliato il verso.

#### Coda destra con media nulla — appello del 19 Giugno 2026
Siano $X_1,\dots,X_{10^6}$ i.i.d. con media 0 e varianza 9. Calcolare $P(X_1+\cdots+X_{10^6}>10^3)$.
**Svolgimento**
	**Passo 1 — riconoscere il caso: Normale esatta o TLC?** La traccia parla di $X_1,\dots,X_{10^6}$ **i.i.d.** e chiede una probabilità sulla loro **somma**, con $n=10^6$ molto grande: sono esattamente i segnali del caso 2 (non il caso 1, in cui $X$ sarebbe già Normale). Serve quindi il **teorema del limite centrale**, e il risultato resterà un'**approssimazione** ($\approx$), mai un'uguaglianza esatta.

**Passo 2 — ricavare $\sigma$ dalla varianza.** La traccia dà la **varianza**, $9$, non $\sigma$: si estrae la radice,
$$\sigma=\sqrt{9}=3$$
mentre la media della singola $X_i$ è $\mu=0$.

**Passo 3 — media e deviazione standard della somma $S_n$.** Per il TLC, se $S_n=X_1+\cdots+X_n$ con gli $X_i$ i.i.d. di media $\mu$ e varianza $\sigma^2$, allora $S_n$ ha media $n\mu$ e deviazione standard $\sigma\sqrt{n}$ — non $\sigma^2\sqrt n$ né $\sigma n$. Qui $n=10^6$, quindi
$$n\mu=10^{6}\cdot0=0\qquad\qquad\sigma\sqrt{n}=3\sqrt{10^{6}}=3\cdot10^{3}$$
dove $\sqrt{10^{6}}=10^{3}$: la traccia sceglie $n$ come quadrato perfetto proprio per rendere pulita questa radice.

**Passo 4 — standardizzare la disuguaglianza.** Si sottrae la media della somma, $n\mu$, e si divide per la deviazione standard della somma, $\sigma\sqrt n$, a **entrambi i membri** della disuguaglianza. Con media nulla il passaggio è ancora più corto: sottrarre $0$ non cambia nulla, resta solo la divisione:
$$P\big(X_1+\cdots+X_{10^{6}}>10^{3}\big)=P\left(\frac{S-0}{3\cdot10^{3}}>\frac{10^{3}-0}{3\cdot10^{3}}\right)=P\left(Z>\frac{1}{3}\right)$$

**Passo 5 — sostituire con $\Phi$, attenti alla coda destra.** $\Phi$ dà sempre la **coda sinistra**, cioè $P(Z\le z)=\Phi(z)$; la coda destra è il suo complemento, $P(Z>z)=1-\Phi(z)$. Poiché il passaggio parte dal TLC, il segno resta $\approx$:
$$P\big(X_1+\cdots+X_{10^{6}}>10^{3}\big)\approx1-\Phi\!\left(\frac{1}{3}\right)$$
### Esercizi svolti — varianti dagli appelli precedenti
#### Normale "pura", senza TLC — appello del 12 Luglio 2022
Sia $X$ Normale con media 2 e varianza 25. Calcolare $P(3\le X\le4)$ esprimendo il risultato con $\Phi$.
**Svolgimento**
**Passo 1 — riconoscere il caso: $X$ è già Normale, non il TLC.** La traccia dice esplicitamente che $X$ è Normale con media e varianza assegnate: non compare nessuna somma $X_1+\cdots+X_n$, nessun $n$ grande, nessun $\lim$. Siamo quindi nel [[#Le due situazioni possibili|caso 1]] e non nel caso 2 del teorema del limite centrale: si standardizza $X$ direttamente, senza passare per nessuna somma di v.a. i.i.d., e il risultato sarà un'**uguaglianza esatta** ($=$), mai un'approssimazione.

**Passo 2 — identificare $\mu$ e $\sigma$, senza confondere $\sigma$ con la varianza.** La traccia dà $\mu=2$ e la **varianza** $\sigma^2=25$: come richiamato nell'[[#Le formule|avviso sulla varianza]], $\sigma$ è la radice della varianza, non la varianza stessa. Quindi
$$\sigma=\sqrt{25}=5$$
Confondere $\sigma$ con la varianza $25$ e dividere per $25$ invece che per $5$ è l'errore più comune di questo tipo di esercizio.

**Passo 3 — richiamare la formula generale per un intervallo.** Per $X$ Normale con media $\mu$ e varianza $\sigma^2$, la probabilità di un intervallo si scrive sempre come **differenza di due $\Phi$**, una per ciascun estremo, [[#Le formule|come richiamato fra le formule]]:
$$P(a<X<b)=\Phi\!\left(\frac{b-\mu}{\sigma}\right)-\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$
Si legge così: si standardizza ciascun estremo sottraendo $\mu$ e dividendo per $\sigma$, e si prende la differenza fra il $\Phi$ dell'estremo superiore e il $\Phi$ dell'estremo inferiore, mai il contrario.

**Passo 4 — sostituire i valori della traccia.** Qui l'estremo inferiore è $a=3$, l'estremo superiore $b=4$, e da $X$ si hanno $\mu=2$, $\sigma=5$ (Passo 2). Sostituendo nella formula del Passo 3:
$$P(3\le X\le4)=\Phi\!\left(\frac{4-2}{5}\right)-\Phi\!\left(\frac{3-2}{5}\right)=\Phi\!\left(\frac{2}{5}\right)-\Phi\!\left(\frac{1}{5}\right)$$

**Passo 5 — controllare gli argomenti: già positivi, niente simmetria.** Entrambi gli argomenti $\frac{2}{5}$ e $\frac{1}{5}$ sono **già positivi**: non serve applicare la simmetria $\Phi(-x)=1-\Phi(x)$ richiamata nel [[#Il procedimento passo per passo|procedimento generale]], perché quel passaggio si usa solo quando compare un $\Phi$ con argomento negativo, e qui non c'è. Il risultato resta quindi
$$P(3\le X\le4)=\Phi\!\left(\frac{2}{5}\right)-\Phi\!\left(\frac{1}{5}\right)$$
come uguaglianza esatta fra $X$ e la sua standardizzata, senza alcuna approssimazione del teorema del limite centrale.
#### Normale standard con un estremo negativo — appello del 20 Giugno 2023
Sia $X$ Normale standard. Calcolare $P\!\left(-1\le X\le\frac{3}{2}\right)$ con $\Phi$ ad argomenti positivi.
**Svolgimento**
**Passo 1 — riconoscere il caso.** Non compaiono somme $X_1+\cdots+X_n$, né $\lim_{n\to\infty}$, né la parola "i.i.d.": $X$ è dichiarata direttamente **Normale standard**, cioè già Normale. Siamo nel **caso 1**: si standardizza (se serve) e il risultato è un'**uguaglianza esatta**, mai un'approssimazione — niente $\approx$ da scrivere.

**Passo 2 — leggere i parametri.** In generale, se $X$ ha media $\mu$ e varianza $\sigma^2$, si standardizza con
$$P(X\le a)=\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$
"Normale standard" è per definizione la Normale con $\mu=0$ e $\sigma^2=1$, quindi $\sigma=\sqrt{1}=1$. Con $\mu=0$ e $\sigma=1$ la formula sopra diventa $P(X\le a)=\Phi(a)$: la standardizzazione è già fatta, non c'è nessuna sottrazione né divisione da eseguire.

**Passo 3 — applicare la formula dell'intervallo.** Per un intervallo vale in generale
$$P(a<X<b)=\Phi\!\left(\frac{b-\mu}{\sigma}\right)-\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$
Qui $a=-1$, $b=\frac{3}{2}$, e per il Passo 2 gli argomenti restano $b$ e $a$ così come sono:
$$P\left(-1\le X\le\frac{3}{2}\right)=\Phi\!\left(\frac{3}{2}\right)-\Phi(-1)$$

**Passo 4 — isolare l'argomento negativo.** Il primo termine, $\Phi\!\left(\frac{3}{2}\right)$, ha già argomento positivo e si lascia com'è. Il secondo, $\Phi(-1)$, ha argomento negativo: si applica la simmetria
$$\Phi(-x)=1-\Phi(x)$$
con $x=1$, ottenendo $\Phi(-1)=1-\Phi(1)$.

**Passo 5 — sostituire e semplificare il segno.** Sostituendo nel Passo 3:
$$P\left(-1\le X\le\frac{3}{2}\right)=\Phi\!\left(\frac{3}{2}\right)-\big(1-\Phi(1)\big)=\Phi\!\left(\frac{3}{2}\right)+\Phi(1)-1$$
Il $-\big(1-\Phi(1)\big)$ distribuisce il segno meno su entrambi i termini della parentesi, cambiandoli: il $+1$ diventa $-1$ e il $-\Phi(1)$ diventa $+\Phi(1)$. Il risultato non è più una differenza fra due $\Phi$, ma una **somma meno 1**: è quello che succede sempre quando gli estremi dell'intervallo stanno **a cavallo dello zero** (uno negativo, uno positivo), perché ribaltare il termine negativo lo trasforma in un $+\Phi(\cdot)$ anziché in un $-\Phi(\cdot)$.
#### Distribuzione data invece dei momenti — appello del 12 Luglio 2022
Sia $\{X_n\}$ i.i.d. con distribuzione **esponenziale** di parametro $\lambda>0$, cioè $f(x)=\lambda e^{-\lambda x}\mathbb{1}_{(0,\infty)}(x)$. Verificare che per ogni $z\in\mathbb{R}$
$$\lim_{n\to\infty}P\left(\frac{X_1+\cdots+X_n-\frac{n}{\lambda}}{\frac{\sqrt{n}}{\lambda}}\le z\right)=\Phi(z)$$
**Svolgimento**
**Passo 1 — riconoscere il caso: qui serve il TLC, non la standardizzazione diretta.** La traccia non parla di un'unica $X$ già Normale, ma di $\{X_n\}$ i.i.d. e chiede il comportamento della somma $X_1+\cdots+X_n$ dentro un $\lim_{n\to\infty}$: sono esattamente i segnali del [[#Le due situazioni possibili|caso 2]] di questa nota (i.i.d., somma di tante variabili, limite per $n$ che tende a infinito). Si tratta dunque di un'applicazione del teorema del limite centrale, e non della standardizzazione esatta che si userebbe se $X$ fosse già Normale.

**Passo 2 — la traccia dà una distribuzione, non media e varianza: vanno ricavate.** Ogni $X_i$ ha densità esponenziale di parametro $\lambda$, $f(x)=\lambda e^{-\lambda x}\mathbb{1}_{(0,\infty)}(x)$: non compaiono direttamente $\mu$ e $\sigma^2$, quindi il primo passo è calcolarli dalla distribuzione, come richiamato nel [[#Il procedimento passo per passo|procedimento]] di questa nota. Per l'esponenziale di parametro $\lambda$ valgono
$$\mu=E[X]=\frac{1}{\lambda}\qquad\qquad\sigma^{2}=\mathrm{Var}[X]=\frac{1}{\lambda^{2}}$$
da cui, ricordando che $\sigma$ è sempre la radice della varianza e mai la varianza stessa,
$$\sigma=\sqrt{\sigma^{2}}=\sqrt{\frac{1}{\lambda^{2}}}=\frac{1}{\lambda}$$

**Passo 3 — scrivere media e deviazione standard della somma $S_n=X_1+\cdots+X_n$, secondo il TLC.** Il [[#Le formule|teorema del limite centrale]] dice che, per $n$ variabili i.i.d. con media $\mu$ e varianza $\sigma^2$, la somma ha sempre
$$\text{media della somma}=n\mu\qquad\qquad\text{deviazione standard della somma}=\sigma\sqrt{n}$$
— mai $\sigma^2\sqrt{n}$ né $\sigma n$ al denominatore. Sostituendo i valori trovati al Passo 2,
$$n\mu=n\cdot\frac{1}{\lambda}=\frac{n}{\lambda}\qquad\qquad\sigma\sqrt{n}=\frac{1}{\lambda}\cdot\sqrt{n}=\frac{\sqrt{n}}{\lambda}$$

**Passo 4 — confrontare con l'espressione della traccia: è già la somma standardizzata.** La somma standardizzata si costruisce sempre sottraendo alla somma la sua media e dividendo per la sua deviazione standard, esattamente come nel [[#Il procedimento passo per passo|procedimento]] generale di questa nota:
$$\frac{S_n-n\mu}{\sigma\sqrt{n}}$$
Sostituendo i due valori appena trovati al Passo 3,
$$\frac{S_n-n\mu}{\sigma\sqrt{n}}=\frac{X_1+\cdots+X_n-\dfrac{n}{\lambda}}{\dfrac{\sqrt{n}}{\lambda}}$$
che è **esattamente** l'espressione scritta nella traccia. A differenza degli altri esercizi di questa nota, qui non c'è nessuna disuguaglianza da manipolare sottraendo o dividendo membro a membro agli estremi: il testo ha già fatto quel lavoro, presentando direttamente la somma standardizzata.

**Passo 5 — applicare il TLC e concludere.** La forma generale del teorema dice che, per $n$ grande, la somma standardizzata si distribuisce approssimativamente come una Normale standard,
$$P\left(\frac{S_n-n\mu}{\sigma\sqrt{n}}\le z\right)\approx\Phi(z)$$
e questa è un'approssimazione valida per $n$ fissato. Ma qui la traccia chiede proprio il **limite** per $n\to\infty$: passando al limite, l'approssimazione diventa l'affermazione esatta del teorema del limite centrale, valida per ogni $z\in\mathbb{R}$:
$$\lim_{n\to\infty}P\left(\frac{X_1+\cdots+X_n-\dfrac{n}{\lambda}}{\dfrac{\sqrt{n}}{\lambda}}\le z\right)=\Phi(z)$$
il che verifica esattamente quanto richiesto dalla traccia.

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
**Passo 1 — riconoscere il caso: qui non serve il TLC.** La traccia dice esplicitamente «$X$ Normale con media 2 e varianza $\sigma^2$»: non compare nessuna somma $X_1+\cdots+X_n$, nessun $\lim_{n\to\infty}$, nessuna famiglia di v.a. i.i.d. — $X$ è **già** Normale. Significa che qualunque probabilità su $X$ si ottiene standardizzando **esattamente**, senza passare per il teorema del limite centrale: il risultato finale sarà un'uguaglianza ($=$), non un'approssimazione ($\approx$). La deviazione standard resta però simbolica, $\sigma=\sqrt{\sigma^{2}}$: la traccia non fornisce un valore numerico della varianza, quindi $\sigma$ accompagnerà tutto il calcolo (e infatti, come si vedrà, sparirà dal risultato finale).

**Passo 2 — impostare la condizionata con la sua definizione.** La quantità richiesta è una probabilità condizionata: si parte sempre dalla definizione generale
$$P(A\mid B)=\frac{P(A\cap B)}{P(B)}$$
e si sostituisce $A=\{X<2\}$, $B=\{0<X<y\}$:
$$P(X<2\mid 0<X<y)=\frac{P\big(\{X<2\}\cap\{0<X<y\}\big)}{P(0<X<y)}$$
Prima di poter usare $\Phi$ occorre quindi capire cos'è l'evento al numeratore.

**Passo 3 — semplificare l'intersezione sfruttando l'ipotesi $y>2$.** L'evento $\{X<2\}\cap\{0<X<y\}$ raccoglie i valori che soddisfano **entrambe** le condizioni, $X<2$ e $0<X<y$. Siccome per ipotesi $y>2$, l'intervallo $(0,y)$ contiene già tutto $(0,2)$ al proprio interno; imporre in più $X<2$ non fa che tagliare $(0,y)$ esattamente in $2$:
$$\{X<2\}\cap\{0<X<y\}=\{0<X<2\}$$
Se invece fosse $y\le2$ questo taglio non ci sarebbe, ed è proprio per questo che la traccia impone il vincolo $y>2$. Sostituendo nella definizione del Passo 2:
$$P(X<2\mid 0<X<y)=\frac{P(0<X<2)}{P(0<X<y)}$$

**Passo 4 — standardizzare numeratore e denominatore con la stessa formula.** Numeratore e denominatore sono entrambi probabilità su un intervallo della stessa $X\sim N(2,\sigma^2)$, quindi si usa la [[#Le formule|formula dell'intervallo standardizzato]] con $\mu=2$:
$$P(a<X<b)=\Phi\!\left(\frac{b-\mu}{\sigma}\right)-\Phi\!\left(\frac{a-\mu}{\sigma}\right)$$
Applicandola a $P(0<X<2)$ (cioè $a=0,\,b=2$) e a $P(0<X<y)$ (cioè $a=0,\,b=y$):
$$P(0<X<2)=\Phi\!\left(\frac{2-2}{\sigma}\right)-\Phi\!\left(\frac{0-2}{\sigma}\right)=\Phi(0)-\Phi\!\left(-\frac2\sigma\right)$$
$$P(0<X<y)=\Phi\!\left(\frac{y-2}{\sigma}\right)-\Phi\!\left(\frac{0-2}{\sigma}\right)=\Phi\!\left(\frac{y-2}{\sigma}\right)-\Phi\!\left(-\frac2\sigma\right)$$
L'estremo $b=2$ dà $\Phi(0)$ perché $2-\mu=2-2=0$: va semplificato subito, e $\Phi(0)=0{,}5$ perché la Normale standard è simmetrica attorno a $0$, che ne divide la massa di probabilità esattamente a metà.

**Passo 5 — eliminare l'argomento negativo con la simmetria.** L'argomento $-\frac2\sigma$ è negativo (perché $\sigma>0$), e le tavole di $\Phi$ si leggono solo per argomenti positivi: serve quindi la simmetria della Normale standard attorno a $0$,
$$\Phi(-x)=1-\Phi(x)$$
applicata con $x=\frac2\sigma$:
$$\Phi\!\left(-\frac2\sigma\right)=1-\Phi\!\left(\frac2\sigma\right)$$
Sostituendo questa uguaglianza e $\Phi(0)=0{,}5$ nelle due espressioni del Passo 4:
$$P(0<X<2)=0{,}5-\left(1-\Phi\!\left(\frac2\sigma\right)\right)=\Phi\!\left(\frac2\sigma\right)-0{,}5$$
$$P(0<X<y)=\Phi\!\left(\frac{y-2}{\sigma}\right)-\left(1-\Phi\!\left(\frac2\sigma\right)\right)=\Phi\!\left(\frac2\sigma\right)+\Phi\!\left(\frac{y-2}{\sigma}\right)-1$$

**Passo 6 — scrivere l'equazione nell'incognita $y$.** Sostituendo numeratore e denominatore appena trovati nella condizionata del Passo 3, e imponendo che valga $\frac12$ come chiede la traccia:
$$\frac12=P(X<2\mid0<X<y)=\frac{\Phi\!\left(\frac2\sigma\right)-0{,}5}{\Phi\!\left(\frac2\sigma\right)+\Phi\!\left(\frac{y-2}{\sigma}\right)-1}$$

**Passo 7 — moltiplicare in croce e isolare $\Phi\!\left(\frac{y-2}{\sigma}\right)$.** Moltiplicando entrambi i membri per il denominatore (una probabilità, quindi diverso da zero) e poi per $2$:
$$\Phi\!\left(\frac2\sigma\right)+\Phi\!\left(\frac{y-2}{\sigma}\right)-1=2\left(\Phi\!\left(\frac2\sigma\right)-0{,}5\right)=2\Phi\!\left(\frac2\sigma\right)-1$$
Sommando $1$ a entrambi i membri e portando $\Phi\!\left(\frac2\sigma\right)$ a destra:
$$\Phi\!\left(\frac{y-2}{\sigma}\right)=2\Phi\!\left(\frac2\sigma\right)-\Phi\!\left(\frac2\sigma\right)=\Phi\!\left(\frac2\sigma\right)$$
L'equazione nell'incognita $y$ si è ridotta a un confronto fra due valori della stessa funzione $\Phi$.

**Passo 8 — usare l'invertibilità di $\Phi$ per uguagliare gli argomenti.** $\Phi(z)=P(Z\le z)$ è la funzione di distribuzione di una Normale standard — la probabilità **cumulata a sinistra** di $z$, non quella a destra — ed è **strettamente crescente** su tutta la retta: una funzione strettamente crescente è iniettiva, cioè assume ogni valore **al più una volta**. Vale quindi, in generale,
$$\Phi(a)=\Phi(b)\ \Longrightarrow\ a=b$$
non basta che i due valori "sembrino" uguali, è la stretta monotonia a garantirlo. Applicandolo ai due argomenti del Passo 7:
$$\frac{2}{\sigma}=\frac{y-2}{\sigma}$$

**Passo 9 — risolvere per $y$.** Poiché $\sigma>0$, si moltiplicano entrambi i membri per $\sigma$ senza cambiare il verso dell'uguaglianza, e i due $\sigma$ si semplificano:
$$2=y-2\ \Longrightarrow\ y=4$$
Il valore trovato soddisfa il vincolo $y>2$ richiesto dalla traccia, quindi la soluzione esiste ed è accettabile. Da notare che $\sigma$ è **sparita** dal risultato finale: la risposta non dipende dalla varianza, ed è proprio questo a segnalare che il conto è impostato correttamente.

> [!info] La scorciatoia, come controllo
> Il risultato si vede anche senza conti: la Normale è **simmetrica** attorno alla media, che qui è 2, quindi la condizionata vale $\frac{1}{2}$ esattamente quando l'intervallo $(0,y)$ è centrato in 2 — cioè $\frac{0+y}{2}=2$, da cui $y=4$. Coerente col fatto che $\sigma$ sparisce dal risultato.
>
> Sull'elaborato conviene comunque scrivere il passaggio algebrico: l'argomento di simmetria è ottimo per verificare, meno per convincere chi corregge.

### Collegamenti
- $\Phi$ è la funzione di distribuzione della Normale standard: stessa nozione di [[Es4 - Trasformazione di variabile continua|Es4]], ma tabulata una volta per tutte.
- Media e varianza in ingresso: [[Es5 - Speranza di variabile continua]] per le continue, [[Es1 - Probabilità discreta elementare]] per le discrete.
