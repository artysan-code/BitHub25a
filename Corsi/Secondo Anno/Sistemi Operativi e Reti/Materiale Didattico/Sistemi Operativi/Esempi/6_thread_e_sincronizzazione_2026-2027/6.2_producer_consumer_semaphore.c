
/*
 * ============================================================
 * PRODUTTORE - CONSUMATORE CON SEMAFORI POSIX
 * ============================================================
 *
 * Autore: Danilo Croce
 * Corso: SOR - Sistemi Operativi e Reti
 *
 * COSA FA QUESTO PROGRAMMA?
 *
 * Il programma crea due thread:
 *
 * 1. PRODUTTORE:
 *    genera numeri casuali e li inserisce in un buffer.
 *
 * 2. CONSUMATORE:
 *    preleva i numeri dal buffer e li consuma.
 *
 * I due thread condividono un buffer di N posizioni.
 *
 * Il buffer è una CODA CIRCOLARE (FIFO):
 * il primo elemento inserito è il primo a essere prelevato.
 *
 * Il produttore e il consumatore NON devono necessariamente
 * alternarsi: il produttore può inserire più elementi prima
 * che il consumatore ne prelevi uno.
 *
 * Per coordinare i thread utilizziamo TRE SEMAFORI:
 *
 * mutex = garantisce la mutua esclusione durante
 *         l'accesso alle variabili condivise.
 *
 * empty = conta i posti LIBERI nel buffer.
 *         Se il buffer è pieno, il produttore aspetta.
 *
 * full  = conta gli elementi PRESENTI nel buffer.
 *         Se il buffer è vuoto, il consumatore aspetta.
 *
 * ------------------------------------------------------------
 * PERCHE' USIAMO down() E up()?
 *
 * Nelle slide abbiamo studiato le operazioni astratte:
 *
 *     down(semaforo)
 *     up(semaforo)
 *
 * In C, con le API POSIX, le operazioni corrispondenti sono:
 *
 *     sem_wait()  -> down()
 *     sem_post()  -> up()
 *
 * Abbiamo quindi definito due semplici funzioni, down() e up(),
 * che chiamano rispettivamente sem_wait() e sem_post().
 *
 * In questo modo il codice rimane identico, nella logica,
 * allo pseudocodice mostrato a lezione.
 *
 * Non stiamo implementando i semafori da zero:
 * stiamo utilizzando i semafori POSIX.
 *
 * ------------------------------------------------------------
 * ATTENZIONE: NON ESEGUIRE QUESTO ESEMPIO SU MAC OS X / macOS!
 *
 * Questo programma utilizza sem_init(), che non è supportata
 * da macOS per creare semafori POSIX anonimi.
 *
 * Su macOS sem_init() fallisce: il programma non può
 * funzionare correttamente utilizzando questa implementazione.
 *
 * UTILIZZARE LINUX!
 *
 * Compilazione:
 *
 * gcc -Wall -Wextra -pthread \
 *     6.2_producer_consumer_semaphore.c \
 *     -o 6.2_producer_consumer_semaphore
 *
 * Esecuzione:
 *
 * ./6.2_producer_consumer_semaphore
 *
 * ============================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 10          // Numero di posti nel buffer
#define MAX_ITEMS 20  // Numero totale di elementi prodotti


// ============================================================
// VARIABILI CONDIVISE TRA I THREAD
// ============================================================

// Semafori per la sincronizzazione.
sem_t mutex;
sem_t empty;
sem_t full;

// Buffer condiviso tra produttore e consumatore.
int buffer[N];

// Prossima posizione in cui il produttore inserirà un elemento.
int in = 0;

// Prossima posizione da cui il consumatore preleverà un elemento.
int out = 0;

// Numero di elementi attualmente presenti nel buffer.
int count = 0;


// ============================================================
// OPERAZIONI DOWN E UP
// ============================================================

/*
 * down() corrisponde a sem_wait().
 *
 * Se il semaforo ha valore maggiore di 0:
 * - viene decrementato;
 * - il thread può proseguire.
 *
 * Se il valore è 0:
 * - il thread viene bloccato in attesa.
 *
 * L'operazione è atomica: non dobbiamo implementare
 * noi la mutua esclusione sull'aggiornamento del semaforo.
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
 * Segnala una nuova disponibilità.
 *
 * Se ci sono thread bloccati sul semaforo,
 * uno di essi potrà proseguire.
 */
void up(sem_t *sem)
{
    if (sem_post(sem) == -1) {
        perror("Errore in sem_post");
        exit(EXIT_FAILURE);
    }
}


// ============================================================
// OPERAZIONI SUL BUFFER
// ============================================================

/*
 * Inserisce un elemento nella coda.
 *
 * ATTENZIONE:
 * questa funzione deve essere chiamata solo dopo
 * aver acquisito un posto libero e il mutex.
 */
void insert_item(void)
{
    // Il produttore genera un numero casuale.
    int item = rand() % 100;

    // Inserisce l'elemento nella prossima posizione libera.
    buffer[in] = item;

    printf("PRODUTTORE: inserisco %d in posizione %d\n",
           item, in);

    /*
     * Avanza l'indice in.
     *
     * L'operatore % N permette di realizzare
     * una CODA CIRCOLARE:
     *
     * 0, 1, 2, ... 9, 0, 1, ...
     *
     * Quando arriviamo all'ultima posizione,
     * ricominciamo dalla prima.
     */
    in = (in + 1) % N;

    // Un elemento in più nel buffer.
    count++;
}

/*
 * Preleva un elemento dalla coda.
 *
 * ATTENZIONE:
 * questa funzione deve essere chiamata solo dopo
 * aver acquisito un elemento disponibile e il mutex.
 */
void remove_item(void)
{
    // Preleva l'elemento più vecchio.
    int item = buffer[out];

    printf("CONSUMATORE: prelevo %d dalla posizione %d\n",
           item, out);

    // Avanza l'indice, tornando a 0 dopo N-1.
    out = (out + 1) % N;

    // Un elemento in meno nel buffer.
    count--;
}

/*
 * Stampa il contenuto del buffer.
 *
 * Gli elementi sono mostrati nell'ordine in cui
 * verranno consumati, dal più vecchio al più recente.
 *
 * Questa funzione viene chiamata nella regione critica,
 * così nessun altro thread modifica il buffer
 * mentre lo stiamo stampando.
 */
void print_buffer(void)
{
    printf("BUFFER (%d/%d): [ ", count, N);

    for (int i = 0; i < count; i++) {
        int pos = (out + i) % N;
        printf("%d ", buffer[pos]);
    }

    printf("]\n\n");
}


// ============================================================
// THREAD PRODUTTORE
// ============================================================

void *producer(void *arg)
{
    (void)arg; // Non utilizziamo l'argomento del thread.

    for (int i = 0; i < MAX_ITEMS; i++) {

        /*
         * 1. ATTENDE UN POSTO LIBERO
         *
         * Il semaforo empty conta i posti liberi.
         *
         * Se il buffer è pieno, empty vale 0
         * e il produttore viene bloccato.
         *
         * E' importante fare questa operazione
         * PRIMA di acquisire mutex.
         */
        down(&empty);

        /*
         * 2. ENTRA NELLA REGIONE CRITICA
         *
         * Il produttore acquisisce l'accesso esclusivo
         * alle variabili condivise.
         */
        down(&mutex);

        // -------- INIZIO REGIONE CRITICA --------

        insert_item();

        print_buffer();

        // -------- FINE REGIONE CRITICA --------

        /*
         * 3. ESCE DALLA REGIONE CRITICA
         *
         * Il consumatore può ora accedere al buffer.
         */
        up(&mutex);

        /*
         * 4. SEGNALA UN NUOVO ELEMENTO
         *
         * Incrementa full perché abbiamo prodotto
         * un nuovo elemento disponibile.
         *
         * Se il consumatore era bloccato su full,
         * potrà essere risvegliato.
         */
        up(&full);

        /*
         * Piccola pausa per simulare la produzione.
         *
         * Il produttore è più veloce del consumatore.
         * In questo modo possiamo osservare il buffer
         * che si riempie progressivamente.
         *
         * La pausa è FUORI dalla regione critica.
         */
        usleep(100000);  // 100 millisecondi
    }

    return NULL;
}


// ============================================================
// THREAD CONSUMATORE
// ============================================================

void *consumer(void *arg)
{
    (void)arg; // Non utilizziamo l'argomento del thread.

    for (int i = 0; i < MAX_ITEMS; i++) {

        /*
         * 1. ATTENDE UN ELEMENTO DISPONIBILE
         *
         * Il semaforo full conta gli elementi presenti.
         *
         * Se il buffer è vuoto, full vale 0
         * e il consumatore viene bloccato.
         *
         * Aspetta senza occupare continuamente la CPU.
         */
        down(&full);

        /*
         * 2. ENTRA NELLA REGIONE CRITICA
         *
         * Il consumatore acquisisce l'accesso esclusivo
         * al buffer.
         */
        down(&mutex);

        // -------- INIZIO REGIONE CRITICA --------

        remove_item();

        print_buffer();

        // -------- FINE REGIONE CRITICA --------

        /*
         * 3. ESCE DALLA REGIONE CRITICA
         */
        up(&mutex);

        /*
         * 4. SEGNALA UN POSTO LIBERO
         *
         * Incrementa empty perché abbiamo consumato
         * un elemento e liberato una posizione.
         *
         * Se il produttore era bloccato perché
         * il buffer era pieno, potrà riprendere.
         */
        up(&empty);

        /*
         * Simuliamo un consumatore più lento.
         *
         * In questo modo il buffer può contenere
         * più elementi contemporaneamente.
         */
        usleep(400000);  // 400 millisecondi
    }

    return NULL;
}


// ============================================================
// PROGRAMMA PRINCIPALE
// ============================================================

int main(void)
{
    // Identificatori dei due thread.
    pthread_t prod, cons;

    /*
     * INIZIALIZZAZIONE DEI SEMAFORI
     *
     * sem_init(&semaforo, pshared, valore_iniziale)
     *
     * pshared = 0:
     * il semaforo è condiviso tra thread
     * appartenenti allo stesso processo.
     *
     * IMPORTANTE:
     * controlliamo gli errori di sem_init().
     * Questo permette anche di rilevare subito
     * il problema su sistemi che non la supportano.
     */

    // mutex = 1: la regione critica è inizialmente libera.
    if (sem_init(&mutex, 0, 1) == -1) {
        perror("Errore sem_init mutex");
        return EXIT_FAILURE;
    }

    // empty = N: inizialmente tutti i posti sono liberi.
    if (sem_init(&empty, 0, N) == -1) {
        perror("Errore sem_init empty");
        return EXIT_FAILURE;
    }

    // full = 0: inizialmente non ci sono elementi.
    if (sem_init(&full, 0, 0) == -1) {
        perror("Errore sem_init full");
        return EXIT_FAILURE;
    }

    /*
     * CREAZIONE DEI THREAD
     *
     * I due thread condividono:
     *
     * - buffer[]
     * - in
     * - out
     * - count
     * - i tre semafori
     *
     * Il main non deve copiare il buffer:
     * tutti i thread dello stesso processo
     * condividono lo spazio di indirizzamento.
     */

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    /*
     * ATTESA DELLA TERMINAZIONE
     *
     * Il main aspetta che produttore e consumatore
     * abbiano terminato il proprio lavoro.
     *
     * pthread_join() NON protegge il buffer:
     * la sincronizzazione avviene con i semafori.
     */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    /*
     * Entrambi i thread sono terminati.
     * Possiamo distruggere i semafori.
     */
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("Produzione e consumo terminati!\n");

    return 0;
}
