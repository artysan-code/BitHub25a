# 2.1 Vettori applicati

Rappresentiamo con $A^1$ (rispettivamente $A^2,A^3$) la retta euclidea standard. Scegliendo un punto $O$ e un'unità di misura $\overline{OA}$ su $A^1$, stabiliamo una corrispondenza biunivoca tra i punti della retta e i numeri reali. In altre parole, possiamo assimilare la retta $A^1$ all'insieme dei numeri reali $\textsf{I\kern-0.1ex R}$. Questo processo introduce su $A^1$ una struttura di campo, con operazioni di somma e prodotto.

Ora vogliamo esaminare se e quando sia possibile estendere questa costruzione al piano e allo spazio. Iniziamo selezionando un punto $O \in A^2$ (o $O \in A^3$). Da questo momento in poi, ogni punto nel piano (o nello spazio) può essere considerato non solo individualmente, ma anche in relazione al punto fisso $O$.

**Definizione 2.1

Un vettore applicato in $O$ è un segmento orientato con primo estremo il punto $O \in A^2$ (rispettivamente, $O \in A^3$) e secondo estremo un altro punto $A \in A^2$ (rispettivamente, $A \in A^3$). 


Indicheremo con $V^2_O$ (o con $V_O^3$ nello spazio) l'insieme dei vettori applicati in $O$; il punto $O$ è l'origine di $V^2_O$ (o con $V_O^3$). Nota che possiamo definire una funzione bigettiva $$\Phi_{O}:(A)=\overline{OA}$$**Osservazione 2.1

A volte, quando l'origine sarà fissata, identificheremo i punti del piano con i vettori applicati nell'origine: semplicemente, staremo usando $\Phi_{O}$ senza dirlo esplicitamente.
**Definizione 2.2

Presi due vettori applicati $\overrightarrow{OA}$ e $\overrightarrow{OB}$, la loro somma $\overrightarrow{OA}+\overrightarrow{OB}$ è il vettore applicato $\overrightarrow{OC}$, dove $C$ è il quarto vertice del parallelogramma individuato da $O$,$A$ e $B$.
**Proposizione 2.1

$V_O^2$ con la somma descritta nella Definizione 2.2 è un gruppo commutativo.
***Dimostrazione

L'elemento neutro è il vettore nullo: infatti, dalla definizione segue subito che $$\begin{array}{}
\forall\ \overrightarrow{OA}\in V_O^2 & &  &  &  &  \overrightarrow{OA}+\overrightarrow{OO}=\overrightarrow{OA}=\overrightarrow{OO}+\overrightarrow{OA} &  &  &  &  &
\end{array}$$
anche 