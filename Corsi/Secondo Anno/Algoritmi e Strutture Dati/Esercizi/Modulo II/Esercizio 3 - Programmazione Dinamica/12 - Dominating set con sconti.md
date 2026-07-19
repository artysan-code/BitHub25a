---
tags:
  - algoritmi
  - dp
  - esercizi
---
# 12 — Dominating set con sconti
*(Esercizio 3 — compito del 30/06/2026 — 11 punti)*
> [!note] Traccia
> **Problema.** Sia $G$ un grafo a cammino di $n$ nodi dove ad ogni nodo $v_i$ è associato un costo non negativo $c_i$. Un *dominating set* è un sottoinsieme di nodi $S$ tale che ogni nodo che non appartiene ad $S$ è dominato, ovvero è adiacente ad almeno un nodo di $S$. Il costo di $S$ è definito come $\sum_{v_i \in S} c_i$, e il problema del minimum dominating set chiede di trovare un dominating set di costo minimo.
> **Sconto.** In questo esercizio vi chiedo di considerare una variante del problema in cui per alcuni nodi di $S$ ricevete uno sconto del 10%. Più precisamente, la regola è questa: se un nodo $v_i \in S$ fa parte in $S$ di almeno un blocco contiguo di nodi lungo almeno 3, il costo di $v_i$ è $0.9\, c_i$.
> **Richiesta.** Progettate un algoritmo di programmazione dinamica che calcoli il dominating set il cui costo scontato è minimo.
## Pattern
**DP su sequenza con stato composito** — `OPT(i,s)`, dove $i$ scorre sul cammino e $s$ è uno stato a **dominio fisso** di cinque valori, non dipendente da $n$ né dai costi. Estende il [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]] con una seconda variabile di stato per un vincolo che riguarda anche i vicini, come già in [[04 - Programmazione Dinamica I (Weighted Independent Set)#Esercizio: WIS su alberi (problema della festa aziendale)|WIS su alberi]]. Il dominio fisso di $s$ è ciò che tiene la DP **polinomiale**, a differenza del Knapsack di [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)]], dove il secondo indice dipende dal valore dell'input.
## Soluzione
### Sottoproblema
$$\text{OPT}(i,s) = \text{costo scontato minimo di un dominating set per il sottocammino } v_1,\ldots,v_i$$
Dominando correttamente ogni nodo $v_1,\ldots,v_{i-1}$, ed eventualmente lasciando $v_i$ "in sospeso" se lo stato $s$ lo prevede. $s$ è una delle cinque configurazioni seguenti, riguardanti la posizione $i$:

| Stato $s$ | Significato |
|---|---|
| $\text{IN}_1$ | $v_i \in S$, inizio di un nuovo blocco ($v_{i-1} \notin S$, o $i=1$): blocco di lunghezza $1$ finora |
| $\text{IN}_2$ | $v_i \in S$ e anche $v_{i-1} \in S$, ma $v_{i-2} \notin S$: blocco di lunghezza $2$ finora, sconto non ancora attivo |
| $\text{IN}_{\geq 3}$ | $v_i \in S$ e il blocco contiguo di $S$ che finisce in $v_i$ ha lunghezza $\geq 3$: sconto attivo su $v_i$ |
| $\text{OUT}_D$ | $v_i \notin S$, ma già dominato perché $v_{i-1} \in S$ |
| $\text{OUT}_U$ | $v_i \notin S$ e $v_{i-1} \notin S$: $v_i$ non è ancora dominato, resta in sospeso e dovrà esserlo da $v_{i+1} \in S$ |

I sottoproblemi sono $n \cdot 5 = \Theta(n)$: cinque per ogni posizione $i = 1,\ldots,n$. Il primo indice individua il prefisso considerato, il secondo lo stato esatto del bordo destro — sia rispetto alla domination (stati $\text{OUT}$) sia al conteggio del blocco (stati $\text{IN}$). Pur essendo $s$ un'etichetta discreta e non un numero come la capacità del Knapsack, il ruolo che gioca è identico: è la seconda variabile senza la quale la ricorrenza non si può scrivere.
### Casi base
$$\text{OPT}(1,\text{IN}_1) = c_1 \qquad \text{OPT}(1,\text{IN}_2) = +\infty \qquad \text{OPT}(1,\text{IN}_{\geq 3}) = +\infty$$
$$\text{OPT}(1,\text{OUT}_D) = +\infty \qquad \text{OPT}(1,\text{OUT}_U) = 0$$
Alla posizione $i=1$ non esiste un nodo precedente: nessun blocco di lunghezza $2$ o $3$ può esistere con un solo nodo disponibile, e non può esserci domination da sinistra. $\text{OPT}(1,\text{IN}_1) = c_1$ è diretto: $v_1 \in S$ costa $c_1$ a prezzo pieno, perché un blocco di un solo nodo non raggiunge mai lo sconto. $\text{OPT}(1,\text{OUT}_U) = 0$ dice che $v_1 \notin S$ non costa nulla per ora, ma resta un debito aperto che dovrà essere saldato da $v_2$.
Gli altri tre casi valgono $+\infty$ perché sono strutturalmente irraggiungibili, non semplicemente costosi: non esiste alcuna scelta su $v_1$ da sola che realizzi un blocco di lunghezza $2$ o $3$, o una domination da un nodo a sinistra che non esiste. Poiché la tabella **minimizza**, il valore neutro per un caso impossibile è $+\infty$ (perde sempre il confronto con un $\min$), mai $0$ — la stessa attenzione già segnalata nella nota [[11 - Scavo su griglia]] per le celle bloccate da una colonna dorica.
### Ricorrenza
Per $i \geq 2$ ci sono cinque transizioni possibili, una per ciascuno stato $s$.
**$v_i$ apre un nuovo blocco.** Perché $v_i$ apra un blocco nuovo, $v_{i-1}$ deve **non** essere in $S$: entrambi gli stati $\text{OUT}$ soddisfano questa condizione. Il termine $\text{OPT}(i-1,\text{OUT}_U)$ conta quanto $\text{OPT}(i-1,\text{OUT}_D)$: se $v_{i-1}$ era rimasto in sospeso, il fatto che ora $v_i \in S$ lo **risolve**, perché è proprio $v_i$ il nodo a destra che lo domina.
**$v_i$ estende un blocco di lunghezza $1$ a lunghezza $2$.** L'unico predecessore compatibile è $\text{IN}_1$: perché il blocco raggiunga lunghezza $2$ in $v_i$, deve esistere in $v_{i-1}$ esattamente un blocco di lunghezza $1$. Il costo di $v_i$ è ancora a prezzo pieno, perché lo sconto scatta solo a lunghezza $3$.
**Il blocco raggiunge o supera la lunghezza $3$.** Vale solo per $i \geq 3$; a $i=2$ si pone $+\infty$ per costruzione, perché con due soli nodi il blocco non può ancora raggiungere lunghezza $3$. Il primo ramo modella il momento in cui un blocco di lunghezza $2$ che finiva in $v_{i-1}$ (composto da $v_{i-2}, v_{i-1}$) si estende aggiungendo $v_i$: $v_i$ entra a prezzo scontato $0.9\,c_i$, mentre $v_{i-1}$ e $v_{i-2}$, pagati a prezzo pieno in $\text{OPT}(i-1,\text{IN}_2)$, vanno corretti retroattivamente sottraendo $0.1\,c_{i-1} + 0.1\,c_{i-2}$. Il secondo ramo estende un blocco già $\geq 3$: lo sconto era già attivo, e $v_i$ paga semplicemente $0.9\,c_i$ senza correzioni.
**$v_i$ è escluso da $S$ ma dominato da sinistra.** Basta che $v_{i-1} \in S$, in una qualunque delle tre configurazioni di blocco: non si aggiunge alcun costo, perché $v_i \notin S$.
**$v_i$ è escluso da $S$ e resta in sospeso.** Il predecessore deve essere $\text{OUT}_D$, non $\text{OUT}_U$: se anche $v_{i-1}$ fosse rimasto in sospeso, non verrebbe mai dominato, perché la domination guarda solo ai vicini immediati.
$$\text{OPT}(i,s) = \begin{cases}
c_i + \min\{\text{OPT}(i-1,\text{OUT}_D),\, \text{OPT}(i-1,\text{OUT}_U)\} & s = \text{IN}_1 \\[4pt]
c_i + \text{OPT}(i-1,\text{IN}_1) & s = \text{IN}_2 \\[4pt]
\min\{0.9c_i + \text{OPT}(i-1,\text{IN}_2) - 0.1c_{i-1} - 0.1c_{i-2},\;\; 0.9c_i + \text{OPT}(i-1,\text{IN}_{\geq 3})\} & s = \text{IN}_{\geq 3},\ i \geq 3 \\[4pt]
+\infty & s = \text{IN}_{\geq 3},\ i = 2 \\[4pt]
\min\{\text{OPT}(i-1,\text{IN}_1),\, \text{OPT}(i-1,\text{IN}_2),\, \text{OPT}(i-1,\text{IN}_{\geq 3})\} & s = \text{OUT}_D \\[4pt]
\text{OPT}(i-1,\text{OUT}_D) & s = \text{OUT}_U
\end{cases}$$
### Giustificazione
**Esaustività.** Ogni nodo $v_i$ è, per definizione, o in $S$ o non in $S$: non c'è una terza macro-alternativa. Se $v_i \in S$, la lunghezza del blocco contiguo che finisce in lui è $1$, $2$, o $\geq 3$ — tre sotto-alternative disgiunte ed esaustive. Se $v_i \notin S$, la sua domination è già garantita da sinistra oppure non ancora — due sotto-alternative disgiunte ed esaustive. In totale cinque casi, nessuna configurazione di $v_i$ ne resta fuori.
**Nessuna doppia transizione ammessa.** Per ogni stato $s$ in posizione $i$ esiste un solo insieme di predecessori compatibili in $i-1$: gli stati $\text{IN}$ derivano solo da $\text{OUT}$ o dallo stato $\text{IN}$ di lunghezza immediatamente inferiore, gli stati $\text{OUT}$ solo da stati $\text{IN}$ o da $\text{OUT}_D$. Escludendo la transizione $\text{OUT}_U \to \text{OUT}_U$, il vincolo di dominating set entra nella ricorrenza senza bisogno di un controllo esterno.
**Correzione retroattiva legittima.** Lo stato $\text{IN}_2$ in posizione $i-1$ fissa univocamente quali nodi compongono il blocco corrente — sono, per definizione dello stato, esattamente $v_{i-2}$ e $v_{i-1}$ — quindi la correzione $-0.1\,c_{i-1} - 0.1\,c_{i-2}$ si applica direttamente sui costi grezzi dell'input, senza dover portare in giro altra informazione né modificare celle già calcolate.
### Ordine di calcolo
Si procede con $i$ crescente da $1$ a $n$, e per ogni $i$ si calcolano i cinque valori $\text{OPT}(i,\cdot)$ in un ordine qualunque fra loro: nessuno dei cinque dipende da un altro valore alla stessa posizione $i$, ma solo da valori a $i-1$ o dai costi grezzi $c_{i-1}, c_{i-2}$ dell'input. È lo stesso principio dei quattro passi generali della DP — un ordinamento topologico dove ogni cella trova già pronte le celle da cui dipende — qui banale perché la dipendenza va sempre indietro di una posizione.
### Risposta
$$\text{Risposta} = \min\bigl\{\text{OPT}(n,\text{IN}_1),\; \text{OPT}(n,\text{IN}_2),\; \text{OPT}(n,\text{IN}_{\geq 3}),\; \text{OPT}(n,\text{OUT}_D)\bigr\}$$
Il minimo è fra i quattro stati che non lasciano nulla in sospeso all'ultima posizione. Lo stato $\text{OPT}(n,\text{OUT}_U)$ va **escluso**: significherebbe che $v_n$ è rimasto non dominato, e non esiste un $v_{n+1}$ che possa risolverlo. Includerlo per errore produrrebbe soluzioni non ammissibili che sembrano più economiche di quelle vere.
### Complessità
$n \cdot 5 = \Theta(n)$ celle, ciascuna calcolata in $O(1)$: ogni riga della ricorrenza è un confronto fra al più due espressioni, somma o sottrazione di un numero costante di termini. Tempo $\Theta(n)$, spazio $\Theta(n)$ per la tabella — riducibile a $O(1)$ tenendo solo la riga $i-1$ e i due costi grezzi $c_{i-1}, c_{i-2}$, se non serve ricostruire l'insieme $S$ (per la ricostruzione serve la tabella intera, come nel WIS).
È **polinomiale**, non pseudo-polinomiale: i costi $c_i$ compaiono nella tabella solo come valori sommati o confrontati, mai come dimensione della tabella stessa. A differenza del Knapsack, dove il secondo indice $w$ scorre fra $0$ e $W$ (un valore dell'input, da cui dipende il numero di sottoproblemi), qui il secondo indice $s$ ha sempre cinque valori possibili, indipendentemente dalla grandezza dei costi $c_i$: il numero di sottoproblemi è $5n$, lineare nella dimensione dell'input e non nel valore dei dati.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{DominatingSetSconto($c[1 \ldots n]$)}
\begin{algorithmic}
\State $\text{OPT}(1,\text{IN}_1) \gets c[1]$
\State $\text{OPT}(1,\text{IN}_2) \gets +\infty$
\State $\text{OPT}(1,\text{IN}_{\geq 3}) \gets +\infty$
\State $\text{OPT}(1,\text{OUT}_D) \gets +\infty$
\State $\text{OPT}(1,\text{OUT}_U) \gets 0$
\For{$i \gets 2$ \To $n$}
  \State $\text{OPT}(i,\text{IN}_1) \gets c[i] + \min\{\text{OPT}(i-1,\text{OUT}_D),\, \text{OPT}(i-1,\text{OUT}_U)\}$
  \State $\text{OPT}(i,\text{IN}_2) \gets c[i] + \text{OPT}(i-1,\text{IN}_1)$
  \If{$i \geq 3$}
    \State $\text{OPT}(i,\text{IN}_{\geq 3}) \gets \min\{0.9 \cdot c[i] + \text{OPT}(i-1,\text{IN}_2) - 0.1 \cdot c[i-1] - 0.1 \cdot c[i-2],\; 0.9 \cdot c[i] + \text{OPT}(i-1,\text{IN}_{\geq 3})\}$
  \Else
    \State $\text{OPT}(i,\text{IN}_{\geq 3}) \gets +\infty$
  \EndIf
  \State $\text{OPT}(i,\text{OUT}_D) \gets \min\{\text{OPT}(i-1,\text{IN}_1),\, \text{OPT}(i-1,\text{IN}_2),\, \text{OPT}(i-1,\text{IN}_{\geq 3})\}$
  \State $\text{OPT}(i,\text{OUT}_U) \gets \text{OPT}(i-1,\text{OUT}_D)$
\EndFor
\State \Return $\min\{\text{OPT}(n,\text{IN}_1),\, \text{OPT}(n,\text{IN}_2),\, \text{OPT}(n,\text{IN}_{\geq 3}),\, \text{OPT}(n,\text{OUT}_D)\}$
\end{algorithmic}
\end{algorithm}
```
La ricostruzione dell'insieme $S$, se richiesta, segue lo stesso schema di WIS e Knapsack: partendo dallo stato che realizza il minimo finale in $i=n$, si risale la tabella confrontando quale ramo della ricorrenza ha effettivamente prodotto ciascun valore, marcando $v_i \in S$ ogni volta che si transita per uno stato $\text{IN}_*$, fino a raggiungere $i=1$.
## Note di studio
### Riconoscere il pattern
Le parole chiave da cogliere sono due, lette insieme: **"grafo a cammino"** più **"ogni nodo che non appartiene ad $S$ è dominato"**. La prima dice che l'oggetto è una sequenza $v_1,\ldots,v_n$ — il territorio del [[04 - Programmazione Dinamica I (Weighted Independent Set)|WIS]]. La seconda introduce un vincolo che il WIS puro non ha: lì un nodo escluso da $S$ non doveva soddisfare alcuna condizione, qui deve essere **adiacente a un nodo incluso**. È un dominating set su cammino, non un independent set: una ricorrenza a stati multipli, analoga per ragione — un vincolo che riguarda anche i vicini — a quella di [[04 - Programmazione Dinamica I (Weighted Independent Set)#Esercizio: WIS su alberi (problema della festa aziendale)|WIS su alberi]].
C'è poi una terza informazione che rende specifico l'esercizio: **"blocco contiguo di nodi lungo almeno 3"**. Il costo di un nodo non dipende solo dalla decisione presa su di lui, ma da quanti nodi consecutivi prima di lui sono stati presi in $S$. È il pattern dello stato che ci si porta dietro, discusso in [[05 - Programmazione Dinamica II (Interval Scheduling e Knapsack)#Riconoscere il sottoproblema in un problema mai visto|Interval Scheduling e Knapsack]]: non basta sapere "ho processato i primi $i$ nodi", serve ricordare anche una configurazione locale con poche possibilità.
L'esercizio mescola due ragioni per cui un solo indice non basta: sapere se il nodo precedente era dominato, per il vincolo di dominating set, e sapere quanto è lungo il blocco corrente di $S$, per lo sconto. Le due esigenze si fondono in un'unica variabile di stato composita invece che in due indici separati: il numero di sottoproblemi resta comunque polinomiale.
### Perché lo stato ha cinque valori
La domanda diagnostica è sempre la stessa: per decidere su $v_i$, cosa serve sapere del passato che $\text{OPT}(i-1)$ da solo non dice?
**Tentativo ingenuo.** Definire $\text{OPT}(i)$ come costo scontato minimo per il sottocammino $v_1,\ldots,v_i$, con un'unica ricorrenza binaria "prendo $v_i$ o no", sul modello del WIS. Se **non** si prende $v_i$, bisogna sapere se è dominato — ma la domination può arrivare da sinistra ($v_{i-1}\in S$) o da destra ($v_{i+1}\in S$, non ancora deciso). Un solo valore numerico $\text{OPT}(i-1)$ non porta con sé se $v_{i-1}$ era in $S$: quel bit è perso non appena si collassa tutto in un numero.
Se invece si **prende** $v_i$, il suo costo dipende da quanto è lungo il blocco contiguo che finisce in lui. $\text{OPT}(i-1)$ non distingue se l'ottimo del prefisso precedente ha $v_{i-1}$ fuori da $S$, come inizio di un blocco di lunghezza $1$, o come terzo nodo di un blocco già scontato: sono situazioni diverse che portano a costi diversi per includere $v_i$.
**Cosa serve ricordare.** Due informazioni, ciascuna con poche configurazioni. Se $v_{i-1}\notin S$: se è stato dominato oppure resta in sospeso — due possibilità. Se $v_{i-1}\in S$: la lunghezza del blocco che finisce in lui, ma solo fino a un tetto — $1$, $2$, oppure $\geq 3$ — perché una volta raggiunta lunghezza $3$ ogni estensione successiva costa $0.9\,c_i$ allo stesso modo, e distinguere $3$ da $57$ non cambierebbe la ricorrenza. Sommando i due punti si ottengono cinque configurazioni: il dominio del secondo indice della DP, piccolo e fisso, non dipendente da $n$, come il colore in House Coloring.
### Esempio numerico
$n=3$, $c_1=c_2=c_3=1$. Un dominating set valido a costo minimo è $S=\{v_2\}$ (domina $v_1$ e $v_3$ per adiacenza), costo $1$, nessuno sconto perché il blocco ha lunghezza $1$.

| $i$ | $\text{IN}_1$ | $\text{IN}_2$ | $\text{IN}_{\geq 3}$ | $\text{OUT}_D$ | $\text{OUT}_U$ |
|---|---|---|---|---|---|
| 1 | $1$ | $\infty$ | $\infty$ | $\infty$ | $0$ |
| 2 | $1+\min(\infty,0)=1$ | $1+1=2$ | $\infty$ | $\min(1,\infty,\infty)=1$ | $\infty$ |
| 3 | $1+\min(1,\infty)=2$ | $1+1=2$ | $0.9+2-0.1-0.1=2.7$ | $\min(1,2,\infty)=1$ | $1$ |

Il risultato è $\min(2,2,2.7,1)=1$, ottenuto tramite $\text{OPT}(3,\text{OUT}_D)=1$: risalendo, questo valore proviene da $\text{OPT}(2,\text{IN}_1)=1$, cioè esattamente $S=\{v_2\}$ con $v_1$ e $v_3$ entrambi dominati da lui. Coincide con la soluzione trovata a mano, confermando la ricorrenza — inclusa la riga $\text{IN}_{\geq 3}$, che vale $2.7$ ed esiste come opzione ma qui non conviene.
### Errori da evitare
| Errore | Come si smaschera |
|---|---|
| Definire $\text{OPT}(i)$ con un solo indice | la ricorrenza non riesce a esprimere né il bit di domination né la lunghezza del blocco senza un secondo indice |
| Applicare lo sconto "in avanti" invece che retroattivamente sui due nodi che completano il blocco | il costo totale di un blocco di lunghezza esattamente $3$ non torna a essere $0.9(c_{i-2}+c_{i-1}+c_i)$ |
| Porre a $0$, anziché $+\infty$, i casi base impossibili di $i=1$ | uno $0$ vince sempre il confronto con un $\min$, introducendo soluzioni fittizie prive di senso |
| Includere $\text{OUT}_U$ nel minimo finale, o ammettere la transizione $\text{OUT}_U \to \text{OUT}_U$ | permette silenziosamente un nodo mai dominato, o due nodi consecutivi esclusi senza che nessuno dei due lo sia |
| Dichiarare la complessità pseudo-polinomiale per analogia col Knapsack | il secondo indice ha dominio fisso a cinque valori, non un range dipendente dal valore dei costi in input |
