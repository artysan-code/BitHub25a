/*
Traccia P4 — Lettura directory (dirent + readdir + permessi).
    - Due figli leggono ciascuno meta' dei file regolari di una directory
      (opendir/readdir da <dirent.h>).
    - Prima di leggere ogni file controllano i permessi con stat ed
      eventualmente aggiungono il permesso di lettura con chmod.
    - Inviano il contenuto al padre nel formato "[PID_FIGLIO] -> TESTO".
    - Il padre stampa quanto ricevuto.

Pattern: fork + opendir/readdir + stat/chmod + pipe condivisa.
Uso: ./a.out <directory>
*/

#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PIPE_RD 0
#define PIPE_WR 1
#define MAXBUF 3000 // < PIPE_BUF (4096): garantisce write atomiche sulla pipe

// Conta i file regolari nella directory.
int count_regular_files(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) return -1;
    struct dirent *e;
    int count = 0;
    char path[1024];
    struct stat st;
    while ((e = readdir(d)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);
        if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) count++;
    }
    closedir(d);
    return count;
}

// Il figlio elabora i file regolari di indice in [start, end).
void child_work(const char *dir, int start, int end, int wr) {
    DIR *d = opendir(dir);
    if (d == NULL) {
        fprintf(stderr, "[ERROR]: figlio %d non puo' aprire %s\n", getpid(), dir);
        return;
    }
    struct dirent *e;
    struct stat st;
    char path[1024];
    int idx = 0;
    while ((e = readdir(d)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);
        if (stat(path, &st) != 0 || !S_ISREG(st.st_mode)) continue;
        if (idx >= start && idx < end) {
            // controllo del permesso di lettura per il proprietario
            if (!(st.st_mode & S_IRUSR)) {
                chmod(path, st.st_mode | S_IRUSR); // aggiunge il permesso di lettura
            }
            FILE *f = fopen(path, "r");
            char report[MAXBUF];
            int n = snprintf(report, sizeof(report), "[%d] -> %s: ", getpid(), e->d_name);
            if (f != NULL) {
                size_t got = fread(report + n, 1, sizeof(report) - n - 2, f);
                n += (int)got;
                fclose(f);
            } else {
                n += snprintf(report + n, sizeof(report) - n, "(non leggibile)");
            }
            report[n++] = '\n';
            write(wr, report, n);
        }
        idx++;
    }
    closedir(d);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <directory>\n", argv[0]);
        return 1;
    }
    const char *dir = argv[1];

    int total = count_regular_files(dir);
    if (total < 0) {
        fprintf(stderr, "[ERROR]: impossibile aprire la directory %s\n", dir);
        return 1;
    }
    int half = total / 2;

    int fd[2];
    pid_t p1, p2;
    if (pipe(fd) < 0) {
        fprintf(stderr, "[ERROR]: could not create pipe\n");
        return 1;
    }

    if ((p1 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return 1;
    }
    if (p1 == 0) {
        close(fd[PIPE_RD]);
        child_work(dir, 0, half, fd[PIPE_WR]); // prima meta'
        close(fd[PIPE_WR]);
        return 0;
    }

    if ((p2 = fork()) < 0) {
        fprintf(stderr, "[ERROR]: could not create process\n");
        return 1;
    }
    if (p2 == 0) {
        close(fd[PIPE_RD]);
        child_work(dir, half, total, fd[PIPE_WR]); // seconda meta'
        close(fd[PIPE_WR]);
        return 0;
    }

    // padre: chiude la scrittura e legge finche' entrambi i figli non chiudono (EOF)
    close(fd[PIPE_WR]);
    char buf[MAXBUF];
    ssize_t r;
    while ((r = read(fd[PIPE_RD], buf, sizeof(buf))) > 0) {
        fwrite(buf, 1, r, stdout);
    }
    close(fd[PIPE_RD]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
