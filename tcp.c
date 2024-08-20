#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

///https://en.wikipedia.org/wiki/Berkeley_sockets

int tcp_client_connect(const char* node, const char* service)
{
	struct addrinfo* res = NULL;
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int errcode = getaddrinfo(node, service, &hints, &res);
	if(errcode < 0)
	{
		return errcode;
	}

	int client_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if(client_fd < 0)
	{
		freeaddrinfo(res);
		return EAI_SYSTEM;
	}
	if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(client_fd);
		freeaddrinfo(res);
		return EAI_SYSTEM;
	}
	if(connect(client_fd, res->ai_addr, res->ai_addrlen) < 0)
	{
		close(client_fd);
		freeaddrinfo(res);
		return EAI_SYSTEM;
	}

	freeaddrinfo(res);
	return client_fd;
}

int tcp_server_create(uint16_t port)
{
	int server_opt = 1;
	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

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
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &server_opt, sizeof(server_opt)) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
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
