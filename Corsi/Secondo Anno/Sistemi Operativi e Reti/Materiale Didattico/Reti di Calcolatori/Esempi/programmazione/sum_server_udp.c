#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf(), fwrite()
#include <string.h>     // memset(), strlen()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // socket(), connect(), htons(), htonl(), inet_pton(), inet_ntop()
#include <sys/types.h>
#include <sys/socket.h> // struct sockaddr, struct sockaddr_in, getsockname()
#include <netdb.h>


int main(void) {

    struct addrinfo hints, *res, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    int err = getaddrinfo(NULL, "8000", &hints, &res);
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

        if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;
        }

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "bind fallita su tutti gli indirizzi\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    memset(&client_addr, 0, client_addr_len);
    
    uint16_t message[2];

    while (1) {
        int nread = recvfrom(sockfd, &message, sizeof(message), 0, (struct sockaddr *)&client_addr, &client_addr_len);

        if (nread == -1) {
            perror("recvfrom");
            continue;
        }

        char hoststr[NI_MAXHOST];
        char portstr[NI_MAXSERV];
        int s = getnameinfo((struct sockaddr *)&client_addr, client_addr_len,
                            hoststr, sizeof(hoststr),
                            portstr, sizeof(portstr),
                            NI_NUMERICHOST | NI_NUMERICSERV);
        if (s == 0) {
            fprintf(
                stdout, 
                "Ricevuto messaggio da %s#%s", 
                hoststr,
                portstr
            );
        } else {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        }


        if (nread != sizeof(message)) {
            fprintf(stderr, "Ricevuti %d byte, attesi %ld byte", nread, sizeof(message));
            continue;
        }

        uint16_t sum = htons(ntohs(message[0]) + ntohs(message[1]));

        sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&client_addr, client_addr_len);
    }
    
    close(sockfd);

    return EXIT_SUCCESS;
}
