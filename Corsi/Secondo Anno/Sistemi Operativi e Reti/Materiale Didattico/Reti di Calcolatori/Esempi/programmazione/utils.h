#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

ssize_t writeAll(int sockfd, const char * buf, size_t count);
ssize_t readAll(int sockfd, char * buf, size_t count);


#endif