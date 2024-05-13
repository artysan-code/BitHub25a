# 2.1 Vettori applicati

Definiamo con $A^1,A^2,A^3$ rispettivamente retta, piano e spazio euclidei. Scegliendo un punto $O$ e un'unità di misura $\overline{OA}$ su $A^1$, stabiliamo una corrispondenza biunivoca tra i punti della retta e i numeri reali. In altre parole, possiamo associare la retta $A^1$ all'insieme dei numeri reali $\textsf{I\kern-0.1ex R}$. Questo introduce su $A^1$ le due operazioni fondamentali di somma e prodotto che lo rendono a tutti gli effetti un **campo**. 

Supponendo di voler estendere questo concetto al piano o allo spazio, partiamo scegliendo un punto $O \in A^2\ o\ A^3$. Da questo momento in poi, ogni punto nel piano o nello spazio può essere considerato non solo individualmente, ma anche in relazione al punto fisso $O$.

**Definizione 2.1**
Un vettore applicato in $O$ è un segmento orientato con primo estremo il punto $O \in A^2\ o\ A^3$ e secondo estremo un altro punto $X \in A^2\ o\ A^3$. 

Indicheremo con $V^2_O$ (o con $V_O^3$ nello spazio) l'insieme dei vettori applicati in $O$; il punto $O$ è l'origine di $V^2_O$ (o con $V_O^3$). Nota che possiamo definire una funzione biettiva. $$\Phi_{O}:(A)=\overline{OA}$$
**Osservazione 2.1**
A volte, quando l'origine sarà fissata, identificheremo i punti del piano con i vettori applicati nell'origine: semplicemente, staremo usando $\Phi_{O}$ senza dirlo esplicitamente.

**Definizione 2.2**
Presi due vettori applicati $\overrightarrow{OA}$ e $\overrightarrow{OB}$, la loro somma $\overrightarrow{OA}+\overrightarrow{OB}$ è il vettore applicato $\overrightarrow{OC}$, dove $C$ è il quarto vertice del parallelogramma individuato da $O$,$A$ e $B$.

**Proposizione 2.1**
$V_O^2$ con la somma descritta nella Definizione 2.2 è un gruppo commutativo.

***Dimostrazione**
L'*elemento neutro* è il vettore nullo: infatti, dalla definizione segue subito che $$\begin{array}{}
\forall\ \overrightarrow{OA}\in V_O^2 & &  &  &  &  \overrightarrow{OA}+\overrightarrow{OO}=\overrightarrow{OA}=\overrightarrow{OO}+\overrightarrow{OA} &  &  &  &  &
\end{array}$$
Anche l'*opposto* si trova facilmente: l'opposto del vettore $\overrightarrow{OA}$ è proprio il vettore $\overrightarrow{OA'}$, dove $A'$ è il simmetrico di $A$ rispetto a $O$ sulla retta passante per $O$ e $A$.

La *proprietà commutativa*: se $O$,$A$ e $B$ non sono allineati, $\overrightarrow{OA}$+$\overrightarrow{OB}$=$\overrightarrow{OB}$+$\overrightarrow{OA}$ segue dal fatto che i punti $O$,$A$ e $B$ e i punti $O$,$B$ e $A$ identificano lo stesso parallelogramma. Se invece i tre punti sono allineati, la commutatività segue dalla proprietà della congruenza fra segmenti orientati.

La *proprietà associativa*: consideriamo tre vettori applicati $\overrightarrow{OA_1}$,$\overrightarrow{OA_2}$ e$\overrightarrow{OA_3}$; supponiamo per un momento che fra i punti $O$, $A_1$, $A_2$ e $A_3$ non ce ne siano tre allineati. Poniamo $$\begin{array}{l}
\overrightarrow{OB_1}= \overrightarrow{OA_1}+\overrightarrow{OA_2}\quad\quad\overrightarrow{OB_2}= \overrightarrow{OA_2}+\overrightarrow{OA_3}\\
\overrightarrow{OC}=\overrightarrow{OB_1}+\overrightarrow{OA_3}=(\overrightarrow{OA_1}+\overrightarrow{OA_2})+\overrightarrow{OA_3}\\
\text{Dobbiamo dimostrare che} \\
\overrightarrow{OA_1}+(\overrightarrow{OA_2}+\overrightarrow{OA_3})= \overrightarrow{OA_1}+\overrightarrow{OB_2}=\overrightarrow{OC}
\end{array}$$
Prima di tutto, consideriamo il parallelogramma $OB_1CA_3$. Poiché i lati $B_1C$ e $OA_3$ sono paralleli e congruenti, e dato che anche $OA_3B_{2}A_{2}$ è un parallelogramma, i segmenti $OA_3$ e $A_{2}B_{2}$ risultano paralleli e congruenti. Di conseguenza, $B_{1}C$ e $A_{2}B_{2}$ sono entrambi paralleli e congruenti, il che implica che $A_{2}B_{1}CB_{2}$ è anch'esso un parallelogramma. Pertanto, $B_{2}C$ è parallelo e congruente ad $A_{2}B_{1}$.

Osserviamo ora che anche $OA_{1}B_{1}A_{2}$ è un parallelogramma, da cui segue che $A_{2}B_{1}$ è parallelo e congruente a $OA_{1}$. Quindi $B_{2}C$ e $OA_{1}$ sono entrambi paralleli e congruenti, implicando che $OA_{1}CB_{2}$ è un parallelogramma, ovvero $\overrightarrow{OC}=\overrightarrow{OA_{1}}+\overrightarrow{OB_{2}}$.

Resta da verificare la proprietà associativa nel caso in cui i punti $O$, $A_{1}$, $A_{2}$ e $A_{3}$ siano allineati; l'approccio è essenzialmente analogo. $\Box$ 

La somma non è l'unica operazione che possiamo fare con i vettori applicati; possiamo anche moltiplicarli per un numero reale.

**Definizione 2.3**
Se $\lambda\in\textsf{I\kern-0.1ex R}$ e $\overrightarrow{OA}\in V_{O}^2$, allora il *prodotto* di $\lambda$ per $\overrightarrow{OA}$ è il vettore $\overrightarrow{OC}=\lambda\overrightarrow{OA}$, dove $C$ è il punto sulla retta passante per $O$ e $A$ tale che il rapporto fra la lunghezza del segmento $\overline{OC}$ e quella del segmento $\overline{OA}$ sia esattamente $|\lambda|$. Inoltre, $C$ è sulla semiretta $OA$ se $\lambda$ è positivo, e sulla semiretta opposta se $\lambda$ è negativo. In parole povere, $\lambda\overrightarrow{OA}$ ha la stessa direzione di $\overrightarrow{OA}$, lunghezza moltiplicata per $|\lambda|$ e verso uguale od opposto a seconda del segno di $\lambda$.

**Proposizione 2.2**
Siano $\lambda$ e $\mu$ due numeri reali, e $\overrightarrow{OA}$, $\overrightarrow{OB}$ due vettori applicati. Allora
	i)$\lambda(\overrightarrow{OA}+\overrightarrow{OB})=\lambda\overrightarrow{OA}+\lambda\overrightarrow{OB}$ 
	ii)$(\lambda+\mu)\overrightarrow{OA}=\lambda\overrightarrow{OA}+\mu\overrightarrow{OA}$
	iii)$(\lambda\mu)\overrightarrow{OA}=\lambda(\mu\overrightarrow{OA})$
	iv)$1\overrightarrow{OA}=\overrightarrow{OA}\quad\text{e}\quad0\overrightarrow{OA}=\overrightarrow{OO}$
**Dimostrazione**
Le proprietà ii) - iv)  sono ovvie; 
i):
Se $O$,$A$ e $B$ sono allineati, è di nuovo tutto banale; supponiamo che non lo siano, e cominciamo prendendo $\lambda>0$, per cui troviamo nella situazione della figura sotto:
![[figura 1.png]]
Poniamo $\overrightarrow{OA_{1}}=\lambda\overrightarrow{OA}$, $\overrightarrow{OB_{1}}=\lambda\overrightarrow{OB}$, e $\overrightarrow{OC}=\overrightarrow{OA}+\overrightarrow{OB}$; dobbiamo dimostrare che $$\lambda\overrightarrow{OC}=\overrightarrow{OA_{1}}+\overrightarrow{OB_{1}}$$
Consideriamo le rette passanti per $A$ e $A_1$ parallele al segmento $\overline{OB}$; queste intersecano la retta passante per $O$ e $C$ rispettivamente nei punti $C$ e $C_1$. Per il teorema di Talete, il rapporto fra le lunghezze dei segmenti $\overline{OA_{1}}$ e $\overline{OA}$ è uguale al rapporto fra le lunghezze dei segmenti $\overline{OC_{1}}$ e $\overline{OC}$; quindi il vettore $\overrightarrow{OC_{1}}$ è proprio $\lambda\overrightarrow{OC}$.
Tracciamo ora le rette passanti per $C$ e $C_1$ parallele al segmento $\overline{OA}$. La retta per $C$ interseca la retta passante per $O$ e $B$ nel punto $B$, in quanto $OACB$ è un parallelogramma; la retta per $C_1$ invece interseca la retta passante per $O$  e $B$ in un punto che chiameremo $B'$ . Sempre il teorema di Talete ci dice che il rapporto fra le lunghezze dei segmenti $\overline{OC_{1}}$ e $\overline{OC}$ è uguale al rapporto fra le lunghezze dei segmenti $\overline{OB_{1}^{'}}$ e $\overline{OB}$; quindi il vettore $\overrightarrow{OB_{1}^{'}}$ è proprio $\lambda\overrightarrow{OB}$, cioè $B_{1}^{'}=B_{1}$. Quindi $OA_1C_1B_1$ è un parallelogramma e dunque $\overrightarrow{OC_{1}}=\overrightarrow{OA_{1}}+\overrightarrow{OB_{1}}$, come volevamo dimostrare.

Il caso $\lambda<0$ è analogo. $\Box$ 

Vi è ancora un altro modo di considerare le operazioni appena introdotte. Fissiamo un vettore $\overrightarrow{OA}\in V_{O}^{2}$. Tramite la somma con $\overrightarrow{OA}$ possiamo definire un'applicazione$$\tau_{\overrightarrow{OA}}(B)=\Phi_{O}^{-1}(\overrightarrow{OA}+\Phi_{O}(B))$$$\tau_{\overrightarrow{OA}}$ non è altro che una traslazione: la somma di un vettore corrispondente a una traslazione del piano.
Interpretiamo in modo analogo il prodotto per uno scalare. Fissato $\lambda\in\textsf{I\kern-0.1ex R}$, possiamo definire un'applicazione $\sigma_{\lambda}:A^2\rightarrow A^2$ associando al punto $A\in A^2$ il punto $B=\sigma_{\lambda}(A)\in A^2$ tale che $\overrightarrow{OB}=\lambda\overrightarrow{OA}$. In formule $$\sigma_{\lambda}(A)=\Phi_{O}^{-1}(\lambda\Phi_{O}(A))$$Questa volta $\sigma_{\lambda}$ è un omotetia (similitudine) di un centro $O$ e scala $|\lambda|$, seguita eventualmente da una simmetria rispetto a $O$ se $\lambda$ è negativo: il prodotto per un numero reale corrisponde a una omotetia del piano.

# 2.2 Coordinate

Prendiamo un singolo vettore $\overrightarrow{i}=\overrightarrow{OA_{1}}\in V_{O}^{2}$ e consideriamo la retta $r_1$ passante per  $O$ e $A_1$. 
Tutti i vettori di questa retta sono della forma $t*\overrightarrow{i} = t*\overrightarrow{OA_{1}}$ per un appropriato $t\in \textsf{I\kern-0.1ex R}$ (multipli di $\overrightarrow{i}$). Fissando un'origine $O$ e un vettore unitario (  $\overrightarrow{i}$  ) a ogni punto $P$ della retta possiamo associare uno e un solo numero reale $t$ tale che $$\overrightarrow{OP}=t*\overrightarrow{i}$$il numero reale $t$ è la coordinata di $\overrightarrow{OP}$ rispetto a $\overrightarrow{i}$.
Ci troviamo sul piano, quindi non tutti i vettori di $V_{O}^{2}$  stanno sulla retta $r$. 
Prendiamone allora uno che non ne appartiene $\overrightarrow{j}=\overrightarrow{OA_{2}}$ . Tutti i vettori della retta $r_2$ per $O$ e $A_2$ si scrivono come multipli di $\overrightarrow{j}$. In questo modo possiamo esprimere in termini di $\overrightarrow{i}$ e $\overrightarrow{j}$  tutti i vettori delle due rette $r_1$ e $r_2$.

**Proposizione 2.3**
Siano $\overrightarrow{i}=\overrightarrow{OA_{1}}$ e $\overrightarrow{j}=\overrightarrow{OA_{2}}$ due vettori non proporzionali di $V_{O}^{2}$.
Allora per ogni vettore $\overrightarrow{OP}\in V_{O}^{2}$ esistono due numeri reali $x_{1},x_{2} \in \textsf{I\kern-0.1ex R}$ tali che $$\overrightarrow{OP}=x_{1}^{'}\ \overrightarrow{i}+x_{2}^{'}\ \overrightarrow{j}$$Inoltre $x_1$ e $x_2$ sono unici, nel senso che se $x_1^{'}$  e $x_{2}^{'}$  sono due altri numeri reali tali che $\overrightarrow{OP}= x_{1}^{'}\ \overrightarrow{i}+x_{2}^{'}\ \overrightarrow{j}$, allora $x_{1}^{'}= x_{1}$ e $x_{2}^{'}= x_{2}$. ^89ab91

*Dimostrazione*
Cominciamo con l'esistenza.
Indichiamo con $r_1$ la retta passante per $O$ e $A_1$ (o $A_2$). Tracciamo la parallela a $r_2$ passante per $P$; questa interseca $r_1$ in un punto $P_1$. Analogamente la parallela a $r_1$ passante per $P$; interseca $r_2$ in un punto $P_2$. Per costruzione $OP_1PP_2$ è un parallelogramma, quindi $$\overrightarrow{OP}=\overrightarrow{OP_{1}}+\overrightarrow{OP_{2}}$$$P_1$ è sulla retta per $O$ e $A_{1}$; quindi esiste un $x_1 \in \textsf{I\kern-0.1ex R}$ tale che $\overrightarrow{OP_{1}}=x_{1}\overrightarrow{i}$. 
Analogamente troviamo un $x_{2}\in\textsf{I\kern-0.1ex R}$ tale che $\overrightarrow{OP_{2}}=x_{2}\overrightarrow{j}$. 
Per l'unicità $$x_{1}^{'}\ \overrightarrow{i}+x_{2}^{'}\ \overrightarrow{j}=\overrightarrow{OP}=x_{1}\ \overrightarrow{i}+x_{2}\ \overrightarrow{j}$$otteniamo $$(x_{1}^{'}+x_{1})\overrightarrow{i}=(x_{2}^{'}+x_{2})\overrightarrow{j}$$
Il vettore a primo membro è un multiplo di $\overrightarrow{i}$, per cui appartiene a $r_1$. Il vettore a secondo membro, invece, appartiene a $r_2$; siccome sono uguali, devono stare nell'intersezione delle due rette che è il vettore nullo $\overrightarrow{OO}$ dunque $$(x_{1}^{'}+x_{1})\overrightarrow{i}= \overrightarrow{OO} = (x_{2}^{'}+x_{2})\overrightarrow{j}$$
Dunque una volta scelti due vettori non proporzionali $\overrightarrow{i}$ e $\overrightarrow{j}$ di $V_{O}^{2}$(una volta fissata la base $B=\{\ \ \overrightarrow{i},\ \ \overrightarrow{j}\ \ \}$ di $V_{O}^{2}$), a ogni vettore di $V_{O}^{2}$ possiamo associare in modo unico una coppia di numeri reali, le sue coordinate rispetto alla base $B$. 
In modo più formale, abbiamo definito un'applicazione $$F_{B}(\overrightarrow{OP})=\left|\begin{array}{}
x_{1} \\
x_{2}
\end{array}\right|$$dove $x_1$ e $x_2$ sono gli unici numeri reali che verificano la [[#^89ab91|prop 2.3]]. 
Gli elementi di $\textsf{I\kern-0.1ex R}^{2}$ verranno scritti per colonna, non per riga.

***Esempio 2.1***
Sia $B=\{\ \ \overrightarrow{i},\ \ \overrightarrow{j}\ \ \}$ una base di $V_{O}^{2}$, e prendiamo il vettore $\overrightarrow{OC}=2\ \overrightarrow{i}-4\ \overrightarrow{j}$
Le coordinate di $\overrightarrow{OC}$ sono, per definizione, 2 e -4; in altre parole, $$F_{B}(\overrightarrow{OP})=\left|\begin{array}{}
2 \\
-4
\end{array}\right|$$Sia $\overrightarrow{OD}=-\overrightarrow{i}+4\ \overrightarrow{j}$; le sue coordinate sono $\left|\begin{array}{}-1\\4\end{array}\right|$. 
Per trovare le coordinate di  $\overrightarrow{OC}+\overrightarrow{OD}$ calcoliamo $$\begin{array}{}
\overrightarrow{OC}+\overrightarrow{OD}=(2\ \overrightarrow{i}-4\ \overrightarrow{j})+(-\overrightarrow{i}+4\ \overrightarrow{j})= \\
= (2\ \overrightarrow{i}-\overrightarrow{i})+(-4\ \overrightarrow{j}+4\ \overrightarrow{j})= \\
=(-2-1)\overrightarrow{i}+(-4+4)\overrightarrow{j}=\overrightarrow{i}+0\ \overrightarrow{J} = \overrightarrow{i}
\end{array}$$per cui $$F_{B}(\overrightarrow{OC}+\overrightarrow{OD})=\left|\begin{array}{}
1 \\0\end{array}\right|$$
*Osservazione 2.4*
La funzione $F_{B}$ (o le coordinate di un vettore) dipende dalla base scelta: cambiando base, le coordinate cambiano. Per esempio, siano $\overrightarrow{i},\ \overrightarrow{j} \in V_{O}^{2}$ due vettori non proporzionali e consideriamo $B=\{\ \ \overrightarrow{i},\ \ \overrightarrow{j}\ \ \}$ e $B^{'}=\{\ \ 2\overrightarrow{i},\ \ \overrightarrow{j}\ \ \}$; siccome $2\ \overrightarrow{i}$ e $\overrightarrow{j}$  continuano a essere non proporzionali, sia $B$ che $B^{'}$ sono basi di $V_{O}^{2}$. 

Ora prendiamo il vettore $\overrightarrow{OP}=4\ \overrightarrow{i}-3\ \overrightarrow{j}$. Le coordinate rispetto alla base $B^{'}$ sono 2 e -3. Quindi $$F_{B}(\overrightarrow{OP})=\left|\begin{array}{} 4\\-3 \end{array}\right|\neq\left|\begin{array}{} 2\\-3 \end{array}\right|=F_{B^{'}}(\overrightarrow{OP})$$
Sulla retta, a ogni numero reale corrispondeva uno e un solo punto: la funzione coordinata era bigettiva. Stessa cosa qui: 