/*
 * Questo programma dimostra come scrivere e leggere dati in un file utilizzando funzioni POSIX.
 * Utilizza sia formati binari che leggibili (testuali) per illustrare le differenze tra i due metodi.
 * 
 * **Sezioni principali:**
 * 
 * 1. **Scrittura nel file (`foo.txt`):**
 *    - Scrive un intero in formato binario.
 *    - Scrive un intero in formato leggibile (testuale).
 *    - Scrive un float in formato binario.
 *    - Scrive un float in formato leggibile.
 *    - Scrive una stringa.
 *    - Scrive una stringa combinata con un numero formattato leggibile.
 * 
 * 2. **Lettura dal file (`foo.txt`):**
 *    - Legge un intero scritto in formato binario.
 *    - Legge un intero scritto in formato leggibile.
 *    - Legge un float scritto in formato binario.
 *    - Legge un float scritto in formato leggibile.
 *    - Legge il resto del file, una riga alla volta, fino alla fine.
 * 
 * 3. **Funzione `read_line`:**
 *    - Implementa una lettura di una riga alla volta da un file in stile POSIX.
 *    - Questa funzione non è nativamente disponibile in POSIX, ma permette di leggere
 *      una riga fino al carattere '\n' o EOF.
 * 
 * **Note:**
 * - Il file è denominato "foo.txt". Viene creato se non esiste e viene sovrascritto se già esiste.
 * - Per le letture leggibili, il codice tiene traccia del numero di byte scritti per interpretare correttamente i dati.
 * - La lettura in formato binario richiede che il programma conosca il tipo e la dimensione dei dati.
 * 
 * **Vantaggi e svantaggi:**
 * - **Binario:**
 *   - Pro: Più efficiente in termini di spazio.
 *   - Contro: Non leggibile dall'utente e dipendente dalla piattaforma (endianness, dimensioni dei tipi).
 * - **Leggibile:**
 *   - Pro: Portabile e facile da leggere e modificare.
 *   - Contro: Richiede più spazio e operazioni di conversione.
 * 
 * **Utilizzo:**
 * - Compilare con un compilatore compatibile con POSIX, ad esempio `gcc`.
 * - Eseguire il programma, che creerà il file `foo.txt` e stamperà i risultati della lettura sulla console.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "foo.txt" // Nome del file da utilizzare
#define BUFFER_SIZE 256


// Funzione per leggere una riga intera da un file. In POSIX "non c'è" :-(
ssize_t read_line(int file_fd, char *buffer, size_t max_length) {
    char ch;
    size_t count = 0;

    // Leggi un carattere alla volta fino a trovare '\n' o EOF
    while (count < max_length - 1) {
        ssize_t bytes_read = read(file_fd, &ch, 1); // Legge un carattere
        if (bytes_read == 0) {
            // Fine del file
            break;
        } else if (bytes_read < 0) {
            // Errore nella lettura
            perror("Errore nella lettura del file");
            return -1;
        }

        // Aggiungi il carattere al buffer
        buffer[count++] = ch;

        // Termina la lettura se troviamo '\n'
        if (ch == '\n') {
            break;
        }
    }

    // Null-terminate la stringa
    buffer[count] = '\0';

    // Restituisce il numero di byte letti
    return count;
}


int main() {
    int file_fd;
    char buffer[BUFFER_SIZE];

    //--------------HOW TO WRITE----------------------

    // 1. Aprire il file foo.txt e, se non esiste, crearlo.
    file_fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("Errore nell'aprire il file");
        return 1;
    }

    // 2. Scrive un intero in formato binario.
    int my_int_bin = 42; // Intero da scrivere in formato binario
    write(file_fd, &my_int_bin, sizeof(my_int_bin)); // Scrittura binaria

    // 3. Scrive un intero in formato leggibile.
    int my_int_text = 43; // Intero da scrivere in formato leggibile
    sprintf(buffer, "%d\n", my_int_text);
    int my_int_string_len = strlen(buffer);
    write(file_fd, buffer, my_int_string_len); // Scrittura testuale

    // 4. Scrive un float in formato binario.
    float my_float_bin = 3.14f; // Float da scrivere in formato binario
    write(file_fd, &my_float_bin, sizeof(my_float_bin)); // Scrittura binaria

    // 5. Scrive un float in formato leggibile.
    float my_float_text = 2.71f; // Float da scrivere in formato leggibile
    sprintf(buffer, "%.2f\n", my_float_text);
    int my_float_string_len = strlen(buffer);
    write(file_fd, buffer, my_float_string_len); // Scrittura testuale

    // 6. Scrive una stringa in formato leggibile.
    const char *my_string_text = "Hello Text"; // Stringa da scrivere
    sprintf(buffer, "%s\n", my_string_text);
    write(file_fd, buffer, strlen(buffer)); // Scrittura testuale

    // 7. Scrive una stringa più un numero in formato leggibile.
    const char *message = "My favorite number is"; // Messaggio da scrivere
    int favorite_number = 7; // Numero associato al messaggio
    // Formatta il messaggio e il numero in una stringa leggibile
    sprintf(buffer, "%s %d\n", message, favorite_number);
    // Scrive il contenuto formattato nel file
    write(file_fd, buffer, strlen(buffer));

    // 8. Chiude il file dopo la scrittura.
    close(file_fd);

    //--------------HOW TO READ----------------------

    // 9. Riapre il file per la lettura.
    file_fd = open(FILENAME, O_RDONLY);
    if (file_fd < 0) {
        perror("Errore nell'aprire il file per lettura");
        return 1;
    }

    // 10. Legge un intero in formato binario.
    int read_int_bin;
    read(file_fd, &read_int_bin, sizeof(read_int_bin)); // Lettura binaria
    printf("Intero letto (binario): %d\n", read_int_bin);

    // 11. Legge un intero in formato leggibile. Ma devo ricordare quanti byte ho scritto prima!
    read(file_fd, buffer, my_int_string_len);
    int read_int_text = atoi(buffer); // Conversione da stringa a intero
    printf("Intero letto (testuale): %d\n", read_int_text);

    // 12. Legge un float in formato binario.
    float read_float_bin;
    read(file_fd, &read_float_bin, sizeof(read_float_bin)); // Lettura binaria
    printf("Float letto (binario): %.2f\n", read_float_bin);

    // 13. Legge un float in formato leggibile. Ancora, devo ricordare quanti byte ho scritto prima!
    read(file_fd, buffer, my_float_string_len);
    float read_float_text = atof(buffer); // Conversione da stringa a float
    printf("Float letto (testuale): %.2f\n", read_float_text);

    // 14. Legge il resto del file, una riga alla volta fino alla fine del file
    while (read_line(file_fd, buffer, BUFFER_SIZE) > 0) {
        printf("Resto del file. Riga letta: %s", buffer);
    }

    // 15. Chiude il file.
    close(file_fd);

    return 0;
}