#include "stdio.h"
#include "stdlib.h" //exit(0)
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

#define BUF_LEN 1024

int main(int argc, char *argv[]) {
	
	char buffer[BUF_LEN];
	struct sockaddr_in server_addr, client_addr;
	int server_fd, client_fd;
	int len, msg_size;

	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Can't open stream socket\n");
		exit(0);
	}
	
  return 0;
}
