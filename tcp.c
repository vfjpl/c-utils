#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

///https://en.wikipedia.org/wiki/Berkeley_sockets

int tcp_client_connect(const char* name, const char* port)
{
	struct addrinfo* list = NULL;
	struct addrinfo hints = {0};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int errcode = getaddrinfo(name, port, &hints, &list);
	if(errcode < 0)
	{
		return errcode;
	}

	for(struct addrinfo* p = list; p != NULL; p = p->ai_next)
	{
		int client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if(client_fd < 0)
		{
			continue;
		}
		if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
		{
			close(client_fd);
			continue;
		}
		if(connect(client_fd, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(client_fd);
			continue;
		}

		freeaddrinfo(list);
		return client_fd;
	}

	freeaddrinfo(list);
	return EAI_SYSTEM;
}

int tcp_server_create(uint16_t port)
{
	int opt = 1;
	struct sockaddr_in addres = {0};
	addres.sin_family = AF_INET;
	addres.sin_port = htons(port);
	addres.sin_addr.s_addr = htonl(INADDR_ANY);

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
	if(bind(server_fd, (struct sockaddr*)&addres, sizeof(addres)) < 0)
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
