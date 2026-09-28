#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf(), fwrite()
#include <string.h>     // memset(), strlen()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // socket(), connect(), htons(), htonl(), inet_pton(), inet_ntop()
#include <sys/socket.h> // struct sockaddr, struct sockaddr_in, getsockname()
#include <netdb.h>
#include "utils.h"      // writeAll(), readAll()

/*
    Un client TCP richiesta-risposta, che utilizza shutdown() per chiudere la connessione in scrittura.
    Usa getaddrinfo per ottenere la struttura indirizzo da usare per fare la connect. 
*/
int main(void) {

    const char * PORT = "9000";
    const int MAX_LINE = 1024;


    struct addrinfo hints, *res, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int err = getaddrinfo(NULL, PORT, &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);  
    }

    int sockfd;

    // Provo tutti i risultati finché uno funziona
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        // Permette il riutilizzo della porta dopo un riavvio del server
        int opt = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
            perror("setsockopt");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
            
        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;
        }

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "bind fallita su tutti gli indirizzi\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    struct sockaddr_storage myaddr;
    socklen_t myaddrlen = sizeof(myaddr);
    memset(&myaddr, 0, myaddrlen);

    if (getsockname(sockfd, (struct sockaddr *)&myaddr, &myaddrlen) == -1) {
        perror("getsockname");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char hoststr[NI_MAXHOST];
    char portstr[NI_MAXSERV];
    int s = getnameinfo((struct sockaddr *)&myaddr, myaddrlen,
                        hoststr, sizeof(hoststr),
                        portstr, sizeof(portstr),
                        NI_NUMERICHOST | NI_NUMERICSERV);

    if (s == 0) {
        printf("Client associato a %s#%s\n",
            hoststr,
            portstr);
    } else {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
    }

    char buffer[MAX_LINE + 1];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        ssize_t nwritten = writeAll(sockfd, buffer, strlen(buffer));
        if (nwritten == -1) {
            perror("writeAll");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        shutdown(sockfd, SHUT_WR);

        ssize_t nread = readAll(sockfd, buffer, nwritten);
        if (nread == -1) {
            perror("readAll");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, nread, stdout);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
