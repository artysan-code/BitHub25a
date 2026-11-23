---
tags:
  - intelligenza-artificiale
  - logica
  - logica-del-primo-ordine
slide:
  - "0042_Logic_CalPredicati_26_27_v1.4.1.pdf"
---
# Logica del primo ordine
## Sintassi, semantica e inferenza nella logica del primo ordine
Lezione 11 (09/11/2026): dopo sintassi, semantica e risoluzione della [[04 - Agenti basati sulla conoscenza#Sintassi della logica proposizionale|logica proposizionale]], si introduce la **logica del primo ordine** (*first order logic*, FOL, o calcolo dei predicati): vocabolario, termini e formule, quantificatori e variabili libere e legate, interpretazione e semantica composizionale, uso da parte di un agente (TELL e ASK con sostituzioni) e i due modi di fare inferenza, la proposizionalizzazione e la risoluzione con unificazione (AIMA cap. 8-9). Per buona parte della lezione il docente collega la logica alle rappresentazioni vettoriali dei modelli neurali e al modo in cui un LLM "impara" la logica. Slide: `0042_Logic_CalPredicati_26_27_v1.4.1.pdf`, pp. 1-64 (alcune slide sono di Maria Simi, Università di Pisa).

> [!info] Fonti della nota
> - Le sezioni non indicate come ricostruite dalle slide, e «Logica e LLM», nascono dalla registrazione del 09/11/2026 e sono state confrontate con le slide: dove c'è la pagina è citata («slide p. N»); ciò che è solo nella registrazione è detto «a lezione».
> - Le sezioni dedicate a regole di istanziazione, Herbrand, forma a clausole, unificazione e risoluzione nel primo ordine vengono dalle sole slide (vedi i callout in testa).
> - Mancano la lezione 10 (04/11/2026), di cui non c'è registrazione, e le slide `Risoluzione.pdf` e `ResoLutionExample.pdf` che il sito del corso collega a questa parte: non sono nel repo.
> - La slide ha il piano a p. 2: logica dei predicati, sintassi e semantica, inferenza, formule ground e interpretazione di Herbrand, risoluzione e completezza (unificazione, algoritmi di risoluzione, «introduzione alla programmazione logica»). Le ultime slide (pp. 63-64) chiudono con la risoluzione per refutazione: la programmazione logica non è sviluppata, e l'interpretazione di Herbrand non è definita.
### Perché il primo ordine
Nel corso di Basi di Dati il dominio si concettualizza con **entità** (gli oggetti di cui si parla), i loro **attributi** e le **relazioni** tra entità. Nel calcolo proposizionale questo non si può fare: le proposizioni sono "chiuse", senza struttura interna. Serve dare un **nome** alle entità, alle proprietà e alle relazioni, e poter dire che cosa è vero: che uno studente ha una certa matricola è una relazione tra un'entità e una sua proprietà. Queste affermazioni sono **predicazioni**: un predicato è vero o falso su uno o più argomenti.

Nella logica dei predicati si hanno **assunzioni ontologiche** più ricche: oggetti, proprietà e relazioni (slide p. 3). Si parte da una **concettualizzazione**, cioè dalla decisione su quali cose interessano:
- gli **oggetti** (un libro, un evento, una persona, un istante di tempo, un insieme, una funzione, un unicorno...), identificati con simboli o relativamente ad altri oggetti mediante funzioni ("la madre di Pietro"); l'insieme degli oggetti rilevanti è il **dominio del discorso**, e può essere infinito;
- le **proprietà** ("la madre di Pietro è simpatica");
- le **relazioni** tra oggetti ("Pietro è amico di Paolo").

Il linguaggio ha quattro ingredienti:
- **costanti**: i nomi degli oggetti del mondo (nel mondo dei blocchi, un nome per ciascuno dei blocchi $A,\dots,E$ del [[04 - Agenti basati sulla conoscenza#Il mondo dei blocchi|mondo dei blocchi]]); ogni costante denota un oggetto del dominio, ma due costanti possono denotare lo stesso oggetto, a meno di assumere i nomi unici (vedi sotto);
- **variabili**, che stanno per un oggetto non ancora specificato;
- **funzioni**: da uno o più oggetti del dominio danno un **altro oggetto** del dominio, come $+1$ applicato a 5 dà 6. Ad esempio $\mathit{FratelloDi}(\mathit{Roberto})$ non è Roberto, ma un'altra persona, e $\mathit{Hat}(b)$ è il blocco sopra $b$. Le funzioni non stabiliscono verità, servono a calcolare altri oggetti;
- **predicati**: da uno o più oggetti danno **vero o falso**. $\mathit{Simpatica}(\mathit{MadreDi}(\mathit{Pietro}))$ predica una proprietà, $\mathit{Amico}(\mathit{Pietro},\mathit{Paolo})$ una relazione.

La differenza tra funzioni e predicati è nel codominio: le funzioni vanno dal dominio al dominio, i predicati dal dominio a $\{\mathit{vero},\mathit{falso}\}$.

> [!info] Simboli e oggetti
> Il simbolo $A$ e il blocco $A$ non sono la stessa cosa: il primo appartiene al linguaggio, il secondo al mondo, e una **legge di interpretazione** collega l'uno all'altro. Lo stesso vale per i numeri: "1/3" e "0,333…" sono due denotazioni della stessa quantità, e il 2 può essere un carattere ASCII (8 bit), un intero in complemento a 2 o un floating point a 32 o 64 bit; in C `a == x` con `int a = 2` e `float x = 2.0` è vero, perché interessa la quantità e non il formato. Per il docente il numero naturale 2 è la classe di equivalenza di tutti gli insiemi con due elementi.
>
> Lo stesso discorso vale per le rappresentazioni **vettoriali** dei modelli neurali: l'encoder che trasforma un'immagine in un vettore produce una denotazione dell'oggetto, e si vorrebbe una legge matematica che, agendo sul vettore, permetta di verificare proprietà logiche come $\mathit{Block}(a)$ o "c'è un gatto nell'immagine". L'approccio **simbolico** all'IA ragiona su simboli discreti; quello **neurale** su rappresentazioni nel continuo. In entrambi i casi bisogna **modellare** il problema prima di costruire il sistema.

> [!info] Concettualizzazione del mondo dei blocchi (slide pp. 4-5)
> Si guardano i blocchi e alcune loro relazioni spaziali, con la pila $a$ su $b$ su $c$ e la pila $d$ su $e$. La concettualizzazione è la terna $\langle D, F, R\rangle$:
> - dominio $D=\{a,b,c,d,e\}$ (i blocchi veri);
> - funzioni $F=\{\mathit{Hat}/1\}$, con $\mathit{Hat}(b)=a$;
> - relazioni $\mathit{On}/2=\{\langle a,b\rangle,\langle b,c\rangle,\langle d,e\rangle\}$, $\mathit{Clear}/1=\{a,d\}$, $\mathit{Table}/1=\{c,e\}$, $\mathit{Block}/1=\{a,b,c,d,e\}$.
>
> Le concettualizzazioni possibili sono infinite: conta il **livello di astrazione** giusto per gli scopi della rappresentazione. Se fossero rilevanti il colore o la grandezza dei blocchi, servirebbero predicati anche per questi aspetti.
### Sintassi
Per convenzione nelle slide le **costanti** sono maiuscole e le **variabili** minuscole. Il docente consiglia nomi leggibili (`Mario`, `Pippo`) invece di lettere singole. Funzioni e predicati hanno un'**arità**: $\mathit{PadreDi}$ ha arità 1, $+$ e $-$ arità 2; $\mathit{On}$ è binario, $\mathit{Clear}$ unario, $\geq$ binario. In Prolog la tipica funzione è quella valutata da `is`.

> [!info] Il vocabolario nelle slide (p. 6)
> - **connettivi**: $\land$, $\lor$, $\lnot$, $\Rightarrow$, $\Leftrightarrow$, $\Leftarrow$;
> - **quantificatori**: $\forall$, $\exists$;
> - **variabili**: $x,y,\dots,a,s,\dots$ (lettere minuscole);
> - **costanti**: ad esempio $A$, $B$, $\mathit{Mario}$, $\mathit{Pippo}$, $2$;
> - **funzioni** con arità $\geq 1$: $\mathit{Hat}$, $\mathit{PadreDi}$, $+$, $-$;
> - **predicati** con arità $\geq 0$: $\mathit{On}$, $\mathit{Clear}$, $\geq$, $<$.

I **termini** denotano oggetti e si definiscono ricorsivamente (slide p. 7):
- ogni costante è un termine;
- ogni variabile è un termine (nel primo ordine le variabili stanno solo per **oggetti**, non per funzioni o predicati);
- se $f$ ha arità $n$ e $t_1,\dots,t_n$ sono termini, $f(t_1,\dots,t_n)$ è un termine. Ad esempio $+(2,3)$ in notazione prefissa, o $\mathit{PadreDi}(\mathit{Giovanni})$.

La slide dà come termini ben formati $f(x,y)$, $+(2,3)$, $\mathit{Padre\text{-}di}(\mathit{Giovanni})$, $x$, $A$, $B$, $2$, $\mathit{Prezzo}(\mathit{Banane})$, $\mathit{Hat}(A)$.

I termini **non** sono formule: non ha senso chiedere se Giovanni è vero o falso (esistere è diverso da essere vero). Le **formule** sono ciò che è vero o falso (slide pp. 8-9):
- **atomiche**: $\mathit{True}$ e $\mathit{False}$ (vere in tutti i modelli o in nessuno); l'**uguaglianza** tra termini, come $\mathit{Renato}=\mathit{FratelloDi}(\mathit{Roberto})$, vera se le due denotazioni indicano lo stesso individuo; un predicato applicato a un numero di termini pari alla sua arità, come $\geq(2,1)$ o $\mathit{Ama}(\mathit{Giorgio},\mathit{Lucia})$. Esempi della slide: $\mathit{On}(A,B)$, $+(2,3)=5$, $x=5$, $\mathit{Madre\text{-}di}(\mathit{Luigi})=\mathit{Silvana}$, $\mathit{Amico}(\mathit{Padre\text{-}di}(\mathit{Giorgio}),\mathit{Padre\text{-}di}(\mathit{Elena}))$;
- **complesse**: negazione, congiunzione, disgiunzione, implicazione e doppia implicazione di formule, come nel calcolo proposizionale, la formula tra parentesi e la **quantificazione** $\forall x\,\varphi$ o $\exists x\,\varphi$ di una formula. Esempi della slide: $\mathit{On}(A,B)\land\mathit{On}(B,C)$ (congiunzione), $\mathit{Studia}(\mathit{Paolo})\Rightarrow\mathit{Promosso}(\mathit{Paolo})$ (implicazione materiale).

> [!info] Uguaglianza e assegnazione
> Uno studente chiede se $+(2,3)=6$ sia un'assegnazione o un confronto. È una formula, e con l'interpretazione usuale dei numeri è **falsa**: il simbolo $=$ è un simbolo logico, come un connettivo, non un'istruzione. Sarebbe vera solo in un'interpretazione bizzarra in cui, ad esempio, 2 denota 1 e 3 denota 5. Il linguaggio è **dichiarativo**: non si cerca né si assegna, si afferma.

**Precedenza** (slide p. 12), dalla più alta: $=$, $\lnot$, $\land$, $\lor$, $\Rightarrow$ e $\Leftrightarrow$ (allo stesso livello), per ultimi i quantificatori $\forall,\exists$. La slide legge $\forall x\ \mathit{Persona}(x)\Rightarrow\mathit{Sesso}(x)=M\lor\mathit{Sesso}(x)=F$ come $\forall x\,\big(\mathit{Persona}(x)\Rightarrow((\mathit{Sesso}(x)=M)\lor(\mathit{Sesso}(x)=F))\big)$.
### Quantificatori, variabili libere e legate
- $\forall x\,\varphi$ è vera se $\varphi$ è vera per **ogni** interpretazione di $x$ nel dominio. Si usa tipicamente con l'**implicazione**, per restringere il dominio: $\forall x\ \mathit{Persona}(x)\Rightarrow\mathit{AmaGelato}(x)$, perché per amare il gelato bisogna almeno poter amare (scrivere $\forall x\ \mathit{AmaGelato}(x)$ lo direbbe anche dei gelati stessi). Nelle slide (p. 10) l'esempio è $\forall x\ \mathit{Ama}(x,\mathit{Gelato})$.
- $\exists x\,\varphi$ è vera se esiste **almeno un** individuo che, sostituito a $x$, rende vera $\varphi$. Si usa tipicamente con la **congiunzione**, per elencare le proprietà di un individuo: $\exists x\ \mathit{Mela}(x)\land\mathit{Rossa}(x)$.
- Tra i due quantificatori vale la dualità di **De Morgan**: $\forall x\,\lnot P(x)\equiv\lnot\exists x\,P(x)$ e $\lnot\forall x\,P(x)\equiv\exists x\,\lnot P(x)$. La slide (p. 20) la scrive in quattro forme, aggiungendo $\forall x\,P(x)\equiv\lnot\exists x\,\lnot P(x)$ e $\exists x\,P(x)\equiv\lnot\forall x\,\lnot P(x)$, accanto alle leggi per i connettivi $\lnot P\land\lnot Q\equiv\lnot(P\lor Q)$, $\lnot(P\land Q)\equiv\lnot P\lor\lnot Q$, $P\land Q\equiv\lnot(\lnot P\lor\lnot Q)$, $P\lor Q\equiv\lnot(\lnot P\land\lnot Q)$: $\forall$ si comporta come una grande congiunzione e $\exists$ come una grande disgiunzione.

> [!example] L'ordine dei quantificatori
> "Tutti amano qualcuno" in italiano ha due letture (slide p. 10):
> - $\forall x\,\exists y\ \mathit{Ama}(x,y)$: ognuno ha qualcuno che ama, e la $y$ può cambiare con la $x$;
> - $\exists y\,\forall x\ \mathit{Ama}(x,y)$: c'è un individuo particolare amato da tutti.

L'**ambito** (*scope*) di un quantificatore è la formula su cui agisce, come lo scope di una variabile in un linguaggio di programmazione: in $\forall x\,(\exists y\ \mathit{Ama}(x,y))$ l'ambito di $x$ è tutta la formula tra parentesi e quello di $y$ è $\mathit{Ama}(x,y)$.
- Un'occorrenza di variabile è **legata** se cade nell'ambito di un quantificatore su quella variabile, **libera** altrimenti (slide p. 11).
- In $\mathit{Mela}(x)\Rightarrow\exists x\,\mathit{Rossa}(x)$ le due $x$ sono variabili diverse (la prima libera, la seconda legata): la formula andrebbe riscritta $\mathit{Mela}(x)\Rightarrow\exists y\,\mathit{Rossa}(y)$. La slide confronta tre formule: in $\mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ la $x$ è libera in entrambe le occorrenze, in $\forall x\ \mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ è legata, in $\mathit{Mela}(x)\Rightarrow\exists x\,\mathit{Rossa}(x)$ la prima è libera e la seconda legata.
- Una formula è **chiusa** se non ha occorrenze libere, **aperta** altrimenti.
- Una formula senza variabili è **ground**, come $\mathit{Pari}(A)$: ha lo stesso potere espressivo di una proposizione, è vera o falsa a seconda solo delle costanti, ma conserva una struttura interna (un predicato applicato a individui). $\geq(x,3)$ è aperta; $\geq(1,3)$ è ground e falsa, $\geq(10,3)$ è ground e vera.

Essere libera, chiusa o ground è una proprietà **sintattica**: una formula aperta non è né valida né insoddisfacibile di per sé, e può non essere soddisfatta da nessun individuo (se nel mondo non ci sono mele rosse).

> [!info] Perché "primo ordine" (slide p. 21)
> Nel primo ordine le variabili denotano **oggetti** del dominio, non funzioni, predicati o formule. Funzioni e predicati possono essere oggetti del dominio, ma allora non si possono usare al posto dei nomi di funzioni o predicati. Non si può scrivere $\exists f\,\forall x\ f(x)=x$ ("esiste la funzione identità"), mentre si può scrivere $\exists f\ \mathit{FunzioneIdentità}(f)$; si può scrivere $\forall p\ \mathit{BuonaQualità}(p)\Rightarrow\mathit{Ha}(\mathit{Giorgio},p)$ ma non $\forall p\ \mathit{BuonaQualità}(p)\Rightarrow p(\mathit{Giorgio})$. Il superamento di questa restrizione porta ai linguaggi del **second'ordine**, o di ordine superiore, fuori dal corso. A lezione si è aggiunto che anche per predicare su tutti i mondi possibili insieme servono logiche più ricche, le logiche modali.
### Semantica
Una formula è vera o falsa a seconda di **com'è fatto il mondo**: se nel mondo non ci sono mele rosse, $\exists x\ \mathit{Mela}(x)\land\mathit{Rossa}(x)$ è falsa; se ci sono anche mele verdi, $\forall x\ \mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ è falsa. Per sapere se una formula è vera nel mondo bisogna saperla **interpretare**. La semantica (slide p. 13) è una corrispondenza tra i termini del linguaggio e gli oggetti del mondo, e tra le formule chiuse e i valori di verità. Un'interpretazione $I$ assegna (slide p. 14):
- a ogni **costante** $c$ un oggetto $I(c)$ del dominio, specifico e univoco (se due persone parlano di "Mario" senza accordarsi su chi sia, non si capiscono);
- a ogni **funzione** di arità $n$ una funzione dalle $n$-uple di oggetti del dominio a oggetti del dominio, $f:D^n\to D$ ($\mathit{PadreDi}$ punta all'unico padre);
- a ogni **predicato** di arità $n$ un **insieme** di $n$-uple, $P\subseteq D^n$, quelle che lo rendono vero, come le righe di una tabella relazionale. Equivalentemente $P:D^n\to\{\mathit{Vero},\mathit{Falso}\}$, e $P(o_1,\dots,o_n)$ è vero se la $n$-upla appartiene all'insieme.

> [!example] Due interpretazioni del mondo dei blocchi (slide p. 15)
> Fatti $\mathit{On}(A,B)$, $\mathit{Clear}(A)$, $\mathit{Table}(B)$, con $a$ sopra $b$. Nell'interpretazione intesa $I$ la costante $A$ denota il blocco $a$, $B$ il blocco $b$, $I(\mathit{On})=\{\langle a,b\rangle\}\subseteq D^2$, $I(\mathit{Clear})=\{a\}$, $I(\mathit{Table})=\{b\}$. In un'interpretazione $I'$ con le stesse costanti ma $I'(\mathit{On})=\{\langle b,a\rangle\}$, $I'(\mathit{Clear})=\{b\}$, $I'(\mathit{Table})=\{a\}$ (a lezione: $\mathit{On}$ letto come "sotto"), la formula $\mathit{On}(B,A)$ è **falsa** in $I$ e **vera** in $I'$. Senza un'interpretazione non si può stabilire la verità: fuori dalla matematica le concettualizzazioni sono opinabili (come i diagrammi ER in cui ognuno sceglie i suoi gradi di libertà), e vanno esplicitate. Vale anche per i prompt: chi scrive male il proprio modello concettuale e poi accusa l'LLM di "allucinare" ha fatto la domanda sbagliata.

La semantica è **composizionale** (slide pp. 16-17): il significato di un termine o di una formula composta è una funzione del significato dei suoi componenti. Il significato di $\mathit{Sorella}(\mathit{Madre}(\mathit{Pietro}))$ si ottiene interpretando la costante $\mathit{Pietro}$ (una persona), poi applicando l'interpretazione di $\mathit{Madre}$ (nella figura della slide, Maria) e infine quella di $\mathit{Sorella}$ (Sofia). Lo stesso calcolo, nei modelli neurali, diventa una composizione di trasformazioni di **vettori**, cioè di matrici. Per le formule composte (slide p. 17):
- $A\land B$ è vera in una certa interpretazione se $A$ e $B$ sono entrambe vere;
- $\lnot A$ è vera se $A$ è falsa;
- $A\lor B$ è vera se $A$ è vera oppure $B$ è vera (o entrambe);
- $A\Rightarrow B$ è vera se $A$ è falsa oppure $B$ è vera (come $\lnot A\lor B$).

- $\forall x\,\varphi$ è vera se $\varphi$ è vera per ciascun elemento del dominio associato a $x$ (slide p. 18). Se il dominio è finito equivale a una congiunzione tra tutti gli elementi: $\forall x\ \mathit{Mortale}(x)$ equivale a $\mathit{Mortale}(\mathit{Gino})\land\mathit{Mortale}(\mathit{Pippo})\land\dots$. Siccome difficilmente una proprietà è universale, si usa quasi sempre con $\Rightarrow$: $\forall x\ \mathit{Persona}(x)\Rightarrow\mathit{Mortale}(x)$. A lezione: $\forall x\ \mathit{Block}(x)$ nel mondo dei blocchi è vera, ma diventa falsa aggiungendo il tavolo al dominio.
- $\exists x\,\varphi$ è vera se almeno un individuo del dominio soddisfa $\varphi$ (slide p. 19). Se il dominio è finito equivale a una grossa disgiunzione, $\mathit{Persona}(\mathit{Gino})\lor\mathit{Persona}(\mathit{Pippo})\lor\dots$. Si usa tipicamente con $\land$: $\exists x\ \mathit{Persona}(x)\land\mathit{Speciale}(x)$, mentre $\exists x\ \mathit{Persona}(x)\Rightarrow\mathit{Speciale}(x)$ è **troppo debole** (basta un $x$ che non sia una persona). A lezione: $\exists x\ \mathit{Persona}(x)$ nel mondo dei blocchi è falsa.
#### Nomi unici e mondo chiuso
> [!example] I fratelli di Riccardo (slide p. 22)
> "Riccardo ha due fratelli, Giovanni e Goffredo": $\mathit{Fratello}(\mathit{Riccardo},\mathit{Giovanni})\land\mathit{Fratello}(\mathit{Riccardo},\mathit{Goffredo})$ non basta. In logica bisogna aggiungere che $\mathit{Giovanni}\neq\mathit{Goffredo}$ (due costanti possono denotare lo stesso individuo, come "il Pupone" e "Francesco Totti") e che non ce ne sono altri:
> $$\forall x\ \mathit{Fratello}(\mathit{Riccardo},x)\Rightarrow(x=\mathit{Giovanni})\lor(x=\mathit{Goffredo})$$

Di solito non lo si scrive perché si adotta la **semantica delle basi di dati** (slide p. 22), con tre ipotesi:
- **nomi unici**: simboli distinti, oggetti distinti;
- **mondo chiuso**: tutto ciò di cui non si sa che è vero è falso ([[04 - Agenti basati sulla conoscenza#Differenza con le basi di dati|già visto]]);
- **chiusura del dominio**: esistono solo gli oggetti di cui si parla.

Una base di dati è in fondo un insieme di formule ground, gestibile in modo molto efficiente; la semantica logica piena è più onerosa, sia nel numero di formule sia nelle dimostrazioni. Nel corso si userà una semantica **intermedia**, quella delle basi di dati dove è possibile.
### La logica in un agente: TELL, ASK e sostituzioni
Un agente usa la FOL con le operazioni di [[04 - Agenti basati sulla conoscenza#L'agente basato sulla conoscenza|TELL e ASK]] (slide p. 23):
- asserisce **fatti**, da percezioni o conoscenza: $\mathit{TELL}(KB,\mathit{King}(\mathit{John}))$;
- asserisce **regole**: $\mathit{TELL}(KB,\forall x\ \mathit{King}(x)\Rightarrow\mathit{Person}(x))$ (non siamo in un film Disney, i re sono persone);
- interroga: $\mathit{ASK}(KB,\mathit{Person}(\mathit{John}))$ risponde sì se $KB\models\mathit{Person}(\mathit{John})$, qui con un passo di modus ponens;
- più interessante, interroga con variabili: $\mathit{ASK}(KB,\exists x\ \mathit{Person}(x))$, cioè "quali persone conosci?". Rispondere solo "sì" sarebbe riduttivo: una risposta più collaborativa è una lista di **sostituzioni** (o *binding*), come $[\{x/\mathit{John}\},\{x/\mathit{George}\},\dots]$, che legano la variabile della query a una costante. Se la costante è interpretata come un certo individuo, rispondere con la costante significa, nella mente dell'utente, indicare quell'individuo: il sistema lavora sui simboli (i record in memoria), e attraverso l'interpretazione parla del mondo.
### Inferenza
Le slide (p. 24) elencano gli approcci all'inferenza nel primo ordine: la riduzione a inferenza proposizionale; il metodo di risoluzione (trasformazione in forma a clausole e unificazione); i casi particolari dei sistemi a regole, cioè il *backward chaining* con la programmazione logica e il *forward chaining* con le basi di dati deduttive. Le ultime due voci sono solo nominate: le slide non le sviluppano.

**Proposizionalizzazione.** Si sostituiscono le variabili con tutte le costanti possibili, ottenendo una base di conoscenza di sole formule ground, cioè proposizionale, a cui si applicano gli algoritmi del calcolo proposizionale. Con 5 blocchi e pochi predicati diventano una sessantina di proposizioni, gestibili. Ma basta **una funzione** per rendere il dominio infinito: da una costante $R$ (Roberto) si generano $\mathit{PadreDi}(R)$, $\mathit{PadreDi}(\mathit{PadreDi}(R))$, … e la versione proposizionale ha **infinite** proposizioni (le slide, p. 27, usano $\mathit{John}$, $\mathit{Padre}(\mathit{John})$, ...). Serve un metodo che eviti di enumerare tutte le istanze.
#### Regole di istanziazione e skolemizzazione
> [!warning] Dalle slide, non nella registrazione del 09/11
> Questa parte (slide pp. 25-28) non compare nella registrazione della lezione del 09/11/2026.

Per ridurre la base alla logica proposizionale servono due regole (slide pp. 25-26):
- **Istanziazione dell'universale** ($\forall$-eliminazione): da $\forall x\,A[x]$ si ottiene $A[g]$, dove $g$ è un termine **ground** e $A[g]$ è il risultato della sostituzione di $g$ a $x$ in $A$. Da $\forall x\ \mathit{King}(x)\land\mathit{Greedy}(x)\Rightarrow\mathit{Evil}(x)$ si ottengono $\mathit{King}(\mathit{John})\land\mathit{Greedy}(\mathit{John})\Rightarrow\mathit{Evil}(\mathit{John})$ e $\mathit{King}(\mathit{Father}(\mathit{John}))\land\mathit{Greedy}(\mathit{Father}(\mathit{John}))\Rightarrow\mathit{Evil}(\mathit{Father}(\mathit{John}))$.
- **Istanziazione dell'esistenziale** ($\exists$-eliminazione): da $\exists x\,A[x]$ si ottiene $A[k]$, in due casi:
  1. se $\exists$ non compare nell'ambito di un $\forall$, $k$ è una **costante nuova** (*costante di Skolem*): $\exists x\ \mathit{Padre}(x,G)$ diventa $\mathit{Padre}(k,G)$;
  2. altrimenti va introdotta una **funzione di Skolem** nelle variabili quantificate universalmente: $\forall x\,\exists y\ \mathit{Padre}(y,x)$ diventa $\forall x\ \mathit{Padre}(p(x),x)$ e **non** $\forall x\ \mathit{Padre}(k,x)$, altrimenti tutti avrebbero lo stesso padre.

La **proposizionalizzazione** (slide p. 27) consiste nel creare tante istanze delle formule quantificate universalmente quanti sono gli oggetti menzionati, ed eliminare gli esistenziali skolemizzando; poi la base si tratta come proposizionale.
#### Teorema di Herbrand
Secondo la slide (p. 28): se $KB\models A$ allora c'è una dimostrazione che coinvolge solo un sottoinsieme **finito** della base proposizionalizzata. Si procede in modo incrementale: prima le istanze con le sole costanti, poi quelle con un livello di annidamento ($\mathit{Padre}(\mathit{John})$, $\mathit{Madre}(\mathit{John})$), poi due livelli ($\mathit{Padre}(\mathit{Padre}(\mathit{John}))$, $\mathit{Padre}(\mathit{Madre}(\mathit{John}))$) e così via. Se $KB\not\models A$ il processo non termina: il problema è quindi **semidecidibile** (come già anticipato a proposito del [[04 - Agenti basati sulla conoscenza#Due linguaggi|calcolo della conseguenza nel primo ordine]]).
#### Verso la risoluzione nel primo ordine
**Risoluzione** (ripresa dalla [[04 - Agenti basati sulla conoscenza#Deduzione e risoluzione|lezione 9]]). Nel caso proposizionale si mette la base in **forma normale congiuntiva** (CNF), si aggiunge la negazione della formula $\alpha$ da dimostrare e si applica la risoluzione: da $\lnot P\lor M$ e $P$ si ottiene $M$ (un passo di modus ponens); se poi c'è $\lnot M$, la risoluzione dà la **clausola vuota**, cioè un'inconsistenza. È la dimostrazione **per assurdo**: se $KB\land\lnot\alpha$ non ha modelli, allora $KB\models\alpha$. Il metodo è completo per il calcolo proposizionale.

Nel primo ordine due letterali complementari possono avere **argomenti diversi**, come $P(x,A)$ e $\lnot P(B,z)$ (esempio nostro: a lezione la forma alla lavagna non si ricava con certezza). Perché si possano risolvere:
- devono essere lo **stesso predicato** con lo stesso numero di argomenti, uno positivo e uno negato;
- bisogna trovare una **sostituzione** che renda uguali gli argomenti, la più generale possibile (l'unificatore più generale, definito sotto): qui $\{x/B,\ z/A\}$, che porta entrambi a $P(B,A)$. Significa restringersi ai mondi in cui le variabili denotano quegli individui;
- la sostituzione si applica a **tutte** le occorrenze delle variabili nelle due clausole, e la risolvente è l'unione di ciò che resta.

È l'**unificazione**, trattata nelle sezioni successive. Con questo meccanismo la dimostrazione o arriva alla clausola vuota (e la risposta è sì) o si ferma prima (nel primo ordine può anche non terminare, vedi Herbrand), e come effetto collaterale produce le **sostituzioni** che rispondono alle query esistenziali ("esiste una $y$ che soddisfa $\mathit{Person}$?", con $y$ legata a $\mathit{John}$). È l'algoritmo che sta dietro a **Prolog**, molto efficiente.
### Forma a clausole
> [!warning] Ricostruita dalle sole slide
> Questa parte e le tre sezioni seguenti (unificazione, risoluzione nel primo ordine, riepilogo) corrispondono alle lezioni successive al 09/11/2026 (quella del 13/11 è «Risoluzione nella FOL», dal post del professore su Teams), di cui non c'è registrazione: sono ricostruite dalle sole slide, pp. 29-64. Ciò che va oltre le slide è dichiarato nel testo.

Per estendere al primo ordine la risoluzione, metodo deduttivo corretto e completo con un'unica regola, servono due cose: la trasformazione in forma a clausole e l'unificazione (slide p. 29).

Nella forma a clausole (slide p. 30) costanti, funzioni e predicati sono come già definiti, ma si escludono le formule atomiche del tipo $t_1=t_2$.
- Una **clausola** è un insieme di **letterali** che ne rappresenta la disgiunzione: $\{L_1,\dots,L_n\}$.
- Un **letterale** è una formula atomica o la sua negazione.
- Una base di conoscenza è un **insieme di clausole**.

#### Trasformazione in forma a clausole
**Teorema** (slide p. 31): per ogni formula chiusa $\alpha$ del FOL si può trovare in modo effettivo un insieme di clausole $FC(\alpha)$ che è soddisfacibile se e solo se $\alpha$ lo era (e insoddisfacibile se e solo se $\alpha$ lo era). Le slide (pp. 31-39) seguono la trasformazione sulla frase «Tutti coloro che amano tutti gli animali sono amati da qualcuno»:
$$\forall x\,\big(\forall y\ \mathit{Animale}(y)\Rightarrow\mathit{Ama}(x,y)\big)\Rightarrow\big(\exists y\ \mathit{Ama}(y,x)\big)$$

1. **Eliminazione delle implicazioni**: $A\Rightarrow B$ diventa $\lnot A\lor B$ e $A\Leftrightarrow B$ diventa $(\lnot A\lor B)\land(\lnot B\lor A)$.
   $$\forall x\ \lnot\big(\forall y\ \lnot\mathit{Animale}(y)\lor\mathit{Ama}(x,y)\big)\lor\big(\exists y\ \mathit{Ama}(y,x)\big)$$
2. **Negazioni all'interno**: $\lnot\lnot A$ diventa $A$, $\lnot(A\land B)$ diventa $\lnot A\lor\lnot B$ e $\lnot(A\lor B)$ diventa $\lnot A\land\lnot B$ (De Morgan), $\lnot\forall x\,A$ diventa $\exists x\,\lnot A$ e $\lnot\exists x\,A$ diventa $\forall x\,\lnot A$.
   $$\forall x\ \big(\exists y\ \mathit{Animale}(y)\land\lnot\mathit{Ama}(x,y)\big)\lor\big(\exists y\ \mathit{Ama}(y,x)\big)$$
3. **Standardizzazione delle variabili**: ogni quantificatore usa una variabile diversa.
   $$\forall x\ \big(\exists y\ \mathit{Animale}(y)\land\lnot\mathit{Ama}(x,y)\big)\lor\big(\exists z\ \mathit{Ama}(z,x)\big)$$
4. **Skolemizzazione**: eliminazione dei quantificatori esistenziali. Ci sono due esistenziali nell'ambito di un universale, quindi servono due funzioni di Skolem $F$ e $G$ di $x$.
   $$\forall x\ \big(\mathit{Animale}(F(x))\land\lnot\mathit{Ama}(x,F(x))\big)\lor\mathit{Ama}(G(x),x)$$
5. **Eliminazione dei quantificatori universali**: si portano tutti davanti (forma **prenessa**), con $(\forall x\,A)\lor B$ che diventa $\forall x\,(A\lor B)$ e $(\forall x\,A)\land B$ che diventa $\forall x\,(A\land B)$ (equivalenti se $B$ non contiene $x$); poi si eliminano, con la convenzione che le variabili libere sono quantificate universalmente.
   $$\big(\mathit{Animale}(F(x))\land\lnot\mathit{Ama}(x,F(x))\big)\lor\mathit{Ama}(G(x),x)$$
6. **Forma normale congiuntiva** (congiunzione di disgiunzioni di letterali): $A\lor(B\land C)$ diventa $(A\lor B)\land(A\lor C)$.
   $$\big(\mathit{Animale}(F(x))\lor\mathit{Ama}(G(x),x)\big)\land\big(\lnot\mathit{Ama}(x,F(x))\lor\mathit{Ama}(G(x),x)\big)$$
7. **Notazione a clausole**:
   $$\{\mathit{Animale}(F(x)),\ \mathit{Ama}(G(x),x)\}\qquad\{\lnot\mathit{Ama}(x,F(x)),\ \mathit{Ama}(G(x),x)\}$$
8. **Separazione delle variabili**: clausole diverse, variabili diverse, perché $\forall x\,(P(x)\land Q(x))\Leftrightarrow\forall x_1\,P(x_1)\land\forall x_2\,Q(x_2)$.
   $$\{\mathit{Animale}(F(x_1)),\ \mathit{Ama}(G(x_1),x_1)\}\qquad\{\lnot\mathit{Ama}(x_2,F(x_2)),\ \mathit{Ama}(G(x_2),x_2)\}$$

Tutti i passi tranne la skolemizzazione **preservano l'equivalenza** delle formule; la skolemizzazione preserva solo la soddisfacibilità: $P(a)\models\exists x\,P(x)$ ma $\exists x\,P(x)\not\models P(a)$ (slide p. 39).
#### Forma normale implicativa e clausole di Horn
La slide (p. 40) presenta la **forma normale implicativa**, "forse più intuitiva": una clausola
$$\lnot P_1\lor\dots\lor\lnot P_k\lor Q_1\lor\dots\lor Q_n\ \equiv\ \lnot(P_1\land\dots\land P_k)\lor Q_1\lor\dots\lor Q_n\ \equiv\ P_1\land\dots\land P_k\Rightarrow Q_1\lor\dots\lor Q_n$$
Il caso particolare con **un solo letterale positivo** sono le **clausole di Horn**, $P_1\land\dots\land P_k\Rightarrow Q$: la **forma a regole** della programmazione logica e delle basi di dati deduttive. La slide non dice altro sulle clausole di Horn.
### Unificazione
> [!warning] Ricostruita dalle sole slide
> Slide pp. 41-52, senza registrazione (vedi il callout di «Forma a clausole»).

L'**unificazione** (slide p. 41) è l'operazione con cui si determina se due espressioni possono essere rese identiche mediante una sostituzione di termini alle variabili. Il risultato è la sostituzione che le rende identiche, detta **unificatore**, oppure $\mathit{FAIL}$ se non sono unificabili.
#### Sostituzioni
Una **sostituzione** è un insieme finito di associazioni tra variabili e termini, in cui ogni variabile compare una sola volta a sinistra, e a sinistra ci sono solo variabili (slide p. 42). Ad esempio $\{x_1/A,\ x_2/f(x_3),\ x_3/B\}$: $A$ va sostituita a $x_1$, $f(x_3)$ a $x_2$; o ancora $\{x/g(y),\ y/z,\ z/f(x)\}$.

Se $\sigma$ è una sostituzione e $A$ un'espressione, $A\sigma$ è l'**istanza** generata dalla sostituzione (slide p. 43). Le variabili sono sostituite **simultaneamente**, in un solo passo:
- $P(x,x,y,v)\{x/A,\ y/f(B),\ z/w\}=P(A,A,f(B),v)$;
- $Q(x,y,z)\{x/g(y),\ y/z,\ z/f(x)\}=Q(g(y),z,f(x))$.

> [!info] Notazione delle slide
> Le slide usano $\{x/A\}$ (variabile/termine) alle pp. 42-44 e nel resto della risoluzione, ma $[t/x]$ (termine/variabile) alle pp. 45-46 (composizione e MGU). Qui si usa sempre variabile/termine; l'esempio di p. 46 è tradotto di conseguenza.

Due espressioni sono **unificabili** se esiste una sostituzione che le rende identiche (slide p. 44). $P(A,y,z)$ e $P(x,B,z)$ sono unificabili con $\tau=\{x/A,\ y/B,\ z/C\}$, perché $P(A,y,z)\tau=P(x,B,z)\tau=P(A,B,C)$, ma $\tau$ non è l'unico unificatore: un altro è $\sigma=\{x/A,\ y/B\}$, e $\sigma$ è **più generale** di $\tau$ (istanzia "meno"). Si vorrebbe l'unificatore più generale di tutti, l'**MGU**; **teorema**: è unico, a parte i nomi delle variabili.

La **composizione** $\sigma\tau$ di due sostituzioni (slide p. 45), con $\sigma=\{x_1/t_1,\dots,x_k/t_k\}$ e $\tau=\{y_1/s_1,\dots,y_n/s_n\}$:
1. si costruisce $\sigma\tau'=\{x_1/t_1\tau,\dots,x_k/t_k\tau,\ y_1/s_1,\dots,y_n/s_n\}$;
2. si eliminano da $\sigma\tau'$ le identità (come $y/y$) e le coppie $y_i/s_i$ con $y_i\in\{x_1,\dots,x_k\}$, ottenendo $\sigma\tau$.

Esempio della slide: $\sigma=\{w/g(x,y),\ y/x\}$, $\tau=\{x/y,\ w/B,\ z/C\}$. Primo passo: $\sigma\tau'=\{w/g(y,y),\ y/y,\ x/y,\ w/B,\ z/C\}$; secondo passo: $\sigma\tau=\{w/g(y,y),\ x/y,\ z/C\}$.
#### Unificatore più generale
L'**MGU** $\gamma$ (slide p. 46) è tale che ogni altro unificatore $\sigma$ si ottiene componendo $\gamma$ con qualche sostituzione: $\forall\sigma\ \exists\delta\ \gamma\delta=\sigma$. Esempio: l'MGU di $P(A,y,z)$ e $P(x,y,v)$ è, nella notazione delle slide, $[A/x,\ z/v]$, cioè $x$ sostituita da $A$ e $v$ da $z$ (nella notazione di queste note $\{x/A,\ v/z\}$); un altro unificatore, $[A/x,\ B/y,\ z/v]$, è la composizione $[A/x,\ z/v][B/y]$.
#### Algoritmo di unificazione
L'algoritmo (slide p. 47) lavora su equazioni $s=_U t$ tra termini, con sei regole:
1. **Caso base +**: $f(s_1,\dots,s_n)=_U f(t_1,\dots,t_n)$ diventa $s_1=_U t_1,\dots,s_n=_U t_n$;
2. **Caso base −**: $f(s_1,\dots,s_n)=_U g(t_1,\dots,t_m)$ dà $\mathit{fail}$ se $f\neq g$ o $n\neq m$ (con $n=m=0$ si fallisce su due costanti diverse);
3. **Skip rule**: $x=_U x$ si cancella;
4. $t=_U x$ diventa $x=_U t$;
5. $x=_U t$, con $x$ che non occorre in $t$: si applica $\{x/t\}$ a tutte le altre equazioni;
6. **Occur check**: $x=_U t$, con $t$ diverso da $x$ ma con $x$ che occorre in $t$: $\mathit{fail}$.

Lo stesso procedimento come pseudocodice (scritto da noi dalle sei regole della slide; le condizioni sulle regole 4 e 5 servono a garantire la terminazione e non sono nella slide):

```pseudo
\begin{algorithm}
\caption{Unify($s$, $t$)}
\begin{algorithmic}
\State $E \gets \{ s =_U t \}$
\While{a un'equazione di $E$ si può applicare una regola}
  \State scegli un'equazione $e$ di $E$ a cui si applica una regola
  \If{$e$ è $f(s_1,\dots,s_n) =_U f(t_1,\dots,t_n)$}
    \State sostituisci $e$ con $s_1 =_U t_1, \dots, s_n =_U t_n$ \Comment{regola 1}
  \ElsIf{$e$ è $f(s_1,\dots,s_n) =_U g(t_1,\dots,t_m)$ con $f \neq g$ o $n \neq m$}
    \State \Return $\mathit{FAIL}$ \Comment{regola 2}
  \ElsIf{$e$ è $x =_U x$}
    \State cancella $e$ \Comment{regola 3}
  \ElsIf{$e$ è $t =_U x$ con $t$ non variabile}
    \State sostituisci $e$ con $x =_U t$ \Comment{regola 4}
  \ElsIf{$e$ è $x =_U t$ e $x$ occorre in $t$, con $t \neq x$}
    \State \Return $\mathit{FAIL}$ \Comment{regola 6, occur check}
  \ElsIf{$e$ è $x =_U t$, $x$ non occorre in $t$ e $x$ compare nelle altre equazioni}
    \State applica $\{x/t\}$ alle altre equazioni di $E$ \Comment{regola 5}
  \EndIf
\EndWhile
\State \Return la sostituzione formata dalle equazioni $x =_U t$ rimaste in $E$
\end{algorithmic}
\end{algorithm}
```

> [!example] Esempio 1: MGU di $P(A,y,z)$ e $P(x,B,z)$ (slide pp. 48-51)
> - Passo 0: $P(A,y,z)=_U P(x,B,z)$, regola 1.
> - Passo 1: $A=_U x$, $y=_U B$, $z=_U z$.
> - Passo 2: $x=_U A$ (regola 4), $y=_U B$, e $z=_U z$ si cancella (regola 3).
> - Passo 3: resta $x=_U A$, $y=_U B$, cioè l'**MGU** $\{x/A,\ y/B\}$.

> [!example] Esempio 2: MGU di $P(f(x),x)$ e $P(z,z)$ (slide p. 52)
> Con la regola 1 si ottengono $f(x)=_U z$ e $x=_U z$; con la regola 4 $z=_U f(x)$; applicando $\{z/f(x)\}$ all'altra equazione (regola 5) si arriva a $x=_U f(x)$, dove $x$ occorre in $f(x)$: per la regola 6 l'unificazione fallisce (**occur check**). Nella slide si vede solo l'ultimo passo, $x=_U f(x)$ con regola 6 e $\mathit{FAIL}$; i passaggi intermedi sono ricostruiti da noi dalle regole.
### Risoluzione nel primo ordine
> [!warning] Ricostruita dalle sole slide
> Slide pp. 53-62, senza registrazione (vedi il callout di «Forma a clausole»).
#### La regola di risoluzione
Date due clausole $\Phi=\{\dots A\dots\}$ e $\Psi=\{\dots\lnot B\dots\}$ con variabili diverse e $\gamma=\mathit{MGU}(A,B)$, il **risolvente** è (slide p. 53)
$$\big((\Phi\setminus\{A\})\cup(\Psi\setminus\{\lnot B\})\big)\gamma$$
dove $\setminus$ è la differenza di insiemi.

> [!example] Esempio di risoluzione (slide p. 54)
> Sulle clausole $\{P(x,x),Q(x),R(x)\}$ e $\{\lnot P(A,z),\lnot Q(B)\}$ si possono risolvere due coppie di letterali:
> - $P(x,x)$ con $\lnot P(A,z)$, con $\gamma=\{x/A,\ z/A\}$: risolvente $\{Q(A),R(A),\lnot Q(B)\}$;
> - $Q(x)$ con $\lnot Q(B)$, con $\gamma=\{x/B\}$: risolvente $\{P(B,B),R(B),\lnot P(A,z)\}$.
>
> La slide lo disegna come **grafo di risoluzione**.
#### Il problema dei fattori
Con $\{P(u),P(v)\}$ e $\{\lnot P(x),\lnot P(y)\}$ la risoluzione dovrebbe produrre la clausola vuota, ma si ottiene solo $\{P(v),\lnot P(y)\}$ e ci si ferma (slide p. 55). Se un sottoinsieme dei letterali di una clausola può essere unificato, la clausola ottenuta dopo l'unificazione si dice **fattore** della clausola originaria. La risoluzione va applicata anche ai fattori delle clausole: da $\{P(u)\}$ e $\{\lnot P(x)\}$ si ottiene la clausola vuota $\{\}$.
#### Correttezza e completezza
Slide p. 56, con $\Gamma$ insieme di clausole:
- la deduzione per risoluzione è **corretta**: se $\Gamma\vdash_{RES}A$ allora $\Gamma\models A$;
- non è **completa**: può essere $\Gamma\models A$ senza $\Gamma\vdash_{RES}A$. Controesempio: $\{\}\models\{P(a),\lnot P(a)\}$, ma non vale $\{\}\vdash_{RES}\{P(a),\lnot P(a)\}$.
#### Risoluzione per refutazione
Il **teorema di refutazione** (slide p. 57): $\Gamma\cup\{\lnot A\}$ è insoddisfacibile se e solo se $\Gamma\models A$. Inoltre $\Gamma$ è insoddisfacibile se e solo se $\Gamma\vdash_{RES}\{\}$: la risoluzione è **completa rispetto alla refutazione**. Si ha dunque un metodo meccanizzabile, corretto e completo: basta aggiungere il negato della formula da dimostrare e provare a generare la clausola vuota.

> [!example] Esempio di refutazione (slide pp. 58-59)
> Base di conoscenza:
> 1. $\{P(A,J)\}$: $A$ è padre di $J$;
> 2. $\{M(B,J)\}$: $B$ è madre di $J$;
> 3. $\{\lnot P(x,y),G(x,y)\}$: padre implica genitore;
> 4. $\{\lnot M(v,w),G(v,w)\}$: madre implica genitore.
>
> Goal: $G(A,J)$, cioè "$A$ è genitore di $J$?". Si aggiunge la negazione del goal, 5. $\{\lnot G(A,J)\}$, e si cerca la clausola vuota: la 3 con la 1 dà $\{G(A,J)\}$, che con la 5 dà $\{\}$. Il grafo della slide mostra anche i risolventi $\{G(B,J)\}$, $\{\lnot P(A,J)\}$ e $\{\lnot M(A,J)\}$ dalle altre coppie. La slide osserva che è la prova per confutazione che "$A$ è genitore di $J$" è vera in un mondo in cui gli assiomi 1-4 sono veri, e che la formula $G(A,J)$ è **ground**.
#### Domande di tipo "Trova..."
Per "chi sono i genitori di $J$?" si cerca di dimostrare $\exists z\ G(z,J)$ (slide p. 60). La clausola goal negata è $FC(\lnot\exists z\,G(z,J))=\{\lnot G(z,J)\}$. La risposta, detta **risposta calcolata**, corrisponde a tutti i possibili **legami** per $z$ che permettono di ottenere la clausola vuota:
- tali legami determinano i mondi possibili in cui le formule della base sono verificate ma la negazione della formula è falsificata, quindi sono necessari a stabilire la verità del teorema;
- sono un **effetto collaterale** della dimostrazione e, in programmazione logica, costituiscono **assegnamenti a variabili**, cioè l'output di un programma.

Nell'esempio (slide p. 61) si risolve $\{\lnot G(z,J)\}$ con le clausole 3 e 4 (ottenendo $\{\lnot P(z,J)\}$ e $\{\lnot M(z,J)\}$) e con i fatti: si trovano quattro derivazioni della clausola vuota, con legami $\{z/A\}$ e $\{z/B\}$. Le risposte sono $A$ e $B$.

> [!info] Ridenominare le variabili (slide p. 62)
> È importante che ogni clausola usi **variabili diverse**, anche quelle generate. Se $\{\lnot P(x,y),G(x,y)\}$ si risolvesse con $\{\lnot G(y,J)\}$ senza ridenominare, si otterrebbe $\{x/J,\ y/J\}$ e $\{\lnot P(J,J)\}$, e non si potrebbe più unificare con $P(A,J)$ per ottenere la risposta.
### Riepilogo dalle slide
> [!warning] Ricostruito dalle sole slide
> Slide pp. 63-64, senza registrazione.

- La logica dei predicati esprime in modo più naturale le conoscenze degli agenti sul mondo; sintassi e semantica servono a formalizzare il dominio e ad automatizzare l'uso della conoscenza nella ricerca di soluzioni.
- Per verificare proprietà utili alla ricerca servono metodi algoritmici efficienti per la deduzione. Le tabelle di verità si possono applicare come nel caso proposizionale dopo la proposizionalizzazione, e il teorema di Herbrand aiuta. Secondo la slide, questo è un metodo consistente ma non completo, che diventa uno strumento completo applicando la prova per refutazione (risoluzione ground).
- L'alternativa è usare metodi che definiscono in modo più restrittivo i tipi di formule, le standardizzano e applicano la risoluzione con l'unificazione: è la risoluzione applicata a un sistema inferenziale proprio, che conduce alla **programmazione logica**, con algoritmi efficienti, consistenti e completi per la deduzione. Le slide si fermano qui e non sviluppano la programmazione logica né i due modi di concatenazione (in avanti e all'indietro), solo nominati a p. 24.
### Logica e LLM
Alla domanda di uno studente su "dove stanno" le formule logiche in un modello già addestrato, il docente risponde con una lunga digressione. In sintesi:
- **Terminologia**: un LLM come Claude o Gemini non è "un'intelligenza artificiale" ma un **agente**, cioè un'istanza che realizza artificialmente l'intelligenza; il plurale "le intelligenze artificiali" viene dalla letteratura cyberpunk degli anni '80. L'IA è una **proprietà** (la capacità di svolgere un compito in modo intelligente). Si addestra un motore di machine learning (ad esempio un Transformer) sui dati, e l'esito è il **modello**, una base di dati di pesi.
- Le regole come $\forall x\ \mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ non sono scritte in logica nei dati, ma in **linguaggio naturale**, e in molti modi ("ogni mela è rossa", "le mele sono rosse", "sono tutte rosse le mele"), con sinonimi ("pomo"). Ci sono $n$ formulazioni linguistiche dell'implicazione, $k$ della premessa e $m$ della conclusione, e il sistema deve rispondere correttamente con qualunque combinazione: ciò richiede rappresentazioni **vettoriali** in cui frasi equivalenti siano vicine.
- **Pre-training**: si toglie circa il 20% delle parole di frasi prese dal web e da Wikipedia e si chiede di ricostruirle (il compito di BERT, un encoder, 2019 secondo quanto detto a lezione; il modello è stato presentato nel 2018, l'articolo è a NAACL 2019). Per farlo bene bisogna conoscere il contesto ("nel sistema operativo abbiamo sincronizzato i processi con il metodo X"); è una vecchia teoria linguistica del significato. Le grammatiche scritte a mano diventavano ingovernabili dopo centinaia di regole, quelle che emergono dai dati no.
- **Instruction tuning**: si insegna a rispondere a nuovi compiti (ad esempio con le conversazioni di Stack Exchange); dopo aver imparato a parlare e a fare inferenze in modo coerente, i modelli generalizzano a temi nuovi (le proprietà **emergenti**).
- I modelli che ragionano **pianificano** come gli algoritmi di ricerca, generando risposte alternative e scegliendo la migliore, con un consumo di token proporzionale al non determinismo del problema: conviene decomporre il problema e dare i sottoproblemi uno per volta, mantenendo il controllo.
### Prossimi passi
Mercoledì si conclude la risoluzione nel primo ordine. Il docente propone anche un incontro anticipato all'una per risolvere insieme l'esercizio del **labirinto**, impostandolo con le proprietà del primo ordine.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra termini e formule, e tra funzioni e predicati? Cosa sono variabili libere e legate, formule chiuse e ground? Cos'è un'interpretazione nella logica del primo ordine e perché senza interpretazione non si può stabilire la verità di una formula? Perché la proposizionalizzazione non basta in presenza di funzioni, e cosa aggiunge l'unificazione alla risoluzione? Traccia: trasformazione in forma a clausole (otto passi, skolemizzazione), unificatore più generale e occur check, regola di risoluzione con fattori, refutazione e risposta calcolata per le domande "Trova...".
