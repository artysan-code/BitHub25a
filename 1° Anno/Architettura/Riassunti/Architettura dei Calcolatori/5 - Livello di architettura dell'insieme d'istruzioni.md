Questo capitolo descrive il livello di architettura dell'insieme d'istruzioni (ISA), posizionato tra la microarchitettura e il sistema operativo. L'ISA è fondamentale per i progettisti di sistemi perché costituisce l'interfaccia tra software e hardware.

I progettisti traducono i linguaggi di alto livello nell'ISA e costruiscono l'hardware per eseguirlo. Quando si sviluppa una nuova macchina, è cruciale mantenere la compatibilità con i modelli precedenti, sia per il sistema operativo che per le applicazioni. Questo garantisce che i vecchi programmi funzionino sui nuovi processori, preservando l'investimento degli utenti nel loro software.

Gli ISA devono essere efficienti per essere economicamente vantaggiosi. Un buon ISA richiede meno risorse hardware e supporta una compilazione del codice efficace, rendendo più semplice per i compilatori generare codice ottimizzato. In sintesi, l'ISA deve soddisfare le esigenze sia dei progettisti hardware che software.

(pagine riassunte: 3)
## 5.1 - Panoramica del livello ISA
Per iniziare lo studio del livello ISA, chiediamoci cos'è. Sebbene sembri una domanda semplice, essa presenta diverse complicazioni. Esamineremo alcune questioni controverse e poi analizzeremo modelli di memoria, registri e istruzioni.
### 5.1.1 - Proprietà del livello ISA

### 5.1.2 - Modelli della memoria

### 5.1.3 - Registri

### 5.1.4 - Istruzioni

### 5.1.5 - Panoramica del livello ISA del Core i7

### 5.1.6 - Panoramica del livello ISA dell'OMAP4430 ARM

### 5.1.7 - Panoramica del livello ISA dell'ATmega168 AVR

## 5.2 - Tipi di dati
### 5.2.1 - Tipi di dati numerici

### 5.2.2 - Tipi di dati non numerici

### 5.2.3 - Tipi di dati del Core i7

### 5.2.4 - Tipi di dati dell'OMAP4430 ARM

### 5.2.5 - Tipi di dati dell'ATmega168

## 5.3 - Formati d'istruzione
### 5.3.1 - Criteri progettuali per i formati d'istruzoni

### 5.3.2 - Codice operativo espandibile

### 5.3.3 - Formati delle istruzioni del Core i7

### 5.3.4 - Formati delle istruzioni dell'OMAP4430 ARM

### 5.3.5 - Formati delle istruzioni dell'ATmega168

## 5.4 - Indirizzamento 
### 5.4.1 - Modalità d'indirizzamento

### 5.4.2 - Indirizzamento immediato

### 5.4.3 - Indirizzamento diretto

### 5.4.4 - Indirizzamento a registro

### 5.4.5 - Indirizzamento a registro indiretto

### 5.4.6 - Indirizzamento indicizzato

### 5.4.7 - Indirizzamento indicizzato esteso

### 5.4.8 - Indirizzamento a stack

### 5.4.9 - Modalità d'indirizzamento per istruzioni di salto

### 5.4.10 - Modalità d'indirizzamento dei codici operativi e delle modalità d'indirizzamento

### 5.4.11 - Modalità d'indirizzamento del Core i7

### 5.4.12 - Modalità d'indirizzamento dell'OMAP4430

### 5.4.13 - Modalità d'indirizzamento dell'ATmega168 AVR

### 5.4.14 - Analisi delle modalità d'indirizzamento

## 5.5 - Tipi d'istruzioni
### 5.5.1 - Istruzioni di trasferimento dati

### 5.5.2 - Operazioni binarie

### 5.5.3 - Operazioni unarie

### 5.5.4 - Confronti e salti condizionati

### 5.5.5 - Invocazione di procedura

### 5.5.6 - Istruzioni di ciclo

### 5.5.7 - Input/Output

### 5.5.8 - Istruzioni del Core i7

### 5.5.9 - Istruzioni della CPU ARM OMAP4430

### 5.5.10 - Istruzioni dell'ATmega168 AVR

### 5.5.11 - Insieme d'istruzioni a confronto

## 5.6 - Controllo del flusso
### 5.6.1 - Flusso sequenziale e diramazioni

### 5.6.2 - Procedure

### 5.6.3 - Coroutine

### 5.6.4 - Trap

### 5.6.5 - Interrupt

## 5.8 - Architettura IA-64 e Itanium 2
### 5.8.1 - Il problema dell'ISA IA-32

### 5.8.2 - Modello IA-64 e calcolo che utilizza il parallelismo esplicito

### 5.8.3 - Riduzione degli accessi in memoria

### 5.8.4 - Scheduling delle istruzioni

### 5.8.5 - Riduzione dei salti condizionati: attribuzione di predicati

### 5.8.6 - Caricamenti speculativi

