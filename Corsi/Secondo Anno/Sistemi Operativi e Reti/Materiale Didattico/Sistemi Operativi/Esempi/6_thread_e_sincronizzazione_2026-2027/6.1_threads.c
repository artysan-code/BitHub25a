#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Numero di thread da creare
#define NUMBER_OF_THREADS 10

// Questa funzione viene eseguita da ciascun thread.
// pthread_create() richiede una funzione che riceve
// un puntatore void * e restituisce un puntatore void *.
void *print_hello_world(void *arg)
{
    // Il main ha passato l'indirizzo di un intero.
    // Convertiamo il puntatore e leggiamo il valore.
    int id = *(int *)arg;

    // Ogni thread aspetta un numero diverso di secondi.
    // Usiamo l'ID per rendere facilmente osservabile
    // che i thread possono terminare in ordine diverso.
    int r = id % 5;

    sleep(r);

    // Stampa il numero identificativo assegnato dal main.
    printf("Hello World dal thread %d\n", id);

    // Il thread ha terminato il proprio lavoro.
    // return NULL equivale, in questo caso,
    // a terminare il thread con pthread_exit(NULL).
    return NULL;
}

int main(void)
{
    // Array che contiene gli identificatori pthread_t
    // assegnati dalla libreria ai thread creati.
    pthread_t threads[NUMBER_OF_THREADS];

    // Array con i numeri da passare ai singoli thread.
    // Deve rimanere valido mentre i thread li utilizzano.
    int ids[NUMBER_OF_THREADS];

    int status;
    int i;

    // =========================================
    // CREAZIONE DEI THREAD
    // =========================================

    for (i = 0; i < NUMBER_OF_THREADS; i++) {

        ids[i] = i;

        /*
         * pthread_create() crea un nuovo thread.
         *
         * Parametri:
         * 1. &threads[i]        dove salvare il suo identificatore
         * 2. NULL               attributi predefiniti
         * 3. print_hello_world  funzione eseguita dal thread
         * 4. &ids[i]            argomento passato alla funzione
         *
         * ATTENZIONE:
         * Passiamo &ids[i], cioè l'indirizzo di un elemento
         * diverso dell'array per ciascun thread.
         *
         * NON passiamo &i:
         * il main modifica continuamente i durante il ciclo,
         * mentre i thread potrebbero leggerlo in momenti diversi.
         * Questo potrebbe produrre valori errati e una data race.
         */

        status = pthread_create(
            &threads[i],
            NULL,
            print_hello_world,
            &ids[i]
        );

        // pthread_create restituisce 0 se ha successo.
        if (status != 0) {
            fprintf(stderr, "Errore nella creazione del thread %d\n", i);
            exit(1);
        }

        printf("Thread %d creato\n", i);
    }

    // =========================================
    // ATTESA DELLA TERMINAZIONE
    // =========================================

    for (i = 0; i < NUMBER_OF_THREADS; i++) {

        /*
         * pthread_join() attende la terminazione
         * del thread specificato.
         *
         * Se il thread è ancora in esecuzione,
         * il main rimane in attesa.
         *
         * Se il thread è già terminato,
         * pthread_join() ritorna immediatamente.
         *
         * NULL significa che non ci interessa
         * recuperare il valore restituito dal thread.
         */

        status = pthread_join(threads[i], NULL);

        if (status != 0) {
            fprintf(stderr, "Errore nell'attesa del thread %d\n", i);
            exit(1);
        }

        printf("Thread %d terminato\n", i);
    }

    // Arriviamo qui solo dopo aver atteso tutti i thread.
    printf("Tutti i thread hanno terminato!\n");

    return 0;
}
