---
tags:
  - basi-di-dati
  - lezione
slide: "04 -Modello Relazionale.pdf"
---
## Modello Relazionale
Il modello relazionale è stato proposto da **E. F. Codd nel 1970** con l'obiettivo di favorire **l'indipendenza dei dati**. È diventato disponibile nei **DBMS reali nel 1981** (non è semplice implementare l'indipendenza con efficienza e affidabilità). Si basa sul concetto matematico di **relazione** (con una variante) e le relazioni hanno naturale rappresentazione per mezzo di **tabelle**.
## Relazione matematica
Dati $D_{1},\ \dots,D_{n}$, detti *domini* (insiemi anche non distinti), definiamo il **prodotto cartesiano** $D_{1}\times \dots \times D_{n}$ come:

> [!quote] Definizione — Prodotto cartesiano
> L'insieme di tutte le **n-uple $(d_{1},\ \dots,d_{n})$** tali che $d_{1}\in D_{1},\ \dots, d_{n}\in D_{n}$

Una **relazione matematica** su $D_{1},\ \dots, D_{n}$ è un sottoinsieme di $D_{1}\times \dots \times D_{n}$, dove $D_{1},\ \dots, D_{n}$ sono i **domini della relazione**.

> [!example] Prodotto cartesiano e relazione
> Dati $D_1 = \{A, B\}$ e $D_2 = \{X, Y, Z\}$, il prodotto cartesiano $D_1 \times D_2$ contiene 6 coppie: $(A,X), (A,Y), (A,Z), (B,X), (B,Y), (B,Z)$. Una possibile relazione $r \subseteq D_1 \times D_2$ è: $\{(A,X), (B,X), (B,Y)\}$.

### Proprietà
Una **relazione** è un **insieme**, quindi:
1. **Non c'è ordinamento** fra le n-uple.
2. Le n-uple sono **distinte**.
3. **Ciascuna n-upla è ordinata**: l'i-esimo valore proviene dall'i-esimo dominio.
### Struttura posizionale
La struttura che si forma è **posizionale**: i ruoli di domini uguali sono distinguibili solo attraverso la posizione.

> [!example] Partite — struttura posizionale
> `Partite ⊆ string × string × int × int`
>
> |       |       |     |     |
> | ----- | ----- | --- | --- |
> | Juve  | Lazio | 3   | 1   |
> | Lazio | Milan | 2   | 0   |
> | Juve  | Roma  | 0   | 2   |
> | Roma  | Milan | 0   | 2   |
>
> Ciascuno dei domini (string per le squadre, int per i gol) ha due **ruoli** diversi, distinguibili solo attraverso la posizione.

![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l31.png]]
### Struttura non posizionale
Se a ciascun dominio si associa un nome (**attributo**), che ne descrive il "ruolo", la struttura diventa **non posizionale**:

| **Casa** | **Fuori** | **RetiCasa** | **RetiFuori** |
|----------|-----------|--------------|---------------|
| Juve | Lazio | 3 | 1 |
| Lazio | Milan | 2 | 0 |
| Juve | Roma | 0 | 2 |
| Roma | Milan | 0 | 2 |

![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l32.png]]
### Relazione come collezione di funzioni
Dato un insieme $X=\{A_{1},\dots,A_{n}\}$ un insieme **non ordinato** di attributi, definiamo $\text{DOM}:X\to D$ la funzione che associa ad ogni attributo il suo dominio:
- Una **ennupla** o **tupla** è una funzione $t$ che associa per ogni attributo $A\in X$ un valore del **dominio** $\text{DOM}(A)$.
- $t[A]$ denota il valore della ennupla $t$ sull'attributo $A$.

> [!example] Notazione
> Se $t$ è la prima tupla della tabella Studenti (Mario Rossi, matricola 1, voto 24), allora `t[Cognome] -> 'Rossi'`.

> [!quote] Definizione — Relazione
> Una **relazione** è una **collezione di ennuple**.

![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l33.png]]
### Tabelle e Relazioni
Una tabella può rappresentare una **relazione** se:
- I valori di ogni **colonna** sono fra loro **omogenei**.
- Le **righe** sono **diverse** fra loro.
- Le **intestazioni** delle colonne sono diverse tra loro.
In una tabella che rappresenta una relazione:
- L'ordinamento tra le righe è **irrilevante**.
- L'ordinamento tra le colonne è **irrilevante**.

> [!warning] Cosa NON è ammesso
> Due righe uguali (le n-uple devono essere distinte) e dati non omogenei nella stessa colonna.

## Modelli basati sui valori
I riferimenti fra dati in relazioni diverse sono rappresentati per mezzo di **valori dei domini** che compaiono nelle ennuple (non tramite puntatori fisici).

![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l34.png]]

> [!example] Database universitario — riferimenti tramite valori
> Un database universitario con tre relazioni collegate tramite valori condivisi (Matricola, Codice corso):
>
> **studenti**
>
> | Matricola | Cognome | Nome  | Data di nascita |
> | --------- | ------- | ----- | --------------- |
> | 6554      | Rossi   | Mario | 05/12/1978      |
> | 8765      | Neri    | Paolo | 03/11/1976      |
> | 9283      | Verdi   | Luisa | 12/11/1979      |
> | 3456      | Rossi   | Maria | 01/02/1978      |
>
> **esami**
>
> | Studente | Voto | Corso |
> | -------- | ---- | ----- |
> | 3456     | 30   | 04    |
> | 3456     | 24   | 02    |
> | 9283     | 28   | 01    |
> | 6554     | 26   | 01    |
>
> **corsi**
>
> | Codice | Titolo  | Docente |
> | ------ | ------- | ------- |
> | 01     | Analisi | Mario   |
> | 02     | Chimica | Bruni   |
> | 04     | Chimica | Verdi   |
>
> Il valore `3456` nella colonna `Studente` di **esami** fa riferimento alla tupla con `Matricola = 3456` in **studenti**.

I vantaggi di un modello basato sui valori sono:
- **Indipendenza dalle strutture fisiche**: si potrebbe avere anche con puntatori di alto livello, che possono cambiare dinamicamente, ma i valori lo garantiscono naturalmente.
- **Si rappresenta solo ciò che è rilevante** dal punto di vista dell'applicazione.
- **L'utente finale vede gli stessi dati dei programmatori**.
- **I dati sono portabili** più facilmente da un sistema ad un altro.
- **I puntatori (i valori stessi) sono direzionali**.
## Modello relazionale: Definizioni
### Schema di relazione
Uno **schema di relazione** è un nome **R** con un insieme di attributi $A_1, \ldots, A_n$: $R(A_1,\ldots, A_n)$
### Schema di base di dati
Uno **schema di base di dati** è un insieme di schemi di relazione: $\mathcal{R} = \{R_1(X_1), \ldots, R_k(X_k)\}$

> [!example] Schema di relazione e di base di dati
> **Schema di relazione:**
> ```
> STUDENTI(Matricola, Cognome, Nome, Data di Nascita)
> ```
> **Schema di base di dati:**
> ```
> STUDENTI(Matricola, Cognome, Nome, Data di Nascita)
> ESAMI(Studente, Voto, Corso)
> CORSO(Codice, Titolo, Docente)
> ```

### Istanza di relazione e di base di dati

> [!quote] Definizione — Istanza di relazione
> **(Istanza di) relazione** su uno schema $R(X)$: insieme $r$ di ennuple su $X$.

> [!quote] Definizione — Istanza di base di dati
> **(Istanza di) base di dati** su uno schema $\mathcal{R} = \{R_1(X_1), \ldots, R_n(X_n)\}$: insieme di relazioni $r = \{r_1, \ldots, r_n\}$ (con $r_i$ relazione su $R_i$).

### Relazioni su singoli attributi
Una relazione può avere anche un **singolo attributo**. Ad esempio, la relazione `studenti_lavoratori` può contenere solo la `Matricola` degli studenti che lavorano:

| **Matricola** |
|--------------|
| 6554 |
| 3456 |

Questa è comunque una relazione valida su un unico dominio.
## Strutture nidificate
Il modello relazionale è **piatto** (flat): le ennuple contengono solo valori atomici. Tuttavia, molte strutture reali sono **nidificate** (gerarchiche), come una ricevuta fiscale che contiene al suo interno più righe di dettaglio.
La **rappresentazione relazionale** di queste strutture le "appiattisce" in due o più relazioni collegate tramite valori:

> [!example] Ricevute — struttura nidificata appiattita
> **Ricevute** (dati di intestazione)
>
> | Numero | Data | Totale |
> |--------|------|--------|
> | 1235 | 12/10/2000 | 39,20 |
> | 1240 | 13/10/2000 | 39,00 |
>
> **Dettaglio** (righe di ogni ricevuta)
>
> | Numero | Qtà | Descrizione | Importo |
> |--------|-----|-------------|---------|
> | 1235 | 3 | Coperti | 3,00 |
> | 1235 | 2 | Antipasti | 6,20 |
> | 1235 | 3 | Primi | 12,00 |
> | 1235 | 2 | Bistecche | 18,00 |
> | 1240 | 2 | Coperti | 2,00 |
> | … | … | … | … |

La scelta della rappresentazione dipende dai requisiti: se l'**ordine delle righe** di una ricevuta è rilevante (o se possono esistere linee ripetute nella stessa ricevuta), si aggiunge un attributo `Riga` che identifica la posizione all'interno della ricevuta. Sono quindi possibili **rappresentazioni diverse** a seconda di cosa interessa modellare.
## Informazione incompleta
Il modello relazionale impone ai dati una struttura rigida:
- Le informazioni sono rappresentate per mezzo di ennuple.
- Solo alcuni formati di ennuple sono ammessi: quelli che corrispondono agli schemi di relazione.
I dati disponibili possono **non corrispondere al formato previsto**: ad esempio, non tutti i politici hanno un secondo nome, ma lo schema lo prevede come attributo.
### Il valore nullo (NULL)
Non conviene usare valori "sentinella" del dominio (0, stringa nulla, "99", …) per rappresentare l'assenza di un valore, perché:
- Potrebbero non esistere valori "non utilizzati" nel dominio.
- I valori "non utilizzati" potrebbero diventare significativi in futuro.
- In fase di utilizzo bisognerebbe tener conto del significato speciale di questi valori in ogni programma.
La soluzione adottata dal modello relazionale è una tecnica rudimentale ma efficace: il **valore nullo** (`NULL`).

> [!quote] Definizione — Valore nullo
> Il **valore nullo** denota **l'assenza** di un valore del dominio. **Non è** esso stesso un valore del dominio.

Formalmente: $t[A]$, per ogni attributo $A$, è un valore del dominio $\text{dom}(A)$ **oppure** il valore nullo `NULL`.
Si possono (e debbono) imporre **restrizioni sulla presenza di valori nulli** (es. `NOT NULL` in SQL) per evitare situazioni di eccessiva incompletezza.
### Tipi di valore nullo
Il valore nullo può rappresentare situazioni concettualmente diverse. I DBMS **non distinguono** tra questi tipi, ma concettualmente esistono (almeno) tre casi:
- **Valore sconosciuto**: il valore esiste ma non è noto (es. data di nascita non registrata).
- **Valore inesistente**: il valore non esiste (es. secondo nome per chi non ce l'ha).
- **Valore senza informazione**: non si sa se il valore esiste o meno.

> [!warning] Troppi valori NULL
> Troppi valori `NULL` rendono difficile l'interrogazione e l'interpretazione dei dati. È buona pratica limitarli il più possibile tramite vincoli `NOT NULL` sugli attributi obbligatori.
