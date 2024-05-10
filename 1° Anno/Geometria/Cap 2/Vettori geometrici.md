# 2.1 Vettori applicati

Rappresentiamo con $A^1$ (rispettivamente $A^2,A^3$) la retta euclidea standard. Scegliendo un punto $O$ e un'unità di misura $\overline{OA}$ su $A^1$, stabiliamo una corrispondenza biunivoca tra i punti della retta e i numeri reali. In altre parole, possiamo assimilare la retta $A^1$ all'insieme dei numeri reali $\textsf{I\kern-0.1ex R}$. Questo processo introduce su $A^1$ una struttura di campo, con operazioni di somma e prodotto.

Ora vogliamo esaminare se e quando sia possibile estendere questa costruzione al piano e allo spazio. Iniziamo selezionando un punto $O \in A^2$ (o $O \in A^3$). Da questo momento in poi, ogni punto nel piano (o nello spazio) può essere considerato non solo individualmente, ma anche in relazione al punto fisso $O$.

**Definizione 2.1**
Un vettore applicato in $O$ è un segmento orientato con primo estremo il punto $O \in A^2$ (rispettivamente, $O \in A^3$) e secondo estremo un altro punto $A \in A^2$ (rispettivamente, $A \in A^3$). 


Indicheremo con $V^2_O$ (o con $V_O^3$ nello spazio) l'insieme dei vettori applicati in $O$; il punto $O$ è l'origine di $V^2_O$ (o con $V_O^3$). Nota che possiamo definire una funzione bigettiva $$\Phi_{O}:(A)=\overline{OA}$$

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

Vi è ancora un altro modo di considerare le operazioni appena introdotte. Fissiamo un vettore $\overrightarrow{OA}\in V_{O}^{2}$. Tramite la somma con $\overrightarrow{OA}$ possiamo definire un'applicazione $$\tau_{\overrightarrow{OA}}(B)=\Phi_{O}^{-1}(\overrightarrow{OA}+\Phi_{O}(B))$$
$\tau_{\overrightarrow{OA}}$ non è altro che una traslazione: la somma di un vettore corrispondente a una traslazione del piano.
Interpretiamo in modo analogo il prodotto per uno scalare. Fissato $\lambda\in\textsf{I\kern-0.1ex R}$, possiamo definire un'applicazione $\sigma_{\lambda}:A^2\rightarrow A^2$ associando al punto $A\in A^2$ il punto $B=\sigma_{\lambda}(A)\in A^2$ tale che $\overrightarrow{OB}=\lambda\overrightarrow{OA}$. In formule $$\sigma_{\lambda}(A)=\Phi_{O}^{-1}(\lambda\Phi_{O}(A))$$
Questa volta $\sigma_{\lambda}$ è un omotetia (similitudine) di un centro $O$ e scala $|\lambda|$, seguita eventualmente da una simmetria rispetto a $O$ se $\lambda$ è negativo: il prodotto per un numero reale corrisponde a una omotetia del piano.