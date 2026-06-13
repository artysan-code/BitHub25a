## Linguaggi per basi di dati

I linguaggi per basi di dati si suddividono in due categorie principali:
- **DDL** (Data Definition Language): operazioni sullo schema.
- **DML** (Data Manipulation Language): operazioni sui dati, a loro volta suddivise in *interrogazione* (query) e *aggiornamento*.

### Linguaggi di interrogazione

I linguaggi di interrogazione per basi di dati relazionali si classificano in:

- **Dichiarativi**: specificano le *proprietà* del risultato ("**che cosa**"). Si descrive il risultato desiderato, non il modo per ottenerlo.
- **Procedurali**: specificano le *modalità di generazione* del risultato ("**come**"). Si descrive la sequenza di operazioni da eseguire.

I principali linguaggi relazionali sono:
- **Algebra relazionale**: procedurale. È un insieme di operatori su relazioni che producono relazioni e possono essere composti.
- **Calcolo relazionale**: dichiarativo (teorico). Basato sul calcolo dei predicati del primo ordine; usa connettivi e clausole per descrivere la relazione risultato.
- **SQL** (Structured Query Language): intermedio (reale), il linguaggio standard dei DBMS.
- **QBE** (Query by Example): dichiarativo (reale).

## Algebra Relazionale

> [!quote] Definizione — Algebra relazionale
> L'**algebra relazionale** è un linguaggio **procedurale** e **chiuso**: ogni operatore accetta relazioni come argomento e restituisce una relazione. Le interrogazioni sono espressioni composte di operatori che producono relazioni.

La proprietà di **chiusura** è fondamentale: poiché input e output sono sempre relazioni, gli operatori possono essere composti liberamente in espressioni arbitrariamente complesse.

Gli operatori di base si suddividono in tre gruppi:
1. **Operatori insiemistici**: *unione*, *differenza*, *intersezione* — derivati dalla teoria degli insiemi.
2. **Operatori specifici**: *ridenominazione*, *selezione*, *proiezione* — propri dell'algebra relazionale.
3. **Join**: *join naturale*, *theta-join*, *prodotto cartesiano* — per correlare dati in relazioni diverse.

### Definizione formale

L'algebra relazionale è formalmente una quintupla:

$$\mathcal{AR} = \langle \mathcal{R}, \mathcal{A}, \mathcal{D}, dom, Op \rangle$$

dove:
- $\mathcal{R}$: insieme di relazioni (schema di base di dati).
- $\mathcal{A}$: insieme di attributi (nomi di colonne).
- $\mathcal{D}$: insieme di domini (tipi di dati).
- $dom$: funzione $\mathcal{A} \to \mathcal{D}$ che associa ogni attributo al suo dominio.
- $Op$: insieme degli operatori primitivi $\{\sigma, \pi, \times, \cup, -\}$.

> [!info] Completezza e minimalità
> Un insieme di operatori è **completo** (Codd, 1972) se può esprimere qualsiasi query definibile tramite formule atomiche ($A\,\theta\,c$ o $A\,\theta\,B$, con $\theta \in \{=, <, >, \leq, \geq, \neq\}$) e connettivi logici $(\land, \lor, \lnot)$. L'insieme $\{\sigma, \pi, \times, \cup, -\}$ è completo. È anche **minimale** perché nessun operatore è ridondante: $\sigma$ non è esprimibile con $\{\pi, \times, \cup, -\}$ e $\times$ non è esprimibile con $\{\sigma, \pi, \cup, -\}$. L'intersezione $\cap$ invece è ridondante: $R \cap S = R - (R - S)$.

## Operatori insiemistici

Le relazioni sono insiemi di tuple omogenee. Gli operatori insiemistici hanno senso solo tra relazioni **unione-compatibili**, ovvero definite sullo stesso insieme di attributi (stessi nomi e stessi domini).

> [!warning] Unione-compatibilità
> L'unione fra due relazioni su tuple *non* omogenee non è una relazione valida. Prima di applicare operatori insiemistici è necessario verificare che le relazioni abbiano lo stesso schema, o usare la **ridenominazione** per renderle compatibili.

### Unione

> [!quote] Definizione — Unione
> L'**unione** $r_1 \cup r_2$ di due relazioni $r_1$ e $r_2$ definite sullo stesso insieme di attributi $X$ è la relazione su $X$ contenente le tuple che appartengono a $r_1$ o a $r_2$ (o ad entrambe). I duplicati sono eliminati.

### Intersezione

> [!quote] Definizione — Intersezione
> L'**intersezione** $r_1 \cap r_2$ di due relazioni $r_1$ e $r_2$ definite sullo stesso insieme di attributi $X$ è la relazione su $X$ contenente le tuple che appartengono sia a $r_1$ che a $r_2$.

### Differenza

> [!quote] Definizione — Differenza
> La **differenza** $r_1 - r_2$ di due relazioni $r_1$ e $r_2$ definite sullo stesso insieme di attributi $X$ è la relazione su $X$ contenente le tuple che appartengono a $r_1$ e non a $r_2$.

> [!example] Laureati e Dirigenti — operatori insiemistici
>
> **Laureati**
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 1 | Rossi | 37 |
> | 2 | Neri | 36 |
> | 3 | Bianchi | 28 |
>
> **Dirigenti**
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 9 | Verdi | 51 |
> | 2 | Neri | 36 |
> | 3 | Bianchi | 28 |
>
> **Laureati $\cap$ Dirigenti**
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 2 | Neri | 36 |
> | 3 | Bianchi | 28 |
>
> **Laureati $-$ Dirigenti**
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 1 | Rossi | 37 |
>
> **Laureati $\cup$ Dirigenti**
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 1 | Rossi | 37 |
> | 2 | Neri | 36 |
> | 3 | Bianchi | 28 |
> | 9 | Verdi | 51 |

## Ridenominazione

> [!quote] Definizione — Ridenominazione
> L'operatore di **ridenominazione** $\rho_{B \leftarrow A}(R)$ è un operatore **monadico** che cambia il nome dell'attributo $A$ in $B$ nella relazione $R$, lasciando inalterata l'istanza. Formalmente, $\rho_{B_1,\dots,B_k \leftarrow A_1,\dots,A_k}(R)$ contiene tuple $t'$ tali che $t'[B_i] = t[A_i]$ per ogni $i$.

La ridenominazione è utile principalmente per rendere relazioni unione-compatibili prima di applicare operatori insiemistici.

> [!example] Genitore — unione di Paternità e Maternità
>
> **Paternità**
>
> | Padre | Figlio |
> |-------|--------|
> | Adamo | Abele |
> | Adamo | Caino |
> | Abramo | Isacco |
>
> **Maternità**
>
> | Madre | Figlio |
> |-------|--------|
> | Eva | Abele |
> | Eva | Set |
> | Sara | Isacco |
>
> Applicando $\rho_{\text{Genitore} \leftarrow \text{Padre}}(\text{Paternità})$ e $\rho_{\text{Genitore} \leftarrow \text{Madre}}(\text{Maternità})$, entrambe le relazioni diventano unione-compatibili su $(\text{Genitore}, \text{Figlio})$.
>
> $$\rho_{\text{Genitore} \leftarrow \text{Padre}}(\text{Paternità}) \cup \rho_{\text{Genitore} \leftarrow \text{Madre}}(\text{Maternità})$$
>
> **Risultato — Genitori**
>
> | Genitore | Figlio |
> |----------|--------|
> | Adamo | Abele |
> | Adamo | Caino |
> | Abramo | Isacco |
> | Eva | Abele |
> | Eva | Set |
> | Sara | Isacco |

## Selezione e Proiezione

Selezione e proiezione sono operatori complementari: la **selezione** opera sulle *righe* (restituisce un sottoinsieme di tuple conservando tutti gli attributi), la **proiezione** opera sulle *colonne* (restituisce tutti i valori su un sottoinsieme di attributi).

### Selezione

> [!quote] Definizione — Selezione
> La **selezione** $\sigma_F(r)$ è un operatore **monadico** che produce una relazione sugli stessi attributi di $r$ contenente le tuple di $r$ su cui la condizione $F$ è **vera**.

La condizione $F$ è una *formula proposizionale* su $X$, costruita combinando con $\land$ (and), $\lor$ (or), $\lnot$ (not) espressioni atomiche del tipo:
- $A\,\theta\,B$: vera se e solo se $t[A]\,\theta\,t[B]$ (confronto tra attributi).
- $A\,\theta\,c$: vera se e solo se $t[A]\,\theta\,c$ (confronto con costante).

dove $\theta \in \{\leq, <, =, >, \geq\}$ e $A$, $B$ sono attributi del dominio compatibile.

> [!example] Selezione su Dirigenti — condizione AND
>
> **Dirigenti**
>
> | Matricola | Cognome | Età | Stipendio |
> |-----------|---------|-----|-----------|
> | 9 | Verdi | 51 | 2700 |
> | 7 | Blu | 35 | 3000 |
> | 10 | Viola | 29 | 2000 |
>
> $\sigma_{\text{Età} > 50 \land \text{Stipendio} > 2500}(\text{Dirigenti})$
>
> | Matricola | Cognome | Età | Stipendio |
> |-----------|---------|-----|-----------|
> | 9 | Verdi | 51 | 2700 |

> [!example] Selezione su Cittadini — confronto tra attributi
>
> **Cittadini**
>
> | Cognome | Nome | Nascita | Residenza |
> |---------|------|---------|-----------|
> | Rossi | Mario | Roma | Milano |
> | Neri | Luca | Roma | Roma |
> | Verdi | Nico | Firenze | Firenze |
> | Rossi | Marco | Napoli | Firenze |
>
> $\sigma_{\text{Nascita} = \text{Residenza}}(\text{Cittadini})$
>
> | Cognome | Nome | Nascita | Residenza |
> |---------|------|---------|-----------|
> | Neri | Luca | Roma | Roma |
> | Verdi | Nico | Firenze | Firenze |

### Selezione con valori nulli

Quando un attributo contiene `NULL`, qualsiasi confronto ordinario ($=$, $<$, $>$, ...) produce il valore di verità **SCONOSCIUTO** (U), terzo valore della logica a tre valori $\{V, U, F\}$.

La logica a tre valori ha le seguenti tavole di verità:

| | not | | and | V | U | F | | or | V | U | F |
|--|-----|--|-----|---|---|---|--|----|----|---|---|
| F | V | | V | V | U | F | | V | V | V | V |
| U | U | | U | U | U | F | | U | V | U | U |
| V | F | | F | F | F | F | | F | V | U | F |

La selezione include una tupla nel risultato solo se la condizione vale **V** (vero). Una condizione che vale U (sconosciuto) fa sì che la tupla sia *esclusa*.

> [!warning] Effetto dei NULL sulla selezione
> Con la relazione **Persone** (Matricola, Cognome, Filiale, Età) dove Bruni ha Età = NULL:
>
> $\sigma_{\text{Età}>30}(\text{Persone}) \cup \sigma_{\text{Età}\leq30}(\text{Persone}) \neq \text{Persone}$
>
> perché Bruni è escluso da entrambe le selezioni (condizione = U). Anche:
>
> $\sigma_{\text{Età}>30 \lor \text{Età}\leq30}(\text{Persone}) \neq \text{Persone}$
>
> Occorre aggiungere esplicitamente il caso NULL:
>
> $\sigma_{\text{Età}>30 \lor \text{Età}\leq30 \lor \text{Età IS NULL}}(\text{Persone}) = \text{Persone}$

Per riferirsi ai valori nulli esistono due condizioni speciali:
- `A IS NULL`: vera su una tupla $t$ se $t[A]$ è nullo; falsa se è specificato.
- `A IS NOT NULL`: vera su una tupla $t$ se $t[A]$ è specificato; falsa se è nullo.

### Proiezione

> [!quote] Definizione — Proiezione
> Dati una relazione $r(X)$ e un sottoinsieme $Y \subseteq X$, la **proiezione** $\pi_Y(r)$ è l'insieme delle tuple su $Y$ ottenute dalle tuple di $r$ considerando solo i valori su $Y$:
>
> $$\pi_Y(r) = \{t[Y] \mid t \in r\}$$

La proiezione ha un numero di tuple *minore o uguale* a quello di $r$: tuple diverse in $r$ possono diventare identiche dopo la proiezione (eliminazione dei duplicati). Il numero è uguale se e solo se $Y$ è **superchiave** per $r$.

> [!example] Proiezione su Cittadini
>
> **Cittadini**
>
> | Cognome | Nome | Nascita | Residenza |
> |---------|------|---------|-----------|
> | Rossi | Mario | Roma | Milano |
> | Neri | Luca | Roma | Roma |
> | Verdi | Nico | Firenze | Firenze |
> | Rossi | Marco | Napoli | Firenze |
>
> $\pi_{\text{Cognome}}(\text{Cittadini})$: i duplicati vengono eliminati.
>
> | Cognome |
> |---------|
> | Rossi |
> | Neri |
> | Verdi |
>
> $\pi_{\text{Cognome, Nome}}(\text{Cittadini})$: nessun duplicato in questo caso.
>
> | Cognome | Nome |
> |---------|------|
> | Rossi | Mario |
> | Neri | Luca |
> | Verdi | Nico |
> | Rossi | Marco |

## Join

Il **join** è l'operatore più importante dell'algebra relazionale: selezione e proiezione permettono di estrarre informazioni da *una* relazione, ma non di correlare dati in relazioni diverse. Il join risolve questo problema, evidenziando la proprietà del modello relazionale di essere **basato su valori**.

### Join naturale

> [!quote] Definizione — Join naturale
> Il **join naturale** $r_1 \bowtie r_2$ di $r_1(X_1)$ e $r_2(X_2)$ è una relazione definita su $X_1 \cup X_2$ (che si scrive $X_1 X_2$):
>
> $$r_1 \bowtie r_2 = \{t \text{ su } X_1 X_2 \mid t[X_1] \in r_1 \text{ e } t[X_2] \in r_2\}$$

Il join naturale correla dati sulla base di valori uguali negli **attributi con lo stesso nome**. Gli attributi comuni compaiono una sola volta nel risultato: il grado della relazione risultante è $\leq |X_1| + |X_2|$.

Casi limite:
- Se $X_1 \cap X_2 = \emptyset$, il join naturale equivale al **prodotto cartesiano**.
- Se $X_1 = X_2$, il join naturale equivale all'**intersezione**.

#### Join completo e tuple dangling

> [!quote] Definizione — Join completo e dangling
> Un join si dice **completo** se ogni tuple di ciascun operando contribuisce ad almeno una tupla del risultato. Le tuple che non trovano corrispondenza e vengono quindi escluse si dicono **dangling** (appese, incomplete).

> [!example] Join naturale completo — Impiegati e Reparti
>
> **$R_1$ (Impiegati)**
>
> | Impiegato | Reparto |
> |-----------|---------|
> | Rossi | vendite |
> | Neri | produzione |
> | Bianchi | produzione |
>
> **$R_2$ (Reparti)**
>
> | Reparto | Capo |
> |---------|------|
> | produzione | Mori |
> | vendite | Bruni |
>
> $R_1 \bowtie R_2$ — join completo (ogni tuple contribuisce):
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|
> | Rossi | vendite | Bruni |
> | Neri | produzione | Mori |
> | Bianchi | produzione | Mori |

> [!example] Join naturale non completo — tuple dangling
>
> **$R_1$**
>
> | Impiegato | Reparto |
> |-----------|---------|
> | Rossi | vendite |
> | Neri | produzione |
> | Bianchi | produzione |
>
> **$R_2$**
>
> | Reparto | Capo |
> |---------|------|
> | produzione | Mori |
> | marketing | Bruni |
>
> $R_1 \bowtie R_2$ — Rossi (vendite) e marketing (Bruni) sono tuple dangling:
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|
> | Neri | produzione | Mori |
> | Bianchi | produzione | Mori |

> [!example] Join vuoto — nessuna corrispondenza
>
> Se nessun valore dell'attributo comune coincide tra $R_1$ e $R_2$, il risultato è la relazione vuota (solo intestazione):
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|

#### Proprietà del join naturale

1. Il join di $r_1$ e $r_2$ contiene un numero di tuple compreso fra 0 e $|r_1| \cdot |r_2|$.
2. Se il join è **completo**, contiene almeno $\max(|r_1|, |r_2|)$ tuple.
3. Se $X_1 \cap X_2$ contiene una chiave per $r_2$, il join contiene almeno $|r_2|$ tuple.
4. Se il join coinvolge una chiave di $R_2$ e un **vincolo di integrità referenziale**, il numero di tuple è pari a $|R_1|$.
5. Il join è **commutativo**: $r_1 \bowtie r_2 = r_2 \bowtie r_1$.
6. Il join è **associativo**: $(r_1 \bowtie r_2) \bowtie r_3 = r_1 \bowtie (r_2 \bowtie r_3)$. Quindi sequenze di join possono essere scritte senza parentesi.

#### Join e proiezioni: perdita di informazione

Date $R_1(X_1)$ e $R_2(X_2)$, vale sempre:

$$\pi_{X_1}(R_1 \bowtie R_2) \subseteq R_1$$

La proiezione del join su $X_1$ è un sottoinsieme di $R_1$ (le tuple dangling vengono perse). Invece, dati $R(X)$ con $X = X_1 \cup X_2$:

$$(\pi_{X_1}(R)) \bowtie (\pi_{X_2}(R)) \supseteq R$$

Il join delle proiezioni può introdurre tuple spurie non presenti in $R$.

### Prodotto cartesiano

> [!quote] Definizione — Prodotto cartesiano
> Il **prodotto cartesiano** $r_1 \times r_2$ di $r_1(X_1)$ e $r_2(X_2)$, con $X_1 \cap X_2 = \emptyset$, è:
>
> $$r_1 \times r_2 = \{t \text{ su } X_1 X_2 \mid t[X_1] \in r_1 \text{ e } t[X_2] \in r_2\}$$

Il prodotto cartesiano è un join naturale su relazioni senza attributi in comune. Contiene sempre $|r_1| \cdot |r_2|$ tuple (tutte le coppie sono combinabili).

> [!example] Prodotto cartesiano — Impiegati e Reparti
>
> **Impiegati**
>
> | Impiegato | Reparto |
> |-----------|---------|
> | Rossi | A |
> | Neri | B |
> | Bianchi | B |
>
> **Reparti**
>
> | Codice | Capo |
> |--------|------|
> | A | Mori |
> | B | Bruni |
>
> **Impiegati $\times$ Reparti** (6 tuple = 3 × 2):
>
> | Impiegato | Reparto | Codice | Capo |
> |-----------|---------|--------|------|
> | Rossi | A | A | Mori |
> | Neri | B | A | Mori |
> | Bianchi | B | A | Mori |
> | Rossi | A | B | Bruni |
> | Neri | B | B | Bruni |
> | Bianchi | B | B | Bruni |

### Theta-join ed equi-join

Quando si devono correlare relazioni su attributi con **nome diverso**, si usa il **theta-join**.

> [!quote] Definizione — Theta-join
> Il **theta-join** $r_1 \bowtie_\theta r_2$ è definito come un prodotto cartesiano seguito da una selezione:
>
> $$r_1 \bowtie_\theta r_2 = \sigma_\theta(r_1 \times r_2)$$
>
> dove $\theta$ è una formula e $r_1$, $r_2$ non hanno attributi di nome comune.

Se $\theta$ è una relazione di **uguaglianza** tra un attributo della prima relazione e uno della seconda, si parla di **equi-join**.

> [!info] Join naturale vs theta-join
> Il join naturale è basato sui *nomi* degli attributi (unisce automaticamente gli omonimi). Equi-join e theta-join sono basati sui *valori* (il confronto è esplicito nella condizione). Il risultato dell'equi-join conserva *entrambe* le colonne di join (duplicando il valore), mentre il join naturale ne mantiene *una sola*.

> [!example] Theta-join (equi-join) — Impiegati e Progetti
>
> **Impiegati**
>
> | Impiegato | Progetto |
> |-----------|----------|
> | Rossi | A |
> | Neri | A |
> | Neri | B |
>
> **Progetti**
>
> | Codice | Nome |
> |--------|------|
> | A | Venere |
> | B | Marte |
>
> $\text{Impiegati} \bowtie_{\text{Progetto}=\text{Codice}} \text{Progetti}$
>
> | Impiegato | Progetto | Codice | Nome |
> |-----------|----------|--------|------|
> | Rossi | A | A | Venere |
> | Neri | A | A | Venere |
> | Neri | B | B | Marte |

#### Equivalenza tra equi-join e join naturale tramite ridenominazione

Le tre espressioni seguenti sono equivalenti:

$$\pi_{\text{Impiegato, Reparto, Capo}}(\text{Impiegati} \bowtie_{\text{Reparto}=\text{Codice}} \text{Reparti})$$
$$= \pi_{\text{Impiegato, Reparto, Capo}}(\sigma_{\text{Reparto}=\text{Codice}}(\text{Impiegati} \times \text{Reparti}))$$
$$= \text{Impiegati} \bowtie \rho_{\text{Reparto} \leftarrow \text{Codice}}(\text{Reparti})$$

### Join esterni (Outer Join)

Il join naturale tralascia le tuple dangling. L'**outer join** le preserva, estendendole con valori `NULL` dove mancano le controparti.

> [!quote] Definizione — Left outer join
> Il **left outer join** $r_1 \mathbin{\overset{\leftarrow}{\bowtie}} r_2$ restituisce tutte le tuple di $r_1$, estese con i valori di $r_2$ dove esiste corrispondenza, e con `NULL` sugli attributi di $r_2$ per le tuple di $r_1$ senza corrispondenza.

> [!quote] Definizione — Right outer join
> Il **right outer join** $r_1 \mathbin{\overset{\rightarrow}{\bowtie}} r_2$ restituisce tutte le tuple di $r_2$, estese analogamente.

> [!quote] Definizione — Full outer join
> Il **full outer join** $r_1 \mathbin{\overset{\leftrightarrow}{\bowtie}} r_2$ restituisce tutte le tuple di entrambi gli operandi, estese con `NULL` dove mancano le controparti.

> [!example] Left, Right e Full outer join — Impiegati e Reparti
>
> **Impiegati**
>
> | Impiegato | Reparto |
> |-----------|---------|
> | Rossi | vendite |
> | Neri | produzione |
> | Bianchi | produzione |
>
> **Reparti**
>
> | Reparto | Capo |
> |---------|------|
> | produzione | Mori |
> | acquisti | Bruni |
>
> **Left outer join** (tutte le tuple di Impiegati):
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|
> | Rossi | vendite | NULL |
> | Neri | produzione | Mori |
> | Bianchi | produzione | Mori |
>
> **Right outer join** (tutte le tuple di Reparti):
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|
> | Neri | produzione | Mori |
> | Bianchi | produzione | Mori |
> | NULL | acquisti | Bruni |
>
> **Full outer join** (tutte le tuple di entrambi):
>
> | Impiegato | Reparto | Capo |
> |-----------|---------|------|
> | Neri | produzione | Mori |
> | Bianchi | produzione | Mori |
> | Rossi | vendite | NULL |
> | NULL | acquisti | Bruni |

## Interrogazioni (Query)

> [!quote] Definizione — Interrogazione
> Un'**interrogazione** è un'espressione $E(\mathcal{R})$ che, applicata a istanze di una base di dati $\mathcal{R}$, produce una relazione su un dato insieme di attributi $X$. Le interrogazioni sono espressioni i cui atomi sono relazioni in $\mathcal{R}$ o costanti.

Le interrogazioni sono in pratica **espressioni di relazioni che producono relazioni**.

### Schema di esempio per le interrogazioni

Le query seguenti usano queste due relazioni:

**Impiegati**

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

**Supervisione**

| Capo | Impiegato |
|------|-----------|
| 210 | 101 |
| 210 | 103 |
| 210 | 104 |
| 301 | 210 |
| 301 | 231 |
| 375 | 252 |

> [!example] Query 1 — Impiegati con stipendio > 40
>
> *"Trovare tutti gli impiegati che guadagnano più di 40."*
>
> $$\sigma_{\text{Stipendio}>40}(\text{Impiegati})$$
>
> | Matricola | Cognome | Età | Stipendio |
> |-----------|---------|-----|-----------|
> | 104 | Neri | 38 | 61 |
> | 210 | Celli | 49 | 60 |
> | 231 | Bisi | 50 | 60 |
> | 252 | Bini | 44 | 70 |
> | 301 | S. Rossi | 34 | 70 |
> | 375 | M. Rossi | 50 | 65 |

> [!example] Query 2 — Matricola, cognome ed età degli impiegati con stipendio > 40
>
> $$\pi_{\text{Matricola, Cognome, Età}}(\sigma_{\text{Stipendio}>40}(\text{Impiegati}))$$
>
> | Matricola | Cognome | Età |
> |-----------|---------|-----|
> | 104 | Neri | 38 |
> | 210 | Celli | 49 |
> | 231 | Bisi | 50 |
> | 252 | Bini | 44 |
> | 301 | S. Rossi | 34 |
> | 375 | M. Rossi | 50 |

> [!example] Query 3 — Matricole dei capi di impiegati con stipendio > 40
>
> *"Trovare le matricole dei capi degli impiegati che guadagnano più di 40."*
>
> $$\pi_{\text{Capo}}\!\left(\text{Supervisione} \bowtie_{\text{Impiegato}=\text{Matricola}} (\sigma_{\text{Stipendio}>40}(\text{Impiegati}))\right)$$

> [!example] Query 4 — Nome e stipendio dei capi degli impiegati con stipendio > 40
>
> Si denomina $A$ il risultato intermedio:
>
> $$A = \text{Supervisione} \bowtie_{\text{Impiegato}=\text{Matricola}} (\sigma_{\text{Stipendio}>40}(\text{Impiegati}))$$
>
> $$\pi_{\text{Cognome, Stipendio}}(\text{Impiegati} \bowtie_{\text{Capo}=\text{Matricola}} A)$$

> [!example] Query 5 — Impiegati che guadagnano più del proprio capo
>
> *"Trovare gli impiegati che guadagnano più del proprio capo, mostrando matricola, cognome e stipendio dell'impiegato e del capo."*
>
> Si ridenomina una copia di Impiegati per rappresentare i capi:
>
> $$\rho_{\text{MatrC, NomeC, StipC, EtàC} \leftarrow \text{Matr, Nome, Stip, Età}}(\text{Impiegati}) = C$$
>
> Poi:
>
> $$\pi_{\text{Nome, Stip, MatrC, NomeC, StipC}}\!\left(\sigma_{\text{Stipendio}>\text{StipC}}\!\left(C \bowtie_{\text{MatrC}=\text{Capo}} (\text{Supervisione} \bowtie_{\text{Impiegato}=\text{Matricola}} \text{Impiegati})\right)\right)$$

> [!example] Query 6 — Matricole dei capi i cui impiegati guadagnano TUTTI più di 40
>
> *Logica: tutti i capi meno quelli che hanno almeno un impiegato con stipendio $\leq 40$.*
>
> $$\pi_{\text{Capo}}(\text{Supervisione}) - \pi_{\text{Capo}}\!\left(\text{Supervisione} \bowtie_{\text{Impiegato}=\text{Matricola}} (\sigma_{\text{Stipendio}\leq40}(\text{Impiegati}))\right)$$

## Equivalenza di espressioni

Due espressioni sono **equivalenti** se producono lo stesso risultato su ogni istanza della base di dati. L'equivalenza è importante perché consente di scegliere, a parità di risultato, l'operazione meno costosa (ottimizzazione delle query).

Le principali equivalenze utili sono:

**Atomizzazione delle selezioni:**
$$\sigma_{F_1 \land F_2}(E) \equiv \sigma_{F_1}(\sigma_{F_2}(E))$$

**Idempotenza delle proiezioni:**
$$\pi_X(E) \equiv \pi_X(\pi_{XY}(E))$$

**Anticipazione della selezione rispetto al join** (push-down della selezione):
$$\sigma_F(E_1 \bowtie E_2) \equiv \sigma_F(E_1) \bowtie \sigma_F(E_2)$$

**Anticipazione della proiezione rispetto al join:**
$$\pi_{X_1 Y_2}(E_1 \bowtie E_2) \equiv \pi_{X_1}(E_1) \bowtie \pi_{Y_2}(E_2)$$
(se gli attributi in $X - X_1$ e $Y - Y_2$ non sono coinvolti nel join).

**Inglobamento di una selezione nel prodotto cartesiano** (formazione di un join):
$$\sigma_F(E_1 \times E_2) \equiv E_1 \bowtie_F E_2$$

**Distributività della selezione rispetto all'unione:**
$$\sigma_F(E_1 \cup E_2) \equiv \sigma_F(E_1) \cup \sigma_F(E_2)$$

**Distributività della selezione rispetto alla differenza:**
$$\sigma_F(E_1 - E_2) \equiv \sigma_F(E_1) - \sigma_F(E_2)$$

**Distributività della proiezione rispetto all'unione:**
$$\pi_X(E_1 \cup E_2) \equiv \pi_X(E_1) \cup \pi_X(E_2)$$

> [!warning] La proiezione NON è distributiva rispetto alla differenza
> $\pi_X(E_1 - E_2) \not\equiv \pi_X(E_1) - \pi_X(E_2)$ in generale. Tutti gli operatori binari eccetto la differenza godono delle proprietà associativa e commutativa.

**Corrispondenze tra selezioni complesse e operatori insiemistici:**
$$\sigma_{F_1 \lor F_2}(R) \equiv \sigma_{F_1}(R) \cup \sigma_{F_2}(R)$$
$$\sigma_{F_1 \land F_2}(R) \equiv \sigma_{F_1}(R) \cap \sigma_{F_2}(R)$$
$$\sigma_{F_1 \land \lnot F_2}(R) \equiv \sigma_{F_1}(R) - \sigma_{F_2}(R)$$

## Viste (Relazioni derivate)

In una base di dati si distinguono:
- **Relazioni di base**: contenuto autonomo, memorizzato fisicamente.
- **Relazioni derivate** (viste): il cui contenuto è funzione del contenuto di altre relazioni, definito per mezzo di interrogazioni.

### Tipi di viste

**Relazioni virtuali (viste):** relazioni definite mediante espressioni del linguaggio di interrogazione, non memorizzate ma utilizzabili come se lo fossero. Devono essere ricalcolate ogni volta che vengono interrogate.

**Viste materializzate:** relazioni virtuali effettivamente memorizzate nella base di dati. Immediatamente disponibili ma critiche per il mantenimento dell'allineamento con le relazioni da cui derivano.

> [!example] Vista Supervisione come relazione derivata
>
> La vista `Supervisione` può essere definita come:
>
> $$\text{Supervisione} = \pi_{\text{Impiegato, Capo}}(\text{Afferenza} \bowtie \text{Direzione})$$
>
> dove **Afferenza** (Impiegato, Reparto) e **Direzione** (Reparto, Capo) sono relazioni di base. Le interrogazioni sulla vista vengono eseguite sostituendo alla vista la sua definizione:
>
> $$\sigma_{\text{Capo}='Leoni'}(\text{Supervisione})$$
>
> viene eseguita come:
>
> $$\sigma_{\text{Capo}='Leoni'}\!\left(\pi_{\text{Impiegato, Capo}}(\text{Afferenza} \bowtie \text{Direzione})\right)$$

### Vantaggi delle viste

- Permettono di mostrare a ciascun utente solo le componenti della base di dati che lo interessano.
- **Sicurezza**: è possibile definire diritti di accesso relativi a una vista.
- Espressioni complesse possono essere definite come viste e riutilizzate.
- In caso di ristrutturazione della base di dati, le vecchie relazioni possono essere ricavate mediante viste, mantenendo la compatibilità con le applicazioni esistenti.

### Aggiornamenti sulle viste

"Aggiornare una vista" significa modificare le relazioni di base in modo che la vista, ricalcolata, rispecchi l'aggiornamento. L'aggiornamento sulle relazioni di base corrispondente a quello specificato sulla vista deve essere **univoco**, ma in generale non lo è: per questo ben pochi aggiornamenti sono ammissibili sulle viste.
