/*
Traccia P2 — Numeri pari/dispari [0-100], soglia 190.
    - Il primo figlio invia al padre numeri pari casuali in [0, 100].
    - Il secondo figlio invia al padre numeri dispari casuali in [0, 100].
    - Il padre legge una coppia per iterazione, ne calcola la somma e la stampa;
      quando la somma supera 190 termina i figli con SIGTERM (kill).

Pattern: fork + due pipe + SIGTERM. Variante della traccia P6 (fork_sum.c) con
soglia e parita' diverse.
*/

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PIPE_RD 0
#define PIPE_WR 1

int main() {
    srand(time(NULL));

    int fd_pari[2], fd_dispari[2];
    pid_t p1, p2;
    int n_rand;

    if (pipe(fd_pari) < 0 || pipe(fd_dispari) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }

    if (p1 == 0) {
        // primo figlio: numeri PARI in [0, 100]
        close(fd_pari[PIPE_RD]);
        close(fd_dispari[PIPE_RD]);
        close(fd_dispari[PIPE_WR]);
        while (1) {
            do {
                n_rand = rand() % 101;
            } while (n_rand % 2 != 0);
            write(fd_pari[PIPE_WR], &n_rand, sizeof(n_rand));
            sleep(1);
        }
    }

    if ((p2 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }

    if (p2 == 0) {
        // secondo figlio: numeri DISPARI in [0, 100]
        close(fd_dispari[PIPE_RD]);
        close(fd_pari[PIPE_RD]);
        close(fd_pari[PIPE_WR]);
        while (1) {
            do {
                n_rand = rand() % 101;
            } while (n_rand % 2 == 0);
            write(fd_dispari[PIPE_WR], &n_rand, sizeof(n_rand));
            sleep(1);
        }
    }

    // padre
    int sum, n1, n2;
    close(fd_pari[PIPE_WR]);
    close(fd_dispari[PIPE_WR]);

    do {
        read(fd_pari[PIPE_RD], &n1, sizeof(n1));
        read(fd_dispari[PIPE_RD], &n2, sizeof(n2));
        sum = n1 + n2;
        printf("[INFO]: %d (pari) + %d (dispari) = %d\n", n1, n2, sum);
    } while (sum <= 190);

    printf("[INFO]: soglia superata, termino i figli\n");
    kill(p1, SIGTERM);
    kill(p2, SIGTERM);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
