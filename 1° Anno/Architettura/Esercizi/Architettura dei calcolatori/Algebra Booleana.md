## Tabella delle proprietà

|                          |                 Forma AND                 |                 Forma OR                  |
| :----------------------: | :---------------------------------------: | :---------------------------------------: |
|     Elemento neutro      |                  $1X=X$                   |                  $0+X=X$                  |
|       Assortimento       |                  $0X=0$                   |                  $1+X=1$                  |
|       Idempotenza        |                  $XX=X$                   |                  $X+X=X$                  |
|     Complementazione     |             $X\overline{X}=0$             |            $X+\overline{X}=1$             |
|  Proprietà commutativa   |                  $XY=YX$                  |                 $X+Y=Y+X$                 |
|  Proprietà associativa   |               $Z(XY)=X(YZ)$               |             $(X+Y)+Z=X+(Y+Z)$             |
|  Proprietà distributiva  |             $X+YZ=(X+Y)(X+Z)$             |              $X(Y+Z)=XY+XZ$               |
| 1° Legge di assorbimento |                $X(X+Y)=X$                 |                 $X+XY=X$                  |
| 2°Legge di assorbimento  |          $X(\overline{X}+Y)=XY$           |           $X+\overline{X}Y=X+Y$           |
|    Legge di De Morgan    | $\overline{XY}=\overline{X}+\overline{Y}$ | $\overline{X+Y}=\overline{X}\overline{Y}$ |

prendiamo per esempio il seguente esercizio da controllare l'uguaglianza: $$ 
\begin{array}{r l}
\overline{\overline{A}+\overline{A+CB}A}=A  & \text{Legge di De Morgan}\\
A(A+CB+\overline{A})=A  & \text{Complementazione}\\
A(CB+1)=A  & \text{Assortimento}\\
A(1)=A  & \text{Elemento neutro}\\
A=A
\end{array}$$