#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf()
#include <string.h>     // memset()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // inet_pton(), inet_ntop(), htons(), ntohs()
#include <netinet/in.h> // struct sockaddr_in, INADDR_ANY
#include <sys/socket.h> // socket(), bind(), listen(), accept(),
                        // setsockopt(), SOL_SOCKET, SO_REUSEADDR,
                        // AF_INET, INET_ADDRSTRLEN, SOCK_STREAM, socklen_t

#include "utils.h"      // writeAll(), readAll()

/*
    Un semplice server echo, che ritrasmette tutto ciò che ha ricevuto.
*/
int main(void) {

    const int BACKLOG = 2;
    const int BUF_SIZE = 5;
    const int PORT = 9000;

    int listenfd = socket(AF_INET, SOCK_STREAM, 0 /* oppure IPPROTO_TCP */);
    if (listenfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Permette il riutilizzo della porta dopo un riavvio del server
    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    /*
        Inizializzazione dell'indirizzo del server:
        - azzera la struttura
        - imposta la famiglia AF_INET
        - imposta l'indirizzo IP (0.0.0.0 = tutte le interfacce)
        - imposta la porta in formato network byte order
    */
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, "0.0.0.0", &serveraddr.sin_addr) <= 0) {
        perror("inet_pton");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    serveraddr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("bind");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, BACKLOG) == -1) {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %d...\n", PORT);

    // server iterativo: gestisce una connessione alla volta
    while (1) {

        struct sockaddr_in peeraddr;
        socklen_t peeraddrlen = sizeof(peeraddr);

        int connfd = accept(listenfd, (struct sockaddr *)&peeraddr, &peeraddrlen);
        if (connfd == -1) {
            perror("accept");
            continue;  // Non chiudiamo il server per un errore di accept
        }

        /*
            Esempio di come ottenere l'indirizzo locale associato alla socket:
            
            struct sockaddr_in myaddr;
            socklen_t mylen = sizeof(myaddr);
            if (getsockname(connfd, (struct sockaddr *)&myaddr, &mylen) == -1) {
                // gestione dell'errore
            }
        */

        /*
            Esempio di come ottenere l'indirizzo del peer (client):
            
            struct sockaddr_in peeraddr;
            socklen_t peeraddrlen = sizeof(peeraddr);
            if (getpeername(connfd, (struct sockaddr *)&peeraddr, &peeraddrlen) == -1) {
                perror("getpeername");
            }
        */

        char addrstr[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &peeraddr.sin_addr, addrstr, sizeof(addrstr)) == NULL) {
            perror("inet_ntop");
            close(connfd);
            continue;
        }

        printf("Connessione accettata da %s:%d\n",
               addrstr,
               ntohs(peeraddr.sin_port));

        char buffer[BUF_SIZE]; /* buffer molto piccolo: scopo didattico */

        while (1) {
            ssize_t nread = read(connfd, buffer, sizeof(buffer));

            if (nread == -1) {
                perror("read");
                break;
            }

            if (nread == 0) {
                // Il client ha chiuso la connessione
                break;
            }

            ssize_t nwritten = writeAll(connfd, buffer, nread);
            if (nwritten == -1) {
                perror("writeAll");
                break;
            }
        }

        close(connfd);
        printf("Connessione chiusa.\n");
    }

    /* 
        Questa riga viene eseguita solo in caso di uscita dal ciclo infinito;
        con una gestione dei segnali potremmo interrompere il loop e arrivare qui.
    */
    close(listenfd);
    return EXIT_SUCCESS;
}
