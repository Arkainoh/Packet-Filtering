#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "time.h"
#include "unistd.h"
//#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

#define BUF_LEN 1024

int main(int argc, char *argv[]) {

	char buffer[BUF_LEN];
	struct sockaddr_in server_addr, client_addr;
	int server_fd, client_fd;
	int len, msg_size;

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {// Create Socket
		printf("Server : Can't open stream socket\n");
		exit(0);
	}
	
	memset(&server_addr, 0x00, sizeof(server_addr));
	//server_addr로 시작하는 메모리 주소부터 sizeof(server_addr)개의 바이트를 0x00으로 채움
	//value는 unsigned char형태로 변환됨
	//return값으로 server_addr 포인터가 리턴된다.
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY : Server의 IP주소를 찾아줌
	server_addr.sin_port = htons(1234);
	//주소를 초기화한다.

	if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		//초기화한 주소를 소켓에 할당한다.
	  printf("Server : Can't bind local address.\n");
		exit(0);
	}
  
	if(listen(server_fd, 5) < 0) { //클라이언트로부터 연결 요청을 대기하는 상태로 설정
	  printf("Server : Can't listening connect.\n");
		exit(0);
	}

	len = sizeof(client_addr);
	while(1) {
		memset(buffer, 0x00, sizeof(buffer));

		printf("Server : Waiting for client...\n");
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
		//client로부터 요청이 들어올 때까지 blocking 상태로 대기한다.

		if(client_fd < 0) {
			printf("Server : Accept failed.\n");
			exit(0);
		}
		
		if(msg_size = read(client_fd, buffer, sizeof(buffer)) == -1) //client가 보낸 data를 읽는다.
			puts("Server : Read failed.\n");
	  else {
			write(client_fd, buffer, strlen(buffer)); //client에게 data를 보낸다.
			printf("Client : ");
			puts(buffer);
		}

		close(client_fd);
	}
	close(server_fd);
	return 0;
}

