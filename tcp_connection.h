#ifndef TCP_CONNECTION_H_INCLUDED
#define TCP_CONNECTION_H_INCLUDED

#include <arpa/inet.h>

int tcp_server_create(uint16_t port);
int tcp_server_accept(int server_fd, struct sockaddr* addr, socklen_t* addrlen);

#endif // TCP_CONNECTION_H_INCLUDED
