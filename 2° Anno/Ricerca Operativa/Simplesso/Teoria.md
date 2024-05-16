**Input**: $A\in \textsf{I\kern-0.1ex R}^{m\times n},b\in\textsf{I\kern-0.1ex R}^{m},c\in\textsf{I\kern-0.1ex R}^{n}$ ed una base ammissibile $B=\{B[1],\dots,B[m]\}$ per il sistema$(3.3)-(3.4)$.

**Output**: Una soluzione ottima di base $\overline{x}$ per il programma lineare $(3.1)-(3.4)$ oppure un raggio $r$ che dimostri che il problema è illimitato.

1. Si calcoli il tableau rispetto alla base $B$ e la soluzione di base $\overline{x}$ relativa a $B$.
2. Se $\overline{c}\leq 0$, allora $\overline{x}$ è una soluzione ottima$\implies$ **STOP**
3. Altrimenti si scelga un indice $k$ tale che $\overline{c}_{k}>0$.
4. Se $\overline{a}_{ik}\leq 0$ per ogni $i\in \{1,\dots,m\}$, allora il problema è illimitato; si definisca $r$ come in $(3.20)-(3.22)$; **STOP**
5. Altrimenti , si scelga $h\in\{1,\dots,m\}$ tale che $$\overline{a}_{hk}>0\quad\text{ e }\quad\frac{\overline{b}_{h}}{\overline{a}_{hk}}=min\{\frac{\overline{b}_{i}}{\overline{a}_{ik}}: i\in\{1,\dots,m\},\overline{a}_{ik}>0\}$$
6. Si ridefinisca $B[h]:=k$ e si torni al passo 1.