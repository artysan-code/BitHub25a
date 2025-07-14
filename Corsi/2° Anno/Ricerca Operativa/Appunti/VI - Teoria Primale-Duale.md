
Tabelle da memorizzare per i passaggi dell'esercizio:

|           |    da Min     |     a Max     |           |
| --------: | :-----------: | :-----------: | --------- |
|           |    Primale    |     Duale     |           |
|   Vincoli | $\geq,\leq,=$ | $\geq,\leq,=$ | Variabili |
| Variabili | $\geq,\leq,=$ | $\leq,\geq,=$ | Vincoli   |

|           |    da Max     |     a Min     |           |
| --------: | :-----------: | :-----------: | :-------- |
|           |    Primale    |     Duale     |           |
|   Vincoli | $\geq,\leq,=$ | $\leq,\geq,=$ | Variabili |
| Variabili | $\geq,\leq,=$ | $\geq,\leq,=$ | Vincoli   |

Esempio$$\begin{matrix}{}
\underset{x}{min}\quad 12x_{1}+2x_{2}+x_{3} \\
\quad \text{vincoli}\begin{cases}
x_{1} & +2x_{2} & -x_{3} & \geq & 10 \\
x_{1} &  & +x_{3} & = & 1 \\
 & x_{2} & +x_{3} & \leq & 7
\end{cases} \\
\text{variabili}\begin{cases}
x_{1}\geq 0,\quad x_{2}\leq 0,\quad x_{3}=0
\end{cases}
\end{matrix}\implies
\begin{matrix}{}
\underset{u}{max}\quad 10u_{1}+u_{2}+7u_{3} \\
\quad\begin{cases}
u_{1} & +u_{2}  & & \leq & 12 \\
2u_{1} &  & +u_{3} & \geq & 2 \\
-u_{1} & +u_{2} & +u_{3} & = & 1
\end{cases} \\
u_{1}\geq 0,\quad u_{2}=\leq= 0,\quad u_{3}\leq0
\end{matrix}$$
Spiegazione dei passaggi:
- passiamo da un esercizio di $min$ ad uno di $max$

- i coefficienti di $10u_{1}+u_{2}+7u_{3}$ derivano dai valori noti dei vincoli $(10,1,7)$

- $u_{1} +u_{2}$ deriva dalle righe (mantenendo i coefficienti) su cui è presente $x_{1}$
- $2u_{1}+u_{3}$ deriva dalle righe (mantenendo i coefficienti) su cui è presente $x_{2}$
- $-u_{1}+u_{2}+u_{3}$ deriva dalle righe (mantenendo i coefficienti) su cui è presente $x_{3}$

- il verso dei vincoli nel Duale derivano (seguendo la tabella) dalle variabili del Primale $$x_{1}\geq 0,x_{2}\leq 0,x_{3}=0 \implies \begin{cases}
\text{vincolo duale}_{1} \leq \dots\\
\text{vincolo duale}_{2} \geq \dots\\
\text{vincolo duale}_{3} = \dots
\end{cases}$$
- il verso delle variabili nel duale derivano (seguendo la tabella) dai vincoli del primale $$\begin{cases}
\text{vincolo primale}_{1} \geq \dots\\
\text{vincolo primale}_{2} = \dots\\
\text{vincolo primale}_{3} \leq \dots
\end{cases}\implies u_{1}\geq 0,\ u_{2}=\leq= 0,\ u_{3}\leq0 $$
- i valori noti del duale derivano dai coefficienti dell'esercizio di $min$ $$12x_{1}+2x_{2}+x_{3}\implies\begin{cases}
\dots\leq 12 \\
\dots\geq 2 \\
\dots = 1
\end{cases}$$
