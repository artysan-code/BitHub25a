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

Nella prossima lezione formalizzeremo tutto questo in modo rigoroso.
## Lezione 2
Esempio pratico:
data una parola costruita da caretteri in 0,1 il numero di 1 contenuti nella parola è pari o dispari?

Viene quindi scritta una parola binaria sul nastro della macchina di Turing e dato il programma facciamo che alla fine della computazione scrive sul terzo nastro la parola p se è pari e la parola d se è dispari.

Qualche osservazione:
- Quando arriva un blank sappiamo che la parola scritta sul nastro è termianta. 
- Supponiamo $q_{i}$ come stato iniziale e $q_{f}$ come stato finale.
- Lavoriamo su una sola testina

Programma:
<$q_{i},1,\square,q_{d},d$>
<$q_{i},0,\square,q_{p},d$>
<$q_{i},\square,p,q_{f},f$>
<$q_{p},0,\square,q_{p},d$>
<$q_{p},1,\square,q_{d},d$>
<$q_{d},0,\square,q_{d},d$>
<$q_{d},1,\square,q_{p},d$>
<$q_{p},\square,p,q_{f},f$>

Chiamamo per esempio questa macchina di Turing $T_{parità}$ che corrisponde a:$$T_{parità}\implies<\{0,1,p,d\},\{q_{i},q_{p},q_{d},q_{f}\},q_{i},q_{f},P_{parità}>$$
Se vogliamo generalizzzare una macchina generica:$$T_{generica}=<\Sigma,Q,q_{0},Q_{F},P>$$
Dove:
- $\Sigma$ sappiamo essere l'alfabeto
- Q l'insieme totale degli stati
- P l'insieme di quintuple del programma
- $q_{0}$ lo stato iniziale
- $Q_{f}$ l'insieme degli stati finali il cui numero dipende da (???)
  
Se:$$\begin{array}{}
\text{1 nastro}\implies P\leq Q\ x\ (\Sigma \cup \{\square\})\ x\ (\Sigma \cup \{\square\})\ x\ Q\ x\ \{s,f,d\} \\
\text{k nastri}\implies P\leq Q\ x\ (\Sigma \cup \{\square\})^k\ x\ (\Sigma \cup \{\square\})^k\ x\ Q\ x\ \{s,f,d\}
\end{array}$$
Piccola cosa:$$\begin{array}{}
\{a,b\} \\
\{a,b\}^2=\{(a,a),(a,b),(b,a),(b,b)\}
\end{array}$$

Per ogni coppia stato simbolo ne esiste solo una, per la [[Fondamenti di Informatica#^2c2748|non ambiguità]]:$$P:Q\ x\ ((\Sigma \cup \{\square\}))\implies(\Sigma \cup \{\square\})\ x\ Q\ \{s,f,d\}$$
La macchina di Turing non sempre si ferma, in quanto a causa di un errore dell'input potrebbe andare all'infinito, possiamo quindi aggiungere ad esempio:$$<q_{i},p,\square,q_{e},f>$$
Dove $q_{e}$ corrisponde ad uno stato d'errore. Questo però non risolverebbe **ogni input**.

Altra intuizione, non scriviamo il simbolo $\square$ nell'alfabeto (durante la definizione), sennò l'utente può scrivere nella parola il simbolo $\square$.

Generalmente però non completiamo mai l'insieme delle quintuple.

Altro esercizio un po' più complesso.

$T_{somma}\implies<\Sigma,Q,q_{0},Q_{F},P>$
$\Sigma=\{0,1,2,\dots,9,+\}$

In questo caso possiamo usare un secondo nastro al fine di output, perché è più semplice. Ancora più semplice, i due numeri da sommare hanno lo stesso numero di cifre.

Programma:
$$\begin{array}{l}
<q_{0},(x,\square),(x,\square),q_{0},(d,f)>&\forall x\ \exists\{0,\dots,9\} \\
<q_{0},(+,\square),(+,\square),q_{ind},(s,f)> \\
<q_{ind},(x,\square),(+,\square),q^{x_{0}},(d,f)>&\forall x\ \exists\{0,\dots,9\} \\
<q^{x_{0}},(y,\square),(y,\square),q^{x_{0}}_{ind},(d,f)>&\forall x\ \exists\{0,\dots,9\}\ \&\ \forall y\ \exists\{0,\dots,9\}\cup\{+\} \\
<q^{x_{0}},(\square,\square),(\square,\square),q^{x_{0}}_{ind},(d,f)>&\forall x\ \exists\{0,\dots,9\} \\
<q_{ind}^{1},(x,\square),(x,\square),q_{ind}^1,(s,f)> \\
<q_{ind}^{1},(+,\square),(+,\square),q_{+}^1,(s,f)> \\
<q_{+}^{1},(+,\square),(+,\square),q_{+}^1,(s,f)> \\
<q_{+}^{1},(x,\square),(+,\square),q^{x_{1}},(d,f)> \\
<q_{+}^{1},(\square,\square),(\square,1),q_{f},(f,f)> \\
<q_{+}^{0},(\square,\square),(\square,\square),q_{f},(f,f)>
\end{array}$$

Esercizio da rivedere e capire.

Se non sai dire che cos'è la macchina di turing bocciato (immagino definizione e esercizio).

> [!Important] Stato Globale
> Possiamo definirlo come una fotografia della macchina di turing ad un certo istante, che magari chiamiamo q. Salva come informazioni: lo stato interno della macchina, il contenuto del nastro, e posiziona q prima di dove è posizionato il nastro (o dopo non saprei ho capito male forse da vedere), non è fisico come salvataggio ma serve per molte definizioni.
> 

^^^ IMPARARE ASSOLUTAMENTE

Esempio:

$\text{Parola: abcd}\ \&\ \text{ stato q con testina su b}\implies a\ q\ b\ c\ d$
$\text{Parola: aacd}\ \&\ \text{ stato q' con testina sulla prima a}\implies q\ a\ a\ c\ d$

Eseguiamo un passaggio $SG_{1}\implies SG_{2}$ se $\exists<q,b,a,q,s>\ \in P$

(Da fare definizione) Transizione: eseguendo una quintupla passiamo da uno stato globale ad un altro. IMPORTANTE

Stato globale iniziale: quando abbiamo la testina sulla cella più a sinistra e ci troviamo nello stato interno iniziale.

(Da fare definizione) Computazione:  una sequenza di transizioni tra stati globale 

$SG_{0}\implies SG_{1}\implies\ \dots\ \implies SG_{h}\implies\ \dots$

- $SG_{0}$ iniziale
- $SG_{h}$ può essere che:
	- Non c'è più alcuna quintupla che può essere eseguita, e quindi la macchina si ferma. **La computazione termina**
	- Se non vi è, allora potrebbe essere una **computazione che non termina**

Esempio:$$<q_{0},a,a,q_{0},f>$$