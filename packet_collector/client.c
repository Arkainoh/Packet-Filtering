#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "string.h"
#include "sys/time.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/stat.h"
#include "unistd.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#define BUF_LEN 1024
#define SERVER_ADDR "192.168.56.103"
#define OUTPUT_DIR "output"

void* connect_server(void *data) {
	struct sockaddr_in server_addr;
	struct timeval start_time, received_time;
	int client_socket, port=*((int *)data);
	char buffer[BUF_LEN];
	char outputfiledir[10];
	char outputfilepath[20] = OUTPUT_DIR;
	FILE * outputfile;
	struct tm *tm;
									
	//build socket
	client_socket=socket(PF_INET, SOCK_STREAM, 0);
	
	if(client_socket==-1) {
		printf("Port #%d : Socket creation failed.\n", port);
		exit(1);
	}
											
	//connect server
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDR);
	
	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
	{
		printf("Port #%d : Connection failed.\n", port);
		exit(1);
	}
																
	//receive and write data
	sprintf(outputfiledir, "/%d.txt", port);
	strcat(outputfilepath, outputfiledir);
	outputfile=fopen(outputfilepath, "w");
																
	gettimeofday(&start_time, NULL);
	gettimeofday(&received_time, NULL);

	while(received_time.tv_sec-start_time.tv_sec < 3) {
	  read(client_socket, buffer, BUF_LEN);
		gettimeofday(&received_time, NULL);
		tm=localtime(&received_time.tv_sec);
		fprintf(outputfile, "%02d:%02d:%02d.%03ld %ld %s\n",
				tm->tm_hour, tm->tm_min, tm->tm_sec, received_time.tv_usec/1000, strlen(buffer), buffer);
	}
												
	fclose(outputfile);
	return 0;
}

int main() {
	pthread_t p_thread[5];
	int thr_id, status, port_number[5] = {5555,6666,7777,8888,9999}, i;
	mkdir(OUTPUT_DIR, 0755);
	for(i=0;i<5;i++) {
		thr_id = pthread_create(&p_thread[i], NULL, connect_server, (void *)&port_number[i]);
	}
						    
	for(i=0;i<5;i++) {
		pthread_join(p_thread[i], (void **) &status);
	}
										
	return 0;
}
