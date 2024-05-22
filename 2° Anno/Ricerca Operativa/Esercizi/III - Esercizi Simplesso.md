# Esempio 1
Una ditta di profumi realizza due nuove fragranze a partire da 3 essenze: rosa, mughetto e viola. 

Per realizzare un decalitro di fragranza 1 sono richiesti 1,5 litri di rosa, 1 litro di mughetto e 0,3 litri di viola. 
Per realizzare un decalitro di fragranza 2 sono richiesti 1 litro di rosa, 1 litro di mughetto e 0,5 litri di viola. 

La disponibilità in magazzino per le tre essenze è di 27, 21 e 9 litri per rosa, mughetto e viola rispettivamente. 
Sapendo che l'azienda realizza un profitto di 130 e 100 euro per ogni decalitro venduto di fragranza 1 e 2 rispettivamente, determinare le quantità ottimali delle due fragranze da produrre.

Il problema sarà quindi:
$$\begin{array}{}
max & 130x_{1}+100x_{2} \\
 & 1.5x_{1}+x_{2}\leq 27 \\
 & x_{1}+x_{2}\leq 21 \\
 & 0.3x_{1}+0.5x_{2}\leq 9 \\
 & x_{1}\geq 0,x_{2}\geq 0
\end{array}$$
1) porto il problema in forma standard $$\begin{array}{}
min & -130x_{1}+100x_{2} \\
 & 1.5x_{1}+x_{2}\leq 27 \\
 & x_{1}+x_{2}\leq 21 \\
 & 0.3x_{1}+0.5x_{2}\leq 9 \\
 & x_{1}\geq 0,x_{2}\geq 0
\end{array}$$$$\begin{array}{l}
1° vincolo: \\
1.5x_{1}+x_{2}+s_{1}=27 \\ \\
2° vincolo:  \\
x_{1}+x_{2}+s_{2}=21 \\ \\
3° vincolo:  \\
0.3x_{1}+0.5x_{2}+s_{3}=9 \\
\end{array}$$$$\begin{matrix}{} 
min & - & 130x_{1} & + & 100x_{2} \\
 & 1.5x_{1} & + & x_{2} &  + & s_{1}  &  &  &  & & = & 27 \\
 & x_{1} & + & x_{2} &  &  & + & s_{2} & &  &  = & 21 \\
 & 0.3x_{1} & + & 0.5x_{2} &  &  &  &  & +  & s_{3} & = & 9 \\
 & x_{1}, & x_{2}, & s_{1}, & s_{2}, & s_{3} & \geq & 0
\end{matrix}$$
tableau del simplesso:
$$\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 0 & -130 & -100 & 0 & 0 & 0 \\
\hline
s_{1} & 27 & 1.5 & 1 & 1 & 0 & 0\\
\hline
s_{2} & 21 & 1 & 1 & 0 & 1 & 0\\
\hline
s_{3} & 9 & 0.3 & 0.5 & 0 & 0 & 1 \\
\end{array}$$
seleziono il pivot $(*)$ trovando quale è il $min\{\frac{b_{i}}{a_{i}}\}$ e lo porto a 0 effettuando la stessa operazione sulla sua riga
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 0 & -130 & -100 & 0 & 0 & 0 \\
\hline
s_{1} & 27 & (1.5) & 1 & 1 & 0 & 0\\
\hline
s_{2} & 21 & 1 & 1 & 0 & 1 & 0\\
\hline
s_{3} & 9 & 0.3 & 0.5 & 0 & 0 & 1 \\
\end{array}$$
modifico le altre righe in modo che sopra e sotto il pivot ho solamente il valore 0 e successivamente scelgo il prossimo pivot $(*)$
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 2340 & 0 & -\frac{40}{3} & \frac{260}{3} & 0 & 0  & =130*R_{2}+R_{1}\\
\hline
x_{1} & 18 & 1 & \frac{2}{3} & \frac{2}{3} & 0 & 0\\
\hline
s_{2} & 3 & 0 & (\frac{1}{3}) & -\frac{2}{3} & 1 & 0 & =-\frac{2}{3}R_{2}+R_{3}\\
\hline
s_{3} & 3.6 & 0 & 0.3 & 0.2 & 0 & 1 & =-0.3R_{3}+R_{4}
\end{array}$$
porto il nuovo pivot a 1 ed effettuo nuovamente l'azzeramento dei valori sopra e sotto del pivot con operazioni sulle loro righe
$$\Downarrow $$$$
\begin{array}{c|c}
 & b & x_{1} & x_{2} & s_{1} & s_{2} & s_{3}\\
\hline 
z & 2460 & 0 & 0 & 60 & 40 & 0  & =\frac{40}{3}R_{3}+R_{1}\\
\hline
x_{1} & 12 & 1 & 0 & 2 & -2 & 0 & =-\frac{2}{3}R_{3}+R_{2}\\
\hline
x_{2} & 9 & 0 & 1 & -2 & 3 & 0 \\
\hline
s_{3} & 0.9 & 0 & 0 & -0.4 & -0.9 & 1 & =-0.3R_{3}+R_{4}
\end{array}$$
la soluzione ottima quindi è:
$$\begin{array}{}
x_{1}=12 \\
x_{2}=9 \\
s_{1},s_{2}=0 \\
s_{3}=0.9 \\
z=2460 (\text{ valore ottimo del problema iniziale})
\end{array}$$

# Esempio 2


[[|Prossimo Argomento]]