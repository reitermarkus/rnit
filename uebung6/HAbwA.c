#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h> // struct sockaddr
#include <sys/socket.h>


#include <arpa/inet.h> // htons

#include <netdb.h>

// #include <netinet/ip.h>
#include <netinet/in.h> // IPPROTO_RAW, IPPROTO_IP, IPPROTO_TCP, INET_ADDRSTRLEN


#include <errno.h>

#include "load_file.h"
#include "tokenize.h"
#include "address_info.h"

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: %s\n", "Exactly one file must be specified.");
    exit(EXIT_FAILURE);
  }

  const char* file_content = load_file(argv[1]);

  size_t line_count;
  char** lines = tokenize(file_content, "\n", &line_count);

  printf("%ld lines\n", line_count);

  for (size_t i = 0; i < line_count; i++) {
    printf("line %ld:\n", i);

    size_t token_count;
    char** tokens = tokenize(lines[i], " ", &token_count);

    for (size_t j = 0; j < token_count; j++) {
      printf("  token %ld: %s\n", j, tokens[j]);
    }
  }

  char buffer[BUFFER_SIZE];

  struct sockaddr_in server;
  struct sockaddr client;

  int socket_server = socket(AF_INET , SOCK_STREAM , 0);
  int client_socket;

  server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(PORT));

  if (bind(socket_server, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("bind");
    return -1;
  }

  listen(socket_server, 3);

  socklen_t client_len = sizeof(client);

  if((client_socket = accept(socket_server, &client, &client_len)) < 0) {
    perror("accept");
    return -1;
  }

  printf("client connected.\n\n");

  memset(buffer, '\0', BUFFER_SIZE);

  if(read(client_socket, buffer, BUFFER_SIZE - 1) == -1) {
    perror("read");
    return -1;
  }

  printf("%s", buffer);

  return 0;
}
