# Esercizi Svolti — Processi e Thread
Esercizi di ragionamento sui processi (conteggio da `fork`, duplicazione del buffer, multiprogrammazione) e **schede di svolgimento** delle soluzioni C di laboratorio. Per lo scritto del **Modulo 1**. Teoria di riferimento: [[03 - Processi e Thread]] e [[10 - Programmazione C e Concorrente]].

> [!info] Verifica
> I conteggi di processi e gli output sono stati **verificati compilando ed eseguendo** programmi C reali (`gcc -Wall -Wextra`). Le soluzioni complete dei `.c` citati sono nelle cartelle `Processi/` e `Thread e Sincronizzazione/`, con le consegne in [[Tracce d'Esame Pratiche]].
## Es. 1 — Conteggio processi: `fork` sequenziali
> [!quote] Consegna
> Quanti processi esistono al termine del seguente frammento? Disegnare l'albero.
> ```c
> fork();
> fork();
> fork();
> ```

Ogni `fork()` **raddoppia** il numero di processi in vita: chi esegue la `fork` continua, e in più nasce un clone che eseguirà *anch'esso* le `fork` successive. Partendo da 1 processo:
$$1 \xrightarrow{\text{fork}} 2 \xrightarrow{\text{fork}} 4 \xrightarrow{\text{fork}} 8.$$
L'albero (P = processo iniziale; ogni nodo genera un figlio a ogni `fork` che gli resta):
```text
            P
      ┌─────┼─────┐         dopo la 1ª fork: P, A
      P     A               dopo la 2ª fork: P,A generano B,C
    ┌─┼─┐ ┌─┼─┐             dopo la 3ª fork: i 4 generano 4 figli
    P B   A C
   ┌┴┐ │ ┌┴┐ │
   P D B E A F C G          → 8 processi totali
```

> [!check] Regola generale
> $n$ `fork()` **in sequenza** (non annidate) producono $2^n$ processi totali, di cui $2^n - 1$ figli. Con 3 `fork` → $2^3 = \mathbf{8}$ processi (verificato: 8 stampe di `getpid`).
## Es. 2 — `fork` dentro un ciclo
> [!quote] Consegna
> Quanti processi crea il ciclo seguente per $n = 3$ e per $n = 4$?
> ```c
> for (int i = 0; i < n; i++)
>     fork();
> ```

Il ciclo equivale a $n$ `fork()` in sequenza: ogni iterazione raddoppia i processi (anche i figli appena nati proseguono il ciclo da dove l'hanno ereditato). Quindi:
$$\text{processi totali} = 2^n.$$
- $n = 3 \Rightarrow 2^3 = \mathbf{8}$ (verificato);
- $n = 4 \Rightarrow 2^4 = \mathbf{16}$ (verificato).

> [!warning] Errore tipico
> Rispondere "$n+1$" pensando che solo il padre forki: **anche i figli eseguono le iterazioni rimanenti** del ciclo. Per ottenere davvero una catena di $n+1$ processi serve far uscire il padre dal ciclo (es. `if (fork() != 0) break;`).
## Es. 3 — `fork` condizionali (solo il figlio si riproduce)
> [!quote] Consegna
> Quanti processi esistono al termine? Spiegare.
> ```c
> if (fork() == 0) {   /* solo il figlio entra */
>     fork();
> }
> ```

[[03 - Processi e Thread#^fork|`fork()`]] restituisce **0 al figlio** e il **PID del figlio (≠ 0) al padre**. Quindi:
- il **padre** valuta la condizione come falsa → **non** rientra nell'`if`, prosegue;
- il **figlio** valuta `0 == 0` vera → esegue la seconda `fork`, generando un nipote.
Processi: padre $P_0$, figlio $P_1$, nipote $P_2$ → **3 processi** (verificato: 3 stampe). Il valore di ritorno di `fork()` è ciò che permette di **differenziare i rami** di esecuzione: è la chiave di tutte le soluzioni C qui sotto.

## Es. 4 — Duplicazione del buffer: `printf` prima della `fork`
> [!quote] Consegna
> Quante righe `A` produce il programma se l'output va su **file** (o pipe)? E se si aggiunge `fflush(stdout)` prima delle `fork`?
> ```c
> printf("A\n");
> fork();
> fork();
> return 0;
> ```

La `stdout` del C è **bufferizzata**. Quando l'output è un **file o una pipe** il buffering è *full* (a blocchi): la stringa `"A\n"` resta nel **buffer in memoria** e non viene scritta subito. Al momento delle `fork`, il buffer — *contenuto della memoria del processo* — viene **copiato in ogni figlio**. I 4 processi finali (vedi [[#Es. 1 — Conteggio processi: `fork` sequenziali|Es. 1]]) svuotano ciascuno il proprio buffer all'uscita → **4 righe `A`** (verificato).
Con `fflush(stdout)` **prima** della `fork`, il buffer viene svuotato subito: alla `fork` non c'è nulla da duplicare → **1 sola riga `A`** (verificato).

> [!warning] Insidia d'esame e regola di laboratorio
> Su **terminale** (TTY) la `stdout` è *line-buffered*: il `\n` provoca lo svuotamento immediato, quindi a video si vedrebbe **1** sola `A` anche senza `fflush` *(comportamento standard di line-buffering; non riproducibile qui perché in ambiente non interattivo la `stdout` è una pipe, quindi full-buffered)*. Morale operativa: **chiamare sempre `fflush(stdout)` prima di `fork()`** per non duplicare l'output bufferizzato — è la convenzione adottata in tutte le soluzioni C di questa raccolta.
## Es. 5 — Utilizzo della CPU in multiprogrammazione *(extra, non da slide)*
> [!quote] Consegna
> Un processo passa l'**80%** del tempo in attesa di I/O ($p = 0{,}8$). Qual è l'utilizzo della CPU con **4** processi in memoria? E con **8**? Quanto si guadagna raddoppiando da 4 a 8?

Con il modello probabilistico [[03 - Processi e Thread#Modellazione della multiprogrammazione|$\text{Utilizzo} = 1 - p^n$]] (probabilità che **non** siano tutti in attesa insieme):
$$n = 4:\quad 1 - 0{,}8^4 = 1 - 0{,}4096 = \mathbf{0{,}590} \;(\approx 59\%).$$
$$n = 8:\quad 1 - 0{,}8^8 = 1 - 0{,}1678 = \mathbf{0{,}832} \;(\approx 83\%).$$

> [!note] Rendimenti decrescenti
> Raddoppiando da 4 a 8 processi l'utilizzo sale di **$\approx 24$ punti** (da 59% a 83%): un buon guadagno. Ma da 8 a 16 si passerebbe solo da 83% a $\approx 97\%$ (**+14**): ogni processo aggiunto rende meno del precedente. È il motivo per cui aumentare la RAM oltre un certo punto dà benefici sempre minori.
## Soluzioni C — Processi (fork, pipe, segnali, file)
Schede di svolgimento ragionato dei `.c` in `Processi/`. La **consegna** di ciascuno è in [[Tracce d'Esame Pratiche#Processi]]; qui sta *come* si costruisce la soluzione. Tutte condividono lo stesso scheletro:

> [!example] Scheletro comune — `fork` + pipe
> 1. **Crea le pipe PRIMA della `fork`** (`pipe(fd)`): solo così i figli le ereditano. `fd[0]` = lettura, `fd[1]` = scrittura (convenzione `#define PIPE_RD 0`, `PIPE_WR 1`).
> 2. **`fflush(stdout)` prima della `fork`** (evita la duplicazione del buffer, vedi [[#Es. 4 — Duplicazione del buffer: `printf` prima della `fork`|Es. 4]]).
> 3. Ogni processo **chiude le estremità che non usa** (un lettore chiude `PIPE_WR` e viceversa): senza questo, una `read` non rileva mai l'**EOF**.
> 4. Il padre **raccoglie** con `read`/`waitpid`; per fermare figli in ciclo infinito usa `kill(pid, SIGTERM)` + `waitpid` (evita gli *zombie*).
### fork_sum.c — traccia P6
**Pattern:** due figli *produttori* + padre *raccoglitore*, terminazione a soglia. Ogni figlio genera in un intervallo e filtra (multipli di 3 / di 2), poi scrive nella **propria** pipe; il padre legge una **coppia** per iterazione, somma e quando `sum >= 130` invia `SIGTERM`. **Idea chiave:** una pipe **dedicata** per figlio così il padre sa da chi arriva il dato; la soglia si controlla nel `do…while` del padre. → `Processi/fork_sum.c` · [[Tracce d'Esame Pratiche#Processi|P6]].
### fork_pari_dispari_soglia.c — traccia P2
**Pattern:** variante di P6 con parità (pari in $[0,100]$ / dispari in $[0,100]$) e soglia 190. **Idea chiave:** il filtro di parità è un `do { n = rand()%101; } while (n%2 != 0);`; il padre esce quando la somma di una coppia supera 190 (max $100+99=199$). → `Processi/fork_pari_dispari_soglia.c` · [[Tracce d'Esame Pratiche#Processi|P2]].
### fork_catena_moltiplica.c — traccia P3
**Pattern:** **due pipe in cascata** figlio1 → padre → figlio2. Il padre fa da *stadio intermedio*: legge dal figlio1, moltiplica per un fattore casuale, inoltra al figlio2. **Idea chiave:** servono due pipe distinte e il padre chiude le estremità giuste di entrambe; il figlio2 è puro consumatore (chiude tutto tranne la lettura della seconda pipe). → `Processi/fork_catena_moltiplica.c` · [[Tracce d'Esame Pratiche#Processi|P3]].
### fork_pipe_bidirezionale_quadrato.c — traccia P7
**Pattern:** **pipe bidirezionale** (due pipe, una per verso) + rilevamento **EOF**. Il padre invia un numero, il figlio calcola il quadrato e lo **rimanda solo se pari**. **Idea chiave:** quando il figlio non rimanda nulla e chiude la pipe, la `read` del padre restituisce **0 (EOF)**: è così che il padre distingue "nessun valore" da "valore 0". → `Processi/fork_pipe_bidirezionale_quadrato.c` · [[Tracce d'Esame Pratiche#Processi|P7]].
### fork_fusione_pari_dispari.c — traccia P8
**Pattern:** due figli inviano gli elementi nelle posizioni **pari** / **dispari**; il padre **ricompone** l'array e calcola max e min. **Idea chiave:** trasferire array via pipe con `write`/`read` di `sizeof(int)*k`; ricomporre interlacciando i due flussi. Mostra l'uso di `fflush(stdout)` prima della `fork`. → `Processi/fork_fusione_pari_dispari.c` · [[Tracce d'Esame Pratiche#Processi|P8]].
### 26_01_24_appello.c — traccia P10
**Pattern:** **buffer condiviso di 11 interi** + due figli + segnali. Figlio1 manda indici (il padre scrive `+1`), figlio2 manda indici (il padre scrive `−1`); quando il buffer non ha più zeri, il padre conta i `+1`/`−1` e termina i figli. **Idea chiave:** il buffer vive **solo nel padre** (i figli mandano *indici*, non scrivono); la condizione di terminazione è "nessuno zero residuo". → `Processi/26_01_24_appello.c` · [[Tracce d'Esame Pratiche#Processi|P10]].
### fork_seek_occurrences.c — traccia P1
**Pattern:** `fork` + pipe + `lseek` + `stat`. Due figli contano le occorrenze di una parola in **metà file** ciascuno: figlio1 da `0` a `size/2`, figlio2 da `size/2` alla fine. **Idea chiave:** `stat()` fornisce la dimensione, `lseek` posiziona il cursore all'inizio della metà; ogni figlio invia il conteggio parziale, il padre somma. Syscall su file in [[07 - File System]]. → `Processi/fork_seek_occurrences.c` · [[Tracce d'Esame Pratiche#Processi|P1]].
### fork_file_pari_dispari.c — traccia P9
**Pattern:** `fork` + pipe + `lseek` su **file condiviso**. Figlio1 scrive cifre pari su `dati.txt` e comunica via pipe la lunghezza scritta; figlio2 fa `lseek` subito dopo e aggiunge cifre dispari; il padre legge tutto. **Idea chiave:** la pipe serve da **segnale di sincronizzazione** ("ho finito, sei a offset X"); senza, il figlio2 sovrascriverebbe. → `Processi/fork_file_pari_dispari.c` · [[Tracce d'Esame Pratiche#Processi|P9]].
### fork_readdir_permessi.c — traccia P4
**Pattern:** `fork` + `opendir`/`readdir` (`<dirent.h>`) + `stat`/`chmod` + pipe condivisa. Due figli leggono **metà** dei file regolari di una directory, aggiungono il permesso di lettura se manca, e inviano `[PID] -> contenuto`. **Idea chiave:** scorrere la directory con `readdir`, filtrare i regolari con `stat` (`S_ISREG`), correggere i permessi con `chmod` prima di aprire. Directory e permessi in [[07 - File System]]. → `Processi/fork_readdir_permessi.c` · [[Tracce d'Esame Pratiche#Processi|P4]].
### matrix_fork.c — traccia P5
**Pattern:** calcolo **parallelo per colonne** di $M_1 \times M_2$ ($3\times3$). Figlio1 calcola la colonna 0, figlio2 la colonna 1, il padre la colonna 2; le colonne dei figli arrivano via pipe e il padre compone il risultato. **Idea chiave:** decomporre il lavoro in unità indipendenti (le colonne) e trasferire array di interi con `write`/`read` di `sizeof(int)*N`; sincronizzazione con `waitpid`. → `Processi/matrix_fork.c` · [[Tracce d'Esame Pratiche#Processi|P5]].

## Da svolgere
Tracce senza soluzione, per esercitarsi. Riusano lo [[#Soluzioni C — Processi (fork, pipe, segnali, file)|scheletro comune]] visto sopra.

> [!todo] Da svolgere — ragionamento
> 1. **Albero misto.** Quanti processi crea `fork(); if (fork() == 0) fork(); fork();`? Disegna l'albero e verifica contando gli `getpid`.
> 2. **Catena di $k$.** Scrivi un frammento che crei una **catena** di esattamente $k$ processi (ognuno figlio del precedente), non un albero. Perché serve `break` dopo la `fork` nel padre?
> 3. **Zombie e orfani.** Cosa succede a un figlio se il padre termina **senza** fare `wait`? E se il figlio termina e il padre **non** lo raccoglie mai? Definisci *processo zombie* e *processo orfano* e di' chi "adotta" gli orfani.
> 4. **Buffer e `fork`.** Modifica l'Es. 4 mettendo `printf("A")` **senza** `\n`: quante `A` compaiono su file? E perché aggiungere `\n` da solo non basta a evitare la duplicazione su file?

> [!todo] Da svolgere — programmazione C
> 5. **Conteggio righe parallelo.** Come [[Tracce d'Esame Pratiche#Processi|P1]] ma i due figli contano le **righe** (non le occorrenze di una parola) di metà file ciascuno; il padre stampa il totale.
> 6. **Pipe a tre stadi.** Estendi [[Tracce d'Esame Pratiche#Processi|P3]] a una catena figlio1 → padre → figlio2 → padre: il figlio2 rimanda il risultato al padre, che stampa solo se è un quadrato perfetto.
> 7. **`fork` + `exec`.** Scrivi una mini-shell che legge un comando da `stdin`, fa `fork` e nel figlio esegue `execvp`; il padre attende con `waitpid` e stampa lo stato di uscita.

---
**Teoria di riferimento:** [[03 - Processi e Thread]] · [[10 - Programmazione C e Concorrente]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
