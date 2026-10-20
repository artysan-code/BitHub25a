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
Programma del corso ancora da completare. Le note seguono le lezioni:
1. [[01 - Interpolazione polinomiale]]: approssimazione di una funzione con un polinomio che ne assume i valori in punti dati, teorema di esistenza e unicità, prima dimostrazione con la matrice di Vandermonde e il suo determinante.
2. [[02 - Polinomi di Lagrange]]: seconda dimostrazione del teorema con i polinomi di Lagrange, definizione di polinomio d'interpolazione, forma canonica e forma di Lagrange, esempio con $\sin x$ sui nodi $0, \pi/6, \pi/4$.
3. [[03 - Errore d'interpolazione]]: funzioni di classe $C^{n+1}$, teorema sull'errore (resto) d'interpolazione e dimostrazione con le funzioni ausiliarie e il teorema di Rolle, scelta dell'intervallo, stima grezza e stima più precisa dell'errore negli esempi con $\sin x$ ed $e^{x^2}$, esercizi 1.4-1.7.
4. [[04 - Forma di Newton del polinomio d'interpolazione]]: differenze divise (definizione ricorsiva, rapporto incrementale), teorema della forma di Newton e confronto con forma canonica e di Lagrange, simmetria delle differenze divise, tabella delle differenze divise ed esempio con $\sqrt x$, algoritmo di valutazione con Ruffini–Horner e suo costo computazionale in uno e in $m$ punti, esercizi 1.8-1.9.
## Materiale di riferimento
Il corso non adotta un libro di testo. Le **dispense** scritte dal docente cambiano ogni anno e vengono fornite a fine corso.
## Note
- Docente: Carlo Garoni (`garoni@mat.uniroma2.it`) — ricevimento su appuntamento via email o Teams.
- Il corso termina prima di Natale.
- Il corso è denominato internamente "Analisi Numerica". Un esempio tipico di problema affrontato: $\displaystyle \int_{0}^1\sqrt{\cos x}\,dx$, non calcolabile in forma chiusa, richiede approssimazione numerica.
