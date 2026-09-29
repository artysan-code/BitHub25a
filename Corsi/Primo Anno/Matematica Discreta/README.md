---
tipo: corso
materia: Matematica Discreta
codice: MD
anno: 1
semestre: "1"
cfu: 9
ssd: MAT/02
docenti:
  - Francesco Brenti
propedeuticita: []
---
# Matematica Discreta
Corso del prof. **Francesco Brenti** su teoria degli insiemi, teoria dei numeri, combinatoria enumerativa, grafi e asintotica: tra gli obiettivi, saper calcolare l'inversa moltiplicativa di una classe di resto, risolvere ricorsioni lineari a coefficienti costanti e codificare/decodificare messaggi con l'algoritmo RSA.
## Modalità d'esame
Le informazioni che seguono sono quelle riportate per l'A.A. 2023/2024; per l'A.A. 2024/2025 non vi sono attualmente informazioni. Secondo DidatticaWEB (A.A. 2025/2026) la valutazione è scritta.
### OPA
- Dati $a,\ b,\ n \in Z$ trovare, se esistono, tutti gli interi $x,\ y \in Z$ tali che:$$ax+by=n$$
- Dato $n\in Z$ e $n\in R$ calcolare se esiste l'inversa moltiplicativa di:$$[n]_m$$
- Saper risolvere ricorsioni lineari a coefficienti costanti.
In tutti gli esami ci sarà una domanda di ogni **OPA**.

**Rispondere a tutti gli OPA presenti nell'esame è condizione necessaria per superarlo**
**Gli errori di conto non sono un problema** interessano gli errori di concetto.

Il programma aggiornato sta su un file sul teams. Vi è presente legenda per analizzare competenze esame:
- Verde $\implies voto \geq20$
- Blu$\implies voto \geq 24$
- Rosso $\implies voto \geq 28$

Almeno 6 domande sugli argomenti $verdi\ \cup\ blu$ e 7 domande sugli argomenti $verdi\ \cup\ blu\ \cup\ rossi$ 
In tutti gli esami saranno presenti
## Programma e Appunti
Le note sono organizzate per capitolo, con la numerazione del programma del corso; le note dei capitoli II, III e IV contengono definizioni, proprietà con dimostrazione ed esempi.
### I - Teoria degli Insiemi
- [[1.1 Insiemi]]: nozione di insieme, appartenenza, sottoinsiemi, inclusione, insieme vuoto.
- [[1.2 Operazioni tra Insiemi]]: intersezione, unione, complementare, proprietà associative e distributive, De Morgan, prodotto cartesiano.
- [[1.3 Applicazioni tra insiemi]]: funzioni iniettive, suriettive, biunivoche, composizione, inversa, immagine e controimmagine, permutazioni.
- [[1.4 Relazioni]]: relazioni riflessive, simmetriche, transitive, relazioni di equivalenza, classi di equivalenza e partizioni.
- [[Esempi]]: esempi sulle applicazioni tra insiemi e sulle relazioni.
- Esercizi svolti sugli insiemi in `Appunti/I - Teoria degli Insiemi/Esercizi Svolti.md` (nome condiviso con la nota del capitolo V, quindi non linkabile in modo univoco).
### II - Numeri
- [[2.1 Principio di Induzione Matematica]]: principio di induzione completa, dimostrazioni per induzione.
- [[2.2 Principio di Buon Ordinamento]]: buon ordinamento dei naturali e teorema collegato.
- [[2.3 Numeri Positivi, Interi e Razionali]]: costruzione dei numeri interi e razionali.
- [[2.4 Numeri Reali]]: numeri reali.
- [[2.5 Numeri Primi e Composti]]: divisibilità, numeri perfetti, primi e composti, coprimi, fattorizzazione.
- [[2.6 Algoritmo Euclideo]]: massimo comune divisore, lemma della divisione, algoritmo euclideo.
- [[2.7 Conseguenze dell'Algoritmo Euclideo]]: identità di Bézout e sue conseguenze.
- [[2.8 Equazioni Diofantee Lineari (OPA 1)]]: condizione di risolubilità e soluzioni delle equazioni diofantee lineari.
- [[2.9 Classi di Resto (OPA 2)]]: congruenza, classi di resto, somma e prodotto, inversa moltiplicativa.
- [[2.9.E Esercizi]]: esercizi su MCD e classi di resto.
- [[2.10 La Funzione di Eulero]]: funzione di Eulero, formula chiusa, teorema di Eulero.
- [[2.11 Il Codice RSA]]: problema fondamentale della crittografia, codifica e decodifica RSA.
- [[2.12 Numerazioni in Basi Diverse]]: rappresentazione dei numeri in basi diverse.
- [[2.13 Numeri Complessi]]: numeri complessi, coniugato, norma, forma polare.
### III - Combinazioni Enumerative
- [[3.1 Il problema fondamentale della combinatoria enumerativa]]: problema fondamentale e possibili soluzioni (formule, ricorsioni, funzioni generatrici).
- [[3.2 Proprietà Fondamentali]]: cardinalità di prodotto cartesiano, potenza e unione di insiemi.
- [[3.3 Coefficienti Binomiali]]: sottoinsiemi di un insieme, coefficienti binomiali e loro proprietà.
- [[3.4 Il Principio di Inclusione-Esclusione]]: principio di inclusione-esclusione.
- [[3.5 Composizioni]]: composizioni e composizioni deboli.
- [[3.6 Coefficienti Multinomiali]]: assegnazione di oggetti in categorie, coefficienti multinomiali.
- [[3.7 Sequenze con Ripetizioni]]: permutazioni di sequenze con ripetizioni.
- [[3.8 Enumerazione Pratica Poker]]: esempio di enumerazione applicato alle mani di poker.
- [[3.9 Ricorsioni Lineari a Coefficienti Costanti (OPA 3)]]: risoluzione delle ricorsioni lineari a coefficienti costanti.
### IV - Somme e approssimazioni
- [[4.1 Somme e Approssimazioni]]: formule chiuse, metodo della perturbazione, somma geometrica.
- [[4.2 Somme Polinomiali]]: formula chiusa per le somme polinomiali.
- [[4.3 Somme Non Polinominiali]]: stima di somme non polinomiali con gli integrali.
- [[4.4 Somme Doppie]]: somme doppie e inversione dell'ordine di sommatoria.
- [[4.5 Prodotti]]: tecnica del logaritmo per i prodotti, formula di Stirling.
- [[4.6 Notazione Asintotiche]]: o-piccolo, O-grande, Omega, Teta, equivalenza asintotica.
- [[4.7 Quanto è grande l'infinito]]: insiemi infiniti, cardinalità, teorema di Cantor.
### V - Grafi
- [[5.1 Grafi]]: grafi, cammini, connessione, alberi, grado, isomorfismi.
- [[5.2 Accoppiamenti]]: accoppiamenti e grafi bipartiti, teorema di Hall.
- [[5.3 Colorazioni]]: colorazioni e numero cromatico.
- [[5.4 Grafi Diretti]]: digrafi, cammini e cicli diretti, raggiungibilità, digrafi aciclici.
- [[5.5 Reti di Comunicazione]]: reti di comunicazione, smistamenti, latenza e congestione.
- [[5.6 Orari Paralleli]]: orari paralleli, sentieri critici, profondità.
- [[Esercizi da Svolgere]]: esercizi proposti sulle somme doppie.
- Esercizi svolti del capitolo in `Appunti/V - Grafi/Esercizi Svolti.md` (ricorsioni lineari e confronto asintotico; nome condiviso con la nota del capitolo I).
### Esercizi
Esercizi svolti, numerati come le esercitazioni del docente (in `Materiale Didattico/Esercitazioni/`).
- [[01 - Insiemi e Relazioni]], [[02 - Funzioni e Relazioni]], [[03 - Induzione]], [[04 - MCD]]
- [[05 - Equazioni Diofantee Lineari (OPA)]], [[06 - Inversa moltiplicativa (OPA)]], [[07 - Funzione di Eulero]], [[8 e 9 - RSA]]
- [[11 - Coefficienti Binomiali]], [[12 e 13 - Inclusione-Esclusione]], [[14, 15, 16, 17 - Ricorsioni (OPA)]]
- [[18 - Somme Polinomiali]], [[19 - Somme non Polinomiali]], [[20 - Somme Doppie]], [[21, 22, 23 - Asintotica]]
- [[24 - Grafi]], [[25 - Accoppiamenti]], [[26 - Isomorfismi]], [[27 e 28 - Reti di Comunicazione]]
### Programma didattico (A.A. 2023/2024)
Il programma del corso è quello che si trova qui sotto.
#### Tipo Verde 
 - [ ] La nozione di insieme e di appartenenza di un elemento ad un insieme. 
 - [ ] Sottoinsiemi di un insieme: inclusione di un insieme in un altro. 
 - [ ] L'insieme vuoto. 
 - [ ] Intersezione e unione di due insiemi. 
 - [ ] Proprietà associativa e distributiva dell'unione e dell'intersezione. 
 - [ ] Diagrammi di Venn. 
 - [ ] L'insieme complementare di un insieme. 
 - [ ] Leggi di De Morgan. 
 - [ ] Il prodotto cartesiano di due insiemi e sue proprietà. 
 - [ ] Funzioni tra insiemi. 
 - [ ] Funzioni iniettive, suriettive, e biunivoche. 
 - [ ] Composizione di funzioni. 
 - [ ] Associatività della composizione. 
 - [ ] La composizione di due funzioni iniettive è iniettiva, e similmente per funzioni suriettive e biunivoche. 
 - [ ] L'inversa di una funzione biunivoca. 
 - [ ] La funzione identità. 
 - [ ] La composizione di una funzione e della sua inversa è la funzione identità. 
 - [ ] L'immagine e la controimmagine di un sottoinsieme mediante una funzione. 
 - [ ] La controimmagine di una unione è l'unione delle contro-immagini, e similmente per l'intersezione. 
 - [ ] Permutazioni. 
 - [ ] Calcolo del prodotto di due permutazioni, e dell'inversa di una permutazione, usando la notazione uni-linea. 
 - [ ] Relazioni su insiemi. 
 - [ ] Relazioni simmetriche, riflessive, e transitive. 
 - [ ] Relazioni di equivalenza. 
 - [ ] Classi di equivalenza. 
 - [ ] Due classi di equivalenza o coincidono o sono disgiunte. 
 - [ ] Partizioni di un insieme. 
 - [ ] Le classi di equivalenza di un insieme rispetto ad una relazione di equivalenza sono una partizione. 
 - [ ] Dimostrazioni dirette. 
 - [ ] Dimostrazioni per assurdo. 
 - [ ] Il Principio di Induzione Matematica. 
#### Tipo Rosso
 - [ ] Il Principio del Buon Ordinamento. 
#### Tipo Verde
 - [ ] Numeri naturali. 
 - [ ] Numeri interi. 
#### Tipo Blu
 - [ ] I numeri razionali sono classi di equivalenza (no dim.). 
#### Tipo Verde
 - [ ] I numeri complessi. 
 - [ ] L'unita' immaginaria. 
 - [ ] Somma, prodotto e quoziente di numeri complessi. 
 - [ ] Il coniugato e la norma di un numero complesso. 
 - [ ] Divisibilità tra numeri interi. 
 - [ ] Numeri perfetti. 
 - [ ] Numeri primi e composti. 
 - [ ] Numeri coprimi. 
 - [ ] Ogni numero >1 è prodotto di numeri primi. 
#### ???
 - [x] L'infinita' dei numeri primi.
#### Tipo Verde
 - [ ] L'Algoritmo Euclideo per la determinazione del massimo comune divisore di due interi positivi. 
 - [ ] L'Identità di Bezout. 
 - [ ] Se un numero primo divide un prodotto allora divide uno dei fattori. 
 - [ ] Il Teorema Fondamentale dell'Aritmetica. 
 - [ ] Equazioni Diofantee lineari. 
 - [ ] Un'equazione Diofantea lineare a due incognite ha soluzione se e solo se il massimo comun divisore dei due coefficienti divide il termine noto. 
 - [ ] La relazione di congruenza. 
 - [ ] La relazione di congruenza e' una relazione di equivalenza (no dim.). Le classi di resto.
 - [ ] Somma e prodotto di due classi di resto. 
 - [ ] L'inversa moltiplicativa di una classe di resto. 
 - [ ] La funzione di Eulero. 
 - [ ] La formula chiusa per la funzione di Eulero. 
 - [ ] La funzione di Eulero del prodotto di due numeri e' il prodotto delle funzioni di Eulero dei due numeri se questi sono coprimi. 
 - [ ] La moltiplicazione per la classe di resto di un numero k modulo n e' una biezione delle classi di resto modulo n che sono coprime con n, se k ed n sono coprimi. 
 - [ ] Il Teorema di Eulero. 
 - [ ] L'algoritmo di crittografia RSA. 
 - [ ] Numerazioni in basi diverse. 
 - [ ] La cardinalità del prodotto Cartesiano di due insiemi e' il prodotto delle loro cardinalità. 
 - [ ] La cardinalità della potenza di due insiemi e' la potenza delle loro cardinalità. 
 - [ ] La cardinalità dell'unione di due insiemi e' uguale alla somma delle loro cardinalità meno la cardinalità dell'intersezione. 
 - [ ] Il problema fondamentale della combinatoria enumerativa e sue possibili soluzioni. 
 - [ ] Formule, ricorsioni, funzioni generatrici. 
 - [ ] Ci sono 2 alla n sottoinsiemi di un insieme di cardinalità n. 
 - [ ] Coefficienti binomiali. 
 - [ ] Il numero di sottoinsiemi di cardinalità k di un insieme di cardinalità n e' n binomiale k. 
 - [ ] Il coefficiente di x alla k in (1+x) alla n e' n binomiale k. 
 - [ ] Assegnazione di oggetti distinguibili in categorie distinguibili, ognuna di cardinalità data. 
 - [ ] Coefficienti multinomiali. 
 - [ ] La formula per i coefficienti multinomiali. 
 - [ ] Sequenze con ripetizioni. 
 - [ ] Permutazioni di una sequenza con ripetizioni. 
 - [ ] Il numero di permutazioni di una sequenza con ripetizioni. 
 - [ ] Composizioni. 
 - [ ] Parti di una composizione. 
 - [ ] Il numero di composizioni di un intero n in k parti e' n-1 binomiale k-1. 
 - [ ] Composizioni deboli. 
 - [ ] Il numero di composizioni deboli di un intero n in k parti e' n+k-1 binomiale k-1. 
 - [ ] Il Principio di Inclusione-Esclusione. 
 - [ ] La risoluzione delle ricorsioni lineari a coefficienti costanti. 
 - [ ] Formule chiuse. 
 - [ ] La formula chiusa per la somma geometrica. 
#### Tipo Blu
 - [ ] Somme polinomiali. 
 - [ ] La formula chiusa per una somma polinomiale. 
 - [ ] Somme non polinomiali. 
 - [ ] Se f e' una funzione reale continua e monotona crescente allora la somma, per i=1,..,n, di f(i) e' limitata superiormente (rispettivamente, inferiormente) da f(n) + l'integrale di f(x) da 1 ad n (rispettivamente, f(1) + l'integrale di f(x) da 1 ad n). 
 - [ ] Similmente se f e' una funzione reale continua e monotona decrescente. 
#### Tipo Rosso
 - [ ] Somme doppie. 
 - [ ] La tecnica di inversione dell'ordine di sommatoria per il calcolo e la stima di una somma doppia. 
 - [ ] Prodotti. 
 - [ ] La tecnica del logaritmo per il calcolo e la stima di prodotti. 
 - [ ] La formula di Stirling (no dim.). 
#### Tipo Blu
 - [ ] Notazioni asintotiche. 
 - [ ] Successioni e funzioni asintoticamente piu' piccole di altre. 
 - [ ] Successioni e funzioni asintoticamente equivalenti. 
 - [ ] x alla a e' asintoticamente piu' piccola di x alla b se 0 < a < b. 
 - [ ] Il logaritmo di x e' asintoticamente piu' piccolo di qualsiasi potenza positiva di x.
 - [ ] Qualsiasi potenza di x e' asintoticamente piu' piccola di a alla x se a>1. 
 - [ ] o-piccolo. 
 - [ ] O-grande. 
 - [ ] Se f e' un o-piccolo di g allora f e' un O-grande di g. 
 - [ ] Se f e' asintoticamente equivalente a g allora f e' un O-grande di g. 
 - [ ] Un polinomio di grado k e' un O-grande di x alla k. 
 - [ ] Se f e' un o-piccolo di g allora g non e' un O-grande di f. 
 - [ ] Omega.
 - [ ] f e' un O-grande di g se e solo se g e' un Omega di f. 
 - [ ] Teta. 
#### ???
 - [x] Insiemi infiniti. 
 - [x] La cardinalita' di un insieme infinito. 
 - [x] Non esiste una biezione tra un insieme ed il suo insieme delle parti. 
 - [x] Un insieme ha cardinalita' strettamente piu' piccola del suo insieme delle parti. 
#### Tipo Verde
 - [ ] Grafi. 
 - [ ] Cammini. 
 - [ ] Sentieri. 
 - [ ] Cammini chiusi. 
 - [ ] Circuiti. 
 - [ ] Grafi connessi. 
 - [ ] Alberi. 
 - [ ] Il grado di un vertice. 
 - [ ] Sottoinsiemi indipendenti e completi. 
 - [ ] Isomorfismi tra grafi. 
 - [ ] Accoppiamenti. 
 - [ ] Grafi bipartiti. 
 - [ ] Accoppiamenti di un grafo bipartito. 
 - [ ] La caratterizzazione dei grafi bipartiti che ammettono un accoppiamento. 
#### Tipo Blu
 - [ ] Grafi bipartiti costretti nei gradi. 
 - [ ] Se un grafo bipartito e' costretto nei gradi in un senso allora ammette un accoppiamento nello stesso senso. 
 - [ ] Grafi bipartiti regolari. 
#### Tipo Verde
 - [ ] Colorazioni di un grafo.
 - [ ] Il numero cromatico di un grafo. 
 - [ ] Grafi vuoti e completi. 
#### Tipo Blu
 - [ ] Se il grado massimo di un grafo e' k allora il grafo puo' essere colorato con k+1 colori. 
 - [ ] Il numero cromatico di un grafo e' limitato superiormente dal massimo, su tutti i vertici v del grafo, di d(v)+1. 
#### Tipo Verde
 - [ ] Grafi diretti (digrafi). 
 - [ ] Cammini diretti. 
 - [ ] Sentieri diretti. 
 - [ ] Cammini chiusi diretti. 
 - [ ] Cicli. 
 - [ ] Raggiungibilita'. 
 - [ ] Distanza da un vertice ad un altro. 
 - [ ] Vertici comparabili e incomparabili. 
 - [ ] Catene. 
 - [ ] Grado interno ed esterno di un vertice. 
 - [ ] Digrafi aciclici. 
#### Tipo Rosso
 - [ ] Reti di comunicazione. 
 - [ ] Terminali. 
 - [ ] Nodi di input e nodi di output.
 - [ ] Diametro di una rete di comunicazione.
 - [ ] Problemi di smistamento.
 - [ ] Smistamenti. 
 - [ ] La latenza e congestione di uno smistamento.
 - [ ] La congestione di una rete di comunicazione.
 - [ ] L'albero binario completo, suo diametro e congestione.
 - [ ] La griglia.
 - [ ] La congestione della griglia e' 2.
 - [ ] La farfalla e la sua congestione.
 - [ ] Orari paralleli.
 - [ ] Passo, tempo, e numero di processori di un orario.
 - [ ] Sentieri critici.
 - [ ] Profondita' di un elemento in un digrafo aciclico.
 - [ ] Un orario parallelo di tempo minimo in un digrafo aciclico e' dato dalla partizione il cui blocco i-esimo consiste di tutti gli elementi di profondita' i. 
## Materiale di riferimento
- **Esami** in `Materiale Didattico/Esami/`: prove d'esame (`MatDisc15`, `MatDisc17`, `MatDisc18`, `MatDisc23`, `Esame`, `Prova_Esame`) e programma del corso in tre versioni (`Programma`, `Programma Ragionato`, `Programma_nel_Testo`).
- **Esercitazioni** in `Materiale Didattico/Esercitazioni/`: fogli di esercizi del docente numerati da 1 a 28 (insiemi, induzione, MCD, equazioni diofantee, inversa moltiplicativa, funzione di Eulero, RSA, coefficienti binomiali, inclusione-esclusione, ricorsioni, somme, asintotica, grafi, accoppiamenti, isomorfismi, reti di comunicazione) più `Extra_Esercizi vecchi esami`.
- Il programma aggiornato è pubblicato sul Team del corso (dalle informazioni dell'A.A. 2023/2024).
## Note
Ricevimento Brenti:
- Su appuntamento
- Scrivere a brenti@mat.uniroma2.it
- Scrivere con 7-10 giorni di anticipo
Anno 2024/2025: non vi sono attualmente informazioni.
