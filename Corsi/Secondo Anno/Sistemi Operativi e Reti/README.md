# Sistemi Operativi e Reti
**Codice**: SOR · **CFU**: 12 · **Semestre**: 1-2 · **Anno**: 2°
**SSD**: INF/01
**Docente/Docenti**: Danilo Croce (Modulo 1 — Sistemi Operativi) · Manuel Fiorelli (Modulo 2 — Reti)
**Propedeuticità**: Architettura dei Sistemi di Elaborazione · Programmazione dei Calcolatori con Laboratorio

Corso annuale diviso in due moduli indipendenti: **Sistemi Operativi** (1° semestre) e **Reti di Calcolatori** (2° semestre).
## Modalità d'esame
Ogni modulo si conclude con **due prove ad accesso esclusivo** (lo scritto dà accesso all'orale).
- **Sessione invernale**: è prevista la prova di **esonero del Modulo 1** (Sistemi Operativi). Superare l'esonero + il relativo orale **conclude il Modulo 1**.
- **Tutte le sessioni** (invernale, estiva, autunnale): è disponibile l'**appello completo su entrambi i moduli**.
## Programma
### Modulo 1 — Sistemi Operativi (1° semestre)
1. Introduzione ai sistemi operativi
2. Classificazione dei sistemi operativi
3. Principali modelli strutturali
4. Gestione dei processi
5. Gestione dei thread
6. Sincronizzazione dei processi
7. Scheduling della CPU
8. Gestione della memoria
9. Gestione del file system
10. Gestione dell'I/O
11. I sistemi operativi Unix e Linux (caso di studio)
### Modulo 2 — Reti di Calcolatori (2° semestre)
- Reti di calcolatori e Internet
- Strato di applicazione
- Strato di trasporto
- Strato di rete: piano dei dati e piano di controllo
- Strato di collegamento e reti di area locale
- Reti wireless e principi di gestione della mobilità
## Perimetro del Modulo 1 (riferimenti sul Tanenbaum)
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
- Slide ufficiali del corso (`SOR2025-2026`) in `Materiale Didattico/`.
## Crediti e fonti integrate
La cartella `Esercizi/` raccoglie esercizi C di laboratorio su **processi**, **thread**, **sincronizzazione** e **file I/O**, integrati — con adattamenti — dal repository di Ionut Zbir ([github.com/IonutZbir/University](https://github.com/IonutZbir/University)), che include inoltre le tracce delle prove pratiche d'esame. Alcuni dettagli teorici puntuali confluiti nelle note del [[01 - Introduzione ai Sistemi Operativi|Modulo 1]] traggono origine dallo stesso materiale.
