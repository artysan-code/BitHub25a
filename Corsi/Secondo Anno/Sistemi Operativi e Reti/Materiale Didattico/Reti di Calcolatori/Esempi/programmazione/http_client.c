#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf(), fwrite()
#include <string.h>     // memset(), strlen()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // ntohs()
#include <sys/types.h>  // struct sockaddr, socklen_t
#include <sys/socket.h> // socket(), connect(), getsockname()
#include <netdb.h>      // getaddrinfo(), freeaddrinfo(), gai_strerror()
#include "utils.h"      // writeAll(), readAll()

int main(void) {

    const int MAX_LINE = 1024;

    struct addrinfo hints, *res, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;   // IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_protocol = 0;

    int err = getaddrinfo("httpbin.org", "http", &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    int sockfd = -1;

    // Provo tutti gli indirizzi finché uno funziona
    for (rp = res; rp != NULL; rp = rp->ai_next) {

        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "connect fallita su tutti gli indirizzi\n");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    // Uso sockaddr_storage per compatibilità IPv4/IPv6
    struct sockaddr_storage myaddr;
    socklen_t mylen = sizeof(myaddr);

    if (getsockname(sockfd, (struct sockaddr *)&myaddr, &mylen) == -1) {
        perror("getsockname");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Stampo la porta locale
    if (myaddr.ss_family == AF_INET) {
        struct sockaddr_in *v4 = (struct sockaddr_in *)&myaddr;
        printf("Client sulla porta %d...\n", ntohs(v4->sin_port));
    } else if (myaddr.ss_family == AF_INET6) {
        struct sockaddr_in6 *v6 = (struct sockaddr_in6 *)&myaddr;
        printf("Client sulla porta %d (IPv6)...\n", ntohs(v6->sin6_port));
    }

    /* 
       Nota: 
       Connection: close serve a fare in modo che il server chiuda la connessione
       dopo aver inviato la risposta; in questo modo si raggiungerà la condizione
       di EOF (End Of File), permettendo di interrompere il ciclo di lettura. 
       L'alternativa sarebbe stata effettuare il parsing dell'intestazione della 
       risposta per verificare il numero di byte contenuti nel corpo (tramite l'header
       Content-Length).
    */
    const char *request =
        "GET /get HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Connection: Close\r\n"
        "\r\n";

    writeAll(sockfd, request, strlen(request));

    char buffer[MAX_LINE];

    while (1) {
        ssize_t nread = read(sockfd, buffer, sizeof(buffer));
        if (nread == -1) {
            perror("read");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if (nread == 0)
            break;

        fwrite(buffer, 1, nread, stdout);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
