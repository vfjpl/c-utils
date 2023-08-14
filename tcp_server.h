#ifndef TCP_SERVER_H_INCLUDED
#define TCP_SERVER_H_INCLUDED

#include <stdint.h>

int tcp_server_create(uint16_t port);
int tcp_server_accept(int server_fd);

#endif // TCP_SERVER_H_INCLUDED
