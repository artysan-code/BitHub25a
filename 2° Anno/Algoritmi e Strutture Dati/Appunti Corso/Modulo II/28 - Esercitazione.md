### Algoritmo ($e \in MST$)
Input:$$\begin{array}{l}
-\ \text{grafo }G=(V,\ E,\ w)\ \text{ (pesi distinti)} \\
-\ \text{arco }e=(u,\ v)
\end{array}$$
Domanda:$$e \in MST(G)?$$
Goal:$$\text{tempo } O(m+n)$$
Sia $G'$ il grafo ottenuto da $G$ dove ha tolto tutti gli archi di $peso\geq w(e)$. Fa una visita di $G'$ BFS / DFS su un nodo $u$ per capire se $v$ è raggiungibile. Se $v$ è raggiungibile $\text{NO}$, altrimenti risponde $\text{SI}$.

Il costo dipende fondamentalmente dalla visita sul grafo che costa $O(n+m)$. Ma la correttezza?
- **Caso I**:$$\begin{array}{l}
v\text{ è raggiunto da }u\text{ in }G' \\ \\
\implies \exists\ \text{ cammino }p\text{ da }u\text{ a }v\text{ in }G' \\
\implies C=P\ \cup\ \{e\}\text{ è un ciclo in }G\text{ t.c. }e\text{ è il max di }C \\
\implies\ \text{cicle property }e\not\in MST(G)
\end{array}$$
- **Caso II**:$$\begin{array}{l}
v\text{ non raggiunto da }u\text{ in }G' \\ \\
S=\{w\in V:w\text{ è raggiungibile in }G'\} \\
 \implies v \in\ V\setminus S,\ e=(u,\ v)\text{ ottenere il taglio }(S, V \setminus S) \\
\implies e\text{ è l'arco più leggero che attraversa il taglio} \\
\implies \text{cut property } e\in MST
\end{array}$$