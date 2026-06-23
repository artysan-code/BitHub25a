# Tracce d'Esame Pratiche — Sistemi Operativi
> [!info] Attribuzione
> Tracce tratte dalla repository del collega Ionut Zbir — [github.com/IonutZbir/University](https://github.com/IonutZbir/University).
## Processi
Tutte le tracce usano [[03 - Processi e Thread#^fork|fork]] e **pipe anonime** POSIX (`pipe()`, `read()`, `write()`). Il pattern generale è: il padre crea le pipe *prima* del `fork`, i figli chiudono l'estremità che non usano, comunicano tramite le pipe, il padre raccoglie con `wait`/`waitpid`.
### P1 — Conteggio occorrenze (fork + pipe + file)
**Consegna.** Due figli leggono ciascuno una metà di un file (`stat` + `lseek`): figlio 1 dalla posizione $0$ alla metà, figlio 2 dalla metà alla fine. Ciascuno conta le occorrenze di una parola e invia il conteggio al padre tramite pipe separate. Il padre somma e stampa.
**Soluzione svolta:** `Processi/fork_seek_occurrences.c`
### P2 — Numeri pari/dispari [0–100], soglia 190
**Consegna.** Figlio 1 invia al padre numeri pari casuali in $[0, 100]$; figlio 2 invia numeri dispari casuali in $[0, 100]$. Il padre somma i valori ricevuti e, quando la somma supera $190$, invia [[03 - Processi e Thread#I segnali|SIGTERM]] ai figli con `kill()`.
**Traccia proposta** (nessuna soluzione svolta disponibile).
### P3 — Catena padre–figlio1–figlio2 (pipe bidirezionale)
**Consegna.** Figlio 1 genera un numero casuale e lo invia al padre tramite pipe. Il padre sceglie un fattore $k$ casuale, moltiplica e invia il risultato a figlio 2 tramite una seconda pipe. Figlio 2 stampa il valore ricevuto.
**Traccia proposta** (nessuna soluzione svolta disponibile).
### P4 — Lettura directory (dirent + readdir + permessi)
**Consegna.** Due figli leggono ciascuno metà dei file di una directory (usando `opendir`/`readdir` da `<dirent.h>`); prima di leggere ogni file controllano i permessi con `stat` ed eventualmente li modificano con `chmod`. Inviano il contenuto al padre nel formato `[PID_FIGLIO] -> TESTO`. Il padre stampa.
**Traccia proposta** (nessuna soluzione svolta disponibile).
### P5 — Moltiplicazione matrici 3×3 in parallelo
**Consegna.** Dati due array $M_1, M_2 \in \mathbb{R}^{3 \times 3}$, figlio 1 calcola la prima colonna di $M_1 \cdot M_2$, figlio 2 la seconda colonna; il padre calcola la terza colonna, riceve le colonne dai figli tramite pipe e compone e stampa la matrice risultante.
**Soluzione svolta:** `Processi/matrix_fork.c`
### P6 — Multipli di 3 e di 2, soglia 130
**Consegna.** Figlio 1 genera numeri casuali in $[0, 50]$ e invia al padre solo i **multipli di 3**; figlio 2 genera numeri casuali in $[50, 100]$ e invia al padre solo i **multipli di 2**. Il padre stampa i numeri ricevuti e somma la coppia ricevuta ad ogni iterazione; quando la somma $\geq 130$ invia [[03 - Processi e Thread#I segnali|SIGTERM]] ai figli.
**Soluzione svolta:** `Processi/fork_sum.c`
### P7 — Pipe bidirezionale padre–figlio (quadrato se pari)
**Consegna.** Il padre invia un numero al figlio tramite una pipe. Il figlio ne calcola il quadrato; se il quadrato è **pari** lo reinvia al padre tramite una seconda pipe (bidirezionale). Il padre stampa il risultato; se non riceve nulla (quadrato dispari) lo segnala.
**Traccia proposta** (nessuna soluzione svolta disponibile).
### P8 — Fusione array pari/dispari (max e min)
**Consegna.** Figlio 1 invia al padre gli elementi del proprio array nelle **posizioni pari**; figlio 2 invia quelli nelle **posizioni dispari**. Il padre riceve i valori, costruisce l'array fuso e calcola il **massimo** e il **minimo**.
**Traccia proposta** (nessuna soluzione svolta disponibile).
### P9 — Fork + file condiviso + lseek (pari e dispari)
**Consegna.** Figlio 1 scrive $N$ numeri pari in un file condiviso (usando `creat`). Figlio 2 aspetta la terminazione di figlio 1 (coordinazione via pipe), usa `lseek` per posizionarsi subito dopo la sequenza pari e scrive $N$ numeri dispari. Il padre attende figlio 2, apre il file in sola lettura e stampa l'intera sequenza.
**Soluzione svolta:** `Processi/fork_file_pari_dispari.c`
### P10 — I Appello 26/01/2024 — Buffer 11 celle (+1/−1)
**Consegna.** Il processo crea un **buffer** di $11$ interi inizializzati a $0$. Figlio 1 sceglie casualmente un indice e lo invia al padre tramite pipe; il padre scrive $+1$ in quella posizione. Figlio 2 fa lo stesso e il padre scrive $-1$. Dopo ogni coppia di scritture il padre controlla se ci sono ancora zeri nel buffer; quando non ve ne sono, conta gli $+1$ e i $-1$, stampa il risultato e invia [[03 - Processi e Thread#I segnali|SIGTERM]] ai figli.
**Soluzione svolta:** `Processi/26_01_24_appello.c`
## Thread — Mutex
Le tracce di questa sezione usano [[04 - Sincronizzazione#Mutex|pthread_mutex_t]] per la **mutua esclusione** e, dove necessario, [[04 - Sincronizzazione#Variabili condizionali (pthread_cond)|pthread_cond_t]] per la sincronizzazione condizionale. Tutti i thread sono creati con `pthread_create` e attesi con `pthread_join`.
### TM1 — Buffer 11 interi (+1/−1/controllo)
**Consegna.** Tre thread operano su un buffer di $11$ interi inizializzati a $0$:
- **Thread 1** — sceglie casualmente una cella e vi scrive $+1$.
- **Thread 2** — sceglie casualmente una cella e vi scrive $-1$.
- **Thread 3** — verifica se tutte le celle sono diverse da $0$; in caso affermativo confronta il numero di $+1$ con quello di $-1$, stampa il risultato e termina tutti i thread.
Un solo thread alla volta può accedere al buffer (mutex); dopo ogni accesso attende un tempo casuale in $[0, 3]$ secondi.
> [!warning] Nota sulla soluzione svolta
> La soluzione `pos_neg_one_thread_mutex.c` usa $N = 5$ celle invece delle $11$ della traccia originale. Usa inoltre una `pthread_cond_t`: thread 1 e thread 2 chiamano `pthread_cond_signal` dopo ogni scrittura; thread 3 attende su `pthread_cond_wait` prima di rieseguire il controllo di inizializzazione.
**Soluzione svolta:** `Thread e Sincronizzazione/pos_neg_one_thread_mutex.c`
### TM2 — Buffer N interi: pari/dispari + somma progressiva
**Consegna.** Buffer di $N$ interi inizializzato a $-1$:
- **Thread 1** — riempie le **posizioni pari** con un numero casuale in $[0, 100]$.
- **Thread 2** — riempie le **posizioni dispari** con un numero casuale in $[100, 200]$.
- **Thread 3** — attende che il buffer sia completamente inizializzato (nessun $-1$ residuo) tramite [[04 - Sincronizzazione#Variabili condizionali (pthread_cond)|variabile condizione]], poi esegue la **somma progressiva**: $\text{buf}[i] = \text{buf}[i] + \text{buf}[i-1]$ per $i \geq 1$.
**Soluzione svolta:** `Thread e Sincronizzazione/pari_dispari_insert_mutex.c`
### TM3 — Due array A e B, max e min
**Consegna.** Tre thread operano su due array $A$ e $B$ di $N$ interi:
- **Thread 1** — riempie l'array con numeri casuali in $[0, 100]$ e imposta un flag `done` al termine.
- **Thread 2** — attende `done` e calcola il **massimo**.
- **Thread 3** — attende `done` e calcola il **minimo**.
La sincronizzazione usa solo il mutex (senza `pthread_cond_t`): i thread di lettura fanno **busy-waiting** sul flag.
**Soluzione svolta:** `Thread e Sincronizzazione/init_max_min_mutex.c`
## Thread — Semafori
Le tracce di questa sezione usano [[04 - Sincronizzazione#Semafori|sem_t]] (POSIX, `<semaphore.h>`). Il semaforo binario sostituisce il mutex dove specificato; i semafori di conteggio (`full`/`empty`) realizzano lo schema **produttore–consumatore** classico (si veda [[04 - Sincronizzazione]]).
### TS1 — Produttore–consumatore con semafori (pari/dispari)
**Consegna.** Buffer di $N$ elementi inizializzato a $-1$. Il **produttore** inserisce:
- numeri dispari in $[1, 99]$ nelle posizioni dispari,
- numeri pari in $[100, 198]$ nelle posizioni pari.
Il **consumatore** legge una coppia (posizione dispari, posizione pari), calcola la somma e la stampa. Sincronizzazione tramite semafori `mutex`, `full`, `empty` (schema classico produttore–consumatore).
**Soluzione svolta:** `Thread e Sincronizzazione/prod_cons_sem.c`
### TS2 — N/2 thread stampano caratteri in maiuscolo
**Consegna.** Data una stringa di $N$ caratteri passata da riga di comando, vengono creati $N/2$ thread. Ogni thread, sincronizzato tramite un semaforo binario (`mutex`), legge il prossimo carattere disponibile da un indice condiviso `in`, lo converte in maiuscolo e lo stampa, poi incrementa `in`. Il risultato è la stampa di tutti gli $N$ caratteri in maiuscolo.
**Soluzione svolta:** `Thread e Sincronizzazione/print_char_sem.c`
### TS3 — Uno scrittore e cinque lettori (semafori, readers–writers)
**Consegna.** Sei thread su un buffer di $N$ interi:
- **Scrittore** — scrive in posizioni dispari numeri dispari in $[1, 49]$ e in posizioni pari numeri pari in $[52, 100]$. Accede al buffer con semaforo `arr` (mutua esclusione totale).
- **Cinque lettori** — leggono coppie (posizione dispari, posizione pari), le sommano e stampano. Implementano lo schema **readers–writers**: più lettori possono leggere in contemporanea; il primo lettore acquisisce `arr`, l'ultimo lo rilascia (contatore `r_count` protetto da `mutex`).
**Soluzione svolta:** `Thread e Sincronizzazione/readers_writers_pari_dispari.c`
