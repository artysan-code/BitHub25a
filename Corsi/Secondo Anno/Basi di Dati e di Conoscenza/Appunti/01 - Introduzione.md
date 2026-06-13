## Dati, informazioni e sistemi informativi

> [!quote] Definizione — Dato
> In informatica, la singola informazione codificabile o codificata (elementi di informazione costituiti da simboli che debbono essere elaborati). Ciò che è immediatamente presente alla conoscenza, prima di ogni elaborazione.

> [!quote] Definizione — Informazione
> Una notizia, un dato o un elemento che consente di avere conoscenza più o meno esatta di fatti, situazioni o modi di essere.

> [!example] 8 e Ferrari
> "8 e Ferrari scritti su un foglio di carta sono due dati, da soli non significano nulla… se il foglio è relativo alle ordinazioni di un ristorante la notte di Capodanno, allora rappresenta l'ordinazione di una bottiglia di spumante marca Ferrari da addebitare alla stanza 8."
> Con le indicazioni aggiuntive i dati diventano informazioni e arricchiscono la conoscenza.

L'evoluzione della tecnologia permette oggi di raccogliere un'enorme quantità di dati in maniera pervasiva e continua (social, smartphone, smartwatch, ecc.). Le grandi quantità di dati digitali accumulate nelle reti di calcolatori costituiscono una risorsa enorme con requisiti critici rispetto all'**efficienza dei metodi di accesso**, **integrazione**, **localizzazione**, **persistenza**, **condivisione**, **affidabilità**, **privatezza** e **riutilizzo** in applicazioni eterogenee.
Questo ha reso necessaria una corretta ed efficiente gestione dei dati, che è sempre stata la base per la buona realizzazione di qualsiasi **sistema informativo**.

> [!quote] Definizione — Sistema informativo
> Componente (**sottosistema**) di un'organizzazione che gestisce (acquisisce, elabora, conserva, produce) le informazioni di interesse, cioè quelle utilizzate per il perseguimento degli scopi dell'organizzazione.

- Ogni organizzazione ha un sistema informativo, anche se non esplicitato nella struttura.
- Quasi sempre questo è di supporto ad altri sottosistemi, va quindi studiato nel contesto in cui è inserito.
- Il sistema informativo è in genere suddiviso in più sottosistemi più o meno fortemente integrati.
Il concetto di sistema informativo è **indipendente da qualsiasi automazione**: esistono organizzazioni la cui ragione d'essere è la gestione d'informazioni (es. servizi anagrafici e banche) e che esistono da secoli. Per la parte automatizzata del sistema informativo, al giorno d'oggi viene usato il termine **sistema informatico**.
```
Sistema Azienda
  └── Sistema Informativo
        └── Sistema Informatico
```
### Le risorse di una organizzazione
Ogni organizzazione dispone di risorse fondamentali:
- Persone
- Denaro
- Materiali
- **Informazioni**
Le informazioni sono quindi una risorsa fondamentale quanto le risorse materiali e finanziarie.
### Funzioni di un sistema informativo
Un sistema informativo svolge le seguenti funzioni:
- **Acquisizione** delle informazioni
- **Conservazione** delle informazioni
- **Elaborazione** delle informazioni
- **Distribuzione e scambio** delle informazioni
Nelle attività umane, le informazioni vengono gestite (registrate e scambiate) in forme diverse:
- Idee informali
- Linguaggio naturale
- Disegni, grafici, schemi
- Numeri e codici
...e su vari supporti: memoria umana, carta, dispositivi elettronici.

> [!example] Evoluzione della codifica — Servizi anagrafici
> Nelle attività standardizzate dei sistemi informativi complessi, sono state introdotte nel tempo forme di organizzazione e codifica delle informazioni. Nei servizi anagrafici si è passati da registrazioni discorsive a:
> - **Nome e cognome**
> - **Estremi anagrafici**
> - **Codice Fiscale**

Nei sistemi informatici, le informazioni vengono rappresentate in modo essenziale attraverso i **dati**: approssimativamente i dati non hanno alcun significato da soli, ma se correlati e interpretati forniscono informazioni che consentono di arricchire la nostra conoscenza del mondo.
### I dati come risorsa strategica
I dati costituiscono spesso una **risorsa strategica**, perché più stabili nel tempo rispetto ad altre componenti (processi, tecnologie, ruoli umani).

> [!example] Dati bancari
> I dati bancari hanno una struttura invariata da decenni. Le applicazioni che operano su essi invece cambiano di frequente. La nuova procedura "eredita" i dati dalla vecchia con opportune trasformazioni.

Vista la loro stabilità, i dati costituiscono una risorsa per l'organizzazione, un **patrimonio da sfruttare e proteggere**.
## Base di dati
All'interno del sistema informativo, la collezione dei dati è chiamata **Base di Dati** o **Database**. Il suo compito è non solo memorizzare i dati ma rappresentare anche le relazioni tra di essi. Il software atto specificatamente a gestire i dati è il **Database Management System** (DBMS). Tradizionalmente adottato nei sistemi informativi di grandi dimensioni (solitamente composti da più programmi), oggi è adottato anche da sistemi più semplici.
La base di dati ha due accezioni:
- **(accezione generica, metodologica)**: insieme organizzato di dati utilizzati per il supporto allo svolgimento delle attività di un ente (azienda, ufficio, persona).
- **(accezione specifica, metodologica e tecnologica)**: insieme di dati gestito da un DBMS.

> [!quote] Definizione — Base di dati (Brunella Longo, 1993)
> "Collezione di informazioni registrate in formato leggibile dall'elaboratore elettronico e relativa ad un preciso dominio di conoscenze (azienda, università, mente di qualcuno, ecc.), organizzata allo scopo di poter essere consultata dai suoi utilizzatori."

> [!quote] Definizione — Data independence
> La struttura di un DB deve dare garanzia che modifiche dei dati non richiedano modifiche ai programmi applicativi e/o alle tecniche di accesso ai dati stessi.

> [!quote] Definizione — DBMS
> Un **Database Management System** è un *prodotto software* in grado di gestire **collezioni di dati** che siano (anche):
> - **Grandi** (di dimensioni molto maggiori alla memoria centrale dei sistemi di calcolo utilizzati)
> - **Persistenti** (con un periodo di vita indipendente dalle singole esecuzioni dei programmi che le utilizzano)
> - **Condivise** (utilizzate da applicazioni e utenti diversi)

Il DBMS garantisce **affidabilità** (resistenza a malfunzionamenti hardware e software) e **privatezza** (con una disciplina e un controllo degli accessi). Come ogni prodotto informatico, un DBMS deve essere **efficiente** (utilizzando al meglio le risorse di spazio e tempo del sistema) ed **efficace** (rendendo produttive le attività dei suoi utilizzatori).
## Archivio di file
L'approccio classico usato dai programmi che compongono il sistema informativo per la gestione delle informazioni è un **archivio basato su files**. Ogni programma ha accesso al file system gestito dal sistema operativo per creare uno o più files (archivi).
Ogni file è un insieme di **registrazioni** (record) all'interno dei quali sono memorizzati i dati elementari (**attributi e campi**). La condivisione di dati tra più programmi può avvenire tramite l'uso di file condivisi.
I file possono avere diverse tipologie di formati **non compatibili** tra loro; i programmi si devono adeguare di conseguenza a diverse convenzioni anche a distanza di parecchio tempo. Questo rende la condivisione dei dati attraverso applicazioni differenti **difficoltosa**.
I dati **non memorizzati su file condivisi** vengono **replicati** con spreco di risorse di memorizzazione e possibili problemi legati a inconsistenze. Inoltre, l'accesso a file in condivisione porta a dover gestire la **concorrenza con soluzioni ad-hoc** (specialmente se due o più programmi vogliono modificarne il contenuto).
### Approccio basato su DBMS
L'approccio basato su DBMS va oltre l'uso di file locali gestiti dalle singole applicazioni tramite l'adozione di un sistema di gestione dei dati che risulta **indipendente** dalle applicazioni e **specializzato** in tale funzione:
- I dati non sono gestiti dalle singole applicazioni ma da un DBMS che offre **un'interfaccia comune** a tutte le applicazioni.
- Si interpone fra le applicazioni e la memoria di massa.
- I dati non appartengono ad una singola applicazione, ma tutte vi accedono attraverso il DBMS.
## Condivisione
Ogni organizzazione generalmente è divisa in settori, a ciascuno dei quali corrisponde un sottosistema informativo. Possono esistere sovrapposizioni fra i dati di interesse dei vari settori. Una base di dati è una risorsa **integrata**, in quanto condivisa fra i vari settori.
Una base di dati permette di:
- **Ridurre la ridondanza**: una base di dati centralizzata permette di ridurre la replica della stessa informazione che si avrebbe se le diverse applicazioni gestissero i dati tramite file locali.
- **Ridurre l'inconsistenza**: l'eliminazione della presenza di varie copie dello stesso dato elimina la possibilità di inconsistenze; la gestione attraverso una componente specializzata permette di introdurre controlli sui dati per garantirne la consistenza.
I DBMS sono componenti software specializzati nel gestire grandi quantità di dati e implementano procedure basate sulle best-practices per la gestione di:
- **Efficacia e efficienza**: le tecniche di memorizzazione adottate permettono di migliorare le prestazioni di memorizzazione e accesso alle informazioni.
- **Affidabilità**: tecniche di salvaguardia e verifica dell'integrità dei dati in caso di malfunzionamenti hardware e software (*crash recovery*).
- **Concorrenza**: metodologie per garantire un accesso concorrente ai dati minimizzandone l'impatto sulle prestazioni (es. limitando i tempi di attesa in seguito alla mutua esclusione su un dato).
- **Privatezza**: tecniche di sicurezza per garantire accesso ristretto, in modo che ciascun utente acceda solo al sottoinsieme dei dati a cui è autorizzato.
- **Riduzione del tempo di sviluppo**: invece di implementare le funzionalità di gestione dei dati, ogni applicazione si appoggia su quelle fornite dal DBMS.
- **Semplificazione e standardizzazione dello sviluppo**: la memorizzazione e la gestione dei dati è demandata ad una componente con la quale l'applicazione interagisce tramite un'interfaccia standard.

> [!info] Grandi quantità e persistenza
> I dati gestiti da una base di dati sono di solito più della memoria centrale e vanno quindi gestiti in memoria secondaria. L'unico limite deve essere la dimensione della memoria secondaria; nelle basi di dati distribuite neanche questo rappresenta un problema. I dati hanno inoltre un **ciclo di vita** che dura nel tempo, il che è un'altra ragione per la loro gestione in memoria secondaria.
