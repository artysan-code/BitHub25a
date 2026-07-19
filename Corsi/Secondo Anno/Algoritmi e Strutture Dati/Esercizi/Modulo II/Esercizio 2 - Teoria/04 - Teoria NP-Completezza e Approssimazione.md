---
tags:
  - algoritmi
  - np-completezza
  - esercizi
---
# Teoria — NP-Completezza, Riduzioni e Approssimazione
*Esercizio 2 · NP-completezza e approssimazione · 6 domande da 3 appelli (16/07/2024 · 09/09/2024 · 24/09/2024).*

*Fonti: i compiti in `Materiale Didattico/Modulo II/Esami/2023-2024/`, appelli 16/07/2024, 09/09/2024, 24/09/2024. Nota sulla seconda data: l'intestazione del PDF di quell'appello riporta erroneamente «9/06/2024», ma nome file e collocazione in cartella (`ASD_compito2024_09_09_mod2.pdf`, sottocartella 2023-2024) indicano 09/09/2024 — data usata qui per coerenza con il resto del materiale del corso.*
## Come leggere questo file
Su 12 compiti analizzati, l'Esercizio 2 è **sempre** teoria discorsiva: due domande aperte da 11 punti, tipicamente da 5 righe ciascuna. Il tema NP-completezza/approssimazione occupa questo slot in tre appelli su dodici, e li copre in modo quasi sistematico: prima la meccanica astratta della riduzione (definizione e uso come evidenza di difficoltà), poi un'istanza concreta della riduzione più citata del corso (3-SAT verso Independent Set), infine un'applicazione a un problema di ottimizzazione NP-hard con una garanzia di approssimazione (load balancing).

Le trappole ricorrenti sono quattro. Il **verso** della riduzione: $X \leq_P Y$ dice che $X$ non è più difficile di $Y$, non il contrario — è l'errore più comune su questo argomento. La natura **condizionale** dell'argomento di intrattabilità: si dimostra "se $Y$ fosse facile, anche $X$ lo sarebbe", non "$Y$ è difficile" in assoluto. Un **refuso** del prof, «Independet Set» invece di «Independent Set», che compare identico in due domande dello stesso appello e va riportato verbatim. E, per il load balancing, la tentazione di enunciare **un solo** lemma di lower bound quando la traccia ne chiede esplicitamente due, con il loro ruolo nella dimostrazione.

Per il punteggio pieno: nelle domande "definisci", ogni quantificatore conta ($|S| \geq k$, "esattamente 3 letterali distinti", "macchine identiche") — è la differenza fra una definizione formale e una informale. Nelle domande "argomenta" o "mostra", va esplicitato lo schema logico (contronominale, per assurdo) e non solo la conclusione. Nella riduzione 3-SAT → Independent Set, la costruzione dell'istanza $(G,k)$ deve essere dichiarata polinomiale essa stessa, non solo la chiamata all'oracolo. Per approfondire la teoria sottostante vedi [[09 - NP-Completezza e Riduzioni]]; per il contrasto fra Independent Set trattabile (su grafi a intervalli) e NP-completo (su grafi generali) vedi [[04 - Programmazione Dinamica I (Weighted Independent Set)]].
## Riduzione polinomiale
Le due domande del 16/07/2024 coprono la riduzione polinomiale dai due lati opposti: prima la definizione formale — dove il verso di $\leq_P$ e il vincolo di dimensione sull'oracolo sono gli unici dettagli che decidono il punteggio pieno — poi il suo uso pratico come argomento (condizionale) di intrattabilità.
### Definizione formale di riduzione polinomiale
*citazione: 16/07/2024 · Es. 2, punto 1*

> Si definisca formalmente il concetto di riduzione polinomiale fra problemi. (Max 5 righe.)

> [!quote] Soluzione — da scrivere sul compito
> $X$ si riduce polinomialmente a $Y$, scritto $X \leq_P Y$, se esiste un algoritmo che risolve ogni istanza di $X$ usando un numero **polinomiale** di passi di calcolo standard, più un numero **polinomiale** di chiamate a un **oracolo** che risolve $Y$ in un singolo passo. Ogni istanza passata all'oracolo deve avere dimensione **polinomiale** rispetto a quella originale di $X$.
>
> **Interpretazione.** $X \leq_P Y$ significa che $X$ non è più difficile di $Y$: componendo un ipotetico algoritmo polinomiale per $Y$ con l'algoritmo di riduzione si ottiene un algoritmo polinomiale per $X$.

> [!info]- Spiegazione
> Due conteggi polinomiali, non uno: i passi standard dell'algoritmo di riduzione **e** il numero di chiamate all'oracolo devono essere entrambi polinomiali — un solo conteggio lascerebbe filtrare lavoro esponenziale nell'altro.
>
> **Il vincolo di dimensione sull'oracolo non è opzionale.** Senza l'ipotesi che l'istanza passata all'oracolo abbia dimensione polinomiale in quella di $X$, l'oracolo potrebbe nascondere lavoro esponenziale nella sola costruzione dell'istanza da passargli, e la definizione perderebbe significato.
>
> **Il verso.** $X \leq_P Y$ non dice che $Y$ è più facile di $X$: dice che $X$ eredita al più la difficoltà di $Y$. Confondere il verso — leggere $X \leq_P Y$ come "$Y$ non è più difficile di $X$" — è l'errore più comune su questo argomento, cfr. [[09 - NP-Completezza e Riduzioni#Riduzioni polinomiali]].
>
> **Dove si perdono punti:** omettere il vincolo di dimensione polinomiale sull'istanza passata all'oracolo, oppure invertire il verso della relazione nell'interpretazione finale.
### Le riduzioni come evidenza di difficoltà computazionale
*citazione: 16/07/2024 · Es. 2, punto 2*

> Si argomenti su come è possibile utilizzare le riduzioni polinomiali per dare evidenza che un problema è computazionalmente difficile. (Max 5 righe.)

> [!quote] Soluzione — da scrivere sul compito
> Si usa la **contronominale** della definizione: se $X \leq_P Y$ e $Y$ fosse risolvibile in tempo polinomiale, componendo con l'algoritmo di riduzione si otterrebbe un algoritmo polinomiale anche per $X$.
>
> **Argomento per assurdo.** Sia $X$ un problema (ritenuto) intrattabile con $X \leq_P Y$ dimostrata: se esistesse un algoritmo polinomiale per $Y$, la composizione darebbe un algoritmo polinomiale per $X$ — contraddizione con l'ipotesi su $X$. Quindi anche $Y$ deve essere intrattabile.
>
> **Applicazione a catena.** Concatenando riduzioni a partire da un problema NP-completo capostipite (tipicamente 3-SAT, via Cook-Levin) si trasferisce questa evidenza a un'intera famiglia di problemi, senza dover dimostrare l'intrattabilità di ciascuno da zero.

> [!info]- Spiegazione
> **È un argomento condizionale, non una dimostrazione di impossibilità.** Tutto il ragionamento poggia sulla premessa (non dimostrata) che $X$ sia effettivamente intrattabile — nella pratica, che $X$ sia NP-hard e $P \neq NP$. Non si dimostra che $Y$ non ammette algoritmo polinomiale in senso assoluto: si dimostra che se $Y$ lo ammettesse, allora anche $X$ lo ammetterebbe, contraddicendo la congettura dominante $P \neq NP$ — evidenza, non prova, coerente con [[09 - NP-Completezza e Riduzioni#Classi P e NP]].
>
> **Perché serve proprio la contronominale.** La definizione dice "$X \leq_P Y$": un algoritmo per $Y$ dà un algoritmo per $X$, non il contrario. Per usare questo fatto come evidenza di difficoltà di $Y$ occorre ragionare sulla contronominale logica: "$X$ intrattabile" implica "$Y$ intrattabile", ottenuta negando entrambi i lati dell'implicazione diretta.
>
> **Dove si perdono punti:** presentare il risultato come una dimostrazione categorica dell'intrattabilità di $Y$ invece che come argomento condizionato a $P \neq NP$; oppure dimenticare di ancorare la catena a un problema NP-completo di partenza (3-SAT via Cook-Levin), lasciando "intrattabile" senza fondamento.
## Problemi decisionali: 3-SAT e Independent Set
L'appello del 09/09/2024 apre l'Esercizio 2 con le definizioni formali dei due problemi decisionali al centro della riduzione più importante del corso. Il testo del prof riporta il refuso «Independet Set» (manca la seconda "n"): qui trascritto verbatim, come da regola.
### Definizioni formali di 3-SAT e Independent Set
*citazione: 09/09/2024 · Es. 2, punto 1*

> Si definiscano formalmente i problemi decisionali 3-SAT e Independet Set. (Max 5 righe.)

> [!quote] Soluzione — da scrivere sul compito
> **3-SAT.** Data una formula booleana $\Phi$ in forma normale congiuntiva (CNF), in cui ogni clausola contiene **esattamente 3 letterali distinti**, il problema chiede: esiste un assegnamento di verità alle variabili che soddisfa $\Phi$, cioè rende vero almeno un letterale in ciascuna clausola?
>
> **Independent Set.** Dato un grafo $G=(V,E)$ e un intero $k$, il problema chiede: esiste un sottoinsieme $S \subseteq V$ con $|S| \geq k$ tale che nessun arco di $E$ abbia entrambi gli estremi in $S$ (i vertici di $S$ sono a due a due non adiacenti)?

> [!info]- Spiegazione
> **Il refuso.** Il testo del compito scrive «Independet Set», senza la seconda "n" — refuso del prof, riportato verbatim nella citazione qui sopra e non corretto in silenzio.
>
> **Le clausole che non si possono omettere.** "Esattamente 3 letterali distinti" per 3-SAT (non "al più 3", non "3 letterali" senza "distinti") e "$|S| \geq k$" insieme a "nessun arco con entrambi gli estremi in $S$" per Independent Set sono le clausole che rendono la definizione **formale** e non solo intuitiva — cfr. [[09 - NP-Completezza e Riduzioni#SAT e 3-SAT]] e [[09 - NP-Completezza e Riduzioni#Independent Set]].
>
> **Perché proprio questi due problemi.** Non è un accoppiamento casuale: sono i due estremi della riduzione più citata del corso, discussa nella domanda successiva, che collega la soddisfacibilità booleana ai problemi di packing su grafi.
>
> **Dove si perdono punti:** definizioni "a parole" senza i quantificatori ($\exists$ assegnamento, $|S|\geq k$), o dimenticare che 3-SAT richiede letterali **distinti** in ogni clausola.
## La riduzione 3-SAT $\leq_P$ Independent Set
Il secondo punto dello stesso appello chiede di *usare* la riduzione, non solo di enunciarla: mostrare come un ipotetico algoritmo polinomiale per Independent Set risolverebbe 3-SAT, sfruttando la costruzione a triangoli-per-clausola discussa in [[09 - NP-Completezza e Riduzioni#La riduzione chiave: 3-SAT $\leq_P$ Independent Set]].
### Usare un ipotetico algoritmo per Independent Set per risolvere 3-SAT
*citazione: 09/09/2024 · Es. 2, punto 2*

> Si mostri come è possibile utilizzare un (ipotetico) algoritmo polinomiale per Independet Set per risolvere 3-SAT. (Max 5 righe.)

> [!quote] Soluzione — da scrivere sul compito
> Si sfrutta la riduzione $3\text{-SAT} \leq_P \text{INDEPENDENT-SET}$. Da $\Phi$ con $m$ clausole si costruisce in tempo **polinomiale** un'istanza $(G, k=m)$: per ogni clausola, un **triangolo** di 3 nodi (uno per letterale), archi interni fra i tre; più un arco fra ogni coppia di nodi che rappresentano un letterale e la sua **negazione** in clausole diverse.
>
> Si invoca l'ipotetico algoritmo polinomiale per Independent Set su $(G,k)$: se restituisce un independent set di dimensione $k$, $\Phi$ è soddisfacibile (l'assegnamento si ricostruisce assegnando vero ai letterali scelti, uno per triangolo); altrimenti $\Phi$ non lo è.
>
> Costruzione e chiamata all'oracolo sono entrambe polinomiali in $|\Phi|$: la procedura complessiva decide 3-SAT in tempo polinomiale.

> [!info]- Spiegazione
> **Perché funziona, direzione ⇒.** Da un assegnamento soddisfacente $\alpha$, si sceglie da ogni triangolo un letterale reso vero da $\alpha$: $k$ nodi in tutto. Sono indipendenti perché vengono da triangoli distinti (niente archi intra-triangolo fra loro) e perché $\alpha$ non può rendere veri sia $\ell$ sia $\overline{\ell}$ (niente arco di negazione fra nodi scelti).
>
> **Perché funziona, direzione ⇐.** Ogni triangolo è una clique $K_3$: un independent set non può contenere più di un suo nodo. Con $k$ triangoli e $|S|=k$, $S$ prende **esattamente un** nodo per triangolo. Assegnare vero ai letterali selezionati soddisfa ogni clausola senza contraddizioni, perché $S$ non contiene mai una coppia letterale/negazione (sarebbero collegati da un arco).
>
> **Il pattern.** È una **codifica con gadget**: il triangolo forza "al più un letterale per clausola" nella soluzione, gli archi di negazione codificano il vincolo logico di coerenza. Cfr. [[09 - NP-Completezza e Riduzioni#La riduzione chiave: 3-SAT $\leq_P$ Independent Set]].
>
> **Dove si perdono punti:** dimostrare solo una delle due direzioni dell'equivalenza (in 5 righe vanno almeno accennate entrambe); oppure dimenticare di dichiarare esplicitamente che anche la **costruzione** di $(G,k)$ — non solo la chiamata all'oracolo — deve essere polinomiale in $|\Phi|$, altrimenti l'intera riduzione non è valida.
## Load balancing e 2-approssimazione
Il 24/09/2024 sposta l'Esercizio 2 su un problema di ottimizzazione NP-hard concreto: prima la definizione del load balancing, poi — nelle 10 righe concesse dal secondo punto — i due lemmi di lower bound che fanno funzionare la dimostrazione del fattore 2 di List-Scheduling, discussa per esteso in [[09 - NP-Completezza e Riduzioni#Load Balancing — 2-approssimazione]].
### Definizione formale del problema di load balancing
*citazione: 24/09/2024 · Es. 2, punto 1*

> Si definisca formalmente il problema del load balancing. (Max 5 righe.)

> [!quote] Soluzione — da scrivere sul compito
> **Istanza.** $m$ macchine **identiche** e $n$ job, dove il job $j$ richiede un tempo di esecuzione $t_j > 0$. Un'assegnazione è una partizione dei job in $m$ insiemi $S_1,\ldots,S_m$ (i job assegnati alla macchina $i$); il **carico** della macchina $i$ è $L_i = \sum_{j \in S_i} t_j$.
>
> **Obiettivo.** Trovare un'assegnazione che minimizzi il **makespan** $L = \max_i L_i$, il carico della macchina più occupata.
>
> È un problema di **ottimizzazione NP-hard**: non ammette (verosimilmente) un algoritmo polinomiale esatto, ma ammette una 2-approssimazione in tempo polinomiale.

> [!info]- Spiegazione
> **"Identiche" non è un dettaglio.** Tutte le $m$ macchine eseguono un job $j$ nello stesso tempo $t_j$, indipendentemente da quale macchina lo esegue: è ciò che rende $L_i$ una semplice somma dei tempi assegnati, senza fattori di velocità per macchina.
>
> **Perché il makespan e non la somma dei carichi.** Minimizzare $\sum_i L_i$ sarebbe banale (è costante, pari a $\sum_j t_j$, qualunque sia l'assegnazione): l'obiettivo interessante è il **massimo**, perché misura quanto tempo serve prima che *tutte* le macchine abbiano finito.
>
> **Dove si perdono punti:** dimenticare "macchine identiche" nella definizione, oppure scrivere l'obiettivo come una somma invece che come un massimo sui carichi $L_i$.
### I due lemmi di lower bound e il loro ruolo nell'analisi del rapporto 2
*citazione: 24/09/2024 · Es. 2, punto 2 (max 10 righe)*

> Per l'analisi dell'algoritmo di 2-approssimazione per il problema del load balancing si usano due lemmi tecnici che forniscono dei lower bound al valore della soluzione ottima. Si enuncino formalmente i due lemmi e si descriva brevemente che ruolo giocano nell'analisi del rapporto di approssimazione. (Max 10 righe.)

> [!quote] Soluzione — da scrivere sul compito
> **Lemma 1.** $L^* \geq \max_k t_k$: qualche macchina deve eseguire il job più lungo, quindi il suo carico — e a maggior ragione il makespan ottimo — è almeno $\max_k t_k$.
>
> **Lemma 2.** $L^* \geq \frac{1}{m}\sum_k t_k$: il lavoro totale $\sum_k t_k$ va comunque distribuito su $m$ macchine, quindi almeno una ha carico pari o superiore alla media.
>
> **Ruolo nell'analisi.** Sia $i^*$ la macchina di carico massimo prodotta da List-Scheduling e $j$ l'ultimo job assegnatole: quando $j$ viene assegnato, $i^*$ ha il carico minimo, quindi $L_{i^*}-t_j \leq L_i$ per ogni $i$; sommando su tutte le macchine e dividendo per $m$ si ottiene $L_{i^*}-t_j \leq \frac{1}{m}\sum_i L_i = \frac{1}{m}\sum_k t_k \leq L^*$ (**Lemma 2**). Il **Lemma 1** copre l'ultimo pezzo, $t_j \leq \max_k t_k \leq L^*$. Sommando le due disuguaglianze: $L = L_{i^*} = (L_{i^*}-t_j)+t_j \leq L^*+L^* = 2L^*$.

> [!info]- Spiegazione
> **I due lemmi coprono i due addendi della somma finale**, non sono intercambiabili: il Lemma 2 (media sulle $m$ macchine) limita il termine $L_{i^*}-t_j$ — il carico accumulato da $i^*$ *prima* dell'ultimo job — mentre il Lemma 1 (job più pesante) limita $t_j$ stesso, l'ultimo contributo. Senza il Lemma 2 non si riesce a legare il carico "storico" di $i^*$ all'ottimo; senza il Lemma 1 non si riesce a legare l'ultimo job assegnato.
>
> **Perché $i^*$ ha carico minimo al momento dell'assegnazione di $j$.** È la regola greedy di List-Scheduling: ogni job viene assegnato alla macchina di carico minimo *corrente*. Se $j$ finisce su $i^*$, è perché in quel momento $i^*$ era la scelta di carico minimo — da cui $L_{i^*}-t_j \leq L_i$ per ogni altra macchina $i$, il punto di partenza dell'intera catena di disuguaglianze.
>
> **Il raffinamento LPT.** Ordinare i job in ordine decrescente di $t_j$ prima di applicare List-Scheduling migliora il fattore a $\frac32$: se ci sono più di $m$ job, l'ottimo deve valere almeno il doppio del tempo del $(m{+}1)$-esimo job più grande, un lower bound più stretto del Lemma 1 semplice — cfr. [[09 - NP-Completezza e Riduzioni#Load Balancing — 2-approssimazione]].
>
> **Dove si perdono punti:** enunciare un solo lemma invece di entrambi (la traccia ne chiede esplicitamente due); enunciarli correttamente ma senza descriverne il ruolo nella dimostrazione — la traccia lo richiede come parte separata della risposta, non è un extra facoltativo; oppure confondere $L^*$ (ottimo) con $L$ (soluzione di List-Scheduling) nelle disuguaglianze.
