
Un fenomeno è detto "fenomeno aleatorio" se il suo esito è incerto.
L'insieme dei possibili esiti viene indicato con $\ohm$ 
$$\begin{array}{}
 & \nearrow \text{DISCRETO se }\ohm \text{ è finito o numerabile}\\
\text{fenomeno aleatorio} &  \\
 & \searrow\text{CONTINUO se }\ohm \text{ è più che numerabile}
\end{array}$$
In genere si introduce una "famiglia di eventi" $A$ che viene individuato da una famiglia di sottoinsiemi di $\ohm$

Si vuole fare riferimento a "famiglie di eventi con buone probabilità" si intende che, facendo operazioni insiemistiche in elementi di $A$, si ottiene ancora un elemento di $A$

## Definizione ($\delta$-algebra)

Sia $\ohm$ un insieme non vuoto e sia $A\subset P(\ohm)$ 
Allora A è una 
1) $\ohm\in A$
2) $\forall A\in A\implies A^c\in A$ ^96616b
3) $\forall\{a_{n}\}_{n\geq1}\subset A\implies\underset{n\geq 1}{\bigcup}A_{n}\in A$

$P(\ohm)$ = insieme delle parti di $\ohm$
### Osservazione

Si vede facilmente che anche $\varnothing\in A$ e che $\underset{n\geq 1}{\bigcap}A_{n}\in A$ nella $3)$ 
### Osservazione

La richiesta della numerabilità viene fatta per semplificare alcune cose successivamente (non trattato nel corso)

### Osservazione

Si può prendere $A=P(\ohm)$
Questa scelta da altri problemi se $\ohm$ è più che numerabile (non trattato nel corso)
Per questo motivo il caso di $\ohm$ DISCRETO viene trattato più diffusamente nel corso.


## Definizione (Misure di Probabilità)

Sia $\ohm$ un insieme non vuoto e $A$ una $\delta$-algebra di eventi allora una funzione $P;[0,\infty)$ è una misura di probabilità se:
1) $P(\ohm)=1$
2) $\forall\{A_{n}\}_{n\geq 1}\subset A$ t.c. $$\begin{matrix}
{\left[\begin{array}{}
A_{m}\cap A_{n}=\varnothing \\
\text{per } m\not=n
\end{array}\right]} \\
\text{disgiunti a due a due}
\end{matrix}$$
 si ha $P\left(\underset{n\geq 1}{\bigcup}A_{n}\right)=\displaystyle\sum_{n\geq 1}P(A_{n})$ 

la terna $(\ohm, A, P)$ è detta spazio di probabilità

#### Commenti
- La misura di probabilità $P:A\to[0,\infty)$ in realtà assume valori in $[0,1]$ 
- La richiesta $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$, cioè "insiemi distinguibili a due a due", è più forte della condizione $\underset{n\geq 1}{\bigcup}A_{n}=\varnothing$
  Per fissare le idee consideriamo una famiglia di 3 insiemi $A,B,C$ allora in questo caso 
$$\begin{array}{}
insert & A\ \cap\ B=\varnothing \\
image & A\ \cap\ C=\varnothing & A\ \cap\ B\ \cap\ C=\varnothing \\
here & B\ \cap\ C=\varnothing
\end{array}$$
## Conseguenze della Definizione di Misura di Probabilità

1) $P(\varnothing)=0$
   infatti se consideriamo $A_{n}=\varnothing\quad\forall\ n\geq 1$,si ha $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$ o $m=n$  da cui segue $$\begin{cases}
  P\left(\right)\underset{n\geq 1}{\bigcup}A_{n}=P(\underset{n\geq 1}{\cup})=P(\varnothing) \\
 \displaystyle\sum_{n\geq 1}P(A_{n})
\end{cases}\implies P(\varnothing)=\sum_{n\geq 1}P(\varnothing)$$Questa condizione non può essere vera se $P(\varnothing)>0$; infatti il secondo membro sarebbe infinito ( e il primo finito).

2) Sia $h\geq 1$ intero e $B_{1},\dots,B_{h}\in A$ con $B_{m}\cap B_{n}=\varnothing$ per $m\not=n$ allora $P(\overset{h}{\underset{n=1}{\cup}}B_{n})=\displaystyle\sum_{n=1}^{h}P(B_{n})$.
   Infatti basta fare riferimento alla condizione [[#^96616b|ii)]] nella definizione con $A_{1}=B_{1},\dots,A_{h}=B_{h},A_{h+1}=B_{h+1}=\varnothing$. 
   Infatti con queste scelte (e per ipotesi), si ha $A_{m}\cap A_{n}=\varnothing$ per $m\not=n$ e si ha $P(\underset{n\geq1}{\cup}A_{n})=\displaystyle\sum_{n\geq 1}P(A_{n})$ da cui segue: $$\begin{cases}
\underset{n\geq 1}{\cup}A_{n}=B_{1}\cup\dots \cup B_{h}\cup\varnothing\cup \varnothing\cup\varnothing\dots= \overset{h}{\underset{n= 1}{\cup}B_{n}}\implies P(\underset{n\geq 1}{\cup}A_{n})=P(\overset{h}{\underset{n= 1}{\cup}}B_{n}) \\ \\
\displaystyle\sum_{n\geq 1}P(A_{n})=P(B_{1})+\dots+P(B_{h})+P(\varnothing)+\dots=\sum_{n=1}^{h}P(B_{n})
\end{cases}$$e quindi si ottiene $P(\overset{h}{\underset{n= 1}{\cup}}B_{n})=\displaystyle\sum_{n=1}^{h}P(B_{n})$
 ^95909c
3) Specializziamo l'uguaglianza appena verificata prendendo $E,F\in A,h=2$,$B_{1}=E\cap F$,$B_{2}=E\cap F^{c}$. Allora $$\begin{array}{l}
\underline{P((E\cap F)\cup(E\cap F^{c}))}=P(E\cap F)+P(E\cap F^{c})\implies P(E)=P(E\cap F)+P(E\cap F^{c}) \\
\quad\quad\Downarrow \\
=P(E)
\end{array}$$
3) .1 
   con $E=\ohm$
   $1=P(F)+P(F^c)\quad\forall\ F\in A$
   quindi  $$\begin{cases}
P(F)=1-P(F^{c}) \\
P(F^{c})=1-P(F)
\end{cases}$$
3) .2 
   con $F\subset E\quad(E\cap F=F)$
   quindi 
   $P(E)=P(F)+\underset{\geq 0}{\underbrace{P(E\cap F^{c})}}\geq P(F)\implies P(E)\geq P(F)$
   da questo segue che $P(A)\leq P(\ohm)=1\quad\forall\ A\in A$

3) .3
   Specializzando la formula al punto [[#^95909c|2)]] con $E,F\in A,h=3$,$B_{1}=E\cap F^{c},B_{2}=E\cap F,B_{3}=F\cap E^{c}$
   ovviamente $B_{1}\cup B_{2}\cup B_{3}=E\cup F$ e quindi $$\begin{array}{l}
P(E\cup F)=P(B_{1})+P(B_{2})+P(B_{3})= \\
\quad\quad\quad\quad\ =P(E\cap F^{c})+P(E\cap F)+P(F\cap E^{c})= \\
=\underset{=P(E)}{\underbrace{P(E\cap F^{c})+P(E\cap F)}}+\underset{=P(F)}{\underbrace{P(F\cap E^{c})+P(E\cap F)}}-P(E\cap F) \\
\implies P(E\cup F)=P(E)+P(F)-P(E\cap F)
\end{array}$$ ^813f60
### Osservazione
L'uguaglianza ottenuta ha un'interpretazione naturale.
Prendendo $P(E)+P(F)$ si ha che $P(E\cap F)$ viene "presi due volte" e quindi dobbiamo sottrarre la stessa quantità.
Se $E\cap F=\varnothing$ ritroviamo la [[#^95909c|2)]] con $h=2,B_{1}=E,B_{2}=F$.

La formula ottenuta nella [[#^813f60|3).3]] si estende al caso di più di due eventi (**Identità di Bonferroni**).
Qui richiamo quella per $n=3$; $\quad\forall\ E,F,G\in A$
$P(E\cup F\cup G)=P(E)+P(F)+P(G)-P(E\cap F)-P(E\cap G)-P(F\cap G)+P(E\cap F\cap G)$
### Commento generale
Le proprietà della misura di probabilità sono svincolate dalla costruzione del modello, e quindi da come si definisce la misura di probabilità in questione per descrivere il fenomeno aleatorio (tale definizione può dipendere dallo stato di conoscenza dell'osservatore).