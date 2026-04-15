# Linguaggi e Metodologie di Programmazione

**Codice**: LMP · **CFU**: 12 · **Semestre**: 1-2 · **Anno**: 2°
**SSD**: ING-INF/05
**Docenti**: Zanzotto, Stellato
**Propedeuticità**: Programmazione dei Calcolatori con Laboratorio

## Modalità d'esame

L'esame si svolge direttamente a **giugno/luglio** e non ha esoneri. È diviso in due moduli:

- **Modulo I** — Metodologie di Programmazione e Java (Zanzotto)
- **Modulo II** — Programmazione Dichiarativa e Prolog (Stellato)

---

## Argomenti del corso (Java — Modulo I)

Riferimento tassonomico degli argomenti da conoscere per padroneggiare Java. Ogni voce è un argomento autonomo, non un'attività da spuntare. L'ordine è didatticamente coerente ma pensato per consultazione non lineare.

### 1. Ecosistema e ambiente

#### 1.1 Piattaforma Java
- Java Virtual Machine (JVM)
- Java Runtime Environment (JRE)
- Java Development Kit (JDK)
- Bytecode e modello di esecuzione
- Ciclo di rilascio e versioni LTS (8, 11, 17, 21)
- Distribuzioni (OpenJDK, Temurin, Oracle JDK, GraalVM)

#### 1.2 Toolchain di base
- Compilatore `javac`
- Launcher `java`
- Jar e Jar eseguibili (`jar`)
- Classpath e module path
- `javadoc` per la documentazione generata

#### 1.3 Ambienti di sviluppo
- IntelliJ IDEA
- Eclipse
- Visual Studio Code con estensione Java
- Editor minimali (Vim, Emacs) con LSP

#### 1.4 Struttura di un progetto
- Convenzione `src/` e `out/` (o `bin/`)
- Classpath e organizzazione in package
- Module system (`module-info.java`)
- File `.iml` (IntelliJ) e `.classpath` / `.project` (Eclipse)

### 2. Sintassi fondamentale

#### 2.1 Tipi primitivi
- Interi: `byte`, `short`, `int`, `long`
- Virgola mobile: `float`, `double`
- `char`
- `boolean`
- Valori di default e intervalli numerici
- Letterali numerici (decimali, esadecimali, binari, con separatore `_`)
- Caratteri di escape

#### 2.2 Tipi di riferimento
- Concetto di reference vs valore
- `null` e suo ruolo nel sistema di tipi
- `String` come tipo speciale

#### 2.3 Variabili e costanti
- Dichiarazione e inizializzazione
- Scope (blocco, metodo, classe)
- `final` per l'immutabilità del riferimento
- `var` per l'inferenza di tipo locale (Java 10+)

#### 2.4 Operatori
- Aritmetici e di assegnamento composto (`+=`, `-=`, ...)
- Confronto e uguaglianza
- Logici booleani (`&&`, `||`, `!`)
- Bitwise e di shift
- Pre e post incremento/decremento
- Operatore ternario (`? :`)
- Precedenza e associatività

#### 2.5 Controllo di flusso
- `if` / `else if` / `else`
- `switch` statement (classico)
- `switch` expression (Java 14+)
- Pattern matching in `switch` (Java 21+)
- `while`, `do-while`
- `for` classico
- `for-each` (enhanced for)
- `break`, `continue`, label
- `return`

#### 2.6 Array
- Dichiarazione e inizializzazione
- Accesso per indice
- Proprietà `length`
- Array multidimensionali
- Array literal

### 3. Metodi e modularità procedurale

- Firma (nome, parametri, tipo di ritorno), `void` vs tipi di ritorno, parametri formali/attuali, passaggio per valore anche per i reference
- Overloading: regole di selezione della firma, ambiguità da evitare
- Varargs (`Type... args`)
- Ricorsione: casi base e ricorsivi, limiti dello stack

### 4. Classi e oggetti

- Definizione: keyword `class`, modificatori top-level, relazione tra nome del file e classe `public`
- Campi di istanza; inizializzazione inline, nel costruttore, in blocchi; modificatore `final`
- Costruttori: default, sovraccaricati, `this(...)`, `super(...)`, privati (singleton/utility)
- Metodi di istanza, `this`, getter/setter, metodi privati di supporto
- Ciclo di vita: `new`, riferimenti multipli, garbage collector (concetto), `finalize` (cenno storico)
- Metodi ereditati da `Object`: `toString`, `equals`, `hashCode` (contratto), `getClass`, `clone`

### 5. Incapsulamento e visibilità

- Modificatori: `public`, `private`, `protected`, package-private
- Campi privati con accessor pubblici, invarianti di classe, information hiding

### 6. Membri statici

- Campi statici, inizializzazione statica, blocchi `static { ... }`
- Metodi statici, utility class, `main`, limitazioni (niente `this`)
- Costanti: idioma `public static final`, naming `SCREAMING_SNAKE_CASE`

### 7. Ereditarietà

- `extends`, single inheritance tra classi, `Object` come radice
- Override: regole, `@Override`, covarianza del tipo di ritorno, visibilità
- `super.metodo(...)`, `super(...)`
- Polimorfismo: upcast implicito, dispatch dinamico, downcast esplicito, `instanceof` con pattern matching (Java 16+)
- Limiti: `final`, composition over inheritance, Liskov

### 8. Classi astratte

- `abstract class`, metodi astratti e concreti insieme
- Impossibilità di istanziare, obbligo delle sottoclassi, template method

### 9. Interfacce

- `interface`, metodi astratti impliciti, costanti `public static final`, ereditarietà multipla tra interfacce
- `implements`, implementazione multipla, combinazione con `extends`
- Evoluzione: `default`, `static`, `private` (Java 9+)
- Funzionali: `@FunctionalInterface`, SAM, lambda

### 10. Enum

- Semplici: sintassi, `values()`, `valueOf(String)`, `ordinal()`, `name()`, uso in `switch`
- Avanzati: campi, costruttori, metodi di istanza, corpo per ogni costante, interfacce

### 11. Record (Java 14+)

- Sintassi `record`, componenti e accessor generati, costruttori compatti/canonici, immutabilità strutturale, quando usarli

### 12. Sealed classes (Java 17+)

- `sealed`, `non-sealed`, `permits`, restrizione delle gerarchie, pattern matching, confronto con enum/interfacce

### 13. Gestione delle eccezioni

- Gerarchia: `Throwable` → `Error` / `Exception` → `RuntimeException`; checked vs unchecked
- Sintassi: `try`/`catch`/`finally`, `throw`, `throws`, multi-catch, try-with-resources, `AutoCloseable`
- Custom: estendere `Exception` / `RuntimeException`, costruttori standard, chaining, `serialVersionUID`
- Pratiche: quando checked vs unchecked, `getMessage`/`getCause`/`printStackTrace`, anti-pattern catch silenzioso

### 14. Generics

- Tipi parametrici: classi/interfacce/metodi generici, diamond operator
- Bounds: upper bound, wildcard `?`, `? extends T`, `? super T`, PECS
- Limitazioni: type erasure, array di tipi generici impossibili, `Class<?>` vs `Class<T>`, tipi reificabili

### 15. Collections Framework

- Interfacce: `Iterable`, `Collection`, `List`, `Set`, `SortedSet`, `NavigableSet`, `Queue`, `Deque`, `Map`, `SortedMap`, `NavigableMap`
- Implementazioni: `ArrayList`, `LinkedList`, `HashSet`, `LinkedHashSet`, `TreeSet`, `HashMap`, `LinkedHashMap`, `TreeMap`, `ArrayDeque`, `PriorityQueue`, `Collections.unmodifiable*`
- Iterazione: `Iterator`/`Iterable`, for-each, `forEach` con lambda, `ConcurrentModificationException`
- Operazioni: inserimento/rimozione/ricerca, `Map.Entry`/`entrySet`/`keySet`/`values`, `Collections.sort`, factory immutabili (`List.of`, `Map.of`)

### 16. Lambda e programmazione funzionale

- Lambda: sintassi `(params) -> expr` e `{ body }`, inferenza, variabili catturate (effectively final)
- Method reference: `Class::staticMethod`, `instance::method`, `Class::instanceMethod`, `Class::new`
- Interfacce funzionali standard: `Function`, `Predicate`, `Consumer`, `Supplier`, varianti `BiX`, `UnaryOperator`, `BinaryOperator`, varianti primitive

### 17. Stream API

- Creazione: da collezioni, `Stream.of`, `generate`, `iterate`, `Arrays.stream`, `Files.lines`
- Intermedie: `filter`, `map`, `flatMap`, `sorted`, `distinct`, `limit`, `skip`, `peek`, `mapToInt`, `boxed`
- Terminali: `forEach`/`forEachOrdered`, `collect` (`toList`, `toSet`, `toMap`, `groupingBy`, `partitioningBy`, `joining`, `counting`), `reduce`, `count`/`min`/`max`, `findFirst`/`findAny`, `anyMatch`/`allMatch`/`noneMatch`
- Primitivi: `IntStream`/`LongStream`/`DoubleStream`, operazioni statistiche
- Parallel: `parallelStream()`, quando ha senso

### 18. Optional

- Creazione: `of`, `ofNullable`, `empty`
- Ispezione: `isPresent`, `isEmpty`, `ifPresent`, `ifPresentOrElse`
- Trasformazione: `map`, `flatMap`, `filter`
- Estrazione: `orElse`, `orElseGet`, `orElseThrow`
- Quando **non** usarlo (campi, parametri di metodo)

### 19. Ordinamento e confronto

- `Comparable<T>` e `compareTo`, `Comparator<T>` e `compare`
- `Comparator.comparing`, `thenComparing`, `reversed`
- Ordinamento naturale vs esplicito, relazione con `equals`/`hashCode`

### 20. Input/Output

- Stream byte/caratteri: `InputStream`/`OutputStream`, `Reader`/`Writer`, buffered, `FileReader`/`FileWriter`, `InputStreamReader`/`OutputStreamWriter` per encoding
- File e path: `java.io.File` (legacy), `java.nio.file.Path`/`Paths`/`Files`, `Files.readAllLines`/`lines`/`writeString`, attributi/permessi
- Try-with-resources per I/O, gestione eccezioni checked
- Serializzazione: `Serializable`, `serialVersionUID`, alternative moderne (JSON, Protobuf, custom)
- Console: `Scanner`, `System.console()`, `PrintWriter`, `printf`

### 21. Reflection API

- `Class<T>`: `forName`, `.class`, `getClass`
- Introspezione: `getFields`/`getDeclaredFields`, `getMethods`/`getDeclaredMethods`, `getConstructors`/`getDeclaredConstructors`, annotazioni runtime, `setAccessible(true)`
- Istanziazione: `Constructor.newInstance`, `Method.invoke`
- Eccezioni: `ClassNotFoundException`, `NoSuchMethodException`, `NoSuchFieldException`, `InvocationTargetException`, `InstantiationException`, `IllegalAccessException`
- Casi d'uso: DI, ORM, serializzatori, plugin loading

### 22. Date e tempo

- API legacy `java.util.Date`/`Calendar` (panoramica storica)
- Moderna `java.time`: `LocalDate`/`LocalTime`/`LocalDateTime`, `ZonedDateTime`/`OffsetDateTime`, `Instant`/`Duration`/`Period`, `DateTimeFormatter`, `ChronoUnit`

### 23. Stringhe

- `String`: immutabilità, metodi principali (`length`, `charAt`, `substring`, `split`, `trim`/`strip`, `replace`, `indexOf`, `contains`, `equals`, `equalsIgnoreCase`, `startsWith`, `endsWith`), `compareTo`, pool e `intern()`
- Costruzione: `StringBuilder`, `StringBuffer`, `String.format`/`printf`, text block (Java 15+)
- Conversioni: `parseInt`/`parseDouble`, `String.valueOf`, autoboxing

### 24. Concorrenza — introduzione

- Thread: `Thread`/`Runnable`, ciclo di vita, `start` vs `run`, `join`/`sleep`/`interrupt`
- Sincronizzazione: `synchronized`, `volatile`, atomic (`AtomicInteger`, `AtomicReference`), deadlock/livelock/starvation
- Executor: `Executor`/`ExecutorService`, `Future`/`Callable`, `CompletableFuture`, thread pool
- Virtual threads (Java 21+)

### 25. Java Platform Module System

- `module-info.java`, direttive `exports`/`requires`/`opens`/`uses`/`provides`
- Moduli nominati, automatici, unnamed
- Encapsulamento forte tra moduli
- Quando adottarlo e quando no

### 26. Design e pratiche

- Principi: SOLID, DRY, KISS, YAGNI, composition over inheritance, immutabilità come default
- Pattern ricorrenti: Factory method, Abstract factory, Builder, Singleton, Strategy, Observer, Template method, Decorator, Adapter
- Convenzioni: naming (PascalCase/camelCase/SCREAMING_SNAKE_CASE/package minuscoli con dominio invertito), package per feature o layer, convenzione `Interface`/`Impl`, Javadoc

### 27. Testing

- JUnit 5: `@Test`, `@BeforeEach`/`@AfterEach`/`@BeforeAll`/`@AfterAll`, assertions (`assertEquals`, `assertThrows`, `assertAll`), `@ParameterizedTest`, lifecycle
- Pratiche: Arrange-Act-Assert, unitari vs integrazione vs end-to-end, Mockito (cenno), coverage e sue insidie

### 28. Build tool e dipendenze

- Maven: ciclo di vita, `pom.xml`, dipendenze/scope/versioning, repository centrale
- Gradle: `build.gradle`/`.kts`, task e plugin, wrapper (`gradlew`)
- Librerie comuni: SLF4J, Guava, Apache Commons, Jackson; gestione versioni

### 29. Logging

- `java.util.logging` (cenno), SLF4J come API di facciata, Logback e Log4j2 come implementazioni
- Livelli: TRACE, DEBUG, INFO, WARN, ERROR
- Buone pratiche: niente `System.out` in produzione

### 30. Argomenti avanzati e ponte verso l'ecosistema

- Annotazioni custom e processing
- Proxy dinamici (`java.lang.reflect.Proxy`)
- Classloader
- JNI (cenno)
- Foreign Function & Memory API (Java 21+, cenno)
- Jshell (REPL ufficiale)
- JPMS e applicazioni modulari reali
- Introduzione ai framework (Spring, Jakarta EE, Quarkus) come destinazione naturale dopo Java core

---

## Come studiare (dal zero al progetto di sintesi)

Guida pensata per chi parte da zero e vuole arrivare al livello degli esercizi del corso senza salti logici.

### Struttura della guida

La guida è divisa in **dodici fasi progressive**. Ogni fase ha:
- **Obiettivo** — cosa saprai fare alla fine
- **Teoria** — concetti da comprendere prima del codice
- **Tracce di esercizio** — problemi concreti da risolvere (fanne almeno due per fase)
- **Auto-verifica** — domande cui rispondere senza IDE
- **Errori comuni** — trappole
- **Consiglio** — suggerimento di metodo

**Regola d'oro**: non passare alla fase successiva finché non hai scritto tu, da zero, almeno un programma che compila ed esegue per quella fase. Leggere non è studiare.

### Prima di iniziare

**Prerequisiti**: computer con Linux/macOS/Windows, terminale, zero Java richiesto.

**Ambiente**:
1. Installa **JDK 21** (Temurin o OpenJDK). Verifica con `java -version` e `javac -version`.
2. Installa **IntelliJ IDEA Community Edition**.
3. In IntelliJ: `File → New Project → Java → Project SDK = 21`, nessun build tool.
4. Verifica che un `Hello World` compili ed esegua.

**Mentalità**: Java è verboso. All'inizio ti sembrerà di scrivere molto codice per fare poco: è normale. La verbosità porta il **type system**, che ti protegge da un'intera classe di errori. Impara a leggere i messaggi del compilatore: sono il tuo tutor personale.

---

### Fase 1 — Primi passi nel linguaggio

**Obiettivo**: scrivere programmi procedurali semplici con variabili, condizioni, cicli e metodi.

**Teoria**: struttura di un file `.java` e `main`, tipi primitivi e `String`, variabili e `final`, operatori, `if`/`else`/`switch`, `while`/`for`, array monodimensionali, metodi `static`.

**Tracce**:
1. **Calcolatrice da riga di comando.** Due numeri + operatore da `args[]`, gestione divisione per zero.
2. **FizzBuzz.** 1-100, "Fizz"/"Buzz"/"FizzBuzz".
3. **Statistiche array.** Min, max, media, pari.
4. **Indovina il numero.** Casuale 1-100, 7 tentativi, `Scanner`.

**Auto-verifica**: differenza `int`/`Integer`? Perché `"abc" == "abc"` può funzionare ma `new String("abc") == new String("abc")` no? Cosa stampa `System.out.println(3 / 2)`? A cosa serve `static` in `main`?

**Errori comuni**: confronto stringhe con `==`, divisione intera tronca, off-by-one.

**Consiglio**: quando il compilatore ti urla, **leggi il messaggio per intero** prima di cercare su Google.

### Fase 2 — Dal procedurale all'oggetto

**Obiettivo**: capire classe/oggetto, modellare un concetto reale come classe.

**Teoria**: classe vs istanza vs oggetto, campi/metodi, costruttori, `this`, `public`/`private`, incapsulamento, getter/setter, override di `toString()`, `package`.

**Tracce**: `Libro` (titolo/autore/anno/pagine, toString), `Rettangolo` (area/perimetro/isQuadrato), `ContoCorrente` (deposita/preleva con controllo saldo).

**Auto-verifica**: perché campi `private`? Cosa succede senza costruttore? Differenza classe/oggetto? Cosa fa `this.nome = nome`?

**Errori comuni**: campi `public`, dimenticare inizializzazione, non fare `new`.

**Consiglio**: prima di scrivere codice, **disegna la classe su carta**.

### Fase 3 — Contratti: le interfacce

**Obiettivo**: separare *cosa* un oggetto sa fare (interfaccia) da *come* lo fa (implementazione).

**Teoria**: `interface`, `implements`, convenzione `Foo`/`FooImpl`, dichiarare per interfaccia (`Forma f = new Cerchio(...)`).

**Tracce**: `Forma` con `area/perimetro` implementata da `Cerchio`/`Rettangolo`/`TriangoloRettangolo`; `Animale` con `nome/verso`; `Descrivibile` implementata da classi diverse (`Libro`, `Automobile`).

**Auto-verifica**: puoi istanziare un'interfaccia? Vantaggio di dichiarare per interfaccia? Più interfacce? Più classi estese?

**Errori comuni**: `public` ridondante, dimenticare `implements`, logica nei metodi dell'interfaccia.

**Consiglio**: se una classe potrebbe avere varianti, estrai un'interfaccia prima di continuare.

### Fase 4 — Ereditarietà e polimorfismo

**Obiettivo**: costruire gerarchie dove le sottoclassi riutilizzano ed estendono.

**Teoria**: `extends`, `super(...)`/`super.metodo()`, override e `@Override`, polimorfismo e dispatch dinamico, overloading vs overriding.

**Tracce**: `Dipendente` → `Manager`/`Operaio` con `stipendioMensile()` ridefinito; `Veicolo` → `Auto`/`Moto`/`Camion`; `Studente` → `StudenteArrabbiato`.

**Auto-verifica**: overloading vs overriding? Cosa fa `super(nome)`? Con `Dipendente d = new Manager(...)` quale metodo si esegue? Perché `@Override` è utile?

**Errori comuni**: dimenticare `super(...)`, credere che si esegua il metodo del tipo dichiarato, rompere il principio di sostituzione.

**Consiglio**: usa sempre `@Override`. Se il compilatore si lamenta, hai sbagliato la firma.

### Fase 5 — Classi astratte e membri statici

**Obiettivo**: gerarchia dove la base impone struttura ma lascia alle sottoclassi i dettagli.

**Teoria**: `abstract class`, metodi `abstract`, `protected`, campi/metodi `static`, contatori statici, differenza `abstract class` vs `interface`.

**Tracce**: `Account` astratto con `calcolaInteresse()` implementato da `ContoRisparmio`/`ContoCorrente`; `Utente` con contatore statico; figure geometriche v2 con classe astratta.

**Auto-verifica**: quando classe astratta vs interfaccia? Puoi fare `new` di una astratta? A chi appartiene un `static`? Un metodo `static` può usare `this`?

**Errori comuni**: `static` dove andrebbe istanza (e viceversa), classe astratta usata solo per bloccare l'istanziazione (anti-pattern), mischiare `static` ed ereditarietà.

**Consiglio**: se una classe astratta non ha campi né metodi concreti, probabilmente volevi un'interfaccia.

### Fase 6 — Enum

**Obiettivo**: modellare insiemi chiusi di valori in modo type-safe.

**Teoria**: enum semplici, enum con campi/costruttore/metodi, `values()`/`valueOf`/`ordinal`/`name`, enum che implementano interfacce.

**Tracce**: `Giorno` con `isWeekend()`; `StatoOrdine` con `puoEssereAnnullato()`; `Pianeta` con `gravitaSuperficie()`.

**Auto-verifica**: `==` o `.equals()` per enum? `MyEnum.valueOf("NON_ESISTE")`? Metodi su enum?

**Errori comuni**: costanti `int` al posto di enum, dimenticare `;` dopo l'ultimo valore con campi/metodi, modificare stato di un enum.

**Consiglio**: ogni volta che scrivi `if (s.equals("APERTO") || s.equals("CHIUSO"))`, fermati: quello è un enum.

### Fase 7 — Eccezioni

**Obiettivo**: gestire errori in modo pulito con tipi dedicati.

**Teoria**: gerarchia `Throwable` → `Error`/`Exception` → `RuntimeException`, checked vs unchecked, `try`/`catch`/`finally`, `throw` vs `throws`, multi-catch, eccezioni custom, exception chaining, try-with-resources (cenno).

**Tracce**: `ContoCorrente` v2 con `SaldoInsufficienteException` (checked) e `ImportoNegativoException` (unchecked); `registraUtente` con `EtaNonValidaException`; parser di numeri con `ParseNumeriException` che incapsula `NumberFormatException`.

**Auto-verifica**: checked vs unchecked? Se non catturi una checked? Anti-pattern del `catch (Exception e)` silenzioso? Causa nel costruttore dell'eccezione?

**Errori comuni**: catturare `Exception` e non fare nulla, eccezioni per controllo di flusso, gerarchie troppo profonde.

**Consiglio**: un'eccezione lanciata va sempre **gestita** o **propagata**. Mai nascosta.

### Fase 8 — Collections e Generics

**Obiettivo**: usare le strutture dati standard di Java in modo type-safe.

**Teoria**: `Collection`/`List`/`Set`/`Map`, `ArrayList`/`HashMap`/`HashSet`, generics `<T>` e diamond operator, for-each, `add`/`get`/`remove`/`contains`/`size`, `Map.Entry`/`entrySet`/`keySet`/`values`.

**Tracce**: Rubrica telefonica; Conteggio parole; Magazzino con scarico e prodotti esauriti; Università v2 con `Map<String, Studente>` per matricola.

**Auto-verifica**: `List` vs `Set`? Perché `HashMap` richiede `hashCode` buono? Type erasure a runtime? Iterare le entry di una `Map`?

**Errori comuni**: `List<Object>` invece di `List<Tipo>`, modificare collection mentre la iteri (`ConcurrentModificationException`), chiavi con `==`.

**Consiglio**: **dichiara per interfaccia, istanzia per implementazione**. Cioè `List<String> l = new ArrayList<>();`.

### Fase 9 — I/O su file

**Obiettivo**: leggere/scrivere file di testo, parsarli in strutture dati.

**Teoria**: `File`/`FileReader`/`BufferedReader`, lettura riga per riga, try-with-resources, manipolazione stringhe (`split`/`trim`/`toUpperCase`), `Integer.parseInt`/`NumberFormatException`, alternativa `java.nio.file.Files`.

**Tracce**: Config reader (chiave=valore, ignora vuoti e commenti `#`); CSV semplice con `CsvParseException`; Log filter con conteggi `INFO`/`WARN`/`ERROR`.

**Auto-verifica**: `BufferedReader` vs `FileReader`? Try-with-resources? Perché `readLine()` ritorna `null`? `java.io` vs `java.nio.file`?

**Errori comuni**: non chiudere il file, ignorare `FileNotFoundException`, `split` con separatore nel valore.

**Consiglio**: il bug più comune dei parser è non considerare input rotto. Chiediti cosa succede se manca una riga, c'è un carattere strano, il file è vuoto.

### Fase 10 — Reflection

**Obiettivo**: capire l'introspezione a runtime e quando è utile.

**Teoria**: `Class<?>` e `Class.forName`, `.class`, `getDeclaredConstructors`/`Fields`/`Methods`, `Constructor.newInstance(...)`, eccezioni (`ClassNotFoundException`, `InvocationTargetException`, `InstantiationException`, `IllegalAccessException`).

**Tracce**: Plugin factory (istanziazione da nome classe); Stampatore generico che elenca i campi di un oggetto via reflection.

**Auto-verifica**: perché è lenta? Cosa rompe della type safety? Casi d'uso reali? `getDeclaredConstructors` vs `getConstructors`?

**Errori comuni**: reflection quando basta il polimorfismo, ignorare la cascata di eccezioni, assumere un ordine specifico degli array restituiti.

**Consiglio**: reflection è l'**ultima spiaggia**, non la prima scelta.

### Fase 11 — Progetto di sintesi

**Obiettivo**: mettere insieme tutto. Nessuna teoria nuova, solo integrazione.

**Traccia: gestionale biblioteca da riga di comando**

Input `libri.txt` con blocchi separati da `---`:
```
tipo:cartaceo
titolo:Il nome della rosa
autore:Umberto Eco
anno:1980
copie:3
---
tipo:ebook
titolo:1984
autore:George Orwell
anno:1949
formato:epub
---
```

Classe astratta `Libro`, sottoclassi `LibroCartaceo` e `LibroDigitale`; enum `Genere` (opzionale); `Biblioteca` con `Map<String, Libro>` e metodi `presta`/`restituisci`/`cercaPerAutore`/`libriDisponibili`; eccezioni custom `LibroNonTrovatoException`/`LibroNonDisponibileException`/`FormatoFileException`; factory basata su `tipo:`; `Main` con loop interattivo (`presta`/`restituisci`/`cerca`/`lista`/`esci`).

**Obiettivo pedagogico**: nel codice finale deve esserci evidenza di ereditarietà e classe astratta, enum, collections + generics, eccezioni custom, I/O da file, incapsulamento corretto, separazione in package (`model`, `io`, `app`).

**Consiglio**: non scrivere tutto di filato. Parti dalla classe `Libro`, poi `Biblioteca` con due libri hardcoded, poi file reader, poi loop interattivo, poi eccezioni, poi raffina. Una feature alla volta, compilando e testando ad ogni passo.

### Fase 12 — Java moderno

**Obiettivo**: conoscere le feature post-Java-8 che nel corso non sono usate ma che trovi ovunque.

**Argomenti**: `var`, `record`, text block, `switch` expression e pattern matching, sealed classes, lambda/method reference, Stream API (`filter`/`map`/`collect`/`reduce`), `Optional`, try-with-resources idiomatico, `java.time`.

**Traccia**: rifai l'esercizio Università con `record` invece di classe, Stream API per `getStudentiByCognome`, `Optional` per `getStudente(matricola)`, `var` dove ha senso. Confronta le due versioni.

---

## Metodo di studio generale

1. **Un argomento per sessione.** Non mischiare.
2. **Leggi, poi scrivi.** Minimo 15 minuti di lettura, minimo 1 ora di codice.
3. **Spiega a voce alta.** Se non sai raccontare un concetto a un amico, non l'hai ancora capito.
4. **Diario di debugging.** Ogni errore che risolvi, una riga su *cosa era* e *come l'hai capito*.
5. **Non copiare codice: riscrivilo.** Chiudi la soluzione trovata e riproducila a memoria.
6. **Usa Git** anche solo localmente: un commit per esercizio.
7. **Pause vere.** Dopo 90 minuti, 15 minuti lontano dallo schermo.

## Risorse

- **Documentazione API Java 21** — <https://docs.oracle.com/en/java/javase/21/docs/api/>
- **Java Tutorial (Oracle)** — <https://docs.oracle.com/javase/tutorial/>
- **Baeldung** — <https://www.baeldung.com/>
- **Effective Java** di Joshua Bloch. Da leggere dopo la Fase 11, prima della 12.

## In caso di blocco

1. Stampa lo stato con `System.out.println` per ispezionare le variabili.
2. Leggi il messaggio d'errore **una riga alla volta**, dall'alto.
3. Scrivi a parole cosa vuoi ottenere *in quel punto esatto*.
4. Solo dopo aver fatto 1-3, cerca o chiedi.
5. Se la soluzione funziona ma non capisci perché, **fermati** e indaga prima di andare avanti.
