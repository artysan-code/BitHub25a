/*
Traccia P7 — Pipe bidirezionale padre-figlio (quadrato se pari).
    - Il padre invia un numero al figlio tramite una prima pipe.
    - Il figlio ne calcola il quadrato; se il quadrato e' PARI lo reinvia al
      padre tramite una seconda pipe.
    - Il padre stampa il risultato; se non riceve nulla (quadrato dispari) lo segnala.

Pattern: fork + due pipe (comunicazione bidirezionale) + rilevamento dell'EOF
per distinguere "nessun valore inviato" da un valore ricevuto.
Uso: ./a.out [numero]   (se omesso, ne genera uno casuale)
*/

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PIPE_RD 0
#define PIPE_WR 1

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int n;
    if (argc == 2) {
        n = atoi(argv[1]);
    } else {
        n = rand() % 20 + 1;
    }

    int fd_pf[2]; // padre -> figlio
    int fd_fp[2]; // figlio -> padre
    pid_t pid;

    if (pipe(fd_pf) < 0 || pipe(fd_fp) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipes\n");
        return -1;
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return -1;
    }

    if (pid == 0) {
        // figlio
        close(fd_pf[PIPE_WR]);
        close(fd_fp[PIPE_RD]);
        int x;
        read(fd_pf[PIPE_RD], &x, sizeof(x));
        int sq = x * x;
        if (sq % 2 == 0) {
            printf("[FIGLIO]: %d^2 = %d e' pari, lo reinvio al padre\n", x, sq);
            write(fd_fp[PIPE_WR], &sq, sizeof(sq));
        } else {
            printf("[FIGLIO]: %d^2 = %d e' dispari, non invio nulla\n", x, sq);
        }
        // in entrambi i casi chiude la scrittura: il padre vedra' un valore o EOF
        close(fd_fp[PIPE_WR]);
        close(fd_pf[PIPE_RD]);
        return 0;
    }

    // padre
    close(fd_pf[PIPE_RD]);
    close(fd_fp[PIPE_WR]);

    printf("[PADRE]: invio %d al figlio\n", n);
    write(fd_pf[PIPE_WR], &n, sizeof(n));
    close(fd_pf[PIPE_WR]);

    int res;
    ssize_t r = read(fd_fp[PIPE_RD], &res, sizeof(res));
    if (r > 0) {
        printf("[PADRE]: ricevuto il quadrato (pari) = %d\n", res);
    } else {
        printf("[PADRE]: nessun valore ricevuto -> il quadrato era dispari\n");
    }
    close(fd_fp[PIPE_RD]);
    waitpid(pid, NULL, 0);
    return 0;
}
