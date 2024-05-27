Un computer è un sistema complesso, costituito da uno o più processori, dalla memoria centrale, da periferiche, ecc. 
Per questo motivo i computer dispongono di uno strato di software chiamato #sistema_operativo.
Gli utenti interagiscono con il sistema operativo tramite un programma: 
Quando è in modalità testo viene solitamente chiamato #shell, oppure #GUI quando si utilizzano icone. Attenzione: questo programma NON è il sistema operativo, bensì solo un'interfaccia per comunicarci.
Alla base ci sono i componenti hardware, come chip, schede, dischi, tastiere, ecc. Sopra l'hardware c'è il software.
La maggior parte dei computer ha due modalità operative: #kernel e #user.
Il sistema operativo è il componente di maggiore importanza e viene eseguito in modalità #kernel (chiamata anche modalità #supervisor). Questa modalità consente al sistema operativo di avere accesso a tutto l'hardware e può eseguire qualsiasi istruzione che la macchina sia in grado di svolgere. Il resto del software gira in modalità utente, in cui è disponibile solo un sottoinsieme di istruzioni macchina. 
L'interfaccia utente, #shell o #GUI, è il livello più basso di software in modalità utente e consente all'utente di avviare altri programmi.
Un'importante differenza fra il sistema operativo e il normale software (modalità utente) è che se a un utente non piace un particolare lettore di posta elettronica, sarà libero di sceglierne un altro o di scriverne uno suo se preferisce; non è libero di scrivere un suo gestore degli interrupt del clock, che è parte del sistema operativo e che è protetto tramite hardware dai tentativi di modifica da parte degli utenti.
Questa differenza, tuttavia, è meno evidente nei sistemi #embedded o #sistemi_integrati o #sistemi_interpretati.
Inoltre, in molti sistemi sistemi ci sono programmi che vengono eseguiti in modalità utente, ma che aiutano il sistema operativo a svolgere le sue funzioni, o che eseguono funzioni privilegiate.
I sistemi operativi differiscono dai programmi utente (le applicazioni) in molti altri modi, oltre che per la loro sede. In particolare, essi sono molto grandi, complessi e di lunga vita. 

## 1.1 Che cos'è un sistema operativo

E' difficile definire cosa sia un sistema operativo al di là della semplice affermazione che si tratta di software che gira in modalità kernel. Infatti, svolge due funzioni non correlate: semplifica la vita ai programmatori, dando loro accesso astratto alle risorse hardware; mentre allo stesso tempo le gestisce.

### 1.1.1 Il sistema operativo come macchina estesa

L'architettura della maggior parte dei computer, a livello di linguaggio macchina, è primitiva e complicata da programmare, specialmente per l'input e l'output. 
Per la gestione dell'hardware si utilizza appunto un software chiamato #driver. 
Un #driver non è altro che un'interfaccia per il sistema operativo/applicazioni per comunicare con il dispositivo per la quale il driver è stato ideato. 
I sistemi operativi possono contenere numerosi driver. 
Anche questo livello è fin troppo basso per la maggior parte delle applicazioni. Per questo motivo, tutti i sistemi operativi contengono un'ulteriore livello di astrazione, per utilizzare i dischi: i #file.
Mediante questa astrazione, i programmi possono leggere, scrivere e creare file.
Una buona astrazione suddivide un'attività quasi impossibili in due attività fattibili.

### 1.1.2 Il sistema operativo come gestore delle risorse

Il concetto di sistema operativo che fornisce principalmente astrazioni ai programmi applicativi è una visione top-down. Una visione alternativa, bottom-up, sostiene che il sistema operativo esiste per gestire tutti i pezzi di un sistema complesso. Il sistema operativo può mettere ordine al caos potenziale immagazzinando tutto l'output destinato alla stampante sul disco. Quando un programma ha terminato, il sistema operativo può copiare il suo output dal file su disco dove è stato immagazzinato per la stampante, mentre allo stesso tempo l'altro programma può continuare a generare altro output, dimentico del fatto che l'output non stia (ancora) andando alla stampante. La gestione delle risorse include il multiplexing (condivisione) delle risorse in due modalità diverse: nel tempo e nello spazio. Quando una risorsa è condivisa temporalmente, programmi o utenti diversi fanno a turno a usarla.

## 1.2 Storia dei sistemi operativi

Il primo vero computer digitale fu progettato dal matematico #charles_babbage (19792-1871).
Non riusci mai a costruire il suo #motore_analitico a causa della tecnologia primitiva dell'epoca. Babbage intui che servisse un software per gestire il suo motore analitico, quindi assunse Ada Lovelace per scriverne uno. Da qui prende il nome il linguaggio #Ada.

### 1.2.1  Prima generazione (1945-55): valvole termoioniche

Fa rima con Scoglioniche. 
La seconda guerra mondiale venne costruito quello che oggi è considerato il primo computer digitale funzionante (Prof #jhon_atanasoff e #clifford_berry, Iowa state university).
Utilizzava 300 #valvole. Nello stesso periodo, Konrad Zuse costruì a Berlino  il computer #Z3 fatto di #relè. Nel 1944 fu costruito il #Colossus, a Bletchley Park, In Inghilterra. Il #mark_1 fu costruito da Howard Aiken ad #Harvard. Lo #ENIAC da #William_Mauchley e il suo studente J. Presper Eckert all'università della pensilvania. Alcuni erano binari, altri usavano valvole, alcuni erano programmabili, ma erano tutti primitivi e impiegavano secondi per le operazioni più semplici.
Tutta la programmazione era fatta esclusivamente in linguaggio macchina o cablando circuiti. Negli anni 50' vennero introdotte le #schede_forate.

### 1.2.2 Seconda generazione (1955-65): transistor e sistemi batch

Con l'avvento dei #transistor negli anni 50, le macchine si evolsero.
Queste macchine, chiamate ora #mainframe, erano chiuse in sale computer dedicate e condizionate, dotate di squadre di operatori professionali che ne gestivano il funzionamento.
Solo grandi gruppi industriali o le maggiori agenzie governative oppure le università potevano permettersi il costo multimilionario. Per eseguire un #job (cioè un programma o un insieme di programmi) un programmatore doveva prima scrivere un programma su carta (in #FORTRAN o in assembler), poi perforarlo sulle #schede. Quando il computer finiva il programmatore poteva prendere l'output da una stampante. 
Questo sistema funzionava, ma era lento. Venne adottato il #sistema_batch : 
L'idea alla base era raccogliere una cassetta piena di job nella sala input per poi riversarli su un nastro magnetico usando un computer piccolo ed economico, come un #ibm_1401, che era abbastanza valido per leggere schede ma non per fare calcoli, a differenza di macchine come l' #ibm_7094. 
Tipico #job di input:
Partiva con una scheda #job, che specificava il tempo massimo di esecuzione in minuti, il numero utente cui veniva assegnata e il nome del programmatore. Poi veniva una scheda $FORTRAN che indicava al sistema operativo di caricare il compilatore #FORTRAN dal nastro di sistema. Era seguita direttamente dal programma da compilare e poi da una scheda #LOAD, che indicava al sistema operativo di caricare il programma oggetto appena compilato. Seguiva con la scheda #run, che indicava al sistema operativo di eseguire il programma. Il tutto terminava con la scheda #end.

### 1.2.3 Terza generazione (1965-85):

Negli anni 60 c'erano due linee ben distinte di computer, i #word_oriented come il 7094 (usati per calcoli scientifici) e i #character_oriented come il 1401 (usati per ordinamento su nastro da banche e compagnie assicurative).
#ibm provò ad unificare le due linee con il #System/360 : una macchina piccola come il 1401 ma più potente di un 7094. Ogni macchina 360 era compatibile con la sua versione più/meno potente, quindi un programma scritto su una di queste macchine poteva girare su ognuna di esse. Versioni successive: 370, 4300, 3080, 3090. La serie #Z è discendente di queste versioni.
IBM 360 fu la prima linea di computer ad adottare (su bassa scala) gli #IC ( #integrated_circuits - circuiti integrati), garantendo così un miglior rapporto prezzo/prestazioni rispetto alle macchine di generazione precedente, costruite con transistor individuali. Fu un successo immediato e l'idea di una famiglia di computer compatibili fu presto adottata da tutti gli altri principali produttori. I discendenti di queste macchine sono tuttora in uso nei centri di calcolo. Attualmente sono spesso usati per gestire grandi basi di dati (per esempio, i sistemi di prenotazione di compagnie aeree) o come server per siti World Wide Web che devono elaborare migliaia di richieste per secondo.
Nonostante i migliaia di bug e problemi che questo sistema aveva, introdusse dei concetti rivoluzionari, tra cui la #multi_programmazione .
Sul 7094, quando il lavoro in corso si fermava per un nastro o per completare un'altra operazione di I/O, la #cpu si poneva in stato inattivo finché l'I/O terminava. Con calcoli scientifici strettamente legati alla #cpu, l'I/O non è frequente, cosicché questo tempo sprecato non è significativo. Con l'elaborazione di dati commerciali, il tempo di attesa dell'I/O può essere dall'80 al 90 percento del tempo totale, quindi la #cpu rimarrebbe per molto tempo inattiva.
La soluzione pensata fu di partizionare la memoria in tanti pezzi, assegnando un diverso lavoro a ogni partizione. Mentre un lavoro rimaneva in attesa del completamento dell'I/O, un altro poteva usufruire della cpu. Se potevano essere tenuti in memoria abbastanza lavori contemporaneamente, la cpu sarebbe stata tenuta occupata quasi al 100 percento del tempo.
Un'altra importante caratteristica dei sistemi operativi di quarta generazione era la capacità di leggere i lavori delle schede sul disco appena venivano portati in sala macchine. Questa tecnica è chiamata #spooling (simultaneous peripheral operation on line) e fu usata anche in output. (anche se tutto questo era ancora un sistema #batch).
Da qui nacque il #time_sharing, un sistema che permetteva a più utenti di usare il computer contemporaneamente. Il primo sistema di time sharing fu inventato dal M.I.T. su un 7094.
Da questo concetto nacque il #multics,  un'unica macchina in grado di gestire migliaia di utenti, nonostante a mala pena più potente di un 386. Non ebbe un grande successo a causa del suo terribile compilatore in PL/I.
Nonostante questo, il multics venne realizzato e venduto a molte aziende grandi. Tant'è che aziende come General Motors, Ford, ecc, spensero i loro multics negli anni 90'.
Questo tipo di sistema si chiamava #computer_utility, ed è una sorta di precursore dei #cloud moderni.
 Ken Thompson, scienziato dei Bell Labs, scrisse una versione ridotta e monoutente del multics, che venne poi chiamato #unix. Da li nacquero varie versioni, tutte incompatibili fra loro, di unix. Una delle quali è #minix (versione didattica), che venne aggiornata e fatta evolvere fino a diventare #minix_3.
 Uno studente finlandese (Linus Torvalds) decisse di scrivere una versione aperta e libera di minix 3, creando così #linux. 
### Quarta generazione (dal 1980 a oggi): i personal computer.

Grazie allo sviluppo dei circuiti #lsi, ovvero chip contenenti migliaia di transistor si un centimetro quadrato di silicio, iniziò la strada dei personal computer. Nel 1974 #Intel usci con l'8080, prima cpu a 8-bit per utilizzo generico. Nel 1977 la #Digital_Research riscrisse il CP/M (sistema operativo basato su floppy disk). Quando ad IBM servì un sistema operativo , #Bill_Gates contattò  un produttore locale di computer : Seattle computer products. Loro avevano sviluppato il #DOS (disk operating system), che venne comprato dall'azienda nascente #Microsoft. 
Microsoft adattò il DOS per IBM, chiamandolo #MS-DOS, dominando il mercato dei pc IBM.
Quando nel 1983 uscì il successore del pc ibm, l'ibm #pc/at, con una cpu intel 80286, l'MS-DOS era saldamente consolidato. Questo sistema operativo era molto primitivo, ma offriva qualche funzione avanzata da #UNIX.
Negli anni 60' #Engelbart inventò le #GUI (graphical user interface) con tanto di finestre, icone, menu e mouse. Queste idee vennero adottate dai ricercatori dello #Xerox #PARC e incorporate nelle loro macchine.
#Steve_Jobs, realizzò immediatamente il suo valore potenziale, cosa non riuscita ai dirigenti di #Xerox.
Jobs quindi si imbarcò nella costruzione di un #Apple con una GUI. 
L'Apple #Macintosh, fu un enorme successo, non solo perché poco costoso, ma anche perché era user friendly. 
Nel 1999, Apple adottò un kernel derivato dal #microkernel #Mach della #Carnegie_Mellon_University, originariamente sviluppato per sostituire il kernel di #BSD UNIX. #Mac_OS_X è pertanto un sistema operativo basato su UNIX, anche se con un'interfaccia assolutamente unica. 
Quando Microsoft decise di costruire un successore per I'MS-DOS fu fortemente influenzata dal successo del Macintosh. Produsse un sistema basato sulla GUI chiamato Windows che originariamente girava sopra all'MS-DOS.
Per circa 10 anni, dal 1985 al 1995, Windows è stato solo un ambiente grafico al di sopra del MS-DOS. Tuttavia, a partire dal 1995 fu rilasciata una versione a sé stante di #Windows,
#Windows_95, che includeva parecchie caratteristiche sottostante sistema MS-DOS solo per l'avvio e l'esecuzione dei vechi programmi MS-DOS.
Nel 1998 usci #Windows_98,  ed in seguito #Windows_nt.
Microsoft si aspettava che la prima versione di NT neutralizzasse l'MS-DOS, ma non andò così.
Microsoft uscì con un'altra versione di windows 98, chiamata #Windows-ME.
Nel 2001 uscì una versione leggermente aggiornata di Windows 2000, chiamata #Windows_XP.
Nel gennaio 2007, microsoft rilasciò il suo successore, #Windows_Vista.
Non fu un grande successo, quindi rilasciarono #Windows_7, una versione nuova del sistema operativo, migliorata e più performante. Questo sistema fu superato successivamente da Windows 8, nel 2012.
Altri fatti: 
Anche #FreeBSD è un popolare derivato di UNIX, che trae origine dal progetto BSD di Berkeley. Tutti i moderni computer Macintosh eseguono una versione modificata di FreeBSD. 
Molti utenti UNIX, specialmente tra i programmatori esperti, preferiscono un'interfaccia a riga di comando rispetto a una GUI, così quasi tutti i sistemi UNIX supportano un sistema a finestre chiamato X Window System (anche noto come X11) prodotto da M.I.T.
Questo sistema controlla la gestione di base delle finestre, consentendo agli utenti di creare, cancellare, muovere e ridimensionare finestre con il mouse. Spesso è disponibile una GUI completa, come Gnome o KDE eseguita sopra X11 che conferisce a UNIX un aspetto simile a Macintosh o Microsoft Windows, per gli utenti UNIX che lo desiderano.

### La quinta generazione (1990-oggi): i computer mobili
Il primo vero #telefono #portatile apparve negli anni '70 e, con il suo peso di circa un chilo-grammo, era veramente leggero; il suo affettuoso nomignolo era "il mattone"
Oggi, la penetrazione dei telefoni mobili è prossima al 90% della popolazione del globo. 
Il primo vero smartphone apparve sul mercato solo alla metà degli anni '90, quando Nokia presentò il suo N9000, che combinava insieme due apparecchi separati: un telefono e un PDA (personal digital assistant, assistente digitale personale). Nel 1997, Ericsson coniò il termine "smartphone" per il proprio apparecchio GS88 "Penelope"
Il sistema operativo dominante è Android, di Google, con Apple iOS in seconda posizione, ma non è così dappertutto e nel giro di pochi anni la situazione potrebbe cambiare profondamente. D'altro canto, la maggior parte degli smartphone nell'ultimo decennio, dopo la loro uscita, eseguivano Symbian OS, il sistema operativo preferito da produttori come Samsung, Sony Ericsson, Motorola e soprattutto Nokia.

## 1.3 Analisi dell'hardware

Un sistema operativo è intimamente legato con l'hardware su cui gira. Per operare deve avere molte informazioni riguardo l'hardware. 

### 1.3.1 Processori 
Il cervello del computer è la CPU. Essa preleva le istruzioni dalla memoria (esegue il #fetch) e le esegue. Il ciclo base di ogni CPU è prelevare la prima istruzione dalla memoria, decodificarla al fine di determinarne il tipo e gli operandi, eseguirla e poi prelevare, decodificare ed eseguire le successive. Il ciclo è ripetuto finché il programma termina. I programmi vengono eseguiti in questo modo.
Ogni CPU ha un insieme specifico di istruzioni che può eseguire. Così un processore
x86 non può eseguire programmi scritti per ARM e un processore ARM non può eseguire programmi per x86. Tutte le CPU contengono all'interno alcuni registri per memorizzare variabili importanti o risultati temporanei.


# file da sottoporre a revisione