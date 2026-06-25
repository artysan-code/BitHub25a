# Esercizi Svolti — Linux e BASH
Soluzioni svolte di una selezione degli **Esercizi di Autovalutazione** del prof. Croce (file `SOR2025-2026_3.1_Exercises-on-Linux-and-BASH`), scelti perché usano strumenti (`awk`, `sed`, `cut`, `od`, `split`, `tr`, `find -exec`) la cui sintassi operativa va oltre quella di base. Per la teoria dei comandi vedi [[09 - Linux e BASH]].

> [!info] Verifica
> Tutti i comandi sono stati **eseguiti** e l'output riportato è quello reale. I file di prova sono **tab-separated** dove indicato (`\t`).
## Es. 3 — Manipolazione con grep, awk, sed
File `studenti.tsv` (tab-separated):
```
id	nome	corso	voto
1	Marta	Programmazione	30
2	Paolo	Programmazione	28
3	Chiara	Sistemi	24
4	Luca	Sistemi	30
5	Anna	Programmazione	26
```
**1. Righe con 3ª colonna = `Programmazione`.** `-F'\t'` imposta il tab come separatore, `$3` è la terza colonna:
```bash
awk -F'\t' '$3 == "Programmazione"' studenti.tsv
```
```
1	Marta	Programmazione	30
2	Paolo	Programmazione	28
5	Anna	Programmazione	26
```
**2. Conteggio delle righe che soddisfano la condizione:**
```bash
awk -F'\t' '$3 == "Programmazione"' studenti.tsv | wc -l      # → 3
```
**3. Sostituire `Sistemi` con `Sistemi Operativi` in tutto il file** (`s/vecchio/nuovo/g`, `g` = tutte le occorrenze sulla riga). Con `-i` la modifica avviene **in place** sul file; senza `-i` l'output va su stdout:
```bash
sed 's/Sistemi/Sistemi Operativi/g' studenti.tsv     # stampa il risultato
sed -i 's/Sistemi/Sistemi Operativi/g' studenti.tsv  # modifica il file
```
```
3	Chiara	Sistemi Operativi	24
4	Luca	Sistemi Operativi	30
```
**4. Righe con voto $\ge 28$** (`NR>1` salta l'intestazione; il confronto numerico su `$4`):
```bash
awk -F'\t' 'NR>1 && $4 >= 28' studenti.tsv
```
```
1	Marta	Programmazione	30
2	Paolo	Programmazione	28
4	Luca	Sistemi	30
```
**5. Salvare l'output in `studenti_top.tsv`:**
```bash
awk -F'\t' 'NR>1 && $4 >= 28' studenti.tsv > studenti_top.tsv
```
## Es. 16 — Tipo di file e ispezione binaria (`file`, `od`)
```bash
printf '\x41\x42\x0a' > bytes.bin   # byte: 0x41 0x42 0x0a
```
**Perché `less bytes.bin` è leggibile?** Perché i tre byte sono tutti **stampabili**: `0x41` è il carattere `A`, `0x42` è `B`, `0x0a` è il **newline** (`\n`). Il file è quindi il testo `AB` seguito da a-capo.
**Differenza tra le due ispezioni** — `od` (octal dump) interpreta i byte in modo diverso:
```bash
od -t x1 bytes.bin   # ogni byte in esadecimale
```
```
0000000 41 42 0a
0000003
```
```bash
od -c bytes.bin      # ogni byte come carattere (con escape per i non stampabili)
```
```
0000000   A   B  \n
0000003
```

> [!note]
> `-t x1` = *type hexadecimal, 1 byte alla volta* (vista "grezza" dei byte); `-c` = *character* (mostra i caratteri, usando escape come `\n`, `\t`, `\0` per i non stampabili). La colonna di sinistra (`0000000`, `0000003`) è l'**offset in ottale** del byte. Utile per capire la codifica reale di un file.
## Es. 19 — Selezione colonne con `cut` (TSV)
`cut` estrae campi: `-f` indica i numeri di campo, il separatore di default è già il **tab** (per CSV si usa `-d','`).
**1. Estrarre le colonne `nome` (2) e `voto` (4) in `esiti.tsv`:**
```bash
cut -f2,4 studenti.tsv > esiti.tsv
```
```
nome	voto
Marta	30
Paolo	28
Chiara	24
Luca	30
Anna	26
```
**2. Estrarre la 3ª colonna e rimuovere i duplicati** (`tail -n +2` scarta l'intestazione):
```bash
cut -f3 studenti.tsv | tail -n +2 | sort -u
```
```
Programmazione
Sistemi
```
**3. Prime $N$ righe di `esiti.tsv` senza aprire un editor:**
```bash
head -n 3 esiti.tsv
```
## Es. 20 — Trasformazioni con `tr`
File `frasi.txt`:
```
CIAO MONDO
Linux     è      fantastico!!!
123abcDEF
```
`tr` lavora **carattere per carattere** leggendo da stdin. **1. Tutto in minuscolo** (rimappa l'intervallo `A-Z` su `a-z`; `è`, essendo non-ASCII, resta invariato):
```bash
tr 'A-Z' 'a-z' < frasi.txt
```
```
ciao mondo
linux     è      fantastico!!!
123abcdef
```
**2. Rimuovere tutte le cifre** (`-d` = *delete* dei caratteri nell'insieme):
```bash
tr -d '0-9' < frasi.txt          # 123abcDEF → abcDEF
```
**3. Comprimere gli spazi multipli in uno solo** (`-s` = *squeeze* ripetizioni):
```bash
tr -s ' ' < frasi.txt            # "Linux     è      fantastico" → "Linux è fantastico"
```
**4. Mantenere solo lettere e spazi** (`-c` = *complemento* dell'insieme, combinato con `-d`: cancella tutto ciò che **non** è lettera/spazio/newline):
```bash
tr -cd 'a-zA-Z \n' < frasi.txt
```
```
CIAO MONDO
Linux           fantastico
abcDEF
```
(le cifre e `!!!` sono rimossi; `è` viene eliminato perché non in `a-zA-Z`, lasciando gli spazi che lo circondavano.)
## Es. 21 — Suddividere file con `split` e ricomporre
**1. Generare `numeri.txt` con le righe da 1 a 1000:**
```bash
seq 1 1000 > numeri.txt          # wc -l → 1000
```
**2. Spezzare in blocchi da 100 righe** (`-l 100`; `parte_` è il prefisso dei file generati `parte_aa`, `parte_ab`, …):
```bash
split -l 100 numeri.txt parte_
```
**3. Verificare numero di parti e righe per parte:**
```bash
ls parte_* | wc -l               # → 10
wc -l parte_*                    # → 100 per ciascuna, 1000 total
```
**4. Ricomporre e verificare l'identità con l'originale:**
```bash
cat parte_* > numeri_join.txt
wc -l numeri_join.txt            # → 1000
diff numeri.txt numeri_join.txt && echo "IDENTICI"   # nessuna differenza → IDENTICI
```

> [!note]
> `cat parte_*` funziona perché la **globbing** espande i nomi in **ordine alfabetico** (`parte_aa`, `parte_ab`, …), che coincide con l'ordine di generazione: la ricomposizione preserva l'ordine originale.
## Es. 24 — Ricerca file con `find` (nome, tipo, azione)
Struttura di prova: `proj/app.log`, `proj/src/run.log`, `proj/empty1.log` (vuoto), `proj/src/empty2.txt` (vuoto), directory `proj/build` e `proj/sub/build`.
**1. File che terminano in `.log` dalla directory corrente:**
```bash
find . -name '*.log'
```
```
./proj/empty1.log
./proj/app.log
./proj/src/run.log
```
**2. Tutte le directory chiamate `build`** (`-type d`):
```bash
find . -type d -name build
```
```
./proj/build
./proj/sub/build
```
**3. Per ogni `.log`, contare le righe** con `-exec ... {} +`: `{}` è sostituito dai file trovati, `+` li passa **tutti insieme** a un solo `wc` (più efficiente di `\;`, che lancerebbe un processo per file):
```bash
find . -name '*.log' -exec wc -l {} +
```
```
  0 ./proj/empty1.log
  3 ./proj/app.log
  1 ./proj/src/run.log
  4 total
```
**4. File vuoti** (`-empty`) salvati in una lista:
```bash
find . -type f -empty > empty_files.txt
```

> [!warning] `-exec ... {} +` vs `-exec ... {} \;`
> `{} +` accoda quanti più file possibile in **una sola** invocazione del comando (come fa `xargs`); `{} \;` esegue il comando **una volta per file**. Per `wc -l` la differenza è anche semantica: con `+` si ottiene la riga `total`, con `\;` no.
## Conteggio di frequenze: `sort | uniq -c`
Classico idioma per contare le occorrenze. `uniq -c` conta righe **adiacenti** uguali, quindi va **sempre** preceduto da `sort`; un secondo `sort -rn` ordina per frequenza decrescente. File `log.txt`:
```
INFO avvio
WARN memoria
INFO richiesta
ERROR disco
INFO risposta
WARN memoria
ERROR rete
INFO chiusura
```
**Contare le righe per livello di log** (`cut -d' ' -f1` prende la prima parola):
```bash
cut -d' ' -f1 log.txt | sort | uniq -c | sort -rn
```
```
      4 INFO
      2 WARN
      2 ERROR
```

> [!note] Perché `sort` prima di `uniq`
> `uniq` collassa solo i duplicati **consecutivi**: senza il `sort` iniziale, `INFO` sparso su righe non adiacenti verrebbe contato più volte. La pipe `sort | uniq -c | sort -rn` è il modo standard per una "classifica" di frequenze.
## Aggregazione di colonne con `awk`
`awk` mantiene **variabili** e **array associativi** tra le righe: ideale per somme e raggruppamenti. File `vendite.tsv` (tab-separated, con intestazione):
```
prodotto	qta	prezzo
mela	10	0.50
pera	4	0.80
mela	6	0.50
uva	2	2.00
```
**1. Incasso totale** ($\sum \text{qta} \times \text{prezzo}$; `NR>1` salta l'intestazione):
```bash
awk -F'\t' 'NR>1 {tot += $2*$3} END {printf "incasso totale = %.2f\n", tot}' vendite.tsv
```
```
incasso totale = 15.20
```
**2. Quantità totale per prodotto** (array associativo `q[$1]` indicizzato sul nome):
```bash
awk -F'\t' 'NR>1 {q[$1]+=$2} END {for (p in q) print p, q[p]}' vendite.tsv | sort
```
```
mela 16
pera 4
uva 2
```

> [!note] Il blocco `END` e gli array associativi
> Il blocco `{ … }` viene eseguito **per ogni riga**; il blocco `END { … }` **una volta sola** alla fine, quando si stampano i totali accumulati. `q[$1]+=$2` crea automaticamente una voce dell'array per ogni valore distinto della prima colonna: è il modo `awk` di fare un *group-by*.
## Da svolgere
Esercizi senza soluzione: prova i comandi a terminale e verifica l'output. Teoria in [[09 - Linux e BASH]].

> [!todo] Da svolgere
> 1. **grep + regex.** Da `log.txt`, estrai solo le righe che **non** sono di livello `INFO` (suggerimento: `grep -v`), poi solo quelle che contengono `memoria` **o** `rete` (regex con `grep -E`). Vedi [[09 - Linux e BASH#Espressioni regolari|espressioni regolari]].
> 2. **sed.** In `vendite.tsv` sostituisci `mela` con `mela rossa` su tutte le righe, stampando il risultato **senza** modificare il file; poi rifallo **in place** con `-i`.
> 3. **find + xargs.** Trova tutti i file `.tsv` nella directory corrente e, per ciascuno, stampa numero di righe e nome (`wc -l`), usando sia `-exec … {} +` sia `xargs`. Confronta con [[#Es. 24 — Ricerca file con `find` (nome, tipo, azione)|Es. 24]].
> 4. **Pipeline completa.** Da `vendite.tsv`, ottieni la classifica dei prodotti per **incasso** decrescente (qta×prezzo per riga, sommato per prodotto, ordinato). Combina `awk` e `sort`.
> 5. **cut + sort -u.** Estrai l'elenco dei prodotti **distinti** da `vendite.tsv`, in ordine alfabetico, senza intestazione.

---
**Teoria di riferimento:** [[09 - Linux e BASH]] · **Indice di tutti gli esercizi:** [[Indice degli Esercizi]]
