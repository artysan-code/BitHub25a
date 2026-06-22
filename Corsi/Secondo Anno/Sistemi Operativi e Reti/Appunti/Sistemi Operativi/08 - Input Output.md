# Input/Output
Oltre a fornire astrazioni come [[03 - Processi e Thread|processi e thread]], [[06 - Gestione della Memoria|spazi di indirizzi]] e [[07 - File System|file]], il sistema operativo **controlla tutti i dispositivi di I/O**: invia comandi, intercetta gli [[#Interrupt|interrupt]], gestisce gli errori. Il codice dedicato all'I/O è una **parte significativa** del sistema operativo.
> [!quote] Le due funzioni del sistema operativo verso l'I/O
> 1. **Controllo dei dispositivi**: invio di comandi, intercettazione degli interrupt, gestione degli errori.
> 2. **Interfaccia uniforme**: offrire ai programmi un'interfaccia *semplice e uniforme*, idealmente identica per tutti i dispositivi (**indipendenza dal dispositivo**, vedi [[#^device-independence]]).

> [!info] Approfondimento — Architettura dei Sistemi di Elaborazione
> Questo intero argomento è trattato, dalla prospettiva architetturale e con lo stesso testo (Tanenbaum), nel corso del primo anno: [[5 - Input & Output]]. La struttura della **CPU**, dei registri, del **bus** e della gerarchia di memoria è in [[2 - Organizzazione dei sistemi di calcolo]].
## Principi dell'hardware di I/O
L'hardware di I/O si guarda da prospettive diverse: gli **ingegneri elettronici** lo vedono come componenti fisici (chip, cavi, alimentatori, motori); i **programmatori** sono interessati all'**interfaccia software** (comandi accettati, funzioni eseguibili, errori possibili). Il corso si concentra sulla **programmazione** dei dispositivi, non sulla loro progettazione o costruzione.
### Dispositivi a blocchi e a caratteri
I dispositivi di I/O si dividono in due grandi categorie.
- **Dispositivi a blocchi**: memorizzano informazioni in **blocchi di dimensione fissa** (tipicamente da $512$ a $32\,768$ byte), ciascuno con un proprio indirizzo. Ogni blocco può essere letto o scritto **indipendentemente** dagli altri. Esempi: dischi rigidi magnetici, SSD, unità a nastro. ^blocchi
- **Dispositivi a caratteri**: gestiscono un **flusso di caratteri** senza struttura a blocchi, **non indirizzabili** e senza operazioni di ricerca (*seek*). Esempi: stampanti, interfacce di rete, mouse. ^caratteri

La classificazione non è perfetta: alcuni dispositivi non vi rientrano (il **clock** genera solo interrupt a intervalli; gli schermi mappati in memoria e i touch screen sono casi ibridi). Resta però utile perché rende il software del SO **indipendente dal tipo di dispositivo**: il [[07 - File System|file system]], ad esempio, gestisce solo *dispositivi a blocchi astratti*, lasciando ai livelli inferiori le specificità.
### Velocità dei dispositivi
I dispositivi di I/O variano **enormemente** in velocità di trasferimento, e questo crea sfide per il software di gestione.
| Dispositivo | Velocità di trasferimento |
|---|---|
| Tastiera | 10 byte/s |
| Mouse | 100 byte/s |
| Modem 56 K | 7 KB/s |
| Bluetooth 5 BLE | 256 KB/s |
| Scanner 300 dpi | 1 MB/s |
| Videocamera digitale | 3,5 MB/s |
| Wireless 802.11n | 37,5 MB/s |
| USB 2.0 | 60 MB/s |
| Disco Blu-ray 16x | 72 MB/s |
| Gigabit Ethernet | 125 MB/s |
| Disco SATA 3 | 600 MB/s |
| USB 3.0 | 625 MB/s |
| Bus PCIe 3.0 (single lane) | 985 MB/s |
| Wireless 802.11ax | 1,25 GB/s |
| SSD NVMe PCIe Gen 3.0 (lettura) | 3,5 GB/s |
| USB 4.0 | 5 GB/s |
| PCI Express 6.0 | 126 GB/s |
### Controller dei dispositivi
Un dispositivo di I/O è composto da una **parte meccanica** (il dispositivo vero e proprio) e da una **parte elettronica**.
> [!quote] Definizione — Controller del dispositivo
> Il **controller** (o **adattatore**) è la parte elettronica del dispositivo. È spesso integrato nella scheda madre o realizzato come scheda aggiuntiva su slot **PCIe**, e può gestire **più dispositivi identici** tramite i suoi connettori.

L'interfaccia tra controller e sistema segue **standard** ufficiali (ANSI, IEEE, ISO) o *de facto* (SATA, SCSI, USB, ThunderBolt), così che dispositivi e controller di aziende diverse risultino compatibili. A basso livello il dispositivo emette un **flusso seriale di bit** che inizia con un *preambolo*, prosegue con i dati del settore e termina con una **checksum**/codice di correzione (**ECC**). Il compito del controller è **convertire** questo flusso in blocchi di byte, **correggere** gli errori e **trasferire** i dati in memoria principale. Senza il controller, il programmatore dovrebbe gestire dettagli complessi (ad esempio la modulazione di ogni singolo pixel su uno schermo).
### Connettori e bus: dalla porta parallela a USB
La vecchia **porta parallela** (DB-25 a 25 pin, o Centronics a 36 pin) trasmetteva più bit *simultaneamente* su canali separati: pin 1-8 per i **dati** (D0-D7), pin 9-16 per **controllo e stato** (select, line feed, error, busy, ack…), pin 17-25 per **masse e alimentazione**. L'ha sostituita la porta **USB** (*Universal Serial Bus*), interfaccia seriale standardizzata che trasporta **dati e alimentazione** insieme: 4 contatti tipici (Vcc +5 V, D−, D+, GND), codifica **NRZI** e formato a pacchetti. Le versioni vanno da USB 1.0 ($12$ Mbit/s) a USB 3.2 Gen 2×2 ($20$ Gbit/s), con connettori Type-A, Type-B e il reversibile **Type-C**; il bus è **retrocompatibile** e *plug-and-play*.
### Dentro un disco: PCB, MCU e VCM
Anche un disco è "dispositivo + controller". Sul suo **PCB** (*Printed Circuit Board*, con connettori SATA e di alimentazione) trovano posto:
- l'**MCU** (*Micro Controller Unit*), il chip più grande, che include una **CPU** e un canale di lettura/scrittura per convertire i segnali analogici in digitali;
- la **cache** (chip DDR SDRAM: un chip da 32 MB indica una cache teorica di 32 MB);
- il controller **VCM** (*Voice Coil Motor*), che comanda rotazione del disco e movimento delle testine, consumando la **maggior parte dell'energia** del PCB;
- un chip **flash** col firmware d'avvio, **sensori di shock** e **diodi TVS** (*Transient Voltage Suppression*) che proteggono da urti e sovratensioni. Il sensore di shock rileva urti eccessivi e invia segnali direttamente al **controller VCM** per proteggere le testine; i diodi TVS si **sacrificano** assorbendo i picchi di tensione per proteggere il resto del circuito.
## Come comunicano CPU e dispositivo
Ogni controller ha dei **registri** con cui la CPU dialoga (scrivendovi invia comandi, leggendoli ne conosce lo stato) e spesso un **buffer di dati** (es. la RAM video usata per disegnare sullo schermo). Esistono **tre approcci** per accedere a registri e buffer: porte di I/O, memoria mappata e ibrido.
### I/O mappato sulle porte (PMIO)
Nel **port-mapped I/O** ogni registro di controllo ha un **numero di porta** associato (intero a 8 o 16 bit). Le porte formano uno **spazio di indirizzi separato** dalla memoria, accessibile **solo dal sistema operativo** tramite istruzioni speciali:
- `IN REG, PORT` — la CPU legge il registro `PORT` e salva in `REG`;
- `OUT PORT, REG` — la CPU scrive il contenuto di `REG` nel registro di controllo.

Lo spazio delle porte e quello della memoria sono **distinti e non correlati**: `IN R0,4` legge dalla **porta** 4, `MOV R0,4` legge dalla **parola di memoria** 4 — lo stesso numero riferisce spazi diversi. Approccio molto usato nei vecchi mainframe (es. IBM 360).
### I/O mappato in memoria (MMIO)
Introdotto col **PDP-11**, il **memory-mapped I/O** assegna a ogni registro di controllo un **indirizzo di memoria univoco**, mappandolo nello *spazio della memoria*.
> [!info] Vantaggi del MMIO
> - **Niente istruzioni speciali**: non servono `IN`/`OUT`.
> - **Registri come variabili C**: si possono scrivere **driver interamente in C**, senza assembly.
> - **Protezione semplificata**: il SO usa la gestione della memoria per rendere gli indirizzi dei registri accessibili **solo al kernel**, e può eseguire i driver in spazi di indirizzi separati (più sicurezza, kernel più piccolo).

> [!warning] MMIO e cache: rischio di ciclo infinito
> Se un registro di controllo finisce **in cache**, la CPU continua a leggere il valore *vecchio* e non si accorge che il **dispositivo** lo ha modificato. Un ciclo `while` che attende il cambiamento del registro può così non terminare mai → **ciclo infinito**. Occorre **disabilitare selettivamente la cache** per le pagine dedicate ai dispositivi: quegli accessi non saranno ottimizzati e quindi più lenti.

Con MMIO tutti i moduli di memoria e i dispositivi devono **esaminare ogni riferimento alla memoria**. Su architetture con bus multipli (memoria, PCIe, SCSI, USB) servono soluzioni: **memory-first** (la richiesta va prima alla memoria, e solo se fallisce agli altri bus — semplice ma con più latenza per l'I/O) oppure **bus snooping** (un dispositivo "spia" il bus e reindirizza gli indirizzi destinati all'I/O — più veloce ma con più complessità hardware).
### Approccio ibrido (PMIO + MMIO)
Combina i due metodi: la **configurazione** iniziale del dispositivo avviene via **PMIO** (`IN`/`OUT`), mentre l'**accesso ai dati** ad alta velocità (schede grafiche, controller di rete) avviene via **MMIO** (`LOAD`/`STORE`). Vantaggi: flessibilità, ottimizzazione delle prestazioni, **compatibilità legacy**. Svantaggi: maggiore complessità e il fatto che alcune CPU moderne (es. **ARM**) **non supportano PMIO**. Esempio pratico su **x86**: i dispositivi **PCIe** si configurano tramite le porte `0xCF8`/`0xCFC` e poi si accede ai loro registri via MMIO.
### Dal modello astratto al chipset reale
Il MMIO definisce un **modello di indirizzamento** (un solo spazio di indirizzi), ma l'hardware reale deve mantenere **alte prestazioni** sulla memoria *e* supportare **molti dispositivi eterogenei**: un bus unico non scala né in banda né in latenza. La soluzione storica è il **chipset a due livelli**.
- **Northbridge** (*Memory Controller Hub*): interposto tra **CPU e memoria**, gestisce gli accessi alla **RAM**, il collegamento agli acceleratori grafici (AGP/PCIe) e la **decodifica primaria degli indirizzi** (decide se un indirizzo è memoria reale o **I/O mappato in memoria** da inoltrare). Caratteristiche: **latenza minima**, **banda elevata**, impatto diretto sulle prestazioni.
- **Southbridge** (*I/O Controller Hub*): gestisce l'I/O — IDE, SATA, USB, Ethernet, audio, CMOS. Dal Southbridge parte un **LPC Bus** (*Low Pin Count*) a cui sono connessi il chip **Super I/O** (che gestisce porta seriale, porta parallela, controller floppy, tastiera e mouse) e la **Flash ROM** contenente il **BIOS**.

Nei **sistemi moderni** il Northbridge è **integrato nella CPU** e il Southbridge diventa il **PCH** (*Platform Controller Hub*): cambia il silicio, **non il modello concettuale**. Il MMIO resta *un solo spazio di indirizzi*; i bridge sono solo l'*instradamento fisico*.
## In attesa dell'I/O: il polling
Inviato un comando, l'operazione richiede **tempo**. La maggior parte dei dispositivi offre un **bit di stato** nei propri registri per segnalare il completamento (ed eventualmente un codice di errore). Il SO può **interrogare** ciclicamente questo bit: questa tecnica si chiama **polling** (o *busy waiting*). ^polling

È una buona soluzione? **No, se la CPU ha altro da fare**: il polling la tiene occupata a vuoto. Da qui nascono le alternative — gli **interrupt** e il **DMA**.
## DMA
Il **DMA** (*Direct Memory Access*) permette di trasferire dati tra **dispositivo e memoria** senza che la CPU debba spostare ogni byte manualmente, riducendo lo spreco di tempo della CPU. ^dma-def
> [!quote] Definizione — Controller DMA
> Il **controller DMA** è un componente (sulla scheda madre o integrato nel controller del dispositivo) dotato di registri per l'**indirizzo di memoria**, il **conteggio dei byte** e il **controllo** (direzione del trasferimento, unità, ecc.). Può gestire trasferimenti verso **più dispositivi**.

Senza DMA, il controller del disco legge i dati nel proprio buffer, controlla gli errori e genera un interrupt; poi è il **SO a copiare** i dati in memoria. Con il DMA la CPU si limita a impostare il trasferimento.
> [!example] I quattro passi di un trasferimento DMA (lettura da disco)
> 1. La **CPU programma** il controller DMA (indirizzo, contatore, controllo) e invia il comando al controller del disco.
> 2. Il **DMA richiede** la lettura al controller del disco.
> 3. Il controller del disco **scrive i dati direttamente in memoria**.
> 4. Il controller del disco invia una **conferma** al DMA. I passi 2-4 si ripetono fino al completamento; al termine il DMA invia un **interrupt** alla CPU.

Le **modalità di interazione col bus** sono: **cycle stealing** (il DMA trasferisce una parola per volta, "rubando" cicli alla CPU che rallenta lievemente ma condivide il bus); **burst mode** (il DMA prende il controllo completo del bus per più trasferimenti — efficiente ma blocca la CPU); **fly-by mode** (trasferimento diretto dispositivo→memoria senza intermediari). Il DMA usa **indirizzi fisici**, che il SO deve convertire. Molti dischi hanno un **buffer interno** per verificare la checksum e gestire il flusso costante di bit, evitando il *buffer overrun*.
> [!info] Dove sta il DMA nei sistemi moderni?
> Guardando una scheda madre si vedono CPU, Northbridge/Southbridge e i controller, ma **il DMA non si vede**. Storicamente esisteva un controller dedicato (es. **Intel 8237**); oggi il DMA **non è un componente fisico unico**, bensì una **funzionalità** — il *bus mastering* — implementata **dentro i controller dei dispositivi** (SATA, USB, NIC, GPU) e supportata dal chipset. Ogni controller moderno contiene un **motore DMA**, può diventare **bus master** e legge/scrive direttamente la RAM. I ruoli: la **CPU** programma il trasferimento (via MMIO), il **controller** lo esegue, il **chipset** arbitra e instrada l'accesso alla memoria, la **CPU** riceve un interrupt a fine operazione.
## Interrupt
Gli **interrupt** sono uno dei tre modi in cui un evento comunica con la CPU.
- **Trap**: azione *deliberata* del programma, come una [[02 - Concetti di Base e Strutture|chiamata di sistema]].
- **Fault/Eccezione**: azione *non deliberata*, come una divisione per zero o un *segmentation fault*.
- **Interrupt hardware**: segnale inviato da un **dispositivo** (stampante, rete…) alla CPU tramite una linea del bus, gestito dal **controller degli interrupt** sulla scheda madre.
### Processo di gestione degli interrupt
Il controller assegna un **numero** alle linee di indirizzo per indicare *quale* dispositivo richiede attenzione e segnala l'interruzione alla CPU. La CPU **interrompe** il task corrente e usa quel numero come **indice nel vettore degli interrupt**, da cui ottiene il nuovo *program counter* (l'inizio della **procedura di servizio**, ISR). La ISR **conferma** l'interrupt scrivendo su una porta del controller, così da evitare *race condition* tra interrupt quasi simultanei.
### Salvataggio dello stato
Al minimo va salvato il **program counter** per riavviare il processo interrotto (alcune CPU salvano *tutti* i registri). Le informazioni si salvano nei **registri interni** (rischio di sovrascrittura e tempi morti) o sullo **stack**:
- **stack corrente** (del processo utente): rischio di puntatori non leciti e *page fault*;
- **stack del kernel**: più sicuro, ma comporta cambio di contesto della [[06 - Gestione della Memoria|MMU]] e invalidazione di **cache** e **TLB** → *overhead*.
### Interrupt precisi vs imprecisi
Le CPU moderne usano **pipeline** e architetture **superscalari**, avviando più istruzioni prima che le precedenti siano completate: al momento di un interrupt molte istruzioni vicine al PC possono essere in **stati di completamento diversi**.
> [!quote] Definizione — Interrupt preciso e impreciso
> Un interrupt è **preciso** se lascia la macchina in uno stato ben definito: il **PC è salvato** in un luogo noto, **tutte** le istruzioni prima del PC sono completate, **nessuna** dopo è stata eseguita, e lo **stato dell'istruzione puntata** dal PC è noto. È **impreciso** quando più istruzioni vicine al PC sono in stati diversi: la CPU deve "vomitare" molto stato interno sullo stack.

L'architettura **x86** garantisce interrupt **precisi** (per compatibilità e prevedibilità), al costo di una logica interna complessa: la CPU **annulla** gli effetti delle istruzioni transitorie eseguite dopo il PC. Gli interrupt imprecisi rendono il SO più lento e complesso e hanno **implicazioni di sicurezza**, perché le istruzioni transitorie annullate lasciano tracce nella **microarchitettura** sfruttabili da un attaccante.
## Principi del software di I/O
Prima gli **obiettivi** del software di I/O, poi i **modi** in cui il SO può gestirlo, infine la sua **organizzazione a livelli**.
### Obiettivi del software di I/O
- **Indipendenza dal dispositivo**: scrivere programmi che accedono a *qualsiasi* dispositivo senza specificarne il tipo in anticipo (un programma che legge un file deve funzionare con disco, SSD o penna USB). ^device-independence
- **Denominazione uniforme**: nomi di file/dispositivi come semplici stringhe, indipendenti dal dispositivo. Non vogliamo digitare `ST6NM04` per il primo disco: `/dev/sda` è meglio, `/mnt/movies` ancora meglio. In UNIX i dispositivi sono integrati nella gerarchia del [[07 - File System|file system]].
- **Gestione degli errori**: vanno gestiti il **più vicino possibile all'hardware** (controller o driver); gli **errori transitori** (es. di lettura) spesso scompaiono **ripetendo** l'operazione.
- **Trasferimenti sincroni vs asincroni**: l'I/O fisico è per lo più **asincrono** (guidato dagli interrupt), ma i programmi utente sono più semplici se l'I/O è **bloccante** (sincrono). Il SO fa *sembrare* bloccanti le operazioni asincrone, pur offrendo l'I/O asincrono per le applicazioni ad alte prestazioni; il SO deve inoltre **gestire il DMA**.
- **Buffering**: spesso i dati non vanno direttamente alla destinazione finale (un pacchetto di rete va analizzato prima di sapere quale applicazione lo userà; un segnale audio va pre-caricato in un buffer per evitare interruzioni). Il buffering influisce sulle prestazioni, soprattutto con vincoli *real-time*.
- **Dispositivi condivisibili vs dedicati**: dischi e SSD sono condivisibili da più utenti; stampanti e scanner sono tipicamente **dedicati**. Il SO deve gestire entrambe le categorie per evitare problemi come i *deadlock*. ^dedicati
### Le tre tecniche di I/O
Tre modi di realizzare l'I/O: **programmato**, **guidato dagli interrupt**, **con DMA**.
#### I/O programmato
Nell'**I/O programmato** la CPU gestisce **interamente** il trasferimento. Esempio: stampare la stringa `"ABCDEFGH"` su una stampante. Il SO copia il buffer dallo spazio utente al kernel e invia i caratteri **uno alla volta**, controllando in `polling` il registro di stato (vedi [[#^polling]]) finché la stampante è pronta.
```c
copy_from_user(buffer, p, count);          /* p è il buffer del kernel */
for (i = 0; i < count; i++) {              /* ripeti per tutti i caratteri */
    while (*printer_status_reg != READY);  /* attendi finché lo stato è READY */
    *printer_data_register = p[i];         /* invia in output il carattere */
}
return_to_user();
```
**Svantaggio**: occupa la CPU **a tempo pieno** facendo polling. È efficace solo quando l'elaborazione di un carattere è **breve** o in sistemi **embedded** dove la CPU non ha altro da fare.
#### I/O guidato dagli interrupt
Una stampante a 100 caratteri/s impiega $10$ ms per carattere: troppo per tenere ferma la CPU in busy waiting. Si usano allora gli **interrupt**: la CPU invia il primo carattere, poi chiama lo **scheduler** ([[05 - Scheduling]]) per eseguire altri [[03 - Processi e Thread|processi]] mentre il processo di stampa resta **bloccato**; quando la stampante è pronta genera un **interrupt**.
```c
/* codice eseguito al momento della syscall di stampa */
copy_from_user(buffer, p, count);
enable_interrupts();
while (*printer_status_reg != READY);
*printer_data_register = p[0];   /* invia il primo carattere */
scheduler();                     /* passa il controllo a un altro processo */
```
```c
/* procedura di servizio dell'interrupt (ISR) della stampante */
if (count == 0) {
    unblock_user();              /* tutti i caratteri stampati: sblocca l'utente */
} else {
    *printer_data_register = p[i];
    count = count - 1;
    i = i + 1;
}
acknowledge_interrupt();
return_from_interrupt();
```
**Problema**: si genera un **interrupt per ogni carattere**, sprecando tempo di CPU.
#### I/O con DMA
Con il **DMA** è il controller a inviare i caratteri uno alla volta, riducendo gli interrupt **da uno per carattere a uno per buffer** e liberando la CPU durante il trasferimento.
```c
/* (a) avvio del trasferimento */
copy_from_user(buffer, p, count);
set_up_DMA_controller();
scheduler();                     /* la CPU fa altro mentre il DMA trasferisce */
```
```c
/* (b) gestione dell'interrupt di fine trasferimento */
acknowledge_interrupt();
unblock_user();
return_from_interrupt();
```
**Limite**: il controller DMA è spesso **più lento della CPU**; se la CPU non ha altro da fare, l'I/O guidato dagli interrupt (o anche quello programmato) può risultare preferibile. Nella maggior parte dei casi, però, il DMA conviene.
## I quattro livelli del software di I/O
Il software di I/O è organizzato in **quattro livelli**, ciascuno con funzione e interfaccia ben definite. Dal basso verso l'alto, sopra l'**hardware**:
> [!info] I livelli del software di I/O (dal basso)
> | Livello | Funzioni nell'I/O |
> |---|---|
> | **Software a livello utente** | eseguire la chiamata I/O; formattare l'I/O; *spooling* |
> | **Software indipendente dal dispositivo** | denominazione, protezione, blocco, buffering, allocazione |
> | **Driver dei dispositivi** | impostazione dei registri; controllo dello stato |
> | **Gestori degli interrupt** | attivare il driver al completamento dell'I/O |
> | **Hardware** | eseguire l'operazione di I/O |
### Gestori degli interrupt
Il driver che avvia un'operazione si **blocca** (ad esempio con un [[04 - Sincronizzazione|semaforo]]) fino al completamento dell'I/O e all'arrivo dell'interrupt. L'elaborazione di un interrupt è **complessa** e, su sistemi con [[06 - Gestione della Memoria|memoria virtuale]], richiede passaggi aggiuntivi per MMU, TLB e cache.
> [!example] I dieci passi della gestione di un interrupt (lato software)
> 1. **Salvataggio dei registri** non salvati dall'interrupt hardware.
> 2. **Impostazione del contesto** della ISR (TLB, MMU, tabella delle pagine).
> 3. **Impostazione dello stack** della ISR.
> 4. **Conferma** al controller degli interrupt (e riabilitazione, se necessario).
> 5. **Copia dei registri** salvati nella tabella dei processi.
> 6. **Esecuzione della ISR**, estraendo le informazioni dai registri del controller.
> 7. **Scelta del processo successivo** (eventualmente uno ad alta priorità sbloccato dall'interrupt).
> 8. **Impostazione del contesto MMU** per il nuovo processo.
> 9. **Caricamento dei registri** del nuovo processo (incluso il PSW).
> 10. **Avvio** del nuovo processo.
### Driver di dispositivo
Ogni dispositivo richiede un codice specifico — il **driver** — che ne gestisce i registri, di solito fornito dal **produttore**. Un driver gestisce un tipo o una *classe* di dispositivi (tecnologie come **USB** usano una **pila di driver**: dal livello base che gestisce l'I/O seriale, ai livelli superiori per i pacchetti dati, fino alle API di alto livello). I driver fanno di norma parte del **kernel** (per accedere ai registri del controller); se eseguiti in **spazio utente** sono più facili da installare e mettono meno a rischio il SO, ma sono **più lenti** (serve passare al kernel per ogni operazione).
> [!info] Caricamento dei driver — da statico a dinamico
> Storicamente i driver erano inclusi nel **binario** del SO: aggiungere un dispositivo significava **ricompilare il kernel**. Nei sistemi moderni i driver si caricano **dinamicamente** a runtime.

Funzioni del driver: validare i parametri di input, tradurli in comandi specifici per il dispositivo, gestire l'I/O e gli errori (a volte attendendo l'interrupt). I driver devono essere **rientranti** (richiamabili mentre stanno già gestendo una richiesta) e saper gestire dispositivi *hot pluggable*: se un dispositivo viene rimosso durante un'operazione, il SO deve "ripulire" le operazioni in corso e impedirne di nuove.
### Software di I/O indipendente dal dispositivo
Ma il software di I/O dipende *sempre* dal dispositivo? No: il **software indipendente dal dispositivo** fa da **intermediario** tra i driver e le applicazioni, offrendo un'interfaccia uniforme e gestendo le operazioni comuni.
#### Interfaccia uniforme dei driver
Senza uniformità, ogni nuovo dispositivo richiederebbe modifiche al SO. La soluzione è un **modello uniforme** in cui tutti i driver condividono la **stessa interfaccia**: per ogni *classe* di dispositivi il SO definisce un insieme di funzioni che i driver devono supportare (per i dischi: lettura, scrittura, formattazione…). Il driver espone una **tabella di puntatori a funzioni** che il SO usa per **chiamate indirette**. La **denominazione** mappa i nomi simbolici sui driver (es. `/dev/disk0` in UNIX, tramite **major** e **minor device number**) e la **protezione** dei dispositivi segue le stesse regole dei file.
#### Buffering
Il buffering è cruciale ma delicato. In **input** si passa da nessun buffer (riavvio del processo a ogni carattere, inefficiente) a un buffer nello **spazio utente** (problemi se la pagina viene paginata fuori), a un buffer nel **kernel**, fino al **doppio buffer** (uno accumula i nuovi caratteri mentre l'altro viene copiato nello spazio utente) e al **buffer circolare**. In **output**, un buffer nel kernel permette di **sbloccare subito** il processo utente. Il costo è la **copia multipla** (utente → kernel → controller → rete), che rallenta la velocità effettiva di trasmissione.
#### Segnalazione degli errori
Gli **errori di programmazione** (scrivere su un dispositivo di input, indirizzo di buffer non valido, dispositivo inesistente) restituiscono un **codice d'errore** al chiamante. I **veri errori di I/O** (es. blocco danneggiato) sono gestiti dal driver e, se irrisolvibili, passati al software indipendente: con un **utente interattivo** si può aprire un dialogo (riprova/ignora/termina), altrimenti la chiamata fallisce con un codice d'errore. Gli **errori critici** (strutture dati danneggiate) possono richiedere un messaggio e la **terminazione** del sistema.
#### Dispositivi dedicati e spooling
Alcuni dispositivi (stampanti) richiedono **uso esclusivo**: i processi fanno `open` su un *file speciale* e la `close` lo rilascia, oppure si usano meccanismi di richiesta/rilascio con **coda** dei processi bloccati. Lo **spooling** gestisce i dispositivi dedicati in ambienti multiprogrammati tramite un processo **daemon** e una **directory di spooling** (i lavori di stampa vi vengono depositati e il daemon li serve in ordine), evitando il blocco prolungato da parte di un singolo processo.
#### Dimensione dei blocchi uniforme
SSD e dischi hanno settori e pagine flash di **dimensioni variabili**. Il software indipendente dal dispositivo **nasconde** queste differenze fornendo una **dimensione di blocco logico uniforme** ai livelli superiori, che interagiscono così con *dispositivi astratti* indipendenti dalle dimensioni fisiche. Lo stesso vale per i dispositivi a caratteri (es. mouse vs interfaccia di rete).
### Software di I/O nello spazio utente
Parte del software di I/O sta **fuori dal kernel**, come **librerie** collegate ai programmi: la chiamata di sistema `write(fd, buffer, nbytes)` in C è facilitata da procedure di libreria, e funzioni come `printf()` e `scanf()` **formattano** i dati prima di invocare le syscall. Qui vive anche lo **spooling**. Queste librerie permettono al programmatore di concentrarsi sulla **logica dell'applicazione** invece che sui dettagli di basso livello.
## Flusso completo di una richiesta di I/O
Quando un programma utente richiede un I/O (es. **leggere un blocco** da un file): il **software indipendente dal dispositivo** controlla prima la *buffer cache*; se il dato non c'è, il **driver** inoltra la richiesta all'**hardware** e il processo utente viene **sospeso**. Completata l'operazione, l'hardware genera un **interrupt**; il **gestore** risponde, recupera lo stato del dispositivo e **risveglia** il processo utente, che completa la richiesta e prosegue. Ogni livello svolge così un ruolo preciso nel trattamento efficiente dell'I/O.
# Collegamenti con altri argomenti
Mappa dei rimandi di questa nota.
- **Memoria, MMU, TLB, cache, memoria virtuale** → [[06 - Gestione della Memoria]]
- **Context switch, blocco/sblocco dei processi** → [[03 - Processi e Thread]]
- **Scheduler invocato durante l'attesa I/O** → [[05 - Scheduling]]
- **Semafori per bloccare i driver, race condition** → [[04 - Sincronizzazione]]
- **Dispositivi a blocchi astratti, `/dev`, VFS** → [[07 - File System]]
- **Chiamate di sistema, kernel space vs user space** → [[02 - Concetti di Base e Strutture]]
- **Sistemi embedded** → [[01 - Introduzione ai Sistemi Operativi#^embedded]]
- **Prospettiva architetturale completa** (CPU, bus, disco) → [[5 - Input & Output]], [[2 - Organizzazione dei sistemi di calcolo]]
