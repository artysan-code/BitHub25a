## Dati, informazioni e sistemi informativi
Un **dato** è in informatica la singola informazione codificabile o codificata, ciò che è immediatamente presente alla conoscenza, prima di ogni elaborazione.

Un **informazione** è una notizia, un dato o un elemento che consente di avere conoscenza più o meno esatta di fatti, situazioni o modi di essere.

Con le indicazioni aggiuntive i dati diventano informazioni e arricchiscono la conoscenza.  ("8 e Ferrari scritti su un foglio non significano nulla")

L'evoluzione della tecnologia permette oggi di raccogliere un'enorme quantità di dati: dallo smartwatch grazie ai social e ad internet, dallo smartwatch per le informazioni rapide, etc... Grazie a ciò abbiamo sviluppato una corretta ed efficiente gestione dei dati che è sempre stata la base di un corretto **sistema informativo**.

Un **sistema informativo** è un componente (sottosistema) di un'organizzazione che gestisce o acquisisce le informazioni di interesse di questa prima.
- Ogni organizzazione ha un sistema informativo, anche se non esplicitato nella struttura.
- Quasi sempre questo è supporto di altri sottosistemi della struttura, va quindi studiato nel contesto in cui è inserito.
- Il sistema informativo è in genre suddiviso in più sottosistemi fortemente integrati.

Il concetto è indipendente da qualsiasi automazione. Per la parte automatizzata del sistema informativo oggi viene chiamata **sistema informatico** (diverso dal sistema informativo).

Nelle attività standardizzate dei sistemi informativi complessi, sono state introdotte nel tempo forme di organizzazione e codifica delle informazioni. Esempio, nei servizi anagrafici si usa ora:
- Nome e cognome
- Estremi Anagrafici
- Codice Fiscale

Nelle attività umane le informazioni vengono gestite in tante maniere diverse, ma nei sistemi informatici le informazioni sono gestite attraverso i *dati*, che rappresentati al meglio formano le informazioni.

Possiamo quindi introdurre il concetto di **Base di Dati** o **Database**, che non solo rappresenta i dati ma anche le relazioni tra essi. Il software che esegue l'azione di gestire i dati è il **Database Management System**. Inizialmente veniva usato nei sistemi che utilizzano tante informazioni, oggi invece viene adottato nei sistemi anche più piccoli.

## Base di dati
Una *base di dati* è un insieme organizzato di dati utilizzato per il supporto allo svolgimento delle attività di un ente (o insieme di dati gestito da un DBMS).

La **data independence** pone come principio che la modifica dei dati in un database non richieda modifiche ai programmi applicativi o ai metodi di accesso ai dati di questi ultimi.

Diamo allora una migliore definizione ai DBMS:

> Un **Database Management System** è un *prodotto software* in grado di gestire **collezioni di dati** che siano (anche):
> - Grandi dimensioni (molto maggiori alla dimensione della memoria centrale).
> - Persistenti (rimangano disponibili per un periodo di vita definito o non definito)
> - Condivise (Usate da applicazioni e utenti diversi)

^98fc74

Il DBMS garantisce affidabilità e sicurezza dei dati che organizza, inoltre deve essere **efficiente** ed **efficacie**. Offre anche soprattutto **privatezza**, con un sistema di gestione degli accessi. La logica di coerenza non viene imposta dal DBMS, ma dalla logica fornita dal linguaggio che utilizza questo primo.

## Archivio di file
L'approccio classico usato dai programmi che compongono il sistema informativo per la gestione delle 
informazioni è un **archivio basato su files**. Ogni programma ha accesso al file system gestito dal sistema operativo per creare uno o più files.

I file possono avere diverse tipologie di formati **non compatibili** tra loro, i programmi si devono adeguare di conseguenza a diverse convenzioni. Questo rende la condivisione dei dati attraverso applicazioni differenti difficoltosa. 

I dati **non memorizzati su file condivisi** vengono replicati con spreco di risorse di memorizzazione e possibili problemi legati a inconsistenze. Questo problema ha portato gli sviluppatori a voler trovare una **soluzione ad-hoc** per la gestione.

## Condivisione
Ogni organizzazione generalmente è divisa in settori, a cui è associato un sottosistema informativo che possono però avere **risorse condivise** tra di loro. Una base di dati è una risorsa **integrata**, in quanto condivisa da vari settori.

Una base di dati permette di:
- **Ridurre la ridondanza**, permette di ridurre le repliche di dati che possono aumentare lo spazio utilizzato e quindi rendere meno efficiente la memorizzazione.
- **Ridurre l'inconsistenza**: permette di non avere diverse copie di un dato con diverse versioni, così da trattenere la consistenza attraverso delle tecniche gestite internamente.

Queste *best-practice* permetto a sistemi DBMS di fornire 
- *Efficienza* ed *Efficacia*
- *Affidabilità*
- *Concorrenza*
- *Privatezza*
- *Riduzione del tempo di sviluppo*
- *Semplificazione e standardizzazione dello sviluppo*
