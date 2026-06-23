/*
Traccia P8 — Fusione array pari/dispari (max e min).
    - Il padre genera un array di N interi (i figli ne ereditano una copia con la fork).
    - Il figlio 1 invia al padre gli elementi nelle POSIZIONI PARI (indici 0, 2, 4, ...).
    - Il figlio 2 invia al padre gli elementi nelle POSIZIONI DISPARI (indici 1, 3, 5, ...).
    - Il padre ricostruisce l'array fuso e calcola il MASSIMO e il MINIMO.

Pattern: fork + due pipe + ricomposizione di un array da contributi paralleli.
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N 10
#define PIPE_RD 0
#define PIPE_WR 1

int main() {
    srand(time(NULL));

    int arr[N];
    for (int i = 0; i < N; i++) arr[i] = rand() % 100;

    printf("[PADRE]: array generato:");
    for (int i = 0; i < N; i++) printf(" %d", arr[i]);
    printf("\n");
    fflush(stdout); // svuota il buffer PRIMA della fork: altrimenti i figli
                    // ne ereditano una copia e lo ri-stampano alla loro uscita

    int fd_pari[2];    // figlio1 -> padre (posizioni pari)
    int fd_dispari[2]; // figlio2 -> padre (posizioni dispari)
    pid_t p1, p2;

    if (pipe(fd_pari) < 0 || pipe(fd_dispari) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }
    if (p1 == 0) {
        // figlio 1: invia gli elementi nelle posizioni pari
        close(fd_pari[PIPE_RD]);
        for (int i = 0; i < N; i += 2)
            write(fd_pari[PIPE_WR], &arr[i], sizeof(int));
        close(fd_pari[PIPE_WR]);
        return 0;
    }

    if ((p2 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }
    if (p2 == 0) {
        // figlio 2: invia gli elementi nelle posizioni dispari
        close(fd_dispari[PIPE_RD]);
        for (int i = 1; i < N; i += 2)
            write(fd_dispari[PIPE_WR], &arr[i], sizeof(int));
        close(fd_dispari[PIPE_WR]);
        return 0;
    }

    // padre: ricompone l'array fuso
    close(fd_pari[PIPE_WR]);
    close(fd_dispari[PIPE_WR]);

    int fuso[N];
    for (int i = 0; i < N; i += 2) read(fd_pari[PIPE_RD], &fuso[i], sizeof(int));
    for (int i = 1; i < N; i += 2) read(fd_dispari[PIPE_RD], &fuso[i], sizeof(int));

    int max = fuso[0], min = fuso[0];
    for (int i = 1; i < N; i++) {
        if (fuso[i] > max) max = fuso[i];
        if (fuso[i] < min) min = fuso[i];
    }

    printf("[PADRE]: array fuso:    ");
    for (int i = 0; i < N; i++) printf(" %d", fuso[i]);
    printf("\n[PADRE]: max = %d, min = %d\n", max, min);

    close(fd_pari[PIPE_RD]);
    close(fd_dispari[PIPE_RD]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
