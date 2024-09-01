#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	int   sockfd;
	int   conn;
	char *buffer;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {AF_INET, htons(9999), 0};
	conn = connect(sockfd, &addr, sizeof(addr));
	if (conn == -1)
	{
		perror("Connection failed");
		return (EXIT_FAILURE);
	}
	struct pollfd fds[2] = {{0, POLLIN, 0}, {sockfd, POLLIN, 0}};
	while (true)
	{
		buffer = calloc(256, sizeof(char));
		poll(fds, 2, 50000);
		if (fds[0].revents & POLLIN)
		{
			read(0, buffer, 255);
			send(sockfd, buffer, 255, 0);
		}
		else if (fds[1].revents & POLLIN)
		{
			if (recv(sockfd, buffer, 255, 0) == 0)
				return (EXIT_SUCCESS);
			printf("%s\n", buffer);
		}
	}
	return (EXIT_SUCCESS);
}
