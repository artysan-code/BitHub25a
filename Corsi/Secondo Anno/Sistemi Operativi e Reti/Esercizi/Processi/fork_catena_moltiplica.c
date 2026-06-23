/*
Traccia P3 — Catena padre-figlio1-figlio2 (due pipe).
    - Il figlio 1 genera un numero casuale e lo invia al padre tramite la prima pipe.
    - Il padre sceglie un fattore k casuale, moltiplica e invia il risultato al
      figlio 2 tramite la seconda pipe.
    - Il figlio 2 stampa il valore ricevuto.

Pattern: fork + due pipe in cascata (figlio1 -> padre -> figlio2).
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PIPE_RD 0
#define PIPE_WR 1

int main() {
    srand(time(NULL));

    int fd1[2]; // figlio1 -> padre
    int fd2[2]; // padre -> figlio2
    pid_t p1, p2;

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }

    if (p1 == 0) {
        // figlio 1: genera un numero e lo invia al padre
        close(fd1[PIPE_RD]);
        close(fd2[PIPE_RD]);
        close(fd2[PIPE_WR]);
        int n = rand() % 100 + 1;
        printf("[FIGLIO1]: genero %d e lo invio al padre\n", n);
        write(fd1[PIPE_WR], &n, sizeof(n));
        close(fd1[PIPE_WR]);
        return 0;
    }

    if ((p2 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }

    if (p2 == 0) {
        // figlio 2: riceve il risultato dal padre e lo stampa
        close(fd2[PIPE_WR]);
        close(fd1[PIPE_RD]);
        close(fd1[PIPE_WR]);
        int res;
        read(fd2[PIPE_RD], &res, sizeof(res));
        printf("[FIGLIO2]: ho ricevuto il risultato %d\n", res);
        close(fd2[PIPE_RD]);
        return 0;
    }

    // padre: legge da figlio1, moltiplica per k, invia a figlio2
    close(fd1[PIPE_WR]);
    close(fd2[PIPE_RD]);

    int n, k, res;
    read(fd1[PIPE_RD], &n, sizeof(n));
    k = rand() % 10 + 1;
    res = n * k;
    printf("[PADRE]: ricevuto %d, fattore k = %d, invio %d a figlio2\n", n, k, res);
    write(fd2[PIPE_WR], &res, sizeof(res));

    close(fd1[PIPE_RD]);
    close(fd2[PIPE_WR]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
