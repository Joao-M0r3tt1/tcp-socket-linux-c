/* sockets-server.c */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8181    /* TCP standard - port the server is listening on */
#define BUF 512    /* buffer size */

int main(void) {
	int server_fd, client_fd;    /* socket file descriptor */
	socklen_t addrlen = 0; /* value required for accept() function */
	struct sockaddr_in srv, cli;
	char buffer[BUF], *data = "httpd v1.0 | Hello from server!\n";

	memset(&srv, 0, sizeof(srv));
	memset(&cli, 0, sizeof(cli));

	/* socket create and verification */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0) {
		printf("socket() error! Socket creation failed!\n");
		return -1;
	}

	/* assign connection family, satandard IP and PORT */
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = 0;    /* or INADDR_ANY; */
	srv.sin_port = htons(PORT);

	/* binding newly created socket to given IP and verification */
	if(bind(server_fd, (struct sockaddr *)&srv, sizeof(srv))) {
		printf("bind() error! Socket bind failed!\n");
		/* close the socket */
		close(server_fd);
		return -1;
	}

	/* server is ready to listen and verification */
	if(listen(server_fd, 5)) {
		printf("listen() error! Listen failed!\n");
		/* close the socket */
		close(server_fd);
		return -1;
	}
	printf("Listening on 0.0.0.0:%d\n\n", PORT);

	/* accept the data packet from client and verification */
	client_fd = accept(server_fd, (struct sockaddr *)&srv, &addrlen);
	if(client_fd < 0) {
		printf("accept() error! Server accept failed!\n");
		/* close the socket */
		close(server_fd);
		return -1;
	}
	printf("Client connected!\n");
	
	/* receive message from client - read the message from client and copy it in buffer */
	read(client_fd, buffer, (BUF - 1));
	/* send message to client */
	write(client_fd, data, strlen(data));

	/* close the connected sockets */
	close(client_fd);
	/* close the listening socket */
	close(server_fd);

	printf("\nFrom client: %s\n", buffer);
	puts("Server exit...\nConnection closed!");

	return 0;
}

