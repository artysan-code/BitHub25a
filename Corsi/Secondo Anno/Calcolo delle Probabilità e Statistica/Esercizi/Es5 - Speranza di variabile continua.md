## Es5 — Speranza di variabile continua
Quinto esercizio dello scritto: data una densità continua $f_X$ (spesso la stessa di [[Es4 - Trasformazione di variabile continua|Es4]]), si chiede una speranza matematica, tipicamente $E[X^2]$ oppure $E\!\left[\frac{1}{X^2}\right]$.
### Prima di tutto: cos'è la speranza
La **speranza** $E[X]$ (o "valore atteso") è la **media pesata** dei valori di $X$, dove ogni valore conta quanto è probabile. Due cose da fissare in testa:
- **È un numero, non una funzione.** L'operazione $E[\,\cdot\,]$ prende *tutta* la variabile e restituisce **un solo numero**: dentro l'integrale la $x$ viene "sommata via" e sparisce. Al contrario di $F_Y(y)$ in [[Es4 - Trasformazione di variabile continua|Es4]], che resta una funzione di $y$.
- **Tre modi di leggerla**: la *media a lungo termine* (ripeti l'esperimento tante volte e fai la media dei risultati); il *baricentro* della densità (il punto in cui il profilo di massa sta in equilibrio); il *valore che ti aspetti*.
Nel discreto $E[X]=\sum_x x\,p_X(x)$; nel continuo la somma diventa l'integrale della prossima sezione.
### Come leggere $g$ dalla traccia
La funzione $g$ **non si sceglie**: è scritta dentro le parentesi di $E[\cdots]$. Prendi ciò che sta dentro, sostituisci $X$ con $x$, e quello è $g(x)$.

| La traccia chiede | $g(x)$ è |
|---|---|
| $E[X]$ (media semplice) | $x$ |
| $E[X^2]$ | $x^2$ |
| $E\!\left[1/X^2\right]$ | $1/x^2$ |
| $E[X^r e^X]$ | $x^r e^x$ |

> [!warning] La trappola numero uno: $E[g(X)]\ne g(E[X])$
> La media di una funzione **non** è la funzione della media: $E[X^2]\ne(E[X])^2$ e $E\!\left[\frac1{X^2}\right]\ne\frac1{E[X]^2}$. Devi mettere $g$ **dentro** l'integrale, non calcolare prima $E[X]$ e poi applicargli $g$. La differenza fra $E[X^2]$ e $(E[X])^2$ è esattamente la [[#Formule di appoggio|varianza]].

### L'unica formula che serve
$$E[g(X)]=\int_{-\infty}^{+\infty}g(x)f_X(x)\,dx$$

> [!info] Non serve passare per $f_Y$
> Per calcolare $E[g(X)]$ **non** occorre prima trovare la densità di $Y=g(X)$ come si fa in [[Es4 - Trasformazione di variabile continua|Es4]]: si integra direttamente $g(x)f_X(x)$.
>
> Le due strade danno lo stesso risultato, ma la seconda è molto più lunga. Se una traccia chiede prima $F_Y$ e poi $E[Y]$, la seconda parte si può comunque fare per la via breve, ignorando quanto trovato prima.

In pratica l'integrale si calcola **solo sul supporto** di $f_X$, perché fuori la densità è nulla:
$$E[g(X)]=\int_{a}^{b}g(x)f_X(x)\,dx$$
Casi frequenti: $g(x)=x$ (media), $g(x)=x^2$, $g(x)=\frac{1}{x^2}$, $g(x)=x^re^{x}$.
### Formule di appoggio
**Linearità** — vale sempre, anche senza indipendenza:
$$E[c_1X_1+c_2X_2]=c_1E[X_1]+c_2E[X_2]$$
**Varianza** — se servisse ricavarla da $E[X^2]$:
$$\text{Var}[X]=E[X^2]-\big(E[X]\big)^2$$
**Uniforme su $(a,b)$** — densità costante $\frac{1}{b-a}$, media $\frac{a+b}{2}$, varianza $\frac{(b-a)^2}{12}$.
**Integrali che ricorrono**:
$$\int x^{n}dx=\frac{x^{n+1}}{n+1}\ (n\ne-1)\qquad \int\frac{1}{x^{2}}dx=-\frac{1}{x}\qquad \int e^{x}dx=e^{x}$$
### Esercizi svolti — formato 2025-2026
#### $E[X^2]$ con densità triangolare — appelli del 6 Febbraio e del 19 Giugno 2026
Sia $f_X(x)=2(1-x)\mathbb{1}_{(0,1)}(x)$. Calcolare $E[X^2]$.
**Svolgimento**
**Passo 1 — riconoscere la formula e restringerla al supporto.** La speranza di una funzione di $X$ si calcola sempre con l'unica formula di apertura di questa nota:
$$E[g(X)]=\int_{-\infty}^{+\infty}g(x)f_X(x)\,dx$$
qui $g(x)=x^2$. A differenza di [[Es4 - Trasformazione di variabile continua|Es4]], non serve prima trovare la densità di $Y=X^2$: si integra direttamente il prodotto $g(x)f_X(x)$. La traccia dà $f_X(x)=2(1-x)\mathbb{1}_{(0,1)}(x)$: fuori dall'intervallo $(0,1)$ la densità vale $0$, quindi quella parte di dominio non contribuisce affatto all'integrale, e resta solo
$$E[X^{2}]=\int_{0}^{1}x^{2}\cdot2(1-x)\,dx$$

**Passo 2 — impostare il prodotto $g(x)f_X(x)$, senza perdere la costante di normalizzazione.** Il fattore $2$ davanti a $(1-x)$ non è un dettaglio decorativo: è la costante di normalizzazione che rende $f_X$ una densità vera, cioè quella che garantisce $\int_{0}^{1}2(1-x)\,dx=2\left[x-\frac{x^{2}}{2}\right]_{0}^{1}=2\left(1-\frac12\right)=1$. Dimenticarla per strada è uno degli errori più comuni: va portata dentro il prodotto esattamente come farebbe qualunque altro fattore. Prima di integrare conviene quindi scrivere per esteso il prodotto fra la funzione richiesta e la densità, invece di lanciarsi subito nel calcolo: $g(x)=x^2$ moltiplicato per $f_X(x)=2(1-x)$ dà
$$x^{2}\cdot2(1-x)=2x^{2}(1-x)=2\left(x^{2}-x^{3}\right)$$
Distribuire il prodotto trasforma l'integrale in quello di un **polinomio**, cioè in un calcolo elementare: non serve integrazione per parti né sostituzioni, basta la regola $\int x^{n}dx=\frac{x^{n+1}}{n+1}$ già richiamata fra le [[#Formule di appoggio|formule di appoggio]] di questa nota.

**Passo 3 — calcolare l'integrale elementare.** Sostituendo il prodotto appena espanso,
$$E[X^{2}]=\int_{0}^{1}2\left(x^{2}-x^{3}\right)dx=2\int_{0}^{1}\left(x^{2}-x^{3}\right)dx=2\left[\frac{x^{3}}{3}-\frac{x^{4}}{4}\right]_{0}^{1}$$
In $x=0$ entrambi i termini della primitiva si annullano, quindi conta solo la valutazione in $x=1$:
$$E[X^{2}]=2\left(\frac{1}{3}-\frac{1}{4}\right)=2\cdot\frac{1}{12}=\frac{1}{6}$$

**Passo 4 — non confondere $E[X^2]$ con $(E[X])^2$.** Anche qui si annida l'errore concettuale più insidioso di questo esercizio: $E[g(X)]\ne g(E[X])$, cioè la speranza di una funzione **non** è la funzione della speranza. Per convincersene basta calcolare $E[X]$ con la stessa formula generale del Passo 1, questa volta con $g(x)=x$:
$$E[X]=\int_{0}^{1}x\cdot2(1-x)\,dx=2\int_{0}^{1}\left(x-x^{2}\right)dx=2\left[\frac{x^{2}}{2}-\frac{x^{3}}{3}\right]_{0}^{1}=2\left(\frac12-\frac13\right)=\frac13$$
Se si elevasse al quadrato questo valore si otterrebbe $(E[X])^{2}=\left(\frac13\right)^{2}=\frac19$, un numero **diverso** da $\frac16$: la differenza fra i due, come richiamato nelle [[#Formule di appoggio|formule di appoggio]] di questa nota, è esattamente $\text{Var}[X]$.

> [!question] Questo esercizio è caduto due volte, identico
> Stessa densità, stessa richiesta, stesso risultato negli appelli di **febbraio e giugno 2026**. Non è una coincidenza isolata: è il motivo per cui il drill sugli appelli rende più della teoria. Vedi [[Es1 - Probabilità discreta elementare|Es1]] per altri esempi di ripetizione.

#### $E[1/X^2]$ con uniforme — appello del 20 Febbraio 2026
Sia $X\sim U(1,5)$. Calcolare $E\!\left[\frac{1}{X^{2}}\right]$.
**Svolgimento**
**Passo 1 — leggere la densità di $X$.** La traccia dà $X\sim U(1,5)$: è una v.a. uniforme sull'intervallo $(1,5)$. Per la [[#Formule di appoggio|densità uniforme]], la densità di $U(a,b)$ è **costante e vale $\frac{1}{b-a}$, non $1$** — errore frequente da evitare fin da subito. Qui $a=1$ e $b=5$, quindi
$$f_X(x)=\begin{cases}\dfrac{1}{5-1}=\dfrac14 & \text{se } 1<x<5\\ 0 & \text{altrimenti}\end{cases}$$

**Passo 2 — applicare la formula generale, ristretta al supporto.** Per calcolare $E\!\left[\frac1{X^2}\right]$ si parte da [[#L'unica formula che serve|l'unica formula di questo esercizio]]:
$$E[g(X)]=\int_{-\infty}^{+\infty}g(x)f_X(x)\,dx$$
che si legge così: si moltiplica la funzione $g$ per la densità di $X$ e si integra su tutta la retta reale. Ma siccome $f_X$ è nulla fuori da $(1,5)$ (Passo 1), i due tratti esterni dell'integrale valgono $0$ e non contribuiscono: l'integrale si può quindi restringere **al solo supporto**,
$$E[g(X)]=\int_{1}^{5}g(x)f_X(x)\,dx$$
Qui $g(x)=\dfrac{1}{x^2}$, dunque
$$E\!\left[\frac1{X^2}\right]=\int_1^5 \frac{1}{x^2}\,f_X(x)\,dx$$

**Passo 3 — impostare il prodotto $g\cdot f_X$ e isolare la costante.** Si sostituisce l'espressione di $f_X$ trovata al Passo 1 dentro l'integrale:
$$\frac{1}{x^2}\cdot f_X(x)=\frac1{x^2}\cdot\frac14$$
La costante $\frac14$ non dipende da $x$: si porta fuori dal segno di integrale, e resta soltanto l'integrale elementare di $\frac1{x^2}$ — non serve nessuna sostituzione o integrazione per parti:
$$E\!\left[\frac1{X^2}\right]=\int_1^5\frac1{x^2}\cdot\frac14\,dx=\frac14\int_1^5\frac{1}{x^2}\,dx$$

**Passo 4 — calcolare l'integrale.** Usando la primitiva $\int\frac{1}{x^{2}}dx=-\frac1x$ richiamata fra le [[#Formule di appoggio|formule di appoggio]]:
$$\frac14\int_1^5\frac1{x^2}\,dx=\frac14\left[-\frac1x\right]_1^5=\frac14\left(-\frac15-\left(-\frac11\right)\right)=\frac14\left(1-\frac15\right)=\frac14\cdot\frac45=\frac15$$
Quindi $E\!\left[\dfrac1{X^2}\right]=\dfrac15$. Si noti che la costante di normalizzazione $\frac14$ dell'uniforme è rimasta nel conto fino in fondo, come ci si aspetta.

**Passo 5 — l'errore concettuale da non commettere.** Un errore molto comune è calcolare $\dfrac{1}{E[X]^2}$ al posto di $E\!\left[\dfrac1{X^2}\right]$, cioè applicare $g$ **dopo** aver preso la speranza invece che prima: ma la speranza di una funzione **non** è la funzione della speranza,
$$E[g(X)]\ne g\big(E[X]\big)$$
Qui $E[X]=\dfrac{1+5}{2}=3$ (media dell'uniforme, ancora dalle [[#Formule di appoggio|formule di appoggio]]), quindi
$$\frac{1}{E[X]^2}=\frac{1}{3^2}=\frac19$$
un valore **diverso** da $\frac15$ trovato al Passo 4, e quindi **sbagliato** come risposta a questa domanda. I due calcoli — $E\!\left[\frac1{X^2}\right]$ e $\frac{1}{E[X]^2}$ — misurano cose diverse e coincidono solo nel caso degenere in cui $X$ è costante; qui $X$ è uniforme su un intervallo, quindi non coincidono.
### Esercizi svolti — varianti dagli appelli precedenti
Fino al 2024-25 questo non era uno slot autonomo, ma la seconda domanda (`D8`) dell'esercizio sulle variabili continue — le tracce sotto vengono da lì.
#### Il fattore che si semplifica con la densità — appello del 20 Febbraio 2025
Sia $f_X(x)=\frac{e^{-x}}{1-e^{-b}}\mathbb{1}_{(0,b)}(x)$ e sia $r>0$. Verificare che $E[X^{r}e^{X}]=\frac{b^{r+1}}{(r+1)(1-e^{-b})}$.
**Svolgimento**
**Passo 1 — la formula, ristretta al supporto.** Vale sempre $E[g(X)]=\int_{-\infty}^{+\infty}g(x)f_X(x)\,dx$, ma qui la densità $f_X(x)=\frac{e^{-x}}{1-e^{-b}}\mathbb{1}_{(0,b)}(x)$ è diversa da zero solo su $(0,b)$: fuori da quell'intervallo l'indicatrice annulla $f_X$ e l'integrando è nullo, quindi non contribuisce. L'integrale su tutta la retta si riduce così al solo supporto, con $g(x)=x^{r}e^{x}$:

$$E[X^{r}e^{X}]=\int_{0}^{b}x^{r}e^{x}\,f_X(x)\,dx$$

**Passo 2 — l'errore da evitare prima di calcolare.** Verificare l'uguaglianza richiesta significa integrare direttamente $g\cdot f_X$: non si può ottenere il risultato sostituendo $E[X]$ dentro $g$, perché $E[g(X)]\ne g(E[X])$. Qui l'espressione tentatrice sarebbe $(E[X])^{r}e^{E[X]}$: non coincide col risultato corretto e va scartata a priori, esattamente come $\frac{1}{E[X]^2}$ non è $E\!\left[\frac{1}{X^2}\right]$.

**Passo 3 — sostituire la densità e scrivere il prodotto $g\cdot f_X$.** Sostituendo l'espressione di $f_X$ nell'integrale del Passo 1:

$$E[X^{r}e^{X}]=\int_{0}^{b}x^{r}e^{x}\cdot\frac{e^{-x}}{1-e^{-b}}\,dx$$

**Passo 4 — la semplificazione che la traccia nasconde.** Nel prodotto compaiono $e^{x}$, portato da $g$, ed $e^{-x}$, portato dalla densità: sono l'uno il reciproco dell'altro, quindi $e^{x}\cdot e^{-x}=1$ e si cancellano. Resta solo la costante di normalizzazione $\frac{1}{1-e^{-b}}$, che non dipende da $x$ e si porta fuori dal segno di integrale:

$$E[X^{r}e^{X}]=\frac{1}{1-e^{-b}}\int_{0}^{b}x^{r}\,dx$$

Senza questa cancellazione l'integrale sarebbe quello di una potenza per un esponenziale, da trattare per parti; con la cancellazione diventa la primitiva elementare di $x^{r}$. È questo il punto attorno a cui è costruita la traccia.

**Passo 5 — calcolare l'integrale elementare rimasto.** Per $r>0$ vale $\int x^{r}\,dx=\frac{x^{r+1}}{r+1}$ (formula di appoggio già enunciata sopra), quindi

$$\int_{0}^{b}x^{r}\,dx=\left[\frac{x^{r+1}}{r+1}\right]_{0}^{b}=\frac{b^{r+1}}{r+1}-\frac{0^{r+1}}{r+1}=\frac{b^{r+1}}{r+1}$$

L'estremo inferiore contribuisce $0$, perché $r+1>0$ rende $0^{r+1}=0$.

**Passo 6 — rimettere la costante di normalizzazione e concludere.** Si moltiplica il risultato del Passo 5 per la costante $\frac{1}{1-e^{-b}}$ lasciata in sospeso al Passo 4:

$$E[X^{r}e^{X}]=\frac{1}{1-e^{-b}}\cdot\frac{b^{r+1}}{r+1}=\frac{b^{r+1}}{(r+1)(1-e^{-b})}$$

che è esattamente il risultato da verificare. La costante di normalizzazione non scompare: resta nel denominatore del risultato finale, come capita spesso quando la densità è troncata su un intervallo finito invece che definita su tutta la retta.

> [!info] Guardare la coppia $g\cdot f_X$ prima di integrare
> Le tracce sono costruite perché il prodotto $g(x)f_X(x)$ si semplifichi in qualcosa di elementare. Se l'integrale che stai per fare sembra difficile — integrazione per parti, sostituzioni — quasi certamente hai sbagliato a impostarlo.

#### Risultato che non dipende dal parametro — appello del 3 Febbraio 2025
Sia $\alpha>0$ e $f_X(x)=\alpha x^{\alpha-1}\mathbb{1}_{(0,1)}(x)$. Sia $r>0$. Calcolare $E[X^{\alpha r}]$ e verificare che non dipende da $\alpha$.
**Svolgimento**
**Passo 1 — riconoscere $g$, $f_X$ e il supporto, e richiamare [[#L'unica formula che serve|la formula generale]].** Per qualunque funzione $g$ vale sempre
$$E[g(X)]=\int_{-\infty}^{+\infty}g(x)f_X(x)\,dx=\int_{a}^{b}g(x)f_X(x)\,dx$$
dove $(a,b)$ è il supporto di $f_X$: fuori da lì la densità è nulla, quindi quel pezzo di integrale vale $0$ e non serve scriverlo. Qui $g(x)=x^{\alpha r}$ e $f_X(x)=\alpha x^{\alpha-1}\mathbb{1}_{(0,1)}(x)$, con supporto $(0,1)$ — e qui $\alpha$ non è solo l'esponente: è anche la **costante di normalizzazione** della densità, quella che rende $\int_0^1\alpha x^{\alpha-1}\,dx=\big[x^{\alpha}\big]_0^1=1$. Lo stesso $\alpha$ ricomparirà, e si cancellerà, al Passo 4. Quindi
$$E[X^{\alpha r}]=\int_{0}^{1}x^{\alpha r}\cdot\alpha x^{\alpha-1}\,dx$$
Attenzione a non cadere nell'errore concettuale più comune di questo tipo di esercizio: $E[X^{\alpha r}]$ **non** è $\big(E[X]\big)^{\alpha r}$. Non si calcola prima $E[X]$ per poi elevarlo alla potenza $\alpha r$ — la speranza di una funzione di $X$ non è la funzione della speranza di $X$ — va integrato per intero il prodotto $g(x)f_X(x)$, come scritto sopra.

**Passo 2 — impostare il prodotto $g\cdot f_X$ e sommare gli esponenti.** La costante $\alpha$ non dipende da $x$ e si porta fuori dal segno di integrale; resta il prodotto di due potenze di $x$ con la stessa base, che si moltiplicano **sommando gli esponenti**:
$$x^{\alpha r}\cdot x^{\alpha-1}=x^{\alpha r+(\alpha-1)}=x^{\alpha(r+1)-1}$$
(si è raccolto $\alpha$ nei primi due termini dell'esponente: $\alpha r+\alpha=\alpha(r+1)$, e resta il $-1$ isolato). Sostituendo,
$$E[X^{\alpha r}]=\alpha\int_{0}^{1}x^{\alpha(r+1)-1}\,dx$$
Questa è esattamente la semplificazione che la traccia nasconde: il prodotto $g(x)f_X(x)$, che a prima vista sembra avere $\alpha$ e $r$ intrecciati in modo complicato, collassa in un'unica potenza di $x$ — un integrale elementare, non una tecnica di integrazione avanzata.

**Passo 3 — calcolare l'integrale con la formula delle potenze.** Posto $n=\alpha(r+1)-1$ (che è $\ne-1$ perché $\alpha>0$ e $r>0$), la primitiva è $\int x^{n}dx=\dfrac{x^{n+1}}{n+1}=\dfrac{x^{\alpha(r+1)}}{\alpha(r+1)}$, quindi
$$E[X^{\alpha r}]=\alpha\left[\frac{x^{\alpha(r+1)}}{\alpha(r+1)}\right]_{0}^{1}$$

**Passo 4 — valutare agli estremi e semplificare la $\alpha$.** All'estremo superiore $x=1$ si ha $1^{\alpha(r+1)}=1$; all'estremo inferiore $x=0$ l'esponente $\alpha(r+1)$ è **positivo** (perché $\alpha>0$ e $r+1>0$), quindi $0^{\alpha(r+1)}=0$ e quel termine sparisce. Resta
$$E[X^{\alpha r}]=\alpha\cdot\frac{1-0}{\alpha(r+1)}=\frac{\alpha}{\alpha(r+1)}$$
A questo punto la $\alpha$ portata fuori dall'integrale al Passo 2 si **cancella** esattamente con la $\alpha$ comparsa al denominatore per effetto dell'integrazione (quella dentro $n+1=\alpha(r+1)$):
$$E[X^{\alpha r}]=\frac{1}{r+1}$$

**Passo 5 — verificare che il risultato non dipende da $\alpha$.** Nell'espressione finale $\frac{1}{r+1}$ compare solo $r$: $\alpha$ è scomparsa, esattamente come chiedeva la traccia. Quando una traccia dice **«verificare che non dipende da …»**, sta indicando la strada per controllare il proprio conto: se alla fine il parametro incriminato è ancora presente nel risultato, c'è un errore di algebra da qualche parte — quasi sempre nella cancellazione del Passo 4.
### Trappole ricorrenti
- **$E[g(X)]\ne g(E[X])$**: è l'errore concettuale più grave. $E\!\left[\frac{1}{X^2}\right]$ non è $\frac{1}{E[X]^2}$, $E[X^2]$ non è $\big(E[X]\big)^2$ — la differenza fra i due è esattamente la varianza.
- **Integrare fuori dal supporto**: gli estremi sono quelli dell'indicatrice $\mathbb{1}_{(a,b)}$, non $\pm\infty$.
- **Dimenticare la costante di normalizzazione** della densità: va moltiplicata, e spesso è proprio lei a comparire nel risultato finale.
- **Uniforme**: la densità è $\frac{1}{b-a}$, non 1. Con $U(1,5)$ vale $\frac{1}{4}$.
- **Semplificazioni mancate**: se il prodotto $g(x)f_X(x)$ non diventa un integrale elementare, ricontrollare l'impostazione prima di lanciarsi in tecniche di integrazione.
### Collegamenti
- Stessa densità, richiesta diversa: [[Es4 - Trasformazione di variabile continua]].
- Media e varianza nel discreto: [[Es1 - Probabilità discreta elementare]], che ha la tabella delle distribuzioni notevoli.
- [[Es6 - Normale e teorema del limite centrale]] usa media e varianza come **input** per standardizzare: se sbagli qui, sbagli anche lì.
