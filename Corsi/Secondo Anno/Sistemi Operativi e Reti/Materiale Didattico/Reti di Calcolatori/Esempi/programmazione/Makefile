CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: echo_server_tcp echo_client_tcp echo_client_tcp2 oneshot_client_tcp http_client sum_client_udp sum_server_udp echo_server_tcp2 sum_client_udp2

# prima esercitazione

echo_server_tcp: echo_server_tcp.c utils.c utils.h

echo_client_tcp: echo_client_tcp.c utils.c utils.h

echo_client_tcp2: echo_client_tcp2.c

# seconda esercitazione

http_client: http_client.c utils.c utils.h

echo_server_tcp2: echo_server_tcp2.c utils.c utils.h

oneshot_client_tcp: oneshot_client_tcp.c utils.c utils.h

sum_server_udp: sum_server_udp.c

sum_client_udp: sum_client_udp.c

sum_client_udp2: sum_client_udp2.c