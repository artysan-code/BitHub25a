/*
 * Questo programma elenca il contenuto di una directory specificata come argomento, 
 * mostrando informazioni dettagliate su ogni file e directory, simile al comando `ls -l` di UNIX.
 * 
 * **Uso:**
 *   ./program_name <directory>
 * 
 * **Descrizione delle funzioni principali:**
 * 
 * - `printf`: Stampa le informazioni di ciascun file in un formato leggibile dall'utente.
 *   Esempi in questo codice:
 *   - `printf("%llu ", fileInfo.st_size);`: Stampa la dimensione del file.
 *   - `printf((S_ISDIR(fileInfo.st_mode)) ? "d" : "-");`: Usa una ternaria per stampare "d" se è una directory o "-" altrimenti.
 *   - `printf("%s %s", pw->pw_name, gr->gr_name);`: Stampa i nomi del proprietario e del gruppo del file.
 * 
 * - `snprintf`: Costruisce una stringa sicura di lunghezza limitata. Utilizzato per concatenare il percorso del file:
 *   ```c
 *   snprintf(filePath, sizeof(filePath), "%s/%s", dirName, fileName);
 *   ```
 *   Questo metodo protegge da buffer overflow, specificando la dimensione massima del buffer.
 * 
 * - `strftime`: Formatta e stampa una data in una stringa leggibile:
 *   ```c
 *   strftime(dateStr, sizeof(dateStr), "%b %d %H:%M", localtime(&fileInfo.st_mtime));
 *   ```
 *   In questo caso, la data di ultima modifica del file viene convertita in formato leggibile 
 *   (es., "Oct 05 15:30").
 * 
 * **Differenze principali tra `printf` e `snprintf`:**
 * - `printf`: Stampa direttamente su `stdout` (console).
 * - `snprintf`: Scrive in un buffer specificato dall'utente, permettendo un controllo sicuro sulla dimensione del buffer.
 * 
 * **Esempi nel programma:**
 * 1. `snprintf` è usato per costruire il percorso completo del file (`filePath`), evitando di superare i limiti di memoria.
 * 2. `printf` è usato per stampare informazioni direttamente sulla console in formato leggibile.
 * 3. `strftime` è usato per formattare la data in modo comprensibile per l'utente.
 * 
 * Questo approccio consente di combinare efficienza (costruzione sicura delle stringhe) e leggibilità
 * (output dettagliato e ben formattato).
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printFileInfo(const char* dirName, const char* fileName) {
    struct stat fileInfo;
    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/%s", dirName, fileName);

    if (stat(filePath, &fileInfo) < 0) {
        perror("Errore nel recupero delle informazioni del file");
        return;
    }

    printf("%llu ", fileInfo.st_size); // Dimensione del file

    // Permessi del file
    printf((S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
    printf((fileInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileInfo.st_mode & S_IROTH) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXOTH) ? "x" : "-");
    
    // Proprietario e gruppo
    struct passwd *pw = getpwuid(fileInfo.st_uid);
    struct group  *gr = getgrgid(fileInfo.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    // Data di ultima modifica
    char dateStr[128];
    strftime(dateStr, sizeof(dateStr), "%b %d %H:%M", localtime(&fileInfo.st_mtime));
    printf(" %s", dateStr);

    // Nome del file
    printf(" %s\n", fileName);
}


int main(int argc, char *argv[]) {
    DIR *dirp;
    struct dirent *dirent;

    if (argc != 2) {
        fprintf(stderr, "Errore: manca inputfile. Uso: %s <directory>\n", argv[0]);
        return 1;
    }

    dirp = opendir(argv[1]);
    if (dirp == NULL) {
        perror("Errore nell'apertura della directory");
        return 1;
    }

    while ((dirent = readdir(dirp)) != NULL) {
        printFileInfo(argv[1], dirent->d_name);
    }

    closedir(dirp);
    return 0;
}

