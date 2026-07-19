---
tags:
  - algoritmi
  - np
  - esercizi
---
# Esercizi d'esame — NP-Completezza
Tutti gli item su **NP-Completezza** realmente usciti nei **12 compiti** di Modulo II dal giugno 2024 al giugno 2026, con la risposta modello. **Nessun esercizio è inventato**: ogni testo è verbatim dal compito, con appello, esercizio e punto.
> [!info] Cosa dicono i numeri per questo argomento
> **4 item** su 2 appelli diversi (su 12 analizzati). Slot: Es. 2 ×4.
> Cosa ti chiede di produrre: definisci ×2, altro ×2.
> Richieste esplicite di **dimostrazione**: **0**.
> Come usarlo: copri la riga «**Risposta.**», rispondi ad alta voce, scopri. Sui vero/falso motiva **sempre in una riga** — il «vero/falso» secco non prende punti pieni.
### 1. Riduzione polinomiale
*(16/07/2024 · Es. 2 · prima domanda aperta · definisci)*
> Si definisca formalmente il concetto di riduzione polinomiale fra problemi. (Max 5 righe.)

**Risposta.** Un problema $A$ si riduce polinomialmente a un problema $B$ (scritto $A \le_p B$) se esiste una funzione $f$ calcolabile in tempo polinomiale tale che, per ogni istanza $x$ di $A$: $x$ è un'istanza sì per $A$ $\iff$ $f(x)$ è un'istanza sì per $B$. In altre parole, $f$ trasforma in tempo polinomiale ogni istanza di $A$ in un'istanza di $B$ che ha la stessa risposta.
### 2. Riduzioni come evidenza di difficoltà
*(16/07/2024 · Es. 2 · seconda domanda aperta · argomenta)*
> Si argomenti su come è possibile utilizzare le riduzioni polinomiali per dare evidenza che un problema è computazionalmente difficile. (Max 5 righe.)

**Risposta.** Se $A \le_p B$ e $A$ è noto essere (NP-)difficile, allora anche $B$ deve esserlo: se esistesse un algoritmo polinomiale per $B$, componendolo con la riduzione $f$ si otterrebbe un algoritmo polinomiale per $A$, contraddicendo la sua difficoltà (a meno che $P=NP$). Quindi si sceglie un problema $A$ già noto come difficile (tipicamente NP-completo) e si costruisce una riduzione $A \le_p B$: questo trasferisce la difficoltà di $A$ a $B$, dando evidenza che anche $B$ non ammette soluzione polinomiale.
### 3. Definizione di 3-SAT e Independent Set
*(9/06/2024, nota: data da verificare — cartella riporta 09/09/2024 · Es. 2 · punto 1 · definisci)*
> Si definiscano formalmente i problemi decisionali 3-SAT e Independet Set. (Max 5 righe.)

**Risposta.** **3-SAT**: data una formula booleana $\phi$ in forma normale congiuntiva con esattamente 3 letterali per clausola, decidere se esiste un assegnamento di verità alle variabili che soddisfa tutte le clausole (rende $\phi$ vera).
**Independent Set**: dato un grafo $G=(V,E)$ e un intero $k$, decidere se esiste $S \subseteq V$ con $|S| \ge k$ tale che nessun arco di $E$ abbia entrambi gli estremi in $S$ (nessuna coppia di vertici di $S$ è adiacente).
### 4. Riduzione 3-SAT → Independent Set
*(9/06/2024, nota: data da verificare — cartella riporta 09/09/2024 · Es. 2 · punto 2 · mostra)*
> Si mostri come è possibile utilizzare un (ipotetico) algoritmo polinomiale per Independet Set per risolvere 3-SAT. (Max 5 righe.)

**Risposta.** Da $\phi$ si costruisce in tempo polinomiale un'istanza $(G,k)$: per ogni clausola (3 letterali) un triangolo di 3 vertici con archi interni; si aggiunge un arco fra ogni coppia di vertici che rappresentano un letterale e il suo negato in clausole diverse; $k$ = numero di clausole. Si dimostra $\phi$ soddisfacibile $\iff$ $G$ ammette independent set di taglia $\ge k$ (un vertice per triangolo, corrispondente a un letterale vero, mai scegliendo letterale e negazione). Dato l'ipotetico algoritmo polinomiale per IS: si costruisce $(G,k)$ da $\phi$, si esegue l'algoritmo su $(G,k)$ e se ne restituisce la risposta come risposta per 3-SAT — l'intera procedura resta polinomiale.
