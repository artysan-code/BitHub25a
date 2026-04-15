Il problema fornisce i seguenti dati:
- Memoria totale del sistema
- Memoria occupata dal sistema operativo
- Memoria occupata da un processo
- Tempo di attesa medio I/O in %

Il problema ci richiede invece, quale è il tempo di attesa medio della CPU.

Ora iniziamo a identificare i valori utili per la seguente formula:$$CPU_{load}=1-p^n$$

In questo contesto sottraiamo a 1 (che equivale al 100% di CPU utilizzabile) il carico $p^n$, dove $p$ corrisponde al tempo di attesa medio (in valore numerico, quindi 50% è 0.5) e invece $n$ sono il numero di processi massimi ottenibili nello spazio di memoria dato. Infatti lo calcoliamo con:$$n=\frac{M_{tot}-M_{os}}{M_{proc}}$$
Quindi sottraiamo alla memoria totale la memoria del sistema operativo per ottenere la **memoria libera** e infine la dividiamo per lo spazio di ogni processo per ottenere il **numero dei processi**.

Sostituisci la formula ed è fatto.