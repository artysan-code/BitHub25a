## Calcolo Relazionale

## Algebra vs. Calcolo: due paradigmi a confronto

Il modello relazionale supporta due famiglie di linguaggi di interrogazione formalmente distinte:

- **Notazione algebrica** $\Rightarrow$ **Algebra relazionale** $\Rightarrow$ linguaggio *procedurale*: le interrogazioni si esprimono applicando operatori (selezione, proiezione, join, …) alle relazioni. Si specifica *come* ottenere il risultato.
- **Notazione logica** $\Rightarrow$ **Calcolo relazionale** $\Rightarrow$ linguaggio *dichiarativo*: le interrogazioni si esprimono tramite formule logiche le cui risposte devono essere rese vere dalle tuple. Si specifica *cosa* si vuole ottenere, non come calcolarlo.

Il calcolo relazionale è basato sulla **logica del primo ordine** (calcolo dei predicati), un linguaggio formale con semantica non ambigua e sistema formale di inferenza. Quasi tutti i linguaggi di interrogazione per basi di dati relazionali — SQL in testa — sono fondati sul calcolo relazionale.

Esistono due versioni principali, che studieremo entrambe:

- **Calcolo relazionale sui domini** (più vicino al calcolo dei predicati puro)
- **Calcolo relazionale sulle ennuple con dichiarazioni di range** (variazione del precedente; base dei costrutti degli attuali linguaggi)

## Struttura formale del calcolo relazionale

> [!quote] Definizione — Calcolo relazionale
> Il **calcolo relazionale** è una sestupla $\{A, D, \text{dom}, s, O, F\}$ dove:
> - $A$: insieme degli **attributi**
> - $D$: insieme dei **domini**
> - $\text{dom}: A \to D$: funzione che associa a ogni attributo il suo dominio
> - $s$: **schema** di base di dati
> - $O$: insieme degli **operatori di confronto** ($>, \geq, <, \leq, \neq, =$) e degli operatori **logici** ($\land, \lor, \lnot$) e dei **quantificatori** esistenziale ($\exists$) e universale ($\forall$)
> - $F$: insieme delle **formule ben formate** secondo il tipo di calcolo (ennuple o domini)

### Formule ben formate

Una **formula ben formata** è definita ricorsivamente a partire dagli **atomi**, che costituiscono le formule atomiche di base:

**Atomi:**
- $R(x)$, dove $R$ appartiene allo schema $s$ e $x$ è una *variabile di ennupla* (Calcolo delle Ennuple)
- $R(A_1{:}x_1, \dots, A_p{:}x_p)$, dove $R(A_1, \dots, A_p)$ è uno schema di relazione in $s$ e $x_1, \dots, x_p$ sono *variabili di dominio* (Calcolo dei Domini)
- $x \,\theta\, y$ oppure $x \,\theta\, c$, con $x$ e $y$ variabili (di ennupla o di dominio), $c$ costante e $\theta$ operatore di confronto

**Costruzione ricorsiva:**
- Se $f_1$ e $f_2$ sono formule ben formate, allora $f_1 \land f_2$, $f_1 \lor f_2$, $\lnot f_1$, $(f_1)$ sono formule ben formate. Le parentesi alterano l'ordine di precedenza standard ($\lnot$ precede $\land$ che precede $\lor$).
- Se $f$ è una formula ben formata e $x$ è una variabile, allora $\exists x(f)$ e $\forall x(f)$ sono formule ben formate.

### Verità delle formule

- Un **atomo** $R(A_1{:}x_1, \dots, A_p{:}x_p)$ è vero sui valori $x_1, \dots, x_p$ che formano una ennupla di $R$.
- Un **atomo** di confronto $x \,\theta\, y$ è vero quando i valori dei due termini soddisfano il confronto.
- Le formule costruite per **congiunzione, disgiunzione e negazione** seguono le regole usuali della logica proposizionale.
- $\exists x(f)$ è vera se **esiste almeno un** valore $a$ per $x$ che rende vera $f$.
- $\forall x(f)$ è vera se **per ogni** possibile valore $a$ di $x$, la formula $f$ risulta vera.

## Calcolo relazionale sui domini

### Struttura di un'espressione

> [!quote] Definizione — Espressione nel calcolo dei domini
> Un'espressione (query) nel **calcolo relazionale sui domini** ha la forma:
> $$\{ A_1{:}x_1, \dots, A_k{:}x_k \mid f \}$$
> dove $A_1, \dots, A_k$ sono attributi distinti, $x_1, \dots, x_k$ sono **variabili di dominio** (la *target list*) e $f$ è una formula ben formata che le variabili devono rendere vera.

Il risultato è l'insieme di tutte le ennuple $(A_1{:}x_1, \dots, A_k{:}x_k)$ tali che esiste un'assegnazione dei valori alle variabili libere $x_1, \dots, x_k$ che rende vera $f$.

### Base di dati di riferimento per gli esempi

Utilizziamo nel seguito due relazioni:

**Impiegati**(<u>Matricola</u>, Cognome, Età, Stipendio)

| Matricola | Cognome | Età | Stipendio |
|-----------|---------|-----|-----------|
| 101 | Rossi | 34 | 40 |
| 103 | Bianchi | 23 | 35 |
| 104 | Neri | 38 | 61 |
| 210 | Celli | 49 | 60 |
| 231 | Bisi | 50 | 60 |
| 252 | Bini | 44 | 70 |
| 301 | S. Rossi | 34 | 70 |
| 375 | M. Rossi | 50 | 65 |

**Supervisione**(<u>Capo</u>, <u>Impiegato</u>)

| Capo | Impiegato |
|------|-----------|
| 210 | 101 |
| 210 | 103 |
| 210 | 104 |
| 301 | 210 |
| 301 | 231 |
| 375 | 252 |

### Esempi di interrogazioni

> [!example] Matricola, Cognome ed Età degli impiegati con stipendio > 40
> **Calcolo dei domini:**
> $$\{ \text{Matricola}{:}m,\ \text{Cognome}{:}n,\ \text{Età}{:}e \mid \exists s\ \text{Impiegati}(\text{Matricola}{:}m, \text{Cognome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \land s > 40 \}$$
>
> La variabile $s$ (stipendio) non compare nella target list: è **quantificata esistenzialmente** perché interessa solo come condizione di filtro.
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 104 | Neri | 38 |
> | 210 | Celli | 49 |
> | 231 | Bisi | 50 |
> | 252 | Bini | 44 |
> | 301 | S. Rossi | 34 |
> | 375 | M. Rossi | 50 |

> [!example] Solo il Cognome degli impiegati con stipendio > 40
> $$\{ \text{Cognome}{:}n \mid \exists m\, \exists e\, \exists s\ \text{Impiegati}(\text{Matricola}{:}m, \text{Cognome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \land s > 40 \}$$
>
> Tutte le variabili non proiettate vengono quantificate esistenzialmente.

> [!example] Impiegati che guadagnano più del proprio capo (nome, stipendio dell'impiegato e del capo)
> **Algebra relazionale** (per confronto):
> $$\pi_{\text{Nome,Stip,MatrC,NomeC,StipC}}\left(\sigma_{\text{Stipendio} > \text{StipC}}\left(\rho_{\text{MatrC,NomeC,StipC,EtàC} \leftarrow \text{Matr,Nome,Stip,Età}}(\text{Impiegati}) \bowtie_{\text{MatrC}=\text{Capo}} \text{Supervisione} \bowtie_{\text{Impiegato}=\text{Matricola}} \text{Impiegati}\right)\right)$$
>
> **Calcolo dei domini:**
> $$\{ \text{Nome}{:}n,\ \text{Stip}{:}s,\ \text{NomeC}{:}nc,\ \text{StipC}{:}sc \mid$$
> $$\text{Impiegati}(\text{Matr}{:}m, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \land (s > sc)$$
> $$\land\ \text{Supervisione}(\text{Impiegato}{:}m, \text{Capo}{:}c)$$
> $$\land\ \text{Impiegati}(\text{Matr}{:}c, \text{Nome}{:}nc, \text{Età}{:}ec, \text{Stipendio}{:}sc) \}$$

> [!example] Matricole e nomi dei capi i cui impiegati guadagnano TUTTI più di 40
> L'interrogazione usa la **negazione** del quantificatore esistenziale per simulare il $\forall$:
>
> **Versione con negazione dell'esistenziale:**
> $$\{ \text{Matricola}{:}c,\ \text{Nome}{:}n \mid \text{Impiegati}(\text{Matr}{:}c, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s)$$
> $$\land\ \text{Supervisione}(\text{Impiegato}{:}m, \text{Capo}{:}c)$$
> $$\land\ \lnot(\exists m'(\exists n'(\exists e'(\exists s'\ \text{Impiegati}(\text{Matr}{:}m', \text{Nome}{:}n', \text{Età}{:}e', \text{Stipendio}{:}s')$$
> $$\land\ \text{Supervisione}(\text{Impiegato}{:}m', \text{Capo}{:}c) \land (s' \leq 40))))) \}$$
>
> **Versione con quantificatore universale** (equivalente):
> $$\{ \text{Matricola}{:}c,\ \text{Nome}{:}n \mid \text{Impiegati}(\text{Matr}{:}c, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s)$$
> $$\land\ \forall m'(\forall n'(\forall e'(\forall s'\ \text{Impiegati}(\text{Matr}{:}m', \text{Nome}{:}n', \text{Età}{:}e', \text{Stipendio}{:}s')$$
> $$\land\ \text{Supervisione}(\text{Impiegato}{:}m', \text{Capo}{:}c) \Rightarrow (s' > 40)))) \}$$

## Limiti del calcolo sui domini: espressioni dipendenti dal dominio

Il calcolo relazionale sui domini ammette espressioni **sintatticamente corrette ma semanticamente problematiche**. Considerare ad esempio:

- $\{ A_1{:}x_1,\ A_2{:}x_2 \mid R(A_1{:}x_1) \land (x_2 = x_2) \}$: la seconda variabile non è vincolata a nessuna relazione; il risultato dipende dall'estensione del dominio di $A_2$, che potrebbe essere infinito.
- $\{ A_1{:}x_1 \mid \lnot(R(A_1{:}x_1)) \}$: restituisce tutti i valori del dominio di $A_1$ che *non* compaiono in $R$, potenzialmente infiniti.

Il risultato di queste espressioni **cambia al variare del dominio** su cui vengono valutate, rendendo il linguaggio *dipendente dal dominio*.

> [!quote] Definizione — Indipendenza dal dominio
> Un linguaggio di interrogazione è **indipendente dal dominio** se il suo risultato, su ciascuna istanza di base di dati, non varia al variare del dominio rispetto al quale l'espressione è valutata.

### Ipotesi di mondo chiuso

La soluzione adottata è l'**ipotesi di mondo chiuso**: i domini sono ristretti ai valori presenti nell'istanza dello schema relazionale e alle costanti presenti nelle espressioni. Sotto questa ipotesi il calcolo relazionale diventa un linguaggio indipendente dal dominio e il risultato di ogni interrogazione è sempre finito.

> [!warning] Espressioni non sicure
> Le espressioni del calcolo dei domini che non rispettano l'ipotesi di mondo chiuso — ossia il cui risultato dipende dal dominio scelto o può essere infinito — si chiamano **espressioni non sicure** (*unsafe*). Un linguaggio pratico deve escluderle o garantire per costruzione che non si presentino.

## Difetti del calcolo sui domini e motivazione del calcolo sulle ennuple

Il calcolo relazionale sui domini presenta un difetto pratico ulteriore: **agisce sui domini** (valori atomici) invece che sulle ennuple. Questo lo rende *verboso*: per ogni relazione con $k$ attributi occorre introdurre $k$ variabili di dominio distinte, anche se molte non compaiono nel risultato. Occorre quindi un linguaggio che "focalizzi" le ennuple di interesse anziché i singoli valori.

## Calcolo relazionale sulle ennuple con dichiarazioni di range

### Struttura di un'espressione

> [!quote] Definizione — Espressione nel calcolo delle ennuple
> Un'espressione nel **calcolo relazionale sulle ennuple con dichiarazioni di range** ha la forma:
> $$\{ \text{Target list} \mid \text{Range list} \mid \text{Formula} \}$$
> dove:
> - **Target list**: lista degli obiettivi, con elementi della forma $x.Z$, $x.(Z_1, \dots, Z_k)$ oppure $x.*$ (tutti gli attributi di $x$)
> - **Range list**: elenco delle variabili libere della formula con i rispettivi *campi di variabilità* (le relazioni su cui rangiano), della forma $x(R)$
> - **Formula**: combinazione booleana di atomi del tipo $x.A\,\theta\,c$, $x.A\,\theta\,y.B$ (confronti tra attributi di ennuple diverse), $\exists x(R)(f)$ oppure $\forall x(R)(f)$

Le variabili non sono più variabili di dominio scalari ma **variabili di ennupla**: ciascuna si riferisce a un'intera ennupla di una relazione, e i suoi attributi si accedono con la notazione $x.A$.

### Esempi di interrogazioni

> [!example] Matricola, Cognome ed Età degli impiegati con stipendio > 40
> $$\{ i.(\text{Matr, Cognome, Età}) \mid i(\text{Impiegati}) \mid i.\text{Stip} > 40 \}$$
>
> oppure, per proiettare tutti gli attributi:
> $$\{ i.* \mid i(\text{Impiegati}) \mid i.\text{Stip} > 40 \}$$
>
> La **range list** $i(\text{Impiegati})$ dichiara che $i$ varia sulle ennuple di Impiegati. Non è necessario elencare gli attributi non proiettati.
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 104 | Neri | 38 |
> | 210 | Celli | 49 |
> | 231 | Bisi | 50 |
> | 252 | Bini | 44 |
> | 301 | S. Rossi | 34 |
> | 375 | M. Rossi | 50 |

> [!example] Impiegati che guadagnano più del proprio capo
> $$\{ t.[\text{Nome, Stip, NomeCapo, StipCapo}] \mid t(\text{Impiegati}) \mid$$
> $$(\exists x)(\text{Impiegati})((\exists y)(\text{Supervisione})((\exists z)(\text{Impiegati})($$
> $$\text{Impiegati}(x) \land \text{Supervisione}(y) \land (y.\text{Impiegato} = x.\text{Matr})$$
> $$\land\ \text{Impiegati}(z) \land (y.\text{Capo} = z.\text{Matr}) \land (t.\text{Nome} = x.\text{Nome})$$
> $$\land\ (t.\text{Stip} = x.\text{Stip}) \land (t.\text{NomeCapo} = z.\text{Nome}) \land (t.\text{StipCapo} = z.\text{Stip})$$
> $$\land\ (x.\text{Stip} > z.\text{Stip}))) \}$$

### Confronto con SQL

Il calcolo sulle ennuple è la base diretta di **SQL**: la clausola `FROM` corrisponde alla range list (dichiara le variabili di ennupla e le relazioni su cui rangiano), la clausola `WHERE` corrisponde alla formula, e la clausola `SELECT` corrisponde alla target list.

```sql
SELECT i.Matricola, i.Cognome, i.Eta
FROM   Impiegati i
WHERE  i.Stipendio > 40
```

## Limitazione del calcolo sulle ennuple: l'unione non è esprimibile

> [!warning] Il calcolo sulle ennuple non esprime l'unione
> Il calcolo relazionale sulle ennuple con dichiarazioni di range **non permette di esprimere tutte le interrogazioni** formulabili in algebra relazionale. In particolare, **l'unione** $R_1(AB) \cup R_2(AB)$ non è esprimibile: non è possibile assegnare a una variabile $x$ un range che spazi su due relazioni distinte contemporaneamente.
>
> Intersezione e differenza sono invece esprimibili.
>
> Per questa ragione SQL prevede un operatore esplicito `UNION`, mentre `INTERSECT` e `EXCEPT` non sono supportati in tutte le versioni dello standard.

## Equivalenza espressiva tra algebra e calcolo

> [!info] Teorema di equivalenza (Codd, 1972)
> È possibile dimostrare che:
> 1. Per ogni espressione del calcolo relazionale che sia **indipendente dal dominio** esiste un'espressione dell'algebra relazionale equivalente ad essa.
> 2. Per ogni espressione dell'**algebra relazionale** esiste un'espressione del calcolo relazionale equivalente ad essa.
>
> La dimostrazione è costruttiva: si procede in modo ricorsivo a partire dagli operatori di base, traducendo ciascun operatore algebrico in una formula del calcolo e viceversa.

L'insieme delle interrogazioni esprimibili con l'algebra relazionale coincide quindi con l'insieme delle interrogazioni del calcolo relazionale che siano indipendenti dal dominio. Questo insieme definisce la nozione di **completezza relazionale** (*relational completeness*): un linguaggio di interrogazione è relativamente completo se può esprimere almeno tutto ciò che è esprimibile in algebra relazionale.

### SQL come sintesi

SQL nasce come linguaggio che integra i due paradigmi:

| Contributo | Provenienza |
|---|---|
| Operatori di selezione, proiezione, join | Algebra relazionale |
| Struttura dichiarativa SELECT-FROM-WHERE | Calcolo sulle ennuple |
| Quantificatori EXISTS, NOT EXISTS | Calcolo dei domini / ennuple |
| UNION esplicita | Aggiunta necessaria (non esprimibile nel calcolo sulle ennuple) |

## Limiti condivisi di algebra e calcolo

Algebra relazionale e calcolo relazionale sono **sostanzialmente equivalenti** e il concetto è *robusto*: entrambi definiscono lo stesso insieme di interrogazioni esprimibili. Esistono però interrogazioni significative che nessuno dei due può esprimere:

- **Calcolo di valori derivati**: è possibile solo *estrarre* valori presenti nei dati, non calcolarne di nuovi (somme, differenze tra valori di ennuple diverse, conversioni di unità, medie). Queste estensioni sono state aggiunte in SQL tramite espressioni aritmetiche nella `SELECT` e funzioni di aggregazione (`SUM`, `AVG`, `COUNT`, …).
- **Interrogazioni inerentemente ricorsive**: il caso prototipico è la **chiusura transitiva**.

### La chiusura transitiva

Data la relazione $\text{Supervisione}(\underline{\text{Impiegato}}, \text{Capo})$, l'interrogazione "trovare per ogni impiegato *tutti* i superiori (il capo, il capo del capo, e così via)" richiede di seguire la catena di supervisione a profondità arbitraria.

> [!example] Chiusura transitiva — istanza e risultato atteso
> **Supervisione**
>
> | Impiegato | Capo |
> |-----------|------|
> | Rossi | Lupi |
> | Neri | Bruni |
> | Lupi | Falchi |
>
> **Superiori** (risultato desiderato)
>
> | Impiegato | Superiore |
> |-----------|-----------|
> | Rossi | Lupi |
> | Neri | Bruni |
> | Lupi | Falchi |
> | Rossi | Falchi |

In algebra relazionale si potrebbe calcolare la chiusura transitiva *per un'istanza specifica* con una sequenza di join (self-join con ridenominazione), ma il numero di join necessari dipende dalla profondità della gerarchia, che non è nota a priori e non ha limite superiore fisso. Non esiste quindi una singola espressione algebrica che calcoli la chiusura transitiva per *qualunque* istanza.

> [!warning] Chiusura transitiva: non esprimibile in algebra né in calcolo
> Non esiste in algebra relazionale né in calcolo relazionale un'espressione che, per ogni relazione binaria arbitraria, ne calcoli la chiusura transitiva. Per ciascuna relazione concreta è possibile scrivere un'espressione ad hoc (con un numero di join pari alla profondità massima della catena), ma non un'espressione generale. Per questo SQL:1999 ha introdotto le **Common Table Expressions ricorsive** (`WITH RECURSIVE`).

## Datalog: cenni

**Datalog** è un linguaggio di programmazione logica per basi di dati, derivato dal Prolog, che supera il limite della non ricorsività. Utilizza predicati di due tipi:

- **Estensionali**: corrispondono alle relazioni della base di dati (fatti noti).
- **Intensionali**: corrispondono a viste o relazioni derivate (definite tramite regole).

### Sintassi

Le interrogazioni Datalog sono espresse tramite **regole** della forma:

$$\text{testa} \leftarrow \text{corpo}$$

dove *testa* è un predicato atomico intensionale e *corpo* è una congiunzione di predicati atomici. Le interrogazioni effettive sono predicati atomici preceduti convenzionalmente da `?`.

> [!example] Datalog — Esempio -1: impiegati con 30 anni
> **Calcolo dei domini** equivalente:
> $$\{ \text{Matricola}{:}m, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s \mid \text{Impiegati}(\text{Matricola}{:}m, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \land e = 30 \}$$
>
> **Datalog** (interrogazione diretta, senza predicato intensionale):
> ```
> ? Impiegati(Matricola: m, Nome: n, Età: 30, Stipendio: s)
> ```
> La costante `30` nell'argomento dell'atomo sostituisce il confronto esplicito.

> [!example] Datalog — Esempio 0a: impiegati ricchi (stipendio > 40)
> Serve un **predicato intensionale** perché il confronto non può essere espresso direttamente nell'argomento:
> ```
> ImpRicchi(Matricola: m, Nome: n, Età: e, Stipendio: s)
>   ← Impiegati(Matricola: m, Nome: n, Età: e, Stipendio: s), s > 40
>
> ? ImpRicchi(Matricola: m, Nome: n, Età: e, Stipendio: s)
> ```

> [!example] Datalog — Esempio 0b: proiezione (matricola, nome, età di tutti gli impiegati)
> **Algebra**: $\pi_{\text{Matricola, Nome, Età}}(\text{Impiegati})$
>
> **Calcolo dei domini**: $\{ \text{Matricola}{:}m, \text{Nome}{:}n, \text{Età}{:}e \mid \text{Impiegati}(\text{Matricola}{:}m, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \}$
>
> **Datalog**:
> ```
> InfoPubbliche(Matricola: m, Nome: n, Età: e)
>   ← Impiegati(Matricola: m, Nome: n, Età: e, Stipendio: s)
>
> ? InfoPubbliche(Matricola: m, Nome: n, Età: e)
> ```

> [!example] Datalog — Esempio 2: capi degli impiegati ricchi
> Trovare le matricole dei capi degli impiegati che guadagnano più di 40.
>
> **Calcolo dei domini**: $\{ \text{Capo}{:}c \mid \text{Supervisione}(\text{Capo}{:}c, \text{Impiegato}{:}m) \land \text{Impiegati}(\text{Matr}{:}m, \text{Nome}{:}n, \text{Età}{:}e, \text{Stipendio}{:}s) \land s > 40 \}$
>
> **Datalog** (riutilizza il predicato `ImpRicchi` definito sopra):
> ```
> CapiDeiRicchi(Capo: c)
>   ← ImpRicchi(Matricola: m, Nome: n, Età: e, Stipendio: s),
>     Supervisione(Capo: c, Impiegato: m)
>
> ? CapiDeiRicchi(Capo: c)
> ```

> [!example] Datalog — Esempio 5: capi i cui impiegati guadagnano TUTTI più di 40
> Serve la **negazione** (stratificata): si definisce prima il predicato degli "capi con almeno un impiegato non ricco", poi lo si nega.
> ```
> CapiDiNonRicchi(Capo: c)
>   ← Supervisione(Capo: c, Impiegato: m),
>     Impiegati(Matricola: m, Nome: n, Età: e, Stipendio: s),
>     s ≤ 40
>
> CapiSoloDiRicchi(Matricola: c, Nome: n)
>   ← Impiegati(Matricola: c, Nome: n, Età: e, Stipendio: s),
>     Supervisione(Capo: c, Impiegato: m),
>     not CapiDiNonRicchi(Capo: c)
>
> ? CapiSoloDiRicchi(Matricola: c, Nome: n)
> ```

> [!example] Datalog ricorsivo — Esempio 6: chiusura transitiva dei superiori
> Trovare per ogni impiegato tutti i superiori (capo, capo del capo, …). Serve la **ricorsione**: il predicato `Superiore` è definito in termini di se stesso.
> ```
> Superiore(Impiegato: i, SuperCapo: c)
>   ← Supervisione(Impiegato: i, Capo: c)
>
> Superiore(Impiegato: i, SuperCapo: c)
>   ← Supervisione(Impiegato: i, Capo: c'),
>     Superiore(Impiegato: c', SuperCapo: c)
>
> ? Superiore(Impiegato: i, SuperCapo: c)
> ```
> La prima regola è il **caso base** (il capo diretto è un superiore); la seconda è il **caso ricorsivo** (se $c'$ è capo diretto di $i$ e $c$ è superiore di $c'$, allora $c$ è superiore di $i$).

### Potere espressivo di Datalog

| Variante | Equivalenza |
|---|---|
| Datalog non ricorsivo senza negazione | Calcolo senza negazione e senza $\forall$ |
| Datalog non ricorsivo con negazione | Calcolo completo e algebra relazionale |
| Datalog ricorsivo senza negazione | Incomparabile con il calcolo (esprime la chiusura transitiva, ma non la differenza) |
| Datalog ricorsivo con negazione | Strettamente più espressivo di calcolo e algebra |

> [!info] Semantica della ricorsione
> La definizione della semantica delle regole ricorsive è delicata, in particolare in presenza di negazione (rischio di cicli e inconsistenza). La soluzione standard è la **negazione stratificata**: le regole vengono suddivise in strati in modo che la negazione non compaia in cicli; ogni strato viene valutato completamente prima del successivo.
