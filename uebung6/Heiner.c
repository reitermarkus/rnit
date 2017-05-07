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

#include "buffer_size.h"

int main(int argc , char *argv[]) {
  const char* HOST = argv[1];
  const int PORT = atoi(argv[2]);

  struct sockaddr_in server;

  int client_socket;

  if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  server.sin_addr.s_addr = inet_addr(HOST);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

  if(connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  printf("Connected to server.\n");

  char send_buffer[BUFFER_SIZE];
  char receive_buffer[BUFFER_SIZE];

  for (int i = 3; i < argc; i++) {
    printf("Sending request to server: '%s'\n", argv[i]);

    memset(send_buffer, '\0', BUFFER_SIZE);
    sprintf(send_buffer, "%s\n", argv[i]);

    if(write(client_socket, send_buffer, strlen(send_buffer)) == -1) {
      perror("write");
      close(client_socket);
      exit(EXIT_FAILURE);
    }

    memset(receive_buffer, '\0', BUFFER_SIZE);
    if(read(client_socket, receive_buffer, BUFFER_SIZE) == -1) {
      perror("read");
      close(client_socket);
      exit(EXIT_FAILURE);
    }

    printf("Got resonse from server:\n%s", receive_buffer);
  }

  close(client_socket);

  return EXIT_SUCCESS;
}
