# 🛠️ Script Utility

Script di utilità per gestire e mantenere la repository BitHub25a.

---

## 📜 Script Disponibili

### `check_structure.sh`

Verifica che ogni corso abbia la struttura corretta.

**Cosa controlla:**
- Presenza di `README.md` in ogni corso
- Lista dei corsi con problemi

**Uso:**
```bash
cd scripts
./check_structure.sh
```

**Output:**
```
=== Verifica Struttura Corsi BitHub25a ===

--- 1° Anno ---
✅ Analisi Matematica
✅ Architettura dei Sistemi di Elaborazione
❌ Logica e Reti Logiche - Manca README.md
...

=== Riepilogo ===
Corsi totali: 20
Corsi OK: 19
Corsi senza README: 1
```

---

### `stats.sh`

Genera statistiche dettagliate sulla repository.

**Statistiche generate:**
- Numero corsi per anno
- File markdown totali
- Immagini (PNG, JPG)
- PDF e file Xournal
- README presenti
- Dimensione totale
- Top 5 corsi per numero di file

**Uso:**
```bash
cd scripts
./stats.sh
```

**Output:**
```
=== Statistiche BitHub25a ===

📚 Corsi per Anno:
  1° Anno: 7 corsi
  2° Anno: 7 corsi
  3° Anno: 6 corsi

📝 File Markdown: 204
🖼️  Immagini: 101 (PNG: 95, JPG: 6)
📄 PDF: 150
✏️  File Xournal: 15
📖 README: 20

💾 Dimensione totale Corsi: 917M

🏆 Top 5 Corsi per Numero di File:
  1. Algoritmi e Strutture Dati (85 file)
  2. Fisica (62 file)
  ...
```

---

## 🚀 Prerequisiti

Gli script sono scritti in **Bash** e richiedono:
- Linux/macOS o WSL su Windows
- Comandi standard Unix: `find`, `wc`, `du`, `sort`

---

## 💡 Utilizzo

### Rendere gli script eseguibili

```bash
chmod +x scripts/*.sh
```

### Eseguire dalla root del progetto

```bash
./scripts/check_structure.sh
./scripts/stats.sh
```

### Eseguire dalla cartella scripts

```bash
cd scripts
./check_structure.sh
./stats.sh
```

---

## 🔧 Personalizzazione

Gli script sono facilmente estendibili. Alcune idee:

### check_structure.sh
- Verificare presenza di cartelle `Appunti/`, `Esercizi/`
- Controllare frontmatter nei file markdown
- Validare naming dei file

### stats.sh
- Statistiche per singolo corso
- Analisi tag usati
- Grafici con gnuplot
- Export in JSON/CSV

---

## 🤝 Contribuire

Se crei nuovi script utili, aggiungili qui e documenta:
1. Scopo dello script
2. Come usarlo
3. Output atteso

---

[[../Dashboard|← Torna alla Dashboard]]
