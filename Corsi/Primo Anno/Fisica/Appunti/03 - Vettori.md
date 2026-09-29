## Introduzione ai vettori

### Approccio algebrico

Un insieme $V$ è detto **Spazio vettoriale** sull'insieme $\mathbb{R}$ dei numeri reali, e i suoi elementi sono detti **vettori** se:
1) dati $\underline u,\ \underline v\in V$, esiste un operazione *somma*, indicata con $+$, tale che $\underline w=\underline u+\underline v\in V$
2) dati $\underline u\in V$ e $c\in \mathbb{R}$, esiste un operazione *prodotto di un vettore per uno scalare* tale che $\underline a=c\cdot \underline u\in V$
3) vale la proprietà associativa della somma; per ogni $\underline u,\ \underline v,\ \underline w\in V$ risulta $\underline u+(\underline v+\underline w)=(\underline u+\underline v)+\underline w$
4) in $V$ esiste l'*elemento neutro della somma*, indicato con $0$, tale che $\underline u+0=0+\underline u=\underline u$ per ogni $\underline u\in V$
5) per ogni $\underline v\in V$ esiste il *vettore opposto* di $\underline v$, indicato con $-\underline v$, tale che $\underline v+(-\underline v)=0$
6) vale la proprietà associativa del prodotto di un vettore per uno scalare: per ogni $a,b\in \mathbb{R}$ e per ogni $\underline v\in V$ risulta $a(b\underline v)=(ab)\underline v$
7) il numero reale 1 e' l'elemento neutro di un vettore per uno scalare: $1\cdot \underline v=\underline v$ per ogni $\underline v\in V$
8) vale la proprietà distributiva del prodotto tra vettore e scalare: $$\begin{array}{}
(a+b)\underline v=a\underline v+b\underline v \\
a(\underline u+\underline v)=a\underline u+a\underline v
\end{array}$$In algebra lineare un vettore viene rappresentato da una sequenza di $n$ numeri reali disposti in colonna: $$\underline v=\begin{pmatrix}
v_{1} \\
v_{2} \\
\vdots \\
v_{n}
\end{pmatrix}$$
Valgono le seguenti regole di calcolo:
a) dati $\underline u,\underline v$ vettori a $n$ componenti, anche $\underline w=\underline v+\underline u$ e' un vettore a $n$ componenti, e risulta $$\underline w=\begin{pmatrix}
v_{1}+u_{1} \\
v_{1}+u_{2} \\
\vdots \\
v_{n}+u_{n}
\end{pmatrix}$$b) dato $\underline v$ un vettore a $n$ componenti, e $c\in \mathbb{R}$, anche $\underline u=c\underline v$ e' un vettore a $n$ componenti e risulta:$$u=\begin{pmatrix}
u_{1} \\
u_{2} \\
\vdots \\
u_{n}
\end{pmatrix}=\begin{pmatrix}
cv_{1} \\
cv_{2} \\
\vdots \\
cv_{n}
\end{pmatrix}$$Tutti gli elementi che soddisfano le due proprietà enunciate costituiscono uno **spazio vettoriale** a $n$ dimensioni.
In fisica di base interessano i vettori a 2 o 3 componenti, perché possono essere associati a grandezze fisiche.

### Nomenclatura

**Grandezza scalare**: e' specificata da un unico valore reale con segno
**Grandezza vettoriale**: in 2 o 3 dimensioni, e' specificata da 3 proprietà:
- Modulo
- Direzione 
- Verso

### Simbologia

Simbologia per vettori in 2 o 3 dimensioni:
$\overrightarrow v$   vettore in 2 o 3 dimensioni
$|\ \overrightarrow v\ |$ modulo del vettore $\overrightarrow v$  (e' un numero con unita di misura)
Risulta $|\ \overrightarrow v\ |\geq 0$ ed e' una grandezza scalare $\geq 0$

La *direzione* di un vettore $\overrightarrow v$  e' la retta lungo la quale giace il vettore.
Il *verso* è l'orientamento del vettore lungo la retta che definisce la direzione.

*Attenzione*: rette parallele individuano una stessa direzione! 
## Operazioni di vettori
### Somma di vettori
Tramite la rappresentazione geometrica, $\overrightarrow w=\overrightarrow v_{1}+\overrightarrow v_{2}$

1) Regola del parallelogramma:
	Nota bene: le lunghezze delle frecce sono proporzionali ai moduli dei vettori corrispondenti
	![[Corsi/1° Anno/Fisica/Appunti/Assets/l31.png|300]]
	
2) Regola del triangolo:
	Rispetto al punto 1), il vettore $\overrightarrow v_{2}$ e' stato traslato parallelamente a se stesso in modo da far coincidere la "punta" di $\overrightarrow v{1}$ con la coda di $\overrightarrow v_{2}$
	![[Corsi/1° Anno/Fisica/Appunti/Assets/l32.png|300]]

Valgono le proprietà seguenti:
- *proprietà commutativa*: $\overrightarrow v_{1}+\overrightarrow v_{2}=\overrightarrow v_{2}+\overrightarrow v_{1}$
- *proprietà associativa*: $\overrightarrow v_{1}+(\overrightarrow v_{2}+\overrightarrow v_{3})=(\overrightarrow v_{1}+\overrightarrow v_{2})+\overrightarrow v_{3}$

Somma di più vettori:
$\overrightarrow w=\overrightarrow v_{1}+\overrightarrow v_{2}+\overrightarrow v_{3}+\overrightarrow v_{4}$
Applicando la regola 2) in "cascata", si vede agevolmente che il vettore somma $\overrightarrow w$  e' rappresentato dalla freccia che congiunge la "coda" del primo vettore con la "punta" dell'ultimo vettore della catena
![[Corsi/1° Anno/Fisica/Appunti/Assets/l33.png|300]]

### Opposto di un vettore
Il vettore $-\overrightarrow u$ e' il vettore che, sommato a $\overrightarrow u$ , fornisce come risultato il vettore nulla $\overrightarrow 0$ .
$\overrightarrow u$ e $-\overrightarrow u$ hanno lo stesso modulo ($|\ \overrightarrow u\ |=|\ -\overrightarrow u\ |$), stessa direzione, ma versi opposti.

### Sottrazione tra vettori

$\overrightarrow w=\overrightarrow v_{1}-\overrightarrow v_{2}=\overrightarrow v_{1}+(-\overrightarrow v_{2})$
Si calcola sommando il primo vettore e l'opposto del secondo vettore 
![[Corsi/1° Anno/Fisica/Appunti/Assets/l34.png|600]]
### Moltiplicazione di un vettore per uno scalare
$\overrightarrow w=c\ \overrightarrow v$  e' un vettore, e risulta $|\overrightarrow w|=|c|\cdot|\ \overrightarrow v\ |$ 
$\overrightarrow w$ ha lo stesso verso di $\overrightarrow v$ se $c>0$
$\overrightarrow w$ ha verso opposto di $\overrightarrow v$ se $c<0$

## Componenti di un vettore e versori

Molto spesso conviene introdurre un **sistema di coordinate cartesiane ortogonali** per eseguire calcoli con grandezze vettoriali nel piano o nello spazio.
Analizziamo in modo più specifico il caso di un vettore nel piano.
Per semplificare questo primo approccio, trasliamo il vettore $\overrightarrow v$ parallelamente a se stesso finché la "coda" della freccia coincide con l'origine del sistema di coordinate.
![[l35.png|500]]
Indichiamo con la lettera greca $\theta$ ("theta") l'angolo formato dal vettore con il semi asse positivo delle ascisse, misurando in senso antiorario a partire dal semiasse positivo delle ascisse. Le proiezioni ortogonali della "punta" della freccia sui due assi cartesiani individuano le **componenti** di $\overrightarrow v$ nel sistema di coordinate cartesiane considerato. Le componenti sono quantità algebriche con segno; cioè, sono grandezze scalari.
$\overrightarrow v$ nel 1° quadrante: $\displaystyle v_{x}>0,\quad v_{y}>0\quad;0<\theta<\frac{\pi}{2} rad$
$\overrightarrow v$ nel 2° quadrante: $\displaystyle v_{x}<0,\quad v_{y}>\frac{\pi}{2}rad\quad;0<\theta<\pi\ rad$
$\overrightarrow v$ nel 3° quadrante: $\displaystyle v_{x}<0,\quad v_{y}<0\quad;\pi\ rad<\theta< \frac{3}{2}\pi\ rad$
$\overrightarrow v$ nel 4° quadrante: $\displaystyle v_{x}>0,\quad v_{y}<0\quad; \frac{3}{2}\pi\ rad<\theta< 2\pi\ rad$