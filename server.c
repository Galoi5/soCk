#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	int   sockfd;
	int   clientfd;
	int   b;
	char *buffer;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {AF_INET, htons(9999), 0};
	b = bind(sockfd, &addr, sizeof(addr));
	if (b == -1)
	{
		perror("Binding error");
		return (EXIT_FAILURE);
	}
	listen(sockfd, 10);
	clientfd = accept(sockfd, 0, 0);
	struct pollfd fds[2] = {{0, POLLIN, 0}, {clientfd, POLLIN, 0}};
	while (1)
	{
		buffer = calloc(256, sizeof(char));
		poll(fds, 2, 50000);
		if (fds[0].revents & POLLIN)
		{
			read(0, buffer, 255);
			send(clientfd, buffer, 255, 0);
		}
		else if (fds[1].revents & POLLIN)
		{
			if (recv(clientfd, buffer, 255, 0) == 0)
				return (EXIT_SUCCESS);
			printf("%s\n", buffer);
		}
	}
	return (EXIT_SUCCESS);
}
