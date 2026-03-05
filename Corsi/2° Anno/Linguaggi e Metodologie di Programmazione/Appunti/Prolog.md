## Paradigma Dichiarativo vs Procedurale
L'obiettivo del corso è uscire dalla mentalità **procedurale** (dire al computer _come_ fare qualcosa) per abbracciare quella **dichiarativa** (dire al computer _cosa è vero_).

| Procedurale   | Dichiarativo                             |                                       |
| ------------- | ---------------------------------------- | ------------------------------------- |
| **Approccio** | Descrive il processo                     | Descrive la realtà                    |
| **Variabile** | Area di memoria con un valore che cambia | Termine che si unifica una volta sola |
| **Esempi**    | C, Java, Python                          | Prolog                                |

## Variabili e Costanti
In prolog la definizione delle "variabili" ha delle regole precise che sono imposte per una qualità di codice e anche logica.

| Tipo                         | Sintassi                 | Note                                                |
| ---------------------------- | ------------------------ | --------------------------------------------------- |
| Variabile                    | Inizia con **maiuscola** | Il suo valore ci interessa — Prolog lo cerca        |
| Variabile Anonima            | **`_`**                  | Il valore non ci interessa; ogni `_` è indipendente |
| Costante (atomo)             | Inizia con **minuscola** | Non è una stringa, è un simbolo                     |
| Costante con maiuscole/spazi | Tra **apici** `''`       | Equivalente all'atomo minuscolo                     |
|                              |                          |                                                     |

```prolog
genitore(marco, biagio)       % costanti in minuscolo
genitore('Marco', 'Biagio')   % stesso significato, notazione alternativa
```
## Unificazione
In Prolog non si _assegna_ un valore a una variabile: si **unifica**. Unificare significa trovare i valori che rendono due termini identici. Una volta unificata, una variabile non cambia più.

```prolog
% Procedurale: x cambia valore
x <- 1
x <- x + 1   % x ora vale 2

% Dichiarativo: X si unifica con 1 e rimane 1
X = 1
```

## Fatti, Regole e Predicati
Un programma Prolog è una **base di conoscenza** composta da fatti e regole.
### Fatti
Verità assolute, definite esplicitamente.

```prolog
genitore(mario, luigi).
genitore(mario, sofia).
```
### Regole
Verità condizionali: sono vere _se_ le condizioni dopo `:-` sono soddisfatte.

```prolog
fratello(X, Y) :-
    genitore(G, X),
    genitore(G, Y).
```

- `:-` si legge **"se"**
- `,` si legge **"e"** (AND logico)
- `fratello` è il **predicato**; `X`, `Y`, `G` sono le variabili

La regola si legge: _"X e Y sono fratelli se esiste G genitore di entrambi."_
### Variabile anonima `_`
```prolog
genitore(_, X)   % X ha un genitore — chi sia non importa
genitore(_, Y)   % Y ha un genitore — può essere uno diverso dal precedente
```

Ogni `_` è completamente indipendente dalle altre.

## Query
Con `?-` si pone una domanda alla base di conoscenza. Prolog risponde `true`/`false` o restituisce i valori delle variabili.

```prolog
?- genitore(mario, luigi).    % true
?- genitore(mario, X).        % X = luigi ; X = sofia
?- fratello(luigi, sofia).    % true (per backtracking sulla regola)
```

## Esempio: Cruciverba
Un esempio concreto della potenza del paradigma dichiarativo. Si definiscono i **fatti** (le parole disponibili) e i **vincoli** (le lettere di intersezione), e Prolog trova autonomamente la soluzione tramite **backtracking**.

```prolog
% Fatti: parole come sequenze di lettere
word(m,a,r,i,o).
word(l,i,v,e,s).
% ...

% Regola: il cruciverba è risolto quando i vincoli sono soddisfatti
cruciverba :-
    word(A1, B1, C1, _, _),
    word(A1, A2, A3, A4, A5),
    % le lettere condivise tra parole orizzontali e verticali devono coincidere
    ...
```

Non si scrive l'algoritmo di ricerca: Prolog prova combinazioni in automatico finché non trova quelle valide.
## Lezione 2
Seguiamo il capitolo 1 del libro di prolog sul teams

Esercizio
```Prolog
persona(mario).
persona(marius).
persona(dario).
persona(maria).

persona('Daria').
```

Se facciamo la query:
```Prolog
?-   persona(mario). -> true
?-   persona(X). -> X = mario \\ esiste un valore X per cui vale il predicato persona, true e dovremmo unificare X a mario.

```

Se vogliamo fare una query come quella di persona(X) e saperne tutte possiamo usare il ;

Per l'esercizio lascia stare roba sopra, facciamo riferimento a Esercizi -> Lezione 2 o come lo avrò chiamato. Controlla.

Scrivere predicati con lo stesso numero di cardinalità vicini.

Obiettivo del corso (sfida con il prof) costruire photomath.