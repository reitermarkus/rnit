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
  }

  server.sin_addr.s_addr = inet_addr("0.0.0.0");
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(PORT));

  if(connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
  }

  printf("client connected to server.\n");

  return 0;
}