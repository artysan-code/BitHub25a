#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      // perror(), printf(), fwrite()
#include <string.h>     // memset(), strlen()
#include <unistd.h>     // close(), read(), write()
#include <arpa/inet.h>  // socket(), connect(), htons(), htonl(), inet_pton(), inet_ntop()
#include <sys/types.h>
#include <sys/socket.h> // struct sockaddr, struct sockaddr_in, getsockname()


int main(void) {

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
  
    struct timeval timeo;
    timeo.tv_sec = 5;      //  secondo
    timeo.tv_usec = 0;    


    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeo, sizeof(timeo));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeo, sizeof(timeo));

    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    peeraddr.sin_port = htons(8000);

    uint16_t arg1;
    uint16_t arg2;
    uint16_t message[2];
    while (1) {
        int s = scanf("%hu %hu", &arg1, &arg2);
        if (s == EOF) {
            break;
        }
        if (s != 2) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} /* svuota il buffer contenente il caratteri successi al punto di errore */
            continue; /* passa alla iterazione successiva, riprendendo dalla lettura dell'input */
        }
        message[0] = htons(arg1);
        message[1] = htons(arg2);

        ssize_t nwritten = sendto(sockfd, &message, sizeof(message), 0, (struct sockaddr *) &peeraddr, sizeof(peeraddr));

        if (nwritten == -1) {
            perror("send");
            continue;
        }

        uint16_t sum;

        struct sockaddr_in replyieraddr;
        socklen_t replieraddrlen = sizeof(replyieraddr);
        memset(&replyieraddr, 0, sizeof(replyieraddr));

        do {
            ssize_t nread = recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *) &replyieraddr, &replieraddrlen);
            if (nread == -1) {
                perror("recv");
                close(sockfd);
                exit(EXIT_FAILURE);
            }
        } while(replieraddrlen != sizeof(peeraddr) || memcmp(&replyieraddr, &peeraddr, replieraddrlen) != 0);

        printf("%hu + %hu = %hu\n", arg1, arg2, ntohs(sum));
    }
    
    close(sockfd);

    return EXIT_SUCCESS;
}
