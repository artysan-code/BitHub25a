#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    for (int i = 20; i >= 1; i--) {
        printf("%d\n", i);
        fflush(stdout);  // Assicura che l'output venga visualizzato immediatamente

        // Dormi per un tempo casuale tra 0 e 2 secondi
        sleep(rand() % 3);
    }

    printf("\nBYE\n");
    fflush(stdout);

    return 0;
}