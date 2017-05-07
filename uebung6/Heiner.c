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

  if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  server.sin_addr.s_addr = inet_addr(HOST);
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(PORT));

  if(connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  printf("Connected to server.\n");

  printf("Enter request...\n");

  char send_buffer[BUFFER_SIZE];
  char receive_buffer[BUFFER_SIZE];

  fgets(send_buffer, BUFFER_SIZE - 1, stdin);

  if(write(client_socket, send_buffer, BUFFER_SIZE) == -1) {
    perror("write");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  if(read(client_socket, receive_buffer, BUFFER_SIZE - 1) == -1) {
    perror("read");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", "resonse from server:");
  printf("%s", receive_buffer);

  close(client_socket);

  return EXIT_SUCCESS;
}
