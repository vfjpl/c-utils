#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>

///https://en.wikipedia.org/wiki/Berkeley_sockets

int tcp_client_connect(uint32_t addr, uint16_t port)
{
	struct sockaddr_in client_addr = {0};
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = htonl(addr);

	int client_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_fd < 0)
	{
		return -1;
	}
	if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(client_fd);
		return -1;
	}
	if(connect(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0)
	{
		close(client_fd);
		return -1;
	}

	return client_fd;
}

int tcp_server_create(uint32_t addr, uint16_t port)
{
	int server_opt = 1;
	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(addr);

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
	if(fcntl(client_fd, F_SETFL, O_NDELAY) < 0)
	{
		close(client_fd);
		return -1;
	}

	return client_fd;
}
