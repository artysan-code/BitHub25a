---
tags:
  - algoritmi
  - dp
  - esercizi
nota: "[[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]]"
---
# Esercizi — Programmazione Dinamica III
Palestra della nota [[06 - Programmazione Dinamica III (Sequence Alignment e Bellman-Ford)]].

> [!warning] Nel campione questa nota non ha ancora prodotto item d'esame
> Sequence Alignment, Hirschberg e Bellman-Ford **non compaiono** nelle 24 tracce esaminate, in nessuna posizione. Sono però programma pieno e materia d'orale, e Bellman-Ford è un algoritmo con nome proprio: l'unico item qui sotto è **costruito** sulla forma che l'Esercizio 2 usa per gli algoritmi con nome proprio, cioè «enuncia idea e complessità di X».
> Quando arriveranno item reali su questi argomenti, questo file è il posto dove metterli.
## Hirschberg
### Idea e complessità di Hirschberg
> [!question] Domanda costruita — Idea e complessità di Hirschberg
> **D:** Qual è l'idea alla base dell'algoritmo di Hirschberg per il sequence alignment, e quali sono tempo e spazio risultanti rispetto alla DP standard?

> [!info]- Risposta modello
> **Idea.** Il valore $\text{OPT}(i,j)$ si può calcolare mantenendo solo due colonne della matrice (quella corrente e la precedente), in spazio $O(m+n)$ — ma così si perde la possibilità di fare il traceback. Hirschberg recupera l'allineamento sfruttando il grafo di edit: si calcola $f(i,j)$ (cammino minimo da $(0,0)$ a $(i,j)$, che coincide con $\text{OPT}(i,j)$) e $g(i,j)$ (cammino minimo da $(i,j)$ a $(m,n)$), ciascuno in tempo $O(mn)$ e spazio $O(m+n)$.
>
> **Divide.** Sulla colonna centrale $n/2$ si trova l'indice $q^*$ che minimizza $f(q,n/2)+g(q,n/2)$: per l'Osservazione 2, il nodo $(q^*,n/2)$ appartiene a un cammino minimo, quindi fa parte di un allineamento ottimo.
>
> **Conquer.** Si applica ricorsivamente lo stesso procedimento ai due sotto-problemi $(x_1\ldots x_{q^*}, y_1\ldots y_{n/2})$ e $(x_{q^*+1}\ldots x_m, y_{n/2+1}\ldots y_n)$, dimezzando ogni volta l'intervallo di colonne.
>
> **Complessità.** Tempo: $T(m,n) \leq T(q^*,n/2)+T(m-q^*,n/2)+O(mn)$, che per induzione forte su $m+n$ dà $T(m,n) \leq 2cmn = O(mn)$ — stesso ordine della DP standard. Spazio: $\Theta(m+n)$, perché ogni chiamata ricorsiva usa $\Theta(m)$ spazio per calcolare $f(\cdot,n/2)$ e $g(\cdot,n/2)$, e il numero di chiamate ricorsive attive è limitato.
>
> **Confronto.** Rispetto alla DP standard ($\Theta(mn)$ tempo e spazio), Hirschberg mantiene lo stesso ordine di tempo ma riduce lo spazio da quadratico a lineare — il vantaggio è puramente sullo spazio.
