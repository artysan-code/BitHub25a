### Problema 1
Una città e' modellata come un grafo diretto e pesato $G=(V,E,w)$ dove ad ogni arco $e\in E$ e' associato un peso $w(e)\geq 0$ che rappresenta il costo, in termini di benzina consumata, per attraversare l'arco (strada) $e$. I vostri docent del corso di algoritmi, Guala e Clementi, vogliono andare a vedere la partita della roma allo stadio, che si trova nel nodo $t$. Loro sono rispettivamente nei nodi $s_1$ e $s_2$, e possiedono una macchina ciascuno. Volendo, possono incontrarsi in un nodo del grafo, parcheggiare una delle due macchine, e proseguire insieme. Ma di solito in questa città parcheggiare costa. Per ogni nodo $v$, dunque, conosco il costo $c(v)$ del parcheggio presente in $v$ (per semplicità $c(s_{1})=c(s_{2})=c(t)=0$). 
Progettare un algoritmo che in tempo $O(m+n\log n)$ calcoli la soluzione che Guala e Clementi devono adottare per spendere complessivamente il meno possibile in termini di costo della benzina più costo del parcheggio.



### Problema 2
Input:
- grafo orientato $G=(V,E,w)$ con pesi non negativi 
- $B\subseteq E$ sottoinsieme di archi blu 
- $k$ intero, $s,\ t\in V$

Output:
- un cammino di costo minimo da $s$ a $t$ che usa al più $k$ archi blu