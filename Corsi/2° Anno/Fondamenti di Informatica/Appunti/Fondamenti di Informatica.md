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
- **Non ambiguo**: per ogni condizione possibile c'è esattamente un'istruzione applicabile — non può capitare che due istruzioni diverse siano entrambe applicabili nella stessa situazione.
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

Nella prossima lezione formalizzeremo tutto questo in modo rigoroso.
## Lezione 2
