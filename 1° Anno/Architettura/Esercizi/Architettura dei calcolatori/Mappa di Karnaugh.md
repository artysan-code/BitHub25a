Avendo una formula booleana in forma canonica (DNF o CNF) possiamo utilizzare la mappa di Karnaugh per semplificare ulteriormente la formula. Prendiamo in considerazione la seguente formula $F=A\cdot B+\overline{A}\cdot C+\overline{B}\cdot\overline{C}$ la sua mappa verrà rappresentata con valori uno dove appunto avremo $A=1,B=1$ (gruppo giallo), dove $A=0,C=1$ (gruppo blu) e dove $B=0,C=0$ (gruppo rosso) quindi:

![[Karnaugh.png|300]]

dovendo raggruppare a gruppi di $2^n$ il più grandi possibile. 

Ecco un altro esempio con $I=\overline{A}\overline{B}+A\overline{B}+\overline{C}\overline{D}+C\overline{D}$ 

![[Es_Karnaugh_2.png|300]]
Dalla sua mappa capiamo che in realtà la formula può essere riscritta come $I=\overline{B}+\overline{D}$