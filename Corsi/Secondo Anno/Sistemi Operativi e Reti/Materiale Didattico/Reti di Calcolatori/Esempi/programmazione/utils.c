#include "utils.h"

/*
    La funzione readAll tenta di leggere esattamente count byte dal 
    file descriptor sockfd (tipicamente una socket), memorizzandoli nel 
    buffer buf. Poiché la read() di POSIX può restituire meno byte di quelli richiesti, 
    la funzione effettua più chiamate fino a completare la lettura o incontrare un errore.
    Restituisce il numero totale di byte letti oppure -1 in caso di errore.
*/
ssize_t readAll(int sockfd, char * buf, size_t count)
{
    size_t total_read = 0;
    while (total_read < count) {
        /*
            Legge i byte rimanenti (count - total_read) e li copia nel buffer
            a partire dalla posizione successiva ai byte già letti (buf + total_read).
        */
        ssize_t nread = read(sockfd,
                            buf + total_read,
                            count - total_read);

        if (nread == -1) { /* errore */
            return -1;
        }

        if (nread == 0) { /* EOF oppure richiesta di 0 byte: non ha senso continuare la lettura */
            break; /* restituiamo quanto letto finora */
        }

        total_read += nread;
    }
    return (ssize_t)total_read;
}

/*
    Scrive esattamente 'count' byte sulla socket 'sockfd'. Poiché write() può
    trasferire meno byte di quelli richiesti in una singola chiamata, la
    funzione continua a inviare i byte rimanenti finché non ha scritto
    l'intero buffer o finché non si verifica un errore. Restituisce il numero
    totale di byte inviati oppure -1 in caso di errore.
*/
ssize_t writeAll(int sockfd, const char * buf, size_t count)
{
    size_t total_written = 0;
    while (total_written < count)
    {
        /*
            Tenta di scrivere tutti i byte richiesti. Poiché write() può
            restituire meno byte di quelli richiesti, invia i byte rimanenti
            (count - total_written) a partire dalla posizione successiva
            nel buffer (buf + total_written).
        */
        ssize_t nwritten = write(sockfd,
                                buf + total_written,
                                count - total_written);

        if (nwritten == -1) {
            return -1;
        }

        if (nwritten == 0) { /* scrittura di zero byte: non ha senso continuare la scrittura */
            return total_written;
        }

        total_written += nwritten;

    }
    return (ssize_t)total_written;
}