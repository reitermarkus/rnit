#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <errno.h>

#include "address_info.h"

int main(int argc , char *argv[]) {
  (void)argc;
  (void)argv;

  struct sockaddr_in server;

  int client_socket;

  if((client_socket = socket(AF_INET , SOCK_STREAM , 0)) == -1) {
    perror("socket");
    return -1;
  }

  server.sin_addr.s_addr = inet_addr(HOST);
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(PORT));

  if(connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    return -1;
  }

  printf("connected to server.\n");

  printf("Enter request...\n");

  char send_buffer[BUFFER_SIZE];
  char receive_buffer[BUFFER_SIZE];

  fgets(send_buffer, BUFFER_SIZE - 1, stdin);
  write(client_socket, send_buffer, BUFFER_SIZE);

  if(read(client_socket, receive_buffer, BUFFER_SIZE - 1) == -1) {
    perror("read");
    return -1;
  }

  printf("%s\n", "resonse from server:");
  printf("%s", receive_buffer);

  close(client_socket);

  return 0;
}
