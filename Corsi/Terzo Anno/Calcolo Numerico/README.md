---
tipo: corso
materia: Calcolo Numerico
codice: CN
anno: 3
semestre: "1"
cfu: 6
ssd: MAT/08
docenti:
  - Carlo Garoni
propedeuticita:
  - Analisi Matematica
  - Matematica Discreta
---
# Calcolo Numerico
Corso del prof. **Carlo Garoni** sull'approssimazione numerica di problemi non risolvibili in forma chiusa.
## Modalità d'esame
Esame **scritto + orale**. Gli esami passati sono disponibili sulla pagina web del docente.

Possibilità di crediti D con MATLAB (annuncio su Teams).
## Programma e Appunti
Programma del corso ancora da completare. Gli appunti sono organizzati per argomento: ogni nota raccoglie tutte le lezioni su quell'argomento, una sezione per lezione.
1. [[01 - Interpolazione polinomiale]]
	- Lezione 1 (06/10/2026), [[01 - Interpolazione polinomiale#Esistenza e unicità del polinomio d'interpolazione|esistenza e unicità del polinomio d'interpolazione]]: approssimazione di una funzione con un polinomio che ne assume i valori in punti dati, teorema di esistenza e unicità, prima dimostrazione con la matrice di Vandermonde e il suo determinante.
	- Lezione 2 (08/10/2026), [[01 - Interpolazione polinomiale#Polinomi di Lagrange|polinomi di Lagrange]]: seconda dimostrazione del teorema con i polinomi di Lagrange, definizione di polinomio d'interpolazione, forma canonica e forma di Lagrange, esempio con $\sin x$ sui nodi $0, \pi/6, \pi/4$.
	- Lezione 3 (13/10/2026), [[01 - Interpolazione polinomiale#Errore d'interpolazione|errore d'interpolazione]]: funzioni di classe $C^{n+1}$, teorema sull'errore (resto) d'interpolazione e dimostrazione con le funzioni ausiliarie e il teorema di Rolle, scelta dell'intervallo, stima grezza e stima più precisa dell'errore negli esempi con $\sin x$ ed $e^{x^2}$, esercizi 1.4-1.7.
	- Lezione 4 (15/10/2026), [[01 - Interpolazione polinomiale#Forma di Newton del polinomio d'interpolazione|forma di Newton]]: differenze divise (definizione ricorsiva, rapporto incrementale), teorema della forma di Newton e confronto con forma canonica e di Lagrange, simmetria delle differenze divise, tabella delle differenze divise ed esempio con $\sqrt x$, algoritmo di valutazione con Ruffini–Horner e suo costo computazionale in uno e in $m$ punti, esercizi 1.8-1.9.
	- Lezione 5 (20/10/2026), prima parte, [[01 - Interpolazione polinomiale#Valutazione e aggiunta di un nodo|valutazione e aggiunta di un nodo]]: esempio dell'algoritmo di valutazione con la tabella delle differenze divise e Ruffini–Horner, aggiunta di un nodo d'interpolazione con la forma di Newton e suo costo computazionale, esempio con $\cos(\pi x)+x^2$, esercizi 1.10 e 1.12.
2. [[02 - Integrazione numerica]]
	- Lezione 5 (20/10/2026), seconda parte, [[02 - Integrazione numerica#Formula dei trapezi|formula dei trapezi]]: cos'è l'integrazione numerica, derivazione della formula dei trapezi di ordine $n$ e interpretazione come somma di aree di trapezi.
	- Lezione 6 (22/10/2026), [[02 - Integrazione numerica#Errore della formula dei trapezi|errore della formula dei trapezi]]: lemma che generalizza il teorema della media integrale e sua dimostrazione, teorema sull'errore della formula dei trapezi e dimostrazione (polinomio d'interpolazione su ogni sottointervallo, verifica delle ipotesi del lemma, media aritmetica e valori intermedi), esempio con $\int_0^1\sqrt{\cos x}\,dx$: calcolo di $I_{10}$ e stima dell'errore.
	- Lezione 7 (27/10/2026), [[02 - Integrazione numerica#Scelta di n ed estrapolazione|scelta di n ed estrapolazione]]: stima uniforme di $|f''|$ (disuguaglianza triangolare, moduli, monotonia, frazioni), esercizi in cui si fissa $\varepsilon$ e si determina $n$ tale che $|I-I_n|\leq\varepsilon$, forma generale $n(\varepsilon)=C/\sqrt\varepsilon$, metodo di estrapolazione (polinomio d'interpolazione dei dati $(h_i^2,I_{n_i})$ valutato in $0$), esempio completo con $\int_0^2xe^x\,dx$, esercizi 2.1 e 2.3.
3. [[03 - Analisi delle matrici]]
	- Lezione 8 (29/10/2026), [[03 - Analisi delle matrici#Richiami di algebra lineare|richiami di algebra lineare]]: determinante con il metodo di Laplace e regola della scacchiera, teorema di Binet, traccia, determinante e raggio spettrale in termini degli autovalori, esempio sugli autovalori dedotti dalla traccia, matrici invertibili e inversa del prodotto, calcolo dell'inversa con il metodo dei cofattori, matrici diagonalizzabili e dimostrazione che $A=XDX^{-1}$ dà autovalori e autovettori, esercizi 3.1 e 3.2.
## Materiale di riferimento
Il corso non adotta un libro di testo. Le **dispense** scritte dal docente cambiano ogni anno e vengono fornite a fine corso.
## Note
- Docente: Carlo Garoni (`garoni@mat.uniroma2.it`) — ricevimento su appuntamento via email o Teams.
- Il corso termina prima di Natale.
- Il corso è denominato internamente "Analisi Numerica". Un esempio tipico di problema affrontato: $\displaystyle \int_{0}^1\sqrt{\cos x}\,dx$, non calcolabile in forma chiusa, richiede approssimazione numerica.
