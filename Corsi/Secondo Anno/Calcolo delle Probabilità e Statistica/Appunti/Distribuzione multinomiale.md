# Distribuzione multinomiale
Generalizzazione della binomiale a $r$ risultati possibili per prova, e coefficiente multinomiale.
### Distribuzione multinomiale
Consideriamo $n$ prove indipendenti. Per ogni prova abbiamo $r$ risultati possibili: $$\begin{cases}
\text{risultato }1 & \text{con probabilità }p_{1}\geq 0 \\
\quad\vdots &  \\
\text{risultato }r & \text{con probabilità }p_{r}\geq 0
\end{cases}$$I valori $p_{1},\dots,p_{r}$ sono gli stessi per ogni prova; inoltre $p_{1}+\dots+p_{r}=1$.
In generale saremo interessati a calcolare probabilità di questo tipo: $$P\begin{pmatrix}
k_{1}\text{ volte risultato }1 \\
\vdots \\
k_{r}\text{ volte risultato }r
\end{pmatrix}\quad\quad\text{dove }\begin{cases}
k_{1},\dots,k_{r}\geq 0\text{ interi} \\
k_{1}+\dots+k_{r}=n
\end{cases}$$
#### Osservazione
Se si ha $r=2$ si recupera il caso della [[Distribuzioni binomiale e ipergeometrica#Caso 1): distribuzione binomiale|binomiale]]; ad esempio risultato 1 $\longleftrightarrow$ successo ($p_{1}=p$) e risultato 2 $\longleftrightarrow$ fallimento ($p_{2}=1-p$), perché $p_{1}+p_{2}=1$.
Consideriamo la seguente sequenza di risultati: $$(\underset{k_{1}\text{ volte}}{\underbrace{R_{1},\dots,R_{1}}},\underset{k_{2}\text{ volte}}{\underbrace{R_{2},\dots,R_{2}}},\ \dots\ ,\underset{k_{r}\text{ volte}}{\underbrace{R_{r},\dots,R_{r}}})$$Allora, per indipendenza delle prove, questa sequenza ha probabilità $p_{1}^{k_{1}}\cdot\dots\cdot p_{r}^{k_{r}}$. Ovviamente si ottiene la stessa probabilità per qualsiasi altra sequenza con "$k_{1}$ volte $R_{1}$, …, $k_{r}$ volte $R_{r}$". Quindi la grandezza che vogliamo calcolare è $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
\vdots \\
k_{r}\text{ volte }R_{r}
\end{pmatrix}=\#\{\text{sequenze con "}k_{1}\text{ volte }R_{1},\dots,k_{r}\text{ volte }R_{r}\text{"}\}\cdot p_{1}^{k_{1}}\cdot\dots\cdot p_{r}^{k_{r}}$$e si può verificare che il numero di tali sequenze vale $$\begin{bmatrix}
\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}
\end{bmatrix}$$detto **coefficiente multinomiale** (per $r=2$ è un coefficiente binomiale).
#### Osservazione (risultati equiprobabili)
Se in ogni prova i risultati $R_{1},\dots,R_{r}$ sono equiprobabili, cioè $p_{1}=\dots=p_{r}=\frac{1}{r}$, si ha $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
\vdots \\
k_{r}\text{ volte }R_{r}
\end{pmatrix}=\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}\left( \frac{1}{r} \right)^{\overset{=n}{\overbrace{k_{1}+\dots+k_{r}}}}=\frac{n!}{k_{1}!\cdot\dots\cdot k_{r}!}\left( \frac{1}{r} \right)^{n}$$È l'analogo di quanto visto per $X\sim BIN\left( n,p=\frac{1}{2} \right)$, dove si ha $P_{X}(k)=\binom{n}{k}\left( \frac{1}{2} \right)^{n}$.
#### Osservazione (si recupera la binomiale)
Per $r=2$, usando $p_{1}=1-p_{2}$ (perché $p_{1}+p_{2}=1$) e $k_{2}=n-k_{1}$ (perché $k_{1}+k_{2}=n$), si ha $$P\begin{pmatrix}
k_{1}\text{ volte }R_{1} \\
k_{2}\text{ volte }R_{2}
\end{pmatrix}=\frac{n!}{k_{1}!(n-k_{1})!}p_{1}^{k_{1}}(1-p_{1})^{n-k_{1}}=\binom{n}{k_{1}}p_{1}^{k_{1}}(1-p_{1})^{n-k_{1}}\quad\quad(0\leq k_{1}\leq n)$$
### Esempio: urna con tre colori (con e senza reinserimento)
Un'urna contiene 3 palline bianche, 3 rosse e 2 nere. Si estraggono 4 palline a caso, una alla volta e **con** reinserimento. Calcolare le probabilità dei seguenti eventi:
1) viene estratta la sequenza di colori (rossa, nera, nera, bianca);
2) vengono estratte esattamente 2 palline rosse e 1 nera in qualsiasi ordine;
3) vengono estratte esattamente 2 palline rosse in un qualsiasi ordine.
> [!info] Convenzione del corso
> Negli esercizi generalmente si sottintendono "esattamente" e "in qualsiasi ordine".

**Svolgimento.** Si hanno prove indipendenti perché le estrazioni sono **con** reinserimento. In ogni prova abbiamo 3 risultati con probabilità $p_{B}=\frac{3}{8}$, $p_{R}=\frac{3}{8}$, $p_{N}=\frac{2}{8}$.
1) Con notazioni ovvie: $$P(R_{1}\cap N_{2}\cap N_{3}\cap B_{4})=P(R_{1})P(N_{2})P(N_{3})P(B_{4})=p_{B}p_{R}p_{N}^{2}=\frac{3}{8}\cdot \frac{3}{8}\left( \frac{2}{8} \right)^{2}=\frac{36}{4096}$$   **Osservazione.** L'espressione $p_{B}p_{R}p_{N}^{2}$ può essere vista come $p_{1}^{k_{1}}p_{2}^{k_{2}}p_{3}^{k_{3}}$ con $k_{1}=1,k_{2}=1,k_{3}=2$: abbiamo una parte della formula della multinomiale **senza** il coefficiente multinomiale (del resto è una sequenza fissata).
2) $$P(\text{"2R e 1N"})=P(\text{"1B, 2R, 1N"})=\underset{=\frac{4\cdot 3\cdot 2}{2}=12}{\underbrace{\frac{4!}{1!\,2!\,1!}}}\left( \frac{3}{8} \right)^{1}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{1}=\frac{648}{4096}$$(si sono estratte 4 palline: se 2 sono rosse e 1 nera, la quarta è necessariamente bianca).
3) Qui conviene contare solo "rosse" e "non rosse" (senza distinguere tra bianche e nere): il numero di rosse estratte è $\sim BIN\left( n=4,p=p_{R}=\frac{3}{8} \right)$, quindi $$P(\text{"2R"})=\binom{4}{2}\left( \frac{3}{8} \right)^{2}\left( 1-\frac{3}{8} \right)^{4-2}=6\left( \frac{3}{8} \right)^{2}\left( \frac{5}{8} \right)^{2}=\frac{1350}{4096}$$   **Osservazione.** Se volessimo tenere conto dei 3 colori si ha $$P(\text{"2R"})=P(\text{"2R, 1B, 1N"})+P(\text{"2R, 2B"})+P(\text{"2R, 2N"})=\frac{648+486+216}{4096}=\frac{1350}{4096}$$dove $P(\text{"2R, 2B"})=\frac{4!}{2!\,2!\,0!}\left( \frac{3}{8} \right)^{2}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{0}$ e $P(\text{"2R, 2N"})=\frac{4!}{0!\,2!\,2!}\left( \frac{3}{8} \right)^{0}\left( \frac{3}{8} \right)^{2}\left( \frac{2}{8} \right)^{2}$. Calcoli più complicati: metodo meno conveniente.
#### Lo stesso esercizio con estrazioni "senza reinserimento"
1) Qui non c'è indipendenza e si usa la [[Cap 2 - Introduzione alla probabilità#Regola del Prodotto|regola del prodotto]]: $$P(R_{1}\cap N_{2}\cap N_{3}\cap B_{4})=\underset{=\frac{3}{8}}{\underbrace{P(R_{1})}}\ \underset{=\frac{2}{7}}{\underbrace{P(N_{2}|R_{1})}}\ \underset{=\frac{1}{6}}{\underbrace{P(N_{3}|R_{1}\cap N_{2})}}\ \underset{=\frac{3}{5}}{\underbrace{P(B_{4}|R_{1}\cap N_{2}\cap N_{3})}}=\frac{3}{280}$$
2) Si usano le formule delle [[Cap 2 - Introduzione alla probabilità#Estensione al caso con più di 2 tipi|estrazioni in blocco con più di 2 tipi]]: $$P(\text{"2R e 1N"})=P(\text{"1B, 2R, 1N"})=\frac{\binom{3}{1}\binom{3}{2}\binom{2}{1}}{\binom{8}{4}}=\frac{3\cdot 3\cdot 2}{70}=\frac{18}{70}=\frac{9}{35}$$
3) Contando "rosse" e "non rosse": $$P(\text{"2R"})=\frac{\binom{3}{2}\binom{5}{2}}{\binom{8}{4}}=\frac{3\cdot 10}{70}=\frac{30}{70}=\frac{3}{7}$$e in effetti, distinguendo i tre colori, $$P(\text{"2R"})=\underset{=\frac{18}{70}}{\underbrace{P(\text{"2R, 1B, 1N"})}}+\underset{=\frac{\binom{3}{2}\binom{3}{2}\binom{2}{0}}{\binom{8}{4}}=\frac{9}{70}}{\underbrace{P(\text{"2R, 2B"})}}+\underset{=\frac{\binom{3}{0}\binom{3}{2}\binom{2}{2}}{\binom{8}{4}}=\frac{3}{70}}{\underbrace{P(\text{"2R, 2N"})}}=\frac{18+9+3}{70}=\frac{30}{70}=\frac{3}{7}$$
### Esempio: raggruppare i risultati (5 lanci di un dado)
Si lancia 5 volte un dado equo. Calcolare la probabilità che escano (esattamente) "2 volte $1$ e 1 volta $3$" (in un qualsiasi ordine).
**Risposta.** Abbiamo 5 prove indipendenti (i 5 lanci) e **3 risultati** in ogni prova: $$\begin{array}{lll}
\boxed{1} & \text{con prob. }p_{1}=\frac{1}{6} & (2\text{ volte}) \\
\boxed{3} & \text{con prob. }p_{2}=\frac{1}{6} & (1\text{ volta}) \\
\boxed{2}\ \boxed{4}\ \boxed{5}\ \boxed{6} & \text{con prob. }p_{3}=\frac{4}{6} & (2\text{ volte, dedotto})
\end{array}$$La probabilità richiesta è (applicazione diretta della formula della multinomiale) $$\frac{5!}{2!\,1!\,2!}\left( \frac{1}{6} \right)^{2}\left( \frac{1}{6} \right)^{1}\left( \frac{4}{6} \right)^{2}=\frac{5\cdot 4\cdot 3\cdot 2}{2\cdot 2}\cdot \frac{1}{6^{3}}\cdot \frac{4}{9}=\frac{5\cdot 4}{36\cdot 9}=\frac{5}{81}$$
#### Osservazione (modo alternativo, molto più complicato)
Pensiamo a 6 risultati possibili tutti con probabilità $\frac{1}{6}$. Abbiamo le due seguenti situazioni: $$\begin{array}{ll}
\text{per }k=2,4,5,6\ (4\text{ casi}) & P(\text{"2 volte }\boxed{1}\text{, 1 volta }\boxed{3}\text{, 2 volte }\boxed{k}\text{"})=\frac{5!}{2!\,1!\,2!\,0!\,0!\,0!}\left( \frac{1}{6} \right)^{5}=\frac{5}{1296} \\
\text{per }\{k,h\}\subset\{2,4,5,6\}\ \left( \binom{4}{2}=6\text{ casi} \right) & P(\text{"2 volte }\boxed{1}\text{, 1 volta }\boxed{3}\text{, 1 volta }\boxed{k}\text{, 1 volta }\boxed{h}\text{"})=\frac{5!}{2!\,1!\,1!\,1!\,0!\,0!}\left( \frac{1}{6} \right)^{5}=\frac{10}{1296}
\end{array}$$La probabilità richiesta è $$4\cdot \frac{5}{1296}+6\cdot \frac{10}{1296}=\frac{20+60}{1296}=\frac{80}{1296}=\frac{5}{81}$$che è lo stesso risultato visto prima.

---
Nota precedente: [[Distribuzioni binomiale e ipergeometrica]]. Nota successiva: [[Distribuzioni uniforme discreta e di Poisson]]. Indice del blocco: [[Cap 3 - Modelli Discreti]].
