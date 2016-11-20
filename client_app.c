#include "stdio.h"
#include "stdlib.h" //exit
#include "string.h" //memset
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#define BUF_LEN 1024

int main(int argc, char *argv[]) {
	
	char rbuffer[BUF_LEN];
	char wbuffer[BUF_LEN];
	struct sockaddr_in server_addr, client_addr;
	int client_fd;
	int msg_size;

	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Can't open stream socket\n");
		exit(0);
	}
  
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
		printf("Connection failed\n");
		exit(0);
	}
	
	printf("Message to server:\n");
	fgets(wbuffer, sizeof(wbuffer), stdin);
	wbuffer[strlen(wbuffer)-1] = '\0';
	write(client_fd, wbuffer, strlen(wbuffer));
		
	if(msg_size = read(client_fd, rbuffer, sizeof(rbuffer)) == -1) {
		printf("Read failed.\n");
	} else {
		printf("Server : ");
		puts(rbuffer);
	}
	

	close(client_fd);
  return 0;
}
