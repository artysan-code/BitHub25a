## Es5 — Speranza di variabile continua
Quinto esercizio dello scritto, e il più corto dei sei: viene data una densità continua $f_X$ e si chiede una speranza matematica, tipicamente $E[X^2]$ oppure $E\!\left[\frac{1}{X^2}\right]$.

È un esercizio da **due righe**: una formula e un integrale elementare. Nel formato fino al 2024-25 non esisteva come slot autonomo — era la seconda domanda dell'esercizio sulle variabili continue — quindi negli appelli vecchi lo si trova come `D8)`.
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

$$E[X^{2}]=\int_{0}^{1}x^{2}\,2(1-x)\,dx=2\int_{0}^{1}\left(x^{2}-x^{3}\right)dx=2\left[\frac{x^{3}}{3}-\frac{x^{4}}{4}\right]_{0}^{1}=2\left(\frac{1}{3}-\frac{1}{4}\right)=2\cdot\frac{1}{12}=\frac{1}{6}$$

> [!question] Questo esercizio è caduto due volte, identico
> Stessa densità, stessa richiesta, stesso risultato negli appelli di **febbraio e giugno 2026**. Non è una coincidenza isolata: è il motivo per cui il drill sugli appelli rende più della teoria. Vedi [[Es1 - Probabilità discreta elementare|Es1]] per altri esempi di ripetizione.

#### $E[1/X^2]$ con uniforme — appello del 20 Febbraio 2026
Sia $X\sim U(1,5)$. Calcolare $E\!\left[\frac{1}{X^{2}}\right]$.

**Svolgimento**

La densità di una uniforme su $(1,5)$ è costante e vale $\frac{1}{5-1}=\frac{1}{4}$:

$$E\left[\frac{1}{X^{2}}\right]=\int_{1}^{5}\frac{1}{x^{2}}\cdot\frac{1}{4}\,dx=\frac{1}{4}\left[-\frac{1}{x}\right]_{1}^{5}=\frac{1}{4}\left(1-\frac{1}{5}\right)=\frac{1}{4}\cdot\frac{4}{5}=\frac{1}{5}$$

L'errore da evitare è calcolare $\frac{1}{E[X]^2}$: la speranza di una funzione **non** è la funzione della speranza. Qui $E[X]=3$ darebbe $\frac{1}{9}$, che è sbagliato.
### Esercizi svolti — varianti dagli appelli precedenti
#### Il fattore che si semplifica con la densità — appello del 20 Febbraio 2025
Sia $f_X(x)=\frac{e^{-x}}{1-e^{-b}}\mathbb{1}_{(0,b)}(x)$ e sia $r>0$. Verificare che $E[X^{r}e^{X}]=\frac{b^{r+1}}{(r+1)(1-e^{-b})}$.

**Svolgimento**

La funzione da integrare contiene $e^{X}$ e la densità contiene $e^{-x}$: i due si **cancellano**, e l'integrale diventa elementare.

$$E[X^{r}e^{X}]=\int_{0}^{b}x^{r}e^{x}\frac{e^{-x}}{1-e^{-b}}dx=\frac{1}{1-e^{-b}}\int_{0}^{b}x^{r}dx=\frac{1}{1-e^{-b}}\left[\frac{x^{r+1}}{r+1}\right]_{0}^{b}=\frac{b^{r+1}}{(r+1)(1-e^{-b})}$$

> [!info] Guardare la coppia $g\cdot f_X$ prima di integrare
> Le tracce sono costruite perché il prodotto $g(x)f_X(x)$ si semplifichi in qualcosa di elementare. Se l'integrale che stai per fare sembra difficile — integrazione per parti, sostituzioni — quasi certamente hai sbagliato a impostarlo.

#### Risultato che non dipende dal parametro — appello del 3 Febbraio 2025
Sia $\alpha>0$ e $f_X(x)=\alpha x^{\alpha-1}\mathbb{1}_{(0,1)}(x)$. Sia $r>0$. Calcolare $E[X^{\alpha r}]$ e verificare che non dipende da $\alpha$.

**Svolgimento**

$$E[X^{\alpha r}]=\int_{0}^{1}x^{\alpha r}\,\alpha x^{\alpha-1}dx=\alpha\int_{0}^{1}x^{\alpha(r+1)-1}dx=\alpha\left[\frac{x^{\alpha(r+1)}}{\alpha(r+1)}\right]_{0}^{1}=\frac{\alpha}{\alpha(r+1)}=\frac{1}{r+1}$$

Gli esponenti si sommano — $x^{\alpha r}\cdot x^{\alpha-1}=x^{\alpha(r+1)-1}$ — e la $\alpha$ davanti si semplifica esattamente con quella che compare integrando. Il risultato dipende solo da $r$, come chiedeva la traccia.

Quando una traccia dice **«verificare che non dipende da …»**, sta indicando la strada: se alla fine il parametro è ancora lì, c'è un errore di algebra.
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
