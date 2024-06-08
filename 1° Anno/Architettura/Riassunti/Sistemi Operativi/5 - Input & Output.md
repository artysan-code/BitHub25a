Oltre a fornire astrazioni come processi e thread, spazi degli indirizzi e file, un sistema operativo controlla anche tutti i dispositivi di I/O del computer, inviando comandi ai dispositivi, intercettando gli interrupt e gestendo gli errori. 

Per prima cosa vedremo alcuni dei principi dell’hardware per l’I/O, poi analizzeremo il software per l’I/O in generale. Il software per l’I/O può essere strutturato in livelli (layer), dove ciascuno svolge un’attività ben precisa.
## 5.1 - Principi hardware dell'I/O
L’hardware per l’I/O viene considerato da punti di vista diversi: gli ingegneri elettronici lo giudicano in termini di chip, cavi, alimentatori, motori e di qualsiasi altro componente fisico. I programmatori sono interessati all’interfaccia disponibile al software: comandi accettati dall’hardware, funzioni eseguibili e possibili errori. Il nostro interesse è focalizzato sulla programmazione dell’hardware e non sul suo funzionamento interno.

(pagine riassunte: 0.75)
### 5.1.1 - Dispositivi di I/O
I dispositivi di I/O si dividono principalmente in due categorie: **dispositivi a blocchi** e **dispositivi a caratteri**.
1. **Dispositivi a blocchi**: Archiviazione di informazioni in blocchi di dimensioni fisse, ciascuno con il proprio indirizzo. I trasferimenti avvengono in unità di uno o più blocchi consecutivi. Ogni blocco può essere letto o scritto indipendentemente dagli altri. Esempi: dischi rigidi magnetici e unità SSD.
2. **Dispositivi a caratteri**: Gestione di un flusso di caratteri senza struttura a blocchi, non indirizzabili e senza operazioni di ricerca. Esempi: tastiere e stampanti.
Questa classificazione non è perfetta, poiché alcuni dispositivi non rientrano in queste categorie, come i clock, che non sono indirizzabili a blocchi e non gestiscono flussi di caratteri, ma generano solo interrupt a intervalli definiti.

Nonostante le limitazioni, la suddivisione in dispositivi a blocchi e a caratteri è utile per rendere il software del sistema operativo indipendente dal tipo di dispositivo, come nel caso del file system, che si occupa solo di dispositivi a blocchi astratti.

Le diverse velocità dei dispositivi di I/O rappresentano una sfida per il software, che deve garantire buone prestazioni nel trasferimento dei dati.

(pagine riassunte: 0.75)
### 5.1.2 - Controller dei dispositivi
I dispositivi di I/O sono composti da una componente meccanica e una elettronica. La parte elettronica è chiamata **controller del dispositivo** o **adattatore**, mentre la parte meccanica è il dispositivo stesso. Questa separazione consente una progettazione modulare e standardizzata.

Se l'interfaccia tra controller e dispositivo segue standard ufficiali (ANSI, IEEE, ISO) o _de facto_, i produttori possono creare controller o dispositivi compatibili.

Il flusso seriale di bit che esce dal dispositivo inizia con un **preambolo** (contenente informazioni come il numero dei cilindri e dei settori), seguito dai 4096 bit del settore e da una **checksum** o **codice di correzione degli errori** (**ECC**). Il controller converte questo flusso in un blocco di byte, esegue le correzioni degli errori e, dopo aver verificato l'integrità dei dati, copia il blocco nella memoria principale.

I monitor LCD hanno rapidamente sostituito i vecchi monitor a **tubo catodico** (**CRT**). I CRT utilizzano un raggio di elettroni per disegnare i pixel su uno schermo fluorescente. Gli LCD, rispetto ai CRT, sono più leggeri, consumano meno energia e sono più resistenti. Inoltre, gli schermi LCD moderni hanno una risoluzione così alta che l'occhio umano non può distinguere i singoli pixel.

(pagine riassunte: 1)
### 5.1.3 - Input/Output mappato in memoria


(pagine riassunte: 3.25)
### 5.1.4 - Direct memory access (DMA)


(pagine riassunte: 3)
### 5.1.5 - Ancora sugli interrupt


(pagine riassunte: 3.5)
## 5.2 - Principi del software di I/O

### 5.2.1 - Obbiettivi del software di I/O

### 5.2.2 - I/O programmato

### 5.2.3 - I/O guidato dagli interrupt

### 5.2.4 - I/O con DMA

## 5.3 - Livelli del software di I/O

### 5.3.1 - Gestori  degli interrupt

### 5.3.2 - Driver di dispositivo

### 5.3.3 - Software per l'I/O indipendente dal dispositivo

### 5.3.4 - Software di I/O nello spazio utente

## 5.4 - Dischi

### 5.4.1 - Hardware dei dischi

### 5.4.2 - Formattazione dei dischi

### 5.4.3 - Algoritmi di scheduling del braccio del disco

### 5.4.4 - Gestione degli errori

### 5.4.5 - Memoria stabile

## 5.5 - Clock

### 5.5.1 - Hardware del clock

### 5.5.2 - Software del clock

### 5.5.3 - Soft timer

## 5.6 - Interfacce utente: tastiera, mouse e monitor

### 5.6.1 - Software di input

### 5.6.2 - Software di output

## 5.7 - Thin client

## 5.8 - Gestione del risparmio energetico

### 5.8.1 - Problemi relativi all'hardware

### 5.8.2 - Problemi relativi al sistema operativo

### 5.8.3 - Questioni relative ai programmi applicativi

## 5.9 - Stato della ricerca sull'input/output


[[8 - Sistemi a più processori|Prossimo Capitolo]]