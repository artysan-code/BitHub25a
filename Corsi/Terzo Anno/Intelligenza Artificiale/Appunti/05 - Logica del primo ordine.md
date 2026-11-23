---
tags:
  - intelligenza-artificiale
  - logica
  - logica-del-primo-ordine
slide: []
---
# Logica del primo ordine
## Sintassi, semantica e inferenza nella logica del primo ordine
Lezione 11 (09/11/2026): dopo sintassi, semantica e risoluzione della [[04 - Agenti basati sulla conoscenza#Sintassi della logica proposizionale|logica proposizionale]], si introduce la **logica del primo ordine** (*first order logic*, FOL, o calcolo dei predicati): vocabolario, termini e formule, quantificatori e variabili libere e legate, interpretazione e semantica composizionale, uso da parte di un agente (TELL e ASK con sostituzioni) e i due modi di fare inferenza, la proposizionalizzazione e la risoluzione con unificazione (AIMA cap. 8-9). Per buona parte della lezione il docente collega la logica alle rappresentazioni vettoriali dei modelli neurali e al modo in cui un LLM "impara" la logica.

> [!warning] Slide da integrare
> Le slide di questa parte (sul sito del corso `0042_Logic_CalPredicati_v1.4.1.pdf`, e per la risoluzione `Risoluzione.pdf` e `ResoLutionExample.pdf`) non sono ancora nel repo: la nota è ricavata dalla sola registrazione. Manca anche la lezione 10 (04/11/2026), di cui non c'è registrazione.
### Perché il primo ordine
Nel corso di Basi di Dati il dominio si concettualizza con **entità** (gli oggetti di cui si parla), i loro **attributi** e le **relazioni** tra entità. Nel calcolo proposizionale questo non si può fare: le proposizioni sono "chiuse", senza struttura interna. Serve dare un **nome** alle entità, alle proprietà e alle relazioni, e poter dire che cosa è vero: che uno studente ha una certa matricola è una relazione tra un'entità e una sua proprietà. Queste affermazioni sono **predicazioni**: un predicato è vero o falso su uno o più argomenti.

Il linguaggio ha quattro ingredienti:
- **costanti**: i nomi degli oggetti del mondo, in corrispondenza uno a uno con gli oggetti del dominio (i blocchi $A,\dots,E$ del [[04 - Agenti basati sulla conoscenza#Il mondo dei blocchi|mondo dei blocchi]]);
- **variabili**, che stanno per un oggetto non ancora specificato;
- **funzioni**: da uno o più oggetti del dominio danno un **altro oggetto** del dominio, come $+1$ applicato a 5 dà 6. Ad esempio $\mathit{FratelloDi}(\mathit{Roberto})$ non è Roberto, ma un'altra persona, e $\mathit{Hat}(b)$ è il blocco sopra $b$. Le funzioni non stabiliscono verità, servono a calcolare altri oggetti;
- **predicati**: da uno o più oggetti danno **vero o falso**. $\mathit{Simpatica}(\mathit{MadreDi}(\mathit{Pietro}))$ predica una proprietà, $\mathit{Amico}(\mathit{Pietro},\mathit{Paolo})$ una relazione.

La differenza tra funzioni e predicati è nel codominio: le funzioni vanno dal dominio al dominio, i predicati dal dominio a $\{\mathit{vero},\mathit{falso}\}$.

> [!info] Simboli e oggetti
> Il simbolo $A$ e il blocco $A$ non sono la stessa cosa: il primo appartiene al linguaggio, il secondo al mondo, e una **legge di interpretazione** collega l'uno all'altro. Lo stesso vale per i numeri: "1/3" e "0,333…" sono due denotazioni della stessa quantità, e il 2 può essere un carattere ASCII (8 bit), un intero in complemento a 2 o un floating point a 32 o 64 bit; in C `a == x` con `int a = 2` e `float x = 2.0` è vero, perché interessa la quantità e non il formato. Per il docente il numero naturale 2 è la classe di equivalenza di tutti gli insiemi con due elementi.
>
> Lo stesso discorso vale per le rappresentazioni **vettoriali** dei modelli neurali: l'encoder che trasforma un'immagine in un vettore produce una denotazione dell'oggetto, e si vorrebbe una legge matematica che, agendo sul vettore, permetta di verificare proprietà logiche come $\mathit{Block}(a)$ o "c'è un gatto nell'immagine". L'approccio **simbolico** all'IA ragiona su simboli discreti; quello **neurale** su rappresentazioni nel continuo. In entrambi i casi bisogna **modellare** il problema prima di costruire il sistema.
### Sintassi
Per convenzione nelle slide le **costanti** sono maiuscole e le **variabili** minuscole. Il docente consiglia nomi leggibili (`Mario`, `Pippo`) invece di lettere singole. Funzioni e predicati hanno un'**arità**: $\mathit{PadreDi}$ ha arità 1, $+$ e $-$ arità 2; $\mathit{On}$ è binario, $\mathit{Clear}$ unario, $\geq$ binario. In Prolog la tipica funzione è quella valutata da `is`.

I **termini** denotano oggetti e si definiscono ricorsivamente:
- ogni costante è un termine;
- ogni variabile è un termine (nel primo ordine le variabili stanno solo per **oggetti**, non per funzioni o predicati);
- se $f$ ha arità $n$ e $t_1,\dots,t_n$ sono termini, $f(t_1,\dots,t_n)$ è un termine. Ad esempio $+(2,3)$ in notazione prefissa, o $\mathit{PadreDi}(\mathit{Giovanni})$.

I termini **non** sono formule: non ha senso chiedere se Giovanni è vero o falso (esistere è diverso da essere vero). Le **formule** sono ciò che è vero o falso:
- **atomiche**: $\mathit{True}$ e $\mathit{False}$ (vere in tutti i modelli o in nessuno); l'**uguaglianza** tra termini, come $\mathit{Renato}=\mathit{FratelloDi}(\mathit{Roberto})$, vera se le due denotazioni indicano lo stesso individuo; un predicato applicato a termini, come $\geq(2,1)$ o $\mathit{Ama}(\mathit{Giorgio},\mathit{Lucia})$;
- **complesse**: negazione, congiunzione, disgiunzione, implicazione e doppia implicazione di formule, come nel calcolo proposizionale, e la **quantificazione** $\forall x\,\varphi$ o $\exists x\,\varphi$ di una formula.

> [!info] Uguaglianza e assegnazione
> Uno studente chiede se $+(2,3)=6$ sia un'assegnazione o un confronto. È una formula, e con l'interpretazione usuale dei numeri è **falsa**: il simbolo $=$ è un simbolo logico, come un connettivo, non un'istruzione. Sarebbe vera solo in un'interpretazione bizzarra in cui, ad esempio, 2 denota 1 e 3 denota 5. Il linguaggio è **dichiarativo**: non si cerca né si assegna, si afferma.

**Precedenza**: prima l'uguaglianza, poi i connettivi nell'ordine già visto, per ultimi i quantificatori.
### Quantificatori, variabili libere e legate
- $\forall x\,\varphi$ è vera se $\varphi$ è vera per **ogni** interpretazione di $x$ nel dominio. Si usa tipicamente con l'**implicazione**, per restringere il dominio: $\forall x\ \mathit{Persona}(x)\Rightarrow\mathit{AmaGelato}(x)$, perché per amare il gelato bisogna almeno poter amare (scrivere $\forall x\ \mathit{AmaGelato}(x)$ lo direbbe anche dei gelati stessi).
- $\exists x\,\varphi$ è vera se esiste **almeno un** individuo che, sostituito a $x$, rende vera $\varphi$. Si usa tipicamente con la **congiunzione**, per elencare le proprietà di un individuo: $\exists x\ \mathit{Mela}(x)\land\mathit{Rossa}(x)$.
- Tra i due quantificatori vale la dualità di **De Morgan**: $\forall x\,\lnot P(x)\equiv\lnot\exists x\,P(x)$ e $\lnot\forall x\,P(x)\equiv\exists x\,\lnot P(x)$.

> [!example] L'ordine dei quantificatori
> "Tutti amano qualcuno" in italiano ha due letture:
> - $\forall x\,\exists y\ \mathit{Ama}(x,y)$: ognuno ha qualcuno che ama, e la $y$ può cambiare con la $x$;
> - $\exists y\,\forall x\ \mathit{Ama}(x,y)$: c'è un individuo particolare amato da tutti.

L'**ambito** (*scope*) di un quantificatore è la formula su cui agisce, come lo scope di una variabile in un linguaggio di programmazione.
- Un'occorrenza di variabile è **legata** se cade nell'ambito di un quantificatore su quella variabile, **libera** altrimenti.
- In $\mathit{Mela}(x)\Rightarrow\exists x\,\mathit{Rossa}(x)$ le due $x$ sono variabili diverse (la prima libera, la seconda legata): la formula andrebbe riscritta $\mathit{Mela}(x)\Rightarrow\exists y\,\mathit{Rossa}(y)$.
- Una formula è **chiusa** se non ha occorrenze libere, **aperta** altrimenti.
- Una formula senza variabili è **ground**, come $\mathit{Pari}(A)$: ha lo stesso potere espressivo di una proposizione, è vera o falsa a seconda solo delle costanti, ma conserva una struttura interna (un predicato applicato a individui). $\geq(x,3)$ è aperta; $\geq(1,3)$ è ground e falsa, $\geq(10,3)$ è ground e vera.

Essere libera, chiusa o ground è una proprietà **sintattica**: una formula aperta non è né valida né insoddisfacibile di per sé, e può non essere soddisfatta da nessun individuo (se nel mondo non ci sono mele rosse).

> [!info] Perché "primo ordine"
> Non si può scrivere $\exists f\,\forall x\ f(x)=x$ ("esiste la funzione identità"): $f$ è una funzione, e nel primo ordine si quantifica solo sugli **oggetti**, non su funzioni o predicati. Per farlo, o per predicare su tutti i mondi possibili insieme, servono logiche di **ordine superiore**, fuori dal corso.
### Semantica
Una formula è vera o falsa a seconda di **com'è fatto il mondo**: se nel mondo non ci sono mele rosse, $\exists x\ \mathit{Mela}(x)\land\mathit{Rossa}(x)$ è falsa; se ci sono anche mele verdi, $\forall x\ \mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ è falsa. Per sapere se una formula è vera nel mondo bisogna saperla **interpretare**. Un'interpretazione $I$ assegna:
- a ogni **costante** $c$ un oggetto $I(c)$ del dominio, specifico e univoco (se due persone parlano di "Mario" senza accordarsi su chi sia, non si capiscono);
- a ogni **funzione** di arità $n$ una funzione dalle $n$-uple di oggetti del dominio a oggetti del dominio ($\mathit{PadreDi}$ punta all'unico padre);
- a ogni **predicato** di arità $n$ un **insieme** di $n$-uple, quelle che lo rendono vero, come le righe di una tabella relazionale. Equivalentemente $P(o_1,\dots,o_n)$ è vero se la $n$-upla appartiene all'insieme.

> [!example] Due interpretazioni del mondo dei blocchi
> Fatti $\mathit{On}(A,B)$, $\mathit{Clear}(A)$, $\mathit{Table}(B)$. Nell'interpretazione $I$ la costante $A$ denota il blocco $a$, $B$ il blocco $b$, $I(\mathit{On})=\{\langle a,b\rangle\}$, $I(\mathit{Clear})=\{a\}$, $I(\mathit{Table})=\{b\}$. In un'interpretazione $I'$ con le stesse costanti ma $\mathit{On}$ letto come "sotto" ($\langle b,a\rangle$), la formula $\mathit{On}(B,A)$ è **falsa** in $I$ e **vera** in $I'$. Senza un'interpretazione non si può stabilire la verità: fuori dalla matematica le concettualizzazioni sono opinabili (come i diagrammi ER in cui ognuno sceglie i suoi gradi di libertà), e vanno esplicitate. Vale anche per i prompt: chi scrive male il proprio modello concettuale e poi accusa l'LLM di "allucinare" ha fatto la domanda sbagliata.

La semantica è **composizionale**: il significato di $\mathit{SorellaDi}(\mathit{MadreDi}(\mathit{Pietro}))$ si ottiene interpretando la costante $\mathit{Pietro}$ (una persona), poi applicando l'interpretazione di $\mathit{MadreDi}$ (ad esempio Maria) e infine quella di $\mathit{SorellaDi}$. Lo stesso calcolo, nei modelli neurali, diventa una composizione di trasformazioni di **vettori**, cioè di matrici.

- $\forall x\,\varphi$ è vera se $\varphi$ è vera per ciascun elemento del dominio associato a $x$; $\forall x\ \mathit{Block}(x)$ nel mondo dei blocchi è vera, ma diventa falsa aggiungendo il tavolo al dominio.
- $\exists x\ \mathit{Persona}(x)$ è vera se almeno un individuo del dominio soddisfa $\mathit{Persona}$; nel mondo dei blocchi è falsa.
#### Nomi unici e mondo chiuso
> [!example] I fratelli di Riccardo
> "Riccardo ha due fratelli, Giovanni e Goffredo": $\mathit{Fratello}(\mathit{Giovanni},\mathit{Riccardo})\land\mathit{Fratello}(\mathit{Goffredo},\mathit{Riccardo})$ non basta. In logica bisogna aggiungere che $\mathit{Giovanni}\neq\mathit{Goffredo}$ (due costanti possono denotare lo stesso individuo, come "il Pupone" e "Francesco Totti") e che non ce ne sono altri:
> $$\forall x\ \mathit{Fratello}(x,\mathit{Riccardo})\Rightarrow x=\mathit{Giovanni}\lor x=\mathit{Goffredo}$$

Di solito non lo si scrive perché si adotta la **semantica delle basi di dati**: chiavi diverse indicano individui diversi (**nomi unici**) e tutto ciò che non è nella base è falso (**mondo chiuso**, [[04 - Agenti basati sulla conoscenza#Differenza con le basi di dati|già visto]]). Una base di dati è in fondo un insieme di formule ground, gestibile in modo molto efficiente; la semantica logica piena è più onerosa, sia nel numero di formule sia nelle dimostrazioni. Nel corso si userà una semantica **intermedia**, quella delle basi di dati dove è possibile.
### La logica in un agente: TELL, ASK e sostituzioni
Un agente usa la FOL con le operazioni di [[04 - Agenti basati sulla conoscenza#L'agente basato sulla conoscenza|TELL e ASK]]:
- asserisce **fatti**, da percezioni o conoscenza: $\mathit{TELL}(KB,\mathit{King}(\mathit{John}))$;
- asserisce **regole**: $\mathit{TELL}(KB,\forall x\ \mathit{King}(x)\Rightarrow\mathit{Person}(x))$ (non siamo in un film Disney, i re sono persone);
- interroga: $\mathit{ASK}(KB,\mathit{Person}(\mathit{John}))$ risponde sì, deducendolo con un passo di modus ponens;
- più interessante, interroga con variabili: $\mathit{ASK}(KB,\exists x\ \mathit{Person}(x))$, cioè "quali persone conosci?". La risposta non è solo sì o no, ma una **sostituzione** (o *binding*), come $\{x/\mathit{John}\}$, che lega la variabile della query a una costante. Se la costante è interpretata come un certo individuo, rispondere con la costante significa, nella mente dell'utente, indicare quell'individuo: il sistema lavora sui simboli (i record in memoria), e attraverso l'interpretazione parla del mondo.
### Inferenza
**Proposizionalizzazione.** Si sostituiscono le variabili con tutte le costanti possibili, ottenendo una base di conoscenza di sole formule ground, cioè proposizionale, a cui si applicano gli algoritmi del calcolo proposizionale. Con 5 blocchi e pochi predicati diventano una sessantina di proposizioni, gestibili. Ma basta **una funzione** per rendere il dominio infinito: da una costante $R$ (Roberto) si generano $\mathit{PadreDi}(R)$, $\mathit{PadreDi}(\mathit{PadreDi}(R))$, … e la versione proposizionale ha **infinite** proposizioni. Serve un metodo che eviti di enumerare tutte le istanze.

**Risoluzione** (ripresa dalla [[04 - Agenti basati sulla conoscenza#Deduzione e risoluzione|lezione 9]]). Nel caso proposizionale si mette la base in **forma normale congiuntiva** (CNF), si aggiunge la negazione della formula $\alpha$ da dimostrare e si applica la risoluzione: da $\lnot P\lor M$ e $P$ si ottiene $M$ (un passo di modus ponens); se poi c'è $\lnot M$, la risoluzione dà la **clausola vuota**, cioè un'inconsistenza. È la dimostrazione **per assurdo**: se $KB\land\lnot\alpha$ non ha modelli, allora $KB\models\alpha$. Il metodo è completo per il calcolo proposizionale.

Nel primo ordine due letterali complementari possono avere **argomenti diversi**, come $P(x,A)$ e $\lnot P(B,z)$ (esempio nostro: a lezione la forma alla lavagna non si ricava con certezza). Perché si possano risolvere:
- devono essere lo **stesso predicato** con lo stesso numero di argomenti, uno positivo e uno negato;
- bisogna trovare una **sostituzione** che renda uguali gli argomenti, l'antenato comune più specifico di cui entrambi sono generalizzazioni: qui $\{x/B,\ z/A\}$, che porta entrambi a $P(B,A)$. Significa restringersi ai mondi in cui le variabili denotano quegli individui;
- la sostituzione si applica a **tutte** le occorrenze delle variabili nelle due clausole, e la risolvente è l'unione di ciò che resta.

È l'**unificazione**, che si vedrà passo per passo nella lezione successiva. Con questo meccanismo ogni dimostrazione o arriva alla clausola vuota (e la risposta è sì) o si ferma prima, e come effetto collaterale produce le **sostituzioni** che rispondono alle query esistenziali ("esiste una $y$ che soddisfa $\mathit{Person}$?", con $y$ legata a $\mathit{John}$). È l'algoritmo che sta dietro a **Prolog**, molto efficiente.
### Logica e LLM
Alla domanda di uno studente su "dove stanno" le formule logiche in un modello già addestrato, il docente risponde con una lunga digressione. In sintesi:
- **Terminologia**: un LLM come Claude o Gemini non è "un'intelligenza artificiale" ma un **agente**, cioè un'istanza che realizza artificialmente l'intelligenza; il plurale "le intelligenze artificiali" viene dalla letteratura cyberpunk degli anni '80. L'IA è una **proprietà** (la capacità di svolgere un compito in modo intelligente). Si addestra un motore di machine learning (ad esempio un Transformer) sui dati, e l'esito è il **modello**, una base di dati di pesi.
- Le regole come $\forall x\ \mathit{Mela}(x)\Rightarrow\mathit{Rossa}(x)$ non sono scritte in logica nei dati, ma in **linguaggio naturale**, e in molti modi ("ogni mela è rossa", "le mele sono rosse", "sono tutte rosse le mele"), con sinonimi ("pomo"). Ci sono $n$ formulazioni linguistiche dell'implicazione, $k$ della premessa e $m$ della conclusione, e il sistema deve rispondere correttamente con qualunque combinazione: ciò richiede rappresentazioni **vettoriali** in cui frasi equivalenti siano vicine.
- **Pre-training**: si toglie circa il 20% delle parole di frasi prese dal web e da Wikipedia e si chiede di ricostruirle (il compito di BERT, un encoder, 2019). Per farlo bene bisogna conoscere il contesto ("nel sistema operativo abbiamo sincronizzato i processi con il metodo X"); è una vecchia teoria linguistica del significato. Le grammatiche scritte a mano diventavano ingovernabili dopo centinaia di regole, quelle che emergono dai dati no.
- **Instruction tuning**: si insegna a rispondere a nuovi compiti (ad esempio con le conversazioni di Stack Exchange); dopo aver imparato a parlare e a fare inferenze in modo coerente, i modelli generalizzano a temi nuovi (le proprietà **emergenti**).
- I modelli che ragionano **pianificano** come gli algoritmi di ricerca, generando risposte alternative e scegliendo la migliore, con un consumo di token proporzionale al non determinismo del problema: conviene decomporre il problema e dare i sottoproblemi uno per volta, mantenendo il controllo.
### Prossimi passi
Mercoledì si conclude la risoluzione nel primo ordine. Il docente propone anche un incontro anticipato all'una per risolvere insieme l'esercizio del **labirinto**, impostandolo con le proprietà del primo ordine.

> [!question] Domanda tipica d'esame
> Qual è la differenza tra termini e formule, e tra funzioni e predicati? Cosa sono variabili libere e legate, formule chiuse e ground? Cos'è un'interpretazione nella logica del primo ordine e perché senza interpretazione non si può stabilire la verità di una formula? Perché la proposizionalizzazione non basta in presenza di funzioni, e cosa aggiunge l'unificazione alla risoluzione?
