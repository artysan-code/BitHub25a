# Esercizi Svolti — Sincronizzazione
Esercizi di ragionamento sulla mutua esclusione (Peterson, semafori, deadlock) e **schede di svolgimento** delle soluzioni C con thread, mutex, variabili condizione e semafori. Per lo scritto del **Modulo 1**. Teoria di riferimento: [[04 - Sincronizzazione]].

> [!info] Verifica
> Le tracce dei semafori (valori, processi bloccati) sono state **verificate** simulando passo-passo la semantica `down`/`up`. Le soluzioni C complete sono in `Thread e Sincronizzazione/`, con le consegne in [[Tracce d'Esame Pratiche]].
## Es. 1 — Traccia dell'algoritmo di Peterson
> [!quote] Consegna
> Due processi $P_0$ e $P_1$ chiamano `enter_region` quasi simultaneamente. Mostrare un'esecuzione interlacciata e spiegare **chi entra** e **chi attende**, senza violare la mutua esclusione. (Codice in [[04 - Sincronizzazione#Algoritmo di Peterson|nota — Peterson]].)

Ricordando la condizione di attesa `while (turn == process && interested[other])`: si attende **solo** se è il proprio turno *e* l'altro è interessato. Interlacciamento critico (entrambi segnalano interesse, poi scrivono `turn`):

| Passo | Azione | Stato dopo |
|---|---|---|
| 1 | $P_0$: `interested[0] = TRUE` | `interested = [T, F]` |
| 2 | $P_1$: `interested[1] = TRUE` | `interested = [T, T]` |
| 3 | $P_0$: `turn = 0` | `turn = 0` |
| 4 | $P_1$: `turn = 1` | `turn = 1` (sovrascrive) |
| 5 | $P_0$: test `turn==0 && interested[1]` → `F && T` = **falso** → **entra** | $P_0$ in regione critica |
| 6 | $P_1$: test `turn==1 && interested[0]` → `T && T` = **vero** → **attende** | $P_1$ in spin |

> [!check] Chi vince è chi scrive `turn` per ultimo… e perde
> L'**ultimo** a scrivere `turn` (qui $P_1$) lascia `turn` puntato a sé stesso: la sua condizione di attesa diventa vera e **aspetta**, mentre l'altro entra. Quando $P_0$ esce (`interested[0] = FALSE`), la condizione di $P_1$ diventa falsa e $P_1$ entra. Mutua esclusione garantita, nessuna attesa reciproca: vale anche il requisito di **progresso**.
## Es. 2 — Valori di un semaforo e coda dei bloccati
> [!quote] Consegna
> Un semaforo $S$ è inizializzato a **2**. Quattro processi $A, B, C, D$ eseguono `down(S)` in quest'ordine, poi arrivano due `up(S)`. Indicare, a ogni passo, il valore di $S$, chi prosegue e chi si blocca; e lo stato finale.

Semantica: [[04 - Sincronizzazione#Semafori|`down`]] entra se $S > 0$ (e decrementa), altrimenti **blocca** in coda; [[04 - Sincronizzazione#Semafori|`up`]] **risveglia** un processo in coda se ce n'è (e $S$ resta invariato), altrimenti incrementa $S$.

| Operazione | $S$ | Effetto | Coda bloccati |
|---|---|---|---|
| init | 2 | — | — |
| `down(A)` | 1 | $A$ prosegue | — |
| `down(B)` | 0 | $B$ prosegue | — |
| `down(C)` | 0 | $C$ si **blocca** | `[C]` |
| `down(D)` | 0 | $D$ si **blocca** | `[C, D]` |
| `up` | 0 | risveglia $C$ | `[D]` |
| `up` | 0 | risveglia $D$ | `[]` |

> [!check] Stato finale
> $S = 0$, coda vuota: tutti e quattro hanno "passato" il semaforo, ma due (`C`, `D`) hanno dovuto **attendere** un `up`. Quando ci sono processi in coda, `up` **non** incrementa il valore: si limita a sbloccarne uno. Il valore di un semaforo "conta" i permessi disponibili **solo** quando è positivo.
## Es. 3 — Deadlock da inversione dei `down`
> [!quote] Consegna
> Nel produttore–consumatore con semafori (`mutex = 1`, `empty = N`, `full = 0`), il produttore corretto fa `down(empty)` **poi** `down(mutex)`. Cosa succede se i due `down` vengono **invertiti**? Costruire lo scenario di blocco.

Con l'ordine **invertito** nel produttore (`down(mutex)` prima di `down(empty)`) e il buffer **pieno** ($\text{empty} = 0$):
1. il produttore esegue `down(mutex)` → entra nella regione critica, `mutex = 0`;
2. poi `down(empty)` con `empty = 0` → si **blocca** (il buffer è pieno), **tenendo ancora il mutex**;
3. il consumatore tenta `down(mutex)` per prelevare → `mutex = 0` → si **blocca**.
Ora: il produttore aspetta che il consumatore liberi un posto (`up(empty)`), ma il consumatore aspetta il mutex che **solo** il produttore può rilasciare. Nessuno avanza.

> [!warning] La regola
> **Acquisire sempre prima il semaforo di conteggio (`empty`/`full`) e poi il `mutex`**, e rilasciare in ordine inverso. Invertirli crea un'attesa circolare → **deadlock**. È l'errore classico d'esame: lo stesso vale per il consumatore (`down(mutex)` prima di `down(full)`).
## Es. 4 — Produttore–consumatore: traccia dei semafori
> [!quote] Consegna
> Buffer di **N = 3** posti, `empty = 3`, `full = 0`, `mutex = 1`. Tracciare `empty` e `full` per: **3 produzioni** consecutive, una **4ª produzione**, poi **1 consumo**.

| Evento | `empty` | `full` | Buffer | Note |
|---|---|---|---|---|
| init | 3 | 0 | 0/3 | — |
| produci #1 | 2 | 1 | 1/3 | `down(empty)` poi `up(full)` |
| produci #2 | 1 | 2 | 2/3 | |
| produci #3 | 0 | 3 | 3/3 | buffer **pieno** |
| produci #4 | 0 | 3 | 3/3 | `down(empty)` con `empty=0` → **bloccato** |
| consuma #1 | 1 | 2 | 2/3 | `down(full)` poi `up(empty)` → risveglia il produttore |

> [!note] I due contatori sono speculari
> `empty + full` resta sempre $\le N$ (qui sempre $= 3$ a regime): `empty` conta i posti liberi e blocca il **produttore** quando è 0; `full` conta gli occupati e blocca il **consumatore** quando è 0. Il `mutex` serializza l'accesso effettivo al buffer (qui omesso dalla traccia perché torna sempre a 1 dopo ogni operazione).
## Es. 5 — Lettori e scrittori: il contatore `rc`
> [!quote] Consegna
> Schema [[04 - Sincronizzazione#Lettori e scrittori|lettori–scrittori]] con priorità ai lettori: contatore `rc` (lettori attivi) protetto da `mutex`, semaforo `db` per l'accesso ai dati. Tracciare `rc` e `db` per: **3 lettori entrano**, poi **3 lettori escono**. Quando è bloccato lo scrittore?

| Evento | `rc` | `db` | Effetto |
|---|---|---|---|
| 1° lettore entra | 1 | 0 | è il **primo**: `down(db)` → **scrittore bloccato** |
| 2° lettore entra | 2 | 0 | `db` invariato (legge in parallelo) |
| 3° lettore entra | 3 | 0 | `db` invariato |
| 1° lettore esce | 2 | 0 | non è l'ultimo |
| 2° lettore esce | 1 | 0 | non è l'ultimo |
| 3° lettore esce | 0 | 1 | è l'**ultimo**: `up(db)` → scrittore può entrare |

> [!warning] Starvation degli scrittori
> Con questo schema lo scrittore entra **solo** quando `rc` torna a 0. Se i lettori arrivano in continuazione, `rc` non si azzera mai e lo scrittore **attende all'infinito** (*starvation*). Le soluzioni con priorità agli scrittori, o "giuste", risolvono il problema a scapito della semplicità.
## Soluzioni C — Thread, mutex, condizioni, semafori
Schede di svolgimento dei `.c` in `Thread e Sincronizzazione/`. Consegne in [[Tracce d'Esame Pratiche#Thread — Mutex]] e [[Tracce d'Esame Pratiche#Thread — Semafori]]. Scheletro comune:

> [!example] Scheletro comune — pthreads
> 1. `pthread_create(&tid, NULL, funzione, arg)` avvia un thread; `pthread_join(tid, NULL)` ne attende la fine. I thread **condividono** lo spazio di indirizzi → le variabili globali sono memoria comune da proteggere.
> 2. **Mutex** (`pthread_mutex_lock`/`unlock`) per la **mutua esclusione**; **variabile condizione** (`pthread_cond_wait`/`signal`) per **attendere un evento** senza busy-wait; **semaforo** (`sem_wait`/`sem_post`) per contare permessi.
> 3. `pthread_cond_wait(&cond, &mutex)` rilascia il mutex e dorme **atomicamente**, lo riacquisisce al risveglio: va sempre usato dentro un `while (condizione)` (non `if`).
### prod_cons_sem.c — traccia TS1
**Pattern:** produttore–consumatore canonico con **tre semafori** `mutex`, `full`, `empty`. Il produttore fa `down(empty)`→`down(mutex)`→inserisce→`up(mutex)`→`up(full)`; il consumatore la sequenza duale. **Idea chiave:** rispettare l'ordine dei `down` per non cadere nel [[#Es. 3 — Deadlock da inversione dei `down`|deadlock dell'Es. 3]]; `empty`/`full` realizzano la sincronizzazione su buffer limitato. → `Thread e Sincronizzazione/prod_cons_sem.c` · [[Tracce d'Esame Pratiche#Thread — Semafori|TS1]].
### readers_writers_pari_dispari.c — traccia TS3
**Pattern:** **lettori–scrittori** con priorità ai lettori (1 scrittore, 5 lettori). Contatore `r_count` protetto da `mutex`; semaforo `arr` per l'accesso esclusivo al buffer. **Idea chiave:** il **primo** lettore fa `sem_wait(arr)` (blocca lo scrittore), l'**ultimo** fa `sem_post(arr)` — esattamente la logica `rc`/`db` dell'[[#Es. 5 — Lettori e scrittori: il contatore `rc`|Es. 5]]. → `Thread e Sincronizzazione/readers_writers_pari_dispari.c` · [[Tracce d'Esame Pratiche#Thread — Semafori|TS3]].
### print_char_sem.c — traccia TS2
**Pattern:** **semaforo binario** come mutex su un indice condiviso. Da una stringa si creano `len/2` thread; ognuno fa `sem_wait(mutex)`, legge e avanza l'indice globale `in`, stampa il carattere in maiuscolo, `sem_post(mutex)`. **Idea chiave:** la sezione critica è "leggi-e-incrementa `in`"; se `in >= len` il thread rilascia subito ed esce (niente accesso fuori dai limiti). → `Thread e Sincronizzazione/print_char_sem.c` · [[Tracce d'Esame Pratiche#Thread — Semafori|TS2]].
### pos_neg_one_thread_mutex.c — traccia TM1
**Pattern:** mutex + **variabile condizione** + terminazione con `pthread_kill`. Thread1 scrive `+1` e thread2 `−1` in celle casuali; il thread3 *control* attende su `pthread_cond_wait` finché tutte le celle sono $\neq 0$, poi conta e termina gli altri due. **Idea chiave:** è la versione **a thread** dell'appello a processi `26_01_24_appello.c` — qui si termina con `pthread_kill(tid, SIGINT)`, non con `kill` (vedi differenza processi/thread in [[03 - Processi e Thread#Thread e processi|03 - Processi e Thread]]). *Nota: la soluzione usa N=5 celle invece delle 11 della traccia.* → `Thread e Sincronizzazione/pos_neg_one_thread_mutex.c` · [[Tracce d'Esame Pratiche#Thread — Mutex|TM1]].
### pari_dispari_insert_mutex.c — traccia TM2
**Pattern:** mutex + variabile condizione + **somma progressiva**. Thread1 riempie le posizioni pari, thread2 le dispari; il thread3 attende con `pthread_cond_wait` che il buffer sia completo, poi calcola $\text{buf}[i] = \text{buf}[i] + \text{buf}[i-1]$. **Idea chiave:** il pattern *wait–signal* (i due riempitori fanno `signal` dopo ogni scrittura; il sommatore controlla la condizione in un `while`). → `Thread e Sincronizzazione/pari_dispari_insert_mutex.c` · [[Tracce d'Esame Pratiche#Thread — Mutex|TM2]].
### init_max_min_mutex.c — traccia TM3
**Pattern:** mutex + **flag `done`** + busy-wait (senza variabile condizione). Thread1 riempie l'array e imposta `done = 1`; thread2 (max) e thread3 (min) fanno `while (done != 1) ;` e poi scandiscono. **Idea chiave:** mostra il **costo** della soluzione senza `cond` — i lettori sprecano CPU in attesa attiva; confrontare con `pari_dispari_insert_mutex.c`. → `Thread e Sincronizzazione/init_max_min_mutex.c` · [[Tracce d'Esame Pratiche#Thread — Mutex|TM3]].
### thread_mutex_file.c — accesso esclusivo a file
**Pattern:** mutex per l'accesso esclusivo a un **file**. Due thread (`increment`/`decrement`) leggono+modificano+riscrivono una cella di `dati.txt`, posizionandosi con `lseek`; un mutex globale protegge l'intera sequenza. **Idea chiave:** la sezione critica non è una variabile ma un **file condiviso**: read-modify-write deve essere atomico. *Nota: versione didattica ridotta a 2 thread (il terzo thread di controllo è dichiarato ma non avviato).* → `Thread e Sincronizzazione/thread_mutex_file.c`.

## Da svolgere
Tracce senza soluzione. Le prime sono di ragionamento, le ultime di programmazione (riusano lo [[#Soluzioni C — Thread, mutex, condizioni, semafori|scheletro pthreads]]).

> [!todo] Da svolgere — ragionamento
> 1. **Semaforo con `up` in eccesso.** $S$ inizia a **1**. Sequenza: `down`, `down`, `up`, `up`, `up`, `down`. Traccia il valore di $S$ e la coda a ogni passo. Qual è il valore finale?
> 2. **Deadlock dei filosofi.** Perché la soluzione "ognuno prende prima la forchetta sinistra, poi la destra" porta a deadlock se **tutti** iniziano insieme? Quale requisito di [[04 - Sincronizzazione#Regioni critiche e requisiti|sezione critica]] viola? (vedi [[04 - Sincronizzazione#I filosofi a cena|filosofi a cena]]).
> 3. **`if` vs `while` sulla cond.** Perché `pthread_cond_wait` va messo in un `while (condizione)` e non in un `if`? Cosa sono gli *spurious wakeup*?
> 4. **Inversione di priorità.** Descrivi uno scenario con tre task (alta/media/bassa priorità) in cui un task ad alta priorità resta bloccato da uno a bassa priorità. Come lo risolve l'**ereditarietà di priorità**? (vedi [[04 - Sincronizzazione#Inversione delle priorità|inversione delle priorità]]).

> [!todo] Da svolgere — programmazione C
> 5. **Conto alla rovescia sincronizzato.** Tre thread incrementano un contatore globale fino a 30; proteggi l'accesso con un mutex e stampa il valore finale (deve essere esattamente 30, non meno: dimostra la *race condition* rimuovendo il mutex).
> 6. **Barriera.** $N$ thread fanno ciascuno un calcolo, poi si **attendono a vicenda** su una barriera (`pthread_barrier_t` oppure mutex + cond) prima di proseguire alla fase 2.
> 7. **Produttore–consumatore con `pthread_cond`.** Riscrivi `prod_cons_sem.c` usando **mutex + due variabili condizione** (`not_full`, `not_empty`) invece dei semafori `empty`/`full`.

---
**Teoria di riferimento:** [[04 - Sincronizzazione]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
