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
	
	char buffer[BUF_LEN];
	struct sockaddr_in server_addr, client_addr;
	int client_fd;
	int len, msg_size;

	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Can't open stream socket\n");
		exit(0);
	}
  
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
		printf("Connection failed");
	}

  return 0;
}
