Il seguente capitolo tratta, come dice il titolo, l'organizzazione hardware di un sistema di calcolo completo: componenti, tecniche di sviluppo, miglioramenti.
## Processori

La **CPU** (*Central Process Unit*) è il cervello della macchina ed esegue tutti i programmi prelevandoli dalla memoria. Essa è connessa internamente ed esternamente ai componenti tramite i **bus**, che per ora vediamo come un insieme di cavi paralleli sui quali vengono trasmessi indirizzi, dati e segnali di controllo.

La CPU è composta da diverse unità, quali la **CU** (*Control Unit*), la **ALU** e diversi registri che fungono da piccola memoria ma con alte velocità di lettura e scrittura. Tra i registri più importanti abbiamo il **Program Counter** e l'**Instruction Register** che rispettivamente puntano alla istruzione successiva e contengono l'istruzione corrente.
### Organizzazione della CPU

Il **percorso dati** (Letteralmente il percorso che esegue un dato) di una tipica CPU di von Neumann è composta da: *1 a 32 registri*, una *ALU* e dei *bus* che connettono i registri, a registri di input, alla ALU, etc\... La ALU esegue semplici operazioni il cui output viene salvato in registri di output.

Esistono due tipologie di operazioni: quelle di **registro-memoria** che prelevano informazioni dalla memoria e le inseriscono nei registri e quelle di **registro-registro** che spostano informazioni o le forniscono alla ALU e poi le spostano nel registro di output. Tutto il lavoro svolto dalla ALU e i suoi registri è chiamato **ciclo del percorso dati** e rappresenta il cuore della maggior parte delle CPU.
### Esecuzione dell'istruzione 

Il **ciclo esecutivo delle istruzioni** sono i passaggi per permettere alla CPU di eseguire una istruzione, si chiama anche **fetch-decode-execute**. I passaggi generalmente sono i seguenti: 
- Prelevare l'istruzione successiva della memoria e portarla nell'IR. 
- Modificare il PC per puntarlo all'istruzione seguente.
- Decodificare l'istruzione interna all'IR.
- Se l'istruzione usa una parola di memoria