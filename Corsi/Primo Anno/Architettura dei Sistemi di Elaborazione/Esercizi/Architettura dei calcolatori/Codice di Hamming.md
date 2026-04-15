Il codice di Hamming viene usato per trovare un errore nel massaggio mandato da un mittente $W$ ad un destinatario che riceve $R$.

Per trasferire una parola di $m$ bit e $n$ bit di controllo deve valere la relazione $m+n+1\leq 2^n$.

Quindi con una parola lunga 8 bit, sono necessari 4 bit di controllo ($b_{3},b_{2},b_{1},b_{0}$) con un totale di 12 bit trasferiti. I bit di controllo ($b_{3},b_{2},b_{1},b_{0}$) si trovano nella posizione $2^i$.
![[controllo_hamming.png|400]]

Per esempio volendo trasmettere $W=F5_{H}$, ovvero $11110101_{2}$ verrà calcolato così:
![[Es_Hamming_1.png|400]]
$$\begin{array}{clc}
b_{0}= & 1\oplus 1\oplus 0\oplus 0\oplus 1 & =1\\
b_{1}= & 1\oplus 1\oplus 0\oplus 1\oplus 1 & =0\\
b_{2}= & 1\oplus 0\oplus 1\oplus 0 & =0\\
b_{3}= & 1\oplus 1\oplus 1\oplus 1 & =0
\end{array}$$
che inserito nella parola da mandare sarà:
![[Es_Hamming_2.png|400]]

Supponendo che ora avvenga un errore nella trasmissione del messaggio e che il bit in posizione 3 arrivi alterato, ovvero
![[Es_Hamming_3.png|400]]
$$\begin{array}{clc}
\hat{b_{0}}= & 1\oplus 1\oplus 0\oplus 0\oplus 0\oplus 1 & =1\\
\hat{b_{1}}= & 1\oplus 1\oplus 0\oplus 1\oplus 0\oplus 0 & =1\\
\hat{b_{2}}= & 1\oplus 0\oplus 1\oplus 0\oplus 0 & =0\\
\hat{b_{3}}= & 1\oplus 1\oplus 1\oplus 1\oplus 0 & =0
\end{array}$$
Poiché il valore non è 0 sappiamo che è avvenuto un errore, in particolare, convertendo il numero ($0011_{2}$) in decimale, otteniamo la posizione in cui si trova l'errore, quindi 3 e sappiamo come correggere il messaggio.