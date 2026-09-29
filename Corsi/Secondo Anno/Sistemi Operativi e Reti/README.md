---
tipo: corso
materia: Sistemi Operativi e Reti
codice: SOR
anno: 2
semestre: "1-2"
cfu: 12
ssd: INF/01
docenti:
  - Danilo Croce
  - Manuel Fiorelli
propedeuticita:
  - Architettura dei Sistemi di Elaborazione
  - Programmazione dei Calcolatori con Laboratorio
---
# Sistemi Operativi e Reti
Corso annuale diviso in due moduli indipendenti: **Sistemi Operativi** (1° semestre, prof. **Danilo Croce**) e **Reti di Calcolatori** (2° semestre, prof. **Manuel Fiorelli**).
## Modalità d'esame
Ogni modulo si conclude con **due prove ad accesso esclusivo** (lo scritto dà accesso all'orale).
- **Sessione invernale**: è prevista la prova di **esonero del Modulo 1** (Sistemi Operativi). Superare l'esonero + il relativo orale **conclude il Modulo 1**.
- **Tutte le sessioni** (invernale, estiva, autunnale): è disponibile l'**appello completo su entrambi i moduli**.

Lo scritto del Modulo 1 è formato da un **test a risposta multipla** sull'intero programma e da una o più **domande aperte**, che possono essere esercizi di calcolo (scheduling, page fault, dimensionamento di FAT e i-node) oppure un esercizio di **programmazione C POSIX**. Per accedere all'orale servono almeno **18/30** allo scritto; il voto finale è fissato dall'orale.
## Programma e Appunti
### Modulo 1 — Sistemi Operativi (1° semestre)
Programma ufficiale: introduzione, classificazione e modelli strutturali dei sistemi operativi; gestione di processi e thread; sincronizzazione; scheduling della CPU; gestione della memoria; file system; I/O; Unix e Linux (caso di studio).
- [[01 - Introduzione ai Sistemi Operativi]] — cos'è un sistema operativo, storia, analisi dell'hardware, classificazione dei sistemi operativi (lo «zoo»).
- [[02 - Concetti di Base e Strutture]] — system call, astrazione di processo, file e file system, protezione e shell, principali modelli strutturali.
- [[03 - Processi e Thread]] — modello di processo, gestione e stati dei processi, multiprogrammazione, segnali e interrupt, thread.
- [[04 - Sincronizzazione]] — problema della concorrenza, mutua esclusione, semafori, mutex, variabili condizionali, monitor, scambio di messaggi, barriere, problemi classici.
- [[05 - Scheduling]] — scheduling nei sistemi batch, interattivi e real-time, meccanismo e politica, scheduling dei thread.
- [[06 - Gestione della Memoria]] — spazi degli indirizzi, swapping, memoria virtuale, algoritmi di sostituzione delle pagine, segmentazione.
- [[07 - File System]] — file, directory, nomi di percorso, implementazione del file system.
- [[08 - Input Output]] — hardware di I/O, polling, DMA, interrupt, livelli del software di I/O.
- [[09 - Linux e BASH]] — shell BASH, variabili, redirezione e pipe, permessi, processi e job control, utility di testo, espressioni regolari.
- [[10 - Programmazione C e Concorrente]] — programmazione C per il laboratorio: build, system call, `fork`/`exec`/`wait`, segnali, pipe.
### Modulo 2 — Reti di Calcolatori (2° semestre)
- [[01 - Introduzione]] — reti di calcolatori e Internet: edge e core della rete, prestazioni, livelli di protocollo, sicurezza.
- [[02 - Livello di Applicazione]] — strato di applicazione: Web e HTTP, e-mail, DNS, P2P, streaming video e CDN.
- [[03 - Livello di Trasporto]] — strato di trasporto: multiplexing, UDP, trasferimento dati affidabile, TCP, controllo della congestione, QUIC.
- [[04 - Livello di Rete]] — strato di rete, piano dei dati e piano di controllo: router, IP, SDN, ICMP, gestione della rete.
- [[05 - Livello di Collegamento]] — strato di collegamento e reti di area locale: rilevazione e correzione degli errori, accesso multiplo, LAN.
- [[06 - Reti Wireless e Mobilita]] — reti wireless e principi di gestione della mobilità: WiFi, reti cellulari 4G/5G, Mobile IP, Bluetooth.
### Esercizi
- [[Indice degli Esercizi]] — indice degli esercizi C di laboratorio (processi, thread e sincronizzazione).
- [[Tracce d'Esame Pratiche]] — tracce d'esame pratiche di Sistemi Operativi.
- Esercizi svolti per argomento: [[03 - Processi e Thread (Esercizi)]], [[04 - Sincronizzazione (Esercizi)]], [[05 - Scheduling (Esercizi)]], [[06 - Gestione della Memoria (Esercizi)]], [[07 - File System (Esercizi)]], [[08 - Input Output (Esercizi)]], [[09 - Linux e BASH (Esercizi)]].
### Perimetro del Modulo 1 (riferimenti sul Tanenbaum)
Mappa argomento ↔ slide del corso ↔ capitolo del libro. **In programma tutto ciò che è coperto dalle slide 1–14.**

| Argomento | Slide | Tanenbaum |
|---|---|---|
| Introduzione, classificazione, strutture, concetti base, syscall | 1–3 | Cap. 1 |
| Processi e thread | 4 | Cap. 2 (2.1–2.2) |
| Sincronizzazione + problemi classici di IPC | 6 | Cap. 2 (2.3, 2.5) |
| Scheduling | 7 | Cap. 2 (2.4) |
| Gestione della memoria (paginazione, memoria virtuale) | 8–10 | Cap. 3 |
| File system | 11–12 | Cap. 4 |
| Input/Output | 13–14 | Cap. 5 |
| Programmazione C / concorrente (strumentale al laboratorio) | 5 | Cap. 1 (1.8) |
| Unix/Linux e BASH (pratico) | 3.1 | — (slide + risorse online, **non** dal Cap. 10) |

**Fuori programma** (nessuna slide dedicata, confermato):
- Deadlock (Cap. 6)
- Virtualizzazione e cloud come capitolo a sé (Cap. e7) — resta solo l'introduzione a VM/container già vista nelle strutture
- Sistemi a più processori (Cap. e8)
- Sicurezza (Cap. e9)
- Casi di studio dal libro: UNIX/Linux/Android (Cap. 10) e Windows (Cap. e11) — la parte Unix/Linux è trattata "a mano" da slide e risorse online, non dal capitolo
- Progettazione di un sistema operativo (Cap. e12)
## Materiale di riferimento
- **Modulo 1**: A. S. Tanenbaum, H. Bos — *I moderni sistemi operativi*, 4ª ed. italiana, Pearson.
- **Modulo 2**: J. F. Kurose, K. W. Ross — *Reti di calcolatori e Internet: un approccio top-down*, Pearson.
- Slide ufficiali del corso (`SOR2025-2026`) in `Materiale Didattico/Sistemi Operativi/Slide/` e `Materiale Didattico/Reti di Calcolatori/Slide/`; esercitazioni, compiti di prova ed esempi di codice nelle cartelle `Esercitazioni/`, `Esami/` ed `Esempi/` di ciascun modulo.
- `Materiale Didattico/Estratti/`: estratti e OCR delle scansioni del libro (`out_kb/`) e script di supporto.
## Crediti e fonti integrate
La cartella `Esercizi/` raccoglie esercizi C di laboratorio su **processi**, **thread**, **sincronizzazione** e **file I/O**, integrati — con adattamenti — dal repository di Ionut Zbir ([github.com/IonutZbir/University](https://github.com/IonutZbir/University)), che include inoltre le tracce delle prove pratiche d'esame. Alcuni dettagli teorici puntuali confluiti nelle note del [[01 - Introduzione ai Sistemi Operativi|Modulo 1]] traggono origine dallo stesso materiale.

Le note del **Modulo 2 (Reti)** in `Appunti/Reti di Calcolatori/` sono redatte dando priorità alle slide ufficiali del prof; gli appunti di Reti dello stesso repository del collega sono serviti solo come traccia di prosa, sempre verificata contro le slide.
