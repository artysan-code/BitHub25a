# Esercizi Svolti — Input/Output
Esercizi di calcolo sull'I/O (tempi di trasferimento, overhead di interrupt, polling vs DMA), svolti passo-passo, per lo scritto del **Modulo 1**. Teoria di riferimento: [[08 - Input Output]].
> [!info] Verifica
> Tutti i tempi e i conteggi sono stati verificati numericamente. Le **velocità di trasferimento** sono quelle della tabella [[08 - Input Output#Velocità dei dispositivi|Velocità dei dispositivi]] della nota. Per i tassi di trasferimento dei dispositivi si usa la convenzione **decimale** dei costruttori ($1\,\text{MB} = 10^6$ byte, $1\,\text{GB} = 10^9$ byte): è quella in cui sono espressi i valori di targa (USB, SATA, Ethernet…).
## Es. 1 — Tempo di trasferimento su bus diversi
> [!quote] Consegna
> Si deve trasferire un file da **3 GB** ($3000\,\text{MB}$). Quanto tempo impiega, al netto delle latenze, su: **USB 2.0** ($60\,\text{MB/s}$), **Gigabit Ethernet** ($125\,\text{MB/s}$), **SATA 3** ($600\,\text{MB/s}$), **USB 3.0** ($625\,\text{MB/s}$)?
**Metodo.** Il tempo di trasferimento ideale è il rapporto tra quantità di dati e velocità del canale:
$$t = \frac{\text{dimensione}}{\text{velocità}}.$$
Applicando la formula con i valori di targa:
| Canale | Velocità | $t = 3000\,\text{MB} / \text{velocità}$ |
|---|---|---|
| USB 2.0 | $60\,\text{MB/s}$ | $50{,}0\,\text{s}$ |
| Gigabit Ethernet | $125\,\text{MB/s}$ | $24{,}0\,\text{s}$ |
| SATA 3 | $600\,\text{MB/s}$ | $5{,}0\,\text{s}$ |
| USB 3.0 | $625\,\text{MB/s}$ | $4{,}8\,\text{s}$ |

> [!check] Osservazione
> Lo stesso dato impiega da $4{,}8\,\text{s}$ a $50\,\text{s}$ a seconda del canale: un fattore **$>10\times$** tra USB 2.0 e USB 3.0. È la ragione per cui l'I/O è quasi sempre il **collo di bottiglia** rispetto alla CPU, e per cui il software di I/O punta a tenere il canale **saturo** (buffering, DMA) invece di lasciarlo in attesa. Questi sono tempi **ideali**: la velocità reale è ridotta da overhead di protocollo, latenza di *seek* sui dischi meccanici e contesa sul bus.
## Es. 2 — I/O guidato da interrupt vs DMA (overhead)
> [!quote] Consegna
> Si trasferisce un blocco da **32 KB** ($32\,768$ byte) con parole da **4 byte**. Confrontare il numero di interrupt e l'overhead di gestione con due tecniche: **I/O guidato dagli interrupt** (un interrupt per ogni parola trasferita) e **DMA** (un solo interrupt a fine blocco). Si assuma che la gestione di un interrupt costi **$2\,\mu\text{s}$**.
**Numero di parole nel blocco:**
$$\frac{32\,768\,\text{B}}{4\,\text{B/parola}} = 8192 \text{ parole}.$$
**I/O guidato dagli interrupt** — la CPU viene interrotta a ogni parola pronta:
$$8192 \text{ interrupt} \times 2\,\mu\text{s} = 16\,384\,\mu\text{s} \approx \mathbf{16{,}4\ ms} \text{ di solo overhead di interrupt}.$$
**DMA** (modalità *burst*) — il [[08 - Input Output#^dma-def|controller DMA]] trasferisce l'intero blocco e interrompe la CPU **una sola volta**, a fine trasferimento:
$$1 \text{ interrupt} \times 2\,\mu\text{s} = \mathbf{2\ \mu s}.$$
Il rapporto di overhead è $8192 : 1$.
> [!check] Perché esiste il DMA
> Con l'I/O guidato dagli interrupt la CPU paga un context-switch **per ogni parola**: per un blocco di 32 KB sono $16{,}4\,\text{ms}$ buttati in puro overhead, durante i quali non fa lavoro utile. Il [[08 - Input Output#DMA|DMA]] sposta il trasferimento dato-per-dato sul controller e lascia alla CPU **solo** l'impostazione iniziale e l'interrupt finale: è il motivo per cui ogni controller moderno integra un *motore DMA* (*bus mastering*).
## Es. 3 — Polling: quando spreca la CPU
> [!quote] Consegna
> Un disco **SATA 3** ($600\,\text{MB/s}$) serve blocchi da **4 KB**. (a) Quanto dura il trasferimento di un blocco? (b) Se la CPU attende in [[08 - Input Output#^polling|polling]] (*busy waiting*) per tutta la durata, quanto tempo di CPU spreca per blocco? (c) Per una **tastiera** ($10\,\text{byte/s}$), perché il polling continuo è ancora peggio?
**(a)** Tempo di trasferimento del blocco:
$$t = \frac{4096\,\text{B}}{600 \times 10^6\,\text{B/s}} \approx 6{,}83\,\mu\text{s}.$$
**(b)** In polling la CPU interroga ciclicamente il bit di stato senza fare altro: spreca **tutti** i $\approx 6{,}83\,\mu\text{s}$ per blocco. Su un flusso di molti blocchi questo tempo si moltiplica e la CPU resta inchiodata all'attesa invece di eseguire altri processi.
**(c)** La tastiera produce in media **un evento ogni $100\,\text{ms}$** ($1/10\,\text{s}$). Pollarla di continuo significa eseguire milioni di letture del registro di stato tra un tasto e l'altro, **tutte inutili**: la frazione di CPU sprecata tende al **100%** a fronte di lavoro utile quasi nullo.
> [!note] Polling vs interrupt — la regola
> Il polling conviene **solo** se il dispositivo è velocissimo e quasi sempre pronto (l'attesa è brevissima e l'overhead di un interrupt non varrebbe la pena). Per dispositivi **lenti o sporadici** (tastiera, mouse, rete) si usano gli **interrupt**: la CPU lancia l'operazione, va a fare altro e viene avvisata solo al completamento. Vedi [[08 - Input Output#Le tre tecniche di I/O|le tre tecniche di I/O]].
## Es. 4 — Frequenza di interrupt di una scheda di rete
> [!quote] Consegna
> Una **Gigabit Ethernet** ($125\,\text{MB/s}$) riceve pacchetti e genera **un interrupt per pacchetto**. Quanti interrupt al secondo deve gestire la CPU con pacchetti da **1500 byte** (MTU tipica) e con pacchetti minimi da **64 byte**?
**Pacchetti (= interrupt) al secondo** $= \dfrac{\text{velocità}}{\text{dimensione pacchetto}}$:
$$\text{1500 B:}\quad \frac{125 \times 10^6}{1500} \approx \mathbf{83\,333 \ interrupt/s}.$$
$$\text{64 B:}\quad \frac{125 \times 10^6}{64} \approx \mathbf{1\,953\,125 \ interrupt/s}.$$
> [!warning] L'*interrupt storm*
> Con pacchetti piccoli a piena velocità si superano i **due milioni di interrupt al secondo**: se ciascuno costa anche solo $1\,\mu\text{s}$ di gestione, la CPU passerebbe **oltre il 100% del tempo** solo a servire interrupt — *livelock* da interrupt, nessun lavoro utile. Per questo le NIC moderne usano l'**interrupt coalescing** (raggruppano più pacchetti sotto un solo interrupt) e meccanismi come **NAPI** che, sotto carico, passano temporaneamente al [[08 - Input Output#^polling|polling]]. *(Coalescing/NAPI: extra, non da slide.)*
## Da svolgere
Esercizi senza soluzione, per esercitarsi. I valori si trovano nella tabella [[08 - Input Output#Velocità dei dispositivi|Velocità dei dispositivi]].
> [!todo] Da svolgere
> 1. **Confronto di canali.** Quanto tempo serve a trasferire un film **Blu-ray da 25 GB** su **USB 2.0**, su **Gigabit Ethernet** e su **SSD NVMe PCIe Gen 3.0** ($3{,}5\,\text{GB/s}$)? Di quanti minuti è la differenza tra il più lento e il più veloce?
> 2. **Saturazione del bus.** Un **bus PCIe 3.0 single lane** ($985\,\text{MB/s}$) deve servire contemporaneamente un disco **SATA 3** ($600\,\text{MB/s}$) a piena velocità e una **Gigabit Ethernet** ($125\,\text{MB/s}$): la banda del bus basta? Di quanto?
> 3. **Overhead di interrupt.** Ripeti l'Es. 2 con un blocco da **1 MB** e parole da **8 byte**, gestione interrupt da $1{,}5\,\mu\text{s}$: quanti ms di overhead con l'I/O guidato dagli interrupt? E con il DMA?
> 4. **Soglia polling/interrupt.** Un dispositivo è pronto dopo $0{,}5\,\mu\text{s}$ e la gestione di un interrupt costa $2\,\mu\text{s}$: conviene il polling o l'interrupt? E se il dispositivo è pronto dopo $5\,\text{ms}$?
> 5. **DMA e *cycle stealing*.** Spiega a parole perché, nella modalità *cycle stealing*, la CPU rallenta ma non si ferma del tutto durante un trasferimento DMA, mentre in *burst mode* resta bloccata (vedi [[08 - Input Output#DMA|DMA]]).
---
**Teoria di riferimento:** [[08 - Input Output]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
