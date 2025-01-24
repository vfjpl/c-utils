#ifndef TCP_H_INCLUDED
#define TCP_H_INCLUDED

#include <netinet/in.h>

int tcp_client_connect(const char* name, const char* port);
int tcp_server_create(uint16_t port);
int tcp_server_accept(int server_fd, struct sockaddr_in* addr);

#endif // TCP_H_INCLUDED
