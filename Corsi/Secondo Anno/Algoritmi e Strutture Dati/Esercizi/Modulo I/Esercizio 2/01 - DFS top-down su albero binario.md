---
tags:
  - algoritmi
  - strutture-dati
---
# DFS top-down su albero binario
Casistica **più frequente** dell'Esercizio 2 (progettazione): una DFS in cui l'informazione **scende** dalla radice nei **parametri** della chiamata (il contesto degli antenati / del cammino) e il conteggio **sale** nel **valore di ritorno** — schema *top-down*. Ripasso: [[08 - Grafi e Visite#Visita in profondità — DFS|DFS]], [[05 - Strutture Dati Elementari e Dizionari#Visite di Alberi|visite di alberi]].
## A · Conteggio per soglia sugli antenati
> [!question] Traccia — 14/09/2022
> Sia $T$ un albero binario in cui ogni nodo $v$ ha un colore $v.\text{col} \in \{B, G\}$ (Blu o Giallo). Dati due interi $b, g \geq 0$, progettare un algoritmo che restituisca il numero di nodi $v$ di $T$ con **almeno $b$ antenati blu oppure almeno $g$ antenati gialli**. $T$ è rappresentato con record e puntatori (campo $v.\text{col}$, puntatori $v.\text{sx}$ e $v.\text{dx}$). Complessità richiesta $O(n)$.

Un **antenato** di $v$ è un nodo sul cammino dalla radice fino a $v$, escluso $v$ stesso (la radice non ha antenati). Per ogni nodo serve sapere quanti dei suoi antenati sono blu e quanti gialli, e contarlo se scatta **almeno una** delle due soglie (è un *oppure*). La struttura collegata dà accesso solo ai figli, non al padre: l'informazione sugli antenati va costruita durante la discesa e passata verso il basso.
### Idea risolutiva
Ogni chiamata sul nodo $v$ riceve nei parametri quanti antenati blu ($ab$) e gialli ($ag$) ha $v$ — cioè i colori già visti sul cammino dalla radice al **padre** di $v$. Su $v$ si procede in **quest'ordine**:

1. **Test**: $v$ va contato se $ab \geq b$ oppure $ag \geq g$. Si controlla *prima* di aggiornare, così il colore di $v$ non entra fra i propri antenati.

2. **Aggiornamento** per i figli: $ab' = ab + [\,v.\text{col}=B\,]$ e $ag' = ag + [\,v.\text{col}=G\,]$ (per i figli, $v$ **è** un antenato).

3. **Ricorsione** sui due figli con i contatori aggiornati, sommando i loro contributi.

Il caso base $v = \text{null}$ (sottoalbero vuoto) restituisce $0$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{contaAntenati($v$, $ab$, $ag$, $b$, $g$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\State $r \gets 0$
\If{$ab \geq b$ o $ag \geq g$}
  \State $r \gets 1$ \Comment{test sugli antenati di $v$, prima dell'aggiornamento}
\EndIf
\State $ab' \gets ab + [\,v.\text{col} = B\,]$ \Comment{per i figli, $v$ è un antenato}
\State $ag' \gets ag + [\,v.\text{col} = G\,]$
\State \Return $r + {}$\Call{contaAntenati}{$v.\text{sx}, ab', ag', b, g$} $+$ \Call{contaAntenati}{$v.\text{dx}, ab', ag', b, g$}
\end{algorithmic}
\end{algorithm}
```

Chiamata iniziale `contaAntenati(T.radice, 0, 0, b, g)`: la radice parte senza antenati. La scrittura $[\,v.\text{col}=B\,]$ è la **parentesi di Iverson** ($1$ se vero, $0$ altrimenti). I contatori aggiornati $ab', ag'$ vanno **ai figli**, mai a $v$ stesso; il ritorno somma il contributo locale $r \in \{0,1\}$ e i due sottoalberi.
### Complessità
Ogni nodo riceve **esattamente una** chiamata e vi svolge lavoro $O(1)$ oltre alle ricorsioni. Detto $k$ il numero di nodi del sottoalbero sinistro:
$$T(n) = T(k) + T(n-k-1) + O(1) = \Theta(n),$$
la somma dei lavori $O(1)$ sugli $n$ nodi (più $\le n+1$ chiamate su `null`, ognuna $O(1)$). Complessità **$O(n)$**; spazio $O(h)$ per la pila di ricorsione ($h$ = altezza).
### Correttezza
> [!quote] Invariante — i parametri sono gli antenati di $v$
> A ogni invocazione di `contaAntenati` su un nodo $v \neq \text{null}$, i parametri valgono $ab = $ numero di antenati blu di $v$ e $ag = $ numero di antenati gialli di $v$ (nodi sul cammino dalla radice al padre di $v$, con $v$ escluso).

**Dimostrazione** (induzione sulla profondità di $v$). *Base*: $v$ è la radice, invocata con $ab = ag = 0$; la radice non ha antenati. *Passo*: sia $u$ un figlio di $v$, che soddisfa l'invariante. Gli antenati di $u$ sono quelli di $v$ più $v$ stesso; la chiamata su $u$ riceve $ab' = ab + [\,v.\text{col}=B\,]$ = (antenati blu di $v$) $+$ ($1$ se $v$ blu) = antenati blu di $u$; idem $ag'$. $\blacksquare$

Per l'invariante il test «$ab \geq b$ o $ag \geq g$» su $v$ coincide con la condizione della traccia, quindi $r=1$ **se e solo se** $v$ va contato; sommando i contributi su tutti i nodi (ciascuno visitato una volta) il ritorno è il numero di nodi che soddisfano la condizione. $\blacksquare$

> [!warning] Prima il test, poi l'aggiornamento
> Aggiornare $ab, ag$ **prima** del test farebbe entrare il colore di $v$ fra i suoi stessi antenati, contando a torto alcuni nodi (sovrastima). L'ordine è sempre *test → aggiorna → ricorri sui figli*.
### Varianti — stesso schema, stato diverso
Cambiano solo *quale stato* scende e *quale test* fa scattare il conteggio; struttura, complessità $O(n)$ e forma dell'invariante restano identici.

> [!question] Traccia — 30/01/2024
> Albero binario con un valore positivo $\text{val}(v)$ per nodo. Contare i nodi la cui **somma dei valori degli antenati** è almeno $\Delta$. Complessità $O(n)$.

Stato che scende: un accumulatore $s$ = somma dei valori sul cammino dalla radice al **padre** di $v$. Test su $v$: $s \geq \Delta$. Aggiornamento per i figli: $s' = s + \text{val}(v)$. Chiamata iniziale $s=0$.

> [!question] Traccia — 23/09/2025
> Albero binario con nodi bianchi (B) o neri (N). Un nodo è **grigio** se ha tanti antenati neri quanti antenati bianchi. Contare i nodi grigi. Complessità $O(n)$.

Stato che scende: un **singolo** intero $d = (\#\text{antenati neri}) - (\#\text{antenati bianchi})$. Test su $v$: $d = 0$. Aggiornamento: $d' = d+1$ se $v$ è nero, $d' = d-1$ se $v$ è bianco. Tenere la sola *differenza* evita due contatori e riduce il test a un confronto con $0$. Chiamata iniziale $d=0$: la radice, senza antenati, è grigia.
## B · Foglie e nodi con vincolo di profondità
Qui la proprietà testata (profondità, colore, essere foglia) è del **nodo stesso**, non dei suoi antenati: quando si arriva su $v$ la profondità è già quella corretta, quindi si **testa direttamente** senza la cautela "test prima / aggiorna dopo". L'unico accorgimento è passare $prof+1$ ai figli.

> [!question] Traccia — 30/01/2023
> Albero binario con nodi blu (B) o gialli (G) e un intero $h$. Contare le **foglie gialle** con profondità almeno $h$ (radice a profondità $0$). Complessità $O(n)$.

Lo stato che scende è la sola **profondità** $prof$ (radice $0$, $+1$ a ogni discesa). Il conteggio scatta **solo sulle foglie** ($v.\text{sx}=v.\text{dx}=\text{null}$) gialle con $prof \geq h$; i nodi interni non contano mai ma propagano $prof+1$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{contaFoglie($v$, $prof$, $h$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\If{$v.\text{sx} = $ null e $v.\text{dx} = $ null}
  \If{$v.\text{col} = G$ e $prof \geq h$}
    \State \Return $1$ \Comment{foglia gialla abbastanza profonda}
  \EndIf
  \State \Return $0$
\EndIf
\State \Return \Call{contaFoglie}{$v.\text{sx}, prof+1, h$} $+$ \Call{contaFoglie}{$v.\text{dx}, prof+1, h$}
\end{algorithmic}
\end{algorithm}
```

Chiamata iniziale `contaFoglie(T.radice, 0, h)`.
### Complessità e correttezza
Una chiamata per nodo, lavoro $O(1)$: $T(n)=\Theta(n)$, quindi **$O(n)$**. Invariante: a ogni chiamata su $v \neq \text{null}$, $prof$ è la profondità di $v$ (numero di archi dalla radice a $v$). *Base*: radice con $prof=0$. *Passo*: un figlio di $v$ ha profondità $prof+1$, che è il valore passato. Per l'invariante il test «foglia, gialla, $prof \geq h$» identifica esattamente le foglie richieste, contate una volta ciascuna. $\blacksquare$

> [!question] Traccia — 18/07/2025
> Variante con colori bianco (B) / nero (N): contare le **foglie nere** di profondità almeno $h$ (profondità = numero di archi dal nodo alla radice). Complessità $O(n)$.

Identica alla precedente cambiando il colore testato ($N$ invece di $G$): stesso `contaFoglie`, stessa analisi.

> [!question] Traccia — 12/09/2023
> Albero binario e due interi $h_1 \leq h_2$. Contare i nodi **non foglia** con profondità $h$ tale che $h_1 \leq h \leq h_2$. Complessità $O(n)$.

Stesso stato (profondità) e stessa struttura: cambia solo il test — il nodo conta se è **interno** (almeno un figlio non null) e $h_1 \leq prof \leq h_2$; la ricorsione sui figli con $prof+1$ resta.
## C · Proprietà del cammino radice→v (stato monotòno)
Qui il pattern riguarda il cammino **incluso $v$**, perciò si aggiorna lo stato con $v$ *prima* di decidere se contarlo. Spesso lo stato include un flag **monotòno** (una volta falso non torna vero): l'intero sottoalbero sotto la rottura è scartato "gratis".

> [!question] Traccia — 04/07/2023
> Albero binario con nodi blu (B) o gialli (G). Un nodo $v$ ha **antenati ben colorati** se il cammino dalla radice a $v$ è una sequenza (eventualmente vuota) di nodi blu seguita da una sequenza (eventualmente vuota) di nodi gialli. Contare i nodi con antenati ben colorati. Complessità $O(n)$.

Stato che scende: due flag — $seenG$ ("sul cammino incluso $v$ è già comparso un giallo") e $valid$ ("il cammino fin qui è della forma blu\*giallo\*"). Al nodo $v$: se $v$ è **blu dopo** un giallo il pattern si rompe ($valid \gets$ false, e resta falso per tutta la discesa per via dell'`and`); un giallo attiva $seenG$. Il nodo conta se $valid$ vale **dopo** aver incluso $v$.
### Pseudocodice
```pseudo
\begin{algorithm}
\caption{contaBenColorati($v$, $seenG$, $valid$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\If{$v.\text{col} = B$ e $seenG$}
  \State $valid \gets$ false \Comment{blu dopo un giallo: pattern rotto}
\EndIf
\If{$v.\text{col} = G$}
  \State $seenG \gets$ true
\EndIf
\State $r \gets 0$
\If{$valid$}
  \State $r \gets 1$
\EndIf
\State \Return $r + {}$\Call{contaBenColorati}{$v.\text{sx}, seenG, valid$} $+$ \Call{contaBenColorati}{$v.\text{dx}, seenG, valid$}
\end{algorithmic}
\end{algorithm}
```

Chiamata iniziale `contaBenColorati(T.radice, false, true)` (cammino vuoto: nessun giallo visto, pattern banalmente valido).
### Complessità e correttezza
Una chiamata per nodo, lavoro $O(1)$ → **$O(n)$**. Invariante: a ogni chiamata su $v$, $seenG$ e $valid$ descrivono correttamente il cammino dalla radice fino al **padre** di $v$; aggiornandoli col colore di $v$ si ottiene la descrizione del cammino incluso $v$, così $r=1$ **se e solo se** il cammino radice→$v$ è blu\*giallo\*. La **monotonia** di $valid$ (solo `and`) garantisce che, rotta la forma, nessun discendente venga contato — coerente col fatto che il loro cammino contiene la stessa violazione. $\blacksquare$

> [!question] Traccia — 16/02/2026
> Albero binario con un valore $\alpha(v)$ per nodo. Un nodo è **crescente** se la sequenza dei valori sul cammino dalla radice a $v$ è strettamente crescente, **pari** se quel cammino ha un numero pari di nodi. Contare le **foglie** crescenti e pari. Complessità $O(n)$.

Stato che scende: l'ultimo valore visto $prec$ (radice: $-\infty$), un flag monotòno $inc$ (cammino ancora strettamente crescente) e la lunghezza $len$ del cammino. Al nodo $v$: $inc' = inc \wedge (\alpha(v) > prec)$, $len' = len+1$. Il conteggio scatta **solo sulle foglie** con $inc'$ vero e $len'$ pari; si ricorre con $prec=\alpha(v)$, $inc'$, $len'$. Chiamata iniziale $prec=-\infty$, $inc=$ true, $len=0$.
