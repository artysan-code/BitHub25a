#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf(), fwrite()
#include <string.h>     // memset(), strlen()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // socket(), connect(), htons(), htonl(), inet_pton(), inet_ntop()
#include <sys/socket.h> // struct sockaddr, struct sockaddr_in, getsockname()

#include "utils.h"      // writeAll(), readAll()

/*
    Un semplice client per il server echo. Legge una riga per volta, fino a EOF (premere CTLR + D all'inizio di una riga)
*/
int main(void) {

    const int PORT = 9000;
    const int MAX_LINE = 1024;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    int ret = inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
    if (ret <= 0) {
        if (ret == 0) {
            fprintf(stderr, "inet_pton: indirizzo non valido\n");
        } else { /* ret == -1 */
            perror("inet_pton");
        }
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    serveraddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in myaddr;
    socklen_t mylen = sizeof(myaddr);
    if (getsockname(sockfd, (struct sockaddr *)&myaddr, &mylen) == -1) {
        perror("getsockname");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Client sulla porta %d...\n", ntohs(myaddr.sin_port));

    char buffer[MAX_LINE + 1];

    while (fgets(buffer, sizeof(buffer), stdin)) {

        ssize_t nwritten = writeAll(sockfd, buffer, strlen(buffer));
        if (nwritten == -1) {
            perror("writeAll");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        ssize_t nread = readAll(sockfd, buffer, nwritten);
        if (nread == -1) {
            perror("readAll");
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
