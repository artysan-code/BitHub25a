# Esercizi Svolti — File System
Esercizi di calcolo sull'implementazione del file system, svolti passo-passo, per lo scritto del **Modulo 1**. Teoria di riferimento: [[07 - File System]].

> [!info] Verifica
> Tutti i calcoli sono stati verificati numericamente. Equivalenze: $1\,\text{KB} = 2^{10}$ B, $1\,\text{MB} = 2^{20}$ B, $1\,\text{GB} = 2^{30}$ B, $1\,\text{TB} = 2^{40}$ B.
## Es. 1 — Dimensione massima di un file con i-node multi-livello
> [!warning] Assunzioni (non tutte fissate dalle slide)
> Le slide e la [[07 - File System#I-node|nota]] descrivono l'i-node con alcuni **blocchi diretti** più uno o più livelli di **indirizzamento indiretto**, ma **non** fissano il numero esatto di puntatori per livello. Questo esercizio usa la struttura **classica UNIX** (la più richiesta agli esami), dichiarandone le ipotesi:
> - **12 blocchi diretti** + **1 indiretto singolo** + **1 indiretto doppio** + **1 indiretto triplo**;
> - dimensione del **blocco** = $1\,\text{KB}$; dimensione di un **puntatore** = $4$ byte.

**Passo 1 — puntatori per blocco.** Un blocco di puntatori contiene $\dfrac{1024\,\text{B}}{4\,\text{B}} = 256$ puntatori.
**Passo 2 — blocchi raggiungibili per livello:**

| Livello | Blocchi dati indirizzati |
|---|---|
| Diretti | $12$ |
| Indiretto singolo | $256$ |
| Indiretto doppio | $256^2 = 65\,536$ |
| Indiretto triplo | $256^3 = 16\,777\,216$ |

**Passo 3 — totale.** Blocchi totali $= 12 + 256 + 65\,536 + 16\,777\,216 = 16\,843\,020$. Moltiplicando per la dimensione del blocco:
$$16\,843\,020 \times 1\,\text{KB} = 16\,843\,020\,\text{KB} \approx \mathbf{16{,}06\ GB}.$$

> [!check] Osservazione
> Il termine **dominante** è l'indiretto triplo ($16\,777\,216\,\text{KB} = 16\,\text{GB}$): i livelli diretti e a singolo/doppio indiretto sono trascurabili nel totale. Aumentando il blocco a $4\,\text{KB}$ (quindi $1024$ puntatori/blocco) il massimo sale a $\approx 4\,\text{TB}$: la dimensione del blocco influisce in modo **cubico** sul limite, perché compare sia come capacità del blocco sia, al cubo, nel numero di puntatori indirizzabili.
## Es. 2 — Occupazione di memoria della FAT
> [!quote] Consegna
> Disco da $1\,\text{TB}$ con blocchi da $1\,\text{KB}$. Quanta RAM serve per tenere la **FAT** in memoria, con voci da 3 byte e da 4 byte?

**Numero di blocchi** (= numero di voci della FAT, una per blocco):
$$\frac{1\,\text{TB}}{1\,\text{KB}} = \frac{2^{40}}{2^{10}} = 2^{30} \approx 1{,}07 \times 10^9 \text{ blocchi}.$$
Per indirizzare $2^{30}$ blocchi servono $\ge 30$ bit per voce → almeno 4 byte (oppure 3 byte "stretti"):
- voci da **3 byte**: $2^{30} \times 3 = \mathbf{3\ GB}$ di RAM.
- voci da **4 byte**: $2^{30} \times 4 = \mathbf{4\ GB}$ di RAM.

> [!warning] Conclusione
> La FAT deve stare **interamente** in RAM: già per un disco da 1 TB richiede **3–4 GB**, il che la rende **inadatta ai dischi grandi**. È il motivo per cui i sistemi UNIX usano gli **i-node**, di cui in memoria sta solo la quota relativa ai **file aperti** (indipendente dalla dimensione del disco). Vedi [[07 - File System#I-node]].
## Es. 3 — Bitmap vs free list per i blocchi liberi
> [!quote] Consegna
> Disco da $1\,\text{TB}$, blocchi da $1\,\text{KB}$, numeri di blocco da $32$ bit. Confrontare lo spazio occupato da **bitmap** e da **lista concatenata** dei blocchi liberi.

Il disco ha $2^{30}$ blocchi (come nell'Es. 2).
**Bitmap** — 1 bit per blocco:
$$2^{30}\ \text{bit} = \frac{2^{30}}{8}\ \text{byte} = 2^{27}\ \text{byte} = \mathbf{128\ MB}.$$
**Lista concatenata** — ogni blocco-lista da $1\,\text{KB}$ contiene $\dfrac{1024}{4} = 256$ numeri da 4 byte, ma **1** è riservato al puntatore al blocco-lista successivo → **255** numeri di blocchi liberi utili per blocco. Nel caso peggiore (disco quasi tutto **libero**):
$$\frac{2^{30}}{255} \approx 4{,}2 \text{ milioni di blocchi-lista} \;\approx\; 4\,\text{GB}.$$

> [!check] Quale conviene?
> La **bitmap** ha **dimensione fissa** (128 MB) qualunque sia l'occupazione. La **free list** ha dimensione **proporzionale ai blocchi liberi**: enorme su disco vuoto, ma **vicina a zero su disco quasi pieno** (pochi blocchi liberi → pochi numeri da memorizzare, e per giunta nei blocchi liberi stessi, a costo zero). Regola pratica: bitmap quando il disco è mediamente pieno; free list quando è quasi pieno.
## Es. 4 — Dimensione del blocco e frammentazione interna
> [!quote] Consegna
> Stimare la **frammentazione interna** media (spazio sprecato nell'ultima pagina/blocco di ogni file) per blocchi da $1\,\text{KB}$ e da $4\,\text{KB}$, con file di dimensione media $2\,\text{KB}$. Commentare il compromesso.

**Modello**: l'ultima parte di un file riempie in media **metà** dell'ultimo blocco → spreco medio $\approx \text{dimensione blocco}/2$ per file (**fenomeno dell'ultima pagina**).

| Dimensione media file | Blocco | Spreco medio ($\approx$ blocco/2) | In % del file |
|---|---|---|---|
| 2 KB | 1 KB | 0,5 KB | 25% |
| 2 KB | 4 KB | 2 KB | 100% |
| 1 KB | 4 KB | 2 KB | 200% |
| 8 KB | 4 KB | 2 KB | 25% |

> [!check] Il compromesso
> Con file **piccoli**, blocchi **grandi** sprecano moltissimo (un file da 1 KB in un blocco da 4 KB spreca il 75% del blocco). Con file **grandi**, lo spreco relativo è trascurabile e i blocchi grandi **velocizzano** il trasferimento (meno `seek`, meno operazioni). Il valore comune **4 KB** è il punto in cui le due curve (velocità di trasferimento ↑ con il blocco, efficienza dello spazio ↓ oltre la dimensione media dei file) si incrociano. Vedi [[07 - File System#Dimensione dei blocchi — il compromesso]].
## Es. 5 — Accessi a disco per la lettura random
> [!quote] Consegna
> Un file occupa **100 blocchi** su disco. Quanti **accessi a disco** servono per leggere il blocco in posizione **#50** (lettura *random*, non sequenziale) con [[07 - File System#Allocazione contigua|allocazione contigua]], [[07 - File System#Allocazione a liste concatenate|a liste concatenate]], [[07 - File System#FAT (File Allocation Table)|FAT]] e [[07 - File System#I-node|i-node]]? Si assuma che FAT e i-node del file aperto siano già in **memoria**.

| Schema | Accessi per leggere il blocco #50 | Perché |
|---|---|---|
| **Contigua** | **1** | l'indirizzo si calcola: `inizio + 50`. Accesso diretto. |
| **Liste concatenate** | **51** | il puntatore al blocco successivo sta **dentro** ogni blocco: per arrivare al #50 bisogna leggere i blocchi $0, 1, \ldots, 50$ dal disco. |
| **FAT** | **1** | la catena dei puntatori è nella **tabella in RAM**: si segue in memoria (0 accessi) e si fa **1** accesso al blocco dati. |
| **I-node** | **1–2** | l'i-node è in memoria; il blocco #50 cade nell'**indiretto singolo** → 1 accesso alla tabella indiretta (se non in cache) + 1 al dato; per i 12 blocchi **diretti** basterebbe 1 accesso. |

> [!check] La lezione
> L'**allocazione concatenata pura** è pessima per la lettura random: $k+1$ accessi per il $k$-esimo blocco. La **FAT** risolve spostando i puntatori in una tabella in RAM (1 solo accesso), ma quella tabella può diventare enorme (vedi [[#Es. 2 — Occupazione di memoria della FAT|Es. 2]]). L'**i-node** dà accesso quasi diretto e in memoria tiene **solo** i file aperti: è il miglior compromesso, ed è la scelta di UNIX/Linux.
## Da svolgere
Esercizi senza soluzione. Equivalenze: $1\,\text{KB}=2^{10}$, $1\,\text{MB}=2^{20}$, $1\,\text{GB}=2^{30}$, $1\,\text{TB}=2^{40}$. Teoria in [[07 - File System]].

> [!todo] Da svolgere
> 1. **I-node con blocco da 4 KB.** Struttura classica UNIX (12 diretti + 1 indiretto singolo + 1 doppio + 1 triplo), blocco $4\,\text{KB}$, puntatore $4$ byte. Calcola i puntatori per blocco e la **dimensione massima** di un file (riusa il metodo dell'[[#Es. 1 — Dimensione massima di un file con i-node multi-livello|Es. 1]]).
> 2. **Limite della FAT.** Con voci della FAT da **16 bit** e blocchi da $4\,\text{KB}$, qual è la **massima dimensione di disco** indirizzabile? E con voci da **32 bit**?
> 3. **Bitmap vs free list.** Disco da $2\,\text{TB}$, blocchi da $4\,\text{KB}$, numeri di blocco da $32$ bit: dimensiona la **bitmap** e confrontala con la **free list** nel caso peggiore (riusa l'[[#Es. 3 — Bitmap vs free list per i blocchi liberi|Es. 3]]).
> 4. **Ricerca in directory.** Una directory ha $10\,000$ voci. Quanti confronti servono in media per trovare un file con ricerca **lineare**? E con una **tabella hash**? (vedi [[07 - File System#Ricerca: liste, hash e cache|ricerca: liste, hash e cache]]).

---
**Teoria di riferimento:** [[07 - File System]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
