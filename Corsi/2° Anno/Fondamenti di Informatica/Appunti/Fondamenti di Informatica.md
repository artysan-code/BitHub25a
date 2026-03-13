## Introduzione alla Calcolabilità
### Notazioni di base
Sia $\Sigma$ un **alfabeto**, cioè un insieme finito di caratteri (es. $\Sigma = \{a, b\}$).

- $\Sigma^*$ = insieme di tutte le **parole** su $\Sigma$, ovvero sequenze di 0 o più caratteri. Es: $aa, aba, baaaba \in \Sigma^*$
- $\varepsilon$ = **parola vuota** (0 caratteri)
- **Concatenazione**: date $x = x_1\dots x_n$ e $y = y_1\dots y_k$, si ha $xy = x_1\dots x_n y_1\dots y_k$
- **Parola inversa**: $x^{-1} = x_n x_{n-1}\dots x_1$
- **Complemento** (solo per $x \in \{0,1\}^*$): $x^c = y_1\dots y_n$ dove $y_i = 1-x_i$
### Problemi e istanze
Un **problema** è la descrizione di un insieme di parametri (i **dati**), collegati da certe relazioni, con la richiesta di derivarne un altro insieme di parametri che costituiscono la **soluzione**.

Un'**istanza** è un particolare insieme di valori assegnati ai dati di un problema.

> Esempio: "Quanto fa 5+2?" non è un problema — è un'**istanza** del *Problema Somma*.
> **Problema Somma**: dati $n, k \in \mathbb{N}$, calcolare $n + k$.

Quando un'istanza non ammette soluzione, si parla di **istanza negativa** (es. trovare $\sqrt{-4}$ come numero reale).
### Risolvere un problema
**Risolvere un problema** significa trovare un **procedimento** che, data una qualunque istanza, sappia calcolare la soluzione — e sappia anche riconoscere le istanze negative.

> Un **procedimento** è la descrizione di un insieme di azioni (*istruzioni*) unita alla specifica dell'ordine in cui devono essere eseguite.

La questione si sposta quindi su: cos'è un'istruzione? e chi la esegue?
### L'istruzione elementare
Per sganciare la definizione di procedimento dall'esecutore specifico, Turing formalizzò cosa si intende per **istruzione elementare**. Un'istruzione è elementare se:
1. È scelta in un insieme di **"poche"** istruzioni disponibili
2. Sceglie l'azione da un insieme di **"poche"** azioni possibili
3. Richiede una **quantità limitata di memoria** (costante, indipendente dall'input)

In pratica: un'operazione che può essere eseguita *a mente*, senza nessuna conoscenza pregressa del problema.
### Esempio: la somma di due numeri naturali
Vogliamo costruire un procedimento che sommi qualunque coppia di naturali. Perché "calcola $n+k$" non è un'istruzione elementare?

Perché per renderla elementare occorrerebbe una tabella con i risultati di **tutte** le possibili coppie — ma i naturali sono infiniti, e la nostra memoria è limitata. Non funziona.

La soluzione è la classica **somma in colonna**, che usa solo somme di coppie di cifre singole (0–9), che sono finite e memorizzabili. Il procedimento mantiene in memoria solo tre valori: le due cifre correnti e il riporto $r \in \{0,1\}$.

**Quante istruzioni servono?** Le condizioni dipendono da:
- 11 possibilità per la prima cifra (0–9 + blank)
- 11 possibilità per la seconda cifra
- 2 valori del riporto

$$11 \times 11 \times 2 = 242 \text{ istruzioni}$$

Indipendentemente da quanto siano grandi i numeri, bastano **sempre 242 istruzioni** (ognuna esegue 3 azioni: scrivi cifra, aggiorna riporto, spostati a sinistra) e si usano **sempre 3 cifre di memoria**. Numero di istruzioni, azioni e memoria sono **costanti**: non dipendono dall'input. Questo è esattamente ciò che Turing intende per "poche" e "limitata".

Ogni istruzione ha la forma:
$$\text{se } \textit{certe condizioni} \text{ allora esegui } \textit{queste azioni}$$

Due proprietà fondamentali del procedimento così costruito:
- **Non ambiguo**: per ogni condizione possibile c'è esattamente un'istruzione applicabile — non può capitare che due istruzioni diverse siano entrambe applicabili nella stessa situazione. ^2c2748
- **Auto-ordinato**: l'ordine di esecuzione è implicito nel meccanismo stesso — ad ogni passo esegui l'unica istruzione applicabile, finché non incontri "termina".

Nota interessante: per eseguire questo procedimento non serve nemmeno sapere cosa significa "sommare". Basta seguire le istruzioni meccanicamente e il risultato arriva — *come per magia*. Potrebbe eseguirlo anche un **automa**.

Questa idea di istruzione imperativa ("ti dico cosa fare, tu lo fai") è alla base dei linguaggi di programmazione **imperativi** (C, Fortran, Java, Python...).
### Risolvere automaticamente un problema
Arriviamo al nocciolo: **risolvere automaticamente un problema** significa progettare un procedimento che risolva **tutte** le istanze del problema e che possa essere eseguito da un **automa** — cioè da un esecutore che non ha alcuna idea del problema né del significato delle istruzioni.
### Un nuovo linguaggio: le quintuple
Per descrivere il procedimento in forma compatta, introduciamo una notazione. Ripensiamo alla somma in colonna:
1. Le istruzioni sono tutte del tipo "se condizione allora azione"
2. Le azioni sono sempre le stesse 3: scrivi cifra, aggiorna riporto, spostati a sinistra
3. Le condizioni dipendono da due parametri: le due cifre lette e il valore del riporto

Il riporto è qualcosa che "teniamo a mente" tra un passo e l'altro — lo chiamiamo **stato interno** (o **stato interiore**). Usiamo $q_0$ per indicare $r=0$ e $q_1$ per $r=1$.

Possiamo allora scrivere ogni istruzione come una coppia $(\textit{condizioni}, \textit{azioni})$, omettendo il "se...allora...":

$$\langle q_0, (4, 6), 0, q_1, \text{s} \rangle$$

che corrisponde a: *"se il riporto è 0 e le cifre sono 4 e 6, allora scrivi 0, il nuovo riporto è 1, spostati a sinistra"*

Quando le cifre di uno degli operandi sono finite, si usa il simbolo $\square$ (**blank**) per indicare l'assenza di cifra:

$$\langle q_1, (5, \square), 6, q_0, \text{f} \rangle \quad \langle q_1, (\square, 5), 6, q_0, \text{f} \rangle$$

Quando entrambe le cifre sono finite, si raggiunge lo **stato finale** $q_F$ e si termina:

$$\langle q_1, (\square, \square), 1, q_F, \text{f} \rangle \quad \langle q_0, (\square, \square), \square, q_F, \text{f} \rangle$$
### Quasi una macchina di Turing
L'automa che esegue questo procedimento usa **3 nastri** (uno per ogni operando + uno per il risultato), ciascuno suddiviso in celle infinite inizialmente vuote ($\square$), con una testina di lettura/scrittura per nastro. La "testa robotizzata" può trovarsi in uno dei 3 stati: $q_0, q_1, q_F$.

Poiché nella vera macchina di Turing occorre specificare cosa viene letto e scritto su **ogni** nastro, la quintupla completa diventa:

$$\langle q_0, (4, 6, \square), (4, 6, 0), q_1, \text{s} \rangle$$

dove $(4, 6, \square)$ è ciò che viene letto sui 3 nastri e $(4, 6, 0)$ è ciò che viene scritto.

Termini chiave:
- **quintupla** — la singola istruzione (specifica 2 condizioni + 3 azioni)
- **stati interni** — i valori dello stato interiore ($q_0, q_1, q_F$)
- **computazione** — l'esecuzione delle quintuple su un insieme fissato di dati
### Calcolabilità
Quello che abbiamo costruito è una descrizione informale di una **macchina di turing** (con la 'm' minuscola) — cioè la descrizione di un procedimento risolutivo espressa nel linguaggio definito da Alan Turing.

Tale linguaggio costituisce un **modello di calcolo**: il modello **Macchina di Turing** (con la 'M' maiuscola).
### La Macchina di Turing — Definizione formale
Una **macchina di Turing ad un nastro** è composta da tre elementi fisici:
- Un'**unità di controllo** che, ad ogni istante, si trova in uno **stato interno** appartenente a un insieme finito $Q$. Tra gli stati vi è uno stato particolare $q_0$ (stato iniziale) e un sottoinsieme $Q_F \subseteq Q$ di **stati finali**.
- Un **nastro** suddiviso in un numero infinito di celle, ciascuna delle quali può contenere un simbolo di $\Sigma$ oppure essere vuota (simbolo $\square$, detto **blank**). Sul nastro si muove una **testina di lettura/scrittura**.
- Ad ogni istante, in base allo stato interno corrente e al simbolo letto dalla testina, viene eseguita una **quintupla** scelta dall'insieme $P$.

**Come funziona:** la macchina parte dallo stato $q_0$ con la testina posizionata sul carattere più a sinistra del nastro. Ad ogni passo, legge il simbolo sotto la testina e cerca in $P$ una quintupla i cui primi due elementi siano lo stato corrente e il simbolo letto. Se la trova, la esegue; altrimenti la computazione termina.

**Eseguire una quintupla** $\langle q, x, x', q', m \rangle$ significa compiere tre azioni:
1. **Sovrascrivere** il simbolo $x$ nella cella corrente con $x'$
2. **Cambiare** (eventualmente) lo stato interno, passando da $q$ a $q'$
3. **Muovere** (eventualmente) la testina nella direzione $m \in \{s, f, d\}$ (sinistra, fermo, destra)

Dopo ogni esecuzione si cerca la quintupla successiva, e così via finché nessuna quintupla è applicabile.

> **Definizione formale.** Una **macchina di Turing ad un nastro** è una quintupla $T = \langle \Sigma, Q, q_0, Q_F, P \rangle$ dove:
> - $\Sigma$ è un insieme **finito** di caratteri (**alfabeto**)
> - $Q$ è un insieme **finito** di **stati interni**
> - $q_0 \in Q$ è lo **stato iniziale**
> - $Q_F \subseteq Q$ è l'insieme degli **stati finali**
> - $P \subseteq Q \times (\Sigma \cup \{\square\}) \times (\Sigma \cup \{\square\}) \times Q \times \{s, f, d\}$ è l'insieme delle **quintuple**

Per la proprietà di [[Fondamenti di Informatica#^2c2748|non ambiguità]], $P$ non contiene mai due quintuple con gli stessi primi due elementi: **$P$ è una funzione**:
$$P: Q \times (\Sigma \cup \{\square\}) \to (\Sigma \cup \{\square\}) \times Q \times \{s, f, d\}$$
### Esempio: $T_{\text{parità}}$
Consideriamo la macchina $T_{\text{parità}} = \langle \Sigma, Q, q_0, Q_F, P \rangle$ che verifica se una sequenza di $0$ e $1$ contiene un numero pari o dispari di $1$:
$$\Sigma = \{0, 1, p, d\} \qquad Q = \{q_0, q_p, q_d, q_F\}$$
con stato iniziale $q_0$ e stato finale $q_F$.

La macchina scandisce la sequenza cancellando i caratteri man mano, tenendo traccia della parità tramite lo stato interno ($q_p$ = pari finora, $q_d$ = dispari finora). Al primo $\square$ incontrato scrive $p$ o $d$ e termina.

**Traccia di esecuzione su "101":** la macchina parte in $q_0$ con la testina sul primo carattere:
- legge $1$ → esegue $\langle q_0, 1, \square, q_d, d \rangle$ → cancella, passa a $q_d$, si sposta a destra
- legge $0$ → esegue $\langle q_d, 0, \square, q_d, d \rangle$ → cancella, rimane $q_d$, si sposta a destra
- legge $1$ → esegue $\langle q_d, 1, \square, q_p, d \rangle$ → cancella, passa a $q_p$, si sposta a destra
- legge $\square$ → esegue $\langle q_p, \square, p, q_F, f \rangle$ → scrive $p$, raggiunge $q_F$: **computazione terminata**

Il risultato è $p$ (pari): "101" contiene due $1$.

**Osservazione:** se sul nastro si scrivesse "p010", la macchina in stato $q_0$ cercherebbe una quintupla che inizi con la coppia $(q_0, p)$, non la troverebbe in $P$, e la computazione terminerebbe immediatamente senza produrre alcun risultato. Questo comportamento sarà approfondito.

**Programma completo:**
$$T_{\text{parità}} = \langle \{0,1,p,d\},\ \{q_0, q_p, q_d, q_F\},\ q_0,\ \{q_F\},\ P_{\text{parità}} \rangle$$
$$P_{\text{parità}} = \left\{\begin{array}{ll}
\langle q_0, 0, \square, q_p, d \rangle & \langle q_0, 1, \square, q_d, d \rangle \\
\langle q_p, 0, \square, q_p, d \rangle & \langle q_d, 0, \square, q_d, d \rangle \\
\langle q_p, 1, \square, q_d, d \rangle & \langle q_d, 1, \square, q_p, d \rangle \\
\langle q_p, \square, p, q_F, f \rangle & \langle q_d, \square, d, q_F, f \rangle
\end{array}\right\}$$
### Macchine di Turing a $k$ nastri
La definizione si generalizza a macchine con $k$ nastri. Una macchina a $k$ nastri è ancora una quintupla $\langle \Sigma, Q, q_0, Q_F, P \rangle$, ma le quintuple hanno la forma:
$$\langle\, q_1,\ (a_1, \dots, a_k),\ (b_1, \dots, b_k),\ q_2,\ (m_1, \dots, m_k)\,\rangle$$
dove $(a_1, \dots, a_k)$ sono i caratteri letti sui $k$ nastri, $(b_1, \dots, b_k)$ quelli scritti (sovrascrivendo i precedenti), e $(m_1, \dots, m_k)$ i movimenti delle $k$ testine.

> **Osservazione.** Per capire quanti nastri ha una macchina $\langle \Sigma, Q, q_0, Q_F, P \rangle$, è sufficiente osservare le quintuple in $P$: il numero di componenti del secondo elemento di una quintupla corrisponde al numero di nastri. Se il secondo elemento è un singolo simbolo $\langle q_1, a_1, \dots \rangle$ allora è una macchina ad un nastro; se è una coppia $\langle q_1, (a_1, a_2), \dots \rangle$ allora è a due nastri; e così via.
### Perché $\Sigma$, $Q$ e $k$ devono essere finiti
Il modello Macchina di Turing richiede che alfabeto, stati e numero di nastri abbiano **cardinalità finita** — e che siano **costanti**, cioè indipendenti dall'input. Il motivo è che una macchina di Turing deve essere **costruibile**.

Se fosse possibile avere un numero infinito di stati, il progetto di $T_{\text{somma}}$ diventerebbe banale: basterebbe porre $\Sigma = \mathbb{N} \cup \{+\}$ e $Q = \{q_x : x \in \mathbb{N}\} \cup \{q_i, q_F\}$ e usare le quintuple
$$\forall n \in \mathbb{N}\ \langle q_i, (n,\square), (n,\square), q_n, (\text{d,f}) \rangle, \quad \forall n \in \mathbb{N}\ \langle q_n, (+,\square), (+,\square), q_n, (\text{d,f}) \rangle$$
$$\forall n, m \in \mathbb{N}\ \langle q_n, (m,\square), (m{+}n,\square), q_F, (\text{d,f}) \rangle$$

Troppo facile — e infatti non funziona. Questa "macchina" richiederebbe tanti stati quanti i naturali, tante quintuple quante le coppie: non si costruirebbe mai. La notazione abbreviata "per ogni $x \in A$" è ammessa solo quando $A$ è **finito**, così da poter elencare esplicitamente tutti gli stati e tutte le quintuple.
### Definizioni formali
#### Parola
Dato un alfabeto finito $\Sigma$, una **parola** su $\Sigma$ è una sequenza **finita** di elementi di $\Sigma$. L'insieme di tutte le parole su $\Sigma$ si indica con $\Sigma^*$ e include la **parola vuota** $\varepsilon$.

> Esempio: su $\Sigma = \{a, b, c\}$, la stringa $aba$ è una parola su $\Sigma$.
#### Stato globale
> **Definizione.** Uno **stato globale** (SG) di una macchina di Turing ad un nastro $T$ è una "fotografia" completa della macchina in un certo istante. Contiene:
> - il contenuto della porzione **non blank** del nastro
> - la **posizione della testina** (e quindi il carattere da essa letto)
> - lo **stato interno** corrente
>
> Si rappresenta come la sequenza dei caratteri non blank del nastro, con lo stato interno **premesso** al carattere letto dalla testina.

**Esempi:**
- Nastro con "abcd", testina su "b", stato $q$: $\quad a\ q\ b\ c\ d$
- Nastro con "aacd", testina sulla prima "a", stato $q'$: $\quad q'\ a\ a\ c\ d$

Lo **stato globale iniziale** è quello in cui la macchina si trova nello stato $q_0$ con la testina posizionata sul carattere più a sinistra scritto sul nastro.

> **Esempio concreto.** Per la macchina che calcola la somma $812 + 53$:
> - SG iniziale: $q_0\ 8\ 1\ 2\ +\ 5\ 3$
> - Uno stato globale successivo: $=\ 8\ 1\ 2\ +\ q_3^0\ 5$
#### Transizione
> **Definizione.** Esiste una **transizione** da $SG_1$ a $SG_2$, scritta $SG_1 \vdash SG_2$, se esiste una quintupla $\langle q, x, x', q', m \rangle \in P$ tale che:
> - in $SG_1$ la macchina si trova nello stato interno $q$ e la testina sta scandendo il carattere $x$
> - in $SG_2$ quella cella contiene $x'$, la macchina si trova nello stato $q'$ e la testina si è spostata di $m$

> **Esempio.** Transizione dallo stato globale $=812+\ q_3^0\ 5$ allo stato globale $=812\ q_3^0\ +5$ a seguito dell'esecuzione della quintupla $\langle q_3^0, 5, 5, q_3^0, s \rangle$.
#### Computazione
> **Definizione.** Una **computazione** di una macchina di Turing $T(x)$ ($T$ corrisponde all'algoritmo, $x$ all'input) è una sequenza (finita o infinita) di stati globali:
> $$SG_0 \vdash SG_1 \vdash SG_2 \vdash \dots \vdash SG_h \vdash \dots$$
> tale che:
> - $SG_0$ è uno stato globale iniziale (stato $q_0$, testina sul carattere più a sinistra)
> - per ogni $0 \le i \le h-1$, esiste una transizione da $SG_i$ a $SG_{i+1}$, **oppure** nessuna quintupla è eseguibile in $SG_i$ (e per ogni $h \ge i+1$, $SG_h$ non è definito)

La computazione **termina** se esiste un indice $h$ tale che da $SG_h$ non può avvenire alcuna transizione. Questo accade quando:
- lo stato interno di $SG_h$ appartiene a $Q_F$, **oppure**
- $P$ non contiene alcuna quintupla eseguibile in $SG_h$

Se nessun tale $h$ esiste, la computazione **non termina** (cicla all'infinito).
### Trasduttori e Riconoscitori
Le macchine di Turing si dividono in due categorie in base al tipo di problema che risolvono.

Un **trasduttore** calcola il valore di una funzione qualsiasi (es. $f(a,b) = a+b$). Dispone di un **nastro di output** su cui scrive il risultato, e ha **un solo stato finale** $q_F$. L'**esito** della computazione $T(x)$, indicato con $o_T(x)$, è la parola scritta sul nastro di output al momento in cui $T$ raggiunge $q_F$.

> Esempio: se $T$ calcola la somma, allora $o_T(15, 6) = 21$.

Un **riconoscitore** calcola il valore di una **funzione booleana** (0 oppure 1). Non ha nastro di output: il risultato è codificato nello **stato finale** con cui termina. Ha **due stati finali**: $q_A$ (accetta, valore $1$) e $q_R$ (rigetta, valore $0$). ^d2437d

- $T$ **accetta** $x$ se la computazione $T(x)$ termina in $q_A$
- $T$ **rigetta** $x$ se la computazione $T(x)$ termina in $q_R$
- L'esito $o_T(x)$ è lo stato interno finale

> Esempio: se $T$ decide se una parola è palindroma, allora $o_T(abba) = q_A$ e $o_T(baaba) = q_R$.

> **Convenzione del corso.** Nel seguito, salvo indicazione contraria, con "macchina di Turing" si intenderà sempre una macchina di tipo **riconoscitore**. Per riferirsi a un trasduttore si dirà esplicitamente "macchina di Turing di tipo trasduttore".
### Esercizio: $T_{\text{somma}}$ a due nastri
**Problema:** progettare una macchina di Turing a due nastri $T_{\text{somma}} = \langle \Sigma, Q, q_0, Q_F, P \rangle$ con $\Sigma = \{0,1,\dots,9,+\}$ che, avendo sul primo nastro due numeri interi della stessa lunghezza separati da "$+$", calcola la loro somma scrivendola sul secondo nastro.

Due osservazioni preliminari:
- Il "$+$" è il **carattere separatore** che distingue i due addendi sul primo nastro.
- Il secondo nastro è il **nastro di output**; il primo è il nastro di **input e lavoro**.

**Idea della soluzione (somma in riga):** si lavora da destra a sinistra, cifra per cifra, ricordando il riporto nello stato interno. Il procedimento è:

1. Da $q_i$, la testina avanza a destra finché incontra "$+$", poi entra in $q_{is}$ e torna indietro di una posizione per posizionarsi sulla cifra più a destra del primo addendo:
$$\forall x \in \{0,\dots,9\}\ \langle q_i, (x,\square), (x,\square), q_i, (d,f) \rangle \qquad \langle q_i, (+,\square), (+,\square), q_{is}, (s,f) \rangle$$

2. In $q_{is}$ si legge la cifra $x$ del primo addendo, la si memorizza nello stato $q_x^0$ (riporto 0) sostituendola con "$+$"; poi si avanza a destra verso la cifra più a destra del secondo addendo (subito a sinistra del $\square$):
$$\forall x \in \{0,\dots,9\}\ \langle q_{is}, (x,\square), (+,\square), q_x^0, (d,f) \rangle$$
$$\forall x \in \{0,\dots,9\}\ \langle q_x^0, (y,\square), (y,\square), q_x^0, (d,f) \rangle \qquad \langle q_x^0, (\square,\square), (\square,\square), q_{xs}^0, (s,f) \rangle$$

3. Si esegue la somma tra la cifra memorizzata nello stato e quella letta: si cancella la cifra letta sul primo nastro ($\square$) e si scrive la cifra risultante sul secondo nastro (testina del secondo nastro si sposta a sinistra). Il nuovo riporto viene memorizzato nello stato ($q^0$ o $q^1$). Le 200 quintuple (10 × 10 × 2) hanno questa forma:
$$\langle q_{0s}^0, (0,\square), (\square,0), q^0, (f,s) \rangle \quad \langle q_{1s}^0, (0,\square), (\square,1), q^0, (f,s) \rangle \quad \dots$$
$$\langle q_{6s}^0, (3,\square), (\square,9), q^0, (f,s) \rangle \quad \langle q_{6s}^1, (3,\square), (\square,0), q^1, (f,s) \rangle \quad \dots$$

4. Si ritorna a sinistra sul primo nastro (attraverso la sequenza di "$+$") per riprendere la cifra successiva del primo addendo, e si ripete dal passo 2. Quando si incontra $\square$ la somma è terminata: se il riporto finale è $1$ si scrive $1$ sul nastro di output, poi si raggiunge $q_F$:
$$\langle q_s^0, (\square,\square), (\square,\square), q_F, (d,f) \rangle \qquad \langle q_s^1, (\square,\square), (\square,1), q_F, (d,f) \rangle$$

**Programma completo (schema per gruppi):**
$$T_{\text{somma}} = \langle \{0,\dots,9,+\},\ Q,\ q_i,\ \{q_F\},\ P_{\text{somma}} \rangle$$
$$P_{\text{somma}} = \left\{\begin{array}{ll}
\forall x \in \{0,\dots,9\} & \langle q_i,\ (x,\square),\ (x,\square),\ q_i,\ (d,f) \rangle \\
 & \langle q_i,\ (+,\square),\ (+,\square),\ q_{is},\ (s,f) \rangle \\[4pt]
\forall x \in \{0,\dots,9\} & \langle q_{is},\ (x,\square),\ (+,\square),\ q_x^0,\ (d,f) \rangle \\[4pt]
\forall x \in \{0,\dots,9\} & \langle q_x^0,\ (y,\square),\ (y,\square),\ q_x^0,\ (d,f) \rangle \quad \forall y \in \{0,\dots,9,+\} \\
\forall x \in \{0,\dots,9\} & \langle q_x^0,\ (\square,\square),\ (\square,\square),\ q_{xs}^0,\ (s,f) \rangle \\[4pt]
\forall x,y \in \{0,\dots,9\} & \langle q_{xs}^0,\ (y,\square),\ (\square,\ (x{+}y)\bmod 10),\ q^r,\ (f,s) \rangle \quad r = \lfloor(x{+}y)/10\rfloor \\
\forall x,y \in \{0,\dots,9\} & \langle q_{xs}^1,\ (y,\square),\ (\square,\ (x{+}y{+}1)\bmod 10),\ q^r,\ (f,s) \rangle \quad r = \lfloor(x{+}y{+}1)/10\rfloor \\[4pt]
\forall x \in \{0,\dots,9\} & \langle q^0,\ (x,\square),\ (x,\square),\ q^0,\ (s,f) \rangle \\
\forall x \in \{0,\dots,9\} & \langle q^1,\ (x,\square),\ (x,\square),\ q^1,\ (s,f) \rangle \\
 & \langle q^0,\ (+,\square),\ (+,\square),\ q_s^0,\ (s,f) \rangle \quad \langle q^1,\ (+,\square),\ (+,\square),\ q_s^1,\ (s,f) \rangle \\[4pt]
\forall x \in \{0,\dots,9\} & \langle q_s^0,\ (x,\square),\ (+,\square),\ q_x^0,\ (d,f) \rangle \quad \langle q_s^1,\ (x,\square),\ (+,\square),\ q_x^1,\ (d,f) \rangle \\[4pt]
 & \langle q_s^0,\ (\square,\square),\ (\square,\square),\ q_F,\ (d,f) \rangle \\
 & \langle q_s^1,\ (\square,\square),\ (\square,1),\ q_F,\ (d,f) \rangle
\end{array}\right\}$$

> **Nota:** la macchina funziona **soltanto** se i due addendi hanno lo stesso numero di cifre. La versione per numeri di lunghezza diversa è trattata nel paragrafo 1.6 della dispensa 1 ed è proposta come esercizio (da svolgere senza consultare la soluzione).

### Lezione
Teorema
$\forall T_{k}=<\Sigma, Q_{k},q_{0},Q_{f},P_{k}>$ una TM a k nastri e testine indipendenti $\exists\ T_{k+1}=<\Sigma\cup[*], Q_{k+1},q_{0},Q_{f},P_{k+1}>$ TM a k+1 nastri e testine solidali tale che $\forall\ x \in \Sigma^*\ [o_{T_{k}}(x)=o_{T_{k+1}}(x)]$, dove $T_{k}$ e $T_{k+1}$ sono [[Fondamenti di Informatica#^d2437d|riconoscitori]].

Cerchiamo di dimostrare

Prima immagine
$$\begin{array}{l}
<q_{1},(o,u),(e,y),q^{'},(m_{1},m_{2})> \\
\text{Riscritto} \\
<q,(a,u),(e,y),q^{'},(d,d)>
\end{array}$$

Creiamo una simulazione dello shift allo scopo di poterla riusare (come con le funzioni)
Principio di shift (sinsitra):$$\begin{array}{l}
<q_{d1},(d,x),(\square,x),q_{d1},(d),s> & \forall x \\
<q_{d1},(d),(c,x_{\alpha}),(d,x_{\alpha}),q_{d1}(c),s>& \forall\ \alpha \in{\square,*}
\end{array}$$

Per poter capire l'unicità diciamo di ogni coppia di valori e copiare quindi lo stato che avevamo in prima immagine, usiamo un nastro in più 

Es. Provate a scrivere le quintuple di questa macchina quando sigma è 0 e 1 o a e b.

Es. Fare quello che sta succedendo sotto della scatola aperta, ma separando i caratteri dei due nastri, nel nastro di output con un *
#### Simulazioni a scatola aperta
$$\begin{array}{l}
<q,a,a,q(a),d> \\
<q(a),u,u,,q(a,u,1),s> \\
<q(a,u,1),a,e,q_{scrivi}(a,u,2),d> \\
<q_{scrivi}(a,u,z),u,y,q_{ind}(q^{'},1),s> \\
<q_{ind}(q^{'},1),a,a,q^{'},f> & \forall\ a \in \Sigma\cup \{\square\}
\end{array}$$

### Lezione 3 temp so tante lo so
$$T\implies P$$
- $\text{P totale}:\forall q\in Q\ s\in \Sigma[\exists(q,s,\dots)]$
- $\text{P deve corrisponde ad una funzione:}$$$\begin{array}[l]
\delta:Q\ x\ \Sigma \implies \Sigma\ x\ Q\ x\ \{s,f,d\} \\
\forall\ q \in Q\quad \forall\ s\in\Sigma \quad <q,s,s_{1},q_{1},m_{1}>,\ <q,s,s_{2},q_{2},m_{2}>\quad s_{1}\neq s_{2}\ q_{1}\neq q_{2}\ m_{1}\neq m_{2} \\
<q,s,s_{1},q_{1},m_{1}>dP\ OR\ <q,s,s_{2},q_{2},m_{2}>dP\quad
\end{array}$$


Noi informatici di base progettiamo un sistema di input ben preciso e se l'utente erra nell'usarlo non è un problema. Logicamente invece dovremmo creare l'insieme *totale* delle quintuple, per ogni caso.
- È ottimale fare un sistema di errori, negli stati interni
- È ottimale anche fare un sistema di print degli errori sul nastro

(Non verrà mai chiesto nell'esame di fare tutto)

Questo per i trasduttori, e per i riconoscitori?