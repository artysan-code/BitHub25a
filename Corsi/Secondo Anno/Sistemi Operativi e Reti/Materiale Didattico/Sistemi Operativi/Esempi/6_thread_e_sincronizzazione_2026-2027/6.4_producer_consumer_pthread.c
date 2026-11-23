
/*
 * ============================================================
 * PRODUTTORE - CONSUMATORE CON MUTEX E VARIABILI CONDIZIONALI
 * ============================================================
 *
 * Autore: Danilo Croce
 * Corso: SOR - Sistemi Operativi e Reti
 *
 * COSA FA QUESTO PROGRAMMA?
 *
 * Il programma crea due thread:
 *
 * - un PRODUTTORE, che genera numeri casuali;
 * - un CONSUMATORE, che preleva i numeri prodotti.
 *
 * I due thread condividono un buffer di N posizioni.
 *
 * Il buffer è una CODA CIRCOLARE FIFO:
 * il primo elemento inserito è il primo a essere prelevato.
 *
 * Il produttore può inserire più elementi consecutivamente,
 * finché esistono posti liberi.
 *
 * Il consumatore può prelevare elementi soltanto
 * quando il buffer non è vuoto.
 *
 * ------------------------------------------------------------
 * CONFRONTO CON L'ESEMPIO 6.2
 *
 * Questo programma risolve lo STESSO problema dell'esempio
 * 6.2_producer_consumer_semaphore.c.
 *
 * Utilizziamo:
 * - lo stesso buffer FIFO di 10 posizioni;
 * - un produttore e un consumatore;
 * - 20 elementi da produrre e consumare;
 * - le stesse pause per osservare la concorrenza.
 *
 * CAMBIA SOLTANTO IL MECCANISMO DI SINCRONIZZAZIONE.
 *
 * ESEMPIO 6.2 (SEMAFORI):
 *
 *     mutex : protegge il buffer
 *     empty : conta i posti liberi
 *     full  : conta gli elementi presenti
 *
 * ESEMPIO 6.4 (PTHREADS):
 *
 *     mutex     : protegge il buffer e i suoi indici
 *     not_full  : permette di aspettare un posto libero
 *     not_empty : permette di aspettare un elemento
 *
 * ------------------------------------------------------------
 * COME FUNZIONANO LE VARIABILI CONDIZIONALI?
 *
 * pthread_cond_wait(&cond, &mutex):
 *
 * - rilascia atomicamente il mutex e mette il thread
 *   in attesa sulla variabile condizionale;
 * - il thread rimane sospeso senza busy waiting;
 * - prima di ritornare, riacquisisce il mutex.
 *
 * pthread_cond_signal(&cond):
 *
 * - segnala a uno dei thread in attesa che qualcosa
 *   potrebbe essere cambiato;
 * - non trasferisce automaticamente il mutex;
 * - non memorizza un segnale se nessuno sta aspettando.
 *
 * Per questo motivo il thread deve SEMPRE controllare
 * la condizione concreta attraverso un ciclo while.
 *
 * ATTENZIONE:
 * una variabile condizionale NON è un semaforo!
 *
 * I semafori contano le disponibilità.
 * Le variabili condizionali permettono di aspettare
 * che una condizione sui dati condivisi diventi vera.
 *
 * ------------------------------------------------------------
 * COMPATIBILITA'
 *
 * Il programma utilizza mutex e variabili condizionali
 * POSIX Threads ed è adatto sia a Linux sia a macOS.
 *
 * Non utilizza sem_init().
 *
 * Compilazione:
 *
 * gcc -Wall -Wextra -pthread \
 *     6.4_producer_consumer_pthread.c \
 *     -o 6.4_producer_consumer_pthread
 *
 * Esecuzione:
 *
 * ./6.4_producer_consumer_pthread
 *
 * ============================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10          // Numero di posti nel buffer
#define MAX_ITEMS 20  // Numero totale di elementi prodotti


// ============================================================
// VARIABILI CONDIVISE TRA I THREAD
// ============================================================

// Mutex che protegge l'accesso al buffer e ai suoi indici.
pthread_mutex_t mutex;

// Variabili condizionali.
//
// not_full: il produttore aspetta se il buffer è pieno.
// not_empty: il consumatore aspetta se il buffer è vuoto.
pthread_cond_t not_full;
pthread_cond_t not_empty;

// Buffer condiviso: stessa struttura del programma 6.2.
int buffer[N];

// Prossima posizione in cui inserire un elemento.
int in = 0;

// Prossima posizione da cui prelevare un elemento.
int out = 0;

// Numero di elementi attualmente presenti nel buffer.
int count = 0;


// ============================================================
// OPERAZIONI SUL BUFFER
// ============================================================

/*
 * Inserisce un nuovo elemento nel buffer.
 *
 * Questa funzione deve essere chiamata
 * soltanto quando il mutex è acquisito
 * e count < N.
 */
void insert_item(void)
{
    int item = rand() % 100;

    buffer[in] = item;

    printf("PRODUTTORE: inserisco %d in posizione %d\n",
           item, in);

    // Avanza l'indice, tornando a 0 dopo N-1.
    in = (in + 1) % N;

    // Un elemento presente in più.
    count++;
}

/*
 * Preleva l'elemento più vecchio dal buffer.
 *
 * Questa funzione deve essere chiamata
 * soltanto quando il mutex è acquisito
 * e count > 0.
 */
void remove_item(void)
{
    int item = buffer[out];

    printf("CONSUMATORE: prelevo %d dalla posizione %d\n",
           item, out);

    // Avanza l'indice, tornando a 0 dopo N-1.
    out = (out + 1) % N;

    // Un elemento presente in meno.
    count--;
}

/*
 * Stampa gli elementi presenti nel buffer.
 *
 * La stampa avviene in ordine FIFO:
 * dal prossimo elemento da consumare all'ultimo inserito.
 *
 * Anche questa funzione viene chiamata
 * mentre il mutex è acquisito.
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
    (void)arg; // Non utilizziamo argomenti.

    for (int i = 0; i < MAX_ITEMS; i++) {

        /*
         * 1. ACQUISISCE IL MUTEX
         *
         * Dobbiamo controllare count e modificare il buffer.
         * Entrambe le operazioni richiedono mutua esclusione.
         */
        pthread_mutex_lock(&mutex);

        /*
         * 2. ASPETTA SE IL BUFFER E' PIENO
         *
         * Nell'esempio 6.2 questa attesa era:
         *
         *     down(&empty);
         *
         * Qui invece controlliamo direttamente count.
         */
        while (count == N) {

            /*
             * pthread_cond_wait():
             *
             * - rilascia il mutex;
             * - sospende il produttore;
             * - al risveglio riacquisisce il mutex.
             *
             * Il consumatore può quindi entrare
             * e prelevare un elemento.
             *
             * Usiamo while e non if perché
             * al risveglio dobbiamo ricontrollare
             * che esista effettivamente un posto libero.
             */
            pthread_cond_wait(&not_full, &mutex);
        }

        // -------- INIZIO OPERAZIONE SUL BUFFER --------

        insert_item();
        print_buffer();

        // -------- FINE OPERAZIONE SUL BUFFER --------

        /*
         * 3. SEGNALA CHE IL BUFFER NON E' VUOTO
         *
         * Abbiamo appena inserito un elemento.
         *
         * Se il consumatore sta aspettando su not_empty,
         * può essere risvegliato.
         *
         * Nell'esempio 6.2 usavamo:
         *
         *     up(&full);
         */
        pthread_cond_signal(&not_empty);

        /*
         * 4. RILASCIA IL MUTEX
         *
         * Se il consumatore era in attesa,
         * potrà proseguire soltanto dopo aver
         * riacquisito questo mutex.
         */
        pthread_mutex_unlock(&mutex);

        /*
         * Simuliamo il tempo necessario
         * per produrre un nuovo elemento.
         *
         * Il produttore è più veloce del consumatore,
         * così possiamo osservare il buffer riempirsi.
         *
         * La pausa è fuori dalla regione critica.
         */
        usleep(100000); // 100 millisecondi
    }

    return NULL;
}


// ============================================================
// THREAD CONSUMATORE
// ============================================================

void *consumer(void *arg)
{
    (void)arg; // Non utilizziamo argomenti.

    for (int i = 0; i < MAX_ITEMS; i++) {

        /*
         * 1. ACQUISISCE IL MUTEX
         *
         * Anche il consumatore deve controllare
         * count e modificare il buffer.
         */
        pthread_mutex_lock(&mutex);

        /*
         * 2. ASPETTA SE IL BUFFER E' VUOTO
         *
         * Nell'esempio 6.2 questa attesa era:
         *
         *     down(&full);
         *
         * Qui invece controlliamo count.
         */
        while (count == 0) {

            /*
             * Il consumatore:
             *
             * - rilascia il mutex;
             * - aspetta sulla variabile not_empty;
             * - al risveglio riacquisisce il mutex.
             *
             * Il produttore può così entrare
             * e inserire un nuovo elemento.
             */
            pthread_cond_wait(&not_empty, &mutex);
        }

        // -------- INIZIO OPERAZIONE SUL BUFFER --------

        remove_item();
        print_buffer();

        // -------- FINE OPERAZIONE SUL BUFFER --------

        /*
         * 3. SEGNALA CHE IL BUFFER NON E' PIENO
         *
         * Abbiamo liberato una posizione.
         *
         * Se il produttore sta aspettando su not_full,
         * può essere risvegliato.
         *
         * Nell'esempio 6.2 usavamo:
         *
         *     up(&empty);
         */
        pthread_cond_signal(&not_full);

        /*
         * 4. RILASCIA IL MUTEX
         */
        pthread_mutex_unlock(&mutex);

        /*
         * Simuliamo un consumatore più lento.
         *
         * Il buffer può quindi accumulare
         * più elementi contemporaneamente.
         */
        usleep(400000); // 400 millisecondi
    }

    return NULL;
}


// ============================================================
// PROGRAMMA PRINCIPALE
// ============================================================

int main(void)
{
    pthread_t prod, cons;

    /*
     * INIZIALIZZAZIONE DEL MUTEX
     *
     * Il mutex viene inizializzato libero.
     */
    pthread_mutex_init(&mutex, NULL);

    /*
     * INIZIALIZZAZIONE DELLE VARIABILI CONDIZIONALI
     *
     * Le condizioni non rappresentano contatori:
     * il loro stato non indica il numero di elementi.
     *
     * E' la variabile count che ci dice
     * se il buffer è pieno oppure vuoto.
     */
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    /*
     * CREAZIONE DEI DUE THREAD
     *
     * I thread condividono buffer, in, out, count,
     * il mutex e le due variabili condizionali.
     */
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    /*
     * Il main attende la terminazione dei due thread.
     *
     * pthread_join() non protegge il buffer:
     * serve soltanto ad attendere la fine dei thread.
     */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    /*
     * Entrambi i thread hanno terminato.
     * Possiamo distruggere le primitive di sincronizzazione.
     */
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    pthread_mutex_destroy(&mutex);

    printf("Produzione e consumo terminati!\n");

    return 0;
}
