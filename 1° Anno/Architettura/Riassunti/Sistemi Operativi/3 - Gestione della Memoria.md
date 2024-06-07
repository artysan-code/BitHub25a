In questo capitolo si tratterà la gestione della memoria da parte del **sistema operativo** seguendo quella che è la **gerarchia delle memorie**, dalle più veloci e costose alle più lente ed economiche. 

Il compito del sistema operativo è di organizzarle (esclusa la cache) per eseguire in maniera efficiente tutti i propri compiti. La parte che esegue questo compito è chiamata **gestore della memoria**.

(Pagine riassunte: 1)
## 3.1 - Nessuna astrazione della memoria
Supponendo un'organizzazione senza astrazione di memoria, un sistema può essere strutturato in tre modalità:
- Può trovarsi *in fondo alla memoria* (fig 3.1 a) nella **RAM** (Random Access Memory).
- Può trovarsi *in cima alla memoria* (fig 3.1 b) nella **ROM** (Read Only Memory).
- Può trovarsi come nel primo caso, ma con i *driver dei dispositivi* in cima alla memoria nella ROM.

Il primo e l'ultimo metodo sono molto rischiosi: un programma utente scritto male potrebbe eliminare o sovrascrivere il sistema operativo, perdendo così l'accesso all'intera memoria.

Inoltre, generalmente non è possibile eseguire più di un programma alla volta. Si potrebbe usare la divisione in thread, ma ciò non permetterebbe l'esecuzione di due programmi non relazionati, a causa della mancanza di astrazione, che implica la mancanza ulteriore di un'astrazione dei possibili thread thread.
#### Esecuzione di molteplici programmi senza astrazione della memoria
Esiste un metodo con cui i creatori dei computer IBM hanno risolto il problema dell'esecuzione dei programmi. ù

Sapendo che generalmente il sistema operativo esegue un programma, lo copia in un file (**swapping**) e passa al successivo, hanno implementato una suddivisione fisica della memoria in blocchi di 2 KB con una chiave di protezione di 4 bit (custodita in registri speciali nella CPU) che specifica l'accesso alla memoria. Il sistema operativo intercettava ogni tentativo di accesso alla memoria con un codice di protezione diverso dal **PSW** (Program Status Word, anch'esso con una chiave di 4 bit), impedendo ai programmi di accedere ai blocchi di memoria assegnati ad altri programmi.

Tuttavia, un problema sorge quando due programmi vengono eseguiti in maniera sequenziale e sovrapposta (il primo programma parte, attende, è ancora in esecuzione e parte il secondo). Quando i due programmi hanno delle locazioni predisposte, essi sono ancora legati alle **chiamate fisiche alla memoria**, generando errori.

Altre implementazioni per risolvere questo problema includono la **rilocazione statica**, che consiste nell'aggiungere n bit all'indirizzo di ogni istruzione. Tuttavia, questo sistema funziona solo in ambiti predefiniti, come elettrodomestici (lavastoviglie, lavatrici), dove il programma conosce già cosa eseguire.

(Pagine riassunte: 3.5)
## 3.2 - Un'astrazione della memoria: gli spazi degli indirizzi

### 3.2.1 - Nozione di spazio degli indirizzi


(Pagine riassunte: 2.5)
### 3.2.2 - Swapping


(Pagine riassunte: 2.25)
### 3.2.3 - Gestione della memoria libera


(Pagine riassunte: 3)
## 3.3 - Memoria virtuale


(Pagine riassunte: 1.25)
### 3.3.1 - Paginazione


(Pagine riassunte: 3.5)
### 3.3.2 - Tabelle delle pagine


(Pagine riassunte: 2)
### 3.3.3 - Velocizzare la paginazione


(Pagine riassunte: 3.5)
### 3.3.4 - Tabelle delle pagine per grandi memorie


(Pagine riassunte: 3.5)
## 3.4 - Algoritmi di sostituzione delle pagine


(Pagine riassunte: 0.75)
### 3.4.1 - L'algoritmo ottimale di sostituzione delle pagine


(Pagine riassunte: 0.5)
### 3.4.2 - Not recently used (NRU)


(Pagine riassunte: 1)
### 3.4.3 - First-in, first-out (FIFO)


(Pagine riassunte: 0.5)
### 3.4.4 - Seconda chance


(Pagine riassunte: 0.5)
### 3.4.5 - Clock

### 3.4.6 - Least recently used (LRU)


(Pagine riassunte: 1)
### 3.4.7 - (Saltato)
### 3.4.8 - Working set


(Pagine riassunte: 3.75)
### 3.4.9 - WSClock


(Pagine riassunte: 1.75)
### 3.4.10 - Riepilogo degli algoritmi di sostituzione delle pagine


(Pagine riassunte: 0.75)
## 3.5 - Problemi di progettazione dei sistemi di paginazione

### 3.5.1 - Politiche di allocazioni globali e locali


(Pagine riassunte: 2.5)
### 3.5.2 - Controllo del carico


(Pagine riassunte: 0.5)
### 3.5.3 - Dimensione dello spazio


(Pagine riassunte: 1.75)
### 3.5.4 - Istruzioni separate e spazi di dati


(Pagine riassunte: 0.75)
### 3.5.5 - Pagine condivise


(Pagine riassunte: 1.5)
### 3.5.6 - Librerie condivise


(Pagine riassunte: 2)
### 3.5.7 - File mappati


(Pagine riassunte: 0.5)
### 3.5.8 - Politica di ripulitura


(Pagine riassunte: 0.5)
### 3.5.9 - Interfaccia della memoria virtuale


(Pagine riassunte:  0.75)
## 3.6 - Problemi di implementazione
### 3.6.1 - Il sistema operativo e la paginazione


(Pagine riassunte: 1)
### 3.6.2 - Gestione dei page fault


(Pagine riassunte: 1)
### 3.6.3 - Backup delle istruzioni


(Pagine riassunte: 1)
### 3.6.4 - Bloccare le pagine in memoria


(Pagine riassunte: 0.5)
### 3.6.5 - Memoria secondaria


(Pagine riassunte: 1.75)
### 3.6.6 - Separazione fra politica e meccanismo


(Pagine riassunte: 1.25)
## 3.7 - Segmentazione


(Pagine riassunte: 2.75)
### 3.7.1 - Implementazione della segmentazione pura


(Pagine riassunte: 0.75)
### 3.7.2 - Segmentazione con la paginazione: MULTICS


(Pagine riassunte: 4)
### 3.7.3 - Segmentazione con paginazione: l'Intel x86


(Pagine riassunte: 4.5)
## 3.8 - Stato della ricerca sulla gestione della memoria

(Pagine riassunte: 1)