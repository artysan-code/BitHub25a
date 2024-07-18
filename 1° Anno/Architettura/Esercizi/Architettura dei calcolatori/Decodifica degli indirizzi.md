Disponendo un calcolatore che presenta la seguente architettura:
1. Una CPU dotata dei seguenti segnali:
	1. 16 bit indirizzamento ($A_{0}\div A_{15}$)
	2. 8 bus dati ($D_{0}\div D_{7}$)
	3. 1 bit controllo per accesso in memoria ($\overline{MREQ}$)
	4. 1 bit controllo per accesso su I/O ($\overline{IOREQ}$)
	5. 1 bit controllo per operazioni di lettura ($\overline{RD}$)
	6. 1 bit controllo per operazioni di scrittura ($\overline{WR}$)
2. una ROM da 16 KB per parole di 1 byte
3. una RAM da 8 KB per parole di 1 byte
4. l'interfaccia programmabile intel 8255A (Parallel I/O)

Supponendo che la ROM cominci dall'indirizzo $8000_{H}$, la RAM nella successiva locazione libera e di interfacciare l'8255A in modalità memory mapped dall'indirizzo $FF00_{H}$.

La memoria ROM è da 16 KB quindi, grazie alla formula otteniamo che:$$\begin{array}{}
2^n\cdot p \\ \\
16\cdot 2^{10}=2^n\cdot1 \\
2^4\cdot2^{10}=2^n \\
2^{14}=2^n \\
\implies n=14
\end{array}$$Visto che inizia dall'indirizzo $8000_{H}$, il suo spazio di indirizzamento sarà: 
![[Es_indirizzi_1.png|400]]
Quindi occupa la memoria $8000_{H}\div BFFF_{H}$ e se deve essere effettuato un accesso in memoria verrà asserito : $\overline{\overline{MREQ}\cdot A_{15}\cdot \overline{A_{14}}}$.

Dovendo la RAM collocarsi subito dopo essa comincerà da $C000_{H}$. La sua dimensione è do 8 KB, seguendo sempre la formula $2^n\cdot p$ essa ha $n=13$, ed il suo spazio di indirizzamento sarà:
![[Es_indirizzi_2.png|400]]
Quindi occupa la memoria $C000_{H}\div DFFF_{H}$ e se deve essere effettuato un accesso in memoria verrà asserito : $\overline{\overline{MREQ}\cdot A_{15}\cdot A_{14}\cdot \overline{A_{13}}}$.

L'Intel 8255A (24 pin, 3 porte da 8 bit) memory-mapped ha 3 modi di funzionamento:
0. le porte A e B possono essere programmate in modalità di ingresso o di uscita, la porta C può essere suddivisa in due sottoporte da 4 bit  e programmate in ingresso o uscita.
1. le porte A e B possono essere programmate in modalità di ingresso o di uscita, la porta C è sacrificata per fornire ad ogni porta 3 bit per l'handshaking e un segnale di controllo degli interrupt.
2. la porta A può essere una porta bidirezionale e la porta B sia in modo 0 che in modo 1. La porta C è sacrificata per fornire alla porta A 5 bit di handshake per il trasferimento dei dati, mentre i restanti 3 bit possono essere utilizzati come I/O diretto o handshake della porta B.

Nel modo 0 l'interfaccia può essere considerata come un registro a quattro porte, 3 per i dati e una di controllo. In questo caso per l'indirizzamento sono necessarie 4 locazioni, quindi:
   ![[Es_indirizzi_3.png|400]]
   Quindi nell'intervallo $FF00_{H}\div FF03_{H}$ e sarà abilitato con $\overline{\overline{MREQ}A_{15}A_{14}A_{13}A_{12}A_{11}A_{10}A_{9}A_{8}\overline{A_{7}}\ \overline{A_{6}}\ \overline{A_{5}}\ \overline{A_{4}}\ \overline{A_{3}}\ \overline{A_{2}}}$