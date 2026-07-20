# Variabili aleatorie multidimensionali discrete
Densità congiunta e densità marginali, legame tra le due, e indipendenza tra variabili aleatorie discrete.
> [!info] Perimetro del corso
> Per le v.a. multidimensionali **si tratta solo il caso discreto**.
## Definizione
Date $m$ v.a. discrete (come quelle viste finora) $X_{1},\dots,X_{m}$ definite su uno stesso spazio di probabilità, quindi $X_{i}:\ohm\to \mathbb{R}$ con opportune proprietà, vogliamo considerare la funzione $\underline{X}=(X_{1},\dots,X_{m}):\ohm\to \mathbb{R}^{m}$ così definita: $$\underline{X}(w)=(X_{1}(w),\dots,X_{m}(w))\quad\quad\forall\ w\in\ohm$$L'insieme dei valori assunti dalla v.a. $\underline{X}$, che indicheremo con $\delta_{\underline{X}}$, soddisfa la seguente condizione: $$\delta_{\underline{X}}\subset\underset{\text{prodotto cartesiano di insiemi finiti o numerabili}}{\underbrace{\delta_{X_{1}}\times\dots\times \delta_{X_{m}}}}$$Quindi l'insieme $\delta_{\underline{X}}$ è finito o numerabile, e la funzione $\underline{X}:\ohm\to \mathbb{R}^{m}$ è una v.a. **multidimensionale** (anzi **$m$-dimensionale**) **discreta**.
### Esempio
Si lanciano due dadi e sia $\ohm=\{1,\dots,6\}\times\{1,\dots,6\}$. (Se i dadi sono equi si ha $P(A)=\frac{\#A}{36}$ per ogni $A\subset \ohm$, cioè uno [[Cap 2 - Introduzione alla probabilità#Spazio di Probabilità Uniforme Discreto|spazio di probabilità uniforme discreto]].)
Vogliamo considerare la v.a. di dimensione 2 che indica la somma e il prodotto dei due numeri ottenuti. Allora avremo $$\underline{X}(w)=\underline{X}(w_{1},w_{2})=(\underset{=X_{1}(w_{1},w_{2})}{\underbrace{w_{1}+w_{2}}},\underset{=X_{2}(w_{1},w_{2})}{\underbrace{w_{1}\cdot w_{2}}})\quad\quad\forall\ w=(w_{1},w_{2})\in\ohm$$
### Osservazioni
- Spesso, quando tratteremo le v.a. discrete multidimensionali, avremo a che fare con **sommatorie con più indici**.
- Nel caso continuo (dove in generale avremo integrali al posto di sommatorie) si dovrebbe fare riferimento agli **integrali multipli**; per questo motivo tratteremo il caso multidimensionale solo nel discreto, mentre tratteremo solo le v.a. continue unidimensionali.
  (In realtà non sempre servono integrali multipli, ma nei "casi facili" è così.)
## Densità congiunta e densità marginali
A questo punto possiamo definire la densità discreta di $\underline{X}$ come si fa per le v.a. discrete unidimensionali: $$P_{\underline{X}}:\mathbb{R}^{m}\to[0,1]\quad\quad P_{\underline{X}}(\underline{x})=P(\underline{X}=\underline{x})\quad\quad\text{dove }\underline{x}=(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$$(si noti l'uso delle **lettere minuscole** per i valori).
La densità discreta di $\underline{X}=(X_{1},\dots,X_{m})$ è detta **congiunta** perché descrive congiuntamente il comportamento delle v.a. $X_{1},\dots,X_{m}$. Per le v.a. $X_{1},\dots,X_{m}$, e per le loro densità discrete, si usa il termine **marginali**.
### Proprietà della densità congiunta
Per la densità congiunta $P_{\underline{X}}$ si mantengono alcune proprietà viste per il caso unidimensionale:
- se $\underline{x}\not\in \delta_{\underline{X}}$, allora $P_{\underline{X}}(\underline{x})=0$;
- per ogni $A\subset \mathbb{R}^{m}$ $$P(\underline{X}\in A)=\sum_{\underline{x}\in A\cap \delta_{\underline{X}}}P_{\underline{X}}(\underline{x})$$da cui (ponendo $A=\mathbb{R}^{m}$) si ottiene $$\begin{bmatrix}
\sum_{\underline{x}\in \delta_{\underline{X}}}P_{\underline{X}}(\underline{x})=1
\end{bmatrix}$$   **Osservazione.** Ovviamente qui la sommatoria può essere ristretta ai vettori $\underline{x}$ per cui $P_{\underline{X}}(\underline{x})>0$.
### Legame tra congiunta e marginali
Note le congiunte, si possono ricavare le marginali. Al contrario, **note le marginali non è possibile ricavare la congiunta**.
Questo per certi versi non sorprende: le marginali descrivono il comportamento di $X_{1},\dots,X_{m}$ prese *separatamente*; la congiunta descrive il comportamento *congiunto* delle v.a. $X_{1},\dots,X_{m}$ e contiene più informazioni delle marginali.
--- Fine lezione 09 ---
### Proposizione (le marginali si ottengono dalla congiunta)
Sia $\underline{X}=(X_{1},\dots,X_{m})$ una v.a. $m$-dimensionale con densità congiunta $P_{\underline{X}}$ e con densità marginali $P_{X_{1}},\dots,P_{X_{m}}$. Allora, per ogni $i\in\{1,\dots,m\}$, si ha $$\begin{bmatrix}
P_{X_{i}}(x_{i})=\sum_{\underline{x}\in \delta_{\underline{X}}}P_{\underline{X}}(\underline{x})
\end{bmatrix}$$dove, quando si scrive $\underline{x}$, si pensa a $\underline{x}=(x_{1},\dots,x_{m})$ **la cui coordinata $i$-sima coincide con il valore $x_{i}$ fissato**.
Quindi, note le congiunte, abbiamo una formula che consente di ottenere ciascuna delle $m$ marginali.
#### Dimostrazione
Per ogni $i\in\{1,\dots,m\}$ si ha $$\begin{array}{ll}
P_{X_{i}}(x_{i})=P(X_{i}=x_{i}) & =P\left( \bigcup_{\underline{x}\in \delta_{\underline{X}}}\{\underline{X}=\underline{x}\} \right)=P\left( \bigcup_{\underline{x}\in \delta_{\underline{X}}}(\{X_{1}=x_{1}\}\cap\dots\cap\{X_{m}=x_{m}\}) \right) \\
 & \overset{(\star)}{=}\displaystyle\sum_{\underline{x}\in \delta_{\underline{X}}}P(\{X_{1}=x_{1}\}\cap\dots\cap\{X_{m}=x_{m}\})=\sum_{\underline{x}\in \delta_{\underline{X}}}P(\underline{X}=\underline{x})=\sum_{\underline{x}\in \delta_{\underline{X}}}P_{\underline{X}}(\underline{x})
\end{array}$$dove in $(\star)$ si è usato che l'insieme $\delta_{\underline{X}}$ è al più numerabile, e quindi si ha un'unione al più numerabile di eventi disgiunti a due a due (si applica la [[Cap 2 - Introduzione alla probabilità#Definizione (Misure di Probabilità)|$\sigma$-additività]]) $\Box$
### Esempio: due congiunte diverse con le stesse marginali
Presentiamo due diverse densità congiunte $m$-dimensionali, in particolare con $m=2$, per cui si ha $$\begin{cases}
\text{"}P_{X_{1}}\text{ della 1}^{\text{a}}\text{ congiunta" coincidente con "}P_{X_{1}}\text{ della 2}^{\text{a}}\text{ congiunta"} \\
\text{"}P_{X_{2}}\text{ della 1}^{\text{a}}\text{ congiunta" coincidente con "}P_{X_{2}}\text{ della 2}^{\text{a}}\text{ congiunta"}
\end{cases}$$In entrambi i casi avremo $m=2$ e $$\delta_{\underline{X}}=\{0,1\}\times\{0,1\}=\{(0,0),(0,1),(1,0),(1,1)\}$$
**Congiunta n. 1:** $P_{\underline{X}}(0,0)=P_{\underline{X}}(0,1)=P_{\underline{X}}(1,0)=P_{\underline{X}}(1,1)=\frac{1}{4}$ (è ben posta). Le marginali sono $$\begin{array}{l|l}
P_{X_{1}}(0)=P_{\underline{X}}(0,0)+P_{\underline{X}}(0,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} & P_{X_{2}}(0)=P_{\underline{X}}(0,0)+P_{\underline{X}}(1,0)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} \\
P_{X_{1}}(1)=P_{\underline{X}}(1,0)+P_{\underline{X}}(1,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2} & P_{X_{2}}(1)=P_{\underline{X}}(0,1)+P_{\underline{X}}(1,1)=\frac{1}{4}+\frac{1}{4}=\frac{1}{2}
\end{array}$$Quindi le marginali di $X_{1}$ e $X_{2}$ coincidono, cioè $P_{X_{1}}=P_{X_{2}}$; inoltre in entrambi i casi si ha la [[Distribuzioni binomiale e ipergeometrica#Distribuzione Bernoulliana|distribuzione bernoulliana]] di parametro $p=\frac{1}{2}$.
**Congiunta n. 2:** $P_{\underline{X}}(0,0)=P_{\underline{X}}(1,1)=\frac{1}{3}$ e $P_{\underline{X}}(1,0)=P_{\underline{X}}(0,1)=\frac{1}{6}$ (è ben posta). Le marginali sono $$\begin{array}{l|l}
P_{X_{1}}(0)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} & P_{X_{2}}(0)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} \\
P_{X_{1}}(1)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2} & P_{X_{2}}(1)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2}
\end{array}$$Quindi abbiamo le stesse marginali che avevamo ottenuto con la congiunta precedente.
> [!quote] Conclusione
> Abbiamo ottenuto ciò che volevamo: **due scelte diverse per $P_{\underline{X}}$** per cui "$P_{X_{i}}$ della 1ª congiunta" coincide con "$P_{X_{i}}$ della 2ª congiunta" per ogni $i=1,\dots,m$. È la prova che dalle marginali non si può risalire alla congiunta.
> (Poi nel caso specifico, dove $m=2$, per entrambe le congiunte si ha anche $P_{X_{1}}=P_{X_{2}}$; questo non era richiesto.)
## Indipendenza tra variabili aleatorie
### Definizione
Una famiglia finita di v.a. **discrete** $X_{1},\dots,X_{m}$, con $m\geq 2$, è una famiglia di **v.a. indipendenti** se $$\forall\ A_{1},\dots,A_{m}\subset \mathbb{R}\quad\quad P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\})=P(X_{1}\in A_{1})\cdot\dots\cdot P(X_{m}\in A_{m})$$Una famiglia **infinita** di v.a. discrete è una famiglia di v.a. indipendenti se questo accade per qualsiasi sottofamiglia finita.
### Proposizione (gli eventi associati sono indipendenti)
Sia $X_{1},\dots,X_{m}$, con $m\geq 2$, una famiglia finita di v.a. indipendenti. Allora, per ogni $A_{1},\dots,A_{m}\subset \mathbb{R}$, gli eventi $\{X_{1}\in A_{1}\},\dots,\{X_{m}\in A_{m}\}$ sono [[Cap 2 - Introduzione alla probabilità#Indipendenza tra Eventi|eventi indipendenti]].
#### Dimostrazione
Per ogni $\{i_{1},\dots,i_{k}\}\subset\{1,\dots,m\}$ con $k\geq 2$ si deve avere $$P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\})=P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})$$Si vede subito che questo è vero se $k=m$, e quindi $\{i_{1},\dots,i_{k}\}=\{1,\dots,m\}$. Vediamo cosa succede nel caso in cui $2\leq k\leq m-1$.
Sia $\{j_{1},\dots,j_{m-k}\}$ il complementare di $\{i_{1},\dots,i_{k}\}$; quindi $$\{i_{1},\dots,i_{k}\}\cup\{j_{1},\dots,j_{m-k}\}=\{1,\dots,m\}\quad\quad(\text{con intersezione vuota})$$Allora, completando con gli eventi certi $\{X_{j}\in \mathbb{R}\}=\ohm$, $$\begin{array}{ll}
P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\}) & =P(\{X_{i_{1}}\in A_{i_{1}}\}\cap\dots\cap\{X_{i_{k}}\in A_{i_{k}}\}\cap\overset{=\ohm}{\overbrace{\{X_{j_{1}}\in \mathbb{R}\}}}\cap\dots\cap\overset{=\ohm}{\overbrace{\{X_{j_{m-k}}\in \mathbb{R}\}}}) \\
 & \overset{(\star)}{=}P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})\underset{=P(\ohm)=1}{\underbrace{P(X_{j_{1}}\in \mathbb{R})}}\cdot\dots\cdot\underset{=P(\ohm)=1}{\underbrace{P(X_{j_{m-k}}\in \mathbb{R})}} \\
 & =P(X_{i_{1}}\in A_{i_{1}})\cdot\dots\cdot P(X_{i_{k}}\in A_{i_{k}})
\end{array}$$dove in $(\star)$ si è usata l'indipendenza delle v.a.; e questa è l'uguaglianza desiderata $\Box$
### Proposizione (condizione necessaria e sufficiente)
Sia $\underline{X}=(X_{1},\dots,X_{m})$ una v.a. $m$-dimensionale, con $m\geq 2$. Allora $$X_{1},\dots,X_{m}\text{ è una famiglia di v.a. discrete indipendenti}\iff\begin{bmatrix}
P_{\underline{X}}(x_{1},\dots,x_{m})=P_{X_{1}}(x_{1})\cdot\dots\cdot P_{X_{m}}(x_{m})
\end{bmatrix}$$per ogni $(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$.
> [!quote] Commento
> **La congiunta è il prodotto delle marginali.**

#### Dimostrazione
$(\implies)$ Consideriamo la definizione di famiglia di v.a. indipendenti scegliendo, per ogni $(x_{1},\dots,x_{m})\in \mathbb{R}^{m}$, gli insiemi $A_{1}=\{x_{1}\},\dots,A_{m}=\{x_{m}\}$. Allora, poiché si ha $$\underset{=P(\underline{X}=\underline{x})=P_{\underline{X}}(\underline{x})}{\underbrace{P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\})}}=\underset{=P(X_{1}=x_{1})\cdot\dots\cdot P(X_{m}=x_{m})=P_{X_{1}}(x_{1})\cdot\dots\cdot P_{X_{m}}(x_{m})}{\underbrace{P(X_{1}\in A_{1})\cdot\dots\cdot P(X_{m}\in A_{m})}}$$abbiamo quanto desideravamo.
$(\impliedby)$ Supponiamo che la densità congiunta sia uguale al prodotto delle densità marginali. Allora, per ogni $A_{1},\dots,A_{m}\subset \mathbb{R}$, $$\begin{array}{ll}
P(\{X_{1}\in A_{1}\}\cap\dots\cap\{X_{m}\in A_{m}\}) & =P((X_{1},\dots,X_{m})\in A_{1}\times\dots\times A_{m})=\displaystyle\sum_{\underline{x}\in(A_{1}\times\dots\times A_{m})\cap \delta_{\underline{X}}}P_{\underline{X}}(\underline{x}) \\
 & =\displaystyle\sum_{\underline{x}\in(A_{1}\times\dots\times A_{m})\cap \delta_{\underline{X}}}P_{X_{1}}(x_{1})\cdot\dots\cdot P_{X_{m}}(x_{m}) \\
 & \overset{(\star)}{=}\underset{=P(X_{1}\in A_{1})}{\underbrace{\displaystyle\sum_{x_{1}\in A_{1}\cap \delta_{X_{1}}}P_{X_{1}}(x_{1})}}\cdot\ \dots\ \cdot\underset{=P(X_{m}\in A_{m})}{\underbrace{\displaystyle\sum_{x_{m}\in A_{m}\cap \delta_{X_{m}}}P_{X_{m}}(x_{m})}}
\end{array}$$dove in $(\star)$ si è usato che, sotto queste ipotesi, si può supporre $\delta_{\underline{X}}=\delta_{X_{1}}\times\dots\times \delta_{X_{m}}$ (e quindi la somma sul prodotto cartesiano si fattorizza). Questa è l'uguaglianza che volevamo per dire che $X_{1},\dots,X_{m}$ è una famiglia di v.a. discrete indipendenti $\Box$
> [!warning] Come si usa in pratica
> Per stabilire se c'è indipendenza si verifica la condizione $P_{\underline{X}}(x_{1},x_{2})=P_{X_{1}}(x_{1})P_{X_{2}}(x_{2})$ solo sui punti del supporto: in tutti gli altri casi si ha $0=0\cdot 0$ e la condizione è automaticamente verificata.
> In generale, **se c'è una sola coppia per cui non vale l'uguaglianza richiesta, allora non c'è indipendenza**.

### Commento generale (criterio del prodotto cartesiano)
Se l'insieme $\{(x_{1},\dots,x_{m}):P_{\underline{X}}(x_{1},\dots,x_{m})>0\}$ **non** è un prodotto cartesiano, allora **non** c'è indipendenza.
In generale non vale il viceversa: cioè è possibile costruire esempi in cui non c'è indipendenza ma quell'insieme è un prodotto cartesiano.
> [!info] Perché il criterio funziona
> Se manca un "punto" per completare il prodotto cartesiano, in quel punto si ha $P_{\underline{X}}(\underline{x})=0$ mentre il prodotto delle marginali è $\neq 0$ (perché ciascun fattore è $\neq 0$): la condizione di indipendenza è quindi violata proprio lì.

#### Esempio (il viceversa non vale)
Presi $a,b\in \mathbb{R}$ con $a<b$, sia $$P_{\underline{X}}(a,a)=P_{\underline{X}}(b,b)=\frac{1}{3}\quad\quad P_{\underline{X}}(a,b)=P_{\underline{X}}(b,a)=\frac{1}{6}$$(è ben posta). Le marginali di $X_{1}$ e $X_{2}$ sono $$\begin{array}{l|l}
P_{X_{1}}(a)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} & P_{X_{2}}(a)=\frac{1}{3}+\frac{1}{6}=\frac{1}{2} \\
P_{X_{1}}(b)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2} & P_{X_{2}}(b)=\frac{1}{6}+\frac{1}{3}=\frac{1}{2}
\end{array}$$Qui l'insieme dove la congiunta è positiva **è** il prodotto cartesiano $\{a,b\}\times\{a,b\}$; tuttavia osserviamo che $$\underset{=1/3}{\underbrace{P_{\underline{X}}(a,a)}}\neq\underset{=\frac{1}{2}\cdot \frac{1}{2}=1/4}{\underbrace{P_{X_{1}}(a)P_{X_{2}}(a)}}$$Quindi $X_{1}$ e $X_{2}$ **non** sono indipendenti.
> [!info] Esercizi della lezione 10
> Le pp. 10-13 e 16-23 della lezione 10 contengono esercizi su densità congiunte discrete, marginali e verifica dell'indipendenza (fra cui l'urna con le palline $0,1,1,2$ e una congiunta di tipo geometrico). Sono esercizi puri: la loro sede è la cartella `Esercizi/`.

--- Fine lezione 10 ---

---
Nota precedente: [[Distribuzione binomiale negativa]]. Nota successiva: [[Trasformazioni e somme di variabili aleatorie discrete]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
