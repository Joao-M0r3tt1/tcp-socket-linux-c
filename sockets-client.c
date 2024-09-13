/* sockets-client.c */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP "0.0.0.0"    /* 0.0.0.0 or 127.0.0.1 - localhost IP address */
/* test --> www.google.se - IP address: `ping www.google.se` */
#define PORT 8181    /* TCP standard */	
/* test --> HTTP - standard port: 80 */
#define BUF 512    /* buffer size */

int main(void) {
	int client_fd;    /* socket file descriptor */
	struct sockaddr_in servaddr;
	char buffer[BUF], *data = "HEAD / HTTP/1.0 | Hello from client\n\n";    /* test --> HEAD / HTTP/1.0\n\n */
	
	memset(&servaddr, 0, sizeof(servaddr));

	/* socket create and verification */
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_fd < 0) {
		printf("socket() error! Socket creation failed!\n");
		return -1;
	}

	/* assign connection IP, PORT and family */
	servaddr.sin_addr.s_addr = inet_addr(IP);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	/* connect the client sockt to server socket and verification */
	if(connect(client_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		printf("connect() error! Connection with the server failed!\n");
		/* close the socket */
		close(client_fd);
		return -1;
	}

	/* send message to server */
	write(client_fd, data, strlen(data));
	/* receive message from server - read the message from server and copy it in buffer */
	read(client_fd, buffer, (BUF - 1));

	/* close the connected socket */
	close(client_fd);

	printf("\nFrom server: %s\n", buffer);
	puts("\nClient exit...");

	return 0;
}
