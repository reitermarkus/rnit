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

const int buffer_size = 256;

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

  char buffer[buffer_size];

  struct sockaddr_in server;
  struct sockaddr client;

  int socket_server = socket(AF_INET , SOCK_STREAM , 0);

  server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(PORT));

  if (bind(socket_server, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("bind");
  }

  listen(socket_server, 3);

  if(accept(socket_server, &client, (socklen_t*)sizeof(struct sockaddr_in))) {
    perror("accept");
  }

  printf("client connected.\n");


  memset(buffer, '\0', buffer_size);

  if(read(socket_server, buffer, buffer_size - 1)) {
    perror("read");
  }

  printf(buffer);
  
  return 0;
}
