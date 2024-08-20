#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

///https://en.wikipedia.org/wiki/Berkeley_sockets

int tcp_client_connect(const char* name, const char* port)
{
	struct addrinfo* addr = NULL;
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int errcode = getaddrinfo(name, port, &hints, &addr);
	if(errcode < 0)
	{
		return errcode;
	}

	int client_fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if(client_fd < 0)
	{
		freeaddrinfo(addr);
		return EAI_SYSTEM;
	}
	if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(client_fd);
		freeaddrinfo(addr);
		return EAI_SYSTEM;
	}
	if(connect(client_fd, addr->ai_addr, addr->ai_addrlen) < 0)
	{
		close(client_fd);
		freeaddrinfo(addr);
		return EAI_SYSTEM;
	}

	freeaddrinfo(addr);
	return client_fd;
}

int tcp_server_create(uint16_t port)
{
	int opt = 1;
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_fd < 0)
	{
		return -1;
	}
	if(fcntl(server_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(listen(server_fd, 0) < 0)
	{
		close(server_fd);
		return -1;
	}

	return server_fd;
}

int tcp_server_accept(int server_fd)
{
	int client_fd = accept(server_fd, NULL, NULL);
	if(client_fd < 0)
	{
		return -1;
	}
	if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(client_fd);
		return -1;
	}

	return client_fd;
}
