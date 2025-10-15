#ifndef TCP_UTILS_H_INCLUDED
#define TCP_UTILS_H_INCLUDED

#include <arpa/inet.h>

int tcp_client_connect(const char* name, const char* port);
int tcp_server_create(uint16_t port);
int tcp_server_accept(int server_fd, struct sockaddr* addr, socklen_t* addrlen);

#endif // TCP_UTILS_H_INCLUDED
