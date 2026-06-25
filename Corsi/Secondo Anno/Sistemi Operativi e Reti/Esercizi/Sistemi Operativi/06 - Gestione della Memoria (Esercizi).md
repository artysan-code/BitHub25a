# Esercizi Svolti — Gestione della Memoria
Esercizi di calcolo su paginazione e memoria virtuale, svolti passo-passo, per lo scritto del **Modulo 1**. Teoria di riferimento: [[06 - Gestione della Memoria]].

> [!info] Verifica
> Tutti i conti e le simulazioni di page fault sono stati verificati numericamente. Le equivalenze in base 2 più usate: $4\,\text{KB} = 2^{12}$, $1\,\text{MB} = 2^{20}$, $1\,\text{GB} = 2^{30}$, $1\,\text{TB} = 2^{40}$.
## Es. 1 — Traduzione indirizzo virtuale → fisico
> [!quote] Consegna
> Sistema con spazio virtuale a **16 bit**, **16 pagine** da **4 KB** ($2^{12} = 4096$ byte), 8 frame fisici. Data la page table parziale sotto, tradurre gli indirizzi virtuali $8196$, $20500$, $32780$.
> | Pagina virtuale | Presente? | Frame |
> |---|---|---|
> | 2 | sì | 6 |
> | 5 | sì | 3 |
> | 8 | **no** (su disco) | — |

**Metodo**: con pagine da $4\,\text{KB}$ l'offset occupa i **12 bit bassi**; il numero di pagina sono i **4 bit alti**.
$$\text{n. pagina} = \left\lfloor \frac{\text{VA}}{4096} \right\rfloor, \qquad \text{offset} = \text{VA} \bmod 4096, \qquad \text{PA} = \text{frame} \times 4096 + \text{offset}.$$
**VA = 8196** → $8196 = 0010\,\underbrace{000000000100}_{\text{offset}}$:
- pagina $= \lfloor 8196 / 4096 \rfloor = 2$, offset $= 8196 - 2\cdot4096 = 4$.
- pagina 2 → frame 6. $\text{PA} = 6 \times 4096 + 4 = 24576 + 4 = \mathbf{24580}$.
**VA = 20500** → pagina $= \lfloor 20500/4096 \rfloor = 5$, offset $= 20500 - 5\cdot4096 = 20$:
- pagina 5 → frame 3. $\text{PA} = 3 \times 4096 + 20 = 12288 + 20 = \mathbf{12308}$.
**VA = 32780** → pagina $= \lfloor 32780/4096 \rfloor = 8$, offset $= 32780 - 8\cdot4096 = 12$:
- pagina 8 → **non presente** in memoria ⇒ **page fault**. Il SO carica la pagina da disco in un frame libero (o liberato con un algoritmo di sostituzione), aggiorna la page table e **riavvia** l'istruzione.

> [!note] L'offset non cambia mai
> Nella traduzione l'offset viene **copiato identico** dall'indirizzo virtuale a quello fisico: la MMU sostituisce solo il numero di pagina con il numero di frame. Questo è il motivo per cui pagine e frame hanno la **stessa** dimensione.
## Es. 2 — Dimensione della page table
> [!quote] Consegna
> Quante voci ha una page table a un livello con pagine da $4\,\text{KB}$ per spazi di indirizzi a **32 bit** e a **64 bit**? Se ogni voce occupa 4 byte, quanta memoria serve a 32 bit? Come si risolve il problema a 64 bit?

**Offset**: pagine da $4\,\text{KB} = 2^{12}$ → **12 bit** di offset.
**32 bit**: i bit per il numero di pagina sono $32 - 12 = 20$ → la tabella ha $2^{20} = 1\,048\,576$ voci. Con voci da 4 byte:
$$2^{20} \times 4\,\text{byte} = 2^{22}\,\text{byte} = \mathbf{4\,MB} \text{ per processo}.$$
È **fattibile** anche con pochi GB di RAM, ma va moltiplicato per ogni processo.
**64 bit**: servirebbero $2^{64-12} = 2^{52}$ voci ($\approx 4{,}5 \times 10^{15}$) → **impraticabile**. Soluzioni: in pratica i sistemi a 64 bit indirizzano solo **48 bit** ($2^{48} = 256\,\text{TB}$, sufficienti) e usano **page table multi-livello** (gerarchia walkata dalla MMU), così si allocano solo i livelli effettivamente usati.

> [!example] Multi-livello a 32 bit (2 livelli)
> Indirizzo a 32 bit diviso in `PT1` (10 bit) + `PT2` (10 bit) + offset (12 bit). La directory di primo livello ha $2^{10}$ voci; ciascuna punta a una tabella di secondo livello di $2^{10}$ voci; $2^{10} \times 2^{10} \times 2^{12} = 2^{32}$. **Vantaggio**: le tabelle di 2° livello non usate **non vengono allocate**. A 64 bit (48 effettivi) si usano 4 livelli da 9 bit: $2^9 \cdot 2^9 \cdot 2^9 \cdot 2^9 \cdot 2^{12} = 2^{48}$ (PGD→PUD→PMD→PTE).
## Es. 3 — Tempo di accesso effettivo (EAT) con TLB
> [!quote] Consegna
> Accesso al TLB: $1\,\text{ns}$; accesso alla memoria (RAM): $100\,\text{ns}$. Tasso di **hit** del TLB $h = 90\%$, page table a **un livello**. Calcolare il tempo di accesso effettivo (EAT). E con una page table a **due livelli**?

**Idea**: a ogni accesso si consulta sempre prima il TLB ($1\,\text{ns}$). Su **hit** si accede direttamente al dato; su **miss** si fa il *page table walk* (uno o più accessi RAM per leggere le voci) e **poi** l'accesso al dato.
**Page table a 1 livello**:
- TLB hit: $1 + 100 = 101\,\text{ns}$.
- TLB miss: $1 + \underbrace{100}_{\text{voce PT}} + \underbrace{100}_{\text{dato}} = 201\,\text{ns}$.
$$\text{EAT} = 0{,}9 \times 101 + 0{,}1 \times 201 = 90{,}9 + 20{,}1 = \mathbf{111\,ns}.$$
**Page table a 2 livelli** (due accessi RAM per il walk):
- TLB miss: $1 + 100 + 100 + 100 = 301\,\text{ns}$.
$$\text{EAT} = 0{,}9 \times 101 + 0{,}1 \times 301 = 90{,}9 + 30{,}1 = \mathbf{121\,ns}.$$

> [!note] Perché il TLB è decisivo
> Senza TLB ogni accesso costerebbe $200\,\text{ns}$ (1 livello) — il **doppio** del solo accesso al dato. Con un hit ratio del $90\%$ l'EAT scende a $111\,\text{ns}$, vicino al minimo teorico di $100\,\text{ns}$: è la **località di riferimento** a rendere efficiente la paginazione.
## Es. 4 — Simulazione algoritmi di sostituzione (FIFO, LRU, Ottimale)
> [!quote] Consegna
> Stringa di riferimenti `7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1` con **3 frame** (inizialmente vuoti). Contare i **page fault** con FIFO, LRU e Ottimale. (`F` = page fault, `.` = hit; le tre righe `f0/f1/f2` mostrano il contenuto dei frame.)

**FIFO** — si rimuove sempre la pagina caricata da più tempo:
```
ref : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
 f0 : 7 7 7 2 2 2 2 4 4 4 0 0 0 0 0 0 0 7 7 7
 f1 : . 0 0 0 0 3 3 3 2 2 2 2 2 1 1 1 1 1 0 0
 f2 : . . 1 1 1 1 0 0 0 3 3 3 3 3 2 2 2 2 2 1
 PF? : F F F F . F F F F F F . . F F . . F F F   → 15 page fault
```
**LRU** — si rimuove la pagina usata **meno di recente**:
```
ref : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
 f0 : 7 7 7 2 2 2 2 4 4 4 0 0 0 1 1 1 1 1 1 1
 f1 : . 0 0 0 0 0 0 0 0 3 3 3 3 3 3 0 0 0 0 0
 f2 : . . 1 1 1 3 3 3 2 2 2 2 2 2 2 2 2 7 7 7
 PF? : F F F F . F . F F F F . . F . F . F . .   → 12 page fault
```
**Ottimale** — si rimuove la pagina che sarà usata **più in là nel futuro** (irrealizzabile, ma è il limite inferiore):
```
ref : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
 f0 : 7 7 7 2 2 2 2 2 2 2 2 2 2 2 2 2 2 7 7 7
 f1 : . 0 0 0 0 0 0 4 4 4 0 0 0 0 0 0 0 0 0 0
 f2 : . . 1 1 1 3 3 3 3 3 3 3 3 1 1 1 1 1 1 1
 PF? : F F F F . F . F . . F . . F . . . F . .   → 9 page fault
```

> [!check] Risultato
> **FIFO 15 · LRU 12 · Ottimale 9**. LRU si avvicina molto all'ottimale sfruttando la località; FIFO è il peggiore perché può sfrattare pagine ancora "calde" solo perché vecchie.
## Es. 5 — Anomalia di Belady (FIFO)
> [!quote] Consegna
> Stringa `1 2 3 4 1 2 5 1 2 3 4 5`. Contare i page fault di **FIFO** con **3** frame e con **4** frame. Cosa si osserva?

- FIFO, **3 frame** → **9** page fault.
- FIFO, **4 frame** → **10** page fault.

> [!warning] Anomalia di Belady
> Con **più** frame i page fault **aumentano** (da 9 a 10): è l'**anomalia di Belady**. Sembra paradossale ma è possibile perché FIFO **non** è un *stack algorithm* (l'insieme di pagine in memoria con $n$ frame non è necessariamente contenuto in quello con $n+1$ frame). Gli algoritmi *stack* come **LRU** e **Ottimale** non soffrono di questa anomalia: con loro più frame implicano sempre $\le$ page fault.
## Es. 6 — Algoritmo Clock (seconda chance circolare)
> [!quote] Consegna
> Stringa `0 1 2 3 0 1 4 0 1 2 3 4`, **3 frame**, algoritmo **Clock**. Sul fault, se la pagina sotto la lancetta ha $R=1$ si azzera $R$ e si avanza; se $R=0$ si sostituisce. All'accesso a una pagina presente si imposta $R=1$.

Evoluzione (ogni frame è mostrato come `pagina(R)`; ⬆ = posizione della lancetta **dopo** l'operazione):

| Rif. | Esito | Frame dopo l'operazione | Lancetta su |
|---|---|---|---|
| 0 | fault | `0(1)` `–` `–` | slot 1 |
| 1 | fault | `0(1)` `1(1)` `–` | slot 2 |
| 2 | fault | `0(1)` `1(1)` `2(1)` | slot 0 |
| 3 | fault | `3(1)` `1(0)` `2(0)` | slot 1 |
| 0 | fault | `3(1)` `0(1)` `2(0)` | slot 2 |
| 1 | fault | `3(1)` `0(1)` `1(1)` | slot 0 |
| 4 | fault | `4(1)` `0(0)` `1(0)` | slot 1 |
| 0 | hit | `4(1)` `0(1)` `1(0)` | — |
| 1 | hit | `4(1)` `0(1)` `1(1)` | — |
| 2 | fault | `4(0)` `2(1)` `1(1)` | slot 2 |
| 3 | fault | `4(0)` `2(1)` `3(1)` | slot 0 |
| 4 | hit | `4(1)` `2(1)` `3(1)` | — |

Totale: **9 page fault** (e 3 hit). Al riferimento `3` la lancetta parte dallo slot 0 (`0(1)`): trova $R=1$, lo azzera e avanza; lo stesso per gli altri due, poi torna allo slot 0 (ora $R=0$) e sostituisce — è il caso in cui Clock degenera momentaneamente in FIFO.
## Es. 7 — Aging (NFU con scorrimento)
> [!quote] Consegna
> Quattro pagine, contatori a **8 bit** inizializzati a 0. A ogni *tick* di clock il contatore diventa `(R << 7) | (contatore >> 1)` (si inserisce il bit R a **sinistra** dopo aver shiftato a destra). Dati i bit R sotto, calcolare i contatori dopo 5 tick e indicare la pagina da rimuovere.

| Pagina | R ai tick 0–4 |
|---|---|
| 0 | 1 0 1 0 0 |
| 1 | 1 1 0 0 0 |
| 2 | 0 1 1 1 0 |
| 3 | 1 0 0 0 1 |

Evoluzione dei contatori (tick 0 → tick 4):
```
Pag 0:  10000000  01000000  10100000  01010000  00101000
Pag 1:  10000000  11000000  01100000  00110000  00011000
Pag 2:  00000000  10000000  11000000  11100000  01110000
Pag 3:  10000000  01000000  00100000  00010000  10001000
```
Contatori finali: P0 `00101000`, P1 `00011000`, P2 `01110000`, P3 `10001000`.

> [!check] Pagina rimossa
> Si rimuove quella con il **contatore più basso**: **Pagina 1** (`00011000`). Nota P3: pur essendo stata usata di recente (R=1 all'ultimo tick → bit più significativo a 1, `10001000`) ha il valore più **alto**, quindi è la più protetta. L'aging dà più peso ai riferimenti **recenti** (bit a sinistra) — è così che approssima LRU.
## Es. 8 — Buddy allocation
> [!quote] Consegna
> Memoria di **64 KB** gestita con **buddy system**. Servire la sequenza di richieste: A = 8 KB, B = 8 KB, C = 4 KB, D = 16 KB; poi liberare B, poi A. Mostrare divisioni e fusioni.

Ogni richiesta è arrotondata alla **potenza di 2** ≥ richiesta; un blocco si divide a metà finché si ottiene la taglia giusta.

| Evento | Stato della memoria (blocchi, KB) |
|---|---|
| iniziale | `[64 libero]` |
| **A=8** | divide 64→32→16→8: `[A:8][8][16][32]` |
| **B=8** | usa il buddy da 8 libero: `[A:8][B:8][16][32]` |
| **C=4** | divide il 16→8→4: `[A:8][B:8][C:4][4][32]` |
| **D=16** | usa il 32: divide 32→16: `[A:8][B:8][C:4][4][D:16][16]` |
| **libera B** | `[A:8][8][C:4][4][D:16][16]` — il buddy di B (dove sta A) è **occupato** → nessuna fusione |
| **libera A** | A e il blocco da 8 adiacente sono **buddy entrambi liberi** → fusione in `[16]`: `[16][C:4][4][D:16][16]` |

> [!note] Frammentazione interna del buddy
> Una richiesta di 5 KB occuperebbe un blocco da **8 KB** (potenza di 2 successiva), sprecando 3 KB: è la **frammentazione interna**. È il motivo per cui Linux mette lo **SLAB allocator** sopra il buddy, per ritagliare oggetti piccoli dentro i blocchi. Vedi [[06 - Gestione della Memoria#Buddy allocation (Linux)]].
## Es. 9 — Page table a due livelli: scomposizione dell'indirizzo
> [!quote] Consegna
> Sistema a **32 bit**, pagine da **4 KB**, page table a **due livelli** con $10 + 10 + 12$ bit (`PT1` | `PT2` | offset). Scomporre l'indirizzo virtuale $\text{VA} = \mathtt{0x00403004}$ in indice di primo livello, indice di secondo livello e offset, e descrivere il *page table walk*.

**Maschere dei campi** (dai 32 bit, dall'alto): `PT1` = bit 31–22 (10 bit), `PT2` = bit 21–12 (10 bit), offset = bit 11–0 (12 bit). In binario $\mathtt{0x00403004} = \mathtt{0000000001\,0000000011\,000000000100}$:
$$\text{offset} = \text{VA} \bmod 2^{12} = \mathtt{0x004} = 4; \quad \text{PT2} = \left\lfloor \frac{\text{VA}}{2^{12}} \right\rfloor \bmod 2^{10} = 3; \quad \text{PT1} = \left\lfloor \frac{\text{VA}}{2^{22}} \right\rfloor = 1.$$
**Page table walk** della [[06 - Gestione della Memoria#La MMU e la page table|MMU]]:
1. legge la voce **1** della directory di primo livello → ottiene l'indirizzo della tabella di secondo livello;
2. in quella tabella legge la voce **3** → ottiene il numero di frame fisico;
3. concatena `frame × 4096 + offset` (l'**offset 4** resta invariato, come nell'[[#Es. 1 — Traduzione indirizzo virtuale → fisico|Es. 1]]).

> [!check] Verifica e vantaggio
> Ricomponendo: $(1 \ll 22) \,|\, (3 \ll 12) \,|\, 4 = \mathtt{0x00403004}$ ✓. Con due livelli si caricano **solo** le tabelle di secondo livello effettivamente usate: se un processo usa poca memoria, la gran parte delle $2^{10}$ tabelle di 2° livello non viene mai allocata (vedi [[#Es. 2 — Dimensione della page table|Es. 2]]).
## Da svolgere
Esercizi senza soluzione. Equivalenze: $4\,\text{KB} = 2^{12}$, $1\,\text{GB} = 2^{30}$, $1\,\text{TB} = 2^{40}$. Teoria in [[06 - Gestione della Memoria]].

> [!todo] Da svolgere
> 1. **Traduzione con page fault.** Spazio virtuale a **16 bit**, pagine da **2 KB**. Page table: pagina 0→frame 4, pagina 1→frame 7, pagina 3→frame 2, pagina 5→assente. Traduci gli indirizzi virtuali $100$, $2148$, $7000$, $10300$; segnala i page fault.
> 2. **EAT con TLB a 3 livelli.** TLB $1\,\text{ns}$, RAM $80\,\text{ns}$, hit ratio $95\%$, page table a **3 livelli**. Calcola l'[[#Es. 3 — Tempo di accesso effettivo (EAT) con TLB|EAT]].
> 3. **LRU vs Ottimale.** Stringa `1 2 3 4 1 2 5 1 2 3 4 5` con **4 frame**: conta i page fault con **LRU** e con **Ottimale** e confronta (riusa la tecnica dell'[[#Es. 4 — Simulazione algoritmi di sostituzione (FIFO, LRU, Ottimale)|Es. 4]]).
> 4. **Working set / thrashing.** Spiega cosa accade quando la somma dei working set dei processi supera i frame disponibili. Cos'è il *thrashing* e come lo si mitiga?
> 5. **Buddy.** Memoria da **128 KB**: servi A = 10 KB, B = 30 KB, C = 12 KB, poi libera A; mostra divisioni, taglie arrotondate e frammentazione interna (riusa l'[[#Es. 8 — Buddy allocation|Es. 8]]).

---
**Teoria di riferimento:** [[06 - Gestione della Memoria]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
