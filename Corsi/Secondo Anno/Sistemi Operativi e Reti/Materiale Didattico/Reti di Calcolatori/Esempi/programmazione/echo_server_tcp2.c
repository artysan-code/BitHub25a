#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf()
#include <string.h>     // memset()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // inet_pton(), inet_ntop(), htons(), ntohs()
#include <netinet/in.h> // struct sockaddr_in, INADDR_ANY
#include <sys/socket.h> // socket(), bind(), listen(), accept(),
                        // setsockopt(), SOL_SOCKET, SO_REUSEADDR,
                        // AF_INET, INET_ADDRSTRLEN, SOCK_STREAM, socklen_t
#include <netdb.h>

#include "utils.h"      // writeAll(), readAll()

/*
    Un semplice server echo, che ritrasmette tutto ciò che ha ricevuto.
    La novità è l'uso di getaddrinfo per ottenere la struttura indirizzo
    da usare per fare la bind. 
*/
int main(void) {

    const int BACKLOG = 2;
    const int BUF_SIZE = 5;
    const char *PORT = "9000";

    struct addrinfo hints, *res, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    int err = getaddrinfo(NULL, PORT, &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);  
    }

    int listenfd;

    // Provo tutti i risultati finché uno funziona
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        listenfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (listenfd == -1)
            continue;

        // Permette il riutilizzo della porta dopo un riavvio del server
        int opt = 1;
        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
            perror("setsockopt");
            close(listenfd);
            exit(EXIT_FAILURE);
        }
            
        if (bind(listenfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;
        }

        close(listenfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "bind fallita su tutti gli indirizzi\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    memset(&client_addr, 0, client_addr_len);

    if (listen(listenfd, BACKLOG) == -1) {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %s...\n", PORT);

    // server iterativo: gestisce una connessione alla volta
    while (1) {

        struct sockaddr_storage peeraddr;
        socklen_t peeraddrlen = sizeof(peeraddr);

        int connfd = accept(listenfd, (struct sockaddr *)&peeraddr, &peeraddrlen);
        if (connfd == -1) {
            perror("accept");
            continue;  // Non chiudiamo il server per un errore di accept
        }

        char hoststr[NI_MAXHOST];
        char portstr[NI_MAXSERV];
        int s = getnameinfo((struct sockaddr *)&peeraddr, peeraddrlen,
                            hoststr, sizeof(hoststr),
                            portstr, sizeof(portstr),
                            NI_NUMERICHOST | NI_NUMERICSERV);

        if (s == 0) {
            printf("Connessione accettata da %s:%s\n",
                hoststr,
                portstr);
        } else {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        }
        
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
