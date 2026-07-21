# Indipendenza e covarianza
Legame tra indipendenza e covarianza nulla: l'implicazione vale in un verso solo, con un controesempio per il verso opposto.
## Proposizione (indipendenza $\implies$ covarianza nulla)
Siano $X_{1}$ e $X_{2}$ due v.a. definite su uno stesso spazio di probabilità, con medie finite e non necessariamente discrete. Allora $$\begin{bmatrix}
X_{1}\text{ e }X_{2}\text{ indipendenti}\implies \text{Cov}(X_{1},X_{2})=0
\end{bmatrix}$$
### Dimostrazione
Segue da una cosa detta in passato, cioè $$X_{1}\text{ e }X_{2}\text{ indipendenti}\implies \mathbb{E}[X_{1}X_{2}]=\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$$e dalla [[Covarianza di variabili aleatorie discrete#1) Formula alternativa: $\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]$|formula alternativa della covarianza]] $$\text{Cov}(X_{1},X_{2})=\mathbb{E}[X_{1}X_{2}]-\mathbb{E}[X_{1}]\mathbb{E}[X_{2}]=0\qquad\Box$$
## Conseguenza (varianza di una somma di v.a. indipendenti)
Se $X_{1},\dots,X_{m}$ sono **indipendenti**, allora nella [[Covarianza di variabili aleatorie discrete#Varianza di una somma e introduzione alla covarianza|formula generale per la varianza di una somma]] tutti i termini $\text{Cov}(X_{i},X_{j})$ (con $i<j$) si annullano, e quindi $$\begin{bmatrix}
\text{Var}[X_{1}+\dots+X_{m}]=\sum_{i=1}^{m}\text{Var}[X_{i}]+2\underset{i<j}{\sum_{i,j=1}^{m}}\underset{=0}{\underbrace{\text{Cov}(X_{i},X_{j})}}=\sum_{i=1}^{m}\text{Var}[X_{i}]
\end{bmatrix}$$
## Il viceversa è falso: $\text{Cov}=0\ \not\Rightarrow\ $ indipendenza
Presentiamo una classe di controesempi (ce ne sono anche altri) per cui $$\text{Cov}(X_{1},X_{2})=0\quad\not\Rightarrow\quad X_{1}\text{ e }X_{2}\text{ sono indipendenti}$$Consideriamo $$X_{1}=X\qquad\text{e}\qquad X_{2}=X^{2}$$dove $X$ è una v.a. tale che:
- $X$ è una v.a. **simmetrica** (cioè tale che $X$ e $-X$ sono equidistribuite; se $X$ è discreta, $X$ e $-X$ hanno la stessa densità discreta);
- $X^{2}$ ha speranza matematica finita;
- $X^{2}$ **non** è una v.a. costante (infatti si può dimostrare che ogni v.a. costante è indipendente da qualunque altra v.a.).

### I momenti dispari di una v.a. simmetrica sono nulli
Se $X$ è simmetrica si ha $\mathbb{E}[X^{k}]=0$ per ogni $k$ intero **dispari**. Infatti $$\mathbb{E}[X^{k}]=\sum_{x_{h}\in \delta_{X}}x_{h}^{k}P_{X}(x_{h})=0\quad\text{perché:}$$
- se si ha $x_{h}=0$, l'addendo $x_{h}^{k}P_{X}(x_{h})=0^{k}\cdot P_{X}(0)=0$;
- se si ha l'addendo $x_{h}^{k}P_{X}(x_{h})$ con $x_{h}>0$, c'è anche l'addendo con il suo opposto $\underset{=-x_{h}^{k}\ (k\text{ dispari})}{\underbrace{(-x_{h})^{k}}}\underset{=P_{X}(x_{h})\ (\text{simmetria})}{\underbrace{P_{X}(-x_{h})}}=-x_{h}^{k}P_{X}(x_{h})$ e quindi si semplifica con $x_{h}^{k}P_{X}(x_{h})$.

### La covarianza è nulla
$$\text{Cov}(X_{1},X_{2})=\text{Cov}(X,X^{2})=\underset{=\mathbb{E}[X^{3}]=0}{\underbrace{\mathbb{E}[X\cdot X^{2}]}}-\underset{=0}{\underbrace{\mathbb{E}[X]}}\ \mathbb{E}[X^{2}]=0$$dove $\mathbb{E}[X^{3}]=0$ e $\mathbb{E}[X]=0$ perché $3$ e $1$ sono dispari (momenti dispari nulli).
### Ma $X$ e $X^{2}$ non sono indipendenti
Basta trovare $x_{1},x_{2}$ tali che $P_{\underline{X}}(x_{1},x_{2})\neq P_{X_{1}}(x_{1})P_{X_{2}}(x_{2})$. Prendiamo $x\in \delta_{X}$ con $P_{X}(x)>0$. Poiché $$\{X^{2}=x^{2}\}=\{X=x\}\cup\{X=-x\}\implies\{X=x\}\subseteq\{X^{2}=x^{2}\}$$per il primo membro si ha $$P_{X,X^{2}}(x,x^{2})=P(\{X=x\}\cap\{X^{2}=x^{2}\})=P(X=x)=P_{X}(x)\qquad(\ast)$$Allora, se $(\ast)$ fosse un caso di indipendenza, si avrebbe $P_{X}(x)=P_{X}(x)P_{X^{2}}(x^{2})$, e quindi $P_{X^{2}}(x^{2})=1$. Ma questo è impossibile, perché significherebbe che $X^{2}$ è una v.a. costante uguale a $x^{2}$. Quindi $X$ e $X^{2}$ **non** sono indipendenti.
### Esempio numerico
Sia $X$ tale che $$P_{X}(2)=P_{X}(-2)=\frac{1}{10},\quad P_{X}(1)=P_{X}(-1)=\frac{3}{10},\quad P_{X}(0)=\frac{2}{10}$$($X$ è effettivamente simmetrica). La densità di $X^{2}$ è $$P_{X^{2}}(4)=P_{X}(2)+P_{X}(-2)=\frac{2}{10}=\frac{1}{5},\quad P_{X^{2}}(1)=P_{X}(1)+P_{X}(-1)=\frac{6}{10}=\frac{3}{5},\quad P_{X^{2}}(0)=P_{X}(0)=\frac{2}{10}=\frac{1}{5}$$(la somma fa 1). In generale, per $k$ dispari, il momento $k$-esimo è nullo: $$\mathbb{E}[X^{k}]=(-2)^{k}\cdot \frac{1}{10}+(-1)^{k}\cdot \frac{3}{10}+\underset{=0}{\underbrace{0\cdot \frac{2}{10}}}+1^{k}\cdot \frac{3}{10}+2^{k}\cdot \frac{1}{10}=-2^{k}\cdot \frac{1}{10}-\frac{3}{10}+0+\frac{3}{10}+2^{k}\cdot \frac{1}{10}=0$$In particolare $\mathbb{E}[X]=0$ e $\mathbb{E}[X^{3}]=0$, mentre $\mathbb{E}[X^{2}]=0\cdot \frac{1}{5}+1\cdot \frac{3}{5}+4\cdot \frac{1}{5}=\frac{7}{5}$. Quindi $$\text{Cov}(X,X^{2})=\underset{=\mathbb{E}[X^{3}]=0}{\underbrace{\mathbb{E}[X\cdot X^{2}]}}-\underset{=0}{\underbrace{\mathbb{E}[X]}}\ \mathbb{E}[X^{2}]=0$$Verifichiamo che **non** c'è indipendenza, ad esempio con la coppia $(2,4)$: $$P_{X,X^{2}}(2,4)=P(\{X=2\}\cap\{X^{2}=4\})=P(X=2)=\frac{1}{10}$$mentre $$P_{X}(2)\cdot P_{X^{2}}(4)=\frac{1}{10}\left( \frac{1}{10}+\frac{1}{10} \right)=\frac{1}{10}\cdot \frac{2}{10}=\frac{2}{100}\neq \frac{1}{10}$$Sono diversi, e questo basta. (Si può verificare anche con una coppia diversa da $(2,4)$: ad esempio $P_{X,X^{2}}(0,0)\neq P_{X}(0)P_{X^{2}}(0)$.)

--- Fine parte su indipendenza e covarianza (lezione 14, pp. 1-6) ---

---
Nota precedente: [[Covarianza di variabili aleatorie discrete]]. Nota successiva: [[Varianza delle distribuzioni discrete notevoli]]. Indice del blocco: [[Speranza matematica e momenti]].
