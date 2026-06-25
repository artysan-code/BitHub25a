/*
 * ESERCIZIO PERSONALE — fork + funzioni + codici d'uscita
 * ---------------------------------------------------------
 * Il processo PADRE ha un array di interi PICCOLI (valori 0..255).
 * Deve creare TRE processi FIGLIO, ognuno dei quali esegue una
 * funzione diversa sull'array e comunica il proprio risultato al
 * padre SOLO tramite il CODICE D'USCITA (exit):
 *
 *   - Figlio 1  -> conta quanti numeri sono PARI    -> exit(conteggio)
 *   - Figlio 2  -> conta quanti numeri sono DISPARI -> exit(conteggio)
 *   - Figlio 3  -> trova il MASSIMO dell'array       -> exit(massimo)
 *
 * Il PADRE attende i tre figli e, per ciascuno, legge il codice
 * d'uscita con WEXITSTATUS, poi stampa un riepilogo.
 *
 * Vincoli e cose da ricordare:
 *   - I figli EREDITANO l'array dal padre (la fork copia la memoria):
 *     NON serve passarglielo, lo trovano già in v[].
 *   - Ogni figlio, finito il suo compito, DEVE fare exit(...):
 *     altrimenti prosegue il codice del padre e forka altri processi.
 *   - Il codice d'uscita sta in 0..255: qui i conteggi e il massimo
 *     ci stanno comodi (per questo l'array ha valori piccoli).
 *
 * OUTPUT ATTESO (per auto-verifica) con l'array qui sotto:
 *   v[] = {7, 12, 3, 8, 20, 5}
 *   Pari: 3 | Dispari: 3 | Massimo: 20
 *
 * Compila e prova man mano:
 *   gcc -Wall -Wextra personal.c -o personal && ./personal
 *
 * -------------------- BONUS (quando il base gira) --------------------
 *   B1) Rifai i 3 figli con un CICLO + un array di puntatori a funzione,
 *       invece di tre if(fork()==0) separati.
 *   B2) Aggiungi un Figlio 4 che calcola la SOMMA dell'array. La somma
 *       puo' superare 255, quindi NON ci sta nel codice d'uscita:
 *       falla tornare al padre con una PIPE. (Anteprima del prossimo
 *       argomento: la comunicazione padre<-figlio per dati "veri".)
 * --------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* TODO: scrivi qui le tue tre funzioni
 *   es. void conta_pari(int v[], int n);  (alla fine chiama exit(...))
 */

int conta_pari(int v[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        if (v[i] % 2 == 0) sum++;
    }
    return sum;
}

int conta_dispari(int v[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        if (v[i] % 2 == 1) sum++;
    }
    return sum;
}

int max_array(int v[], int n){
    int max = 0;
    for(int i = 0; i < n; i++){
        if (v[i] > max) max = v[i];
    }
    return max;
}

int main(void) {
    int v[] = {7, 12, 3, 8, 20, 5};
    int n = sizeof(v) / sizeof(v[0]);   /* numero di elementi = 6 */

    /* TODO:
     *   1. crea il Figlio 1 -> esegue la sua funzione -> exit(conteggio)
     *   2. crea il Figlio 2 -> ...
     *   3. crea il Figlio 3 -> ...
     *   4. il PADRE attende i 3 figli (wait/waitpid) e per ciascuno
     *      legge WEXITSTATUS(status) dopo aver controllato WIFEXITED(status)
     *   5. stampa:  Pari: X | Dispari: Y | Massimo: Z
     */

    pid_t figlio_1 = fork();

    int risultato;

    if (figlio_1 == 0){
        risultato = conta_pari(v, n);
        exit(risultato);
    }

    pid_t figlio_2 = fork();

    if (figlio_2 == 0){
        risultato = conta_dispari(v, n);
        exit(risultato);
    }

    pid_t figlio_3 = fork();

    if (figlio_3 == 0){
        risultato = max_array(v, n);
        exit(risultato);
    }

    int status;
    int pari, dispari, max;

    waitpid(figlio_1, &status, 0);
    if (WIFEXITED(status)) pari = WEXITSTATUS(status);

    waitpid(figlio_2, &status, 0);
    if (WIFEXITED(status)) dispari = WEXITSTATUS(status);

    waitpid(figlio_3, &status, 0);
    if (WIFEXITED(status)) max = WEXITSTATUS(status);

    printf("Di seguito i risultati: Pari %d, Dispari %d, Max %d\n", pari, dispari, max);

    return 0;
}
