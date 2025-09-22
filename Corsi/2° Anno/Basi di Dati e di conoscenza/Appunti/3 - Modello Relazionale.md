Favorisce l'indipendenza dei dati tramite il concetto matematico della **relazione** (con qualche variante), queste ultime sono rappresentate tramite le tabelle.

Dati $D_{1},\ \dots,D_{n}$, detti *domini*, definiamo il **prodotto cartesiano** $D_{1}\times \dots \times D_{n}$ come l'insieme di **n-uple $(d_{1},\ \dots,d_{n})$** tali che $d_{1}\in D_{1},\ \dots, d_{n}\in D_{n}$.

Una **relazione matematica** su $D_{1},\ \dots, D_{n}$ è un sottoinsieme $D_{1}\times \dots \times D_{n}$, dove questi primi sono i **domini della relazione**. Possiamo definirla in una maniera più generica come le **n-uple** $(d_{1},\ \dots,d_{n})$ tali che $d_{1}\in D_{1},\ \dots, d_{n}\in D_{n}$.

Una **relazione** è un insieme quindi:
- Non c'è ordinamento fra le n-uple
- Le n-uple sono distinte
- Ciascuna n-upla è ordinata, cioè che l'i-esimo valore proviene dall'i-esimo dominio.

La struttura che si forma alla fine è **posizionale**:
![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l31.png]]

Associando ad ogni indice un **attributo** (un identificatore diciamo) allora la struttura diventa **non posizionale**:![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l32.png]]

Dato un insieme $X=\{A_{1},\dots,A_{n}\}$ un insieme non ordinato di attributi, definiamo $\text{dom}:X\to D$ la funzione che associa ad ogni attributo il suo dominio, quindi:
- Una **ennupla** o **tupla** è una funzione $t$ che associa per ogni attributo $A\in X$ un valore del **domino**.
- $t[A]$ denota il valore della ennupla t sull'attributo A.

![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l33.png]]

### Tabelle e Relazioni
Una tabella può rappresentare una **relazione** se:
- Ciascuna colonna ha un tipo di valore **omogeneo**.
- Ciascuna riga ha diversi valori.
- Ogni intestazione della colonna è diversa dalle altre.
- L'ordinamento tra righe e colonne è *irrilevante*.

## Modelli basati sui valori
I riferimenti fra dati in relazioni diverse sono rappresentati per mezzo di valori dei domini che compaiono nelle ennuple:![[Corsi/2° Anno/Basi di Dati e di conoscenza/Appunti/assets/l34.png]]

I vantaggi di un modello del genere sono:
- Dinamicità della struttura grazie ai *puntatori* (i valori stessi sono puntatori ad altre ennuple) e questi sono *direzionali*.
- Si rappresenta solo ciò che è rilevante.
- L'utente vede gli stessi dati dei programmatori.
- I dati sono facilmente portabili.
## Modello relazionale
Uno schema relazione, definito come **R** 