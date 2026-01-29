/*
==========================================================
ESERCIZIO:

Un processo padre genera due processi figli P1 e P2.
- Il figlio P1 esegue un ciclo indefinito durante il quale genera casualmente 
  numeri interi compresi tra 0 e 100.
  P1 invia al padre i numeri soltanto se essi sono dispari.

- Il figlio P2 fa la stessa cosa ma invia al padre soltanto i numeri pari.

- Il padre legge i numeri inviati da P1 e P2, e non appena ne ha uno da P1 e uno da P2 
  (cioè una coppia), calcola la somma e la visualizza sullo schermo.

- L'esecuzione termina quando la somma dei due numeri ricevuti dai figli supera 190.
  A quel punto, il padre invia un segnale di terminazione (SIGTERM) a entrambi i figli 
  e poi termina a sua volta.

- Tutti i processi disabilitano la gestione predefinita del segnale SIGINT, 
  sostituendola con un handler che, alla pressione di Ctrl+C, non termini l'esecuzione 
  ma visualizzi un messaggio "Interruzione disabilitata!!!".

==========================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

// Handler per il segnale SIGINT: non termina il processo ma mostra un messaggio.
void signal_handler(int signal) {
    printf("Sono il processo %d: Interruzione disabilitata!!!\n", getpid());
    // Non usciamo, il programma continua normalmente.
}

int main(int argc, char **argv) {
    int fd1[2], fd2[2]; // Pipe per comunicazione: P1->Padre su fd1, P2->Padre su fd2
    pid_t P1, P2;
    int r1, r2;         // Variabili per i numeri ricevuti dai figli
    int sum;            // Somma dei due numeri

    // Disabilito la terminazione su SIGINT.
    // Se l'utente preme CTRL+C, verrà eseguito signal_handler.
    // Avendolo inserito all'inizio tutti i processi poi useranno questo signal_handler
    signal(SIGINT, signal_handler);

    // Creo le pipe per la comunicazione dai figli al padre.
    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        perror("Errore nella creazione delle pipe");
        exit(1);
    }

    // Creo il primo figlio P1.
    // P1 genererà numeri dispari e li invierà al padre.
    P1 = fork();
    if (P1 < 0) {
        perror("Errore nella creazione del primo processo figlio");
        exit(1);
    }

    if (P1 == 0) {
        // Codice del primo figlio (P1).
        close(fd1[0]); // P1 non legge dalla pipe, quindi chiudo estremità di lettura.
        srand(time(NULL) ^ getpid()); // Inizializzo il seed del generatore (veramente!) random.

        while (1) {
            r1 = rand() % 101; // Genero un numero tra 0 e 100
            // Invia solo i numeri dispari
            if (r1 % 2 == 1) {
                // Scrivo il numero nella pipe verso il padre.
                // Attenzione: sto scrivendo in forma binaria. Avrei potuto convertirlo in stringa, ma con un overhead (vedi lezione )
                if (write(fd1[1], &r1, sizeof(r1)) < 0) {
                    perror("Errore nella scrittura da P1");
                    break; // Esco se non riesco a scrivere
                }
            }
            // Introduco una breve pausa per evitare loop troppo veloci
            usleep(100000); 
        }

        close(fd1[1]); // Chiudo la pipe in uscita prima di terminare.
        exit(0);
    }

    // Creo il secondo figlio P2.
    // P2 genererà numeri pari e li invierà al padre.
    P2 = fork();
    if (P2 < 0) {
        perror("Errore nella creazione del secondo processo figlio");
        exit(1);
    }

    if (P2 == 0) {
        // Codice del secondo figlio (P2)
        close(fd2[0]); // P2 non legge, quindi chiudo estremità di lettura.
        srand(time(NULL) ^ getpid());

        while (1) {
            r2 = rand() % 101; // Genero un numero tra 0 e 100
            // Invia solo i numeri pari
            if (r2 % 2 == 0) {
                // Scrivo il numero nella pipe verso il padre
                if (write(fd2[1], &r2, sizeof(r2)) < 0) {
                    perror("Errore nella scrittura da P2");
                    break;
                }
            }
            usleep(100000);
        }

        close(fd2[1]);
        exit(0);
    }

    // Codice del padre
    close(fd1[1]); // Chiudo estremità di scrittura lato padre nella pipe 1
    close(fd2[1]); // Chiudo estremità di scrittura lato padre nella pipe 2

    // Il padre ora legge ciclicamente un valore da P1 e uno da P2 e calcola la somma. 
    while (1) {
        // Leggo da P1 un numero dispari
        if (read(fd1[0], &r1, sizeof(r1)) <= 0) {
            // Se non leggo più nulla significa che il figlio P1 ha terminato o c'è un errore.
            break;
        }

        // Leggo da P2 un numero pari
        if (read(fd2[0], &r2, sizeof(r2)) <= 0) {
            // Se non leggo più nulla significa che il figlio P2 ha terminato o c'è un errore.
            break;
        }

        sum = r1 + r2;
        printf("Padre riceve: P1=%d, P2=%d, Somma=%d\n", r1, r2, sum);

        // Se la somma supera 190, il padre termina i figli e poi sé stesso.
        if (sum > 190) {
            printf("Somma > 190, termino i processi figli.\n");
            kill(P1, SIGTERM);
            kill(P2, SIGTERM);
            break;
        }

        usleep(100000);
    }

    // Chiudo le estremità di lettura.
    close(fd1[0]);
    close(fd2[0]);

    // Attendo la terminazione dei figli
    waitpid(P1, NULL, 0);
    waitpid(P2, NULL, 0);

    return 0;
}