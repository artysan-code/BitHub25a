
/*
 * ============================================================
 * PROBLEMA LETTORI - SCRITTORI CON SEMAFORI POSIX
 * ============================================================
 *
 * Autore: Danilo Croce
 * Corso: SOR - Sistemi Operativi e Reti
 *
 * COSA FA QUESTO PROGRAMMA?
 *
 * Il programma crea:
 *
 * - 3 thread LETTORI
 * - 1 thread SCRITTORE
 *
 * Tutti condividono un dato che rappresenta un database.
 *
 * I LETTORI possono leggere contemporaneamente.
 *
 * Lo SCRITTORE deve invece accedere al database
 * in modo esclusivo:
 *
 * - mentre scrive, nessuno può leggere;
 * - mentre uno o più lettori leggono, non può scrivere.
 *
 * ------------------------------------------------------------
 * COME FUNZIONA LA SINCRONIZZAZIONE?
 *
 * Utilizziamo DUE semafori:
 *
 * mutex = protegge la variabile condivisa rc,
 *         che conta i lettori attivi.
 *
 * db    = protegge l'accesso al database.
 *         È acquisito dallo scrittore oppure,
 *         collettivamente, dai lettori.
 *
 * La variabile rc conta quanti lettori stanno
 * attualmente accedendo al database.
 *
 * Il PRIMO lettore acquisisce db.
 * I lettori successivi possono leggere senza acquisirlo.
 * L'ULTIMO lettore rilascia db.
 *
 * Lo scrittore acquisisce direttamente db e lo
 * rilascia quando ha terminato la scrittura.
 *
 * ------------------------------------------------------------
 * PERCHE' ABBIAMO DEFINITO down() E up()?
 *
 * Nelle slide utilizziamo le operazioni astratte:
 *
 *     down(semaforo)
 *     up(semaforo)
 *
 * Le corrispondenti operazioni POSIX sono:
 *
 *     sem_wait()  -> down()
 *     sem_post()  -> up()
 *
 * Le funzioni down() e up() sono semplici wrapper:
 * richiamano le funzioni POSIX già disponibili.
 *
 * NON stiamo implementando i semafori da zero.
 * Utilizziamo i semafori messi a disposizione
 * dal sistema operativo.
 *
 * ------------------------------------------------------------
 * ATTENZIONE: NON ESEGUIRE SU MAC OS X / macOS!
 *
 * Questo programma utilizza sem_init() per creare
 * semafori POSIX anonimi.
 *
 * macOS non supporta sem_init() per questi semafori:
 * il programma non può funzionare così com'è.
 *
 * ESEGUIRE SU LINUX.
 *
 * Compilazione:
 *
 * gcc -Wall -Wextra -pthread \
 *     6.3_reader_writer_semaphore.c \
 *     -o 6.3_reader_writer_semaphore
 *
 * Esecuzione:
 *
 * ./6.3_reader_writer_semaphore
 *
 * ------------------------------------------------------------
 * LIMITAZIONE DELL'ALGORITMO
 *
 * Questa è la soluzione classica con PREFERENZA
 * PER I LETTORI.
 *
 * Se continuano ad arrivare nuovi lettori,
 * uno scrittore potrebbe aspettare indefinitamente.
 *
 * Questo problema prende il nome di STARVATION.
 *
 * ============================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_OPERATIONS 5


// ============================================================
// VARIABILI CONDIVISE
// ============================================================

// Semaforo che protegge il contatore rc.
sem_t mutex;

// Semaforo che protegge l'accesso al database.
sem_t db;

// Numero di lettori attualmente attivi.
int rc = 0;

// Dato condiviso che simula il database.
//
// Soltanto lo scrittore lo modifica.
// I lettori si limitano a leggerlo.
int database = 0;


// ============================================================
// OPERAZIONI DOWN E UP
// ============================================================

/*
 * down() corrisponde a sem_wait().
 *
 * Se il semaforo è disponibile, il thread prosegue.
 * Altrimenti si blocca fino a quando una disponibilità
 * non viene resa disponibile.
 */
void down(sem_t *sem)
{
    if (sem_wait(sem) == -1) {
        perror("Errore in sem_wait");
        exit(EXIT_FAILURE);
    }
}

/*
 * up() corrisponde a sem_post().
 *
 * Rende disponibile una risorsa e può permettere
 * a un thread in attesa di riprendere l'esecuzione.
 */
void up(sem_t *sem)
{
    if (sem_post(sem) == -1) {
        perror("Errore in sem_post");
        exit(EXIT_FAILURE);
    }
}


// ============================================================
// OPERAZIONI SUL DATABASE
// ============================================================

/*
 * Simula una lettura dal database.
 *
 * id identifica il lettore che sta eseguendo
 * questa operazione.
 *
 * ATTENZIONE:
 * più lettori possono eseguire questa funzione
 * contemporaneamente.
 */
void read_database(int id)
{
    printf("LETTORE %d: legge il valore %d\n",
       id, database);

    // Simula una lettura che richiede tempo.
    sleep(1);

    printf("LETTORE %d: lettura completata\n", id);
}

/*
 * Simula una scrittura nel database.
 *
 * Lo scrittore modifica il dato condiviso.
 *
 * Durante questa operazione nessun altro thread
 * può leggere o scrivere il database.
 */
void write_database(void)
{
    database++;

    printf("\nSCRITTORE: scrive il valore %d\n\n",
           database);

    // Simula una scrittura che richiede tempo.
    sleep(1);
}

/*
 * Simula l'elaborazione dei dati già letti.
 *
 * Questa funzione viene eseguita FUORI
 * dalla regione di lettura protetta da db.
 *
 * Il lettore non ha più bisogno di accedere
 * al database condiviso.
 */
void use_data_read(int id)
{
    printf("LETTORE %d: utilizza i dati letti\n", id);

    sleep(1);
}

/*
 * Simula la preparazione di nuovi dati da scrivere.
 *
 * Lo scrittore non ha ancora bisogno
 * dell'accesso esclusivo al database.
 */
void think_up_data(void)
{
    printf("SCRITTORE: prepara nuovi dati\n");

    sleep(1);
}


// ============================================================
// THREAD LETTORE
// ============================================================

void *reader(void *arg)
{
    // Il main ha passato l'indirizzo di un intero
    // che identifica questo lettore.
    int id = *(int *)arg;

    for (int i = 0; i < NUM_OPERATIONS; i++) {

        /*
         * 1. PROTEGGE LA VARIABILE rc
         *
         * Più lettori potrebbero tentare di
         * modificare rc contemporaneamente.
         *
         * L'incremento rc++ NON è un'operazione
         * automaticamente atomica.
         */
        down(&mutex);

        // Un lettore in più vuole accedere al database.
        rc++;

        /*
         * 2. IL PRIMO LETTORE BLOCCA GLI SCRITTORI
         *
         * Se rc == 1, significa che questo
         * è il primo lettore.
         *
         * Acquisisce db per impedire allo
         * scrittore di accedere al database.
         *
         * Se lo scrittore sta già scrivendo,
         * il primo lettore aspetta qui.
         *
         * I lettori successivi non devono
         * eseguire down(&db), perché il primo
         * ha già acquisito db per tutti.
         */
        if (rc == 1) {
            down(&db);
        }

        // Rilascia l'accesso esclusivo a rc.
        up(&mutex);

        // =========================================
        // REGIONE DI LETTURA DEL DATABASE
        // =========================================

        /*
         * Più lettori possono trovarsi qui
         * nello stesso momento.
         *
         * Lo scrittore NON può accedere
         * perché il semaforo db è occupato.
         */
        read_database(id);

        // =========================================
        // FINE REGIONE DI LETTURA
        // =========================================

        /*
         * 3. IL LETTORE TERMINA LA LETTURA
         *
         * Proteggiamo di nuovo rc prima
         * di modificarlo.
         */
        down(&mutex);

        // Un lettore in meno.
        rc--;

        /*
         * 4. L'ULTIMO LETTORE LIBERA IL DATABASE
         *
         * Se rc == 0, significa che non
         * ci sono più lettori attivi.
         *
         * Lo scrittore può quindi acquisire db.
         */
        if (rc == 0) {
            up(&db);
        }

        // Libera la variabile rc.
        up(&mutex);

        /*
         * 5. UTILIZZO DEI DATI LETTI
         *
         * Il lettore lavora sui dati senza
         * mantenere occupato il database.
         *
         * Lo scrittore e gli altri lettori
         * possono quindi proseguire.
         */
        use_data_read(id);
    }

    return NULL;
}


// ============================================================
// THREAD SCRITTORE
// ============================================================

void *writer(void *arg)
{
    (void)arg; // Non utilizziamo l'argomento.

    for (int i = 0; i < NUM_OPERATIONS; i++) {

        /*
         * 1. PREPARAZIONE DEI DATI
         *
         * Avviene fuori dalla regione critica.
         * Non serve impedire agli altri thread
         * di accedere al database.
         */
        think_up_data();

        /*
         * 2. ACCESSO ESCLUSIVO AL DATABASE
         *
         * Lo scrittore deve attendere se:
         *
         * - un altro scrittore sta scrivendo;
         * - uno o più lettori stanno leggendo.
         */
        down(&db);

        // -------- INIZIO REGIONE CRITICA --------

        write_database();

        // -------- FINE REGIONE CRITICA --------

        /*
         * 3. RILASCIO DEL DATABASE
         *
         * Dopo la scrittura, altri thread
         * possono accedere al database.
         */
        up(&db);
    }

    return NULL;
}


// ============================================================
// PROGRAMMA PRINCIPALE
// ============================================================

int main(void)
{
    // Array degli identificatori dei thread lettori.
    pthread_t readers[NUM_READERS];

    // Identificativo del thread scrittore.
    pthread_t writer_thread;

    // Identificatori numerici assegnati ai lettori.
    // Ogni thread riceve l'indirizzo di un elemento distinto.
    int ids[NUM_READERS];

    /*
     * INIZIALIZZAZIONE DEI SEMAFORI
     *
     * sem_init(&semaforo, pshared, valore_iniziale)
     *
     * pshared = 0:
     * semaforo condiviso tra thread dello stesso processo.
     */

    // mutex = 1: inizialmente rc può essere modificato.
    if (sem_init(&mutex, 0, 1) == -1) {
        perror("Errore sem_init mutex");
        return EXIT_FAILURE;
    }

    // db = 1: inizialmente il database è libero.
    if (sem_init(&db, 0, 1) == -1) {
        perror("Errore sem_init db");
        return EXIT_FAILURE;
    }

    // =========================================
    // CREAZIONE DEI THREAD LETTORI
    // =========================================

    for (int i = 0; i < NUM_READERS; i++) {

        ids[i] = i + 1;

        // Ogni lettore esegue la stessa funzione,
        // ma riceve un identificatore differente.
        if (pthread_create(&readers[i], NULL,
                           reader, &ids[i]) != 0) {
            fprintf(stderr,
                    "Errore creazione lettore %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // =========================================
    // CREAZIONE DEL THREAD SCRITTORE
    // =========================================

    if (pthread_create(&writer_thread, NULL,
                       writer, NULL) != 0) {
        fprintf(stderr, "Errore creazione scrittore\n");
        exit(EXIT_FAILURE);
    }

    // =========================================
    // ATTESA DELLA TERMINAZIONE
    // =========================================

    /*
     * Il main attende tutti i lettori.
     *
     * pthread_join() non sincronizza l'accesso
     * al database: attende soltanto che il
     * thread indicato abbia terminato.
     */
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Attende anche lo scrittore.
    pthread_join(writer_thread, NULL);

    // =========================================
    // DISTRUZIONE DEI SEMAFORI
    // =========================================

    sem_destroy(&mutex);
    sem_destroy(&db);

    printf("\nTutti i thread hanno terminato.\n");
    printf("Valore finale del database: %d\n", database);

    return 0;
}
