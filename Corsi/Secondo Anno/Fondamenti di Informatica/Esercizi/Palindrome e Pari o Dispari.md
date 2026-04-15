$L_{p,pal}=\{ x\in \{a\ |\ b\}^k :\text{x è palindroma}\ \&\ \text{x ha lunghezza pari}\}$

Es.
abba -> 1 (pari e palindroma)
ababb -> 0 (dispari e non palindroma)
ababa -> 0 (dispari)

Definiamo stato di **accettazione** e stato di **rigetto**:$$\begin{array}{} 
q_{p,pal}^p \implies \text{Stato di accettazione} \\
q_{r}^p \implies \text{Stato di rigetto}
\end{array}$$
Programma:$$\displaystyle\begin{array}{l}
<q_{0}^p,a,\square,q_{0}^p,d> \\
<q_{0}^p,b,\square, q_{0}^p,d> \\
<q_{z}^p,y,y,q_{z}^p,d>&\forall\ y,z \in \{a,b\}\\
<q_{z}^p,\square,\square,q_{z_{ind}}^p,s> \\
<q_{z_{ind}}^p,z,\square,q_{1}^p,s> \\
<q_{z_{ind}}^p,y,\square,q_{r}^p,f>  \\
<q_{z_{ind}}^p,\square,q_{r}^p,f> \\
<q_{1}^p,y,y,q_{1}^p,s> \\
<q_{1}^p,\square,\square,q_{0}^p,d> \\
<q_{0}^p,\square,\square,q_{ppal}^p,f>
\end{array}$$
Esercizio per casa: Sostituire $\{a,b\}^*$ con $\{a,b,q\}^*$.

E invece ora con dispari?

Definiamo stato di **accettazione** e stato di **rigetto**:$$\begin{array}{} 
q_{d,pal}^d \implies \text{Stato di accettazione} \\
q_{r}^d \implies \text{Stato di rigetto}
\end{array}$$

Programma (cambiare tutti gli ^p in ^d):$$\displaystyle\begin{array}{l}
<q_{0}^p,a,\square,q_{0}^p,d> \\
<q_{0}^p,b,\square, q_{0}^p,d> \\
<q_{z}^p,y,y,q_{z}^p,d>&\forall\ y,z \in \{a,b\}\\
<q_{z}^p,\square,\square,q_{z_{ind}}^p,s> \\
<q_{z_{ind}}^p,z,\square,q_{1}^p,s> \\
<q_{z_{ind}}^p,y,\square,q_{r}^p,f>  \\
<q_{z_{ind}}^p,\square,\square,q_{d,pal}^p,f> \\
<q_{1}^p,y,y,q_{1}^p,s> \\
<q_{1}^p,\square,\square,q_{0}^p,d> \\
<q_{0}^p,\square,\square,q_{r}^p,f>
\end{array}$$

Ora se voglio invece $L_{pal}=\{x\in\{z,b\}^k:\text{x è palindroma}\}$ ma in un modo diverso? Proviamo a riutilizzare le due precedenti. Usando il **concetto di funzione**.

Questa è una **simulazione**, e può essere fatta in questa maniera a **scatola chiusa** (non possiamo scrivere sulle macchine che stiamo simulando, ma solo usarle). Esiste anche quella a scatola aperta ma la vedremo in futuro.
$T_{pal}:\text{input }x\in\{z,b\}^*\text{ su }n_{1}$:
1) Copia il contenuto di $n_{1}$ su $n_{2}$ e $n_{3}$
2) Simula $T_{p,pal}(x)$ su $n_{2}$: se $T_{p,pal}$ accetta allora termina in $q_{a}$, altrimenti se $T_{p,pal}$ rigetta allora fase successiva.
3) Simula $T_{d,pal}$ su $n_{3}$: se $T_{d,pal}$ accetta allora termina in $q_{a}$, altrimenti se $T_{d,pal}$ rigetta allora termina con $q_{r}$

Che si potrebbe riscrivere.

$T_{pal}:\text{input }x\in\{z,b\}^*\text{ su }n_{1}$:
1) Copia il contenuto di $n_{1}$ su $n_{2}$ e $n_{3}$
2) $q=T_{p,pal}(n_{2})$ se $q=q_{p,pal}^p$ allora termina in $q_{a}$, se $q_{q_{r}^p}$ allora $q'=T_{d,pal}(n_{3})$
3) E così continui...

Importante il concetto di **simulazione**, se dovessimo scrivere il programma dovremmo scrivere:$$\begin{array}{l}
<q_{0},(y,\square,\square),(\square,y,y),q_{0},(d,d,d)>&\forall\ y\in \{a,b\} \\
<q_{0},(\square,\square,\square),(\square,\square,\square),q_{1},(f,s,s)> \\
<q_{1},(\square,y,y),(\square,y,y),q_{1},(f,s,s)> \\
<q_{1},(\square,\square,\square),(\square,\square,\square),q_{0}^p,(f,d,d)> \\
<q_{r}^p, (\square,\square,z),(\square,\square,z),q_{0}^d,(f,f,f)>
\end{array}$$