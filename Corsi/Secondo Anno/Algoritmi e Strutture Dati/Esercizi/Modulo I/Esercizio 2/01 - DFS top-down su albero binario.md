---
tags:
  - algoritmi
---
# DFS top-down su albero binario
Casistica **più frequente** dell'[[Casistiche d'Esame Modulo I|Esercizio 2 (Progettazione)]] — 8 tracce dal 2022 al 2026 — basata su [[08 - Grafi e Visite|visite di alberi binari]]; checklist [[Piano Esame ASD - Modulo I]]. In una DFS su albero l'informazione viaggia su **due canali**: ciò che **scende** dalla radice (il contesto degli antenati) viaggia nei **parametri** della chiamata; ciò che **sale** verso la radice (il conteggio) viaggia nel **valore di ritorno**. Lo schema si dice *top-down* perché è lo stato che scende a decidere la risposta.
## Conteggio con soglia sugli antenati
> [!question] Traccia — 14/09/2022
> Dato un albero binario i cui nodi sono colorati di bianco (W), blu (B) o giallo (G), e due interi $b, g \geq 0$, scrivere un algoritmo efficiente che conti il numero di nodi $v$ tali che $v$ abbia almeno $b$ antenati blu **oppure** almeno $g$ antenati gialli.

**Schema comune.** Tutte queste tracce si risolvono con un'unica DFS ricorsiva che porta verso il basso (radice → foglie) uno **stato cumulativo** sul cammino degli antenati. Ogni chiamata riceve dal padre lo stato calcolato fino a sé, lo **testa** sul nodo corrente *prima* di aggiornarlo (così il nodo non finisce tra i propri antenati), poi **aggiorna** lo stato col contributo di $v$ e **ricorre** sui due figli sommando i contributi. Caso base $v=\text{null}\to 0$. Complessità sempre $T(n)=T(k)+T(n-k-1)+O(1)=O(n)$, lavoro $O(1)$ per nodo. Cambia solo *quale stato* si trasporta e *quale condizione* fa scattare il conteggio.

**Idea.** Si visita l'albero con una DFS top-down (pre-order): ogni chiamata riceve dal padre i contatori $b\_cnt$ e $g\_cnt$, numero di antenati blu e gialli di $v$ **già incontrati** sul cammino dalla radice fino al padre di $v$ — il nodo $v$ stesso **non** è incluso. Il processing di $v$ avviene in tre fasi:
1. **Controllo**: si verifica $b\_cnt \geq b$ oppure $g\_cnt \geq g$ usando i contatori ricevuti; se la condizione vale, $v$ contribuisce $1$ al risultato.
2. **Aggiornamento**: si costruiscono i contatori da passare ai figli, aggiungendo il colore di $v$ stesso — $b' = b\_cnt + [\,v.\text{col} = B\,]$ e $g' = g\_cnt + [\,v.\text{col} = G\,]$.
3. **Ricorsione**: si ricorre su entrambi i sottoalberi con i contatori aggiornati e si somma il loro contributo.

> [!info] Le variabili in gioco
> - $b,\ g$ = le **soglie** date dalla traccia (*quanti antenati servono*); costanti per tutta la visita.
> - $b\_cnt,\ g\_cnt$ = stato che **scende**: antenati blu/gialli di $v$, cioè sul cammino radice→**padre** di $v$ ($v$ escluso).
> - $r$ (variabile `r` nel codice) = contributo locale di $v$: vale $1$ se $v$ è qualificato, $0$ altrimenti.
> - $b',\ g'$ = i contatori **aggiornati col colore di $v$**, da passare ai figli (per loro $v$ è un antenato). La scrittura $[\,v.\text{col}=B\,]$ vale $1$ se vero, $0$ altrimenti (parentesi di Iverson).

Il caso base è $v = \text{null}$, che restituisce $0$.
```pseudo
\begin{algorithm}
\caption{contaQualificati($v$, $b\_cnt$, $g\_cnt$, $b$, $g$) → intero}
\begin{algorithmic}
\If{$v = $ null}
  \State \Return $0$
\EndIf
\State $r \gets 0$
\If{$b\_cnt \geq b$ oppure $g\_cnt \geq g$}
  \State $r \gets 1$
\EndIf
\State $b' \gets b\_cnt + [\,v.\text{col} = B\,]$
\State $g' \gets g\_cnt + [\,v.\text{col} = G\,]$
\State \Return $r + {}$\Call{contaQualificati}{$v.\text{sx},\, b',\, g',\, b,\, g$} $+$ \Call{contaQualificati}{$v.\text{dx},\, b',\, g',\, b,\, g$}
\end{algorithmic}
\end{algorithm}
```
La chiamata iniziale è `contaQualificati(radice, 0, 0, b, g)`: la radice non ha antenati, quindi entrambi i contatori partono da $0$.

Albero d'esempio (soglie $b = 1$, $g = 1$):

```
        v1 (B)
       /    \
    v2 (G)  v3 (B)
```

> [!example] Esempio — i contatori scendono, il conteggio sale
> Si cercano i nodi con almeno $1$ antenato blu **oppure** almeno $1$ antenato giallo.
> - **v1** (B): riceve $(b\_cnt, g\_cnt) = (0,0)$ → $0 \geq 1$? no, $0 \geq 1$? no → $r = 0$. Ai figli passa $b' = 1,\ g' = 0$.
> - **v2** (G): riceve $(1,0)$ → $1 \geq 1$ → $r = 1$ (ha l'antenato blu $v_1$). Figli `null` → risale $1$.
> - **v3** (B): riceve $(1,0)$ → $1 \geq 1$ → $r = 1$. Figli `null` → risale $1$.
> - **v1** somma: $r + 1 + 1 = 0 + 2 = 2$.
>
> Risultato = **2** ($v_2$ e $v_3$; la radice $v_1$ non ha antenati, quindi non qualifica).

**Complessità:** $O(n)$ — ogni nodo è visitato una volta, lavoro $O(1)$.
**Trappola:** aggiornare i contatori ($b'$, $g'$) **prima** di verificare la condizione su $v$ comporta di contare $v$ tra i propri antenati, sovrastimando il numero di nodi qualificati. I contatori vanno prima controllati, poi aggiornati e infine passati ai **figli**, non al nodo corrente. Secondo errore tipico: dimenticare il `\Return $0$` nel caso base, oppure omettere la ricorsione su uno dei due rami.
### Varianti — stessa struttura, stato diverso
> [!question] Traccia — 30/01/2024
> Albero binario con un valore positivo $\text{val}(v)$ per nodo. Contare i nodi la cui **somma dei valori degli antenati** è almeno $\Delta$. Complessità $O(n)$.

Stato trasportato: un accumulatore $s$ = somma dei valori sul cammino dalla radice fino al **padre** di $v$. Test su $v$: $s \geq \Delta$. Aggiornamento per i figli: $s' = s + \text{val}(v)$. Chiamata iniziale con $s = 0$ (la radice non ha antenati).

> [!question] Traccia — 23/09/2025
> Albero binario con nodi bianchi (B) o neri (N). Un nodo è **grigio** se ha tanti antenati neri quanti antenati bianchi. Contare i nodi grigi. Complessità $O(n)$.

Stato trasportato: un **singolo** intero $d = (\#\text{antenati neri}) - (\#\text{antenati bianchi})$. Test su $v$: $d = 0$. Aggiornamento: $d' = d + 1$ se $v$ è nero, $d' = d - 1$ se $v$ è bianco. Tenere la sola *differenza* evita di trasportare due contatori separati e rende il test un confronto con $0$.
## Foglie con vincolo di profondità
> [!question] Traccia — 30/01/2023
> Albero binario con nodi blu (B) o gialli (G) e un intero $h$. Contare le **foglie gialle** che hanno profondità almeno $h$ (radice a profondità $0$). Complessità $O(n)$.

> [!question] Traccia — 18/07/2025
> Variante identica con colori bianco (B) / nero (N): contare le **foglie nere** di profondità almeno $h$.

**Idea.** Lo stato trasportato è la sola **profondità** del nodo (radice $= 0$, $+1$ a ogni discesa). Il conteggio scatta **solo sulle foglie** ($v.\text{sx} = v.\text{dx} = \text{null}$) che siano del colore richiesto e con profondità $\geq h$. I nodi interni non contano mai ma propagano la profondità ai figli.

> [!info] Differenza chiave rispetto al caso "antenati"
> Qui la proprietà testata (profondità + colore) è del **nodo stesso**, non dei suoi antenati: quando si arriva su $v$, $prof$ è già la sua profondità corretta, quindi si **testa direttamente** senza la cautela "test prima / aggiorna dopo". L'unica accortezza è passare $prof+1$ ai figli. Regola generale: *proprietà degli antenati → escludi il nodo; proprietà del nodo stesso → usalo così com'è.*

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
\State \Return \Call{contaFoglie}{$v.\text{sx},\, prof+1,\, h$} $+$ \Call{contaFoglie}{$v.\text{dx},\, prof+1,\, h$}
\end{algorithmic}
\end{algorithm}
```
Chiamata iniziale `contaFoglie(radice, 0, h)`.

> [!question] Traccia — 12/09/2023
> Contare i nodi **non foglia** con profondità $h$ tale che $h_1 \leq h \leq h_2$. Complessità $O(n)$.

Stessa idea, stesso stato (profondità): cambia solo il test — il nodo conta se è **interno** (almeno un figlio non null) e $h_1 \leq prof \leq h_2$.
## Stato monotòno / proprietà del cammino
> [!question] Traccia — 04/07/2023
> Albero binario con nodi blu (B) o gialli (G). Un nodo $v$ ha **antenati ben colorati** se il cammino dalla radice a $v$ è una sequenza (eventualmente vuota) di nodi blu seguita da una sequenza (eventualmente vuota) di nodi gialli. Contare i nodi con antenati ben colorati. Complessità $O(n)$.

**Idea.** Si trasportano due flag: $seenG$ (sul cammino è già comparso un giallo) e $valid$ (il cammino fin qui rispetta il pattern blu\*giallo\*). Al nodo $v$: se $v$ è blu **dopo** che è già comparso un giallo il pattern si rompe e resta rotto per tutta la discesa; un giallo è sempre ammesso e attiva $seenG$. Il nodo conta se $valid$ vale **dopo** aver incluso $v$.

> [!info] I due flag che scendono
> - $seenG$ = booleano: *sul cammino dalla radice fino a $v$ (incluso) è già comparso almeno un nodo giallo?*
> - $valid$ = booleano: *il cammino fin qui è ancora della forma "blu… poi giallo…"?* È **monotòno**: una volta diventato falso non torna più vero (per via dell'`and`), quindi l'intero sottoalbero sotto la rottura è scartato gratis.
>
> Qui il pattern riguarda il cammino **incluso $v$**, perciò si aggiornano i flag con il colore di $v$ *prima* di decidere se contarlo.

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
\State \Return $r + {}$\Call{contaBenColorati}{$v.\text{sx},\, seenG,\, valid$} $+$ \Call{contaBenColorati}{$v.\text{dx},\, seenG,\, valid$}
\end{algorithmic}
\end{algorithm}
```
Chiamata iniziale `contaBenColorati(radice, false, true)`. Una volta che $valid$ diventa falso non torna mai vero, quindi l'intero sottoalbero del nodo che rompe il pattern è scartato correttamente.

> [!question] Traccia — 16/02/2026
> Albero binario con un valore $\alpha(v)$ per nodo. Un nodo è **crescente** se la sequenza dei valori sul cammino dalla radice a $v$ è strettamente crescente, **pari** se quel cammino ha un numero pari di nodi. Contare le **foglie** crescenti e pari. Complessità $O(n)$.

Stato trasportato: l'ultimo valore visto $prec$ (per la radice $-\infty$), un flag $inc$ (cammino ancora strettamente crescente) e il numero di nodi $len$ sul cammino. Al nodo $v$: $inc' = inc \,\wedge\, (\alpha(v) > prec)$, $len' = len + 1$. Il conteggio scatta **solo sulle foglie** con $inc'$ vero e $len'$ pari; si ricorre con $prec = \alpha(v)$, $inc'$, $len'$. Chiamata iniziale con $prec = -\infty$, $inc = $ true, $len = 0$.
