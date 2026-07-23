## Es3 — Densità congiunta discreta
Terzo esercizio dello scritto: la traccia **regala** la densità congiunta $p_{X_1,X_2}(x_1,x_2)$ di due variabili aleatorie discrete e chiede di ricavarne qualcosa — una probabilità su un evento che coinvolge entrambe, una marginale, una condizionata, o la densità di una trasformazione $Y=g(X_1,X_2)$. Tutto l'esercizio è **sommare la densità sulle coppie giuste**, e riconoscere le serie che ne escono.
### Prima di tutto: cos'è una densità congiunta (e il legame con Es4)
Hai **due** variabili discrete $X_1,X_2$. La densità congiunta $p_{X_1,X_2}(x_1,x_2)=P(X_1=x_1\ \text{e}\ X_2=x_2)$ è la probabilità che le due cose accadano **insieme**: immaginala come una **tabella di pesi**, un peso per ogni coppia di valori. Due regole fisse: **tutti i pesi sommano a 1**, e la densità **vive solo su certe coppie** (il *supporto*) — su tutte le altre vale $0$.
È il **cugino discreto di [[Es4 - Trasformazione di variabile continua|Es4]]**: là *integravi* una densità su una regione, qui **sommi** una densità su un insieme di coppie. Stessa idea — accumulare probabilità sulla zona giusta — con la somma al posto dell'integrale.
### Riconoscere quale delle 4 richieste è
La prima mossa su ogni Es3 è capire in quale delle quattro richieste cadi: il **segnale** è nel testo della traccia.

| Cosa leggi nella richiesta | Richiesta | Cosa fai |
|---|---|---|
| "$p$ di $X_1$", "la marginale" | Marginale | sommi via l'altra variabile |
| "$P(\dots)$" **senza** barra (es. $P(X_1>X_2)$) | Evento | elenchi le coppie e sommi |
| "$P(\dots\mid\dots)$" **con la barra** | Condizionata | $\dfrac{P(A\cap B)}{P(B)}$ |
| "la densità di $Y=g(X_1,X_2)$" | Trasformazione | raggruppi le coppie per valore di $Y$ |

La barra $\mid$ vuol dire *"sapendo che"* (sinonimi: "dato che", "condizionato a"): appena la vedi → condizionata. Una condizionata è comunque **due** somme di pesi (numeratore $A\cap B$, denominatore $B$), cioè due "eventi" uno sopra l'altro.
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
Quando il supporto è infinito, la somma diventa una serie, e Macci ne usa sempre le stesse due.
**Serie esponenziale** — è quella della [[Distribuzioni uniforme discreta e di Poisson#Distribuzione di Poisson|Poisson]]:
$$\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda}$$
**Serie geometrica** — dimostrata in [[Distribuzione geometrica#Formula della serie geometrica|serie geometrica]]:
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
**Passo 1 — riconoscere la formula generale della condizionata.** La richiesta $P(X_1=X_2\mid X_2=0)$ è una probabilità condizionata fra due eventi costruiti sulla coppia $(X_1,X_2)$, quindi si parte dalla definizione di sempre:
$$P(A\mid B)=\frac{P(A\cap B)}{P(B)}$$
Si legge così: al numeratore la probabilità che **entrambi** gli eventi accadano insieme, al denominatore la probabilità dell'evento condizionante da solo. Qui $A=\{X_1=X_2\}$ (la diagonale) e $B=\{X_2=0\}$ (la riga orizzontale $x_2=0$); per il principio generale di Es3, sia $P(A\cap B)$ sia $P(B)$ si ottengono sommando la densità congiunta $p_{X_1,X_2}$ sulle coppie che soddisfano rispettivamente $A\cap B$ e $B$.

**Passo 2 — mappare il supporto a pezzi.** La densità è definita solo su due sottoinsiemi del piano, e vale **zero** su ogni coppia non elencata:
$$p_{X_1,X_2}(k,k)=q\frac{2^{k}}{k!}e^{-2}\ (k\ge0)\qquad p_{X_1,X_2}(h,0)=(1-q)\frac{3^{h-1}}{(h-1)!}e^{-3}\ (h\ge1)$$
Il primo pezzo vive sulla **diagonale** $x_1=x_2=k$, il secondo sulla **riga** $x_2=0,\ x_1=h\ge1$. Le due rette, disegnate nel piano, si incrociano nel punto $(0,0)$: ma il ramo diagonale, con $k=0$, lo copre già, mentre il ramo di riga parte da $h\ge1$ e **non** ridefinisce $(0,0)$. Non c'è quindi doppio conteggio, ma c'è un punto in cui serve attenzione: quando si elencano le coppie con $x_2=0$, la coppia $(0,0)$ va presa dal ramo diagonale, e le coppie $(h,0)$ con $h\ge1$ dal ramo di riga — dimenticare la prima, o cercarla nel ramo di riga (dove non è definita), è l'errore tipico su questo tipo di supporto.

**Passo 3 — individuare le coppie del numeratore, $\{X_1=X_2\}\cap\{X_2=0\}$.** Imporre insieme $x_1=x_2$ e $x_2=0$ forza $x_1=x_2=0$: nessun'altra coppia del supporto soddisfa entrambe le condizioni, perché le coppie di riga $(h,0)$ con $h\ge1$ hanno $x_1=h\ne0=x_2$ e quindi non stanno sulla diagonale. Resta la sola coppia $(0,0)$, presa dal ramo diagonale del Passo 2:
$$P(\{X_1=X_2\}\cap\{X_2=0\})=p_{X_1,X_2}(0,0)=q\frac{2^{0}}{0!}e^{-2}=qe^{-2}$$

**Passo 4 — individuare le coppie del denominatore, $\{X_2=0\}$.** Qui basta la sola condizione $x_2=0$, senza vincoli su $x_1$: dal Passo 2 questa riga raccoglie $(0,0)$ dal ramo diagonale **più** tutte le $(h,0)$ con $h\ge1$ dal ramo di riga — due famiglie distinte, che si sommano:
$$P(X_2=0)=\underbrace{p_{X_1,X_2}(0,0)}_{\text{ramo diagonale}}+\sum_{h\ge1}\underbrace{p_{X_1,X_2}(h,0)}_{\text{ramo di riga}}=qe^{-2}+(1-q)\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}e^{-3}$$

**Passo 5 — riconoscere e risolvere la serie di [[Distribuzioni uniforme discreta e di Poisson#Distribuzione di Poisson|Poisson]].** Il fattore $e^{-3}$ non dipende dall'indice $h$ e si porta fuori dalla somma:
$$\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}e^{-3}=e^{-3}\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}$$
La somma superstite ha la stessa forma della serie esponenziale della Poisson, ma non parte da $h=0$: la forma generale è
$$\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda}$$
Per riportarcisi si pone $j=h-1$: al variare di $h$ da 1 in su, $j$ varia da 0 in su, quindi la serie si riporta alla forma standard con $\lambda=3$:
$$\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}=\sum_{j\ge0}\frac{3^{j}}{j!}=e^{3}$$
Il cambio di indice sposta solo il punto di partenza della somma, non toglie alcun termine: il risultato è **esattamente** $e^{3}$, non $e^{3}-1$. Rimoltiplicando per il fattore $e^{-3}$ messo da parte,
$$e^{-3}\sum_{j\ge0}\frac{3^{j}}{j!}=e^{-3}e^{3}=1$$
e il motivo per cui viene esattamente 1 è che $\sum_{j\ge0}\frac{3^{j}}{j!}e^{-3}$ è la densità di Poisson di parametro 3 sommata su **tutto** il suo supporto $\{0,1,2,\dots\}$: ogni densità completa somma a 1. Quindi
$$P(X_2=0)=qe^{-2}+(1-q)\cdot1=qe^{-2}+1-q$$

**Passo 6 — comporre la condizionata.** Si sostituiscono numeratore (Passo 3) e denominatore (Passo 5) nella formula del Passo 1:
$$P(X_1=X_2\mid X_2=0)=\frac{qe^{-2}}{qe^{-2}+1-q}$$
Il risultato resta in forma letterale: è normale, la traccia non dà valori numerici per $q$.
#### Densità di $Y=X_1X_2$ su supporto finito — appello del 20 Febbraio 2026
Densità congiunta: $p_{X_1,X_2}(x_1,x_2)=\frac{1}{10}$ per $(x_1,x_2)\in\{(0,0),(0,1),(0,2),(1,0),(2,0)\}$, e $p_{X_1,X_2}(1,1)=p_{X_1,X_2}(2,2)=\frac{1}{4}$.
Trovare la densità discreta di $Y=X_1X_2$.
**Svolgimento**
**Passo 1 — riconoscere il tipo di richiesta.** La traccia chiede "la densità discreta di $Y=X_1X_2$": non è né una marginale, né la probabilità di un singolo evento, né una condizionata, ma il quarto caso delle [[#Le quattro richieste possibili|quattro richieste possibili]] di questo esercizio — la densità di una **trasformazione** $Y=g(X_1,X_2)$, qui con $g(x_1,x_2)=x_1x_2$. La formula generale è
$$p_Y(y)=\sum_{(x_1,x_2)\,:\,g(x_1,x_2)=y}p_{X_1,X_2}(x_1,x_2).$$
Si legge così: per ogni valore $y$ che $Y$ può assumere, si **raggruppano** tutte le coppie $(x_1,x_2)$ del supporto congiunto che danno $g(x_1,x_2)=y$, e si somma la loro densità congiunta. È [[#L'unico principio che serve|il principio unico]] dell'esercizio, $P((X_1,X_2)\in A)=\sum_{(x_1,x_2)\in A}p_{X_1,X_2}(x_1,x_2)$, applicato con $A=\{(x_1,x_2):g(x_1,x_2)=y\}$.

**Passo 2 — individuare il supporto.** Prima di sommare bisogna sapere *dove* la densità non è zero: sulle coppie non elencate dalla traccia $p_{X_1,X_2}$ vale $0$, quindi solo le coppie elencate possono contribuire. Qui il supporto è composto da **sette** coppie in tutto, divise in due gruppi con valore diverso:
$$p_{X_1,X_2}(0,0)=p_{X_1,X_2}(0,1)=p_{X_1,X_2}(0,2)=p_{X_1,X_2}(1,0)=p_{X_1,X_2}(2,0)=\frac{1}{10},\qquad p_{X_1,X_2}(1,1)=p_{X_1,X_2}(2,2)=\frac{1}{4}.$$
Qualunque altra coppia — ad esempio $(1,2)$ o $(3,0)$ — non compare nell'elenco, vale $0$ e non entra in nessuna somma.

**Passo 3 — calcolare $g$ su ciascuna delle sette coppie e raggruppare.** Si applica $g(x_1,x_2)=x_1x_2$ a turno su tutte e sette le coppie del Passo 2:
$$0\cdot0=0\qquad0\cdot1=0\qquad0\cdot2=0\qquad1\cdot0=0\qquad2\cdot0=0\qquad1\cdot1=1\qquad2\cdot2=4.$$
Le prime cinque coppie — tutte quelle con **almeno uno dei due indici uguale a zero** — danno lo stesso prodotto $0$ e si raggruppano nel valore $y=0$; la coppia $(1,1)$ è l'unica che dà $y=1$; la coppia $(2,2)$ è l'unica che dà $y=4$. Nessuna coppia del supporto produce altri valori, quindi $Y$ assume **solo** $0,1,4$: un valore come $y=2$ o $y=3$ non è raggiungibile, perché nessuna delle sette coppie lo produce.

**Passo 4 — sommare la densità dentro ciascun gruppo.** Si applica ora la formula del Passo 1 ai tre gruppi appena trovati: per $y=0$ la somma ha **cinque** addendi (uno per ciascuna coppia con prodotto nullo), tutti di densità $\frac{1}{10}$; per $y=1$ e $y=4$ la somma ha un solo addendo ciascuna, presi dal secondo gruppo del Passo 2:
$$p_Y(0)=\underbrace{\frac{1}{10}+\frac{1}{10}+\frac{1}{10}+\frac{1}{10}+\frac{1}{10}}_{5\text{ coppie con }g=0}=5\cdot\frac{1}{10}=\frac{1}{2}\qquad p_Y(1)=\frac{1}{4}\qquad p_Y(4)=\frac{1}{4}.$$

**Passo 5 — controllo finale.** Gli eventi $\{Y=0\}$, $\{Y=1\}$, $\{Y=4\}$ sono disgiunti e la loro unione è **tutto** il supporto: ciascuna delle sette coppie di partenza contribuisce a uno e un solo gruppo, e la somma delle sette densità congiunte vale $1$ perché è l'intera densità di $(X_1,X_2)$. Quindi anche $p_Y$, ripartendo esattamente quella stessa massa fra $0,1,4$, deve sommare a $1$:
$$p_Y(0)+p_Y(1)+p_Y(4)=\frac{1}{2}+\frac{1}{4}+\frac{1}{4}=1.$$
Il conto torna: nessuna delle sette coppie è stata dimenticata né contata due volte.

> [!info] Il controllo che costa dieci secondi
> $\frac{1}{2}+\frac{1}{4}+\frac{1}{4}=1$. Quando la richiesta è **la densità di $Y$**, la somma dei valori trovati deve fare 1 — se non torna, hai perso una coppia o ne hai contata una due volte.

#### Marginale e coda — appello del 19 Giugno 2026
Siano $q\in(0,1)$ e $\lambda>0$. Densità congiunta:
$$p_{X_1,X_2}(x_1,x_2)=(1-q^2)^{x_1}q^2\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}e^{-\lambda}\qquad\text{per }x_2\ge x_1\ge0$$
Calcolare $P(X_1\ge k)$ per $k\ge0$ intero.
**Svolgimento**
**Passo 1 — riconoscere il problema: due variabili, un solo evento.** L'evento richiesto, $\{X_1\ge k\}$, riguarda solo $X_1$, ma la densità di cui disponiamo è quella **congiunta** $p_{X_1,X_2}(x_1,x_2)$, definita sul supporto bidimensionale $x_2\ge x_1\ge0$. Per il principio unico di Es3,
$$P(X_1\ge k)=\sum_{(x_1,x_2)\,:\,x_1\ge k}p_{X_1,X_2}(x_1,x_2),$$
la somma dovrebbe scorrere su **entrambi** gli indici contemporaneamente: per ogni $x_1\ge k$, tutti gli $x_2\ge x_1$ ammessi dal supporto. Conviene spezzare il lavoro in due tempi: prima **eliminare** $x_2$ sommando la densità congiunta su tutti i suoi valori a $x_1$ fissato — cioè calcolare la **marginale** di $X_1$ — e solo dopo sommare la marginale (che dipende da un solo indice) sui valori $x_1\ge k$.

**Passo 2 — la formula generale della marginale.** Per definizione,
$$p_{X_1}(x_1)=\sum_{x_2}p_{X_1,X_2}(x_1,x_2).$$
Si legge così: fissato un valore di $x_1$, si percorrono **tutti** i valori di $x_2$ compatibili con il supporto e si sommano i corrispondenti valori della densità congiunta; il risultato non dipende più da $x_2$, che è stato "fatto sparire" dalla somma.

**Passo 3 — applicare al supporto di questa traccia.** Il supporto è $x_2\ge x_1\ge0$: fissato $x_1$, la variabile $x_2$ percorre tutti gli interi da $x_1$ in poi, cioè $x_2\in\{x_1,x_1+1,x_1+2,\dots\}$ — per ogni $x_2<x_1$ la densità vale zero e non contribuisce. Quindi
$$p_{X_1}(x_1)=\sum_{x_2\ge x_1}(1-q^2)^{x_1}q^2\,\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}e^{-\lambda}.$$
I fattori $(1-q^2)^{x_1}q^2$ ed $e^{-\lambda}$ **non dipendono da $x_2$**: rispetto alla somma su $x_2$ sono entrambi costanti, quindi si portano insieme fuori dal segno di somma:
$$p_{X_1}(x_1)=(1-q^2)^{x_1}q^2\,e^{-\lambda}\sum_{x_2\ge x_1}\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}.$$

**Passo 4 — cambio di indice e serie esponenziale.** La somma rimasta non è ancora nella forma standard $\sum_{h\ge0}\frac{\lambda^h}{h!}$: l'esponente e il fattoriale contengono $x_2-x_1$, e l'indice di somma $x_2$ parte da $x_1$, non da $0$. Si pone $h=x_2-x_1$: quando $x_2=x_1$ si ha $h=0$, e ogni incremento di $1$ in $x_2$ produce lo stesso incremento in $h$, quindi $x_2\ge x_1$ equivale esattamente a $h\ge0$. La **serie esponenziale** generale — la stessa che compare nella normalizzazione di una densità di Poisson — è
$$\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda},$$
motivo per cui una densità di Poisson completa somma sempre a 1: $\sum_{h\ge0}\frac{\lambda^h}{h!}e^{-\lambda}=e^{-\lambda}e^{\lambda}=1$. Con la sostituzione $h=x_2-x_1$, la somma rimasta nel Passo 3 è esattamente questa serie:
$$\sum_{x_2\ge x_1}\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}=\sum_{h\ge0}\frac{\lambda^{h}}{h!}=e^{\lambda}.$$
Il fattore $e^{-\lambda}$, già portato fuori nel Passo 3, si cancella esattamente con questo $e^{\lambda}$:
$$p_{X_1}(x_1)=(1-q^2)^{x_1}q^2\cdot e^{-\lambda}\cdot e^{\lambda}=(1-q^2)^{x_1}q^2.$$

**Passo 5 — riconoscere la distribuzione della marginale.** Il risultato $(1-q^2)^{x_1}q^2$ per $x_1\ge0$ è esattamente la densità di una **geometrica** (non traslata — quella che conta gli insuccessi prima del primo successo e parte da $0$, non da $1$) di parametro $p=q^2$: $(1-p)^{x_1}p$. Marginalmente, dunque, $X_1$ è geometrica di parametro $q^2$ — un fatto tutt'altro che ovvio guardando la densità congiunta originale, che emerge solo dopo aver sommato su $x_2$.

**Passo 6 — la coda con la serie geometrica.** Resta da sommare la marginale sui valori $x_1\ge k$:
$$P(X_1\ge k)=\sum_{x_1\ge k}p_{X_1}(x_1)=\sum_{x_1\ge k}(1-q^2)^{x_1}q^2=q^2\sum_{x_1\ge k}(1-q^2)^{x_1}.$$
Si riconosce la serie geometrica generale
$$\sum_{j\ge h}r^{j}=\frac{r^{h}}{1-r}\qquad(|r|<1),$$
che si legge "ragione elevata al primo indice della somma, diviso $1-r$". Qui la ragione è $r=1-q^2$ (che sta in $(0,1)$ perché $q\in(0,1)$) e il primo indice è $h=k$:
$$P(X_1\ge k)=q^2\cdot\frac{(1-q^2)^{k}}{1-(1-q^2)}=q^2\cdot\frac{(1-q^2)^{k}}{q^2}=(1-q^2)^{k}.$$
Stesso risultato che si otterrebbe applicando direttamente la [[Distribuzione geometrica#Formula per la "coda" di una v.a. geometrica (e per la traslata)|formula della coda]] della geometrica non traslata con $p=q^2$: una volta riconosciuta al Passo 5 la distribuzione della marginale, la coda è immediata.
### Esercizi svolti — varianti dagli appelli precedenti
#### Densità che si fattorizza: variabili indipendenti — appello del 20 Febbraio 2025
Densità congiunta:
$$p_{X_1,X_2}(x_1,x_2)=\frac{2^{x_1}}{x_1!}e^{-2}\cdot\frac{\binom{3}{x_2}\binom{3}{2-x_2}}{\binom{6}{2}}\qquad x_1\ge0,\ x_2\in\{0,1,2\}$$
**D5)** Calcolare $P(X_1X_2=0)$. **D6)** Verificare che $P(X_1+X_2\le1)=\frac{6}{5}e^{-2}$.
**Svolgimento**
**Passo 1 — riconoscere che la densità si fattorizza.** Il criterio generale è: se la densità congiunta si scrive come **prodotto** di una funzione della sola $x_1$ per una funzione della sola $x_2$, su un supporto rettangolare (senza vincoli incrociati fra le due variabili),
$$p_{X_1,X_2}(x_1,x_2)=f(x_1)\,g(x_2)\qquad\text{per }(x_1,x_2)\in S_1\times S_2,$$
allora $X_1$ e $X_2$ sono [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenti]]. Qui la densità è scritta esattamente in questa forma:
$$p_{X_1,X_2}(x_1,x_2)=\underbrace{\frac{2^{x_1}}{x_1!}e^{-2}}_{f(x_1)}\cdot\underbrace{\frac{\binom{3}{x_2}\binom{3}{2-x_2}}{\binom{6}{2}}}_{g(x_2)}\qquad x_1\ge0,\ x_2\in\{0,1,2\},$$
e il supporto è davvero un rettangolo: $x_1$ varia su tutti i naturali e $x_2$ su $\{0,1,2\}$, l'uno indipendentemente dall'altro — a differenza, per esempio, del supporto $x_2\ge x_1$ di un altro esercizio di questa sezione, dove le due variabili si vincolano a vicenda. Il fattore $f(x_1)$ è la densità **Poisson**$(2)$ nota da [[Distribuzioni uniforme discreta e di Poisson#Distribuzione di Poisson|Poisson]]; il fattore $g(x_2)$ è la densità **ipergeometrica** — [[Distribuzioni binomiale e ipergeometrica#Caso 2): distribuzione ipergeometrica|caso ipergeometrico]] — con i parametri di quella stessa nota: un'urna con $n_1=3$ oggetti di "tipo 1" e $n_2=3$ di "tipo 2", da cui si estraggono senza reinserimento $n=2$ oggetti, e $x_2$ conta i successi di tipo 1. Riconoscere l'indipendenza è ciò che rende gestibili D5 e D6: si può ragionare separatamente su $X_1$ e su $X_2$ invece che sempre sulla coppia.

**Passo 2 — leggere le marginali direttamente dai fattori.** In generale la marginale di $X_1$ si ottiene sommando la densità congiunta su tutti gli $x_2$,
$$p_{X_1}(x_1)=\sum_{x_2}p_{X_1,X_2}(x_1,x_2)=f(x_1)\sum_{x_2}g(x_2)=f(x_1)\cdot1=f(x_1),$$
e l'ultimo passaggio vale perché $g(x_2)$ è **già** una densità completa sul proprio supporto, quindi la sua somma su tutti gli $x_2$ vale 1 per definizione — non c'è nessun calcolo da fare, il fattore è già normalizzato. Lo stesso argomento, scambiando i ruoli, dà $p_{X_2}(x_2)=g(x_2)$. Concretamente:
$$X_1\sim\text{Poisson}(2),\qquad X_2\sim\text{Ipergeometrica}(n_1=3,\,n_2=3,\,n=2).$$
Questo è il senso concreto della regola "quando la densità si fattorizza, ogni marginale si legge da un fattore": qui serve per calcolare separatamente $P(X_1=0)$ e $P(X_2=0)$ in D5, invece di risommare tutta la congiunta.

**D5) Prodotto nullo come unione.** Un prodotto di due numeri è zero se e solo se **almeno uno** dei due fattori è zero, quindi l'evento richiesto è l'**unione**
$$\{X_1X_2=0\}=\{X_1=0\}\cup\{X_2=0\}.$$
I due eventi non sono disgiunti — la coppia $(0,0)$ appartiene a entrambi, cioè $X_1=0$ **e** $X_2=0$ possono accadere insieme — quindi sommare semplicemente $P(X_1=0)+P(X_2=0)$ conterebbe $(0,0)$ due volte. Serve la formula generale di inclusione-esclusione,
$$P(A\cup B)=P(A)+P(B)-P(A\cap B),$$
dove si sottrae l'intersezione una volta per compensare il doppio conteggio. Con $A=\{X_1=0\}$, $B=\{X_2=0\}$, le marginali del Passo 2 danno $P(X_1=0)=f(0)=e^{-2}$ e $P(X_2=0)=g(0)=\dfrac{\binom{3}{0}\binom{3}{2}}{\binom{6}{2}}=\dfrac{3}{15}=\dfrac{1}{5}$; e proprio perché $X_1,X_2$ sono indipendenti (Passo 1), l'intersezione è il semplice prodotto $P(X_1=0,X_2=0)=P(X_1=0)\,P(X_2=0)=e^{-2}\cdot\dfrac{1}{5}$. Sostituendo:
$$P(X_1X_2=0)=e^{-2}+\frac{1}{5}-\frac{1}{5}e^{-2}=\frac{1}{5}+e^{-2}\left(1-\frac{1}{5}\right)=\frac{1}{5}+\frac{4}{5}e^{-2}.$$
Lo stesso risultato si ritrova elencando le coppie a mano: la famiglia $(k,0)$ con $k\ge0$ (che include già $(0,0)$) più le sole $(0,1)$ e $(0,2)$ — evitando così di ricontare $(0,0)$ una seconda volta, che è esattamente ciò che fa l'inclusione-esclusione in forma implicita. Sommando la densità su tutta la prima famiglia si riconosce a vista la **serie esponenziale** della Poisson, già completa sul proprio supporto:
$$\sum_{k\ge0}\frac{2^k}{k!}e^{-2}=1,$$
quindi quella famiglia contribuisce da sola $1\cdot g(0)=\dfrac15$, mentre le restanti due coppie aggiungono $f(0)\big(g(1)+g(2)\big)=e^{-2}\!\left(\dfrac{9}{15}+\dfrac{3}{15}\right)=\dfrac{4}{5}e^{-2}$: si ritrova esattamente $\dfrac15+\dfrac45e^{-2}$.

**D6) Somma vincolata: solo tre coppie.** Torna qui il principio unico di tutto Es3, elencare le coppie compatibili e sommare la densità su quelle,
$$P\big((X_1,X_2)\in A\big)=\sum_{(x_1,x_2)\in A}p_{X_1,X_2}(x_1,x_2).$$
Il supporto di $X_1$ è infinito, ma il vincolo $x_1+x_2\le1$ con $x_1,x_2\ge0$ lo riduce a pochissimi casi non appena si fissa $x_2$: basta scorrere i tre soli valori $x_2\in\{0,1,2\}$ ammessi dal supporto e vedere quali $x_1$ restano compatibili. Per $x_2=0$ serve $x_1\le1$, quindi $x_1\in\{0,1\}$: coppie $(0,0)$ e $(1,0)$. Per $x_2=1$ serve $x_1\le0$, quindi $x_1=0$: coppia $(0,1)$. Per $x_2=2$ servirebbe $x_1\le-1$, impossibile perché $x_1\ge0$: nessuna coppia. In tutto contribuiscono solo **tre** coppie, nonostante $X_1$ possa in linea di principio assumere infiniti valori. Sommando la densità fattorizzata su ciascuna delle tre:
$$P(X_1+X_2\le1)=\underbrace{f(0)g(0)}_{(0,0)}+\underbrace{f(0)g(1)}_{(0,1)}+\underbrace{f(1)g(0)}_{(1,0)}=e^{-2}\cdot\frac{3}{15}+e^{-2}\cdot\frac{9}{15}+2e^{-2}\cdot\frac{3}{15}=\frac{3+9+6}{15}e^{-2}=\frac{18}{15}e^{-2}=\frac{6}{5}e^{-2},$$
che è esattamente il valore da verificare.
#### Inclusione-esclusione su $\{X_1X_2=0\}$ — appello del 20 Giugno 2024
Sia $q\in(0,1)$ e $p_{X_1,X_2}(x_1,x_2)=(1-q)^{x_1}(1-q^2)^{x_2}q^3$ per $x_1,x_2\ge0$ interi. Verificare che $P(X_1X_2=0)=q+q^2-q^3$.
**Svolgimento**
**Passo 1 — riconoscere la fattorizzazione: indipendenza.** La densità congiunta è scritta come un **prodotto** di due fattori, uno che dipende solo da $x_1$ e uno solo da $x_2$, su un supporto **rettangolare** — $x_1$ e $x_2$ variano ciascuno liberamente su tutti gli interi $\ge0$, senza che il valore dell'uno vincoli i valori possibili dell'altro (non è la diagonale né una riga, come in altre densità di questa nota). Il principio generale è
$$p_{X_1,X_2}(x_1,x_2)=f(x_1)\,g(x_2)\quad\text{su supporto rettangolare}\ \Longrightarrow\ X_1,X_2\ \text{indipendenti},$$
e ogni marginale si legge direttamente dal fattore corrispondente. Qui
$$p_{X_1,X_2}(x_1,x_2)=\underbrace{(1-q)^{x_1}}_{\text{solo }x_1}\cdot\underbrace{(1-q^2)^{x_2}q^3}_{\text{solo }x_2}\qquad x_1,x_2\ge0,$$
quindi $X_1$ e $X_2$ sono **indipendenti**. Riconoscerlo prima di sommare qualunque cosa evita di dover trattare $x_1$ e $x_2$ come legati fra loro.

**Passo 2 — tradurre l'evento $\{X_1X_2=0\}$ in un'unione.** Un prodotto di due numeri è zero se e solo se **almeno uno** dei due fattori è zero, quindi
$$\{X_1X_2=0\}=\{X_1=0\}\cup\{X_2=0\}.$$
Le due parti dell'unione **non sono disgiunte**: la coppia $(0,0)$ appartiene a entrambe, perché in essa sia $X_1=0$ sia $X_2=0$ sono vere contemporaneamente. Non si possono quindi sommare direttamente le due probabilità: si conterebbe $(0,0)$ due volte.

**Passo 3 — enunciare l'inclusione-esclusione.** Per l'unione di due eventi non disgiunti la formula generale è
$$P(A\cup B)=P(A)+P(B)-P(A\cap B),$$
e si legge così: sommando $P(A)+P(B)$ la parte comune $A\cap B$ viene contata due volte (una dentro $A$, una dentro $B$), quindi la si **sottrae una volta** per riportare il conteggio a quello corretto. Con $A=\{X_1=0\}$ e $B=\{X_2=0\}$:
$$P(X_1X_2=0)=P(X_1=0)+P(X_2=0)-P(X_1=0,X_2=0).$$

**Passo 4 — calcolare $P(X_1=0)$: la marginale come serie geometrica.** La definizione generale di marginale è
$$p_{X_1}(x_1)=\sum_{x_2\ge0}p_{X_1,X_2}(x_1,x_2),$$
cioè: si fissa il valore di $x_1$ che interessa e si somma la densità congiunta su tutti gli $x_2\ge0$ del supporto — sono le uniche coppie con quel $x_1$ a contribuire, perché la densità vale zero altrove. Sostituendo $x_1=0$:
$$P(X_1=0)=\sum_{x_2\ge0}p_{X_1,X_2}(0,x_2)=\sum_{k\ge0}q^3(1-q^2)^{k}.$$
È una **serie geometrica** di ragione $r=1-q^2$ che parte già dall'indice $k=0$ (nessun cambio di indice necessario, a differenza dei casi con $\frac{\lambda^{x_2-x_1}}{(x_2-x_1)!}$ visti altrove in questa nota). La formula generale è
$$\sum_{k\ge h}r^{k}=\frac{r^{h}}{1-r}\qquad(|r|<1),$$
cioè "ragione elevata al primo indice della somma, diviso $1-r$". Qui il parametro $h$ della formula generale vale $0$, quindi $r^h=1$ e
$$P(X_1=0)=q^3\cdot\frac{1}{1-(1-q^2)}=\frac{q^3}{q^2}=q.$$

**Passo 5 — calcolare $P(X_2=0)$ con lo stesso principio.** Stessa definizione generale di marginale del Passo 4, applicata a $X_2$: si somma su $x_1\ge0$ anziché su $x_2$, e si fissa $x_2=0$:
$$P(X_2=0)=\sum_{x_1\ge0}p_{X_1,X_2}(x_1,0)=\sum_{k\ge0}q^3(1-q)^{k}.$$
Stessa serie geometrica del Passo 4, questa volta di ragione $r=1-q$, ancora con $h=0$ (nessun cambio di indice):
$$P(X_2=0)=q^3\cdot\frac{1}{1-(1-q)}=\frac{q^3}{q}=q^2.$$

**Passo 6 — calcolare l'intersezione e concludere.** L'intersezione $\{X_1=0,X_2=0\}$ è la **singola coppia** $(0,0)$: non serve nessuna serie, basta valutare la densità congiunta in quel punto,
$$P(X_1=0,X_2=0)=p_{X_1,X_2}(0,0)=(1-q)^{0}(1-q^2)^{0}q^3=q^3.$$
Sostituendo i tre pezzi dei Passi 4, 5 e 6 nella formula di inclusione-esclusione del Passo 3:
$$P(X_1X_2=0)=\underbrace{q}_{\text{Passo 4}}+\underbrace{q^2}_{\text{Passo 5}}-\underbrace{q^3}_{\text{Passo 6}}=q+q^2-q^3.$$

> [!warning] Prodotto uguale a zero significa unione, non intersezione
> $X_1X_2=0$ vale quando **almeno una** delle due è nulla. Sommare $P(X_1=0)+P(X_2=0)$ senza sottrarre l'intersezione conta due volte la coppia $(0,0)$.

#### Densità simbolica a tabella — appello del 23 Febbraio 2021
La densità è data per valori simbolici: $p_{X_1,X_2}(0,0)=q_{00}$, $p_{X_1,X_2}(0,1)=q_{01}$, $p_{X_1,X_2}(1,0)=q_{10}$, $p_{X_1,X_2}(1,2)=q_{12}$, $p_{X_1,X_2}(2,1)=q_{21}$, tutti positivi e con somma 1.
**D5)** Trovare la densità di $Y=X_1+X_2$. **D6)** Calcolare $P(X_1>X_2|X_1+X_2>1)$.
**Svolgimento**
**Passo 1 — leggere il supporto.** La densità è definita **solo** sulle cinque coppie elencate — $(0,0)$, $(0,1)$, $(1,0)$, $(1,2)$, $(2,1)$ — con i pesi simbolici $q_{00},q_{01},q_{10},q_{12},q_{21}$ (positivi, di somma 1); su **ogni altra coppia** $p_{X_1,X_2}(x_1,x_2)=0$. Non essendoci numeri da calcolare, tutto l'esercizio si riduce a elencare correttamente quali di queste cinque coppie soddisfano ciascuna richiesta.

**Passo 2 — principio generale per la densità di una trasformazione.** Per $Y=g(X_1,X_2)$ vale
$$p_Y(y)=\sum_{(x_1,x_2)\,:\,g(x_1,x_2)=y}p_{X_1,X_2}(x_1,x_2).$$
Si legge così: per ogni valore $y$ si **raggruppano** tutte le coppie del supporto che, applicando $g$, danno esattamente $y$, e si somma la loro densità; i valori $y$ per cui **nessuna** coppia del supporto dà $g(x_1,x_2)=y$ semplicemente non compaiono nella densità di $Y$ — sono valori che $Y$ non assume mai.

**D5) Densità di $Y=X_1+X_2$.** Qui $g(x_1,x_2)=x_1+x_2$: si calcola la somma per ciascuna delle cinque coppie del Passo 1 e si raggruppano quelle con lo stesso risultato — $(0,0)\to0$; $(0,1)$ e $(1,0)\to1$; $(1,2)$ e $(2,1)\to3$:
$$p_Y(0)=q_{00}\qquad p_Y(1)=q_{01}+q_{10}\qquad p_Y(3)=q_{12}+q_{21}$$
Il valore $Y=2$ **non compare**: nessuna delle cinque coppie del supporto somma a 2 (servirebbe una coppia come $(0,2)$, $(1,1)$ o $(2,0)$, e nessuna di queste è nell'elenco), quindi $Y=2$ è **non raggiungibile** e va scritto esplicitamente, non lasciato sottinteso — dimenticarlo è l'errore più comune quando si raggruppano coppie su un supporto piccolo.

**D6) Condizionata $P(X_1>X_2\mid X_1+X_2>1)$.** La condizionata resta sempre la definizione
$$P(A\mid B)=\frac{P(A\cap B)}{P(B)},$$
cioè: si sommano le coppie che soddisfano **sia** $A$ **sia** $B$ (numeratore), si sommano quelle che soddisfano $B$ (denominatore), e si divide. Qui $B=\{X_1+X_2>1\}$: guardando i valori trovati al Passo D5, l'unico valore di $Y$ maggiore di 1 è 3, quindi $B$ coincide esattamente con $\{Y=3\}$, cioè le coppie $(1,2)$ e $(2,1)$, con $P(B)=p_Y(3)=q_{12}+q_{21}$. Dentro queste due coppie si cerca ora $A=\{X_1>X_2\}$: in $(1,2)$ è $1<2$ (non soddisfa $A$), in $(2,1)$ è $2>1$ (soddisfa $A$); quindi $A\cap B$ è la sola coppia $(2,1)$, con $P(A\cap B)=q_{21}$. Applicando la definizione:
$$P(X_1>X_2\mid X_1+X_2>1)=\frac{q_{21}}{q_{12}+q_{21}}$$

Con una densità simbolica non c'è nessun conto numerico da fare: tutta la difficoltà dell'esercizio sta nell'**elencare correttamente le coppie** che soddisfano ciascuna condizione.
### Trappole ricorrenti

- **Sommare fuori dal supporto**: la densità vale zero sulle coppie non elencate. Se il supporto è $x_2\ge x_1$, la coppia $(3,1)$ non contribuisce.
- **Dimenticare l'intersezione dei pezzi**: quando la densità è definita a pezzi (diagonale + riga), la coppia comune — tipicamente $(0,0)$ — appartiene a entrambi. Va contata una volta sola, e con la formula giusta.
- **Prodotto nullo = unione**: $\{X_1X_2=0\}=\{X_1=0\}\cup\{X_2=0\}$, quindi inclusione-esclusione.
- **Valori non raggiungibili**: nella densità di $Y$ vanno indicati **solo** i valori che $Y$ assume davvero. Scrivere $p_Y(2)=0$ non è sbagliato, ma dimenticare che $p_Y(3)$ esiste sì.
- **Cambio di indice nelle serie**: $\sum_{h\ge1}\frac{3^{h-1}}{(h-1)!}$ non è $e^3-1$, è $e^3$ — perché sostituendo $j=h-1$ la somma riparte da $j=0$. Sbagliare qui manda a monte tutto il denominatore.
- **Fattorizzazione = indipendenza**: se la densità si scrive come prodotto di una funzione di $x_1$ per una di $x_2$ (supporto rettangolare compreso), le variabili sono indipendenti e ogni marginale si legge direttamente.

### Collegamenti

- Serie e distribuzioni: [[Distribuzione geometrica#Formula della serie geometrica|serie geometrica]], [[Distribuzioni uniforme discreta e di Poisson#Distribuzione di Poisson|Poisson]], [[Variabili aleatorie discrete]].
- Teoria delle condizionate: [[Cap 2 - Introduzione alla probabilità#Formule legate alle probabilità condizionate|Cap 2]], e [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|indipendenza]] per il criterio di fattorizzazione.
- Slot vicini: [[Es1 - Probabilità discreta elementare|Es1]] fa la modellizzazione che qui è già data dalla traccia; [[Es2 - Probabilità condizionata]] usa le stesse condizionate su eventi anziché su variabili; [[Es4 - Trasformazione di variabile continua]] fa la stessa operazione di trasformazione, ma nel continuo.
