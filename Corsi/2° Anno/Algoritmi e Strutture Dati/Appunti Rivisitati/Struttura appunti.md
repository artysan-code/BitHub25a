# Guida alla Creazione degli Appunti (Standard Obsidian)

Questa guida definisce lo standard organizzativo e visivo da seguire per la creazione o la revisione di tutti gli appunti del corso di **Algoritmi e Strutture Dati**. L'obiettivo è mantenere la coerenza, facilitare la lettura e ottimizzare lo studio tramite Obsidian.

## 📂 Nomenclatura File
I file devono essere nominati seguendo il pattern:
`Numero - Titolo Argomento.md`
*Esempio: `1 - Problema di Fibonacci.md`*

## 🏗️ Struttura del Documento
Ogni nota deve seguire questa gerarchia logica:
1. **Titolo H1** (Titolo dell'argomento)
2. **Abstract** (Callout introduttivo con obiettivi)
3. **Corpo della Nota** (Suddiviso in sezioni H2 e H3)
4. **Riepilogo/Conclusione** (Se applicabile)

## 🎨 Utilizzo dei Callout (Pattern Visivo)
I callout di Obsidian sono fondamentali per categorizzare le informazioni a colpo d'occhio.

| Callout | Utilizzo | Esempio |
| :--- | :--- | :--- |
| `> [!abstract]` | Introduzioni, obiettivi della lezione, scopi di un algoritmo. | Descrizione del problema di base. |
| `> [!definition]` | Definizioni formali, definizioni di strutture dati, relazioni di ricorrenza. | Definizione di Grafo o Notazione O. |
| `> [!theorem]` | Teoremi, Lemmi, Dimostrazioni matematiche, Proprietà formali. | Master Theorem, Lemma delle foglie. |
| `> [!example]` | Esercizi, quesiti storici, istanze di esempio di un algoritmo. | Problema della moneta falsa. |
| `> [!tip]` | Tecniche algoritmiche (Greedy, DP), ottimizzazioni, intuizioni chiave. | Tecnica del Caching o Divide et Impera. |
| `> [!code]` | **Pseudocodice** e **Implementazioni**. Contiene sempre entrambi. | Vedi sezione successiva. |
| `> [!warning]` | Inefficienze, bug comuni, problemi di correttezza, limiti di un algoritmo. | Caso peggiore quadratico, errore approssimazione. |
| `> [!success]` | Analisi finale, complessità ottimali, risultati di confronto, conclusioni. | Risultato $O(n \log n)$. |
| `> [!info]` | Note generali, fatti storici, curiosità o proprietà minori. | Fatto sulla macchina di Turing. |

## 💻 Standard per Codice e Pseudocodice
È **obbligatorio** fornire sempre lo pseudocodice prima dell'implementazione reale. Usa il callout `[!code]` per raggrupparli.

**Formato richiesto:**

```markdown
> [!code] Titolo dell'Algoritmo
> **Pseudocodice**
> ```text
> funzione nomeAlgoritmo(input):
>     istruzione 1
>     istruzione 2
>     return risultato
> ```
> **Implementazione (Python)**
> ```python
> def nome_algoritmo(input):
>     # codice
>     return risultato
> ```
```

## 🔢 Formattazione Matematica
*   **LaTeX:** Usa sempre il dollaro singolo per formule inline `$O(n)$` e il doppio dollaro per formule centrate:
    $$\sum_{i=1}^n i = \frac{n(n+1)}{2}$$

## 🔗 Link e Riferimenti
*   Usa i **Internal Links** `[[Note Name]]` per collegare argomenti correlati.
*   Se un argomento è "da fare" o incompleto, segnalalo chiaramente con un Callout `[!warning]`.